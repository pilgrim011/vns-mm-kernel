/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccInstMgmt.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2014��09��05��
  ��������   : ����1X CC(call control) instance����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��09��05��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "CnasCcb.h"
#include  "CnasXccInstanceMgmt.h"
#include  "xcc_xcall_pif.h"
#include  "xsd_xcc_pif.h"
#include  "cas_1x_control_main_nas_pif.h"
#include  "cas_1x_access_ctrl_proc_nas_pif.h"
#include  "cas_1x_trchctrl_proc_nas_pif.h"
#include  "xcc_aps_pif.h"
#include  "xsd_xcc_pif.h"
#include  "CnasXccTimer.h"
#include  "CnasMntn.h"
#include  "NasFsm.h"
#include  "CnasXccSndInternalMsg.h"
#include  "CnasXccComFunc.h"
#include  "CnasXccCtx.h"
#include  "CnasXccSndXcall.h"
#include  "CnasCcb.h"
#include  "xcc_sms_pif.h"

#include  "xcc_xpds_pif.h"
#include  "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_INSTANCE_MGMT_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ���Ͷ���
*****************************************************************************/
typedef VOS_VOID (*CNAS_XCC_GET_CALL_INSTANCE_FUNC)(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList);

typedef struct
{
    VOS_UINT32                          ulMsgEvtType;
    CNAS_XCC_GET_CALL_INSTANCE_FUNC     pfGetCallInstanceFun;
} CNAS_XCC_GET_CALL_INSTANCE_STRU;

/*****************************************************************************
  3 ȫ�ֱ�������
*****************************************************************************/
CNAS_XCC_GET_CALL_INSTANCE_STRU g_astCnasXccGetCallInstanceMsgTbl[] = {
    /* 1XCASM����Ϣ */
    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_EST_CNF,
                     CNAS_XCC_GetCallInstanceOf1xEstCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_DSCH_DATA_CNF,
                     CNAS_XCC_GetCallInstanceOf1xDschDataCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_DSCH_DATA_IND,
                     CNAS_XCC_GetCallInstanceOf1xDschDataInd),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_PAGING_IND,
                     CNAS_XCC_GetCallInstanceOf1xPagingInd),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_RESET_WFO_SUBSTATE_TIMER_IND,
                     CNAS_XCC_GetCallInstanceOf1xResetWfoSubStateTimerInd),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND,
                     CNAS_XCC_GetCallInstanceOf1xUpdateCallInfoInd),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_INIT_IND,
                     CNAS_XCC_GetCallInstanceOf1xCallInitInd),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_REL_IND,
                     CNAS_XCC_GetCallInstanceOf1xCallRelInd),

    NAS_ACT_TBL_ITEM(UEPS_PID_1XCASM,
                     ID_CAS_CNAS_1X_CALL_TERMINATE_IND,
                     CNAS_XCC_GetCallInstanceOf1xCallTerminateInd),

    /* XCALL��Ϣ */
    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_ORIG_CALL_REQ,
                     CNAS_XCC_GetCallInstanceOfOrigCallReq),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_HANGUP_CALL_REQ,
                     CNAS_XCC_GetCallInstanceOfOtherMsg),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_INCOMING_CALL_RSP,
                     CNAS_XCC_GetCallInstanceOfOtherMsg),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_ANSWER_CALL_REQ,
                     CNAS_XCC_GetCallInstanceOfOtherMsg),

#if 0
    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_START_DTMF_REQ,
                     CNAS_XCC_GetCallInstanceOfXccStartDtmfReq),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_STOP_DTMF_REQ,
                     CNAS_XCC_GetCallInstanceOfXccStopDtmfReq),
#endif

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_SEND_BURST_DTMF_REQ,
                     CNAS_XCC_GetCallInstanceOfXccSendBurstDtmfReq),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_SEND_FLASH_REQ,
                     CNAS_XCC_GetCallInstanceOfXccSendFlashReq),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_XCALL_XCC_SEND_CONT_DTMF_REQ,
                     CNAS_XCC_GetCallInstanceOfXccSendContDtmfReq),

    /* APS��Ϣ */
    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_DATA_CALL_SUSPEND_RSP,
                     CNAS_XCC_GetCallInstanceOfApsDataCallSuspendRsp),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_ORIG_DATA_CALL_REQ,
                     CNAS_XCC_GetCallInstanceOfOrigCallReq),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_HANGUP_DATA_CALL_REQ,
                     CNAS_XCC_GetCallInstanceOfOtherMsg),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_INCOMING_CALL_RSP,
                     CNAS_XCC_GetCallInstanceOfOtherMsg),

    NAS_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_APS_XCC_ANSWER_DATA_CALL_REQ,
                     CNAS_XCC_GetCallInstanceOfOtherMsg),

    /* SMS��Ϣ */
    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_ORIG_SMS_CALL_REQ,
                     CNAS_XCC_GetCallInstanceOfOrigCallReq),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_END_SMS_CALL_REQ,
                     CNAS_XCC_GetCallInstanceOfOtherMsg),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_INCOMING_CALL_RSP,
                     CNAS_XCC_GetCallInstanceOfOtherMsg),

    NAS_ACT_TBL_ITEM(UEPS_PID_XSMS,
                     ID_CSMS_XCC_ANSWER_CALL_REQ,
                     CNAS_XCC_GetCallInstanceOfOtherMsg),


    /* XPDS��Ϣ */
    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_ORIG_AGPS_CALL_REQ,
                     CNAS_XCC_GetCallInstanceOfOrigCallReq),

    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_END_AGPS_CALL_REQ,
                     CNAS_XCC_GetCallInstanceOfOtherMsg),

    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_INCOMING_CALL_RSP,
                     CNAS_XCC_GetCallInstanceOfOtherMsg),

    NAS_ACT_TBL_ITEM(UEPS_PID_XPDS,
                     ID_XPDS_XCC_ANSWER_CALL_REQ,
                     CNAS_XCC_GetCallInstanceOfOtherMsg),


    /* Timer��Ϣ */
    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_T52M,
                     CNAS_XCC_GetCallInstanceOfTimerMsg),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_T53M,
                     CNAS_XCC_GetCallInstanceOfTimerMsg),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_APS_SUSPEND_RSP,
                     CNAS_XCC_GetCallInstanceOfTimerMsg),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_AS_EST_CNF,
                     CNAS_XCC_GetCallInstanceOfTimerMsg),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_AS_CALL_INIT_IND,
                     CNAS_XCC_GetCallInstanceOfTimerMsg),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_CONN_L2_ACK,
                     CNAS_XCC_GetCallInstanceOfTimerMsg),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_WAIT_FOR_INCOMING_RSP,
                     CNAS_XCC_GetCallInstanceOfTimerMsg),

    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_CNAS_XCC_PROTECT_POWER_DOWN_ENDING,
                     CNAS_XCC_GetCallInstanceOfTimerMsg),

    /* XCC�ڲ���Ϣ */
    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_MO_CALLING_RSLT_CNF,
                     CNAS_XCC_GetCallInstanceOfXccMoCalingRlstCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_MT_CALLING_RSLT_CNF,
                     CNAS_XCC_GetCallInstanceOfXccMtCalingRlstCnf),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_ABORT_REQ,
                     CNAS_XCC_GetCallInstanceOfXccAbortReq),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_POWER_DOWN_IND,
                     CNAS_XCC_GetCallInstanceOfXccPowerDownReq),

    NAS_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_CNAS_XCC_XCC_NDSS_REDIAL_IND,
                     CNAS_XCC_GetCallInstanceOfXccNdssRedialInd)
};


