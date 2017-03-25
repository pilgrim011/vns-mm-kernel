/*******************************************************************************
  Copyright     : 2005-2007, Huawei Tech. Co., Ltd.
  File name     : GmmDetach.c
  Description   : GMM��ʱ��������ش�����Դ�ļ�
  Function List :
    01.   Gmm_RcvTimerExpired
    02.   Gmm_Tim3302Expired
    03.   Gmm_Tim3310Expired
    04.   Gmm_Tim3311Expired
    05.   Gmm_Tim3312Expired
    06.   Gmm_Tim3312Expired_RegNmlServ
    07.   Gmm_Tim3312Expired_RegNoCell
    08.   Gmm_Tim3316Expired
    09.   Gmm_Tim3317Expired
    10.   Gmm_Tim3318Expired
    11.   Gmm_Tim3320Expired
    12.   Gmm_Tim3321Expired
    13.   Gmm_Tim3321Expired_DeregInit
    14.   Gmm_Tim3321Expired_RegImsiDtchInit
    15.   Gmm_Tim3330Expired
    16.   Gmm_Tim5sExpired
    17.   Gmm_TimerCreat
    18.   Gmm_TimerDistroy
    19.   Gmm_TimerPause
    20.   Gmm_TimerPauseForTc
    21.   Gmm_TimerResume
    22.   Gmm_TimerResumeForTc
    23.   Gmm_TimerStart
    24.   Gmm_TimerStop
    25.   Gmm_TimProtectExpired
  History       :
    1.  ��־��  2003.12.05  �¹�����
    2.  s46746  2006-03-08  �������ⵥA32D02368�޸�
    3.  s46746  2006-03-27  �������ⵥA32D02387�޸�
    4.  s46746  2006-04-18  �������ⵥA32D03102�޸�
    5.  l40632   2006-04-17  �������ⵥA32D03132�޸�
    6.  s46746  2006-05-08  �������ⵥA32D03487�޸�
    7.  l40632  2006-06-08  �������ⵥA32D04196�޸�
    8.  ��    ��   : 2006��9��23��
        ��    ��   : sunxibo id:46746
        �޸�����   : �������ⵥ�ţ�A32D05848
    9.  ��    ��   : 2006��11��8��
        ��    ��   : s46746
        �޸�����   : ���ⵥ��:A32D06867
   10.  ��    ��   : 2006��11��20��
        ��    ��   : s46746
        �޸�����   : �������������ⵥ�ţ�A32D07433
   11.  ��    ��   : 2006��12��07��
        ��    ��   : s46746
        �޸�����   : �������������ⵥ�ţ�A32D07799
   12.  ��    ��   : 2007��01��04��
        ��    ��   : s46746
        �޸�����   : �������������ⵥ�ţ�A32D08235
   13.  ��    ��   : 2007��03��20��
        ��    ��   : x51137
        �޸�����   : A32D09192
   14.  ��    ��   : 2007��3��30��
        ��    ��   : s46746
        �޸�����   : ���ⵥ��:A32D09854
   15.  ��    ��   : 2007��05��11��
        ��    ��   : luojian id:60022475
        �޸�����   : ���ⵥ��:A32D10713
   16.  ��    ��   : 2007��7��14��
        ��    ��   : luojian id:60022475
        �޸�����   : �������ⵥ�ţ�A32D12438
   17.  ��    ��   : 2007��11��12��
        ��    ��   : l39007
        �޸�����   : �������ⵥA32D13044,VOS_GetRelTmRemainTime����ִ��ʧ��,
                     ��ʱ��ʣ��ʱ�䲻����,��ʱ����������
   18.  ��    ��   : 2007��11��22��
        ��    ��   : s46746
        �޸�����   : �������ⵥ�ţ�A32D13475,�޸���ϵͳ�ı��ָ�ɵ�old TLLI�Ϳ���������ԿΪȫ0����
   19.  ��    ��   : 2007��12��14��
        ��    ��   : s46746
        �޸�����   : ���ⵥA32D13638����֤����RAU֮ǰ�������෢���������ݣ�����RAU���ɹ������ָ���2
   20.  ��    ��   : 2007��12��28��
        ��    ��   : s46746
        �޸�����   : �������ⵥ�ţ�A32D13954,�޸�GMM��2G3�����л�����Ϣ����
   21.  ��    ��   : 2008��7��2��
        ��    ��   : l00107747
        �޸�����   : �������ⵥ�ţ�AT2D03900,FOLLOW ON��־����Ų�
   22.  ��    ��   : 2008��10��2��
        ��    ��   : s46746
        �޸�����   : �������ⵥ�ţ�AT2D05988,W�¹ػ�ʱ�����GPRS Detach��������
                     δ�ͷ����ӵ���GMM 5S��ʱ����ʱ��GMMδ��MMCָʾ���Ӳ�����
   23.  ��    ��   : 2007��4��25��
        ��    ��   : h44270
        �޸�����   : ���ⵥ��:AT2D11404/AT2D10802
   24.  ��    ��   : 2009��04��25��
        ��    ��   : h44270
        �޸�����   : ���ⵥ��:AT2D08867
   25.  ��    ��   : 2009��07��30��
        ��    ��   : x00115505
        �޸�����   : ���ⵥ��:AT2D13363,���뱻�ܺ�GAS��Ӧ�����GRM���ݣ�Ӧ����STOP GRM���ȴ�T3172/T3146��ʱ����INIT GRM��
   26.  ��    ��   : 2009��08��24��
        ��    ��   : x00115505
        �޸�����   : AT2D14023,����GCF����44.2.2.1.9ʧ��
   27.  ��    ��   : 2009��08��25��
        ��    ��   : l60609
        �޸�����   : AT2D14064,פ���ڲ�֧��GPRS��С����T3312��ʱû����LAU
   28.  ��    ��   : 2009��09��07��
        ��    ��   : x00115505
        �޸�����   : AT2D14252,���������У���RNCǨ�Ƶ���RNC�£�MS����RAU���̣�û������Follow-on
   29.  ��    ��   : 2010��03��15��
        ��    ��   : x00115505
        �޸�����   : AT2D17570,ĳЩ���Rau����ʱû���ϱ�EVENT�¼�
   30.  ��    ��   : 2010��04��14��
        ��    ��   : x00115505
        �޸�����   : AT2D18080,Direct Signalling Re-establish������Rau��Counterά������
*******************************************************************************/

#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasTimer.h"
#include "GmmCasSend.h"
#include "GmmCasComm.h"
#include "GmmCasSuspend.h"
#include "GmmMmInterface.h"
#include  "GmmCasGsm.h"

/* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, begin */
#include "NasComm.h"
/* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, end */

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:luojian 107747;������:sunshaohua65952;ԭ��:LOG���������Ҫ*/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_TIMER_C
/*lint +e767 �޸���:luojian 107747;������:sunshaohua*/

extern VOS_UINT32   g_ulGmmDelaySuspendRsp;

/*lint -save -e958 */

/* delete by z00234330 for PCLINT����, 2014-06-24, begin */
/* delete by z00234330 for PCLINT����, 2014-06-24, end */


/* extern VOS_UINT32 Mmc_IsPlmnSearching(VOS_VOID); */

/***********************************************************************
  Module   : Gmm_TimerStart
  Function : GMMʹ�õĶ�ʱ������
  Input    : VOS_UINT8           ucTimerId     ��ʱ��ID
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1. ��־��    2003.12.10  �°�����
     2.��    ��   : 2012��3��3��
       ��    ��   : z00161729
       �޸�����   : V7R1 C50 ֧��ISR�޸�,T3312����ֹͣ��ʱ����֪ͨL
     3.��    ��   : 2015��6��4��
       ��    ��   : z00161729
       �޸�����   : 24008 23122 R11 CR������Ŀ�޸�
     4.��    ��   : 2015��9��26��
       ��    ��   : c00318887
       �޸�����   : ��չGMM��ʱ����64��
 ************************************************************************/
VOS_VOID Gmm_TimerStart(
                    VOS_UINT8 ucTimerId                                             /* Timer ID                                 */
                    )
{
    VOS_UINT32                          ulResult;                               /* �����������TIMER�������                */

    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask     = VOS_NULL_PTR;
    VOS_UINT8                           ucTimerBitIndex;

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendMask(ucTimerId,&pulTimerSusMask, &ucTimerBitIndex);
    
    /*lint -e701*/
    if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
    /*lint +e701*/
    {                                                                           /* ��timer�Ѿ�����                          */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerStart:WARNING: This Timer has been started");
        return;                                                                 /* ����                                     */
    }

    if ((GMM_TIMER_T3302 == ucTimerId) || (GMM_TIMER_T3312 == ucTimerId))
    {                                                                           /* T3302��T3312                             */
        if (0 == g_GmmTimerMng.aTimerInf[ucTimerId].ulTimerVal)
        {                                                                       /* T3302��T3312ʱ��Ϊ0                      */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_TimerStart:NORMAL: Timer Length of T3302 or T3312 is 0");
            return;                                                             /* ����                                     */
        }
    }


    ulResult = Mm_StartRelTimer(      &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer,        /* ���TIMER ID�ĵ�ַ                       */
                                       WUEPS_PID_GMM,
                                       g_GmmTimerMng.aTimerInf[ucTimerId].ulTimerVal,     /* ʱ��                                     */
                                       (VOS_UINT32)ucTimerId,                             /* ��Ϣ���е�ID                             */
                                       g_GmmTimerMng.aTimerInf[ucTimerId].ulParam,        /* ��Ϣ��ַ                                 */
                                       g_GmmTimerMng.aTimerInf[ucTimerId].ucMode          /* ��Ϣ���ȼ�                               */
                                       );
    if (VOS_OK != ulResult)
    {                                                                                         /* ����ʧ��                                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_TimerStart:ERROR: Start timer unsuccessfully");
        return;                                                                               /* ����                                     */
    }


    /*lint -e701*/
    (*pulTimerRunMask) |= (0x00000001 << ucTimerBitIndex);                  /* ��Timer��������־                        */

    (*pulTimerSusMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);     /* ��Timer�Ĺ����־                        */
    /*lint +e701*/

    if (GMM_TIMER_T3314 == ucTimerId)
    {
        /*lint -e701*/
        if ((g_GmmTimerMng.ulTimerRunMask) & (0x00000001 << GMM_TIMER_T3312))   /*T3312��������̬*/
        /*lint +e701*/
        {
#if (FEATURE_LTE == FEATURE_ON)
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);
        }

        /* 24008_CR1735R3_(Rel-10)_C1-111529 was 1470 was 1012 24008-a10 24008 4.7.5.1.5�½���������:
        If in addition the ROUTING AREA UPDATE REQUEST message indicated "periodic updating",
        -   in Iu mode, the timer T3311 may be stopped when the MS enters PMM-CONNECTED mode;
        -   in A/Gb mode, the timer T3311 may be stopped when the READY timer is started.*/
        if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3311);
        }

        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_READY_TIMER_START,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);
    }

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerStart:INFO: StartTimer: ", ucTimerId);

}

/***********************************************************************
  Module   : Gmm_TimerStop
  Function : GMMʹ�õĶ�ʱ��ֹͣ
  Input    : VOS_UINT8           ucTimerId     ��ʱ��ID
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1.  ��־��  2003.12.10  �°�����
     2.  ��    ��   : 2006��12��07��
         ��    ��   : s46746
         �޸�����   : �������������ⵥ�ţ�A32D07799
     3.  ��    ��   : 2007��01��04��
         ��    ��   : s46746
         �޸�����   : �������������ⵥ�ţ�A32D08235
     4.  ��    ��   : 2007��3��30��
         ��    ��   : s46746
         �޸�����   : ���ⵥ��:A32D09854
     5.  ��    ��   : 2009��5��9��
         ��    ��   : l00130025
         �޸�����   : �������ⵥ�ţ�AT2D11645/AT2D11797,�ػ�����detach��EST_REQʧ�ܣ�Gmm�ᷴ������EST_REQ
     6.  ��    ��   : 2010��12��18��
         ��    ��   : o00132663
         �޸�����   : �������ⵥ�ţ����ⵥ��:DTS2010121800152,GMM�ػ��ز�����״̬����
     7.  ��    ��   : 2011��5��16��
         ��    ��   : c00173809
         �޸�����   : �������ⵥ�ţ����ⵥ��:DTS2011050905176,��֧��GPRS��С����ϵͳ��ѡ����֧��GPRS��
                      С��,�쳣ֹͣ��T3312��ʱ��.
     8.  ��    ��   : 2012��4��3��
         ��    ��   : z00161729
         �޸�����   : ֧�� ISR�޸�

  9.��    ��   : 2015��9��26��
    ��    ��   : c00318887
    �޸�����   : ��չGMM��ʱ����64��
 ************************************************************************/
