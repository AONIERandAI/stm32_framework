#include "OLED.h"
#include "oledfont.h"


/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
	SimuI2C_Start(&SimuI2C_Handle);
	
	SimuI2C_WriteByte(&SimuI2C_Handle,0x78);
	SimuI2C_WaitAck(&SimuI2C_Handle);	
	
	SimuI2C_WriteByte(&SimuI2C_Handle,0x00);	//write command
	SimuI2C_WaitAck(&SimuI2C_Handle);
	
	SimuI2C_WriteByte(&SimuI2C_Handle,IIC_Command);
	SimuI2C_WaitAck(&SimuI2C_Handle);	
	SimuI2C_Stop(&SimuI2C_Handle);
}

/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
	SimuI2C_Start(&SimuI2C_Handle);
	
	SimuI2C_WriteByte(&SimuI2C_Handle,0x78);
	SimuI2C_WaitAck(&SimuI2C_Handle);
	
	SimuI2C_WriteByte(&SimuI2C_Handle,0x40);	//write data
	SimuI2C_WaitAck(&SimuI2C_Handle);	
   
	SimuI2C_WriteByte(&SimuI2C_Handle,IIC_Data);
	SimuI2C_WaitAck(&SimuI2C_Handle);	
	
	SimuI2C_Stop(&SimuI2C_Handle);
}


void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
	if(cmd)
	{
		Write_IIC_Data(dat);
	}else {
		Write_IIC_Command(dat);
	}
}

//��������
void OLED_Set_Pos(unsigned char x, unsigned char y) 
{ 	
	OLED_WR_Byte(0xb0+y,OLED_CMD);
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD); 
}   	  
//����OLED��ʾ    
void OLED_Display_On(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
	OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}
//�ر�OLED��ʾ     
void OLED_Display_Off(void)
{
	OLED_WR_Byte(0X8D,OLED_CMD);  //SET DCDC����
	OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
	OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}		   			 
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!	  
void OLED_Clear(void)  
{  
	u8 i,n;		    
	for(i=0;i<8;i++)  
	{  
		OLED_WR_Byte (0xb0+i,OLED_CMD);    //����ҳ��ַ��0~7��
		OLED_WR_Byte (0x00,OLED_CMD);      //������ʾλ�á��е͵�ַ
		OLED_WR_Byte (0x10,OLED_CMD);      //������ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)OLED_WR_Byte(0,OLED_DATA); 
	} //������ʾ
}

void OLED_LightMode(void)  
{  
	u8 i,n;	
		
	for(i=0;i<8;i++)  
	{
		OLED_Set_Pos(0,i);
		for(n=0;n<128;n++)
			OLED_WR_Byte(0xff,OLED_DATA); 
	}
}


//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//mode:0,������ʾ;1,������ʾ				 
//size:ѡ������ 16/8
//OLEDɨ�跽��Ϊ�����ϵ��£�������
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size,u8 mode)
{      	
	unsigned char c=0,i=0;	
	c=chr-' ';//�õ�ƫ�ƺ��ֵ			
	if(x>Max_Column-1){x=0;y=y+2;}
	if(Char_Size ==16)
	{
		OLED_Set_Pos(x,y);	
		for(i=0;i<8;i++)
		{	if(mode)
				 OLED_WR_Byte(F8X16[c][i],OLED_DATA);
			else OLED_WR_Byte(~F8X16[c][i],OLED_DATA);
		}
		OLED_Set_Pos(x,y+1);
		for(i=0;i<8;i++)
		{	if(mode)
				 OLED_WR_Byte(F8X16[c][i+8],OLED_DATA);
			else OLED_WR_Byte(~F8X16[c][i+8],OLED_DATA);
		}
	}else if(Char_Size == 8){	
		OLED_Set_Pos(x,y);
		for(i=0;i<6;i++)
		{	
			if(mode)
				 OLED_WR_Byte(F6x8[c][i],OLED_DATA);
			else OLED_WR_Byte(~F6x8[c][i],OLED_DATA);
		}
	}
	 
}				  

//��ʾһ���ַ��Ŵ�
void OLED_ShowString(u8 x,u8 y,u8 *chr,u8 Char_Size,u8 mode)
{
    while((*chr<='~')&&(*chr>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>(128-(Char_Size/2))){x=0;y+=Char_Size;}
        if(y>(64-Char_Size)){y=x=0;OLED_Clear();}
        OLED_ShowChar(x,y,*chr,Char_Size,mode);	 
        x+=Char_Size/2;
        chr++;
    } 
}

//��ʾ����
void OLED_ShowCHinese(u8 x,u8 y,u8 no)
{      			    
	u8 t,adder=0;
	OLED_Set_Pos(x,y);	
    for(t=0;t<16;t++)
	{
		OLED_WR_Byte(Hzk[2*no][t],OLED_DATA);
		adder+=1;
     }	
	OLED_Set_Pos(x,y+1);	
    for(t=0;t<16;t++)
	{	
		OLED_WR_Byte(Hzk[2*no+1][t],OLED_DATA);
		adder+=1;
     }					
}

//������������ʾ��ʾBMPͼƬ128��64��ʼ������(x,y),x�ķ�Χ0��127��yΪҳ�ķ�Χ0��7
void OLED_DrawBMP(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) y=y1/8;      
  else y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
		OLED_Set_Pos(x0,y);
		for(x=x0;x<x1;x++)
	    {      
	    	OLED_WR_Byte(BMP[j++],OLED_DATA);	    	
	    }
	}
} 
/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
	unsigned char m,n;
	for(m=0;m<8;m++)
	{
		OLED_WR_Byte(0xb0+m,0);		//page0-page1
		OLED_WR_Byte(0x00,0);		//low column start address
		OLED_WR_Byte(0x10,0);		//high column start address
		for(n=0;n<128;n++)
			{
				OLED_WR_Byte(fill_Data,1);
			}
	}
}

//��ʼ��SSD1306					    
void OLED_Init(void)
{ 	

//	OLED_WR_Byte(0xAE,OLED_CMD);//--display off
//	OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
//	OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
//	OLED_WR_Byte(0x40,OLED_CMD);//--set start line address  
//	
//	OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
//	
//	OLED_WR_Byte(0x81,OLED_CMD); // contract control
//	OLED_WR_Byte(0x7F,OLED_CMD);//--128   
//	
//	OLED_WR_Byte(0xA1,OLED_CMD);//set segment remap 
//	OLED_WR_Byte(0xA6,OLED_CMD);
//	
//	OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
//	OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
//	
//	OLED_WR_Byte(0xC0,OLED_CMD);//Com scan direction
////	OLED_WR_Byte(0xC8,OLED_CMD);//
//	
//	OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
//	OLED_WR_Byte(0x00,OLED_CMD);
//	
//	OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
//	OLED_WR_Byte(0x80,OLED_CMD);
//	
//	OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
//	OLED_WR_Byte(0x05,OLED_CMD);//
//	
//	OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
//	OLED_WR_Byte(0xF1,OLED_CMD);//
//	
//	OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
//	OLED_WR_Byte(0x12,OLED_CMD);//
//	
//	OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
//	OLED_WR_Byte(0x30,OLED_CMD);//
//	
//	OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
//	OLED_WR_Byte(0x14,OLED_CMD);//
//	
//	OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
	
	
	OLED_WR_Byte(0xAE,OLED_CMD); //�ر���ʾ
	OLED_WR_Byte(0xD5,OLED_CMD); //����ʱ�ӷ�Ƶ����,��Ƶ��
	OLED_WR_Byte(0x80,OLED_CMD); //[3:0],��Ƶ����;[7:4],��Ƶ��
	OLED_WR_Byte(0xA8,OLED_CMD); //��������·��
	OLED_WR_Byte(0X3F,OLED_CMD); //Ĭ��0X3F(1/64) 
	
	//OLED_WR_Byte(0xC0,OLED_CMD); //����COMɨ�跽��;bit3:0,��ͨģʽ;1,�ض���ģʽ COM[N-1]->COM0;N:����·��
	OLED_WR_Byte(0xC8,OLED_CMD); //�ڵ�ǰ�У�C8Ϊ���µ���ɨ�裬C0Ϊ���ϵ��£�ȡģʱѡ��˳��Ϊ���µ���
	
	OLED_WR_Byte(0xD3,OLED_CMD); //������ʾƫ��
	OLED_WR_Byte(0X00,OLED_CMD); //Ĭ��Ϊ0
	OLED_WR_Byte(0x40,OLED_CMD); //������ʾ��ʼ�� [5:0],����.										    
	OLED_WR_Byte(0x8D,OLED_CMD); //��ɱ�����
	OLED_WR_Byte(0x14,OLED_CMD); //bit2������/�ر�
	OLED_WR_Byte(0x20,OLED_CMD); //�����ڴ��ַģʽ
	OLED_WR_Byte(0x02,OLED_CMD); //[1:0],00���е�ַģʽ;01���е�ַģʽ;10,ҳ��ַģʽ;Ĭ��10;
	OLED_WR_Byte(0xA1,OLED_CMD); //���ض�������,bit0:0,0->0;1,0->127; //����ɨ��˳��
	
	OLED_WR_Byte(0xDA,OLED_CMD); //����COMӲ����������
	OLED_WR_Byte(0x12,OLED_CMD); //[5:4]����	 
	OLED_WR_Byte(0x81,OLED_CMD); //�Աȶ�����
	OLED_WR_Byte(0x7F,OLED_CMD); //1~255;Ĭ��0X7F (��������,Խ��Խ��)
	OLED_WR_Byte(0xD9,OLED_CMD); //����Ԥ�������
	OLED_WR_Byte(0xf1,OLED_CMD); //[3:0],PHASE 1;[7:4],PHASE 2;
	OLED_WR_Byte(0xDB,OLED_CMD); //����VCOMH ��ѹ����
	OLED_WR_Byte(0x30,OLED_CMD); //[6:4] 000,0.65*vcc;001,0.77*vcc;011,0.83*vcc;
	OLED_WR_Byte(0xA4,OLED_CMD); //ȫ����ʾ����;bit0:1,����;0,�ر�;(����/����)
	OLED_WR_Byte(0xA6,OLED_CMD); //������ʾ��ʽ;bit0:1,������ʾ;0,������ʾ	    						   
	OLED_WR_Byte(0xAF,OLED_CMD); //������ʾ	
	HAL_Delay(5);
	OLED_Clear();
}  


