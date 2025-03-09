/*******************************************************************************
  Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This file contains the "main" function for a project.

  Description:
    This file contains the "main" function for a project. The
    "main" function calls the "SYS_Initialize" function to initialize the state
    machines of all modules in the system.
 *******************************************************************************/

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stddef.h>                     // Defines NULL
#include <stdbool.h>                    // Defines true
#include <stdlib.h>                     // Defines EXIT_FAILURE
#include "definitions.h"                // SYS function prototypes

#include <stdio.h>
#include <string.h>  // For strlen()
#include "bme280.h"  // BME280 sensor driver

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************

#define BME280_I2C_ADDR 0x76  // Default I2C Address (Change to 0x77 if needed)

// BME280 device instance
struct bme280_dev bme280_dev;

// Function prototypes
void UART_WriteString(const char *str);
void UART_WriteInt(int value);
void bme280_delay_us(uint32_t period, void *intf_ptr);
int8_t bme280_read(uint8_t reg_addr, uint8_t *data, uint32_t len, void *intf_ptr);
int8_t bme280_write(uint8_t reg_addr, const uint8_t *data, uint32_t len, void *intf_ptr);
void init_bme280(void);
void read_bme280_data(void);
void delay_ms(uint32_t ms);  // Custom delay function

// ? Function to send a string over UART
void UART_WriteString(const char *str)
{
    SERCOM3_USART_Write((uint8_t *)str, strlen(str));  // Send string over UART
}

// ? Function to send an integer over UART
void UART_WriteInt(int value)
{
    char buffer[12];  // Buffer for integer to string conversion
    sprintf(buffer, "%d", value);  // Convert int to string
    UART_WriteString(buffer);
}

// ? Microsecond delay function (for BME280)
void bme280_delay_us(uint32_t period, void *intf_ptr)
{
    uint32_t i;
    for (i = 0; i < period * 10; i++)  // Rough estimate for delay
    {
        asm("nop");
    }
}

// ? Millisecond delay function using a simple loop
void delay_ms(uint32_t ms)
{
    uint32_t count = ms * 5000;  // Adjust for ~1ms at 48MHz CPU clock
    while (count--) asm("nop");
}

// ? I2C Read Function (SERCOM2)
int8_t bme280_read(uint8_t reg_addr, uint8_t *data, uint32_t len, void *intf_ptr)
{
    uint16_t i2c_addr = *(uint16_t *)intf_ptr;

    // Send register address
    if (!SERCOM2_I2C_Write(i2c_addr, &reg_addr, 1))
    {
        return -1;  // Write failed
    }

    // Read data from sensor
    if (!SERCOM2_I2C_Read(i2c_addr, data, len))
    {
        return -1;  // Read failed
    }

    return 0;  // Success
}

// ? I2C Write Function (SERCOM2)
int8_t bme280_write(uint8_t reg_addr, const uint8_t *data, uint32_t len, void *intf_ptr)
{
    uint16_t i2c_addr = *(uint16_t *)intf_ptr;
    uint8_t buffer[len + 1];

    buffer[0] = reg_addr;
    memcpy(&buffer[1], data, len);

    if (!SERCOM2_I2C_Write(i2c_addr, buffer, len + 1))
    {
        return -1;  // Write failed
    }

    return 0;  // Success
}

// ? Initialize BME280 Sensor
void init_bme280(void)
{
    static uint8_t i2c_address = BME280_I2C_ADDR;  // Store in a variable

    // Test BME280 communication by reading chip ID
    uint8_t chip_id;
    uint8_t reg_addr = 0xD0; // Chip ID register

    if (bme280_read(reg_addr, &chip_id, 1, &i2c_address) == 0) {
        char msg[50];
        sprintf(msg, "BME280 Chip ID: 0x%02X (should be 0x60)\n", chip_id);
        UART_WriteString(msg);
        if (chip_id == 0x60) {
            UART_WriteString("BME280 Found!\n");
        } else {
            UART_WriteString("Wrong Chip ID! Check connections.\n");
            while (1);  // Stop execution if chip ID is incorrect
        }
    } else {
        UART_WriteString("Failed to read Chip ID!\n");
        while (1);  // Stop execution if reading fails
    }

    bme280_dev.intf = BME280_I2C_INTF;
    bme280_dev.read = bme280_read;
    bme280_dev.write = bme280_write;
    bme280_dev.delay_us = bme280_delay_us;
    bme280_dev.intf_ptr = &i2c_address;

    // Initialize BME280
    int8_t result = bme280_init(&bme280_dev);
    if (result == BME280_OK) {
        UART_WriteString("BME280 Initialized Successfully!\n");
    } else {
        char error_msg[50];
        sprintf(error_msg, "BME280 Init Error: %d\n", result);
        UART_WriteString(error_msg);
        while (1);  // Stop if initialization fails
    }

    // Set sensor settings
    struct bme280_settings settings;
    settings.osr_h = BME280_OVERSAMPLING_1X;
    settings.osr_p = BME280_OVERSAMPLING_1X;
    settings.osr_t = BME280_OVERSAMPLING_1X;
    settings.filter = BME280_FILTER_COEFF_OFF;
    settings.standby_time = BME280_STANDBY_TIME_0_5_MS;

    // Apply settings
    bme280_set_sensor_settings(BME280_SEL_ALL_SETTINGS, &settings, &bme280_dev);
    bme280_set_sensor_mode(BME280_POWERMODE_NORMAL, &bme280_dev);
}

// ? Read Sensor Data and Print via UART
void read_bme280_data(void)
{
    struct bme280_data comp_data;

    if (bme280_get_sensor_data(BME280_ALL, &comp_data, &bme280_dev) == BME280_OK)
    {
        char msg[100];

        sprintf(msg, "Temperature: %.2f C\n", comp_data.temperature);
        UART_WriteString(msg);

        sprintf(msg, "Pressure: %.2f hPa\n", comp_data.pressure / 100.0);
        UART_WriteString(msg);

        sprintf(msg, "Humidity: %.2f %%\n", comp_data.humidity);
        UART_WriteString(msg);
    }
    else
    {
        UART_WriteString("Failed to read BME280 data.\n");
    }
}

// ? Main Function
int main(void)
{
    SYS_Initialize(NULL);  // Initialize Harmony system

    SERCOM3_USART_Initialize();  // Initialize UART
    UART_WriteString("UART Initialized! BME280 Starting...\n");

    SERCOM2_I2C_Initialize();  // Initialize I2C
    UART_WriteString("I2C Initialized!\n");

    // Test I2C communication
    UART_WriteString("Testing I2C Communication...\n");
    uint8_t test_data;
    if (SERCOM2_I2C_Read(BME280_I2C_ADDR, &test_data, 1)) {
        UART_WriteString("I2C Communication OK!\n");
    } else {
        UART_WriteString("I2C Communication Failed!\n");
        while (1);
    }

    // Initialize BME280
    UART_WriteString("Initializing BME280...\n");
    init_bme280();
    UART_WriteString("BME280 Initialized!\n");

    // Main loop
    while (1)
    {
        read_bme280_data();
        delay_ms(1000);  // 1-second delay
    }

    return 0;
}

/*******************************************************************************
 End of File
*/