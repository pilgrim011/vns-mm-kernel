/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdSndMscc.c
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��12��7��
  ����޸�   :
  ��������   : HSD���͸�MMA����Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasHsdSndMscc.h"
#include  "PsCommonDef.h"
#include  "CnasMntn.h"
#include  "CnasHsdComFunc.h"

#include  "hsm_hsd_pif.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_SND_MSCC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndMsccStartCnf
 ��������  : ��MSCC���Ϳ������
 �������  : enRslt - �������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��17��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndMsccStartCnf(
    HSD_MSCC_START_RESULT_ENUM_UINT32    enRslt
)
{
    HSD_MSCC_START_CNF_STRU            *pstStartCnf  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstStartCnf = (HSD_MSCC_START_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSD,
                                                                         sizeof(HSD_MSCC_START_CNF_STRU));
    if (VOS_NULL_PTR == pstStartCnf)
    {
        return;
    }

    /* �����Ϣ */
    pstStartCnf->stMsgHeader.ulReceiverPid      = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstStartCnf->stMsgHeader.ulMsgName          = ID_HSD_MSCC_START_CNF;
    pstStartCnf->enRslt                         = enRslt;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstStartCnf);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstStartCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndMsccPowerOffCnf
 ��������  : ��MSCC���͹ػ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��17��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndMsccPowerOffCnf(VOS_VOID)
{
    HSD_MSCC_POWER_OFF_CNF_STRU         *pstPowerOffCnf  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstPowerOffCnf = (HSD_MSCC_POWER_OFF_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSD,
                                                                                sizeof(HSD_MSCC_POWER_OFF_CNF_STRU));
    if (VOS_NULL_PTR == pstPowerOffCnf)
    {
        return;
    }

    /* �����Ϣ */
    pstPowerOffCnf->stMsgHeader.ulReceiverPid   = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstPowerOffCnf->stMsgHeader.ulMsgName       = ID_HSD_MSCC_POWER_OFF_CNF;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstPowerOffCnf);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstPowerOffCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndMsccSysAcqCnf
 ��������  : ��MMA����ID_HSD_MMA_SYSTEM_ACQUIRE_CNF��Ϣ
 �������  : HSD_MMA_ACQUIRED_RESULT_ENUM_UINT32 enRslt
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��17��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndMsccSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32 enRslt)
{
    HSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU    *pstSysAcqCnf;

    /* ������Ϣ */
    pstSysAcqCnf = (HSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSD,
                                                                                   sizeof(HSD_MSCC_SYSTEM_ACQUIRE_CNF_STRU));
    if (VOS_NULL_PTR == pstSysAcqCnf)
    {
        return;
    }

    /* �����Ϣ */
    pstSysAcqCnf->stMsgHeader.ulReceiverPid          = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSysAcqCnf->stMsgHeader.ulMsgName              = ID_HSD_MSCC_SYSTEM_ACQUIRE_CNF;
    pstSysAcqCnf->enRslt                 = enRslt;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSysAcqCnf);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstSysAcqCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndMsccSysAcqInd
 ��������  : ��MSCC����ID_HSD_MSCC_SYSTEM_ACQUIRE_IND��Ϣ
 �������  : NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32 enRslt
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��17��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndMsccSysAcqInd(NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32 enRslt)
{
    HSD_MSCC_SYSTEM_ACQUIRE_END_IND_STRU                   *pstSysAcqInd;

    /* ������Ϣ */
    pstSysAcqInd = (HSD_MSCC_SYSTEM_ACQUIRE_END_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSD,
                                                                                   sizeof(HSD_MSCC_SYSTEM_ACQUIRE_END_IND_STRU));
    if (VOS_NULL_PTR == pstSysAcqInd)
    {
        return;
    }

    /* �����Ϣ */
    pstSysAcqInd->stMsgHeader.ulReceiverPid     = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSysAcqInd->stMsgHeader.ulMsgName         = ID_HSD_MSCC_SYSTEM_ACQUIRE_END_IND;
    pstSysAcqInd->enRslt                        = enRslt;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSysAcqInd);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstSysAcqInd);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndMsccSysAcqStartInd
 ��������  : ��MSCC����ID_HSD_MSCC_SYSTEM_ACQUIRE_START_IND��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��17��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndMsccSysAcqStartInd(VOS_VOID)
{
    HSD_MSCC_SYSTEM_ACQUIRE_START_IND_STRU                  *pstSysAcqStartInd;

    /* ������Ϣ */
    pstSysAcqStartInd = (HSD_MSCC_SYSTEM_ACQUIRE_START_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSD,
                                                                                              sizeof(HSD_MSCC_SYSTEM_ACQUIRE_START_IND_STRU));
    if (VOS_NULL_PTR == pstSysAcqStartInd)
    {
        return;
    }

    /* �����Ϣ */
    pstSysAcqStartInd->stMsgHeader.ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSysAcqStartInd->stMsgHeader.ulMsgName        = ID_HSD_MSCC_SYSTEM_ACQUIRE_START_IND;

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstSysAcqStartInd);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndMsccHrpdIratToLteNtf
 ��������  : ��SCC����ID_HSD_MSCC_HRPD_IRAT_TO_LTE_NTF��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndMsccHrpdIratToLteNtf(VOS_VOID)
{
    HSD_MSCC_HRPD_IRAT_TO_LTE_NTF_STRU  *pstHrpdIratToLteNtf;

    /* ������Ϣ */
    pstHrpdIratToLteNtf = (HSD_MSCC_HRPD_IRAT_TO_LTE_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSD,
                                                                                            sizeof(HSD_MSCC_HRPD_IRAT_TO_LTE_NTF_STRU));
    if (VOS_NULL_PTR == pstHrpdIratToLteNtf)
    {
        return;
    }

    /* �����Ϣ */
    pstHrpdIratToLteNtf->stMsgHeader.ulReceiverPid  = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstHrpdIratToLteNtf->stMsgHeader.ulMsgName      = ID_HSD_MSCC_HRPD_IRAT_TO_LTE_NTF;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstHrpdIratToLteNtf);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstHrpdIratToLteNtf);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndMsccDataCallRedialSysAcqCnf
 ��������  : ��MSCC����HSD_MSCC_DATA_CALL_REDIAL_SYS_ACQ_CNF_STRU��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��14��
    ��    ��   : d00212987
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndMsccDataCallRedialSysAcqCnf(NAS_MSCC_PIF_ACQUIRED_RESULT_ENUM_UINT32 enRslt)
{
    HSD_MSCC_DATA_CALL_REDIAL_SYS_ACQ_CNF_STRU  *pstDataCallSysAcqCnf;

    /* ������Ϣ */
    pstDataCallSysAcqCnf = (HSD_MSCC_DATA_CALL_REDIAL_SYS_ACQ_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSD,
                                                                                            sizeof(HSD_MSCC_DATA_CALL_REDIAL_SYS_ACQ_CNF_STRU));
    if (VOS_NULL_PTR == pstDataCallSysAcqCnf)
    {
        return;
    }

    /* �����Ϣ */
    pstDataCallSysAcqCnf->stMsgHeader.ulReceiverPid     = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstDataCallSysAcqCnf->stMsgHeader.ulMsgName         = ID_HSD_MSCC_DATA_CALL_REDIAL_SYS_ACQ_CNF;
    pstDataCallSysAcqCnf->enRslt                        = enRslt;
    pstDataCallSysAcqCnf->ucIsEhrpdSupport              = VOS_FALSE;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstDataCallSysAcqCnf);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstDataCallSysAcqCnf);

    return;
}


