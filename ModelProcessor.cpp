#include "ModelProcessor.h"
#include "ContourBuilder.h"
#include "ContourFiller.h"

#include <cstdio>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

void ModelProcessor::processModel(const MultiSTLManager& manager, size_t modelIndex, float layerHeight, float directionVector[3]) {
    const auto& modelInfo = manager.getModelInfo(modelIndex);

    std::ostringstream outFileName;
    outFileName << "C:\\output\\model_" << modelIndex << "_output.txt";
    std::ofstream outFile(outFileName.str());

    if (!outFile) {
        std::cerr << "Failed to open output file: " << outFileName.str() << std::endl;
        return;
    }

    outFile << "Model " << modelIndex << " (material: " << modelInfo.material << ")" << std::endl;
    outFile << "Position: (" << modelInfo.position[0] << ", " << modelInfo.position[1] << ", " << modelInfo.position[2] << ")" << std::endl << std::endl;

    auto slices = manager.sliceSingleModel(modelIndex, layerHeight, directionVector);

    ContourBuilder contourBuilder;
    ContourFiller contourFiller(modelInfo.fillAngle, modelInfo.angleIncrement, modelInfo.fillSpacing, modelInfo.contourCount,
        1, modelInfo.contourPower, modelInfo.contourSpeed);

    if (modelInfo.useCheckerboard) {
        std::vector<fs::path> scriptCandidates = {
            fs::absolute(fs::path("scripts") / "pyslm_checkerboard.py"),
            fs::absolute(fs::path("..") / "scripts" / "pyslm_checkerboard.py"),
            fs::absolute(fs::path("..") / ".." / "scripts" / "pyslm_checkerboard.py")
        };

        fs::path scriptPath;
        for (const auto& candidate : scriptCandidates) {
            if (fs::exists(candidate)) {
                scriptPath = candidate;
                break;
            }
        }

        if (!scriptPath.empty()) {
            contourFiller.enablePySLMCheckerboard("python", scriptPath.string(),
                modelInfo.checkerboardIslandWidth,
                modelInfo.checkerboardIslandOverlap,
                modelInfo.checkerboardIslandOffset);
        }
        else {
            std::cerr << "Warning: unable to locate pyslm_checkerboard.py. Falling back to raster fill." << std::endl;
        }
    }

    std::ostringstream commandFileName;
    commandFileName << "C:\\output\\model_" << modelIndex << "_commands.txt";
    std::remove(commandFileName.str().c_str());

    for (size_t i = 0; i < slices.size(); ++i) {
        outFile << "Layer " << i << " height = " << i * layerHeight << std::endl;

        outFile << "Slice lines (2D):" << std::endl;
        for (const auto& line : slices[i]) {
            outFile << std::fixed << std::setprecision(6)
                << "Line (" << line.point1[0] << ", " << line.point1[1] << ") -> ("
                << line.point2[0] << ", " << line.point2[1] << ")" << std::endl;
        }

        std::vector<Polyline> contours = contourBuilder.buildContours(slices[i]);
        contourBuilder.simplifyContours(contours, 1e-7f);

        outFile << "Contours (2D):" << std::endl;
        for (size_t j = 0; j < contours.size(); ++j) {
            outFile << "Contour " << j << ":" << std::endl;
            for (const auto& point : contours[j].points) {
                outFile << std::fixed << std::setprecision(6)
                    << "(" << point.x << ", " << point.y << ")" << std::endl;
            }
            outFile << (contours[j].isClosed() ? "Closed" : "Open") << std::endl;
        }
        outFile << std::endl;

        contourFiller.writeLayerSeparator(commandFileName.str(), static_cast<int>(i));
        contourFiller.fillLayer(contours, static_cast<int>(i));
        contourFiller.writeCommands(commandFileName.str());
    }

    std::cout << "Model " << modelIndex << " processing complete." << std::endl;
}

