#ifndef I2C_HELPER_H_
#define I2C_HELPER_H_

#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>
#include <pins_arduino.h>
#include <set>
#include <map>
#include <algorithm>
#include "I2CDef.h"

#define DEBUG_TWI

using namespace std;

class I2C_Helper : private TwoWire {
    
    public:

        //STATIC
        //each I2C bus uses "one" I2C_Helper object
        // each I2C_comm is assigned to one device of I2C BUS(i)
        inline static I2C_Helper *get(uint8_t busNumber){

            auto it = I2C_Helper::_myI2CBusList.find(busNumber);
            if (it == _myI2CBusList.end()){
                //I2C_Helper * not found in _myI2CBusList
                I2C_Helper::_myI2CBusList[busNumber] = new I2C_Helper(busNumber);
            }
            return I2C_Helper::_myI2CBusList[busNumber];
        }

        inline static bool remove(uint8_t bus_number) {
            return true;
        }

    private:
        I2C_Helper(uint8_t busNumber);
        virtual ~I2C_Helper();

        static const uint8_t _MAX_I2CADD = 0x7E;
        static std::map<uint8_t, I2C_Helper * > _myI2CBusList;

        std::set<uint8_t> _listOfDevices;
        uint8_t _busNumber;

        bool scan();                // fills list of available I2C devices of the actual I2C BUS
    public: 
        bool deviceAvailable(uint8_t dec_add) const;
        void writeTo(uint8_t devAdd, uint8_t regAdd, uint8_t val);
        void readFrom(uint8_t devAdd, uint8_t regAdd, uint8_t * const buffer, uint8_t len);
};

#endif