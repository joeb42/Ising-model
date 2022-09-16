#include "Lattice2D.h"
#include <iostream>
#include <string>

using std::stoi, std::stof;

int main(int argc, char **argv) {
    int dim, sweeps, threads;
    float T;
    if (argc != 5) {
        dim = 100;
        T = 1.1;
        sweeps = 100;
        threads = 4;
    }
    else {
        dim = stoi(argv[1]);
        T = stof(argv[2]);
        sweeps = stoi(argv[3]);
        threads = stoi(argv[4]);
    }
    Lattice2D lattice(dim, T, 4);
    for (int i = 0; i < sweeps; i++) {
        lattice.sweep();
    }
    lattice.write_grid();
    return 0;
} 