#ifndef STATION_PARAMS_H_
#define STATION_PARAMS_H_

#include <Arduino.h>
#include <String.h>
#include <math.h>
#include <ArduinoLog.h>

using namespace std;

class StationParams
{
	private:
		uint8_t   _header;
		uint8_t   _cnt;
		uint16_t  _temp;  // 0.1 °C
		String   _sJSON;

	public:
		StationParams( uint8_t header, uint8_t cnt, uint16_t temp ) :
			_header(header), _cnt(cnt), _temp(temp)
		{ }

		void setHeader(uint8_t header) { _header = header; }
		void setCnt( uint8_t cnt )     { _cnt = cnt;       }
		void setTemp( int16_t temp )   { _temp = temp;     }

		uint8_t getHeader() { return _header; }
		uint8_t getTemp()   { return _temp;   }
		int16_t get_cnt()   { return _cnt;    }

		String serialize() const
		{
			String H(_header);
			String CNT(_cnt);
			String TEMP(_temp);

			return "Header:<" + H + ">, CNT:<" + CNT + ">, POS:<" + TEMP +  ">";
		}

		String& serialize2JSONEX()
		{
			String H(_header);
			String CNT(_cnt);
			String TEMP(_temp);

			// build JSon String
			_sJSON  = "{\"d\":{ "\
					    "\"H\":\""  + H + "\", "\
						"\"C\":\""  + CNT + "\", "\
						"\"T\":\""  + TEMP + "\" "\
						"} }";
			return _sJSON;
		}
};

#endif