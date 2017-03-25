/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLcsEmmMsgProc.c
    Description : ����EMM����LCS����Ϣ
    History     :
            1.lihong  00150010       2015-09-28  Draft Enact
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "vos.h"
#include    "PsLogdef.h"
#include    "PsTypeDef.h"
#include    "LmmLcsInterface.h"
#include    "NasLcsEmmMsgProc.h"
#include    "NasLcsDecode.h"
#include    "NasLcsMmMsgProc.h"
#include    "NasLcsEncode.h"
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



#define    THIS_FILE_ID            PS_FILE_ID_NASLCSEMMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLCSEMMMSGPROC_C

#if (FEATURE_LPP == FEATURE_ON)



/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
Function Name  : NAS_LCS_SndLmmEstReq
Description    : ��LMM����LCS_LMM_EST_REQ��������
Input          : ulOpid---------------opid
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-9-29  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_SndLmmEstReq
(
    VOS_UINT32                          ulOpid
)
{
    LCS_LMM_EST_REQ_STRU               *pstLmmEstReq = NAS_LCS_NULL_PTR;

    NAS_LCS_INFO_LOG("NAS_LCS_SndLmmEstReq is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LCS_SndLmmEstReq_ENUM, LNAS_ENTRY);

    pstLmmEstReq   = (VOS_VOID *)NAS_LCS_ALLOC_MSG(sizeof(LCS_LMM_EST_REQ_STRU));
    if (NAS_LCS_NULL_PTR == pstLmmEstReq)
    {
        return;
    }

    NAS_LCS_WRITE_LMM_MSG_HEAD( pstLmmEstReq,
                                (sizeof(LCS_LMM_EST_REQ_STRU)-
                                NAS_LCS_LEN_VOS_MSG_HEADER));

    pstLmmEstReq->ulMsgId   = ID_LCS_LMM_EST_REQ;
    pstLmmEstReq->ulOpId    = ulOpid;

    NAS_LCS_SND_MSG(pstLmmEstReq);
}

/*****************************************************************************
Function Name  : NAS_LCS_SndLmmDataReq
Description    : ��LMM����LCS_LMM_DATA_REQ
Input          : ulOpid------------------opid
                 ulLength----------------��Ϣ����
                 pucSendMsg--------------������Ϣָ��
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-10-16  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_SndLmmDataReq
(
    VOS_UINT32                          ulOpid,
    VOS_UINT32                          ulLength,
    const VOS_UINT8                    *pucSendMsg
)
{
    LCS_LMM_DATA_REQ_STRU              *pstLmmDataReq   = NAS_LCS_NULL_PTR;
    VOS_UINT32                          ulTmpLength     = 0;

    NAS_LCS_INFO_LOG("NAS_LCS_SndLmmDataReq is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LCS_SndLmmDataReq_ENUM, LNAS_ENTRY);

    /*���ݿտ���Ϣ�ĳ��ȷ���ռ�*/
    if( 0 == ulLength)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_SndLmmDataReq: WARNING: Msg Length is zero");
        TLPS_PRINT2LAYER_WARNING(NAS_LCS_SndLmmDataReq_ENUM, LNAS_LCS_LengthZero);
        return ;
    }
    else if(ulLength > NAS_LCS_MIN_SND_MSG_LEN)
    {
        ulTmpLength     = ulLength - NAS_LCS_MIN_SND_MSG_LEN ;
        ulTmpLength     = sizeof(LCS_LMM_DATA_REQ_STRU) + ulTmpLength;
        pstLmmDataReq   = (VOS_VOID*)NAS_LCS_ALLOC_MSG(ulTmpLength);
    }
    else
    {
        ulTmpLength     = sizeof(LCS_LMM_DATA_REQ_STRU);
        pstLmmDataReq   = (VOS_VOID*)NAS_LCS_ALLOC_MSG(ulTmpLength);
    }

    if (NAS_LCS_NULL_PTR == pstLmmDataReq)
    {
        return;
    }

    NAS_LCS_WRITE_LMM_MSG_HEAD( pstLmmDataReq,
                                (ulTmpLength - NAS_LCS_LEN_VOS_MSG_HEADER));

    pstLmmDataReq->ulMsgId  = ID_LCS_LMM_DATA_REQ;
    pstLmmDataReq->ulOpId   = ulOpid;
    pstLmmDataReq->stLcsMsg.ulLcsMsgSize = ulLength;

    /*lint -e669*/
    NAS_LCS_MEM_CPY_S(      pstLmmDataReq->stLcsMsg.aucLcsMsg,
                            ulLength,
                            pucSendMsg,
                            ulLength);
    /*lint +e669*/

    NAS_LCS_SND_MSG(pstLmmDataReq);
}


