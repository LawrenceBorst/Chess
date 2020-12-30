#include <iostream>
#include "Board.h"
#include "AI/Tree.h"
#include <regex>
#include <stdexcept>

array<int, 2> convert_algebraic(string);

int main() {
  Board board;

  wcout << "You're playing black!" << endl;
  string start, end;
  array<int, 2> s, e;

  // Game loop
  while (true) {
    wcout << "You moved. Current position:\n" << board.print_board() << endl;
    
    Tree computer(board, 0);
    board = computer.get_best_move();

    wcout << "Computer moved. Current position:\n" << board.print_board() << endl;
    do {
      wcout << "Make a move from [...] to [...]" << endl;
      do {
        wcout << "From (e.g. b2):" << endl;
        cin >> start;
      } while (not regex_match(start, regex("([a-h])([1-8])")));
      s = convert_algebraic(start);
      
      do {
        wcout << "To (e.g. c3):" << endl;
        cin >> end;
      } while (not regex_match(end, regex("([a-h])([1-8])")));
      e = convert_algebraic(end);
      
    } while (not board.is_move_allowed({s[0], s[1]}, {e[0], e[1]}));

    board.move(s, e);
  }




  return 0;
}

array<int, 2> convert_algebraic(string s) {
  int a = s[1] - '0';
  int b = (int)s[0];
  b -= 96;
  return {a - 1, b - 1};
}
