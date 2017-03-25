/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMsccTimerMgmt.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2015��01��26��
  ��������   : MSCC module��ʱ������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��01��26��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "PsCommonDef.h"
#include "NasMsccCtx.h"
#include "NasMntn.h"
#include "NasComm.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_TIMER_MGMT_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : NAS_MSCC_SndOmTimerStatus
 ��������  : ������Ϣ��OMģ�飬MSCC��ʱ������״̬
 �������  : enTimerStatus - ��ʱ��״̬
             enTimerId     - ��ʱ��ID
             ulLen         - ��ʱ��ʱ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��27��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MSCC_SndOmTimerStatus(
    NAS_MSCC_TIMER_STATUS_ENUM_UINT8    enTimerStatus,
    NAS_MSCC_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulLen
)
{
    NAS_MSCC_TIMER_INFO_STRU            *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_MSCC_TIMER_INFO_STRU*)PS_MEM_ALLOC(UEPS_PID_MSCC,
                sizeof(NAS_MSCC_TIMER_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_SndOmTimerStatus:ERROR:Alloc Mem Fail.");
        return;
    }

    /* ��ʱ��������Ϣ��ֵ */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_MSCC;
    pstMsg->stMsgHeader.ulReceiverPid   = VOS_PID_TIMER;

    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_MSCC_TIMER_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stMsgHeader.ulMsgName       = enTimerId;
    pstMsg->enTimerStatus               = enTimerStatus;
    pstMsg->ulLen                       = ulLen;

    /* ��ʱ����Ϣ���� */
    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_MSCC, pstMsg);
}


