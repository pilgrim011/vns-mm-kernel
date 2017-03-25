/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccSndAps.h
  �� �� ��   : ����
  ��    ��   : w00242748
  ��������   : 2014��9��6��
  ����޸�   :
  ��������   : CnasXccSndAps.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��9��6��
    ��    ��   : w00242748
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CNAS_XCC_SND_APS_H__
#define __CNAS_XCC_SND_APS_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "CnasXccCtx.h"


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
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID CNAS_XCC_SndApsDataCallSuspendInd(
    VOS_UINT8                                   ucConnectId,
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32           enServiceType
);

VOS_VOID CNAS_XCC_SndApsDataCallResumeInd(
    VOS_UINT8                                   ucConnectId,
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32           enServiceType
);

VOS_VOID CNAS_XCC_SndApsOrigDataCallCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_FAIL_LAYER_ENUM_UINT8       enFailLayer,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause,
    VOS_UINT8                           ucConRef,
    VOS_UINT8                           ucConnectId,
    VOS_INT16                           sRssi
);

VOS_VOID CNAS_XCC_SndApsHangupDataCallCnf(
    VOS_UINT8                           ucCallId
);

VOS_VOID CNAS_XCC_SndApsAnswerDataCallCnf(
    VOS_UINT8                           ucCallId,
    TAF_XCC_CAUSE_ENUM_UINT32           enRslt
);

VOS_VOID CNAS_XCC_SndApsIncomingCallInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
);

VOS_VOID CNAS_XCC_SndApsDataCallConnectInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
);

VOS_VOID CNAS_XCC_SndApsDataServiceConnectInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
);

VOS_VOID CNAS_XCC_SndApsDataCallDiscInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
);


VOS_VOID CNAS_XCC_SndApsSoCtrlMsgInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo,
    CNAS_XCC_SOCM_STRU                 *pstSOCM
);

VOS_VOID CNAS_XCC_SndApsUpdateDataCallInfoInd(
    CNAS_XCC_CALL_INFO_CTX_STRU        *pstCallInfo
);

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

#endif /* end of CnasXsdSndInternalMsg.h */
