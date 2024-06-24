#include "out_stream_terminal.hpp"

#include <iostream>

void OutputTerminal::Write(const std::string& data) {
  std::lock_guard<std::mutex> lock(mutex_);
  std::cout << data << std::endl;
}
