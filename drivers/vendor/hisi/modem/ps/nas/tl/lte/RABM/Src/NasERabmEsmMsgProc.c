/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasERabmEsmMsgProc.c
  Description     : ��C�ļ�������SM_MSGģ���ʵ��
  History         :
     1.yangqianhui 00135146      2008-9-11  Draft Enact

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasERabmEsmMsgProc.h"
#include  "NasERabmAppMsgProc.h"
#include  "NasERabmRrcMsgProc.h"
#include  "NasERabmIpFilter.h"
#include  "NasERabmCdsMsgProc.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASRABMESMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASRABMESMMSGPROC_C
/*lint +e767*/

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


/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name   : NAS_ERABM_EsmMsgDistr()
 Description     : RABMģ��SM��Ϣ�ַ�����
 Input           : VOS_VOID *pRcvMsg-----------��Ϣָ��
 Output          : VOS_VOID
 Return          : VOS_VOID
 History         :
      1.yangqianhui 00135146      2008-9-11  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_ERABM_EsmMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU                 *pSmMsg;

    pSmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_EsmMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_EsmMsgDistr_ENUM, LNAS_ENTRY);

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch (pSmMsg->ulMsgName)
    {
        /*����յ�����ESM_ERABM_ACT_IND��Ϣ������NAS_ERABM_RcvRabmEsmActInd����*/
        case ID_ESM_ERABM_ACT_IND:
            NAS_ERABM_RcvRabmEsmActInd((ESM_ERABM_ACT_IND_STRU *) pRcvMsg);
            break;

        /*����յ�����ESM_ERABM_MDF_IND��Ϣ������NAS_ERABM_RcvRabmEsmMdfInd����*/
        case ID_ESM_ERABM_MDF_IND:
            NAS_ERABM_RcvRabmEsmMdfInd((ESM_ERABM_MDF_IND_STRU *) pRcvMsg);
            break;

        /*����յ�����ESM_ERABM_DEACT_IND��Ϣ������NAS_ERABM_RcvRabmEsmDeactInd����*/
        case ID_ESM_ERABM_DEACT_IND:
            NAS_ERABM_RcvRabmEsmDeactInd((ESM_ERABM_DEACT_IND_STRU *) pRcvMsg);
            break;

        /*����յ�����ESM_ERABM_REL_IND��Ϣ������NAS_ERABM_RcvRabmEsmRelInd����*/
        case ID_ESM_ERABM_REL_IND:
            NAS_ERABM_RcvRabmEsmRelInd();
            break;

        #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

        /*����յ�����ID_ESM_ERABM_CLEAR_CL_BEARER_NOTIFY��Ϣ������NAS_ERABM_RcvRabmEsmClearClBearerNotify����*/
        case ID_ESM_ERABM_CLEAR_CL_BEARER_NOTIFY:
            NAS_ERABM_RcvRabmEsmClearClBearerNotify();
            break;
        #endif

        default:
            NAS_ERABM_WARN_LOG("NAS_ERABM_EsmMsgDistr:WARNING:SM->RABM Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ERABM_EsmMsgDistr_ENUM, LNAS_MSG_INVALID);
            break;
    }

    /*�������ؼ�������ֻ��һ�����ؼ���жϸó������û������TFT,��¼�ó��غ�*/
    NAS_ERABM_SrchOnlyActiveAndNoUlTftEpsb();

    return;
}

