/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLcsLppMsgProc.c
    Description : ����LPP����LCS����Ϣ
    History     :
        1.lihong  00150010       2015-09-28  Draft Enact
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "vos.h"
#include    "PsLogdef.h"
#include    "PsTypeDef.h"
#include    "NasLcsLppMsgProc.h"
#include    "NasLcsPublic.h"
#include    "NasLcsEmmMsgProc.h"
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



#define    THIS_FILE_ID            PS_FILE_ID_NASLCSLPPMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLCSLPPMSGPROC_C

#if (FEATURE_LPP == FEATURE_ON)



/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
Function Name  : NAS_LCS_RcvLppGnssAssistDataReq
Description    : ����LPP_LCS_GNSS_ASSISTDATA_REQ��Ϣ
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-10-09  �¿���
*****************************************************************************/
VOS_VOID NAS_LCS_RcvLppGnssAssistDataReq
(
    const LPP_LCS_GNSS_ASSISTDATA_REQ_STRU     *pstGnssAssistDataReq
)
{
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enMolrDomain    = NAS_LCS_DOMAIN_TYPE_BUTT;
    VOS_UINT32                          ulIndex         = 0;
    NAS_LCS_LPP_MSG_RECORD_STRU        *pstLppMsgRecord = NAS_LCS_NULL_PTR;
    VOS_UINT8                           ucInvokeId      = 0;
    VOS_UINT8                           ucMoTi          = 0;

    /* ���LPP��Ϣ��������ֱ�ӻظ�ʧ�� */
    if (NAS_LCS_MAX_LPP_MSG_LEN < pstGnssAssistDataReq->ulLppMsgSize)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvLppGnssAssistDataReq:LPP msg too loog!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvLppGnssAssistDataReq_ENUM, LNAS_LCS_LppMsgTooLoog);
        NAS_LCS_SndLppGnssAssistDataCnf(LCS_LPP_RSLT_FAIL);
        return;
    }

    /* �������ѡ��EPC-LCS����ֱ�ӻظ�ʧ�� */
    enMolrDomain = NAS_LCS_SelectMolrDomain();
    NAS_LCS_SndOmDomainSelectInfo(enMolrDomain);
    if (NAS_LCS_DOMAIN_TYPE_EPC_LCS != enMolrDomain)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvLppGnssAssistDataReq:EPC-LCS not support!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvLppGnssAssistDataReq_ENUM, LNAS_LCS_SelectDomainFail);
        NAS_LCS_SndLppGnssAssistDataCnf(LCS_LPP_RSLT_FAIL);
        return ;
    }

    /* ����LPP������MO-LRʵ�壬�������ʧ�ܣ���ֱ�ӻظ�ʧ�� */
    if (NAS_LCS_FAIL == NAS_LCS_CreateLcsEntity(    NAS_LCS_START_SOURCE_LPP,
                                                    &ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvLppGnssAssistDataReq:create entity fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvLppGnssAssistDataReq_ENUM, LNAS_LCS_CreateEntityFail);
        NAS_LCS_SndLppGnssAssistDataCnf(LCS_LPP_RSLT_FAIL);
        NAS_LCS_SndOmEntityInfo();
        return ;
    }

    /* �洢LPP��Ϣ */
    pstLppMsgRecord = NAS_LCS_GetLppMolrRecord();
    pstLppMsgRecord->ulLppMsgSize = pstGnssAssistDataReq->ulLppMsgSize;
    NAS_LCS_MEM_CPY_S(    pstLppMsgRecord->aucLppMsg,
                          NAS_LCS_MAX_LPP_MSG_LEN,
                          pstGnssAssistDataReq->aucLppMsg,
                          pstGnssAssistDataReq->ulLppMsgSize);

    /* ��¼ʵ������ϢΪѡ����� */
    NAS_LCS_SetEntityLcsDomain(ulIndex, enMolrDomain);

    /* ����TI�����洢 */
    ucMoTi = NAS_LCS_CreateMoTi(ulIndex);
    NAS_LCS_SetEntityTi(ulIndex, ucMoTi);

    /* ����InvokeId,���洢 */
    ucInvokeId = NAS_LCS_CreateInvokeId();
    NAS_LCS_SetEntityInvokeId(ulIndex, ucInvokeId);

    /* �����ȴ�������Ӧ��ʱ�� */
    NAS_LCS_StartTimer(ulIndex, TI_NAS_LCS_WAIT_NW_RSP_TIMER);

    /* ��LMM���������� */
    NAS_LCS_SndLmmEstReq(ucMoTi);

    /* ����ʵ������״̬Ϊ���������� */
    NAS_LCS_SetEntityConnState(ulIndex, NAS_LCS_CONN_STATE_ESTING);
}

