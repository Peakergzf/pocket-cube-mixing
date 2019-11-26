#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

enum Color {WT, YL, GN, BL, OR, RD};
string ColorName = "WYGBOR";

// 3674160 (x24 without equivalence of spatial rotations) configurations
int m = 3674160 * 24;

typedef vector<Color> vc;

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

struct Cube2x2 {
        // ========================================================================
        // cube[i] := the color of piece i, 0 <= i <= 23 
        // (initialied as the solved state)
        // ========================================================================
        
        vc cube= {
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

        // ========================================================================
        // face rotations
        // ========================================================================
        
        void clockwiseRotate(Layer2x2 x) {
            //    ur ul    |    lr ll    
            // ll tl tr rr | dl bl tl ur 
            // lr bl br rl | dr br tr ul 
            //    dl dr    |    rl rr    
            
            vc prev(cube);
            
            // current (front) face
            cube[x.tl] = prev[x.bl], cube[x.tr] = prev[x.tl];
            cube[x.bl] = prev[x.br], cube[x.br] = prev[x.tr];
            // left face
            cube[x.ll] = prev[x.dl], cube[x.lr] = prev[x.dr];
            // up face
            cube[x.ul] = prev[x.ll], cube[x.ur] = prev[x.lr];
            // right face
            cube[x.rl] = prev[x.ul], cube[x.rr] = prev[x.ur];
            // down face
            cube[x.dl] = prev[x.rl], cube[x.dr] = prev[x.rr];
        };

        void U() {clockwiseRotate(up);}

        void D() {clockwiseRotate(down);}

        void F() {clockwiseRotate(front);}

        void B() {clockwiseRotate(back);}

        void L() {clockwiseRotate(left);}
        
        void R() {clockwiseRotate(right);}

        // ------------------------------------------------------------------------

        void counterClockwiseRotate(Layer2x2 x) {
            //    ur ul    |    rr rl    
            // ll tl tr rr | ul tr br dr 
            // lr bl br rl | ur tl bl dl 
            //    dl dr    |    ll lr    
            
            vc prev(cube);
            
            // current (front) face
            cube[x.tl] = prev[x.tr], cube[x.tr] = prev[x.br];
            cube[x.bl] = prev[x.tl], cube[x.br] = prev[x.bl];
            // left face
            cube[x.ll] = prev[x.ul], cube[x.lr] = prev[x.ur];
            // up face
            cube[x.ul] = prev[x.rl], cube[x.ur] = prev[x.rr];
            // right face
            cube[x.rl] = prev[x.dl], cube[x.rr] = prev[x.dr];
            // down face
            cube[x.dl] = prev[x.ll], cube[x.dr] = prev[x.lr];
        };

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

        // ------------------------------------------------------------------------

        void rotate180(Layer2x2 x) {
            //    ur ul    |    dr dl    
            // ll tl tr rr | rl br bl lr 
            // lr bl br rl | rr tr tl ll 
            //    dl dr    |    ul ur    
            
            vc prev(cube);
            
            // current (front) face
            cube[x.tl] = prev[x.br], cube[x.tr] = prev[x.bl];
            cube[x.bl] = prev[x.tr], cube[x.br] = prev[x.tl];
            // left face
            cube[x.ll] = prev[x.rl], cube[x.lr] = prev[x.rr];
            // up face
            cube[x.ul] = prev[x.dl], cube[x.ur] = prev[x.dr];
            // right face
            cube[x.rl] = prev[x.ll], cube[x.rr] = prev[x.lr];
            // down face
            cube[x.dl] = prev[x.ul], cube[x.dr] = prev[x.ur];
        };

        void U2() {rotate180(up);}

        void D2() {rotate180(down);}

        void F2() {rotate180(front);}

        void B2() {rotate180(back);}

        void L2() {rotate180(left);}

        void R2() {rotate180(right);}

        // ========================================================================
        // utility functions
        // ========================================================================

        bool operator ==(const Cube2x2 c1) {return c1.cube == cube;}

        void print() {
            //        0  1
            //        2  3
            // 18 16  8  9 20 21 15 14
            // 19 17 10 11 22 23 13 12
            //        4  5
            //        6  7
            
            auto printSpaces = []() {
                for (int i = 0; i < 2; i++) cout << "   ";
            };

            auto printRow = [this](int i, int j, bool endL) {
                cout << ColorName[cube[i]] << "  " << ColorName[cube[j]];
                if (endL) cout << endl;
                else cout << "  ";
            };

            printSpaces(); printRow(0, 1, true);
            printSpaces(); printRow(2, 3, true);

            printRow(18, 16, false); printRow(8, 9, false); printRow(20, 21, false); printRow(15, 14, true);
            printRow(19, 17, false); printRow(10, 11, false); printRow(22, 23, false); printRow(13, 12, true);

            printSpaces(); printRow(4, 5, true);
            printSpaces(); printRow(6, 7, true);

            cout << endl;
        };

        // ========================================================================
        // stats
        // ========================================================================

        vc moves(int t) {
            int x;
            for (int i = 0; i < t; i++) {
                x = rand() % 18;
                switch (x) {
                    case 0:
                        this->U();
                        break;
                    case 1:
                        this->D();
                        break;
                    case 2:
                        this->F();
                        break;
                    case 3:
                        this->B();
                        break;
                    case 4:
                        this->L();
                        break;
                    case 5:
                        this->R();
                        break;
                    // -------------
                    case 6:
                        this->U_();
                        break;
                    case 7:
                        this->D_();
                        break;
                    case 8:
                        this->F_();
                        break;
                    case 9:
                        this->B_();
                        break;
                    case 10:
                        this->L_();
                        break;
                    case 11:
                        this->R_();
                        break;
                    // -------------
                    case 12:
                        this->U2();
                        break;
                    case 13:
                        this->D2();
                        break;
                    case 14:
                        this->F2();
                        break;
                    case 15:
                        this->B2();
                        break;
                    case 16:
                        this->L2();
                        break;
                    case 17:
                        this->R2();
                        break;
                }
                // this->print();
            }
            return cube;
        };
};

// K_1 := # elements of the sample space of size m, 
//        that have been observed exactly once in a random sample of size N
int K1(int N, int t) {
    map<vc, int> freq;

    for (int i = 0; i < N; i++) {
        Cube2x2 cube;
        vc state = cube.moves(t);
        freq[state]++;
    }

    int cnt = 0;
    for (const auto &x : freq) {
        if (x.second == 1) {
            cnt++;
        }
    }

    return cnt;
}

// E_U(K_1)
double EUK1(int N) {
    return N * pow((m-1)/double(m), N-1); 
} 


int main() {
    auto start = high_resolution_clock::now();

    int N = 1e6;
    double euk1 = EUK1(N);
    for (int t = 1; t <= 30; t++) {
        // test statistic T := E_U(K_1) - K_1
        double t = euk1 - K1(N, t);
        cout << t << " ";
        cout << fixed << setprecision(4) << t << endl;
    }

    auto finish = high_resolution_clock::now();
    
    duration<double> elapsed = finish - start;

    cout << elapsed.count() << "s" << endl;
}
