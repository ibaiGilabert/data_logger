#include "safety_mgr.hpp"

SafetyMgr::SafetyMgr() {}

std::optional<float> temp;
std::optional<int> heart_rate;
std::optional<int> oxygen_saturation;

void SafetyMgr::AddAlarmHandler(DataMonitor data_type,
                                std::shared_ptr<AlertHandler> handler) {
  alert_handlers_[data_type] = handler;
}

void SafetyMgr::Process(const SensorData& data) {
  for (auto handler : alert_handlers_) {
    switch (handler.first) {
      case DataMonitor::kTemperature:
        if (data.temp.has_value()) {
          handler.second->Handle(data.temp.value());
        }
        break;
      case DataMonitor::kHeartRate:
        if (data.heart_rate.has_value()) {
          handler.second->Handle(data.heart_rate.value());
        }
        break;
      case DataMonitor::kOxygenSaturation:
        if (data.oxygen_saturation.has_value()) {
          handler.second->Handle(data.oxygen_saturation.value());
        }
        break;
    }
  }
}
