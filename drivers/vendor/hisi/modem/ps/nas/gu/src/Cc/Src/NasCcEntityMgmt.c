/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasCcEntityMgmt.c
  �� �� ��   : ����
  ��    ��   : ���� 49431
  ��������   : 2007��10��15��
  ����޸�   : 2007��10��15��
  ��������   : ����CCʵ��ķ��䡢�ͷź͸���״̬ת��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��10��15��
    ��    ��   : ���� 49431
    �޸�����   : �����ļ�
  2.��    ��   : 2008��7��12��
    ��    ��   : ����� 00130025
    �޸�����   : ���ⵥ��:AT2D04057
 3.��    ��   : 2008��9��11��
    ��    ��   :S62952
    �޸�����   : ���ⵥ��:AT2D05593
  4.��    ��   : 2008��12��15��
    ��    ��   :S62952
    �޸�����   : ���ⵥ��:AT2D07162

  5.��    ��   : 2010��3��2��
    ��    ��   : zhoujun /z40661
    �޸�����   : NAS R7Э������

  6.��    ��   : 2010��3��17��
    ��    ��   : zhoujun /z40661
    �޸�����   : ��ά�ɲ��Զ���AT����
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasCcInclude.h"
#include "NasCcIe.h"
#include "MnCallApi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_NASCC_ENTITYMGMT_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/
/*****************************************************************************
  2 ��������
*****************************************************************************/
/* DTMF�ַ�����ĳ��� */
#define  NAS_CC_MAX_DTMF_BUF_LEN            24

/* ����Ĳ���ҵ������������� */
#define  NAS_CC_MAX_STORED_SS_OPERATION     32

/* PC�طŵ���ȫ�ֱ���ʹ�� */
#define EVT_NAS_CC_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY   0xaaaa          /* ΪPC���̻طŶ������Ϣ */

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/
/* DTMF�����¼�ṹ�����ڻ���һ��DTMF���� */
typedef struct
{
    NAS_CC_DTMF_REQ_ENUM_U8             enReq;
    VOS_UINT8                           ucKey;
} NAS_CC_DTMF_REQ_RECORD_STRU;

/* CCʵ��ṹ */
typedef struct
{
    VOS_BOOL                            bUsed;
    VOS_UINT32                          ulStartT310Flag;                          /* ��ʶ�Ƿ���Ҫ����T310 VOS_TRUE: ������VOS_FALSE: ������ */
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucTi;
    NAS_CC_BC_PARAM_IDX_ENUM_U8         enCurrBcIdx;
    NAS_CC_BC_PARAMS_STRU               stBcParams[NAS_CC_MAX_BC_PARAM_NUM];
    NAS_CC_CALL_STATE_ENUM_U8           enCallState;
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       enHoldAuxState;
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enMptyAuxState;
    NAS_CC_DTMF_STATE_ENUM              enDtmfState;
    VOS_UINT8                           ucDtmfReqCnt;
    NAS_CC_CALL_TYPE_ENUM_U8            enCallType;
    VOS_UINT8                           aucReserve1[2];
    NAS_CC_DTMF_REQ_RECORD_STRU         astDtmfReqBuf[NAS_CC_MAX_DTMF_BUF_LEN];
} NAS_CC_ENTITY_STRU;

/* ����ҵ������洢�ÿ���洢��洢һ������ҵ����� */
typedef struct
{
    VOS_BOOL                            bUsed;
    NAS_CC_ENTITY_ID_T                  entityId;
    VOS_UINT8                           ucInvokeId;
    NAS_SS_OPERATION_ENUM_U8            enOperation;
    VOS_UINT8                           aucReserve[2];
} NAS_CC_SS_OPERATION_ITEM_STRU;

/* �����طŵ���ȫ�ֱ���ʹ��*/
typedef struct
{
    NAS_CC_ENTITY_STRU                  pc_g_f_astCcEntities[NAS_CC_MAX_ENTITY_NUM];
    NAS_CC_DTMF_Q_STATE_ENUM            pc_g_f_astDtmfQState[NAS_CC_MAX_ENTITY_NUM];
    NAS_CC_SS_OPERATION_ITEM_STRU       pc_g_f_astCcSsOperations[NAS_CC_MAX_STORED_SS_OPERATION];
} NAS_CC_OUTSIDE_RUNNING_CONTEXT_ST;

/*****************************************************************************
 Structure      : NAS_CC_SDT_MSG_ST
 Description    : PC�طŹ��̣�CC��ص�ȫ�ֱ���ͨ��������Ϣ�ṹ����
 Message origin :
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                      MsgHeader;                                          /* ��Ϣͷ                                   *//*_H2ASN_Skip*/
    NAS_CC_OUTSIDE_RUNNING_CONTEXT_ST    stOutsideCtx;
}NAS_CC_SDT_MSG_ST;

/*****************************************************************************
  4 ��������
*****************************************************************************/
/* CCʵ�� */
LOCAL NAS_CC_ENTITY_STRU                    f_astCcEntities[NAS_CC_MAX_ENTITY_NUM];
LOCAL NAS_CC_DTMF_Q_STATE_ENUM          f_astDtmfQState[NAS_CC_MAX_ENTITY_NUM];

/* CC����ĵ�ǰ���ڽ��еĲ���ҵ����� */
LOCAL NAS_CC_SS_OPERATION_ITEM_STRU         f_astCcSsOperations[NAS_CC_MAX_STORED_SS_OPERATION];

/* Added by l00198894 for V9R1 STK����, 2013/07/11, begin */
/* CCģ�鲹��ҵ��״̬�л�ʱ��״̬�봦�������ձ� */
LOCAL NAS_CC_SS_SWITCH_PROC_FUNC_MAP_STRU   f_astCcSsSwitchFuncMap[] =
{
    {NAS_CC_SS_SWITCH_IDLE,     NAS_CC_SS_SWITCH_SUCCESS,   NAS_CC_ProcSsSwitchSingleCallRetrieveSucc},
    {NAS_CC_SS_SWITCH_IDLE,     NAS_CC_SS_SWITCH_FAILED,    NAS_CC_ProcSsSwitchSingleCallRetrieveFail},
    {NAS_CC_SS_SWITCH_IDLE,     NAS_CC_SS_SWITCH_TIME_OUT,  NAS_CC_ProcSsSwitchSingleCallRetrieveFail},

    {NAS_CC_SS_SWITCH_IDLE, NAS_CC_SS_SWITCH_LAST_CALL_RELEASED, NAS_CC_ProcSsSwitchSingleCallRetrieveFail},

    {NAS_CC_SS_SWITCH_SUCCESS,  NAS_CC_SS_SWITCH_IDLE,      NAS_CC_ProcSsSwitchSingleCallHoldSucc},
    {NAS_CC_SS_SWITCH_SUCCESS,  NAS_CC_SS_SWITCH_SUCCESS,   NAS_CC_ProcSsSwitchMultiCallSucc},
    {NAS_CC_SS_SWITCH_SUCCESS,  NAS_CC_SS_SWITCH_FAILED,    NAS_CC_ProcSsSwitchMultiCallFail},
    {NAS_CC_SS_SWITCH_SUCCESS,  NAS_CC_SS_SWITCH_TIME_OUT,  NAS_CC_ProcSsSwitchMultiCallFail},

    {NAS_CC_SS_SWITCH_FAILED,   NAS_CC_SS_SWITCH_IDLE,      NAS_CC_ProcSsSwitchSingleCallHoldFail},
    {NAS_CC_SS_SWITCH_FAILED,   NAS_CC_SS_SWITCH_SUCCESS,   NAS_CC_ProcSsSwitchMultiCallFail},
    {NAS_CC_SS_SWITCH_FAILED,   NAS_CC_SS_SWITCH_FAILED,    NAS_CC_ProcSsSwitchMultiCallFail},
    {NAS_CC_SS_SWITCH_FAILED,   NAS_CC_SS_SWITCH_TIME_OUT,  NAS_CC_ProcSsSwitchMultiCallFail},

    {NAS_CC_SS_SWITCH_TIME_OUT, NAS_CC_SS_SWITCH_IDLE,      NAS_CC_ProcSsSwitchSingleCallHoldFail},

    {NAS_CC_SS_SWITCH_LAST_CALL_RELEASED, NAS_CC_SS_SWITCH_IDLE, NAS_CC_ProcSsSwitchSingleCallHoldFail},

    {NAS_CC_SS_SWITCH_TIME_OUT, NAS_CC_SS_SWITCH_SUCCESS,   NAS_CC_ProcSsSwitchMultiCallFail},
    {NAS_CC_SS_SWITCH_TIME_OUT, NAS_CC_SS_SWITCH_FAILED,    NAS_CC_ProcSsSwitchMultiCallFail},
    {NAS_CC_SS_SWITCH_TIME_OUT, NAS_CC_SS_SWITCH_TIME_OUT,  NAS_CC_ProcSsSwitchMultiCallFail},
};
/* Added by l00198894 for V9R1 STK����, 2013/07/11, end */

/*lint -save -e958 */

/*****************************************************************************
  5 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : NAS_CC_LogCcStateInfo
 ��������  : ��CC��״̬
 �������  : ucCcState: CC�ĵ�ǰ״̬
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��30��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_CC_LogCcStateInfo(
    NAS_CC_CALL_STATE_ENUM_U8           ucCcState
)
{
    NAS_CC_LOG_STATE_INFO_STRU         *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_CC_LOG_STATE_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_CC,
                                         sizeof(NAS_CC_LOG_STATE_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_LogMmStateInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET(pstMsg, 0x00, sizeof(NAS_CC_LOG_STATE_INFO_STRU));

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_CC;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_CC;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_CC_LOG_STATE_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = CCOM_LOG_STATE_INFO_IND;
    pstMsg->enCcState                   = ucCcState;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_CC, pstMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_CC_InitEntities
 ��������  : ��ʼ������CCʵ�壬��CCģ���ʼ��ʱ������øú�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��15��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_CC_InitEntities()
{
    VOS_UINT32  i;

    for (i=0; i<NAS_CC_MAX_ENTITY_NUM; i++)
    {
        f_astCcEntities[i].bUsed = VOS_FALSE;
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_CreateEntity
 ��������  : ��������ʼ��һ��CCʵ��
 �������  : ucCallId  - �ϲ�ĺ���ID�������й����иò������Դ������ϲ��ԭ����
                         �õ����ڱ��й����иò��������壬��������ֵ
             ucTi      - ���е�Transcation ID. �����й�������ΪCC_INVALID_TI_VALUE��
                         ��������Ϊ�½���ʵ�����һ���µ�Ti���ڱ��й������������
                         MM��ԭ���л�øò���ֵ�����뺯����
 �������  : pEntityId - �´�����CCʵ���ID
 �� �� ֵ  : VOS_TRUE - �����ɹ�  VOS_FALSE - ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2008��7��12��
    ��    ��   : ����� 00130025
    �޸�����   : ���ⵥ��:AT2D04057
  3.��    ��   : 2008��12��15��
    ��    ��   :S62952
    �޸�����   : ���ⵥ��:AT2D07162
  4.��    ��   : 2014��6��24��
    ��    ��   : w00167002
    �޸�����   : DSDS III��Ŀ
*****************************************************************************/
VOS_UINT32  NAS_CC_CreateEntity(
    NAS_CC_CALL_TYPE_ENUM_U8            enCallType,
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucTi,
    NAS_CC_ENTITY_ID_T                  *pEntityId
)
{
    VOS_UINT32  i;

    /* Ѱ��δʹ�õ�CCʵ�� */
    for (i=0; i<NAS_CC_MAX_ENTITY_NUM; i++)
    {
        if (VOS_FALSE == f_astCcEntities[i].bUsed)
        {
            break;
        }
    }

    if (i < NAS_CC_MAX_ENTITY_NUM)
    {
        /* �ҵ���δʹ�õ�CCʵ�壬��ʼ����ʵ�� */
        *pEntityId = i;

        if (NAS_CC_INVALID_TI_VALUE == ucTi)
        {
            /* ����һ�����˷����ҵ�񣬷����µ�Ti(��ǰδ��ʹ�õ���С��Ti)*/
            for (ucTi=0; ucTi<NAS_CC_MAX_ENTITY_NUM; ucTi++)
            {
                /* �鿴��Tiֵ�Ƿ��ѱ�ʹ�� */
                for (i=0; i<NAS_CC_MAX_ENTITY_NUM; i++)
                {
                    if ((VOS_TRUE == f_astCcEntities[i].bUsed) &&
                        (ucTi == (f_astCcEntities[i].ucTi & 0x7)))
                    {
                        break;
                    }
                }

                if (NAS_CC_MAX_ENTITY_NUM == i)
                {
                    /* ��Tiֵδ��ʹ�� */
                    break;
                }
            }

            f_astCcEntities[*pEntityId].ucTi = ucTi;
        }
        else
        {
            /* ����һ�����緢���ҵ�񣬻ظ�����Ϣ��Ti�����λ��Ϊ"1" */
            f_astCcEntities[*pEntityId].ucTi = ucTi | 0x8;
        }

        f_astCcEntities[*pEntityId].ucCallId = ucCallId;

        f_astCcEntities[*pEntityId].enCurrBcIdx = NAS_CC_BC_PARAM_1;

        f_astCcEntities[*pEntityId].enCallState = NAS_CC_CALL_STATE_U0;
        f_astCcEntities[*pEntityId].enHoldAuxState = NAS_CC_HOLD_AUX_S_IDLE;
        f_astCcEntities[*pEntityId].enMptyAuxState = NAS_CC_MPTY_AUX_S_IDLE;
        f_astCcEntities[*pEntityId].enDtmfState = NAS_CC_DTMF_S_IDLE;

        f_astCcEntities[*pEntityId].ucDtmfReqCnt = 0;

        f_astCcEntities[*pEntityId].ulStartT310Flag = VOS_TRUE;

        f_astDtmfQState[*pEntityId] = NAS_CC_DTMF_Q_NULL;

        f_astCcEntities[*pEntityId].bUsed = VOS_TRUE;

        f_astCcEntities[*pEntityId].enCallType = enCallType;

        return  VOS_OK;
    }
    else
    {
        NAS_CC_ERR_LOG("NAS_CC_CreateEntity: Can not find free CC entity.");
        return VOS_ERR;
    }
}

/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-15, begin */
/*****************************************************************************
 �� �� ��  : NAS_CC_DeleteAllEntities
 ��������  : ɾ������CCʵ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��15��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_CC_DeleteAllEntities(VOS_VOID)
{
    VOS_UINT8                           i;

    for (i = 0; i < NAS_CC_MAX_ENTITY_NUM; i++)
    {
        if (VOS_TRUE == f_astCcEntities[i].bUsed)
        {
            NAS_CC_ChangeCallState(i, NAS_CC_CALL_STATE_U0);
        }
    }

    return;
}

/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-15, end */

/*****************************************************************************
 �� �� ��  : NAS_CC_DeleteEntity
 ��������  : ɾ��һ��CCʵ��
 �������  : entityId - ��Ҫɾ����ʵ��ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2008��7��12��
    ��    ��   : ����� 00130025
    �޸�����   : ���ⵥ��:AT2D04057
  3.��    ��   : 2008��12��15��
    ��    ��   :S62952
    �޸�����   : ���ⵥ��:AT2D07162
  4.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  5.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������
  6.��    ��   : 2015��01��27��
    ��    ��   : j00174725
    �޸�����   : DTS2015010503619
*****************************************************************************/
VOS_VOID  NAS_CC_DeleteEntity(
    NAS_CC_ENTITY_ID_T                  entityId
)
{

    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_DeleteEntity: entityId wrong.");
        return;
    }

    NAS_CC_StopAllTimer(entityId);
    NAS_CC_DetachUserConn(entityId);
    NAS_CC_LocalAbortDtmf(entityId);
    NAS_CC_FlushDTMFBuff(entityId);

    f_astCcEntities[entityId].enCallState = NAS_CC_CALL_STATE_U0;
    f_astCcEntities[entityId].enHoldAuxState = NAS_CC_HOLD_AUX_S_IDLE;
    f_astCcEntities[entityId].enMptyAuxState = NAS_CC_MPTY_AUX_S_IDLE;
    f_astCcEntities[entityId].enDtmfState = NAS_CC_DTMF_S_IDLE;
    f_astDtmfQState[entityId] = NAS_CC_DTMF_Q_NULL;
    f_astCcEntities[entityId].ucDtmfReqCnt = 0;

    f_astCcEntities[entityId].ulStartT310Flag = VOS_TRUE;

    f_astCcEntities[entityId].bUsed = VOS_FALSE;
    f_astCcEntities[entityId].enCallType = NAS_CC_CALL_TYPE_BUTT;
}


/*****************************************************************************
 �� �� ��  : NAS_CC_GetEntityByTi
 ��������  : ȡ����ָ��Tiֵ��Ӧ��CCʵ���ID
 �������  : ucTi - Transcation ID
 �������  : ��
 �� �� ֵ  : ȡ�õ�CCʵ��ID. ���û���ҵ���Ӧʵ�壬�򷵻�CC_INVALID_ENTITY_ID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_CC_ENTITY_ID_T  NAS_CC_GetEntityByTi(
    VOS_UINT8                           ucTi
)
{
    VOS_UINT32 i;

    for (i=0; i<NAS_CC_MAX_ENTITY_NUM; i++)
    {
        if ((VOS_TRUE == f_astCcEntities[i].bUsed)
         && (ucTi == f_astCcEntities[i].ucTi))
        {
            /* �ҵ� */
            return i;
        }
    }

    return NAS_CC_INVALID_ENTITY_ID;
}


