/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmNwMsgPdnConProc.c
    Description : ����EMM����SM��������Ϣ
    History     :
     1.���� 00128736        2008-09-01  Draft Enact
     2.ף��ǿ 00138739      2008-12-03  Modify BA8D00656
     3.����� 00135146      2008-12-19  Modify BA8D00755
     4.����� 00135146      2009-03-06  Modify BA8D01127
     5.���00150010         2009-08-05  Modify  BJ9D01627
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmInclude.h"
/*#include    "IpDhcpv4Server.h"*/
#include    "LRabmPdcpInterface.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASESMNWMSGPDNCONPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASESMNWMSGPDNCONPROC_C
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
/*extern VOS_UINT32  APPITF_SendRequestArp(const VOS_UINT8* pucReqIPAddr);
extern VOS_UINT32 APPITF_ConfigBoardIPAddr(const VOS_UINT8* pucCfgIP);*/


/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwMsgEsmCause54
 Description     : ����ESMԭ��ֵ54
 Input           : ulStateTblIndex -- ��̬������
                   pRcvMsg         -- �յ��Ŀտ���Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151      2014-02-17   Draft Enact
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_ESM_ProcNwMsgEsmCause54
(
    VOS_UINT32                          ulStateTblIndex,
    const EMM_ESM_INTRA_DATA_IND_STRU  *pRcvMsg
)
{
	#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulIndex;
	#endif

    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr    = VOS_NULL_PTR;

    (VOS_VOID)pRcvMsg;
    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcNwMsgEsmCause54 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgEsmCause54_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* �ȵ�EHRPDʵ���в����Ƿ�����EHRPD���� */
    if (NAS_ESM_SUCCESS == NAS_ESM_GetEhrpdPdnEntityIndexBasedCid(pstStateAddr->ulCid, &ulIndex))
    {
        /* �����ATTACH������ */
        if (NAS_ESM_PS_REGISTER_STATUS_ATTACHED != NAS_ESM_GetEmmStatus())
        {
            /* ���EHRPDʵ�崦�ڵȴ��ָ�̬��˵��һֱδ�յ��������ȱʡ���ؼ������� */
            if (NAS_ESM_EHRPD_ENTITY_STATE_ALREADY_RCV_FIRST_BEARER_ACT_REQ != NAS_ESM_GET_EHRPD_ENTITY_STATE())
            {
                /* ǿ������EHRPDʵ������Ѿ��յ������һ��ȱʡ����״̬��֪ͨEHSMɾ�����г��� */
                NAS_ESM_SET_EHRPD_ENTITY_STATE(NAS_ESM_EHRPD_ENTITY_STATE_ALREADY_RCV_FIRST_BEARER_ACT_REQ);

                /* ֧��EHRPD���뼼����֪ͨEHSM */
                if (NAS_ESM_SUCCESS == NAS_EMM_IsEhrpdOr1XRatExist())
                {
                    NAS_ESM_SndEhsmClearAllBearerNotifyMsg();
                }
            }

            /* ɾ������EHRPD���ؼ�¼����APS���ָ�ʧ�� */
            NAS_ESM_ClearAllEhrpdPdnInfoProc();

            /* ֪ͨRABM������г�����Դ */
            NAS_ESM_SndEsmRabmClearClBearerNotifyMsg();
        }
        else
        {
            /* ע��̬���������ػָ�ʧ�ܣ����˳��ذ��ָ�ʧ�ܴ��� */
            NAS_ESM_EhrpdPdnConnectHandOverFailProc(ulIndex);
        }

        return;
    }
    #endif

    /* �Ѿ�ע�ᣬ��APP���Ŵ���PDN��������ĳ��������ظ�APP���ֱ�����·���PDN��������
       ������������Ϊinitial request */
    if((NAS_ESM_PS_REGISTER_STATUS_ATTACHED == NAS_ESM_GetEmmStatus())
        &&(ID_APP_ESM_NDISCONN_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType))
    {
        /* �޸�״̬���м�¼��PDN�������ͣ����·���PDN������������֮ǰ��״̬��δ�ͷţ�
           �������±��뼴�� */
        pstStateAddr->enPdnReqType = NAS_ESM_PDN_REQ_TYPE_INITIAL;

        /*���NAS_ESM_ENCODE_INFO_STRU*/
        NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                            sizeof(NAS_ESM_ENCODE_INFO_STRU),
                            0,
                            sizeof(NAS_ESM_ENCODE_INFO_STRU));

        stEncodeInfo.bitOpESMCau        = NAS_ESM_OP_FALSE;
        stEncodeInfo.ulCid              = pstStateAddr->ulCid;
        stEncodeInfo.ucPti              = pstStateAddr->stNwMsgRecord.ucPti;
        stEncodeInfo.ulEpsbId           = pstStateAddr->ulEpsbId;
        stEncodeInfo.enPdnReqType       = pstStateAddr->enPdnReqType;

        /*��װPDN_Connect_Req��Ϣ*/
        if(NAS_ESM_FAILURE == NAS_ESM_EncodePdnConReqMsg(stEncodeInfo, \
                                                         pstStateAddr->stNwMsgRecord.aucMsgBuff,\
                                                         &pstStateAddr->stNwMsgRecord.ulMsgLength))
        {
            NAS_ESM_WARN_LOG("NAS_ESM_ProcNwMsgEsmCause54:WARNING:EncodePdnConReqMsg fail!");
            TLPS_PRINT2LAYER_WARNING(NAS_ESM_ProcNwMsgEsmCause54_ENUM, ESM_PDN_TYPE_ERROR);

            /*��APP�ظ�APP_ESM_BEARER_SETUP_CNF(ʧ��)��Ϣ*/
            NAS_ESM_SndEsmAppNdisConnCnfFailMsg(ulStateTblIndex, APP_ERR_UNSPECIFIED_ERROR);
            NAS_ESM_RelStateTblResource(ulStateTblIndex);
            return ;
        }

        pstStateAddr->stNwMsgRecord.ulOpId = NAS_ESM_AllocEmmEsmOpId();
        #if (FEATURE_ON == FEATURE_DSDS)
        pstStateAddr->enEsmBearerDataCnf = NAS_ESM_BEARER_DATA_CNF_SENDING;
        NAS_ESM_SendBeginSessionNotify();
        #endif

        /*���ú�����SM->EMM������Ϣ:ID_EMM_ESM_DATA_REQ(NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ)*/
        NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,
                                    pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,
                                    pstStateAddr->stNwMsgRecord.ulMsgLength,
                                    pstStateAddr->stNwMsgRecord.aucMsgBuff);

        /* ��¼�տ���Ϣ */
        NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,
                                   pstStateAddr->stNwMsgRecord.ulMsgLength,
                                   NAS_ESM_AIR_MSG_DIR_ENUM_UP,
                                   ESM_PDN_CONNECT_REQ);

        /*����T3482��ʱ��*/
        NAS_ESM_TimerStart(ulStateTblIndex,TI_NAS_ESM_T3482);

        /*״̬ת��*/
        NAS_ESM_SetProcTransState(ulStateTblIndex,NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);
        return;

    }

    return;

}
/*****************************************************************************
 Function Name  : NAS_ESM_PdnRejInfoCreate
 Description    : ����һ��PDN���ܾ��Ľڵ�
 Input          :
 Output         : VOS_VOID
 Return Value   : ��ַ��ʵ��ָ�룬�������ʧ�ܣ��򷵻�VOS_NULL_PTR

 History        :
      1.wangchen 00209181   2014-09-20  Draft Enact
*****************************************************************************/
NAS_ESM_PDN_REJ_INFO_STRU* NAS_ESM_PdnRejInfoCreate
(
    APP_ESM_PDN_TYPE_ENUM_UINT32        enPdnType,
    VOS_UINT32                          bitOpApn,
    APP_ESM_APN_INFO_STRU               *pstApnInfo
)
{
    NAS_ESM_PDN_REJ_INFO_STRU *pstPdnRejInfo = VOS_NULL_PTR;

    NAS_ESM_NORM_LOG("NAS_ESM_PdnRejInfoCreate is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_PdnRejInfoCreate_ENUM, LNAS_ENTRY);

    pstPdnRejInfo = (NAS_ESM_PDN_REJ_INFO_STRU*)NAS_ESM_MEM_ALLOC(sizeof(NAS_ESM_PDN_REJ_INFO_STRU));
    if (pstPdnRejInfo != VOS_NULL_PTR)
    {
        NAS_ESM_MEM_SET_S(  pstPdnRejInfo,
                            sizeof(NAS_ESM_PDN_REJ_INFO_STRU),
                            0,
                            sizeof(NAS_ESM_PDN_REJ_INFO_STRU));

        pstPdnRejInfo->enPdnType = enPdnType;

        if (NAS_ESM_OP_TRUE == bitOpApn)
        {
             pstPdnRejInfo->bitOpApnInfo = NAS_ESM_OP_TRUE;

             NAS_ESM_MEM_CPY_S( &(pstPdnRejInfo->stApnInfo),
                                sizeof(APP_ESM_APN_INFO_STRU),
                                pstApnInfo,
                                sizeof(APP_ESM_APN_INFO_STRU));
        }
        else
        {
             pstPdnRejInfo->bitOpApnInfo = NAS_ESM_OP_FALSE;
        }

        NAS_EMM_GetEplmnList(&(pstPdnRejInfo->stEPlmnList));

    }

    return pstPdnRejInfo;
}

/*****************************************************************************
 Function Name  : NAS_ESM_PdnRejListAdd
 Description    : �򱻽��б������һ���µĵ�ַ�ԣ��µĵ�ַ�Իᱻ��ӵ��б��β��
 Input          : ppstListHead  ָ���ַ���б��ָ��
                  pstNode       ����ӵĵ�ַ��
 Output         : VOS_VOID
 Return Value   : �ɹ���ӵĵ�ַ��ָ��

 History        :
      1.wangchen 00209181   2014-09-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_PdnRejListAdd(NAS_ESM_PDN_REJ_INFO_STRU **ppstListHead, NAS_ESM_PDN_REJ_INFO_STRU *pstNode)
{
    NAS_ESM_PDN_REJ_INFO_STRU *pstTmp = VOS_NULL_PTR;

    NAS_ESM_NORM_LOG("NAS_ESM_PdnRejListAdd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_PdnRejListAdd_ENUM, LNAS_ENTRY);

    if (VOS_NULL_PTR == *ppstListHead)
    {
        *ppstListHead = pstNode;

        pstNode->pstNext = VOS_NULL_PTR;
    }
    else
    {
        pstTmp = *ppstListHead;
        while (VOS_NULL_PTR != pstTmp->pstNext)
        {
            pstTmp = pstTmp->pstNext;
        }
        pstTmp->pstNext = pstNode;

        pstNode->pstNext = VOS_NULL_PTR;
    }

    return;
}
/*****************************************************************************
 Function Name  : NAS_ESM_PdnRejListDestroy
 Description    : �������������б�
 Input          : pstListHead   �����ٵĵ�ַ���б�
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2014-09-20  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_PdnRejListDestroy(NAS_ESM_PDN_REJ_INFO_STRU *pstListHead)
{
    NAS_ESM_PDN_REJ_INFO_STRU *pstTmpPdnRejInfo = VOS_NULL_PTR;

    NAS_ESM_NORM_LOG("NAS_ESM_PdnRejListDestroy is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_PdnRejListDestroy_ENUM, LNAS_ENTRY);

    while (pstListHead)
    {
        pstTmpPdnRejInfo = pstListHead;
        pstListHead = pstListHead->pstNext;

        NAS_ESM_MEM_FREE(pstTmpPdnRejInfo);
    }
}


/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwMsgEsmCause50
 Description     : ����ESMԭ��ֵ50
 Input           : ulStateTblIndex -- ��̬������
                   pRcvMsg         -- �յ��Ŀտ���Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181     2014-09-04   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_ProcNwMsgEsmCause50
(
    VOS_UINT32                          ulStateTblIndex,
    const EMM_ESM_INTRA_DATA_IND_STRU  *pRcvMsg
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr    = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara   = VOS_NULL_PTR;
    NAS_ESM_PDN_REJ_INFO_STRU           **ppstPdnRejInfo = VOS_NULL_PTR;
    NAS_ESM_PDN_REJ_INFO_STRU           *pstNewPdnRejInfo = VOS_NULL_PTR;

    (VOS_VOID)pRcvMsg;
    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcNwMsgEsmCause50 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgEsmCause50_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfPara = NAS_ESM_GetSdfParaAddr(pstStateAddr->ulCid);

    ppstPdnRejInfo = &(pg_stNasEsmEntity->pstPdnRej50Info);

    if ( VOS_TRUE == NAS_ESM_IsCurrentApnHas50Rej(pstSdfPara->enPdnType,
                                                    pstSdfPara->bitOpApn,
                                                    &(pstSdfPara->stApnInfo)))
    {
        return;
    }

    /* �����µĽڵ㣬��������Ϣ��ӵ������б� */
    pstNewPdnRejInfo = NAS_ESM_PdnRejInfoCreate(pstSdfPara->enPdnType,pstSdfPara->bitOpApn,&pstSdfPara->stApnInfo);

    if (pstNewPdnRejInfo)
    {
        NAS_ESM_PdnRejListAdd(ppstPdnRejInfo, pstNewPdnRejInfo);

    }
    else
    {
        NAS_ESM_ERR_LOG("NAS_ESM_PdnRejInfoCreate: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ProcNwMsgEsmCause50_ENUM, LNAS_EMM_ALLOC_FAIL);
    }


    return;

}
/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwMsgEsmCause51
 Description     : ����ESMԭ��ֵ51
 Input           : ulStateTblIndex -- ��̬������
                   pRcvMsg         -- �յ��Ŀտ���Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181     2014-09-04   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_ProcNwMsgEsmCause51
(
    VOS_UINT32                          ulStateTblIndex,
    const EMM_ESM_INTRA_DATA_IND_STRU  *pRcvMsg
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr    = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara   = VOS_NULL_PTR;
    NAS_ESM_PDN_REJ_INFO_STRU           **ppstPdnRejInfo = VOS_NULL_PTR;
    NAS_ESM_PDN_REJ_INFO_STRU           *pstNewPdnRejInfo = VOS_NULL_PTR;
    ESM_EMM_PLMN_ID_STRU                stCurrentCampInfo;

    (VOS_VOID)pRcvMsg;
    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcNwMsgEsmCause51 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgEsmCause51_ENUM, LNAS_ENTRY);

    NAS_EMM_GetCurrentCampInfo(&stCurrentCampInfo);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfPara = NAS_ESM_GetSdfParaAddr(pstStateAddr->ulCid);

    ppstPdnRejInfo = &(pg_stNasEsmEntity->pstPdnRej51Info);

    /* ��������б�Ϊ�գ�����������鿴��APN��PLMN�Ƿ��Ѿ����б��д��� */
    if ( VOS_TRUE == NAS_ESM_IsCurrentApnHas51Rej(pstSdfPara->enPdnType,
                                                pstSdfPara->bitOpApn,
                                                &(pstSdfPara->stApnInfo)))
    {
        return;
    }

    /* �����µĽڵ㣬��������Ϣ��ӵ������б� */
    pstNewPdnRejInfo = NAS_ESM_PdnRejInfoCreate(pstSdfPara->enPdnType,pstSdfPara->bitOpApn, &pstSdfPara->stApnInfo);

    if (pstNewPdnRejInfo)
    {
        NAS_ESM_PdnRejListAdd(ppstPdnRejInfo, pstNewPdnRejInfo);

    }
    else
    {
        NAS_ESM_ERR_LOG("NAS_ESM_PdnRejInfoCreate: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ProcNwMsgEsmCause51_ENUM, LNAS_EMM_ALLOC_FAIL);
    }


    return;

}
/*****************************************************************************
 Function Name   : NAS_ESM_ProcNwMsgEsmCause66
 Description     : ����ESMԭ��ֵ66
 Input           : ulStateTblIndex -- ��̬������
                   pRcvMsg         -- �յ��Ŀտ���Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181     2014-09-04   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_ProcNwMsgEsmCause66
(
    VOS_UINT32                          ulStateTblIndex,
    const EMM_ESM_INTRA_DATA_IND_STRU  *pRcvMsg
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr    = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara   = VOS_NULL_PTR;
    NAS_ESM_PDN_REJ_INFO_STRU           **ppstPdnRejInfo = VOS_NULL_PTR;
    NAS_ESM_PDN_REJ_INFO_STRU           *pstNewPdnRejInfo = VOS_NULL_PTR;
    ESM_EMM_PLMN_ID_STRU                stCurrentCampInfo;

    (VOS_VOID)pRcvMsg;
    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcNwMsgEsmCause66 is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcNwMsgEsmCause66_ENUM, LNAS_ENTRY);

    NAS_EMM_GetCurrentCampInfo(&stCurrentCampInfo);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfPara = NAS_ESM_GetSdfParaAddr(pstStateAddr->ulCid);

    ppstPdnRejInfo = &(pg_stNasEsmEntity->pstPdnRej66Info);

    /* ��������б�Ϊ�գ�����������鿴��APN��PLMN�Ƿ��Ѿ����б��д��� */
    if ( VOS_TRUE == NAS_ESM_IsCurrentApnHas66Rej(pstSdfPara->bitOpApn,
                                                &(pstSdfPara->stApnInfo)))
    {
        return;
    }

    /* �����µĽڵ㣬��������Ϣ��ӵ������б� */
    pstNewPdnRejInfo = NAS_ESM_PdnRejInfoCreate(pstSdfPara->enPdnType,pstSdfPara->bitOpApn, &pstSdfPara->stApnInfo);

    if (pstNewPdnRejInfo)
    {
        NAS_ESM_PdnRejListAdd(ppstPdnRejInfo, pstNewPdnRejInfo);

    }
    else
    {
        NAS_ESM_ERR_LOG("NAS_ESM_PdnRejInfoCreate: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_ProcNwMsgEsmCause66_ENUM, LNAS_EMM_ALLOC_FAIL);
    }


    return;

}

/*****************************************************************************
 Function Name   : NAS_ESM_ProcValidNwMsgPdnConnRej
 Description     : ����PDN���Ӿܾ�������Ϣ
 Input           : ulStateTblIndex -- ��̬������
                   pRcvMsg         -- �յ��Ŀտ���Ϣ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunbing49683      2009-4-16   Draft Enact
    2.lihong00150010    2010-08-12  Modify
    3.liuwenyu00143951  2010-11-11  Modify
*****************************************************************************/
VOS_VOID NAS_ESM_ProcValidNwMsgPdnConnRej
(
    VOS_UINT32                          ulStateTblIndex,
    const EMM_ESM_INTRA_DATA_IND_STRU  *pRcvMsg
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr    = VOS_NULL_PTR;
    NAS_BACKOFF_MAINTAIN_PARA_STRU      stMaintainPara;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara      = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcValidNwMsgPdnConnRej is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcValidNwMsgPdnConnRej_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstSdfPara   = NAS_ESM_GetSdfParaAddr(pstStateAddr->ulCid);

    /* ����APN������Back-off�㷨����ά�� */
    if(NAS_ESM_OP_TRUE == pstSdfPara->bitOpApn)
    {
        NAS_ESM_MEM_SET_S(  &stMaintainPara,
                            sizeof(NAS_BACKOFF_MAINTAIN_PARA_STRU),
                            0,
                            sizeof(NAS_BACKOFF_MAINTAIN_PARA_STRU));
        NAS_ESM_MEM_CPY_S(  &stMaintainPara.stApnInfo,
                            sizeof(APP_ESM_APN_INFO_STRU),
                            &pstSdfPara->stApnInfo,
                            sizeof(APP_ESM_APN_INFO_STRU));

        stMaintainPara.enPdpResult = NAS_BACKOFF_PDP_ACTIVE_RESULT_CN_REJ;
        if(NAS_ESM_OP_TRUE == pRcvMsg->stEsmNwMsgIE.bitOpEsmCause)
        {
            stMaintainPara.ucCnCause = pRcvMsg->stEsmNwMsgIE.enEsmCau;
        }
        else
        {
            stMaintainPara.ucCnCause = 0;
        }

        NAS_BACKOFF_OperateMaintain(NAS_BACKOFF_NETRAT_LTE, &stMaintainPara);
    }

    /* ����������handover��PDN���������յ�ԭ��ֵ54 */
    if((NAS_ESM_OP_TRUE == pRcvMsg->stEsmNwMsgIE.bitOpEsmCause)
        &&(NAS_ESM_CAUSE_PDN_CONNECTION_DOES_NOT_EXIST == pRcvMsg->stEsmNwMsgIE.enEsmCau)
        &&(NAS_ESM_PDN_REQ_TYPE_HANDOVER == pstStateAddr->enPdnReqType))
    {
        NAS_ESM_ProcNwMsgEsmCause54(ulStateTblIndex, pRcvMsg);
        return;
    }

    if (ESM_EMM_RELEASE_R11 <= NAS_EMM_GetNasRelease())
    {
        if((NAS_ESM_OP_TRUE == pRcvMsg->stEsmNwMsgIE.bitOpEsmCause)
            &&(NAS_ESM_CAUSE_PDNTYPE_IPV4_ONLY_ALLOWED == pRcvMsg->stEsmNwMsgIE.enEsmCau))
        {
            NAS_ESM_ProcNwMsgEsmCause50(ulStateTblIndex, pRcvMsg);
        }

        if((NAS_ESM_OP_TRUE == pRcvMsg->stEsmNwMsgIE.bitOpEsmCause)
            &&(NAS_ESM_CAUSE_PDNTYPE_IPV6_ONLY_ALLOWED == pRcvMsg->stEsmNwMsgIE.enEsmCau))
        {
            NAS_ESM_ProcNwMsgEsmCause51(ulStateTblIndex, pRcvMsg);
        }

        if((NAS_ESM_OP_TRUE == pRcvMsg->stEsmNwMsgIE.bitOpEsmCause)
            &&(NAS_ESM_CAUSE_APN_NOT_SUPPORT_IN_CURRENT_RAT_AND_PLMN == pRcvMsg->stEsmNwMsgIE.enEsmCau))
        {
            NAS_ESM_ProcNwMsgEsmCause66(ulStateTblIndex, pRcvMsg);
        }
    }

    /*��APP�ظ���Ϣ*/
    if(ID_APP_ESM_PDP_SETUP_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType )
    {
        /*��APP����ID_APP_ESM_PDP_SETUP_CNF(ʧ��)��Ϣ*/
        NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, \
                  NAS_ESM_GetAppErrorByEsmCause(pRcvMsg->stEsmNwMsgIE.enEsmCau));
    }
    /*��APP�ظ���Ϣ*/
    else if(ID_APP_ESM_NDISCONN_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType )
    {
        /*��APP����ID_APP_ESM_NDISCONN_CNF(ʧ��)��Ϣ*/
        NAS_ESM_LOG1("NAS_ESM_ProcValidNwMsgPdnConnRej:ERROR =", NAS_ESM_GetAppErrorByEsmCause(pRcvMsg->stEsmNwMsgIE.enEsmCau));
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_ProcValidNwMsgPdnConnRej_ENUM, LNAS_ERROR, NAS_ESM_GetAppErrorByEsmCause(pRcvMsg->stEsmNwMsgIE.enEsmCau));
        NAS_ESM_SndEsmAppNdisConnCnfFailMsg(ulStateTblIndex, \
                                      NAS_ESM_GetAppErrorByEsmCause(pRcvMsg->stEsmNwMsgIE.enEsmCau));
    }
    else
    {
        /*��APP����ID_APP_ESM_PDP_SETUP_IND(ʧ��)��Ϣ*/
        NAS_ESM_SndEsmAppSdfSetupIndMsg(ulStateTblIndex, \
                  NAS_ESM_GetAppErrorByEsmCause(pRcvMsg->stEsmNwMsgIE.enEsmCau));
    }

    /*�ͷ�״̬����Դ*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);

}


/*****************************************************************************
 Function Name   : NAS_ESM_ProcValidNwMsgActDefltEpsbReq
 Description     : ����ȱʡ���ؼ��������տ���Ϣ
 Input           : ulStateTblIndex -- ��̬������
                   pRcvMsg         -- �յ��Ŀտ���Ϣ
 Output          : None
 Return          : None

 History         :
    1.���� 00128736      2008-9-10   Draft Enact
    2.sunbing 49683         2009-02-05  Modify
    3.lihong00150010        2010-2-02   Modify
    4.liuwenyu00143951      2010-11-11  Modify
*****************************************************************************/
VOS_VOID  NAS_ESM_ProcValidNwMsgActDefltEpsbReq
(
    VOS_UINT32                                  ulStateTblIndex,
    const EMM_ESM_INTRA_DATA_IND_STRU          *pRcvMsg
)
{
    VOS_UINT32                          ulEpsbId         = NAS_ESM_NULL;
    EMM_ESM_INTRA_DATA_IND_STRU        *pMsg             = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;

    /*��ӡ����ú���*/
    NAS_ESM_NORM_LOG("NAS_ESM_ProcValidNwMsgActDefltEpsbReq is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ProcValidNwMsgActDefltEpsbReq_ENUM, LNAS_ENTRY);

    pMsg = (EMM_ESM_INTRA_DATA_IND_STRU *) pRcvMsg;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*ȡ��������Ϣ*/
    ulEpsbId = (VOS_UINT32)(pMsg->stEsmNwMsgIE.ucEpsbId);
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);
    pstEpsbCntxtInfo->ulLinkedEpsbId = 0;

    /*��ʼ���������NAS_ESM_ENCODE_INFO_STRU*/

    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.bitOpESMCau = NAS_ESM_OP_FALSE;
    stEncodeInfo.ucPti       = pstStateAddr->stNwMsgRecord.ucPti;
    stEncodeInfo.ulEpsbId    = ulEpsbId;

    /*ֹͣ��ʱ��*/
    NAS_ESM_TimerStop(ulStateTblIndex, TI_NAS_ESM_T3482);

    /* �Զ�����ȱʡ���ؼ���Ĵ��� */
    NAS_ESM_DefltBearActMsgAutoAccept(ulStateTblIndex,
                                      stEncodeInfo,
                                      &(pMsg->stEsmNwMsgIE));
}

