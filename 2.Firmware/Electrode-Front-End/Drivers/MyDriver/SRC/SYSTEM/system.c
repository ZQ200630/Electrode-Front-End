#include <system.h>
#define CPU_FREQUENCY_MHZ    48

void MyDelayUs(int Delay) {
    int last, curr, val;
    int temp;

    while (Delay != 0)
    {
        temp = Delay > 900 ? 900 : Delay;
        last = SysTick->VAL;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = SysTick->VAL;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = SysTick->VAL;
            }
            while ((val <= last) || (val > curr));
        }
        Delay -= temp;
    }
}


void MyDelayMs(int Delay) {
    HAL_Delay(Delay);
}
