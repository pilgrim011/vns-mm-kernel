/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLppMtaMsgProc.c
    Description : ����EMM����SM����Ϣ
    History     :
    1. lifuxin 00253982 2015-7-7 �¿���
******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/

#include    "PsTypeDef.h"
#include    "NasLppMtaMsgProc.h"
#include    "LppMtaInterface.h"
#include    "NasLppPublic.h"
#include    "OmCommon.h"
#include    "NasLppOm.h"
#include    "NasLppEncode.h"
#include    "NasLppLrrcMsgProc.h"
#include    "NasLppSendMsg.h"
#include    "NasLppEmmMsgProc.h"
#include    "NasLppIntraMsgProc.h"
#include    "LcsLppInterface.h"

#define    THIS_FILE_ID            PS_FILE_ID_NASLPPMTAMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPMTAMSGPROC_C

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
#if (FEATURE_LPP == FEATURE_ON)



/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : NAS_LPP_GetOneRunningTransWaitGnssCapCnf
 Description    : �õ�һ��transaction����running �ȴ�GNSS�����ظ�
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
    1. lifuxin 00253982 2015-10-24 �¿���
*****************************************************************************/
 VOS_BOOL   NAS_LPP_GetOneRunningTransWaitGnssCapCnf( VOS_UINT8  *pucTransIndx)
 {
    VOS_UINT8                                  ucLoop              = 0;
    NAS_LPP_TRANSACTION_ENTITY_POOL_STRU       *psTransEntityPool   = NAS_LPP_NULL_PTR;

    psTransEntityPool = NAS_LPP_GetLppTransEntityPool();

    for(ucLoop = 0; ucLoop < NAS_LPP_MAX_TRANS_POOL_COUNT; ucLoop++)
    {
        /*lint -e701*/
        if(0 != ( psTransEntityPool->ulTransBitmap & (0x01<<ucLoop) ) )
        /*lint +e701*/
        {
            if((LPP_MS_CAPABILITY == psTransEntityPool->astTransElementEntity[ucLoop].enLppMainState)
               && (LPP_SS_CAP_REQ_WAIT_CNF == psTransEntityPool->astTransElementEntity[ucLoop].enLppSubState))
            {
                *pucTransIndx  = ucLoop;
                return PS_TRUE;
            }
        }
    }

    return PS_FALSE;
 }

