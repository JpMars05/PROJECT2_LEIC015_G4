#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
#include "../include/pallet.h"
#include <chrono>

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

void dynamicProgrammingKnapsack(const vector<pallet>& pallets, int maxWeight) {
    auto start = std::chrono::high_resolution_clock::now();
    int n = pallets.size(); // Número de paletes disponíveis

    // Cria uma tabela DP com n+1 linhas e maxWeight+1 colunas, inicializada a zero.
    // dp[i][j] representa o lucro máximo usando as primeiras i paletes com capacidade j.
    vector<vector<int>> dp(n + 1, vector<int>(maxWeight + 1, 0));

    // Preenche a tabela DP de forma iterativa
    for (int i = 1; i <= n; ++i) {
        int w = pallets[i - 1].weight; // Peso da palete atual
        int p = pallets[i - 1].profit; // Lucro da palete atual

        for (int j = 0; j <= maxWeight; ++j) {
            // Se a palete atual couber na capacidade j
            if (w <= j) {
                // Escolhe o melhor entre: não usar esta palete (dp[i-1][j])
                // ou usar esta palete (dp[i-1][j-w] + lucro desta palete)
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w] + p);
            } else {
                // Não dá para usar esta palete, então copia o valor de cima
                dp[i][j] = dp[i - 1][j];
            }
        }
    }

    // Recupera o lucro máximo total a partir da última célula da tabela
    int res = dp[n][maxWeight];
    int w = maxWeight; // Capacidade restante
    vector<int> selected; // IDs das paletes escolhidas

    // Percorre a tabela de trás para a frente para descobrir quais paletes foram escolhidas
    for (int i = n; i > 0 && res > 0; --i) {
        // Se o valor mudou ao passar de dp[i][w] para dp[i-1][w],
        // isso significa que esta palete foi incluída na solução ótima
        if (res != dp[i - 1][w]) {
            selected.push_back(pallets[i - 1].id);         // Guarda o ID da palete
            res -= pallets[i - 1].profit;                  // Subtrai o lucro da palete escolhida
            w -= pallets[i - 1].weight;                    // Subtrai o peso da palete
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    // Imprime os resultados finais
    cout << "Best combination (Dynamic Programming):" << endl;
    cout << "Pallets: ";
    for (int id : selected) cout << id << " ";
    cout << "\nTotal weight: " << maxWeight - w << endl;
    cout << "Total profit: " << dp[n][maxWeight] << endl;
    std::cout << "Execution time: " << duration.count() << " ms\n";
}

void greedyKnapsack(const vector<pallet>& pallets, int maxWeight) {
    auto start = std::chrono::high_resolution_clock::now();
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
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> duration = end - start;

    cout << "Best combination (Greedy):" << endl;
    cout << "Pallets: ";
    for(int id : currentCombination) cout << id << " ";
    cout << "\nTotal weight: " << currentWeight << endl;
    cout << "Total profit: " << totalProfit << endl;
    std::cout << "Execution time: " << duration.count() << " ms\n";
}

void greedyPlusLocalSearchKnapsack(const vector<pallet>& pallets, int maxWeight) {
    auto start = std::chrono::high_resolution_clock::now();
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

    // ------------------ LOCAL SEARCH ------------------
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
                    break; // Recomeça a pesquisa após troca
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

void hybridKnapsack(const std::vector<pallet>& pallets, int maxWeight) {
  if(pallets.size() <= 20){
      cout << "[Hybrid Knapsack] Using Dynamic Programming (small instance)" << endl;
    dynamicProgrammingKnapsack(pallets, maxWeight);
  }else {
      cout << "[Hybrid Knapsack] Using Greedy + Local Search (large instance)" << endl;
     greedyPlusLocalSearchKnapsack(pallets, maxWeight);
  }
}
