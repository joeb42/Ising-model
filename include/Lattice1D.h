#pragma once
#include "LatticeBase.h"
#include <vector>


class Lattice1D: public LatticeBase {
    Lattice1D(int dimension, float temperature, int num_threads);
    void write_grid();
    int delta_E(const std::vector<int> &coords);
    void sweep();
};