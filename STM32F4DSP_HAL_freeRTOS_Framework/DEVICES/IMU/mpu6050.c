#include "mpu6050.h"
#include "filter.h"

/*说明  要使用软件 I2C 库，应该把 SYSTEM_SUPPORT_simui2c 宏定义打开，并补充 SimuI2C_Handle 的内容*/
//SimuI2C SimuI2C_Handle;

/**
  * 函数功能: 写数据到MPU6050寄存器
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */ 
void MPU6050_WriteReg(uint8_t reg_add,uint8_t reg_dat)
{
	SimuI2C_Start(&SimuI2C_Handle);
	
	SimuI2C_WriteByte(&SimuI2C_Handle,MPU6050_SLAVE_ADDRESS);
	SimuI2C_WaitAck(&SimuI2C_Handle);
	
	SimuI2C_WriteByte(&SimuI2C_Handle,reg_add);
	SimuI2C_WaitAck(&SimuI2C_Handle);
	
	SimuI2C_WriteByte(&SimuI2C_Handle,reg_dat);
	SimuI2C_WaitAck(&SimuI2C_Handle);
	
	SimuI2C_Stop(&SimuI2C_Handle);
}

/**
  * 函数功能: 从MPU6050寄存器读取数据
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */ 
void MPU6050_ReadData(uint8_t reg_add,unsigned char *Read,uint8_t num)
{
	unsigned char i;
	
	SimuI2C_Start(&SimuI2C_Handle);
	
	SimuI2C_WriteByte(&SimuI2C_Handle,MPU6050_SLAVE_ADDRESS);
	SimuI2C_WaitAck(&SimuI2C_Handle);
	
	SimuI2C_WriteByte(&SimuI2C_Handle,reg_add);
	SimuI2C_WaitAck(&SimuI2C_Handle);
	
	SimuI2C_Start(&SimuI2C_Handle);
	
	SimuI2C_WriteByte(&SimuI2C_Handle,MPU6050_SLAVE_ADDRESS + 1);
	SimuI2C_WaitAck(&SimuI2C_Handle);
	
	for(i=0;i<(num-1);i++)
	{
		*Read=SimuI2C_ReadByte(&SimuI2C_Handle,1);
		Read++;
	}
	*Read=SimuI2C_ReadByte(&SimuI2C_Handle,0);
	SimuI2C_Stop(&SimuI2C_Handle);
}

unsigned char MPU6050_ID;
/**
  * 函数功能: 初始化MPU6050芯片
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */ 
void MPU6050_Init(void)
{
	//在初始化之前要延时一段时间，若没有延时，则断电后再上电数据可能会出错
	SimuI2C_Init(&SimuI2C_Handle);
	HAL_Delay(50);
	
	MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_1,0X80);	//复位MPU6050
	HAL_Delay(100);
	MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_1,0X00);	//唤醒MPU6050 
	
	//MPU6050_WriteReg(MPU6050_RA_GYRO_CONFIG,3<<3);		//设置陀螺仪满量程范围 ，±2000dps
	MPU6050_WriteReg(MPU6050_RA_GYRO_CONFIG, 0x18);     	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)

	//MPU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG ,0<<3);		//设置加速度传感器满量程范围，±2g
	MPU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG , 0x00);		//配置加速度传感器工作在2G模式，不自检
	
	MPU6050_WriteReg(MPU6050_RA_INT_ENABLE,0X00);			//关闭所有中断
	MPU6050_WriteReg(MPU6050_RA_USER_CTRL,0X00);			//I2C主模式关闭
	MPU6050_WriteReg(MPU6050_RA_FIFO_EN,0X00);				//关闭FIFO
	MPU6050_WriteReg(MPU6050_RA_INT_PIN_CFG,0X80);			//INT引脚低电平有效
	
	MPU6050_ReadData(MPU6050_RA_WHO_AM_I,&MPU6050_ID,1);    //读器件地址
	if(MPU6050_ID != MPU6050_ADDRESS)
	{		
		FaultASSERT("MPU6050 dectected error!\r\n",1,flag_Warning);
	}else
	{
//		MPU6050_WriteReg(MPU6050_RA_SMPLRT_DIV , 0x07);	   	 	//陀螺仪采样率，1KHz
//		MPU6050_WriteReg(MPU6050_RA_CONFIG , 0x06);	        	//低通滤波器的设置，截止频率是1K，带宽是5K
		
		MPU_Set_Rate(50);										//设置采样率为50Hz，LPF为采样率的一半
		
		MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_1,0X01);			//设置CLKSEL,PLL X轴为参考
		MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_2,0X00);			//加速度与陀螺仪都工作
	}
}

