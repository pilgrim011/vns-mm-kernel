/******************************************************************************

                  ��Ȩ���� (C), 2001-2013, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MtcPsTransfer.c
  �� �� ��   : ����
  ��    ��   : l00198894
  ��������   : 2013��10��21��
  ����޸�   :
  ��������   : ����PS���л���ع���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��10��21��
    ��    ��   : l00198894
    �޸�����   : �����ļ�

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MtcDebug.h"
#include "MtcComm.h"
#include "MtcPsTransfer.h"

#include "MtcGmmInterface.h"

#include "UsimPsInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*lint -e767 �޸���: l00198894; */
#define    THIS_FILE_ID        PS_FILE_ID_MTC_PS_TRANSFER_C
/*lint +e767 �޸���: l00198894; */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : MTC_SndModem0MtaPsTransferInd
 ��������  : ֪ͨModem0 MTAģ���ϱ�^PSTRANSFER����
 �������  : enPsTransferCause    -- PS���л�ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��21��
    ��    ��   : l00198894
    �޸�����   : V9R1C50 SVLTE������ѡ��Ŀ����
*****************************************************************************/
VOS_VOID MTC_SndModem0MtaPsTransferInd(
    MTC_PS_TRANSFER_CAUSE_ENUM_UINT8    enPsTransferCause
)
{
    VOS_UINT16                          ulLenth;
    MTC_MTA_PS_TRANSFER_IND_STRU       *pstPsTransferInd = VOS_NULL_PTR;

    /* Added by Y00213812 for ����������ѡ, 2014-04-10, begin */
    MTC_PS_TRANSFER_CTX_STRU           *pstPsTransferCtx = VOS_NULL_PTR;

    pstPsTransferCtx                    = MTC_GetPsTransferCtxAddr();
    pstPsTransferCtx->enReportCause     = enPsTransferCause;
    /* Added by Y00213812 for ����������ѡ, 2014-04-10, end */

    ulLenth = sizeof(MTC_MTA_PS_TRANSFER_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ�ռ� */
    pstPsTransferInd = (MTC_MTA_PS_TRANSFER_IND_STRU*)PS_ALLOC_MSG(UEPS_PID_MTC, ulLenth);

    if (VOS_NULL_PTR == pstPsTransferInd)
    {
        MTC_ERROR_LOG("MTC_SndModem0MtaPsTransferInd: Alloc msg fail!");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstPsTransferInd + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* �����Ϣ */
    pstPsTransferInd->stMsgHeader.ulReceiverPid = I0_UEPS_PID_MTA;
    pstPsTransferInd->stMsgHeader.ulMsgName     = ID_MTC_MTA_PS_TRANSFER_IND;
    pstPsTransferInd->ucCause                   = enPsTransferCause;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstPsTransferInd))
    {
        MTC_ERROR1_LOG("MTC_SndModem0MtaPsTransferInd: Snd Msg err. Rec Pid ", I0_UEPS_PID_MTA);
        return;
    }

    /* ��ά�ɲ�: ��¼�ϱ�PS��Ǩ��ָʾ���� */
    MTC_DEBUG_SndPsTransferInd(enPsTransferCause);

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_SndModem0GmmRrcAreaLostInd
 ��������  : ֪ͨModem0 gmm rrc�ٶ���ָʾ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��8��
    ��    ��   : z00161729
    �޸�����   : SVLTE�Ż�G-TL ps�л������޸�
*****************************************************************************/
VOS_VOID MTC_SndModem0GmmRrcAreaLostInd(VOS_VOID)
{
    VOS_UINT16                          ulLenth;
    MTC_GMM_RRC_AREA_LOST_IND_STRU     *pstAreaLostInd = VOS_NULL_PTR;

    ulLenth = sizeof(MTC_GMM_RRC_AREA_LOST_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ�ռ� */
    pstAreaLostInd = (MTC_GMM_RRC_AREA_LOST_IND_STRU*)PS_ALLOC_MSG(UEPS_PID_MTC, ulLenth);

    if (VOS_NULL_PTR == pstAreaLostInd)
    {
        MTC_ERROR_LOG("MTC_SndModem0GmmRrcAreaLostInd: Alloc msg fail!");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstAreaLostInd + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* �����Ϣ */
    pstAreaLostInd->stMsgHeader.ulReceiverPid   = I0_WUEPS_PID_GMM;
    pstAreaLostInd->stMsgHeader.ulMsgName       = ID_MTC_GMM_RRC_AREA_LOST_IND;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstAreaLostInd))
    {
        MTC_ERROR1_LOG("MTC_SndModem0GmmRrcAreaLostInd: Snd Msg err. Rec Pid ", I0_UEPS_PID_MTA);
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_SndModem0MmaPsTransferInd
 ��������  : ֪ͨModem0��mma ps transfer��Ϣ
 �������  : enPsTransferCause - MTCģ��PS���л�ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��11��25��
    ��    ��   : z00161729
    �޸�����   : SVLTE�Ż�G-TL ps�л������޸�
  2.��    ��   : 2014��01��17��
    ��    ��   : l00198894
    �޸�����   : V9R1C53 C+L ������ѡ��Ŀ
*****************************************************************************/
VOS_VOID MTC_SndModem0MmaPsTransferInd(
    MTC_PS_TRANSFER_CAUSE_ENUM_UINT8    enPsTransferCause
)
{
    VOS_UINT16                          ulLenth;
    MTC_MMA_PS_TRANSFER_IND_STRU       *pstPsTransferInd = VOS_NULL_PTR;

    ulLenth = sizeof(MTC_MMA_PS_TRANSFER_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ������Ϣ�ռ� */
    pstPsTransferInd = (MTC_MMA_PS_TRANSFER_IND_STRU*)PS_ALLOC_MSG(UEPS_PID_MTC, ulLenth);

    if (VOS_NULL_PTR == pstPsTransferInd)
    {
        MTC_ERROR_LOG("MTC_SndMmaPsTransferInd: Alloc msg fail!");
        return;
    }

    /* ����Ϣ�ռ� */
    PS_MEM_SET((VOS_UINT8*)pstPsTransferInd + VOS_MSG_HEAD_LENGTH, 0, ulLenth);

    /* �����Ϣ */
    pstPsTransferInd->stMsgHeader.ulReceiverPid     = I0_WUEPS_PID_MMA;
    pstPsTransferInd->stMsgHeader.ulMsgName         = ID_MTC_MMA_PS_TRANSFER_IND;
    pstPsTransferInd->enSolutionCfg                 = MTC_GetPsTransferCfg();
    pstPsTransferInd->ucCause                       = enPsTransferCause;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstPsTransferInd))
    {
        MTC_ERROR1_LOG("MTC_SndMmaPsTransferInd: Snd Msg err. Rec Pid ", I0_WUEPS_PID_MMA);
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_RcvRrcAreaLostInd
 ��������  : �յ�������ϱ�������Ϣ
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��21��
    ��    ��   : l00198894
    �޸�����   : V9R1C50 SVLTE������ѡ��Ŀ����
  2.��    ��   : 2013��11��22��
    ��    ��   : z00161729
    �޸�����   : SVLTE�Ż�G-TL ps�л������޸�
  3.��    ��   : 2014��01��17��
    ��    ��   : l00198894
    �޸�����   : V9R1C53 C+L ������ѡ��Ŀ
  4.��    ��   : 2014��1��23��
    ��    ��   : z00161729
    �޸�����   : DTS2014012305088:svlte���Կ�������Ч����mtc�����ϱ�pstransfer:0
  5.��    ��   : 2014��4��09��
    ��    ��   : Y00213812
    �޸�����   : ����������ѡ����Ҫ��¼�Ƿ��ϱ���pstransfer:0
*****************************************************************************/
VOS_VOID MTC_RcvRrcAreaLostInd(VOS_VOID * pMsg)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    RRC_MTC_AREA_LOST_IND_STRU         *pstAreaLostInd = VOS_NULL_PTR;
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enModem1PowerState;
    MTC_OPERATOR_CUST_SOLUTION_ENUM_UINT8   enOperatorCustSolution;
    VOS_BOOL                            enTestCardFlg;

    /* Added by Y00213812 for ����������ѡ, 2014-04-10, begin */
    MTC_PS_TRANSFER_CTX_STRU           *pstPsTransferCtx    = VOS_NULL_PTR;
    pstPsTransferCtx                    = MTC_GetPsTransferCtxAddr();
    /* Added by Y00213812 for ����������ѡ, 2014-04-10, end */

    /* GCF����ʱ����Ҫ����PSTRANSFER���̣�������GCF���Բ���ͨ�� */
    enTestCardFlg = USIMM_IsTestCard();
    if (VOS_TRUE == enTestCardFlg)
    {
        return;
    }

    pstAreaLostInd      = (RRC_MTC_AREA_LOST_IND_STRU*)pMsg;
    enModemId           = VOS_GetModemIDFromPid(pstAreaLostInd->stMsgHeader.ulSenderPid);

    /* ������Modem0���͵Ķ���ָʾ */
    if (enModemId != MODEM_ID_0)
    {
        MTC_ERROR1_LOG("MTC_RcvRrcAreaLostInd: Err ModemId ", enModemId);
        return;
    }

    /* δ����PS��Ǩ�Ʋ��ԣ�ֻ��¼���� */
    if (MTC_PS_TRANSFER_NONE == MTC_GetPsTransferCfg())
    {
        /* ��ά�ɲ�: ��¼���յ�����ָʾ�Ĵ��� */
        MTC_DEBUG_RcvRrcAreaLostInd(pstAreaLostInd->stMsgHeader.ulSenderPid);
        return;
    }

    /* ��Ӫ�̶��Ʒ���SVLTE��C+Lʱ��Ҫ�ϱ�AT����ָʾ */
    enOperatorCustSolution  = MTC_GetOperatorCustSolution();
    enModem1PowerState      = MTC_GetModemPowerState(MODEM_ID_1);

    /* ���������ҵ��̬��idle̬������Modem1�����ҿ���Чʱ���ϱ�PS��Ǩ��ָʾ */
    if ((VOS_TRUE == MTC_GetModemUsimValidFlag(enModemId))
     && (((MTC_OPERATOR_CUST_CMCC_SVLTE == enOperatorCustSolution)
       && (MTC_MODEM_POWER_ON == enModem1PowerState))
      || (MTC_OPERATOR_CUST_CT_LC == enOperatorCustSolution) ))
    {
        /* Modified by Y00213812 for ����������ѡ, 2014-04-10, begin */
        if (MTC_PS_TRANSFER_CAUSE_AREA_LOST != pstPsTransferCtx->enReportCause)
        {
            MTC_SndModem0MtaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_LOST);

            /* ֪ͨmodem0 gmm������gmm��¼ȫ�ֱ�������detachֻ��һ�μ���detachʱ�� */
            MTC_SndModem0GmmRrcAreaLostInd();
        }
        /* Modified by Y00213812 for ����������ѡ, 2014-04-10, end */
    }

    /* Added by Y00213812 for ����������ѡ, 2014-04-10, begin */
    pstPsTransferCtx->enRrcCause = MTC_PS_TRANSFER_CAUSE_AREA_LOST;
    /* Added by Y00213812 for ����������ѡ, 2014-04-10, end */

    /* ��ά�ɲ�: ��¼���յ�����ָʾ�Ĵ��� */
    MTC_DEBUG_RcvRrcAreaLostInd(pstAreaLostInd->stMsgHeader.ulSenderPid);

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_RcvRrcAreaAvaliableInd
 ��������  : �յ�������ϱ�����ָ���Ϣ
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��01��17��
    ��    ��   : l00198894
    �޸�����   : V9R1C53 C+L ������ѡ��Ŀ

  2.��    ��   : 2014��4��09��
    ��    ��   : Y00213812
    �޸�����   : ����������ѡ����Ҫ��¼��ģ�Ƿ�Avaliable

  3.��    ��   : 2014��5��29��
    ��    ��   : x00203213
    �޸�����   : ����NCELL����RAT ˳����ģ���פ��LTE ��ʱ��NCELL ����������TDS����ֹLTE���ź�ʼ��û�л�������TDS��
                              Ϊ��֤������ʱ�����㹻��ʱ��������פ����ʱ�򲻷���Ϣ��mmaͣ������ʱ��
*****************************************************************************/
VOS_VOID MTC_RcvRrcAreaAvaliableInd(VOS_VOID * pMsg)
{
    MODEM_ID_ENUM_UINT16                enModemId;
    RRC_MTC_AREA_AVALIABLE_IND_STRU    *pstAreaAvaliableInd = VOS_NULL_PTR;
    MTC_MODEM_NETWORK_INFO_STRU        *pstNetworkInfo      = VOS_NULL_PTR;

    /* Added by Y00213812 for ����������ѡ, 2014-04-10, begin */
    VOS_UINT8                           ucUsimValidFlag;
    MTC_PS_TRANSFER_CTX_STRU           *pstPsTransferCtx    = VOS_NULL_PTR;

    pstPsTransferCtx    = MTC_GetPsTransferCtxAddr();
    ucUsimValidFlag     = MTC_GetModemUsimValidFlag(MODEM_ID_0);
    /* Added by Y00213812 for ����������ѡ, 2014-04-10, end */

    pstAreaAvaliableInd = (RRC_MTC_AREA_AVALIABLE_IND_STRU*)pMsg;
    enModemId           = VOS_GetModemIDFromPid(pstAreaAvaliableInd->stMsgHeader.ulSenderPid);

    /* ������Modem0���͵�����ָ�ָʾ */
    if (enModemId != MODEM_ID_0)
    {
        MTC_ERROR1_LOG("MTC_RcvRrcAreaAvaliableInd: Err ModemId ", enModemId);
        return;
    }

    /* PS��������ѡ���Կ���ʱ */
    if (MTC_PS_TRANSFER_OFF_AREA == MTC_GetPsTransferCfg())
    {
        pstNetworkInfo = MTC_GetModemNetworkInfoAddr(enModemId);

        /* Modified by Y00213812 for ����������ѡ, 2014-04-10, begin */
        /* ��ǰפ������ǽ�ֹPLMN���ǽ�ֹGPRS���롢��״̬��Ч�����ظ��ϱ� */
        if ( (VOS_FALSE == pstNetworkInfo->ucIsForbiddenPlmnFlag)
          && (VOS_TRUE == pstNetworkInfo->stPsDomainInfo.ucPsSupportFlg)
          && (VOS_TRUE == ucUsimValidFlag)
          && (MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE != pstPsTransferCtx->enReportCause))
        {
            /* �ϱ�PS��Ǩ������ָ�ָʾAT���� */
            MTC_SndModem0MtaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
        }

        pstPsTransferCtx->enRrcCause = MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE;
        /* Modified by Y00213812 for ����������ѡ, 2014-04-10, end */

        MTC_SndModem0MmaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
 
    }

    /* ��ά�ɲ�: ��¼���յ�����ָʾ�Ĵ��� */
    MTC_DEBUG_RcvRrcAreaAvaliableInd();

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_ProcCurrCampPlmnInfoForSvlte
 ��������  : SVLTE����Modem0����ָ�ʱPS��Ǩ�����̴���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��01��17��
    ��    ��   : l00198894
    �޸�����   : V9R1C53 C+L ������ѡ��Ŀ
  2.��    ��   : 2014��1��23��
    ��    ��   : z00161729
    �޸�����   : DTS2014012305088:svlte���Կ�������Ч����mtc�����ϱ�pstransfer:0��1
  3.��    ��   : 2014��4��09��
    ��    ��   : Y00213812
    �޸�����   : ����������ѡ:��ģע��ɹ����ϱ�pstransfer:1

    4.��    ��   : 2014��5��29��
    ��    ��   : x00203213
    �޸�����   : ����NCELL����RAT ˳����ģ���פ��LTE ��ʱ��NCELL ����������TDS����ֹLTE���ź�ʼ��û�л�������TDS��
                              Ϊ��֤������ʱ�����㹻��ʱ��������פ����ʱ�򲻷���Ϣ��mmaͣ������ʱ��
*****************************************************************************/
VOS_VOID MTC_ProcCurrCampPlmnInfoForSvlte(VOS_VOID)
{
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enModem1PowerState;
    MTC_MODEM_NETWORK_INFO_STRU        *pstModem0NetworkInfo = VOS_NULL_PTR;
    MTC_PS_TRANSFER_ENUM_UINT8          enPsTransferSolution;
    MTC_RATMODE_ENUM_UINT8              enModem0RateMode;

    VOS_UINT8                           ucUsimValidFlag;

    /* Added by Y00213812 for ����������ѡ, 2014-04-10, begin */
    MTC_PS_TRANSFER_CTX_STRU           *pstPsTransferCtx    = VOS_NULL_PTR;
    pstPsTransferCtx                    = MTC_GetPsTransferCtxAddr();
    /* Added by Y00213812 for ����������ѡ, 2014-04-10, end */

    enModem1PowerState      = MTC_GetModemPowerState(MODEM_ID_1);
    pstModem0NetworkInfo    = MTC_GetModemNetworkInfoAddr(MODEM_ID_0);
    enPsTransferSolution    = MTC_GetPsTransferCfg();
    enModem0RateMode        = MTC_GetModemRatMode(MODEM_ID_0);



    /* Modem1�ػ�������ģʽ����PS��Ǩ�� */
    if (MTC_MODEM_POWER_OFF == enModem1PowerState)
    {
        return;
    }

    ucUsimValidFlag = MTC_GetModemUsimValidFlag(MODEM_ID_0);

    /* 1��modem1���ڿ���״̬
       2����ǰפ��������뼼��ΪT/L(OscarTLͨ��������G��ѡ��T/L)
       3����ǰפ������ǽ�ֹplmn
       4������ģʽmodem0��ps��detach״̬���ϱ�PS��Ǩ��ָʾ */
    if ( ( (MTC_RATMODE_LTE == enModem0RateMode)
        || (MTC_RATMODE_TDS == enModem0RateMode) )
      && (VOS_FALSE == pstModem0NetworkInfo->ucIsForbiddenPlmnFlag)
      && (VOS_TRUE == ucUsimValidFlag)
      && (VOS_FALSE == pstModem0NetworkInfo->stPsDomainInfo.ucPsAttachAllowFlg)
      && (VOS_TRUE == pstModem0NetworkInfo->stPsDomainInfo.ucPsSupportFlg) )
    {
        /* PS��Ǩ�Ʋ���������ѡ���ϱ�����ָ�ָʾAT���� */
        if (MTC_PS_TRANSFER_LOST_AREA == enPsTransferSolution)
        {
            MTC_SndModem0MtaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
            MTC_SndModem0MmaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
        }

        /* Added by Y00213812 for ����������ѡ, 2014-04-10, begin */
        /* PS��Ǩ�Ʋ���������ѡ���ϱ�����ָ�ָʾAT���� */
        if ((MTC_PS_TRANSFER_OFF_AREA == enPsTransferSolution)
         && (MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE == pstPsTransferCtx->enRrcCause))
        {
            MTC_SndModem0MtaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
            MTC_SndModem0MmaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
        }
        /* Added by Y00213812 for ����������ѡ, 2014-04-10, end */
        //MTC_SndModem0MmaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);

    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_ProcCurrCampPlmnInfoForLC
 ��������  : C+L����Modem0����ָ�ʱPS��Ǩ�����̴���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��01��17��
    ��    ��   : l00198894
    �޸�����   : V9R1C53 C+L ������ѡ��Ŀ
  2.��    ��   : 2014��4��09��
    ��    ��   : Y00213812
    �޸�����   : ����������ѡ:��ģע��ɹ����ϱ�pstransfer:1
*****************************************************************************/
VOS_VOID MTC_ProcCurrCampPlmnInfoForLC(VOS_VOID)
{
    MTC_MODEM_NETWORK_INFO_STRU        *pstModem0NetworkInfo = VOS_NULL_PTR;
    MTC_PS_TRANSFER_ENUM_UINT8          enPsTransferSolution;
    MTC_RATMODE_ENUM_UINT8              enModem0RateMode;

    /* Added by Y00213812 for ����������ѡ, 2014-04-10, begin */
    MTC_PS_TRANSFER_CTX_STRU           *pstPsTransferCtx    = VOS_NULL_PTR;
    pstPsTransferCtx                    = MTC_GetPsTransferCtxAddr();
    /* Added by Y00213812 for ����������ѡ, 2014-04-10, end */


    pstModem0NetworkInfo    = MTC_GetModemNetworkInfoAddr(MODEM_ID_0);
    enPsTransferSolution    = MTC_GetPsTransferCfg();
    enModem0RateMode        = MTC_GetModemRatMode(MODEM_ID_0);

    /* 1����ǰפ������ǽ�ֹplmn
        2������ģʽmodem0��ps��detach״̬���ϱ�PS��Ǩ��ָʾ */
    if ( (MTC_RATMODE_LTE == enModem0RateMode)
      && (VOS_FALSE == pstModem0NetworkInfo->ucIsForbiddenPlmnFlag)
      && (VOS_FALSE == pstModem0NetworkInfo->stPsDomainInfo.ucPsAttachAllowFlg))
    {
        /* PS��Ǩ�Ʋ���������ѡ���ϱ�����ָ�ָʾAT���� */
        if (MTC_PS_TRANSFER_LOST_AREA == enPsTransferSolution)
        {
            MTC_SndModem0MtaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
        }

        /* Added by Y00213812 for ����������ѡ, 2014-04-10, begin */
        /* PS��Ǩ�Ʋ���������ѡ���ϱ�����ָ�ָʾAT���� */
        if ((MTC_PS_TRANSFER_OFF_AREA == enPsTransferSolution)
         && (MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE == pstPsTransferCtx->enRrcCause))
        {
            MTC_SndModem0MtaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
        }
        /* Added by Y00213812 for ����������ѡ, 2014-04-10, end */

        MTC_SndModem0MmaPsTransferInd(MTC_PS_TRANSFER_CAUSE_AREA_AVALIABLE);
    }

    return;
}

/* Added by Y00213812 for ����������ѡ, 2014-04-10, begin */
/*****************************************************************************
 �� �� ��  : MTC_RcvGsmCellInfoInd
 ��������  : ���յ�ID_MTC_RRC_GSM_CELL_INFO_IND�ϱ�Ƶ����ź�ǿ����Ϣ�Ĵ���
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��04��08��
    ��    ��   : Y00213812
    �޸�����   : RF&LCD���Ź����Ŀ����
*****************************************************************************/
VOS_VOID MTC_RcvGsmCellInfoInd(VOS_VOID *pMsg)
{
    RRC_MTC_GSM_CELL_INFO_IND_STRU     *pstGsmInfoInd  = VOS_NULL_PTR;
    MTC_RRC_GSM_CELL_INFO_IND_STRU     *pstGsmCellInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulReceiverPid;

    /* �����ǰ�Ѿ��ػ�����ֹͣ������Ϣ */
    if (MTC_MODEM_POWER_OFF == MTC_GetModemPowerState(MODEM_ID_0))
    {
        return;
    }

    /* �жϵ�ǰ��ģ״̬, ΪTDS/LTEʱ���� */
    if (MTC_RATMODE_TDS == MTC_GetModemRatMode(MODEM_ID_0))
    {
        ulReceiverPid = TPS_PID_RRC;
    }
    else if (MTC_RATMODE_LTE== MTC_GetModemRatMode(MODEM_ID_0))
    {
        ulReceiverPid = PS_PID_ERRC;
    }
    else
    {
        return;
    }

    /* ������Ϣ�ռ� */
    pstGsmCellInfo  = (MTC_RRC_GSM_CELL_INFO_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                UEPS_PID_MTC,
                                                                sizeof(MTC_RRC_GSM_CELL_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstGsmCellInfo)
    {
        MTC_ERROR_LOG("MTC_RcvGsmCellInfoInd: Alloc Msg Fail!");
        return;
    }

    pstGsmCellInfo->stMsgHeader.ulReceiverPid = ulReceiverPid;
    pstGsmCellInfo->stMsgHeader.ulMsgName     = ID_MTC_RRC_GSM_CELL_INFO_IND;

    pstGsmInfoInd                             = (RRC_MTC_GSM_CELL_INFO_IND_STRU *)pMsg;
    PS_MEM_CPY(&pstGsmCellInfo->stGsmCellInfo,
               &pstGsmInfoInd->stGsmCellInfo,
               sizeof(RRC_MTC_GSM_CELL_INFO_STRU));

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTC, pstGsmCellInfo))
    {
        MTC_ERROR_LOG("MTC_RcvGsmCellInfoInd: Snd Msg Err!");
    }

    return;

}
/* Added by Y00213812 for ����������ѡ, 2014-04-10, end */

/*lint +e958*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* end of MtcPsTransfer.c */


