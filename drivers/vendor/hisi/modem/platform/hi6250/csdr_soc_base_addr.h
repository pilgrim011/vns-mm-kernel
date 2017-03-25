/******************************************************************************

                 ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_baseaddr_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2012-12-08 16:50:26
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��12��8��
    ��    ��   : f00204170
    �޸�����   : �ӡ�Hi6620V100 SOC�Ĵ����ֲ�_BaseAddr.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __CSDR_SOC_BASE_ADDR_H__
#define __CSDR_SOC_BASE_ADDR_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/


#include "csdr_platform.h"

#define SOC_BBP_CDMA_BASE_ADDR          (g_stPlatformContext.stBaseAddr.uwBbpCdmaBaseAddr)
#define SOC_BBP_CDMA_ON_BASE_ADDR       (g_stPlatformContext.stBaseAddr.uwBbpCdmaOnBaseAddr)
#define SOC_Modem_DMAC_BASE_ADDR        (g_stPlatformContext.stBaseAddr.uwEdmaBaseAddr)
#define SOC_IPC_S_BASE_ADDR             (g_stPlatformContext.stBaseAddr.uwIpcmBaseAddr)
#define SOC_SOCP_BASE_ADDR              (g_stPlatformContext.stBaseAddr.uwSocpBaseAddr)
#define SOC_AO_SCTRL_BASE_ADDR          (g_stPlatformContext.stBaseAddr.uw32kBaseAddr)
#define SOC_MODEM_SCTRL_BASE_ADDR       (g_stPlatformContext.stBaseAddr.uwSysctrlBaseAddr)
#define SOC_ABB_CFG_BASE_ADDR           (g_stPlatformContext.stBaseAddr.uwAbbCfgAddr)
#define SOC_BBP_COMM_BASE_ADDR          (g_stPlatformContext.stBaseAddr.uwBbpcomAddr)
#define SOC_BBP_COMM_ON_BASE_ADDR       (g_stPlatformContext.stBaseAddr.uwBbpcomOnAddr)
#define SOC_BBP_GLB_ON_BASE_ADDR        (g_stPlatformContext.stBaseAddr.uwBbpGlbOnAddr)
#define SOC_BBP_WCDMA_BASE_ADDR         (g_stPlatformContext.stBaseAddr.uwWbbpBaseAddr)
#define CSDR_DDR_RAM_BASE               (g_stPlatformContext.stBaseAddr.uwDataMailboxAddr)
#define SOC_BBP_COMM_2_BASE_ADDR        (g_stPlatformContext.stBaseAddr.uwBbpcom2Addr)
#define SOC_PMU_SSI_BASE_ADDR           (g_stPlatformContext.stBaseAddr.uwPmuSsiAddr)
#define SOC_PA_POWER_ON_BASE_ADDR       (g_stPlatformContext.stBaseAddr.uwPaPowerOnBaseAddr)
#define CSDR_HRPD_HARQ_MEM_ADDR_IN_DDR  (g_stPlatformContext.stBaseAddr.uwHarqMemAddr)
#define SOC_BBP_WDG_BASE_ADDR           (g_stPlatformContext.stBaseAddr.uwWatchDogAddr)

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/



/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/



/*****************************************************************************
  6 STRUCT����
*****************************************************************************/



/*****************************************************************************
  7 UNION����
*****************************************************************************/





/*****************************************************************************
  8 OTHERS����
*****************************************************************************/



/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of csdr_soc_base_addr.h */


