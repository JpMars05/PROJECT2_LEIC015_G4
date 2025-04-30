#include <vector>
#include <iostream>
#include "../include/pallet.h"

using namespace std;

int bestProfit = 0;
int bestWeight = 0;
vector<int> bestCombination;

void backtrack(const vector<pallet>& pallets, int index, int currentWeight, int currentProfit, int maxWeight, vector<int>& currentCombination) {

    if (index == pallets.size()) {
        // Verifica se é melhor solução válida
        if (currentWeight <= maxWeight && currentProfit > bestProfit) {
            bestProfit = currentProfit;
            bestWeight = currentWeight;
            bestCombination = currentCombination;
        }
        return;
    }

    // Escolher a palete atual (se couber)
    if (currentWeight + pallets[index].weight <= maxWeight) {
        currentCombination.push_back(pallets[index].id);
        backtrack(pallets, index + 1,
                  currentWeight + pallets[index].weight,
                  currentProfit + pallets[index].profit,
                  maxWeight,
                  currentCombination);
        currentCombination.pop_back(); // backtrack
    }

    // Ignorar a palete atual
    backtrack(pallets, index + 1, currentWeight, currentProfit, maxWeight, currentCombination);
}

void backtrackingKnapsack(const vector<pallet>& pallets, int maxWeight) {
    bestProfit = 0;
    bestWeight = 0;
    bestCombination.clear();

    vector<int> currentCombination;
    backtrack(pallets, 0, 0, 0, maxWeight, currentCombination);

    cout << "Melhor combinação (Backtracking):" << endl;
    cout << "Paletes: ";
    for (int id : bestCombination) cout << id << " ";
    cout << "\nPeso total: " << bestWeight << endl;
    cout << "Lucro total: " << bestProfit << endl;
}