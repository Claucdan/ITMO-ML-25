#pragma once

#include "include/genetic/brain.h"

#include <cstdint>

namespace ml {

class genetic_algorithm_t {
public:
  genetic_algorithm_t() = default;
  genetic_algorithm_t(const genetic_algorithm_t& other) = delete;
  genetic_algorithm_t(genetic_algorithm_t&& other) = delete;

  genetic_algorithm_t& operator=(const genetic_algorithm_t& other) = delete;
  genetic_algorithm_t& operator=(genetic_algorithm_t&& other) = delete;

  ~genetic_algorithm_t() = default;

  void fit() noexcept;

  [[nodiscard]] brain_t game() noexcept;

private:
  uint8_t gen_;
  uint64_t best_recorded_fitness_;
};

} // namespace ml
