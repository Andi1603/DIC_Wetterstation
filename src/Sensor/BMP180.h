#ifndef BMP180_H
#define BMP180_H

#include <stdint.h>

enum BMP180_Resolution {
    ULTRA_LOW_POWER = 0, // lower resolution, faster, lower current drain
    STANDARD = 1,
    HIGH_RESOLUTION = 2,
    ULTRA_HIGH_RESOLUTION = 3 // higher resolution, slower, higher current drain
};

// Variables have to be prefixed with BMP180 because of a disruptive define in a 
// library header file.
struct BMP180_EEPROM {
    int16_t BMP180_AC1;
    int16_t BMP180_AC2;
    int16_t BMP180_AC3;
    uint16_t BMP180_AC4;
    uint16_t BMP180_AC5;
    uint16_t BMP180_AC6;
    int16_t BMP180_B1;
    int16_t BMP180_B2;
    int16_t BMP180_MB;
    int16_t BMP180_MC;
    int16_t BMP180_MD;
};

class BMP180 {
public:
    BMP180();
    virtual ~BMP180() {}

    float getTemperature();
    float getAltitude();
    long getPressure(BMP180_Resolution resolution = STANDARD);
private:
    static const uint8_t device_address = 0x77;
    static const long pressure_sea_level = 101325L;
    BMP180_EEPROM m_calibrationParameter;

    void readCalibrationParameter();
    long readUncompensatedTemperature();
    long readUncompensatedPressure(BMP180_Resolution resolution);
};

#endif