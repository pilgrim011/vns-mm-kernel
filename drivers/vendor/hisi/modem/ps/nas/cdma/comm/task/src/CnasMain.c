/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasMain.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2014��06��27��
  ��������   : ʵ��CDMA������1x��evdo��ģ��FID��ʼ����ע���Լ���PID��ע��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��06��27��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CnasMain.h"
#include "CnasXsdMain.h"
#include "CnasXregMain.h"
#include "CnasXccMain.h"
#include "CnasMntn.h"
#include "CnasCcb.h"
#include "CnasPrlApi.h"
#include "CnasHluMain.h"

#include "CnasHsdMain.h"

#include  "CnasHsmMain.h"

#include "CnasEhsmMain.h"

#include  "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
CNAS_INTERNAL_MSG_CTX_STRU              g_stCnasIntCtxInfo;

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 �� �� ��  : CNAS_GetIntMsgCtxAddr
 ��������  : ��ȡCNAS���������ݽṹ�׵�ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_INTERNAL_MSG_CTX_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��06��27��
   ��    ��   : y00245242
   �޸�����   : ������ȡ�ڲ���Ϣ������е�ָ��
*****************************************************************************/
CNAS_INTERNAL_MSG_CTX_STRU *CNAS_GetIntMsgCtxAddr(VOS_VOID)
{
    return &(g_stCnasIntCtxInfo);
}

/*****************************************************************************
 �� �� ��  : CNAS_InitIntMsgCtx
 ��������  : ��ʼ��CNAS�ڲ���Ϣ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��06��27��
   ��    ��   : y00245242
   �޸�����   : ������ȡ�ڲ���Ϣ������е�ָ��
*****************************************************************************/
VOS_VOID CNAS_InitIntMsgCtx(VOS_VOID)
{
    CNAS_INTERNAL_MSG_CTX_STRU         *pstInternalMsgCtx = VOS_NULL_PTR;

    /* ��ʼ��CNAS�ڲ���Ϣ���� */
    pstInternalMsgCtx                   = CNAS_GetIntMsgCtxAddr();
    CNAS_InitIntMsgBuf(pstInternalMsgCtx);

}

/*****************************************************************************
 �� �� ��  : CNAS_InitIntMsgBuf
 ��������  : ��ʼ���ڲ���Ϣ����
 �������  : CNAS_INTERNAL_MSG_CTX_STRU    *pstInternalMsgCtx
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��06��27��
   ��    ��   : y00245242
   �޸�����   : ������ȡ�ڲ���Ϣ������е�ָ��
 2.��    ��   : 2015��09��06��
   ��    ��   : w00176964
   �޸�����   : CNAS�ڴ�ü�����
*****************************************************************************/
VOS_VOID CNAS_InitIntMsgBuf(
    CNAS_INTERNAL_MSG_CTX_STRU         *pstInternalMsgCtx
)
{
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-6, begin */
    VOS_UINT32                          i;

    for (i = 0; i < CNAS_INTERNAL_MSG_MAX_QUEUE_SIZE; i++)
    {
        pstInternalMsgCtx->pastIntMsg[i] = VOS_NULL_PTR;
    }

    pstInternalMsgCtx->ucIntMsgNum = 0;
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-6, end */
}

/*****************************************************************************
 �� �� ��  : CNAS_GetIntMsgSendBuf
 ��������  : ���ڲ���Ϣ��������л�ȡ�ڲ���Ϣ���ͻ�����
 �������  : ulMsgID  -- ���󻺴���Ϣ��ID
             ulBufLen -- ���󻺴���Ϣ����
 �������  : ��
 �� �� ֵ  : CNAS_INTERNAL_MSG_BUF_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��06��27��
   ��    ��   : y00245242
   �޸�����   : ������ȡ�ڲ���Ϣ������е�ָ��
 2.��    ��   : 2015��09��06��
   ��    ��   : w00176964
   �޸�����   : CNAS�ڴ�ü�����
*****************************************************************************/
VOS_VOID *CNAS_GetIntMsgSendBuf(
    VOS_UINT32                          ulModuleId,
    VOS_UINT32                          ulBufLen
)
{
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-6, begin */
    VOS_VOID         *pstSendMsgBuf = VOS_NULL_PTR;

    pstSendMsgBuf = PS_MEM_ALLOC(ulModuleId, ulBufLen);
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-6, end */

    return pstSendMsgBuf;
}

