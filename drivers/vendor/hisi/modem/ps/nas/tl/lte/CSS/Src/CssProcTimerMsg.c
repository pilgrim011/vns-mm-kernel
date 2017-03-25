/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : CssProcTimerMsg.c
  Description     : ��C�ļ�������CSSģ���ʼ������Ϣ������ڵ�ʵ��
  History           :
     1.wangchen 00209181    2015-05-14  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "CssProcTimerMsg.h"
#include    "CssProcLphyMsg.h"
#include    "CssProcCommMsg.h"
#include    "CssCloudStrategyPublic.h"

#define    THIS_FILE_ID        PS_FILE_ID_CSSPROCTIMERMSG_C

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
 Function Name  : CSS_ProcSetInactiveModeTimerExp()
 Description    : TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF��ʱ����ʱ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcSetInactiveModeTimerExp
(
    VOS_VOID
)
{
    TLPS_PRINT2LAYER_INFO(CSS_ProcSetInactiveModeTimerExp_ENUM, LNAS_ENTRY);

    CSS_ClearLocalResource();

    /* ���ô�ģʧ�ܣ����õ���ӿڣ�ֱ�Ӹ�λ */
    (VOS_VOID)LPS_SoftReBoot_WithLineNoAndFileID( CSS_REBOOT_TYPE_SET_INACTIVE_MODE_TIMEOUT, (__LINE__), (THIS_FILE_ID) );
    return ;
}

/*****************************************************************************
 Function Name  : CSS_ProcSetActiveModeTimerExp()
 Description    : TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF��ʱ����ʱ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcSetActiveModeTimerExp
(
    VOS_VOID
)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    TLPS_PRINT2LAYER_INFO(CSS_ProcSetActiveModeTimerExp_ENUM, LNAS_TIMER_EXPIRED);

    pstCssControl = CSS_GetControlAddr();

    /* ��״̬Ǩ�����ȴ�ֹͣɨƵɨƵ״̬ */
    CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

    /* ������ʱ�� */
    CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);

     /* ��Ҫ֪ͨLPHY���ô�ģ���յ��ظ��󣬻ظ�ɨƵʧ�� */
    CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);

    return ;
}
/*****************************************************************************
 Function Name  : CSS_ProcBandScanTimerExp()
 Description    : TI_CSS_WAIT_FOR_SCAN_IND��ʱ����ʱ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcBandScanTimerExp
(
    VOS_VOID
)
{
    CSS_CONTROL_STRU                        *pstCssControl;

    TLPS_PRINT2LAYER_INFO(CSS_ProcBandScanTimerExp_ENUM, LNAS_TIMER_EXPIRED);

    pstCssControl = CSS_GetControlAddr();

    /* ��״̬Ǩ�����ȴ�ֹͣɨƵɨƵ״̬ */
    CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_STOP_SCAN_CNF);

    /* ������ʱ�� */
    CSS_StartTimer(&pstCssControl->stStopBandScanTimer);

    /* ��Ҫ֪ͨLPHYֹͣɨƵ�������ô�ģ���յ��ظ��󣬻ظ�ɨƵʧ�� */
    CSS_SndLphyMsgStopBandScanReq();

    return ;
}
/*****************************************************************************
 Function Name  : CSS_ProcStopBandScanTimerExp()
 Description    : TI_CSS_WAIT_FOR_STOP_SCAN_CNF��ʱ����ʱ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcStopBandScanTimerExp
(
    VOS_VOID
)
{
    TLPS_PRINT2LAYER_INFO(CSS_ProcStopBandScanTimerExp_ENUM, LNAS_TIMER_EXPIRED);

    CSS_ClearLocalResource();

    /* ֹͣɨƵʧ�ܣ����õ���ӿڣ�ֱ�Ӹ�λ */
    (VOS_VOID)LPS_SoftReBoot_WithLineNoAndFileID( CSS_REBOOT_TYPE_SET_INACTIVE_MODE_TIMEOUT, (__LINE__), (THIS_FILE_ID) );

    return ;
}

/*****************************************************************************
 Function Name  : CSS_ProcApUpdateWaitMccSetReqTimerExp()
 Description    : TI_CSS_WAIT_AP_UPDATE_MCC_SET_REQ��ʱ����ʱ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcApUpdateWaitMccSetReqTimerExp(VOS_VOID)
{
    /* ��ֹAP�������� */
    CSS_EndApUpdateProcedure();
}


