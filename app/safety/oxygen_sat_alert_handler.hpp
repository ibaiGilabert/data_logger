#ifndef OXYGEN_SATURATION_ALERT_HANDLER_H_
#define OXYGEN_SATURATION_ALERT_HANDLER_H_

#include <iostream>

#include "alert_handler.hpp"

/**
 * @brief Handler for oxygen saturation alerts.
 *
 * The OxygenSaturationAlertHandler class checks if the oxygen saturation is out
 * of the specified range and raises an alert if it is.
 */
class OxygenSaturationAlertHandler : public AlertHandler<int> {
 public:
  /**
   * @brief Constructs an OxygenSaturationAlertHandler with the specified range.
   *
   * @param min_range The minimum acceptable oxygen saturation.
   * @param max_range The maximum acceptable oxygen saturation.
   */
  OxygenSaturationAlertHandler(int min_range, int max_range);

  /**
   * @brief Handles the oxygen saturation alert.
   *
   * Checks if the oxygen saturation is out of the specified range
   * and raises an alert if it is. Passes the data to the next handler in the
   * chain.
   *
   * @param oxygen_sat The oxygen saturation value.
   */
  void Handle(int oxygen_sat) override;

 private:
  int min_range_; /**< Minimum acceptable oxygen saturation */
  int max_range_; /**< Maximum acceptable oxygen saturation */
};

#endif  // OXYGEN_SATURATION_ALERT_HANDLER_H_