/*****************************************************************************
 Function Name  : NAS_LPP_GetSessionIndxAndSesssionTransIndxByTransIndx
 Description    : ͨ��transactionIndx�ҵ���Ӧ��sessionIndx�Լ�SessionTransaIndx
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
    1. lifuxin 00253982 2015-10-24 �¿���
*****************************************************************************/
VOS_VOID   NAS_LPP_GetSessionIndxAndSesssionTransIndxByTransIndx
(
    VOS_UINT8                           ucTransIndx,
    VOS_UINT8                          *pucSessionIndx,
    VOS_UINT8                          *pucSessionTransIndx
)
{
    VOS_UINT8                                   ucLoopSession       = 0;
    VOS_UINT8                                   ucLoopTrans         = 0;
    NAS_LPP_SESSION_ENTITY_POOL_STRU           *pstSessionEntityPool= NAS_LPP_NULL_PTR;


    *pucSessionIndx         = PS_NULL_UINT8;
    *pucSessionTransIndx    = PS_NULL_UINT8;

    pstSessionEntityPool = NAS_LPP_GetLppSessionEntityPool();

    for(ucLoopSession = 0; ucLoopSession < NAS_LPP_MAX_SESSION_COUNT; ucLoopSession++)
    {
    /*lint -e701*/
        if(0 != ( (pstSessionEntityPool->ulSessionActiveBitmap) & (0x01 <<  ucLoopSession) ) )
    /*lint +e701*/
        {
            for(ucLoopTrans = 0; ucLoopTrans < NAS_LPP_MAX_TRANS_COUNT; ucLoopTrans++)
            {
                if(ucTransIndx == pstSessionEntityPool->astLppSessionEntity[ucLoopSession].stLppTrans.aucTransElementIdx[ucLoopTrans])
                {
                    *pucSessionIndx         = ucLoopSession;
                    *pucSessionTransIndx    = ucLoopTrans;
                     return;
                }
            }
        }
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_RcvMtaLppGnssCapCnf
 Description    : LPPģ��Mta��Ϣ������
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
    1. wangensheng 00324863 2015-10-19 �¿���
*****************************************************************************/
 VOS_VOID   NAS_LPP_RcvMtaLppGnssCapCnf
 (
    MTA_LPP_GNSS_PROVIDE_CAPABITY_CNF_STRU                *pstMtaLppGnssProvideCap
 )
 {
    VOS_UINT8                                   ucSessionIndx       = 0;
    VOS_UINT8                                   ucTransIndx         = 0;
    VOS_UINT8                                   ucSessionTransIndx  = 0;
    VOS_BOOL                                    bHaveWaitGnssCapTrans = PS_FALSE;
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransEntity      = NAS_LPP_NULL_PTR;
    NAS_LPP_ENTITY_STRU                        *pstLppEntity        = NAS_LPP_NULL_PTR;
    NAS_LPP_MSG_HEAD_STRU                       stLppMsgHead        = {0};
    VOS_UINT32                                  ulSessionId         = 0;
    VOS_UINT8                                   ucRslt              = 0;
    NAS_LPP_TRANS_ID_STRU                       stTransId          = {0};

    NAS_LPP_NORM_LOG("NAS_LPP_RcvMtaLppGnssCapCnf is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvMtaLppGnssCapCnf_ENUM, LNAS_RCV_MTA_GNSS_CAP_CNF);

    /* TODO:MEM */
    /* �����յ������ݴ洢��LPP ENTITY�� */
    pstLppEntity = NAS_LPP_GetLppEntityCtx();
    NAS_LPP_MEM_CPY_S(  &pstLppEntity->stStructDataForGnss.stMtaLppGnssCap,
                        sizeof(MTA_LPP_AGNSS_PROVIDE_CAP_STRU),
                        &pstMtaLppGnssProvideCap->stGnssProvideCap,
                        sizeof(MTA_LPP_AGNSS_PROVIDE_CAP_STRU));
    pstLppEntity->stStructDataForGnss.bGnssCapbilityFlag = PS_TRUE;

    bHaveWaitGnssCapTrans = NAS_LPP_GetOneRunningTransWaitGnssCapCnf(&ucTransIndx);
    if(PS_TRUE == bHaveWaitGnssCapTrans)
    {
        /*���������֧��ʾ��ǰ��һ��transaction���ڵȴ�GNSS�������ظ�, ��ʼ��֯provide������Ϣ*/
        NAS_LPP_GetSessionIndxAndSesssionTransIndxByTransIndx(ucTransIndx,
                                                              &ucSessionIndx,
                                                              &ucSessionTransIndx);
        if((PS_NULL_UINT8 != ucSessionIndx) && (PS_NULL_UINT8 != ucSessionTransIndx))
        {
            stLppMsgHead.stTransactionId.enInitiator =
                pstLppEntity->stTransEntityPool.astTransElementEntity[ucTransIndx].stTransId.enInitiator;
            stLppMsgHead.stTransactionId.ucTransactionNumber =
                pstLppEntity->stTransEntityPool.astTransElementEntity[ucTransIndx].stTransId.ucTransactionNumber;
            ulSessionId = pstLppEntity->stSessionEntityPool.astLppSessionEntity[ucSessionIndx].ulSessionId;

            /*�ظ�ProvideCapbility��Ϣ*/
            ucRslt = NAS_LPP_SndUplinkProvideCapbilityMsg(&stLppMsgHead, ulSessionId,ucTransIndx);
            if(NAS_LPP_SUCCESS != ucRslt)
            {
                stTransId.enInitiator = stLppMsgHead.stTransactionId.enInitiator;
                stTransId.ucTransactionNumber = stLppMsgHead.stTransactionId.ucTransactionNumber;
                NAS_LPP_ReleaseTransactionOrSession(ucSessionIndx,
                                                    ucSessionTransIndx,
                                                    &stTransId);
                return;
            }

            pstTransEntity = &(NAS_LPP_GetLppTransEntityPool()->astTransElementEntity[ucTransIndx]);

            /*��ʾ��ǰtransaction����յ�������ACK֮�󣬾Ϳ��Խ�����*/
            pstTransEntity->ucTransEndFlag   = PS_TRUE;

            /*��¼��ǰ���͵Ŀտ���Ϣ�������յ���������Ϣ֮�����ת��ʲô״̬*/
            pstTransEntity->enLastUpMsgId    = NAS_LPP_AIR_MSG_PROVIDE_CAP;

            /*ת״̬,ת��������������״̬���ڲ���data cnf��Ҳ����ȷ�ϰѿտ���Ϣ���͵��˻�վ, ͬʱ�����ȴ���Ӧ�Ķ�ʱ��*/
            NAS_LPP_ChangeTransFsmState(ucSessionIndx,
                                        ucSessionTransIndx,
                                        LPP_MS_CAPABILITY,
                                        LPP_SS_WAIT_INTRA_DATA_CNF);
        }
    }
    else
    {
        /*��ʾ��ǰû��GNSS����������Ϊ������������GNSS�����Ļظ�*/
        /* ֹͣ��ʱ�� */
        NAS_LPP_TimerStop(NAS_LPP_TIMER_INVAILD_PARA,
                          NAS_LPP_TIMER_INVAILD_PARA,
                          TI_NAS_LPP_WAIT_GNSS_CAP_CNF);
    }
 }

/*****************************************************************************
Function Name  : NAS_LPP_ResetGnssMeasRslt
Description    : ��յ�ǰGNSS�Ĳ�����Ϣ
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-10-20 �¿���
*****************************************************************************/
VOS_VOID   NAS_LPP_ResetGnssMeasRslt
(
    NAS_LPP_GNSS_MEAS_RESLT_STRU           *pstGnssMeasRslt
)
{
    VOS_UINT32                  ulLoop = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_ResetGnssMeasRslt is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_ResetGnssMeasRslt_ENUM, LNAS_LPP_Func_Enter);

    /*û������GNSS�Ĳ���ind*/
    if(pstGnssMeasRslt->bHaveGnssMeasFlag == PS_FALSE)
    {
        NAS_LPP_MEM_SET_S(pstGnssMeasRslt,sizeof(NAS_LPP_GNSS_MEAS_RESLT_STRU), 0, sizeof(NAS_LPP_GNSS_MEAS_RESLT_STRU));
        for(ulLoop = 0; ulLoop < LPP_MAX_VALID_GNSS_POSITION_TECH; ulLoop++)
        {
            pstGnssMeasRslt->stGnssReqLocationInfo.stGNSSsignalMeasInfo.stGNSSMeasList.pastGNSSMeasListArray[ulLoop] = NAS_LPP_NULL_PTR;
        }

        return;
    }

    /*�Ѿ�����GNSS�Ĳ���ind*/
    /*ѭ���ͷŵ��ڴ���MTA����ģ��ڴ洢���ص�GNSS�Ĳ�����Ϣ��ʱ����������ڴ�, free��ʱ��:
      1. �����µ�GNSS meas ind����ʱ����Ҫ�ͷ�
      2. ��transaction��session�ͷŵ�ʱ����Ҫ�ͷ�
    */
    if (LPP_MAX_VALID_GNSS_POSITION_TECH <= pstGnssMeasRslt->stGnssReqLocationInfo.stGNSSsignalMeasInfo.stGNSSMeasList.ulGNSSMeasListCnt)
    {
        pstGnssMeasRslt->stGnssReqLocationInfo.stGNSSsignalMeasInfo.stGNSSMeasList.ulGNSSMeasListCnt = LPP_MAX_VALID_GNSS_POSITION_TECH;
    }

    for(ulLoop = 0; ulLoop < pstGnssMeasRslt->stGnssReqLocationInfo.stGNSSsignalMeasInfo.stGNSSMeasList.ulGNSSMeasListCnt; ulLoop++)
    {
        NAS_LPP_MEM_FREE(pstGnssMeasRslt->stGnssReqLocationInfo.stGNSSsignalMeasInfo.stGNSSMeasList.pastGNSSMeasListArray[ulLoop]);
    }
    NAS_LPP_MEM_SET_S(pstGnssMeasRslt,sizeof(NAS_LPP_GNSS_MEAS_RESLT_STRU), 0, sizeof(NAS_LPP_GNSS_MEAS_RESLT_STRU));

    return;
}
/*****************************************************************************
Function Name  : NAS_LPP_RcvMtaLppGnssLocInfoInd
Description    : LPPģ��Mta��Ϣ������λ�ò���IND��Ϣ
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. wangensheng 00324863 2015-10-20 �¿���
*****************************************************************************/
VOS_VOID NAS_LPP_SndRrcMtaGnssLocInfo
(
     MTA_LPP_GNSS_RROVIDE_LOCATION_INFO_IND_STRU          *pstMtaLppGnssProvideLocInfoInd
)
{

    MTA_LPP_MEAS_REF_TIME_STRU             *pstMtaLppMeasRefTime    = NAS_LPP_NULL_PTR;
    LOC_COM_VELOCITY_STRU                  *pstVelocityEstimate     = NAS_LPP_NULL_PTR;
    LOC_COM_COORDINATE_STRU                *pstLocationEstimate     = NAS_LPP_NULL_PTR;
    LPP_LRRC_INFO_FLAG_ENUM_UINT8           ucGnssDataFlag          = LPP_LRRC_INFO_FLAG_VALID;

    /* ֹͣλ����ϢʧЧ��ʱ�� */
    NAS_LPP_TimerStop(NAS_LPP_TIMER_INVAILD_PARA,
                      NAS_LPP_TIMER_INVAILD_PARA,
                      TI_NAS_LPP_LOCATION_INVALID);

    /* ����RRC��λ����Ϣ��֯���� */
    if (NAS_LPP_SLCT == pstMtaLppGnssProvideLocInfoInd->bitCommonInfo)
    {
        if ( NAS_LPP_SLCT == pstMtaLppGnssProvideLocInfoInd->stCommonProvideLocInfo.bitOpLocationEstimate)
        {
            pstLocationEstimate = &pstMtaLppGnssProvideLocInfoInd->stCommonProvideLocInfo.stLocationEstimate;
        }

        if ( NAS_LPP_SLCT == pstMtaLppGnssProvideLocInfoInd->stCommonProvideLocInfo.bitOpVelocityEstimate)
        {
            pstVelocityEstimate= &pstMtaLppGnssProvideLocInfoInd->stCommonProvideLocInfo.stVelocityEstimate;
        }
    }

    if (NAS_LPP_SLCT == pstMtaLppGnssProvideLocInfoInd->bitAgnssInfo)
    {
        if ( NAS_LPP_SLCT == pstMtaLppGnssProvideLocInfoInd->stGnssReqLocationInfo.bitOpGNSSLocationInfo)
        {
            pstMtaLppMeasRefTime = &pstMtaLppGnssProvideLocInfoInd->stGnssReqLocationInfo.stGNSSLocationInfo.stMeasRefTime;
        }
    }

    NAS_LPP_SndLppLrrcLocationInfo(pstMtaLppMeasRefTime, pstVelocityEstimate, pstLocationEstimate, ucGnssDataFlag);
    /* ���� GNSS LOC INFO ��ʱ�� */
    NAS_LPP_TimerStart(NAS_LPP_TIMER_INVAILD_PARA,
                       NAS_LPP_TIMER_INVAILD_PARA,
                       TI_NAS_LPP_LOCATION_INVALID);
}

/*****************************************************************************
Function Name  : NAS_LPP_RcvMtaLppGnssLocInfoInd
Description    : LPPģ��Mta��Ϣ������λ�ò���IND��Ϣ
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-10-20 �¿���
*****************************************************************************/
VOS_VOID   NAS_LPP_RcvMtaLppGnssLocInfoInd
(
    MTA_LPP_GNSS_RROVIDE_LOCATION_INFO_IND_STRU          *pstMtaLppGnssProvideLocInfoInd
)
{
    NAS_LPP_GNSS_MEAS_RESLT_STRU           *pstGnssMeasRslt         = NAS_LPP_NULL_PTR;
    NAS_LPP_LOC_TECH_MAP_STRU              *pstLocTechMap           = NAS_LPP_NULL_PTR;
    VOS_UINT8                               ucCfgTableIndex         = PS_NULL_UINT8;
    NAS_LPP_COMM_CONFIG_INFO_STRU          *pstCommCfgInfo          = NAS_LPP_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_RcvMtaLppGnssLocInfoInd is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvMtaLppGnssLocInfoInd_ENUM, LNAS_LPP_Func_Enter);

    /*��ȡ�洢�Ĳ�������ĵ�ַ*/
    pstGnssMeasRslt = NAS_LPP_GetGnssMeasRsltAddr();

    /*��ղ������*/
    NAS_LPP_ResetGnssMeasRslt(pstGnssMeasRslt);

    /*����GNSS ����IND��Ϣ��ȫ�ֽṹ*/
    pstGnssMeasRslt->bHaveGnssMeasFlag = PS_TRUE;
    pstGnssMeasRslt->bitCommonInfo  = pstMtaLppGnssProvideLocInfoInd->bitCommonInfo;
    pstGnssMeasRslt->bitAgnssInfo   = pstMtaLppGnssProvideLocInfoInd->bitAgnssInfo;
    if(NAS_LPP_SLCT == pstGnssMeasRslt->bitCommonInfo)
    {
        NAS_LPP_MEM_CPY_S(&(pstGnssMeasRslt->stCommonProvideLocInfo),
                        sizeof(MTA_LPP_COMMON_IES_PROVIDE_LOCATION_INFO_STRU),
                        &(pstMtaLppGnssProvideLocInfoInd->stCommonProvideLocInfo),
                        sizeof(MTA_LPP_COMMON_IES_PROVIDE_LOCATION_INFO_STRU));
    }

    if(NAS_LPP_SLCT == pstGnssMeasRslt->bitAgnssInfo)
    {
        NAS_LPP_MEM_CPY_S(&(pstGnssMeasRslt->stGnssReqLocationInfo),
                        sizeof(MTA_LPP_AGNSS_PROVIDE_LOCATION_INFO_STRU),
                        &(pstMtaLppGnssProvideLocInfoInd->stGnssReqLocationInfo),
                        sizeof(MTA_LPP_AGNSS_PROVIDE_LOCATION_INFO_STRU));
    }

    /* ���͸�RRC MTA��λ����Ϣ */
    NAS_LPP_SndRrcMtaGnssLocInfo(pstMtaLppGnssProvideLocInfoInd);

    /*������ϱ�һ�εĳ��������ҵ�ǰtransactionֻ��һ�ֶ�λ��������
    ���ֶ�λ����������GNSS֮�����������ֵ�Ѿ����ˣ�����Ҫ�����ϱ�λ����Ϣ*/
    /*��ȡrunning��*/
    pstLocTechMap = NAS_LPP_SearchRunningPositionTech(NAS_LPP_POSITION_TECH_GNSS);
    if(NAS_LPP_NULL_PTR == pstLocTechMap)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_RcvMtaLppGnssLocInfoInd: Can't find the running table of GNSS");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvMtaLppGnssLocInfoInd_ENUM, LNAS_LPP_CannotFindGnssRunningTable);

        return;
    }

    /*��ȡ�������ó�*/
    ucCfgTableIndex = NAS_LPP_GetLppEntityCtx()->stTransEntityPool.astTransElementEntity[pstLocTechMap->ucTransIndx].ucCommCfgIndex;
    pstCommCfgInfo = NAS_LPP_GetCommCfgInfoElementByIndex(ucCfgTableIndex);
    if(NAS_LPP_NULL_PTR == pstCommCfgInfo)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_RcvMtaLppGnssLocInfoInd: Can't find the Comm Cfg Pool");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvMtaLppGnssLocInfoInd_ENUM, LNAS_LPP_CannotFindCommCfgPool);
        return;
    }

    /*����GNSS�Ķ�λ�����������ϱ���ʽ�� һ��once�� һ���������ϱ����ϱ�once����
    ���������������ط���Ҫ�ϱ�λ�ò�����Ϣ�� һ��ֻ��һ�ֶ�λ����������һ����
    �ж��ֶ�λ������ͬһ��transaction�ĳ��������������Ϣ����������Ҫ�ϱ��� ����
    �������ϱ��ĳ��������������ϱ���ͬһ�ȴ������Զ�ʱ����ʱ��ʱ����
    */
    if(NAS_LPP_REPORT_LOCATION_TYPE_ONCE == pstCommCfgInfo->stReportCriteria.enType)
    {
        NAS_LPP_ReportOnceProcess(pstLocTechMap->ucSessionIndx,
                                  pstLocTechMap->ucSessionTranIndx,
                                  pstLocTechMap->ucTransIndx);
    }

    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_GetOneSessionIndx
