#include <bits/stdc++.h>
using namespace std;

// https://ruwix.com/the-rubiks-cube/notation/advanced/
// https://ruwix.com/the-rubiks-cube/japanese-western-color-schemes/

enum Color {WT, YL, GN, BL, OR, RD};

typedef vector<Color> vc;

struct RubiksCube {

    // initialied as the solved state
    vc state = {
        WT, WT, WT, WT, WT, WT, WT, WT, WT, // up
        YL, YL, YL, YL, YL, YL, YL, YL, YL, // down
        GN, GN, GN, GN, GN, GN, GN, GN, GN, // front
        BL, BL, BL, BL, BL, BL, BL, BL, BL, // back
        OR, OR, OR, OR, OR, OR, OR, OR, OR, // left
        RD, RD, RD, RD, RD, RD, RD, RD, RD, // right
    };

    // ========================================================================
    // face rotations
    // ========================================================================
    
    // up face clockwise
    void U() {
        vc copy(state);
        copy[0] = state[53];
        state = copy;
    }

    // down face clockwise
    void D() {

    }
    // front face clockwise
    void F() {

    }

    // back face clockwise
    void B() {

    }
    
    // left face clockwise
    void L() {

    }
    
    // right face clockwise
    void R() {

    }
    
    // ------------------------------------------------------------------------

    // up face counterclockwise
    void U_() {

    }

    // down face counterclockwise
    void D_() {

    }

    // front face counterclockwise
    void F_() {

    }

    // back face counterclockwise
    void B_() {

    }
    
    // left face counterclockwise
    void L_() {

    }
    
    // right face counterclockwise
    void R_() {

    }

    // ========================================================================
    // slice turns
    // ========================================================================

    // middle layer turn
    void M() {

    }

    // equatorial layer turn
    void E() {

    }

    // standing layer turn
    void S() {

    }

    // ========================================================================
    // utility functions
    // ========================================================================
    
    void print_cube() {
        cout << state[0] << endl;
    }

};

int main() {
    RubiksCube cube;
    cube.print_cube();
    cube.U();
    cube.print_cube();
}
