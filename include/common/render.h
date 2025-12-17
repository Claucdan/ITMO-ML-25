#pragma once

#include <ostream>
#include "include/grid.h"
#include "include/figure.h"

namespace common {

void render(std::ostream& os, const tetris::grid_t& grid) {
  uint16_t buffer[tetris::GRID_HEIGHT]{};
  for (int y = 0; y < tetris::GRID_HEIGHT; ++y)
    buffer[y] = grid.matrix_[y];

  os << "\033[2J\033[H";
  os << "+";
  for (int i = 0; i < tetris::GRID_WIGHT; ++i)
    os << "-";
  os << "+\n";
  for (int y = 0; y < tetris::GRID_HEIGHT; ++y) {
    os << "|";
    for (int x = 0; x < tetris::GRID_WIGHT; ++x) {
      bool filled = buffer[y] & (1 << x);
      os << (filled ? "#" : ".");
    }
    os << "|\n";
  }
  os << "+";
  for (int i = 0; i < tetris::GRID_WIGHT; ++i)
    os << "-";
  os << "+\n";
  os.flush();
}

} // namespace common
