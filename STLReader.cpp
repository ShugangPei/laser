#include "STLReader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring>
#include <cmath>
#include <limits>
#include <algorithm>


bool STLReader::isBinarySTL(const std::string& filename) const {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return false;
    }

    char header[80];
    file.read(header, 80);

    file.seekg(0, std::ios::end);
    std::streampos fileSize = file.tellg();
    file.seekg(80, std::ios::beg);//前80个字节是文件头

    uint32_t numTriangles;
    file.read(reinterpret_cast<char*>(&numTriangles), sizeof(uint32_t));

    return (fileSize == 80 + 4 + numTriangles * 50);//法向量：12字节，顶点：3*12字节，属性：2字节
}

void STLReader::readBinarySTL(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }
      
    char header[80];
    file.read(header, 80);

    uint32_t numTriangles;
    file.read(reinterpret_cast<char*>(&numTriangles), sizeof(uint32_t));

    triangles.clear();
    triangles.reserve(numTriangles);//预分配内存空间

    for (uint32_t i = 0; i < numTriangles; ++i) {
        Triangle triangle;
        file.read(reinterpret_cast<char*>(triangle.normal), 3 * sizeof(float));
        for (int j = 0; j < 3; ++j) {
            file.read(reinterpret_cast<char*>(triangle.vertices[j]), 3 * sizeof(float));
        }
        uint16_t attributeByteCount;//读取属性字节
        file.read(reinterpret_cast<char*>(&attributeByteCount), sizeof(uint16_t));

        triangles.push_back(triangle);
    }

    std::cout << "Read " << triangles.size() << " triangles from binary STL file." << std::endl;
}

void STLReader::readSTL(const std::string& filename) {
    if (isBinarySTL(filename)) {
        std::cout << "Detected binary STL file." << std::endl;
        readBinarySTL(filename);
    }
    else {
        std::cout << "Detected ASCII STL file." << std::endl;
        readASCIISTL(filename);
    }
}

void STLReader::readASCIISTL(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Cannot open file: " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("facet normal") != std::string::npos) {
            Triangle triangle;
            std::istringstream ss(line);
            std::string dummy;
            ss >> dummy >> dummy >> triangle.normal[0] >> triangle.normal[1] >> triangle.normal[2];
            std::getline(file, line); // 跳过 "outer loop"
            for (int i = 0; i < 3; ++i) {
                std::getline(file, line);
                std::istringstream vertexSS(line);
                vertexSS >> dummy >> triangle.vertices[i][0] >> triangle.vertices[i][1] >> triangle.vertices[i][2];
            }
            std::getline(file, line); // 跳过 "endloop"
            std::getline(file, line); // 跳过 "endfacet"
            triangles.push_back(triangle);
        }
    }
}

void STLReader::writeTriangles(const std::string& outputFilename) const {
    std::ofstream outFile(outputFilename);
    if (!outFile) {
        std::cerr << "Cannot open output file: " << outputFilename << std::endl;
        return;
    }
    outFile << "Number of triangles: " << triangles.size() << std::endl;
    for (const auto& triangle : triangles) {
        outFile << "facet normal " << triangle.normal[0] << " " << triangle.normal[1] << " " << triangle.normal[2] << std::endl;
        outFile << "  outer loop" << std::endl;
        for (int i = 0; i < 3; ++i) {
            outFile << "    vertex " << triangle.vertices[i][0] << " " << triangle.vertices[i][1] << " " << triangle.vertices[i][2] << std::endl;
        }
        outFile << "  endloop" << std::endl;
        outFile << "endfacet" << std::endl;
    }
}

std::vector<std::vector<IntersectionLine>> STLReader::sliceAlongDirection(float layerHeight, float directionVector[3]) const {
    std::vector<std::vector<IntersectionLine>> slices;
    float maxProjection = getMaxProjection(directionVector);

    // Normalize the direction vector
    float magnitude = std::sqrt(directionVector[0] * directionVector[0] +
        directionVector[1] * directionVector[1] +
        directionVector[2] * directionVector[2]);
    float normalized[3] = { directionVector[0] / magnitude,
                           directionVector[1] / magnitude,
                           directionVector[2] / magnitude };


    float orthogonal1[3], orthogonal2[3]; 
    createOrthogonalVectors(normalized, orthogonal1, orthogonal2);

    for (float distance = 0.0f; distance <= maxProjection; distance += layerHeight) {
        std::vector<IntersectionLine> slice;
        for (const auto& triangle : triangles) {
            auto intersectionLines = getIntersectionLines(triangle, distance, normalized);
            for (auto& line : intersectionLines) {
                // 把线段投影到二维平面上
                projectPointsTo2D(line.point1, orthogonal1, orthogonal2);
                projectPointsTo2D(line.point2, orthogonal1, orthogonal2);

                // 只有当线段的两端点不同时，才将其添加到切片中
                if (!arePointsEqual(line.point1, line.point2)) {
                    slice.push_back(line);
                }
            }
        }
        slices.push_back(slice);
    }
    return slices;
}

