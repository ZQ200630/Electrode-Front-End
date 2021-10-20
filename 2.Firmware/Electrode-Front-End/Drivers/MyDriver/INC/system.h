#ifndef __SYS_H
#define __SYS_H

#include "stm32f0xx_hal.h"

typedef enum
{
    MY_PIN_RESET = 0,
    MY_PIN_SET = 1
}MY_PinState;

void MyDelayMs(int Delay);
void MyDelayUs(int Delay);

#endif //__SYS_H
