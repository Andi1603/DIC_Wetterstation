#ifndef HW_TIMER_H
#define HW_TIMER_H

#include <Arduino.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include "HW_Connector.h"


using namespace std;

class HW_Timer
{
	public :

		enum HW_TIMER_INDEX
		{
			TIMER1 = 1,
			TIMER2,
			TIMER3
		};
		
	private :
	
	static const uint8_t clk_frequ = 80;  // 80MHz
	static const bool RISING_EDGE  = true;
	static const bool falling_edge = false;
	static const bool AUTORELOAD   = true;
	static const bool COUNTER_UP   = true;
	static const bool counter_down = false;
	
	static hw_timer_t *   _timer;
	static HW_TIMER_INDEX _hwTimerIndex;
	static uint16_t       _prescaler;  // Timer works with fosz/3 = 240MHz/3 = 80MHz
	static uint64_t       _overflow;
	static uint8_t        _counter;
	
	static SemaphoreHandle_t xBinarySemaphore;
	
	public:
	
		static bool initialize( HW_TIMER_INDEX hwTimerIndex, uint16_t prescaler = 80,
			uint64_t overflow = 1000000 ); // default: 1s
			
		static void startTimer();
		static void endTimer();
		static void changePrescaler( uint16_t prescaler );
		static void changeOverflow( uint64_t overflow );
		static void processTimer( void * parameter = 0);  // child process
		static void IRAM_ATTR onTimer(); // interrupt routine keep in RAM
	
};

#endif