/*****************************************************************************
  4 ��������
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetActivedCallInstanceNum
 ��������  : ��ȡ�Ѿ������call instance��Ŀ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ucNum -- �����call instance��Ŀ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��05��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XCC_GetActivedCallInstanceNum(VOS_VOID)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr   = VOS_NULL_PTR;
    VOS_UINT8                           i;
    VOS_UINT8                           ucNum;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    ucNum = 0;
    for (i = 0; i < CNAS_XCC_MAX_FSM_ENTITY_NUM; i++)
    {
        if (VOS_TRUE == pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.ucIsEntityActive)
        {
            ucNum++;
        }
    }

    return ucNum;
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_AllocConnectedId
 ��������  : ����connect id�����ص�ǰ����connect id������
 �������  : ��
 �������  : pucIndex -- ���ص�ǰ�����call index
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��15��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XCC_AllocConnectedId(
    VOS_UINT8                          *pucIndex
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr   = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    for (i = 0; i < CNAS_XCC_MAX_FSM_ENTITY_NUM; i++)
    {
        if (VOS_FALSE == pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.ucIsEntityActive)
        {
            /* ����connect id��ucIsEntityActive��L1״̬������ */
            pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.ucConnectId = (i + 1);

            *pucIndex = i;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_IsCurrCallInstanceActive
 ��������  : check��ǰ��call control instance�Ƿ��Ѿ���ʹ��
 �������  : ��
 �������  : pstIndexList -- ��ǰ�����call index �б�
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��05��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_GetAllActiveCallInstanceIndex(
    CNAS_XCC_CALL_INSTANCE_LIST_STRU    *pstIndexList
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr   = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* ��ȡ�����call instance���� */
    for (i = 0; i < CNAS_XCC_MAX_FSM_ENTITY_NUM; i++)
    {
        if (VOS_TRUE == pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.ucIsEntityActive)
        {
            pstIndexList->aucInstance[pstIndexList->ucInstanceNum] = i;
            pstIndexList->ucInstanceNum++;
        }
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_IsVoiceCallInstanceActive
 ��������  : ���voice call����instance�Ƿ񼤻�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- �Ѽ���
             VOS_FALSE -- �޼���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��19��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XCC_IsVoiceCallInstanceActive(VOS_VOID)
{
    VOS_UINT8                           i;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    for (i = 0; i < CNAS_XCC_MAX_FSM_ENTITY_NUM; i++)
    {
        if (VOS_TRUE == pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.ucIsEntityActive)
        {
            CNAS_XCC_ConvertSoToServiceType(pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.enCurrentSo,
                                            &enServiceType);

            if ( (CNAS_XCC_SERVICE_TYPE_VOICE_CALL == enServiceType)
              || (CNAS_XCC_SERVICE_TYPE_LOOPBACK == enServiceType) )
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetVoiceCallInstance
 ��������  : ��ȡvoice call instance����
 �������  : ��
 �������  : pucIndex -- ����call instance����
 �� �� ֵ  : VOS_TRUE  -- �ҵ���Ӧ��call instance����
             VOS_FALSE -- ��Ӧ��call instance����û���ҵ�

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��05��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XCC_GetSpecTypeInstance(
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType,
    VOS_UINT8                          *pucIndex
)
{
    VOS_UINT8                           i;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enLocalServiceType;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;

    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* ��ȡ��Ϣ��Ҫ�����call instance */
    for (i = 0; i < CNAS_XCC_MAX_FSM_ENTITY_NUM; i++)
    {
        if (VOS_TRUE == pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.ucIsEntityActive)
        {
            CNAS_XCC_ConvertSoToServiceType(pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.enCurrentSo,
                                            &enLocalServiceType);

            if ( (enServiceType == enLocalServiceType)
              || (CNAS_XCC_SERVICE_TYPE_LOOPBACK == enLocalServiceType) )
            {
                *pucIndex = i;
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceIndexByConnId
 ��������  : ����UcConnId���Ҷ�Ӧ��Ҫ����Call Control Instanceʵ��
 �������  : ucConnId -- ҵ�����ӱ�ʶ

 �������  : pucIndex  -- ����call instance����
 �� �� ֵ  : VOS_TRUE  -- �ҵ���Ӧ��call instance����
             VOS_FALSE -- ��Ӧ��call instance����û���ҵ�

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��05��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XCC_GetCallInstanceIndexByConnId(
    VOS_UINT8                           ucConnId,
    VOS_UINT8                          *pucIndex
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr   = VOS_NULL_PTR;
    VOS_UINT8                           i;


    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* ����connId���Ҷ�Ӧ��call control instance״̬�������ĵ�ַ */
    for (i = 0; i < CNAS_XCC_MAX_FSM_ENTITY_NUM; i++)
    {
        if (VOS_TRUE == pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.ucIsEntityActive)
        {
            if (ucConnId == pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.ucConnectId)
            {
                *pucIndex = i;
                return VOS_TRUE;
            }
        }
    }

    /* ���û���ҵ�������ΪFALSE */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceIndexByCallId
 ��������  : ����ucCallId���Ҷ�Ӧ��Ҫ����Call Control Instanceʵ��
 �������  : ucCallId -- ҵ��ʵ��ID

 �������  : pucIndex  -- ����call instance����
 �� �� ֵ  : VOS_TRUE  -- �ҵ���Ӧ��call instance����
             VOS_FALSE -- ��Ӧ��call instance����û���ҵ�

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��12��
    ��    ��   : f279542
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 CNAS_XCC_GetCallInstanceIndexByCallId(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                          *pucIndex
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr   = VOS_NULL_PTR;
    VOS_UINT8                           i;


    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    /* ����connId���Ҷ�Ӧ��call control instance״̬�������ĵ�ַ */
    for (i = 0; i < CNAS_XCC_MAX_FSM_ENTITY_NUM; i++)
    {
        if (VOS_TRUE == pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.ucIsEntityActive)
        {
            if (ucCallId == pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.ucCallId)
            {
                *pucIndex = i;
                return VOS_TRUE;
            }
        }
    }

    /* ���û���ҵ�������ΪFALSE */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceIndexByCallRef
 ��������  : ����ucConRef���Ҷ�Ӧ��Ҫ����Call Control Instanceʵ��
 �������  : ucConRef     -- ҵ������Reference

 �������  : pucIndex     -- ����call instance����
 �� �� ֵ  : VOS_TRUE  -- �ҵ���Ӧ��call instance����
             VOS_FALSE -- ��Ӧ��call instance����û���ҵ�

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��06��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XCC_GetCallInstanceIndexByCallRef(
    VOS_UINT8                           ucConRef,
    VOS_UINT8                          *pucIndex
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr   = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstXccCtxAddr  = CNAS_XCC_GetCtxAddr();

    /* if CON_REF_INCLr equals ��0��, the layer 3Layer 3 shall deliver this message
       to the Call Control instance identified by NULL; otherwise, the layer 3 shall
       deliver this message to the Call Control instance identified by CON_REFr
     */
    if (CNAS_XCC_INVALID_CON_REF != ucConRef)
    {
        for (i = 0; i < CNAS_XCC_MAX_FSM_ENTITY_NUM; i++)
        {
            if (VOS_TRUE == pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.ucIsEntityActive)
            {
                if (ucConRef  == pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.ucConRef)
                {
                    *pucIndex = i;

                    return VOS_TRUE;
                }
            }
        }
    }
    else
    {
        /* ����NULL��ʶ��call control instance */
        for (i = 0; i < CNAS_XCC_MAX_FSM_ENTITY_NUM; i++)
        {
            if (VOS_TRUE == pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.ucIsEntityActive)
            {
                if (VOS_TRUE == pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.ucIsNullCc)
                {
                    *pucIndex = i;

                    return VOS_TRUE;
                }
            }
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_IsCallConRefExist
 ��������  : check����reference�Ƿ����
 �������  : ucConRef     -- ҵ������Reference

 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ����
             VOS_FALSE -- ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��29��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_XCC_IsCallConRefExist(
    VOS_UINT8                           ucConRef
)
{
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr   = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstXccCtxAddr  = CNAS_XCC_GetCtxAddr();

    /* if CON_REF_INCLr equals ��0��, the layer 3Layer 3 shall deliver this message
       to the Call Control instance identified by NULL; otherwise, the layer 3 shall
       deliver this message to the Call Control instance identified by CON_REFr
     */
    if (CNAS_XCC_INVALID_CON_REF != ucConRef)
    {
        for (i = 0; i < CNAS_XCC_MAX_FSM_ENTITY_NUM; i++)
        {
            if (VOS_TRUE == pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.ucIsEntityActive)
            {
                if (ucConRef  == pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.ucConRef)
                {
                    return VOS_TRUE;
                }
            }
        }
    }
    else
    {
        /* ����NULL��ʶ��call control instance */
        for (i = 0; i < CNAS_XCC_MAX_FSM_ENTITY_NUM; i++)
        {
            if (VOS_TRUE == pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.ucIsEntityActive)
            {
                if (VOS_TRUE == pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.ucIsNullCc)
                {
                    return VOS_TRUE;
                }
            }
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetConRefFromDschDataInd
 ��������  : ��f_dsch�տ���Ϣ�У���ȡconRef
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : pstCallInstanceFsmList -- ������Ҫ����call control instance�б�
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��15��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_GetConRefFromDschDataInd(
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd,
    VOS_UINT8                          *pucConRef
)
{
    CNAS_XCC_EAWIM_STRU                *pstEawim;
    CNAS_XCC_EFWIM_STRU                *pstEfwim;
    CNAS_XCC_ORDRM_STRU                 stOrdrm;

    /* ���ݲ�ͬ��Ϣ��������ͬ��CON REF */
    switch (pst1xDschDataInd->enDschMsgType)
    {
        case CAS_CNAS_1X_RX_TCH_ORDER_MSG :
            CNAS_XCC_DecodeOrderMsg(pst1xDschDataInd, &stOrdrm);
            *pucConRef = (VOS_TRUE == stOrdrm.ucConRefPresent) ? stOrdrm.ucConRef : CNAS_XCC_INVALID_CON_REF;
            break;

        case CAS_CNAS_1X_RX_TCH_EXT_ALERT_WITH_INFORMATION_MSG :
            pstEawim = (CNAS_XCC_EAWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_EAWIM_STRU));
            if (VOS_NULL_PTR == pstEawim)
            {
                *pucConRef = CNAS_XCC_INVALID_CON_REF;
                return;
            }

            (VOS_VOID)CNAS_XCC_DecodeExtendedAlertWithInformationMsg(pst1xDschDataInd, pstEawim);

            *pucConRef = (VOS_TRUE == pstEawim->ucConRefPresent) ? pstEawim->ucConRef : CNAS_XCC_INVALID_CON_REF;

            PS_MEM_FREE(UEPS_PID_XCC, pstEawim);
            break;

        case CAS_CNAS_1X_RX_TCH_EXT_FLASH_WITH_INFORMATION_MSG :
            pstEfwim = (CNAS_XCC_EFWIM_STRU *)PS_MEM_ALLOC(UEPS_PID_XCC, sizeof(CNAS_XCC_EFWIM_STRU));
            if (VOS_NULL_PTR == pstEfwim)
            {
                *pucConRef = CNAS_XCC_INVALID_CON_REF;
                return;
            }

            (VOS_VOID)CNAS_XCC_DecodeExtendedFlashWithInformationMsg(pst1xDschDataInd, pstEfwim);

            *pucConRef = (VOS_TRUE == pstEfwim->ucConRefPresent) ? pstEfwim->ucConRef : CNAS_XCC_INVALID_CON_REF;;

            PS_MEM_FREE(UEPS_PID_XCC, pstEfwim);

            break;

        default:
            *pucConRef = CNAS_XCC_INVALID_CON_REF;
            break;
    }

    return;
}



/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceOf1xEstCnf
 ��������  : ��ȡ��ϢID_CAS_CNAS_1X_EST_CNF�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOf1xEstCnf(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    CAS_CNAS_1X_EST_CNF_STRU           *pst1xEstCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pst1xEstCnf = (CAS_CNAS_1X_EST_CNF_STRU *)pstMsg;

    /* ��ȡID_CAS_CNAS_1X_EST_CNF��Ϣ��Ҫ�����call instance */
    ucIndex = 0;
    if (VOS_TRUE == CNAS_XCC_GetCallInstanceIndexByConnId(pst1xEstCnf->ucConnectId, &ucIndex))
    {
        pstCallInstanceList->ucInstanceNum  = 1;
        pstCallInstanceList->aucInstance[0] = ucIndex;

        if ( CAS_CNAS_1X_EST_RSLT_SUCCESS != pst1xEstCnf->enEstRslt )
        {
            CNAS_XCC_ClearSpecificedOrigCallOrderIndex(ucIndex);
        }
    }
    else
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC,
                          "CNAS_XCC_GetCallInstanceOf1xEstCnf: ucConnectId is not found!",
                          pst1xEstCnf->ucConnectId);

        pstCallInstanceList->ucInstanceNum  = 0;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceOf1xDschDataCnf
 ��������  : ��ȡ��ϢID_CAS_CNAS_1X_DSCH_DATA_CNF�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��


 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOf1xDschDataCnf(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    /* ����ϢΪL2 ACK��Ϣ�������м����call instance״̬�������ɸ�����ʵ���Լ�check
     * ��Ϣ�е����кţ�ȷ���Ƿ���Ҫ����
     */
    CNAS_XCC_GetAllActiveCallInstanceIndex(pstCallInstanceList);
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceOf1xDschDataInd
 ��������  : ��ȡ��ϢID_CAS_CNAS_1X_DSCH_DATA_IND�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOf1xDschDataInd(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    CAS_CNAS_1X_DSCH_DATA_IND_STRU     *pst1xDschDataInd = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucConRef;

    pst1xDschDataInd = (CAS_CNAS_1X_DSCH_DATA_IND_STRU *)pstMsg;

    CNAS_XCC_GetConRefFromDschDataInd(pst1xDschDataInd, &ucConRef);

    /* ��ȡID_CAS_CNAS_1X_DSCH_DATA_IND��Ϣ��Ҫ�����call instance */
    ucIndex = 0;
    if (VOS_TRUE == CNAS_XCC_GetCallInstanceIndexByCallRef(ucConRef,
                                                           &ucIndex))
    {
        pstCallInstanceList->ucInstanceNum  = 1;
        pstCallInstanceList->aucInstance[0] = ucIndex;
    }
    else
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC, "CNAS_XCC_GetCallInstanceOf1xDschDataCnf: ucConRef is not found!",
                          ucConRef);

        pstCallInstanceList->ucInstanceNum  = 0;
    }

}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceOf1xPagingInd
 ��������  : ��ȡ��ϢID_CAS_CNAS_1X_PAGING_IND�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOf1xPagingInd(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           uc1XCallExistCount;

    uc1XCallExistCount                  = CNAS_CCB_Get1XCallExistCount();

    /* ����ID_CAS_CNAS_1X_PAGING_IND��Ϣ��Ҫ�����call instance */
    ucIndex = 0;

    if (VOS_TRUE == CNAS_XCC_AllocConnectedId(&ucIndex))
    {
        pstCallInstanceList->ucInstanceNum  = 1;
        pstCallInstanceList->aucInstance[0] = ucIndex;

        uc1XCallExistCount++;

        if (uc1XCallExistCount > CNAS_XCC_MAX_FSM_ENTITY_NUM)
        {
            CNAS_WARNING_LOG(UEPS_PID_XCC,
                             "CNAS_XCC_GetCallInstanceOf1xPagingInd: Current exist 1X Call Num beyond the MAX XCC FSM Entity Num!");
        }

        CNAS_CCB_Set1XCallExistCount(uc1XCallExistCount);
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceOf1xResetWfoSubStateTimerInd
 ��������  : ��ȡ��ϢID_CAS_CNAS_1X_RESET_WFO_SUBSTATE_TIMER_IND�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��


 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOf1xResetWfoSubStateTimerInd(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    /* ��ȡID_CAS_CNAS_1X_RESET_WFO_SUBSTATE_TIMER_IND��Ϣ��Ҫ�����call instance */
    CNAS_XCC_GetAllActiveCallInstanceIndex(pstCallInstanceList);

    CNAS_INFO_LOG1(UEPS_PID_XCC,
                   "CNAS_XCC_GetCallInstanceOf1xResetWfoSubStateTimerInd",
                   pstCallInstanceList->ucInstanceNum);
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstOf1xUpdateCallInfoInd
 ��������  : ��ȡ��ϢID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOf1xUpdateCallInfoInd(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    CAS_CNAS_1X_UPDATE_CALL_INFO_IND_STRU                  *pst1xUpdateCallInfoInd = VOS_NULL_PTR;
    VOS_UINT8                                               ucIndex;

    pst1xUpdateCallInfoInd = (CAS_CNAS_1X_UPDATE_CALL_INFO_IND_STRU *)pstMsg;

    /* ��ȡID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND��Ϣ��Ҫ�����call instance */
    ucIndex = 0;
    if (VOS_TRUE == CNAS_XCC_GetCallInstanceIndexByConnId(pst1xUpdateCallInfoInd->ucConnectId, &ucIndex))
    {
        pstCallInstanceList->ucInstanceNum  = 1;
        pstCallInstanceList->aucInstance[0] = ucIndex;
    }
    else
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC,
                          "CNAS_XCC_GetCallInstanceOf1xUpdateCallInfoInd: ucConnectId is not found!",
                          pst1xUpdateCallInfoInd->ucConnectId);

        pstCallInstanceList->ucInstanceNum  = 0;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceOf1xCallInitInd
 ��������  : ��ȡ��ϢID_CAS_CNAS_1X_CALL_INIT_IND�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOf1xCallInitInd(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    CAS_CNAS_1X_CALL_INIT_IND_STRU     *pst1xCallInitInd = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pst1xCallInitInd = (CAS_CNAS_1X_CALL_INIT_IND_STRU *)pstMsg;

    /* ��ȡID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND��Ϣ��Ҫ�����call instance */
    ucIndex = 0;
    if (VOS_TRUE == CNAS_XCC_GetCallInstanceIndexByConnId(pst1xCallInitInd->ucConnectId, &ucIndex))
    {
        pstCallInstanceList->ucInstanceNum  = 1;
        pstCallInstanceList->aucInstance[0] = ucIndex;
    }
    else
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC,
                          "CNAS_XCC_GetCallInstanceOf1xCallInitInd: ucConnectId is not found!",
                          pst1xCallInitInd->ucConnectId);

        pstCallInstanceList->ucInstanceNum  = 0;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstOf1xCallRelInd
 ��������  : ��ȡ��ϢID_CAS_CNAS_1X_CALL_REL_IND�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOf1xCallRelInd(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    CAS_CNAS_1X_CALL_REL_IND_STRU      *pst1xCallRelInd = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pst1xCallRelInd = (CAS_CNAS_1X_CALL_REL_IND_STRU *)pstMsg;

    /* ��ȡID_CAS_CNAS_1X_CALL_REL_IND��Ϣ��Ҫ�����call instance */
    ucIndex = 0;

    if (VOS_TRUE == CNAS_XCC_GetCallInstanceIndexByConnId(pst1xCallRelInd->ucConnectId,
                                                           &ucIndex))
    {
        pstCallInstanceList->ucInstanceNum  = 1;
        pstCallInstanceList->aucInstance[0] = ucIndex;
    }
    else
    {
        CNAS_WARNING_LOG2(UEPS_PID_XCC, "CNAS_XCC_GetCallInstanceOf1xCallRelInd: ucConRef is not found!",
                          VOS_TRUE,
                          pst1xCallRelInd->ucConRef);

        pstCallInstanceList->ucInstanceNum  = 0;
    }
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceOf1xCallTerminateInd
 ��������  : ��ȡ��ϢID_CAS_CNAS_1X_CALL_TERMINATE_IND�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOf1xCallTerminateInd(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    CAS_CNAS_1X_CALL_TERMINATE_IND_STRU                    *pst1xCallTerminateInd = VOS_NULL_PTR;
    CNAS_XCC_CTX_STRU                                      *pstXccCtxAddr = VOS_NULL_PTR;
    VOS_UINT8                                               i;
    VOS_UINT8                                               j;

    pst1xCallTerminateInd = (CAS_CNAS_1X_CALL_TERMINATE_IND_STRU *)pstMsg;

    /* ��ȡID_CAS_CNAS_1X_CALL_TERMINATE_IND��Ϣ��Ҫ�����call instance */
    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    pstCallInstanceList->ucInstanceNum = 0;

    for (i = 0, j = 0; i < CNAS_XCC_MAX_FSM_ENTITY_NUM; i++)
    {
        if (VOS_TRUE == pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.ucIsEntityActive)
        {
            if (PS_TRUE == pst1xCallTerminateInd->enTerminateAll)
            {
                pstCallInstanceList->ucInstanceNum++;
                pstCallInstanceList->aucInstance[j] = i;
                j++;
                CNAS_XCC_ClearSpecificedOrigCallOrderIndex(i);
            }
            else
            {
                if (pst1xCallTerminateInd->ucConnectId == pstXccCtxAddr->astFsmEntity[i].stCallInfoCtx.ucConnectId)
                {
                    pstCallInstanceList->ucInstanceNum++;
                    pstCallInstanceList->aucInstance[j] = i;
                    j++;
                    CNAS_XCC_ClearSpecificedOrigCallOrderIndex(i);
                }
            }
        }
    }

}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceOfOrigCallReq
 ��������  : ��ȡ��ϢID_XCALL_XCC_ORIG_CALL_REQ�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��


 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��1��3��
    ��    ��   : y00245242
    �޸�����   : NDSS ORIG���ܿ���

  3.��    ��   : 2015��7��20��
    ��    ��   : h00313353
    �޸�����   : ����17 ������

  4.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity
*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOfOrigCallReq(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           uc1XCallExistCount;

    uc1XCallExistCount                  = CNAS_CCB_Get1XCallExistCount();

    /* ����ID_XCALL_XCC_ORIG_CALL_REQ��Ϣ��Ҫ�����call instance */
    ucIndex = 0;

    if (VOS_TRUE == CNAS_XCC_AllocConnectedId(&ucIndex))
    {
        pstCallInstanceList->ucInstanceNum  = 1;
        pstCallInstanceList->aucInstance[0] = ucIndex;

        /* ˢ�µ�ǰ��������Ϊ���ĺ������� */
        CNAS_XCC_SetOrigCallOrderIndex(ucIndex);

        uc1XCallExistCount++;

        if (uc1XCallExistCount > CNAS_XCC_MAX_FSM_ENTITY_NUM)
        {
            CNAS_WARNING_LOG(UEPS_PID_XCC,
                             "CNAS_XCC_GetCallInstanceOfOrigCallReq: Current exist 1X Call Num beyond the MAX XCC FSM Entity Num!");
        }

        CNAS_CCB_Set1XCallExistCount(uc1XCallExistCount);
    }
    else
    {
        pstCallInstanceList->ucInstanceNum  = 0;

        CNAS_ERROR_LOG(UEPS_PID_XCC,
                       "CNAS_XCC_GetCallInstanceOfXccOrigReq: XCC is abnormal!");
    }
}

/* Delete If 0 */

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceOfXccSendBurstDtmfReq
 ��������  : ��ȡ��ϢID_XCALL_XCC_BURST_DTMF_REQ�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��11��17��
    ��    ��   : f279542
    �޸�����   : 1X SS Project�޸�
*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOfXccSendBurstDtmfReq(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    VOS_UINT8                           ucIndex;
    XCALL_XCC_BURST_DTMF_REQ_STRU      *pstXcallBurstDTMFReq = VOS_NULL_PTR;

    pstXcallBurstDTMFReq  = (XCALL_XCC_BURST_DTMF_REQ_STRU *)pstMsg;

    if (VOS_TRUE == CNAS_XCC_GetCallInstanceIndexByCallId(pstXcallBurstDTMFReq->ucCallId, &ucIndex))
    {
        pstCallInstanceList->ucInstanceNum  = 1;
        pstCallInstanceList->aucInstance[0] = ucIndex;
    }
    else
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC,
                         "CNAS_XCC_GetCallInstanceOfXccSendBurstDtmfReq: no voice call instance is found!");

        pstCallInstanceList->ucInstanceNum  = 0;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceOfXccSendFlashReq
 ��������  : ��ȡ��ϢXCALL_XCC_SEND_FLASH_REQ_STRU�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��


 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOfXccSendFlashReq(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;
    VOS_UINT8                           ucIndex;

    pstMsgHeader  = (MSG_HEADER_STRU *)pstMsg;

    enServiceType = CNAS_XCC_GetServiceTypeAccordingMsgId(pstMsgHeader->ulMsgName);

    ucIndex = 0;

    if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(enServiceType, &ucIndex))
    {
        pstCallInstanceList->ucInstanceNum  = 1;
        pstCallInstanceList->aucInstance[0] = ucIndex;
    }
    else
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC,
                         "CNAS_XCC_GetCallInstanceOfXccSendFlashReq: no voice call instance is found!");

        pstCallInstanceList->ucInstanceNum  = 0;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetServiceTypeAccordingMsgId
 ��������  : ��ȡXCC��Ϣ�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��


 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_XCC_SERVICE_TYPE_ENUM_UINT32 CNAS_XCC_GetServiceTypeAccordingMsgId(
    VOS_UINT32                          ulMsgName
)
{
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32 enServiceType;

    switch (ulMsgName)
    {
        case ID_XCALL_XCC_HANGUP_CALL_REQ :
        case ID_XCALL_XCC_INCOMING_CALL_RSP :
        case ID_XCALL_XCC_ANSWER_CALL_REQ :
        case ID_XCALL_XCC_SEND_BURST_DTMF_REQ :
        case ID_XCALL_XCC_SEND_FLASH_REQ :
            enServiceType = CNAS_XCC_SERVICE_TYPE_VOICE_CALL;
            break;

        case ID_APS_XCC_HANGUP_DATA_CALL_REQ :
        case ID_APS_XCC_INCOMING_CALL_RSP :
        case ID_APS_XCC_ANSWER_DATA_CALL_REQ :
            enServiceType = CNAS_XCC_SERVICE_TYPE_DATA_CALL;
            break;

        case ID_CSMS_XCC_END_SMS_CALL_REQ :
        case ID_CSMS_XCC_INCOMING_CALL_RSP :
        case ID_CSMS_XCC_ANSWER_CALL_REQ :
            enServiceType = CNAS_XCC_SERVICE_TYPE_SMS;
            break;

        case ID_XPDS_XCC_END_AGPS_CALL_REQ :
        case ID_XPDS_XCC_INCOMING_CALL_RSP :
        case ID_XPDS_XCC_ANSWER_CALL_REQ :
            enServiceType = CNAS_XCC_SERVICE_TYPE_AGPS_CALL;
            break;

        default:
            enServiceType = CNAS_XCC_SERVICE_TYPE_BUTT;
            break;
    }

    return enServiceType;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceOfOtherMsg
 ��������  : ��ȡXCC��Ϣ�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��


 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOfOtherMsg(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    CNAS_XCC_SERVICE_TYPE_ENUM_UINT32   enServiceType;
    VOS_UINT8                           ucIndex;

    pstMsgHeader  = (MSG_HEADER_STRU *)pstMsg;

    enServiceType = CNAS_XCC_GetServiceTypeAccordingMsgId(pstMsgHeader->ulMsgName);

    ucIndex = 0;

    if (VOS_TRUE == CNAS_XCC_GetSpecTypeInstance(enServiceType, &ucIndex))
    {
        pstCallInstanceList->ucInstanceNum  = 1;
        pstCallInstanceList->aucInstance[0] = ucIndex;
    }
    else
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC,
                         "CNAS_XCC_GetCallInstanceOfOtherMsg: no voice call instance is found!");

        pstCallInstanceList->ucInstanceNum  = 0;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceOfApsDataCallSuspendRsp
 ��������  : ��ȡXSD��ϢID_APS_XCC_DATA_CALL_SUSPEND_RSP��call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��


 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOfApsDataCallSuspendRsp(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    VOS_UINT8                           ucIndex;
    APS_XCC_DATA_CALL_SUSPEND_RSP_STRU *pstApsSuspendReq = VOS_NULL_PTR;

    /* ����ID_APS_XCC_DATA_CALL_SUSPEND_RSP��Ϣ��Ҫ�����call instance */
    pstApsSuspendReq = (APS_XCC_DATA_CALL_SUSPEND_RSP_STRU *)pstMsg;

    /* ��ȡID_CAS_CNAS_1X_UPDATE_CALL_INFO_IND��Ϣ��Ҫ�����call instance */
    ucIndex = 0;
    if (VOS_TRUE == CNAS_XCC_GetCallInstanceIndexByConnId(pstApsSuspendReq->ucConnectId, &ucIndex))
    {
        pstCallInstanceList->ucInstanceNum  = 1;
        pstCallInstanceList->aucInstance[0] = ucIndex;
    }
    else
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC,
                         "CNAS_XCC_GetCallInstanceOfApsDataCallSuspendRsp: no voice call instance is found!");

        pstCallInstanceList->ucInstanceNum  = 0;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceOfTimerMsg
 ��������  : ��ȡTimer��Ϣ�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��


 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOfTimerMsg(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    VOS_UINT8                           ucIndex;
    REL_TIMER_MSG                      *pstTimerMsg = VOS_NULL_PTR;

    /* ��ȡtimer��Ϣ��Ҫ�����call instance */
    pstTimerMsg = (REL_TIMER_MSG *)pstMsg;

    ucIndex     = 0;

    if (VOS_TRUE == CNAS_XCC_GetCallInstanceIndexByConnId((VOS_UINT8)pstTimerMsg->ulPara, &ucIndex))
    {
        pstCallInstanceList->ucInstanceNum  = 1;
        pstCallInstanceList->aucInstance[0] = ucIndex;

        CNAS_XCC_ClearSpecificedOrigCallOrderIndex(ucIndex);
    }
    else
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC,
                         "CNAS_XCC_GetCallInstanceOfTimerMsg: ucConnectId is not found!",
                         pstTimerMsg->ulPara);

        pstCallInstanceList->ucInstanceNum  = 0;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceOfXccMoCalingRlstCnf
 ��������  : ��ȡ�ڲ���ϢID_CNAS_XCC_XCC_MO_CALLING_RSLT_CNF�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��


 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOfXccMoCalingRlstCnf(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    VOS_UINT8                                               ucIndex;
    CNAS_XCC_XCC_MO_CALLING_RSLT_CNF_STRU                  *pstXccMoCallingRsltCnf = VOS_NULL_PTR;

    /* ��ȡID_CNAS_XCC_XCC_MO_CALLING_RSLT_CNF��Ϣ��Ҫ�����call instance */
    pstXccMoCallingRsltCnf = (CNAS_XCC_XCC_MO_CALLING_RSLT_CNF_STRU *)pstMsg;

    ucIndex     = 0;

    if (VOS_TRUE == CNAS_XCC_GetCallInstanceIndexByConnId(pstXccMoCallingRsltCnf->ucConnectId, &ucIndex))
    {
        pstCallInstanceList->ucInstanceNum  = 1;
        pstCallInstanceList->aucInstance[0] = ucIndex;
    }
    else
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC,
                         "CNAS_XCC_GetCallInstanceOfXccMoCalingRlstCnf: ucConnectId is not found!",
                         pstXccMoCallingRsltCnf->ucConnectId);

        pstCallInstanceList->ucInstanceNum  = 0;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceOfXccMtCalingRlstCnf
 ��������  : ��ȡ�ڲ���ϢID_CNAS_XCC_XCC_MT_CALLING_RSLT_CNF�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��


 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOfXccMtCalingRlstCnf(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    VOS_UINT8                                               ucIndex;
    CNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU                  *pstXccMtCallingRsltCnf = VOS_NULL_PTR;

    /* ��ȡID_CNAS_XCC_XCC_MO_CALLING_RSLT_CNF��Ϣ��Ҫ�����call instance */
    pstXccMtCallingRsltCnf = (CNAS_XCC_XCC_MT_CALLING_RSLT_CNF_STRU *)pstMsg;

    ucIndex     = 0;

    if (VOS_TRUE == CNAS_XCC_GetCallInstanceIndexByConnId(pstXccMtCallingRsltCnf->ucConnectId, &ucIndex))
    {
        pstCallInstanceList->ucInstanceNum  = 1;
        pstCallInstanceList->aucInstance[0] = ucIndex;
    }
    else
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC,
                         "CNAS_XCC_GetCallInstanceOfXccMtCalingRlstCnf: ucConnectId is not found!",
                         pstXccMtCallingRsltCnf->ucConnectId);

        pstCallInstanceList->ucInstanceNum  = 0;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceOfXccAbortReq
 ��������  : ��ȡ�ڲ���ϢID_CNAS_XCC_XCC_ABORT_REQ�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��


 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOfXccAbortReq(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    VOS_UINT8                           ucIndex;
    CNAS_XCC_XCC_ABORT_REQ_STRU        *pstXccAbortReq = VOS_NULL_PTR;

    /* ��ȡID_CNAS_XCC_XCC_ABORT_REQ��Ϣ��Ҫ�����call instance */
    pstXccAbortReq = (CNAS_XCC_XCC_ABORT_REQ_STRU *)pstMsg;

    if (VOS_TRUE == CNAS_XCC_GetCallInstanceIndexByConnId(pstXccAbortReq->ucConnectId, &ucIndex))
    {
        pstCallInstanceList->ucInstanceNum  = 1;
        pstCallInstanceList->aucInstance[0] = ucIndex;
    }
    else
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC,
                         "CNAS_XCC_GetCallInstanceOfXccAbortReq: ucConnectId is not found!",
                         pstXccAbortReq->ucConnectId);

        pstCallInstanceList->ucInstanceNum  = 0;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceOfXccPowerDownReq
 ��������  : ��ȡ�ڲ���ϢID_CNAS_XCC_XCC_POWER_DOWN_IND�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��


 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOfXccPowerDownReq(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    VOS_UINT8                           ucIndex;
    CNAS_XCC_XCC_POWER_DOWN_IND_STRU   *pstXccPowerDownInd = VOS_NULL_PTR;

    /* ��ȡID_CNAS_XCC_XCC_POWER_DOWN_IND��Ϣ��Ҫ�����call instance */
    pstXccPowerDownInd = (CNAS_XCC_XCC_POWER_DOWN_IND_STRU *)pstMsg;

    ucIndex     = 0;

    if (VOS_TRUE == CNAS_XCC_GetCallInstanceIndexByConnId(pstXccPowerDownInd->ucConnectId, &ucIndex))
    {
        pstCallInstanceList->ucInstanceNum  = 1;
        pstCallInstanceList->aucInstance[0] = ucIndex;
    }
    else
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC,
                         "CNAS_XCC_GetCallInstanceOfXccPowerDownReq: ucConnectId is not found!",
                         pstXccPowerDownInd->ucConnectId);

        pstCallInstanceList->ucInstanceNum  = 0;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceOfXccNdssRedialInd
 ��������  : ��ȡ�ڲ���ϢID_CNAS_XCC_XCC_NDSS_REDIAL_IND�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��


 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOfXccNdssRedialInd(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    VOS_UINT8                           ucIndex;
    CNAS_XCC_XCC_NDSS_REDIAL_IND_STRU  *pstXccNdssRedialInd = VOS_NULL_PTR;

    /* ��ȡID_CNAS_XCC_XCC_NDSS_REDIAL_IND��Ϣ��Ҫ�����call instance */
    pstXccNdssRedialInd = (CNAS_XCC_XCC_NDSS_REDIAL_IND_STRU *)pstMsg;

    if (VOS_TRUE == CNAS_XCC_GetCallInstanceIndexByConnId(pstXccNdssRedialInd->ucConnectId, &ucIndex))
    {
        pstCallInstanceList->ucInstanceNum  = 1;
        pstCallInstanceList->aucInstance[0] = ucIndex;
    }
    else
    {
        CNAS_WARNING_LOG1(UEPS_PID_XCC,
                         "CNAS_XCC_GetCallInstanceOfXccNdssRedialInd: ucConnectId is not found!",
                         pstXccNdssRedialInd->ucConnectId);

        pstCallInstanceList->ucInstanceNum  = 0;
    }
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceEntity
 ��������  : ���Ҵ�����Ϣ�ĺ��п���instance
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : pstCallInstanceFsmList -- ������Ҫ����call control instance�б�
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��06��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceEntity(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_XCC_FSM_ENTITY_LIST_STRU      *pstFsmEntityList
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucIndex;
    CNAS_XCC_CALL_INSTANCE_LIST_STRU    stCallInstanceList;
    CNAS_XCC_CTX_STRU                  *pstXccCtxAddr = VOS_NULL_PTR;


    NAS_MEM_SET_S(&stCallInstanceList, sizeof(CNAS_XCC_CALL_INSTANCE_LIST_STRU), 0, sizeof(CNAS_XCC_CALL_INSTANCE_LIST_STRU));

    for (i = 0; i < (sizeof(g_astCnasXccGetCallInstanceMsgTbl)/sizeof(CNAS_XCC_GET_CALL_INSTANCE_STRU)); i++)
    {
        if (g_astCnasXccGetCallInstanceMsgTbl[i].ulMsgEvtType == ulEventType)
        {
            g_astCnasXccGetCallInstanceMsgTbl[i].pfGetCallInstanceFun(pstMsg, &stCallInstanceList);
            break;
        }
    }


    pstXccCtxAddr = CNAS_XCC_GetCtxAddr();

    pstFsmEntityList->ucFsmNum = CNAS_MIN(stCallInstanceList.ucInstanceNum, CNAS_XCC_MAX_FSM_ENTITY_NUM);

    /* ����call control instanceʵ�����б� */
    for (i = 0; i < pstFsmEntityList->ucFsmNum; i++)
    {
        ucIndex = stCallInstanceList.aucInstance[i];

        pstFsmEntityList->pstFsmEntity[i] = &(pstXccCtxAddr->astFsmEntity[ucIndex]);
    }
}


/*****************************************************************************
 �� �� ��  : CNAS_XCC_GetCallInstanceOfXccSendContDtmfReq
 ��������  : ��ȡ��ϢXCALL_XCC_SEND_CONT_DTMF_REQ_STRU�����call instance
 �������  : pstMsg          -- ��Ϣָ��
 �������  : pstCallInstList -- ����call instance�б�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��25
    ��    ��   : l00324781
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_GetCallInstanceOfXccSendContDtmfReq(
    struct MsgCB                       *pstMsg,
    CNAS_XCC_CALL_INSTANCE_LIST_STRU   *pstCallInstanceList
)
{
    VOS_UINT8                           ucIndex;
    XCALL_XCC_SEND_CONT_DTMF_REQ_STRU  *pstXcallContDTMFReq = VOS_NULL_PTR;

    pstXcallContDTMFReq  = (XCALL_XCC_SEND_CONT_DTMF_REQ_STRU *)pstMsg;

    if (VOS_TRUE == CNAS_XCC_GetCallInstanceIndexByCallId(pstXcallContDTMFReq->ucCallId, &ucIndex))
    {
        pstCallInstanceList->ucInstanceNum  = 1;
        pstCallInstanceList->aucInstance[0] = ucIndex;
    }
    else
    {
        CNAS_WARNING_LOG(UEPS_PID_XCC,
                         "CNAS_XCC_GetCallInstanceOfXccSendContDtmfReq: no voice call instance is found!");

        pstCallInstanceList->ucInstanceNum  = 0;
    }

    return;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



