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

# Getting Started with Ring Buffer USART

A Ring Buffer USART automatically stores incoming data in the background, ensuring no data loss even when the user isn't actively reading. It also allows for efficient transmission without requiring constant status checks.

## How to Use Ring Buffer USART for Another Module
To integrate ring buffer USART into another module, follow these steps:

1. **Copy USART Files**
   - Copy any existing `sercomX_usart.c` and `sercomX_usart.h` file into your module's directory.
   - Search and replace the SERCOM instance:
     - If you copied `SERCOM5`, replace all occurrences of `SERCOM5` with `SERCOM0` (or your desired instance).
     - Similarly, replace `sercom5` with `sercom0` in both C and header files.

2. **Set the Baud Rate**
   - Use the formula to calculate the `BAUD_VALUE` in `sercomX_usart.c`:
   ```C
   // BAUD_VALUE = 65536 * (1 - 16 * BAUD_RATE / CLK_FREQ)
   #define SERCOM1_USART_INT_BAUD_VALUE (65326UL) // BAUD_VALUE for 9600 baud rate
   ```

3. **Initialize USART in Your Module**
   - Include the SERCOM header and configure the pins in your module's C file:
   ```C
   #include "sercom1_usart.h"
   #include "pm_sensor.h"  

   void PMS_Initialize(void) {
       SERCOM1_USART_Initialize();
       PORT_SEC_REGS->GROUP[0].PORT_PINCFG[16] = 0x1U;
       PORT_SEC_REGS->GROUP[0].PORT_PINCFG[17] = 0x1U;
       PORT_SEC_REGS->GROUP[0].PORT_PMUX[8] = 0x22U;
   }
   ```

4. **Basic USART Communication**
   - **Writing Data**:
   ```C
   void SerialWrite(char* message) {
       // Wait until USART TX has enough space
       while (SERCOM1_USART_WriteFreeBufferCountGet() < sizeof(message));
       // Transmit the formatted string
       SERCOM1_USART_Write((void *)message, sizeof(message)); 
       // Transmits in background. No need for additional checks
   }
   ```
   
   - **Reading Data**:
   ```C
   void SerialRead(char* message, uint8_t length) {
       // Wait until the USART RX buffer has enough unread data
       while (SERCOM1_USART_ReadCountGet() < length);
       SERCOM1_USART_Read(message, length);
   }
   ```

By following these steps, you can quickly integrate USART functionality into any module using the ring buffer approach.


## License

This project is for educational purposes under EEE192. Feel free to modify and extend it based on project needs.

