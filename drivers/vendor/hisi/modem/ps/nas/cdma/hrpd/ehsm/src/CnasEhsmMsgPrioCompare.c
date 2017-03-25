/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasEhsmMsgPrioCompare.c
  �� �� ��   : ����
  ��    ��   : h00246512
  ��������   : 2015��5��27��
  ����޸�   :
  ��������   : CnasEhsmMsgPrioCompare.h��ʵ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��5��27��
    ��    ��   : h00246512
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasEhsmMsgPrioCompare.h"
#include  "NasFsm.h"
#include  "CnasEhsmSndInternalMsg.h"
#include  "CnasCcb.h"
#include  "ehsm_hsd_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_CNAS_EHSM_MSG_PRIO_COMPARE_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/*****************************************************************************
 ȫ�ֱ�����    : g_astEhmsMsgPrioCompareWithActivatingTbl
 ȫ�ֱ���˵��  : Activating״̬����Ϣ���ȼ��Ƚϴ���ıȽϱ�
 1.��    ��   : 2015��5��27��
   ��    ��   : h00246512
   �޸�����   : �½�

*****************************************************************************/
CNAS_EHSM_MSG_COMPARE_STRU g_astEhsmMsgPrioCompareWithActivatingTbl[] =
{
    /* Activating�������յ�HSD�Ĺػ��������Ϣ���ȼ��Ƚ� */
    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSD, ID_HSD_EHSM_POWER_OFF_REQ),
                               CNAS_EHSM_CompareHsdPowerOffReqPrioWithActivating),

    /* Activating�������յ�HSD�Ĺػ��������Ϣ���ȼ��Ƚ� */
    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSM, ID_HSM_EHSM_SUSPEND_IND),
                               CNAS_EHSM_CompareHsmSuspendIndPrioWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(MSPS_PID_PPPC, ID_CTTF_CNAS_EHRPD_DETACH_IND),
                               CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_DEACTIVATE_REQ),
                               CNAS_EHSM_CompareTafPdnDeactivateReqWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_RECONN_REQ),
                               CNAS_EHSM_CompareTafPdnReconnReqWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ),
                               CNAS_EHSM_CompareTafPdnActivateReqWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_LOC_DETACH_NOTIFY),
                               CNAS_EHSM_CompareTafLocalDetachNotifyWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_LOC_DEACTIVATE_NOTIFY),
                               CNAS_EHSM_CompareTafLocalDeactivateNotifyWithActivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSM, ID_HSM_EHSM_SESSION_INFO_IND),
                               CNAS_EHSM_CompareHsmSessionInfoIndPrioWithActivating)/* ,

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSD, ID_HSD_EHSM_POWER_SAVE_REQ),
                               CNAS_EHSM_CompareHsdPowerSaveReqPrioWithActivating)*/
};

/*****************************************************************************
 ȫ�ֱ�����    : g_astEhmsMsgPrioCompareWithDeactivatingTbl
 ȫ�ֱ���˵��  : Activating״̬����Ϣ���ȼ��Ƚϴ���ıȽϱ�
 1.��    ��   : 2015��5��27��
   ��    ��   : h00246512
   �޸�����   : �½�

*****************************************************************************/
CNAS_EHSM_MSG_COMPARE_STRU g_astEhsmMsgPrioCompareWithDeactivatingTbl[] =
{
    /* Deactivating�������յ�HSD�Ĺػ��������Ϣ���ȼ��Ƚ� */
    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSD, ID_HSD_EHSM_POWER_OFF_REQ),
                               CNAS_EHSM_CompareHsdPowerOffReqPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSM, ID_HSM_EHSM_SUSPEND_IND),
                               CNAS_EHSM_CompareHsmSuspendIndPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(MSPS_PID_PPPC, ID_CTTF_CNAS_EHRPD_DETACH_IND),
                               CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ),
                               CNAS_EHSM_CompareTafPdnActivateReqPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_DEACTIVATE_REQ),
                               CNAS_EHSM_CompareTafPdnDeactivateReqPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_RECONN_REQ),
                               CNAS_EHSM_CompareTafReconnReqPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_LOC_DETACH_NOTIFY),
                               CNAS_EHSM_CompareTafLocalDetachNotifyPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_LOC_DEACTIVATE_NOTIFY),
                               CNAS_EHSM_CompareTafLocalDeactivateNotifyWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSM, ID_HSM_EHSM_SESSION_INFO_IND),
                               CNAS_EHSM_CompareHsmSessionInfoIndPrioWithDeactivating),

    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_DISC_NOTIFY),
                               CNAS_EHSM_CompareTafDiscNotifyPrioWithDeactivating)/* ,


    CNAS_EHSM_COMPARE_TBL_ITEM(CNAS_BuildEventType(UEPS_PID_HSD, ID_HSD_EHSM_POWER_SAVE_REQ),
                               CNAS_EHSM_CompareHsdPowerSaveReqPrioWithDeactivating)*/

};



