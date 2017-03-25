/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLcsMmMsgProc.c
    Description : ����MM����LCS����Ϣ
    History     :
            1.lihong  00150010       2015-09-28  Draft Enact
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "vos.h"
#include    "PsLogdef.h"
#include    "PsTypeDef.h"
#include    "NasLcsMmMsgProc.h"
#include    "NasLcsDecode.h"
#include    "NasLcsOm.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/



#define    THIS_FILE_ID            PS_FILE_ID_NASLCSMMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLCSMMMSGPROC_C

#if (FEATURE_LPP == FEATURE_ON)



/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
Function Name  : NAS_LCS_SndMmEstReq
Description    : ��LMM����LCS_MM_EST_REQ��������
Input          : ulTi--------------transation id
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-9-29  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_SndMmEstReq
(
    VOS_UINT32                          ulTi
)
{
    LCS_MM_EST_REQ_STRU                *pstMmEstReq = NAS_LCS_NULL_PTR;

    NAS_LCS_INFO_LOG("NAS_LCS_SndMmEstReq is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LCS_SndLmmEstReq_ENUM, LNAS_ENTRY);

    pstMmEstReq   = (VOS_VOID *)NAS_LCS_ALLOC_MSG(sizeof(LCS_MM_EST_REQ_STRU));
    if (NAS_LCS_NULL_PTR == pstMmEstReq)
    {
        return;
    }

    NAS_LCS_WRITE_MM_MSG_HEAD(  pstMmEstReq,
                                (sizeof(LCS_MM_EST_REQ_STRU)-
                                NAS_LCS_LEN_VOS_MSG_HEADER));

    pstMmEstReq->ulMsgId    = ID_LCS_MM_EST_REQ;
    pstMmEstReq->ulTi       = ulTi;

    NAS_LCS_SND_MSG(pstMmEstReq);
}

/*****************************************************************************
Function Name  : NAS_LCS_SndMmRelReq
Description    : ��LMM����LCS_MM_REL_REQ�������ͷ�ʵ��
Input          : ulTi--------------transation id
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-10-08  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_SndMmRelReq
(
    VOS_UINT32                          ulTi
)
{
    LCS_MM_REL_REQ_STRU                *pstMmRelReq = NAS_LCS_NULL_PTR;

    NAS_LCS_INFO_LOG("NAS_LCS_SndMmRelReq is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LCS_SndLmmRelReq_ENUM, LNAS_ENTRY);

    pstMmRelReq   = (VOS_VOID *)NAS_LCS_ALLOC_MSG(sizeof(LCS_MM_REL_REQ_STRU));
    if (NAS_LCS_NULL_PTR == pstMmRelReq)
    {
        return;
    }

    NAS_LCS_WRITE_MM_MSG_HEAD(  pstMmRelReq,
                                (sizeof(LCS_MM_REL_REQ_STRU)-
                                NAS_LCS_LEN_VOS_MSG_HEADER));

    pstMmRelReq->ulMsgId    = ID_LCS_MM_REL_REQ;
    pstMmRelReq->ulTi       = ulTi;

    NAS_LCS_SND_MSG(pstMmRelReq);
}

/*****************************************************************************
Function Name  : NAS_LCS_SndMmDataReq
Description    : ��LMM����LCS_MM_DATA_REQ
Input          : ulTi--------------------TI
                 ulLength----------------��Ϣ����
                 pucSendMsg--------------������Ϣָ��
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-10-16  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_SndMmDataReq
(
    VOS_UINT32                          ulTi,
    VOS_UINT32                          ulLength,
    const VOS_UINT8                    *pucSendMsg
)
{
    LCS_MM_DATA_REQ_STRU               *pstMmDataReq   = NAS_LCS_NULL_PTR;
    VOS_UINT32                          ulTmpLength     = 0;

    NAS_LCS_INFO_LOG("NAS_LCS_SndMmDataReq is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LCS_SndMmDataReq_ENUM, LNAS_ENTRY);

    /*���ݿտ���Ϣ�ĳ��ȷ���ռ�*/
    if( 0 == ulLength)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_SndMmDataReq: WARNING: Msg Length is zero");
        TLPS_PRINT2LAYER_WARNING(NAS_LCS_SndMmDataReq_ENUM, LNAS_LCS_LengthZero);
        return ;
    }
    else if(ulLength > NAS_LCS_MIN_SND_MSG_LEN)
    {
        ulTmpLength     = ulLength - NAS_LCS_MIN_SND_MSG_LEN ;
        ulTmpLength     = sizeof(LCS_LMM_DATA_REQ_STRU) + ulTmpLength;
        pstMmDataReq    = (VOS_VOID*)NAS_LCS_ALLOC_MSG(ulTmpLength);
    }
    else
    {
        ulTmpLength     = sizeof(LCS_LMM_DATA_REQ_STRU);
        pstMmDataReq    = (VOS_VOID*)NAS_LCS_ALLOC_MSG(ulTmpLength);
    }

    if (NAS_LCS_NULL_PTR == pstMmDataReq)
    {
        return;
    }

    NAS_LCS_WRITE_MM_MSG_HEAD(  pstMmDataReq,
                                (ulTmpLength - NAS_LCS_LEN_VOS_MSG_HEADER));

    pstMmDataReq->ulMsgId  = ID_LCS_MM_DATA_REQ;
    pstMmDataReq->ulTi      = ulTi;
    pstMmDataReq->stLcsMsg.ulLcsMsgSize = ulLength;

    /*lint -e669*/
    NAS_LCS_MEM_CPY_S(      pstMmDataReq->stLcsMsg.aucLcsMsg,
                            ulLength,
                            pucSendMsg,
                            ulLength);
    /*lint +e699*/

    NAS_LCS_SND_MSG(pstMmDataReq);
}