/*****************************************************************************
 Function Name   : NAS_ESM_SaveNwActDefltEpsbReqInfo
 Description     : ����ȱʡ���ؼ������������Ϣ
 Input           : pstMsgIE         -- ������������Ϣ
                   ulStateTblIndex  -- ��̬������
 Output          : None
 Return          : VOS_VOID

 History         :
    1.liuwenyu  00143951      2009-12-02  Draft Enact
    2.sunjitan    00193151      2011-09-23  Modified
*****************************************************************************/
VOS_VOID NAS_ESM_SaveNwActDefltEpsbReqInfo
(
    const  NAS_ESM_NW_MSG_STRU          *pstMsgIE,
    VOS_UINT32                           ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr      = VOS_NULL_PTR;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo   = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo  = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_SaveNwActDefltEpsbReqInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveNwActDefltEpsbReqInfo_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(pstStateAddr->ulCid);

    /* ����SDF��QOS���� */
    NAS_ESM_MEM_CPY_S(  &pstSdfCntxtInfo->stSdfQosInfo,
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU),
                        &pstMsgIE->stSdfQosInfo,
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));

    /* ����SDF�������е�PF��Ϣ�͹���������Ϣ */
    pstSdfCntxtInfo->ulSdfPfNum = NAS_ESM_NULL;
    pstSdfCntxtInfo->ulEpsbId = pstMsgIE->ucEpsbId;

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstMsgIE->ucEpsbId);

    /* ����EPS QOS��ʶλ��EPS QOS���� */
    pstEpsbCntxtInfo->bitOpEpsQos = NAS_ESM_OP_TRUE;

    NAS_ESM_MEM_CPY_S(  &(pstEpsbCntxtInfo->stEpsQoSInfo),
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU),
                        &(pstSdfCntxtInfo->stSdfQosInfo),
                        sizeof(NAS_ESM_CONTEXT_LTE_QOS_STRU));

    /*�洢PDN��Ϣ������PDN��ʶλ*/
    pstEpsbCntxtInfo->bitOpPdnAddr = NAS_ESM_OP_TRUE;
    NAS_ESM_MEM_CPY_S(  &pstEpsbCntxtInfo->stPdnAddrInfo,
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                        &pstMsgIE->stPdnAddrInfo,
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

    if ((NAS_ESM_PDN_IPV4 == pstEpsbCntxtInfo->stPdnAddrInfo.ucIpType)
        || (NAS_ESM_PDN_IPV4_IPV6 == pstEpsbCntxtInfo->stPdnAddrInfo.ucIpType))
    {
        #if (VOS_OS_VER != VOS_WIN32)
        /*������������IP��ַ����CPE��IP��ַ��Ŀǰֻ������IPV4*/
        pstEpsbCntxtInfo->bitOpGateWayAddrInfo = NAS_ESM_OP_TRUE;

        /* ����IP��ַ����������� */
        pstEpsbCntxtInfo->stSubnetMask.ucIpType = NAS_ESM_PDN_IPV4;
        NAS_ESM_DHCPGetIPv4Mask(pstEpsbCntxtInfo->stPdnAddrInfo.aucIpV4Addr,
                                        pstEpsbCntxtInfo->stSubnetMask.aucIpV4Addr);

        /* ����IP��ַ������ص�ַ */
        pstEpsbCntxtInfo->stGateWayAddrInfo.ucIpType = NAS_ESM_PDN_IPV4;
        NAS_ESM_DHCPGetIPv4GateWay(pstEpsbCntxtInfo->stPdnAddrInfo.aucIpV4Addr,
                                        pstEpsbCntxtInfo->stSubnetMask.aucIpV4Addr,
                                        pstEpsbCntxtInfo->stGateWayAddrInfo.aucIpV4Addr);
        #else
        /*������������IP��ַ����CPE��IP��ַ��Ŀǰֻ������IPV4*/
        pstEpsbCntxtInfo->bitOpGateWayAddrInfo = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  &pstEpsbCntxtInfo->stGateWayAddrInfo,
                            sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                            &pstEpsbCntxtInfo->stPdnAddrInfo,
                            sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

        if(pstEpsbCntxtInfo->stGateWayAddrInfo.aucIpV4Addr[APP_MAX_IPV4_ADDR_LEN-1] == NAS_ESM_GATEWAYE_IP1)
        {
            pstEpsbCntxtInfo->stGateWayAddrInfo.aucIpV4Addr[APP_MAX_IPV4_ADDR_LEN-1] = NAS_ESM_GATEWAYE_IP2;
        }
        else
        {
            pstEpsbCntxtInfo->stGateWayAddrInfo.aucIpV4Addr[APP_MAX_IPV4_ADDR_LEN-1] = NAS_ESM_GATEWAYE_IP1;
        }

        NAS_ESM_SetSubnetMask(pstEpsbCntxtInfo->stSubnetMask);
        #endif
    }
    /*����APN��ʶλ*/
    pstEpsbCntxtInfo->bitOpApn= NAS_ESM_OP_TRUE;

    NAS_ESM_MEM_CPY_S(  &pstEpsbCntxtInfo->stApnInfo,
                        sizeof(APP_ESM_APN_INFO_STRU),
                        &pstMsgIE->stApnInfo,
                        sizeof(APP_ESM_APN_INFO_STRU));

    /*���TI(�������)��ֱ�Ӵ洢*/
    pstEpsbCntxtInfo->bitOpTransId = pstMsgIE->bitOpTransId;
    NAS_ESM_MEM_CPY_S(  &pstEpsbCntxtInfo->stTransId,
                        sizeof(NAS_ESM_CONTEXT_TRANS_ID_STRU),
                        &pstMsgIE->stTransId,
                        sizeof(NAS_ESM_CONTEXT_TRANS_ID_STRU));

    /*���PDP QOS(�������)��ֱ�Ӵ洢*/
    pstEpsbCntxtInfo->bitOpNegQos = pstMsgIE->bitOpNegQos;
    NAS_ESM_MEM_CPY_S(  &pstEpsbCntxtInfo->stCntxtQosInfo,
                        sizeof(NAS_ESM_CONTEXT_QOS_STRU),
                        &pstMsgIE->stCntxtQosInfo,
                        sizeof(NAS_ESM_CONTEXT_QOS_STRU));

    /*���LLC SAPI(�������)��ֱ�Ӵ洢*/
    pstEpsbCntxtInfo->bitOpLlcSapi = pstMsgIE->bitOpLlcSapi;
    pstEpsbCntxtInfo->ucLlcSapi = pstMsgIE->ucLlcSapi;

    /*���Radio Priority(�������)��ֱ�Ӵ洢*/
    pstEpsbCntxtInfo->bitOpRadioPriority = pstMsgIE->bitOpRadioPriority;
    pstEpsbCntxtInfo->ucRadioPriority = pstMsgIE->ucRadioPriority;

    /*���Packet Flow Identifer(�������)��ֱ�Ӵ洢*/
    pstEpsbCntxtInfo->bitOpPacketFlowId = pstMsgIE->bitOpPacketFlowId;
    pstEpsbCntxtInfo->ucPacketFlowId = pstMsgIE->ucPacketFlowId;

    /*���APN-AMBR(�������)��ֱ�Ӵ洢*/
    pstEpsbCntxtInfo->bitOpApnAmbr = pstMsgIE->bitOpApnAmbr;

    NAS_ESM_MEM_CPY_S(  &pstEpsbCntxtInfo->stApnAmbrInfo,
                        sizeof(NAS_ESM_CONTEXT_APN_AMBR_STRU),
                        &pstMsgIE->stApnAmbrInfo,
                        sizeof(NAS_ESM_CONTEXT_APN_AMBR_STRU));

    /*���ESM Cause(�������)��ֱ�Ӵ洢*/
    pstEpsbCntxtInfo->bitOpEsmCause = pstMsgIE->bitOpEsmCause;
    pstEpsbCntxtInfo->enEsmCau = pstMsgIE->enEsmCau;

    /*���ESM PCO(�������)��ֱ�Ӵ洢*/
    pstEpsbCntxtInfo->bitOpPco = pstMsgIE->bitOpPco;

    NAS_ESM_MEM_CPY_S(  &pstEpsbCntxtInfo->stPcoInfo,
                        sizeof(NAS_ESM_CONTEXT_PCO_STRU),
                        &pstMsgIE->stPcoInfo,
                        sizeof(NAS_ESM_CONTEXT_PCO_STRU));
}
/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmAppPdpManageIndMsg
 Description     : ��APP����
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-12-3  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_SndEsmAppPdpManageIndMsg
(
    const APP_ESM_PDP_MANAGER_IND_STRU       *pstPdpManInd
)
{
    APP_ESM_PDP_MANAGER_IND_STRU    *pstPdpManIndTmp = VOS_NULL_PTR;

    /*����ռ�ͼ���Ƿ����ɹ�*/
    pstPdpManIndTmp = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(APP_ESM_PDP_MANAGER_IND_STRU));
    if (VOS_NULL_PTR == pstPdpManIndTmp)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_SndEsmAppPdpManageIndMsg:ERROR:Alloc msg fail!" );
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEsmAppPdpManageIndMsg_ENUM, LNAS_EMM_ALLOC_FAIL);
        return;
    }

    /*���*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pstPdpManIndTmp),
                        NAS_ESM_GET_MSG_LENGTH(pstPdpManIndTmp),
                        NAS_ESM_NULL,
                        NAS_ESM_GET_MSG_LENGTH(pstPdpManIndTmp));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_TAF_MSG_HEAD(pstPdpManIndTmp,
                               ID_APP_ESM_PDP_MANAGER_IND,
                               pstPdpManInd->usOriginalId,
                               pstPdpManInd->usTerminalId,
                               pstPdpManInd->ulSN);

    /* ��д��Ϣ���� */
    pstPdpManIndTmp->ulCid           = pstPdpManInd->ulCid;
    pstPdpManIndTmp->ulOpId          = pstPdpManInd->ulOpId;
    pstPdpManIndTmp->enOperateType   = pstPdpManInd->enOperateType;

    pstPdpManIndTmp->bitOpLinkCid    = pstPdpManInd->bitOpLinkCid;
    pstPdpManIndTmp->ulLinkCid       = pstPdpManInd->ulLinkCid;

    pstPdpManIndTmp->bitOpModifyTpye = pstPdpManInd->bitOpModifyTpye;
    pstPdpManIndTmp->enBearerModifyType = pstPdpManInd->enBearerModifyType;

    /* ������Ϣ���ͺ���*/
    NAS_ESM_SND_MSG(pstPdpManIndTmp);

}

