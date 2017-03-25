/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmRabmMsgProc.c
    Description : ����RABM����SM����Ϣ
    History     :
     1.���� 00128736      2008-09-01  Draft Enact
     2.����� 00135146    2008-12-18  Modify BA8D00749
     3.����� 00135146    2009-03-06  Modify BA8D01127
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmInclude.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMRABMMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMRABMMSGPROC_C
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
 Function Name  : NAS_ESM_RabmMsgDistr()
 Description    : SMģ��RABM��Ϣ�ַ�����
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.���� 00128736      2008-09-01  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_RabmMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pRabmMsg = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_RabmMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RabmMsgDistr_ENUM, LNAS_ENTRY);

    pRabmMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch(pRabmMsg->ulMsgName)
    {
        /*����յ�����ID_ESM_ERABM_REL_REQ��Ϣ*/
        case ID_ESM_ERABM_REL_REQ:

            /* ���ESM���ڷ�ע��̬����ֱ�ӷ��� */
            if (NAS_ESM_PS_REGISTER_STATUS_DETACHED == NAS_ESM_GetEmmStatus())
            {
                NAS_ESM_WARN_LOG("NAS_ESM_RabmMsgDistr:WARNING:Msg is discard cause ESM state is detached!");
                TLPS_PRINT2LAYER_WARNING(NAS_ESM_RabmMsgDistr_ENUM, 1);
                return ;
            }


            /*����Դ*/
            NAS_ESM_ClearEsmResource();
            break;

        /*RBδ����������ȥ������Ӧ����������*/
        case ID_ESM_ERABM_BEARER_STATUS_REQ:

            /*����ȥ�������������*/
            NAS_ESM_RcvEsmRabmBearerStatusReq((ESM_ERABM_BEARER_STATUS_REQ_STRU *) pRcvMsg);
            break;

        default:
            /*��ӡ�쳣��Ϣ*/
            NAS_ESM_WARN_LOG("NAS_ESM_RabmMsgDistr:WARNING:RABM->SM Message name non-existent!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_RabmMsgDistr_ENUM, 2);
            break;
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_GetPdnAddr
 Description     : ��ȡĳ���ص�PDN��Ϣ
 Input           : NAS_ESM_CONTEXT_IP_ADDR_STRU *pstPdnAddr,
                   VOS_UINT32 ulEpsbId
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong 00150010      2009-7-8  Draft Enact

*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID  NAS_ESM_GetPdnAddr
(
    NAS_ESM_CONTEXT_IP_ADDR_STRU       *pstPdnAddr,
    VOS_UINT32                          ulEpsbId,
    VOS_UINT32                          ulEhrpdBearerId,
    ESM_ERABM_BEARER_RAT_ENUM_UINT8     enBearerCntxtRat
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo   = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity       = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex            = 0;
#endif

    if(VOS_NULL_PTR == pstPdnAddr)
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetPdnAddr:Error:Input parameter is null!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetPdnAddr_ENUM, LNAS_PARAM_INVALID);
        return;
    }
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* ����޸ĵ���EHRPD���أ�ĿǰCL������ֻ֧��ȱʡ���أ���֧��ר�г��� */
    if (ESM_ERABM_BEARER_RAT_EHRPD == enBearerCntxtRat)
    {
        /* ����EHRPD����ID���ҵ�ESM��Ӧ��EHRPD����ʵ������ */
        if (NAS_ESM_SUCCESS == NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId(ulEhrpdBearerId, &ulIndex))
        {

            pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);
            NAS_ESM_MEM_CPY_S(  pstPdnAddr,
                                sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                                &pstPdnEntity->stEhPdnContextInfo.stPdnAddr,
                                sizeof(EHSM_ESM_PDN_ADDR_STRU));

        }
        return;
    }
