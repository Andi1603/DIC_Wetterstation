#ifndef HWCONNECTOR_H
#define HWCONNECTOR_H

#include <stdint.h>

class HwConnector {
public:
    virtual bool device_available() const = 0;
    virtual void write_to(uint8_t register_add, uint8_t value) = 0;
    virtual void read_from(uint8_t register_add) = 0;
};

#endif