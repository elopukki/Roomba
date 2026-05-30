#pragma once

#include "esphome.h"
#include <Roomba.h>

namespace esphome {
namespace roomba {

class RoombaComponent : public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
  
  void set_uart(uart::UARTBus *uart) { uart_ = uart; }
  
  // Датчики
  sensor::Sensor *voltage_sensor = new sensor::Sensor();
  sensor::Sensor *current_sensor = new sensor::Sensor();
  sensor::Sensor *charge_sensor = new sensor::Sensor();
  sensor::Sensor *capacity_sensor = new sensor::Sensor();
  sensor::Sensor *percent_sensor = new sensor::Sensor();
  sensor::Sensor *temperature_sensor = new sensor::Sensor();
  sensor::Sensor *speed_sensor = new sensor::Sensor();
  
  // Текстовые датчики
  text_sensor::TextSensor *charging_sensor = new text_sensor::TextSensor();
  text_sensor::TextSensor *activity_sensor = new text_sensor::TextSensor();
  text_sensor::TextSensor *mode_sensor = new text_sensor::TextSensor();
  
  // Команды
  void send_command(const char *cmd);
  
 private:
  uart::UARTBus *uart_;
  Roomba *roomba_;
  uint32_t last_update_ = 0;
  uint32_t polling_interval_ = 8000;
};

} // namespace roomba
} // namespace esphome