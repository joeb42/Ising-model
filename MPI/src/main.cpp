#include <iostream>
#include "LatticeWorker.h"

int main(int argc, char **argv) {
    int numprocs, rank, namelen, source, dest, offset;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &namelen);
    if (rank == 0) {
        std::cout << "numprocs: " << numprocs << "\n";
    }
    LatticeWorker worker(10, 10, 1.0, rank, &status, numprocs);
    for (int sweep = 0; sweep < 10; sweep++) {
        worker.sweep();
    }
    if (rank == 0) { 
        std::vector<int8_t> lattice (numprocs * 10 * 10);
        MPI_Gather(worker.sub_lattice.data() + 10, worker.sub_lattice.size() - 20 , MPI_INT8_T, lattice.data(), worker.sub_lattice.size() - 20, MPI_INT8_T, 0, MPI_COMM_WORLD);
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                std::cout << +lattice[i * 10 + j] << " ";
                if (j == 9) {
                    std::cout << "\n";
                }
            }
        }
    }
    else {
        MPI_Gather(worker.sub_lattice.data() + 10, worker.sub_lattice.size() - 20, MPI_INT8_T, NULL, 0, MPI_INT8_T, 0, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
