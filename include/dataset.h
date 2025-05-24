#ifndef DATASET_H
#define DATASET_H

#pragma once
#include <vector>
#include "pallet.h"


/**
* @struct dataset
*
* @brief A structure that represents the dataset to be read for the 0/1 Knapsack Problem.
*/
struct dataset {
    /**
    * @brief Integer that shows the maximum weight of the truck.
    */

    int capacity;

    /**
    * @brief Integer that represents the number of pallets possible in a certain truck.
    */

    int numPallets;

    /**
    * @brief Vector that represents the pallets that are selected to be stored on the truck.
    */

    std::vector<pallet> pallets;
};

#endif
