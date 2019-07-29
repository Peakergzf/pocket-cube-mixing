#include "rubiks_cube_2x2.hpp"
#include <iostream> 


void RubiksCube2x2::Cube2x2::clockwiseRotate(Layer2x2 x) {
    //    ur ul    |    lr ll    
    // ll tl tr rr | dl bl tl ur 
    // lr bl br rl | dr br tr ul 
    //    dl dr    |    rl rr    
    
    vector<Color> prev(cube);
    
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
}

void RubiksCube2x2::Cube2x2::counterClockwiseRotate(Layer2x2 x) {
    //    ur ul    |    rr rl    
    // ll tl tr rr | ul tr br dr 
    // lr bl br rl | ur tl bl dl 
    //    dl dr    |    ll lr    
    
    vector<Color> prev(cube);
    
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
}

void RubiksCube2x2::Cube2x2::print() {
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
}