/*****************************************************************************
 ȫ�ֱ�����    : g_astEhsmMsgCompareTbl
 ȫ�ֱ���˵��  : EHSM״̬���ȽϺ�����
  1.��    ��   : 2015��5��27��
    ��    ��   : h00246512
    �޸�����   : �½�
*****************************************************************************/
CNAS_EHSM_FSM_MSG_COMPARE_STRU g_astEhsmMsgCompareTbl[] =
{
    /* ACTIVATING ״̬���ȽϺ�����*/
    CNAS_EHSM_FSM_COMPARE_TBL_ITEM(CNAS_EHSM_FSM_ACTIVATING,
                                 g_astEhsmMsgPrioCompareWithActivatingTbl),

    /* DEACTIVATING ״̬���ȽϺ�����*/
    CNAS_EHSM_FSM_COMPARE_TBL_ITEM(CNAS_EHSM_FSM_DEACTIVATING,
                                 g_astEhsmMsgPrioCompareWithDeactivatingTbl),
};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : CNAS_EHSM_CompareHsdPowerOffReqPrioWithActivating
 ��������  : ��EHSM�յ���HSD��power off��Ϣ��Activating״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��27��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareHsdPowerOffReqPrioWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    CNAS_EHSM_StartTimer(TI_CNAS_EHSM_PROTECTING_POWER_OFF_PROCESS, TI_CNAS_EHSM_PROTECTING_POWER_OFF_PROCESS_LEN);

    CNAS_EHSM_ClearAllCacheMsg();

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : CNAS_EHSM_CompareHsmSuspendIndPrioWithActivating
 ��������  : ��EHSM�յ���HSM��Suspend��Ϣ��Activating״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��27��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareHsmSuspendIndPrioWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithActivating
 ��������  : ��EHSM�յ���CTTF��Ehrpd_Detach_Ind��Ϣ��Activating״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��27��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    VOS_UINT32                              i;
    CNAS_EHSM_CACHE_MSG_QUEUE_STRU         *pstMsgQueue = VOS_NULL_PTR;
    MSG_HEADER_STRU                        *pstCacheMsgHdr;
    REL_TIMER_MSG                          *pstTimerMsg;
    VOS_UINT32                              ulCacheMsgEventType;

    pstMsgQueue     = CNAS_EHSM_GetCacheMsgAddr();
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    /* ���֮ǰ����Ĳ���Ҫ�������Ϣ */
    for (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        pstCacheMsgHdr = (MSG_HEADER_STRU *)(pstMsgQueue->pastCacheMsg[i]);

        if (VOS_NULL_PTR == pstCacheMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

            ulCacheMsgEventType  = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulCacheMsgEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
        }

        if ((CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_DEACTIVATE_REQ) == ulCacheMsgEventType)
         || (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_RECONN_REQ)         == ulCacheMsgEventType)
         || (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ)   == ulCacheMsgEventType))
        {
            CNAS_EHSM_ClearCacheMsg((VOS_UINT8)i);
        }
    }

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_CompareTafPdnDeactivateReqWithActivating
 ��������  : ��EHSM�յ���TAF��Pdn Deactivate Req��Ϣ��Activating״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��8��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafPdnDeactivateReqWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    VOS_UINT8                           ucCid;
    APS_EHSM_PDN_DEACTIVATE_REQ_STRU   *pstPdnDeactReq;

    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    pstPdnDeactReq  = (APS_EHSM_PDN_DEACTIVATE_REQ_STRU*)pstMsg;
    ucCid           = CNAS_EHSM_GetCid_Activating();

    if (ucCid == pstPdnDeactReq->ucCid)
    {
        return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
    }


    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_CompareTafPdnReconnReqWithActivating
 ��������  : ��EHSM�յ���TAF��Pdn Reconn Req��Ϣ��Activating״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��8��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafPdnReconnReqWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_CompareTafPdnActivateReqWithActivating
 ��������  : ��EHSM�յ���TAF��Pdn Activate Req��Ϣ��Activating״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��8��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafPdnActivateReqWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}


