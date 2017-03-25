/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsmSndRrm.c
  �� �� ��   : ����
  ��    ��   : t00323010
  ��������   : 2015��5��29��
  ����޸�   :
  ��������   : HSM���͸�RRM����Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��05��29��
    ��    ��   : t00323010
    �޸�����   : �����ɺ���

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CnasMntn.h"
#include "CnasHsmSndRrm.h"
#include "CnasMntn.h"
#include "Nas_Mem.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSM_SND_RRM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_HSM_SndRrmRegisterInd
 ��������  : ��RRM����ID_PS_RRM_REGISTER_IND��Ϣ
 �������  : enTaskType         :ע����������
             enRatType          :����ģʽ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��29��
    ��    ��   : t00323010
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_HSM_SndRrmRegisterInd(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType,
    VOS_RATMODE_ENUM_UINT32             enRatType
)
{
    /* �������VOS���ͺ����ķ���ֵ  */
    VOS_UINT32                          ulRet;
    MODEM_ID_ENUM_UINT16                enModemId;

    /* ����ԭ������ָ�� */
    PS_RRM_REGISTER_IND_STRU           *pstMsg    = VOS_NULL_PTR;

    enModemId   = VOS_GetModemIDFromPid(UEPS_PID_HSM);

    pstMsg      = (PS_RRM_REGISTER_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  UEPS_PID_HSM,
                                                  sizeof(PS_RRM_REGISTER_IND_STRU));
    /* �ڴ�����ʧ�� */
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_SndRrmRegisterInd():Alloc memory failed.");

        /* ����ʧ�� */
        return;
    }

    NAS_MEM_SET_S((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(PS_RRM_REGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(PS_RRM_REGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = UEPS_PID_HSM;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = UEPS_PID_RRM;
    pstMsg->stMsgHeader.ulMsgName           = ID_PS_RRM_REGISTER_IND;

    pstMsg->enModemId                       = enModemId;
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = enRatType;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*������Ϣ*/
    ulRet = PS_SEND_MSG(UEPS_PID_HSM, pstMsg);

    /* ����ʧ�� */
    if (VOS_OK != ulRet)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_SndRrmRegisterInd():Send Msg failed.");
    }

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_HSM_SndRrmDeRegisterInd
 ��������  : ��RRM����ID_PS_RRM_DEREGISTER_IND��Ϣ
 �������  : enTaskType         :ȥע����������
             enRatType          :����ģʽ����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��29��
    ��    ��   : t00323010
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID CNAS_HSM_SndRrmDeRegisterInd(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType,
    VOS_RATMODE_ENUM_UINT32             enRatType
)
{
    /* �������VOS���ͺ����ķ���ֵ  */
    VOS_UINT32                          ulRet;
    MODEM_ID_ENUM_UINT16                enModemId;

    /* ����ԭ������ָ�� */
    PS_RRM_DEREGISTER_IND_STRU         *pstMsg    = VOS_NULL_PTR;

    enModemId   = VOS_GetModemIDFromPid(UEPS_PID_HSM);

    pstMsg      = (PS_RRM_DEREGISTER_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  UEPS_PID_HSM,
                                                  sizeof(PS_RRM_DEREGISTER_IND_STRU));
    /* �ڴ�����ʧ�� */
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSM, "CNAS_HSM_SndRrmDeRegisterInd():Alloc memory failed.");

        /* ����ʧ�� */
        return;
    }

    NAS_MEM_SET_S((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,
                  sizeof(PS_RRM_DEREGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH,
                  0,
                  sizeof(PS_RRM_DEREGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = UEPS_PID_HSM;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = UEPS_PID_RRM;
    pstMsg->stMsgHeader.ulMsgName           = ID_PS_RRM_DEREGISTER_IND;

    pstMsg->enModemId                       = enModemId;
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = enRatType;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*������Ϣ*/
    ulRet = PS_SEND_MSG(UEPS_PID_HSM, pstMsg);

    /* ����ʧ�� */
    if (VOS_OK != ulRet)
    {
        CNAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRrmDeRegisterInd():Send Msg failed.");
    }

    return;
}

#endif
/*lint -restore*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
