#ifndef OUT_STREAM_H_
#define OUT_STREAM_H_
#include <string>

#include "trace_formatter.hpp"

/**
 * @brief Abstract base class for output streams.
 *
 * The Output class defines an interface for writing data to different output
 * streams.
 */
class Output {
 public:
  /**
   * @brief Virtual destructor for Output class.
   */
  virtual ~Output() = default;

  /**
   * @brief Writes data to the output stream.
   *
   * This pure virtual function must be implemented by derived classes
   * to write data to a specific output stream.
   *
   * @param data The data to be written to the output stream.
   */
  virtual void Write(const std::string& data) = 0;
};

#endif  // OUT_STREAM_H_