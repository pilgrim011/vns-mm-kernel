/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafCbaProcTimer.c
  �� �� ��   : ����
  ��    ��   : l00171473
  ��������   : 2012��3��26��
  ����޸�   :
  ��������   : CBAģ�鴦��TIMER��صĴ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��3��26��
    ��    ��   : l00171473
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafCbaProcTimer.h"
#include  "TafCbaProcUsim.h"
#include  "TafCbaProcAs.h"
#include  "TafCbaComFunc.h"
#include  "TafLog.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_CBA_PROC_TIMER_C

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


/*****************************************************************************
 �� �� ��  : TAF_CBA_RcvTiWaitGetCbEfRspTimerExpired
 ��������  : ��ʼ��ʱ��ȡUSIM�е�EFCBMI,EFCBMIR,EFCBMID�ļ�ʱ,��ʱ����ʱ��Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2007��2��04��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��3��20��
    ��    ��   : l00171473
    �޸�����   : for V7R1C50 CSFB&PPAC&ETWS&ISR
  3.��    ��   : 2012��3��28��
    ��    ��   : w00176964
    �޸�����   : for V7R1C50 CSFB&PPAC&ETWS&ISR
  4.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����

*****************************************************************************/
VOS_VOID  TAF_CBA_RcvTiWaitGetCbEfRspTimerExpired(
    VOS_UINT32                          ulParam
)
{
    TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvTiWaitGetCbEfRspTimerExpired: Entered.");

    /* �����ȡ�ļ������б�� */
    /* Deleted by f62575 for V9R1 STK����, 2013-6-26, begin */
    /* TAF_CBA_ClearAllReadUsimFilesFlg */
    /* Deleted by f62575 for V9R1 STK����, 2013-6-26, end */

}

#if ((FEATURE_ON == FEATURE_ETWS))
/*****************************************************************************
 �� �� ��  : TAF_CBA_RcvTiEtwsTempEnableCbsTimerExpired
 ��������  : ��ʱʹ�ܵ�CBS�Ķ�ʱ����ʱ����ȥʹ��CBS����
 �������  : ulParam: Timer parameter, input when the timer is started.
                      ���ڱ���ʱ������ʱδ����ò����������ﲻ������
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��2��
    ��    ��   : l00171473
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CBA_RcvTiEtwsTempEnableCbsTimerExpired(
    VOS_UINT32                          ulParam
)
{
    TAF_CBA_NET_RAT_TYPE_ENUM_UINT8     enNetMode;
    VOS_UINT32                          ulIsActiveListEmpty;

    TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_CBA_RcvTiEtwsTempEnableCbsTimerExpired: Entered.");

    enNetMode = TAF_CBA_GetNetRatType();

    /* Wģʱ����Ҫȥʹ��CBS���� */
    /* todo:���G֧��ETWS��������Ҫ�޸� */
    if (TAF_CBA_NET_RAT_TYPE_WCDMA  != enNetMode)
    {
        return;
    }

    /* ��ʱ�������������û��������ü����б�Ϊ���ˣ���ʱ�Ͳ���Ҫ��AS��DISABLE�� */
    ulIsActiveListEmpty = TAF_CBA_IsCbsActiveListEmpty();
    if ( VOS_TRUE != ulIsActiveListEmpty )
    {
        /* ��AS��CBS DISABLE��Ϣ */
        TAF_CBA_SndAsActiveCbsReq(TAF_CBS_CFG_DEACTIVE);
    }
}

/*lint -restore */

#endif
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