/*****************************************************************************
 �� �� ��  : CNAS_EHSM_CompareTafLocalDetachNotifyWithActivating
 ��������  : ��EHSM�յ���TAF��ID_APS_EHSM_LOC_DETACH_NOTIFY��Ϣ��Activating״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��8��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafLocalDetachNotifyWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_CompareTafLocalDeactivateNotifyWithActivating
 ��������  : ��EHSM�յ���TAF��ID_APS_EHSM_LOC_DEACTIVATE_NOTIFY��Ϣ��Activating״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��8��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��9��9��
   ��    ��   : w00176964
   �޸�����   : CNAS�ڴ�ü�
*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafLocalDeactivateNotifyWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    VOS_UINT32                              i;
    CNAS_EHSM_CACHE_MSG_QUEUE_STRU         *pstMsgQueue = VOS_NULL_PTR;
    APS_EHSM_PDN_ACTIVATE_REQ_STRU         *pstPdnAct;
    APS_EHSM_PDN_DEACTIVATE_REQ_STRU       *pstPdnDeact;
    APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU    *pstLocPdnDeact;
    /* Added by w00176964 for CNAS�ڴ�ü�, 2015-9-9, begin */
    MSG_HEADER_STRU                        *pstCacheMsgHdr;
    REL_TIMER_MSG                          *pstTimerMsg;
    VOS_UINT32                              ulCacheMsgEventType;
    /* Added by w00176964 for CNAS�ڴ�ü�, 2015-9-9, end */

    pstMsgQueue     = CNAS_EHSM_GetCacheMsgAddr();
    pstLocPdnDeact  = (APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU*)pstMsg;
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    /* �鿴��������û����ͬCID�Ĳ������еĻ���������� */
    for  (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, begin */
        pstCacheMsgHdr          = (MSG_HEADER_STRU *)(pstMsgQueue->pastCacheMsg[i]);

        if (VOS_NULL_PTR == pstCacheMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

            ulCacheMsgEventType  = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulCacheMsgEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
        }

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ) == ulCacheMsgEventType)
        {
            pstPdnAct = (APS_EHSM_PDN_ACTIVATE_REQ_STRU*)pstCacheMsgHdr;
            if (pstLocPdnDeact->ucCid == pstPdnAct->ucCid)
            {
                CNAS_EHSM_ClearCacheMsg((VOS_UINT8)i);
                return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_DISCARD;
            }
        }

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_DEACTIVATE_REQ) == ulCacheMsgEventType)
        {
            pstPdnDeact = (APS_EHSM_PDN_DEACTIVATE_REQ_STRU*)pstCacheMsgHdr;
            if (pstLocPdnDeact->ucCid == pstPdnDeact->ucCid)
            {
                CNAS_EHSM_ClearCacheMsg((VOS_UINT8)i);
            }
        }
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, end */
    }

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}



