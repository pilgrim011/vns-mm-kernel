/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsSndAds.h
  �� �� ��   : ����
  ��    ��   : m00217266
  ��������   : 2014��1��27��
  ����޸�   :
  ��������   : TafApsSndAds.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��1��27��
    ��    ��   : m00217266
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __TAF_APS_SNDADS_H__
#define __TAF_APS_SNDADS_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "Ps.h"
#include "AdsInterface.h"
#include "Taf_Aps.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* Added by m00217266 for L-C��������Ŀ, 2014-1-26, begin */
/* APP QOS: */
#define TAF_APS_APP_QOS_TRAFFIC_CLASS_CONVERSATIONAL        (0)
#define TAF_APS_APP_QOS_TRAFFIC_CLASS_STREAMING             (1)
#define TAF_APS_APP_QOS_TRAFFIC_CLASS_INTERACTIVE           (2)
#define TAF_APS_APP_QOS_TRAFFIC_CLASS_BACKGROUND            (3)

/* APP QOS: Traffic Handling */
#define TAF_APS_APP_QOS_TRAFFIC_HANDLING_PRIORITY_1         (1)
#define TAF_APS_APP_QOS_TRAFFIC_HANDLING_PRIORITY_2         (2)
#define TAF_APS_APP_QOS_TRAFFIC_HANDLING_PRIORITY_3         (3)

/* APP QOS: Source Statistic Descriptor */
#define TAF_APS_APP_QOS_SRC_STATS_DESCRIPTOR_UNKNOWN        (0)
#define TAF_APS_APP_QOS_SRC_STATS_DESCRIPTOR_SPEECH         (1)

/* APP QOS: Transfer Delay */
#define TAF_APS_APP_QOS_TRANSFER_DELAY_150MS                (150)

/* APP QOS: Signal Ind */
#define TAF_APS_APP_QOS_SIGNAL_IND_NOT_OPTIMISE             (0)
#define TAF_APS_APP_QOS_SIGNAL_IND_OPTIMISE                 (1)
/* Added by m00217266 for L-C��������Ŀ, 2014-1-26, end */

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

/* Added by m00217266 for L-C��������Ŀ, 2014-1-26, begin */
ADS_QCI_TYPE_ENUM_UINT8 TAF_APS_QosParaTransferToQci(
    TAF_UMTS_QOS_STRU                   *pQos
);

VOS_VOID TAF_APS_SendAdsPdpStatusInd(
    VOS_UINT32                          ulPid,
    ADS_PDP_STATUS_IND_STRU            *pstAdsInd
);

VOS_VOID TAF_APS_NotifyAdsWhenPdpModify(
    TAF_PS_CALL_PDP_MODIFY_CNF_STRU    *pstEvent
);

VOS_VOID TAF_APS_NotifyAdsWhenPdpDeactivated(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU    *pstEvent
);

VOS_VOID TAF_APS_NotifyAdsWhenPdpAvtivated(
    TAF_PS_CALL_PDP_ACTIVATE_CNF_STRU  *pstEvent
);
/* Added by m00217266 for L-C��������Ŀ, 2014-1-26, end */

ADS_CLEAN_RCV_CB_FLAG_ENUM_UINT8 TAF_APS_GetCleanRcvCbFlag(
    TAF_PS_CALL_PDP_DEACTIVATE_CNF_STRU *pstEvent
);

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

#endif /* end of TafApsSndAds.h */

