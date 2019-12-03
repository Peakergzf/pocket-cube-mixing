import numpy as np
import timeit
from scipy.sparse import rand, csc_matrix
from scipy.sparse.linalg import LinearOperator


def print_float_matrix(mat):
    for row in mat:
        for entry in row:
            print("{0:.10f} ".format(entry), end="")
        print()
    print()


def small():
    m = 10
    mat = rand(m, m, density=0.1, format="csc")
    print_float_matrix(mat.toarray())

    t_start = timeit.default_timer()
    for _ in range(5):
        mat = mat @ mat
        print_float_matrix(mat.toarray())
    t_end = timeit.default_timer()

    print(t_end - t_start)


def large():
    # m          1e4  2e4  4e4
    # construct  25s  156s  -
    # 2nd power  36s  328s  -

    m = int(2e4)

    t_start = timeit.default_timer()

    lil_mat = rand(m, m, density=0.1, format="lil")
    t0 = timeit.default_timer()
    print("construct matrix in", t0 - t_start, "s")

    matrix = csc_matrix(lil_mat)
    t1 = timeit.default_timer()
    print("convert matrix in", t1 - t0, "s")

    _ = matrix @ matrix
    t_end = timeit.default_timer()
    print("multiply matrix in", t_end - t1, "s")


def main():
    # small()
    large()


if __name__ == '__main__':
    main()
