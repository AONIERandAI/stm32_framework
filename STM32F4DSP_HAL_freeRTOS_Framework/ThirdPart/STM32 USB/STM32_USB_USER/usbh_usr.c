#include "usbh_usr.h"
#include "usb_hcd_int.h"
#include "PeriphConfigCore.h"

#include "ff.h"	//����MSC
#include "fatfs_app.h"

#include "usbh_hid_mouse.h"
#include "usbh_hid_keybd.h"  
/*
Դ�ļ��޸ļ�¼��
	usbh_hid_core.c ���� 587�У�phost->Control.setup.b.wLength.w = 100;		//������0�޸�Ϊ 100 �Ժ�,ʶ�����������
						 395�У�classReqStatus = USBH_Set_Idle (pdev, pphost, 100, 0);	//��0�޸�Ϊ100,��߼�����
					����.h�ļ����棬131�У����������й� HID_Machine_TypeDef ����������Ϊ���ڱ��ļ���.h������Ī������
	usbh_hid_keybd.h ���棬Ҫ�޸ļ������͵Ķ��壬ѡ��#define QWERTY_KEYBOARD		//ͨ�ü���
	usbh_hid_mouse.c ���棬123�е� MOUSE_Decode() �����޸�
*/


/*
ѡ�� USB HSOT �������� class
	ѡ��				class
	use_for_MSC			MSC�������ⲿUSB����FATFS�ļ�ϵͳ��
	use_for_VCP			VCP��USB HOST��֧�� VCP��HOST��ô�度��������VCP̫�˷��ˣ�
	use_for_HID			HID��Ŀǰ��֧�����ͼ��̣�
	...
	
	ע��ֻ���ڿ�����ʱ��ѡ��һ�Σ�����ʱ�Ķ���Ч
	�����µ�class��ʱ������ usbh_usr.h �������ö�٣�����Ҫ�Ա����޸� usbh_usr.c��usbh_usr.h �� usbh_conf.h
*/
const enum sys_USBH_use_for_enum sys_USBH_use_for_ = use_for_HID;

/*
USB HOSTʹ��˵��
������һ����ѭ����������³��򣺣�����ѭ���ﲻ������ʱ����Ĭ���Ѿ���BareConfig.c��ѭ������ӣ�
		#if ((SYSTEM_USB_ENABLE) && (USE_HOST_MODE))
			//Host Task handler
			//USBH_Process �������� U ��ʶ��׶Σ���ҪƵ���������ã����ǵ� U �̱�ʶ���ʣ�µĲ�����U �̶�д������������ USB �жϴ���
			USBH_Process(&USB_OTG_Core, &USB_Host);
			
			if(sys_USBH_use_for_ == use_for_HID)	//ֻ����ʹ��HOST HID��ʱ�����������Ⲣ����
			{
				if(bDeviceState==1)//���ӽ�����
				{
					if(USBH_Check_HIDCommDead(&USB_OTG_Core,&HID_Machine))//���USB HIDͨ��,�Ƿ�����? 
					{ 	    
						USBH_HID_Reconnect();//����
					}					
				}
				else	//����δ������ʱ��,���
				{
					if(USBH_Check_EnumeDead(&USB_Host))	//���USB HOST ö���Ƿ�������?������,�����³�ʼ�� 
					{ 	    
						USBH_HID_Reconnect();//����
					}		
				}
			}
			
			//����豸�Ƿ�����
			if(HCD_IsDeviceConnected(&USB_OTG_Core))
			{
				
			}
		#endif

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
	USB HOST��֧�� VCP��HOST��ô�度��������VCP̫�˷���


MSCģʽ���������洢����
	�����FATFS���õĺ� SYSTEM_FATFS_ENABLE
	��U�̲���USB HOST�ӿں󣬻�ִ��������û�����һ�Σ��ڴ˳�����Ĭ�ϻ���FATS���� DEV_USB�豸��������USB UOST MSC�ļ��豸��U�̣�
	u8 USH_MSC_User_App(void)
	
	�ɹ���Ϳ�����FATFS��API����ͨ��USB MSC���ص��ⲿU����
	
	
HID���˻��ӿڣ�������ģ����꣨�����xy�ƶ��͹��֣����߼���
	�ڴ��ļ��������棬��Ҫ����ĸ��û�API����
		����USB HOST�ӿڲ������ ���HID�豸���������º�����������豸�����ִ��һ�ε��û�����ˢ����Ӧ�Ľ��棬��־λ�ȵȣ�
		void USR_MOUSE_Init	(void)

		����USB HOST�ӿڲ������ ����HID�豸���������º�����������豸�����ִ��һ�ε��û�����ˢ����Ӧ�Ľ��棬��־λ�ȵȣ�
		void  USR_KEYBRD_Init(void)
		
		���ͼ��̵��û�Ӧ�ó���ÿ���豸����һ�Σ���ᱻ�ص�һ��
		void USR_MOUSE_ProcessData(HID_MOUSE_Data_TypeDef *data)
		void  USR_KEYBRD_ProcessData (uint8_t data)
	
	�����ĸ�API��ԭ���� usbh_hid_keybd.c �� usbh_hid_mouse.c ����
*/


