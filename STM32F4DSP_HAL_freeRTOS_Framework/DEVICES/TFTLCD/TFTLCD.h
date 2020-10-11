#ifndef __TFTLCD_H__
#define __TFTLCD_H__

#include "PeriphConfigCore.h"
#include "PeriphConfig.h"

/*
  ˵����API��

Ĭ�ϣ�
1��ͳһ��LCD��RESET������MCU��RESET��
2��FSMCĿǰֻ֧��16λ���ݣ���Ȼ�Ѿ���FSMC����ôIO�ڿ϶������ţ�û��Ҫ��8λ�������ˣ�
3��IO������Ĭ��8λ���ݣ�Ϊ��IO���ٵ�MCU���ǣ�
4��IO������Ŀǰû��ReadReg()��ReadPoint()������Ҳû�ж����ͺţ�Ŀǰֻ֧��ILI9341
5��FSMC�������е�API������
void LCD_with_FSMC_init_LCD(void);						//��ʼ��
void LCD_SSD_BackLightSet(u8 pwm);						//SSD1963 �������
u32  LCD_ReadPoint(u16 x,u16 y); 						//���� 
void LCD_DisplayOn(void);								//����ʾ
void LCD_DisplayOff(void);								//����ʾ
void LCD_Scan_Dir(u8 dir);								//������ɨ�跽��
void LCD_Display_Dir(u8 dir);							//������Ļ��ʾ����
u16 LCD_ReadReg(u16 LCD_Reg);
u16 LCD_RD_DATA(void);

6��IO�������е�API��
void LCD_Init_no_FSMC(void);							//��ʼ��
void LCD_SetParam_4ILI9341(void);						//д��ֻ֧��ILI9341�Ĳ���
void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode);	//������ʾһ���ַ�����������Ӣ����ʾ
void DrawPageHead(u8 *str);										//����Ļ��������ҳ��ı���
void Gui_Drawbmp16(u16 x,u16 y,const unsigned char *p);			//��ʾ��ʾһ��16λBMPͼ��
void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);
void GUI_DrawFont24(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);
void GUI_DrawFont32(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);

void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode);
//����д��Ӣ�ĺ����Ļ���ַ������Ƽ�����д�����ã����ĸ�֧��16��24��32����Ҫ��ǰȡģ���뵽FONT.H����

7�������������е�API��
void LCD_Clear(u32 Color);	 									//����
void LCD_SetCursor(u16 Xpos, u16 Ypos);							//���ù��
void LCD_DrawPoint(u16 x,u16 y);								//����
void LCD_Fast_DrawPoint(u16 x,u16 y,u32 color);					//���ٻ���
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r);						//��Բ
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);				//����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);			//������
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u32 color);		   	//��䵥ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);	//���ָ����ɫ

void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);			//��ʾһ���ַ�
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);  			//��ʾһ������
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);	//��ʾ ����

void LCD_ShowString(u16 x,u16 y,u8 size,u8 *p);	
//��ʾһ���ַ�����12/16/24/32���壬����дӢ�ĺ����֣�����д���ģ��Ƽ�ֻддӢ�ĺ������ã�TODO���ֿ��Ѿ�����24��32�ı��룬����4�ִ�С�Ƿ񶼿���֧�֣�

void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);	


8��ָ����ɫ��Ҫ���⻭�ʺͱ���ͬɫ
POINT_COLOR = RED;
BACK_COLOR = BLACK;


	ʹ��˵����

����������һ��16λ�����ߵ�FSMC������һ��8λ����ѡ��IO����������Ӧ��ͬ�ĳ�ʼ��������

1������FSMC�������Լ���ʼ��IO�ڣ��򿪺궨��SYSTEM_FSMC_ENABLE��SYSTEM_FSMC_use4LCD��Ȼ�����LCD_Init_with_FSMC()��ʼ���������ɣ�
Ĭ����sys_Device_Init_Seq()�����Ѿ����á�Ĭ��ʹ��FSMC�Ŀ�1��3������IO�������£�
	һ��ӷ�����CEǰ���һ��N����ʾCE����Ч������ͬ��
	FSMC			LCD
	NEx			CS����ѡ�У�
	NOE			RD���Ͷ���
	NWE			WR����д��
				RS�������ݵ���������ɽ���FSMC��һ����ַ����A10
	D[15:0]			D[15:0]�����ݣ�
	LCD�ֱ��ʲ�����
	1���޸ĺ���void LCD_Display_Dir(u8 dir)�ڶ����LCD�ֱַ���
	2���޸������ //LCD�ֱ������ã�ע������������ֻ����SSD1963��������
			#define SSD_HOR_RESOLUTION		240		//LCDˮƽ�ֱ���
			#define SSD_VER_RESOLUTION		320		//LCD��ֱ�ֱ���

2������IO��������ֻ�����LCD_Init_no_FSMC()��ʼ���������ɣ�Ĭ����sys_Device_Init_Seq()�����Ѿ����á�
LCD�ֱ��ʲ�����
	���ʹ�÷�240x320����Ļ����LCD_SetParam_4ILI9341()�������޸ķֱ���
����Ҫ��IO����periphconfig.c����Ķ���IO�ģ�����Ӧ�ĸ�lcd.h�����IO�ں궨�壨�Ƚ��鷳����Ĭ��IO�����£�
	LCD_RST	��PB7	//��λ�ź�
	LCD_CS	��PB6	//Ƭѡ�ź�
	LCD_RS	��PB5	//�Ĵ���/����ѡ���ź�
	LCD_WR	��PB4	//д�ź�
	LCD_RD	��PB3	//���ź�
	D[0:7]	��PB8~15	//������
	
	˵��������0x5510��������д�Ĵ�����ַ��16λ�ģ�Ŀǰ�ĺ����ǰ�λ�ģ�����֧��16λ��
	
*/

