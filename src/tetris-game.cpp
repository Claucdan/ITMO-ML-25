#include "include/tetris-game.h"

namespace tetris {

tetris_game_t::tetris_game_t(uint32_t seed)
    : figures_(seed) {
  grid_.set_figure(figures_.current());
}

void tetris_game_t::spawn_new_figure() {
  figures_.spawn();
  grid_.set_figure(figures_.current());

  if (!grid_.gravity(0)) {
    game_over_ = true;
  }
}

void tetris_game_t::lock_and_continue() {
  grid_.erase_line();
  spawn_new_figure();
}

void tetris_game_t::tick() {
  if (game_over_)
    return;

  if (!grid_.gravity(1)) {
    lock_and_continue();
  }
}

void tetris_game_t::move_left() noexcept {
  if (!game_over_)
    grid_.move_figure(true);
}

void tetris_game_t::move_right() noexcept {
  if (!game_over_)
    grid_.move_figure(false);
}

void tetris_game_t::rotate(bool clockwise) noexcept {
  if (!game_over_)
    grid_.rotate_figure(clockwise);
}

void tetris_game_t::soft_drop() noexcept {
  if (game_over_)
    return;

  if (!grid_.gravity(1)) {
    lock_and_continue();
  }
}

void tetris_game_t::hard_drop() noexcept {
  if (game_over_)
    return;

  while (grid_.gravity(1)) {
  }

  lock_and_continue();
}

} // namespace tetris