Description    : �ҵ�һ������running��session������sessionIndx
Input          :
Output         : VOS_VOID
Return Value   : sessionIndx

History        :
1. lifuxin 00253982 2015-10-20 �¿���
*****************************************************************************/
VOS_UINT8   NAS_LPP_GetOneRunningSessionIndx( VOS_VOID )
{
    VOS_UINT8                   ucLoop      = 0;
    NAS_LPP_ENTITY_STRU        *pstLppCtx   = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_GetOneRunningSessionIndx is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_GetOneRunningSessionIndx_ENUM, LNAS_LPP_Func_Enter);

    pstLppCtx = NAS_LPP_GetLppEntityCtx();
    for(ucLoop = 0; ucLoop < NAS_LPP_MAX_SESSION_COUNT; ucLoop++)
    {
        /*lint -e701*/
        if((0 != ((pstLppCtx->stSessionEntityPool.ulSessionActiveBitmap) & (0x01<<ucLoop)))
        /*lint +e701*/
         &&(NAS_LPP_MAX_TRANS_COUNT >= pstLppCtx->stSessionEntityPool.astLppSessionEntity[0].stLppTrans.ucTransIdCount))
        {
            return ucLoop;
        }
    }

    return PS_NULL_UINT8;
}

/*****************************************************************************
Function Name  : NAS_LPP_SndLcsGnssAssistDataReq
Description    : ����GNSS�������ݵ�������LCS
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-10-22 �¿���
*****************************************************************************/
VOS_VOID   NAS_LPP_SndLcsGnssAssistDataReq
(
    VOS_UINT8                                  *pucEncodeOutMsg,
    VOS_UINT32                                  ulLppMsgLen
)
{
    VOS_UINT32                          ulTmpLength     = 0;
    LPP_LCS_GNSS_ASSISTDATA_REQ_STRU   *pstLcsAssistDataReq   = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_SndLcsGnssAssistDataReq enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_SndLcsGnssAssistDataReq_ENUM, LNAS_LPP_Func_Enter);

    /*���ݿտ���Ϣ�ĳ��ȷ���ռ�*/
    if( 0 == ulLppMsgLen)
    {
        NAS_LPP_WARN_LOG("NAS_LPP_SndLcsGnssAssistDataReq: WARNING: Msg Length is zero");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SndLcsGnssAssistDataReq_ENUM, LNAS_LPP_MallocMemFail);
        return ;
    }
    else if(ulLppMsgLen > NAS_LPP_MIN_SND_MSG_LEN)
    {
        ulTmpLength = ulLppMsgLen - NAS_LPP_MIN_SND_MSG_LEN ;
        pstLcsAssistDataReq = (VOS_VOID*)NAS_LPP_ALLOC_MSG(sizeof(LPP_LCS_GNSS_ASSISTDATA_REQ_STRU) + ulTmpLength);
    }
    else/*�������С��NAS_LPP_MIN_SND_MSG_LEN������Ŀռ����NAS_LPP_MIN_SND_MSG_LEN*/
    {
        pstLcsAssistDataReq = (VOS_VOID*)NAS_LPP_ALLOC_MSG(sizeof(LPP_LCS_GNSS_ASSISTDATA_REQ_STRU));
    }

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstLcsAssistDataReq)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_LPP_ERR_LOG("NAS_LPP_SndLcsGnssAssistDataReq:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_SndLcsGnssAssistDataReq_ENUM, LNAS_LPP_MallocMemFail);
        return ;
    }

    /*��д�տ���Ϣͷ����*/
    pstLcsAssistDataReq->ulLppMsgSize = ulLppMsgLen;

    /*���տ���Ϣ��ŵ�ID_LPP_LCS_GNSS_ASSISTDATA_REQ�ṹ��*/
    /*lint -e669*/
    NAS_LPP_MEM_CPY_S(pstLcsAssistDataReq->aucLppMsg,ulLppMsgLen, pucEncodeOutMsg, ulLppMsgLen);
    /*lint +e669*/

    /*��д��Ϣͷ*/
    NAS_LPP_WRITE_LCS_MSG_HEAD(pstLcsAssistDataReq, ID_LPP_LCS_GNSS_ASSISTDATA_REQ);

    /*������Ϣ���ͺ��� */
    NAS_LPP_SND_MSG(pstLcsAssistDataReq);
}

