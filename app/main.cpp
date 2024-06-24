#include <asio.hpp>
#include <iostream>

#include "safety/heart_rate_alert_handler.hpp"
#include "safety/oxygen_sat_alert_handler.hpp"
#include "safety/temp_alert_handler.hpp"
#include "server/server.hpp"

int main(int argc, char* argv[]) {
  try {
    if (argc != 2) {
      std::cerr << "Usage: ./server <port>" << std::endl;
      return 1;
    }

    // Create Temperature alert handlers with specific ranges
    auto temp_normal_range_handler =
        std::make_shared<TemperatureAlertHandler>(35.5f, 37.5f);
    auto temp_critical_range_handler =
        std::make_shared<TemperatureAlertHandler>(33.0f, 40.0f);
    // Chain the handlers together
    temp_normal_range_handler->SetNext(temp_critical_range_handler);

    // Heart Rate
    auto heart_rate_handler = std::make_shared<HeartRateAlertHandler>(60, 100);
    // Oxygen Saturation
    auto oxygen_handler =
        std::make_shared<OxygenSaturationAlertHandler>(95, 100);

    /* run server */
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
