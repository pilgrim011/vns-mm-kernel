/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : CssProcLphyMsg.c
  Description     : ��C�ļ�������CSSģ���ʼ������Ϣ������ڵ�ʵ��
  History           :
     1.wangchen 00209181    2015-05-14  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "CssProcLphyMsg.h"
#include    "CssProcSrchRslt.h"
#include    "CssProcCommMsg.h"

#define    THIS_FILE_ID        PS_FILE_ID_CSSPROCLPHYMSG_C

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
 Function Name  : CSS_AssignLphyOpid
 Description    : ����CSSģ���LPHYģ����OPID
 Input          :
 Output         : pulOpid-----------------�����OPID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_AssignLphyOpid
(
    VOS_UINT16                          *pusOpid
)
{
    VOS_UINT16                           usOpid = CSS_NULL;

    /*��ȡ��ǰ���OPID*/
    usOpid = (VOS_UINT16)CSS_GetLphyCurOpid();

    /*�����δ�����ֵ��ֱ�Ӽ�1*/
    if( usOpid < CSS_MAX_OPID)
    {
        *pusOpid = usOpid + 1;
    }
    else/*����Ѿ������ֵ���ӳ�ֵ��ʼ����*/
    {
        (*pusOpid) = CSS_MIN_OPID;
    }

    CSS_SetLphyCurOpid(*pusOpid);

    CSS_INFO_LOG1("CSS_AssignLphyOpid,normal,assin opid:", (*pusOpid));
    TLPS_PRINT2LAYER_INFO1(CSS_AssignLphyOpid_ENUM, LNAS_FUNCTION_LABEL1, (*pusOpid));
}

/*****************************************************************************
 Function Name  : CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfSucc()
 Description    : �ȴ��������ģ�ظ��������յ���ģ�ظ��ɹ���Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-05-18  Draft Enact
*****************************************************************************/
VOS_VOID CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfSucc(VOS_VOID)
{
    CSS_CONTROL_STRU                   *pstCssControl = CSS_GetControlAddr();

    /* ��״̬Ǩ�����ȴ�����������״̬ */
    CSS_FSMTranState(CSS_MS_SCAN, CSS_SS_WAIT_START_BG_SRCH_CNF);

    /* ������ʱ�� */
    CSS_StartTimer(&pstCssControl->stStartBGSTimer);

    /* ֪ͨLPHY���������� */
    CSS_SndLphyMsgStartBgSearchReq();
}

/*****************************************************************************
 Function Name  : CSS_MsScanSsWaitStartBgsCnfMsgStartBgsCnfSucc()
 Description    : �ȴ���������������ѻظ��������յ����������ѻظ��ɹ���Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-05  Draft Enact
*****************************************************************************/
VOS_VOID CSS_MsScanSsWaitStartBgsCnfMsgStartBgsCnfSucc(VOS_VOID)
{
    CSS_CONTROL_STRU                   *pstCssControl;

    CSS_INFO_LOG("CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfSucc ENTER");
    TLPS_PRINT2LAYER_INFO(CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfSucc_ENUM, LNAS_ENTRY);

    pstCssControl = CSS_GetControlAddr();

    /* ���������MCCɨƵ Ŀǰ������ */
    if (CSS_BAND_SCAN_MCC_BASED == pstCssControl->stCommMsg.enBandScanType)
    {
    }
    else
    {
        /* �����ȴ������ɨƵ��ʱ�� */
        CSS_StartTimer(&pstCssControl->stBandScanIndTimer);

        /* Ǩ��״̬ */
        CSS_FSMTranState(CSS_MS_SCAN, CSS_SS_WAIT_BAND_SCAN_IND);

        /* ����ǿ���ǰ��FFTɨ */
        if (CSS_SCAN_TYPE_MULTI_BAND_SCAN == pstCssControl->ucScanType)
        {
            CSS_SndLphyMsgCommBandScanReq(  CSS_GetCommScanBandListCurrNode(),
                                            CSS_LPHY_BAND_SCAN_TYPE_IRAT,
                                            CSS_GetCommScanCurFreqRangeIdx());
        }
        else
        {
            CSS_SndLphyMsgCommBandScanReq(  CSS_GetAsScanBandListCurrNode(),
                                            CSS_LPHY_BAND_SCAN_TYPE_IRAT,
                                            CSS_GetAsScanCurFreqRangeIdx());
        }
    }
}

/*****************************************************************************
 Function Name  : CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfFail()
 Description    : �ȴ�������𱳾����յ��𱳾���ʧ����Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_MsScanSsWaitStartBgsCnfMsgStartBgsCnfFail()
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    /* ��״̬Ǩ�����ȴ�ֹͣɨƵɨƵ״̬ */
    CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

    /* ������ʱ�� */
    CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);

    /* ��Ҫ֪ͨLPHY���ô�ģ���յ��ظ��󣬻ظ�ɨƵʧ�� */
    CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);

    /* ����ǿ���ǰ��FFTɨ */
    if (CSS_SCAN_TYPE_MULTI_BAND_SCAN == pstCssControl->ucScanType)
    {
        /* �洢ɨƵ����Ŀռ��ͷ� */
        CSS_FreeCommScanRsltMemory();
    }
    else
    {
        /* �洢ɨƵ����Ŀռ��ͷ� */
        CSS_FreeAsScanRsltMemory();
    }

}

