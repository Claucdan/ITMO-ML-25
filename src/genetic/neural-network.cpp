#include "include/genetic/neural-network.h"

#include "include/genetic/constants.h"

#include <random>
#include <cstdint>
#include <fstream>
#include <stdexcept>

namespace {

std::random_device g_rd2;
std::uniform_int_distribution<uint64_t> g_d2(std::numeric_limits<uint64_t>::min(),
                                             std::numeric_limits<uint64_t>::max());

float random_f() noexcept {
  return ((g_d2(g_rd2) % 2) * 2 - 1) * static_cast<float>(g_d2(g_rd2)) / std::numeric_limits<uint64_t>::max();
}

} // namespace

namespace ml {
neural_network_t::neural_network_t() {
  layer_1_.reserve(LAYER1_NEURONS);
  biases_1_.reserve(LAYER1_NEURONS);

  for (size_t i = 0; i < LAYER1_NEURONS; ++i) {
    std::vector<float> weights;
    weights.reserve(LAYER1_INPUTS);
    for (size_t j = 0; j < LAYER1_INPUTS; ++j) {
      weights.emplace_back(random_f());
    }
    layer_1_.emplace_back(std::move(weights));
    biases_1_.emplace_back(random_f());
  }

  constexpr size_t LAYER2_NEURONS = 3;
  layer_2_.reserve(LAYER2_NEURONS);
  for (size_t i = 0; i < LAYER2_NEURONS; ++i) {
    layer_2_.emplace_back(random_f());
  }

  bias_2_ = random_f();
}

float neural_network_t::forward(std::vector<uint64_t> inputs) noexcept {
  float tmp, out = 0.0;

  for (int i = 0; i < LAYER1_NEURONS; i++) {
    tmp = 0.0;
    for (int j = 0; j < LAYER1_INPUTS; j++) {
      tmp += inputs[j] * layer_1_[i][j];
    }

    out += relu(tmp + biases_1_[i]) * layer_2_[i];
  }

  return out + bias_2_;
}

void neural_network_t::save(const std::string& filename, uint64_t score) {
  std::ofstream file(filename);

  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file: " + filename);
  }

  for (size_t i = 0; i < layer_1_.size(); ++i) {
    for (const auto& j : layer_1_[i]) {
      file << j << '\n';
    }
    file << biases_1_[i] << '\n';
  }

  for (const auto& i : layer_2_) {
    file << i << '\n';
  }

  file << bias_2_ << '\n';
  file << score << '\n';
}

void neural_network_t::load(const std::string& filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    throw std::runtime_error("Cannot open file: " + filename);
  }

  layer_1_.clear();
  biases_1_.clear();
  layer_2_.clear();

  std::string line;
  for (int i = 0; i < LAYER1_NEURONS; ++i) {
    std::vector<float> neuron_weights;
    neuron_weights.reserve(LAYER1_INPUTS);

    for (int j = 0; j < 4; ++j) {
      if (!std::getline(file, line)) {
        throw std::runtime_error("Unexpected end of file while reading weights");
      }
      neuron_weights.push_back(std::stof(line));
    }
    layer_1_.push_back(std::move(neuron_weights));
    if (!std::getline(file, line)) {
      throw std::runtime_error("Unexpected end of file while reading bias");
    }
    biases_1_.push_back(std::stof(line));
  }
  for (int i = 0; i < LAYER1_NEURONS; ++i) {
    if (!std::getline(file, line)) {
      throw std::runtime_error("Unexpected end of file while reading layer2");
    }
    layer_2_.push_back(std::stof(line));
  }
  if (!std::getline(file, line)) {
    throw std::runtime_error("Unexpected end of file while reading bias2");
  }
  bias_2_ = std::stof(line);
}

} // namespace ml
