#include "ContourFiller.h"

#include <algorithm>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <sstream>
#include <stdexcept>
#ifdef _WIN32
#include <process.h>
#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace {
constexpr float kRadToDeg = 180.0f / static_cast<float>(M_PI);
}

ContourFiller::ContourFiller(float initialFillAngleDeg, float angleIncrementDeg, float fillSpacing, int contourCount,
    float controlBoard, float contourPower, float contourSpeed)
    : initialFillAngle(initialFillAngleDeg * static_cast<float>(M_PI) / 180.0f),
    angleIncrement(angleIncrementDeg * static_cast<float>(M_PI) / 180.0f),
    fillSpacing(fillSpacing),
    contourCount(contourCount),
    controlBoard(controlBoard),
    contourPower(contourPower),
    contourSpeed(contourSpeed) {
}

void ContourFiller::enablePySLMCheckerboard(const std::string& pythonExecutable,
    const std::string& scriptPath,
    float islandWidth,
    float islandOverlap,
    float islandOffset) {
    checkerboardPythonExecutable = pythonExecutable.empty() ? "python" : pythonExecutable;
    checkerboardScriptPath = scriptPath;
    checkerboardIslandWidth = islandWidth;
    checkerboardIslandOverlap = islandOverlap;
    checkerboardIslandOffset = islandOffset;
    usePySLMCheckerboard = true;
}

void ContourFiller::fillLayer(const std::vector<Polyline>& contours, int layerNumber) {
    commands.clear();

    float currentFillAngle = initialFillAngle + layerNumber * angleIncrement;

    bool generatedByPySLM = false;
    if (usePySLMCheckerboard) {
        generatedByPySLM = generateCheckerboardFillLinesWithPySLM(contours, currentFillAngle, layerNumber);
    }

    if (!generatedByPySLM) {
        generateFillLines(contours, currentFillAngle);
    }

    drawContours(contours);
}

void ContourFiller::generateFillLines(const std::vector<Polyline>& contours, float currentFillAngle) {
    if (contours.empty()) {
        return;
    }

    auto [minX, minY, maxX, maxY] = getBoundingBox(contours);

    float width = maxX - minX;
    float height = maxY - minY;

    float cosA = std::cos(currentFillAngle);
    float sinA = std::sin(currentFillAngle);
    float rotatedWidth = std::abs(width * cosA) + std::abs(height * sinA);
    float rotatedHeight = std::abs(width * sinA) + std::abs(height * cosA);

    std::vector<std::pair<Point, Point>> fillLines;
    float startX = -rotatedWidth / 2.0f;
    float endX = rotatedWidth / 2.0f;
    bool leftToRight = true;

    for (float y = -rotatedHeight / 2.0f; y <= rotatedHeight / 2.0f; y += fillSpacing) {
        Point start = unrotatePoint({ startX, y, 0.0f }, currentFillAngle);
        Point end = unrotatePoint({ endX, y, 0.0f }, currentFillAngle);

        if (!leftToRight) {
            std::swap(start, end);
        }

        float midX = (minX + maxX) / 2.0f;
        float midY = (minY + maxY) / 2.0f;
        start.x += midX;
        start.y += midY;
        end.x += midX;
        end.y += midY;

        fillLines.push_back({ start, end });
        leftToRight = !leftToRight;
    }

    for (const auto& line : fillLines) {
        std::vector<Point> intersections = findIntersections(line.first, line.second, contours);
        if (intersections.size() < 2) {
            continue;
        }

        for (size_t i = 0; i + 1 < intersections.size(); i += 2) {
            addCommand("jump_abs(" + formatPoint(intersections[i]) + ")");
            addCommand("mark_abs(" + formatPoint(intersections[i + 1]) + ")");
        }
    }
}

