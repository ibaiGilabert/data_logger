#include <asio.hpp>
#include <iostream>

#include "server.hpp"

int main(int argc, char* argv[]) {
  try {
    if (argc != 2) {
      std::cerr << "Usage: ./server <port>" << std::endl;
      return 1;
    }
    asio::io_context context;

    Server server(context, std::atoi(argv[1]));
    server.Start();

    // Run the io_context to start async operations
    context.run();
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
