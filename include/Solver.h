#ifndef SOLVER_H
#define SOLVER_H

#include "pallet.h"
#include <vector>

/**
* @brief Integer that stores the best total profit for each algorithm.
*/

extern int bestProfit;

/**
* @brief Integer that stores the best total weight for each algorithm.
*/

extern int bestWeight;

/**
* @brief A vector of integers that stores the IDs of the best combination of pallets found for each algorithm.
*/

extern std::vector<int> bestCombination;

/**
* @brief Function that works as a recursive helper for the backtracking solution of the 0/1 Knapsack Problem.
* @param pallets A vector of pallet's structure that contains the pallets of a certain file.
* @param index Integer that represents a certain index in the pallets vector.
* @param currentWeight Integer that accumulates the total weight throughout the vector of pallets.
* @param currentProfit Integer that accumulates the total profit throughout the vector of pallets.
* @param maxWeight Integer that represents the maximum weight allowed.
* @param currentCombination A vector of integers that represents the combination of pallets IDs that were selected.
*
* @note Time Complexity: O(2^n), where n is the number of pallets.
*/

void backtrack(const std::vector<pallet>& pallets, int index, int currentWeight, int currentProfit, int maxWeight, std::vector<int>& currentCombination);

/**
* @brief Function that solves the 0/1 Knapsack Problem using the backtracking approach.
* @param pallets A vector of pallet's structure containing the pallets of a certain file.
* @param maxWeight Integer that represents the maximum weight allowed on a certain truck.
* @note Time Complexity: O(2^n), where n is the total number of pallets.
*/

void backtrackingKnapsack(const std::vector<pallet>& pallets, int maxWeight);

/**
* @brief Function that solves the 0/1 Knapsack Problem using a Dynamic Programming approach.
* @param pallets A vector of pallet's structure that conatins the pallets available for the algorithm.-
* @param maxWeight Integer that represents the maximum weight allowed on a certain truck.
* @note Time Complexity: O(n*W), where n is the number of pallets available and W is the maximum allowed weight.
*/

void dynamicProgrammingKnapsack(const std::vector<pallet>& pallets, int maxWeight);

/**
* @brief Function that solves the 0/1 Knapsack Problem using a Greedy approach.
* @param pallets A vector of pallet's structure that contains the pallets available for the algorithm.
* @param maxWeight Integer that represents the maximum allowed weight on a certain truck.
* @note Time Complexity: O(n log n), where n is the number of available pallets.
*/

void greedyKnapsack(const std::vector<pallet>& pallets, int maxWeight);

/**
* @brief Function that solves the 0/1 Knapsack Problem using a Greedy aproach followed by a Local Search improvement.
* @param pallets A vector of pallet's structure that contains the pallets available for the algorithm.
* @param maxWeight Integer that represents the maximum allowed weight on a certain truck.
* @note Time Complexity: O(n log n + k * n^2), where n is the number of available pallets and k the number of successful improvements.
*/

void greedyPlusLocalSearchKnapsack(const std::vector<pallet>& pallets, int maxWeight);

/**
* @brief Function that contains a Hybrid Aprroach for the 0/1 Knapsack Problem that chooses the best strategy to solve the problem.
* @param pallets A vector of pallet's structure that contains the pallets available for the algorithm.
* @param maxWeight Integer that represents the maximum allowed weight on a certain truck.
*/

void hybridKnapsack(const std::vector<pallet>& pallets, int maxWeight);

#endif //SOLVER_H
