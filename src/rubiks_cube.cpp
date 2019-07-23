#include <bits/stdc++.h>
using namespace std;

enum Color {WT, YL, GN, BL, OR, RD};
string ColorName = "WYGBOR";

typedef vector<Color> vc;

const int DIM = 3;
const int N_FACES = 6;

// pieces in a (non-middle) layer
struct Layer {
    //    ur um ul
    // ll tl tm tr rr
    // lm ml mm mr rm
    // lr bl bm br rl
    //    dl dm dr

    // current (front) face
    int tl, tm, tr; // topLeft, topMid, topRight
    int ml, mm, mr; // midLeft, midMid, midRight
    int bl, bm, br; // bottomLeft, bottomMid, bottomRight
    // left face
    int ll, lm, lr; // leftLeft, leftMid, leftRight
    // up face
    int ul, um, ur; // upLeft, upMid, upRight
    // right face
    int rl, rm, rr; // rightLeft, rightMid, rightRight
    // down face
    int dl, dm, dr; // downLeft, downMid, downRight
};

struct RubiksCube {

    // cube[i] := the color of piece i, 0 <= i <= 53
    // (initialied as the solved state)
    vc cube = {
    //   0,  1,  2,  3,  4,  5,  6,  7,  8, 
        WT, WT, WT, WT, WT, WT, WT, WT, WT, // up
    //   9, 10, 11, 12, 13, 14, 15, 16, 17,
        YL, YL, YL, YL, YL, YL, YL, YL, YL, // down
    //  18, 19, 20, 21, 22, 23, 24, 25, 26, 
        GN, GN, GN, GN, GN, GN, GN, GN, GN, // front
    //  27, 28, 29, 30, 31, 32, 33, 34, 35, 
        BL, BL, BL, BL, BL, BL, BL, BL, BL, // back
    //  36, 37, 38, 39, 40, 41, 42, 43, 44, 
        OR, OR, OR, OR, OR, OR, OR, OR, OR, // left
    //  45, 46, 47, 48, 49, 50, 51, 52, 53
        RD, RD, RD, RD, RD, RD, RD, RD, RD  // right
    };

    // ========================================================================
    // face rotations
    // ========================================================================

    void clockwiseRotate(Layer x) {
        //    ur um ul    |    lr lm ll
        // ll tl tm tr rr | dl bl ml tl ur
        // lm ml mm mr rm | dm bm mm tm um
        // lr bl bm br rl | dr br mr tr ul
        //    dl dm dr    |    rl rm rr
        
        vc prev(cube);
        
        // current (front) face
        cube[x.tl] = prev[x.bl], cube[x.tm] = prev[x.ml], cube[x.tr] = prev[x.tl];
        cube[x.ml] = prev[x.bm], cube[x.mm] = prev[x.mm], cube[x.mr] = prev[x.tm];
        cube[x.bl] = prev[x.br], cube[x.bm] = prev[x.mr], cube[x.br] = prev[x.tr];
        
        // left face
        cube[x.ll] = prev[x.dl], cube[x.lm] = prev[x.dm], cube[x.lr] = prev[x.dr];
        
        // up face
        cube[x.ul] = prev[x.ll], cube[x.um] = prev[x.lm], cube[x.ur] = prev[x.lr];

        // right face
        cube[x.rl] = prev[x.ul], cube[x.rm] = prev[x.um], cube[x.rr] = prev[x.ur];
        // down face
        cube[x.dl] = prev[x.rl], cube[x.dm] = prev[x.rm], cube[x.dr] = prev[x.rr];

    }

    // up face clockwise
    void U() {
        Layer x;
        //    ur um ul    |    33 34 35 
        // ll tl tm tr rr | 36  0  1  2 47
        // lm ml mm mr rm | 37  3  4  5 46
        // lr bl bm br rl | 38  6  7  8 45
        //    dl dm dr    |    18 19 20 
        x.tl = 0, x.tm = 1, x.tr = 2;
        x.ml = 3, x.mm = 4, x.rr = 5;
        x.bl = 6, x.bm = 7, x.br = 8;
        x.ll = 36, x.lm = 37, x.lr = 38;
        x.ul = 35, x.um = 34, x.ur = 33;
        x.rl = 45, x.rm = 46, x.rr = 47;
        x.dl = 18, x.dm = 19, x.dr = 20;
        clockwiseRotate(x);
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
    
    void print() {
        int n = DIM * DIM * N_FACES; // n = 54
        for (int i = 0; i < n; i++) {
            cout << cube[i] << " ";
            if (i % (DIM * DIM) == (DIM * DIM - 1)) cout << endl;
        }
        for (int i = 0; i < DIM * DIM; i++) cout << "- ";
        cout << endl;
    }

    void prettyPrint() {
        //           0  1  2
        //           3  4  5
        //           6  7  8
        // 36 37 38 18 19 20 45 46 47 35 34 33
        // 39 40 41 21 22 23 48 49 50 32 31 30
        // 42 43 44 24 25 26 51 52 53 29 28 27
        //           9 10 11
        //          12 13 14
        //          15 16 17
        
        auto printSpaces = []() {
            for (int i = 0; i < DIM; i++) cout << "   ";
        };

        auto printRow = [this](int i, int j, int k, bool endL) {
            cout << ColorName[cube[i]] << "  " << ColorName[cube[j]] << "  " << ColorName[cube[k]];
            if (endL) cout << endl;
            else cout << "  ";
        };

        printSpaces(); printRow(0, 1, 2, true);
        printSpaces(); printRow(3, 4, 5, true);
        printSpaces(); printRow(6, 7, 8, true);

        printRow(36, 37, 38, false); printRow(18, 19, 20, false); printRow(45, 46, 47, false); printRow(35, 34, 33, true);
        printRow(39, 40, 41, false); printRow(21, 22, 23, false); printRow(48, 49, 50, false); printRow(32, 31, 30, true);
        printRow(42, 43, 44, false); printRow(24, 25, 26, false); printRow(51, 52, 53, false); printRow(29, 28, 27, true);

        printSpaces(); printRow(9, 10, 11, true);
        printSpaces(); printRow(12, 13, 14, true);
        printSpaces(); printRow(15, 16, 17, true);

        cout << endl;
    }
};

int main() {
    RubiksCube cube;
    cube.prettyPrint();
    cube.U();
    cube.prettyPrint();
}
