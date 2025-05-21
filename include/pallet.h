#ifndef PALLET_H
#define PALLET_H

#pragma once

struct pallet {
    int id;
    int weight;
    int profit;
};
struct BBNode {
    int level;
    int profit;
    int weight;
    double bound;
    std::vector<int> taken;
};
#endif //PALLET_H