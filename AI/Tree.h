#ifndef __TREE_H_INCLUDED__
#define __TREE_H_INCLUDED__

#include "Node.h"
#include <queue>

class Tree {
  public:
  Tree(Board);
  ~Tree();
  void destroy_tree(Node*);
  Node *root;
  int minimax(Node*);
  void add_leaves();
  int height;
  Node* get_best_move();
  void print_level_order();
};

#endif