/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXccSndMma.c
  �� �� ��   : ����
  ��    ��   : y00322978
  ��������   : 2015��07��21��
  ��������   : 1X CC����mma����Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��07��21��
    ��    ��   : y00322978
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasXccSndMma.h"
#include  "CnasCcb.h"
#include  "CnasMntn.h"
#include  "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_XCC_SND_MMA_C


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 �� �� ��  : CNAS_XCC_SndMma1XCallState
 ��������  : xcc �ϱ�mma 1x call state
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��21��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��20��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_VOID CNAS_XCC_SndMma1XCallState(
    XCC_MMA_1X_CALL_STATE_ENUM_UINT8    enCallState
)
{
    XCC_MMA_1X_CALL_STATE_IND_STRU     *pstCallStateInd = VOS_NULL_PTR;

    /* ������Ϣ */
    pstCallStateInd  = (XCC_MMA_1X_CALL_STATE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_XCC,
                      sizeof(XCC_MMA_1X_CALL_STATE_IND_STRU));

    if (VOS_NULL_PTR == pstCallStateInd)
    {
        return;
    }

    /* �����Ϣ���� */
    NAS_MEM_SET_S((VOS_UINT8 *)pstCallStateInd + VOS_MSG_HEAD_LENGTH,
                  sizeof(XCC_MMA_1X_CALL_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(XCC_MMA_1X_CALL_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    /* �����Ϣ */
    pstCallStateInd->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstCallStateInd->ulSenderPid      = UEPS_PID_XCC;
    pstCallStateInd->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstCallStateInd->ulReceiverPid    = CNAS_CCB_ConvertPidBasedOnModemId(CNAS_CCB_GetCdmaModeModemId(), WUEPS_PID_MMA);
    pstCallStateInd->ulLength         = sizeof(XCC_MMA_1X_CALL_STATE_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCallStateInd->enMsgId          = ID_XCC_MMA_1X_CALL_STATE_IND;
    pstCallStateInd->enCallState      = enCallState;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstCallStateInd);

    /* ������Ϣ */
    (VOS_VOID)PS_SEND_MSG(UEPS_PID_XCC, pstCallStateInd);
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




