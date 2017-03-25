/************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : MmGsmDifMsg.h
  Author      : ---
  Version     : V200R001
  Date        : 2005-09-08
  Description : ��ͷ�ļ���������ģ�� GsmDifMsgProc �Ľӿڶ���
  History     :
  1. Date:2005-04-19
     Author: ---
     Modification:Create
  2. s46746 2006-03-39  �������ⵥA32D02486�޸�
  3.��    ��   : 2006��08��09��
    ��    ��   : ����Ƽj60010247
    �޸�����   : ���ⵥA32D03479����PC����ʵ��ʱ��#pragma pack(0)��#pragma pack()�ӱ��뿪��
  4.��    ��   : 2006��11��22��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:A32D07372
************************************************************************/

#ifndef _MM_GSMDIFMSG_H_
#define _MM_GSMDIFMSG_H_

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MM_T3212_UNIT_TRANSFORM         360000/*(6 * 60 * 1000)*/

/*******************************************************************************
  3 ö�ٶ���
*******************************************************************************/

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/
/*ģ���������士HEADER
 */


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
  8 OTHERS����
*****************************************************************************/
/* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, begin */

/* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-15, end */
VOS_UINT8 MM_RcvGsmRrcPagingInd(VOS_VOID *pRcvMsg);

VOS_UINT8 MM_RcvGsmRrcSyncInd(VOS_VOID *pRcvMsg);

VOS_INT32 MM_GasRrDataReq(VOS_UINT8 ucCnDomain, VOS_UINT8 ucPriority,
                          VOS_UINT32 ulSize, VOS_INT8 *pData);

VOS_UINT32  MM_SupplementNsdInfo(VOS_UINT8 *pData);

VOS_INT32 MM_WasRrDataReq(VOS_UINT8 ucCnDomain, VOS_UINT8 ucPriority,
                          VOS_UINT32 ulSize, VOS_INT8 *pData);

VOS_INT32 MM_GasRrEstReq(VOS_UINT32 ulOpId, VOS_UINT8 ucCnDomain,
                         VOS_UINT32 ulEstCause, IDNNS_STRU *pIdnnsInfo, RRC_PLMN_ID_STRU *pstPlmnId,
                         VOS_UINT32 ulSize, VOS_INT8 *pFisrstMsg);

VOS_INT32 MM_WasRrEstReq(VOS_UINT32 ulOpId, VOS_UINT8 ucCnDomain,
                         VOS_UINT32 ulEstCause, IDNNS_STRU *pIdnnsInfo, RRC_PLMN_ID_STRU *pstPlmnId,
                         VOS_UINT32 ulSize, VOS_INT8 *pFisrstMsg);


VOS_INT32 MM_GasRrRelReq(VOS_UINT8 ucCnDomain,RRC_CELL_BAR_ENUM_UINT32 enBarValidFlg);

/*VOS_INT32 MM_GasRrAbortReq(VOS_UINT32 ulAbortType);*/

VOS_INT32 MM_GasAttachReq(ATTACH_INFO_STRU *pAttachInfo);

VOS_INT32 MM_GasUsimStatusReq(USIM_VALID_INFO_STRU *pUsimValidInfo);

VOS_INT32 MM_GasSecurityKeyChgReq(SECURITY_KEY_INFO_STRU *pSecurityKeyInfo);

VOS_INT32 MM_GasTmsiLaiChgReq(NAS_INFO_TMSI_LAI_STRU *pTmsiLai);

VOS_INT32 MM_GasDelKeyReq(VOS_UINT8 ucCnDomain);


#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of MmGsmDifMsg.h */
