/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : GmmCasTimer.c
  Author       : Roger Leo
  Version      : V200R001
  Date         : 2005-08-25
  Description  : ��C�ļ�������GmmCasTimerģ���ʵ��
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2005-08-25
     Author: Roger Leo
     Modification:update
  2. s46746 2006-03-08 �������ⵥA32D02368�޸�
  3. x51137 2006/4/28 A32D02889
  4. s46746 2006-05-08 �������ⵥA32D03487�޸�
  5.��    ��   : 2006��11��1��
    ��    ��   : s46746
    �޸�����   : �������ⵥ�ţ�A32D06572
  6.��    ��   : 2006��11��8��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:A32D06867
  7.��    ��   : 2006��12��31��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:A32D08178
  8.��    ��   : 2007��06��16��
    ��    ��   : l60022475
    �޸�����   : ���ⵥ��:A32D11726
  9.��    ��   : 2007��12��12��
    ��    ��   : l00107747
    �޸�����   : �������ⵥ�ţ�A32D12829
 10.��    ��   : 2007��12��28��
    ��    ��   : s46746
    �޸�����   : �������ⵥ�ţ�A32D13987,RAU֮��û�����SPEC��־
************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/

#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasTimer.h"
#include "GmmCasSend.h"
#include "GmmCasComm.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:luojian 107747;������:sunshaohua65952;ԭ��:LOG���������Ҫ*/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_CASTIMER_C
/*lint +e767 �޸���:luojian 107747;������:sunshaohua*/

/*****************************************************************************
 Prototype      :
 Description    :
                  HSS 4100 V200R001 ����
                  READY TIMER��ʱ��Ϣ��ں���
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-25
    Author      : Roger Leo
    Modification: Created function

  2. x51137 2006/4/28 A32D02889
  3.��    ��   : 2006��11��8��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:A32D06867
  4.��    ��   : 2006��12��31��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:A32D08178
  5.��    ��   : 2007��06��16��
    ��    ��   : l60022475
    �޸�����   : ���ⵥ��:A32D11726
  6.��    ��   : 2009��08��23��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:AT2D13700,�ػ���,T3314��ʱ����T3312δ�ر�
  7.��    ��   : 2011��05��03��
    ��    ��   : l65478
    �޸�����   : ���ⵥDTS2011043000267,ready״̬��G->W->G CCO,��W�½����ֹ,��W��û������T3312
  8.��    ��   : 2011��12��24��
    ��    ��   : w00166186
    �޸�����   : DTS2011121905287,L��ѡ��W��3312��ʱ������ATTACH
  9.��    ��   : 2012��1��30��
    ��    ��   : l00130025
    �޸�����   : DTS2012010500368,����ͬ���ӿ�VOS_GetRelTmRemainTimehTimerʱû���ж�hTimer�Ƿ�Ϊ0���붨ʱ���첽��Ϣ��ͻ�����쳣��ӡ
  10.��    ��   : 2012��3��3��
     ��    ��   : z00161729
     �޸�����   : V7R1 C50 ֧��ISR�޸�,T3312����ֹͣ��ʱ����֪ͨL
  11.��    ��   : 2012��08��02��
    ��    ��   : l65478
    �޸�����   : DTS2012080104467,��W��T3314��ʱ,����״̬û�и���
  12.��    ��   : 2013��07��24��
    ��    ��   : l65478
    �޸�����   : DTS2013072303435,T3314��ʱ��,��RAU��״̬��û��֪ͨGAS����STANDBY
  13.��    ��   : 2013��08��16��
    ��    ��   : l65478
    �޸�����   : DTS2013081400197,T3314��ʱ��,������ֹ��ǰ��ע�����

*****************************************************************************/
VOS_VOID GMM_TimReadyExpired(VOS_VOID)
{
    VOS_UINT32                          ulT3311Status;
    VOS_UINT32                          ulT3302Status;

    if (GMM_DEREGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {
        gstGmmCasGlobalCtrl.GmmSrvState     = GMM_IU_PMM_DETACHED;
    }
    else
    {
        gstGmmCasGlobalCtrl.GmmSrvState     = GMM_AGB_GPRS_STANDBY;
    }

    /* WCDMAģʽ����HSS 4100 V100R001���봦�� */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        /* ��ע��״̬,���ҷ���״̬�ǿ���̬ʱ,����3312 */
        if ((0x20 == (g_GmmGlobalCtrl.ucState & 0xF0))
         && (GMM_FALSE == g_GmmGlobalCtrl.ucSigConFlg)
         && (GMM_TRUE != g_GmmRauCtrl.ucT3312ExpiredFlg ))
        {
#if (FEATURE_LTE == FEATURE_ON)
            if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
            {
                NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
            }
#endif
            Gmm_TimerStart(GMM_TIMER_T3312);
        }
        return;     /* ���账���� */
    }

    if (GMM_DEREGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {
        gstGmmCasGlobalCtrl.GmmSrvState     = GMM_IU_PMM_DETACHED;
    }
    else
    {
        ulT3311Status = NAS_GMM_QryTimerStatus(GMM_TIMER_T3311);
        ulT3302Status = NAS_GMM_QryTimerStatus(GMM_TIMER_T3302);

        if ((GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState)
          || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == g_GmmGlobalCtrl.ucState))
        {
            if ((VOS_FALSE == ulT3311Status)
             && (VOS_FALSE == ulT3302Status))
            {
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                }
#endif
                Gmm_TimerStart(GMM_TIMER_T3312);
            }
        }
        else
        {
            if ((0x10 != (g_GmmGlobalCtrl.ucState & 0xF0))
             && (GMM_REGISTERED_INITIATED != g_GmmGlobalCtrl.ucState))
                {
#if (FEATURE_LTE == FEATURE_ON)
                if (GMM_TIMER_T3312_FLG != (GMM_TIMER_T3312_FLG & g_GmmTimerMng.ulTimerRunMask))
                {
                    NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_START);
                }
#endif
                Gmm_TimerStart(GMM_TIMER_T3312);
            }
        }

        gstGmmCasGlobalCtrl.GmmSrvState     = GMM_AGB_GPRS_STANDBY;
    }

    NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);


    return;
}

/*****************************************************************************
 Prototype      :
 Description    :
                  HSS 4100 V200R001 ����
                  GMM_TIMER_RAU_RSP��ʱ��Ϣ����
 Input          :
 Output         :
 Return Value   :
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-11-25
    Author      : Roger Leo
    Modification: Created function

  2. x51137 2006/4/28 A32D02889
  3.��    ��   : 2006��11��1��
    ��    ��   : s46746
    �޸�����   : �������ⵥ�ţ�A32D06572
  4.��    ��   : 2006��11��6��
    ��    ��   : s46746
    �޸�����   : �������ⵥ�ţ�A32D06867
*****************************************************************************/
VOS_VOID GMM_TimRauRspExpired(VOS_VOID)
{
    gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg = VOS_TRUE;

    /* ����Ҫ�ȴ�WRR�Ļظ���Ϣ�������Ѿ��յ�WRR�Ļظ���Ϣ������RAU���̽�������Ӧ���� */
    if (   (VOS_FALSE == g_GmmInterRatInfoCtrl.ucRauCmpWaitInterRatCnfMsg)
        || (VOS_TRUE == g_GmmInterRatInfoCtrl.ucInterRatCnfMsgRcvdFlg))
    {
        NAS_GMM_RauCompleteHandling();
    }

    return;
}


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
