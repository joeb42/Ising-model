#include "LatticeBase.h"
#include <cmath>

void LatticeBase::set_rngs() {
    for (int i = 0; i < 4; i++) {
        r[i] = gsl_rng_alloc(gsl_rng_taus2);
        if (i == 0){
            gsl_rng_set(r[i],i);
            continue;
        }
        int seed = gsl_rng_get(r[0]);
        gsl_rng_set(r[i], seed);
    }
}

void LatticeBase::set_grid() {
        grid.resize(pow(dim, n_dim));
        for (auto &i: grid) {
            float z = gsl_rng_uniform(r[0]);
            if (z > 0.5)
                i = 1;
            else 
                i = -1;
        }
    }

std::vector<int8_t> LatticeBase::get_grid() {
    return grid;
}
