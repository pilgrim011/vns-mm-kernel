/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnCallProcMma.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2014��04��26��
  ����޸�   :
  ��������   : ��������MMAģ�����Ϣ
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2014��04��26��
    ��    ��   : y00245242
    �޸�����   : �����ļ�

******************************************************************************/


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "MnCallProcMma.h"
#include "MnCallMnccProc.h"
#include "MnCall.h"

#include "TafSdcLib.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define    THIS_FILE_ID                 PS_FILE_ID_MN_CALL_PROC_MMA_C

/*****************************************************************************
   2 ��������
*****************************************************************************/


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 �� �� ��  : TAF_CALL_ClearCallInfo
 ��������  : ���������Ϣ

 �������  : pstMsg   - ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��20��
    ��    ��   : w00242748
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_CALL_ClearCallInfo(VOS_VOID)
{
    /*���������������ر�������*/
    if (VOS_TRUE == MN_CALL_GetChannelOpenFlg())
    {
        MN_CALL_SetChannelOpenFlg(VOS_FALSE);
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-18, begin */
        /* ������Ϣ֪ͨVC�ر�����ͨ�� */
        MN_CALL_SendVcMsg(CALL_VC_CHANNEL_CLOSE);
        /* ������Ϣ֪ͨAT����ͨ��״̬ */
        MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_CLOSE);
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-18, end */
    }

    MN_CALL_Init(MN_CALL_POWER_STATE_OFF);
}
/*****************************************************************************
 �� �� ��  : TAF_CALL_RcvMmaPowerOffInd
 ��������  : ��������MMA�Ĺػ�ָʾ��Ϣ

 �������  : pstMsg   - ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��04��26��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_VOID TAF_CALL_RcvMmaPowerOffInd(
    TAF_MMA_POWER_OFF_IND_STRU         *pstMsg
)
{
    TAF_CALL_ClearCallInfo();
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_CALL_RcvMmaPowerOffInd
 ��������  : ��������MMA�Ĺػ�ָʾ��Ϣ

 �������  : pstMsg   - ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��04��26��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_VOID TAF_CALL_RcvMmaSyscfgInfoInd(
    MMA_TAF_SYS_CFG_INFO_IND_STRU       *pstMsg
)
{
    VOS_UINT32                          ulIsSupportGsm;

    ulIsSupportGsm = TAF_SDC_IsSpecRatInRatList(TAF_MMA_RAT_GSM, &(pstMsg->stNewRatOrder));

    if ( (VOS_TRUE == TAF_SDC_IsSpecRatInRatList(TAF_MMA_RAT_WCDMA, &(pstMsg->stNewRatOrder)))
      || (VOS_TRUE == ulIsSupportGsm) )
    {
        return;
    }

    TAF_CALL_ClearCallInfo();
}
#endif

/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



