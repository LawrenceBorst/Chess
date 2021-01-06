#include "Tree.h"

Tree::Tree(Board b, int p) {
  this->root = new Node(b);
  this->root->depth = 0;
  this->height = 0;
  this->player = p; // 1 for white, 0 for black
  this->search_depth = 2;
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

/* Uses level-order traversal to add leaves
This will add another layer to the tree
*/
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

void Tree::print_level_order() {
  queue<Node*> q;
  q.push(root);

  while(q.empty() == false) {
    Node *node = q.front();
    wcout << node->board.print_board() << endl;
    wcout << node->score << endl;
    q.pop();

    /* Enqueue children */
    for (Node *child : node->children) {
      q.push(child);
    }
  }
}

/* Gives a minimax score a given move*/
int Tree::minimax(Node *node, int depth, int alpha, int beta, bool maximizing_player) {
  if (depth == 0 || node->children.empty()) {
    return node->board.count_material();
  } else {
    node->add_children();
  }

  if (maximizing_player) {
    int max_val = -INFINITY;
    for (Node *child : node->children) {
      int val = this->minimax(child, depth - 1, alpha, beta, false);
      max_val = max(max_val, val);
      alpha = max(alpha, val);
      if (beta <= alpha) {
        break;
      }
      return max_val;
    }
  } else {
    int min_val = +INFINITY;
    for (Node *child : node->children) {
      int val = this->minimax(child, depth - 1, alpha, beta, true);
      min_val = min(min_val, val);
      beta = min(beta, val);
      if (alpha <= beta) {
        break;
      }
    }
    return min_val;
  }
}

/* Returns the best next move*/
Board Tree::get_best_move() {
  this->add_leaves();
  
  Node *best_move = NULL;
  int score = -INFINITY;
  for (Node *child : this->root->children) {
    int minimax = this->minimax(child, this->search_depth - 1, -INFINITY, +INFINITY, true);
    if (minimax > score) {
      best_move = child;
      score = minimax;
    }
  }
  return best_move->board;
}
