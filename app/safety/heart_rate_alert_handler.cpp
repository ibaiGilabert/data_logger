#include "heart_rate_alert_handler.hpp"

HeartRateAlertHandler::HeartRateAlertHandler(int min_range, int max_range,
                                             std::shared_ptr<Output> display)
    : display_(display), min_range_(min_range), max_range_(max_range) {}

bool HeartRateAlertHandler::HandleAlert(int heart_rate) {
  if (heart_rate < min_range_ || heart_rate > max_range_) {
    std::stringstream stream;
    stream << "Alert: Heart rate out of range! (" << heart_rate << ") range: ["
           << min_range_ << ", " << max_range_ << "]";
    // Display error
    display_->Write(TraceFormatter::Format(stream.str()));
    return false;
  }
  return true;
}
