#include <bits/stdc++.h>
#include <chrono>
#include <assert.h>

using namespace std;
using namespace std::chrono;

typedef vector<int> vi;
typedef vector<vi> vvi;

int factorial(int n) {
    return (n == 1 || n == 0) ? 1 : n * factorial(n - 1);
}

void print_vec(vi v) {
    int n = v.size();
    cout << "[";
    for (int i = 0; i < n; i++) {
        cout << v[i];
        if (i != n - 1) cout << " ";
    }
    cout << "]" << endl;
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

int rank_perm(vi p) {
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

vi un_rank_perm(int r, int n) {
    vi p(n); 
    iota(p.begin(), p.end(), 0);
    for (int k = n - 1; k > 0; k--) {
        int f = factorial(k);
        int s = r / f;
        r %= f;
        swap(p[k], p[s]);
    }
    return p;
}

struct Cube {
    // initialised to the solved state
    vi p = {0, 1, 2, 3, 4, 5, 6};
    vi q = {0, 0, 0, 0, 0, 0, 0};
};

int base_3_to_10(vi q) {
    vi v(q.begin(), q.end() - 1);
    reverse(v.begin(), v.end());
    int dec = 0;
    for (int i = 0; i < 6; i++) {
        dec += v[i] * pow(3, i);
    }
    return dec;
}

int pack_cube(Cube cube) {
    int x = rank_perm(cube.p);
    int y = base_3_to_10(cube.q);
    return x * pow(3, 6) + y;
}

vi base_10_to_3(int dec) {
    vi q(7);
    int idx = 1;
    while (dec) {
        q[idx++] = dec % 3;
        dec /= 3;
    }
    reverse(q.begin(), q.end());
    int sum = accumulate(q.begin(), q.end(), 0);
    q[6] = (3-sum % 3)%3;
    return q;
}

Cube unpack_cube(int i) {
    int x = i / (int)pow(3, 6), y = i % (int)pow(3, 6);
    Cube cube;
    cube.p = un_rank_perm(x, 7);
    cube.q = base_10_to_3(y);
    return cube;
}

vi compose(vi sgm, vi tau) {
    int n = sgm.size();
    vi comp(n);
    for (int i = 0; i < n; i++) {
        comp[i] = sgm[tau[i]];
    }
    return comp;
}

// TODO
Cube X = {  .p={4, 1, 0, 3, 6, 5, 2}, .q = {1, 0, 1, 0, 2, 0, 2}};
Cube X_ = { .p={2, 1, 6, 3, 0, 5, 4}, .q={2, 0, 1, 0, 2, 0, 1} };
Cube Y =  { .p={0, 2, 6, 3, 4, 1, 5}, .q={0, 1, 2, 0, 0, 1, 2} };
Cube Y_ = { .p={0, 5, 1, 3, 4, 6, 2}, .q={0, 2, 2, 0, 0, 1, 1} };
Cube Z =  { .p={0, 1, 2, 5, 3, 6, 4}, .q={0, 0, 0, 1, 1, 2, 2} };
Cube Z_ = { .p={0, 1, 2, 4, 6, 3, 5}, .q={0, 0, 0, 2, 1, 2, 1} };
vector<Cube> moves = {X, X_, Y, Y_, Z, Z_};

Cube make_move(Cube before, Cube move) {
    Cube after;
    after.p = compose(before.p, move.p);
    vi x = compose(before.q, move.p);
    for (int i = 0; i < 7; i++) {
        after.q[i] = (x[i] + move.q[i]) % 3;
    }
    return after;
}

vvi construct_graph() {
    int n = factorial(7) * pow(3, 6);
    vvi G(n);
    for (int v = 0; v < n; v++) {
        Cube cube = unpack_cube(v);
        for (int j = 0; j < 6; j++) {
            Cube move = moves[j];
            int u = pack_cube(make_move(cube, move));
            G[v].push_back(u);
            // TODO G[u].push_back(v);
        }
    }
    return G;
}

bool is_bipartite(vvi G, int s) {
    vi color(G.size(), -1);
    color[s] = 1;
    queue<int> q;
    q.push(s);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int w: G[u]) {
            if (color[w] == -1) {
                color[w] = 1 - color[u];
                q.push(w);
            }
            else if (color[w] == color[u]) {
                return false;
            }
        }
    }
    return true;
}


void test_perm_rank() {
    for (int n = 0; n < 9; n++) {
        for (int r = 0; r < factorial(n); r++) {
            assert(rank_perm(un_rank_perm(r, n)) == r);
        }

        vi perm(n);
        iota(perm.begin(), perm.end(), 0);
        do {
            assert(un_rank_perm(rank_perm(perm), n) == perm);
        } while (next_permutation(perm.begin(), perm.end()));
    }
}

void test_pack_cube() {
    for (int i = 0; i < factorial(7) * pow(3, 6); i++) {
        assert(pack_cube(unpack_cube(i)) == i);
    }
}


int main() {
    // test_perm_rank();
    // test_pack_cube();

    auto t0 = high_resolution_clock::now();

    vvi G = construct_graph();
    Cube solved;
    auto t1 = high_resolution_clock::now();
    duration<double> elapsed = t1 - t0;
    cout << elapsed.count() << "s" << endl;

    assert(is_bipartite(G, pack_cube(solved)));
    auto t2 = high_resolution_clock::now();
    elapsed = t2 - t1;
    cout << elapsed.count() << "s" << endl;
}
