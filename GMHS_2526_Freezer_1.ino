/*
 * @file   GMHS_2526_Freezer_1.ino
 * @brief  Controller for freezer inventory system
 * 
 * Controller uses Hall sensors and shift registers
 * to identify shelves with unique magnetic codes
 * and perform related inventory
 * 
 * @author  Jordan Deitsch
 * @date    2025-11-11
 * @version 1.0
 *
 */

#include "ShiftRegisterDriver.h"

#define PIN_LED_OUT (13)
#define HALL_SENSOR_MASK  (0x1)   // Bit 0 of [7:0] shift register read

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(PIN_LED_OUT, OUTPUT);
  pinMode(PIN_CLK_OUT, OUTPUT);
  pinMode(PIN_CLK_INH_OUT, OUTPUT);
  pinMode(PIN_SHIFT_LOAD_OUT, OUTPUT);
  pinMode(PIN_SERIAL_IN, INPUT);

  // Initialize shift register control signals
  digitalWrite(PIN_CLK_OUT, LOW);
  digitalWrite(PIN_CLK_INH_OUT, HIGH);
  digitalWrite(PIN_SHIFT_LOAD_OUT, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t shift_reg_value = read_shift_register();
  print_shift_register(shift_reg_value);

  // Check if magnet is present
  uint8_t magnet_present = !(shift_reg_value & HALL_SENSOR_MASK);
  digitalWrite(PIN_LED_OUT, magnet_present);
  magnet_present != 0 ? Serial.println("-- MAGNET") : Serial.println("-- NONE");
  delay(100);
}
