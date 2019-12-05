
#include "Timer/HW_Timer.h"

uint8_t HW_Timer::_counter = 0;  // initialisation of _counter
hw_timer_t * HW_Timer::_timer = NULL;
HW_Timer::HW_TIMER_INDEX HW_Timer::_hwTimerIndex = HW_Timer::HW_TIMER_INDEX::TIMER1;
uint16_t HW_Timer::_prescaler = 0;
uint64_t HW_Timer::_overflow = 0;


SemaphoreHandle_t HW_Timer::xBinarySemaphore;  // global var


// child process
void HW_Timer::HW_Timer::processTimer( void * parameter = 0 )
{
	Serial.printf( "Start child process<%s>\n", __FUNCTION__ );
	// endless loop
	for(;;)
	{
			xSemaphoreTake( HW_Timer::xBinarySemaphore, portMAX_DELAY);
			
			// read temperature, pressure, highvideo
			_counter++;
			_counter = _counter%256;
			
			Serial.printf( "<%s> counter:<%x>\n", __FUNCTION__, _counter );
			// read data from sensor
			
	}
}

bool HW_Timer::initialize( HW_TIMER_INDEX hwTimerIndex, uint16_t prescaler,
			uint64_t overflow )
{
		_hwTimerIndex    = hwTimerIndex;
		uint8_t taskCore = 1; // CORE 1
		_overflow        = overflow;
		_prescaler       = prescaler;
		
		HW_Timer::xBinarySemaphore = xSemaphoreCreateBinary();
		
		xTaskCreatePinnedToCore( 
				processTimer,      // function of child process, usually endless loop
				"processTimer",    // name of the child processTimer
				4000,              // stack size
				NULL,              // no need of parameters
				10,                // priority of the taskCore
				NULL,
				taskCore           // number of the core of ESP32: 0 or 1 allowed
		);
		_counter = 0;
		startTimer();
}

// wake up by timer overflow (1s)
void IRAM_ATTR HW_Timer::onTimer()   // keep in RAM
{
	ets_intr_lock();	
	BaseType_t xHigherPriorityTaskWoken = pdTRUE;

	// wake up child process
	xSemaphoreGiveFromISR( HW_Timer::xBinarySemaphore, &xHigherPriorityTaskWoken );
	Serial.printf( "hallo Interrupt\n" );
	ets_intr_unlock();
}

void HW_Timer::startTimer()
{
	Serial.printf( "Start timer\n" );
	_timer = timerBegin(_hwTimerIndex, _prescaler, COUNTER_UP );
	timerAttachInterrupt( _timer, onTimer /* pointer to function */, RISING_EDGE );
	timerAlarmWrite( _timer, _overflow, AUTORELOAD );
	
	// turn on timer
	timerAlarmEnable(  _timer );
}

void HW_Timer::changePrescaler( uint16_t prescaler )
{
}

void HW_Timer::changeOverflow( uint64_t overflow )
{
}

void HW_Timer::endTimer()
{
}