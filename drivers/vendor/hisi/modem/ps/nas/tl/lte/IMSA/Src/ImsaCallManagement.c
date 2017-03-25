/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : ImsaCallManagement.c
  Description     : ��C�ļ�ʵ�ֺ��й���ģ��ĳ�ʼ�����ڲ���Ϣ�Ĵ���ͷ��ͣ�
                    �ṩ�ⲿ���õ�API
  History           :
     1.sunbing 49683      2013-06-19  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include <limits.h>
#include "ImsaEntity.h"
#include "ImsaCallManagement.h"
#include "ImsaRegManagement.h"
#include "ImsaPublic.h"
#include "ImsaImsAdaption.h"
#include "ImsaImsInterface.h"
#include "CallImsaInterface.h"
#include "ImsaServiceManagement.h"
#include "ImsaLrrcInterface.h"
#include "ImsaProcAtMsg.h"
#include "ImsaProcSpmMsg.h"
#include "VcImsaInterface.h"
#include "ImsaProcImsCallMsg.h"

#include "ImsaProcUssdMsg.h"

/*lint -e767*/
#define    THIS_FILE_ID         PS_FILE_ID_IMSACALLMANAGEMENT_C
#define    THIS_NAS_FILE_ID     NAS_FILE_ID_IMSACALLMANAGEMENT_C

/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_ON == FEATURE_IMS)

/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/
static VOS_UINT16 g_ausSsacBarringTimer[] = {4, 8, 16, 32, 64, 128, 256, 512};


extern VOS_VOID IMSA_CallConverterDtmf2Ims
(
    VOS_UINT32                          ulCallId,
    VOS_CHAR                            cKey,
    VOS_UINT32                          ulDuration,
    IMSA_IMS_INPUT_EVENT_STRU          *pstInputEvent
);
extern TAF_CS_CAUSE_ENUM_UINT32 IMSA_CallIsAllowDtmf
(
    const VOS_UINT8                    *pucCallIds,
    VOS_UINT32                          ulNumOfCalls,
    VOS_UINT8                           ucCallId
);

/*****************************************************************************
  3 Function Declaration
*****************************************************************************/

/*lint -e961*/
/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : IMSA_CallTypeAvailabilityCheck
 Description    : �������Ϳ����Լ��
 Input          :
 Output         :
 Return Value   :

 History        :
      1.wangchen 00209181   2014-12-16  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallTypeAvailabilityCheck(MN_CALL_TYPE_ENUM_UINT8 enCallType)
{


    IMSA_INFO_LOG("IMSA_CallTypeAvailabilityCheck is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallTypeAvailabilityCheck_ENUM, LNAS_ENTRY);

    if ((MN_CALL_TYPE_EMERGENCY != enCallType) &&
        (MN_CALL_TYPE_VOICE != enCallType) &&
        (MN_CALL_TYPE_VIDEO != enCallType))
    {
        return VOS_FALSE;
    }
    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallNormalCallAvailabilityCheck
 Description    : ���п����Լ��
 Input          : ulIsEmcCall   ���κ����Ƿ��ǽ�������
 Output         : penEmcType    ����������
 Return Value   : ���п����Լ����
                  IMSA_CALL_AVAILABILITY_CHECK_RESULT_CONTINUE  �������̿��Լ���ִ��
                  IMSA_CALL_AVAILABILITY_CHECK_RESULT_CACHED    ����������ʱ���棬����������׼���ú��ټ���
                  IMSA_CALL_AVAILABILITY_CHECK_RESULT_REJECT    ��������ܾ�

 History        :
      1.wangchen 00209181   2015-11-28  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallNormalCallAvailabilityCheck
(
    MN_CALL_TYPE_ENUM_UINT8 enCallType
)
{
    VOS_UINT32 ulServiceRet = 0;
    VOS_UINT32 ulResult = IMSA_CALL_AVAILABILITY_CHECK_RESULT_REJECT;
    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_ENUM_UINT16 enCallFailReason = IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NONE;
    #endif

    IMSA_INFO_LOG("IMSA_CallNormalCallAvailabilityCheck is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallAvailabilityCheck_ENUM, LNAS_ENTRY);

    ulServiceRet = IMSA_StartImsNormalService(enCallType);

    /* �����ͨ�������������㣬��ظ����оܾ� */
    if (IMSA_START_SRV_RESULT_CAN_MAKE_CALL != ulServiceRet)
    {
        return IMSA_CALL_AVAILABILITY_CHECK_RESULT_REJECT;
    }

    /* ���SSAC���������㣬��ظ��ܾ� */
    if (VOS_TRUE != IMSA_ProcSsacInfo(enCallType))
    {
        #if (FEATURE_ON == FEATURE_PTM)
        if (MN_CALL_TYPE_VIDEO == enCallType)
        {
            enCallFailReason = IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_SSAC_BAR_FOR_VIDEO_CALL;
        }
        else if (MN_CALL_TYPE_VOICE == enCallType)
        {
            enCallFailReason = IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_SSAC_BAR_FOR_VOICE_CALL;
        }
        else
        {
        }
        IMSA_CallFailErrRecord( enCallType,
                                enCallFailReason,
                                IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NONE,
                                VOS_NULL_PTR,
                                VOS_FALSE);
        #endif
        return IMSA_CALL_AVAILABILITY_CHECK_RESULT_REJECT;
    }

    /* �ж���Դ�����Ƿ����� */
    switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_MO_NORMAL_CALL))
    {
    case IMSA_RESOURCE_STATUS_ACTIVE:

        ulResult = IMSA_CALL_AVAILABILITY_CHECK_RESULT_CONTINUE;
        break;
    case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

        ulResult = IMSA_CALL_AVAILABILITY_CHECK_RESULT_APPLY_NOTNEED_WAIT;
        break;
    case IMSA_RESOURCE_STATUS_NULL:

        ulResult = IMSA_CALL_AVAILABILITY_CHECK_RESULT_NO_RF;
        break;
    default:
        ulResult = IMSA_CALL_AVAILABILITY_CHECK_RESULT_REJECT;
        break;
    }

    return ulResult;
}
/*****************************************************************************
 Function Name  : IMSA_CallEmcCallAvailabilityCheck
 Description    : ���п����Լ��
 Input          : ulIsEmcCall   ���κ����Ƿ��ǽ�������
 Output         : penEmcType    ����������
 Return Value   : ���п����Լ����
                  IMSA_CALL_AVAILABILITY_CHECK_RESULT_CONTINUE  �������̿��Լ���ִ��
                  IMSA_CALL_AVAILABILITY_CHECK_RESULT_CACHED    ����������ʱ���棬����������׼���ú��ټ���
                  IMSA_CALL_AVAILABILITY_CHECK_RESULT_REJECT    ��������ܾ�

 History        :
      1.wangchen 00209181   2015-11-28  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallEmcCallAvailabilityCheck
(
    IMSA_EMC_CALL_TYPE_ENUM_UINT32 *penEmcType
)
{
    VOS_UINT32 ulServiceRet = 0;
    VOS_UINT32 ulResult = IMSA_CALL_AVAILABILITY_CHECK_RESULT_REJECT;

    IMSA_INFO_LOG("IMSA_CallEmcCallAvailabilityCheck is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallAvailabilityCheck_ENUM, LNAS_ENTRY);

    ulServiceRet = IMSA_StartImsEmergServiceAbilityCheck(penEmcType);

    /* �жϻ�ȡ����IMS����������Ƿ�߱���������߱����򷵻ز��ܴ������ */
    if (IMSA_START_SRV_RESULT_CANNOT_MAKE_CALL == ulServiceRet)
    {
        IMSA_INFO_LOG("IMSA_CallEmcCallAvailabilityCheck:EMC service condition not satisfied!");
        TLPS_PRINT2LAYER_INFO(IMSA_StartImsEmergService_ENUM, 1);
        return IMSA_CALL_AVAILABILITY_CHECK_RESULT_REJECT;
    }
    else if (IMSA_START_SRV_RESULT_CAN_MAKE_CALL == ulServiceRet)
    {
        /* �ж���Դ�����Ƿ����� */
        switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL))
        {
        case IMSA_RESOURCE_STATUS_ACTIVE:

            ulResult = IMSA_CALL_AVAILABILITY_CHECK_RESULT_CONTINUE;
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

            ulResult = IMSA_CALL_AVAILABILITY_CHECK_RESULT_APPLY_NOTNEED_WAIT;
            break;
        case IMSA_RESOURCE_STATUS_NULL:

            ulResult = IMSA_CALL_AVAILABILITY_CHECK_RESULT_NO_RF;
            break;
        default:
            ulResult = IMSA_CALL_AVAILABILITY_CHECK_RESULT_REJECT;
            break;
        }
    }
    else  //IMSA_START_SRV_RESULT_BUFFER_CALL_WAIT_INDICATION
    {
        switch (IMSA_DsdsGetResourceStatus(RRM_PS_TASK_TYPE_LTE_IMS_EMERGENCY_CALL))
        {
        case IMSA_RESOURCE_STATUS_ACTIVE:

            ulResult = IMSA_CALL_AVAILABILITY_CHECK_RESULT_CACHED;
            break;

        case IMSA_RESOURCE_STATUS_APPLY_NOT_NEED_WAIT_CNF:

            ulResult = IMSA_CALL_AVAILABILITY_CHECK_RESULT_CACHED_NOTNEED_WAIT;
            break;

        case IMSA_RESOURCE_STATUS_NULL:

            ulResult = IMSA_CALL_AVAILABILITY_CHECK_RESULT_NO_RF;
            break;

        default:
            ulResult = IMSA_CALL_AVAILABILITY_CHECK_RESULT_REJECT;
            break;
        }
    }
    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_CallCheckIsAllowNewOrig
 Description    : �Ƿ��������µ�Orig
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : �����

 History        :
      1.xiongxianghui 00253310      2014-04-15  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallCheckIsAllowNewOrig(VOS_VOID)
{
    VOS_UINT32    i = 0;
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallCheckIsAllowNewOrig is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallCheckIsAllowNewOrig_ENUM, LNAS_ENTRY);

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if (IMSA_OP_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed)
        {
            if ((IMSA_CALL_STATUS_IDLE != pstCallCtx->astCallEntity[i].enStatus) &&
                (IMSA_CALL_STATUS_HELD != pstCallCtx->astCallEntity[i].enStatus))
            {
                IMSA_INFO_LOG("IMSA_CallCheckIsAllowNewOrig: not allow orig!");
                TLPS_PRINT2LAYER_INFO(IMSA_CallCheckIsAllowNewOrig_ENUM, 1);
                return VOS_FALSE;
            }
        }
    }

    return VOS_TRUE;
}


/*****************************************************************************
 Function Name  : IMSA_CallCtxInit
 Description    : ����ģ���ʼ��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : ����ģ���ʼ�������Ŀǰ���ǳɹ�

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallCtxInit(VOS_VOID)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallCtxInit is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallCtxInit_ENUM, LNAS_ENTRY);

    /* Initialize memory */
    IMSA_MEM_SET_S( pstCallCtx,
                    sizeof(IMSA_CALL_MANAGER_STRU),
                    0,
                    sizeof(IMSA_CALL_MANAGER_STRU));

    /* Initialize timer */
    pstCallCtx->stProctectTimer.usName = TI_IMSA_CALL_PROTECT;
    pstCallCtx->stProctectTimer.ulTimerLen = IMSA_CALL_TIMER_LEN_PROTECT;
    pstCallCtx->stProctectTimer.ucMode = VOS_RELTIMER_NOLOOP;

    pstCallCtx->stResReadyTimer.usName = TI_IMSA_CALL_RES_READY;
    pstCallCtx->stResReadyTimer.ulTimerLen = IMSA_CALL_TIMER_LEN_WAIT_RES;
    pstCallCtx->stResReadyTimer.ucMode = VOS_RELTIMER_NOLOOP;

    pstCallCtx->stDtmfCtx.stDtmfDurationTimer.usName = TI_IMSA_CALL_DTMF_DURATION;
    pstCallCtx->stDtmfCtx.stDtmfDurationTimer.ucMode = VOS_RELTIMER_NOLOOP;

    pstCallCtx->stDtmfCtx.stDtmfProtectTimer.usName = TI_IMSA_CALL_DTMF_PROTECT;
    pstCallCtx->stDtmfCtx.stDtmfProtectTimer.ulTimerLen = IMSA_CALL_TIMER_LEN_PROTECT;
    pstCallCtx->stDtmfCtx.stDtmfProtectTimer.ucMode = VOS_RELTIMER_NOLOOP;

    /* ��ʼ��BACK-OFF��ʱ�� */
    pstCallCtx->stBackOffTxTimer.phTimer     = VOS_NULL_PTR;
    pstCallCtx->stBackOffTxTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstCallCtx->stBackOffTxTimer.usName      = TI_IMSA_BACK_OFF_TX;
    pstCallCtx->stBackOffTxTimer.ulTimerLen  = 0;

    pstCallCtx->stBackOffTyTimer.phTimer     = VOS_NULL_PTR;
    pstCallCtx->stBackOffTyTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstCallCtx->stBackOffTyTimer.usName      = TI_IMSA_BACK_OFF_TY;
    pstCallCtx->stBackOffTyTimer.ulTimerLen  = 0;

    /* ��ʼ���ز���ض�ʱ�� */
    pstCallCtx->stRedialMaxTimer.phTimer     = VOS_NULL_PTR;
    pstCallCtx->stRedialMaxTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstCallCtx->stRedialMaxTimer.usName      = TI_IMSA_CALL_REDIAL_MAX_TIME;
    pstCallCtx->stRedialMaxTimer.ulTimerLen  = 0;

    pstCallCtx->stRedialIntervelTimer.phTimer     = VOS_NULL_PTR;
    pstCallCtx->stRedialIntervelTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstCallCtx->stRedialIntervelTimer.usName      = TI_IMSA_CALL_REDIAL_INTERVEL;
    pstCallCtx->stRedialIntervelTimer.ulTimerLen  = 0;

    /* ��ʼ��Tcall��ʱ��, SilentRedial����,CMCC���� */
    pstCallCtx->stNormalTcallTimer.phTimer     = VOS_NULL_PTR;
    pstCallCtx->stNormalTcallTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstCallCtx->stNormalTcallTimer.usName      = TI_IMSA_CALL_NORMAL_TCALL;
    pstCallCtx->stNormalTcallTimer.ulTimerLen  = 0;
    pstCallCtx->stEmcTcallTimer.phTimer     = VOS_NULL_PTR;
    pstCallCtx->stEmcTcallTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstCallCtx->stEmcTcallTimer.usName      = TI_IMSA_CALL_EMC_TCALL;
    pstCallCtx->stEmcTcallTimer.ulTimerLen  = 0;

    pstCallCtx->stNormMediaLostRelCallTimer.phTimer     = VOS_NULL_PTR;
    pstCallCtx->stNormMediaLostRelCallTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstCallCtx->stNormMediaLostRelCallTimer.usName      = TI_IMSA_CALL_NORM_MEDIA_LOST_REL_CALL;
    pstCallCtx->stNormMediaLostRelCallTimer.ulTimerLen  = IMSA_CALL_TIMER_LEN_BEAR_LOST_REL_CALL;

    pstCallCtx->stEmcMediaLostRelCallTimer.phTimer     = VOS_NULL_PTR;
    pstCallCtx->stEmcMediaLostRelCallTimer.ucMode      = VOS_RELTIMER_NOLOOP;
    pstCallCtx->stEmcMediaLostRelCallTimer.usName      = TI_IMSA_CALL_EMC_MEDIA_LOST_REL_CALL;
    pstCallCtx->stEmcMediaLostRelCallTimer.ulTimerLen  = IMSA_CALL_TIMER_LEN_BEAR_LOST_REL_CALL;

    /* DTMF����buffer��ʼ�� */
    IMSA_CallDtmfInfoInit();

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallCtxDeinit
 Description    : ����ģ�鷴��ʼ��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : ����ģ�鷴��ʼ�������Ŀǰ���ǳɹ�

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallCtxDeinit(VOS_VOID)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();
    IMSA_CALL_ENTITY_STRU              *pstCallEntity   = VOS_NULL_PTR;
    VOS_UINT16                          usRedialCallIndex = IMSA_NULL;
    VOS_UINT32                          i = 0;

    IMSA_INFO_LOG("IMSA_CallCtxDeinit is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallCtxDeinit_ENUM, LNAS_ENTRY);

    /* ���DTMF��Ϣ */
    IMSA_CallClearDtmfInfo(TAF_CS_CAUSE_POWER_OFF);

    if (IMSA_OP_TRUE == pstCallCtx->stSpmMsg.bitOpSpmMsg)
    {
        switch (pstCallCtx->stSpmMsg.ulSpmMsgId)
        {
        case ID_SPM_IMSA_CALL_ORIG_REQ:
            (VOS_VOID)IMSA_CallSendSpmOrigCnfMsg(pstCallCtx->stSpmMsg.usClientId,
                                                 pstCallCtx->stSpmMsg.ulOpId,
                                                 pstCallCtx->stSpmMsg.ulCallId,
                                                 TAF_CS_CAUSE_IMSA_SERVICE_NOT_AVAILABLE);
            break;
        case ID_SPM_IMSA_CALL_SUPS_CMD_REQ:
            (VOS_VOID)IMSA_CallSendSpmSupsResultMsg(pstCallCtx->stSpmMsg.usClientId,
                                              pstCallCtx->stSpmMsg.ulOpId,
                                              pstCallCtx->stSpmMsg.ulCallId,
                                              MN_CALL_SS_RES_FAIL);
            break;
        default:
            IMSA_ERR_LOG1("IMSA_CallCtxDeinit: invalid call request", pstCallCtx->stSpmMsg.ulSpmMsgId);
            TLPS_PRINT2LAYER_ERROR1(IMSA_CallCtxDeinit_ENUM, IMSA_INVALID_CALL_REQUEST, pstCallCtx->stSpmMsg.ulSpmMsgId);
            break;
        }

        IMSA_CallSpmMsgClear();
    }

    /* Stop timer if running */
    if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stProctectTimer))
    {
        IMSA_StopTimer(&pstCallCtx->stProctectTimer);
    }

    if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stResReadyTimer))
    {
        IMSA_StopTimer(&pstCallCtx->stResReadyTimer);
    }

    if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stDtmfCtx.stDtmfDurationTimer))
    {
        IMSA_StopTimer(&pstCallCtx->stDtmfCtx.stDtmfDurationTimer);
    }

    if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stDtmfCtx.stDtmfProtectTimer))
    {
        IMSA_StopTimer(&pstCallCtx->stDtmfCtx.stDtmfProtectTimer);
    }

    if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stBackOffTxTimer))
    {
        IMSA_StopTimer(&pstCallCtx->stBackOffTxTimer);
    }

    if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stBackOffTyTimer))
    {
        IMSA_StopTimer(&pstCallCtx->stBackOffTyTimer);
    }

    if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stRedialMaxTimer))
    {
        IMSA_StopTimer(&pstCallCtx->stRedialMaxTimer);
    }

    if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stRedialIntervelTimer))
    {
        /* �ز������йػ�����Ҫ��SPM�ظ���Ϣ */
        usRedialCallIndex   = pstCallCtx->stRedialMaxTimer.usPara;
        if (usRedialCallIndex < IMSA_CALL_MAX_NUM)
        {
            pstCallEntity = &pstCallCtx->astCallEntity[usRedialCallIndex];
            IMSA_CallInterruptRedial(pstCallEntity);
        }
        IMSA_StopTimer(&pstCallCtx->stRedialIntervelTimer);
    }

    /* �ػ�ʱ�������CALL���ڣ���Ҫ֪ͨSPM release�¼� */
    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if (VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed)
        {
            IMSA_CallReleaseCallCommonProc(&(pstCallCtx->astCallEntity[i]), TAF_CS_CAUSE_IMSA_SERVICE_NOT_AVAILABLE);
        }
    }

    /* Stop active call */
    if (IMSA_CallEntityGetUsedCount() > 0)
    {
        (VOS_VOID)IMSA_CallImsCmdRelAll();
    }
    if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stNormalTcallTimer))
    {
        IMSA_StopTimer(&pstCallCtx->stNormalTcallTimer);
    }

    if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stEmcTcallTimer))
    {
        IMSA_StopTimer(&pstCallCtx->stEmcTcallTimer);
    }

    (VOS_VOID)IMSA_CallCtxInit();

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallEntityAlloc
 Description    : �������ʵ��
 Input          : VOS_VOID
 Output         : None
 Return Value   : ���䵽�ĺ���ʵ���ָ�룻���ʧ�ܣ�����VOS_NULL_PTR

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-12-20  Modify:Redial
      3.wangchen 00209181   2015-03-16 Modify:volte
*****************************************************************************/
IMSA_CALL_ENTITY_STRU* IMSA_CallEntityAlloc( VOS_VOID )
{
    VOS_UINT16                          i = 0;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallEntityAlloc is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallEntityAlloc_ENUM, LNAS_ENTRY);

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if (VOS_FALSE == pstCallCtx->astCallEntity[i].bitOpIsUsed)
        {
            IMSA_MEM_SET_S( &(pstCallCtx->astCallEntity[i]),
                            sizeof(IMSA_CALL_ENTITY_STRU),
                            0,
                            sizeof(IMSA_CALL_ENTITY_STRU));

            pstCallCtx->astCallEntity[i].bitOpIsUsed = IMSA_OP_TRUE;

            pstCallCtx->astCallEntity[i].usClientId = MN_CLIENT_ALL;
            pstCallCtx->astCallEntity[i].ulOpId = 0;
            pstCallCtx->astCallEntity[i].ucSpmcallId = (VOS_UINT8)(i + 1);
            pstCallCtx->astCallEntity[i].enStatus = IMSA_CALL_STATUS_DIALING;

            pstCallCtx->astCallEntity[i].ucCallEntityIndex = (VOS_UINT8)i;

            return &(pstCallCtx->astCallEntity[i]);
        }
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 Function Name  : IMSA_CallEntityFree
 Description    : �ͷź���ʵ��
 Input          : pstCallEntity   ��Ҫ�ͷŵĺ���ʵ��ָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-12-24  Modify
*****************************************************************************/
VOS_VOID IMSA_CallEntityFree(IMSA_CALL_ENTITY_STRU *pstCallEntity)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx  = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallEntityFree is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallEntityFree_ENUM, LNAS_ENTRY);

    if (pstCallEntity)
    {
        /**
         * TODO: ��Ҫ������Դ�ȴ���ʱ���Լ�������ʱ����������Ϣ��
         * �����Щ��ʱ������Ϣ�Ǹպ��ǻ��ڴ˺��У�
         * ����Ҫ�ͷ���Щ��Դ
         *
         * �������Ӧ�÷���EntityFree���
         *
         * �ȴ���Դ��ʱ���п����Ƕ�Ӧ��������У�
         * Ŀǰû�б���������ӳ���ϵ
         */

        /* ���Ҫ�ͷŵ�CALL���ڽ�����ԴԤ��������Ҫֹͣ��ԴԤ����ʱ�� */
        if ((VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stResReadyTimer))
            && (pstCallEntity == &pstCallCtx->astCallEntity[pstCallCtx->stResReadyTimer.usPara]))
        {
            IMSA_StopTimer(&pstCallCtx->stResReadyTimer);
        }

        IMSA_MEM_SET_S( pstCallEntity,
                        sizeof(IMSA_CALL_ENTITY_STRU),
                        0,
                        sizeof(IMSA_CALL_ENTITY_STRU));

        pstCallEntity->bitOpIsUsed     = VOS_FALSE;
        /* NOTE: other clear procedure, nothing now*/
    }
}

/*****************************************************************************
 Function Name  : IMSA_CallClearTransToCsInfo
 Description    : �������SRVCCת�Ƶ�CS���call��ʾ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-10-14  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallClearTransToCsInfo(VOS_VOID)
{
    VOS_UINT32 i = 0;
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if (VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed)
        {
            pstCallCtx->astCallEntity[i].bitOpTransToCs = VOS_FALSE;
        }
    }

}

/*****************************************************************************
 Function Name  : IMSA_CallEntityGetUsedByImsCallId
 Description    : ���ݺ���Id��������ʹ�õĺ���ʵ��
 Input          : ulCallId   ����Id
 Output         : VOS_VOID
 Return Value   : ���ҵ��ĺ���ʵ��ָ�룻���ʧ�ܣ��򷵻�VOS_NULL_PTR

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
IMSA_CALL_ENTITY_STRU* IMSA_CallEntityGetUsedByImsCallId(VOS_UINT32 ulCallId)
{
    VOS_UINT32 i = 0;
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallEntityGetUsedByImsCallId is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallEntityGetUsedByImsCallId_ENUM, LNAS_ENTRY);

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
            ((VOS_UINT8)ulCallId == pstCallCtx->astCallEntity[i].ucImscallId))
        {
            return &(pstCallCtx->astCallEntity[i]);
        }
    }

    return VOS_NULL_PTR;
}
/*****************************************************************************
 Function Name  : IMSA_EconfCalledGetUsedByCalledNum
 Description    : ���ݱ��к��룬���������
 Input          : ulCallId   ����Id
 Output         : VOS_VOID
 Return Value   : ���ҵ��ĺ���ʵ��ָ�룻���ʧ�ܣ��򷵻�VOS_NULL_PTR

 History        :
      1.wangchen 00209181   2014-12-12  Draft Enact
*****************************************************************************/
IMSA_CALL_ECONF_SUMMARY_STRU* IMSA_EconfCalledGetUsedByCalledNum
(
    IMSA_CALL_ENTITY_STRU              *pstCallEntity,
    VOS_CHAR                                 *pCalledNum
)
{
    VOS_UINT32 i = 0;

    IMSA_INFO_LOG("IMSA_EconfCalledGetUsedByCalledNum is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_EconfCalledGetUsedByCalledNum_ENUM, LNAS_ENTRY);

    for (i = 0; i < IMSA_IMS_ECONF_CALLED_MAX_NUM; i++)
    {
        if ((IMSA_OP_TRUE == pstCallEntity->stEconfCalllist[i].bitOpIsUsed) &&
            (0 == IMSA_MEM_CMP(pCalledNum,pstCallEntity->stEconfCalllist[i].stCalledNumber.aucNumber,IMSA_IMS_NUMBER_STRING_SZ)))
        {
            return &(pstCallEntity->stEconfCalllist[i]);
        }
    }

    /* ���IMS�ϱ�������߲����б��У�����Ҫ�����к�����ӵ�����ʵ����,��ǿ�Ͷ෽ͨ������ͨͨ���ϲ�ʱ��IMS��౨һ���û����� */
    for (i = 0; i < IMSA_IMS_ECONF_CALLED_MAX_NUM; i++)
    {
        if (VOS_FALSE == pstCallEntity->stEconfCalllist[i].bitOpIsUsed)
        {
            pstCallEntity->stEconfCalllist[i].bitOpIsUsed = IMSA_OP_TRUE;

            return &(pstCallEntity->stEconfCalllist[i]);
        }
    }

    return VOS_NULL_PTR;
}
/*****************************************************************************
 Function Name  : IMSA_CallEntityGetUsedByEconfFlag
 Description    : ������ǿ�෽ͨ���ĺ���ʵ��
 Input          : ulCallId   ����Id
 Output         : VOS_VOID
 Return Value   : ���ҵ��ĺ���ʵ��ָ�룻���ʧ�ܣ��򷵻�VOS_NULL_PTR

 History        :
      1.wangchen 00209181   2014-12-13  Draft Enact
*****************************************************************************/
IMSA_CALL_ENTITY_STRU* IMSA_CallEntityGetUsedByEconfFlag(VOS_VOID)
{
    VOS_UINT32 i = 0;
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallEntityGetUsedByEconfFlag is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallEntityGetUsedByEconfFlag_ENUM, LNAS_ENTRY);

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
            (VOS_TRUE == pstCallCtx->astCallEntity[i].ucIsEconfFlag))
        {
            return &(pstCallCtx->astCallEntity[i]);
        }
    }

    return VOS_NULL_PTR;
}

/*****************************************************************************
 Function Name  : IMSA_CallEntityGetUsedBySpmCallId
 Description    : ���ݺ���SpmId��������ʹ�õĺ���ʵ��
 Input          : ulCallId   ����Id
 Output         : VOS_VOID
 Return Value   : ���ҵ��ĺ���ʵ��ָ�룻���ʧ�ܣ��򷵻�VOS_NULL_PTR

 History        :
      1.wangchen 00209181   2014-12-01  Draft Enact
*****************************************************************************/
IMSA_CALL_ENTITY_STRU* IMSA_CallEntityGetUsedBySpmCallId(VOS_UINT32 ulCallId)
{
    VOS_UINT32 i = 0;
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallEntityGetUsedBySpmCallId is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallEntityGetUsedBySpmCallId_ENUM, LNAS_ENTRY);

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
            ((VOS_UINT8)ulCallId == pstCallCtx->astCallEntity[i].ucSpmcallId))
        {
            return &(pstCallCtx->astCallEntity[i]);
        }
    }

    return VOS_NULL_PTR;
}


/*****************************************************************************
 Function Name  : IMSA_CallUpdateDiscCallDir
 Description    : ����CALLʵ��ĹҶϷ�����Ϣ
 Input          : ulCallId   ����Id
                  ucIsUser   �Ƿ����û��Ҷ�
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-09-29  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallUpdateDiscCallDir
(
    VOS_UINT32                          ulCallId,
    VOS_UINT8                           ucIsUser
)
{
    IMSA_CALL_ENTITY_STRU              *pstCallEntity = VOS_NULL_PTR;

    if ( (ulCallId == 0) || ( ulCallId > IMSA_CALL_MAX_NUM ) )
    {
        IMSA_ERR_LOG("IMSA_CallUpdateDiscCallDir:call id error!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallUpdateDiscCallDir_ENUM, IMSA_CALL_ID_ERROR);
        return;
    }

    pstCallEntity = IMSA_CallEntityGetUsedBySpmCallId(ulCallId);

    if (VOS_NULL_PTR == pstCallEntity)
    {
        IMSA_ERR_LOG("IMSA_CallUpdateDiscCallDir:call not exist!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallUpdateDiscCallDir_ENUM, IMSA_CALL_NOT_EXIST);
        return;
    }

    if (VOS_TRUE == pstCallEntity->stDiscDir.ucDiscCallFlag)
    {
        return;
    }

    pstCallEntity->stDiscDir.ucIsUser       = ucIsUser;
    pstCallEntity->stDiscDir.ucDiscCallFlag = VOS_TRUE;

    return;
}

/*****************************************************************************
 Function Name  : IMSA_CallGetCallsByState
 Description    : ��ȡĳ״̬��CALL
 Input          : enStatus-----------------����״̬
 Output         : pulNumOfCalls------------���и���
                  pulCallIds---------------����ID�����׵�ַ
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-09-29  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallGetCallsByState
(
    IMSA_CALL_STATUS_ENUM_UINT8         enStatus,
    VOS_UINT32                         *pulNumOfCalls,
    VOS_UINT32                         *pulCallIds
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx  = IMSA_CallCtxGet();
    VOS_UINT32                          i           = IMSA_NULL;

    *pulNumOfCalls = 0;

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
            (enStatus == pstCallCtx->astCallEntity[i].enStatus))
        {
            pulCallIds[*pulNumOfCalls] = (VOS_UINT32)pstCallCtx->astCallEntity[i].ucSpmcallId;
            (*pulNumOfCalls)++;
        }
    }
}

/*****************************************************************************
 Function Name  : IMSA_CallEntityGetUsedCount
 Description    : ��ȡ��ǰ����ʹ�õĺ���ʵ�����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : ����ʹ�õĺ���ʵ�����

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallEntityGetUsedCount(VOS_VOID)
{
    VOS_UINT32 i = 0;
    VOS_UINT32 ulCount = 0;
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallEntityGetUsedCount is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallEntityGetUsedCount_ENUM, LNAS_ENTRY);

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if (VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed)
        {
            ulCount++;
        }
    }

    return ulCount;
}

/*****************************************************************************
 Function Name  : IMSA_CallSpmOrigReqMsgSave
 Description    : �������ڴ����SPM��������
 Input          : pstAppMsg   SPM�·��ĺ�������
 Output         : VOS_VOID
 Return Value   : ���������Ƿ񱣴�ɹ�

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.wangchen 00209181  2013-10-12  Modify
 Note           :
     1. ������ƻ������ټ򻯣�ֱ�ӱ���MN_CALL_APP_REQ_MSG_STRU
*****************************************************************************/
VOS_VOID IMSA_CallSpmOrigReqMsgSave(const SPM_IMSA_CALL_ORIG_REQ_STRU *pstAppMsg)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallSpmOrigReqMsgSave is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSpmOrigReqMsgSave_ENUM, LNAS_ENTRY);

    /* ���֮ǰ�Ѿ��б��������򷵻�ʧ�� */
    if (IMSA_OP_TRUE == pstCallCtx->stSpmMsg.bitOpSpmMsg)
    {
        IMSA_INFO_LOG("IMSA_CallSpmOrigReqMsgSave has existed");
        TLPS_PRINT2LAYER_INFO(IMSA_CallSpmOrigReqMsgSave_ENUM, IMSA_EXISTED);
    }

    /* ���ñ���λ */
    pstCallCtx->stSpmMsg.bitOpSpmMsg = IMSA_OP_TRUE;

    /* ���湫������ */
    pstCallCtx->stSpmMsg.ulSpmMsgId = pstAppMsg->ulMsgId;
    pstCallCtx->stSpmMsg.usClientId = pstAppMsg->usClientId;
    pstCallCtx->stSpmMsg.ulOpId     = pstAppMsg->ucOpId;
    pstCallCtx->stSpmMsg.ulCallId   = IMSA_CALL_INVALID_ID;

    IMSA_MEM_CPY_S( &(pstCallCtx->stSpmMsg.stParam.stOrigParam),
                    sizeof(MN_CALL_ORIG_PARAM_STRU),
                    &pstAppMsg->stOrig,
                    sizeof(MN_CALL_ORIG_PARAM_STRU));
}
/*****************************************************************************
 Function Name  : IMSA_CallSpmEconfDialReqMsgSave
 Description    : �������ڴ����SPM��������
 Input          : pstAppMsg   SPM�·��ĺ�������
 Output         : VOS_VOID
 Return Value   : ���������Ƿ񱣴�ɹ�

 History        :
      1.wangchen 00209181   2014-12-17  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallSpmEconfDialReqMsgSave(const SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU *pstAppMsg)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallSpmOrigReqMsgSave is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSpmEconfDialReqMsgSave_ENUM, LNAS_ENTRY);

    /* ���֮ǰ�Ѿ��б��������򷵻�ʧ�� */
    if (IMSA_OP_TRUE == pstCallCtx->stSpmMsg.bitOpSpmMsg)
    {
        IMSA_INFO_LOG("IMSA_CallSpmOrigReqMsgSave has existed");
        TLPS_PRINT2LAYER_INFO(IMSA_CallSpmEconfDialReqMsgSave_ENUM, IMSA_EXISTED);
    }

    /* ���ñ���λ */
    pstCallCtx->stSpmMsg.bitOpSpmMsg = IMSA_OP_TRUE;

    /* ���湫������ */
    pstCallCtx->stSpmMsg.ulSpmMsgId = pstAppMsg->ulMsgId;
    pstCallCtx->stSpmMsg.usClientId = pstAppMsg->usClientId;
    pstCallCtx->stSpmMsg.ulOpId     = pstAppMsg->ucOpId;
    pstCallCtx->stSpmMsg.ulCallId   = IMSA_CALL_INVALID_ID;

    IMSA_MEM_CPY_S( &(pstCallCtx->stSpmMsg.stParam.stEconfDialParam),
                    sizeof(TAF_CALL_ECONF_DIAL_REQ_STRU),
                    &pstAppMsg->stDialReq,
                    sizeof(TAF_CALL_ECONF_DIAL_REQ_STRU));
}
/*****************************************************************************
 Function Name  : IMSA_CallSpmEconfAddUserMsgSave
 Description    : �������ڴ����SPM��������
 Input          : pstAppMsg   SPM�·��ĺ�������
 Output         : VOS_VOID
 Return Value   : ���������Ƿ񱣴�ɹ�

 History        :
      1.wangchen 00209181   2014-12-17  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallSpmEconfAddUserMsgSave(const SPM_IMSA_CALL_ECONF_ADD_USERS_REQ_STRU *pstAppMsg)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallSpmEconfAddUserMsgSave is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSpmEconfAddUserMsgSave_ENUM, LNAS_ENTRY);

    /* ���֮ǰ�Ѿ��б��������򷵻�ʧ�� */
    if (IMSA_OP_TRUE == pstCallCtx->stSpmMsg.bitOpSpmMsg)
    {
        IMSA_INFO_LOG("IMSA_CallSpmEconfAddUserMsgSave has existed");
        TLPS_PRINT2LAYER_INFO(IMSA_CallSpmEconfAddUserMsgSave_ENUM, IMSA_EXISTED);
    }

    /* ���ñ���λ */
    pstCallCtx->stSpmMsg.bitOpSpmMsg = IMSA_OP_TRUE;

    /* ���湫������ */
    pstCallCtx->stSpmMsg.ulSpmMsgId = pstAppMsg->ulMsgId;
    pstCallCtx->stSpmMsg.usClientId = pstAppMsg->usClientId;
    pstCallCtx->stSpmMsg.ulOpId     = pstAppMsg->ucOpId;
    pstCallCtx->stSpmMsg.ulCallId   = IMSA_CALL_INVALID_ID;

    IMSA_MEM_CPY_S( &(pstCallCtx->stSpmMsg.stParam.stEconfAddParam),
                    sizeof(TAF_CALL_ECONF_CALL_LIST_STRU),
                    &pstAppMsg->stEconfCalllist,
                    sizeof(TAF_CALL_ECONF_CALL_LIST_STRU));
}

