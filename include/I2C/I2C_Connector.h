#ifndef I2C_CONNECTOR_H
#define I2C_CONNECTOR_H

#include "HW_Connector.h"
#include "I2C_Helper.h"

class I2C_Connector : public HW_Connector {
public:
    I2C_Connector(uint8_t bus_number, uint8_t device_add);
    virtual ~I2C_Connector() {}

    virtual bool device_available() const override;
    virtual void write_to(uint8_t register_add, uint8_t value) override;
    virtual uint8_t read_from(uint8_t register_add) override;
private:
    uint8_t m_device_add;
    I2C_Helper* m_i2c_helper;
};

#endif