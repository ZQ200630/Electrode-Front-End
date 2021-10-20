/*
 * FreeModbus Libary: BARE Port
 * Copyright (C) 2006 Christian Walter <wolti@sil.at>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * File: $Id$
 */

/* ----------------------- Platform includes --------------------------------*/
#include "port.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

#include "tim.h"

extern uint32_t ADC0Buffer[10];
extern uint32_t ADC1Buffer[10];
extern uint32_t ADC2Buffer[10];
extern uint32_t ADC3Buffer[10];
extern uint32_t ADC_0;
extern uint32_t ADC_1;
extern uint32_t ADC_2;
extern uint32_t ADC_3;

extern float ADC_0_REAL;
extern float ADC_1_REAL;
extern float ADC_2_REAL;
extern float ADC_3_REAL;

//extern  uint16_t UART_TRANS_BUFFER[4];
extern uint16_t usRegHoldingBuf[4];

/* ----------------------- static functions ---------------------------------*/
static void prvvTIMERExpiredISR( void );

/* ----------------------- Start implementation -----------------------------*/
BOOL
xMBPortTimersInit( USHORT usTim1Timerout50us )
{
	htim14.Instance = TIM14;
	  htim14.Init.Prescaler = 2399;
	  htim14.Init.CounterMode = TIM_COUNTERMODE_UP;
	  htim14.Init.Period = usTim1Timerout50us - 1;
	  htim14.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	  htim14.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	  if (HAL_TIM_Base_Init(&htim14) != HAL_OK)
	  {
		  return FALSE;
	  }
    return TRUE;
}


inline void
vMBPortTimersEnable(  )
{
    /* Enable the timer with the timeout passed to xMBPortTimersInit( ) */
	__HAL_TIM_SET_COUNTER(&htim14, 0);	// 清空计数器
	__HAL_TIM_CLEAR_FLAG(&htim14,TIM_FLAG_UPDATE);
	//__HAL_TIM_ENABLE(&htim14);
	 HAL_TIM_Base_Start_IT(&htim14);     // 使能定时器

}

inline void
vMBPortTimersDisable(  )
{
    /* Disable any pending timers. */
	HAL_TIM_Base_Stop_IT(&htim14);
	//__HAL_TIM_DISABLE(&htim14);	// 禁能定时器
}

/* Create an ISR which is called whenever the timer has expired. This function
 * must then call pxMBPortCBTimerExpired( ) to notify the protocol stack that
 * the timer has expired.
 */
static void prvvTIMERExpiredISR( void )
{
    ( void )pxMBPortCBTimerExpired(  );
}

// 定时器4中断服务程序
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	
	if(htim->Instance == TIM17){
      ADC_0 = 0;
	   ADC_1 = 0;
	   ADC_2 = 0;
	   ADC_3 = 0;
		 
	   for(int i = 0; i < 10; i++) {
			ADC_0 += ADC0Buffer[i];
		   ADC_1 += ADC1Buffer[i];
		   ADC_2 += ADC2Buffer[i];
		   ADC_3 += ADC3Buffer[i];
	   }
	   ADC_0 = ADC_0 / 10;
	   ADC_1 = ADC_1 / 10;
	   ADC_2 = ADC_2 / 10;
	   ADC_3 = ADC_3 / 10;
		
		 ADC_0_REAL = ADC_0/4096.0*3.3;
		 ADC_1_REAL = ADC_1/4096.0*3.3;
		 ADC_2_REAL = ADC_2/4096.0*3.3;
		 ADC_3_REAL = ADC_3/4096.0*3.3;
	   
		 usRegHoldingBuf[0] = ADC_0;
		 usRegHoldingBuf[1] = ADC_1;
		 usRegHoldingBuf[2] = ADC_2;
		 usRegHoldingBuf[3] = ADC_3;
		 
		 //HAL_UART_Transmit(&huart1, (uint8_t *)UART_TRANS_BUFFER, 8, 0xffff);
		 
     }
		 if(htim->Instance == TIM14){
		 prvvTIMERExpiredISR();	// 通知modbus3.5个字符等待时间到
		 }

}


