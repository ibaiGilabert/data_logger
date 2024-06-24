#ifndef COMMON_HPP
#define COMMON_HPP
#include <optional>
#include <random>

// Define a common struct for data exchange
struct SensorData {
  std::optional<float> temp;
  std::optional<int> heart_rate;
  std::optional<int> oxygen_saturation;
};

#endif  // COMMON_HPP
