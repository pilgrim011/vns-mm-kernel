/*************************************************************************
*   ��Ȩ����(C) 2008-2013 ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  soc_memmap_mdm.h
*
*   ��    �� :  y00184236
*
*   ��    �� :  k3v3 v7r2 MODEM(A9) memory map
*
*   �޸ļ�¼ :  2013��8��30��  v1.00  y00184236  ����
*************************************************************************/

#ifndef __SOC_MEMMAP_MDM_H__
#define __SOC_MEMMAP_MDM_H__
#if 0
#ifdef __cplusplus
extern "C" {
#endif

#include "soc_memmap_comm.h"
/* timer: timer 0-7 ,C COREʹ��*/
#define HI_TIMER_00TO07_REGBASE_ADDR      (0xE0202000)
#define HI_TIMER_00TO07_REG_SIZE          (SZ_4K)

#define HI_TIMER_04_REGBASE_ADDR          (HI_TIMER_00TO07_REGBASE_ADDR+0x50)

#ifdef __cplusplus
}
#endif
#endif
#endif    /* __SOC_MEMMAP_MDM_H__ */

