#include <iostream>
#include "../include/DatasetReader.h"
#include "../include/Solver.h"
#include <chrono>

/**
* @brief Main function that operates in a loop where the user can choose when to stop and what algorithm to solve the 0/1 Knapsack Problem.
* @return int Returns 0 if it was a successful termination.
* @note The time complexity depends on what was the chosen algorithm:
*      -Backtracking: O(2^n);
*      -Dynamic Programming: O(n*W);
*      -Greedy: O(n log n);
*      -Hybrid: O(n log n + k * n^2) or O(n * W), depending if it is more useful using Dynamic Programming or Greedy and Local Search improvement.
*/

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
            std::cout << "4. Hybrid approach\n";
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
                hybridKnapsack(data.pallets, data.capacity);
            }
            else {
                std::cout << "Invalid algorithm option.\n";
            }
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