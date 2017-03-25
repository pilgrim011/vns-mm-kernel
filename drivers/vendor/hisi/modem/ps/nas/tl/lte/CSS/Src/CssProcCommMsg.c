/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : CssProcCommMsg.c
  Description     : ��C�ļ�������IMSAģ���ʼ������Ϣ������ڵ�ʵ��
  History           :
     1.wangchen 00209181    2015-05-14  Draft Enact

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "CssProcLphyMsg.h"
#include "CssProcCommMsg.h"
#include "CssProcSrchRslt.h"
#include "CssOmInterface.h"
#include "CssCloudStrategyPublic.h"

#define    THIS_FILE_ID        PS_FILE_ID_CSSPROCCOMMMSG_C


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name   : CSS_JudgeIsExitFreq
 Description     : �ж��Ƿ����ĳ�����뼼���µĸ�����Ƶ����߿�פ�����޵�Ƶ��
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    wangchen 00209181 2015-05-18   Draft Enact
*****************************************************************************/
VOS_VOID  CSS_JudgeLowTypeScanRssiExistType
(
    VOS_UINT8                               *pucIsExistLLowFreq,
    VOS_UINT8                               *pucIsExistLHigFreq,
    VOS_UINT8                               *pucIsExistWLowFreq,
    VOS_UINT8                               *pucIsExistWHigFreq,
    VOS_UINT8                               *pucIsExistGLowFreq,
    VOS_UINT8                               *pucIsExistGHigFreq
)
{
    CSS_COMM_SCAN_BAND_NODE_STRU       *pstBandNode;
    CSS_CONTROL_STRU                   *pstCssControl;
    VOS_UINT32                          ulBandNum;
    CSS_COMM_SCAN_BAND_LIST_STRU       *pstCommScanBandList;

    pstBandNode                         = CSS_GetCommScanBandListHeadNode();
    pstCommScanBandList                 = CSS_GetCommScanBandListAddr();
    pstCssControl                       = CSS_GetControlAddr();

    /* ��ʼ�� */
    *pucIsExistLLowFreq = CSS_FALSE;
    *pucIsExistLHigFreq = CSS_FALSE;
    *pucIsExistWLowFreq = CSS_FALSE;
    *pucIsExistWHigFreq = CSS_FALSE;
    *pucIsExistGLowFreq = CSS_FALSE;
    *pucIsExistGHigFreq = CSS_FALSE;

    /* �ж��Ƿ����G�ĸ�����Ƶ����߿�פ����Ƶ�� */
    for (ulBandNum = 0; ulBandNum < pstCommScanBandList->ucBandCount; ulBandNum++)
    {
        if (0 != pstBandNode->stBandInfo.ucScanRsltArrayCount)
        {
            if (CSS_OP_TRUE == pstBandNode->stBandInfo.bitOpLteSupport)
            {
                if ((pstBandNode->stBandInfo.pstScanRsltArray[0].sRssi) >= (pstCssControl->stRssiThreshold.sLLowRssiThresHold))
                {
                    *pucIsExistLLowFreq = CSS_TRUE;
                }

                if ((pstBandNode->stBandInfo.pstScanRsltArray[0].sRssi) >= (pstCssControl->stRssiThreshold.sLHighRssiThresHold))
                {
                    *pucIsExistLHigFreq = CSS_TRUE;
                }
            }
            if (CSS_OP_TRUE == pstBandNode->stBandInfo.bitOpWcdmaSupport)
            {
                if ((pstBandNode->stBandInfo.pstScanRsltArray[0].sRssi) >= (pstCssControl->stRssiThreshold.sWLowRssiThresHold))
                {
                    *pucIsExistWLowFreq = CSS_TRUE;
                }
                if ((pstBandNode->stBandInfo.pstScanRsltArray[0].sRssi) >= (pstCssControl->stRssiThreshold.sWHighRssiThresHold))
                {
                    *pucIsExistWHigFreq = CSS_TRUE;
                }
            }
            if (CSS_OP_TRUE == pstBandNode->stBandInfo.bitOpGsmSupport)
            {
                if ((pstBandNode->stBandInfo.pstScanRsltArray[0].sRssi) >= (pstCssControl->stRssiThreshold.sGLowRssiThresHold))
                {
                    *pucIsExistGLowFreq = CSS_TRUE;
                }

                if ((pstBandNode->stBandInfo.pstScanRsltArray[0].sRssi) >= (pstCssControl->stRssiThreshold.sGHighRssiThresHold))
                {
                    *pucIsExistGHigFreq = CSS_TRUE;
                }
            }
        }
        /* ������ֽ��뼼�������ڸ�����Ƶ�㣬��ֱ���˳� */
        if ((CSS_TRUE == *pucIsExistLHigFreq) && (CSS_TRUE == *pucIsExistWHigFreq) && (CSS_TRUE == *pucIsExistGHigFreq))
        {
            break;
        }
        pstBandNode = pstBandNode->pstNext;
    }

}
/*****************************************************************************
 Function Name   : CSS_JudgeIsExitFreq
 Description     : �ж��Ƿ����ĳ�����뼼���µĸ�����Ƶ����߿�פ�����޵�Ƶ��
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    wangchen 00209181 2015-05-18   Draft Enact
*****************************************************************************/
VOS_VOID  CSS_JudgeHighTypeScanRssiExistType
(
    VOS_UINT8                               *pucIsExistLHigFreq,
    VOS_UINT8                               *pucIsExistWHigFreq,
    VOS_UINT8                               *pucIsExistGHigFreq
)
{
    CSS_COMM_SCAN_BAND_NODE_STRU       *pstBandNode;
    VOS_UINT32                          ulBandNum;
    CSS_COMM_SCAN_BAND_LIST_STRU       *pstCommScanBandList;
    CSS_CONTROL_STRU                   *pstCssControl;

    pstBandNode                         = CSS_GetCommScanBandListHeadNode();
    pstCommScanBandList                 = CSS_GetCommScanBandListAddr();
    pstCssControl                       = CSS_GetControlAddr();

    /* ��ʼ�� */
    *pucIsExistLHigFreq = CSS_FALSE;
    *pucIsExistWHigFreq = CSS_FALSE;
    *pucIsExistGHigFreq = CSS_FALSE;

    for (ulBandNum = 0; ulBandNum < pstCommScanBandList->ucBandCount; ulBandNum++)
    {
        if (0 != pstBandNode->stBandInfo.ucScanRsltArrayCount)
        {
            if (CSS_OP_TRUE == pstBandNode->stBandInfo.bitOpLteSupport)
            {
                if ((pstBandNode->stBandInfo.pstScanRsltArray[0].sRssi) >= (pstCssControl->stRssiThreshold.sLHighRssiThresHold))
                {
                    *pucIsExistLHigFreq = CSS_TRUE;
                }
            }
            if (CSS_OP_TRUE == pstBandNode->stBandInfo.bitOpWcdmaSupport)
            {
                if ((pstBandNode->stBandInfo.pstScanRsltArray[0].sRssi) >= (pstCssControl->stRssiThreshold.sWHighRssiThresHold))
                {
                    *pucIsExistWHigFreq = CSS_TRUE;
                }
            }
            if (CSS_OP_TRUE == pstBandNode->stBandInfo.bitOpGsmSupport)
            {
                if ((pstBandNode->stBandInfo.pstScanRsltArray[0].sRssi) >= (pstCssControl->stRssiThreshold.sGHighRssiThresHold))
                {
                    *pucIsExistGHigFreq = CSS_TRUE;
                }
            }
        }
        /* ������ֽ��뼼�������ڸ�����Ƶ�㣬��ֱ���˳� */
        if ((CSS_TRUE == *pucIsExistLHigFreq) && (CSS_TRUE == *pucIsExistWHigFreq) && (CSS_TRUE == *pucIsExistGHigFreq))
        {
            break;
        }
        pstBandNode = pstBandNode->pstNext;
    }
}

