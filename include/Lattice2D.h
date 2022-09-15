#pragma once
#include "LatticeBase.h"
#include <vector>
#include <gsl/gsl_rng.h>


class Lattice2D: public LatticeBase {

    public:
        Lattice2D (int dimension, float temperature, int num_threads);
        void write_grid();
        int delta_E(const std::vector<int> &coords);
        void sweep(int offset);
        void sweep();
};