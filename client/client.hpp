#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <asio.hpp>
#include <iostream>
#include <thread>

#include "common.hpp"

using asio::ip::tcp;

class Client {
 public:
  Client(asio::io_context& context, const std::string& host,
         unsigned short port);
  ~Client();

  void Connect();

 private:
  void CloseSocket();
  void SendData();

  static SensorData GenerateRandomData();

 private:
  // Timeout duration for receiveAck()
  static constexpr std::chrono::seconds kReceiveTimeout{5};
  // Delay duration for sendData()
  static constexpr std::chrono::seconds kSendRate{1};

  tcp::resolver::results_type endpoints_;
  tcp::resolver resolver_;
  tcp::socket socket_;
};

#endif  // CLIENT_HPP
