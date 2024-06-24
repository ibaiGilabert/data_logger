#include "server.hpp"

Server::Server(asio::io_context& context, unsigned short port)
    : acceptor_(context, tcp::endpoint(tcp::v4(), port)), context_(context) {}

Server::~Server() {
  // Ensure all sessions and resources are properly released
  Stop();
}

void Server::Start() { AcceptConnection(); }

void Server::Stop() {
  // Close all active sessions
  std::lock_guard<std::mutex> lock(sessions_mutex_);
  while (!sessions_.empty()) {
    auto session = sessions_.front();
    session->Close();
    sessions_.pop();
  }

  // Close the acceptor to prevent new connections
  std::error_code ec;
  acceptor_.close(ec);
  if (ec) {
    std::cerr << "Error closing acceptor: " << ec.message() << std::endl;
  }
}

void Server::AcceptConnection() {
  auto socket = std::make_shared<tcp::socket>(context_);

  acceptor_.async_accept(*socket, [this, socket](const std::error_code& ec) {
    HandleAccept(std::move(*socket), ec);
  });
}

void Server::HandleAccept(tcp::socket socket, const std::error_code& ec) {
  if (!ec) {
    try {
      // Create a new session and start it
      auto newSession = std::make_shared<Session>(std::move(socket));
      newSession->Start();

      // Add the session to the queue of active sessions
      {
        std::lock_guard<std::mutex> lock(sessions_mutex_);
        sessions_.push(newSession);
      }
    } catch (const std::exception& e) {
      std::cerr << "Session creation error: " << e.what() << std::endl;
      socket.close();
    }
  } else {
    std::cerr << "Accept error: " << ec.message() << std::endl;
  }

  // Accept the next connection
  AcceptConnection();
}
