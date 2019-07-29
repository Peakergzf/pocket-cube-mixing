#include <string>
#include <vector>

using namespace std;


#ifndef RUBIKS_CUBE_2X2
#define RUBIKS_CUBE_2X2


namespace RubiksCube2x2 {
    
    enum Color {WT, YL, GN, BL, OR, RD};
    string ColorName = "WYGBOR";

    struct Layer2x2 {
        // current (front) face
        int tl, tr; // topLeft, topRight
        int bl, br; // bottomLeft, bottomRight
        // left face
        int ll, lr; // leftLeft, leftRight
        // up face
        int ul, ur; // upLeft, upRight
        // right face
        int rl, rr; // rightLeft, rightRight
        // down face
        int dl, dr; // downLeft, downRight

        // constructor
        Layer2x2(int tl, int tr, int bl, int br,
                 int ll, int lr, int ul, int ur, int rl, int rr, int dl, int dr): 
            tl{tl}, tr{tr}, bl{bl}, br{br},
            ll{ll}, lr{lr}, ul{ul}, ur{ur}, rl{rl}, rr{rr}, dl{dl}, dr{dr}  {}
    };



    class Cube2x2 {
        
        private:
            
            // ========================================================================
            // cube[i] := the color of piece i, 0 <= i <= 23 
            // (initialied as the solved state)
            // ========================================================================
            
            vector<Color> cube= {
            //   0,  1,  2,  3,
                WT, WT, WT, WT, // up
            //   4,  5,  6,  7, 
                YL, YL, YL, YL, // down
            //   8,  9, 10, 11,
                GN, GN, GN, GN, // front
            //  12, 13, 14, 15,
                BL, BL, BL, BL, // back
            //  16, 17, 18, 19, 
                OR, OR, OR, OR, // left
            //  20, 21, 22, 23, 
                RD, RD, RD, RD, // right
            };

            // ========================================================================
            // six layers of the cube: up, down, front, back, left and right
            // ========================================================================

            //    ur ul    |    14 15 
            // ll tl tr rr | 18  0  1 21
            // lr bl br rl | 16  2  3 20
            //    dl dr    |     8  9 
            Layer2x2 up {0, 1, 2, 3, 18, 16, 15, 14, 20, 21, 8, 9};
            
            //    ur ul    |    10 11 
            // ll tl tr rr | 17  4  5 22
            // lr bl br rl | 19  6  7 23
            //    dl dr    |    12 13 
            Layer2x2 down {4, 5, 6, 7, 17, 19, 11, 10, 23, 22, 12, 13};

            //    ur ul    |     2  3 
            // ll tl tr rr | 16  8  9 20
            // lr bl br rl | 17 10 11 22
            //    dl dr    |     4  5 
            Layer2x2 front {8, 9, 10, 11, 16, 17, 3, 2, 22, 20, 4, 5};

            //    ur ul    |     6  7 
            // ll tl tr rr | 19 12 13 23
            // lr bl br rl | 18 14 15 21
            //    dl dr    |     0  1 
            Layer2x2 back {12, 13, 14, 15, 19, 18, 7, 6, 21, 23, 0, 1};

            //    ur ul    |     8 10 
            // ll tl tr rr |  2 16 17 4
            // lr bl br rl |  0 18 19 6
            //    dl dr    |    14 12 
            Layer2x2 left {16, 17, 18, 19, 2, 0, 10, 8, 6, 4, 14, 12};

            //    ur ul    |     3  1 
            // ll tl tr rr |  9 20 21 15
            // lr bl br rl | 11 22 23 13
            //    dl dr    |     5  7 
            Layer2x2 right {20, 21, 22, 23, 9, 11, 1, 3, 13, 15, 5, 7};

        public:

            // ========================================================================
            // face rotations
            // ========================================================================
            
            void clockwiseRotate(Layer2x2 x);

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

            void counterClockwiseRotate(Layer2x2 x);

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

            bool operator ==(const Cube2x2 c1) {return c1.cube == cube;}

            void print();
    };


    // ========================================================================
    // tests
    // ========================================================================

    void basicTest();

    void seq1();

    void seq2();

}

#endif
