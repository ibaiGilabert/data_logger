#include <asio.hpp>
#include <iostream>

#include "output/out_stream_file.hpp"
#include "output/out_stream_terminal.hpp"
#include "safety/heart_rate_alert_handler.hpp"
#include "safety/oxygen_sat_alert_handler.hpp"
#include "safety/temp_alert_handler.hpp"
#include "safety_mgr.hpp"
#include "server/server.hpp"

std::shared_ptr<SafetyMgr> SetupSafetyMgr() {
  // Setup alarm handlers for SafetyMgr
  auto safety_mgr = std::make_shared<SafetyMgr>();

  auto display_log = std::make_shared<OutputTerminal>();
  // Create Temperature alert handlers with specific ranges
  auto temp_normal_range_handler =
      std::make_shared<TemperatureAlertHandler>(35.5f, 37.5f, display_log);
  auto temp_critical_range_handler =
      std::make_shared<TemperatureAlertHandler>(33.0f, 40.0f, display_log);
  // Chain the handlers together
  temp_normal_range_handler->SetNext(temp_critical_range_handler);
  safety_mgr->AddAlarmHandler(DataMonitor::kTemperature,
                              temp_normal_range_handler);

  // Heart Rate
  auto heart_rate_handler =
      std::make_shared<HeartRateAlertHandler>(60, 180, display_log);
  safety_mgr->AddAlarmHandler(DataMonitor::kHeartRate, heart_rate_handler);

  // Oxygen Saturation
  auto oxygen_handler =
      std::make_shared<OxygenSaturationAlertHandler>(95, 100, display_log);
  safety_mgr->AddAlarmHandler(DataMonitor::kOxygenSaturation, oxygen_handler);
  return safety_mgr;
}

std::shared_ptr<Dispatcher> SetupDispatcher() {
  // Define maximum number of threads available for Thread Pool
  size_t thread_count = 4;

  // Output File concrete implementation for Dispatcher
  auto file_log = std::make_unique<OutputFile>();
  auto dispatcher =
      std::make_shared<Dispatcher>(std::move(file_log), thread_count);

  // Add SafetyMgr as an observer to Dispatcher
  auto safety_mgr = SetupSafetyMgr();
  dispatcher->AddObserver(safety_mgr);

  return dispatcher;
}

void RunServer(unsigned short port, std::shared_ptr<Dispatcher> dispatcher) {
  asio::io_context context;

  Server server(context, port);
  server.SetDispatcher(dispatcher);
  server.Start();

  // Run the io_context to start async operations
  context.run();
}

int main(int argc, char* argv[]) {
  try {
    if (argc != 2) {
      std::cerr << "Usage: ./server <port>" << std::endl;
      return 1;
    }

    // Setup Dispatcher in charge of business logic
    auto dispatcher = SetupDispatcher();

    // Run server
    RunServer(std::atoi(argv[1]), dispatcher);

  } catch (const std::exception& e) {
    std::cerr << "Exception: " << e.what() << "\n";
  }

  return 0;
}
