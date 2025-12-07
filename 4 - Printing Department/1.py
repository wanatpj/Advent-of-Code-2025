import sys

import numpy as np

from common import shifts, shifted


def main():
    x = np.array([list(line.strip()) for line in sys.stdin])
    blockage = np.sum(
        [
            ((x == '@') & (shifted(x, shift) == '@')).astype(int)
            for shift in shifts
        ],
        axis=0,
    )
    print(((x == '@') & (blockage < 4)).sum().item())

if __name__ == "__main__":
    main()