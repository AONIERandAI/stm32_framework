#ifndef __SYS_MENU_H
#define __SYS_MENU_H

#include "PeriphConfigCore.h"
#include "PeriphConfig.h"


/*______________________�����������������������Ϣ_________________________________*/
//�������Ϊ�����������������AD Key����������������ң�ء���ת��������
//ö�٣�ȫ�֣�����������ȡ��ַ
enum inputValue_enum{
	none = 0,
	up,			//������ת���������룬ֻ��"�ϡ���"��־λ
	down,
	left,
	right,
	back,
	enter
};
enum inputMode_enum{
	notRdy = 0,	//û׼����
	once,		//����
	doub,		//˫��
	lon			//����
};
//������Ϣ�ṹ��
struct input_struct
{
	enum inputValue_enum keyValue;
	enum inputMode_enum keyMode;
	
};

extern struct input_struct inputKey;


/*______________________�˵��ṹ�����ö�_________________________________*/
struct MenuItem     
{  
	char MenuCount; 					//��ǰ�˵�����Ŀ����
	char *DisplayString;  				//��ǰ�˵���Ŀ��ʾ����Ϣ
	void (*Subs)();  					//ִ�еĺ�����ָ��
	struct MenuItem *Childrenms;  		//ָ���ӽڵ��ָ��
	struct MenuItem *Parentms;  		//ָ�򸸽ڵ��ָ��
}; 
void keyProcess(void);
void menuProcess(void);
void Locate(const struct MenuItem *MenuItemNow,const char * const menuid,const int deepth);
void Run(const struct MenuItem *MenuItemNow,const struct input_struct input);
void Nop(void);


/*______________________STEP3: ����ϵͳ��Ϣ���û��޸�_________________________________*/
//����ϵͳ�������迪��״̬�����Ŀ��Ƽ���
struct sysPara_struct
{
	char lightSwt;
	char isAutoLight;
	char netSwt;
	char isAutoNet;
};
extern struct sysPara_struct sysPara;

//��������mode1��mode2��ϵͳ����
//����������ͬҳ�桢��ͬ����ģʽ������
struct runMode1_struct
{
	char isRun;//�����Ƿ�����mode1
	int Para1;//mode1�еĲ���1
	int Para2;
};
extern struct runMode1_struct RunMode1;

struct runMode2_struct
{
	char isRun;//�����Ƿ�����mode2
	int Para3;//mode2�еĲ���1
	int Para4;
};
extern struct runMode2_struct RunMode2;


//�û���������������ȫ�����const ���η������ú����ڲ��Դ�������޸ģ��ȹ��Ŀ�..
void runFunctions(const struct MenuItem *MenuItemNow,const struct input_struct input);//run������ĸ�����
void adjustFunctionsMode1(const struct MenuItem *MenuItemNow,const struct input_struct input);//adjust��Mode1�����2������
void adjustFunctionsMode2(const struct MenuItem *MenuItemNow,const struct input_struct input);//adjust��Mode2�����2������
void adjustFunctionsOption(const struct MenuItem *MenuItemNow,const struct input_struct input);//adjust��Option�����2������

#endif


