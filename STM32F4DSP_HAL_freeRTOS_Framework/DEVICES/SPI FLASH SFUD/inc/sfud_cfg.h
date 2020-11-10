/*
 * This file is part of the Serial Flash Universal Driver Library.
 *
 * Copyright (c) 2016-2018, Armink, <armink.ztl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: It is the configure head file for this library.
 * Created on: 2016-04-23
 */

#ifndef _SFUD_CFG_H_
#define _SFUD_CFG_H_

/*��Դ���ַ��https://github.com/armink/SFUD*/

/*ע�⣬��Դ�����ʱ��sfud_cfg.h �� sfud_port.c �� sfud_flash_def.h �������ļ����Բ�Ҫֱ�Ӹ��ǵ���
	��Ϊ�������ļ�����������"stm32_framework"�޸Ĺ�*/

/*֧�ֵĴ���FLASH�ͺţ�
	1������֧��SFUD��׼���ͺ�
		������SFUD��׼�涨�ˣ�ÿ�� Flash �л����һ���������ñ��л��� Flash ������д���ȡ����������ַģʽ�� Flash ��������
				���Ա����ڳ�ʼ��ʱ�����ȶ�ȡ SFDP �������
	2������Ĭ��������ͺţ������� sfud_flash_def.h �е� SFUD_FLASH_CHIP_TABLE �����г���
	3���û���ӵ��ͺţ�
		1���� SFUD_FLASH_CHIP_TABLE�����±��������ͺŵ���Ϣ��
		���磺| ���� | ������ ID | ���� ID | ���� ID | ���� | дģʽ | �������ȣ���������С��λ�� | �������ȶ�Ӧ������ | 
				{"GD25Q64B", SFUD_MF_ID_GIGADEVICE, 0x40, 0x17, 8*1024*1024, SFUD_WM_PAGE_256B, 4096, 0x20},
		2��Ȼ����������� SFUD_FLASH_DEVICE_TABLE ���FLASH���û��豸��Ϣ
*/

#define SFUD_Use_simuSPI_or_hardwareSPI	1	/*1��ʹ��Ӳ��SPI���裨Ĭ��SPI1����0��ʹ�����ģ��SPI*/

#define SFUD_DEBUG_MODE
/*�Ӵ��ڴ�ӡ��Ϣ*/

//#define SFUD_USING_QSPI
/*������SFUD Ҳ��֧��ʹ�� QSPI �������ӵ� Flash*/

/*
	���û���FLASHоƬ����Ĭ��������ͺţ�
		����������� SFUD_FLASH_CHIP_TABLE �����е�оƬ���û��豸��Ϣ�����Բ������û�е�
	
	���û���FLASHоƬ����Ĭ��û������ͺţ�
		1���� SFUD_FLASH_CHIP_TABLE�����±��������ͺŵ���Ϣ��
			���磺| ���� | ������ ID | ���� ID | ���� ID | ���� | дģʽ | �������ȣ���������С��λ�� | �������ȶ�Ӧ������ | 
					{"GD25Q64B", SFUD_MF_ID_GIGADEVICE, 0x40, 0x17, 8*1024*1024, SFUD_WM_PAGE_256B, 4096, 0x20},
		2��Ȼ�������������FLASH���û��豸��Ϣ
*/
enum {
	SFUD_BY25Q128ASSIG_DEVICE_INDEX = 0,
};

#define SFUD_FLASH_DEVICE_TABLE                                               		\
{                                                                              		\
	[SFUD_BY25Q128ASSIG_DEVICE_INDEX] = {.name = "BY25Q128ASSIG", .spi.name = "SPI1"},		\
}