/*****************************************************************************
 Function Name   : NAS_ERABM_SrchOnlyActiveAndNoUlTftEpsb
 Description     : �������ؼ��������Ƿ�ֻ��һ���������
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2010-7-12  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ERABM_SrchOnlyActiveAndNoUlTftEpsb( VOS_VOID )
{

    VOS_UINT32                          ulEpsbId = NAS_ERABM_NULL;
    VOS_UINT32                          ulTempActEpsbId = NAS_ERABM_NULL;
    VOS_UINT32                          ulActEpsbNum = NAS_ERABM_NULL;

    /*�������ؼ������¼������صĸ��������һ��������غ�*/
    for (ulEpsbId = NAS_ERABM_MIN_EPSB_ID; ulEpsbId <= NAS_ERABM_MAX_EPSB_ID; ulEpsbId++)
    {
        if (NAS_ERABM_EPSB_ACTIVE == NAS_ERABM_GetEpsbStateInfo(ulEpsbId))
        {
            ulTempActEpsbId = ulEpsbId;
            ulActEpsbNum++;
        }
    }

    /*���������������� 1���򲻼�¼�κγ��أ�����*/
    if(NAS_ERABM_ACT_EPSB_NUM_ONE != ulActEpsbNum)
    {
        NAS_ERABM_SetOnlyActiveAndNoUlTftEpsbId(NAS_ERABM_ILL_EPSB_ID);
        NAS_ERABM_INFO_LOG("NAS_ERABM_SrchOnlyActiveAndNoUlTftEpsb:the active EpsbNum is not one!");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_SrchOnlyActiveAndNoUlTftEpsb_ENUM, LNAS_ERABM_ActiveEpsbNumIsNotOne);
        return;
    }

    /*���ֻ��һ��������أ��жϸó����������������TFT����¼���غ�*/
    if(PS_FALSE == NAS_ERABM_IsExistUplinkPfinTft(ulTempActEpsbId))
    {
        NAS_ERABM_SetOnlyActiveAndNoUlTftEpsbId(ulTempActEpsbId);
    }
    else
    {
        NAS_ERABM_SetOnlyActiveAndNoUlTftEpsbId(NAS_ERABM_ILL_EPSB_ID);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_ERABM_SaveUeIpAddr
 Description     : ����ue��IP��ַ
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.yangqianhui 00135146      2009-7-8  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_SaveUeIpAddr(const ESM_ERABM_ACT_IND_STRU *pRcvMsg, VOS_UINT32 ulEpsbId)
{
    VOS_UINT8                           ucIpType   = ESM_ERABM_PDN_TYPE_IPV4;
    APP_ESM_IP_ADDR_STRU               *pstPdnAddr = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_SaveUeIpAddr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_SaveUeIpAddr_ENUM, LNAS_ENTRY);

    ucIpType = pRcvMsg->stPdnAddr.ucIpType;

    pstPdnAddr = NAS_ERABM_GetEpsbPdnAddr(ulEpsbId);

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* �����EHRPD���͵ĳ��أ���Ҫ������EHRPDʵ���� */
    if (ESM_ERABM_BEARER_RAT_EHRPD == pRcvMsg->enBearerCntxtRat)
    {
        NAS_ERABM_INFO_LOG("NAS_ERABM_SaveUeIpAddr: EHRPD bearer.");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_SaveUeIpAddr_ENUM, LNAS_FUNCTION_LABEL1);
        pstPdnAddr = NAS_ERABM_GetEhrpdPdnAddr(ulEpsbId);
    }
    #endif

    switch(ucIpType)
    {
        /*����IPv4��ַ*/
        case ESM_ERABM_PDN_TYPE_IPV4:
            pstPdnAddr->ucIpType = ESM_ERABM_PDN_TYPE_IPV4;
            NAS_ERABM_MEM_CPY_S(pstPdnAddr->aucIpV4Addr,
                                APP_MAX_IPV4_ADDR_LEN,
                                pRcvMsg->stPdnAddr.aucIpV4Addr,
                                APP_MAX_IPV4_ADDR_LEN);
            break;

        /*����IPv6��ַ*/
        case ESM_ERABM_PDN_TYPE_IPV6:
            pstPdnAddr->ucIpType = ESM_ERABM_PDN_TYPE_IPV6;
            NAS_ERABM_MEM_CPY_S(pstPdnAddr->aucIpV6Addr,
                                APP_MAX_IPV6_ADDR_LEN,
                                pRcvMsg->stPdnAddr.aucIpV6Addr,
                                APP_MAX_IPV6_ADDR_LEN);
            break;

        /*���δ��IPV4��IPV6��ַ*/
        case ESM_ERABM_PDN_TYPE_IPV4_IPV6:
            pstPdnAddr->ucIpType = ESM_ERABM_PDN_TYPE_IPV4_IPV6;
            NAS_ERABM_MEM_CPY_S(pstPdnAddr->aucIpV4Addr,
                                APP_MAX_IPV4_ADDR_LEN,
                                pRcvMsg->stPdnAddr.aucIpV4Addr,
                                APP_MAX_IPV4_ADDR_LEN);
            NAS_ERABM_MEM_CPY_S(pstPdnAddr->aucIpV6Addr,
                                APP_MAX_IPV6_ADDR_LEN,
                                pRcvMsg->stPdnAddr.aucIpV6Addr,
                                APP_MAX_IPV6_ADDR_LEN);
            break;

        default:
            NAS_ERABM_WARN_LOG("NAS_ERABM_SaveUeIpAddr:WARNING:ESM->RABM Invalid IP Type!");
            TLPS_PRINT2LAYER_WARNING(NAS_ERABM_SaveUeIpAddr_ENUM, LNAS_ERABM_InvalidIPType);
            NAS_ERABM_MEM_SET_S((VOS_VOID*)pstPdnAddr,
                                sizeof(APP_ESM_IP_ADDR_STRU),
                                0,
                                sizeof(APP_ESM_IP_ADDR_STRU));
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ERABM_SaveEpsbActInfo()
 Description     : �յ����ؼ�����Ϣʱ����¼�µĳ��ؼ�����Ϣ
 Input           : ESM_ERABM_ACT_IND_STRU *pRcvMsg
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.yangqianhui 00135146      2008-9-11  Draft Enact
    2.lihong 00150010           2009-5-27  Modify

*****************************************************************************/
VOS_VOID NAS_ERABM_SaveEpsbActInfo(const ESM_ERABM_ACT_IND_STRU *pRcvMsg, VOS_UINT32 ulEpsbId )
{
    VOS_UINT32                          ulEpsTftPfNum           = pRcvMsg->ulTftPfNum;
    VOS_UINT32                          ulTftPfCnt              = NAS_ERABM_NULL;
    ESM_ERABM_TFT_PF_STRU               *pstTftPf                = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_SaveEpsbActInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_SaveEpsbActInfo_ENUM, LNAS_ENTRY);

    if(ulEpsTftPfNum > ESM_ERABM_MAX_PF_NUM_IN_BEARER)
    {
        ulEpsTftPfNum = ESM_ERABM_MAX_PF_NUM_IN_BEARER;
    }

    /*����IP��ַ*/
    NAS_ERABM_SaveUeIpAddr(pRcvMsg, ulEpsbId);

    /* ��¼����������������PF��Ϣ */
    for(ulTftPfCnt = 0; ulTftPfCnt < ulEpsTftPfNum; ulTftPfCnt++)
    {
        pstTftPf = NAS_ERABM_GetEpsbTftAddr(ulEpsbId, ulTftPfCnt);

        /* ������PF��Ϣ */
        NAS_ERABM_MEM_CPY_S(pstTftPf, sizeof(ESM_ERABM_TFT_PF_STRU), &pRcvMsg->astTftPf[ulTftPfCnt], sizeof(ESM_ERABM_TFT_PF_STRU));

        /* Ϊ�˷�ֹNDIS�������ݰ����͵��տڣ�NDIS�������ݰ��Ĺ����������ȼ�
           Ҫ���ڿտ���Ϣ�е�TFT�����ȼ���Ŀǰ���ȼ�0-5Ԥ����NDIS�������ݰ���
           ���������ȼ� */
        pstTftPf->ucPrecedence += NAS_ERABM_IPF_UL_NDIS_PRIORITY_NUM;
    }

    /* ���ó��ذ�����PF���� */
    NAS_ERABM_SetEpsbTftPfNum(ulEpsbId, ulEpsTftPfNum);

    /*��¼���������ļ���״̬*/
    NAS_ERABM_SetEpsbStateInfo(ulEpsbId, NAS_ERABM_EPSB_ACTIVE);

    NAS_ERABM_SetEpsbBearerType(ulEpsbId, (pRcvMsg->enBearerCntxtType));
    NAS_ERABM_SetEpsbLinkedEpsbId(ulEpsbId, (pRcvMsg->ulLinkedEpsbId));
    NAS_ERABM_SetEpsbQCI(ulEpsbId, (pRcvMsg->ucQCI));

    /* �����һ�����ؼ����Ҳ��ǻ���ģʽʱ������enUlNdisFilterValidFlagΪ��Ч */
    if ((1 == NAS_ERABM_GetActiveEpsBearerNum())
        && (NAS_ERABM_MODE_TYPE_NORMAL == NAS_ERABM_GetMode()))
    {
        NAS_ERABM_SetUlNdisFilterValidFlag(NAS_ERABM_UL_NDIS_FILTER_VALID);
    }
}


