#ifndef SESSION_HPP
#define SESSION_HPP

#include <asio.hpp>
#include <iostream>
#include <memory>

#include "common.hpp"

using asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
 public:
  Session(tcp::socket socket);
  ~Session();

  void Start();
  void Close();

 private:
  void ReadData();
  void ProcessData(const SensorData& data);

 private:
  static constexpr std::chrono::seconds kProcessDelay{1};

  tcp::socket socket_;
  std::array<char, sizeof(SensorData)> recvBuffer_;
};

#endif  // SESSION_HPP