/*****************************************************************************
 Function Name   : CSS_JudgeRssiExistType
 Description     : �ж��Ƿ����ĳ�����뼼���µĸ�����Ƶ����߿�פ�����޵�Ƶ��
 Input           : None
 Output          : None
 Return          : VOS_UINT32
 History         :
    1.    wangchen 00209181 2015-05-18   Draft Enact
*****************************************************************************/
VOS_VOID  CSS_JudgeRssiExistType
(
    CSS_COVERAGE_TYPE_ENUM_UINT8                    *penGsmCoverageType,
    CSS_COVERAGE_TYPE_ENUM_UINT8                    *penUmtsFddCoverageType,
    CSS_COVERAGE_TYPE_ENUM_UINT8                    *penLteCoverageType
)
{
    CSS_CONTROL_STRU                        *pstCssControl;
    VOS_UINT8                               ucIsExistLLowFreq   = CSS_FALSE;
    VOS_UINT8                               ucIsExistLHigFreq   = CSS_FALSE;
    VOS_UINT8                               ucIsExistWLowFreq   = CSS_FALSE;
    VOS_UINT8                               ucIsExistWHigFreq   = CSS_FALSE;
    VOS_UINT8                               ucIsExistGLowFreq   = CSS_FALSE;
    VOS_UINT8                               ucIsExistGHigFreq   = CSS_FALSE;

    pstCssControl                           = CSS_GetControlAddr();

    if (CSS_OP_TRUE != pstCssControl->stCommMsg.bitOpHighRssi) /* ����ǿ�פ������ɨƵ */
    {
        CSS_JudgeLowTypeScanRssiExistType(&ucIsExistLLowFreq, &ucIsExistLHigFreq,
                                            &ucIsExistWLowFreq, &ucIsExistWHigFreq,
                                            &ucIsExistGLowFreq, &ucIsExistGHigFreq);
    }
    else    /* ����Ǹ�����ɨƵ */
    {
        CSS_JudgeHighTypeScanRssiExistType(&ucIsExistLHigFreq, &ucIsExistWHigFreq, &ucIsExistGHigFreq);
    }

    /* ������ڸ������ģ��򷵻�����Ϊ����������������ڿ�פ���ģ��򷵻�����Ϊ��פ�������򣬷���NONE */
    if (CSS_TRUE == ucIsExistLHigFreq)
    {
        *penLteCoverageType = CSS_COVERAGE_TYPE_HIGH;
    }
    else if (CSS_TRUE == ucIsExistLLowFreq)
    {
        *penLteCoverageType = CSS_COVERAGE_TYPE_LOW;
    }
    else
    {
        *penLteCoverageType = CSS_COVERAGE_TYPE_NONE;
    }

    if (CSS_TRUE == ucIsExistWHigFreq)
    {
        *penUmtsFddCoverageType = CSS_COVERAGE_TYPE_HIGH;
    }
    else if (CSS_TRUE == ucIsExistWLowFreq)
    {
        *penUmtsFddCoverageType = CSS_COVERAGE_TYPE_LOW;
    }
    else
    {
        *penUmtsFddCoverageType = CSS_COVERAGE_TYPE_NONE;
    }

    if (CSS_TRUE == ucIsExistGHigFreq)
    {
        *penGsmCoverageType = CSS_COVERAGE_TYPE_HIGH;
    }
    else if (CSS_TRUE == ucIsExistGLowFreq)
    {
        *penGsmCoverageType = CSS_COVERAGE_TYPE_LOW;
    }
    else
    {
        *penGsmCoverageType = CSS_COVERAGE_TYPE_NONE;
    }
    return;
}

