/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnCallReqProc.c
  �� �� ��   : ����
  ��    ��   : ���� 49431
  ��������   : 2007��9��20��
  ����޸�   : 2007��9��20��
  ��������   : ��������APP���첽������Ϣ
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ļ�
  2.��    ��   : 2008��06��11��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:AT2D03709

  3.��    ��   : 2010��3��2��
    ��    ��   : zhoujun /z40661
    �޸�����   : NAS R7Э������
  4.��    ��   : 2010��5��14��
    ��    ��   : h44270
    �޸�����   : ���ⵥ�ţ�AT2D19318
******************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "TafTypeDef.h"
#include "MnCallApi.h"
#include "MnCallSendCc.h"
#include "MnCallMgmt.h"
#include "MnComm.h"
#include "MnErrorCode.h"
#include "UsimPsInterface.h"
#include "MnCallBcProc.h"
#include "NasIeUtil.h"
#include "siapppb.h"
#include "NasOmInterface.h"
#include "MnCallMnccProc.h"
#include "MmaAppLocal.h"
#include "MnCall.h"
#include "MnCallMnccProc.h"
#include "MnCallTimer.h"
#include "MnCallCtx.h"
#include "MnCallProcNvim.h"
#include "MnCallReqProc.h"

/* Modified by z00161729 for V9R1 STK����, 2013-7-24, begin */
#include "NasStkInterface.h"
/* Modified by z00161729 for V9R1 STK����, 2013-7-24, end */

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, begin */
#include "TafSdcLib.h"
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, end */

/* Added by l00167671 for NV�����Ŀ , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV�����Ŀ , 2013-05-17, end*/
#include "NasUsimmApi.h"

/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, begin */
#include "TafStdlib.h"
/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-24, end */

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-21, begin */
#include "MnCallSendApp.h"
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-21, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_REQ_PROC_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */
/* f_aucCallEmerNumsNoUsim��f_aucCallEmerNumsWithUsim��MN_CALL_MAX_ASCII_NUM_LEN
   f_stMmCallEmerNumList��g_stTafCallCustomEccNumCtx �Ƶ�SPMģ�� */
/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */

#define MN_CALL_MODE_FULL               1   /* full functionality */


/*lint -save -e958 */

/*****************************************************************************
   2 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : MN_CALL_ActCcbsReqPorc
 ��������  : �����û�ѡ�����CCBS���������,ͨ��AT����CHLD+5�·�
 �������  : clientId    - ����������Client��ID
             opId        - Operation ID, ��ʶ���β���
             ucCallId    - ���е�call ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��12��23��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_ActCcbsReqPorc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        ucCallId
)
{
    MN_CALL_SendCcActCcbsReq(ucCallId);

    /* ��עCCBS����ɹ��¼�, ��������Ϊ�ϱ������ɹ� */
    MN_CALL_RegSsKeyEvent(ucCallId,
                          MN_CALL_SS_PROG_EVT_ACT_CCBS_CNF,
                          MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

    /*��עCCBS����ʧ���¼�����������Ϊ�ϱ�����ʧ��*/
    MN_CALL_RegSsKeyEvent(ucCallId,
                          MN_CALL_SS_PROG_EVT_ACT_CCBS_REJ,
                          MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

    MN_CALL_BeginCallSupsCmdProgress(clientId, MN_CALL_SUPS_CMD_ACT_CCBS);

    MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_SUCCESS);

}

/*****************************************************************************
 �� �� ��  : MN_CALL_RecallCcbsReqPorc
 ��������  : �����û�ѡ�����CCBS�غ�������,ͨ��AT����CHLD+5�·�
 �������  : clientId    - ����������Client��ID
             opId        - Operation ID, ��ʶ���β���
             ucCallId    - ���е�call ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��12��23��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  3.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  4.��    ��   : 2013��01��29��
    ��    ��   : Y00213812
    �޸�����   : DTS2013012909872,��¼CALL�Ҷϵķ���
  5.��    ��   : 2014��4��15��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature�޸�
*****************************************************************************/
LOCAL VOS_VOID  MN_CALL_RecallCcbsReqPorc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        ucCallId
)
{
    VOS_UINT32                          ulRslt = MN_ERR_NO_ERROR;
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];


    /*�����Ƿ�������ͨ���ĺ��У�����У����ܷ���SETUP��Ϣ*/
    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aCallIds);
    if (0 == ulNumOfCalls)
    {
        ulRslt = MN_CALL_SendCcbsSetupReq(ucCallId);
        /* ��Ϣ����ʧ�ܣ���������������ʵ�� */
        if ( VOS_OK != ulRslt)
        {
            MN_CALL_FreeCallId(ucCallId);

            MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_UNKNOWN);

            return;
        }

        MN_CALL_UpdateClientId(ucCallId,clientId);
        MN_CALL_UpdateRecallSupsProgress(ucCallId,
                                         MN_CALL_ERR_SS_UNSPECIFIC,
                                         MN_CALL_SS_RES_SUCCESS);

        MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_SUCCESS);

        MN_CALL_UpdateCcCallDir(ucCallId, MN_CALL_DIR_MO);
        MN_CALL_UpdateCallState(ucCallId, MN_CALL_S_DIALING);

        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */
        /* ���֧�ֺ����ؽ����ܣ�������MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD��ʱ�� */
        if (VOS_TRUE == TAF_CALL_GetRedialSupportFlg(ucCallId))
        {
            TAF_CALL_StartRedialPeriodTimer(ucCallId);
        }
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-8, end */

        MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_ORIG);
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MO_ATTEMPT,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);
     }
     else
     {
        /*����û�ѡ�����CCBS�غ����򷵻�ʧ��,��ǰ���ں��в��ܽ��лغ�*/
        MN_CALL_UpdateClientId(ucCallId, clientId);


        /*�Ҷ�ָ���ĺ���*/
        (VOS_VOID)MN_CALL_SendCcDiscReq(ucCallId, MN_CALL_USER_BUSY);

        /* ��¼�����Ҷϵ�ԭ��ֵ */
        MN_CALL_UpdateCcCause(ucCallId, MN_CALL_USER_BUSY);

        /* ��¼���йҶϵķ��� */
        MN_CALL_UpdateDiscCallDir(ucCallId, VOS_TRUE);

        /* ��ע�ú��еĹҶ�����¼�, ��������Ϊ�ϱ������ɹ� */
        MN_CALL_RegSsKeyEvent(ucCallId,
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);


        /*����ҵ�������ʼ����*/
        MN_CALL_BeginCallSupsCmdProgress(clientId, MN_CALL_SUPS_CMD_ACT_CCBS);

        MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_STATE_ERROR);
     }

}

/*****************************************************************************
 �� �� ��  : MN_CALL_SupsCmdCcbsReqProc
 ��������  : ��������Ӧ�ò��CCBS�����CCBS�غ���������
 �������  : clientId           - ����������Client��ID
             opId               - Operation ID, ��ʶ���β���
             pstCallSupsParam   - ����ҵ���������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��12��23��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����

  3.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_SupsCmdCcbsReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    /*�û�����CCBS��������CCBS�غ�����Ϊ����AT����:CHLD+5*/
    MN_CALL_GetCallsByState(MN_CALL_S_CCBS_WAITING_ACTIVE,&ulNumOfCalls,aCallIds);
    if (0 != ulNumOfCalls)
    {
        MN_CALL_ActCcbsReqPorc(clientId, opId, aCallIds[0]);
        return;
    }
    MN_CALL_GetCallsByState(MN_CALL_S_CCBS_WAITING_RECALL,&ulNumOfCalls,aCallIds);
    if (0 != ulNumOfCalls)
    {
        MN_CALL_RecallCcbsReqPorc(clientId, opId, aCallIds[0]);
        return;
    }

    MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_STATE_ERROR);
}

/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */
/* MN_CALL_IsValidEmerCategory���Ƶ�SPMģ�鲢������ */
/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */

/*****************************************************************************
 �� �� ��  : MN_CALL_JudgeAllowToBuildMpty
 ��������  : �ж��Ƿ��ܹ�build Mpty
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ����build Mpty
             VOS_FALSE - ����build Mpty
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_BOOL MN_CALL_JudgeAllowToBuildMpty(VOS_VOID)
{
    VOS_UINT32                          ulNumOfMptyCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT32                          ulNumOfHoldCalls,ulNumOfActCalls;


    /* ��ȡ����active����hold״̬�ĺ��� */
    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfActCalls, aCallIds);
    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfHoldCalls, aCallIds);


    /* �ж���ǰ�Ƿ��к�������MPTY */
    MN_CALL_GetCallsByMptyState(MN_CALL_IN_MPTY, &ulNumOfMptyCalls, aCallIds);
    if (5 <= ulNumOfMptyCalls)
    {
        /* MPTY�Ѿ��������� */
        MN_WARN_LOG("MN_CALL_JudgeAllowToBuildMpty: Beyond MPTY Capability.");
        return VOS_FALSE;
    }

    if (0 == ulNumOfMptyCalls)
    {
        /* ��ǰû��MPTY,�����в�ֹһ�����ڼ������hold״̬�ĺ��� */
        if ((1 != ulNumOfActCalls) || (1 != ulNumOfHoldCalls))
        {
            MN_WARN_LOG("MN_CALL_JudgeAllowToBuildMpty: Not Only One Active or hold Call.");
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }
    else
    {
        if ((0 == ulNumOfActCalls) || (0 == ulNumOfHoldCalls))
        {
            MN_WARN_LOG("MN_CALL_JudgeAllowToBuildMpty: No Active or hold Call.");
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
�� �� ��  : MN_CALL_CallSupsCmdReqCommProc
��������  : ����ҵ��ͨ�ò���,��¼����ҵ�������ʼ����,��Ӧ�ò�������Ӧ
�������  : clientId            - ����������Client��ID
            opId                - Operation ID, ��ʶ���β���
            pstCallSupsParam    - ����ҵ���������
            ulRslt              - ��Ӧ���
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2009��12��20��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��07��09��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseI��Ŀ
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_CallSupsCmdReqCommProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam,
    VOS_UINT32                          ulRslt
)
{
    /*����ҵ�������ʼ����*/
    MN_CALL_BeginCallSupsCmdProgress(clientId, pstCallSupsParam->enCallSupsCmd);

    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, ulRslt);
    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              ulRslt);
}

/*****************************************************************************
 �� �� ��  : MN_CALL_CommRelAction
 ��������  : �ͷź���ͨ�õĲ���
 �������  : clientId           - ����������Client��ID
             opId               - Operation ID, ��ʶ���β���
             callId             - ����Call Id
             pstCallSupsParam   - ����ҵ���������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��2��
    ��    ��   : zhoujun /z40661
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  3.��    ��   : 2013��01��29��
    ��    ��   : Y00213812
    �޸�����   : DTS2013012909872,��¼CALL�Ҷϵķ���
*****************************************************************************/
VOS_VOID MN_CALL_CommRelAction(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    MN_CALL_UpdateClientId(callId, clientId);
    (VOS_VOID)MN_CALL_SendCcDiscReq(callId, MN_CALL_USER_BUSY);

    /* ��¼�����Ҷϵ�ԭ��ֵ */
    MN_CALL_UpdateCcCause(callId, MN_CALL_USER_BUSY);

    /* ��¼���йҶϵķ��� */
    MN_CALL_UpdateDiscCallDir(callId, VOS_TRUE);

    /* ��ע�ú��еĹҶ�����¼�, ��������Ϊ�ϱ������ɹ� */
    MN_CALL_RegSsKeyEvent(callId,
                          MN_CALL_SS_PROG_EVT_REL,
                          MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

    MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);
}

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
/*****************************************************************************
�� �� ��  : TAF_CALL_RelIncomingOrWaitingCall
��������  : �ͷ���������ڵȴ��ĺ���
�������  : ucCallId            - ����ID
            enCallState         - ����״̬

�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2014��4��15��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature�޸�
*****************************************************************************/
VOS_VOID TAF_CALL_RelIncomingOrWaitingCall(
    VOS_UINT8                           ucCallId,
    MN_CALL_STATE_ENUM_U8               enCallState
)
{
    (VOS_VOID)MN_CALL_SendCcDiscReq(ucCallId, MN_CALL_USER_BUSY);

    /* ��¼�����Ҷϵ�ԭ��ֵ */
    MN_CALL_UpdateCcCause(ucCallId, MN_CALL_USER_BUSY);

    /* ��¼���йҶϵķ��� */
    MN_CALL_UpdateDiscCallDir(ucCallId, VOS_TRUE);

    if ((MN_CALL_S_INCOMING == enCallState)
      ||(MN_CALL_S_WAITING == enCallState))
    {
        MN_CALL_StopTimer(MN_CALL_TID_RING);
    }
}

/*****************************************************************************
�� �� ��  : TAF_CALL_RelRedialingCall
��������  : �ͷ������ز��ĺ���
�������  : clientId         -- �û�ID
            opId             -- ����ID
            pstCallSupsParam -- ����ҵ����������ַ

�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2014��4��15��
   ��    ��   : y00245242
   �޸�����   : ΪeCall feature�޸�
 2.��    ��   : 2015��7��7��
   ��    ��   : zwx247453
   �޸�����   : CHR �Ż���Ŀ
*****************************************************************************/
VOS_VOID TAF_CALL_RelRedialingCall(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU      *pstCallSupsParam
)
{
    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg = VOS_NULL_PTR;

    pstBufferdMsg = MN_CALL_GetBufferedMsg();

#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_GetInternalHangUpFlag())
    {
        /* ��TAF�ڲ��һ�����������ȷ����Ϣ��TAF */
        TAF_CALL_SetInternalHangUpFlag(VOS_FALSE);
        TAF_CALL_SendTafRelCallCnf(clientId, opId, TAF_CS_CAUSE_SUCCESS);
    }
    else
#endif
    {
        /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
        TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_SUCCESS);
        /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

        TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                  opId,
                                                  pstCallSupsParam->callId,
                                                  TAF_CS_CAUSE_SUCCESS);
    }

    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-4, begin */
    if (VOS_TRUE == pstBufferdMsg->bitOpBufferedSetupMsg)
    {
#if (FEATURE_ON == FEATURE_ECALL)
        if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstBufferdMsg->stBufferedSetupMsg.ucCallId))
        {
            /* ֹͣT9��ʱ�� */
            MN_CALL_StopTimer(TAF_CALL_TID_T9);
        }
#endif
        TAF_CALL_StopAllRedialTimers(pstBufferdMsg->stBufferedSetupMsg.ucCallId);

        TAF_CALL_ProcBufferedRedialMessage(pstBufferdMsg, MN_CALL_NORMAL_CALL_CLEARING);
    }
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-4, end */
}
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, end */

/*****************************************************************************
�� �� ��  : TAF_CALL_AtaReportOkAsync
��������  : ATA�첽�ϱ�ok�Ĵ���
�������  : clientId           - ����������Client��ID
            opId               - Operation ID, ��ʶ���β���
            callId             - ����ID
            pstCallSupsParam   - ����ҵ���������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2014��6��23��
   ��    ��   : z00161729
   �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_CALL_AtaReportOkAsync(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_SUPS_PARAM_STRU      *pstCallSupsParam
)
{
    /* ����ú��е�call sub state ΪTAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK��ظ�ʧ��*/
    if (TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK == TAF_CALL_GetCallSubState(callId))
    {
        TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_NOT_ALLOW);

        TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                  opId,
                                                  pstCallSupsParam->callId,
                                                  TAF_CS_CAUSE_NOT_ALLOW);

        return;
    }

    /* ���ú�����״̬ΪTAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK */
    TAF_CALL_SetCallSubState(callId, TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK);

    /*�����ú��� */
    (VOS_VOID)MN_CALL_SendCcSetupRsp(callId);
    MN_CALL_StopTimer(MN_CALL_TID_RING);

    /*�ж�ҵ���ŵ��Ƿ�׼���ã����׼���þ͸�VC���ʹ�����������*/
    if(VOS_TRUE == MN_CALL_GetTchStatus())
    {
        if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
        {
            /* ������Ϣ֪ͨVC������ͨ�� */
            MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);

            /* ������Ϣ֪ͨAT����ͨ��״̬ */
            MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);
        }
        MN_CALL_SetChannelOpenFlg(VOS_TRUE);
    }

    /* ���¸ú��е�Client��Ϣ */
    MN_CALL_UpdateClientId(callId, clientId);

    TAF_CALL_SendSupsCmdCnf(clientId, opId, callId, TAF_CS_CAUSE_SUCCESS);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              callId,
                                              TAF_CS_CAUSE_SUCCESS);

    return;
}

