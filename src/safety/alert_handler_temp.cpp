#include "alert_handler_temp.hpp"

TemperatureAlertHandler::TemperatureAlertHandler(
    float min_range, float max_range, std::shared_ptr<Output> display)
    : display_(display), min_range_(min_range), max_range_(max_range) {}

bool TemperatureAlertHandler::HandleAlert(float temp) {
  if (temp < min_range_ || temp > max_range_) {
    std::stringstream stream;
    stream << "Alert: Temperature out of range! (" << temp << ")" << min_range_
           << ", " << max_range_ << "]";
    // Display error
    display_->Write(TraceFormatter::Format(stream.str()));
    return false;
  }
  return true;
}