VOS_VOID CNAS_HSD_SndMsccSessionNegRsltInd(
    VOS_UINT8                                   ucNegRslt,
    VOS_UINT8                                   ucIsNewSession,
    HSD_MSCC_SESSION_RELEASE_TYPE_ENUM_UINT32   enCurrSessionRelType,
    VOS_UINT8                                   ucIsEhrpdSupport
)
{
    HSD_MSCC_SESSION_NEG_RSLT_IND_STRU                     *pstSessionInfo;
    HSD_MSCC_SESSION_NEG_RSLT_ENUM_UINT32                   enRslt;

    /* ������Ϣ */
    pstSessionInfo = (HSD_MSCC_SESSION_NEG_RSLT_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSD,
                    sizeof(HSD_MSCC_SESSION_NEG_RSLT_IND_STRU));
    if (VOS_NULL_PTR == pstSessionInfo)
    {
        return;
    }

    if (HSM_HSD_SESSION_NEG_RSLT_SUCCESS == ucNegRslt)
    {
        enRslt = HSD_MSCC_SESSION_NEG_RESULT_SUCC;
    }
    else
    {
        enRslt = HSD_MSCC_SESSION_NEG_RESULT_FAIL;
    }

    /* �����Ϣ */
    pstSessionInfo->stMsgHeader.ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);;
    pstSessionInfo->stMsgHeader.ulMsgName           = ID_HSD_MSCC_SESSION_NEG_RSLT_IND;
    pstSessionInfo->enRslt                          = enRslt;
    pstSessionInfo->ucIsNewSession                  = ucIsNewSession;
    pstSessionInfo->enCurrSessionRelType            = enCurrSessionRelType;

    pstSessionInfo->ucIsEhrpdSupport                = ucIsEhrpdSupport;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSessionInfo);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstSessionInfo);

    return;
}



