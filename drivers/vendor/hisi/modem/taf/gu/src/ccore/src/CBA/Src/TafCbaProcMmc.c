/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafCbaProcMmc.c
  �� �� ��   : ����
  ��    ��   : l00171473
  ��������   : 2012��3��21��
  ����޸�   :
  ��������   : ����MMC��CBA��ص���Ϣ
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��3��21��
    ��    ��   : l00171473
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafCbaProcMmc.h"
#include  "TafCbaProcAs.h"
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, begin */
/* ɾ��ExtAppMmcInterface.h*/
/* Deleted by z00161729 for �����ϱ�AT�������������C��, 2013-4-7, end */
#include  "TafMmcInterface.h"
#include  "TafCbaComFunc.h"
#include  "MnComm.h"
#include  "TafLog.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_PROC_MMC_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_CBA_RcvMmcNetModeInd
 ��������  : �յ�MMC֪ͨAS��׼���ã���֪ͨ�˵�ǰģʽ��CBSģ���ж�CBS�Ƿ񼤻�,
             �������·�����б������,���򲻽����κβ���
 �������  : ucCurrNet  - ��ǰ�Ľ���ģʽ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��7��
    ��    ��   : zhoujun /z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��3��2��
    ��    ��   : l00171473
    �޸�����   : for V7R1C50 CSFB&PPAC&ETWS&ISR
  3.��    ��   : 2012��3��28��
    ��    ��   : w00176964
    �޸�����   : USIM�ļ���ȡ�߼��޸�
  4.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
*****************************************************************************/
VOS_VOID TAF_CBA_RcvMmcNetModeInd(
    VOS_UINT8                           ucCurrNet
)
{
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enNetType;

    /* ���뼼������ת�� */
    TAF_CBA_ConvertMnNetModeToCbaFormat(ucCurrNet, &enNetType);

    /* ���ģʽ��Ч,ֱ�ӷ��أ�������*/
    if ( TAF_CBA_NET_RAT_TYPE_BUTT == enNetType )
    {
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvMmcNetModeInd:INVALID Mode ");
        return;
    }

    /* ���ģʽδ�����ı�,����Ҫ֪ͨAS */
    if ( enNetType == TAF_CBA_GetNetRatType() )
    {
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvMmcNetModeInd:Same Mode ");
        return;
    }

    /* ��¼�µĽ���ģʽ */
    TAF_CBA_SetNetRatType(enNetType);

    /* ��ǰ�꿪��δ�򿪻�CBSδ����,��ֱ�ӷ���  */
    if ( VOS_FALSE == TAF_CBA_IsNeedActAsCbs())
    {
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvMmcNetModeInd:CBS Disable ");
        return;
    }

    /* Deleted by f62575 for V9R1 STK����, 2013-6-26, begin */
    /* ��ѯ�Ƿ��USIM�л�ȡ��CBS ID�������,�����ǰδ��ȡ�򲻽����κδ���ֱ�ӷ���
        �ȴ�USIM��ʼ����ɺ�,�ڼ����·������Ϣ���д��� */
    /* Deleted by f62575 for V9R1 STK����, 2013-6-26, end */

    /* �����б�Ϊ��ʱ����AS��CBS���� */
    if (VOS_FALSE == TAF_CBA_IsCbsActiveListEmpty())
    {
        TAF_CBA_SndAsActiveCbsReq(TAF_CBS_CFG_ACTIVE);
    }
}

/*****************************************************************************
 �� �� ��  : TAF_CBA_ProcMmcMsg
 ��������  : ��������MMC����Ϣ
 �������  : pstMsg: ����MMCģ���VOS��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CBA_ProcMmcMsg(
    struct MsgCB                       *pstMsg
)
{
    TAFMMC_CBS_CURR_NET_MODE_IND_STRU  *pstMsgInd;

    switch (((MSG_HEADER_STRU *)pstMsg)->ulMsgName)
    {
        case TAFMMC_CBS_NO_NETWORK_IND:
            TAF_CBA_SetNetRatType(TAF_CBA_NET_RAT_TYPE_BUTT);
            break;

        case TAFMMC_CBS_CURR_NET_MODE_IND:
            pstMsgInd = (TAFMMC_CBS_CURR_NET_MODE_IND_STRU *)pstMsg;
            TAF_CBA_RcvMmcNetModeInd(pstMsgInd->ucCurNetWork);
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_ProcMmcMsg:Rcv Invalid Msg Type");
            break;
    }
}



#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
