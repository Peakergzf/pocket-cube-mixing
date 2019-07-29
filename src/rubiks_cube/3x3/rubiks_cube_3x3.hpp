#include <string>
#include <vector>

using namespace std;


#ifndef RUBIKS_CUBE_3X3
#define RUBIKS_CUBE_3X3


namespace RubiksCube3x3 {
    
    enum Color {WT, YL, GN, BL, OR, RD};
    string ColorName = "WYGBOR";

    struct Layer3x3 {
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

        // constructor
        Layer3x3(int tl, int tm, int tr, int ml, int mm, int mr, int bl, int bm, int br,
                 int ll, int lm, int lr, int ul, int um, int ur, int rl, int rm, int rr, int dl, int dm, int dr): 
            tl{tl}, tm{tm}, tr{tr}, ml{ml}, mm{mm}, mr{mr}, bl{bl}, bm{bm}, br{br},
            ll{ll}, lm{lm}, lr{lr}, ul{ul}, um{um}, ur{ur}, rl{rl}, rm{rm}, rr{rr}, dl{dl}, dm{dm}, dr{dr}  {}
    };



    class Cube3x3 {
        
        private:
            
            // ========================================================================
            // cube[i] := the color of piece i, 0 <= i <= 53 
            // (initialied as the solved state)
            // ========================================================================
            
            vector<Color> cube= {
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
            // six layers of the cube: up, down, front, back, left and right
            // ========================================================================

            //    ur um ul    |    33 34 35 
            // ll tl tm tr rr | 36  0  1  2 47
            // lm ml mm mr rm | 37  3  4  5 46
            // lr bl bm br rl | 38  6  7  8 45
            //    dl dm dr    |    18 19 20 
            Layer3x3 up {0, 1, 2, 3, 4, 5, 6, 7, 8, 36, 37, 38, 35, 34, 33, 45, 46, 47, 18, 19, 20};

            //    ur um ul    |    24 25 26 
            // ll tl tm tr rr | 44  9 10 11 51
            // lm ml mm mr rm | 43 12 13 14 52
            // lr bl bm br rl | 42 15 16 17 53
            //    dl dm dr    |    27 28 29 
            Layer3x3 down {9, 10, 11, 12, 13, 14, 15, 16, 17, 44, 43, 42, 26, 25, 24, 53, 52, 51, 27, 28, 29};

            //    ur um ul    |     6  7  8 
            // ll tl tm tr rr | 38 18 19 20 45
            // lm ml mm mr rm | 41 21 22 23 48
            // lr bl bm br rl | 44 24 25 26 51
            //    dl dm dr    |     9 10 11 
            Layer3x3 front {18, 19, 20, 21, 22, 23, 24, 25, 26, 38, 41, 44, 8, 7, 6, 51, 48, 45, 9, 10, 11};

            //    ur um ul    |    15 16 17 
            // ll tl tm tr rr | 42 27 28 29 53
            // lm ml mm mr rm | 39 30 31 32 50
            // lr bl bm br rl | 36 33 34 35 47
            //    dl dm dr    |     0  1  2 
            Layer3x3 back {27, 28, 29, 30, 31, 32, 33, 34, 35, 42, 39, 36, 17, 16, 15, 47, 50, 53, 0, 1, 2};

            //    ur um ul    |     0  3  6 
            // ll tl tm tr rr | 33 36 37 38 18
            // lm ml mm mr rm | 30 39 40 41 21
            // lr bl bm br rl | 27 42 43 44 24
            //    dl dm dr    |    15 12  9 
            Layer3x3 left {36, 37, 38, 39, 40, 41, 42, 43, 44, 33, 30, 27, 6, 3, 0, 24, 21, 18, 15, 12, 9};

            //    ur um ul    |     8  5  2 
            // ll tl tm tr rr | 20 45 46 47 35
            // lm ml mm mr rm | 23 48 49 50 32
            // lr bl bm br rl | 26 51 52 53 29
            //    dl dm dr    |    11 14 17 
            Layer3x3 right {45, 46, 47, 48, 49, 50, 51, 52, 53, 20, 23, 26, 2, 5, 8, 29, 32, 35, 11, 14, 17};

        public:

            // ========================================================================
            // face rotations
            // ========================================================================
            
            void clockwiseRotate(Layer3x3 x);

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

            void counterClockwiseRotate(Layer3x3 x);

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
            // utility functions
            // ========================================================================

            bool operator ==(const Cube3x3 c1) {return c1.cube == cube;}

            void print();
    };


    // ========================================================================
    // tests
    // ========================================================================

    void basicTest();

    void seq1();

    void seq2();

    void seq3();

    void seq4();

    void seq5();
    
}

#endif
