/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdSndHsm.c
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��12��10��
  ����޸�   :
  ��������   : HSD���͸�HSM����Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��10��
    ��    ��   : h00300778
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "hsm_hsd_pif.h"
#include  "CnasMain.h"
#include  "CnasHsdSndHsm.h"
#include  "cas_hrpd_airlinkmgmt_nas_pif.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_SND_HSM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndHsmStartReq
 ��������  : ��HSM���Ϳ�������
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
VOS_VOID CNAS_HSD_SndHsmStartReq(VOS_VOID)
{
    HSD_HSM_START_REQ_STRU             *pstMsg;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(HSD_HSM_START_REQ_STRU);

    pstMsg  = (HSD_HSM_START_REQ_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_START_REQ;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �����ڲ���Ϣ */
    CNAS_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndHsmPowerOffReq
 ��������  : ��HSM���͹ػ�����
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
VOS_VOID CNAS_HSD_SndHsmPowerOffReq(VOS_VOID)
{
    HSD_HSM_POWEROFF_REQ_STRU          *pstMsg;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(HSD_HSM_POWEROFF_REQ_STRU);

    pstMsg  = (HSD_HSM_POWEROFF_REQ_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_POWEROFF_REQ;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_POWEROFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �����ڲ���Ϣ */
    CNAS_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndHsmSysAcqSuccInd
 ��������  : ��HSM���������ɹ�
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
VOS_VOID CNAS_HSD_SndHsmSysAcqSuccInd(
    VOS_UINT32                                              aulSystemTime[],
    HSD_HSM_SYSTEM_ACQUIRE_TYPE_ENUM_UINT8                  enCurSysAcqType
)
{
    HSD_HSM_SYSTEM_ACQUIRED_IND_STRU   *pstMsg;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(HSD_HSM_SYSTEM_ACQUIRED_IND_STRU);

    pstMsg  = (HSD_HSM_SYSTEM_ACQUIRED_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_SYSTEM_ACQUIRED_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_SYSTEM_ACQUIRED_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->aulSystemTime[0]            = aulSystemTime[0];
    pstMsg->aulSystemTime[1]            = aulSystemTime[1];
    pstMsg->enSysAcqType                = enCurSysAcqType;

    /* �����ڲ���Ϣ */
    CNAS_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndHsmOverheadMsgInd
 ��������  : ��HSM����Overhead��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��14��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndHsmOverheadMsgInd(
    CAS_CNAS_HRPD_OVERHEAD_MSG_IND_STRU                    *pstCasOhmMsg
)
{
    HSD_HSM_OVERHEAD_MSG_IND_STRU      *pstMsg;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen   = sizeof(HSD_HSM_OVERHEAD_MSG_IND_STRU);

    pstMsg  = (HSD_HSM_OVERHEAD_MSG_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_OVERHEAD_MSG_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_OVERHEAD_MSG_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->usBandClass                 = pstCasOhmMsg->usBandClass;
    pstMsg->usFreq                      = pstCasOhmMsg->usFreq;
    pstMsg->usCountryCode               = pstCasOhmMsg->usCountryCode;

    pstMsg->ucColorCode                 = pstCasOhmMsg->ucColorCode;

    pstMsg->ucSubNetMask                = pstCasOhmMsg->ucSubNetMask;
    pstMsg->ucSecondaryColorCodeCount   = pstCasOhmMsg->ucSecondaryColorCodeCount;
    pstMsg->lLongitude                  = pstCasOhmMsg->lLongitude;
    pstMsg->lLatitude                   = pstCasOhmMsg->lLatitude;

    PS_MEM_CPY(pstMsg->aucSectorId, pstCasOhmMsg->aucSectorId, HSD_HSM_SUBNET_ID_MAX_LENGTH);
    PS_MEM_CPY(pstMsg->aucSecondaryColorCode, pstCasOhmMsg->aucSecondaryColorCode, HSD_HSM_SECOND_COLORCODE_MAX_LENGTH);

    /* �����ڲ���Ϣ */
    CNAS_SndInternalMsg(pstMsg);

    return;
}


VOS_VOID CNAS_HSD_SndHsmOhmNotCurrentInd(VOS_VOID)
{
    HSD_HSM_OHM_NOT_CURRENT_IND_STRU   *pstMsg;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen   = sizeof(HSD_HSM_OHM_NOT_CURRENT_IND_STRU);

    pstMsg  = (HSD_HSM_OHM_NOT_CURRENT_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_OHM_NOT_CURRENT_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_OHM_NOT_CURRENT_IND_STRU) - VOS_MSG_HEAD_LENGTH;


    /* �����ڲ���Ϣ */
    CNAS_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndHsmIratFromLteInd
 ��������  : ��HSM����ID_HSD_HSM_IRAT_FROM_LTE_IND
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
VOS_VOID CNAS_HSD_SndHsmIratFromLteInd(VOS_VOID)
{
    HSD_HSM_IRAT_FROM_LTE_IND_STRU     *pstMsg;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen   = sizeof(HSD_HSM_IRAT_FROM_LTE_IND_STRU);

    pstMsg  = (HSD_HSM_IRAT_FROM_LTE_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_IRAT_FROM_LTE_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_IRAT_FROM_LTE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �����ڲ���Ϣ */
    (VOS_VOID)CNAS_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndHsmIratToLteInd
 ��������  : ��HSM����ID_HSD_HSM_IRAT_TO_LTE_IND
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
VOS_VOID CNAS_HSD_SndHsmIratToLteInd(VOS_VOID)
{
    HSD_HSM_IRAT_TO_LTE_IND_STRU       *pstMsg;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen   = sizeof(HSD_HSM_IRAT_TO_LTE_IND_STRU);

    pstMsg  = (HSD_HSM_IRAT_TO_LTE_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_IRAT_TO_LTE_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_IRAT_TO_LTE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �����ڲ���Ϣ */
    (VOS_VOID)CNAS_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndHsmSuspendInd
 ��������  : ��HSM����ID_HSD_HSM_SUSPEND_IND
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
VOS_VOID CNAS_HSD_SndHsmSuspendInd(VOS_VOID)
{
    HSD_HSM_SUSPEND_IND_STRU           *pstMsg;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen   = sizeof(HSD_HSM_SUSPEND_IND_STRU);

    pstMsg  = (HSD_HSM_SUSPEND_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_SUSPEND_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_SUSPEND_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �����ڲ���Ϣ */
    (VOS_VOID)CNAS_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndHsmResumeInd
 ��������  : ��HSM����ID_HSD_HSM_RESUME_IND
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
VOS_VOID CNAS_HSD_SndHsmResumeInd(VOS_VOID)
{
    HSD_HSM_RESUME_IND_STRU            *pstMsg;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen   = sizeof(HSD_HSM_RESUME_IND_STRU);

    pstMsg  = (HSD_HSM_RESUME_IND_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_RESUME_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_RESUME_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �����ڲ���Ϣ */
    (VOS_VOID)CNAS_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndHsmPowerSaveReq
 ��������  : ��HSM����ID_HSD_HSM_POWER_SAVE_REQ
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
VOS_VOID CNAS_HSD_SndHsmPowerSaveReq(VOS_VOID)
{
    HSD_HSM_POWER_SAVE_REQ_STRU         *pstMsg;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen   = sizeof(HSD_HSM_POWER_SAVE_REQ_STRU);

    pstMsg  = (HSD_HSM_POWER_SAVE_REQ_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_POWER_SAVE_REQ;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_POWER_SAVE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �����ڲ���Ϣ */
    (VOS_VOID)CNAS_SndInternalMsg(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndHsmPilotSearchFailNtf
 ��������  : ��HSM����ID_HSD_HSM_RESUME_IND
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��12��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndHsmPilotSearchFailNtf(VOS_VOID)
{
    HSD_HSM_PILOT_SEARCH_FAIL_NTF_STRU *pstMsg;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen   = sizeof(HSD_HSM_PILOT_SEARCH_FAIL_NTF_STRU);

    pstMsg  = (HSD_HSM_PILOT_SEARCH_FAIL_NTF_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSM;

    pstMsg->enMsgId                     = ID_HSD_HSM_PILOT_SEARCH_FAIL_NTF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_HSM_PILOT_SEARCH_FAIL_NTF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �����ڲ���Ϣ */
    (VOS_VOID)CNAS_SndInternalMsg(pstMsg);

    return;
}

/*lint -restore*/
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
