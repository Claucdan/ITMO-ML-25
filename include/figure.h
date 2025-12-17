#pragma once

#include "include/constants.h"

#include <cstdint>

namespace tetris {

class figure_t {
public:
  figure_t() noexcept = default;
  figure_t(const figure_t& other) = default;
  figure_t(figure_t&& other) noexcept = default;

  figure_t(figure_type type, rotation_type rotation, uint8_t x, uint8_t y) noexcept
      : type_(type), rotation_(rotation), position_x_(x), position_y_(y) {}

  ~figure_t() = default;

  figure_t& operator=(const figure_t& other) = default;
  figure_t& operator=(figure_t&& other) noexcept = default;

  void set_x(uint8_t x) noexcept {
    position_x_ = x;
  }

  void set_y(uint8_t y) noexcept {
    position_y_ = y;
  }

  [[nodiscard]] uint8_t x() const noexcept {
    return position_x_;
  }

  [[nodiscard]] uint8_t y() const noexcept {
    return position_y_;
  }

  [[nodiscard]] bool fixed() const noexcept {
    return fixed_;
  }

  [[nodiscard]] uint16_t shape() const noexcept {
    return TETROMINOS[type_][rotation_];
  }

  void rotation(bool clockwise) noexcept {
    rotation_ = (rotation_ + (clockwise ? 3 : 1)) % ROTATION_COUNT;
  }

private:
  uint8_t type_       : 4;
  uint8_t rotation_   : 4;

  uint8_t position_x_ : 4;
  uint8_t position_y_ : 5;
  uint8_t fixed_      : 1;
  uint8_t             : 2;
};

} // namespace tetris