/*****************************************************************************
 Function Name   : NAS_ERABM_ClearEpsbResource
 Description     : ���EPS���ص������Ϣ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.yangqianhui 00135146      2008-9-23  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_ClearEpsbResource( VOS_UINT32 ulEpsbId )
{
    VOS_UINT32                          ulEpsTftPfNum   = NAS_ERABM_NULL;
    VOS_UINT32                          ulTftPfCnt      = NAS_ERABM_NULL;
    ESM_ERABM_TFT_PF_STRU               *pstTftPf        = VOS_NULL_PTR;
    APP_ESM_IP_ADDR_STRU               *pstPdnAddr      = VOS_NULL_PTR;

    NAS_ERABM_SetEpsbStateInfo(ulEpsbId, NAS_ERABM_EPSB_INACTIVE);

    pstPdnAddr = NAS_ERABM_GetEpsbPdnAddr(ulEpsbId);

    ulEpsTftPfNum = NAS_ERABM_GetEpsbTftPfNum(ulEpsbId);

    /* ��ճ��ذ���������PF��Ϣ��PF��־ */
    for(ulTftPfCnt = 0; ulTftPfCnt < ulEpsTftPfNum; ulTftPfCnt++)
    {
         pstTftPf = NAS_ERABM_GetEpsbTftAddr(ulEpsbId, ulTftPfCnt);

        /* ���PF��Ϣ */
        NAS_ERABM_MEM_SET_S(pstTftPf,sizeof(ESM_ERABM_TFT_PF_STRU), NAS_ERABM_NULL, sizeof(ESM_ERABM_TFT_PF_STRU));
    }

    NAS_ERABM_SetEpsbTftPfNum(ulEpsbId, NAS_ERABM_NULL);

    NAS_ERABM_MEM_SET_S(pstPdnAddr,sizeof(APP_ESM_IP_ADDR_STRU), NAS_ERABM_NULL, sizeof(APP_ESM_IP_ADDR_STRU));
}


