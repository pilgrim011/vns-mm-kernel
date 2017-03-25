/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMtaModemInfoQuery.c
  �� �� ��   : ����
  ��    ��   : zwx247453
  ��������   : 2015��10��19��
  ����޸�   :
  ��������   : MTAģ�鴦��AT���·���ѯ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : Network Monitor����

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TafMtaModemInfoQuery.h"
#include "TafSdcLib.h"
#include "TafMtaComm.h"
#include "TafMtaMain.h"
#include "MtaRrcInterface.h"
#include "NasUtranCtrlInterface.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID                 PS_FILE_ID_TAF_MTA_MODEM_INFO_QUERY_C
/*lint +e767 */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvQryWrrAutotestReq
 ��������  : MTA����at����^WAS
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��18��
    ��    ��   : s00217060
    �޸�����   : DTS2013031800705���ػ�״̬�·�CWAS�ظ�ERROR
*****************************************************************************/
VOS_VOID TAF_MTA_RcvQryWrrAutotestReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstQryReq       = VOS_NULL_PTR;
    MTA_WRR_AUTOTEST_PARA_STRU         *pstRrcAtQryPara = VOS_NULL_PTR;
    MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU    stQryCnf;
    VOS_UINT32                          ulResult;
    /* ����UtranMode�ж��Ƿ��was������Ϣ����Ϊƽ̨֧��FDD������WAS������Ϣ */

    pstQryReq          = (AT_MTA_MSG_STRU *)pMsg;
    pstRrcAtQryPara    = (MTA_WRR_AUTOTEST_PARA_STRU *)pstQryReq->aucContent;
    ulResult           = VOS_ERR;

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF))
    {
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                      ID_MTA_AT_WRR_AUTOTEST_QRY_CNF,
                      sizeof(stQryCnf),
                      (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* ���ƽ̨֧��Wģ�����������as�������at�ظ�ʧ�� */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        /* �յ�at�������󣬷�������Ϣ֪ͨas */
        ulResult = TAF_MTA_SndWrrQryAutotestReqMsg(pstRrcAtQryPara);
    }

    if (ulResult != VOS_OK)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                         ID_MTA_AT_WRR_AUTOTEST_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF,
                        TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF,
                                     (VOS_UINT8*)&pstQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvQryWrrCellInfoReq
 ��������  : MTA����at����^CELLINFO��ѯС����Ϣ
 �������  : void *pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��18��
    ��    ��   : s00217060
    �޸�����   : DTS2013031800705���ػ�״̬�·�CWAS�ظ�ERROR
*****************************************************************************/
VOS_VOID TAF_MTA_RcvQryWrrCellInfoReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstQryCellinfoReq = VOS_NULL_PTR;
    MTA_AT_WRR_CELLINFO_QRY_CNF_STRU    stQryCnf;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulAtCmdCellInfo;
    /* ����UtranMode�ж��Ƿ��was������Ϣ����Ϊƽ̨֧��FDD������WAS������Ϣ */

    ulAtCmdCellInfo        = 0;
    pstQryCellinfoReq      = (AT_MTA_MSG_STRU *)pMsg;
    ulResult               = VOS_ERR;

    PS_MEM_CPY(&ulAtCmdCellInfo, pstQryCellinfoReq->aucContent, sizeof(VOS_UINT32));

    PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));

    /* �����ǰ��ʱ�������������AT�ظ���ѯʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF))
    {
        stQryCnf.ulResult = VOS_ERR;
        TAF_MTA_SndAtMsg(&pstQryCellinfoReq->stAppCtrl,
                        ID_MTA_AT_WRR_CELLINFO_QRY_CNF,
                        sizeof(stQryCnf),
                        (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* ���ƽ̨֧��Wģ�����������as�������at�ظ�ʧ�� */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        ulResult = TAF_MTA_SndWrrQryCellinfoReqMsg(ulAtCmdCellInfo);
    }

    /* �����ǰ��Utranģʽ����FDDģʽ,ulResultΪVOS_ERR��
       ���߸�����㷢����Ϣʧ��,ulResultҲΪVOS_ERR����AT�ظ���ѯʧ�� */
    if (VOS_OK != ulResult)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryCellinfoReq->stAppCtrl,
                         ID_MTA_AT_WRR_CELLINFO_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );

        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF, TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF,
                                     (VOS_UINT8*)&pstQryCellinfoReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvQryWrrMeanrptReq
 ��������  : MTA����^MEANRPT����
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��3��18��
    ��    ��   : s00217060
    �޸�����   : DTS2013031800705���ػ�״̬�·�CWAS�ظ�ERROR
