/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasCcTimer.c
  �� �� ��   : ����
  ��    ��   : ���� 49431
  ��������   : 2007��8��31��
  ����޸�   : 2007��8��31��
  ��������   : ����CC��ʱ�����Լ����г�ʱ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��8��31��
    ��    ��   : ���� 49431
    �޸�����   : �����ļ�

  2.��    ��   : 2010��3��2��
    ��    ��   : zhoujun /z40661
    �޸�����   : NAS R7Э������
  3.��    ��   : 2011��11��11��
    ��    ��   : h44270
    �޸�����   : ���ⵥ��:DTS2010102500585,����RABȥ�������ʱ��
****************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasCcInclude.h"

#include "NasUsimmApi.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 ��������
*****************************************************************************/
/* CC��ͬʱ���еĶ�ʱ���������Ŀ */
#define NAS_CC_MAX_TIMER_NUM   16
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define THIS_FILE_ID PS_FILE_ID_NASCC_TIMER_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/
/* ��ʱ������ṹ�����ڹ���ʱ����Դ */
typedef struct
{
    HTIMER                              hTimer;
    NAS_CC_TIMER_ID_ENUM                enTimerId;
    NAS_CC_ENTITY_ID_T                  entityId;
} NAS_CC_TIMER_HANDLE_STRU;

/* ��ʱ�����������Ͷ��� */
typedef VOS_VOID (* NAS_CC_TIMEOUT_PROC_FUNC)(NAS_CC_ENTITY_ID_T entityId, VOS_UINT32 ulParam);

/* ��ʱ����Ϣ�ṹ */
typedef struct
{
    VOS_UINT32                          ulTimeout;
    NAS_CC_TIMEOUT_PROC_FUNC            pfnTimeoutProc;
} NAS_CC_TIMER_INFO_STRU;


/*****************************************************************************
  4 ��������
*****************************************************************************/
/* ��ʱ���������� */
LOCAL VOS_VOID  NAS_CC_T303Timeout(NAS_CC_ENTITY_ID_T entityId, VOS_UINT32 ulParam);
LOCAL VOS_VOID  NAS_CC_T305Timeout(NAS_CC_ENTITY_ID_T entityId, VOS_UINT32 ulParam);
LOCAL VOS_VOID  NAS_CC_T308Timeout(NAS_CC_ENTITY_ID_T entityId, VOS_UINT32 ulParam);
LOCAL VOS_VOID  NAS_CC_T310Timeout(NAS_CC_ENTITY_ID_T entityId, VOS_UINT32 ulParam);
LOCAL VOS_VOID  NAS_CC_T313Timeout(NAS_CC_ENTITY_ID_T entityId, VOS_UINT32 ulParam);
LOCAL VOS_VOID  NAS_CC_T323Timeout(NAS_CC_ENTITY_ID_T entityId, VOS_UINT32 ulParam);
LOCAL VOS_VOID  NAS_CC_T332Timeout(NAS_CC_ENTITY_ID_T entityId, VOS_UINT32 ulParam);
LOCAL VOS_VOID  NAS_CC_T335Timeout(NAS_CC_ENTITY_ID_T entityId, VOS_UINT32 ulParam);
LOCAL VOS_VOID  NAS_CC_T336Timeout(NAS_CC_ENTITY_ID_T entityId, VOS_UINT32 ulParam);
LOCAL VOS_VOID  NAS_CC_T337Timeout(NAS_CC_ENTITY_ID_T entityId, VOS_UINT32 ulParam);
LOCAL VOS_VOID  NAS_CC_HoldTimeout(NAS_CC_ENTITY_ID_T entityId, VOS_UINT32 ulParam);
LOCAL VOS_VOID  NAS_CC_MptyTimeout(NAS_CC_ENTITY_ID_T entityId, VOS_UINT32 ulParam);
LOCAL VOS_VOID  NAS_CC_ECTTimeout(NAS_CC_ENTITY_ID_T entityId, VOS_UINT32 ulParam);
LOCAL VOS_VOID  NAS_CC_UserConnTimeout(NAS_CC_ENTITY_ID_T entityId, VOS_UINT32 ulParam);
LOCAL VOS_VOID  NAS_CC_RabInactProtectTimeout(NAS_CC_ENTITY_ID_T entityId, VOS_UINT32 ulParam);


/*****************************************************************************
  5 ��������
*****************************************************************************/
/* ���п��õĶ�ʱ����Դ */
LOCAL NAS_CC_TIMER_HANDLE_STRU  f_astCcTimerHandles[NAS_CC_MAX_TIMER_NUM];

LOCAL VOS_UINT32  f_astCcTimerLenFromNvim[] = {
    30000,
    30000,
    30000,
    30000,
    30000,
    30000,
    30000,
    30000,
    10000,
    10000,
    10000,
    10000,
    10000,
    30000,
    30000,
};

/* ��ʱ����Ϣ���ñ��м�¼��ÿ�ֶ�ʱ���ĳ�ʱʱ��ͳ�ʱ������ */

LOCAL NAS_CC_TIMER_INFO_STRU  f_astCcTimerInfoTbl[] = {
    {30000, NAS_CC_T303Timeout},
    {30000, NAS_CC_T305Timeout},
    {30000, NAS_CC_T308Timeout},
    {30000, NAS_CC_T310Timeout},
    {30000, NAS_CC_T313Timeout},
    {30000, NAS_CC_T323Timeout},
    {30000, NAS_CC_T332Timeout},
    {30000, NAS_CC_T335Timeout},
    {10000, NAS_CC_T336Timeout},
    {10000, NAS_CC_T337Timeout},
    {10000, NAS_CC_HoldTimeout},
    {10000, NAS_CC_MptyTimeout},
    {10000, NAS_CC_ECTTimeout},
    {30000, NAS_CC_UserConnTimeout},
    {30000, NAS_CC_RabInactProtectTimeout}
};

/*lint -save -e958 */

