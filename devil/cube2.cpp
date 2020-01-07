#include <bits/stdc++.h>
#include <chrono>
#include <assert.h>
#include <limits>
#include "./alglib/stdafx.h"
#include "./alglib/linalg.h"

using namespace std;
using namespace alglib;

typedef vector<int> vi;
typedef vector<vi> vvi;


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
// vector<Cube> MOVES = {X, X_, Y, Y_, Z, Z_};

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


void test() {
    sparsematrix s;
    integer_1d_array row_sizes = "[2,2,2,1]";
    sparsecreatecrs(4, 4, row_sizes, s);
    sparseset(s, 0, 0, 2);
    sparseset(s, 0, 1, 1);
    sparseset(s, 1, 1, 4);
    sparseset(s, 1, 2, 2);
    sparseset(s, 2, 2, 3);
    sparseset(s, 2, 3, 1);
    sparseset(s, 3, 3, 9);
    real_1d_array x = "[1,-1,1,-1]";
    real_1d_array y1 = "[]";
    real_1d_array y2 = "[]";

    // https://www.alglib.net/translator/man/manual.cpp.html#sub_sparsemv
    sparsemv(s, x, y1);
    printf("%s\n", y1.tostring(0).c_str()); // [1,-2,2,-9]

    // https://www.alglib.net/translator/man/manual.cpp.html#sub_sparsemtv
    sparsemtv(s, x, y2);
    printf("%s\n", y2.tostring(0).c_str()); // [2,-3,1,-8]
}


void power() {
    // each of the N rows has M non-zero entries
    string sizes_str = "[";
    for (int i = 0; i < N; i++) {
        sizes_str += to_string(M);
        if (i != N - 1) sizes_str += ",";
    } 
    sizes_str += "]";
    // https://stackoverflow.com/questions/13294067/how-to-convert-string-to-char-array-in-c
    char *sizes_c = new char [sizes_str.length()+1];
    strcpy(sizes_c, sizes_str.c_str());

    // https://www.alglib.net/translator/man/manual.cpp.html#example_sparse_d_crs
    auto t0 = chrono::high_resolution_clock::now();
    sparsematrix q;

    integer_1d_array row_sizes(sizes_c);
    // https://www.alglib.net/translator/man/manual.cpp.html#sub_sparsecreatecrs
    sparsecreatecrs(N, N, row_sizes, q);
    // initialize from left to right, from top to bottom
    for (int v = 0; v < N; v++) {
        Cube cube = decode_cube(v);
        vi u_vec;
        for (Cube move: MOVES) {
            int u = encode_cube(apply_move(cube, move));
            u_vec.push_back(u);
        }
        sort(u_vec.begin(), u_vec.end());
        for (int i = 0; i < M; i++) sparseset(q, v, u_vec[i], 1);
    }

    auto t1 = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = t1 - t0;
    cout << "matrix constructed (in " << elapsed.count() << "s)" << endl;

    // // check that q is symmetric
    // for (int i = 0; i < N; i++) {
    //     for (int j = i + 1; j < N; j++) {
    //         assert(sparseget(q, i, j) == sparseget(q, j, i));
    //     }
    // }

    string x_str = "[1,";
    for (int i = 1; i < N; i++) {
        x_str += "0";
        if (i != N - 1) x_str += ",";
    } 
    x_str += "]";
    char *x_c = new char [x_str.length()+1];
    strcpy(x_c, x_str.c_str());

    real_1d_array x(x_c);

    double u = 1.0 / N;

    for (int t = 1; t <= 50; t++) {
        real_1d_array y = "[]";
        sparsemtv(q, x, y);
        x = y;

        double d = 0.0;
        for (int i = 0; i < N; i++) {
            d += fabsl(x[i] / pow(M, t) - u);
        }
        cout << t << "\t";
        cout << fixed << setprecision(20) << d / 2 << endl;
    }
}

int main() {
    // test();
    power();
}
