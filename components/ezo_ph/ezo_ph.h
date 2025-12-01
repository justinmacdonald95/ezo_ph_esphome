#pragma once
#include "esphome.h"

namespace esphome {
namespace ezo_ph {

class EZOPhSensor : public PollingSensorComponent {
 public:
  UARTComponent *uart;

  void setup() override {
    // This will be called by ESPHome when initializing the component
    ESP_LOGD("ezo_ph", "Setup complete");
  }

  void update() override {
    // Poll the EZO UART sensor
    if (!uart) return;

    // Request a reading (send "R\r")
    uart->write_array((uint8_t*)"R\r", 2);

    // Read response (blocking here for simplicity)
    String response;
    unsigned long start = millis();
    while (millis() - start < 500) {  // wait max 500ms
      if (uart->available()) {
        char c = uart->read();
        response += c;
      }
    }

    if (response.length() > 0) {
      float value = response.toFloat();
      publish_state(value);
      ESP_LOGD("ezo_ph", "pH = %.2f", value);
    } else {
      ESP_LOGW("ezo_ph", "No response from EZO pH sensor");
    }
  }
};

}  // namespace ezo_ph
}  // namespace esphome
