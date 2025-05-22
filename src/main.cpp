#include <iostream>
#include "../include/DatasetReader.h"
#include "../include/Solver.h"

int main() {
    while (true) {
        std::cout << "\n=== Pallet Packing Optimization ===\n";
        std::cout << "1. Escolher e usar um Dataset\n";
        std::cout << "2. Sair\n";

        int option;
        std::cin >> option;

        if (option == 1) {
            // Seleciona o dataset
            dataset data = selectDataset("../datasets/");

            std::cout << "\nCapacidade do camiao: " << data.capacity << "\n";
            std::cout << "Numero de paletes: " << data.numPallets << "\n";

            std::cout << "\nEscolhe o algoritmo:\n";
            std::cout << "1. Backtracking\n";
            std::cout << "2. Programacao Dinamica\n";
            std::cout << "3. Greedy Solution\n";
            std::cout << "4. Linear Integer Programming\n";
            int algOption;
            std::cin >> algOption;

            if (algOption == 1) {
                backtrackingKnapsack(data.pallets, data.capacity);
            }
            else if (algOption == 2) {
                dynamicProgrammingKnapsack(data.pallets, data.capacity);
            }
            else if (algOption == 3) {
                greedyKnapsack(data.pallets, data.capacity);
            }
            else if (algOption == 4) {
                LIP_Knapsack(data.pallets, data.capacity);
            }
            else {
                std::cout << "Opcao invalida de algoritmo.\n";
            }
        }
        else if (option == 2) {
            std::cout << "Saindo...\n";
            break;
        }
        else {
            std::cout << "Opcao invalida! Tente novamente.\n";
        }
    }

    return 0;
}