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

/* Min max, picks a node, looks at children, finds the worst outcome*/
int Tree::minimax(Node* root) {
  vector<int> scores;
  queue<Node*> q;
  q.push(root);

  while(q.empty() == false) {
    Node *node = q.front();
    if (node->depth == this->height) {
      scores.push_back(node->score);
    }
    q.pop();

    /* Enqueue children */
    for (Node *child : node->children) {
      q.push(child);
    }
  }
  return *min_element(scores.begin(), scores.end());
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

Board Tree::get_best_move() {
  int depth = 3;
  for (int i = 0; i < depth; i++) {
    this->add_leaves();
  }
  // Look at the children of root
  // For each child, calculate the worst outcome
  // Pick the one with the highest worst outcome
  int minimax_outcome = -1000;
  Node* best_move;
  for (Node *child : this->root->children) {
    int score = this->minimax(child);
    if (score > minimax_outcome) {
      best_move = child;
      minimax_outcome = score;
    }
  }
  return best_move->board;
}