*****************************************************************************/
VOS_VOID TAF_MTA_RcvQryWrrMeanrptReq(
    VOS_VOID                           *pMsg
)
{

    AT_MTA_MSG_STRU                    *pstQryReq = VOS_NULL_PTR;
    MTA_AT_WRR_MEANRPT_QRY_CNF_STRU     stQryCnf;
    VOS_UINT32                          ulResult;
    /* ����UtranMode�ж��Ƿ��was������Ϣ����Ϊƽ̨֧��FDD������WAS������Ϣ */

    pstQryReq           = (AT_MTA_MSG_STRU *)pMsg;
    ulResult            = VOS_ERR;
    PS_MEM_SET(&stQryCnf, 0x0, sizeof(stQryCnf));

    /* �����ǰ��ʱ�������������AT�ظ���ѯʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF))
    {
        stQryCnf.ulResult = VOS_ERR;
        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                      ID_MTA_AT_WRR_MEANRPT_QRY_CNF,
                      sizeof(stQryCnf),
                      (VOS_UINT8*)&stQryCnf );
        return;
    }

    /* ���ƽ̨֧��Wģ�����������as�������at�ظ�ʧ�� */
    if ( VOS_TRUE == TAF_SDC_IsPlatformSupportUtranFdd() )
    {
        /* �յ�at�������󣬷�������Ϣ֪ͨas */
        ulResult = TAF_MTA_SndWrrQryMeanrptReqMsg();
    }

    if (VOS_OK != ulResult)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        stQryCnf.ulResult = VOS_ERR;

        TAF_MTA_SndAtMsg(&pstQryReq->stAppCtrl,
                         ID_MTA_AT_WRR_MEANRPT_QRY_CNF,
                         sizeof(stQryCnf),
                         (VOS_UINT8*)&stQryCnf );

        return;
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF, TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF,
                                     (VOS_UINT8*)&pstQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndWrrQryAutotestReqMsg
 ��������  : ��as����mntn��ѯ��Ϣ
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��31��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndWrrQryAutotestReqMsg(
    MTA_WRR_AUTOTEST_PARA_STRU         *pAutotestQryPara
)
{
    VOS_UINT32                          ulLength;
    MTA_WRR_AUTOTEST_QRY_REQ_STRU      *pstMtaWrrQryReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength              = sizeof(MTA_WRR_AUTOTEST_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrQryReq       = (MTA_WRR_AUTOTEST_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);

    if (VOS_NULL_PTR == pstMtaWrrQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryAutotestReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* ������Ϣ�ṹ�� */
    pstMtaWrrQryReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrQryReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrQryReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrQryReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrQryReq->ulMsgName         = ID_MTA_WRR_AUTOTEST_QRY_REQ;

    /* ���ݸ���Ϣ������ */
    PS_MEM_CPY(&(pstMtaWrrQryReq->stWrrAutotestPara),
        pAutotestQryPara,
        sizeof(MTA_WRR_AUTOTEST_PARA_STRU));

    /* ������Ϣ��AS */
    if ( VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrQryReq) )
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryAutotestReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndWrrQryCellinfoReqMsg
 ��������  : ��as����Cellinfo��ѯ��Ϣ
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��31��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndWrrQryCellinfoReqMsg(
    VOS_UINT32                          ulSetCellInfo
)
{
    VOS_UINT32                          ulLength;
    MTA_WRR_CELLINFO_QRY_REQ_STRU      *pstMtaWrrQryCellinfoReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength                    = sizeof(MTA_WRR_CELLINFO_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrQryCellinfoReq     = (MTA_WRR_CELLINFO_QRY_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstMtaWrrQryCellinfoReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryCellinfoReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* ������Ϣ�ṹ�� */
    pstMtaWrrQryCellinfoReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrQryCellinfoReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrQryCellinfoReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrQryCellinfoReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrQryCellinfoReq->ulMsgName         = ID_MTA_WRR_CELLINFO_QRY_REQ;
    pstMtaWrrQryCellinfoReq->ulSetCellInfo     = ulSetCellInfo;

    /* ������Ϣ��AS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrQryCellinfoReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryCellinfoReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}



/*****************************************************************************
 �� �� ��  : TAF_MTA_SndWrrQryMeanrptReqMsg
 ��������  : ��as���Ͳ�ѯmeanrpt��ѯ��Ϣ
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��31��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndWrrQryMeanrptReqMsg( VOS_VOID )
{
    VOS_UINT32                          ulLength;
    MTA_WRR_MEANRPT_QRY_REQ_STRU       *pstMtaWrrQryMeanrptReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength                    = sizeof(MTA_WRR_MEANRPT_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMtaWrrQryMeanrptReq      = (MTA_WRR_MEANRPT_QRY_REQ_STRU*)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstMtaWrrQryMeanrptReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryMeanrptReqMsg: Alloc msg fail!");
        return VOS_ERR;
    }

    /* ������Ϣ�ṹ�� */
    pstMtaWrrQryMeanrptReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMtaWrrQryMeanrptReq->ulSenderPid       = UEPS_PID_MTA;
    pstMtaWrrQryMeanrptReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMtaWrrQryMeanrptReq->ulReceiverPid     = WUEPS_PID_WRR;
    pstMtaWrrQryMeanrptReq->ulMsgName         = ID_MTA_WRR_MEASRPT_QRY_REQ;

    /* ������Ϣ��AS */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstMtaWrrQryMeanrptReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndWrrQryMeanrptReqMsg: Send msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvWrrAutotestQryCnf
 ��������  : MTA�յ�was�ظ���MNTN��Ϣ
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_RcvWrrAutotestQryCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf            = VOS_NULL_PTR;
    WRR_MTA_AUTOTEST_QRY_CNF_STRU      *pstRcvWrrAutotestCnf = VOS_NULL_PTR;
    MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU    stSndAtAutotestCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrAutotestQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrAutotestQryCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrAutotestCnf                 = (WRR_MTA_AUTOTEST_QRY_CNF_STRU *)pWrrCnfMsg;
    stSndAtAutotestCnf.ulResult          = pstRcvWrrAutotestCnf->ulResult;
    stSndAtAutotestCnf.stWrrAutoTestRslt.ulRsltNum = pstRcvWrrAutotestCnf->stWrrAutoTestRslt.ulRsltNum;
    PS_MEM_CPY(stSndAtAutotestCnf.stWrrAutoTestRslt.aulRslt,
               pstRcvWrrAutotestCnf->stWrrAutoTestRslt.aulRslt,
               sizeof(pstRcvWrrAutotestCnf->stWrrAutoTestRslt.aulRslt));

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_AUTOTEST_QRY_CNF,
                     sizeof(stSndAtAutotestCnf),
                     (VOS_UINT8*)&stSndAtAutotestCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvWrrCellInfoQryCnf
 ��������  : MTA�յ�WAS�ظ���CELLINFO��Ϣ
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_RcvWrrCellInfoQryCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf            = VOS_NULL_PTR;
    WRR_MTA_CELLINFO_QRY_CNF_STRU      *pstRcvWrrCellinfoCnf = VOS_NULL_PTR;
    MTA_AT_WRR_CELLINFO_QRY_CNF_STRU    stSndAtCellinfoQryCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrCellInfoQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrCellInfoQryCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrCellinfoCnf           = (WRR_MTA_CELLINFO_QRY_CNF_STRU *)pWrrCnfMsg;
    stSndAtCellinfoQryCnf.ulResult = pstRcvWrrCellinfoCnf->ulResult;
    PS_MEM_CPY(&(stSndAtCellinfoQryCnf.stWrrCellInfo),
                &(pstRcvWrrCellinfoCnf->stWrrCellInfo),
                sizeof(pstRcvWrrCellinfoCnf->stWrrCellInfo));

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_CELLINFO_QRY_CNF,
                     sizeof(stSndAtCellinfoQryCnf),
                     (VOS_UINT8*)&stSndAtCellinfoQryCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvWrrMeanrptQryCnf
 ��������  : �յ�was�ظ���MEANRPT��Ϣ
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_RcvWrrMeanrptQryCnf(
    VOS_VOID                           *pWrrCnfMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf           = VOS_NULL_PTR;
    WRR_MTA_MEANRPT_QRY_CNF_STRU       *pstRcvWrrMeanrptCnf = VOS_NULL_PTR;
    MTA_AT_WRR_MEANRPT_QRY_CNF_STRU     stSndAtMeanrptQryCnf;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrMeanrptQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrMeanrptQryCnf: get command buffer failed!");
        return;
    }

    pstRcvWrrMeanrptCnf                         = (WRR_MTA_MEANRPT_QRY_CNF_STRU *)pWrrCnfMsg;
    stSndAtMeanrptQryCnf.ulResult               = pstRcvWrrMeanrptCnf->ulResult;
    stSndAtMeanrptQryCnf.stMeanRptRslt.ulRptNum = pstRcvWrrMeanrptCnf->stMeanRptRslt.ulRptNum;
    PS_MEM_CPY((stSndAtMeanrptQryCnf.stMeanRptRslt.astMeanRptInfo), pstRcvWrrMeanrptCnf->stMeanRptRslt.astMeanRptInfo, sizeof(pstRcvWrrMeanrptCnf->stMeanRptRslt.astMeanRptInfo));

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_MEANRPT_QRY_CNF,
                     sizeof(stSndAtMeanrptQryCnf),
                     (VOS_UINT8*)&stSndAtMeanrptQryCnf);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF);
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiReqAutotestQryExpired
 ��������  : CWAS����ִ�г�ʱ
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiReqAutotestQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_AUTOTEST_QRY_CNF_STRU    stQryAutotestCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_AUTOTEST_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*��ʱ����ʱlog*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqAutotestQryExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stQryAutotestCnf, 0x0, sizeof(stQryAutotestCnf));

    stQryAutotestCnf.ulResult = VOS_ERR;

    /* �ϱ���ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_AUTOTEST_QRY_CNF,
                     sizeof(stQryAutotestCnf),
                     (VOS_UINT8*)&stQryAutotestCnf );


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiReqCellInfoQryExpired
 ��������  : ^CELLINFOִ�г�ʱ����
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiReqCellInfoQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_CELLINFO_QRY_CNF_STRU    stCellinfoQryCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_CELLINFO_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*��ʱ����ʱlog*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqCellInfoQryExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stCellinfoQryCnf, 0x0, sizeof(stCellinfoQryCnf));

    stCellinfoQryCnf.ulResult = VOS_ERR;

    /* �ϱ���ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_CELLINFO_QRY_CNF,
                     sizeof(stCellinfoQryCnf),
                     (VOS_UINT8*)&stCellinfoQryCnf );


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;

}



/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiReqMeanrptQryExpired
 ��������  : ^MEANRPTִ�г�ʱ����
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��29��
    ��    ��   : m00217266
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiReqMeanrptQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_WRR_MEANRPT_QRY_CNF_STRU     stMeanrptQryCnf;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_WRR_MEANRPT_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*��ʱ����ʱlog*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiReqMeanrptQryExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stMeanrptQryCnf, 0x0, sizeof(stMeanrptQryCnf));

    stMeanrptQryCnf.ulResult = VOS_ERR;

    /* �ϱ���ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_WRR_MEANRPT_QRY_CNF,
                     sizeof(stMeanrptQryCnf),
                     (VOS_UINT8*)&stMeanrptQryCnf );


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtTransModeQryReq
 ��������  : mta�յ�ID_AT_MTA_TRANSMODE_QRY_REQ��Ϣ������
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 ��    ��   : 2015��7��30��
 ��    ��   : lwx277467
 �޸�����   : ^TRANSMODE��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtTransModeQryReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                    *pstTransModeQryReq      = VOS_NULL_PTR;
    MTA_AT_TRANSMODE_QRY_CNF_STRU       stTransModeQryCnf;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enRatType;

    pstTransModeQryReq      = (AT_MTA_MSG_STRU *)pMsg;
    enRatType               = TAF_SDC_GetSysMode();
    PS_MEM_SET(&stTransModeQryCnf, 0x0, sizeof(stTransModeQryCnf));

    /* ��ѯ�Ƿ���LTEģʽ�£����򷵻�ʧ��*/
    if (TAF_SDC_SYS_MODE_LTE != enRatType)
    {
        stTransModeQryCnf.enResult = MTA_AT_RESULT_INCORRECT_PARAMETERS;

        TAF_MTA_SndAtMsg(&pstTransModeQryReq->stAppCtrl,
                      ID_MTA_AT_TRANSMODE_QRY_CNF,
                      sizeof(stTransModeQryCnf),
                      (VOS_UINT8*)&stTransModeQryCnf );

        return;
    }

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF))
    {
        stTransModeQryCnf.enResult = MTA_AT_RESULT_ERROR;

        TAF_MTA_SndAtMsg(&pstTransModeQryReq->stAppCtrl,
                      ID_MTA_AT_TRANSMODE_QRY_CNF,
                      sizeof(stTransModeQryCnf),
                      (VOS_UINT8*)&stTransModeQryCnf );
        return;
    }

#if (FEATURE_ON == FEATURE_LTE)
    TAF_MTA_SndLrrcTransModeQryReq();

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF, TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF,
                                     (VOS_UINT8*)&pstTransModeQryReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
#else
    stTransModeQryCnf.enResult = MTA_AT_RESULT_ERROR;

    TAF_MTA_SndAtMsg(&pstTransModeQryReq->stAppCtrl,
                  ID_MTA_AT_TRANSMODE_QRY_CNF,
                  sizeof(stTransModeQryCnf),
                  (VOS_UINT8*)&stTransModeQryCnf );
#endif
    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLrrcTransModeQryReq
 ��������  : MTA����ϢID_MTA_LRRC_TRANSMODE_QRY_REQ��LRRC��ѯLTE����ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��30��
    ��    ��   : lwx277467
    �޸�����   : ����^TRANSMODE����
*****************************************************************************/
VOS_VOID TAF_MTA_SndLrrcTransModeQryReq(VOS_VOID)
{
    VOS_UINT32                           ulLength;
    MTA_LRRC_TRANSMODE_QRY_REQ_STRU     *pstTransModeQryReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    ulLength               = sizeof(MTA_LRRC_TRANSMODE_QRY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstTransModeQryReq     = (MTA_LRRC_TRANSMODE_QRY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA, ulLength);
    if (VOS_NULL_PTR == pstTransModeQryReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcTransModeQryReq: Alloc msg fail!");
        return;
    }

    /* ������Ϣ�ṹ�� */
    pstTransModeQryReq->stMsgHeader.ulSenderPid       = UEPS_PID_MTA;
    pstTransModeQryReq->stMsgHeader.ulReceiverPid     = PS_PID_ERRC;
    pstTransModeQryReq->stMsgHeader.ulMsgName         = ID_MTA_LRRC_TRANSMODE_QRY_REQ;

    PS_MEM_SET(pstTransModeQryReq->aucReserved, 0, sizeof(pstTransModeQryReq->aucReserved));

    /* ������Ϣ��LTE */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstTransModeQryReq))
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcTransModeQryReq(): Send MSG Fail!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLrrcTransModeQryCnf
 ��������  : MTA�յ�LTE����㴫��ģʽ��ѯ�ظ���Ϣ������
 �������  : pMsg  -- ��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��30��
    ��    ��   : lwx277467
    �޸�����   : ����^TRANSMODE����
*****************************************************************************/
VOS_VOID TAF_MTA_RcvLrrcTransModeQryCnf(VOS_VOID *pMsg)
{
    TAF_MTA_CMD_BUFFER_STRU             *pstCmdBuf          = VOS_NULL_PTR;
    LRRC_MTA_TRANSMODE_QRY_CNF_STRU     *pstTransModeQryCnf = VOS_NULL_PTR;
    MTA_AT_TRANSMODE_QRY_CNF_STRU        stMtaAtTransModeQryCnf;

    PS_MEM_SET(&stMtaAtTransModeQryCnf, 0x00, sizeof(MTA_AT_TRANSMODE_QRY_CNF_STRU));

    pstTransModeQryCnf = (LRRC_MTA_TRANSMODE_QRY_CNF_STRU *)pMsg;

    /* �����ǰ��ʱ����Ϊ����״̬ */
    if (TAF_MTA_TIMER_STATUS_RUNING != TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcTransModeQryCnf: Timer was already stoped!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF);
    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvLrrcTransModeQryCnf: No Buffer!");
        return;
    }

    if (MTA_RRC_RESULT_NO_ERROR != pstTransModeQryCnf->enResult)
    {
        stMtaAtTransModeQryCnf.enResult    = MTA_AT_RESULT_ERROR;
    }
    else
    {
        stMtaAtTransModeQryCnf.enResult    = MTA_AT_RESULT_NO_ERROR;
        stMtaAtTransModeQryCnf.ucTransMode = pstTransModeQryCnf->ucTransMode;
    }

    TAF_MTA_SndAtMsg( (AT_APPCTRL_STRU *)(pstCmdBuf->pucMsgInfo),
                      ID_MTA_AT_TRANSMODE_QRY_CNF,
                      sizeof(MTA_AT_TRANSMODE_QRY_CNF_STRU),
                      (VOS_UINT8*)&stMtaAtTransModeQryCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitLrrcTransModeQryExpired
 ��������  : ��ѯLTE����ģʽ��ʱ�Ĵ�����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2015��08��04��
    ��    ��   : lwx277467
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitLrrcTransModeQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_TRANSMODE_QRY_CNF_STRU       stMtaAtTransModeQryCnf;

    PS_MEM_SET(&stMtaAtTransModeQryCnf, 0, sizeof(MTA_AT_TRANSMODE_QRY_CNF_STRU));

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_TRANSMODE_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        /*��ʱ����ʱlog*/
        MTA_ERROR_LOG("TAF_MTA_RcvTiWaitLrrcTransModeQryExpired: get command buffer failed!");
        return;
    }

    PS_MEM_SET(&stMtaAtTransModeQryCnf, 0x0, sizeof(stMtaAtTransModeQryCnf));

    stMtaAtTransModeQryCnf.enResult = VOS_ERR;

    /* �ϱ���ATģ�������Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_TRANSMODE_QRY_CNF,
                     sizeof(stMtaAtTransModeQryCnf),
                     (VOS_UINT8*)&stMtaAtTransModeQryCnf );


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(pstCmdBuf->enTimerId);

    return;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtSetNetMonSCellReq
 ��������  : ����at�·�������MONSC����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : �½�

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetNetMonSCellReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstSetReq = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU        stMoncellInfo;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulReceiverPid;

    PS_MEM_SET(&stMoncellInfo, 0, sizeof(MTA_AT_NETMON_CELL_INFO_STRU));
    pstSetReq                     = (AT_MTA_MSG_STRU *)pMsg;
    ulResult                      = VOS_ERR;
    ulMsgName                     = TAF_SDC_SYS_MODE_GSM;
    ulReceiverPid                 = UEPS_PID_GAS;
    stMoncellInfo.enResult        = MTA_AT_RESULT_ERROR;

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF))
    {
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_SET_NETMON_SCELL_CNF,
                         sizeof(MTA_AT_NETMON_CELL_INFO_STRU),
                         (VOS_UINT8*)&stMoncellInfo);
        return;
    }

    ulResult = TAF_MTA_GetNetMonSndMsgInfo(&ulMsgName, &ulReceiverPid);
    if (VOS_OK != ulResult)
    {
        /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_SET_NETMON_SCELL_CNF,
                         sizeof(MTA_AT_NETMON_CELL_INFO_STRU),
                         (VOS_UINT8*)&stMoncellInfo);
        return;
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (PS_PID_ERRC == ulReceiverPid)
    {
        TAF_MTA_SndLrrcSetNetMonCellReq(ulMsgName, ulReceiverPid, MTA_NETMON_SCELL_TYPE);
    }
    else
#endif
    {
        TAF_MTA_SndRrcSetNetMonCellReq(ulMsgName, ulReceiverPid, MTA_NETMON_SCELL_TYPE);
    }

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF,
                                 TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
   TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF,
                                   (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                    sizeof(AT_APPCTRL_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtSetNetMonNCellReq
 ��������  : ����at�·�������MONNC����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : �½�

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetNetMonNCellReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                    *pstSetReq = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU        stMoncellInfo;
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulReceiverPid;

    PS_MEM_SET(&stMoncellInfo, 0, sizeof(MTA_AT_NETMON_CELL_INFO_STRU));
    pstSetReq              = (AT_MTA_MSG_STRU *)pMsg;
    ulResult               = VOS_ERR;
    ulMsgName              = TAF_SDC_SYS_MODE_GSM;
    ulReceiverPid          = UEPS_PID_GAS;
    stMoncellInfo.enResult = MTA_AT_RESULT_ERROR;

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF))
    {
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_SET_NETMON_NCELL_CNF,
                         sizeof(MTA_AT_NETMON_CELL_INFO_STRU),
                         (VOS_UINT8*)&stMoncellInfo);
        return;
    }

   ulResult = TAF_MTA_GetNetMonSndMsgInfo(&ulMsgName, &ulReceiverPid);
   if (VOS_OK != ulResult)
   {
       /* ��Ϣ����ʧ�ܣ���at�ظ�ʧ��*/
       TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                        ID_MTA_AT_SET_NETMON_NCELL_CNF,
                        sizeof(MTA_AT_NETMON_CELL_INFO_STRU),
                        (VOS_UINT8*)&stMoncellInfo);
       return;
   }

   /* �յ�at�������󣬷�������Ϣ֪ͨAS */
