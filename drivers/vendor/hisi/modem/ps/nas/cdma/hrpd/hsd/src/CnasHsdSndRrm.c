/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdSndRrm.c
  �� �� ��   : ����
  ��    ��   : g00256031
  ��������   : 2015��1��16��
  ����޸�   :
  ��������   : HSD���͸�RRM����Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��1��16��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasMntn.h"
#include  "PsRrmInterface.h"
#include  "CnasCcb.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_SND_RRM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958*/
/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndRrmRegisterInd
 ��������  : ��RRM����ID_PS_RRM_REGISTER_IND��Ϣ
 �������  : enTaskType         :ע����������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��14��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��07��15��
    ��    ��   : x00306642
    �޸�����   : �޸Ľӿ�
*****************************************************************************/
VOS_VOID CNAS_HSD_SndRrmRegisterInd(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType
)
{
    /* �������VOS���ͺ����ķ���ֵ  */
    VOS_UINT32                          ulRet;

    /* ����ԭ������ָ�� */
    PS_RRM_REGISTER_IND_STRU            *pstMsg    = VOS_NULL_PTR;

    pstMsg = (PS_RRM_REGISTER_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  UEPS_PID_HSD,
                                                  sizeof(PS_RRM_REGISTER_IND_STRU));
    /* �ڴ�����ʧ�� */
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_SndRrmRegisterInd():Alloc memory failed.");

        /* ����ʧ�� */
        return;
    }

    PS_MEM_SET( (VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                 sizeof(PS_RRM_REGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH );

    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = UEPS_PID_RRM;
    pstMsg->stMsgHeader.ulMsgName           = ID_PS_RRM_REGISTER_IND;

    pstMsg->enModemId                       = CNAS_CCB_GetCdmaModeModemId();
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = VOS_RATMODE_HRPD;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*������Ϣ*/
    ulRet = PS_SEND_MSG(UEPS_PID_HSD, pstMsg);

    /* ����ʧ�� */
    if (VOS_OK != ulRet)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_SndRrmRegisterInd():Send Msg failed.");
    }

    return;
}


/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndRrmDeRegisterInd
 ��������  : ��RRM����ID_PS_RRM_DEREGISTER_IND��Ϣ
 �������  : enTaskType         :ע����������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��14��
    ��    ��   : g00256031
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��07��15��
    ��    ��   : x00306642
    �޸�����   : �޸Ľӿ�
*****************************************************************************/
VOS_VOID CNAS_HSD_SndRrmDeRegisterInd(
    RRM_PS_TASK_TYPE_ENUM_UINT16        enTaskType
)
{
    /* �������VOS���ͺ����ķ���ֵ  */
    VOS_UINT32                          ulRet;

    /* ����ԭ������ָ�� */
    PS_RRM_DEREGISTER_IND_STRU         *pstMsg    = VOS_NULL_PTR;

    pstMsg = (PS_RRM_DEREGISTER_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                  UEPS_PID_HSD,
                                                  sizeof(PS_RRM_DEREGISTER_IND_STRU));
    /* �ڴ�����ʧ�� */
    if (VOS_NULL_PTR == pstMsg)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_SndRrmDeRegisterInd():Alloc memory failed.");

        /* ����ʧ�� */
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
                 sizeof(PS_RRM_DEREGISTER_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = UEPS_PID_HSD;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = UEPS_PID_RRM;
    pstMsg->stMsgHeader.ulMsgName           = ID_PS_RRM_DEREGISTER_IND;

    pstMsg->enModemId                       = CNAS_CCB_GetCdmaModeModemId();
    pstMsg->enTaskType                      = enTaskType;
    pstMsg->enRatType                       = VOS_RATMODE_HRPD;

    CNAS_MNTN_LogMsgInfo((MSG_HEADER_STRU*)pstMsg);

    /*������Ϣ*/
    ulRet = PS_SEND_MSG(UEPS_PID_HSD, pstMsg);

    /* ����ʧ�� */
    if (VOS_OK != ulRet)
    {
        CNAS_ERROR_LOG(UEPS_PID_HSD, "CNAS_HSD_SndRrmDeRegisterInd():Send Msg failed.");
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
