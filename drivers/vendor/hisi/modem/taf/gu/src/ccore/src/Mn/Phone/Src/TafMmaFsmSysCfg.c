/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMmaFsmSysCfg.c
  �� �� ��   : ����
  ��    ��   : l00301449
  ��������   : 2015��04��07��
  ��������   : Sys Cfg״̬��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��04��07��
    ��    ��   : l00301449
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafMmaFsmSysCfg.h"
#include "TafMmaFsmSysCfgTbl.h"
#include "TafMmaCtx.h"
#include "TafMmaSndApp.h"
#include "TafAppMma.h"
#include "TafMmaSndInternalMsg.h"
#include "TafMmaSndMscc.h"
#include "TafMmaSndTaf.h"
#include "Taf_Status.h"
#include "TafMmaComFunc.h"
#include "TafMmaSndMtc.h"

#include "TafLog.h"

#include "NasComm.h"


#include "NasMsccPifInterface.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_MMA_FSM_SYS_CFG_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
extern STATUS_CONTEXT_STRU              g_StatusContext;

extern TAF_MMA_GLOBAL_VALUE_ST          gstMmaValue;

TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU g_astOperTypeFromGULToCLTab[TAF_MMA_GUL_RAT_SUBMODE_BUTT][TAF_MMA_CL_RAT_SUBMODE_BUTT] =
{
    /**********************************************************************************************
                    |     BYTE 1     |      BYTE 2     |       BYTE 3     | BYTE 4  |
                    {detach operation, attach operation, sys cfg operation, reserved}

     ע:  1) L->1X/HRPD/L֮��RAT�仯����g_stOperTypeFromCLtoCLTab������ɣ�����ȫ0
          2) G/U/L->L֮���RAT�仯������GUL֮���RAT�仯������ȫ0
     **********************************************************************************************/
                       /*  to 1X   ,    to  HRPD ,      to L   ,      to C   ,   to 1X&L   ,  to HRPD&L  ,    to C&L  */
    /* from G   */     {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 0, 0}, {1, 0, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}},
    /* from U   */     {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 0, 0}, {1, 0, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}},
    /* from L   */     {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 0, 0}, {1, 0, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}},
    /* from GU  */     {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 0, 0}, {1, 0, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}},
    /* from GL  */     {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 0, 0}, {1, 0, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}},
    /* from UL  */     {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 0, 0}, {1, 0, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}},
    /* from GUL */     {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 0, 0}, {1, 0, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}}
};

TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU g_astOperTypeFromCLToGULTab[TAF_MMA_CL_RAT_SUBMODE_BUTT][TAF_MMA_GUL_RAT_SUBMODE_BUTT] =
{
    /**********************************************************************************************
                    |     BYTE 1     |      BYTE 2     |       BYTE 3     | BYTE 4  |
                    {detach operation, attach operation, sys cfg operation, reserved}

     ע:  1) L->G/U/L֮��RAT�仯������GUL֮��ı仯������ȫ0
          2) 1X/HRPD/L->L֮��ı仯����g_stOperTypeFromCLtoCLTab������ɣ�����ȫ0
     **********************************************************************************************/

                       /*  to G    ,     to U    ,      to L   ,     to GU   ,     to GL   ,     to UL   ,   to GUL  */
    /* from 1X      */ {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}},
    /* from HRPD    */ {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}},
    /* from L       */ {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}},
    /* from C       */ {{0, 1, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}},
    /* from 1X&L    */ {{1, 1, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}},
    /* from HRPD&L  */ {{1, 1, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}},
    /* from C&L     */ {{1, 1, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}, {1, 1, 1, 0}}
};

TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU g_astOperTypeFromCLtoCLTab[TAF_MMA_CL_RAT_SUBMODE_BUTT][TAF_MMA_CL_RAT_SUBMODE_BUTT] =
{
    /**********************************************************************************************
     |     BYTE 1     |      BYTE 2     |       BYTE 3     | BYTE 4  |
     {detach operation, attach operation, sys cfg operation, reserved}

     ע:  1) �����RAT˳�����仯����RAT����û����������٣�����ȫ��0����1X&L->L&1X, 1X&HRPD->HRPD&1X
     **********************************************************************************************/

                       /*  to 1X   ,    to  HRPD ,      to L   ,     to C   ,    to 1X&L   ,   to HRPD&L ,  to C&L   */
    /* from 1X      */ {{0, 0, 0, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}},
    /* from HRPD    */ {{0, 0, 1, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}},
    /* from L       */ {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 0, 0}, {1, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
    /* from C       */ {{0, 0, 1, 0}, {0, 0, 1, 0}, {0, 1, 1, 0}, {0, 0, 0, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}, {0, 1, 1, 0}},
    /* from 1X&L    */ {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}},
    /* from HRPD&L  */ {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}, {0, 0, 1, 0}},
    /* from C&L     */ {{1, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 1, 0}, {1, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 1, 0}, {0, 0, 0, 0}}
};

