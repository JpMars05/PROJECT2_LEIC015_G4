#ifndef SOLVER_H
#define SOLVER_H

#include "pallet.h"
#include <vector>

extern int bestProfit;
extern int bestWeight;
extern std::vector<int> bestCombination;


void backtrack(const std::vector<pallet>& pallets, int index, int currentWeight, int currentProfit, int maxWeight, std::vector<int>& currentCombination);
void backtrackingKnapsack(const std::vector<pallet>& pallets, int maxWeight);
void dynamicProgrammingKnapsack(const std::vector<pallet>& pallets, int maxWeight);
void greedyKnapsack(const std::vector<pallet>& pallets, int maxWeight);
void greedyPlusLocalSearchKnapsack(const std::vector<pallet>& pallets, int maxWeight);
void hybridKnapsack(const std::vector<pallet>& pallets, int maxWeight);

#endif //SOLVER_H
