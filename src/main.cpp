#include "Lattice2D.h"
#include <iostream>
#include <string>

int main(int argc, char **argv) {
    int dim = std::stoi(argv[1]);
    float T = std::stof(argv[2]);
    int sweeps = std::stoi(argv[3]);
    int threads = std::stoi(argv[4]);
    Lattice2D lattice(dim, T, 4);
    for (int i = 0; i < sweeps; i++) {
        lattice.sweep();
    }
    lattice.write_grid();
    return 0;
}

