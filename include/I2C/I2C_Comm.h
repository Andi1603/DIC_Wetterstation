/*
 * I2Ccomm.h
 *
 *  Created on: 26.02.2017
 *      Author: reinhard
 */

#ifndef I2CCOMM_H_
#define I2CCOMM_H_

#include <Arduino.h>
#include <ArduinoLog.h>

// #include "../global/global.h"
#include "../hwConnector/hwConnector.h"
// #include "I2C_Helper.h"

using namespace std;

class I2C_Comm : public hwConnector  // each device on BUS(i) is assigned to one  I2C_Comm
{
private:

	I2C_Helper * _i2c_helper;
    uint8_t      _bus_number;
    uint8_t      _dev_addr;  // illegal: address > 0x7F
    bool         _devAvailable;

public:

    I2C_Comm(uint8_t bus_number, uint8_t dev_addr );
    virtual ~I2C_Comm() 
    {
        Log.verbose("<%s> destructor I2C_Comm\n", __FUNCTION__ );
    }

    bool writeTo(  uint8_t regAdd,  uint8_t * const buf,  uint8_t const len );
    bool writeTo(  uint8_t regAdd, uint8_t val );
    bool readFrom( uint8_t regAdd,  uint8_t * const buffer, uint8_t const len );
    bool deviceAvailable () const;
};

#endif /* I2CCOMM_H_ */
