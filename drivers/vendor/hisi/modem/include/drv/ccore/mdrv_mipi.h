#ifndef __MDRV_CCORE_MIPI_H__
#define __MDRV_CCORE_MIPI_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_public.h"

typedef enum{
    MIPI_ONE_BYTE  = 1,
    MIPI_TWO_BYTE  = 2,
    MIPI_THREE_BYTE= 3,
    MIPI_FOUR_BYTE = 4
}MDRV_MIPI_WR_E;
/*****************************************************************************
    * �� ��    : mdrv_mipi_write_byte
    * �� ��    : mipi ����д1��byte
    * �� ��    : @mipi_id     ʹ���ĸ�mipi ����
                         @slave_id   slave id
                         @reg_addr   Ҫд�ļĴ���ƫ��
                         @value       ��Ҫд���ֵ

    * �� ��    : ��
    * �� ��    : 0Ϊ�ɹ���-1Ϊʧ��
    * �� ��    : z00228752
    * ˵ ��    : 
    *****************************************************************************/
int mdrv_mipi_write_byte(unsigned int mipi_id, unsigned int slave_id, unsigned int reg_addr, unsigned char  value);

/*****************************************************************************
    * �� ��    : mdrv_mipi_write
    * �� ��    : mipi ��չд
    * �� ��    : @mipi_id     ʹ���ĸ�mipi ����
                        @slave_id    slave id
                        @reg_addr    Ҫд�ļĴ���ƫ��
                        @value        ��Ҫд���ֵ
                        @byte_cnt    ��Ҫд����ֽ�������ǰ֧��1��2��4�ֽڵ�д��

    * �� ��    : ��
    * �� ��    : 0Ϊ�ɹ���-1Ϊʧ��
    * �� ��    : z00228752
    * ˵ ��    : byte_cnt��Ҫ����4
    *****************************************************************************/
int mdrv_mipi_ex_write(unsigned int mipi_id, unsigned int slave_id, unsigned int reg_addr, unsigned int value, unsigned int byte_cnt);

/*****************************************************************************
    * �� ��    : mdrv_mipi_write_byte
    * �� ��    : mipi ��ͨ��1��byte
    * �� ��    : @mipi_id     ʹ���ĸ�mipi ����
                         @slave_id    slave id
                         @reg_addr   Ҫд�ļĴ���ƫ��

    * �� ��    : ��
    * �� ��    : -1Ϊʧ��,other ����ֵ
    * �� ��    : z00228752
    * ˵ ��    : ֻ�е�byteΪ��Ч�Ĵ���ֵ
    *****************************************************************************/
int mdrv_mipi_read_byte(unsigned int mipi_id, unsigned int slave_id, unsigned int reg_addr, unsigned char* value);


/*****************************************************************************
    * �� ��    : mdrv_mipi_write_byte
    * �� ��    : mipi ��չ��
    * �� ��    : @mipi_id     ʹ���ĸ�mipi ����
                        @slave_id    slave id
                        @reg_addr    Ҫд�ļĴ���ƫ��
	                 @byte_cnt	 ��Ҫд����ֽ�������ǰ֧��1��2��4�ֽڵ�д��

    * �� ��    : ��
    * �� ��    : -1Ϊʧ��,other ����ֵ
    * �� ��    : z00228752
    * ˵ ��    : byte_cnt��Ҫ����4
    *****************************************************************************/
int mdrv_mipi_ex_read(unsigned int mipi_id, unsigned int slave_id, unsigned int reg_addr, unsigned int* value, unsigned int byte_cnt);

#ifdef __cplusplus
}
#endif

#endif

