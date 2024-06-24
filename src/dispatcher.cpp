#include "dispatcher.hpp"

Dispatcher::Dispatcher(std::unique_ptr<Output> tracer, size_t thread_count)
    : tracer_(std::move(tracer)), pool_(thread_count) {}

void Dispatcher::AddObserver(std::shared_ptr<Observer> observer) {
  observers_.insert(observer);
}

void Dispatcher::RemoveObserver(std::shared_ptr<Observer> observer) {
  observers_.erase(observer);
}

void Dispatcher::ProcessData(const SensorData& data) {
  std::string data_formatted = TraceFormatter::Format(data);
  tracer_->Write(data_formatted);

  // Notify all observers
  for (auto& observer : observers_) {
    pool_.enqueue([observer, &data]() { observer->Process(data); });
  }

  // NOTE: Todo: to verify exceptions grafefully in future<T> types, the result
  // must be collected by a synchronous blocking 'get()' operation. To do this
  // smoothely, another process checking the future's result must be carried
  // out.
}