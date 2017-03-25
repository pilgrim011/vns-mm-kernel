/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdMain.c
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��12��12��
  ��������   : HRPD SD(system determination)�����ʼ����������ں�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CnasHsdMain.h"
#include "CnasHsdCtx.h"
#include "CnasTimerMgmt.h"
#include "CnasCcb.h"
#include "CnasMntn.h"
#include "CnasHsdFsmMainTbl.h"
#include "CnasHsdFsmSwitchOnTbl.h"
#include "CnasHsdFsmPowerOffTbl.h"
#include "CnasHsdFsmSysAcqTbl.h"
#include "CnasHsdPreProcTbl.h"
#include "CnasHsdFsmPowerSaveTbl.h"
#include "CnasHsdFsmInterSysTbl.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_HSD_RegPreFsm
 ��������  : HSDԤ����״̬��ע��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE -- ע��ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RegPreFsm(VOS_VOID)
{
    /* Ԥ����״̬��ע�� */
    NAS_FSM_RegisterFsm((CNAS_HSD_GetPreFsmDescAddr()),
                         "CNAS:FSM:HSD:PRE",
                         (VOS_UINT32)(CNAS_HSD_GetPreProcessStaTblSize()),
                         CNAS_HSD_GetPreProcStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RegMainL1Fsm
 ��������  : HSD L1 main״̬��ע��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE -- ע��ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RegMainL1Fsm(VOS_VOID)
{
    /* main״̬��ע�� */
    NAS_FSM_RegisterFsm((CNAS_HSD_GetMainFsmDescAddr()),
                         "CNAS:FSM:HSD:MAIN",
                         (VOS_UINT32)(CNAS_HSD_GetL1MainStaTblSize()),
                         CNAS_HSD_GetL1MainStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_HSD_InitFsmCtx_L1Main);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RegL2Fsm
 ��������  : HSD L1 main״̬��ע��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE -- ע��ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_RegL2Fsm(VOS_VOID)
{
    /* SwitchOn״̬��ע�� */
    NAS_FSM_RegisterFsm((CNAS_HSD_GetSwitchOnFsmDescAddr()),
                         "CNAS:FSM:HSD:SwitchOn",
                         (VOS_UINT32)CNAS_HSD_GetSwitchOnStaTblSize(),
                         CNAS_HSD_GetSwitchOnStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_HSD_InitFsmCtx_SwitchOn);

    /* PowerOff״̬��ע�� */
    NAS_FSM_RegisterFsm((CNAS_HSD_GetPowerOffFsmDescAddr()),
                         "CNAS:FSM:HSD:PowerOff",
                         (VOS_UINT32)CNAS_HSD_GetPowerOffStaTblSize(),
                         CNAS_HSD_GetPowerOffStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    /* SysAcq״̬��ע�� */
    NAS_FSM_RegisterFsm((CNAS_HSD_GetSysAcqFsmDescAddr()),
                         "CNAS:FSM:HSD:SysAcq",
                         (VOS_UINT32)CNAS_HSD_GetSysAcqStaTblSize(),
                         CNAS_HSD_GetSysAcqStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_HSD_InitFsmCtx_SysAcq);

    /* PowerSave״̬��ע�� */
    NAS_FSM_RegisterFsm((CNAS_HSD_GetPowerSaveFsmDescAddr()),
                         "CNAS:FSM:HSD:PowerSave",
                         (VOS_UINT32)CNAS_HSD_GetPowerSaveStaTblSize(),
                         CNAS_HSD_GetPowerSaveStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);

    /* InterSys״̬��ע�� */
    NAS_FSM_RegisterFsm((CNAS_HSD_GetInterSysFsmDescAddr()),
                         "CNAS:FSM:HSD:InterSys",
                         (VOS_UINT32)CNAS_HSD_GetInterSysStaTblSize(),
                         CNAS_HSD_GetInterSysStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_HSD_InitFsmCtx_InterSys);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_RegFsm
 ��������  : HSDע��״̬��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  CNAS_HSD_RegFsm(VOS_VOID)
{
    /* ע��Ԥ����״̬�� */
    CNAS_HSD_RegPreFsm();

    /* ע��L1״̬�� */
    CNAS_HSD_RegMainL1Fsm();

    /* ע��L2״̬�� */
    CNAS_HSD_RegL2Fsm();

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_PreProcessMsg
 ��������  : HSD��ϢԤ����
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- Ԥ�������
             VOS_FALSE -- ����Ҫ����״̬���д���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet      = VOS_FALSE;
    NAS_ACTION_FUNC                     pActFun    = VOS_NULL_PTR;
    NAS_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;

    /* ��ȡԤ����״̬����������ַ */
    pstFsmDesc = CNAS_HSD_GetPreFsmDescAddr();

    /* ��ȡ״̬ת�Ʊ��е���Ӧ�Ķ��������� */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, CNAS_HSD_L1_STA_PREPROC, ulEventType);

    /* ������ָ���� */
    if (VOS_NULL_PTR != pActFun )
    {
        /* ִ�к������ܲ��� */
        ulRet = (*pActFun) ( ulEventType, pstMsg);
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��    : CNAS_HSD_FsmProcessEvent
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
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

 *****************************************************************************/
VOS_UINT32 CNAS_HSD_FsmProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
)
{
    NAS_ACTION_FUNC                     pActFun;
    NAS_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    CNAS_INFO_LOG2(UEPS_PID_HSD, "CNAS_HSD_FsmProcessEvent", ulCurState, ulEventType);

    pstFsmDesc = CNAS_HSD_GetCurFsmDesc();

    /* ����״̬ת�Ʊ��е���Ӧ�Ķ��������� */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, ulCurState, ulEventType);

    if (VOS_NULL_PTR == pActFun)
    {
        /* ��Ϣδ������������������ */
        return VOS_FALSE;
    }

    /* ������ص��¼���������Ϊ��,�����������¼����� */
    ulRet   = (*pActFun) ( ulEventType,(struct MsgCB*)pRcvMsg);
    CNAS_INFO_LOG1(UEPS_PID_HSD, "CNAS_HSD_FsmProcessEvent", ulRet);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ProcessMsgInFsm
 ��������  : ��Ϣ״̬������
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ��Ϣ�������
             VOS_FALSE -- ��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    CNAS_HSD_FSM_CTX_STRU              *pstCurFsm = VOS_NULL_PTR;
    VOS_UINT16                          usOldStackDepth;
    VOS_UINT16                          usNewStackDepth;

    /* ��ȡ��ǰHSD��״̬�������� */
    pstCurFsm           = CNAS_HSD_GetCurFsmAddr();

    /* ��ȡ��ǰHSD��ջ��� */
    usOldStackDepth     = CNAS_HSD_GetFsmStackDepth();

    /* ��Ϣ���� */
    ulRet     = CNAS_HSD_FsmProcessEvent(pstCurFsm->ulState,
                                         ulEventType,
                                         (VOS_VOID*)pstMsg);

    /* ��ȡ��ǰHSD����ջ��� */
    usNewStackDepth    = CNAS_HSD_GetFsmStackDepth();

    /* ջ���û������,����û�д����µ�״̬���������˳�*/
    if (usNewStackDepth <= usOldStackDepth)
    {
        return ulRet;
    }

    /* �µ�ջ��ȴ����ϵ�ջ��� ����������ѹջ,��Ҫ����Ϣ����״̬���м������� */
    /* ���»�ȡ��ǰMMC�Ķ���״̬ */
    pstCurFsm   = CNAS_HSD_GetCurFsmAddr();

    /* ����Ϣ���붥��״̬������������ */
    ulRet       = CNAS_HSD_FsmProcessEvent(pstCurFsm->ulState,
                                           ulEventType,
                                           (VOS_VOID*)pstMsg);


    return ulRet;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ProcessHsdIntMsg
 ��������  : HSD�ڲ����е���Ϣ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��13��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_ProcessHsdIntMsg(VOS_VOID)
{
    MSG_HEADER_STRU                    *pstIntMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;

    pstIntMsg = (MSG_HEADER_STRU *)CNAS_HSD_GetNextIntMsg();

    while (VOS_NULL_PTR != pstIntMsg)
    {
        /* ��Ϣ���� */
        CNAS_MNTN_TraceIntMsg(pstIntMsg->ulSenderPid,
                              pstIntMsg->ulLength + VOS_MSG_HEAD_LENGTH,
                              (VOS_VOID *)pstIntMsg);

        ulEventType  = CNAS_BuildEventType(pstIntMsg->ulSenderPid, (VOS_UINT16)pstIntMsg->ulMsgName);

        /* ����Ѿ����������ȡ������Ϣ�������� */
        if (VOS_TRUE == CNAS_HSD_PreProcessMsg(ulEventType, (struct MsgCB*)pstIntMsg))
        {
            /* �ͷ��ڲ���Ϣ */
            PS_MEM_FREE(pstIntMsg->ulSenderPid, pstIntMsg);

            /* ������һ����Ϣ���� */
            pstIntMsg = (MSG_HEADER_STRU *)CNAS_HSD_GetNextIntMsg();

            continue;
        }

        /* ��Ϣ��״̬������ */
        CNAS_HSD_ProcessMsgInFsm(ulEventType, (struct MsgCB *)pstIntMsg);

        /* �ͷ��ڲ���Ϣ */
        PS_MEM_FREE(pstIntMsg->ulSenderPid, pstIntMsg);

        /* ������һ����Ϣ���� */
        pstIntMsg = (MSG_HEADER_STRU *)CNAS_HSD_GetNextIntMsg();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_ProcessBufferMsg
 ��������  : ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��22��
   ��    ��   : g00256031
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_ProcessBufferMsg(VOS_VOID)
{
    CNAS_HSD_MSG_STRU                  *pstEntryMsg = VOS_NULL_PTR;

    /* �ڴ�ռ���� */
    pstEntryMsg = (CNAS_HSD_MSG_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD, sizeof(CNAS_HSD_MSG_STRU) );

    if (VOS_NULL_PTR == pstEntryMsg)
    {
        return;
    }

    while (VOS_TRUE == CNAS_HSD_GetNextCachedMsg(pstEntryMsg))
    {
        /* ����Ѿ����������ȡ������Ϣ�������� */
        if (VOS_TRUE == CNAS_HSD_PreProcessMsg(pstEntryMsg->ulEventType, (struct MsgCB*)pstEntryMsg->aucMsgBuffer))
        {
            continue;
        }

        /* ����״̬������ */
        CNAS_HSD_ProcessMsgInFsm(pstEntryMsg->ulEventType, (struct MsgCB*)pstEntryMsg->aucMsgBuffer);

        /* �ڲ����е���Ϣ���� */
        CNAS_HSD_ProcessHsdIntMsg();
    }

    PS_MEM_FREE(UEPS_PID_HSD, pstEntryMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_MsgProc
 ��������  : HRPD HSDģ����Ϣ������ں���
 �������  : pMsg -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_HSD_MsgProc (struct MsgCB* pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pRcvTimerMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          usPrevStackDepth;
    VOS_UINT32                          usNewStackDepth;
    VOS_UINT32                          ulSenderPid;

    ulSenderPid = CNAS_CCB_GetModem0Pid(CNAS_CCB_GetCdmaModeModemId(), pstMsg->ulSenderPid);

    pstMsg->ulSenderPid = ulSenderPid;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* �����¼����� */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        pRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

        ulEventType  = CNAS_BuildEventType(pstMsgHeader->ulSenderPid, pRcvTimerMsg->ulName);

        /* ֹͣ��Ӧ�Ķ�ʱ�� */
        CNAS_StopTimer(UEPS_PID_HSD, pRcvTimerMsg->ulName, pRcvTimerMsg->ulPara);
    }
    else
    {
        ulEventType  = CNAS_BuildEventType(pstMsgHeader->ulSenderPid, (VOS_UINT16)pstMsgHeader->ulMsgName);
    }

    /* ����Ѿ����������ֱ�ӷ��� */
    if (VOS_TRUE == CNAS_HSD_PreProcessMsg(ulEventType, pstMsg))
    {
        /* �����ڲ���Ϣ���� */
        CNAS_HSD_ProcessHsdIntMsg();

        return;
    }

    /* ��ȡ��ǰHSD��ջ��� */
    usPrevStackDepth = CNAS_HSD_GetFsmStackDepth();

    /* ����״̬������ */
    CNAS_HSD_ProcessMsgInFsm(ulEventType, pstMsg);

    /* ��״̬���˳��󣬻�ȡ�µ�ջ��� */
    usNewStackDepth = CNAS_HSD_GetFsmStackDepth();

    /* �����ڲ���Ϣ���� */
    CNAS_HSD_ProcessHsdIntMsg();

    /* ���ջ����ȼ���,˵���϶���������ջ����,����һ�λ��� */
    if (usNewStackDepth < usPrevStackDepth)
    {
        CNAS_HSD_ProcessBufferMsg();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitTask
 ��������  : HRPD SDģ�������ʼ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE
             VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��12��12��
   ��    ��   : h00300778
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  CNAS_HSD_InitTask(VOS_VOID)
{
    /* ��ʼ��HSDȫ�ֱ��� */
    CNAS_HSD_InitCtx(CNAS_HSD_INIT_CTX_STARTUP);

    /* HSD ״̬��ע�� */
    CNAS_HSD_RegFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_InitPid
 ��������  : HRPD SDģ��PID��ʼ������
 �������  : enInitPhase -- ��ʼ���׶�
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_InitPid(
    enum VOS_INIT_PHASE_DEFINE         enInitPhase
)
{
    switch (enInitPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            /* ����HSDģ���ʼ������ */
            CNAS_HSD_InitTask();
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



