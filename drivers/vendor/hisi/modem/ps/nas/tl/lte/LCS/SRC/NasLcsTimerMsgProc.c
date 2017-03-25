/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasLcsTimerMsgProc.c
    Description : ����ʱ����ʱ��Ϣ
    History     :
            1.lihong  00150010       2015-09-28  Draft Enact
******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "vos.h"
#include    "PsLogdef.h"
#include    "PsTypeDef.h"
#include    "NasLcsOm.h"
#include    "NasLcsEmmMsgProc.h"
#include    "NasLcsMmMsgProc.h"

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/



#define    THIS_FILE_ID            PS_FILE_ID_NASLCSTIMERMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLCSTIMERMSGPROC_C

#if (FEATURE_LPP == FEATURE_ON)



/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : NAS_LCS_RcvWaitNwRspTimerExp
 Discription    : ����ȴ����綨ʱ����ʱ
 Input          : ulIndex---------------ʵ������
 Output         : None
 Return         : VOS_VOID
 History:
      1.lihong 00150010 2015-10-10 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_RcvWaitNwRspTimerExp
(
    VOS_UINT32                          ulIndex
)
{
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity    = NAS_LCS_NULL_PTR;

    NAS_LCS_INFO_LOG1("NAS_LCS_RcvWaitNwRspTimerExp:ulIndex= ", ulIndex);
    TLPS_PRINT2LAYER_INFO1(NAS_LCS_RcvWaitNwRspTimerExp_ENUM, LNAS_LCS_InvalidEntityType, ulIndex);

    /* �Ƿ�ΪMOLR */
    if (PS_TRUE != NAS_LCS_IsMoLr(ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitNwRspTimerExp:Is not MOLR!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitNwRspTimerExp_ENUM, LNAS_LCS_InvalidEntityType);

        return ;
    }

    pstLcsEntity = NAS_LCS_GetLcsEntity(ulIndex);
    if (NAS_LCS_ENTITY_USED != pstLcsEntity->enUsedFlag)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitNwRspTimerExp:entity not exist!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitNwRspTimerExp_ENUM, LNAS_LCS_EntityNotExist);

        return ;
    }

    /* ״̬�Ƿ�Ϊ�ȴ�����ظ� */
    if (NAS_LCS_ENTITY_STATE_WAIT_NW_RSP != NAS_LCS_GetEntityState(ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitNwRspTimerExp:state invalid!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitNwRspTimerExp_ENUM, LNAS_LCS_EntityStateInvalid);

        return ;
    }

    if (NAS_LCS_CONN_STATE_CONN == NAS_LCS_GetEntityConnState(ulIndex))
    {
        /* ����RELEASE COMPLTE��Ϣ���������� */
        NAS_LCS_SndReleaseComplte(ulIndex);
    }

    NAS_LCS_ClearLcsEntityAndNotify(ulIndex, TAF_LCS_CAUSE_LCS_NW_TIMER_OUT);
}

/*****************************************************************************
 Function Name  : NAS_LCS_RcvWaitReestTimerExp
 Discription    : �����ؽ�����ʱ����ʱ
 Input          : ulIndex---------------����
 Output         : None
 Return         : VOS_VOID
 History:
      1.lihong 00150010 2015-10-10 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_RcvWaitReestTimerExp
(
    VOS_UINT32                          ulIndex
)
{
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity    = NAS_LCS_NULL_PTR;

    NAS_LCS_INFO_LOG1("NAS_LCS_RcvWaitReestTimerExp:ulIndex= ", ulIndex);
    TLPS_PRINT2LAYER_INFO1(NAS_LCS_RcvWaitReestTimerExp_ENUM, LNAS_LCS_InvalidEntityType, ulIndex);

    /* �Ƿ�ΪMOLR */
    if (PS_TRUE != NAS_LCS_IsMoLr(ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitReestTimerExp:Is not MOLR!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitReestTimerExp_ENUM, LNAS_LCS_InvalidEntityType);

        return ;
    }

    pstLcsEntity = NAS_LCS_GetLcsEntity(ulIndex);
    if (NAS_LCS_ENTITY_USED != pstLcsEntity->enUsedFlag)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitReestTimerExp:entity not exist!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitReestTimerExp_ENUM, LNAS_LCS_EntityNotExist);

        return ;
    }

    /* ״̬�Ƿ�Ϊ�ȴ�����ظ� */
    if (NAS_LCS_ENTITY_STATE_WAIT_NW_RSP != NAS_LCS_GetEntityState(ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitReestTimerExp:state invalid!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitReestTimerExp_ENUM, LNAS_LCS_EntityStateInvalid);

        return ;
    }

    /* ����Ӧ�򷢽������� */
    if (NAS_LCS_DOMAIN_TYPE_EPC_LCS == NAS_LCS_GetEntityLcsDomain(ulIndex))
    {
        NAS_LCS_SndLmmEstReq(NAS_LCS_GetEntityTi(ulIndex));
    }
    else
    {
        NAS_LCS_SndMmEstReq(NAS_LCS_GetEntityTi(ulIndex));
    }

    /* ����ʵ������״̬Ϊ���������� */
    NAS_LCS_SetEntityConnState(ulIndex, NAS_LCS_CONN_STATE_ESTING);
}

