#ifndef TEMPERATURE_ALERT_HANDLER_H_
#define TEMPERATURE_ALERT_HANDLER_H_

#include <iostream>

#include "alert_handler.hpp"

/**
 * @brief Handler for temperature alerts.
 *
 * The TemperatureAlertHandler class checks if the temperature is out of the
 * specified range and raises an alert if it is.
 */
class TemperatureAlertHandler : public AlertHandler<float> {
 public:
  /**
   * @brief Constructs a TemperatureAlertHandler with the specified range.
   *
   * @param min_range The minimum acceptable temperature.
   * @param max_range The maximum acceptable temperature.
   */
  TemperatureAlertHandler(float min_range, float max_range);

  /**
   * @brief Handles the temperature alert.
   *
   * Checks if the temperature is out of the specified range
   * and raises an alert if it is. Passes the data to the next handler in the
   * chain.
   *
   * @param temp The temperature value.
   */
  void Handle(float temp) override;

 private:
  float min_range_; /**< Minimum acceptable temperature */
  float max_range_; /**< Maximum acceptable temperature */
};

#endif  // TEMPERATURE_ALERT_HANDLER_H_