/*****************************************************************************
 �� �� ��  : NAS_CC_GetEntityTi
 ��������  : ȡ��ָ��CCʵ���Tiֵ
 �������  : entityId - CCʵ���ID
 �������  : ��
 �� �� ֵ  : ��ʵ���Tiֵ.
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  4.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_UINT8  NAS_CC_GetEntityTi(
    NAS_CC_ENTITY_ID_T                  entityId
)
{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_GetEntityTi: entityId wrong.");
        return 0;
    }

    NAS_CC_ASSERT(VOS_TRUE == f_astCcEntities[entityId].bUsed);

    return f_astCcEntities[entityId].ucTi;
}


/*****************************************************************************
 �� �� ��  : NAS_CC_GetCallId
 ��������  : ȡ��ָ��CCʵ���Call IDֵ
 �������  : entityId - CCʵ���ID
 �������  : ��
 �� �� ֵ  : ��ʵ���Call ID.
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_UINT8  NAS_CC_GetCallId(
    NAS_CC_ENTITY_ID_T                  entityId
)
{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_GetCallId: entityId wrong.");
        return 0;
    }

    NAS_CC_ASSERT(VOS_TRUE == f_astCcEntities[entityId].bUsed);

    return f_astCcEntities[entityId].ucCallId;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_UpdateCallId
 ��������  : �ı�ָ��CCʵ���Ӧ��CallIdֵ��
 �������  : entityId - CCʵ���ID
              enState  - �µĺ���״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  NAS_CC_UpdateCallId(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucCallId
)
{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_UpdateCallId: entityId wrong.");
        return;
    }

    NAS_CC_ASSERT(VOS_TRUE == f_astCcEntities[entityId].bUsed);

    NAS_CC_NORM_LOG1("CC change state to :", ucCallId);

    f_astCcEntities[entityId].ucCallId= ucCallId;
}


/*****************************************************************************
 �� �� ��  : NAS_CC_UpdateBcParams
 ��������  : ����ʵ���б���ĳ�����������
 �������  : entityId  - CCʵ���ID
              enIdx     - ��Ҫ���µĳ�����������������(BC1 or BC2)
              pstParams - ������������������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  NAS_CC_UpdateBcParams(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_BC_PARAM_IDX_ENUM_U8         enIdx,
    const NAS_CC_BC_PARAMS_STRU         *pstParams
)

{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_UpdateBcParams: entityId wrong.");
        return;
    }

    NAS_CC_ASSERT(VOS_TRUE == f_astCcEntities[entityId].bUsed);

    if (enIdx <= NAS_CC_BC_PARAM_2)
    {
        f_astCcEntities[entityId].stBcParams[enIdx].enItc = pstParams->enItc;
    }
    else
    {
        NAS_CC_ERR_LOG("NAS_CC_UpdateBcParams: enIdx wrong.");
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_GetBcParams
 ��������  : ȡ��ʵ���б���ĳ�����������
 �������  : entityId  - CCʵ���ID
              enIdx     - ��Ҫ��ȡ�ĳ�����������������(BC1, BC2 or Current)
 �������  : pstParams - ȡ�õĳ�����������������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  NAS_CC_GetBcParams(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_BC_PARAM_IDX_ENUM_U8         enIdx,
    NAS_CC_BC_PARAMS_STRU               *pstParams
)
{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_GetBcParams: entityId wrong.");
        return;
    }

    NAS_CC_ASSERT(VOS_TRUE == f_astCcEntities[entityId].bUsed);

    if (enIdx <= NAS_CC_BC_PARAM_2)
    {
        pstParams->enItc = f_astCcEntities[entityId].stBcParams[enIdx].enItc;
    }
    else
    {
        /* Get current BC params */
        pstParams->enItc =
        f_astCcEntities[entityId].stBcParams[f_astCcEntities[entityId].enCurrBcIdx].enItc;
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_BcAlertnate
 ��������  : BC�������棬�ú������ǵ�ǰʹ�õ�BC�����������л�
 �������  : entityId  - CCʵ���ID
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��3��27��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  NAS_CC_BcAlertnate(
    NAS_CC_ENTITY_ID_T                  entityId
)
{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_BcAlertnate: entityId wrong.");
        return;
    }

    NAS_CC_ASSERT(VOS_TRUE == f_astCcEntities[entityId].bUsed);

    if (NAS_CC_BC_PARAM_1 == f_astCcEntities[entityId].enCurrBcIdx)
    {
        f_astCcEntities[entityId].enCurrBcIdx = NAS_CC_BC_PARAM_2;
    }
    else
    {
        f_astCcEntities[entityId].enCurrBcIdx = NAS_CC_BC_PARAM_1;
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_GetCallState
 ��������  : ȡ��ָ��CCʵ��ĺ���״̬
 �������  : entityId - CCʵ���ID
 �������  : ��
 �� �� ֵ  : ��ʵ��ĺ���״̬.
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
NAS_CC_CALL_STATE_ENUM_U8  NAS_CC_GetCallState(
    NAS_CC_ENTITY_ID_T                  entityId
)
{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_GetCallState: entityId wrong.");
        return NAS_CC_CALL_STATE_BUTT;
    }

    NAS_CC_ASSERT(VOS_TRUE == f_astCcEntities[entityId].bUsed);

    return f_astCcEntities[entityId].enCallState;
}

/* Added by n00355355 for �����ؽ�, 2015-9-18, begin */
/*****************************************************************************
 �� �� ��  : NAS_CC_GetCallType
 ��������  : ȡ��ָ��CCʵ��ĺ�������
 �������  : entityId - CCʵ���ID
 �������  : ��
 �� �� ֵ  : ��ʵ��ĺ���״̬.
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2015��9��17��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_CC_CALL_TYPE_ENUM_U8  NAS_CC_GetCallType(
    NAS_CC_ENTITY_ID_T                  entityId
)
{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_GetCallType: entityId wrong.");
        return NAS_CC_CALL_STATE_BUTT;
    }

    NAS_CC_ASSERT(VOS_TRUE == f_astCcEntities[entityId].bUsed);

    return f_astCcEntities[entityId].enCallType;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_IsSpecCallEntityInUse
 ��������  : ȡ��ָ��CCʵ���Ƿ�����
 �������  : entityId - CCʵ���ID
 �������  : ��
 �� �� ֵ  : ��ʵ��ĺ���״̬.
 ���ú���  :
 ��������  :

 �޸���ʷ      :

  1.��    ��   : 2015��9��17��
    ��    ��   : n00355355
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL  NAS_CC_IsSpecCallEntityInUse(
    NAS_CC_ENTITY_ID_T                  entityId
)
{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_IsSpecCallEntityInUse: entityId wrong.");
        return NAS_CC_CALL_STATE_BUTT;
    }

    return f_astCcEntities[entityId].bUsed;
}



/* Added by n00355355 for �����ؽ�, 2015-9-18, end */


/*****************************************************************************
 �� �� ��  : NAS_CC_ChangeCallState
 ��������  : �ı�ָ��CCʵ��ĺ���״̬���ú���������һЩ�ڽ�����״̬ʱÿ������
             �������ִ�еĲ����������NULL״̬ʱ�ͷ�CCʵ��ȡ�
 �������  : entityId - CCʵ���ID
              enState  - �µĺ���״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2014��6��23��
    ��    ��   : w00242748
    �޸�����   : DSDS III����
  4.��    ��   : 2014��7��25��
    ��    ��   : b00269685
    �޸�����   : Klocwork����
  5.��    ��   : 2014��12��23��
    ��    ��   : b00269685
    �޸�����   : ultra falsh�����������

*****************************************************************************/
VOS_VOID  NAS_CC_ChangeCallState(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_CALL_STATE_ENUM_U8           enState
)
{
#if(FEATURE_ON == FEATURE_DSDS)
    MMCC_SESSION_TYPE_ENUM_UINT8        enSessionType;
    NAS_CC_CALL_STATE_ENUM_U8           enPreState;
#endif

    /* Deleted by b00269685 for Klocwork����, 2014-7-26, begin */
    /* Deleted by b00269685 for Klocwork����, 2014-7-26, end */

    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_ChangeCallState: entityId wrong.");
        return;
    }

    /* Modified by b00269685 for Klocwork����, 2014-7-25, begin */
    NAS_CC_LogCcStateInfo(f_astCcEntities[entityId].enCallState);
    /* Modified by b00269685 for Klocwork����, 2014-7-25, end */

    NAS_CC_ASSERT(VOS_TRUE == f_astCcEntities[entityId].bUsed);

    NAS_CC_NORM_LOG1("CC change state to :", enState);

#if(FEATURE_ON == FEATURE_DSDS)
    enPreState                            = f_astCcEntities[entityId].enCallState;
#endif

    f_astCcEntities[entityId].enCallState = enState;

    NAS_CC_LogCcStateInfo(f_astCcEntities[entityId].enCallState);

    switch(enState)
    {
    case NAS_CC_CALL_STATE_U0:

#if(FEATURE_ON == FEATURE_DSDS)
        /* NAS_CC_IsOnlySpecTypeCall�ú���ֻ���ж��Ƿ���ĳ������еĵ�һ�����У���״̬��U1 */
        /* Ǩ�Ƶ�U6��ͬ������VOS_TRUE */
        if ( (VOS_TRUE == NAS_CC_IsOnlySpecTypeCall(f_astCcEntities[entityId].enCallType))
          && (NAS_CC_CALL_STATE_U0 != enPreState) )
        {
            enSessionType = NAS_CC_ConvertCallTypeToSessionType(f_astCcEntities[entityId].enCallType);

            NAS_CC_SendMmccEndSessionNotify(enSessionType);
        }
#endif

        if (VOS_TRUE == NAS_CC_IsLastCallEntityID(entityId))
        {
            NAS_CC_ClearAllCacheMsg();
        }

        NAS_CC_DeleteEntity(entityId);
        break;

    default:
#if(FEATURE_ON == FEATURE_DSDS)
        if ( (VOS_TRUE == NAS_CC_IsOnlySpecTypeCall(f_astCcEntities[entityId].enCallType))
          && (NAS_CC_CALL_STATE_U0 == enPreState) )
        {
            enSessionType = NAS_CC_ConvertCallTypeToSessionType(f_astCcEntities[entityId].enCallType);

            NAS_CC_SendMmccBeginSessionNotify(enSessionType);
        }
#endif

        break;
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_GetHoldAuxState
 ��������  : ȡ��ָ��CCʵ��ĺ��б���״̬
 �������  : entityId - CCʵ���ID
 �������  : ��
 �� �� ֵ  : ��ʵ��ĺ��б���״̬.
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
NAS_CC_HOLD_AUX_STATE_ENUM_U8 NAS_CC_GetHoldAuxState(
    NAS_CC_ENTITY_ID_T                  entityId
)
{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_GetHoldAuxState: entityId wrong.");
        return NAS_CC_HOLD_AUX_S_BUTT;
    }

    /* Modified by l00198894 for V9R1 STK����, 2013/07/11, begin */
    if (VOS_TRUE != f_astCcEntities[entityId].bUsed)
    {
        return NAS_CC_HOLD_AUX_S_BUTT;
    }
    /* Modified by l00198894 for V9R1 STK����, 2013/07/11, end */

    return f_astCcEntities[entityId].enHoldAuxState;
}


/*****************************************************************************
 �� �� ��  : NAS_CC_ChangeHoldAuxState
 ��������  : �ı�ָ��CCʵ��ĺ��б���״̬
 �������  : entityId - CCʵ���ID
              state    - �µĺ��б���״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  NAS_CC_ChangeHoldAuxState(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       state
)
{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_ChangeHoldAuxState: entityId wrong.");
        return;
    }

    NAS_CC_ASSERT(VOS_TRUE == f_astCcEntities[entityId].bUsed);

    f_astCcEntities[entityId].enHoldAuxState = state;

    NAS_CC_NORM_LOG1("CC change hold state to :", state);
}


/*****************************************************************************
 �� �� ��  : NAS_CC_GetMptyAuxState
 ��������  : ȡ��ָ��CCʵ���Mpty״̬
 �������  : entityId - CCʵ���ID
 �������  : ��
 �� �� ֵ  : ��ʵ���Mpty״̬.
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
NAS_CC_MPTY_AUX_STATE_ENUM_U8 NAS_CC_GetMptyAuxState(
    NAS_CC_ENTITY_ID_T                  entityId
)
{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_GetMptyAuxState: entityId wrong.");
        return NAS_CC_MPTY_AUX_S_BUTT;
    }

    /* Modified by l00198894 for V9R1 STK����, 2013/07/11, begin */
    if (VOS_TRUE != f_astCcEntities[entityId].bUsed)
    {
        return NAS_CC_MPTY_AUX_S_BUTT;
    }
    /* Modified by l00198894 for V9R1 STK����, 2013/07/11, end */

    return f_astCcEntities[entityId].enMptyAuxState;
}


/*****************************************************************************
 �� �� ��  : NAS_CC_ChangeMptyAuxState
 ��������  : �ı�ָ��CCʵ���Mpty״̬
 �������  : entityId - CCʵ���ID
              state    - �µ�Mpty״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  NAS_CC_ChangeMptyAuxState(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       state
)
{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_ChangeMptyAuxState: entityId wrong.");
        return;
    }

    NAS_CC_ASSERT(VOS_TRUE == f_astCcEntities[entityId].bUsed);

    f_astCcEntities[entityId].enMptyAuxState = state;

    NAS_CC_NORM_LOG1("CC change MPTY state to :", state);
}

/*****************************************************************************
 �� �� ��  : NAS_CC_CheckBuildMptyWithCallInMpty
 ��������  : ���Build MPTY�����Ƿ�������к�����MPTY����½���
 �������  : entityId    - CCʵ���ID
             enMptyState - MPTY״̬
 �������  : ��
 �� �� ֵ  : VOS_OK      - ���ͨ����
             VOS_ERR     - ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��6��29��
    ��    ��   : z00161729
    �޸�����   : ��NAS_CC_CheckBuildMptyOperationȦ���Ӷ������ɺ���
*****************************************************************************/
LOCAL VOS_UINT32 NAS_CC_CheckBuildMptyWithCallInMpty(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enMptyState
)
{
    VOS_UINT32                          i;

    for (i = 0; i < NAS_CC_MAX_ENTITY_NUM; i++)
    {
        if (i == entityId)
        {
            continue;
        }

        /*�ж�CCʵ��״̬�Ƿ�������mpty����*/
        if (((NAS_CC_CALL_STATE_U10 == f_astCcEntities[i].enCallState)
         || (NAS_CC_CALL_STATE_U26 == f_astCcEntities[i].enCallState))
         && (NAS_CC_MPTY_AUX_S_IDLE == f_astCcEntities[i].enMptyAuxState))
        {
            break;
        }
    }

    if (i < NAS_CC_MAX_ENTITY_NUM)
    {
        return VOS_OK;
    }

    NAS_CC_WARN_LOG1("NAS_CC_CheckBuildMptyWithCallInMpty error In Mpty enMptyState :", enMptyState);
    return VOS_ERR;

}

/*****************************************************************************
 �� �� ��  : NAS_CC_CheckBuildMptyWithNoCallInMpty
 ��������  : ���Build MPTY�����Ƿ�������޺�����MPTY����½���
 �������  : entityId      - CCʵ���ID
             enHoldState   - ����״̬
             enMptyState   - MPTY״̬
 �������  : ��
 �� �� ֵ  : VOS_OK - ���ͨ��
             VOS_ERR - ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��6��29��
    ��    ��   : z00161729
    �޸�����   : ��NAS_CC_CheckBuildMptyOperationȦ���Ӷ������ɺ���
*****************************************************************************/
LOCAL VOS_UINT32 NAS_CC_CheckBuildMptyWithNoCallInMpty(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       enHoldState,
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enMptyState
)
{
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       enExpHoldState;
    VOS_UINT32                          i;

    if (NAS_CC_HOLD_AUX_S_IDLE == enHoldState)
    {
        enExpHoldState = NAS_CC_HOLD_AUX_S_CALL_HELD;
    }
    else
    {
        enExpHoldState = NAS_CC_HOLD_AUX_S_IDLE;
    }

    for (i = 0; i < NAS_CC_MAX_ENTITY_NUM; i++)
    {
        if (i == entityId)
        {
            continue;
        }

        /*�ж�CCʵ��״̬�Ƿ�������mpty����*/
        if (((NAS_CC_CALL_STATE_U10 == f_astCcEntities[i].enCallState)
         || (NAS_CC_CALL_STATE_U26 == f_astCcEntities[i].enCallState))
         && (enExpHoldState == f_astCcEntities[i].enHoldAuxState))
        {
            break;
        }
    }

    if (i < NAS_CC_MAX_ENTITY_NUM)
    {
        return VOS_OK;
    }

    NAS_CC_WARN_LOG1("NAS_CC_CheckBuildMptyWithNoCallInMpty error Idle enMptyState :", enMptyState);
    return VOS_ERR;

}

