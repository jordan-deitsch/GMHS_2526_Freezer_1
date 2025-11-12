/*
 * @file   ShiftRegisterDriver.h
 * @brief  Driver for 8-bit shift register
 * 
 * Shift Register PN: SN74HC165
 * Driver provides funtions for reading and printing results
 * of parallel-to-serial shift register
 * 
 * @author  Jordan Deitsch
 * @date    2025-11-11
 * @version 1.0
 *
 * @note    Requires Arduino.h for digitalWrite and delay functions.
 */

#ifndef SHIFT_REGISTER_DRIVER_H
#define SHIFT_REGISTER_DRIVER_H

// Include files
#include <Arduino.h>  // Include Arduino functions like digitalWrite, delay

// External macro definitions
#define PIN_CLK_OUT         (2)
#define PIN_CLK_INH_OUT     (3)
#define PIN_SERIAL_IN       (4)
#define PIN_SHIFT_LOAD_OUT  (5)

// Functions
uint8_t read_shift_register();
void print_shift_register(uint8_t reg_value);

#endif