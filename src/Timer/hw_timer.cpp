
#include "Timer/hw_timer.h"

hw_timer_t* HW_Timer::m_timer = nullptr;
SemaphoreHandle_t HW_Timer::m_xBinarySemaphore;

void HW_Timer::processTimer(void* parameter) {
    while (1)
    {
        xSemaphoreTake(m_xBinarySemaphore, portMAX_DELAY);
        // read bmp
    }
}