/*****************************************************************************
Function Name  : NAS_LCS_LppMsgDistr
Description    : LCSģ��LPP��Ϣ������
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-9-28  �¿���
*****************************************************************************/
VOS_VOID NAS_LCS_LppMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pLppMsg  = VOS_NULL_PTR;

    pLppMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    NAS_LCS_INFO_LOG("NAS_LCS_LppMsgDistr is entered!");
    TLPS_PRINT2LAYER_INFO1(NAS_LCS_LppMsgDistr_ENUM, LNAS_ENTRY, pLppMsg->ulMsgName);

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch(pLppMsg->ulMsgName)
    {
        case ID_LPP_LCS_GNSS_ASSISTDATA_REQ:
            NAS_LCS_RcvLppGnssAssistDataReq((LPP_LCS_GNSS_ASSISTDATA_REQ_STRU *)pRcvMsg);
            break;

        default:
            NAS_LCS_WARN_LOG("NAS_LCS_LppMsgDistr:NORM: Error MsgId!");
            TLPS_PRINT2LAYER_ERROR(NAS_LCS_LppMsgDistr_ENUM, LNAS_LCS_InvalidRsvMsgId);
            break;
    }

    return;
}

/*****************************************************************************
Function Name  : NAS_LCS_SndLppGnssAssistDataCnf
Description    : ��LPP����LCS_LPP_GNSS_ASSISTDATA_CNF
Input          : enRslt--------------���
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-10-09  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_SndLppGnssAssistDataCnf
(
    LCS_LPP_RSLT_ENUM_UINT32            enRslt
)
{
    LCS_LPP_GNSS_ASSISTDATA_CNF_STRU   *pstLppGnssAssistDataCnf = NAS_LCS_NULL_PTR;

    NAS_LCS_INFO_LOG("NAS_LCS_SndLppGnssAssistDataCnf is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LCS_SndLppGnssAssistDataCnf_ENUM, LNAS_ENTRY);

    pstLppGnssAssistDataCnf   = (VOS_VOID *)NAS_LCS_ALLOC_MSG(sizeof(LCS_LPP_GNSS_ASSISTDATA_CNF_STRU));
    if (NAS_LCS_NULL_PTR == pstLppGnssAssistDataCnf)
    {
        return;
    }

    NAS_LCS_WRITE_LPP_MSG_HEAD( pstLppGnssAssistDataCnf,
                                (sizeof(LCS_LPP_GNSS_ASSISTDATA_CNF_STRU)-
                                NAS_LCS_LEN_VOS_MSG_HEADER));

    pstLppGnssAssistDataCnf->ulMsgId    = ID_LCS_LPP_GNSS_ASSISTDATA_CNF;
    pstLppGnssAssistDataCnf->enRslt     = enRslt;

    NAS_LCS_SND_MSG(pstLppGnssAssistDataCnf);
}

/*****************************************************************************
Function Name  : NAS_LCS_SndLppLocationInfoNtf
Description    : ��LPP����LCS_LPP_LOCATION_INFO_NTF
Input          : pstLocationEstimate---------����λ����Ϣָ��
                 pstVelocityEstimate---------�ٶ���Ϣָ��
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-10-17  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_SndLppLocationInfoNtf
(
    LOC_COM_COORDINATE_STRU            *pstLocationEstimate,
    LOC_COM_VELOCITY_STRU              *pstVelocityEstimate
)
{
    LCS_LPP_LOCATION_INFO_NTF_STRU     *pstLppLocationInfoNtf = NAS_LCS_NULL_PTR;

    NAS_LCS_INFO_LOG("NAS_LCS_SndLppLocationInfoNtf is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LCS_SndLppLocationInfoNtf_ENUM, LNAS_ENTRY);

    pstLppLocationInfoNtf   = (VOS_VOID *)NAS_LCS_ALLOC_MSG(sizeof(LCS_LPP_LOCATION_INFO_NTF_STRU));
    if (NAS_LCS_NULL_PTR == pstLppLocationInfoNtf)
    {
        return;
    }

    NAS_LCS_WRITE_LPP_MSG_HEAD( pstLppLocationInfoNtf,
                                (sizeof(LCS_LPP_LOCATION_INFO_NTF_STRU)-
                                NAS_LCS_LEN_VOS_MSG_HEADER));

    pstLppLocationInfoNtf->ulMsgId    = ID_LCS_LPP_LOCATION_INFO_NTF;
    if (NAS_LCS_NULL_PTR != pstLocationEstimate)
    {
        pstLppLocationInfoNtf->bitOpLocationEstimate = NAS_LCS_OP_TRUE;

        NAS_LCS_MEM_CPY_S(  &pstLppLocationInfoNtf->stLocationEstimate,
                            sizeof(LOC_COM_COORDINATE_STRU),
                            pstLocationEstimate,
                            sizeof(LOC_COM_COORDINATE_STRU));

    }
    else
    {
        pstLppLocationInfoNtf->bitOpLocationEstimate = NAS_LCS_OP_FALSE;
    }

    if (NAS_LCS_NULL_PTR != pstVelocityEstimate)
    {
        pstLppLocationInfoNtf->bitOpVelocityEstimate = NAS_LCS_OP_TRUE;

        NAS_LCS_MEM_CPY_S(  &pstLppLocationInfoNtf->stVelocityEstimate,
                            sizeof(LOC_COM_VELOCITY_STRU),
                            pstVelocityEstimate,
                            sizeof(LOC_COM_VELOCITY_STRU));
    }
    else
    {
        pstLppLocationInfoNtf->bitOpVelocityEstimate = NAS_LCS_OP_FALSE;
    }

    NAS_LCS_SND_MSG(pstLppLocationInfoNtf);
}


#endif
#ifdef __cplusplus
#if __cplusplus
    }
    #endif
#endif
/* end of NasLcsLppMsgProc.c */