/*****************************************************************************
 Function Name  : CSS_ProcMmcOrAsUpdateWaitMccSetReqTimerExp()
 Description    : TI_CSS_WAIT_MMC_OR_AS_UPDATE_MCC_SET_REQ��ʱ����ʱ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcMmcOrAsUpdateWaitMccSetReqTimerExp(const REL_TIMER_MSG *pRcvMsg)
{
    VOS_UINT32                          ulLoop;
    CSS_MCC_UPDATE_STRU                *pstUpdate;

    CSS_SndCurrGeoRsp(pRcvMsg->ulPara, CSS_RESULT_FAIL);

    CSS_PrintLocalPrefFreqInfo();

    for (ulLoop = 0; ulLoop < CSS_MAX_PID_NUM; ++ulLoop)
    {
        pstUpdate = &(CSS_GetCloudContrlAddr()->astMccUpdate[ulLoop]);
        /* �ҵ���PID */
        if (pRcvMsg->ulPara == pstUpdate->ulPid
            && CSS_TRUE == pstUpdate->ucIsUpdating)
        {
            /* ��ֹMMC��AS�������� */
            CSS_EndMmcOrAsUpdateProcedure(pstUpdate);
            break;
        }
    }

}

/*****************************************************************************
 Function Name  : CSS_ProcWaitStartBgsTimerExp()
 Description    : TI_CSS_WAIT_START_BG_SERACH_CNF��ʱ����ʱ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-12-05  Draft Enact
*****************************************************************************/
VOS_VOID CSS_ProcWaitStartBgsTimerExp(const REL_TIMER_MSG *pRcvMsg)
{
    CSS_CONTROL_STRU                   *pstCssControl = CSS_GetControlAddr();

    TLPS_PRINT2LAYER_INFO(CSS_ProcWaitStartBgsTimerExp_ENUM, LNAS_ENTRY);

    /* ֪ͨ�����ֹͣ������ */
    CSS_SndLphyMsgStopBgSearchReq();

    /* ת��STOP_SCAN+WAIT_INACTIVE_CNF״̬ */
    CSS_FSMTranState(CSS_MS_STOP_SCAN, CSS_SS_WAIT_SET_WORK_INACTIVE_MODE_CNF);

    /* ������ʱ�� */
    CSS_StartTimer(&pstCssControl->stSetInactiveModeTimer);

     /* ��Ҫ֪ͨLPHY���ô�ģ���յ��ظ��󣬻ظ�ɨƵʧ�� */
    CSS_SndLphyMsgSetWorkModeReq(CSS_LPHY_WORK_MODE_TYPE_INACTIVE);
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
VOS_VOID CSS_ProcTimerMsg(const REL_TIMER_MSG *pRcvMsg)
{
    CSS_TIMER_ID_ENUM_UINT16            enTimerName;

    enTimerName = (VOS_UINT16)PS_GET_REL_TIMER_NAME(pRcvMsg);

    switch(enTimerName)
    {
        case TI_CSS_WAIT_FOR_SET_INACTIVE_MODE_CNF:
            CSS_ProcSetInactiveModeTimerExp();
            break;

        case TI_CSS_WAIT_FOR_SET_ACTIVE_MODE_CNF:
            CSS_ProcSetActiveModeTimerExp();
            break;

        case TI_CSS_WAIT_FOR_SCAN_IND:
            CSS_ProcBandScanTimerExp();
            break;

        case TI_CSS_WAIT_FOR_STOP_SCAN_CNF:
            CSS_ProcStopBandScanTimerExp();
            break;
        case TI_CSS_WAIT_AP_UPDATE_MCC_SET_REQ:
            CSS_ProcApUpdateWaitMccSetReqTimerExp();
            break;
        case TI_CSS_WAIT_MMC_OR_AS_UPDATE_MCC_SET_REQ:
            CSS_ProcMmcOrAsUpdateWaitMccSetReqTimerExp(pRcvMsg);
            break;
        case TI_CSS_WAIT_START_BG_SERACH_CNF:
            CSS_ProcWaitStartBgsTimerExp(pRcvMsg);
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