VOS_VOID CNAS_HSD_SndMsccOverheadMsgInd(
    CAS_CNAS_HRPD_OVERHEAD_MSG_IND_STRU                    *pstCasOhmMsg,
    CNAS_PRL_HRPD_SYSTEM_STRU                              *pstHrpdSys
)
{
    HSD_MSCC_OVERHEAD_MSG_IND_STRU      *pstOhmInd;

    /* ������Ϣ */
    pstOhmInd = (HSD_MSCC_OVERHEAD_MSG_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSD,
                    sizeof(HSD_MSCC_OVERHEAD_MSG_IND_STRU));
    if (VOS_NULL_PTR == pstOhmInd)
    {
        return;
    }

    /* �����Ϣ */
    pstOhmInd->stMsgHeader.ulReceiverPid = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstOhmInd->stMsgHeader.ulMsgName     = ID_HSD_MSCC_OVERHEAD_MSG_IND;

    pstOhmInd->usBandClass               = pstCasOhmMsg->usBandClass;
    pstOhmInd->usFreq                    = pstCasOhmMsg->usFreq;
    pstOhmInd->ulMcc                     = CNAS_HSD_ConvertHrpdMccToNasMcc(pstCasOhmMsg->usCountryCode);
    pstOhmInd->ucUATIColorCode           = pstCasOhmMsg->ucColorCode;
    pstOhmInd->ucSubNetMask              = pstCasOhmMsg->ucSubNetMask;
    pstOhmInd->ucSecondaryColorCodeCount = pstCasOhmMsg->ucSecondaryColorCodeCount;
    pstOhmInd->lLongitude                = pstCasOhmMsg->lLongitude;
    pstOhmInd->lLatitude                 = pstCasOhmMsg->lLatitude;
    pstOhmInd->ulSector24                = pstCasOhmMsg->ulSector24;

    PS_MEM_SET(pstOhmInd->aucRsv, 0, sizeof(pstOhmInd->aucRsv));

    pstOhmInd->ucPriClass_AI                              = CNAS_HSD_GetPriClassWithTypeAI(pstHrpdSys);
    pstOhmInd->ucPriClass_HRPD                            = CNAS_HSD_GetPriClassWithTypeHRPD(pstHrpdSys);

    PS_MEM_CPY(pstOhmInd->aucSectorId, pstCasOhmMsg->aucSectorId, HSD_MSCC_SUBNET_ID_MAX_LENGTH);
    PS_MEM_CPY(pstOhmInd->aucSecondaryColorCode, pstCasOhmMsg->aucSecondaryColorCode, HSD_MSCC_SECOND_COLORCODE_MAX_LENGTH);

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstOhmInd);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstOhmInd);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndMsccSysCfgCnf
 ��������  : ��MSCC����HSD_MSCC_SYS_CFG_CNF��Ϣ
 �������  : pstRcvMsg -- �յ�����Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��13��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndMsccSysCfgCnf(
    CAS_CNAS_HRPD_SYS_CFG_CNF_STRU     *pstRcvMsg
)
{
    HSD_MSCC_SYS_CFG_CNF_STRU          *pstSysCfgCnf = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSysCfgCnf = (HSD_MSCC_SYS_CFG_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSD,
                                                                             sizeof(HSD_MSCC_SYS_CFG_CNF_STRU));
    if (VOS_NULL_PTR == pstSysCfgCnf)
    {
        return;
    }

    PS_MEM_SET(pstSysCfgCnf, 0, sizeof(HSD_MSCC_SYS_CFG_CNF_STRU));

    pstSysCfgCnf->stMsgHeader.ulSenderPid     = UEPS_PID_HSD;
    pstSysCfgCnf->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstSysCfgCnf->stMsgHeader.ulReceiverPid   = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSysCfgCnf->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSysCfgCnf->stMsgHeader.ulLength        = sizeof(HSD_MSCC_SYS_CFG_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstSysCfgCnf->usOpId                      = pstRcvMsg->usOpId;
    pstSysCfgCnf->stMsgHeader.ulMsgName       = ID_HSD_MSCC_SYS_CFG_CNF;

    pstSysCfgCnf->enRst                       = NAS_MSCC_PIF_SYS_CFG_SET_SUCCESS;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSysCfgCnf);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstSysCfgCnf);

}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndMsccPowerSaveCnf
 ��������  : ��MSCC����POWER SAVE���
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
VOS_VOID CNAS_HSD_SndMsccPowerSaveCnf(
    NAS_MSCC_PIF_POWER_SAVE_RESULT_ENUM_UINT8               enRslt
)
{
    HSD_MSCC_POWER_SAVE_CNF_STRU         *pstPowerSaveCnf  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstPowerSaveCnf = (HSD_MSCC_POWER_SAVE_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSD,
                                                                                sizeof(HSD_MSCC_POWER_SAVE_CNF_STRU));
    if (VOS_NULL_PTR == pstPowerSaveCnf)
    {
        return;
    }

    /* �����Ϣ */
    pstPowerSaveCnf->stMsgHeader.ulReceiverPid   = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstPowerSaveCnf->stMsgHeader.ulMsgName       = ID_HSD_MSCC_POWER_SAVE_CNF;
    pstPowerSaveCnf->usOpId                      = 0;
    pstPowerSaveCnf->enResult                    = enRslt;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstPowerSaveCnf);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstPowerSaveCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndMsccBgSearchCnf
 ��������  : ��MSCC����Bg Search���
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
VOS_VOID CNAS_HSD_SndMsccBgSearchCnf(
    CAS_CNAS_HRPD_BSR_LTE_CNF_STRU     *pstMsg
)
{
    HSD_MSCC_BG_SEARCH_CNF_STRU        *pstBgSearchCnf  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstBgSearchCnf = (HSD_MSCC_BG_SEARCH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSD,
                                                                                sizeof(HSD_MSCC_BG_SEARCH_CNF_STRU));
    if (VOS_NULL_PTR == pstBgSearchCnf)
    {
        return;
    }

    /* �����Ϣ */
    pstBgSearchCnf->stMsgHeader.ulReceiverPid   = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstBgSearchCnf->stMsgHeader.ulMsgName       = ID_HSD_MSCC_BG_SEARCH_CNF;
    pstBgSearchCnf->usOpId                      = 0;
    pstBgSearchCnf->enRslt                      = pstMsg->ucRslt;

    pstBgSearchCnf->stPlmnList.enRat         = NAS_MSCC_PIF_NET_RAT_TYPE_LTE;
    pstBgSearchCnf->stPlmnList.ucHighPlmnNum = CNAS_MIN(pstMsg->ucHighPlmnNum, CNAS_CAS_HRPD_BSR_LTE_MAX_HIGH_PLMN_NUM);
    pstBgSearchCnf->stPlmnList.ucLowPlmnNum  = CNAS_MIN(pstMsg->ucLowPlmnNum, CNAS_CAS_HRPD_BSR_LTE_MAX_LOW_PLMN_NUM);

    if (CNAS_CAS_HRPD_BSR_RSLT_SUCC == pstMsg->ucRslt)
    {
        CNAS_HSD_ConvertLmmPlmnToGUNasPlmn(pstBgSearchCnf->stPlmnList.ucHighPlmnNum,
                                           pstMsg->astHighPlmnList,
                                           pstBgSearchCnf->stPlmnList.astHighPlmnID);

        CNAS_HSD_ConvertLmmPlmnToGUNasPlmn(pstBgSearchCnf->stPlmnList.ucLowPlmnNum,
                                           pstMsg->astLowPlmnList,
                                           pstBgSearchCnf->stPlmnList.astLowPlmnID);

    }

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstBgSearchCnf);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstBgSearchCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndMsccHrpdSysInfoCnf
 ��������  : ��MSCC����qry hrpd sys info���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��04��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndMsccHrpdSysInfoCnf(
    VOS_UINT8                            ucHrpdSysNum,
    MSCC_HSD_HRPD_SYS_INFO_STRU         *pstHrpdSysInfoList
)
{
    HSD_MSCC_QRY_HRPD_SYS_INFO_CNF_STRU        *pstHrpdSysInfoCnf  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstHrpdSysInfoCnf = (HSD_MSCC_QRY_HRPD_SYS_INFO_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSD,
                                                                                sizeof(HSD_MSCC_QRY_HRPD_SYS_INFO_CNF_STRU));
    if (VOS_NULL_PTR == pstHrpdSysInfoCnf)
    {
        return;
    }

    /* �����Ϣ */
    pstHrpdSysInfoCnf->stMsgHeader.ulReceiverPid   = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstHrpdSysInfoCnf->stMsgHeader.ulMsgName       = ID_HSD_MSCC_QRY_HRPD_SYS_INFO_CNF;
    pstHrpdSysInfoCnf->usOpId                      = 0;
    pstHrpdSysInfoCnf->ucHrpdSysNum                = ucHrpdSysNum;

    PS_MEM_CPY(pstHrpdSysInfoCnf->astHrpdSysInfoList,
               pstHrpdSysInfoList,
               sizeof(MSCC_HSD_HRPD_SYS_INFO_STRU) * ucHrpdSysNum);

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstHrpdSysInfoCnf);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstHrpdSysInfoCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndMsccStopBgSearchCnf
 ��������  : ��MSCC����ID_HSD_MSCC_STOP_BG_SEARCH_CNF
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
VOS_VOID CNAS_HSD_SndMsccStopBgSearchCnf(VOS_VOID)
{
    HSD_MSCC_STOP_BG_SEARCH_CNF_STRU                        *pstStopBgSearchCnf  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstStopBgSearchCnf = (HSD_MSCC_STOP_BG_SEARCH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSD,
                                        sizeof(HSD_MSCC_STOP_BG_SEARCH_CNF_STRU));
    if (VOS_NULL_PTR == pstStopBgSearchCnf)
    {
        return;
    }

    /* �����Ϣ */
    pstStopBgSearchCnf->stMsgHeader.ulReceiverPid   = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstStopBgSearchCnf->stMsgHeader.ulMsgName       = ID_HSD_MSCC_STOP_BG_SEARCH_CNF;
    pstStopBgSearchCnf->usOpId                      = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstStopBgSearchCnf);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstStopBgSearchCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndMsccSystemSyncInd
 ��������  : ͬ���ɹ�����MSCC����SYNC IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��07��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndMsccSystemSyncInd(VOS_VOID)
{
    HSD_MSCC_SYSTEM_SYNC_IND_STRU      *pstSyncInd  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSyncInd = (HSD_MSCC_SYSTEM_SYNC_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSD,
                                                                                sizeof(HSD_MSCC_SYSTEM_SYNC_IND_STRU));
    if (VOS_NULL_PTR == pstSyncInd)
    {
        return;
    }

    /* �����Ϣ */
    pstSyncInd->stMsgHeader.ulReceiverPid   = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSyncInd->stMsgHeader.ulMsgName       = ID_HSD_MSCC_SYSTEM_SYNC_IND;
    pstSyncInd->usOpId                      = 0;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstSyncInd);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstSyncInd);

    return;
}