#endif
    /*��ȡ��ӦEpsbCntxtTbl���ַ*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    /* ����ר�г��أ����ȡ����ȱʡ���ص�EpsbCntxtTbl���ַ */
    if(NAS_ESM_BEARER_TYPE_DEDICATED == NAS_ESM_GetBearCntxtType(ulEpsbId))
    {
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstEpsbCntxtInfo->ulLinkedEpsbId);
    }

    /* ��ȡPDN��Ϣ */
    if(NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpPdnAddr)
    {
        NAS_ESM_MEM_CPY_S(  pstPdnAddr,
                            sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                            &pstEpsbCntxtInfo->stPdnAddrInfo,
                            sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));
    }
    else
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetPdnAddr:Error:No Pdn Address!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetPdnAddr_ENUM, ESM_PDN_TYPE_ERROR);
    }
    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_SndEsmRabmActIndMsg
 Description    : SMģ�鷢��ID_ESM_ERABM_ACT_IND��Ϣ����
 Input          : VOS_UINT32                          LTE�ĳ���ID
                  ESM_ERABM_BEARER_RAT_ENUM_UINT8     ���ؽ��뼼������
                  VOS_UINT8                           EHRPD���ػָ���ʶ
                  VOS_UINT32                          EHRPD����ID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.���� 00128736      2008-09-01  Draft Enact
      2.wangchen 00209181  2014-09-20  Modify:��Ƶͨ������Ƶ���ؽ����󣬱���ȥ���������޸�
        RABM            ESM             EMM             RRC
        |               |               |               |
        |               |               |               |
        |               |LRRC_LRABM_RAB_IND(BEARID=7)   |
        |<----------------------------------------------|
        |               |               |               |
        |               |               |               |
        |               |               |               |
        |               |LMM_ESM_DATA_IND(bearid=7)     |
        |               |<--------------|               |
        |               |(ACT_DEDICT_EPS_BEAR_REQ)      |
        |               |               |               |
        |               |ACT_BEAR_ACP   |               |
        |               |-------------->|               |
        | ESM_LRABM_ACT_IND(bearid=7)   |               |
        |<--------------|               |               |
        |               |               |               |
        |BEAR_STATUS_REQ(bearid=5,6,7)  |               |
        |---->          |               |               |
        |               |               |               |
        |               |LRRC_LRABM_RAB_IND(BEARID=8)   |
        |<----------------------------------------------|
        |               |               |               |
        |               |               |               |
        |               |               |               |
        |               |LMM_ESM_DATA_IND(bearid=8)     |
        |               |<--------------|               |
        |               |(ACT_DEDICT_EPS_BEAR_REQ)      |
        |               |               |               |
        |               |ACT_BEAR_ACP   |               |
        |               |-------------->|               |
        | ESM_LRABM_ACT_IND(bearid=8)   |               |
        |<--------------|               |               |
        |               |               |               |
        | BEAR_STATUS_REQ(bearid=5,6,7) |               |
        |       ------->|               |               |
        |               ESM�յ��󣬽�����8����ȥ����
        |
     3.sunjitan 00193151  2016-01-14  Modify:CL��ģ���������׶��������2��3��4