/*****************************************************************************
 Function Name  : NAS_LCS_RcvWaitPeriodIntervelTimerExp
 Discription    : �������ڼ����ʱ����ʱ
 Input          : ulIndex---------------����
 Output         : None
 Return         : VOS_VOID
 History:
      1.lihong 00150010 2015-10-10 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_RcvWaitPeriodIntervelTimerExp
(
    VOS_UINT32                          ulIndex
)
{
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity    = NAS_LCS_NULL_PTR;

    NAS_LCS_INFO_LOG1("NAS_LCS_RcvWaitPeriodIntervelTimerExp:ulIndex= ", ulIndex);
    TLPS_PRINT2LAYER_INFO1(NAS_LCS_RcvWaitPeriodIntervelTimerExp_ENUM, LNAS_LCS_InvalidEntityType, ulIndex);

    /* �Ƿ�ΪTAF MOLR */
    if (NAS_LCS_MO_LR_TAF_INDEX != ulIndex)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitPeriodIntervelTimerExp:Is not TAF-MOLR!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitPeriodIntervelTimerExp_ENUM, LNAS_LCS_InvalidIndex);

        return ;
    }

    pstLcsEntity = NAS_LCS_GetLcsEntity(ulIndex);
    if (NAS_LCS_ENTITY_USED != pstLcsEntity->enUsedFlag)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitPeriodIntervelTimerExp:entity not exist!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitPeriodIntervelTimerExp_ENUM, LNAS_LCS_EntityNotExist);

        return ;
    }

    /* ״̬�Ƿ�Ϊ���ڼ�� */
    if (NAS_LCS_ENTITY_STATE_PERIOD_INTERVAL != NAS_LCS_GetEntityState(ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitPeriodIntervelTimerExp:state invalid!");
        TLPS_PRINT2LAYER_ERROR1(NAS_LCS_RcvWaitNwRspTimerExp_ENUM, LNAS_LCS_EntityStateInvalid, NAS_LCS_GetEntityState(ulIndex));

        return ;
    }

    /* ʵ��״̬ת���ȴ�������Ӧ */
    NAS_LCS_SetEntityState(ulIndex, NAS_LCS_ENTITY_STATE_WAIT_NW_RSP);

    /* �����ȴ�������Ӧ��ʱ�� */
    NAS_LCS_StartTimer(ulIndex, TI_NAS_LCS_WAIT_NW_RSP_TIMER);

    /* ���������̬�������FACILITY�������ࣻ���������� */
    if (NAS_LCS_CONN_STATE_CONN == NAS_LCS_GetEntityConnState(ulIndex))
    {
        /* ����FACILITY��Ϣ���������� */
        NAS_LCS_SndFacility(ulIndex);
    }
    else
    {
        /* ����Ӧ�򷢽������� */
        if (NAS_LCS_DOMAIN_TYPE_EPC_LCS == NAS_LCS_GetEntityLcsDomain(ulIndex))
        {
            NAS_LCS_SndLmmEstReq(NAS_LCS_GetEntityTi(ulIndex));
        }
        else
        {
            NAS_LCS_SndMmEstReq(NAS_LCS_GetEntityTi(ulIndex));
        }

        /* ����ʵ������״̬Ϊ���������� */
        NAS_LCS_SetEntityConnState(ulIndex, NAS_LCS_CONN_STATE_ESTING);

        /* ���ý������Դ��� */
        NAS_LCS_ResetEntityEstRetryTimers(ulIndex);
    }
}

