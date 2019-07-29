#include "./rubiks_cube/3x3/tests_3x3.cpp"
#include "./rubiks_cube/2x2/tests_2x2.cpp"
#include <chrono>
#include <iostream> 

using namespace std::chrono;

void test2x2() {
    for (int i = 0; i < 5000; i++) {
        RubiksCube2x2::basicTest();  // 12 moves
        RubiksCube2x2::seq1();  // 24 moves
        RubiksCube2x2::seq2();  // 18 moves
    }
    // 42 * 5000 = 210,000 moves (assertions not included) in 0.08-0.10s
}

void test3x3() {
    for (int i = 0; i < 2000; i++) {
        RubiksCube3x3::basicTest(); // 12 moves
        RubiksCube3x3::seq1(); // 24 moves
        RubiksCube3x3::seq2(); // 126 moves
        RubiksCube3x3::seq3(); // 24 moves
        RubiksCube3x3::seq4(); // 16 moves
        RubiksCube3x3::seq5(); // 24 moves
    }
    // 226 * 2000 = 452,000 moves (assertions not included) in 0.17-0.25s
}

int main() {
    auto start = high_resolution_clock::now();

    // test3x3();
    test2x2();

    auto finish = high_resolution_clock::now();
    
    duration<double> elapsed = finish - start;

    cout << elapsed.count() << "s" << endl;
}
