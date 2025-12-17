#pragma once

#include "include/figure.h"
#include "include/constants.h"

#include <random>

namespace tetris {

class figure_manager_t {
public:
  figure_manager_t() = delete;
  figure_manager_t(const figure_manager_t& other) = delete;
  figure_manager_t(figure_manager_t&& other) noexcept = default;

  explicit figure_manager_t(uint32_t seed = std::random_device{}())
      : rng_(seed) {
    refill_bag();
    current_ = figure_t(draw_from_bag(), UP, 3, 0);
    next_ = figure_t(draw_from_bag(), UP, 3, 0);
  }

  figure_manager_t& operator=(const figure_manager_t& other) = delete;
  figure_manager_t& operator=(figure_manager_t&& other) noexcept = default;

  ~figure_manager_t() = default;

  [[nodiscard]] const figure_t& current() const noexcept {
    return current_;
  }

  [[nodiscard]] const figure_t& next() const noexcept {
    return next_;
  }

  void spawn() noexcept {
    current_ = next_;
    next_ = figure_t(draw_from_bag(), UP, 3, 0);
  }

private:
  void refill_bag() noexcept;
  figure_type draw_from_bag() noexcept;

  figure_t next_;
  figure_t current_;
  std::mt19937 rng_;
  std::vector<figure_type> bag_;
};

} // namespace tetris