VOS_VOID Gmm_TimerStop(
                   VOS_UINT8       ucTimerId                                    /* Timer ID                                 */
                   )
{
    VOS_UINT8    i;                                                             /* ����ѭ������                             */

    VOS_UINT32                         *pulTimerRunMask             = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask             = VOS_NULL_PTR;
    VOS_UINT32                         *pulTimerSuspendCtrlRunMask  = VOS_NULL_PTR;    
    VOS_UINT8                           ucTimerBitIndex;

    switch (ucTimerId)
    {                                                                           /* �ж϶�ʱ������                           */
        case GMM_TIMER_ALL:

            for (i = 0; i < GMM_TIMER_NUM; i ++)
            {
                /* �ػ�������ʱ��������ʾͣ����TIMER_ALL��ֹͣ�ö�ʱ�� */
                if ( GMM_TIMER_1S == i )
                {
                    continue;
                }

                NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
                NAS_GMM_GetTimerSuspendMask(i, &pulTimerSusMask, &ucTimerBitIndex);

                /*lint -e701*/
                if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
                /*lint +e701*/
                {                                                                   /* �ö�ʱ���Ѿ�����                         */
                    if ((GMM_TIMER_T3314 == i)
                     || (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
                    {
                        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;

                        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
                        NAS_EventReport(WUEPS_PID_GMM,
                                        NAS_OM_EVENT_READY_TIMER_STOP,
                                        VOS_NULL_PTR,
                                        NAS_OM_EVENT_NO_PARA);
                    }


                    if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                        Mm_StopRelTimer(WUEPS_PID_GMM, i, &g_GmmTimerMng.aTimerInf[i].hTimer))
                    {                                                               /* ֹͣʧ�ܣ��Ѿ�ֹͣ��Timer������          */
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerStop:WARNING: Stop all timer unsuccessfully");
                        return;                                                     /* ����                                     */
                    }
                    /*lint -e701*/
                    (*pulTimerRunMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);                  /* ��Timer��������־                        */

                    (*pulTimerSusMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);         /* ��Timer�Ĺ����־                        */
                    /*lint +e701*/
                    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerStop:INFO: StopTimer: ", i);

                }
            }
            gstGmmSuspendCtrl.ulTimerRunMask = 0x0;

            gstGmmSuspendCtrl.ulTimerRunMaskEx              = 0x0; 
                
            break;                                                                  /* ����                                     */
        case GMM_REGSTER_AND_SHUTDOWN_TIMER:
            for (i = 0; i < GMM_TIMER_NUM; i ++)
            {
                /* ��֧��GPRSʱ,����Ҫֹͣ��Щ��ʱ�� */
                if ((GMM_TIMER_1S == i) || (GMM_TIMER_T3302 == i) || (GMM_TIMER_T3311 == i)
                 || (GMM_TIMER_T3312 == i) || (GMM_TIMER_T3314 == i))
                {
                    continue;
                }

                NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
                NAS_GMM_GetTimerSuspendMask(i, &pulTimerSusMask, &ucTimerBitIndex);
                NAS_GMM_GetTimerSuspendCtrlRunMask(i, &pulTimerSuspendCtrlRunMask, &ucTimerBitIndex);
                
                /*lint -e701*/
                if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
                /*lint +e701*/
                {                                                                   /* �ö�ʱ���Ѿ�����                         */
                    if ((GMM_TIMER_T3314 == i)
                     || (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
                    {
                        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
                        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
                        NAS_EventReport(WUEPS_PID_GMM,
                                        NAS_OM_EVENT_READY_TIMER_STOP,
                                        VOS_NULL_PTR,
                                        NAS_OM_EVENT_NO_PARA);
                    }

                    if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                        Mm_StopRelTimer(WUEPS_PID_GMM, i, &g_GmmTimerMng.aTimerInf[i].hTimer))
                    {                                                               /* ֹͣʧ�ܣ��Ѿ�ֹͣ��Timer������          */
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerStop:WARNING: Stop all timer unsuccessfully");
                    }
                    /*lint -e701*/
                    (*pulTimerRunMask)              &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);          /* ��Timer��������־                        */

                    (*pulTimerSusMask)              &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);         /* ��Timer�Ĺ����־                        */
                    
                    (*pulTimerSuspendCtrlRunMask)   &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);
                    /*lint +e701*/
                    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerStop:INFO: StopTimer: ", i);

                }
            }
            break;
        case GMM_TIMER_T3312:
            /*lint -e701*/
            if (0 != (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << ucTimerId)))
            /*lint +e701*/
            {                                                                       /* Timer��������                            */
                if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                        Mm_StopRelTimer(WUEPS_PID_GMM, ucTimerId, &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer))
                {                                                                   /* ֹͣʧ�ܣ��Ѿ�ֹͣ��Timer������          */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerStop:WARNING: Stop timer unsuccessfully");
                    return;                                                         /* ����                                     */
                }
                /*lint -e701*/
                g_GmmTimerMng.ulTimerRunMask &= ~(VOS_UINT32)(0x00000001 << ucTimerId);         /* ��Timer��������־                        */

                g_GmmTimerMng.ulTimerSusMask &= ~(VOS_UINT32)(0x00000001 << ucTimerId); /* ��Timer�Ĺ����־                        */
                /*lint +e701*/
                PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerStop:INFO: StopTimer: ", ucTimerId);

            }
            break;

        case GMM_TIMER_ALL_EXCEPT_T3312_T3323_T3302:

           for (i = 0; i < GMM_TIMER_NUM; i ++)
           {
               if ((GMM_TIMER_1S == i )
                || (GMM_TIMER_T3312 == i)
                || (GMM_TIMER_T3323 == i)
                || (GMM_TIMER_T3302 == i))
               {
                   continue;
               }

               NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
               NAS_GMM_GetTimerSuspendMask(i, &pulTimerSusMask, &ucTimerBitIndex);

               /*lint -e701*/
               if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
               /*lint +e701*/
               {                                                                   /* �ö�ʱ���Ѿ�����                         */
                   if ((GMM_TIMER_T3314 == i)
                    || (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
                   {
                       gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;

                       NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
                       NAS_EventReport(WUEPS_PID_GMM,
                                       NAS_OM_EVENT_READY_TIMER_STOP,
                                       VOS_NULL_PTR,
                                       NAS_OM_EVENT_NO_PARA);
                   }


                   if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                       Mm_StopRelTimer(WUEPS_PID_GMM, i, &g_GmmTimerMng.aTimerInf[i].hTimer))
                   {                                                               /* ֹͣʧ�ܣ��Ѿ�ֹͣ��Timer������          */
                       PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerStop:WARNING: Stop all timer unsuccessfully");
                       return;                                                     /* ����                                     */
                   }
                   /*lint -e701*/
                   (*pulTimerRunMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);          /* ��Timer��������־                        */

                   (*pulTimerSusMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);         /* ��Timer�Ĺ����־                        */
                   /*lint +e701*/
                   PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerStop:INFO: StopTimer: ", i);

               }
           }
           gstGmmSuspendCtrl.ulTimerRunMask = 0x0;
           gstGmmSuspendCtrl.ulTimerRunMaskEx              = 0x0;
           
           break;

        default:                                                                    /* �������                                 */
            NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
            NAS_GMM_GetTimerSuspendMask(ucTimerId, &pulTimerSusMask, &ucTimerBitIndex);
            
            /*lint -e701*/
            if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
            /*lint +e701*/
            {                                                                       /* Timer��������                            */
                if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                        Mm_StopRelTimer(WUEPS_PID_GMM, ucTimerId, &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer))
                {                                                                   /* ֹͣʧ�ܣ��Ѿ�ֹͣ��Timer������          */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerStop:WARNING: Stop timer unsuccessfully");
                    return;                                                         /* ����                                     */
                }
                /*lint -e701*/
                (*pulTimerRunMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);                  /* ��Timer��������־                        */

                (*pulTimerSusMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);     /* ��Timer�Ĺ����־                        */
                /*lint +e701*/
                PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerStop:INFO: StopTimer: ", ucTimerId);
                if (GMM_TIMER_T3314 == ucTimerId)
                {
                    NAS_EventReport(WUEPS_PID_GMM,
                                    NAS_OM_EVENT_READY_TIMER_STOP,
                                    VOS_NULL_PTR,
                                    NAS_OM_EVENT_NO_PARA);
                }

            }
            break;                                                                  /* ����                                     */
    }
    return;                                                                     /* ����                                     */
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsTimerIdInTimerList
 ��������  : �ж�ĳ����ʱ���Ƿ��ڶ�ʱ��������
 �������  : ucTimerId   �ض���ʱ��
             ucTimerNum  ��ʱ������
             pucTimer    ��ʱ������
 �������  : ��
 �� �� ֵ  : VOS_TRUE  ��ʾ�ڸ�������
             VOS_FALSE ��ʾ���ڸ�������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��6��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsTimerIdInTimerList(
    VOS_UINT8                           ucTimerId,
    VOS_UINT8                           ucTimerNum,
    VOS_UINT8                          *pucTimer
)
{
    VOS_UINT8                           ucIndex;

    for ( ucIndex = 0 ; ucIndex < ucTimerNum; ucIndex++ )
    {
        if ( ucTimerId == *(pucTimer + ucIndex) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_TimerStopExceptSpecialTimers
 ��������  : GMMģ��ֹͣ���г��ض���ʱ��������ж�ʱ��
 �������  : ucTimerNum  ��ʱ������
             pucTimer    ��ʱ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��6��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��9��26��
    ��    ��   : c00318887
    �޸�����   : ��չGMM��ʱ����64��
*****************************************************************************/
VOS_VOID NAS_GMM_TimerStopExceptSpecialTimers(
    VOS_UINT8                           ucTimerNum,
    VOS_UINT8                          *pucTimer
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucTotalTimerNum;

    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask     = VOS_NULL_PTR;
    VOS_UINT8                           ucTimerBitIndex;

    ucTotalTimerNum = ucTimerNum;

    if (ucTotalTimerNum > GMM_TIMER_NUM)
    {
        ucTotalTimerNum = GMM_TIMER_NUM;
    }

    for (i = 0; i < GMM_TIMER_NUM; i ++)
    {
        if ( VOS_TRUE == NAS_GMM_IsTimerIdInTimerList(i, ucTotalTimerNum, pucTimer) )
        {
            continue;
        }

        NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
        NAS_GMM_GetTimerSuspendMask(i, &pulTimerSusMask, &ucTimerBitIndex);

        /*lint -e701*/
        if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
        /*lint +e701*/
        {                                                                   /* �ö�ʱ���Ѿ�����                         */
            if ((GMM_TIMER_T3314 == i)
             || (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
            {
                gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;

                NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
                NAS_EventReport(WUEPS_PID_GMM,
                                NAS_OM_EVENT_READY_TIMER_STOP,
                                VOS_NULL_PTR,
                                NAS_OM_EVENT_NO_PARA);
            }


            if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                Mm_StopRelTimer(WUEPS_PID_GMM, i, &g_GmmTimerMng.aTimerInf[i].hTimer))
            {                                                               /* ֹͣʧ�ܣ��Ѿ�ֹͣ��Timer������          */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_TimerStopExceptSpecialTimers:WARNING: Stop all timer unsuccessfully");
                return;                                                     /* ����                                     */
            }
            /*lint -e701*/
            (*pulTimerRunMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);             /* ��Timer��������־                        */

            (*pulTimerSusMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);             /* ��Timer�Ĺ����־                        */
            /*lint +e701*/
            PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_GMM_TimerStopExceptSpecialTimers:INFO: StopTimer: ", i);

        }
    }

    gstGmmSuspendCtrl.ulTimerRunMask    = 0x0;
    gstGmmSuspendCtrl.ulTimerRunMaskEx  = 0x0;
}

/***********************************************************************
  Module   : Gmm_TimerPause
  Function : GMMʹ�õĶ�ʱ����ͣ
  Input    : VOS_UINT8           ucTimerId     ��ʱ��ID
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1. ��־��  2003.12.10  �°�����

  2.��    ��   : 2015��9��26��
    ��    ��   : c00318887
    �޸�����   : ��չGMM��ʱ����64��
 ************************************************************************/
VOS_VOID Gmm_TimerPause(
                    VOS_UINT8                   ucTimerId                           /* Timer ID                                 */
                    )
{
    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask     = VOS_NULL_PTR;
    VOS_UINT8                           ucTimerBitIndex;

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendMask(ucTimerId, &pulTimerSusMask, &ucTimerBitIndex);
    

    /*lint -e701*/
    if (0 != ( (*pulTimerRunMask) & ( 0x00000001 << ucTimerBitIndex)))
    /*lint +e701*/
    {                                                                           /* ��timer�Ѿ�����                          */


        if( VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                    Mm_StopRelTimer(WUEPS_PID_GMM, ucTimerId, &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer))
        {                                                                       /* ��ͣʧ��                                 */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerPause:WARNING: Stop timer unsuccessfully");
            return;                                                             /* ����                                     */
        }
        /*lint -e701*/
        (*pulTimerSusMask) |= (0x00000001 << ucTimerBitIndex);              /* ����Timer�Ĺ����־                      */
        /*lint +e701*/
    }
    else
    {                                                                           /* ��timerδ����                            */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerPause:WARNING: Timer is not running");
        return;                                                                 /* ����                                     */
    }
}

/***********************************************************************
  Module   : Gmm_TimerResume
  Function : GMMʹ�õ���ͣ��Ķ�ʱ���Ļָ�
  Input    : VOS_UINT8           ucTimerId     ��ʱ��ID
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1.  ��־��  2003.12.10  �°�����

  2.��    ��   : 2015��9��26��
    ��    ��   : c00318887
    �޸�����   : ��չGMM��ʱ����64��
 ************************************************************************/
VOS_VOID Gmm_TimerResume (
                      VOS_UINT8                   ucTimerId                         /* Timer ID                                 */
                      )
{
    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask     = VOS_NULL_PTR;
    VOS_UINT8                           ucTimerBitIndex;

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendMask(ucTimerId, &pulTimerSusMask, &ucTimerBitIndex);

    /*lint -e701*/
    if (0 != ( (*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
    {                                                                           /* ��timer����                              */
        if (0 == ((*pulTimerSusMask) & (0x00000001 << ucTimerBitIndex)))
        {                                                                       /* ��Timerδ������                          */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerResume:WARNING: This timer has been Stoped");
            return;                                                             /* ����                                     */
        }


        if (VOS_OK != Mm_StartRelTimer(   &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer,     /* ���TIMER ID�ĵ�ַ                       */
                                           WUEPS_PID_GMM,
                                           g_GmmTimerMng.aTimerInf[ucTimerId].ulTimerVal,         /* ʱ��                                     */
                                           (VOS_UINT32)ucTimerId,            /* ��Ϣ���е�ID                             */
                                           g_GmmTimerMng.aTimerInf[ucTimerId].ulParam,               /* ��Ϣ��ַ                                 */
                                           g_GmmTimerMng.aTimerInf[ucTimerId].ucMode          /* ��Ϣ���ȼ�                               */
                                           ))
        {                                                                       /* �ָ�ʧ��                                 */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerResume:WARNING: Start timer unsuccessfully");
            return;                                                             /* ����                                     */
        }

        NAS_NORMAL_LOG1(WUEPS_PID_GMM, "Gmm_TimerResume: Timer resumed, ucTimerId =", ucTimerId);

        (*pulTimerSusMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);     /* ��Timer�Ĺ����־                        */
    }
    else
    {                                                                           /* ��timerδ����                            */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerResume:WARNING: Timer is not running");
        return;                                                                 /* ����                                     */
    }
    /*lint +e701*/
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_QryTimerStatus
 ��������  : ��ѯָ����GMM��ʱ����״̬�Լ�ʣ��ʱ��
 �������  : ucTimerId  - ��Ҫ��ѯ�Ķ�ʱ��ID
 �������  : pusLeftLen - ��ʱ����ʣ��ʱ��
 �� �� ֵ  : VOS_TRUE - ��ʱ��������
             VOS_FALSE - ��ʱ����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��27��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��30��
    ��    ��   : l00130025
    �޸�����   : DTS2012010500368,����ͬ���ӿ�VOS_GetRelTmRemainTimehTimerʱû���ж�hTimer�Ƿ�Ϊ0���붨ʱ���첽��Ϣ��ͻ�����쳣��ӡ

  3.��    ��   : 2015��9��26��
    ��    ��   : c00318887
    �޸�����   : ��չGMM��ʱ����64��
*****************************************************************************/
VOS_UINT32  NAS_GMM_QryTimerStatus(VOS_UINT8 ucTimerId)
{
    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT8                           ucTimerBitIndex;

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);

    /*lint -e701*/
    if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
    /*lint +e701*/
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsTimerNeedSuspend
 ��������  : �ж϶�ʱ���Ƿ���Ҫ������
 �������  : ucTimerId  - ��Ҫ��ѯ�Ķ�ʱ��ID
 �������  : 
 �� �� ֵ  : VOS_TRUE - ��Ҫ������
             VOS_FALSE - ����Ҫ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��3��1��
    ��    ��   : z00359541
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsTimerNeedSuspend(
    VOS_UINT8                           ucTimerId
)
{
    VOS_UINT32                          ulSuspendFlg;

    ulSuspendFlg = VOS_TRUE;

    /* ���¶�ʱ�����յ�������Ϣʱ����Ҫ������ */
    switch (ucTimerId)
    {
        case GMM_TIMER_T3312:
            ulSuspendFlg = VOS_FALSE;
            break;

        case GMM_TIMER_T3314:
            ulSuspendFlg = VOS_FALSE;
            break;

        case GMM_TIMER_1S:
            ulSuspendFlg = VOS_FALSE;
            break;

        case GMM_TIMER_T3323:
            ulSuspendFlg = VOS_FALSE;
            break;

        case GMM_TIMER_T3302:
            ulSuspendFlg = VOS_FALSE;
            break;

        default:
            ulSuspendFlg = VOS_TRUE;
            break;
    }

    return ulSuspendFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsTimerNeedResume
 ��������  : �ж϶�ʱ���Ƿ���Ҫ���ָ�
 �������  : ucTimerId  - ��Ҫ��ѯ�Ķ�ʱ��ID
 �������  : 
 �� �� ֵ  : VOS_TRUE - ��Ҫ���ָ�
             VOS_FALSE - ����Ҫ���ָ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��3��15��
    ��    ��   : z00359541
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsTimerNeedResume(
    VOS_UINT8                           ucTimerId
)
{
    VOS_UINT32                          ulResumeFlg;

    ulResumeFlg = VOS_TRUE;

    /* ���¶�ʱ�����յ�������Ϣʱ����Ҫ������ */
    switch (ucTimerId)
    {
        case GMM_TIMER_T3312:
            ulResumeFlg = VOS_FALSE;
            break;

        case GMM_TIMER_T3314:
            ulResumeFlg = VOS_FALSE;
            break;

        case GMM_TIMER_SUSPENDED:
            ulResumeFlg = VOS_FALSE;
            break;

        case GMM_TIMER_T3302:
            ulResumeFlg = VOS_FALSE;
            break;

        default:
            ulResumeFlg = VOS_TRUE;
            break;
    }

    return ulResumeFlg;
}


/***********************************************************************
  Module   : Gmm_SuspendTimer
  Function : GMMʹ�õĶ�ʱ����ͣ
  Input    : VOS_UINT8           ucTimerId     ��ʱ��ID
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1. s46746  2006.05.07  �°�����
     2. ��    ��   : 2007��11��12��
        ��    ��   : l39007
        �޸�����   : �������ⵥA32D13044
     3. ��    ��   : 2014��3��13��
        ��    ��   : w00176964
        �޸�����   : DTS2014031207844:SYSCFG����detach��ֹͣdetach��ʱ��
     4.��    ��   :2014��4��2��
       ��    ��   :w00242748
       �޸�����   :DTS2014040310584:LTE��δ�����罻����ATTACH/TAU����ֹͣT3211/T3212/T3213;
                   ֻ�������罻���󣬲Ž�T3211/T3212/T3213ֹͣ��
     5.��    ��   : 2015��4��15��
       ��    ��   : y00245242
       �޸�����   : iteration 13����
      6.��    ��   : 2015��9��26��
        ��    ��   : c00318887
        �޸�����   : ��չGMM��ʱ����64��
     7.��    ��   : 2016��3��1��
       ��    ��   : z00359541
       �޸�����   : DTS2016022908722: �յ�������Ϣʱ����ֹͣT3302��ʱ��
 ************************************************************************/
VOS_VOID GMM_SuspendTimer(VOS_VOID)
{
    VOS_UINT8 i;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT8                           ucTimerBitIndex;

    enCurRat = NAS_MML_GetCurrNetRatType();

    gstGmmSuspendCtrl.ulTimerRunMask    = g_GmmTimerMng.ulTimerRunMask;
    gstGmmSuspendCtrl.ulTimerRunMaskEx  = g_GmmTimerMng.ulTimerRunMaskEx;
        

    for (i = 0; i < GMM_TIMER_NUM; i ++)
    {
        if (VOS_FALSE == NAS_GMM_IsTimerNeedSuspend(i))
        {
            NAS_NORMAL_LOG1(WUEPS_PID_GMM, "GMM_SuspendTimer: Timer should not be suspended, ucTimerId =", i);
            continue;
        }

        NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
        
        /*lint -e701*/
        if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
        /*lint +e701*/
        {
            /* MMAͨ��SYSCFGEX����detach��attach���̣����detach����������δ��Ӧʱ,
               ��ʱ����һ���µ�LA��RA��Ҫ����LAU/RAUʱ,���ⷴ����GPRS�����ӳ�MMA�ȴ�
               detach�ظ���ʱ��,����MMA��detach��ʱ����attach��GMM��detach��ʱ����ʱ
               ��������detach,��ʱ��ֹͣGMM������detach��ʱ��,��ʱ��ֱ�ӽ��б���detach
            */
            if ((VOS_TRUE                    == g_GmmDetachCtrl.ucSysCfgDetachFlg)
             && (GMM_TIMER_PROTECT_PS_DETACH == i)
             && (NAS_MML_NET_RAT_TYPE_GSM    == enCurRat))
            {
                NAS_NORMAL_LOG(WUEPS_PID_GMM, "GMM_SuspendTimer: GMM_TIMER_PROTECT_PS_DETACH should not be suspended");
                continue;
            }

            GMM_SuspendSingleTimer(i);
            /*g_GmmTimerMng.ulTimerRunMask &= ~(VOS_UINT32)(0x00000001 << i);*/
        }
    }

}

/***********************************************************************
  Module   : Gmm_SuspendTimer
  Function : GMMʹ�õĶ�ʱ����ͣ
  Input    : VOS_UINT8           ucTimerId     ��ʱ��ID
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1. s46746  2006.05.07  �°�����
     2. ��    ��   : 2007��11��12��
        ��    ��   : l39007
        �޸�����   : �������ⵥA32D13044
     3. ��    ��   : 2012��1��30��
        ��    ��   : l00130025
        �޸�����   : DTS2012010500368,����ͬ���ӿ�VOS_GetRelTmRemainTimehTimerʱû���ж�hTimer�Ƿ�Ϊ0���붨ʱ���첽��Ϣ��ͻ�����쳣��ӡ
 ************************************************************************/
VOS_VOID GMM_SuspendSingleTimer(VOS_UINT8 ucTimerId)
{
    VOS_UINT32                          ulRet;


    if (VOS_NULL_PTR != g_GmmTimerMng.aTimerInf[ucTimerId].hTimer)
    {
        ulRet = VOS_GetRelTmRemainTime(&(g_GmmTimerMng.aTimerInf[ucTimerId].hTimer),
                                       &gstGmmSuspendCtrl.ulTimerValue[ucTimerId]);
        if (VOS_OK != ulRet)
        {
            gstGmmSuspendCtrl.ulTimerValue[ucTimerId] = MM_EXTRA_DELAY_TIME_LEN;
        }
        else
        {
            gstGmmSuspendCtrl.ulTimerValue[ucTimerId] = gstGmmSuspendCtrl.ulTimerValue[ucTimerId]*MM_TIMER_TICK;
            Gmm_TimerStop(ucTimerId);
        }
    }
    else
    {
        /*  g_GmmTimerMng.aTimerInf[ucTimerId].hTimer Ϊ��ʱ��˵���˶�ʱ���ѳ�ʱ��ֹͣ */
        gstGmmSuspendCtrl.ulTimerValue[ucTimerId] = MM_EXTRA_DELAY_TIME_LEN;
    }


    return;
}

/***********************************************************************
  Module   : Gmm_ResumeTimer
  Function : GMM��ʱ���ָ�
  Input    : VOS_UINT8           ucTimerId     ��ʱ��ID
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1. s46746  2006.05.07  �°�����
     2. ��    ��   : 2013��2��4��
        ��    ��   : w00176964
        �޸�����   : DTS2011082402748:EST CNF fail����CCO����ʱ,3311����Ҫ�ָ�����
     3. ��    ��   : 2014��3��13��
        ��    ��   : w00176964
        �޸�����   : DTS2014031207844:SYSCFG����detach��ֹͣdetach��ʱ��
      4.��    ��   : 2015��9��26��
        ��    ��   : c00318887
        �޸�����   : ��չGMM��ʱ����64��
 ************************************************************************/
VOS_VOID GMM_ResumeTimer(VOS_UINT8 ucResume)
{
    VOS_UINT8                           i;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    VOS_UINT32                         *pulTimerSuspendRunMask      = VOS_NULL_PTR;
    VOS_UINT32                         *pulTimerRunMask             = VOS_NULL_PTR;  
    VOS_UINT8                           ucTimerBitIndex;

    enCurRat = NAS_MML_GetCurrNetRatType();

    if (GMM_TIMER_NOT_RESUME == ucResume)
    {
        NAS_NORMAL_LOG(WUEPS_PID_GMM, "GMM_ResumeTimer: No need to resume GMM timer");

        gstGmmSuspendCtrl.ulTimerRunMask                    = 0x0;

        gstGmmSuspendCtrl.ulTimerRunMaskEx                  = 0x0;
        
        return;
    }

    for (i = 0; i < GMM_TIMER_NUM; i ++)
    {
        if (VOS_FALSE == NAS_GMM_IsTimerNeedResume(i))
        {
            NAS_NORMAL_LOG1(WUEPS_PID_GMM, "GMM_ResumeTimer: Timer should not be resumed, ucTimerId =", i);
            continue;
        }

        /* CCO����EST CNF fail���µĻ���,3311ͨ�����ݻ��ƻָ����� */
        if ((gstGmmSuspendCtrl.ucPreRat != NAS_MML_GetCurrNetRatType())
         && (MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK == gstGmmSuspendCtrl.ucSuspendCause)
         && (GMM_TIMER_T3311 == i)
         && (GMM_GPRS_SUSPENSION != g_GmmGlobalCtrl.ucState)
         && (GMM_SUSPENDED_WAIT_FOR_SYSINFO != g_GmmGlobalCtrl.ucState))
        {
            continue;
        }

        NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
        NAS_GMM_GetTimerSuspendCtrlRunMask(i, &pulTimerSuspendRunMask, &ucTimerBitIndex);
        
        /*lint -e701*/
        if (0 != ((*pulTimerSuspendRunMask) & (0x00000001 << ucTimerBitIndex)))
        /*lint +e701*/
        {
            /* MMAͨ��SYSCFGEX����detach��attach���̣����detach����������δ��Ӧʱ,
               ��ʱ����һ���µ�LA��RA��Ҫ����LAU/RAUʱ,���ⷴ����GPRS�����ӳ�MMA�ȴ�
               detach�ظ���ʱ��,����MMA��detach��ʱ����attach��GMM��detach��ʱ����ʱ
               ��������detach,��ʱ��ֹͣGMM������detach��ʱ��,��ʱ��ֱ�ӽ��б���detach
            */
            if ((VOS_TRUE                    == g_GmmDetachCtrl.ucSysCfgDetachFlg)
             && (GMM_TIMER_PROTECT_PS_DETACH == i)
             && (NAS_MML_NET_RAT_TYPE_GSM    == enCurRat))
            {
                continue;
            }

            /* ������ʱ��ʱ���ж�ʣ��ʱ���Ƿ�Ϊ0����������ʱ��0��Ķ�ʱ�� */
            if (0 != gstGmmSuspendCtrl.ulTimerValue[i])
            {
                if (VOS_OK != Mm_StartRelTimer(&g_GmmTimerMng.aTimerInf[i].hTimer,
                                                WUEPS_PID_GMM,
                                                gstGmmSuspendCtrl.ulTimerValue[i],
                                                (VOS_UINT32)i,
                                                g_GmmTimerMng.aTimerInf[i].ulParam,
                                                VOS_RELTIMER_NOLOOP))
                {
                    GMM_LOG_WARN("Gmm_ResumeTimer:Resume some timer fail.");
                }
                else
                {
                    /*lint -e701*/
                    (*pulTimerRunMask) |= (0x00000001 << ucTimerBitIndex);
                    /*lint +e701*/
                
                    NAS_NORMAL_LOG1(WUEPS_PID_GMM, "GMM_ResumeTimer: GMM Timer resumed, TimerId =", i);
                }
            }
            else
            {
                NAS_WARNING_LOG1(WUEPS_PID_GMM, "GMM_ResumeTimer: WARNING: resume timer len is 0", i);
            }
        }
    }
    gstGmmSuspendCtrl.ulTimerRunMask = 0x0;
    gstGmmSuspendCtrl.ulTimerRunMaskEx = 0x0;
}


/***********************************************************************
  Module   : Gmm_Tim3302Expired
  Function : ��ʱ��T3302�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1. ��־��  2003.12.10  �°�����
     2.��    ��   : 2012��2��15��
       ��    ��   : w00166186
       �޸�����   : CSFB&PPAC&ETWS&ISR ����
     3.��    ��   : 2013��7��19��
       ��    ��   : w00167002
       �޸�����   : DTS2013071900239:W������ģʽI,����ע��PS only�ɹ���CSʧ��ԭ��
                    #17,����ģʽ��I--->II,��ʱ��Ӧ��������ATTACH.
                    �����ʱ��Ȼ������ģʽI,���û�����ΪPS ONLY,��Ҳ���÷���
                    ����ATTACH.
     4.��    ��   : 2015��1��5��
       ��    ��   : z00161729
       �޸�����   : AT&T ֧��DAM�����޸�
 ************************************************************************/
VOS_VOID Gmm_Tim3302Expired(VOS_VOID)
{
    VOS_UINT8                           ucCsRestrictionFlg;
    VOS_UINT8                           ucPsRestrictionFlg;

    /* ��ǰפ����LTE,������ */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        return;
    }

    ucCsRestrictionFlg  = NAS_MML_GetCsRestrictRegisterFlg();
    ucPsRestrictionFlg  = NAS_MML_GetPsRestrictRegisterFlg();
    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* �ж�GMM��ǰ״̬                          */
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:

        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                                  /* attach attempt counter��0                */

        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* ���ú�������ATTACH����                   */
        break;                                                                  /* ����                                     */
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:

        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter ��0                  */

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ���ú�������RAU����                      */
        break;                                                                  /* ����                                     */
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:


        /* �����ǰֻ��PS ONLY�� ��������ģʽII,����Ҫ��������ATTACH */
        if ((VOS_TRUE       == NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm())
         && (GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
         && (GMM_NET_MODE_I  == g_GmmGlobalCtrl.SysInfo.ucNetMod))

        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH); /* ���ú�������RAU����                      */
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* ���ú�������RAU����                      */
        }
        break;                                                                  /* ����                                     */
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_REGISTERED_UPDATE_NEEDED:
        if (  (VOS_TRUE == ucPsRestrictionFlg)
            &&(VOS_FALSE == ucCsRestrictionFlg)
            &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3302_EXPIRED);          /* ֪ͨMM����LU                             */
        }
        break;                                                                  /* ����                                     */
    default:                                                                    /* �������                                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_Tim3302Expired:WARNING: g_GmmGlobalCtrl.ucState is Abnormal");
        break;                                                                  /* ����                                     */
    }
}

/***********************************************************************
  Module   : Gmm_Tim3310Expired
  Function : ��ʱ��T3310�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��    2003.12.10  �°�����

  2.��    ��   : 2009��5��7��
    ��    ��   : l00130025
    �޸�����   : �������ⵥ�ţ�AT2D11692/At2D11768,HPlmnTIMER��T3310,T3311ͬʱ��ʱ�Ĵ���

  3.��    ��   : 2009��09��25��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:AT2D14675,RAU/Attach�����У�list����ʧ��

  4.��    ��   : 2010��7��21��
    ��    ��   : ŷ����
    �޸�����   : DTS2010071500036,��ATTACH��RAUʧ�ܺ�δ֪ͨLL�����������
                 ������UE��Ȼ�ڷ����ط�����
  5.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  6.��    ��   : 2011��11��8��
    ��    ��   : s46746
    �޸�����   : V7R1 PhaseII�׶ν���ػ�������
  7.��    ��   : 2011��12��24��
    ��    ��   : w00166186
    �޸�����   : DTS2011122104474,ָ��������ͣLAU����ͳһ�޸�
  8.��    ��   : 2012��08��24��
    ��    ��   : m00217266
    �޸�����   : �޸�Gmm_SndSmEstablishCnf�ӿڣ����ԭ��ֵ
  9.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
 10.��    ��   : 2014��05��22��
    ��    ��   : W00242748
    �޸�����   : DTS2014050900899:��GMM�Ĵ���״̬֪ͨ��WAS
 11.��    ��   : 2015��4��21��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
************************************************************************/
VOS_VOID Gmm_Tim3310Expired(VOS_VOID)
{
    NAS_MSG_STRU                    *pNasMsg = VOS_NULL_PTR ;
    VOS_UINT8                        ucAttachType;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    enCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;

    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    /* �����ǰ���뼼����G����GAS����GRRGMM_GPRS_PROC_IND,����ΪATTACH,��־ΪFINISH */
    if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
      || (NAS_MML_NET_RAT_TYPE_WCDMA== enCurRat))
    {
        NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_ATTACH, RRMM_GMM_PROC_FLAG_FINISH);

        NAS_MML_SetGmmProcType(NAS_MML_GMM_PROC_TYPE_ATTACH);
        NAS_MML_SetGmmProcFlag(NAS_MML_GMM_PROC_FLAG_FINISH);
    }
    /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* �ж�GMM״̬��GMM_REGISTERED_INITIATED    */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_SIGNALLING);
        }

        g_GmmAttachCtrl.ucT3310outCnt++;                                        /* ����T3310���������1                     */
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* ���ԭ��ȴ���־                         */
        }

        if (g_GmmAttachCtrl.ucT3310outCnt < GMM_TIMER_EXPIRED_MAX_CNT)
        {                                                                       /* �ж�ucT3310OutCnt С�� 5                 */

            /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
            /* �����ǰ���뼼����G����GAS����GRRGMM_GPRS_PROC_IND,����ΪATTACH,��־ΪSTART */
            if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
              || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
            {
                NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_ATTACH, RRMM_GMM_PROC_FLAG_START);

                NAS_MML_SetGmmProcType(NAS_MML_GMM_PROC_TYPE_ATTACH);
                NAS_MML_SetGmmProcFlag(NAS_MML_GMM_PROC_FLAG_START);
            }
            /* Modified by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

#if (FEATURE_ON == FEATURE_DSDS)

            if (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
            {
                NAS_GMM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_PS_ATTACH);
                NAS_GMM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_PS_ATTACH);
            }
#endif

            pNasMsg = Gmm_AttachRequestMsgMake();                               /* ���ú��������տ���Ϣattach request       */

            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);              /* ʹ��RRMM_DATA_REQԭ�﷢��attach request  */
            Gmm_TimerStart(GMM_TIMER_T3310);                                    /* �˺����ڣ����ж�Timer�Ƿ����С���������
                                                                                 * �У���������                             */


            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                         GMM_MMC_ACTION_RESULT_FAILURE,
                                         enCause);

            if ((GMM_ATTACH_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc)
              || (GMM_ATTACH_NORMAL       == g_GmmGlobalCtrl.ucSpecProc))
            {
                ucAttachType = NAS_OM_GMM_GPRS_ATTACH;
            }
            else if (GMM_ATTACH_WHILE_IMSI_ATTACHED == g_GmmGlobalCtrl.ucSpecProc)
            {
                ucAttachType = NAS_OM_GMM_COMBINED_GPRS_IMSI_ATTACH;

                NAS_GMM_SndMmCombinedAttachRejected(enCause);

                NAS_GMM_SndMmCombinedRauInitiation();

            }
            else
            {
                ucAttachType = NAS_OM_GMM_COMBINED_GPRS_IMSI_ATTACH;

                NAS_GMM_SndMmCombinedAttachRejected(enCause);

                NAS_GMM_SndMmCombinedRauInitiation();

            }
            NAS_EventReport(WUEPS_PID_GMM,
                            NAS_OM_EVENT_ATTACH_REQ,
                            (VOS_VOID *)&ucAttachType,
                            NAS_OM_EVENT_ATTACH_REQ_LEN);


        }
        else
        {                                                                       /* �ж�ucT3310OutCnt ���� 5                 */
            g_GmmAttachCtrl.ucT3310outCnt = 0;                                  /* ����T3310���������0                     */
            g_GmmAttachCtrl.ucRetryFlg = GMM_FALSE;                             /* ���û�С��������attach��־               */
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                          /* ���followon��־                         */
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

            if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
            {                                                                   /* ATTACH��������SM������                   */
                Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_T3310_EXPIRED);/* ֪ͨSM GMMע��ʧ��                       */
                g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                         /* ��ucSmCnfFlg��־                         */
            }
            if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
             && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
            {
                Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
                NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);

                Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);

                if ((GMM_ATTACH_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc)
                    || (GMM_ATTACH_NORMAL       == g_GmmGlobalCtrl.ucSpecProc))
                {
                    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                                    enCause);
                }
                else
                {
                    NAS_GMM_SndMmCombinedAttachRejected(enCause);
                }


                /* ��MMC����PSע���� */
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                             GMM_MMC_ACTION_RESULT_FAILURE,
                                             enCause);

                /* �¼��ϱ� */
                NAS_EventReport(WUEPS_PID_GMM,
                                NAS_OM_EVENT_ATTACH_FAIL,
                                &enCause,
                                NAS_OM_EVENT_ATTACH_FAIL_LEN
                                );

            }
            else
            {
                Gmm_AttachAttemptCounter(NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);           /* ���ú�������T3310������                */
            }
            g_GmmGlobalCtrl.ucSpecProc    = GMM_NULL_PROCEDURE;                 /* ������ڽ��е�specific���̱�־           */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_Tim3310Expired:INFO: specific procedure ended");
        }
    }
    return;                                                                     /* ����                                     */
}