/*****************************************************************************
 �� �� ��  : CNAS_EHSM_CompareHsdPowerOffReqPrioWithDeactivating
 ��������  : ��EHSM�յ���HSD��power off��Ϣ��Deactivating״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��27��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareHsdPowerOffReqPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    CNAS_EHSM_StartTimer(TI_CNAS_EHSM_PROTECTING_POWER_OFF_PROCESS, TI_CNAS_EHSM_PROTECTING_POWER_OFF_PROCESS_LEN);

    CNAS_EHSM_ClearAllCacheMsg();

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_CompareHsmSuspendIndPrioWithDeactivating
 ��������  : ��EHSM�յ���HSM��Suspend��Ϣ��Deactivating״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��27��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareHsmSuspendIndPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithDeactivating
 ��������  : ��EHSM�յ���CTTF��Detach Ind��Ϣ��Deactivating״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��27��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    VOS_UINT32                              i;
    CNAS_EHSM_CACHE_MSG_QUEUE_STRU         *pstMsgQueue = VOS_NULL_PTR;
    MSG_HEADER_STRU                        *pstCacheMsgHdr;
    REL_TIMER_MSG                          *pstTimerMsg;
    VOS_UINT32                              ulCacheMsgEventType;

    pstMsgQueue     = CNAS_EHSM_GetCacheMsgAddr();
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    /* ���֮ǰ����Ĳ���Ҫ�������Ϣ */
    for (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        pstCacheMsgHdr = (MSG_HEADER_STRU *)(pstMsgQueue->pastCacheMsg[i]);

        if (VOS_NULL_PTR == pstCacheMsgHdr)
        {
            continue;
        }

        if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

            ulCacheMsgEventType  = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulCacheMsgEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
        }

        if ((CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_DEACTIVATE_REQ) == ulCacheMsgEventType)
         || (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_RECONN_REQ)         == ulCacheMsgEventType)
         || (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ)   == ulCacheMsgEventType))
        {
            CNAS_EHSM_ClearCacheMsg((VOS_UINT8)i);
        }
    }

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_CompareTafPdnActivateReqPrioWithDeactivating
 ��������  : ��EHSM�յ���APS��Pdn Activate Req��Ϣ��Deactivating״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��27��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafPdnActivateReqPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_CompareTafPdnDeactivateReqPrioWithDeactivating
 ��������  : ��EHSM�յ���APS��Pdn Deactivate Req��Ϣ��Deactivating״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��27��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafPdnDeactivateReqPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_CompareTafReconnReqPrioWithDeactivating
 ��������  : ��EHSM�յ���APS��Reconn Req��Ϣ��Deactivating״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��27��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafReconnReqPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_CompareTafLocalDetachNotifyPrioWithDeactivating
 ��������  : ��EHSM�յ���ID_APS_EHSM_LOC_DETACH_NOTIFY��Ϣ��Deactivating״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��5��27��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafLocalDetachNotifyPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}


