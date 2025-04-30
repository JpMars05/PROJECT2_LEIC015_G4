#ifndef DATASETREADER_H
#define DATASETREADER_H

#pragma once
#include "dataset.h"
#include <string>

dataset readDataset(const std::string& truckFile, const std::string& palletsFile);

#endif //DATASETREADER_H