/*****************************************************************************
 Function Name  : IMSA_CallSpmSupsCmdReqMsgSave
 Description    : �������ڴ����SPM��������
 Input          : pstAppMsg   SPM�·��ĺ�������
 Output         : VOS_VOID
 Return Value   : ���������Ƿ񱣴�ɹ�

 History        :
      1.lihong 00150010      2013-12-25  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CallSpmSupsCmdReqMsgSave
(
    const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU  *pstAppMsg
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallSpmSupsCmdReqMsgSave is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSpmSupsCmdReqMsgSave_ENUM, LNAS_ENTRY);

    /* ���֮ǰ�Ѿ��б��������򷵻�ʧ�� */
    if (IMSA_OP_TRUE == pstCallCtx->stSpmMsg.bitOpSpmMsg)
    {
        IMSA_INFO_LOG("IMSA_CallSpmSupsCmdReqMsgSave has existed");
        TLPS_PRINT2LAYER_INFO(IMSA_CallSpmSupsCmdReqMsgSave_ENUM, IMSA_EXISTED);
    }

    /* ���ñ���λ */
    pstCallCtx->stSpmMsg.bitOpSpmMsg = IMSA_OP_TRUE;

    /* ���湫������ */
    pstCallCtx->stSpmMsg.ulSpmMsgId = pstAppMsg->ulMsgId;
    pstCallCtx->stSpmMsg.usClientId = pstAppMsg->usClientId;
    pstCallCtx->stSpmMsg.ulOpId     = pstAppMsg->ucOpId;
    pstCallCtx->stSpmMsg.ulCallId   = pstAppMsg->stCallMgmtCmd.callId;

    IMSA_MEM_CPY_S( &(pstCallCtx->stSpmMsg.stParam.stSupsParam),
                    sizeof(MN_CALL_SUPS_PARAM_STRU),
                    &pstAppMsg->stCallMgmtCmd,
                    sizeof(MN_CALL_SUPS_PARAM_STRU));
}

/*****************************************************************************
 Function Name  : IMSA_CallSpmModifyReqMsgSave
 Description    : �������ڴ����SPM��������
 Input          : pstAppMsg   SPM�·��ĺ�������
 Output         : VOS_VOID
 Return Value   : ���������Ƿ񱣴�ɹ�

 History        :
      1.wangchen 00209181 2014-06-19  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CallSpmModifyMsgSave
(
    const SPM_IMSA_CALL_MODIFY_REQ_STRU  *pstAppMsg
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallSpmModifyMsgSave is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSpmModifyMsgSave_ENUM, LNAS_ENTRY);

    /* ���֮ǰ�Ѿ��б��������򷵻�ʧ�� */
    if (IMSA_OP_TRUE == pstCallCtx->stSpmMsg.bitOpSpmMsg)
    {
        IMSA_INFO_LOG("IMSA_CallSpmModifyMsgSave has existed");
        TLPS_PRINT2LAYER_INFO(IMSA_CallSpmModifyMsgSave_ENUM, IMSA_EXISTED);
    }

    /* ���ñ���λ */
    pstCallCtx->stSpmMsg.bitOpSpmMsg = IMSA_OP_TRUE;

    /* ���湫������ */
    pstCallCtx->stSpmMsg.ulSpmMsgId = pstAppMsg->ulMsgId;
    pstCallCtx->stSpmMsg.usClientId = pstAppMsg->usClientId;
    pstCallCtx->stSpmMsg.ulOpId     = pstAppMsg->ucOpId;
    pstCallCtx->stSpmMsg.ulCallId   = pstAppMsg->callId;

}
/*****************************************************************************
 Function Name  : IMSA_CallSpmModifyReqMsgSave
 Description    : �������ڴ����SPM��������
 Input          : pstAppMsg   SPM�·��ĺ�������
 Output         : VOS_VOID
 Return Value   : ���������Ƿ񱣴�ɹ�

 History        :
      1.wangchen 00209181 2014-06-19  Draft Enact

*****************************************************************************/
VOS_VOID IMSA_CallSpmAnswerRemoteModifyMsgSave
(
    const SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ_STRU *pstAppMsg
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallSpmAnswerRemoteModifyMsgSave is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSpmAnswerRemoteModifyMsgSave_ENUM, LNAS_ENTRY);

    /* ���֮ǰ�Ѿ��б��������򷵻�ʧ�� */
    if (IMSA_OP_TRUE == pstCallCtx->stSpmMsg.bitOpSpmMsg)
    {
        IMSA_INFO_LOG("IMSA_CallSpmAnswerRemoteModifyMsgSave has existed");
        TLPS_PRINT2LAYER_INFO(IMSA_CallSpmAnswerRemoteModifyMsgSave_ENUM, IMSA_EXISTED);
    }

    /* ���ñ���λ */
    pstCallCtx->stSpmMsg.bitOpSpmMsg = IMSA_OP_TRUE;

    /* ���湫������ */
    pstCallCtx->stSpmMsg.ulSpmMsgId = pstAppMsg->ulMsgId;
    pstCallCtx->stSpmMsg.usClientId = pstAppMsg->usClientId;
    pstCallCtx->stSpmMsg.ulOpId     = pstAppMsg->ucOpId;
    pstCallCtx->stSpmMsg.ulCallId   = pstAppMsg->callId;

}


/*****************************************************************************
 Function Name  : IMSA_CallSpmMsgClear
 Description    : ���֮ǰ�Ѿ������SPM����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallSpmMsgClear(VOS_VOID)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallSpmMsgClear is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSpmMsgClear_ENUM, LNAS_ENTRY);

    IMSA_MEM_SET_S( &pstCallCtx->stSpmMsg,
                    sizeof(IMSA_CALL_SPM_MSG_STRU),
                    0,
                    sizeof(IMSA_CALL_SPM_MSG_STRU));

    pstCallCtx->stSpmMsg.bitOpSpmMsg = IMSA_FALSE;
}

/*****************************************************************************
 Function Name  : IMSA_CallImsMsgSave
 Description    : ��������ִ�е�IMS���������Ŀǰֻ����opid������ִ�е���������
 Input          : pstCallEvt    ����ִ�е�IMS��Ϣ
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.wangchen 00209181  2013-10-12  Modify
*****************************************************************************/
VOS_UINT32 IMSA_CallImsMsgSave(const IMSA_IMS_INPUT_CALL_EVENT_STRU *pstCallEvt)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallImsMsgSave is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallImsMsgSave_ENUM, LNAS_ENTRY);

    /* ���֮ǰ�Ѿ��б��棬�򷵻�ʧ�� */
    if (IMSA_OP_TRUE == pstCallCtx->stImsMsg.bitOpImsMsg)
    {
        IMSA_INFO_LOG("IMSA_CallImsMsgSave has existed");
        TLPS_PRINT2LAYER_INFO(IMSA_CallImsMsgSave_ENUM, IMSA_EXISTED);
    }

    /* ������������ */
    pstCallCtx->stImsMsg.bitOpImsMsg = IMSA_OP_TRUE;
    pstCallCtx->stImsMsg.ulCsmId     = pstCallEvt->ulOpId;
    pstCallCtx->stImsMsg.ulCsmReason = pstCallEvt->enInputCallReason;

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallImsMsgFind
 Description    : ���D2 IMS���ص�opid�Ƿ��ǵ�ǰ���ڵȴ���Ӧ��opid
 Input          : ulOpId    D2 IMS���ص�opid
 Output         : VOS_VOID
 Return Value   : �������������򷵻�VOS_TRUE,�����򷵻�VOS_FALSE

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
 Note           :
     1. Ŀǰֻ����һ��CSM_Id��δ���������Ҫ�������ͨ�������ڲ����ݽṹ��֧��
        ���Ա�����CSM_Id
*****************************************************************************/
VOS_UINT32 IMSA_CallImsMsgFind(VOS_UINT32 ulOpId)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallImsMsgFind is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallImsMsgFind_ENUM, LNAS_ENTRY);

    if ((IMSA_OP_TRUE == pstCallCtx->stImsMsg.bitOpImsMsg) &&
        (ulOpId == pstCallCtx->stImsMsg.ulCsmId))
    {
        return IMSA_CALL_FIND_SUCC;
    }
    else if(((IMSA_CALL_DTMF_WAIT_START_CNF == pstCallCtx->stDtmfCtx.enDtmfState)
                || (IMSA_CALL_DTMF_WAIT_STOP_CNF == pstCallCtx->stDtmfCtx.enDtmfState)
                || (IMSA_CALL_DTMF_WAIT_AUTO_STOP_CNF == pstCallCtx->stDtmfCtx.enDtmfState))
         && (ulOpId == pstCallCtx->stDtmfCtx.stCurrentDtmf.ulImsOpid))
    {
        return IMSA_CALL_FIND_SUCC_DTMF;
    }
    else
    {
        return IMSA_CALL_FIND_FAIL;
    }
}

/*****************************************************************************
 Function Name  : IMSA_CallImsMsgClear
 Description    : ����Ѿ������IMS����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallImsMsgClear(VOS_VOID)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallImsMsgClear is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallImsMsgClear_ENUM, LNAS_ENTRY);

    pstCallCtx->stImsMsg.bitOpImsMsg = IMSA_FALSE;

    pstCallCtx->stImsMsg.ulCsmId = 0;
    pstCallCtx->stImsMsg.ulCsmReason = 0xffffffff;
}

/*****************************************************************************
 Function Name  : IMSA_CallGetCurrentProcessingCallTypeByCallStatus
 Description    : ͨ������״̬��ȡ��ǰ���ڴ�����ĺ�������
 Input          : VOS_VOID
 Output         : penCallType------------��������
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310      2014-01-04  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallGetCurrentProcessingCallTypeByCallStatus
(
    IMSA_CALL_TYPE_ENUM_UINT8        *penCallType
)
{
    IMSA_CALL_MANAGER_STRU           *pstCallCtx  = IMSA_CallCtxGet();
    VOS_UINT32                       i           = IMSA_NULL;

    IMSA_INFO_LOG("IMSA_CallGetCurrentProcessingCallTypeByCallStatus is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallGetCurrentProcessingCallTypeByCallStatus_ENUM, LNAS_ENTRY);

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
            (IMSA_CALL_STATUS_HELD != pstCallCtx->astCallEntity[i].enStatus) &&
            (IMSA_CALL_STATUS_ACTIVE != pstCallCtx->astCallEntity[i].enStatus))
        {
            *penCallType = pstCallCtx->astCallEntity[i].enType;
            return;
        }
    }

    if (IMSA_CALL_MAX_NUM == i)
    {
        IMSA_INFO_LOG("IMSA_CallGetCurrentProcessingCallTypeByCallStatus:not found call type!");
        TLPS_PRINT2LAYER_INFO(IMSA_CallGetCurrentProcessingCallTypeByCallStatus_ENUM, 1);
    }

    return;
}

/*****************************************************************************
 Function Name  : IMSA_ProcCallResourceIsReady
 Description    : ��ԴԤ���ɹ��Ĵ�������Ŀǰ�Ĵ���ֻ�Ǳ������к���ʵ�壬
                  �����ʵ�����ڵȴ���ԴԤ���Ľ������֪ͨD2 IMS�ú��е���ԴԤ���ɹ�
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-12-06  Modify:emc dedicated
*****************************************************************************/
VOS_VOID IMSA_ProcCallResourceIsReady
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType,
    IMSA_CONN_MEDIA_PDP_TYPE_ENUM_UINT32    enMediaPdpType
)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();
    VOS_UINT32 i = 0;

    IMSA_INFO_LOG("IMSA_ProcCallResourceIsReady is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcCallResourceIsReady_ENUM, LNAS_ENTRY);

    if (IMSA_CONN_MEDIA_PDP_TYPE_VOICE == enMediaPdpType)
    {
        pstCallCtx->ucVoiceBearExistFlag = IMSA_TRUE;
    }
    else if (IMSA_CONN_MEDIA_PDP_TYPE_VIDEO == enMediaPdpType)
    {
        pstCallCtx->ucVideoBearExistFlag = IMSA_TRUE;
    }
    else
    {
    }

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
            (VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpNeedSendResResult) &&
            (IMSA_CALL_CALL_REASON_RESOURCE_READY == IMSA_CallIsResourceReady(&pstCallCtx->astCallEntity[i])))
        {
            pstCallCtx->astCallEntity[i].bitOpNeedSendResResult = IMSA_OP_FALSE;
            (VOS_VOID)IMSA_CallSendImsMsgResRsp(pstCallCtx->astCallEntity[i].ucImscallId,
                                                pstCallCtx->astCallEntity[i].ulResRspOpId,
                                                pstCallCtx->astCallEntity[i].ulDialogId,
                                                IMSA_CALL_CALL_REASON_RESOURCE_READY);
            /* ֹͣ�ȴ���ԴԤ�������ʱ */
            IMSA_StopTimer(&pstCallCtx->stResReadyTimer);
        }

    }

    if (IMSA_TRUE == IMSA_CONN_HasActiveVoicePdp())
    {
        IMSA_StopTimer(&pstCallCtx->stNormMediaLostRelCallTimer);
    }

    if (IMSA_TRUE == IMSA_CONN_HasEmcActiveVoicePdp())
    {
        IMSA_StopTimer(&pstCallCtx->stEmcMediaLostRelCallTimer);
    }

}

/*****************************************************************************
 Function Name  : IMSA_ProcCallResourceIsNotReady
 Description    : ��ԴԤ��ʧ�ܵĴ�������Ŀǰ�Ĵ���ֻ�Ǳ������к���ʵ�壬
                  �����ʵ�����ڵȴ���ԴԤ���Ľ������֪ͨD2 IMS�ú��е���ԴԤ��ʧ��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-12-06  Modify:emc dedicated
*****************************************************************************/
VOS_VOID IMSA_ProcCallResourceIsNotReady
(
    IMSA_CONN_TYPE_ENUM_UINT32              enConnType
)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_ProcCallResourceIsNotReady is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcCallResourceIsNotReady_ENUM, LNAS_ENTRY);


    /* ��Ƶcall��Ҫ�������غ���Ƶ���ض����ڣ����������������ȥ�����ulIsVideoMediaPdpReady
    ��Ҫ����ΪFALSE */
    if (IMSA_FALSE == IMSA_CONN_HasActiveVoicePdp())
    {
        pstCallCtx->ucVoiceBearExistFlag = IMSA_FALSE;
    }
    else if (IMSA_FALSE == IMSA_CONN_HasActiveVideoPdp())
    {
        pstCallCtx->ucVideoBearExistFlag = IMSA_FALSE;
    }
    else
    {
    }


}

/*****************************************************************************
 Function Name  : IMSA_CallNum2EmcSubType
 Description    : ���ݷ�����в���ӳ�䵽D2 IMS����Ľ�����������
 Input          : pstEmcCat         SPM�·��Ľ���������
 Output         : VOS_VOID
 Return Value   : CSM_EmergencyType     ӳ����

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
IMSA_IMS_EMERGENCY_TYPE_ENUM_UINT8 IMSA_CallNum2EmcSubType(const MN_CALL_EMERGENCY_CAT_STRU *pstEmcCat)
{
    IMSA_IMS_EMERGENCY_TYPE_ENUM_UINT8 enEmcSubType = IMSA_IMS_EMERGENCY_SUB_TYPE_GENERIC;

    IMSA_INFO_LOG("IMSA_CallNum2EmcSubType is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallNum2EmcSubType_ENUM, LNAS_ENTRY);

    switch (pstEmcCat->ucEmergencyCat)
    {
    case MN_CALL_EMER_CATEGORG_POLICE:
        enEmcSubType = IMSA_IMS_EMERGENCY_SUB_TYPE_POLICE;
        break;
    case MN_CALL_EMER_CATEGORG_AMBULANCE:
        enEmcSubType = IMSA_IMS_EMERGENCY_SUB_TYPE_AMBULANCE;
        break;
    case MN_CALL_EMER_CATEGORG_FIRE_BRIGADE:
        enEmcSubType = IMSA_IMS_EMERGENCY_SUB_TYPE_FIRE;
        break;
    case MN_CALL_EMER_CATEGORG_MARINE_GUARD:
        enEmcSubType = IMSA_IMS_EMERGENCY_SUB_TYPE_MARINE;
        break;
    case MN_CALL_EMER_CATEGORG_MOUNTAIN_RESCUE:
        enEmcSubType = IMSA_IMS_EMERGENCY_SUB_TYPE_MOUNTAIN;
        break;
    default:
        IMSA_ERR_LOG1("IMSA_CallNum2EmcSubType: invalid emergency category", pstEmcCat->ucEmergencyCat);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallNum2EmcSubType_ENUM, LNAS_PARAM_INVALID, pstEmcCat->ucEmergencyCat);
    }

    return enEmcSubType;
}

/*****************************************************************************
 Function Name  : IMSA_CallEmcSubType2SpmEmcCat
 Description    : ����D2 IMS����Ľ�����������ת��ΪSPM����Ľ�����������.
 Input          : EmcSubType     IMS�������������ͣ��𾯣��˾���.
 Output         : MN_CALL_EMER_CATEGORG_TYPE_ENUM_U8
 Return Value   : SPM����Ľ�����������.

 History        :
      1.mengchao 277840      2014-09-09  Draft Enact
*****************************************************************************/
MN_CALL_EMER_CATEGORG_TYPE_ENUM_U8 IMSA_CallEmcSubType2SPMEmcCat(const IMSA_IMS_EMERGENCY_TYPE_ENUM_UINT8 EmcSubType)
{
    MN_CALL_EMER_CATEGORG_TYPE_ENUM_U8 enEmcCat = MN_CALL_EMER_CATEGORG_MAX;
    IMSA_INFO_LOG1("IMSA_CallEmcSubType2SpmEmcCat: IMS Emc Type: ", EmcSubType);
    TLPS_PRINT2LAYER_INFO1(IMSA_CallEmcSubType2SPMEmcCat_ENUM, LNAS_ENTRY, EmcSubType);

    switch (EmcSubType)
    {
    case IMSA_IMS_EMERGENCY_SUB_TYPE_AMBULANCE:
        enEmcCat = MN_CALL_EMER_CATEGORG_AMBULANCE;
        break;
    case IMSA_IMS_EMERGENCY_SUB_TYPE_POLICE:
        enEmcCat = MN_CALL_EMER_CATEGORG_POLICE;
        break;
    case IMSA_IMS_EMERGENCY_SUB_TYPE_FIRE:
        enEmcCat = MN_CALL_EMER_CATEGORG_FIRE_BRIGADE;
        break;
    case IMSA_IMS_EMERGENCY_SUB_TYPE_MARINE:
        enEmcCat = MN_CALL_EMER_CATEGORG_MARINE_GUARD;
        break;
    case IMSA_IMS_EMERGENCY_SUB_TYPE_MOUNTAIN:
        enEmcCat = MN_CALL_EMER_CATEGORG_MOUNTAIN_RESCUE;
        break;
    default:
        IMSA_ERR_LOG1("IMSA_CallEmcSubType2SPMEmcCat: Unexpected EmcSubType: ", EmcSubType);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallEmcSubType2SPMEmcCat_ENUM, LNAS_PARAM_INVALID, EmcSubType);
    }

    return enEmcCat;
}

/*****************************************************************************
 Function Name  : IMSA_CallConverterClir2Ims
 Description    : ���ݷ�����в���ӳ�䵽D2 IMS�����CLIR����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : CSM_CallCidType     ӳ����

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
IMSA_IMS_CALL_CLIR_TYPE_ENUM_UINT8 IMSA_CallConverterClir2Ims(MN_CALL_CLIR_CFG_ENUM_UINT8 enClir)
{
    IMSA_IMS_CALL_CLIR_TYPE_ENUM_UINT8 enResult = IMSA_IMS_CALL_CLIR_TYPE_NONE;

    IMSA_INFO_LOG("IMSA_CallConverterClir2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallConverterClir2Ims_ENUM, LNAS_ENTRY);

    switch (enClir)
    {
    case MN_CALL_CLIR_AS_SUBS:
        enResult = IMSA_IMS_CALL_CLIR_TYPE_NONE;
        break;
    case MN_CALL_CLIR_INVOKE:
        enResult = IMSA_IMS_CALL_CLIR_TYPE_INVOCATION;
        break;
    case MN_CALL_CLIR_SUPPRESS:
        enResult = IMSA_IMS_CALL_CLIR_TYPE_SUPPRESSION;
        break;
    default:
        IMSA_ERR_LOG1("IMSA_CallConverterClir2Ims: invalid clir setting ", enClir);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallConverterClir2Ims_ENUM, LNAS_PARAM_INVALID, enClir);
    }

    return enResult;
}
/*****************************************************************************
 Function Name  : IMSA_CallCopyRemoteAddrForm
 Description    : ת��BCD��ʽ�ı��к���ΪASCII�ַ���������
 Input          : pstCalledNum      ��ת����BCD����
 Output         : paucRemoteAddr    ת���������ĵ�ַ
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallCopyRemoteAddrForm(const MN_CALL_CALLED_NUM_STRU *pstCalledNum, VOS_CHAR *paucRemoteAddr)
{
    VOS_UINT8 ucCallTon;

    IMSA_INFO_LOG("IMSA_CallCopyRemoteAddrForm is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallCopyRemoteAddrForm_ENUM, LNAS_ENTRY);

    /*24.008 10.5.4.9,Type of Number,5,6,7bit of the MN_CALL_NUM_TYPE_ENUM_U8*/
    ucCallTon = (pstCalledNum->enNumType>>4)&0x7;

    /*���ʺ��룬��������"+"*/
    if(ucCallTon == MN_CALL_TON_INTERNATIONAL)
    {
        paucRemoteAddr[0] = '+';

        if (VOS_FALSE == IMSA_UtilBcdNumberToAscii(pstCalledNum->aucBcdNum, pstCalledNum->ucNumLen, &paucRemoteAddr[1]))
        {
            IMSA_ERR_LOG("IMSA_CallCopyRemoteAddrForm: BCD to ASCII fail!");
            TLPS_PRINT2LAYER_ERROR1(IMSA_CallCopyRemoteAddrForm_ENUM, LNAS_FAIL, 1);
        }

        return;
    }

    /*�ǹ��ʺ���*/
    if (VOS_FALSE == IMSA_UtilBcdNumberToAscii(pstCalledNum->aucBcdNum, pstCalledNum->ucNumLen, paucRemoteAddr))
    {
        IMSA_ERR_LOG("IMSA_CallCopyRemoteAddrForm: BCD to ASCII fail.");
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallCopyRemoteAddrForm_ENUM, LNAS_FAIL, 2);
    }
}

/*****************************************************************************
 Function Name  : IMSA_CallConverterOrig2Ims
 Description    : ����������������D2 Input��Ϣ��ת������
 Input          : ulCallId          ����Id
                  pSpmParam         SPM�������
 Output         : pstInputEvent    ת���������ĵ�ַ
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallConverterOrig2Ims(VOS_UINT32 ulCallId,
                                    const MN_CALL_ORIG_PARAM_STRU*  pSpmParam,
                                    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent)
{
    IMSA_INFO_LOG("IMSA_CallConverterOrig2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallConverterOrig2Ims_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulCallId;

    pstInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_CALL;

    /* ���ú��������OpId */
    pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_DIAL;
    pstInputEvent->evt.stInputCallEvent.ulOpId = IMSA_AllocImsOpId();

    /* ���ú������� */
    pstInputEvent->evt.stInputCallEvent.enCallType = (IMSA_IMS_CALL_MODE_ENUM_UINT8)pSpmParam->enCallType;

    /* ���ý�������ʶ */
    if (MN_CALL_TYPE_EMERGENCY == pSpmParam->enCallType)
    {
        pstInputEvent->evt.stInputCallEvent.bitOpEmergencyType = IMSA_OP_TRUE;
        pstInputEvent->evt.stInputCallEvent.enEmergencyType = IMSA_CallNum2EmcSubType(&pSpmParam->stEmergencyCat);
    }
    else
    {
        pstInputEvent->evt.stInputCallEvent.bitOpEmergencyType = IMSA_OP_TRUE;
        pstInputEvent->evt.stInputCallEvent.enEmergencyType = IMSA_IMS_EMERGENCY_SUB_TYPE_NONE;
    }

    /* ���ñ����û� */
    pstInputEvent->evt.stInputCallEvent.bitOpRemoteAddress = IMSA_OP_TRUE;
    IMSA_CallCopyRemoteAddrForm(&pSpmParam->stDialNumber, pstInputEvent->evt.stInputCallEvent.aucRemoteAddress);

    /* ����CLIR�����ʶ */
    pstInputEvent->evt.stInputCallEvent.bitOpClirType = IMSA_OP_TRUE;
    pstInputEvent->evt.stInputCallEvent.enClirCfg = IMSA_CallConverterClir2Ims(pSpmParam->enClirCfg);
}
/*****************************************************************************
 Function Name  : IMSA_CallConverterCreatEconf2Ims
 Description    : ������ǿ�෽ͨ�����������D2 Input��Ϣ��ת������
 Input          : ulCallId          ����Id
                  pSpmParam         SPM�������
 Output         : pstInputEvent    ת���������ĵ�ַ
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181  2014-12-11  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallConverterCreatEconf2Ims(VOS_UINT32 ulCallId,
                                    const TAF_CALL_ECONF_DIAL_REQ_STRU*  pSpmParam,
                                    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent)
{
    VOS_UINT8                           i = 0;
    IMSA_INFO_LOG("IMSA_CallConverterCreatEconf2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallConverterCreatEconf2Ims_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulCallId;

    pstInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_CALL;

    /* ���ú��������OpId */
    pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_CREAT_NEW_ECONFERENCE;
    pstInputEvent->evt.stInputCallEvent.ulOpId = IMSA_AllocImsOpId();

    /* ���ú������� */
    pstInputEvent->evt.stInputCallEvent.enCallType = (IMSA_IMS_CALL_MODE_ENUM_UINT8)pSpmParam->enCallType;

    /* ���ñ����û� */
    pstInputEvent->evt.stInputCallEvent.bitOpEconfList = IMSA_OP_TRUE;
    pstInputEvent->evt.stInputCallEvent.stEconfList.ucNumCalls = (VOS_UINT8)pSpmParam->stEconfCalllist.ulCallNum;
    for (i = 0; i < pSpmParam->stEconfCalllist.ulCallNum; i ++)
    {
        IMSA_CallCopyRemoteAddrForm(&(pSpmParam->stEconfCalllist.astDialNumber[i]), pstInputEvent->evt.stInputCallEvent.stEconfList.astEconfList[i].aucRemoteAddress);
    }


    /* ����CLIR�����ʶ */
    pstInputEvent->evt.stInputCallEvent.bitOpClirType = IMSA_OP_TRUE;
    pstInputEvent->evt.stInputCallEvent.enClirCfg = IMSA_CallConverterClir2Ims(pSpmParam->enClirCfg);
}
/*****************************************************************************
 Function Name  : IMSA_CallConverterEconfAddUser2Ims
 Description    : ������ǿ�෽ͨ�����������D2 Input��Ϣ��ת������
 Input          : ulCallId          ����Id
                  pSpmParam         SPM�������
 Output         : pstInputEvent    ת���������ĵ�ַ
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181  2014-12-11  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallConverterEconfAddUser2Ims(VOS_UINT32 ulCallId,
                                    const TAF_CALL_ECONF_CALL_LIST_STRU*  pSpmParam,
                                    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent)
{
    VOS_UINT8                           i = 0;
    IMSA_INFO_LOG("IMSA_CallConverterEconfAddUser2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallConverterEconfAddUser2Ims_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulCallId;

    pstInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_CALL;

    /* ���ú��������OpId */
    pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_ECONFERENCE_INVITE_NEW_PARTICIPANT;
    pstInputEvent->evt.stInputCallEvent.ulOpId = IMSA_AllocImsOpId();

    /* ���ñ����û� */
    pstInputEvent->evt.stInputCallEvent.bitOpEconfList = IMSA_OP_TRUE;
    pstInputEvent->evt.stInputCallEvent.stEconfList.ucNumCalls = (VOS_UINT8)pSpmParam->ulCallNum;
    for (i = 0; i < pSpmParam->ulCallNum; i ++)
    {
        IMSA_CallCopyRemoteAddrForm(&(pSpmParam->astDialNumber[i]), pstInputEvent->evt.stInputCallEvent.stEconfList.astEconfList[i].aucRemoteAddress);
    }

}

/*****************************************************************************
 Function Name  : IMSA_CallConverterSups2Ims
 Description    : ��ֵ�������������D2 Input��Ϣ��ת������
 Input          : ulCallId          ����Id
                  pSpmParam         SPM�������
 Output         : pstInputEvent    ת���������ĵ�ַ
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallConverterSups2Ims(VOS_UINT32 ulCallId,
                                    const MN_CALL_SUPS_PARAM_STRU*  pSpmParam,
                                    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent)
{
    IMSA_CALL_ENTITY_STRU *pstCallEntity = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallConverterSups2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallConverterSups2Ims_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulCallId;

    /* ��Ҫ��SPMCALLIDת��ΪIMS CALLID */
    pstCallEntity = IMSA_CallEntityGetUsedBySpmCallId(pSpmParam->callId);

    pstInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_CALL;

    /* ���ú���OpId */
    pstInputEvent->evt.stInputCallEvent.ulOpId = IMSA_AllocImsOpId();

    pstInputEvent->evt.stInputCallEvent.enCallType = (IMSA_IMS_CALL_MODE_ENUM_UINT8)pSpmParam->enCallType;

    switch (pSpmParam->enCallSupsCmd)
    {
        /* CHLD=0, Releases all held calls or sets User Determined User Busy (UDUB) for a waiting call */
        case MN_CALL_SUPS_CMD_REL_HELD_OR_UDUB:
            {
                pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_REL_HELD_OR_WAITING;
                break;
            }
        /* CHLD=1, Releases all active calls (if any exist) and accepts the other (held or waiting) call */
        case MN_CALL_SUPS_CMD_REL_ACT_ACPT_OTH:
            {
                pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_REL_ACTIVE_AND_ACCEPT_OTH;
                break;
            }
        /* CHLD=1x, Releases a specific active call X*/
        case MN_CALL_SUPS_CMD_REL_CALL_X:
            {
                pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_RELEASE_AT_X;

                pstInputEvent->evt.stInputCallEvent.bitOpCallIndex = IMSA_OP_TRUE;
                if (pstCallEntity)
                {
                    pstInputEvent->evt.stInputCallEvent.ulCallIndex = pstCallEntity->ucImscallId;
                }
                pstInputEvent->evt.stInputCallEvent.enRelCause = IMSA_IMS_CALL_REL_CAUSE_USER_REL;
                break;
            }
        /* ATH, Release all calls */
        case MN_CALL_SUPS_CMD_REL_ALL_CALL:
            {
                pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_HANGUP;
                pstInputEvent->evt.stInputCallEvent.enRelCause = IMSA_IMS_CALL_REL_CAUSE_USER_REL;
                break;
            }
        /* CHLD=2, Places all active calls (if any exist) on hold and accepts the other (held or waiting) call */
        case MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH:
            {
                pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_SWAP;
                break;
            }
        /* CHLD=2x, Places all active calls on hold except call X with which communication shall be supported */
        case MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X:
            {
                pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_HOLD_ALL_EXCEPT_X;

                pstInputEvent->evt.stInputCallEvent.bitOpCallIndex = IMSA_OP_TRUE;
                if (pstCallEntity)
                {
                    pstInputEvent->evt.stInputCallEvent.ulCallIndex = pstCallEntity->ucImscallId;
                }
                break;
            }
        /* CHLD=3, Adds a held call to the conversation */
        case MN_CALL_SUPS_CMD_BUILD_MPTY:
            {
                pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_CONFERENCE;
                break;
            }
        case MN_CALL_SUPS_CMD_ECONF_REL_USER:
            {
                pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_ECONFERENCE_KICK_PARTICIPANT;
                pstInputEvent->evt.stInputCallEvent.bitOpEconfList = IMSA_OP_TRUE;
                /* ÿ�����˽�������һ�� */
                pstInputEvent->evt.stInputCallEvent.stEconfList.ucNumCalls = 1;
                IMSA_CallCopyRemoteAddrForm(&pSpmParam->stRemoveNum,
                                            pstInputEvent->evt.stInputCallEvent.stEconfList.astEconfList[0].aucRemoteAddress);
                break;
            }
        case MN_CALL_SUPS_CMD_ECONF_MERGE_CALL:
            {
                pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_ECONFERENCE_MERGER_NEW_PARTICIPANT;
                break;
            }
        default:
            IMSA_ERR_LOG1("IMSA_CallConverterSups2Ims : unsupported sups cmd", pSpmParam->enCallSupsCmd);
            TLPS_PRINT2LAYER_ERROR1(IMSA_CallConverterSups2Ims_ENUM, LNAS_PARAM_INVALID, pSpmParam->enCallSupsCmd);
    }
}

