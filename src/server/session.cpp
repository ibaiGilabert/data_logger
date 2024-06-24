#include "session.hpp"

#include <thread>

Session::Session(tcp::socket socket, std::shared_ptr<Dispatcher> dispatcher)
    : socket_(std::move(socket)), dispatcher_(dispatcher) {}

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
      socket_, asio::buffer(recv_buffer_),
      [this, self](std::error_code ec, std::size_t length) {
        if (!ec) {
          try {
            // std::cout << "Data read: " << length << " bytes." << std::endl;

            // Deserialize received data into SensorData struct
            SensorData received_data;
            std::memcpy(&received_data, recv_buffer_.data(),
                        sizeof(SensorData));

            // Check if dispatcher is defined
            if (!dispatcher_) {
              throw std::runtime_error("Dispatcher is not defined.");
            }

            // Notify the dispatcher to process the data
            dispatcher_->ProcessData(received_data);

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