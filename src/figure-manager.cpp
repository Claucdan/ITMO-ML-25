#include "include/figure-manager.h"

#include <algorithm>

namespace tetris {

void figure_manager_t::refill_bag() noexcept {
  bag_.clear();
  bag_.reserve(SHAPE_COUNT);
  for (uint8_t i = 0; i < SHAPE_COUNT; ++i) {
    bag_.push_back(static_cast<figure_type>(i));
  }
  std::shuffle(bag_.begin(), bag_.end(), rng_);
}

figure_type figure_manager_t::draw_from_bag() noexcept {
  if (bag_.empty()) {
    refill_bag();
  }

  figure_type type = bag_.back();
  bag_.pop_back();
  return type;
}

} // namespace tetris