/*****************************************************************************
 Function Name  : CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfFail()
 Description    : �ȴ��������ģ�ظ��������յ���ģ�ظ�ʧ����Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfFail()
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    /* ת״̬ */
    CSS_FSMTranState(CSS_MS_IDLE, CSS_SS_IDLE);

    /* ����ǿ���ǰ��FFTɨ */
    if (CSS_SCAN_TYPE_MULTI_BAND_SCAN == pstCssControl->ucScanType)
    {
        /* �洢ɨƵ����Ŀռ��ͷ� */
        CSS_FreeCommScanRsltMemory();

        /* ���������ģʧ�ܣ���֪ͨɨƵʧ�ܣ�ֹͣ��ʱ����Ǩ��״̬ */
        CSS_SndCommMsgBandScanCnf(  pstCssControl->stCommMsg.ulReceiverPid,
                                    pstCssControl->stCommMsg.ulOpid,
                                    CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS);
    }
    else
    {
        /* �洢ɨƵ����Ŀռ��ͷ� */
        CSS_FreeAsScanRsltMemory();

        /* ���������ģʧ�ܣ���֪ͨɨƵʧ�ܣ�ֹͣ��ʱ����Ǩ��״̬ */
        CSS_SndMsgAsBandScanCnf(pstCssControl->stAsMsg.ulReceiverPid,
                                pstCssControl->stAsMsg.ulOpid,
                                CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS);
    }

}


/*****************************************************************************
 Function Name  : CSS_MsScanSsWaitInactModeCnfMsgSetInactModeCnfSucc()
 Description    : �ȴ�������д�ģ�ظ��������յ��д�ģ�ظ��ɹ���Ϣ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-05-18  Draft Enact
*****************************************************************************/
VOS_VOID CSS_MsScanSsWaitInactModeCnfMsgSetInactModeCnfSucc(VOS_VOID)
{
    CSS_CONTROL_STRU                   *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    /* ����ǿ���ǰ��FFTɨ */
    if (CSS_SCAN_TYPE_MULTI_BAND_SCAN == pstCssControl->ucScanType)
    {
        CSS_SndCommMsgBandScanCnf(  pstCssControl->stCommMsg.ulReceiverPid,
                                    pstCssControl->stCommMsg.ulOpid,
                                    CSS_MULTI_BAND_SCAN_RESULT_SUCC);

        /* �����ر����ɨƵ�������HIDS�� */
        CSS_SendOmBandScanResultInfoInd(CSS_GetCommScanBandListHeadNode(), CSS_GetCommScanBandListAddr()->ucBandCount);
    }
    else
    {
        CSS_SndMsgAsBandScanCnf(pstCssControl->stAsMsg.ulReceiverPid,
                                pstCssControl->stAsMsg.ulOpid,
                                CSS_MULTI_BAND_SCAN_RESULT_SUCC);

        /* �����ر����ɨƵ�������HIDS�� */
        CSS_SendOmBandScanResultInfoInd(CSS_GetAsScanBandListHeadNode(), CSS_GetAsScanBandListAddr()->ucBandCount);

        CSS_SndAsBandScanRslt(pstCssControl->stAsMsg.ulReceiverPid, pstCssControl->stAsMsg.ulOpid);

        /* �洢ɨƵ����Ŀռ��ͷ� */
        CSS_FreeAsScanRsltMemory();
    }

}




VOS_VOID CSS_SndLphyMsgStopBandScanReq
(
    VOS_VOID
)
{
    CSS_LPHY_STOP_BAND_SCAN_REQ_STRU *pstCssStopBandScanReq;
    VOS_UINT16                           usOpid = CSS_NULL;

    /*������Ϣ�ռ�*/
    pstCssStopBandScanReq = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_STOP_BAND_SCAN_CNF_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstCssStopBandScanReq)
    {
        /*��ӡ�쳣��Ϣ*/
        CSS_ERR_LOG("CSS_SndCommMsgStopBandScanCnf:ERROR:Alloc Msg fail!");
        return ;
    }

    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstCssStopBandScanReq),
                    CSS_GET_MSG_LENGTH(pstCssStopBandScanReq),
                    0,
                    CSS_GET_MSG_LENGTH(pstCssStopBandScanReq));

    CSS_WRITE_LPHY_MSG_HEAD(pstCssStopBandScanReq,ID_CSS_LPHY_STOP_BAND_SCAN_REQ);

    CSS_AssignLphyOpid(&usOpid);

    pstCssStopBandScanReq->usOpId = usOpid;

    /*������Ϣ���ͺ��� */
    CSS_SND_MSG(pstCssStopBandScanReq);

    return ;
}


