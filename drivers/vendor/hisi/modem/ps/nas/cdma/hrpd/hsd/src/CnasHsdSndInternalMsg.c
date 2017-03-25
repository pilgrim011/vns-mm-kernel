
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdSndInternalMsg.c
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��12��2��
  ����޸�   :
  ��������   : HSD���͸�HSD����Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��12��2��
    ��    ��   : h00300778
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "CnasHsdSndInternalMsg.h"
#include  "CnasMain.h"
#include  "CnasHsdCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_SND_INTERNAL_MSG_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 -e429 -e830 */
/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndSwitchOnRlst
 ��������  : ��ɿ���������Ϣ��HSDָʾ�������
 �������  : ulResult:�������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��12��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndSwitchOnRlst(VOS_UINT32 ulResult)
{
    CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF_STRU                   *pstMsg;
    VOS_UINT32                                              ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF_STRU);

    pstMsg  = (CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF_STRU*)PS_MEM_ALLOC(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSD;
    pstMsg->enMsgId                     = ID_CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_HSD_HSD_SWITCH_ON_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enRslt                      = ulResult;

    CNAS_HSD_PutMsgInIntMsgQueue((VOS_UINT8*)pstMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndPowerOffRslt
 ��������  : ���͹ػ�״̬����ɽ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_OK: ����������Ϣ�ɹ�
             VOS_ERR: ����������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��16��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndPowerOffRslt(VOS_VOID)
{
    CNAS_HSD_HSD_POWER_OFF_RSLT_CNF_STRU                   *pstMsg;
    VOS_UINT32                                              ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen  = sizeof(CNAS_HSD_HSD_POWER_OFF_RSLT_CNF_STRU);

    pstMsg = (CNAS_HSD_HSD_POWER_OFF_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return ;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSD;
    pstMsg->enMsgId                     = ID_CNAS_HSD_HSD_POWER_OFF_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_HSD_HSD_POWER_OFF_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �����ڲ���Ϣ */
    CNAS_HSD_PutMsgInIntMsgQueue((VOS_UINT8*)pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndInternalSysAcqReq
 ��������  : ����ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ��Ϣ
 �������  : enSysAcqScene:��������
             ulFreqNum:������Ƶ�����
             pstFreq:������Ƶ������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��17��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndInternalSysAcqReq(
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enSysAcqScene,
    VOS_UINT32                                              ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU                         *pstFreq
)
{
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ_STRU                  *pstMsg;
    VOS_UINT32                                              ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen   = sizeof(CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ_STRU);

    pstMsg  = (CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return ;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSD;
    pstMsg->enMsgId                     = ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_HSD_HSD_SYSTEM_ACQUIRED_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enSysAcqScene               = enSysAcqScene;
    pstMsg->ulFreqNum                   = ulFreqNum;

    PS_MEM_SET(pstMsg->astFreq, 0, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * CNAS_HSD_INTERNAL_SYSTEM_ACQ_REQ_CHAN_MAX_NUM);

    if ((0 != ulFreqNum)
     && (ulFreqNum <= CNAS_HSD_INTERNAL_SYSTEM_ACQ_REQ_CHAN_MAX_NUM))
    {
        PS_MEM_CPY(pstMsg->astFreq, pstFreq, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * ulFreqNum);
    }

    /* �����ڲ���Ϣ */
    CNAS_HSD_PutMsgInIntMsgQueue((VOS_UINT8*)pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndSysAcqRslt
 ��������  : ����SYSTEM ACQUIRE״̬����ɽ����Ϣ
 �������  : enResult:�������
             enSysAcqScene:��������
             enImmediateSysAcq:�������ɹ�ʱ�Ƿ���������������ָʾ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��16��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndSysAcqRslt(
    CNAS_HSD_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enResult,
    CNAS_HSD_SYS_ACQ_SCENE_ENUM_UINT32                      enCurAcqScene,
    CNAS_HSD_SYS_ACQ_FAIL_ACT_ENUM_UINT8                    enImmediateSysAcq
)
{
    CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstMsg         = VOS_NULL_PTR;
    VOS_UINT32                                              ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen   = sizeof(CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU);

    pstMsg  = (CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU*)PS_MEM_ALLOC(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return ;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSD;
    pstMsg->enMsgId                     = ID_CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_HSD_HSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enRslt                      = enResult;
    pstMsg->enImmediateSysAcq           = enImmediateSysAcq;
    pstMsg->enCurAcqScene               = enCurAcqScene;


    /* �����ڲ���Ϣ */
    CNAS_HSD_PutMsgInIntMsgQueue((VOS_UINT8*)pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndPowerSaveRslt
 ��������  : ����POWER SAVE״̬����ɽ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_OK: ����������Ϣ�ɹ�
             VOS_ERR: ����������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��03��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndPowerSaveRslt(VOS_VOID)
{
    CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF_STRU                   *pstMsg;
    VOS_UINT32                                              ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen  = sizeof(CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF_STRU);

    pstMsg = (CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return ;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSD;
    pstMsg->enMsgId                     = ID_CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_HSD_HSD_POWER_SAVE_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    /* �����ڲ���Ϣ */
    CNAS_HSD_PutMsgInIntMsgQueue((VOS_UINT8*)pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndInterSysRslt
 ��������  : ����ID_CNAS_HSD_HSD_INTER_SYS_RSLT_CNF��Ϣ
 �������  : enCampedRatMode            פ����ʽ
             ucRslt                     C-L���
             enNetworkLostReason        lostԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��17��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndInterSysRslt(
    VOS_RATMODE_ENUM_UINT32                                 enCampedRatMode,
    VOS_UINT8                                               ucRslt,
    CAS_CNAS_HRPD_NETWORK_LOST_REASON_ENUM_UINT16           enNetworkLostReason
)
{
    CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU                   *pstMsg;
    VOS_UINT32                                              ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen   = sizeof(CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU);

    pstMsg  = (CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstMsg)
    {
        return ;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_HSD;
    pstMsg->enMsgId                     = ID_CNAS_HSD_HSD_INTER_SYS_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_HSD_HSD_INTER_SYS_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enCampedRatMode             = enCampedRatMode;
    pstMsg->ucRslt                      = ucRslt;
    pstMsg->enNetworkLostReason         = enNetworkLostReason;

    /* �����ڲ���Ϣ */
    CNAS_HSD_PutMsgInIntMsgQueue((VOS_UINT8*)pstMsg);

    return;
}


/*lint -restore*/

#endif









#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
