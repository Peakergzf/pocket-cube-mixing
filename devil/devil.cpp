#include "devil.hpp"

// ========================================================================
// function implementations
// ========================================================================

int encode_p(vi p) {
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
    vi v(q.begin(), q.end() - 1);
    reverse(v.begin(), v.end());
    int dec = 0;
    for (int i = 0; i < 6; i++) {
        dec += v[i] * pow(3, i);
    }
    return dec;
}

vi decode_q(int y) {
    vi q(7);
    int idx = 1;
    while (y) {
        q[idx++] = y % 3;
        y /= 3;
    }
    reverse(q.begin(), q.end());
    int sum = accumulate(q.begin(), q.end(), 0);
    q[6] = (3-sum % 3)%3;
    return q;
}

int encode_cube(Cube cube) {
    int x = encode_p(cube.p);
    int y = encode_q(cube.q);
    return x * Q + y;
}

Cube decode_cube(int i) {
    int x = i / (int)Q, y = i % (int)Q;
    Cube cube = { decode_p(x, 7), decode_q(y) };
    return cube;
}

vi compose(vi sgm, vi tau) {
    int n = sgm.size();
    vi comp(n);
    for (int i = 0; i < n; i++) {
        comp[i] = sgm[tau[i]];
    }
    return comp;
};

Cube make_move(Cube before, Cube move) {
    vi p(7), q(7);
    p = compose(before.p, move.p);
    vi x = compose(before.q, move.p);
    for (int i = 0; i < 7; i++) {
        q[i] = (x[i] + move.q[i]) % 3;
    }
    Cube after = {p, q};
    return after;
}

int factorial(int n) {
    return (n == 1 || n == 0) ? 1 : n * factorial(n - 1);
}

vi argsort(vi v) {
    // returns the indices that would sort v
    // e.g. when v = [8, 7, 5, 6], idx = [2, 3, 1, 0]
    // (https://stackoverflow.com/a/12399290)

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

vvi construct_graph() {
    vvi G(N);
    for (int v = 0; v < N; v++) {
        Cube cube = decode_cube(v);
        for (Cube move: MOVES) {
            int u = encode_cube(make_move(cube, move));
            G[v].push_back(u);
        }
    }
    return G;
}

bool is_bipartite(vvi G, int s) {
    const int UNCOLORED = -1;
    // switch between the two colors 1 and 0
    auto _switch = [](int col) { return 1 - col; };

    vi color(G.size(), UNCOLORED);
    color[s] = 1; // color the source 1
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int w: G[u]) {
            if (color[w] == UNCOLORED) {
                color[w] = _switch(color[u]);
                q.push(w);
            }
            else if (color[w] == color[u]) {
                return false;
            }
        }
    }
    return true;
}

// ========================================================================
// testing
// ========================================================================

void test_encode_p() {
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
}

void test_encode_q() {
    for (int y = 0; y < Q; y++) {
        assert(encode_q(decode_q(y)) == y);
    }
}

void test_encode_cube() {
    for (int i = 0; i < N; i++) {
        assert(encode_cube(decode_cube(i)) == i);
    }
}

void state_graph_timing() {
    auto t0 = high_resolution_clock::now();

    vvi G = construct_graph();

    auto t1 = high_resolution_clock::now();
    duration<double> elapsed = t1 - t0;
    cout << elapsed.count() << "s" << endl;

    assert(is_bipartite(G, encode_cube(SOLVED)));

    auto t2 = high_resolution_clock::now();
    elapsed = t2 - t1;
    cout << elapsed.count() << "s" << endl;
}

// ========================================================================
// main program
// ========================================================================

int main() {
    test_encode_p();
    test_encode_q();
    test_encode_cube();


}
