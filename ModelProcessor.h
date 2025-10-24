#pragma once
#ifndef MODEL_PROCESSOR_H
#define MODEL_PROCESSOR_H

#include <fstream>
#include <string>
#include <vector>
#include "MultiSTLManager.h"

class ModelProcessor {
public:
    static void processModel(const MultiSTLManager& manager, size_t modelIndex, float layerHeight, float directionVector[3]);
    static void generateCombinedCommands(const std::vector<std::string>& modelCommandFiles,
        const std::string& outputFile,
        const std::vector<MultiSTLManager::ModelInfo>& modelInfos);

private:
    static void writeLayerCommands(std::ofstream& outFile, std::ofstream& machineTestFile, std::ofstream& layerFile,
        const std::vector<std::string>& commands, const MultiSTLManager::ModelInfo& modelInfo, size_t modelIndex);
};

#endif // MODEL_PROCESSOR_H