VOS_VOID CNAS_HSD_SndMsccHrpdCasStatusInd(
    HSD_MSCC_HRPD_CAS_STATUS_ENUM_UINT16                    enHrpdCasStatus
)
{
    HSD_MSCC_CAS_STATUS_IND_STRU       *pstHsdMsccCasStatusInd   = VOS_NULL_PTR;

    pstHsdMsccCasStatusInd = (HSD_MSCC_CAS_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSD,
                    sizeof(HSD_MSCC_CAS_STATUS_IND_STRU));

    if (VOS_NULL_PTR == pstHsdMsccCasStatusInd)
    {
        return;
    }

    pstHsdMsccCasStatusInd->stMsgHeader.ulReceiverPid      = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstHsdMsccCasStatusInd->stMsgHeader.ulMsgName          = ID_HSD_MSCC_CAS_STATUS_IND;

    pstHsdMsccCasStatusInd->enCasStatus                    = enHrpdCasStatus;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstHsdMsccCasStatusInd);

    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstHsdMsccCasStatusInd);
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndMsccInterSysStartInd
 ��������  : ͬ���ɹ�����MSCC����INTERSYS_START_IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��11��13��
    ��    ��   : y00346957
    �޸�����   : DTS2015070910837�޸ģ�intersys cause ö��ͳһ��mscc pif�е�

