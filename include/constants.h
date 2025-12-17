#pragma once

#include <cstdint>
#include <sys/types.h>

namespace tetris {

enum figure_type : uint8_t {
  O_SHAPE,
  I_SHAPE,
  Z_SHAPE,
  S_SHAPE,
  L_SHAPE,
  J_SHAPE,
  T_SHAPE,
  SHAPE_COUNT
};

enum rotation_type : uint8_t {
  UP,
  DOWN,
  LEFT,
  RIGHT,
  ROTATION_COUNT
};

inline constexpr uint16_t TETROMINOS[SHAPE_COUNT][ROTATION_COUNT] = {{0x0660, 0x0660, 0x0660, 0x0660},
                                                                     {0x0F00, 0x2222, 0x00F0, 0x4444},
                                                                     {0x0C60, 0x2640, 0x0C60, 0x2640},
                                                                     {0x06C0, 0x4620, 0x06C0, 0x4620},
                                                                     {0x02E0, 0x4460, 0x0E80, 0xC440},
                                                                     {0x08E0, 0x6440, 0x0E20, 0x44C0},
                                                                     {0x04E0, 0x4640, 0x0E40, 0x4C40}};

inline constexpr uint8_t GRID_WIGHT = 10;
inline constexpr uint8_t GRID_HEIGHT = 20;

inline constexpr uint8_t FILLED_LINE = (1U << GRID_WIGHT) - 1;

} // namespace tetris