/*****************************************************************************
 Function Name  : CSS_ProcCommMsgCurrGeoInd
 Description    : ID_CSS_CURR_GEO_IND��Ϣ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-12  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcCommMsgCurrGeoInd
(
    const CSS_CURR_GEO_IND_STRU *pstCurrGeoInd
)
{
    CSS_MCC_ID_STRU                     astMccID[CSS_MAX_PLMN_ID_NUM];
    VOS_UINT32                          ulMccNum = 0;
    CSS_MCC_ID_STRU                     astMccToSend[CSS_MAX_PLMN_ID_NUM];
    VOS_UINT32                          ulMccNumToSend = 0;
    VOS_UINT32                          i;

    CSS_MEM_SET_S(  astMccID,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM,
                    0,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);
    CSS_MEM_SET_S(  astMccToSend,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM,
                    0,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);

    CSS_INFO_LOG("CSS_ProcCommMsgCurrGeoInd is entered!");
    TLPS_PRINT2LAYER_INFO(CSS_ProcCommMsgCurrGeoInd_ENUM, LNAS_ENTRY);

    /* �����ͨ�����Բ�ʹ�ã�ֱ�ӷ���RSP�ɹ� */
    if (CSS_FALSE == CSS_IsCloudStrategyEnable())
    {
        CSS_SndCurrGeoRsp(pstCurrGeoInd->ulSenderPid, CSS_RESULT_SUCC);
        CSS_INFO_LOG("CSS_ProcCommMsgCurrGeoInd: cloud strategy is not enabled");
        TLPS_PRINT2LAYER_INFO(CSS_ProcCommMsgCurrGeoInd_ENUM, LNAS_FUNCTION_LABEL1);

        CSS_PrintLocalPrefFreqInfo();
        return;
    }

    /* ��������ƶ˻�ȡ��Ҳֱ�ӷ���RSP�ɹ� */
    if (CSS_FALSE == CSS_IsPrefFreqEnable())
    {
        CSS_SndCurrGeoRsp(pstCurrGeoInd->ulSenderPid, CSS_RESULT_SUCC);
        CSS_INFO_LOG("CSS_ProcCommMsgCurrGeoInd: cloud pref freq is not enabled");
        TLPS_PRINT2LAYER_INFO(CSS_ProcCommMsgCurrGeoInd_ENUM, LNAS_FUNCTION_LABEL2);

        CSS_PrintLocalPrefFreqInfo();
        return;
    }

    TLPS_PRINT2LAYER_INFO1(CSS_ProcCommMsgCurrGeoInd_ENUM, LNAS_FUNCTION_LABEL3, pstCurrGeoInd->ulIsPowerOn);

    /* �ҳ���Ϣ�е�MCC�б� */
    CSS_GetMccFromPlmnArr(astMccID, &ulMccNum, pstCurrGeoInd->astPlmnId, pstCurrGeoInd->ulPlmnNum);
    TLPS_PRINT2LAYER_INFO1(CSS_ProcCommMsgCurrGeoInd_ENUM, LNAS_FUNCTION_LABEL4, ulMccNum);
    if ( 0 == ulMccNum )
    {
        CSS_SndCurrGeoRsp(pstCurrGeoInd->ulSenderPid, CSS_RESULT_FAIL);
        return;
    }

    for (i = 0; i < ulMccNum; ++i)
    {
        TLPS_PRINT2LAYER_INFO2(CSS_ProcCommMsgCurrGeoInd_ENUM, LNAS_FUNCTION_LABEL4, astMccID[i].aucMccId[0], astMccID[i].aucMccId[1]);
    }


    /* ����������AP���͵��б��� */
    CSS_MEM_CPY_S(  astMccToSend,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM,
                    astMccID,
                    sizeof(CSS_MCC_ID_STRU)*CSS_MAX_PLMN_ID_NUM);

    ulMccNumToSend = ulMccNum;

    /* �п����� */
    if (VOS_TRUE == pstCurrGeoInd->ulIsPowerOn)
    {
        /* ������Щ�б��ڱ����Ƿ��Ѿ��洢 */
        CSS_DeleteSameMccAccordToLocal(astMccToSend, &ulMccNumToSend);
    }

    /* log ��ӡ */
    TLPS_PRINT2LAYER_INFO1(CSS_ProcCommMsgCurrGeoInd_ENUM, LNAS_FUNCTION_LABEL5, ulMccNumToSend);
    for (i = 0; i < ulMccNumToSend; ++i)
    {
        TLPS_PRINT2LAYER_INFO2( CSS_ProcCommMsgCurrGeoInd_ENUM,
                                LNAS_FUNCTION_LABEL5,
                                astMccToSend[i].aucMccId[0],
                                astMccToSend[i].aucMccId[1]);
    }

    /* �������д洢��ֱ�ӻظ��ɹ� */
    if (0 == ulMccNumToSend)
    {
        CSS_SndCurrGeoRsp(pstCurrGeoInd->ulSenderPid, CSS_RESULT_SUCC);
        CSS_PrintLocalPrefFreqInfo();
        return;
    }

    /* ������Щ�б��Ƿ����ڵȴ��ƶ��·� */
    CSS_DeleteMccAlreadySndToAp(astMccToSend, &ulMccNumToSend);

    TLPS_PRINT2LAYER_INFO1(CSS_ProcCommMsgCurrGeoInd_ENUM, LNAS_FUNCTION_LABEL6, ulMccNumToSend);
    for (i = 0; i < ulMccNumToSend; ++i)
    {
        TLPS_PRINT2LAYER_INFO2( CSS_ProcCommMsgCurrGeoInd_ENUM,
                                LNAS_FUNCTION_LABEL6,
                                astMccToSend[i].aucMccId[0],
                                astMccToSend[i].aucMccId[1]);
    }

    TLPS_PRINT2LAYER_INFO1(CSS_ProcCommMsgCurrGeoInd_ENUM, LNAS_FUNCTION_LABEL7, CSS_GetPrefMccNodeNum());

    /* ɾ�������ڴ��е���ЩMCC */
    CSS_DeleteLocalMccFromMccArray(astMccToSend, ulMccNumToSend);

    TLPS_PRINT2LAYER_INFO1(CSS_ProcCommMsgCurrGeoInd_ENUM, LNAS_FUNCTION_LABEL8, CSS_GetPrefMccNodeNum());

    /* ����PID������������ */
    CSS_StartMmcOrAsMccUpdateProcedure(astMccID, ulMccNum, astMccToSend, ulMccNumToSend, pstCurrGeoInd->ulSenderPid);

    /* ��ӡ����ȫ�ֱ��� */
    CSS_SndOmPubCloudCtrlInd();
}



VOS_VOID CSS_SndCurrGeoRsp(VOS_UINT32 ulPid, CSS_RESULT_ENUM_UINT32 enRslt)
{
    CSS_CURR_GEO_RSP_STRU              *pstGeoRsp;

    TLPS_PRINT2LAYER_INFO2(CSS_SndCurrGeoRsp_ENUM, LNAS_ENTRY, ulPid, enRslt);

    /* ����ѹػ����򲻷��� */
    if (CSS_SS_WAIT_START_IND == CSS_GetCurSubStatus())
    {
        CSS_WARN_LOG("CSS_SndCurrGeoRsp: no start yet");
        return;
    }

    /*������Ϣ�ռ�*/
    pstGeoRsp = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_CURR_GEO_RSP_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstGeoRsp)
    {
        /*��ӡ�쳣��Ϣ*/
        return ;
    }

    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstGeoRsp),
                    CSS_GET_MSG_LENGTH(pstGeoRsp),
                    0,
                    CSS_GET_MSG_LENGTH(pstGeoRsp));

    CSS_WRITE_COMM_MSG_HEAD(pstGeoRsp, ID_CSS_CURR_GEO_RSP, ulPid);

    pstGeoRsp->enResult = enRslt;

    /*������Ϣ���ͺ��� */
    CSS_SND_MSG(pstGeoRsp);
}





VOS_VOID CSS_SndCommMsgStopBandScanCnf
(
    VOS_UINT32                                      ulReceiverPid,
    CSS_RESULT_ENUM_UINT32                          enResult
)
{
    CSS_STOP_BAND_SCAN_CNF_STRU *pstCssStopBandScanCnf;

    /*������Ϣ�ռ�*/
    pstCssStopBandScanCnf = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_STOP_BAND_SCAN_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstCssStopBandScanCnf)
    {
        /*��ӡ�쳣��Ϣ*/
        CSS_ERR_LOG("CSS_SndCommMsgStopBandScanCnf:ERROR:Alloc Msg fail!");
        return ;
    }

    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstCssStopBandScanCnf),
                    CSS_GET_MSG_LENGTH(pstCssStopBandScanCnf),
                    0,
                    CSS_GET_MSG_LENGTH(pstCssStopBandScanCnf));

    CSS_WRITE_COMM_MSG_HEAD(pstCssStopBandScanCnf,ID_CSS_STOP_BAND_SCAN_CNF, ulReceiverPid);

    pstCssStopBandScanCnf->enResult = enResult;

    /*������Ϣ���ͺ��� */
    CSS_SND_MSG(pstCssStopBandScanCnf);

    return ;
}

