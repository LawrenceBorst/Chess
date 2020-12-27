#include "Board.h"

/* map<int, wstring> Board::to_char {
  { -1, L"\u2659" }, { -2, L"\u2658" },
  { -3, L"\u2657" }, { -4, L"\u2656"},
  { -5, L"\u2655" }, {-6, L"\u2654" },
  {0, L" " },
  {1, L"\u265F" }, {2, L"\u265E" },
  {3, L"\u265D" }, {4, L"\u265C" },
  {5, L"\u265B"}, {6, L"\u265A" }
}; */

map<int, wstring> Board::to_char {
  { -1, L"-1" }, { -2, L"-2" },
  { -3, L"-3" }, { -4, L"-4"},
  { -5, L"-5" }, {-6, L"-6" },
  {0, L"  " },
  {1, L"+1" }, {2, L"+2" },
  {3, L"+3" }, {4, L"+4" },
  {5, L"+5"}, {6, L"+6" }
};

// Constructor
Board::Board() {
  this->castled_allowed_black = false;
  this->castled_allowed_white = false;
  this->has_castled_white = false;
  this->has_castled_black = false;
  this->player = true; // White
  this->en_passant_loc = {0, 0};
  this->prepare_pieces();
  this->load_board();
}

// Copy Constructor
Board::Board(const Board &b2) {
  this->castled_allowed_black = b2.castled_allowed_black;
  this->castled_allowed_white = b2.castled_allowed_white;
  this->has_castled_white = b2.has_castled_white;
  this->has_castled_black = b2.has_castled_black;
  this->player = b2.player; // White
  this->en_passant_loc = b2.en_passant_loc;
  this->pieces = b2.pieces;
  this->load_board();
}

/* Public */
void Board::empty_board() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      this->board[i][j] = 0;
    }
  }
}

void Board::prepare_pieces() {
  // pawns
  for (int i = 0; i < 8; i++) {
    this->pieces.push_back(Piece({1, i}, 1));
    this->pieces.push_back(Piece({6, i}, -1));
  }
  // knights
  this->pieces.push_back(Piece({0, 1}, 2));
  this->pieces.push_back(Piece({0, 6}, 2));
  this->pieces.push_back(Piece({7, 1}, -2));
  this->pieces.push_back(Piece({7, 6}, -2));
  // bishops
  this->pieces.push_back(Piece({0, 2}, 3));
  this->pieces.push_back(Piece({0, 5}, 3));
  this->pieces.push_back(Piece({7, 2}, -3));
  this->pieces.push_back(Piece({7, 5}, -3));
  // rooks
  this->pieces.push_back(Piece({0, 0}, 4));
  this->pieces.push_back(Piece({0, 7}, 4));
  this->pieces.push_back(Piece({7, 0}, -4));
  this->pieces.push_back(Piece({7, 7}, -4));
  // queens
  this->pieces.push_back(Piece({0, 3}, 5));
  this->pieces.push_back(Piece({7, 3}, -5));
  // kings
  this->pieces.push_back(Piece({0, 4}, 6));
  this->pieces.push_back(Piece({7, 4}, -6));
}

void Board::load_board() {
  this->empty_board();
  for (Piece p : this->pieces) {
    int i = p.pos[0];
    int j = p.pos[1];
    int index = p.index;
    this->board[i][j] = index;
  }
}

void Board::move(array<int, 2> start, array<int, 2> dest) {
  if (not this->is_move_allowed(start, dest)) {
    return;
  } else {
    this->make_move(start, dest);
    this->load_board();
    this->change_player();
  }
}

void Board::change_player() {
  this->player = not this->player;
}

