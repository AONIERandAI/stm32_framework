#include "usbd_usr.h"
#include "usbd_desc.h"
#include "usb_dcd_int.h"
#include "PeriphConfigCore.h"

#include "usbd_msc_core.h"
#include "usbd_msc_bot.h"

#include "usbd_cdc_core.h"
/*Դ�ļ��޸ļ�¼���� usbd_cdc_core ���� �� USBD_DeviceDesc ������ USBD_DeviceDesc_vcp*/

#include "usbd_hid_core.h"



/*
ѡ�� USB Device �������� class
	ѡ��				class
	use_for_MSC			MSC�����ڰѱ���ģ��Ϊһ��U�̣��ѱ�����ҵ�SPI FLASH����SD��ģ���U�̹����Զ˲�����
	use_for_VCP			VCP�����ڰѱ���ģ��Ϊһ��USB���⴮�ڣ���λ����Ҫ�Ȱ�װSTM32 VCP������
	use_for_mouse		HID�����ڰѱ���ģ��Ϊһ����꣩
	use_for_keyboard	HID�����ڰѱ���ģ��Ϊһ�����̣����д���ֲ�ļ������̣�https://blog.csdn.net/xuquanlin_1680/article/details/80502183��
	...
	
	ע��ֻ���ڿ�����ʱ��ѡ��һ�Σ�����ʱ�Ķ���Ч
	�����µ�class��ʱ������ usbd_usr.h �������ö�٣�����Ҫ�Ա����޸� usbd_desc.c �� usbd_conf.h
*/
const enum sys_USBD_use_for_enum sys_USBD_use_for_ = use_for_mouse;

/*USB Deviceʹ��˵��
����״����־λʹ�����ӣ�
	u8 Divece_STA;
	if(Divece_STA != bDeviceState)
	{
		if(bDeviceState == 1)
			LCD_ShowString(10,140,tftlcd_data.width,tftlcd_data.height,16,"USB Connected    ");//��ʾUSB�����Ѿ�����
		else 
			LCD_ShowString(10,140,tftlcd_data.width,tftlcd_data.height,16,"USB DisConnected ");//��ʾUSB���γ���
		Divece_STA = bDeviceState;
	}
VCPģʽ��USBģ�����⴮�ڣ���
	�� usbd_cdc_vcp.c �ļ����棺
		���գ�
			��USB�ڽ������ݺ���Զ����� uint16_t VCP_DataRx(uint8_t * Buf, uint32_t Len) ����
			ֻ�蹹��һ�����ݴ���������У�Ȼ������־λ
			
		���ͣ�
			Ŀǰ����һ��һ���ֽڵķ��͡�
			���� APP_Rx_Buffer[APP_Rx_ptr_in] �����һ���ֽ�
			Ȼ����� uint16_t VCP_DataTx(void) ����һ��
			���磺
				APP_Rx_Buffer[APP_Rx_ptr_in] = aRxBuffer[0];
				VCP_DataTx();
		�趨Ҫģ��Ĵ��ڵ�ģʽ��
			uint16_t VCP_Ctrl(uint32_t Cmd, uint8_t * Buf, uint32_t Len)
			
			
MSCģʽ���������洢����
	����FATFS��diskio.c����һ������ usbd_storage_msd.c �ļ����棺
		�����м����豸�� #define STORAGE_LUN_NBR 	2
		��д ��׼��ѯ����(ÿ��lunռ36�ֽ�)�� STORAGE_Inquirydata[]
		����⼸��������
			int8_t STORAGE_Init (uint8_t lun);
			int8_t STORAGE_GetCapacity (uint8_t lun,uint32_t *block_num,uint32_t *block_size);
			int8_t  STORAGE_IsReady (uint8_t lun);
			int8_t  STORAGE_IsWriteProtected (uint8_t lun);
			int8_t STORAGE_Read (uint8_t lun,uint8_t *buf,uint32_t blk_addr,uint16_t blk_len);
			int8_t STORAGE_Write (uint8_t lun,uint8_t *buf,uint32_t blk_addr,uint16_t blk_len);
			int8_t STORAGE_GetMaxLun (void);
			
			STORAGE_GetMaxLun()Ҫע�⣬�������ȼ��SD���ڲ����ߣ�������򷵻� (STORAGE_LUN_NBR - 1)����ʾ�������豸 0��1
				���SD�����ڣ��򷵻� (STORAGE_LUN_NBR - 2)����ʾֻ��һ���豸��SPI FLASH�������0
		��ѯ��־λʹ�þ�����
			if(USB_STATUS_REG)	//״̬�ı��ˣ�״̬���� usbd_storage_msd.c �ļ����汻�ص������Զ��ı�
			{
				USB_STATUS_REG = 0;
				LCD_Fill(10,160,240,160+16,WHITE);//�����ʾ			  	   
				if(USB_STATUS_REG&0x01)//����д		  
				{
					LCD_ShowString(10,160,tftlcd_data.width,tftlcd_data.height,16,"USB Writing...");//��ʾUSB����д������	 
				}
				
				if(USB_STATUS_REG&0x02)//���ڶ�
				{
					LCD_ShowString(10,160,tftlcd_data.width,tftlcd_data.height,16,"USB Reading...");//��ʾUSB���ڶ�������  		 
				}	 										  
				
				if(USB_STATUS_REG&0x04)
					LCD_ShowString(10,180,tftlcd_data.width,tftlcd_data.height,16,"USB Write Err ");//��ʾд�����
				else 
					LCD_Fill(10,180,240,180+16,WHITE);//�����ʾ	  
				
				if(USB_STATUS_REG&0x08)
					LCD_ShowString(10,210,tftlcd_data.width,tftlcd_data.height,16,"USB Read  Err ");//��ʾ��������
				else 
					LCD_Fill(10,210,240,210+16,WHITE);//�����ʾ    
				
			}
			
			
HID���˻��ӿڣ�������ģ����꣨�����xy�ƶ��͹��֣����߼���
		
		�д���ֲ�ļ������̣�https://blog.csdn.net/xuquanlin_1680/article/details/80502183
		�����ƾ�����
			uint32_t counter = 0;
			char buf[4] = {0};		//���ܴ���unsigned��ʶ����
			//���Ĭ�Ϸ���1msѭ��ִ���USBD_HID_GetPollingInterval(&USB_OTG_dev)Ϊ10����10ms����һ������
			if (counter++ >= USBD_HID_GetPollingInterval(&USB_OTG_dev))
			{
				//buf ���ĸ��ֽڣ�0 1 2 3���ֱ��� ��굥����x��y������
				//	˵����	x\y��ֵ���ϣ���ֵ����
				buf[0] = 0;buf[3] = 0;
				buf[1] = 1;buf[2] = -1;
				USBD_HID_SendReport(&USB_OTG_dev, (uint8_t*)buf, 4);
				counter = 0;
			}
*/


