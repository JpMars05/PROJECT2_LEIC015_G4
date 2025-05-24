#ifndef DATASETREADER_H
#define DATASETREADER_H

#pragma once
#include "dataset.h"
#include <string>
#include <filesystem>
#include <string>
#include <vector>

/**
* @brief Reads the truck and pallet data from the CSV files and builds a dataset object.
*
* @param truckFile A string that contains the name of the CSV file containing the data from a truck.
* @param palletsFile A string that contains the name of the CSV file containing the data from a collection of pallets.
* @return dataset The final dataset structure that contains the best information from both CSV files.
*
* @note Time Complexity: O(n), where n is the number of pallets in a CSV file.
* @note Space Complexity: O(n), where n is the number of pallets in a CSV file.
*/

dataset readDataset(const std::string& truckFile, const std::string& palletsFile);

/**
* @brief Function that lists the available datasets in a directory, where the user can select which one he wants to analyze.
*
* @param datasetFolder String that contains the path to the directory that contains the datasets.
* @return dataset A dataset object that correspond to the files that were selected by the user.
*
* @note Time Complexity: O(m+n), where m is the number of files in the folder and n is the number of pallets that were selected in the dataset.
* @note Space Complexity: O(m+n), where m is the number of files in the folder and n is the number of pallets that were selected in the dataset.
*/

dataset selectDataset(const std::string& datasetFolder = "../datasets/");

#endif