/*
	API��
&		��ʼ�� SFUD �⣺		sfud_err sfud_init(void)
			��������һ��ʼ���豸�� SFUD_FLASH_DEVICE_TABLE ���ж���ĵ����д���FLASH
			ע�⣺��ʼ����� SPI Flash Ĭ�϶� ��ȡ��д���� ״̬�����迪��д��������ʹ�� sfud_write_status �����޸� SPI Flash ״̬��
		
&		��ȡ Flash �豸����	sfud_flash *sfud_get_device(size_t index)
			�������������ΪFlash �豸λ�� FLash �豸��SFUD_FLASH_DEVICE_TABLE���е�����ֵ��
				  ������ͨ�� Flash �豸λ���豸��������ֵ������ Flash �豸���󣬳����豸��Χ���� NULL
			���磺				const sfud_flash *flash = sfud_get_device(SFUD_BY25Q128ASSIG_DEVICE_INDEX);
		
&		��ʼ��ָ���� Flash �豸��sfud_err sfud_device_init(sfud_flash *flash)
		
			
&		��ȡ Flash ���ݣ�		sfud_err sfud_read(const sfud_flash *flash, uint32_t addr, size_t size, uint8_t *data)
			������	���������	flash	Flash �豸����
								addr	��ʼ��ַ
								size	����ʼ��ַ��ʼ��ȡ���ݵ��ܴ�С
								data	��ȡ��������
		
&		�� Flash д���ݣ�		sfud_err sfud_write(const sfud_flash *flash, uint32_t addr, size_t size, const uint8_t *data)
			���������������	flash	Flash �豸����
								addr	��ʼ��ַ
								size	����ʼ��ַ��ʼд�����ݵ��ܴ�С
								data	��д�������
		
		ʹ�ܿ��ٶ�ģʽ������ SFUD ���� QSPI ģʽ����ã����ԣ�Ҫ�õĻ����ٷ��ֲ��F4L������
			��������ȴ�ͳ�� SPI ģʽ��ʹ�� QSPI �ܹ����� Flash ���ݵĶ�ȡ������������Ҫд��ʱ������ Flash ���������д���ٶ����� SPI �����ٶȣ����� QSPI ģʽ�µ�����д���ٶ������������ԡ�
		
		��ȡ Flash ״̬����
		д���޸ģ� Flash ״̬����
		
		���� Flash ���ݣ������ã�sfud_err sfud_erase(const sfud_flash *flash, uint32_t addr, size_t size)	
			������	���������	flash	Flash �豸����
								addr	��ʼ��ַ
								size	����ʼ��ַ��ʼ�������ݵ��ܴ�С
			ע�⣺�����������ᰴ�� Flash оƬ�Ĳ������ȣ���� Flash �����ֲᣬһ��Ϊ block ��С��
					��ʼ����ɺ󣬿���ͨ�� sfud_flash->chip.erase_gran �鿴�����룬��ע�Ᵽ֤��ʼ��ַ�Ͳ������ݴ�С���� Flash оƬ�Ĳ������ȶ��룬����ִ�в��������󣬽��ᵼ���������ݶ�ʧ��
		
		���� Flash ȫ�����ݣ������ã�sfud_err sfud_chip_erase(const sfud_flash *flash)


*/
	


		
/*����Ĭ�ϲ��ö�*/
/*
������ټ��ٱ����ռ��FLASH  2KB��RAM 0.1KB��
�Ͱ����������궼ע�͵���Ȼ���Լ��ڳ�ʼ���ĵط��Լ�����FLASHоƬ��Ϣ�͵��� sfud_device_init() �����FLASH��ɳ�ʼ��

sfud_flash sfud_norflash0 = {
        .name = "norflash0",
        .spi.name = "SPI1",
        .chip = { "W25Q64FV", SFUD_MF_ID_WINBOND, 0x40, 0x17, 8L * 1024L * 1024L, SFUD_WM_PAGE_256B, 4096, 0x20 } };
......
sfud_device_init(&sfud_norflash0);
......
*/
	#define SFUD_USING_SFDP	/*�Ƿ�ʹ�� SFDP �������ܣ����������Ĭ��֧�ֵ��ͺ����Ҳ��������Ҳ������ȡоƬSFUD����*/
	/*�رպ�ֻ���ѯ�ÿ��� /sfud/inc/sfud_flash_def.h ���ṩ�� Flash ��Ϣ��������Ȼ�ή������������ԣ������ٴ�������*/

	#define SFUD_USING_FLASH_INFO_TABLE	/*�Ƿ�ʹ�øÿ��Դ��� Flash ������Ϣ��*/
	/*�رպ�ÿ�ֻ����֧�� SFDP �淶�� Flash��Ҳ���ʵ��Ľ��Ͳ��ִ�������*/

void sfud_log_debug(const char *file, const long line, const char *format, ...); /*���ö�*/
void sfud_log_info(const char *format, ...); /*���ö�*/
#endif /* _SFUD_CFG_H_ */


