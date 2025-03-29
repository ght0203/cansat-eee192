# CanSat EEE192 Project

This repository contains the firmware for the CanSat project developed for EEE192. The project is structured into multiple modules, each handling different aspects of the system, such as sensor communication, serial communication, and timing.

## Project Structure

```
./
├── README.md           # Main project documentation
├── main.c             # Entry point of the program
├── usart_common.h     # Common USART definitions
├── clock/             # System clock configuration
├── delay_timer/       # Timer-based delay implementation
├── hc12/              # HC-12 wireless communication module
├── pm_sensor/         # Particulate Matter (PM) sensor module
├── usb_serial/        # USB-to-serial communication module
```

## Module Descriptions

- **Clock (`clock/`)**
  - Handles system clock configuration.

- **Delay Timer (`delay_timer/`)**
  - Provides timing delays for operations.

- **HC-12 (`hc12/`)**
  - Manages communication with the HC-12 wireless transceiver.

- **PM Sensor (`pm_sensor/`)**
  - Interfaces with the particulate matter sensor.
  - [Read more](pm_sensor/README.md)

- **USB Serial (`usb_serial/`)**
  - Provides serial communication via USB.
  - [Read more](usb_serial/README.md)

## Getting Started

## License

This project is for educational purposes under EEE192. Feel free to modify and extend it based on project needs.