/*****************************************************************************
�� �� ��  : MN_CALL_CallSupsCmdRelHoldOrUdubReqProc
��������  : �ͷ����б����ֵĺ��л��߰ѵȴ��ĺ�������ΪUser Determined User Busy
�������  : clientId            - ����������Client��ID
            opId                - Operation ID, ��ʶ���β���
            pstCallSupsParam    - ����ҵ���������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
  1.��    ��   : 2009��12��20��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��7��30��
    ��    ��   : h44270
    �޸�����   : ���ⵥ��:DTS2010072901109�������Զ�������ͨ���е绰��Ϊ����״̬

  3.��    ��   : 2010��8��21��
    ��    ��   : zhoujun /40661
    �޸�����   : DTS2010081702497,ͨ��MODEM������У�ͨ��AT�ڷ�����б���,
                 û��AT������ʾ���

  4.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ

  5.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����

  6.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�

  7.��    ��   : 2013��01��29��
    ��    ��   : Y00213812
    �޸�����   : DTS2013012909872,��¼CALL�Ҷϵķ���
  8.��    ��   : 2013��07��09��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ

  9.��    ��   : 2013��12��28��
    ��    ��   : j00174725
    �޸�����   : HSUART PHASE III

 10.��    ��   : 2014��4��15��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature�޸�
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_CallSupsCmdRelHoldOrUdubReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           i;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    /* �����ڵȴ��ĺ���, �Ҷϸú���(ԭ��ΪUser busy) */
    MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        MN_CALL_CommRelAction(clientId,opId,aCallIds[0],pstCallSupsParam);
        MN_CALL_StopTimer(MN_CALL_TID_RING);
        return;
    }

    /* Incoming״̬��Ҳ��ȴ��ĺ���, ���ԹҶϸú���(ԭ��ΪUser busy) */
    MN_CALL_GetCallsByState(MN_CALL_S_INCOMING, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        MN_CALL_CommRelAction(clientId,opId,aCallIds[0],pstCallSupsParam);
        MN_CALL_StopTimer(MN_CALL_TID_RING);
        return;
    }

    /* �б����ֵĺ���,�Ҷ����б����ֵĺ��� */
    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfCalls, aCallIds);
    if (0 < ulNumOfCalls)
    {
        /* �Ҷ����б����ֵĺ��� */
        for (i = 0; i < ulNumOfCalls; i++)
        {
            /*��������к��е�ClientId*/
            MN_CALL_UpdateClientId(aCallIds[i], clientId);
            (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* ��¼�����Ҷϵ�ԭ��ֵ */
            MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* ��¼���йҶϵķ��� */
            MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

            /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-30, begin */
#if (FEATURE_ON == FEATURE_ECALL)
            if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
            {
                /* ���"�ȴ�mt eCall���б�־λ" */
                TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

                /* ����ز��������ز���ʱ�� */
                TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
            }
#endif
            /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-30, end */
        }

        /* ��ע���һ�����ҶϺ��еĹҶ�����¼�, ��������Ϊ�ϱ������ɹ� */
        MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
    {
        /* �����ڵȴ�CCBS����ĺ���, �Ҷϸú���(ԭ��ΪUser busy) */
        MN_CALL_GetCallsByState(MN_CALL_S_CCBS_WAITING_ACTIVE, &ulNumOfCalls, aCallIds);
        if (0 != ulNumOfCalls)
        {
            MN_CALL_CommRelAction(clientId,opId,aCallIds[0],pstCallSupsParam);
            return;
        }

        /* �����ڵȴ�CCBS�غ��ĺ���, �Ҷϸú���(ԭ��ΪUser busy) */
        MN_CALL_GetCallsByState(MN_CALL_S_CCBS_WAITING_RECALL, &ulNumOfCalls, aCallIds);
        if (0 != ulNumOfCalls)
        {
            MN_CALL_CommRelAction(clientId,opId,aCallIds[0],pstCallSupsParam);
            return;
        }
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    MN_WARN_LOG("MN_CALL_CallSupsCmdRelHoldOrUdubReqProc: state err REL ACT ACPT OTH");

    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);
    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;

}
/*****************************************************************************
�� �� ��  : MN_CALL_CallSupsCmdRelActAcptOthReqProc
��������  : ���������ͨ���еĺ���,�ͷ���������ͨ���еĺ���,�������������ڵȴ�
            �򱻱��ֵĺ���
�������  : clientId            - ����������Client��ID
            opId                - Operation ID, ��ʶ���β���
            pstCallSupsParam    - ����ҵ���������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
  1.��    ��   : 2009��12��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��8��21��
    ��    ��   : zhoujun /40661
    �޸�����   : DTS2010081702497,ͨ��MODEM������У�ͨ��AT�ڷ�����б���,
                 û��AT������ʾ���
  3.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����

  4.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  5.��    ��   : 2013��01��29��
    ��    ��   : Y00213812
    �޸�����   : DTS2013012909872,��¼CALL�Ҷϵķ���
  6.��    ��   : 2013��07��09��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ

  7.��    ��   : 2013��12��28��
    ��    ��   : j00174725
    �޸�����   : HSUART PHASE III

  8.��    ��   : 2014��4��15��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature�޸�
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_CallSupsCmdRelActAcptOthReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           i;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    /* ������ͨ���ĺ���,�Ҷ���������ͨ���ĺ��� */
    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* �Ҷ���������ͨ���ĺ��� */
        for (i = 0; i < ulNumOfCalls; i++)
        {
            MN_CALL_UpdateClientId(aCallIds[i], clientId);
            (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* ��¼�����Ҷϵ�ԭ��ֵ */
            MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* ��¼���йҶϵķ��� */
            MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

            /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-30, begin */
#if (FEATURE_ON == FEATURE_ECALL)
            if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
            {
                /* ���"�ȴ�mt eCall���б�־λ" */
                TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

                /* ����ز��������ز���ʱ�� */
                TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
            }
#endif
            /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-30, end */
        }

        /* ��ע���һ�����ҶϺ��еĹҶ�����¼�, ��������Ϊ������һ�� */
        MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_ACCPT_OTH);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    /* �����ڵȴ��ĺ��� */
    MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /*�����ú��� */
        (VOS_VOID)MN_CALL_SendCcSetupRsp(aCallIds[0]);
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        /* ֹͣMN_CALL_TID_RING��ʱ�� */
        MN_CALL_StopTimer(MN_CALL_TID_RING);

        /* ��ע�ú��е����ӽ�������¼�, ��������Ϊ�ϱ������ɹ� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_SETUP_COMPL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* ��ע�ú��е����ӹҶ�����¼�, ��������Ϊ�ϱ�����ʧ�� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    /* �б����ֵĺ��� */
    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* ��������ֵĺ�����MTPY,��ô�ָ�MTPY����Ȼ�ָ��ú���*/
        MN_CALL_GetCallState(aCallIds[0], &enCallState, &enMptyState);
        if (MN_CALL_IN_MPTY == enMptyState)
        {
            /*�ָ�MPTY*/
            MN_CALL_SendCcSimpleFacility(aCallIds[0],
                                         MN_CALL_SS_RETRIEVEMPTY_OPERATION);
        }
        else
        {
            /*�����ú��� */
            MN_CALL_SendCcRetrieveReq(aCallIds[0]);
        }

        /* ���µ�ǰ��client */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);
        /* ��ע�ú��еĻָ��ɹ��¼�, ��������Ϊ�ϱ������ɹ� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_RETRIEVE_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* ��ע�ú��еĻָ����ܾ��¼�, ��������Ϊ�ϱ�����ʧ�� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_RETRIEVE_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    MN_WARN_LOG("MN_CALL_CallSupsCmdRelActAcptOthReqProc: state err REL ACT ACPT OTH");

    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);
    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;

}

/*****************************************************************************
�� �� ��  : MN_CALL_CallSupsCmdRelCallXReqProc
��������  : �ͷ�ָ��������ͨ���ĺ���X
�������  : clientId            - ����������Client��ID
            opId                - Operation ID, ��ʶ���β���
            pstCallSupsParam    - ����ҵ���������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
  1.��    ��   : 2009��12��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��5��14��
    ��    ��   : h44270
    �޸�����   : ���ⵥ�ţ�AT2D19318

  3.��    ��   : 2011��12��17��
    ��    ��   : s46746
    �޸�����   : ���ⵥ�ţ�DTS2011110304908,���ں���ת��ʱ���Ҷϵ绰�ظ���ԭ��ֵ����ȷ

  4.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  5.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  6.��    ��   : 2012��12��11��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  7.��    ��   : 2012��12��29��
    ��    ��   : f62575
    �޸�����   : DTS2012122901074, ��������ؽ�ʱ���йҶ�ʧ������
  8.��    ��   : 2013��01��29��
    ��    ��   : Y00213812
    �޸�����   : DTS2013012909872,��¼CALL�Ҷϵķ���
  9.��    ��   : 2013��07��09��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ
 10.��    ��   : 2014��4��15��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature�޸�
 11.��    ��   : 2014��8��1��
    ��    ��   : w00242748
    �޸�����   : DTS2014072908383:���ز�״̬ʱ��ͬ����Ҫע��Ҷ��¼���
 12.��    ��   :2016��03��08��
    ��    ��   :l00356716
    �޸�����   :NAS���������Ż�
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_CallSupsCmdRelCallXReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;

    /* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-30, begin */
    /* �˴�ɾ�� */
    /* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-30, end */



    enCallState    = MN_CALL_S_BUTT;
    enMptyState    = MN_CALL_MPYT_STATE_BUTT;

    /*����X��״̬Ϊunknown��idle, ���������*/
    MN_CALL_GetCallState(pstCallSupsParam->callId, &enCallState, &enMptyState);
    if ((MN_CALL_S_IDLE == enCallState) || (MN_CALL_S_UNKNOWN == enCallState))
    {
        MN_WARN_LOG("MN_CALL_CallSupsCmdRelCallXReqProc: state err REL CALL X");

       /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
        TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);
        /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

        TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                  opId,
                                                  pstCallSupsParam->callId,
                                                  TAF_CS_CAUSE_STATE_ERROR);

        return;
    }

    MN_CALL_UpdateClientId(pstCallSupsParam->callId, clientId);

    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-30, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstCallSupsParam->callId))
    {
        /* ���"�ȴ�mt eCall���б�־λ" */
        TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

        /* ����ز��������ز���ʱ�� */
        TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(pstCallSupsParam->callId);
    }
#endif
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-30, end */

    if ((MN_CALL_S_INCOMING == enCallState)
     || (MN_CALL_S_WAITING == enCallState)
     || (MN_CALL_S_CCBS_WAITING_RECALL == enCallState))
    {
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-30, begin */
        TAF_CALL_RelIncomingOrWaitingCall(pstCallSupsParam->callId, enCallState);
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-30, end */
    }
    /* ������д���dialing״̬���Һ����ط������ʱ�������У�cc����U0״̬������
       ��cc����disconnect��Ϣ���������rej ind��Ϣ */
   /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */
    else if ((MN_CALL_TIMER_STATUS_RUNING == TAF_CALL_GetRedialIntervalTimerStatus(pstCallSupsParam->callId))
          && (MN_CALL_S_DIALING           == enCallState))
   /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-8, end */
    {
        /* ��ע�ú��еĹҶ�����¼�, ��������Ϊ�ϱ������ɹ� */
        MN_CALL_RegSsKeyEvent(pstCallSupsParam->callId,
            MN_CALL_SS_PROG_EVT_REL,
            MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /*����ҵ�������ʼ����*/
        MN_CALL_BeginCallSupsCmdProgress(clientId, pstCallSupsParam->enCallSupsCmd);

        /* ��¼�����Ҷϵ�ԭ��ֵ */
        MN_CALL_UpdateCcCause(pstCallSupsParam->callId, MN_CALL_NORMAL_CALL_CLEARING);

        /* ��¼���йҶϵķ��� */
        MN_CALL_UpdateDiscCallDir(pstCallSupsParam->callId, VOS_TRUE);

        TAF_CALL_RelRedialingCall(clientId, opId, pstCallSupsParam);
        return;
    }
    else
    {
        /*�Ҷ�ָ���ĺ���*/
        (VOS_VOID)MN_CALL_SendCcDiscReq(pstCallSupsParam->callId, MN_CALL_NORMAL_CALL_CLEARING);

        /* ��¼�����Ҷϵ�ԭ��ֵ */
        MN_CALL_UpdateCcCause(pstCallSupsParam->callId, MN_CALL_NORMAL_CALL_CLEARING);

        /* ��¼���йҶϵķ��� */
        MN_CALL_UpdateDiscCallDir(pstCallSupsParam->callId, VOS_TRUE);
    }

    /* ��ע�ú��еĹҶ�����¼�, ��������Ϊ�ϱ������ɹ� */
    MN_CALL_RegSsKeyEvent(pstCallSupsParam->callId,
                          MN_CALL_SS_PROG_EVT_REL,
                          MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

    /*�����Ҷϣ�ֹͣ�ز���ʱ��*/
    if (VOS_TRUE == TAF_CALL_GetCallRedialForDiscSupportFlg())
    {
        TAF_CALL_StopAllRedialTimers(pstCallSupsParam->callId);
    }

    MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

    MN_NORM_LOG("MN_CALL_CallSupsCmdRelCallXReqProc: send clint res succ.");
    return;
 }

/*****************************************************************************
�� �� ��  : MN_CALL_CallSupsCmdRelAllCallReqProc
��������  : �ͷ���������ͨ���ͱ����ֺ͵ȴ��ĺ���
�������  : clientId            - ����������Client��ID
            opId                - Operation ID, ��ʶ���β���
            pstCallSupsParam    - ����ҵ���������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
  1.��    ��   : 2009��12��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��5��14��
    ��    ��   : h44270
    �޸�����   : ���ⵥ�ţ�AT2D19318
  3.��    ��   : 2010��7��30��
    ��    ��   : h44270
    �޸�����   : ���ⵥ��:DTS2010072901109�������Զ�������ͨ���е绰��Ϊ����״̬
  4.��    ��   : 2011��10��06��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ��API��Ϊ�첽��Ϣ����
  5.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����

  6.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  7.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  8.��    ��   : 2012��12��11��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  9.��    ��   : 2013��01��29��
    ��    ��   : Y00213812
    �޸�����   : DTS2013012909872,��¼CALL�Ҷϵķ���
 10.��    ��   : 2013��07��09��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ

 11.��    ��   : 2013��12��28��
    ��    ��   : j00174725
    �޸�����   : HSUART PHASE III
 12.��    ��   : 2014��4��15��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature�޸�
 13.��    ��   :2016��03��08��
    ��    ��   :l00356716
    �޸�����   :NAS���������Ż�
*****************************************************************************/
VOS_VOID MN_CALL_CallSupsCmdRelAllCallReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           i;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetNotIdleStateCalls(&ulNumOfCalls, aCallIds);

    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
    if (0 == ulNumOfCalls)
    {
        MN_WARN_LOG("MN_CALL_CallSupsCmdRelAllCallReqProc: state err REL ALL CALL");

#if (FEATURE_ON == FEATURE_ECALL)
        if (VOS_TRUE == TAF_CALL_GetInternalHangUpFlag())
        {
            /* �÷�֧���ᷢ�����쳣���� */
            TAF_CALL_SetInternalHangUpFlag(VOS_FALSE);
            TAF_CALL_SendTafRelCallCnf(clientId, opId, TAF_CS_CAUSE_SUCCESS);
        }
        else
#endif
        {
            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
            TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_SUCCESS);
            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

            TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                      opId,
                                                      pstCallSupsParam->callId,
                                                      TAF_CS_CAUSE_SUCCESS);
        }

        return;
    }
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, end */

    /* �Ҷ���������ͨ���ĺ��� */
    for (i = 0; i < ulNumOfCalls; i++)
    {
        MN_CALL_GetCallState(aCallIds[i], &enCallState, &enMptyState);
        MN_CALL_UpdateClientId(aCallIds[i], clientId);
        if ((MN_CALL_S_INCOMING            == enCallState)
         || (MN_CALL_S_WAITING             == enCallState)
         || (MN_CALL_S_CCBS_WAITING_RECALL == enCallState))
        {
            TAF_CALL_RelIncomingOrWaitingCall(aCallIds[i], enCallState);
        }
        /* ������д���dialing״̬���Һ����ط������ʱ�������У�cc����U0״̬������
           ��cc����disconnect��Ϣ���������rej ind��Ϣ */
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */
        else if ((MN_CALL_TIMER_STATUS_RUNING == TAF_CALL_GetRedialIntervalTimerStatus(aCallIds[i]))
              && (MN_CALL_S_DIALING           == enCallState))
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-8, end */
        {
            TAF_CALL_RelRedialingCall(clientId, opId, pstCallSupsParam);
            return;
        }
        else
        {
            (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* ��¼�����Ҷϵ�ԭ��ֵ */
            MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* ��¼���йҶϵķ��� */
            MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

            /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-30, begin */
#if (FEATURE_ON == FEATURE_ECALL)
            if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
            {
                /* ���"�ȴ�mt eCall���б�־λ" */
                TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

                /* ����ز��������ز���ʱ�� */
                TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
            }
#endif
            /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-30, end */
        }

        MN_CALL_DeRegSsKeyEvent(aCallIds[i],MN_CALL_SS_PROG_EVT_SETUP_COMPL);
        MN_CALL_DeRegSsKeyEvent(aCallIds[i],MN_CALL_SS_PROG_EVT_REL);
    }

    /* ��ע���һ�����ҶϺ��еĹҶ�����¼�, ��������Ϊ������һ�� */
    MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                          MN_CALL_SS_PROG_EVT_REL,
                          MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

    /*�����Ҷϣ�ֹͣ�ز���ʱ��*/
    if (VOS_TRUE == TAF_CALL_GetCallRedialForDiscSupportFlg())
    {
        TAF_CALL_StopAllRedialTimers(pstCallSupsParam->callId);
    }

    MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

    MN_NORM_LOG("MN_CALL_CallSupsCmdRelAllCallReqProc: send clint res succ.");
    return;
}

