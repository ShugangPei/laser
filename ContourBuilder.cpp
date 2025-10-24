#include "ContourBuilder.h"
#include <algorithm>

void Polyline::merge(const Polyline& other) {
    if (points.back() == other.points.front()) {
        points.insert(points.end(), other.points.begin() + 1, other.points.end());
    }
    else if (points.back() == other.points.back()) {
        points.insert(points.end(), other.points.rbegin() + 1, other.points.rend());
    }
    else if (points.front() == other.points.back()) {
        points.insert(points.begin(), other.points.begin(), other.points.end() - 1);
    }
    else if (points.front() == other.points.front()) {
        points.insert(points.begin(), other.points.rbegin(), other.points.rend() - 1);
    }
}

std::vector<Polyline> ContourBuilder::buildContours(const std::vector<IntersectionLine>& lines) {
    remainingLines = lines;
    std::vector<Polyline> contours;
    while (!remainingLines.empty()) {
        Polyline contour;
        IntersectionLine firstLine = remainingLines.front();
        remainingLines.erase(remainingLines.begin());
        contour.addPoint({ firstLine.point1[0], firstLine.point1[1], firstLine.point1[2] });
        contour.addPoint({ firstLine.point2[0], firstLine.point2[1], firstLine.point2[2] });
        while (findAndAddNextLine(contour)) {
            if (contour.isClosed()) {
                break;
            }
        }
        contours.push_back(contour);
    }
    mergeContours(contours);
    return contours;
}

bool ContourBuilder::findAndAddNextLine(Polyline& contour) {
    for (auto it = remainingLines.begin(); it != remainingLines.end(); ++it) {
        Point start = { it->point1[0], it->point1[1], it->point1[2] };
        Point end = { it->point2[0], it->point2[1], it->point2[2] };
        if (start == contour.points.back()) {
            contour.addPoint(end);
            remainingLines.erase(it);
            return true;
        }
        else if (end == contour.points.back()) {
            contour.addPoint(start);
            remainingLines.erase(it);
            return true;
        }
        else if (start == contour.points.front()) {
            contour.addPointFront(end);
            remainingLines.erase(it);
            return true;
        }
        else if (end == contour.points.front()) {
            contour.addPointFront(start);
            remainingLines.erase(it);
            return true;
        }
    }
    return false;
}

void ContourBuilder::mergeContours(std::vector<Polyline>& contours) {
    bool merged;
    do {
        merged = false;
        for (size_t i = 0; i < contours.size(); ++i) {
            for (size_t j = i + 1; j < contours.size(); ) {
                if (contours[i].points.front() == contours[j].points.front() ||
                    contours[i].points.front() == contours[j].points.back() ||
                    contours[i].points.back() == contours[j].points.front() ||
                    contours[i].points.back() == contours[j].points.back()) {
                    contours[i].merge(contours[j]);
                    contours.erase(contours.begin() + j);
                    merged = true;
                }
                else {
                    ++j;
                }
            }
        }
    } while (merged);
}

void ContourBuilder::simplifyContours(std::vector<Polyline>& contours, float epsilon) {
    for (auto& contour : contours) {
        simplifyPolyline(contour, epsilon);
    }
}

void ContourBuilder::simplifyPolyline(Polyline& polyline, float epsilon) {
    if (polyline.points.size() <= 2) {
        return;
    }

    std::vector<Point> simplified;
    simplified.push_back(polyline.points.front());

    for (size_t i = 1; i < polyline.points.size() - 1; ++i) {
        if (!isPointOnLine(polyline.points[i - 1], polyline.points[i + 1], polyline.points[i], epsilon)) {
            simplified.push_back(polyline.points[i]);
        }
    }

    simplified.push_back(polyline.points.back());

    polyline.points = simplified;
}

bool ContourBuilder::isPointOnLine(const Point& start, const Point& end, const Point& point, float epsilon) {
    float d = distancePointToLine(start, end, point);
    return d <= epsilon;
}

float ContourBuilder::distancePointToLine(const Point& lineStart, const Point& lineEnd, const Point& point) {
    float lineLength = std::sqrt(std::pow(lineEnd.x - lineStart.x, 2) + std::pow(lineEnd.y - lineStart.y, 2));
    if (lineLength == 0) {
        return std::sqrt(std::pow(point.x - lineStart.x, 2) + std::pow(point.y - lineStart.y, 2));
    }

    float t = ((point.x - lineStart.x) * (lineEnd.x - lineStart.x) +
        (point.y - lineStart.y) * (lineEnd.y - lineStart.y)) / (lineLength * lineLength);

    t = std::max(0.0f, std::min(1.0f, t));

    float projectionX = lineStart.x + t * (lineEnd.x - lineStart.x);
    float projectionY = lineStart.y + t * (lineEnd.y - lineStart.y);

    return std::sqrt(std::pow(point.x - projectionX, 2) + std::pow(point.y - projectionY, 2));
}

