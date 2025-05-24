#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include "../include/pallet.h"
#include <chrono>

using namespace std;

/**
* @brief Integer that stores the best total profit for each algorithm.
*/

int bestProfit = 0;

/**
* @brief Integer that stores the best total weight for each algorithm.
*/

int bestWeight = 0;

/**
* @brief A vector of integers that stores the IDs of the best combination of pallets found for each algorithm.
*/

vector<int> bestCombination;

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
* In case of multiple combinations with the same profit and weight, the one with fewer pallets is chosen.
*/

void backtrack(const vector<pallet>& pallets, int index, int currentWeight, int currentProfit, int maxWeight, vector<int>& currentCombination) {

    if (index == pallets.size()) {
        if (currentWeight <= maxWeight) {
            if (currentProfit > bestProfit ||
                (currentProfit == bestProfit && currentCombination.size() < bestCombination.size())) {
                bestProfit = currentProfit;
                bestWeight = currentWeight;
                bestCombination = currentCombination;
                }
        }
        return;
    }

    if (currentWeight + pallets[index].weight <= maxWeight) {
        currentCombination.push_back(pallets[index].id);
        backtrack(pallets, index + 1,
                  currentWeight + pallets[index].weight,
                  currentProfit + pallets[index].profit,
                  maxWeight,
                  currentCombination);
        currentCombination.pop_back();
    }

    backtrack(pallets, index + 1, currentWeight, currentProfit, maxWeight, currentCombination);
}

/**
* @brief Function that solves the 0/1 Knapsack Problem using the backtracking approach.
* @param pallets A vector of pallet's structure containing the pallets of a certain file.
* @param maxWeight Integer that represents the maximum weight allowed on a certain truck.
* @note Time Complexity: O(2^n), where n is the total number of pallets.
* @note Space Complexity: O(n), because of the recursion depth and the forward storage on the currentCombination vector.
*/

void backtrackingKnapsack(const vector<pallet>& pallets, int maxWeight) {
    auto start = std::chrono::high_resolution_clock::now();
    bestProfit = 0;
    bestWeight = 0;
    bestCombination.clear();

    vector<int> currentCombination;
    backtrack(pallets, 0, 0, 0, maxWeight, currentCombination);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    cout << "Best combination (Backtracking):" << endl;
    cout << "Pallets: ";
    for (int id : bestCombination) cout << id << " ";
    cout << "\nTotal weight: " << bestWeight << endl;
    cout << "Total profit: " << bestProfit << endl;
    std::cout << "Execution time: " << duration.count() << " ms\n";

}

/**
* @brief Function that solves the 0/1 Knapsack Problem using a Dynamic Programming approach.
* @param pallets A vector of pallet's structure that conatins the pallets available for the algorithm.-
* @param maxWeight Integer that represents the maximum weight allowed on a certain truck.
* @note Time Complexity: O(n*W), where n is the number of pallets available and W is the maximum allowed weight.
* @note Space Complexity: O(n*W), due to the count tables.
*/