/*****************************************************************************
Function Name  : NAS_LCS_JudgeSndMmRelReq
Description    : �ж��Ƿ���LCS_MM_REL_REQ�������Ҫ����
Input          : ulIndex--------------ʵ������
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-10-09  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_JudgeSndMmRelReq
(
    VOS_UINT32                          ulIndex
)
{
    if (NAS_LCS_DOMAIN_TYPE_CS_LCS == NAS_LCS_GetEntityLcsDomain(ulIndex))
    {
        NAS_LCS_SndMmRelReq(NAS_LCS_GetEntityTi(ulIndex));
    }
}


/*****************************************************************************
Function Name  : NAS_LCS_RcvMmEstCnf
Description    : MM_LCS_EST_CNF��Ϣ������
Input          : VOS_VOID *pstEstCnf
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-10-08  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_RcvMmEstCnf
(
    const MM_LCS_EST_CNF_STRU          *pstEstCnf
)
{
    VOS_UINT32                          ulRslt          = NAS_LCS_FAIL;
    VOS_UINT32                          ulIndex         = 0;

    /* ͨ��OPID���ҹ���ʵ�� */
    ulRslt = NAS_LCS_QueryMolrEntity(pstEstCnf->ulTi, &ulIndex);
    if (NAS_LCS_FAIL == ulRslt)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvMmEstCnf:query entity fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvMmEstCnf_ENUM, LNAS_LCS_QueryEntityFail);
        return ;
    }

    /* �ж�ʵ��״̬�Ƿ�Ϊ�ȴ�������Ӧ�������ǣ���ֱ�ӷ��� */
    if (NAS_LCS_ENTITY_STATE_WAIT_NW_RSP != NAS_LCS_GetEntityState(ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvMmEstCnf:entity state invalid!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvMmEstCnf_ENUM, LNAS_LCS_EntityStateInvalid);
        return ;
    }

    /* �ж�ʵ�����Ƿ���CS��ģ�������ǣ���ֱ�ӷ��� */
    if (NAS_LCS_DOMAIN_TYPE_CS_LCS != NAS_LCS_GetEntityLcsDomain(ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvMmEstCnf:cur domain mismatch!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvMmEstCnf_ENUM, LNAS_LCS_EntityCurDomainMismatch);
        return ;
    }

    /* ��������״̬Ϊ����̬ */
    NAS_LCS_SetEntityConnState(ulIndex, NAS_LCS_CONN_STATE_CONN);

    /* ����REGISTER��Ϣ������MM */
    NAS_LCS_SndRegister(ulIndex);
}

