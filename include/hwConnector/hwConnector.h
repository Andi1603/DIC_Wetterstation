/*
 * hwConnector.h
 *
 *  Created on: 27.09.2019
 *      Author: reinhard
 */

#ifndef HWDEVICE_HWCONNECTOR_H_
#define HWDEVICE_HWCONNECTOR_H_

#include <stdint.h>

class hwConnector
{

private:

public:

	virtual ~hwConnector() {};

    virtual bool writeTo(  uint8_t regAdd,  uint8_t * const buf,  uint8_t const len ) = 0;
    virtual bool writeTo(  uint8_t regAdd, uint8_t val ) = 0;
    virtual bool readFrom( uint8_t regAdd,  uint8_t * const buffer, uint8_t const len ) = 0;
    virtual bool deviceAvailable () const = 0;
};


#endif /* HWDEVICE_HWCONNECTOR_H_ */
