#pragma once

#include "include/grid.h"
#include "include/figure-manager.h"

namespace tetris {

class tetris_game_t {
public:
  tetris_game_t(const tetris_game_t& other) = delete;
  tetris_game_t(tetris_game_t&& other) = delete;

  explicit tetris_game_t(uint32_t seed = std::random_device{}());

  tetris_game_t& operator=(const tetris_game_t& other) = delete;
  tetris_game_t& operator=(tetris_game_t&& other) = delete;

  ~tetris_game_t() = default;

  void tick();

  void soft_drop() noexcept;
  void hard_drop() noexcept;
  void move_left() noexcept;
  void move_right() noexcept;
  void rotate(bool clockwise) noexcept;

  [[nodiscard]] bool game_over() const noexcept {
    return game_over_;
  }

  [[nodiscard]] const grid_t& grid() const noexcept {
    return grid_;
  }

  [[nodiscard]] const figure_t& current() const noexcept {
    return figures_.current();
  }

  [[nodiscard]] const figure_t& next() const noexcept {

    return figures_.next();
  }

private:
  void spawn_new_figure();
  void lock_and_continue();

  grid_t grid_;
  figure_manager_t figures_;
  bool game_over_{false};
};

} // namespace tetris
