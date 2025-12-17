#pragma once

#include "include/genetic/neural-network.h"
#include "include/grid.h"
#include <cstdint>
#include <string>

namespace ml {

class brain_t {
public:
  brain_t() = default;
  brain_t(const brain_t& other) = delete;
  brain_t(brain_t&& other) = delete;

  explicit brain_t(neural_network_t params)
      : params_(std::move(params)) {};

  brain_t& operator=(const brain_t& other) = delete;
  brain_t& operator=(brain_t&& other) = delete;

  ~brain_t() = default;

  brain_t cross(brain_t partner);
  std::string best_move(tetris::grid_t grid) noexcept;

  uint16_t get_holes(const tetris::grid_t& grid) noexcept;
  uint16_t get_bumpiness(const tetris::grid_t& grid) noexcept;
  uint16_t get_completed_lines(const tetris::grid_t& grid) noexcept;
  uint16_t get_aggregate_height(const tetris::grid_t& grid) noexcept;

private:
  std::vector<uint8_t> get_columns_heights(const tetris::grid_t& grid);

  uint64_t score_;
  neural_network_t params_;
};

} // namespace ml
