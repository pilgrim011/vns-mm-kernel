/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdPreProcAct.h
  �� �� ��   : ����
  ��    ��   : g00256031
  ��������   : 2014��12��10��
  ����޸�   :
  ��������   : CnasHsdPreProcAct.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��10��
    ��    ��   : g00256031
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CNAS_HSD_PRE_PROC_ACT_H__
#define __CNAS_HSD_PRE_PROC_ACT_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "CnasHsdCtx.h"
#include  "hsd_mscc_pif.h"
#include  "hsm_hsd_pif.h"
#include  "CnasHsdSndHsm.h"

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

extern VOS_UINT32 CNAS_HSD_RcvSliceReverseProtectTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#if 0
extern VOS_UINT32 CNAS_HSD_RcvTchAssignTimeoutInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

extern VOS_UINT32 CNAS_HSD_RcvCasStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_VOID CNAS_HSD_ProcHrpd1XSysAssn(CNAS_HSD_AT_STATUS_ENUM_UINT32 enHsdATStatus);

extern VOS_UINT32 CNAS_HSD_RcvPsStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_Rcv1xSysChgInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

#ifdef DMT
extern VOS_UINT32 CNAS_HSD_RcvHsdTestCfgREQ_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

VOS_UINT32 CNAS_HSD_RcvMsccSysCfgSet_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSD_RcvCasSysCfgCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
extern VOS_UINT32 CNAS_HSD_RcvMsccDisableLteNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvMsccBgSearchReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvMsccStopBgSearchReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasBsrLteCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvMsccQryHrpdSysInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasFreqListReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasStopBsrLteCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSD_RcvCasOhmNotCurrentInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvCasNetworkLostIndProc_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_VOID CNAS_HSD_AvoidNetwkLostProc(
    CNAS_HSD_NETWORK_LOST_SYS_RECORD_STRU                  *pstNetwkLostSysRec
);


extern VOS_UINT32 CNAS_HSD_RcvMsccCFreqLockSetNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvNoRFProtectTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#if 0
extern VOS_UINT32 CNAS_HSD_RcvMsccDataCallStartNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvMsccDataCallEndNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

extern VOS_UINT32 CNAS_HSD_RcvMsccDataCallSuccNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
#endif

extern VOS_UINT32 CNAS_HSD_RcvCasSuspendInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSD_RcvMsccHdrCsqSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSD_RcvCasHdrCsqSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 CNAS_HSD_RcvMsccHdrCsqQualityInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
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

#endif /* end of CnasHsdPreProcAct.h */