/*****************************************************************************
�� �� ��  : MN_CALL_CallSupsCmdHoldActAcptOthReqProc
��������  : ���������ͨ���ĺ��У�������ͨ���ĺ�����Ϊ�����֣���������һ�������ֻ�ȴ��ĺ���
�������  : clientId            - ����������Client��ID
            opId                - Operation ID, ��ʶ���β���
            pstCallSupsParam    - ����ҵ���������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
  1.��    ��   : 2009��12��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��6��19��
    ��    ��   : z00161729
    �޸�����   : ���ⵥDTS2010061100528

  3.��    ��   : 2010��7��21��
    ��    ��   : h44270
    �޸�����   : ���ⵥDTS2010062601120

  4.��    ��   : 2010��7��30��
    ��    ��   : h44270
    �޸�����   : ���ⵥ��:DTS2010072901109�������Զ�������ͨ���е绰��Ϊ����״̬

  5.��    ��   : 2010��8��21��
    ��    ��   : zhoujun /40661
    �޸�����   : DTS2010081702497,ͨ��MODEM������У�ͨ��AT�ڷ�����б���,
                 û��AT������ʾ���
  6.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����

  7.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  8.��    ��   : 2012��12��11��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  9.��    ��   : 2013��08��01��
    ��    ��   : l65478
    �޸�����   : DTS2013073006494, ����һ��HOLD��һ��MO�Զ���������ĺ���ʱ,����CHLD=2 retrieve��HOLD�ĺ���
 10.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
 11.��    ��   : 2013��07��09��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ

 12.��    ��   : 2013��12��28��
    ��    ��   : j00174725
    �޸�����   : HSUART PHASE III
 13.��    ��   : 2014��04��18��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature�޸�
 14.��    ��   : 2014��6��11��
    ��    ��   : y00245242
    �޸�����   : DTS2014060306029
 15.��    ��   : 2014��6��24��
    ��    ��   : z00161729
    �޸�����   : DSDS III����
 16.��    ��   : 2014��12��17��
    ��    ��   : l00198894
    �޸�����   : DTS2014121602595: AT+CHLD=2�쳣���̴���
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_CallSupsCmdHoldActAcptOthReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    MN_CALL_ID_T                        ucCallId;
    VOS_UINT32                          ulHeldNumOfCalls;
    VOS_UINT32                          ulIncomingNumOfCalls;
    VOS_UINT32                          ulWaitingNumOfCalls;
    VOS_UINT32                          ulDialNumOfCalls;
    VOS_UINT32                          ulAlertingNumOfCalls;

    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aCallIds);
    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulHeldNumOfCalls, aCallIds);
    MN_CALL_GetCallsByState(MN_CALL_S_INCOMING, &ulIncomingNumOfCalls, aCallIds);
    MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulWaitingNumOfCalls, aCallIds);
    MN_CALL_GetCallsByState(MN_CALL_S_DIALING, &ulDialNumOfCalls, aCallIds);
    MN_CALL_GetCallsByState(MN_CALL_S_ALERTING, &ulAlertingNumOfCalls, aCallIds);

    /* ��˶�CHLD=2,������������ʱ,��������:
       if ����һ������ĺ���:
           a.�����ڲ��ҽ�����һ��HOLD�ĺ���,����
           b.�����ڲ��ҽ�����һ��MT�ĺ���,����
           c.��������������
       else if ����һ��HOLD�ĺ���:
           a.�����ڲ��ҽ�����һ��MT�ĺ���,����
           b.��������������
       else if ����һ��MT�ĺ���
    */
    /* ��ǰ��MO�������ڲ��Ż�����������,�ܾ��û����� */
    if ((0 != ulDialNumOfCalls) || (0 != ulAlertingNumOfCalls))
    {
        /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
        TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);
        /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

        TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                  opId,
                                                  pstCallSupsParam->callId,
                                                  TAF_CS_CAUSE_STATE_ERROR);

        return;
    }


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    /* ������ͨ���ĺ��� */
    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* ��ǰ��һ������ĺ���,������һ��HOLD��MT����ʱ,�ܾ�CHLD=2������ */
        if ((0 != ulHeldNumOfCalls) && ((0 != ulIncomingNumOfCalls) || (0 != ulWaitingNumOfCalls)))
        {
            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
            TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);
            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

            TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                      opId,
                                                      pstCallSupsParam->callId,
                                                      TAF_CS_CAUSE_STATE_ERROR);

            return;
        }

        /* �������ͨ���ĺ�����MTPY,��ô����MTPY*/
        MN_CALL_GetCallState(aCallIds[0], &enCallState, &enMptyState);
        if (MN_CALL_IN_MPTY == enMptyState)
        {
            /*����MPTY*/
            MN_CALL_SendCcSimpleFacility(aCallIds[0],
                                         MN_CALL_SS_HOLDMPTY_OPERATION);
        }
        else
        {
            /*���ָú��� */
            MN_CALL_SendCcHoldReq(aCallIds[0]);
        }
        /* ���¸ú��е�Client��Ϣ */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        /* ��ע�ú��еĺ��еı��ֱ��ܾ��¼�, ��������Ϊ�ϱ�����ʧ�� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_HOLD_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        ucCallId = aCallIds[0];

        /*�����ڵȴ��ĺ���*/
        MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aCallIds);
        if (0 != ulNumOfCalls)
        {
            /* ���¸ú��е�Client��Ϣ */
            MN_CALL_UpdateClientId(ucCallId, clientId);

            /*��ע����ͨ���ĺ��еı��ֳɹ��¼�, ��������Ϊ������һ�� */
            MN_CALL_RegSsKeyEvent(ucCallId,
                                  MN_CALL_SS_PROG_EVT_HOLD_CNF,
                                  MN_CALL_SS_SUBSEQ_OP_ACCPT_OTH);

            /* ��ע����ͨ���ĺ��б��ֹ����б��Ҷ��ͷ�ʱ�䣬��������Ϊ������һ�� */
            MN_CALL_RegSsKeyEvent(ucCallId,
                                  MN_CALL_SS_PROG_EVT_REL,
                                  MN_CALL_SS_SUBSEQ_OP_ACCPT_OTH);

            MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

            return;
        }

        /*�б����ֵĺ���*/
        MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfCalls, aCallIds);
        if (0 != ulNumOfCalls)
        {
            /* ��������ֵĺ�����MTPY,��ô�ָ�MTPY����Ȼ�ָ��ú���*/
            MN_CALL_GetCallState(aCallIds[0], &enCallState, &enMptyState);
            if (MN_CALL_IN_MPTY == enMptyState)
            {
                /*�ָ� MPTY*/
                MN_CALL_SendCcSimpleFacility(aCallIds[0],
                                     MN_CALL_SS_RETRIEVEMPTY_OPERATION);
            }
            else
            {
                /*�ָ��ú��� */
                MN_CALL_SendCcRetrieveReq(aCallIds[0]);
            }

            /* ���¸ú��е�Client��Ϣ */
            MN_CALL_UpdateClientId(aCallIds[0], clientId);

            /*��ע�ú��еĻָ��ɹ��¼�, ��������Ϊ�ϱ������ɹ�*/
            MN_CALL_RegSsKeyEvent(aCallIds[0],
                                  MN_CALL_SS_PROG_EVT_RETRIEVE_CNF,
                                  MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

            /*��ע�ú��еĻָ����ܾ��¼�, ��������Ϊ�ϱ�����ʧ��*/
            MN_CALL_RegSsKeyEvent(aCallIds[0],
                                  MN_CALL_SS_PROG_EVT_RETRIEVE_REJ,
                                  MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

            /* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
            /* ����CCģ��ʵ�֣�HOLD CNF���յ��ͱ�־HOLD CNF��RETRIEVE CNF���ᵽ�� */
            MN_CALL_RegSsKeyEvent(ucCallId,
                                  MN_CALL_SS_PROG_EVT_HOLD_CNF,
                                  MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);
            /* Added by f62575 for V9R1 STK����, 2013-6-26, end */

            MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

            return;
        }

        /* ���¸ú��е�Client��Ϣ */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        /*��ע����ͨ���ĺ��еı��ֳɹ��¼�, ��������Ϊ�ϱ������ɹ�*/
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_HOLD_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    /*�����ڵȴ��ĺ���*/
    MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /*�����ú��� */
        (VOS_VOID)MN_CALL_SendCcSetupRsp(aCallIds[0]);
        MN_CALL_StopTimer(MN_CALL_TID_RING);

        /* ���¸ú��е�Client��Ϣ */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        /* ��ע�ú��е����ӽ����ɹ��¼�, ��������Ϊ�ϱ������ɹ� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_SETUP_COMPL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* ��ע�ú��еĹҶ�����¼�, ��������Ϊ�ϱ�����ʧ�� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }
    /*�����ڵȴ��ĺ���,��ӦATA*/
    MN_CALL_GetCallsByState(MN_CALL_S_INCOMING, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* ����Ŀǰ����alert������Ϣ�󣬲Ż��ϱ�incoming�¼�����˴˴��������·�alert�¼� */

        if (VOS_TRUE == TAF_CALL_GetAtaReportOkAsyncFlag())
        {
            TAF_CALL_AtaReportOkAsync(clientId, opId, aCallIds[0], pstCallSupsParam);
            return;
        }

        /*�����ú��� */
        (VOS_VOID)MN_CALL_SendCcSetupRsp(aCallIds[0]);
        MN_CALL_StopTimer(MN_CALL_TID_RING);

        /*�ж�ҵ���ŵ��Ƿ�׼���ã����׼���þ͸�VC���ʹ�����������*/
        if(VOS_TRUE == MN_CALL_GetTchStatus())
        {
            if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
            {
                /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-18, begin */
                /* ������Ϣ֪ͨVC������ͨ�� */
                MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);
                /* ������Ϣ֪ͨAT����ͨ��״̬ */
                MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);
                /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-18, end */
            }
            MN_CALL_SetChannelOpenFlg(VOS_TRUE);
        }

        /* ���¸ú��е�Client��Ϣ */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        /* ��ע�ú��е����ӽ����ɹ��¼�, ��������Ϊ�ϱ������ɹ� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_SETUP_COMPL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* ��ע�ú��еĹҶ�����¼�, ��������Ϊ�ϱ�����ʧ�� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    /*�б����ֵĺ���*/
    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* ��������ֵĺ�����MTPY,��ô�ָ�MTPY����Ȼ�ָ��ú���*/
        MN_CALL_GetCallState(aCallIds[0], &enCallState, &enMptyState);
        if (MN_CALL_IN_MPTY == enMptyState)
        {
            /*�ָ� MPTY*/
            MN_CALL_SendCcSimpleFacility(aCallIds[0],
                                        MN_CALL_SS_RETRIEVEMPTY_OPERATION);
        }
        else
        {
            /*�ָ��ú��� */
            MN_CALL_SendCcRetrieveReq(aCallIds[0]);
        }

        /* ���¸ú��е�Client��Ϣ */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        /*��ע�ú��еĻָ��ɹ��¼�, ��������Ϊ�ϱ������ɹ�*/
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_RETRIEVE_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /*��ע�ú��еĻָ����ܾ��¼�, ��������Ϊ�ϱ�����ʧ��*/
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_RETRIEVE_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err HOLD ACT ACPT OTH");

    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);
    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}