VOS_VOID CSS_SndLphyMsgSetWorkModeReq
(
    CSS_LPHY_WORK_MODE_TYPE_ENUM_UINT16       enWorkModeType
)
{
    CSS_LPHY_SET_WORK_MODE_REQ_STRU     *pstCssSetModeInactive;
    VOS_UINT16                          usOpid = CSS_NULL;

    /*������Ϣ�ռ�*/
    pstCssSetModeInactive = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_LPHY_SET_WORK_MODE_REQ_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstCssSetModeInactive)
    {
        /*��ӡ�쳣��Ϣ*/
        CSS_ERR_LOG("CSS_SndCommMsgStopBandScanCnf:ERROR:Alloc Msg fail!");
        return ;
    }

    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstCssSetModeInactive),
                    CSS_GET_MSG_LENGTH(pstCssSetModeInactive),
                    0,
                    CSS_GET_MSG_LENGTH(pstCssSetModeInactive));

    CSS_WRITE_LPHY_MSG_HEAD(pstCssSetModeInactive,ID_CSS_LPHY_SET_WORK_MODE_REQ);

    CSS_AssignLphyOpid(&usOpid);

    pstCssSetModeInactive->usOpId = usOpid;
    pstCssSetModeInactive->enWorkModeType = enWorkModeType;

    pstCssSetModeInactive->enDsdsRfShardFlg = CSS_LPHY_DSDS_RFSHARED_ENABLE;

    /*������Ϣ���ͺ��� */
    CSS_SND_MSG(pstCssSetModeInactive);

    TLPS_PRINT2LAYER_INFO1(CSS_SndLphyMsgSetWorkModeReq_EUM, LNAS_WorkModeType, pstCssSetModeInactive->enWorkModeType);

    return ;
}


/*****************************************************************************
 Function Name  : CSS_SndLphyMsgBandScanReq
 Description    : ��LPHY����BandScan����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-05-16  Draft Enact
*****************************************************************************/
VOS_VOID CSS_SndLphyMsgCommBandScanReq
(
    CSS_COMM_SCAN_BAND_NODE_STRU               *pstBandNode,
    CSS_LPHY_BAND_SCAN_TYPE_ENUM_UINT16         enScanType,
    VOS_UINT8                                   ucCurFreqRangeIdx
)
{
    CSS_LPHY_BAND_SCAN_REQ_STRU        *pstCssBandScanReq;
    VOS_UINT16                          usOpid = CSS_NULL;

    if (VOS_NULL_PTR == pstBandNode)
    {
        /*��ӡ�쳣��Ϣ*/
        TLPS_PRINT2LAYER_WARNING(CSS_SndLphyMsgCommBandScanReq_ENUM, LNAS_BandNodeIsNULL);
        return ;
    }

    /*������Ϣ�ռ�*/
    pstCssBandScanReq = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_LPHY_BAND_SCAN_REQ_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstCssBandScanReq)
    {
        return ;
    }

    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstCssBandScanReq),
                    CSS_GET_MSG_LENGTH(pstCssBandScanReq),
                    0,
                    CSS_GET_MSG_LENGTH(pstCssBandScanReq));

    CSS_WRITE_LPHY_MSG_HEAD(pstCssBandScanReq,ID_CSS_LPHY_BAND_SCAN_REQ);

    CSS_AssignLphyOpid(&usOpid);

    pstCssBandScanReq->usOpId                       = usOpid;
    pstCssBandScanReq->enBandScanType               = enScanType;
    pstCssBandScanReq->enBandInd                    = pstBandNode->stBandInfo.ucBandInd;
    pstCssBandScanReq->enLteModeType                = CSS_GetLteModeTypeByBandInd(pstBandNode->stBandInfo.ucBandInd);
    pstCssBandScanReq->stFreqRangeInfo.usFreqBegin  = pstBandNode->stBandInfo.pstScanReqArray[ucCurFreqRangeIdx].usFreqBegin;
    pstCssBandScanReq->stFreqRangeInfo.usFreqEnd    = pstBandNode->stBandInfo.pstScanReqArray[ucCurFreqRangeIdx].usFreqEnd;
    pstCssBandScanReq->bitOpLteSupport              = pstBandNode->stBandInfo.bitOpLteSupport;
    pstCssBandScanReq->bitOpWcdmaSupport            = pstBandNode->stBandInfo.bitOpWcdmaSupport;
    pstCssBandScanReq->bitOpGsmSupport              = pstBandNode->stBandInfo.bitOpGsmSupport;
    pstCssBandScanReq->bitOpTdsSupport              = pstBandNode->stBandInfo.bitOpTdsSupport;

    /*������Ϣ���ͺ��� */
    CSS_SND_MSG(pstCssBandScanReq);

    TLPS_PRINT2LAYER_INFO1(CSS_SndLphyMsgCommBandScanReq_ENUM, LNAS_BandInd, pstCssBandScanReq->enBandInd);
    TLPS_PRINT2LAYER_INFO1(CSS_SndLphyMsgCommBandScanReq_ENUM, LNAS_FreqRangeBegin, pstCssBandScanReq->stFreqRangeInfo.usFreqBegin);
    TLPS_PRINT2LAYER_INFO1(CSS_SndLphyMsgCommBandScanReq_ENUM, LNAS_FreqRangeEnd, pstCssBandScanReq->stFreqRangeInfo.usFreqEnd);

    return ;
}