/*****************************************************************************
  6 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : NAS_CC_GetNvTimerLen
 ��������  : ��ȡ��ʱ��ʱ��
 �������  : enTimerId :��ʱ��ID
             ulTimerLen:��ʱ����ʱ��
 �������  : ��
 �� �� ֵ  : ��ȡ��ʱ��ʱ���Ƿ�ɹ�

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��30��
    ��    ��   : l00208543
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 NAS_CC_GetNvTimerLen(
    NAS_CC_TIMER_ID_ENUM                enTimerId,
    VOS_UINT32                         *ulTimerLen
)
{
    if (enTimerId >= (sizeof(f_astCcTimerLenFromNvim)/sizeof(f_astCcTimerLenFromNvim[0])))
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_GetTimerLen: enTimerId wrong.");
        return VOS_FALSE;
    }

    *ulTimerLen = f_astCcTimerLenFromNvim[enTimerId];

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_SetNvTimerLen
 ��������  : ���¶�ʱ��ʱ��
 �������  : enTimerId :��ǰ��ʱ��ID
             ulTimerLen:���º�ʱ����ʱ��
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��30��
    ��    ��   : l00208543
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_CC_SetNvTimerLen(
    NAS_CC_TIMER_ID_ENUM                enTimerId,
    VOS_UINT32                          ulTimerLen
)
{
    if (enTimerId >= (sizeof(f_astCcTimerLenFromNvim)/sizeof(f_astCcTimerLenFromNvim[0])))
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_SetTimerLen: enTimerId wrong.");
        return;
    }

    f_astCcTimerLenFromNvim[enTimerId] = ulTimerLen;
}
/*****************************************************************************
 �� �� ��  : NAS_CC_StopAllRunningTimer
 ��������  : ֹͣ���е�ǰ�����������еĶ�ʱ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��26��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_CC_StopAllRunningTimer(VOS_VOID)
{
    VOS_UINT32                          i;

    for (i=0; i<NAS_CC_MAX_TIMER_NUM; i++)
    {
        if (( VOS_NULL_PTR != f_astCcTimerHandles[i].hTimer )
          &&( TI_NAS_CC_MAX != f_astCcTimerHandles[i].enTimerId))
        {
             /* ֹͣVOS��ʱ�� */
            if (VOS_OK == NAS_StopRelTimer(WUEPS_PID_CC,
                                 f_astCcTimerHandles[i].enTimerId,
                                 &f_astCcTimerHandles[i].hTimer))
            {
                f_astCcTimerHandles[i].hTimer = VOS_NULL_PTR;
                f_astCcTimerHandles[i].enTimerId = TI_NAS_CC_MAX;
            }
            else
            {
                NAS_CC_ERR_LOG("NAS_CC_StopAllRunningTimer: NAS_StopRelTimer failed.");
            }
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_CC_InitAllTimers
 ��������  : ��ʼ�����ж�ʱ����Ӧ��CC��ʼ����Resetʱ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_CC_InitAllTimers(VOS_VOID)
{
    VOS_UINT32                          i;

    for (i=0; i<NAS_CC_MAX_TIMER_NUM; i++)
    {
        f_astCcTimerHandles[i].hTimer = VOS_NULL_PTR;
        f_astCcTimerHandles[i].enTimerId = TI_NAS_CC_MAX;
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_StartTimer
 ��������  : ����ָ����CC��ʱ��
 �������  : entityId  - ��Ҫ������ʱ����CCʵ��
              enTimerId - ��Ҫ�����Ķ�ʱ��ID
              ulParam   - ��ʱ��������Я�����Զ������(��ѡ)
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��3��1��
    ��    ��   : zhoujun /z40661
    �޸�����   : �޸�������ʱ���Ա㽫��ʱ����Ϣ����
  3.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  4.��    ��   : 2013��8��30��
    ��    ��   : l00208543
    �޸�����   : DTS2013082902121
  5.��    ��   : 2015��3��20��
    ��    ��   : wx270776
    �޸�����   : DTS2015032009376: ��װ��ȡ��ʱ��ʱ��
*****************************************************************************/
VOS_VOID  NAS_CC_StartTimer(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_TIMER_ID_ENUM                enTimerId,
    VOS_UINT32                          ulParam
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulTimerLen;

    ulTimerLen = 0;

    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_StartTimer: entityId wrong.");
        return;
    }

    if (enTimerId >= (sizeof(f_astCcTimerInfoTbl)/sizeof(NAS_CC_TIMER_INFO_STRU)))
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_StartTimer: enTimerId wrong.");
        return;
    }

    /* Ѱ�ҿ��еĶ�ʱ����� */
    for (i=0; i<NAS_CC_MAX_TIMER_NUM; i++)
    {
        if (TI_NAS_CC_MAX == f_astCcTimerHandles[i].enTimerId)
        {
            break;
        }
    }

    if (i < NAS_CC_MAX_TIMER_NUM)
    {
        /* ��ȡ��ʱ��ʱ�� */
        ulTimerLen = NAS_CC_GetTimerLength(enTimerId);

        /* ����VOS��ʱ�� */
        /* ��Ҫ��TimerId���� */
        ulMsgName = (enTimerId ) | (entityId << 16) ;

        if (VOS_OK == NAS_StartRelTimer(&f_astCcTimerHandles[i].hTimer,
                                        WUEPS_PID_CC,
                                        ulTimerLen,
                                        ulMsgName,
                                        ulParam,
                                        VOS_RELTIMER_NOLOOP))
        {
            /* ��¼entity ID�ͳ�ʱ������ */
            f_astCcTimerHandles[i].entityId = entityId;
            f_astCcTimerHandles[i].enTimerId = enTimerId;
        }
        else
        {
            NAS_CC_ERR_LOG("NAS_CC_StartTimer: VOS_StartRelTimer failed.");
        }
    }
    else
    {
        NAS_CC_ERR_LOG("NAS_CC_StartTimer: Can not find free timer handle.");
    }
}

