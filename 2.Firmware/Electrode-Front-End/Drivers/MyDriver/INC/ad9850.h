/*--------------------------------------------

            AD9850驱动程序

----------------------------------------------*/

#ifndef __AD9850_H
#define __AD9850_H

#include "system.h"

/*选择数据通信方式，只能选择一个*/
#define MODE_SEIAL   //串行模式
//#define MODE_PARALLEL  //并行模式

/* AD9850 控制和数据引脚定义 */
#define MY_AD9850_CONTROL_PORT      GPIOA
#define MY_AD9850_FQUD_PIN          GPIO_PIN_4
#define MY_AD9850_WCLK_PIN          GPIO_PIN_5
#define MY_AD9850_RST_PIN           GPIO_PIN_6

#ifdef MODE_PARALLEL  //并行模式数据口0~7
#define MY_AD9850_DATA_PORT_PARALLEL  GPIOC
#endif

#ifdef MODE_SEIAL   //串行模式数据口
#define MY_AD9850_DATA_PORT_SERIAL GPIOA
#define MY_AD9850_DATA_PIN GPIO_PIN_7
#endif

#define MY_AD9850_SYSTEM_COLCK     80000000
//#define MY_AD9850_SYSTEM_COLCK     100000000

#ifdef MODE_SEIAL   //串行模式数据口
void MyOperateDataSerial(MY_PinState PinState);
#endif

void MyOperateWCLK(MY_PinState PinState);

void MyOperateFQUD(MY_PinState PinState);

void MyOperateRST(MY_PinState PinState);

char MyCalculatePhase(int phase);

void MyOperateDataParallel(unsigned char W0);

/* 串行模式操作函数 */
#ifdef MODE_SEIAL
void MyAD9850ResetSreial(void) ;
void MyAD9850WriteSerial(unsigned char W0,unsigned long freq) ;
#endif

/* 并行模式操作函数 */
#ifdef MODE_PARALLEL
void MyAD9850ResetParallel(void) ;
void MyAD9850WriteParallel(unsigned char W0,unsigned long freq) ;
#endif

void AD9850_Init(void) ;

#endif /* AD8950_H */