VOS_VOID CSS_SndCommMsgBandScanCnf
(
    VOS_UINT32                                      ulReceiverPid,
    VOS_UINT32                                      ulOpid,
    CSS_MULTI_BAND_SCAN_RESULT_ENUM_UINT8           enResult
)
{
    CSS_MULTI_BAND_SCAN_CNF_STRU *pstCssBandScanCnf;

    /*������Ϣ�ռ�*/
    pstCssBandScanCnf = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_MULTI_BAND_SCAN_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstCssBandScanCnf)
    {
        /*��ӡ�쳣��Ϣ*/
        CSS_ERR_LOG("CSS_SndCommMsgStopBandScanCnf:ERROR:Alloc Msg fail!");
        return ;
    }

    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstCssBandScanCnf),
                    CSS_GET_MSG_LENGTH(pstCssBandScanCnf),
                    0,
                    CSS_GET_MSG_LENGTH(pstCssBandScanCnf));

    CSS_WRITE_COMM_MSG_HEAD(pstCssBandScanCnf,ID_CSS_MULTI_BAND_SCAN_CNF, ulReceiverPid);

    pstCssBandScanCnf->enResult = enResult;

    pstCssBandScanCnf->ulOpid = ulOpid;

    if (CSS_MULTI_BAND_SCAN_RESULT_SUCC == enResult)
    {
        /* ���ɨƵ�����У�������G�ģ��������������뼼������Ҫ�����жϣ�ֱ����ΪNULL */
        CSS_JudgeRssiExistType(&pstCssBandScanCnf->enGsmCoverageType,
                                &pstCssBandScanCnf->enUmtsFddCoverageType,
                                &pstCssBandScanCnf->enLteCoverageType);
    }

    TLPS_PRINT2LAYER_INFO2(CSS_SndCommMsgBandScanCnf_ENUM, LNAS_FUNCTION_LABEL1, pstCssBandScanCnf->enGsmCoverageType, pstCssBandScanCnf->enUmtsFddCoverageType);
    TLPS_PRINT2LAYER_INFO1(CSS_SndCommMsgBandScanCnf_ENUM, LNAS_FUNCTION_LABEL1, pstCssBandScanCnf->enLteCoverageType);
    CSS_INFO_LOG1(" CSS_SndCommMsgBandScanCnf pstCssBandScanCnf->enGsmHighRssiExitType = ", pstCssBandScanCnf->enGsmCoverageType);
    TLPS_PRINT2LAYER_INFO1(CSS_SndCommMsgBandScanCnf_ENUM, LNAS_FUNCTION_LABEL2, pstCssBandScanCnf->enGsmCoverageType);
    CSS_INFO_LOG1(" CSS_SndCommMsgBandScanCnf pstCssBandScanCnf->enGsmHighRssiExitType = ", pstCssBandScanCnf->enUmtsFddCoverageType);
    TLPS_PRINT2LAYER_INFO1(CSS_SndCommMsgBandScanCnf_ENUM, LNAS_FUNCTION_LABEL3, pstCssBandScanCnf->enUmtsFddCoverageType);
    CSS_INFO_LOG1(" CSS_SndCommMsgBandScanCnf pstCssBandScanCnf->enLteCoverageType = ", pstCssBandScanCnf->enLteCoverageType);
    TLPS_PRINT2LAYER_INFO1(CSS_SndCommMsgBandScanCnf_ENUM, LNAS_FUNCTION_LABEL4, pstCssBandScanCnf->enLteCoverageType);


    /*������Ϣ���ͺ��� */
    CSS_SND_MSG(pstCssBandScanCnf);


    return ;
}



VOS_VOID CSS_SndMsgAsStopBandScanCnf
(
    VOS_UINT32                                      ulReceiverPid,
    CSS_RESULT_ENUM_UINT32                          enResult
)
{
    CSS_AS_STOP_BAND_SCAN_CNF_STRU     *pstCssStopBandScanCnf;

    /*������Ϣ�ռ�*/
    pstCssStopBandScanCnf = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_AS_STOP_BAND_SCAN_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstCssStopBandScanCnf)
    {
        return ;
    }

    CSS_MEM_SET_S( CSS_GET_MSG_ENTITY(pstCssStopBandScanCnf), CSS_GET_MSG_LENGTH(pstCssStopBandScanCnf), 0, CSS_GET_MSG_LENGTH(pstCssStopBandScanCnf));

    CSS_WRITE_COMM_MSG_HEAD(pstCssStopBandScanCnf,ID_CSS_AS_STOP_BAND_SCAN_CNF, ulReceiverPid);

    pstCssStopBandScanCnf->enResult = enResult;

    /*������Ϣ���ͺ��� */
    CSS_SND_MSG(pstCssStopBandScanCnf);
}


VOS_VOID CSS_SndMsgAsBandScanCnf
(
    VOS_UINT32                                      ulReceiverPid,
    VOS_UINT32                                      ulOpid,
    CSS_MULTI_BAND_SCAN_RESULT_ENUM_UINT8           enResult
)
{
    CSS_AS_BAND_SCAN_CNF_STRU *pstCssBandScanCnf;

    /*������Ϣ�ռ�*/
    pstCssBandScanCnf = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_AS_BAND_SCAN_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstCssBandScanCnf)
    {
        return ;
    }

    CSS_MEM_SET_S( CSS_GET_MSG_ENTITY(pstCssBandScanCnf), CSS_GET_MSG_LENGTH(pstCssBandScanCnf), 0, CSS_GET_MSG_LENGTH(pstCssBandScanCnf));

    CSS_WRITE_COMM_MSG_HEAD(pstCssBandScanCnf,ID_CSS_AS_BAND_SCAN_CNF, ulReceiverPid);

    pstCssBandScanCnf->enResult = enResult;

    pstCssBandScanCnf->ulOpid = ulOpid;

    /*������Ϣ���ͺ��� */
    CSS_SND_MSG(pstCssBandScanCnf);
}


VOS_VOID CSS_SndAsBandScanRslt
(
    VOS_UINT32                                    ulReceiverPid,
    VOS_UINT32                                    ulOpid
)
{
    CSS_COMM_SCAN_BAND_NODE_STRU                 *pstBandNode;
    CSS_COMM_SCAN_BAND_LIST_STRU                 *pstBandList = CSS_GetAsScanBandListAddr();
    VOS_UINT8                                     ucCopyedBandNum = 0;
    VOS_UINT8                                     ucCopyFreqNum;
    CSS_AS_BAND_SCAN_RSLT_STRU                   *pstBandRslt;
    VOS_UINT8                                     ucLoopNum = 0;

    pstBandRslt = (CSS_AS_BAND_SCAN_RSLT_STRU*)CSS_MEM_ALLOC(sizeof(CSS_AS_BAND_SCAN_RSLT_STRU));
    if (CSS_NULL_PTR == pstBandRslt)
    {
        return;
    }

    CSS_MEM_SET_S(pstBandRslt, sizeof(CSS_AS_BAND_SCAN_RSLT_STRU), 0, sizeof(CSS_AS_BAND_SCAN_RSLT_STRU));

    /* �Ƚ�BAND����������� */
    pstBandNode = pstBandList->pstHead;
    while ((CSS_NULL_PTR != pstBandNode) && (ucLoopNum < pstBandList->ucBandCount))
    {
        ucCopyFreqNum = (pstBandNode->stBandInfo.ucScanRsltArrayCount < CSS_AS_BAND_SCAN_MAX_FREQ_RSLT_NUM)
                        ? (pstBandNode->stBandInfo.ucScanRsltArrayCount)
                        : (CSS_AS_BAND_SCAN_MAX_FREQ_RSLT_NUM);

        /* ��BAND IND��ֵ */
        pstBandRslt->astRsltList[ucCopyedBandNum].enBandInd = pstBandNode->stBandInfo.ucBandInd;
        /* freq������ֵ */
        pstBandRslt->astRsltList[ucCopyedBandNum].usFreqRangeNum = ucCopyFreqNum;
        /* ����freq */
        CSS_MEM_CPY_S(  pstBandRslt->astRsltList[ucCopyedBandNum].astFreqScanResult,
                        sizeof(CSS_FREQ_RANGE_STRU)*CSS_AS_BAND_SCAN_MAX_FREQ_RSLT_NUM,
                        pstBandNode->stBandInfo.pstScanRsltArray,
                        sizeof(CSS_FREQ_RANGE_STRU)*ucCopyFreqNum);
        /* �Ѿ������ĸ�����1 */
        ucCopyedBandNum ++;
        pstBandRslt->ucBandNum = ucCopyedBandNum;

        if (CSS_NULL_PTR == pstBandNode->pstNext)
        {
            CSS_SndMsgAsBandScanInd(pstBandRslt, VOS_TRUE, ulReceiverPid, ulOpid);
            break;
        }

        if (ucCopyedBandNum >= CSS_AS_BAND_SCAN_RSLT_MAX_BAND_NUM)
        {
            CSS_SndMsgAsBandScanInd(pstBandRslt, VOS_FALSE, ulReceiverPid, ulOpid);

            CSS_MEM_SET_S(pstBandRslt, sizeof(CSS_AS_BAND_SCAN_RSLT_STRU), 0, sizeof(CSS_AS_BAND_SCAN_RSLT_STRU));
            ucCopyedBandNum = 0;
        }
        pstBandNode = pstBandNode->pstNext;
        ucLoopNum ++;
    }

    CSS_MEM_FREE(pstBandRslt);

}



