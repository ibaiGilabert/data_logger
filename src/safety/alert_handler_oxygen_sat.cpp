#include "alert_handler_oxygen_sat.hpp"

OxygenSaturationAlertHandler::OxygenSaturationAlertHandler(
    int min_range, int max_range, std::shared_ptr<Output> display)
    : display_(display), min_range_(min_range), max_range_(max_range) {}

bool OxygenSaturationAlertHandler::HandleAlert(int oxygen_sat) {
  if (oxygen_sat < min_range_ || oxygen_sat > max_range_) {
    std::stringstream stream;
    stream << "Oxygen saturation out of range! (" << oxygen_sat << ") range: ["
           << min_range_ << ", " << max_range_ << "]";
    // Display error
    display_->Write(TraceFormatter::Format(stream.str()));
    return false;
  }
  return true;
}
