#include <iostream>
#include "../include/DatasetReader.h"
#include "../include/Solver.h"

int main() {
    std::cout << "=== Pallet Packing Optimization ===\n";
    std::cout << "1. Escolher Dataset\n";
    std::cout << "2. Sair\n";

    int option;
    std::cin >> option;

    if (option == 1) {
        // Lê o dataset
        dataset data = selectDataset();
        
        std::cout << "Capacidade do camiao: " << data.capacity << "\n";
        std::cout << "Numero de paletes: " << data.numPallets << "\n";
        std::cout << "Paletes lidas:\n";
        for (const auto& p : data.pallets) {
            std::cout << "ID: " << p.id << " | Peso: " << p.weight << " | Lucro: " << p.profit << "\n";
        }

        // Aplica o algoritmo de backtracking
        backtrackingKnapsack(data.pallets, data.capacity);
    }
    else if (option == 2) {
        std::cout << "Saindo...\n";
        return 0;
    }
    else {
        std::cout << "Opçao invalida! Por favor, tente novamente.\n";
        main();
    }

    return 0;
}