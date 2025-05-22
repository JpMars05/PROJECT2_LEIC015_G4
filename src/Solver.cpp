#include <vector>
#include <iostream>
#include <algorithm>
#include <stack>
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

    cout << "Melhor combinacao (Backtracking):" << endl;
    cout << "Paletes: ";
    for (int id : bestCombination) cout << id << " ";
    cout << "\nPeso total: " << bestWeight << endl;
    cout << "Lucro total: " << bestProfit << endl;
}

void dynamicProgrammingKnapsack(const vector<pallet>& pallets, int maxWeight) {
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

    // Imprime os resultados finais
    cout << "Melhor combinacao (Dynamic Programming):" << endl;
    cout << "Paletes: ";
    for (int id : selected) cout << id << " ";
    cout << "\nPeso total: " << maxWeight - w << endl;
    cout << "Lucro total: " << dp[n][maxWeight] << endl;
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
    cout << "Melhor combinacao (Greedy):" << endl;
    cout << "Paletes: ";
    for(int id : currentCombination) cout << id << " ";
    cout << "\nPeso total: " << currentWeight << endl;
    cout << "Lucro total: " << totalProfit << endl;
}
bool cmpRatio(const pallet& a, const pallet& b) {
    return (double)a.profit / a.weight > (double)b.profit / b.weight;
}
double bound(int level, int weight, int profit, const vector<pallet>& pallets, int capacity) {
    if (weight >= capacity) return 0;

    double profit_bound = profit;
    int total_weight = weight;

    for (int i = level; i < pallets.size(); ++i) {
        if (total_weight + pallets[i].weight <= capacity) {
            total_weight += pallets[i].weight;
            profit_bound += pallets[i].profit;
        } else {
            int remain = capacity - total_weight;
            profit_bound += (double)pallets[i].profit / pallets[i].weight * remain;
            break;
        }
    }
    return profit_bound;
}
void LIP_Knapsack(const vector<pallet>& items, int capacity) {
    vector<pallet> pallets = items;
    sort(pallets.begin(), pallets.end(), cmpRatio);

    stack<BBNode> S;
    BBNode root = {0, 0, 0, bound(0, 0, 0, pallets, capacity), {}};
    S.push(root);

    int maxProfit = 0;
    vector<int> bestTaken;

    while (!S.empty()) {
        BBNode node = S.top(); S.pop();

        if (node.level >= pallets.size()) continue;

        BBNode with = node;
        with.level++;
        with.weight += pallets[node.level].weight;
        with.profit += pallets[node.level].profit;
        with.taken.push_back(pallets[node.level].id);
        with.bound = bound(with.level, with.weight, with.profit, pallets, capacity);

        if (with.weight <= capacity && with.profit > maxProfit) {
            maxProfit = with.profit;
            bestTaken = with.taken;
        }

        if (with.bound > maxProfit)
            S.push(with);

        BBNode without = node;
        without.level++;
        without.bound = bound(without.level, without.weight, without.profit, pallets, capacity);
        if (without.bound > maxProfit)
            S.push(without);
    }
    int totalWeight = 0;
    for (int id : bestTaken) {
        for (const auto& p : items) {
            if (p.id == id) {
                totalWeight += p.weight;
                break;
            }
        }
    }

    cout << "Melhor combinacao (LIP - Branch and Bound):";
    cout << "Paletes: ";
    for (int id : bestTaken) cout << id << " ";
    cout << "\nPeso total: " << totalWeight << endl;
    cout << "Lucro total: " << maxProfit << endl;
}