/*****************************************************************************
 Function Name  : NAS_LCS_RcvWaitUeRspTimerExp
 Discription    : ����ȴ��û���Ӧ��ʱ����ʱ
 Input          : ulIndex---------------����
 Output         : None
 Return         : VOS_VOID
 History:
      1.lihong 00150010 2015-10-10 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_RcvWaitUeRspTimerExp
(
    VOS_UINT32                          ulIndex
)
{
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity    = NAS_LCS_NULL_PTR;

    NAS_LCS_INFO_LOG1("NAS_LCS_RcvWaitUeRspTimerExp:ulIndex= ", ulIndex);
    TLPS_PRINT2LAYER_INFO1(NAS_LCS_RcvWaitUeRspTimerExp_ENUM, LNAS_LCS_InvalidEntityType, ulIndex);

    if ((ulIndex > NAS_LCS_MT_LR_ENTITY_INDEX_END) || (ulIndex < NAS_LCS_MT_LR_ENTITY_INDEX_BEGIN))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitUeRspTimerExp:is not mt-lr!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitNwRspTimerExp_ENUM, LNAS_LCS_InvalidEntityType);

        return ;
    }

    pstLcsEntity = NAS_LCS_GetLcsEntity(ulIndex);
    if (NAS_LCS_ENTITY_USED != pstLcsEntity->enUsedFlag)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitUeRspTimerExp:entity not exist!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitUeRspTimerExp_ENUM, LNAS_LCS_EntityNotExist);

        return ;
    }

    /* ״̬�Ƿ�Ϊ�ȴ��û��ظ� */
    if (NAS_LCS_ENTITY_STATE_WAIT_USER_RSP != NAS_LCS_GetEntityState(ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_RcvWaitUeRspTimerExp:state invalid!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_RcvWaitUeRspTimerExp_ENUM, LNAS_LCS_EntityStateInvalid);

        return ;
    }

    /* ֪ͨMM�����ͷ����TI��ص�LCSʵ����Ϣ, MTLR������֪ͨMM�Ƿ������ͷ���· */
    NAS_LCS_JudgeSndMmRelReq(ulIndex);

    /* �ͷ�LCSʵ�� */
    NAS_LCS_ClearSingleLcsEntity(ulIndex, TAF_LCS_CAUSE_LCS_USER_TIMER_OUT);
}


/*****************************************************************************
Function Name  : NAS_LCS_TimerMsgDistr
Description    : LCSģ�鶨ʱ����ʱ��Ϣ������
Input          : VOS_VOID *pRcvMsg
Output         : VOS_VOID
Return Value   : VOS_VOID

History        :
  lihong 00150010 2015-9-28  �¿���
*****************************************************************************/
VOS_VOID NAS_LCS_TimerMsgDistr( VOS_VOID *pRcvMsg )
{

    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType  = TI_NAS_LCS_TIMER_BUTT;
    VOS_UINT32                          ulIndex         = 0;

    NAS_LCS_NORM_LOG("NAS_LCS_TimerMsgDistr is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LCS_TimerMsgDistr_ENUM, LNAS_ENTRY);

    ulIndex         = PS_GET_REL_TIMER_NAME(pRcvMsg);
    enLcsTimerType  = (NAS_LCS_TIMER_ID_ENUM_UINT8)PS_GET_REL_TIMER_PARA(pRcvMsg);

    NAS_LCS_SndOmTimerExpire(ulIndex, enLcsTimerType);

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch(enLcsTimerType)
    {
        case TI_NAS_LCS_WAIT_NW_RSP_TIMER:
            NAS_LCS_RcvWaitNwRspTimerExp(ulIndex);
            break;

        case TI_NAS_LCS_WAIT_UE_RSP_TIMER:
            NAS_LCS_RcvWaitUeRspTimerExp(ulIndex);
            break;

        case TI_NAS_LCS_WATI_REEST_TIMER:
            NAS_LCS_RcvWaitReestTimerExp(ulIndex);
            break;

        case TI_NAS_LCS_PERIOD_INTERVAL_TIMER:
            NAS_LCS_RcvWaitPeriodIntervelTimerExp(ulIndex);
            break;

        default:
            NAS_LCS_WARN_LOG("NAS_LCS_TimerMsgDistr:NORM: Error TimerId!");
            TLPS_PRINT2LAYER_ERROR(NAS_LCS_TimerMsgDistr_ENUM, LNAS_LCS_InvalidTimerId);
            break;
    }

    return;
}


#endif
#ifdef __cplusplus
#if __cplusplus
    }
    #endif
#endif
/* end of NasLcsTimerMsgProc.c */
