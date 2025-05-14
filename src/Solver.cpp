#include <vector>
#include <iostream>
#include <algorithm>
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

void greedyKnapsack(const vector<pallet>& pallets, int maxWeight) {
  vector<pallet> sortedPallets = pallets;

  // Ordena pela divisão entre lucro e peso de cada um, por ordem decrescente
  sort(sortedPallets.begin(), sortedPallets.end(), [](const pallet& a, const pallet& b) {
        double ratioA = static_cast<double>(a.profit) / a.weight;
        double ratioB = static_cast<double>(b.profit) / b.weight;
        return ratioA > ratioB;
    });
  int currentWeight = 0;
  int totalProfit = 0;
  vector<int> currentCombination;

  // Adiciona-se paletes ao vetor enquanto não ultrapassa a capacidade total
  for(const auto& p : sortedPallets) {
    if(currentWeight + p.weight <= maxWeight) {
      currentWeight+=p.weight;
      totalProfit += p.profit;
      currentCombination.push_back(p.id);
    }
  }
  cout << "Melhor combinação (Greedy):" << endl;
  cout << "Paletes: ";
  for(int id : currentCombination) cout << id << " ";
  cout << "\nPeso total: " << currentWeight << endl;
  cout << "Lucro total: " << totalProfit << endl;
}