//��ʾUSB����״̬
//0,û������;
//1,�Ѿ�����;
vu8 bDeviceState=0;		//Ĭ��û������  

USBH_HOST  USB_Host;
USB_OTG_CORE_HANDLE  USB_OTG_Core;

static u8 AppState = USH_USR_FS_INIT;

/*
�û�ʹ�ã�USB HOST ��ʼ��
����0�ɹ�����������ʧ��
*/
u8 sys_USBH_User_Init(void)
{
	switch(sys_USBH_use_for_)
	{
		case use_for_MSC:
						/*USB���	      ʶ��HS����FS		 USB_Host��Ϣ�ṹ��     MSC(��MSC class����)	 �û��ص���������*/
			USBH_Init(&USB_OTG_Core, USB_OTG_FS_CORE_ID,	&USB_Host,				&USBH_MSC_cb,			&USR_Callbacks);
			break;
		case use_for_VCP:
			FaultASSERT("USB HOST��֧�� VCP��HOST��ô�度��������VCP̫�˷���\r\n\r\n",NULL,flag_Warning);
			break;
		case use_for_HID:
			USBH_Init(&USB_OTG_Core, USB_OTG_FS_CORE_ID,	&USB_Host,				&HID_cb,				&USR_Callbacks);
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
	USBH_OTG_ISR_Handler(&USB_OTG_Core);
}  

//USB HOST �û��ص�����.
USBH_Usr_cb_TypeDef USR_Callbacks =
{
  USBH_USR_Init,
  USBH_USR_DeInit,
  USBH_USR_DeviceAttached,
  USBH_USR_ResetDevice,
  USBH_USR_DeviceDisconnected,
  USBH_USR_OverCurrentDetected,
  USBH_USR_DeviceSpeedDetected,
  USBH_USR_Device_DescAvailable,
  USBH_USR_DeviceAddressAssigned,
  USBH_USR_Configuration_DescAvailable,
  USBH_USR_Manufacturer_String,
  USBH_USR_Product_String,
  USBH_USR_SerialNum_String,
  USBH_USR_EnumerationDone,
  USBH_USR_UserInput,
  USBH_USR_MSC_Application,
  USBH_USR_DeviceNotSupported,
  USBH_USR_UnrecoveredError
};
 
//USB HOST ��ʼ�� 
void USBH_USR_Init(void)
{
//	printf("USB OTG FS MSC Host\r\n");
//	printf("> USB Host library started.\r\n");
//	printf("  USB Host Library v2.1.0\r\n\r\n");
	FaultASSERT("USB OTG FS MSC Host\r\n",NULL,flag_Warning);
	FaultASSERT("> USB Host library started.\r\n",NULL,flag_Warning);
	FaultASSERT("  USB Host Library v2.1.0\r\n\r\n",NULL,flag_Warning);
	
}
//��⵽U�̲���
void USBH_USR_DeviceAttached(void)//U�̲���
{ 
//	printf("��⵽USB�豸����!\r\n");
	FaultASSERT("��⵽USB�豸����!\r\n",NULL,flag_Warning);
}
//��⵽U�̰γ�
void USBH_USR_DeviceDisconnected (void)//U���Ƴ�
{ 
//	printf("USB�豸�γ�!\r\n");
	FaultASSERT("USB�豸�γ�!\r\n",NULL,flag_Warning);
	bDeviceState=0;	//USB�豸�γ���
	
	if(sys_USBH_use_for_ == use_for_MSC)
	{
		f_mount(0,"DEV_USB:",1); 	//ж��U��
	}
}
//��λ�ӻ�
void USBH_USR_ResetDevice(void)
{
//	printf("��λ�豸...\r\n");
	FaultASSERT("��λ�豸...\r\n",NULL,flag_Warning);
}
//��⵽�ӻ��ٶ�
//DeviceSpeed:�ӻ��ٶ�(0,1,2 / ����)
void USBH_USR_DeviceSpeedDetected(uint8_t DeviceSpeed)
{
	if(DeviceSpeed==HPRT0_PRTSPD_HIGH_SPEED)
	{
//		printf("����(HS)USB�豸!\r\n");
		FaultASSERT("����(HS)USB�豸!\r\n",NULL,flag_Warning);
 	}  
	else if(DeviceSpeed==HPRT0_PRTSPD_FULL_SPEED)
	{
//		printf("ȫ��(FS)USB�豸!\r\n"); 
		FaultASSERT("ȫ��(FS)USB�豸!\r\n",NULL,flag_Warning);
	}
	else if(DeviceSpeed==HPRT0_PRTSPD_LOW_SPEED)
	{
//		printf("����(LS)USB�豸!\r\n");  
		FaultASSERT("����(LS)USB�豸!\r\n",NULL,flag_Warning);
	}
	else
	{
//		printf("�豸����!\r\n");  
		FaultASSERT("�豸����!\r\n",NULL,flag_Warning);
	}
}
//��⵽�ӻ���������
//DeviceDesc:�豸������ָ��
void USBH_USR_Device_DescAvailable(void *DeviceDesc)
{ 
	USBH_DevDesc_TypeDef *hs;
	hs=DeviceDesc;   
//	printf_("VID: %04Xh\r\n" , (uint32_t)(*hs).idVendor); 
//	printf_("PID: %04Xh\r\n" , (uint32_t)(*hs).idProduct); 
	printf_uart(UART1,"VID: %04Xh\r\n", (uint32_t)(*hs).idVendor);
	printf_uart(UART1,"PID: %04Xh\r\n", (uint32_t)(*hs).idProduct);
}
//�ӻ���ַ����ɹ�
void USBH_USR_DeviceAddressAssigned(void)
{
//	printf("�ӻ���ַ����ɹ�!\r\n");  
	FaultASSERT("�ӻ���ַ����ɹ�!\r\n",NULL,flag_Warning);	
}
//��������������Ч
void USBH_USR_Configuration_DescAvailable(USBH_CfgDesc_TypeDef * cfgDesc,
                                          USBH_InterfaceDesc_TypeDef *itfDesc,
                                          USBH_EpDesc_TypeDef *epDesc)
{
	USBH_InterfaceDesc_TypeDef *id; 
	id = itfDesc;   
	if((*id).bInterfaceClass==0x08)
	{
//		printf("���ƶ��洢���豸!\r\n"); 
		FaultASSERT("���ƶ��洢���豸!\r\n",NULL,flag_Warning);
	}else if((*id).bInterfaceClass==0x03)
	{
//		printf("HID �豸!\r\n"); 
		FaultASSERT("HID �豸!\r\n",NULL,flag_Warning);
	}    
}
//��ȡ���豸Manufacturer String
void USBH_USR_Manufacturer_String(void *ManufacturerString)
{
//	printf("Manufacturer: %s\r\n",(char *)ManufacturerString);
	printf_uart(UART1,"Manufacturer: %s\r\n",(char *)ManufacturerString);
}
//��ȡ���豸Product String 
void USBH_USR_Product_String(void *ProductString)
{
//	printf("Product: %s\r\n",(char *)ProductString);  
	printf_uart(UART1,"Product: %s\r\n", (char *)ProductString);
}
//��ȡ���豸SerialNum String 
void USBH_USR_SerialNum_String(void *SerialNumString)
{
//	printf("Serial Number: %s\r\n",(char *)SerialNumString);    
	printf_uart(UART1,"Serial Number: %s\r\n", (char *)SerialNumString);
} 
//�豸USBö�����
void USBH_USR_EnumerationDone(void)
{ 
//	printf("�豸ö�����!\r\n\r\n");   
	FaultASSERT("�豸ö�����!\r\n\r\n",NULL,flag_Warning);
} 
//�޷�ʶ���USB�豸
void USBH_USR_DeviceNotSupported(void)
{ 
//	USBH_Msg_Show(3);//�޷�ʶ���USB�豸
//	printf("�޷�ʶ���USB�豸!\r\n\r\n"); 
	FaultASSERT("�޷�ʶ���USB�豸!\r\n\r\n",NULL,flag_Warning);
}  
//�ȴ��û����밴��,ִ����һ������
USBH_USR_Status USBH_USR_UserInput(void)
{ 
//	printf("�����û�ȷ�ϲ���!\r\n");
	FaultASSERT("�����û�ȷ�ϲ���!\r\n",NULL,flag_Warning);
	bDeviceState=1;//USB�豸�Ѿ����ӳɹ�
	return USBH_USR_RESP_OK;
} 
//USB�ӿڵ�������
void USBH_USR_OverCurrentDetected (void)
{
//	printf("�˿ڵ�������!!!\r\n");
	FaultASSERT("�˿ڵ�������!!!\r\n",NULL,flag_Warning);
}  
//���³�ʼ��
void USBH_USR_DeInit(void)
{
	switch(sys_USBH_use_for_)
	{
		case use_for_HID:
			FaultASSERT("���³�ʼ��!!!\r\n",NULL,flag_Warning);
			break;
		case use_for_MSC:
			AppState=USH_USR_FS_INIT;
			break;
		case use_for_VCP:
			break;
		default:break;
	}

}
//�޷��ָ��Ĵ���!!  
void USBH_USR_UnrecoveredError (void)
{
//	printf("�޷��ָ��Ĵ���!!!\r\n\r\n");
	FaultASSERT("�޷��ָ��Ĵ���!!!\r\n\r\n",NULL,flag_Warning);	
}
//////////////////////////////////////////////////////////////////////////////////////////
//������������,�Է�ֹUSB����

//USBö��״̬�������,��ֹUSBö��ʧ�ܵ��µ�����
//phost:USB_HOST�ṹ��ָ��
//����ֵ:0,û������
//       1,������,�ⲿ������������USB����.
u8 USBH_Check_EnumeDead(USBH_HOST *phost)
{
	static u16 errcnt=0;
	//���״̬,�����������,��˵��USB������.
	if(phost->gState==HOST_CTRL_XFER&&(phost->EnumState==ENUM_IDLE||phost->EnumState==ENUM_GET_FULL_DEV_DESC))
	{
		errcnt++;
		if(errcnt>2000)//������
		{ 
			errcnt=0;
			RCC->AHB2RSTR|=1<<7;	//USB OTG FS ��λ
			HAL_Delay(5);
			RCC->AHB2RSTR&=~(1<<7);	//��λ����  
			return 1;
		} 
	}else errcnt=0;
	return 0;
} 
//USB HIDͨ���������,��ֹUSBͨ������(��ʱ�����:DTERR,��Data toggle error)
//pcore:USB_OTG_Core_dev_HANDLE�ṹ��ָ��
//phidm:HID_Machine_TypeDef�ṹ��ָ�� 
//����ֵ:0,û������
//       1,������,�ⲿ������������USB����.
u8 USBH_Check_HIDCommDead(USB_OTG_CORE_HANDLE *pcore,HID_Machine_TypeDef *phidm)
{
 	if(pcore->host.HC_Status[phidm->hc_num_in]==HC_DATATGLERR)//��⵽DTERR����,ֱ������USB.
	{  
		return 1;
	}
	return 0;
}

//HID��������
void USBH_HID_Reconnect(void)
{
	//�ر�֮ǰ������
	USBH_DeInit(&USB_OTG_Core,&USB_Host);	//��λUSB HOST
	USB_OTG_StopHost(&USB_OTG_Core);		//ֹͣUSBhost
	if(USB_Host.usr_cb->DeviceDisconnected)		//����,�Ž�ֹ
	{
		USB_Host.usr_cb->DeviceDisconnected(); 	//�ر�USB����
		USBH_DeInit(&USB_OTG_Core, &USB_Host);
		USB_Host.usr_cb->DeInit();
		USB_Host.class_cb->DeInit(&USB_OTG_Core,&USB_Host.device_prop);
	}
	USB_OTG_DisableGlobalInt(&USB_OTG_Core);//�ر������ж�
	//���¸�λUSB
    __HAL_RCC_USB_OTG_FS_FORCE_RESET();//USB OTG FS ��λ
	HAL_Delay(5);
    __HAL_RCC_USB_OTG_FS_RELEASE_RESET();//��λ����
	
	memset(&USB_OTG_Core,0,sizeof(USB_OTG_CORE_HANDLE));
	memset(&USB_Host,0,sizeof(USB_Host));
	//��������USB HID�豸
	USBH_Init(&USB_OTG_Core,USB_OTG_FS_CORE_ID,&USB_Host,&HID_cb,&USR_Callbacks);  
}

//////////////////////////////////////////////////////////////////////////////////////////
//USB����������ݴ���

u8 USB_FIRST_PLUGIN_FLAG = 0;	//USB��һ�β����־,���Ϊ1,˵���ǵ�һ�β��룬���ö�

//����ʼ��
void USR_MOUSE_Init	(void)
{
	//USB ��꣬�����HID�豸�ı�ǣ�ִ����괦���û�����
	USB_FIRST_PLUGIN_FLAG=1;//��ǵ�һ�β���
}
//���̳�ʼ��
void  USR_KEYBRD_Init(void)
{ 
	//USB ���̣�������HID�豸�ı�ǣ�ִ�м��̴����û�����
	USB_FIRST_PLUGIN_FLAG=1;//��ǵ�һ�β���
}

//���ڴ�ż�����������
const u16 maxinputchar = 100;
__align(4) u8 Keybd_buf[maxinputchar]; 

//USB������ݴ���
//data:USB������ݽṹ��ָ��
void USR_MOUSE_ProcessData(HID_MOUSE_Data_TypeDef *data)
{  
	static signed short x,y,z; 
	if(USB_FIRST_PLUGIN_FLAG)//��һ�β���,����������
	{
		USB_FIRST_PLUGIN_FLAG=0;
		x=y=z=0;
	}
	x += (signed char)data->x;			//HID_MOUSE_Data_TypeDef *dataΪ����ʽ
		if(x>9999)x=9999;
		if(x<-9999)x=-9999;
	y += (signed char)data->y;
		if(y>9999)y=9999;
		if(y<-9999)y=-9999;
	z += (signed char)data->z;			//zΪ����
		if(z>9999)z=9999;
		if(z<-9999)z=-9999;
	
	//0000 0001��������LEFT
	if(data->button&0X01)
	{
		
	}
	
	//0000 0010��������RIGHT
	if((data->button&0X03)==0X02)
	{
		
	}
	//0000 0011��������+RIGHT
	else if((data->button&0X03)==0X03)
	{
		
	}
	
	//0000 0100��������MID
	if((data->button&0X07)==0X04)
	{
		
	}
	//0000 01xx��������+MID��xx > 0��
	else if((data->button&0X07)>0X04)
	{
		
	}
	
//	printf_uart(UART1,"btn,X,Y,Z:0x%x,%d,%d,%d\r\n",data->button,(signed char)data->x,(signed char)data->y,(signed char)data->z); 
} 


//USB�������ݴ���
//data:USB������ݽṹ��ָ��
void  USR_KEYBRD_ProcessData (uint8_t data)
{ 
	static u16 pos;
	
	if(USB_FIRST_PLUGIN_FLAG)//��һ�β���,����������
	{
		USB_FIRST_PLUGIN_FLAG=0;
 		pos=0; 
	}
	
	if(data>=' '&&data<='~')
	{
		Keybd_buf[pos++]=data;
		Keybd_buf[pos]=0;		//��ӽ�����. 
		if(pos>maxinputchar)pos=maxinputchar;//���������ô��
	}else if(data==0X0D)	//�˸��
	{
		if(pos)pos--;
		Keybd_buf[pos]=0;		//��ӽ�����.  
	}
	
	
	if(pos<=maxinputchar)	//û�г�����ʾ��
	{
		printf_uart(UART1,"%s\r\n",Keybd_buf);
	}
	
//	printf_uart(UART1,"KEY Board Value:%02X\r\n",data);
//	printf_uart(UART1,"KEY Board Char:%c\r\n",data); 
}


//////////////////////////////////////////////////////////////////////////////////////////
//USB HOST MSC��������ʵ��fatfs diskio�Ľӿں���

//����U�̲��Ϻ�ִ��һ�ε��û�����
u8 USBH_MSC_User_App(void)
{
	#if SYSTEM_FATFS_ENABLE
	
		u8 init_return = 1;
		u32 total,free;	//��ȡU��������ʣ���������ֽ�Ϊ��λ
		
		init_return = f_mount(fs[2],"DEV_USB:",1);		//����USB UOST MSC�ļ��豸��U�̣�
			if(init_return != 0){ FaultASSERT("f_mount fs[2]",init_return,flag_Warning);return init_return;}
		init_return = fatfs_getfree((u8*)"DEV_USB:",&total,&free);
		if(init_return == 0)
		{
			printf_uart(UART1,"U Disk Total Size: %d MB\r\n",total >> 10);	//��ȡU��������ʣ������ ����ʾ��
			printf_uart(UART1,"U Disk  Free Size: %d MB\r\n",free >> 10);
		}else{return init_return;}
	
	#endif
	
	return 0;
} 

//USB HOST MSC���û�Ӧ�ó���
int USBH_USR_MSC_Application(void)
{
	u8 res=0;
  	switch(AppState)
  	{
    	case USH_USR_FS_INIT://��ʼ���ļ�ϵͳ 
			FaultASSERT("��ʼִ���û�����!!!\r\n",NULL,flag_Warning);
			AppState=USH_USR_FS_TEST;
      		break;
    	case USH_USR_FS_TEST:	//ִ��USB OTG ����������
			res=USBH_MSC_User_App(); //�û�������
     		res=0;
			if(res)AppState=USH_USR_FS_INIT;
      		break;
    	default:break;
  	} 
	return res;
}

//��ȡU��״̬
//����ֵ:0,U��δ����
//      1,����
u8 USBH_UDISK_Status(void)
{
	return HCD_IsDeviceConnected(&USB_OTG_Core);//����U��״̬
}

//��U��
//buf:�����ݻ�����
//sector:������ַ
//cnt:��������	
//����ֵ:����״̬;0,����;����,�������;		 
u8 USBH_UDISK_Read(u8* buf,u32 sector,u32 cnt)
{
	u8 res=1;
	if(HCD_IsDeviceConnected(&USB_OTG_Core)&&AppState==USH_USR_FS_TEST)//���ӻ�����,����APP����״̬
	{  		    
		do
		{
			res=USBH_MSC_Read10(&USB_OTG_Core,buf,sector,512*cnt);
			USBH_MSC_HandleBOTXfer(&USB_OTG_Core ,&USB_Host);		      
			if(!HCD_IsDeviceConnected(&USB_OTG_Core))
			{
				res=1;//��д����
				break;
			};   
		}while(res==USBH_MSC_BUSY);
	}else res=1;		  
	if(res==USBH_MSC_OK)res=0;	
	return res;
}

//дU��
//buf:д���ݻ�����
//sector:������ַ
//cnt:��������	
//����ֵ:����״̬;0,����;����,�������;		 
u8 USBH_UDISK_Write(u8* buf,u32 sector,u32 cnt)
{
	u8 res=1;
	if(HCD_IsDeviceConnected(&USB_OTG_Core)&&AppState==USH_USR_FS_TEST)//���ӻ�����,����APP����״̬
	{  		    
		do
		{
			res=USBH_MSC_Write10(&USB_OTG_Core,buf,sector,512*cnt); 
			USBH_MSC_HandleBOTXfer(&USB_OTG_Core ,&USB_Host);		      
			if(!HCD_IsDeviceConnected(&USB_OTG_Core))
			{
				res=1;//��д����
				break;
			};   
		}while(res==USBH_MSC_BUSY);
	}else res=1;		  
	if(res==USBH_MSC_OK)res=0;	
	return res;
}