/*****************************************************************************
 Function Name  : CSS_SndLphyMsgStartBgSearchReq
 Description    : ��LPHY����start bg search����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-05  Draft Enact
*****************************************************************************/
VOS_VOID CSS_SndLphyMsgStartBgSearchReq(VOS_VOID)
{
    CSS_LPHY_START_BG_SEARCH_REQ_STRU            *pstCssStartBgsReq;
    VOS_UINT16                                    usOpid = CSS_NULL;

    TLPS_PRINT2LAYER_INFO(CSS_SndLphyMsgStartBgSearchReq_ENUM, LNAS_ENTRY);

    /*������Ϣ�ռ�*/
    pstCssStartBgsReq = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_LPHY_START_BG_SEARCH_REQ_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstCssStartBgsReq)
    {
        return ;
    }

    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstCssStartBgsReq),
                    CSS_GET_MSG_LENGTH(pstCssStartBgsReq),
                    0,
                    CSS_GET_MSG_LENGTH(pstCssStartBgsReq));

    CSS_WRITE_LPHY_MSG_HEAD(pstCssStartBgsReq,ID_CSS_LPHY_START_BG_SEARCH_REQ);

    CSS_AssignLphyOpid(&usOpid);

    pstCssStartBgsReq->usOpId                       = usOpid;
    pstCssStartBgsReq->enStartBGSearchRat           = CSS_LPHY_RAT_TYPE_LTE;
    pstCssStartBgsReq->enBsgCfgType                 = CSS_LPHY_BGSCFG_TYPE_DSDS;

    /*������Ϣ���ͺ��� */
    CSS_SND_MSG(pstCssStartBgsReq);

}

/*****************************************************************************
 Function Name  : CSS_SndLphyMsgStopBgSearchReq
 Description    : ��LPHY����stop bg search����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-05  Draft Enact
*****************************************************************************/
VOS_VOID CSS_SndLphyMsgStopBgSearchReq(VOS_VOID)
{
    CSS_LPHY_STOP_BG_SEARCH_REQ_STRU             *pstCssStopBgsReq;
    VOS_UINT16                                    usOpid = CSS_NULL;

    TLPS_PRINT2LAYER_INFO(CSS_SndLphyMsgStopBgSearchReq_ENUM, LNAS_ENTRY);

    /*������Ϣ�ռ�*/
    pstCssStopBgsReq = (VOS_VOID*)CSS_ALLOC_MSG(sizeof(CSS_LPHY_STOP_BG_SEARCH_REQ_STRU));

    /*����Ƿ����ɹ�*/
    if (VOS_NULL_PTR == pstCssStopBgsReq)
    {
        return ;
    }

    CSS_MEM_SET_S(  CSS_GET_MSG_ENTITY(pstCssStopBgsReq),
                    CSS_GET_MSG_LENGTH(pstCssStopBgsReq),
                    0,
                    CSS_GET_MSG_LENGTH(pstCssStopBgsReq));

    CSS_WRITE_LPHY_MSG_HEAD(pstCssStopBgsReq,ID_CSS_LPHY_STOP_BG_SEARCH_REQ);

    CSS_AssignLphyOpid(&usOpid);

    pstCssStopBgsReq->usOpId                       = usOpid;

    /*������Ϣ���ͺ��� */
    CSS_SND_MSG(pstCssStopBgsReq);

}


/*****************************************************************************
 Function Name  : CSS_ProcLphyMsgScanIndForCommScan
 Description    : ID_CSS_LPHY_BAND_SCAN_IND��Ϣ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcLphyMsgScanIndForCommScan
(
    const CSS_LPHY_BAND_SCAN_IND_STRU *pRcvMsg
)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    /*����ϱ���BAND�Ƿ�͵�ǰ���ڴ����BAND�Ƿ�һ��*/
    if (pRcvMsg->stBandScanResult.enBandInd != CSS_GetCommScanBandListCurrNode()->stBandInfo.ucBandInd)
    {
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgScanIndForCommScan_ENUM, LNAS_WrongBand);
        return;
    }

    CSS_StopTimer(&pstCssControl->stBandScanIndTimer);

    TLPS_PRINT2LAYER_INFO1(CSS_ProcLphyMsgScanIndForCommScan_ENUM, LNAS_BandInd, pRcvMsg->stBandScanResult.enBandInd);
    TLPS_PRINT2LAYER_INFO1(CSS_ProcLphyMsgScanIndForCommScan_ENUM, LNAS_FreqRangeNum, pRcvMsg->stBandScanResult.usFreqRangeNum);

    /*��������쳣�����򷵻�*/
    if (CSS_CAUSE_NULL_PTR == CSS_ProcLphyBandScanRsltForCommScan(&(pRcvMsg->stBandScanResult)))
    {
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgScanIndForCommScan_ENUM, LNAS_BandNodeIsNULL);
        return;
    }

    /*�ж��Ƿ���Ҫ������һ��ɨƵ*/
    if (CSS_TRUE == CSS_IsCommScanNeedSndLphyNextBandScanReq())
    {
        CSS_StartTimer(&pstCssControl->stBandScanIndTimer);
        CSS_SndLphyMsgCommBandScanReq(CSS_GetCommScanBandListCurrNode(),
                                          CSS_LPHY_BAND_SCAN_TYPE_IRAT,
                                          CSS_GetCommScanCurFreqRangeIdx());
    }
    /*���е�Ƶ�㶼ɨ���ˣ��˴��к�������ת״̬����������*/
    else
    {
        /* ֪ͨ�����ֹͣ������ */
        CSS_SndLphyMsgStopBgSearchReq();

        /* ��LPHY����Ϊ��ģ */
        CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);

        CSS_FSMTranState(CSS_MS_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

        CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);

    }

    /* print */
    TLPS_PRINT2LAYER_INFO2(CSS_ProcLphyMsgScanInd_ENUM, LNAS_BandInd, pRcvMsg->stBandScanResult.enBandInd,1);
    TLPS_PRINT2LAYER_INFO2(CSS_ProcLphyMsgScanInd_ENUM, LNAS_FreqRangeNum, pRcvMsg->stBandScanResult.usFreqRangeNum,1);
}

