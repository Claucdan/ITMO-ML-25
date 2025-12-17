#pragma once

#include "include/constants.h"
#include "include/figure.h"

namespace tetris {

class grid_t {
public:
  grid_t() = default;
  grid_t(const grid_t& other) = default;
  grid_t(grid_t&& other) noexcept = default;

  grid_t& operator=(const grid_t& other) = default;
  grid_t& operator=(grid_t&& other) noexcept = default;

  ~grid_t() = default;

  uint8_t erase_line() noexcept;
  bool gravity(uint16_t n) noexcept;
  bool move_figure(bool to_left) noexcept;
  bool rotate_figure(bool clockwise) noexcept;

  void set_figure(figure_t other) noexcept {
    figure_ = other;
  }

private:
  void merge_figure() noexcept;

  [[nodiscard]] bool intersects(int8_t dx = 0, int8_t dy = 0) const noexcept;

  figure_t figure_;
  uint16_t matrix_[GRID_HEIGHT]{0};
};

} // namespace tetris
