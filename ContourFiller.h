#ifndef CONTOURFILLER_H
#define CONTOURFILLER_H

#include <vector>
#include <string>
#include "ContourBuilder.h"

class ContourFiller {
public:
    ContourFiller(float initialFillAngle, float angleIncrement, float fillSpacing, int contourCount,
        float controlBoard, float contourPower, float contourSpeed);
    void fillLayer(const std::vector<Polyline>& contours, int layerNumber);
    void writeCommands(const std::string& filename) const;
    void writeLayerSeparator(const std::string& filename, int layerNumber) const;
    void enablePySLMCheckerboard(const std::string& pythonExecutable,
        const std::string& scriptPath,
        float islandWidth,
        float islandOverlap,
        float islandOffset);

private:
    float initialFillAngle;
    float angleIncrement;
    float fillSpacing;
    int contourCount;
    float controlBoard;
    float contourPower;
    float contourSpeed;
    std::vector<std::string> commands;
    bool usePySLMCheckerboard = false;
    std::string checkerboardPythonExecutable = "python";
    std::string checkerboardScriptPath;
    float checkerboardIslandWidth = 5.0f;
    float checkerboardIslandOverlap = 0.0f;
    float checkerboardIslandOffset = 0.5f;

    void generateFillLines(const std::vector<Polyline>& contours, float currentFillAngle);
    bool generateCheckerboardFillLinesWithPySLM(const std::vector<Polyline>& contours,
        float currentFillAngle,
        int layerNumber);
    // ���෽�����ֲ���
    void addCommand(const std::string& command);
    std::string formatPoint(const Point& point);
    std::vector<Point> findIntersections(const Point& start, const Point& end, const std::vector<Polyline>& contours);
    void drawContours(const std::vector<Polyline>& contours);
    bool lineIntersection(const Point& p1, const Point& p2, const Point& p3, const Point& p4, Point& intersection);
    Point rotatePoint(const Point& p, float angle) const;
    Point unrotatePoint(const Point& p, float angle) const;
    std::tuple<float, float, float, float> getBoundingBox(const std::vector<Polyline>& contours) const;
    bool isPointInsideContours(const Point& p, const std::vector<Polyline>& contours) const;
};

#endif // CONTOURFILLER_H
