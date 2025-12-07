import sys

import numpy as np

from common import shifts, shifted


def main():
    x = np.array([list(line.strip()) for line in sys.stdin])
    total = 0
    last_chunk = -1
    empty = np.full_like(x, '.')
    while last_chunk != 0:
        blockage = np.sum(
            [
                ((x == '@') & (shifted(x, shift) == '@')).astype(int)
                for shift in shifts
            ],
            axis=0,
        )
        last_chunk = ((x == '@') & (blockage < 4)).sum().item()
        total += last_chunk
        x = np.where((x == '@') & (blockage < 4), empty, x)
    print(total)

if __name__ == "__main__":
    main()