#include "Node.h"

Node::Node(Board board) {
  this->board = board;
  this->score = board.count_material();
}

void Node::add_children() {
  for (Piece p : this->board.pieces) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (this->board.is_move_allowed(p.pos, {i, j})) {
          // Copy into child, move, and add to results
          Node* child_pointer = new Node(this->board);
          child_pointer->depth = this->depth + 1;
          child_pointer->board.move(p.pos, {i, j});
          child_pointer->score = child_pointer->board.count_material();
          this->children.push_back(child_pointer);
        }
      }
    }
  }
}