/* �Ƹ����鵽TafMmaComFunc.c�ļ� */

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvSysCfgSetReq_SysCfg_Init
 ��������  : ��TAF_MMA_SYS_CFG_STA_INIT״̬�յ�ID_TAF_MMA_SYS_CFG_SET_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��8��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��3��
    ��    ��   : w00176964
    �޸�����   : DTS2015061601845:����ԭʼSYSCFG�����Ĳ�������

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvSysCfgSetReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_SYS_CFG_REQ_STRU                               *pstRcvMsg        = VOS_NULL_PTR;
    TAF_MMA_SYS_CFG_OPER_TYPE                               usOperType;
    TAF_MMA_DETACH_CAUSE_ENUM_UINT8                         enDetachReason;
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                    *pstLastSyscfgSet = VOS_NULL_PTR;

    /* ���������Ϣ */
    TAF_MMA_SaveCurEntryMsg(ulEventType, pstMsg);

    pstRcvMsg        = (TAF_MMA_SYS_CFG_REQ_STRU *)pstMsg;

    /* ��״̬���������б���syscfg�Ĳ�����ע: �����ò�Ҫ�����ƶ�λ�� */
    TAF_MMA_SetSysCfgPara_SysCfg(&(pstRcvMsg->stSysCfgPara));

    usOperType       = TAF_MMA_SYS_CFG_NONE_SET;

    enDetachReason   = TAF_MMA_DETACH_CAUSE_BUTT;

    TAF_MMA_GetSysCfgOperType_SysCfg(&(pstRcvMsg->stSysCfgPara),
                                     &usOperType,
                                     &enDetachReason);

    /* ��������ֱ���ϱ��ɹ� */
    if (TAF_MMA_SYS_CFG_NONE_SET == usOperType)
    {
        pstLastSyscfgSet = TAF_MMA_GetLastSyscfgSetAddr();

        TAF_MMA_SndSysCfgSetCnf(&(pstRcvMsg->stCtrl), TAF_ERR_NO_ERROR);

        /* �����õ������Ҫ���������ȼ�д��NVIM�� */
        TAF_MMA_UpdatePrioAccessMode(&(pstRcvMsg->stSysCfgPara), pstLastSyscfgSet);

        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_SYS_CFG_SUCC, VOS_FALSE);

        /* �˳�״̬�� */
        TAF_MMA_FSM_QuitSubFsm();

        return VOS_TRUE;
    }

    /* ��״̬���������м�¼�������� */
    TAF_MMA_SetSysCfgOperType_SysCfg(usOperType);

    TAF_MMA_SaveSysCfgOrigOperType_SysCfg(usOperType);

    /* ���ݲ�������ִ�в����������ؽ�� */
    TAF_MMA_ProcSysCfgOper_SysCfg(&(pstRcvMsg->stSysCfgPara),
                                  usOperType,
                                  enDetachReason);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvInterSysCfgSetReq_SysCfg_Init
 ��������  : ��TAF_MMA_SYS_CFG_STA_INIT״̬�յ�MMA_MMA_INTER_SYS_CFG_SET_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��3��
    ��    ��   : w00176964
    �޸�����   : DTS2015061601845:����ԭʼSYSCFG�����Ĳ�������

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvInterSysCfgSetReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_INTER_SYS_CFG_SET_REQ_STRU *pstRcvMsg = VOS_NULL_PTR;
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType;
    TAF_MMA_DETACH_CAUSE_ENUM_UINT8     enDetachReason;

    /* ���������Ϣ */
    TAF_MMA_SaveCurEntryMsg(ulEventType, pstMsg);

    pstRcvMsg        = (TAF_MMA_INTER_SYS_CFG_SET_REQ_STRU *)pstMsg;

    usOperType       = TAF_MMA_SYS_CFG_NONE_SET;

    enDetachReason   = TAF_MMA_DETACH_CAUSE_BUTT;

    TAF_MMA_GetSysCfgOperType_SysCfg(&(pstRcvMsg->stSysCfgPara), &usOperType, &enDetachReason);

    /* ��������ֱ���ϱ��ɹ� */
    if (TAF_MMA_SYS_CFG_NONE_SET == usOperType)
    {
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_SYS_CFG_SUCC, VOS_FALSE);

        /* �˳�״̬�� */
        TAF_MMA_FSM_QuitSubFsm();
    }
    else
    {
        /* ��״̬���������м�¼�������� */
        TAF_MMA_SetSysCfgOperType_SysCfg(usOperType);

        TAF_MMA_SaveSysCfgOrigOperType_SysCfg(usOperType);

        /* ��״̬���������б���syscfg�Ĳ��� */
        TAF_MMA_SetSysCfgPara_SysCfg(&(pstRcvMsg->stSysCfgPara));

        /* ���ݲ�������ִ�в����������ؽ�� */
        TAF_MMA_ProcSysCfgOper_SysCfg(&(pstRcvMsg->stSysCfgPara),
                                      usOperType,
                                      enDetachReason);

    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvAttachReq_SysCfg_Init
 ��������  : ��TAF_MMA_SYS_CFG_STA_INIT״̬�յ�TAF_MSG_MMA_ATTACH��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��3��
    ��    ��   : w00176964
    �޸�����   : DTS2015061601845:����ԭʼSYSCFG�����Ĳ�������

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAttachReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucOpID;
    TAF_MMA_ATTACH_REQ_STRU                                *pstAttachReqMsg = VOS_NULL_PTR;
    TAF_MMA_SYS_CFG_OPER_TYPE                               usOperType;
    NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32                    enMsccAttachType;

    /* ���������Ϣ */
    TAF_MMA_SaveCurEntryMsg(ulEventType, pstMsg);

    pstAttachReqMsg     = (TAF_MMA_ATTACH_REQ_STRU *)pstMsg;

    ucOpID              = TAF_MMA_GetAttachOpId();

    usOperType          = TAF_MMA_SYS_CFG_NONE_SET;

    enMsccAttachType    = NAS_MSCC_PIF_ATTACH_TYPE_BUTT;

    TAF_MMA_GetAttachOperType_SysCfg(pstAttachReqMsg->enAttachType, &usOperType);

    if (VOS_OK == TAF_MMA_ConvertAttachTypeToMscc(pstAttachReqMsg->enAttachType, &enMsccAttachType))
    {
        (VOS_VOID)TAF_MMA_SndMsccAttachReq(ucOpID, enMsccAttachType, TAF_MMA_ATTACH_REASON_INITIAL);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvAttachReq_SysCfg_Init():Wrong AttachType!");
    }

    /* ����������ʱ�� */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_ATTACH_CNF, TI_TAF_MMA_WAIT_MSCC_ATTACH_CNF_LEN);

    /* Ǩ��TAF_MMA_SYS_CFG_STA_WAIT_ATTACH_CNF״̬ */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_SYS_CFG_STA_WAIT_ATTACH_CNF);

    TAF_MMA_SetAttachAllowFlg(pstAttachReqMsg->enAttachType);

    /* ״̬���������б���attach�����Op Id */
    TAF_MMA_SetAttachOpId_SysCfg(ucOpID);

    /* ״̬���������б���������� */
    TAF_MMA_SetSysCfgOperType_SysCfg(usOperType);

    TAF_MMA_SaveSysCfgOrigOperType_SysCfg(usOperType);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvDetachReq_SysCfg_Init
 ��������  : ��TAF_MMA_SYS_CFG_STA_INIT״̬�յ�ID_TAF_MMA_DETACH_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��13��
    ��    ��   : h00313353
    �޸�����   : SysCfg�ع�
  3.��    ��   : 2015��12��3��
    ��    ��   : w00176964
    �޸�����   : DTS2015061601845:����ԭʼSYSCFG�����Ĳ�������
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvDetachReq_SysCfg_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_DETACH_REQ_STRU                                *pstDetachReqMsg = VOS_NULL_PTR;
    NAS_MSCC_PIF_DETACH_TYPE_ENUM_UINT32                    enMsccDetachType;
    TAF_MMA_SYS_CFG_OPER_TYPE                               usOperType;
    TAF_MMA_DETACH_TYPE_ENUM_UINT8                          enDetachType;

    /* ��ʼ�� */
    pstDetachReqMsg     = (TAF_MMA_DETACH_REQ_STRU *)pstMsg;
    usOperType          = TAF_MMA_SYS_CFG_NONE_SET;
    enMsccDetachType    = NAS_MSCC_PIF_DETACH_TYPE_BUTT;

    /* ���������Ϣ */
    TAF_MMA_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ��ȡDetach������ʶ */
    usOperType      = TAF_MMA_GetDetachOperType_SysCfg(pstDetachReqMsg->stDetachPara.enDetachDomain);

    /* ��ȡDetachType */
    enDetachType    = TAF_MMA_GetDetachTypeFromSysCfgOperType_SysCfg(usOperType);

    (VOS_VOID)TAF_MMA_ConvertDetachTypeToMscc(enDetachType, &enMsccDetachType);

    /* ��MSCC����Detach Req��Ϣ */
    (VOS_VOID)TAF_MMA_SndMsccDetachReq(pstDetachReqMsg->stCtrl.ucOpId,
                                       enMsccDetachType,
                                       TAF_MMA_DETACH_CAUSE_USER_DETACH);

    /* �����ⲿģ���ʼ��������ʱ�� */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_DETACH_CNF, TI_TAF_MMA_WAIT_MSCC_DETACH_CNF_LEN);

    /* ����״̬��״̬ */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_SYS_CFG_STA_WAIT_DETACH_CNF);

    /* ��״̬���������м�¼�������� */
    TAF_MMA_SetSysCfgOperType_SysCfg(usOperType);

    TAF_MMA_SaveSysCfgOrigOperType_SysCfg(usOperType);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcDetachCnfTriggeredByDetachReq_SysCfg
 ��������  : ��TAF_MMA_SYS_CFG_STA_WAIT_DETACH_CNF״̬�յ�ID_MSCC_MMA_DETACH_CNF�������ϢΪDETACH REQ�Ĵ���
 �������  : MSCC_MMA_DETACH_CNF_STRU           *pstDetachCnf
             TAF_MMA_CTRL_STRU                  *pstCtrl
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��14��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ProcDetachCnfTriggeredByDetachReq_SysCfg(
    MSCC_MMA_DETACH_CNF_STRU           *pstDetachCnf,
    TAF_MMA_CTRL_STRU                  *pstCtrl
)
{
    TAF_MMA_FSM_SYS_CFG_CTX_STRU       *pstSysCfgCtx = VOS_NULL_PTR;
    TAF_ERROR_CODE_ENUM_UINT32          enPhoneError;
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enDetachRslt;
    TAF_MMA_SYS_CFG_RSLT_ENUM_UINT8     enSysCfgRslt;

    /* ��ȡ��ǰ״̬���������� */
    pstSysCfgCtx = &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx);

    enDetachRslt = TAF_MMA_APP_OPER_RESULT_SUCCESS;
    enSysCfgRslt = TAF_MMA_SYS_CFG_RSLT_DETACH_SUCCESS;
    enPhoneError = TAF_ERR_NO_ERROR;

    if (NAS_MSCC_PIF_OPER_RESULT_REJECT == pstDetachCnf->enOperRslt)
    {
        enSysCfgRslt = TAF_MMA_SYS_CFG_RSLT_DETACH_FAIL;

         /* ֹͣ������ʱ�� */
        TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_DETACH_CNF);

        TAF_MMA_SndDetachCnf(pstCtrl, TAF_MMA_APP_OPER_RESULT_REJECT, TAF_MMA_SYS_CFG_RSLT_DETACH_FAIL);

        /* ����״̬���˳������Ϣ */
        TAF_MMA_SndSysCfgRsltInd(enSysCfgRslt, FALSE);

        /* �˳�״̬�� */
        TAF_MMA_FSM_QuitSubFsm();

        return;
    }

    /* �ϱ�detach��� */
    /* ֻ�ϱ���ǰ��Ч����״̬ */
    if (NAS_MSCC_PIF_SRVDOMAIN_CS == pstDetachCnf->enCnDomainId)
    {
        /* ����״̬�ϱ���ͳһ�ŵ�Sta_ServiceStatusInd()����,attach cnf �� detach cnf���������� */

        /*�����ж�DETACH�����ԭ��ֵ*/
        if (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == pstDetachCnf->enServiceStatus)
        {
            enPhoneError = TAF_ERR_PHONE_DETACH_FORBIDDEN;
        }

        /*���CS DETACH��־*/
        pstSysCfgCtx->usOperType &= ~TAF_MMA_SYS_CFG_CS_DETACH_SET;

        TAF_SDC_SetCsAttachAllowFlg(VOS_FALSE);
    }

    if (NAS_MSCC_PIF_SRVDOMAIN_PS == pstDetachCnf->enCnDomainId)
    {
        /* ����״̬�ϱ���ͳһ�ŵ�Sta_ServiceStatusInd()����,attach cnf �� detach cnf���������� */

        /*�����ж�DETACH�����ԭ��ֵ*/
        if (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == pstDetachCnf->enServiceStatus)
        {
            enPhoneError = TAF_ERR_PHONE_DETACH_FORBIDDEN;
        }

        /*���PS DETACH��־*/
        pstSysCfgCtx->usOperType &= ~TAF_MMA_SYS_CFG_PS_DETACH_SET;

        TAF_SDC_SetPsAttachAllowFlg(VOS_FALSE);
    }

    if (NAS_MSCC_PIF_SRVDOMAIN_CS_PS == pstDetachCnf->enCnDomainId)
    {
        /*���CS DETACH��־*/
        pstSysCfgCtx->usOperType &= ~TAF_MMA_SYS_CFG_CS_DETACH_SET;

        /*���PS DETACH��־*/
        pstSysCfgCtx->usOperType &= ~TAF_MMA_SYS_CFG_PS_DETACH_SET;

        TAF_SDC_SetCsAttachAllowFlg(VOS_FALSE);
        TAF_SDC_SetPsAttachAllowFlg(VOS_FALSE);
    }
    /* Modified by w00167002 for L-C��������Ŀ, 2014-2-19, begin */

    /* �Ѿ����DETACH��������� */
    if (TAF_MMA_SYS_CFG_NONE_SET == (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_DETACH_REQ_REQUIRED))
    {
        /* ֹͣ������ʱ�� */
        TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_DETACH_CNF);

        if (TAF_ERR_NO_ERROR != enPhoneError)
        {
            enDetachRslt = TAF_MMA_APP_OPER_RESULT_FAILURE;
            enSysCfgRslt = TAF_MMA_SYS_CFG_RSLT_DETACH_FAIL;
        }

        TAF_MMA_SndDetachCnf(pstCtrl, enDetachRslt, enPhoneError);

        /* ����״̬���˳������Ϣ */
        TAF_MMA_SndSysCfgRsltInd(enSysCfgRslt, VOS_FALSE);

        /* �˳�״̬�� */
        TAF_MMA_FSM_QuitSubFsm();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcDetachCnfTriggeredBySysCfgReq_SysCfg
 ��������  : ��TAF_MMA_SYS_CFG_STA_WAIT_DETACH_CNF״̬�յ�ID_MSCC_MMA_DETACH_CNF�������ϢΪSYSCFG REQ�Ĵ���
 �������  : MSCC_MMA_DETACH_CNF_STRU           *pstDetachCnf
             VOS_UINT32                          ulSndAppRsltFlg,
             TAF_MMA_CTRL_STRU                  *pstCtrl
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��10��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ProcDetachCnfTriggeredBySysCfgReq_SysCfg(
    MSCC_MMA_DETACH_CNF_STRU           *pstDetachCnf,
    VOS_UINT32                          ulSndAppRsltFlg,
    TAF_MMA_CTRL_STRU                  *pstCtrl
)
{
    NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32                    enMsccAttachType;
    TAF_MMA_FSM_SYS_CFG_CTX_STRU                           *pstSysCfgCtx = VOS_NULL_PTR;
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8                          enAttachType;
    VOS_UINT8                                               ucOpID;
    VOS_UINT8                                               ucOnlyRoamParaChanged;
    VOS_UINT8                                               ucIsNeedAttachPs;
    TAF_PH_MS_CLASS_TYPE                                    ucClassType;

    ucOnlyRoamParaChanged    = VOS_FALSE;
    ucIsNeedAttachPs         = VOS_FALSE;

    /* ��ȡ��ǰ״̬���������� */
    pstSysCfgCtx = &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx);

    /* CS DETACH����ϱ� */
    if (NAS_MSCC_PIF_SRVDOMAIN_CS == pstDetachCnf->enCnDomainId)
    {
        TAF_MMA_NotifyCsServiceChange_SysCfg(pstSysCfgCtx->usOperType);

        /*���CS DETACH��־*/
        pstSysCfgCtx->usOperType &= ~TAF_MMA_SYS_CFG_CS_DETACH_SET;
    }

    /* PS DETACH����ϱ� */
    if (NAS_MSCC_PIF_SRVDOMAIN_PS == pstDetachCnf->enCnDomainId)
    {
        /*���PS DETACH��־*/
        pstSysCfgCtx->usOperType &= ~TAF_MMA_SYS_CFG_PS_DETACH_SET;
    }

    if (TAF_MMA_SYS_CFG_NONE_SET != (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_DETACH_REQ_REQUIRED))
    {
        /* ��Detach��Ϣ��־ʱ�����ȴ�  */
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_DETACH_CNF);

    /* ��Ҫ��ײ㷢��SYS CFG���� */
    if (TAF_MMA_SYS_CFG_NONE_SET != (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_SET_REQ_REQUIRED))
    {
        /* ��Ҫ��ײ㷢��SYS CFG���󣬺�������Ҫ����ATTACH�ĳ�������Ҫ����mode change */
        if (TAF_MMA_SYS_CFG_NONE_SET == (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED))
        {
            MMA_ChangeSrv2Class(pstSysCfgCtx->stSysCfgPara.enSrvDomain, &ucClassType);

            TAF_MMA_SndMsccModeChangeReq((NAS_MSCC_PIF_MS_MODE_ENUM_UINT32)ucClassType);
        }

        ucOnlyRoamParaChanged    = TAF_MMA_IsOnlyRoamParaChangeFlgFromSysCfgOperType_SysCfg(pstSysCfgCtx->usOperType);
        ucIsNeedAttachPs         = TAF_MMA_IsNeedAttachPsFlgFromSysCfgOperType_SysCfg(pstSysCfgCtx->usOperType);
        TAF_MMA_SndMsccSysCfgReq(&(pstSysCfgCtx->stSysCfgPara), ucOnlyRoamParaChanged, ucIsNeedAttachPs);

        /* ����������ʱ�� */
        TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_SYSCFG_CNF, TI_TAF_MMA_WAIT_MSCC_SYSCFG_CNF_LEN);

        /* Ǩ��TAF_MMA_SYS_CFG_STA_WAIT_DETACH_CNF״̬ */
        TAF_MMA_FSM_SetCurrState(TAF_MMA_SYS_CFG_STA_WAIT_SYS_CFG_CNF);
    }
    /* ����Ҫ��ײ㷢��SYS CFG������ATTACH��־���� */
    else if (TAF_MMA_SYS_CFG_NONE_SET != (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED))
    {
        MMA_ChangeSrv2Class(pstSysCfgCtx->stSysCfgPara.enSrvDomain, &ucClassType);

        TAF_MMA_SndMsccModeChangeReq((NAS_MSCC_PIF_MS_MODE_ENUM_UINT32)ucClassType);

        enAttachType = TAF_MMA_GetAttachTypeFromSysCfgOperType_SysCfg(pstSysCfgCtx->usOperType);

        if (VOS_OK == TAF_MMA_ConvertAttachTypeToMscc(enAttachType, &enMsccAttachType))
        {
            TAF_MMA_NotifyCsServiceChange_SysCfg(pstSysCfgCtx->usOperType);

            ucOpID = TAF_MMA_GetAttachOpId();

            /* Modified by b00269685 for L-C��������Ŀ, 2014-2-17, begin */
            (VOS_VOID)TAF_MMA_SndMsccAttachReq(ucOpID, enMsccAttachType, TAF_MMA_ATTACH_REASON_INITIAL);
            /* Modified by b00269685 for L-C��������Ŀ, 2014-2-17, end */
        }

        if (VOS_TRUE == ulSndAppRsltFlg)
        {
            TAF_MMA_SndSysCfgSetCnf(pstCtrl, TAF_ERR_NO_ERROR);
        }

        /* ����״̬���˳������Ϣ */
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_SYS_CFG_SUCC, VOS_FALSE);

        /* �˳�״̬�� */
        TAF_MMA_FSM_QuitSubFsm();

    }
    else
    {
        MMA_ChangeSrv2Class(pstSysCfgCtx->stSysCfgPara.enSrvDomain, &ucClassType);

        TAF_MMA_SndMsccModeChangeReq((NAS_MSCC_PIF_MS_MODE_ENUM_UINT32)ucClassType);

        if (VOS_TRUE == ulSndAppRsltFlg)
        {
            TAF_MMA_SndSysCfgSetCnf(pstCtrl, TAF_ERR_NO_ERROR);
        }

        TAF_MMA_NotifyCsServiceChange_SysCfg(pstSysCfgCtx->usOperType);

        /* ����״̬���˳������Ϣ */
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_SYS_CFG_SUCC, VOS_FALSE);

        /* �˳�״̬�� */
        TAF_MMA_FSM_QuitSubFsm();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvDetachCnf_SysCfg_WaitDetachCnf
 ��������  : ��TAF_MMA_SYS_CFG_STA_WAIT_DETACH_CNF״̬�յ�ID_MSCC_MMA_DETACH_CNF�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvDetachCnf_SysCfg_WaitDetachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_DETACH_CNF_STRU           *pstDetachCnf;
    VOS_UINT32                          ulEntryMsgId;
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;
    TAF_MMA_CTRL_STRU                   stCtrl;

    /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg     = TAF_MMA_GetCurrFsmMsgAddr();

    ulEntryMsgId    = TAF_MMA_GetCurrFsmEntryMsgId_SysCfg();

    pstDetachCnf    = (MSCC_MMA_DETACH_CNF_STRU*)pstMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_MMA_CTRL_STRU));

    /* �����ϢΪID_TAF_MMA_DETACH_REQ�Ĵ��� */
    if (ID_TAF_MMA_DETACH_REQ == ulEntryMsgId)
    {
        stCtrl = ((TAF_MMA_DETACH_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer))->stCtrl;

        TAF_MMA_ProcDetachCnfTriggeredByDetachReq_SysCfg(pstDetachCnf, &stCtrl);
    }
    else if (ID_TAF_MMA_SYS_CFG_SET_REQ == ulEntryMsgId)
    {
        stCtrl = ((TAF_MMA_SYS_CFG_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer))->stCtrl;

        /* ��Ҫ��APP���ؽ�� */
        TAF_MMA_ProcDetachCnfTriggeredBySysCfgReq_SysCfg(pstDetachCnf, VOS_TRUE, &stCtrl);
    }
    else if (MMA_MMA_INTER_SYS_CFG_SET_REQ == ulEntryMsgId)
    {
        /* ����Ҫ��APP���ؽ�� */
        TAF_MMA_ProcDetachCnfTriggeredBySysCfgReq_SysCfg(pstDetachCnf, VOS_FALSE, &stCtrl);
    }
    else
    {
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiWaitDetachCnfExpired_SysCfg_WaitDetachCnf
 ��������  : �ȴ�MsccDetachCnf�ж�ʱ����ʱ��Ϣ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��13��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitDetachCnfExpired_SysCfg_WaitDetachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulEntryMsgId;
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;
    TAF_MMA_CTRL_STRU                   stCtrl;
    MSCC_MMA_DETACH_CNF_STRU            stDetachCnf;
    TAF_MMA_FSM_SYS_CFG_CTX_STRU       *pstSysCfgCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulSndAppRsltFlg;

    /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg     = TAF_MMA_GetCurrFsmMsgAddr();

    ulEntryMsgId    = TAF_MMA_GetCurrFsmEntryMsgId_SysCfg();

    /* ��ȡ��ǰ״̬���������� */
    pstSysCfgCtx    = &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx);

    ulSndAppRsltFlg = VOS_FALSE;

    PS_MEM_SET(&stDetachCnf, 0, sizeof(MSCC_MMA_DETACH_CNF_STRU));

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_MMA_CTRL_STRU));

    if (ID_TAF_MMA_SYS_CFG_SET_REQ == ulEntryMsgId)
    {
        ulSndAppRsltFlg = VOS_TRUE;

        stCtrl = ((TAF_MMA_SYS_CFG_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer))->stCtrl;
    }

    if ((ID_TAF_MMA_SYS_CFG_SET_REQ == ulEntryMsgId)
     || (MMA_MMA_INTER_SYS_CFG_SET_REQ == ulEntryMsgId))
    {
        /* δ�յ�detach cnf��Ϣ����Ϊdetach�ɹ�������ٵ�detach cnf��Ϣ */
        if ((TAF_MMA_SYS_CFG_CS_DETACH_SET == (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_CS_DETACH_SET))
         && (TAF_MMA_SYS_CFG_PS_DETACH_SET == (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_PS_DETACH_SET)))
        {
            stDetachCnf.enCnDomainId    = NAS_MSCC_PIF_SRVDOMAIN_CS;
            stDetachCnf.enServiceStatus = NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE;

            /* ��Ҫ��APP���ؽ�� */
            TAF_MMA_ProcDetachCnfTriggeredBySysCfgReq_SysCfg(&stDetachCnf, ulSndAppRsltFlg, &stCtrl);

            stDetachCnf.enCnDomainId    = NAS_MSCC_PIF_SRVDOMAIN_PS;
            stDetachCnf.enServiceStatus = NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE;

            /* ��Ҫ��APP���ؽ�� */
            TAF_MMA_ProcDetachCnfTriggeredBySysCfgReq_SysCfg(&stDetachCnf, ulSndAppRsltFlg, &stCtrl);
        }
        else if(TAF_MMA_SYS_CFG_CS_DETACH_SET == (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_CS_DETACH_SET))
        {
            stDetachCnf.enCnDomainId    = NAS_MSCC_PIF_SRVDOMAIN_CS;
            stDetachCnf.enServiceStatus = NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE;

            /* ��Ҫ��APP���ؽ�� */
            TAF_MMA_ProcDetachCnfTriggeredBySysCfgReq_SysCfg(&stDetachCnf, ulSndAppRsltFlg, &stCtrl);
        }
        else if (TAF_MMA_SYS_CFG_PS_DETACH_SET == (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_PS_DETACH_SET))
        {
            stDetachCnf.enCnDomainId    = NAS_MSCC_PIF_SRVDOMAIN_PS;
            stDetachCnf.enServiceStatus = NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE;

            /* ��Ҫ��APP���ؽ�� */
            TAF_MMA_ProcDetachCnfTriggeredBySysCfgReq_SysCfg(&stDetachCnf, ulSndAppRsltFlg, &stCtrl);
        }
        else
        {
        }
    }
    else if (ID_TAF_MMA_DETACH_REQ == ulEntryMsgId)
    {
        /* ֱ�Ӹ�APP�ظ�ʧ�� */
        TAF_MMA_SndDetachCnf(&(((TAF_MMA_DETACH_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer))->stCtrl),
                             TAF_MMA_APP_OPER_RESULT_FAILURE,
                             TAF_ERR_TIME_OUT);

        /* ����״̬���˳������Ϣ */
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_DETACH_FAIL, VOS_FALSE);

        /* �˳�״̬�� */
        TAF_MMA_FSM_QuitSubFsm();
    }
    else
    {
    }


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvAbortInd_SysCfg_WaitDetachCnf
 ��������  : �ȴ�MsccDetachCnf���յ��ڲ�Abort��Ϣ
 �������  : ulEventType
            *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��13��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAbortInd_SysCfg_WaitDetachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgId;

    /* ֹͣ������ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_DETACH_CNF);

    /* ��ȡ������Ϣ */
    pstEntryMsg                         = TAF_MMA_GetCurrFsmMsgAddr();
    ulMsgId                             = TAF_MMA_GetCurrFsmEntryMsgId_SysCfg();

    /* ���ݻ�����Ϣ�����ϱ���� */
    if (ID_TAF_MMA_SYS_CFG_SET_REQ == ulMsgId)
    {
        TAF_MMA_SndSysCfgSetCnf(&(((TAF_MMA_SYS_CFG_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer))->stCtrl),
                                TAF_ERR_ERROR);

        /* ����״̬���˳������Ϣ */
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_SYS_CFG_FAIL, VOS_FALSE);
    }
    else if (ID_TAF_MMA_DETACH_REQ == ulMsgId)
    {
        TAF_MMA_SndDetachCnf(&(((TAF_MMA_DETACH_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer))->stCtrl),
                             TAF_MMA_APP_OPER_RESULT_FAILURE,
                             TAF_ERR_ERROR);

        /* ����״̬���˳������Ϣ */
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_DETACH_FAIL, VOS_FALSE);
    }
    else
    {
        /* ����״̬���˳������Ϣ */
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_BUTT, VOS_FALSE);
    }

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvAttachCnf_SysCfg_WaitAttachCnf
 ��������  : ��TAF_MMA_SYS_CFG_STA_WAIT_ATTACH_CNF״̬�յ�ID_MSCC_MMA_ATTACH_CNF�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��14��
    ��    ��   : h00313353
    �޸�����   : SysCfg�ع�
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAttachCnf_SysCfg_WaitAttachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_ATTACH_CNF_STRU                               *pstAttachCnf    = VOS_NULL_PTR;
    TAF_MMA_FSM_SYS_CFG_CTX_STRU                           *pstSysCfgCtx    = VOS_NULL_PTR;
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32                     enAttachRslt;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enCsSrvStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enPsSrvStatus;
    VOS_UINT16                                              usPhoneError;

    /* ��ʼ�� */
    pstAttachCnf    = (MSCC_MMA_ATTACH_CNF_STRU *)pstMsg;
    pstSysCfgCtx    = &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx);
    enPsSrvStatus   = TAF_SDC_GetPsServiceStatus();
    enCsSrvStatus   = TAF_SDC_GetCsServiceStatus();
    enAttachRslt    = TAF_MMA_APP_OPER_RESULT_SUCCESS;
    usPhoneError    = TAF_ERR_NO_ERROR;

    /* ���OpId�Ƿ�ƥ�� */
    if (pstSysCfgCtx->ucAttachOpId != (VOS_UINT8)pstAttachCnf->ulOpID)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvAttachCnf_SysCfg_WaitAttachCnf():Wrong OpId!");

        return VOS_TRUE;
    }

    /* ����Service Domain�����־�����·�����״̬ */
    switch (pstAttachCnf->enCnDomainId)
    {
        case NAS_MSCC_PIF_SRVDOMAIN_CS:
            /* ���CS ATTACH��־ */
            pstSysCfgCtx->usOperType &= ~TAF_MMA_SYS_CFG_CS_ATTACH_SET;

            /* �绹��δ�յ�����Ϣ�������ȴ� */
            if (TAF_MMA_SYS_CFG_NONE_SET != (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED))
            {
                return VOS_TRUE;
            }

            /* ��ȡ��ǰ�ķ�����״̬ */
            if (NAS_MSCC_PIF_SERVICE_STATUS_NO_CHANGE != pstAttachCnf->enServiceStatus)
            {
                enCsSrvStatus = (TAF_SDC_SERVICE_STATUS_ENUM_UINT8)pstAttachCnf->enServiceStatus;
            }

            break;

        case NAS_MSCC_PIF_SRVDOMAIN_PS:
            /* ���PS ATTACH��־ */
            pstSysCfgCtx->usOperType &= ~TAF_MMA_SYS_CFG_PS_ATTACH_SET;

            /* �绹��δ�յ�����Ϣ�������ȴ� */
            if (TAF_MMA_SYS_CFG_NONE_SET != (pstSysCfgCtx->usOperType & TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED))
            {
                return VOS_TRUE;
            }

            /* ��ȡ��ǰ�ķ�����״̬ */
            if (NAS_MSCC_PIF_SERVICE_STATUS_NO_CHANGE != pstAttachCnf->enServiceStatus)
            {
                enPsSrvStatus = (TAF_SDC_SERVICE_STATUS_ENUM_UINT8)pstAttachCnf->enServiceStatus;
            }

            break;

        case NAS_MSCC_PIF_SRVDOMAIN_CS_PS:
            /* ���PS_CS ATTACH��־ */
            pstSysCfgCtx->usOperType &= ~TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED;

            /* ��ȡ��ǰ�ķ�����״̬ */
            if (NAS_MSCC_PIF_SERVICE_STATUS_NO_CHANGE != pstAttachCnf->enServiceStatus)
            {
                enPsSrvStatus = (TAF_SDC_SERVICE_STATUS_ENUM_UINT8)pstAttachCnf->enServiceStatus;
                enCsSrvStatus = (TAF_SDC_SERVICE_STATUS_ENUM_UINT8)pstAttachCnf->enServiceStatus;
            }

            break;

        default:
            /* ����󣬲����� */
            return VOS_TRUE;
    }

    /* ֹͣ������ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_ATTACH_CNF);

    /* ���������Attach����,�ж�Attach��� */
    TAF_MMA_GetAttachRsltFromServiceStatus_SysCfg(enCsSrvStatus, enPsSrvStatus, &enAttachRslt, &usPhoneError);

    /* ������Ϣ���������ϱ���� */
    TAF_MMA_SndAttachCnf(&(((TAF_MMA_ATTACH_REQ_STRU *)(TAF_MMA_GetCurrFsmMsgAddr()->aucEntryMsgBuffer))->stCtrl),
                         enAttachRslt,
                         usPhoneError);

    /* ����״̬���˳������Ϣ */
    if (TAF_MMA_APP_OPER_RESULT_SUCCESS == enAttachRslt)
    {
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_ATTACH_SUCCESS, VOS_FALSE);
    }
    else
    {
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_ATTACH_FAIL, VOS_FALSE);
    }

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiWaitAttachCnfExpired_SysCfg_WaitAttachCnf
 ��������  : �ȴ�AttachCnf��ʱ��Ϣ�Ĵ���
 �������  : VOS_UINT32 ulEventType
             struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��14��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitAttachCnfExpired_SysCfg_WaitAttachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���ݻ�����Ϣ�����ϱ���� */
    TAF_MMA_SndAttachCnf(&(((TAF_MMA_ATTACH_REQ_STRU *)(TAF_MMA_GetCurrFsmMsgAddr()->aucEntryMsgBuffer))->stCtrl),
                          TAF_MMA_APP_OPER_RESULT_FAILURE,
                          TAF_ERR_TIME_OUT);

    /* ����״̬���˳������Ϣ */
    TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_ATTACH_FAIL, VOS_FALSE);

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvAbortInd_SysCfg_WaitAttachCnf
 ��������  : �ȴ�AttachCnfʱ�յ�Abort��Ϣ�Ĵ���
 �������  : VOS_UINT32 ulEventType
             struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��14��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAbortInd_SysCfg_WaitAttachCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_ATTACH_CNF);

    /* ���ݻ�����Ϣ�����ϱ���� */
    TAF_MMA_SndAttachCnf(&(((TAF_MMA_ATTACH_REQ_STRU *)(TAF_MMA_GetCurrFsmMsgAddr()->aucEntryMsgBuffer))->stCtrl),
                          TAF_MMA_APP_OPER_RESULT_FAILURE,
                          TAF_ERR_ERROR);

    /* ����״̬���˳������Ϣ */
    TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_ATTACH_FAIL, VOS_FALSE);

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetRatListBasedOnSysmode_SysCfg
 ��������  : ����sysmode����ȡrat���б�
 �������  : TAF_SDC_SYS_MODE_ENUM_UINT8         enstSysCfgPara
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��12��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_GetRatListBasedOnSysmode_SysCfg(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode,
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
)
{
    switch (enSysMode)
    {
        case TAF_SDC_SYS_MODE_GSM:
            pstRatOrder->ucRatOrderNum  = 1;
            pstRatOrder->aenRatOrder[0] = TAF_MMA_RAT_GSM;
            break;

        case TAF_SDC_SYS_MODE_WCDMA:
            pstRatOrder->ucRatOrderNum  = 1;
            pstRatOrder->aenRatOrder[0] = TAF_MMA_RAT_WCDMA;
            break;

        case TAF_SDC_SYS_MODE_LTE:
            pstRatOrder->ucRatOrderNum  = 1;
            pstRatOrder->aenRatOrder[0] = TAF_MMA_RAT_LTE;
            break;

        case TAF_SDC_SYS_MODE_CDMA_1X:
            pstRatOrder->ucRatOrderNum  = 1;
            pstRatOrder->aenRatOrder[0] = TAF_MMA_RAT_1X;
            break;

        case TAF_SDC_SYS_MODE_EVDO:
            pstRatOrder->ucRatOrderNum  = 1;
            pstRatOrder->aenRatOrder[0] = TAF_MMA_RAT_HRPD;
            break;

        case TAF_SDC_SYS_MODE_HYBRID:
            pstRatOrder->ucRatOrderNum  = 2;
            pstRatOrder->aenRatOrder[0] = TAF_MMA_RAT_1X;
            pstRatOrder->aenRatOrder[1] = TAF_MMA_RAT_HRPD;
            break;

        case TAF_SDC_SYS_MODE_SVLTE:
            pstRatOrder->ucRatOrderNum  = 2;
            pstRatOrder->aenRatOrder[0] = TAF_MMA_RAT_1X;
            pstRatOrder->aenRatOrder[1] = TAF_MMA_RAT_LTE;
            break;

        default :
            pstRatOrder->ucRatOrderNum  = 0;
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsConfigCMode_SysCfg
 ��������  : �յ�SYS CNF�ɹ��Ĵ���
 �������  : TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��28��
    ��    ��   : h00313353
    �޸�����   : 1X ��������

*****************************************************************************/
VOS_UINT8 TAF_MMA_IsConfigCMode_SysCfg(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          i;

    for (i = 0; i < TAF_SDC_MIN(TAF_PH_MAX_GUL_RAT_NUM, pstRatOrder->ucRatOrderNum); i++)
    {
        if ((TAF_MMA_RAT_1X   == pstRatOrder->aenRatOrder[i])
         || (TAF_MMA_RAT_HRPD == pstRatOrder->aenRatOrder[i]))
        {
            TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_IsConfigCMode_SysCfg: TRUE!");

            return VOS_TRUE;
        }
    }
#endif
    TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_IsConfigCMode_SysCfg: FLASE!");

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcSysCfgCnfSucc_SysCfg
 ��������  : �յ�SYS CNF�ɹ��Ĵ���
 �������  : TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��20��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ProcSysCfgCnfSucc_SysCfg(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
)
{
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                    *pstLastSyscfgSet = VOS_NULL_PTR;
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode;
    TAF_MMA_RAT_ORDER_STRU                                  stRatOrder;
    VOS_UINT32                                              ulSysModeSupportFlg;
    VOS_UINT8                                               i;

    enSysMode        = TAF_SDC_GetSysMode();
    pstLastSyscfgSet = TAF_MMA_GetLastSyscfgSetAddr();

    TAF_MMA_SndTafSysCfgInfoInd(&(pstLastSyscfgSet->stRatPrioList), &(pstSysCfgPara->stRatOrder));

    if (ID_TAF_MMA_SYS_CFG_SET_REQ == TAF_MMA_GetCurrFsmEntryMsgId_SysCfg())
    {
         /* ���µ�ǰ���óɹ��Ľ��뼼�� */
        TAF_MMA_UpdateSysCfgPara(pstSysCfgPara);
    }
    else
    {
        /* ֻ����ȫ�ֱ��� */
        pstLastSyscfgSet->stRatPrioList = pstSysCfgPara->stRatOrder;
    }

    PS_MEM_SET(&stRatOrder, 0x00, sizeof(stRatOrder));
    ulSysModeSupportFlg = VOS_FALSE;

    TAF_MMA_GetRatListBasedOnSysmode_SysCfg(enSysMode, &stRatOrder);

    for (i = 0; i < TAF_SDC_MIN(TAF_PH_MAX_GUL_RAT_NUM, stRatOrder.ucRatOrderNum); i++)
    {
        if (VOS_TRUE == MN_MMA_IsSpecRatSupported(stRatOrder.aenRatOrder[i]) )
        {
            ulSysModeSupportFlg = VOS_TRUE;
            break;
        }
    }

    /* ��ǰ�Ľ��뼼�����Ƿ����µĽ��뼼���б���, ����RAT�б���ʱ���ϱ� Mode:0,0*/
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, begin */
    if ((VOS_FALSE == ulSysModeSupportFlg)
     && (TAF_SDC_SYS_MODE_BUTT != enSysMode))
    {
        /* CMDA��򿪵�����£�����״̬����ʱ�򣬴���SYSMODE */
#if (FEATURE_OFF == FEATURE_UE_MODE_CDMA)
        TAF_SDC_SetSysMode(TAF_SDC_SYS_MODE_BUTT);
        TAF_SDC_SetSysSubMode(TAF_SDC_SYS_SUBMODE_NONE);

        Sta_ModeChangeEventReport(TAF_PH_INFO_NONE_RAT, TAF_SYS_SUBMODE_NONE);
#endif

        /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* ��MTCģ���ϱ���ǰ����ģʽ */
        /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, begin */
        TAF_MMA_SndMtcRatModeInd(TAF_SDC_SYS_MODE_BUTT, NAS_UTRANCTRL_GetCurrUtranMode());
        /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, end */
        TAF_MMA_SndMtcRatCfgInd(&(pstSysCfgPara->stRatOrder));
#endif
        /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, end */

    }

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvSysCfgCnf_SysCfg_WaitSysCfgCnf
 ��������  : ��TAF_MMA_SYS_CFG_STA_WAIT_SYS_CFG_CNF״̬�յ�ID_MSCC_MMA_SYS_CFG_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��3��
    ��    ��   : w00176964
    �޸�����   : DTS2015061601845:SYSCFG����ʧ��ʱ,������Ӧ�Ĳ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvSysCfgCnf_SysCfg_WaitSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_ERROR_CODE_ENUM_UINT32                              enErrorCode;
    NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32                    enMsccAttachType;
    MSCC_MMA_SYS_CFG_SET_CNF_STRU                          *pstSysCfgCnf;
    TAF_MMA_FSM_SYS_CFG_CTX_STRU                           *pstSysCfgCtx = VOS_NULL_PTR;
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg    = VOS_NULL_PTR;
    VOS_UINT32                                              ulEntryMsgId;
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8                          enAttachType;
    TAF_MMA_CTRL_STRU                                       stCtrl;
    TAF_PH_MS_CLASS_TYPE                                    ucClassType;
    TAF_MMA_SYS_CFG_OPER_TYPE                               usOperType;
    VOS_UINT8                                               ucIsOrigCfgCMode;
    VOS_UINT8                                               ucIsNeedChkLock;        /* �Ƿ���Ҫ���½���������������־ */

    ucIsNeedChkLock                                         = VOS_FALSE;
    ucIsOrigCfgCMode                                        = VOS_FALSE;

    /* ��ȡ��ǰ״̬���������� */
    pstSysCfgCtx    = &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx);

    /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg      = TAF_MMA_GetCurrFsmMsgAddr();

    ulEntryMsgId     = TAF_MMA_GetCurrFsmEntryMsgId_SysCfg();

    pstSysCfgCnf     = (MSCC_MMA_SYS_CFG_SET_CNF_STRU*)pstMsg;

    /* ֹͣ������ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_SYSCFG_CNF);

    ucClassType  = TAF_PH_MS_CLASS_NULL;
    enAttachType = TAF_MMA_ATTACH_TYPE_NULL;
    usOperType   = TAF_MMA_SYS_CFG_RAT_NONE_SET;

    /* ��Ҫ��ײ㷢��ATTACH���� */
    if (VOS_TRUE == TAF_MMA_IsNeedAttachAfterSyscfgSet_SysCfg(pstSysCfgCnf->enRst, &enAttachType, &ucClassType, &usOperType))
    {
        TAF_MMA_SndMsccModeChangeReq((NAS_MSCC_PIF_MS_MODE_ENUM_UINT32)ucClassType);

        if (VOS_OK == TAF_MMA_ConvertAttachTypeToMscc(enAttachType, &enMsccAttachType))
        {
            TAF_MMA_NotifyCsServiceChange_SysCfg(usOperType);

            /* Modified by b00269685 for L-C��������Ŀ, 2014-2-17, begin */
            (VOS_VOID)TAF_MMA_SndMsccAttachReq(TAF_MMA_GetAttachOpId(), enMsccAttachType, TAF_MMA_ATTACH_REASON_INITIAL);
            /* Modified by b00269685 for L-C��������Ŀ, 2014-2-17, end */
        }
    }

    if (NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS == pstSysCfgCnf->enRst)
    {
        enErrorCode = TAF_ERR_NO_ERROR;

        ucIsOrigCfgCMode = TAF_MMA_IsConfigCMode_SysCfg(&(TAF_MMA_GetLastSyscfgSetAddr()->stRatPrioList));

        if (ucIsOrigCfgCMode != TAF_MMA_IsConfigCMode_SysCfg(&(pstSysCfgCtx->stSysCfgPara.stRatOrder)))
        {
            ucIsNeedChkLock = VOS_TRUE;

            TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvSysCfgCnf_SysCfg_WaitSysCfgCnf: Need Chk Lock!");
        }

        TAF_MMA_ProcSysCfgCnfSucc_SysCfg(&(pstSysCfgCtx->stSysCfgPara));
    }
    else if (NAS_MSCC_PIF_SYS_CFG_SET_FAILURE_CS_SERV_EXIST == pstSysCfgCnf->enRst)
    {
        enErrorCode = TAF_ERR_SYSCFG_CS_SERV_EXIST;

        /* �����4F36refresh������SYSCFGʧ�ܣ���Ҫ����TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING��ʱ�� */
        if (MMA_MMA_INTER_SYS_CFG_SET_REQ == ulEntryMsgId)
        {
            TAF_MMA_ProcInterSysCfgCnfFail_SysCfg();
        }
    }
    else
    {
        enErrorCode = TAF_ERR_ERROR;

        /* �����4F36refresh������SYSCFGʧ�ܣ���Ҫ����TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING��ʱ�� */
        if (MMA_MMA_INTER_SYS_CFG_SET_REQ == ulEntryMsgId)
        {
            TAF_MMA_ProcInterSysCfgCnfFail_SysCfg();
        }
    }

    if (ID_TAF_MMA_SYS_CFG_SET_REQ == ulEntryMsgId)
    {
        stCtrl = ((TAF_MMA_SYS_CFG_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer))->stCtrl;

        /* Modified by w00167002 for L-C��������Ŀ, 2014-2-14, begin */
        TAF_MMA_SndSysCfgSetCnf(&stCtrl, enErrorCode);
        /* Modified by w00167002 for L-C��������Ŀ, 2014-2-14, end */
    }

    /* ����״̬���˳������Ϣ */
    if (TAF_ERR_NO_ERROR == enErrorCode)
    {
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_SYS_CFG_SUCC, ucIsNeedChkLock);
    }
    else
    {
        TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_SYS_CFG_FAIL, ucIsNeedChkLock);
    }

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvTiWaitSysCfgCnfExpired_SysCfg_WaitSysCfgCnf
 ��������  : �ȴ�SysCfgCnf��ʱ��Ϣ�Ĵ���
 �������  : VOS_UINT32 ulEventType
             struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��14��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvTiWaitSysCfgCnfExpired_SysCfg_WaitSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgId;

    /* ��ȡ������Ϣ */
    pstEntryMsg                         = TAF_MMA_GetCurrFsmMsgAddr();
    ulMsgId                             = TAF_MMA_GetCurrFsmEntryMsgId_SysCfg();

    /* ���ݻ�����Ϣ�����ϱ���� */
    if (ID_TAF_MMA_SYS_CFG_SET_REQ == ulMsgId)
    {
        TAF_MMA_SndSysCfgSetCnf(&(((TAF_MMA_SYS_CFG_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer))->stCtrl),
                                TAF_ERR_TIME_OUT);
    }

    /* ����״̬���˳������Ϣ */
    TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_SYS_CFG_FAIL, VOS_FALSE);

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_RcvAbortInd_SysCfg_WaitSysCfgCnf
 ��������  : �ȴ�SysCfgʱ�յ�Abort��Ϣ�Ĵ���
 �������  : VOS_UINT32 ulEventType
             struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��14��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvAbortInd_SysCfg_WaitSysCfgCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgId;

    /* ��ȡ������Ϣ */
    pstEntryMsg                         = TAF_MMA_GetCurrFsmMsgAddr();
    ulMsgId                             = TAF_MMA_GetCurrFsmEntryMsgId_SysCfg();

    /* ���ݻ�����Ϣ�����ϱ���� */
    if (ID_TAF_MMA_SYS_CFG_SET_REQ == ulMsgId)
    {
        TAF_MMA_SndSysCfgSetCnf(&(((TAF_MMA_SYS_CFG_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer))->stCtrl),
                                TAF_ERR_ERROR);
    }

    /* ֹͣ������ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_SYSCFG_CNF);

    /* ����״̬���˳������Ϣ */
    TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_SYS_CFG_FAIL, VOS_FALSE);

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcInterSysCfgCnfFail_SysCfg_WaitSysCfgCnf
 ��������  : �ڲ�������SYSCFG����ʧ�ܵĴ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��9��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ProcInterSysCfgCnfFail_SysCfg(VOS_VOID)
{
    /* TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING��ʱ���������У����� */
    if (MMA_TIMER_RUN == TAF_MMA_GetTiTryingPeriodRatBalancingStatus())
    {
        return;
    }

    /* �����4F36refresh������SYSCFGʧ�ܣ���Ҫ����TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING��ʱ�� */
    TAF_MMA_StartTimer(TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING, TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING_LEN);

    TAF_MMA_SetTiTryingPeriodRatBalancingStatus(MMA_TIMER_RUN);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetOperTypeFromGULToCL
 ��������  : ��ȡRAT���ô�GUL��CL��������
 �������  : enLastGULRatType -- �ϴ�GUL RAT����
             enCurrCLRatType  -- ��ǰCL RAT����

 �������  : ��
 �� �� ֵ  : TAF_MMA_MODE_CHANGE_OPER_TYPE_STRU -- ��������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU *TAF_MMA_GetOperTypeFromGULToCL(
    TAF_MMA_GUL_RAT_SUBMODE_TYPE_ENUM_UINT8     enLastGULSubmodeType,
    TAF_MMA_CL_RAT_SUBMODE_TYPE_ENUM_UINT8      enCurrCLSubmodeType
)
{
    return &(g_astOperTypeFromGULToCLTab[enLastGULSubmodeType][enCurrCLSubmodeType]);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetOperTypeFromCLToGUL
 ��������  : ��ȡRAT���ô�CL��GUL��������
 �������  : enLastCLRatType  -- CL RAT����
             enCurrGULRatType -- GUL RAT����

 �������  : ��
 �� �� ֵ  : TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU -- ��������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU *TAF_MMA_GetOperTypeFromCLToGUL(
    TAF_MMA_CL_RAT_SUBMODE_TYPE_ENUM_UINT8      enLastCLSubModeType,
    TAF_MMA_GUL_RAT_SUBMODE_TYPE_ENUM_UINT8     enCurrGULSubModeType
)
{
    return &(g_astOperTypeFromCLToGULTab[enLastCLSubModeType][enCurrGULSubModeType]);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetOperTypeFromCLToCL
 ��������  : ��ȡRAT���ô�CL��GUL��������
 �������  : enLastCLRatType -- �ϴ�CL RAT����
             enCurrCLRatType -- ��ǰCL RAT����

 �������  : ��
 �� �� ֵ  : TAF_MMA_MODE_CHANGE_OPER_TYPE_STRU -- ��������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU *TAF_MMA_GetOperTypeFromCLToCL(
    TAF_MMA_CL_RAT_SUBMODE_TYPE_ENUM_UINT8     enLastCLSubModeType,
    TAF_MMA_CL_RAT_SUBMODE_TYPE_ENUM_UINT8     enCurrCLSubModeType
)
{
    return &(g_astOperTypeFromCLtoCLTab[enLastCLSubModeType][enCurrCLSubModeType]);
}

/* �Ƶ�ǰ������TafMmaComFunc.c�ļ� */

/*****************************************************************************
 �� �� ��  : TAF_MMA_CovertGULRatOrderToGULSubMode
 ��������  : ת��GUL RAT order��GUL��ģʽ
 �������  : pstRatOrder -- RAT˳��

 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- RAT�����仯
             VOS_FALSE -- RATδ�����仯
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_GUL_RAT_SUBMODE_TYPE_ENUM_UINT8 TAF_MMA_CovertGULRatOrderToGULSubMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
)
{
    /* ��ǰRAT����Ϊ��������һ����GUL����  */
    if (TAF_MMA_THREE_RAT_NUM == pstRatOrder->ucRatOrderNum)
    {
        return TAF_MMA_GUL_RAT_SUBMODE_GUL;
    }

    if (TAF_MMA_TWO_RAT_NUM == pstRatOrder->ucRatOrderNum)
    {
        if (TAF_MMA_RAT_GSM == pstRatOrder->aenRatOrder[0])
        {
            if (TAF_MMA_RAT_WCDMA == pstRatOrder->aenRatOrder[1])
            {
                return TAF_MMA_GUL_RAT_SUBMODE_GU;
            }

            return TAF_MMA_GUL_RAT_SUBMODE_GL;
        }

        if (TAF_MMA_RAT_WCDMA == pstRatOrder->aenRatOrder[0])
        {
            if (TAF_MMA_RAT_GSM == pstRatOrder->aenRatOrder[1])
            {
                return TAF_MMA_GUL_RAT_SUBMODE_GU;
            }

            return TAF_MMA_GUL_RAT_SUBMODE_UL;
        }

        if (TAF_MMA_RAT_GSM == pstRatOrder->aenRatOrder[1])
        {
            return TAF_MMA_GUL_RAT_SUBMODE_GL;
        }

        return TAF_MMA_GUL_RAT_SUBMODE_UL;
    }

    if (TAF_MMA_RAT_GSM == pstRatOrder->aenRatOrder[0])
    {
        return TAF_MMA_GUL_RAT_SUBMODE_G;
    }

    if (TAF_MMA_RAT_WCDMA == pstRatOrder->aenRatOrder[0])
    {
        return TAF_MMA_GUL_RAT_SUBMODE_U;
    }

    return TAF_MMA_GUL_RAT_SUBMODE_L;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_MMA_CovertCLRatOrderToCLSubMode
 ��������  : ת��CL RAT order��CL��ģʽ
 �������  : pstRatOrder -- RAT˳��

 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- RAT�����仯
             VOS_FALSE -- RATδ�����仯
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_CL_RAT_SUBMODE_TYPE_ENUM_UINT8 TAF_MMA_CovertCLRatOrderToCLSubMode(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder
)
{
    /* ��ǰRAT����Ϊ��������һ����CL����  */
    if (TAF_MMA_THREE_RAT_NUM == pstRatOrder->ucRatOrderNum)
    {
        return TAF_MMA_CL_RAT_SUBMODE_CL;
    }

    if (TAF_MMA_TWO_RAT_NUM == pstRatOrder->ucRatOrderNum)
    {
        if (TAF_MMA_RAT_1X == pstRatOrder->aenRatOrder[0])
        {
            if (TAF_MMA_RAT_HRPD == pstRatOrder->aenRatOrder[1])
            {
                return TAF_MMA_CL_RAT_SUBMODE_C;
            }

            return TAF_MMA_CL_RAT_SUBMODE_1XL;
        }

        if (TAF_MMA_RAT_HRPD == pstRatOrder->aenRatOrder[0])
        {
            if (TAF_MMA_RAT_1X == pstRatOrder->aenRatOrder[1])
            {
                return TAF_MMA_CL_RAT_SUBMODE_C;
            }

            return TAF_MMA_CL_RAT_SUBMODE_HRPDL;
        }

        if (TAF_MMA_RAT_1X == pstRatOrder->aenRatOrder[1])
        {
            return TAF_MMA_CL_RAT_SUBMODE_1XL;
        }

        return TAF_MMA_CL_RAT_SUBMODE_HRPDL;
    }

    if (TAF_MMA_RAT_1X == pstRatOrder->aenRatOrder[0])
    {
        return TAF_MMA_CL_RAT_SUBMODE_1X;
    }

    if (TAF_MMA_RAT_HRPD == pstRatOrder->aenRatOrder[0])
    {
        return TAF_MMA_CL_RAT_SUBMODE_HRPD;
    }

    return TAF_MMA_CL_RAT_SUBMODE_L;
}
#endif

/* �Ƶ�ǰ������TafMmaComFunc.c�ļ� */

/*****************************************************************************
 �� �� ��  : TAF_MMA_CovertSrvDomainToSysCfgOperType
 ��������  : ת�����򵽲�������
 �������  : enRatModeChange -- RATģʽ

 �������  : pstRatOperType -- ����RAT��������
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_SYS_CFG_OPER_TYPE TAF_MMA_CovertSrvDomainToSysCfgOperType(VOS_VOID)
{
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8   enSrvDomain;
    TAF_MMA_SYS_CFG_OPER_TYPE           usSysCfgOperType;
    TAF_MMA_SYS_CFG_PARA_STRU          *pstCurSysCfgPara = VOS_NULL_PTR;

    usSysCfgOperType = TAF_MMA_SYS_CFG_NONE_SET;

    pstCurSysCfgPara = TAF_MMA_GetSysCfgPara_SysCfg();

    if (TAF_MMA_SERVICE_DOMAIN_NOCHANGE == pstCurSysCfgPara->enSrvDomain)
    {
        /* �����ǰ�û����õķ�����Ϊno change��ʹ���ϴα���ķ����� */
        enSrvDomain = MN_MMA_GetServiceDomain();
    }
    else
    {
        /* �����ǰ�û����õķ�����Ϊno change��ʹ�õ�ǰ���õķ����� */
        enSrvDomain = pstCurSysCfgPara->enSrvDomain;
    }

    switch (enSrvDomain)
    {
        case TAF_MMA_SERVICE_DOMAIN_ANY:
        case TAF_MMA_SERVICE_DOMAIN_CS:
            usSysCfgOperType |= TAF_MMA_SYS_CFG_CS_ATTACH_SET;
            break;

        case TAF_MMA_SERVICE_DOMAIN_PS:
            usSysCfgOperType |= TAF_MMA_SYS_CFG_PS_ATTACH_SET;
            break;

        case TAF_MMA_SERVICE_DOMAIN_CS_PS:
            usSysCfgOperType |= TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED;
            break;

        default:
            break;
    }

    return usSysCfgOperType;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_CovertRatOperTypeToSysCfgOperType
 ��������  : ����RAT�����Ĳ�������ת��Ϊϵͳ���ò�������
 �������  : enRatModeChange -- RATģʽ

 �������  : pstRatOperType -- ����RAT��������
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_SYS_CFG_OPER_TYPE TAF_MMA_CovertRatOperTypeToSysCfgOperType(
    TAF_MMA_RAT_MODE_TYPE_ENUM_UINT8    enRatModeChange,
    TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU  *pstRatOperType
)
{
    TAF_MMA_SYS_CFG_OPER_TYPE           usSysCfgOperType;

    usSysCfgOperType = TAF_MMA_SYS_CFG_NONE_SET;

    switch (enRatModeChange)
    {
        case TAF_MMA_RAT_MODE_GUL_TO_CL:
            if (VOS_TRUE == pstRatOperType->ucDetachOperation)
            {
                /* GUL->CL, ǿ��detach CS/PS */
                usSysCfgOperType |= (TAF_MMA_SYS_CFG_CS_DETACH_SET|TAF_MMA_SYS_CFG_PS_DETACH_SET);
            }

            if (VOS_TRUE == pstRatOperType->ucAttachOperation)
            {
                /* GUL->CL, ���ݵ�ǰ����������attach���� */
                usSysCfgOperType |= TAF_MMA_CovertSrvDomainToSysCfgOperType();
            }
            break;

        case TAF_MMA_RAT_MODE_CL_TO_GUL:
            if (VOS_TRUE == pstRatOperType->ucDetachOperation)
            {
                /* CL->GUL, detach CS/PS */
                usSysCfgOperType |= (TAF_MMA_SYS_CFG_CS_DETACH_SET|TAF_MMA_SYS_CFG_PS_DETACH_SET);
            }

            if (VOS_TRUE == pstRatOperType->ucAttachOperation)
            {
                /* CL->GUL, ���ݵ�ǰ����������attach���� */
                usSysCfgOperType |= TAF_MMA_CovertSrvDomainToSysCfgOperType();
            }
            break;

        case TAF_MMA_RAT_MODE_CL_TO_CL:
            if (VOS_TRUE == pstRatOperType->ucDetachOperation)
            {
                /* CL->CL, detach CS/PS */
                usSysCfgOperType |= (TAF_MMA_SYS_CFG_CS_DETACH_SET|TAF_MMA_SYS_CFG_PS_DETACH_SET);
            }

            if (VOS_TRUE == pstRatOperType->ucAttachOperation)
            {
                /* CL->CL, ���ݵ�ǰ����������attach���� */
                usSysCfgOperType |= TAF_MMA_CovertSrvDomainToSysCfgOperType();
            }
            break;

        case TAF_MMA_RAT_MODE_GUL_TO_GUL:
            /* GUL->GUL���������ú��� */
        default:
            break;
    }

    if (VOS_TRUE == pstRatOperType->ucSysCfgOperation)
    {
        usSysCfgOperType |= TAF_MMA_SYS_CFG_MODE_SET;
    }

    return usSysCfgOperType;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetOperTypeTriggerredByRatChanges
 ��������  : ����SYSCFG�Ĳ�������
 �������  : pstSysCfg  -- ��ǰϵͳ���ò���
             pstLastRat -- �ϴ����õ�RAT

 �������  : penRatType -- ����RAT����
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_SYS_CFG_OPER_TYPE TAF_MMA_GetOperTypeTriggerredByRatChanges(
    TAF_MMA_RAT_ORDER_STRU             *pstCurrRat,
    TAF_MMA_RAT_ORDER_STRU             *pstLastRat,
    TAF_MMA_RAT_MODE_TYPE_ENUM_UINT8   *penRatType
)
{
    TAF_MMA_SYS_CFG_OPER_TYPE                               usOperType;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_MMA_RAT_CHANGE_OPER_TYPE_STRU                      *pstOperType = VOS_NULL_PTR;
    TAF_MMA_CL_RAT_SUBMODE_TYPE_ENUM_UINT8                  enCurrRatType;
    TAF_MMA_CL_RAT_SUBMODE_TYPE_ENUM_UINT8                  enLastRatType;
#endif

    usOperType = TAF_MMA_SYS_CFG_NONE_SET;

    /* get RAT mode change type */
    *penRatType = TAF_MMA_GetRatModeChangeType(pstCurrRat, pstLastRat);

    /* RAT is unchange, no opertion is required  */
    if (VOS_FALSE == TAF_MMA_IsRatOrderChange(pstCurrRat, pstLastRat))
    {
        return usOperType;
    }

    if (TAF_MMA_RAT_MODE_GUL_TO_GUL == *penRatType)
    {
        /* GUL֮���RAT�仯������Ҫ����sys cfg set���� */
        usOperType |= TAF_MMA_SYS_CFG_MODE_SET;

        return usOperType;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (TAF_MMA_RAT_MODE_GUL_TO_CL == *penRatType)
    {
        /* covert current RAT type */
        enCurrRatType = TAF_MMA_CovertCLRatOrderToCLSubMode(pstCurrRat);

        /* covert last RAT type */
        enLastRatType = TAF_MMA_CovertGULRatOrderToGULSubMode(pstLastRat);


        pstOperType = TAF_MMA_GetOperTypeFromGULToCL(enLastRatType, enCurrRatType);
    }
    else if (TAF_MMA_RAT_MODE_CL_TO_GUL == *penRatType)
    {
        /* covert current RAT type */
        enCurrRatType = TAF_MMA_CovertGULRatOrderToGULSubMode(pstCurrRat);

        /* covert last RAT type */
        enLastRatType = TAF_MMA_CovertCLRatOrderToCLSubMode(pstLastRat);


        pstOperType = TAF_MMA_GetOperTypeFromCLToGUL(enLastRatType, enCurrRatType);
    }
    else
    {
        /* covert current RAT type */
        enCurrRatType = TAF_MMA_CovertCLRatOrderToCLSubMode(pstCurrRat);

        /* covert last RAT type */
        enLastRatType = TAF_MMA_CovertCLRatOrderToCLSubMode(pstLastRat);

        pstOperType = TAF_MMA_GetOperTypeFromCLToCL(enLastRatType, enCurrRatType);
    }

    usOperType = TAF_MMA_CovertRatOperTypeToSysCfgOperType(*penRatType, pstOperType);
#endif
    return usOperType;
}

/*****************************************************************************
 �� �� ��  :TAF_MMA_IsUserSettedGuBandChanged_SysCfg
 ��������  :�ж��û�����syscfg��GUƵ�β�����ԭ�����Ƿ����˸ı�
 �������  :pstGuBand     - �û����õ�syscfg GUƵ��
            pstOrigGuBand - ԭsyscfg ���õ�GUƵ��
 �������  :��
 �� �� ֵ  :VOS_TRUE  - �û�����syscfg��GUƵ����ԭ���÷����ı�
            VOS_FALSE - �û�����syscfg��GUƵ����ԭ����δ�����ı�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��15��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsUserSettedGuBandChanged_SysCfg(
    TAF_USER_SET_PREF_BAND64            *pstGuBand,
    TAF_MMA_USER_BAND_SET_UN            *pstOrigGuBand

)
{
    TAF_MMA_USER_BAND_SET_UN             uGuBand;

    if ((TAF_PH_BAND_NO_CHANGE != pstGuBand->ulBandLow)
     || (0                     != pstGuBand->ulBandHigh))
    {
        MN_MMA_Convert64BitBandTo32Bit(pstGuBand, &uGuBand.ulPrefBand);
        MN_MMA_ConvertGUFrequencyBand(&uGuBand.ulPrefBand);

        if (uGuBand.ulPrefBand != pstOrigGuBand->ulPrefBand)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  :TAF_MMA_IsUserRoamSettingChange_SysCfg
 ��������  :�ж��û�����syscfg���������øı�
 �������  :ucCurrRoam - sys cfg���õ�����ֵ
            ucLastRoam - �ϴ��û����õ�����ֵ
 �������  :��
 �� �� ֵ  :VOS_TRUE  - ����ֵ�ı�
            VOS_FALSE - ����ֵδ�ı�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsUserRoamSettingChange_SysCfg(
    TAF_MMA_ROAM_MODE_ENUM_UINT8        enCurrRoam,
    TAF_MMA_ROAM_MODE_ENUM_UINT8        enLastRoam
)
{
    NAS_NVIM_ROAM_CFG_INFO_STRU         stRoamFeature;

    PS_MEM_SET(&stRoamFeature, 0x00, sizeof(stRoamFeature));

    if (NV_OK != NV_Read(en_NV_Item_Roam_Capa, &stRoamFeature, sizeof(stRoamFeature)))
    {
        MN_ERR_LOG("TAF_MMA_IsUserRoamSettingChange_SysCfg: Read en_NV_Item_Roam_Capa Nvim Error");
        return VOS_FALSE;
    }

    /* ��������NVδ����ʱ��0��ʾ��֧�����Σ�1��ʾ�������Σ�2��ʾ���ı� */
    if (NAS_MSCC_PIF_ROAM_FEATURE_OFF == stRoamFeature.ucRoamFeatureFlg)
    {
        if ((enLastRoam                                != enCurrRoam)
         && (2 != enCurrRoam))
        {
            return VOS_TRUE;
        }
    }
    else
    {
        /******************************************************************************************************
        ��������NV����ʱ��
        TAF_MMA_ROAM_NATIONAL_ON_INTERNATIONAL_ON,                                    �������ڹ�������
        TAF_MMA_ROAM_NATIONAL_ON_INTERNATIONAL_OFF,                                   �����������Σ��رչ�������
        TAF_MMA_ROAM_NATIONAL_OFF_INTERNATIONAL_ON,                                   �رչ������Σ�������������
        TAF_MMA_ROAM_NATIONAL_OFF_INTERNATIONAL_OFF,                                  �رչ��ڹ�������
        *******************************************************************************************************/
        if ((enLastRoam            != enCurrRoam)
            && (TAF_MMA_ROAM_UNCHANGE != enCurrRoam))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetOperTypeTriggerredBySrvDomain
 ��������  : ϵͳ�����������ô�����������Ԥ����
 �������  : enSrvDomain -- ������

 �������  : penDetachReason -- �����Ҫdetach����������detachԭ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��21��
    ��    ��   : luojian id:107747
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��9��
    ��    ��   : h00313353
    �޸�����   : SrvDomain�궨���Ϊö��
  3.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
TAF_MMA_SYS_CFG_OPER_TYPE TAF_MMA_GetOperTypeTriggerredBySrvDomain(
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8    enSrvDomain,
    TAF_MMA_DETACH_CAUSE_ENUM_UINT8     *penDetachReason
)
{
    TAF_PH_MS_CLASS_TYPE                ucNewMsClass;
    TAF_PH_MS_CLASS_TYPE                ucCurMsClass;
    MMA_CLASS_CHANGE_INDEX_ENUM         enClassChnageIndex;
    TAF_MMA_SYS_CFG_OPER_TYPE           usSrvDomainSetFlg;

    MMA_ChangeSrv2Class(enSrvDomain, &ucNewMsClass);

    ucCurMsClass = gstMmaValue.stSetMsClass.MsClassType;

    gstMmaValue.stSetMsClass.NewMsClassType = ucNewMsClass;

    /*���ݵ�ǰ�ֻ������ж���ҪATTACH����DETACH����*/
    enClassChnageIndex = (MMA_CLASS_CHANGE_INDEX_ENUM)(((ucCurMsClass << 4) & 0xf0)
                                                     | (ucNewMsClass & 0x0f));

    usSrvDomainSetFlg = TAF_MMA_SYS_CFG_NONE_SET;

    switch (enClassChnageIndex)
    {
            /*NULL->A*/
        case MMA_NULL2A:
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_CS_ATTACH_SET;
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_PS_ATTACH_SET;
            break;

            /*CG->A*/
        case MMA_CG2A:

            /*NULL->CC*/
        case MMA_NULL2CC:
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_CS_ATTACH_SET;
            break;

            /*NULL->CG*/
        case MMA_NULL2CG:

            /*CC->A*/
        case MMA_CC2A:
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_PS_ATTACH_SET;
            break;

            /*ֻ��DETACH����������л�*/
            /*CC->NULL*/
        case MMA_CC2NULL:

            /*A->CG*/
        case MMA_A2CG:
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_CS_DETACH_SET;
            break;

            /*CG->NULL*/
        case MMA_CG2NULL:

            /*A->CC*/
        case MMA_A2CC:
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_PS_DETACH_SET;
            break;

            /*A->NULL*/
        case MMA_A2NULL:
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_CS_DETACH_SET;
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_PS_DETACH_SET;
            break;

            /*CG->CC*/
        case MMA_CG2CC:
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_PS_DETACH_SET;
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_CS_ATTACH_SET;
            break;

            /*CC->CG*/
        case MMA_CC2CG:
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_CS_DETACH_SET;
            usSrvDomainSetFlg |= TAF_MMA_SYS_CFG_PS_ATTACH_SET;
            break;

        default:
            break;
    }

    if (0 != (TAF_MMA_SYS_CFG_DETACH_REQ_REQUIRED & usSrvDomainSetFlg))
    {
        *penDetachReason = TAF_MMA_DETACH_CAUSE_SRV_DOMAIN_DETACH;
    }

    return usSrvDomainSetFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsUserSrvDomainSettingChange_SysCfg
 ��������  : check service domain setting change
 �������  : ucCurrSrvDomain -- ��ǰ�û����õķ�����
             ucLastSrvDomain -- �ϴ��û����õķ�����
 �������  : VOS_VOID
 �� �� ֵ  : VOS_TRUE  -- ���������仯
             VOS_FALSE -- ������δ�����仯
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsUserSrvDomainSettingChange_SysCfg(
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8     ucCurrSrvDomain,
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8     ucLastSrvDomain
)
{
    if (TAF_MMA_SERVICE_DOMAIN_NOCHANGE != ucCurrSrvDomain)
    {
        if (ucCurrSrvDomain != ucLastSrvDomain)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_MMA_NeedDetachAttach_CampOnGUMode
 ��������  : �Ƿ�ӵ�ǰפ��GUģ����ΪLonly��ֻ��L��Ƶ��,
              ��ӵ�ǰ��Lģʽ������Ϊû��Lģʽ
 �������  : pstSysCfgPara ��ǰSYSCFG����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:GU to L Only;VOS_FALSE:��GU to L only
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012041002516: SYSCFG����L��GUģ֮��ģʽ�л�ʱ��
                 ��Ҫ����Detach��Attach����
  2.��    ��   : 2012��6��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012061502460:L only ������ģʽ��������ģʽ��L only��Ҫ����Detach/Attach
  3.��    ��   : 2013��4��3��
    ��    ��   : z00161729
    �޸�����   : �����ϱ�AT�������������C�˼�mma��mscc�ӿڵ���
  4.��    ��   : 2014��2��13��
    ��    ��   : w00167002
    �޸�����   : L-C��������Ŀ:����SYSCFG�����ò�ѯ�ӿ�
  5.��    ��   : 2015��4��10��
    ��    ��   : h00313353
    �޸�����   : SysCfg�ع�
  6.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
/* Modified by w00167002 for L-C��������Ŀ, 2014-2-13, begin */
VOS_UINT32  TAF_MMA_NeedDetachAttach_CampOnGUMode(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
)
/* Modified by w00167002 for L-C��������Ŀ, 2014-2-13, end */
{
    VOS_UINT32                          ulPrefBand;
    VOS_UINT32                          ulNeedAttachDetachFlag;
    VOS_UINT32                          ulNewRatLteExistFlag;
    VOS_UINT32                          ulOldRatLteExistFlag;
    TAF_USER_SET_PREF_BAND64           *pstOldLteBand = VOS_NULL_PTR;

    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, begin */
    TAF_SDC_SYS_MODE_ENUM_UINT8         enCurRatType;

    enCurRatType = TAF_SDC_GetSysMode();
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, end */

    ulPrefBand             = 0;
    ulNeedAttachDetachFlag = VOS_FALSE;

    /* ��GUƵ�� pstSysCfgPara->stGuBand 64λת��Ϊ32λ�� */
    MN_MMA_Convert64BitBandTo32Bit(&pstSysCfgPara->stGuBand, &ulPrefBand);
    MN_MMA_ConvertGUFrequencyBand(&ulPrefBand);

    /* ��ȡ�û����õ�LBand */
    TAF_MMA_ConvertLteFrequencyBand(&pstSysCfgPara->stLBand);

    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, begin */
    if ((TAF_SDC_SYS_MODE_WCDMA == enCurRatType)
     || (TAF_SDC_SYS_MODE_GSM == enCurRatType))
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, end */
    {
        /* ��ǰפ��GUģ�������õ�ģʽΪL only */
        if ((VOS_TRUE == MN_MMA_IsLOnlyMode(&(pstSysCfgPara->stRatOrder)))
         || (0 == ulPrefBand))
        {
            ulNeedAttachDetachFlag = VOS_TRUE;

            return ulNeedAttachDetachFlag;
        }


        /* ��ǰפ��GUģ��ģʽ��֧��L��û��L�ĳ���,��Ҫ��Detach/Attach */

        pstOldLteBand = TAF_MMA_GetUserSetLteBandAddr();

        if ((VOS_TRUE == MN_MMA_IsSpecRatSupported(TAF_MMA_RAT_LTE))
         && ((0 != pstOldLteBand->ulBandHigh)
         ||  (0 != pstOldLteBand->ulBandLow)))
        {
            ulOldRatLteExistFlag = VOS_TRUE;
        }
        else
        {
            ulOldRatLteExistFlag = VOS_FALSE;
        }

        if ( (VOS_TRUE ==  MN_MMA_IsSpecRatInRatList(TAF_MMA_RAT_LTE, &(pstSysCfgPara->stRatOrder)))
         && ((0 != pstSysCfgPara->stLBand.ulBandHigh)
          || (0 != pstSysCfgPara->stLBand.ulBandLow)))
        {
            ulNewRatLteExistFlag = VOS_TRUE;
        }
        else
        {
            ulNewRatLteExistFlag = VOS_FALSE;
        }

        if ((VOS_TRUE  == ulOldRatLteExistFlag)
         && (VOS_FALSE == ulNewRatLteExistFlag))
        {
            ulNeedAttachDetachFlag = VOS_TRUE;
        }

    }

    return ulNeedAttachDetachFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_NeedDetachAttach_CampOnLMode
 ��������  : �Ƿ�ӵ�ǰפ��Lģ����ΪGU only��ֻ��GU��Ƶ��
 �������  : pstSysCfgPara ��ǰSYSCFG����
 �������  : ��
 �� �� ֵ  : VOS_TRUE: L to GU Only;VOS_FALSE:��L to GU Only
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012041002516: SYSCFG����L��GUģ֮��ģʽ�л�ʱ��
                 ��Ҫ����Detach��Attach����
  2.��    ��   : 2012��6��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012061502460:L only ������ģʽ��������ģʽ��L only��Ҫ����Detach/Attach
  3.��    ��   : 2013��4��3��
    ��    ��   : z00161729
    �޸�����   : �����ϱ�AT�������������C�˼�mma��mscc�ӿڵ���
  4.��    ��   : 2014��2��13��
    ��    ��   : w00167002
    �޸�����   : L-C��������Ŀ:����SYSCFG�����ò�ѯ�ӿ�
  5.��    ��   : 2015��4��10��
    ��    ��   : h00313353
    �޸�����   : SysCfg�ع�
  6.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
/* Modified by w00167002 for L-C��������Ŀ, 2014-2-13, begin */
VOS_UINT32  TAF_MMA_NeedDetachAttach_CampOnLMode(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
)
/* Modified by w00167002 for L-C��������Ŀ, 2014-2-13, end */
{
    VOS_UINT32                          ulDetachAttachFlag;
    VOS_UINT32                          ulOldRatOnlyLteFlag;
    VOS_UINT32                          ulNewRatOnlyLteFlag;
    VOS_UINT32                          ulPrefBand;
    TAF_MMA_SYSCFG_USER_SET_BAND_STRU  *pstOldUserSetBand = VOS_NULL_PTR;

    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, begin */
    TAF_SDC_SYS_MODE_ENUM_UINT8          enCurRatType;

    enCurRatType  = TAF_SDC_GetSysMode();
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, end */

    ulDetachAttachFlag  = VOS_FALSE;

    /* ��GUƵ�� pstSysCfgPara->stGuBand 64λת��Ϊ32λ�� */
    MN_MMA_Convert64BitBandTo32Bit(&pstSysCfgPara->stGuBand, &ulPrefBand);
    MN_MMA_ConvertGUFrequencyBand(&ulPrefBand);

    /* ��ȡ�û����õ�LBand */
    TAF_MMA_ConvertLteFrequencyBand(&pstSysCfgPara->stLBand);

    pstOldUserSetBand = TAF_MMA_GetSyscfgUserSetBandAddr();

    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, begin */
    if (TAF_SDC_SYS_MODE_LTE == enCurRatType)
    /* Modified by z00161729 for �����ϱ�AT�������������C��, 2013-4-3, end */
    {
        /* Ŀ��ģʽ����ΪGUʱ����Ҫ����Detach/Attach */
        if ((VOS_FALSE == MN_MMA_IsSpecRatInRatList(TAF_MMA_RAT_LTE, &(pstSysCfgPara->stRatOrder)))
         || ((0 == pstSysCfgPara->stLBand.ulBandHigh)
          && (0 == pstSysCfgPara->stLBand.ulBandLow)))
        {
            ulDetachAttachFlag = VOS_TRUE;

            return ulDetachAttachFlag;
        }


        /* ��Lonly����L onlyʱ�����ߴӷ�Lonly��L onlyʱ,��Ҫ����Detach/Attach */

        /* �ϵ������Ƿ�LTE only */
        if ((VOS_TRUE == MN_MMA_IsLOnlyMode(TAF_MMA_GetRatPrioListAddr()))
         || (0 == pstOldUserSetBand->uUserSetGuBand.ulPrefBand))
        {
            ulOldRatOnlyLteFlag = VOS_TRUE;
        }
        else
        {
            ulOldRatOnlyLteFlag = VOS_FALSE;
        }

        /* �µ������Ƿ�LTE only */
        if ((VOS_TRUE == MN_MMA_IsLOnlyMode(&(pstSysCfgPara->stRatOrder)))
         || (0 == ulPrefBand))
        {
            ulNewRatOnlyLteFlag = VOS_TRUE;
        }
        else
        {
            ulNewRatOnlyLteFlag = VOS_FALSE;
        }

        if (ulOldRatOnlyLteFlag != ulNewRatOnlyLteFlag)
        {
            ulDetachAttachFlag = VOS_TRUE;
        }


    }

    return ulDetachAttachFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateRatTrigedAttachPara
 ��������  : ����RAT�仯,���·������Attach���ͺ�SetFlag
 �������  : ucNewMsClassType,�����õ�Ms����
 �������  : pusSetFlg     ��ǰSYSCFG���ô��������ñ�־
             pucAttachType ��ǰSYSCFG���ô�����Attach����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012041002516: SYSCFG����L��GUģ֮��ģʽ�л�ʱ��
                 ��Ҫ����Detach��Attach����
  2.��    ��   : 2014��3��25��
    ��    ��   : s00217060
    �޸�����   : DTS2014032101534:at^cgcatt=0,1,����SYSCFG��LUG��ΪUGʱ������Ҫattach ps
  3.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
TAF_MMA_SYS_CFG_OPER_TYPE TAF_MMA_UpdateRatTrigedAttachPara(
    TAF_PH_MS_CLASS_TYPE                ucNewMsClassType
)
{
    /* Attach�����뵱ǰ�ķ�����������ͬ:
     PS Onlyʱ,����PS attach,CS_PSʱ,���� CS_PS Attach,CS only����CS Attach */
    VOS_UINT8                           ucCsAttachAllow;
    VOS_UINT8                           ucPsAttachAllow;
    VOS_UINT8                           ucSndPsAttach;
    VOS_UINT8                           ucSndCsAttach;
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType;

    usOperType = TAF_MMA_SYS_CFG_NONE_SET;

    ucSndPsAttach       = VOS_TRUE;
    ucSndCsAttach       = VOS_TRUE;
    ucCsAttachAllow     = TAF_SDC_GetCsAttachAllowFlg();
    ucPsAttachAllow     = TAF_SDC_GetPsAttachAllowFlg();

    /* �������syscfg��ҪPS attach, ��ǰ���ֻ�ģʽ�϶���֧��PS���
       1.���syscfg֮ǰ���ֻ�ģʽ��֧��PS��ģ�����ps������ע�ᣬ��ô������at^cgcatt=0,1���µ�ps detach,����Ҫ��MSCC��attach req
       2.���syscfg֮ǰ���ֻ�ģʽ��֧��PS��ģ�����PS����ע�ᣬ��Ҫ��MSCC��attach req
       3.���syscfg֮ǰ���ֻ�ģʽ�ǲ�֧��PS��ģ���������Ϊ֧�֣���Ҫ��MSCC��attach req */
    /* CS������ͬ */

    /* ֮ǰ��ģʽ֧��PS�򣬵�PS������ע�ᣬ����Ҫ��ps attach */
    if ( (VOS_TRUE  == TAF_MMA_IsPsServDomainAvail(gstMmaValue.stSetMsClass.MsClassType))
      && (VOS_FALSE == ucPsAttachAllow) )
    {
        ucSndPsAttach   = VOS_FALSE;
    }

    /* ֮ǰ��ģʽ֧��CS�򣬵�CS������ע�ᣬ����Ҫ��cs attach */
    if ( (VOS_TRUE  == TAF_MMA_IsCsServDomainAvail(gstMmaValue.stSetMsClass.MsClassType))
      && (VOS_FALSE == ucCsAttachAllow) )
    {
        ucSndCsAttach   = VOS_FALSE;
    }

    if (TAF_PH_MS_CLASS_A == ucNewMsClassType)
    {
        /* ���CS��PS������Ҫattach,ֱ�ӷ��� */
        if ( (VOS_FALSE == ucSndCsAttach)
          && (VOS_FALSE == ucSndPsAttach) )
        {
            return usOperType;
        }

        /* CS��PS����ֻ��һ����Ҫattachʱ���޸���Ӧ��pusSetFlg��pucAttachType */
        if (ucSndCsAttach != ucSndPsAttach)
        {
            if (VOS_TRUE == ucSndCsAttach)
            {
                usOperType |= TAF_MMA_SYS_CFG_CS_ATTACH_SET;
            }
            else
            {
                usOperType |= TAF_MMA_SYS_CFG_PS_ATTACH_SET;
            }
        }
        else
        {
            /* ��������Ҫattach */
            usOperType |= TAF_MMA_SYS_CFG_CS_ATTACH_SET;
            usOperType |= TAF_MMA_SYS_CFG_PS_ATTACH_SET;
        }
    }
    else if (TAF_PH_MS_CLASS_CG == ucNewMsClassType)
    {
        /* ����Ҫps attachʱ�����־ */
        if (VOS_FALSE == ucSndPsAttach)
        {
            return usOperType;
        }

        usOperType |= TAF_MMA_SYS_CFG_PS_ATTACH_SET;
    }
    else
    {
        /* ����Ҫcs attachʱ�����־ */
        if (VOS_FALSE == ucSndCsAttach)
        {
            return usOperType;
        }

        usOperType |= TAF_MMA_SYS_CFG_CS_ATTACH_SET;
    }

    return usOperType;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateRatTrigedSrvDomianPara
 ��������  : ����RAT�仯,���·������Detach,Attach���ͺ�SetFlag
 �������  : pstSysCfgPara ��ǰSYSCFG����
 �������  : ��
 �� �� ֵ  : TAF_MMA_SYS_CFG_OPER_TYPE --���ز�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012041002516: SYSCFG����L��GUģ֮��ģʽ�л�ʱ��
                 ��Ҫ����Detach��Attach����
  2.��    ��   : 2012��6��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012061502460:L only ������ģʽ��������ģʽ��L only��Ҫ����Detach/Attach
  3.��    ��   : 2014��2��13��
    ��    ��   : w00167002
    �޸�����   : L-C��������Ŀ:����SYSCFG�����ò�ѯ�ӿ�
  4.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
/* Modified by w00167002 for L-C��������Ŀ, 2014-2-13, begin */
TAF_MMA_SYS_CFG_OPER_TYPE TAF_MMA_UpdateRatTrigedSrvDomianPara(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
)
/* Modified by w00167002 for L-C��������Ŀ, 2014-2-13, end */
{
    TAF_MMA_SYS_CFG_OPER_TYPE          usOperType;

    usOperType = TAF_MMA_SYS_CFG_NONE_SET;


    /* 1)  ��ǰפ����GUģ������ΪLģOnly��ֻ��L��Ƶ��ʱ��
        ���ݵ�ǰ��SrvDomain����Detach����
        (CS Only��PS Only��CS_PSʱ,������PS Detach)*/
    if (VOS_TRUE == TAF_MMA_NeedDetachAttach_CampOnGUMode(pstSysCfgPara))
    {
        usOperType |= TAF_MMA_SYS_CFG_PS_DETACH_SET;
    }

    /* 2)  ��ǰפ����Lģ������ΪGUģ��Ƶ��ֻ��GU��Ƶ��ʱ��
        ���ݵ�ǰ��SrvDomain����Detach����
        (PS Only����PS Detach ,CS_PSʱ,����CS_PS Detach) */
    if (VOS_TRUE == TAF_MMA_NeedDetachAttach_CampOnLMode(pstSysCfgPara))
    {
        if (TAF_PH_MS_CLASS_A == gstMmaValue.stSetMsClass.MsClassType)
        {
            usOperType |= TAF_MMA_SYS_CFG_PS_DETACH_SET;
            usOperType |= TAF_MMA_SYS_CFG_CS_DETACH_SET;
        }
        else
        {
            usOperType |= TAF_MMA_SYS_CFG_PS_DETACH_SET;
        }

    }

    /* RAT�仯������DetachʱҲ���ᴥ��Attach��ֱ�ӷ��� */
    if (TAF_MMA_SYS_CFG_NONE_SET == usOperType)
    {
        return usOperType;
    }

    /* ���µ�ǰ��Attach���ñ��� */
    usOperType |= TAF_MMA_UpdateRatTrigedAttachPara(gstMmaValue.stSetMsClass.NewMsClassType);

    return usOperType;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetSysCfgOperType
 ��������  : ����SYSCFG�Ĳ�������
 �������  : TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg
 �������  : TAF_MMA_SYS_CFG_OPER_TYPE          *pusOperType,
             TAF_MMA_DETACH_CAUSE_ENUM_UINT8    *penDetachReason
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��8��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_GetSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg,
    TAF_MMA_SYS_CFG_OPER_TYPE          *pusOperType,
    TAF_MMA_DETACH_CAUSE_ENUM_UINT8    *penDetachReason
)
{
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                    *pstLastSyscfgSet = VOS_NULL_PTR;
    TAF_MMA_RAT_MODE_TYPE_ENUM_UINT8                        enRatChangeType;

    pstLastSyscfgSet = TAF_MMA_GetLastSyscfgSetAddr();

    enRatChangeType  = TAF_MMA_RAT_MODE_BUTT;

    /* 1. ��ȡ��RAT�����Ĳ������� */
    *pusOperType |= TAF_MMA_GetOperTypeTriggerredByRatChanges(&(pstSysCfg->stRatOrder),
                                                              &(pstLastSyscfgSet->stRatPrioList),
                                                              &enRatChangeType);

    switch (enRatChangeType)
    {
        case TAF_MMA_RAT_MODE_GUL_TO_GUL:
        case TAF_MMA_RAT_MODE_CL_TO_GUL:
            {
                /* GUƵ�β��������˸ı� */
                if (VOS_TRUE == TAF_MMA_IsUserSettedGuBandChanged_SysCfg(&pstSysCfg->stGuBand,
                                                                         &pstLastSyscfgSet->stUserSetBand.uUserSetGuBand))
                {
                    *pusOperType |= TAF_MMA_SYS_CFG_BAND_SET;
                }

                /* GU����ָʾ�����˸ı� */
                if (VOS_TRUE == TAF_MMA_IsUserRoamSettingChange_SysCfg(pstSysCfg->enRoam,
                                                                       pstLastSyscfgSet->enRoam))
                {
                    *pusOperType |= TAF_MMA_SYS_CFG_ROAM_SET;
                }

                /* ���������˸ı� */
                if (VOS_TRUE == TAF_MMA_IsUserSrvDomainSettingChange_SysCfg(pstSysCfg->enSrvDomain,
                                                                            pstLastSyscfgSet->enSrvDomain))
                {
                    *pusOperType  |= TAF_MMA_GetOperTypeTriggerredBySrvDomain(pstSysCfg->enSrvDomain,
                                                                              penDetachReason);
                }

#if (FEATURE_ON == FEATURE_LTE)
                if (TAF_MMA_RAT_MODE_GUL_TO_GUL == enRatChangeType)
                {
                    /* RAT��Band�б仯ʱ������ */
                    if ((0 != (*pusOperType & TAF_MMA_SYS_CFG_MODE_SET))
                     || (0 != (*pusOperType & TAF_MMA_SYS_CFG_BAND_SET)))
                    {
                        *pusOperType |= TAF_MMA_UpdateRatTrigedSrvDomianPara(pstSysCfg);
                    }
                }
#endif
            }
            break;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case TAF_MMA_RAT_MODE_CL_TO_CL:
            {
                if (VOS_TRUE == TAF_MMA_IsLteExistInBothCurSysCfgAndOldSysCfg(pstSysCfg, pstLastSyscfgSet))
                {
                    /* ���������˸ı� */
                    if (VOS_TRUE == TAF_MMA_IsUserSrvDomainSettingChange_SysCfg(pstSysCfg->enSrvDomain,
                                                                                pstLastSyscfgSet->enSrvDomain))
                    {
                        *pusOperType  |= TAF_MMA_GetOperTypeTriggerredBySrvDomain(pstSysCfg->enSrvDomain,
                                                                                  penDetachReason);
                    }
                }
            }
            break;
#endif

        default:
            break;
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* LƵ�β��������ı� */
    if (VOS_TRUE == TAF_MMA_IsUserSettedLBandChanged(&pstSysCfg->stLBand,
                                                     &pstLastSyscfgSet->stUserSetBand.stUserSetLteBand))
    {
        *pusOperType |= TAF_MMA_SYS_CFG_BAND_SET;
    }
#endif

    /* ���������û�д���detach�����������ǰ��detach����������Ϊ��sys cfg������detach */
    if ((TAF_MMA_DETACH_CAUSE_SRV_DOMAIN_DETACH != *penDetachReason)
     && (0                                      != (*pusOperType & TAF_MMA_SYS_CFG_DETACH_REQ_REQUIRED)))
    {
        *penDetachReason = TAF_MMA_DETACH_CAUSE_RAT_OR_BAND_DETACH;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdatePrioAccessMode
 ��������  : ���½������ȼ�
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
VOS_VOID TAF_MMA_UpdatePrioAccessMode(
    TAF_MMA_SYS_CFG_PARA_STRU                              *pstCurrSysCfg,
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                    *pstLastSysCfg
)
{
    VOS_UINT32                          ucWriteAccessPrio;
    VOS_UINT16                          i;

    /* ��֧��Lģʱ��Ҫд�� */
    ucWriteAccessPrio = VOS_TRUE;

    for ( i = 0 ; i < pstLastSysCfg->stRatPrioList.ucRatOrderNum; i++ )
    {
        if ( TAF_MMA_RAT_LTE == pstLastSysCfg->stRatPrioList.aenRatOrder[i])
        {
            ucWriteAccessPrio = VOS_FALSE;
        }
    }

    if ( (VOS_TRUE                       == ucWriteAccessPrio)
      && (pstCurrSysCfg->enUserPrio      != pstLastSysCfg->enPrioRat)
      && (TAF_MMA_USER_SET_PRIO_NOCHANGE != pstCurrSysCfg->enUserPrio))
    {
        pstLastSysCfg->enPrioRat = pstCurrSysCfg->enUserPrio;

        TAF_MMA_WritePrioAccessModeToNvim();
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetDetachOperType_SysCfg
 ��������  : ��ȡDetach��������
 �������  : enDetachDomain -- detach��

 �������  : VOS_UINT16                                             *pusOperType,
             NAS_MSCC_PIF_DETACH_TYPE_ENUM_UINT32                   *penDetachType

 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��13��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_SYS_CFG_OPER_TYPE TAF_MMA_GetDetachOperType_SysCfg(
    TAF_MMA_SERVICE_DOMAIN_ENUM_UINT8                       enDetachDomain
)
{
    switch (enDetachDomain)
    {
        case TAF_MMA_SERVICE_DOMAIN_CS:
            return TAF_MMA_SYS_CFG_CS_DETACH_SET;

        case TAF_MMA_SERVICE_DOMAIN_PS:
            return TAF_MMA_SYS_CFG_PS_DETACH_SET;

        /* Ԥ�������Ѿ��Բ�����Ч�Լ�� */
        case TAF_MMA_SERVICE_DOMAIN_CS_PS:
        default:
            return (TAF_MMA_SYS_CFG_PS_DETACH_SET | TAF_MMA_SYS_CFG_CS_DETACH_SET);
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetAttachOperType_SysCfg
 ��������  : ���ݷ����򷵻�attach���ͺͲ�������
 �������  : TAF_MMA_ATTACH_TYPE_ENUM_UINT8                          enAttachType,
 �������  : TAF_MMA_SYS_CFG_OPER_TYPE                              *pusOperType
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��18��
    ��    ��   : l301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_GetAttachOperType_SysCfg(
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8                          enAttachType,
    TAF_MMA_SYS_CFG_OPER_TYPE                              *pusOperType
)
{
    switch (enAttachType)
    {
        case TAF_MMA_ATTACH_TYPE_IMSI:
            *pusOperType               |= TAF_MMA_SYS_CFG_CS_ATTACH_SET;
            break;

        case TAF_MMA_ATTACH_TYPE_GPRS:
            *pusOperType               |= TAF_MMA_SYS_CFG_PS_ATTACH_SET;
            break;

        /* Ԥ�������Ѿ��Բ�����Ч�Լ�� */
        case TAF_MMA_ATTACH_TYPE_GPRS_IMSI:
        default:
            *pusOperType               |= (TAF_MMA_SYS_CFG_PS_ATTACH_SET | TAF_MMA_SYS_CFG_CS_ATTACH_SET);
            break;

    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_WriteAccessModeToNvim
 ��������  : ��AccessModeд��NVIM
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��4��20��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��05��20��
    ��    ��   : m00217266
    �޸�����   : nv����

*****************************************************************************/
VOS_VOID TAF_MMA_WritePrioAccessModeToNvim(VOS_VOID)
{
    NAS_MMA_NVIM_ACCESS_MODE_STRU                            stAccessMode;
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU                     *pstLastSyscfgSet    = VOS_NULL_PTR;
    VOS_UINT32                                               ulLength;

    pstLastSyscfgSet     = TAF_MMA_GetLastSyscfgSetAddr();
    ulLength             = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_MMA_AccessMode, &ulLength);
    if (ulLength > sizeof(NAS_MMA_NVIM_ACCESS_MODE_STRU))
    {
        return;
    }

    if (NV_OK != NV_Read(en_NV_Item_MMA_AccessMode ,
                         &stAccessMode,
                         ulLength))

    {
        MN_WARN_LOG("TAF_MMA_WritePrioAccessModeToNvim:Read:NV_Read runs failed");
        return ;
    }

    stAccessMode.aucAccessMode[1] = pstLastSyscfgSet->enPrioRat;
    if (MMA_SUCCESS != MMA_WriteValue2Nvim(en_NV_Item_MMA_AccessMode,
                                           &stAccessMode,
                                           (VOS_UINT16)ulLength))
    {
        MN_ERR_LOG("TAF_MMA_WritePrioAccessModeToNvim():WARNING:NVIM_Write en_NV_Item_MMA_AccessMode failed");
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetAttachRsltFromServiceStatus_SysCfg
 ��������  : ����AttachType�ͷ�����״̬�ж�attach���
 �������  : enCsSrvStatus:Cs��״̬
             enPsSrvStatus:Ps��״̬
 �������  : *penAttachRslt:Attach���
             *pusPhoneError:��������
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��15��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_GetAttachRsltFromServiceStatus_SysCfg(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enCsSrvStatus,
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8                       enPsSrvStatus,
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32                    *penAttachRslt,
    VOS_UINT16                                             *pusPhoneError
)
{
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8      enAttachType;

    /* ��ȡ�����������Ϣ�е�AttachType */
    enAttachType = ((TAF_MMA_ATTACH_REQ_STRU *)(TAF_MMA_GetCurrFsmMsgAddr()->aucEntryMsgBuffer))->enAttachType;

    switch(enAttachType)
    {
        case TAF_MMA_ATTACH_TYPE_GPRS:
            if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enPsSrvStatus)
            {
                *penAttachRslt  = TAF_MMA_APP_OPER_RESULT_FAILURE;
                *pusPhoneError  = TAF_ERR_PHONE_ATTACH_FORBIDDEN;
            }
            break;

        case TAF_MMA_ATTACH_TYPE_IMSI:
            if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enCsSrvStatus)
            {
                *penAttachRslt  = TAF_MMA_APP_OPER_RESULT_FAILURE;
                *pusPhoneError  = TAF_ERR_PHONE_ATTACH_FORBIDDEN;
            }
            break;

        case TAF_MMA_ATTACH_TYPE_GPRS_IMSI:
            /* �����ж�CS+PS ATTACH�����ԭ��ֵ��ֻ�������򶼲�����������ʱ���Ÿ�AT�ϱ�ERROR */
            if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enPsSrvStatus)
             && (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE != enCsSrvStatus))
            {
                *penAttachRslt  = TAF_MMA_APP_OPER_RESULT_FAILURE;
                *pusPhoneError  = TAF_ERR_PHONE_ATTACH_FORBIDDEN;
            }
            break;

        default:
            /* AttachType���� */
            TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_GetAttachRsltFromServiceStatus_SysCfg():Wrong AttachType!");
            *penAttachRslt  = TAF_MMA_APP_OPER_RESULT_FAILURE;
            *pusPhoneError  = TAF_ERR_PHONE_ATTACH_FORBIDDEN;
            break;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcSysCfgOper_SysCfg
 ��������  : ���ݲ�������ִ�в��������ؽ��
 �������  : TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg
             TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
             TAF_MMA_DETACH_CAUSE_ENUM_UINT8     enDetachReason
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��10��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ProcSysCfgOper_SysCfg(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg,
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType,
    TAF_MMA_DETACH_CAUSE_ENUM_UINT8     enDetachReason
)
{
    VOS_UINT32                                              ulNeedSendMsccSysCfgFlag;
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8                          enAttachType;
    TAF_MMA_DETACH_TYPE_ENUM_UINT8                          enDetachType;
    NAS_MSCC_PIF_ATTACH_TYPE_ENUM_UINT32                    enMsccAttachType;
    NAS_MSCC_PIF_DETACH_TYPE_ENUM_UINT32                    enMsccDetachType;
    VOS_UINT8                                               ucOnlyRoamParaChanged;
    VOS_UINT8                                               ucIsNeedAttachPs;
    TAF_MMA_ENTRY_MSG_STRU                                 *pstEntryMsg = VOS_NULL_PTR;
    VOS_UINT8                                               ucClassType;

    ucOnlyRoamParaChanged    = VOS_FALSE;
    ucIsNeedAttachPs         = VOS_FALSE;

    ulNeedSendMsccSysCfgFlag = VOS_FALSE;

    enMsccAttachType         = NAS_MSCC_PIF_ATTACH_TYPE_BUTT;
    enMsccDetachType         = NAS_MSCC_PIF_DETACH_TYPE_BUTT;

    enDetachType             = TAF_MMA_GetDetachTypeFromSysCfgOperType_SysCfg(usOperType);
    enAttachType             = TAF_MMA_GetAttachTypeFromSysCfgOperType_SysCfg(usOperType);

    pstEntryMsg              = TAF_MMA_GetCurrFsmMsgAddr();

    /* ��������,����ģʽ����,Ƶ�����ò����з����ı䣬��Ҫ��ײ㷢��SYSCFG���� */
    if (TAF_MMA_SYS_CFG_NONE_SET != (usOperType & TAF_MMA_SYS_CFG_SET_REQ_REQUIRED))
    {
        ulNeedSendMsccSysCfgFlag = VOS_TRUE;
    }

    /* �����ҪDETACH���Ƚ���DETACH */
    if (TAF_MMA_SYS_CFG_NONE_SET != (usOperType & TAF_MMA_SYS_CFG_DETACH_REQ_REQUIRED))
    {
        if (VOS_OK == TAF_MMA_ConvertDetachTypeToMscc(enDetachType, &enMsccDetachType))
        {
            /* Modified by s00246516 for L-C��������Ŀ, 2014-02-14, Begin */
            (VOS_VOID)TAF_MMA_SndMsccDetachReq(STA_OPID_INSIDE, enMsccDetachType, enDetachReason);
            /* Modified by s00246516 for L-C��������Ŀ, 2014-02-14, End */

            /* ����������ʱ�� */
            TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_DETACH_CNF, TI_TAF_MMA_WAIT_MSCC_SYSCFG_DETACH_CNF_LEN);

            /* Ǩ��TAF_MMA_SYS_CFG_STA_WAIT_DETACH_CNF״̬ */
            TAF_MMA_FSM_SetCurrState(TAF_MMA_SYS_CFG_STA_WAIT_DETACH_CNF);
        }
    }
    /* �������ҪDETACH */
    else if (TAF_MMA_SYS_CFG_NONE_SET != (usOperType & TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED))
    {
        /* �����Ҫ��MSCC���н�������syscfg����,attach�������ý��������� */
        if ((VOS_OK == TAF_MMA_ConvertAttachTypeToMscc(enAttachType, &enMsccAttachType))
         && (VOS_FALSE == ulNeedSendMsccSysCfgFlag))
        {
            TAF_MMA_NotifyCsServiceChange_SysCfg(usOperType);

            /*ATTACH��Ϣ��Ҫ�ȷ���MODE CHANGE��Ϣ*/
            MMA_ChangeSrv2Class(pstSysCfg->enSrvDomain, &ucClassType);
            TAF_MMA_SndMsccModeChangeReq((NAS_MSCC_PIF_MS_MODE_ENUM_UINT32)ucClassType);

            /* Modified by b00269685 for L-C��������Ŀ, 2014-2-17, begin */
            (VOS_VOID)TAF_MMA_SndMsccAttachReq(TAF_MMA_GetAttachOpId(), enMsccAttachType, TAF_MMA_ATTACH_REASON_INITIAL);
            /* Modified by b00269685 for L-C��������Ŀ, 2014-2-17, end */
        }
    }
    else
    {
    }

    /* ��Ҫ֪ͨMSCC SYSCFG���� */
    if (VOS_TRUE == ulNeedSendMsccSysCfgFlag)
    {
        /* û��DETACH��ֱ��֪ͨ������ȴ�DETACH��� */
        if (TAF_MMA_DETACH_TYPE_NULL == enDetachType)
        {
            ucOnlyRoamParaChanged    = TAF_MMA_IsOnlyRoamParaChangeFlgFromSysCfgOperType_SysCfg(usOperType);
            ucIsNeedAttachPs         = TAF_MMA_IsNeedAttachPsFlgFromSysCfgOperType_SysCfg(usOperType);
            TAF_MMA_SndMsccSysCfgReq(pstSysCfg, ucOnlyRoamParaChanged, ucIsNeedAttachPs);

            /* ����������ʱ�� */
            TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_SYSCFG_CNF, TI_TAF_MMA_WAIT_MSCC_SYSCFG_CNF_LEN);

            /* Ǩ��TAF_MMA_SYS_CFG_STA_WAIT_SYS_CFG_CNF״̬ */
            TAF_MMA_FSM_SetCurrState(TAF_MMA_SYS_CFG_STA_WAIT_SYS_CFG_CNF);
        }
    }
    /* ����Ҫ֪ͨMSCC SYSCFG���� */
    else
    {
        if (ID_TAF_MMA_SYS_CFG_SET_REQ == TAF_MMA_GetCurrFsmEntryMsgId_SysCfg())
        {
            /* ����NV */
            TAF_MMA_UpdateSysCfgPara(pstSysCfg);
        }

        /* ����ҪDETACH */
        if (TAF_MMA_DETACH_TYPE_NULL == enDetachType)
        {
            if (ID_TAF_MMA_SYS_CFG_SET_REQ == TAF_MMA_GetCurrFsmEntryMsgId_SysCfg())
            {
                TAF_MMA_SndSysCfgSetCnf(&(((TAF_MMA_DETACH_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer))->stCtrl),
                                        TAF_ERR_NO_ERROR);
            }

            /* ����״̬���˳������Ϣ */
            TAF_MMA_SndSysCfgRsltInd(TAF_MMA_SYS_CFG_RSLT_SYS_CFG_SUCC, VOS_FALSE);

            /* �˳�״̬�� */
            TAF_MMA_FSM_QuitSubFsm();
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetCurrFsmEntryMsgId_SysCfg
 ��������  : ��ȡSYSCFG״̬���������Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��10��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_GetCurrFsmEntryMsgId_SysCfg(VOS_VOID)
{
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgId;

    /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg     = TAF_MMA_GetCurrFsmMsgAddr();

    ulMsgId         = TAF_MMA_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType);

    return ulMsgId;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetCsStateFromSyscfgOperType_SysCfg
 ��������  : ����SYSCFG�������ͷ���CS��״̬
 �������  : TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
 �������  : ��
 �� �� ֵ  : TAF_CS_SERVICE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��11��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_CS_SERVICE_ENUM_UINT32  TAF_MMA_GetCsStateFromSyscfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
)
{
    /* ��֧��SVLTE������Ҫ֪ͨMSG��STK,��Ϊ�ޱ仯 */
    if (VOS_FALSE == TAF_SDC_GetSvlteSupportFlag())
    {
        return TAF_CS_SERVICE_BUTT;
    }

    /* syscfg���ñ�־�µ�CS������������ */
    if (TAF_MMA_SYS_CFG_CS_DETACH_SET
        == (usOperType & TAF_MMA_SYS_CFG_CS_DETACH_SET))
    {
        return TAF_CS_OFF;
    }

    /* syscfg���ñ�־�µ�CS���������� */
    if (TAF_MMA_SYS_CFG_CS_ATTACH_SET
        == (usOperType & TAF_MMA_SYS_CFG_CS_ATTACH_SET))
    {
        return TAF_CS_ON;
    }

    /* �������Ĭ�ϲ���Ҫ���� */
    return TAF_CS_SERVICE_BUTT;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetDetachTypeFromSysCfgOperType_SysCfg
 ��������  : ���ݲ������ͷ���detach������
 �������  : TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
 �������  : ��
 �� �� ֵ  : TAF_MMA_DETACH_TYPE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��10��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_DETACH_TYPE_ENUM_UINT8 TAF_MMA_GetDetachTypeFromSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
)
{
    if((TAF_MMA_SYS_CFG_CS_DETACH_SET == (usOperType & TAF_MMA_SYS_CFG_CS_DETACH_SET))
    && (TAF_MMA_SYS_CFG_PS_DETACH_SET == (usOperType & TAF_MMA_SYS_CFG_PS_DETACH_SET)))
    {
        return TAF_MMA_DETACH_TYPE_GPRS_IMSI;
    }
    else if(TAF_MMA_SYS_CFG_CS_DETACH_SET == (usOperType & TAF_MMA_SYS_CFG_CS_DETACH_SET))
    {
        return TAF_MMA_DETACH_TYPE_IMSI;
    }
    else if(TAF_MMA_SYS_CFG_PS_DETACH_SET == (usOperType & TAF_MMA_SYS_CFG_PS_DETACH_SET))
    {
        return TAF_MMA_DETACH_TYPE_GPRS;
    }
    else
    {
        return TAF_MMA_DETACH_TYPE_NULL;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetAttachTypeFromSysCfgOperType_SysCfg
 ��������  : ���ݲ������ͷ���attach������
 �������  : TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
 �������  : ��
 �� �� ֵ  : TAF_MMA_ATTACH_TYPE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��10��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_ATTACH_TYPE_ENUM_UINT8 TAF_MMA_GetAttachTypeFromSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
)
{
    if((TAF_MMA_SYS_CFG_CS_ATTACH_SET == (usOperType & TAF_MMA_SYS_CFG_CS_ATTACH_SET))
    && (TAF_MMA_SYS_CFG_PS_ATTACH_SET == (usOperType & TAF_MMA_SYS_CFG_PS_ATTACH_SET)))
    {
        return TAF_MMA_ATTACH_TYPE_GPRS_IMSI;
    }
    else if(TAF_MMA_SYS_CFG_CS_ATTACH_SET == (usOperType & TAF_MMA_SYS_CFG_CS_ATTACH_SET))
    {
        return TAF_MMA_ATTACH_TYPE_IMSI;
    }
    else if(TAF_MMA_SYS_CFG_PS_ATTACH_SET == (usOperType & TAF_MMA_SYS_CFG_PS_ATTACH_SET))
    {
        return TAF_MMA_ATTACH_TYPE_GPRS;
    }
    else
    {
        return TAF_MMA_ATTACH_TYPE_NULL;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsOnlyRoamParaChangeFlgFromSysCfgOperType_SysCfg
 ��������  : ���ݲ������ͻ�ȡ�Ƿ�ֻ�����β����ı��־
 �������  : TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��16��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_MMA_IsOnlyRoamParaChangeFlgFromSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
)
{
    if ((TAF_MMA_SYS_CFG_MODE_SET != (usOperType & TAF_MMA_SYS_CFG_MODE_SET))
     && (TAF_MMA_SYS_CFG_BAND_SET != (usOperType & TAF_MMA_SYS_CFG_BAND_SET))
     && (TAF_MMA_SYS_CFG_ROAM_SET == (usOperType & TAF_MMA_SYS_CFG_ROAM_SET)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsNeedAttachPsFlgFromSysCfgOperType_SysCfg
 ��������  : ���ݲ������ͻ�ȡ�Ƿ�ֻ�����β����ı��־
 �������  : TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��16��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_MMA_IsNeedAttachPsFlgFromSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
)
{
    if (TAF_MMA_SYS_CFG_PS_ATTACH_SET == (usOperType & TAF_MMA_SYS_CFG_PS_ATTACH_SET))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_NotifyCsServiceChange_SysCfg
 ��������  : SYSCFG״̬����֪ͨCS����ı�
 �������  : TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��16��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_NotifyCsServiceChange_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
)
{
    TAF_CS_SERVICE_ENUM_UINT32          enCsState;

    enCsState = TAF_MMA_GetCsStateFromSyscfgOperType_SysCfg(usOperType);

    if (TAF_CS_SERVICE_BUTT != enCsState)
    {
        TAF_MMA_SndStkCsServiceChangeNotify(enCsState);
        TAF_MMA_SndMsgCsServiceChangeNotify(enCsState);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsLteExistInBothCurSysCfgAndOldSysCfg
 ��������  : ��ǰ�����ϴε�ϵͳ������LTE������
 �������  : pstCurSysCfg -- ��ǰ��ϵͳRAT����
             pstOldSyscfg -- �ϴε�ϵͳRAT����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- LTE�ڵ�ǰ�����ϴεĶ�������
             VOS_FALSE -- LTE�ڵ�ǰ�����ϴε�����û��ͬʱ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��4��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsLteExistInBothCurSysCfgAndOldSysCfg(
    TAF_MMA_SYS_CFG_PARA_STRU           *pstCurSysCfg,
    TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU *pstOldSyscfg
)
{
    VOS_UINT32                          ulCurLteSysCfg;

    ulCurLteSysCfg = MN_MMA_IsSpecRatInRatList(TAF_MMA_RAT_LTE, &pstCurSysCfg->stRatOrder);

    if ((VOS_TRUE == MN_MMA_IsSpecRatInRatList(TAF_MMA_RAT_LTE, &pstOldSyscfg->stRatPrioList))
     && (VOS_TRUE == ulCurLteSysCfg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  :TAF_MMA_IsNeedAttachAfterSyscfgSet_SysCfg
 ��������  :�ж�SYSCFG������ɺ��Ƿ���Ҫ����attach����
 �������  :enRst---syscfg���ý��
 �������  :penAttachType----��Ҫ����attachʱ��attach����
            pucClassType-----��Ҫ����attachʱ�ķ�����
 �� �� ֵ  :VOS_TRUE  - ��Ҫ����attach
            VOS_FALSE - ����Ҫ����attach
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��3��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsNeedAttachAfterSyscfgSet_SysCfg(
    NAS_MSCC_PIF_SYS_CFG_SET_RESULT_ENUM_UINT32             enRst,
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8                         *penAttachType,
    TAF_PH_MS_CLASS_TYPE                                   *pucClassType,
    TAF_MMA_SYS_CFG_OPER_TYPE                              *pusOperType
)
{
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType;
    TAF_MMA_SYS_CFG_OPER_TYPE           usOrigOperType;
    TAF_MMA_FSM_SYS_CFG_CTX_STRU       *pstSysCfgCtx = VOS_NULL_PTR;

    /* ��ȡ��ǰ״̬���������� */
    pstSysCfgCtx = &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx);

    usOperType      = pstSysCfgCtx->usOperType;
    usOrigOperType  = TAF_MMA_GetSysCfgOrigOperType_SysCfg();

    *pucClassType  = TAF_PH_MS_CLASS_NULL;

    MMA_ChangeSrv2Class(pstSysCfgCtx->stSysCfgPara.enSrvDomain, pucClassType);

    *penAttachType = TAF_MMA_GetAttachTypeFromSysCfgOperType_SysCfg(pstSysCfgCtx->usOperType);

    *pusOperType   = pstSysCfgCtx->usOperType;

    /* 1) syscfg���ô���DETACH-SYSCFG����-ATTACH����ʱ��syscfg������ɺ�,
            �������óɹ���ʧ��,����Ҫ����attach����; */
    if ((TAF_MMA_SYS_CFG_NONE_SET  != (usOperType & TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED))
     && (TAF_MMA_SYS_CFG_NONE_SET  != (usOrigOperType & TAF_MMA_SYS_CFG_DETACH_REQ_REQUIRED))
     && (TAF_MMA_SYS_CFG_NONE_SET  != (usOrigOperType & TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED)))
    {
        return VOS_TRUE;
    }

    /*
    2) syscfg���ô���DETACH-syscfg����,���syscfg����ʧ��,��Ҫ���·���attach����;
    */
    if ((TAF_MMA_SYS_CFG_NONE_SET         != (usOrigOperType & TAF_MMA_SYS_CFG_DETACH_REQ_REQUIRED))
     && (TAF_MMA_SYS_CFG_NONE_SET         == (usOperType & TAF_MMA_SYS_CFG_DETACH_REQ_REQUIRED))
     && (NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS != enRst))
    {
        /* detach�ĸ���,���ʱ��attach�����ĸ��� */
        *penAttachType = TAF_MMA_GetDetachTypeFromSysCfgOperType_SysCfg(usOrigOperType);

        /* SYSCFGʧ��,�ָ�ʱʹ��֮ǰ��class type */
        *pucClassType  = gstMmaValue.stSetMsClass.MsClassType;

        *pusOperType  = TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED;

        return VOS_TRUE;
    }

    /*
    3) syscfg���ô���ATTACH-syscfg����,���syscfg���óɹ�,��Ҫ����attach����;
    */
    if ((TAF_MMA_SYS_CFG_NONE_SET         != (usOrigOperType & TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED))
     && (TAF_MMA_SYS_CFG_NONE_SET         != (usOperType & TAF_MMA_SYS_CFG_ATTACH_REQ_REQUIRED))
     && (NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS == enRst))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*lint -restore*/


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */





