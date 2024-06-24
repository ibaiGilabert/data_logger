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
template <typename T>
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
  void SetNext(std::shared_ptr<AlertHandler<T>> next_handler) {
    next_ = next_handler;
  }

  /**
   * @brief Handles the alert by processing the provided value.
   *
   * This method should be overridden by derived classes to handle specific
   * alerts.
   *
   * @param value The value to check against the range.
   */
  virtual void Handle(T value) = 0;

 protected:
  std::shared_ptr<AlertHandler<T>> next_; /**< The next handler in the chain */
};

#endif  // ALERT_HANDLER_H_