/*****************************************************************************
Function Name  : NAS_LPP_EncodeGnssAssistReq
Description    : �����������ݵ�����
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-10-22 �¿���
*****************************************************************************/
VOS_UINT32   NAS_LPP_EncodeGnssAssistDataReq
(
    MTA_LPP_GNSS_ASSIST_DATA_REQ_STRU          *pstMtaLppGnssAssistDataReq,
    VOS_UINT8                                  *pucEncodeOutMsg,
    VOS_UINT32                                 *pulLppMsglen
)
{
    LPP_MESSAGE_STRU                       *pstReqAssistData        = NAS_LPP_NULL_PTR;
    LPP_REQUEST_ASSIST_DATA_R9_IES_STRU    *pstRequestAsisstDataR9  = NAS_LPP_NULL_PTR;
    NAS_LPP_SERVING_CELL_STRU              *pstServingCell          = NAS_LPP_NULL_PTR;
    VOS_UINT16                              usRslt                  = 0;
    VOS_UINT16                              usBitPos                = 0;
    VOS_UINT32                              ulLppMsgLen             = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_EncodeGnssAssistDataReq is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_EncodeGnssAssistDataReq_ENUM, LNAS_LPP_Func_Enter);

    /*��ȡLPP MSG BUFF*/
    pstReqAssistData = NAS_LPP_GetLppMsgBuff();
    NAS_LPP_MEM_SET_S(pstReqAssistData,sizeof(LPP_MESSAGE_STRU), 0, sizeof(LPP_MESSAGE_STRU));

    pstServingCell = NAS_LPP_GetServingCell();
    pstReqAssistData->bitOpLppTransactionId = NAS_LPP_NO_SLCT;
    pstReqAssistData->bitOpSequenceNumber   = NAS_LPP_SLCT;
    pstReqAssistData->bitOpLppMessageBody   = NAS_LPP_SLCT;
    pstReqAssistData->bitOpAcknowledgement  = NAS_LPP_SLCT;

    pstReqAssistData->stAcknowledgement.bAckRequested = VOS_FALSE;

    pstReqAssistData->bEndTransaction = VOS_FALSE;

    pstReqAssistData->stSequenceNumber.ucSequenceNumber = NAS_LPP_GetUpMsgSequenceNum();

    pstReqAssistData->stLppMessageBody.ulChoice = LPP_C1_MESSAGE_BODY_CHOSEN;
    pstReqAssistData->stLppMessageBody.u.stC1.ulChoice = LPP_SUPPORT_MESSAGE_BODY_PEQUEST_ASSISTANCE_DATA_CHOSEN;
    pstReqAssistData->stLppMessageBody.u.stC1.u.stRequestAssistanceData.ulChoice = LPP_C1_CRITI_EXT_REQUEST_ASSIST_DATA_CHOSEN;
    pstReqAssistData->stLppMessageBody.u.stC1.u.stRequestAssistanceData.u.stC1.ulChoice = LPP_C1_CRITI_EXT_REQUEST_ASSIST_DATA_R9_CHOSEN;
    pstRequestAsisstDataR9 = &pstReqAssistData->stLppMessageBody.u.stC1.u.stRequestAssistanceData.u.stC1.u.stRequestAssitDataR9;

    pstRequestAsisstDataR9->bitOpCommonIEsRequestAssitData = NAS_LPP_SLCT;
    pstRequestAsisstDataR9->stCommonIEsRequestAssistanceData.bitOpPrimaryCellID = NAS_LPP_SLCT;
    pstRequestAsisstDataR9->stCommonIEsRequestAssistanceData.stPrimaryCellID.ulCellIdentity = pstServingCell->ulCellIdentity;
    NAS_LPP_NasPlmn2LppPlmn(pstServingCell->aucPlmnId,
                         &pstRequestAsisstDataR9->stCommonIEsRequestAssistanceData.stPrimaryCellID.stPlmnIdentity);

     NAS_LPP_PreGnssAssistDataParameter(pstMtaLppGnssAssistDataReq, pstRequestAsisstDataR9);

    /*��ʼ����*/
    usRslt = NAS_LPP_EncodeMessage(pstReqAssistData,
                                   &usBitPos,
                                   pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
         NAS_LPP_ERR_LOG(" Encode assist data msg Fail!");
         TLPS_PRINT2LAYER_ERROR(NAS_LPP_EncodeGnssAssistDataReq_ENUM, LNAS_LPP_ENCODE_LPP_MSG_FAIL);
         return NAS_LPP_FAILURE;
    }

    /*HIDS air msg */
    NAS_LPP_SendOmtAirMsg(NAS_LPP_OMT_AIR_MSG_UP,
                          LNAS_LPP_REQ_ASSIST_DATA,
                          ulLppMsgLen,
                          pucEncodeOutMsg);

    ulLppMsgLen     = usBitPos/8;
    *pulLppMsglen   = ulLppMsgLen;

    return NAS_LPP_SUCCESS;
}

