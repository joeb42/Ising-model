#include <iostream>
#include <string>
#include "LatticeWorker.h"

int main(int argc, char **argv) {
    int numprocs, rank, namelen, dim, height, num_sweeps;
    float T; 
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &namelen);
    dim = std::stoi(argv[1]);
    T = std::stof(argv[2]);
    num_sweeps = std::stoi(argv[3]);
    height = dim / numprocs;
    if (rank == 0) {
        std::cout << "parameters: lattice dimension = " << dim << " temperature = " << T <<
        "K number of lattice sweeps = " << num_sweeps << "\nusing " << numprocs << " MPI workers\n"; 
    }
    LatticeWorker worker(height, dim, T, rank, &status, numprocs);
    for (int sweep = 0; sweep < num_sweeps; sweep++) {
        worker.sweep();
    }
    if (rank == 0) { 
        std::vector<int8_t> lattice (dim * dim);
        MPI_Gather(worker.sub_lattice.data() + dim, worker.sub_lattice.size() - 2 * dim, MPI_INT8_T, lattice.data(), worker.sub_lattice.size() - 2 * dim, MPI_INT8_T, 0, MPI_COMM_WORLD);
        // uncomment to print lattice
        // for (int i = 0; i < dim; i++) {
        //     for (int j = 0; j < dim; j++) {
        //         std::cout << +lattice[i * dim + j] << ",";
        //     }
        // }
    }
    else {
        MPI_Gather(worker.sub_lattice.data() + dim, worker.sub_lattice.size() - 2 * dim, MPI_INT8_T, NULL, 0, MPI_INT8_T, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
