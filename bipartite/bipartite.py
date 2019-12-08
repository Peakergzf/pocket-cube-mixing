# https://possiblywrong.wordpress.com/2011/08/28/solving-the-2x2x2-rubiks-cube/

from math import factorial
from itertools import permutations
from numpy import arange, base_repr, array, append, zeros
from collections import deque


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
    p, q = cube
    return rank_perm(p) * 3 ** 6 + sum(q[:6] * (3 ** arange(5, -1, -1)))


def unpack_cube(i):
    p, q = divmod(i, 3 ** 6)
    q = array(list(map(ord, base_repr(q, 3, 6)[-6:]))) - ord('0')
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

    solved = pack_cube((arange(7), zeros(7, dtype='int32')))
    assert is_bipartite(cube_graph(), solved)


if __name__ == '__main__':
    main()
