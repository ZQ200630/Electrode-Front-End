/*--------------------------------------------

            XC9104驱动程序

----------------------------------------------*/

#ifndef __XC9104_H
#define __XC9104_H

#include "system.h"

// Define CS Port And CS Pin
#define MY_XC9104_CS_PIN GPIO_PIN_3
#define MY_XC9104_CS_PORT GPIOA

// Define INC Port And INC Pin
#define MY_XC9104_INC_PIN GPIO_PIN_4
#define MY_XC9104_INC_PORT GPIOA

// Define UP/DOWN Port And UP/DOWN Pin
#define MY_XC9104_UD_PIN GPIO_PIN_5
#define MY_XC9104_UD_PORT GPIOA

void MyOperateCS(MY_PinState PinState);
void MyOperateINC(MY_PinState PinState);
void MyOperateUD(MY_PinState PinState);

void MyXC9104Init();
void MyXC9104Inc();
void MyXC9104Dec();
void MyXC9104Clear();
void MyXC9104ToValue(int Value);
void MyXC9104IncValue(int Value);
void MyXC9104DecValue(int Value);
void XC9104Init();

#endif