/*****************************************************************************
Function Name  : NAS_LCS_RcvMmDataInd
Description    : MM_LCS_DATA_IND��Ϣ������
Input          : VOS_VOID *pstDataInd
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-10-08  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_RcvMmDataInd
(
    MM_LCS_DATA_IND_STRU               *pstDataInd
)
{
    NAS_LCS_MEM_SET_S(  &g_stLcsCnDecodeMsgStru,
                        sizeof(NAS_LCS_CN_MSG_STRU),
                        0,
                        sizeof(NAS_LCS_CN_MSG_STRU));

    NAS_LCS_ProcAirMsg( pstDataInd->stLcsMsg.aucLcsMsg,
                        pstDataInd->stLcsMsg.ulLcsMsgSize,
                        &g_stLcsCnDecodeMsgStru,
                        NAS_LCS_DOMAIN_TYPE_CS_LCS);
}

/*****************************************************************************
Function Name  : NAS_LCS_RcvMmRelInd
Description    : MM_LCS_REL_IND��Ϣ������
Input          : VOS_VOID *pstRelInd
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-10-10  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_RcvMmRelInd
(
    const MM_LCS_REL_IND_STRU          *pstRelInd
)
{
    VOS_UINT32                          ulRslt  = 0;
    VOS_UINT32                          ulIndex = 0;
    TAF_LCS_CAUSE_ENUM_UINT32           enTafLcsCause = TAF_LCS_CAUSE_SUCCESS;

    /* ͨ��TI���ҹ���ʵ�� */
    ulRslt = NAS_LCS_QueryLcsEntity(pstRelInd->ulTi, &ulIndex);
    if (NAS_LCS_FAIL == ulRslt)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvMmRelInd:query entity fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvMmRelInd_ENUM, LNAS_LCS_QueryEntityFail);
        NAS_LCS_SndOmEntityInfo();
        return ;
    }

    enTafLcsCause = pstRelInd->ulRelCause + TAF_LCS_CAUSE_MM_ERR_BEGIN;

    /* �����MO-LR */
    if (PS_TRUE == NAS_LCS_IsMoLr(ulIndex))
    {
        NAS_LCS_SetEntityConnState(ulIndex, NAS_LCS_CONN_STATE_IDLE);

        /* ����ؽ�����ʱ�������У��򲻴��� */
        if (NAS_LCS_TIMER_RUNNING == NAS_LCS_IsTimerRunning(ulIndex, TI_NAS_LCS_WATI_REEST_TIMER))
        {
            NAS_LCS_SndOmEntityInfo();
            return ;
        }

        /* �����������MO-LR���������ڼ��״̬���򲻴��� */
        if ((NAS_LCS_MO_LR_TAF_INDEX == ulIndex)
            && (LCS_REP_MODE_PERIODIC_RPT == NAS_LCS_GetMolrMode())
            && (NAS_LCS_ENTITY_STATE_PERIOD_INTERVAL == NAS_LCS_GetEntityState(ulIndex)))
        {
            NAS_LCS_SndOmEntityInfo();
            return ;
        }

        /* ����CS MOLR������·�쳣 */
        NAS_LCS_ProcMolrConnAbnormal(ulIndex, enTafLcsCause);

        NAS_LCS_SndOmEntityInfo();
        return ;
    }

    /* �ͷŵ���LCSʵ�岢֪ͨ������ */
    NAS_LCS_ClearLcsEntityAndNotify(ulIndex, enTafLcsCause);
    NAS_LCS_SndOmEntityInfo();
}

/*****************************************************************************
Function Name  : NAS_LCS_MmMsgDistr
Description    : LCSģ��MM��Ϣ������
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-9-28  �¿���
*****************************************************************************/
VOS_VOID NAS_LCS_MmMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pMmMsg  = VOS_NULL_PTR;

    pMmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    NAS_LCS_INFO_LOG("NAS_LCS_MmMsgDistr is entered!");
    TLPS_PRINT2LAYER_INFO1(NAS_LCS_MmMsgDistr_ENUM, LNAS_ENTRY, pMmMsg->ulMsgName);

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch(pMmMsg->ulMsgName)
    {
        case ID_MM_LCS_EST_CNF:
            NAS_LCS_RcvMmEstCnf((MM_LCS_EST_CNF_STRU *)pRcvMsg);
            break;

        case ID_MM_LCS_DATA_IND:
            NAS_LCS_RcvMmDataInd((MM_LCS_DATA_IND_STRU *)pRcvMsg);
            break;

        case ID_MM_LCS_REL_IND:
            NAS_LCS_RcvMmRelInd((MM_LCS_REL_IND_STRU *)pRcvMsg);
            break;

        default:
            NAS_LCS_WARN_LOG("NAS_LCS_MmMsgDistr:NORM: Error MsgId!");
            TLPS_PRINT2LAYER_ERROR(NAS_LCS_MmMsgDistr_ENUM, LNAS_LCS_InvalidRsvMsgId);
            break;
    }

    return;
}


#endif
#ifdef __cplusplus
#if __cplusplus
    }
    #endif
#endif
/* end of NasLcsMmMsgProc.c */
