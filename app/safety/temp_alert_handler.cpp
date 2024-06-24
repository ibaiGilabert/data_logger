#include "temp_alert_handler.hpp"

TemperatureAlertHandler::TemperatureAlertHandler(float min_range,
                                                 float max_range)
    : min_range_(min_range), max_range_(max_range) {}

void TemperatureAlertHandler::Handle(float temp) {
  if (temp < min_range_ || temp > max_range_) {
    std::cout << "Alert: Temperature out of range!" << std::endl;
  }
  if (next_) {
    next_->Handle(temp);
  }
}
