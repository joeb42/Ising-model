#pragma once
#include <vector>
#include <gsl/gsl_rng.h>
#include <array>

// Lattice base class 
class LatticeBase {
    protected:
        int n_threads;
        int n_dim;
        int dim;
        float T;
        // gsl_rng *r [4];
        std::array<gsl_rng*, 4> r;
        std::vector<int8_t> grid;
    public:
        // print grid to stdout in csv format 
        virtual void write_grid() = 0;

        // Calculate delta E for spin flip of lattice point defined by coords (argument left as std::vector to allow for different dims)
        virtual int delta_E(const std::vector<int> &coords) = 0;

        // Single monte carlo step (sample N^Dim random lattice points)
        virtual void sweep() = 0;

        // Setup gsl random number generators
        void set_rngs();

        // Initialise lattice with random spins
        void set_grid();

	// getter for grid 
        const std::vector<int8_t> &get_grid();
        
	// virtual double energy() = 0;
        // virtual double E_squared() = 0;
        // virtual double magnetisation() = 0;
};
