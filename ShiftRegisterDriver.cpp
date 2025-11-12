#include "ShiftRegisterDriver.h"

#define LOAD_TIME_MSEC    (1)     // Delay to load data into shift register
#define NUM_BITS          (8)     // 8-bit shift register
#define READ_FREQ_HZ      (100)   // 100 Hz = 10 msec clk period
#define HALL_SENSOR_MASK  (0x1)   // Bit 0 of [7:0] shift register read

uint8_t read_shift_register() {
  float clock_period_msec = 1000.0f / READ_FREQ_HZ;
  uint16_t clock_half_period_msec = (uint16_t)(clock_period_msec/2.0f);
  
  // Check minimum clock frequency and set to 1 msec
  if(clock_half_period_msec == 0) {
    clock_half_period_msec = 1;
  }

  // Load data from parallel inputs into shift register
  digitalWrite(PIN_SHIFT_LOAD_OUT, LOW);
  delay(LOAD_TIME_MSEC);
  digitalWrite(PIN_SHIFT_LOAD_OUT, HIGH);

  // Set CLK_INH to LOW to allow data shift
  digitalWrite(PIN_CLK_INH_OUT, LOW);
  delay(LOAD_TIME_MSEC);

  // Read Shift Register
  uint8_t ret_value = 0;
  for(uint8_t i=0; i<NUM_BITS; i++) {
    ret_value = (ret_value << 1) | digitalRead(PIN_SERIAL_IN);
    delay(clock_half_period_msec); 
    digitalWrite(PIN_CLK_OUT, HIGH);
    delay(clock_half_period_msec);
    digitalWrite(PIN_CLK_OUT, LOW);
  }

  // Reset CLK_INH to HIGH after data shift complete
  digitalWrite(PIN_CLK_INH_OUT, HIGH);

  return ret_value;
}

void print_shift_register(uint8_t reg_value) {
  // Print results of shift register
  Serial.print("Shift Reg: 8'b");
  for (int i=(NUM_BITS-1); i >= 0; i--) {        // Loop over each bit from MSB to LSB
    Serial.print((reg_value >> i) & 0x1);  // Extract and print each bit
  }

  // Check if magnet is present
  uint8_t mag_present = !(reg_value & HALL_SENSOR_MASK);
  mag_present != 0 ? Serial.print(" : MAGNET") : Serial.print(" : NONE");
  Serial.println();
}