/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRabmEsmActInd()
 Description     : RABMģ��ESM_ERABM_ACT_IND_STRU��Ϣ�ַ�����
 Input           : ESM_ERABM_ACT_IND_STRU *pRcvMsg-----------��Ϣָ��
 Output          : VOS_VOID
 Return          : VOS_VOID

 History         :
     1.yangqianhui 00135146      2008-9-11  Draft Enact
     2.lihong 00150010           2009-12-24  Modify
     3.sunjitan 00193151         2016-01-14  Mofify for CL��ģ������
*****************************************************************************/
VOS_VOID  NAS_ERABM_RcvRabmEsmActInd(const ESM_ERABM_ACT_IND_STRU *pRcvMsg )
{
    VOS_UINT32               ulEpsbId          = 0;                         /*������¼EPS���ؼ�����е�EPSID*/

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEsmActInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEsmActInd_ENUM, LNAS_ENTRY);

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* �����EHRPD��ģ�µĳ��ؼ��ERABM��¼EHRPD���������Ϣ */
    if(ESM_ERABM_BEARER_RAT_EHRPD == pRcvMsg->enBearerCntxtRat)
    {
        NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEsmActInd: EHRPD bearer.");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEsmActInd_ENUM, LNAS_FUNCTION_LABEL1);
        NAS_ERABM_SaveEhrpdbActInfo(pRcvMsg);
        return;
    }
    #endif

    /*�ҵ���Ӧ��EPS����*/
    ulEpsbId = pRcvMsg->ulEpsId;

    (VOS_VOID)VOS_TaskLock();

    /*�����Ӧ��EPS���ص������Ϣ*/
    NAS_ERABM_ClearEpsbResource(ulEpsbId);

    /*��¼��Ӧ�Ĳ���*/
    NAS_ERABM_SaveEpsbActInfo(pRcvMsg, ulEpsbId);

    (VOS_VOID)VOS_TaskUnlock();

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* �����EHRPD���ػָ��ɹ���ERABM������IPF֮ǰҪɾ�����ؼ�¼��EHRPD������Ϣ */
    if(VOS_TRUE == pRcvMsg->ucHandoverFlag)
    {
        NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEsmActInd: EHRPD bearer handover succ.");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEsmActInd_ENUM, LNAS_FUNCTION_LABEL2);

        TLPS_PRINT2LAYER_INFO2(NAS_ERABM_RcvRabmEsmActInd_ENUM, LNAS_ERABM_EhrpdBearerIdAndStorePktNum,  \
                               pRcvMsg->ulEhrpdBearerId, NAS_ERABM_GetEhrpdBearerStorePktNum(pRcvMsg->ulEhrpdBearerId));

        /* ����ID�п��ܱ仯������������ԭ����¼ʱ���EHRPD����ID */
        NAS_ERABM_InitEhrpdIdInfo(pRcvMsg->ulEhrpdBearerId);
    }
    #endif

    /* ��CDS����CDS_ERABM_RAB_CREATE_IND */
    NAS_ERABM_SndErabmCdsRabCreatInd(ulEpsbId);

    /*�ж��Ƿ��ڵȴ����ؼ���*/
    if (NAS_ERABM_WAIT_EPSB_ACT_MSG == NAS_ERABM_GetWaitEpsbActSign())
    {
        /* �ж��Ƿ����DRB�ѽ�������������EPS������δ��������*/
        if (NAS_ERABM_FAILURE == NAS_ERABM_HasDrbWithoutRelatingEpsBear())
        {
            /*ֹͣ�����ȴ���ʱ��*/
            NAS_ERABM_TimerStop(NAS_ERABM_WAIT_EPSB_ACT_TIMER);

            /* ��ESM������״̬��Ϣ */
            NAS_ERABM_InformEsmBearerStatus(pRcvMsg->ucSessionId);

            /*����ȴ���ʶ*/
            NAS_ERABM_SetWaitEpsBActSign(NAS_ERABM_NOT_WAIT_EPSB_ACT_MSG);
        }
    }

    /* ����̬�²���Ҫ����IPF */
    if (NAS_ERABM_L_MODE_STATUS_NORMAL != NAS_ERABM_GetLModeStatus())
    {
        return ;
    }
    /*����TFT�ͳ�����Ϣ����IP Filter��Ӳ��������*/
    if(PS_FAIL == NAS_ERABM_IpfConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: IPF Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEsmActInd_ENUM, LNAS_ERABM_IPFUpdateIPFilterFailed);
    }

    /*����TFT�ͳ�����Ϣ����IP Filter��CDS*/
    if(PS_FAIL == NAS_ERABM_CdsConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: CDS Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEsmActInd_ENUM, LNAS_ERABM_CDSUpdateIPFilterFailed);
    }

}

