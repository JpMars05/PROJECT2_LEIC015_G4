#include <iostream>
#include "../include/DatasetReader.h"
#include "../include/Solver.h"

dataset data;
int datasetChoice = 0;

void loadDataset() {
    std::string truckFile = "../../datasets/TruckAndPallets_0" + std::to_string(datasetChoice) + ".csv";
    std::string palletFile = "../../datasets/Pallets_0" + std::to_string(datasetChoice) + ".csv";

    data = readDataset(truckFile, palletFile);

    std::cout << "Capacidade do camiao: " << data.capacity << "\n";
    std::cout << "Numero de paletes: " << data.numPallets << "\n";
    std::cout << "Paletes lidas:\n";
    for (const auto& p : data.pallets) {
        std::cout << "ID: " << p.id << " | Peso: " << p.weight << " | Lucro: " << p.profit << "\n";
    }
}

int main() {
    std::cout << "=== Pallet Packing Optimization ===\n";
    std::cout << "1. Escolher Dataset 01\n";
    std::cout << "2. Escolher Dataset 02\n";
    std::cout << "3. Escolher Dataset 03\n";
    std::cout << "4. Escolher Dataset 04\n";
    std::cout << "5. Executar BackTracking\n";
    std::cout << "6. Executar Greedy\n";
    std::cout << "7. Sair\n";

    int option;
    std::cin >> option;

    if (option >= 1 && option <= 4) {
        datasetChoice = option;
        loadDataset();
    }
    else if (option == 5) {
        if (datasetChoice == 0) {
            std::cout << "Por favor, escolha um dataset primeiro (1-4): ";
            std::cin >> datasetChoice;
            loadDataset();
        }
        backtrackingKnapsack(data.pallets, data.capacity);
    }
    else if (option == 6) {
        if (datasetChoice == 0) {
            std::cout << "Por favor, escolha um dataset primeiro (1-4): ";
            std::cin >> datasetChoice;
            loadDataset();
        }
        greedyKnapsack(data.pallets, data.capacity);
    }
    else if (option == 7) {
        return 0;
    }
    else {
        std::cout << "Opçao invalida! Por favor, tente novamente.\n";
    }

    main();

    return 0;
}
