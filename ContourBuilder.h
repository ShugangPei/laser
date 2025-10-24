#ifndef CONTOURBUILDER_H
#define CONTOURBUILDER_H

#include <vector>
#include <cmath>
#include "STLReader.h"

struct Point {
    float x, y, z;
    bool operator==(const Point& other) const {
        const float EPSILON = 1e-5f;
        return std::abs(x - other.x) < EPSILON &&
            std::abs(y - other.y) < EPSILON &&
            std::abs(z - other.z) < EPSILON;
    }
};

struct Line {
    Point start, end;
};

class Polyline {
public:
    std::vector<Point> points;
    void addPoint(const Point& p) { points.push_back(p); }
    void addPointFront(const Point& p) { points.insert(points.begin(), p); }
    bool isClosed() const { return !points.empty() && points.front() == points.back(); }
    void merge(const Polyline& other);
};

class ContourBuilder {
public:
    std::vector<Polyline> buildContours(const std::vector<IntersectionLine>& lines);
    void simplifyContours(std::vector<Polyline>& contours, float epsilon = 0.01f);

private:
    std::vector<IntersectionLine> remainingLines;
    bool findAndAddNextLine(Polyline& contour);
    void mergeContours(std::vector<Polyline>& contours);
    void simplifyPolyline(Polyline& polyline, float epsilon);
    bool isPointOnLine(const Point& start, const Point& end, const Point& point, float epsilon);
    float distancePointToLine(const Point& lineStart, const Point& lineEnd, const Point& point);
};

#endif // CONTOURBUILDER_H