void Board::make_move(array<int, 2> start, array<int, 2> dest) {
  Piece *p = NULL;
  // Remove element at the destination
  for (int i = 0; i < this->pieces.size(); i++) {
    if (this->pieces[i].pos == dest) {
      this->pieces.erase(this->pieces.begin()+i);
      i--;
    } else if (this->pieces[i].pos == start) {
      p = &this->pieces[i];
    }
  }
  // Move element at the start
  if (p) {
    p->pos = dest;
  }
  // Update en passant location
  if ((abs(p->index) == 1) && (abs(start[0] - dest[0]) == 2)) {
    switch (start[0]) {
      case 1: this->en_passant_loc = {2, dest[1]}; break;
      case 6: this->en_passant_loc = {5, dest[1]}; break;
    }
  } else {
    this->en_passant_loc = {0, 0};
  }
  // Pawn promotion (to queen)
  if ((abs(p->index) == 1) && (abs(2*dest[0] - 7) == 7)) {
    p->index *= 6;
  }
  // Change castled_white/black
  if (this->in_check(6) && (player == true)) {
    castled_allowed_white = true;
  } else if (this->in_check(6) && (player == false)) {
    castled_allowed_black = true;
  } else if (p->index == 6) {
    castled_allowed_white = true;
  } else if (p->index == -6) {
    castled_allowed_black = true;
  }
}

bool Board::is_move_allowed(array<int, 2> start, array<int, 2> dest) {
  // Select piece with start position
  for (Piece p : this->pieces) {
    if (start == p.pos) {
      return this->is_move_allowed(p, dest);
    }
  }
  return false;
}

bool Board::is_move_allowed(Piece p, array<int, 2> dest) {
  bool flag = true;
  array<int, 2> start = p.pos;
  int index = p.index;
  // Check if we're moving from the right team
  if ((index > 0) && (this->player == false)) {
    return false;
  } else if ((index < 0) && (this->player == true)) {
    return false;
  }
  // Check if not just going nowhere
  if (start == dest) {
    return false;
  }
  // Check if jump is allowed for this piece
  if (not Piece::jump_allowed(start, dest, index)) {
    flag = false;
  }

  // Check for pawn collisions and captures
  if (abs(index) == 1) {
    if (this->pawn_collision(dest)) {
      flag = false;
    }
    if (this->pawn_capture(start, dest, index)) {
      flag = true;
    }
  }
  // Check if any pieces are in the way
  if (not this->path_free(start, dest)) {
    flag = false;
  }

  // Check if we are not capturing from the same team
  if (this->same_team(dest, index)) {
    flag = false;
  }
  // En passant (should go at the end)
  if (this->en_passant(start, dest, index)) {
    flag = true;
  }
  if (this->castle_allowed(start, dest, index)) {
    flag = true;
    switch (index) {
      case 6: this->has_castled_white = true; break;
      case -6: this->has_castled_black = true; break;
    }
  }
  // Check if we are creating a discovered attack
  return flag;
}

wstring Board::print_board() {
  wstring str = L"";
  // Print the Board
  str += L"----------------\n";
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      str.append(this->to_char.find((this->board)[7-i][j])->second);
    }
    str += L"\n";
  }
  str += L"----------------\n";
  return str;
}

bool Board::path_free(array<int, 2> start, array<int, 2> dest) {
  vector<array<int, 2>> path = Board::get_path(start, dest);
  // If there are trivially no pieces in the way (small jump)
  if (path.empty()) {
    return true;
  }
  // Big jump, where the path is nonempty
  else {
    // If there is a piece in the way of the path
    for (Piece p : this->pieces) {
      for (array<int, 2> pos : path) {
        if (p.pos == pos) {
          return false;
        }
      }
    }
    return true;
  }
}

bool Board::pawn_capture(array<int, 2> start, array<int, 2> dest, int index) {
  // Check if destination is empty
  bool dest_empty = true;
  for (Piece p : this->pieces) {
    if (p.pos == dest) {
      dest_empty = false;
    }
  }
  if (dest_empty) {
    return false;
  }

  // Horizontal check
  if (abs(start[1] - dest[1]) != 1) {
    return false;
  }
  // Vertical check
  switch (index) {
    case 1: {
      return (start[0] - dest[0] == -1 ? true : false);
    }
    case -1: {
      return (start[0] - dest[0] == 1 ? true : false);
    }
  }
  return false;
}

