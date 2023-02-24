#pragma once
#include <vector>
#include <gsl/gsl_rng.h>
#include "mpi.h"

class LatticeWorker {
    private:
        int height;
        int width;
        float T;
        int id;
        int numprocs;
        gsl_rng *r;
        MPI_Status status;
    
    public:
        LatticeWorker(int height_, int width_, float T_, int id_, MPI_Status &status_, int numprocs);
        void set_lattice();
        std::vector<int8_t> sub_lattice;
        // energy change of flipping spin at coords[0], coords[1]
        int delta_E(const std::vector<int> &coords);
        // complete monte carlo step
        void sweep();
        // single monte carlo half step
        void sweep(int offset);
        // exchange data before half step
        void exchange(int offset);
};