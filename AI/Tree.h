#ifndef __TREE_H_INCLUDED__
#define __TREE_H_INCLUDED__

#include "Node.h"
#include <queue>
#include <algorithm>

class Tree {
  public:
  Tree(Board, int);
  ~Tree();
  Node *root;
  int player;
  int minimax(Node*, int, int, int, bool);
  int search_depth;
  int height;
  Board get_best_move();

  private:
  void add_leaves();
  void destroy_tree(Node*);
};

#endif