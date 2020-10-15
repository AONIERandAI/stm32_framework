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
	TODO��ʵ�ַ�����ʾ		
		OLED_ShowString(0,6,"ASCII:",16);
		
		
		
		OLED_DrawBMP(0,0,128,8,BMP1);
		
		
*/
	 



