#include "usb_bsp.h"
#include "PeriphConfigCore.h"

/*
	Ӳ����������ö�������
	�����API�ᱻUSB Core����
	
	����API��Ҫ���壺
	void USB_OTG_BSP_Init (USB_OTG_CORE_HANDLE *pdev);						//USBӲ����ʼ��
	void USB_OTG_BSP_uDelay (const uint32_t usec);
	void USB_OTG_BSP_mDelay (const uint32_t msec);
	void USB_OTG_BSP_EnableInterrupt (USB_OTG_CORE_HANDLE *pdev);

USB HOST������Ҫ�����API��
	void USB_OTG_BSP_ConfigVBUS(USB_OTG_CORE_HANDLE *pdev);
	void USB_OTG_BSP_DriveVBUS(USB_OTG_CORE_HANDLE *pdev,uint8_t state);	//����USB�ڹ���
	void USB_OTG_BSP_Resume(USB_OTG_CORE_HANDLE *pdev) ;            		//USB�ڹ������IO�ĳ�ʼ��
	void USB_OTG_BSP_Suspend(USB_OTG_CORE_HANDLE *pdev);
*/


//USB������Դ���ƿ�
#define USB_HOST_PWRCTRL 	PAout(15)	//PA15

//USB OTG �ײ�IO��ʼ��
//pdev:USB OTG�ں˽ṹ��ָ��
void USB_OTG_BSP_Init(USB_OTG_CORE_HANDLE *pdev)
{
     GPIO_InitTypeDef  GPIO_InitStruct;
    __HAL_RCC_GPIOA_CLK_ENABLE();                   //ʹ��GPIOAʱ��
    __HAL_RCC_USB_OTG_FS_CLK_ENABLE();              //ʹ��OTG FSʱ��
	
	
	//����PA11 12
    GPIO_InitStruct.Pin=GPIO_PIN_11|GPIO_PIN_12;    //PA11 12
    GPIO_InitStruct.Mode=GPIO_MODE_AF_PP;           //����
    GPIO_InitStruct.Pull=GPIO_NOPULL;               //��������
    GPIO_InitStruct.Speed=GPIO_SPEED_HIGH;          //����
    GPIO_InitStruct.Alternate=GPIO_AF10_OTG_FS;     //����ΪOTG FS
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);         //��ʼ��
   
	//PA15
    GPIO_InitStruct.Pin=GPIO_PIN_15; 				//PA15
    GPIO_InitStruct.Mode=GPIO_MODE_OUTPUT_PP;  		//�������
    GPIO_InitStruct.Pull=GPIO_NOPULL;          		//��������
    GPIO_InitStruct.Speed=GPIO_SPEED_HIGH;     		//����
    HAL_GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	USB_HOST_PWRCTRL=1;								//����USB HOST��Դ����
}

//USB OTG �ж�����,����USB FS�ж�
//pdev:USB OTG�ں˽ṹ��ָ��
void USB_OTG_BSP_EnableInterrupt(USB_OTG_CORE_HANDLE *pdev)
{  	
    HAL_NVIC_SetPriority(OTG_FS_IRQn,1,0);          //��ռ���ȼ�1�������ȼ�0
    HAL_NVIC_EnableIRQ(OTG_FS_IRQn);                //ʹ��OTG USB FS�ж� 
}

//�ر� OTG_FS_IRQn �ж�
void USB_OTG_BSP_DisableInterrupt(void)
{
}
//USB OTG �˿ڹ�������(������δ�õ�)
//pdev:USB OTG�ں˽ṹ��ָ��
//state:0,�ϵ�;1,�ϵ�
void USB_OTG_BSP_DriveVBUS(USB_OTG_CORE_HANDLE *pdev, uint8_t state)
{ 
}
//USB_OTG �˿ڹ���IO����(������δ�õ�)
//pdev:USB OTG�ں˽ṹ��ָ��
void  USB_OTG_BSP_ConfigVBUS(USB_OTG_CORE_HANDLE *pdev)
{ 
} 
//USB_OTG us����ʱ����
//�ٷ����̲��õ��Ƕ�ʱ��2��ʵ�ֵ�.
//usec:Ҫ��ʱ��us��.
void USB_OTG_BSP_uDelay (const uint32_t usec)
{ 
	delay_us(usec);
}
//USB_OTG ms����ʱ����
//�ٷ����̲��õ��Ƕ�ʱ��2��ʵ�ֵ�.
//msec:Ҫ��ʱ��ms��.
void USB_OTG_BSP_mDelay (const uint32_t msec)
{  
	HAL_Delay(msec);
}






















