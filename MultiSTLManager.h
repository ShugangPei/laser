#pragma once

#include <string>
#include <vector>

#include "STLReader.h"

class MultiSTLManager {
public:
    struct ModelInfo {
        STLReader model;
        std::string material;
        float position[3];
        float write_da_x_a;
        float write_da_x_b;
        float set_mark_speed;
        float fillAngle;
        float fillSpacing;
        float angleIncrement;
        int contourCount;
        float contourPower;
        float contourSpeed;
        bool useCheckerboard;
        float checkerboardIslandWidth;
        float checkerboardIslandOverlap;
        float checkerboardIslandOffset;
    };

    void addModel(const std::string& filename, const std::string& material,
        float x, float y, float z,
        float write_da_x_a, float write_da_x_b, float set_mark_speed,
        float fillSpacing, float fillAngle, float angleIncrement,
        int contourCount, float contourPower, float contourSpeed,
        bool useCheckerboard = false,
        float checkerboardIslandWidth = 5.0f,
        float checkerboardIslandOverlap = 0.0f,
        float checkerboardIslandOffset = 0.5f) {
        ModelInfo info;
        info.model.readSTL(filename);
        info.material = material;
        info.position[0] = x;
        info.position[1] = y;
        info.position[2] = z;
        info.write_da_x_a = write_da_x_a;
        info.write_da_x_b = write_da_x_b;
        info.set_mark_speed = set_mark_speed;
        info.fillSpacing = fillSpacing;
        info.fillAngle = fillAngle;
        info.angleIncrement = angleIncrement;
        info.contourCount = contourCount;
        info.contourPower = contourPower;
        info.contourSpeed = contourSpeed;
        info.useCheckerboard = useCheckerboard;
        info.checkerboardIslandWidth = checkerboardIslandWidth;
        info.checkerboardIslandOverlap = checkerboardIslandOverlap;
        info.checkerboardIslandOffset = checkerboardIslandOffset;
        models.push_back(info);
    }

    void adjustModelPosition(size_t modelIndex, float dx, float dy, float dz);
    std::vector<std::vector<IntersectionLine>> sliceAllModels(float layerHeight, float directionVector[3]) const;

    const ModelInfo& getModelInfo(size_t modelIndex) const {
        return models[modelIndex];
    }

    size_t getModelCount() const {
        return models.size();
    }

    std::vector<std::vector<IntersectionLine>> sliceSingleModel(size_t modelIndex, float layerHeight, float directionVector[3]) const {
        if (modelIndex >= models.size()) {
            return {};
        }

        const auto& modelInfo = models[modelIndex];
        auto modelSlices = modelInfo.model.sliceAlongDirection(layerHeight, directionVector);

        for (auto& slice : modelSlices) {
            for (auto& line : slice) {
                for (int i = 0; i < 3; ++i) {
                    line.point1[i] += modelInfo.position[i];
                    line.point2[i] += modelInfo.position[i];
                }
            }
        }

        return modelSlices;
    }

private:
    std::vector<ModelInfo> models;
};
