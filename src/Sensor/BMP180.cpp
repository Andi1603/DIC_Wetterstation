
#include <math.h>
#include "BMP180.h"

BMP180::BMP180(HW_Connector& connector) 
    : m_hw_connector(&connector) {
    readCalibrationParameter();
}

float BMP180::getTemperature() {
    int64_t ut, x1, x2, b5, temperature;
    ut = readUncompensatedTemperature();
    x1 = (ut - m_calibrationParameter.BMP180_AC6) * m_calibrationParameter.BMP180_AC5 / 32768;
    x2 = m_calibrationParameter.BMP180_MC * 2048 / (x1 + m_calibrationParameter.BMP180_MD);
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
    up = readUncompensatedPressure((int16_t)resolution);
    
    // Calculations taken from the datasheet
    x1 = (ut - m_calibrationParameter.BMP180_AC6) * m_calibrationParameter.BMP180_AC5 / 32768;
    x2 = m_calibrationParameter.BMP180_MC * 2048 / (x1 + m_calibrationParameter.BMP180_MD);
    b5 = x1 + x2;
    b6 = b5 - 4000;
    x1 = (m_calibrationParameter.BMP180_B2 * (b6 * b6 / 4096)) / 2048;
    x2 = m_calibrationParameter.BMP180_AC2 * b6 / 2048;
    x3 = x1 + x2;
    b3 = (((m_calibrationParameter.BMP180_AC1 * 4 + x3) << (int16_t)resolution) + 2) / 4;
    x1 = m_calibrationParameter.BMP180_AC3 * b6 / 8192;
    x2 = (m_calibrationParameter.BMP180_B1 * (b6 * b6 / 4096)) / 65536;
    x3 = ((x1 + x2) + 2) / 4;
    b4 = m_calibrationParameter.BMP180_AC4 * (uint64_t)(x3 + 32768) / 32768;
    b7 = ((uint64_t)up - b3) * (50000 >> (int16_t)resolution);
    p = (b7 < 0x80000000) ? ((b7 * 2) / b4) : ((b7 / b4) * 2);
    x1 = (p / 256) * (p / 256);
    x1 = (x1 * 3038) / 65536;
    x2 = (-7357 * p) / 65536;
    return p + (x1 + x2 + 3791) / 16; // pressure in Pa
}

float BMP180::getAltitude(BMP180_Resolution resolution) {
    return 44330 * (1 - pow((double)getPressure(resolution) / (double)pressure_sea_level, 1.0 / 5.255)); // altitude in m relative to the sea level
}

void BMP180::readCalibrationParameter() {
    m_calibrationParameter.BMP180_AC1 = ((uint16_t) m_hw_connector->read_from(0xAA) << 8) + m_hw_connector->read_from(0xAB);
    m_calibrationParameter.BMP180_AC2 = ((uint16_t) m_hw_connector->read_from(0xAC) << 8) + m_hw_connector->read_from(0xAD);
    m_calibrationParameter.BMP180_AC3 = ((uint16_t) m_hw_connector->read_from(0xAE) << 8) + m_hw_connector->read_from(0xAF);
    m_calibrationParameter.BMP180_AC4 = ((uint16_t) m_hw_connector->read_from(0xB0) << 8) + m_hw_connector->read_from(0xB1);
    m_calibrationParameter.BMP180_AC5 = ((uint16_t) m_hw_connector->read_from(0xB2) << 8) + m_hw_connector->read_from(0xB3);
    m_calibrationParameter.BMP180_AC6 = ((uint16_t) m_hw_connector->read_from(0xB4) << 8) + m_hw_connector->read_from(0xB5);
    m_calibrationParameter.BMP180_B1  = ((uint16_t) m_hw_connector->read_from(0xB6) << 8) + m_hw_connector->read_from(0xB7);
    m_calibrationParameter.BMP180_B2  = ((uint16_t) m_hw_connector->read_from(0xB8) << 8) + m_hw_connector->read_from(0xB9);
    m_calibrationParameter.BMP180_MB  = ((uint16_t) m_hw_connector->read_from(0xBA) << 8) + m_hw_connector->read_from(0xBB);
    m_calibrationParameter.BMP180_MC  = ((uint16_t) m_hw_connector->read_from(0xBC) << 8) + m_hw_connector->read_from(0xBD);
    m_calibrationParameter.BMP180_MD  = ((uint16_t) m_hw_connector->read_from(0xBE) << 8) + m_hw_connector->read_from(0xBF);
}

int64_t BMP180::readUncompensatedTemperature() {
    m_hw_connector->write_to(0xF4, 0x2E);
    delay(5); // TODO: replace delay
    return ((int16_t) m_hw_connector->read_from(0xF6) << 8) + m_hw_connector->read_from(0xF7);
}

int64_t BMP180::readUncompensatedPressure(int16_t oss) {
    m_hw_connector->write_to(0xF4, 0x34 + (oss << 6));
    delay(26); // TODO: replace delay and check oss
    int32_t msb = m_hw_connector->read_from(0xF6);
    int32_t lsb = m_hw_connector->read_from(0xF7);
    int32_t xlsb = m_hw_connector->read_from(0xF8);
    return ((msb<<16) + (lsb<<8) + (xlsb)) >> (8-oss);
}