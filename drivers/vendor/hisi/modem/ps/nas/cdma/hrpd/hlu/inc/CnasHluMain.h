/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHluMain.h
  �� �� ��   : ����
  ��    ��   : y00213
  ��������   : 2014��12��17��
  ����޸�   :
  ��������   : CnasHluMain.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��17��
    ��    ��   : y00213
    �޸�����   : �����ļ�

******************************************************************************/

#ifndef __CNAS_HLU_MAIN_H__
#define __CNAS_HLU_MAIN_H__

/*****************************************************************************
  1 Include files
*****************************************************************************/
#include "CnasHluCtx.h"
#include "hsd_hlu_pif.h"

#include "hsm_hlu_pif.h"


#include "CnasHluSndHsd.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 Macro definitions
*****************************************************************************/

/*****************************************************************************
  3 ENUM define
*****************************************************************************/


/*****************************************************************************
  4 Global Variable declaration
*****************************************************************************/


/*****************************************************************************
  5 Message Header define
*****************************************************************************/


/*****************************************************************************
  6 Message define
*****************************************************************************/


/*****************************************************************************
  7 STRUCT
*****************************************************************************/


/*****************************************************************************
  8 UNION
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/


/*****************************************************************************
  10 Function declaration
*****************************************************************************/

VOS_VOID CNAS_HLU_HndlHsmHandoffReq(
    HSM_HLU_1X_TO_HRPD_HANDOFF_REQ_STRU     *pstHsmHandOffReq
);


VOS_VOID CNAS_HLU_HndlHsmSessChngInd(
    HSM_HLU_SESSION_CHANGED_IND_STRU   *pstHsmSessChngInd
);


VOS_VOID CNAS_HLU_HndlPowerOnReq(VOS_VOID);

VOS_VOID CNAS_HLU_HndlPowerOffReq(VOS_VOID);

VOS_VOID  CNAS_HLU_DispatchMsg
(
    struct MsgCB                       *pstMsg
);

VOS_VOID  CNAS_HLU_DispatchHsdMsg
(
    struct MsgCB                       *pstMsg
);

VOS_VOID  CNAS_HLU_DispatchHsmMsg
(
    struct MsgCB                       *pstMsg
);

VOS_VOID  CNAS_HLU_DispatchFsigMsg
(
    struct MsgCB                       *pstMsg
);

VOS_VOID CNAS_HLU_DispatchRpaMsg(
    struct MsgCB                       *pstMsg
);
VOS_VOID CNAS_HLU_HndlRpaCommitInd(
    CTTF_CNAS_HRPD_PA_COMMITTED_IND_STRU *pstCommitInd
);



VOS_UINT32 CNAS_HLU_InitPid
(
    enum VOS_INIT_PHASE_DEFINE         enInitPhase
);


VOS_UINT32  CNAS_HLU_InitTask();

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

#endif /* end of CnasHluCtx.h */