/*���������¼���ȫ���ο�����ֲ������ԭ�ӵ�LCD�½�Դ��������ϵĲ���Դ�룬�����ǿ�Դ���룬������Ҳ��Դ������������ҵ��;*/

/*_______________________ֻ�޸������DFT_SCAN_DIRҲ���ԣ�����Ͳ��ö���___________________________________*/
#define USE_HORIZONTAL  	0	//�����Ƿ�ʹ�ú��� 		0,����.1,����.

/*ȥFONT.H���涨���ֿ�ı���ѡ�������FLASHռ��*/
	//������������������ѡ��
	//#define USE_ALL_ASC_FONT	0	//�Ƿ�ʹ�����е�ASC���壻��ѡ�������0��ֻ����1608��ASC
	//#define USE_Chinese_FONT	1	//�Ƿ�ʹ��������ʾ�����û�õ�����0���򲻻������غ������ֿ�

/*_______________________________���¶��ǹ̶��ģ����ö�______________________________________*/

//LCD��Ҫ������
typedef struct  
{		 	 
	u16 width;			//LCD ���
	u16 height;			//LCD �߶�
	u16 id;				//LCD ID
	u8  dir;			//���������������ƣ�0��������1��������	
	u16	wramcmd;		//��ʼдgram��ָ��
	u16 setxcmd;		//����x����ָ��
	u16 setycmd;		//����y����ָ�� 
}_lcd_dev; 
extern _lcd_dev lcddev;	//����LCD��Ҫ����


//LCD�Ļ�����ɫ�ͱ���ɫ	   
extern u16  POINT_COLOR;//Ĭ�Ϻ�ɫ    
extern u16  BACK_COLOR; //������ɫ��Ĭ��Ϊ��ɫ


//ɨ�跽����
#define L2R_U2D  0 		//������,���ϵ���
#define L2R_D2U  1 		//������,���µ��ϡ�������IO������Ϊ������
#define R2L_U2D  2 		//���ҵ���,���ϵ��¡�������IO������Ϊ������
#define R2L_D2U  3 		//���ҵ���,���µ���

#define U2D_L2R  4 		//���ϵ���,�����ҡ�������IO������Ϊ��������
#define U2D_R2L  5 		//���ϵ���,���ҵ���
#define D2U_L2R  6 		//���µ���,������
#define D2U_R2L  7		//���µ���,���ҵ��󡪡�����IO������Ϊ��������

/*_______________________�û��޸�___________________________________*/
#define DFT_SCAN_DIR  L2R_D2U  //Ĭ�ϵ�ɨ�跽��

//������ɫ������16λ��ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
//#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)


#define	LCD_CS_SET  GPIOB->BSRR=1<<6    //Ƭѡ�˿�  	PB6
#define	LCD_RS_SET	GPIOB->BSRR=1<<5    //����/����   	PB5	   
#define	LCD_WR_SET	GPIOB->BSRR=1<<4    //д����		PB4
#define	LCD_RD_SET	GPIOB->BSRR=1<<3    //������		PB3
#define	LCD_RST_SET	GPIOB->BSRR=1<<7    //��λ			PB7
								    
#define	LCD_CS_CLR  GPIOB->BSRR=1<<(6+16)     //Ƭѡ�˿�  	PB6
#define	LCD_RS_CLR	GPIOB->BSRR=1<<(5+16)     //����/����  	PB5	   
#define	LCD_WR_CLR	GPIOB->BSRR=1<<(4+16)     //д����		PB4
#define	LCD_RD_CLR	GPIOB->BSRR=1<<(3+16)     //������		PB3
#define	LCD_RST_CLR	GPIOB->BSRR=1<<(7+16)     //��λ		PB7	

