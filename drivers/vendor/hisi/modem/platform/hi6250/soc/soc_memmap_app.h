/*************************************************************************
*   ��Ȩ����(C) 2008-2013 ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  soc_memmap_app.h
*
*   ��    �� :  y00184236
*
*   ��    �� :  k3v3 v7r2 AP(A7/A15) memory map
*
*   �޸ļ�¼ :  2013��8��30��  v1.00  y00184236  ����
*************************************************************************/

#ifndef __SOC_MEMMAP_APP_H__
#define __SOC_MEMMAP_APP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "soc_memmap_comm.h"

/**********************begin:timer********************/
/*�ǵ�����*/
#define HI_TIMER_00_REGBASE_ADDR          0xfff00000   //��Ӧk3 timer00
#define HI_TIMER_01_REGBASE_ADDR          0xfff00000   //��Ӧk3 timer01
#define HI_TIMER_02_REGBASE_ADDR          0xfff01000   //��Ӧk3 timer10
#define HI_TIMER_03_REGBASE_ADDR          0xfff01000   //��Ӧk3 timer11
#define HI_TIMER_04_REGBASE_ADDR          0xfff02000   //��Ӧk3 timer20
#define HI_TIMER_05_REGBASE_ADDR          0xfff02000   //��Ӧk3 timer21
#define HI_TIMER_06_REGBASE_ADDR          0xfff03000   //��Ӧk3 timer30
#define HI_TIMER_07_REGBASE_ADDR          0xfff03000   //��Ӧk3 timer31

/*������*/
#define HI_TIMER_08_REGBASE_ADDR          0xe8a00000   //��Ӧk3 timer40
#define HI_TIMER_09_REGBASE_ADDR          0xe8a00000   //��Ӧk3 timer41
#define HI_TIMER_10_REGBASE_ADDR          0xe8a01000   //��Ӧk3 timer50
#define HI_TIMER_11_REGBASE_ADDR          0xe8a01000   //��Ӧk3 timer51
#define HI_TIMER_12_REGBASE_ADDR          0xe8a02000   //��Ӧk3 timer60
#define HI_TIMER_13_REGBASE_ADDR          0xe8a02000   //��Ӧk3 timer61
#define HI_TIMER_14_REGBASE_ADDR          0xe8a03000   //��Ӧk3 timer70
#define HI_TIMER_15_REGBASE_ADDR          0xe8a03000   //��Ӧk3 timer71
#define TIMER_ADDR_SIZE                   0X1000        //����timer��ַ��С
/*K3��̬����timer��׮*/
#define HI_TIMER_16_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_17_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_18_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_19_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_20_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_21_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_22_REGBASE_ADDR          0xFFFFFFFF
#define HI_TIMER_23_REGBASE_ADDR          0xFFFFFFFF

/**********************end:timer********************/

#ifdef __cplusplus
}
#endif

#endif    /* __SOC_MEMMAP_APP_H__ */

