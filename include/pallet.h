#ifndef PALLET_H
#define PALLET_H
#include <iostream>

#pragma once

/**
* @struct pallet
*
* @brief Structure that represents the data of a single pallet.
*/

struct pallet {
    /**
    * @brief Integer that represents the unique id of a pallet in a file.
    */

    int id;

    /**
    * @brief Integer that represents the weight of a pallet.
    */

    int weight;

    /**
    * @brief Integer that shows the profit of a certain pallet.
    */

    int profit;
};

/**
* @struct BBNode
* @brief Structure that represents a node in the Branch and Bound tree for solving the 0/1 Knapsack Problem with the LIP algorithm.
*/

struct BBNode {
    /**
    * @brief Integer that represents the current level in the decision tree.
    */

    int level;

    /**
    * @brief Integer that represents the profit that was accumulated to this node.
    */

    int profit;
    /**
    * @brief Integer that represents the weight that was accumulated to this node.
    */

    int weight;

    /**
    * @brief Double value that represents the upper bound of the maximum profit possible.
    */

    double bound;

    /**
    * @brief Vector that indicates the items that were taken up to this node.
    */

    std::vector<int> taken;
};
#endif //PALLET_H