/***********************************************************************
  Module   : Gmm_Tim3311Expired
  Function : ��ʱ��T3311�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1.  ��־��  2003.12.10  �°�����
     2.  ��    ��   : 2009��5��7��
         ��    ��   : l00130025
         �޸�����   : �������ⵥ�ţ�AT2D11692/At2D11768,HPlmnTIMER��T3310,T3311ͬʱ��ʱ�Ĵ���
     3.  ��    ��   : 2011��04��02��
         ��    ��   : f00179208
         �޸�����   : �������ⵥ�ţ�DTS2011032604117,������RAU����ʧ�ܺ�û���ٷ���������RAU
     4.  ��    ��   : 2013��06��18��
         ��    ��   : l65478
         �޸�����   : ���ⵥ�ţ�DTS2013061406222,T3311��ʱʱ,����RAUʱӦ���ж� CS��ҵ��״̬

     5.��    ��   : 2013��7��19��
       ��    ��   : w00167002
       �޸�����   : DTS2013071900239:W������ģʽI,����ע��PS only�ɹ���CSʧ��ԭ��
                    #17,����ģʽ��I--->II,��ʱ��Ӧ��������ATTACH.
                    �����ʱ��Ȼ������ģʽI,���û�����ΪPS ONLY,��Ҳ���÷���
                    ����ATTACH.
     6.��    ��   : 2014��6��17��
       ��    ��   : s00217060
       �޸�����   : DTS2014061003286:��¼T3311��ʱ��־����GMM_REGISTERED_NO_CELL_AVAILABLE/
                    GMM_REGISTERED_PLMN_SEARCH�յ�ϵͳ��Ϣʱ��RAU
***********************************************************************/
VOS_VOID Gmm_Tim3311Expired(VOS_VOID)
{
    VOS_UINT8                           ucCsRestrictionFlg;
    VOS_UINT8                           ucPsRestrictionFlg;

    ucCsRestrictionFlg  = NAS_MML_GetCsRestrictRegisterFlg();
    ucPsRestrictionFlg  = NAS_MML_GetPsRestrictRegisterFlg();

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* �ж�GMM��ǰ״̬                          */
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* ���ú�������ATTACH����                   */
        break;                                                                  /* ����                                     */
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_NORMAL_SERVICE:
        if ((GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
         && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);            /* ���ú�������������RAU����                      */
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);       /* ���ú�������RAU����                      */
        }
        break;                                                                  /* ����                                     */
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
        /*Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);*/           /* ���ú�������RAU����                      */


        /* �����ǰֻ��PS ONLY�� ��������ģʽII,����Ҫ��������ATTACH */
        if ( VOS_TRUE == NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm() )
        {

            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }

        break;                                                                  /* ����                                     */
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_REGISTERED_UPDATE_NEEDED:
        /* ��¼T3311��ʱ��־����GMM_REGISTERED_NO_CELL_AVAILABLE״̬�յ�ϵͳ��Ϣ֮�󴥷�RAU */
        g_GmmRauCtrl.ucT3311ExpiredFlg = GMM_TRUE;

        if (  (VOS_TRUE == ucPsRestrictionFlg)
            &&(VOS_FALSE == ucCsRestrictionFlg)
            &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3311_EXPIRED);          /* ֪ͨMM����LU                             */
        }
        break;                                                                  /* ����                                     */
    default:                                                                    /* �������                                 */

        /* ��¼T3311��ʱ��־����GMM_REGISTERED_PLMN_SEARCH״̬�յ�ϵͳ��Ϣ֮�󴥷�RAU */
        g_GmmRauCtrl.ucT3311ExpiredFlg = GMM_TRUE;

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_Tim3311Expired:WARNING: g_GmmGlobalCtrl.ucState is Abnormal");
        break;                                                                  /* ����                                     */
    }
}

/***********************************************************************
  Module   : Gmm_Tim3312Expired
  Function : ��ʱ��T3312�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1.  ��־��  2003.12.10  �°�����
     2. ��    ��   : 2007��05��11��
        ��    ��   : luojian id:60022475
        �޸�����   : ���ⵥ��:A32D10713
     3. ��    ��   : 2007��7��14��
        ��    ��   : luojian id:60022475
        �޸�����   : �������ⵥ�ţ�A32D12438
     4. ��    ��   : 2012��2��15��
        ��    ��   : w00166186
        �޸�����   : CSFB&PPAC&ETWS&ISR ����
     5. ��    ��   : 2012��3��3��
        ��    ��   : z00161729
        �޸�����   : V7R1 C50 ֧��ISR�޸�,T3312����ֹͣ��ʱ����֪ͨL
     6. ��    ��   : 2012��5��7��
        ��    ��   : l00171473
        �޸�����   : DTS2012050204913, Lģʱ����Ҫ����LU
     7. ��    ��   : 2012��11��25��
        ��    ��   : l65478
        �޸�����   : DTS2012112606482,GCF 9.2.3.3.2����ʧ��
     8. ��    ��   : 2013��1��23��
        ��    ��   : w00176964
        �޸�����   : DTS2013012290625:3312��ʱ��L��פ��̬���GS��
 ************************************************************************/
