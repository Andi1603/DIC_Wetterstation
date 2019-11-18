#include "I2C_Helper.h"

std::map<uint8_t, I2C_Helper* > I2C_Helper::_myI2CBusList = {};

I2C_Helper::I2C_Helper(uint8_t busNumber) 
    : TwoWire(busNumber & 0x01), _busNumber(busNumber) {
    _listOfDevices = {};
    switch(busNumber & 0x01){
        case 0: begin(SDA, SCL, TWI_CLK0); break;
        case 1: begin(SDA1, SCL1, TWI_CLK1); break;     //actually not used
        default: break;
    }
    scan();
}

I2C_Helper::~I2C_Helper(){
    #ifdef DEBUG_TWI
        Serial.printf("<%s> Destructor\n", __FUNCTION__);
    #endif
}

bool I2C_Helper::scan(){
    //take each possible dev_add and look if ACK of device is set to zero
    uint8_t error = 0;
    for(uint8_t dev_add = 1; dev_add <= _MAX_I2CADD; dev_add++){
        beginTransmission(dev_add);
        error = endTransmission(true);

        if (error == 0) {
            Serial.printf("<%s> device found at <%x>\n", __FUNCTION__, dev_add);
            _listOfDevices.insert(dev_add);
        }
    }
    return true;
}

bool I2C_Helper::deviceAvailable(uint8_t devAdd) const {
    auto it = _listOfDevices.find(devAdd);
    return it != _listOfDevices.end();
}

void I2C_Helper::writeTo(uint8_t devAdd, uint8_t regAdd, uint8_t val) {
    const uint8_t bufferTr[] = { regAdd, val };
    beginTransmission(devAdd);
    write(bufferTr, 2);
    endTransmission();
}

void I2C_Helper::readFrom(uint8_t devAdd, uint8_t regAdd, uint8_t* const buffer, uint8_t len) {
    const uint8_t bufferTr[] = { regAdd };
    beginTransmission(devAdd);
    write(bufferTr, 1);
    endTransmission();

    beginTransmission(devAdd);
    requestFrom(devAdd, len);
    for (int i = 0; i < len && available(); i++)
    {
        buffer[i] = read();
    }
}