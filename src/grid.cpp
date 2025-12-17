#include "include/grid.h"

namespace tetris {

uint8_t grid_t::erase_line() noexcept {
  uint8_t erased = 0;

  for (int y = GRID_HEIGHT - 1; y >= 0; --y) {
    if ((matrix_[y] & FILLED_LINE) == FILLED_LINE) {
      ++erased;
      for (int ty = y; ty > 0; --ty)
        matrix_[ty] = matrix_[ty - 1];
      matrix_[0] = 0;
      ++y;
    }
  }

  return erased;
}

bool grid_t::gravity(uint16_t n) noexcept {
  while (n--) {
    if (intersects(0, 1)) {
      merge_figure();
      return false;
    }
    figure_.set_y(figure_.y() + 1);
  }
  return true;
}

bool grid_t::move_figure(bool to_left) noexcept {
  int8_t dx = to_left ? -1 : 1;

  if (intersects(dx, 0))
    return false;

  figure_.set_x(figure_.x() + dx);
  return true;
}

bool grid_t::rotate_figure(bool clockwise) noexcept {
  figure_t backup = figure_;
  figure_.rotation(clockwise);

  if (intersects()) {
    figure_ = backup;
    return false;
  }

  return true;
}

void grid_t::merge_figure() noexcept {
  const uint16_t shape = figure_.shape();

  for (uint8_t sy = 0; sy < 4; ++sy) {
    for (uint8_t sx = 0; sx < 4; ++sx) {
      if (!(shape & (1 << (15 - (sy * 4 + sx)))))
        continue;

      uint8_t x = figure_.x() + sx;
      uint8_t y = figure_.y() + sy;

      if (y < GRID_HEIGHT)
        matrix_[y] |= (1 << x);
    }
  }
}

bool grid_t::intersects(int8_t dx, int8_t dy) const noexcept {
  const uint16_t shape = figure_.shape();

  for (uint8_t sy = 0; sy < 4; ++sy) {
    for (uint8_t sx = 0; sx < 4; ++sx) {
      if (!(shape & (1 << (15 - (sy * 4 + sx)))))
        continue;

      int x = figure_.x() + sx + dx;
      int y = figure_.y() + sy + dy;

      if (x < 0 || x >= GRID_WIGHT || y >= GRID_HEIGHT)
        return true;

      if (y >= 0 && (matrix_[y] & (1 << x)))
        return true;
    }
  }

  return false;
}

} // namespace tetris