bool Board::en_passant(array<int, 2> start, array<int, 2> dest, int index) {
  // Check if en passant is still allowed using placeholder loc {0, 0}
  if (this->en_passant_loc[0] == 0) {
    return false;
  }
  // Check if the destination is at the en passant
  if (dest != this->en_passant_loc) {
    return false;
  }
  // Horizontal check
  if (abs(start[1] - dest[1]) != 1) {
    return false;
  }
  // Vertical check
  switch (index) {
    case 1: {
      return (start[0] - dest[0] == -1 ? true : false);
    }
    case -1: {
      return (start[0] - dest[0] == 1 ? true : false);
    }
  }
  return false;
}

bool Board::pawn_collision(array<int, 2> dest) {
  /* At this stage in the tests in this->move_allowed(...) we've already tested
  for legal jumps and en passant. Long story short, we only need to check if the destination is not already taken. */
  for (Piece p : this->pieces) {
    if (p.pos == dest) {
      return true;
    }
  }
  return false;
}

bool Board::castle_allowed(array<int, 2> start, array<int, 2> dest, int index) {
  int x1 = start[1];
  int y1 = start[0];
  int x2 = dest[1];
  int y2 = dest[0];
  if (abs(index) != 6) {
    return false;
  }
  if ((this->castled_allowed_white) && (index == 6)) {
    return false;
  } else if ((this->castled_allowed_black) && index == -6) {
    return false;
  }
  if (not this->path_free(start, dest)) {
    return false;
  }
  if ((x1 == 4) && (y1 == 0) && (x2 == 2) && (y2 == 0)) {
    if (this->in_check({0, 3}, 6)) {
      return false;
    } else {
      this->make_move({0, 0}, {0, 3});
      this->castled_allowed_white = true;
      return true;
    }
  } else if ((x1 == 4) && (y1 == 0) && (x2 == 6) && (y2 == 0)) {
    if (this->in_check({0, 5}, 6)) {
      return false;
    } else {
      this->make_move({0, 7}, {0, 5});
      this->castled_allowed_white = true;
      return true;
    }
  } else if ((x1 == 4) && (y1 == 7) && (x2 == 2) && (y2 == 7)) {
    if (this->in_check({7, 3}, -6)) {
      return false;
    } else {
      this->make_move({7, 0}, {7, 3});
      this->castled_allowed_black = true;
      return true;
    }
  } else if ((x1 == 4) && (y1 == 7) && (x2 == 6) && (y2 == 7)) {
    if (this->in_check({7, 5}, -6)) {
      return false;
    } else {
      this->make_move({7, 7}, {7, 5});
      this->castled_allowed_black = true;
      return true;
    }
  }
  return false;
}

vector<array<int, 2>> Board::get_path(array<int, 2> start, array<int, 2> dest) {
  vector<array<int, 2>> path;
  int x1 = start[1];
  int y1 = start[0];
  int x2 = dest[1];
  int y2 = dest[0];

  // Horizontal
  if (y1 == y2) {
    int x = min(x1, x2) + 1;
    while (x < max(x1, x2)) {
      path.push_back({y1, x});
      x += 1;
    }
  }
  // Vertical
  else if (x1 == x2) {
    int y = min(y1, y2) + 1;
    while (y < max(y1, y2)) {
      path.push_back({y, x1});
      y += 1;
    }
  }
  // Diagonal
  else if (abs(y1 - y2) == abs(x1 - x2)) {
    int delta_x = (x2 - x1) / abs(x2 - x1);
    int delta_y = (y2 - y1) / abs(y2 - y1);
    int x = x1 + delta_x;
    int y = y1 + delta_y;
    // Repeat abs(x2 - x1) times
    for (int i = 0; i < abs(x2 - x1) - 1; i++) {
      path.push_back({y, x});
      x += delta_x;
      y += delta_y;
    }
  }
  return path;
}