/*****************************************************************************
 �� �� ��  : NAS_CC_CheckBuildMptyOperation
 ��������  : ���Build MPTY�����Ƿ�����ڵ�ǰ״̬�½���
 �������  : entityId      - CCʵ���ID
              enCallState   - ����״̬
              enHoldState   - ����״̬
              enMptyState   - MPTY״̬
 �������  : ��
 �� �� ֵ  : VOS_OK - ���ͨ���� VOS_ERR - ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��15��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��6��29��
    ��    ��   : z00161729
    �޸�����   : ��NAS_CC_CheckBuildMptyOperationȦ���Ӷ������ɺ���
*****************************************************************************/
LOCAL VOS_UINT32 NAS_CC_CheckBuildMptyOperation(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_CALL_STATE_ENUM_U8           enCallState,
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       enHoldState,
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enMptyState
)
{
    VOS_UINT32                          ulResult;

    /* ����:
       1. �����ĺ�����MPTY��: ����һ������MPTY�е�active����
       2. �����ĺ��в���MPTY��: ����һ��active(held)����
       3. ��������ĺ����ڽ�������hold��mpty����������ʧ��
    */
    if ((enCallState != NAS_CC_CALL_STATE_U10)
     && (enCallState != NAS_CC_CALL_STATE_U26))
    {
        NAS_CC_WARN_LOG1("NAS_CC_CheckBuildMptyOperation error callState :", enCallState);
        return VOS_ERR;
    }

    if ((enHoldState != NAS_CC_HOLD_AUX_S_IDLE)
     && (enHoldState != NAS_CC_HOLD_AUX_S_CALL_HELD))
    {
        NAS_CC_WARN_LOG1("NAS_CC_CheckBuildMptyOperation error enHoldState :", enHoldState);
        return VOS_ERR;
    }

    if (NAS_CC_MPTY_AUX_S_CALL_IN_MPTY == enMptyState)
    {
       ulResult = NAS_CC_CheckBuildMptyWithCallInMpty(entityId, enMptyState);
       return ulResult;
    }
    else if (NAS_CC_MPTY_AUX_S_IDLE == enMptyState)
    {
        ulResult = NAS_CC_CheckBuildMptyWithNoCallInMpty(entityId, enHoldState, enMptyState);
        return ulResult;
    }
    else
    {
        /*��ǰMPTY״̬����ȷ�����ؼ��ʧ��*/
        return VOS_ERR;
    }
}

/* Added by l00198894 for V9R1 STK����, 2013/07/11, begin */
/*****************************************************************************
 �� �� ��  : NAS_CC_CheckSsSwitchHoldAllowed
 ��������  : CCģ�鲹��ҵ��״̬��鵱ǰ�Ƿ�������HOLD����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_OK     -- ���ͨ��
             VOS_ERR    -- ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_UINT32 NAS_CC_CheckSsSwitchHoldAllowed(VOS_VOID)
{
    NAS_CC_SS_SWITCH_STATE_ENUM_UINT8   enHoldState;
    NAS_CC_SS_SWITCH_STATE_ENUM_UINT8   enRetrieveState;

    enHoldState     = NAS_CC_GetSsSwitchHoldState();
    enRetrieveState = NAS_CC_GetSsSwitchRetrieveState();

    if (NAS_CC_SS_SWITCH_IDLE == enHoldState)
    {
        if ( (NAS_CC_SS_SWITCH_IDLE == enRetrieveState)
          || (NAS_CC_SS_SWITCH_WAIT_CNF == enRetrieveState) )
        {
            return VOS_OK;
        }
    }

    NAS_CC_WARN_LOG2("NAS_CC_CheckSsSwitchHoldAllowed: Error Switch State :", enHoldState, enRetrieveState);
    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_CheckSsSwitchRetrieveAllowed
 ��������  : CCģ�鲹��ҵ��״̬��鵱ǰ�Ƿ�������RETRIEVE����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_OK     -- ���ͨ��
             VOS_ERR    -- ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_UINT32 NAS_CC_CheckSsSwitchRetrieveAllowed(VOS_VOID)
{
    NAS_CC_SS_SWITCH_STATE_ENUM_UINT8   enHoldState;
    NAS_CC_SS_SWITCH_STATE_ENUM_UINT8   enRetrieveState;

    enHoldState     = NAS_CC_GetSsSwitchHoldState();
    enRetrieveState = NAS_CC_GetSsSwitchRetrieveState();

    if (NAS_CC_SS_SWITCH_IDLE == enRetrieveState)
    {
        if ( (NAS_CC_SS_SWITCH_IDLE == enHoldState)
          || (NAS_CC_SS_SWITCH_WAIT_CNF == enHoldState) )
        {
            return VOS_OK;
        }
    }

    NAS_CC_WARN_LOG2("NAS_CC_CheckSsSwitchRetrieveAllowed: Error Switch State :", enHoldState, enRetrieveState);
    return VOS_ERR;
}

/* Added by l00198894 for V9R1 STK����, 2013/07/11, end */

/*****************************************************************************
 �� �� ��  : NAS_CC_CheckHoldMptyOperation
 ��������  : ���Hold MPTY�����Ƿ�����ڵ�ǰ״̬�½���
 �������  : enHoldState   - ����״̬
             enMptyState   - MPTY״̬
 �������  : ��
 �� �� ֵ  : VOS_OK - ���ͨ���� VOS_ERR - ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��15��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
LOCAL VOS_UINT32 NAS_CC_CheckHoldMptyOperation(
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       enHoldState,
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enMptyState
)
{
    /* Modified by l00198894 for V9R1 STK����, 2013/07/11, begin */
    /* ����: ������MPTY�У���δ������ */
    if ((NAS_CC_MPTY_AUX_S_CALL_IN_MPTY == enMptyState)
     && (NAS_CC_HOLD_AUX_S_IDLE == enHoldState))
    {
        return NAS_CC_CheckSsSwitchHoldAllowed();
    }

    NAS_CC_WARN_LOG1("NAS_CC_CheckHoldMptyOperation hold mpty error enMptyState :", enMptyState);
    return VOS_ERR;
    /* Modified by l00198894 for V9R1 STK����, 2013/07/11, end */

}

/*****************************************************************************
 �� �� ��  : NAS_CC_CheckRetrieveMptyOperation
 ��������  : ���RETRIEVE MPTY�����Ƿ�����ڵ�ǰ״̬�½���
 �������  : enHoldState   - ����״̬
             enMptyState   - MPTY״̬
 �������  : ��
 �� �� ֵ  : VOS_OK - ���ͨ���� VOS_ERR - ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��15��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
LOCAL VOS_UINT32 NAS_CC_CheckRetrieveMptyOperation(
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       enHoldState,
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enMptyState
)
{
    /* Modified by l00198894 for V9R1 STK����, 2013/07/11, begin */
    /* ����: ������MPTY�У��ұ����� */
    if ((NAS_CC_MPTY_AUX_S_CALL_IN_MPTY == enMptyState)
     && (NAS_CC_HOLD_AUX_S_CALL_HELD == enHoldState))
    {
        return NAS_CC_CheckSsSwitchRetrieveAllowed();
    }

    NAS_CC_WARN_LOG1("NAS_CC_CheckRetrieveMptyOperation retrieve mpty error enMptyState :", enMptyState);
    return VOS_ERR;
    /* Modified by l00198894 for V9R1 STK����, 2013/07/11, end */
}

/*****************************************************************************
 �� �� ��  : NAS_CC_CheckSplitMptyOperation
 ��������  : ���SPLIT MPTY�����Ƿ�����ڵ�ǰ״̬�½���
 �������  : enHoldState   - ����״̬
              enMptyState   - MPTY״̬
 �������  : ��
 �� �� ֵ  : VOS_OK - ���ͨ���� VOS_ERR - ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��15��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_UINT32 NAS_CC_CheckSplitMptyOperation(
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       enHoldState,
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enMptyState
)
{
    /* ����: ������MPTY�У���δ������ */
    if ((NAS_CC_MPTY_AUX_S_CALL_IN_MPTY == enMptyState)
     && (NAS_CC_HOLD_AUX_S_IDLE == enHoldState))
    {
        return VOS_OK;
    }
    else
    {
        NAS_CC_WARN_LOG1("NAS_CC_CheckSplitMptyOperation split mpty error enMptyState :", enMptyState);
        return VOS_ERR;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_CC_CheckMptyOperation
 ��������  : ���MPTY�����Ƿ�����ڵ�ǰ״̬�½���
 �������  : entityId      - CCʵ���ID
              enSsOperation - �����Ĳ���ҵ����
 �������  : ��
 �� �� ֵ  : VOS_OK - ���ͨ���� VOS_ERR - ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��15��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_CC_CheckMptyOperation(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_SS_OPERATION_ENUM_U8            enSsOperation
)
{

    NAS_CC_CALL_STATE_ENUM_U8     enCallState = NAS_CC_GetCallState(entityId);
    NAS_CC_HOLD_AUX_STATE_ENUM_U8 enHoldState = NAS_CC_GetHoldAuxState(entityId);
    NAS_CC_MPTY_AUX_STATE_ENUM_U8 enMptyState = NAS_CC_GetMptyAuxState(entityId);

    switch (enSsOperation)
    {
    case NAS_SS_OPERATION_BUILD_MPTY:
        return NAS_CC_CheckBuildMptyOperation(entityId,
                                          enCallState,
                                          enHoldState,
                                          enMptyState);

    case NAS_SS_OPERATION_HOLD_MPTY:
        return NAS_CC_CheckHoldMptyOperation(enHoldState, enMptyState);

    case NAS_SS_OPERATION_RETRIEVE_MPTY:
        return NAS_CC_CheckRetrieveMptyOperation(enHoldState, enMptyState);

    case NAS_SS_OPERATION_SPLIT_MPTY:
        return NAS_CC_CheckSplitMptyOperation(enHoldState, enMptyState);

    default:
        NAS_CC_NORM_LOG("NAS_CC_CheckMptyOperation: No check for this operation.");
        return VOS_OK;
    }
}



/*****************************************************************************
 �� �� ��  : NAS_CC_ConditionalChangeAuxState
 ��������  : �������ĸı���еĴ�״̬���ú������ı����з���������CCʵ��Ĵ�״̬��
 �������  : bCheckHoldState   - �Ƿ��鵱ǰ�ĺ��б���״̬
              bCheckMptyState   - �Ƿ��鵱ǰ��MPTY״̬
              bChangeHoldState  - �Ƿ�ı���б���״̬
              bChangeMptyState  - �Ƿ�ı�MPTY״̬
              enExpectHoldState - �����ĺ��б���״̬(���bCheckHoldStateΪFALSE, �ò���������)
              enExpectMptyState - ������MPTY״̬(���bCheckMptyStateΪFALSE, �ò���������)
              enNewHoldState    - �µĺ��б���״̬(���bChangeHoldStateΪFALSE, �ò���������)
              enNewMptyState    - �µ�MPTY״̬(���bChangeMptyStateΪFALSE, �ò���������)
 �������  : ��
 �� �� ֵ  : �����˺��д�״̬�ı��CCʵ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��6��17��
    ��    ��   : z00234330
    �޸�����   : TQE����
*****************************************************************************/
LOCAL VOS_UINT32  NAS_CC_ConditionalChangeAuxState(
    VOS_BOOL                            bCheckHoldState,
    VOS_BOOL                            bCheckMptyState,
    VOS_BOOL                            bChangeHoldState,
    VOS_BOOL                            bChangeMptyState,
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       enExpectHoldState,
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enExpectMptyState,
    NAS_CC_HOLD_AUX_STATE_ENUM_U8       enNewHoldState,
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enNewMptyState
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulChanged = 0;
    VOS_BOOL                            bCheckOk;

    for (i=0; i<NAS_CC_MAX_ENTITY_NUM; i++)
    {
        /* ֻ������ʹ�õ�ʵ����ܸı�״̬ */
        bCheckOk = f_astCcEntities[i].bUsed;

        /* ֻ�к���״̬ΪActive��MO Modify��ʵ����ܸı��״̬ */
        bCheckOk &= ((NAS_CC_CALL_STATE_U10 == f_astCcEntities[i].enCallState) ||
                     (NAS_CC_CALL_STATE_U26 == f_astCcEntities[i].enCallState)) ?
                     VOS_TRUE : VOS_FALSE;

        /* ��鵱ǰ�ĺ��б���״̬�Ƿ��������� */
        if (bCheckHoldState)
        {
            bCheckOk &= (f_astCcEntities[i].enHoldAuxState == enExpectHoldState) ?
                     VOS_TRUE : VOS_FALSE;
        }

        /* ��鵱ǰ��MPTY״̬�Ƿ��������� */
        if (bCheckMptyState)
        {
            bCheckOk &= (f_astCcEntities[i].enMptyAuxState == enExpectMptyState) ?
                     VOS_TRUE : VOS_FALSE;
        }

        /* Modified by z00234330 for coverity����, 2014-06-16, begin */
        /* �����鲻ͨ�����޸Ĵ�ʵ���״̬�����ż����һ�� */
        if ( VOS_FALSE == bCheckOk)
        {
            continue;
        }
        /* Modified by z00234330 for coverity����, 2014-06-16, end */

        /* �ı���б���״̬ */
        if (bChangeHoldState)
        {
            NAS_CC_ChangeHoldAuxState(i, enNewHoldState);
        }

        /* �ı�MPTY״̬ */
        if (bChangeMptyState)
        {
            if((NAS_CC_MPTY_AUX_S_MPTY_REQ == enNewMptyState)
                && (NAS_CC_MPTY_AUX_S_CALL_IN_MPTY == f_astCcEntities[i].enMptyAuxState))
            {
                continue;
            }
            NAS_CC_ChangeMptyAuxState(i, enNewMptyState);
        }

        ulChanged++;
    }

    return ulChanged;
}


/*****************************************************************************
 �� �� ��  : NAS_CC_HandleMptyEventInvoke
 ��������  : ��������һ��MPTY�����¼����ı����CCʵ��Ĵ�״̬
 �������  : entityId      - �����¼���CCʵ���ID
              enSsOperation - ������¼��Ĳ���ҵ�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_HandleMptyEventInvoke(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_SS_OPERATION_ENUM_U8            enSsOperation
)
{
    if (NAS_SS_OPERATION_BUILD_MPTY == enSsOperation)
    {
        (VOS_VOID)NAS_CC_ConditionalChangeAuxState(
                                         VOS_FALSE,
                                         VOS_FALSE,
                                         VOS_FALSE,
                                         VOS_TRUE,
                                         0,
                                         0,
                                         0,
                                         NAS_CC_MPTY_AUX_S_MPTY_REQ
                                         );
    }
    else if (NAS_SS_OPERATION_HOLD_MPTY == enSsOperation)
    {
        (VOS_VOID)NAS_CC_ConditionalChangeAuxState(
                                         VOS_FALSE,
                                         VOS_TRUE,
                                         VOS_TRUE,
                                         VOS_FALSE,
                                         0,
                                         NAS_CC_MPTY_AUX_S_CALL_IN_MPTY,
                                         NAS_CC_HOLD_AUX_S_HOLD_REQ,
                                         0
                                         );

        /* Added by l00198894 for V9R1 STK����, 2013/07/11, begin */
        NAS_CC_SetSsSwitchHoldInfo(entityId, NAS_CC_SS_SWITCH_WAIT_CNF, NAS_CC_CAUSE_NULL);
        /* Added by l00198894 for V9R1 STK����, 2013/07/11, end */
    }
    else if (NAS_SS_OPERATION_RETRIEVE_MPTY == enSsOperation)
    {
        (VOS_VOID)NAS_CC_ConditionalChangeAuxState(
                                         VOS_FALSE,
                                         VOS_TRUE,
                                         VOS_TRUE,
                                         VOS_FALSE,
                                         0,
                                         NAS_CC_MPTY_AUX_S_CALL_IN_MPTY,
                                         NAS_CC_HOLD_AUX_S_RETRIEVE_REQ,
                                         0
                                         );

        /* Added by l00198894 for V9R1 STK����, 2013/07/11, begin */
        NAS_CC_SetSsSwitchRetrieveInfo(entityId, NAS_CC_SS_SWITCH_WAIT_CNF, NAS_CC_CAUSE_NULL);
        /* Added by l00198894 for V9R1 STK����, 2013/07/11, end */
    }
    else if (NAS_SS_OPERATION_SPLIT_MPTY == enSsOperation)
    {
        if ((VOS_TRUE == f_astCcEntities[entityId].bUsed) &&
            (NAS_CC_MPTY_AUX_S_CALL_IN_MPTY == f_astCcEntities[entityId].enMptyAuxState))
        {
            f_astCcEntities[entityId].enMptyAuxState = NAS_CC_MPTY_AUX_S_SPLIT_REQ;
        }
        else
        {
            NAS_CC_ERR_LOG("NAS_CC_HandleMptyEventInvoke: Can not split.");
        }
    }
    else
    {
        NAS_CC_WARN_LOG("NAS_CC_HandleMptyEventInvoke: Event ignored.");
    }
}