/*****************************************************************************
 �� �� ��  : NAS_CC_GetTimerLength
 ��������  : ��ȡ��ʱ��ʱ��
 �������  : enTimerId    - ��ʱ��ID
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��21��
    ��    ��   : wx270776
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_CC_GetTimerLength(
    NAS_CC_TIMER_ID_ENUM                enTimerId
)
{
    VOS_UINT32                          ulTimerLen;

    /* �˴����жϣ������T305/T308/T303���ж�һ���Ƿ��ǲ��Կ�ģʽ��������ǲ��Կ�ģʽ��
    ���ȡen_NV_Item_CC_TimerLen(T303���ȡen_NV_Item_CC_T303Len)��д��Ķ�ʱ��ʱ�� */
    ulTimerLen = f_astCcTimerInfoTbl[enTimerId].ulTimeout;

    if ( (TI_NAS_CC_T305 == enTimerId)
      || (TI_NAS_CC_T308 == enTimerId)
      || (TI_NAS_CC_T303 == enTimerId) )
    {
        if (VOS_FALSE == NAS_USIMMAPI_IsTestCard())
        {
            (VOS_VOID)NAS_CC_GetNvTimerLen(enTimerId, &ulTimerLen);
        }
    }

    return ulTimerLen;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_StopTimer
 ��������  : ָֹͣ����CC��ʱ��
 �������  : entityId  - ��Ҫֹͣ��ʱ����CCʵ��
              enTimerId - ��Ҫֹͣ�Ķ�ʱ��ID
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��3��1��
    ��    ��   : zhoujun /z40661
    �޸�����   : �޸�ֹͣ��ʱ���Ա㽫��ʱ����Ϣ����
*****************************************************************************/
VOS_VOID  NAS_CC_StopTimer(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_TIMER_ID_ENUM                enTimerId
)
{
    VOS_UINT32                          i;

    NAS_CC_ASSERT(entityId < NAS_CC_MAX_ENTITY_NUM);
    NAS_CC_ASSERT(enTimerId < TI_NAS_CC_MAX);

    /* Ѱ��entityId��enTimerId������ƥ��ľ�� */
    for (i=0; i<NAS_CC_MAX_TIMER_NUM; i++)
    {
        if ((enTimerId == f_astCcTimerHandles[i].enTimerId) &&
            (entityId == f_astCcTimerHandles[i].entityId))
        {
            break;
        }
    }

    if (i < NAS_CC_MAX_TIMER_NUM)
    {
        /* ֹͣVOS��ʱ�� */
        if (NAS_StopRelTimer(WUEPS_PID_CC,
                             f_astCcTimerHandles[i].enTimerId,
                             &f_astCcTimerHandles[i].hTimer) == VOS_OK)

        {
            f_astCcTimerHandles[i].hTimer = VOS_NULL_PTR;
            f_astCcTimerHandles[i].enTimerId = TI_NAS_CC_MAX;
        }
        else
        {
            NAS_CC_ERR_LOG("NAS_CC_StopTimer: NAS_StopRelTimer failed.");
        }
    }
    else
    {
        NAS_CC_NORM_LOG1("NAS_CC_StopTimer: Timer is not running.", enTimerId);
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_StopAllTimer
 ��������  : ָֹͣ��CCʵ�������CC��ʱ��
 �������  : entityId  - ��Ҫֹͣ���ж�ʱ����CCʵ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��4��28��
    ��    ��   : z00161729
    �޸�����   : �޸����ⵥAT2D17794:��ʱ����ʱδ��f_astCcTimerHandles����Ӧֵ
*****************************************************************************/
VOS_VOID  NAS_CC_StopAllTimer(
    NAS_CC_ENTITY_ID_T                  entityId
)
{
    VOS_UINT32                          i;

    NAS_CC_ASSERT(entityId < NAS_CC_MAX_ENTITY_NUM);

    /* Ѱ��ָ��ʵ���������е����ж�ʱ�� */
    for (i=0; i<NAS_CC_MAX_TIMER_NUM; i++)
    {
        if ((f_astCcTimerHandles[i].entityId == entityId)
         && (f_astCcTimerHandles[i].hTimer != VOS_NULL_PTR))
        {
            /* ֹͣVOS��ʱ�� */
            if (NAS_StopRelTimer(WUEPS_PID_CC,
                                 f_astCcTimerHandles[i].enTimerId,
                                 &f_astCcTimerHandles[i].hTimer) == VOS_OK)
            {
                f_astCcTimerHandles[i].hTimer = VOS_NULL_PTR;
                f_astCcTimerHandles[i].enTimerId = TI_NAS_CC_MAX;
            }
            else
            {
                NAS_CC_ERR_LOG("NAS_CC_StopAllTimer: NAS_StopRelTimer failed.");
            }
        }
        else if ((f_astCcTimerHandles[i].entityId == entityId)
              && (f_astCcTimerHandles[i].enTimerId < TI_NAS_CC_MAX))
        {
            /*��ʱ����ʱ����Ҫ���f_astCcTimerHandles����Ӧ��¼*/
            f_astCcTimerHandles[i].enTimerId = TI_NAS_CC_MAX;
        }
        else
        {
        }
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_ClearCallOnTimeout
 ��������  : ���ڳ�ʱԭ���������
 �������  : entityId  - ��ʱ��CCʵ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_CC_ClearCallOnTimeout(
    NAS_CC_ENTITY_ID_T                  entityId
)
{
    NAS_CC_ASSERT(entityId < NAS_CC_MAX_ENTITY_NUM);

/* if �������ѿ�������ر������� (TBD) */

    NAS_CC_StopAllTimer(entityId);
    NAS_CC_SendDisconnect(NAS_CC_GetEntityTi(entityId), NAS_CC_CAUSE_102);
    NAS_CC_StartTimer(entityId, TI_NAS_CC_T305, NAS_CC_CAUSE_102);
    NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U11);
}


/*****************************************************************************
 �� �� ��  : NAS_CC_ProcTimeoutMsg
 ��������  : ����ʱ����ʱ��Ϣ���ú��������ݳ�ʱ��Ϣ��Я���Ķ�ʱ�������Ϣ�ҵ�
             ��ʱ��CCʵ��Ͷ�Ӧ�ĳ�ʱ�������������øó�ʱ���������д���
 �������  : pMsg  - ��ʱ����ʱ��Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��06��28��
    ��    ��   : l00167671
    �޸�����   : DCM LOGGER��Ŀ��ʱ���¼��ϱ�
*****************************************************************************/
VOS_VOID  NAS_CC_ProcTimeoutMsg(
    VOS_VOID                            *pMsg
)
{
    REL_TIMER_MSG           *pTmrMsg = (REL_TIMER_MSG *)pMsg;
    NAS_CC_TIMER_ID_ENUM            enTid;
    NAS_CC_ENTITY_ID_T              enEntityId;

    enTid =  (NAS_CC_TIMER_ID_ENUM)((pTmrMsg->ulName) & 0xff);
    if ( enTid >=  TI_NAS_CC_MAX )
    {
        NAS_CC_WARN_LOG1("CC Timer expired,timer id is overflow.", enTid);
        return;
    }
    enEntityId = ((pTmrMsg->ulName) >> 16);

    /* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, begin */
    NAS_TIMER_EventReport(enTid, WUEPS_PID_CC, NAS_OM_EVENT_TIMER_OPERATION_EXPIRED);
    /* added  by l00167671 for v9r1 dcm logger��ά�ɲ���Ŀ, 2013-06-27, end */

    f_astCcTimerInfoTbl[enTid].pfnTimeoutProc(enEntityId, pTmrMsg->ulPara);
}



/*****************************************************************************
 �� �� ��  : NAS_CC_T303Timeout
 ��������  : ��ʱ��T303��ʱ����
 �������  : entityId  - ��ʱ��CCʵ��
             ulParam   - �Զ�������������ô�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  3.��    ��   : 2014��9��26��
    ��    ��   : s00217060
    �޸�����   : for cs_err_log
  4.��    ��   : 2014��10��13��
    ��    ��   : z00161729
    �޸�����   : DTS2014101104705:CC��ʱ����ʱ��Ҫ��ʾֹͣ��ʱ��������f_astCcTimerHandlesȫ�ֱ�������������start��ʱ�����䲻�������
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_T303Timeout(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT32                          ulParam
)
{
    VOS_UINT8 ucTi = NAS_CC_GetEntityTi(entityId);
    NAS_CC_CALL_STATE_ENUM_U8  enCurrState = NAS_CC_GetCallState(entityId);

    NAS_CC_CAUSE_VALUE_ENUM_U32          enCcCause;

    NAS_CC_ASSERT(entityId < NAS_CC_MAX_ENTITY_NUM);

    NAS_CC_INFO_LOG("NAS_CC_T303Timeout");

    NAS_CC_StopTimer(entityId, TI_NAS_CC_T303);

    if (NAS_CC_CALL_STATE_U1 == enCurrState)
    {
        NAS_CC_ClearCallOnTimeout(entityId);
    }
    else if(NAS_CC_CALL_STATE_U0_1 == enCurrState)
    {
        NAS_CC_StopAllTimer(entityId);
        NAS_CC_SendMmccAbortReq(ucTi);

        enCcCause = NAS_CC_CAUSE_CC_INTER_ERR_T303_TIME_OUT;
        NAS_CC_SendMnccMsg(entityId, MNCC_REJ_IND, &enCcCause, sizeof(enCcCause));

        NAS_CC_INFO_LOG1("NAS_CC_T303Timeout: ChangeCallState to U0, current state:", enCurrState);
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0);
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_T303Timeout: Bad state.", enCurrState);
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_T305Timeout
 ��������  : ��ʱ��T305��ʱ����
 �������  : entityId  - ��ʱ��CCʵ��
              ulParam   - �Զ��������disconnect��Ϣ�е�ԭ��ֵ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��10��13��
    ��    ��   : z00161729
    �޸�����   : DTS2014101104705:CC��ʱ����ʱ��Ҫ��ʾֹͣ��ʱ��������f_astCcTimerHandlesȫ�ֱ�������������start��ʱ�����䲻�������
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_T305Timeout(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT32                          ulParam
)
{
    NAS_CC_CALL_STATE_ENUM_U8  enCurrState = NAS_CC_GetCallState(entityId);

    NAS_CC_ASSERT(entityId < NAS_CC_MAX_ENTITY_NUM);

    NAS_CC_INFO_LOG("NAS_CC_T305Timeout");

    NAS_CC_StopTimer(entityId, TI_NAS_CC_T305);

    if (NAS_CC_CALL_STATE_U11 == enCurrState)
    {
        /*
        [5.4.3.5 Abnormal cases]
        send a RELEASE message to the network with the cause number originally
        contained in the DISCONNECT message and optionally, a second cause
        information element with cause #102
        */
        NAS_CC_SendRelease(NAS_CC_GetEntityTi(entityId),
                           VOS_TRUE,
                           (NAS_CC_CAUSE_VALUE_ENUM_U32)ulParam,
                           VOS_TRUE,
                           NAS_CC_CAUSE_102);

        NAS_CC_StartTimer(entityId, TI_NAS_CC_T308, NAS_CC_T308_FIRST);

        NAS_CC_INFO_LOG("NAS_CC_T305Timeout ChangeCallState to U19");

        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U19);
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_T305Timeout: Bad state.", enCurrState);
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_T308Timeout
 ��������  : ��ʱ��T308��ʱ����
 �������  : entityId  - ��ʱ��CCʵ��
              ulParam   - �Զ������������T308�Ĵ���
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��10��13��
    ��    ��   : z00161729
    �޸�����   : DTS2014101104705:CC��ʱ����ʱ��Ҫ��ʾֹͣ��ʱ��������f_astCcTimerHandlesȫ�ֱ�������������start��ʱ�����䲻�������
  3.��    ��   : 2015-04-14
    ��    ��   : n00269697
    �޸�����   : CHR�Ż���Ŀ��T308�ڶ��γ�ʱ��Я��ԭ��ֵ102
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_T308Timeout(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT32                          ulParam
)
{
    NAS_CC_CALL_STATE_ENUM_U8  enCurrState = NAS_CC_GetCallState(entityId);
    NAS_CC_MSG_RELEASE_COMPLETE_MT_STRU     stRelComp;

    VOS_UINT8  ucTi = NAS_CC_GetEntityTi(entityId);

    NAS_CC_ASSERT(entityId < NAS_CC_MAX_ENTITY_NUM);

    NAS_CC_StopTimer(entityId, TI_NAS_CC_T308);

    if (enCurrState != NAS_CC_CALL_STATE_U19)
    {
        NAS_CC_ERR_LOG1("NAS_CC_T308Timeout: Bad state.", enCurrState);
        return;
    }

    NAS_CC_INFO_LOG("NAS_CC_T308Timeout");

    if (NAS_CC_T308_FIRST == ulParam)
    {
        /* ����ǵ�һ�γ�ʱ���ٴη���Release��Ϣ */
        NAS_CC_SendRelease(ucTi, VOS_TRUE, NAS_CC_CAUSE_102, VOS_FALSE, 0);
        NAS_CC_StartTimer(entityId, TI_NAS_CC_T308, NAS_CC_T308_SECOND);
    }
    else
    {
        /* �ͷ�MM���� */
        NAS_CC_SendMmccRelReq(ucTi, MMCC_RELEASE_SPECIFIC);

        /* CHR�Ż���Ŀ��T308�ڶ��γ�ʱ��Я��ԭ��ֵ102 */
        PS_MEM_SET(&stRelComp, 0, sizeof(NAS_CC_MSG_RELEASE_COMPLETE_MT_STRU));

        NAS_CC_FillCauseIe(NAS_CC_CAUSE_102, &stRelComp.stCause);

        /* �ϱ�MNCC_REL_CNFԭ�� */
        NAS_CC_SendMnccMsg(entityId, MNCC_REL_CNF, &stRelComp, sizeof(NAS_CC_MSG_RELEASE_COMPLETE_MT_STRU));

        /* ����null״̬ */
        NAS_CC_INFO_LOG("NAS_CC_T308Timeout ChangeCallState to U0");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0);
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_T310Timeout
 ��������  : ��ʱ��T310��ʱ����
 �������  : entityId  - ��ʱ��CCʵ��
              ulParam   - �Զ�������������ô�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��10��13��
    ��    ��   : z00161729
    �޸�����   : DTS2014101104705:CC��ʱ����ʱ��Ҫ��ʾֹͣ��ʱ��������f_astCcTimerHandlesȫ�ֱ�������������start��ʱ�����䲻�������
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_T310Timeout(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT32                          ulParam
)
{
    NAS_CC_CALL_STATE_ENUM_U8  enCurrState = NAS_CC_GetCallState(entityId);

    NAS_CC_ASSERT(entityId < NAS_CC_MAX_ENTITY_NUM);

    NAS_CC_INFO_LOG("NAS_CC_T310Timeout");

    NAS_CC_StopTimer(entityId, TI_NAS_CC_T310);

    if (NAS_CC_CALL_STATE_U3 == enCurrState)
    {
        NAS_CC_ClearCallOnTimeout(entityId);
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_T310Timeout: Bad state.", enCurrState);
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_T313Timeout
 ��������  : ��ʱ��T313��ʱ����
 �������  : entityId  - ��ʱ��CCʵ��
              ulParam   - �Զ�������������ô�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��10��13��
    ��    ��   : z00161729
    �޸�����   : DTS2014101104705:CC��ʱ����ʱ��Ҫ��ʾֹͣ��ʱ��������f_astCcTimerHandlesȫ�ֱ�������������start��ʱ�����䲻�������
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_T313Timeout(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT32                          ulParam
)
{
    NAS_CC_CALL_STATE_ENUM_U8  enCurrState = NAS_CC_GetCallState(entityId);

    NAS_CC_ASSERT(entityId < NAS_CC_MAX_ENTITY_NUM);

    NAS_CC_INFO_LOG("NAS_CC_T313Timeout");

    NAS_CC_StopTimer(entityId, TI_NAS_CC_T313);

    if (NAS_CC_CALL_STATE_U8 == enCurrState)
    {
        NAS_CC_ClearCallOnTimeout(entityId);
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_T313Timeout: Bad state.", enCurrState);
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_T323Timeout
 ��������  : ��ʱ��T323��ʱ����
 �������  : entityId  - ��ʱ��CCʵ��
              ulParam   - �Զ�������������ô�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��10��13��
    ��    ��   : z00161729
    �޸�����   : DTS2014101104705:CC��ʱ����ʱ��Ҫ��ʾֹͣ��ʱ��������f_astCcTimerHandlesȫ�ֱ�������������start��ʱ�����䲻�������
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_T323Timeout(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT32                          ulParam
)
{
    NAS_CC_CALL_STATE_ENUM_U8  enCurrState = NAS_CC_GetCallState(entityId);

    NAS_CC_ASSERT(entityId < NAS_CC_MAX_ENTITY_NUM);

    NAS_CC_INFO_LOG("NAS_CC_T323Timeout");

    NAS_CC_StopTimer(entityId, TI_NAS_CC_T323);

    if (NAS_CC_CALL_STATE_U26 == enCurrState)
    {
        NAS_CC_ClearCallOnTimeout(entityId);
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_T323Timeout: Bad state.", enCurrState);
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_T332Timeout
 ��������  : ��ʱ��T332��ʱ����
 �������  : entityId  - ��ʱ��CCʵ��
              ulParam   - �Զ�������������ô�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��10��13��
    ��    ��   : z00161729
    �޸�����   : DTS2014101104705:CC��ʱ����ʱ��Ҫ��ʾֹͣ��ʱ��������f_astCcTimerHandlesȫ�ֱ�������������start��ʱ�����䲻�������
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_T332Timeout(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT32                          ulParam
)
{
    NAS_CC_CALL_STATE_ENUM_U8  enCurrState = NAS_CC_GetCallState(entityId);
    VOS_UINT8        ucTi = NAS_CC_GetEntityTi(entityId);

    NAS_CC_ASSERT(entityId < NAS_CC_MAX_ENTITY_NUM);

    NAS_CC_INFO_LOG("NAS_CC_T332Timeout");

    NAS_CC_StopTimer(entityId, TI_NAS_CC_T332);

    if (NAS_CC_CALL_STATE_U0_3 == enCurrState)
    {
        NAS_CC_SendReleaseComplete(ucTi, VOS_TRUE, NAS_CC_CAUSE_102);

        NAS_CC_SendMmccRelReq(ucTi, MMCC_RELEASE_SPECIFIC);

        NAS_CC_INFO_LOG("NAS_CC_T332Timeout ChangeCallState to U0");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0);
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_T332Timeout: Bad state.", enCurrState);
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_T335Timeout
 ��������  : ��ʱ��T335��ʱ����
 �������  : entityId  - ��ʱ��CCʵ��
              ulParam   - �Զ�������������ô�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  3.��    ��   : 2014��9��26��
    ��    ��   : s00217060
    �޸�����   : for cs_err_log
  4.��    ��   : 2014��10��13��
    ��    ��   : z00161729
    �޸�����   : DTS2014101104705:CC��ʱ����ʱ��Ҫ��ʾֹͣ��ʱ��������f_astCcTimerHandlesȫ�ֱ�������������start��ʱ�����䲻�������
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_T335Timeout(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT32                          ulParam
)
{
    NAS_CC_CALL_STATE_ENUM_U8   enCurrState = NAS_CC_GetCallState(entityId);
    VOS_UINT8                   ucTi = NAS_CC_GetEntityTi(entityId);

    NAS_CC_CAUSE_VALUE_ENUM_U32          enCcCause;

    NAS_CC_ASSERT(entityId < NAS_CC_MAX_ENTITY_NUM);

    NAS_CC_StopTimer(entityId, TI_NAS_CC_T335);

    if (NAS_CC_CALL_STATE_U0_5 == enCurrState)
    {
        NAS_CC_SendReleaseComplete(ucTi, VOS_TRUE, NAS_CC_CAUSE_102);

        NAS_CC_SendMmccRelReq(ucTi, MMCC_RELEASE_SPECIFIC);

        enCcCause = NAS_CC_CAUSE_CC_INTER_ERR_T335_TIME_OUT;
        NAS_CC_SendMnccMsg(entityId, MNCC_REJ_IND, &enCcCause, sizeof(enCcCause));

        NAS_CC_INFO_LOG("NAS_CC_T335Timeout ChangeCallState to U0");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0);
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_T335Timeout: Bad state.", enCurrState);
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_T336Timeout
 ��������  : ��ʱ��T336��ʱ����
 �������  : entityId  - ��ʱ��CCʵ��
              ulParam   - �Զ�������������ô�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��2��18��
    ��    ��   : z00161729
    �޸�����   : DTS2013021803962:start dtmf rej������յ�stop dtmf������������罻��ֱ�ӻظ�stop dtmf cnf
  3.��    ��   : 2014��10��13��
    ��    ��   : z00161729
    �޸�����   : DTS2014101104705:CC��ʱ����ʱ��Ҫ��ʾֹͣ��ʱ��������f_astCcTimerHandlesȫ�ֱ�������������start��ʱ�����䲻�������

*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_T336Timeout(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT32                          ulParam
)
{
    NAS_CC_CAUSE_VALUE_ENUM_U32          cause;

    NAS_CC_ASSERT(entityId < NAS_CC_MAX_ENTITY_NUM);

    NAS_CC_INFO_LOG("NAS_CC_T336Timeout");

    NAS_CC_StopTimer(entityId, TI_NAS_CC_T336);

    if (NAS_CC_GetDtmfState(entityId) != NAS_CC_DTMF_S_START_REQ)
    {
        NAS_CC_ERR_LOG("NAS_CC_T336Timeout: Not in start_req state.");
        return;
    }

    /* ����MNCC_START_DTMF_REJԭ�� */
    cause = NAS_CC_CAUSE_102;
    NAS_CC_SendMnccMsg(entityId, MNCC_START_DTMF_REJ, &cause, sizeof(cause));

    NAS_CC_ChangeDtmfState(entityId, NAS_CC_DTMF_S_START_REJ);

    /* ���ͻ����dtmf���� */
    NAS_CC_SendBufferedDtmfReq(entityId);
}


/*****************************************************************************
 �� �� ��  : NAS_CC_T337Timeout
 ��������  : ��ʱ��T337��ʱ����
 �������  : entityId  - ��ʱ��CCʵ��
              ulParam   - �Զ�������������ô�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��10��13��
    ��    ��   : z00161729
    �޸�����   : DTS2014101104705:CC��ʱ����ʱ��Ҫ��ʾֹͣ��ʱ��������f_astCcTimerHandlesȫ�ֱ�������������start��ʱ�����䲻�������
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_T337Timeout(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT32                          ulParam
)
{
    NAS_CC_ASSERT(entityId < NAS_CC_MAX_ENTITY_NUM);

    NAS_CC_INFO_LOG("NAS_CC_T337Timeout");

    NAS_CC_StopTimer(entityId, TI_NAS_CC_T337);

    if (NAS_CC_GetDtmfState(entityId) != NAS_CC_DTMF_S_STOP_REQ)
    {
        NAS_CC_ERR_LOG("NAS_CC_T337Timeout: Not in stop_req state.");
        return;
    }

    /* stop dtmf������ʹ��ʱҲ��Ϊ�����ɹ��ˣ������һ���澯 */
    NAS_CC_SendMnccMsg(entityId, MNCC_STOP_DTMF_CNF, VOS_NULL_PTR, 0);
    NAS_CC_WARN_LOG("Timeout when stop dtmf.");

    NAS_CC_INFO_LOG("NAS_CC_T337Timeout: ChangeDtmfState IDLE");
    NAS_CC_ChangeDtmfState(entityId, NAS_CC_DTMF_S_IDLE);

    /* ���ͻ����dtmf���� */
    NAS_CC_SendBufferedDtmfReq(entityId);
}


/*****************************************************************************
 �� �� ��  : NAS_CC_HoldTimeout
 ��������  : Hold������ʱ����ʱ����
 �������  : entityId  - ��ʱ��CCʵ��
              ulParam   - �Զ�������������ô�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��02��03��
    ��    ��   : Y00213812
    �޸�����   : DTS2013020203946,hold��ʱ��ԭ���б���ΪNAS_CC_HOLD_AUX_S_CALL_HELD״̬��
                 ��������Ǩ��ԭ״̬
  3.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
  4.��    ��   : 2014��10��13��
    ��    ��   : z00161729
    �޸�����   : DTS2014101104705:CC��ʱ����ʱ��Ҫ��ʾֹͣ��ʱ��������f_astCcTimerHandlesȫ�ֱ�������������start��ʱ�����䲻�������
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_HoldTimeout(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT32                          ulParam
)
{
    NAS_CC_HOLD_AUX_STATE_ENUM_U8   holdState = NAS_CC_GetHoldAuxState(entityId);
    NAS_CC_CAUSE_VALUE_ENUM_U32      cause = NAS_CC_CAUSE_102;

    NAS_CC_ASSERT(entityId < NAS_CC_MAX_ENTITY_NUM);

    NAS_CC_StopTimer(entityId, TI_NAS_CC_HOLD);

    if (NAS_CC_HOLD_AUX_S_HOLD_REQ == holdState)
    {
        /* Modified by l00198894 for V9R1 STK����, 2013/07/11, begin */
        /* ��¼����ҵ���л�״̬������ͳһ����ҵ���л�״̬������ */
        NAS_CC_SetSsSwitchHoldInfo(entityId, NAS_CC_SS_SWITCH_TIME_OUT, cause);

        NAS_CC_ProcSsSwitchMain();
        /* Modified by l00198894 for V9R1 STK����, 2013/07/11, end */
    }
    else if (NAS_CC_HOLD_AUX_S_RETRIEVE_REQ == holdState)
    {
        /* Modified by l00198894 for V9R1 STK����, 2013/07/11, begin */
        /* ��¼����ҵ���л�״̬������ͳһ����ҵ���л�״̬������ */
        NAS_CC_SetSsSwitchRetrieveInfo(entityId, NAS_CC_SS_SWITCH_TIME_OUT, cause);

        NAS_CC_ProcSsSwitchMain();
        /* Modified by l00198894 for V9R1 STK����, 2013/07/11, end */
    }
    else
    {
        NAS_CC_ERR_LOG1("NAS_CC_HoldTimeout: Bad hold state.", holdState);
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_MptyTimeout
 ��������  : MPTY������ʱ����ʱ����
 �������  : entityId  - ��ʱ��CCʵ��
             ulParam   - �Զ����������Ų�����invoke ID
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
  3.��    ��   : 2014��10��13��
    ��    ��   : z00161729
    �޸�����   : DTS2014101104705:CC��ʱ����ʱ��Ҫ��ʾֹͣ��ʱ��������f_astCcTimerHandlesȫ�ֱ�������������start��ʱ�����䲻�������
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_MptyTimeout(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT32                          ulParam
)
{
    /* Modified by l00198894 for V9R1 STK����, 2013/07/11, begin */
    VOS_UINT8                           ucInvokeId = (VOS_UINT8)ulParam;
    NAS_SS_OPERATION_ENUM_U8            enOperation;
    NAS_CC_ENTITY_ID_T                  ulHoldEntityID;
    NAS_CC_ENTITY_ID_T                  ulRetrieveEntityID;

    NAS_CC_ASSERT(entityId < NAS_CC_MAX_ENTITY_NUM);

    NAS_CC_INFO_LOG("NAS_CC_MptyTimeout");

    NAS_CC_StopTimer(entityId, TI_NAS_CC_MPTY);

    if (NAS_CC_RestoreSsOperation(entityId, ucInvokeId, &enOperation) != VOS_OK)
    {
        NAS_CC_ERR_LOG1("NAS_CC_RestoreSsOperation: Restore SsOperation failure.", (VOS_INT32)entityId);
        return;
    }

    NAS_CC_HandleMptyEvent(entityId, NAS_CC_MPTY_EVT_FAIL, enOperation);

    /* ���entityId��¼���˲���ҵ���л���Ϣ�У��򻺴����Ϣ�����򷢳� */
    ulHoldEntityID      = NAS_CC_GetSsSwitchHoldEntityID();
    ulRetrieveEntityID  = NAS_CC_GetSsSwitchRetrieveEntityID();

    if (entityId == ulHoldEntityID)
    {
        /* ����InvokeId */
        NAS_CC_SetSsSwitchInvokeId(VOS_TRUE, ucInvokeId);

        NAS_CC_SetSsSwitchHoldInfo(entityId, NAS_CC_SS_SWITCH_TIME_OUT, NAS_CC_CAUSE_102);

        NAS_CC_ProcSsSwitchMain();
    }
    else if (entityId == ulRetrieveEntityID)
    {
        /* ����InvokeId */
        NAS_CC_SetSsSwitchInvokeId(VOS_TRUE, ucInvokeId);

        NAS_CC_SetSsSwitchRetrieveInfo(entityId, NAS_CC_SS_SWITCH_TIME_OUT, NAS_CC_CAUSE_102);

        NAS_CC_ProcSsSwitchMain();
    }
    else
    {
        NAS_CC_SendMnccMsg(entityId,
                           MNCC_FACILITY_LOCAL_REJ,
                           &ucInvokeId,
                           sizeof(ucInvokeId));
    }

    return;
    /* Modified by l00198894 for V9R1 STK����, 2013/07/11, end */
}

/*****************************************************************************
 �� �� ��  : NAS_CC_ECTTimeout
 ��������  : ECT������ʱ����ʱ����
 �������  : entityId  - ��ʱ��CCʵ��
              ulParam   - �Զ����������Ų�����invoke ID
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��10��13��
    ��    ��   : z00161729
    �޸�����   : DTS2014101104705:CC��ʱ����ʱ��Ҫ��ʾֹͣ��ʱ��������f_astCcTimerHandlesȫ�ֱ�������������start��ʱ�����䲻�������
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_ECTTimeout(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT32                          ulParam
)
{
    VOS_UINT8                   ucInvokeId = (VOS_UINT8)ulParam;
    NAS_SS_OPERATION_ENUM_U8    enOperation;

    NAS_CC_ASSERT(entityId < NAS_CC_MAX_ENTITY_NUM);

    NAS_CC_INFO_LOG("NAS_CC_ECTTimeout");

    NAS_CC_StopTimer(entityId, TI_NAS_CC_ECT);

    if (NAS_CC_RestoreSsOperation(entityId, ucInvokeId, &enOperation) != VOS_OK)
    {
        NAS_CC_ERR_LOG1("NAS_CC_RestoreSsOperation: Restore SsOperation failure.", (VOS_INT32)entityId);
        return;
    }

    NAS_CC_SendMnccMsg(entityId,
                       MNCC_FACILITY_LOCAL_REJ,
                       &ucInvokeId,
                       sizeof(ucInvokeId));
}



/*****************************************************************************
 �� �� ��  : NAS_CC_UserConnTimeout
 ��������  : �û������ӽ�����ʱ
 �������  : entityId - ��ʱ��CCʵ��
             ulParam  - �Զ�������������ô�
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��4��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��10��13��
    ��    ��   : z00161729
    �޸�����   : DTS2014101104705:CC��ʱ����ʱ��Ҫ��ʾֹͣ��ʱ��������f_astCcTimerHandlesȫ�ֱ�������������start��ʱ�����䲻�������

*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_UserConnTimeout(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT32                          ulParam
)
{
/*
    If:
    - the user connection has to be attached but no appropriate channel is available
    for a contiguous time of 30 seconds; or if

    - the codec or interworking function is de-activated for a contiguous time of 30
    seconds;

    then the mobile station may initiate call clearing.
*/
    NAS_CC_StopTimer(entityId, TI_NAS_CC_USER_CONN);

    NAS_CC_INFO_LOG("NAS_CC_UserConnTimeout");

}


/*****************************************************************************
 �� �� ��  : NAS_CC_RabInactProtectTimeout
 ��������  : Rabȥ�����Ժ�ı�����ʱ����ʱ
 �������  : entityId - ��ʱ��CCʵ��
             ulParam  - �Զ�������������ô�
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��11��10��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  3.��    ��   : 2014��9��24��
    ��    ��   : s00217060
    �޸�����   : for cs_err_log
  4.��    ��   : 2014��10��13��
    ��    ��   : z00161729
    �޸�����   : DTS2014101104705:CC��ʱ����ʱ��Ҫ��ʾֹͣ��ʱ��������f_astCcTimerHandlesȫ�ֱ�������������start��ʱ�����䲻�������
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_RabInactProtectTimeout(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT32                          ulParam
)
{
    VOS_UINT8                           ucTi;

    NAS_CC_CAUSE_VALUE_ENUM_U32          enCcCause;


    ucTi = NAS_CC_GetEntityTi(entityId);

    NAS_CC_StopTimer(entityId, TI_NAS_CC_RABMINACT_PROTECT);

    /* �����Ӧʵ����active״̬���Ҷϵ绰 */
    if (NAS_CC_CALL_STATE_U10 == NAS_CC_GetCallState(entityId))
    {
        NAS_CC_SendReleaseComplete(ucTi, VOS_TRUE, NAS_CC_CAUSE_111);

        NAS_CC_SendMmccRelReq(ucTi, MMCC_RELEASE_SPECIFIC);

        enCcCause = NAS_CC_CAUSE_CC_INTER_ERR_WAIT_RAB_TIME_OUT;
        NAS_CC_SendMnccMsg(entityId, MNCC_REJ_IND, &enCcCause, sizeof(enCcCause));

        NAS_CC_INFO_LOG("NAS_CC_RabInactProtectTimeout ChangeCallState to U0");
        NAS_CC_ChangeCallState(entityId, NAS_CC_CALL_STATE_U0);
    }

}

/*****************************************************************************
 �� �� ��  : NAS_CC_StopRabProtectTimer
 ��������  : ֹͣ��ǰ��Rabȥ����ı�����ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��10��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_CC_StopRabProtectTimer(VOS_VOID)
{
    VOS_UINT32                          i;

    /*ֹͣ��ʱ��*/
    for (i = 0; i < NAS_CC_MAX_ENTITY_NUM; i++)
    {
        if (NAS_CC_CALL_STATE_U10 == NAS_CC_GetCallState(i))
        {
            NAS_CC_StopTimer(i, TI_NAS_CC_RABMINACT_PROTECT);
        }
    }
}

/*****************************************************************************
 �� �� ��  : NAS_CC_StartRabProtectTimer
 ��������  : ������ǰ��Rabȥ����ı�����ʱ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��10��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_CC_StartRabProtectTimer(VOS_VOID)
{
    VOS_UINT32                          i;

    /*������ʱ��*/
    for (i = 0; i < NAS_CC_MAX_ENTITY_NUM; i++)
    {
        if (NAS_CC_CALL_STATE_U10 == NAS_CC_GetCallState(i))
        {
            NAS_CC_StartTimer(i, TI_NAS_CC_RABMINACT_PROTECT, 0);
        }
    }
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

