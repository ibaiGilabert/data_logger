#ifndef SERVER_HPP
#define SERVER_HPP

#include <asio.hpp>
#include <iostream>
#include <memory>
#include <queue>
#include <thread>

#include "session.hpp"

using asio::ip::tcp;

class Server {
 public:
  Server(asio::io_context& context, unsigned short port);
  ~Server();

  void Start();
  void Stop();

 private:
  void AcceptConnection();
  void HandleAccept(tcp::socket socket, const std::error_code& ec);

 private:
  asio::io_context& context_;
  tcp::acceptor acceptor_;
  // Track active sessions
  std::queue<std::shared_ptr<Session>> sessions_;
  // Mutex for thread-safe access to sessions
  std::mutex sessionsMutex_;
};

#endif  // SERVER_HPP