*****************************************************************************/
/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_SndEsmRabmActIndMsg(
    VOS_UINT32                          ulEpsbId,
    ESM_ERABM_BEARER_RAT_ENUM_UINT8     enBearerCntxtRat,
    VOS_UINT8                           ucHandoverFlag,
    VOS_UINT32                          ulEhrpdBearerId
)
{
    VOS_UINT32                          ulTftPfNum         = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt              = NAS_ESM_NULL;
    VOS_UINT32                          ulTmpCid           = NAS_ESM_NULL;
    ESM_ERABM_ACT_IND_STRU             *pEsmRabmActIndMsg  = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo    = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo   = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    /*lint -e433 -e826*/
    pEsmRabmActIndMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(ESM_ERABM_ACT_IND_STRU));
    /*lint +e433 +e826*/

    if ( VOS_NULL_PTR == pEsmRabmActIndMsg )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmRabmActIndMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmRabmActIndMsg_ENUM, LNAS_EMM_ALLOC_FAIL);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pEsmRabmActIndMsg),
                        NAS_ESM_GET_MSG_LENGTH(pEsmRabmActIndMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pEsmRabmActIndMsg));

    /*��ȡ��ӦEpsbCntxtTbl���ַ*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);
    ulTmpCid = pstEpsbCntxtInfo->ulBitCId;

    NAS_ESM_AssignErabmSessionId(&(pEsmRabmActIndMsg->ucSessionId));

    /* �������ص�����PF��Ϣ */
    for(ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++)
    {
        if(NAS_ESM_OP_TRUE ==((ulTmpCid >> ulCnt )& NAS_ESM_BIT_0))
        {
            pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCnt);

            /*����SDF��PF��Ϣ*/
            NAS_ESM_CopyRabmTftInfo(pEsmRabmActIndMsg->astTftPf + ulTftPfNum,\
                               pstSdfCntxtInfo->astSdfPfInfo,\
                               pstSdfCntxtInfo->ulSdfPfNum);

            ulTftPfNum += pstSdfCntxtInfo->ulSdfPfNum;
        }
    }

    /*��д��Ϣ����*/
    pEsmRabmActIndMsg->ulEpsId = ulEpsbId;
    pEsmRabmActIndMsg->ulTftPfNum = ulTftPfNum;

    /* ��дPDN��Ϣ */
    NAS_ESM_GetPdnAddr(&pEsmRabmActIndMsg->stPdnAddr,ulEpsbId, ulEhrpdBearerId,enBearerCntxtRat);

    pEsmRabmActIndMsg->enBearerCntxtType = pstEpsbCntxtInfo->enBearerCntxtType;
    pEsmRabmActIndMsg->ulLinkedEpsbId = pstEpsbCntxtInfo->ulLinkedEpsbId;
    pEsmRabmActIndMsg->ucQCI = pstEpsbCntxtInfo->stEpsQoSInfo.ucNwQCI;

    /* ��д���صĽ��뼼�����ͣ��Ƿ���handover�ĳ��أ��Լ�EHRPD����ID */
    pEsmRabmActIndMsg->enBearerCntxtRat = enBearerCntxtRat;
    pEsmRabmActIndMsg->ucHandoverFlag   = ucHandoverFlag;
    pEsmRabmActIndMsg->ulEhrpdBearerId  = ulEhrpdBearerId;

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_RABM_MSG_HEAD(pEsmRabmActIndMsg,ID_ESM_ERABM_ACT_IND);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pEsmRabmActIndMsg);

}
/*lint -specific(+e433)*/

