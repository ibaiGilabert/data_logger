#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <optional>
#include <random>

/**
 * @brief Struct for storing sensor data.
 *
 * The SensorData struct encapsulates optional values for temperature, heart
 * rate, and oxygen saturation.
 */
struct SensorData {
  std::optional<float> temp;            /**< Optional temperature value */
  std::optional<int> heart_rate;        /**< Optional heart rate value */
  std::optional<int> oxygen_saturation; /**< Optional oxygen saturation value */
};

/**
 * @brief Overloaded output stream operator for SensorData.
 *
 * This operator<< function allows SensorData objects to be printed to an output
 * stream, showing the values of temperature, heart rate, and oxygen saturation
 * if they are present.
 *
 * @param os The output stream to write to.
 * @param data The SensorData object to output.
 * @return The modified output stream.
 */
inline std::ostream& operator<<(std::ostream& os, const SensorData& data) {
  os << "SensorData {";
  if (data.temp.has_value()) {
    os << " temp: " << data.temp.value() << ";";
  }
  if (data.heart_rate.has_value()) {
    os << " heart_rate: " << data.heart_rate.value() << ";";
  }
  if (data.oxygen_saturation.has_value()) {
    os << " oxygen_saturation: " << data.oxygen_saturation.value() << ";";
  }
  os << " }";
  return os;
}

#endif  // COMMON_HPP