/*****************************************************************************
�� �� ��  : MN_CALL_CallSupsCmdHoldAllExcptXReqProc
��������  : ������X��MPTY�з���
�������  : clientId            - ����������Client��ID
            opId                - Operation ID, ��ʶ���β���
            pstCallSupsParam    - ����ҵ���������
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
  1.��    ��   : 2009��12��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��8��21��
    ��    ��   : zhoujun /40661
    �޸�����   : DTS2010081702497,ͨ��MODEM������У�ͨ��AT�ڷ�����б���,
                 û��AT������ʾ���

  3.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  4.��    ��   : 2012��12��11��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  5.��    ��   : 2013��07��09��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_CallSupsCmdHoldAllExcptXReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstCallSupsParam->callId, &enCallState, &enMptyState);
    if (MN_CALL_IN_MPTY == enMptyState)
    {

        /* ���¸ú��е�Client��Ϣ */
        MN_CALL_UpdateClientId(pstCallSupsParam->callId, clientId);

        /*������X��MPTY�з���*/
        MN_CALL_SendCcSimpleFacility(pstCallSupsParam->callId,
                                     MN_CALL_SS_SPLITMPTY_OPERATION);

        /*��ע�ú��еķ���ɹ��¼�, ��������Ϊ�ϱ������ɹ�*/
        MN_CALL_RegSsKeyEvent(pstCallSupsParam->callId,
                              MN_CALL_SS_PROG_EVT_SPLIT_MPTY_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /*��ע�ú��еķ��뱻�ܾ��¼�, ��������Ϊ�ϱ�����ʧ��*/
        MN_CALL_RegSsKeyEvent(pstCallSupsParam->callId,
                              MN_CALL_SS_PROG_EVT_SPLIT_MPTY_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err HOLD ALL EXCPT X");

    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);
    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_CallSupsCmdBuildMptyReqProc
 ��������  : ����MPTY
 �������  : clientId            - ����������Client��ID
             opId                - Operation ID, ��ʶ���β���
             pstCallSupsParam    - ����ҵ���������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��12��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��8��21��
    ��    ��   : zhoujun /40661
    �޸�����   : DTS2010081702497,ͨ��MODEM������У�ͨ��AT�ڷ�����б���,
                 û��AT������ʾ���

  3.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����

  4.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  5.��    ��   : 2013��07��09��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_CallSupsCmdBuildMptyReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    if (VOS_TRUE == MN_CALL_JudgeAllowToBuildMpty())
    {
        /* ����MPTY */
        MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aCallIds);

        /* ���¸ú��е�Client��Ϣ */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        MN_CALL_SendCcSimpleFacility(aCallIds[0],
                                     MN_CALL_SS_BUILDMPTY_OPERATION);


        /* ��ע�ú��еĽ���MPTY�ɹ��¼�, ��������Ϊ�ϱ������ɹ� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_BUILD_MPTY_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* ��ע�ú��еĽ���MPTY���ܾ��¼�, ��������Ϊ�ϱ�����ʧ�� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_BUILD_MPTY_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }
    MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err BUILD MPTY");


    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);
    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_CallSupsCmdDeflectCallReqProc
 ��������  : �������ȴ��ĺ���ƫת����һ������
 �������  : clientId            - ����������Client��ID
             opId                - Operation ID, ��ʶ���β���
             pstCallSupsParam    - ����ҵ���������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��12��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��7��30��
    ��    ��   : h44270
    �޸�����   : ���ⵥ��:DTS2010072901109�������Զ�������ͨ���е绰��Ϊ����״̬

  3.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����

  4.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  5.��    ��   : 2013��07��09��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ

  6.��    ��   : 2013��12��28��
    ��    ��   : j00174725
    �޸�����   : HSUART PHASE III
  7.��    ��   : 2014��6��24��
    ��    ��   : z00161729
    �޸�����   : DSDS III����
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_CallSupsCmdDeflectCallReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];

    TAF_CALL_SUB_STATE_ENUM_UINT8       enCallSubState;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    MN_CALL_GetCallsByState(MN_CALL_S_INCOMING, &ulNumOfCalls, aCallIds);
    if (0 == ulNumOfCalls)
    {
        MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aCallIds);
        if (0 == ulNumOfCalls)
        {
            MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err DEFLECT CALL");

            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
            TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);
            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

            TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                      opId,
                                                      pstCallSupsParam->callId,
                                                      TAF_CS_CAUSE_STATE_ERROR);

            return;
        }
        else
        {
            MN_CALL_StopTimer(MN_CALL_TID_RING);
        }
    }
    else
    {
        /* NV����ж�incoming���еĺ�����״̬Ϊ
           TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK��ֱ���ϱ�ERROR */
        enCallSubState = TAF_CALL_GetCallSubState(pstCallSupsParam->callId);

        if ((VOS_TRUE == TAF_CALL_GetAtaReportOkAsyncFlag())
         && (TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK == enCallSubState))
        {
            TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

            TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                      opId,
                                                      pstCallSupsParam->callId,
                                                      TAF_CS_CAUSE_STATE_ERROR);

            return;
        }

        MN_CALL_StopTimer(MN_CALL_TID_RING);
    }

    MN_CALL_UpdateRedirNumber(aCallIds[0], &pstCallSupsParam->stRedirectNum);

    /*���¸ú��е�Client��Ϣ*/
    MN_CALL_UpdateClientId(aCallIds[0], clientId);

    /* ��������ƫת�Ĳ���ҵ������ */
    MN_CALL_SendCcDeflectFacility(aCallIds[0], &pstCallSupsParam->stRedirectNum);


    /* ��ע�ú��е�ƫת�ɹ��¼�, ��������Ϊ�ϱ������ɹ� */
    MN_CALL_RegSsKeyEvent(aCallIds[0],
                          MN_CALL_SS_PROG_EVT_DEFLECT_CNF,
                          MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

    /* ��ע�ú��е�ƫת���ܾ��¼�, ��������Ϊ�ϱ�����ʧ�� */
    MN_CALL_RegSsKeyEvent(aCallIds[0],
                          MN_CALL_SS_PROG_EVT_DEFLECT_REJ,
                          MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

    MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

    MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
    return;

}

/*****************************************************************************
 �� �� ��  : MN_CALL_CallSupsCmdEctReqProc
 ��������  : ECT��ز���ҵ���������
 �������  : clientId            - ����������Client��ID
             opId                - Operation ID, ��ʶ���β���
             pstCallSupsParam    - ����ҵ���������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��12��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��8��8��
    ��    ��   : z40661
    �޸�����   : DTS2012072303448

  3.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����

  4.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  5.��    ��   : 2013��07��09��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_CallSupsCmdEctReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT32                          ulNumOfCalls2;
    MN_CALL_ID_T                        aHeldCallIds[MN_CALL_MAX_NUM];
    MN_CALL_ID_T                        aOtherCallIds[MN_CALL_MAX_NUM];


    PS_MEM_SET(aHeldCallIds,  0x00, sizeof(aHeldCallIds));
    PS_MEM_SET(aOtherCallIds, 0x00, sizeof(aOtherCallIds));

    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfCalls, aHeldCallIds);
    if ( 0 != ulNumOfCalls )
    {
        MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aOtherCallIds);
        ulNumOfCalls2 = ulNumOfCalls;
        MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aOtherCallIds);
        ulNumOfCalls2 += ulNumOfCalls;
        MN_CALL_GetCallsByState(MN_CALL_S_ALERTING, &ulNumOfCalls, aOtherCallIds);
        ulNumOfCalls2 += ulNumOfCalls;
        if( 0 == ulNumOfCalls2 )
        {
            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
            TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);
            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

            TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                      opId,
                                                      pstCallSupsParam->callId,
                                                      TAF_CS_CAUSE_STATE_ERROR);

            return;
        }

        /*���¸ú��е�Client��Ϣ*/
        MN_CALL_UpdateClientId(aHeldCallIds[0], clientId);

        /* ECT���� */
        MN_CALL_SendCcSimpleFacility(aHeldCallIds[0],
                                     MN_CALL_SS_ECT_OPERATION);
        /* ��ע�ú��е�ECT�ɹ��¼�, ��������Ϊ�ϱ������ɹ� */
        MN_CALL_RegSsKeyEvent(aHeldCallIds[0],
                              MN_CALL_SS_PROG_EVT_ECT_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* ��ע�ú��е�ECT���ܾ��¼�, ��������Ϊ�ϱ�����ʧ�� */
        MN_CALL_RegSsKeyEvent(aHeldCallIds[0],
                              MN_CALL_SS_PROG_EVT_ECT_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);


        /*������һ���е�Client��Ϣ*/
        MN_CALL_UpdateClientId(aOtherCallIds[0], clientId);


        /* ��ע�ú��е�ECT�ɹ��¼�, ��������Ϊ�ϱ������ɹ� */
        MN_CALL_RegSsKeyEvent(aOtherCallIds[0],
                              MN_CALL_SS_PROG_EVT_ECT_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* ��ע�ú��е�ECT���ܾ��¼�, ��������Ϊ�ϱ�����ʧ�� */
        MN_CALL_RegSsKeyEvent(aOtherCallIds[0],
                              MN_CALL_SS_PROG_EVT_ECT_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);
    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_CallSupsCmdRelAllExceptWaitCallReqProc
 ��������  : �ͷų��˵ȴ����������к���
 �������  : clientId            - ����������Client��ID
             opId                - Operation ID, ��ʶ���β���
             pstCallSupsParam    - ����ҵ���������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��12��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����

  3.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  4.��    ��   : 2012��12��11��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  5.��    ��   : 2013��01��29��
    ��    ��   : Y00213812
    �޸�����   : DTS2013012909872,��¼CALL�Ҷϵķ���
  6.��    ��   : 2013��07��09��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ
  7.��    ��   : 2014��4��15��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature�޸�
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_CallSupsCmdRelAllExceptWaitCallReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    VOS_UINT8                           i;

    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetNotIdleStateCalls(&ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* �Ҷ���������ͨ���ĺ��� */
        for (i = 0; i < ulNumOfCalls; i++)
        {
            MN_CALL_GetCallState(aCallIds[i], &enCallState, &enMptyState);
            if (( MN_CALL_S_INCOMING != enCallState)
             && ( MN_CALL_S_WAITING != enCallState))
            {
                /* ���¸ú��е�Client��Ϣ */
                MN_CALL_UpdateClientId(aCallIds[i], clientId);
                (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

                /* ��¼�����Ҷϵ�ԭ��ֵ */
                MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

                /* ��¼���йҶϵķ��� */
                MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

                /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-30, begin */
#if (FEATURE_ON == FEATURE_ECALL)
                if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
                {
                    /* ���"�ȴ�mt eCall���б�־λ" */
                    TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

                    /* ����ز��������ز���ʱ�� */
                    TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
                }
#endif
                /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-30, end */
            }
        }

        /* ��ע���һ�����ҶϺ��еĹҶ�����¼�, ��������Ϊ������һ�� */
        MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err REL ALL CALL");

    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);
    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_CallSupsCmdRelHeldReqProc
 ��������  : �ͷ����б����ֵĺ���
 �������  : clientId            - ����������Client��ID
             opId                - Operation ID, ��ʶ���β���
             pstCallSupsParam    - ����ҵ���������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��12��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��8��21��
    ��    ��   : zhoujun /40661
    �޸�����   : DTS2010081702497,ͨ��MODEM������У�ͨ��AT�ڷ�����б���,
                 û��AT������ʾ���
  3.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����

  4.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  5.��    ��   : 2013��01��29��
    ��    ��   : Y00213812
    �޸�����   : DTS2013012909872,��¼CALL�Ҷϵķ���
  6.��    ��   : 2013��07��09��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ
  7.��    ��   : 2014��4��15��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature�޸�
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_CallSupsCmdRelHeldReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT8                           i;

    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* �Ҷ���������ͨ���ĺ��� */
        for (i = 0; i < ulNumOfCalls; i++)
        {
            /* ���¸ú��е�Client��Ϣ */
            MN_CALL_UpdateClientId(aCallIds[i], clientId);
            (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* ��¼�����Ҷϵ�ԭ��ֵ */
            MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* ��¼���йҶϵķ��� */
            MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

            /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-30, begin */
#if (FEATURE_ON == FEATURE_ECALL)
            if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
            {
                /* ���"�ȴ�mt eCall���б�־λ" */
                TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

                /* ����ز��������ز���ʱ�� */
                TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
            }
#endif
            /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-30, end */
        }

        /* ��ע���һ�����ҶϺ��еĹҶ�����¼�, ��������Ϊ������һ�� */
        MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err REL ALL CALL");

    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);
    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_CallSupsCmdRelActiveReqProc
 ��������  : �ͷ���������ͨ���ĺ���
 �������  : clientId            - ����������Client��ID
             opId                - Operation ID, ��ʶ���β���
             pstCallSupsParam    - ����ҵ���������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��12��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��8��21��
    ��    ��   : zhoujun /40661
    �޸�����   : DTS2010081702497,ͨ��MODEM������У�ͨ��AT�ڷ�����б���,
                 û��AT������ʾ���

  3.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����

  4.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  5.��    ��   : 2013��01��29��
    ��    ��   : Y00213812
    �޸�����   : DTS2013012909872,��¼CALL�Ҷϵķ���
  6.��    ��   : 2013��07��09��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ
  7.��    ��   : 2014��4��15��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature�޸�
*****************************************************************************/
LOCAL VOS_VOID MN_CALL_CallSupsCmdRelActiveReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT8                           i;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* �Ҷ���������ͨ���ĺ��� */
        for (i = 0; i < ulNumOfCalls; i++)
        {
            /* ���¸ú��е�Client��Ϣ */
            MN_CALL_UpdateClientId(aCallIds[i], clientId);
            (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* ��¼�����Ҷϵ�ԭ��ֵ */
            MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* ��¼���йҶϵķ��� */
            MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

            /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-30, begin */
#if (FEATURE_ON == FEATURE_ECALL)
            if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
            {
                /* ���"�ȴ�mt eCall���б�־λ" */
                TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

                /* ����ز��������ز���ʱ�� */
                TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
            }
#endif
            /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-30, end */
        }

        /* ��ע���һ�����ҶϺ��еĹҶ�����¼�, ��������Ϊ������һ�� */
        MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err REL ALL CALL");

    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);
    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}


/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */

/*****************************************************************************
 �� �� ��  : MN_CALL_SetMmEmerNumList
 ��������  : �洢����MM�Ӳ�Ľ������к����б�
 �������  : pstMsg - ����CC��ԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��09��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ���� ENERGENCY CALL
  3.��    ��   : 2012��06��11��
    ��    ��   : w00166186
    �޸�����   : AT&T&DCM��Ŀ
  4.��    ��   : 2013��10��28��
    ��    ��   : w00167002
    �޸�����   : DTS2013102201891:���ӶԽ�����������0xf���ݴ����������Я��
                  �Ľ�����Ϊ22f222�����ݴ����Ϊ222��
  5.��    ��   : 2013��12��16��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ
*****************************************************************************/
VOS_VOID  MN_CALL_SetMmEmerNumList(
    MNCC_EMERGENCY_LIST_IND_STRU       *pstMnccEmcListInd
)
{
    VOS_UINT8                           i;

    VOS_UINT32                          j;

    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */
    TAF_SDC_MM_EMERGENCY_LIST_STRU     *pstMmCallEmerNumList    = VOS_NULL_PTR;

    pstMmCallEmerNumList                    = TAF_SDC_GetMmCallEmerNumList();

    pstMmCallEmerNumList->ulMcc             = pstMnccEmcListInd->ulMcc;
    pstMmCallEmerNumList->ucEmergencyNumber = pstMnccEmcListInd->ucEmergencyNumber;

    /* ������������������������ֵ����ʹ�����ֵ */
    if (pstMnccEmcListInd->ucEmergencyNumber > TAF_SDC_EMER_NUM_LISTS_MAX_NUMBER)
    {
        pstMmCallEmerNumList->ucEmergencyNumber = TAF_SDC_EMER_NUM_LISTS_MAX_NUMBER;
    }
    else
    {
        pstMmCallEmerNumList->ucEmergencyNumber = pstMnccEmcListInd->ucEmergencyNumber;
    }

    /* �����������뱣����ȫ�ֱ����� */
    for (i = 0; i < pstMmCallEmerNumList->ucEmergencyNumber; i++)
    {
        pstMmCallEmerNumList->astEmergencyLists[i].ucCategoryValue = pstMnccEmcListInd->astEmergencyLists[i].ucCategoryValue;
        pstMmCallEmerNumList->astEmergencyLists[i].ucEmcNumLen     = pstMnccEmcListInd->astEmergencyLists[i].ucEmcNumLen;


        /* BCD����0X0F��ʾ�������к�����������BCD����дΪ99f947,����Ҫת��Ϊ99f9 */
        for ( j = 0; j < pstMnccEmcListInd->astEmergencyLists[i].ucEmcNumLen; j++ )
        {
            pstMmCallEmerNumList->astEmergencyLists[i].aucEmergencyList[j] = pstMnccEmcListInd->astEmergencyLists[i].aucEmergencyNum[j];

            /* ��⵽��������0XF_ */
            if (MN_CALL_BCD_ODD_NUMBER_END == (pstMnccEmcListInd->astEmergencyLists[i].aucEmergencyNum[j] & MN_CALL_BCD_ODD_NUMBER_END) )
            {
                /* ��Ҫ�Գ���ֵ���¸�ֵ */
                pstMmCallEmerNumList->astEmergencyLists[i].ucEmcNumLen = (VOS_UINT8)(j + 1);
                break;
            }

        }

    }
    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */
}

/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */
/* TAF_SPM_UsimEccNumCheck ��TAF_SPM_NetworkEccNumCheck��TAF_SPM_AppCustomEccNumCheck
    TAF_SPM_EccNumCheck���Ƶ�SPM,������ΪTAF_SPM_... */
/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */


/*****************************************************************************
 �� �� ��  : MN_CALL_GetMoCallBc
 ��������  : ��ȡ���е�BC��Ϣ
 �������  : pstCallInfo         - ���е�ID
 �������  : pstBc1    -
             pstBc2    -
             penBcRepeatInd
 �� �� ֵ  : VOS_UINT32
                VOS_ERR        ��ȡ���е�BC��Ϣʧ��
                VOS_OK         ��ȡ���е�BC��Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��23��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��05��21��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ��:DTS2012052100994,������ӵ绰����������ĳ������Ͳ���
*****************************************************************************/
VOS_UINT32 MN_CALL_GetMoCallBc(
    MN_CALL_ID_T                        CallId,
    NAS_CC_IE_BC_STRU                  *pstBc1,
    NAS_CC_IE_BC_STRU                  *pstBc2,
    MN_CALL_REP_IND_ENUM_U8            *penBcRepeatInd
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulNumOfBc;
    MN_CALL_MGMT_STRU                   stCallInfo;

    ulRet = MN_CALL_GetSpecificCallInfo(CallId, &stCallInfo);
    if (VOS_OK != ulRet)
    {
        return ulRet;
    }

    /* ���ݺ�������, ����ģʽ�����ݺ�����������BC��Repeat Ind���� */
    PS_MEM_SET(pstBc1, 0, sizeof(NAS_CC_IE_BC_STRU));
    PS_MEM_SET(pstBc2, 0, sizeof(NAS_CC_IE_BC_STRU));

    ulNumOfBc = MN_CALL_BuildBcOfSetup(stCallInfo.stCallInfo.enCallType,
                                       stCallInfo.stCallInfo.enCallMode,
                                       &stCallInfo.stCallInfo.stDataCfgInfo,
                                       pstBc1,
                                       pstBc2);
    if (0 == ulNumOfBc)
    {
        return VOS_ERR;
    }
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-30, begin */
    else if (TAF_CALL_MAX_BC_NUM == ulNumOfBc)
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-30, end */
    {
        /* ������BC������£�repeat indicator��Ϊalternate */
        *penBcRepeatInd = MN_CALL_REP_IND_ALTER;
    }
    else
    {
        /* �˴���Ҫ�ο�24.008 10.5.4.22 �еĶ���ȷ��?? */
        *penBcRepeatInd = MN_CALL_REP_IND_NULL;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_BuildNormalCallReqProc
 ��������  : ��������Ӧ�ò����ͨ����
             �ú���������ͨ���е�Setup��Ϣ
 �������  : clientId       - ����������Client��ID
             opId           - Operation ID, ��ʶ���β���
             callId         - �������еĺ���ID������Ψһ�ı�ʶ�������
             pstOrigParam   - ����������Я���Ĳ���
 �������  : ��
 �� �� ֵ  : VOS_UINT32
                MN_ERR_NO_ERROR     ������ͨ���е�Setup��Ϣ�ɹ�
                ������              ������ͨ���е�Setup��Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��02��24��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : C50_IPC Project Ϊ����FDNҵ��CALL SETUP��Ϣ��������Ϣ���Ӻ���ʵ���ȡ
  3.��    ��   : 2012��05��21��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ��:DTS2012052100994,������ӵ绰����������ĳ������Ͳ���
  4.��    ��   : 2012��09��18��
    ��    ��   : y00213812
    �޸�����   : STK&DCM ��Ŀ���Ӵ��ӵ�ַ�ĺ���

  5.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  6.��    ��   : 2013��8��3��
    ��    ��   : z60575
    �޸�����   : TQE�޸�
*****************************************************************************/
VOS_UINT32  MN_CALL_BuildNormalCallReqProc(MN_CALL_ID_T callId)
{
    NAS_CC_IE_BC_STRU                   stBc1;
    NAS_CC_IE_BC_STRU                   stBc2;
    MN_CALL_REP_IND_ENUM_U8             enBcRepeatInd;
    VOS_UINT32                          ulRet;
    MN_CALL_MGMT_STRU                   stCallInfo;

    PS_MEM_SET(&stCallInfo, 0, sizeof(stCallInfo));

    ulRet = MN_CALL_GetSpecificCallInfo(callId, &stCallInfo);
    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("MN_CALL_BuildNormalCallReqProc: BUILD BC FAIL.");
        return TAF_CS_CAUSE_UNKNOWN;
    }

    ulRet = MN_CALL_GetMoCallBc(stCallInfo.stCallInfo.callId, &stBc1, &stBc2, &enBcRepeatInd);
    if (VOS_OK != ulRet)
    {
        /* ����BCʧ�ܣ��ͷź��� */
        MN_WARN_LOG("MN_CALL_BuildNormalCallReqProc: BUILD BC FAIL.");
        return TAF_CS_CAUSE_UNKNOWN;
    }

    /* �����ϱ���speed�Ķ��壬��API�еĶ��岻ͬ��
       ��speed����ת����ֱ�Ӵ�BC�н���ת�� */
    if ((MN_CALL_TYPE_CS_DATA == stCallInfo.stCallInfo.enCallType)
      ||(MN_CALL_TYPE_FAX == stCallInfo.stCallInfo.enCallType))
    {
        MN_CALL_GetDataCfgInfoFromBc(&stBc1, &stCallInfo.stCallInfo.stDataCfgInfo);
    }
    else
    {
        /* ������������棬���BC2�л�ȡ */
        if (( MN_CALL_MODE_AVF == stCallInfo.stCallInfo.enCallMode )
          &&( VOS_TRUE == NAS_IE_IS_PRESENT(&stBc2)))
        {
            MN_CALL_GetDataCfgInfoFromBc(&stBc2, &stCallInfo.stCallInfo.stDataCfgInfo);
        }
    }

    /* FDN���Ӧ���� MO CONTROL����ǰִ�У��˴�����ǰ�� */

    /* �����������е�Setup��Ϣ��CC */

    if (VOS_OK != MN_CALL_SendCcSetupReq(enBcRepeatInd,
                                         &stBc1,
                                         &stBc2,
                                         &stCallInfo))
    {
        MN_WARN_LOG("MN_CALL_CallOrigReqProc: SEND MSG ERROR.");
        return TAF_CS_CAUSE_UNKNOWN;
    }
    else
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MO_ATTEMPT,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);
    }

    return TAF_CS_CAUSE_SUCCESS;
}

/*****************************************************************************
 �� �� ��  :  MN_CALL_CheckNVAllowCallOrig
 ��������  : ���NV�������Ƿ����������
 �������  : ucCallType     - ��������
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_BOOL MN_CALL_CheckNVAllowCallOrig(
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    VOS_UINT8                           enVpNvCfgState;

    if (MN_CALL_TYPE_VOICE == enCallType)
    {
        /* VOICE���͵ĺ������������Ļ���ֱ�ӷ���VOS_FALSE */
        /* Modified by z00234330 for PCLINT����, 2014-06-24, begin */
        if ( VOS_FALSE == TAF_CALL_GetCallStatusControl())
        /* Modified by z00234330 for PCLINT����, 2014-06-24, end */
        {
            return VOS_FALSE;
        }
        return VOS_TRUE;
    }
    /* Modified by z00234330 for PCLINT����, 2014-07-03, end */
    enVpNvCfgState = TAF_CALL_GetVpCfgState();
    if (MN_CALL_TYPE_VIDEO == enCallType)
    {
        /* ���ݵ�ǰ��NV�˫���MO��������ģ�����VOS_TRUE */
        if (( MN_CALL_VP_MO_MT_BOTH == enVpNvCfgState )
         || ( MN_CALL_VP_MO_ONLY == enVpNvCfgState ))
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }
    /* Modified by z00234330 for PCLINT����, 2014-07-03, end */
    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : MN_CALL_CallOrigReqProc
 ��������  : ��������Ӧ�ò����������
             �ú�������鵱ǰ״̬�Ƿ�������һ�����У����Ҽ����еĺ�����ȷ��
             �ú����Ƿ������Լ��Ƿ��ǽ������к��롣���ͨ������CC����
             MNCC_SETUP_REQ��MNCC_EMERG_SETUP_REQԭ�﷢��һ�����л�������С�
 �������  : clientId       - ����������Client��ID
             opId           - Operation ID, ��ʶ���β���
             callId         - �������еĺ���ID������Ψһ�ı�ʶ�������
             pstOrigParam   - ����������Я���Ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��2��23��
    ��    ��   : zhoujun /z40661
    �޸�����   : NAS R7Э������
  3.��    ��   : 2011��3��1��
    ��    ��   : z00161729
    �޸�����   : DTS2011022800325:detach״̬atd����绰��Ӧ����ok
  4.��    ��   : 2011��10��06��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ
  5.��    ��   : 2012��02��24��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : C50_IPC Project ���������й����е�FDNҵ����
  6.��    ��   : 2012��9��20��
    ��    ��   : f62575
    �޸�����   : STK SETUP CALL
  7.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  8.��    ��   : 2012��10��30��
    ��    ��   : l00198894
    �޸�����   : DTS2012102906862: �ֲ�������ʼ��
  9.��    ��   : 2012��10��29��
    ��    ��   : l00198894
    �޸�����   : DTS2012100901666: ���к��볤�ȸı䣬FDN���ʱ�ض�
  10.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
 11.��    ��   : 2012��12��26��
    ��    ��   : ���� id:00214637
    �޸�����   : USIM����ӿں�������Ĵ���
 12.��    ��   : 2013��5��15��
    ��    ��   : w00176964
    �޸�����   : SS FDN&Call Control��Ŀ:FDN���������client ID
 13.��    ��   : 2013��6��5��
    ��    ��   : w00242748
    �޸�����   : SVLTE��USIM�ӿ�����
 14.��    ��   : 2013��07��09��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ
 15.��    ��   : 2013��12��14��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ
 16.��    ��   : 2013��12��14��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII ��Ŀ:FDN CALLcontrol�������Ƶ�SPM
 17.��    ��   : 2014��4��22��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature����
 18.��    ��   : 2014��07��22��
    ��    ��   : w00242748
    �޸�����   : DTS2014072101479:call proceedingʱ��CC��taf����rej ind����ʱ���������ز�
                 MSD���ݴ�����ɺ��ٷ�����У�alerting��CC��taf����rej ind����ʱҲ�������ز�
*****************************************************************************/
VOS_VOID  MN_CALL_CallOrigReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    MN_CALL_ORIG_PARAM_STRU            *pstOrigParam
)
{
    VOS_UINT32                          ulRet;
    MN_CALL_ID_T                        NewcallId;

    NewcallId = 0;

    /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-14, begin */
    /* ���������жϷ���SPMԤ�����У�����ɾ�� */
    /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-14, end */

    /* ��������У�֪ͨ���з��𷽺����쳣���� */
    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-14, begin */
    ulRet = MN_CALL_MakeNewCall(pstOrigParam->enCallType,
                                &NewcallId);

    if (TAF_CS_CAUSE_SUCCESS != ulRet)
    {
        MN_NORM_LOG("MN_CALL_CallOrigReqProc: Fail to MN_CALL_MakeNewCall.");

        /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
        TAF_CALL_SendCallOrigCnf(clientId, opId, callId, ulRet);
        /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

#if (FEATURE_ON == FEATURE_PTM)
        /* ��¼CS�����쳣log */
        MN_CALL_CsCallErrRecord(NewcallId, ulRet);
#endif

        return;
    }
    callId = NewcallId;

    /* ����ǽ������У���ֱ�ӷ���CC,�������л���Ҫ����һϵ���ж� */
    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-22, begin */
    if ((MN_CALL_TYPE_EMERGENCY == pstOrigParam->enCallType)
#if (FEATURE_ON == FEATURE_ECALL)
     || (MN_CALL_TYPE_MIEC      == pstOrigParam->enCallType)
     || (MN_CALL_TYPE_AIEC      == pstOrigParam->enCallType)
#endif
       )
    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-22, end */
    {
        /*�½�һ������ʵ��, ulCcTi��û��ʵ�ʺ���*/
        MN_CALL_CreateMoCallEntity(clientId, opId, callId, pstOrigParam);

        if (VOS_TRUE == pstOrigParam->stEmergencyCat.bExist)
        {
            ulRet = MN_CALL_SendCcEmergSetupReq(callId,
                                                &(pstOrigParam->stEmergencyCat.ucEmergencyCat));

        }
        else
        {
            ulRet = MN_CALL_SendCcEmergSetupReq(callId, VOS_NULL_PTR);
        }
        /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-14, end */

        if (VOS_OK != ulRet)
        {
            MN_WARN_LOG("MN_CALL_CallOrigReqProc: SEND MSG ERROR: emerge.");

            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
            TAF_CALL_SendCallOrigCnf(clientId, opId, callId, TAF_CS_CAUSE_UNKNOWN);
            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

#if (FEATURE_ON == FEATURE_PTM)
            /* ��¼CS�����쳣log */
            MN_CALL_CsCallErrRecord(callId, TAF_CS_CAUSE_UNKNOWN);
#endif

            MN_CALL_FreeCallId(callId);
            return;
        }
    }
    else
    {
        /*�½�һ������ʵ��, ulCcTi��û��ʵ�ʺ���*/
        MN_CALL_CreateMoCallEntity(clientId, opId, callId, pstOrigParam);

        /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */
        /* FDN��CALL control�ļ��������Ƶ�SPMģ�� */
        /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */

        ulRet = MN_CALL_BuildNormalCallReqProc(callId);

        if (TAF_CS_CAUSE_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_CALL_CallOrigReqProc: MN_CALL_BuildNormalCallReqProc fail.");

            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
            TAF_CALL_SendCallOrigCnf(clientId, opId, callId, ulRet);
            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

#if (FEATURE_ON == FEATURE_PTM)
            /* ��¼CS�����쳣log */
            MN_CALL_CsCallErrRecord(callId, ulRet);
#endif

            MN_CALL_FreeCallId(callId);
            return;
        }
    }

    NAS_EventReport(WUEPS_PID_TAF,
                    NAS_OM_EVENT_CC_MO_ATTEMPT,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    MN_CALL_UpdateCallState(callId, MN_CALL_S_DIALING);

    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    /* ���T9��ʱ����running, ֹͣT9��ʱ�� */
    MN_CALL_StopTimer(TAF_CALL_TID_T9);

    TAF_CALL_ResetEcallPeriodRemainTimerLen();

    TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_BUTT);
#endif

    /* ���֧�ֺ����ؽ����ܣ�������MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD��ʱ�� */
    if (VOS_TRUE == TAF_CALL_GetRedialSupportFlg(callId))
    {
        TAF_CALL_StartRedialPeriodTimer(callId);
    }
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-8, end */

    TAF_CALL_SendCallOrigCnf(clientId, opId, callId, TAF_CS_CAUSE_SUCCESS);


    MN_CALL_ReportEvent(callId, MN_CALL_EVT_ORIG);

    MN_NORM_LOG("MN_CALL_CallOrigReqProc: send clint res normal and report event.");
}

/*****************************************************************************
 �� �� ��  : MN_CALL_GetEndCause
 ��������  : ���ɷ���������causeֵ
 �������  : enEndCause    - Ӧ����д��causeֵ
              enCallState   - ����״̬
 �������  : ��
 �� �� ֵ  : ����������causeֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��29��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��10��13��
    ��    ��   : s00217060
    �޸�����   : for cs_err_log
*****************************************************************************/
TAF_CS_CAUSE_ENUM_UINT32 MN_CALL_GetEndCause(
    TAF_CS_CAUSE_ENUM_UINT32            enEndCause,
    MN_CALL_STATE_ENUM_U8               enCallState
)
{
    /* ��д��Ӧ�ĹҶ�ԭ��ֵ */
    /* enEndCauseС��128ʱ��enEndCause��incoming/waiting״̬��USER_BUSY������127ʱ��interwork unspecified */
    if ( (MN_CALL_INVALID_CAUSE            != enEndCause)
      && (MN_CALL_INTERWORKING_UNSPECIFIED >= enEndCause ) )
    {
        return enEndCause;
    }
    else if ((MN_CALL_S_INCOMING == enCallState)
          || (MN_CALL_S_WAITING == enCallState)
          || (MN_CALL_S_CCBS_WAITING_RECALL == enCallState))
    {
        return TAF_CS_CAUSE_CC_NW_USER_BUSY;
    }
    else if (MN_CALL_INTERWORKING_UNSPECIFIED < enEndCause)
    {
        return MN_CALL_INTERWORKING_UNSPECIFIED;
    }
    else
    {
        return TAF_CS_CAUSE_CC_NW_NORMAL_CALL_CLEARING;
    }

}

