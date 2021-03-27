#include "conversion.h"

//x �� Byte�Ĳ���תԴ�룬����64bit��8�ֽڣ�
signed long int Comp_to_origin_xByte(const signed long int comp_num, const unsigned char xByte)
{
	unsigned char i;
	unsigned long int temp;
	//����תԴ�룬�����Ĳ��벻�䣬�����Ĳ���ΪԴ�������λȡ����һ�������Ĳ����ٳ�����λȡ����һ��ԭ��
	//�ж����λ�Ƿ�Ϊ1
	if(comp_num & (0x80 << (xByte - 1)) )
	{
		//���� 0x7f_ff_ff��3�ֽ�Ϊ����
		for(i = 0;i < xByte;i++)
		{
			if(i == 0)
			{
				temp = (0x7F << ((xByte - 1) * 8) );
			}else
			{
				temp |= 0xFF << ((xByte - i - 1) * 8);
			}
		}
		//������λȡ����һ
		return ( (comp_num ^ temp) + 1 );
	}else
	{
		return comp_num;
	}
}
 
//������ȡ��  
int BinFlip(unsigned char *dst, const unsigned char *src, int length)  
{  
	int i;  

	for(i=0; i<length; i++)  
	{  
			dst[i] = src[i]^0xFF;  
	}  
	return 0;  
}  

/* ����������ת��ʮ������*/
int BintoDec(char *str)
{
    int sum =0;
    int j = 1;
    /*����ѭ������*/
    int pos = BitNum - 1;
    for(;pos>=0;pos--)
    {
        /*�տ�ʼ��pos��󣬶�Ӧ������������ұ�*/
        sum += (str[pos]-'0')*j;
        j *= 2;
    }
    return sum;
}



//ʮ������תΪʮ����  
unsigned long HextoDec(const unsigned char *hex, int length)  
{  
    int i;  
    unsigned long rslt = 0;  
   
    for(i=0; i<length; i++)  
    {  
        rslt += (unsigned long)(hex[i])<<(8*(length-1-i));  
                                                           
    }  
   
    return rslt;  
}  
   
   
 
//ʮ����תʮ������   
int DectoHex(int dec, unsigned char *hex, int length)  
{  
    int i;  
   
    for(i=length-1; i>=0; i--)  
    {  
        hex[i] = (dec%256)&0xFF;  
        dec /= 256;  
    }  
   
    return 0;  
}  
   
  
// ��Ȩ  
//  
// ���룺 int base                    ���ƻ���  
//        int times                   Ȩ����  
// ���أ� unsigned long               ��ǰ����λ��Ȩ  
//��ʱ����������
unsigned long power(int base, int times)  
{   
    int i;  
    unsigned long rslt = 1;  
   
    for(i=0; i<times; i++)  
        rslt *= base;  
   
    return rslt;  
}

/*��ʮ������ת���ɶ��������*/
void DectoBin(DateType num,char *code,int bitNum)
{
  //  findNegcode(num,code,bitNum);
    findNegCode_iter(num,code,bitNum,0);
    /*�ݹ���ֹ����*/
    if(num>0)   return;
    /**/
   // findNegcode(num*(-1),code,bitNum);
    findNegCode_iter(num*(-1),code,bitNum,0);
    code[0] = '1';
}
   



//ʮ����תBCD����
unsigned char DecToBCD(unsigned char _dec)
{
        unsigned char temp = 0;
        while (_dec >= 10)
        {
                temp++;
                _dec -= 10;
        }
        return ((unsigned char)(temp << 4) | _dec);
}


//BCD����תʮ����
unsigned char BCDToDec(unsigned char _BCD)
{
        unsigned char temp = 0;

        temp = ((unsigned char)(_BCD & (unsigned char)0xF0) >> (unsigned char)0x04) * 10;
        return (temp + (_BCD & (unsigned char)0x0F));
}


