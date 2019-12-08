#include <bits/stdc++.h>
#include <eigen/Eigen/Sparse>

#define N 3000000 // N x N matrix
#define M 18 // M non zero entries per column

// https://eigen.tuxfamily.org/dox/group__TutorialSparse.html

using namespace std;
using namespace std::chrono;
using namespace Eigen;

int main() {
    duration<double> elapsed;
    auto t0 = high_resolution_clock::now();

    SparseMatrix<int> mat(N, N);
    mat.reserve(VectorXi::Constant(N, M));
    for (int i = 0; i < N; i++) {
        // vector<int> v(N);
        // iota(v.begin(), v.end(), 0);
        // random_shuffle (v.begin(), v.end());
        // for (int j = 0; j < M; j++) mat.insert(i, v[j]) = 1;

        for (int j = i; j < min(i + M, N); j++) mat.insert(i, j) = 1;
    }
    mat.makeCompressed();

    auto t1 = high_resolution_clock::now();
    elapsed = t1 - t0;
    cout << elapsed.count() << "s" << endl;

    for (int i = 0; i < 5; i++) {
        t0 = high_resolution_clock::now();
        mat = (mat * mat).pruned();

        t1 = high_resolution_clock::now();
        elapsed = t1 - t0;
        cout << elapsed.count() << "s" << endl;
    }
}


/*
     3e4  3e5   3e6
fill 0.06 0.75  6.34
mult 0.41 4.82 54.38
*/

/*
i-th power: 48.61, 151.78, 523.77 
*/