bool ContourFiller::generateCheckerboardFillLinesWithPySLM(const std::vector<Polyline>& contours,
    float currentFillAngle,
    int layerNumber) {
    namespace fs = std::filesystem;

    if (!usePySLMCheckerboard || checkerboardScriptPath.empty()) {
        return false;
    }

    if (!fs::exists(checkerboardScriptPath)) {
        std::cerr << "PySLM checkerboard script not found: " << checkerboardScriptPath << std::endl;
        return false;
    }

    auto now = std::chrono::steady_clock::now().time_since_epoch().count();
    fs::path inputPath = fs::temp_directory_path() / ("pyslm_checkerboard_input_" + std::to_string(now) + ".json");
    fs::path outputPath = fs::temp_directory_path() / ("pyslm_checkerboard_output_" + std::to_string(now) + ".txt");

    std::ofstream inputFile(inputPath);
    if (!inputFile.is_open()) {
        std::cerr << "Unable to open PySLM input file: " << inputPath << std::endl;
        return false;
    }

    inputFile << std::fixed << std::setprecision(6);
    inputFile << "{\n";
    inputFile << "  \"layer_number\": " << layerNumber << ",\n";
    inputFile << "  \"fill_angle_deg\": " << (currentFillAngle * kRadToDeg) << ",\n";
    inputFile << "  \"fill_spacing\": " << fillSpacing << ",\n";
    inputFile << "  \"island_width\": " << checkerboardIslandWidth << ",\n";
    inputFile << "  \"island_overlap\": " << checkerboardIslandOverlap << ",\n";
    inputFile << "  \"island_offset\": " << checkerboardIslandOffset << ",\n";
    inputFile << "  \"contours\": [\n";

    for (size_t i = 0; i < contours.size(); ++i) {
        const auto& contour = contours[i];
        inputFile << "    [\n";
        for (size_t j = 0; j < contour.points.size(); ++j) {
            const auto& point = contour.points[j];
            inputFile << "      [" << point.x << ", " << point.y << "]";
            if (j + 1 < contour.points.size()) {
                inputFile << ",";
            }
            inputFile << "\n";
        }
        inputFile << "    ]";
        if (i + 1 < contours.size()) {
            inputFile << ",";
        }
        inputFile << "\n";
    }

    inputFile << "  ]\n";
    inputFile << "}\n";
    inputFile.close();

#ifdef _WIN32
    std::filesystem::path pythonPath = checkerboardPythonExecutable.empty()
        ? std::filesystem::path(L"python")
        : std::filesystem::path(checkerboardPythonExecutable);

    std::wstring pythonExe = pythonPath.wstring();
    std::wstring scriptPathW = std::filesystem::path(checkerboardScriptPath).wstring();
    std::wstring inputPathW = inputPath.wstring();
    std::wstring outputPathW = outputPath.wstring();

    int exitCode = _wspawnlp(
        _P_WAIT,
        pythonExe.c_str(),
        pythonExe.c_str(),
        scriptPathW.c_str(),
        inputPathW.c_str(),
        outputPathW.c_str(),
        nullptr);
#else
    std::string pythonExe = checkerboardPythonExecutable.empty() ? "python" : checkerboardPythonExecutable;
    std::ostringstream commandStream;
    commandStream << "\"" << pythonExe << "\""
        << " \"" << checkerboardScriptPath << "\""
        << " \"" << inputPath.string() << "\""
        << " \"" << outputPath.string() << "\"";

    int exitCode = std::system(commandStream.str().c_str());
#endif
    if (exitCode != 0) {
#ifdef _WIN32
        std::wcerr << L"PySLM checkerboard script failed with exit code " << exitCode << std::endl;
        std::wcerr << L"Command: " << pythonExe << L" \"" << scriptPathW << L"\" \"" << inputPathW << L"\" \"" << outputPathW << L"\"" << std::endl;
        std::wcerr << L"Working directory: " << fs::current_path().wstring() << std::endl;
#else
        std::cerr << "PySLM checkerboard script failed with exit code " << exitCode << std::endl;
        std::cerr << "Command: " << commandStream.str() << std::endl;
        std::cerr << "Working directory: " << fs::current_path() << std::endl;
#endif
        std::error_code ec;
        fs::remove(inputPath, ec);
        fs::remove(outputPath, ec);
        return false;
    }

    std::ifstream outputFile(outputPath);
    if (!outputFile.is_open()) {
        std::cerr << "Unable to open PySLM output file: " << outputPath << std::endl;
        std::error_code ec;
        fs::remove(inputPath, ec);
        fs::remove(outputPath, ec);
        return false;
    }

    bool hasCommands = false;
    std::string line;
    while (std::getline(outputFile, line)) {
        line.erase(std::remove(line.begin(), line.end(), '\r'), line.end());
        if (line.empty()) {
            continue;
        }
        addCommand(line);
        hasCommands = true;
    }

    outputFile.close();
    std::error_code ec;
    fs::remove(inputPath, ec);
    fs::remove(outputPath, ec);

    return hasCommands;
}

void ContourFiller::drawContours(const std::vector<Polyline>& contours) {
    for (int i = 0; i < contourCount; ++i) {
        addCommand("write_da_x_list(" + std::to_string(controlBoard) + "," + std::to_string(contourPower) + ")");
        addCommand("set_mark_speed(" + std::to_string(contourSpeed * 0.1862156f) + ")");
        for (const auto& contour : contours) {
            if (contour.points.empty()) {
                continue;
            }
            addCommand("jump_abs(" + formatPoint(contour.points[0]) + ")");
            for (size_t j = 1; j < contour.points.size(); ++j) {
                addCommand("mark_abs(" + formatPoint(contour.points[j]) + ")");
            }
            if (contour.isClosed()) {
                addCommand("mark_abs(" + formatPoint(contour.points[0]) + ")");
            }
        }
    }
}

