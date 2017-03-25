/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXregMain.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2014��06��27��
  ��������   : 1X REG(register)�����ʼ����������ں�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��06��27��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasCcb.h"
#include  "CnasXregCtx.h"
#include  "CnasXregMain.h"
#include  "CnasXregFsmMainTbl.h"
#include  "CnasTimerMgmt.h"
#include  "CnasMntn.h"
#include  "CnasXregRegingProcTbl.h"
#include  "CnasXregPreProcTbl.h"
#include  "CnasXregProcess.h"
#include  "CnasXregListProc.h"
#include  "CnasXregFsmSwitchOnTbl.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XREG_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XREG_RegPreFsm
 ��������  : XREGԤ����״̬��ע��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE -- ע��ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��07��07��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XREG_RegPreFsm(VOS_VOID)
{
    /* Ԥ����״̬��ע�� */
    NAS_FSM_RegisterFsm((CNAS_XREG_GetPreFsmDescAddr()),
                         "CNAS:FSM:XREG:PRE",
                         (VOS_UINT32)(CNAS_XREG_GetPreProcessStaTblSize()),
                         g_astCnasXregPreProcessFsmTbl,
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RegMainL1Fsm
 ��������  : XREG L1 main״̬��ע��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE -- ע��ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��07��07��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XREG_RegMainL1Fsm(VOS_VOID)
{
    /* main״̬��ע�� */
    NAS_FSM_RegisterFsm((CNAS_XREG_GetMainFsmDescAddr()),
                         "CNAS:FSM:XREG:MAIN",
                         (VOS_UINT32)(CNAS_XREG_GetL1MainStaTblSize()),
                         CNAS_XREG_GetL1MainStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_XREG_InitFsmCtx_L1Main);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RegL2Fsm
 ��������  : XREG L1 main״̬��ע��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE -- ע��ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��07��04��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XREG_RegL2Fsm(VOS_VOID)
{
    /* SWITCHON״̬��ע�� */
    NAS_FSM_RegisterFsm((CNAS_XREG_GetSwitchOnFsmDescAddr()),
                         "CNAS:FSM:XREG:SwitchOn",
                         (VOS_UINT32)CNAS_XREG_GetSwitchOnStaTblSize(),
                         CNAS_XREG_GetSwitchOnStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_XREG_InitFsmCtx_SwitchOn);

    /* Reging״̬��ע�� */
    NAS_FSM_RegisterFsm((CNAS_XREG_GetRegingFsmDescAddr()),
                         "CNAS:FSM:XREG:Reging",
                         (VOS_UINT32)CNAS_XREG_GetRegingStaTblSize(),
                         CNAS_XREG_GetRegingStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_RegFsm
 ��������  : XREGע��״̬��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��07��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  CNAS_XREG_RegFsm(VOS_VOID)
{
    /* ע��Ԥ����״̬�� */
    CNAS_XREG_RegPreFsm();

    /* ע��L1״̬�� */
    CNAS_XREG_RegMainL1Fsm();

    /* ע��L2״̬�� */
    CNAS_XREG_RegL2Fsm();
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_PreProcessMsg
 ��������  : XREG��ϢԤ����
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- Ԥ�������
             VOS_FALSE -- ����Ҫ����״̬���д���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��07��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XREG_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRslt = VOS_FALSE;
    NAS_ACTION_FUNC                     pActFun;
    NAS_FSM_DESC_STRU                  *pstFsmDesc;

    /* ��ȡԤ���������е���Ӧ�Ķ��������� */
    pstFsmDesc = CNAS_XREG_GetPreFsmDescAddr();

    /* ����״̬ת�Ʊ��е���Ӧ�Ķ��������� */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, CNAS_XREG_L1_STA_PREPROC, ulEventType);

    if (VOS_NULL_PTR != pActFun )
    {
        /* Ԥ������Ϣ,��Ϊ������Ϣ,һ��ΪԤ��������ͷ���,����һ��ΪԤ����
        ������,��Ȼ��Ҫ���е�״̬���м�������,��˴˴�ֱ��ͨ����������Ԥ��
        ��������Ƿ���Ҫ����״̬������*/
        ulRslt = (*pActFun) ( ulEventType, pstMsg);
    }

    return ulRslt;
}

/*****************************************************************************
 �� �� ��    : CNAS_XREG_FsmProcessEvent
 ��������    : ״̬�����¼�������
 �������    :
               ulCurState  -- ��ǰ״̬
               ulEventType -- �����¼�
               pRcvMsg     -- ��Ϣָ��
 �������    :
 ����ֵ      : VOS_FALSE -- ��Ϣ����δ���
               VOS_TRUE  -- ��Ϣ���������
 ���ú���  :
 ��������  :

  �޸���ʷ      :
   1.��    ��   : 2014��7��07��
     ��    ��   : h00246512
     �޸�����   : �����ɺ���

 *****************************************************************************/
VOS_UINT32 CNAS_XREG_FsmProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
)
{
    NAS_ACTION_FUNC                     pActFun;
    NAS_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    CNAS_INFO_LOG2(UEPS_PID_XREG, "CNAS_XREG_FsmProcessEvent", ulCurState, ulEventType);

    pstFsmDesc = CNAS_XREG_GetCurFsmDesc();

    /* ����״̬ת�Ʊ��е���Ӧ�Ķ��������� */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, ulCurState, ulEventType);

    if (VOS_NULL_PTR != pActFun)
    {
        /* ������ص��¼���������Ϊ��,�����������¼����� */
        ulRet   = (*pActFun)(ulEventType, (struct MsgCB*)pRcvMsg);

        CNAS_INFO_LOG1(UEPS_PID_XREG, "CNAS_XREG_FsmProcessEvent", ulRet);

        return VOS_TRUE;
    }

    /* ��Ϣδ��������������� */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_ProcessMsgInFsm
 ��������  : ��Ϣ״̬������
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ��Ϣ�������
             VOS_FALSE -- ��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��07��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XREG_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    CNAS_XREG_FSM_CTX_STRU             *pstCurFsm = VOS_NULL_PTR;
    VOS_UINT16                          usOldStackDepth;
    VOS_UINT16                          usNewStackDepth;

    /* ��ȡ��ǰXREG��״̬�������� */
    pstCurFsm          = CNAS_XREG_GetCurFsmAddr();

    /* ��ȡ��ǰXREG��ջ��� */
    usOldStackDepth    = CNAS_XREG_GetFsmStackDepth();

    /* ��Ϣ���� */
    ulRet              = CNAS_XREG_FsmProcessEvent(pstCurFsm->ulState,
                                                   ulEventType,
                                                   (VOS_VOID*)pstMsg);

    /* ��ȡ��ǰXREG����ջ��� */
    usNewStackDepth    = CNAS_XREG_GetFsmStackDepth();

    /* ջ���û������,����û�д����µ�״̬���������˳�*/
    if (usNewStackDepth <= usOldStackDepth)
    {
        return ulRet;
    }

    /* �µ�ջ��ȴ����ϵ�ջ��� ����������ѹջ,��Ҫ����Ϣ����״̬���м������� */
    /* ���»�ȡ��ǰXREG�Ķ���״̬ */
    pstCurFsm   = CNAS_XREG_GetCurFsmAddr();

    /* ����Ϣ���붥��״̬������������ */
    ulRet       = CNAS_XREG_FsmProcessEvent(pstCurFsm->ulState,
                                            ulEventType,
                                            (VOS_VOID*)pstMsg);


    return ulRet;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_ProcMsgPrio
 ��������  : ����ǰ�յ�����Ϣ��L2״̬���������Ϣ���бȽ�,�����ݱȽϽ�����к����Ķ���
 �������  : ulEventType -- ��Ϣ����
             pstMsg      -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ��ǰ��Ϣ������ɣ�����Ҫ��������
             VOS_FALSE -- ��ǰ��Ϣ������ɣ���Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��07��07��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XREG_ProcMsgPrio(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �жϵ�ǰ�ڲ��״̬�� */
    if (CNAS_XREG_FSM_REGING == CNAS_XREG_GetCurrFsmId())
    {
        return CNAS_XREG_PostProcessMsg_Reging(ulEventType, pstMsg);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_PostProcessMsg
 ��������  : XREG״̬��������,����ǰ�յ�����Ϣ��L2״̬���������Ϣ���бȽ�,
             �жϺ����Ķ���
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ��Ϣ�������
             VOS_FALSE -- ��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��07��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  CNAS_XREG_PostProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���ε������漰 */

    if (VOS_TRUE == CNAS_XREG_ProcMsgPrio(ulEventType, pstMsg))
    {
        /* ��ӡlog��Ϣ */


        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_ProcessBufferMsg
 ��������  : ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��07��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XREG_ProcessBufferMsg(VOS_VOID)
{
    CNAS_XREG_MSG_STRU                 *pstCacheMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          usOldStackDepth;
    VOS_UINT32                          usNewStackDepth;

    /* �ڴ�ռ���� */
    pstCacheMsg = (CNAS_XREG_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_XREG, sizeof(CNAS_XREG_MSG_STRU));

    if (VOS_NULL_PTR == pstCacheMsg)
    {
        return VOS_FALSE;
    }

    ulRet = VOS_TRUE;
    while (VOS_TRUE == CNAS_XREG_GetNextCachedMsg(pstCacheMsg))
    {
        if (VOS_TRUE == CNAS_XREG_PreProcessMsg(pstCacheMsg->ulEventType, (struct MsgCB*)pstCacheMsg->aucMsgBuffer))
        {
            continue;
        }

        /* ��ȡ��ǰXREG��ջ��� */
        usOldStackDepth     = CNAS_XREG_GetFsmStackDepth();

        /* ����״̬������ */
        ulRet  = CNAS_XREG_ProcessMsgInFsm(pstCacheMsg->ulEventType, (struct MsgCB*)pstCacheMsg->aucMsgBuffer);

        /* ��ȡ��ǰXREG��ջ��� */
        usNewStackDepth     = CNAS_XREG_GetFsmStackDepth();

        /* ���ջ���������,˵���϶�������ѹջ����,���ܼ���������Ϣ */
        if (usNewStackDepth > usOldStackDepth)
        {
            ulRet   = VOS_FALSE;
            break;
        }

        /* ����Ϣ�����˺���,�������Ǵ�ϻ򻺴��,��������ܼ��������� */
        if (VOS_FALSE == ulRet)
        {
            if (VOS_TRUE == CNAS_XREG_PostProcessMsg(pstCacheMsg->ulEventType,
                                                     (struct MsgCB*)pstCacheMsg->aucMsgBuffer))
            {
                ulRet   = VOS_FALSE;
                break;
            }
        }
    }

    PS_MEM_FREE(UEPS_PID_XREG, pstCacheMsg);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_MsgProc
 ��������  : 1X REGģ����Ϣ������ں���
 �������  : pMsg -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��06��28��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XREG_MsgProc (struct MsgCB* pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pRcvTimerMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          usOldStackDepth;
    VOS_UINT32                          usNewStackDepth;
    VOS_UINT32                          ulSenderPid;

    /* ��ָ���� */
    if (VOS_NULL_PTR == pstMsg)
    {
        /* ��ӡ������Ϣ */
        return;
    }

    ulSenderPid = CNAS_CCB_GetModem0Pid(CNAS_CCB_GetCdmaModeModemId(), pstMsg->ulSenderPid);

    pstMsg->ulSenderPid = ulSenderPid;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* �����¼����� */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        pRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

        ulEventType  = CNAS_BuildEventType(pstMsgHeader->ulSenderPid, pRcvTimerMsg->ulName);

        /* ֹͣ��Ӧ�Ķ�ʱ�� */
        CNAS_StopTimer(UEPS_PID_XREG, pRcvTimerMsg->ulName, pRcvTimerMsg->ulPara);
    }
    else
    {
        ulEventType  = CNAS_BuildEventType(pstMsgHeader->ulSenderPid, (VOS_UINT16)pstMsgHeader->ulMsgName);
    }

    CNAS_XREG_GlobalMntn(CNAS_XREG_MNTN_GLOBALIN, ulEventType);

    /* ����Ѿ����������ֱ�ӷ��� */
    if (VOS_TRUE == CNAS_XREG_PreProcessMsg(ulEventType, pstMsg))
    {
       CNAS_XREG_GlobalMntn(CNAS_XREG_MNTN_GLOBALOUT, ulEventType);
       return;
    }

    /* ��ȡ��ǰXREG��ջ��� */
    usOldStackDepth = CNAS_XREG_GetFsmStackDepth();

    /* ����״̬������ */
    ulRet = CNAS_XREG_ProcessMsgInFsm(ulEventType, pstMsg);

    /* ��״̬���˳��󣬻�ȡ�µ�ջ��� */
    usNewStackDepth = CNAS_XREG_GetFsmStackDepth();

    /* ���ջ����ȼ���,˵���϶���������ջ����,��Ҫ���ȴ����״̬���Ľ����Ϣ,ֱ�ӷ��� */
    if (usNewStackDepth < usOldStackDepth)
    {
        /* ��¼��ջ����,ֻҪ��������ջ�����Ϳ��Դ����� */
        CNAS_XREG_SetFsmStackPopFlg(VOS_TRUE);
        return;
    }

    /* ����Ϣ��״̬�����Ѿ��������,�ɳ��Դ���һ�»��� */
    if (VOS_TRUE == ulRet)
    {
        /* ��ǰ���յ�״̬�����˳���Ϣ���ܹ������� */
        if (VOS_TRUE == CNAS_XREG_GetFsmStackPopFlg())
        {
            CNAS_XREG_ProcessBufferMsg();
            CNAS_XREG_SetFsmStackPopFlg(VOS_FALSE);
        }
    }
    /* �ڵ�ǰ״̬����δ������ϣ��ж���Ϣ�Ƿ���Ҫ��ϵ�ǰ��L2״̬��,���� */
    else
    {
        CNAS_XREG_PostProcessMsg(ulEventType, pstMsg);
    }

    CNAS_XREG_GlobalMntn(CNAS_XREG_MNTN_GLOBALOUT, ulEventType);

    return;

}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_InitTask
 ��������  : 1X REGģ�������ʼ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE
             VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��06��27��
   ��    ��   : l60609
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  CNAS_XREG_InitTask(VOS_VOID)
{
    /* ��ʼ��ZONEע��ʹ�õ����� */
    CNAS_XREG_InitList();

    /* ��ʼ�������� */
    CNAS_XREG_InitCtx();

    /* ע��״̬�� */
    CNAS_XREG_RegFsm();

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : CNAS_XREG_InitPid
 ��������  : 1X REG��PID��ʼ������
 �������  : enInitPhase -- PID��ʼ���׶�
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XREG_InitPid(
    enum VOS_INIT_PHASE_DEFINE         enInitPhase
)
{
    switch (enInitPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            /* ����XREGģ���ʼ������ */
            CNAS_XREG_InitTask();
            break;

        case VOS_IP_INITIAL:
        case VOS_IP_FARMALLOC:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
        case VOS_IP_BUTT:
            break;

        default:
            break;
    }

    return VOS_OK;
}
/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