/*****************************************************************************
 Function Name  : NAS_ESM_SndEsmRabmMdfIndMsg()
 Description    : SMģ�鷢��ID_ESM_ERABM_MDF_IND��Ϣ����
 Input          : VOS_UINT32                          ����ID
                  ESM_ERABM_BEARER_RAT_ENUM_UINT8     ��������
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.���� 00128736      2008-09-01  Draft Enact
      2.sunjitan 00193151  2016-01-14  Mofify for CL��ģ������
*****************************************************************************/
/*lint -specific(-e433)*/
VOS_VOID NAS_ESM_SndEsmRabmMdfIndMsg(
    VOS_UINT32                          ulEpsbId,
    ESM_ERABM_BEARER_RAT_ENUM_UINT8     enBearerCntxtRat
)
{
    VOS_UINT32                          ulTftPfNum         = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt              = NAS_ESM_NULL;
    VOS_UINT32                          ulTmpCid           = NAS_ESM_NULL;
    ESM_ERABM_MDF_IND_STRU             *pEsmRabmMdfIndMsg  = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo    = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo   = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity       = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex            = 0;
#endif

    /*����ռ䲢��������Ƿ�ɹ�*/
    /*lint -e433 -e826*/
    pEsmRabmMdfIndMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(ESM_ERABM_MDF_IND_STRU));
    /*lint +e433 +e826*/

    if ( VOS_NULL_PTR == pEsmRabmMdfIndMsg )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmRabmMdfIndMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmRabmMdfIndMsg_ENUM, LNAS_EMM_ALLOC_FAIL);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pEsmRabmMdfIndMsg),
                        NAS_ESM_GET_MSG_LENGTH(pEsmRabmMdfIndMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pEsmRabmMdfIndMsg));

    /* ��ֵ���ؽ��뼼������ */
    pEsmRabmMdfIndMsg->enBearerCntxtRat  = enBearerCntxtRat;

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* ����޸ĵ���EHRPD���أ�ĿǰCL������ֻ֧��ȱʡ���أ���֧��ר�г��� */
    if (ESM_ERABM_BEARER_RAT_EHRPD == enBearerCntxtRat)
    {
        /* ����EHRPD����ID���ҵ�ESM��Ӧ��EHRPD����ʵ������ */
        if (NAS_ESM_SUCCESS == NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId(ulEpsbId, &ulIndex))
        {
            /* ȡ��ʵ�� */
            pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

            pEsmRabmMdfIndMsg->enBearerCntxtType = ESM_ERABM_BEARER_TYPE_DEFAULT;
            pEsmRabmMdfIndMsg->ucHandoverFlag    = PS_FALSE;
            pEsmRabmMdfIndMsg->ulEhrpdBearerId   = ulEpsbId;
            pEsmRabmMdfIndMsg->ulEpsId           = ESM_ERABM_INVALID_BEARER_ID;

            /* ����ط����ݽṹ��һ�£���ö��һ�£�1ΪIPV4��2ΪIPV6��3ΪIPV4V6 */
            pEsmRabmMdfIndMsg->stPdnAddr.ucIpType = pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType;

            /* ȡ��IPV4��ַ */
            NAS_ESM_MEM_CPY_S(pEsmRabmMdfIndMsg->stPdnAddr.aucIpV4Addr,
                              APP_MAX_IPV4_ADDR_LEN,
                              pstPdnEntity->stEhPdnContextInfo.stPdnAddr.aucIpv4Addr,
                              EHSM_ESM_IPV4_ADDR_LEN);

            /* ȡ��IPV6��ַ */
            NAS_ESM_MEM_CPY_S(pEsmRabmMdfIndMsg->stPdnAddr.aucIpV6Addr,
                              APP_MAX_IPV6_ADDR_LEN,
                              pstPdnEntity->stEhPdnContextInfo.stPdnAddr.aucIpv6Addr,
                              EHSM_ESM_IPV6_ADDR_LEN);
        }

        /*��д��Ϣͷ*/
        NAS_ESM_WRITE_RABM_MSG_HEAD(pEsmRabmMdfIndMsg,ID_ESM_ERABM_MDF_IND);

        /* ������Ϣ���ͺ��� */
        NAS_ESM_SND_MSG(pEsmRabmMdfIndMsg);
        return;
    }
    #endif

    /* ����޸ĵ���LTE���� */

    /*��ȡ��ӦEpsbCntxtTbl���ַ*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);
    ulTmpCid = pstEpsbCntxtInfo->ulBitCId;

    /* �������ص�����PF��Ϣ */
    for(ulCnt = NAS_ESM_MIN_CID; ulCnt <= NAS_ESM_MAX_CID; ulCnt++)
    {
        if(NAS_ESM_OP_TRUE ==((ulTmpCid >> ulCnt )& NAS_ESM_BIT_0))
        {
            pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCnt);

            /*����SDF��PF��Ϣ*/
            NAS_ESM_CopyRabmTftInfo(pEsmRabmMdfIndMsg->astTftPf + ulTftPfNum,\
                               pstSdfCntxtInfo->astSdfPfInfo,\
                               pstSdfCntxtInfo->ulSdfPfNum);

            ulTftPfNum += pstSdfCntxtInfo->ulSdfPfNum;
        }
    }

    /*��д��Ϣ����*/
    pEsmRabmMdfIndMsg->ulEpsId = ulEpsbId;
    pEsmRabmMdfIndMsg->ulTftPfNum = ulTftPfNum;

    /* ��дPDN��Ϣ */
    NAS_ESM_GetPdnAddr(&pEsmRabmMdfIndMsg->stPdnAddr, ulEpsbId,ESM_ERABM_INVALID_BEARER_ID,enBearerCntxtRat);

    pEsmRabmMdfIndMsg->enBearerCntxtType = pstEpsbCntxtInfo->enBearerCntxtType;
    pEsmRabmMdfIndMsg->ulLinkedEpsbId = pstEpsbCntxtInfo->ulLinkedEpsbId;
    pEsmRabmMdfIndMsg->ucQCI= pstEpsbCntxtInfo->stEpsQoSInfo.ucNwQCI;

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_RABM_MSG_HEAD(pEsmRabmMdfIndMsg,ID_ESM_ERABM_MDF_IND);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pEsmRabmMdfIndMsg);

}
/*lint -specific(+e433)*/

