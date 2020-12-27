#ifndef __PIECE_H_INCLUDED__
#define __PIECE_H_INCLUDED__

#include <array>
#include <iostream>
using namespace std;

class Piece {
  public:
    Piece(array<int, 2>, int);
    array<int, 2> pos;
    int index;
    static bool jump_allowed(array<int, 2>, array<int, 2>, int);
    static int sign(int);
  private:
    static float distance2(array<int, 2>, array<int, 2>);
};

#endif