std::vector<Point> ContourFiller::findIntersections(const Point& start, const Point& end, const std::vector<Polyline>& contours) {
    std::vector<Point> intersections;

    for (const auto& contour : contours) {
        for (size_t i = 0; i < contour.points.size(); ++i) {
            const Point& p1 = contour.points[i];
            const Point& p2 = contour.points[(i + 1) % contour.points.size()];

            Point intersection{};
            if (lineIntersection(start, end, p1, p2, intersection)) {
                intersections.push_back(intersection);
            }
        }
    }

    std::sort(intersections.begin(), intersections.end(),
        [&start](const Point& a, const Point& b) {
            float da = (a.x - start.x) * (a.x - start.x) + (a.y - start.y) * (a.y - start.y);
            float db = (b.x - start.x) * (b.x - start.x) + (b.y - start.y) * (b.y - start.y);
            return da < db;
        });

    return intersections;
}

bool ContourFiller::lineIntersection(const Point& p1, const Point& p2, const Point& p3, const Point& p4, Point& intersection) {
    float x1 = p1.x, y1 = p1.y;
    float x2 = p2.x, y2 = p2.y;
    float x3 = p3.x, y3 = p3.y;
    float x4 = p4.x, y4 = p4.y;

    float denom = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
    if (std::abs(denom) < 1e-6f) {
        return false;
    }

    float ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denom;
    float ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denom;

    if (ua < 0.0f || ua > 1.0f || ub < 0.0f || ub > 1.0f) {
        return false;
    }

    intersection.x = x1 + ua * (x2 - x1);
    intersection.y = y1 + ua * (y2 - y1);
    intersection.z = 0.0f;
    return true;
}

void ContourFiller::addCommand(const std::string& command) {
    commands.push_back(command);
}

std::string ContourFiller::formatPoint(const Point& point) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(6) << point.x << "," << point.y;
    return oss.str();
}

void ContourFiller::writeCommands(const std::string& filename) const {
    std::ofstream outFile(filename, std::ios::app);
    if (!outFile) {
        throw std::runtime_error("Unable to open file: " + filename);
    }
    for (const auto& command : commands) {
        outFile << command << ";" << std::endl;
    }
}

void ContourFiller::writeLayerSeparator(const std::string& filename, int layerNumber) const {
    std::ofstream outFile(filename, std::ios::app);
    if (!outFile) {
        throw std::runtime_error("Unable to open file: " + filename);
    }
    outFile << "\n//;Layer " << layerNumber << " Fill Commands\n";
}

Point ContourFiller::rotatePoint(const Point& p, float angle) const {
    float cosA = std::cos(angle);
    float sinA = std::sin(angle);
    return {
        p.x * cosA - p.y * sinA,
        p.x * sinA + p.y * cosA,
        p.z
    };
}

Point ContourFiller::unrotatePoint(const Point& p, float angle) const {
    float cosA = std::cos(-angle);
    float sinA = std::sin(-angle);
    return {
        p.x * cosA - p.y * sinA,
        p.x * sinA + p.y * cosA,
        p.z
    };
}

std::tuple<float, float, float, float> ContourFiller::getBoundingBox(const std::vector<Polyline>& contours) const {
    float minX = std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();
    float maxX = std::numeric_limits<float>::lowest();
    float maxY = std::numeric_limits<float>::lowest();

    for (const auto& contour : contours) {
        for (const auto& point : contour.points) {
            minX = std::min(minX, point.x);
            minY = std::min(minY, point.y);
            maxX = std::max(maxX, point.x);
            maxY = std::max(maxY, point.y);
        }
    }

    return std::make_tuple(minX, minY, maxX, maxY);
}

bool ContourFiller::isPointInsideContours(const Point& p, const std::vector<Polyline>& contours) const {
    int intersectionCount = 0;
    for (const auto& contour : contours) {
        for (size_t i = 0; i < contour.points.size(); ++i) {
            const Point& p1 = contour.points[i];
            const Point& p2 = contour.points[(i + 1) % contour.points.size()];

            bool intersects = ((p1.y > p.y) != (p2.y > p.y)) &&
                (p.x < (p2.x - p1.x) * (p.y - p1.y) / (p2.y - p1.y) + p1.x);
            if (intersects) {
                intersectionCount++;
            }
        }
    }
    return (intersectionCount % 2) == 1;
}
