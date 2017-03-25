/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsProcNvim.h
  �� �� ��   : ����
  ��    ��   : o00132663
  ��������   : 2011��12��15��
  ����޸�   :
  ��������   : TafApsProcNvim.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��12��15��
    ��    ��   : o00132663
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __TAFAPSPROCNVIM_H__
#define __TAFAPSPROCNVIM_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TafApsCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

VOS_VOID  TAF_APS_ReadDsFlowInfoFromNv(
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx
);
VOS_VOID  TAF_APS_ClearDsFlowInfoInNv( VOS_VOID );
VOS_VOID  TAF_APS_SaveDsFlowInfoToNv( VOS_VOID );

VOS_VOID TAF_APS_ReadPdpActLimitFlgFromNv(VOS_VOID);

VOS_VOID TAF_APS_ReadDsflowRateConfigFromNv(TAF_APS_SWITCH_DDR_RATE_INFO_STRU *pstSwitchDdrInfo);

VOS_VOID TAF_APS_Recorrect_ProfileNum(
    TAF_NV_DFS_DSFLOW_RATE_CONFIG_STRU     *pstDfsProfile,
    VOS_UINT32                              ulProfileNum);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_APS_ReadPktCdataInactivityTimeLenFromNv(VOS_VOID);


VOS_VOID TAF_APS_Read1xDataSoCfgNvim(VOS_VOID);

VOS_VOID TAF_APS_ReadCdataDiscingParaCfgFromNv(VOS_VOID);
VOS_VOID TAF_APS_ReadPppAuthInfoFromCardNv( VOS_VOID );


VOS_VOID TAF_APS_ReadCdataEhrpdAutoAttachFlagFromNv(VOS_VOID);

VOS_VOID TAF_APS_ReadCdataUlNdisFilterVaildFlagFromNv(VOS_VOID);
#endif

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_APS_ReadPdnTeardownPolicyNV(VOS_VOID);
#endif



#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of TafApsProcNvim.h */
