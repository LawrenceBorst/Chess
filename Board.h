#ifndef __BOARD_H_INCLUDED__
#define __BOARD_H_INCLUDED__

#include <map>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Piece.h"
using namespace std;

class Board {
  public:
    Board();
    Board(const Board&);
    void move(array<int, 2>, array<int, 2>);
    bool is_move_allowed(array<int, 2>, array<int, 2>);
    bool is_move_allowed(Piece, array<int, 2>);
    vector<Piece> pieces;
    wstring print_board();
    array<int, 2> en_passant_loc;
    bool in_check(array<int, 2>, int);
    bool in_check(int);
    bool player;
    int count_material();

  private:
    void change_player();
    bool castled_allowed_white;
    bool castled_allowed_black;
    bool has_castled_white;
    bool has_castled_black;
    int board[8][8];
    void make_move(array<int, 2>, array<int, 2>);
    void load_board();
    void empty_board();
    void prepare_pieces();
    static bool jump_allowed(array<int, 2>, array<int, 2> dest, int);
    static map<int, wstring> to_char;
    static vector<array<int, 2>> get_path(array<int, 2>, array<int, 2>);
    bool path_free(array<int, 2>, array<int, 2>);
    bool en_passant(array<int, 2>, array<int, 2>, int);
    bool pawn_collision(array<int, 2>);
    bool same_team(array<int, 2>, int);
    bool pawn_capture(array<int, 2>, array<int, 2>, int);
    bool castle_allowed(array<int, 2>, array<int, 2>, int);
};

extern int const KING_ARR[8][8];
extern int const QUEEN_ARR[8][8];
extern int const ROOK_ARR[8][8];
extern int const BISHOP_ARR[8][8];
extern int const KNIGHT_ARR[8][8];
extern int const PAWN_ARR[8][8];

#endif