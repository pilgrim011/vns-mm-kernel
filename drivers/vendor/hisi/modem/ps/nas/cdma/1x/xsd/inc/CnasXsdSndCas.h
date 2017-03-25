/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdSndCas.h
  �� �� ��   : ����
  ��    ��   : h00246512
  ��������   : 2014��7��7��
  ����޸�   :
  ��������   : CnasXsdSndCas.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��7��7��
    ��    ��   : h00246512
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CNAS_XSD_SND_CAS_H__
#define __CNAS_XSD_SND_CAS_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "CnasXsdCtx.h"
#include  "cas_1x_control_initialstate_nas_pif.h"
#include  "cas_1x_control_main_nas_pif.h"
#include  "CnasXsdCtx.h"

#include "PsRrmInterface.h"

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


VOS_VOID CNAS_XSD_SndCasPowerOffReq(VOS_VOID);

VOS_VOID CNAS_XSD_SndCasStartReq(
    MSCC_XSD_START_REQ_STRU            *pstRcvMsg
);

VOS_VOID CNAS_XSD_SndCasSysSyncReq(
    VOS_UINT32                          ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreqList
);


VOS_VOID CNAS_XSD_SndCasStopSysSyncReq(VOS_VOID);


VOS_VOID CNAS_XSD_SndCas1xCampSyncedChannelNtf(VOS_VOID);

VOS_UINT32 CNAS_XSD_SndCasCdmaCsqSetReq(
    VOS_UINT8                                               ucRssiRptThreshold,
    VOS_UINT8                                               ucEcIoRptThreshold,
    VOS_UINT8                                               ucTimeInterval
);
VOS_UINT32 CNAS_XSD_SndCasCFreqLockNtf(MSCC_XSD_CFREQ_LOCK_NTF_STRU   *pstMmaXsdCFreqLockNtf);

VOS_VOID CNAS_XSD_SndCasSysCfgReq(
    MSCC_XSD_SYS_CFG_REQ_STRU          *pstRcvMsg
);

VOS_VOID CNAS_XSD_SndCasSuspendReq(VOS_VOID);

VOS_VOID CNAS_XSD_SndRrmRegisterInd(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType
);

VOS_VOID CNAS_XSD_SndRrmDeRegisterInd(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType
);

VOS_VOID CNAS_XSD_SndCasBeginSessionNotify(
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enSessionType
);

VOS_VOID CNAS_XSD_SndCasEndSessionNotify(
    CNAS_CAS_1X_SESSION_TYPE_ENUM_UINT16                    enSessionType
);

VOS_VOID CNAS_XSD_SndCasAvailableCampQueryCnf(
    VOS_UINT16                          usOpId,
    PS_BOOL_ENUM_UINT8                  enIsCurSysCanCamp
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

#endif /* end of CnasXsdSndMscc.h */
