#include <asio.hpp>
#include <iostream>

#include "client.hpp"

int main(int argc, char* argv[]) {
  try {
    if (argc != 3) {
      std::cerr << "Usage: ./client <server_ip> <server_port>" << std::endl;
      return 1;
    }
    asio::io_context context;

    Client client(context, argv[1], std::atoi(argv[2]));
    client.Connect();

    // Run the io_context to start async operations
    context.run();
  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