/*****************************************************************************
 �� �� ��  : NAS_CC_HandleMptyEventSuccess
 ��������  : ����MPTY�����ɹ��¼����ı����CCʵ��Ĵ�״̬
 �������  : entityId      - �����¼���CCʵ���ID
              enSsOperation - ������¼��Ĳ���ҵ�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_HandleMptyEventSuccess(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_SS_OPERATION_ENUM_U8            enSsOperation
)
{
    if (NAS_SS_OPERATION_BUILD_MPTY == enSsOperation)
    {
        (VOS_VOID)NAS_CC_ConditionalChangeAuxState(
                                         VOS_FALSE,
                                         VOS_FALSE,
                                         VOS_TRUE,
                                         VOS_TRUE,
                                         0,
                                         0,
                                         NAS_CC_HOLD_AUX_S_IDLE,
                                         NAS_CC_MPTY_AUX_S_CALL_IN_MPTY
                                         );
    }
    else if (NAS_SS_OPERATION_HOLD_MPTY == enSsOperation)
    {
        /* Modified by l00198894 for V9R1 STK����, 2013/07/11, begin */
        /* ��¼����ҵ���л�״̬ */
        NAS_CC_SetSsSwitchHoldInfo(entityId, NAS_CC_SS_SWITCH_SUCCESS, NAS_CC_CAUSE_NULL);
        /* Modified by l00198894 for V9R1 STK����, 2013/07/11, end */
    }
    else if (NAS_SS_OPERATION_RETRIEVE_MPTY == enSsOperation)
    {
        /* Modified by l00198894 for V9R1 STK����, 2013/07/11, begin */
        /* ��¼����ҵ���л�״̬ */
        NAS_CC_SetSsSwitchRetrieveInfo(entityId, NAS_CC_SS_SWITCH_SUCCESS, NAS_CC_CAUSE_NULL);
        /* Modified by l00198894 for V9R1 STK����, 2013/07/11, end */
    }
    else if (NAS_SS_OPERATION_SPLIT_MPTY == enSsOperation)
    {
        if ((VOS_TRUE == f_astCcEntities[entityId].bUsed) &&
            (NAS_CC_MPTY_AUX_S_SPLIT_REQ == f_astCcEntities[entityId].enMptyAuxState))
        {
            f_astCcEntities[entityId].enMptyAuxState = NAS_CC_MPTY_AUX_S_IDLE;
            f_astCcEntities[entityId].enHoldAuxState = NAS_CC_HOLD_AUX_S_IDLE;

            (VOS_VOID)NAS_CC_ConditionalChangeAuxState(
                                             VOS_FALSE,
                                             VOS_TRUE,
                                             VOS_TRUE,
                                             VOS_FALSE,
                                             0,
                                             NAS_CC_MPTY_AUX_S_CALL_IN_MPTY,
                                             NAS_CC_HOLD_AUX_S_CALL_HELD,
                                             0
                                             );
        }
        else
        {
            NAS_CC_ERR_LOG("NAS_CC_HandleMptyEventSuccess: Not spliting MPTY.");
        }
    }
    else
    {
        NAS_CC_WARN_LOG("NAS_CC_HandleMptyEventSuccess: Event ignored.");
    }

}

/*****************************************************************************
 �� �� ��  : NAS_CC_HandleMptyEventFail
 ��������  : ����MPTY����ʧ���¼����ı����CCʵ��Ĵ�״̬
 �������  : entityId      - �����¼���CCʵ���ID
              enSsOperation - ������¼��Ĳ���ҵ�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
LOCAL VOS_VOID  NAS_CC_HandleMptyEventFail(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_SS_OPERATION_ENUM_U8            enSsOperation
)
{
    VOS_UINT32                          ulHeldCnt;
    VOS_UINT32                          ulIdleCnt;

    if (NAS_SS_OPERATION_BUILD_MPTY == enSsOperation)
    {
        /* ��Ҫ������MPTY�еĺ��е�MPTY״̬�ı�Ϊin MPTY��������MPTY�еĺ���
           ��MPTY״̬��ΪIDLE��Ϊ�������Ҫ����Ҫ������MPTY�Ͳ���MPTY�еĺ��С�
           ����ͨ���鿴HELD��IDLE�ĺ��и��ж��ٸ���ʵ��������֡�*/
        ulHeldCnt = NAS_CC_ConditionalChangeAuxState(
                                         VOS_TRUE,
                                         VOS_TRUE,
                                         VOS_FALSE,
                                         VOS_TRUE,
                                         NAS_CC_HOLD_AUX_S_CALL_HELD,
                                         NAS_CC_MPTY_AUX_S_MPTY_REQ,
                                         0,
                                         NAS_CC_MPTY_AUX_S_IDLE );

        ulIdleCnt = NAS_CC_ConditionalChangeAuxState(
                                         VOS_TRUE,
                                         VOS_TRUE,
                                         VOS_FALSE,
                                         VOS_TRUE,
                                         NAS_CC_HOLD_AUX_S_IDLE,
                                         NAS_CC_MPTY_AUX_S_MPTY_REQ,
                                         0,
                                         NAS_CC_MPTY_AUX_S_IDLE );

        if (ulHeldCnt > 1)
        {
            /* HELD�ĺ���������1������HELD�ĺ�����MPTY�� */
            (VOS_VOID)NAS_CC_ConditionalChangeAuxState(
                                         VOS_TRUE,
                                         VOS_TRUE,
                                         VOS_FALSE,
                                         VOS_TRUE,
                                         NAS_CC_HOLD_AUX_S_CALL_HELD,
                                         NAS_CC_MPTY_AUX_S_MPTY_REQ,
                                         0,
                                         NAS_CC_MPTY_AUX_S_CALL_IN_MPTY);
        }

        if (ulIdleCnt > 1)
        {
            /* IDLE�ĺ���������1������IDLE�ĺ�����MPTY�� */
            (VOS_VOID)NAS_CC_ConditionalChangeAuxState(
                                         VOS_TRUE,
                                         VOS_TRUE,
                                         VOS_FALSE,
                                         VOS_TRUE,
                                         NAS_CC_HOLD_AUX_S_IDLE,
                                         NAS_CC_MPTY_AUX_S_MPTY_REQ,
                                         0,
                                         NAS_CC_MPTY_AUX_S_CALL_IN_MPTY);
        }
    }
    else if (NAS_SS_OPERATION_HOLD_MPTY == enSsOperation)
    {
        /* Modified by l00198894 for V9R1 STK����, 2013/07/11, begin */
        /* ��¼����ҵ���л�״̬ */
        NAS_CC_SetSsSwitchHoldInfo(entityId, NAS_CC_SS_SWITCH_FAILED, NAS_CC_CAUSE_NULL);
        /* Modified by l00198894 for V9R1 STK����, 2013/07/11, end */
    }
    else if (NAS_SS_OPERATION_RETRIEVE_MPTY == enSsOperation)
    {
        /* Modified by l00198894 for V9R1 STK����, 2013/07/11, begin */
        /* ��¼����ҵ���л�״̬ */
        NAS_CC_SetSsSwitchRetrieveInfo(entityId, NAS_CC_SS_SWITCH_FAILED, NAS_CC_CAUSE_NULL);
        /* Modified by l00198894 for V9R1 STK����, 2013/07/11, end */
    }
    else if (NAS_SS_OPERATION_SPLIT_MPTY == enSsOperation)
    {
        if ((VOS_TRUE == f_astCcEntities[entityId].bUsed) &&
            (NAS_CC_MPTY_AUX_S_SPLIT_REQ == f_astCcEntities[entityId].enMptyAuxState))
        {
            f_astCcEntities[entityId].enMptyAuxState = NAS_CC_MPTY_AUX_S_CALL_IN_MPTY;
        }
        else
        {
            NAS_CC_ERR_LOG("NAS_CC_HandleMptyEventFail: Not spliting MPTY.");
        }
    }
    else
    {
        NAS_CC_WARN_LOG("NAS_CC_HandleMptyEventFail: Event ignored.");
    }

}

/*****************************************************************************
 �� �� ��  : NAS_CC_HandleMptyEvent
 ��������  : ����MPTY�¼������ݷ������¼��ı����CCʵ��Ĵ�״̬
 �������  : entityId      - �����¼���CCʵ���ID
              enMptyEvent   - �������¼�
              enSsOperation - ������¼��Ĳ���ҵ�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  NAS_CC_HandleMptyEvent(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_MPTY_EVT_ENUM                enMptyEvent,
    NAS_SS_OPERATION_ENUM_U8            enSsOperation
)
{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_HandleMptyEvent: entityId wrong.");
        return;
    }

    NAS_CC_ASSERT(VOS_TRUE == f_astCcEntities[entityId].bUsed);

    switch (enMptyEvent)
    {
    case NAS_CC_MPTY_EVT_INVOKE:
        NAS_CC_HandleMptyEventInvoke(entityId, enSsOperation);
        break;

    case NAS_CC_MPTY_EVT_SUCCESS:
        NAS_CC_HandleMptyEventSuccess(entityId, enSsOperation);
        break;

    case NAS_CC_MPTY_EVT_FAIL:
        NAS_CC_HandleMptyEventFail(entityId, enSsOperation);
        break;

    default:
        break;
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_GetDtmfState
 ��������  : ��ȡָ��CCʵ���DTMF״̬
 �������  : entityId - CCʵ���ID
 �������  : ��
 �� �� ֵ  : ��ʵ���DTMF״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
NAS_CC_DTMF_STATE_ENUM  NAS_CC_GetDtmfState(
    NAS_CC_ENTITY_ID_T                  entityId
)
{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_GetDtmfState: entityId wrong.");
        return NAS_CC_DTMF_S_UNKNOWN;
    }

    NAS_CC_ASSERT(VOS_TRUE == f_astCcEntities[entityId].bUsed);

    return f_astCcEntities[entityId].enDtmfState;
}


/*****************************************************************************
 �� �� ��  : NAS_CC_ChangeDtmfState
 ��������  : �ı�ָ��CCʵ���DTMF״̬
 �������  : entityId - CCʵ���ID
              enState  - �µ�DTMF״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  NAS_CC_ChangeDtmfState(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_DTMF_STATE_ENUM              enState
)
{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_ChangeDtmfState: entityId wrong.");
        return;
    }

    NAS_CC_ASSERT(VOS_TRUE == f_astCcEntities[entityId].bUsed);

    f_astCcEntities[entityId].enDtmfState = enState;

    NAS_CC_NORM_LOG1("CC change DTMF state to :", enState);
}
/*****************************************************************************
 �� �� ��  : NAS_CC_GetDtmfQState
 ��������  : ��ȡָ��CCʵ���DTMF����״̬
 �������  : entityId - CCʵ���ID
 �������  : ��
 �� �� ֵ  : ��ʵ���DTMF����״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��12��02��
    ��    ��   : S62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
NAS_CC_DTMF_Q_STATE_ENUM  NAS_CC_GetDtmfQState(
    NAS_CC_ENTITY_ID_T                  entityId
)
{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_GetDtmfQState: entityId wrong.");
        return NAS_CC_DTMF_Q_UNKNOWN;
    }

    NAS_CC_ASSERT(VOS_TRUE == f_astCcEntities[entityId].bUsed);
    return f_astDtmfQState[entityId];
}


/*****************************************************************************
 �� �� ��  : NAS_CC_ChangeDtmfQState
 ��������  : �ı�ָ��CCʵ���DTMF����״̬
 �������  : entityId - CCʵ���ID
              enState  - �µ�DTMF����״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��12��02��
    ��    ��   : S62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  NAS_CC_ChangeDtmfQState(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_DTMF_Q_STATE_ENUM            enState
)
{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_ChangeDtmfQState: entityId wrong.");
        return;
    }

    NAS_CC_ASSERT(VOS_TRUE == f_astCcEntities[entityId].bUsed);
    f_astDtmfQState[entityId] = enState;
    NAS_CC_INFO_LOG1("CC change DTMF state to :", enState);
}


/*****************************************************************************
 �� �� ��  : NAS_CC_QueueDtmfReq
 ��������  : ��һ��DTMF������뻺�����
 �������  : entityId  - CCʵ���ID
              enDtmfReq - DTMF���������(START/STOP)
              ucKey     - Start DTMF�����е�DTMF�ַ���������������ΪSTARTʱ��Ч
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��22��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2008��9��11��
    ��    ��   :S62952
    �޸�����   : ���ⵥ��:AT2D05593
  3.��    ��   : 2008��12��15��
    ��    ��   :S62952
    �޸�����   : ���ⵥ��:AT2D07162
  4.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  NAS_CC_QueueDtmfReq(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_DTMF_REQ_ENUM_U8             enDtmfReq,
    VOS_UINT8                           ucKey
)
{
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause;
    NAS_CC_DTMF_Q_STATE_ENUM            enstate;
    NAS_CC_DTMF_REQ_RECORD_STRU        *pstCurrRecord;

    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_QueueDtmfReq: entityId wrong.");
        return;
    }

    enstate = NAS_CC_GetDtmfQState(entityId);
    if (f_astCcEntities[entityId].ucDtmfReqCnt < NAS_CC_MAX_DTMF_BUF_LEN)
    {
        if(enDtmfReq == NAS_CC_DTMF_START_REQ)
        {
            if(enstate != NAS_CC_DTMF_Q_START_REQ)
            {
                pstCurrRecord = &f_astCcEntities[entityId].astDtmfReqBuf[f_astCcEntities[entityId].ucDtmfReqCnt];
                pstCurrRecord->enReq = enDtmfReq;
                pstCurrRecord->ucKey = ucKey;
                f_astCcEntities[entityId].ucDtmfReqCnt++;
                NAS_CC_ChangeDtmfQState(entityId,NAS_CC_DTMF_Q_START_REQ);

            }
            else
            {
                enCause = NAS_CC_CAUSE_128;
                NAS_CC_SendMnccMsg(entityId, MNCC_START_DTMF_REJ, &enCause, sizeof(enCause));
                NAS_CC_ERR_LOG("NAS_CC_QueueDtmfReq: discard DTMFStarREQ.");
            }

        }
        else
        {
            if(enstate != NAS_CC_DTMF_Q_STOP_REQ)
            {
                pstCurrRecord = &f_astCcEntities[entityId].astDtmfReqBuf[f_astCcEntities[entityId].ucDtmfReqCnt];
                pstCurrRecord->enReq = enDtmfReq;
                pstCurrRecord->ucKey = ucKey;
                f_astCcEntities[entityId].ucDtmfReqCnt++;
                NAS_CC_ChangeDtmfQState(entityId,NAS_CC_DTMF_Q_STOP_REQ);

            }
            else
            {
                NAS_CC_SendMnccMsg(entityId, MNCC_STOP_DTMF_CNF, VOS_NULL_PTR, 0);
                NAS_CC_ERR_LOG("NAS_CC_QueueDtmfReq: discard DTMFStopREQ.");

            }

        }
    }
    else
    {
        if(enDtmfReq == NAS_CC_DTMF_START_REQ)
        {
            enCause = NAS_CC_CAUSE_128;
            NAS_CC_SendMnccMsg(entityId, MNCC_START_DTMF_REJ, &enCause, sizeof(enCause));
            NAS_CC_WARN_LOG("NAS_CC_QueueDtmfReq: DTMF buffer is full.");
        }
        else
        {
            NAS_CC_SendMnccMsg(entityId, MNCC_STOP_DTMF_CNF, VOS_NULL_PTR, 0);
            NAS_CC_WARN_LOG("NAS_CC_QueueDtmfReq: DTMF buffer is full.");
        }
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_DequeueDtmfReq
 ��������  : �ӻ�����ȡ��һ��DTMF����
 �������  : entityId  - CCʵ��ID
 �������  : pstRecord - ȡ�õ�DTMF�����¼
 �� �� ֵ  : VOS_OK - ȡ�óɹ�;  VOS_ERR - ������Ϊ�գ�ȡ��ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��19��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  4.��    ��   : 2008��12��15��
    ��    ��   :S62952
    �޸�����   : ���ⵥ��:AT2D07162
  5.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
LOCAL VOS_UINT32 NAS_CC_DequeueDtmfReq(
    NAS_CC_ENTITY_ID_T                  entityId,
    NAS_CC_DTMF_REQ_RECORD_STRU        *pstRecord
)
{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_DequeueDtmfReq: entityId wrong.");
        return VOS_ERR;
    }

    if (f_astCcEntities[entityId].ucDtmfReqCnt > 0)
    {
        PS_MEM_CPY(pstRecord,
                   &f_astCcEntities[entityId].astDtmfReqBuf[0],
                   sizeof(NAS_CC_DTMF_REQ_RECORD_STRU));

        f_astCcEntities[entityId].ucDtmfReqCnt--;

        /* ��������ʣ������м�¼ǰ�� */
        if (f_astCcEntities[entityId].ucDtmfReqCnt > 0)
        {
            PS_MEM_CPY(&f_astCcEntities[entityId].astDtmfReqBuf[0],
                       &f_astCcEntities[entityId].astDtmfReqBuf[1],
                       f_astCcEntities[entityId].ucDtmfReqCnt * sizeof(NAS_CC_DTMF_REQ_RECORD_STRU));
        }
        else
        {
            NAS_CC_ChangeDtmfQState(entityId, NAS_CC_DTMF_Q_NULL);
        }

        return VOS_OK;
    }
    else
    {
        NAS_CC_WARN_LOG1("NAS_CC_DequeueDtmfReq ucDtmfReqCnt", f_astCcEntities[entityId].ucDtmfReqCnt);
        return VOS_ERR;
    }

}


