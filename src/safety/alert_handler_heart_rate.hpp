#ifndef HEART_RATE_ALERT_HANDLER_H_
#define HEART_RATE_ALERT_HANDLER_H_

#include <iostream>

#include "../output/out_stream.hpp"
#include "alert_handler.hpp"

/**
 * @brief Handler for heart rate alerts.
 *
 * The HeartRateAlertHandler class checks if the heart rate is out of the
 * specified range and raises an alert if it is.
 */
class HeartRateAlertHandler : public AlertHandler {
 public:
  /**
   * @brief Constructs a HeartRateAlertHandler with the specified range.
   *
   * @param min_range The minimum acceptable heart rate.
   * @param max_range The maximum acceptable heart rate.
   */
  HeartRateAlertHandler(int min_range, int max_range,
                        std::shared_ptr<Output> display);

 protected:
  /**
   * @brief Handles the heart rate alert.
   *
   * Checks if the heart rate is out of the specified range
   * and raises an alert if it is. Passes the data to the next handler in the
   * chain.
   *
   * @param heart_rate The heart rate value.
   */
  bool HandleAlert(int heart_rate) override;

 private:
  std::shared_ptr<Output> display_; /**< Output object for displaying alerts */
  int min_range_;                   /**< Minimum acceptable heart rate */
  int max_range_;                   /**< Maximum acceptable heart rate */
};

#endif  // HEART_RATE_ALERT_HANDLER_H_