void ModelProcessor::generateCombinedCommands(const std::vector<std::string>& modelCommandFiles,
    const std::string& outputFile,
    const std::vector<MultiSTLManager::ModelInfo>& modelInfos) {
    std::vector<std::ifstream> inputFiles;
    for (const auto& file : modelCommandFiles) {
        inputFiles.emplace_back(file);
        if (!inputFiles.back().is_open()) {
            std::cerr << "Error opening file: " << file << std::endl;
            return;
        }
    }

    std::ofstream outFile(outputFile);
    std::ofstream machineTestFile(outputFile.substr(0, outputFile.find_last_of('.')) + "_machine_test.txt");
    if (!outFile.is_open() || !machineTestFile.is_open()) {
        std::cerr << "Error opening output files" << std::endl;
        return;
    }

    fs::path layerTestDir = "C:\\output\\layer_test";
    if (!fs::exists(layerTestDir)) {
        fs::create_directories(layerTestDir);
    }

    std::string line;
    std::vector<std::vector<std::string>> layerCommands(modelCommandFiles.size());
    int layerNumber = 0;

    while (true) {
        bool allFilesProcessed = true;
        for (size_t i = 0; i < inputFiles.size(); ++i) {
            layerCommands[i].clear();
            while (std::getline(inputFiles[i], line)) {
                if (line.find(";Layer") != std::string::npos) {
                    if (!layerCommands[i].empty()) {
                        allFilesProcessed = false;
                        break;
                    }
                    layerCommands[i].push_back(line);
                }
                else if (!line.empty()) {
                    layerCommands[i].push_back(line);
                }
            }
            if (!inputFiles[i].eof()) {
                allFilesProcessed = false;
            }
        }

        if (allFilesProcessed) {
            break;
        }

        std::ostringstream layerFileName;
        layerFileName << layerTestDir.string() << "\\layer_" << layerNumber << ".txt";
        std::ofstream layerFile(layerFileName.str());

        if (!layerFile.is_open()) {
            std::cerr << "Error opening layer file: " << layerFileName.str() << std::endl;
            return;
        }

        std::string layerStartMarker = "\n//;Begin Layer " + std::to_string(layerNumber) + "\n";
        outFile << layerStartMarker << std::endl;
        machineTestFile << layerStartMarker << std::endl;
        layerFile << layerStartMarker << std::endl;

        for (size_t i = 0; i < layerCommands.size(); ++i) {
            if (!layerCommands[i].empty()) {
                writeLayerCommands(outFile, machineTestFile, layerFile, layerCommands[i], modelInfos[i], i);
            }
        }

        std::string layerEndMarker = "//;End Layer " + std::to_string(layerNumber) + "\n";
        outFile << layerEndMarker << std::endl;
        machineTestFile << layerEndMarker << std::endl;
        layerFile << layerEndMarker << std::endl;

        layerFile.close();
        layerNumber++;
    }

    std::cout << "Combined commands written to " << outputFile << std::endl;
    std::cout << "Machine test commands written to " << outputFile.substr(0, outputFile.find_last_of('.')) + "_machine_test.txt" << std::endl;
    std::cout << "Layer files written to " << layerTestDir.string() << std::endl;
}

void ModelProcessor::writeLayerCommands(std::ofstream& outFile, std::ofstream& machineTestFile, std::ofstream& layerFile,
    const std::vector<std::string>& commands, const MultiSTLManager::ModelInfo& modelInfo, size_t modelIndex) {
    std::string modelHeader = "//;Model " + std::to_string(modelIndex) + " Commands";
    outFile << modelHeader << std::endl;
    machineTestFile << modelHeader << std::endl;
    layerFile << modelHeader << std::endl;

    std::string daCommand = "write_da_x_list(" + std::to_string(modelInfo.write_da_x_a) + "," +
        std::to_string(modelInfo.write_da_x_b) + ");";
    machineTestFile << daCommand << std::endl;
    layerFile << daCommand << std::endl;

    std::string markSpeedCommand = "set_mark_speed(" + std::to_string(modelInfo.set_mark_speed * 0.1862156f) + ");";
    machineTestFile << markSpeedCommand << std::endl;
    layerFile << markSpeedCommand << std::endl;

    for (const auto& cmd : commands) {
        outFile << cmd << std::endl;

        auto writeScaled = [&](const std::string& command) {
            machineTestFile << command << std::endl;
            layerFile << command << std::endl;
        };

        if (cmd.find("jump_abs") != std::string::npos || cmd.find("mark_abs") != std::string::npos) {
            size_t start = cmd.find('(') + 1;
            size_t end = cmd.find(')');
            std::string coords = cmd.substr(start, end - start);
            std::istringstream iss(coords);
            float x = 0.0f;
            float y = 0.0f;
            char comma = ',';
            if (iss >> x >> comma >> y) {
                x *= 186.2156f;
                y *= 186.2156f;
                std::string processedCmd = cmd.substr(0, start) + std::to_string(x) + "," + std::to_string(y) + cmd.substr(end);
                writeScaled(processedCmd);
            }
            else {
                writeScaled(cmd);
            }
        }
        else {
            writeScaled(cmd);
        }
    }

    outFile << std::endl;
    machineTestFile << std::endl;
    layerFile << std::endl;
}

void MultiSTLManager::adjustModelPosition(size_t modelIndex, float dx, float dy, float dz) {
    if (modelIndex < models.size()) {
        models[modelIndex].position[0] += dx;
        models[modelIndex].position[1] += dy;
        models[modelIndex].position[2] += dz;
    }
}

std::vector<std::vector<IntersectionLine>> MultiSTLManager::sliceAllModels(float layerHeight, float directionVector[3]) const {
    std::vector<std::vector<IntersectionLine>> allSlices;

    for (const auto& modelInfo : models) {
        auto modelSlices = modelInfo.model.sliceAlongDirection(layerHeight, directionVector);

        for (auto& slice : modelSlices) {
            for (auto& line : slice) {
                for (int i = 0; i < 3; ++i) {
                    line.point1[i] += modelInfo.position[i];
                    line.point2[i] += modelInfo.position[i];
                }
            }
        }

        if (allSlices.empty()) {
            allSlices = modelSlices;
        }
        else {
            for (size_t i = 0; i < allSlices.size(); ++i) {
                allSlices[i].insert(allSlices[i].end(), modelSlices[i].begin(), modelSlices[i].end());
            }
        }
    }

    return allSlices;
}