/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRabmEsmMdfInd()
 Description     : RABMģ��ESM_ERABM_MDF_IND_STRU��Ϣ�ַ�����
 Input           : ESM_ERABM_MDF_IND_STRU *pRcvMsg-----------��Ϣָ��
 Output          : VOS_VOID
 Return          : VOS_VOID

 History         :
    1.RabmStru      2008-9-5  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_RcvRabmEsmMdfInd(const ESM_ERABM_MDF_IND_STRU *pRcvMsg )
{
    VOS_UINT32                         ulEpsbId = 0;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEsmMdfInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEsmMdfInd_ENUM, LNAS_ENTRY);

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* �����EHRPD��ģ�µĳ����޸ģ�ERABM����ʽ��¼EHRPD���������Ϣ */
    if(ESM_ERABM_BEARER_RAT_EHRPD == pRcvMsg->enBearerCntxtRat)
    {
        NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEsmMdfInd: EHRPD bearer.");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEsmMdfInd_ENUM, LNAS_FUNCTION_LABEL1);

        /* �˴������������޸�EHRPD����ʱLһ�����ڴ�ģ���������ģ�޸ĵ�һ����LTE���ͳ��� */
        NAS_ERABM_InitEhrpdIdInfo(pRcvMsg->ulEhrpdBearerId);

        /* ���������Ϣ */
        NAS_ERABM_SaveEhrpdbActInfo(pRcvMsg);
        return;
    }
    #endif

    /*�ҵ�Ҫ�޸ĵ�EPS����*/
    ulEpsbId = pRcvMsg->ulEpsId;
    /* ��ֹ�ڱ��������Ӧ���������У��ϲ�����CDS�������񣬵��ýӿڻ�ȡ���غ����ڳ�����Ϣ��û�б����굼�»�ȡ���غ�ʧ�ܣ������ڴ˴�������  */
    (VOS_VOID)VOS_TaskLock();

    /*�����Ӧ��EPS���ص������Ϣ*/
    NAS_ERABM_ClearEpsbResource(ulEpsbId);

    /*��¼��Ӧ�Ĳ���*/
    NAS_ERABM_SaveEpsbActInfo(pRcvMsg, ulEpsbId);

    (VOS_VOID)VOS_TaskUnlock();

    /* ��CDS����CDS_ERABM_RAB_CREATE_IND_STRU */
    NAS_ERABM_SndErabmCdsRabCreatInd(ulEpsbId);

    /* ����̬�²���Ҫ����IPF */
    if (NAS_ERABM_L_MODE_STATUS_NORMAL != NAS_ERABM_GetLModeStatus())
    {
        return ;
    }

    /*����TFT�ͳ�����Ϣ����IP Filter��Ӳ��������*/
    if(PS_FAIL == NAS_ERABM_IpfConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: IPF Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEsmMdfInd_ENUM, LNAS_ERABM_IPFUpdateIPFilterFailed);
    }

    /*����TFT�ͳ�����Ϣ����IP Filter��CDS*/
    if(PS_FAIL == NAS_ERABM_CdsConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: CDS Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEsmMdfInd_ENUM, LNAS_ERABM_CDSUpdateIPFilterFailed);
    }
}