/*****************************************************************************
 �� �� ��  : MN_CALL_InternalCallEndReqProc
 ��������  : �ͷź��б�����Դ������CC����MNCC_DISC_REQԭ��
 �������  : clientId    - ����������Client��ID
             opId        - Operation ID, ��ʶ���β���
             callId      - ��Ҫ�Ҷϵĺ��е�ID
             pstEndParm  - �Ҷ�������Я���Ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��17��
    ��    ��   : f62575
    �޸�����   : DTS2013091104858���һ�ǰ������ɵ��û�����

  2.��    ��   : 2013��12��28��
    ��    ��   : j00174725
    �޸�����   : HSUART PHASE III
*****************************************************************************/
VOS_UINT32 MN_CALL_InternalCallEndReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_END_PARAM_STRU       *pstEndParm
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    MN_CALL_CC_CAUSE_ENUM_U8            enCause;

    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_CC_CAUSE_BUTT;

    /* ��ȡ��Ӧ�ĺ���״̬�������Idle��Unknown״̬��ֱ���ϱ����� */
    MN_CALL_GetCallState(callId, &enCallState, &enMptyState);
    if ((MN_CALL_S_IDLE == enCallState)
     || (MN_CALL_S_UNKNOWN == enCallState))
    {
        if ( MN_CLIENT_ALL != clientId )
        {
            MN_WARN_LOG1("MN_CALL_InternalCallEndReqProc: send clint res err.",TAF_CS_CAUSE_STATE_ERROR);
            return TAF_CS_CAUSE_STATE_ERROR;
        }

    }

    if ((MN_CALL_S_INCOMING == enCallState)
      ||(MN_CALL_S_WAITING == enCallState))
    {
        MN_CALL_StopTimer(MN_CALL_TID_RING);
    }

    /* enCause��CC��Disconnectʱ�ã����ܳ���127
       pstEndParm->enEndCause��Ҫ���µ��Ҷ�ԭ��ֵ�У���CEND��ʱ���� */
    enCause = (MN_CALL_CC_CAUSE_ENUM_U8)MN_CALL_GetEndCause(pstEndParm->enEndCause, enCallState);

    /* ��¼�����Ҷϵ�ԭ��ֵ */
    MN_CALL_UpdateCcCause(callId, pstEndParm->enEndCause);

    /* ��¼���йҶϵķ��� */
    MN_CALL_UpdateDiscCallDir(callId, VOS_TRUE);

    /* ����MNCC_DISC_REQԭ�� */
    if (VOS_OK != MN_CALL_SendCcDiscReq(callId, enCause))
    {
        MN_WARN_LOG1("MN_CALL_InternalCallEndReqProc: send clint res err.",TAF_CS_CAUSE_UNKNOWN);
        return TAF_CS_CAUSE_UNKNOWN;
    }

    MN_NORM_LOG("MN_CALL_InternalCallEndReqProc: send clint res normal.");
    return TAF_CS_CAUSE_SUCCESS;

}

/*****************************************************************************
 �� �� ��  : MN_CALL_CallEndReqProc
 ��������  : ��������Ӧ�ò�ĹҶ����󣬸ú�������CC����MNCC_DISC_REQԭ��
 �������  : clientId    - ����������Client��ID
             opId        - Operation ID, ��ʶ���β���
             callId      - ��Ҫ�Ҷϵĺ��е�ID
             pstEndParm  - �Ҷ�������Я���Ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��2��23��
    ��    ��   : zhoujun /z40661
    �޸�����   : NAS R7Э������
  3.��    ��   : 2010��7��30��
    ��    ��   : h44270
    �޸�����   : ���ⵥ��:DTS2010072901109�������Զ�������ͨ���е绰��Ϊ����״̬

  4.��    ��   : 2010��8��21��
    ��    ��   : zhoujun /40661
    �޸�����   : DTS2010081702497,ͨ��MODEM������У�ͨ��AT�ڷ�����б���,
                 û��AT������ʾ���

  5.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  6.��    ��   : 2012��12��11��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  7.��    ��   : 2013��01��29��
    ��    ��   : Y00213812
    �޸�����   : DTS2013012909872,��¼CALL�Ҷϵķ���
  8.��    ��   : 2013��9��17��
    ��    ��   : f62575
    �޸�����   : DTS2013091104858���һ�ǰ������ɵ��û�����
*****************************************************************************/
VOS_VOID  MN_CALL_CallEndReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_END_PARAM_STRU        *pstEndParm
)
{
    VOS_UINT32                          ulRet;

    /* ���д��ں�����ز���ҵ������У�������Ҷϵ绰 */
    if (VOS_FALSE == MN_CALL_AllowSupsOperation())
    {
        MN_WARN_LOG("MN_CALL_CallEndReqProc: state err ss cmd in progress ");

        MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_STATE_ERROR);

        return;

    }

    /* ���ݺ���״̬�ͷź��б�����Դ����֪ͨ����绰�Ҷ� */
    ulRet = MN_CALL_InternalCallEndReqProc(clientId, opId, callId, pstEndParm);
    if (TAF_CS_CAUSE_SUCCESS != ulRet)
    {
        MN_SendClientResponse(clientId, opId, ulRet);
        return;
    }

    /* ���û�֪ͨ�Ҷ��������ڴ��� */
    MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_SUCCESS);

    /* �����û���Ϣ���ȴ��Ҷϲ����Ľ�� */
    MN_CALL_UpdateClientId(callId, clientId);

    return;

}


/*****************************************************************************
 �� �� ��  : MN_CALL_CallAnswerReqProc
 ��������  : ��������Ӧ�ò��Ӧ������
             �ú�������鵱ǰ״̬�Ƿ��������һ�����磬���ͨ������CC����
             MNCC_SETUP_RESԭ���������
 �������  : clientId    - ����������Client��ID
             opId        - Operation ID, ��ʶ���β���
             callId      - ��Ҫ�����ĺ��е�ID
             pstAnsParam - Ӧ��������Я���Ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��6��20��
    ��    ��   : z00161729
    �޸�����   : ���ⵥDTS2010061100528
  2.��    ��   : 2010��7��21��
    ��    ��   : h44270
    �޸�����   : ���ⵥDTS2010062601120
  4.��    ��   : 2010��7��30��
    ��    ��   : h44270
    �޸�����   : ���ⵥ��:DTS2010072901109�������Զ�������ͨ���е绰��Ϊ����״̬
  5.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  6.��    ��   : 2012��12��11��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����

  7.��    ��   : 2013��12��28��
    ��    ��   : j00174725
    �޸�����   : HSUART PHASE III
  8.��    ��   : 2014��04��18��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature�޸�
  9.��    ��   : 2014��6��11��
    ��    ��   : y00245242
    �޸�����   : DTS2014060306029
*****************************************************************************/
VOS_VOID  MN_CALL_CallAnswerReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_ANS_PARAM_STRU        *pstAnsParam
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;

    enCallState          = MN_CALL_S_BUTT;
    enMptyState          = MN_CALL_MPYT_STATE_BUTT;

    /* ��ȡ��Ӧ�ĺ���״̬���������Incoming����Waiting״̬��ֱ���ϱ����� */
    MN_CALL_GetCallState(callId, &enCallState, &enMptyState);
    if ((MN_CALL_S_INCOMING != enCallState) && (MN_CALL_S_WAITING != enCallState))
    {
        MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_STATE_ERROR);

#if (FEATURE_ON == FEATURE_PTM)
        /* ��¼CS�����쳣log */
        MN_CALL_CsCallErrRecord(callId, TAF_CS_CAUSE_STATE_ERROR);
#endif

        MN_WARN_LOG1("MN_CALL_CallAnswerReqProc: call state err.state:",enCallState);
        return;
    }

    MN_CALL_StopTimer(MN_CALL_TID_RING);

    /* ����Ŀǰ����alert������Ϣ�󣬲Ż��ϱ�incoming�¼�����˴˴��������·�alert�¼� */

    /*����MN_SETUP_RESԭ�����*/
    if (VOS_OK != MN_CALL_SendCcSetupRsp(callId))
    {
        MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_UNKNOWN);

#if (FEATURE_ON == FEATURE_PTM)
        /* ��¼CS�����쳣log */
        MN_CALL_CsCallErrRecord(callId, TAF_CS_CAUSE_UNKNOWN);
#endif

        MN_ERR_LOG1("MN_CALL_CallAnswerReqProc: send clint res err.ulrslt:",TAF_CS_CAUSE_UNKNOWN);
        return;
    }

    /*�ж�ҵ���ŵ��Ƿ�׼���ã����׼���þ͸�VC���ʹ�����������*/
    if(VOS_TRUE == MN_CALL_GetTchStatus())
    {
        if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
        {
            /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-18, begin */
            /* ������Ϣ֪ͨVC������ͨ�� */
            MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);
            /* ������Ϣ֪ͨAT����ͨ��״̬ */
            MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);
            /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-18, end */
        }
        MN_CALL_SetChannelOpenFlg(VOS_TRUE);
    }

    /* �ϱ�Ӧ������ȷ�� */
    MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_SUCCESS);


    /*���¸ú��е�Client��Ϣ*/
    MN_CALL_UpdateClientId(callId, clientId);

    MN_NORM_LOG("MN_CALL_CallEndReqProc: send clint res normal.");
}

/*****************************************************************************
 �� �� ��  : MN_CALL_CallMgmtCmdReqProc
 ��������  : ��������Ӧ�ò�Ĳ���ҵ���������
             �ú�������Ӧ�÷���Ĳ���ҵ��������ͺ͵�ǰ���к��е�״̬����CC����
             һ�������ԭ�����¼�������õ����������Ӧ���Ա����յ��������Ӧ
             ʱ���жϳ����������Ƿ���ִ����ɣ����Ƿ���Ҫ���ͺ�����ԭ��
 �������  : clientId           - ����������Client��ID
             opId               - Operation ID, ��ʶ���β���
             pstCallSupsParam   - ����ҵ���������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2008��06��11��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:AT2D03709
  3.��    ��   : 2009��01��29��
    ��    ��   : x00115505
    �޸�����   : GCF����26.8.1.3.5.3 Fail,���й����йҲ��ϵ绰
  4.��    ��   : 2010��2��23��
    ��    ��   : zhoujun /z40661
    �޸�����   : NAS R7Э�������޸�
  5.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ

  6.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  7.��    ��   : 2013��03��23��
    ��    ��   : f62575
    �޸�����   : DTS2013031406373�����DTMF�����к��в��ܹҶ�����
  8.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK�������޸ĺ�����ڲ���
  9.��    ��   : 2013��9��17��
    ��    ��   : f62575
    �޸�����   : DTS2013091104858���һ�ǰ������ɵ��û�����
 10.��    ��   : 2013��07��09��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ
 11.��    ��   : 2014��04��28��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature�޸�
*****************************************************************************/
VOS_VOID  MN_CALL_CallSupsCmdReqProc(struct MsgCB *pstCallSups)
{
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    MN_CALL_CUSTOM_CFG_INFO_STRU       *pstCustomCfgAddr = VOS_NULL_PTR;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
    MN_CALL_SUPS_PARAM_STRU            *pstCallSupsParam = VOS_NULL_PTR;
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;

    pstCallSupsParam = (MN_CALL_SUPS_PARAM_STRU *)(&((MN_APP_CALL_SUPS_REQ_STRU *)pstCallSups)->stSupsPara);
    clientId         = ((MN_APP_CALL_SUPS_REQ_STRU *)pstCallSups)->usClientId;
    opId             = ((MN_APP_CALL_SUPS_REQ_STRU *)pstCallSups)->opID;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, end */

    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    /*
    ��ǰ���в���ҵ�������
    ����������Ϊ�Ҷ����к���
    */
    if (VOS_FALSE == MN_CALL_AllowSupsOperation())
    {
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-28, begin */
        if ((MN_CALL_SUPS_CMD_REL_ALL_CALL != pstCallSupsParam->enCallSupsCmd)
#if (FEATURE_ON == FEATURE_ECALL)
         && (MN_CALL_SUPS_CMD_REL_ECALL    != pstCallSupsParam->enCallSupsCmd)
#endif
        )
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-28, end */
        {
            MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err ss cmd in progress ");

            TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

            TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                      opId,
                                                      pstCallSupsParam->callId,
                                                      TAF_CS_CAUSE_STATE_ERROR);

            return;

        }

        TAF_CALL_PreProcRelAllCall();

    }

    switch(pstCallSupsParam->enCallSupsCmd)
    {
        case MN_CALL_SUPS_CMD_REL_HELD_OR_UDUB:
            MN_CALL_CallSupsCmdRelHoldOrUdubReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_REL_ACT_ACPT_OTH:
            MN_CALL_CallSupsCmdRelActAcptOthReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_REL_CALL_X:
            MN_CALL_CallSupsCmdRelCallXReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_REL_ALL_CALL:
            MN_CALL_CallSupsCmdRelAllCallReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH:
            MN_CALL_CallSupsCmdHoldActAcptOthReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X:
            MN_CALL_CallSupsCmdHoldAllExcptXReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_BUILD_MPTY:
            MN_CALL_CallSupsCmdBuildMptyReqProc(clientId, opId, pstCallSupsParam);
            break;
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
        case MN_CALL_SUPS_CMD_DEFLECT_CALL:
            if ( MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCallDeflectionSupportFlg)
            {
                MN_CALL_CallSupsCmdDeflectCallReqProc(clientId, opId, pstCallSupsParam);
            }
            else
            {
                TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

                TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                          opId,
                                                          pstCallSupsParam->callId,
                                                          TAF_CS_CAUSE_STATE_ERROR);
            }

            break;

        case MN_CALL_SUPS_CMD_ACT_CCBS:
            if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
            {
                MN_CALL_SupsCmdCcbsReqProc(clientId, opId, pstCallSupsParam);
            }
            else
            {
                TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

                TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                          opId,
                                                          pstCallSupsParam->callId,
                                                          TAF_CS_CAUSE_STATE_ERROR);
            }
            break;
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */
        /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

        case MN_CALL_SUPS_CMD_ECT:
            MN_CALL_CallSupsCmdEctReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_REL_ALL_EXCEPT_WAITING_CALL:
            MN_CALL_CallSupsCmdRelAllExceptWaitCallReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_REL_HELD:
            MN_CALL_CallSupsCmdRelHeldReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_REL_ACTIVE:
            MN_CALL_CallSupsCmdRelActiveReqProc(clientId, opId, pstCallSupsParam);
            break;

        /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-22, begin */
        #if (FEATURE_ON == FEATURE_ECALL)
        case MN_CALL_SUPS_CMD_REL_ECALL:
            TAF_CALL_EcallSupsCmdRelReqProc(clientId, opId, pstCallSupsParam);
            break;
        #endif
        /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-22, end */

        default:
            break;
    }

}

/* Deleted by l00198894 for V9R1 STK����, 2013/07/11 */

/*****************************************************************************
 �� �� ��  : MN_CALL_QryAls
 ��������  : ��ȡ��ǰʹ�õ���·��
 �������  : clientId           - ����������Client��ID
             opId               - Operation ID, ��ʶ���β���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��17��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��22��
    ��    ��   : z00220246
    �޸�����   : DSDA Phase II,����SenderPid����ϱ���ClientId

*****************************************************************************/
VOS_VOID  MN_CALL_QryAls(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
)
{
    MN_CALL_QRY_ALS_CNF_STRU       stQryAlsCnf;

    stQryAlsCnf.ClientId = MN_GetRealClientId(clientId, WUEPS_PID_TAF);
    stQryAlsCnf.OpId     = opId;
    stQryAlsCnf.ulRet    = TAF_ERR_NO_ERROR;
    stQryAlsCnf.enEvent  = MN_CALL_EVT_QRY_ALS_CNF;

    stQryAlsCnf.enAlsLine = MN_CALL_GetAlsLineInfo();

    MN_SendReportMsg(MN_CALLBACK_CS_CALL,(VOS_UINT8*)&stQryAlsCnf,sizeof(stQryAlsCnf));

}
/*****************************************************************************
 �� �� ��  : MN_CALL_QryUus1Info
 ��������  : ��ȡ��ǰ���к��е���Ϣ
 �������  : clientId           - ����������Client��ID
             opId               - Operation ID, ��ʶ���β���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��17��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��22��
    ��    ��   : z00220246
    �޸�����   : DSDA Phase II,����SenderPid����ϱ���ClientId
  3.��    ��   : 2013��5��6��
    ��    ��   : s00217060
    �޸�����  : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
*****************************************************************************/
VOS_VOID  MN_CALL_QryUus1Info(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
)
{
    TAF_PH_QRY_UUS1_INFO_CNF_STRU       stQryUus1Cnf;
    VOS_UINT32                          ulRet;
    /* Modified by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, begin */
    VOS_UINT32                          ulChkCuus1IFlg;
    VOS_UINT32                          ulChkCuus1UFlg;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;

    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    ulChkCuus1IFlg  = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                                TAF_SDC_RPT_CMD_CUUS1I);

    ulChkCuus1UFlg  = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                                TAF_SDC_RPT_CMD_CUUS1U);

    PS_MEM_SET(&stQryUus1Cnf, 0, sizeof(stQryUus1Cnf));
    stQryUus1Cnf.ClientId = MN_GetRealClientId(clientId, WUEPS_PID_TAF);
    stQryUus1Cnf.OpId     = opId;
    stQryUus1Cnf.ulRet    = TAF_ERR_NO_ERROR;
    stQryUus1Cnf.enEvent  = MN_CALL_EVT_QRY_UUS1_INFO_CNF;

    /* ��ѯ���������CUUS1I��CUUS1U�Ƿ���Ҫ�����ϱ����� */
    stQryUus1Cnf.aenSetType[0] = ulChkCuus1IFlg;
    stQryUus1Cnf.aenSetType[1] = ulChkCuus1UFlg;
    /* Modified by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, begin */

    ulRet = MN_CALL_GetCcUus1Info(&stQryUus1Cnf.ulActNum,stQryUus1Cnf.stUus1Info);

    if (VOS_OK != ulRet)
    {
        stQryUus1Cnf.ulRet = TAF_ERR_AT_ERROR;
    }

    MN_SendReportMsg(MN_CALLBACK_CS_CALL,(VOS_UINT8*)&stQryUus1Cnf,sizeof(stQryUus1Cnf));
}

