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

#include "port.h"
#include "usart.h"

/* ----------------------- Modbus includes ----------------------------------*/
#include "mb.h"
#include "mbport.h"

uint8_t uartbuf[10];
CHAR byte_rx;
CHAR byte_tx;

uint8_t flag = 0;

/* ----------------------- static functions ---------------------------------*/
//static void prvvUARTTxReadyISR( void );
static void prvvUARTRxISR( void );

/* ----------------------- Start implementation -----------------------------*/
void
vMBPortSerialEnable( BOOL xRxEnable, BOOL xTxEnable )
{
    /* If xRXEnable enable serial receive interrupts. If xTxENable enable
     * transmitter empty interrupts.
     */
		if (xRxEnable) {
			HAL_UART_Receive_IT(&huart1, uartbuf, 1);
		//__HAL_UART_ENABLE_IT(&huart1, UART_IT_RXNE);		 //使能接收寄存器非空中断
		//HAL_GPIO_WritePin(RS485_DE_GPIO_Port, RS485_DE_Pin, GPIO_PIN_RESET); //MAX485操作 低电平为接收模式
	} else {
		//__HAL_UART_DISABLE_IT(&huart1, UART_IT_RXNE);		//禁能接收寄存器非空中断
		//HAL_GPIO_WritePin(RS485_DE_GPIO_Port, RS485_DE_Pin, GPIO_PIN_SET); //MAX485操作 高电平为发送模式
	}
	if (TRUE == xTxEnable) {
		flag = 0;
		HAL_UART_Transmit_IT(&huart1, uartbuf, 1);
		//HAL_GPIO_WritePin(RS485_DE_GPIO_Port, RS485_DE_Pin, GPIO_PIN_SET); //MAX485操作 高电平为发送模式
		//__HAL_UART_ENABLE_IT(&huart1, UART_IT_TC);      //使能发送完成中断
	} else {
		flag = 1;
		//__HAL_UART_DISABLE_IT(&huart1, UART_IT_TC);   //禁能发送完成中断
	}
	
}

BOOL
xMBPortSerialInit( UCHAR ucPORT, ULONG ulBaudRate, UCHAR ucDataBits, eMBParity eParity )
{
	huart1.Instance = USART1;
  huart1.Init.BaudRate = ulBaudRate;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	switch(eParity)
	    {
		// 奇校验
	    case MB_PAR_ODD:
	        huart1.Init.Parity = UART_PARITY_ODD;
	        huart1.Init.WordLength = UART_WORDLENGTH_9B;			// 带奇偶校验数据位为9bits
	        break;
		// 偶校验
	    case MB_PAR_EVEN:
	        huart1.Init.Parity = UART_PARITY_EVEN;
	        huart1.Init.WordLength = UART_WORDLENGTH_9B;			// 带奇偶校验数据位为9bits
	        break;
		// 无校验
	    default:
	        huart1.Init.Parity = UART_PARITY_NONE;
	        huart1.Init.WordLength = UART_WORDLENGTH_8B;			// 无奇偶校验数据位为8bits
	        break;
	    }
  return HAL_UART_Init(&huart1) == HAL_OK ? TRUE : FALSE;
	
	
	//HAL_GPIO_WritePin(RS485_DE_GPIO_Port, RS485_DE_Pin, GPIO_PIN_RESET); //MAX485操作 低电平为接收模式
	
}

BOOL
xMBPortSerialPutByte( CHAR ucByte )
{
    /* Put a byte in the UARTs transmit buffer. This function is called
     * by the protocol stack if pxMBFrameCBTransmitterEmpty( ) has been
     * called. */
	uartbuf[0] = ucByte;
    return TRUE;
}

BOOL
xMBPortSerialGetByte( CHAR * pucByte )
{
    /* Return the byte in the UARTs receive buffer. This function is called
     * by the protocol stack after pxMBFrameCBByteReceived( ) has been called.
     */
		*pucByte = byte_rx;
    return TRUE;
}

/* Create an interrupt handler for the transmit buffer empty interrupt
 * (or an equivalent) for your target processor. This function should then
 * call pxMBFrameCBTransmitterEmpty( ) which tells the protocol stack that
 * a new character can be sent. The protocol stack will then call 
 * xMBPortSerialPutByte( ) to send the character.
 */
//static void prvvUARTTxReadyISR( void )
//{
//    pxMBFrameCBTransmitterEmpty(  );
//}

/* Create an interrupt handler for the receive interrupt for your target
 * processor. This function should then call pxMBFrameCBByteReceived( ). The
 * protocol stack will then call xMBPortSerialGetByte( ) to retrieve the
 * character.
 */
static void prvvUARTRxISR( void )
{
    pxMBFrameCBByteReceived(  );
}


void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	byte_rx = uartbuf[0];
	prvvUARTRxISR();
	HAL_UART_Receive_IT(&huart1, uartbuf, 1);
	
	}

//void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart) {
//	prvvUARTTxReadyISR();
//	if(flag == 0) {
//	HAL_UART_Transmit_IT(&huart1, uartbuf, 1);
//	}
//}
