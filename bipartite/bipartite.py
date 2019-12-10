# https://possiblywrong.wordpress.com/2011/08/28/solving-the-2x2x2-rubiks-cube/

from math import factorial
from itertools import permutations
from numpy import arange, base_repr, array, append, zeros
from collections import deque
import timeit


def rank_perm(p):
    p = array(p)
    q = array(p).argsort()
    r = 0
    for k in range(len(p) - 1, 0, -1):
        s = p[k]
        p[k], p[q[k]] = p[q[k]], p[k]
        q[k], q[s] = q[s], q[k]
        r += s * factorial(k)
    return r


def un_rank_perm(r, n):
    p = list(range(n))
    for k in range(n - 1, 0, -1):
        s, r = divmod(r, factorial(k))
        p[k], p[s] = p[s], p[k]
    return p


def pack_cube(cube):
    """
    :param cube = (p, q) where
    p is in S_7 and q[:6] is in Z_3^6 (a 6-digit number in base 3)
    (only need q[:6] since the orientations of any 6 cubies determine the remaining orientation)

    represent p as a decimal number, call it x, x is in [0, 7!-1]
    convert the number represented by q[:6] from base 3 to base 10, call it y, y is in [0, 3^6-1]
    e.g. max q[:6] is (222222)_3 = (2*3^5 + 2*3^4 + 2*3^3 + 2*3^2 + 2*3^1 + 2*3^0)_10 = (3^6-1)_10

    now, combine x and y and produce a number in [0, (7!*3^6)-1] (there are 7!*3^6 states):
    :returns x * 3^6 + y
    3^6 is the "base" in this representation (one more than 3^6-1)
    e.g. say x is in [0, 4-1], y is in [0, 10-1],
         if we want to represent a number in [0, (4*10)-1], we write x * 10 + y

    note: representing the states of the cube as Z_6^24 (24 facelets, each has possibly 6 colors),
    and directly converting the number between base 6 and 10 wouldn't work because
    there is no bijection between [0, 6^24-1] and [0, 7!-1]
    (too much redundancy in this representation, not compact enough)
    """
    p, q = cube
    return rank_perm(p) * 3 ** 6 + sum(q[:6] * (3 ** arange(5, -1, -1)))


def unpack_cube(i):
    p, q = divmod(i, 3 ** 6)  # p and q in base 10
    # base_repr(q, 3, 6) is a string representation of q10
    # in base 3 with 6 zeros padded at the front
    # base_repr(q, 3, 6)[-6:] slices the last 6 characters
    q = array(list(map(ord, base_repr(q, 3, 6)[-6:]))) - ord('0')
    # FTC states: sum(q) = 0 mod 3, which can be used to recover the 7th element of q
    return array(un_rank_perm(p, 7)), append(q, -sum(q) % 3)


cube_moves = ((array([4, 1, 0, 3, 6, 5, 2]), array([1, 0, 1, 0, 2, 0, 2])),
              (array([2, 1, 6, 3, 0, 5, 4]), array([2, 0, 1, 0, 2, 0, 1])),
              (array([0, 2, 6, 3, 4, 1, 5]), array([0, 1, 2, 0, 0, 1, 2])),
              (array([0, 5, 1, 3, 4, 6, 2]), array([0, 2, 2, 0, 0, 1, 1])),
              (array([0, 1, 2, 5, 3, 6, 4]), array([0, 0, 0, 1, 1, 2, 2])),
              (array([0, 1, 2, 4, 6, 3, 5]), array([0, 0, 0, 2, 1, 2, 1])))


def move_cube(cube, move):
    (cp, cq), (mp, mq) = cube, move
    return cp[mp], (cq[mp] + mq) % 3


def cube_graph():
    n = factorial(7) * 3 ** 6
    g = []
    for i in range(n):
        cube = unpack_cube(i)
        g.append([pack_cube(move_cube(cube, move)) for move in cube_moves])
    return g


def is_bipartite(g, v):
    n = len(g)
    color = [-1 for _ in range(n)]
    color[v] = 1
    q = deque([v])
    while q:
        u = q.popleft()
        for w in g[u]:
            if color[w] == -1:
                color[w] = 1 - color[u]
                q.append(w)
            elif color[w] == color[u]:
                return False
    return True


def main():
    for n in range(8):
        for p in map(lambda tup: list(tup), list(permutations(list(range(n))))):
            assert un_rank_perm(rank_perm(p), n) == p

    t0 = timeit.default_timer()
    solved = pack_cube((arange(7), zeros(7, dtype='int32')))
    g = cube_graph()
    t1 = timeit.default_timer()
    print("construct graph in", t1 - t0, "s")

    assert is_bipartite(g, solved)
    print("bfs in", timeit.default_timer() - t1, "s")


if __name__ == '__main__':
    main()