VOS_VOID Gmm_Tim3312Expired(VOS_VOID)
{
    VOS_UINT32                  ucOldState;

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_Tim3312Expired:INFO:T3312 Expire.");
    GMM_PrintState();

    ucOldState = g_GmmGlobalCtrl.ucState;
#if (FEATURE_LTE == FEATURE_ON)
     NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_EXP);

     if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
     {
         g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;
         if (VOS_TRUE == NAS_GMM_IsNeedStartT3323())
         {
             Gmm_TimerStart(GMM_TIMER_T3323);
         }

        NAS_NORMAL_LOG(WUEPS_PID_GMM, "Gmm_Tim3312Expired: Clear ucGsAssociationFlg to VOS_FALSE");
        g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;

         return;
     }
#endif

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* �жϵ�ǰ״̬                             */
    case GMM_REGISTERED_NORMAL_SERVICE:
        Gmm_Tim3312Expired_RegNmlServ();                                        /* ����״̬GMM_REGISTERED_NORMAL_SERVICE��  *
                                                                                 * ��T3312�������                          */
        break;                                                                  /* ����                                     */

    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
        Gmm_Tim3312Expired_RegNoCell();                                         /* ����״̬GMM_REGISTERED_NO_CELL_AVAILABLE *
                                                                                 * �µ�T3312�������                        */
        break;
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_REGISTERED_UPDATE_NEEDED:
        g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;

        if (  (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
            &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);          /* ֪ͨMM����LU                             */
        }

#if (FEATURE_LTE == FEATURE_ON)
        /* GMM����ע�ᱻbar״̬��ISR�����Ҫ����T3323��ʱ�� */
        if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
        {
            Gmm_TimerStart(GMM_TIMER_T3323);
        }
#endif
        break;                                                                  /* ����                                     */

    case GMM_REGISTERED_PLMN_SEARCH:
        g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;

#if (FEATURE_LTE == FEATURE_ON)

        /* GMM����ʱ����GMM_REGISTERED_PLMN_SEARCH��ISR�����Ҫ����T3323��ʱ����
           ���������米���ѵĿ���ָ����״̬ISR������������T3323  */
        if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
         && (GMM_TRUE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
        {
            Gmm_TimerStart(GMM_TIMER_T3323);
        }
#endif
        break;

     default:                                                                    /* �������                                 */
        g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;                                                                            /* ����                                     */
        break;
    }

    /* ��ǰ��LTE�²���GMM��REG_NORMAL_SERVICE̬,���GS�� */
    if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
     && (GMM_REGISTERED_NORMAL_SERVICE != ucOldState)
     && (GMM_REGISTERED_PLMN_SEARCH    != ucOldState))
    {
        g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;
    }

    return;
}

/***********************************************************************
  Module   : Gmm_Tim3312Expired_RegNmlServ
  Function : ��ʱ��T3312��״̬GMM_REGISTERED_NORMAL_SERVICE�µ��������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1.  ��־��  2003.12.10  �°�����
     2. ��    ��   : 2007��05��11��
        ��    ��   : luojian id:60022475
        �޸�����   : ���ⵥ��:A32D10713
     3. ��    ��   : 2009��04��25��
        ��    ��   : h44270
        �޸�����   : ���ⵥ��:AT2D08867
     4. ��    ��   : 2010��12��08��
        ��    ��   : l00167671
        �޸�����   : ���ⵥ��:DTS2010111202717,��ѡ�����в���RAU,
                      �ȵ�SYS_INFO�ϱ�ʱ����
     5. ��    ��   : 2012��2��02��
        ��    ��   : l00130025
        �޸�����   : ���ⵥ��:DTS2012011906061,ֻ��G����Ҫ�ж�gstGmmCasGlobalCtrl.ucCellReselFlg
************************************************************************/
VOS_VOID Gmm_Tim3312Expired_RegNmlServ(VOS_VOID)
{
    g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;                                  /* ��3312�����־                           */


    /*��ǰG�²�����ѡ��������ʱ������������RAU */
    if ((NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
     && (VOS_FALSE == gstGmmCasGlobalCtrl.ucCellReselFlg))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
    }
    else
    {
    }


}


/***********************************************************************
  Module   : Gmm_Tim3312Expired_RegNoCell
  Function : ��ʱ��T3312��״̬GMM_REGISTERED_NO_CELL_AVAILABLE�µ��������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1. ��־�� 2003.12.10  �°�����
     2. ��    ��   : 2007��05��11��
        ��    ��   : luojian id:60022475
        �޸�����   : ���ⵥ��:A32D10713
     3. ��    ��   : 2011��03��24��
        ��    ��   : ŷ����
        �޸�����   : ���ⵥ��:DTS2011032400460��פ���ɹ����û�ָ������������������
                     ����פ����T3312��ʱ��MM�����˲�������LAU
     4.��    ��   : 2012��3��7��
       ��    ��   : z00161729
       �޸�����   : V7R1 C50 ֧��ISR�޸�
     5.��    ��   : 2013��2��4��
       ��    ��   : w00176964
       �޸�����   : DTS2011022802215:CS ONLY,����ģʽI��Ҳ��������ע��
 ************************************************************************/
VOS_VOID Gmm_Tim3312Expired_RegNoCell(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    enTinType = NAS_MML_GetTinType();

    /* GMM����GMM_REGISTERED_NO_CELL_AVAILABLE��GMM_REGISTERED_LIMITED_SERVICE��ISR���
       ��Ҫ����T3323��ʱ�� */
    if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType)
    {
        Gmm_TimerStart(GMM_TIMER_T3323);
    }
#endif

    g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;                                  /* ���T3312�Ѿ����                        */

    if ((GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucSysValidFlg)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
    {                                                                           /* ��ǰС����֧��GPRS                       */
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* �û�ģʽA������ģʽI                     */
            NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);          /* ֪ͨMM����LU                             */
        }
    }
    else
    {
    }
}


/***********************************************************************
  Module   : Gmm_Tim3316Expired
  Function : ��ʱ��T3316�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1.  ��־��  2003.12.10  �°�����
    2.��    ��  :2014��01��09��
      ��    ��  :l65478
      �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ

 ************************************************************************/
VOS_VOID Gmm_Tim3316Expired(VOS_VOID)
{
    g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;                                /* ��RES���ڱ�־��ΪFALSE                   */
    g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;                                /* RAND���ڱ�־�ó�FALSE                    */
}


/***********************************************************************
  Module   : Gmm_Tim3317Expired
  Function : ��ʱ��T3317�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��    2003.12.10  �°�����
  2.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
  3.��    ��   : 2012��3��17��
    ��    ��   : w00176964
    �޸�����   : DTS2012031900095 V7R1 C30 SBM&EM��������:���Ӳ��ű��ܶ���
  4.��    ��   : 2012��08��24��
    ��    ��   : m00217266
    �޸�����   : �޸�GMM_SndSmServiceRej�ӿڣ����ԭ��ֵ

************************************************************************/
VOS_VOID Gmm_Tim3317Expired(VOS_VOID)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;
    enCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;

    if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* �жϵ�ǰ״̬��SERVICE_REQUEST_INITIATED  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                            /* ����״̬�Ĺ�������                       */
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
                                        == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* ���ԭ��ȴ���־                         */
        }
        Gmm_ComCnfHandle();
        if ((GMM_SERVICE_REQUEST_DATA_IDLE
                        == g_GmmGlobalCtrl.ucSpecProc)
                 || (GMM_SERVICE_REQUEST_SIGNALLING
                        == g_GmmGlobalCtrl.ucSpecProc)
                 || (GMM_SERVICE_REQUEST_PAGING_RSP
                        == g_GmmGlobalCtrl.ucSpecProc))
        {                                                                       /* service request������Ϊ��PMM-IDLE�´���
                                                                                 * data,signalling,paging response����֮һ  */
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);                               /* �ͷ�����                                 */
        }
        else
        {
        }

        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* ���ڱ������T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* �ָ�T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* ���ڱ������T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* �ָ�T3302                                */
        }
        else
        {
        }

        if (VOS_TRUE== NAS_MML_GetDailRejectCfg())
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_T3317_EXPIRED);

            g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
        }

        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                        enCause);                                     /* ����MMCGMM_GMM_ACTION_RESULT_IND()       */


        /* ��MMC����service request��� */
        NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                              enCause);
        /* �¼��ϱ� */
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_DATA_SERVICE_REJ,
                        (VOS_VOID*)&enCause,
                        NAS_OM_EVENT_SERVICE_REJ_LEN);

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �����ǰ����                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_Tim3317Expired:INFO: specific procedure ended");
    }
}

/***********************************************************************
  Module   : Gmm_Tim3318Expired
  Function : ��ʱ��T3318�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1. ��־��  2003.12.10  �°�����
     2.��    ��   : 2009��03��31��
       ��    ��   : L65478
       �޸�����   : �������ⵥ�ţ�AT2D10529���μ�Ȩʧ�ܺ�û���ͷ�RRC����
     3.��    ��   : 2012��4��20��
       ��    ��   : l00130025
       �޸�����   : DTS2012032004389��Netork����3�α�Ms Auth Rej��T3318/T3320��ʱʱ��û��֪ͨGAS Bar����ǰС��
     4.��    ��   : 2012��12��25��
       ��    ��   : L65478
       �޸�����   : DTS2012122900226,G�¶�ʱ����ʱ����ʧ�ܴ��������Ƿ��ֹ��ǰС��
     5.��    ��   : 2013��01��23��
       ��    ��   : L65478
       �޸�����   : DTS2013012301527,GCF 12.6.1.3.3ʧ��
 ************************************************************************/
VOS_VOID Gmm_Tim3318Expired(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8             enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    /* Authentication attempt counter��0 */
    /* ��ǰС����barred */
    /* ��ǰ��RAT��W��������ֹ��ǰ������;��ǰ��RAT��G��������Ȩʧ��3������ֹ��ǰ������ */
    if (((g_GmmAuthenCtrl.ucAuthenAttmptCnt >= GMM_AUTHEN_ATTEMPT_MAX_CNT)
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurRat))
     || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat))
    {
        g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;
        g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;

        /* ��ǰС����barred)                        */
        NAS_GMM_SndGasGprsAuthFailNotifyReq();

        Gmm_SndRrmmRelReq(RRC_CELL_BARRED);
    }

    /* ���ڱ�ֹͣ��retransmission timer�������� */
    Gmm_Start_StopedRetransmissionTimer();
}
/***********************************************************************
  Module   : Gmm_Tim3319Expired
  Function : ��ʱ��T3319�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
        1.  x00115505     2009.05.11  �°�����
 ************************************************************************/
VOS_VOID Gmm_Tim3319Expired(VOS_VOID)
{
    VOS_VOID                            *pMsg;
    GMMRABM_REESTABLISH_REQ_STRU        *pRabmReEst;

    if (GMM_MSG_HOLD_FOR_SERVICE ==
        (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* ����б�����SRԭ��                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* ��������־                             */

        pMsg = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;

        /*����ַ���Ϣ*/
        pRabmReEst = (GMMRABM_REESTABLISH_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMRABM_REESTABLISH_REQ_STRU));

        if (VOS_NULL_PTR == pRabmReEst)
        {
            Gmm_MemFree(pMsg);
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DealWithBuffAfterProc:ERROR: Gmm_MemMalloc fail !! ");
            return;
        }

        Gmm_MemCpy(pRabmReEst, pMsg, sizeof(GMMRABM_REESTABLISH_REQ_STRU));

        /*�ͷű����RAMB��Ϣ*/
        Gmm_MemFree(pMsg);

        /*�ַ������Service��Ϣ*/
        Gmm_MsgDistribute((VOS_VOID *)(pRabmReEst));

        /*�ͷ���������ڴ�*/
        Gmm_MemFree(pRabmReEst);
    }
}
/***********************************************************************
  Module   : Gmm_Tim3320Expired
  Function : ��ʱ��T3320�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1.  ��־��  2003.12.10  �°�����
 ************************************************************************/
VOS_VOID Gmm_Tim3320Expired(VOS_VOID)
{
    Gmm_Tim3318Expired();
}

/***********************************************************************
  Module   : Gmm_Tim3321Expired
  Function : ��ʱ��T3321�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1.  ��־��  2003.12.10  �°�����
 ************************************************************************/
VOS_VOID Gmm_Tim3321Expired(VOS_VOID)
{
    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* �жϵ�ǰ״̬                             */
    case GMM_DEREGISTERED_INITIATED:
        Gmm_Tim3321Expired_DeregInit ();                                        /* ����T3321��״̬GMM_DEREGISTERED_INITIATE
                                                                                 * D�µ��������                            */
        break;                                                                  /* ����                                     */
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_Tim3321Expired_RegImsiDtchInit ();                                  /* ����T3321��״̬GMM_REGISTERED_IMSI_DETAC *
                                                                                 * H_INITIATED�µ��������                  */
        break;                                                                  /* ����                                     */
    default:                                                                    /* �������                                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_Tim3321Expired:WARNING: g_GmmGlobalCtrl.ucState is Abnormal");
        break;                                                                  /* ����                                     */
    }
}

/*****************************************************************************
 �� �� ��  : VOS_VOID NAS_GMM_TimerProtectPsDetachExpired(VOS_VOID)
 ��������  : GMM PS��Detach��Ϣ������ʱ����ʱ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_TimerProtectPsDetachExpired(VOS_VOID)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulGmmState;

    ulGmmState = g_GmmGlobalCtrl.ucState;

    /* ɾ�������PS��DETACHԭ�� */
    ulRslt = NAS_GMM_DeleteSavedDetachMsg(GMM_WAIT_PS_DETACH);

    if ( VOS_TRUE == ulRslt )
    {
        /* ֪ͨMMC/MM��ǰdetach��� */
        g_GmmGlobalCtrl.stDetachInfo.enDetachType = GMM_WAIT_PS_DETACH;

        /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
        NAS_GMM_SndMmcMmDetachInfo();
    }

    switch ( ulGmmState )
    {
        case GMM_SUSPENDED_NORMAL_SERVICE:
        case GMM_GPRS_SUSPENSION:
        case GMM_SUSPENDED_GPRS_SUSPENSION:
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:

            /* ����״̬���б���detach��������ϣ�ֱ�ӷ��� */
            NAS_GMM_LocalDetach_GprsSuspension();
            return;

        case GMM_DEREGISTERED_INITIATED:

            /* GMM_DEREGISTERED_INITIATED״̬���б���detach��������ϣ�ֱ�ӷ��� */
            NAS_GMM_LocalDetach_GmmDeregisteredInitiated();
            return;

        case GMM_ROUTING_AREA_UPDATING_INITIATED:

            /* GMM_ROUTING_AREA_UPDATING_INITIATED״̬���б���detach��������ϣ�ֱ�ӷ��� */
            NAS_GMM_LocalDetach_GmmRauInitiated();
            return;

        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:

            /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE״̬���б���detach��������ϣ�ֱ�ӷ���  */
            NAS_GMM_LocalDetach_GmmDeregisteredAttemptingToAttach();
            return;

        case GMM_REGISTERED_NO_CELL_AVAILABLE :
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);
            break;

        case GMM_REGISTERED_PLMN_SEARCH :
            Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
            break;

        case GMM_REGISTERED_LIMITED_SERVICE :
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            break;

        case GMM_REGISTERED_UPDATE_NEEDED :
            Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
            break;

        /* ����״̬������Ǩ�� */
        case GMM_DEREGISTERED_NO_IMSI :
        case GMM_DEREGISTERED_PLMN_SEARCH :
        case GMM_DEREGISTERED_LIMITED_SERVICE :
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE :
        case GMM_NULL :
        case GMM_DEREGISTERED_ATTACH_NEEDED :

            break;

        /* �����Ƿ񶼿���Ǩ�Ƶ�GMM_DEREGISTERED_NORMAL_SERVICE */
        default:
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
            break;
    }

    /* GMM���б���PS��DETACH */
    NAS_GMM_GprsLocalDetach();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_Gmm_RcvMmT3211ExpiredNotify
 ��������  : GMM�յ�MM��T3211��ʱ����ʱ��Ϣ�Ĵ���
 �������  : pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��5��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
*****************************************************************************/
VOS_VOID NAS_Gmm_RcvMmT3211ExpiredNotify(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucPsAttachAllowFlg;
    NAS_MML_CONN_STATUS_INFO_STRU                          *pstConnStatus = VOS_NULL_PTR;
    MMGMM_T3211_TIMER_EXPIRED_NOTIFY_STRU                  *pstT3211ExpiredNotify = VOS_NULL_PTR;
    VOS_UINT8                                               ucSimPsRegStatus;

    pstConnStatus         = NAS_MML_GetConnStatus();
    pstT3211ExpiredNotify = (MMGMM_T3211_TIMER_EXPIRED_NOTIFY_STRU *)pstMsg;
    ucSimPsRegStatus      = NAS_MML_GetSimPsRegStatus();

    if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
    {
        /* ��ǰפ�����粻��֧��DAM���������б��У������� */
        return;
    }

    /* ���mm����T3211��ʱ��ʱlau����ԭ��ֵ��Ϊ#17�򲻴���GSM-BTR-1-0644��
       GSM-BTR-1-0650��GSM-BTR-1-0652��GSM-BTR-1-0656������������lau��#17�ܾ� */
    if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE != pstT3211ExpiredNotify->ucRejectCause)
    {
        return;
    }

    /* GAS��PS���Է���ע��GMM�Ż������Ϣ�������յ�GAS��gprs resume ind��Ϣ
       ��cs�������Ӳ�����Ϣʱ�������T3211��ʱ����ʱ��Ϣ
       �����register normal service״̬Ҳ�败��rau��*/

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        ucPsAttachAllowFlg = NAS_MML_GetPsAttachAllowFlg();

        /* PS���Է���ע��ʱ����Ҫ�����յ�T3211��ʱ����ʱ��ʶ */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (VOS_TRUE  == ucPsAttachAllowFlg)
         && (VOS_TRUE == ucSimPsRegStatus))
        {
            if (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg)
            {
                /* RR���Ӳ����ڱ�ʾCS���ڽ�������,��Ҫ�����յ�T3211��ʱ����ʱ��ʶ*/
                if (VOS_FALSE == pstConnStatus->ucRrcStatusFlg)
                {
                    NAS_GMM_SetMmT3211ExpiredDelayRauFlag(VOS_TRUE);
                }
                return;
            }
        }
        return;
    }

    /* AT&T GSM-BTR-1-0644��GSM-BTR-1-0650��GSM-BTR-1-0652��GSM-BTR-1-0656��������
      Ҫ��MM��attempting to update״̬��T3211��ʱ����ʱ��MM��lau��ͬʱ��
      ֪ͨGMM T3211��ʱ����ʱ��W��GMM��register normal service״̬Ҳ�败��rau*/
    if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        return;
    }

    /* ���gmm��GMM_SERVICE_REQUEST_INITIATED״̬����rabm�ؽ���pdp��������У�����*/
    if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        NAS_GMM_SetMmT3211ExpiredDelayRauFlag(VOS_TRUE);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : VOS_VOID NAS_Gmm_RcvMmCsLocalDetachInd(VOS_VOID)
 ��������  : GMM�յ�MM��CS�򱾵�Detach��Ϣ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_Gmm_RcvMmCsLocalDetachInd(
    VOS_VOID                           *pstMsg
)
{
    /* ɾ�������CS��DETACH */
    (VOS_VOID)NAS_GMM_DeleteSavedDetachMsg(GMM_WAIT_CS_DETACH);

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* ����״̬�ַ�                             */
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
            NAS_Gmm_RcvMmCsLocalDetachInd_RegImsiDtchInit();
            break;

        case GMM_REGISTERED_INITIATED:
            NAS_Gmm_RcvMmCsLocalDetachInd_RegInit();
            break;

        case GMM_ROUTING_AREA_UPDATING_INITIATED:
            NAS_Gmm_RcvMmCsLocalDetachInd_RauInit();
            break;

        default:
            break;
    }

    /* ����ģʽI��,CS DETACH��־����,��ɾ����־ */
    if (GMM_WAIT_CS_DETACH ==
        (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_CS_DETACH) )
    {
        g_GmmGlobalCtrl.stDetachInfo.enDetachType &= ~GMM_WAIT_CS_DETACH;
    }

    return;
}