*****************************************************************************/
VOS_VOID CNAS_HSD_SndMsccInterSysStartInd(
    VOS_RATMODE_ENUM_UINT32                                 enOrignRatMode,
    VOS_RATMODE_ENUM_UINT32                                 enDestRatMode,
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32                 enInterSysCause
)
{
    HSD_MSCC_INTERSYS_START_IND_STRU   *pstInterSysStaInd  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstInterSysStaInd = (HSD_MSCC_INTERSYS_START_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSD,
                                                                                sizeof(HSD_MSCC_INTERSYS_START_IND_STRU));
    if (VOS_NULL_PTR == pstInterSysStaInd)
    {
        return;
    }

    /* �����Ϣ */
    pstInterSysStaInd->stMsgHeader.ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstInterSysStaInd->stMsgHeader.ulMsgName        = ID_HSD_MSCC_INTERSYS_START_IND;
    pstInterSysStaInd->usOpId                       = 0;
    pstInterSysStaInd->enOrignRatMode               = enOrignRatMode;
    pstInterSysStaInd->enDestRatMode                = enDestRatMode;
    pstInterSysStaInd->enInterSysCause              = enInterSysCause;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstInterSysStaInd);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstInterSysStaInd);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndMsccInterSysEndInd
 ��������  : ͬ���ɹ�����MSCC����INTERSYS_END_IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��02��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndMsccInterSysEndInd(
    VOS_RATMODE_ENUM_UINT32             enCurrRatMode
)
{
    HSD_MSCC_INTERSYS_END_IND_STRU     *pstInterSysEndInd  = VOS_NULL_PTR;

    /* ������Ϣ */
    pstInterSysEndInd = (HSD_MSCC_INTERSYS_END_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_HSD,
                                                                                sizeof(HSD_MSCC_INTERSYS_END_IND_STRU));
    if (VOS_NULL_PTR == pstInterSysEndInd)
    {
        return;
    }

    /* �����Ϣ */
    pstInterSysEndInd->stMsgHeader.ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstInterSysEndInd->stMsgHeader.ulMsgName        = ID_HSD_MSCC_INTERSYS_END_IND;
    pstInterSysEndInd->usOpId                       = 0;
    pstInterSysEndInd->enCurrRatMode                = enCurrRatMode;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstInterSysEndInd);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_HSD, pstInterSysEndInd);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndMsccRfAvailInd
 ��������  : ��MSCC����RF��Դ�Ƿ����ָʾ
 �������  : VOS_UINT8 : ucRfAvail - RF�Ƿ����
             VOS_TRUE  : ��Ƶ����
             VOS_FALSE : ��Ƶ������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��14��
   ��    ��   : x00306642
   �޸�����   : �½�
