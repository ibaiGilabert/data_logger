#ifndef SAFETY_MGR_H_
#define SAFETY_MGR_H_

#include <map>

#include "observer.hpp"
#include "safety/alert_handler.hpp"

enum class DataMonitor {
  kTemperature,
  kHeartRate,
  kOxygenSaturation,
  kUndefined = -1
};

/**
 * @brief Safety Manager which performs safety analysis.
 *
 *  It follows the Observer pattern such that it checks the new data received
 * through whoever notifies it
 */
class SafetyMgr : public Observer {
 public:
  SafetyMgr();
  ~SafetyMgr() override = default;

  /**
   * @brief Add chained alarm handler (Chain of Responsibility Pattern) for a
   * specific type of data to monitor.
   *
   * @param data_type The type of data to monitor
   * etc.).
   * @param handler A shared pointer to the alert handler object.
   */
  void AddAlarmHandler(DataMonitor data_type,
                       std::shared_ptr<AlertHandler> handler);

  /**
   * @brief Perform a safety check through the data received
   *
   * @param data The SensorData object containing temperature, heart rate, and
   * oxygen saturation data.
   */
  void Process(const SensorData& data) override;

 private:
  std::map<DataMonitor, std::shared_ptr<AlertHandler>> alert_handlers_;
};

#endif  // SAFETY_MGR_H_
