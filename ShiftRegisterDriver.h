#ifndef SHIFT_REGISTER_DRIVER_H
#define SHIFT_REGISTER_DRIVER_H

#include <Arduino.h>  // Include Arduino functions like digitalWrite, delay

#define PIN_CLK_OUT         (2)
#define PIN_CLK_INH_OUT     (3)
#define PIN_SERIAL_IN       (4)
#define PIN_SHIFT_LOAD_OUT  (5)

uint8_t read_shift_register();
void print_shift_register(uint8_t reg_value);

#endif