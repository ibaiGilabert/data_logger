#include "client.hpp"

Client::Client(asio::io_context& context, const std::string& host,
               unsigned short port)
    : resolver_(context), socket_(context) {
  endpoints_ = resolver_.resolve(host, std::to_string(port));
}

Client::~Client() {
  // Ensure resources are released upon destruction
  CloseSocket();
}

void Client::CloseSocket() {
  if (socket_.is_open()) {
    asio::error_code ec;
    socket_.shutdown(asio::ip::tcp::socket::shutdown_both, ec);
    socket_.close(ec);
    if (ec) {
      std::cerr << "Error closing socket: " << ec.message() << std::endl;
    }
  }
}

void Client::Connect() {
  try {
    asio::connect(socket_, endpoints_);
    std::cout << "Connected to the server." << std::endl;

    // send random data
    while (true) {
      SendData();
      // Wait till to send next data
      std::this_thread::sleep_for(kSendRate);
    }

  } catch (const std::exception& e) {
    std::cerr << "Client connection exception: " << e.what() << std::endl;
    // Close resources in case of exception
    CloseSocket();
  }
}

void Client::SendData() {
  try {
    auto data = GenerateRandomData();

    // Print values for debug purposes
    std::cout << "Sensor Data:" << std::endl;
    if (data.temp.has_value()) {
      std::cout << "Temperature: " << data.temp.value() << "C" << std::endl;
    } else {
      std::cout << "Temperature: Not Available" << std::endl;
    }
    if (data.oxygen_saturation.has_value()) {
      std::cout << "Oxygen Saturation: " << data.oxygen_saturation.value()
                << "%" << std::endl;
    } else {
      std::cout << "Oxygen Saturation: Not Available" << std::endl;
    }
    if (data.heart_rate.has_value()) {
      std::cout << "Heart Rate: " << data.heart_rate.value() << "bpm"
                << std::endl;
    } else {
      std::cout << "Heart Rate: Not Available" << std::endl;
    }

    // Serialize SensorData into buffer
    std::vector<char> sendBuffer(sizeof(SensorData));
    std::memcpy(sendBuffer.data(), &data, sizeof(SensorData));

    // Asynchronously write SensorData to the socket
    asio::async_write(
        socket_, asio::buffer(sendBuffer),
        [this](std::error_code ec, std::size_t length) {
          if (!ec) {
            std::cout << "SensorData sent to server. Waiting for echo..."
                      << std::endl;
          } else {
            std::cerr << "Error sending SensorData: " << ec.message()
                      << std::endl;
            // Close socket on error
            CloseSocket();
          }
        });
  } catch (const std::exception& e) {
    std::cerr << "Client send exception: " << e.what() << std::endl;
    // Close resources in case of exception
    CloseSocket();
  }
}

SensorData Client::GenerateRandomData() {
  SensorData randomData;

  // Initialize random number generator
  std::random_device rd;
  std::mt19937 gen(rd());

  // Generate random temperature values
  std::uniform_real_distribution<float> temp_dist(30.0f, 50.0f);
  // Generate random heart rate values
  std::uniform_int_distribution<int> heart_rate_dist(50, 200);
  // Generate random Oxygen saturation values
  std::uniform_int_distribution<int> oxygen_dist(90, 110);

  // Generate random values and decide if optional should be populated
  std::uniform_int_distribution<int> bool_dist(0, 1);
  if (bool_dist(gen) == 1) {
    randomData.temp = temp_dist(gen);
  }
  if (bool_dist(gen) == 1) {
    randomData.oxygen_saturation = oxygen_dist(gen);
  }
  if (bool_dist(gen) == 1) {
    randomData.heart_rate = heart_rate_dist(gen);
  }

  return randomData;
}
