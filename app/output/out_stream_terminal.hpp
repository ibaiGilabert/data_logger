#ifndef OUT_STREAM_TERMINAL_H_
#define OUT_STREAM_TERMINAL_H_

#include <mutex>
#include <string>

#include "out_stream.hpp"

class OutputTerminal : public Output {
 public:
  /**
   * @brief Writes data to the terminal.
   *
   * The Write function locks a mutex to ensure thread safety and then writes
   * the provided data to the standard output (terminal).
   *
   * @param data The data to be written to the terminal.
   */
  void Write(const std::string& data) override;

 private:
  std::mutex mutex_;  // Mutex for thread safety
};

#endif  // OUT_STREAM_TERMINAL_H_