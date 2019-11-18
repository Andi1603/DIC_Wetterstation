#include <Arduino.h>
#include "I2C/I2C_Connector.h"
#include "Sensor/BMP180.h"

BMP180* sensor;

void setup() {
    Serial.begin(9600);

    HW_Connector* connector = new I2C_Connector(0, BMP180_DEVICE_ADD);
    sensor = new BMP180(*connector);
    Serial.println("Temperature [°C]\t|\tPressure [Pa]\t|\tAltitude [m]");
}

void loop() {
    Serial.printf("%.1f\t\t\t|\t%ld\t\t|\t%.2f\n", sensor->getTemperature(), sensor->getPressure(), sensor->getAltitude());
    delay(1000);
}