bool Board::same_team(array<int, 2> dest, int index) {
  // Find the piece at dest, check if indices match signs
  for (Piece p : this->pieces) {
    if ((p.pos == dest) && (Piece::sign(index) == Piece::sign(p.index))) {
      return true;
    }
  }
  return false;
}

/* Looks for checks at a certain position. Takes index 6 or -6
Slightly more efficient than just calling is_move_allowed*/
bool Board::in_check(array<int, 2> pos, int index) {
  // Look for pieces that can attack the position
  if (index == 6) {
    for (Piece p : this->pieces) {
      if (p.index > 0) {
        continue; // Piece on the same team
      }
      if ((not Piece::jump_allowed(p.pos, pos, p.index)) && (abs(p.index) != 1)) {
        continue; // Piece not allowed to capture the king
        // Skip this test for pawns, as an exception
      }
      switch(p.index) {
        case -1: {
          if ((p.pos[0] == pos[0] + 1) && (abs(p.pos[1] - pos[1]) == 1)) {
            return true;
          }
          break;
        }
        case -2:
        case -3:
        case -4:
        case -5: {
          if (this->path_free(p.pos, pos)) {
            return true;
          }
          break;
        }
        case -6: {
          return true;
        }
      }
    }
  }
  // Look for pieces that can attack the black king
  if (index == -6) {
    for (Piece p : this->pieces) {
      if (p.index < 0) {
        continue; // Piece on the same team
      }
      if ((not Piece::jump_allowed(p.pos, pos, p.index)) && (abs(p.index) != 1)) {
        continue; // Piece not allowed to capture the king
        // Skip this test for pawns, as an exception
      }
      switch(p.index) {
        case 1: {
          if ((p.pos[0] == pos[0] - 1) && (abs(p.pos[1] - pos[1]) == 1)) {
            return true;
          }
          break;
        }
        case 2:
        case 3:
        case 4:
        case 5: {
          if (this->path_free(p.pos, pos)) {
            return true;
          }
          break;
        }
        case 6: {
          return true;
        }
      }
    }
  }
  return false;
}

/* Looks for checks generically, without position, only team. */
bool Board::in_check(int index) {
  Piece *king = NULL;
  // Get position of king
  for (Piece p : this->pieces) {
    if (p.index == index) {
      king = &p;
    }
  }
  if (not king) {
    return false;
  }
  return this->in_check(king->pos, king->index);
}

int Board::count_material() {
  int total = 0;
  for (Piece p: this->pieces) {
    int x = p.pos[1];
    int y = p.pos[0];
    switch (p.index) {
      case 1: {
        total += PAWN_ARR[7-y][x];
        break;
      }
      case 2: {
        total += KNIGHT_ARR[7-y][x];
        break;
      }
      case 3: {
        total += BISHOP_ARR[7-y][x];
        break;
      }
      case 4: {
        total += ROOK_ARR[7-y][x];
        break;
      }
      case 5: {
        total += QUEEN_ARR[7-y][x];
        break;
      }
      case 6: {
        total += KING_ARR[7-y][x];
        break;
      }
      case -1: {
        total -= PAWN_ARR[y][x];
        break;
      }
      case -2: {
        total -= KNIGHT_ARR[y][x];
        break;
      }
      case -3: {
        total -= BISHOP_ARR[y][x];
        break;
      }
      case -4: {
        total -= ROOK_ARR[y][x];
        break;
      }
      case -5: {
        total -= QUEEN_ARR[y][x];
        break;
      }
      case -6: {
        total -= KING_ARR[y][x];
        break;
      }
    }
  }

  if (this->has_castled_black) {
    //total -= 40;
  }
  if (this->has_castled_white) {
    //total += 40;
  }

  return total;
}
