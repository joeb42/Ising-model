import numpy as np 
import matplotlib.pyplot as plt 
import pandas as pd
import sys
import argparse

def main(path=None):
    lattice = pd.read_csv(sys.stdin, header=None, engine='c').to_numpy()
    plt.imshow(lattice, cmap="binary")
    if path is not None:
        plt.savefig(path+"img.png")
    plt.show()

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--path", "-p", default=None)
    args = parser.parse_args()
    main(path=args.path)
