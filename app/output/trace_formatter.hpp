#ifndef TRACE_H_
#define TRACE_H_

#include <chrono>
#include <iomanip>
#include <string>

/**
 * @brief Utility class for formatting trace messages.
 *
 * The TraceFormatter class provides static methods to format data with a
 * timestamp in the CEF (Common Event Format) style.
 */
class TraceFormatter {
 public:
  /**
   * @brief Formats the provided data with a timestamp in CEF (Common Event
   * Format) style.
   *
   * @tparam T The type of data to format.
   * @param data The data to be formatted.
   * @return A string containing the formatted trace message.
   */
  template <typename T>
  static std::string Format(const T& data) {
    std::string now = GetTimestamp();
    // Format timestamp as ISO 8601
    std::stringstream formatted;
    formatted << "CEF:0|" << now << "|NE|DataLogger|1.0|"
              << "DeviceVendor=Neuroelectrics " << "DeviceProduct=231X"
              << "DeviceVersion=1.0 " << "|" << data << "|";
    return formatted.str();
  }

  /**
   * @brief Retrieves the current timestamp formatted as ISO 8601.
   *
   * @return A string containing the current timestamp in ISO 8601 format (UTC).
   */
  static std::string GetTimestamp() {
    // Get current time as UTC
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);

    // Format timestamp as ISO 8601
    std::stringstream timestamp;
    timestamp << std::put_time(std::gmtime(&now_time), "%Y-%m-%dT%H:%M:%SZ");

    return timestamp.str();
  }
};

#endif  // TRACE_H_