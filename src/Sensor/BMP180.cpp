
#include "BMP180.h"

BMP180::BMP180() {
    readCalibrationParameter();
}

float BMP180::getTemperature() {
    int64_t ut, x1, x2, b5, temperature;
    ut = readUncompensatedTemperature();
    x1 = (ut - m_calibrationParameter.AC6) * m_calibrationParameter.AC5 / 32768;
    x2 = m_calibrationParameter.MC * 2048 / (x1 + m_calibrationParameter.MD);
    b5 = x1 + x2;
    temperature = (b5 + 8) / 16; // temperature in 0.1 C
    return (float) temperature / 10.f; // temperature in C
}

long BMP180::getPressure(BMP180_Resolution resolution) {
    int64_t ut, up, x1, x2, x3, b3, b5, b6, p;
    uint64_t b4, b7;
    // The uncompensated temperature has to be read in order to compute x1.
    // The datasheet is not clearly stating why this parameter requires the temperature to be read. 
    ut = readUncompensatedTemperature();
    up = readUncompensatedPressure(resolution);
    
    // Calculations taken from the datasheet
    x1 = (ut - m_calibrationParameter.AC6) * m_calibrationParameter.AC5 / 32768;
    x2 = m_calibrationParameter.MC * 2048 / (x1 + m_calibrationParameter.MD);
    b5 = x1 + x2;
    b6 = b5 - 4000;
    x1 = (m_calibrationParameter.B2 * (b6 * b6 / 4096)) / 2048;
    x2 = m_calibrationParameter.AC2 * b6 / 2048;
    x3 = x1 + x2;
    b3 = (((m_calibrationParameter.AC1 * 4 + x3) << (int16_t)resolution) + 2) / 4;
    x1 = m_calibrationParameter.AC3 * b6 / 8192;
    x2 = (m_calibrationParameter.B1 * (b6 * b6 / 4096)) / 65536;
    x3 = ((x1 + x2) + 2) / 4;
    b4 = m_calibrationParameter.AC4 * (uint64_t)(x3 + 32768) / 32768;
    b7 = ((uint64_t)up - b3) * (50000 >> (int16_t)resolution);
    p = (b7 < 0x80000000) ? ((b7 * 2) / b4) : ((b7 / b4) * 2);
    x1 = (p / 256) * (p / 256);
    x1 = (x1 * 3038) / 65536;
    x2 = (-7357 * p) / 65536;
    return p + (x1 + x2 + 3791) / 16; // pressure in Pa
}

float BMP180::getAltitude() {
    return 0.0f;
}


void BMP180::readCalibrationParameter() {
    
}

long BMP180::readUncompensatedTemperature() {
    return 0L;
}

long BMP180::readUncompensatedPressure(BMP180_Resolution resolution) {
    return 0L;
}