/*****************************************************************************
 Function Name   : NAS_ESM_IsDhcpProcedureNeeded
 Description     : �ж��Ƿ���Ҫ����DHCP���̻�ȡ�������
 Input           : ucEpsbId-----------------���غ�
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.lihong00150010      2010-11-30  Draft Enact

*****************************************************************************/
VOS_UINT32 NAS_ESM_IsDhcpProcedureNeeded
(
    VOS_UINT32                          ucEpsbId
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo = VOS_NULL_PTR;

    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ucEpsbId);

    /* ���PDN����ΪIPV6������Ҫ����DHCP���� */
    if (NAS_ESM_PDN_IPV6 == pstEpsbCntxtInfo->stPdnAddrInfo.ucIpType)
    {
        NAS_ESM_NORM_LOG("NAS_ESM_IsDhcpProcedureNeeded:PDN type is ipv6!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_IsDhcpProcedureNeeded_ENUM, 1);
        return PS_FALSE;
    }

    /* ���IPv4��ַΪ0.0.0.0������Ҫ����DHCP���� */
    if (NAS_ESM_IS_IPV4_ADDR_INVALID(pstEpsbCntxtInfo->stPdnAddrInfo.aucIpV4Addr))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_IsDhcpProcedureNeeded:PDN address is 0.0.0.0!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_IsDhcpProcedureNeeded_ENUM, 2);
        return PS_TRUE;
    }

    /* ���������DNS������������Ҫ����DHCP���� */
    if ((NAS_ESM_OP_TRUE != pstEpsbCntxtInfo->bitOpPco)
        || (NAS_ESM_NULL == pstEpsbCntxtInfo->stPcoInfo.ucIpv4DnsSerNum))
    {
        NAS_ESM_NORM_LOG("NAS_ESM_IsDhcpProcedureNeeded:DNS address is not exist!");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_IsDhcpProcedureNeeded_ENUM, 3);
        return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndEsmAppSdfSetupSuccMsg
 Description     : ��APP�ظ��ɹ���Ϣ
 Input           : ucEpsbId-----------------���غ�
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2010-11-30  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SndEsmAppSdfSetupSuccMsg
(
    VOS_UINT32                          ulStateTblIndex
)
{
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    if((NAS_ESM_OP_TRUE == pstStateAddr->bitOpAppMsgRecord)
        && (ID_APP_ESM_PDP_SETUP_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType))
    {
        /*��APP����ID_APP_ESM_PDP_SETUP_CNF(�ɹ�)��Ϣ*/
        NAS_ESM_SndEsmAppSdfSetupCnfSuccMsg(ulStateTblIndex);
    }
    else if((NAS_ESM_OP_TRUE == pstStateAddr->bitOpAppMsgRecord)
            && (ID_APP_ESM_NDISCONN_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType))
    {
        /*��APP����ID_APP_ESM_NDISCONN_CNF(�ɹ�)��Ϣ*/
        NAS_ESM_SndEsmAppNdisConnCnfSuccMsg(ulStateTblIndex);
    }
    else
    {
        NAS_ESM_SndEsmAppSdfSetupIndMsg(ulStateTblIndex, APP_SUCCESS);
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_SetEpsBearTftInfo
 Description     : ��ֵ����TFT��Ϣ
 Input           : ulBitCId-----------------���ع���CID
                   pstEpsBearInfoInd--------ESM��SM�ӿڵĳ�����Ϣָ��
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-04-30  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SetEpsBearTftInfo
(
    VOS_UINT32                          ulBitCId,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearInfoInd
)
{
    VOS_UINT32                          ulCnt1          = NAS_ESM_NULL;
    VOS_UINT32                          ulCnt2          = NAS_ESM_NULL;
    NAS_ESM_SDF_CNTXT_INFO_STRU        *pstSdfCntxtInfo = VOS_NULL_PTR;

    pstEpsBearInfoInd->bitOpTft         = NAS_ESM_OP_TRUE;
    pstEpsBearInfoInd->stTft.ulPfNum    = NAS_ESM_NULL;

    for ( ulCnt1 = NAS_ESM_MIN_CID; ulCnt1 <= NAS_ESM_MAX_CID; ulCnt1++ )
    {
        if(NAS_ESM_OP_FALSE == ((ulBitCId >> ulCnt1) & NAS_ESM_OP_TRUE))
        {
            continue;
        }

        pstSdfCntxtInfo = NAS_ESM_GetSdfCntxtInfo(ulCnt1);
        for ( ulCnt2 = NAS_ESM_NULL; ulCnt2 < pstSdfCntxtInfo->ulSdfPfNum; ulCnt2++ )
        {
            pstEpsBearInfoInd->stTft.astCidPf[pstEpsBearInfoInd->stTft.ulPfNum].ulCid = ulCnt1;

            NAS_ESM_MEM_CPY_S(  &pstEpsBearInfoInd->stTft.astCidPf[pstEpsBearInfoInd->stTft.ulPfNum].stPf,
                                sizeof(SM_ESM_PF_STRU),
                                &pstSdfCntxtInfo->astSdfPfInfo[ulCnt2],
                                sizeof(NAS_ESM_CONTEXT_TFT_STRU));

            pstEpsBearInfoInd->stTft.ulPfNum++;
        }
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_SetEpsBearPcoIpv4Item
 Description     : ��ֵ����PCO IPV4��
 Input           : pstEpsbCntxtInfo-----------------ESM������Ϣָ��
                   pstEpsBearInfoInd----------------ESM��SM�ӿ��еĳ�����Ϣָ��
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-04-30  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SetEpsBearPcoIpv4Item
(
    const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbCntxtInfo,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearInfoInd
)
{
    if (pstEpsbCntxtInfo->stPcoInfo.ucIpv4DnsSerNum == 1)
    {
        pstEpsBearInfoInd->bitOpPcoIpv4Item = NAS_ESM_OP_TRUE;
        pstEpsBearInfoInd->stPcoIpv4Item.bitOpPriDns = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv4Item.aucPriDns,
                            APP_MAX_IPV4_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv4DnsServer[0].aucIpV4Addr,
                            APP_MAX_IPV4_ADDR_LEN);

        pstEpsBearInfoInd->stPcoIpv4Item.bitOpSecDns = NAS_ESM_OP_FALSE;
    }

    if (pstEpsbCntxtInfo->stPcoInfo.ucIpv4DnsSerNum == 2)
    {
        pstEpsBearInfoInd->bitOpPcoIpv4Item = NAS_ESM_OP_TRUE;
        pstEpsBearInfoInd->stPcoIpv4Item.bitOpPriDns = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv4Item.aucPriDns,
                            APP_MAX_IPV4_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv4DnsServer[0].aucIpV4Addr,
                            APP_MAX_IPV4_ADDR_LEN);
        pstEpsBearInfoInd->stPcoIpv4Item.bitOpSecDns = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv4Item.aucSecDns,
                            APP_MAX_IPV4_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv4DnsServer[1].aucIpV4Addr,
                            APP_MAX_IPV4_ADDR_LEN);
    }

    if (pstEpsbCntxtInfo->stPcoInfo.ucIpv4PcscfNum == 1)
    {
        pstEpsBearInfoInd->bitOpPcoIpv4Item = NAS_ESM_OP_TRUE;
        pstEpsBearInfoInd->stPcoIpv4Item.bitOpPriPcscf = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv4Item.aucPriPcscf,
                            APP_MAX_IPV4_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv4Pcscf[0].aucIpV4Addr,
                            APP_MAX_IPV4_ADDR_LEN);

        pstEpsBearInfoInd->stPcoIpv4Item.bitOpSecPcscf = NAS_ESM_OP_FALSE;
        pstEpsBearInfoInd->stPcoIpv4Item.bitOpThiPcscf = NAS_ESM_OP_FALSE;
    }

    if (pstEpsbCntxtInfo->stPcoInfo.ucIpv4PcscfNum == 2)
    {
        pstEpsBearInfoInd->bitOpPcoIpv4Item = NAS_ESM_OP_TRUE;
        pstEpsBearInfoInd->stPcoIpv4Item.bitOpPriPcscf = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv4Item.aucPriPcscf,
                            APP_MAX_IPV4_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv4Pcscf[0].aucIpV4Addr,
                            APP_MAX_IPV4_ADDR_LEN);
        pstEpsBearInfoInd->stPcoIpv4Item.bitOpSecPcscf = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv4Item.aucSecPcscf,
                            APP_MAX_IPV4_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv4Pcscf[1].aucIpV4Addr,
                            APP_MAX_IPV4_ADDR_LEN);

        pstEpsBearInfoInd->stPcoIpv4Item.bitOpThiPcscf = NAS_ESM_OP_FALSE;
    }

    if (pstEpsbCntxtInfo->stPcoInfo.ucIpv4PcscfNum == 3)
    {
        pstEpsBearInfoInd->bitOpPcoIpv4Item = NAS_ESM_OP_TRUE;
        pstEpsBearInfoInd->stPcoIpv4Item.bitOpPriPcscf = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv4Item.aucPriPcscf,
                            APP_MAX_IPV4_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv4Pcscf[0].aucIpV4Addr,
                            APP_MAX_IPV4_ADDR_LEN);
        pstEpsBearInfoInd->stPcoIpv4Item.bitOpSecPcscf = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv4Item.aucSecPcscf,
                            APP_MAX_IPV4_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv4Pcscf[1].aucIpV4Addr,
                            APP_MAX_IPV4_ADDR_LEN);

        pstEpsBearInfoInd->stPcoIpv4Item.bitOpThiPcscf = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv4Item.aucThiPcscf,
                            APP_MAX_IPV4_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv4Pcscf[2].aucIpV4Addr,
                            APP_MAX_IPV4_ADDR_LEN);
    }

    if (pstEpsbCntxtInfo->stPcoInfo.ucIpv4NbnsNum == 1)
    {
        pstEpsBearInfoInd->bitOpPcoIpv4Item = NAS_ESM_OP_TRUE;
        pstEpsBearInfoInd->stPcoIpv4Item.bitOpPriNbns = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv4Item.aucPriNbns,
                            APP_MAX_IPV4_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv4Nbns[0].aucIpV4Addr,
                            APP_MAX_IPV4_ADDR_LEN);

        pstEpsBearInfoInd->stPcoIpv4Item.bitOpSecNbns = NAS_ESM_OP_FALSE;
    }

    if (pstEpsbCntxtInfo->stPcoInfo.ucIpv4NbnsNum == 2)
    {
        pstEpsBearInfoInd->bitOpPcoIpv4Item = NAS_ESM_OP_TRUE;
        pstEpsBearInfoInd->stPcoIpv4Item.bitOpPriNbns = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv4Item.aucPriNbns,
                            APP_MAX_IPV4_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv4Nbns[0].aucIpV4Addr,
                            APP_MAX_IPV4_ADDR_LEN);
        pstEpsBearInfoInd->stPcoIpv4Item.bitOpSecNbns = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv4Item.aucSecNbns,
                            APP_MAX_IPV4_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv4Nbns[1].aucIpV4Addr,
                            APP_MAX_IPV4_ADDR_LEN);
    }
}
/*****************************************************************************
 Function Name   : NAS_ESM_SetEpsBearPcoIpv6Item
 Description     : ��ֵ����PCO IPV6��
 Input           : pstEpsbCntxtInfo-----------------ESM������Ϣָ��
                   pstEpsBearInfoInd----------------ESM��SM�ӿ��еĳ�����Ϣָ��
 Output          : None
 Return          : VOS_VOID

 History         :
    1.n00181501       2011-12-16  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SetEpsBearPcoIpv6Item
(
    const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbCntxtInfo,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearInfoInd
)
{
    if (pstEpsbCntxtInfo->stPcoInfo.ucIpv6DnsSerNum == 1)
    {
        pstEpsBearInfoInd->bitOpPcoIpv6Item = NAS_ESM_OP_TRUE;
        pstEpsBearInfoInd->stPcoIpv6Item.bitOpPriDns = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv6Item.aucPriDns,
                            APP_MAX_IPV6_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv6DnsServer[0].aucIpV6Addr,
                            APP_MAX_IPV6_ADDR_LEN);

        pstEpsBearInfoInd->stPcoIpv6Item.bitOpSecDns = NAS_ESM_OP_FALSE;
    }

    if (pstEpsbCntxtInfo->stPcoInfo.ucIpv6DnsSerNum == 2)
    {
        pstEpsBearInfoInd->bitOpPcoIpv6Item = NAS_ESM_OP_TRUE;
        pstEpsBearInfoInd->stPcoIpv6Item.bitOpPriDns = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv6Item.aucPriDns,
                            APP_MAX_IPV6_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv6DnsServer[0].aucIpV6Addr,
                            APP_MAX_IPV6_ADDR_LEN);
        pstEpsBearInfoInd->stPcoIpv6Item.bitOpSecDns = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv6Item.aucSecDns,
                            APP_MAX_IPV6_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv6DnsServer[1].aucIpV6Addr,
                            APP_MAX_IPV6_ADDR_LEN);
    }

    if (pstEpsbCntxtInfo->stPcoInfo.ucIpv6PcscfNum == 1)
    {
        pstEpsBearInfoInd->bitOpPcoIpv6Item = NAS_ESM_OP_TRUE;
        pstEpsBearInfoInd->stPcoIpv6Item.bitOpPriPcscf = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv6Item.aucPriPcscf,
                            APP_MAX_IPV6_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv6Pcscf[0].aucIpV6Addr,
                            APP_MAX_IPV6_ADDR_LEN);

        pstEpsBearInfoInd->stPcoIpv6Item.bitOpSecPcscf = NAS_ESM_OP_FALSE;
    }

    if (pstEpsbCntxtInfo->stPcoInfo.ucIpv6PcscfNum == 2)
    {
        pstEpsBearInfoInd->bitOpPcoIpv6Item = NAS_ESM_OP_TRUE;
        pstEpsBearInfoInd->stPcoIpv6Item.bitOpPriPcscf = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv6Item.aucPriPcscf,
                            APP_MAX_IPV6_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv6Pcscf[0].aucIpV6Addr,
                            APP_MAX_IPV6_ADDR_LEN);
        pstEpsBearInfoInd->stPcoIpv6Item.bitOpSecPcscf = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv6Item.aucSecPcscf,
                            APP_MAX_IPV6_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv6Pcscf[1].aucIpV6Addr,
                            APP_MAX_IPV6_ADDR_LEN);
    }
    if (pstEpsbCntxtInfo->stPcoInfo.ucIpv6PcscfNum == 3)
    {
        pstEpsBearInfoInd->bitOpPcoIpv6Item = NAS_ESM_OP_TRUE;
        pstEpsBearInfoInd->stPcoIpv6Item.bitOpPriPcscf = NAS_ESM_OP_TRUE;

        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv6Item.aucPriPcscf,
                            APP_MAX_IPV6_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv6Pcscf[0].aucIpV6Addr,
                            APP_MAX_IPV6_ADDR_LEN);
        pstEpsBearInfoInd->stPcoIpv6Item.bitOpSecPcscf = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv6Item.aucSecPcscf,
                            APP_MAX_IPV6_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv6Pcscf[1].aucIpV6Addr,
                            APP_MAX_IPV6_ADDR_LEN);

        pstEpsBearInfoInd->stPcoIpv6Item.bitOpThiPcscf = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stPcoIpv6Item.aucThiPcscf,
                            APP_MAX_IPV6_ADDR_LEN,
                            pstEpsbCntxtInfo->stPcoInfo.astIpv6Pcscf[2].aucIpV6Addr,
                            APP_MAX_IPV6_ADDR_LEN);
    }

}

/*****************************************************************************
 Function Name   : NAS_ESM_SetEpsBearInfo
 Description     : ��ֵ������Ϣ
 Input           : pstEpsbCntxtInfo-----------------ESM������Ϣָ��
                   pstEpsBearInfoInd----------------ESM��SM�ӿ��еĳ�����Ϣָ��
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-04-30  Draft Enact

*****************************************************************************/
VOS_VOID NAS_ESM_SetEpsBearInfo
(
    const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbCntxtInfo,
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearInfoInd
)
{
    NAS_ESM_CONTEXT_APN_STRU            stTmpApnInfo    = {NAS_ESM_NULL};
    VOS_UINT32                          ulRslt          = NAS_ESM_NULL;

    /* ��ֵEPS QOS */
    pstEpsBearInfoInd->bitOpEpsQos = NAS_ESM_OP_TRUE;

    NAS_ESM_MEM_CPY_S(  &pstEpsBearInfoInd->stEpsQos,
                        sizeof(SM_ESM_EPS_QOS_STRU),
                        &pstEpsbCntxtInfo->stEpsQoSInfo.stQosInfo,
                        sizeof(APP_ESM_EPS_QOS_INFO_STRU));

    /* ��ֵ����CID */
    pstEpsBearInfoInd->ulBitCid = pstEpsbCntxtInfo->ulBitCId;

    /* ��ֵTFT��Ϣ */
    NAS_ESM_SetEpsBearTftInfo(pstEpsbCntxtInfo->ulBitCId, pstEpsBearInfoInd);

    /* ��ֵLLC SAPI */
    pstEpsBearInfoInd->bitOpLlcSapi = pstEpsbCntxtInfo->bitOpLlcSapi;
    pstEpsBearInfoInd->ucLlcSapi = pstEpsbCntxtInfo->ucLlcSapi;

    /* ��ֵPDP QOS */
    pstEpsBearInfoInd->bitOpNegQos = pstEpsbCntxtInfo->bitOpNegQos;

    NAS_ESM_MEM_CPY_S(  &pstEpsBearInfoInd->stNegQos,
                        sizeof(SM_ESM_PDP_QOS_STRU),
                        &pstEpsbCntxtInfo->stCntxtQosInfo,
                        sizeof(NAS_ESM_CONTEXT_QOS_STRU));

    /* ��ֵpacket flow id */
    pstEpsBearInfoInd->bitOpPacketFlowId = pstEpsbCntxtInfo->bitOpPacketFlowId;
    pstEpsBearInfoInd->ucPacketFlowId = pstEpsbCntxtInfo->ucPacketFlowId;

    /* ��ֵradio priority */
    pstEpsBearInfoInd->bitOpRadioPriority = pstEpsbCntxtInfo->bitOpRadioPriority;
    pstEpsBearInfoInd->ucRadioPriority = pstEpsbCntxtInfo->ucRadioPriority;

    /* ��ֵtransaction id */
    pstEpsBearInfoInd->bitOpTransId = pstEpsbCntxtInfo->bitOpTransId;

    NAS_ESM_MEM_CPY_S(  &pstEpsBearInfoInd->stTransId,
                        sizeof(SM_ESM_TRANSACTION_ID_STRU),
                        &pstEpsbCntxtInfo->stTransId,
                        sizeof(NAS_ESM_CONTEXT_TRANS_ID_STRU));

    if (PS_TRUE == NAS_ESM_IsDefaultEpsBearerType(pstEpsbCntxtInfo->enBearerCntxtType))
    {
        /* �������APN��Ϣת��δ�����APN��Ϣ */
        ulRslt = NAS_ESM_ApnTransformaton(&stTmpApnInfo,
                                          &pstEpsbCntxtInfo->stApnInfo);
        if(APP_SUCCESS != ulRslt)
        {
            pstEpsBearInfoInd->bitOpApn = NAS_ESM_OP_FALSE;
        }
        else
        {
            /* ��ֵAPN */
            pstEpsBearInfoInd->bitOpApn = NAS_ESM_OP_TRUE;
            pstEpsBearInfoInd->stApn.ucLength = stTmpApnInfo.ucApnLen;

            NAS_ESM_MEM_CPY_S(  pstEpsBearInfoInd->stApn.aucValue,
                                SM_ESM_MAX_LENGTH_OF_APN,
                                stTmpApnInfo.aucApnName,
                                APP_MAX_APN_LEN);
        }

        /* ��ֵPDN ADDRESS */
        NAS_ESM_MEM_CPY_S(   &pstEpsBearInfoInd->stPdnAddr,
                             sizeof(SM_ESM_PDN_ADDR_STRU),
                             &pstEpsbCntxtInfo->stPdnAddrInfo,
                             sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

        /* ��ֵAPN-AMBR */
        pstEpsBearInfoInd->bitOpApnAmbr = pstEpsbCntxtInfo->bitOpApnAmbr;
        NAS_ESM_MEM_CPY_S(  &pstEpsBearInfoInd->stEpsApnAmbr,
                            sizeof(SM_ESM_EPS_APN_AMBR_STRU),
                            &pstEpsbCntxtInfo->stApnAmbrInfo,
                            sizeof(NAS_ESM_CONTEXT_APN_AMBR_STRU));

        if (NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpPco)
        {
            /* ��ֵBCM */
            pstEpsBearInfoInd->bitOpBcm = pstEpsbCntxtInfo->stPcoInfo.bitOpBcm;
            pstEpsBearInfoInd->enBcm = pstEpsbCntxtInfo->stPcoInfo.enBcm;

            /* ��ֵ����PCO IPV4�� */
            NAS_ESM_SetEpsBearPcoIpv4Item(pstEpsbCntxtInfo, pstEpsBearInfoInd);

            /* ��ֵ����PCO IPV6�� */
            NAS_ESM_SetEpsBearPcoIpv6Item(pstEpsbCntxtInfo, pstEpsBearInfoInd);
            pstEpsBearInfoInd->bitOpImCnSigalFlag   = pstEpsbCntxtInfo->stPcoInfo.bitOpImsCnSignalFlag;
            pstEpsBearInfoInd->enImCnSignalFlag     = (VOS_UINT8)pstEpsbCntxtInfo->stPcoInfo.enImsCnSignalFlag;
        }


        /* ����ǽ������أ������ý�����ʶ */
        if (NAS_ESM_BEARER_TYPE_EMERGENCY == pstEpsbCntxtInfo->enBearerCntxtType)
        {
            pstEpsBearInfoInd->bitOpEmcInd = NAS_ESM_OP_TRUE;
            pstEpsBearInfoInd->enEmergencyInd = SM_ESM_PDP_FOR_EMC;
        }
    }
    else
    {
        /* ��ֵLink EpabId */
        pstEpsBearInfoInd->bitOpLinkedEpsbId = NAS_ESM_OP_TRUE;
        pstEpsBearInfoInd->ulLinkedEpsbId = pstEpsbCntxtInfo->ulLinkedEpsbId;

        /* ��ֵPDN ADDRESS */
        pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(pstEpsbCntxtInfo->ulLinkedEpsbId);

        NAS_ESM_MEM_CPY_S(  &pstEpsBearInfoInd->stPdnAddr,
                            sizeof(SM_ESM_PDN_ADDR_STRU),
                            &pstEpsbCntxtInfo->stPdnAddrInfo,
                            sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));
    }
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndSmEspBearerActIndMsg
 Description     : ��SM���ͳ��ؼ�����Ϣ
 Input           : ucEpsbId-----------------���غ�
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2011-04-30  Draft Enact

*****************************************************************************/
/*lint -specific(-e433)*/

VOS_VOID NAS_ESM_SndSmEspBearerActIndMsg
(
    VOS_UINT32                          ulEpsbId
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo   = VOS_NULL_PTR;
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearInfoInd  = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    /*lint -e433 -e826*/
    pstEpsBearInfoInd = (VOS_VOID*)NAS_ESM_ALLOC_MSG(sizeof(SM_ESM_EPS_BEARER_INFO_IND_STRU));
    /*lint +e433 +e826*/

    if ( VOS_NULL_PTR == pstEpsBearInfoInd )
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndSmEspBearerActIndMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndSmEspBearerActIndMsg_ENUM, LNAS_EMM_ALLOC_FAIL);
        return ;
    }

    /*���*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pstEpsBearInfoInd),
                        NAS_ESM_GET_MSG_LENGTH(pstEpsBearInfoInd),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pstEpsBearInfoInd));

    /*��ȡ��ӦEpsbCntxtTbl���ַ*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    pstEpsBearInfoInd->enPdpOption  = SM_ESM_PDP_OPT_ACTIVATE;
    pstEpsBearInfoInd->ulEpsbId     = ulEpsbId;

    /* ��ֵ������Ϣ */
    NAS_ESM_SetEpsBearInfo(pstEpsbCntxtInfo, pstEpsBearInfoInd);

    if( NAS_ESM_OP_TRUE == pstEpsbCntxtInfo->bitOpEsmCause)
    {
        /*���������Ϣ����ԭ���룬��֪ͨSM*/
        pstEpsBearInfoInd->bitOpErrorCode = NAS_ESM_OP_TRUE;
        pstEpsBearInfoInd->ulErrorCode    = NAS_ESM_GetAppErrorByEsmCause(pstEpsbCntxtInfo->enEsmCau);
    }
    else
    {
        pstEpsBearInfoInd->bitOpErrorCode = NAS_ESM_OP_FALSE;
    }

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_SM_MSG_HEAD(pstEpsBearInfoInd, ID_ESM_SM_EPS_BEARER_INFO_IND);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstEpsBearInfoInd);
}
/*lint -specific(+e433)*/