/*****************************************************************************
 Function Name  : IMSA_CallConverterStartDtmf2Ims
 Description    : ����DTMF���������D2 Input��Ϣ��ת������
 Input          : ulCallId          ����Id
                  pSpmParam         SPM�������
                  ulDuration        ����ʱ��
 Output         : pstInputEvent    ת���������ĵ�ַ
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-10-14  Modify
*****************************************************************************/
VOS_VOID IMSA_CallConverterDtmf2Ims
(
    VOS_UINT32                          ulCallId,
    VOS_CHAR                            cKey,
    VOS_UINT32                          ulDuration,
    IMSA_IMS_INPUT_EVENT_STRU          *pstInputEvent
)
{
    IMSA_IMS_DTMF_KEY_ENUM_UINT8        enDtmfKey = IMSA_IMS_DTMF_KEY_0;

    IMSA_INFO_LOG("IMSA_CallConverterDtmf2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallConverterDtmf2Ims_ENUM, LNAS_ENTRY);

    (VOS_VOID)ulCallId;

    pstInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_CALL;

    /* ���ú��������OpId */
    pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_DTMF;
    pstInputEvent->evt.stInputCallEvent.ulOpId = IMSA_AllocImsOpId();

    pstInputEvent->evt.stInputCallEvent.bitOpDtmf = IMSA_OP_TRUE;

    (VOS_VOID)IMSA_AsciiToDtmfKeyEnum(cKey, &enDtmfKey);
    pstInputEvent->evt.stInputCallEvent.stDtmf.enDtmfKey = enDtmfKey;
    pstInputEvent->evt.stInputCallEvent.stDtmf.ulDuration = ulDuration;
}

/*****************************************************************************
 Function Name  : IMSA_CallConverterResRsp2Ims
 Description    : ��ԴԤ�����֪ͨ�Ĳ�����D2 Input��Ϣ��ת������
 Input          : ulImsOpId         D2 IMS��Ҫ��opid
                  ulCallId          ����Id
                  ulSuccess         ��ԴԤ�������VOS_TRUE��ʾ�ɹ���VOS_FALSE��ʾʧ��
 Output         : pstInputEvent    ת���������ĵ�ַ
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.wangchen 00209181   2015-01-20  Modify:video to voice
*****************************************************************************/
VOS_VOID IMSA_CallConverterResRsp2Ims
(
    VOS_UINT32 ulImsOpId,
    VOS_UINT32 ulCallId,
    VOS_UINT32 ulDialogId,
    IMSA_CALL_CALL_REASON_RESOURCE_RESULT_ENUM_UINT8 enResResult,
    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent
)
{
    IMSA_INFO_LOG("IMSA_CallConverterResRsp2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallConverterResRsp2Ims_ENUM, LNAS_ENTRY);

    pstInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_CALL;

    /* ����OpId */
    pstInputEvent->evt.stInputCallEvent.ulOpId = ulImsOpId;

    switch(enResResult)
    {
        case IMSA_CALL_CALL_REASON_RESOURCE_READY:
            pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_RESOURCE_READY;
            break;

        case IMSA_CALL_CALL_REASON_RESOURCE_ONLY_VOICE:
            pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_RESOURCE_ONLY_VOICE_READY;
            break;

        case IMSA_CALL_CALL_REASON_RESOURCE_FAILED:
            pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_RESOURCE_FAILED;
            break;
        default:
            IMSA_INFO_LOG("IMSA_CallConverterResRsp2Ims error result!");
            TLPS_PRINT2LAYER_INFO(IMSA_CallConverterResRsp2Ims_ENUM, LNAS_PARAM_INVALID);
            break;
    }

    pstInputEvent->evt.stInputCallEvent.bitOpCallIndex = IMSA_OP_TRUE;
    pstInputEvent->evt.stInputCallEvent.ulCallIndex = ulCallId;
    pstInputEvent->evt.stInputCallEvent.ulDlgId = ulDialogId;
}

/*****************************************************************************
 Function Name  : IMSA_CallSendImsMsgResRsp
 Description    : ������ԴԤ�����
 Input          : ulCallId          ����Id
                  ulImsOpId         D2 IMS��Ҫ��opid
                  ulSuccess         ��ԴԤ�������VOS_TRUE��ʾ�ɹ���VOS_FALSE��ʾʧ��
 Output         : VOS_VOID
 Return Value   : ������Ϣ���

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.wangchen 00209181   2015-01-20  Modify:video to voice
*****************************************************************************/
VOS_UINT32 IMSA_CallSendImsMsgResRsp
(
    VOS_UINT32 ulCallId,
    VOS_UINT32 ulImsOpId,
    VOS_UINT32 ulDialogId,
    IMSA_CALL_CALL_REASON_RESOURCE_RESULT_ENUM_UINT8 enResResult
)
{
    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendImsMsgResRsp is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendImsMsgResRsp_ENUM, LNAS_ENTRY);

    pstInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));
    if (VOS_NULL_PTR == pstInputEvent)
    {
        IMSA_ERR_LOG("IMSA_CallSendImsMsgResRsp: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendImsMsgResRsp_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET_S( pstInputEvent,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU),
                    0,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    IMSA_CallConverterResRsp2Ims(ulImsOpId,
                                 ulCallId,
                                 ulDialogId,
                                 enResResult,
                                 pstInputEvent);

    IMSA_SndImsMsgCallEvent(pstInputEvent);

    IMSA_MEM_FREE(pstInputEvent);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallSendImsMsgDial
 Description    : �������
 Input          : ulCallId          ����Id
                  pSpmParam         SPM�·��ķ�����в���
 Output         : VOS_VOID
 Return Value   : ������Ϣ���

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-10-14  Modify
*****************************************************************************/
VOS_UINT32 IMSA_CallSendImsMsgDial
(
    VOS_UINT32                          ulCallId,
    const SPM_IMSA_CALL_ORIG_REQ_STRU  *pstAppMsg
)
{
    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendImsMsgDial is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendImsMsgDial_ENUM, LNAS_ENTRY);

    pstInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));
    if (VOS_NULL_PTR == pstInputEvent)
    {
        IMSA_ERR_LOG("IMSA_CallSendImsMsgDial: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendImsMsgDial_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET_S( pstInputEvent,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU),
                    0,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    IMSA_CallConverterOrig2Ims(ulCallId, &pstAppMsg->stOrig, pstInputEvent);

    IMSA_SndImsMsgCallEvent(pstInputEvent);

    (VOS_VOID)IMSA_CallImsMsgSave(&pstInputEvent->evt.stInputCallEvent);

    /* ����SPM���� */
    IMSA_CallSpmOrigReqMsgSave(pstAppMsg);

    IMSA_MEM_FREE(pstInputEvent);

    return VOS_TRUE;
}
/*****************************************************************************
 Function Name  : IMSA_CallSendImsMsgCreatEconf
 Description    : �������
 Input          : ulCallId          ����Id
                  pSpmParam         SPM�·��ķ�����в���
 Output         : VOS_VOID
 Return Value   : ������Ϣ���

 History        :
      1.wangchen 00209181  2014-12-11  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallSendImsMsgCreatEconf
(
    VOS_UINT32                              ulCallId,
    const SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU  *pstAppMsg
)
{
    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendImsMsgCreatEconf is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendImsMsgCreatEconf_ENUM, LNAS_ENTRY);

    pstInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));
    if (VOS_NULL_PTR == pstInputEvent)
    {
        IMSA_ERR_LOG("IMSA_CallSendImsMsgCreatEconf: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendImsMsgCreatEconf_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET_S( pstInputEvent,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU),
                    0,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    IMSA_CallConverterCreatEconf2Ims(ulCallId, &pstAppMsg->stDialReq, pstInputEvent);

    IMSA_SndImsMsgCallEvent(pstInputEvent);

    (VOS_VOID)IMSA_CallImsMsgSave(&pstInputEvent->evt.stInputCallEvent);

    /* ����SPM���� */
    IMSA_CallSpmEconfDialReqMsgSave(pstAppMsg);

    IMSA_MEM_FREE(pstInputEvent);

    return VOS_TRUE;
}
/*****************************************************************************
 Function Name  : IMSA_CallSendImsMsgEconfAddUser
 Description    : �������
 Input          : ulCallId          ����Id
                  pSpmParam         SPM�·��ķ�����в���
 Output         : VOS_VOID
 Return Value   : ������Ϣ���

 History        :
      1.wangchen 00209181  2014-12-11  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallSendImsMsgEconfAddUser
(
    VOS_UINT32                              ulCallId,
    const SPM_IMSA_CALL_ECONF_ADD_USERS_REQ_STRU  *pstAppMsg
)
{
    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendImsMsgEconfAddUser is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendImsMsgEconfAddUser_ENUM, LNAS_ENTRY);

    pstInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));
    if (VOS_NULL_PTR == pstInputEvent)
    {
        IMSA_ERR_LOG("IMSA_CallSendImsMsgEconfAddUser: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendImsMsgEconfAddUser_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET_S( pstInputEvent,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU),
                    0,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    IMSA_CallConverterEconfAddUser2Ims(ulCallId, &pstAppMsg->stEconfCalllist, pstInputEvent);

    IMSA_SndImsMsgCallEvent(pstInputEvent);

    (VOS_VOID)IMSA_CallImsMsgSave(&pstInputEvent->evt.stInputCallEvent);

    /* ����SPM���� */
    IMSA_CallSpmEconfAddUserMsgSave(pstAppMsg);

    IMSA_MEM_FREE(pstInputEvent);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallInviteNewPtptAvailableCheck
 Description    : ����������������Լ��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : �����Լ���Ƿ�ɹ�

 History        :
      1.xiongxianghui00253310      2014-02-10  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallInviteNewPtptAvailableCheck(VOS_VOID)
{

    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();
    VOS_UINT32 i = 0;
    VOS_UINT32 ulResult = VOS_FALSE;

    IMSA_INFO_LOG("IMSA_CallInviteNewPtptAvailableCheck is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallInviteNewPtptAvailableCheck_ENUM, LNAS_ENTRY);

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
            (MN_CALL_IN_MPTY == pstCallCtx->astCallEntity[i].enMpty) &&
            (VOS_FALSE == pstCallCtx->astCallEntity[i].ucIsEconfFlag))
        {
            ulResult = VOS_TRUE;
            break;
        }
    }

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_CallSpmInviteNewPtptReqMsgSave
 Description    : �������ڴ����SPM����
 Input          : pstAppMsg   SPM�·������������������
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui00253310      2014-02-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallSpmInviteNewPtptReqMsgSave(const SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ_STRU *pstAppMsg)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallSpmInviteNewPtptReqMsgSave is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSpmInviteNewPtptReqMsgSave_ENUM, LNAS_ENTRY);

    /* ���֮ǰ�Ѿ��б��������򷵻�ʧ�� */
    if (IMSA_OP_TRUE == pstCallCtx->stSpmMsg.bitOpSpmMsg)
    {
        IMSA_INFO_LOG("IMSA_CallSpmInviteNewPtptReqMsgSave has existed");
        TLPS_PRINT2LAYER_INFO(IMSA_CallSpmInviteNewPtptReqMsgSave_ENUM, IMSA_EXISTED);
    }

    /* ���ñ���λ */
    pstCallCtx->stSpmMsg.bitOpSpmMsg = IMSA_OP_TRUE;

    /* ���湫������ */
    pstCallCtx->stSpmMsg.ulSpmMsgId = pstAppMsg->ulMsgId;
    pstCallCtx->stSpmMsg.usClientId = pstAppMsg->usClientId;
    pstCallCtx->stSpmMsg.ulOpId     = pstAppMsg->ucOpId;
    pstCallCtx->stSpmMsg.ulCallId   = IMSA_CALL_INVALID_ID;

}


/*****************************************************************************
 Function Name  : IMSA_CallConverterInviteNewPtpt2Ims
 Description    : ��������������������D2 Input��Ϣ��ת������
 Input          : ulCallId          ����Id
                  pstCalledNum      SPM�������
 Output         : pstInputEvent     ת���������ĵ�ַ
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui00253310      2014-02-10  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallConverterInviteNewPtpt2Ims(VOS_UINT32 ulCallId,
                                    const MN_CALL_CALLED_NUM_STRU* pstCalledNum,
                                    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent)
{
    IMSA_INFO_LOG("IMSA_CallConverterInviteNewPtpt2Ims is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallConverterInviteNewPtpt2Ims_ENUM, LNAS_ENTRY);
    (VOS_VOID)ulCallId;

    pstInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_CALL;

    /* ���ú��������OpId */
    pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_CONFERENCE_INVITE_NEW_PARTICIPANT;
    pstInputEvent->evt.stInputCallEvent.ulOpId = IMSA_AllocImsOpId();

    /* ���ñ����û� */
    pstInputEvent->evt.stInputCallEvent.bitOpRemoteAddress = IMSA_OP_TRUE;
    IMSA_CallCopyRemoteAddrForm(pstCalledNum, pstInputEvent->evt.stInputCallEvent.aucRemoteAddress);
}


/*****************************************************************************
 Function Name  : IMSA_CallSendImsMsgInviteNewPtpt
 Description    : ��IMS�������������������
 Input          : ulCallId          ����Id
                  pstAppMsg         SPM�·���������������������
 Output         : VOS_VOID
 Return Value   : ������Ϣ���

 History        :
      1.xiongxianghui00253310      2014-02-10  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallSendImsMsgInviteNewPtpt
(
    VOS_UINT32 ulCallId,
    const SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ_STRU *pstAppMsg
)
{
    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendImsMsgInviteNewPtpt is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendImsMsgInviteNewPtpt_ENUM, LNAS_ENTRY);

    pstInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));
    if (VOS_NULL_PTR == pstInputEvent)
    {
        IMSA_ERR_LOG("IMSA_CallSendImsMsgInviteNewPtpt: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendImsMsgInviteNewPtpt_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET_S( pstInputEvent,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU),
                    0,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    IMSA_CallConverterInviteNewPtpt2Ims(ulCallId, &pstAppMsg->stNewPtptNumber, pstInputEvent);

    IMSA_SndImsMsgCallEvent(pstInputEvent);

    (VOS_VOID)IMSA_CallImsMsgSave(&pstInputEvent->evt.stInputCallEvent);

    /*  ����SPM���� */
    IMSA_CallSpmInviteNewPtptReqMsgSave(pstAppMsg);

    IMSA_MEM_FREE(pstInputEvent);

    return VOS_TRUE;
}



/*****************************************************************************
 Function Name  : IMSA_CallSendImsMsgStartDtmf
 Description    : ����DTMF
 Input          : ulCallId          ����Id
                  ulKey             DTMF��Ӧ������
                  ulDuration        ����ʱ��
 Output         : VOS_VOID
 Return Value   : ������Ϣ���

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-10-14  Modify
*****************************************************************************/
VOS_UINT32 IMSA_CallSendImsMsgStartDtmf
(
    VOS_UINT32                          ulCallId,
    VOS_CHAR                            cKey,
    VOS_UINT32                          ulDuration
)
{
    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendImsMsgStartDtmf is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendImsMsgStartDtmf_ENUM, LNAS_ENTRY);

    pstInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));
    if (VOS_NULL_PTR == pstInputEvent)
    {
        IMSA_ERR_LOG("IMSA_CallSendImsMsgStartDtmf: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendImsMsgStartDtmf_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET_S( pstInputEvent,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU),
                    0,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    IMSA_CallConverterDtmf2Ims(ulCallId, cKey, ulDuration, pstInputEvent);

    IMSA_SndImsMsgCallEvent(pstInputEvent);

    IMSA_MEM_FREE(pstInputEvent);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallSendImsMsgStopDtmf
 Description    : ֹͣDTMF
 Input          : ulCallId          ����Id
                  ulKey             DTMF��Ӧ������
                  ulDuration        ����ʱ��
 Output         : VOS_VOID
 Return Value   : ������Ϣ���

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-10-14  Modify
*****************************************************************************/
VOS_UINT32 IMSA_CallSendImsMsgStopDtmf
(
    VOS_UINT32                          ulCallId,
    VOS_CHAR                            cKey
)
{
    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendImsMsgStopDtmf is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendImsMsgStopDtmf_ENUM, LNAS_ENTRY);

    (VOS_VOID)cKey;

    pstInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));
    if (VOS_NULL_PTR == pstInputEvent)
    {
        IMSA_ERR_LOG("IMSA_CallSendImsMsgStopDtmf: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendImsMsgStopDtmf_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET_S( pstInputEvent,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU),
                    0,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    IMSA_CallConverterDtmf2Ims(ulCallId, '0', 0, pstInputEvent);

    IMSA_SndImsMsgCallEvent(pstInputEvent);

    IMSA_MEM_FREE(pstInputEvent);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallSendImsMsgSups
 Description    : ������ֵ����
 Input          : ulCallId          ����Id
                  pSpmParam         SPM�·�����ֵ�����������
 Output         : VOS_VOID
 Return Value   : ������Ϣ���

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-10-14  Modify
*****************************************************************************/
VOS_UINT32 IMSA_CallSendImsMsgSups
(
    VOS_UINT32                              ulCallId,
    const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU  *pstAppMsg
)
{
    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendImsMsgSups is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendImsMsgSups_ENUM, LNAS_ENTRY);

    pstInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));
    if (VOS_NULL_PTR == pstInputEvent)
    {
        IMSA_ERR_LOG("IMSA_CallSendImsMsgSups: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendImsMsgSups_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET_S( pstInputEvent,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU),
                    0,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    IMSA_CallConverterSups2Ims(ulCallId, &pstAppMsg->stCallMgmtCmd, pstInputEvent);

    IMSA_SndImsMsgCallEvent(pstInputEvent);

    (VOS_VOID)IMSA_CallImsMsgSave(&pstInputEvent->evt.stInputCallEvent);

    /* ����SPM���� */
    IMSA_CallSpmSupsCmdReqMsgSave(pstAppMsg);

    IMSA_MEM_FREE(pstInputEvent);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallSendImsMsgSupsNotNeedCnf
 Description    : ������ֵ����
 Input          : ulCallId          ����Id
                  pSpmParam         SPM�·�����ֵ�����������
 Output         : VOS_VOID
 Return Value   : ������Ϣ���

 History        :
      1.wangchen 00209181  2015-11-23  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallSendImsMsgSupsRelCallXWithoutCnf
(
    VOS_UINT32                              ulCallId
)
{
    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendImsMsgSups is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendImsMsgSups_ENUM, LNAS_ENTRY);

    pstInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));
    if (VOS_NULL_PTR == pstInputEvent)
    {
        IMSA_ERR_LOG("IMSA_CallSendImsMsgSups: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendImsMsgSups_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET_S(pstInputEvent, sizeof(IMSA_IMS_INPUT_EVENT_STRU), 0, sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_RELEASE_AT_X;

    pstInputEvent->evt.stInputCallEvent.bitOpCallIndex = IMSA_OP_TRUE;

    pstInputEvent->evt.stInputCallEvent.ulCallIndex = ulCallId;

    IMSA_SndImsMsgCallEvent(pstInputEvent);

    //(VOS_VOID)IMSA_CallImsMsgSave(&pstInputEvent->evt.stInputCallEvent);

    IMSA_MEM_FREE(pstInputEvent);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallSendImsMsgSupsNotNeedCnf
 Description    : ������ֵ����
 Input          : ulCallId          ����Id
                  pSpmParam         SPM�·�����ֵ�����������
 Output         : VOS_VOID
 Return Value   : ������Ϣ���

 History        :
      1.wangchen 00209181  2015-11-23  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallSendImsMsgSupsRelCallX
(
    VOS_UINT32                              ulCallId
)
{
    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendImsMsgSups is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendImsMsgSups_ENUM, LNAS_ENTRY);

    pstInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));
    if (VOS_NULL_PTR == pstInputEvent)
    {
        IMSA_ERR_LOG("IMSA_CallSendImsMsgSups: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendImsMsgSups_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET_S(pstInputEvent, sizeof(IMSA_IMS_INPUT_EVENT_STRU), 0, sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_RELEASE_AT_X;

    pstInputEvent->evt.stInputCallEvent.bitOpCallIndex = IMSA_OP_TRUE;

    pstInputEvent->evt.stInputCallEvent.ulCallIndex = ulCallId;

    IMSA_SndImsMsgCallEvent(pstInputEvent);

    (VOS_VOID)IMSA_CallImsMsgSave(&pstInputEvent->evt.stInputCallEvent);

    IMSA_MEM_FREE(pstInputEvent);

    return VOS_TRUE;
}


/*****************************************************************************
 Function Name  : IMSA_CallSendImsMsgModify
 Description    : ����voice<->video���л�����
 Input          :
 Output         : VOS_VOID
 Return Value   : ������Ϣ���

 History        :
      1.wangchen 00209181 2014-06-19  Draft Enact
      2.wangchen 00209181 2014-12-02  Modify:DTS2014112906255
*****************************************************************************/
VOS_UINT32 IMSA_CallSendImsMsgModify
(
    const SPM_IMSA_CALL_MODIFY_REQ_STRU  *pstAppMsg
)
{
    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent = VOS_NULL_PTR;
    IMSA_CALL_ENTITY_STRU              *pstCallEntity   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendImsMsgModify is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendImsMsgModify_ENUM, LNAS_ENTRY);

    pstCallEntity = IMSA_CallEntityGetUsedBySpmCallId(pstAppMsg->callId);

    if (VOS_NULL_PTR == pstCallEntity)
    {
        IMSA_ERR_LOG("IMSA_CallSendImsMsgModify: NO CALL ID");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendImsMsgModify_ENUM, IMSA_CALL_NOT_EXIST);
        return VOS_FALSE;
    }

    pstInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));
    if (VOS_NULL_PTR == pstInputEvent)
    {
        IMSA_ERR_LOG("IMSA_CallSendImsMsgModify: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendImsMsgModify_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET_S( pstInputEvent,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU),
                    0,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU));


    pstInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_CALL;
    pstInputEvent->evt.stInputCallEvent.ulOpId= IMSA_AllocImsOpId();
    pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_MODIFY;
    pstInputEvent->evt.stInputCallEvent.bitOpCallIndex = IMSA_OP_TRUE;
    pstInputEvent->evt.stInputCallEvent.ulCallIndex = pstCallEntity->ucSpmcallId;

    pstInputEvent->evt.stInputCallEvent.bitOpModify = IMSA_OP_TRUE;
    pstInputEvent->evt.stInputCallEvent.stModify.enSrcCallType = pstAppMsg->enCurrCallType;
    pstInputEvent->evt.stInputCallEvent.stModify.enDstCallType = pstAppMsg->enExpectCallType;

    IMSA_SndImsMsgCallEvent(pstInputEvent);

    (VOS_VOID)IMSA_CallImsMsgSave(&pstInputEvent->evt.stInputCallEvent);

    /* ����SPM���� */
    IMSA_CallSpmModifyMsgSave(pstAppMsg);

    IMSA_MEM_FREE(pstInputEvent);

    return VOS_TRUE;
}
/*****************************************************************************
 Function Name  : IMSA_CallSendImsMsgAnswerRemoteModify
 Description    : ����voice<->video���л�����
 Input          :
 Output         : VOS_VOID
 Return Value   : ������Ϣ���

 History        :
      1.wangchen 00209181 2014-06-19  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallSendImsMsgAnswerRemoteModify
(
    const SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ_STRU  *pstAppMsg
)
{
    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent = VOS_NULL_PTR;
    IMSA_CALL_ENTITY_STRU *pstCallEntity = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendImsMsgAnswerRemoteModify is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendImsMsgAnswerRemoteModify_ENUM, LNAS_ENTRY);

    pstCallEntity = IMSA_CallEntityGetUsedBySpmCallId(pstAppMsg->callId);

    if (VOS_NULL_PTR == pstCallEntity)
    {
        IMSA_ERR_LOG("IMSA_CallSendImsMsgAnswerRemoteModify: NO CALL ID");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendImsMsgAnswerRemoteModify_ENUM, IMSA_CALL_NOT_EXIST);
        return VOS_FALSE;
    }

    pstInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));
    if (VOS_NULL_PTR == pstInputEvent)
    {
        IMSA_ERR_LOG("IMSA_CallSendImsMsgAnswerRemoteModify: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendImsMsgAnswerRemoteModify_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET_S( pstInputEvent,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU),
                    0,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU));


    pstInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_CALL;
    pstInputEvent->evt.stInputCallEvent.ulOpId= IMSA_AllocImsOpId();
    pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_ANSWER_REMOTE_MODIFY;
    pstInputEvent->evt.stInputCallEvent.bitOpCallIndex = IMSA_OP_TRUE;
    pstInputEvent->evt.stInputCallEvent.ulCallIndex = pstCallEntity->ucImscallId;

    pstInputEvent->evt.stInputCallEvent.bitOpModify = IMSA_OP_TRUE;
    pstInputEvent->evt.stInputCallEvent.stModify.enSrcCallType = pstAppMsg->enCurrCallType;
    pstInputEvent->evt.stInputCallEvent.stModify.enDstCallType = pstAppMsg->enExpectCallType;

    IMSA_SndImsMsgCallEvent(pstInputEvent);

    (VOS_VOID)IMSA_CallImsMsgSave(&pstInputEvent->evt.stInputCallEvent);

    /* ����SPM���� */
    IMSA_CallSpmAnswerRemoteModifyMsgSave(pstAppMsg);

    IMSA_MEM_FREE(pstInputEvent);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallSendImsMsgSrvcc
 Description    : ��IMS����SRVCC����ָʾ
 Input          : enSrvccReason  srvcc�¼�����
 Output         : VOS_VOID
 Return Value   : ������Ϣ���

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallSendImsMsgSrvcc(IMSA_IMS_INPUT_CALL_REASON_ENUM_UINT32 enSrvccReason)
{
    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendImsMsgSrvcc is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendImsMsgSrvcc_ENUM, LNAS_ENTRY);

    pstInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));
    if (VOS_NULL_PTR == pstInputEvent)
    {
        IMSA_ERR_LOG("IMSA_CallSendImsMsgSrvcc: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendImsMsgSrvcc_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET_S( pstInputEvent,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU),
                    0,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_CALL;
    pstInputEvent->evt.stInputCallEvent.ulOpId= IMSA_AllocImsOpId();
    pstInputEvent->evt.stInputCallEvent.enInputCallReason = enSrvccReason;

    IMSA_SndImsMsgCallEvent(pstInputEvent);

    /* srvccͨ��TAF callģ�鷢�𣬲���AT����𣬲���ҪIMS�ظ�ȷ�ϣ�
       ���е���ims����SRVCC����ָʾʱ������Ҫ�ڱ���ims���� */
    /* (VOS_VOID)IMSA_CallImsMsgSave(&pstInputEvent->evt.stInputCallEvent); */

    IMSA_MEM_FREE(pstInputEvent);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallInterruptRedial
 Description    : ����ز����̣���ֹͣ�ز����ʱ����ʱ�����ز������ʱ����
                  ��SPM�ϱ�RELEASED�¼���Я���ز���Ϣ�б���Ĵ���ԭ��ֵ��
                  ������������һ��CALL��������SPM�ϱ�ALL RELEASED�¼���
                  ���CALLʵ����Ϣ��������ز���Ϣ��
 Input          : pstCallEntity------------------CALLʵ��ָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 0015001     2013-12-23  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallInterruptRedial
(
    IMSA_CALL_ENTITY_STRU        *pstCallEntity
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx  = IMSA_CallCtxGet();
    TAF_CS_CAUSE_ENUM_UINT32            enSpmErr    = IMSA_NULL;

    IMSA_INFO_LOG("IMSA_CallInterruptRedial is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallInterruptRedial_ENUM, LNAS_ENTRY);

    /* �����ز������ʱ��ʱ����CALLʵ���е�CALL ID��Ϣ���Ϊ0��
       ������Ҫ���½������ʱ���м�¼��CALLIDд��CALLʵ���У����ܱ�֤�ϱ�
       RELEASD�¼�ʱ��д��CALL ID��ȷ */
    pstCallEntity->ucSpmcallId = (VOS_UINT8)((pstCallCtx->stRedialIntervelTimer.usPara & 0xff00) >> IMSA_MOVEMENT_8);

    /* ֹͣ�ز����ʱ����ʱ�����ز������ʱ�� */
    IMSA_StopTimer(&pstCallCtx->stRedialMaxTimer);
    IMSA_StopTimer(&pstCallCtx->stRedialIntervelTimer);

    /* ��IMS����ԭ��ֵת��ΪSPM����ԭ��ֵ */
    /* �޸ĺ������ */
    enSpmErr = IMSA_CallTransImsErr2SpmErr(&pstCallEntity->stImsError.stErrorCode);

    IMSA_CallReleaseCallCommonProc(pstCallEntity, enSpmErr);
}


/*****************************************************************************
 Function Name  : IMSA_CallImsCmdRel
 Description    : �ͷ��ض�����
 Input          : ulCallId          ���ͷź��е�Id
 Output         : VOS_VOID
 Return Value   : ������Ϣ���

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.wangchen 00209181   2016-02-04 Modify:rel call with cause
*****************************************************************************/
VOS_UINT32 IMSA_CallImsCmdRel
(
    VOS_UINT32                              ulCallId,
    IMSA_IMS_CALL_REL_CAUSE_ENUM_UINT8      enRelCause

)
{
    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallImsCmdRel is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallImsCmdRel_ENUM, LNAS_ENTRY);

    pstInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));
    if (VOS_NULL_PTR == pstInputEvent)
    {
        IMSA_ERR_LOG("IMSA_CallImsCmdRel: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallImsCmdRel_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET_S( pstInputEvent,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU),
                    0,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_CALL;

    pstInputEvent->evt.stInputCallEvent.ulOpId= IMSA_AllocImsOpId();
    pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_RELEASE_AT_X;

    pstInputEvent->evt.stInputCallEvent.bitOpCallIndex = IMSA_OP_TRUE;
    pstInputEvent->evt.stInputCallEvent.ulCallIndex = ulCallId;

    pstInputEvent->evt.stInputCallEvent.enRelCause  = enRelCause;

    IMSA_SndImsMsgCallEvent(pstInputEvent);

    IMSA_MEM_FREE(pstInputEvent);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallImsCmdRelAll
 Description    : �ͷ����к���
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : ������Ϣ���

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallImsCmdRelAll(VOS_VOID)
{
    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallImsCmdRelAll is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallImsCmdRelAll_ENUM, LNAS_ENTRY);

    pstInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));
    if (VOS_NULL_PTR == pstInputEvent)
    {
        IMSA_ERR_LOG("IMSA_CallImsCmdRelAll: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallImsCmdRelAll_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET_S( pstInputEvent,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU),
                    0,
                    sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_CALL;

    pstInputEvent->evt.stInputCallEvent.ulOpId = IMSA_AllocImsOpId();
    pstInputEvent->evt.stInputCallEvent.enInputCallReason = IMSA_IMS_INPUT_CALL_REASON_HANGUP;

    IMSA_SndImsMsgCallEvent(pstInputEvent);

    IMSA_MEM_FREE(pstInputEvent);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallCmdRelAllEmc
 Description    : �ͷ����н�������
 Input          : ucIsUserDisc-------------�Ƿ����û��Ҷ�
 Output         : VOS_VOID
 Return Value   : ������Ϣ���

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-09-29  Modify
      3.lihong 00150010    2013-12-23  Modify:Redail
 Note           :
     1. �˺����ڽ������񲻿���ʱ�����ã����������ֻ��һ�������ǽ�������
     2. ���ﲻ���ͷ�������������������������Ӧ�ò�������յ��˽���������е��޵ı仯ʱ��
        �����������������ĳ���
*****************************************************************************/
VOS_UINT32 IMSA_CallCmdRelAllEmc
(
    VOS_UINT8                           ucIsUserDisc,
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32  enNoSrvCause

)
{
    VOS_UINT32                          i                   = 0;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx          = IMSA_CallCtxGet();
    IMSA_CALL_ENTITY_STRU              *pstCallEntity       = VOS_NULL_PTR;
    VOS_UINT8                           ucRedialCallIndex   = IMSA_NULL;
    TAF_CS_CAUSE_ENUM_UINT32            enSpmErr        = IMSA_NULL;

    IMSA_INFO_LOG("IMSA_CallCmdRelAllEmc is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallCmdRelAllEmc_ENUM, LNAS_ENTRY);

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
            (IMSA_CALL_TYPE_EMC == pstCallCtx->astCallEntity[i].enType))
        {
            if (IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR == enNoSrvCause)
            {
                pstCallCtx->astCallEntity[i].ucSipLostRelCallFlag = VOS_TRUE;
            }
             else if ((IMSA_CALL_NO_SRV_CAUSE_NON_SRVCC_RAT_CHANGE == enNoSrvCause) &&
                      (IMSA_TRUE != IMSA_CallGetSrvccFlag()))
            {
                pstCallCtx->astCallEntity[i].ucNonSrvccRatChgFlag = VOS_TRUE;
            }
            else if (IMSA_CALL_NO_SRV_CAUSE_MEDIA_PDP_RELEASE == enNoSrvCause)
            {
                pstCallCtx->astCallEntity[i].ucMediaLostRelCallFlag = VOS_TRUE;
            }
            else
            {
                pstCallCtx->astCallEntity[i].ucIsImsaRelCallFlag = VOS_TRUE;
            }

            /* �������Tcall��ʱ���������У���Ҫֹͣ */
            if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stEmcTcallTimer))
            {
                IMSA_StopTimer(&pstCallCtx->stEmcTcallTimer);
            }

            /* ���Ҫ�ͷŵ�CALL�������ز�CALL�������ز����� */
            if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stRedialIntervelTimer))
            {
                ucRedialCallIndex = (VOS_UINT8)pstCallCtx->stRedialIntervelTimer.usPara;
                if (i == ucRedialCallIndex)
                {
                    pstCallEntity = &pstCallCtx->astCallEntity[ucRedialCallIndex];
                    #if (FEATURE_ON == FEATURE_PTM)
                    IMSA_CallErrRecord(pstCallEntity->stImsError.stErrorCode.usSipStatusCode, pstCallEntity);
                    IMSA_EmcCallErrRecord(IMSA_CallTransImsaEmcErr2ErrlogInfo(enNoSrvCause),
                                          IMSA_ERR_LOG_EMC_REG_FAIL_REASON_NONE,
                                          IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                          pstCallEntity->stImsError.stErrorCode.usSipStatusCode,
                                          IMSA_FALSE,
                                          IMSA_ERR_LOG_CALL_STATUS_IDLE);
                    #endif
                    IMSA_CallInterruptRedial(pstCallEntity);

                    continue;
                }
            }
            if (IMSA_TRUE == pstCallCtx->ucRetryEmcRegFlag)
            {
                /* ����ǽ������У��յ�#380�����·������ע�ᣬ����ʧ�ܵĳ�������Ҫ֪ͨSPM release�¼� */
                pstCallEntity = &pstCallCtx->astCallEntity[pstCallCtx->ucCallEntityIndex];

                pstCallEntity->ucSpmcallId = pstCallCtx->ucId;
                #if (FEATURE_ON == FEATURE_PTM)
                IMSA_CallErrRecord(pstCallEntity->stImsError.stErrorCode.usSipStatusCode, pstCallEntity);
                IMSA_EmcCallErrRecord(IMSA_CallTransImsaEmcErr2ErrlogInfo(enNoSrvCause),
                                          IMSA_ERR_LOG_EMC_REG_FAIL_REASON_NONE,
                                          IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                          pstCallEntity->stImsError.stErrorCode.usSipStatusCode,
                                          IMSA_FALSE,
                                          IMSA_ERR_LOG_CALL_STATUS_IDLE);
                #endif
                /* ��IMS����ԭ��ֵת��ΪSPM����ԭ��ֵ */
                /* �޸ĺ������ */
                enSpmErr = IMSA_CallTransImsErr2SpmErr(&pstCallEntity->stImsError.stErrorCode);

                IMSA_CallReleaseCallCommonProc(pstCallEntity, enSpmErr);

                /* ����������ע���ʶ�Ȳ��� */
                pstCallCtx->ucRetryEmcRegFlag = IMSA_FALSE;
                pstCallCtx->ucId = IMSA_NULL;
                pstCallCtx->ucCallEntityIndex = IMSA_NULL;
                continue;
            }

            /* ֻ�н���Ϣ���͸�IMS�����յ�IMS�ϱ���callid�󣬲���Ҫ��IMS�����ͷ����� */
            if (IMSA_CALL_INVALID_ID !=pstCallCtx->astCallEntity[i].ucImscallId)
            {
                IMSA_CallUpdateDiscCallDir( (VOS_UINT32)pstCallCtx->astCallEntity[i].ucSpmcallId,
                                            ucIsUserDisc);

                (VOS_VOID)IMSA_CallImsCmdRel(pstCallCtx->astCallEntity[i].ucImscallId,
                                                IMSA_CallTransImsaErr2ImsInfo(enNoSrvCause));

                #if (FEATURE_ON == FEATURE_PTM)
                IMSA_CallErrRecord(IMSA_ERR_LOG_CALL_FAIL_REASON_SERVICE_NOT_AVAILABLE, &pstCallCtx->astCallEntity[i]);
                IMSA_EmcCallErrRecord(IMSA_CallTransImsaEmcErr2ErrlogInfo(enNoSrvCause),
                                          IMSA_ERR_LOG_EMC_REG_FAIL_REASON_NONE,
                                          IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                          pstCallCtx->astCallEntity[i].stImsError.stErrorCode.usSipStatusCode,
                                          IMSA_FALSE,
                                          IMSA_ERR_LOG_CALL_STATUS_IDLE);
                #endif
            }

        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallCmdRelAllNormal
 Description    : �ͷ�������ͨ��������
 Input          : ucIsUserDisc-------------�Ƿ����û��Ҷ�
 Output         : VOS_VOID
 Return Value   : ������Ϣ���

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-09-29  Modify
      3.lihong 00150010    2013-12-23  Modify:Redail
      4.wangchen 00209181  2016-01-09  Modify:CHR
 NOTE           :
     1. �˺������������񲻿���ʱ������
*****************************************************************************/
VOS_UINT32 IMSA_CallCmdRelAllNormal
(
    VOS_UINT8                           ucIsUserDisc,
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32  enNoSrvCause
)
{
    VOS_UINT32                          i                   = 0;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx          = IMSA_CallCtxGet();
    IMSA_CALL_ENTITY_STRU              *pstCallEntity       = VOS_NULL_PTR;
    VOS_UINT8                           ucRedialCallIndex   = IMSA_NULL;

    IMSA_INFO_LOG("IMSA_CallCmdRelAllNormal is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallCmdRelAllNormal_ENUM, LNAS_ENTRY);

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
            ((IMSA_CALL_TYPE_EMC != pstCallCtx->astCallEntity[i].enType) ||
            ((IMSA_CALL_TYPE_EMC == pstCallCtx->astCallEntity[i].enType) &&
            (IMSA_EMC_CALL_TYPE_IN_NORMAL_SRV == pstCallCtx->astCallEntity[i].enEmcType))))
        {
            if (IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR == enNoSrvCause)
            {
                pstCallCtx->astCallEntity[i].ucSipLostRelCallFlag = VOS_TRUE;
            }
            else if (IMSA_CALL_NO_SRV_CAUSE_NON_SRVCC_RAT_CHANGE == enNoSrvCause)
            {
                pstCallCtx->astCallEntity[i].ucNonSrvccRatChgFlag = VOS_TRUE;
            }
            else if (IMSA_CALL_NO_SRV_CAUSE_MEDIA_PDP_RELEASE == enNoSrvCause)
            {
                pstCallCtx->astCallEntity[i].ucMediaLostRelCallFlag = VOS_TRUE;
            }
            else
            {
                pstCallCtx->astCallEntity[i].ucIsImsaRelCallFlag = VOS_TRUE;
            }

            /* ���Ҫ�ͷŵ�CALL�������ز�CALL�������ز����� */
            if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stRedialIntervelTimer))
            {
                ucRedialCallIndex = (VOS_UINT8)pstCallCtx->stRedialIntervelTimer.usPara;
                if (i == ucRedialCallIndex)
                {
                    pstCallEntity = &pstCallCtx->astCallEntity[ucRedialCallIndex];
                    #if (FEATURE_ON == FEATURE_PTM)
                    IMSA_CallErrRecord(pstCallEntity->stImsError.stErrorCode.usSipStatusCode, pstCallEntity);
                    IMSA_NormCallErrRecord(IMSA_CallTransImsaErr2ErrlogInfo(enNoSrvCause),
                                            pstCallEntity,
                                            pstCallEntity->stImsError.stErrorCode.usSipStatusCode);
                    #endif
                    IMSA_CallInterruptRedial(pstCallEntity);

                    continue;
                }
            }
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_CallErrRecord(IMSA_ERR_LOG_CALL_FAIL_REASON_SERVICE_NOT_AVAILABLE, &pstCallCtx->astCallEntity[i]);
            IMSA_NormCallErrRecord(IMSA_CallTransImsaErr2ErrlogInfo(enNoSrvCause),
                                    &pstCallCtx->astCallEntity[i],
                                    pstCallCtx->astCallEntity[i].stImsError.stErrorCode.usSipStatusCode);
            #endif
            IMSA_CallUpdateDiscCallDir( (VOS_UINT32)pstCallCtx->astCallEntity[i].ucSpmcallId,
                                        ucIsUserDisc);

            (VOS_VOID)IMSA_CallImsCmdRel(pstCallCtx->astCallEntity[i].ucImscallId,
                                         IMSA_CallTransImsaErr2ImsInfo(enNoSrvCause));
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallSendIntraResultAction
 Description    : ����ʧ�ܺ󣬸�Serviceģ�鷢�͵ĺ�������ָʾ
 Input          : enCallType    ��������
                  enAction      Service����Ҫ��Ҫ���Ĵ���
 Output         : VOS_VOID
 Return Value   : ���ͽ��

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallSendIntraResultAction(IMSA_CALL_TYPE_ENUM_UINT8 enCallType,
                                          IMSA_RESULT_ACTION_ENUM_UINT32 enAction)
{
    IMSA_CALL_RESULT_ACTION_IND_STRU stAction = {0};

    IMSA_INFO_LOG("IMSA_CallSendIntraResultAction is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendIntraResultAction_ENUM, LNAS_ENTRY);

    stAction.enCallType     = enCallType;
    stAction.enResultAction = enAction;

    return IMSA_RegSendIntraMsg(ID_IMSA_CALL_RESULT_ACTION_IND, (VOS_UINT8 *)&stAction, sizeof(IMSA_CALL_RESULT_ACTION_IND_STRU));
}

/*****************************************************************************
 Function Name  : IMSA_CallSendIntraSrvccSucc
 Description    : SRVCC�ɹ��󣬸�Serviceģ�鷢�͵�ָʾ����ʹSERVICEģ���TAF��ȥע��״̬
 Input          : enCallType    ��������
 Output         : VOS_VOID
 Return Value   : ���ͽ��

 History        :
      1.zhaochen  00308719      2015-12-24  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallSendIntraSrvccSucc(VOS_VOID)
{
    IMSA_CALL_SRVCC_SUCC_IND_STRU stSrvccSuccInd = {0};


    return IMSA_RegSendIntraMsg( ID_IMSA_CALL_SRVCC_SUCC_IND,
                                (VOS_UINT8 *)&stSrvccSuccInd,
                                 sizeof(IMSA_CALL_SRVCC_SUCC_IND_STRU));
}

/*****************************************************************************
 Function Name  : IMSA_CallSendSpmEventMsg
 Description    : ����ģ���SPM���͵Ļظ���Ϣ
 Input          : pEvtData        ����ظ���ʱ�估��ϸ����
                  ulLen           ����ʱ�估��ϸ���ݵĳ���
 Output         : VOS_VOID
 Return Value   : ���ͽ��

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-09-29  Modify
*****************************************************************************/
VOS_UINT32 IMSA_CallSendSpmEventMsg(
                                    const VOS_VOID  *pEvtData,
                                    VOS_UINT16 usLen)
{
    IMSA_SPM_CALL_MSG_STRU *pstSpmCallMsg = VOS_NULL_PTR;
    VOS_UINT32 ulMsgLen = 0;

    IMSA_INFO_LOG("IMSA_CallSendSpmEventMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmEventMsg_ENUM, LNAS_ENTRY);

    ulMsgLen = ((sizeof(IMSA_SPM_CALL_MSG_STRU) + usLen) - sizeof(MN_CALL_INFO_STRU)) - sizeof(MN_CALL_EVENT_ENUM_UINT32);

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstSpmCallMsg = (VOS_VOID*)IMSA_ALLOC_MSG(ulMsgLen);
    if (VOS_NULL_PTR == pstSpmCallMsg)
    {
        IMSA_ERR_LOG("IMSA_CallSendSpmEventMsg: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendSpmEventMsg_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    /* ��� */
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstSpmCallMsg),
                    IMSA_GET_MSG_LENGTH(pstSpmCallMsg),
                    0,
                    IMSA_GET_MSG_LENGTH(pstSpmCallMsg));

    /* ��д��Ϣͷ */
    IMSA_WRITE_SPM_MSG_HEAD(pstSpmCallMsg, ID_IMSA_SPM_CALL_MSG);

    /* ����Client Id����GU��ͨ�������Χ��CLIENT IDд���ɹ㲥*/
    pstSpmCallMsg->usClientId = MN_CLIENT_ALL;

    /* ������Ϣ���ݼ����� */
    pstSpmCallMsg->usLen = usLen;
    IMSA_MEM_CPY_S( (VOS_UINT8 *)&pstSpmCallMsg->enEventType,
                    pstSpmCallMsg->usLen,
                    pEvtData,
                    pstSpmCallMsg->usLen);

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstSpmCallMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallSendSpmEvtAndCallInfo
 Description    : IMSA��SPM�ظ��ķ�����н��
 Input          : enAction      Service����Ҫ��Ҫ���Ĵ���
 Output         : VOS_VOID
 Return Value   : ���ͽ��

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-09-29  Modify
      3.wangchen 00209181   2014-12-01  Modify:DTS2014112906255
*****************************************************************************/
VOS_UINT32 IMSA_CallSendSpmEvtAndCallInfo(VOS_UINT16 usClientId,
                                          VOS_UINT32 ulOpId,
                                          VOS_UINT32 ulCallId,
                                          MN_CALL_EVENT_ENUM_UINT32 enEvt,
                                          TAF_CS_CAUSE_ENUM_UINT32 ulResult)
{
    IMSA_CALL_ENTITY_STRU *pstCallEntity = VOS_NULL_PTR;
    MN_CALL_EVT_ORIG_CNF_STRU stOrigCnf = {0};

    IMSA_INFO_LOG("IMSA_CallSendSpmEvtAndCallInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmEvtAndCallInfo_ENUM, LNAS_ENTRY);

    /* �����¼����� */
    stOrigCnf.enEventType = enEvt;

    /* ����MN_CALL_INFO_STRU�е�call id�ȹ�����Ϣ */
    stOrigCnf.stCallInfo.opId     = (MN_OPERATION_ID_T)ulOpId;
    stOrigCnf.stCallInfo.clientId = usClientId;

    /* ���������� */
    stOrigCnf.stCallInfo.enCause  = ulResult;

    stOrigCnf.stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_IMS;

    /**
     * �����Call Id��Ӧ�ĺ���ʵ����ڣ������IMSA����ʵ���������ظ�����е�stCallInfo��
     * �������ʵ�岻���ڣ���IMSAֻ��֤������op id, client id�������Ч
     */
    pstCallEntity = IMSA_CallEntityGetUsedBySpmCallId(ulCallId);
    if (pstCallEntity)
    {
        IMSA_CallEntity2SpmCallInfo(pstCallEntity, enEvt, &stOrigCnf.stCallInfo);
    }

    IMSA_INFO_LOG1("IMSA_CallSendSpmEvtAndCallInfo: MptyState", stOrigCnf.stCallInfo.enMptyState);
    TLPS_PRINT2LAYER_INFO1(IMSA_CallSendSpmEvtAndCallInfo_ENUM, 1, stOrigCnf.stCallInfo.enMptyState);

    /* ���÷��ͺ��� */
    return IMSA_CallSendSpmEventMsg((VOS_VOID *)&stOrigCnf,
                                    sizeof(MN_CALL_EVT_ORIG_CNF_STRU));
}

/*****************************************************************************
 Function Name  : IMSA_CallSendSpmReleasedEvt
 Description    : IMSA��SPM����RELEASED�¼�
 Input          : pstCallEntity-----------CALLʵ����Ϣ
                  ulResult----------------ԭ��ֵ
 Output         : VOS_VOID
 Return Value   : ���ͽ��

 History        :
      1.lihong 00150010     2013-09-29  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallSendSpmReleasedEvt
(
    const IMSA_CALL_ENTITY_STRU        *pstCallEntity,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
)
{
    MN_CALL_EVT_ORIG_CNF_STRU stOrigCnf = {0};

    IMSA_INFO_LOG("IMSA_CallSendSpmReleasedEvt is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmReleasedEvt_ENUM, LNAS_ENTRY);

    /* �����¼����� */
    stOrigCnf.enEventType = MN_CALL_EVT_RELEASED;

    /* ����MN_CALL_INFO_STRU�е�call id�ȹ�����Ϣ */
    stOrigCnf.stCallInfo.callId   = (MN_CALL_ID_T)pstCallEntity->ucSpmcallId;

    stOrigCnf.stCallInfo.opId     = (MN_OPERATION_ID_T)pstCallEntity->ulOpId;
    stOrigCnf.stCallInfo.clientId = pstCallEntity->usClientId;

    /* ���������� */
    stOrigCnf.stCallInfo.enCause  = ulResult;

    stOrigCnf.stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_IMS;

    IMSA_CallEntity2SpmCallInfo(pstCallEntity, MN_CALL_EVT_RELEASED, &stOrigCnf.stCallInfo);

    /* ���÷��ͺ��� */
    return IMSA_CallSendSpmEventMsg((VOS_VOID *)&stOrigCnf,
                                    sizeof(MN_CALL_EVT_ORIG_CNF_STRU));
}
/*****************************************************************************
 Function Name  : IMSA_CallSendSpmSsNotifyEvt
 Description    : IMSA��SPM����SsNotify�¼�
 Input          : pstCallEntity-----------CALLʵ����Ϣ
                  ulResult----------------ԭ��ֵ
 Output         : VOS_VOID
 Return Value   : ���ͽ��

 History        :
      1.wangchen 00209181   2013-12-27  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallSendSpmSsNotifyEvt
(
    VOS_UINT16 usClientId,
    VOS_UINT32 ulOpId,
    VOS_UINT32 ulCallId,
    MN_CALL_EVENT_ENUM_UINT32 enEvt,
    TAF_CS_CAUSE_ENUM_UINT32 ulResult,
    MN_CALL_SS_NOTIFY_CODE_ENUM_U8 enCode
)
{
    MN_CALL_EVT_ORIG_CNF_STRU stOrigCnf = {0};

    IMSA_INFO_LOG("IMSA_CallSendSpmSsNotifyEvt is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmSsNotifyEvt_ENUM, LNAS_ENTRY);

    /* �����¼����� */
    stOrigCnf.enEventType = enEvt;

    /* ����MN_CALL_INFO_STRU�е�call id�ȹ�����Ϣ */
    stOrigCnf.stCallInfo.callId   = (MN_CALL_ID_T)ulCallId;
    stOrigCnf.stCallInfo.opId     = (MN_OPERATION_ID_T)ulOpId;
    stOrigCnf.stCallInfo.clientId = usClientId;

    /* ���������� */
    stOrigCnf.stCallInfo.enCause  = ulResult;

    stOrigCnf.stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_IMS;

    stOrigCnf.stCallInfo.stSsNotify.enCode = enCode;

    /* ���÷��ͺ��� */
    return IMSA_CallSendSpmEventMsg((VOS_VOID *)&stOrigCnf,
                                    sizeof(MN_CALL_EVT_ORIG_CNF_STRU));
}

/*****************************************************************************
 Function Name  : IMSA_CallSendSpmAllReleasedEvt
 Description    : IMSA��SPM����ALL RELEASED�¼�
 Input          : pstCallEntity-----------CALLʵ����Ϣ
                  ulResult----------------ԭ��ֵ
 Output         : VOS_VOID
 Return Value   : ���ͽ��

 History        :
      1.lihong 00150010     2013-09-29  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallSendSpmAllReleasedEvt( VOS_VOID )
{
    MN_CALL_EVT_ORIG_CNF_STRU stOrigCnf = {0};

    IMSA_INFO_LOG("IMSA_CallSendSpmAllReleasedEvt is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmAllReleasedEvt_ENUM, LNAS_ENTRY);

    if (IMSA_TRUE ==IMSA_CallGetNotReportAllReleasedFlag())
    {
        /* ɾ���Ա�־���жϣ������Ҫ���漰���ñ�־�ĵ��ö�ɾ�� */
        IMSA_CallSetNotReportAllReleasedFlag(IMSA_FALSE);
    }

    /* �����¼����� */
    stOrigCnf.enEventType = MN_CALL_EVT_ALL_RELEASED;

    stOrigCnf.stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_IMS;

    /* ���÷��ͺ��� */
    return IMSA_CallSendSpmEventMsg((VOS_VOID *)&stOrigCnf,
                                    sizeof(MN_CALL_EVT_ORIG_CNF_STRU));
}

/*****************************************************************************
 Function Name  : IMSA_CallSendSpmStartDtmfRsltMsg
 Description    : IMSA��SPM�ظ���Start dtmf ���ս��
 Input          : usClientId--------------CLIENT ID
                  ucOpId------------------OPID
                  ucCallId----------------CALL ID
                  ulResult----------------���
 Output         : VOS_VOID
 Return Value   : ���ͽ��

 History        :
      1.lihong 00150010      2013-10-14  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallSendSpmStartDtmfRsltMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
)
{
    IMSA_SPM_CALL_START_DTMF_RSLT_IND_STRU   *pstStartDtmfRsltInd = VOS_NULL_PTR;

    (VOS_VOID)ucCallId;

    IMSA_INFO_LOG("IMSA_CallSendSpmStartDtmfRsltMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmStartDtmfRsltMsg_ENUM, LNAS_ENTRY);

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstStartDtmfRsltInd = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_SPM_CALL_START_DTMF_RSLT_IND_STRU));
    if (VOS_NULL_PTR == pstStartDtmfRsltInd)
    {
        IMSA_ERR_LOG("IMSA_CallSendSpmStartDtmfRsltMsg: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendSpmStartDtmfRsltMsg_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    /* ��� */
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstStartDtmfRsltInd),
                    IMSA_GET_MSG_LENGTH(pstStartDtmfRsltInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstStartDtmfRsltInd));

    /* ��д��Ϣͷ */
    IMSA_WRITE_SPM_MSG_HEAD(pstStartDtmfRsltInd, ID_IMSA_SPM_CALL_START_DTMF_RSLT_IND);

    pstStartDtmfRsltInd->usClientId = usClientId;
    pstStartDtmfRsltInd->ucOpId     = ucOpId;
    pstStartDtmfRsltInd->enCause    = ulResult;

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstStartDtmfRsltInd);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallSendSpmStopDtmfRsltMsg
 Description    : IMSA��SPM�ظ���Stop dtmf ���ս��
 Input          : usClientId--------------CLIENT ID
                  ucOpId------------------OPID
                  ucCallId----------------CALL ID
                  ulResult----------------���
 Output         : VOS_VOID
 Return Value   : ���ͽ��

 History        :
      1.lihong 00150010      2013-10-14  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallSendSpmStopDtmfRsltMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            ulResult
)
{
    IMSA_SPM_CALL_STOP_DTMF_RSLT_IND_STRU   *pstStopDtmfRsltInd = VOS_NULL_PTR;

    (VOS_VOID)ucCallId;

    IMSA_INFO_LOG("IMSA_CallSendSpmStopDtmfRsltMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmStopDtmfRsltMsg_ENUM, LNAS_ENTRY);

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstStopDtmfRsltInd = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_SPM_CALL_STOP_DTMF_RSLT_IND_STRU));
    if (VOS_NULL_PTR == pstStopDtmfRsltInd)
    {
        IMSA_ERR_LOG("IMSA_CallSendSpmStopDtmfRsltMsg: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendSpmStopDtmfRsltMsg_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    /* ��� */
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstStopDtmfRsltInd),
                    IMSA_GET_MSG_LENGTH(pstStopDtmfRsltInd),
                    0,
                    IMSA_GET_MSG_LENGTH(pstStopDtmfRsltInd));

    /* ��д��Ϣͷ */
    IMSA_WRITE_SPM_MSG_HEAD(pstStopDtmfRsltInd, ID_IMSA_SPM_CALL_STOP_DTMF_RSLT_IND);

    pstStopDtmfRsltInd->usClientId = usClientId;
    pstStopDtmfRsltInd->ucOpId     = ucOpId;
    pstStopDtmfRsltInd->enCause    = ulResult;

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstStopDtmfRsltInd);

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallSendSpmSupsResultMsg
 Description    : IMSA��SPM�ظ�����ֵ�������ս��
 Input          : usClientId--------------CLIENT ID
                  ulOpId------------------OPID
                  ulCallId----------------CALL ID
                  ulResult----------------���
 Output         : VOS_VOID
 Return Value   : ���ͽ��

 History        :
      1.lihong 00150010      2013-09-12  Draft Enact
      2.lihong 00150010      2013-09-29  Modify
