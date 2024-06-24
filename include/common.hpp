#ifndef COMMON_HPP
#define COMMON_HPP
#include <optional>
#include <random>

// Define a common struct for data exchange
struct SensorData {
  std::optional<float> temp;
  std::optional<int> heartRate;
  std::optional<int> oxygenSaturation;
};

#endif  // COMMON_HPP
