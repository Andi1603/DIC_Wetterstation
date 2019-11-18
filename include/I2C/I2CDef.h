/*
 * I2CDef.h
 *
 *  Created on: 16.08.2019
 *      Author: reinhard
 */

#ifndef I2C_I2CDEF_H_
#define I2C_I2CDEF_H_

#include <Arduino.h>


// SDA, SCL for bus 0 is defined in pin_arduino.h

#define DEBUG_TWI


//#define SDA1 (17)
//#define SCL1 (16)

//#define TWI_CLK0 (100000)
//#define TWI_CLK1 (100000)

static const unsigned long TWI_CLK0 = 100000;
static const unsigned long TWI_CLK1 = 100000;

static const uint8_t SDA1 = 17;
static const uint8_t SCL1 = 16;

// 0, 1 available i2c bus devices
#define TW_BUSMASK 0x01
#define NUM_TW 0x01

#endif /* I2C_I2CDEF_H_ */