/*****************************************************************************
 Function Name  : NAS_ESM_SndEsmRabmDeactIndMsg()
 Description    : SMģ�鷢��ID_ESM_ERABM_DEACT_IND��Ϣ����
 Input          : VOS_UINT32                         ������Ŀ
                  VOS_UINT32                         ����ID�б�
                  ESM_ERABM_BEARER_RAT_ENUM_UINT8    ���ؽ��뼼������
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.���� 00128736      2008-09-01  Draft Enact
      2.sunjitan 00193151  2016-01-14  Mofify for CL��ģ������
*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmRabmDeactIndMsg(
    VOS_UINT32                          ulEpsbIdNum,
    const VOS_UINT32                   *pulEpsbId,
    ESM_ERABM_BEARER_RAT_ENUM_UINT8     enBearerCntxtRat
)
{
    ESM_ERABM_DEACT_IND_STRU       *pEsmRabmDeactIndMsg   = VOS_NULL_PTR;

    /*�����ڲ���*/
    if( (ulEpsbIdNum == 0) || (ulEpsbIdNum > NAS_ESM_MAX_EPSB_NUM) \
            || (VOS_NULL_PTR == pulEpsbId) )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_WARN_LOG("NAS_ESM_SndEsmRabmDeactIndMsg:WARNING:Input Para error!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_SndEsmRabmDeactIndMsg_ENUM, LNAS_PARAM_INVALID);
        return ;
    }

    /*����ռ䲢��������Ƿ�ɹ�*/
    pEsmRabmDeactIndMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(ESM_ERABM_DEACT_IND_STRU));

    if ( VOS_NULL_PTR == pEsmRabmDeactIndMsg )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmRabmDeactIndMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmRabmDeactIndMsg_ENUM, LNAS_EMM_ALLOC_FAIL);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pEsmRabmDeactIndMsg),
                        NAS_ESM_GET_MSG_LENGTH(pEsmRabmDeactIndMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pEsmRabmDeactIndMsg));

    /*��ulEpsbIdNum��pulEpsbId����pEsmRabmDeactIndMsg*/
    pEsmRabmDeactIndMsg->ulEpsIdNum = ulEpsbIdNum;

    pEsmRabmDeactIndMsg->enBearerCntxtRat = enBearerCntxtRat;

    NAS_ESM_MEM_CPY_S(  (VOS_UINT8*)pEsmRabmDeactIndMsg->aulEpsId,
                        sizeof(pEsmRabmDeactIndMsg->aulEpsId),
                        (VOS_UINT8*)pulEpsbId,
                        (pEsmRabmDeactIndMsg->ulEpsIdNum)*(sizeof(VOS_UINT32)/sizeof(VOS_UINT8)));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_RABM_MSG_HEAD(pEsmRabmDeactIndMsg,ID_ESM_ERABM_DEACT_IND);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pEsmRabmDeactIndMsg);
}

/*****************************************************************************
 Function Name  : NAS_ESM_SndEsmRabmRelIndMsg()
 Description    : SMģ�鷢��ID_ESM_ERABM_REL_IND��Ϣ����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.���� 00128736      2008-09-01  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmRabmRelIndMsg( VOS_VOID )
{
    ESM_ERABM_REL_IND_STRU       *pEsmRabmRelIndMsg   = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pEsmRabmRelIndMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(ESM_ERABM_REL_IND_STRU));

    if ( VOS_NULL_PTR == pEsmRabmRelIndMsg )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmRabmRelIndMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmRabmRelIndMsg_ENUM, LNAS_EMM_ALLOC_FAIL);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pEsmRabmRelIndMsg),
                        NAS_ESM_GET_MSG_LENGTH(pEsmRabmRelIndMsg),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pEsmRabmRelIndMsg));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_RABM_MSG_HEAD(pEsmRabmRelIndMsg,ID_ESM_ERABM_REL_IND);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pEsmRabmRelIndMsg);

}

/*****************************************************************************
 Function Name  : NAS_ESM_SndEsmRabmDeactAllMsg()
 Description    : SMģ����������Ѽ�����ط���ID_ESM_ERABM_DEACT_IND��Ϣ����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.���� 00128736      2008-09-01  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmRabmDeactAllMsg( VOS_VOID )
{
    VOS_UINT32                  ulEpsbId                    = NAS_ESM_NULL;
    VOS_UINT32                  ulActiveFlg                 = NAS_ESM_FAILURE;
    VOS_UINT32                  ulEpsbIdNum                 = NAS_ESM_NULL;
    VOS_UINT32                  aulEpsbId[NAS_ESM_MAX_EPSB_NUM]  = {NAS_ESM_NULL};

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_SndEsmRabmDeactAllMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmRabmDeactAllMsg_ENUM, LNAS_ENTRY);

    /*�ҳ��Ѽ�����أ�����¼��ID*/
    for( ulEpsbId = NAS_ESM_MIN_EPSB_ID; ulEpsbId <= NAS_ESM_MAX_EPSB_ID; ulEpsbId++ )
    {
        /*�˳����Ѽ���*/
        if( NAS_ESM_BEARER_STATE_ACTIVE == NAS_ESM_GetBearCntxtState(ulEpsbId) )
        {
            /*�����Ѽ������ID,׼�����͸�RABM*/
            aulEpsbId[ulEpsbIdNum++] = ulEpsbId;

            /*���ñ�ʶλ*/
            ulActiveFlg = NAS_ESM_SUCCESS;
        }
    }

    /*������еĳ��ؾ�δ����*/
    if( NAS_ESM_FAILURE == ulActiveFlg )
    {
        /*��ӡ��Ϣ*/
        NAS_ESM_NORM_LOG("NAS_ESM_SndEsmRabmDeactAllMsg:NORMAL:no bearer active!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_SndEsmRabmDeactAllMsg_ENUM, 1);
        return ;
    }

    /*֪ͨRABM����RABM����ID_ESM_ERABM_DEACT_IND*/
    NAS_ESM_SndEsmRabmDeactIndMsg(ulEpsbIdNum, aulEpsbId, ESM_ERABM_BEARER_RAT_LTE);

}

