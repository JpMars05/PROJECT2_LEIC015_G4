#ifndef DATASETREADER_H
#define DATASETREADER_H

#pragma once
#include "dataset.h"
#include <string>
#include <filesystem>
#include <string>
#include <vector>


dataset readDataset(const std::string& truckFile, const std::string& palletsFile);

dataset selectDataset(const std::string& datasetFolder = "../datasets/");

#endif //DATASETREADER_H