/**
  * 函数功能: 读取MPU6050的加速度数据
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */ 
void MPU6050ReadAcc(short *accData)
{
    uint8_t buf[6];
    MPU6050_ReadData(MPU6050_ACC_OUT, buf, 6);
    accData[0] = ((u16)buf[0] << 8) | buf[1];
    accData[1] = ((u16)buf[2] << 8) | buf[3];
    accData[2] = ((u16)buf[4] << 8) | buf[5];
}

/**
  * 函数功能: 读取MPU6050的角速度数据
  * 输入参数: 无
  * 返 回 值: 无
  * 说    明: 无
  */ 
void MPU6050ReadGyro(short *gyroData)
{
    uint8_t buf[6];
    MPU6050_ReadData(MPU6050_GYRO_OUT,buf,6);
    gyroData[0] = ((u16)buf[0] << 8) | buf[1];
    gyroData[1] = ((u16)buf[2] << 8) | buf[3];
    gyroData[2] = ((u16)buf[4] << 8) | buf[5];
}


//设置MPU6050的数字低通滤波器
//lpf:数字低通滤波频率(Hz)
//返回值:0,设置成功
//    其他,设置失败 
void MPU_Set_LPF(u16 lpf)
{
	u8 data=0;
	if(lpf>=188)data=1;
	else if(lpf>=98)data=2;
	else if(lpf>=42)data=3;
	else if(lpf>=20)data=4;
	else if(lpf>=10)data=5;
	else data=6; 
	MPU6050_WriteReg(MPU6050_RA_CONFIG,data);//设置数字低通滤波器  
}
//设置MPU6050的采样率(假定Fs=1KHz)
//rate:4~1000(Hz)
//返回值:0,设置成功
//    其他,设置失败 
void MPU_Set_Rate(u16 rate)
{
	u8 data;
	if(rate>1000)rate=1000;
	if(rate<4)rate=4;
	data=1000/rate-1;
	MPU6050_WriteReg(MPU6050_RA_SMPLRT_DIV,data);
 	MPU_Set_LPF(rate/2);	//自动设置LPF为采样率的一半
}

//得到温度值
//返回值:温度值
float MPU_Get_Temperature(void)
{
    u8 buf[2]; 
    short raw;
	float temp;
	MPU6050_ReadData(MPU6050_RA_TEMP_OUT_H,buf,2); 
    raw=((u16)buf[0]<<8)|buf[1];  
    temp=36.53f+((float)raw)/340.0f;  
    return temp;
}


/*一阶低通滤波器：本次滤波结果=(1-a)*本次采样值+a*上次滤波结果，a越大滤波程度越高，a必须在0~1之间*/
/*a与一阶低通的时间常数T关系：a = T/(T+1),T越大滤波程度越高*/
#define LPF_A (0.69f)
float __FirstOrderLPF(float NewValue)
{
	static float LastValue,output;
	output = (1.0f - LPF_A) * NewValue + LPF_A * LastValue;
	LastValue = NewValue;
	return output;
}


#define PI_F  3.14159265358979323846f /*使用PI值*/
#include <math.h>  /*使用atan2f函数*/


/**
  * 函数功能: 计算得到的三轴角度和角速度
  * 输入参数: 前两个参数接得到的角度和角度
			  第三个参数定义使用哪一种互补滤波算法：
				1：Kalman_Filter
				2：first_order_filter_for_mpu
				3：QingHua_AngleCal
  * 返 回 值: 无
  * 说    明: 这个函数必须10ms循环调用；加速度单位为 g，陀螺仪单位为 度/ms
  */

