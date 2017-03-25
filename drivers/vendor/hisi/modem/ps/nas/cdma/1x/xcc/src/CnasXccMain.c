/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccMain.c
  �� �� ��   : ����
  ��    ��   : Y00213812
  ��������   : 2014��06��27��
  ��������   : 1X CC(call control)ģ�������ʼ����������ں�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��06��27��
    ��    ��   : Y00213812
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "PsTypeDef.h"
#include  "CnasCcb.h"
#include  "CnasXccMain.h"
#include  "CnasXccFsmMainTbl.h"
#include  "CnasXccFsmMoCallingTbl.h"
#include  "CnasXccFsmMtCallingTbl.h"
#include  "CnasXccFsmMainTbl.h"
#include  "CnasXccInstanceMgmt.h"
#include  "CnasMntn.h"
#include  "CnasXccMainCtrl.h"
#include  "NasFsm.h"
#include  "CnasXccComFunc.h"
#include  "CnasXccCtx.h"
#include  "xsd_xcc_pif.h"
#include  "CnasXccSndXsd.h"
#include  "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_XCC_RegMainL1Fsm
 ��������  : XCC L1 main״̬��ע��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE -- ע��ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��07��04��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RegMainL1Fsm(VOS_VOID)
{
    /* main״̬��ע�� */

    NAS_FSM_RegisterFsm((CNAS_XCC_GetMainFsmDescAddr()),
                         "CNAS:FSM:XCC:MAIN",
                         (VOS_UINT32)(CNAS_XCC_GetL1MainStaTblSize()),
                         CNAS_XCC_GetL1MainStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_XCC_InitFsmCtx_L1Main);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RegL2Fsm
 ��������  : XCC L1 main״̬��ע��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE -- ע��ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��07��04��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_RegL2Fsm(VOS_VOID)
{
    /* L2״̬��ע�� */
    /* MO CALLING״̬��ע�� */
    NAS_FSM_RegisterFsm((CNAS_XCC_GetMoCallingFsmDescAddr()),
                         "CNAS:FSM:XCC:MO CALLING",
                         (VOS_UINT32)CNAS_XCC_GetMoCallingStaTblSize(),
                         CNAS_XCC_GetMoCallingStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_XCC_InitFsmCtx_MoCalling);

    /* MT CALLING״̬��ע�� */
    NAS_FSM_RegisterFsm((CNAS_XCC_GetMtCallingFsmDescAddr()),
                         "CNAS:FSM:XCC:MT CALLING",
                         (VOS_UINT32)CNAS_XCC_GetMtCallingStaTblSize(),
                         CNAS_XCC_GetMtCallingStaTbl(),
                         VOS_NULL_PTR,
                         CNAS_XCC_InitFsmCtx_MtCalling);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_RegFsm
 ��������  : XCCע��״̬��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��04��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  CNAS_XCC_RegFsm(VOS_VOID)
{
    /* ע��L1״̬�� */
    CNAS_XCC_RegMainL1Fsm();

    /* ע��L2״̬�� */
    CNAS_XCC_RegL2Fsm();
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_LoadSpecifiedCallInstEntity
 ��������  : ����ָ����call instanceʵ��
 �������  : pstFsmEntity -- call instanceʵ���ַ

 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��09��09��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_LoadSpecifiedCallInstEntity(
    CNAS_XCC_FSM_ENTITY_STRU           *pstFsmEntity
)
{
    /* �Ѷ�Ӧ��״̬��ʵ�����Ϊ��ǰ״̬�� */
    CNAS_XCC_GetCtxAddr()->pstCurFsmEntity = pstFsmEntity;

    pstFsmEntity->stCurFsm.ucConnectId = pstFsmEntity->stCallInfoCtx.ucConnectId;
}

/*****************************************************************************
 �� �� ��    : CNAS_XCC_FSM_ProcessEvent
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
   1.��    ��   : 2014��7��04��
     ��    ��   : Y00213812
     �޸�����   : �����ɺ���

 *****************************************************************************/
VOS_UINT32 CNAS_XCC_FSM_ProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg
)
{
    NAS_ACTION_FUNC                     pActFun;
    NAS_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt     = VOS_FALSE;

    CNAS_INFO_LOG2(UEPS_PID_XCC,
                   "CNAS_XCC_FsmProcessEvent",
                   ulCurState, ulEventType);

    pstFsmDesc = CNAS_XCC_GetCurFsmDesc();

    /* ����״̬ת�Ʊ��е���Ӧ�Ķ��������� */
    pActFun = NAS_FSM_FindAct(pstFsmDesc, ulCurState, ulEventType);

    /* ������ָ���� */
    if (VOS_NULL_PTR == pActFun)
    {
        /* ��Ϣδ������������������ */
        return VOS_FALSE;
    }

    /* ������ص��¼���������Ϊ��,�����������¼����� */
    ulRslt   = (*pActFun) (ulEventType, (struct MsgCB*)pRcvMsg);

    CNAS_INFO_LOG1(UEPS_PID_XCC, "CNAS_XCC_FsmProcessEvent", ulRslt);

    return ulRslt;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcBufferReqMsg
 ��������  : �������������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��09��10��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��09��10��
   ��    ��   : w00176964
   �޸�����   : CNAS�ڴ�ü�����
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcBufferReqMsg(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucMsgNum;
    VOS_UINT8                           ucActInstNum;
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, begin */
    MSG_HEADER_STRU                    *pstBufferMsgHdr;
    VOS_UINT32                          ulBufferMsgEventType;
    REL_TIMER_MSG                      *pstTimerMsg;
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, end */

    /* ��ȡ��ǰ�����call instance��Ŀ */
    ucActInstNum = CNAS_XCC_GetActivedCallInstanceNum();

    /* ��ȡ��ǰ������Ϣ��Ŀ */
    ucMsgNum     = CNAS_XCC_GetBufferedMsgNum();

    /* ע: �����ǰ��Ϣ���ܴ�����Ҫ�������棬�����·ŵ��˶��е�β�����ڱ�ѭ�������һ��
     *     ���ڶ���ͷ���ĸ���Ϣ����ˣ����������������л������Ϣһ�Σ���Ҫ��������Ļᱻ
     *     ���±��ŵ���Ϣ������
     */

    for (i = 0; i < ucMsgNum; i++)
    {
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, begin */
        pstBufferMsgHdr = (MSG_HEADER_STRU *)CNAS_XCC_GetNextBufferMsg();

        if (VOS_NULL_PTR == pstBufferMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstBufferMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstBufferMsgHdr;

            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulBufferMsgEventType = CNAS_BuildEventType(pstBufferMsgHdr->ulSenderPid, pstBufferMsgHdr->ulMsgName);
        }

        /* ���������ǹػ������������ȴ�����call instanceȥ���� */
        if ((CNAS_BuildEventType(UEPS_PID_XSD, ID_XSD_XCC_POWER_OFF_REQ) == ulBufferMsgEventType)
         && (0                                                           != ucActInstNum))
        {
            return;
        }

        /* main���� */
        if (VOS_FALSE == CNAS_XCC_ProcessMsgInMainCtrl(ulBufferMsgEventType,
                                                       (struct MsgCB *)pstBufferMsgHdr))
        {
            /* �ⲿ��Ϣ��״̬������ */
            CNAS_XCC_ProcessMsgInFsm(ulBufferMsgEventType,
                                     (struct MsgCB *)pstBufferMsgHdr);

        }
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, end */

        /* �����ڲ���Ϣ���� */
        CNAS_XCC_ProcXccIntMsg();

        /* �ͷŻ�����Ϣ */
        CNAS_XCC_FreeCurrentBufferMsg();
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcessMsgInFsm
 ��������  : ��Ϣ״̬������
 �������  : ulEventType -- ��Ϣ����+PID
             pMsg        -- ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ��Ϣ�������
             VOS_FALSE -- ��Ϣ����δ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��04��
   ��    ��   : Y00213812
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_XCC_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulRslt;
    VOS_UINT16                                              usOldStackDepth;
    VOS_UINT16                                              usNewStackDepth;
    CNAS_XCC_FSM_ENTITY_LIST_STRU                           stFsmEntityList;
    CNAS_XCC_FSM_ENTITY_STRU                               *pstFsmEntity = VOS_NULL_PTR;
    CNAS_XCC_FSM_CTX_STRU                                  *pstCurFsm    = VOS_NULL_PTR;
    VOS_UINT8                                               i;

    ulRslt = VOS_TRUE;

    /* ��ȡ������Ҫ�����call control instance�б� */
    NAS_MEM_SET_S(&stFsmEntityList, sizeof(CNAS_XCC_FSM_ENTITY_LIST_STRU), 0, sizeof(CNAS_XCC_FSM_ENTITY_LIST_STRU));

    CNAS_XCC_GetCallInstanceEntity(ulEventType, pstMsg, &stFsmEntityList);

    for (i = 0; i < CNAS_MIN(stFsmEntityList.ucFsmNum, CNAS_XCC_MAX_FSM_ENTITY_NUM); i++)
    {
        pstFsmEntity = (stFsmEntityList.pstFsmEntity[i]);

        CNAS_INFO_LOG1(UEPS_PID_XCC, "CNAS_XCC_ProcessMsgInFsm",
                       pstFsmEntity->stCallInfoCtx.ucConnectId);

        /* ����ָ����call control instance״̬�� */
        CNAS_XCC_LoadSpecifiedCallInstEntity(pstFsmEntity);

        /* ��ȡ��ǰXCC��״̬�������� */
        pstCurFsm           = CNAS_XCC_GetCurFsmAddr();

        /* ��ȡ��ǰXCC��ջ��� */
        usOldStackDepth    = CNAS_XCC_GetFsmStackDepth();

        /* ��Ϣ���� */
        ulRslt    = CNAS_XCC_FSM_ProcessEvent(pstCurFsm->ulState,
                                              ulEventType,
                                             (VOS_VOID*)pstMsg);

        /* ��ȡ��ǰXCC����ջ��� */
        usNewStackDepth    = CNAS_XCC_GetFsmStackDepth();

        /* ջ���û������,����û�д����µ�״̬���������˳�*/
        if (usNewStackDepth <= usOldStackDepth)
        {
            continue;
        }

        /* �µ�ջ��ȴ����ϵ�ջ��� ����������ѹջ,��Ҫ����Ϣ����״̬���м������� */
        /* ���»�ȡ��ǰXCC�Ķ���״̬ */
        pstCurFsm   = CNAS_XCC_GetCurFsmAddr();

        /* ����Ϣ���붥��״̬������������ */
        ulRslt      = CNAS_XCC_FSM_ProcessEvent(pstCurFsm->ulState,
                                                ulEventType,
                                                (VOS_VOID*)pstMsg );
    }

    return ulRslt;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_ProcXccIntMsg
 ��������  : ����XCCģ���ڲ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��09��15��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_XCC_ProcXccIntMsg(VOS_VOID)
{
    MSG_HEADER_STRU                    *pstIntMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;


    pstIntMsg = (MSG_HEADER_STRU *)CNAS_XCC_GetNextIntMsg();

    while (VOS_NULL_PTR != pstIntMsg)
    {
        /* ��Ϣ���� */
        CNAS_MNTN_TraceIntMsg(pstIntMsg->ulSenderPid,
                              pstIntMsg->ulLength + VOS_MSG_HEAD_LENGTH,
                              (VOS_VOID *)pstIntMsg);

        ulEventType  = CNAS_BuildEventType(pstIntMsg->ulSenderPid, (VOS_UINT16)pstIntMsg->ulMsgName);

        if (VOS_FALSE == CNAS_XCC_ProcessMsgInMainCtrl(ulEventType, (struct MsgCB *)pstIntMsg))
        {
            /* ��Ϣ��״̬������ */
            CNAS_XCC_ProcessMsgInFsm(ulEventType, (struct MsgCB *)pstIntMsg);
        }

        /* �ͷ��ڲ���Ϣ */
        PS_MEM_FREE(pstIntMsg->ulSenderPid, pstIntMsg);

        /* ������һ����Ϣ���� */
        pstIntMsg = (MSG_HEADER_STRU *)CNAS_XCC_GetNextIntMsg();
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_MsgProc
 ��������  : 1X CCģ����Ϣ������ں���
 �������  : pstMsg -- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��06��28��
   ��    ��   : Y00213812
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��5��22��
   ��    ��   : w00242748
   �޸�����   : CDMA Iteration 15 modified

*****************************************************************************/
VOS_VOID CNAS_XCC_MsgProc (struct MsgCB* pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pRcvTimerMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           ulOldActInstNum;
    VOS_UINT8                           ulNewActInstNum;
    VOS_UINT32                          ulSenderPid;

    ulSenderPid = CNAS_CCB_GetModem0Pid(CNAS_CCB_GetCdmaModeModemId(), pstMsg->ulSenderPid);

    pstMsg->ulSenderPid = ulSenderPid;

    /* ��ȡ��Ϣͷ */
    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* �����¼����� */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        pRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

        ulEventType  = CNAS_BuildEventType(pstMsgHeader->ulSenderPid, pRcvTimerMsg->ulName);

        /* ֹͣ��Ӧ�Ķ�ʱ�� */
        CNAS_StopTimer(UEPS_PID_XCC, pRcvTimerMsg->ulName, pRcvTimerMsg->ulPara);
    }
    else
    {
        ulEventType  = CNAS_BuildEventType(pstMsgHeader->ulSenderPid,
                                           (VOS_UINT16)pstMsgHeader->ulMsgName);
    }

    /* ��ȡ��Ϣ����ǰ�����call instance��Ŀ */
    ulOldActInstNum = CNAS_XCC_GetActivedCallInstanceNum();

    /* main���� */
    if (VOS_FALSE == CNAS_XCC_ProcessMsgInMainCtrl(ulEventType, pstMsg))
    {
        /* �ⲿ��Ϣ��״̬������ */
        CNAS_XCC_ProcessMsgInFsm(ulEventType, pstMsg);
    }

    /* �����ڲ���Ϣ���� */
    CNAS_XCC_ProcXccIntMsg();

    /* ��ȡ��Ϣ����󼤻��call instance��Ŀ */
    ulNewActInstNum = CNAS_XCC_GetActivedCallInstanceNum();

    /* ����µļ���call instance��Ŀ����0��С����Ϣ����ǰ�����call instance��Ŀ������������ */
    if ((0               == ulNewActInstNum)
     || (ulNewActInstNum <  ulOldActInstNum))
    {
        /* ��������û�������Ϣ */
        CNAS_XCC_ProcBufferReqMsg();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_InitTask
 ��������  : 1X CCģ�������ʼ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE
             VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��06��27��
   ��    ��   : Y00213812
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  CNAS_XCC_InitTask(VOS_VOID)
{
    /* ��ʼ��XCCȫ�ֱ��� */
    CNAS_XCC_InitCtx(CNAS_XCC_INIT_TYPE_POWER_ON);

    /* XCC ״̬��ע�� */
    CNAS_XCC_RegFsm();

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_InitPid
 ��������  : 1X CCģ��PID��ʼ������
 �������  : enInitPhase -- ��ʼ���׶�
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_XCC_InitPid(
    enum VOS_INIT_PHASE_DEFINE         enInitPhase
)
{
    switch (enInitPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            /* ����XCCģ���ʼ������ */
            CNAS_XCC_InitTask();
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