/***********************************************************************
  Module   : Gmm_Tim3321Expired_DeregInit
  Function : ��ʱ��T3321�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1. ��־��    2003.12.10  �°�����
  2. ��    ��   : 2006��9��23��
     ��    ��   : sunxibo id:46746
     �޸�����   : �������ⵥ�ţ�A32D05848
  3. ��    ��   : 2006��11��20��
     ��    ��   : s46746
     �޸�����   : �������������ⵥ�ţ�A32D07433
  4. ��    ��   : 2011��07��13��
     ��    ��   : w00166186
     �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  5.��    ��   : 2011��7��27��
    ��    ��   : h44270
    �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
  6. ��    ��   : 2012��1��12��
     ��    ��   : w00166186
     �޸�����   : DTS2011122704039:����������CSע�ᱻ��#12,PSע�ᱻ��#14����ON
                   PLMN״̬������������Ϊ��֧��GMM��Ҫ��������֧����Ϣ֪ͨ��MMC.
  7.��    ��   : 2013��8��7��
    ��    ��   : w00167002
    �޸�����   : DTS2013080207367:��CS onlyʱ���û�����PDP�������ģʽIʱ��
                 �ᴥ������ע��.�û�����PDPȥ����ᵼ��PS���ȥע�ᡣ�յ�����
                 ��ȥע��ɹ�����Ҫ֪ͨMM������MM��ǰ��NORMAL SERVICE״̬����
                 ����T3212��ʱ������������ʱ����ܵ��¶�Ѱ��.
************************************************************************/
VOS_VOID Gmm_Tim3321Expired_DeregInit(VOS_VOID)
{
    NAS_MSG_STRU         *pNasMsg = VOS_NULL_PTR ;                              /* ����ָ��                                 */

    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* �ȴ���Ȩ��Ӧ                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* ���ԭ��ȴ���־                         */
    }
    g_GmmDetachCtrl.ucT3321OutCnt ++;                                           /* T3321���������1                         */
    if (g_GmmDetachCtrl.ucT3321OutCnt < GMM_TIMER_EXPIRED_MAX_CNT)
    {                                                                           /* �ж���������Ƿ�С��5                    */

#if (FEATURE_ON == FEATURE_DSDS)
        /* ��DSDSʱ��GSM��ATTACH/RAU/DETACHʧ��ʱ�������Ѿ��ͷ�����Դ����Ҫ�������룬������ģһֱ��ȡ������Դ */
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            NAS_GMM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_PS_DETACH);
            NAS_GMM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_PS_DETACH);
        }
#endif

        pNasMsg = Gmm_DetachRequestMsgMake();                                   /* ����detach request��Ϣ��������           */

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);                  /* ����DETACH REQUEST��Ϣ                   */
        Gmm_TimerStart(GMM_TIMER_T3321);                                        /* ��T3321                                  */
    }
    else
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* ����״̬�Ĺ�������                       */

        if (GMM_DETACH_NORMAL_NETMODE_CHANGE != g_GmmGlobalCtrl.ucSpecProc)
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);     /* ��PS���attach��ֹ��־                   */
        }

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;

        g_GmmDetachCtrl.ucT3321OutCnt = 0;                                      /* T3321���������0                         */

        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                       /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                &= ~GMM_UEID_P_TMSI_SIGNATURE;                                  /* ���P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }

        /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }
        else
        {
            /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
            NAS_GMM_SndMmGprsDetachComplete();
        }



        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);
        }

    }
    return;                                                                     /* ����                                     */
}

/***********************************************************************
  Module   : Gmm_Tim3321Expired_RegImsiDtchInit
  Function : ��ʱ��T3321�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1. ��־��    2003.12.10  �°�����

************************************************************************/
VOS_VOID Gmm_Tim3321Expired_RegImsiDtchInit(VOS_VOID)
{
    NAS_MSG_STRU        *pNasMsg = VOS_NULL_PTR ;                               /* ����ָ��                                 */

    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* �ȴ���Ȩ��Ӧ                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* ���ԭ��ȴ���־                         */
    }
    g_GmmDetachCtrl.ucT3321OutCnt++;                                            /* T3321���������1                         */
    if (GMM_TIMER_EXPIRED_MAX_CNT > g_GmmDetachCtrl.ucT3321OutCnt)
    {                                                                           /* �ж��������С��5                        */


#if (FEATURE_ON == FEATURE_DSDS)
        /* ��DSDSʱ��GSM��ATTACH/RAU/DETACHʧ��ʱ�������Ѿ��ͷ�����Դ����Ҫ�������룬������ģһֱ��ȡ������Դ */
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            NAS_GMM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_PS_DETACH);
            NAS_GMM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_PS_DETACH);
        }
#endif

        pNasMsg = Gmm_DetachRequestMsgMake();                                   /* ����detach request��Ϣ��������           */

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);                  /* ����DETACH REQUEST��Ϣ                   */
        Gmm_TimerStart(GMM_TIMER_T3321);                                        /* ��T3321                                  */
    }
    else
    {                                                                           /* �ж������������5                        */
        Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                           /* ����״̬�Ĺ�������                       */
        g_GmmDetachCtrl.ucT3321OutCnt = 0;                                      /* T3321���������0                         */

        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                       /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                &= ~GMM_UEID_P_TMSI_SIGNATURE;                                  /* ���P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
        }

        /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }
    }
    return;                                                                     /* ����                                     */
}

/***********************************************************************
  Module   : Gmm_Tim3330Expired
  Function : ��ʱ��T3330�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
  1.��־��    2003.12.10  �°�����
  2.��    ��   : 2008��9��18��
    ��    ��   : ouyangfei 00132663
    �޸�����   : �������ⵥ�ţ�AT2D05816����GMM�����У�����CM���SMS����Ӧ�ñ����棬��GMM���̽����ٷ���
  3.��    ��   : 2009��05��23��
    ��    ��   : L65478
    �޸�����   : ���ⵥ��:AT2D06770,RAUʧ�ܣ���ΪGRM������ԭ����DATA��ʵ��Ӧ��������
  4.��    ��   : 2009��06��30��
    ��    ��   : l65478
    �޸�����   : ���ⵥ��AT2D12655,�������LLC�������͵Ĵ���
  5.��    ��   : 2009��09��25��
    ��    ��   : l00130025
    �޸�����   : ���ⵥ��:AT2D14675,RAU/Attach�����У�list����ʧ��
  6.��    ��   : 2009��10��3��
    ��    ��   : l00130025
    �޸�����   : �������ⵥ�ţ�AT2D14889,G����ģʽI��,Combined RAU�����У�
                 ������ҪCS detach��SYSCFGʧ��
  7.��    ��   : 2010��7��21��
    ��    ��   : ŷ����
    �޸�����   : DTS2010071500036,��ATTACH��RAUʧ�ܺ�δ֪ͨLL�����������
                ������UE��Ȼ�ڷ����ط�����
  8.��    ��   : 2011��7��10��
    ��    ��   : w00166186
    �޸�����   : V7R1 PHASE II ATTACH/DETACH����
  9.��    ��   : 2011��7��14��
    ��    ��   : h44270
    �޸�����   : V7R1 PhaseII�׶ε�����ע������
 10.��    ��   : 2011��7��26��
    ��    ��   : l00130025
    �޸�����   : V7R1 PhaseII�׶ε�����ɾ��UserDelay��־����MMC����
 11.��    ��   : 2011��4��29��
    ��    ��   : c00173809
    �޸�����   : DTS2011042804013,UE������ģʽI��,ͨ������W��ģ������W����ͬRAI
                      ��С��,����W�·���绰,Ȼ��PDP����,Ȼ���ͷ�CS�绰,UE���е�����RAU
                      ��ͨ��EST_REQ������ͨ��DATE_REQ���͵�.
 12.��    ��   : 2011��11��8��
    ��    ��   : s46746
    �޸�����   : V7R1 PhaseII�׶ν���ػ�������
 13.��    ��   : 2011��12��24��
    ��    ��   : w00166186
    �޸�����   : DTS2011122104474,ָ��������ͣLAU����ͳһ�޸�
 14.��    ��   : 2012��2��15��
    ��    ��   : w00167002
    �޸�����   : V7R1C50 CSFB&PPAC&ETWS&ISR:����������ǰ����CSFBҵ���־����ֻ��RAU
 15.��    ��   : 2012��2��15��
    ��    ��   : w00166186
    �޸�����   : CSFB&PPAC&ETWS&ISR ����
 16.��    ��   : 2013��3��30��
    ��    ��   : l00167671
    �޸�����   : �����ϱ�AT�������������C��
 17.��    ��   : 2013��7��22��
    ��    ��   : z00161729
    �޸�����   : DTS2013071908566:rau init״̬��w cco��g�ٻ��˵�w��gmm�����·���rau
 18.��    ��   : 2014��05��22��
    ��    ��   : W00242748
    �޸�����   : DTS2014050900899:��GMM�Ĵ���״̬֪ͨ��WAS
 19.��    ��   : 2015��4��21��
    ��    ��   : z00161729
    �޸�����   : 24301 R11 CR������Ŀ�޸�
************************************************************************/
VOS_VOID Gmm_Tim3330Expired(VOS_VOID)
{
    VOS_UINT8            ucUpdateType = GMM_RA_UPDATING;                         /* ������ʱ���������������                 */
    NAS_MSG_STRU        *pNasMsg = VOS_NULL_PTR ;                                /* ����ֲ�����                             */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;
    VOS_UINT8                           ucCsRestrictionFlg;
    VOS_UINT8                           ucPsRestrictionFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    ucCsRestrictionFlg  = NAS_MML_GetCsRestrictRegisterFlg();
    ucPsRestrictionFlg  = NAS_MML_GetPsRestrictRegisterFlg();

    enCause  = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;

    /* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
    if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
      || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        if (GMM_TRUE == g_GmmRauCtrl.ucPeriodicRauFlg)
        {
            /* ��GAS����GRRGMM_GPRS_PROC_IND,����ΪPERIODIC RAU,��־ΪFINISH */;
            NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_PERIOD_RAU, RRMM_GMM_PROC_FLAG_FINISH);

            NAS_MML_SetGmmProcType(NAS_MML_GMM_PROC_TYPE_PERIOD_RAU);
            NAS_MML_SetGmmProcFlag(NAS_MML_GMM_PROC_FLAG_FINISH);
        }
        else
        {
            /* ��GAS����GRRGMM_GPRS_PROC_IND,����ΪNORMAL RAU,��־ΪFINISH */;
            NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_NORMAL_RAU, RRMM_GMM_PROC_FLAG_FINISH);

            NAS_MML_SetGmmProcType(NAS_MML_GMM_PROC_TYPE_NORMAL_RAU);
            NAS_MML_SetGmmProcFlag(NAS_MML_GMM_PROC_FLAG_FINISH);
        }
    }
    /* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

    if (GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
    {
        /* �˱�־��¼����ϵͳ����ѡ�����л�ʱ,RAI��ͬʱ,����������������ʱ��Ҫ����RAU.
           ��Ϊ���ô˺���ʱRAU�Ѿ����,������Ҫ����˱�־ */
        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;
    }

    if (GMM_REGISTERED_UPDATE_NEEDED == g_GmmGlobalCtrl.ucState)
    {
        if (  (VOS_TRUE == ucPsRestrictionFlg)
            &&(VOS_FALSE == ucCsRestrictionFlg)
            &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3330_EXPIRED);          /* ֪ͨMM����LU                             */
            Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
            Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */
            return;
        }
    }

    if (GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState)
    {                                                                           /* �жϵ�ǰ״̬                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "g_GmmGlobalCtrl.ucState:WARNING: g_GmmGlobalCtrl.ucState is not GMM_ROUTING_AREA_UPDATING_INITIATED");
        return;                                                                 /* ����                                     */
    }

    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_SIGNALLING);
    }

    /* �����ǰ�л���Ķ������󣬻ظ�ʧ��ָʾ��*/
    if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
    {
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* ����PMMSMS_ERROR_IND                     */
        g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
    }

    if (GMM_MSG_HOLD_FOR_SMS
        ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SMS;
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)NULL;
    }

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* �ȴ���Ȩ��Ӧ                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* ���ԭ��ȴ���־                         */
    }


    g_GmmRauCtrl.ucT3330outCnt ++;                                              /* T3330�������+1                          */
    if (GMM_TIMER_EXPIRED_MAX_CNT > g_GmmRauCtrl.ucT3330outCnt)
    {                                                                           /* �жϴ���                                 */
        if (GMM_TRUE == g_GmmRauCtrl.ucPeriodicRauFlg)
        {                                                                       /* ��ǰRAU�Ƿ�������RAU��־                 */
            ucUpdateType = GMM_PERIODC_UPDATING;                                /* RAU������RAU                             */

            /* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
            /* �����ǰ���뼼����G����GAS����GRRGMM_GPRS_PROC_IND,����ΪPERIODIC RAU,��־ΪSTART */;
            if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
              || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
            {
                NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_PERIOD_RAU, RRMM_GMM_PROC_FLAG_START);

                NAS_MML_SetGmmProcType(NAS_MML_GMM_PROC_TYPE_PERIOD_RAU);
                NAS_MML_SetGmmProcFlag(NAS_MML_GMM_PROC_FLAG_START);
            }
            /* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

        }
        else
        {
        #if (FEATURE_ON == FEATURE_LTE)

            /* ����CSFBҵ��ʱ������RAU */
            if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
            {
                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
            }
        #endif

            if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
            {
                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                g_GmmGlobalCtrl.CsInfo.ucCsTransFlg = GMM_FALSE;                         /* ��CSͨ����Ϊ��                           */
            }

            if ((GMM_RAU_NORMAL != g_GmmGlobalCtrl.ucSpecProc)
             && (GMM_RAU_NORMAL_CS_TRANS != g_GmmGlobalCtrl.ucSpecProc)
             && (GMM_RAU_WITH_IMSI_ATTACH != g_GmmGlobalCtrl.ucSpecProc)
             && (GMM_RAU_COMBINED != g_GmmGlobalCtrl.ucSpecProc))
            {

                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "g_GmmGlobalCtrl:WARNING: g_GmmGlobalCtrl.ucSpecProc is Abnormal");
                return;                                                         /* ����                                     */
            }

            ucUpdateType = NAS_GMM_GetRoutingAreaUpdateType();

            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg  = GMM_FALSE;                        /* �����־                                 */
            g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* �����־                                 */


            /* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
            /* �����ǰ���뼼����G����GAS����GRRGMM_GPRS_PROC_IND,����ΪNORMAL RAU,��־ΪSTART */;
            if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
              || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
            {
                NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_NORMAL_RAU, RRMM_GMM_PROC_FLAG_START);

                NAS_MML_SetGmmProcType(NAS_MML_GMM_PROC_TYPE_NORMAL_RAU);
                NAS_MML_SetGmmProcFlag(NAS_MML_GMM_PROC_FLAG_START);
            }
            /* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */

        }

        /* ���� Rau ʱ���ж��Ƿ����ϲ�ҵ������У������� Follow-On ��־ */
        if ((GMM_MSG_HOLD_FOR_SERVICE
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
            ||(GMM_MSG_HOLD_FOR_SM
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM)))
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);
        }

#if (FEATURE_ON == FEATURE_DSDS)

        if (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
        {
            NAS_GMM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_PS_RAU);
            NAS_GMM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_PS_RAU);
        }
#endif

        pNasMsg = Gmm_RoutingAreaUpdateRequestMsgMake(ucUpdateType);            /* ��Ϣ����                                 */
           /* send DATA Req to delete the saved data */
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pNasMsg);             /* ����RAU REQUEST��Ϣ                      */
        Gmm_TimerStart(GMM_TIMER_T3330);                                    /* ����T3330                                */
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_RAU_REQ,
                        (VOS_VOID *)&ucUpdateType,
                        NAS_OM_EVENT_RAU_REQ_LEN);

        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     enCause);

        if ((GMM_COMBINED_RALA_UPDATING == ucUpdateType)
         || (GMM_COMBINED_RALAU_WITH_IMSI_ATTACH == ucUpdateType))
        {
            NAS_GMM_SndMmCombinedRauRejected(enCause);

            NAS_GMM_SndMmCombinedRauInitiation();
        }
    }
    else
    {
        if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
        {
            GMM_RauFailureInterSys();
        }
        else
        {
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        }

        g_GmmRauCtrl.ucT3330outCnt = 0;                                         /* T3330���������0                         */
        g_GmmRauCtrl.ucRetryFlg = GMM_FALSE;                                    /* ���û�С��������RAU��־                  */
        Gmm_RoutingAreaUpdateAttemptCounter(NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);        /* ����RAU attempt counter�Ĺ�������        */
    }
    return;                                                                     /* ����                                     */
}

/***********************************************************************
  Module   : NAS_GMM_Timer3340Expired
  Function : ��ʱ��T3340�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1. ŷ����    2010.01.03  �����¶�ʱ��T3340
 ************************************************************************/