/*****************************************************************************
Function Name  : NAS_LCS_TryToChangeDomain
Description    : ���Ի���
Input          : ulIndex-------------ʵ������
                 enTafLcsCause-------ԭ��ֵ
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-9-30  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_TryToChangeDomain
(
    VOS_UINT32                          ulIndex,
    TAF_LCS_CAUSE_ENUM_UINT32           enTafLcsCause
)
{
    /* �����֧��CS-LCS��������LPP����MO-LR����ʵ���������1���ߵ�ǰ����CS-LCS��
       �򲻻������LCSʵ�� */
    if ((PS_FALSE == NAS_LCS_IsLteSupportCsLcs())
        || (NAS_LCS_MO_LR_LPP_INDEX == ulIndex)
        || (NAS_LCS_GetLcsEntityNum() > 1)
        || (NAS_LCS_DOMAIN_TYPE_CS_LCS == NAS_LCS_GetEntityLcsDomain(ulIndex)))
    {
        NAS_LCS_ClearLcsEntityAndNotify(ulIndex, enTafLcsCause);
        return ;
    }

    /* ������ΪCS-LCS */
    NAS_LCS_SetEntityLcsDomain(ulIndex, NAS_LCS_DOMAIN_TYPE_CS_LCS);

    /* ��0���Դ��� */
    NAS_LCS_ResetEntityEstRetryTimers(ulIndex);

    /* ����MM���� */
    NAS_LCS_SndMmEstReq(NAS_LCS_GetEntityTi(ulIndex));

    NAS_LCS_SetEntityConnState(ulIndex, NAS_LCS_CONN_STATE_ESTING);
}

/*****************************************************************************
Function Name  : NAS_LCS_RcvLmmEstCnf
Description    : LMM_LCS_EST_CNF��Ϣ������
Input          : VOS_VOID *pstEstCnf
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-9-30  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_RcvLmmEstCnf
(
    const LMM_LCS_EST_CNF_STRU         *pstEstCnf
)
{
    VOS_UINT32                          ulRslt          = NAS_LCS_FAIL;
    VOS_UINT32                          ulIndex         = 0;
    TAF_LCS_CAUSE_ENUM_UINT32           enTafLcsCause;

    /* ͨ��OPID���ҹ���ʵ�� */
    ulRslt = NAS_LCS_QueryMolrEntity(pstEstCnf->ulOpId, &ulIndex);
    if (NAS_LCS_FAIL == ulRslt)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvLmmEstCnf:query entity fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvLmmEstCnf_ENUM, LNAS_LCS_QueryEntityFail);
        NAS_LCS_SndOmEntityInfo();
        return ;
    }

    /* �ж�ʵ��״̬�Ƿ�Ϊ�ȴ�������Ӧ�������ǣ���ֱ�ӷ��� */
    if (NAS_LCS_ENTITY_STATE_WAIT_NW_RSP != NAS_LCS_GetEntityState(ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvLmmEstCnf:entity state invalid!");
        TLPS_PRINT2LAYER_ERROR1(NAS_LCS_RcvLmmEstCnf_ENUM, LNAS_LCS_EntityStateInvalid, NAS_LCS_GetEntityState(ulIndex));
        return ;
    }

    /* �ж�ʵ�����Ƿ���EPC��ģ�������ǣ���ֱ�ӷ��� */
    if (NAS_LCS_DOMAIN_TYPE_EPC_LCS != NAS_LCS_GetEntityLcsDomain(ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvLmmEstCnf:cur domain mismatch!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvLmmEstCnf_ENUM, LNAS_LCS_EntityCurDomainMismatch);
        return ;
    }

    if (LMM_LCS_EST_RSLT_SUCC == pstEstCnf->enEstRst)
    {
        /* ��������״̬Ϊ����̬ */
        NAS_LCS_SetEntityConnState(ulIndex, NAS_LCS_CONN_STATE_CONN);

        /* ����REGISTER��Ϣ������LMM */
        NAS_LCS_SndRegister(ulIndex);

        return ;
    }

    enTafLcsCause = NAS_LCS_LmmEstCnfCauseMap(pstEstCnf->enEstRst);

    if ((LMM_LCS_EST_RSLT_FAIL_3411_RUNNING == pstEstCnf->enEstRst)
        || (LMM_LCS_EST_RSLT_FAIL_SERVICE_FAIL == pstEstCnf->enEstRst))
    {
        /* ����EPC MOLR������·�쳣 */
        NAS_LCS_ProcMolrConnAbnormal(ulIndex, enTafLcsCause);
        return ;
    }

    /* ����ԭ��ֵ������ܻ��������򣬷����ͷ�ʵ����Ϣ */
    NAS_LCS_TryToChangeDomain(ulIndex, enTafLcsCause);
}