VOS_VOID CSS_SndMsgAsBandScanInd
(
    const CSS_AS_BAND_SCAN_RSLT_STRU             *pstBandRslt,
    VOS_UINT8                                     ucIsEnd,
    VOS_UINT32                                    ulReceiverPid,
    VOS_UINT32                                    ulOpid
)
{
    CSS_AS_BAND_SCAN_IND_STRU                    *pstCssBandScanInd;

    /*������Ϣ�ռ�*/
    pstCssBandScanInd = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_AS_BAND_SCAN_IND_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstCssBandScanInd)
    {
        return ;
    }

    CSS_MEM_SET_S( CSS_GET_MSG_ENTITY(pstCssBandScanInd), CSS_GET_MSG_LENGTH(pstCssBandScanInd), 0, CSS_GET_MSG_LENGTH(pstCssBandScanInd));

    CSS_WRITE_COMM_MSG_HEAD(pstCssBandScanInd,ID_CSS_AS_BAND_SCAN_IND, ulReceiverPid);

    pstCssBandScanInd->ulOpid = ulOpid;

    pstCssBandScanInd->ucIsEnd = ucIsEnd;

    CSS_MEM_CPY_S(&(pstCssBandScanInd->stScanRslt), sizeof(CSS_AS_BAND_SCAN_RSLT_STRU), pstBandRslt, sizeof(CSS_AS_BAND_SCAN_RSLT_STRU));

    /*������Ϣ���ͺ��� */
    CSS_SND_MSG(pstCssBandScanInd);
}



/*****************************************************************************
 Function Name  : CSS_CommBandScanReqMsgSave
 Description    : ����ɨƵ������Ϣ
 Input          :
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.wangchen 00209181   2015-05-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_CommBandScanReqMsgSave(const CSS_MULTI_BAND_SCAN_REQ_STRU *pstBandScanReq)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    CSS_INFO_LOG("CSS_CommBandScanReqMsgSave is entered!");
    TLPS_PRINT2LAYER_INFO(CSS_BandScanReqMsgSave_ENUM, LNAS_ENTRY);

    /* ���֮ǰ�Ѿ��б��棬�򷵻�ʧ�� */
    if (CSS_OP_TRUE == pstCssControl->stCommMsg.bitOpSaveMsg)
    {
        CSS_INFO_LOG("CSS_CommBandScanReqMsgSave has existed");
        TLPS_PRINT2LAYER_INFO(CSS_BandScanReqMsgSave_ENUM, LNAS_BandScanReqMsgSave_Existed);

        CSS_MEM_SET_S(  &(pstCssControl->stCommMsg),
                        sizeof(pstCssControl->stCommMsg),
                        0,
                        sizeof(pstCssControl->stCommMsg));
    }

    /* ������������ */
    pstCssControl->stCommMsg.bitOpSaveMsg      = CSS_OP_TRUE;
    pstCssControl->stCommMsg.bitOpHighRssi     = pstBandScanReq->bitOpHighRssi;
    pstCssControl->stCommMsg.ulOpid            = pstBandScanReq->ulOpid;
    pstCssControl->stCommMsg.ulReceiverPid     = pstBandScanReq->ulSenderPid;
    pstCssControl->stCommMsg.enMsgId           = ID_CSS_MULTI_BAND_SCAN_REQ;

    pstCssControl->stCommMsg.enBandScanType    = pstBandScanReq->enBandScanType;
    pstCssControl->stCommMsg.bitOpMcc          = pstBandScanReq->bitOpMcc;
    pstCssControl->stCommMsg.aucMcc[0]         = pstBandScanReq->aucMcc[0];
    pstCssControl->stCommMsg.aucMcc[1]         = pstBandScanReq->aucMcc[1];

    CSS_MEM_CPY_S(  &(pstCssControl->stCommMsg.stRatList),
                    sizeof(CSS_RAT_LIST),
                    &(pstBandScanReq->stRatList),
                    sizeof(CSS_RAT_LIST));


    return;
}

/*****************************************************************************
 Function Name  : CSS_AsBandScanReqMsgSave
 Description    : ����ASɨƵ������Ϣ
 Input          :
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.chengmin 00285307   2015-12-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AsBandScanReqMsgSave(const CSS_AS_BAND_SCAN_REQ_STRU *pstBandScanReq)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    TLPS_PRINT2LAYER_INFO(CSS_AsBandScanReqMsgSave_ENUM, LNAS_ENTRY);

    /* ���֮ǰ�Ѿ��б��棬��ֱ�ӽ�ԭ�д洢��Ϣ���� */
    if (VOS_TRUE == pstCssControl->stAsMsg.ulIsSaveMsg)
    {
        TLPS_PRINT2LAYER_INFO(CSS_AsBandScanReqMsgSave_ENUM, LNAS_BandScanReqMsgSave_Existed);
        CSS_MEM_SET_S(&(pstCssControl->stAsMsg), sizeof(CSS_AS_MSG_STRU), 0, sizeof(CSS_AS_MSG_STRU));
    }

    /* ������������ */
    pstCssControl->stAsMsg.ulIsSaveMsg       = VOS_TRUE;
    pstCssControl->stAsMsg.ulMsgId           = pstBandScanReq->ulMsgId;
    pstCssControl->stAsMsg.ulOpid            = pstBandScanReq->ulOpid;
    pstCssControl->stAsMsg.ulReceiverPid     = pstBandScanReq->ulSenderPid;

    pstCssControl->stAsMsg.ucRatType         = pstBandScanReq->ucRatType;
    CSS_MEM_CPY_S(&(pstCssControl->stAsMsg.stBandList), sizeof(CSS_BAND_LIST), &(pstBandScanReq->stBandList), sizeof(CSS_BAND_LIST));
}

/*****************************************************************************
 Function Name  : CSS_AsStopBandScanReqMsgSave
 Description    : ����ASֹͣɨƵ������Ϣ
 Input          :
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.chengmin 00285307   2015-12-18  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AsStopBandScanReqMsgSave(const CSS_AS_STOP_BAND_SCAN_REQ_STRU *pstAsStopBandScanReq)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    TLPS_PRINT2LAYER_INFO(CSS_AsStopBandScanReqMsgSave_ENUM, LNAS_ENTRY);

    /* ���֮ǰ�Ѿ��б��棬��ֱ�ӽ�ԭ�д洢��Ϣ���� */
    if (CSS_OP_TRUE == pstCssControl->stAsMsg.ulIsSaveMsg)
    {
        TLPS_PRINT2LAYER_INFO(CSS_AsStopBandScanReqMsgSave_ENUM, LNAS_BandScanReqMsgSave_Existed);
        CSS_MEM_SET_S(&(pstCssControl->stAsMsg), sizeof(CSS_AS_MSG_STRU), 0, sizeof(CSS_AS_MSG_STRU));
    }

    /* ������������ */
    pstCssControl->stAsMsg.ulIsSaveMsg = CSS_OP_TRUE;
    pstCssControl->stAsMsg.ulReceiverPid = pstAsStopBandScanReq->ulSenderPid;
    pstCssControl->stAsMsg.ulMsgId = pstAsStopBandScanReq->ulMsgId;
    return;
}