/*****************************************************************************
 Function Name   : NAS_ESM_DefltBearActMsgAutoAccept
 Description     : �Զ�����ȱʡ���ؼ���Ĵ���
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.liuwenyu 00143951    2009-12-3    Draft Enact
    2.liuhua   00212067    2012-09-06   Add support for double APN
    3.sunjitan 00193151    2015-06-16   Modify for 1XCL_MULTI_MODE_PHASEI
*****************************************************************************/
VOS_VOID NAS_ESM_DefltBearActMsgAutoAccept
(
    VOS_UINT32                          ulStateTblIndex,
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo,
    const NAS_ESM_NW_MSG_STRU          *pstDecodedNwMsg
)
{
    VOS_UINT32                          ulSndNwMsgLen    = NAS_ESM_NULL;
    VOS_UINT32                          ulCurPdnNum      = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt           = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulIsEhPdnHandover= NAS_ESM_FAILURE;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstEhrpdEntity   = VOS_NULL_PTR;
    #endif

    NAS_BACKOFF_MAINTAIN_PARA_STRU      stMaintainPara;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara       = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_DefltBearActMsgAutoAccept is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DefltBearActMsgAutoAccept_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstSdfPara   = NAS_ESM_GetSdfParaAddr(pstStateAddr->ulCid);

    /* ����APN������Back-off�㷨����ά�� */
    if(NAS_ESM_OP_TRUE == pstSdfPara->bitOpApn)
    {
        NAS_ESM_MEM_SET_S(  &stMaintainPara,
                            sizeof(NAS_BACKOFF_MAINTAIN_PARA_STRU),
                            0,
                            sizeof(NAS_BACKOFF_MAINTAIN_PARA_STRU));
        NAS_ESM_MEM_CPY_S(  &stMaintainPara.stApnInfo,
                            sizeof(APP_ESM_APN_INFO_STRU),
                            &pstSdfPara->stApnInfo,
                            sizeof(APP_ESM_APN_INFO_STRU));

        stMaintainPara.enPdpResult = NAS_BACKOFF_PDP_ACTIVE_RESULT_SUCC;
        stMaintainPara.ucCnCause   = 0;
        NAS_BACKOFF_OperateMaintain(NAS_BACKOFF_NETRAT_LTE, &stMaintainPara);
    }

    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* ���ж��Ƿ���EHRPD���ػָ����̣�APNֻ����SDF�еģ��տ��еĿ��ܱ����Ӻ�׺���²�׼ȷ */
    ulIsEhPdnHandover = NAS_ESM_GetEhrpdPdnEntityIndexBasedApn(&pstSdfPara->stApnInfo, &ulIndex);
    #endif

    /* ����ȱʡ���ؼ������������Ϣ */
    NAS_ESM_SaveNwActDefltEpsbReqInfo(pstDecodedNwMsg,ulStateTblIndex);

    /*������ظ�Activate default bearer context accept*/
    NAS_ESM_EncodeActDefltEpsbCntxtAccMsg(stEncodeInfo, \
                                  NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                 &ulSndNwMsgLen);
    NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                               ulSndNwMsgLen, NAS_ESM_AIR_MSG_DIR_ENUM_UP,\
                               ESM_ACT_DEFLT_EPS_BEARER_CNTXT_ACP);

    /*�����ǰ���̴���ATTACH�����У���֪ͨEMM PDN Conn SUCC������֪ͨEMM Data Req*/
    if(NAS_ESM_PS_REGISTER_STATUS_ATTACHED != NAS_ESM_GetEmmStatus())
    {
        NAS_ESM_SndEsmEmmPdnConSuccReqMsg(ulSndNwMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
    }
    else
    {
        /* �����EHRPD���ػָ����̣�OPID����Ϊ��Ӧ��PDNʵ������ֵ������EMM�ظ�ʱ
        �ܹ��ҵ���Ӧ��PDNʵ�壬��EHRPD���ػָ�����ʱ��OPID����Ϊ��Чֵ */
        #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (NAS_ESM_SUCCESS == ulIsEhPdnHandover)
        {
            pstEhrpdEntity                                  = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

            /* ����һ��OPID����¼��EHRPD��PDNʵ���У���Ϣ����Ϊ����ȱʡ����ACP */
            pstEhrpdEntity->stNwMsgRecord.ulNwMsgOpId       = NAS_ESM_AllocEmmEsmOpId();
            pstEhrpdEntity->stNwMsgRecord.enEsmCnMsgType    = NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_ACC;

            NAS_ESM_SndEsmEmmDataReqMsg(pstEhrpdEntity->stNwMsgRecord.ulNwMsgOpId,
                                        PS_FALSE, ulSndNwMsgLen,
                                        NAS_ESM_GetCurEsmSndNwMsgAddr());
        }
        else
        #endif
        {
            NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID,
                                        PS_FALSE, ulSndNwMsgLen,
                                        NAS_ESM_GetCurEsmSndNwMsgAddr());
        }
    }

    /* ���֧��˫APN�����¼ע����� */
    if (NAS_ESM_OP_TRUE == NAS_ESM_AttachBearerReestEnable())
    {
        if (NAS_ESM_ATTACH_CID == pstStateAddr->ulCid)
        {
            NAS_ESM_SetAttachBearerId(stEncodeInfo.ulEpsbId);
        }
    }

    NAS_ESM_UpdateEsmSndNwMsgLen(ulSndNwMsgLen);

    /* ����PTI�ͻظ���Ϣ */
    ulRslt = NAS_ESM_SavePtiBuffItem(stEncodeInfo.ucPti,
                                     (VOS_UINT8)stEncodeInfo.ulEpsbId,
                                     ulSndNwMsgLen,
                                     NAS_ESM_GetCurEsmSndNwMsgAddr());
    if (ulRslt != NAS_ESM_SUCCESS)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_DefltBearActMsgAutoAccept:WARN:Save pti buffer item failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_DefltBearActMsgAutoAccept_ENUM, 1);
    }

    /*ת��״̬*/
    NAS_ESM_SetBearCntxtState(stEncodeInfo.ulEpsbId, NAS_ESM_BEARER_STATE_ACTIVE);
    if (NAS_ESM_BEARER_TYPE_EMERGENCY == pstStateAddr->enBearerCntxtType)
    {
        NAS_ESM_SetBearCntxtType(stEncodeInfo.ulEpsbId, NAS_ESM_BEARER_TYPE_EMERGENCY);
    }
    else
    {
        NAS_ESM_SetBearCntxtType(stEncodeInfo.ulEpsbId, NAS_ESM_BEARER_TYPE_DEFAULT);
    }
    NAS_ESM_SetBearCntxtLinkCid(stEncodeInfo.ulEpsbId,pstStateAddr->ulCid);

    /*��ǰPDN����������1��*/
    ulCurPdnNum = NAS_ESM_GetCurPdnNum()+1;

    /*���浱ǰPDN������*/
    NAS_ESM_SetCurPdnNum(ulCurPdnNum);

    /*�ؼ��¼��ϱ�*/
    NAS_ESM_SndKeyEventReportInd(NAS_ESM_EVENT_BEARER_SETUP(stEncodeInfo.ulEpsbId));

    /* L4A�ع�, ����BEARER_INFO_IND�͸�APP CNF����Ϣ˳�� */

    /*��EMM����ID_EMM_ESM_BEARER_STATUS_REQ*/
    NAS_ESM_SndEsmEmmBearerStatusReqMsg(EMM_ESM_BEARER_CNTXT_MOD_MUTUAL);

    /* ֪ͨERABM���ؼ���ŵ��ж��Ƿ���EHRPD���ػָ�����֮�� */

    NAS_ESM_PrintEpsbInfo(stEncodeInfo.ulEpsbId);

    /* L4A�ع�, ����BEARER_INFO_IND�͸�APP CNF����Ϣ˳��, �ͷ���Դ�����ڻظ�APP CNF֮�� */

    /* �����EHRPD���ػָ����̣��ڴ˽�֪ͨEHSM���ؼ��� */
    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if(NAS_ESM_SUCCESS == ulIsEhPdnHandover)
    {
        /* ��APP�ظ��ɹ���Ϣ, ����BEARER_INFO_IND�͸�APP CNF����Ϣ˳�� */
        NAS_ESM_SndEsmAppSdfSetupSuccMsg(ulStateTblIndex);

        /*�ͷ�״̬����Դ*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        pstEhrpdEntity                   = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

        /* ������L�³ɹ��ָ����������ĳ���ID */
        pstEhrpdEntity->ulHandoverEpsbId = stEncodeInfo.ulEpsbId;

        /* handover���̱�Ȼ����EHRPD���뼼����֪ͨEHSM���ؼ��֪ͨAPS���ػָ��ڼ���ȱʡ����ACP����ȥ�Ժ����ϱ� */
        NAS_ESM_SndEhsmSyncPdnInfoConnIndMsg(stEncodeInfo.ulEpsbId);

        /* ֪ͨERABM��������ڳ��س��׻ָ��ɹ�ʱ��֪ͨ */

        /* ��һ��EHRPD���ػָ����̣��յ�����ļ�������ʵ�����RECONNECTING̬ */
        if (PS_TRUE == pstEhrpdEntity->ucAttachPdnFlag)
        {
            NAS_ESM_SET_EHRPD_ENTITY_STATE(NAS_ESM_EHRPD_ENTITY_STATE_ALREADY_RCV_FIRST_BEARER_ACT_REQ);
        }

        NAS_ESM_INFO_LOG("NAS_ESM_DefltBearActMsgAutoAccept: handover PDN REQ.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_DefltBearActMsgAutoAccept_ENUM, ESM_HANDOVER_PDN_REQ);

        return;
    }

    /* �������EHRPD���뼼������Ҫ֪ͨEHSM���ؼ��� */
    if (NAS_ESM_SUCCESS == NAS_EMM_IsEhrpdOr1XRatExist())
    {
        NAS_ESM_SndEhsmSyncPdnInfoConnIndMsg(stEncodeInfo.ulEpsbId);
    }
    #endif

    /* ����EHRPD���ػָ����̣�ֱ����RABM����ID_ESM_ERABM_ACT_IND */
    NAS_ESM_SndEsmRabmActIndMsg(stEncodeInfo.ulEpsbId, ESM_ERABM_BEARER_RAT_LTE, PS_FALSE, ESM_ERABM_INVALID_BEARER_ID);

    /* ֪ͨSM���ؼ��� */
    NAS_ESM_SndSmEspBearerActIndMsg(stEncodeInfo.ulEpsbId);

    /* ��APP�ظ��ɹ���Ϣ, ����BEARER_INFO_IND�͸�APP CNF����Ϣ˳�� */
    NAS_ESM_SndEsmAppSdfSetupSuccMsg(ulStateTblIndex);

    /*�ͷ�״̬����Դ*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_DefltBearActMsgManualProc
 Description     : ȱʡ���ؼ����ֶ�����
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-12-3  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_DefltBearActMsgManualProc
(
    VOS_UINT32                          ulStateTblIndex,
    const NAS_ESM_NW_MSG_STRU          *pstDecodedNwMsg
)
{
    APP_ESM_PDP_MANAGER_IND_STRU        stPdpManInd;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_DefltBearActMsgManualProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_DefltBearActMsgManualProc_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /* ���ٿռ䣬���ڻ���������������Ϣ */
    pstStateAddr->pstDecodedNwMsg = (VOS_VOID *)NAS_ESM_MEM_ALLOC(sizeof(NAS_ESM_NW_MSG_STRU));

    if (VOS_NULL_PTR == pstStateAddr->pstDecodedNwMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_DefltBInactPPendMsgNwActDefltEpsbReq:ERROR:SM->APP,Memory Alloc FAIL!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_DefltBearActMsgManualProc_ENUM, LNAS_EMM_ALLOC_FAIL);

        /*�ͷ�״̬����Դ*/
        NAS_ESM_RelStateTblResource(ulStateTblIndex);

        return ;
    }

     /* ��������������Ϣ������������ */
    NAS_ESM_MEM_CPY_S(  pstStateAddr->pstDecodedNwMsg,
                        sizeof(NAS_ESM_NW_MSG_STRU),
                        pstDecodedNwMsg,
                        sizeof(NAS_ESM_NW_MSG_STRU));

    /* �����ʱ����stPdpManInd */
    NAS_ESM_MEM_SET_S(&stPdpManInd,
                     sizeof(APP_ESM_PDP_MANAGER_IND_STRU),
                     NAS_ESM_NULL,
                     sizeof(APP_ESM_PDP_MANAGER_IND_STRU));

    stPdpManInd.bitOpLinkCid = NAS_ESM_OP_FALSE;
    stPdpManInd.bitOpModifyTpye = NAS_ESM_OP_FALSE;

    /* ��дCID */
    stPdpManInd.ulCid = pstStateAddr->ulCid;

    /* ��дOpid, OriginalId��TerminalId*/
    if((NAS_ESM_OP_TRUE == pstStateAddr->bitOpAppMsgRecord)
        &&(ID_APP_ESM_PDP_SETUP_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType))
    {
        stPdpManInd.ulOpId = pstStateAddr->stAppMsgRecord.ulAppMsgOpId;
        stPdpManInd.usTerminalId = pstStateAddr->stAppMsgRecord.usOriginalId;
        stPdpManInd.usOriginalId = pstStateAddr->stAppMsgRecord.usTerminalId;
    }
    else
    {
        stPdpManInd.ulOpId = NAS_ESM_OPID_TYPE_MANAGER_IND;

        /* ���䱾�ι���APP_MSG_HEADER*/
        /* ��Ϊ��NAS_ESM_SndEsmAppPdpManageIndMsg�л�Ҫ����OriginalId��uTerminalId */
        /* �������ﴫ��Ĳ����Ƿ��� */
        NAS_ESM_AssignMidHeader(&stPdpManInd.usOriginalId,&stPdpManInd.usTerminalId);
    }

    /* ��д�������� */
    stPdpManInd.enOperateType = APP_ESM_BEARER_OPERATE_TYPE_DEF_ACT;

    /* ��APP����ID_APP_ESM_PDP_MANAGER_IND��Ϣ */
    NAS_ESM_SndEsmAppPdpManageIndMsg(&stPdpManInd);

    /* ������ʱ���ȴ�APP�ظ���Ϣ */
    NAS_ESM_TimerStart(ulStateTblIndex, TI_NAS_ESM_WAIT_APP_CNF);

    /* ���õȴ�App�ظ���־λ */
    pstStateAddr->ucIsWaitForUserAnswer = PS_TRUE;
}

