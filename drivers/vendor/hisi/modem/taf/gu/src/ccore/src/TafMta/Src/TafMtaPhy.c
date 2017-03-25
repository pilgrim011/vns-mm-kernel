/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMtaPhy.c
  �� �� ��   : ����
  ��    ��   : ����/00214637
  ��������   : 2013��03��11��
  ����޸�   :
  ��������   : ����MTAģ����Ƶ��غ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��8��30��
    ��    ��   : ����/00214637
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafMtaPhy.h"
#include "TafMtaMain.h"
#include "TafMtaComm.h"
#include "TafSdcCtx.h"
#include "TafMtaMntn.h"
#include "TafMtaMbms.h"

/* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */
#include "NasUtranCtrlInterface.h"
/* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, End */

#include "TafSdcLib.h"




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*lint -e767 �޸���: ���� 00214637; */
#define    THIS_FILE_ID        PS_FILE_ID_TAF_MTA_PHY_C
/*lint +e767 �޸���: ���� 00214637; */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_MTA_SndPhyBodySarReqMsg
 ��������  : MTA�����㷢��ID_MTA_APM_BODY_SAR_SET_REQ��Ϣ
 �������  : ulReceiverPid - ���շ�pid
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2013��03��11��
    ��    ��   : z00214637
    �޸�����   : ֧��BODYSAR

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndPhyBodySarReqMsg(
    MTA_BODY_SAR_STATE_ENUM_UINT16      enState,
    MTA_BODY_SAR_PARA_STRU             *pstBodySarPara
)
{
    VOS_UINT8                           i;
    VOS_UINT32                          ulLength;
    MTA_APM_BODY_SAR_SET_REQ_STRU      *pstMtaPhyBodySarReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength            = sizeof(MTA_APM_BODY_SAR_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaPhyBodySarReq = (MTA_APM_BODY_SAR_SET_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaPhyBodySarReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndPhyBodySarReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_UINT8*)pstMtaPhyBodySarReq + VOS_MSG_HEAD_LENGTH, 0x00, ulLength);

    /* ������Ϣ�ṹ�� */
    pstMtaPhyBodySarReq->ulSenderCpuId      = VOS_LOCAL_CPUID;
    pstMtaPhyBodySarReq->ulSenderPid        = UEPS_PID_MTA;
    pstMtaPhyBodySarReq->ulReceiverCpuId    = VOS_LOCAL_CPUID;
    pstMtaPhyBodySarReq->ulReceiverPid      = DSP_PID_APM;
    pstMtaPhyBodySarReq->usMsgID            = ID_MTA_APM_BODY_SAR_SET_REQ;
    pstMtaPhyBodySarReq->enState            = enState;

    PS_MEM_CPY((VOS_UINT8*)&pstMtaPhyBodySarReq->stBodySARPara, pstBodySarPara,  sizeof(MTA_BODY_SAR_PARA_STRU));

    /* ʵ�ʴ���PHY�Ĺ�������ֵΪ�û����õ�10�� */
    for (i = 0; i < MTA_BODY_SAR_GBAND_MAX_NUM; i++)
    {
        pstMtaPhyBodySarReq->stBodySARPara.astGBandPara[i].sGPRSPower   *= 10;
        pstMtaPhyBodySarReq->stBodySARPara.astGBandPara[i].sEDGEPower   *= 10;
    }

    for (i = 0; i < MTA_BODY_SAR_WBAND_MAX_NUM; i++)
    {
        pstMtaPhyBodySarReq->stBodySARPara.astWBandPara[i].sPower       *= 10;
    }

    /* ������Ϣ�� PHY */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaPhyBodySarReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndPhyBodySarReqMsg(): WARNING:SEND MSG FIAL");
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtBodySarSetReq
 ��������  : mta�յ�ID_AT_MTA_BODY_SAR_SET_REQ��Ϣ������
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��03��11��
    ��    ��   : z00214637
    �޸�����   : ֧��^BODYSARON��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtBodySarSetReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                    *pstBodySarReqMsg    = VOS_NULL_PTR;
    AT_MTA_BODY_SAR_SET_REQ_STRU       *pstBodySarReqPara   = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU              stBodySarCnf;
    VOS_UINT32                          ulResult;

    /* �ֲ�������ʼ�� */
    pstBodySarReqMsg    = (AT_MTA_MSG_STRU*)pMsg;
    pstBodySarReqPara   = (AT_MTA_BODY_SAR_SET_REQ_STRU*)pstBodySarReqMsg->aucContent;

    /* �����ǰ��ʱ������������ֱ�ӷ���ʧ�� */
    if (TAF_MTA_TIMER_STATUS_STOP != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF))
    {
        stBodySarCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstBodySarReqMsg->stAppCtrl,
                         ID_MTA_AT_BODY_SAR_SET_CNF,
                         sizeof(stBodySarCnf),
                         (VOS_UINT8*)&stBodySarCnf );
        return;
    }

    /* �յ�at��BODYSAR�������󣬷�ID_MTA_APM_BODY_SAR_SET_REQ��Ϣ֪ͨPHY */
    ulResult = TAF_MTA_SndPhyBodySarReqMsg(pstBodySarReqPara->enState,
                                           &pstBodySarReqPara->stBodySARPara);

    /* ��Ϣ����ʧ�ܣ���AT�ظ�ERROR */
    if (VOS_ERR == ulResult)
    {
        stBodySarCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstBodySarReqMsg->stAppCtrl,
                          ID_MTA_AT_BODY_SAR_SET_CNF,
                          sizeof(stBodySarCnf),
                          (VOS_UINT8*)&stBodySarCnf );
        return;
    }

    /* ����������ʱ�� */
    if (TAF_MTA_TIMER_START_FAILURE == TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF, TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF_TIMER_LEN))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvAtBodySarSetReq: WARNING: Start Timer failed!");
    }

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF,
                                     (VOS_UINT8*)&pstBodySarReqMsg->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvPhyBodySarSetCnf
 ��������  : mta�յ�ID_APM_MTA_BODY_SAR_SET_CNF��Ϣ������
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��03��11��
    ��    ��   : z00214637
    �޸�����   : ֧��^BODYSARON��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvPhyBodySarSetCnf(VOS_VOID *pMsg)
{
    APM_MTA_BODY_SAR_SET_CNF_STRU      *pstBodySarCnfMsg    = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf           = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU              stBodySarCnf;

    pstBodySarCnfMsg = (APM_MTA_BODY_SAR_SET_CNF_STRU*)pMsg;

    /* �����ǰ��ʱ����Ϊ����״̬ */
    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvPhyBodySarSetCnf: WARNING: Timer was already stop!");
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    /* ��PHY APM���ؽ��ת���󷢸�AT */
    if (MTA_PHY_RESULT_NO_ERROR == pstBodySarCnfMsg->enResult)
    {
        stBodySarCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        stBodySarCnf.enResult = MTA_AT_RESULT_ERROR;
    }

    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU*)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_BODY_SAR_SET_CNF,
                     sizeof(stBodySarCnf),
                     (VOS_UINT8*)&stBodySarCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitPhySetBodySarExpired
 ��������  : �ȴ�phy BodySar���ûظ�������ʱ����ʱ�Ĵ�����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2013��03��11��
    ��    ��   : z00214637
    �޸�����   :֧��^BODYSARON��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitPhySetBodySarExpired(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf   = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU              stBodySarCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    PS_MEM_SET(&stBodySarCnf, 0x0, sizeof(stBodySarCnf));

    stBodySarCnf.enResult = MTA_AT_RESULT_ERROR;

    /* �ѽ�����ϱ���nmr�����ϱ���ATģ�� */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_BODY_SAR_SET_CNF,
                     sizeof(stBodySarCnf),
                     (VOS_UINT8*)&stBodySarCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_SET_BODYSAR_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndPhyEmergencyCallStatus
 ��������  : MTA�����㷢��ID_MTA_APM_EMERGENCY_CALL_STATUS_NTF��Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2013��03��11��
    ��    ��   : z00214637
    �޸�����   : ֧���±���Ŀ
*****************************************************************************/
VOS_VOID TAF_MTA_SndPhyEmergencyCallStatus(
    MTA_PHY_EMERGENCY_CALL_STATUS_ENUM_UINT16               enState
)
{
    MTA_PHY_EMERGENCY_CALL_STATUS_NOTIFY_STRU              *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength    = sizeof(MTA_PHY_EMERGENCY_CALL_STATUS_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (MTA_PHY_EMERGENCY_CALL_STATUS_NOTIFY_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndPhyEmergencyCallStatus: Alloc msg fail!");
        return;
    }

    /* ��д����Ϣ���� */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid           = DSP_PID_APM;
    pstMsg->ulLength                = ulLength;
    pstMsg->usMsgID                 = ID_MTA_APM_EMERGENCY_CALL_STATUS_NOTIFY;
    pstMsg->enEmergencyCallStatus   = enState;
    PS_MEM_SET(&(pstMsg->usReserved0), 0x00, sizeof(pstMsg->usReserved0));
    PS_MEM_SET(pstMsg->ausReserved1, 0x00, sizeof(pstMsg->ausReserved1));

    /*������Ϣ��OAM��ָ��PID ;*/
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MN_ERR_LOG("TAF_MTA_SndPhyEmergencyCallStatus: PS_SEND_MSG fail.");
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtSetHandleDectReq
 ��������  : ����at�·��������ֳ�λ����Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��8��
    ��    ��   : M00217266
    �޸�����   : AP Sensor:

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetHandleDectReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstSetReq       = VOS_NULL_PTR;
    MTA_AT_HANDLEDECT_SET_CNF_STRU      stSetCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT16                          usHandleType;

    pstSetReq          = (AT_MTA_MSG_STRU *)pMsg;
    ulResult           = MTA_AT_RESULT_ERROR;
    usHandleType       = pstSetReq->aucContent[0];
    PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF))
    {
        stSetCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                      ID_MTA_AT_HANDLEDECT_SET_CNF,
                      sizeof(stSetCnf),
                      (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* �յ�at�������󣬷�������Ϣ֪ͨAPM */
    ulResult = TAF_MTA_SndPhySetHandleDectReqMsg(usHandleType);

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        stSetCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_HANDLEDECT_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF,
                        TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF,
                                     (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtQryHandleDectReq
 ��������  : ����at�·��Ĳ�ѯcp���ֳ�λ����Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��8��
    ��    ��   : M00217266
    �޸�����   : AP Sensor:

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtQryHandleDectReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstQryReq       = VOS_NULL_PTR;
    MTA_AT_HANDLEDECT_QRY_CNF_STRU      stQryCnf;
    VOS_UINT32                          ulResult;

    pstQryReq           = (AT_MTA_MSG_STRU *)pMsg;
    ulResult            = MTA_AT_RESULT_ERROR;
    PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF))
    {
        stQryCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                      ID_MTA_AT_HANDLEDECT_QRY_CNF,
                      sizeof(stQryCnf),
                      (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* �յ�at�������󣬷�������Ϣ֪ͨAPM */
    ulResult = TAF_MTA_SndPhyQryHandleDectReqMsg();

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        stQryCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                         ID_MTA_AT_HANDLEDECT_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF,
                        TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF,
                                     (VOS_UINT8*)&pstQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndPhySetHandleDectReqMsg
 ��������  : MTA�·��Ĳ�ѯcp���ֳ�λ����Ϣ��phy
 �������  : VOS_UINT8 ucHandleType
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��8��
    ��    ��   : M00217266
    �޸�����   : AP Sensor:

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndPhySetHandleDectReqMsg(
    VOS_UINT16                          usHandleType
)
{
    VOS_UINT32                          ulLength;
    MTA_APM_HANDLE_DETECT_SET_REQ_STRU *pstMtaPhyReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength            = sizeof(MTA_APM_HANDLE_DETECT_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaPhyReq        = (MTA_APM_HANDLE_DETECT_SET_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaPhyReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndPhySetHandleDectReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_UINT8*)pstMtaPhyReq + VOS_MSG_HEAD_LENGTH, 0x00, ulLength);

    /* ������Ϣ�ṹ�� */
    pstMtaPhyReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaPhyReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaPhyReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaPhyReq->ulReceiverPid     = DSP_PID_APM;
    pstMtaPhyReq->usMsgID           = ID_MTA_APM_HANDLE_DETECT_SET_REQ;
    pstMtaPhyReq->usHandle          = usHandleType;

    /* ������Ϣ�� PHY */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaPhyReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndPhySetHandleDectReqMsg(): WARNING:SEND MSG FIAL");
    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : TAF_MTA_SndPhyQryHandleDectReqMsg
 ��������  : MTA�·��Ĳ�ѯcp���ֳ�λ����Ϣ��phy
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��8��
    ��    ��   : M00217266
    �޸�����   : AP Sensor:

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndPhyQryHandleDectReqMsg(VOS_VOID)
{
    VOS_UINT32                          ulLength;
    MTA_APM_HANDLE_DETECT_QRY_REQ_STRU *pstMtaPhyReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength            = sizeof(MTA_APM_HANDLE_DETECT_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaPhyReq        = (MTA_APM_HANDLE_DETECT_QRY_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaPhyReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndPhyQryHandleDectReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_UINT8*)pstMtaPhyReq + VOS_MSG_HEAD_LENGTH, 0x00, ulLength);

    /* ������Ϣ�ṹ�� */
    pstMtaPhyReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaPhyReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaPhyReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaPhyReq->ulReceiverPid     = DSP_PID_APM;
    pstMtaPhyReq->usMsgID           = ID_MTA_APM_HANDLE_DETECT_QRY_REQ;

    /* ������Ϣ�� PHY */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaPhyReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndPhyQryHandleDectReqMsg(): WARNING:SEND MSG FIAL");
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndPhyQryHandleDectReqMsg
 ��������  : MTA�������������cp���ֳ�λ�ý��
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��8��
    ��    ��   : M00217266
    �޸�����   : AP Sensor:

*****************************************************************************/
VOS_VOID TAF_MTA_RcvPhyHandleDectSetCnf(
    VOS_VOID                           *pMsg
)
{
    APM_MTA_HANDLE_DETECT_SET_CNF_STRU     *pstApmMtaCnf   = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU                *pstCmdBuf   = VOS_NULL_PTR;
    MTA_AT_HANDLEDECT_SET_CNF_STRU          stMtaAtCnf;

    pstApmMtaCnf = (APM_MTA_HANDLE_DETECT_SET_CNF_STRU *)pMsg;

    /* �����ǰ��ʱ����Ϊ����״̬ */
    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvPhyHandleDectSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    /* ��PHY APM���ؽ��ת���󷢸�AT */
    if (MTA_PHY_RESULT_NO_ERROR == pstApmMtaCnf->enResult)
    {
        stMtaAtCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        stMtaAtCnf.enResult = MTA_AT_RESULT_ERROR;
    }

    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU*)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_HANDLEDECT_SET_CNF,
                     sizeof(stMtaAtCnf),
                     (VOS_UINT8*)&stMtaAtCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndPhyQryHandleDectReqMsg
 ��������  : MTA����������ѯcp���ֳ�λ�ý��
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��8��
    ��    ��   : M00217266
    �޸�����   : AP Sensor:

*****************************************************************************/
VOS_VOID TAF_MTA_RcvPhyHandleDectQryCnf(
    VOS_VOID                           *pMsg
)
{
    APM_MTA_HANDLE_DETECT_QRY_CNF_STRU     *pstApmMtaCnf   = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU                *pstCmdBuf   = VOS_NULL_PTR;
    MTA_AT_HANDLEDECT_QRY_CNF_STRU          stMtaAtCnf;

    pstApmMtaCnf = (APM_MTA_HANDLE_DETECT_QRY_CNF_STRU *)pMsg;
    PS_MEM_SET((VOS_UINT8*)&stMtaAtCnf, 0x00, sizeof(MTA_AT_HANDLEDECT_QRY_CNF_STRU));

    /* �����ǰ��ʱ����Ϊ����״̬ */
    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvPhyHandleDectQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    /* ��PHY APM���ؽ��ת���󷢸�AT */
    if (MTA_PHY_RESULT_NO_ERROR == pstApmMtaCnf->enResult)
    {
        stMtaAtCnf.enResult = MTA_AT_RESULT_NO_ERROR;
        stMtaAtCnf.usHandle = pstApmMtaCnf->usHandle;
    }
    else
    {
        stMtaAtCnf.enResult = MTA_AT_RESULT_ERROR;
    }

    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU*)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_HANDLEDECT_QRY_CNF,
                     sizeof(stMtaAtCnf),
                     (VOS_UINT8*)&stMtaAtCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitPhySetHandleDectExpired
 ��������  : MTA����TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF��Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��8��
    ��    ��   : M00217266
    �޸�����   : AP Sensor:

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitPhySetHandleDectExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_HANDLEDECT_SET_CNF_STRU      stMtaAtSetCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*��ʱ����ʱlog*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiWaitPhySetHandleDectExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stMtaAtSetCnf, 0x0, sizeof(stMtaAtSetCnf));

    stMtaAtSetCnf.enResult = MTA_AT_RESULT_ERROR;

    /* �ϱ���ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_HANDLEDECT_SET_CNF,
                     sizeof(stMtaAtSetCnf),
                     (VOS_UINT8*)&stMtaAtSetCnf );


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitPhyQryHandleDectExpired
 ��������  : MTA����TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF��Ϣ
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��8��
    ��    ��   : M00217266
    �޸�����   : AP Sensor:

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitPhyQryHandleDectExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_HANDLEDECT_QRY_CNF_STRU      stMtaAtQryCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_PHY_HANDLEDECT_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*��ʱ����ʱlog*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiWaitPhyQryHandleDectExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stMtaAtQryCnf, 0x0, sizeof(stMtaAtQryCnf));

    stMtaAtQryCnf.enResult = MTA_AT_RESULT_ERROR;

    /* �ϱ���ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_HANDLEDECT_QRY_CNF,
                     sizeof(stMtaAtQryCnf),
                     (VOS_UINT8*)&stMtaAtQryCnf );


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_CheckRatModeTypeValid
 ��������  : ���ݵ�ǰϵͳפ����ģʽ���������ظ���Ϣ��ratMode������Ч���ж�
 �������  : AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��4��
    ��    ��   : g00261581
    �޸�����   : �½�
  2.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
VOS_UINT32 TAF_MTA_CheckRatModeTypeValid(
    AT_MTA_CMD_RATMODE_ENUM_UINT8       enRatMode
)
{
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysCurrMode;
    /* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enUtranctrlMode;

    enUtranctrlMode = NAS_UTRANCTRL_GetCurrUtranMode();
    /* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, End */
    enSysCurrMode   = TAF_SDC_GetSysMode();

    if ( (AT_MTA_CMD_RATMODE_GSM        == enRatMode)
     && (TAF_SDC_SYS_MODE_GSM           == enSysCurrMode) )
    {
        return VOS_OK;
    }

    /* Modify by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */
    if ( (AT_MTA_CMD_RATMODE_WCDMA      == enRatMode)
     && (TAF_SDC_SYS_MODE_WCDMA         == enSysCurrMode)
     && (NAS_UTRANCTRL_UTRAN_MODE_FDD   == enUtranctrlMode) )
    {
        return VOS_OK;
    }

    if ( (AT_MTA_CMD_RATMODE_TD         == enRatMode)
     && (TAF_SDC_SYS_MODE_WCDMA         == enSysCurrMode)
     && (NAS_UTRANCTRL_UTRAN_MODE_TDD   == enUtranctrlMode) )
    {
        return VOS_OK;
    }
    /* Modify by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */

    if ((AT_MTA_CMD_RATMODE_LTE == enRatMode)
     && (TAF_SDC_SYS_MODE_LTE   == enSysCurrMode))
    {
        return VOS_OK;
    }

    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndGuPhySetDpdtTestFlagNtfMsg
 ��������  : MTA����Set DpdtTest Flag������Ϣ��GU PHY
 �������  : AT_MTA_SET_DPDT_VALUE_REQ_STRU     *pstQryDpdtReq
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��4��
    ��    ��   : g00261581
    �޸�����   : �½�

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndGuPhySetDpdtTestFlagNtfMsg(
    AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU  *pstSetDpdtFlagReq
)
{
    MTA_GUPHY_SET_DPDTTEST_FLAG_NTF_STRU   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                              ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength    = sizeof(MTA_GUPHY_SET_DPDTTEST_FLAG_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (MTA_GUPHY_SET_DPDTTEST_FLAG_NTF_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndGuPhySetDpdtTestFlagNtfMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* ��д����Ϣ���� */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulLength                = ulLength;
    pstMsg->usMsgID                 = ID_MTA_GUPHY_SET_DPDTTEST_FLAG_NTF;

    if (AT_MTA_CMD_RATMODE_GSM   == pstSetDpdtFlagReq->enRatMode)
    {
        pstMsg->ulReceiverPid       = DSP_PID_GPHY;
    }
    else if (AT_MTA_CMD_RATMODE_WCDMA   == pstSetDpdtFlagReq->enRatMode)
    {
        pstMsg->ulReceiverPid       = DSP_PID_WPHY;
    }
    else if (AT_MTA_CMD_RATMODE_CDMA   == pstSetDpdtFlagReq->enRatMode)
    {
        pstMsg->ulReceiverPid       = DSP_PID_RCM;
    }
    else
    {
    }

    pstMsg->usDpdtTest = (VOS_UINT16)pstSetDpdtFlagReq->ucFlag;

    /* ������Ϣ��Gu phy */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MTA_ERROR_LOG("TAF_MTA_SndGuPhySetDpdtTestFlagNtfMsg: PS_SEND_MSG fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndGuPhySetDpdtValueNtfMsg
 ��������  : MTA����Set Dpdt Value������Ϣ��GU PHY
 �������  : AT_MTA_SET_DPDT_VALUE_REQ_STRU     *pstQryDpdtReq
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��4��
    ��    ��   : g00261581
    �޸�����   : �½�

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndGuPhySetDpdtValueNtfMsg(
    AT_MTA_SET_DPDT_VALUE_REQ_STRU     *pstSetDpdtReq
)
{
    MTA_GUPHY_SET_DPDT_VALUE_NTF_STRU  *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength    = sizeof(MTA_GUPHY_SET_DPDT_VALUE_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (MTA_GUPHY_SET_DPDT_VALUE_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndGuPhySetDpdtValueNtfMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* ��д����Ϣ���� */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulLength                = ulLength;
    pstMsg->usMsgID                 = ID_MTA_GUPHY_SET_DPDT_VALUE_NTF;

    if (AT_MTA_CMD_RATMODE_GSM   == pstSetDpdtReq->enRatMode)
    {
        pstMsg->ulReceiverPid       = DSP_PID_GPHY;
    }
    else
    {
        pstMsg->ulReceiverPid       = DSP_PID_WPHY;
    }

    pstMsg->ulDpdtValue = pstSetDpdtReq->ulDpdtValue;

    /* ������Ϣ��Gu phy */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MTA_ERROR_LOG("TAF_MTA_SndGuPhySetDpdtValueNtfMsg: PS_SEND_MSG fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndGuPhyQryDpdtValueReqMsg
 ��������  : MTA����Qry Dpdt Value������Ϣ��GU PHY
 �������  : AT_MTA_QRY_DPDT_VALUE_REQ_STRU     *pstQryDpdtReq
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��4��
    ��    ��   : g00261581
    �޸�����   : �½�

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndGuPhyQryDpdtValueReqMsg(
    AT_MTA_QRY_DPDT_VALUE_REQ_STRU     *pstQryDpdtReq
)
{
    MTA_GUPHY_QRY_DPDT_VALUE_REQ_STRU  *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength    = sizeof(MTA_GUPHY_QRY_DPDT_VALUE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (MTA_GUPHY_QRY_DPDT_VALUE_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndGuPhyQryDpdtValueReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* ��д����Ϣ���� */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulLength                = ulLength;
    pstMsg->usMsgID                 = ID_MTA_GUPHY_QRY_DPDT_VALUE_REQ;

    if (AT_MTA_CMD_RATMODE_GSM   == pstQryDpdtReq->enRatMode)
    {
        pstMsg->ulReceiverPid       = DSP_PID_GPHY;
    }
    else
    {
        pstMsg->ulReceiverPid       = DSP_PID_WPHY;
    }

    /* ������Ϣ��Gu phy */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MTA_ERROR_LOG("TAF_MTA_SndGuPhyQryDpdtValueReqMsg: PS_SEND_MSG fail.");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtSetDpdtTestFlagReq
 ��������  : ����at�·���˫�������Կ��ش򿪡��ر�����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��4��
    ��    ��   : g00261581
    �޸�����   : �½�
  2.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetDpdtTestFlagReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstQryReq      = VOS_NULL_PTR;
    AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU  *pstAtMtaQryReq = VOS_NULL_PTR;
    MTA_AT_SET_DPDTTEST_FLAG_CNF_STRU   stMtaAtQryCnf;
    VOS_UINT32                          ulResult;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulIsClMode;

    ulIsClMode              = TAF_SDC_IsConfigCLMode();
#endif
    ulResult                = VOS_ERR;
    stMtaAtQryCnf.enResult  = MTA_AT_RESULT_ERROR;

    /* ����AT���͹�������Ϣ�ṹ */
    pstQryReq       = (AT_MTA_MSG_STRU *)pMsg;
    pstAtMtaQryReq  = (AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU *)(pstQryReq->aucContent);


    /* Modify by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */
    /* ����RatMode,����Ϣ�ṹ������GU phy����LRRC */
    if ( (AT_MTA_CMD_RATMODE_GSM    == pstAtMtaQryReq->enRatMode)
     ||  (AT_MTA_CMD_RATMODE_WCDMA  == pstAtMtaQryReq->enRatMode) )
    {
        ulResult = TAF_MTA_SndGuPhySetDpdtTestFlagNtfMsg(pstAtMtaQryReq);
    }
    /* Modify by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */

#if (FEATURE_ON == FEATURE_LTE)
    if (AT_MTA_CMD_RATMODE_LTE      == pstAtMtaQryReq->enRatMode)
    {
        ulResult = TAF_MTA_SndTLrrcSetDpdtTestFlagNtfMsg(pstAtMtaQryReq);
    }
#endif

    /* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    if (AT_MTA_CMD_RATMODE_TD       == pstAtMtaQryReq->enRatMode)
    {
        ulResult = TAF_MTA_SndTLrrcSetDpdtTestFlagNtfMsg(pstAtMtaQryReq);
    }
#endif
    /* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, End */

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    if (AT_MTA_CMD_RATMODE_CDMA    == pstAtMtaQryReq->enRatMode)
    {
    #if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (VOS_FALSE == ulIsClMode)
    #endif
        {
            ulResult = TAF_MTA_SndGuPhySetDpdtTestFlagNtfMsg(pstAtMtaQryReq);
        }
    }
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((AT_MTA_CMD_RATMODE_CDMA    == pstAtMtaQryReq->enRatMode)
     && (VOS_TRUE                   == ulIsClMode))
    {
        ulResult = TAF_MTA_SndCtasSetDpdtTestFlagNtfMsg(pstAtMtaQryReq);
    }
#endif

    if (VOS_OK == ulResult)
    {
        stMtaAtQryCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }

    /* MTA�ظ�ATģ��DPDT FLAG���������� */
    TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                    ID_MTA_AT_SET_DPDTTEST_FLAG_CNF,
                    sizeof(stMtaAtQryCnf),
                    (VOS_UINT8 *)&stMtaAtQryCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtSetDpdtValueReq
 ��������  : ����at�·�������DPDT Valueֵ������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��4��
    ��    ��   : g00261581
    �޸�����   : �½�
  4.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetDpdtValueReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstQryReq      = VOS_NULL_PTR;
    AT_MTA_SET_DPDT_VALUE_REQ_STRU     *pstAtMtaQryReq = VOS_NULL_PTR;
    MTA_AT_SET_DPDT_VALUE_CNF_STRU      stMtaAtQryCnf;
    VOS_UINT32                          ulResult;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulIsClMode;

    ulIsClMode              = TAF_SDC_IsConfigCLMode();
#endif

    ulResult               = VOS_ERR;
    stMtaAtQryCnf.enResult = MTA_AT_RESULT_ERROR;

    /* ����AT���͹�������Ϣ�ṹ */
    pstQryReq       = (AT_MTA_MSG_STRU *)pMsg;
    pstAtMtaQryReq  = (AT_MTA_SET_DPDT_VALUE_REQ_STRU *)(pstQryReq->aucContent);


    /* Modify by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */
    /* ����RatMode,����Ϣ�ṹ������GU phy����LRRC */
    if ( (AT_MTA_CMD_RATMODE_GSM        == pstAtMtaQryReq->enRatMode)
     ||  (AT_MTA_CMD_RATMODE_WCDMA      == pstAtMtaQryReq->enRatMode) )
    {
        ulResult = TAF_MTA_SndGuPhySetDpdtValueNtfMsg(pstAtMtaQryReq);
    }
    /* Modify by j00174725 for K3V3 ��ģ����������, 2014-06-16, End */

#if (FEATURE_ON == FEATURE_LTE)
    if (AT_MTA_CMD_RATMODE_LTE          == pstAtMtaQryReq->enRatMode)
    {
        ulResult = TAF_MTA_SndTLrrcSetDpdtValueNtfMsg(pstAtMtaQryReq);
    }
#endif

/* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    if (AT_MTA_CMD_RATMODE_TD           == pstAtMtaQryReq->enRatMode)
    {
        ulResult = TAF_MTA_SndTLrrcSetDpdtValueNtfMsg(pstAtMtaQryReq);
    }
#endif
/* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, End */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((AT_MTA_CMD_RATMODE_CDMA        == pstAtMtaQryReq->enRatMode)
     && (VOS_TRUE                       == ulIsClMode))
    {
        ulResult = TAF_MTA_SndCtasSetDpdtValueNtfMsg(pstAtMtaQryReq);
    }
#endif

    if (VOS_OK == ulResult)
    {
        stMtaAtQryCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    }

    /* MTA�ظ�ATģ��DPDT VALUE���������� */
    TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                    ID_MTA_AT_SET_DPDT_VALUE_CNF,
                    sizeof(stMtaAtQryCnf),
                    (VOS_UINT8 *)&stMtaAtQryCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtSetDpdtValueInd
 ��������  : ����at�·��Ĳ�ѯDPDT Value������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��4��
    ��    ��   : g00261581
    �޸�����   : �½�

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtQryDpdtValueReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstQryReq      = VOS_NULL_PTR;
    AT_MTA_QRY_DPDT_VALUE_REQ_STRU     *pstAtMtaQryReq = VOS_NULL_PTR;
    MTA_AT_QRY_DPDT_VALUE_CNF_STRU      stMtaAtQryCnf;
    VOS_UINT32                          ulResult;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulIsClMode;

    ulIsClMode              = TAF_SDC_IsConfigCLMode();
#endif
    ulResult                = VOS_ERR;
    PS_MEM_SET(&stMtaAtQryCnf, 0x0, sizeof(stMtaAtQryCnf));
    stMtaAtQryCnf.enResult = MTA_AT_RESULT_ERROR;

    /* ����AT���͹�������Ϣ�ṹ */
    pstQryReq       = (AT_MTA_MSG_STRU *)pMsg;
    pstAtMtaQryReq  = (AT_MTA_QRY_DPDT_VALUE_REQ_STRU *)(pstQryReq->aucContent);

    /* �����ʱ��TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF���������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF))
    {
        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                        ID_MTA_AT_QRY_DPDT_VALUE_CNF,
                        sizeof(stMtaAtQryCnf),
                        (VOS_UINT8 *)&stMtaAtQryCnf );
        return;
    }


    /* Modify by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */
    /* ����RatMode,����Ϣ�ṹ������GU phy����LRRC */
    if ( (AT_MTA_CMD_RATMODE_GSM    == pstAtMtaQryReq->enRatMode)
      || (AT_MTA_CMD_RATMODE_WCDMA  == pstAtMtaQryReq->enRatMode) )
    {
        ulResult = TAF_MTA_SndGuPhyQryDpdtValueReqMsg(pstAtMtaQryReq);
    }
    /* Modify by j00174725 for K3V3 ��ģ����������, 2014-06-16, end */

#if (FEATURE_ON == FEATURE_LTE)
    if (AT_MTA_CMD_RATMODE_LTE      == pstAtMtaQryReq->enRatMode)
    {
        ulResult = TAF_MTA_SndTLrrcQryDpdtValueReqMsg(pstAtMtaQryReq);
    }
#endif

/* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
    if ( AT_MTA_CMD_RATMODE_TD      == pstAtMtaQryReq->enRatMode)
    {
        ulResult = TAF_MTA_SndTLrrcQryDpdtValueReqMsg(pstAtMtaQryReq);
    }
#endif
/* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, End */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if ((AT_MTA_CMD_RATMODE_CDMA    == pstAtMtaQryReq->enRatMode)
     && (VOS_TRUE                   == ulIsClMode))
    {
        ulResult = TAF_MTA_SndCtasQryDpdtValueReqMsg(pstAtMtaQryReq);
    }
#endif

    if (VOS_OK != ulResult)
    {
        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                        ID_MTA_AT_QRY_DPDT_VALUE_CNF,
                        sizeof(stMtaAtQryCnf),
                        (VOS_UINT8 *)&stMtaAtQryCnf);

        return;
    }

    /* ����������ʱ��TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF,
                        TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF,
                                     (VOS_UINT8*)&pstQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvGuPhyQryDpdtValueCnf
 ��������  : MTA�յ�GU phy��DPDT Value��ѯ�ظ���Ϣ������
 �������  : pMsg  -- ��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��4��
    ��    ��   : g00261581
    �޸�����   : �½�
*****************************************************************************/
VOS_VOID TAF_MTA_RcvGuPhyQryDpdtValueCnf(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf         = VOS_NULL_PTR;
    GUPHY_MTA_QRY_DPDT_VALUE_CNF_STRU  *pstGuPhyMtaQryCnf = VOS_NULL_PTR;
    MTA_AT_QRY_DPDT_VALUE_CNF_STRU      stMtaAtQryCnf;
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId;

    /* �ֲ�������ʼ�� */
    pstGuPhyMtaQryCnf = (GUPHY_MTA_QRY_DPDT_VALUE_CNF_STRU *)pMsg;
    enTimerId = TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF;

    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(enTimerId))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvGuPhyQryDpdtValueCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(enTimerId);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(enTimerId);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    /* ������Ϣ�ṹ�� */
    stMtaAtQryCnf.enResult = MTA_AT_RESULT_NO_ERROR;
    stMtaAtQryCnf.ulDpdtValue = pstGuPhyMtaQryCnf->ulDpdtValue;

    /* ������Ϣ��ATģ�� */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                      ID_MTA_AT_QRY_DPDT_VALUE_CNF,
                      sizeof(MTA_AT_QRY_DPDT_VALUE_CNF_STRU),
                      (VOS_UINT8 *)&stMtaAtQryCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiReqDpdtValueQryExpired
 ��������  : DPDTQRY����ִ�г�ʱ
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��4��
    ��    ��   : g00261581
    �޸�����   : �½�

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiReqDpdtValueQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf   = VOS_NULL_PTR;
    MTA_AT_QRY_DPDT_VALUE_CNF_STRU      stQryDpdtValueCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    PS_MEM_SET(&stQryDpdtValueCnf, 0x0, sizeof(stQryDpdtValueCnf));

    stQryDpdtValueCnf.enResult = MTA_AT_RESULT_ERROR;

    /* �ϱ�ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_QRY_DPDT_VALUE_CNF,
                     sizeof(stQryDpdtValueCnf),
                     (VOS_UINT8 *)&stQryDpdtValueCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF);

    return;
}

/*lint +e958*/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_MTA_SndCtasSetDpdtTestFlagNtfMsg
 ��������  : MTA����Set DpdtTest Flag������Ϣ��CTAS
 �������  : AT_MTA_SET_DPDT_VALUE_REQ_STRU     *pstQryDpdtReq
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : h00313353
    �޸�����   : �½�

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndCtasSetDpdtTestFlagNtfMsg(
    AT_MTA_SET_DPDTTEST_FLAG_REQ_STRU  *pstSetDpdtFlagReq
)
{
    MTA_CTAS_SET_DPDTTEST_FLAG_NTF_STRU    *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                              ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength    = sizeof(MTA_CTAS_SET_DPDTTEST_FLAG_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (MTA_CTAS_SET_DPDTTEST_FLAG_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndCtasSetDpdtTestFlagNtfMsg: Alloc msg fail!");

        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* ��д����Ϣ���� */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid           = CPROC_PID_1X_CTAS;
    pstMsg->ulLength                = ulLength;
    pstMsg->ulMsgName               = (VOS_UINT32)ID_MTA_CTAS_SET_DPDTTEST_FLAG_NTF;
    pstMsg->usDpdtTest              = (VOS_UINT16)pstSetDpdtFlagReq->ucFlag;

    /* ������Ϣ��CTAS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MTA_ERROR_LOG("TAF_MTA_SndCtasSetDpdtTestFlagNtfMsg: PS_SEND_MSG fail.");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndCtasSetDpdtValueNtfMsg
 ��������  : MTA����Set Dpdt Value������Ϣ��CTAS
 �������  : AT_MTA_SET_DPDT_VALUE_REQ_STRU     *pstQryDpdtReq
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : h00313353
    �޸�����   : �½�

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndCtasSetDpdtValueNtfMsg(
    AT_MTA_SET_DPDT_VALUE_REQ_STRU     *pstSetDpdtReq
)
{
    MTA_CTAS_SET_DPDT_VALUE_NTF_STRU   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength    = sizeof(MTA_CTAS_SET_DPDT_VALUE_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (MTA_CTAS_SET_DPDT_VALUE_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndCtasSetDpdtValueNtfMsg: Alloc msg fail!");

        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* ��д����Ϣ���� */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid           = CPROC_PID_1X_CTAS;
    pstMsg->ulLength                = ulLength;
    pstMsg->ulMsgName               = (VOS_UINT32)ID_MTA_CTAS_SET_DPDT_VALUE_NTF;
    pstMsg->ulDpdtValue             = pstSetDpdtReq->ulDpdtValue;

    /* ������Ϣ��CTAS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MTA_ERROR_LOG("TAF_MTA_SndCtasSetDpdtValueNtfMsg: PS_SEND_MSG fail.");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndCtasQryDpdtValueReqMsg
 ��������  : MTA����Qry Dpdt Value������Ϣ��CTAS
 �������  : AT_MTA_QRY_DPDT_VALUE_REQ_STRU     *pstQryDpdtReq
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : h00313353
    �޸�����   : �½�

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndCtasQryDpdtValueReqMsg(
    AT_MTA_QRY_DPDT_VALUE_REQ_STRU     *pstQryDpdtReq
)
{
    MTA_CTAS_QRY_DPDT_VALUE_REQ_STRU   *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength    = sizeof(MTA_CTAS_QRY_DPDT_VALUE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg      = (MTA_CTAS_QRY_DPDT_VALUE_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndCtasQryDpdtValueReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* ��д����Ϣ���� */
    pstMsg->ulSenderCpuId           = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid             = UEPS_PID_MTA;
    pstMsg->ulReceiverCpuId         = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid           = CPROC_PID_1X_CTAS;
    pstMsg->ulLength                = ulLength;
    pstMsg->ulMsgName               = (VOS_UINT32)ID_MTA_CTAS_QRY_DPDT_VALUE_REQ;

    /* ������Ϣ��CTAS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMsg))
    {
        MTA_ERROR_LOG("TAF_MTA_SndCtasQryDpdtValueReqMsg: PS_SEND_MSG fail.");

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvCtasQryDpdtValueCnf
 ��������  : MTA�յ�CTAS��DPDT Value��ѯ�ظ���Ϣ������
 �������  : pMsg  -- ��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��18��
    ��    ��   : h00313353
    �޸�����   : �½�
*****************************************************************************/
VOS_VOID TAF_MTA_RcvCtasQryDpdtValueCnf(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf         = VOS_NULL_PTR;
    CTAS_MTA_QRY_DPDT_VALUE_CNF_STRU   *pstCtasMtaQryCnf  = VOS_NULL_PTR;
    MTA_AT_QRY_DPDT_VALUE_CNF_STRU      stMtaAtQryCnf;
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId;

    /* �ֲ�������ʼ�� */
    pstCtasMtaQryCnf = (CTAS_MTA_QRY_DPDT_VALUE_CNF_STRU *)pMsg;
    enTimerId        = TI_TAF_MTA_WAIT_DPDT_VALUE_QRY_CNF;
    PS_MEM_SET(&stMtaAtQryCnf, 0x00, sizeof(MTA_AT_QRY_DPDT_VALUE_CNF_STRU));

    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(enTimerId))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvCtasQryDpdtValueCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(enTimerId);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(enTimerId);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    /* ������Ϣ�ṹ�� */
    stMtaAtQryCnf.enResult      = MTA_AT_RESULT_NO_ERROR;
    stMtaAtQryCnf.ulDpdtValue   = pstCtasMtaQryCnf->ulDpdtValue;

    /* ������Ϣ��ATģ�� */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     (VOS_UINT32)ID_MTA_AT_QRY_DPDT_VALUE_CNF,
                      sizeof(MTA_AT_QRY_DPDT_VALUE_CNF_STRU),
                     (VOS_UINT8 *)&stMtaAtQryCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}
#endif

#if(FEATURE_ON == FEATURE_LTE)
#if 0
/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLphySetIsmCoexReqMsg
 ��������  : ��lphy������������^SIMCOEX
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_SndLphySetIsmCoexReqMsg(
    AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU           *pstCoexPara
)
{
    VOS_UINT32                                      ulLength;
    MTA_LPHY_LTE_WIFI_COEX_SET_REQ_STRU            *pstMtaLphySetReq = VOS_NULL_PTR;
    VOS_UINT32                                      ulCoexParaPtr;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(pstCoexPara->aucCoexPara) + sizeof(MTA_LPHY_LTE_WIFI_COEX_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH - 4;
    pstMtaLphySetReq      = (MTA_LPHY_LTE_WIFI_COEX_SET_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaLphySetReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLphySetIsmCoexReqMsg: Alloc msg fail!");
        return;
    }

    /* ������Ϣ�ṹ�� */
    MTA_FILL_MSG_HEADER(pstMtaLphySetReq, TLPHY_PID_RTTAGENT);
    pstMtaLphySetReq->usMsgID                       = ID_MTA_LPHY_LTE_WIFI_COEX_SET_REQ;
    pstMtaLphySetReq->usCoexParaNum                 = pstCoexPara->usCoexParaNum;
    pstMtaLphySetReq->usCoexParaSize                = pstCoexPara->usCoexParaSize;
    ulCoexParaPtr                                   = (VOS_UINT32)pstMtaLphySetReq->aucCoexPara;
    PS_MEM_CPY((VOS_UINT8 *)ulCoexParaPtr, pstCoexPara->aucCoexPara, sizeof(pstCoexPara->aucCoexPara));

    /* ������Ϣ��LPHY */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaLphySetReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndLphySetIsmCoexReqMsg: Send msg fail!");
        return;
    }

    return;
}
#endif
/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtIsmCoexSetReq
 ��������  : MTA����^ISMCOEX����
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtIsmCoexSetReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                                        *pstSetReq               = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                                  stSetCnf;
    VOS_UINT32                                              ulResult;

    pstSetReq = (AT_MTA_MSG_STRU *)pMsg;
    ulResult  = VOS_OK;

    /* ģʽ״̬�����������ҵ�ǰ��Ϊ����ģʽ�����at�ظ�ʧ�� */
    if (TAF_SDC_PHONE_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        ulResult  = VOS_ERR;
    }

    /* �����ǰ��ʱ�������������at�ظ�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF))
    {
        ulResult  = VOS_ERR;
    }

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stSetCnf, 0x0, sizeof(stSetCnf));
        stSetCnf.enResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_LTE_WIFI_COEX_SET_CNF,
                         sizeof(stSetCnf),
                         (VOS_UINT8*)&stSetCnf );
        return;
    }
#if 0
    /* �յ�at�������󣬷�������Ϣ֪ͨLPHY*/
    TAF_MTA_SndLphySetIsmCoexReqMsg((AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU *)pstSetReq->aucContent);
#endif

    /* �յ�at�������󣬷�������Ϣ֪ͨLRRC*/
    TAF_MTA_SndLrrcSetIsmCoexReqMsg((AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU *)pstSetReq->aucContent);

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF,
                       TI_TAF_MTA_WAIT_SET_LTE_WIFI_COEX_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF,
                                     (VOS_UINT8*)pstSetReq,
                                     sizeof(AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU) + sizeof(AT_MTA_MSG_STRU) - 4);
    return;
}
#if 0
/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvLphyIsmCoexSetCnf
 ��������  : MTA�յ�LPHY ^ISMCOEX���ý��
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_RcvLphyIsmCoexSetCnf(
    VOS_VOID                           *pLphyCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                        *pstCmdBuf               = VOS_NULL_PTR;
    LPHY_MTA_LTE_WIFI_COEX_SET_CNF_STRU            *pstRcvLphyCnf           = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                          stSndAtCnf;
    AT_MTA_MSG_STRU                                *pstMsg                  = VOS_NULL_PTR;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLphyIsmCoexSetCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLphyIsmCoexSetCnf: get command buffer failed!");
        return;
    }

    pstRcvLphyCnf           = (LPHY_MTA_LTE_WIFI_COEX_SET_CNF_STRU *)pLphyCnfMsg;
    stSndAtCnf.enResult     = pstRcvLphyCnf->enResult;

    pstMsg                  = (AT_MTA_MSG_STRU *)pstCmdBuf->pucMsgInfo;

    if (VOS_OK != stSndAtCnf.enResult)
    {
        /* ��at����Ϣ */
        TAF_MTA_SndAtMsg(&pstMsg->stAppCtrl,
                         ID_MTA_AT_LTE_WIFI_COEX_SET_CNF,
                         sizeof(stSndAtCnf),
                         (VOS_UINT8*)&stSndAtCnf );

        /* ֹͣ������ʱ�� */
        TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF);

        /* �ӵȴ�������ɾ����Ϣ */
        TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF);
    }
    else
    {
        /* ��������Ϣ֪ͨLRRC*/
        TAF_MTA_SndLrrcSetIsmCoexReqMsg((AT_MTA_LTE_WIFI_COEX_SET_REQ_STRU *)pstMsg->aucContent);
    }

    return;
}
#endif
/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitSetIsmCoexList
 ��������  : ��������^ISMCOEX��ʱ�Ĵ�����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2015��5��22��
    ��    ��   : w00316404
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitSetIsmCoexList(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf       = VOS_NULL_PTR;
    AT_MTA_MSG_STRU                            *pstMsg          = VOS_NULL_PTR;
    MTA_AT_RESULT_CNF_STRU                      stSndAtCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    pstMsg              = (AT_MTA_MSG_STRU *)pstCmdBuf->pucMsgInfo;

    stSndAtCnf.enResult = MTA_AT_RESULT_ERROR;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg(&pstMsg->stAppCtrl,
                     ID_MTA_AT_LTE_WIFI_COEX_SET_CNF,
                     sizeof(stSndAtCnf),
                     (VOS_UINT8*)&stSndAtCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_LTE_WIFI_COEX_SET_CNF);

    return;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtRficSsiRdQryReq
 ��������  : MTAģ���յ�AT������RFICSSIRD������Ϣ�Ĵ�����
 �������  : pMsg   -- AT���͵���Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��29��
    ��    ��   : x00316382
    �޸�����   : ����
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtRficSsiRdQryReq(VOS_VOID *pMsg)
{
    VOS_UINT32                              ulLength;
    MTA_AGENT_RFICSSIRD_REQ_STRU           *pstMtaRficSsiRdReq  = VOS_NULL_PTR;
    AT_MTA_MSG_STRU                        *pstAtMtaReqMsg      = VOS_NULL_PTR;     /* �յ�AT��������Ϣָ�� */
    AT_MTA_RFICSSIRD_REQ_STRU              *pstRficSsiRdReq     = VOS_NULL_PTR;

    pstAtMtaReqMsg          = ( AT_MTA_MSG_STRU *)pMsg;
    pstRficSsiRdReq         = ( AT_MTA_RFICSSIRD_REQ_STRU *)pstAtMtaReqMsg->aucContent;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength                = sizeof(MTA_AGENT_RFICSSIRD_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaRficSsiRdReq      = (MTA_AGENT_RFICSSIRD_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaRficSsiRdReq)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvAtRficSsiRdQryReq: Alloc msg fail!");
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstMtaRficSsiRdReq + VOS_MSG_HEAD_LENGTH, 0, ulLength);

    /* ������Ϣ�ṹ�� */
    MTA_FILL_MSG_HEADER(pstMtaRficSsiRdReq, TLPHY_PID_RTTAGENT);
    pstMtaRficSsiRdReq->usMsgID           = ID_MTA_AGENT_RFIC_SSI_RD_NTF;
    pstMtaRficSsiRdReq->usChannelNo       = pstRficSsiRdReq->usChannelNo;
    pstMtaRficSsiRdReq->usRficReg         = pstRficSsiRdReq->usRficReg;

    /* ������Ϣ��TLPHY */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaRficSsiRdReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndTlphyAfclockStatusNtf: Send msg fail!");
    }

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTlPhyRficSsiRdInd
 ��������  : tafģ���յ�mta������RFICSSIRD�ظ���Ϣ�Ĵ�����
 �������  : pMsg   -- AT���͵���Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��29��
    ��    ��   : x00316382
    �޸�����   : ����
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTlPhyRficSsiRdInd(VOS_VOID *pMsg)
{
    APM_MTA_RFICSSIRD_IND_STRU             *pstRficSsiRdInd = VOS_NULL_PTR;
    MTA_AT_RFICSSIRD_CNF_STRU               stRficSsiRdInd;
    AT_APPCTRL_STRU                         stAppCtrl;

    pstRficSsiRdInd     = (APM_MTA_RFICSSIRD_IND_STRU *)pMsg;

    PS_MEM_SET(&stRficSsiRdInd, 0, sizeof(stRficSsiRdInd));
    PS_MEM_SET(&stAppCtrl, 0, sizeof(stAppCtrl));

    stRficSsiRdInd.ulRegValue   = pstRficSsiRdInd->ulRegValue;
    stAppCtrl.usClientId        = MTA_CLIENTID_BROADCAST;
    stAppCtrl.ucOpId            = MTA_INVALID_TAB_INDEX;

    TAF_MTA_SndAtMsg(&stAppCtrl,
                     ID_MTA_AT_RFICSSIRD_QRY_CNF,
                     sizeof(stRficSsiRdInd),
                     (VOS_UINT8*)&stRficSsiRdInd);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndRcmAfcClkAndXoCoEfReq
 ��������  : send rcm the afcclk and xocoef req
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��24��
    ��    ��   : c00299064
    �޸�����   : ����
*****************************************************************************/
VOS_VOID TAF_MTA_SndRcmAfcClkAndXoCoEfQryReq(
    VOS_VOID
)
{
    MTA_RCM_AFC_CLK_INFO_QRY_REQ_STRU  *pstAfcReq;

    pstAfcReq = (MTA_RCM_AFC_CLK_INFO_QRY_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA,
                                                    sizeof(MTA_RCM_AFC_CLK_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstAfcReq)
    {
        return;
    }

    pstAfcReq->ulReceiverPid    =   DSP_PID_RCM;

    PS_MEM_SET((VOS_UINT8*)pstAfcReq + VOS_MSG_HEAD_LENGTH, 0, sizeof(MTA_RCM_AFC_CLK_INFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstAfcReq->usMsgID          =   ID_MTA_RCM_AFC_CLK_INFO_QRY_REQ;

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_MTA, pstAfcReq);

    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


