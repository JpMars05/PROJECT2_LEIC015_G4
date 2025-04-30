#include <iostream>
#include "../include/DatasetReader.h"

int main() {
    std::cout << "=== Pallet Packing Optimization ===\n";
    std::cout << "1. Escolher Dataset 01\n";
    std::cout << "2. Sair\n";

    int option;
    std::cin >> option;

    if (option == 1) {
        dataset data = readDataset("../datasets/TruckAndPallets_01.csv", "../datasets/Pallets_01.csv");
        std::cout << "Capacidade do camiao: " << data.capacity << "\n";
        std::cout << "Numero de paletes: " << data.numPallets << "\n";
        std::cout << "Paletes lidas:\n";
        for (const auto& p : data.pallets) {
            std::cout << "ID: " << p.id << " | Peso: " << p.weight << " | Lucro: " << p.profit << "\n";
        }
    }

    return 0;
}