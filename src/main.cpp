#include "./rubiks_cube/tests_3x3.cpp"
#include <chrono>
#include <iostream> 

using namespace RubiksCube3x3;
using namespace std::chrono;

int main() {
    auto start = high_resolution_clock::now();

    for (int i = 0; i < 2000; i++) {
        basicTest(); // 12 moves
        seq1(); // 24 moves
        seq2(); // 126 moves
        seq3(); // 24 moves
        seq4(); // 16 moves
        seq5(); // 24 moves
    }

    auto finish = high_resolution_clock::now();
    
    duration<double> elapsed = finish - start;

    // 226 * 2000 = 452,000 moves (assertions not included) in 0.17-0.25s
    cout << elapsed.count() << "s" << endl;
}
