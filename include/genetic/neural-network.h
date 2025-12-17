#pragma once

#include <vector>
#include <string>
#include <cstdint>

namespace ml {

class neural_network_t {
public:
  neural_network_t();
  neural_network_t(const neural_network_t& other) = delete;
  neural_network_t(neural_network_t&& other) noexcept = default;

  neural_network_t(const std::string& filename) {
    load(filename);
  }

  neural_network_t& operator=(const neural_network_t& other) = delete;
  neural_network_t& operator=(neural_network_t&& other) noexcept = default;

  ~neural_network_t() = default;

  [[nodiscard]] float relu(float node) noexcept {
    return node > 0.0 ? node : 0.0f;
  }

  [[nodiscard]] float forward(std::vector<uint64_t> inputs) noexcept;

  void load(const std::string& filename);
  void save(const std::string& filename, uint64_t score);

private:
  float bias_2_;
  std::vector<float> layer_2_;
  std::vector<float> biases_1_;
  std::vector<std::vector<float>> layer_1_;
};

} // namespace ml
