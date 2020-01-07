#include <bits/stdc++.h>
// #include <eigen/Eigen/Sparse>
#include <Eigen/Sparse>
#include <chrono>
#include <assert.h>
#include <limits>

using namespace std;
using namespace Eigen;

typedef vector<int> vi;
typedef vector<vi> vvi;

typedef SparseMatrix<unsigned int, RowMajor> SpMt;
typedef SparseVector<unsigned int, RowMajor> SpVc;

// ========================================================================
// struct and function declaration
// ========================================================================

struct Cube {
    vi p; // an element of S_7
    vi q; // an element of Z_3^7

    bool operator ==(const Cube other) { return other.p == p && other.q == q; }

    void print() {
        auto print_vec = [](vi v) { cout << "["; for (auto x : v) { cout << x << " "; } cout << "]"; };
        print_vec(p); cout << ", "; print_vec(q); cout << endl;
    }
};

// helper functions
int factorial(int n);
vi argsort(vi v);
vi compose(vi sgm, vi tau);

// ========================================================================
// constants and global variables
// ========================================================================

Cube X =  { {4, 1, 0, 3, 6, 5, 2}, {0, 0, 0, 0, 0, 0, 0} };
Cube X_ = { {2, 1, 6, 3, 0, 5, 4}, {0, 0, 0, 0, 0, 0, 0} };
Cube X2 = { {6, 1, 4, 3, 2, 5, 0}, {0, 0, 0, 0, 0, 0, 0} };

Cube Y =  { {0, 2, 6, 3, 4, 1, 5}, {0, 2, 1, 0, 0, 1, 2} };
Cube Y_ = { {0, 5, 1, 3, 4, 6, 2}, {0, 2, 1, 0, 0, 1, 2} };
Cube Y2 = { {0, 6, 5, 3, 4, 2, 1}, {0, 2, 1, 0, 0, 1, 2} };

Cube Z =  { {0, 1, 2, 5, 3, 6, 4}, {0, 0, 0, 1, 2, 2, 1} };
Cube Z_ = { {0, 1, 2, 4, 6, 3, 5}, {0, 0, 0, 1, 2, 2, 1} };
Cube Z2 = { {0, 1, 2, 6, 5, 4, 3}, {0, 0, 0, 1, 2, 2, 1} };

vector<Cube> MOVES = {X, X_, X2, Y, Y_, Y2, Z, Z_, Z2};

Cube SOLVED = { {0, 1, 2, 3, 4, 5, 6}, {0, 0, 0, 0, 0, 0, 0} };

const int P = factorial(7);
const int Q = pow(3, 6);
const int N = P * Q;

const int M = MOVES.size();


// ========================================================================
// cube state representation
// ========================================================================

int encode_p(vi p) {
    // map from S7 to [0, 7! - 1]
    vi q = argsort(p);
    int r = 0, n = p.size();
    for (int k = n - 1; k > 0; k--) {
        int s = p[k];
        swap(p[k], p[q[k]]);
        swap(q[k], q[s]);
        r += s * factorial(k);
    }
    return r;
}

vi decode_p(int x, int n) {
    // map from [0, 7! - 1] to S7
    vi p(n); 
    iota(p.begin(), p.end(), 0);
    for (int k = n - 1; k > 0; k--) {
        int f = factorial(k);
        int s = x / f;
        x %= f;
        swap(p[k], p[s]);
    }
    return p;
}

int encode_q(vi q) {
    // convert `q` from base 3 to decimal

    // the orientations of any 6 cubies determine the remaining orientation
    vi v(q.begin(), q.end() - 1);
    reverse(v.begin(), v.end());
    int dec = 0;
    for (int i = 0; i < 6; i++) {
        dec += v[i] * pow(3, i);
    }
    return dec;
}

vi decode_q(int y) {
    // convert `y` from decimal to base 3
    // 0 <= y <= 3^6 - 1

    vi q(7);
    int idx = 1; // (before reverse q) q[0] is not encoded in y
    while (y) {
        q[idx++] = y % 3;
        y /= 3;
    }
    reverse(q.begin(), q.end());
    int sum = accumulate(q.begin(), q.end(), 0);
    // FTC states: sum(q) = 0 mod 3, which can be used to recover the 7th element of q
    q[6] = (3 - sum % 3) % 3;
    return q;
}