//#define	LCD_CS_SET  PBout(6) = 1    //Ƭѡ�˿�  	PB6
//#define	LCD_RS_SET	PBout(5) = 1    //����/����   	PB5	   
//#define	LCD_WR_SET	PBout(4) = 1    //д����		PB4
//#define	LCD_RD_SET	PBout(3) = 1    //������		PB3
//#define	LCD_RST_SET	PBout(7) = 1    //��λ			PB7
//								    
//#define	LCD_CS_CLR  PBout(6) = 0     //Ƭѡ�˿�  	PB6
//#define	LCD_RS_CLR	PBout(5) = 0     //����/����  	PB5	   
//#define	LCD_WR_CLR	PBout(4) = 0     //д����		PB4
//#define	LCD_RD_CLR	PBout(3) = 0     //������		PB3
//#define	LCD_RST_CLR	PBout(7) = 0     //��λ			PB7	

#define DATAOUT(x) GPIOB->ODR = x; //�������
#define DATAIN     (GPIOB->IDR);   //��������

#define LCD_PBh8dataOut(x)	GPIOB->ODR=(((GPIOB->IDR)&0x00ff)|((x << 8)&0xff00))	//PB�߰�λ���


void LCD_with_FSMC_init_LCD(void);												//��ʼ��
void LCD_Init_no_FSMC(void);
void LCD_DisplayOn(void);													//����ʾ
void LCD_DisplayOff(void);													//����ʾ
void LCD_Clear(u32 Color);	 												//����
void LCD_SetCursor(u16 Xpos, u16 Ypos);										//���ù��
void LCD_DrawPoint(u16 x,u16 y);											//����
void LCD_Fast_DrawPoint(u16 x,u16 y,u32 color);								//���ٻ���
u32  LCD_ReadPoint(u16 x,u16 y); 											//���� 
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r);						 			//��Բ
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2);							//����
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2);		   				//������
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u32 color);		   				//��䵥ɫ
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color);				//���ָ����ɫ
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode);						//��ʾһ���ַ�
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size);  						//��ʾһ������
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode);				//��ʾ ����
void LCD_ShowString(u16 x,u16 y,u8 size,u8 *p);								//��ʾһ����ĸ�����ַ���,12/16/24/32����


void LCD_WriteReg(u16 LCD_Reg, u16 LCD_RegValue);
u16 LCD_ReadReg(u16 LCD_Reg);
void LCD_WriteRAM_Prepare(void);
void LCD_WriteRAM(u16 RGB_Code);
void LCD_Scan_Dir(u8 dir);									//������ɨ�跽��
void LCD_Display_Dir(u8 dir);								//������Ļ��ʾ����
void LCD_SSD_BackLightSet(u8 pwm);							//SSD1963 �������
void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height);	//FSMC��غ���û�е��ã����ô���	

void LCD_SetParam_4ILI9341(void);								//д��ֻ֧��ILI9341�Ĳ���
void LCD_SetWindows(u16 xStar, u16 yStar,u16 xEnd,u16 yEnd);//����IO����������غ�������
void Gui_StrCenter(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode);	//������ʾһ���ַ�����������Ӣ����ʾ
void DrawPageHead(u8 *str);										//����Ļ��������ҳ��ı���
void Gui_Drawbmp16(u16 x,u16 y,const unsigned char *p);			//��ʾ��ʾһ��16λBMPͼ��
void GUI_DrawFont16(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);
void GUI_DrawFont24(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);
void GUI_DrawFont32(u16 x, u16 y, u16 fc, u16 bc, u8 *s,u8 mode);

void Show_Str(u16 x, u16 y, u16 fc, u16 bc, u8 *str,u8 size,u8 mode);	

//LCD�ֱ������ã�ע������������ֻ����SSD1963��������
#define SSD_HOR_RESOLUTION		240		//LCDˮƽ�ֱ���
#define SSD_VER_RESOLUTION		320		//LCD��ֱ�ֱ���
//LCD������������
#define SSD_HOR_PULSE_WIDTH		1		//ˮƽ����
#define SSD_HOR_BACK_PORCH		46		//ˮƽǰ��
#define SSD_HOR_FRONT_PORCH		210		//ˮƽ����

#define SSD_VER_PULSE_WIDTH		1		//��ֱ����
#define SSD_VER_BACK_PORCH		23		//��ֱǰ��
#define SSD_VER_FRONT_PORCH		22		//��ֱǰ��
//���¼����������Զ�����
#define SSD_HT	(SSD_HOR_RESOLUTION+SSD_HOR_BACK_PORCH+SSD_HOR_FRONT_PORCH)
#define SSD_HPS	(SSD_HOR_BACK_PORCH)
#define SSD_VT 	(SSD_VER_RESOLUTION+SSD_VER_BACK_PORCH+SSD_VER_FRONT_PORCH)
#define SSD_VPS (SSD_VER_BACK_PORCH)




#endif


