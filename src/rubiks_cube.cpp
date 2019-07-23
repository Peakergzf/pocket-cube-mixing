#include <bits/stdc++.h>
using namespace std;

enum Color {WT, YL, GN, BL, OR, RD};
string ColorName = "WYGBOR";

typedef vector<Color> vc;

const int DIM = 3;
const int N_FACES = 6;

// indexes of the pieces in a (non-middle) layer
struct Layer {
    //    ur um ul
    // ll tl tm tr rr
    // lm ml mm mr rm
    // lr bl bm br rl
    //    dl dm dr
    
    // constructor
    Layer(int tl, int tm, int tr, int ml, int mm, int mr, int bl, int bm, int br,
          int ll, int lm, int lr, int ul, int um, int ur, int rl, int rm, int rr, int dl, int dm, int dr): 
        tl{tl}, tm{tm}, tr{tr}, ml{ml}, mm{mm}, mr{mr}, bl{bl}, bm{bm}, br{br},
        ll{ll}, lm{lm}, lr{lr}, ul{ul}, um{um}, ur{ur}, rl{rl}, rm{rm}, rr{rr}, dl{dl}, dm{dm}, dr{dr}  {}
    
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

    // ------------------------------------------------------------------------

    //    ur um ul    |    33 34 35 
    // ll tl tm tr rr | 36  0  1  2 47
    // lm ml mm mr rm | 37  3  4  5 46
    // lr bl bm br rl | 38  6  7  8 45
    //    dl dm dr    |    18 19 20 
    Layer up {0, 1, 2, 3, 4, 5, 6, 7, 8, 36, 37, 38, 35, 34, 33, 45, 46, 47, 18, 19, 20};

    //    ur um ul    |    24 25 26 
    // ll tl tm tr rr | 44  9 10 11 51
    // lm ml mm mr rm | 43 12 13 14 52
    // lr bl bm br rl | 42 15 16 17 53
    //    dl dm dr    |    27 28 29 
    Layer down {9, 10, 11, 12, 13, 14, 15, 16, 17, 44, 43, 42, 26, 25, 24, 53, 52, 51, 27, 28, 29};

    //    ur um ul    |     6  7  8 
    // ll tl tm tr rr | 38 18 19 20 45
    // lm ml mm mr rm | 41 21 22 23 48
    // lr bl bm br rl | 44 24 25 26 51
    //    dl dm dr    |     9 10 11 
    Layer front {18, 19, 20, 21, 22, 23, 24, 25, 26, 38, 41, 44, 8, 7, 6, 51, 48, 45, 9, 10, 11};

    //    ur um ul    |    15 16 17 
    // ll tl tm tr rr | 42 27 28 29 53
    // lm ml mm mr rm | 39 30 31 32 50
    // lr bl bm br rl | 36 33 34 35 47
    //    dl dm dr    |     0  1  2 
    Layer back {27, 28, 29, 30, 31, 32, 33, 34, 35, 42, 39, 36, 17, 16, 15, 47, 50, 53, 0, 1, 2};

    //    ur um ul    |     0  3  6 
    // ll tl tm tr rr | 33 36 37 38 18
    // lm ml mm mr rm | 30 39 40 41 21
    // lr bl bm br rl | 27 42 43 44 24
    //    dl dm dr    |    15 12  9 
    Layer left {36, 37, 38, 39, 40, 41, 42, 43, 44, 33, 30, 27, 6, 3, 0, 24, 21, 18, 15, 12, 9};

    //    ur um ul    |     8  5  2 
    // ll tl tm tr rr | 20 45 46 47 35
    // lm ml mm mr rm | 23 48 49 50 32
    // lr bl bm br rl | 25 51 52 53 29
    //    dl dm dr    |    11 14 17 
    Layer right {45, 46, 47, 48, 49, 50, 51, 52, 53, 20, 23, 25, 2, 5, 8, 29, 32, 35, 11, 14, 17};

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
    void U() {clockwiseRotate(up);}

    // down face clockwise
    void D() {clockwiseRotate(down);}

    // front face clockwise
    void F() {clockwiseRotate(front);}

    // back face clockwise
    void B() {clockwiseRotate(back);}
    
    // left face clockwise
    void L() {clockwiseRotate(left);}
    
    // right face clockwise
    void R() {clockwiseRotate(right);}
    
    // ------------------------------------------------------------------------
    
    // TODO
    void counterClockwiseRotate(Layer x) {
        // //    ur um ul    |    lr lm ll
        // // ll tl tm tr rr | dl bl ml tl ur
        // // lm ml mm mr rm | dm bm mm tm um
        // // lr bl bm br rl | dr br mr tr ul
        // //    dl dm dr    |    rl rm rr
        
        // vc prev(cube);
        
        // // current (front) face
        // cube[x.tl] = prev[x.bl], cube[x.tm] = prev[x.ml], cube[x.tr] = prev[x.tl];
        // cube[x.ml] = prev[x.bm], cube[x.mm] = prev[x.mm], cube[x.mr] = prev[x.tm];
        // cube[x.bl] = prev[x.br], cube[x.bm] = prev[x.mr], cube[x.br] = prev[x.tr];
        
        // // left face
        // cube[x.ll] = prev[x.dl], cube[x.lm] = prev[x.dm], cube[x.lr] = prev[x.dr];
        
        // // up face
        // cube[x.ul] = prev[x.ll], cube[x.um] = prev[x.lm], cube[x.ur] = prev[x.lr];

        // // right face
        // cube[x.rl] = prev[x.ul], cube[x.rm] = prev[x.um], cube[x.rr] = prev[x.ur];
        // // down face
        // cube[x.dl] = prev[x.rl], cube[x.dm] = prev[x.rm], cube[x.dr] = prev[x.rr];
    }

    // up face counterclockwise
    void U_() {counterClockwiseRotate(up);}

    // down face counterclockwise
    void D_() {counterClockwiseRotate(down);}

    // front face counterclockwise
    void F_() {counterClockwiseRotate(front);}

    // back face counterclockwise
    void B_() {counterClockwiseRotate(back);}
    
    // left face counterclockwise
    void L_() {counterClockwiseRotate(left);}
    
    // right face counterclockwise
    void R_() {counterClockwiseRotate(right);}


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
    cube.B();
    cube.L();
    cube.U();
    cube.L();
    cube.F();
    cube.prettyPrint();
}
