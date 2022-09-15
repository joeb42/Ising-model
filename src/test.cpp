#include <vector>
#include <gsl/gsl_rng.h>
#include <iostream>
#include <omp.h>
#include <cmath>


class LatticeBase {
    protected:
        int n_threads;
        int n_dim;
        int dim;
        float T;
        gsl_rng *r [4];
        std::vector<int8_t> grid;
    public:
        // virtual funcs will depend on number of dimensions so remain abstract (virtual) in base class
        virtual void write_grid() = 0;
        virtual int delta_E(const std::vector<int> &coords) = 0;
        virtual void sweep(int offset) = 0;
        virtual void sweep() = 0;
        // virtual double energy() = 0;
        // virtual double E_squared() = 0;
        // virtual double magnetisation() = 0;
        void set_rngs() {
            for (int i = 0; i < 4; i++) {
                r[i] = gsl_rng_alloc(gsl_rng_taus2);
                if (i == 0){
                    gsl_rng_set(r[i],i);
                    continue;
                }
                int seed = gsl_rng_get(r[0]);
                gsl_rng_set(r[i], seed);
            }
        }
        void set_grid() {
            grid.resize(pow(dim, n_dim));
            for (auto &i: grid) {
                float z = gsl_rng_uniform(r[0]);
                if (z > 0.5)
                    i = 1;
                else 
                    i = -1;
            }
        }
        std::vector<int8_t> get_grid() {
            return grid;
        }
};

class Lattice2D: public LatticeBase {

    public:
        Lattice2D (int dimension, float temperature, int num_threads) { 
            n_dim = 2;
            dim = dimension;
            T = temperature;
            n_threads = num_threads;
            set_rngs();
            set_grid();
        }

        void write_grid() {
            int idx = 0;
            for (auto &i: grid) {
                if (idx % dim == dim-1) {
                    std::cout << +i << "\n";
                }
                else {
                    std::cout << +i << ",";
                }
            }
        }

        int delta_E(const std::vector<int> &coords) {
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

        void sweep(int offset) {
            #pragma omp parallel for num_threads(n_threads)  
            for (int i = 0; i < (dim * dim)/2; i++){
                int min = omp_get_thread_num() * dim / (2 * n_threads);
                int range = ceil( (float) dim / (2 * n_threads));
                int x = gsl_rng_uniform_int(r[omp_get_thread_num()], range + min) + offset;
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

        void sweep() {
            sweep(0);
            sweep(1);
        }
};


int main(int argc, char **argv) {
    int dim = std::stoi(argv[1]);
    float T = std::stof(argv[2]);
    int sweeps = std::stoi(argv[3]);
    Lattice2D lattice(dim, T, sweeps);
    for (int i = 0; i < sweeps; i++) {
        lattice.sweep();
    }
    lattice.write_grid();
    return 0;
}