/*****************************************************************************
Function Name  : NAS_LPP_RcvMtaGnssAssistDataReqNoSessionRunningHandle
Description    : LPPģ��MtaGnssAssistDataReq�Ĵ�����ǰû������running��Session
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-10-22 �¿���
*****************************************************************************/
VOS_VOID   NAS_LPP_RcvMtaGnssAssistDataReqNoSessionRunningHandle
(
        MTA_LPP_GNSS_ASSIST_DATA_REQ_STRU          *pstMtaLppGnssAssistDataReq
)
{
    VOS_UINT8                               *pucEncodeOutMsg  = NAS_LPP_NULL_PTR;
    VOS_UINT32                               ulLppMsgLen      = 0;
    VOS_UINT32                               ulRslt           = 0;

    NAS_LPP_INFO_LOG("NAS_LPP_RcvMtaGnssAssistDataReqNoSessionRunningHandle is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvMtaGnssAssistDataReqNoSessionRunningHandle_ENUM, LNAS_LPP_Func_Enter);

    /*�������֮�������Ĵ洢�ռ�*/
    pucEncodeOutMsg = NAS_LPP_MEM_ALLOC(NAS_LPP_MAX_LCS_ASSIST_DATA_BUFF_MSG_LEN);
    if(NAS_LPP_NULL_PTR == pucEncodeOutMsg)
    {
        NAS_LPP_ERR_LOG("enocde up error  Alloc Mem Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvMtaGnssAssistDataReqNoSessionRunningHandle_ENUM, LNAS_LPP_MallocMemFail);
        return;
    }

    /*���*/
    NAS_LPP_MEM_SET_S(pucEncodeOutMsg,NAS_LPP_MAX_LCS_ASSIST_DATA_BUFF_MSG_LEN, 0, NAS_LPP_MAX_LCS_ASSIST_DATA_BUFF_MSG_LEN);

    /*�õ�GNSS���������ݵ�����*/
    ulRslt = NAS_LPP_EncodeGnssAssistDataReq(pstMtaLppGnssAssistDataReq, pucEncodeOutMsg, &ulLppMsgLen);
    if(NAS_LPP_FAILURE == ulRslt)
    {
        NAS_LPP_MEM_FREE(pucEncodeOutMsg);
        return;
    }

    /*���͸������������LCS*/
    NAS_LPP_SndLcsGnssAssistDataReq(pucEncodeOutMsg, ulLppMsgLen);

    NAS_LPP_MEM_FREE(pucEncodeOutMsg);

    return;
}

/*****************************************************************************
Function Name  : NAS_LPP_RcvMtaLppGnssAssistDataReq
Description    : LPPģ��MtaGnssAssistDataReq�Ĵ���
Input          :
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
1. lifuxin 00253982 2015-10-20 �¿���
*****************************************************************************/
VOS_VOID   NAS_LPP_RcvMtaLppGnssAssistDataReq
(
    MTA_LPP_GNSS_ASSIST_DATA_REQ_STRU          *pstMtaLppGnssAssistDataReq
)
{
    VOS_UINT8                       ucSessionIndx   = 0;
    NAS_LPP_CONFIG_PARA_STRU       *pstCfgPara      = NAS_LPP_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_RcvMtaLppGnssAssistDataReq is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvMtaLppGnssAssistDataReq_ENUM, LNAS_LPP_Func_Enter);

    pstCfgPara = NAS_LPP_GetCfgPara();

    ucSessionIndx = NAS_LPP_GetOneRunningSessionIndx();
    if(PS_NULL_UINT8 != ucSessionIndx)
    {
        /* �Գ崦��MTA����Ҫ���������ݵ�ʱ���Ѿ���һ��transaction�����·�GNSS�ĸ�����������,
          ֱ��return�����÷��͸����������� */
        if(pstCfgPara->bitGnssAssisChng)
        {
            NAS_LPP_INFO_LOG("NAS_LPP_RcvMtaLppGnssAssistDataReq: Have Gnss AssistData Process");
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvMtaLppGnssAssistDataReq_ENUM, LNAS_LPP_HaveGnssAssistDataProcess);
            return;
        }

        /*���ҵ�����running��session,ֱ�ӷ������еĸ�������������Ϣ*/
        NAS_LPP_CreatNewTransAndReqAssistData(ucSessionIndx, VOS_FALSE, VOS_TRUE, pstMtaLppGnssAssistDataReq);
    }
    else
    {
        /* �����ҵ�����running��session���򽫸�������������Ϣ���͸�LCS */
        NAS_LPP_RcvMtaGnssAssistDataReqNoSessionRunningHandle(pstMtaLppGnssAssistDataReq);
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_LPP_MtaMsgDistr
 Description    : LPPģ��Mta��Ϣ������
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
    1. lifuxin 00253982 2015-7-7 �¿���
*****************************************************************************/
VOS_VOID NAS_LPP_MtaMsgDistr( VOS_VOID *pRcvMsg )
{
    PS_MSG_HEADER_STRU         *pMtaMsg  = VOS_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_MtaMsgDistr is entered!");
    TLPS_PRINT2LAYER_ERROR(NAS_LPP_MtaMsgDistr_ENUM, LNAS_LPP_Func_Enter);

    pMtaMsg = (PS_MSG_HEADER_STRU*)pRcvMsg;

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch(pMtaMsg->ulMsgName)
    {
        /*������*/
        case ID_MTA_LPP_GNSS_CAP_CNF:
            NAS_LPP_RcvMtaLppGnssCapCnf( (MTA_LPP_GNSS_PROVIDE_CAPABITY_CNF_STRU *)pMtaMsg);
            break;

        case ID_MTA_LPP_GNSS_LOC_INFO_IND:
            NAS_LPP_RcvMtaLppGnssLocInfoInd( (MTA_LPP_GNSS_RROVIDE_LOCATION_INFO_IND_STRU *)pMtaMsg);
            break;

        case ID_MTA_LPP_GNSS_ASSISTDATA_REQ:
            NAS_LPP_RcvMtaLppGnssAssistDataReq((MTA_LPP_GNSS_ASSIST_DATA_REQ_STRU*)pMtaMsg);
            break;

        /*�û���*/
        case ID_MTA_LPP_UP_CAP_REQ:
            NAS_LPP_RcvMtaLppUpCapReq((MTA_LPP_UP_CAPABILITY_REQ_STRU*)pMtaMsg);
            break;

        case ID_MTA_LPP_UP_MEAS_NTY:
            NAS_LPP_RcvMtaLppUpMeasNotify((MTA_LPP_UP_MEAS_NTY_STRU*)pMtaMsg);
            break;

        case ID_MTA_LPP_UP_OTDOA_ASSIST_DATA_NTY:
            NAS_LPP_UpRcvMtaOtdoaAssistData((MTA_LPP_UP_OTDOA_ASSIST_DATA_NTY_STRU*)pMtaMsg);
            break;

        case ID_MTA_LPP_UP_MEAS_ABORT_NTY:
            NAS_LPP_RcvMtaLppUpAbortMeas((MTA_LPP_UP_MEAS_ABORT_NTY_STRU *)pMtaMsg);
            break;

        default:
            NAS_LPP_INFO_LOG("NAS_LPP_MtaMsgDistr: Msg Id Error");
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_MtaMsgDistr_ENUM, LNAS_LPP_TaskEntryNoThisMsg);
            break;
    }
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasLppMtaMsgProc.c */
