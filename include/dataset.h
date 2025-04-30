#ifndef DATASET_H
#define DATASET_H

#pragma once
#include <vector>
#include "pallet.h"

struct dataset {
    int capacity;
    int numPallets;
    std::vector<pallet> pallets;
};

#endif //DATASET_H