/*****************************************************************************
 Function Name  : NAS_ESM_CopyRabmTftInfo()
 Description    : ����TFT��Ϣ��RABM
 Input          : ESM_ERABM_TFT_PF_STRU* pstRabmTftInfo
                  NAS_ESM_CONTEXT_TFT_STRU* pstCntxtTftInfo
 Output         : ESM_ERABM_TFT_PF_STRU* pstRabmTftInfo
 Return Value   : VOS_VOID

 History        :
      1.���� 00128736      2008-09-01  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_CopyRabmTftInfo( ESM_ERABM_TFT_PF_STRU* pstRabmTftInfo,
                                         const NAS_ESM_CONTEXT_TFT_STRU* pstCntxtTftInfo,
                                            VOS_UINT32 ulSdfPfNum)
{
    VOS_UINT32                          ulPfNum = NAS_ESM_NULL;

    ulPfNum = ulSdfPfNum;

    /*���*/
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)pstRabmTftInfo,
                        ulPfNum * sizeof(ESM_ERABM_TFT_PF_STRU),
                        0,
                        ulPfNum * sizeof(ESM_ERABM_TFT_PF_STRU));

    /* ����*/
    NAS_ESM_MEM_CPY_S(  pstRabmTftInfo,
                        ulPfNum * sizeof(ESM_ERABM_TFT_PF_STRU),
                        pstCntxtTftInfo,
                        ulPfNum * sizeof(ESM_ERABM_TFT_PF_STRU));
}


