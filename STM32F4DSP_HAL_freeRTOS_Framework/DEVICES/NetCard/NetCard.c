#include "NetCard.h"

#if	SYS_SUPPORT_LWIP

//NetCard_PHY��ʼ��
//����ֵ:0,�ɹ�;
//    ����,ʧ��
u8 NetCard_PHY_Init(void)
{
	return 0;
}

extern ETH_HandleTypeDef ETH_Handler;
//��ȡPHY�Ĵ���ֵ
u32 NetCard_PHY_ReadPHY(u16 reg)
{
    u32 regval;
    HAL_ETH_ReadPHYRegister(&ETH_Handler,reg,&regval);
    return regval;
}
//��NetCard_PHYָ���Ĵ���д��ֵ
//reg:Ҫд��ļĴ���
//value:Ҫд���ֵ
void NetCard_PHY_WritePHY(u16 reg,u16 value)
{
    u32 temp=value;
    HAL_ETH_ReadPHYRegister(&ETH_Handler,reg,&temp);
}
//�õ�8720���ٶ�ģʽ
//����ֵ:
//001:10M��˫��
//101:10Mȫ˫��
//010:100M��˫��
//110:100Mȫ˫��
//����:����
u8 NetCard_PHY_Get_Speed(void)
{
	u8 speed;
	speed=((NetCard_PHY_ReadPHY(31)&0x1C)>>2); //��LAN8720��31�żĴ����ж�ȡ�����ٶȺ�˫��ģʽ
	return speed;
}

#endif







