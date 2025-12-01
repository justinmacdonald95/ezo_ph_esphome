#pragma once
#include "esphome/core/component.h"
#include "esphome/components/uart/uart.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace ezo_ph {

class EZOPHSensor : public uart::UARTDevice, public sensor::Sensor, public Component {
 public:
  EZOPHSensor(uart::UARTComponent *parent) : uart::UARTDevice(parent) {}

  void setup() override {
    // Nothing required — EZO automatically replies on "R" command.
  }

  void update() override {
    this->write_str("R\r");
  }

  void loop() override {
    while (this->available()) {
      char c = this->read();
      if (c == '\r' || c == '\n') {
        if (!buffer_.empty()) {
          float ph = atof(buffer_.c_str());
          publish_state(ph);
          buffer_.clear();
        }
      } else {
        buffer_ += c;
      }
    }
  }

 protected:
  std::string buffer_;
};

}  // namespace ezo_ph
}  // namespace esphome
