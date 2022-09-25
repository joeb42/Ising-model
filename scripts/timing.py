import pandas as pd
import matplotlib.pyplot as plt
import sys

def main():
    times = pd.read_csv(sys.stdin)
    plt.errorbar(times['dim'], times['mean_time'], yerr=times['stdev'], fmt="x")
    plt.xlabel("Lattice dimension")
    plt.ylabel("Mean time (s)")
    plt.show()

if __name__ == "__main__":
    main()