*****************************************************************************/
VOS_UINT32 IMSA_CallSendSpmSupsResultMsg
(
    VOS_UINT16                          usClientId,
    VOS_UINT32                          ulOpId,
    VOS_UINT32                          ulCallId,
    MN_CALL_SS_RESULT_ENUM_U8           enSsResult
)
{
    IMSA_CALL_ENTITY_STRU              *pstCallEntity   = VOS_NULL_PTR;
    MN_CALL_EVT_ORIG_CNF_STRU           stOrigCnf       = {0};

    IMSA_INFO_LOG("IMSA_CallSendSpmSupsResultMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmSupsResultMsg_ENUM, LNAS_ENTRY);

    /* �����¼����� */
    stOrigCnf.enEventType = MN_CALL_EVT_SS_CMD_RSLT;

    /* ����MN_CALL_INFO_STRU�е�call id�ȹ�����Ϣ */
    stOrigCnf.stCallInfo.callId   = (MN_CALL_ID_T)ulCallId;
    stOrigCnf.stCallInfo.opId     = (MN_OPERATION_ID_T)ulOpId;
    stOrigCnf.stCallInfo.clientId = usClientId;

    /* ���������� */
    stOrigCnf.stCallInfo.enSsResult = enSsResult;

    stOrigCnf.stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_IMS;

    /**
     * �����Call Id��Ӧ�ĺ���ʵ����ڣ������IMSA����ʵ���������ظ�����е�stCallInfo��
     * �������ʵ�岻���ڣ���IMSAֻ��֤������op id, client id�������Ч
     */
    pstCallEntity = IMSA_CallEntityGetUsedBySpmCallId(ulCallId);

    if (pstCallEntity)
    {
        IMSA_CallEntity2SpmCallInfo(pstCallEntity, MN_CALL_EVT_SS_CMD_RSLT, &stOrigCnf.stCallInfo);
    }

    /* ���÷��ͺ��� */
    return IMSA_CallSendSpmEventMsg((VOS_VOID *)&stOrigCnf,
                                    sizeof(MN_CALL_EVT_ORIG_CNF_STRU));
}


VOS_UINT32 IMSA_CallSendSpmStateEvt(VOS_UINT32 ulCallId,VOS_UINT16 usClientId,
                                          VOS_UINT32 ulOpId, MN_CALL_EVENT_ENUM_UINT32 enEvt)
{
    IMSA_INFO_LOG("IMSA_CallSendSpmStateEvt is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmStateEvt_ENUM, LNAS_ENTRY);

    return IMSA_CallSendSpmEvtAndCallInfo(usClientId,
                                          ulOpId,
                                          ulCallId,
                                          enEvt,
                                          TAF_CS_CAUSE_SUCCESS);
}

/*****************************************************************************
 Function Name  : IMSA_CallSendSpmLocalAlertingInd
 Description    : IMSA��SPM���ͱ�������֪ͨ
 Input          : ulClientId      SPM�����·�ʱЯ����Client id
                  ulCallId        �ú��ж�Ӧ��id
                  ucIsLocalAlerting  �Ƿ񱾵������ʶ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-29  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallSendSpmLocalAlertingInd(VOS_UINT16 usClientId,
                                            VOS_UINT8 ucIsLocalAlerting)
{
    IMSA_SPM_CHANNEL_INFO_IND_STRU *pstSpmChannelInfoMsg = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallSendSpmLocalAlertingInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmLocalAlertingInd_ENUM, LNAS_ENTRY);

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstSpmChannelInfoMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_SPM_CHANNEL_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstSpmChannelInfoMsg)
    {
        IMSA_ERR_LOG("IMSA_CallSendSpmLocalAlertingInd: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendSpmLocalAlertingInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstSpmChannelInfoMsg),
                    IMSA_GET_MSG_LENGTH(pstSpmChannelInfoMsg),
                    0,
                    IMSA_GET_MSG_LENGTH(pstSpmChannelInfoMsg));

    /* ��д��Ϣͷ */
    IMSA_WRITE_SPM_MSG_HEAD(pstSpmChannelInfoMsg, ID_IMSA_SPM_CHANNEL_INFO_IND);

    /* ����Client Id */
    pstSpmChannelInfoMsg->usClientId = usClientId;
    /* pstSpmChannelInfoMsg->enChannelEvent = MN_CALL_EVT_CHANNEL_LOCAL_ALERTING; */
    pstSpmChannelInfoMsg->ucIsLocalAlertingFlag = ucIsLocalAlerting;

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstSpmChannelInfoMsg);
}

/*****************************************************************************
 Function Name  : IMSA_CallSendSpmEconfNotifyInd
 Description    : IMSA��SPM������ǿ�෽ͨ����notigy
 Input          :
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2014-12-13 Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallSendSpmEconfNotifyInd
(
    IMSA_CALL_ENTITY_STRU* pstCallEntity
)
{
    IMSA_SPM_CALL_ECONF_NOTIFY_IND_STRU *pstSpmEconfNotifyIndMsg = VOS_NULL_PTR;
    TAF_CS_CAUSE_ENUM_UINT32            enSpmErr        = IMSA_NULL;
    VOS_UINT8                           i = 0;

    IMSA_INFO_LOG("IMSA_CallSendSpmEconfNotifyInd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSendSpmEconfNotifyInd_ENUM, LNAS_ENTRY);

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstSpmEconfNotifyIndMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_SPM_CALL_ECONF_NOTIFY_IND_STRU));
    if (VOS_NULL_PTR == pstSpmEconfNotifyIndMsg)
    {
        IMSA_ERR_LOG("IMSA_CallSendSpmEconfNotifyInd: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSendSpmEconfNotifyInd_ENUM, LNAS_NULL_PTR);
        return ;
    }

    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstSpmEconfNotifyIndMsg),
                    IMSA_GET_MSG_LENGTH(pstSpmEconfNotifyIndMsg),
                    0,
                    IMSA_GET_MSG_LENGTH(pstSpmEconfNotifyIndMsg));

    /* ��д��Ϣͷ */
    IMSA_WRITE_SPM_MSG_HEAD(pstSpmEconfNotifyIndMsg, ID_IMSA_SPM_CALL_ECONF_NOTIFY_IND);

    pstSpmEconfNotifyIndMsg->usClientId = MN_CLIENT_ALL;
    pstSpmEconfNotifyIndMsg->ucOpId = 0;

    pstSpmEconfNotifyIndMsg->ucNumOfCalls = pstCallEntity->ucCurUserNum;

    for (i = 0; i < pstCallEntity->ucCurUserNum; i ++)
    {
        /* ���������״̬ */
        pstSpmEconfNotifyIndMsg->astCallInfo[i].enCallState = IMSA_EconfImsState2CsState( pstCallEntity->stEconfCalllist[i].enCallState);

        /* ��������ߺ��� */
        IMSA_CallCalledNumberImsa2CS(&pstCallEntity->stEconfCalllist[i].stCalledNumber, &pstSpmEconfNotifyIndMsg->astCallInfo[i].stCallNumber);

        /* ����display name */
        IMSA_MEM_CPY_S( pstSpmEconfNotifyIndMsg->astCallInfo[i].aucDisplaytext,
                        TAF_IMSA_ALPHA_STRING_SZ,
                        pstCallEntity->stEconfCalllist[i].acAlpha,
                        TAF_IMSA_ALPHA_STRING_SZ);

        /* ����ԭ��ֵ */
        if (IMSA_OP_TRUE == pstCallEntity->stEconfCalllist[i].bitOpErrorInfo)
        {
            /* ��IMS����ԭ��ֵת��ΪSPM����ԭ��ֵ */
            /* �޸ĺ������ */
            enSpmErr = IMSA_CallTransImsErr2SpmErr(&pstCallEntity->stEconfCalllist[i].stErrorCode);

            pstSpmEconfNotifyIndMsg->astCallInfo[i].enCause = enSpmErr;
        }
        else
        {
            pstSpmEconfNotifyIndMsg->astCallInfo[i].enCause = TAF_CS_CAUSE_SUCCESS;
        }

    }

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstSpmEconfNotifyIndMsg);
}


VOS_VOID IMSA_CallEntityUpdateCalledNumber(const MN_CALL_CALLED_NUM_STRU *pstSrcNumber,
                                           IMSA_CALLED_NUMBER_STRU *pstDstNumber)
{
    IMSA_INFO_LOG("IMSA_CallEntityUpdateCalledNumber is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallEntityUpdateCalledNumber_ENUM, LNAS_ENTRY);

    if ((VOS_NULL_PTR == pstSrcNumber) ||
        (VOS_NULL_PTR == pstDstNumber))
    {
        IMSA_INFO_LOG("IMSA_CallEntityUpdateCalledNumber: null pointer");
        TLPS_PRINT2LAYER_INFO(IMSA_CallEntityUpdateCalledNumber_ENUM, LNAS_NULL_PTR);
        return;
    }

    /* ���º������� */
    if (MN_CALL_TON_INTERNATIONAL == (0x07 & (pstDstNumber->enNumType >> 4)))
    {
        pstDstNumber->enNumType = IMSA_CALL_NUM_INTERNATIONAL;
    }
    else
    {
        pstDstNumber->enNumType = IMSA_CALL_NUM_NATIONAL;
    }

    /* ���º������ݣ����ת��ʧ�ܣ������ַ�������Ϊ0 */

    IMSA_MEM_SET_S( pstDstNumber->aucNumber,
                    sizeof(pstDstNumber->aucNumber),
                    0,
                    sizeof(pstDstNumber->aucNumber));

    /*IMSA_MEM_SET_S(pstDstNumber->aucNumber, 0, IMSA_CALLED_NUMBER_MAX_NUM);*/
    if (VOS_FALSE == IMSA_UtilBcdNumberToAscii(pstSrcNumber->aucBcdNum, pstSrcNumber->ucNumLen, pstDstNumber->aucNumber))
    {
        pstDstNumber->aucNumber[0] = 0;
    }
}

/*****************************************************************************
 Function Name  : IMSA_CallEntityUpdateCallNumberByAscii
 Description    : ʹ��D2�ϱ��ĺ����ִ��������к���
 Input          : pcAddress      D2�ϱ��ĺ����ִ�
 Output         : pstDstNumber   ���к���
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-08-05  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallEntityUpdateCallNumberByAscii(const VOS_CHAR *pcAddress,
                                                IMSA_CALL_NUMBER_STRU *pstDstNumber)
{
    IMSA_INFO_LOG("IMSA_CallEntityUpdateCallNumberByAscii is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallEntityUpdateCallNumberByAscii_ENUM, LNAS_ENTRY);

    if ((VOS_NULL_PTR == pcAddress) ||
        (VOS_NULL_PTR == pstDstNumber))
    {
        IMSA_INFO_LOG("IMSA_CallEntityUpdateCallNumberByAscii: null pointer");
        TLPS_PRINT2LAYER_INFO(IMSA_CallEntityUpdateCallNumberByAscii_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET_S( pstDstNumber->aucNumber,
                    sizeof(pstDstNumber->aucNumber),
                    0,
                    sizeof(pstDstNumber->aucNumber));

    /* ���º������� */
    if ('+' == pcAddress[0])
    {
        pstDstNumber->enNumType = IMSA_CALL_NUM_INTERNATIONAL;

        /*ȥ��'+'*/
        IMSA_UtilStrNCpy(pstDstNumber->aucNumber, &pcAddress[1], IMSA_CALL_NUMBER_MAX_NUM);
    }
    else
    {
        pstDstNumber->enNumType = IMSA_CALL_NUM_NATIONAL;

        IMSA_UtilStrNCpy(pstDstNumber->aucNumber, pcAddress, IMSA_CALL_NUMBER_MAX_NUM);
    }
}

/*****************************************************************************
 Function Name  : IMSA_CallEntityUpdateCalledNumberByAscii
 Description    : ʹ��IMS�ϱ��ĺ����ִ����±��к���
 Input          : pcAddress      D2�ϱ��ĺ����ִ�
 Output         : pstDstNumber   ���к���
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-08-05  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallEntityUpdateCalledNumberByAscii(const VOS_CHAR *pcAddress,
                                                  IMSA_CALLED_NUMBER_STRU *pstDstNumber)
{
    IMSA_INFO_LOG("IMSA_CallEntityUpdateCalledNumberByAscii is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallEntityUpdateCalledNumberByAscii_ENUM, LNAS_ENTRY);

    if ((VOS_NULL_PTR == pcAddress) ||
        (VOS_NULL_PTR == pstDstNumber))
    {
        IMSA_INFO_LOG("IMSA_CallEntityUpdateCalledNumberByAscii: null pointer");
        TLPS_PRINT2LAYER_INFO(IMSA_CallEntityUpdateCalledNumberByAscii_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET_S( pstDstNumber->aucNumber,
                    sizeof(pstDstNumber->aucNumber),
                    0,
                    sizeof(pstDstNumber->aucNumber));

    /* ���º������ͺ����� */
    if ('+' == pcAddress[0])
    {
        pstDstNumber->enNumType = IMSA_CALL_NUM_INTERNATIONAL;

        /*ȥ��'+'*/
        IMSA_UtilStrNCpy(pstDstNumber->aucNumber, &pcAddress[1], IMSA_CALLED_NUMBER_MAX_NUM);
    }
    else
    {
        pstDstNumber->enNumType = IMSA_CALL_NUM_NATIONAL;

        IMSA_UtilStrNCpy(pstDstNumber->aucNumber, pcAddress, IMSA_CALLED_NUMBER_MAX_NUM);
    }
}

/*****************************************************************************
 Function Name  : IMSA_CallEntityUpdateCalledNumberByBcd
 Description    : ʹ��SPM ORIG REQ��Ϣ�еı��к�����±��к���
 Input          : pcAddress      D2�ϱ��ĺ����ִ�
 Output         : pstDstNumber   ���к���
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2014-12-16  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallEntityUpdateCalledNumberByBcd
(
    MN_CALL_CALLED_NUM_STRU            *pstDialNumber,
    IMSA_CALLED_NUMBER_STRU              *pstCalledNumber
)
{
    IMSA_INFO_LOG("IMSA_CallEntityUpdateCalledNumberByBcd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallEntityUpdateCalledNumberByBcd_ENUM, LNAS_ENTRY);

    if ((VOS_NULL_PTR == pstDialNumber) ||
        (VOS_NULL_PTR == pstCalledNumber))
    {
        IMSA_INFO_LOG("IMSA_CallEntityUpdateCalledNumberByBcd: null pointer");
        TLPS_PRINT2LAYER_INFO(IMSA_CallEntityUpdateCalledNumberByBcd_ENUM, LNAS_NULL_PTR);
        return;
    }

    if (MN_CALL_TON_INTERNATIONAL == (((pstDialNumber->enNumType)>>4)&0x7))
    {
        pstCalledNumber->enNumType = IMSA_CALL_NUM_INTERNATIONAL;
        (VOS_VOID)IMSA_UtilBcdNumberToAscii(pstDialNumber->aucBcdNum,
                                  pstDialNumber->ucNumLen,
                                  pstCalledNumber->aucNumber);

    }
    else
    {
        pstCalledNumber->enNumType = IMSA_CALL_NUM_NATIONAL;
        (VOS_VOID)IMSA_UtilBcdNumberToAscii(pstDialNumber->aucBcdNum,
                                  pstDialNumber->ucNumLen,
                                  pstCalledNumber->aucNumber);
    }
}


/*****************************************************************************
 Function Name  : IMSA_CallImsaNumType2SpmNumType
 Description    : IMSA�������͵�SPM�������͵�ת��
 Input          : enNumType      IMSA����ĺ�������
 Output         : VOS_VOID
 Return Value   : SPM����ĺ�������

 History        :
      1.liuhua 212067      2013-08-05  Draft Enact
*****************************************************************************/
MN_CALL_NUM_TYPE_ENUM_U8 IMSA_CallImsaNumType2SpmNumType(IMSA_CALL_NUM_TYPE_ENUM_UINT8 enNumType)
{
    MN_CALL_NUM_TYPE_ENUM_U8 enSpmNumType = 0;

    IMSA_INFO_LOG("IMSA_CallImsaNumType2SpmNumType is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallImsaNumType2SpmNumType_ENUM, LNAS_ENTRY);

    switch (enNumType)
    {
    case IMSA_CALL_NUM_NATIONAL:
        enSpmNumType = (MN_CALL_IS_EXIT | (MN_CALL_TON_NATIONAL << 4) | MN_CALL_NPI_ISDN);
        break;
    case IMSA_CALL_NUM_INTERNATIONAL:
        enSpmNumType = (MN_CALL_IS_EXIT | (MN_CALL_TON_INTERNATIONAL << 4) | MN_CALL_NPI_ISDN);
        break;
    default:
        IMSA_ERR_LOG1("IMSA_CallImsaNumType2SpmNumType: invalid number type", enNumType);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallImsaNumType2SpmNumType_ENUM, LNAS_PARAM_INVALID, enNumType);
        enSpmNumType = (MN_CALL_IS_EXIT | (MN_CALL_TON_UNKNOWN << 4) | MN_CALL_NPI_UNKNOWN);
    }

    return enSpmNumType;
}

/*****************************************************************************
 Function Name  : IMSA_CallCallNumberImsa2CS
 Description    : IMSA���к������ݽṹ��SPM���к������ݽṹת��
 Input          : pstSrcNumber      IMSA���к������ݽṹ
 Output         : pstDstNumber      SPM���к������ݽṹ
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-08-05  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallCallNumberImsa2CS(const IMSA_CALL_NUMBER_STRU *pstSrcNumber,
                                    MN_CALL_BCD_NUM_STRU *pstDstNumber)
{
    IMSA_INFO_LOG("IMSA_CallCallNumberImsa2CS is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallCallNumberImsa2CS_ENUM, LNAS_ENTRY);

    /* ���º������� */
    pstDstNumber->enNumType = IMSA_CallImsaNumType2SpmNumType(pstSrcNumber->enNumType);

    /* ���º������� */
    if (VOS_FALSE == IMSA_UtilAsciiNumberToBcd(pstSrcNumber->aucNumber, pstDstNumber->aucBcdNum, &pstDstNumber->ucNumLen))
    {
        pstDstNumber->ucNumLen = 0;
    }
}

/*****************************************************************************
 Function Name  : IMSA_CallCalledNumberImsa2CS
 Description    : IMSA���к������ݽṹ��SPM���к������ݽṹת��
 Input          : pstSrcNumber      IMSA���к������ݽṹ
 Output         : pstDstNumber      SPM���к������ݽṹ
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-08-05  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallCalledNumberImsa2CS(const IMSA_CALLED_NUMBER_STRU *pstSrcNumber,
                                      MN_CALL_CALLED_NUM_STRU *pstDstNumber)
{
    IMSA_INFO_LOG("IMSA_CallCalledNumberImsa2CS is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallCalledNumberImsa2CS_ENUM, LNAS_ENTRY);

    /* ���º������� */
    pstDstNumber->enNumType = IMSA_CallImsaNumType2SpmNumType(pstSrcNumber->enNumType);

    /* ���º������� */
    if (VOS_FALSE == IMSA_UtilAsciiNumberToBcd(pstSrcNumber->aucNumber, pstDstNumber->aucBcdNum, &pstDstNumber->ucNumLen))
    {
        pstDstNumber->ucNumLen = 0;
    }
}


/*****************************************************************************
 Function Name  : IMSA_ProcSsacInfo
 Description    : IMSA����SSAC��Ϣ
 Input          :
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.leili 00132387     2013-10-11  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_ProcSsacInfo
(
    MN_CALL_TYPE_ENUM_UINT8             enCallType
)
{
    IMSA_LRRC_SSAC_INFO_STRU            stSsacInfo;
    VOS_UINT32                          ulRand1 = 0;
    VOS_UINT32                          ulRand2 = 0;
    VOS_UINT32                          ulTxLen = 0;
    VOS_UINT32                          ulRand3 = 0;
    VOS_UINT32                          ulRand4 = 0;
    VOS_UINT32                          ulTyLen = 0;
    IMSA_CALL_MANAGER_STRU              *pstImsaCallCtx  = VOS_NULL_PTR;

    pstImsaCallCtx   = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_ProcSsacInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcSsacInfo_ENUM, LNAS_ENTRY);

    if(MN_CALL_TYPE_EMERGENCY == enCallType)
    {
        IMSA_INFO_LOG("IMSA_ProcSsacInfo: emc voice or vedio!");
        TLPS_PRINT2LAYER_INFO(IMSA_ProcSsacInfo_ENUM, IMSA_EMERGENCY);
        return VOS_TRUE;
    }

    if (MN_CALL_TYPE_VIDEO == enCallType)
    {
        if (VOS_TRUE == IMSA_IsTimerRunning(&pstImsaCallCtx->stBackOffTxTimer))
        {
            /*�ܾ���ý��ҵ��*/

            return VOS_FALSE;
        }

        /*ͨ��API��ȡ�ײ��SSAC��Ϣ*/
        if (VOS_OK != IMSA_LRRC_GetSSACInfo(&stSsacInfo))
        {
            IMSA_WARN_LOG("IMSA_ProcSsacInfo: vedio get LRRC SSAC Info err!");
            TLPS_PRINT2LAYER_WARNING1(IMSA_ProcSsacInfo_ENUM, IMSA_CALL_API_ERROR, 1);

            return VOS_TRUE;
        }

        /* ����һ������� fRandom(0--15) */
        ulRand1 = VOS_Rand(16);

        if (ulRand1 < stSsacInfo.ucBarFactorForVideo)
        {
            return VOS_TRUE;
        }
        ulRand2 = VOS_Rand(100);
        ulTxLen = (700 +(6*ulRand2))*(g_ausSsacBarringTimer[stSsacInfo.ucBarTimeForVideo]);
        pstImsaCallCtx->stBackOffTxTimer.ulTimerLen = ulTxLen;
        IMSA_StartTimer(&pstImsaCallCtx->stBackOffTxTimer);
        /*�ܾ���ý��ҵ��*/

        return VOS_FALSE;
    }

    if (MN_CALL_TYPE_VOICE == enCallType)
    {
        if (VOS_TRUE == IMSA_IsTimerRunning(&pstImsaCallCtx->stBackOffTyTimer))
        {
            /*�ܾ���ý��ҵ��*/

            return VOS_FALSE;
        }

        /*ͨ��API��ȡ�ײ��SSAC��Ϣ*/
        if (VOS_OK != IMSA_LRRC_GetSSACInfo(&stSsacInfo))
        {
            IMSA_WARN_LOG("IMSA_ProcSsacInfo: voice get LRRC SSAC Info err!");
            TLPS_PRINT2LAYER_WARNING1(IMSA_ProcSsacInfo_ENUM, IMSA_CALL_API_ERROR, 1);

            return VOS_TRUE;
        }

        /* ����һ������� fRandom(0--15) */
        ulRand3 = VOS_Rand(16);
        if (ulRand3 < stSsacInfo.ucBarFactorForVoice)
        {
            return VOS_TRUE;
        }
        ulRand4 = VOS_Rand(100);
        ulTyLen = (700 + (6*ulRand4))*(g_ausSsacBarringTimer[stSsacInfo.ucBarTimeForVoice]);
        pstImsaCallCtx->stBackOffTyTimer.ulTimerLen = ulTyLen;
        IMSA_StartTimer(&pstImsaCallCtx->stBackOffTyTimer);

        /*�ܾ���ý��ҵ��*/

        return VOS_FALSE;

    }
    return VOS_TRUE;

}

