/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdSndCas.c
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��7��7��
  ����޸�   :
  ��������   : HSD���͸�CAS����Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "PsCommonDef.h"
#include  "CnasHsdSndCas.h"
#include  "CnasMntn.h"
#include  "CnasCcb.h"
#include  "CnasHsdCtx.h"
#include  "cas_hrpd_airlinkmgmt_nas_pif.h"
#include  "CnasHsdSysAcqStrategy.h"
#include  "hsd_mscc_pif.h"
#include  "NasMntn.h"
#include  "cas_hrpd_routeupdate_nas_pif.h"
#include  "CnasHsdAvoidStrategy.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_SND_CAS_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasStartReq
 ��������  : ��CAS���Ϳ�������
 �������  : pstMsg - �������뼼��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��4��15��
    ��    ��   : y00245242
    �޸�����   : iteration 13����

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasStartReq(MSCC_HSD_START_REQ_STRU *pstMsg)
{
    CNAS_CAS_HRPD_START_REQ_STRU       *pstStartrReq;
    VOS_UINT32                          i;

    /* ������Ϣ */
    pstStartrReq = (CNAS_CAS_HRPD_START_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,  sizeof(CNAS_CAS_HRPD_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstStartrReq)
    {
        return;
    }

    /* �����Ϣ */
    pstStartrReq->ulReceiverPid         = UEPS_PID_HALMP;
    pstStartrReq->enMsgId               = ID_CNAS_CAS_HRPD_START_REQ;
    pstStartrReq->usOpId                = 0;
    pstStartrReq->enModemId             = pstMsg->enModemId;
    pstStartrReq->ucSuppRatNum          = pstMsg->ucSuppRatNum;

    for (i = 0; i < (sizeof(pstStartrReq->aenRatMode)/sizeof(pstStartrReq->aenRatMode[0])); i++)
    {
        pstStartrReq->aenRatMode[i] = VOS_RATMODE_BUTT;
    }

    for (i = 0; i < pstStartrReq->ucSuppRatNum; i++)
    {
        pstStartrReq->aenRatMode[i] = pstMsg->aenRatMode[i];
    }

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstStartrReq);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstStartrReq);

    NAS_TRACE_HIGH("Send Msg!");

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasPowerOffReq
 ��������  : ��CAS���͹ػ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasPowerOffReq(VOS_VOID)
{
    CNAS_CAS_HRPD_POWER_OFF_REQ_STRU     *pstPowerOffReq;

    /* ������Ϣ */
    pstPowerOffReq = (CNAS_CAS_HRPD_POWER_OFF_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD, sizeof(CNAS_CAS_HRPD_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstPowerOffReq)
    {
        return;
    }

    /* �����Ϣ */
    pstPowerOffReq->ulReceiverPid       = UEPS_PID_HALMP;
    pstPowerOffReq->enMsgId             = ID_CNAS_CAS_HRPD_POWER_OFF_REQ;
    pstPowerOffReq->usOpId              = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstPowerOffReq);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstPowerOffReq);

    NAS_TRACE_HIGH("Send Msg!");

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasSysSyncReq
 ��������  : ��CAS����ID_CNAS_CAS_HSD_SYSTEM_SYNC_REQ��Ϣ
 �������  : ulFreqNum   : �·�����Ƶ�����
             pstFreqList : �·�����Ƶ���ַ

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��1��19��
    ��    ��   : d00212987
    �޸�����   : ����ÿ���·�����Ƶ�����

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasSysSyncReq(
    VOS_UINT32                          ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreqList
)
{
    CNAS_CAS_HRPD_SYSTEM_SYNC_REQ_STRU *pstSysSyncReq;

    /* ������Ϣ */
    pstSysSyncReq = (CNAS_CAS_HRPD_SYSTEM_SYNC_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,  sizeof(CNAS_CAS_HRPD_SYSTEM_SYNC_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSysSyncReq)
    {
        return;
    }

    /* �����Ϣ */
    pstSysSyncReq->ulReceiverPid   = UEPS_PID_HALMP;
    pstSysSyncReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSysSyncReq->enMsgId         = ID_CNAS_CAS_HRPD_SYSTEM_SYNC_REQ;
    pstSysSyncReq->usOpId          = 0;

    PS_MEM_SET(pstSysSyncReq->astFreqList, 0x00, sizeof(CNAS_CAS_HRPD_FREQENCY_CHANNEL_STRU) * CNAS_CAS_HRPD_MAX_FREQ_NUM);

    PS_MEM_CPY(pstSysSyncReq->astFreqList, pstFreqList, sizeof(CNAS_CAS_HRPD_FREQENCY_CHANNEL_STRU) * ulFreqNum);

    pstSysSyncReq->ulFreqNum = ulFreqNum;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSysSyncReq);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstSysSyncReq);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasStopSysSyncReq
 ��������  : ��CAS����ֹͣHRPD��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasStopSysSyncReq(VOS_VOID)
{
    CNAS_CAS_HRPD_STOP_SYSTEM_SYNC_REQ_STRU                *pstStopSysAcqReq;

    /* ������Ϣ */
    pstStopSysAcqReq = (CNAS_CAS_HRPD_STOP_SYSTEM_SYNC_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD, \
                                                                               sizeof(CNAS_CAS_HRPD_STOP_SYSTEM_SYNC_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstStopSysAcqReq)
    {
        return;
    }

    /* �����Ϣ */
    pstStopSysAcqReq->ulReceiverPid       = UEPS_PID_HALMP;
    pstStopSysAcqReq->enMsgId             = ID_CNAS_CAS_HRPD_STOP_SYSTEM_SYNC_REQ;
    pstStopSysAcqReq->usOpId              = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstStopSysAcqReq);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstStopSysAcqReq);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasOocNtf
 ��������  : ��CAS����ID_CNAS_CAS_HRPD_OOC_NTF��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasOocNtf(VOS_VOID)
{
    CNAS_CAS_HRPD_OOC_NTF_STRU          *pstOocNtf;

    /* ������Ϣ */
    pstOocNtf = (CNAS_CAS_HRPD_OOC_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD, sizeof(CNAS_CAS_HRPD_OOC_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstOocNtf)
    {
        return;
    }

    pstOocNtf->ulReceiverPid       = UEPS_PID_HALMP;
    pstOocNtf->enMsgId             = ID_CNAS_CAS_HRPD_OOC_NTF;
    pstOocNtf->usOpId              = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstOocNtf);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstOocNtf);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasPilotSearchSuccNtf
 ��������  : ��CAS����ID_CNAS_CAS_HRPD_PILOT_SEARCH_SUCC_NTF��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��15��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasPilotSearchSuccNtf(VOS_VOID)
{
    CNAS_CAS_HRPD_PILOT_SEARCH_SUCC_NTF_STRU               *pstPilotSearchSuccNft;

    /* ������Ϣ */
    pstPilotSearchSuccNft = (CNAS_CAS_HRPD_PILOT_SEARCH_SUCC_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,
                                                sizeof(CNAS_CAS_HRPD_PILOT_SEARCH_SUCC_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstPilotSearchSuccNft)
    {
        return;
    }

    pstPilotSearchSuccNft->ulReceiverPid       = UEPS_PID_HALMP;
    pstPilotSearchSuccNft->enMsgId             = ID_CNAS_CAS_HRPD_PILOT_SEARCH_SUCC_NTF;
    pstPilotSearchSuccNft->usOpId              = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstPilotSearchSuccNft);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstPilotSearchSuccNft);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasPilotSearchFailNtf
 ��������  : ��CAS����ID_CNAS_CAS_HRPD_PILOT_SEARCH_FAIL_NTF��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��15��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasPilotSearchFailNtf(VOS_VOID)
{
    CNAS_CAS_HRPD_PILOT_SEARCH_FAIL_NTF_STRU               *pstPilotSearchFailNft;

    /* ������Ϣ */
    pstPilotSearchFailNft = (CNAS_CAS_HRPD_PILOT_SEARCH_FAIL_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,
                                                sizeof(CNAS_CAS_HRPD_PILOT_SEARCH_FAIL_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstPilotSearchFailNft)
    {
        return;
    }

    pstPilotSearchFailNft->ulReceiverPid       = UEPS_PID_HALMP;
    pstPilotSearchFailNft->enMsgId             = ID_CNAS_CAS_HRPD_PILOT_SEARCH_FAIL_NTF;
    pstPilotSearchFailNft->usOpId              = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstPilotSearchFailNft);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstPilotSearchFailNft);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasSysCfgReq
 ��������  : ��CAS����ID_CNAS_CAS_SYS_CFG_SET_REQ��Ϣ
 �������  : pstSysCfg -- ϵͳ����������Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��13��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasSysCfgReq(
    MSCC_HSD_SYS_CFG_REQ_STRU          *pstSysCfg
)
{
    CNAS_CAS_HRPD_SYS_CFG_REQ_STRU     *pstSysCfgReq = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSysCfgReq = (CNAS_CAS_HRPD_SYS_CFG_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,
                                                                  sizeof(CNAS_CAS_HRPD_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSysCfgReq)
    {
        return;
    }

    PS_MEM_SET(pstSysCfgReq, 0, sizeof(CNAS_CAS_HRPD_SYS_CFG_REQ_STRU));

    pstSysCfgReq->ulSenderPid     = UEPS_PID_HSD;
    pstSysCfgReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstSysCfgReq->ulReceiverPid   = UEPS_PID_HALMP;
    pstSysCfgReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSysCfgReq->ulLength        = sizeof(CNAS_CAS_HRPD_SYS_CFG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstSysCfgReq->usOpId          = pstSysCfg->usOpId;
    pstSysCfgReq->enMsgId         = ID_CNAS_CAS_HRPD_SYS_CFG_REQ;

    pstSysCfgReq->stSuppBand.bitOpBC0_A  = pstSysCfg->stCdmaBand.bitOpBC0_A;
    pstSysCfgReq->stSuppBand.bitOpBC0_B  = pstSysCfg->stCdmaBand.bitOpBC0_B;
    pstSysCfgReq->stSuppBand.bitOpBC1    = pstSysCfg->stCdmaBand.bitOpBC1;
    pstSysCfgReq->stSuppBand.bitOpBC2    = pstSysCfg->stCdmaBand.bitOpBC2;
    pstSysCfgReq->stSuppBand.bitOpBC3    = pstSysCfg->stCdmaBand.bitOpBC3;
    pstSysCfgReq->stSuppBand.bitOpBC4    = pstSysCfg->stCdmaBand.bitOpBC4;
    pstSysCfgReq->stSuppBand.bitOpBC5    = pstSysCfg->stCdmaBand.bitOpBC5;
    pstSysCfgReq->stSuppBand.bitOpBC6    = pstSysCfg->stCdmaBand.bitOpBC6;
    pstSysCfgReq->stSuppBand.bitOpBC7    = pstSysCfg->stCdmaBand.bitOpBC7;
    pstSysCfgReq->stSuppBand.bitOpBC8    = pstSysCfg->stCdmaBand.bitOpBC8;
    pstSysCfgReq->stSuppBand.bitOpBC9    = pstSysCfg->stCdmaBand.bitOpBC9;
    pstSysCfgReq->stSuppBand.bitOpBC10   = pstSysCfg->stCdmaBand.bitOpBC10;
    pstSysCfgReq->stSuppBand.bitOpBC11   = pstSysCfg->stCdmaBand.bitOpBC11;
    pstSysCfgReq->stSuppBand.bitOpBC12   = pstSysCfg->stCdmaBand.bitOpBC12;
    pstSysCfgReq->stSuppBand.bitOpBC14   = pstSysCfg->stCdmaBand.bitOpBC14;
    pstSysCfgReq->stSuppBand.bitOpBC15   = pstSysCfg->stCdmaBand.bitOpBC15;

    pstSysCfgReq->ucSuppRatNum    = pstSysCfg->ucSuppRatNum;

    PS_MEM_CPY(&(pstSysCfgReq->aenRatMode[0]),
               &(pstSysCfg->aenRatMode[0]),
               VOS_RATMODE_BUTT * sizeof(VOS_RATMODE_ENUM_UINT32));

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSysCfgReq);


    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstSysCfgReq);
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasSuspendReq
 ��������  : ��CAS����ID_CNAS_CAS_HRPD_SUSPEND_REQ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��04��03��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasSuspendReq(VOS_VOID)
{
    CNAS_CAS_HRPD_SUSPEND_REQ_STRU     *pstSuspendReq;

    /* ������Ϣ */
    pstSuspendReq = (CNAS_CAS_HRPD_SUSPEND_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD, sizeof(CNAS_CAS_HRPD_SUSPEND_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSuspendReq)
    {
        return;
    }

    pstSuspendReq->ulReceiverPid       = UEPS_PID_HALMP;
    pstSuspendReq->enMsgId             = ID_CNAS_CAS_HRPD_SUSPEND_REQ;
    pstSuspendReq->usOpId              = 0;

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstSuspendReq);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasDisableLteNtfReq
 ��������  : ��CAS����ID_CNAS_CAS_HRPD_DISABLE_LTE_NTF��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasDisableLteNtf(VOS_VOID)
{
    CNAS_CAS_HRPD_DISABLE_LTE_NTF_STRU *pstDisableReq;

    /* ������Ϣ */
    pstDisableReq = (CNAS_CAS_HRPD_DISABLE_LTE_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,
                                        sizeof(CNAS_CAS_HRPD_DISABLE_LTE_NTF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstDisableReq)
    {
        return;
    }

    PS_MEM_SET(pstDisableReq, 0, sizeof(CNAS_CAS_HRPD_DISABLE_LTE_NTF_STRU));

    pstDisableReq->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstDisableReq->ulSenderPid         = UEPS_PID_HSD;
    pstDisableReq->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstDisableReq->ulReceiverPid       = UEPS_PID_HALMP;
    pstDisableReq->ulLength            = sizeof(CNAS_CAS_HRPD_DISABLE_LTE_NTF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstDisableReq->enMsgId             = ID_CNAS_CAS_HRPD_DISABLE_LTE_NTF;
    pstDisableReq->usOpId              = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstDisableReq);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstDisableReq);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasBsrLteReq
 ��������  : ��CAS����ID_CNAS_CAS_HRPD_BSR_LTE_REQ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasBsrLteReq(VOS_VOID)
{
    CNAS_CAS_HRPD_BSR_LTE_REQ_STRU *pstBsrLteReq;

    /* ������Ϣ */
    pstBsrLteReq = (CNAS_CAS_HRPD_BSR_LTE_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,
                                        sizeof(CNAS_CAS_HRPD_BSR_LTE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstBsrLteReq)
    {
        return;
    }

    pstBsrLteReq->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstBsrLteReq->ulSenderPid         = UEPS_PID_HSD;
    pstBsrLteReq->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstBsrLteReq->ulReceiverPid       = UEPS_PID_HALMP;
    pstBsrLteReq->ulLength            = sizeof(CNAS_CAS_HRPD_BSR_LTE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBsrLteReq->enMsgId             = ID_CNAS_CAS_HRPD_BSR_LTE_REQ;
    pstBsrLteReq->usOpId              = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstBsrLteReq);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstBsrLteReq);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasStopBsrLteReq
 ��������  : ��CAS����ID_CNAS_CAS_HRPD_STOP_BSR_LTE_REQ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasStopBsrLteReq(VOS_VOID)
{
    CNAS_CAS_HRPD_STOP_BSR_LTE_REQ_STRU                    *pstStopBsrLteReq;

    /* ������Ϣ */
    pstStopBsrLteReq = (CNAS_CAS_HRPD_STOP_BSR_LTE_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,
                                        sizeof(CNAS_CAS_HRPD_STOP_BSR_LTE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstStopBsrLteReq)
    {
        return;
    }

    pstStopBsrLteReq->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstStopBsrLteReq->ulSenderPid         = UEPS_PID_HSD;
    pstStopBsrLteReq->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstStopBsrLteReq->ulReceiverPid       = UEPS_PID_HALMP;
    pstStopBsrLteReq->ulLength            = sizeof(CNAS_CAS_HRPD_STOP_BSR_LTE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstStopBsrLteReq->enMsgId             = ID_CNAS_CAS_HRPD_STOP_BSR_LTE_REQ;
    pstStopBsrLteReq->usOpId              = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstStopBsrLteReq);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstStopBsrLteReq);

    return;
}



/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasFreqListReq
 ��������  : ��CAS����ID_CNAS_CAS_HRPD_BSR_FREQ_LIST_QUERY_CNF��Ϣ
 �������  : ulFreqNum   : �·�����Ƶ�����
             pstFreqList : �·�����Ƶ���ַ

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��16��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasFreqListCnf(
    VOS_UINT32                          ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreqList
)
{
    CNAS_CAS_HRPD_BSR_FREQ_LIST_QUERY_CNF_STRU             *pstFreqListCnf;

    /* ������Ϣ */
    pstFreqListCnf = (CNAS_CAS_HRPD_BSR_FREQ_LIST_QUERY_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,
                                        sizeof(CNAS_CAS_HRPD_BSR_FREQ_LIST_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstFreqListCnf)
    {
        return;
    }

    /* �����Ϣ */
    pstFreqListCnf->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstFreqListCnf->ulSenderPid         = UEPS_PID_HSD;
    pstFreqListCnf->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstFreqListCnf->ulReceiverPid       = UEPS_PID_HALMP;
    pstFreqListCnf->ulLength            = sizeof(CNAS_CAS_HRPD_BSR_FREQ_LIST_QUERY_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstFreqListCnf->enMsgId             = ID_CNAS_CAS_HRPD_BSR_FREQ_LIST_QUERY_CNF;
    pstFreqListCnf->usOpId              = 0;

    PS_MEM_SET(pstFreqListCnf->astFreqList, 0x00, sizeof(CNAS_CAS_HRPD_FREQENCY_CHANNEL_STRU) * CNAS_CAS_HRPD_MAX_FREQ_NUM);

    PS_MEM_CPY(pstFreqListCnf->astFreqList,
               pstFreqList,
               sizeof(CNAS_CAS_HRPD_FREQENCY_CHANNEL_STRU) * ulFreqNum);

    pstFreqListCnf->ulFreqNum = ulFreqNum;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstFreqListCnf);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstFreqListCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasSubnetIdChkCnf
 ��������  : ��CAS����ID_CNAS_CAS_HRPD_SUBNET_ID_CHECK_CNF��Ϣ
 �������  : enValidFlag   : subnetId�Ƿ���Ч

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasSubnetIdChkCnf(
    PS_BOOL_ENUM_UINT8                  enIsValidFlag
)
{
    CNAS_CAS_HRPD_SUBNET_ID_CHECK_CNF_STRU                 *pstChkCnf;

    /* ������Ϣ */
    pstChkCnf = (CNAS_CAS_HRPD_SUBNET_ID_CHECK_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,
                                        sizeof(CNAS_CAS_HRPD_SUBNET_ID_CHECK_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstChkCnf)
    {
        return;
    }

    /* �����Ϣ */
    pstChkCnf->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstChkCnf->ulSenderPid              = UEPS_PID_HSD;
    pstChkCnf->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstChkCnf->ulReceiverPid            = UEPS_PID_HALMP;
    pstChkCnf->ulLength                 = sizeof(CNAS_CAS_HRPD_SUBNET_ID_CHECK_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstChkCnf->enMsgId                  = ID_CNAS_CAS_HRPD_SUBNET_ID_CHECK_CNF;
    pstChkCnf->usOpId                   = 0;
    pstChkCnf->enSubnetIdIsValidFlag    = enIsValidFlag;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstChkCnf);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstChkCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasSuspendRsp
 ��������  : ��CAS����ID_CNAS_CAS_HRPP_RESUME_RSP��Ϣ
 �������  : enValidFlag   : subnetId�Ƿ���Ч

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasSuspendRsp(
    CAS_CNAS_HRPD_RSLT_ENUM_UINT16      enRslt
)
{
    CNAS_CAS_HRPD_SUSPEND_RSP_STRU      *pstSuspendRsp;

    /* ������Ϣ */
    pstSuspendRsp = (CNAS_CAS_HRPD_SUSPEND_RSP_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,
                                        sizeof(CNAS_CAS_HRPD_SUSPEND_RSP_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSuspendRsp)
    {
        return;
    }

    /* �����Ϣ */
    pstSuspendRsp->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstSuspendRsp->ulSenderPid              = UEPS_PID_HSD;
    pstSuspendRsp->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstSuspendRsp->ulReceiverPid            = UEPS_PID_HALMP;
    pstSuspendRsp->ulLength                 = sizeof(CNAS_CAS_HRPD_SUSPEND_RSP_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSuspendRsp->enMsgId                  = ID_CNAS_CAS_HRPD_SUSPEND_RSP;
    pstSuspendRsp->usOpId                   = 0;
    pstSuspendRsp->enRslt                   = enRslt;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSuspendRsp);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstSuspendRsp);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasResumeRsp
 ��������  : ��CAS����ID_CNAS_CAS_HRPP_RESUME_RSP��Ϣ
 �������  : enValidFlag   : subnetId�Ƿ���Ч

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasResumeRsp(VOS_VOID)
{
    CNAS_CAS_HRPD_RESUME_RSP_STRU      *pstResumeRsp;

    /* ������Ϣ */
    pstResumeRsp = (CNAS_CAS_HRPD_RESUME_RSP_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD,
                                        sizeof(CNAS_CAS_HRPD_RESUME_RSP_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstResumeRsp)
    {
        return;
    }

    /* �����Ϣ */
    pstResumeRsp->ulSenderCpuId            = VOS_LOCAL_CPUID;
    pstResumeRsp->ulSenderPid              = UEPS_PID_HSD;
    pstResumeRsp->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstResumeRsp->ulReceiverPid            = UEPS_PID_HALMP;
    pstResumeRsp->ulLength                 = sizeof(CNAS_CAS_HRPD_RESUME_RSP_STRU) - VOS_MSG_HEAD_LENGTH;
    pstResumeRsp->enMsgId                  = ID_CNAS_CAS_HRPD_RESUME_RSP;
    pstResumeRsp->usOpId                   = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstResumeRsp);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstResumeRsp);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasCFreqLockNtf
 ��������  : �����㷢��CNAS_CAS_1X_FREQ_LOCK_NTF_STRU��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_HSD_SndCasCFreqLockNtf(MSCC_HSD_CFREQ_LOCK_NTF_STRU   *pstCFreqLockNtf)
{
    CNAS_CAS_HRPD_FREQ_LOCK_NTF_STRU     *pstCnasCasCFreqLockNtf   = VOS_NULL_PTR;

    pstCnasCasCFreqLockNtf =
            (CNAS_CAS_HRPD_FREQ_LOCK_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSD,
                                                                        sizeof(CNAS_CAS_HRPD_FREQ_LOCK_NTF_STRU));

    if (VOS_NULL_PTR == pstCnasCasCFreqLockNtf)
    {
        return VOS_FALSE;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCnasCasCFreqLockNtf + VOS_MSG_HEAD_LENGTH),
               0x00,
               (sizeof(CNAS_CAS_HRPD_FREQ_LOCK_NTF_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ����Ϣ */
    pstCnasCasCFreqLockNtf->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstCnasCasCFreqLockNtf->ulSenderPid     = UEPS_PID_HSD;
    pstCnasCasCFreqLockNtf->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstCnasCasCFreqLockNtf->ulReceiverPid   = UEPS_PID_HALMP;
    pstCnasCasCFreqLockNtf->enMsgId         = ID_CNAS_CAS_HRPD_FREQ_LOCK_NTF;
    pstCnasCasCFreqLockNtf->usOpId          = 0;
    pstCnasCasCFreqLockNtf->enMode          = pstCFreqLockNtf->enFreqLockMode;
    pstCnasCasCFreqLockNtf->usBandClass     = pstCFreqLockNtf->usHrpdBandClass;
    pstCnasCasCFreqLockNtf->usFreq          = pstCFreqLockNtf->usHrpdFreq;
    pstCnasCasCFreqLockNtf->usPilotPn       = pstCFreqLockNtf->usHrpdPn;

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstCnasCasCFreqLockNtf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasBeginSessionNotify
 ��������  : HSD֪ͨCAS��ʼSession֪ͨ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��15��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasBeginSessionNotify(VOS_VOID)
{
    CNAS_CAS_HRPD_SESSION_BEGIN_NTF_STRU                   *pstBeginSessionNotify = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength = sizeof(CNAS_CAS_HRPD_SESSION_BEGIN_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstBeginSessionNotify = (CNAS_CAS_HRPD_SESSION_BEGIN_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD, ulMsgLength);

    if (VOS_NULL_PTR == pstBeginSessionNotify)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstBeginSessionNotify + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLength);

    /* ������Ϣ�ṹ�� */
    pstBeginSessionNotify->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->ulSenderPid      = UEPS_PID_HSD;
    pstBeginSessionNotify->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->ulReceiverPid    = UEPS_PID_HALMP;
    pstBeginSessionNotify->ulLength         = ulMsgLength;
    pstBeginSessionNotify->enMsgId          = ID_CNAS_CAS_HRPD_SESSION_BEGIN_NTF;
    pstBeginSessionNotify->enSessionType    = CNAS_CAS_HRPD_SESSION_TYPE_NETWORK_ACQ;

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstBeginSessionNotify);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasEndSessionNotify
 ��������  : HSD֪ͨCAS������Session֪ͨ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��15��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_HSD_SndCasEndSessionNotify(VOS_VOID)
{
    CNAS_CAS_HRPD_SESSION_END_NTF_STRU                     *pstEndSessionNotify = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength = sizeof(CNAS_CAS_HRPD_SESSION_END_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstEndSessionNotify = (CNAS_CAS_HRPD_SESSION_END_NTF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD, ulMsgLength);

    if (VOS_NULL_PTR == pstEndSessionNotify)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstEndSessionNotify + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLength);

    /* ������Ϣ�ṹ�� */
    pstEndSessionNotify->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstEndSessionNotify->ulSenderPid      = UEPS_PID_HSD;
    pstEndSessionNotify->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstEndSessionNotify->ulReceiverPid    = UEPS_PID_HALMP;
    pstEndSessionNotify->ulLength         = ulMsgLength;
    pstEndSessionNotify->enMsgId          = ID_CNAS_CAS_HRPD_SESSION_END_NTF;
    pstEndSessionNotify->enSessionType    = CNAS_CAS_HRPD_SESSION_TYPE_NETWORK_ACQ;

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstEndSessionNotify);

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasHdrCsqSetReq
 ��������  : HSD֪ͨCAS hdr csq set req
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : c00299064
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_SndCasHdrCsqSetReq(
    MSCC_HSD_HDR_CSQ_SET_REQ_STRU      *psrHdrSetReq
)
{
    CNAS_CAS_HRPD_SET_SIGNAL_QUALITY_REQ_STRU              *pstHdrcsqSetReq = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength = sizeof(CNAS_CAS_HRPD_SET_SIGNAL_QUALITY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstHdrcsqSetReq = (CNAS_CAS_HRPD_SET_SIGNAL_QUALITY_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD, ulMsgLength);

    if (VOS_NULL_PTR == pstHdrcsqSetReq)
    {
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_UINT8 *)pstHdrcsqSetReq + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLength);

    /* ������Ϣ�ṹ�� */
    pstHdrcsqSetReq->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstHdrcsqSetReq->ulSenderPid      = UEPS_PID_HSD;
    pstHdrcsqSetReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstHdrcsqSetReq->ulReceiverPid    = UEPS_PID_HRUP;
    pstHdrcsqSetReq->ulLength         = ulMsgLength;

    pstHdrcsqSetReq->enMsgId                = ID_CNAS_CAS_HRPD_SET_SIGNAL_QUALITY_REQ;

    pstHdrcsqSetReq->ucRptRssiThreshold     = psrHdrSetReq->stHdrCsq.ucRssiThreshold;
    pstHdrcsqSetReq->ucTimeInterval         = psrHdrSetReq->stHdrCsq.ucTimeInterval;
    pstHdrcsqSetReq->ucRptSinrThreshold     = psrHdrSetReq->stHdrCsq.ucSnrThreshold;
    pstHdrcsqSetReq->ucRptEcIoThreshold     = psrHdrSetReq->stHdrCsq.ucEcioThreshold;

    /* SNR THRESHOLD �������Ժ�����п��ܻ���� */

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstHdrcsqSetReq);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndCasSuspendRelReq
 ��������  : HSD֪ͨCAS ID_CNAS_CAS_HRPD_SUSPEND_REL_REQ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��29��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_HSD_SndCasSuspendRelReq(VOS_VOID)
{
    CNAS_CAS_HRPD_SUSPEND_REL_REQ_STRU *pstSuspendRelReq = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength = sizeof(CNAS_CAS_HRPD_SUSPEND_REL_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstSuspendRelReq = (CNAS_CAS_HRPD_SUSPEND_REL_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD, ulMsgLength);

    if (VOS_NULL_PTR == pstSuspendRelReq)
    {
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_UINT8 *)pstSuspendRelReq + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLength);

    /* ������Ϣ�ṹ�� */
    pstSuspendRelReq->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstSuspendRelReq->ulSenderPid      = UEPS_PID_HSD;
    pstSuspendRelReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstSuspendRelReq->ulReceiverPid    = UEPS_PID_HALMP;
    pstSuspendRelReq->ulLength         = ulMsgLength;

    pstSuspendRelReq->enMsgId          = ID_CNAS_CAS_HRPD_SUSPEND_REL_REQ;

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstSuspendRelReq);

    return VOS_OK;
}


/*lint -restore*/

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
