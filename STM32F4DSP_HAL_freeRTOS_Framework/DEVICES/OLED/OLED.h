#ifndef __OLED_H
#define __OLED_H
#include "PeriphConfigCore.h" 




/*_________________���¶����ö�_________________*/

#define Max_Column	128
#define Max_Row		64
		     
#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����

//OLED�����ú���
void OLED_WR_Byte(unsigned dat,unsigned cmd);  
void OLED_Display_On(void);
void OLED_Display_Off(void);	   							   		    
void OLED_Init(void);
void OLED_Clear(void);
void OLED_LightMode(void);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size,u8 mode);
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size,u8 mode);	 
void OLED_Set_Pos(unsigned char x, unsigned char y);
void OLED_ShowCHinese(u8 x,u8 y,u8 no);
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void fill_picture(unsigned char fill_Data);


extern unsigned char BMP1[];

#endif


/*
API������
		OLED_Init();
		void OLED_Display_Off(void);
		void OLED_Display_On(void);
		void OLED_LightMode(void);
		OLED_Clear(); 


	TODO����ʾ�����д��޸ĸ�����ĸ�ʽ
		OLED_ShowCHinese(0,0,0);//��
		OLED_ShowCHinese(18,0,1);//��
		OLED_ShowCHinese(36,0,2);//԰
		OLED_ShowCHinese(54,0,3);//��
		OLED_ShowCHinese(72,0,4);//��
		OLED_ShowCHinese(90,0,5);//��
		OLED_ShowCHinese(108,0,6);//��
		
		
		API����˵��������TFT��һ������
		x������Ļ��ƽ�ƶ�������ؿ�ʼ��ʾ
			y������Ļ��ƽ�ƶ���8�����ؿ�ʼ��ʾ��������64/8����
				char*s�ַ�
					1��������ʾ��0��������ʾ
		OLED_ShowString(5,0,"ASCII:",12,1);
		OLED_ShowString(5,20,"ASCII:",16,0);
		OLED_DrawBMP(0,0,128,8,BMP1);
		
		
		�������̣�
			OLED_DrawBMP(0,0,128,8,BMP1);
			HAL_Delay(500);
			OLED_LightMode();
			HAL_Delay(500);
			OLED_Clear();
			OLED_ShowString(5,1,(u8*)"ASCII:",8,0);
			OLED_ShowString(5,2,(u8*)"ASCII:",16,1);
		
		
*/
	 