/*****************************************************************************
Function Name  : NAS_LCS_RcvLmmDataCnf
Description    : LMM_LCS_DATA_CNF��Ϣ������
Input          : VOS_VOID *pstDataCnf
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-9-28  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_RcvLmmDataCnf
(
    const LMM_LCS_DATA_CNF_STRU        *pstDataCnf
)
{
    VOS_UINT32                          ulRslt      = NAS_LCS_FAIL;
    VOS_UINT32                          ulIndex     = 0;
    NAS_LCS_CAUSE_ENUM_UINT32           enTafLcsCause;

    /* ͨ��OPID���ҹ���ʵ�� */
    ulRslt = NAS_LCS_QueryMolrEntity(pstDataCnf->ulOpId, &ulIndex);
    if (NAS_LCS_FAIL == ulRslt)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvLmmDataCnf:query entity fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvLmmDataCnf_ENUM, LNAS_LCS_QueryEntityFail);
        NAS_LCS_SndOmEntityInfo();
        return ;
    }

    /* �ж�ʵ��״̬�Ƿ�Ϊ�ȴ�������Ӧ�������ǣ���ֱ�ӷ��� */
    if (NAS_LCS_ENTITY_STATE_WAIT_NW_RSP != NAS_LCS_GetEntityState(ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvLmmDataCnf:entity state invalid!");
        TLPS_PRINT2LAYER_ERROR1(NAS_LCS_RcvLmmDataCnf_ENUM, LNAS_LCS_EntityStateInvalid, NAS_LCS_GetEntityState(ulIndex));
        return ;
    }

    /* �ж�ʵ�����Ƿ���EPC��ģ�������ǣ���ֱ�ӷ��� */
    if (NAS_LCS_DOMAIN_TYPE_EPC_LCS != NAS_LCS_GetEntityLcsDomain(ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvLmmDataCnf:cur domain mismatch!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvLmmDataCnf_ENUM, LNAS_LCS_EntityCurDomainMismatch);
        return ;
    }

    if (LMM_LCS_SEND_RSLT_SUCCESS == pstDataCnf->enDataCnfRst)
    {
        return ;
    }

    enTafLcsCause = NAS_LCS_LmmDataCnfCauseMap(pstDataCnf->enDataCnfRst);

    if ((LMM_LCS_SEND_RSLT_RSLT_FAIL_3411_RUNNING == pstDataCnf->enDataCnfRst)
        || (LMM_LCS_SEND_RSLT_FAIL_LOW_LAYER == pstDataCnf->enDataCnfRst))
    {
        /* ����EPC MOLR������·�쳣 */
        NAS_LCS_ProcMolrConnAbnormal(ulIndex, enTafLcsCause);
        return ;
    }

    /* ����ԭ��ֵ������ܻ��������򣬷����ͷ�ʵ����Ϣ */
    NAS_LCS_TryToChangeDomain(ulIndex, enTafLcsCause);
}

