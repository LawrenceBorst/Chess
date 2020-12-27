#include <iostream>
#include "Board.h"
#include "AI/Tree.h"

int main() {
  Board board;

  Tree computer(board);
  computer.add_leaves();
  computer.add_leaves();
  computer.add_leaves();
  //computer.print_level_order();
  wcout << computer.get_best_move()->board.print_board() << endl;

  computer.~Tree();
  //computer.add_leaves();

  /*board.move({1, 3}, {3, 3});
  wcout << board.print_board() << endl;
  
  board.move({6, 4}, {5, 4});
  wcout << board.print_board() << endl;

  board.move({1, 2}, {3, 2});
  wcout << board.print_board() << endl;

  board.move({6, 5}, {4, 5});
  wcout << board.print_board() << endl;

  board.move({0, 1}, {2, 2});
  wcout << board.print_board() << endl;

  board.move({7, 6}, {5, 5});
  wcout << board.print_board() << endl;

  board.move({0, 6}, {2, 5});
  wcout << board.print_board() << endl;

  board.move({6, 1}, {5, 1});
  wcout << board.print_board() << endl;
  
  board.move({1, 4}, {2, 4});
  wcout << board.print_board() << endl;

  board.move({7, 2}, {6, 1});
  wcout << board.print_board() << endl;

  board.move({0, 5}, {2, 3});
  wcout << board.print_board() << endl;

  board.move({7, 5}, {3, 1});
  wcout << board.print_board() << endl;

  board.move({0, 2}, {1, 3});
  wcout << board.print_board() << endl;

  board.move({3, 1}, {2, 2});
  wcout << board.print_board() << endl;

  board.move({1, 3}, {2, 2});
  wcout << board.print_board() << endl;

  board.move({6, 3}, {4, 3});
  wcout << board.print_board() << endl;

  board.move({0, 4}, {0, 6});
  wcout << board.print_board() << endl;

  board.move({7, 4}, {7, 6});
  wcout << board.print_board() << endl;

  board.move({0, 0}, {0, 2});
  wcout << board.print_board() << endl;

  board.move({7, 1}, {6, 3});
  wcout << board.print_board() << endl;

  board.move({1, 1}, {2, 1});
  wcout << board.print_board() << endl;

  board.move({5, 5}, {3, 4});
  wcout << board.print_board() << endl;

  board.move({2, 2}, {1, 1});
  wcout << board.print_board() << endl;

  board.move({7, 5}, {5, 5});
  wcout << board.print_board() << endl;

  board.move({3, 2}, {4, 3});
  wcout << board.print_board() << endl;

  board.move({6, 1}, {4, 3});
  wcout << board.print_board() << endl;

  board.move({2, 3}, {3, 2});
  wcout << board.print_board() << endl;

  board.move({6, 2}, {5, 2});
  wcout << board.print_board() << endl;

  board.move({3, 2}, {4, 3});
  wcout << board.print_board() << endl;

  board.move({5, 2}, {4, 3});
  wcout << board.print_board() << endl;

  board.move({2, 5}, {1, 3});
  wcout << board.print_board() << endl;

  board.move({5, 5}, {5, 7});
  wcout << board.print_board() << endl;

  board.move({1, 3}, {3, 4});
  wcout << board.print_board() << endl;

  board.move({7, 3}, {3, 7});
  wcout << board.print_board() << endl;

  board.move({1, 7}, {2, 7});
  wcout << board.print_board() << endl;

  board.move({4, 5}, {3, 4});
  wcout << board.print_board() << endl;

  board.move({0, 3}, {3, 6});
  wcout << board.print_board() << endl;

  board.move({3, 7}, {6, 4});
  wcout << board.print_board() << endl;

  board.move({0, 2}, {2, 2});
  wcout << board.print_board() << endl;

  board.move({5, 7}, {5, 6});
  wcout << board.print_board() << endl;

  board.move({3, 6}, {1, 4});
  wcout << board.print_board() << endl;

  board.move({6, 4}, {3, 7});
  wcout << board.print_board() << endl;

  board.move({0, 5}, {0, 2});
  wcout << board.print_board() << endl;

  board.move({3, 7}, {2, 7});
  wcout << board.print_board() << endl;

  board.move({2, 2}, {7, 2});
  wcout << board.print_board() << endl;*/

  return 0;

}