/*****************************************************************************
 Function Name  : IMSA_CallSaveCliendIdOpidWhenAnswerCall
 Description    : �����绰ʱ����CLIENT ID��OPID
                  pstAppMsg         SPM�·����������
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-08-13  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallSaveCliendIdOpidWhenAnswerCall
(
    const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU     *pstAppMsg
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx  = IMSA_CallCtxGet();
    VOS_UINT32                          ulLoop      = IMSA_NULL;

    for (ulLoop = 0; ulLoop < IMSA_CALL_MAX_NUM; ulLoop++)
    {
        if (VOS_TRUE != pstCallCtx->astCallEntity[ulLoop].bitOpIsUsed)
        {
            continue;
        }

        if ((IMSA_CALL_STATUS_INCOMING == pstCallCtx->astCallEntity[ulLoop].enStatus)
            || (IMSA_CALL_STATUS_WAITING == pstCallCtx->astCallEntity[ulLoop].enStatus))
        {
            IMSA_INFO_LOG("IMSA_CallSaveCliendIdOpidWhenAnswerCall: save client id and opid!");
            TLPS_PRINT2LAYER_INFO(IMSA_CallSaveCliendIdOpidWhenAnswerCall_ENUM, 1);

            pstCallCtx->astCallEntity[ulLoop].usClientId = pstAppMsg->usClientId;
            pstCallCtx->astCallEntity[ulLoop].ulOpId = pstAppMsg->ucOpId;

            return ;
        }
    }
}


/*****************************************************************************
 Function Name  : IMSA_CallProcSpmMsgSupsBuidMpty
 Description    : SPM�·�����ֵ����������
 Input          : ulCallId          ����id
                  pstAppMsg         SPM�·����������
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-09-12  Modify
*****************************************************************************/
VOS_UINT32 IMSA_CallProcSpmMsgSupsBuidMpty(VOS_UINT32 ulCallId, const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU *pstAppMsg)
{
    VOS_UINT32 ulResult = VOS_TRUE;
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallProcSpmMsgSupsBuidMpty is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgSupsBuidMpty_ENUM, LNAS_ENTRY);


    ulResult = IMSA_CallSendImsMsgSups(ulCallId, pstAppMsg);
    if (VOS_TRUE == ulResult)
    {
        /* ����������ʱ�� */
        IMSA_StartTimer(&pstCallCtx->stProctectTimer);

        (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             pstAppMsg->stCallMgmtCmd.callId,
                                             TAF_CS_CAUSE_SUCCESS);
    }
    else
    {
        IMSA_ERR_LOG("IMSA_CallProcSpmMsgSupsBuidMpty: error occurs, should return failure to SPM");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallProcSpmMsgSupsBuidMpty_ENUM, LNAS_ERROR);

        (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             pstAppMsg->stCallMgmtCmd.callId,
                                             TAF_CS_CAUSE_IMSA_ERROR);
    }

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcSpmMsgSupsEconfRelUser
 Description    : SPM�·����߳���ǿ�෽ͨ����ĳ���û�
 Input          : ulCallId          ����id
                  pstAppMsg         SPM�·����������
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.wangchen 00209181   2014-12-15  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcSpmMsgSupsEconfRelUser(VOS_UINT32 ulCallId, const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU *pstAppMsg)
{
    VOS_UINT32 ulResult = VOS_TRUE;
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallProcSpmMsgSupsEconfRelUser is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgSupsEconfRelUser_ENUM, LNAS_ENTRY);


    ulResult = IMSA_CallSendImsMsgSups(ulCallId, pstAppMsg);
    if (VOS_TRUE == ulResult)
    {
        /* ����������ʱ�� */
        IMSA_StartTimer(&pstCallCtx->stProctectTimer);

        (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             pstAppMsg->stCallMgmtCmd.callId,
                                             TAF_CS_CAUSE_SUCCESS);
    }
    else
    {
        IMSA_ERR_LOG("IMSA_CallProcSpmMsgSupsEconfRelUser: error occurs, should return failure to SPM");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallProcSpmMsgSupsEconfRelUser_ENUM, LNAS_ERROR);

        (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             pstAppMsg->stCallMgmtCmd.callId,
                                             TAF_CS_CAUSE_IMSA_ERROR);
    }

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcSpmMsgSupsHoldAllExpectX
 Description    : SPM�·�����ֵ����������
 Input          : ulCallId          ����id
                  pstAppMsg         SPM�·����������
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-09-12  Modify
*****************************************************************************/
VOS_UINT32 IMSA_CallProcSpmMsgSupsHoldAllExpectX
(
    VOS_UINT32                              ulCallId,
    const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU  *pstAppMsg
)
{
    VOS_UINT32 ulResult = VOS_TRUE;
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallProcSpmMsgSupsHoldAllExpectX is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgSupsHoldAllExpectX_ENUM, LNAS_ENTRY);


    ulResult = IMSA_CallSendImsMsgSups(ulCallId, pstAppMsg);
    if (VOS_TRUE == ulResult)
    {
        /* ����������ʱ�� */
        IMSA_StartTimer(&pstCallCtx->stProctectTimer);

        (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             pstAppMsg->stCallMgmtCmd.callId,
                                             TAF_CS_CAUSE_SUCCESS);
    }
    else
    {
        IMSA_ERR_LOG("IMSA_CallProcSpmMsgSupsHoldAllExpectX: error occurs, should return failure to SPM");
        TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgSupsHoldAllExpectX_ENUM, LNAS_ERROR);

        (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             pstAppMsg->stCallMgmtCmd.callId,
                                             TAF_CS_CAUSE_IMSA_ERROR);
    }

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcSpmMsgSupsHoldActAcptOths
 Description    : SPM�·�����ֵ����������
 Input          : ulCallId          ����id
                  pstAppMsg         SPM�·����������
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-09-12  Modify
*****************************************************************************/
VOS_UINT32 IMSA_CallProcSpmMsgSupsHoldActAcptOth
(
    VOS_UINT32                              ulCallId,
    const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU  *pstAppMsg
)
{
    VOS_UINT32 ulResult = VOS_TRUE;
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallProcSpmMsgSupsHoldActAcptOth is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgSupsHoldActAcptOth_ENUM, LNAS_ENTRY);

    ulResult = IMSA_CallSendImsMsgSups(ulCallId, pstAppMsg);
    if (VOS_TRUE == ulResult)
    {
        IMSA_CallSaveCliendIdOpidWhenAnswerCall(pstAppMsg);

        /* ����������ʱ�� */
        IMSA_StartTimer(&pstCallCtx->stProctectTimer);

        (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             pstAppMsg->stCallMgmtCmd.callId,
                                             TAF_CS_CAUSE_SUCCESS);
    }
    else
    {
        IMSA_ERR_LOG("IMSA_CallProcSpmMsgSupsHoldActAcptOth: error occurs, should return failure to SPM");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallProcSpmMsgSupsHoldActAcptOth_ENUM, LNAS_ERROR);

        (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             pstAppMsg->stCallMgmtCmd.callId,
                                             TAF_CS_CAUSE_IMSA_ERROR);
    }

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcSpmMsgSupsRelAllCall
 Description    : SPM�·�����ֵ����������
 Input          : ulCallId          ����id
                  pstAppMsg         SPM�·����������
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-09-12  Modify
      3.lihong 00150010    2013-12-23  Modify:Redial
*****************************************************************************/
VOS_UINT32 IMSA_CallProcSpmMsgSupsRelAllCall
(
    VOS_UINT32                              ulCallId,
    const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU  *pstAppMsg
)
{
    VOS_UINT32                          ulResult        = VOS_TRUE;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx      = IMSA_CallCtxGet();
    VOS_UINT32                          i               = IMSA_NULL;
    IMSA_CALL_ENTITY_STRU              *pstCallEntity   = VOS_NULL_PTR;
    VOS_UINT8                           ucRedialCallIndex   = IMSA_NULL;
    TAF_CS_CAUSE_ENUM_UINT32            enSpmErr        = IMSA_NULL;
    VOS_UINT8                           ucIsNeedSendtoIms = VOS_FALSE;

    IMSA_INFO_LOG("IMSA_CallProcSpmMsgSupsRelAllCall is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgSupsRelAllCall_ENUM, LNAS_ENTRY);

    /* ���������һ������ʵ�壬��δ��IMS����DIAL��Ϣ������Ҫ֪ͨIMS��
    �����ǰ����2·call��һ·����HOLD��һ·IMSδ�ϱ���DIALING״̬������Ҫ֪ͨIMS
    REL ALL������IMSδ�ϱ���DIALING״̬�ĺ���ʵ�壬��ҪIMSA�Լ��ͷţ�SPM��Ҫ���յ�AT���������
    ���ܴ���release�¼���*/
    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if (VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed)
        {
            if (IMSA_CALL_INVALID_ID != pstCallCtx->astCallEntity[i].ucImscallId)
            {
                ucIsNeedSendtoIms = VOS_TRUE;
            }
            else
            {
                pstCallEntity = &(pstCallCtx->astCallEntity[i]);
            }
        }
    }

    /* �������Ҫ֪ͨSPM������Ҫ��AT������������ϱ�RELEASE�¼� */
    if(VOS_FALSE == ucIsNeedSendtoIms)
    {
        (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             pstAppMsg->stCallMgmtCmd.callId,
                                             TAF_CS_CAUSE_SUCCESS);

        (VOS_VOID)IMSA_CallSendSpmSupsResultMsg(pstAppMsg->usClientId,
                                                pstAppMsg->ucOpId,
                                                pstAppMsg->stCallMgmtCmd.callId,
                                                MN_CALL_SS_RES_SUCCESS);

        /* ��������ͷŵ�CALL ID���ز�CALL IDһ�£���ֱ�ӻظ��ɹ���������ز����� */
        if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stRedialIntervelTimer))
        {
            ucRedialCallIndex   = (VOS_UINT8)pstCallCtx->stRedialIntervelTimer.usPara;
            if (ucRedialCallIndex < IMSA_CALL_MAX_NUM)
            {
                pstCallEntity = &pstCallCtx->astCallEntity[ucRedialCallIndex];
                IMSA_CallInterruptRedial(pstCallEntity);
            }
            return ulResult;
        }

         /*  ��������ͷŵ�CALL ID�����ڽ�����ע���CALL IDһ�£���֪ͨSPM RELEASE �¼� */
        if (IMSA_TRUE == pstCallCtx->ucRetryEmcRegFlag)
        {
            pstCallEntity = &pstCallCtx->astCallEntity[pstCallCtx->ucCallEntityIndex];


            /* ��IMS����ԭ��ֵת��ΪSPM����ԭ��ֵ */
            /* �޸ĺ������ */
            enSpmErr = IMSA_CallTransImsErr2SpmErr(&pstCallEntity->stImsError.stErrorCode);

            pstCallEntity->ucSpmcallId = pstCallCtx->ucId;

            IMSA_CallReleaseCallCommonProc(pstCallEntity, enSpmErr);

            /* ����������ע���ʶ�Ȳ��� */
            pstCallCtx->ucRetryEmcRegFlag = IMSA_FALSE;
            pstCallCtx->ucId = IMSA_NULL;
            pstCallCtx->ucCallEntityIndex = IMSA_NULL;

            return ulResult;
        }

        /* ���ֻ�����յ�IMS�ϱ���DIALING״̬ǰ���û��Ҷϵ绰 */
        IMSA_CallSpmMsgClear();

        if (pstCallEntity)
        {
            /* ����Ϊ�û������Ҷ� */
            IMSA_CallUpdateDiscCallDir( pstCallEntity->ucSpmcallId, IMSA_TRUE);

            IMSA_CallReleaseCallCommonProc(pstCallEntity, TAF_CS_CAUSE_SUCCESS);
        }

        return ulResult;
    }

    ulResult = IMSA_CallSendImsMsgSups(ulCallId, pstAppMsg);
    if (VOS_TRUE == ulResult)
    {
        /* ����������ʱ�� */
        IMSA_StartTimer(&pstCallCtx->stProctectTimer);

        (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             pstAppMsg->stCallMgmtCmd.callId,
                                             TAF_CS_CAUSE_SUCCESS);

        /* �����precondition���̣���Щ��δ�ϱ���״̬��SPM��incoming�� waiting
           CALL(����IDLE̬)����Ҫ��ǣ���Ϊ����CALL���ͷŲ����ϱ���SPM */

        /* ��ȡ��IDLE״̬��CALL����������ЩCALLʵ������Ϊ�û������Ҷ� */
        for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
        {
            if ((VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
                (IMSA_CALL_STATUS_IDLE != pstCallCtx->astCallEntity[i].enStatus))
            {
                IMSA_CallUpdateDiscCallDir( pstCallCtx->astCallEntity[i].ucSpmcallId,
                                            IMSA_TRUE);
            }
        }


    }
    else
    {
        IMSA_ERR_LOG("IMSA_CallProcSpmMsgSupsRelAllCall: error occurs, should return failure to SPM");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallProcSpmMsgSupsRelAllCall_ENUM, LNAS_ERROR);

        (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             pstAppMsg->stCallMgmtCmd.callId,
                                             TAF_CS_CAUSE_IMSA_ERROR);
    }

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcSpmMsgSupsRelCallX
 Description    : SPM�·�����ֵ����������
 Input          : ulCallId          ����id
                  pstAppMsg         SPM�·����������
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-09-12  Modify
      3.lihong 00150010    2013-09-12  Modify:stDiscDir
      4.lihong 00150010    2013-12-23  Modify:Redial
*****************************************************************************/
VOS_UINT32 IMSA_CallProcSpmMsgSupsRelCallX
(
    VOS_UINT32                              ulCallId,
    const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU  *pstAppMsg
)
{
    VOS_UINT32                          ulResult        = VOS_TRUE;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx      = IMSA_CallCtxGet();
    IMSA_CALL_ENTITY_STRU              *pstCallEntity   = VOS_NULL_PTR;
    VOS_UINT8                           ucRedialCallId  = IMSA_NULL;
    VOS_UINT8                           ucRedialCallIndex   = IMSA_NULL;
    TAF_CS_CAUSE_ENUM_UINT32            enSpmErr        = IMSA_NULL;

    IMSA_INFO_LOG("IMSA_CallProcSpmMsgSupsRelCallX is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgSupsRelCallX_ENUM, LNAS_ENTRY);

    /* ��������ͷŵ�CALL ID���ز�CALL IDһ�£���ֱ�ӻظ��ɹ���������ز����� */
    if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stRedialIntervelTimer))
    {
        ucRedialCallId = (pstCallCtx->stRedialIntervelTimer.usPara & 0xff00) >> IMSA_MOVEMENT_8;
        if (ulCallId == (VOS_UINT32)ucRedialCallId)
        {
            /* ֱ�ӷ���SPM�ɹ� */
            (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                                 pstAppMsg->ucOpId,
                                                 pstAppMsg->stCallMgmtCmd.callId,
                                                 TAF_CS_CAUSE_SUCCESS);

            (VOS_VOID)IMSA_CallSendSpmSupsResultMsg( pstAppMsg->usClientId,
                                                     pstAppMsg->ucOpId,
                                                     pstAppMsg->stCallMgmtCmd.callId,
                                                     MN_CALL_SS_RES_SUCCESS);

            ucRedialCallIndex   = (VOS_UINT8)pstCallCtx->stRedialIntervelTimer.usPara;
            if (ucRedialCallIndex < IMSA_CALL_MAX_NUM)
            {
                pstCallEntity = &pstCallCtx->astCallEntity[ucRedialCallIndex];
                IMSA_CallInterruptRedial(pstCallEntity);
            }

            return VOS_TRUE;
        }
    }
    if ((IMSA_TRUE == pstCallCtx->ucRetryEmcRegFlag) && (ulCallId == pstCallCtx->ucId))
    {
        pstCallEntity = &pstCallCtx->astCallEntity[pstCallCtx->ucCallEntityIndex];

        /* ֱ�ӷ���SPM�ɹ� */
        (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             pstAppMsg->stCallMgmtCmd.callId,
                                             TAF_CS_CAUSE_SUCCESS);

        (VOS_VOID)IMSA_CallSendSpmSupsResultMsg( pstAppMsg->usClientId,
                                                 pstAppMsg->ucOpId,
                                                 pstAppMsg->stCallMgmtCmd.callId,
                                                 MN_CALL_SS_RES_SUCCESS);

        /* ��IMS����ԭ��ֵת��ΪSPM����ԭ��ֵ */
        /* �޸ĺ������ */
        enSpmErr = IMSA_CallTransImsErr2SpmErr(&pstCallEntity->stImsError.stErrorCode);

        pstCallEntity->ucSpmcallId = pstCallCtx->ucId;

        IMSA_CallReleaseCallCommonProc(pstCallEntity, enSpmErr);

        /* ����������ע���ʶ�Ȳ��� */
        pstCallCtx->ucRetryEmcRegFlag = IMSA_FALSE;
        pstCallCtx->ucId = IMSA_NULL;
        pstCallCtx->ucCallEntityIndex = IMSA_NULL;

        return VOS_TRUE;
    }

    pstCallEntity = IMSA_CallEntityGetUsedBySpmCallId(ulCallId);

    if (pstCallEntity)
    {
        /* ������յ�IMS�ϱ���DIALING״̬ǰ���յ��û��ĹҶ������ֱ�Ӹ�SPM�ظ�CMD_RSLT��
        ����Ҫ֪ͨIMS�����յ�IMS��DIALIGN״̬ʱ������Ҳ�������ʵ�壬��֪ͨIMS RELEASE�¼� */
        if (IMSA_CALL_INVALID_ID == pstCallEntity->ucImscallId)
        {
            /* ����л����SPM��Ϣ����ֱ����� */
            if ((IMSA_OP_TRUE == pstCallCtx->stSpmMsg.bitOpSpmMsg) &&
                (ID_SPM_IMSA_CALL_ORIG_REQ == pstCallCtx->stSpmMsg.ulSpmMsgId) )
            {
                IMSA_CallSpmMsgClear();
            }

             /* ֱ�ӷ���SPM�ɹ� */
            (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                                 pstAppMsg->ucOpId,
                                                 pstAppMsg->stCallMgmtCmd.callId,
                                                 TAF_CS_CAUSE_SUCCESS);

            (VOS_VOID)IMSA_CallSendSpmSupsResultMsg(pstAppMsg->usClientId,
                                                    pstAppMsg->ucOpId,
                                                    pstAppMsg->stCallMgmtCmd.callId,
                                                    MN_CALL_SS_RES_SUCCESS);
            /* ����Ϊ�û������Ҷ� */
            IMSA_CallUpdateDiscCallDir( pstCallEntity->ucSpmcallId, IMSA_TRUE);

            IMSA_CallReleaseCallCommonProc(pstCallEntity, TAF_CS_CAUSE_SUCCESS);

        }

        else
        {
            ulResult = IMSA_CallSendImsMsgSups(ulCallId, pstAppMsg);
            if (VOS_TRUE == ulResult)
            {
                /* ����������ʱ�� */
                IMSA_StartTimer(&pstCallCtx->stProctectTimer);

                (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                                 pstAppMsg->ucOpId,
                                                 pstAppMsg->stCallMgmtCmd.callId,
                                                 TAF_CS_CAUSE_SUCCESS);

                IMSA_CallUpdateDiscCallDir(ulCallId, IMSA_TRUE);
            }
            else
            {
                IMSA_ERR_LOG("IMSA_CallProcSpmMsgSupsRelCallX: error occurs, should return failure to SPM");
                TLPS_PRINT2LAYER_ERROR(IMSA_CallProcSpmMsgSupsRelCallX_ENUM, LNAS_ERROR);

                (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                                 pstAppMsg->ucOpId,
                                                 pstAppMsg->stCallMgmtCmd.callId,
                                                 TAF_CS_CAUSE_IMSA_ERROR);
            }
        }
    }
    else
    {
        /* ֱ�ӷ���SPM�ɹ� */
        (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             pstAppMsg->stCallMgmtCmd.callId,
                                             TAF_CS_CAUSE_SUCCESS);

        (VOS_VOID)IMSA_CallSendSpmSupsResultMsg(pstAppMsg->usClientId,
                                                pstAppMsg->ucOpId,
                                                pstAppMsg->stCallMgmtCmd.callId,
                                                MN_CALL_SS_RES_SUCCESS);
    }

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcSpmMsgSupsRelActAcptOth
 Description    : SPM�·�����ֵ����������
 Input          : ulCallId          ����id
                  pstAppMsg         SPM�·����������
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-09-12  Modify
      3.lihong 00150010    2013-09-12  Modify:stDiscDir