/*****************************************************************************
 Function Name  : CSS_StopBandScanReqMsgSave
 Description    : ����ֹͣɨƵ������Ϣ
 Input          :
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.wangchen 00209181   2015-05-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_StopBandScanReqMsgSave(const CSS_STOP_BAND_SCAN_REQ_STRU *pstStopBandScanReq)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    CSS_INFO_LOG("CSS_StopBandScanReqMsgSave is entered!");
    TLPS_PRINT2LAYER_INFO(CSS_StopBandScanReqMsgSave_ENUM, LNAS_ENTRY);

    /* ���֮ǰ�Ѿ��б��棬��ֱ�ӽ�ԭ�д洢��Ϣ���� */
    if (CSS_OP_TRUE == pstCssControl->stCommMsg.bitOpSaveMsg)
    {
        CSS_INFO_LOG("CSS_StopBandScanReqMsgSave has existed");
        TLPS_PRINT2LAYER_INFO(CSS_StopBandScanReqMsgSave_ENUM, LNAS_BandScanReqMsgSave_Existed);

        CSS_MEM_SET_S(  &(pstCssControl->stCommMsg),
                        sizeof(pstCssControl->stCommMsg),
                        0,
                        sizeof(pstCssControl->stCommMsg));
    }

    /* ������������ */
    pstCssControl->stCommMsg.bitOpSaveMsg = CSS_OP_TRUE;
    pstCssControl->stCommMsg.ulReceiverPid = pstStopBandScanReq->ulSenderPid;
    pstCssControl->stCommMsg.enMsgId = ID_CSS_STOP_BAND_SCAN_REQ;


    return;
}

/*****************************************************************************
 Function Name  : CSS_ProcMsgAsBandScanReq
 Description    : �������㷢����������FFTɨƵ����Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-10  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcMsgAsBandScanReq
(
    const CSS_AS_BAND_SCAN_REQ_STRU  *pRcvMsg
)
{
    CSS_MAIN_STATE_ENUM_UINT16          enMainState        = CSS_MAIN_STATE_BUTT;    /* ��ǰ���ڵ���״̬ */
    CSS_SUB_STATE_ENUM_UINT16           enSubState         = CSS_SS_STATE_BUTT;      /* ��ǰ���ڵ���״̬ */
    CSS_CONTROL_STRU                   *pstCssControl;

    pstCssControl = CSS_GetControlAddr();
    enMainState = CSS_GetCurMainStatus();
    enSubState  = CSS_GetCurSubStatus();

    TLPS_PRINT2LAYER_INFO1(CSS_ProcMsgAsBandScanReq_ENUM, LNAS_EMM_MAIN_STATE, enMainState);
    TLPS_PRINT2LAYER_INFO1(CSS_ProcMsgAsBandScanReq_ENUM, LNAS_EMM_SUB_STATE, enSubState);

    switch(enMainState)
    {
        case CSS_MS_IDLE:
            if (CSS_SS_IDLE == enSubState)
            {
                pstCssControl->ucScanType = CSS_SCAN_TYPE_AS_BAND_SCAN;

                /* �洢ɨƵ����Ŀռ��ͷ� */
                CSS_FreeAsScanRsltMemory();

                /* ɨƵ������Ϣ���� */
                CSS_AsBandScanReqMsgSave(pRcvMsg);

                /* ��ɨƵ������д���:�罫BANDƵ��ֶΡ������ڴ�ռ�� */
                if (CSS_SUCC != CSS_ProcAsBandScanReqest(pRcvMsg->ucRatType, &(pRcvMsg->stBandList)))
                {
                    CSS_SndMsgAsBandScanCnf(pRcvMsg->ulSenderPid,
                                            pRcvMsg->ulOpid,
                                            CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS);
                    return;
                }

                /* ��LPHY����Ϊ��ģ */
                CSS_StartTimer(&pstCssControl->stSetactiveModeTimer);
                CSS_FSMTranState(CSS_MS_SCAN, CSS_SS_WAIT_SET_WORK_ACTIVE_MODE_CNF);

                CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_ACTIVE);
            }
            /* ����Ʒû��Lģ��ʱ��LMM�����CSS�·��������󣬴�ʱ����������п���ʹ��CSS���������������������ֱ�ӻظ�ʧ�ܣ����������Ż� */
            else
            {
                CSS_SndMsgAsBandScanCnf(pRcvMsg->ulSenderPid, pRcvMsg->ulOpid, CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS);
            }
            break;

        case CSS_MS_SCAN:
            /* �����ɨƵ���������յ�ɨƵ������ֱ�ӻظ�ʧ�ܣ�ԭ��ֵΪɨƵ������ */
            TLPS_PRINT2LAYER_WARNING1(CSS_ProcMsgAsBandScanReq_ENUM, LNAS_FUNCTION_LABEL2, CSS_BAND_SCAN_FAIL_REASON_SCANING);
            CSS_SndMsgAsBandScanCnf(pRcvMsg->ulSenderPid, pRcvMsg->ulOpid, CSS_MULTI_BAND_SCAN_RESULT_FAIL_SCANING);
            break;

        case CSS_MS_STOP_SCAN:
            /* �����ֹͣɨƵ�������յ�ɨƵ������ֱ�ӻظ�ʧ�� */
            TLPS_PRINT2LAYER_WARNING1(CSS_ProcMsgAsBandScanReq_ENUM, LNAS_FUNCTION_LABEL3, CSS_BAND_SCAN_FAIL_REASON_STOP_SCANING);
            CSS_SndMsgAsBandScanCnf(pRcvMsg->ulSenderPid, pRcvMsg->ulOpid, CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS);
            break;

        default:
            TLPS_PRINT2LAYER_WARNING1(CSS_ProcMsgAsBandScanReq_ENUM, LNAS_FUNCTION_LABEL4, enMainState);
            break;
    }

    return ;
}


