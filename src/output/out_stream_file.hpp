#ifndef OUT_STREAM_FILE_H_
#define OUT_STREAM_FILE_H_

#include <fstream>
#include <mutex>
#include <string>

#include "out_stream.hpp"

class OutputFile : public Output {
 public:
  /**
   * @brief Constructs an OutputFile object and opens an output file.
   *
   * The constructor generates a filename based on the current timestamp
   * and attempts to open the file for writing.
   */
  OutputFile();

  /**
   * @brief Closes the output file.
   *
   * The destructor ensures that the file is properly closed when the OutputFile
   * object is destroyed.
   */
  ~OutputFile() override;

  /**
   * @brief Writes data to the output file.
   *
   * @param data The data to write to the output file.
   */
  void Write(const std::string& data) override;

 private:
  /**
   * @brief Opens the specified output file.
   *
   * @param filename The name of the file to open.
   * @throws std::runtime_error if the file cannot be opened.
   */
  void OpenFile(const std::string& filename);

  /**
   * @brief Closes the currently open output file.
   */
  void CloseFile();

 private:
  std::mutex mutex_;  // Mutex for thread safety
  std::ofstream file_;
};

#endif  // OUT_STREAM_FILE_H_