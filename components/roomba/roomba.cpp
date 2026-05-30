#include "roomba.h"
#include "esphome/core/log.h"

namespace esphome {
namespace roomba {

static const char *const TAG = "roomba";

void RoombaComponent::setup() {
  ESP_LOGCONFIG(TAG, "Setting up Roomba component...");
  
  roomba_ = new Roomba(115200);  // baud rate
  roomba_->sensor_init();
  
  last_update_ = millis();
}

void RoombaComponent::loop() {
  uint32_t now = millis();
  
  if (now - last_update_ >= polling_interval_) {
    last_update_ = now;
    
    // Обновление датчиков
    float voltage = roomba_->getVoltage() * 0.001f;
    float current = roomba_->getCurrent() * 0.001f;
    float charge = roomba_->getCharge() * 0.001f;
    float capacity = roomba_->getCapacity() * 0.001f;
    float percent = roomba_->getBatteryPercent();
    float temperature = roomba_->getBatteryTemperature();
    int speed = roomba_->getDriveSpeed();
    
    voltage_sensor->publish_state(voltage);
    current_sensor->publish_state(current);
    charge_sensor->publish_state(charge);
    capacity_sensor->publish_state(capacity);
    percent_sensor->publish_state(percent);
    temperature_sensor->publish_state(temperature);
    speed_sensor->publish_state(speed);
    
    // Текстовые датчики
    charging_sensor->publish_state(roomba_->getChargingState());
    activity_sensor->publish_state(roomba_->getActivity());
    mode_sensor->publish_state(roomba_->getOiMode());
  }
}

void RoombaComponent::dump_config() {
  ESP_LOGCONFIG(TAG, "Roomba Component:");
  ESP_LOGCONFIG(TAG, "  Polling interval: %d ms", polling_interval_);
}

void RoombaComponent::send_command(const char *cmd) {
  if (strcmp(cmd, "start") == 0) {
    roomba_->start();
  } else if (strcmp(cmd, "stop") == 0) {
    roomba_->stop();
  } else if (strcmp(cmd, "dock") == 0) {
    roomba_->dock();
  } else if (strcmp(cmd, "locate") == 0) {
    roomba_->locate();
  } else if (strcmp(cmd, "sleep") == 0) {
    roomba_->sleep();
  }
}

} // namespace roomba
} // namespace esphome