/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRabmEsmDeactInd()
 Description     : RABMģ��ESM_ERABM_DEACT_IND_STRU��Ϣ�ַ�����
 Input           : ESM_ERABM_DEACT_IND_STRU *pRcvMsg-----------��Ϣָ��
 Output          : VOS_VOID
 Return          : VOS_VOID

 History         :
    1.yangqianhui      2008-9-5  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_RcvRabmEsmDeactInd(const ESM_ERABM_DEACT_IND_STRU *pRcvMsg )
{
    VOS_UINT32          ulEpsbId   = 0;
    VOS_UINT32          ulEpsIdCnt = 0;
    VOS_UINT32          ulLoop     = 0;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEsmDeactInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEsmDeactInd_ENUM, LNAS_ENTRY);

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* �����EHRPD��ģ�µĳ���ȥ���ERABMֻɾ��EHRPD���������Ϣ��CDS��IPF�ȶ�����ģȥ���� */
    if(ESM_ERABM_BEARER_RAT_EHRPD == pRcvMsg->enBearerCntxtRat)
    {
        NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEsmDeactInd: EHRPD bearer.");
        TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEsmDeactInd_ENUM, LNAS_FUNCTION_LABEL1);

        /*��ȡȥ����ĳ�����*/
        ulEpsIdCnt = pRcvMsg->ulEpsIdNum;

        /*�ҵ�Ҫȥ�����EPS����*/
        for (ulLoop = 0; ulLoop < ulEpsIdCnt; ulLoop++)
        {
            ulEpsbId = pRcvMsg->aulEpsId[ulLoop];

            /* ��ʼ����Ӧ��EHRPD������Ϣ */
            NAS_ERABM_InitEhrpdIdInfo(ulEpsbId);
        }

        return;
    }
    #endif

    /*��ȡȥ����ĳ�����*/
    ulEpsIdCnt = pRcvMsg->ulEpsIdNum;

    /*�ҵ�Ҫȥ�����EPS����*/
    for (ulLoop = 0; ulLoop < ulEpsIdCnt; ulLoop++)
    {
        ulEpsbId = pRcvMsg->aulEpsId[ulLoop];

        /* ��CDS����CDS_ERABM_RAB_RELEASE_IND_STRU */
        NAS_ERABM_SndErabmCdsRabReleaseInd(ulEpsbId);

        /*RABM�ͷ�������ص���Դ*/
        NAS_ERABM_ClearEpsbResource(ulEpsbId);
        NAS_ERABM_SetRbStateInfo(ulEpsbId, NAS_ERABM_RB_DISCONNECTED);
        NAS_ERABM_SetEpsbRbIdInfo(ulEpsbId, NAS_ERABM_ILL_RB_ID);
    }

    /* ������ر��ͷţ�����enUlNdisFilterValidFlagΪ��Ч */
    if (0 == NAS_ERABM_GetActiveEpsBearerNum())
    {
        NAS_ERABM_SetUlNdisFilterValidFlag(NAS_ERABM_UL_NDIS_FILTER_INVALID);

        /* ֪ͨCDS�ͷŻ�������ݰ� */
        NAS_ERABM_SndErabmCdsFreeBuffDataInd();
    }

    /* ����̬�²���Ҫ����IPF */
    if (NAS_ERABM_L_MODE_STATUS_NORMAL != NAS_ERABM_GetLModeStatus())
    {
        return ;
    }

    /*����TFT�ͳ�����Ϣ����IP Filter��Ӳ��������*/
    if(PS_FAIL == NAS_ERABM_IpfConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: IPF Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEsmDeactInd_ENUM, LNAS_ERABM_IPFUpdateIPFilterFailed);
    }

    /*����TFT�ͳ�����Ϣ����IP Filter��CDS*/
    if(PS_FAIL == NAS_ERABM_CdsConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: CDS Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEsmDeactInd_ENUM, LNAS_ERABM_CDSUpdateIPFilterFailed);
    }
}

/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRabmEsmRelInd()
 Description     : RABMģ��ESM_ERABM_REL_IND_STRU��Ϣ�ַ�����
 Input           : VOS_VOID
 Output          : VOS_VOID
 Return          : VOS_VOID

 History         :
    1.RabmStru      2008-9-5  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_RcvRabmEsmRelInd( VOS_VOID )
{
    VOS_UINT32 ulLoop = NAS_ERABM_NULL;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEsmRelInd is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEsmRelInd_ENUM, LNAS_ENTRY);

    /* ֪ͨCDS RAB RELEASE */
    for (ulLoop = NAS_ERABM_MIN_EPSB_ID; ulLoop <= NAS_ERABM_MAX_EPSB_ID; ulLoop++)
    {
        if (NAS_ERABM_EPSB_ACTIVE == NAS_ERABM_GetEpsbStateInfo(ulLoop))
        {
            /* ��CDS����CDS_ERABM_RAB_RELEASE_IND */
            NAS_ERABM_SndErabmCdsRabReleaseInd(ulLoop);
        }
    }
    /*�ͷ�������Դ���ص�������ʼ�����״̬*/
    NAS_ERABM_ClearRabmResource();

    if(NAS_ERABM_L_MODE_STATUS_NORMAL != NAS_ERABM_GetLModeStatus())
    {
        return;
    }

    /*����TFT�ͳ�����Ϣ����IP Filter��Ӳ��������*/
    if(PS_FAIL == NAS_ERABM_IpfConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: IPF Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEsmRelInd_ENUM, LNAS_ERABM_IPFUpdateIPFilterFailed);
    }

    /*����TFT�ͳ�����Ϣ����IP Filter��CDS*/
    if(PS_FAIL == NAS_ERABM_CdsConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_EsmMsgDistr: CDS Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEsmRelInd_ENUM, LNAS_ERABM_CDSUpdateIPFilterFailed);
    }
    return;
}

