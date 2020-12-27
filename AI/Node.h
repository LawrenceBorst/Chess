#ifndef __NODE_H_INCLUDED__
#define __NODE_H_INCLUDED__

#include "../Board.h"

class Node {
  public:
  Node(Board);
  Board board;
  int score;
  int depth;
  vector<Node*> children;
  void add_children();
};

#endif