/*****************************************************************************
 Function Name   : NAS_ESM_RcvEsmRabmBearerStatusReq
 Description     : RBδ������RABM���͵�ǰ������������Ϣ��
                    ESMȥ�����ӦRBδ��������������
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.zhuyiqiang 00138739      2009-3-10  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_RcvEsmRabmBearerStatusReq(const ESM_ERABM_BEARER_STATUS_REQ_STRU *pRcvMsg )
{
    VOS_UINT32                  ulCnt                           = NAS_ESM_NULL;
    VOS_UINT32                  ulQueryRslt                     = NAS_ESM_FAILURE;
    VOS_UINT32                  ulEpsbId                        = NAS_ESM_NULL;
    VOS_UINT32                  ulEpsbIdNum                     = NAS_ESM_NULL;
    VOS_UINT32                  aulEpsbId[NAS_ESM_MAX_EPSB_NUM] = {NAS_ESM_NULL};
    VOS_UINT32                  ulStateTblIndex                 =  NAS_ESM_NULL;
    NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbCntxtInfo              = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_RcvEsmRabmBearerStatusReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_RcvEsmRabmBearerStatusReq_ENUM, LNAS_ENTRY);

    /* ���ESM���ڷ�ע��̬����ֱ�ӷ��� */
    if (NAS_ESM_PS_REGISTER_STATUS_DETACHED == NAS_ESM_GetEmmStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmRabmBearerStatusReq:WARNING:Msg is discard cause ESM state is detached!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmRabmBearerStatusReq_ENUM, LNAS_FAIL);
        return ;
    }

    /* ����������������ʱ������ERABM���͵�BEAR_STATUS_REQ��Ϣʱ�����ʱ������ı���ȥ������أ��������
    OPID����ƥ�䣻�����RABM�������͵���Ϣ������ƥ�䣻RABM���ESM��ACT_IND��Ϣ�ظ�BEAR_STATUS_REQ��Ϣʱ��
    ����OPIDƥ�䣬���ƥ�䲻�ɹ���ֱ�Ӷ��� */
    if ((pRcvMsg->ucSessionId != 0) && (pRcvMsg->ucSessionId != NAS_ESM_GetErabmSessionIdValue()))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_RcvEsmRabmBearerStatusReq:WARNING:Msg is discard cause OPID is not match!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_RcvEsmRabmBearerStatusReq_ENUM, LNAS_ERROR);
        return;
    }

    /*ȡ����Ϣ�е�EPSID��Ϣ*/
    ulEpsbIdNum = pRcvMsg->ulEpsIdNum;

    NAS_ESM_MEM_CPY_S(  aulEpsbId,
                        sizeof(aulEpsbId),
                        pRcvMsg->aulEpsId,
                        ulEpsbIdNum*(sizeof(VOS_UINT32)/sizeof(VOS_UINT8)));

    /*��ѯÿһ��������Ϣ*/
    for( ulEpsbId = NAS_ESM_MIN_EPSB_ID; ulEpsbId <= NAS_ESM_MAX_EPSB_ID; ulEpsbId++ )
    {
        /*ȡ��������Ϣ*/
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

        /*����˳���δ����*/
        if( NAS_ESM_BEARER_STATE_INACTIVE == pstEpsbCntxtInfo->enBearerCntxtState )
        {
            continue;
        }

        ulQueryRslt = NAS_ESM_FAILURE;

        /*��ѯID_ESM_ERABM_BEARER_STATUS_IND��Ϣ��EPSID��Ϣ���Ƿ�����˳���ID*/
        for( ulCnt = 0; ulCnt < ulEpsbIdNum; ulCnt++ )
        {
            if( ulEpsbId == aulEpsbId[ulCnt] )
            {
                ulQueryRslt = NAS_ESM_SUCCESS;
                break;
            }
        }

        /*���������*/
        if( NAS_ESM_FAILURE == ulQueryRslt )
        {
            /*֪ͨAPP�ͷų��أ����ͷ���س��غ���Դ*/
            NAS_ESM_DeactBearerAndInformApp(ulEpsbId);
            /*�������ֹ��ulEpsbId������������Ϣ*/
            if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByEpsbId(ulEpsbId, &ulStateTblIndex))
            {
                NAS_ESM_RelStateTblResource(ulStateTblIndex);
            }
        }
    }

    /*֪ͨEMM��ǰ����״̬��Ϣ������ID_EMM_ESM_BEARER_STATUS_REQ*/
    NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);

}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 Function Name  : NAS_ESM_SndEsmRabmClearClBearerNotifyMsg
 Description    : SMģ�鷢��ID_ESM_ERABM_CLEAR_CL_BEARER_NOTIFY��Ϣ����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151         2016-01-14  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmRabmClearClBearerNotifyMsg(VOS_VOID)
{
    ESM_ERABM_CLEAR_CL_BEARER_NOTIFY_STRU        *pEsmRabmClearBearerMsg = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pEsmRabmClearBearerMsg = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(ESM_ERABM_CLEAR_CL_BEARER_NOTIFY_STRU));

    if ( VOS_NULL_PTR == pEsmRabmClearBearerMsg )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmRabmClearClBearerNotifyMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmRabmClearClBearerNotifyMsg_ENUM, LNAS_EMM_ALLOC_FAIL);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET_S(NAS_ESM_GET_MSG_ENTITY(pEsmRabmClearBearerMsg),
                      NAS_ESM_GET_MSG_LENGTH(pEsmRabmClearBearerMsg),
                      0,
                      NAS_ESM_GET_MSG_LENGTH(pEsmRabmClearBearerMsg));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_RABM_MSG_HEAD(pEsmRabmClearBearerMsg, ID_ESM_ERABM_CLEAR_CL_BEARER_NOTIFY);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pEsmRabmClearBearerMsg);
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
/* end of NasEsmRabmMsgProc.c */
