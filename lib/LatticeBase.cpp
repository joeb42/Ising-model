#include "LatticeBase.h"
#include <iostream>

void LatticeBase::set_rngs() {
	int seed = 0;
	for (auto &gen: r) {
		gen = gsl_rng_alloc(gsl_rng_taus2);
		gsl_rng_set(gen, seed);
		seed++;
	}
}

void LatticeBase::set_grid() {
        grid.resize(pow(dim, n_dim));
        for (auto &i: grid) {
            float z = gsl_rng_uniform(r[0]);
	    i = (z > 0.5) ? 1 : -1; 
        }
    }

const std::vector<int8_t> &LatticeBase::get_grid() {
    return grid;
}