/*****************************************************************************
 �� �� ��  : MN_CALL_SetAls
 ��������  : ������·��
 �������  : clientId           - ����������Client��ID
             opId               - Operation ID, ��ʶ���β���
             pstCallInfoParam   - ����ҵ���������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��17��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��22��
    ��    ��   : z00220246
    �޸�����   : DSDA Phase II,����SenderPid����ϱ���ClientId
*****************************************************************************/
VOS_VOID  MN_CALL_SetAls(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_SET_ALS_PARAM_STRU         *pstAls
)
{
    MN_CALL_SET_ALS_CNF_STRU       stAlsCnf;
    VOS_UINT32                     ulRet;

    stAlsCnf.ClientId = MN_GetRealClientId(clientId, WUEPS_PID_TAF);
    stAlsCnf.OpId     = opId;
    stAlsCnf.ulRet    = TAF_ERR_NO_ERROR;
    stAlsCnf.enEvent  = MN_CALL_EVT_SET_ALS_CNF;

    ulRet = MN_CALL_UpdateAlsLineInfo(pstAls->enAlsLine,VOS_TRUE);

    if (VOS_OK != ulRet )
    {
        stAlsCnf.ulRet = TAF_ERR_UNSPECIFIED_ERROR;
    }

    MN_SendReportMsg(MN_CALLBACK_CS_CALL,(VOS_UINT8*)&stAlsCnf,sizeof(stAlsCnf));

}
/*****************************************************************************
 �� �� ��  : MN_CALL_SetUus1Info
 ��������  : ��ȡ��ǰ���к��е���Ϣ
 �������  : clientId           - ����������Client��ID
             opId               - Operation ID, ��ʶ���β���
             pstCallInfoParam   - ����ҵ���������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��17��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��22��
    ��    ��   : z00220246
    �޸�����   : DSDA Phase II,����SenderPid����ϱ���ClientId
  3.��    ��   : 2013��4��8��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C��

*****************************************************************************/
VOS_VOID  MN_CALL_SetUus1Info(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_UUS1_PARAM_STRU            *pstUus1Info
)
{
    VOS_UINT32                          i;
    TAF_PH_SET_UUS1_INFO_CNF_STRU       stUus1Cnf;

    /* Modified by s00217060 for �����ϱ�AT�������������C��, 2013-4-8, begin */
    /* ��ȡ�������������ϱ���ȫ�ֱ��� */
    VOS_UINT32                          ulCuus1URptCmdStatus;
    VOS_UINT32                          ulCuus1IRptCmdStatus;

    /* ����CUUS1I��CUUS1U��Ӧ��SDCȫ�ֱ��� */
    if (MN_CALL_CUUS1_ENABLE == pstUus1Info->enCuus1UFlg)
    {
        ulCuus1URptCmdStatus  = VOS_TRUE;
    }
    else
    {
        ulCuus1URptCmdStatus  = VOS_FALSE;
    }

    if (MN_CALL_CUUS1_ENABLE == pstUus1Info->enCuus1IFlg)
    {
        ulCuus1IRptCmdStatus  = VOS_TRUE;
    }
    else
    {
        ulCuus1IRptCmdStatus  = VOS_FALSE;
    }

    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUUS1U, ulCuus1URptCmdStatus);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUUS1I, ulCuus1IRptCmdStatus);
    /* Modified by s00217060 for �����ϱ�AT�������������C��, 2013-4-8, end */

    stUus1Cnf.ClientId = MN_GetRealClientId(clientId, WUEPS_PID_TAF);
    stUus1Cnf.OpId     = opId;
    stUus1Cnf.ulRet    = TAF_ERR_NO_ERROR;
    stUus1Cnf.enEvent  = MN_CALL_EVT_SET_UUS1_INFO_CNF;

    for (i = 0; i < pstUus1Info->ulActNum; i++ )
    {
        /* ���±�����CC�е������Ϣ��UUS1��Ϣ */
        if (MN_ERR_NO_ERROR != MN_CALL_UpdateCcUus1Info(pstUus1Info->enSetType[i],
                                                       &(pstUus1Info->stUus1Info[i])) )
        {
            stUus1Cnf.ulRet = TAF_ERR_PARA_ERROR;
            break;
         }
    }

    MN_SendReportMsg(MN_CALLBACK_CS_CALL,(VOS_UINT8*)&stUus1Cnf,sizeof(stUus1Cnf));

}

/*****************************************************************************
 �� �� ��  : MN_CALL_AddEmerNumsWithUsimToReportList
 ��������  : ��Э��涨���п�ʱ�Ľ�������������б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE �б�����
             VOS_FALSE �б�δ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��11��
    ��    ��   : w00166186
    �޸�����   : AT&T&DCM��Ŀ��������
  2.��    ��   : 2013��07��222��
    ��    ��   : j00177245
    �޸�����   : ����Coverity
  3.��    ��   : 2013��12��16��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ
  4.��    ��   : 2014��12��20��
    ��    ��   : l00198894
    �޸�����   : DTS2014110508255: �����п��ҷ���������ʱ���������ƹ���
*****************************************************************************/
VOS_UINT32 MN_CALL_AddEmerNumsWithUsimToReportList(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
)
{
    VOS_UINT8                           i;
    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */
    VOS_CHAR                          **pucEmcNumsWithUsim  = VOS_NULL_PTR;

    pucEmcNumsWithUsim  = TAF_SDC_GetCallEmerNumsWithUsimTblAddr();

    /* ��Э�鶨��Ľ��������������Ϣ */
    for (i = 0; i < TAF_SDC_NUMOF_EMER_NUMS_WITH_USIM; i++)
    {
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ulMcc                  = 0xffffffff;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory             = MN_CALL_ECC_NUM_INVALID_CATEGORY;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucValidSimPresent      = MN_CALL_ECC_NUM_VALID_SIM_PRESENT;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucAbnormalServiceFlg   = VOS_FALSE;

        if (MN_ERR_NO_ERROR != TAF_STD_ConvertAsciiNumberToBcd(pucEmcNumsWithUsim[i],
                            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].aucEccNum,
                            &pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucEccNumLen))
        {
            MN_WARN_LOG("MN_CALL_AddEmerNumsWithUsimToReportList: TAF_STD_ConvertAsciiNumberToBcd Fail.");
        }

        pstEccNumInfo->ulEccNumCount++;

        /* �б����� */
        if (MN_CALL_MAX_EMC_NUM == pstEccNumInfo->ulEccNumCount)
        {
            return VOS_TRUE;
        }
    }
    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_AddEmerNumsNoUsimToReportList
 ��������  : ��Э��涨���޿�ʱ�Ľ�������������б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE �б�����
             VOS_FALSE �б�δ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��11��
    ��    ��   : w00166186
    �޸�����   : AT&T&DCM��Ŀ��������
  2.��    ��   : 2013��07��222��
    ��    ��   : j00177245
    �޸�����   : ����Coverity
  3.��    ��   : 2013��12��16��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ
  4.��    ��   : 2014��12��20��
    ��    ��   : l00198894
    �޸�����   : DTS2014110508255: �����п��ҷ���������ʱ���������ƹ���

*****************************************************************************/
VOS_UINT32 MN_CALL_AddEmerNumsNoUsimToReportList(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
)
{
    VOS_UINT8                           i;
    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */
    VOS_CHAR                          **pucEmcNumsNoUsim    = VOS_NULL_PTR;

    pucEmcNumsNoUsim    = TAF_SDC_GetCallEmerNumsNoUsimTblAddr();

    /* ��Э�鶨����޿�ʱ���������� */
    for (i = 0; i < TAF_SDC_NUMOF_EMER_NUMS_NO_USIM; i++)
    {
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ulMcc                  = 0xffffffff;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory             = MN_CALL_ECC_NUM_INVALID_CATEGORY;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucValidSimPresent      = MN_CALL_ECC_NUM_VALID_SIM_ABSENT;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucAbnormalServiceFlg   = VOS_FALSE;

        if (MN_ERR_NO_ERROR != TAF_STD_ConvertAsciiNumberToBcd(pucEmcNumsNoUsim[i],
                            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].aucEccNum,
                            &pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucEccNumLen))
        {
            MN_WARN_LOG("MN_CALL_AddEmerNumsNoUsimToReportList: TAF_STD_ConvertAsciiNumberToBcd Fail.");
        }
    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */

        pstEccNumInfo->ulEccNumCount++;

        /* �б����� */
        if (MN_CALL_MAX_EMC_NUM == pstEccNumInfo->ulEccNumCount)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_AddEccNumsInUsimToReportList
 ��������  : ��SIM���еĽ�������������б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE �б�����
             VOS_FALSE �б�δ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��11��
    ��    ��   : w00166186
    �޸�����   : AT&T&DCM��Ŀ��������
  2.��    ��   : 2013��6��5��
    ��    ��   : w00242748
    �޸�����   : SVLTE��USIM�ӿ�����
  3.��    ��   : 2013��10��11��
    ��    ��   : z00161729
    �޸�����   : DTS2013101103670:2G sim��at^xlema��ѯδ�ϱ���EFecc�н������к���
  4.��    ��   : 2014��12��20��
    ��    ��   : l00198894
    �޸�����   : DTS2014110508255: �����п��ҷ���������ʱ���������ƹ���
*****************************************************************************/
VOS_UINT32 MN_CALL_AddEccNumsInUsimToReportList(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
)
{
    SI_PB_ECC_DATA_STRU                *pstEccData;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           i;

    /* �����еĽ��������������Ϣ */
    pstEccData = (SI_PB_ECC_DATA_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(SI_PB_ECC_DATA_STRU));
    if (VOS_NULL_PTR == pstEccData)
    {
        MN_WARN_LOG("MN_CALL_AddEccNumsInUsimToReportList: Alloc Mem Fail.");
        return VOS_FALSE;
    }
    else
    {
        /* ��ȡUSIM�еĽ������к��� */
        PS_MEM_SET(pstEccData, 0, sizeof(SI_PB_ECC_DATA_STRU));
        NAS_PBAPI_GetEccNumber(pstEccData);

        for (i = 0; i < pstEccData->ulReocrdNum; i++)
        {
            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ulMcc                  = 0xffffffff;

            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory = 0;

            /* �ж�ֵ����Ч�� */
            ulResult = TAF_STD_IsValidEmerCategory(pstEccData->astEccRecord[i].ucESC);

            if ( (VOS_TRUE == pstEccData->astEccRecord[i].bESC)
              && (VOS_TRUE == ulResult))
            {
                pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory         = (pstEccData->astEccRecord[i].ucESC & MN_CALL_EMER_CATEGORG_VAL_MAX);
            }

            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucValidSimPresent      = MN_CALL_ECC_NUM_VALID_SIM_PRESENT;
            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucAbnormalServiceFlg   = VOS_FALSE;
            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucEccNumLen            = USIM_ECC_LEN;
            (VOS_VOID)VOS_MemCpy(pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].aucEccNum,
                       pstEccData->astEccRecord[i].aucEccCode,
                       USIM_ECC_LEN);

            pstEccNumInfo->ulEccNumCount++;

            /* �б����� */
            if (MN_CALL_MAX_EMC_NUM == pstEccNumInfo->ulEccNumCount)
            {
                /* �ڴ��ͷ� */
                PS_MEM_FREE(WUEPS_PID_TAF,pstEccData);
                return VOS_TRUE;
            }
        }

        /* �ڴ��ͷ� */
        PS_MEM_FREE(WUEPS_PID_TAF,pstEccData);
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_AddMmEccNumsToReportList
 ��������  : ��MM���ϱ��Ľ�������������б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE �б�����
             VOS_FALSE �б�δ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��11��
    ��    ��   : w00166186
    �޸�����   : AT&T&DCM��Ŀ��������
  2.��    ��   : 2013��12��16��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ
  3.��    ��   : 2014��12��20��
    ��    ��   : l00198894
    �޸�����   : DTS2014110508255: �����п��ҷ���������ʱ���������ƹ���

*****************************************************************************/
VOS_UINT32 MN_CALL_AddMmEccNumsToReportList(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
)
{
    VOS_UINT8                           i;
    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */
    TAF_SDC_MM_EMERGENCY_LIST_STRU     *pstMmCallEmerNumList    = VOS_NULL_PTR;

    pstMmCallEmerNumList    = TAF_SDC_GetMmCallEmerNumList();

    /* ��ע��������Ľ��������������Ϣ */
    for (i = 0; i < pstMmCallEmerNumList->ucEmergencyNumber; i++)
    {
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ulMcc                  = pstMmCallEmerNumList->ulMcc;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory             = pstMmCallEmerNumList->astEmergencyLists[i].ucCategoryValue;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucValidSimPresent      = MN_CALL_ECC_NUM_VALID_SIM_PRESENT;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucAbnormalServiceFlg   = VOS_FALSE;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucEccNumLen            = pstMmCallEmerNumList->astEmergencyLists[i].ucEmcNumLen;

        (VOS_VOID)VOS_MemCpy(pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].aucEccNum,
                   pstMmCallEmerNumList->astEmergencyLists[i].aucEmergencyList,
                   pstMmCallEmerNumList->astEmergencyLists[i].ucEmcNumLen);

        pstEccNumInfo->ulEccNumCount++;

        /* �б����� */
        if (MN_CALL_MAX_EMC_NUM == pstEccNumInfo->ulEccNumCount)
        {
            return VOS_TRUE;
        }
    }
    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_AddCustomEccNumsToReportList
 ��������  : ��APP���ƵĽ�������������б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE �б�����
             VOS_FALSE �б�δ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��11��
    ��    ��   : w00166186
    �޸�����   : AT&T&DCM��Ŀ��������
  2.��    ��   : 2013��12��16��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ
  3.��    ��   : 2014��12��20��
    ��    ��   : l00198894
    �޸�����   : DTS2014110508255: �����п��ҷ���������ʱ���������ƹ���

*****************************************************************************/
VOS_UINT32 MN_CALL_AddCustomEccNumsToReportList(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
)
{
    VOS_UINT8                           i;
    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */
    TAF_SDC_CUSTOM_ECC_CTX_STRU        *pstCustomCallEmerNumCtx    = VOS_NULL_PTR;

    pstCustomCallEmerNumCtx = TAF_SDC_GetCustomCallEccNumCtx();

    /* ��APP���ƵĽ��������������Ϣ */
    for (i = 0; i < pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount; i++)
    {
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ulMcc
            = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ulMcc;

        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory
            = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucCategory;

        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucValidSimPresent
            = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucValidSimPresent;

        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucAbnormalServiceFlg
            = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucAbnormalServiceFlg;

        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucEccNumLen
            = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucEccNumLen;

        (VOS_VOID)VOS_MemCpy(pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].aucEccNum,
                   pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].aucEccNum,
                   pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucEccNumLen);

        pstEccNumInfo->ulEccNumCount++;

        /* �б����� */
        if (MN_CALL_MAX_EMC_NUM == pstEccNumInfo->ulEccNumCount)
        {
            return VOS_TRUE;
        }
    }
    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_ReportEccNumList
 ��������  : ��AT�ϱ��������б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��11��
    ��    ��   : w00166186
    �޸�����   : AT&T&DCM��Ŀ��������
  2.��    ��   : 2012��12��11��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  3.��    ��   : 2013��4��3��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2013��01��23��
    ��    ��   : Y00213812
    �޸�����   : DTS2013012309236,��ȡ��������
*****************************************************************************/
VOS_VOID MN_CALL_ReportEccNumList(VOS_VOID)
{
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo = VOS_NULL_PTR;
    VOS_UINT16                          usLen;
    /* Modified by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, begin */
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl          = VOS_NULL_PTR;

    pstCurcRptCtrl                  = TAF_SDC_GetCurcRptCtrl();



    /* �ж������ϱ��Ƿ�� */
    if (VOS_FALSE == TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_XLEMA))
    {
        return;
    }
    /* Modified by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, end */

    pstEccNumInfo = (MN_CALL_ECC_NUM_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_CALL_ECC_NUM_INFO_STRU));
    if (VOS_NULL_PTR == pstEccNumInfo)
    {
        MN_WARN_LOG("MN_CALL_ReportEccNumList: Alloc Mem Fail.");
        return;
    }

    /* ��Ϣ��ʼ�� */
    PS_MEM_SET(pstEccNumInfo, 0, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    pstEccNumInfo->enEvent    = MN_CALL_EVT_ECC_NUM_IND;
    pstEccNumInfo->usClientId = MN_GetRealClientId(MN_CLIENT_ALL, WUEPS_PID_TAF);

    /* ��ȡ�������б� */
    MN_CALL_GetEccNumList(pstEccNumInfo);

    usLen = (VOS_UINT16)sizeof(MN_CALL_ECC_NUM_INFO_STRU);

    /*  �ϱ�AT */
    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (TAF_UINT8 *)pstEccNumInfo, usLen);

    /* �ڴ��ͷ� */
    PS_MEM_FREE(WUEPS_PID_TAF,pstEccNumInfo);

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_SaveCustomEccNum
 ��������  : ��APP���ƵĽ��������뱣�浽ȫ�ֱ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��11��
    ��    ��   : w00166186
    �޸�����   : AT&T&DCM��Ŀ��������
  2.��    ��   : 2013��12��16��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ
  3.��    ��   : 2014��12��20��
    ��    ��   : l00198894
    �޸�����   : DTS2014110508255: �����п��ҷ���������ʱ���������ƹ���

*****************************************************************************/
VOS_VOID MN_CALL_SaveCustomEccNum(
    MN_CALL_APP_CUSTOM_ECC_NUM_REQ_STRU*    pstCustomEccNumReq
)
{
    VOS_UINT8                               ucIndex;
    TAF_SDC_CUSTOM_ECC_NUM_STRU            *pstCustomEccNum = VOS_NULL_PTR;

    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */
    TAF_SDC_CUSTOM_ECC_CTX_STRU            *pstCustomCallEmerNumCtx    = VOS_NULL_PTR;

    pstCustomCallEmerNumCtx = TAF_SDC_GetCustomCallEccNumCtx();

    /* ��ǰPLMN�����ڶ��ƽ��������룬�����ǰ�б� */
    if ((1 == pstCustomEccNumReq->ucIndex)
     && (1 == pstCustomEccNumReq->ucTotal)
     && (MN_CALL_INVALID_CATEGORY == pstCustomEccNumReq->ucCategory))
    {
        PS_MEM_SET(&pstCustomCallEmerNumCtx->stCustomEccNumList, 0, sizeof(TAF_SDC_CUSTOM_ECC_NUM_LIST_STRU));
    }
    else
    {
        /* ���涨�ƺ��뵽ȫ�ֱ��� */
        ucIndex         = pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount;
        pstCustomEccNum = &(pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[ucIndex]);

        pstCustomEccNum->ucCategory             = pstCustomEccNumReq->ucCategory;
        pstCustomEccNum->ucValidSimPresent      = pstCustomEccNumReq->ucSimPresent;
        pstCustomEccNum->ulMcc                  = pstCustomEccNumReq->ulMcc;
        pstCustomEccNum->ucEccNumLen            = pstCustomEccNumReq->stEccNum.ucNumLen;
        pstCustomEccNum->ucAbnormalServiceFlg   = pstCustomEccNumReq->ucAbnormalServiceFlg;

        (VOS_VOID)VOS_MemCpy(pstCustomEccNum->aucEccNum,
                   pstCustomEccNumReq->stEccNum.aucBcdNum,
                   pstCustomEccNumReq->stEccNum.ucNumLen);

        (pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount)++;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_RcvTafEccNumReq
 ��������  : ���ƽ�������������Ĵ���
 �������  : pstCustomEccNumReq APP���ƽ���������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��11��
    ��    ��   : w00166186
    �޸�����   : AT&T&DCM��Ŀ��������
  2.��    ��   : 2013��12��16��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ
  3.��    ��   : 2014��12��20��
    ��    ��   : l00198894
    �޸�����   : DTS2014110508255: �����п��ҷ���������ʱ���������ƹ���

*****************************************************************************/
VOS_VOID MN_CALL_RcvTafEccNumReq(
    MN_CALL_APP_CUSTOM_ECC_NUM_REQ_STRU*    pstCustomEccNumReq
)
{
    VOS_UINT32                              ulRst;
    MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU   stNvimCustomEccNumList;
    VOS_UINT8                               i;
    MN_CALL_CUSTOM_CFG_INFO_STRU           *pstCustomCfg       = VOS_NULL_PTR;
    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */
    TAF_SDC_CUSTOM_ECC_NUM_STRU            *pstCustomEccNum    = VOS_NULL_PTR;
    TAF_SDC_CUSTOM_ECC_CTX_STRU            *pstCustomCallEmerNumCtx    = VOS_NULL_PTR;

    pstCustomCallEmerNumCtx = TAF_SDC_GetCustomCallEccNumCtx();

    pstCustomCfg      = MN_CALL_GetCustomCfgInfo();

    /* ���indexΪ1,��ն����б�, ��Ƕ��ƿ�ʼ */
    if (1 == pstCustomEccNumReq->ucIndex)
    {
        PS_MEM_SET(&(pstCustomCallEmerNumCtx->stCustomEccNumList), 0, sizeof(TAF_SDC_CUSTOM_ECC_NUM_LIST_STRU));

        pstCustomCallEmerNumCtx->ucCustomSetFlg = VOS_TRUE;
    }

    /* ��ǰ���ڶ��ƹ��� */
    if (VOS_FALSE == pstCustomCallEmerNumCtx->ucCustomSetFlg)
    {
        /* ���������� */
        return;
    }

    /* ���涨�ƺ��뵽ȫ�ֱ��� */
    MN_CALL_SaveCustomEccNum(pstCustomEccNumReq);

    /* ��INDEX = TOTAL���߶��ƺ��������ﵽ�����Ϊ���ζ��ƽ��� */
    if ((pstCustomEccNumReq->ucIndex == pstCustomEccNumReq->ucTotal)
     || (TAF_SDC_MAX_CUSTOM_ECC_NUM == pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount))
    {
        (VOS_VOID)VOS_MemSet(&stNvimCustomEccNumList, 0, sizeof(MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU));

        stNvimCustomEccNumList.ucEccNumCount = pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount;

        for (i = 0; i < pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount; i++)
        {
            pstCustomEccNum = &(pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i]);

            stNvimCustomEccNumList.astCustomEccNumList[i].ucCategory
                = pstCustomEccNum->ucCategory;
            stNvimCustomEccNumList.astCustomEccNumList[i].ulMcc
                = pstCustomEccNum->ulMcc;
            stNvimCustomEccNumList.astCustomEccNumList[i].ucValidSimPresent
                = pstCustomEccNum->ucValidSimPresent;
            stNvimCustomEccNumList.astCustomEccNumList[i].ucAbnormalServiceFlg
                = pstCustomEccNum->ucAbnormalServiceFlg;
            stNvimCustomEccNumList.astCustomEccNumList[i].ucEccNumLen
                = pstCustomEccNum->ucEccNumLen;
            (VOS_VOID)VOS_MemCpy(stNvimCustomEccNumList.astCustomEccNumList[i].aucEccNum,
                       pstCustomEccNum->aucEccNum,
                       pstCustomEccNum->ucEccNumLen);
        }

        /* ��Ƕ��ƽ��� */
        pstCustomCallEmerNumCtx->ucCustomSetFlg = VOS_FALSE;
        /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */

        /* ��ȫ�ֱ���������б�д��NV */
        ulRst = NV_Write(en_NV_Item_CUSTOM_ECC_NUM_LIST,(VOS_VOID*)&stNvimCustomEccNumList,sizeof(MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU));
        if (NV_OK != ulRst)
        {
            MN_ERR_LOG("MN_CALL_RcvTafEccNumReq:Write NVIM Error");
        }

        /* �������ϱ�����NV���ش� */
        if (VOS_TRUE == pstCustomCfg->ucReportEccNumFlg)
        {
            /* ��AT�ϱ���ǰ���еĽ��������� */
            MN_CALL_ReportEccNumList();
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_MakeNewCall
 ��������  : �����µ�����
 �������  : MN_CALL_TYPE_ENUM_U8                enCallType   �û��·����º�������
 �������  : MN_CALL_ID_T                        *pNewCallId  �º���CALLID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��21��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  3.��    ��   : 2012��12��11��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  4.��    ��   : 2013��12��23��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ
*****************************************************************************/
VOS_UINT32 MN_CALL_MakeNewCall(
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_ID_T                       *pNewCallId
)
{
    MN_CALL_ID_T                        callId;
    /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */

    /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */

    /* ��ȡ���Կ���NV��ַ */

    /* ��MN Callģ���Ϸ���CallId MN_CALL_AllocCallId */

    /* ���NV�������Ƿ���������� MN_CALL_CheckNVAllowCallOrig */

    /* ����Ƿ���Է���/����һ���µĺ��� MN_CALL_IsAllowToMakeNewCall */

    /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-23, begin */
    /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-23, end */

    if (VOS_FALSE == MN_CALL_CheckNVAllowCallOrig(enCallType))
    {
        MN_NORM_LOG("MN_CALL_MakeNewCall: Fail to MN_CALL_CheckNVAllowCallOrig.");
        return TAF_CS_CAUSE_NOT_ALLOW;
    }


    /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */

    /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */

    /* ��MN Callģ���Ϸ���CallId */
    if (VOS_OK != MN_CALL_AllocCallId(&callId))
    {
        MN_WARN_LOG("MN_CALL_MakeNewCall: Null Point.");
        return TAF_CS_CAUSE_NO_CALL_ID;
    }

    *pNewCallId = callId;

    /* ������������ʵ����״̬����HELD��IDLE����ܾ��º��� */
    if (VOS_TRUE != MN_CALL_IsAllowToMakeNewCall(callId, MN_CALL_DIR_MO))
    {
        MN_WARN_LOG("MN_CALL_MakeNewCall: ONLY SUPPORT ONE CALL.");
        MN_CALL_FreeCallId(callId);
        return TAF_CS_CAUSE_NOT_ALLOW;
    }

    return TAF_CS_CAUSE_SUCCESS;
}



/*****************************************************************************
 �� �� ��  : MN_CALL_RcvAtClprGetReq
 ��������  : ����Դ�����������
 �������  : MN_CALL_APP_REQ_MSG_STRU            *pstCallMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��09��18��
    ��    ��   : y00213812
    �޸�����   : STK&DCM ��Ŀ��������

*****************************************************************************/
VOS_VOID MN_CALL_RcvAtClprGetReq(MN_CALL_APP_REQ_MSG_STRU            *pstCallMsg)
{
    MN_CALL_CLPR_GET_CNF_STRU           stGetClprCnf;

    PS_MEM_SET(&stGetClprCnf, 0x00, sizeof(MN_CALL_CLPR_GET_CNF_STRU));

    /* ����MN_CALL_EVT_CLPR_GET_CNF��Ϣ */
    stGetClprCnf.stAppCtrl.usClientId = pstCallMsg->clientId;
    stGetClprCnf.stAppCtrl.ucOpId     = pstCallMsg->opId;
    stGetClprCnf.ulRet                = TAF_ERR_ERROR;
    stGetClprCnf.enEvent              = MN_CALL_EVT_CLPR_SET_CNF;

    /* ��������CALLID�Ƿ����,����Ϊ���� */

    if (VOS_TRUE == MN_CALL_CheckCallEntityExist(pstCallMsg->callId))
    {
        MN_CALL_ReadCallEntityRedirectInfo(pstCallMsg->callId, &stGetClprCnf);
    }

    MN_SendReportMsg(MN_CALLBACK_CS_CALL,
                    (VOS_UINT8*)&stGetClprCnf,
                    sizeof(MN_CALL_CLPR_GET_CNF_STRU));

}


/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */

/*****************************************************************************
 �� �� ��  : MN_CALL_StkCallOrigReqProc
 ��������  : ��������STKģ��ĺ�������
             ��ע������AT������д�����MN_CALL_CallOrigReqProc����������:
             1. �����Ϣ���Ͳ�һ������Ҫ����MN_CALL_CallOrigReqProc�Ĵ�������
             2. STK���в���Ҫ��FDN��飻
             3. STK���еĽ����������ͼ�鲻��Ҫ���EFECC�ļ���
             4. Ҫ���¼OPID������͸����STKģ�飬�����Ƿ�CALL����Ӧ
 �������  : pstOrigParam   - STK����������Я���Ĳ���
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��20��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�

  3.��    ��   : 2012��10��29��
    ��    ��   : l00198894
    �޸�����   : DTS2012100901666: �޸ı��к���ṹ��
  4.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  5.��    ��   : 2013��5��16��
    ��    ��   : w00176964
    �޸�����   : SS FDN&Call Control��Ŀ:MN_CALL_CallControlEnvelopeReq����client ID����
  6.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK�������޸ĺ�����ڲ���
  7.��    ��   : 2013��07��20��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ
  8.��    ��   : 2013��12��14��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseIII ��Ŀ:FDN CALLcontrol�������Ƶ�SPM
  9.��    ��   : 2013��12��16��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ
  10.��    ��   : 2016��8��22��
    ��    ��   : h00360002
    �޸�����   : ɾ��TAF����STK CALL���ز�����
*****************************************************************************/
VOS_VOID MN_CALL_StkCallOrigReqProc(struct MsgCB * pstMsg)
{
    /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */
    VOS_UINT32                          ulRet;
    MN_CALL_ID_T                        NewcallId;
    MN_CALL_ID_T                        callId;

    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */
    VOS_BOOL                            bSupported;
    /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */
    /* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
    MN_APP_CALL_CALLORIG_REQ_STRU      *pstOrigParam = VOS_NULL_PTR;

    pstOrigParam = (MN_APP_CALL_CALLORIG_REQ_STRU *)pstMsg;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, end */

    NewcallId = 0;

    /* ��ȡ���Կ���NV��ַ */

    /* ��MN Callģ���Ϸ���CallId MN_CALL_AllocCallId */

    /* ���NV�������Ƿ���������� MN_CALL_CheckNVAllowCallOrig */

    /* ����Ƿ���Է���/����һ���µĺ��� MN_CALL_IsAllowToMakeNewCall */

    /*
       �ǽ������к��룬��ֱ�ӷ���EMERGENTCY SETUP CALL��Ϣ��CC��������:
       2.����EMERGENTCY SETUP CALL��Ϣ��CC��
       3.״̬Ǩ�Ƶ�MN_CALL_S_DIALING
       4.�㲥�ϱ�Ӧ������ȷ���¼�MN_CALL_EVT_NO_ERROR,
       5.�㲥���з���(ORIG)MN_CALL_EVT_ORIG
       6.��STK������ʱ��Ӧ��Ϣ��ԭ��ֵΪMN_ERR_NO_ERROR
       7.�˳�����
    */

     /*
       1.����SETUP CALL��Ϣ��CC��
       2.״̬Ǩ�Ƶ�MN_CALL_S_DIALING
       3.�㲥�ϱ�Ӧ������ȷ���¼�MN_CALL_EVT_NO_ERROR,
       4.�㲥���з���(ORIG)MN_CALL_EVT_ORIG
       5.��STK������ʱ��Ӧ��Ϣ��ԭ��ֵΪMN_ERR_NO_ERROR
       6.�˳�����

     */


    /* ��������У�֪ͨ���з��𷽺����쳣���� */
    ulRet = MN_CALL_MakeNewCall(pstOrigParam->enCallType, &NewcallId);
    if (TAF_CS_CAUSE_SUCCESS != ulRet)
    {
        MN_NORM_LOG("MN_CALL_StkCallOrigReqProc: Fail to MN_CALL_MakeNewCall.");
        /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-20, begin */
        TAF_CALL_SendCallOrigCnf(pstOrigParam->usClientId,
                                 pstOrigParam->opID,
                                 pstOrigParam->callID,
                                 ulRet);
        /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-20, end */

#if (FEATURE_ON == FEATURE_PTM)
        /* ��¼CS�����쳣log */
        MN_CALL_CsCallErrRecord(NewcallId, ulRet);
#endif

        return;
    }
    callId = NewcallId;

    /* ����ǽ������У���ֱ�ӷ���CC,�������л���Ҫ����һϵ���ж� */
    if (MN_CALL_TYPE_EMERGENCY == pstOrigParam->enCallType)
    {
        MN_CALL_CreateStkMoCallEntity(callId, MN_CALL_TYPE_EMERGENCY, pstOrigParam);

        if (VOS_TRUE == pstOrigParam->stEmergencyCat.bExist)
        {
            ulRet = MN_CALL_SendCcEmergSetupReq(callId, &(pstOrigParam->stEmergencyCat.ucEmergencyCat));
        }
        else
        {
            ulRet = MN_CALL_SendCcEmergSetupReq(callId, VOS_NULL_PTR);
        }

        if (TAF_CS_CAUSE_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_CALL_StkCallOrigReqProc: SEND MSG ERROR: emerge.");
            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-20, begin */
            TAF_CALL_SendCallOrigCnf(pstOrigParam->usClientId,
                                     pstOrigParam->opID,
                                     callId,
                                     TAF_CS_CAUSE_UNKNOWN);
            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-20, end */

#if (FEATURE_ON == FEATURE_PTM)
            /* ��¼CS�����쳣log */
            MN_CALL_CsCallErrRecord(callId, TAF_CS_CAUSE_UNKNOWN);
#endif

            MN_CALL_FreeCallId(callId);
            return;
        }
    }
    else
    {
        MN_CALL_SupportMoCallType(pstOrigParam->enCallType, &bSupported);
        if (VOS_TRUE != bSupported)
        {
            MN_WARN_LOG("MN_CALL_StkCallOrigReqProc: Fail to MN_CALL_SupportMoCallType.");
            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-20, begin */
            TAF_CALL_SendCallOrigCnf(pstOrigParam->usClientId,
                                     pstOrigParam->opID,
                                     callId,
                                     TAF_CS_CAUSE_CALL_CTRL_BEYOND_CAPABILITY);
            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-20, end */

#if (FEATURE_ON == FEATURE_PTM)
            /* ��¼CS�����쳣log */
            MN_CALL_CsCallErrRecord(callId, TAF_CS_CAUSE_CALL_CTRL_BEYOND_CAPABILITY);
#endif

            MN_CALL_FreeCallId(callId);
            return;
        }

        MN_CALL_CreateStkMoCallEntity(callId, pstOrigParam->enCallType, pstOrigParam);
        /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */

        /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */

        /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */

        ulRet = MN_CALL_BuildNormalCallReqProc(callId);
        if (TAF_CS_CAUSE_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_CALL_StkCallOrigReqProc: MN_CALL_BuildNormalCallReqProc fail.");
            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-20, begin */
            TAF_CALL_SendCallOrigCnf(pstOrigParam->usClientId,
                                     pstOrigParam->opID,
                                     callId,
                                     ulRet);
            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-20, end */

#if (FEATURE_ON == FEATURE_PTM)
            /* ��¼CS�����쳣log */
            MN_CALL_CsCallErrRecord(callId, ulRet);
#endif

            MN_CALL_FreeCallId(callId);
            return;
        }
    }

    NAS_EventReport(WUEPS_PID_TAF,
                    NAS_OM_EVENT_CC_MO_ATTEMPT,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    MN_CALL_UpdateCallState(callId, MN_CALL_S_DIALING);


    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-20, begin */
    TAF_CALL_SendCallOrigCnf(pstOrigParam->usClientId,
                             pstOrigParam->opID,
                             callId,
                             TAF_CS_CAUSE_SUCCESS);
    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-20, end */


    MN_CALL_ReportEvent(callId, MN_CALL_EVT_ORIG);

    MN_NORM_LOG("MN_CALL_StkCallOrigReqProc: send clint res normal and report event.");

    return;
}


/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-8, begin */
/*****************************************************************************
 �� �� ��  : MN_CALL_RcvAtCssnSetReq
 ��������  : CALLģ���յ�AT����CSSN������Ϣ�Ĵ���
 �������  : clientId           - ����������Client��ID
             opId               - Operation ID, ��ʶ���β���
             pstSetCssnReq      - cssn���ò�����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��8��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C����������

*****************************************************************************/
VOS_VOID  MN_CALL_RcvAtCssnSetReq(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_SET_CSSN_REQ_STRU          *pstSetCssnReq
)
{
    MN_CALL_SET_CSSN_CNF_STRU           stSetCssnCnf;
    VOS_UINT32                          ulCssiRptStatus;
    VOS_UINT32                          ulCssuRptStatus;

    /* ����CSSI��CSSU��Ӧ��SDCȫ�ֱ��� */
    if (MN_CALL_SET_CSSN_ACT == pstSetCssnReq->aenSetType[0])
    {
        ulCssiRptStatus = VOS_TRUE;
    }
    else
    {
        ulCssiRptStatus = VOS_FALSE;
    }


    if (MN_CALL_SET_CSSN_ACT == pstSetCssnReq->aenSetType[1])
    {
        ulCssuRptStatus = VOS_TRUE;
    }
    else
    {
        ulCssuRptStatus = VOS_FALSE;
    }

    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CSSI, ulCssiRptStatus);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CSSU, ulCssuRptStatus);

    PS_MEM_SET(&stSetCssnCnf, 0, sizeof(stSetCssnCnf));
    stSetCssnCnf.ClientId = MN_GetRealClientId(clientId, WUEPS_PID_TAF);
    stSetCssnCnf.OpId     = opId;
    stSetCssnCnf.ulRet    = TAF_ERR_NO_ERROR;
    stSetCssnCnf.enEvent  = MN_CALL_EVT_SET_CSSN_CNF;

    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8*)&stSetCssnCnf, sizeof(stSetCssnCnf));

}
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-8, end */

/*****************************************************************************
 �� �� ��  : MN_CALL_GetEccNumList
 ��������  : ��ȡ�����������б�
 �������  : ��
 �������  : pstEccNumInfo
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��01��23��
    ��    ��   : Y00213812
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID MN_CALL_GetEccNumList(MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo)
{
    VOS_UINT32                          ulListFulled;

    if (VOS_NULL_PTR == pstEccNumInfo)
    {
        MN_WARN_LOG("MN_CALL_GetEccNumList: pstEccNumInfo is NULL.");
        return;
    }

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-1-7, begin */
    /* �����н������붼�������Ϣ */
    if (TAF_SDC_USIM_STATUS_NO_PRESENT != TAF_SDC_GetUsimStatus())
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-1-7, end */
    {
        /* ��Э�鶨����п�ʱ������������ϱ��б� */
        ulListFulled = MN_CALL_AddEmerNumsWithUsimToReportList(pstEccNumInfo);

        /* �б�δ���������еĽ��������������Ϣ */
        if (VOS_FALSE == ulListFulled)
        {
            ulListFulled = MN_CALL_AddEccNumsInUsimToReportList(pstEccNumInfo);
        }

        /* �б�δ������MM���ϱ��Ľ��������������Ϣ */
        if (VOS_FALSE == ulListFulled)
        {
           ulListFulled = MN_CALL_AddMmEccNumsToReportList(pstEccNumInfo);
        }
    }
    else
    {
        /* ��Э�鶨����޿�ʱ���������� */
        ulListFulled = MN_CALL_AddEmerNumsNoUsimToReportList(pstEccNumInfo);
    }

    /* �б�δ��,��APP���ƵĽ��������������Ϣ */
    if (VOS_FALSE == ulListFulled)
    {
       (VOS_VOID)MN_CALL_AddCustomEccNumsToReportList(pstEccNumInfo);
    }

    return;
}
/*****************************************************************************
 �� �� ��  : MN_CALL_RcvAtXlemaReq
 ��������  : �����������ѯ����
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��01��23��
    ��    ��   : Y00213812
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID MN_CALL_RcvAtXlemaReq(MN_CALL_APP_REQ_MSG_STRU            *pstCallMsg)
{
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo = VOS_NULL_PTR;
    VOS_UINT16                          usLen;

    pstEccNumInfo = (MN_CALL_ECC_NUM_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_CALL_ECC_NUM_INFO_STRU));
    if (VOS_NULL_PTR == pstEccNumInfo)
    {
        MN_WARN_LOG("MN_CALL_RcvAtXlemaReq: Alloc Mem Fail.");
        return;
    }

    /* ��Ϣ��ʼ�� */
    PS_MEM_SET(pstEccNumInfo, 0, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    pstEccNumInfo->enEvent    = MN_CALL_EVT_XLEMA_CNF;
    pstEccNumInfo->usClientId = pstCallMsg->clientId;

    /* ��ȡ�������б� */
    MN_CALL_GetEccNumList(pstEccNumInfo);

    usLen = (VOS_UINT16)sizeof(MN_CALL_ECC_NUM_INFO_STRU);

    /* �ϱ�AT */
    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (TAF_UINT8 *)pstEccNumInfo, usLen);

    /* �ڴ��ͷ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstEccNumInfo);

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_CALL_RcvStartDtmfReq
 ��������  : �յ�START_DTMF����Ĵ���
             ���ȼ��Ҫ���͵��ַ��Ƿ�Ϸ������Ϸ���ͨ����ʱ��Ӧ�ظ�����
             �����һ��DTMF���̻�δ�������ú������ѱ�����Ҫ���͵��ַ�����������
             ���򣬽���CC����MNCC_START_DTMF_REQԭ�﷢�͸�DTMF�ַ�
 �������  : pstStartDtmf   - START DTMF������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ������DTMF�������
  2.��    ��   :2013��10��24��
        ��    ��   :z00161729
        �޸�����   :DTS2013102403705:dtmf��֧��off_length������SBM IOT��֤��Ҫstop dtmf req����һ��start dtmf req�������70msС��600ms
*****************************************************************************/
VOS_VOID  TAF_CALL_RcvStartDtmfReq(struct MsgCB * pstStartDtmf)
{
    MN_CALL_ID_T                        CallId;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppReq       = VOS_NULL_PTR;
    TAF_CALL_DTMF_PARAM_STRU           *pstDtmfParam    = VOS_NULL_PTR;
    TAF_CALL_DTMF_INFO_STRU             stDtmfInfo;
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfCurInfo  = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stDtmfInfo, 0, sizeof(stDtmfInfo));

    pstAppReq               = ((MN_CALL_APP_REQ_MSG_STRU *)pstStartDtmf);
    pstDtmfParam            = &pstAppReq->unParm.stDtmf;
    stDtmfInfo.CallId       = pstDtmfParam->CallId;
    stDtmfInfo.cKey         = pstDtmfParam->cKey;
    stDtmfInfo.usOnLength   = pstDtmfParam->usOnLength;
    stDtmfInfo.usClientId   = pstAppReq->clientId;
    stDtmfInfo.opId         = pstAppReq->opId;

    stDtmfInfo.usOffLength  = pstDtmfParam->usOffLength;

    /* DTMF��Ϣ�Ϸ����ж� */
    if ( (VOS_OK != TAF_SDC_CheckDtmfKey(&stDtmfInfo.cKey))
      || (stDtmfInfo.usOnLength < TAF_CALL_DTMF_MIN_ONLENGTH) )
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_START_DTMF_CNF,
                             TAF_CS_CAUSE_INVALID_PARAMETER);
        return;
    }

    /* ���жϵ�ǰ�Ƿ�������DTMF���ٻ�ȡ���п��Է���DTMF�ĺ���ID */
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    ulResult    = TAF_CALL_CheckUserDtmfCallId(stDtmfInfo.CallId);
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    if (TAF_CS_CAUSE_SUCCESS != ulResult)
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_START_DTMF_CNF,
                             ulResult);
        return;
    }

    /* �ж�DTMF״̬�Ƿ����� */
    if (TAF_CALL_GetDtmfState() >= TAF_CALL_DTMF_STATE_BUTT)
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_START_DTMF_CNF,
                             TAF_CS_CAUSE_STATE_ERROR);
        return;
    }

    /* DTMF���ڷǿ���״̬���򻺴��DTMF */
    if (TAF_CALL_GetDtmfState() != TAF_CALL_DTMF_IDLE)
    {
        ulResult = TAF_CALL_SaveDtmfInfo(&stDtmfInfo);

        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_START_DTMF_CNF,
                             ulResult);
        return;
    }

    /* DTMF��ǰ���ڿ���̬�����͵�CC */
    pstDtmfCurInfo  = TAF_CALL_GetDtmfCurInfo();
    *pstDtmfCurInfo = stDtmfInfo;

    /* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
    /* ��ȡ����DTMF��CALL ID */
    CallId   = 0;
    ulResult = TAF_CALL_GetAllowedDtmfCallId(&CallId);
    if (TAF_CS_CAUSE_SUCCESS != ulResult)
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_START_DTMF_CNF,
                             ulResult);
        return;
    }
    /* Added by f62575 for V9R1 STK����, 2013-6-26, end */

    if (VOS_OK != MN_CALL_SendCcStartDtmfReq(CallId, pstDtmfCurInfo->cKey))
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_START_DTMF_CNF,
                             TAF_CS_CAUSE_UNKNOWN);
        return;
    }

    /* ���ͳɹ�������DTMF״̬ */
    TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_START_CNF);

    TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                         stDtmfInfo.opId,
                         MN_CALL_EVT_START_DTMF_CNF,
                         TAF_CS_CAUSE_SUCCESS);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_RcvStopDtmfReq
 ��������  : �յ�STOP_DTMF����Ĵ���
 �������  : pstStopDtmf   - STOP DTMF������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ������DTMF�������
  2.��    ��   :2013��10��24��
    ��    ��   :z00161729
    �޸�����   :DTS2013102403705:dtmf��֧��off_length������SBM IOT��֤��Ҫstop dtmf req����һ��start dtmf req�������70ms
