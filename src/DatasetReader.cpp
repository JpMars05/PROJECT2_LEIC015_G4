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

dataset selectDataset(const std::string& datasetFolder) {
    using std::filesystem::directory_iterator;
    using std::filesystem::path;

    std::vector<std::string> datasetIds;

    for (const auto& entry : directory_iterator(datasetFolder)) {
        std::string filename = entry.path().filename().string();
        std::string prefix = "TruckAndPallets_";
        std::string suffix = ".csv";

        if (filename.size() >= prefix.size() + suffix.size() &&
            filename.substr(0, prefix.size()) == prefix &&
            filename.substr(filename.size() - suffix.size()) == suffix) {

            std::string id = filename.substr(prefix.size(), 2); // "XX"
            datasetIds.push_back(id);
            }
    }

    if (datasetIds.empty()) {
        std::cerr << "Nenhum dataset encontrado na pasta: " << datasetFolder << "\n";
        exit(1);
    }

    std::cout << "\n=== Datasets Disponiveis ===\n";
    for (const auto& id : datasetIds) {
        std::cout << "Dataset " << id << "\n";
    }

    std::string chosen;
    std::cout << "\nEscolhe o numero do dataset (ex: 01): ";
    std::cin >> chosen;

    std::string truckPath = datasetFolder + "TruckAndPallets_" + chosen + ".csv";
    std::string palletPath = datasetFolder + "Pallets_" + chosen + ".csv";

    return readDataset(truckPath, palletPath);
}
