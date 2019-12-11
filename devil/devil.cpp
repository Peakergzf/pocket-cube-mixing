#include <bits/stdc++.h>
#include <assert.h>

using namespace std;
using namespace std::chrono;

typedef vector<int> vi;

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


int main() {
    test_perm_rank();
}

