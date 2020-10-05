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

#include "Periphconfig.h"	

/* Definitions of physical drive number for each drive */
#define DEV_ExFLASH			0	/* �ⲿFLASH��MMC/NAND/SPI FLASH��	Example: Map Ramdisk to physical drive 0 */
#define DEV_SD				1	/* SD��								Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB				2	/* USB�ļ��豸						Example: Map USB MSD to physical drive 2 */
#define DEV_InrFlash		3	/* STM32�ڲ�FLASH					Example: Map Inner Flash to physical drive 3 */

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	return (DSTATUS)RES_OK;
//	DSTATUS stat;
//	int result;

//	switch (pdrv) {
//	case DEV_ExFLASH :
//		result = RAM_disk_status();

//		// translate the reslut code here

//		return stat;

//	case DEV_SD :
//		result = MMC_disk_status();

//		// translate the reslut code here

//		return stat;

//	case DEV_USB :
//		result = USB_disk_status();

//		// translate the reslut code here

//		return stat;
//	}
//	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	/*DSTATUS ���� unsigned char*/
	DSTATUS stat = (DSTATUS)0;
	
	switch (pdrv) {
		case DEV_ExFLASH : /*�ⲿflash��ʼ��*/
			//stat = W25QXX_Init(); //����MMC/NAND�ȵ�

			return stat;

		case DEV_SD : 	/*SDIO SD����ʼ��*/
			#if (SYSTEM_SDIO_SD_ENABLE) && ((STM32F103xG) || (STM32F103xE))
			stat = (DSTATUS)SD_Init();
			#endif
			return stat;

		case DEV_USB :
			//stat = 

			return stat;
		
		case DEV_InrFlash :
			//stat = 

			return stat;
	}
	return (DSTATUS)STA_NOINIT;
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
	DRESULT res = (DRESULT)0;
	
	if (!count)return RES_PARERR;

	switch (pdrv) {
		
			case DEV_ExFLASH : /*�ⲿflash��*/
				
				return res;

			case DEV_SD : 	/*SDIO SD����*/
				#if (SYSTEM_SDIO_SD_ENABLE) && ((STM32F103xG) || (STM32F103xE))
				res = (DRESULT)SD_ReadDisk(buff,sector,count);
				#endif
				return res;

			case DEV_USB :
				
				return res;
			
			case DEV_InrFlash :
				
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
	DRESULT res = (DRESULT)0;
	
	if (!count)return RES_PARERR;

	switch (pdrv) {
		
			case DEV_ExFLASH : /*�ⲿflashд*/
				
				return res;

			case DEV_SD : 	/*SDIO SD��д*/
				#if (SYSTEM_SDIO_SD_ENABLE) && ((STM32F103xG) || (STM32F103xE))
				res = (DRESULT)SD_WriteDisk((u8*)buff,sector,count);
				#endif
				return res;

			case DEV_USB :
				
				return res;
			
			case DEV_InrFlash :
				
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
	DRESULT res = (DRESULT)0;

	switch (pdrv) {
		
			case DEV_ExFLASH : /*�ⲿflash����*/
				
				return res;

			case DEV_SD : 	/*SDIO SD������*/
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
						#if (SYSTEM_SDIO_SD_ENABLE) && ((STM32F103xG) || (STM32F103xE))
						*(WORD*)buff = SDCardInfo.LogBlockSize;
						#endif
						res = RES_OK;
						break;	 
					case GET_SECTOR_COUNT:
						#if (SYSTEM_SDIO_SD_ENABLE) && ((STM32F103xG) || (STM32F103xE))
						*(DWORD*)buff = SDCardInfo.LogBlockNbr;
						#endif
						res = RES_OK;
						break;
					default:
						res = RES_PARERR;
						break;
				}

				return res;

			case DEV_USB :
				
				return res;
			
			case DEV_InrFlash :
				
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
		RTC_buf |= ((DWORD)(calendar.w_year - 1980)) << 25;
		RTC_buf |= ((DWORD)(calendar.w_month)) << 21;
		RTC_buf |= ((DWORD)(calendar.w_date)) << 16;
		RTC_buf |= ((DWORD)(calendar.hour)) << 11;
		RTC_buf |= ((DWORD)(calendar.min)) << 5;
		RTC_buf |= (DWORD)(calendar.sec > 29 ? 29 : calendar.sec);
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

