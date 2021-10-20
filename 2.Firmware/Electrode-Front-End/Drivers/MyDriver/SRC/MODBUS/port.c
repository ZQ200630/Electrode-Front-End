#include "port.h"
#include "mb.h"
//保持寄存器起始地址
#define REG_HOLDING_START     0x0001
//保持寄存器数量
#define REG_HOLDING_NREGS     4
//保持寄存器内容
uint16_t usRegHoldingBuf[REG_HOLDING_NREGS]
= {0x147b,0x3f8e,0x147b,0x400e};
/**
* @brief 保持寄存器处理函数，保持寄存器可读，可读可写
* @param pucRegBuffer 读操作时--返回数据指针，写操作时--输入数据指针
* usAddress 寄存器起始地址
* usNRegs 寄存器长度
* eMode 操作方式，读或者写
* @retval eStatus 寄存器状态
*/
eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs,
eMBRegisterMode eMode )
{
	//错误状态
	eMBErrorCode eStatus = MB_ENOERR;
	//偏移量
	int16_t iRegIndex;
	//判断寄存器是不是在范围内
	if ((usAddress >= (USHORT)REG_HOLDING_START)
    && (usAddress + usNRegs <= (USHORT)(REG_HOLDING_START + REG_HOLDING_NREGS)) )
	{
         //计算偏移量
         iRegIndex = ( int16_t )( usAddress - REG_HOLDING_START);switch ( eMode ){
         //读处理函数
         case MB_REG_READ:
         while( usNRegs > 0 )
          {
              *pucRegBuffer++ = ( uint8_t )( usRegHoldingBuf[iRegIndex] >> 8 );
    	   *pucRegBuffer++ = ( uint8_t )( usRegHoldingBuf[iRegIndex] & 0xFF );
    	   iRegIndex++;
		   usNRegs--;
		}
           break;
		//写处理函数
		case MB_REG_WRITE:
		while( usNRegs > 0 )
		{
			usRegHoldingBuf[iRegIndex] = *pucRegBuffer++ << 8;
			usRegHoldingBuf[iRegIndex] |= *pucRegBuffer++;
			iRegIndex++;
			usNRegs--;
		}
		break;
      }
	}
	else
	{
		//返回错误状态
		eStatus = MB_ENOREG;
	}
	return eStatus;
}

/// 未使用
eMBErrorCode eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
	 return MB_ENOREG;
}
/// 未使用
eMBErrorCode eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils, eMBRegisterMode eMode )
{
    return MB_ENOREG;
}

/// 未使用
eMBErrorCode eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    return MB_ENOREG;
}