void dynamicProgrammingKnapsack(const vector<pallet>& pallets, int maxWeight) {
    auto start = std::chrono::high_resolution_clock::now();
    int n = pallets.size();

    vector<vector<int>> dp(n + 1, vector<int>(maxWeight + 1, 0));
    vector<vector<int>> cnt(n + 1, vector<int>(maxWeight + 1, 0));

    for (int i = 1; i <= n; ++i) {
        int w = pallets[i - 1].weight;
        int p = pallets[i - 1].profit;

        for (int j = 0; j <= maxWeight; ++j) {
             int bestProfit = dp[i - 1][j];
             int bestCount  = cnt[i - 1][j];

             if (w <= j) {
                 int pickProfit = dp[i - 1][j - w] + p;
                 int pickCount  = cnt[i - 1][j - w] + 1;

                 if (pickProfit > bestProfit ||
                    (pickProfit == bestProfit && pickCount < bestCount)) {
                     bestProfit = pickProfit;
                     bestCount  = pickCount;
                 }
             }

             dp[i][j]  = bestProfit;
             cnt[i][j] = bestCount;
        }
    }

    int w = maxWeight;
    vector<int> selected;

    for (int i = n; i > 0; --i) {
      if (dp[i][w] == dp[i - 1][w] && cnt[i][w] == cnt[i - 1][w]) {

      } else {
        selected.push_back(pallets[i - 1].id);
        w -= pallets[i - 1].weight;
      }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    cout << "Best combination (Dynamic Programming):" << endl;
    cout << "Pallets: ";
    for (int id : selected) cout << id << " ";
    cout << "\nTotal weight: " << maxWeight - w << endl;
    cout << "Total profit: " << dp[n][maxWeight] << endl;
    std::cout << "Execution time: " << duration.count() << " ms\n";
}

/**
* @brief Function that solves the 0/1 Knapsack Problem using a Greedy approach.
* @param pallets A vector of pallet's structure that contains the pallets available for the algorithm.
* @param maxWeight Integer that represents the maximum allowed weight on a certain truck.
* @note Time Complexity: O(n log n), where n is the number of available pallets.
* @note Space Complexity: O(n), due to the sort function and the forward storage on the currentCombination vector.
*/

void greedyKnapsack(const vector<pallet>& pallets, int maxWeight) {
    auto start = std::chrono::high_resolution_clock::now();
    vector<pallet> sortedPallets = pallets;

    sort(sortedPallets.begin(), sortedPallets.end(), [](const pallet& a, const pallet& b) {
          double ratioA = static_cast<double>(a.profit) / a.weight;
          double ratioB = static_cast<double>(b.profit) / b.weight;
          return ratioA > ratioB;
      });
    int currentWeight = 0;
    int totalProfit = 0;
    vector<int> currentCombination;

    for(const auto& p : sortedPallets) {
        if(currentWeight + p.weight <= maxWeight) {
            currentWeight+=p.weight;
            totalProfit += p.profit;
            currentCombination.push_back(p.id);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    cout << "Best combination (Greedy):" << endl;
    cout << "Pallets: ";
    for(int id : currentCombination) cout << id << " ";
    cout << "\nTotal weight: " << currentWeight << endl;
    cout << "Total profit: " << totalProfit << endl;
    std::cout << "Execution time: " << duration.count() << " ms\n";
}

/**
* @brief Function that solves the 0/1 Knapsack Problem using a Greedy aproach followed by a Local Search improvement.
* @param pallets A vector of pallet's structure that contains the pallets available for the algorithm.
* @param maxWeight Integer that represents the maximum allowed weight on a certain truck.
* @note Time Complexity: O(n log n + k * n^2), where n is the number of available pallets and k the number of successful improvements.
* @note Space Complexity: O(n), because of the sort function and forward storage on the currentCombination vector.
*/

void greedyPlusLocalSearchKnapsack(const vector<pallet>& pallets, int maxWeight) {
    auto start = std::chrono::high_resolution_clock::now();
    vector<pallet> sortedPallets = pallets;

    sort(sortedPallets.begin(), sortedPallets.end(), [](const pallet& a, const pallet& b) {
          double ratioA = static_cast<double>(a.profit) / a.weight;
          double ratioB = static_cast<double>(b.profit) / b.weight;
          return ratioA > ratioB;
      });
    int currentWeight = 0;
    int totalProfit = 0;
    vector<int> currentCombination;

    for(const auto& p : sortedPallets) {
        if(currentWeight + p.weight <= maxWeight) {
            currentWeight+=p.weight;
            totalProfit += p.profit;
            currentCombination.push_back(p.id);
        }
    }

    bool improved = true;
    while (improved) {
        improved = false;

        for (int i = 0; i < currentCombination.size(); ++i) {
            pallet in = *find_if(pallets.begin(), pallets.end(), [&](const pallet& p) {
                return p.id == currentCombination[i];
            });

            for (const auto& out : pallets) {
                if (find(currentCombination.begin(), currentCombination.end(), out.id) != currentCombination.end()) continue;

                int newWeight = currentWeight - in.weight + out.weight;
                int newProfit = totalProfit - in.profit + out.profit;

                if (newWeight <= maxWeight && newProfit > totalProfit) {
                    currentWeight = newWeight;
                    totalProfit = newProfit;
                    currentCombination[i] = out.id;
                    improved = true;
                    break;
                }
            }

            if (improved) break;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    cout << "Best combination (Greedy + Local Search):" << endl;
    cout << "Pallets: ";
    for(int id : currentCombination) cout << id << " ";
    cout << "\nTotal weight: " << currentWeight << endl;
    cout << "Total profit: " << totalProfit << endl;
    std::cout << "Execution time: " << duration.count() << " ms\n";
}

/**
* @brief Function that contains a Hybrid Aprroach for the 0/1 Knapsack Problem that chooses the best strategy to solve the problem.
* @param pallets A vector of pallet's structure that contains the pallets available for the algorithm.
* @param maxWeight Integer that represents the maximum allowed weight on a certain truck.
* @note Time Complexity: Depends on the chosen strategy:
*        -O(n*W) for Dynamic Programming (if pallets <=20);
*        -O(n log n + k * n^2) for Greedy + Local Search (if pallets > 20).
* @note Space Complexity: Depends on the chosen strategy:
*        -O(n*W) for Dynamic Programming (if pallets <=20);
*        -O(n) for Greedy + Local Search (if pallets > 20).
*/

void hybridKnapsack(const std::vector<pallet>& pallets, int maxWeight) {
  if(pallets.size() <= 20){
      cout << "[Hybrid Knapsack] Using Dynamic Programming (small instance)" << endl;
    dynamicProgrammingKnapsack(pallets, maxWeight);
  }else {
      cout << "[Hybrid Knapsack] Using Greedy + Local Search (large instance)" << endl;
     greedyPlusLocalSearchKnapsack(pallets, maxWeight);
  }
}