/*****************************************************************************
Function Name  : NAS_LCS_RcvLmmDataInd
Description    : LMM_LCS_DATA_IND��Ϣ������
Input          : VOS_VOID *pstDataInd
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-10-08  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_RcvLmmDataInd
(
    LMM_LCS_DATA_IND_STRU              *pstDataInd
)
{
    NAS_LCS_MEM_SET_S(  &g_stLcsCnDecodeMsgStru,
                        sizeof(NAS_LCS_CN_MSG_STRU),
                        0,
                        sizeof(NAS_LCS_CN_MSG_STRU));

    NAS_LCS_ProcAirMsg( pstDataInd->stLcsMsg.aucLcsMsg,
                        pstDataInd->stLcsMsg.ulLcsMsgSize,
                        &g_stLcsCnDecodeMsgStru,
                        NAS_LCS_DOMAIN_TYPE_EPC_LCS);
}

/*****************************************************************************
Function Name  : NAS_LCS_RcvLmmPosCapInfoInd
Description    : LMM_LCS_POS_CAP_INFO_IND��Ϣ������
Input          : VOS_VOID *pstPosCapInfoInd
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-9-28  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_RcvLmmPosCapInfoInd
(
    const LMM_LCS_POS_CAP_INFO_IND_STRU    *pstPosCapInfoInd
)
{
    NAS_LCS_NW_CAP_INFO_STRU           *pstNwLcsCap     = NAS_LCS_NULL_PTR;
    VOS_UINT32                          i               = 0;
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity    = NAS_LCS_NULL_PTR;

    /* �洢����LCS���� */
    pstNwLcsCap = NAS_LCS_GetNwLcsCap();
    pstNwLcsCap->enNwCsLcs  = pstPosCapInfoInd->enNwCsLcs;
    pstNwLcsCap->enNwEpcLcs = pstPosCapInfoInd->enNwEpcLcs;

    /* ����EPC-LCSʵ�壬�ж��Ƿ�֧��EPC-LCS���������֧�֣����ͷ�LCSʵ�� */
    if (NAS_LCS_NW_EPC_LCS_SUPPORT == pstNwLcsCap->enNwEpcLcs)
    {
        return ;
    }

    for (i = NAS_LCS_MO_LR_LPP_INDEX; i <= NAS_LCS_MT_LR_ENTITY_INDEX_END; i++)
    {
        pstLcsEntity = NAS_LCS_GetLcsEntity(i);

        if (NAS_LCS_ENTITY_USED != pstLcsEntity->enUsedFlag)
        {
            continue ;
        }

        if (NAS_LCS_DOMAIN_TYPE_EPC_LCS != NAS_LCS_GetEntityLcsDomain(i))
        {
            continue ;
        }

        /* �ͷŵ���LCSʵ�岢֪ͨ������ */
        NAS_LCS_ClearLcsEntityAndNotify(i, TAF_LCS_CAUSE_LCS_NOT_SUPPORT);
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_RcvLmmRelInd
Description    : LMM_LCS_REL_IND��Ϣ������
Input          : VOS_VOID *pstRelInd
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-10-09  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_RcvLmmRelInd
(
    const LMM_LCS_REL_IND_STRU         *pstRelInd
)
{
    VOS_UINT32                          i               = 0;
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity    = NAS_LCS_NULL_PTR;
    TAF_LCS_CAUSE_ENUM_UINT32           enTafLcsCause;

    enTafLcsCause = NAS_LCS_LmmRelCauseMap(pstRelInd->enRelCause);

    for (i = NAS_LCS_MO_LR_LPP_INDEX; i <= NAS_LCS_MT_LR_ENTITY_INDEX_END; i++)
    {
        pstLcsEntity = NAS_LCS_GetLcsEntity(i);

        if (NAS_LCS_ENTITY_USED != pstLcsEntity->enUsedFlag)
        {
            continue ;
        }

        /* �����MO-LR */
        if (PS_TRUE == NAS_LCS_IsMoLr(i))
        {
            /* ��ǰ����״̬ΪESTINGʱ������, ��ֹ����MO LR�����������ͷŶԳ峡�� */
            if (NAS_LCS_CONN_STATE_ESTING == NAS_LCS_GetEntityConnState(i))
            {
                continue;
            }

            NAS_LCS_SetEntityConnState(i, NAS_LCS_CONN_STATE_IDLE);

            /* ����ؽ�����ʱ�������У��򲻴��� */
            if (NAS_LCS_TIMER_RUNNING == NAS_LCS_IsTimerRunning(i, TI_NAS_LCS_WATI_REEST_TIMER))
            {
                continue ;
            }

            /* �����������MO-LR���������ڼ��״̬���򲻴��� */
            if ((NAS_LCS_MO_LR_TAF_INDEX == i) && (LCS_REP_MODE_PERIODIC_RPT == NAS_LCS_GetMolrMode())
                && (NAS_LCS_ENTITY_STATE_PERIOD_INTERVAL == NAS_LCS_GetEntityState(i)))
            {
                continue ;
            }

            /* ����EPC MOLR������·�쳣 */
            NAS_LCS_ProcMolrConnAbnormal(i, enTafLcsCause);

            continue ;
        }

        /* �ͷŵ���LCSʵ�岢֪ͨ������ */
        NAS_LCS_ClearLcsEntityAndNotify(i, TAF_LCS_CAUSE_CONN_REL);
    }

    if (NAS_LCS_GetLcsEntityNum() > 0)
    {
        NAS_LCS_SndOmEntityInfo();
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_EmmMsgDistr
Description    : LCSģ��EMM��Ϣ������
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-9-28  �¿���
*****************************************************************************/
VOS_VOID NAS_LCS_EmmMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pEmmMsg  = VOS_NULL_PTR;

    pEmmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    NAS_LCS_INFO_LOG("NAS_LCS_EmmMsgDistr is entered!");
    TLPS_PRINT2LAYER_INFO1(NAS_LCS_EmmMsgDistr_ENUM, LNAS_ENTRY, pEmmMsg->ulMsgName);

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch(pEmmMsg->ulMsgName)
    {
        case ID_LMM_LCS_EST_CNF:
            NAS_LCS_RcvLmmEstCnf((LMM_LCS_EST_CNF_STRU *)pRcvMsg);
            break;

        case ID_LMM_LCS_DATA_CNF:
            NAS_LCS_RcvLmmDataCnf((LMM_LCS_DATA_CNF_STRU *)pRcvMsg);
            break;

        case ID_LMM_LCS_DATA_IND:
            NAS_LCS_RcvLmmDataInd((LMM_LCS_DATA_IND_STRU *)pRcvMsg);
            break;

        case ID_LMM_LCS_POS_CAP_INFO_IND:
            NAS_LCS_RcvLmmPosCapInfoInd((LMM_LCS_POS_CAP_INFO_IND_STRU *)pRcvMsg);
            break;

        case ID_LMM_LCS_REL_IND:
            NAS_LCS_RcvLmmRelInd((LMM_LCS_REL_IND_STRU *)pRcvMsg);
            break;

        default:
            NAS_LCS_INFO_LOG("NAS_LCS_EmmMsgDistr:NORM: Error MsgId!");
            TLPS_PRINT2LAYER_ERROR(NAS_LCS_EmmMsgDistr_ENUM, LNAS_LCS_InvalidRsvMsgId);
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
/* end of NasLcsEmmMsgProc.c */
