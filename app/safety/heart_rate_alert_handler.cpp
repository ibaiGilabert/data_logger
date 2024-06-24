#include "heart_rate_alert_handler.hpp"

HeartRateAlertHandler::HeartRateAlertHandler(int min_range, int max_range)
    : min_range_(min_range), max_range_(max_range) {}

void HeartRateAlertHandler::Handle(int heart_rate) {
  if (heart_rate < min_range_ || heart_rate > max_range_) {
    std::cout << "Alert: Heart rate out of range!" << std::endl;
  }
  if (next_) {
    next_->Handle(heart_rate);
  }
}
