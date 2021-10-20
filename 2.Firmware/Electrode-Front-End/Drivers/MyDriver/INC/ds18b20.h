/**
  ******************************************************************************
  * @file			bsp_ds18b20.h
  * @author		
  * @date			
  * @version	    v1.0
  * @note			DS18B20 driver
  ******************************************************************************
  */
 
#ifndef __BSP_DS18B20_H
#define __BSP_DS18B20_H
 
#include "conf.h"
#include "main.h"
#include "system.h"
 
#define BSP_DS18B20_PORT             TEMP_SENSOR_GPIO_Port
#define BSP_DS18B20_PIN                TEMP_SENSOR_Pin
 
#define DS18B20_OUT_1                HAL_GPIO_WritePin(BSP_DS18B20_PORT, BSP_DS18B20_PIN, GPIO_PIN_SET)
#define DS18B20_OUT_0                HAL_GPIO_WritePin(BSP_DS18B20_PORT, BSP_DS18B20_PIN, GPIO_PIN_RESET)
 
#define DS18B20_IN			        HAL_GPIO_ReadPin(BSP_DS18B20_PORT, BSP_DS18B20_PIN)
 
uint8_t DS18B20_Init(void);
void DS18B20_ReadId(uint8_t *ds18b20_id);
float DS18B20_GetTemp_SkipRom(void);
float DS18B20_GetTemp_MatchRom(uint8_t * ds18b20_id);
 
#endif	/* __BSP_DS18B20_H */