/*****************************************************************************
 �� �� ��  : NAS_CC_SendBufferedDtmfReq
 ��������  : ����һ�������DTMF����
 �������  : entityId  - CCʵ��ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��19��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  NAS_CC_SendBufferedDtmfReq(
    NAS_CC_ENTITY_ID_T                  entityId
)
{
    NAS_CC_DTMF_REQ_RECORD_STRU             stDtmfReq;


    stDtmfReq.enReq = NAS_CC_DTMF_REQ_BUTT;
    stDtmfReq.ucKey = 0;

    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_SendBufferedDtmfReq: entityId wrong.");
        return;
    }

    if (NAS_CC_DequeueDtmfReq(entityId, &stDtmfReq) == VOS_OK)
    {
        VOS_UINT8  ucTi = NAS_CC_GetEntityTi(entityId);

        if (NAS_CC_DTMF_START_REQ == stDtmfReq.enReq)
        {
            NAS_CC_SendStartDtmf(ucTi, stDtmfReq.ucKey);
            NAS_CC_StartTimer(entityId, TI_NAS_CC_T336, 0);
            NAS_CC_INFO_LOG("NAS_CC_SendBufferedDtmfReq ChangeDtmfState to START_REQ");
            NAS_CC_ChangeDtmfState(entityId, NAS_CC_DTMF_S_START_REQ);
        }
        else
        {
            NAS_CC_SendStopDtmf(ucTi);
            NAS_CC_StartTimer(entityId, TI_NAS_CC_T337, 0);
            NAS_CC_INFO_LOG("NAS_CC_SendBufferedDtmfReq ChangeDtmfState to STOP_REQ");
            NAS_CC_ChangeDtmfState(entityId, NAS_CC_DTMF_S_STOP_REQ);
        }
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_StoreSsOperation
 ��������  : ͨ��invoke���͵�facility��Ϣ���𲹳�ҵ�����ʱ�����øú����洢��
             ����ҵ��������Ա��յ������facility�ظ�ʱ����invoke ID�õ���Ӧ��
             ����ҵ�������
 �������  : entityId      - CCʵ���ID
              ucInvokeId    - ����ҵ�������invoke ID
              enSsOperation - ����ҵ�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��15��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��6��17��
    ��    ��   : z00234330
    �޸�����   : TQE����

*****************************************************************************/
VOS_VOID NAS_CC_StoreSsOperation(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucInvokeId,
    NAS_SS_OPERATION_ENUM_U8            enSsOperation
)
{
    VOS_UINT32 i;
    VOS_UINT32 ulStorePos = NAS_CC_MAX_STORED_SS_OPERATION;

    NAS_CC_ASSERT(entityId < NAS_CC_MAX_ENTITY_NUM);

    for (i=0; i<NAS_CC_MAX_STORED_SS_OPERATION; i++)
    {
        /*
        ����Ҫ����Ƿ�����ͬ��invoke ID�������ˣ��������ҵ��յĴ洢λ�ú�ֻ�Ǽ�¼
        ��������������������ѭ��
        */
        /* Modified by z00234330 for coverity����, 2014-06-16, begin */
        if ( (VOS_FALSE == f_astCcSsOperations[i].bUsed)
          && (NAS_CC_MAX_STORED_SS_OPERATION == ulStorePos))
        {
            ulStorePos = i;
        }

        if ((VOS_TRUE == f_astCcSsOperations[i].bUsed)
         && (f_astCcSsOperations[i].entityId == entityId)
         && (f_astCcSsOperations[i].ucInvokeId == ucInvokeId))
        {
            /* ��һ��invoke ID�洢�����ǲ�����ģ��ڳ�����ȷ��������ǲ�Ӧ���ֵ� */
            NAS_CC_ERR_LOG("NAS_CC_StoreSsOperation: This invoke ID is in use.");
            return;
        }

        /* Modified by z00234330 for coverity����, 2014-06-16, end */
    }

    if (ulStorePos != NAS_CC_MAX_STORED_SS_OPERATION)
    {
        f_astCcSsOperations[ulStorePos].entityId = entityId;
        f_astCcSsOperations[ulStorePos].ucInvokeId = ucInvokeId;
        f_astCcSsOperations[ulStorePos].enOperation = enSsOperation;
        f_astCcSsOperations[ulStorePos].bUsed = VOS_TRUE;
    }
    else
    {
        /* �洢�ռ䲻�������Ӧ�����ڵ��Խ׶ν���ģ��ú�����Ӧ����ʧ�� */
        NAS_CC_ERR_LOG("NAS_CC_StoreSsOperation: The storage is full.");
    }
}


/*****************************************************************************
 �� �� ��  : NAS_CC_RestoreSsOperation
 ��������  : ȡ�ô洢�Ĳ���ҵ�������������ô洢��
 �������  : entityId      - CCʵ���ID
              ucInvokeId    - ����ҵ�������invoke ID
 �������  : penSsOperation - ȡ�õĲ���ҵ�������
 �� �� ֵ  : VOS_OK - �����ɹ���VOS_ERR - û���ҵ����������Ĵ洢�����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��15��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��6��17��
    ��    ��   : z00234330
    �޸�����   : TQE����
*****************************************************************************/
VOS_UINT32 NAS_CC_RestoreSsOperation(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucInvokeId,
    NAS_SS_OPERATION_ENUM_U8           *penSsOperation
)
{
    VOS_UINT32 i;

    NAS_CC_ASSERT(entityId < NAS_CC_MAX_ENTITY_NUM);

    for (i=0; i<NAS_CC_MAX_STORED_SS_OPERATION; i++)
    {
        /* Modified by z00234330 for coverity����, 2014-06-16, begin */
        if ((VOS_TRUE == f_astCcSsOperations[i].bUsed)
         && (f_astCcSsOperations[i].entityId == entityId)
         && (f_astCcSsOperations[i].ucInvokeId == ucInvokeId))
        {
            *penSsOperation = f_astCcSsOperations[i].enOperation;
            f_astCcSsOperations[i].bUsed = VOS_FALSE;
            return VOS_OK;
        }
        /* Modified by z00234330 for coverity����, 2014-06-16, end */
    }

    return VOS_ERR;
}


/*****************************************************************************
 �� �� ��  : NAS_CC_GetStoredSsOperation
 ��������  : ȡ�ô洢�Ĳ���ҵ�����
 �������  : entityId      - CCʵ���ID
              ucInvokeId    - ����ҵ�������invoke ID
 �������  : penSsOperation - ȡ�õĲ���ҵ�������
 �� �� ֵ  : VOS_OK - �����ɹ���VOS_ERR - û���ҵ����������Ĵ洢�����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��15��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��6��17��
    ��    ��   : z00234330
    �޸�����   : TQE����

*****************************************************************************/
VOS_UINT32 NAS_CC_GetStoredSsOperation(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT8                           ucInvokeId,
    NAS_SS_OPERATION_ENUM_U8            *penSsOperation
)
{
    VOS_UINT32 i;

    NAS_CC_ASSERT(entityId < NAS_CC_MAX_ENTITY_NUM);

    for (i=0; i<NAS_CC_MAX_STORED_SS_OPERATION; i++)
    {
        /* Modified by z00234330 for coverity����, 2014-06-16, begin */
        if ((VOS_TRUE == f_astCcSsOperations[i].bUsed)
         && (f_astCcSsOperations[i].entityId == entityId)
         && (f_astCcSsOperations[i].ucInvokeId == ucInvokeId))
        {
            *penSsOperation = f_astCcSsOperations[i].enOperation;
            return VOS_OK;
        }
        /* Modified by z00234330 for coverity����, 2014-06-16, end */
    }

    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_SetStartT310Flag
 ��������  : �����Ƿ���T310��ʱ����־
 �������  : entityId - CCʵ���ID
              bSet     - ���ñ�־
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��06��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_CC_SetStartT310Flag(
    NAS_CC_ENTITY_ID_T                  entityId,
    VOS_UINT32                          ulSet
)
{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_SetStartT310Flag: entityId wrong.");
        return;
    }

    NAS_CC_ASSERT(VOS_TRUE == f_astCcEntities[entityId].bUsed);

    f_astCcEntities[entityId].ulStartT310Flag = ulSet;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_GetStartT310Flag
 ��������  : ��ȡ�Ƿ�����T310�ı�־
 �������  : entityId - CCʵ���ID
 �������  : ��
 �� �� ֵ  : ��־��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��06��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_CC_GetStartT310Flag(
    NAS_CC_ENTITY_ID_T                  entityId
)
{
    if (entityId >= NAS_CC_MAX_ENTITY_NUM)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_GetStartT310Flag: entityId wrong.");
        return VOS_TRUE;
    }

    NAS_CC_ASSERT(VOS_TRUE == f_astCcEntities[entityId].bUsed);

    return f_astCcEntities[entityId].ulStartT310Flag;
}


/*****************************************************************************
 �� �� ��  : NAS_CC_IsAllowNewMtCall
 ��������  : �ж��Ƿ��ܽ����µ�MT����
 �������  : entityId - CCʵ���ID
 �������  : ��
 �� �� ֵ  : progress��־��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��15��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_BOOL  NAS_CC_IsAllowNewMtCall(VOS_VOID)
{
    VOS_UINT8                           i;

    for (i=0; i<NAS_CC_MAX_ENTITY_NUM; i++)
    {
        if (VOS_TRUE == f_astCcEntities[i].bUsed)
        {
            if ((NAS_CC_CALL_STATE_U0 != f_astCcEntities[i].enCallState)
              &&(NAS_CC_CALL_STATE_U10 != f_astCcEntities[i].enCallState)
              &&(NAS_CC_CALL_STATE_U26 != f_astCcEntities[i].enCallState)
              &&(NAS_CC_CALL_STATE_U27 != f_astCcEntities[i].enCallState))
            {
                return VOS_FALSE;
            }
        }
    }

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : NAS_CC_FlushDTMFBuff
 ��������  : ��������DTMF��Ϣ
 �������  : entityId - CCʵ��ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��07��02��
    ��    ��   : ����� 65478
    �޸�����   : �����ɺ��������ⵥ��:AT2D04057
  2.��    ��   : 2008��12��15��
    ��    ��   :S62952
    �޸�����   : ���ⵥ��:AT2D07162
  3.��    ��   : 2013��5��20��
    ��    ��   : s00217060
    �޸�����   : coverity��foritfy�޸�
*****************************************************************************/
VOS_VOID NAS_CC_FlushDTMFBuff(
    NAS_CC_ENTITY_ID_T                  entityId
)
{
    NAS_CC_DTMF_REQ_RECORD_STRU         stDtmfReq;
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause;
    VOS_UINT8                           i;

    /* Added by s00217060 for coverity��foritfy�޸� , 2013-05-20, begin */
    /* ��ʼ�� */
    PS_MEM_SET(&stDtmfReq, 0, sizeof(stDtmfReq));
    /* Added by s00217060 for coverity��foritfy�޸� , 2013-05-20, end */

    for (i = 0; i < NAS_CC_MAX_DTMF_BUF_LEN; i++)
    {
        if (NAS_CC_DequeueDtmfReq(entityId, &stDtmfReq) == VOS_OK)
        {
            if (NAS_CC_DTMF_START_REQ == stDtmfReq.enReq)
            {
                enCause = NAS_CC_CAUSE_111;
                NAS_CC_SendMnccMsg(entityId, MNCC_START_DTMF_REJ, &enCause, sizeof(enCause));
            }
            else
            {
                NAS_CC_SendMnccMsg(entityId, MNCC_STOP_DTMF_CNF, VOS_NULL_PTR, 0);
            }
        }
        else
        {
            break;
        }
    }
    NAS_CC_ChangeDtmfQState(entityId, NAS_CC_DTMF_Q_NULL);
}

/*****************************************************************************
 �� �� ��  : NAS_CC_AtTest
 ��������  : ��ά�ɲ��Զ���AT����
 �������  : enAtTesttyp -  ��������
             ucCallId    -  ����ID
 �������  : pstCcEntity -  ��ǰ����
 �� �� ֵ  : VOS_UINT32:��ȡ�ɹ���ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��17��
    ��    ��   : zhoujun /z40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_CC_AtTest(
    VOS_UINT8                           ucCallId,
    NAS_CC_STATE_INFO_STRU              *pstStateInfo
)
{
    /* ��������Ƿ�,ֱ�ӷ��س��� */
    if ( (ucCallId > NAS_CC_MAX_ENTITY_NUM)
      || (ucCallId < 1) )
    {
        return VOS_ERR;
    }

    if ( VOS_FALSE == f_astCcEntities[ucCallId - 1].bUsed )
    {
        return VOS_ERR;
    }

    pstStateInfo->ucCallId = f_astCcEntities[ucCallId - 1].ucCallId;
    pstStateInfo->ucTi = f_astCcEntities[ucCallId - 1].ucTi;
    pstStateInfo->enCallState = f_astCcEntities[ucCallId - 1].enCallState;
    pstStateInfo->enHoldAuxState = f_astCcEntities[ucCallId - 1].enHoldAuxState;
    pstStateInfo->enMptyAuxState = f_astCcEntities[ucCallId - 1].enMptyAuxState;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_SndOutsideContextData
 ��������  : ��CC�ⲿ��������ΪSDT��Ϣ���ͳ�ȥ���Ա��ڻط�ʱͨ��׮������ԭ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��11��30��
    ��    ��   : ��ë 00166186
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_CC_SndOutsideContextData()
{
    NAS_CC_SDT_MSG_ST                      *pSndMsgCB     = VOS_NULL_PTR;
    NAS_CC_OUTSIDE_RUNNING_CONTEXT_ST      *pstOutsideCtx;

    pSndMsgCB = (NAS_CC_SDT_MSG_ST *)PS_ALLOC_MSG(WUEPS_PID_CC, sizeof(NAS_CC_SDT_MSG_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        NAS_CC_ERR_LOG("NAS_CC_SndOutsideContextData:ERROR: Alloc Memory Fail.");
        return;
    }

    pstOutsideCtx = &pSndMsgCB->stOutsideCtx;

    PS_MEM_CPY(pstOutsideCtx->pc_g_f_astCcEntities, f_astCcEntities,NAS_CC_MAX_ENTITY_NUM * sizeof(NAS_CC_ENTITY_STRU));
    PS_MEM_CPY(pstOutsideCtx->pc_g_f_astDtmfQState, f_astDtmfQState,NAS_CC_MAX_ENTITY_NUM * sizeof(NAS_CC_DTMF_Q_STATE_ENUM));
    PS_MEM_CPY(pstOutsideCtx->pc_g_f_astCcSsOperations, f_astCcSsOperations,NAS_CC_MAX_STORED_SS_OPERATION * sizeof(NAS_CC_SS_OPERATION_ITEM_STRU));

    pSndMsgCB->MsgHeader.ulReceiverPid = WUEPS_PID_CC;
    pSndMsgCB->MsgHeader.ulSenderPid   = WUEPS_PID_CC;
    pSndMsgCB->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pSndMsgCB->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;

    pSndMsgCB->MsgHeader.ulLength  = sizeof(NAS_CC_OUTSIDE_RUNNING_CONTEXT_ST) + 4;
    pSndMsgCB->MsgHeader.ulMsgName = EVT_NAS_CC_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY;

    DIAG_TraceReport(pSndMsgCB);
    PS_FREE_MSG(WUEPS_PID_CC, pSndMsgCB);

    return;
}

#ifdef __PS_WIN32_RECUR__
/*****************************************************************************
 �� �� ��  : NAS_CC_RestoreContextData
 ��������  : �ָ�CCȫ�ֱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��12��1��
    ��    ��   : ��ë 00166186
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_CC_RestoreContextData(struct MsgCB * pMsg)
{
    NAS_CC_SDT_MSG_ST                      *pRcvMsgCB;
    NAS_CC_OUTSIDE_RUNNING_CONTEXT_ST      *pstOutsideCtx;

    pRcvMsgCB     = (NAS_CC_SDT_MSG_ST *)pMsg;
    pstOutsideCtx = &pRcvMsgCB->stOutsideCtx;

    if (EVT_NAS_CC_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY == pRcvMsgCB->MsgHeader.ulMsgName)
    {
        PS_MEM_CPY(f_astCcEntities,pstOutsideCtx->pc_g_f_astCcEntities, NAS_CC_MAX_ENTITY_NUM * sizeof(NAS_CC_ENTITY_STRU));
        PS_MEM_CPY(f_astDtmfQState,pstOutsideCtx->pc_g_f_astDtmfQState,NAS_CC_MAX_ENTITY_NUM * sizeof(NAS_CC_DTMF_Q_STATE_ENUM));
        PS_MEM_CPY(f_astCcSsOperations,pstOutsideCtx->pc_g_f_astCcSsOperations,NAS_CC_MAX_STORED_SS_OPERATION * sizeof(NAS_CC_SS_OPERATION_ITEM_STRU));

        PS_NAS_LOG(WUEPS_PID_CC, VOS_NULL, PS_LOG_LEVEL_INFO,"CC: NAS_CC_RestoreContextData - data is restored.");
        return VOS_TRUE;
    }
    return VOS_FALSE;
}
#endif


/*****************************************************************************
 �� �� ��  : NAS_CC_ProcAtPrimitive
 ��������  : ���պʹ�������AT��ԭ��
 �������  : pMsg - AT����CC����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��17��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_CC_ProcAtPrimitive(
    const VOS_VOID                      *pMsg
)
{
    MN_APP_REQ_MSG_STRU                *pMnAppReqMsg;

    pMnAppReqMsg = (MN_APP_REQ_MSG_STRU *)pMsg;

    switch (pMnAppReqMsg->usMsgName)
    {
        case AT_CC_MSG_STATE_QRY_REQ:
            NAS_CC_ProcAtCcStateQry(pMsg);
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_ProcAtCcStateQry
 ��������  : ���պʹ�������AT��AT_CC_MSG_STATE_QRY_REQԭ��
 �������  : pMsg - AT����CC����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��17��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_CC_ProcAtCcStateQry(
    const VOS_VOID                      *pMsg
)
{
    MN_APP_REQ_MSG_STRU                *pMnAppReqMsg;
    VOS_UINT8                           ucCallId;
    AT_CC_STATE_QRY_CNF_MSG_STRU       *pstAtCcStateQryCnfMsg;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucCallNum;

    /* ������Ϣ�ڴ� */
    pstAtCcStateQryCnfMsg = (AT_CC_STATE_QRY_CNF_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             WUEPS_PID_CC,
                                             sizeof(AT_CC_STATE_QRY_CNF_MSG_STRU));

    if( VOS_NULL_PTR == pstAtCcStateQryCnfMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_ProcAtCcStateQry:ERROR: Memory Alloc Error for pMsg");
        return;
    }

    /* ��ʼ�� */
    pMnAppReqMsg = (MN_APP_REQ_MSG_STRU *)pMsg;
    ucCallId     = pMnAppReqMsg->aucContent[0];
    ucCallNum    = 0;

    if (0 == ucCallId)
    {
        /* ��ѯ���к��� */
        for (ucCallId = 1 ; ucCallId <= MN_CALL_MAX_NUM ; ucCallId++ )
        {
            ulRet = NAS_CC_AtTest(ucCallId,&pstAtCcStateQryCnfMsg->astCcStateInfoList[ucCallNum]);
            if ( VOS_OK ==  ulRet)
            {
                pstAtCcStateQryCnfMsg->aucCallExist[ucCallNum] = 1;
                ucCallNum++;
            }
        }
    }
    else
    {
        /* ��ѯ�ض�call id ��Ϣ */
        ulRet = NAS_CC_AtTest(ucCallId,&pstAtCcStateQryCnfMsg->astCcStateInfoList[0]);
        if ( VOS_OK ==  ulRet)
        {
            pstAtCcStateQryCnfMsg->aucCallExist[0] = 1;
            ucCallNum = 1;
        }
        else
        {
            pstAtCcStateQryCnfMsg->aucCallExist[0] = 0;
        }
    }

    /* ���췢����Ϣ */
    pstAtCcStateQryCnfMsg->ulReceiverPid          = WUEPS_PID_AT;
    pstAtCcStateQryCnfMsg->ulMsgName              = AT_CC_MSG_STATE_QRY_CNF;
    pstAtCcStateQryCnfMsg->stAtAppCtrl.usClientId = pMnAppReqMsg->clientId;
    pstAtCcStateQryCnfMsg->stAtAppCtrl.ucOpId     = pMnAppReqMsg->opId;
    pstAtCcStateQryCnfMsg->ucCallNum              = ucCallNum;

    /* ������Ϣ */
    ulRet = PS_SEND_MSG(WUEPS_PID_CC, pstAtCcStateQryCnfMsg);
    if( VOS_OK != ulRet)
    {
        NAS_ERROR_LOG(WUEPS_PID_CC, "NAS_CC_ProcAtCcStateQry:ERROR: Send Msg Error!");
    }

    return;
}