/*****************************************************************************
 Function Name  : CSS_ProcLphyMsgScanIndForAsScan
 Description    : ID_CSS_LPHY_BAND_SCAN_IND��Ϣ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcLphyMsgScanIndForAsScan
(
    const CSS_LPHY_BAND_SCAN_IND_STRU *pRcvMsg
)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    /*����ϱ���BAND�Ƿ�͵�ǰ���ڴ����BAND�Ƿ�һ��*/
    if (pRcvMsg->stBandScanResult.enBandInd != CSS_GetAsScanBandListCurrNode()->stBandInfo.ucBandInd)
    {
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgScanIndForAsScan_ENUM, LNAS_WrongBand);
        return;
    }

    CSS_StopTimer(&pstCssControl->stBandScanIndTimer);

    TLPS_PRINT2LAYER_INFO1(CSS_ProcLphyMsgScanIndForAsScan_ENUM, LNAS_BandInd, pRcvMsg->stBandScanResult.enBandInd);
    TLPS_PRINT2LAYER_INFO1(CSS_ProcLphyMsgScanIndForAsScan_ENUM, LNAS_FreqRangeNum, pRcvMsg->stBandScanResult.usFreqRangeNum);

    /*��������쳣�����򷵻�*/
    if (CSS_CAUSE_NULL_PTR == CSS_ProcLphyBandScanRsltForAsScan(&(pRcvMsg->stBandScanResult)))
    {
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgScanIndForAsScan_ENUM, LNAS_BandNodeIsNULL);
        return;
    }

    /*�ж��Ƿ���Ҫ������һ��ɨƵ*/
    if (CSS_TRUE == CSS_IsAsScanNeedSndLphyNextBandScanReq())
    {
        CSS_StartTimer(&pstCssControl->stBandScanIndTimer);
        CSS_SndLphyMsgCommBandScanReq(  CSS_GetAsScanBandListCurrNode(),
                                        CSS_LPHY_BAND_SCAN_TYPE_IRAT,
                                        CSS_GetAsScanCurFreqRangeIdx());
    }
    /*���е�Ƶ�㶼ɨ���ˣ��˴��к�������ת״̬����������*/
    else
    {
        /* ֪ͨ�����ֹͣ������ */
        CSS_SndLphyMsgStopBgSearchReq();

        /* ��LPHY����Ϊ��ģ */
        CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);

        CSS_FSMTranState(CSS_MS_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

        CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);

    }

    /* print */
    TLPS_PRINT2LAYER_INFO2(CSS_ProcLphyMsgScanIndForAsScan_ENUM, LNAS_BandInd, pRcvMsg->stBandScanResult.enBandInd,1);
    TLPS_PRINT2LAYER_INFO2(CSS_ProcLphyMsgScanIndForAsScan_ENUM, LNAS_FreqRangeNum, pRcvMsg->stBandScanResult.usFreqRangeNum,1);
}


