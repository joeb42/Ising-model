#include <vector>
#include <array>
#include <gsl/gsl_rng.h>
#include <cmath>
#include <iostream>
#include "mpi.h"
#include "LatticeWorker.h"

#define ODD 0
#define EVEN 1

LatticeWorker::LatticeWorker(int height_, int width_, float T_, int id_, MPI_Status *status_, int numprocs_) {
    height = height_;
    width = width_;
    T = T_;
    id = id_;
    status = *status_;
    numprocs = numprocs_;
    sub_lattice.resize((height + 2) * (width));
    r = gsl_rng_alloc(gsl_rng_taus2);
    gsl_rng_set(r, id);
    set_lattice();
}

void LatticeWorker::set_lattice() {
    for (auto &i: sub_lattice) {
        float z = gsl_rng_uniform(r);
        i = (z > 0.5) ? 1 : -1;
    }
}

int LatticeWorker::delta_E(const std::vector<int> &coords) {
    int x = coords[0];
    int y = coords[1];
    int s = 0;
    std::array<std::array<int, 2>, 4> neighbours = {{{x-1, y}, {x, y-1}, {x+1, y}, {x, y+1}}};
    for (auto &neighbour: neighbours) {
        int row = (neighbour[0] + width) % height;
        int column = (neighbour[1] + height) % width;
        s += sub_lattice[row * width + column];
    }
    return 2 * s * sub_lattice[x * width + y];
}

void LatticeWorker::sweep() {
    exchange(ODD);
    sweep(ODD);
    exchange(EVEN);
    sweep(EVEN);
}

void LatticeWorker::sweep(int offset) {
    for (int i = 0; i < (height * width) / 2; i++) {
        int x =  gsl_rng_uniform_int(r, width);
        int y = gsl_rng_uniform_int(r, height / 2);
        if (offset) {
            y += height / 2;
        }
        std::vector<int> coords = {x, y};
        int dE = delta_E(coords);
        if (dE <= 0) {
            sub_lattice[y * width + x] *= -1;
        }
        else {
            float n = gsl_rng_uniform(r);
            if (std::exp(-dE/T) > n) {
                sub_lattice[y * width + x] *= -1;
            }
        }
    }
}


void LatticeWorker::exchange(int offset) {
    int source, dest;
    // for even half step
    if (offset == 0) {
        dest = (id + 1) % numprocs;
        source = (numprocs + id - 1) % numprocs;
        // std::cout << "rank: " << id << " source: " << source << " dest: " << dest << "\n";
        if (id % 2 == 0) {
            MPI_Ssend(sub_lattice.data() + width * (height - 2), width, MPI_INT8_T, dest, 1, MPI_COMM_WORLD);
            MPI_Recv(sub_lattice.data(), width, MPI_INT8_T, source, 1, MPI_COMM_WORLD, &status);
        }
        else if (id % 2 == 1) {
            MPI_Recv(sub_lattice.data(), width, MPI_INT8_T, source, 1, MPI_COMM_WORLD, &status);
            MPI_Ssend(sub_lattice.data() + width * (height - 2), width, MPI_INT8_T, dest, 1, MPI_COMM_WORLD);
        }
    }
    else if (offset == 1) {
        dest = (numprocs + id - 1) % numprocs;
        source = (id + 1) % numprocs;
        if (id % 2 == 0) {
            MPI_Ssend(sub_lattice.data() + width, width, MPI_INT8_T, dest, 2, MPI_COMM_WORLD);
            MPI_Recv(sub_lattice.data() + width * height, width, MPI_INT8_T, source, 2, MPI_COMM_WORLD, &status);
        }
        else if (id % 2 == 1) {
            MPI_Recv(sub_lattice.data() + width * height, width, MPI_INT8_T, source, 2, MPI_COMM_WORLD, &status);
            MPI_Ssend(sub_lattice.data() + width, width, MPI_INT8_T, dest, 2, MPI_COMM_WORLD);
        }
    }
}
