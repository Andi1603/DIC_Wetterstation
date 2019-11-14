#include <Arduino.h>
#include "Sensor/BMP180.h"

BMP180 sensor;

void setup() {
    sensor.getTemperature();
}

void loop() {
}