/*****************************************************************************
 Function Name  : CSS_ProcLphyMsgScanInd()
 Description    : ID_CSS_LPHY_BAND_SCAN_IND��Ϣ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcLphyMsgScanInd
(
    const CSS_LPHY_BAND_SCAN_IND_STRU *pRcvMsg
)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    /* ���OPID��ƥ�䣬��ֱ���˳� */
    if (pstCssControl->ulCssLphyOpid != pRcvMsg->usOpId)
    {
        /*��ӡ������Ϣ*/
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgScanInd_ENUM, LNAS_OpidMismatch);
        return;
    }

    /*���״̬�Ƿ�ƥ�䣬����ƥ�䣬�˳�*/
    if (CSS_MS_SCAN != CSS_GetCurMainStatus() || CSS_SS_WAIT_BAND_SCAN_IND != CSS_GetCurSubStatus())
    {
        /*��ӡ������Ϣ*/
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgScanInd_ENUM, LNAS_STATE_ERR);
        return;
    }

    if (VOS_TRUE == pRcvMsg->usNoRfValid)
    {
        TLPS_PRINT2LAYER_INFO(CSS_ProcLphyMsgScanInd_ENUM, LNAS_CSS_SCAN_RSLT_NO_RF);

        CSS_StopTimer(&pstCssControl->stBandScanIndTimer);

        /* ֪ͨ�����ֹͣ������ */
        CSS_SndLphyMsgStopBgSearchReq();

        /* ת��STOP_SCAN+WAIT_INACTIVE_CNF״̬ */
        CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

        /* ������ʱ�� */
        CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);

        /* ��Ҫ֪ͨLPHY���ô�ģ���յ��ظ��󣬻ظ�ɨƵʧ�� */
        CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);

        /* ԭ��ֵ��NO_RF */
        pstCssControl->ucBandScanRslt = CSS_MULTI_BAND_SCAN_RESULT_NO_RF;

        return;
    }

    /* ����ǿ���ǰ��FFTɨ */
    if (CSS_SCAN_TYPE_MULTI_BAND_SCAN == pstCssControl->ucScanType)
    {
        CSS_ProcLphyMsgScanIndForCommScan(pRcvMsg);
    }
    else
    {
        CSS_ProcLphyMsgScanIndForAsScan(pRcvMsg);
    }

    return ;
}