#if (FEATURE_ON == FEATURE_LTE)
   if (PS_PID_ERRC == ulReceiverPid)
   {
       TAF_MTA_SndLrrcSetNetMonCellReq(ulMsgName, ulReceiverPid, MTA_NETMON_NCELL_TYPE);
   }
   else
#endif
   {
       TAF_MTA_SndRrcSetNetMonCellReq(ulMsgName, ulReceiverPid, MTA_NETMON_NCELL_TYPE);
   }

   /* ����������ʱ�� */
   (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF,
                                TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF_TIMER_LEN);

   /* �����Ϣ���ȴ����� */
   TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF,
                                   (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                    sizeof(AT_APPCTRL_STRU));
   return;
}
/*****************************************************************************
 �� �� ��  : TAF_MTA_GetNetMonSndMsgInfo
 ��������  : ��ȡҪ������Ϣ��ID ������PID
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 TAF_MTA_GetNetMonSndMsgInfo(
    VOS_UINT32                         *pulMsgName,
    VOS_UINT32                         *pulReceiverPid
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulReceiverPid;
    VOS_UINT32                          ulMsgName;

    ulResult      = VOS_OK;
    ulReceiverPid = UEPS_PID_GAS;
    ulMsgName     = ID_MTA_GRR_NETMON_CELL_QRY_REQ;

    /*���ݵ�ǰģʽȷ�����͵���Ϣ ID ������PID*/
    switch (TAF_SDC_GetSysMode())
    {
        case TAF_SDC_SYS_MODE_GSM:
        {
            ulReceiverPid = UEPS_PID_GAS;
            ulMsgName     = ID_MTA_GRR_NETMON_CELL_QRY_REQ;
            break;
        }
        case TAF_SDC_SYS_MODE_WCDMA:
        {
            /*FDD*/
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                ulReceiverPid = WUEPS_PID_WRR;
                ulMsgName     = ID_MTA_RRC_NETMON_CELL_QRY_REQ;
            }
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
            else if (NAS_UTRANCTRL_UTRAN_MODE_TDD == NAS_UTRANCTRL_GetCurrUtranMode())  /*TDD*/
            {
                ulReceiverPid = TPS_PID_RRC;
                ulMsgName     = ID_MTA_RRC_NETMON_CELL_QRY_REQ;
            }
#endif
            else
            {
                 ulResult = VOS_ERR;
            }
            break;
        }
