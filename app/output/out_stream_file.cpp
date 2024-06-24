#include "out_stream_file.hpp"

#include <filesystem>  // C++17 filesystem library
#include <iostream>

namespace fs = std::filesystem;

OutputFile::OutputFile() {
  try {
    std::string filename = "output_" + TraceFormatter::GetTimestamp() + ".log";
    OpenFile(filename);
  } catch (const std::exception& e) {
    std::cerr << "Error opening file: " << e.what() << std::endl;
    // Optionally re-throw the exception if necessary
    throw;
  }
}

OutputFile::~OutputFile() { CloseFile(); }

void OutputFile::OpenFile(const std::string& filename) {
  fs::path filePath = fs::current_path() / filename;
  file_.open(filePath);
  if (!file_.is_open()) {
    throw std::runtime_error("Failed to open file: " + filePath.string());
  }
}

void OutputFile::CloseFile() {
  if (file_.is_open()) {
    file_.close();
  }
}

void OutputFile::Write(const std::string& data) {
  std::lock_guard<std::mutex> lock(mutex_);
  file_ << data << std::endl;
}