/*****************************************************************************
 Function Name  : CSS_ProcLphyMsgStopScanCnf()
 Description    : ID_CSS_LPHY_STOP_BAND_SCAN_CNF��Ϣ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcLphyMsgStopScanCnf
(
    const CSS_LPHY_STOP_BAND_SCAN_CNF_STRU  *pRcvMsg
)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    /* ���OPIDƥ�䲻�ɹ�����ֱ�Ӷ��� */
    if (CSS_GetLphyCurOpid() != pRcvMsg->usOpId)
    {
        CSS_WARN_LOG("CSS_ProcLphyMsgStopScanCnf opid mismatch ");
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgStopScanCnf_ENUM, LNAS_OpidMismatch);
        return;
    }

    /* ֹͣ��ʱ�� */
    CSS_StopTimer(&pstCssControl->stStopBandScanTimer);

    /* ���ֹͣɨƵʧ�ܣ���ֱ�ӵ��õ���ӿڸ�λ */
    if(CSS_LPHY_RESULT_FAIL == pRcvMsg->enStopBandScanRslt)
    {
        CSS_ClearLocalResource();

        /* ���ô�ģʧ�ܣ����õ���ӿڣ�ֱ�Ӹ�λ */
        (VOS_VOID)LPS_SoftReBoot_WithLineNoAndFileID( CSS_REBOOT_TYPE_STOP_SCAN_FAIL, (__LINE__), (THIS_FILE_ID) );

        return ;
    }

    /* ���OPIDƥ��ɹ�����״̬ΪSTOP_SCAN+CSS_SS_WAIT_STOP_SCAN_CNF,����Ҫ��LPHY����Ϊ��ģ */
    if ((CSS_MS_STOP_SCAN == CSS_GetCurMainStatus()) && (CSS_SS_WAIT_STOP_SCAN_CNF == CSS_GetCurSubStatus()))
    {
        /* ֪ͨ�����ֹͣ������ */
        CSS_SndLphyMsgStopBgSearchReq();

        /* ��LPHY����Ϊ��ģ */
        CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);
        CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

        CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);

    }

    return ;
}
/*****************************************************************************
 Function Name  : CSS_ProcLphyMsgSetModeCnf()
 Description    : ID_CSS_LPHY_SET_WORK_MODE_CNF��Ϣ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_MsScanProcLphyMsgSetModeCnf
(
    const CSS_LPHY_SET_WORK_MODE_CNF_STRU   *pstSetModeCnf
)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    if (CSS_SS_WAIT_SET_WORK_ACTIVE_MODE_CNF == CSS_GetCurSubStatus())
    {
        CSS_StopTimer(&pstCssControl->stSetactiveModeTimer);

        if (CSS_LPHY_RESULT_SUCC == pstSetModeCnf->enWorkModeCfgRslt)
        {
            CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfSucc();
        }
        else
        {
            CSS_MsScanSsWaitActModeCnfMsgSetActModeCnfFail();
        }
    }
    else if (CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF == CSS_GetCurSubStatus())
    {
        CSS_StopTimer(&pstCssControl->stSetInactiveModeTimer);

        /* �����ɨƵ�������յ����ô�ģ�Ļظ�����Ҫ��GUNAS/AS����ɨƵ��� */
        /* ������ô�ģʧ�ܣ���ֱ�Ӹ�λ */
        if (CSS_LPHY_RESULT_FAIL == pstSetModeCnf->enWorkModeCfgRslt)
        {
            CSS_ClearLocalResource();

            /* ���ô�ģʧ�ܣ����õ���ӿڣ�ֱ�Ӹ�λ */
            (VOS_VOID)LPS_SoftReBoot_WithLineNoAndFileID( CSS_REBOOT_TYPE_SET_INACTIVE_MODE_FAIL, (__LINE__), (THIS_FILE_ID) );

            return;
        }

        /* ��GUNSA/AS����ɨƵ��� */
        CSS_FSMTranState(CSS_MS_IDLE, CSS_SS_IDLE);
        CSS_MsScanSsWaitInactModeCnfMsgSetInactModeCnfSucc();
    }
}
/*****************************************************************************
 Function Name  : CSS_ProcLphyMsgSetModeCnf()
 Description    : ID_CSS_LPHY_SET_WORK_MODE_CNF��Ϣ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcLphyMsgSetModeCnf
(
    const CSS_LPHY_SET_WORK_MODE_CNF_STRU   *pstSetModeCnf
)
{
    CSS_MAIN_STATE_ENUM_UINT16          enMainState;    /* ��ǰ���ڵ���״̬ */
    CSS_SUB_STATE_ENUM_UINT16           enSubState;     /* ��ǰ���ڵ���״̬ */
    CSS_CONTROL_STRU                   *pstCssControl;
    VOS_UINT8                           ucTmpFailRslt;

    pstCssControl = CSS_GetControlAddr();

    enMainState = CSS_GetCurMainStatus();
    enSubState = CSS_GetCurSubStatus();

    /* ���OPIDƥ�䲻�ɹ�����ֱ�Ӷ��� */
    if (CSS_GetLphyCurOpid() != pstSetModeCnf->usOpId)
    {
        CSS_WARN_LOG("CSS_ProcLphyMsgSetModeCnf opid mismatch");
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgSetModeCnf_ENUM, LNAS_OpidMismatch);
        return;
    }

    /* �����״̬��ɨƵ����������ģ�ɹ������LPHY����ɨƵ���� */
    if (CSS_MS_SCAN == enMainState)
    {
        CSS_MsScanProcLphyMsgSetModeCnf(pstSetModeCnf);
    }
    else if ((CSS_MS_STOP_SCAN == enMainState) && (CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF == enSubState))
    {
        /* ֹͣ��ʱ�� */
        CSS_StopTimer(&pstCssControl->stSetInactiveModeTimer);

        /* ������ô�ģʧ�ܣ���ֱ�Ӹ�λ */
        if (CSS_LPHY_RESULT_FAIL == pstSetModeCnf->enWorkModeCfgRslt)
        {
            CSS_ClearLocalResource();

            /* ���ô�ģʧ�ܣ����õ���ӿڣ�ֱ�Ӹ�λ */
            (VOS_VOID)LPS_SoftReBoot_WithLineNoAndFileID( CSS_REBOOT_TYPE_SET_INACTIVE_MODE_FAIL, (__LINE__), (THIS_FILE_ID) );

            return;
        }

        /* �����״̬���������: GUNAS/AS֪ͨCSSģ��ֹͣɨƵ��������ɨƵ�����У������쳣��CSSģ������֪ͨLPHYֹͣɨƵ */
        /* ����������Ϣ��ֹͣɨƵ����ֱ�ӻظ�ֹͣɨƵ�ɹ� */
        /* �����ɨƵ�����г����쳣����ظ�ɨƵʧ�� */
        CSS_FSMTranState(CSS_MS_IDLE, CSS_SS_IDLE);

        if (CSS_MULTI_BAND_SCAN_RESULT_NO_RF == pstCssControl->ucBandScanRslt)
        {
            ucTmpFailRslt = CSS_MULTI_BAND_SCAN_RESULT_NO_RF;
        }
        else
        {
            ucTmpFailRslt = CSS_MULTI_BAND_SCAN_RESULT_FAIL_OTHERS;
        }
        if (CSS_SCAN_TYPE_MULTI_BAND_SCAN == pstCssControl->ucScanType)
        {
            if ((CSS_OP_TRUE == pstCssControl->stCommMsg.bitOpSaveMsg)
                && (ID_CSS_MULTI_BAND_SCAN_REQ == pstCssControl->stCommMsg.enMsgId))
            {
                CSS_SndCommMsgBandScanCnf(  pstCssControl->stCommMsg.ulReceiverPid,
                                            pstCssControl->stCommMsg.ulOpid,
                                            ucTmpFailRslt);
            }

            if ((CSS_OP_TRUE == pstCssControl->stCommMsg.bitOpSaveMsg)
                    && (ID_CSS_STOP_BAND_SCAN_REQ == pstCssControl->stCommMsg.enMsgId))
            {
                CSS_SndCommMsgStopBandScanCnf(  pstCssControl->stCommMsg.ulReceiverPid,
                                                CSS_RESULT_SUCC );
            }
            /* ֹͣɨƵ����ɨƵ�������쳣����Ҫ���洢ɨƵ����Ŀռ��ͷ� */
            CSS_FreeCommScanRsltMemory();
        }
        else
        {
            if ((CSS_OP_TRUE == pstCssControl->stAsMsg.ulIsSaveMsg)
                && (ID_CSS_AS_BAND_SCAN_REQ == pstCssControl->stAsMsg.ulMsgId))
            {
                CSS_SndMsgAsBandScanCnf(pstCssControl->stAsMsg.ulReceiverPid,
                                        pstCssControl->stAsMsg.ulOpid,
                                        ucTmpFailRslt);
            }

            if ((CSS_OP_TRUE == pstCssControl->stAsMsg.ulIsSaveMsg)
                    && (ID_CSS_AS_STOP_BAND_SCAN_REQ == pstCssControl->stAsMsg.ulMsgId))
            {
                CSS_SndMsgAsStopBandScanCnf(pstCssControl->stAsMsg.ulReceiverPid,
                                            CSS_RESULT_SUCC );
            }
            /* ֹͣɨƵ����ɨƵ�������쳣����Ҫ���洢ɨƵ����Ŀռ��ͷ� */
            CSS_FreeAsScanRsltMemory();
        }

        /* ԭ��ֵ��0 */
        pstCssControl->ucBandScanRslt = CSS_MULTI_BAND_SCAN_RESULT_SUCC;
    }

    return ;
}