/*****************************************************************************
 �� �� ��  : CNAS_EHSM_CompareTafLocalDeactivateNotifyWithDeactivating
 ��������  : ��EHSM�յ���TAF��ID_APS_EHSM_LOC_DEACTIVATE_NOTIFY��Ϣ��Deactivating״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��6��8��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��9��8��
   ��    ��   : w00176964
   �޸�����   : CNAS�ڴ�ü�
*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafLocalDeactivateNotifyWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    VOS_UINT32                              i;
    CNAS_EHSM_CACHE_MSG_QUEUE_STRU         *pstMsgQueue = VOS_NULL_PTR;
    APS_EHSM_PDN_ACTIVATE_REQ_STRU         *pstPdnAct;
    APS_EHSM_PDN_DEACTIVATE_REQ_STRU       *pstPdnDeact;
    APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU    *pstLocPdnDeact;
    /* Added by w00176964 for CNAS�ڴ�ü�, 2015-9-9, begin */
    MSG_HEADER_STRU                        *pstCacheMsgHdr;
    VOS_UINT32                              ulCacheMsgEventType;
    REL_TIMER_MSG                          *pstTimerMsg;
    /* Added by w00176964 for CNAS�ڴ�ü�, 2015-9-9, end */

    pstMsgQueue     = CNAS_EHSM_GetCacheMsgAddr();
    pstLocPdnDeact  = (APS_EHSM_LOC_DEACTIVATE_NOTIFY_STRU*)pstMsg;
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    /* �鿴��������û����ͬCID�Ĳ������еĻ���������� */
    for  (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, begin */
        pstCacheMsgHdr          = (MSG_HEADER_STRU *)(pstMsgQueue->pastCacheMsg[i]);

        if (VOS_PID_TIMER == pstCacheMsgHdr->ulSenderPid)
        {
            pstTimerMsg = (REL_TIMER_MSG *)pstCacheMsgHdr;

            ulCacheMsgEventType  = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstTimerMsg->ulName);
        }
        else
        {
            ulCacheMsgEventType = CNAS_BuildEventType(pstCacheMsgHdr->ulSenderPid, pstCacheMsgHdr->ulMsgName);
        }

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_ACTIVATE_REQ) == ulCacheMsgEventType)
        {
            pstPdnAct = (APS_EHSM_PDN_ACTIVATE_REQ_STRU*)pstCacheMsgHdr;
            if (pstLocPdnDeact->ucCid == pstPdnAct->ucCid)
            {
                CNAS_EHSM_ClearCacheMsg((VOS_UINT8)i);
                return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_DISCARD;
            }
        }

        if (CNAS_BuildEventType(WUEPS_PID_TAF, ID_APS_EHSM_PDN_DEACTIVATE_REQ) == ulCacheMsgEventType)
        {
            pstPdnDeact = (APS_EHSM_PDN_DEACTIVATE_REQ_STRU*)pstCacheMsgHdr;
            if (pstLocPdnDeact->ucCid == pstPdnDeact->ucCid)
            {
                CNAS_EHSM_ClearCacheMsg((VOS_UINT8)i);
            }
        }
        /* Modified by w00176964 for CNAS�ڴ�ü�, 2015-9-9, end */
    }

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithActivating
 ��������  : ��EHSM�յ���CTTF��Ehrpd_Detach_Ind��Ϣ��Activating״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��14��
   ��    ��   : y00314741
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareHsmSessionInfoIndPrioWithActivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    HSM_EHSM_SESSION_INFO_IND_STRU     *pstSessionInfo = VOS_NULL_PTR;

    pstSessionInfo = (HSM_EHSM_SESSION_INFO_IND_STRU *)pstMsg;

    if (EHSM_HSM_SESSION_TYPE_EHRPD != pstSessionInfo->enSessionType)
    {
        *penAbortType = CNAS_EHSM_ABORT_BUTT;

        return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
    }
    else
    {
        *penAbortType = CNAS_EHSM_ABORT_FSM_IMMEDIATELY;

        return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_CompareCttfEhrpdDetachIndPrioWithActivating
 ��������  : ��EHSM�յ���CTTF��Ehrpd_Detach_Ind��Ϣ��Activating״̬�������ȼ����бȽ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ����
 �������  : penAbortType:�������
 �� �� ֵ  : �ȽϽ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��14��
   ��    ��   : y00314741
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareHsmSessionInfoIndPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    HSM_EHSM_SESSION_INFO_IND_STRU     *pstSessionInfo = VOS_NULL_PTR;

    pstSessionInfo = (HSM_EHSM_SESSION_INFO_IND_STRU *)pstMsg;

    if (EHSM_HSM_SESSION_TYPE_EHRPD != pstSessionInfo->enSessionType)
    {
        *penAbortType   = CNAS_EHSM_ABORT_BUTT;

        return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ABORT;
    }
    else
    {
        *penAbortType = CNAS_EHSM_ABORT_FSM_IMMEDIATELY;

        return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_INITFSM;
    }
}

