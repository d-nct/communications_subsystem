#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <Arduino.h>
#include <cstdint>
#include <stdint.h>
#include <SPI.h>

/* Definição da placa */
/* ------------------ */
#define ESP32                     
//#define ARDUINO_UNO               

/* Configurações de Debug */
/* ---------------------- */
/* Log levels:
    LOG_ERROR      - Only errors
    LOG_WARNING    - Errors and warnings
    LOG_INFO       - Errors, warnings and info
    LOG_DEBUG      - Errors, warnings, info and debug messages */
#define LOG_LEVEL                 LOG_DEBUG

/* Configurações de Hardware */
/* ------------------------- */
#define LORA_PIN_SS               24 // Chip Select
#define LORA_PIN_RST              25 // Reset
#define LORA_PIN_DIO0             26 // Interrupt
#define LORA_FREQUENCY            915E6
#define LORA_SYNC_WORD            0x53 // S, de SATS.    0-0xFF

#ifdef ESP32
#define SERIAL_BAUDRATE           115200
#endif
#ifdef ARDUINO_UNO
#define SERIAL_BAUDRATE           9600
#endif


#endif // DEFINITIONS_H