/*****************************************************************************
 �� �� ��  : NAS_CC_GetEntityByCallId
 ��������  : ȡ����ָ��CallIdֵ��Ӧ��CCʵ���ID
 �������  : ucCallId - ����ID
 �������  : ��
 �� �� ֵ  : ȡ�õ�CCʵ��ID. ���û���ҵ���Ӧʵ�壬�򷵻�CC_INVALID_ENTITY_ID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��02��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���
*****************************************************************************/
NAS_CC_ENTITY_ID_T  NAS_CC_GetEntityByCallId(
    VOS_UINT8                           ucCallId
)
{
    NAS_CC_ENTITY_ID_T entityId;

    for (entityId = 0; entityId < NAS_CC_MAX_ENTITY_NUM; entityId++)
    {
        if ((VOS_TRUE == f_astCcEntities[entityId].bUsed)
         && (ucCallId == f_astCcEntities[entityId].ucCallId))
        {
            /* �ҵ� */
            return entityId;
        }
    }

    return NAS_CC_INVALID_ENTITY_ID;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_ProcSsSwitchSingleCallRetrieveSucc
 ��������  : ����ҵ���л�ʱ��·ͨ��(�෽ͨ��)�ظ��ɹ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_VOID NAS_CC_ProcSsSwitchSingleCallRetrieveSucc(VOS_VOID)
{
    NAS_CC_ENTITY_ID_T                  ulEntityID;
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enMptyState;
    NAS_CC_MSG_FACILITY_MT_STRU        *pstMsg          = VOS_NULL_PTR;

    ulEntityID  = NAS_CC_GetSsSwitchRetrieveEntityID();
    enMptyState = NAS_CC_GetMptyAuxState(ulEntityID);

    /* �������Ƿ�Ϊ�෽ͨ�����Ƕ෽ͨ��ֱ�ӽ��ظ�CALLģ��RETRIEVE_CNF������״̬ */
    if (NAS_CC_MPTY_AUX_S_CALL_IN_MPTY != enMptyState)
    {
        NAS_CC_SendMnccMsg(ulEntityID, MNCC_RETRIEVE_CNF, VOS_NULL_PTR, VOS_NULL);

        NAS_CC_INFO_LOG("NAS_CC_ProcSsSwitchSingleCallRetrieveSucc: ChangeHoldAuxState to IDLE");
        NAS_CC_ChangeHoldAuxState(ulEntityID, NAS_CC_HOLD_AUX_S_IDLE);

        /* ����ҵ���л�״̬������ϣ�������Ϣ */
        NAS_CC_InitSsSwitchInfo();
        return;
    }

    /* ����Ϊ�෽ͨ���������״̬�����������Facility��Ϣ���͸�CALLģ�� */
    if (VOS_TRUE == NAS_CC_GetSsSwitchOpFacility())
    {
        pstMsg = NAS_CC_GetSsSwitchFacility();

        (VOS_VOID)NAS_CC_ConditionalChangeAuxState(VOS_FALSE,
                                         VOS_TRUE,
                                         VOS_TRUE,
                                         VOS_FALSE,
                                         NAS_CC_HOLD_AUX_S_IDLE,
                                         NAS_CC_MPTY_AUX_S_CALL_IN_MPTY,
                                         NAS_CC_HOLD_AUX_S_IDLE,
                                         NAS_CC_MPTY_AUX_S_IDLE);

        NAS_CC_SendMnccMsg(ulEntityID,
                           MNCC_FACILITY_IND,
                           pstMsg,
                           sizeof(NAS_CC_MSG_FACILITY_MT_STRU));

        /* ����ҵ���л�״̬������ϣ�������Ϣ */
        NAS_CC_InitSsSwitchInfo();
        return;
    }

    NAS_CC_ERR_LOG("NAS_CC_ProcSsSwitchSingleCallRetrieveSucc: Error AuxState or Switch State!");

    /* ����ҵ���л�״̬�����쳣��������Ϣ */
    NAS_CC_InitSsSwitchInfo();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_ProcSsSwitchSingleCallRetrieveFail
 ��������  : ����ҵ���л�ʱ��·ͨ��(�෽ͨ��)�ظ�ʧ�ܴ�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_VOID NAS_CC_ProcSsSwitchSingleCallRetrieveFail(VOS_VOID)
{
    NAS_CC_ENTITY_ID_T                  ulEntityID;
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enMptyState;
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause;
    NAS_CC_MSG_FACILITY_MT_STRU        *pstMsg          = VOS_NULL_PTR;
    VOS_UINT8                           ucInvokeId;

    ulEntityID  = NAS_CC_GetSsSwitchRetrieveEntityID();
    enCause     = NAS_CC_GetSsSwitchRetrieveCause();
    enMptyState = NAS_CC_GetMptyAuxState(ulEntityID);

    /* �������Ƿ�Ϊ�෽ͨ�����Ƕ෽ͨ��ֱ�ӽ��ظ�CALLģ��RETRIEVE_REJ������״̬ */
    if (NAS_CC_MPTY_AUX_S_CALL_IN_MPTY != enMptyState)
    {
        NAS_CC_SendMnccMsg(ulEntityID, MNCC_RETRIEVE_REJ, &enCause, sizeof(enCause));

        NAS_CC_INFO_LOG("NAS_CC_ProcSsSwitchSingleCallRetrieveFail: ChangeHoldAuxState to CALL_HELD");
        NAS_CC_ChangeHoldAuxState(ulEntityID, NAS_CC_HOLD_AUX_S_CALL_HELD);

        /* ����ҵ���л�״̬������ϣ�������Ϣ */
        NAS_CC_InitSsSwitchInfo();
        return;
    }

    /* ������ʵ��״̬�ָ�ΪHELD */
    (VOS_VOID)NAS_CC_ConditionalChangeAuxState(VOS_FALSE,
                                     VOS_TRUE,
                                     VOS_TRUE,
                                     VOS_FALSE,
                                     NAS_CC_HOLD_AUX_S_IDLE,
                                     NAS_CC_MPTY_AUX_S_CALL_IN_MPTY,
                                     NAS_CC_HOLD_AUX_S_CALL_HELD,
                                     NAS_CC_MPTY_AUX_S_IDLE);

    /* ����Ϊ�෽ͨ���������״̬�����������Facility��Ϣ���͸�CALLģ�� */
    if (VOS_TRUE == NAS_CC_GetSsSwitchOpFacility())
    {
        pstMsg = NAS_CC_GetSsSwitchFacility();

        NAS_CC_SendMnccMsg(ulEntityID,
                           MNCC_FACILITY_IND,
                           pstMsg,
                           sizeof(NAS_CC_MSG_FACILITY_MT_STRU));

        /* ����ҵ���л�״̬������ϣ�������Ϣ */
        NAS_CC_InitSsSwitchInfo();
        return;
    }

    /* ����Facility������ʱ����ʱ�ظ�FACILITY_LOCAL_REJ */
    if (VOS_TRUE == NAS_CC_GetSsSwitchOpInvokeId())
    {
        ucInvokeId = NAS_CC_GetSsSwitchInvokeId();

        NAS_CC_SendMnccMsg(ulEntityID,
                           MNCC_FACILITY_LOCAL_REJ,
                           &ucInvokeId,
                           sizeof(ucInvokeId));

        /* ����ҵ���л�״̬������ϣ�������Ϣ */
        NAS_CC_InitSsSwitchInfo();
        return;
    }

    NAS_CC_ERR_LOG("NAS_CC_ProcSsSwitchSingleCallRetrieveFail: Error AuxState or Switch State!");

    /* ����ҵ���л�״̬�����쳣��������Ϣ */
    NAS_CC_InitSsSwitchInfo();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_ProcSsSwitchSingleCallHoldSucc
 ��������  : ����ҵ���л�ʱ��·ͨ��(�෽ͨ��)���ֳɹ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_VOID NAS_CC_ProcSsSwitchSingleCallHoldSucc(VOS_VOID)
{
    NAS_CC_ENTITY_ID_T                  ulEntityID;
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enMptyState;
    NAS_CC_MSG_FACILITY_MT_STRU        *pstMsg          = VOS_NULL_PTR;

    ulEntityID  = NAS_CC_GetSsSwitchHoldEntityID();
    enMptyState = NAS_CC_GetMptyAuxState(ulEntityID);

    /* �������Ƿ�Ϊ�෽ͨ�����Ƕ෽ͨ��ֱ�ӽ��ظ�CALLģ��HOLD_CNF������״̬ */
    if (NAS_CC_MPTY_AUX_S_CALL_IN_MPTY != enMptyState)
    {
        NAS_CC_SendMnccMsg(ulEntityID, MNCC_HOLD_CNF, VOS_NULL_PTR, VOS_NULL);

        NAS_CC_INFO_LOG("NAS_CC_ProcSsSwitchSingleCallHoldSucc: ChangeHoldAuxState to CALL_HELD");
        NAS_CC_ChangeHoldAuxState(ulEntityID, NAS_CC_HOLD_AUX_S_CALL_HELD);

        /* ����ҵ���л�״̬������ϣ�������Ϣ */
        NAS_CC_InitSsSwitchInfo();
        return;
    }

    (VOS_VOID)NAS_CC_ConditionalChangeAuxState(VOS_FALSE,
                                     VOS_TRUE,
                                     VOS_TRUE,
                                     VOS_FALSE,
                                     NAS_CC_HOLD_AUX_S_IDLE,
                                     NAS_CC_MPTY_AUX_S_CALL_IN_MPTY,
                                     NAS_CC_HOLD_AUX_S_CALL_HELD,
                                     NAS_CC_MPTY_AUX_S_IDLE);

    /* ����Ϊ�෽ͨ���������״̬�����������Facility��Ϣ���͸�CALLģ�� */
    if (VOS_TRUE == NAS_CC_GetSsSwitchOpFacility())
    {
        pstMsg = NAS_CC_GetSsSwitchFacility();

        NAS_CC_SendMnccMsg(ulEntityID,
                           MNCC_FACILITY_IND,
                           pstMsg,
                           sizeof(NAS_CC_MSG_FACILITY_MT_STRU));

        /* ����ҵ���л�״̬������ϣ�������Ϣ */
        NAS_CC_InitSsSwitchInfo();
        return;
    }

    NAS_CC_ERR_LOG("NAS_CC_ProcSsSwitchSingleCallRetrieveSucc: Error AuxState or Switch State!");

    /* ����ҵ���л�״̬�����쳣��������Ϣ */
    NAS_CC_InitSsSwitchInfo();
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_ProcSsSwitchSingleCallHoldFail
 ��������  : ����ҵ���л�ʱ��·ͨ��(�෽ͨ��)����ʧ�ܴ�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_VOID NAS_CC_ProcSsSwitchSingleCallHoldFail(VOS_VOID)
{
    NAS_CC_ENTITY_ID_T                  ulEntityID;
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enMptyState;
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause;
    NAS_CC_MSG_FACILITY_MT_STRU        *pstMsg          = VOS_NULL_PTR;
    VOS_UINT8                           ucInvokeId;

    ulEntityID  = NAS_CC_GetSsSwitchHoldEntityID();
    enCause     = NAS_CC_GetSsSwitchHoldCause();
    enMptyState = NAS_CC_GetMptyAuxState(ulEntityID);

    /* �������Ƿ�Ϊ�෽ͨ�����Ƕ෽ͨ��ֱ�ӽ��ظ�CALLģ��HOLD_REJ������״̬ */
    if (NAS_CC_MPTY_AUX_S_CALL_IN_MPTY != enMptyState)
    {
        NAS_CC_SendMnccMsg(ulEntityID, MNCC_HOLD_REJ, &enCause, sizeof(enCause));

        NAS_CC_INFO_LOG("NAS_CC_ProcSsSwitchSingleCallHoldFail: ChangeHoldAuxState to IDLE");
        NAS_CC_ChangeHoldAuxState(ulEntityID, NAS_CC_HOLD_AUX_S_IDLE);

        /* ����ҵ���л�״̬������ϣ�������Ϣ */
        NAS_CC_InitSsSwitchInfo();
        return;
    }

    (VOS_VOID)NAS_CC_ConditionalChangeAuxState(VOS_FALSE,
                                     VOS_TRUE,
                                     VOS_TRUE,
                                     VOS_FALSE,
                                     NAS_CC_HOLD_AUX_S_IDLE,
                                     NAS_CC_MPTY_AUX_S_CALL_IN_MPTY,
                                     NAS_CC_HOLD_AUX_S_IDLE,
                                     NAS_CC_MPTY_AUX_S_IDLE);

    /* ����Ϊ�෽ͨ���������״̬�����������Facility��Ϣ���͸�CALLģ�� */
    if (VOS_TRUE == NAS_CC_GetSsSwitchOpFacility())
    {
        pstMsg = NAS_CC_GetSsSwitchFacility();

        NAS_CC_SendMnccMsg(ulEntityID,
                           MNCC_FACILITY_IND,
                           pstMsg,
                           sizeof(NAS_CC_MSG_FACILITY_MT_STRU));

        /* ����ҵ���л�״̬������ϣ�������Ϣ */
        NAS_CC_InitSsSwitchInfo();
        return;
    }

    /* ����Facility������ʱ����ʱ�ظ�FACILITY_LOCAL_REJ */
    if (VOS_TRUE == NAS_CC_GetSsSwitchOpInvokeId())
    {
        ucInvokeId = NAS_CC_GetSsSwitchInvokeId();

        NAS_CC_SendMnccMsg(ulEntityID,
                           MNCC_FACILITY_LOCAL_REJ,
                           &ucInvokeId,
                           sizeof(ucInvokeId));

        /* ����ҵ���л�״̬������ϣ�������Ϣ */
        NAS_CC_InitSsSwitchInfo();
        return;
    }

    NAS_CC_ERR_LOG("NAS_CC_ProcSsSwitchSingleCallHoldFail: Error AuxState or Switch State!");

    /* ����ҵ���л�״̬�����쳣��������Ϣ */
    NAS_CC_InitSsSwitchInfo();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_ProcSsSwitchMultiCallSucc
 ��������  : ����ҵ���л�ʱ��·ͨ��״̬�л��ɹ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_VOID NAS_CC_ProcSsSwitchMultiCallSucc(VOS_VOID)
{
    NAS_CC_ENTITY_ID_T                  ulHoldEntityID;
    NAS_CC_ENTITY_ID_T                  ulRetrieveEntityID;
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enHoldMptyState;
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enRetrieveMptyState;
    NAS_CC_MSG_FACILITY_MT_STRU        *pstMsg          = VOS_NULL_PTR;

    ulHoldEntityID      = NAS_CC_GetSsSwitchHoldEntityID();
    enHoldMptyState     = NAS_CC_GetMptyAuxState(ulHoldEntityID);
    ulRetrieveEntityID  = NAS_CC_GetSsSwitchRetrieveEntityID();
    enRetrieveMptyState = NAS_CC_GetMptyAuxState(ulRetrieveEntityID);

    /* �ȴ�����б���ͨ�� */
    /* �������Ƿ�Ϊ�෽ͨ�����Ƕ෽ͨ��ֱ�ӽ��ظ�CALLģ��HOLD_CNF������״̬ */
    if (NAS_CC_MPTY_AUX_S_CALL_IN_MPTY != enHoldMptyState)
    {
        NAS_CC_SendMnccMsg(ulHoldEntityID, MNCC_HOLD_CNF, VOS_NULL_PTR, VOS_NULL);

        NAS_CC_INFO_LOG("NAS_CC_ProcSsSwitchMultiCallSucc: ChangeHoldAuxState to HELD");
        NAS_CC_ChangeHoldAuxState(ulHoldEntityID, NAS_CC_HOLD_AUX_S_CALL_HELD);
    }
    else
    {
        /* ����Ϊ�෽ͨ���������״̬ */
        (VOS_VOID)NAS_CC_ConditionalChangeAuxState(VOS_FALSE,
                                         VOS_TRUE,
                                         VOS_TRUE,
                                         VOS_FALSE,
                                         NAS_CC_HOLD_AUX_S_IDLE,
                                         NAS_CC_MPTY_AUX_S_CALL_IN_MPTY,
                                         NAS_CC_HOLD_AUX_S_CALL_HELD,
                                         NAS_CC_MPTY_AUX_S_IDLE);

        /*�������Facility��Ϣ���͸�CALLģ�� */
        if (VOS_TRUE == NAS_CC_GetSsSwitchOpFacility())
        {
            pstMsg = NAS_CC_GetSsSwitchFacility();

            NAS_CC_SendMnccMsg(ulHoldEntityID,
                               MNCC_FACILITY_IND,
                               pstMsg,
                               sizeof(NAS_CC_MSG_FACILITY_MT_STRU));

            /* ��������Facility��Ϣ */
            NAS_CC_SetSsSwitchOpFacility(VOS_FALSE, VOS_NULL_PTR);

        }
        else
        {
            NAS_CC_ERR_LOG("NAS_CC_ProcSsSwitchMultiCallSucc: Error MPTY State First!");
        }
    }

    /* �ٴ�����лָ�ͨ�� */
    /* �������Ƿ�Ϊ�෽ͨ�����Ƕ෽ͨ��ֱ�ӽ��ظ�CALLģ��RETRIEVE_CNF������״̬ */
    if (NAS_CC_MPTY_AUX_S_CALL_IN_MPTY != enRetrieveMptyState)
    {
        NAS_CC_SendMnccMsg(ulRetrieveEntityID, MNCC_RETRIEVE_CNF, VOS_NULL_PTR, VOS_NULL);

        NAS_CC_INFO_LOG("NAS_CC_ProcSsSwitchMultiCallSucc: ChangeHoldAuxState to IDLE");
        NAS_CC_ChangeHoldAuxState(ulRetrieveEntityID, NAS_CC_HOLD_AUX_S_IDLE);
    }
    else
    {
        (VOS_VOID)NAS_CC_ConditionalChangeAuxState(VOS_FALSE,
                                         VOS_TRUE,
                                         VOS_TRUE,
                                         VOS_FALSE,
                                         NAS_CC_HOLD_AUX_S_IDLE,
                                         NAS_CC_MPTY_AUX_S_CALL_IN_MPTY,
                                         NAS_CC_HOLD_AUX_S_IDLE,
                                         NAS_CC_MPTY_AUX_S_IDLE);

        /* ����Ϊ�෽ͨ���������״̬�����������Facility��Ϣ���͸�CALLģ�� */
        if (VOS_TRUE == NAS_CC_GetSsSwitchOpFacility())
        {
            pstMsg = NAS_CC_GetSsSwitchFacility();

            NAS_CC_SendMnccMsg(ulRetrieveEntityID,
                               MNCC_FACILITY_IND,
                               pstMsg,
                               sizeof(NAS_CC_MSG_FACILITY_MT_STRU));

            /* ��������Facility��Ϣ */
            NAS_CC_SetSsSwitchOpFacility(VOS_FALSE, VOS_NULL_PTR);

        }
        else
        {
            NAS_CC_ERR_LOG("NAS_CC_ProcSsSwitchMultiCallSucc: Error MPTY State Second!");
        }
    }

    /* ����ҵ���·�л�״̬����ɹ���������Ϣ */
    NAS_CC_InitSsSwitchInfo();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_ProcSsSwitchMultiCallFail
 ��������  : ����ҵ���л�ʱ��·ͨ��״̬�л�ʧ�ܴ�����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_VOID NAS_CC_ProcSsSwitchMultiCallFail(VOS_VOID)
{
    NAS_CC_ENTITY_ID_T                  ulHoldEntityID;
    NAS_CC_ENTITY_ID_T                  ulRetrieveEntityID;
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enHoldMptyState;
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enRetrieveMptyState;
    NAS_CC_CAUSE_VALUE_ENUM_U32         enHoldCause;
    NAS_CC_CAUSE_VALUE_ENUM_U32         enRetrieveCause;
    NAS_CC_SS_SWITCH_STATE_ENUM_UINT8   enHoldState;
    NAS_CC_SS_SWITCH_STATE_ENUM_UINT8   enRetrieveState;
    NAS_CC_MSG_FACILITY_MT_STRU        *pstMsg          = VOS_NULL_PTR;
    VOS_UINT8                           ucInvokeId;

    ulHoldEntityID      = NAS_CC_GetSsSwitchHoldEntityID();
    enHoldCause         = NAS_CC_GetSsSwitchHoldCause();
    enHoldState         = NAS_CC_GetSsSwitchHoldState();
    enHoldMptyState     = NAS_CC_GetMptyAuxState(ulHoldEntityID);
    ulRetrieveEntityID  = NAS_CC_GetSsSwitchRetrieveEntityID();
    enRetrieveCause     = NAS_CC_GetSsSwitchRetrieveCause();
    enRetrieveState     = NAS_CC_GetSsSwitchRetrieveState();
    enRetrieveMptyState = NAS_CC_GetMptyAuxState(ulRetrieveEntityID);

    /* �ȴ�����б���ͨ�� */
    /* �������Ƿ�Ϊ�෽ͨ�����Ƕ෽ͨ��ֱ�ӽ��ظ�CALLģ��HOLD_REJ������״̬ */
    if (NAS_CC_MPTY_AUX_S_CALL_IN_MPTY != enHoldMptyState)
    {
        /* ���HOLD����ʧ�ܣ���ظ�HOLD_REJ */
        if (NAS_CC_SS_SWITCH_SUCCESS != enHoldState)
        {
            NAS_CC_SendMnccMsg(ulHoldEntityID,
                               MNCC_HOLD_REJ,
                               &enHoldCause,
                               sizeof(enHoldCause));
        }

        NAS_CC_INFO_LOG("NAS_CC_ProcSsSwitchMultiCallFail: ChangeHoldAuxState to IDLE");
        NAS_CC_ChangeHoldAuxState(ulHoldEntityID, NAS_CC_HOLD_AUX_S_IDLE);
    }
    else
    {
        /* ����Ϊ�෽ͨ���������״̬�����������Facility��Ϣ���͸�CALLģ�� */
        (VOS_VOID)NAS_CC_ConditionalChangeAuxState(VOS_FALSE,
                                         VOS_TRUE,
                                         VOS_TRUE,
                                         VOS_FALSE,
                                         NAS_CC_HOLD_AUX_S_IDLE,
                                         NAS_CC_MPTY_AUX_S_CALL_IN_MPTY,
                                         NAS_CC_HOLD_AUX_S_IDLE,
                                         NAS_CC_MPTY_AUX_S_IDLE);

        /* ���Facility����ʧ�ܣ����ͻظ� */
        if (NAS_CC_SS_SWITCH_SUCCESS != enHoldState)
        {
            if (VOS_TRUE == NAS_CC_GetSsSwitchOpFacility())
            {
                pstMsg = NAS_CC_GetSsSwitchFacility();

                NAS_CC_SendMnccMsg(ulHoldEntityID,
                                   MNCC_FACILITY_IND,
                                   pstMsg,
                                   sizeof(NAS_CC_MSG_FACILITY_MT_STRU));
            }

            if (VOS_TRUE == NAS_CC_GetSsSwitchOpInvokeId())
            {
                ucInvokeId = NAS_CC_GetSsSwitchInvokeId();

                NAS_CC_SendMnccMsg(ulHoldEntityID,
                                   MNCC_FACILITY_LOCAL_REJ,
                                   &ucInvokeId,
                                   sizeof(ucInvokeId));

            }
        }

        /* ��������Facility��Ϣ��InvokeId */
        NAS_CC_SetSsSwitchOpFacility(VOS_FALSE, VOS_NULL_PTR);
        NAS_CC_SetSsSwitchInvokeId(VOS_FALSE, NAS_CC_INVALID_INVOKE_ID);

    }

    /* �ٴ�����лָ�ͨ�� */
    /* �������Ƿ�Ϊ�෽ͨ�����Ƕ෽ͨ��ֱ�ӽ��ظ�CALLģ��RETRIEVE_REJ������״̬ */
    if (NAS_CC_MPTY_AUX_S_CALL_IN_MPTY != enRetrieveMptyState)
    {
        /* ���RETRIEVE����ʧ�ܣ���ظ�RETRIEVE_REJ */
        if (NAS_CC_SS_SWITCH_SUCCESS != enRetrieveState)
        {
            NAS_CC_SendMnccMsg(ulRetrieveEntityID,
                               MNCC_RETRIEVE_REJ,
                               &enRetrieveCause,
                               sizeof(enRetrieveCause));
        }

        NAS_CC_INFO_LOG("NAS_CC_ProcSsSwitchMultiCallFail: ChangeHoldAuxState to HELD");
        NAS_CC_ChangeHoldAuxState(ulRetrieveEntityID, NAS_CC_HOLD_AUX_S_CALL_HELD);
    }
    else
    {
        /* ����Ϊ�෽ͨ���������״̬�����������Facility��Ϣ���͸�CALLģ�� */
        (VOS_VOID)NAS_CC_ConditionalChangeAuxState(VOS_FALSE,
                                         VOS_TRUE,
                                         VOS_TRUE,
                                         VOS_FALSE,
                                         NAS_CC_HOLD_AUX_S_IDLE,
                                         NAS_CC_MPTY_AUX_S_CALL_IN_MPTY,
                                         NAS_CC_HOLD_AUX_S_CALL_HELD,
                                         NAS_CC_MPTY_AUX_S_IDLE);

        /* ���Facility����ʧ�ܣ����ͻظ� */
        if (NAS_CC_SS_SWITCH_SUCCESS != enRetrieveState)
        {
            if (VOS_TRUE == NAS_CC_GetSsSwitchOpFacility())
            {
                pstMsg = NAS_CC_GetSsSwitchFacility();

                NAS_CC_SendMnccMsg(ulRetrieveEntityID,
                                   MNCC_FACILITY_IND,
                                   pstMsg,
                                   sizeof(NAS_CC_MSG_FACILITY_MT_STRU));
            }

            if (VOS_TRUE == NAS_CC_GetSsSwitchOpInvokeId())
            {
                ucInvokeId = NAS_CC_GetSsSwitchInvokeId();

                NAS_CC_SendMnccMsg(ulRetrieveEntityID,
                                   MNCC_FACILITY_LOCAL_REJ,
                                   &ucInvokeId,
                                   sizeof(ucInvokeId));

            }
        }

        /* ��������Facility��Ϣ��InvokeId */
        NAS_CC_SetSsSwitchOpFacility(VOS_FALSE, VOS_NULL_PTR);
        NAS_CC_SetSsSwitchInvokeId(VOS_FALSE, NAS_CC_INVALID_INVOKE_ID);

    }

    /* ����ҵ���·�л�״̬����ɹ���������Ϣ */
    NAS_CC_InitSsSwitchInfo();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_ProcSsSwitchMain
 ��������  : CCģ�鲹��ҵ��״̬�л�����������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_VOID NAS_CC_ProcSsSwitchMain(VOS_VOID)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMapNum;
    NAS_CC_SS_SWITCH_STATE_ENUM_UINT8   enHoldState;
    NAS_CC_SS_SWITCH_STATE_ENUM_UINT8   enRetrievetate;
    NAS_CC_FUNC_VOID                    pFunc           = VOS_NULL_PTR;

    ulMapNum        = sizeof(f_astCcSsSwitchFuncMap) / sizeof(NAS_CC_SS_SWITCH_PROC_FUNC_MAP_STRU);
    enHoldState     = NAS_CC_GetSsSwitchHoldState();
    enRetrievetate  = NAS_CC_GetSsSwitchRetrieveState();

    for (ulLoop = 0; ulLoop < ulMapNum; ulLoop++)
    {
        if ( (f_astCcSsSwitchFuncMap[ulLoop].enHoldState == enHoldState)
          && (f_astCcSsSwitchFuncMap[ulLoop].enRetrieveState == enRetrievetate) )
        {
            pFunc = f_astCcSsSwitchFuncMap[ulLoop].pFunc;
        }
    }

    if (VOS_NULL_PTR != pFunc)
    {
        pFunc();
    }

    return;
}

/* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
/*****************************************************************************
 �� �� ��  : NAS_CC_GetFirstMptyCallEntityID
 ��������  : ��ȡ��һ���෽ͨ����ENTITY ID
 �������  : �ͷŵ�ENTITY ID
 �������  : ��
 �� �� ֵ  : ��һ���෽ͨ����ENTITY ID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
*****************************************************************************/
VOS_UINT32 NAS_CC_GetFirstMptyCallEntityID(NAS_CC_ENTITY_ID_T EntityID)
{
    VOS_UINT8                           i;

    for (i=0; i < NAS_CC_MAX_ENTITY_NUM; i++)
    {
        if (EntityID == i)
        {
            continue;
        }

        if (VOS_TRUE == f_astCcEntities[i].bUsed)
        {
            if (NAS_CC_MPTY_AUX_S_CALL_IN_MPTY == f_astCcEntities[i].enMptyAuxState)
            {
                return i;
            }
        }
    }

    return NAS_CC_INVALID_ENTITY_ID;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_IsLastCallEntityID
 ��������  : �ж�entity id�Ƿ��Ǵ��ڵ����һ������
 �������  : EntityID - ����ʵ��id
 �������  : ��
 �� �� ֵ  : VOS_TRUE :�����һ������
             VOS_FALSE:�������һ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : z00161729
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 NAS_CC_IsLastCallEntityID(NAS_CC_ENTITY_ID_T EntityID)
{
    VOS_UINT8                           ucCallNumIndex;

    for (ucCallNumIndex = 0; ucCallNumIndex < NAS_CC_MAX_ENTITY_NUM; ucCallNumIndex++)
    {
        if (EntityID == ucCallNumIndex)
        {
            continue;
        }

        if (VOS_TRUE == f_astCcEntities[ucCallNumIndex].bUsed)
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_CC_ProcSsSwitchCallRelease
 ��������  : �����ͷ�ʱ���²���ҵ���л���Ϣ��
             �෽ͨ�����ͷ�һ·������л���Ϣ��CALLʵ�嵽δ�ͷŵ�ʵ�壬�˳���
             ���л��鶼�ͷţ�������FACILITY��ص��л�����HOLD/RETRIEVE״̬Ϊ���У����ô�����֪ͨCALL��һ�����Ĵ�������
             �Ƕ෽ͨ��������չ������л�״̬Ϊ���У����ô�����֪ͨCALL��һ�����Ĵ�������
 �������  : EntityID   �ͷź��е�ʵ��ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  2.��    ��   : 2014��5��31��
    ��    ��   : z00161729
    �޸�����   : DTS2014060402388:һ·active���У�һ·hold��mpty���У�at+chld=1�����ж������к��ж����ͷź�call״̬�쳣������hold mpty�����޷��ָ�
*****************************************************************************/
VOS_VOID NAS_CC_ProcSsSwitchCallRelease(NAS_CC_ENTITY_ID_T EntityID)
{
    NAS_CC_ENTITY_ID_T                  OtherMptyEntityID;
    NAS_CC_ENTITY_ID_T                  ulHoldEntityID;
    NAS_CC_ENTITY_ID_T                  ulRetrieveEntityID;
    NAS_CC_MPTY_AUX_STATE_ENUM_U8       enMptyStatus;

    /* ��ȡ���еĶ෽ͨ��״̬��HOLD/RETRIEVE״̬ */
    enMptyStatus        = NAS_CC_GetMptyAuxState(EntityID);

    ulHoldEntityID      = NAS_CC_GetSsSwitchHoldEntityID();
    ulRetrieveEntityID  = NAS_CC_GetSsSwitchRetrieveEntityID();

    /* ���ͷŵĺ���ʵ��ID�����л�����ҵ���ע�ĺ���ʵ��ID�У������� */
    if ((EntityID != ulHoldEntityID)
     && (EntityID != ulRetrieveEntityID))
    {
        return;
    }

    /* ���һ·���йҶϣ���Ҫ����ʱ�����taf call�ظ��ȴ���Ϣ������call״̬�쳣 */
    if (VOS_TRUE == NAS_CC_IsLastCallEntityID(EntityID))
    {
        if (EntityID == ulHoldEntityID)
        {
            NAS_CC_SetSsSwitchHoldInfo(EntityID, NAS_CC_SS_SWITCH_LAST_CALL_RELEASED, NAS_CC_CAUSE_NULL);
        }
        else
        {
            NAS_CC_SetSsSwitchRetrieveInfo(EntityID, NAS_CC_SS_SWITCH_LAST_CALL_RELEASED, NAS_CC_CAUSE_NULL);
        }

        NAS_CC_ProcSsSwitchMain();

        return;

    }

    if (NAS_CC_MPTY_AUX_S_CALL_IN_MPTY == enMptyStatus)
    {
        /* �������������ڻ����У����л�����ҵ���ע�ĺ���ʵ��ID����Ϊ������δ�ͷŵĺ��� */
        OtherMptyEntityID = NAS_CC_GetFirstMptyCallEntityID(EntityID);

        if (NAS_CC_INVALID_ENTITY_ID != OtherMptyEntityID)
        {
            if (EntityID == ulHoldEntityID)
            {
                NAS_CC_SetSsSwitchHoldEntityID(OtherMptyEntityID);
            }
            else
            {
                NAS_CC_SetSsSwitchRetrieveEntityID(OtherMptyEntityID);
            }

            return;

        }

        /* ������û��δ�ͷŵĺ��У�������л�����ҵ����Ϣ�Ļ�����Ϣ */
        NAS_CC_SetSsSwitchOpFacility(VOS_FALSE, VOS_NULL_PTR);
        NAS_CC_SetSsSwitchInvokeId(VOS_FALSE, NAS_CC_INVALID_INVOKE_ID);

    }

    /*
    ���ͷź������л�����ҵ���ע�ı��ֲ�����غ��У�����ղ���ҵ���л���ϢHOLD����
    ���ͷź������л�����ҵ���ע�Ļָ�������غ��У�����ղ���ҵ���л���ϢRETRIEVE����
    */
    if (EntityID == ulHoldEntityID)
    {
        NAS_CC_SetSsSwitchHoldInfo(NAS_CC_INVALID_ENTITY_ID, NAS_CC_SS_SWITCH_IDLE, NAS_CC_CAUSE_NULL);
    }
    else
    {
        NAS_CC_SetSsSwitchRetrieveInfo(NAS_CC_INVALID_ENTITY_ID, NAS_CC_SS_SWITCH_IDLE, NAS_CC_CAUSE_NULL);
    }

    NAS_CC_ProcSsSwitchMain();

    return;
}
/* Added by f62575 for V9R1 STK����, 2013-6-26, end */

/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-25, begin */
#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : NAS_CC_CreateCcEntityWithCallEntityInfo
 ��������  : CCģ����ݺ��е�ʵ����Ϣ����CCʵ��
 �������  : pstSrvccCallInfoNtf--SRVCCͬ�������ĺ���ʵ����Ϣ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��25��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��6��13��
    ��    ��   : w00242748
    �޸�����   : DSDS ������
*****************************************************************************/
VOS_VOID  NAS_CC_CreateCcEntityWithCallEntityInfo(
    VOS_VOID                           *pMsg
)
{
    NAS_CC_BC_PARAMS_STRU               stBcParams;
    NAS_CC_ENTITY_ID_T                  entityId;
    VOS_UINT8                           i;
    VOS_UINT8                           ucCallEntityNum;
    MNCC_SRVCC_CALL_INFO_NOTIFY_STRU   *pstSrvccCallInfoNtf = VOS_NULL_PTR;

    pstSrvccCallInfoNtf = (MNCC_SRVCC_CALL_INFO_NOTIFY_STRU *)pMsg;

    /* �߽��飬��������Խ�� */
    ucCallEntityNum = pstSrvccCallInfoNtf->ucCallNum;
    if (MNCC_MAX_ENTITY_NUM < ucCallEntityNum)
    {
        ucCallEntityNum = MNCC_MAX_ENTITY_NUM;
    }

    /* ����Э��涨��SRVCC�ɹ���GU��,������MT CALL,��IMSA���TI�����Ϣͬ����CALLģ�� */
    for (i = 0; i < ucCallEntityNum; i++)
    {
        /* ����ʵ��ɹ�ʱ��ͬ��������Ϣ */
        if (VOS_OK == NAS_CC_CreateEntity(NAS_CC_CALL_TYPE_MT_NORMAL_CALL, pstSrvccCallInfoNtf->astEntityStatus[i].ucCallId, pstSrvccCallInfoNtf->astEntityStatus[i].ucTi, &entityId))
        {
            NAS_CC_ChangeCallState(entityId, pstSrvccCallInfoNtf->astEntityStatus[i].enCallState);
            f_astCcEntities[entityId].ucTi           = pstSrvccCallInfoNtf->astEntityStatus[i].ucTi;
            f_astCcEntities[entityId].enHoldAuxState = pstSrvccCallInfoNtf->astEntityStatus[i].enHoldAuxState;
            f_astCcEntities[entityId].enMptyAuxState = pstSrvccCallInfoNtf->astEntityStatus[i].enMptyAuxState;

            /* ����BC��Ϣ */
            stBcParams.enItc = pstSrvccCallInfoNtf->astEntityStatus[i].stBC1.Octet3.InfoTransCap;
            NAS_CC_UpdateBcParams(entityId, NAS_CC_BC_PARAM_1, &stBcParams);

            if (pstSrvccCallInfoNtf->astEntityStatus[i].stBC2.IsExist)
            {
                stBcParams.enItc = pstSrvccCallInfoNtf->astEntityStatus[i].stBC2.Octet3.InfoTransCap;
                NAS_CC_UpdateBcParams(entityId, NAS_CC_BC_PARAM_2, &stBcParams);
            }
        }
    }
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_CC_GetEntityTiInfo
 ��������  : CCģ����ݺ��е�ʵ����Ϣ��ȡTI��Ϣ
 �������  : ��
 �������  :
             VOS_UINT8                          *pucTiNum----��Ч��TI����
             VOS_UINT8                          *pucTi   ----��Ч��TI��Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��19��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��6��17��
    ��    ��   : z00234330
    �޸�����   : PCINT����
*****************************************************************************/
VOS_VOID  NAS_CC_GetEntityTiInfo(
    VOS_UINT8                          *pucTiNum,
    VOS_UINT8                          *pucTi
)
{
    VOS_UINT8                           i;

    *pucTiNum = 0;

    /* Ѱ��δʹ�õ�CCʵ�� */
    for (i =0; i <NAS_CC_MAX_ENTITY_NUM; i++)
    {
        if (VOS_FALSE == f_astCcEntities[i].bUsed)
        {
            continue;
        }
        /* Modified by z00234330 for PCLINT����, 2014-06-24, begin */
        pucTi[(*pucTiNum)] = f_astCcEntities[i].ucTi;
        (*pucTiNum)++;
        /* Modified by z00234330 for PCLINT����, 2014-06-24, end */
    }
}

/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-25, end */

/*****************************************************************************
 �� �� ��  : NAS_CC_IsOnlySpecTypeCall
 ��������  : ����CALL�����ж��Ƿ��Ǹ������е�һ������
 �������  : enCallType:��������
 �������  :
 �� �� ֵ  :VOS_TRUE:�������е�һ������
            VOS_FALSE:���Ǹ������е�һ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��18��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_CC_IsOnlySpecTypeCall(
    NAS_CC_CALL_TYPE_ENUM_U8            enCallType
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulNumOfSpecType;

    ulNumOfSpecType = 0;

    /* Ѱ��δʹ�õ�CCʵ�� */
    for (ulIndex = 0; ulIndex < NAS_CC_MAX_ENTITY_NUM; ulIndex++)
    {
        if ( (VOS_TRUE      == f_astCcEntities[ulIndex].bUsed)
          && (enCallType    == f_astCcEntities[ulIndex].enCallType) )
        {
            ulNumOfSpecType++;
        }
    }

    if ( 1 == ulNumOfSpecType )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_ConvertCallTypeToSessionType
 ��������  : ���绰����ת������Ӧ��Session����
 �������  : enCallType:��������
 �������  : ��
 �� �� ֵ  : MMCC_SESSION_TYPE_ENUM_UINT8
             ��Ӧ��Session����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��18��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
*****************************************************************************/
MMCC_SESSION_TYPE_ENUM_UINT8  NAS_CC_ConvertCallTypeToSessionType(
    NAS_CC_CALL_TYPE_ENUM_U8            enCallType
)
{
    MMCC_SESSION_TYPE_ENUM_UINT8        enSessionType;

    switch(enCallType)
    {
        case NAS_CC_CALL_TYPE_MO_NORMAL_CALL:
            enSessionType = MMCC_SESSION_TYPE_MO_NORMAL_CALL;
            break;

        case NAS_CC_CALL_TYPE_EMERGENCY_CALL:
            enSessionType = MMCC_SESSION_TYPE_MO_EMERGENCY_CALL;
            break;

        case NAS_CC_CALL_TYPE_MT_NORMAL_CALL:
            enSessionType = MMCC_SESSION_TYPE_MT_NORMAL_CALL;
            break;

        default:
            enSessionType = MMCC_SESSION_TYPE_BUTT;
            break;
    }

    return enSessionType;
}



#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 �� �� ��  : NAS_CC_SndAcpuOmErrLogRptCnf
 ��������  : ����ID_OM_ERR_LOG_REPORT_CNF��Ϣ��ACPU OM
 �������  : pbuffer:��������
             ulBufUseLen:���ݳ���
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��09��22��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_CC_SndAcpuOmErrLogRptCnf(
    VOS_CHAR                           *pbuffer,
    VOS_UINT32                          ulBufUseLen
)
{
    OM_ERR_LOG_REPORT_CNF_STRU         *pstQryCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    /* �ϱ�����Ϣ�ܳ��� */
    ulMsgLen  = ((sizeof(OM_ERR_LOG_REPORT_CNF_STRU) - VOS_MSG_HEAD_LENGTH) - 4) + ulBufUseLen;

    /* ��Ϣ�ռ����� */
    pstQryCnf = (OM_ERR_LOG_REPORT_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_CC, ulMsgLen);
    if (VOS_NULL_PTR == pstQryCnf)
    {
        NAS_CC_ERR_LOG("NAS_CC_SndAcpuOmErrLogRptCnf: alloc msg fail!");
        return;
    }

    pstQryCnf->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstQryCnf->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstQryCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstQryCnf->ulSenderPid      = WUEPS_PID_CC;
    pstQryCnf->ulMsgName        = ID_OM_ERR_LOG_REPORT_CNF;
    pstQryCnf->ulMsgType        = OM_ERR_LOG_MSG_ERR_REPORT;
    pstQryCnf->ulMsgSN          = 0;
    pstQryCnf->ulRptlen         = ulBufUseLen;

    /* buffer��Ϊ��ʱ��lenҲ�ǲ���Ϊ�յ� */
    if (VOS_NULL_PTR != pbuffer)
    {
        PS_MEM_CPY(pstQryCnf->aucContent, pbuffer, ulBufUseLen);
    }

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_CC, pstQryCnf))
    {
        NAS_CC_ERR_LOG("NAS_CC_SndAcpuOmErrLogRptCnf: SEND MSG FAIL");
    }

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_CC_RcvAcpuOmErrLogRptReq
 ��������  : CC����Acpu om������ERROR LOG�����ϱ�����
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��09��22��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_CC_RcvAcpuOmErrLogRptReq(
    const VOS_VOID                           *pMsg
)
{
    VOS_CHAR                           *pbuffer   = VOS_NULL_PTR;
    VOS_UINT32                          ulBufUseLen;
    VOS_UINT32                          ulRealLen;
    VOS_UINT32                          ulTotalLen;
    NAS_ERR_LOG_MNTN_EVENT_STRU         stNasErrLogMntnEvent;

    /* ��ѯһ��RING BUFFER���ж������ݣ��Ա�����ڴ� */
    ulBufUseLen = NAS_CC_GetErrLogRingBufferUseBytes();
    ulTotalLen = ulBufUseLen + sizeof(NAS_ERR_LOG_MNTN_EVENT_STRU);

    pbuffer = (VOS_CHAR *)PS_MEM_ALLOC(WUEPS_PID_CC, ulTotalLen);
    if (VOS_NULL_PTR == pbuffer)
    {
        /* ����ID_OM_ERR_LOG_REPORT_CNF����Ϊ�յ���Ϣ��OM */
        NAS_CC_SndAcpuOmErrLogRptCnf(VOS_NULL_PTR, 0);
        return;
    }

    PS_MEM_SET(pbuffer, 0, ulTotalLen);

    /* ��ȡRING BUFFER������ */
    ulRealLen = NAS_CC_GetErrLogRingBufContent(pbuffer, ulBufUseLen);
    if (ulRealLen != ulBufUseLen)
    {
        /* ����ID_OM_ERR_LOG_REPORT_CNF����Ϊ�յ���Ϣ��OM */
        NAS_CC_SndAcpuOmErrLogRptCnf(VOS_NULL_PTR, 0);
        PS_MEM_FREE(WUEPS_PID_CC, pbuffer);
        return;
    }

    /* �����������������Ϣ׷����RingBuf���� */
    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stNasErrLogMntnEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_CC),
                                      NAS_ERR_LOG_ALM_MNTN,
                                      NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_MNTN),
                                      VOS_GetSlice(),
                                      (sizeof(NAS_ERR_LOG_MNTN_EVENT_STRU) - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stNasErrLogMntnEvent.ulCount = NAS_CC_GetErrlogOverflowCnt();

    PS_MEM_CPY(pbuffer + ulBufUseLen, &stNasErrLogMntnEvent, sizeof(stNasErrLogMntnEvent));

    /* ��ȡ���˺���Ҫ��RINGBUFFER��� */
    NAS_CC_CleanErrLogRingBuf();

    /* ����������� */
    NAS_CC_SetErrlogOverflowCnt(0);

    /* ��ά�ɲ�BUF����Ĺ��� */
    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_MNTN,
                           WUEPS_PID_CC,
                           (VOS_UINT8 *)&stNasErrLogMntnEvent,
                           sizeof(stNasErrLogMntnEvent));

    /* ����ID_OM_ERR_LOG_REPORT_CNF��Ϣ��ACPU OM */
    NAS_CC_SndAcpuOmErrLogRptCnf(pbuffer, ulTotalLen);

    PS_MEM_FREE(WUEPS_PID_CC, pbuffer);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_CC_RcvAcpuOmErrLogCtrlInd
 ��������  : CC����Acpu om������ERROR LOG����ָʾ
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��09��22��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_CC_RcvAcpuOmErrLogCtrlInd(
    const VOS_VOID                           *pMsg
)
{
    OM_ERROR_LOG_CTRL_IND_STRU         *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg = (OM_ERROR_LOG_CTRL_IND_STRU*)pMsg;

    /* ����ERRLOG���Ʊ�ʶ */
    if ((VOS_FALSE == pstRcvMsg->ucAlmStatus)
     || (VOS_TRUE  == pstRcvMsg->ucAlmStatus))
    {
        NAS_CC_SetErrlogCtrlFlag(pstRcvMsg->ucAlmStatus);
    }

    if ((pstRcvMsg->ucAlmLevel >= NAS_ERR_LOG_CTRL_LEVEL_CRITICAL)
     && (pstRcvMsg->ucAlmLevel <= NAS_ERR_LOG_CTRL_LEVEL_WARNING))
    {
        NAS_CC_SetErrlogAlmLevel(pstRcvMsg->ucAlmLevel);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAcpuOmMsg
 ��������  : ��������A��OMģ�����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��09��22��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_CC_RcvAcpuOmMsg(
    const VOS_VOID                     *pMsg
)
{
    MSG_HEADER_STRU                    *pMsgHeader = (MSG_HEADER_STRU *)pMsg;

    switch(pMsgHeader->ulMsgName)
    {
        case ID_OM_ERR_LOG_CTRL_IND:
            NAS_CC_RcvAcpuOmErrLogCtrlInd(pMsg);
            break;

        case ID_OM_ERR_LOG_REPORT_REQ:
            NAS_CC_RcvAcpuOmErrLogRptReq(pMsg);
            break;

        default:
            break;
    }

    return;
}
#endif

/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
