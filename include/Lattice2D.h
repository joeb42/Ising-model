#pragma once
#include "LatticeBase.h"
#include <vector>

class Lattice2D: public LatticeBase {

    public:
	// Constructor 
        Lattice2D (int dimension, float temperature, int num_threads);
	
	// write grid to stdout in csv format
        void write_grid();

	// change in energy for spin flip, where coords = {x, y}
        int delta_E(const std::vector<int> &coords);

	// single MC half-step (offset = 0 -> evens, offset = 1 -> odds)
        void sweep(int offset);

	// single MC step 
        void sweep();
};