int encode_cube(Cube cube) {
    int x = encode_p(cube.p);
    int y = encode_q(cube.q);
    return x * Q + y;
}

Cube decode_cube(int i) {
    // 0 <= i <= (7! * 3^6) - 1
    int x = i / Q;
    int y = i % Q;
    Cube cube = { decode_p(x, 7), decode_q(y) };
    return cube;
}

Cube apply_move(Cube before, Cube move) {
    // apply one of the moves `move` to cube state `before` 
    // and get cube state `after`

    vi p(7), q(7);
    p = compose(before.p, move.p);
    vi _q = compose(before.q, move.p);
    for (int i = 0; i < 7; i++) {
        q[i] = (_q[i] + move.q[i]) % 3;
    }
    Cube after = {p, q};
    return after;
}

// ------------------------------------------------------------------------
// helper functions
// ------------------------------------------------------------------------

int factorial(int n) {
    return (n == 1 || n == 0) ? 1 : n * factorial(n - 1);
}

vi argsort(vi v) {
    // returns the indices that would sort `v`
    // e.g. when v = [8, 7, 5, 6], idx = [2, 3, 1, 0]
    // https://stackoverflow.com/a/12399290

    vi idx(v.size());
    // initialised to [0, 1, ..., v.size()-1]
    iota(idx.begin(), idx.end(), 0);

    // sort idx by values in v
    auto comp = [v](int i, int j) {
        return v[i] < v[j];
    };
    sort(idx.begin(), idx.end(), comp);

    return idx;
}

vi compose(vi sgm, vi tau) {
    // compose two permutations `sgm` and `tau`
    // e.g. when sgm = {2, 0, 1}, tau = {1, 0, 2}, comp(sgm, tau) = {0, 2, 1}
    // since {0, 1, 2} --tau--> {1, 0, 2} --sgm--> {0, 2, 1}

    int n = sgm.size();
    vi comp(n);
    for (int i = 0; i < n; i++) {
        comp[i] = sgm[tau[i]];
    }
    return comp;
}

// ------------------------------------------------------------------------
// testing
// ------------------------------------------------------------------------

void cube_encoding_test() {
    // p encoding test
    for (int n = 0; n < 9; n++) {
        for (int x = 0; x < factorial(n); x++) {
            assert(encode_p(decode_p(x, n)) == x);
        }

        vi perm(n);
        iota(perm.begin(), perm.end(), 0);
        do {
            assert(decode_p(encode_p(perm), n) == perm);
        } while (next_permutation(perm.begin(), perm.end()));
    }

    // q encoding test
    for (int y = 0; y < Q; y++) {
        assert(encode_q(decode_q(y)) == y);
    }

    // cube encoding test
    for (int i = 0; i < N; i++) {
        assert(encode_cube(decode_cube(i)) == i);
    }
}

void seq_test() {
    Cube cube = SOLVED, id = SOLVED;
    for (int i = 0; i < 4; i++) { apply_move(cube, X); } assert(id == cube);
    for (int i = 0; i < 4; i++) { apply_move(cube, X_); } assert(id == cube);
    for (int i = 0; i < 4; i++) { apply_move(cube, Y); } assert(id == cube);
    for (int i = 0; i < 4; i++) { apply_move(cube, Y_); } assert(id == cube);
    for (int i = 0; i < 4; i++) { apply_move(cube, Z); } assert(id == cube);
    for (int i = 0; i < 4; i++) { apply_move(cube, Z_); } assert(id == cube);
    for (int i = 0; i < 2; i++) { apply_move(cube, X2); } assert(id == cube);
    for (int i = 0; i < 2; i++) { apply_move(cube, Y2); } assert(id == cube);
    for (int i = 0; i < 2; i++) { apply_move(cube, Z2); } assert(id == cube);
    // seq1
    for (int i = 0; i < 6; i++) {
        cube = apply_move(cube, Y); // R
        cube = apply_move(cube, Z_); // U_
        cube = apply_move(cube, Y_); // R_
        cube = apply_move(cube, Z); // U
    }
    assert(id == cube);
    // seq2 on R, U_
    for (int i = 0; i < 9; i++) {
        cube = apply_move(cube, Y); // R
        cube = apply_move(cube, Z_); // U_
    }
    assert(id == cube);
    // seq2 on F, U_
    for (int i = 0; i < 9; i++) {
        cube = apply_move(cube, X); // F
        cube = apply_move(cube, Z_); // U_
    }
    assert(id == cube);
}

