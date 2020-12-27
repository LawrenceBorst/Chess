#include "Piece.h"

Piece::Piece(array<int, 2> pos, int index) {
  this->index = index;
  this->pos[0] = pos[0];
  this->pos[1] = pos[1];
}

int Piece::sign(int x) {
  if (x > 0) {
    return 1;
  } else if (x < 0) {
    return -1;
  } else {
    return 0;
  }
}

bool Piece::jump_allowed(array<int, 2> start, array<int, 2> dest, int index) {
  int y1 = start[0];
  int x1 = start[1];
  int y2 = dest[0];
  int x2 = dest[1];
  if ((x2 > 8) || (x2 < 0) || (y2 > 8) || (y2 < 0)) {
    return false;
  }

  switch(index) {
    // White pawn
    case 1: {
      if ((y2 - 1 == y1) && (x2 == x1)) {
        return true;
      } else if ((y1 == 1) && (x2 == x1) && (y2 == 3)) {
        return true;
      } else {
        return false;
      }
      break;
    }
    // Black pawn
    case -1: {
      if ((y2 + 1 == y1) && (x2 == x1)) {
        return true;
      } else if ((y1 == 6) && (x2 == x1) && (y2 == 4)) {
        return true;
      } else {
        return false;
      }
      break;
    }
    // Knights
    case 2:
    case -2: {
      return (abs(distance2(start, dest) - 5) < 0.01 ? true : false);
      break;
    }
    // Bishops
    case 3:
    case -3: {
     return (abs(y1 - y2) == abs(x1 - x2) ? true : false);
     break;
    }
    // Rooks
    case 4:
    case -4: {
      return ((y1 == y2) || (x1 == x2) ? true: false);
      break;
    }
    // Queens
    case 5:
    case -5: {
      return ((y1 == y2) || (x1 == x2) || (abs(y2 - y1) == abs(x2 - x1)) ? true: false);
      break;
    }
    case 6:
    case -6: {
      return (distance2(start, dest) < 2.01 ? true : false);
      break;
    }
    default: {
      return false;
    }
  }
}

float Piece::distance2(array<int, 2> a, array<int, 2> b) {
  int diff1 = a[0] - b[0];
  int diff2 = a[1] - b[1];
  float distance2 = diff1 * diff1 + diff2 * diff2;
  return distance2;
}