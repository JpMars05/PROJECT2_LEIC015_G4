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

#endif //PALLET_H