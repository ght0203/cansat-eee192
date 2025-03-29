# PMS Sensor Communication Library

## Overview
This library provides functions for communicating with a PMS7003 particulate matter sensor using USART. It supports passive mode operation, polling sensor data, and retrieving PM1.0, PM2.5, and PM10 readings. Additionally, it includes debugging functions for displaying raw sensor data over USB serial.

## Initialization
Before using the library, initialize the PMS sensor and USART interface:

```c
void PMS_Initialize(void);
```

This function configures the USART communication for the PMS sensor on SERCOM1 and sets the appropriate pin configurations.

## Switching to Passive Mode
The PMS sensor supports both passive and active modes. The following function switches the sensor to passive mode:

```c
void PMSUsart_PassiveMode(void);
```

## Sending Commands to the PMS Sensor
The function `PMSUSart_Command` sends commands to the PMS sensor by formatting a byte sequence including a checksum:

```c
static void PMSUSart_Command(uint8_t cmd, uint8_t datah, uint8_t datal);
```

## Polling Sensor Data
To retrieve data from the sensor, use:

```c
void PMS_PollSensorData(void);
```

This function sends a request to the sensor and reads a 32-byte response.

## Debugging Sensor Data
To display raw sensor data over USB serial, use:

```c
void PMSUsart_DebugRead(void);
```

This function prints the received 30 bytes of sensor data in hexadecimal format.

## Retrieving PM Measurements
To extract specific PM measurements, use the following functions after polling data:

```c
uint16_t PMS_GetDataPM10(void);
uint16_t PMS_GetDataPM1(void);
uint16_t PMS_GetDataPM2_5(void);
```

Each function returns the corresponding PM concentration as a 16-bit integer.

## Validating Sensor Data
For active mode, you can verify the integrity of received data using:

```c
static bool PMSUsart_ValidData(uint8_t data[32]);
```

This function checks if the checksum of the received data matches the expected value.

## Notes
- Always call `PMS_PollSensorData()` before retrieving PM values.
- The USART interface must be properly initialized before using any functions.
- The library currently supports passive mode operation but can be extended for active mode usage.

## License
This code is provided as-is without warranty. Modify and use it as needed for your application.

