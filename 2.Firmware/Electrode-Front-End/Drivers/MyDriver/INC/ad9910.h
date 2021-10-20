//
// Created by 张潜 on 2021/7/23.
//

#ifndef AD9910_AD9910_H
#define AD9910_AD9910_H

#include "system.h"


#define MY_AD9910_RST_PIN GPIO_PIN_7
#define MY_AD9910_RST_PORT GPIOE

#define MY_AD9910_PWR_PIN GPIO_PIN_10
#define MY_AD9910_PWR_PORT GPIOD

#define MY_AD9910_PLL_LOCK_PIN GPIO_PIN_1
#define MY_AD9910_PLL_LOCK_PORT GPIOD

#define MY_AD9910_RSO_PIN GPIO_PIN_9
#define MY_AD9910_RSO_PORT GPIOD

#define MY_AD9910_PDCLK_PIN GPIO_PIN_0
#define MY_AD9910_PDCLK_PORT GPIOD

#define MY_AD9910_TXENABLE_PIN GPIO_PIN_8
#define MY_AD9910_TXENABLE_PORT GPIOD

#define MY_AD9910_PF2_PIN GPIO_PIN_15
#define MY_AD9910_PF2_PORT GPIOD

#define MY_AD9910_PF1_PIN GPIO_PIN_15
#define MY_AD9910_PF1_PORT GPIOE

#define MY_AD9910_PF0_PIN GPIO_PIN_14
#define MY_AD9910_PF0_PORT GPIOD

#define MY_AD9910_SYNC_CLK_PIN GPIO_PIN_14
#define MY_AD9910_SYNC_CLK_PORT GPIOE

#define MY_AD9910_IO_UPDATE_PIN GPIO_PIN_5
#define MY_AD9910_IO_UPDATE_PORT GPIOE

#define MY_AD9910_OSK_PIN GPIO_PIN_13
#define MY_AD9910_OSK_PORT GPIOE

#define MY_AD9910_DROVER_PIN GPIO_PIN_6
#define MY_AD9910_DROVER_PORT GPIOE

#define MY_AD9910_DRCTL_PIN GPIO_PIN_12
#define MY_AD9910_DRCTL_PORT GPIOE

#define MY_AD9910_DRHOLD_PIN GPIO_PIN_4
#define MY_AD9910_DRHOLD_PORT GPIOE

#define MY_AD9910_SDIO_PIN GPIO_PIN_11
#define MY_AD9910_SDIO_PORT GPIOE

#define MY_AD9910_SDO_PIN GPIO_PIN_10
#define MY_AD9910_SDO_PORT GPIOE

#define MY_AD9910_SCLK_PIN GPIO_PIN_9
#define MY_AD9910_SCLK_PORT GPIOE

#define MY_AD9910_CSB_PIN GPIO_PIN_8
#define MY_AD9910_CSB_PORT GPIOE

#define uchar unsigned char
#define uint  unsigned int
#define ulong  unsigned long int

//新增IO
//#define SDO PAout(4)
//#define PDCLK PCout(6)//PDCLK
//#define PLL_LOCK PCout(7)//悬空
//#define SYNC_CLK PCout(9)//悬空
//#define TXENABLE PCout(11)//TXEN
//#define RSO PCout(12)//RAM-SWP-OVR
#define AD9910_PWR PCout(13)//0
//原始IO


#define AD9910_SDIO PAout(5)
#define DRHOLD PCout(1)
#define DROVER PCout(2)
#define UP_DAT PCout(3)
#define PROFILE1 PCout(10)
#define MAS_REST PAout(6)//
#define SCLK PAout(2)//
#define DRCTL  PAout(4)//
#define OSK PCout(8)
#define PROFILE0 PCout(4)
#define PROFILE2 PCout(5)
#define CS  PBout(10)//



//void Init_AD9910(void);  //INIT 9910
//void AD9910WriteByte (unsigned char commond, unsigned char *databyte,unsigned char lengh);
void AD9110_IOInit(void);
void Init_ad9910(void);
void Freq_convert(ulong Freq);										//写频率
//void Write_Amplitude(bit Channel,unsigned int Amplitude);	//写幅度
void Write_Amplitude(uint Amp); //写幅度，输入范围：1-650 mV
void Txcfr(void);
void Freq_xiangwei(uint xiangwei);
void txd_8bit(uchar txdat);
void Square_wave(uint Sample_interval);//方波，采样时间间隔输入范围：4*(1~65536)ns
void Txramprofile(void);
void Txramdata(void);
void Txcfrram(void);
void Txdrg(void);
void test(void);

void MyOperateRESET(MY_PinState PinState);
void MyOperatePWR(MY_PinState PinState);
void MyOperateTXENABLE(MY_PinState PinState);
void MyOperatePF2(MY_PinState PinState);
void MyOperatePF1(MY_PinState PinState);
void MyOperatePF0(MY_PinState PinState);
void MyOperateIOUPDATE(MY_PinState PinState);
void MyOperateOSK(MY_PinState PinState);
void MyOperateDRCTL(MY_PinState PinState);
void MyOperateDRHOLD(MY_PinState PinState);
void MyOperateSDIO(MY_PinState PinState);
void MyOperateSCLK(MY_PinState PinState);
void MyOperateCSB(MY_PinState PinState);
MY_PinState MyGetStatePLLLOCK();
MY_PinState MyGetStateRSO();
MY_PinState MyGetStatePDCLK();
MY_PinState MyGetStateSYNCLK();
MY_PinState MyGetStateDROVER();
MY_PinState MyGetStateSDO();



#endif //AD9910_AD9910_H