*****************************************************************************/
VOS_UINT32 IMSA_CallProcSpmMsgSupsRelActAcptOth
(
    VOS_UINT32                              ulCallId,
    const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU  *pstAppMsg
)
{
    VOS_UINT32                          ulResult        = VOS_TRUE;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx      = IMSA_CallCtxGet();
    VOS_UINT32                          ulNumOfCalls    = IMSA_NULL;
    VOS_UINT32                          aulCallIds[IMSA_CALL_MAX_NUM] = {0};
    VOS_UINT32                          i               = IMSA_NULL;

    IMSA_INFO_LOG("IMSA_CallProcSpmMsgSupsRelActAcptOth is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgSupsRelActAcptOth_ENUM, LNAS_ENTRY);


    ulResult = IMSA_CallSendImsMsgSups(ulCallId, pstAppMsg);
    if (VOS_TRUE == ulResult)
    {
        IMSA_CallSaveCliendIdOpidWhenAnswerCall(pstAppMsg);

        /* ����������ʱ�� */
        IMSA_StartTimer(&pstCallCtx->stProctectTimer);

        (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             pstAppMsg->stCallMgmtCmd.callId,
                                             TAF_CS_CAUSE_SUCCESS);

        /* ��ȡACTIVE״̬��CALL����������ЩCALLʵ������Ϊ�û������Ҷ� */
        IMSA_CallGetCallsByState(   IMSA_CALL_STATUS_ACTIVE,
                                    &ulNumOfCalls,
                                    aulCallIds);

        for (i = 0; i < ulNumOfCalls; i++)
        {
            IMSA_CallUpdateDiscCallDir(aulCallIds[i], IMSA_TRUE);
        }
    }
    else
    {
        IMSA_ERR_LOG("IMSA_CallProcSpmMsgSupsRelActAcptOth: error occurs, should return failure to SPM");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallProcSpmMsgSupsRelActAcptOth_ENUM, LNAS_ERROR);

        (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             pstAppMsg->stCallMgmtCmd.callId,
                                             TAF_CS_CAUSE_IMSA_ERROR);
    }

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcSpmMsgSupsRelHeldOrUdub
 Description    : SPM�·�����ֵ����������
 Input          : ulCallId          ����id
                  pstAppMsg         SPM�·����������
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-09-12  Modify
      3.lihong 00150010    2013-09-12  Modify:stDiscDir
*****************************************************************************/
VOS_UINT32 IMSA_CallProcSpmMsgSupsRelHeldOrUdub
(
    VOS_UINT32                              ulCallId,
    const SPM_IMSA_CALL_SUPS_CMD_REQ_STRU  *pstAppMsg
)
{
    VOS_UINT32                          ulResult        = VOS_TRUE;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx      = IMSA_CallCtxGet();
    VOS_UINT32                          ulNumOfCalls    = IMSA_NULL;
    VOS_UINT32                          aulCallIds[IMSA_CALL_MAX_NUM] = {0};
    VOS_UINT32                          i               = IMSA_NULL;

    IMSA_INFO_LOG("IMSA_CallProcSpmMsgSupsRelHeldOrUdub is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcSpmMsgSupsRelHeldOrUdub_ENUM, LNAS_ENTRY);

    ulResult = IMSA_CallSendImsMsgSups(ulCallId, pstAppMsg);
    if (VOS_TRUE == ulResult)
    {
        /* ����������ʱ�� */
        IMSA_StartTimer(&pstCallCtx->stProctectTimer);

        (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             pstAppMsg->stCallMgmtCmd.callId,
                                             TAF_CS_CAUSE_SUCCESS);

        /* ��ȡHOLD״̬��CALL����������ЩCALLʵ������Ϊ�û������Ҷ� */
        IMSA_CallGetCallsByState(   IMSA_CALL_STATUS_HELD,
                                    &ulNumOfCalls,
                                    aulCallIds);

        for (i = 0; i < ulNumOfCalls; i++)
        {
            IMSA_CallUpdateDiscCallDir(aulCallIds[i], IMSA_TRUE);
        }

        /* �����precondition���̣���Щ��δ�ϱ���״̬��SPM��incoming�� waiting
           CALL(����IDLE̬)����Ҫ��ǣ���Ϊ����CALL���ͷŲ����ϱ���SPM */

        /* ��ȡWATING״̬��CALL����������ЩCALLʵ������Ϊ�û������Ҷ� */
        IMSA_CallGetCallsByState(   IMSA_CALL_STATUS_WAITING,
                                    &ulNumOfCalls,
                                    aulCallIds);

        for (i = 0; i < ulNumOfCalls; i++)
        {
            IMSA_CallUpdateDiscCallDir(aulCallIds[i], IMSA_TRUE);
        }

        /* ��ȡINCOMING״̬��CALL����������ЩCALLʵ������Ϊ�û������Ҷ� */
        IMSA_CallGetCallsByState(   IMSA_CALL_STATUS_INCOMING,
                                    &ulNumOfCalls,
                                    aulCallIds);

        for (i = 0; i < ulNumOfCalls; i++)
        {
            IMSA_CallUpdateDiscCallDir(aulCallIds[i], IMSA_TRUE);
        }
    }
    else
    {
        IMSA_ERR_LOG("IMSA_CallProcSpmMsgSupsRelHeldOrUdub: error occurs, should return failure to SPM");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallProcSpmMsgSupsRelHeldOrUdub_ENUM, LNAS_ERROR);

        (VOS_VOID)IMSA_CallSendSpmSupsCnfMsg(pstAppMsg->usClientId,
                                             pstAppMsg->ucOpId,
                                             pstAppMsg->stCallMgmtCmd.callId,
                                             TAF_CS_CAUSE_IMSA_ERROR);
    }

    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_CallCheckDtmfKey
 Description    : ���DTMF���ַ��Ƿ�Ϸ�
 Input          : pckey-------------�ַ�ָ��
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010    2013-10-14  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallCheckDtmfKey
(
    VOS_CHAR                           *pckey
)
{
    /* ת��Ϊ��д�ַ� */
    if ( (*pckey >= 'a') && (*pckey <= 'z'))
    {
        *pckey = *pckey - 0x20;
    }

    if (!( (('0' <= *pckey) && ('9' >= *pckey))
         || ('*' == *pckey) || ('#' == *pckey)
         || ('A' == *pckey) || ('B' == *pckey)
         || ('C' == *pckey) || ('D' == *pckey) ))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 Function Name  : IMSA_CallCheckUserDtmfCallId
 Description    : �ж��Ƿ��к���CALL������DTMF��
 Input          : ucCallId-------------CALL ID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010    2013-10-14  Draft Enact
*****************************************************************************/
TAF_CS_CAUSE_ENUM_UINT32 IMSA_CallIsAllowDtmf
(
    const VOS_UINT8                    *pucCallIds,
    VOS_UINT32                          ulNumOfCalls,
    VOS_UINT8                           ucCallId
)
{
    VOS_UINT8                           ucLoop;

    /* �ж�CallID����Ч�� 0Ĭ��Ϊ��ǰ����CallID */
    if (0 != ucCallId)
    {
        for (ucLoop = 0; ucLoop < ulNumOfCalls; ucLoop++)
        {
            if (pucCallIds[ucLoop] == ucCallId)
            {
                break;
            }
        }

        if (ucLoop == ulNumOfCalls)
        {
            return TAF_CS_CAUSE_NO_CALL_ID;
        }
    }

    return TAF_CS_CAUSE_SUCCESS;
}


/*****************************************************************************
 Function Name  : IMSA_CallCheckUserDtmfCallId
 Description    : �ж��Ƿ��к���CALL������DTMF��
 Input          : ucCallId-------------CALL ID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010    2013-10-14  Draft Enact
*****************************************************************************/
TAF_CS_CAUSE_ENUM_UINT32  IMSA_CallCheckUserDtmfCallId
(
    VOS_UINT8                           ucCallId
)
{
    VOS_UINT8                           ucLoop                          = IMSA_NULL;
    VOS_UINT32                          ulNumOfCalls                    = IMSA_NULL;
    VOS_UINT8                           aucCallIds[IMSA_CALL_MAX_NUM]   = {0};
    IMSA_CALL_MANAGER_STRU             *pstCallCtx                      = IMSA_CallCtxGet();

    IMSA_MEM_SET_S(aucCallIds, sizeof(aucCallIds), 0, sizeof(aucCallIds));

    for (ucLoop = 0; ucLoop < IMSA_CALL_MAX_NUM; ucLoop++)
    {
        if (VOS_TRUE != pstCallCtx->astCallEntity[ucLoop].bitOpIsUsed)
        {
            continue;
        }

        #if 0
        if ((IMSA_CALL_STATUS_ACTIVE == pstCallCtx->astCallEntity[ucLoop].enStatus) ||
            (IMSA_CALL_STATUS_ALERTING == pstCallCtx->astCallEntity[ucLoop].enStatus))
        {
            aucCallIds[ulNumOfCalls] = pstCallCtx->astCallEntity[ucLoop].ucSpmcallId;
            ulNumOfCalls++;
        }
        #endif
        aucCallIds[ulNumOfCalls] = pstCallCtx->astCallEntity[ucLoop].ucSpmcallId;
        ulNumOfCalls++;
    }

    if (0 == ulNumOfCalls)
    {
        return TAF_CS_CAUSE_NO_CALL_ID;
    }

    /*
        DTMF��������ӿ�Լ����
        �û������CALL ID����Чֵ0��ָʾʹ������CALL ID����DTMF��Ϣ
        �û������CALL ID������Чֵ0��ָʾ���û��·���CALL ID����DTMF��Ϣ���������CALL ID
        ��Ҫ���㷢��DTMF��Ϣ������
    */
    return IMSA_CallIsAllowDtmf(aucCallIds, ulNumOfCalls, ucCallId);
}

/*****************************************************************************
 Function Name  : IMSA_CallFillCurrentDtmfInfo
 Description    : ���浱ǰ���͵�DTMF������Ϣ
 Input          : ucCallId---------------------CALL ID
                  cKey-------------------------�ַ�
                  usDuration-------------------����ʱ��
                  usClientId-------------------CLIENT ID
                  ucSpmOpid--------------------SPM OPID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010    2013-10-14  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallFillCurrentDtmfInfo
(
    VOS_UINT8                           ucCallId,
    VOS_CHAR                            cKey,
    VOS_UINT16                          usDuration,
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucSpmOpid
)
{
    IMSA_CALL_DTMF_INFO_STRU           *pstDtmfCurInfo  = VOS_NULL_PTR;

    pstDtmfCurInfo  = IMSA_CallGetCurrentDtmfInfo();
    pstDtmfCurInfo->ucCallId    = ucCallId;
    pstDtmfCurInfo->cKey        = cKey;
    pstDtmfCurInfo->usOnLength  = usDuration;
    pstDtmfCurInfo->usClientId  = usClientId;
    pstDtmfCurInfo->ucSpmOpId   = ucSpmOpid;
    pstDtmfCurInfo->ulImsOpid   = IMSA_GetImsOpId();
}

/*****************************************************************************
 Function Name  : IMSA_CallImsaState2SpmState
 Description    : IMSA����״̬��SPM����״̬��ӳ��
 Input          : enImsaState      IMSA����״̬
 Output         : VOS_VOID
 Return Value   : ӳ�����SPM����״̬

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
MN_CALL_STATE_ENUM_UINT8 IMSA_CallImsaState2SpmState(IMSA_CALL_STATUS_ENUM_UINT8 enImsaState)
{
    MN_CALL_STATE_ENUM_UINT8 enSpmState = MN_CALL_S_BUTT;

    IMSA_INFO_LOG("IMSA_CallImsaState2SpmState is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallImsaState2SpmState_ENUM, LNAS_ENTRY);

    switch (enImsaState)
    {
    case IMSA_CALL_STATUS_IDLE:
        enSpmState = MN_CALL_S_IDLE;
        break;
    case IMSA_CALL_STATUS_DIALING:
        enSpmState = MN_CALL_S_DIALING;
        break;
    case IMSA_CALL_STATUS_TRYING:
        enSpmState = MN_CALL_S_DIALING;
        break;
    case IMSA_CALL_STATUS_ALERTING:
        enSpmState = MN_CALL_S_ALERTING;
        break;
    case IMSA_CALL_STATUS_ACTIVE:
        enSpmState = MN_CALL_S_ACTIVE;
        break;
    case IMSA_CALL_STATUS_INCOMING:
        enSpmState = MN_CALL_S_INCOMING;
        break;
    case IMSA_CALL_STATUS_HELD:
        enSpmState = MN_CALL_S_HELD;
        break;
    case IMSA_CALL_STATUS_WAITING:
        enSpmState = MN_CALL_S_WAITING;
        break;
    default:
        IMSA_ERR_LOG1("IMSA_CallImsaState2SpmState: invalid imsa call state", enImsaState);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallImsaState2SpmState_ENUM, LNAS_PARAM_INVALID, enImsaState);
    }

    return enSpmState;
}

/*****************************************************************************
 Function Name  : IMSA_CallEntity2SpmCallInfoParam
 Description    : IMSA����ʵ�嵽SPM������Ϣ�ṹ���ת��
 Input          : pstCallEntity      IMSA����ʵ��ָ��
                  pstCallInfo        ������Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallEntity2SpmCallInfoParam(const IMSA_CALL_ENTITY_STRU *pstCallEntity,
                                          MN_CALL_INFO_PARAM_STRU *pstCallInfoParam)
{
    IMSA_INFO_LOG("IMSA_CallEntity2SpmCallInfoParam is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallEntity2SpmCallInfoParam_ENUM, LNAS_ENTRY);

    pstCallInfoParam->callId      = pstCallEntity->ucSpmcallId;
    pstCallInfoParam->enCallDir   = pstCallEntity->enDir;
    pstCallInfoParam->enCallState = IMSA_CallImsaState2SpmState(pstCallEntity->enStatus);
    pstCallInfoParam->enMptyState = pstCallEntity->enMpty;
    pstCallInfoParam->enVoiceDomain = TAF_CALL_VOICE_DOMAIN_IMS;

    pstCallInfoParam->ucEConferenceFlag = pstCallEntity->ucIsEconfFlag;

    pstCallInfoParam->enCallType = (MN_CALL_TYPE_ENUM_UINT8)pstCallEntity->enType;

    /* �������к��� */
    IMSA_CallCallNumberImsa2CS(&pstCallEntity->stCallNumber, &pstCallInfoParam->stCallNumber);

    /* ���±��к��� */
    IMSA_CallCalledNumberImsa2CS(&pstCallEntity->stCalledNumber, &pstCallInfoParam->stCalledNumber);

    IMSA_CallCallNumberImsa2CS(&pstCallEntity->stConnectNumber, &pstCallInfoParam->stConnectNumber);

}

/*****************************************************************************
 Function Name  : IMSA_CallEntity2SpmCallInfo
 Description    : IMSA����ʵ�嵽SPM���нṹ���ת��
 Input          : pstCallEntity      IMSA����ʵ��ָ��
                  pstCallInfo        ������Ϣָ��
                  enEvt              �ϱ��¼�
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 00150010    2013-08-21  Modify

*****************************************************************************/
VOS_VOID IMSA_CallEntity2SpmCallInfo
(
    const IMSA_CALL_ENTITY_STRU        *pstCallEntity,
    MN_CALL_EVENT_ENUM_UINT32           enEvt,
    MN_CALL_INFO_STRU                  *pstCallInfo
)
{
    IMSA_INFO_LOG("IMSA_CallEntity2SpmCallInfo is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallEntity2SpmCallInfo_ENUM, LNAS_ENTRY);

    pstCallInfo->callId      = pstCallEntity->ucSpmcallId;
    pstCallInfo->enCallDir   = pstCallEntity->enDir;
    pstCallInfo->enCallState = IMSA_CallImsaState2SpmState(pstCallEntity->enStatus);
    pstCallInfo->enMptyState = pstCallEntity->enMpty;

    pstCallInfo->ucEconfFlag = pstCallEntity->ucIsEconfFlag;

    pstCallInfo->enCallType = (MN_CALL_TYPE_ENUM_UINT8)pstCallEntity->enType;

    /* �������к��� */
    IMSA_CallCallNumberImsa2CS(&pstCallEntity->stCallNumber, &pstCallInfo->stCallNumber);

    /* ���±��к��� */
    IMSA_CallCalledNumberImsa2CS(&pstCallEntity->stCalledNumber, &pstCallInfo->stCalledNumber);

    /* ֻ��UE����MO CALLʱ��IMSA�ϱ�CONNECT�¼�ʱ����Ҫ��дstConnectNumber */
    if ((MN_CALL_EVT_CONNECT == enEvt) && (MN_CALL_DIR_MO == pstCallEntity->enDir))
    {
        /* ��ʵ�ֺ���ת�ƣ����к���ת��ʱ���ϱ�CONNECT NUMBER */
        IMSA_CallCallNumberImsa2CS(&pstCallEntity->stConnectNumber, &pstCallInfo->stConnectNumber);
    }

    /* ����ת�ƺ��� */
    IMSA_CallCallNumberImsa2CS(&pstCallEntity->stRedirectNumber, &pstCallInfo->stRedirectNumber);

    /*�����RELEASE�¼�������Ҫָʾ�Ƿ����û��Ҷ�*/
    if (MN_CALL_EVT_RELEASED == enEvt)
    {
        pstCallInfo->enCallState                = MN_CALL_S_IDLE;
        pstCallInfo->stDiscDir.ucIsUser         = pstCallEntity->stDiscDir.ucIsUser;
        pstCallInfo->stDiscDir.ucDiscCallFlag   = IMSA_TRUE;
    }

    pstCallInfo->enVoiceDomain = TAF_CALL_VOICE_DOMAIN_IMS;
}


/*****************************************************************************
 Function Name  : IMSA_CallReadCallEntityRedirectInfo
 Description    : ��ȡCALLʵ��redirect��Ϣ
 Input          : pstCallEntity------------CALLʵ��ָ��
 Output         : pstGetClprCnf------------CLPR�ظ�ָ��
 Return Value   : ������

 History        :
      1.lihong 00150010      2013-10-12  Draft Enact
      2.wangchen 00209181    2013-12-20  Modify
*****************************************************************************/
VOS_VOID  IMSA_CallReadCallEntityRedirectInfo
(
    const IMSA_CALL_ENTITY_STRU        *pstCallEntity,
    IMSA_SPM_CALL_GET_CLPR_CNF_STRU    *pstGetClprCnf
)
{
    if (MN_CALL_DIR_MT != pstCallEntity->enDir)
    {
        pstGetClprCnf->ulRet = VOS_ERR;
        return;
    }

    /* ��дredirect��Ϣ */
    /* ֻ�к���ת�ƺ�����ڵ�����²Ų���Ҫ��дת�ƺ��� */
    if ('\0' != pstCallEntity->stRedirectNumber.aucNumber[0])
    {
        IMSA_CallCallNumberImsa2CS(&pstCallEntity->stRedirectNumber, &pstGetClprCnf->stRedirectInfo.stRedirectNum);

        if (0 != pstGetClprCnf->stRedirectInfo.stRedirectNum.ucNumLen)
        {
            pstGetClprCnf->stRedirectInfo.bitOpRedirectNum   = VOS_TRUE;
        }
    }


    pstGetClprCnf->ulRet = VOS_OK;
    return;
}

/*****************************************************************************
 Function Name  : IMSA_CallRcvImsStartDtmfProtectTimerExp
 Description    : start dmtf������ʱ����ʱ����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.lihong 0015001     2013-10-14  Draft Enact
*****************************************************************************/
VOS_VOID  IMSA_CallRcvImsStartDtmfProtectTimerExp( VOS_VOID )
{
    IMSA_CALL_DTMF_INFO_STRU           *pstDtmfCurInfo = VOS_NULL_PTR;

    /* �ж�״̬�Ƿ��쳣 */
    if (IMSA_CallGetDtmfState() != IMSA_CALL_DTMF_WAIT_START_CNF)
    {
        IMSA_WARN_LOG("IMSA_CallRcvImsStartDtmfProtectTimerExp: Dtmf State Error!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CallRcvImsStartDtmfProtectTimerExp_ENUM, IMSA_STATE_ERROR);
        return;
    }

    /* �ظ�DTMF��ʽ��Ӧ�¼� */
    pstDtmfCurInfo  = IMSA_CallGetCurrentDtmfInfo();
    (VOS_VOID)IMSA_CallSendSpmStartDtmfRsltMsg( pstDtmfCurInfo->usClientId,
                                                pstDtmfCurInfo->ucSpmOpId,
                                                pstDtmfCurInfo->ucCallId,
                                                TAF_CS_CAUSE_IMSA_TIMEOUT);

    IMSA_CallSetDtmfState(IMSA_CALL_DTMF_IDLE);

    /* ������� */
    IMSA_CallClearDtmfInfo(TAF_CS_CAUSE_UNKNOWN);

    return;
}

/*****************************************************************************
 Function Name  : IMSA_CallRcvImsStopDtmfProtectTimerExp
 Description    : stop dmtf������ʱ����ʱ����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.lihong 0015001     2013-10-14  Draft Enact
*****************************************************************************/
 VOS_VOID  IMSA_CallRcvImsStopDtmfProtectTimerExp( VOS_VOID )
{
    IMSA_CALL_DTMF_INFO_STRU           *pstDtmfCurInfo  = VOS_NULL_PTR;
    IMSA_CALL_DTMF_STATE_ENUM_UINT8     enDtmfState     = IMSA_CALL_DTMF_STATE_BUTT;

    /* �ж�״̬�Ƿ��쳣 */
    enDtmfState = IMSA_CallGetDtmfState();
    if ( (enDtmfState != TAF_CALL_DTMF_WAIT_STOP_CNF)
      && (enDtmfState != TAF_CALL_DTMF_WAIT_AUTO_STOP_CNF) )
    {
        IMSA_WARN_LOG("IMSA_CallRcvImsStopDtmfProtectTimerExp: Dtmf State Error!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CallRcvImsStopDtmfProtectTimerExp_ENUM, IMSA_STATE_ERROR);
        return;
    }

    /* ������û�������STOP_DTMF��Ҫ�ظ���ʽ��Ӧ�¼� */
    pstDtmfCurInfo  = IMSA_CallGetCurrentDtmfInfo();
    if (enDtmfState != (IMSA_CALL_DTMF_STATE_ENUM_UINT8)IMSA_CALL_DTMF_WAIT_AUTO_STOP_CNF)
    {
        (VOS_VOID)IMSA_CallSendSpmStopDtmfRsltMsg(  pstDtmfCurInfo->usClientId,
                                                    pstDtmfCurInfo->ucSpmOpId,
                                                    pstDtmfCurInfo->ucCallId,
                                                    TAF_CS_CAUSE_IMSA_TIMEOUT);
    }

    IMSA_CallSetDtmfState(IMSA_CALL_DTMF_IDLE);

    /* ������� */
    IMSA_CallClearDtmfInfo(TAF_CS_CAUSE_UNKNOWN);

    return;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcTimeoutProtect
 Description    : ������ʱ����ʱ����

                  ������ʱ����ʱ��IMSA
                     - ����Ѿ������SPM���opId
                     - ����Ѿ������IMS���opId
 Input          : pTimerMsg     ��ʱ��ʱ����Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 0015001     2013-09-30  Modify
      3.wangchen 00209181   2014-11-29 Modify:DTS2014112906255
*****************************************************************************/
VOS_VOID IMSA_CallProcOrigReqProtectTimeout(VOS_VOID)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx      = IMSA_CallCtxGet();
    IMSA_CALL_ENTITY_STRU              *pstCallEntity   = VOS_NULL_PTR;
    VOS_UINT16                          usRedialCallIndex = IMSA_NULL;
    TAF_CS_CAUSE_ENUM_UINT32            enSpmErr        = IMSA_NULL;

    /* ������ز��������ز����� */
    if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stRedialMaxTimer))
    {
        usRedialCallIndex   = pstCallCtx->stRedialMaxTimer.usPara;
        if (usRedialCallIndex < IMSA_CALL_MAX_NUM)
        {
            pstCallEntity = &pstCallCtx->astCallEntity[usRedialCallIndex];
            if (pstCallEntity->ucRedialTimes > 0)
            {
                IMSA_INFO_LOG("IMSA_CallProcOrigReqProtectTimeout:redial orig error");
                TLPS_PRINT2LAYER_INFO(IMSA_CallProcOrigReqProtectTimeout_ENUM, 1);
                #if (FEATURE_ON == FEATURE_PTM)
                IMSA_CallErrRecord(pstCallEntity->stImsError.stErrorCode.usSipStatusCode, pstCallEntity);
                #endif
                IMSA_CallInterruptRedial(pstCallEntity);
                return;
            }
        }
    }
    if (IMSA_TRUE == pstCallCtx->ucRetryEmcRegFlag)
    {
        pstCallEntity = &pstCallCtx->astCallEntity[pstCallCtx->ucCallEntityIndex];

        /* ��IMS����ԭ��ֵת��ΪSPM����ԭ��ֵ */
        /* �޸ĺ������ */
        enSpmErr = IMSA_CallTransImsErr2SpmErr(&pstCallEntity->stImsError.stErrorCode);

        pstCallEntity->ucSpmcallId = pstCallCtx->ucId;
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallErrRecord(pstCallEntity->stImsError.stErrorCode.usSipStatusCode, pstCallEntity);
        #endif
        IMSA_CallReleaseCallCommonProc(pstCallEntity, enSpmErr);

        /* ����������ע���ʶ�Ȳ��� */
        pstCallCtx->ucRetryEmcRegFlag = IMSA_FALSE;
        pstCallCtx->ucId = IMSA_NULL;
        pstCallCtx->ucCallEntityIndex = IMSA_NULL;

        return;
    }
    /* imsa���յ�SPM���͵�ORIG_REQ��Ϣ�������ظ���ORIG_CNF�����Բ���Ҫ���ϱ�ORIG_CNF�¼���
    ����IMSA���յ�ORIG_REQ��ʱ�򣬻���SPM�ϱ���ORIG�¼���������Ҫ֪ͨSPM RELEASE */
    pstCallEntity = IMSA_CallEntityGetUsedByImsCallId(IMSA_CALL_INVALID_ID);
    if (VOS_NULL_PTR != pstCallEntity)
    {
        IMSA_CallReleaseCallCommonProc(pstCallEntity, TAF_CS_CAUSE_SUCCESS);
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallErrRecord(IMSA_ERR_LOG_CALL_FAIL_REASON_SERVICE_NOT_AVAILABLE, VOS_NULL_PTR);
        #endif
    }

    return;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcTimeoutProtect
 Description    : ������ʱ����ʱ����

                  ������ʱ����ʱ��IMSA
                     - ����Ѿ������SPM���opId
                     - ����Ѿ������IMS���opId
 Input          : pTimerMsg     ��ʱ��ʱ����Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
      2.lihong 0015001     2013-09-30  Modify
*****************************************************************************/
VOS_VOID IMSA_CallProcTimeoutProtect(const VOS_VOID *pTimerMsg)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx      = IMSA_CallCtxGet();
    IMSA_CALL_ENTITY_STRU              *pstCallEntity   = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallProcTimeoutProtect is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcTimeoutProtect_ENUM, LNAS_ENTRY);

    (VOS_VOID)pTimerMsg;


    /* ���ݲ�ͬ����ظ�SPM */
    switch (pstCallCtx->stSpmMsg.ulSpmMsgId)
    {
    case ID_SPM_IMSA_CALL_ORIG_REQ:
        IMSA_CallProcOrigReqProtectTimeout();
        #if (FEATURE_ON == FEATURE_PTM)
        IMSA_CallErrRecord(IMSA_ERR_LOG_CALL_FAIL_REASON_REMOTE, VOS_NULL_PTR);
        #endif
        break;

    case ID_SPM_IMSA_CALL_SUPS_CMD_REQ:
        (VOS_VOID)IMSA_CallSendSpmSupsResultMsg(pstCallCtx->stSpmMsg.usClientId,
                                                pstCallCtx->stSpmMsg.ulOpId,
                                                pstCallCtx->stSpmMsg.ulCallId,
                                                MN_CALL_SS_RES_FAIL);
        break;

    case ID_SPM_IMSA_CALL_GET_CALL_INFO_REQ:
        IMSA_INFO_LOG("IMSA_CallProcTimeoutProtect: this command has handled by IMSA");
        TLPS_PRINT2LAYER_INFO(IMSA_CallProcTimeoutProtect_ENUM, LNAS_SUCC);
        break;

    case ID_SPM_IMSA_CALL_START_DTMF_REQ:
        IMSA_CallRcvImsStartDtmfProtectTimerExp();
        break;

    case ID_SPM_IMSA_CALL_STOP_DTMF_REQ:
        IMSA_CallRcvImsStopDtmfProtectTimerExp();
        break;

    case ID_SPM_IMSA_CALL_GET_CUDR_REQ:
        IMSA_INFO_LOG("IMSA_CallProcTimeoutProtect: this command is not supported by IMSA");
        TLPS_PRINT2LAYER_INFO(IMSA_CallProcTimeoutProtect_ENUM, IMSA_NOT_SUPPORT);
        break;

    case ID_SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ:
        (VOS_VOID)IMSA_CallSendSpmInviteNewPtptCnfMsg(pstCallCtx->stSpmMsg.usClientId,
                                                      pstCallCtx->stSpmMsg.ulOpId,
                                                      pstCallCtx->stSpmMsg.ulCallId,
                                                      TAF_CS_CAUSE_IMSA_TIMEOUT);

        pstCallEntity = IMSA_CallEntityGetUsedByImsCallId(IMSA_CALL_INVALID_ID);
        if (VOS_NULL_PTR != pstCallEntity)
        {
            IMSA_CallEntityFree(pstCallEntity);
        }
        break;
    case ID_SPM_IMSA_CALL_MODIFY_REQ:
         /* ��Ҫ֪ͨSPM �л�����ʧ�� */
        (VOS_VOID)IMSA_CallSendSpmModifyCnfMsg(pstCallCtx->stSpmMsg.usClientId,
                                                pstCallCtx->stSpmMsg.ulOpId,
                                                pstCallCtx->stSpmMsg.ulCallId,
                                                TAF_CS_CAUSE_IMSA_TIMEOUT);
        break;
    case ID_SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ:
        /* ��Ҫ֪ͨSPM �л�����ʧ�� */
        (VOS_VOID)IMSA_CallSendSpmAnswerRemoteModifyCnfMsg(pstCallCtx->stSpmMsg.usClientId,
                                                            pstCallCtx->stSpmMsg.ulOpId,
                                                            pstCallCtx->stSpmMsg.ulCallId,
                                                            TAF_CS_CAUSE_IMSA_TIMEOUT);
        break;
    case ID_SPM_IMSA_CALL_ECONF_DIAL_REQ:
        /* ��Ҫ֪ͨSPMrelease */
        pstCallEntity = IMSA_CallEntityGetUsedByImsCallId(IMSA_CALL_INVALID_ID);
        if (VOS_NULL_PTR != pstCallEntity)
        {
            IMSA_CallReleaseCallCommonProc(pstCallEntity, TAF_CS_CAUSE_SUCCESS);
        }
        break;
    case ID_SPM_IMSA_CALL_ECONF_ADD_USERS_REQ:
        (VOS_VOID)IMSA_CallSendSpmEconfAddUserCnfMsg(pstCallCtx->stSpmMsg.usClientId,
                                           pstCallCtx->stSpmMsg.ulOpId,
                                           TAF_CS_CAUSE_IMSA_TIMEOUT);
        break;
    default:
        IMSA_ERR_LOG1("IMSA_CallProcTimeoutProtect: invalid call request", pstCallCtx->stSpmMsg.ulSpmMsgId);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallProcTimeoutProtect_ENUM, LNAS_MSG_INVALID, pstCallCtx->stSpmMsg.ulSpmMsgId);
    }

    /* ����������� */
    IMSA_CallSpmMsgClear();
    IMSA_CallImsMsgClear();

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcTimeoutDtmfProtect
 Description    : DTMF������ʱ����ʱ����
 Input          : pTimerMsg     ��ʱ��ʱ����Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 0015001     2013-10-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallProcTimeoutDtmfProtect(const VOS_VOID *pTimerMsg)
{
    IMSA_CALL_DTMF_STATE_ENUM_UINT8     enDtmfState = IMSA_CALL_DTMF_STATE_BUTT;

    IMSA_INFO_LOG("IMSA_CallProcTimeoutDtmfProtect is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcTimeoutProtect_ENUM, LNAS_ENTRY);

    (VOS_VOID)pTimerMsg;

    enDtmfState = IMSA_CallGetDtmfState();
    if (enDtmfState == IMSA_CALL_DTMF_WAIT_START_CNF)
    {
        IMSA_CallRcvImsStartDtmfProtectTimerExp();
    }
    else if ((enDtmfState == IMSA_CALL_DTMF_WAIT_STOP_CNF)
            || (enDtmfState == IMSA_CALL_DTMF_WAIT_AUTO_STOP_CNF))
    {
        IMSA_CallRcvImsStopDtmfProtectTimerExp();
    }
    else
    {
        IMSA_WARN_LOG1("IMSA_CallProcTimeoutDtmfProtect: invalid dtmf state", enDtmfState);
        TLPS_PRINT2LAYER_WARNING1(IMSA_CallProcTimeoutProtect_ENUM, IMSA_STATE_ERROR, enDtmfState);
    }

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcTimeoutRedialMaxTime
 Description    : �ز����ʱ����ʱ����ʱ����
 Input          : pTimerMsg     ��ʱ��ʱ����Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 0015001     2013-12-23  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallProcTimeoutRedialMaxTime(const VOS_VOID *pTimerMsg)
{
    IMSA_INFO_LOG1("IMSA_CallProcTimeoutRedialMaxTime: timer para:",PS_GET_REL_TIMER_PARA(pTimerMsg));
    TLPS_PRINT2LAYER_INFO1(IMSA_CallProcTimeoutRedialMaxTime_ENUM, IMSA_TIMER_PARA, PS_GET_REL_TIMER_PARA(pTimerMsg));

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcTimeoutRedialIntervel
 Description    : �ز������ʱ����ʱ����
 Input          : pTimerMsg     ��ʱ��ʱ����Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 0015001     2013-12-23  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallProcTimeoutRedialIntervel(const VOS_VOID *pTimerMsg)
{
    VOS_UINT16                          usTimerPara         = IMSA_NULL;
    VOS_UINT8                           ucCallEntityIndex   = IMSA_NULL;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx          = IMSA_CallCtxGet();
    IMSA_CALL_ENTITY_STRU              *pstCallEntity       = VOS_NULL_PTR;
    SPM_IMSA_CALL_ORIG_REQ_STRU         stCallOrigReq       = {0};
    VOS_UINT32                          ulResult            = VOS_FALSE;

    usTimerPara = (VOS_UINT16)PS_GET_REL_TIMER_PARA(pTimerMsg);

    IMSA_INFO_LOG1("IMSA_CallProcTimeoutRedialIntervel: timer para:", usTimerPara);
    TLPS_PRINT2LAYER_INFO1(IMSA_CallProcTimeoutRedialIntervel_ENUM, IMSA_TIMER_PARA, usTimerPara);

    ucCallEntityIndex = (VOS_UINT8)usTimerPara;

    /* ʶ��CALLʵ�������ĺϷ��� */
    if (ucCallEntityIndex >= IMSA_CALL_MAX_NUM)
    {
        IMSA_WARN_LOG("IMSA_CallProcTimeoutRedialIntervel: call index illegal");
        TLPS_PRINT2LAYER_WARNING(IMSA_CallProcTimeoutRedialIntervel_ENUM, IMSA_CALL_ID_ERROR);
        IMSA_StopTimer(&pstCallCtx->stRedialMaxTimer);
        return ;
    }

    pstCallEntity = &pstCallCtx->astCallEntity[ucCallEntityIndex];

    /* ʶ��CALL״̬�ĺϷ��� */
    if ((IMSA_CALL_STATUS_DIALING != pstCallEntity->enStatus)
        && (IMSA_CALL_STATUS_TRYING != pstCallEntity->enStatus))
    {
        IMSA_WARN_LOG("IMSA_CallProcTimeoutRedialIntervel: call state illegal");
        TLPS_PRINT2LAYER_WARNING(IMSA_CallProcTimeoutRedialIntervel_ENUM, IMSA_STATE_ERROR);
        IMSA_StopTimer(&pstCallCtx->stRedialMaxTimer);
        return ;
    }

    /* �ز�������1 */
    pstCallEntity->ucRedialTimes++;

    IMSA_INFO_LOG1("IMSA_CallProcTimeoutRedialIntervel redial times:", pstCallEntity->ucRedialTimes);
    TLPS_PRINT2LAYER_INFO1(IMSA_CallProcTimeoutRedialIntervel_ENUM, 1, pstCallEntity->ucRedialTimes);

    /* ȡ�洢��ORIG REQ��Ϣ���ٴη�����н������� */
    stCallOrigReq.ulMsgId       = ID_SPM_IMSA_CALL_ORIG_REQ;
    stCallOrigReq.usClientId      = pstCallEntity->stSpmMsg.usClientId;
    stCallOrigReq.ucOpId          = (MN_OPERATION_ID_T)pstCallEntity->stSpmMsg.ulOpId;
    stCallOrigReq.stOrig        = pstCallEntity->stSpmMsg.stParam.stOrigParam;
    ulResult = IMSA_CallSendImsMsgDial(IMSA_CALL_INVALID_ID, &stCallOrigReq);
    if (VOS_TRUE == ulResult)
    {
        /* ����������ʱ�� */
        IMSA_StartTimer(&pstCallCtx->stProctectTimer);

        IMSA_MEM_CPY_S( &pstCallCtx->stSpmMsg,
                        sizeof(IMSA_CALL_SPM_MSG_STRU),
                        &pstCallEntity->stSpmMsg,
                        sizeof(IMSA_CALL_SPM_MSG_STRU));
    }
    else
    {
        IMSA_WARN_LOG("IMSA_CallProcTimeoutRedialIntervel: send ims dial failed");
        TLPS_PRINT2LAYER_WARNING(IMSA_CallProcTimeoutRedialIntervel_ENUM, LNAS_FAIL);

        IMSA_CallInterruptRedial(pstCallEntity);
    }

    return ;
}


/*****************************************************************************
 Function Name  : IMSA_CallProcTimeoutResReady
 Description    : ��ԴԤ�����������ʱ����ʱ����
 Input          : pTimerMsg     ��ʱ��ʱ����Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallProcTimeoutResReady(const VOS_VOID *pTimerMsg)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();
    VOS_UINT32 i = 0;
    IMSA_CALL_CALL_REASON_RESOURCE_RESULT_ENUM_UINT8 enResResult = IMSA_CALL_CALL_REASON_RESOURCE_FAILED;

    IMSA_INFO_LOG("IMSA_CallProcTimeoutResReady is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcTimeoutResReady_ENUM, LNAS_ENTRY);

    (VOS_VOID)pTimerMsg;

    /**
     * �ȴ���ԴԤ����ʱ����ʱ����
     *
     * ����Ŀǰ��ʵ����D2 IMS�ϱ���ԴԤ�������
     * IMSA���������ȴ���ԴԤ���ɹ���ʱ����
     * ����ڵ�һ�����е���ԴԤ����δ��Ӧ֮ǰ�����ڶ�����ԴԤ��������
     * ��IMSA�Ĵ���ֻ��ˢ�¶�ʱ����
     *
     * ����ܵ��ȴ���Դ��ʱ����ʱ��Ĵ���Ŀǰ��
     * �������к��У�����ú������ڵȴ���ԴԤ����
     * ��ظ��ú�����ԴԤ��ʧ��
     *
     * Ŀǰ�ⲿ�ֵĴ����Ǹ��򻯴���������Ҫ���Ż�
     *
     */

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
            (VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpNeedSendResResult))
        {
            /* ֻ�б��еĳ����£����п��ܴ��ڳ������յ�IMS����ԴԤ������֮ǰ���� */
            if (MN_CALL_DIR_MO == pstCallCtx->astCallEntity[i].enDir)
            {
                enResResult = IMSA_CallIsResourceReady(&pstCallCtx->astCallEntity[i]);
                //coverity[unchecked_value]
            }
            else
            {
                /* Ϊ����ڶ�·�绰����ʱ������δ�·�MODIFY������MT CALLʱ�����ཨ�����ر�IMS�������̿죬
                ����ԴԤ����ʱ����ʱ�������ж��Ƿ��ж�Ӧ���͵ĳ��ش��ڣ�������ڣ���֪ͨIMS��ԴԤ�����Ϊ
                �ɹ� */

                enResResult = IMSA_CALL_CALL_REASON_RESOURCE_FAILED;

                if (((IMSA_CALL_TYPE_VOICE == pstCallCtx->astCallEntity[i].enType) ||
                     (IMSA_CALL_TYPE_EMC == pstCallCtx->astCallEntity[i].enType)) &&
                    (IMSA_TRUE == IMSA_CONN_HasActiveVoicePdp()))
                {
                    enResResult = IMSA_CALL_CALL_REASON_RESOURCE_READY;
                }

                if ((IMSA_CALL_TYPE_VIDEO == pstCallCtx->astCallEntity[i].enType) &&
                    (IMSA_TRUE == IMSA_CONN_HasActiveVoicePdp()) &&
                    (IMSA_TRUE == IMSA_CONN_HasActiveVideoPdp()))
                {
                    enResResult = IMSA_CALL_CALL_REASON_RESOURCE_READY;
                }

            }
            //coverity[unchecked_value]
            (VOS_VOID)IMSA_CallSendImsMsgResRsp(pstCallCtx->astCallEntity[i].ucImscallId,
                                                pstCallCtx->astCallEntity[i].ulResRspOpId,
                                                pstCallCtx->astCallEntity[i].ulDialogId,
                                                enResResult);

            pstCallCtx->astCallEntity[i].bitOpNeedSendResResult = IMSA_FALSE;

            if (IMSA_CALL_CALL_REASON_RESOURCE_FAILED == enResResult)
            {
                /* �������ԴԤ��ʧ�ܣ���¼��ԴԤ����ʱ����ʱ�ı�ʶ */
                pstCallCtx->astCallEntity[i].ucTqosExpFlag = VOS_TRUE;
            }

            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_CallErrRecord(IMSA_ERR_LOG_CALL_FAIL_REASON_RES_READY_FAIL, VOS_NULL_PTR);
            #endif
        }
    }

    return ;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcTimeoutDtmfDuration
 Description    : DTMF DURATION��ʱ����ʱ����
 Input          : pTimerMsg     ��ʱ��ʱ����Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010      2013-10-14  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallProcTimeoutDtmfDuration(const VOS_VOID *pTimerMsg)
{
    VOS_UINT32                          ulResult    = VOS_FALSE;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx  = IMSA_CallCtxGet();

    (VOS_VOID)pTimerMsg;

    /* �ж�״̬�Ƿ��쳣 */
    if (IMSA_CallGetDtmfState() != IMSA_CALL_DTMF_WAIT_TIME_OUT)
    {
        IMSA_WARN_LOG("IMSA_CallProcTimeoutDtmfDuration: Dtmf State Error!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CallProcTimeoutDtmfDuration_ENUM, IMSA_STATE_ERROR);
        return;
    }

    /* ���жϵ�ǰ�Ƿ�������DTMF���Լ��û�����ĺ���ID�Ƿ���Է���DTMF */
    ulResult    = IMSA_CallCheckUserDtmfCallId(pstCallCtx->stDtmfCtx.stCurrentDtmf.ucCallId);
    if (TAF_CS_CAUSE_SUCCESS != ulResult)
    {
        IMSA_WARN_LOG("IMSA_CallProcTimeoutDtmfDuration: no active call!");
        TLPS_PRINT2LAYER_WARNING(IMSA_CallProcTimeoutDtmfDuration_ENUM, IMSA_CALL_ID_ERROR);
        IMSA_CallClearDtmfInfo(TAF_CS_CAUSE_UNKNOWN);

        return;
    }

    if (VOS_TRUE != IMSA_CallSendImsMsgStopDtmf(pstCallCtx->stDtmfCtx.stCurrentDtmf.ucCallId,
                                                pstCallCtx->stDtmfCtx.stCurrentDtmf.cKey))
    {
        IMSA_ERR_LOG("IMSA_CallProcTimeoutDtmfDuration: IMSA_CallSendImsMsgStopDtmf failed!");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallProcTimeoutDtmfDuration_ENUM, LNAS_FAIL);
        IMSA_CallClearDtmfInfo(TAF_CS_CAUSE_UNKNOWN);

        return ;
    }

    /* ���ͳɹ�������DTMF״̬ */
    IMSA_StartTimer(&pstCallCtx->stProctectTimer);

    IMSA_CallFillCurrentDtmfInfo(   pstCallCtx->stDtmfCtx.stCurrentDtmf.ucCallId,
                                    pstCallCtx->stDtmfCtx.stCurrentDtmf.cKey,
                                    0,
                                    pstCallCtx->stDtmfCtx.stCurrentDtmf.usClientId,
                                    pstCallCtx->stDtmfCtx.stCurrentDtmf.ucSpmOpId);

    IMSA_CallSetDtmfState(IMSA_CALL_DTMF_WAIT_AUTO_STOP_CNF);

    return;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcEmcTcallExpWhenEmcSrvEstablishSucc
 Description    : IMS EMC�������ɹ�������Tcall��ʱ����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310      2015-09-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallProcEmcTcallExpWhenEmcSrvEstablishSucc(VOS_VOID)
{
    VOS_UINT32  i = 0;
    VOS_UINT32  ulIsTimeOut  = IMSA_FALSE;
    IMSA_CALL_MANAGER_STRU   *pstCallCtx   = IMSA_CallCtxGet();

    IMSA_StopTimer(&pstCallCtx->stRedialMaxTimer);

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed)
            && (IMSA_CALL_TYPE_EMC == pstCallCtx->astCallEntity[i].enType))
        {
            if(IMSA_CALL_STATUS_DIALING == pstCallCtx->astCallEntity[i].enStatus)
            {
                ulIsTimeOut = IMSA_TRUE;
                break;
            }
        }
    }

    if(IMSA_CALL_MAX_NUM == i)
    {
        return;
    }

    if(ulIsTimeOut)
    {
        (VOS_VOID)IMSA_CallImsCmdRel(pstCallCtx->astCallEntity[i].ucImscallId, IMSA_IMS_CALL_REL_CAUSE_TCALL_EXPIR);
    }

    pstCallCtx->ucIsTcallTimeOutProc = VOS_TRUE;

    return;
}


/*****************************************************************************
 Function Name  : IMSA_CallProcTimeoutEmcTCall
 Description    : ������Tcall������ʱ����ʱ����
 Input          : pTimerMsg     ��ʱ��ʱ����Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310      2015-09-01  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallProcTimeoutEmcTCall(const VOS_VOID *pTimerMsg)
{
    if (IMSA_FALSE == IMSA_IsImsEmcServiceEstablishSucc())
    {
        IMSA_StopImsEmcService();
    }
    else
    {
        IMSA_CallProcEmcTcallExpWhenEmcSrvEstablishSucc();
    }
}


/*****************************************************************************
 Function Name  : IMSA_CallProcTimeoutTCall
 Description    : CMCC����Tcall��ʱ����ʱ����
 Input          : pTimerMsg     ��ʱ��ʱ����Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.mengchao 00277840      2014-08-22  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallProcTimeoutTCall(const VOS_VOID *pTimerMsg)
{
    VOS_UINT32 i = 0;
    VOS_UINT32 ulIsDialingTimeOut = IMSA_FALSE;
    IMSA_CALL_MANAGER_STRU   *pstCallCtx      = IMSA_CallCtxGet();

    IMSA_StopTimer(&pstCallCtx->stRedialMaxTimer);
    IMSA_StopTimer(&pstCallCtx->stRedialIntervelTimer);

    for(i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if(VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed)
        {
            if(IMSA_CALL_STATUS_DIALING == pstCallCtx->astCallEntity[i].enStatus)
            {
                ulIsDialingTimeOut = IMSA_TRUE;
                break;
            }
            else if(IMSA_CALL_STATUS_IDLE == pstCallCtx->astCallEntity[i].enStatus)
            {
                break;
            }
        }
    }

    if(IMSA_CALL_MAX_NUM == i)
    {
        IMSA_ERR_LOG("IMSA_CallProcTimeoutTCall: Call Entity not found.");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallProcTimeoutCMCCTCall_ENUM, IMSA_CALL_NOT_EXIST);
        return;
    }

    if(ulIsDialingTimeOut)
    {
        IMSA_INFO_LOG1("IMSA_CallProcTimeoutTCall: Hang up call id: ", pstCallCtx->astCallEntity[i].ucImscallId);
        TLPS_PRINT2LAYER_INFO1(IMSA_CallProcTimeoutCMCCTCall_ENUM, IMSA_CALL_ID, pstCallCtx->astCallEntity[i].ucImscallId);
        (VOS_VOID)IMSA_CallImsCmdRel(pstCallCtx->astCallEntity[i].ucImscallId,
                                    IMSA_IMS_CALL_REL_CAUSE_TCALL_EXPIR);
    }
    pstCallCtx->ucIsTcallTimeOutProc = VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_StartTcallTimer
 Description    : ����CMCC����Tcall��ʱ��
 Input          : pstCallEntity
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.mengchao 00277840      2014-08-22  Draft Enact
      2.wangchen 00209181       2015-07-02  Modify:�����ƶ����ư汾��TCALL��ʱ��ҲȥCS���ز�
*****************************************************************************/
VOS_VOID IMSA_StartTcallTimer(const IMSA_CALL_ENTITY_STRU *pstCallEntity)
{
    IMSA_CALL_MANAGER_STRU    *pstCallCtx = IMSA_CallCtxGet();

    if (IMSA_CALL_TYPE_EMC == pstCallEntity->enType)
    {
        /* ������������Tcall��ʱ�� */
        pstCallCtx->stEmcTcallTimer.ulTimerLen = IMSA_GetConfigParaAddress()->stCMCCCustomReq.ulTcallTimerLen;
        pstCallCtx->stEmcTcallTimer.usPara = pstCallEntity->ucCallEntityIndex;
        IMSA_StartTimer(&pstCallCtx->stEmcTcallTimer);
    }
    else
    {
        /* ������ͨ���л���Ƶ����Tcall��ʱ�� */
        pstCallCtx->stNormalTcallTimer.ulTimerLen = IMSA_GetConfigParaAddress()->stCMCCCustomReq.ulTcallTimerLen;
        pstCallCtx->stNormalTcallTimer.usPara = pstCallEntity->ucCallEntityIndex;
        IMSA_StartTimer(&pstCallCtx->stNormalTcallTimer);
    }
}
/*****************************************************************************
 Function Name  : IMSA_CallProcIntraMsgEmcCallSrvStatus
 Description    : ��������״̬�仯�Ĵ���
 Input          : pMsg        ����״̬�仯֪ͨ
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallProcIntraMsgEmcCallSrvStatusWhenNoSrv
(
    const IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32          enNoSrvCause
)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();
    IMSA_CALL_ENTITY_STRU              *pstCallEntity       = VOS_NULL_PTR;

    /* ���ý����ر��ͷţ��ҵ�ǰ���е绰�ĳ����£���Ҫ������ʱ��������Ѿ�û�е绰���ڣ���ֱ�Ӷ���*/
    if (IMSA_CALL_NO_SRV_CAUSE_MEDIA_PDP_RELEASE == enNoSrvCause)
    {
        if (IMSA_TRUE == IMSA_IsExistEmcCall())
        {
            IMSA_StartTimer(&pstCallCtx->stEmcMediaLostRelCallTimer);
        }
        return;
    }

    /* �������������ʹ�ã������ͷ����н����Ự.
       ����ǻ���Ľ����������ڻ�û�з���CALLʵ�壬����ʵ���ϲ���
       ����IMSЭ��ջ�ͷŽ����� */
    if ((IMSA_CALL_NO_SRV_CAUSE_PORT_CFG_FAIL == enNoSrvCause)
        || (IMSA_CALL_NO_SRV_CAUSE_SET_DEVICE_FAIL == enNoSrvCause)
        || (IMSA_CALL_NO_SRV_CAUSE_SET_START_FAIL == enNoSrvCause)
        || (IMSA_CALL_NO_SRV_CAUSE_SET_VOLUME_FAIL == enNoSrvCause)
        || (IMSA_CALL_NO_SRV_CAUSE_SAMPLE_RATE_FAIL == enNoSrvCause)
        || (IMSA_CALL_NO_SRV_CAUSE_TI_START_EXPIRED == enNoSrvCause)
        || (IMSA_CALL_NO_SRV_CAUSE_NON_SRVCC_RAT_CHANGE == enNoSrvCause))
    {
        (VOS_VOID)IMSA_CallCmdRelAllEmc(IMSA_TRUE, enNoSrvCause);
    }
    else
    {
        (VOS_VOID)IMSA_CallCmdRelAllEmc(IMSA_FALSE, enNoSrvCause);
    }

    /**
     * �����ǰ�����˷���������������ֱ�ӻظ�SPMʧ�ܣ�
     * ����Ҳ�п��ܻ�������������ֳ�����ҳ��Ҫ�ظ�SPM�����
     * Ŀǰ��ʱ�ȴ�������Ľ������������������Ҫ��Ͼ����������ֱ���
     */
    if ((IMSA_OP_TRUE == pstCallCtx->stSpmMsg.bitOpSpmMsg) &&
        (ID_SPM_IMSA_CALL_ORIG_REQ == pstCallCtx->stSpmMsg.ulSpmMsgId) &&
        (MN_CALL_TYPE_EMERGENCY == pstCallCtx->stSpmMsg.stParam.stOrigParam.enCallType))
    {
        /* �����յ�SPM���͵�ORIG_REQ��Ϣ���Ѿ���SPM���͹�ORIG_CNF��ͬʱ�ϱ���ORIG�¼�������
        ����Ҫ�ٻظ�ORIG_CNF��������Ҫ�ϱ�RELEASE�¼� */
        pstCallEntity = IMSA_CallEntityGetUsedByImsCallId(IMSA_CALL_INVALID_ID);

        if (pstCallEntity)
        {
            #if (FEATURE_ON == FEATURE_PTM)
            IMSA_CallErrRecord(IMSA_ERR_LOG_CALL_FAIL_REASON_SERVICE_NOT_AVAILABLE, pstCallEntity);
            #endif
            IMSA_CallReleaseCallCommonProc(pstCallEntity, TAF_CS_CAUSE_SUCCESS);
        }

        IMSA_CallSpmMsgClear();
    }
    return;
}
/*****************************************************************************
 Function Name  : IMSA_CallProcIntraMsgEmcCallSrvStatus
 Description    : ��������״̬�仯�Ĵ���
 Input          : pMsg        ����״̬�仯֪ͨ
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallProcIntraMsgEmcCallSrvStatusWhenNorSrv
(
    VOS_VOID
)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx = IMSA_CallCtxGet();
    SPM_IMSA_CALL_ORIG_REQ_STRU *pstAppReq = VOS_NULL_PTR;
    IMSA_CALL_ENTITY_STRU              *pstCallEntity       = VOS_NULL_PTR;
    SPM_IMSA_CALL_ORIG_REQ_STRU         stCallOrigReq       = {0};
    VOS_UINT32                          ulResult            = VOS_FALSE;
    TAF_CS_CAUSE_ENUM_UINT32            enSpmErr        = IMSA_NULL;
    VOS_UINT8                           i= 0;

    /* �������������ã����Ƿ��л���Ľ������н�����������У���������н������� */

    if ((IMSA_OP_TRUE == pstCallCtx->stSpmMsg.bitOpSpmMsg) &&
        (ID_SPM_IMSA_CALL_ORIG_REQ == pstCallCtx->stSpmMsg.ulSpmMsgId) &&
        (MN_CALL_TYPE_EMERGENCY == pstCallCtx->stSpmMsg.stParam.stOrigParam.enCallType))
    {
        pstAppReq = (SPM_IMSA_CALL_ORIG_REQ_STRU*)IMSA_MEM_ALLOC(sizeof(SPM_IMSA_CALL_ORIG_REQ_STRU));
        if(VOS_NULL_PTR == pstAppReq)
        {
            IMSA_ERR_LOG("IMSA_CallProcIntraMsgEmcCallSrvStatusWhenNorSrv: Mem Alloc fail!");
            TLPS_PRINT2LAYER_ERROR(IMSA_CallProcIntraMsgEmcCallSrvStatusWhenNorSrv_ENUM, LNAS_NULL_PTR);
            return;
        }
        pstAppReq->ulMsgId      = ID_SPM_IMSA_CALL_ORIG_REQ;
        pstAppReq->usClientId   = pstCallCtx->stSpmMsg.usClientId;
        pstAppReq->ucOpId         = (MN_OPERATION_ID_T)pstCallCtx->stSpmMsg.ulOpId;
        pstAppReq->stOrig       = pstCallCtx->stSpmMsg.stParam.stOrigParam;

        ulResult = IMSA_CallSendImsMsgDial(IMSA_CALL_INVALID_ID, pstAppReq);
        if (VOS_TRUE == ulResult)
        {
            for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
            {
                if ((VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
                    (IMSA_CALL_TYPE_EMC == pstCallCtx->astCallEntity[i].enType))
                {
                    pstCallEntity = &pstCallCtx->astCallEntity[i];

                    /* ���津���˺��ж�Ӧ��SPM���������б��ܾ�����Ҫ����ע���������ʱʹ�� */
                    IMSA_MEM_CPY_S( &pstCallEntity->stSpmMsg,
                                    sizeof(IMSA_CALL_SPM_MSG_STRU),
                                    &pstCallCtx->stSpmMsg,
                                    sizeof(IMSA_CALL_SPM_MSG_STRU));
                    break;
                }
            }

            /* ����������ʱ�� */
            IMSA_StartTimer(&pstCallCtx->stProctectTimer);
        }
        else
        {
            /* �������Tcall�������У���Ҫֹͣ */
            if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stEmcTcallTimer))
            {
                IMSA_StopTimer(&pstCallCtx->stEmcTcallTimer);
            }

            /* ֪ͨSPM RELEASE�¼� */
            /* ���ҽ������еĺ���ʵ�� */
            for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
            {
                if ((VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
                    (IMSA_CALL_TYPE_EMC == pstCallCtx->astCallEntity[i].enType))
                {
                    IMSA_CallReleaseCallCommonProc(&(pstCallCtx->astCallEntity[i]), TAF_CS_CAUSE_IMSA_ERROR);
                    IMSA_CallSpmMsgClear();
                    break;
                }
            }
        }
        IMSA_MEM_FREE(pstAppReq);
        return;
    }

    /* ����ǽ������У��յ�#380�����·������ע�ᣬ���ҳɹ��ĳ���������Ҫ���·������ʵ�� */
    if (IMSA_TRUE == pstCallCtx->ucRetryEmcRegFlag)
    {
        IMSA_ERR_LOG1("IMSA_CallProcIntraMsgEmcCallSrvStatus: pstCallCtx->ucRetryEmcRegFlag = ",pstCallCtx->ucRetryEmcRegFlag);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallProcIntraMsgEmcCallSrvStatusWhenNorSrv_ENUM, 1, pstCallCtx->ucRetryEmcRegFlag);
        pstCallEntity = &pstCallCtx->astCallEntity[pstCallCtx->ucCallEntityIndex];

        /* ȡ�洢��ORIG REQ��Ϣ���ٴη�����н������� */
        stCallOrigReq.ulMsgId       = ID_SPM_IMSA_CALL_ORIG_REQ;
        stCallOrigReq.usClientId      = pstCallEntity->stSpmMsg.usClientId;
        stCallOrigReq.ucOpId          = (MN_OPERATION_ID_T)pstCallEntity->stSpmMsg.ulOpId;
        stCallOrigReq.stOrig        = pstCallEntity->stSpmMsg.stParam.stOrigParam;
        ulResult = IMSA_CallSendImsMsgDial(IMSA_CALL_INVALID_ID, &stCallOrigReq);
        if (VOS_TRUE == ulResult)
        {
            /* ����������ʱ�� */
            IMSA_StartTimer(&pstCallCtx->stProctectTimer);

            IMSA_MEM_CPY_S( &pstCallCtx->stSpmMsg,
                            sizeof(IMSA_CALL_SPM_MSG_STRU),
                            &pstCallEntity->stSpmMsg,
                            sizeof(IMSA_CALL_SPM_MSG_STRU));

            /* ��Ҫ�����ԭ��ֵ������CALL�ͷ�ʱ�ϱ�RELEASE�¼�ʱЯ��ԭ��ֵ����� */
            pstCallEntity->bitOpErrorInfo = IMSA_OP_FALSE;

            IMSA_MEM_SET_S( &pstCallEntity->stImsError,
                            sizeof(IMSA_IMS_CALL_ERROR_STRU),
                            0,
                            sizeof(IMSA_IMS_CALL_ERROR_STRU));
        }
        else
        {
            /* ��IMS����ԭ��ֵת��ΪSPM����ԭ��ֵ */
            /* �޸ĺ������ */
            enSpmErr = IMSA_CallTransImsErr2SpmErr(&pstCallEntity->stImsError.stErrorCode);

            pstCallEntity->ucSpmcallId = pstCallCtx->ucId;

            IMSA_CallReleaseCallCommonProc(pstCallEntity, enSpmErr);

            /* ����������ע���ʶ�Ȳ��� */
            pstCallCtx->ucRetryEmcRegFlag = IMSA_FALSE;
            pstCallCtx->ucId = IMSA_NULL;
            pstCallCtx->ucCallEntityIndex = IMSA_NULL;
        }
        IMSA_ERR_LOG1("IMSA_CallProcIntraMsgEmcCallSrvStatus: pstCallCtx->ucRetryEmcRegFlag = ",pstCallCtx->ucRetryEmcRegFlag);
        TLPS_PRINT2LAYER_ERROR1(IMSA_CallProcIntraMsgEmcCallSrvStatusWhenNorSrv_ENUM, 2, pstCallCtx->ucRetryEmcRegFlag);
    }
    return;
}
/*****************************************************************************
 Function Name  : IMSA_CallProcIntraMsgEmcCallSrvStatus
 Description    : ��������״̬�仯�Ĵ���
 Input          : pMsg        ����״̬�仯֪ͨ
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcIntraMsgEmcCallSrvStatus(const VOS_VOID *pMsg)
{
    IMSA_EMC_CALL_SRV_STATUS_IND_STRU *pstSrvStatus = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_CallProcIntraMsgEmcCallSrvStatus is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcIntraMsgEmcCallSrvStatus_ENUM, LNAS_ENTRY);

    pstSrvStatus = (IMSA_EMC_CALL_SRV_STATUS_IND_STRU *)pMsg;

    if (IMSA_CALL_SERVICE_STATUS_NO_SERVICE == pstSrvStatus->enCallSrvStatus)
    {
        IMSA_CallProcIntraMsgEmcCallSrvStatusWhenNoSrv(pstSrvStatus->enNoSrvCause);
    }
    else if (IMSA_CALL_SERVICE_STATUS_NORMAL_SERVICE == pstSrvStatus->enCallSrvStatus)
    {
        IMSA_CallProcIntraMsgEmcCallSrvStatusWhenNorSrv();
    }
    else
    {
        IMSA_ERR_LOG("IMSA_CallProcIntraMsgEmcCallSrvStatus: invalid srv status");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallProcIntraMsgEmcCallSrvStatus_ENUM, IMSA_STATE_ERROR);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcIntraMsgEmcCallSrvStatus
 Description    : ��ͨ����״̬�仯�Ĵ���
 Input          : pMsg        ����״̬�仯֪ͨ
 Output         : VOS_VOID
 Return Value   : ������

 History        :
      1.liuhua 212067      2013-07-18  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcIntraMsgNrmCallSrvStatus(const VOS_VOID *pMsg)
{
    IMSA_NRM_CALL_SRV_STATUS_IND_STRU *pstSrvStatus = VOS_NULL_PTR;
    IMSA_CALL_MANAGER_STRU    *pstCallCtx = IMSA_CallCtxGet();

    IMSA_INFO_LOG("IMSA_CallProcIntraMsgNrmCallSrvStatus is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallProcIntraMsgNrmCallSrvStatus_ENUM, LNAS_ENTRY);

    if (VOS_NULL_PTR == pMsg)
    {
        IMSA_ERR_LOG("IMSA_CallProcIntraMsgNrmCallSrvStatus: NULL message");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallProcIntraMsgNrmCallSrvStatus_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    pstSrvStatus = (IMSA_NRM_CALL_SRV_STATUS_IND_STRU *)pMsg;

    if (IMSA_CALL_SERVICE_STATUS_NO_SERVICE == pstSrvStatus->enCallSrvStatus)
    {
        /* �����SRVCC�������յ�NO SERVOCE ����Ӧ��ȥ�Ҷϵ绰��SRVCC�ɹ���IMS���Լ��Ҷϣ�SRVCCʧ�ܣ����ز� */
        if ((IMSA_CALL_NO_SRV_CAUSE_NON_SRVCC_RAT_CHANGE == pstSrvStatus->enNoSrvCause) &&
            (IMSA_TRUE == IMSA_CallGetSrvccFlag()))
        {
            return VOS_TRUE;
        }
        /* ���ý����ر��ͷţ��ҵ�ǰ���е绰�ĳ����£���Ҫ������ʱ��������Ѿ�û�е绰���ڣ���ֱ�Ӷ���*/
        if (IMSA_CALL_NO_SRV_CAUSE_MEDIA_PDP_RELEASE == pstSrvStatus->enNoSrvCause)
        {
            if (IMSA_TRUE == IMSA_IsExistNormCall())
            {
                IMSA_StartTimer(&pstCallCtx->stNormMediaLostRelCallTimer);
            }
            return VOS_TRUE;
        }
        /* �����ͨ������ʹ�ã������ͷ�������ͨ�Ự */
        if ((IMSA_CALL_NO_SRV_CAUSE_PORT_CFG_FAIL == pstSrvStatus->enNoSrvCause)
            || (IMSA_CALL_NO_SRV_CAUSE_SET_DEVICE_FAIL == pstSrvStatus->enNoSrvCause)
            || (IMSA_CALL_NO_SRV_CAUSE_SET_START_FAIL == pstSrvStatus->enNoSrvCause)
            || (IMSA_CALL_NO_SRV_CAUSE_SET_VOLUME_FAIL == pstSrvStatus->enNoSrvCause)
            || (IMSA_CALL_NO_SRV_CAUSE_SAMPLE_RATE_FAIL == pstSrvStatus->enNoSrvCause)
            || (IMSA_CALL_NO_SRV_CAUSE_TI_START_EXPIRED == pstSrvStatus->enNoSrvCause)
            || (IMSA_CALL_NO_SRV_CAUSE_NON_SRVCC_RAT_CHANGE == pstSrvStatus->enNoSrvCause))
        {
            (VOS_VOID)IMSA_CallCmdRelAllNormal(IMSA_TRUE, pstSrvStatus->enNoSrvCause);
        }
        else
        {
            (VOS_VOID)IMSA_CallCmdRelAllNormal(IMSA_FALSE, pstSrvStatus->enNoSrvCause);
        }
    }
    else if (IMSA_CALL_SERVICE_STATUS_NORMAL_SERVICE == pstSrvStatus->enCallSrvStatus)
    {
        /* �����ͨ������ã������κ����⴦�� */
    }
    else
    {
        IMSA_ERR_LOG("IMSA_CallProcIntraMsgNrmCallSrvStatus: invalid srv status");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallProcIntraMsgNrmCallSrvStatus_ENUM, IMSA_STATE_ERROR);
    }

    return VOS_TRUE;
}
/*****************************************************************************
 Function Name  : IMSA_TransHifiCauseToImsaCause()
 Description    : ��HIFI�Ĵ���ԭ��ֵת��ΪIMSA�Ĵ���ԭ��ֵ
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-22  Draft Enact
*****************************************************************************/
IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32 IMSA_TransHifiCauseToImsaCause
(
    VC_IMSA_EXCEPTION_CAUSE_ENUM_UINT32 enCause
)
{
    switch(enCause)
    {
        case VC_IMSA_EXCEPTION_CAUSE_PORT_CFG_FAIL:
            return IMSA_CALL_NO_SRV_CAUSE_PORT_CFG_FAIL;

        case VC_IMSA_EXCEPTION_CAUSE_SET_DEVICE_FAIL:
            return IMSA_CALL_NO_SRV_CAUSE_SET_DEVICE_FAIL;

        case VC_IMSA_EXCEPTION_CAUSE_SET_START_FAIL:
            return IMSA_CALL_NO_SRV_CAUSE_SET_START_FAIL;

        case VC_IMSA_EXCEPTION_CAUSE_SET_VOLUME_FAIL:
            return IMSA_CALL_NO_SRV_CAUSE_SET_VOLUME_FAIL;

        case VC_IMSA_EXCEPTION_CAUSE_SAMPLE_RATE_FAIL:
            return IMSA_CALL_NO_SRV_CAUSE_SAMPLE_RATE_FAIL;

        case VC_IMSA_EXCEPTION_CAUSE_TI_START_EXPIRED:
            return IMSA_CALL_NO_SRV_CAUSE_TI_START_EXPIRED;

        default:
            return IMSA_CALL_NO_SRV_CAUSE_HIFI_EXCEPTION;
    }
}

