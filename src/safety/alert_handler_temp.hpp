#ifndef TEMPERATURE_ALERT_HANDLER_H_
#define TEMPERATURE_ALERT_HANDLER_H_

#include <iostream>

#include "../output/out_stream.hpp"
#include "alert_handler.hpp"

/**
 * @brief Handler for temperature alerts.
 *
 * The TemperatureAlertHandler class checks if the temperature is out of the
 * specified range and raises an alert if it is.
 */
class TemperatureAlertHandler : public AlertHandler {
 public:
  /**
   * @brief Constructs a TemperatureAlertHandler with the specified range.
   *
   * @param min_range The minimum acceptable temperature.
   * @param max_range The maximum acceptable temperature.
   */
  TemperatureAlertHandler(float min_range, float max_range,
                          std::shared_ptr<Output> display);

 protected:
  /**
   * @brief Handles the temperature alert.
   *
   * Checks if the temperature is out of the specified range
   * and raises an alert if it is. Passes the data to the next handler in the
   * chain.
   *
   * @param temp The temperature value.
   */
  bool HandleAlert(float temp) override;

 private:
  std::shared_ptr<Output> display_; /**< Output object for displaying alerts */
  float min_range_;                 /**< Minimum acceptable temperature */
  float max_range_;                 /**< Maximum acceptable temperature */
};

#endif  // TEMPERATURE_ALERT_HANDLER_H_