VOS_VOID NAS_GMM_Timer3340Expired(VOS_VOID)
{
    if ((GMM_FALSE == GMM_IsCasGsmMode()) && (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg))
    {
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
    }

    return;                                                                     /* ����                                     */
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_TimerDetachForPowerOffExpired
 ��������  : GMM�յ��ػ�detach��ʱ����ʱ��Ϣ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��10��15��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID NAS_GMM_TimerDetachForPowerOffExpired(VOS_VOID)
{
    /* �ػ�������ʱ����ʱ��ǿ�ƹػ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    if (GMM_TRUE != GMM_IsCasGsmMode())
    {
        /* W�������������ڣ��ͷ���· */
        if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        {
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
        }

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }

    /* ���P_TMSI_SIGNATURE */
    if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

        NAS_MML_InitUeIdPtmsiSignatureInvalid();

        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
    }

    /* ��MMC�������Ӧ��ģ��ظ���Ϣ */
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

    if (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
    {
        NAS_GMM_SndMmGprsDetachComplete();
    }

    Gmm_SndMmcPowerOffCnf();
    Gmm_ComCnfHandle();
    NAS_GMM_FreeTlliForPowerOff();

    /* ���ȫ�ֱ��� */
    if (GMM_MSG_HOLD_FOR_POWEROFF == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;
    }
    Gmm_HoldBufferFree();
    Gmm_ComVariantInit();
    GMM_BufferMsgDump();
    return;
}


/***********************************************************************
  Module   : Gmm_Tim5sExpired
  Function : ��ʱ�� 5s�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.10  �°�����
    2.  ��    ��   : 2009��5��9��
        ��    ��   : l00130025
        �޸�����   : �������ⵥ�ţ�AT2D11645/AT2D11797,�ػ�����detach��EST_REQʧ�ܣ�Gmm�ᷴ������EST_REQ
    3. ��    ��   : 2009��05��23��
       ��    ��   : L65478
       �޸�����   : ���ⵥ��:AT2D06770,RAUʧ�ܣ���ΪGRM������ԭ����DATA��ʵ��Ӧ��������
    4. ��    ��   : 2010��07��26��
       ��    ��   : L65478
       �޸�����   : ���ⵥ��:DTS2010072200479,����ע������У��ػ����ٿ���ʱʧ�ܣ���ΪGMMû�����̴���ػ���Ϣ������MMC������ʱ����ʱ
    5. ��    ��   : 2010��09��13��
       ��    ��   : L65478
       �޸�����   : ���ⵥ��:DTS2010091301310,WCDMA�¹ػ������¿�������GSMģʽ���޷�ע��ɹ�
    6. ��    ��   : 2010��12��18��
       ��    ��   : o00132663
       �޸�����   : ���ⵥ��:DTS2010121800152,����ػ����̣���֤GMM���յ��ػ������8���ڹػ�
    7. ��    ��   : 2011��11��8��
       ��    ��   : s46746
       �޸�����   : V7R1 PhaseII�׶ν���ػ�������
    8. ��    ��   : 2012��2��15��
       ��    ��   : w00166186
       �޸�����   : CSFB&PPAC&ETWS&ISR ����
    9. ��    ��   : 2012��2��15��
       ��    ��   : w00166186
       �޸�����   : CSFB&PPAC&ETWS&ISR ����
   10. ��    ��   : 2012��10��12��
       ��    ��   : w00176964
       �޸�����   : DTS2012091400694:Gģ�ػ���
   11. ��    ��   : 2015��2��6��
       ��    ��   : h00313353
       �޸�����   : USIMM���ӿڵ���
************************************************************************/
VOS_VOID Gmm_Tim5sExpired(VOS_VOID)
{
    NAS_MSG_STRU           *pNasMsg;                                            /* ����ָ�� */
    VOS_UINT8               ucPsRestrictionFlg;

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    if (g_GmmGlobalCtrl.stPowerOffCtrl.ucSndDetachCnt < GMM_MAX_DETACH_CNT_WHEN_POWER_OFF)
    {
        ++ g_GmmGlobalCtrl.stPowerOffCtrl.ucSndDetachCnt;

        Gmm_TimerStart(GMM_TIMER_1S);

        /* ���������������GPRS��֧�֣����ٳ��� */
        if (  (RRC_EST_OTHER_ACCESS_BARRED == g_GmmGlobalCtrl.stPowerOffCtrl.ulEstResult)
           || (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
           || (VOS_TRUE == ucPsRestrictionFlg))
        {
            g_GmmGlobalCtrl.stPowerOffCtrl.ucSndDetachCnt = GMM_MAX_DETACH_CNT_WHEN_POWER_OFF;
            return;
        }

        /* GMM����̬��ֱ�ӷ��� */
        if ( (GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
          || (GMM_SUSPENDED_GPRS_SUSPENSION  == g_GmmGlobalCtrl.ucState))
        {
            return;
        }

        /* RRC ���ӽ��������С����� */
        if (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
        {
            return;
        }

        /* W��RRC���ӻ�δ���� */
        if (GMM_TRUE != g_GmmGlobalCtrl.ucSigConFlg)
        {
            pNasMsg = Gmm_DetachRequestMsgMake();                       /* DETACH REQUEST��Ϣ����                   */

            Gmm_SndRrmmEstReq (RRC_EST_CAUSE_DETACH,
                               GMM_RRC_IDNNS_UNKNOWN,
                               pNasMsg);                                /* ����RRMM_EST_REQ                         */

            Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ESTING);      /* ֪ͨMMC PS�������������ڽ���             */

            GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NORMAL_SERVICE);

            if ((GMM_DETACH_COMBINED_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc)
             || (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc))
            {                                                                   /* ��ǰ������combined sim remove��power off */
                g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;   /* �ñ�־λ����detach                       */
            }

            /* G�¹ػ��ο��������:GMM����5S��ʱ��,����detach������ֻ��Ҫ����5�� */
            Gmm_TimerStart(GMM_TIMER_DETACH_FOR_POWER_OFF);
        }

        return;
    }

    /* �ػ�������ʱ����ʱ��ǿ�ƹػ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    if (GMM_TRUE != GMM_IsCasGsmMode())
    {
        /* W�������������ڣ��ͷ���· */
        if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        {
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
        }

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }

    /* ���P_TMSI_SIGNATURE */
    if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

        NAS_MML_InitUeIdPtmsiSignatureInvalid();

        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
    }

    /* ��MMC�������Ӧ��ģ��ظ���Ϣ */
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

    if (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
    {
        NAS_GMM_SndMmGprsDetachComplete();
    }

    Gmm_SndMmcPowerOffCnf();
    Gmm_ComCnfHandle();
    NAS_GMM_FreeTlliForPowerOff();

    /* ���ȫ�ֱ��� */
    if (GMM_MSG_HOLD_FOR_POWEROFF == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;
    }
    Gmm_HoldBufferFree();

    GMM_BufferMsgDump();

    Gmm_ComVariantInit();

    return;
}

/***********************************************************************
  Module   : Gmm_TimProtectExpired
  Function : ������ʱ���������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1. ��־��  2003.12.10  �°�����
     2.��    ��  : 2011��03��30��
       ��    ��  : ŷ����
       �޸�����  : DTS2011032802556,�����쳣���������ͼ�Ȩ������Ϣ�����¼�Ȩʧ�ܣ�����Ч��
    3.��    ��  :2014��01��09��
      ��    ��  :l65478
      �޸�����  :DTS2014010704608:��һ�μ�Ȩ��Ӧ�����緢��ĵڶ��μ�Ȩ�����ͻ
 ************************************************************************/
VOS_VOID Gmm_TimProtectExpired(VOS_VOID)
{
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimProtectExpired:WARNING: Protected Timer is expired");

    /* �ȴ�USIM����Ȩ���������� */
    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
       == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;


        g_GmmAuthenCtrl.ucAuthenAttmptCnt++;

        if (GMM_AUTHEN_ATTEMPT_MAX_CNT == g_GmmAuthenCtrl.ucAuthenAttmptCnt)
        {
            Gmm_AuCntFail();            /* ��Ȩʧ�ܴ����������� */
        }
    }
}

/***********************************************************************
  Module   : Gmm_RcvTimerExpired
  Function : ��ʱ���������
  Input    : VOS_UINT8           ucTimerId     ��ʱ��ID
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1.  ��־��  2003.12.10  �°�����
     2. ��    ��   : 2006��11��8��
        ��    ��   : s46746
        �޸�����   : ���ⵥ��:A32D06867
     3. ��    ��   : 2009��5��9��
        ��    ��   : l00130025
        �޸�����   : �������ⵥ�ţ�AT2D11645/AT2D11797,�ػ�����detach��EST_REQʧ�ܣ�Gmm�ᷴ������EST_REQ
     4. ��    ��   : 2011��7��11��
        ��    ��   : sunxibo 46746
        �޸�����   : V7R1 phase II,autoplmnsrch״̬������ΪPlmnSelection״̬��
     5. ��    ��   : 2011��10��11��
        ��    ��   : l00171473
        �޸�����   : V7R1 phase II, TC���ص������ӳ���MMC�ظ�SUSPEND_RSP��ʱ����ʱ����
     6.��    ��   : 2012��4��17��
       ��    ��   : z00161729
       �޸�����  : DTS2012041402264��LС���·���CS����ҵ��ͨ���ض���CS Fallback��WС��������PDP���ͷ�CS������δ��ϵͳ��Ϣ��UE���ᷢ������RAU
     6. ��    ��   : 2012��5��15��
        ��    ��   : l00130025
        �޸�����   : DTS2012041002516: L��Ĭ�ϳ��ش�����������ʱ����W onlyʧ��
     7.��    ��   : 2012��8��13��
       ��    ��   : z00161729
       �޸�����   : DCM������������������޸�
     8.��    ��   : 2012��10��12��
       ��    ��   : w00176964
       �޸�����   : DTS2012091400694:Gģ�ػ���
     9.��    ��   : 2012��10��30��
       ��    ��   : s00217060
       �޸�����   : DTS2012050301830:����,�յ�MM��CsConnectIndʱ,���RRC���Ӵ���,��������RAU��
                    ����,�յ�������ϱ���ϵͳ��Ϣ����������RAU.
    10.��    ��   : 2013��6��6��
       ��    ��   : w00167002
       �޸�����   : V9R1_SVLTE��Ŀ�޸�
    11.��    ��   : 2013��06��28��
       ��    ��   : l00167671
       �޸�����   : DCM LOGGER��Ŀ��ʱ���¼��ϱ�
     2.��    ��   : 2014��12��25��
       ��    ��   : w00167002
       �޸�����   : DTS2014122201960:��L��SRVCC HO��G��HO��W,RABM�����ؽ�����������
                    ����RAU�������յ�ϵͳ��Ϣ���ٴη���RAU,��������REL����·������
                    �������޸�Ϊ��HO������������ʱ����ϵͳ��Ϣ��
    13.��    ��   : 2015��9��26��
       ��    ��   : c00318887
       �޸�����   : ��չGMM��ʱ����64��
 ************************************************************************/
VOS_VOID Gmm_RcvTimerExpired(
    VOS_UINT8                           ucTimerId
)
{
    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT8                           ucTimerBitIndex;
    
    NAS_INFO_LOG1(WUEPS_PID_GMM, "Gmm_RcvTimerExpired:INFO: Timer Expired: ", ucTimerId);

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
 

    /* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, begin */
    NAS_TIMER_EventReport(ucTimerId, WUEPS_PID_GMM, NAS_OM_EVENT_TIMER_OPERATION_EXPIRED);
    /* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, begin */

    /*lint -e701*/
    if (0 != ( (*pulTimerRunMask) & ( 0x00000001 << ucTimerBitIndex )))
    /*lint +e701*/
    {
        /* ָ��Timer�Ѿ�����  */
        Gmm_TimerStop(ucTimerId);
    }
    else
    {
        /* �ö�ʱ����ǰδ���� */
        NAS_WARNING_LOG1(WUEPS_PID_GMM, "Gmm_RcvTimerExpired:WARNING: The Timer hasn't been started: ", ucTimerId);
        return;
    }

    switch (ucTimerId)
    {
    case  GMM_TIMER_T3302:
        Gmm_Tim3302Expired();
        break;
    case  GMM_TIMER_T3310:
        Gmm_Tim3310Expired();
        break;
    case  GMM_TIMER_T3311:
        Gmm_Tim3311Expired();
        break;
    case  GMM_TIMER_T3312:
        Gmm_Tim3312Expired();
        break;
    case  GMM_TIMER_T3316:
        Gmm_Tim3316Expired();
        break;
    case  GMM_TIMER_T3317:
        Gmm_Tim3317Expired();
        break;
    case  GMM_TIMER_T3318:
        Gmm_Tim3318Expired();
        break;
    case  GMM_TIMER_T3319:
        Gmm_Tim3319Expired();
        break;
    case  GMM_TIMER_T3320:
        Gmm_Tim3320Expired();
        break;
    case  GMM_TIMER_T3321:
        Gmm_Tim3321Expired();
        break;
    case  GMM_TIMER_T3330:
        Gmm_Tim3330Expired();
        break;
    case  GMM_TIMER_1S:
        Gmm_Tim5sExpired();
        break;
    case  GMM_TIMER_PROTECT:
        Gmm_TimProtectExpired();
        break;
    case  GMM_TIMER_PROTECT_FOR_SIGNALING:
        Gmm_TimProtectForSignalingExpired();
        break;
    case  GMM_TIMER_SUSPENDED:
        GMM_LOG_WARN("GMM_TIMER_SUSPENDED expired.");
        GMM_TimSuspendedExpired();
        break;
    case  GMM_TIMER_T3314:
        GMM_TimReadyExpired();
        break;
    case  GMM_TIMER_RAU_RSP:
        GMM_TimRauRspExpired();
        break;
    case  GMM_TIMER_PROTECT_FOR_RR_REL:
        NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_RcvTimerExpired:WARNING: PROTECT_FOR_RR_REL Expired");
        GMM_TimProtectForRrRel();
        break;
    case  GMM_TIMER_PROTECT_OLD_TLLI:
        GMM_TimProtectForOldTlli();
        break;
    case  GMM_TIMER_T3340:
        NAS_GMM_Timer3340Expired();
        break;
    case  GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF:
        NAS_GMM_TimerWaitInterRatCnfExpired();
        break;

    case  GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF:
        NAS_GMM_TimerWaitReselSecuCnfExpired();
        break;

    case  GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF:
#if (FEATURE_ON == FEATURE_LTE)
        NAS_GMM_TimerWaitHoSecuCnfExpired();
#endif
        break;

    case GMM_TIMER_WAIT_CONNECT_REL:
        NAS_GMM_TimerWaitConnectRelExpired();
        break;

    case GMM_TIMER_TC_DELAY_SUSPEND_RSP:
        NAS_GMM_TimerTcDelaySuspendRspExpired();
        break;

    case GMM_TIMER_T3323:
#if (FEATURE_ON == FEATURE_LTE)
        NAS_GMM_Timer3323Expired();
#endif
        break;




#if (FEATURE_ON == FEATURE_LTE)
    case GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU:
        NAS_GMM_TimerDelayRadioCapaTrigedRauExpired();
        break;
#endif


    /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
#if (FEATURE_ON == FEATURE_LTE)
    case GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO:
        NAS_GMM_TimerWaitAsMsRadioCapaInfoExpired();
        break;
#endif
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

    /* GMM �ػ�detach��ʱ����ʱ */
    case GMM_TIMER_DETACH_FOR_POWER_OFF:
        NAS_GMM_TimerDetachForPowerOffExpired();
        break;


    /* GMM��PS��detach���̱�����ʱ����ʱ */
    case GMM_TIMER_PROTECT_PS_DETACH:
        NAS_GMM_TimerProtectPsDetachExpired();
        break;



    /* GMM��GMM_TIMER_HO_WAIT_SYSINFO������ʱ����ʱ */
    case GMM_TIMER_HO_WAIT_SYSINFO:
        NAS_GMM_TimerHoWaitSysinfoExpired();
        break;

#if (FEATURE_ON == FEATURE_LTE)
    case GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU:
        NAS_GMM_TimerDelayVoiceDomainTrigRauExpired();
        break;
#endif


    case GMM_TIMER_DELAY_PS_SMS_CONN_REL:
        NAS_GMM_RcvTiDelayPsSmsConnRelExpired();
        break;

    default:
        NAS_WARNING_LOG1(WUEPS_PID_GMM, "Gmm_RcvTimerExpired:WARNING: Unhandled TimerId: ", ucTimerId);
        break;
    }
}


/***********************************************************************
  Module   : Gmm_TimerPauseForTc
  Function : GMMʹ�õĶ�ʱ����ͣ(TC������)
  Input    : VOS_UINT8           ucTimerId     ��ʱ��ID
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1. ��־��  2004.06.18  �¹�����(TC��Ӧ)
 ************************************************************************/
VOS_VOID Gmm_TimerPauseForTc(
                         VOS_UINT8                   ucTimerId                      /* Timer ID                                 */
                         )
{
    VOS_UINT8    i;
    VOS_UINT32                         *pulTimerRunMask             = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask             = VOS_NULL_PTR;
    VOS_UINT32                         *pulTimerSusTcMask           = VOS_NULL_PTR;    
    VOS_UINT8                           ucTimerBitIndex;

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendMask(ucTimerId, &pulTimerSusMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendTcMask(ucTimerId, &pulTimerSusTcMask, &ucTimerBitIndex);

    /*lint -e701*/
    if (GMM_TIMER_ALL == ucTimerId)
    {
        for (i = 0; i < GMM_TIMER_NUM; i ++)
        {                                                                       /* ѭ����������TIMER                        */
            NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
            NAS_GMM_GetTimerSuspendMask(i, &pulTimerSusMask, &ucTimerBitIndex);
            NAS_GMM_GetTimerSuspendTcMask(i, &pulTimerSusTcMask, &ucTimerBitIndex);

            if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
            {                                                                   /* �ö�ʱ���Ѿ�����                         */

                if (0 == ((*pulTimerSusMask) & (0x00000001 << ucTimerBitIndex)))
                {                                                               /* �ö�ʱ��û�б�����                       */
                    if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                           Mm_StopRelTimer(WUEPS_PID_GMM, i, &g_GmmTimerMng.aTimerInf[i].hTimer))
                    {                                                           /* ֹͣʧ�ܣ��Ѿ�ֹͣ��Timer������          */
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerPauseForTc:WARNING: Stop all timer unsuccessfully");
                        return;                                                 /* ����                                     */
                    }

                    (*pulTimerSusTcMask) |= (0x00000001 << ucTimerBitIndex);        /* ��Timer�Ĺ����־(TC)                    */
                    
                    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerPauseForTc:INFO: StopTimer: ",i);
                }
            }
        }
    }
    else if (0 != ( (*pulTimerRunMask) & ( 0x00000001 << ucTimerBitIndex)))
    {                                                                           /* ��timer�Ѿ�����                          */
        if ((0 == ((*pulTimerSusTcMask) & (0x00000001 << ucTimerBitIndex)))
            &&(0 == ((*pulTimerSusMask) & (0x00000001 << ucTimerBitIndex))))
        {
            if( VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                 Mm_StopRelTimer(WUEPS_PID_GMM, ucTimerId, &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer))
            {                                                                   /* ��ͣʧ��                                 */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerPauseForTc:WARNING: Stop timer unsuccessfully");
                return;                                                         /* ����                                     */
            }
            (*pulTimerSusTcMask) |= (0x00000001 << ucTimerBitIndex);        /* ����Timer�Ĺ����־                      */
            PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerPauseForTc:INFO: StopTimer: ",ucTimerId);
        }
    }
    else
    {
    }
    /*lint +e701*/
    return;
}

