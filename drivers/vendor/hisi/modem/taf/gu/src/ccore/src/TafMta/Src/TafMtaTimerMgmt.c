/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMtaTimerMgmt.c
  �� �� ��   : ����
  ��    ��   : ��־��
  ��������   : 2012��6��27��
  ����޸�   :
  ��������   : MTAģ�鶨ʱ��ʵ�ֺ���Դ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��6��27��
    ��    ��   : Y00213812
    �޸�����   : A-GPS��Ŀ����

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define     THIS_FILE_ID        PS_FILE_ID_TAF_MTA_TIMER_MGMT_C


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TafMtaComm.h"
#include "TafMtaCtx.h"
#include "TafMtaTimerMgmt.h"

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
TAF_MTA_TIMER_PRECISION_STRU g_astTafMtaTimerPrecisionTab[]=
{
   {TI_TAF_MTA_WAIT_REFCLOCK_STATUS_IND,      VOS_TIMER_NO_PRECISION}
};

/*****************************************************************************
  3 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_MTA_SndOmTimerStatus
 ��������  : TAF �� MTA ��ʱ��״̬���͸� OM
 �������  : enTimerStatus ��ʱ��״̬,
             enTimerId     ��ʱ��ID,
             ulLen         ��ʱ��ʱ��
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : A-GPS��Ŀ��������

*****************************************************************************/
VOS_VOID  TAF_MTA_SndOmTimerStatus(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    TAF_MTA_TIMER_STATUS_ENUM_UINT8     enTimerStatus
)
{
    /*lint -e958*/
    TAF_MTA_TIMER_INFO_STRU            *pstMsg = VOS_NULL_PTR;
    /*lint +e958*/

    pstMsg = (TAF_MTA_TIMER_INFO_STRU*)PS_MEM_ALLOC(UEPS_PID_MTA,
                             sizeof(TAF_MTA_TIMER_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        MTA_ERROR_LOG("TAF_MTA_SndOmTimerStatus:ERROR:Alloc Mem Fail.");
        return;
    }

    /* ��ʱ��������Ϣ��ֵ */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_MTA;
    pstMsg->stMsgHeader.ulReceiverPid   = VOS_PID_TIMER;

    pstMsg->stMsgHeader.ulLength        = sizeof(TAF_MTA_TIMER_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stMsgHeader.ulMsgName       = enTimerId;
    pstMsg->enTimerStatus               = enTimerStatus;
    pstMsg->ulLen                       = ulLen;

    /* ��ʱ����Ϣ���� */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MTA, pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetTimerPrecision
 ��������  : ��ȡ��ʱ�����ȷ�Χ
 �������  : enTimerId    -- ��ʱ����
 �������  : ��
 �� �� ֵ  : VOS_TIMER_PRECISION_ENUM_UINT32 -- ��ʱ�����ȷ�Χ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��17��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_TIMER_PRECISION_ENUM_UINT32 TAF_MTA_GetTimerPrecision(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId
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

    VOS_UINT32                      i;
    VOS_TIMER_PRECISION_ENUM_UINT32 ulPrecision;

    /* Ĭ�Ͼ���Ϊ32K */
    ulPrecision = VOS_TIMER_PRECISION_5;

    for(i=0; i<( sizeof(g_astTafMtaTimerPrecisionTab)/sizeof(TAF_MTA_TIMER_PRECISION_STRU) ); i++)
    {
        if (enTimerId == g_astTafMtaTimerPrecisionTab[i].enTimerId)
        {
            ulPrecision = g_astTafMtaTimerPrecisionTab[i].ulPrecision;
            break;
        }
    }

    return ulPrecision;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_InitAllTimers
 ��������  : ��ʼ�����ж�ʱ����Ӧ��MTA��ʼ��ʱ������
 �������  : pstMtaTimerCtx - ��ʱ��������ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : A-GPS��Ŀ��������
  2.��    ��   : 2013��01��22��
    ��    ��   : m00217266
    �޸�����   : DSDA C����Ŀ�ӿ��޸�
*****************************************************************************/
VOS_VOID  TAF_MTA_InitAllTimers(
    TAF_MTA_TIMER_CTX_STRU              *pstMtaTimerCtx
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < TAF_MTA_CTX_MAX_TIMER_NUM; i++)
    {
        pstMtaTimerCtx[i].hTimer        = VOS_NULL_PTR;
        pstMtaTimerCtx[i].enTimerId     = TI_TAF_MTA_TIMER_BUTT;
        pstMtaTimerCtx[i].enTimerStatus = TAF_MTA_TIMER_STATUS_STOP;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MTA_StartTimer
 ��������  : ����ָ����MTA��ʱ��
 �������  : enTimerId - ��Ҫ�����Ķ�ʱ��ID
             ulLen     - ��ʱ��ʱ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : A-GPS��Ŀ��������
  2.��    ��   : 2013��01��22��
    ��    ��   : m00217266
    �޸�����   : DSDA C����Ŀ�ӿ��޸�
  3.��    ��   : 2013��03��11��
    ��    ��   : l00198894
    �޸�����   : Body SAR��Ŀ��������
  4.��    ��   : 2013��9��4��
    ��    ��   : w00167002
    �޸�����   : DTS2013090403562:NAS��ʱ��������Ҫ����32K��ʱ������MM/MMA/SMS
                ģ���ѭ����ʱ���޸�Ϊ��ѭ����ʱ����
*****************************************************************************/
TAF_MTA_TIMER_START_RESULT_ENUM_UINT8  TAF_MTA_StartTimer(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen
)
{
    TAF_MTA_TIMER_CTX_STRU             *pstMtaTimerCtx;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;

    if ( enTimerId >= TI_TAF_MTA_TIMER_BUTT)
    {
        MTA_WARNING1_LOG("TAF_MTA_StartTimer:Error TimerId!", (VOS_INT32)enTimerId);
        return TAF_MTA_TIMER_START_FAILURE;
    }

    pstMtaTimerCtx   =  TAF_MTA_GetTimerCtxAddr();

    /* �����������иö�ʱ���Ѿ�������ֱ�ӷ��� */
    for ( i = 0; i < TAF_MTA_CTX_MAX_TIMER_NUM; i++)
    {
        if ( ( TAF_MTA_TIMER_STATUS_RUNING == pstMtaTimerCtx[i].enTimerStatus )
          && ( enTimerId                   == pstMtaTimerCtx[i].enTimerId))
        {
            MTA_WARNING1_LOG("TAF_MTA_StartTimer:timer is running!", (VOS_INT32)enTimerId);
            return TAF_MTA_TIMER_START_FAILURE;
        }
    }

    /* ���ҵ�ǰ�б���δ�õĽڵ� */
    for ( i = 0; i < TAF_MTA_CTX_MAX_TIMER_NUM; i++)
    {
        if ( TAF_MTA_TIMER_STATUS_STOP == pstMtaTimerCtx[i].enTimerStatus )
        {
            break;
        }
    }

    if (TAF_MTA_CTX_MAX_TIMER_NUM == i)
    {
        MTA_WARNING_LOG("TAF_MTA_StartTimer: five timers are running!");
        return TAF_MTA_TIMER_START_FAILURE;
    }

    /* ��鶨ʱ��ʱ�� */
    if ( 0 == ulLen)
    {
        MTA_WARNING1_LOG("TAF_MTA_StartTimer:timer len is zero!", (VOS_INT32)enTimerId);
        return TAF_MTA_TIMER_START_FAILURE;
    }
    else if ( ulLen >= VOS_TIMER_MAX_LENGTH )
    {
        ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }
    else
    {

    }
    ulPrecision = TAF_MTA_GetTimerPrecision(enTimerId);

    /* ������ʱ�� */
    ulRet = VOS_StartRelTimer(&(pstMtaTimerCtx[i].hTimer),
                              UEPS_PID_MTA,
                              ulLen,
                              enTimerId,
                              0,
                              VOS_RELTIMER_NOLOOP,
                              ulPrecision);

    if ( VOS_OK != ulRet)
    {
        MTA_WARNING_LOG("TAF_MTA_StartTimer:VOS_StartRelTimer failed");
        return TAF_MTA_TIMER_START_FAILURE;
    }

    pstMtaTimerCtx[i].enTimerId     = enTimerId;
    pstMtaTimerCtx[i].enTimerStatus = TAF_MTA_TIMER_STATUS_RUNING;

    /* ��ʱ��״̬�������� */
    TAF_MTA_SndOmTimerStatus(enTimerId, ulLen, TAF_MTA_TIMER_STATUS_RUNING);

    return TAF_MTA_TIMER_START_SUCCEE;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_StopTimer
 ��������  : ָֹͣ����MTA��ʱ��
 �������  : enTimerId - ��Ҫֹͣ�Ķ�ʱ��ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : A-GPS��Ŀ��������
  2.��    ��   : 2013��01��22��
    ��    ��   : m00217266
    �޸�����   : DSDA C����Ŀ�ӿ��޸�
*****************************************************************************/
VOS_VOID  TAF_MTA_StopTimer(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId
)
{
    TAF_MTA_TIMER_CTX_STRU             *pstMtaTimerCtx;
    VOS_UINT32                          i;

    pstMtaTimerCtx   =  TAF_MTA_GetTimerCtxAddr();

    for ( i = 0; i < TAF_MTA_CTX_MAX_TIMER_NUM; i++)
    {
        if ( ( TAF_MTA_TIMER_STATUS_RUNING  == pstMtaTimerCtx[i].enTimerStatus )
          && ( enTimerId                    == pstMtaTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if ( i >= TAF_MTA_CTX_MAX_TIMER_NUM)
    {
        MTA_WARNING1_LOG("TAF_MTA_StopTimer:timer already stopped!", (VOS_INT32)enTimerId);
        return;
    }

    /* ֹͣVOS��ʱ��: ����ʱ����ָ���Ѿ�Ϊ�յ�ʱ��, ˵�����Ѿ�ֹͣ���߳�ʱ */
    if (VOS_NULL_PTR != pstMtaTimerCtx[i].hTimer)
    {
        (VOS_VOID)VOS_StopRelTimer(&(pstMtaTimerCtx[i].hTimer));
    }

    pstMtaTimerCtx[i].hTimer        = VOS_NULL_PTR;
    pstMtaTimerCtx[i].enTimerId     = TI_TAF_MTA_TIMER_BUTT;
    pstMtaTimerCtx[i].enTimerStatus = TAF_MTA_TIMER_STATUS_STOP;

    /* ��ʱ��״̬�������� */
    TAF_MTA_SndOmTimerStatus(enTimerId, 0, TAF_MTA_TIMER_STATUS_STOP);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_GetTimerStatus
 ��������  : ��ȡָ����MTA��ʱ������״̬
 �������  : enTimerId - ��Ҫ��ȡ����״̬�Ķ�ʱ��ID
 �������  : ��
 �� �� ֵ  : TAF_MTA_TIMER_STATUS_ENUM_UINT8 - ��ʱ������״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��27��
    ��    ��   : y00213812
    �޸�����   : A-GPS��Ŀ��������
  2.��    ��   : 2013��01��22��
    ��    ��   : m00217266
    �޸�����   : DSDA C����Ŀ�ӿ��޸�
*****************************************************************************/
TAF_MTA_TIMER_STATUS_ENUM_UINT8  TAF_MTA_GetTimerStatus(
    TAF_MTA_TIMER_ID_ENUM_UINT32        enTimerId
)
{
    TAF_MTA_TIMER_CTX_STRU             *pstMtaTimerCtx;
    VOS_UINT32                          i;
    TAF_MTA_TIMER_STATUS_ENUM_UINT8     enTimerStatus;

    pstMtaTimerCtx = TAF_MTA_GetTimerCtxAddr();

    enTimerStatus  = TAF_MTA_TIMER_STATUS_STOP;

    /* ���Ҹö�ʱ���Ƿ��������� */
    for ( i = 0; i < TAF_MTA_CTX_MAX_TIMER_NUM; i++)
    {
        if (enTimerId == pstMtaTimerCtx[i].enTimerId)
        {
            enTimerStatus = pstMtaTimerCtx[i].enTimerStatus;
            break;
        }
    }

    return enTimerStatus;
}

/*lint +e958*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