/*****************************************************************************
 Function Name  : CSS_ProcLphyMsgStartBgSearchCnf()
 Description    : ID_CSS_LPHY_START_BG_SEARCH_CNF��Ϣ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-05  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcLphyMsgStartBgSearchCnf
(
    const CSS_LPHY_START_BG_SEARCH_CNF_STRU  *pRcvMsg
)
{
    CSS_MAIN_STATE_ENUM_UINT16                    enMainState;    /* ��ǰ���ڵ���״̬ */
    CSS_SUB_STATE_ENUM_UINT16                     enSubState;     /* ��ǰ���ڵ���״̬ */
    CSS_CONTROL_STRU                             *pstCssControl;

    pstCssControl = CSS_GetControlAddr();

    enMainState = CSS_GetCurMainStatus();
    enSubState = CSS_GetCurSubStatus();

    TLPS_PRINT2LAYER_INFO(CSS_ProcLphyMsgStartBgSearchCnf_ENUM, LNAS_ENTRY);

    /* ���OPIDƥ�䲻�ɹ�����ֱ�Ӷ��� */
    if (CSS_GetLphyCurOpid() != pRcvMsg->usOpId)
    {
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgStartBgSearchCnf_ENUM, LNAS_OpidMismatch);
        return;
    }

    /* �����״̬��ɨƵ����״̬�ǵȴ��������ѻظ� */
    if ((CSS_MS_SCAN == enMainState) && (CSS_SS_WAIT_START_BG_SRCH_CNF == enSubState))
    {
        /* ֹͣ��ʱ�� */
        CSS_StopTimer(&pstCssControl->stStartBGSTimer);

        if (CSS_LPHY_RESULT_SUCC == pRcvMsg->enResult)
        {
            CSS_MsScanSsWaitStartBgsCnfMsgStartBgsCnfSucc();
        }
        else
        {
            CSS_MsScanSsWaitStartBgsCnfMsgStartBgsCnfFail();
        }
    }
}
/*****************************************************************************
 Function Name  : CSS_ProcLphyMsgStopBgSearchCnf()
 Description    : ID_CSS_LPHY_STOP_BG_SEARCH_CNF��Ϣ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-05  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcLphyMsgStopBgSearchCnf
(
    const CSS_LPHY_STOP_BG_SEARCH_CNF_STRU  *pRcvMsg
)
{
    TLPS_PRINT2LAYER_INFO(CSS_ProcLphyMsgStopBgSearchCnf_ENUM, LNAS_ENTRY);

    /* ���OPIDƥ�䲻�ɹ�����ֱ�Ӷ��� */
    if (CSS_GetLphyCurOpid() != pRcvMsg->usOpId)
    {
        TLPS_PRINT2LAYER_WARNING(CSS_ProcLphyMsgStopBgSearchCnf_ENUM, LNAS_OpidMismatch);
        return;
    }
}





/*****************************************************************************
 Function Name  : CSS_ProcLphyMsg()
 Description    : LPHY��Ϣ������
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcLphyMsg(const VOS_VOID *pRcvMsg )
{
    /* ������Ϣͷָ��*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* ��ȡ��Ϣͷָ��*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        case ID_CSS_LPHY_BAND_SCAN_IND:
            CSS_ProcLphyMsgScanInd((const CSS_LPHY_BAND_SCAN_IND_STRU *)pRcvMsg);
            break;

        case ID_CSS_LPHY_STOP_BAND_SCAN_CNF:
            CSS_ProcLphyMsgStopScanCnf((const CSS_LPHY_STOP_BAND_SCAN_CNF_STRU *)pRcvMsg);
            break;

        case ID_CSS_LPHY_SET_WORK_MODE_CNF:
            CSS_ProcLphyMsgSetModeCnf((const CSS_LPHY_SET_WORK_MODE_CNF_STRU *)pRcvMsg);
            break;
        case ID_CSS_LPHY_START_BG_SEARCH_CNF:
            CSS_ProcLphyMsgStartBgSearchCnf((const CSS_LPHY_START_BG_SEARCH_CNF_STRU *)pRcvMsg);
            break;
        case ID_CSS_LPHY_STOP_BG_SEARCH_CNF:
            CSS_ProcLphyMsgStopBgSearchCnf((const CSS_LPHY_STOP_BG_SEARCH_CNF_STRU *)pRcvMsg);
            break;

        default:
            break;
    }
}

#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif




