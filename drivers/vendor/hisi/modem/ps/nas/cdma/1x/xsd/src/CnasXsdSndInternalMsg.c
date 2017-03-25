/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsdSndInternalMsg.c
  �� �� ��   : ����
  ��    ��   : h00246512
  ��������   : 2014��7��5��
  ����޸�   :
  ��������   : XSD���͸�XSD����Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��7��5��
    ��    ��   : h00246512
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "CnasXsdSndInternalMsg.h"
#include  "CnasMain.h"
#include "Nas_Mem.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XSD_SND_INTERNAL_MSG_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 -e429 -e830 */
/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndSwitchOnRlst
 ��������  : �յ�CAS�������ȷ�Ϻ�����Ϣ��XSDָʾ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��8��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��10��15��
    ��    ��   : c00299063
    �޸�����   : ����XSD�ڲ���Ϣ

*****************************************************************************/
VOS_VOID CNAS_XSD_SndSwitchOnRlst(
    VOS_UINT32                          ulResult
)
{
    CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF_STRU                   *pstMsg = VOS_NULL_PTR;


    pstMsg  = (CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                            sizeof(CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */

    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XSD;
    pstMsg->enMsgId                     = ID_CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_XSD_XSD_SWITCH_ON_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enRslt                      = ulResult;

    CNAS_XSD_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);

}


/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndPowerOffRslt
 ��������  : ���͹ػ�״̬����ɽ����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_OK: ����������Ϣ�ɹ�
             VOS_ERR: ����������Ϣʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��8��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��10��15��
    ��    ��   : c00299063
    �޸�����   : ����XSD�ڲ���Ϣ
  3. Date      : 2015-04-11
     Author    : a00295761
     Content   : Added argument to receive internal message ID. The function can accept two arguments:
                 ID_CNAS_XSD_XSD_POWER_OFF_RSLT_CNF and ID_CNAS_XSD_XSD_POWER_SAVE_RSLT_CNF

*****************************************************************************/
VOS_VOID CNAS_XSD_SndPowerOffRslt(
    CNAS_XSD_POWEROFF_RSLT_ENUM_UINT32                      enRslt,
    CNAS_XSD_POWEROFF_REASON_ENUM_UINT32                    enPowerOffReason
)
{
    CNAS_XSD_XSD_POWER_OFF_RSLT_CNF_STRU                   *pstMsg = VOS_NULL_PTR;


    pstMsg  = (CNAS_XSD_XSD_POWER_OFF_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                            sizeof(CNAS_XSD_XSD_POWER_OFF_RSLT_CNF_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */

    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XSD;
    pstMsg->enMsgId                     = ID_CNAS_XSD_XSD_POWER_OFF_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_XSD_XSD_POWER_OFF_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enPowerOffReason            = enPowerOffReason;
    pstMsg->enRslt                      = enRslt;

    /* �����ڲ���Ϣ */
    CNAS_XSD_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndInternalSysAcqReq
 ��������  : ����ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ��Ϣ
 �������  : CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene
             VOS_UINT32                          ulFreqNum
             CNAS_PRL_FREQENCY_CHANNEL_STRU         *pstFreq
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��8��7��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��10��15��
    ��    ��   : c00299063
    �޸�����   : ����XSD�ڲ���Ϣ

*****************************************************************************/
VOS_VOID CNAS_XSD_SndInternalSysAcqReq(
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32  enSysAcqScene,
    VOS_UINT32                          ulFreqNum,
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstFreq
)
{
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU                  *pstMsg = VOS_NULL_PTR;


    /* ����ڲ���Ϣ���У��Ƿ��л���������� */
    pstMsg  = (CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                            sizeof(CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */

    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XSD;
    pstMsg->enMsgId                     = ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_XSD_XSD_SYSTEM_ACQUIRED_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enSysAcqScene               = enSysAcqScene;
    pstMsg->ulFreqNum                   = ulFreqNum;

    NAS_MEM_SET_S(pstMsg->astFreq, sizeof(pstMsg->astFreq), 0, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * CNAS_XSD_INTERNAL_SYSTEM_ACQ_REQ_CHAN_MAX_NUM);

    if ((0 != ulFreqNum)
     && (ulFreqNum <= CNAS_XSD_INTERNAL_SYSTEM_ACQ_REQ_CHAN_MAX_NUM))
    {
        NAS_MEM_CPY_S(pstMsg->astFreq, sizeof(pstMsg->astFreq), pstFreq, sizeof(CNAS_PRL_FREQENCY_CHANNEL_STRU) * ulFreqNum);
    }

    /* �����ڲ���Ϣ */
    CNAS_XSD_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}

/*****************************************************************************
 �� �� ��  : CNAS_XSD_SndSysAcqRslt
 ��������  : ����SYSTEM ACQUIRE״̬����ɽ����Ϣ
 �������  : CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enResult
             VOS_UINT8                                               ucImmediateSysAcq
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��31��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��10��15��
    ��    ��   : c00299063
    �޸�����   : ����XSD�ڲ���Ϣ
  3.��    ��   : 2014��12��2��
    ��    ��   : w00176964
    �޸�����   : CDMA 1X Iteration 5 Modfied

*****************************************************************************/
VOS_VOID CNAS_XSD_SndSysAcqRslt(
    CNAS_XSD_SYSTEM_ACQUIRED_RESULT_ENUM_UINT32             enResult,
    CNAS_XSD_SYS_ACQ_SCENE_ENUM_UINT32                      enCurAcqScene,
    VOS_UINT8                                               ucImmediateSysAcq
)
{
    CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU             *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                            sizeof(CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */

    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XSD;
    pstMsg->enMsgId                     = ID_CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_XSD_XSD_SYSTEM_ACQUIRED_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enRslt                      = enResult;
    pstMsg->ucImmediateSysAcq           = ucImmediateSysAcq;
    pstMsg->enCurAcqScene               = enCurAcqScene;


    /* �����ڲ���Ϣ */
    CNAS_XSD_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}




VOS_VOID CNAS_XSD_SndInternalRedirInd(
    CNAS_XSD_REDIRECTION_INFO_STRU                          *pstRedirectionInfo
)
{
    CNAS_XSD_XSD_REDIRECTION_IND_STRU  *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_XSD_XSD_REDIRECTION_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                            sizeof(CNAS_XSD_XSD_REDIRECTION_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XSD;
    pstMsg->enMsgId                     = ID_CNAS_XSD_XSD_REDIRECTION_IND;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_XSD_XSD_REDIRECTION_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stRedirectionInfo           = *pstRedirectionInfo;

    /* �����ڲ���Ϣ */
    CNAS_XSD_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}




VOS_VOID CNAS_XSD_SndRedirRslt(
    CNAS_XSD_REDIRECTION_RESULT_ENUM_UINT32                 enResult
)
{
    CNAS_XSD_XSD_REDIRECTION_RSLT_CNF_STRU                 *pstMsg = VOS_NULL_PTR;

    pstMsg  = (CNAS_XSD_XSD_REDIRECTION_RSLT_CNF_STRU *)PS_MEM_ALLOC(UEPS_PID_XSD,
                                                            sizeof(CNAS_XSD_XSD_REDIRECTION_RSLT_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */

    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_XSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_XSD;
    pstMsg->enMsgId                     = ID_CNAS_XSD_XSD_REDIRECTION_RSLT_CNF;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(CNAS_XSD_XSD_REDIRECTION_RSLT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enRslt                      = enResult;

    /* �����ڲ���Ϣ */
    CNAS_XSD_PutMsgInIntMsgQueue((VOS_UINT8 *)pstMsg);
}




/*lint -restore*/

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
