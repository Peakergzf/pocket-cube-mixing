#include "rubiks_cube_3x3.hpp"
#include <iostream> 


void RubiksCube3x3::Cube3x3::clockwiseRotate(Layer3x3 x) {
    //    ur um ul    |    lr lm ll
    // ll tl tm tr rr | dl bl ml tl ur
    // lm ml mm mr rm | dm bm mm tm um
    // lr bl bm br rl | dr br mr tr ul
    //    dl dm dr    |    rl rm rr
    
    vector<Color> prev(cube);
    
    // current (front) face
    cube[x.tl] = prev[x.bl], cube[x.tm] = prev[x.ml], cube[x.tr] = prev[x.tl];
    cube[x.ml] = prev[x.bm],                          cube[x.mr] = prev[x.tm];
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

void RubiksCube3x3::Cube3x3::counterClockwiseRotate(Layer3x3 x) {
    //    ur um ul    |    rr rm rl
    // ll tl tm tr rr | ul tr mr br dr
    // lm ml mm mr rm | um tm mm bm dm
    // lr bl bm br rl | ur tl ml bl dl
    //    dl dm dr    |    ll lm lr
    
    vector<Color> prev(cube);
    
    // current (front) face
    cube[x.tl] = prev[x.tr], cube[x.tm] = prev[x.mr], cube[x.tr] = prev[x.br];
    cube[x.ml] = prev[x.tm],                          cube[x.mr] = prev[x.bm];
    cube[x.bl] = prev[x.tl], cube[x.bm] = prev[x.ml], cube[x.br] = prev[x.bl];
    // left face
    cube[x.ll] = prev[x.ul], cube[x.lm] = prev[x.um], cube[x.lr] = prev[x.ur];
    // up face
    cube[x.ul] = prev[x.rl], cube[x.um] = prev[x.rm], cube[x.ur] = prev[x.rr];
    // right face
    cube[x.rl] = prev[x.dl], cube[x.rm] = prev[x.dm], cube[x.rr] = prev[x.dr];
    // down face
    cube[x.dl] = prev[x.ll], cube[x.dm] = prev[x.lm], cube[x.dr] = prev[x.lr];
}

void RubiksCube3x3::Cube3x3::print() {
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
        for (int i = 0; i < 3; i++) cout << "   ";
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
