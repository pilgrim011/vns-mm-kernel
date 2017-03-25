/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcTimer.c
  �� �� ��   : ����
  ��    ��   : zhoujun 40661
  ��������   : 2011��5��30��
  ����޸�   : 2011��5��30��
  ��������   : ����MMC��ʱ�����Լ����г�ʱ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��5��30��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ļ�
  2.��    ��   : 2012��1��30��
    ��    ��   : l00130025
    �޸�����   : DTS2012010500368,����ͬ���ӿ�VOS_GetRelTmRemainTimehTimer,
                  ɾ��NAS_MMC_GetTimerRemainLen/NAS_MMC_SetTimerStopStatus

****************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "vos.h"
#include "Ps.h"
#include "NasComm.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmcCtx.h"
#include "NasMmcSndOm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 ��������
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define THIS_FILE_ID PS_FILE_ID_NASMMC_TIMERMGMT_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/

/* ���������޾��ȶ�ʱ����Ϣ��Ĭ��32k */
NAS_TIMER_PRECISION_STRU g_stNasMmcTimerPrcision[]=
{
   {WUEPS_PID_MMC,  TI_NAS_MMC_TIMER_BUTT,       VOS_TIMER_NO_PRECISION},
};

/*lint -save -e958 */

/*****************************************************************************
  6 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitAllTimers
 ��������  : ��ʼ�����ж�ʱ����Ӧ��MMC��ʼ����Resetʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��30��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_MMC_InitAllTimers(
    NAS_MMC_TIMER_CTX_STRU              *pstMmcTimerCtx
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < NAS_MMC_MAX_TIMER_NUM ; i++ )
    {
        pstMmcTimerCtx[i].hTimer        = VOS_NULL_PTR;
        pstMmcTimerCtx[i].enTimerId     = TI_NAS_MMC_TIMER_BUTT;
        pstMmcTimerCtx[i].enTimerStatus = NAS_MMC_TIMER_STATUS_STOP;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_StartTimer
 ��������  : ����ָ����MMC��ʱ��
 �������  : enTimerId - ��Ҫ�����Ķ�ʱ��ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��5��30��
   ��    ��   : zhoujun 40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2011��5��30��
   ��    ��   : w00167002
   �޸�����   : ���Ӷ�ʱ����ʱ����ӡ

 3.��    ��   : 2012��11��7��
   ��    ��   : l00167671
   �޸�����   : ���ӷ���ֵ���Ա��ڵ�����֪���Ƿ�������ʱ���ɹ���
                DTS2012110607212
 4.��    ��   : 2013��6��14��
   ��    ��   : z00161729
   �޸�����   : SVLTE ��usim�ӿڵ����޸�
5. ��    ��   : 2013��06��28��
   ��    ��   : l00167671
   �޸�����   : DCM LOGGER��Ŀ��ʱ���¼��ϱ�
*****************************************************************************/
VOS_UINT32  NAS_MMC_StartTimer(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId,
    VOS_UINT32                          ulLen
)
{
    NAS_MMC_TIMER_CTX_STRU             *pstMmcTimerCtx;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;

    pstMmcTimerCtx   =  NAS_MMC_GetTimerAddr();

    if (0 == ulLen)
    {
        NAS_INFO_LOG1(WUEPS_PID_MMC,"NAS_MMC_StartTimer:timer len is zero!", (VOS_INT32)enTimerId);
        return VOS_FALSE;
    }

    /* �����������иö�ʱ���Ѿ�������ֱ�ӷ��� */
    for ( i = 0 ; i < NAS_MMC_MAX_TIMER_NUM ; i++ )
    {
        if ( ( NAS_MMC_TIMER_STATUS_RUNING == pstMmcTimerCtx[i].enTimerStatus )
          && ( enTimerId                   == pstMmcTimerCtx[i].enTimerId))
        {
            NAS_INFO_LOG1(WUEPS_PID_MMC, "NAS_MMC_StartTimer:timer is running", enTimerId);

            return VOS_FALSE;
        }
    }

    for ( i = 0 ; i < NAS_MMC_MAX_TIMER_NUM ; i++ )
    {
        if ( NAS_MMC_TIMER_STATUS_STOP == pstMmcTimerCtx[i].enTimerStatus )
        {
            break;
        }
    }

    if ( i >= NAS_MMC_MAX_TIMER_NUM)
    {
        NAS_WARNING_LOG1(WUEPS_PID_MMC, "NAS_MMC_StartTimer:too many timer", enTimerId);

        return VOS_FALSE;
    }

    if ( ulLen >= VOS_TIMER_MAX_LENGTH )
    {
        ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }

    ulPrecision = NAS_MMC_GetTimerPrecision(enTimerId);

    ulRet = VOS_StartRelTimer(&(pstMmcTimerCtx[i].hTimer),
                              WUEPS_PID_MMC,
                              ulLen,
                              enTimerId,
                              0,
                              VOS_RELTIMER_NOLOOP,
                              ulPrecision);

    if ( VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_StartTimer:NAS_StartRelTimer failed");

        return VOS_FALSE;
    }

    pstMmcTimerCtx[i].enTimerId     = enTimerId;
    pstMmcTimerCtx[i].enTimerStatus = NAS_MMC_TIMER_STATUS_RUNING;


    /* ��ʱ��״̬�������� */
    NAS_MMC_SndOmMmcTimerStatus(NAS_MMC_TIMER_STATUS_RUNING, enTimerId, ulLen);


    /* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, begin */
    NAS_TIMER_EventReport((VOS_UINT32)enTimerId, WUEPS_PID_MMC, NAS_OM_EVENT_TIMER_OPERATION_START);
    /* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, end */

    return VOS_TRUE;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_StopTimer
 ��������  : ָֹͣ����MMC��ʱ��
 �������  : enTimerId - ��Ҫֹͣ�Ķ�ʱ��ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��30��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��06��
    ��    ��   : z49106
    �޸�����   : ��ʱ��ָ�벻Ϊ�յ�ʱ��, ��ֹͣ��ʱ��
  3.��    ��   : 2012��1��30��
    ��    ��   : l00130025
    �޸�����   : DTS2012010500368,����ͬ���ӿ�VOS_GetRelTmRemainTimehTimerʱû���ж�hTimer�Ƿ�Ϊ0���붨ʱ���첽��Ϣ��ͻ�����쳣��ӡ

  4.��    ��   : 2012��8��21��
    ��    ��   : z40661
    �޸�����   : DTS2012080208200,VOS_GetRelTmRemainTimehTimerʱ��δ��tickתΪms��
  5.��    ��   : 2013��06��28��
    ��    ��   : l00167671
    �޸�����   : DCM LOGGER��Ŀ��ʱ���¼��ϱ�
*****************************************************************************/
VOS_VOID  NAS_MMC_StopTimer(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
)
{
    NAS_MMC_TIMER_CTX_STRU             *pstMmcTimerCtx;
    VOS_UINT32                          i;

    VOS_UINT32                          ulTimerRemainLen;

    ulTimerRemainLen = 0;


    pstMmcTimerCtx   =  NAS_MMC_GetTimerAddr();

    for ( i = 0 ; i < NAS_MMC_MAX_TIMER_NUM ; i++ )
    {
        if ( ( NAS_MMC_TIMER_STATUS_RUNING  == pstMmcTimerCtx[i].enTimerStatus )
          && ( enTimerId                    == pstMmcTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if ( i >= NAS_MMC_MAX_TIMER_NUM)
    {
        NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MMC_StopTimer:Timer not running", enTimerId);

        return;
    }

    /* ֹͣVOS��ʱ��: ����ʱ����ָ���Ѿ�Ϊ�յ�ʱ��, ˵�����Ѿ�ֹͣ���߳�ʱ */
    if (VOS_NULL_PTR != pstMmcTimerCtx[i].hTimer)
    {


        /* ��ȡ��ǰ��ʱ����ʣ��ʱ�� */
        if (VOS_OK != VOS_GetRelTmRemainTime(&(pstMmcTimerCtx[i].hTimer), &ulTimerRemainLen ))
        {
            ulTimerRemainLen = 0;
        }



        (VOS_VOID)VOS_StopRelTimer(&(pstMmcTimerCtx[i].hTimer));
    }

    pstMmcTimerCtx[i].hTimer        = VOS_NULL_PTR;
    pstMmcTimerCtx[i].enTimerId     = TI_NAS_MMC_TIMER_BUTT;
    pstMmcTimerCtx[i].enTimerStatus = NAS_MMC_TIMER_STATUS_STOP;



    /* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, begin */
    if (0!=ulTimerRemainLen)
    {
        NAS_TIMER_EventReport(enTimerId, WUEPS_PID_MMC, NAS_OM_EVENT_TIMER_OPERATION_STOP);
    }
    /* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, end */


    /* ��ʱ��״̬�������� */
    NAS_MMC_SndOmMmcTimerStatus(NAS_MMC_TIMER_STATUS_STOP, enTimerId, ulTimerRemainLen * 10);




}


/*****************************************************************************
 �� �� ��  : NAS_MMC_StopAllTimer
 ��������  : ֹͣMMC�����ж�ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��30��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��3��12��
    ��    ��   : s00246516
    �޸�����   : L-C��������Ŀ�����ӿ�ά�ɲ���Ϣ
*****************************************************************************/
VOS_VOID  NAS_MMC_StopAllTimer( VOS_VOID )
{
    NAS_MMC_TIMER_CTX_STRU             *pstMmcTimerCtx;
    VOS_UINT32                          i;

    /* Added by s00246516 for L-C��������Ŀ, 2014-02-14, Begin */
    VOS_UINT32                          ulTimerRemainLen;

    ulTimerRemainLen = 0;
    /* Added by s00246516 for L-C��������Ŀ, 2014-02-14, End */

    pstMmcTimerCtx   =  NAS_MMC_GetTimerAddr();

    for ( i = 0 ; i < NAS_MMC_MAX_TIMER_NUM ; i++ )
    {
        if ( NAS_MMC_TIMER_STATUS_RUNING  == pstMmcTimerCtx[i].enTimerStatus )
        {
            /* Modified by s00246516 for L-C��������Ŀ, 2014-02-14, Begin */
            if (VOS_OK != VOS_GetRelTmRemainTime(&(pstMmcTimerCtx[i].hTimer), &ulTimerRemainLen ))
            {
                ulTimerRemainLen = 0;
            }

            /* ֹͣVOS��ʱ�� */
            (VOS_VOID)VOS_StopRelTimer(&(pstMmcTimerCtx[i].hTimer));

            NAS_MMC_SndOmMmcTimerStatus(NAS_MMC_TIMER_STATUS_STOP, pstMmcTimerCtx[i].enTimerId, ulTimerRemainLen * 10);
            /* Modified by s00246516 for L-C��������Ŀ, 2014-02-14, End */

            pstMmcTimerCtx[i].hTimer        = VOS_NULL_PTR;
            pstMmcTimerCtx[i].enTimerId     = TI_NAS_MMC_TIMER_BUTT;
            pstMmcTimerCtx[i].enTimerStatus = NAS_MMC_TIMER_STATUS_STOP;
        }
    }
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetTimerStatus
 ��������  : ��ѯָ����MMC��ʱ����״̬
 �������  : enTimerId  - ��Ҫ��ѯ�Ķ�ʱ��ID
 �������  : ��
 �� �� ֵ  : NAS_MMC_TIMER_STATUS_ENUM_U8:��ʱ��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��4��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��30��
    ��    ��   : l00130025
    �޸�����   : DTS2012010500368,����ͬ���ӿ�VOS_GetRelTmRemainTimehTimerʱû���ж�hTimer�Ƿ�Ϊ0���붨ʱ���첽��Ϣ��ͻ�����쳣��ӡ
*****************************************************************************/
NAS_MMC_TIMER_STATUS_ENUM_U8  NAS_MMC_GetTimerStatus(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
)
{
    NAS_MMC_TIMER_CTX_STRU             *pstMmcTimerCtx;
    VOS_UINT32                          i;

    pstMmcTimerCtx = NAS_MMC_GetTimerAddr();

    for ( i = 0 ; i < NAS_MMC_MAX_TIMER_NUM ; i++ )
    {
        if ( ( NAS_MMC_TIMER_STATUS_RUNING  == pstMmcTimerCtx[i].enTimerStatus )
          && ( enTimerId                    == pstMmcTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if ( i >= NAS_MMC_MAX_TIMER_NUM)
    {
        return NAS_MMC_TIMER_STATUS_STOP;
    }

    return NAS_MMC_TIMER_STATUS_RUNING;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetTimerPrecision
 ��������  : ��ȡMMCģ�鶨ʱ�����ȷ�Χ
 �������  : Pid       -- ������ʱ����PID
             ulName    -- ��ʱ����
 �������  : ��
 �� �� ֵ  : VOS_TIMER_PRECISION_ENUM_UINT32 -- ��ʱ�����ȷ�Χ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��7��25��
   ��    ��   : zhoujun \40661
   �޸�����   : �����ɺ���

 2.��    ��   : 2013��9��4��
   ��    ��   : w00167002
   �޸�����   : DTS2013090403562:NAS��ʱ��������Ҫ����32K��ʱ������MM/MMA/SMS
                ģ���ѭ����ʱ���޸�Ϊ��ѭ����ʱ����
*****************************************************************************/
VOS_TIMER_PRECISION_ENUM_UINT32 NAS_MMC_GetTimerPrecision(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
)
{
   /*��ʱ����Ϊ���֣�26M��ʱ����32K��ʱ����
         26M��ʱ����ϵͳ�����٣��Ƽ�ʹ�ã�����DRX˯��ʱ��ֹͣ���������ܼ�ʱ��׼��
         32K��ʱ����ϵͳ�����󣬲��Ƽ�ʹ�ã�����ʱ׼ȷ��
         ��ѡ���޾���Ҫ��ʱ(VOS_TIMER_NO_PRECISION)������26M��ʱ��
         �����о���Ҫ��ģ�����32K��ʱ����
     ��ʱ��ѡ������:
       1����IDLE̬�¶�ʱ����Ҫ��ʱ�������Ǿ�ȷ��ʱ�ģ����������쳣������ʱ����
          �Լ���Ƶ�Ҫ����Զ�ʱ�ģ� Э�鶨ʱ���б�����Զ�ʱ�ģ�����˵�������
          ��ʱ����ͨ��GCF������ �����ඨʱ����ʹ��32K��ʱ����
       2������IDLE��ʱ��������Ҫ���Զ�ʱ�ģ��ҵ�26M��ʱ����
       3����IDLE̬�Ķ�ʱ����ʹ��26M��ʱ�� */

    VOS_UINT32                          i;
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;



    /* Ĭ��Ϊ�о���Ҫ�󣬹���32Kʱ���� */
    ulPrecision = VOS_TIMER_PRECISION_5;

    for ( i = 0; i < ( sizeof(g_stNasMmcTimerPrcision)/sizeof(NAS_TIMER_PRECISION_STRU) ); i++)
    {
        if (enTimerId == g_stNasMmcTimerPrcision[i].ulTimerName)
        {
            ulPrecision = g_stNasMmcTimerPrcision[i].ulPrecision;
            break;
        }
    }

    return ulPrecision;
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

