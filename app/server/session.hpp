#ifndef SESSION_H_
#define SESSION_H_

#include <asio.hpp>
#include <iostream>
#include <memory>

#include "../dispatcher.hpp"

using asio::ip::tcp;

class Session : public std::enable_shared_from_this<Session> {
 public:
  Session(tcp::socket socket, std::shared_ptr<Dispatcher> dispatcher);
  ~Session();

  void Start();
  void Close();

 private:
  void ReadData();
  void ProcessData(const SensorData& data);

 private:
  static constexpr std::chrono::seconds kProcessDelay{1};

  std::shared_ptr<Dispatcher> dispatcher_;
  tcp::socket socket_;
  std::array<char, sizeof(SensorData)> recv_buffer_;
};

#endif  // SESSION_H_