/*****************************************************************************
 Function Name  : IMSA_ProcHifiExceptionNtf()
 Description    : HIFI�쳣��Ϣ������
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-07-22  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcHifiExceptionNtf(VOS_VOID *pRcvMsg)
{
    VC_IMSA_HIFI_EXCEPTION_NTF_STRU    *pstHifiExption = VOS_NULL_PTR;

    pstHifiExption = (VC_IMSA_HIFI_EXCEPTION_NTF_STRU *)pRcvMsg;

    if (VC_IMSA_EXCEPTION_CAUSE_STARTED == pstHifiExption->enCause)
    {
        IMSA_NORM_LOG("IMSA_ProcHifiExceptionNtf,hifi already started!");
        TLPS_PRINT2LAYER_INFO(IMSA_ProcHifiExceptionNtf_ENUM, IMSA_EXISTED);
        return ;
    }

    /* ֪ͨCALLģ��������������޷���״̬����Ҫ�ͷ���ͨCALL */
    IMSA_SRV_SndNrmCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                    IMSA_TransHifiCauseToImsaCause(pstHifiExption->enCause));

    /* ֪ͨCALLģ�������������޷���״̬����Ҫ�ͷŽ���CALL */
    IMSA_SRV_SndEmcCallSrvStatusInd(IMSA_CALL_SERVICE_STATUS_NO_SERVICE,
                                    IMSA_TransHifiCauseToImsaCause(pstHifiExption->enCause));
}

/*****************************************************************************
 Function Name  : IMSA_CallSrvccSuccProcSupsCmd()
 Description    : SRVCC�ɹ��������Sups����
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.xiongxianghui 00253310      2015-12-28  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallSrvccSuccProcSupsCmd(VOS_VOID)
{
    IMSA_CALL_MANAGER_STRU *pstCallCtx     = IMSA_CallCtxGet();
    SPM_IMSA_CALL_SUPS_CMD_REQ_STRU  *pstCallSupsCmdReq  = VOS_NULL_PTR;

    /* ���֮ǰû�б����SPM�����ֱ���˳� */
    if (IMSA_OP_FALSE == pstCallCtx->stSpmMsg.bitOpSpmMsg)
    {
        return;
    }

    /* ��������SPM�����Sups�����ֱ���˳� */
    if (ID_SPM_IMSA_CALL_SUPS_CMD_REQ != pstCallCtx->stSpmMsg.ulSpmMsgId)
    {
        return;
    }

    IMSA_INFO_LOG("IMSA_CallSrvccSuccProcSupsCmd is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_CallSrvccSuccProcSupsCmd_ENUM, LNAS_ENTRY);

    pstCallSupsCmdReq = IMSA_MEM_ALLOC(sizeof(SPM_IMSA_CALL_SUPS_CMD_REQ_STRU));
    if (VOS_NULL_PTR == pstCallSupsCmdReq)
    {
        IMSA_ERR_LOG("IMSA_CallSrvccSuccProcSupsCmd: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallSrvccSuccProcSupsCmd_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET_S(pstCallSupsCmdReq,
                   sizeof(SPM_IMSA_CALL_SUPS_CMD_REQ_STRU),
                   0x0,
                   sizeof(SPM_IMSA_CALL_SUPS_CMD_REQ_STRU));

    pstCallSupsCmdReq->ulMsgId = pstCallCtx->stSpmMsg.ulSpmMsgId;
    pstCallSupsCmdReq->usClientId = pstCallCtx->stSpmMsg.usClientId;
    pstCallSupsCmdReq->ucOpId = (MN_OPERATION_ID_T)pstCallCtx->stSpmMsg.ulOpId;

    IMSA_MEM_CPY_S( &pstCallSupsCmdReq->stCallMgmtCmd,
                    sizeof(MN_CALL_SUPS_PARAM_STRU),
                    &(pstCallCtx->stSpmMsg.stParam.stSupsParam),
                    sizeof(MN_CALL_SUPS_PARAM_STRU));

    IMSA_CallSupsCmdReqSrvccingProc(pstCallSupsCmdReq);

    IMSA_MEM_FREE(pstCallSupsCmdReq);

    if (VOS_TRUE == IMSA_IsTimerRunning(&pstCallCtx->stProctectTimer))
    {
        IMSA_StopTimer(&pstCallCtx->stProctectTimer);
    }

    /* ����������� */
    IMSA_CallImsMsgClear();
    IMSA_CallSpmMsgClear();

}

/*****************************************************************************
 Function Name  : IMSA_ProcCallSrvccSatusNoify()
 Description    : CALLģ��SRVCCָʾ�Ĵ�����
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-10-15  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcCallSrvccSatusNoify(const VOS_VOID *pRcvMsg)
{

    CALL_IMSA_SRVCC_STATUS_NOTIFY_STRU    *pstSrvccStatusNotify;

    IMSA_INFO_LOG("IMSA_ProcCallSrvccSatusNoify is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_ProcCallSrvccSatusNoify_ENUM, LNAS_ENTRY);

    pstSrvccStatusNotify = (CALL_IMSA_SRVCC_STATUS_NOTIFY_STRU*)pRcvMsg;

    if(CALL_IMSA_SRVCC_STATUS_START ==pstSrvccStatusNotify->enSrvccStatus)
    {
        /*��¼�ȴ���ϵͳָʾ��ʾ*/
        IMSA_CallSetSrvccFlag(IMSA_TRUE);

        /* ��¼�����ϱ�ALL RELEASED�¼� */
        IMSA_CallSetNotReportAllReleasedFlag(IMSA_TRUE);

        /*AT�ϱ�SRVCC����*/
        IMSA_SndMsgAtCirephInd(AT_IMSA_SRVCC_HANDOVER_STARTED);

        /*֪ͨIMSЭ��ջ SRVCC����*/
        (VOS_VOID)IMSA_CallSendImsMsgSrvcc(IMSA_IMS_INPUT_CALL_REASON_SRVCC_START);
    }
    else if(CALL_IMSA_SRVCC_STATUS_SUCCESS ==pstSrvccStatusNotify->enSrvccStatus)
    {
        /*AT�ϱ�SRVCC�ɹ�*/
        IMSA_SndMsgAtCirephInd(AT_IMSA_SRVCC_HANDOVER_SUCCESS);

        /*֪ͨIMSЭ��ջ SRVCC�ɹ�*/
        (VOS_VOID)IMSA_CallSendImsMsgSrvcc(IMSA_IMS_INPUT_CALL_REASON_SRVCC_SUCCESS);

        IMSA_USSD_ClearResource();

        /* ���DTMF���� */
        IMSA_CallSrvccSuccClearDtmfInfo(TAF_CS_CAUSE_IMSA_SRVCC_SUCC);
        /* ���ڴ���������ñ�־���������յ�SERVICE_CHANGE_INDʱ�����ת�Ƶ�SRVCC�ɹ�ʱ��� */
        IMSA_CallSetSrvccFlag(IMSA_FALSE);

        /* SRVCC�ɹ�����֪ͨTAFδע��״̬����ֹ֮��û���յ�TAU�����TAF�ͽ��绰��ѡ����
           IMSA����ά����״̬��Ȼ����ע��״̬�����´��յ�SERVICE_CHANGE_IND��
           �����ϴη��͵�״̬�͵�ǰά����״̬��ͬ���ͻ���֪ͨ��TAF��ǰ��ע��״̬*/
        (VOS_VOID)IMSA_CallSendIntraSrvccSucc();

        /* IMSA���յ�HOLD���ϲ������˵Ȳ���������SDKʱ����ʱ����SRVCC��SDKȷ��SRVCC���ǰ��
           ���ܻظ�IMSA��������SRVCC�ɹ���IMSA��Ҫ��HOLD���ϲ������˵Ȳ���֪ͨSPM֮��
           ��CS��������Щ������IMSA����Դ˺�SDK����Щ�����Ļظ������SRVCCʧ�ܣ�SDK��Ҫ
           ��IMS�����HOLD���ϲ������˵Ȳ������ظ���� */
        IMSA_CallSrvccSuccProcSupsCmd();
    }
    else /*CALL_IMSA_SRVCC_STATUS_FAIL*/
    {
        /*����ȴ���ϵͳָʾ��ʾ*/
        IMSA_CallSetSrvccFlag(IMSA_FALSE);

        /* ��������ϱ�ALL RELEASED�¼���ʶ */
        IMSA_CallSetNotReportAllReleasedFlag(IMSA_FALSE);

        /*AT�ϱ�SRVCCʧ�ܣ��ײ�handoverʧ��*/
        IMSA_SndMsgAtCirephInd(AT_IMSA_SRVCC_HANDOVER_CANCEL);

        /*���SRVCCת��CS��ĺ���*/
        IMSA_CallClearTransToCsInfo();

        /*֪ͨIMSЭ��ջ SRVCCʧ��*/
        (VOS_VOID)IMSA_CallSendImsMsgSrvcc(IMSA_IMS_INPUT_CALL_REASON_SRVCC_FAILED);

        /* ���SRVCCʧ�ܣ���û�г��ش��ڣ��Ҷ�ʱ��δ����״̬���򽫵绰�Ҷ� */
        IMSA_CallProcSrvccFail();

        IMSA_SrvccFailBuffProc();
    }

}


/*****************************************************************************
 Function Name  : IMSA_ProcTafCallMsg
 Description    : TAF CALL�·�������
 Input          : pRcvMsg      CALL�·����������
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunbing 49683      2013-10-11  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_ProcTafCallMsg(const VOS_VOID *pRcvMsg)
{
    /* ������Ϣͷָ��*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* ��ȡ��Ϣͷָ��*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;

    switch(pHeader->ulMsgName)
    {
        case ID_CALL_IMSA_SRVCC_STATUS_NOTIFY:
            IMSA_ProcCallSrvccSatusNoify(pRcvMsg);
            break;
        default:
            IMSA_ERR_LOG("IMSA_ProcTafCallMsg: Not support call message");
            TLPS_PRINT2LAYER_ERROR(IMSA_ProcTafCallMsg_ENUM, LNAS_MSG_INVALID);
            break;
    }

}

/*****************************************************************************
 Function Name  : IMSA_CallSetSrvccFlag()
 Description    : ����SRVCC��ʶ
 Input          : ulSrvccFlag-----------SRVCC��ʶ
 Output         : VOS_VOID
 Return Value   : VOS_VOID
 History        :
      1.lihong 00150010      2013-10-11  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallSetSrvccFlag
(
    VOS_UINT32                          ulSrvccFlag
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx = IMSA_CallCtxGet();

    pstCallCtx->ulSrvccFlag = ulSrvccFlag;
}

/*****************************************************************************
 Function Name  : IMSA_CallGetSrvccFlag()
 Description    : ��ȡSRVCC��ʶ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-10-11  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallGetSrvccFlag( VOS_VOID )
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx = IMSA_CallCtxGet();

    return pstCallCtx->ulSrvccFlag;
}

/*****************************************************************************
 Function Name  : IMSA_CallSetNotReportAllReleasedFlag()
 Description    : ���ò����ϱ�ALL RELEASED�¼���ʶ
 Input          : ulSrvccFlag-----------SRVCC��ʶ
 Output         : VOS_VOID
 Return Value   : VOS_VOID
 History        :
      1.lihong 00150010      2013-10-27  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallSetNotReportAllReleasedFlag
(
    VOS_UINT32                          ulNotReportAllReleasdFlag
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx = IMSA_CallCtxGet();

    pstCallCtx->ulNotReprotAllReleasedFlag = ulNotReportAllReleasdFlag;
}

/*****************************************************************************
 Function Name  : IMSA_CallGetNotReportAllReleasedFlag()
 Description    : ��ȡ�����ϱ�ALL RELEASED�¼���ʶ
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.lihong 00150010      2013-10-27  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallGetNotReportAllReleasedFlag( VOS_VOID )
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx = IMSA_CallCtxGet();

    return pstCallCtx->ulNotReprotAllReleasedFlag;
}

#if (FEATURE_ON == FEATURE_DSDS)
/*****************************************************************************
 Function Name  : IMSA_CallProcResourceApplyCnf
 Discription    : �յ�ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-23  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallProcMoCallResourceApplyCnf
(
    const SPM_IMSA_CALL_ORIG_REQ_STRU *pstAppReq
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx          = IMSA_CallCtxGet();
    VOS_UINT32                          ulResult            = VOS_FALSE;
    IMSA_CALL_ENTITY_STRU              *pstCallEntity       = VOS_NULL_PTR;

    pstCallEntity = IMSA_CallEntityGetUsedByImsCallId(IMSA_CALL_INVALID_ID);

    if (VOS_NULL_PTR == pstCallEntity)
    {
        return;
    }

    ulResult = IMSA_CallSendImsMsgDial(IMSA_CALL_INVALID_ID, pstAppReq);
    if (VOS_TRUE == ulResult)
    {
        /* ���津���˺��ж�Ӧ��SPM���������б��ܾ�����Ҫ����ע���������ʱʹ�� */
        IMSA_MEM_CPY_S( &pstCallEntity->stSpmMsg,
                        sizeof(IMSA_CALL_SPM_MSG_STRU),
                        &pstCallCtx->stSpmMsg,
                        sizeof(IMSA_CALL_SPM_MSG_STRU));

        /* ����������ʱ�� */
        IMSA_StartTimer(&pstCallCtx->stProctectTimer);

        /* �����ز����ʱ����ʱ�� */
        pstCallCtx->stRedialMaxTimer.ulTimerLen = IMSA_GetImsRedialCfgAddress()->ulCallRedialMaxTime;
        pstCallCtx->stRedialMaxTimer.usPara = pstCallEntity->ucCallEntityIndex;
        IMSA_StartTimer(&pstCallCtx->stRedialMaxTimer);
        IMSA_StartTcallTimer(pstCallEntity);
    }
    else
    {
        /* ֪ͨSPM release�¼� */
        IMSA_CallReleaseCallCommonProc(pstCallEntity, TAF_CS_CAUSE_IMSA_ERROR);
    }
}
/*****************************************************************************
 Function Name  : IMSA_CallProcResourceApplyCnf
 Discription    : �յ�ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-23  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallProcEconfResourceApplyCnf
(
    const SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU *pstAppReq
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx          = IMSA_CallCtxGet();
    VOS_UINT32                          ulResult            = VOS_FALSE;
    IMSA_CALL_ENTITY_STRU              *pstCallEntity       = VOS_NULL_PTR;

    pstCallEntity = IMSA_CallEntityGetUsedByImsCallId(IMSA_CALL_INVALID_ID);

    ulResult = IMSA_CallSendImsMsgCreatEconf(IMSA_CALL_INVALID_ID, pstAppReq);
    if (VOS_TRUE == ulResult)
    {
        /* ���津���˺��ж�Ӧ��SPM���������б��ܾ�����Ҫ����ע���������ʱʹ�� */
        IMSA_MEM_CPY_S( &pstCallEntity->stSpmMsg,
                        sizeof(IMSA_CALL_SPM_MSG_STRU),
                        pstAppReq,
                        sizeof(IMSA_CALL_SPM_MSG_STRU));

        /* ����������ʱ�� */
        IMSA_StartTimer(&pstCallCtx->stProctectTimer);

        /* �Ż���ǿ�͵�����ͨ����������Alerting, �����ڴ˴�֪ͨLRRC Start, LRRC�յ�����Ϣ��,
        ���ź���������ʱ����ǰ�ϱ�A2/B2�¼�,����������ǰ�·�Srvcc */
        if (VOS_FALSE == g_ulImsaNotifyRrcVoLteCallStartFlag)
        {
            IMSA_SndRrcVolteStatusNotify(IMSA_LRRC_VOLTE_STATUS_START);
        }
    }
    else
    {
        /* ֪ͨSPM release�¼� */
        IMSA_CallReleaseCallCommonProc(pstCallEntity, TAF_CS_CAUSE_IMSA_ERROR);
    }
}

/*****************************************************************************
 Function Name  : IMSA_CallProcEmcResourceApplyCnf
 Discription    : �յ�ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-23  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallProcEmcResourceApplyCnf
(
    const SPM_IMSA_CALL_ORIG_REQ_STRU *pstAppReq
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx          = IMSA_CallCtxGet();
    VOS_UINT32                          ulResult            = VOS_FALSE;
    VOS_UINT32                          ulCheckRet          = 0;
    IMSA_EMC_CALL_TYPE_ENUM_UINT32      enEmcType           = IMSA_EMC_CALL_TYPE_BUTT;
    IMSA_CALL_ENTITY_STRU              *pstCallEntity       = VOS_NULL_PTR;
    SPM_IMSA_CALL_ORIG_REQ_STRU         stCallOrigReq       = {0};

    /* �������ע�� */
    ulCheckRet = IMSA_CallEmcCallAvailabilityCheck(&enEmcType);

    pstCallEntity = IMSA_CallEntityGetUsedByImsCallId(IMSA_CALL_INVALID_ID);

    if (VOS_NULL_PTR == pstCallEntity)
    {
        /* �ͷ���Դ */
        /* todo */

        return;
    }

    if(ulCheckRet == IMSA_CALL_AVAILABILITY_CHECK_RESULT_CONTINUE)
    {
        /* ���������#380���µĽ�������*/
        if (IMSA_TRUE == pstCallCtx->ucRetryEmcRegFlag)
        {
            IMSA_ERR_LOG1("IMSA_CallProcIntraMsgEmcCallSrvStatus: pstCallCtx->ucRetryEmcRegFlag = ",pstCallCtx->ucRetryEmcRegFlag);
            TLPS_PRINT2LAYER_ERROR1(IMSA_CallProcIntraMsgEmcCallSrvStatusWhenNorSrv_ENUM, 1, pstCallCtx->ucRetryEmcRegFlag);
            pstCallEntity = &pstCallCtx->astCallEntity[pstCallCtx->ucCallEntityIndex];

            /* ȡ�洢��ORIG REQ��Ϣ���ٴη�����н������� */
            stCallOrigReq.ulMsgId       = ID_SPM_IMSA_CALL_ORIG_REQ;
            stCallOrigReq.usClientId    = pstCallEntity->stSpmMsg.usClientId;
            stCallOrigReq.ucOpId        = (MN_OPERATION_ID_T)pstCallEntity->stSpmMsg.ulOpId;
            stCallOrigReq.stOrig        = pstCallEntity->stSpmMsg.stParam.stOrigParam;

            pstAppReq                   = &stCallOrigReq;
        }
        ulResult = IMSA_CallSendImsMsgDial(IMSA_CALL_INVALID_ID, pstAppReq);
        if (VOS_TRUE == ulResult)
        {
            /* ���津���˺��ж�Ӧ��SPM���������б��ܾ�����Ҫ����ע���������ʱʹ�� */
            IMSA_MEM_CPY_S( &pstCallEntity->stSpmMsg,
                            sizeof(IMSA_CALL_SPM_MSG_STRU),
                            &pstCallCtx->stSpmMsg,
                            sizeof(IMSA_CALL_SPM_MSG_STRU));

            /* ����������ʱ�� */
            IMSA_StartTimer(&pstCallCtx->stProctectTimer);

            /* �����ز����ʱ����ʱ�� */
            pstCallCtx->stRedialMaxTimer.ulTimerLen = IMSA_GetImsRedialCfgAddress()->ulCallRedialMaxTime;
            pstCallCtx->stRedialMaxTimer.usPara = pstCallEntity->ucCallEntityIndex;
            IMSA_StartTimer(&pstCallCtx->stRedialMaxTimer);
            IMSA_StartTcallTimer(pstCallEntity);
        }
        else
        {
            /* ֪ͨSPM release�¼� */
            IMSA_CallReleaseCallCommonProc(pstCallEntity, TAF_CS_CAUSE_IMSA_ERROR);
        }
    }
    else if(ulCheckRet == IMSA_CALL_AVAILABILITY_CHECK_RESULT_CACHED)
    {
        /* �������ע�� */
        IMSA_StartImsEmcService();

        IMSA_CallSpmOrigReqMsgSave(pstAppReq);
        IMSA_StartTcallTimer(pstCallEntity);
    }
}
/*****************************************************************************
 Function Name  : IMSA_CallProcMtResourceApplyCnf
 Discription    : �յ�ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-23  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcMtResourceApplyCnfIntializingState
(
    VOS_VOID
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx          = IMSA_CallCtxGet();
    VOS_UINT8                           i                   = 0;
    IMSA_CALL_ENTITY_STRU              *pstCallEntity       = VOS_NULL_PTR;

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
            (MN_CALL_DIR_MT == pstCallCtx->astCallEntity[i].enDir) &&
            (IMSA_CALL_STATUS_IDLE == pstCallCtx->astCallEntity[i].enStatus))
        {
            pstCallEntity = &(pstCallCtx->astCallEntity[i]);
            break;
        }
    }

    if (VOS_NULL_PTR != pstCallEntity)
    {
        if (IMSA_CALL_CALL_REASON_RESOURCE_READY == IMSA_CallIsResourceReady(pstCallEntity))
        {
            IMSA_INFO_LOG("IMSA_CallProcImsMsgInitializing:call already exist,resource already!");
            TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgInitializing_ENUM, IMSA_EXISTED);
            TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgInitializing_ENUM, IMSA_RESOURCE_READY);

            (VOS_VOID)IMSA_CallSendImsMsgResRsp(pstCallEntity->ucImscallId,
                                                pstCallEntity->ulResRspOpId,
                                                pstCallEntity->ulDialogId,
                                                IMSA_CALL_CALL_REASON_RESOURCE_READY);
        }
        else
        {
            IMSA_INFO_LOG("IMSA_CallProcImsMsgInitializing:call not exist,wait for resource!");
            TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgInitializing_ENUM, IMSA_CALL_NOT_EXIST);
            TLPS_PRINT2LAYER_INFO(IMSA_CallProcImsMsgInitializing_ENUM, IMSA_RESOURCE_NOT_READY);

            /* ���ú��ж�Ӧ����Դ��־λ */
            pstCallEntity->bitOpNeedSendResResult = IMSA_TRUE;

            /* ˢ�µȴ���Դ������ʱ�� */
            if(VOS_TRUE == IMSA_GetConfigParaAddress()->stCMCCCustomReq.ucCMCCCustomTqosFlag)
            {
                pstCallCtx->stResReadyTimer.ulTimerLen = IMSA_GetConfigParaAddress()->stCMCCCustomReq.ulTqosTimerLen;
            }
            IMSA_RegTimerRefresh(&pstCallCtx->stResReadyTimer, pstCallEntity->ucCallEntityIndex);
        }
        return IMSA_TRUE;
    }
    return IMSA_FALSE;
 }
