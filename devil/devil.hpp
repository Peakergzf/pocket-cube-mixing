#include <bits/stdc++.h>
#include <chrono>
#include <assert.h>

using namespace std;
using namespace std::chrono;

typedef vector<int> vi;
typedef vector<vi> vvi;

// ========================================================================
// struct and function declaration
// ========================================================================

struct Cube {
    vi p;
    vi q;
};

int encode_p(vi p);
vi decode_p(int x, int n);

int encode_q(vi q);
vi decode_q(int y);

int encode_cube(Cube cube);
Cube decode_cube(int i);

vi compose(vi sgm, vi tau);
Cube make_move(Cube before, Cube move);

int factorial(int n);
vi argsort(vi v);

vvi construct_graph();
bool is_bipartite(vvi G, int s);

void test_encode_p();
void test_encode_q();
void test_encode_cube();
void state_graph_timing();

// ========================================================================
// constants and global variables
// ========================================================================

Cube X =  { {4, 1, 0, 3, 6, 5, 2}, {1, 0, 1, 0, 2, 0, 2} };
Cube X_ = { {2, 1, 6, 3, 0, 5, 4}, {2, 0, 1, 0, 2, 0, 1} };
Cube Y =  { {0, 2, 6, 3, 4, 1, 5}, {0, 1, 2, 0, 0, 1, 2} };
Cube Y_ = { {0, 5, 1, 3, 4, 6, 2}, {0, 2, 2, 0, 0, 1, 1} };
Cube Z =  { {0, 1, 2, 5, 3, 6, 4}, {0, 0, 0, 1, 1, 2, 2} };
Cube Z_ = { {0, 1, 2, 4, 6, 3, 5}, {0, 0, 0, 2, 1, 2, 1} };

vector<Cube> MOVES = {X, X_, Y, Y_, Z, Z_};

Cube SOLVED = { {0, 1, 2, 3, 4, 5, 6}, {0, 0, 0, 0, 0, 0, 0} };

const int P = factorial(7);
const int Q = pow(3, 6);
const int N = P * Q;
