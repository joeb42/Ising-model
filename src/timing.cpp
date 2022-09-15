#include <iostream>
#include "Lattice.h"
#include <string>
#include <cmath>

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cout << "Wrong number of command line args, 5 required you inputted: " << argc << "\n";
        return;
    }
    int dim = std::stoi(argv[1]);
    float T = std::stof(argv[2]);
    int num_threads = std::stoi(argv[3]);
    
}