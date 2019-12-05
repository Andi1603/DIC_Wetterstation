#include <Arduino.h>
#include <ArduinoLog.h>

#include "I2C/I2C_Helper.h"
#include "I2C/I2C_Connector.h"
#include "Timer/HW_Timer.h"

bool temp_sensor_available = false;

void setup() {
  
  Serial.begin(115200);
  Log.begin(LOG_LEVEL_VERBOSE, &Serial, true);
  HW_Timer::initialize(HW_Timer::HW_TIMER_INDEX::TIMER1);   // 1s timer
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
}