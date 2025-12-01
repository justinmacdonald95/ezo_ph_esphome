### ESPHome External Component – Atlas Scientific EZO pH (UART) ###

This repository provides an ESPHome **External Component** for reading pH values from the  
**Atlas Scientific EZO pH Circuit** using **UART mode**.

This component is compatible with ESPHome 2023.6+ and the current 2024–2025 builds  
where `custom_components/` support has been removed and **only external components**  
(GitHub-based) are allowed.

---

## Wiring

### **EZO pH Circuit → ESP32 (UART2 example)**

| EZO Pin | ESP32 Pin |
|--------|-----------|
| VCC    | 3.3V      |
| GND    | GND       |
| TX     | GPIO16 (RX2) |
| RX     | GPIO17 (TX2) |

The EZO board **must be set to UART mode** 