/*****************************************************************************
 Function Name   : NAS_ERABM_SndRabmEsmRelReq()
 Description     : �����ͷ���ESM_ERABM_REL_REQ��Ϣ
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID
 History         :
     1.yangqianhui 00135146      2008-9-11  Draft Enact

*****************************************************************************/

VOS_VOID NAS_ERABM_SndRabmEsmRelReq( VOS_VOID )
{
    ESM_ERABM_REL_REQ_STRU    *pstRelReq = VOS_NULL_PTR;

    /*����ռ�ͼ���Ƿ����ɹ�*/
    pstRelReq = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(ESM_ERABM_REL_REQ_STRU));
    if (VOS_NULL_PTR == pstRelReq)
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmEsmRelReq:ERROR:Alloc msg fail!" );
        return;
    }

    /*���*/
    NAS_ERABM_MEM_SET_S(NAS_ERABM_GET_MSG_ENTITY(pstRelReq),
                        NAS_ERABM_GET_MSG_LENGTH(pstRelReq),
                        NAS_ERABM_NULL,
                        NAS_ERABM_GET_MSG_LENGTH(pstRelReq));

    /*��д��Ϣͷ*/
    NAS_ERABM_WRITE_ESM_MSG_HEAD(pstRelReq,ID_ESM_ERABM_REL_REQ);

    /* ������Ϣ���ͺ���*/
    NAS_ERABM_SND_MSG(pstRelReq);

}

/*****************************************************************************
 Function Name   : NAS_ERABM_SndRabmEsmBearerStatusReq
 Description     : ��ESM���ͽ���rb��EpsbId��Ϣ
 Input           : VOS_UINT32 *pulEpsbId
                   VOS_UINT32 ulEpsbIdNum
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2009-3-28  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ERABM_SndRabmEsmBearerStatusReq(const VOS_UINT32 *pulEpsbId,
                                                              VOS_UINT32 ulEpsbIdNum,
                                                              VOS_UINT8 ucSessionId)
{
    ESM_ERABM_BEARER_STATUS_REQ_STRU    *pstBearerStatusReq  = VOS_NULL_PTR;

    /*��ڲ������*/
    if ((VOS_NULL_PTR == pulEpsbId) || (ulEpsbIdNum > NAS_ERABM_MAX_EPSB_NUM))
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmEsmBearerStatusReq:ERROR:Input para error!");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_SndRabmEsmBearerStatusReq_ENUM, LNAS_PARAM_INVALID);
        return;
    }

    /*����ռ�ͼ���Ƿ����ɹ�*/
    pstBearerStatusReq = (VOS_VOID*)NAS_ERABM_ALLOC_MSG(sizeof(ESM_ERABM_BEARER_STATUS_REQ_STRU));
    if ( VOS_NULL_PTR == pstBearerStatusReq )
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_SndRabmEsmBearerStatusReq:ERROR:Alloc msg fail!" );
        return;
    }

    NAS_ERABM_MEM_SET_S(NAS_ERABM_GET_MSG_ENTITY(pstBearerStatusReq),
                        NAS_ERABM_GET_MSG_LENGTH(pstBearerStatusReq),
                        NAS_ERABM_NULL,
                        NAS_ERABM_GET_MSG_LENGTH(pstBearerStatusReq));

    /*��д��Ϣͷ*/
    NAS_ERABM_WRITE_ESM_MSG_HEAD(pstBearerStatusReq, ID_ESM_ERABM_BEARER_STATUS_REQ);

    /*��д��Ϣʵ��*/
    pstBearerStatusReq->ucSessionId = ucSessionId;
    pstBearerStatusReq->ulEpsIdNum = ulEpsbIdNum;
    NAS_ERABM_MEM_CPY_S(    (VOS_UINT8*)pstBearerStatusReq->aulEpsId,
                            sizeof(VOS_UINT32) * ESM_ERABM_MAX_EPSB_NUM,
                            (VOS_UINT8*)pulEpsbId,
                            (pstBearerStatusReq->ulEpsIdNum)*(sizeof(VOS_UINT32)/sizeof(VOS_UINT8)));

    /*������Ϣ���ͺ���*/
    NAS_ERABM_SND_MSG(pstBearerStatusReq);

}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 Function Name   : NAS_ERABM_SaveEhrpdbActInfo
 Description     : �յ�EHRPD���ؼ�����Ϣʱ����¼�µĳ��ؼ�����Ϣ
 Input           : *pRcvMsg              ���ؼ�����Ϣ
                   ulEhrpbBearerId
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.sunjitan 00193151      2016-01-14  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ERABM_SaveEhrpdbActInfo(
    const ESM_ERABM_ACT_IND_STRU       *pRcvMsg
)
{
    NAS_ERABM_INFO_STRU                *pstEhrpdBearerInfo = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_SaveEhrpdbActInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_InitEhrpdIdInfo_ENUM, LNAS_ENTRY);

    /* ��ֹ����Խ�磬����ID�Ƿ�ʱ�������� */
    if ((NAS_ERABM_MAX_EPSB_ID < pRcvMsg->ulEhrpdBearerId)
      ||(NAS_ERABM_MIN_EPSB_ID > pRcvMsg->ulEhrpdBearerId))
    {
        return;
    }

    /* ����EHRPD������Ϣ����ǰ�׶�ֻ֧��ȱʡ���ػ����� */
    pstEhrpdBearerInfo = NAS_ERABM_GetEhrpdBearerIdInfoAddr(pRcvMsg->ulEhrpdBearerId);

    /* ��¼����������Ϊ����̬ */
    pstEhrpdBearerInfo->enContextState    = NAS_ERABM_EPSB_ACTIVE;

    /* EHRPD��ģʱ����Ӧ�ĳ�����L�¾�Ϊ����̬ */
    pstEhrpdBearerInfo->enRbState         = NAS_ERABM_RB_SUSPENDED;

    /* ֻ֧��ȱʡ���ػ����� */
    pstEhrpdBearerInfo->enBearerCntxtType = ESM_ERABM_BEARER_TYPE_DEFAULT;

    /* ����QCI */
    pstEhrpdBearerInfo->ucQCI             = pRcvMsg->ucQCI;

    /*����IP��ַ*/
    NAS_ERABM_SaveUeIpAddr(pRcvMsg, pRcvMsg->ulEhrpdBearerId);

    return;

}

