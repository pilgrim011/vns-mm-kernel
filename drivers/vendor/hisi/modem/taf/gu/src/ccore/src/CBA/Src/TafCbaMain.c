/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafCbaMain.c
  �� �� ��   : ����
  ��    ��   : l00171473
  ��������   : 2012��3��19��
  ����޸�   :
  ��������   : CBAģ�����Ϣ��ڴ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafCbaMain.h"
#include  "TafCbaProcAs.h"
#include  "TafCbaProcAt.h"
#include  "TafCbaProcMmc.h"
#include  "TafCbaProcMma.h"
#include  "TafCbaProcUsim.h"
#include  "MnComm.h"
#include  "TafLog.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_MAIN_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/



/*****************************************************************************
 �� �� ��  : TAF_CBA_MsgProc
 ��������  : CBAģ�����Ϣ�������
 �������  : pstMsg: CBAģ���յ�����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��19��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���, for V7R1C50 CSFB&PPAC&ETWS&ISR
  2.��    ��   : 2013��07��11��
    ��    ��   : f62575
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_VOID TAF_CBA_MsgProc(
    struct MsgCB                       *pstMsg
)
{
    switch (pstMsg->ulSenderPid)
    {
        case UEPS_PID_GAS:
            TAF_CBA_ProcGasMsg(pstMsg);
            break;

        case WUEPS_PID_WRR:
            TAF_CBA_ProcWrrMsg(pstMsg);
            break;

        case WUEPS_PID_BMC:
            TAF_CBA_ProcBmcMsg(pstMsg);
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case PS_PID_ERRC:
            TAF_CBA_ProcLrrcMsg(pstMsg);
            break;
#endif

        case WUEPS_PID_MMC:
            TAF_CBA_ProcMmcMsg(pstMsg);
            break;

        case WUEPS_PID_AT:
            TAF_CBA_ProcAtMsg(pstMsg);
            break;

        case WUEPS_PID_MMA:
            TAF_CBA_ProcMmaMsg(pstMsg);
            break;

        /* Deleted WUEPS_PID_USIM by f62575 for V9R1 STK����, 2013/07/11 */

        default:
            TAF_ERROR_LOG1(WUEPS_PID_TAF, "TAF_CBA_MsgProc: Unknown message sender, SenderPid, ", (VOS_INT32)pstMsg->ulSenderPid);
            break;

    }
}


#endif /* ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS)) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
