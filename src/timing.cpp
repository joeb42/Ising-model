#include <iostream>
#include "Lattice2D.h"
#include <string>
#include <omp.h>
#include <vector>
#include <cmath>

using std::stoi; 

int MAX_DIM = 1000;
int MIN_DIM = 10;

double mean(const std::vector<double> &v);
double stdev(const std::vector<double> &v);
void print_times(const std::vector<std::vector<double>> &times, const std::vector<int> &dims);

int main(int argc, char **argv) { 
    // get parameters as command line args or revert to defaults
    int sweeps, n_threads, n_repeats;
    float T = 1.0;
    if (argc == 4) {
        sweeps = stoi(argv[1]);
        n_threads = stoi(argv[2]);
        n_repeats = stoi(argv[3]);
    }
    else {
        sweeps = 100;
        n_threads = 2;
        n_repeats = 10;
    }
    std::vector<int> dims = {10, 100, 500, 1000};
    std::vector<std::vector<double>> times;
    for (int &dim: dims) {
        std::vector<double> t(n_repeats);
        Lattice2D lattice(dim, T, n_threads);
        for (int i = 0; i < n_repeats; i++) {
            double t0 = omp_get_wtime();
            for (int i = 0; i < sweeps; i++)
                lattice.sweep();
            double t1 = omp_get_wtime();
            t[i] = t1 - t0;
        }
        times.push_back(t);
    }
    print_times(times, dims);
    return 0;
}

double mean(const std::vector<double> &v) {
    double sum = 0;
    for (auto &i: v)
        sum += i;
    return sum / v.size(); 
}

double stdev(const std::vector<double> &v) {
    double m = mean(v);
    double variance = 0;
    for (auto &i: v) 
        variance += (m - i) * (m - i);
    variance = (double) variance / v.size();
    return sqrt(variance);
}

void print_times(const std::vector<std::vector<double>> &times, const std::vector<int> &dims) {
    std::cout << "dim,mean_time,stdev\n";
    for (int i = 0; i < dims.size(); i++) {
        std::cout << dims[i] << "," << mean(times[i]) << "," << stdev(times[i]) << "\n";
    }
}