/*****************************************************************************
 Function Name   : NAS_ERABM_RcvRabmEsmClearClBearerNotify
 Description     : RABMģ��ID_ESM_ERABM_CLEAR_CL_BEARER_NOTIFY��Ϣ�ַ�����,
                   �յ�����Ϣʱ��ERABM�������LTE�º�EHRPD���ؼ�¼
 Input           : VOS_VOID
 Output          : VOS_VOID
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151      2016-01-14  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ERABM_RcvRabmEsmClearClBearerNotify(VOS_VOID)
{
    VOS_UINT32                          ulLoop;

    /*��ӡ����ú���*/
    NAS_ERABM_INFO_LOG("NAS_ERABM_RcvRabmEsmClearClBearerNotify is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ERABM_RcvRabmEsmClearClBearerNotify_ENUM, LNAS_ENTRY);

    /* ֪ͨCDS RAB RELEASE */
    for (ulLoop = NAS_ERABM_MIN_EPSB_ID; ulLoop <= NAS_ERABM_MAX_EPSB_ID; ulLoop++)
    {
        if (NAS_ERABM_EPSB_ACTIVE == NAS_ERABM_GetEpsbStateInfo(ulLoop))
        {
            /* ��CDS����CDS_ERABM_RAB_RELEASE_IND */
            NAS_ERABM_SndErabmCdsRabReleaseInd(ulLoop);
        }
    }

    /*�ͷ�����LTE����Դ���ص�������ʼ�����״̬*/
    NAS_ERABM_ClearRabmResource();

    /* �������EHRPD���أ���������֪ͨCDS������� */
    if (0 != NAS_ERABM_GetActiveEhrpdBearerNum())
    {
        /* ֪ͨCDS�ͷŻ�������ݰ� */
        NAS_ERABM_SndErabmCdsFreeBuffDataInd();
    }

    /* �������EHRPD������Ϣ */
    NAS_ERABM_InitEhrpdEntity();

    if(NAS_ERABM_L_MODE_STATUS_NORMAL != NAS_ERABM_GetLModeStatus())
    {
        return;
    }

    /*����TFT�ͳ�����Ϣ����IP Filter��Ӳ��������*/
    if(PS_FAIL == NAS_ERABM_IpfConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_RcvRabmEsmClearClBearerNotify: IPF Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEsmRelInd_ENUM, LNAS_ERABM_IPFUpdateIPFilterFailed);
    }

    /*����TFT�ͳ�����Ϣ����IP Filter��CDS*/
    if(PS_FAIL == NAS_ERABM_CdsConfigUlFilter())
    {
        NAS_ERABM_ERR_LOG("NAS_ERABM_RcvRabmEsmClearClBearerNotify: CDS Update IP Filter Failed.");
        TLPS_PRINT2LAYER_ERROR(NAS_ERABM_RcvRabmEsmRelInd_ENUM, LNAS_ERABM_CDSUpdateIPFilterFailed);
    }

    return;
}


#endif


/*lint +e961*/
/*lint +e960*/




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

