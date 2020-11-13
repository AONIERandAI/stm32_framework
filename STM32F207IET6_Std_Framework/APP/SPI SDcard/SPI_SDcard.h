#ifndef __SPI_SDCARD_H
#define __SPI_SDCARD_H

#include "system.h"
#include "simuspi.h"		//ģ��SPIЭ��


//SD��CSD�Ĵ�������		  
typedef struct
{
	u8  CSDStruct;            /*!< CSD structure */
	u8  SysSpecVersion;       /*!< System specification version */
	u8  Reserved1;            /*!< Reserved */
	u8  TAAC;                 /*!< Data read access-time 1 */
	u8  NSAC;                 /*!< Data read access-time 2 in CLK cycles */
	u8  MaxBusClkFrec;        /*!< Max. bus clock frequency */
	u16 CardComdClasses;      /*!< Card command classes */
	u8  RdBlockLen;           /*!< Max. read data block length */
	u8  PartBlockRead;        /*!< Partial blocks for read allowed */
	u8  WrBlockMisalign;      /*!< Write block misalignment */
	u8  RdBlockMisalign;      /*!< Read block misalignment */
	u8  DSRImpl;              /*!< DSR implemented */
	u8  Reserved2;            /*!< Reserved */
	u32 DeviceSize;           /*!< Device Size */
	u8  MaxRdCurrentVDDMin;   /*!< Max. read current @ VDD min */
	u8  MaxRdCurrentVDDMax;   /*!< Max. read current @ VDD max */
	u8  MaxWrCurrentVDDMin;   /*!< Max. write current @ VDD min */
	u8  MaxWrCurrentVDDMax;   /*!< Max. write current @ VDD max */
	u8  DeviceSizeMul;        /*!< Device size multiplier */
	u8  EraseGrSize;          /*!< Erase group size */
	u8  EraseGrMul;           /*!< Erase group size multiplier */
	u8  WrProtectGrSize;      /*!< Write protect group size */
	u8  WrProtectGrEnable;    /*!< Write protect group enable */
	u8  ManDeflECC;           /*!< Manufacturer default ECC */
	u8  WrSpeedFact;          /*!< Write speed factor */
	u8  MaxWrBlockLen;        /*!< Max. write data block length */
	u8  WriteBlockPaPartial;  /*!< Partial blocks for write allowed */
	u8  Reserved3;            /*!< Reserded */
	u8  ContentProtectAppli;  /*!< Content protection application */
	u8  FileFormatGrouop;     /*!< File format group */
	u8  CopyFlag;             /*!< Copy flag (OTP) */
	u8  PermWrProtect;        /*!< Permanent write protection */
	u8  TempWrProtect;        /*!< Temporary write protection */
	u8  FileFormat;           /*!< File Format */
	u8  ECC;                  /*!< ECC code */
	u8  CSD_CRC;              /*!< CSD CRC */
	u8  Reserved4;            /*!< always 1*/
}SPI_SD_CSD; 
//SD��CID�Ĵ�������
typedef struct
{
	u8  ManufacturerID;       /*!< ManufacturerID */
	u16 OEM_AppliID;          /*!< OEM/Application ID */
	u32 ProdName1;            /*!< Product Name part1 */
	u8  ProdName2;            /*!< Product Name part2*/
	u8  ProdRev;              /*!< Product Revision */
	u32 ProdSN;               /*!< Product Serial Number */
	u8  Reserved1;            /*!< Reserved1 */
	u16 ManufactDate;         /*!< Manufacturing Date */
	u8  CID_CRC;              /*!< CID CRC */
	u8  Reserved2;            /*!< always 1 */
}SPI_SD_CID;	

//SD����Ϣ,����CSD,CID������
//TODO�����Ժ�Ҫ�ö��SPI SD�����Ͱ�ÿ������CS���ż�������Ŀ�����ṹ����
//Ȼ��ø�.c�ļ���ĵײ㺯������ʼ������д�Ͷ�����Ϣ������֧�����ֲ�ͬ�Ŀ��������������Ϊ���ֿ��ľ��
typedef struct
{
  SPI_SD_CSD SD_csd;
  SPI_SD_CID SD_cid;
  long long CardCapacity;  	//SD������,��λ:�ֽ�,���֧��2^64�ֽڴ�С�Ŀ�.
  u32 CardBlockSize; 		//SD�����С	
  u16 RCA;					//����Ե�ַ
  u8 CardType;				//������
}SPI_SD_CardInfo;

