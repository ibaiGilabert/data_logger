#ifndef OBSERVER_H_
#define OBSERVER_H_

#include "common.hpp"

class Observer {
 public:
  virtual ~Observer() = default;
  virtual void Process(const SensorData& data) = 0;
};

#endif  // SESSION_H_
