#ifndef SERVER_H_
#define SERVER_H_

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

  void SetDispatcher(std::shared_ptr<Dispatcher> dispatcher);
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
  std::mutex sessions_mutex_;
  // Dispatcher for business logic
  std::shared_ptr<Dispatcher> dispatcher_;
};

#endif  // SERVER_H_