/* TODO 还没写好...*/
void MPU6050_GetAngle(float* Angle[3],float* AngleSpeed[3],u8 which_filter)
{
//	u8 i;
//	
//	short MPU6050_Gyro_origin[3];	//从MPU6050读出的陀螺仪原始数据
//	short MPU6050_Accel_origin[3];	//从MPU6050读出的加速度计原始数据
//	
//	float MPU6050_Gyro[3];			//从MPU6050读出的陀螺仪转换为单位g的数值
//	float MPU6050_Accel[3];			//从MPU6050读出的加速度计转换为单位度/ms的数值
//	
//	static float MPU6050_Angle[3];			//计算得到的三轴角度
//	static float MPU6050_AngleSpeed[3];		//计算得到的三轴角速度（对于非卡尔曼滤波，为直接用陀螺仪数据经过滤波的值）
//	
//	/*读出原始数据*/
//	MPU6050ReadAcc(MPU6050_Accel_origin);
//	MPU6050ReadGyro(MPU6050_Gyro_origin);
//	
//	/*原始数据限幅*/
//	for(i = 0;i < 3;i++)
//	{
////		if(MPU6050_Gyro_origin[i] > )
////		{
////			
////		}
////		
////		if(MPU6050_Accel_origin[i] > )
////		{
////			
////		}
//	}
//	
//	/*单位转换，加速度单位为 g，陀螺仪单位为 度/ms*/
//	for(i = 0;i < 3;i++)
//	{
////		MPU6050_Gyro[i]  =	((float)MPU6050_Gyro_origin[i]) 	*	xx.xxf;
////		MPU6050_Accel[i] =	((float)MPU6050_Accel_origin[i])	*	xx.xxf;
//	}
//	
//	/*把加速度计的值(Gx/Gy/Gz (g)) 转为与陀螺仪同位置的 角度值(θx/θy/θz (度))*/
//	MPU6050_Accel[0] = atan2f(MPU6050_Accel[1], MPU6050_Accel[2])*180.0f/PI_F;	//tan(θx) = tan(θyz) = Ry/Rz
//	MPU6050_Accel[1] = atan2f(MPU6050_Accel[0], MPU6050_Accel[2])*180.0f/PI_F;	//tan(θy) = tan(θxz) = Rx/Rz
//	MPU6050_Accel[2] = atan2f(MPU6050_Accel[0], MPU6050_Accel[1])*180.0f/PI_F;	//tan(θz) = tan(θxy) = Rx/Ry
//	
//	
//	switch(which_filter)
//	{
//		case 1:
//			float angleAnddot[3][2];
//			for(i = 0;i < 3;i++)
//			{
//				Kalman_Filter(MPU6050_Accel[i], MPU6050_Gyro[i], MPU6050_Angle[i],angleAnddot[i]);
//				MPU6050_Angle[i] = 		angleAnddot[i][0];
//				MPU6050_AngleSpeed[i] = angleAnddot[i][1];
//			}
//			break;
//		case 2:
//			for(i = 0;i < 3;i++)
//			{
//				MPU6050_Angle[i] = first_order_filter_for_mpu(&MPU6050_Accel[i], &MPU6050_Gyro[i],&MPU6050_Angle[i]);
//				MPU6050_AngleSpeed[i] = __FirstOrderLPF(MPU6050_GyroF[i]); //对于非卡尔曼滤波，为直接用陀螺仪数据经过滤波的值
//			}
//			break;
//		case 3:
//			for(i = 0;i < 3;i++)
//			{
//				MPU6050_Angle[i] = QingHua_AngleCal(&MPU6050_Accel[i], &MPU6050_Gyro[i],&MPU6050_Angle[i]);
//				MPU6050_AngleSpeed[i] = __FirstOrderLPF(MPU6050_GyroF[i]); //对于非卡尔曼滤波，为直接用陀螺仪数据经过滤波的值
//			}
//			break;
//		default:
//			break;
//	}
//	
//	for(i = 0;i < 3;i++)
//	{
//		Angle[i] 		= MPU6050_Angle[i];
//		AngleSpeed[i]	= MPU6050_AngleSpeed[i];
//	}
}