extern SPI_SD_CardInfo SPI_SDcardInfo;				//SD����Ϣ����ʼ��ʱ�Զ���ȡ��
u8 SPI_SD_Init(void);								//�û��ã�һ��������ʼ��SPI������SD��
u8 SPI_SD_ReadDisk2(u8* buf,u32 sector,u8 cnt);		//�û��ã���SD��,fatfs/usb����
u8 SPI_SD_WriteDisk2(u8* buf,u32 sector,u8 cnt);	//�û��ã�дSD��,fatfs/usb����


u8 SPI_SD_ReadInfo(void);
u32 SD_GetSectorCount(void);

// SD�����Ͷ���
#define SD_TYPE_ERR     0X00
#define SD_TYPE_MMC     0X01
#define SD_TYPE_V1      0X02
#define SD_TYPE_V2      0X04
#define SD_TYPE_V2HC    0X06	   
// SD��ָ���	   
#define CMD0    0       //����λ
#define CMD1    1
#define CMD8    8       //����8 ,SEND_IF_COND
#define CMD9    9       //����9 ,��CSD����
#define CMD10   10      //����10,��CID����
#define CMD12   12      //����12,ֹͣ���ݴ���
#define CMD16   16      //����16,����SectorSize ����0x00
#define CMD17   17      //����17,��sector
#define CMD18   18      //����18,�� Multi sector
#define CMD23   23      //����23,���ö�sectorд��ǰԤ�Ȳ���N��block
#define CMD24   24      //����24,дsector
#define CMD25   25      //����25,дMulti sector
#define CMD41   41      //����41,����0x00
#define CMD55   55      //����55,����0x01
#define CMD58   58      //����58,��OCR��Ϣ
#define CMD59   59      //����59,ʹ��/��ֹCRC,Ӧ����0x00
//����д���Ӧ������
#define MSD_DATA_OK                0x05
#define MSD_DATA_CRC_ERROR         0x0B
#define MSD_DATA_WRITE_ERROR       0x0D
#define MSD_DATA_OTHER_ERROR       0xFF
//SD����Ӧ��־��
#define MSD_RESPONSE_NO_ERROR      0x00
#define MSD_IN_IDLE_STATE          0x01
#define MSD_ERASE_RESET            0x02
#define MSD_ILLEGAL_COMMAND        0x04
#define MSD_COM_CRC_ERROR          0x08
#define MSD_ERASE_SEQUENCE_ERROR   0x10
#define MSD_ADDRESS_ERROR          0x20
#define MSD_PARAMETER_ERROR        0x40
#define MSD_RESPONSE_FAILURE       0xFF


/*
�����ܽ᣺
		��SD����������Ҫ�г�ʼ��������д�������ȡ�
		1�� ��ʼ�� ���裺
		��1��      ��ʱ����74clock
		��2��      ����CMD0����Ҫ����0x01������Idle״̬
		��3��      ѭ������CMD55+ACMD41��ֱ������0x00������Ready״̬��
		�����MMC���˲�Ӧ����CMD1��
		2�� �� ���裺
		��1��      ����CMD17�����飩��CMD18����飩���������0x00
		��2��      �������ݿ�ʼ����0xfe����0xfc�� + ��ʽ����512Bytes + CRC У��2Bytes
		Ĭ����ʽ��������ݳ�����512Bytes������CMD16���á�
		3�� д ���裺
		��1��      ����CMD24�����飩��CMD25����飩д�������0x00
		��2��      �������ݿ�ʼ����0xfe����0xfc�� + ��ʽ����512Bytes + CRCУ��2Bytes
		4�� ���� ���裺
		��1��      ����CMD32����һ��������ָ���׸�Ҫ�����������ţ�SD�ֲ���˵�ǿ�ţ�
		��2��      ����CMD33,��ָ������������
		��3��      ����CMD38������ָ�����������
		��3��˳���ܵߵ���
		��Ҫע�ⷢ��CMD����ʱ������Ҫ��һ���ֽڵ�CRCУ�����ݣ���֮Ҫ��֤ÿ�η��͵����ݰ����ȷ���Э��Ҫ��������ݷ���ʱ��Ҫ��
		
		
		 ��sd����ʼ���������棬��������sd����ʼ�����̴�������һ���ģ�һЩ�ر�ĵط��У�
			1.�ڳ�ʼ�������ǰ����Ҫ����72��ʱ�����ڵ�ʱ���źŸ�sd������Ϊʹ���ź�
			2.����cmd0ʱ�����sd����⵽DAT3Ϊ����״̬���ͻ��Զ�����SPIģʽ�����ҷ���һ����Ϊ0xff��ֵ��Ϊ��Ӧ
			3.�ڷ���acmd41ʱ����������ֵ����0xff8000������0
			4.�ڶ�ȡsd��cid�Ĵ���ʱʹ�õ�������cmd10������cmd2
			5.spiģʽ��֧��ѡ������cmd3
*/



#endif

