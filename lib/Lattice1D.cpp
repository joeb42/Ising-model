#include "Lattice1D.h"
#include <gsl/gsl_rng.h>
#include <cmath>

Lattice1D::Lattice1D(int dimension, float temperature, int num_threads) {
    n_dim = 1;
    dim = dimension;
    T = temperature;
    n_threads = num_threads;
    set_rngs();
    set_grid();
}

int Lattice1D::delta_E(const std::vector<int> &coords) {
    int x = coords[0];
}

