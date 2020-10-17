#include "mpu6050.h"
#include "filter.h"

/**
  * ��������: д���ݵ�MPU6050�Ĵ���
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
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
  * ��������: ��MPU6050�Ĵ�����ȡ����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
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
	
	for(i=0;i<(num-1);i++){
		*Read=SimuI2C_ReadByte(&SimuI2C_Handle,1);
		Read++;
	}
	*Read=SimuI2C_ReadByte(&SimuI2C_Handle,0);
	SimuI2C_Stop(&SimuI2C_Handle);
}

unsigned char MPU6050_ID;
/**
  * ��������: ��ʼ��MPU6050оƬ
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */ 
void MPU6050_Init(void)
{
	int i=0,j=0;
	//�ڳ�ʼ��֮ǰҪ��ʱһ��ʱ�䣬��û����ʱ����ϵ�����ϵ����ݿ��ܻ����
	HAL_Delay(10);
	
	MPU6050_WriteReg(MPU6050_RA_PWR_MGMT_1, 0x00);	    //�������״̬
	MPU6050_WriteReg(MPU6050_RA_SMPLRT_DIV , 0x07);	    //�����ǲ����ʣ�1KHz
	MPU6050_WriteReg(MPU6050_RA_CONFIG , 0x06);	        //��ͨ�˲��������ã���ֹƵ����1K��������5K
	MPU6050_WriteReg(MPU6050_RA_ACCEL_CONFIG , 0x00);	//���ü��ٶȴ�����������2Gģʽ�����Լ�
	MPU6050_WriteReg(MPU6050_RA_GYRO_CONFIG, 0x18);     //�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
	
	MPU6050_ReadData(MPU6050_RA_WHO_AM_I,&MPU6050_ID,1);    //��������ַ
	if(MPU6050_ID != 0x68)
			FaultASSERT("MPU6050 dectected error!\r\n");
	else 	return;
}

/**
  * ��������: ��ȡMPU6050�ļ��ٶ�����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */ 
void MPU6050ReadAcc(short *accData)
{
    uint8_t buf[6];
    MPU6050_ReadData(MPU6050_ACC_OUT, buf, 6);
    accData[0] = (buf[0] << 8) | buf[1];
    accData[1] = (buf[2] << 8) | buf[3];
    accData[2] = (buf[4] << 8) | buf[5];
}

/**
  * ��������: ��ȡMPU6050�Ľ��ٶ�����
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */ 
void MPU6050ReadGyro(short *gyroData)
{
    uint8_t buf[6];
    MPU6050_ReadData(MPU6050_GYRO_OUT,buf,6);
    gyroData[0] = (buf[0] << 8) | buf[1];
    gyroData[1] = (buf[2] << 8) | buf[3];
    gyroData[2] = (buf[4] << 8) | buf[5];
}

/**
  * ��������: ��ȡMPU6050���¶����ݣ�ת�������϶�
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: ��
  */ 
void MPU6050_ReadTemp(short*Temperature)
{
	short temp3;
	uint8_t buf[2];
	
	MPU6050_ReadData(MPU6050_RA_TEMP_OUT_H,buf,2);     //��ȡ�¶�ֵ
  temp3= (buf[0] << 8) | buf[1];
	*Temperature=(((double) (temp3 + 13200)) / 280)-13;
}


short MPU6050_Gyro[3];	//��MPU6050������������ԭʼ����
short MPU6050_Accel[3];	//��MPU6050�����ļ��ٶȼ�ԭʼ����

float MPU6050_GyroF[3];	//��MPU6050������������ת��Ϊ��λg����ֵ
float MPU6050_AccelF[3];	//��MPU6050�����ļ��ٶȼ�ת��Ϊ��λ��/ms����ֵ

float MPU6050_Angle[3];			//����õ�������Ƕ�
float MPU6050_AngleSpeed[3];	//����õ���������ٶȣ����ڷǿ������˲���Ϊֱ�������������ݾ����˲���ֵ��


/*����ʹ����һ�ֻ����˲��㷨��
	1��Kalman_Filter
	2��first_order_filter_for_mpu
	3��QingHua_AngleCal
*/
u8 MPU6050_which_filter = 1;

#include "pid.h" /*ʹ��һ���˲�*/
#include "sysVar.h" /*ʹ��M_PIֵ*/
/**
  * ��������: ����õ�������ǶȺͽ��ٶ�
  * �������: ��
  * �� �� ֵ: ��
  * ˵    ��: �����������10msѭ�����ã����ٶȵ�λΪg�������ǵ�λΪ��/ms�����ԣ����ms���оͻ�s����Ӧ���廪�˲���Td�ĳ�1000��
  */ 
void MPU6050_GetAngle(float* Angle[3],float* AngleSpeed[3])
{
	float angleAnddot[3][2],buf[3][2];
	u8 i;
	
	/*����ԭʼ����*/
	MPU6050ReadAcc(MPU6050_Accel);
	MPU6050ReadGyro(MPU6050_Gyro);
	
	/*�޷�*/
	for(i = 0;i < 3;i++)
	{
		if(MPU6050_Gyro[i] > )
		{
			
		}
		
		if(MPU6050_Accel[i] > )
		{
			
		}
	}
	
	/*�Ѽ��ٶȼƵ�ֵתΪ��������ͬλ�õĽǶ�ֵ*/
	MPU6050_GyroF[0] = ((float)atan2(MPU6050_Gyro[1],MPU6050_Gyro[2]))*180.0f/M_PI;	//tan(��x) = tan(��yz) = Ry/Rz
	MPU6050_GyroF[1] = ((float)atan2(MPU6050_Gyro[0],MPU6050_Gyro[2]))*180.0f/M_PI;	//tan(��y) = tan(��xz) = Rx/Rz
	MPU6050_GyroF[2] = ((float)atan2(MPU6050_Gyro[0],MPU6050_Gyro[1]))*180.0f/M_PI;	//tan(��z) = tan(��xy) = Rx/Ry
	
	
	/*��λת�������ٶȵ�λΪg�������ǵ�λΪ��/ms*/
	for(i = 0;i < 3;i++)
	{
		MPU6050_GyroF[i] = 		MPU6050_Gyro[i];
		MPU6050_AccelF[i] = 	MPU6050_Accel[i];
	}
	
	
	switch(MPU6050_which_filter)
	{
		case 1:
			for(i = 0;i < 3;i++)
			{	
				Kalman_Filter((float)MPU6050_Accel[i], (float)MPU6050_Gyro[i], MPU6050_Angle[i],angleAnddot[i]);
				MPU6050_Angle[i] = 		angleAnddot[i][0];
				MPU6050_AngleSpeed[i] = angleAnddot[i][1];
			}
			break;
		case 2:
			for(i = 0;i < 3;i++)
			{	
				buf[i][0] = (float)MPU6050_Accel[i]; //��תΪfloat����
				buf[i][1] = (float)MPU6050_Gyro[i];
				MPU6050_Angle[i] = first_order_filter_for_mpu(&buf[i][0], &buf[i][1],&MPU6050_Angle[i]);
				MPU6050_AngleSpeed[i] = FirstOrderLPF(MPU6050_GyroF[i]); //���ڷǿ������˲���Ϊֱ�������������ݾ����˲���ֵ
			}
			break;
		case 3:
			for(i = 0;i < 3;i++)
			{	
				buf[i][0] = (float)MPU6050_Accel[i]; //��תΪfloat����
				buf[i][1] = (float)MPU6050_Gyro[i];
				MPU6050_Angle[i] = QingHua_AngleCal(&buf[i][0], &buf[i][1],&MPU6050_Angle[i]);
				MPU6050_AngleSpeed[i] = FirstOrderLPF(MPU6050_GyroF[i]); //���ڷǿ������˲���Ϊֱ�������������ݾ����˲���ֵ
			}
			break;
		default:
			break;
	}
}



