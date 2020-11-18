/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */

#include "PeriphConfigCore.h"

#if SYSTEM_SPI_SD_ENABLE
	#include "SPI_SDcard.h"
#endif


/* Definitions of physical drive number for each drive */
#define DEV_ExFLASH			0	/* �ⲿSPI FLASH��					Example: Map Ext FLASH to physical drive 0 */
#define DEV_SD				1	/* SDIO������SD��					Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB				2	/* USB�ļ��豸						Example: Map USB MSD to physical drive 2 */
#define DEV_SPI_SD			3	/* SPI������SD��					Example: Map SPI MMC/SD card to physical drive 3 */

#define ExFLASH_SECTOR_SIZE 	512
#define ExFLASH_SECTOR_COUNT	(2*1024*12) //����Ҫ��12MB�ռ䣬����Ը�Ϊ��12*1024*1024/ExFLASH_SECTOR_SIZE ��ֱ��
#define ExFLASH_BLOCK_SIZE		8			//ÿ�� BLOCK �� 8 ������

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	/*DSTATUS ���� unsigned char*/
	DSTATUS stat = STA_NOINIT;
	
	switch (pdrv) {
		case DEV_ExFLASH : 	/*�ⲿflash��ʼ��*/
			#if SYSTEM_SUPPORT_SFUD
				stat = (DRESULT)sfud_device_init(sfud_get_device(SFUD_BY25Q128ASSIG_DEVICE_INDEX));
			#endif
			return stat;

		case DEV_SD : 		/*SDIO SD����ʼ��*/
			#if SYSTEM_SDIO_SD_ENABLE
				stat = (DRESULT)SD_Init();
			#endif
			return stat;

		case DEV_USB : 		/*USB�ļ�ϵͳ��ʼ��*/
			//stat = 

			return stat;
		
		case DEV_SPI_SD :	/*SPI SD����ʼ��*/
			#if SYSTEM_SPI_SD_ENABLE
				stat = (DRESULT)SPI_SD_Init();
			#endif
			return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res = RES_ERROR;
	static u8 errCount = 0;
	if (!count)return RES_PARERR;

	switch (pdrv) {
		
			case DEV_ExFLASH : 	/*�ⲿflash��*/
				#if SYSTEM_SUPPORT_SFUD
					for(;count>0;count--)
					{
						res = (DRESULT)sfud_read(sfud_get_device(SFUD_BY25Q128ASSIG_DEVICE_INDEX), sector * ExFLASH_SECTOR_SIZE, ExFLASH_SECTOR_SIZE, buff);
						sector++;
						buff += ExFLASH_SECTOR_SIZE;
					}
				#endif
				return res;

			case DEV_SD : 		/*SDIO SD����*/
				#if SYSTEM_SDIO_SD_ENABLE
					res = (DRESULT)SD_ReadDisk(buff,sector,count);
					while(res)	//������
					{
						if(++errCount > 10) {errCount = 0; break;}
						SD_Init();	//���³�ʼ��SD��
						res = (DRESULT)SD_ReadDisk(buff,sector,count);	
					}
					errCount = 0;
				#endif
				return res;

			case DEV_USB :
				
				return res;
			
			case DEV_SPI_SD : /*SPI SD����*/
				#if SYSTEM_SPI_SD_ENABLE
					res = (DRESULT)SPI_SD_ReadDisk2(buff,sector,count);
					while(res)//������
					{
						if(++errCount > 10) {errCount = 0; break;}
						SPI_SD_Init();	//���³�ʼ��SD��
						res = (DRESULT)SPI_SD_ReadDisk2(buff,sector,count);
					}
					errCount = 0;
				#endif
				return res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res = RES_ERROR;
	static u8 errCount = 0;
	if (!count)return RES_PARERR;

	switch (pdrv) {
		
			case DEV_ExFLASH : /*�ⲿflashд*/
				#if SYSTEM_SUPPORT_SFUD
					for(;count>0;count--)
					{
						res = (DRESULT)sfud_write(sfud_get_device(SFUD_BY25Q128ASSIG_DEVICE_INDEX), sector * ExFLASH_SECTOR_SIZE, ExFLASH_SECTOR_SIZE, buff);
						sector++;
						buff += ExFLASH_SECTOR_SIZE;
					}
				#endif
				return res;

			case DEV_SD : 	/*SDIO SD��д*/
				#if SYSTEM_SDIO_SD_ENABLE
					res = (DRESULT)SD_WriteDisk((u8*)buff,sector,count);
					while(res)	//д����
					{
						if(++errCount > 10) {errCount = 0; break;}
						SD_Init();	//���³�ʼ��SD��
						res = (DRESULT)SD_WriteDisk((u8*)buff,sector,count);	
					}
					errCount = 0;
				#endif
				return res;

			case DEV_USB :
				
				return res;
			
			case DEV_SPI_SD : /*SPI SD��д*/
				#if SYSTEM_SPI_SD_ENABLE
					res = (DRESULT)SPI_SD_WriteDisk2((u8*)buff,sector,count);
					while(res)//д����
					{
						if(++errCount > 10) {errCount = 0; break;}
						SPI_SD_Init();	//���³�ʼ��SD��
						res = (DRESULT)SPI_SD_WriteDisk2((u8*)buff,sector,count);	
					}
					errCount = 0;
				#endif
				return res;
	}

	return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data ����ʹ��ʱָ��һ��NULL*/
)
{
	DRESULT res = RES_PARERR;

	switch (pdrv) {
		
			case DEV_ExFLASH : /*�ⲿflash����*/
				switch(cmd)
				{
					case CTRL_SYNC:
						res = RES_OK; 
						break;	 
					case GET_SECTOR_SIZE:
						*(DWORD*)buff = ExFLASH_SECTOR_SIZE; 
						res = RES_OK;
						break;	 
					case GET_BLOCK_SIZE:
						*(WORD*)buff = ExFLASH_BLOCK_SIZE;
						res = RES_OK;
						break;	 
					case GET_SECTOR_COUNT:
						*(WORD*)buff = ExFLASH_SECTOR_COUNT;
						res = RES_OK;
						break;
					default:
						res = RES_PARERR;
						break;
				}
				return res;

			case DEV_SD : 	/*SDIO SD������*/
				#if SYSTEM_SDIO_SD_ENABLE
					switch(cmd)
					{
						case CTRL_SYNC:
							res = RES_OK; 
							break;	 
						case GET_SECTOR_SIZE:
							*(DWORD*)buff = 512; 
							res = RES_OK;
							break;	 
						case GET_BLOCK_SIZE:
							*(WORD*)buff = SDCardInfo.LogBlockSize;
							res = RES_OK;
							break;	 
						case GET_SECTOR_COUNT:
							*(DWORD*)buff = SDCardInfo.LogBlockNbr;
							res = RES_OK;
							break;
						default:
							res = RES_PARERR;
							break;
					}
				#endif
				return res;

			case DEV_USB :
				
				return res;
			
			case DEV_SPI_SD : /*SPI SD������*/
				#if SYSTEM_SPI_SD_ENABLE
					switch(cmd)
					{
						case CTRL_SYNC:
							res = RES_OK; 
							break;	 
						case GET_SECTOR_SIZE:
							*(DWORD*)buff = 512; 
							res = RES_OK;
							break;	 
						case GET_BLOCK_SIZE:
							*(WORD*)buff = SPI_SDcardInfo.CardBlockSize;
							res = RES_OK;
							break;	 
						case GET_SECTOR_COUNT:
							*(DWORD*)buff = SPI_SDcardInfo.CardCapacity/512;
							res = RES_OK;
							break;
						default:
							res = RES_PARERR;
							break;
					}
				#endif
				return res;
	}
	return RES_PARERR;
}

/*
����RTCʱ�䣬��ʽ��
	7bits				4bits		5bits		5bits		6bits		5bits
	31~25				24~21		20~16		15~11		10~5		4~0
��1980��ʼ�ĵڼ���		1~12��		1~31��		0~23Сʱ	0~59��		0~29��
*/
DWORD get_fattime (void)
{
	DWORD RTC_buf = 0x00000000;
	#if SYSTEM_RTC_ENABLE //���ô˹��ܣ���Ҫ��RTC
		RTC_TimeTypeDef RTC_RealTime;
		RTC_DateTypeDef	RTC_RealDate;
		HAL_RTC_GetTime(&RTC_Handler, &RTC_RealTime, RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&RTC_Handler, &RTC_RealDate, RTC_FORMAT_BIN);
		
		RTC_buf |= ((DWORD)(RTC_RealDate.Year+1970-1980)) << 25;
		RTC_buf |= ((DWORD)(RTC_RealDate.Month)) << 21;
		RTC_buf |= ((DWORD)(RTC_RealDate.Date)) << 16;
		RTC_buf |= ((DWORD)(RTC_RealTime.Hours)) << 11;
		RTC_buf |= ((DWORD)(RTC_RealTime.Minutes)) << 5;
		RTC_buf |= (DWORD)(RTC_RealTime.Seconds > 29 ? 29 : RTC_RealTime.Seconds);
		return RTC_buf;
	#else
		RTC_buf |= ((DWORD)(2020 - 1980)) << 25;
		RTC_buf |= ((DWORD)(9)) << 21;
		RTC_buf |= ((DWORD)(16)) << 16;
		RTC_buf |= ((DWORD)(14)) << 11;
		RTC_buf |= ((DWORD)(55)) << 5;
		RTC_buf |= (DWORD)(3);
		return RTC_buf;
	#endif
}