/*****************************************************************************
 �� �� ��  : CNAS_EHSM_CompareTafDiscNotifyPrioWithDeactivating
 ��������  : DEACTIVING״̬�»��洦��TAF������DISC_NOTIFY��Ϣ
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
             CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��20��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_EHSM_CompareTafDiscNotifyPrioWithDeactivating(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    *penAbortType   = CNAS_EHSM_ABORT_BUTT;

    return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_STORE;
}


/*****************************************************************************
 �� �� ��  : CNAS_EHSM_FindMsgPrioCompareFun
 ��������  : ������Ϣ�ȽϺ���
 �������  : ulEventType:���������Ϣ����
             pstMsg     :���������Ϣ����
             ulFsmEntryEventType    :״̬���������Ϣ
             enFsmId                :״̬����ID
 �������  : ��
 �� �� ֵ  : ��ǰ��������Ϣ�����ȼ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��27��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_EHSM_MSG_COMPARE_FUNC  CNAS_EHSM_FindMsgPrioCompareFun(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_FSM_ID_ENUM_UINT32        enFsmId
)
{
    CNAS_EHSM_FSM_MSG_COMPARE_STRU     *pstFsmCompareTbl = VOS_NULL_PTR;
    VOS_UINT32                          i;
    VOS_UINT32                          ulTblSize;

    ulTblSize = sizeof(g_astEhsmMsgCompareTbl)/sizeof(CNAS_EHSM_FSM_MSG_COMPARE_STRU);

    for ( i = 0 ; i < ulTblSize ; i++ )
    {
        if ( enFsmId == g_astEhsmMsgCompareTbl[i].enFsmId)
        {
            pstFsmCompareTbl = &g_astEhsmMsgCompareTbl[i];
            break;
        }
    }

    /* δ���ҵ���״̬���ıȽϺ�����,ֱ�ӷ��ؿ�ָ�� */
    if ( VOS_NULL_PTR == pstFsmCompareTbl )
    {
        return VOS_NULL_PTR;
    }

    for ( i = 0 ; i < pstFsmCompareTbl->ulSize; i++ )
    {
        /* ���Ҳ�ͬ�¼��ıȽϺ��� */
        if ( pstFsmCompareTbl->pfCompareTbl[i].ulCurrEventType == ulEventType)
        {
            return pstFsmCompareTbl->pfCompareTbl[i].pfCompareFun;
        }
    }

    /* δ�ҵ�������ֱ�ӷ��ؿ�ָ�� */
    return VOS_NULL_PTR;
}



/*****************************************************************************
 �� �� ��  : CNAS_EHSM_GetMsgComparePrio
 ��������  : ��ȡ��Ϣ���ȼ��ȽϺ�Ľ��
 �������  : ulEventType:���������Ϣ����
             pstMsg     :���������Ϣ����
 �������  : pulAbortType:����ֵΪ���ʱ,���صĴ������
 �� �� ֵ  : ��ǰ��������Ϣ�����ȼ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��27��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
*****************************************************************************/
CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32 CNAS_EHSM_GetMsgComparePrioRslt(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    CNAS_EHSM_ABORT_FSM_TYPE_UINT8     *penAbortType
)
{
    CNAS_EHSM_MSG_COMPARE_FUNC                      pfCompareFunc;
    CNAS_EHSM_FSM_ID_ENUM_UINT32                    enCurrFsmId;
    CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_ENUM_UINT32     enRslt;

    /*  ��ȡ��ǰ״̬����ID */
    enCurrFsmId         = CNAS_EHSM_GetCurrFsmId();

    if (CNAS_EHSM_FSM_BUTT <= enCurrFsmId)
    {
        CNAS_ERROR_LOG(UEPS_PID_EHSM, "ERROR:FsmId Error");
    }

    /*  ��ȡ�ȽϺ��� CNAS_EHSM_FindMsgPrioCompareFun() */
    pfCompareFunc       = CNAS_EHSM_FindMsgPrioCompareFun(ulEventType, pstMsg, enCurrFsmId);

    /* δ�ҵ�������,��Ĭ����Ϣ���� */
    if ( VOS_NULL_PTR == pfCompareFunc )
    {
        *penAbortType = CNAS_EHSM_ABORT_BUTT;
        return CNAS_EHSM_MSG_COMPARE_PRIO_RSLT_DISCARD;
    }

    /* ���ñȽϺ���,�������ȼ��ʹ������ */
    enRslt = pfCompareFunc(ulEventType, pstMsg, penAbortType);

    return enRslt;

}


#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