// ========================================================================
// graph
// ========================================================================

vvi construct_graph() {
    vvi G(N);
    for (int v = 0; v < N; v++) { // for each vertex v (cube state)
        Cube cube = decode_cube(v);
        for (Cube move: MOVES) { // for each neighbour of v (reached by a move)
            int u = encode_cube(apply_move(cube, move));
            G[v].push_back(u);
            // G[u].push_back(v);
        }
    }
    return G;
}

bool is_bipartite(vvi G, int s) {
    // bfs traverse and (1, 0)-color graph `G` from source vertex `s`

    const int UNCOLORED = -1;
    vi color(G.size(), UNCOLORED); // the color of each vertex
    color[s] = 1; // color s with color 1
    queue<int> q; q.push(s);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int w: G[u]) { // for each neighbour w of vertex u
            if (color[w] == UNCOLORED) { // if w is not colored
                color[w] = 1 - color[u]; // switch color between 0 and 1
                q.push(w);
            }
            // if w and u are adjacent and have the same color
            else if (color[w] == color[u]) {
                return false; // the graph is not bipartite
            }
        }
    }
    return true;
}

// ========================================================================
// matrix
// ========================================================================

SpMt construct_matrix() {
    // https://eigen.tuxfamily.org/dox/group__TutorialSparse.html#title3

    // column major NxN sparse matrix
    SpMt mat(N, N);
    // reserve space for M non-zero entries per column
    mat.reserve(VectorXi::Constant(N, M));

    for (int v = 0; v < N; v++) {
        Cube cube = decode_cube(v);
        for (Cube move: MOVES) {
            int u = encode_cube(apply_move(cube, move));
            mat.insert(v, u) = 1;
        }
    }
    mat.makeCompressed();

    assert(mat.nonZeros() == N * M);

    return mat;
}

SpMt matrix_power(int T, SpMt mat) {
    auto t0 = chrono::high_resolution_clock::now();
    auto t1 = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed;

    // https://eigen.tuxfamily.org/dox/group__TutorialSparse.html#title6
    // https://eigen.tuxfamily.org/dox/group__SparseQuickRefPage.html
    SpMt prod(mat);
    prod.makeCompressed();
    
    for (int t = 2; t < T; t++) {
        t0 = chrono::high_resolution_clock::now();
        prod = (prod * mat).pruned();
        prod.makeCompressed();

        t1 = chrono::high_resolution_clock::now();
        elapsed = t1 - t0;
        cout << t << "-th power in " << elapsed.count() << "s (";
        cout << prod.nonZeros() << " non-zeros)" << endl;
    }
    return prod;
}

// ========================================================================
// main program
// ========================================================================

void main_test() {
    cout << "cube encoding testing ... ";
    cube_encoding_test();
    cout << "passed" << endl;
    
    cout << "move sequence testing ...";
    seq_test();
    cout << "passed" << endl;
    
    cout << "graph constructing ... ";
    auto t0 = chrono::high_resolution_clock::now();
    vvi G = construct_graph();
    auto t1 = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = t1 - t0;
    cout << "constructed (in " << elapsed.count() << "s)" << endl;

    cout << "bipartite testing ... ";
    assert(is_bipartite(G, encode_cube(SOLVED)));
    cout << "passed" << endl;
}

int main() {
    auto t0 = chrono::high_resolution_clock::now();
    SpMt q = construct_matrix();
    auto t1 = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = t1 - t0;
    cout << "matrix constructed (in " << elapsed.count() << "s)" << endl;

    SpVc x(N);
    x.coeffRef(0) = 1; // initialise x to be e1
    double u = 1.0 / N;
    
    assert(x.cols() == q.rows());
    for (int t = 1; t <= 50; t++) {
        x = x * q;
        double d = 0.0;
        for (int i = 0; i < N; i++) {
            d += fabsl(x.coeffRef(i) / pow(M, t) - u);
        }
        cout << t << "\t";
        cout << fixed << setprecision(20) << d / 2 << endl;
    }

    // cout << std::numeric_limits<double>::min() << endl;
    // cout << std::numeric_limits<double>::max() << endl;
}
