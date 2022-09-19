#include "Lattice2D.h"
#include <cmath>
#include <omp.h>
#include <iostream>

Lattice2D::Lattice2D (int dimension, float temperature, int num_threads) { 
    n_dim = 2;
    dim = dimension;
    T = temperature;
    n_threads = num_threads;
    set_rngs();
    set_grid();
}

void Lattice2D::write_grid() {
    int idx = 0;
    for (auto &i: grid) {
        if (idx % dim == dim-1) {
            std::cout << +i << "\n";
        }
        else {
            std::cout << +i << ",";
        }
        idx++;
    }
}

int Lattice2D::delta_E(const std::vector<int> &coords) {
    // random row between thread num * rows_per_thread and thread num * rows_per_thread + rows_per_thread 
    // split grid into chunks along x axis for each thread
    int x = coords[0];
    int y = coords[1];
    int s = 0;
    std::vector<std::vector<int>> neighbours = {{x-1, y}, {x, y-1}, {x+1, y}, {x, y+1}};
    for (auto &neighbour: neighbours) {
        int row = (neighbour[0] + dim) % dim;
        int column = (neighbour[1] + dim) % dim;
        s += grid[row*dim + column];
    }
    return 2 * s * grid[x*dim + y];
}

void Lattice2D::sweep(int offset) {
    #pragma omp parallel for num_threads(n_threads)  
    for (int i = 0; i < (dim * dim)/2; i++) {
        int min = omp_get_thread_num() * dim / (2 * n_threads);
        int range = ceil( (float) dim / (2 * n_threads));
        int x = 2 * (gsl_rng_uniform_int(r[omp_get_thread_num()], range) + min) + offset;
        int y = gsl_rng_uniform_int(r[omp_get_thread_num()], dim);
        std::vector<int> coords = {x, y};
        int dE = delta_E(coords);
        if (dE <= 0) {
            grid[x*dim + y] *= -1;
        }
        else {
            float n = gsl_rng_uniform(r[omp_get_thread_num()]);
            if (exp(-dE/T) > n) {
                grid[x*dim +y] *= -1;
            }
        }
    }
}

void Lattice2D::sweep() {
    Lattice2D::sweep(0);
    Lattice2D::sweep(1);
}