/*****************************************************************************
 Function Name  : IMSA_CallProcMtResourceApplyCnf
 Discription    : �յ�ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-23  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcMtResourceApplyCnfIncomingState
(
    VOS_VOID
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx          = IMSA_CallCtxGet();
    VOS_UINT8                           i                   = 0;
    IMSA_CALL_ENTITY_STRU              *pstCallEntity       = VOS_NULL_PTR;

    for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
            (MN_CALL_DIR_MT == pstCallCtx->astCallEntity[i].enDir) &&
            ((IMSA_CALL_STATUS_INCOMING == pstCallCtx->astCallEntity[i].enStatus) ||
             (IMSA_CALL_STATUS_WAITING == pstCallCtx->astCallEntity[i].enStatus)))
        {
            pstCallEntity = &(pstCallCtx->astCallEntity[i]);
            break;
        }
    }

    if (VOS_NULL_PTR != pstCallEntity)
    {
        (VOS_VOID)IMSA_CallSendSpmStateEvt( pstCallEntity->ucSpmcallId,
                                            pstCallEntity->usClientId,
                                            pstCallEntity->ulOpId,
                                            MN_CALL_EVT_INCOMING);
        return IMSA_TRUE;
    }
    return IMSA_FALSE;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcMtResourceApplyCnf
 Discription    : �յ�ID_RRM_PS_RADIO_RESOURCE_APPLY_CNF��Ϣ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-23  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_CallProcMtResourceApplyCnf
(
    IMSA_IMS_CALL_STATE_ENUM_UINT8         enCallState
)
{
    VOS_UINT32                          ulResult = IMSA_FALSE;

    /* ����Ǳ��У���Ҫ���ݴ���ԭ��ֵ�жϣ��Ǹ�SPM�ϱ�incoming�¼�������֪ͨIMS��ԴԤ���ɹ� */
    if (IMSA_IMS_CALL_STATE_INITIALIZING == enCallState)
    {
        ulResult = IMSA_CallProcMtResourceApplyCnfIntializingState();
    }
    else  /* ����Ƿ�precondition���̵ı��� */
    {
        ulResult = IMSA_CallProcMtResourceApplyCnfIncomingState();

    }
    return ulResult;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcMoResourceApplyTimerExp
 Discription    : ����MO CALL������Դ��ʱ����ʱ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-23  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallProcMoOrEmcResourceApplyTimerExp
(
    VOS_VOID
)
{
    IMSA_CALL_ENTITY_STRU              *pstCallEntity       = VOS_NULL_PTR;

    pstCallEntity = IMSA_CallEntityGetUsedByImsCallId(IMSA_CALL_INVALID_ID);

    /* ֪ͨSPM release�¼� */
    IMSA_CallReleaseCallCommonProc(pstCallEntity, TAF_CS_CAUSE_IMSA_NO_RF);

    return;
}

/*****************************************************************************
 Function Name  : IMSA_CallProcMtResourceApplyTimerExp
 Discription    : ����MO CALL������Դ��ʱ����ʱ�Ĵ���
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-11-23  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallProcMtResourceApplyTimerExp
(
    IMSA_IMS_CALL_STATE_ENUM_UINT8         enCallState
)
{
    IMSA_CALL_MANAGER_STRU             *pstCallCtx          = IMSA_CallCtxGet();
    VOS_UINT8                           i                   = 0;
    IMSA_CALL_ENTITY_STRU              *pstCallEntity       = VOS_NULL_PTR;

    if (IMSA_IMS_CALL_STATE_INITIALIZING == enCallState)
    {
        for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
        {
            if ((VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
                (MN_CALL_DIR_MT == pstCallCtx->astCallEntity[i].enDir) &&
                (IMSA_CALL_STATUS_IDLE == pstCallCtx->astCallEntity[i].enStatus))
            {
                pstCallEntity = &(pstCallCtx->astCallEntity[i]);
                break;
            }
        }

        if (VOS_NULL_PTR != pstCallEntity)
        {
            (VOS_VOID)IMSA_CallSendImsMsgResRsp(pstCallEntity->ucImscallId,
                                                pstCallEntity->ulResRspOpId,
                                                pstCallEntity->ulDialogId,
                                                IMSA_CALL_CALL_REASON_RESOURCE_FAILED);
        }
    }
    else  /* ����Ƿ�precondition���̵ı��� */
    {
        for (i = 0; i < IMSA_CALL_MAX_NUM; i++)
        {
            if ((VOS_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
                (MN_CALL_DIR_MT == pstCallCtx->astCallEntity[i].enDir) &&
                ((IMSA_CALL_STATUS_INCOMING == pstCallCtx->astCallEntity[i].enStatus) ||
                 (IMSA_CALL_STATUS_WAITING == pstCallCtx->astCallEntity[i].enStatus)))
            {
                pstCallEntity = &(pstCallCtx->astCallEntity[i]);
                break;
            }
        }

        if (VOS_NULL_PTR != pstCallEntity)
        {
            IMSA_CallSendImsMsgSupsRelCallXWithoutCnf(pstCallEntity->ucImscallId);
        }
    }

    return;
}
#endif


/*****************************************************************************
 Function Name  : IMSA_IsCallConnExist
 Description    : �жϵ�ǰ�Ƿ���IMS����ҵ��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.xiongxianghui 00253310      2014-07-01  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_IsCallConnExist(VOS_VOID)
{

    VOS_UINT16                          i = 0;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx = IMSA_CallCtxGet();

    for (i = 0; i < IMSA_CALL_MAX_NUM; i ++)
    {
        if (IMSA_OP_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 Function Name  : IMSA_IsExitImsService()
 Description    : �Ƿ���ڲ����еĺ���
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.wangchen 00209181   2015-07-06  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_IsExitImsService(VOS_VOID)
{
    return IMSA_IsImsExist();
}
/*****************************************************************************
 Function Name  : IMSA_IsExistNormCall
 Description    : �жϵ�ǰ�Ƿ�����ͨ��IMS����ҵ��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.wangchen 00209181   2016-02-25  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_IsExistNormCall(VOS_VOID)
{
    VOS_UINT16                          i = 0;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx = IMSA_CallCtxGet();

    for (i = 0; i < IMSA_CALL_MAX_NUM; i ++)
    {
        if ((IMSA_OP_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
            (IMSA_CALL_TYPE_EMC != pstCallCtx->astCallEntity[i].enType))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 Function Name  : IMSA_IsExistNormCall
 Description    : �жϵ�ǰ�Ƿ�����ͨ��IMS����ҵ��
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_UINT32

 History        :
      1.wangchen 00209181   2016-02-25  Draft Enact
*****************************************************************************/
VOS_UINT32 IMSA_IsExistEmcCall(VOS_VOID)
{
    VOS_UINT16                          i = 0;
    IMSA_CALL_MANAGER_STRU             *pstCallCtx = IMSA_CallCtxGet();

    for (i = 0; i < IMSA_CALL_MAX_NUM; i ++)
    {
        if ((IMSA_OP_TRUE == pstCallCtx->astCallEntity[i].bitOpIsUsed) &&
            (IMSA_CALL_TYPE_EMC == pstCallCtx->astCallEntity[i].enType))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : IMSA_CallTransImsaErr2ImsInfo
 ��������  : ��¼IMSA����ʧ���¼�
 �������  : enCallFailReason    ����ʧ��ԭ��ֵ
             pstCallEntity       ����ʵ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��07��
    ��    ��   : W00209181
    �޸�����   : �����ɺ���

*****************************************************************************/
IMSA_IMS_CALL_REL_CAUSE_ENUM_UINT8 IMSA_CallTransImsaErr2ImsInfo
(
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32  enImsaErr
)
{
    switch(enImsaErr)
    {
        case IMSA_CALL_NO_SRV_CAUSE_HIFI_EXCEPTION:
            return IMSA_IMS_CALL_REL_CAUSE_HIFI_SET_START_FAIL;

        case IMSA_CALL_NO_SRV_CAUSE_NON_SRVCC_RAT_CHANGE:
            return IMSA_IMS_CALL_REL_CAUSE_NON_SRVCC_RAT_CHANGE;

        case IMSA_CALL_NO_SRV_CAUSE_NW_NOT_SUPPORT_IMS_VOICE:
            return IMSA_IMS_CALL_REL_CAUSE_NW_NOT_SUPPORT_IMS_VOICE;

        case IMSA_CALL_NO_SRV_CAUSE_MEDIA_PDP_RELEASE:
            return IMSA_IMS_CALL_REL_CAUSE_NW_DEACTIVE_MEDIA_BEAR;

        case IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR:
            return IMSA_IMS_CALL_REL_CAUSE_NW_DEACTIVE_SIP_BEAR;

        case IMSA_CALL_NO_SRV_CAUSE_REG_ERR:
            return IMSA_IMS_CALL_REL_CAUSE_IMS_REG_FAIL;

        case IMSA_CALL_NO_SRV_CAUSE_PORT_CFG_FAIL:
            return IMSA_IMS_CALL_REL_CAUSE_HIFI_PORT_CFG_FAIL;

        case IMSA_CALL_NO_SRV_CAUSE_SET_DEVICE_FAIL:
            return IMSA_IMS_CALL_REL_CAUSE_HIFI_SET_DEVICE_FAIL;

        case IMSA_CALL_NO_SRV_CAUSE_SET_START_FAIL:
            return IMSA_IMS_CALL_REL_CAUSE_HIFI_SET_START_FAIL;

        case IMSA_CALL_NO_SRV_CAUSE_SET_VOLUME_FAIL:
            return IMSA_IMS_CALL_REL_CAUSE_HIFI_SET_VOLUME_FAIL;

        case IMSA_CALL_NO_SRV_CAUSE_SAMPLE_RATE_FAIL:
            return IMSA_IMS_CALL_REL_CAUSE_HIFI_SAMPLE_RATE_FAIL;

        case IMSA_CALL_NO_SRV_CAUSE_TI_START_EXPIRED:
            return IMSA_IMS_CALL_REL_CAUSE_HIFI_TI_START_EXPIRED;
        default:
            return IMSA_IMS_CALL_REL_CAUSE_BUTT;
    }
}

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 �� �� ��  : IMSA_SndCallErrLogInfo
 ��������  : ��IMSA�ĺ���ERROR LOG ��Ϣ����HIDS
 �������  : stImsCallRstEvent   VoLTE����ʧ����Ϣ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��15��
    ��    ��   : w00209181
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IMSA_SndCallErrLogInfo
(
    IMSA_ERR_LOG_CALL_FAIL_STRU  stImsCallRstEvent
)
{
    IMSA_CALL_ERROR_LOG_INFO_STRU  *pstMsg = VOS_NULL_PTR;

    pstMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_CALL_ERROR_LOG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        IMSA_ERR_LOG("IMSA_SndCallErrLogInfo:ERROR:Alloc Mem Fail.");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndCallErrLogInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

    /*���*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsg),
                    IMSA_GET_MSG_LENGTH(pstMsg),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsg));

    IMSA_WRITE_OM_MSG_HEAD( pstMsg,
                            ID_IMSA_OM_CALL_ERROR_LOG_IND);

    IMSA_MEM_CPY_S( &pstMsg->stImsaCallErrlog,
                    sizeof(IMSA_ERR_LOG_CALL_FAIL_STRU),
                    &stImsCallRstEvent,
                    sizeof(IMSA_ERR_LOG_CALL_FAIL_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    IMSA_SND_MSG(pstMsg);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstMsg);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_FREE_MSG(pstMsg);

#endif

    return;
}

/*****************************************************************************
 �� �� ��  : IMSA_SndNormCallErrLogInfo
 ��������  : ��IMSA�ĺ���ERROR LOG ��Ϣ����HIDS
 �������  : stImsCallRstEvent   VoLTE����ʧ����Ϣ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��15��
    ��    ��   : w00209181
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IMSA_SndNormCallErrLogInfo
(
    IMSA_ERR_LOG_NORM_CALL_FAIL_STRU  stImsCallRstEvent
)
{
    IMSA_NORM_CALL_ERROR_LOG_INFO_STRU  *pstMsg = VOS_NULL_PTR;

    pstMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_NORM_CALL_ERROR_LOG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        IMSA_ERR_LOG("IMSA_SndCallErrLogInfo:ERROR:Alloc Mem Fail.");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndCallErrLogInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

     /*���*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsg),
                    IMSA_GET_MSG_LENGTH(pstMsg),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsg));

    IMSA_WRITE_OM_MSG_HEAD( pstMsg,
                            ID_IMSA_OM_NORM_CALL_FAIL_ERR_LOG_IND);

    IMSA_MEM_CPY_S( &pstMsg->stImsaCallErrlog,
                    sizeof(IMSA_ERR_LOG_NORM_CALL_FAIL_STRU),
                    &stImsCallRstEvent,
                    sizeof(IMSA_ERR_LOG_NORM_CALL_FAIL_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    IMSA_SND_MSG(pstMsg);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstMsg);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_FREE_MSG(pstMsg);

#endif

    return;
}

/*****************************************************************************
 �� �� ��  : IMSA_SndEmcCallErrLogInfo
 ��������  : ��IMSA�ĺ���ERROR LOG ��Ϣ����HIDS
 �������  : stImsCallRstEvent   VoLTE����ʧ����Ϣ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��15��
    ��    ��   : w00209181
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IMSA_SndEmcCallErrLogInfo
(
    IMSA_ERR_LOG_EMC_CALL_FAIL_STRU  stImsCallRstEvent
)
{
    IMSA_EMC_CALL_ERROR_LOG_INFO_STRU  *pstMsg = VOS_NULL_PTR;

    pstMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_EMC_CALL_ERROR_LOG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        IMSA_ERR_LOG("IMSA_SndCallErrLogInfo:ERROR:Alloc Mem Fail.");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndCallErrLogInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

     /*���*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsg),
                    IMSA_GET_MSG_LENGTH(pstMsg),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsg));

    IMSA_WRITE_OM_MSG_HEAD( pstMsg,
                            ID_IMSA_OM_EMC_CALL_FAIL_ERR_LOG_IND);

    IMSA_MEM_CPY_S( &pstMsg->stImsaEmcCallErrlog,
                    sizeof(IMSA_ERR_LOG_EMC_CALL_FAIL_STRU),
                    &stImsCallRstEvent,
                    sizeof(IMSA_ERR_LOG_EMC_CALL_FAIL_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    IMSA_SND_MSG(pstMsg);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstMsg);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_FREE_MSG(pstMsg);

#endif

    return;
}

/*****************************************************************************
 �� �� ��  : IMSA_SndEmcCallErrLogInfo
 ��������  : ��IMSA�ĺ���ERROR LOG ��Ϣ����HIDS
 �������  : stImsCallRstEvent   VoLTE����ʧ����Ϣ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��01��15��
    ��    ��   : w00209181
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IMSA_SndModifyCallTypeErrLogInfo
(
    IMSA_ERR_LOG_MODIFY_CALL_TYPE_FAIL_STRU  stImsCallRstEvent
)
{
    IMSA_MODIFY_CALL_TYPE_ERROR_LOG_INFO_STRU  *pstMsg = VOS_NULL_PTR;

    pstMsg = (VOS_VOID*)IMSA_ALLOC_MSG(sizeof(IMSA_MODIFY_CALL_TYPE_ERROR_LOG_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        IMSA_ERR_LOG("IMSA_SndCallErrLogInfo:ERROR:Alloc Mem Fail.");
        TLPS_PRINT2LAYER_ERROR(IMSA_SndCallErrLogInfo_ENUM, LNAS_NULL_PTR);
        return;
    }

     /*���*/
    IMSA_MEM_SET_S( IMSA_GET_MSG_ENTITY(pstMsg),
                    IMSA_GET_MSG_LENGTH(pstMsg),
                    0,
                    IMSA_GET_MSG_LENGTH(pstMsg));

    IMSA_WRITE_OM_MSG_HEAD( pstMsg,
                            ID_IMSA_OM_MODIFY_CALL_TYPE_FAIL_ERR_LOG_IND);

    IMSA_MEM_CPY_S( &pstMsg->stImsaModCallTypeFail,
                    sizeof(IMSA_ERR_LOG_MODIFY_CALL_TYPE_FAIL_STRU),
                    &stImsCallRstEvent,
                    sizeof(IMSA_ERR_LOG_MODIFY_CALL_TYPE_FAIL_STRU));


#if(VOS_WIN32 == VOS_OS_VER)
    /*PC���ԣ�����Ϣ���ͳ�ȥ������ST��֤*/
    IMSA_SND_MSG(pstMsg);

#else
    /*��Ϣ����HSO��*/
    (VOS_VOID)LTE_MsgHook(pstMsg);

    /*�ͷ���Ϣ�ռ�*/
    IMSA_FREE_MSG(pstMsg);

#endif

    return;
}
/*****************************************************************************
 �� �� ��  : IMSA_CallTransImsaErr2ErrlogInfo
 ��������  : ��¼IMSA����ʧ���¼�
 �������  : enCallFailReason    ����ʧ��ԭ��ֵ
             pstCallEntity       ����ʵ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��07��
    ��    ��   : W00209181
    �޸�����   : �����ɺ���

*****************************************************************************/
IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_ENUM_UINT16 IMSA_CallTransImsaErr2ErrlogInfo
(
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32  enImsaErr
)
{
    switch(enImsaErr)
    {
        case IMSA_CALL_NO_SRV_CAUSE_PORT_CFG_FAIL:
        case IMSA_CALL_NO_SRV_CAUSE_SET_DEVICE_FAIL:
        case IMSA_CALL_NO_SRV_CAUSE_SET_START_FAIL:
        case IMSA_CALL_NO_SRV_CAUSE_SET_VOLUME_FAIL:
        case IMSA_CALL_NO_SRV_CAUSE_SAMPLE_RATE_FAIL:
        case IMSA_CALL_NO_SRV_CAUSE_TI_START_EXPIRED:
            return IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_HIFI_EXCEPTION;

        case IMSA_CALL_NO_SRV_CAUSE_NON_SRVCC_RAT_CHANGE:
            return IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NON_SRVCC_RAT_CHANGE;

        case IMSA_CALL_NO_SRV_CAUSE_NW_NOT_SUPPORT_IMS_VOICE:
            return IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NOT_SUPPORTED_CALL_TYPE;

        case IMSA_CALL_NO_SRV_CAUSE_MEDIA_PDP_RELEASE:
            return IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_MEDIA_PDP_RELEASE;

        case IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR:
            return IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_SIP_PDP_ERR;

        case IMSA_CALL_NO_SRV_CAUSE_REG_ERR:
            return IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_REG_ERR;

        default:
            return IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NONE;
    }
}
/*****************************************************************************
 �� �� ��  : IMSA_CallTransImsaErr2ErrlogInfo
 ��������  : ��¼IMSA����ʧ���¼�
 �������  : enCallFailReason    ����ʧ��ԭ��ֵ
             pstCallEntity       ����ʵ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��07��
    ��    ��   : W00209181
    �޸�����   : �����ɺ���

*****************************************************************************/
IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_ENUM_UINT16 IMSA_CallTransImsaEmcErr2ErrlogInfo
(
    IMSA_CALL_NO_SRV_CAUSE_ENUM_UINT32  enImsaErr
)
{
    switch(enImsaErr)
    {
        case IMSA_CALL_NO_SRV_CAUSE_PORT_CFG_FAIL:
        case IMSA_CALL_NO_SRV_CAUSE_SET_DEVICE_FAIL:
        case IMSA_CALL_NO_SRV_CAUSE_SET_START_FAIL:
        case IMSA_CALL_NO_SRV_CAUSE_SET_VOLUME_FAIL:
        case IMSA_CALL_NO_SRV_CAUSE_SAMPLE_RATE_FAIL:
        case IMSA_CALL_NO_SRV_CAUSE_TI_START_EXPIRED:
            return IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_HIFI_EXCEPTION;

        case IMSA_CALL_NO_SRV_CAUSE_NON_SRVCC_RAT_CHANGE:
            return IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NON_SRVCC_RAT_CHANGE;

        case IMSA_CALL_NO_SRV_CAUSE_NW_NOT_SUPPORT_IMS_VOICE:
            return IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NOT_SUPPORTED_CALL_TYPE;

        case IMSA_CALL_NO_SRV_CAUSE_MEDIA_PDP_RELEASE:
            return IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_MEDIA_PDP_RELEASE;

        case IMSA_CALL_NO_SRV_CAUSE_SIP_PDP_ERR:
            return IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_SIP_PDP_ERR;

        case IMSA_CALL_NO_SRV_CAUSE_REG_ERR:
            return IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_REG_ERR;

        default:
            return IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NONE;
    }
}


/*****************************************************************************
 �� �� ��  : IMSA_CallErrRecord
 ��������  : ��¼IMSA����ʧ���¼�
 �������  : enCallFailReason    ����ʧ��ԭ��ֵ
             pstCallEntity       ����ʵ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��06��
    ��    ��   : W00209181
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IMSA_CallErrRecord
(
    IMSA_ERR_LOG_CALL_FAIL_REASON_ENUM_UINT16       enCallFailReason,
    IMSA_CALL_ENTITY_STRU *pstCallEntity
)
{
    IMSA_ERR_LOG_CALL_FAIL_STRU                             stImsCallRstEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;
    IMSA_REG_MANAGER_STRU              *pstRegCtx = IMSA_RegCtxGet();
    VOS_CHAR                            aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};
    VOS_CHAR                            aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};


    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_CALL_FAIL_EVENT);
    ulIsLogRecord = IMSA_IsErrLogNeedRecord(usLevel);
    /* ģ���쳣����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(IMSA_ERR_LOG_REG_FAIL_STRU);

    /* ���CSע��ʧ���쳣��Ϣ */
    IMSA_MEM_SET_S(&stImsCallRstEvent, ulLength, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsCallRstEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_CALL_FAIL_EVENT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));
    if (VOS_NULL_PTR == pstCallEntity)
    {
        stImsCallRstEvent.enCallStatus = IMSA_ERR_LOG_CALL_STATUS_IDLE;
        stImsCallRstEvent.enMpty = IMSA_ERR_LOG_CALL_NOT_IN_MPTY;
    }
    else
    {
        stImsCallRstEvent.enCallStatus = IMSA_CallImsaState2ErrlogState(pstCallEntity->enStatus);
        stImsCallRstEvent.enMpty = IMSA_CallImsaMpty2ErrlogMpty(pstCallEntity->enMpty);
    }

    stImsCallRstEvent.enCallFailReason      = enCallFailReason;
    stImsCallRstEvent.enEmcRegStatus        = IMSA_RegState2ErrlogState(pstRegCtx->stEmcRegEntity.enStatus);
    stImsCallRstEvent.enNormRegStatus       = IMSA_RegState2ErrlogState(pstRegCtx->stNormalRegEntity.enStatus);
    stImsCallRstEvent.enPdnConnStatus       = IMSA_ConnState2ErrlogConnState(IMSA_CONN_GetNormalConnStatus());
    stImsCallRstEvent.enVopsStatus          = IMSA_VoPsState2ErrlogVoPsState(IMSA_GetNwImsVoiceCap());
    stImsCallRstEvent.ucIsVoiceMediaExist   = (VOS_UINT8)IMSA_CONN_HasActiveVoicePdp();
    stImsCallRstEvent.ucIsVideoMediaExist   = (VOS_UINT8)IMSA_CONN_HasActiveVideoPdp();

    if (VOS_TRUE == IMSA_RegAddrPairMgrGetCurrent(IMSA_REG_TYPE_NORMAL, aucUeAddr, aucPcscfAddr))
    {
        IMSA_MEM_CPY_S(stImsCallRstEvent.aucPcscfAddr,
                     IMSA_IPV6_ADDR_STRING_LEN+1,
                     aucPcscfAddr,
                     IMSA_IPV6_ADDR_STRING_LEN+1);
    }

    /* ������HIDS */
    IMSA_SndCallErrLogInfo(stImsCallRstEvent);

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = IMSA_PutErrLogRingBuf((VOS_CHAR *)&stImsCallRstEvent, ulLength);
    if (ulResult != ulLength)
    {
        IMSA_ERR_LOG("IMSA_CallErrRecord: Push buffer error.");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallErrRecord_ENUM, LNAS_ERROR);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : IMSA_NormCallErrRecord
 ��������  : ��¼IMSA����ʧ���¼�
 �������  : enCallFailReason    ����ʧ��ԭ��ֵ
             pstCallEntity       ����ʵ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��06��
    ��    ��   : W00209181
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IMSA_NormCallErrRecord
(
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_ENUM_UINT16 enCallFailReason,
    IMSA_CALL_ENTITY_STRU                      *pstCallEntity,
    VOS_UINT16                                  usSipStatusCode
)
{
    IMSA_ERR_LOG_NORM_CALL_FAIL_STRU                        stImsNormCallRstEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;
    IMSA_REG_MANAGER_STRU              *pstRegCtx = IMSA_RegCtxGet();
    VOS_CHAR                            aucUeAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};
    VOS_CHAR                            aucPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN+1] = {0};


    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_NORM_CALL_FAIL_EVENT);
    ulIsLogRecord = IMSA_IsErrLogNeedRecord(usLevel);
    /* ģ���쳣����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(IMSA_ERR_LOG_NORM_CALL_FAIL_STRU);

    /* ���CSע��ʧ���쳣��Ϣ */
    IMSA_MEM_SET_S(&stImsNormCallRstEvent, ulLength, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsNormCallRstEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_NORM_CALL_FAIL_EVENT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));
    if (VOS_NULL_PTR == pstCallEntity)
    {
        stImsNormCallRstEvent.enCallStatus      = IMSA_ERR_LOG_CALL_STATUS_IDLE;
        stImsNormCallRstEvent.enMpty            = IMSA_ERR_LOG_CALL_NOT_IN_MPTY;
    }
    else
    {
        stImsNormCallRstEvent.enCallStatus      = IMSA_CallImsaState2ErrlogState(pstCallEntity->enStatus);
        stImsNormCallRstEvent.enMpty            = IMSA_CallImsaMpty2ErrlogMpty(pstCallEntity->enMpty);
        stImsNormCallRstEvent.enCallType        = pstCallEntity->enType;
    }

    stImsNormCallRstEvent.enCallFailReason      = enCallFailReason;
    stImsNormCallRstEvent.usSipStatusCode       = usSipStatusCode;
    stImsNormCallRstEvent.enNormRegStatus       = IMSA_RegState2ErrlogState(pstRegCtx->stNormalRegEntity.enStatus);
    stImsNormCallRstEvent.enPdnConnStatus       = IMSA_ConnState2ErrlogConnState(IMSA_CONN_GetNormalConnStatus());
    stImsNormCallRstEvent.enVopsStatus          = IMSA_VoPsState2ErrlogVoPsState(IMSA_GetNwImsVoiceCap());
    stImsNormCallRstEvent.ucIsVoiceMediaExist   = (VOS_UINT8)IMSA_CONN_HasActiveVoicePdp();
    stImsNormCallRstEvent.ucIsVideoMediaExist   = (VOS_UINT8)IMSA_CONN_HasActiveVideoPdp();

    if (VOS_TRUE == IMSA_RegAddrPairMgrGetCurrent(IMSA_REG_TYPE_NORMAL, aucUeAddr, aucPcscfAddr))
    {
        IMSA_MEM_CPY_S(stImsNormCallRstEvent.aucPcscfAddr,
                     IMSA_IPV6_ADDR_STRING_LEN+1,
                     aucPcscfAddr,
                     IMSA_IPV6_ADDR_STRING_LEN+1);
    }

    /* ������HIDS */
    IMSA_SndNormCallErrLogInfo(stImsNormCallRstEvent);

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = IMSA_PutErrLogRingBuf((VOS_CHAR *)&stImsNormCallRstEvent, ulLength);
    if (ulResult != ulLength)
    {
        IMSA_ERR_LOG("IMSA_CallErrRecord: Push buffer error.");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallErrRecord_ENUM, LNAS_ERROR);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : IMSA_EmcCallErrRecord
 ��������  : ��¼IMSA��������ʧ���¼�
 �������  : enCallFailReason    ����ʧ��ԭ��ֵ
             pstCallEntity       ����ʵ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��06��
    ��    ��   : W00209181
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IMSA_EmcCallErrRecord
(
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_ENUM_UINT16   enCallFailReason,
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_ENUM_UINT16    enRegFailReason,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16  enPdnConnNwRej,
    VOS_UINT16                                      usCallSipStatusCode,
    VOS_UINT16                                      usEmcRegSipStatusCode,
    IMSA_ERR_LOG_CALL_STATUS_ENUM_UINT8             enCallStatus
)
{
    IMSA_ERR_LOG_EMC_CALL_FAIL_STRU                         stImsEmcCallRstEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_EMC_CALL_FAIL_EVENT);
    ulIsLogRecord = IMSA_IsErrLogNeedRecord(usLevel);
    /* ģ���쳣����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(IMSA_ERR_LOG_EMC_CALL_FAIL_STRU);

    /* ���CSע��ʧ���쳣��Ϣ */
    IMSA_MEM_SET_S(&stImsEmcCallRstEvent, ulLength, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsEmcCallRstEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_EMC_CALL_FAIL_EVENT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));
    stImsEmcCallRstEvent.enCallStatus           = enCallStatus;
    stImsEmcCallRstEvent.enCallFailReason       = enCallFailReason;
    stImsEmcCallRstEvent.enNormSrvStatus        = IMSA_SRV_GetNormalSrvStatus();
    stImsEmcCallRstEvent.enVopsStatus           = IMSA_VoPsState2ErrlogVoPsState(IMSA_GetNwImsVoiceCap());
    stImsEmcCallRstEvent.enEmcSrvStatus         = IMSA_SRV_GetEmcSrvStatus();
    stImsEmcCallRstEvent.enPdnConnNwRej         = enPdnConnNwRej;
    stImsEmcCallRstEvent.enRegFailReason        = enRegFailReason;
    stImsEmcCallRstEvent.usCallSipStatusCode    = usCallSipStatusCode;
    stImsEmcCallRstEvent.usEmcRegSipStatusCode  = usEmcRegSipStatusCode;
    stImsEmcCallRstEvent.enRegisterAddrType     = IMSA_RegAddrType2ErrlogRegReason(IMSA_GetControlManagerAddress()->enEmcAddrType);


    /* ������HIDS */
    IMSA_SndEmcCallErrLogInfo(stImsEmcCallRstEvent);

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = IMSA_PutErrLogRingBuf((VOS_CHAR *)&stImsEmcCallRstEvent, ulLength);
    if (ulResult != ulLength)
    {
        IMSA_ERR_LOG("IMSA_CallErrRecord: Push buffer error.");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallErrRecord_ENUM, LNAS_ERROR);
    }

    return;
}
/*****************************************************************************
 �� �� ��  : IMSA_ModifyCallTypeErrRecord
 ��������  : ��¼IMSA���������л�ʧ���¼�
 �������  : enCallFailReason    ����ʧ��ԭ��ֵ
             pstCallEntity       ����ʵ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��06��
    ��    ��   : W00209181
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IMSA_ModifyCallTypeErrRecord
(
    IMSA_ERR_LOG_CALL_TYPE_ENUM_UINT8   enCurCallType,
    VOS_UINT16                          usSipStatusCode
)
{
    IMSA_ERR_LOG_MODIFY_CALL_TYPE_FAIL_STRU                 stImsModCallTypeRstEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = IMSA_GetErrLogAlmLevel(IMSA_ERR_LOG_ALM_MODIFY_CALL_TYPE_FAIL_EVENT);
    ulIsLogRecord = IMSA_IsErrLogNeedRecord(usLevel);
    /* ģ���쳣����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(IMSA_ERR_LOG_MODIFY_CALL_TYPE_FAIL_STRU);

    /* ���CSע��ʧ���쳣��Ϣ */
    IMSA_MEM_SET_S(&stImsModCallTypeRstEvent, ulLength, 0x00, ulLength);

    IMSA_WRITE_ERRLOG_HEADER_INFO(&stImsModCallTypeRstEvent.stHeader,
                                  VOS_GetModemIDFromPid(PS_PID_IMSA),
                                  IMSA_ERR_LOG_ALM_MODIFY_CALL_TYPE_FAIL_EVENT,
                                  usLevel,
                                  VOS_GetSlice(),
                                  (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stImsModCallTypeRstEvent.enCurCallType      = enCurCallType;
    stImsModCallTypeRstEvent.usSipStatusCode    = usSipStatusCode;

    /* ������HIDS */
    IMSA_SndModifyCallTypeErrLogInfo(stImsModCallTypeRstEvent);

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = IMSA_PutErrLogRingBuf((VOS_CHAR *)&stImsModCallTypeRstEvent, ulLength);
    if (ulResult != ulLength)
    {
        IMSA_ERR_LOG("IMSA_CallErrRecord: Push buffer error.");
        TLPS_PRINT2LAYER_ERROR(IMSA_CallErrRecord_ENUM, LNAS_ERROR);
    }

    return;
}
/*****************************************************************************
 �� �� ��  : IMSA_CallFailErrRecord
 ��������  : ��¼IMSA���������л�ʧ���¼�
 �������  : enCallFailReason    ����ʧ��ԭ��ֵ
             pstCallEntity       ����ʵ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��06��
    ��    ��   : W00209181
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID IMSA_CallFailErrRecord
(
    IMSA_CALL_TYPE_ENUM_UINT8                       enType,
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_ENUM_UINT16  enNormCallFailReason,
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_ENUM_UINT16   enEmcCallFailReason,
    IMSA_CALL_ENTITY_STRU                           *pstCallEntity,
    VOS_UINT16                                      usSipStatusCode
)
{
    if (IMSA_CALL_TYPE_EMC != enType)
    {
        IMSA_NormCallErrRecord( enNormCallFailReason,
                                pstCallEntity,
                                usSipStatusCode);
    }
    else
    {

        if (VOS_NULL_PTR == pstCallEntity)
        {
            IMSA_EmcCallErrRecord(  enEmcCallFailReason,
                                    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_NONE,
                                    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                    usSipStatusCode,
                                    VOS_FALSE,
                                    IMSA_ERR_LOG_CALL_STATUS_IDLE);
        }
        else
        {
            IMSA_EmcCallErrRecord(  enEmcCallFailReason,
                                    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_NONE,
                                    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE,
                                    usSipStatusCode,
                                    VOS_FALSE,
                                    IMSA_CallImsaState2ErrlogState(pstCallEntity->enStatus));
        }


    }
}
#endif
/*****************************************************************************
 Function Name  : IMSA_CallProcTimeoutNormMediaLost
 Description    : ��ͨý������ͷŹҶ϶�ʱ����ʱ������
 Input          : pTimerMsg     ��ʱ��ʱ����Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2016-02-27  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallProcTimeoutNormMediaLost(const VOS_VOID *pTimerMsg)
{
    IMSA_CALL_MANAGER_STRU   *pstCallCtx      = IMSA_CallCtxGet();

    IMSA_StopTimer(&pstCallCtx->stNormMediaLostRelCallTimer);

    /* �����SRVCC�����У���ʱ����ʱ���ݲ�������SRVCCʧ�ܺ��ٴ��� */
    if (IMSA_TRUE == IMSA_CallGetSrvccFlag())
    {
        return;
    }

    /* �ж��Ƿ����������ش��ڣ��ڶ�ʱ�������ڼ䣬������ܻ��½����أ� */
    if (IMSA_TRUE == IMSA_CONN_HasActiveVoicePdp())
    {
        return;
    }

    /* �Ҷ�������ͨ�绰 */
    (VOS_VOID)IMSA_CallCmdRelAllNormal(IMSA_TRUE, IMSA_CALL_NO_SRV_CAUSE_MEDIA_PDP_RELEASE);
}
/*****************************************************************************
 Function Name  : IMSA_CallProcTimeoutEmcMediaLost
 Description    : ����ý������ͷŹҶ϶�ʱ����ʱ������
 Input          : pTimerMsg     ��ʱ��ʱ����Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2016-02-27  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallProcTimeoutEmcMediaLost(const VOS_VOID *pTimerMsg)
{
    IMSA_CALL_MANAGER_STRU   *pstCallCtx      = IMSA_CallCtxGet();

    IMSA_StopTimer(&pstCallCtx->stEmcMediaLostRelCallTimer);

    /* �����SRVCC�����У���ʱ����ʱ���ݲ�������SRVCCʧ�ܺ��ٴ��� */
    if (IMSA_TRUE == IMSA_CallGetSrvccFlag())
    {
        return;
    }

    /* �ж��Ƿ����������ش��ڣ��ڶ�ʱ�������ڼ䣬������ܻ��½����أ� */
    if (IMSA_TRUE == IMSA_CONN_HasEmcActiveVoicePdp())
    {
        return;
    }

    /* �Ҷ�������ͨ�绰 */
    (VOS_VOID)IMSA_CallCmdRelAllEmc(IMSA_TRUE, IMSA_CALL_NO_SRV_CAUSE_MEDIA_PDP_RELEASE);
}
/*****************************************************************************
 Function Name  : IMSA_CallProcTimeoutEmcMediaLost
 Description    : ����ý������ͷŹҶ϶�ʱ����ʱ������
 Input          : pTimerMsg     ��ʱ��ʱ����Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2016-02-27  Draft Enact
*****************************************************************************/
VOS_VOID IMSA_CallProcSrvccFail(VOS_VOID)
{
    IMSA_CALL_MANAGER_STRU   *pstCallCtx      = IMSA_CallCtxGet();

    /* ���SRVCCʧ�ܺ󣬴�����ͨ���У���û����ͨ�������ش��ڣ��Ҷ�ʱ��δ���У����ͷ�
    ���� */
    if ((IMSA_TRUE == IMSA_IsExistNormCall()) &&
        (IMSA_FALSE == IMSA_CONN_HasActiveVoicePdp()))
    {
        if (IMSA_FALSE == IMSA_IsTimerRunning(&pstCallCtx->stNormMediaLostRelCallTimer))
        {
            /* �Ҷ�������ͨ�绰 */
            (VOS_VOID)IMSA_CallCmdRelAllNormal(IMSA_TRUE, IMSA_CALL_NO_SRV_CAUSE_MEDIA_PDP_RELEASE);
        }
    }

    if ((IMSA_TRUE == IMSA_IsExistEmcCall()) &&
        (IMSA_FALSE == IMSA_CONN_HasEmcActiveVoicePdp()))
    {
        if (IMSA_FALSE == IMSA_IsTimerRunning(&pstCallCtx->stEmcMediaLostRelCallTimer))
        {
            /* �Ҷ�������ͨ�绰 */
            (VOS_VOID)IMSA_CallCmdRelAllEmc(IMSA_TRUE, IMSA_CALL_NO_SRV_CAUSE_MEDIA_PDP_RELEASE);
        }
    }
}
/*lint +e961*/

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaCallManagement.c */



