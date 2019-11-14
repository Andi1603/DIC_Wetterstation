/*
 * I2Ccomm.cpp
 *
 *  Created on: 26.02.2017
 *      Author: reinhard
 */

#include "I2C_Comm.h"


I2C_Comm::I2C_Comm(uint8_t bus_number, uint8_t dev_addr) :
	_bus_number(bus_number),
	_dev_addr(dev_addr)
{
	_i2c_helper = I2C_Helper::get( bus_number );
#ifdef DEBUG_TWI
	Serial.printf( "<%s> I2C constructor\n", __FUNCTION__);
#endif

	_devAvailable = I2C_Helper::get(bus_number)->devAvailable(dev_addr);
}

bool I2C_Comm::writeTo( uint8_t const regAdd, uint8_t * const buf,  uint8_t const len )
{
#ifdef DEBUG_TWI
	Serial.printf( "************************************\n");
	Serial.printf( "I2C_Comm::writeTo: device Address:<%x> register address; <%x> register value <%x> ... num of bytes <%d> \n", _dev_addr, regAdd, buf[0], len );
	Serial.printf( "************************************\n");
#endif

	if ( _devAvailable )
		return _i2c_helper->writeTo(_dev_addr, regAdd, buf, len);

	return false;
}

bool I2C_Comm::writeTo( uint8_t regAdd, uint8_t val )
{
	if ( _devAvailable )
		return _i2c_helper->writeTo(_dev_addr, regAdd, val);

	return false;
}

bool I2C_Comm::readFrom(  uint8_t const regAdd, uint8_t * const buffer, uint8_t const len )
{
	if ( _devAvailable )
		return _i2c_helper->readFrom(_dev_addr, regAdd, buffer, len);

	return false;
}

bool I2C_Comm::deviceAvailable() const
{
	if ( _devAvailable )
		return _devAvailable; // I2C_Helper::get(_bus_number)->devAvailable(_dev_addr);

	return false;
}




