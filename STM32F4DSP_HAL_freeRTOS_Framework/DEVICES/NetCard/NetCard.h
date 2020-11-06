#ifndef _NETCARD_H
#define _NETCARD_H
#include "PeriphConfigCore.h"

#define NetCard_PHY_RST 		   	PDout(3) 			//NetCard_PHY��λ����

#define NetCard_PHY_ADDRESS             0x00			//PHYоƬ��ַ
 
u8 NetCard_PHY_Init(void);
u32 NetCard_PHY_ReadPHY(u16 reg);
void NetCard_PHY_WritePHY(u16 reg,u16 value);
u8 NetCard_PHY_Get_Speed(void);


#endif



