
#include "I2C_Connector.h"

I2C_Connector::I2C_Connector(uint8_t bus_number, uint8_t device_add) 
    : m_device_add(device_add) {
    
}

bool I2C_Connector::device_available() const {
    return false;
}

void I2C_Connector::write_to(uint8_t register_add, uint8_t value) {

}

uint8_t I2C_Connector::read_from(uint8_t register_add) {
    return 0;
}