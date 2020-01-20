#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef long long ll;
typedef vector<ll> vll;
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
Cube Y2 = { {0, 6, 5, 3, 4, 2, 1}, {0, 0, 0, 0, 0, 0, 0} };

Cube Z =  { {0, 1, 2, 5, 3, 6, 4}, {0, 0, 0, 1, 2, 2, 1} };
Cube Z_ = { {0, 1, 2, 4, 6, 3, 5}, {0, 0, 0, 1, 2, 2, 1} };
Cube Z2 = { {0, 1, 2, 6, 5, 4, 3}, {0, 0, 0, 0, 0, 0, 0} };

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

// ========================================================================
// main program
// ========================================================================

int main() {
    vvi Y(N, vi(M, 0));

    for (int i = 0; i < N; i++) {
        Cube cube = decode_cube(i);
        for (int j = 0; j < M; j++) {
            Y[i][j] = encode_cube(apply_move(cube, MOVES[j]));
        }
    }

    double ui = 1.0 / N;
    vector<double> x(N, 0.0); 
    x[0] = 1.0;

    for (int t = 1; t <= 50; t++) {
        double d = 0.0;

        for (int i = 0; i < N; i++) {
            double xi = 0.0; // new x[i]
            for (int j = 0; j < M; j++) {
                xi += x[Y[i][j]] / M;
            }
            x[i] = xi;
            d += fabsl(xi - ui);
        }
        cout << t << "\t";
        cout << fixed << setprecision(20) << d / 2 << endl;
    }
}


/*
acknowledgements

the cube state representation is inspired from
https://possiblywrong.wordpress.com/2011/08/28/solving-the-2x2x2-rubiks-cube/

the matrix vector multiplication method is derived by Eric Zhou
http://users.monash.edu/~ezhou/

*/