/***********************************************************************
  Module   : Gmm_TimerResumeForTc
  Function : GMMʹ�õ���ͣ��Ķ�ʱ���Ļָ�(TC������)
  Input    : VOS_UINT8           ucTimerId     ��ʱ��ID
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1.  ��־��  2004.06.18  �¹�����(TC��Ӧ)
 ************************************************************************/
VOS_VOID Gmm_TimerResumeForTc(
                          VOS_UINT8                   ucTimerId                     /* Timer ID                                 */
                          )
{
    VOS_UINT8    i;
    VOS_UINT32                         *pulTimerRunMask             = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask             = VOS_NULL_PTR;
    VOS_UINT32                         *pulTimerSusTcMask           = VOS_NULL_PTR;    
    VOS_UINT8                           ucTimerBitIndex;

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendMask(ucTimerId, &pulTimerSusMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendTcMask(ucTimerId, &pulTimerSusTcMask, &ucTimerBitIndex);

    /*lint -e701*/
    if (GMM_TIMER_ALL == ucTimerId)
    {
        for (i = 0; i < GMM_TIMER_NUM; i ++)
        {                                                                       /* ѭ����������TIMER                        */
            NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
            NAS_GMM_GetTimerSuspendMask(i, &pulTimerSusMask, &ucTimerBitIndex);
            NAS_GMM_GetTimerSuspendTcMask(i, &pulTimerSusTcMask, &ucTimerBitIndex);

            if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
            {                                                                   /* �ö�ʱ���Ѿ�����                         */
                if (0 != ((*pulTimerSusTcMask) & (0x00000001 << ucTimerBitIndex)))
                {                                                               /* �ö�ʱ���Ѿ�����                         */
                    if (VOS_OK != Mm_StartRelTimer(
                                           &g_GmmTimerMng.aTimerInf[i].hTimer,     /* ���TIMER ID�ĵ�ַ                       */
                                           WUEPS_PID_GMM,
                                           g_GmmTimerMng.aTimerInf[i].ulTimerVal,         /* ʱ��                                     */
                                           (VOS_UINT32)i,            /* ��Ϣ���е�ID                             */
                                           g_GmmTimerMng.aTimerInf[i].ulParam,               /* ��Ϣ��ַ                                 */
                                           g_GmmTimerMng.aTimerInf[i].ucMode          /* ��Ϣ���ȼ�                               */
                                           ))
                    {                                                           /* �ָ�ʧ��                                 */
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerResumeForTc:WARNING: Start all timer unsuccessfully");
                        return;                                                 /* ����                                     */
                    }
                    
                    (*pulTimerSusTcMask)
                        &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);      /* ��Timer�Ĺ����־                        */
                    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerResumeForTc:INFO: StartTimer: ",i);
                }
            }
        }
    }
    else if (0 != ( (*pulTimerRunMask) & ( 0x00000001 << ucTimerBitIndex)))
    {                                                                           /* ��timer�Ѿ�����                          */
        if (0 != ((*pulTimerSusTcMask) & (0x00000001 << ucTimerBitIndex)))
        {
            if( VOS_OK != Mm_StartRelTimer(
                                &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer,     /* ���TIMER ID�ĵ�ַ                       */
                                WUEPS_PID_GMM,
                                g_GmmTimerMng.aTimerInf[ucTimerId].ulTimerVal,         /* ʱ��                                     */
                                (VOS_UINT32)ucTimerId,            /* ��Ϣ���е�ID                             */
                                g_GmmTimerMng.aTimerInf[ucTimerId].ulParam,               /* ��Ϣ��ַ                                 */
                                g_GmmTimerMng.aTimerInf[ucTimerId].ucMode          /* ��Ϣ���ȼ�                               */
                                ))
            {                                                                   /* �ָ�ʧ��                                 */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerResumeForTc:WARNING: Start timer unsuccessfully");
                return;                                                         /* ����                                     */
            }
            (*pulTimerSusTcMask)
                &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);      /* ����Timer�Ĺ����־                      */
            PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerResumeForTc:INFO: StartTimer: ",ucTimerId);
        }
    }
    else
    {
    }
    /*lint +e701*/
    return;
}

/***********************************************************************
Module   : Gmm_TimProtectForSignalingExpired
Function : GMM_TIMER_PROTECT_FOR_SIGNALING �������
Input    : ��
Output   : ��
NOTE     : ��
Return   : ��
History  :
1. ��־��  2005.01.10  �°�����
2. ��    ��   : 2007��11��1��
   ��    ��   : l65478
   �޸�����   : A32D13307, ����SR���̳�ʱ��Ĵ���
 3.��    ��   : 2012��3��17��
   ��    ��   : w00176964
   �޸�����   : DTS2012031900095 V7R1 C30 SBM&EM��������:���Ӳ��ű��ܶ���
 4.��    ��   : 2012��08��24��
   ��    ��   : m00217266
   �޸�����   : �޸�GMM_SndSmServiceRej�ӿڣ����ԭ��ֵ

************************************************************************/
VOS_VOID Gmm_TimProtectForSignalingExpired(VOS_VOID)
{
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimProtectForSignalingExpired:WARNING: Protected timer for signalling is expired");
    GMM_SndRrmmRelReqGsm();

    /* ��ȡ���ű��ܶ����Ƿ�ʹ�� */
    if (VOS_TRUE == NAS_MML_GetDailRejectCfg())
    {
        GMM_SndSmServiceRej(GMM_SM_CAUSE_TIMER_SIGNALING_PROTECT_EXPIRED);

        g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
    }
}

/***********************************************************************
Module   : GMM_TimProtectForRrRel
Function : GMM_TIMER_PROTECT_FOR_RR_REL �������
Input    : ��
Output   : ��
NOTE     : ��
Return   : ��
History  :
1. s46746  2006.03.27  Create
2. ��    ��   : 2007��01��25��
   ��    ��   : s46746
   �޸�����   : �������������ⵥ�ţ�A32D07433
3. ��    ��   : 2007��03��20��
   ��    ��   : x51137
   �޸�����   : A32D09192
4.��    ��   : 2011��07��13��
  ��    ��   : w00166186
  �޸�����   : V7R1 PHASE II ATTACH/DETACH����
5. ��    ��   : 2012��1��12��
   ��    ��   : w00166186
   �޸�����   : DTS2011122704039:����������CSע�ᱻ��#12,PSע�ᱻ��#14����ON
                 PLMN״̬������������Ϊ��֧��GMM��Ҫ��������֧����Ϣ֪ͨ��MMC.
6.��    ��   : 2013��8��7��
  ��    ��   : w00167002
  �޸�����   : DTS2013080207367:��CS onlyʱ���û�����PDP�������ģʽIʱ��
                 �ᴥ������ע��.�û�����PDPȥ����ᵼ��PS���ȥע�ᡣ�յ�����
                 ��ȥע��ɹ�����Ҫ֪ͨMM������MM��ǰ��NORMAL SERVICE״̬����
                 ����T3212��ʱ������������ʱ����ܵ��¶�Ѱ��.
7.��    ��   : 2015��3��27��
  ��    ��   : wx270776
  �޸�����   : DTS2015022804322: ������ʱ����ʱ��W�´�����������ʱ��֪ͨPS�����·�ͷ�
************************************************************************/
VOS_VOID GMM_TimProtectForRrRel()
{
    RRMM_REL_IND_STRU *prrmm_rel_ind;

    if ( GMM_ABORT_CURRENT_SERVICE == g_GmmGlobalCtrl.ucSpecProc )
    {
        prrmm_rel_ind = (RRMM_REL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM, sizeof(RRMM_REL_IND_STRU) );
        if ( VOS_NULL_PTR == prrmm_rel_ind )
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
        }
        else
        {
            prrmm_rel_ind->MsgHeader.ulSenderPid = WUEPS_PID_WRR;
            prrmm_rel_ind->MsgHeader.ulMsgName = RRMM_REL_IND;
            prrmm_rel_ind->ulCnDomainId = RRC_NAS_PS_DOMAIN;
            prrmm_rel_ind->ulRelCause = RRC_REL_CAUSE_NAS_ABORT;
            prrmm_rel_ind->ulRrcConnStatus = RRC_RRC_CONN_STATUS_ABSENT;

            Gmm_RcvRrmmRelInd(prrmm_rel_ind);

            PS_FREE_MSG(WUEPS_PID_GMM, prrmm_rel_ind);

        }

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;

        return;
    }

    if (GMM_DEREGISTERED_INITIATED != g_GmmGlobalCtrl.ucState)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "GMM_TimProtectForRrRel:WARNING: Gmm State is unexpected.");
        return;
    }

    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                             /* ����״̬�Ĺ�������                       */

    if (GMM_DETACH_NORMAL_NETMODE_CHANGE != g_GmmGlobalCtrl.ucSpecProc)
    {
        NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);          /* ����PS���ֹע���־                     */
    }

    if (GMM_UEID_P_TMSI_SIGNATURE
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {                                                                           /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;   /* ���P_TMSI_SIGNATURE                     */

        NAS_MML_InitUeIdPtmsiSignatureInvalid();

        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
    }
    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
    {
        /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
        NAS_GMM_SndMmGprsDetachComplete();
    }
    else
    {

    }


    /* ��MMC����PSע���� */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

	/* W�´�����������ʱ��֪ͨPS�����·�ͷ� */
	if ( (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
		&& (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg) )
	{
		Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
	}
}

/***********************************************************************
Module   : GMM_TimSuspendedExpired
Function : GMM_TIMER_SUSPENDED �������
Input    : ��
Output   : ��
NOTE     : ��
Return   : ��
History  :
 1. s46746  2006.03.27  Create
 2.��    ��   : 2011��7��12��
   ��    ��   : h44270
   �޸�����   : V7R1 PhaseII�׶ε�����ȫ�ֱ�����������Ҫ�޸���Ӧ�ĳ�ʱ����
************************************************************************/
VOS_VOID GMM_TimSuspendedExpired()
{
    switch(g_GmmGlobalCtrl.ucState)
    {
        case GMM_SUSPENDED_NORMAL_SERVICE:
            GMM_LOG_INFO("GMM_TimSuspendedExpired:MMC is still suspended.");
            Gmm_TimerStart(GMM_TIMER_SUSPENDED);
            break;

        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            GMM_LOG_WARN("GMM_TimSuspendedExpired:MMC have not get sys info.");
            g_GmmRauCtrl.ucNpduCnt = 0x0;
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
            {
                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
            }
            else
            {
#if 0
                GMM_SndRabmGprsInfoInd(GMM_RABM_GPRS_SUPPORTED, GMM_RABM_PROC_HANDOVER,
                               GMM_RABM_IMMEDIATELY_RAU);
#endif

                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
            }
            Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
            GMM_ResumeTimer(GMM_TIMER_RESUME);
            GMM_ResumeFailure();
            break;
        default:
            GMM_LOG_WARN("GMM_TimSuspendedExpired:Receive GMM_TIMER_SUSPENDED in abnormal state.");
            break;
    }
    return;
}

/***********************************************************************
Module   : GMM_TimProtectForOldTlli
Function : GMM_TIMER_PROTECT_FOR_OLD_TLLI �������
Input    : ��
Output   : ��
NOTE     : ��
Return   : ��
History  :
1. s46746  2006.11.08  Create for A32D06867
       10.  ��    ��   : 2006��11��20��
            ��    ��   : s46746
            �޸�����   : �������������ⵥ�ţ�A32D07433
************************************************************************/
VOS_VOID GMM_TimProtectForOldTlli()
{
    Gmm_TimerStop(GMM_TIMER_PROTECT_OLD_TLLI);
    GMM_FreeOldTlli();
    gstGmmCasGlobalCtrl.ulOldTLLI = 0xffffffff;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_TimerWaitInterRatCnfExpired
 ��������  : ��ʱ��GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF��ʱ����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��27��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������
  3.��    ��   : 2014��7��18��
    ��    ��   : b00269685
    �޸�����   : DSDS IV�޸�

*****************************************************************************/
VOS_VOID NAS_GMM_TimerWaitInterRatCnfExpired( VOS_VOID )
{
    NAS_MSG_STRU                            *pstSendNasMsg = VOS_NULL_PTR;

    g_GmmInterRatInfoCtrl.ucInterRatCnfMsgRcvdFlg = VOS_TRUE;

    if (VOS_TRUE == g_GmmInterRatInfoCtrl.ucAttachCmpWaitInterRatCnfMsg)
    {
        if (VOS_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {
            /* ATTACH��������SM������,֪ͨSM GMMע��ɹ�,����ucSmCnfFlg��־ */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);
            g_GmmAttachCtrl.ucSmCnfFlg = VOS_FALSE;
        }

        /* �ظ�����Attach Complete ��Ϣ */
        pstSendNasMsg = Gmm_AttachCompleteMsgMake();

        if (VOS_NULL_PTR == pstSendNasMsg)
        {
            NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvInterRatHandoverInfoCnf: Make Attach Complete Msg Fail!");
            return;
        }
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pstSendNasMsg);

    }
    else if (VOS_TRUE == g_GmmInterRatInfoCtrl.ucRauCmpWaitInterRatCnfMsg)
    {
        /* ����Ҫ�ȴ�RABM�Ļظ���Ϣ�������Ѿ��յ�RABM�Ļظ���Ϣ������RAU���̽�������Ӧ���� */
        if (   (VOS_FALSE == gstGmmCasGlobalCtrl.ucWaitRabmRauRspFlg)
            || (VOS_TRUE == gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg))
        {
            NAS_GMM_RauCompleteHandling();
        }
    }
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvInterRatHandoverInfoCnf: Not Expected Msg Received.");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_TimerWaitReselSecuCnfExpired
 ��������  : GMM��ȡLMM��ȫ������ʱ����ʱ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��14��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��2��
    ��    ��   : s46746
    �޸�����   : ��L��ϵͳ�ı䵽GU��û��ָ�ɼ�����Կ��GU�����
  3.��    ��   : 2012��3��17��
    ��    ��   : w00176964
    �޸�����   : DTS2012031308021:[GCF����]L2U��ѡ,Я��RAU request��������Ϣ
                 �е�RAU�����Լ�PTMSI���ʹ���

*****************************************************************************/
VOS_VOID  NAS_GMM_TimerWaitReselSecuCnfExpired( VOS_VOID )
{
    if (NAS_GMM_SPEC_PROC_RAU == NAS_GMM_GetSpecProcNeedSecInfo())
    {
        Gmm_SndRoutingAreaUpdateReq(NAS_GMM_GetRauUpdateType());
    }
    else
    {
        Gmm_SndAttachReq();
    }

    NAS_GMM_SetLmmSecInfoFlg(VOS_FALSE);

    g_GmmInterRatCellReselect = 0;

    /* ��Ҫ��ȡ��ȫ������ʱ,����ǰ�Ľ��뼼���ӳٸ��� */
    gstGmmSuspendCtrl.ucPreRat = NAS_MML_GetCurrNetRatType();

    NAS_GMM_SetSpecProcNeedSecInfo(NAS_GMM_SPEC_PROC_BUTT);
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_GMM_TimerWaitHoSecuCnfExpired
 ��������  : GMM��ȡLMM��ȫ������ʱ����ʱ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��20��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��2��
    ��    ��   : s46746
    �޸�����   : ��L��ϵͳ�ı䵽GU��û��ָ�ɼ�����Կ��GU�����
*****************************************************************************/
VOS_VOID  NAS_GMM_TimerWaitHoSecuCnfExpired( VOS_VOID )
{
    /* �����ʱ��GMM�Ĺ���״̬�����ҹ�����ΪLTE������MMC�ظ�����ظ� */
    if ( (NAS_MML_NET_RAT_TYPE_LTE     == NAS_MML_GetCurrNetRatType())
      && (GMM_SUSPENDED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
    {
        Gmm_TimerStart(GMM_TIMER_SUSPENDED);

        GMM_SndMmcSuspendRsp();
    }

}

/*****************************************************************************
 �� �� ��  : NAS_GMM_Timer3323Expired
 ��������  : T3323��ʱ����ʱ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��7��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_Timer3323Expired(VOS_VOID)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /* 3GPP 24.008 4.7.2.2�½�������
       After expiry of timer T3323 the MS shall deactivate ISR by setting
       its TIN to "GUTI". */
    if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == pstRplmnCfgInfo->enTinType)
    {
        NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_GUTI, pstRplmnCfgInfo->aucLastImsi);
        Gmm_TimerStop(GMM_TIMER_T3323);

        /* ISRȥ�����Ҫ����pdp��������ISR����ǰ����� */
        NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
    }
    return;
}

#endif

/* �յ�MM��CsConnectIndʱ,���RRC���Ӵ���,��������RAU��
   ����,�յ�������ϱ���ϵͳ��Ϣ����������RAU */

/*****************************************************************************
 �� �� ��  : NAS_GMM_TimerWaitConnectRelExpired
 ��������  : �ȴ����������ͷŵı�����ʱ����ʱ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2011��7��11��
    ��    ��  : s46746
    �޸�����  : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_TimerWaitConnectRelExpired()
{
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_TimerWaitConnectRelExpired:WARNING: Wait connect rel expired.");

    if ((GMM_DEREGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState)
     && (GMM_REGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState))
    {
        return;
    }

    /* �����ǰפ��WCDMA������MMCָʾ���Ӳ����ڣ�������MMCָʾTBF�ͷ� */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        /* ����PS�������Ӳ����� */
        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);

        /* ��MMC�������Ӳ�������Ϣ */
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

        NAS_GMM_ClearGmmLinkCtrlStru();
    }
    else
    {
        /* ����TBF���Ӳ����� */
        NAS_MML_SetPsTbfStatusFlg(VOS_FALSE);

        /* ��MMC�������Ӳ�������Ϣ */
        Gmm_SndMmcTBFRelInd();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_TimerTcDelaySuspendRspExpired
 ��������  : �ӳ���MMC�ظ�SUSPEND_RSP�Ķ�ʱ����ʱ�Ĵ���
             ����TC״̬��GCF�����У��Դﵽ�ӳ�������ظ�SUSPEND_RSP��
             GMM�ӳ���MMC�ظ�SUSPEND_RSP, ������Ӧ��������ظ�SUSPEND_RSPҲ�ӳ��ˡ�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��9��14��
   ��    ��   : L00171473
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_GMM_TimerTcDelaySuspendRspExpired(VOS_VOID)
{
#if (defined(__PS_WIN32_RECUR__)) || ( VOS_WIN32 == VOS_OS_VER )
    if (1 == g_ulGmmDelaySuspendRsp)
    {
        Gmm_TimerStart(GMM_TIMER_SUSPENDED);

        GMM_SndMmcSuspendRsp();

        return;
    }
#endif

    /* ���ڴ˴�״̬��Ǩ�ƣ���ʹ���л�֮ǰGMM״̬�����жϡ� */
    if (GMM_TC_ACTIVE != gstGmmSuspendCtrl.ucPreState)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_TimerTcDelaySuspendRspExpired:WARNING: Expired NOT GMM_TC_ACTIVE STATE");
        return;
    }

    Gmm_TimerStart(GMM_TIMER_SUSPENDED);

    GMM_SndMmcSuspendRsp();
}