#if (FEATURE_ON == FEATURE_LTE)
        case TAF_SDC_SYS_MODE_LTE:
        {
            ulReceiverPid = PS_PID_ERRC;
            ulMsgName     = ID_MTA_LRRC_NETMON_CELL_QRY_REQ;
            break;
        }
#endif
        default:
            ulResult = VOS_ERR;
     }

     if (VOS_OK == ulResult)
     {
        *pulReceiverPid = ulReceiverPid;
        *pulMsgName     = ulMsgName;
     }

     return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndRrcSetNetMonCellReq
 ��������  : mta��GUAS����С����Ϣ��ѯ��Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MTA_SndRrcSetNetMonCellReq(
    VOS_UINT32                          ulMsgName,
    VOS_UINT32                          ulReceiverPid,
    MTA_NETMON_CELL_TYPE_ENUM_UINT32    enCelltype
)
{
    MTA_RRC_NETMON_CELL_QRY_REQ_STRU   *pstMtaRrcMonCellReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    pstMtaRrcMonCellReq   = (MTA_RRC_NETMON_CELL_QRY_REQ_STRU*)TAF_MTA_ALLOC_MSG_WITH_HDR(sizeof(MTA_RRC_NETMON_CELL_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstMtaRrcMonCellReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndRrcSetNetMonCellReq: Alloc msg fail!");
        return ;
    }

    /* �����Ϣ���� */
    TAF_MTA_CLR_MSG_ENTITY(pstMtaRrcMonCellReq);

    /* ��д��Ϣͷ */
    TAF_MTA_CFG_MSG_HDR(pstMtaRrcMonCellReq, ulReceiverPid, ulMsgName);

    /* ��д��Ϣ���� */
    pstMtaRrcMonCellReq->enCelltype        = enCelltype;

    /* ������Ϣ��AS */
    TAF_MTA_SEND_MSG(pstMtaRrcMonCellReq);

    /*��¼GSM ��ѯ����С��״̬*/
    if ((UEPS_PID_GAS == ulReceiverPid) &&  (MTA_NETMON_SCELL_TYPE == enCelltype))
    {
        TAF_MTA_SetNetmonGsmState(MTA_AT_NETMON_GSM_STATTE_WAIT_CELL_INFO);
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndGasNetMonQryTaReq
 ��������  : ��GAS�������󣬻�ȡTA��Ϣ
 �������  :
 �������  :
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : �½�

*****************************************************************************/
VOS_UINT32 TAF_MTA_SndGasNetMonQryTaReq(
    AT_APPCTRL_STRU                    *pstAppCtrl
)
{
    MTA_GRR_NETMON_TA_QRY_REQ_STRU     *pstMtaGrrNetMonTaReq = VOS_NULL_PTR;

    /* �����ǰ��ʱ�����������򷵻�ʧ�� */
    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF))
    {
        return VOS_ERR;
    }

    /* ������Ϣ�ṹ�ڴ� */
    pstMtaGrrNetMonTaReq  = (MTA_GRR_NETMON_TA_QRY_REQ_STRU*)TAF_MTA_ALLOC_MSG_WITH_HDR(sizeof(MTA_GRR_NETMON_TA_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstMtaGrrNetMonTaReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndGasNetMonQryTaReq: Alloc msg fail!");
        return VOS_ERR;
    }

    /* �����Ϣ���� */
    TAF_MTA_CLR_MSG_ENTITY(pstMtaGrrNetMonTaReq);

    /* ��д��Ϣͷ */
    TAF_MTA_CFG_MSG_HDR(pstMtaGrrNetMonTaReq, UEPS_PID_GAS, ID_MTA_GRR_NETMON_TA_QRY_REQ);

    /* ������Ϣ��AS */
    TAF_MTA_SEND_MSG(pstMtaGrrNetMonTaReq);

    /* ����������ʱ�� */
    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF,
                                 TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF,
                                    (VOS_UINT8*)pstAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvGasNetMonTaQryCnf
 ��������  : MTA�յ�GAS ID_MTA_GAS_QRY_TA_CNF��Ϣ������
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvGasNetMonTaQryCnf(
    VOS_VOID                           *pMsg
)
{
    GRR_MTA_NETMON_TA_QRY_CNF_STRU     *pstGQryTA            = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf            = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU       *pstNetMonCellInfo    = VOS_NULL_PTR;

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvGasNetMonTaQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvGasNetMonTaQryCnf: get command buffer failed!");
        return;
    }

    pstGQryTA = (GRR_MTA_NETMON_TA_QRY_CNF_STRU *)pMsg;

    if (MTA_AT_NETMON_GSM_STATTE_WAIT_TA == TAF_MTA_GetNetmonGsmState())
    {
        TAF_MTA_SetNetmonGsmState(MTA_AT_NETMON_GSM_STATE_INIT);

        pstNetMonCellInfo = TAF_MTA_GetNetmonCellInfo();

        /* ��д�����ϱ�����Ϣ���� */
        if (MTA_NETMON_RESULT_NO_ERR == pstGQryTA->enResult)
        {
            if (TAF_MTA_NETMON_GSM_TA_INVALID_VALUE == pstGQryTA->usTa)
            {
                pstNetMonCellInfo->unSCellInfo.stGsmSCellInfo.bitOpTa = PS_IE_NOT_PRESENT;
                pstNetMonCellInfo->unSCellInfo.stGsmSCellInfo.usTa    = 0xFFFF;
            }
            else
            {
                pstNetMonCellInfo->unSCellInfo.stGsmSCellInfo.bitOpTa = PS_IE_PRESENT;
                pstNetMonCellInfo->unSCellInfo.stGsmSCellInfo.usTa    = pstGQryTA->usTa;
            }
        }
        else
        {
            pstNetMonCellInfo->unSCellInfo.stGsmSCellInfo.bitOpTa = PS_IE_NOT_PRESENT;
            pstNetMonCellInfo->unSCellInfo.stGsmSCellInfo.usTa    = 0xFFFF;
        }
        /* ��at����Ϣ */
        TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                         ID_MTA_AT_SET_NETMON_SCELL_CNF,
                         sizeof(MTA_AT_NETMON_CELL_INFO_STRU),
                         (VOS_UINT8*)pstNetMonCellInfo);
    }

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvGasNetMonCellQryCnf
 ��������  : MTA�յ�GAS ID_RRC_MTA_MON_CELL_INFO_CNF��Ϣ������
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvGasNetMonCellQryCnf(
    VOS_VOID                           *pMsg
)
{
    GRR_MTA_NETMON_CELL_QRY_CNF_STRU    *pstGsmNetMonCellInfo = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU             *pstCmdBuf            = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU        *pstNetMonCellInfo    = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU         stMtaAtInd;
    VOS_UINT32                           ulMsgId;
    TAF_MTA_TIMER_ID_ENUM_UINT32         enTimerId;

    pstGsmNetMonCellInfo = (GRR_MTA_NETMON_CELL_QRY_CNF_STRU *)pMsg;
    PS_MEM_SET(&stMtaAtInd, 0, sizeof(MTA_AT_NETMON_CELL_INFO_STRU));

    if (MTA_NETMON_SCELL_TYPE == pstGsmNetMonCellInfo->enCelltype)
    {
        enTimerId = TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF;
        ulMsgId   = ID_MTA_AT_SET_NETMON_SCELL_CNF;
        PS_MEM_CPY(&stMtaAtInd.unSCellInfo.stGsmSCellInfo.stSCellInfo,
                   &pstGsmNetMonCellInfo->u.stSCellinfo,
                   sizeof(GRR_MTA_NETMON_SCELL_INFO_STRU));
    }
    else if (MTA_NETMON_NCELL_TYPE == pstGsmNetMonCellInfo->enCelltype)
    {
        enTimerId = TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF;
        ulMsgId   = ID_MTA_AT_SET_NETMON_NCELL_CNF;
        PS_MEM_CPY(&stMtaAtInd.stNCellInfo,
                   &pstGsmNetMonCellInfo->u.stNCellinfo,
                   sizeof(RRC_MTA_NETMON_NCELL_INFO_STRU));
    }
    else
    {
        MTA_WARNING_LOG("TAF_MTA_RcvGasNetMonCellQryCnf: WARNING: Celltype error!");
        return;
    }

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(enTimerId))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvGasNetMonCellQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(enTimerId);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(enTimerId);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvGasNetMonCellQryCnf: get command buffer failed!");
        return;
    }

    /* ���سɹ�������»�ȡ������� */
    if (MTA_NETMON_RESULT_NO_ERR == pstGsmNetMonCellInfo->enResult)
    {
        stMtaAtInd.enResult = MTA_AT_RESULT_NO_ERROR;

        /* �ж�GSM��������Ϣ�Ƿ���С����Ϣ����������Ϣ */
        if (MTA_NETMON_SCELL_TYPE == pstGsmNetMonCellInfo->enCelltype)
        {
            /* ��GAS������Ϣ����ȡTA */
            if (VOS_OK == TAF_MTA_SndGasNetMonQryTaReq((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo))
            {
                /* �ӵȴ�������ɾ����Ϣ */
                TAF_MTA_DelItemInCmdBufferQueue(enTimerId);

                pstNetMonCellInfo = TAF_MTA_GetNetmonCellInfo();

                /* �������в��� */
                PS_MEM_SET(pstNetMonCellInfo, 0, sizeof(MTA_AT_NETMON_CELL_INFO_STRU));
                PS_MEM_CPY(&pstNetMonCellInfo->unSCellInfo.stGsmSCellInfo.stSCellInfo,
                           &pstGsmNetMonCellInfo->u.stSCellinfo,
                           sizeof(GRR_MTA_NETMON_SCELL_INFO_STRU));

                pstNetMonCellInfo->enResult    = pstGsmNetMonCellInfo->enResult;
                pstNetMonCellInfo->enCellType  = pstGsmNetMonCellInfo->enCelltype;
                pstNetMonCellInfo->enRatType   = MTA_AT_NETMON_CELL_INFO_GSM;

                TAF_MTA_SetNetmonGsmState(MTA_AT_NETMON_GSM_STATTE_WAIT_TA);

                return;
            }
            else
            {
                TAF_MTA_SetNetmonGsmState(MTA_AT_NETMON_GSM_STATE_INIT);

                stMtaAtInd.unSCellInfo.stGsmSCellInfo.bitOpTa = PS_IE_NOT_PRESENT;
                stMtaAtInd.unSCellInfo.stGsmSCellInfo.usTa    = 0xFFFF;
            }
        }
    }
    else
    {
         stMtaAtInd.enResult = MTA_AT_RESULT_ERROR;
    }
    stMtaAtInd.enRatType  = MTA_AT_NETMON_CELL_INFO_GSM;
    stMtaAtInd.enCellType = pstGsmNetMonCellInfo->enCelltype;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ulMsgId,
                     sizeof(MTA_AT_NETMON_CELL_INFO_STRU),
                     (VOS_UINT8*)&stMtaAtInd);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(enTimerId);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvWrrNetMonCellQryCnf
 ��������  : MTA�յ�WRR ID_RRC_MTA_MON_CELL_INFO_CNF��Ϣ������
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvWrrNetMonCellQryCnf(
    VOS_VOID                           *pMsg
)
{
    RRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU  *pstUtranNetMonCellInfo = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU                *pstCmdBuf              = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU            stMtaAtInd;
    VOS_UINT32                              ulMsgId;
    TAF_MTA_TIMER_ID_ENUM_UINT32            enTimerId;

    pstUtranNetMonCellInfo = (RRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU *)pMsg;

    PS_MEM_SET(&stMtaAtInd, 0, sizeof(MTA_AT_NETMON_CELL_INFO_STRU));

    if (MTA_NETMON_SCELL_TYPE == pstUtranNetMonCellInfo->enCelltype)
    {
        enTimerId = TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF;
        ulMsgId   = ID_MTA_AT_SET_NETMON_SCELL_CNF;
        PS_MEM_CPY(&stMtaAtInd.unSCellInfo.stUtranSCellInfo,
                   &pstUtranNetMonCellInfo->u.stSCellinfo,
                   sizeof(RRC_MTA_NETMON_UTRAN_SCELL_INFO_STRU));
    }
    else if (MTA_NETMON_NCELL_TYPE == pstUtranNetMonCellInfo->enCelltype)
    {
        enTimerId = TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF;
        ulMsgId   = ID_MTA_AT_SET_NETMON_NCELL_CNF;
        PS_MEM_CPY(&stMtaAtInd.stNCellInfo,
                   &pstUtranNetMonCellInfo->u.stNCellinfo,
                   sizeof(RRC_MTA_NETMON_NCELL_INFO_STRU));
    }
    else
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrNetMonCellQryCnf: WARNING: Celltype error!");
        return;
    }

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(enTimerId))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrNetMonCellQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(enTimerId);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(enTimerId);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvWrrNetMonCellQryCnf: get command buffer failed!");
        return;
    }

    /* ��д�����ϱ�����Ϣ���� */
    if (MTA_NETMON_RESULT_NO_ERR == pstUtranNetMonCellInfo->enResult)
    {
        stMtaAtInd.enResult = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        stMtaAtInd.enResult = MTA_AT_RESULT_ERROR;
    }

    stMtaAtInd.enRatType  = MTA_AT_NETMON_CELL_INFO_UTRAN_FDD;
    stMtaAtInd.enCellType = pstUtranNetMonCellInfo->enCelltype;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ulMsgId,
                     sizeof(stMtaAtInd),
                     (VOS_UINT8*)&stMtaAtInd);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(enTimerId);

    return;
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_MTA_SndLrrcSetNetMonCellReq
 ��������  : mta��Lrrc����С����Ϣ��ѯ��Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MTA_SndLrrcSetNetMonCellReq(
    VOS_UINT32                          ulMsgName,
    VOS_UINT32                          ulReceiverPid,
    MTA_NETMON_CELL_TYPE_ENUM_UINT32    enCelltype
)
{
    MTA_LRRC_NETMON_CELL_QRY_REQ_STRU  *pstMtaLrrcMonCellReq = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    pstMtaLrrcMonCellReq  = (MTA_LRRC_NETMON_CELL_QRY_REQ_STRU*)TAF_MTA_ALLOC_MSG_WITH_HDR(sizeof(MTA_LRRC_NETMON_CELL_QRY_REQ_STRU));
    if (VOS_NULL_PTR == pstMtaLrrcMonCellReq)
    {
        MTA_ERROR_LOG("TAF_MTA_SndLrrcSetNetMonCellReq: Alloc msg fail!");
        return ;
    }

    /* �����Ϣ���� */
    TAF_MTA_CLR_MSG_ENTITY(pstMtaLrrcMonCellReq);

    /* ��д��Ϣͷ */
    TAF_MTA_CFG_MSG_HDR(pstMtaLrrcMonCellReq, ulReceiverPid, ulMsgName);

    /* ��д��Ϣ���� */
    pstMtaLrrcMonCellReq->enCelltype        = enCelltype;

    /* ������Ϣ��AS */
    TAF_MTA_SEND_MSG(pstMtaLrrcMonCellReq);

    return ;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvLrrcNetMonCellQryCnf
 ��������  : MTA�յ�LTE ID_LRRC_MTA_NETMON_CELL_QRY_CNF��Ϣ������
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvLrrcNetMonCellQryCnf(
    VOS_VOID                            *pMsg
)
{
    LRRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU       *pstLteNetMonCellInfo = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU                      *pstCmdBuf            = VOS_NULL_PTR;
    VOS_UINT32                                    ulMsgId;
    TAF_MTA_TIMER_ID_ENUM_UINT32                  enTimerId;
    MTA_AT_NETMON_CELL_INFO_STRU                  stMtaAtInd;

    pstLteNetMonCellInfo = (LRRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU *)pMsg;

    PS_MEM_SET(&stMtaAtInd, 0, sizeof(MTA_AT_NETMON_CELL_INFO_STRU));

    if (MTA_NETMON_SCELL_TYPE == pstLteNetMonCellInfo->enCelltype)
    {
        enTimerId = TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF;
        ulMsgId   = ID_MTA_AT_SET_NETMON_SCELL_CNF;
        PS_MEM_CPY(&stMtaAtInd.unSCellInfo.stLteSCellInfo,
                   &pstLteNetMonCellInfo->u.stSCellinfo,
                   sizeof(MTA_NETMON_EUTRAN_SCELL_INFO_STRU));
    }
    else if (MTA_NETMON_NCELL_TYPE == pstLteNetMonCellInfo->enCelltype)
    {
        enTimerId = TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF;
        ulMsgId   = ID_MTA_AT_SET_NETMON_NCELL_CNF;
        PS_MEM_CPY(&stMtaAtInd.stNCellInfo,
                   &pstLteNetMonCellInfo->u.stNCellinfo,
                   sizeof(RRC_MTA_NETMON_NCELL_INFO_STRU));
    }
    else
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcNetMonCellQryCnf: WARNING: Celltype error!");
        return;
    }

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(enTimerId))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcNetMonCellQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(enTimerId);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(enTimerId);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvLrrcNetMonCellQryCnf: get command buffer failed!");
        return;
    }

    /* ��д�����ϱ�����Ϣ���� */
    if (MTA_NETMON_RESULT_NO_ERR == pstLteNetMonCellInfo->enResult)
    {
        stMtaAtInd.enResult = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        stMtaAtInd.enResult = MTA_AT_RESULT_ERROR;
    }

    stMtaAtInd.enRatType  = MTA_AT_NETMON_CELL_INFO_LTE;
    stMtaAtInd.enCellType = pstLteNetMonCellInfo->enCelltype;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ulMsgId,
                     sizeof(stMtaAtInd),
                     (VOS_UINT8*)&stMtaAtInd);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(enTimerId);

    return;

}
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTrrcNetMonCellQryCnf
 ��������  : MTA�յ�TRRC ID_RRC_MTA_NETMON_CELL_QRY_CNF��Ϣ������
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTrrcNetMonCellQryCnf(
    VOS_VOID                           *pMsg
)
{
    RRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU        *pstUtranNetMonCellInfo = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU                      *pstCmdBuf              = VOS_NULL_PTR;
    VOS_UINT32                                    ulMsgId;
    TAF_MTA_TIMER_ID_ENUM_UINT32                  enTimerId;
    MTA_AT_NETMON_CELL_INFO_STRU                  stMtaAtInd;

    pstUtranNetMonCellInfo = (RRC_MTA_NETMON_CELL_INFO_QRY_CNF_STRU *)pMsg;

    PS_MEM_SET(&stMtaAtInd, 0, sizeof(MTA_AT_NETMON_CELL_INFO_STRU));

    if (MTA_NETMON_SCELL_TYPE == pstUtranNetMonCellInfo->enCelltype)
    {
        enTimerId = TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF;
        ulMsgId   = ID_MTA_AT_SET_NETMON_SCELL_CNF;
        PS_MEM_CPY(&stMtaAtInd.unSCellInfo.stUtranSCellInfo,
                   &pstUtranNetMonCellInfo->u.stSCellinfo,
                   sizeof(RRC_MTA_NETMON_UTRAN_SCELL_INFO_STRU));
    }
    else if (MTA_NETMON_NCELL_TYPE == pstUtranNetMonCellInfo->enCelltype)
    {
        enTimerId = TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF;
        ulMsgId   = ID_MTA_AT_SET_NETMON_NCELL_CNF;
        PS_MEM_CPY(&stMtaAtInd.stNCellInfo,
                   &pstUtranNetMonCellInfo->u.stNCellinfo,
                   sizeof(RRC_MTA_NETMON_NCELL_INFO_STRU));
    }
    else
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTrrcNetMonCellQryCnf: WARNING: Celltype error!");
        return;
    }

    /* �ж϶�ʱ���Ƿ����� */
    if (TAF_MTA_TIMER_STATUS_STOP == TAF_MTA_GetTimerStatus(enTimerId))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTrrcNetMonCellQryCnf: WARNING: Timer was already stop!");
        return;
    }

    /* ֹͣ������ʱ�� */
    TAF_MTA_StopTimer(enTimerId);

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(enTimerId);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTrrcNetMonCellQryCnf: get command buffer failed!");
        return;
    }

    /* ��д�����ϱ�����Ϣ���� */
    if (MTA_NETMON_RESULT_NO_ERR == pstUtranNetMonCellInfo->enResult)
    {
        stMtaAtInd.enResult = MTA_AT_RESULT_NO_ERROR;
    }
    else
    {
        stMtaAtInd.enResult = MTA_AT_RESULT_ERROR;
    }
    stMtaAtInd.enRatType  = MTA_AT_NETMON_CELL_INFO_UTRAN_TDD;
    stMtaAtInd.enCellType = pstUtranNetMonCellInfo->enCelltype;

    /* ��at����Ϣ */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ulMsgId,
                     sizeof(stMtaAtInd),
                     (VOS_UINT8*)&stMtaAtInd);

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(enTimerId);

    return;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitGrrNetMonTaQryExpired
 ��������  : ��ѯTA��Ϣ��ʱ����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitGrrNetMonTaQryExpired(
    VOS_VOID                            *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU             *pstCmdBuf         = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU        *pstNetMonCellInfo = VOS_NULL_PTR;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTiWaitGrrNetMonTaQryExpired: get command buffer failed!");
        return;
    }

    /* ��ȡTA������ʱ����Ȼ�ϱ��������� */
    if (MTA_AT_NETMON_GSM_STATTE_WAIT_TA == TAF_MTA_GetNetmonGsmState())
    {
        TAF_MTA_SetNetmonGsmState(MTA_AT_NETMON_GSM_STATE_INIT);

        pstNetMonCellInfo = TAF_MTA_GetNetmonCellInfo();

        pstNetMonCellInfo->unSCellInfo.stGsmSCellInfo.bitOpTa = PS_IE_NOT_PRESENT;
        pstNetMonCellInfo->unSCellInfo.stGsmSCellInfo.usTa    = 0xFFFF;

        TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                           ID_MTA_AT_SET_NETMON_SCELL_CNF,
                           sizeof(MTA_AT_NETMON_CELL_INFO_STRU),
                           (VOS_UINT8*)pstNetMonCellInfo);
    }

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_GAS_NETMON_TA_QRY_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitRrcNetMonSCellQryExpired
 ��������  : MONSC��ѯ����С����Ϣ��ʱ�Ĵ�����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitRrcNetMonSCellQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf           = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU        stQryNetmonCellInfo;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    PS_MEM_SET(&stQryNetmonCellInfo, 0x0, sizeof(MTA_AT_NETMON_CELL_INFO_STRU));

    stQryNetmonCellInfo.enResult = MTA_AT_RESULT_ERROR;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_SET_NETMON_SCELL_CNF,
                     sizeof(stQryNetmonCellInfo),
                     (VOS_UINT8*)&stQryNetmonCellInfo );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_RRC_NETMON_SCELL_QRY_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitRrcNetMonNCellQryExpired
 ��������  : MONNC��ѯ������Ϣ��ʱ�Ĵ�����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2015��10��19��
    ��    ��   : zwx247453
    �޸�����   : ��������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitRrcNetMonNCellQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU            *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_NETMON_CELL_INFO_STRU        stQryNetmonCellInfo;

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    PS_MEM_SET(&stQryNetmonCellInfo, 0x0, sizeof(MTA_AT_NETMON_CELL_INFO_STRU));

    stQryNetmonCellInfo.enResult = MTA_AT_RESULT_ERROR;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_SET_NETMON_NCELL_CNF,
                     sizeof(MTA_AT_NETMON_CELL_INFO_STRU),
                     (VOS_UINT8*)&stQryNetmonCellInfo );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_RRC_NETMON_NCELL_QRY_CNF);

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtQryAfcAndXoInfoReq
 ��������  : ��ѯ�²�ϵ���Ĵ���
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2015��12��24��
    ��    ��   : c00299064
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtQryAfcAndXoInfoReq(
    VOS_VOID                           *pMsg
)
{
    AT_MTA_MSG_STRU                             *pstSetReq = VOS_NULL_PTR;
    MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU      stQryCnf;

    PS_MEM_SET(&stQryCnf, 0, sizeof(MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU));

    pstSetReq = (AT_MTA_MSG_STRU*)pMsg;

    if (TAF_MTA_TIMER_STATUS_RUNING == TAF_MTA_GetTimerStatus(TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_QRY_CNF))
    {
        stQryCnf.enResult   =   MTA_AT_RESULT_ERROR;
        TAF_MTA_SndAtMsg(&pstSetReq->stAppCtrl,
                         ID_MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF,
                         sizeof(MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU),
                         (VOS_UINT8*)&stQryCnf);
        return;
    }

    /* snd rcm the req */
    TAF_MTA_SndRcmAfcClkAndXoCoEfQryReq();

    (VOS_VOID)TAF_MTA_StartTimer(TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_QRY_CNF,
                       TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_TIMER_LEN);

    /* �����Ϣ���ȴ����� */
    TAF_MTA_SaveItemInCmdBufferQueue(TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_QRY_CNF,
                                    (VOS_UINT8*)&pstSetReq->stAppCtrl,
                                     sizeof(AT_APPCTRL_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTiWaitRcmAfcInfoQryExpired
 ��������  : wait rcm afc info cnf��ʱ�Ĵ�����
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2015��12��24��
    ��    ��   : c00299064
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvTiWaitRcmAfcInfoQryExpired(
    VOS_VOID                           *pMsg
)
{
    TAF_MTA_CMD_BUFFER_STRU                     *pstCmdBuf = VOS_NULL_PTR;
    MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU      stQryCnf;

    PS_MEM_SET(&stQryCnf, 0, sizeof(MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU));

    /* ��ȡ��ǰ��ʱ����Ӧ����Ϣ���� */
    pstCmdBuf = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        return;
    }

    stQryCnf.enResult = MTA_AT_RESULT_OPTION_TIMEOUT;

    /* �ϱ���ATģ���ѯ���� */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)pstCmdBuf->pucMsgInfo,
                     ID_MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF,
                     sizeof(MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU),
                     (VOS_UINT8*)&stQryCnf );

    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_QRY_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvRcmAfcInfoCnf
 ��������  : �յ�RCM��ѯ�²�ϵ����CNF�Ĵ���
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2015��12��24��
    ��    ��   : c00299064
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_MTA_RcvRcmAfcInfoCnf(
    VOS_VOID                           *pMsg
)
{
    RCM_MTA_AFC_CLK_INFO_QRY_CNF_STRU          *pstCnf               = VOS_NULL_PTR;
    TAF_MTA_CMD_BUFFER_STRU                    *pstCmdBuf            = VOS_NULL_PTR;
    MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU     stQryCnf;

    PS_MEM_SET(&stQryCnf, 0, sizeof(MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU));

    pstCnf      = (RCM_MTA_AFC_CLK_INFO_QRY_CNF_STRU*)pMsg;

    pstCmdBuf   = TAF_MTA_GetItemFromCmdBufferQueue(TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_QRY_CNF);

    if (VOS_NULL_PTR == pstCmdBuf)
    {
        MTA_ERROR_LOG("TAF_MTA_RcvRcmAfcInfoCnf:get appctrl err");
        return;
    }

    /*  ֹͣ��ʱ�� */
    TAF_MTA_StopTimer(TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_QRY_CNF);

    if (MTA_PHY_RESULT_NO_ERROR != pstCnf->enResult)
    {
        stQryCnf.enResult = MTA_AT_RESULT_ERROR;
    }
    else
    {
        stQryCnf.enResult               =  MTA_AT_RESULT_NO_ERROR;

        stQryCnf.enStatus               =  TAF_MTA_GetAfcClkStatus(pstCnf->enStatus);
        stQryCnf.lDeviation             =  pstCnf->lDeviation;
        stQryCnf.sCoeffStartTemp        =  pstCnf->sCoeffStartTemp;
        stQryCnf.sCoeffEndTemp          =  pstCnf->sCoeffEndTemp;

        PS_MEM_CPY(stQryCnf.aulCoeffMantissa,
                   pstCnf->aulCoeffMantissa,
                   sizeof(stQryCnf.aulCoeffMantissa));

        PS_MEM_CPY(stQryCnf.ausCoeffExponent,
                   pstCnf->ausCoeffExponent,
                   sizeof(stQryCnf.ausCoeffExponent));
    }

    /* ���ͻظ� */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU*)pstCmdBuf->pucMsgInfo,
                 ID_MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF,
                 sizeof(MTA_AT_QRY_AFC_CLK_FREQ_XOCOEF_CNF_STRU),
                 (VOS_UINT8*)&stQryCnf);


    /* �ӵȴ�������ɾ����Ϣ */
    TAF_MTA_DelItemInCmdBufferQueue(TI_TAF_MTA_WAIT_RCM_AFC_CLK_INFO_QRY_CNF);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetAfcClkStatus
 ��������  : �յ�RCM��ѯ�²�ϵ����CNF��AFC CLK STATUS �Ĵ���
 �������  : PHY_MTA_AFC_CLK_STATUS_ENUM_UINT16  enStatus
 �������  : ��
 �� �� ֵ  : AT_MTA_AFC_CLK_STATUS_ENUM_UINT32
 ���ú���  :
 ��������  :
 �޸���ʷ  :
  1.��    ��   : 2015��12��24��
    ��    ��   : c00299064
    �޸�����   : ��������
*****************************************************************************/
AT_MTA_AFC_CLK_STATUS_ENUM_UINT32 TAF_MTA_GetAfcClkStatus(PHY_MTA_AFC_CLK_STATUS_ENUM_UINT16  enStatus)
{
    AT_MTA_AFC_CLK_STATUS_ENUM_UINT32   enAfcClkStatus;

    /* ԭ��ֵ��ת�� */
    switch (enStatus)
    {
        case PHY_MTA_AFC_CLK_UNLOCKED:

            enAfcClkStatus = AT_MTA_AFC_CLK_UNLOCKED;
            break;

        case PHY_MTA_AFC_CLK_LOCKED:

            enAfcClkStatus = AT_MTA_AFC_CLK_LOCKED;
            break;

        default:

            enAfcClkStatus = AT_MTA_AFC_CLK_STATUS_BUTT;
            break;
    }

    return enAfcClkStatus;

}




#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