float STLReader::getMaxProjection(float directionVector[3]) const {
    float maxProjection = std::numeric_limits<float>::lowest();
    for (const auto& triangle : triangles) {
        for (int i = 0; i < 3; ++i) {
            float projection = dotProduct(triangle.vertices[i], directionVector);
            if (projection > maxProjection) {
                maxProjection = projection;
            }
        }
    }
    return maxProjection;
}

std::vector<IntersectionLine> STLReader::getIntersectionLines(const Triangle& triangle, float planeDistance, float directionVector[3]) const {
    std::vector<float*> intersectingPoints;
    for (int i = 0; i < 3; ++i) {
        const float* v1 = triangle.vertices[i];
        const float* v2 = triangle.vertices[(i + 1) % 3];
        if ((dotProduct(v1, directionVector) - planeDistance) * (dotProduct(v2, directionVector) - planeDistance) < 0) {
            float point[3];
            getIntersectionPoint(planeDistance, v1, v2, point, directionVector);
            intersectingPoints.push_back(new float[3] { point[0], point[1], point[2] });
        }
        else if (std::abs(dotProduct(v1, directionVector) - planeDistance) < 1e-5) {
            intersectingPoints.push_back(new float[3] { v1[0], v1[1], v1[2] });
        }
    }

    std::vector<IntersectionLine> lines;
    if (intersectingPoints.size() == 2) {
        lines.push_back({ { intersectingPoints[0][0], intersectingPoints[0][1], intersectingPoints[0][2] },
                          { intersectingPoints[1][0], intersectingPoints[1][1], intersectingPoints[1][2] } });
    }
    for (auto& point : intersectingPoints) {
        delete[] point;
    }
    return lines;
}

bool STLReader::isIntersecting(float planeDistance, const float vertex[3], float directionVector[3]) const {
    return std::abs(dotProduct(vertex, directionVector) - planeDistance) < 1e-5;
}

void STLReader::getIntersectionPoint(float planeDistance, const float v1[3], const float v2[3], float result[3], float directionVector[3]) const {
    float t = (planeDistance - dotProduct(v1, directionVector)) / (dotProduct(v2, directionVector) - dotProduct(v1, directionVector));
    for (int i = 0; i < 3; ++i) {
        result[i] = v1[i] + t * (v2[i] - v1[i]);
    }
}

float STLReader::dotProduct(const float v1[3], const float v2[3]) const {
    return v1[0] * v2[0] + v1[1] * v2[1] + v1[2] * v2[2];
}

void STLReader::createOrthogonalVectors(const float v[3], float out1[3], float out2[3]) const {
    // Find the index of the largest absolute component
    int maxIndex = 0;
    for (int i = 1; i < 3; ++i) {
        if (std::abs(v[i]) > std::abs(v[maxIndex])) {
            maxIndex = i;
        }
    }

    // 创建一个正交向量out1
    out1[0] = out1[1] = out1[2] = 0.0f;
    out1[(maxIndex + 1) % 3] = v[(maxIndex + 2) % 3];
    out1[(maxIndex + 2) % 3] = -v[(maxIndex + 1) % 3];

    // 标准化out1
    float magnitude = std::sqrt(out1[0] * out1[0] + out1[1] * out1[1] + out1[2] * out1[2]);
    if (magnitude > 1e-6) {  // 避免除以零
        out1[0] /= magnitude;
        out1[1] /= magnitude;
        out1[2] /= magnitude;
    }
    else {
        //如果out1的模长接近于零，则选择另一个方向
        out1[(maxIndex + 1) % 3] = 1.0f;
    }

    // 创建第二个正交向量
    out2[0] = v[1] * out1[2] - v[2] * out1[1];
    out2[1] = v[2] * out1[0] - v[0] * out1[2];
    out2[2] = v[0] * out1[1] - v[1] * out1[0];

    // 标准化out2
    magnitude = std::sqrt(out2[0] * out2[0] + out2[1] * out2[1] + out2[2] * out2[2]);
    if (magnitude > 1e-6) {  // 避免除以零
        out2[0] /= magnitude;
        out2[1] /= magnitude;
        out2[2] /= magnitude;
    }
}
void STLReader::projectPointsTo2D(float point[3], const float orthogonal1[3], const float orthogonal2[3]) const {
    float x = dotProduct(point, orthogonal1);
    float y = dotProduct(point, orthogonal2);
    point[0] = x;
    point[1] = y;
    point[2] = 0.0f;    //设置z为0
}

bool STLReader::arePointsEqual(const float p1[3], const float p2[3]) const {
    const float EPSILON = 1e-5f;
    return std::abs(p1[0] - p2[0]) < EPSILON &&
        std::abs(p1[1] - p2[1]) < EPSILON &&
        std::abs(p1[2] - p2[2]) < EPSILON;
}