#include "Tree.h"

Tree::Tree(Board b, int p) {
  this->root = new Node(b);
  this->root->depth = 0;
  this->height = 0;
  this->player = p; // 1 for white, 0 for black
}

Tree::~Tree() {
  this->destroy_tree(this->root);
}

void Tree::destroy_tree(Node *node) {
  if (not node->children.empty()) {
    for (Node* child : node->children) {
      this->destroy_tree(child);
      return;
    }
    delete node;
  }
}

/* Uses level-order traversal to add leaves*/
void Tree::add_leaves() {
  queue<Node*> q;
  q.push(this->root);

  while(q.empty() == false) {
    Node *node = q.front();
    if (node->depth == this->height) {
      node->add_children();
    } else if (node->depth > this->height) {
      this->height += 1;
      return;
    }
    q.pop();

    /* Enqueue children */
    for (Node *child : node->children) {
      q.push(child);
    }
  }
}

int Tree::minimax(Node *node, int depth, bool maximizing_player) {
  if (depth == 0) {
    return node->board.count_material();
  }
  if (maximizing_player) {
    int val = -10000;
    for (Node *child : node->children) {
      val = max(val, this->minimax(child, depth - 1, false));
    }
    return val;
  } else {
    int val = +10000;
    for (Node *child : node->children) {
      val = min(val, this->minimax(child, depth - 1, false));
    }
    return val;
  }
}

Board Tree::get_best_move() {
  int depth = 3;
  for (int i = 0; i < depth; i++) {
    this->add_leaves();
  }
  Node *best_move = NULL;
  int score = -10000;
  for (Node *child : this->root->children) {
    int minimax = this->minimax(child, depth - 1, true);
    if (minimax > score) {
      best_move = child;
      score = minimax;
    }
  }
  return best_move->board;
}
