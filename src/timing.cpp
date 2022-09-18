#include <iostream>
#include "Lattice2D.h"
#include <string>
#include <omp.h>

using std::stoi; 

int main(int argc, char **argv) { 
    // get parameters as command line args or revert to defaults
    int dim, sweeps, n_threads;
    float T = 1.0;
    if (argc == 4) {
        dim = stoi(argv[1]);
        sweeps = stoi(argv[2]);
        n_threads = stoi(argv[3]);
    }
    else {
        dim = 100;
        sweeps = 100;
        n_threads = 4;
    }

    Lattice2D lattice(dim, T, n_threads);
    double t0 = omp_get_wtime();
    for (int i = 0; i < sweeps; i++)
        lattice.sweep();
    double t1 = omp_get_wtime();
    std::cout << "Took " << t1 - t0 << " seconds for " << sweeps << " sweeps for lattice dimension of " << dim << " (" << n_threads << " threads)\n";
    return 0;
}
