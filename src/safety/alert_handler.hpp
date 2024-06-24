#ifndef ALERT_HANDLER_H_
#define ALERT_HANDLER_H_

#include <iostream>
#include <memory>

/**
 * @brief Templated class for handling alerts.
 *
 * The AlertHandler class provides a template for handling alerts of specific
 * types in a Chain of Responsibility pattern.
 */
class AlertHandler {
 public:
  /**
   * @brief Virtual destructor.
   */
  virtual ~AlertHandler() = default;

  /**
   * @brief Sets the next handler in the chain.
   *
   * @param next_handler A shared pointer to the next AlertHandler.
   */
  void SetNext(std::shared_ptr<AlertHandler> next_handler) {
    next_ = next_handler;
  }

  /**
   * @brief Handles the alert value of type T.
   *
   * This method attempts to handle the alert value of type <T>. If it handles
   * the alert successfully and there is a next handler in the chain, the alert
   * value is passed to the next handler.
   *
   * @tparam T The type of the alert value to handle (int, float, etc.).
   * @param value The alert value to handle.
   */
  template <typename T>
  void Handle(T value) {
    if (HandleAlert(value) && next_) {
      next_->Handle(value);
    }
  }

 protected:
  /**
   * @brief Handles the alert of type int.
   *
   * Override this method in derived classes to handle alerts of type int.
   *
   * @param value The integer alert value to handle.
   * @return true if the alert is handled, false otherwise.
   */
  virtual bool HandleAlert(int value) { return false; }

  /**
   * @brief Handles the alert of type float.
   *
   * Override this method in derived classes to handle alerts of type float.
   *
   * @param value The float alert value to handle.
   * @return true if the alert is handled, false otherwise.
   */
  virtual bool HandleAlert(float value) { return false; }

 protected:
  std::shared_ptr<AlertHandler> next_; /**< The next handler in the chain */
};

#endif  // ALERT_HANDLER_H_