/*****************************************************************************
 �� �� ��  : NAS_MSCC_StartTimer
 ��������  : ����ָ����MMA��ʱ��
 �������  : enTimerId - ��Ҫ�����Ķ�ʱ��ID
             ulLen     - ��ʱ��ʱ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:start timer succ
             VOS_FALSE:start timer fail
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��01��27��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 7/1/2015
   ��    ��   : W00176964
   �޸�����   : CDMA 1X Iteration 10 Modified:Add return value

*****************************************************************************/
VOS_UINT32  NAS_MSCC_StartTimer(
    NAS_MSCC_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulLen
)
{
    NAS_MSCC_TIMER_CTX_STRU             *pstMsccTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                           i;
    VOS_UINT32                           ulRet;

    if (0 == ulLen)
    {
        NAS_WARNING_LOG1(UEPS_PID_MSCC, "NAS_MSCC_StartTimer:timer len is zero!", (VOS_INT32)enTimerId);
        return VOS_FALSE;
    }

    if (ulLen >= VOS_TIMER_MAX_LENGTH)
    {
       ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }

    pstMsccTimerCtx   =  NAS_MSCC_GetTimerCtxAddr();

    /* �����������иö�ʱ���Ѿ�������ֱ�ӷ��� */
    for (i = 0 ; i < TI_NAS_MSCC_TIMER_BUTT ; i++)
    {
        if ((NAS_MSCC_TIMER_STATUS_RUNING == pstMsccTimerCtx[i].enTimerStatus)
         && (enTimerId                    == pstMsccTimerCtx[i].enTimerId))
        {
            NAS_WARNING_LOG1(UEPS_PID_MSCC, "NAS_MSCC_StartTimer:timer is running!", (VOS_INT32)enTimerId);

            return VOS_FALSE;
        }
    }

    for (i = 0 ; i < TI_NAS_MSCC_TIMER_BUTT ; i++)
    {
        if (NAS_MSCC_TIMER_STATUS_STOP == pstMsccTimerCtx[i].enTimerStatus )
        {
            break;
        }
    }

    if (i >= TI_NAS_MSCC_TIMER_BUTT)
    {
       NAS_WARNING_LOG1(UEPS_PID_MSCC, "NAS_MSCC_StartTimer: timer resource is not enough", (VOS_INT32)enTimerId);

       return VOS_FALSE;
    }

    /* ������ʱ�� */
    ulRet = VOS_StartRelTimer(&(pstMsccTimerCtx[i].hTimer),
                              UEPS_PID_MSCC,
                              ulLen,
                              enTimerId,
                              0,
                              VOS_RELTIMER_NOLOOP,
                              VOS_TIMER_PRECISION_5);

    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(UEPS_PID_MSCC,"NAS_MSCC_StartTimer:VOS_StartRelTimer failed");

        return VOS_FALSE;
    }

    pstMsccTimerCtx[i].enTimerId     = enTimerId;
    pstMsccTimerCtx[i].enTimerStatus = NAS_MSCC_TIMER_STATUS_RUNING;

    NAS_MSCC_SndOmTimerStatus(NAS_MSCC_TIMER_STATUS_RUNING, enTimerId, ulLen);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_StopTimer
 ��������  : ָֹͣ����MMA��ʱ��
 �������  : enTimerId - ��Ҫֹͣ�Ķ�ʱ��ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��27��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_MSCC_StopTimer(
    NAS_MSCC_TIMER_ID_ENUM_UINT32       enTimerId
)
{
    NAS_MSCC_TIMER_CTX_STRU            *pstMsccTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstMsccTimerCtx   =  NAS_MSCC_GetTimerCtxAddr();

    for (i = 0 ; i < TI_NAS_MSCC_TIMER_BUTT ; i++)
    {
        if ((NAS_MSCC_TIMER_STATUS_RUNING == pstMsccTimerCtx[i].enTimerStatus)
         && (enTimerId                    == pstMsccTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if (i >= TI_NAS_MSCC_TIMER_BUTT)
    {
        NAS_WARNING_LOG1(UEPS_PID_MSCC, "NAS_MSCC_StopTimer:timer already stopped", (VOS_INT32)enTimerId);
        return;
    }

    /* ֹͣVOS��ʱ��: ����ʱ����ָ���Ѿ�Ϊ�յ�ʱ��, ˵�����Ѿ�ֹͣ���߳�ʱ */
    if (VOS_NULL_PTR != pstMsccTimerCtx[i].hTimer)
    {
        (VOS_VOID)VOS_StopRelTimer(&(pstMsccTimerCtx[i].hTimer));
    }

    pstMsccTimerCtx[i].hTimer            = VOS_NULL_PTR;
    pstMsccTimerCtx[i].enTimerId         = TI_NAS_MSCC_TIMER_BUTT;
    pstMsccTimerCtx[i].enTimerStatus     = NAS_MSCC_TIMER_STATUS_STOP;

    NAS_MSCC_SndOmTimerStatus(NAS_MSCC_TIMER_STATUS_STOP, enTimerId, 0);
}




/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetTimerStatus
 ��������  : ��ȡָ����MMA��ʱ������״̬
 �������  : enTimerId - ��Ҫֹͣ�Ķ�ʱ��ID
 �������  : ��
 �� �� ֵ  : NAS_MSCC_TIMER_STATUS_ENUM_UINT8 - ��ʱ������״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��27��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_MSCC_TIMER_STATUS_ENUM_UINT8  NAS_MSCC_GetTimerStatus(
    NAS_MSCC_TIMER_ID_ENUM_UINT32       enTimerId
)
{
    NAS_MSCC_TIMER_CTX_STRU            *pstMsccTimerCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;
    NAS_MSCC_TIMER_STATUS_ENUM_UINT8     enTimerStatus;

    pstMsccTimerCtx = NAS_MSCC_GetTimerCtxAddr();

    enTimerStatus  = NAS_MSCC_TIMER_STATUS_STOP;

    /* ���Ҹö�ʱ���Ƿ��������� */
    for (i = 0 ; i < TI_NAS_MSCC_TIMER_BUTT; i++)
    {
        if (enTimerId    == pstMsccTimerCtx[i].enTimerId)
        {
            enTimerStatus = pstMsccTimerCtx[i].enTimerStatus;
            break;
        }
    }

    return enTimerStatus;
}


VOS_VOID NAS_MSCC_StopAllTimer(VOS_VOID)
{
    VOS_UINT32                          i;

    for (i = 0; i < TI_NAS_MSCC_TIMER_BUTT; i++)
    {
        NAS_MSCC_StopTimer(i);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MSCC_GetRemainTimerLen
 ��������  : ��ȡ��ʱ��ʣ��ʱ��
 �������  : enTimerId        --- ��ʱ��ID
 �������  : pulRemainTimeLen --- ʣ��ʱ��(��λ: ����)
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��9��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MSCC_GetRemainTimerLen(
    NAS_MSCC_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                         *pulRemainTimeLen
)
{
    NAS_MSCC_TIMER_CTX_STRU             *pstTimerCtx;
    VOS_UINT32                          ulRemainTick;
    VOS_UINT32                          i;

    pstTimerCtx = NAS_MSCC_GetTimerCtxAddr();
    ulRemainTick   = 0;

    for (i = 0 ; i < TI_NAS_MSCC_TIMER_BUTT ; i++)
    {
        if ( (NAS_MSCC_TIMER_STATUS_RUNING  == pstTimerCtx[i].enTimerStatus)
          && (enTimerId                     == pstTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if (i >= TI_NAS_MSCC_TIMER_BUTT)
    {
        NAS_WARNING_LOG1(UEPS_PID_MSCC, "NAS_MSCC_GetRemainTimerLen: Timer already stopped!", (VOS_INT32)enTimerId);
        *pulRemainTimeLen = 0;
        return;
    }

    if (VOS_NULL_PTR == pstTimerCtx[i].hTimer)
    {
        NAS_WARNING_LOG1(UEPS_PID_MSCC, "NAS_MSCC_GetRemainTimerLen: Timer handle is null!", (VOS_INT32)enTimerId);
        *pulRemainTimeLen = 0;
        return;
    }

    if (VOS_OK != VOS_GetRelTmRemainTime(&(pstTimerCtx[i].hTimer), &ulRemainTick))
    {
        NAS_WARNING_LOG1(UEPS_PID_MSCC, "NAS_MSCC_GetRemainTimerLen: Get remain time fail!", (VOS_INT32)enTimerId);
        *pulRemainTimeLen = 0;
        return;
    }

    *pulRemainTimeLen = ulRemainTick * NAS_MSCC_TIMER_TICK;

    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