/*****************************************************************************
 Function Name   : NAS_ESM_ActDefltBearFailProc
 Description     : ����ȱʡ����ʧ�ܴ���
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.lihong00150010      2009-12-4  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_ESM_ActDefltBearFailProc
(
    const NAS_ESM_ENCODE_INFO_STRU     *pstEncodeInfo,
    VOS_UINT32                          ulStateTblIndex
)
{
    VOS_UINT32                          ulSndNwMsgLen    = NAS_ESM_NULL;
    VOS_UINT32                          ulRslt           = NAS_ESM_NULL;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr     = VOS_NULL_PTR;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_ActDefltBearFailProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ActDefltBearFailProc_ENUM, LNAS_ENTRY);

    pstStateAddr = NAS_ESM_GetStateTblAddr(ulStateTblIndex);

    /*������ظ�Activate default bearer context reject*/
    NAS_ESM_EncodeActDefltEpsbCntxtRejMsg(*pstEncodeInfo, \
                                  NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                 &ulSndNwMsgLen);

    NAS_ESM_SndAirMsgReportInd(NAS_ESM_GetCurEsmSndNwMsgAddr(),\
                                   ulSndNwMsgLen, NAS_ESM_AIR_MSG_DIR_ENUM_UP,\
                                   ESM_ACT_DEFLT_EPS_BEARER_CNTXT_REJ);
    NAS_ESM_SndEsmEmmDataReqMsg(NAS_ESM_ILLEGAL_OPID, PS_FALSE, ulSndNwMsgLen, NAS_ESM_GetCurEsmSndNwMsgAddr());
    NAS_ESM_UpdateEsmSndNwMsgLen(ulSndNwMsgLen);

    /* ����PTI�ͻظ���Ϣ */
    ulRslt =  NAS_ESM_SavePtiBuffItem(pstEncodeInfo->ucPti,
                                      (VOS_UINT8)pstEncodeInfo->ulEpsbId,
                                      ulSndNwMsgLen,
                                      NAS_ESM_GetCurEsmSndNwMsgAddr());
    if (ulRslt != NAS_ESM_SUCCESS)
    {
        NAS_ESM_WARN_LOG("NAS_ESM_ActDefltBearFailProc:WARN:Save pti buffer item failed!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_ActDefltBearFailProc_ENUM, 1);
    }

    /*��APP�ظ���Ϣ*/
    if(ID_APP_ESM_PDP_SETUP_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType )
    {
        /*��APP����ID_APP_ESM_PDP_SETUP_CNF(ʧ��)��Ϣ*/
        NAS_ESM_SndEsmAppSdfSetupCnfFailMsg(ulStateTblIndex, \
                                      NAS_ESM_GetAppErrorByEsmCause(pstEncodeInfo->ucESMCau));
    }

    /*��APP�ظ���Ϣ*/
    if(ID_APP_ESM_NDISCONN_REQ == pstStateAddr->stAppMsgRecord.enAppMsgType )
    {
        /*��APP����ID_APP_ESM_NDISCONN_CNF(ʧ��)��Ϣ*/
        NAS_ESM_LOG1("NAS_ESM_ActDefltBearFailProc:ERROR =", NAS_ESM_GetAppErrorByEsmCause(pstEncodeInfo->ucESMCau));
        TLPS_PRINT2LAYER_INFO1(NAS_ESM_ActDefltBearFailProc_ENUM, LNAS_ERROR, NAS_ESM_GetAppErrorByEsmCause(pstEncodeInfo->ucESMCau));
        NAS_ESM_SndEsmAppNdisConnCnfFailMsg(ulStateTblIndex, \
                                      NAS_ESM_GetAppErrorByEsmCause(pstEncodeInfo->ucESMCau));
    }


   /*�ͷ�״̬����Դ*/
    NAS_ESM_RelStateTblResource(ulStateTblIndex);
}
/*lint +e961*/
/*lint +e960*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasEsmNwMsgPdnConProc.c */
