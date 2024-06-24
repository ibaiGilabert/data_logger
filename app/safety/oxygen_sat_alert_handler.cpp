#include "oxygen_sat_alert_handler.hpp"

OxygenSaturationAlertHandler::OxygenSaturationAlertHandler(int min_range,
                                                           int max_range)
    : min_range_(min_range), max_range_(max_range) {}

void OxygenSaturationAlertHandler::Handle(int oxygen_sat) {
  if (oxygen_sat < min_range_ || oxygen_sat > max_range_) {
    std::cout << "Alert: Oxygen saturation out of range!" << std::endl;
  }
  if (next_) {
    next_->Handle(oxygen_sat);
  }
}
