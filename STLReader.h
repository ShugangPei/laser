#ifndef STLREADER_H
#define STLREADER_H

#include <string>
#include <vector>

struct Triangle {
    float normal[3];
    float vertices[3][3];
};

struct IntersectionLine {
    float point1[3];
    float point2[3];
};

class STLReader {
public:
    void readSTL(const std::string& filename);
    void writeTriangles(const std::string& outputFilename) const;
    std::vector<std::vector<IntersectionLine>> sliceAlongDirection(float layerHeight, float directionVector[3]) const;
    float getMaxProjection(float directionVector[3]) const;
 

private:
    bool isBinarySTL(const std::string& filename) const;
    void readBinarySTL(const std::string& filename);
    void readASCIISTL(const std::string& filename);
    std::vector<Triangle> triangles;
    std::vector<IntersectionLine> getIntersectionLines(const Triangle& triangle, float planeDistance, float directionVector[3]) const;
    bool isIntersecting(float planeDistance, const float vertex[3], float directionVector[3]) const;
    void getIntersectionPoint(float planeDistance, const float v1[3], const float v2[3], float result[3], float directionVector[3]) const;
    float dotProduct(const float v1[3], const float v2[3]) const;
    void createOrthogonalVectors(const float v[3], float out1[3], float out2[3]) const;
    void projectPointsTo2D(float point[3], const float orthogonal1[3], const float orthogonal2[3]) const;
    bool arePointsEqual(const float p1[3], const float p2[3]) const;
};

#endif // STLREADER_H