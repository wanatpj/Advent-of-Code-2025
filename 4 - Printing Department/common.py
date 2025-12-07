import numpy as np

shifts = [
    (i, j)
    for i in range(-1, 2)
    for j in range(-1, 2)
    if i != 0 or j != 0
]

def shifted(x: np.ndarray, shift: tuple[int, int]) -> np.ndarray:
    i, j = shift

    cropped_i = x[max(i,0) or None:min(i,0) or None, :]
    shift_i = np.concat([np.zeros_like(x[x.shape[0] + min(i,0):, :]), cropped_i, np.zeros_like(x[:max(i,0), :])], axis=0)
    cropped_j = shift_i[:, max(j,0) or None:min(j,0) or None]
    shift_ij = np.concat([np.zeros_like(x[:, x.shape[1] + min(j,0):]), cropped_j, np.zeros_like(x[:, :max(j,0)])], axis=1)

    return shift_ij