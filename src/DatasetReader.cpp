#include "../include/DatasetReader.h"
#include <fstream>
#include <sstream>
#include <iostream>

dataset readDataset(const std::string& truckFile, const std::string& palletsFile) {

    dataset data;

    // Lê capacidade e número de paletes
    std::ifstream truckStream(truckFile);
    std::string line;

    std::getline(truckStream, line); // Header
    std::getline(truckStream, line);
    std::stringstream ss(line);
    std::string capacityStr, palletsStr;
    std::getline(ss, capacityStr, ',');
    std::getline(ss, palletsStr, ',');

    data.capacity = std::stoi(capacityStr);
    data.numPallets = std::stoi(palletsStr);

    // Lê dados das paletes
    std::ifstream palletStream(palletsFile);
    std::getline(palletStream, line); // Header

    while (std::getline(palletStream, line)) {
        std::stringstream ps(line);
        std::string idStr, weightStr, profitStr;
        std::getline(ps, idStr, ',');
        std::getline(ps, weightStr, ',');
        std::getline(ps, profitStr, ',');

        pallet p{};
        p.id = std::stoi(idStr);
        p.weight = std::stoi(weightStr);
        p.profit = std::stoi(profitStr);
        data.pallets.push_back(p);
    }

    return data;
}