/*****************************************************************************
 Function Name  : CSS_ProcMsgAsStopBandScanReq
 Description    : �������㷢����������ֹͣɨƵ����Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-10  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcMsgAsStopBandScanReq(const CSS_AS_STOP_BAND_SCAN_REQ_STRU  *pRcvMsg)
{
    CSS_MAIN_STATE_ENUM_UINT16          enMainState     = CSS_MAIN_STATE_BUTT;    /* ��ǰ���ڵ���״̬ */
    CSS_SUB_STATE_ENUM_UINT16           enSubState      = CSS_SS_STATE_BUTT;     /* ��ǰ���ڵ���״̬ */
    CSS_CONTROL_STRU                   *pstCssControl;

    enMainState = CSS_GetCurMainStatus();
    enSubState = CSS_GetCurSubStatus();
    pstCssControl = CSS_GetControlAddr();

    TLPS_PRINT2LAYER_INFO1(CSS_ProcMsgAsStopBandScanReq_ENUM, LNAS_EMM_MAIN_STATE, enMainState);
    TLPS_PRINT2LAYER_INFO1(CSS_ProcMsgAsStopBandScanReq_ENUM, LNAS_EMM_SUB_STATE, enSubState);

    if (CSS_MS_IDLE == enMainState)
    {
        /* ֻ���Ѿ�������״̬�Ŵ���δ���������� */
        if (CSS_SS_IDLE == enSubState)
        {
            /* ֱ�ӻظ��ɹ� */
            CSS_SndMsgAsStopBandScanCnf(pRcvMsg->ulSenderPid, CSS_RESULT_SUCC);
        }
    }
    else if (CSS_MS_SCAN == enMainState)
    {
        /* ���COMMɨƵ�����У��յ���AS��ֹͣɨƵ������ֱ�Ӷ��� */
        if (CSS_SCAN_TYPE_AS_BAND_SCAN != pstCssControl->ucScanType)
        {
            return;
        }
        CSS_AsStopBandScanReqMsgSave(pRcvMsg);

        if (CSS_SS_WAIT_SET_WORK_ACTIVE_MODE_CNF == enSubState)
        {
            /* �����ǰ���ڵȴ�������ģ�ظ���״̬��ֱ��֪ͨLPHY���ô�ģ */
            CSS_StopTimer(&pstCssControl->stSetactiveModeTimer);
            CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);

            CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

            CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);
        }
        else if (CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF == enSubState)
        {
            /* �����ǰ���ڵȴ����ô�ģ�ظ���״̬����ֱ��Ǩ��״̬��STOP+WAIT_SET_WORK_INACTIVE_MODE_CNF */
            CSS_GetCurMainStatus() = CSS_MS_STOP_SCAN;
        }
        else if (CSS_SS_WAIT_BAND_SCAN_IND == enSubState)
        {
            /* �����ǰ���ڵȴ�ɨƵ���ʱ����Ҫ��֪ͨLPHYֹͣɨƵ��Ǩ��״̬ */
            CSS_StopTimer(&pstCssControl->stBandScanIndTimer);
            CSS_StartTimer(&pstCssControl->stStopBandScanTimer);

            CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_STOP_SCAN_CNF);

            CSS_SndLphyMsgStopBandScanReq();
        }
        else if (CSS_SS_WAIT_START_BG_SRCH_CNF == enSubState)
        {
            /* ֹͣ�ȴ������Ѷ�ʱ�� */
            CSS_StopTimer(&pstCssControl->stStartBGSTimer);

            /* ֪ͨ�����ֹͣ������ */
            CSS_SndLphyMsgStopBgSearchReq();

            /* ת��STOP_SCAN+WAIT_INACTIVE_CNF״̬ */
            CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

            /* ������ʱ�� */
            CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);

            /* ��Ҫ֪ͨLPHY���ô�ģ���յ��ظ��󣬻ظ�ֹͣɨƵ�ɹ� */
            CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);
        }
       else
       {
            /* ����coverity�Ⱦ�̬���淶 */
       }
    }
    else
    {
        /* ֹͣɨƵ�����У����յ�ֹͣɨƵ��Ϣ����ֱ�Ӷ��� */
    }
    return ;
}


