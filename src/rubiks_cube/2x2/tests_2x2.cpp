#include "rubiks_cube_2x2.cpp"
#include <assert.h>


void RubiksCube2x2::basicTest() {
    RubiksCube2x2::Cube2x2 cube, id;
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

void RubiksCube2x2::seq1() {
    RubiksCube2x2::Cube2x2 cube, id;
    for (int i = 0; i < 6; i++) {
        cube.R();
        cube.U_();
        cube.R_();
        cube.U();
    }
    assert(id == cube);
}

void RubiksCube2x2::seq2U() {
    RubiksCube2x2::Cube2x2 cube, id;
    for (int i = 0; i < 9; i++) {
        cube.R();
        cube.U_();
    }
    assert(id == cube);
}

void RubiksCube2x2::seq2D() {
    RubiksCube2x2::Cube2x2 cube, id;
    for (int i = 0; i < 9; i++) {
        cube.B();
        cube.D_();
    }
    assert(id == cube);
}

void RubiksCube2x2::seq2L() {
    RubiksCube2x2::Cube2x2 cube, id;
    for (int i = 0; i < 9; i++) {
        cube.F();
        cube.L_();
    }
    assert(id == cube);
}

void RubiksCube2x2::seq2R() {
    RubiksCube2x2::Cube2x2 cube, id;
    for (int i = 0; i < 9; i++) {
        cube.D();
        cube.R_();
    }
    assert(id == cube);
}

void RubiksCube2x2::seq2F() {
    RubiksCube2x2::Cube2x2 cube, id;
    for (int i = 0; i < 9; i++) {
        cube.R();
        cube.F_();
    }
    assert(id == cube);
}

void RubiksCube2x2::seq2B() {
    RubiksCube2x2::Cube2x2 cube, id;
    for (int i = 0; i < 9; i++) {
        cube.U();
        cube.B_();
    }
    assert(id == cube);
}
