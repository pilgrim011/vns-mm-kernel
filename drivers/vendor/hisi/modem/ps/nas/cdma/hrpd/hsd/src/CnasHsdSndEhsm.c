/******************************************************************************

                  ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasHsdSndEhsm.c
  �� �� ��   : ����
  ��    ��   : z00316370
  ��������   : 2015��06��03��
  ����޸�   :
  ��������   : HSD���͸�EHSM����Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��06��03��
    ��    ��   : z00316370
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "CnasMain.h"
#include  "CnasHsdSndEhsm.h"
#include  "cas_hrpd_airlinkmgmt_nas_pif.h"
#include  "PsCommonDef.h"
#include  "CnasMntn.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_HSD_SND_EHSM_C

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
 ��������  : ��EHSM���Ϳ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��04��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndEhsmStartReq(
    MSCC_HSD_START_REQ_STRU            *pstMsg
)
{
    HSD_EHSM_START_REQ_STRU            *pstStartMsg;
    VOS_UINT32                          ulLen;
    VOS_UINT32                          i;

    i                                   = 0;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen        = sizeof(HSD_EHSM_START_REQ_STRU);

    pstStartMsg  = (HSD_EHSM_START_REQ_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);

    if (VOS_NULL_PTR == pstStartMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstStartMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstStartMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstStartMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstStartMsg->ulReceiverPid               = UEPS_PID_EHSM;
    pstStartMsg->enMsgId                     = ID_HSD_EHSM_START_REQ;
    pstStartMsg->usOpId                      = 0;
    pstStartMsg->ulLength                    = sizeof(HSD_EHSM_START_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    pstStartMsg->enModemId                   = pstMsg->enModemId;

    /* ��ʼ��RatMode = BUTT */
    for (i = NAS_MSCC_PIF_MAX_RAT_NUM; i < VOS_RATMODE_BUTT; i++)
    {
        pstStartMsg->aenRatMode[i]  = VOS_RATMODE_BUTT;
    }

    PS_MEM_CPY(pstStartMsg->aenRatMode,
               pstMsg->aenRatMode,
               NAS_MSCC_PIF_MAX_RAT_NUM * sizeof(VOS_RATMODE_ENUM_UINT32));

    /* �����ڲ���Ϣ */
    (VOS_VOID)CNAS_SndInternalMsg(pstStartMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_HSD_SndEhsmPowerOffReq
 ��������  : ��EHSM���͹ػ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��04��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_HSD_SndEhsmPowerOffReq(
    EHSM_HSD_POWER_OFF_CAUSE_ENUM_UINT32                    enCause
)
{
    HSD_EHSM_POWER_OFF_REQ_STRU        *pstMsg;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(HSD_EHSM_POWER_OFF_REQ_STRU);

    pstMsg  = (HSD_EHSM_POWER_OFF_REQ_STRU *)CNAS_GetIntMsgSendBuf(UEPS_PID_HSD, ulLen);
    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    /* �����Ϣ */
    pstMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = UEPS_PID_HSD;
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid               = UEPS_PID_EHSM;

    pstMsg->enMsgId                     = ID_HSD_EHSM_POWER_OFF_REQ;
    pstMsg->usOpId                      = 0;
    pstMsg->ulLength                    = sizeof(HSD_EHSM_POWER_OFF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->enCause                     = enCause;

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
