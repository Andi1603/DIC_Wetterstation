
#include "BMP180.h"

BMP180::BMP180() {
    readCalibrationParameter();
}

float BMP180::getTemperature() {
    return 0.0f;
}

float BMP180::getAltitude() {
    return 0.0f;
}

long BMP180::getPressure(BMP180_Resolution resolution) {
    return 0L;
}

void BMP180::readCalibrationParameter() {
    
}

long BMP180::readUncompensatedTemperature() {
    return 0L;
}

long BMP180::readUncompensatedPressure() {
    return 0L;
}