/*���¶��ǹ̶��ģ����ö�*/

//��ʾUSB����״̬
//���ֻ��������ǵģ��û����Բ�ѯ��û��������
//0,û������;
//1,�Ѿ�����;
vu8 bDeviceState=0;		//Ĭ��û������  


USB_OTG_CORE_HANDLE  USB_OTG_dev;

/*
�û�ʹ�ã�USB Dvice��ʼ��
����0�ɹ�����������ʧ��
*/
u8 sys_USBD_User_Init(void)
{
	switch(sys_USBD_use_for_)
	{
		case use_for_MSC:
			MSC_BOT_Data = mymalloc(InrRAM,MSC_MEDIA_PACKET);	//�����ڴ棬MSC_MEDIA_PACKET Ĭ��ռ InrRAM 12KB
			if(MSC_BOT_Data == NULL) return 1;
						/*USB���	      ʶ��HS����FS	������(��usbd_desc.c����)   MSC(��MSC class����)	 �û��ص���������*/
			USBD_Init(&USB_OTG_dev,		USB_OTG_FS_CORE_ID,		&USR_desc,				&USBD_MSC_cb,			&USR_cb);
			break;
		
		case use_for_VCP:
			USBD_Init(&USB_OTG_dev,		USB_OTG_FS_CORE_ID,		&USR_desc,				&USBD_CDC_cb, 			&USR_cb);
			break;
		case use_for_keyboard:
		case use_for_mouse:
			USBD_Init(&USB_OTG_dev,		USB_OTG_FS_CORE_ID,		&USR_desc,				&USBD_HID_cb, 			&USR_cb);
			break;
			
		
		default:
			return 0xfe;
	}
	HAL_Delay(100);
	
	return 0;
}

//USB OTG �жϷ�����
//��������USB�ж�
void OTG_FS_IRQHandler(void)
{
  	USBD_OTG_ISR_Handler(&USB_OTG_dev);
}
//ָ��DEVICE_PROP�ṹ��
//USB Device �û��ص�����. 
USBD_Usr_cb_TypeDef USR_cb =
{
  USBD_USR_Init,
  USBD_USR_DeviceReset,
  USBD_USR_DeviceConfigured,
  USBD_USR_DeviceSuspended,
  USBD_USR_DeviceResumed,
  
  USBD_USR_DeviceConnected,
  USBD_USR_DeviceDisconnected,    
};
//USB Device �û��Զ����ʼ��������û���õ�
void USBD_USR_Init(void)
{
	//FaultASSERT("USBD_USR_Init\r\n",0,flag_Warning);
}
//USB Device ��λ
//speed:USB�ٶ�,0,����;1,ȫ��;����,����.
void USBD_USR_DeviceReset (uint8_t speed)
{
	switch (speed)
	{
		case USB_OTG_SPEED_HIGH:
//			printf("USB Device Library v1.1.0  [HS]\r\n");
			FaultASSERT("USB Device Library v1.1.0  [HS]\r\n",0,flag_Warning);
			break; 
		case USB_OTG_SPEED_FULL: 
//			printf("USB Device Library v1.1.0  [FS]\r\n");
			FaultASSERT("USB Device Library v1.1.0  [FS]\r\n",0,flag_Warning);
			break;
		default:
//			printf("USB Device Library v1.1.0  [??]\r\n"); 
			FaultASSERT("USB Device Library v1.1.0  [??]\r\n",0,flag_Warning);
			break;
	}
}
//USB Device ���óɹ�
void USBD_USR_DeviceConfigured (void)
{
    bDeviceState=1;
//	printf("MSC Interface started.\r\n"); 
	FaultASSERT("MSC Interface started.\r\n",0,flag_Warning);
} 
//USB Device����
void USBD_USR_DeviceSuspended(void)
{
    bDeviceState=0;
//	printf("Device In suspend mode.\r\n");
	FaultASSERT("Device In suspend mode.\r\n",0,flag_Warning);
} 
//USB Device�ָ�
void USBD_USR_DeviceResumed(void)
{ 
//	printf("Device Resumed\r\n");
	FaultASSERT("Device Resumed\r\n",0,flag_Warning);
}
//USB Device���ӳɹ�
void USBD_USR_DeviceConnected (void)
{
	bDeviceState=1;
//	printf("USB Device Connected.\r\n");
	FaultASSERT("USB Device Connected.\r\n",0,flag_Warning);
}
//USB Deviceδ����
void USBD_USR_DeviceDisconnected (void)
{
	bDeviceState=0;
//	printf("USB Device Disconnected.\r\n");
	FaultASSERT("USB Device Disconnected.\r\n",0,flag_Warning);
} 








