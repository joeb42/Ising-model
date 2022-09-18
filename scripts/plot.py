import numpy as np 
import matplotlib.pyplot as plt 
import pandas as pd
import sys

def main():
    # for line in sys.stdin:
    #     print(line)
    lattice = pd.read_csv(sys.stdin, header=None, engine='c').to_numpy()
    plt.imshow(lattice, cmap="binary")
    plt.show()

if __name__ == "__main__":
    main()
