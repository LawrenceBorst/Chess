#ifndef __TREE_H_INCLUDED__
#define __TREE_H_INCLUDED__

#include "Node.h"
#include <queue>
#include <algorithm>
#include <math.h>

class Tree {
  public:
  Tree(Board, int);
  ~Tree();
  Node *root;
  int player;
  void print_level_order();
  int minimax(Node*, int, int, int, bool);
  int search_depth;
  int height;
  Board get_best_move();
  void add_leaves();

  private:
  void destroy_tree(Node*);
};

#endif