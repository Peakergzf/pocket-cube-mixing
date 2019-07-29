#include "rubiks_cube_3x3.cpp"
#include <assert.h>


void RubiksCube3x3::basicTest() {
    RubiksCube3x3::Cube3x3 cube, id;
    cube.F(); cube.F_();
    assert(id == cube);
    cube.B(); cube.B_();
    assert(id == cube);
    cube.U(); cube.U_();
    assert(id == cube);
    cube.D(); cube.D_();
    assert(id == cube);
    cube.L(); cube.L_();
    assert(id == cube);
    cube.R(); cube.R_();
    assert(id == cube);
}

void RubiksCube3x3::seq1() {
    RubiksCube3x3::Cube3x3 cube, id;
    for (int i = 0; i < 6; i++) {
        cube.R();
        cube.U_();
        cube.R_();
        cube.U();
    }
    assert(id == cube);
}

void RubiksCube3x3::seq2() {
    RubiksCube3x3::Cube3x3 cube, id;
    for (int i = 0; i < 63; i++) {
        cube.R();
        cube.U_();
    }
    assert(id == cube);
}

void RubiksCube3x3::seq3() {
    RubiksCube3x3::Cube3x3 cube, id;
    for (int i = 0; i < 4; i++) {
        cube.R(); cube.R();
        cube.L_(); cube.L_();
        if (i % 2 == 0) {
            cube.D(); cube.D();
        }
        else {
            cube.U(); cube.U();
        }
    }
    assert(id == cube);
}

void RubiksCube3x3::seq4() {
    RubiksCube3x3::Cube3x3 cube, id;
    for (int i = 0; i < 4; i++) {
        if (i % 2 == 0) {
            cube.R(); cube.R();
            cube.L_(); cube.L_();
        }
        else {
            cube.F(); cube.F();
            cube.B_(); cube.B_();
        }
    }
    assert(id == cube);
}

void RubiksCube3x3::seq5() {
    RubiksCube3x3::Cube3x3 cube, id;
    for (int i = 0; i < 12; i++) {
        if (i % 2 == 0) {
            cube.R(); cube.L_();
        }
        else {
            cube.F(); cube.B_();
        }
    }
    assert(id == cube);
}