#if (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 �� �� ��  : NAS_GMM_CheckRadioAccessCapaTrigedRAU
 ��������  : ���յ�Gas������RadioAccessCapability���ϴβ�ͬʱ���ж�ǰ���RAT�仯�Ƿ���Ҫ����RAU;
              Ŀǰֻ��ģʽ����Lģʱ������Ӧ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��Ҫ����RAU,VOS_FALSE:����Ҫ����RAUs
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012041002516: L��Ĭ�ϳ��ش�����������ʱ����W onlyʧ��,
                  GU�½��������仯ʱ����Ҫ����һ��RAU����
*****************************************************************************/
VOS_UINT32 NAS_GMM_CheckRatTrigedRAU(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstOldRatList,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstNewRatList
)
{
    VOS_UINT32                          ulLteExistInOldRatList;
    VOS_UINT32                          ulLteExistInNewRatList;
    VOS_UINT32                          ulWExistInNewRatLList;
    VOS_UINT32                          ulGExistInNewRatLList;

    /* ��ǰ����GUģ��ģʽ�仯�漰�����ӻ����Lģʱ������RAU,��������£������� */
    ulLteExistInOldRatList = NAS_MML_IsSpecRatInRatList(NAS_MML_NET_RAT_TYPE_LTE,
                                                        pstOldRatList);
    ulLteExistInNewRatList = NAS_MML_IsSpecRatInRatList(NAS_MML_NET_RAT_TYPE_LTE,
                                                        pstNewRatList);
    ulWExistInNewRatLList  = NAS_MML_IsSpecRatInRatList(NAS_MML_NET_RAT_TYPE_WCDMA,
                                                        pstNewRatList);
    ulGExistInNewRatLList  = NAS_MML_IsSpecRatInRatList(NAS_MML_NET_RAT_TYPE_GSM,
                                                        pstNewRatList);

    if (ulLteExistInOldRatList != ulLteExistInNewRatList)
    {
        if ((VOS_TRUE == ulWExistInNewRatLList)
         || (VOS_TRUE == ulGExistInNewRatLList))
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_GMM_TimerDelayRadioCapaTrigedRauExpired
 ��������  : SYSCFG���ú�,���RadioCapa�ı��Ƿ���Ҫ����RAU,��Ҫʱ������RAU
             Ŀǰ RAU����best Effort���ԣ��������𣬲��ܷ���ʱ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��5��15��
   ��    ��   : l00130025
   �޸�����   : DTS2012041002516: L��Ĭ�ϳ��ش�����������ʱ����W onlyʧ��
 2.��    ��   : 2012��8��15��
   ��    ��   : z00161729
   �޸�����   : DCM������������������޸�
 3.��    ��   : 2013��05��08��
   ��    ��   : s46746
   �޸�����   : SS FDN&Call Control��Ŀ��lte�����ı��CSҵ���������������RAU
*****************************************************************************/
VOS_VOID NAS_GMM_TimerDelayRadioCapaTrigedRauExpired(VOS_VOID)
{
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
    /* rau��attach��ms radio capa IE��Я����LTE���������������ϱ���LTE������һ�£���Ҫ����rau */
    if (g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs == g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq)
    {
        return;
    }

    NAS_GMM_HandleMsRadioCapLteSupportChanged();

    return;
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

}

/* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
/*****************************************************************************
 �� �� ��  : NAS_GMM_TimerWaitAsMsRadioCapaInfoExpired
 ��������  : GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO��ʱ����ʱ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��15��
   ��    ��   : z00161729
   �޸�����   : ��������
 2.��    ��   : 2013��9��2��
    ��    ��  : z00161729
    �޸�����  : DTS2013082702039:syscfg��֧��l��l disableʱ��gmm rau��attach����Я��ue network capability
 3.��    ��   : 2014��02��25��
   ��    ��   : z00161729
   �޸�����   : DTS2014022206794:GCF 9.2.1.2.1b/9.2.3.2.3/9.2.1.2.1ʧ��disable lteʱrau��Ҫ��L��ȡ��ȫ������

*****************************************************************************/
VOS_VOID NAS_GMM_TimerWaitAsMsRadioCapaInfoExpired(VOS_VOID)
{
    VOS_UINT32                          ulGetLmmSecInfoFlg;

    VOS_UINT32                          ucIsSupportLteCapaFlg;

    VOS_UINT8                           ucLDisabledUseLInfoFlag;

    ucLDisabledUseLInfoFlag = NAS_MML_GetLteDisabledRauUseLteInfoFlag();

    ucIsSupportLteCapaFlg  = NAS_MML_IsSupportLteCapability();

    ulGetLmmSecInfoFlg = NAS_GMM_GetLmmSecInfoFlg();

    /* l disabled attach ����l��ȡ��ȫ�����ģ� l disabled rau nv�����Ƿ���Ҫ��l��ȡ��ȫ������*/
    if ((NAS_MML_TIN_TYPE_GUTI == NAS_MML_GetTinType())
     && (VOS_FALSE == gstGmmSuspendCtrl.ucGetLteSecContext)
     && (VOS_FALSE == ulGetLmmSecInfoFlg)
     && ((VOS_TRUE == ucIsSupportLteCapaFlg)
      || ((VOS_TRUE == ucLDisabledUseLInfoFlag)
       && (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState))))
    {
        NAS_GMM_SetSpecProcNeedSecInfo(NAS_GMM_SPEC_PROC_RAU);
        NAS_GMM_SetLmmSecInfoFlg(VOS_TRUE);

        if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            NAS_GMM_SetSpecProcNeedSecInfo(NAS_GMM_SPEC_PROC_RAU);
        }

        if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            NAS_GMM_SetSpecProcNeedSecInfo(NAS_GMM_SPEC_PROC_ATTACH);
        }

        /* ��Lģ����GMM_LMM_RESEL_SECU_INFO_REQ */
        NAS_GMM_SndLmmReselSecuInfoReq();

        /* ������ʱ�� */
        Gmm_TimerStart(GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF);

        return;
    }

    if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_SndRoutingAreaUpdateReq(NAS_GMM_GetRauUpdateType());
        return;
    }

    if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_SndAttachReq();
    }
    return;
}

/* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

/*****************************************************************************
 �� �� ��  : NAS_GMM_IsNeedStartT3323
 ��������  : �Ƿ���Ҫ����T3323��ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ
             VOS_FALSE - ����Ҫ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��10��22��
   ��    ��   : z00161729
   �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 NAS_GMM_IsNeedStartT3323(VOS_VOID)
{
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    VOS_UINT8                           ucIsNeedStartT3323;

    enTinType          = NAS_MML_GetTinType();
    ucIsNeedStartT3323 = VOS_FALSE;

    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_REGISTERED_LIMITED_SERVICE:
        case GMM_REGISTERED_NO_CELL_AVAILABLE:
        case GMM_DEREGISTERED_ATTACH_NEEDED:
        case GMM_REGISTERED_UPDATE_NEEDED:

             /* GMM����GMM_REGISTERED_NO_CELL_AVAILABLE��GMM_REGISTERED_LIMITED_SERVICE��ISR���
                ��Ҫ����T3323��ʱ��,GMM����ע�ᱻbar״̬��ISR�����Ҫ����T3323��ʱ�� */
            if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType)
            {
                ucIsNeedStartT3323 = VOS_TRUE;
            }
            break;

        case GMM_REGISTERED_PLMN_SEARCH:

            /* GMM����ʱ����GMM_REGISTERED_PLMN_SEARCH��ISR�����Ҫ����T3323��ʱ����
               ���������米���ѵĿ���ָ����״̬ISR������������T3323  */
            if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
             && (GMM_TRUE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
            {
                ucIsNeedStartT3323 = VOS_TRUE;
            }
            break;

        default:
            break;
    }

    return ucIsNeedStartT3323;
}

#endif



/*****************************************************************************
 �� �� ��  : NAS_GMM_TimerHoWaitSysinfoExpired
 ��������  : GMM_TIMER_HO_WAIT_SYSINFO������ʱ����ʱ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��15��
   ��    ��   : s00217060
   �޸�����   : ��������
*****************************************************************************/
VOS_VOID NAS_GMM_TimerHoWaitSysinfoExpired(VOS_VOID)
{
    /* �л�����һ����ҵ��ʱ�Ż��У�PS�򲻱�ע��ɹ������̣���CS�ϱ�����֤פ����Ϣ���ź�ǿ�ȸ��£�����IMSA���ܻ���ǰȥ����IMSA
       ����:L2G��SRVCC,CMCCҪ��绰����֮�󣬲���ȥע��IMSA��
       ��ʱ����������̣�MMC�ͻ�֪ͨMMAע��״̬�ͷ���״̬��MMA�ͻ�֪ͨIMSA����״̬�仯 */
    /* ��ǰ����GMM_SUSPENDED_WAIT_FOR_SYSINFO״̬������Ҫ����  */
    if ( GMM_SUSPENDED_WAIT_FOR_SYSINFO != Gmm_GetState() )
    {
        return ;
    }

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        return;
    }

    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);

    return;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_GMM_TimerDelayVoiceDomainTrigRauExpired
 ��������  : GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU������ʱ����ʱ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��12��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : User_Exp_Improve�޸�
*****************************************************************************/
VOS_VOID NAS_GMM_TimerDelayVoiceDomainTrigRauExpired(VOS_VOID)
{
    /* ���Э���½�:
    3GPP 24008:
    4.7.5.1 Normal and periodic routing area updating procedure

    The normal routing area updating procedure is initiated:
    ......
    -    when the UE's usage setting or the voice domain preference for E-UTRAN change in the MS;
    ......
    */

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;
    VOS_INT8                  cVersion;

    cVersion        = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);
    pstConnStatus   = NAS_MML_GetConnStatus();

    if (cVersion < PS_PTL_VER_R9)
    {
        return;
    }

    /* voice domain���ϴη���ע��ʱ����ͬ������Ҫ����RAU */
    if (g_GmmGlobalCtrl.UeInfo.enVoiceDomainFromRegReq == NAS_MML_GetVoiceDomainPreference())
    {
        return;
    }

    /* �������CSҵ����ֱ�ӷ��� */
    if (VOS_TRUE == pstConnStatus->ucCsServiceConnStatusFlg)
    {
        return;
    }

    /* ������ڷ���CSҵ����������ʱ����ҵ����ʧ��������ʱ������RAU��
       ҵ����ɹ���ʱ����ʱʱ��ֱ�ӷ��� */
    if ((VOS_TRUE == NAS_MML_GetCsServiceBufferStatusFlg())
     && (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg))
    {
        Gmm_TimerStart(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);

        return;
    }

    if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        return;
    }

    if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        Gmm_TimerStart(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);
    }

    return;
}
#endif


/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvTiDelayPsSmsConnRelExpired
 ��������  : GMM_TIMER_DELAY_PS_SMS_CONN_REL��ʱ����ʱ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��23��
    ��    ��   : c00318887
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_GMM_RcvTiDelayPsSmsConnRelExpired(VOS_VOID)
{
    if (VOS_TRUE == NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer())
    {
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
    }

    return;    
}

/***********************************************************************
  Module   : NAS_GMM_GetTimerRunMask
  Function : GMMʹ�õĶ�ʱ������
  Input    : VOS_UINT8           ucTimerId     ��ʱ��ID
  Output   : 
             VOS_UINT32    **pulTimerRunMask   �ö�ʱ��RunMask ��ʾλ�ĳ�Ա: g_GmmTimerMng.ulTimerRunMask �� g_GmmTimerMng.ulTimerRunMaskEx
             VOS_UINT8      *pucTimerBitIndex  �ö�ʱ���ڱ�ʾλ������
  NOTE     : ��
  Return   : ��
  History  :
  1.��    ��   : 2015��9��26��
    ��    ��   : c00318887
    �޸�����   : �½�����
 ************************************************************************/
VOS_VOID NAS_GMM_GetTimerRunMask(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                        **pulTimerRunMask,  
    VOS_UINT8                          *pucTimerBitIndex
)
{
    if (ucTimerId < GMM_TIMER_ONE_GROUP_NUMR)
    {
        (*pulTimerRunMask)              = &g_GmmTimerMng.ulTimerRunMask;
        (*pucTimerBitIndex)             = ucTimerId;
    }
    else
    {
        (*pulTimerRunMask)              = &g_GmmTimerMng.ulTimerRunMaskEx;
        (*pucTimerBitIndex)             = ucTimerId - GMM_TIMER_ONE_GROUP_NUMR;
    }
}

/***********************************************************************
  Module   : NAS_GMM_GetTimerSuspendMask
  Function : GMMʹ�õĶ�ʱ������
  Input    : VOS_UINT8           ucTimerId     ��ʱ��ID
  Output   : 
             VOS_UINT32    **pulTimerSusMask   �ö�ʱ��SusMask ��ʾλ�ĳ�Ա: g_GmmTimerMng.ulTimerSusMask �� g_GmmTimerMng.ulTimerSusMaskEx
             VOS_UINT8      *pucTimerIndex     �ö�ʱ���ڱ�ʾλ������
  NOTE     : ��
  Return   : ��
  History  :
  1.��    ��   : 2015��9��26��
    ��    ��   : c00318887
    �޸�����   : �½�����
 ************************************************************************/
VOS_VOID NAS_GMM_GetTimerSuspendMask(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                        **pulTimerSusMask,  
    VOS_UINT8                          *pucTimerBitIndex 
)
{
    if (ucTimerId < GMM_TIMER_ONE_GROUP_NUMR)
    {
        (*pulTimerSusMask)              = &g_GmmTimerMng.ulTimerSusMask;
        (*pucTimerBitIndex)             = ucTimerId;
    }
    else
    {
        (*pulTimerSusMask)              = &g_GmmTimerMng.ulTimerSusMaskEx;
        (*pucTimerBitIndex)             = ucTimerId - GMM_TIMER_ONE_GROUP_NUMR;
    }
}


/***********************************************************************
  Module   : NAS_GMM_GetTimerSuspendTcMask
  Function : GMMʹ�õĶ�ʱ������
  Input    : VOS_UINT8       ucTimerId     ��ʱ��ID
  Output   : 
             VOS_UINT32    **pulTimerSusTcMask   �ö�ʱ��ulTimerSusTcMask ��ʾλ�ĳ�Ա: g_GmmTimerMng.ulTimerSusTcMask �� g_GmmTimerMng.ulTimerSusTcMaskEx
             VOS_UINT8      *pucTimerBitIndex    �ö�ʱ���ڱ�ʾλ������
  NOTE     : ��
  Return   : ��
  History  :
  1.��    ��   : 2015��9��26��
    ��    ��   : c00318887
    �޸�����   : �½�����
 ************************************************************************/
VOS_VOID NAS_GMM_GetTimerSuspendTcMask(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                        **pulTimerSusTcMask,  
    VOS_UINT8                          *pucTimerBitIndex 
)
{
    if (ucTimerId < GMM_TIMER_ONE_GROUP_NUMR)
    {
        (*pulTimerSusTcMask)            = &g_GmmTimerMng.ulTimerSusTcMask;
        (*pucTimerBitIndex)             = ucTimerId;
    }
    else
    {
        (*pulTimerSusTcMask)            = &g_GmmTimerMng.ulTimerSusTcMaskEx;
        (*pucTimerBitIndex)             = ucTimerId - GMM_TIMER_ONE_GROUP_NUMR;
    }
}

/***********************************************************************
  Module   : NAS_GMM_GetTimerSuspendTcMask
  Function : GMMʹ�õĶ�ʱ������
  Input    : VOS_UINT8       ucTimerId     ��ʱ��ID
  Output   : 
             VOS_UINT32    **pulTimerRunMask   �ö�ʱ��ulTimerValMask ��ʾλ�ĳ�Ա: g_GmmTimerMng.ulTimerValMask �� g_GmmTimerMng.ulTimerValMaskEx
             VOS_UINT8      *pucTimerIndex     �ö�ʱ���ڱ�ʾλ������
  NOTE     : ��
  Return   : ��
  History  :
  1.��    ��   : 2015��9��26��
    ��    ��   : c00318887
    �޸�����   : �½�����
 ************************************************************************/
VOS_VOID NAS_GMM_GetTimerValMask(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                        **pulTimerValMask,  
    VOS_UINT8                          *pucTimerBitIndex
)
{
    if (ucTimerId < GMM_TIMER_ONE_GROUP_NUMR)
    {
        (*pulTimerValMask)              = &g_GmmTimerMng.ulTimerValMask;
        (*pucTimerBitIndex)             = ucTimerId;
    }
    else
    {
        (*pulTimerValMask)              = &g_GmmTimerMng.ulTimerValMaskEx;
        (*pucTimerBitIndex)             = ucTimerId - GMM_TIMER_ONE_GROUP_NUMR;
    }
}
/***********************************************************************
  Module   : NAS_GMM_GetTimerSuspendCtrlRunMask
  Function : GMMʹ�õĶ�ʱ������
  Input    : VOS_UINT8       ucTimerId     ��ʱ��ID
  Output   : 
             VOS_UINT32    **pulSuspendCtrlRunMask   �ö�ʱ��TimerSusTcMask ��ʾλ�ĳ�Ա: gstGmmSuspendCtrl.ulTimerRunMask �� gstGmmSuspendCtrl.ulTimerRunMaskEx
             VOS_UINT8      *pucTimerBitIndex     �ö�ʱ���ڱ�ʾλ������
  NOTE     : ��
  Return   : ��
  History  :
  1.��    ��   : 2015��9��26��
    ��    ��   : c00318887
    �޸�����   : �½�����
 ************************************************************************/
VOS_VOID NAS_GMM_GetTimerSuspendCtrlRunMask(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                        **pulSuspendCtrlRunMask,  
    VOS_UINT8                          *pucTimerBitIndex 
)
{
    if (ucTimerId < GMM_TIMER_ONE_GROUP_NUMR)
    {
        (*pulSuspendCtrlRunMask)        = &gstGmmSuspendCtrl.ulTimerRunMask;
        (*pucTimerBitIndex)             = ucTimerId;
    }
    else
    {
        (*pulSuspendCtrlRunMask)        = &gstGmmSuspendCtrl.ulTimerRunMaskEx;
        (*pucTimerBitIndex)             = ucTimerId - GMM_TIMER_ONE_GROUP_NUMR;
    }
}


/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

