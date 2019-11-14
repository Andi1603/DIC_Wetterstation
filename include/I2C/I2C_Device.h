#ifndef I2C_DEVICE_H
#define I2C_DEVICE_H

class I2C_Device : public HW_Connector {
public:
    I2C_Device();
    virtual ~I2C_Device() {}

    virtual bool device_available() const;
    virtual void write_to(uint8_t register_add, uint8_t value);
    virtual uint8_t read_from(uint8_t register_add);
private:
    
};

#endif