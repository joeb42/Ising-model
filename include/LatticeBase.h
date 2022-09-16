#pragma once
#include <vector>
#include <gsl/gsl_rng.h>


class LatticeBase {
    protected:
        int n_threads;
        int n_dim;
        int dim;
        float T;
        gsl_rng *r [4];
        std::vector<int8_t> grid;
    public:
        virtual void write_grid() = 0;
        virtual int delta_E(const std::vector<int> &coords) = 0;
        virtual void sweep() = 0;
        // virtual double energy() = 0;
        // virtual double E_squared() = 0;
        // virtual double magnetisation() = 0;
        void set_rngs();
        void set_grid();
        std::vector<int8_t> get_grid();
};