*****************************************************************************/
VOS_VOID CNAS_HSD_SndMsccRfAvailInd(
    VOS_UINT8                           ucRfAvail
)
{
    NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU *pstRfAvailInd = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength     = sizeof(NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstRfAvailInd   = (NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD, ulMsgLength);

    if (VOS_NULL_PTR == pstRfAvailInd)
    {
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstRfAvailInd) + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLength);

    pstRfAvailInd->stMsgHeader.ulMsgName           = ID_HSD_MSCC_RF_AVAILABLE_IND;
    pstRfAvailInd->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstRfAvailInd->stMsgHeader.ulSenderPid         = UEPS_PID_HSD;
    pstRfAvailInd->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstRfAvailInd->stMsgHeader.ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstRfAvailInd->stMsgHeader.ulLength            = ulMsgLength;
    pstRfAvailInd->ucRfAvailFlg                    = ucRfAvail;
    pstRfAvailInd->enRatType                       = NAS_MSCC_PIF_RF_AVAILABLE_RAT_TYPE_HRPD;

    PS_SEND_MSG(UEPS_PID_HSD, pstRfAvailInd);

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndMsccHrpdNoSrvInd
 ��������  : ��MSCC֪ͨHSD�޷�����ã�MSCC�յ�����Ϣ��MMA֪ͨHRPD�޷���MMA�����޷�����ʱ�ϱ���ʱ��
             ���ó���:IDLE̬���յ�CAS_CNAS_HRPD_NETWORK_LOST_IND��Ϣ����������
                      IDLE̬���յ�HSM_HSD_SESSION_NEG_RESULT_IND��Ϣ��enNegResult������SUCCESS
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��09��30��
   ��    ��   : l00324781
   �޸�����   : �½�
*****************************************************************************/
VOS_VOID CNAS_HSD_SndMsccHrpdNoSrvInd(VOS_VOID)
{
    HSD_MSCC_HRPD_NO_SERVICE_IND_STRU                      *pstRptHrpdNoSrvInd = VOS_NULL_PTR;
    VOS_UINT32                                              ulMsgLength;

    ulMsgLength          = sizeof(HSD_MSCC_HRPD_NO_SERVICE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstRptHrpdNoSrvInd   = (HSD_MSCC_HRPD_NO_SERVICE_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD, ulMsgLength);

    if (VOS_NULL_PTR == pstRptHrpdNoSrvInd)
    {
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstRptHrpdNoSrvInd) + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLength);

    pstRptHrpdNoSrvInd->stMsgHeader.ulMsgName           = ID_HSD_MSCC_HRPD_NO_SERVICE_IND;
    pstRptHrpdNoSrvInd->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstRptHrpdNoSrvInd->stMsgHeader.ulSenderPid         = UEPS_PID_HSD;
    pstRptHrpdNoSrvInd->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstRptHrpdNoSrvInd->stMsgHeader.ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstRptHrpdNoSrvInd->stMsgHeader.ulLength            = ulMsgLength;

    PS_SEND_MSG(UEPS_PID_HSD, pstRptHrpdNoSrvInd);

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndMsccHdrCsqSetCnf
 ��������  : ��MSCC����HDRCSQ_SET_CNF
 �������  : NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM_UINT8      enRslt
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��14��
   ��    ��   : C00299064
   �޸�����   : �½�
*****************************************************************************/
VOS_VOID CNAS_HSD_SndMsccHdrCsqSetCnf(
    NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM_UINT8      enRslt
)
{
    HSD_MSCC_HDR_CSQ_SET_CNF_STRU      *pstSetCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength     = sizeof(HSD_MSCC_HDR_CSQ_SET_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstSetCnf   = (HSD_MSCC_HDR_CSQ_SET_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD, ulMsgLength);

    if (VOS_NULL_PTR == pstSetCnf)
    {
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstSetCnf) + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLength);

    pstSetCnf->stMsgHeader.ulMsgName           = ID_HSD_MSCC_HDR_CSQ_SET_CNF;
    pstSetCnf->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstSetCnf->stMsgHeader.ulSenderPid         = UEPS_PID_HSD;
    pstSetCnf->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstSetCnf->stMsgHeader.ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstSetCnf->stMsgHeader.ulLength            = ulMsgLength;

    pstSetCnf->enRslt                          = enRslt;

    PS_SEND_MSG(UEPS_PID_HSD, pstSetCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndMsccHdrCsqQualityInd
 ��������  : ��MSCC����HDRCSQ_IND
 �������  : NAS_MSCC_PIF_CDMACSQ_SET_RESULT_ENUM_UINT8      enRslt
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��14��
   ��    ��   : C00299064
   �޸�����   : �½�
*****************************************************************************/
VOS_VOID CNAS_HSD_SndMsccHdrCsqQualityInd(
    VOS_INT16                            sHrpdRssi,
    VOS_INT16                            sHrpdSnr,
    VOS_INT16                            sHrpdEcio
)
{
    HSD_MSCC_HDR_CSQ_IND_STRU          *pstCsqInd = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLength;

    ulMsgLength     = sizeof(HSD_MSCC_HDR_CSQ_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstCsqInd       = (HSD_MSCC_HDR_CSQ_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_HSD, ulMsgLength);

    if (VOS_NULL_PTR == pstCsqInd)
    {
        return;
    }

    PS_MEM_SET(((VOS_UINT8 *)pstCsqInd) + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLength);

    pstCsqInd->stMsgHeader.ulMsgName           = ID_HSD_MSCC_HDR_CSQ_IND;
    pstCsqInd->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstCsqInd->stMsgHeader.ulSenderPid         = UEPS_PID_HSD;
    pstCsqInd->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstCsqInd->stMsgHeader.ulReceiverPid       = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), UEPS_PID_MSCC);
    pstCsqInd->stMsgHeader.ulLength            = ulMsgLength;

    pstCsqInd->sHrpdRssi                       = sHrpdRssi;
    pstCsqInd->sHrpdSnr                        = sHrpdSnr;
    pstCsqInd->sHrpdEcio                       = sHrpdEcio;

    PS_SEND_MSG(UEPS_PID_HSD, pstCsqInd);

    return;
}



/*lint -restore*/

#endif









#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