/*****************************************************************************
 �� �� ��  : CNAS_SndInternalMsg
 ��������  : �����ڲ���Ϣ
 �������  : pSndMsg:�����͵���Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��27��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��09��06��
    ��    ��   : w00176964
    �޸�����   : CNAS�ڴ�ü�����
*****************************************************************************/
VOS_UINT32  CNAS_SndInternalMsg(
    VOS_VOID                           *pSndMsg
)
{
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-6, begin */
    VOS_UINT8                           ucIntMsgNum;
    MSG_HEADER_STRU                    *pstIntMsg = VOS_NULL_PTR;

    ucIntMsgNum = CNAS_GetIntMsgCtxAddr()->ucIntMsgNum;
    pstIntMsg   = (MSG_HEADER_STRU *)pSndMsg;

    /* ����ڲ���Ϣ���У��Ƿ��л���������� */
    if (CNAS_INTERNAL_MSG_MAX_QUEUE_SIZE <= ucIntMsgNum)
    {
        PS_MEM_FREE(pstIntMsg->ulSenderPid, pSndMsg);

        CNAS_ERROR_LOG(pstIntMsg->ulSenderPid, "CNAS_SndInternalMsg: msg queue is full!" );

        return VOS_FALSE;
    }

    /* ���浱ǰ��Ϣ */
    CNAS_GetIntMsgCtxAddr()->pastIntMsg[ucIntMsgNum] = pSndMsg;

    CNAS_GetIntMsgCtxAddr()->ucIntMsgNum = (ucIntMsgNum + 1);
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-6, end */

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : CNAS_GetNextInternalMsg
 ��������  : ��ȡ�ڲ���Ϣ�����е���һ�����õ��ڲ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ڲ���Ϣ���е�ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��06��27��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��09��06��
   ��    ��   : w00176964
   �޸�����   : CNAS�ڴ�ü�����
*****************************************************************************/
VOS_UINT8 *CNAS_GetNextInternalMsg(VOS_VOID)
{
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-6, begin */
    VOS_UINT8                           ucIntMsgNum;
    VOS_UINT8                          *pstIntMsg = VOS_NULL_PTR;

    ucIntMsgNum = CNAS_GetIntMsgCtxAddr()->ucIntMsgNum;

    if (0 < ucIntMsgNum)
    {
        /* ��ȡ��һ���������Ϣ��Ϣ */
        pstIntMsg = CNAS_GetIntMsgCtxAddr()->pastIntMsg[0];

        /* �ڲ���Ϣ��Ŀ����һ�� */
        ucIntMsgNum--;

        if (0 != ucIntMsgNum)
        {
            /* ǰ���ڲ���Ϣ */
            NAS_MEM_MOVE_S(&(CNAS_GetIntMsgCtxAddr()->pastIntMsg[0]),
                           CNAS_INTERNAL_MSG_MAX_QUEUE_SIZE * sizeof(VOS_UINT8 *),
                           &(CNAS_GetIntMsgCtxAddr()->pastIntMsg[1]),
                           ucIntMsgNum * sizeof(VOS_UINT8 *));
        }

        /* ����Ϣ������β������Ϣ��Ϊ��ָ�� */
        CNAS_GetIntMsgCtxAddr()->pastIntMsg[ucIntMsgNum] = VOS_NULL_PTR;

        CNAS_GetIntMsgCtxAddr()->ucIntMsgNum = ucIntMsgNum;
    }

    return pstIntMsg;
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-6, end */
}

/* Deleted by w00176964 for CNAS�ڴ�ü�, 2015-9-6, begin */

/* Deleted by w00176964 for CNAS�ڴ�ü�, 2015-9-6, end */
/*****************************************************************************
 �� �� ��  : CNAS_FindPidMsgProc
 ��������  : ���Ҵ�����Ϣ��PID����
 �������  : ulRcvPid -- ������ϢID
 �������  : ��
 �� �� ֵ  : pCnasPidMsgProc -- ������Ϣ���������ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��06��27��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��02��4��
   ��    ��   : w00176964
   �޸�����   : CDMA Iteration 8 Modified:����HSMģ����Ϣ������
*****************************************************************************/
pCnasPidMsgProc CNAS_FindPidMsgProc(
    VOS_UINT32                          ulRcvPid
)
{
    pCnasPidMsgProc                     pMsgProc = VOS_NULL_PTR;

    switch (ulRcvPid)
    {
        case UEPS_PID_XSD:
            pMsgProc = CNAS_XSD_MsgProc;
            break;

        case UEPS_PID_XREG:
            pMsgProc = CNAS_XREG_MsgProc;
            break;

        case UEPS_PID_XCC:
            pMsgProc = CNAS_XCC_MsgProc;
            break;

        case UEPS_PID_HLU:
            pMsgProc = CNAS_HLU_DispatchMsg;
            break;

        case UEPS_PID_HSD:
            pMsgProc = CNAS_HSD_MsgProc;
            break;

       case UEPS_PID_HSM:
           pMsgProc = CNAS_HSM_MsgProc;
           break;

        case UEPS_PID_EHSM:
            pMsgProc = CNAS_EHSM_MsgProcEntry;
            break;

        default:
            break;
    }

    return pMsgProc;
}

/*****************************************************************************
 �� �� ��  : CNAS_FidMsgProc
 ��������  : CDMA NAS����Ϣ��ڴ�����
 �������  : pRcvMsg -- ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_TRUE : ��Ϣ�������
             VOS_FALSE: ��Ϣ�쳣
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��06��27��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  CNAS_FidMsgProc(
    struct MsgCB                        *pRcvMsg
)
{
    pCnasPidMsgProc                     pMsgProc  = VOS_NULL_PTR;
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-6, begin */
    MSG_HEADER_STRU                    *pstIntMsg = VOS_NULL_PTR;
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-6, end */
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;

    /* ��ڲ������ */
    if (VOS_NULL_PTR == pRcvMsg)
    {
        /* ��ӡerror��Ϣ */
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_FidMsgProc: pRcvMsg pointer is NULL!");
        return VOS_FALSE;
    }

    pstMsgHeader = (MSG_HEADER_STRU *)pRcvMsg;
    CNAS_MNTN_LogMsgInfo(pstMsgHeader);

    pMsgProc = CNAS_FindPidMsgProc(pRcvMsg->ulReceiverPid);

    if (VOS_NULL_PTR == pMsgProc)
    {
        /* ��ӡerror��Ϣ */
        CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_FidMsgProc: pMsgProc pointer is NULL!");

        return VOS_FALSE;
    }

    pMsgProc(pRcvMsg);

    //��������Ϣ���¼ʱ��
    CNAS_MNTN_UpdateMsgExitTime();

    /* ��ȡCNAS�ڲ�������Ϣ */
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-6, begin */
    pstIntMsg = (MSG_HEADER_STRU *)CNAS_GetNextInternalMsg();
    /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-6, end */

    while (VOS_NULL_PTR != pstIntMsg)
    {
        /* ��Ϣ���� */
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-6, begin */
        CNAS_MNTN_TraceIntMsg(pstIntMsg->ulSenderPid,
                              pstIntMsg->ulLength + VOS_MSG_HEAD_LENGTH,
                              (VOS_VOID *)pstIntMsg);
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-6, end */

        /* ��ȡ��Ϣ������ָ�� */
        pMsgProc = CNAS_FindPidMsgProc(pstIntMsg->ulReceiverPid);

        if (VOS_NULL_PTR != pMsgProc)
        {
            /* ������Ϣ */
            pMsgProc((struct MsgCB *)pstIntMsg);
        }
        else
        {
            /* ��ӡerror��Ϣ */
            CNAS_ERROR_LOG(UEPS_PID_XSD, "CNAS_FidMsgProc: pMsgProc pointer is NULL!");
        }

        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-6, begin */
        /* �ͷ��ڲ���Ϣ */
        PS_MEM_FREE(pstIntMsg->ulSenderPid, pstIntMsg);

        /* ��ȡ��һ��CNAS�ڲ�������Ϣ */
        pstIntMsg = (MSG_HEADER_STRU *)CNAS_GetNextInternalMsg();
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-6, end */
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_XCC_InitTask
 ��������  : CNASģ�������ʼ������
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
VOS_VOID  CNAS_InitTask(VOS_VOID)
{
    /* ��ʼ��������Ϣ */
    CNAS_MNTN_InitCtx();

    /* ��ʼ����ʱ�� */
    CNAS_InitTimerCtx();

    /* ��ʼ��CNAS�ڲ����� */
    CNAS_InitIntMsgCtx();

    /* ��ʼ��CCB������ */
    CNAS_CCB_InitCcbCtx();

    /* ��ʼ��PRL������ */
    CNAS_PRL_InitPrlCtx(VOS_TRUE);
}
#endif

/*****************************************************************************
 �� �� ��  : CNAS_FidInit
 ��������  : CDMA NAS��FID��ʼ������
 �������  : enInitPhase:��ʼ���׶�
 �������  : ��
 �� �� ֵ  : VOS_TRUE : ��ʼ���ɹ�
             VOS_FALSE: ��ʼ��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��06��27��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��02��4��
   ��    ��   : w00176964
   �޸�����   : CDMA Iteration 8 Modified:����HSMģ���ʼ��
*****************************************************************************/
VOS_UINT32 CNAS_FidInit(enum VOS_INIT_PHASE_DEFINE enInitPhase)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32 ulReturnCode;

    switch (enInitPhase)
    {
        case VOS_IP_LOAD_CONFIG:
            ulReturnCode = VOS_RegisterPIDInfo(UEPS_PID_XSD,
                                               (Init_Fun_Type)CNAS_XSD_InitPid,
                                               (Msg_Fun_Type)CNAS_FidMsgProc);
            if (VOS_OK != ulReturnCode)
            {
                return VOS_ERR;
            }

            ulReturnCode = VOS_RegisterPIDInfo(UEPS_PID_XREG,
                                               (Init_Fun_Type)CNAS_XREG_InitPid,
                                               (Msg_Fun_Type)CNAS_FidMsgProc);
            if (VOS_OK != ulReturnCode)
            {
                return VOS_ERR;
            }


            ulReturnCode = VOS_RegisterPIDInfo(UEPS_PID_XCC,
                                               (Init_Fun_Type)CNAS_XCC_InitPid,
                                               (Msg_Fun_Type)CNAS_FidMsgProc);

            if (VOS_OK != ulReturnCode)
            {
                return VOS_ERR;
            }

            ulReturnCode = VOS_RegisterPIDInfo(UEPS_PID_HLU,
                                   (Init_Fun_Type)CNAS_HLU_InitPid,
                                   (Msg_Fun_Type)CNAS_FidMsgProc);

            if (VOS_OK != ulReturnCode)
            {
                return VOS_ERR;
            }

            ulReturnCode = VOS_RegisterPIDInfo(UEPS_PID_HSD,
                                               (Init_Fun_Type)CNAS_HSD_InitPid,
                                               (Msg_Fun_Type)CNAS_FidMsgProc);

            if (VOS_OK != ulReturnCode)
            {
                return VOS_ERR;
            }

            ulReturnCode = VOS_RegisterPIDInfo(UEPS_PID_HSM,
                                               (Init_Fun_Type)CNAS_HSM_InitPid,
                                               (Msg_Fun_Type)CNAS_FidMsgProc);

            if (VOS_OK != ulReturnCode)
            {
                return VOS_ERR;
            }


            ulReturnCode = VOS_RegisterPIDInfo(UEPS_PID_EHSM,
                                               (Init_Fun_Type)CNAS_EHSM_InitPid,
                                               (Msg_Fun_Type)CNAS_FidMsgProc);

            if (VOS_OK != ulReturnCode)
            {
                return VOS_ERR;
            }


            ulReturnCode = VOS_RegisterTaskPrio(UEPS_FID_CNAS, CNAS_TASK_PRIO);

            if (VOS_OK != ulReturnCode)
            {
                return VOS_ERR;
            }

            break;

        case VOS_IP_FARMALLOC:
            /* CNASģ�������ĳ�ʼ�� */
            CNAS_InitTask();

            break;

        case VOS_IP_INITIAL:
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

    }
#endif

    return VOS_OK;
}
/*lint -restore*/

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



