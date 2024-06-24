#include "session.hpp"

#include <thread>

Session::Session(tcp::socket socket) : socket_(std::move(socket)) {}

Session::~Session() {
  // Ensure resources are released upon destruction
  Close();
}

void Session::Close() {
  if (socket_.is_open()) {
    std::error_code ec;
    socket_.shutdown(tcp::socket::shutdown_both, ec);
    socket_.close();
    if (ec) {
      std::cerr << "Error closing socket: " << ec.message() << std::endl;
    }
  }
}

void Session::Start() {
  std::cout << "Starting session" << std::endl;
  ReadData();
}

void Session::ReadData() {
  auto self(shared_from_this());

  // Buffer to hold received data
  asio::async_read(
      socket_, asio::buffer(recvBuffer_),
      [this, self](std::error_code ec, std::size_t length) {
        if (!ec) {
          try {
            std::cout << "Data read: " << length << " bytes." << std::endl;

            // Deserialize received data into SensorData struct
            SensorData receivedData;
            std::memcpy(&receivedData, recvBuffer_.data(), sizeof(SensorData));

            // Print or log received data
            ProcessData(receivedData);

            // Continue reading data
            ReadData();
          } catch (const std::exception& e) {
            // Handle exceptions during data processing
            std::cerr << "Exception in readData: " << e.what() << std::endl;
            // Close socket on error
            Close();
          }
        } else {
          // Handle read errors
          std::cerr << "Read error: " << ec.message() << std::endl;
          // Close socket on error
          Close();
        }
      });
}

void Session::ProcessData(const SensorData& data) {
  // Print data
  std::cout << "Received Sensor Data:" << std::endl;
  if (data.temp.has_value()) {
    std::cout << "Temperature: " << data.temp.value() << "C" << std::endl;
  } else {
    std::cout << "Temperature: Not Available" << std::endl;
  }
  if (data.oxygenSaturation.has_value()) {
    std::cout << "Oxygen Saturation: " << data.oxygenSaturation.value() << "%"
              << std::endl;
  } else {
    std::cout << "Oxygen Saturation: Not Available" << std::endl;
  }
  if (data.heartRate.has_value()) {
    std::cout << "Heart Rate: " << data.heartRate.value() << " bpm"
              << std::endl;
  } else {
    std::cout << "Heart Rate: Not Available" << std::endl;
  }

  // Simulate process delay
  std::this_thread::sleep_for(kProcessDelay);
}
