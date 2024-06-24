#ifndef DISPATCHER_H_
#define DISPATCHER_H_

#include <iostream>
#include <memory>
#include <thread>
#include <unordered_set>

#include "observer.hpp"
#include "output/out_stream.hpp"
#include "thread_pool.hpp"

class Dispatcher {
 public:
  /**
   * @brief Constructor for Dispatcher class.
   *
   * @param tracer A unique pointer to an Output object used for
   * tracing/logging.
   * @param thread_count Number of threads to be used in the thread pool.
   */
  Dispatcher(std::unique_ptr<Output> tracer, size_t thread_count);

  /**
   * @brief Adds an observer to the Dispatcher.
   *
   * @param observer A shared pointer to the Observer object to be added.
   */
  void AddObserver(std::shared_ptr<Observer> observer);

  /**
   * @brief Removes an observer from the Dispatcher.
   *
   * @param observer A shared pointer to the Observer object to be removed.
   */
  void RemoveObserver(std::shared_ptr<Observer> observer);

  /**
   * @brief Processes the incoming SensorData.
   *
   * This method formats the SensorData using TraceFormatter, writes it to the
   * tracer, and then notifies all registered observers asynchronously using a
   * thread pool.
   *
   * @param data The SensorData object to be processed.
   */
  void ProcessData(const SensorData& data);

 private:
  std::unique_ptr<Output> tracer_;

  std::unordered_set<std::shared_ptr<Observer>> observers_;
  ThreadPool pool_;
};

#endif  // DISPATCHER_H_
