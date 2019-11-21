#ifndef HW_TIMER_H
#define HW_TIMER_H

#include <Arduino.h>
#include <stdint.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "HW_Connector.h"

enum HW_TIMER_INDEX {
    TIMER1 = 1,
    TIMER2 = 2,
    TIMER3 = 3
};

class HW_Timer {
public:
    static bool initialize(HW_TIMER_INDEX index, uint16_t prescaler = 80, uint64_t overflow = 1000000);
    static void startTimer();
    static void stopTimer();
    static void changePrescaler(uint16_t prescaler);
    static void changeOverflow(uint64_t overflow);
    static void processTimer(void* parameter = nullptr);
    static void IRAM_ATTR onTimer(); // interrupt routine, keep in RAM
private:
    static const bool rising_edge = true;
    static const bool falling_edge = false;
    static const bool autoreload = true;
    static const bool counter_up = true;
    static const bool counter_down = false;
    static const uint16_t prescaler;
    
    static uint8_t m_clk_freq;
    static hw_timer_t* m_timer;
    static HW_TIMER_INDEX m_timer_index;
    static uint64_t m_overflow;
    static uint8_t m_counter;
    static SemaphoreHandle_t m_xBinarySemaphore;
};

#endif