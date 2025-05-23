#include <iostream>
#include "../include/DatasetReader.h"
#include "../include/Solver.h"
#include <chrono>

int main() {
    while (true) {
        std::cout << "\n=== Pallet Packing Optimization ===\n";
        std::cout << "1. Select and use a dataset\n";
        std::cout << "2. Exit\n";

        int option;
        std::cin >> option;

        if (option == 1) {
            // Seleciona o dataset
            dataset data = selectDataset("../datasets/");

            std::cout << "\nTruck capacity: " << data.capacity << "\n";
            std::cout << "Number of pallets: " << data.numPallets << "\n";

            std::cout << "\nChoose the algorithm:\n";
            std::cout << "1. Backtracking\n";
            std::cout << "2. Dynamic Programming\n";
            std::cout << "3. Approximation Solution (Greedy Approach)\n";
            std::cout << "4. Linear Integer Programming\n";
            int algOption;
            std::cin >> algOption;

            auto start = std::chrono::high_resolution_clock::now();
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
                std::cout << "Invalid algorithm option.\n";
            }
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::milli> duration = end - start;

            std::cout << "Execution time: " << duration.count() << " ms\n";
        }
        else if (option == 2) {
            std::cout << "Exiting...\n";
            break;
        }
        else {
            std::cout << "Invalid option! Please try again.\n";
        }
    }

    return 0;
}