*****************************************************************************/
VOS_VOID  TAF_CALL_RcvStopDtmfReq(struct MsgCB * pstStopDtmf)
{
    MN_CALL_ID_T                        CallId;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppReq       = VOS_NULL_PTR;
    TAF_CALL_DTMF_PARAM_STRU           *pstDtmfParam    = VOS_NULL_PTR;
    TAF_CALL_DTMF_INFO_STRU             stDtmfInfo;
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfCurInfo  = VOS_NULL_PTR;
    TAF_CALL_DTMF_STATE_ENUM_UINT8      enDtmfState;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stDtmfInfo, 0, sizeof(stDtmfInfo));

    pstAppReq               = ((MN_CALL_APP_REQ_MSG_STRU *)pstStopDtmf);
    pstDtmfParam            = &pstAppReq->unParm.stDtmf;
    stDtmfInfo.CallId       = pstDtmfParam->CallId;
    stDtmfInfo.cKey         = pstDtmfParam->cKey;
    stDtmfInfo.usOnLength   = pstDtmfParam->usOnLength;
    stDtmfInfo.usClientId   = pstAppReq->clientId;
    stDtmfInfo.opId         = pstAppReq->opId;
    enDtmfState             = TAF_CALL_GetDtmfState();

    stDtmfInfo.usOffLength  = pstDtmfParam->usOffLength;

    /* STOP_DTMF����ʱ��OnLengthֵ��Ϊ0 */
    if (0 != stDtmfInfo.usOnLength)
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_STOP_DTMF_CNF,
                             TAF_CS_CAUSE_INVALID_PARAMETER);
        return;
    }

    /* �ж�DTMF״̬�Ƿ����� */
    if ( (TAF_CALL_DTMF_STATE_BUTT <= enDtmfState)
      || (TAF_CALL_DTMF_IDLE == enDtmfState) )
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_STOP_DTMF_CNF,
                             TAF_CS_CAUSE_STATE_ERROR);
        return;
    }

    /* ���жϵ�ǰ�Ƿ�������DTMF���Լ��û�����ĺ���ID�Ƿ���Է���DTMF */
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    ulResult    = TAF_CALL_CheckUserDtmfCallId(stDtmfInfo.CallId);
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    if (TAF_CS_CAUSE_SUCCESS != ulResult)
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_STOP_DTMF_CNF,
                             ulResult);
        return;
    }

    /* �����ǰû�л����Ҵ��ڵȴ���ʱ����ʱ״̬����ͣ��ʱ��������STOP_DTMF�����򻺴� */
    if ( (0 == TAF_CALL_GetDtmfBufCnt())
      && (TAF_CALL_DTMF_WAIT_ON_LENGTH_TIME_OUT == enDtmfState))
    {
        MN_CALL_StopTimer(TAF_CALL_TID_DTMF_ON_LENGTH);


        pstDtmfCurInfo  = TAF_CALL_GetDtmfCurInfo();
        *pstDtmfCurInfo = stDtmfInfo;

        /* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
        /* ��ȡ����DTMF��CALL ID */
        CallId = 0;
        ulResult = TAF_CALL_GetAllowedDtmfCallId(&CallId);
        if (TAF_CS_CAUSE_SUCCESS != ulResult)
        {
            TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                                 stDtmfInfo.opId,
                                 MN_CALL_EVT_STOP_DTMF_CNF,
                                 ulResult);
            return;
        }
        /* Added by f62575 for V9R1 STK����, 2013-6-26, end */

        if (VOS_OK != MN_CALL_SendCcStopDtmfReq(CallId))
        {
            TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                                 stDtmfInfo.opId,
                                 MN_CALL_EVT_STOP_DTMF_CNF,
                                 TAF_CS_CAUSE_UNKNOWN);
            return;
        }

        /* ���ͳɹ�������DTMF״̬ */
        TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_STOP_CNF);

        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_STOP_DTMF_CNF,
                             TAF_CS_CAUSE_SUCCESS);
        return;
    }

    /* ��ǰ���ܷ���STOP_DTMF�����򻺴� */
    ulResult = TAF_CALL_SaveDtmfInfo(&stDtmfInfo);

    TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                         stDtmfInfo.opId,
                         MN_CALL_EVT_STOP_DTMF_CNF,
                         ulResult);
    return;
}
/* Added by l00198894 for V9R1 STK����, 2013/07/11, end */

/*****************************************************************************
 �� �� ��  : TAF_CALL_RcvCcwaiSetReq
 ��������  : �յ�CCWAI��������Ĵ���
 �������  : pstMsg   - CCWAI����������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��02��16��
    ��    ��   : n00269697
    �޸�����   : DTS2016021506132��ccwai������call����call��ims�ṩ�ӿ�����ѯ
*****************************************************************************/
VOS_VOID  TAF_CALL_RcvCcwaiSetReq(MN_CALL_APP_REQ_MSG_STRU *pstAppReq)
{
    TAF_CALL_CCWAI_MODE_ENUM_UINT8      enCcwaiMode;
    TAF_CALL_NVIM_CCWA_CTRL_MODE_STRU   stCcwaCtrlMode;
    VOS_UINT32                          ulRst;

    enCcwaiMode = pstAppReq->unParm.stCcwaiSet.enMode;


    if (TAF_CALL_CCWAI_SRV_CLASS_SET_NW == pstAppReq->unParm.stCcwaiSet.enSrvClass)
    {
        /* ��CCWAI����д��NV */
        PS_MEM_SET(&stCcwaCtrlMode, 0, sizeof(stCcwaCtrlMode));
        stCcwaCtrlMode.enCcwaCtrlMode = TAF_CALL_CCWA_CTRL_BY_NW;
        stCcwaCtrlMode.enCcwaiMode = enCcwaiMode;

        ulRst = NV_Write(en_NV_Item_Ccwa_Ctrl_Mode,
                         (VOS_VOID *)&stCcwaCtrlMode,
                         sizeof(TAF_CALL_NVIM_CCWA_CTRL_MODE_STRU));

        /* ���дNVʧ�ܣ���CCWAI����ʧ�� */
        if (NV_OK != ulRst)
        {
            MN_ERR_LOG("TAF_CALL_RcvCcwaiSetReq:Write NVIM Error");

            TAF_CALL_SendCcwaiCnf(pstAppReq->clientId,
                                  pstAppReq->opId,
                                  TAF_CALL_EVT_CCWAI_SET_CNF,
                                  VOS_ERR);

            return;
        }

        TAF_CALL_SetCcwaiMode(enCcwaiMode);
        TAF_CALL_SetCcwaCtrlMode(TAF_CALL_CCWA_CTRL_BY_NW);

        TAF_WARNING_LOG2(WUEPS_PID_TAF, "TAF_CALL_RcvCcwaiSetReq ", TAF_CALL_CCWA_CTRL_BY_NW, enCcwaiMode);

        TAF_CALL_SendCcwaiCnf(pstAppReq->clientId,
                              pstAppReq->opId,
                              TAF_CALL_EVT_CCWAI_SET_CNF,
                              VOS_OK);

        return;
    }

    /* ��CCWAI����д��NV */
    PS_MEM_SET(&stCcwaCtrlMode, 0, sizeof(stCcwaCtrlMode));
    stCcwaCtrlMode.enCcwaCtrlMode = TAF_CALL_CCWA_CTRL_BY_UE;
    stCcwaCtrlMode.enCcwaiMode = enCcwaiMode;

    ulRst = NV_Write(en_NV_Item_Ccwa_Ctrl_Mode,
                     (VOS_VOID*)&stCcwaCtrlMode,
                     sizeof(TAF_CALL_NVIM_CCWA_CTRL_MODE_STRU));

    /* ���дNVʧ�ܣ���CCWAI����ʧ�� */
    if (NV_OK != ulRst)
    {
        MN_ERR_LOG("TAF_CALL_RcvCcwaiSetReq:Write NVIM Error");

        TAF_CALL_SendCcwaiCnf(pstAppReq->clientId,
                              pstAppReq->opId,
                              TAF_CALL_EVT_CCWAI_SET_CNF,
                              VOS_ERR);

        return;
    }

    /* ��CCWAI���ñ��浽ȫ�ֱ��� */
    TAF_CALL_SetCcwaiMode(enCcwaiMode);
    TAF_CALL_SetCcwaCtrlMode(TAF_CALL_CCWA_CTRL_BY_UE);

    TAF_WARNING_LOG2(WUEPS_PID_TAF, "TAF_CALL_RcvCcwaiSetReq ", TAF_CALL_CCWA_CTRL_BY_UE, enCcwaiMode);

    TAF_CALL_SendCcwaiCnf(pstAppReq->clientId,
                          pstAppReq->opId,
                          TAF_CALL_EVT_CCWAI_SET_CNF,
                          VOS_OK);
    return;
}

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-3-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 �� �� ��  : TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer
 ��������  : �յ���ѯeCall������Ϣ������
 �������  : pstQryEcallInfoReq   - ��ѯ������Ϣ������Ϣ��ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��26��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_VOID TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(
    VOS_UINT8                           ucCallId
)
{
    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg = VOS_NULL_PTR;

    pstBufferdMsg  = MN_CALL_GetBufferedMsg();

    if ((VOS_TRUE == pstBufferdMsg->bitOpBufferedSetupMsg)
     && (ucCallId == pstBufferdMsg->stBufferedSetupMsg.ucCallId))
    {
        MN_CALL_ClearBufferedMsg();

        /* ֹͣeCall�ز���ʱ�� */
        MN_CALL_StopTimer(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL);
        MN_CALL_StopTimer(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD);
    }
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_RcvQryEcallInfoReq
 ��������  : �յ���ѯeCall������Ϣ������
 �������  : pstQryEcallInfoReq   - ��ѯ������Ϣ������Ϣ��ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��29��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_VOID TAF_CALL_RcvQryEcallInfoReq(MN_CALL_QRY_ECALL_INFO_REQ_STRU *pstQryEcallInfoReq)
{
    MN_CALL_EVT_QRY_ECALL_INFO_CNF_STRU stQryEcallCnf;
    MN_CALL_MGMT_STRU                  *pstCallEntityAddr = VOS_NULL_PTR;
    VOS_UINT8                           i;

    PS_MEM_SET(&stQryEcallCnf, 0, sizeof(MN_CALL_EVT_QRY_ECALL_INFO_CNF_STRU));

    /* �ں���ʵ���л�ȡMO eCall���е������Ϣ */
    pstCallEntityAddr = TAF_CALL_GetCallEntityAddr();

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if (VOS_FALSE == pstCallEntityAddr->bUsed)
        {
            pstCallEntityAddr++;

            continue;
        }

        /* ��ȡeCall������Ϣ */
        if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstCallEntityAddr->stCallInfo.callId))
        {
            stQryEcallCnf.stEcallInfo.astEcallInfos[stQryEcallCnf.stEcallInfo.ucNumOfEcall].ucCallId    =
                pstCallEntityAddr->stCallInfo.callId;

            stQryEcallCnf.stEcallInfo.astEcallInfos[stQryEcallCnf.stEcallInfo.ucNumOfEcall].enCallState =
                pstCallEntityAddr->stCallInfo.enCallState;

            stQryEcallCnf.stEcallInfo.astEcallInfos[stQryEcallCnf.stEcallInfo.ucNumOfEcall].enEcallType =
                pstCallEntityAddr->stCallInfo.enCallType;

            PS_MEM_CPY(&(stQryEcallCnf.stEcallInfo.astEcallInfos[stQryEcallCnf.stEcallInfo.ucNumOfEcall].stDialNumber),
                       &(pstCallEntityAddr->stCallInfo.stCalledNumber),
                       sizeof(MN_CALL_CALLED_NUM_STRU));

            stQryEcallCnf.stEcallInfo.ucNumOfEcall++;
        }

        pstCallEntityAddr++;
    }

    stQryEcallCnf.ucOpId     = pstQryEcallInfoReq->ucOpId;
    stQryEcallCnf.usClientId = pstQryEcallInfoReq->usClientId;

    /* ������Ϣ��������Ϣ�Ĳ�ѯ�� */
    TAF_CALL_SendQueryEcallInfoCnf(pstQryEcallInfoReq->usClientId,
                                   pstQryEcallInfoReq->ucOpId,
                                   &stQryEcallCnf);
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_EcallSupsCmdRelReqProc
 ��������  : �յ�eCall���йһ�����
 �������  : usClientId       - �û���ʶ
             ucOpId           - ������ʶ
             pstCallSupsParam - ҵ���������

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��29��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature����
  2.��    ��   :2016��03��08��
    ��    ��   :l00356716
    �޸�����   :NAS���������Ż�
*****************************************************************************/
VOS_VOID TAF_CALL_EcallSupsCmdRelReqProc(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    const MN_CALL_SUPS_PARAM_STRU      *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           i;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;

    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetNotIdleStateCalls(&ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* �Ҷ���������ͨ����eCall���� */
        for (i = 0; i < ulNumOfCalls; i++)
        {
            if (VOS_FALSE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
            {
                /* ECLSTOP������ܹҶ�eCall���� */
                continue;
            }

            /* ���"�ȴ�mt eCall���б�־λ" */
            TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

            MN_CALL_GetCallState(aCallIds[i], &enCallState, &enMptyState);
            MN_CALL_UpdateClientId(aCallIds[i], usClientId);

            /* ������д���dialing״̬���Һ����ط������ʱ�������У�cc����U0״̬������
               ��cc����disconnect��Ϣ���������rej ind��Ϣ */
            if ((MN_CALL_TIMER_STATUS_RUNING == TAF_CALL_GetRedialIntervalTimerStatus(aCallIds[i]))
             && (MN_CALL_S_DIALING           == enCallState))
            {
                TAF_CALL_RelRedialingCall(usClientId, ucOpId, pstCallSupsParam);
                return;
            }

            if ((MN_CALL_S_INCOMING            == enCallState)
             || (MN_CALL_S_WAITING             == enCallState)
             || (MN_CALL_S_CCBS_WAITING_RECALL == enCallState))
            {
                TAF_CALL_RelIncomingOrWaitingCall(aCallIds[i], enCallState);
            }
            else
            {
                (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

                /* ��¼�����Ҷϵ�ԭ��ֵ */
                MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

                /* ��¼���йҶϵķ��� */
                MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

                /* ���T9��ʱ�������У�ֹͣT9��ʱ�� */
                if (MN_CALL_TIMER_STATUS_RUNING == MN_CALL_GetTimerStatus(TAF_CALL_TID_T9))
                {
                    /* ֹͣT9��ʱ�� */
                    MN_CALL_StopTimer(TAF_CALL_TID_T9);
                }

                /* ����ز��������ز���ʱ�� */
                TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
            }

            MN_CALL_DeRegSsKeyEvent(aCallIds[i],MN_CALL_SS_PROG_EVT_SETUP_COMPL);
            MN_CALL_DeRegSsKeyEvent(aCallIds[i],MN_CALL_SS_PROG_EVT_REL);
        }

        MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /*�����Ҷϣ�ֹͣ�ز���ʱ��*/
        if (VOS_TRUE == TAF_CALL_GetCallRedialForDiscSupportFlg())
        {
            TAF_CALL_StopAllRedialTimers(pstCallSupsParam->callId);
        }

        MN_CALL_CallSupsCmdReqCommProc(usClientId, ucOpId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    TAF_CALL_SendSupsCmdCnf(usClientId, ucOpId, pstCallSupsParam->callId, TAF_CS_CAUSE_SUCCESS);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(usClientId,
                                              ucOpId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_SUCCESS);
}
#endif
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-3-29, end */

/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