/*****************************************************************************
 Function Name  : CSS_ProcCommMsgBandScanReq()
 Description    : ID_CSS_MULTI_BAND_SCAN_REQ��Ϣ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcCommMsgBandScanReq
(
    const CSS_MULTI_BAND_SCAN_REQ_STRU  *pRcvMsg
)
{
    CSS_MAIN_STATE_ENUM_UINT16          enMainState        = CSS_MAIN_STATE_BUTT;    /* ��ǰ���ڵ���״̬ */
    CSS_SUB_STATE_ENUM_UINT16           enSubState         = CSS_SS_STATE_BUTT;      /* ��ǰ���ڵ���״̬ */
    CSS_CONTROL_STRU                   *pstCssControl;

    pstCssControl = CSS_GetControlAddr();
    enMainState = CSS_GetCurMainStatus();
    enSubState  = CSS_GetCurSubStatus();

    TLPS_PRINT2LAYER_INFO1(CSS_ProcCommMsgBandScanReq_ENUM, LNAS_BandScanType, pRcvMsg->enBandScanType);
    TLPS_PRINT2LAYER_INFO1(CSS_ProcCommMsgBandScanReq_ENUM, LNAS_EMM_MAIN_STATE, enMainState);
    TLPS_PRINT2LAYER_INFO1(CSS_ProcCommMsgBandScanReq_ENUM, LNAS_EMM_SUB_STATE, enSubState);

    switch(enMainState)
    {
        case CSS_MS_IDLE:
            if (CSS_SS_IDLE == enSubState)
            {
                /*�ֲ�֧��MCCɨƵ����*/
                if (CSS_BAND_SCAN_MCC_BASED == pRcvMsg->enBandScanType)
                {
                    CSS_WARN_LOG1("CSS_ProcCommMsgBandScanReq:not support MCC scan ",CSS_BAND_SCAN_FAIL_REASON_TYPE_NOT_SUPPORT);
                    TLPS_PRINT2LAYER_WARNING1(CSS_ProcCommMsgBandScanReq_ENUM, LNAS_FUNCTION_LABEL1, CSS_BAND_SCAN_FAIL_REASON_TYPE_NOT_SUPPORT);
                    CSS_SndCommMsgBandScanCnf(pRcvMsg->ulSenderPid, pRcvMsg->ulOpid, CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS);
                    return;
                }
                pstCssControl->ucScanType = CSS_SCAN_TYPE_MULTI_BAND_SCAN;

                /* �洢ɨƵ����Ŀռ��ͷ� */
                CSS_FreeCommScanRsltMemory();

                /* ɨƵ������Ϣ���� */
                CSS_CommBandScanReqMsgSave(pRcvMsg);

                /* ��ɨƵ������д���:�罫BANDƵ��ֶΡ������ڴ�ռ�� */
                if (CSS_SUCC != CSS_ProcBandScanReqest())
                {
                    CSS_SndCommMsgBandScanCnf(pstCssControl->stCommMsg.ulReceiverPid,
                                              pstCssControl->stCommMsg.ulOpid,
                                              CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS);
                    return;
                }

                /* ԭ��ֵ��0 */
                pstCssControl->ucBandScanRslt = CSS_MULTI_BAND_SCAN_RESULT_SUCC;

                /* ��LPHY����Ϊ��ģ */
                CSS_StartTimer(&pstCssControl->stSetactiveModeTimer);
                CSS_FSMTranState(CSS_MS_SCAN, CSS_SS_WAIT_SET_WORK_ACTIVE_MODE_CNF);

                CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_ACTIVE);
            }
            /* ����Ʒû��Lģ��ʱ��LMM�����CSS�·��������󣬴�ʱ����������п���ʹ��CSS���������������������ֱ�ӻظ�ʧ�ܣ����������Ż� */
            else
            {
                CSS_SndCommMsgBandScanCnf(pRcvMsg->ulSenderPid, pRcvMsg->ulOpid, CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS);
            }
            break;

        case CSS_MS_SCAN:
            /* �����ɨƵ���������յ�ɨƵ������ֱ�ӻظ�ʧ�ܣ�ԭ��ֵΪɨƵ������ */
            CSS_WARN_LOG1("CSS_ProcCommMsgBandScanReq FAIL band scaning ", CSS_BAND_SCAN_FAIL_REASON_SCANING);
            TLPS_PRINT2LAYER_WARNING1(CSS_ProcCommMsgBandScanReq_ENUM, LNAS_FUNCTION_LABEL2, CSS_BAND_SCAN_FAIL_REASON_SCANING);
            CSS_SndCommMsgBandScanCnf(pRcvMsg->ulSenderPid, pRcvMsg->ulOpid, CSS_MULTI_BAND_SCAN_RESULT_FAIL_SCANING);
            break;

        case CSS_MS_STOP_SCAN:
            /* �����ֹͣɨƵ�������յ�ɨƵ������ֱ�ӻظ�ʧ�� */
            CSS_WARN_LOG1("CSS_ProcCommMsgBandScanReq FAIL stop band scaning ", CSS_BAND_SCAN_FAIL_REASON_STOP_SCANING );
            TLPS_PRINT2LAYER_WARNING1(CSS_ProcCommMsgBandScanReq_ENUM, LNAS_FUNCTION_LABEL3, CSS_BAND_SCAN_FAIL_REASON_STOP_SCANING);
            CSS_SndCommMsgBandScanCnf(pRcvMsg->ulSenderPid, pRcvMsg->ulOpid, CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS);
            break;

        default:
            CSS_WARN_LOG("CSS_ProcCommMsgBandScanReq FAIL stop band scaning, enMainState= ");
            TLPS_PRINT2LAYER_WARNING(CSS_ProcCommMsgBandScanReq_ENUM, LNAS_FUNCTION_LABEL4);
            break;
    }

    return ;
}
/*****************************************************************************
 Function Name  : CSS_ProcCommMsgStopBandScanReq()
 Description    : ID_CSS_STOP_BAND_SCAN_REQ��Ϣ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcCommMsgStopBandScanReq
(
    const CSS_STOP_BAND_SCAN_REQ_STRU *pstStopBandScanReq
)
{
    CSS_MAIN_STATE_ENUM_UINT16  enMainState     = CSS_MAIN_STATE_BUTT;    /* ��ǰ���ڵ���״̬ */
    CSS_SUB_STATE_ENUM_UINT16   enSubState      = CSS_SS_STATE_BUTT;     /* ��ǰ���ڵ���״̬ */
    CSS_CONTROL_STRU                   *pstCssControl;

    enMainState = CSS_GetCurMainStatus();
    enSubState = CSS_GetCurSubStatus();
    pstCssControl = CSS_GetControlAddr();

    TLPS_PRINT2LAYER_INFO1(CSS_ProcCommMsgStopBandScanReq_ENUM, LNAS_EMM_MAIN_STATE, enMainState);
    TLPS_PRINT2LAYER_INFO1(CSS_ProcCommMsgStopBandScanReq_ENUM, LNAS_EMM_SUB_STATE, enSubState);

    if (CSS_MS_IDLE == enMainState)
    {
        /* ֻ���Ѿ�������״̬�Ŵ���δ���������� */
        if (CSS_SS_IDLE == enSubState)
        {
            /* ֱ�ӻظ��ɹ� */
            CSS_SndCommMsgStopBandScanCnf(pstStopBandScanReq->ulSenderPid, CSS_RESULT_SUCC);
        }
    }
    else if (CSS_MS_SCAN == enMainState)
    {
        /* ���ASɨƵ�����У��յ���COMM��ֹͣɨƵ������ֱ�Ӷ��� */
        if (CSS_SCAN_TYPE_MULTI_BAND_SCAN != pstCssControl->ucScanType)
        {
            return;
        }
        if (CSS_SS_WAIT_SET_WORK_ACTIVE_MODE_CNF == enSubState)
        {
            /* �����ǰ���ڵȴ�������ģ�ظ���״̬��ֱ��֪ͨLPHY���ô�ģ */
            CSS_StopTimer(&pstCssControl->stSetactiveModeTimer);
            CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);

            CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

            CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);

            CSS_StopBandScanReqMsgSave(pstStopBandScanReq);
        }
        else if (CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF == enSubState)
        {
            /* �����ǰ���ڵȴ����ô�ģ�ظ���״̬����ֱ��Ǩ��״̬��STOP+WAIT_SET_WORK_INACTIVE_MODE_CNF */
            CSS_GetCurMainStatus() = CSS_MS_STOP_SCAN;

            CSS_StopBandScanReqMsgSave(pstStopBandScanReq);
        }
        else if (CSS_SS_WAIT_BAND_SCAN_IND == enSubState)
        {
            /* �����ǰ���ڵȴ�ɨƵ���ʱ����Ҫ��֪ͨLPHYֹͣɨƵ��Ǩ��״̬ */
            CSS_StopTimer(&pstCssControl->stBandScanIndTimer);
            CSS_StartTimer(&pstCssControl->stStopBandScanTimer);

            CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_STOP_SCAN_CNF);

            CSS_SndLphyMsgStopBandScanReq();

            CSS_StopBandScanReqMsgSave(pstStopBandScanReq);
        }
        else if (CSS_SS_WAIT_START_BG_SRCH_CNF == enSubState)
        {
            /* ֹͣ�ȴ������Ѷ�ʱ�� */
            CSS_StopTimer(&pstCssControl->stStartBGSTimer);

            /* ֪ͨ�����ֹͣ������ */
            CSS_SndLphyMsgStopBgSearchReq();

            /* ����stop��Ϣ */
            CSS_StopBandScanReqMsgSave(pstStopBandScanReq);

            /* ת��STOP_SCAN+WAIT_INACTIVE_CNF״̬ */
            CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

            /* ������ʱ�� */
            CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);

            /* ��Ҫ֪ͨLPHY���ô�ģ���յ��ظ��󣬻ظ�ֹͣɨƵ�ɹ� */
            CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);
        }
        else
        {

        }
    }
    else
    {
        /* ֹͣɨƵ�����У����յ�ֹͣɨƵ��Ϣ����ֱ�Ӷ��� */
    }
    return ;
}

/*****************************************************************************
 Function Name  : CSS_ProcCommMsg()
 Description    : LPHY��Ϣ������
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcCommMsg(const VOS_VOID *pRcvMsg)
{

    /* ������Ϣͷָ��*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* ��ȡ��Ϣͷָ��*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        case ID_CSS_MULTI_BAND_SCAN_REQ:
            CSS_ProcCommMsgBandScanReq((const CSS_MULTI_BAND_SCAN_REQ_STRU*)pRcvMsg);
            break;

        case ID_CSS_STOP_BAND_SCAN_REQ:
            CSS_ProcCommMsgStopBandScanReq((const CSS_STOP_BAND_SCAN_REQ_STRU *)pRcvMsg);
            break;
        case ID_CSS_CURR_GEO_IND:
            CSS_ProcCommMsgCurrGeoInd((const CSS_CURR_GEO_IND_STRU *)pRcvMsg);
            break;
        case ID_CSS_AS_BAND_SCAN_REQ:
            CSS_ProcMsgAsBandScanReq((const CSS_AS_BAND_SCAN_REQ_STRU *)pRcvMsg);
            break;
        case ID_CSS_AS_STOP_BAND_SCAN_REQ:
            CSS_ProcMsgAsStopBandScanReq((const CSS_AS_STOP_BAND_SCAN_REQ_STRU *)pRcvMsg);
            break;
        default:
            break;
    }

    return;
}


#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaMain.c */



