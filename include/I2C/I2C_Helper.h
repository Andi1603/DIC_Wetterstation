#ifndef I2C_HELPER
#define I2C_HELPER

#include <Arduino.h>
#include <pins_arduino.h>
#include <Wire.h>
#include <map>
#include <set>
#include <algorithm>

#include "I2CDef.h"

class I2C_Helper : private TwoWire {
public:
    virtual ~I2C_Helper();

    inline static I2C_Helper* get(uint8_t bus_number) {
        return nullptr;
    }

    bool device_available(uint8_t dev_add) const;
    bool write_to(uint8_t dev_add, uint8_t reg_add, uint8_t * const buffer, uint8_t len);
    bool write_to(uint8_t dev_add, uint8_t reg_add, uint8_t val);
    bool read_from(uint8_t dev_add, uint8_t reg_add, uint8_t * const buffer, uint8_t len);

private:
    static const uint8_t MAX_I2CADD = 0x7F;
    static std::map<uint8_t, I2C_Helper* const> m_helpers;
    std::set<uint8_t> m_list_of_devices;

    I2C_Helper(uint8_t bus_number);
    bool scan(); 
};

#endif