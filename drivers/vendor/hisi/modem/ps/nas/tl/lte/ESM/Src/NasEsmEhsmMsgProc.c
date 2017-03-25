/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEsmEhsmMsgProc.c
    Description : ����EHSM����ESM�ĳ��ش�������Ϣ
    History     :
     1.sunjitan 00193151    2015-06-16   Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "NasEsmEhsmMsgProc.h"
#include    "NasEsmInclude.h"


/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_NASESMEHSMMSGPROC_C
#define    THIS_NAS_FILE_ID             NAS_FILE_ID_NASESMEHSMMSGPROC_C
/*lint +e767*/


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


/*****************************************************************************
  3 Function
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
NAS_ESM_EHRPD_ENTITY_STRU               g_stEsmEhrpdEntity;


/*****************************************************************************
 Function Name  : NAS_ESM_EhsmMsgDistr
 Description    : ESMģ��EHSM��Ϣ������
 Input          : VOS_VOID*              EHSM��������Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhsmMsgDistr(
    VOS_VOID                           *pRcvMsg
)
{
    EHSM_ESM_MSG_HEADER_STRU           *pEhsmMsg  = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EhsmMsgDistr is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmMsgDistr_ENUM, LNAS_ENTRY);

    pEhsmMsg        = (EHSM_ESM_MSG_HEADER_STRU*)pRcvMsg;

    /*������ϢID��������Ӧ����Ϣ������*/
    switch (pEhsmMsg->enMsgId)
    {
        case ID_EHSM_ESM_SYNC_PDN_INFO_IND:

            NAS_ESM_EhsmSyncPdnInfoMsgProc(pRcvMsg);

            /* ��ά�ɲ⣬�ϱ�HIDSʵ��״̬ */
            NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo();
            break;

        case ID_EHSM_ESM_CLEAR_ALL_BEARER_NOTIFY:

            /* ��ά�ɲ⣬�ϱ�HIDSʵ���������֮ǰ�ļ�¼״̬ */
            NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo();

            NAS_ESM_EhsmClearAllBearerNotifyMsgProc(pRcvMsg);
            break;

        default:

            /*��ӡ�쳣��Ϣ*/
            NAS_ESM_WARN_LOG("NAS_ESM_EhsmMsgDistr:Warning:EHSM->SM,Receive Abnormal Message!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmMsgDistr_ENUM, ESM_EHSM_MSGID_ERROR);
            break;
    }

    return;
}


/*****************************************************************************
 Function Name  : NAS_ESM_InitEhrpdEntity
 Description    : ESMģ���ʼ��EHRPDʵ��Ĵ���
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_InitEhrpdEntity(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_ESM_EHRPD_ENTITY_STRU          *pstEhrpdEntity      = VOS_NULL_PTR;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_InitEhrpdEntity is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_InitEhrpdEntity_ENUM, LNAS_ENTRY);

    pstEhrpdEntity = NAS_ESM_GET_EHRPD_ENTITY_ADDR();

    /* EHRPDʵ�崦�ڵȴ��ָ�״̬ */
    NAS_ESM_SET_EHRPD_ENTITY_STATE(NAS_ESM_EHRPD_ENTITY_STATE_WAIT_HANDOVER);

    /* EHRPD���ؼ�¼����Ϊ0 */
    NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM()      = 0;

    pstEhrpdEntity->aucRsv[0]                     = 0;
    pstEhrpdEntity->aucRsv[1]                     = 0;

    /* ѭ����ÿ��PDNʵ���ʼ�� */
    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);
        pstPdnEntity->ucUsedFlag        = PS_FALSE;
        pstPdnEntity->ucAttachPdnFlag   = PS_FALSE;
        pstPdnEntity->ucIsOnReconnFlag  = PS_FALSE;
        pstPdnEntity->ucRsv             = 0;
        pstPdnEntity->ulHandoverEpsbId  = 0;

        NAS_ESM_MEM_SET_S(  &pstPdnEntity->stNwMsgRecord,
                            sizeof(NAS_ESM_EHRPD_NW_MSG_RECORD_STRU),
                            0,
                            sizeof(NAS_ESM_EHRPD_NW_MSG_RECORD_STRU));

        NAS_ESM_MEM_SET_S(  &pstPdnEntity->stTimerInfo,
                            sizeof(NAS_ESM_TIMER_STRU),
                            0,
                            sizeof(NAS_ESM_TIMER_STRU));

        NAS_ESM_MEM_SET_S(  &pstPdnEntity->stEhPdnContextInfo,
                            sizeof(NAS_ESM_EHRPD_PDN_CONTEXT_INFO_STRU),
                            0,
                            sizeof(NAS_ESM_EHRPD_PDN_CONTEXT_INFO_STRU));
    }

    return;
}


/*****************************************************************************
 Function Name  : NAS_ESM_EhsmSyncPdnInfoMsgProc
 Description    : ESMģ���յ�ID_EHSM_ESM_SYNC_PDN_INFO_IND��Ϣ�Ĵ���
 Input          : VOS_VOID*             EHSM��������Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhsmSyncPdnInfoMsgProc(
    VOS_VOID                           *pRcvMsg
)
{
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg            = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoMsgProc_ENUM, LNAS_ENTRY);

    pEhsmMsg        = (EHSM_ESM_SYNC_PDN_INFO_IND_STRU*)pRcvMsg;

    /* ״̬��Ϊ����̬��˵�����쳣��������Ϣ */
    if (NAS_ESM_L_MODE_STATUS_SUSPENDED != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc: LTE is not suspend, discard msg.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoMsgProc_ENUM, ESM_EHSM_NOT_SUSPEND_STATE);
        return;
    }

    /* ����EHSM�����ĳ�����Ϣͬ���������ֱ���д��� */
    switch (pEhsmMsg->enPdnOption)
    {
        case EHSM_ESM_PDN_OPT_CONNECTED:

            NAS_ESM_EhsmSyncPdnInfoConnectedProc(pEhsmMsg);
            break;

        case EHSM_ESM_PDN_OPT_MODIFIED:

            NAS_ESM_EhsmSyncPdnInfoModifiedProc(pEhsmMsg);
            break;

        case EHSM_ESM_PDN_OPT_DISCONNECTED:

            NAS_ESM_EhsmSyncPdnInfoDisconnectedProc(pEhsmMsg);
            break;

        default:

            /*��ӡ�쳣��Ϣ*/
            NAS_ESM_WARN_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc:Warning:EHSM->SM,Receive Abnormal PdnOption!");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoMsgProc_ENUM, ESM_EHSM_MSGID_ERROR);
            break;
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_EhsmClearAllBearerNotifyMsgProc
 Description    : ESMģ���յ�ID_EHSM_ESM_CLEAR_ALL_BEARER_NOTIFY��Ϣ�Ĵ���
 Input          : VOS_VOID*             EHSM��������Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhsmClearAllBearerNotifyMsgProc(
    VOS_VOID                           *pRcvMsg
)
{
    NAS_ESM_INFO_LOG("NAS_ESM_EhsmClearAllBearerNotifyMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmClearAllBearerNotifyMsgProc_ENUM, LNAS_ENTRY);

    /* ״̬��Ϊ����̬��˵�����쳣��������Ϣ */
    if (NAS_ESM_L_MODE_STATUS_SUSPENDED != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_EhsmClearAllBearerNotifyMsgProc: LTE is not suspend, discard msg.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmClearAllBearerNotifyMsgProc_ENUM, ESM_EHSM_NOT_SUSPEND_STATE);
        return;
    }

    /* ɾ��L�µ����г��� */
    NAS_ESM_ClearEsmResource();

    /* ɾ������֮ǰ��¼��EHRPD���� */
    NAS_ESM_ClearAllEhrpdPdnInfoProc();

    /* ֪ͨEMMִ�б���DETACH */
    NAS_ESM_SndEmmClLocalDetachNotifyMsg();

    /* ֪ͨRABM������г�����Դ������LTE���غ�EHRPD���� */
    NAS_ESM_SndEsmRabmClearClBearerNotifyMsg();

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_EhsmSyncPdnInfoConnectedProc
 Description    : ESM�յ�EHSM�����ĳ���CONNָʾʱ�Ĵ���
 Input          : EHSM_ESM_SYNC_PDN_INFO_IND_STRU*          EHSM��������Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhsmSyncPdnInfoConnectedProc(
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg
)
{
    VOS_UINT32                          ulIndex;

    NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoConnectedProc_ENUM, LNAS_ENTRY);

    /* �����EHRPD��ATTACH��PDN���ӣ����⴦�� */
    if (PS_TRUE == pEhsmMsg->ulAttachFlag)
    {
        /* ɾ��L�µ����г��� */
        NAS_ESM_ClearAllLteDefaultBearerInfoNotInformApsProc();

        /* ɾ������֮ǰ��¼������EHRPD���� */
        NAS_ESM_ClearAllEhrpdPdnInfoProc();

        /* ֪ͨEMMִ�б���DETACH */
        NAS_ESM_SndEmmClLocalDetachNotifyMsg();

        /* ֪ͨRABM������г�����Դ������EHRPD��LTE�ĳ��� */
        NAS_ESM_SndEsmRabmClearClBearerNotifyMsg();

        /* ����һ��PDNʵ�� */
        if (NAS_ESM_SUCCESS != NAS_ESM_AllocPdnIndexInEhrpdEntity(&ulIndex))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc: ATTACH PDN Alloc fail.");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoConnectedProc_ENUM, ESM_EHSM_PDN_ALLOC_FAIL);
            return;
        }

        /* ����ATTACH FLAG��ʶ */
        NAS_ESM_SET_EHRPD_PDN_ENTITY_ATTACH_FLAG(ulIndex, PS_TRUE);

        /* ����EHRPD������Ϣ */
        NAS_ESM_SaveEhrpdPdnInfo(ulIndex, pEhsmMsg);
    }
    else
    {
        /* ����һ��δ���õ�PDN��Ϣʵ�� */
        if (NAS_ESM_SUCCESS != NAS_ESM_AllocPdnIndexInEhrpdEntity(&ulIndex))
        {
            NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoMsgProc: Alloc fail.");
            TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoConnectedProc_ENUM, ESM_EHSM_PDN_ALLOC_FAIL);
            return;
        }

        /* ����EHRPD������Ϣ */
        NAS_ESM_SaveEhrpdPdnInfo(ulIndex, pEhsmMsg);
    }
    /* ʹ�õ�PDNʵ��������1 */
    NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM() ++;

    /* ��RABM����ID_ESM_ERABM_ACT_IND, ���뼼������ΪEHRPD�����ǻָ����̣���дEHRPD����ID */
    NAS_ESM_SndEsmRabmActIndMsg(ESM_ERABM_INVALID_BEARER_ID, ESM_ERABM_BEARER_RAT_EHRPD, PS_FALSE, pEhsmMsg->ulEpsbId);

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_EhsmSyncPdnInfoModifiedProc
 Description    : ESM�յ�EHSM�����ĳ���MODIFYָʾʱ�Ĵ���
 Input          : EHSM_ESM_SYNC_PDN_INFO_IND_STRU*          EHSM��������Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhsmSyncPdnInfoModifiedProc(
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg
)
{
    VOS_UINT32                          ulIndex;

    NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoModifiedProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoModifiedProc_ENUM, LNAS_ENTRY);

    /* ��EHRPDʵ���и���EHRPD����ID���ҵ�ǰ�޸ĵ�PDN�����Ƿ���� */
    if (NAS_ESM_SUCCESS == NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId(pEhsmMsg->ulEpsbId, &ulIndex))
    {
        /* ������ʽ�����޸Ĵ�PDN���ӵ���Ϣ */
        NAS_ESM_SaveEhrpdPdnInfo(ulIndex, pEhsmMsg);

        /* ����ID_ESM_ERABM_MDF_IND��Ϣ */
        NAS_ESM_SndEsmRabmMdfIndMsg(pEhsmMsg->ulEpsbId, ESM_ERABM_BEARER_RAT_EHRPD);
    }
    else
    {
        /* �����ڣ�˵�������쳣����������Ϣ����ӡ�쳣��Ϣ*/
        NAS_ESM_WARN_LOG("NAS_ESM_EhsmSyncPdnInfoModifiedProc:Warning:not exist this PDN info.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EhsmSyncPdnInfoModifiedProc_ENUM, ESM_EHSM_NO_PDN);
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_EhsmSyncPdnInfoDisconnectedProc
 Description    : ESM�յ�EHSM�����ĳ���DISCONNָʾʱ�Ĵ���
 Input          : EHSM_ESM_SYNC_PDN_INFO_IND_STRU*          EHSM��������Ϣ
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhsmSyncPdnInfoDisconnectedProc(
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg
)
{
    VOS_UINT32                          ulIndex;

    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];

    NAS_ESM_INFO_LOG("NAS_ESM_EhsmSyncPdnInfoDisconnectedProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhsmSyncPdnInfoDisconnectedProc_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_SET_S(aulEpsId, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32), 0, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32));

    /* ��EHRPDʵ���и���EHRPD����ID���ҵ�ǰ�޸ĵ�PDN�����Ƿ���� */
    if (NAS_ESM_SUCCESS == NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId(pEhsmMsg->ulEpsbId, &ulIndex))
    {
        /* ֪ͨRABM����RABM����ID_ESM_ERABM_DEACT_IND��ֻȥ����1��EHRPD���� */
        aulEpsId[0] = pEhsmMsg->ulEpsbId;
        NAS_ESM_SndEsmRabmDeactIndMsg(1, aulEpsId, ESM_ERABM_BEARER_RAT_EHRPD);

        /* ɾ����PDN���ӵ���Ϣ */
        NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);
    }
    else
    {
        /* �����ڣ�˵�������쳣����������Ϣ����ӡ�쳣��Ϣ*/
        NAS_ESM_WARN_LOG("NAS_ESM_EhsmSyncPdnInfoDisconnectedProc:Warning:not exist this PDN info.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EhsmSyncPdnInfoDisconnectedProc_ENUM, ESM_EHSM_NO_PDN);
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_ClearAllLteDefaultBearerInfoNotInformApsProc
 Description    : ESMģ��������д��ڼ���̬��LTE���أ�
                  ȱʡ���ز�֪ͨAPS��ר�г���֪ͨAPS
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_ClearAllLteDefaultBearerInfoNotInformApsProc(VOS_VOID)
{
    VOS_UINT32                          i;

    /*��ӡ����ú���*/
    NAS_ESM_INFO_LOG("NAS_ESM_ClearAllLteDefaultBearerInfoNotInformApsProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ClearAllLteDefaultBearerInfoNotInformApsProc_ENUM, LNAS_ENTRY);

    /* ������Ϣ��¼֪ͨAPP */
    NAS_ESM_ClearStateTable(APP_ERR_SM_DETACHED, PS_FALSE);

    /* ����EMM��״̬Ϊδע�� */
    NAS_ESM_SetEmmStatus(NAS_ESM_PS_REGISTER_STATUS_DETACHED);

    /* ���֧��˫APN����ֹͣ��Ӧ��ʱ����������ע�������Ч */
    if (NAS_ESM_OP_TRUE == NAS_ESM_AttachBearerReestEnable())
    {
        NAS_ESM_TimerStop(0, TI_NAS_ESM_ATTACH_BEARER_REEST);
        NAS_ESM_SetAttachBearerId(NAS_ESM_UNASSIGNED_EPSB_ID);
    }

    /* ����OPIDΪ0 */
    NAS_ESM_SetCurMaxOpIdValue(NAS_ESM_MIN_OPID_VALUE);

    #ifdef PS_ITT_PC_TEST_NAS
    /* NAS ST�����£���������������ע��ʱʹ����PTIֵΪ2������PTI��ʼ��Ϊ1������PTI���亯�������2��ʼʹ�� */
    NAS_ESM_SetCurMaxPTIValue(NAS_ESM_PTI_MIN_VALUE);
    #else

    /* PTI��ʼ��Ϊ0��ע��ʱ������PTI���亯�������1��ʼʹ�� */
    /*lint -e778*/
    NAS_ESM_SetCurMaxPTIValue(NAS_ESM_PTI_MIN_VALUE-1);
    /*lint +e778*/

    /* CID0��PS�ںϺ�Ƚ����⣬��ESMά����������NV�����ݻ���ڲ�һ��, �轫CID0��ʼ��Ϊר������ */
    NAS_ESM_ClearCid0StaticInfo();
    #endif

    NAS_ESM_SetCurMaxGwAuthIdVaule(NAS_ESM_GWAUTHID_MIN_VALUE);

    /* ��ʼ��CID 21~31 ������̬��Ϣ */
    NAS_ESM_ClearNwCtrlSdfPara();

    /* ֪ͨAPP��APS ������ر��ͷţ���ʼ��������Ϣ */
    for (i = NAS_ESM_MIN_EPSB_ID; i <= NAS_ESM_MAX_EPSB_ID; i++)
    {
        /* δ���ֱ��ɾ�� */
        if (NAS_ESM_BEARER_STATE_ACTIVE != NAS_ESM_GetBearCntxtState(i))
        {
            /* ��ʼ��������Ϣ */
            NAS_ESM_InitEpsbCntxtInfo(i);
            continue;
        }

        /* ����̬����ר�г��أ�����Ҫ֪ͨAPSȥ���ȱʡ���ز���֪ͨ */
        if (NAS_ESM_BEARER_TYPE_DEDICATED == NAS_ESM_GetBearCntxtType(i))
        {
            /* L4A�ع�, GUҪ��BEARER_INFO_IND��Rel Cnf֮ǰ */
            /* ֪ͨAPS ������ر��ͷ� */
            NAS_ESM_SndSmEspBearerDeactIndMsg(i);

            /* ֪ͨAPP ������ر��ͷţ���۵�����CID��֪ͨAPP�ͷŵ� */
            NAS_ESM_InformAppBearerRel(i);
        }

        /* ��ʼ��������Ϣ */
        NAS_ESM_InitEpsbCntxtInfo(i);
    }

    /* ��ʼ��ҵ�����Ķ�̬��Ϣ */
    for (i = 0; i < NAS_ESM_MAX_CID_NUM; i++)
    {
        NAS_ESM_MEM_SET_S(  NAS_ESM_GetSdfCntxtInfo(i),
                            sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU),
                            0,
                            sizeof(NAS_ESM_SDF_CNTXT_INFO_STRU));
    }

    /* ��ʼ��PDN���ӵĸ��� */
    NAS_ESM_SetCurPdnNum(0);

    /* ��ʼ�����Ϳտ���Ϣ�Ľṹ�� */
    NAS_ESM_ClearEsmSndNwMsgAddr();

    /* ���ESM������ */
    NAS_ESM_ClearEsmBuff();

    return;

}


/*****************************************************************************
 Function Name  : NAS_ESM_ClearAllEhrpdPdnInfoProc
 Description    : ESMģ���������EHRPD���ؼ�¼�Ĵ���
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_ClearAllEhrpdPdnInfoProc(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EhsmClearAllEhrpdPdnInfoProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_ClearAllEhrpdPdnInfoProc_ENUM, LNAS_ENTRY);

    /* ����PDNʵ���б� */
    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        if (PS_TRUE == pstPdnEntity->ucUsedFlag)
        {
            if (NAS_ESM_EHRPD_ENTITY_STATE_ALREADY_RCV_FIRST_BEARER_ACT_REQ ==  \
                                        NAS_ESM_GET_EHRPD_ENTITY_STATE())
            {
                /* ��APS�ϱ����ػָ�ʧ�� */
                NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(i, NAS_ESM_PDN_RECONNECT_RESULT_FAIL);
            }

            /* ɾ��EHRPD���ؼ�¼ */
            NAS_ESM_DeleteEhrpdPdnEntityInfo(i);
        }
    }

    /* ����EHRPDʵ�����ȴ��ָ�״̬ */
    NAS_ESM_SET_EHRPD_ENTITY_STATE(NAS_ESM_EHRPD_ENTITY_STATE_WAIT_HANDOVER);

    /* ʹ�õ�ʵ������ǿ����0 */
    NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM()      = 0;

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_AllocPdnIndexInEhrpdEntity
 Description    : ��EHRPDʵ���з���һ��δʹ�õ�����λ��
 Input          :
 Output         : VOS_UINT32*           �������䵽������ֵ
 Return Value   : VOS_UINT32            ������: 0�ɹ���1ʧ��

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_AllocPdnIndexInEhrpdEntity(
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_AllocPdnIndexInEhrpdEntity is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AllocPdnIndexInEhrpdEntity_ENUM, LNAS_ENTRY);

    /* ���PDNʵ��ʹ����Ϊ���ֱ�ӷ��ط���ʧ�� */
    if (NAS_ESM_EHRPD_PDN_MAX_NUM == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        /* δ�ҵ�������ʧ�� */
        NAS_ESM_INFO_LOG("NAS_ESM_AllocPdnIndexInEhrpdEntity: Entity total num is Max.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_AllocPdnIndexInEhrpdEntity_ENUM, ESM_EHSM_PDN_REACH_MAXNUM);
        return  NAS_ESM_FAILURE;
    }

    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* ��ʵ���б�����һ���ң��ҵ�δʹ�õ�λ�ã����سɹ�����������ֵ */
        if (PS_TRUE != pstPdnEntity->ucUsedFlag)
        {
            pstPdnEntity->ucUsedFlag    = PS_TRUE;
            *pulIndex                   = i;

            return NAS_ESM_SUCCESS;
        }
    }

    /* δ�ҵ�������ʧ�� */
    NAS_ESM_WARN_LOG("NAS_ESM_AllocPdnIndexInEhrpdEntity: Alloc failed.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_AllocPdnIndexInEhrpdEntity_ENUM, ESM_EHSM_PDN_ALLOC_FAIL);

    return NAS_ESM_FAILURE;
}

/*****************************************************************************
 Function Name  : NAS_ESM_SaveEhrpdPdnInfo
 Description    : ��EHRPDʵ���б���EHRPD������Ϣ
 Input          : VOS_UINT32                                ���������λ��
                  EHSM_ESM_SYNC_PDN_INFO_IND_STRU*          EHSM��������Ϣ
 Output         : None
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SaveEhrpdPdnInfo(
    VOS_UINT32                          ulIndex,
    EHSM_ESM_SYNC_PDN_INFO_IND_STRU    *pEhsmMsg
)
{
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;
    NAS_ESM_CONTEXT_APN_STRU            stTmpApnInfo1;
    APP_ESM_APN_INFO_STRU               stTmpApnInfo2;

    NAS_ESM_INFO_LOG("NAS_ESM_SaveEhrpdPdnInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SaveEhrpdPdnInfo_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_SET_S(  &stTmpApnInfo1,
                        sizeof(NAS_ESM_CONTEXT_APN_STRU),
                        0,
                        sizeof(NAS_ESM_CONTEXT_APN_STRU));
    NAS_ESM_MEM_SET_S(  &stTmpApnInfo2,
                        sizeof(APP_ESM_APN_INFO_STRU),
                        0,
                        sizeof(APP_ESM_APN_INFO_STRU));

    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* ����CID */
    pstPdnEntity->stEhPdnContextInfo.ulBitCid               = pEhsmMsg->ulBitCid;

    /* ����EHRPD�µĳ���ID */
    pstPdnEntity->stEhPdnContextInfo.ulEpsbId               = pEhsmMsg->ulEpsbId;

    /* ����EHRPD�µ�PDN��ַ */
    NAS_ESM_MEM_CPY_S(  &pstPdnEntity->stEhPdnContextInfo.stPdnAddr,
                        sizeof(EHSM_ESM_PDN_ADDR_STRU),
                        &pEhsmMsg->stPdnAddr,
                        sizeof(EHSM_ESM_PDN_ADDR_STRU));

    /* ����APN */
    if (NAS_ESM_OP_TRUE == pEhsmMsg->bitOpApn)
    {
        /* ��ʱ����APN������APN��ʽת�� */
        stTmpApnInfo1.ucApnLen          = pEhsmMsg->stApn.ucApnLen;
        NAS_ESM_MEM_CPY_S(  stTmpApnInfo1.aucApnName,
                            NAS_ESM_MAX_APN_NUM,
                            pEhsmMsg->stApn.aucApn,
                            pEhsmMsg->stApn.ucApnLen);

        /* ��APN��ʽ��δ����תΪ���� */
        if(NAS_ESM_SUCCESS != NAS_ESM_ApnReverseTransformation(&stTmpApnInfo2, &stTmpApnInfo1))
        {
            NAS_ESM_ERR_LOG("NAS_ESM_SaveEhrpdPdnInfo:apn format is illegal!");
            TLPS_PRINT2LAYER_ERROR(NAS_ESM_SaveEhrpdPdnInfo_ENUM, ESM_EHSM_APN_FORMAT_ILL);
            pstPdnEntity->stEhPdnContextInfo.bitOpApn       = NAS_ESM_OP_FALSE;
        }
        else
        {
            pstPdnEntity->stEhPdnContextInfo.bitOpApn       = NAS_ESM_OP_TRUE;
            NAS_ESM_MEM_CPY_S(  &pstPdnEntity->stEhPdnContextInfo.stApn,
                                sizeof(APP_ESM_APN_INFO_STRU),
                                &stTmpApnInfo2,
                                sizeof(APP_ESM_APN_INFO_STRU));
        }
    }

    /* ����APN AMBR */
    if (NAS_ESM_OP_TRUE == pEhsmMsg->bitOpApnAmbr)
    {
        pstPdnEntity->stEhPdnContextInfo.bitOpApnAmbr       = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY_S(  &pstPdnEntity->stEhPdnContextInfo.stApnAmbr,
                            sizeof(EHSM_ESM_APN_AMBR_STRU),
                            &pEhsmMsg->stApnAmbr,
                            sizeof(EHSM_ESM_APN_AMBR_STRU));
    }

    /* ����PCO IPV4 */
    if (NAS_ESM_OP_TRUE == pEhsmMsg->bitOpPcoIpv4Item)
    {
        pstPdnEntity->stEhPdnContextInfo.bitOpPcoIpv4Item   = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY_S(  &pstPdnEntity->stEhPdnContextInfo.stPcoIpv4Item,
                            sizeof(EHSM_ESM_PCO_IPV4_ITEM_STRU),
                            &pEhsmMsg->stPcoIpv4Item,
                            sizeof(EHSM_ESM_PCO_IPV4_ITEM_STRU));
    }

    /* ����PCO IPV6 */
    if (NAS_ESM_OP_TRUE == pEhsmMsg->bitOpPcoIpv6Item)
    {
        pstPdnEntity->stEhPdnContextInfo.bitOpPcoIpv6Item   = NAS_ESM_OP_TRUE;
        NAS_ESM_MEM_CPY_S(  &pstPdnEntity->stEhPdnContextInfo.stPcoIpv6Item,
                            sizeof(EHSM_ESM_PCO_IPV6_ITEM_STRU),
                            &pEhsmMsg->stPcoIpv6Item,
                            sizeof(EHSM_ESM_PCO_IPV6_ITEM_STRU));
    }

    return;
}


/*****************************************************************************
 Function Name  : NAS_ESM_DeleteEhrpdPdnEntityInfo
 Description    : ESMģ�����ĳEHRPD����ʵ����Ϣ��¼�Ĵ���
 Input          : VOS_UINT32            ʵ������
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_DeleteEhrpdPdnEntityInfo(
    VOS_UINT32                          ulIndex
)
{
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG1("NAS_ESM_DeleteEhrpdPdnEntityInfo:delete entity index = ", ulIndex);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_DeleteEhrpdPdnEntityInfo_ENUM, LNAS_ENTRY, ulIndex);

    pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* ����PDNʵ��Ϊδʹ�� */
    pstPdnEntity->ucUsedFlag            = PS_FALSE;

    /* ���ʵ����ر�ʶ */
    pstPdnEntity->ucAttachPdnFlag       = PS_FALSE;
    pstPdnEntity->ucIsOnReconnFlag      = PS_FALSE;
    pstPdnEntity->ucRsv                 = 0;

    /* ����L�»ָ��ĳ���ID */
    pstPdnEntity->ulHandoverEpsbId      = 0;

    /* ֹͣ�ȴ�PDN�ָ��ɹ���ʱ�� */
    NAS_ESM_TimerStop(ulIndex, TI_NAS_ESM_WAIT_EHRPD_PDN_RECONN_SUCC);

    /* ����տ���Ϣ��¼ */
    NAS_ESM_MEM_SET_S(  &pstPdnEntity->stNwMsgRecord,
                        sizeof(NAS_ESM_EHRPD_NW_MSG_RECORD_STRU),
                        0,
                        sizeof(NAS_ESM_EHRPD_NW_MSG_RECORD_STRU));

    /* ���������������Ϣ */
    NAS_ESM_MEM_SET_S(  &pstPdnEntity->stEhPdnContextInfo,
                        sizeof(NAS_ESM_EHRPD_PDN_CONTEXT_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_EHRPD_PDN_CONTEXT_INFO_STRU));

    /* EHRPD���ؼ�¼������һ */
    NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM() --;

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId
 Description    : ����EHRPD�ĳ���ID��Ϣ��EHRPDʵ���л�ȡ��Ӧ��PDNʵ������
 Input          : VOS_UINT32            EHRPD����ID��Ϣ
 Output         : VOS_UINT32*           ��ȡ��������ֵ��ַ
 Return Value   : VOS_UINT32            ��ȡ���: 0�ɹ���1ʧ��

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId(
    VOS_UINT32                          ulEpsbId,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId_ENUM, LNAS_ENTRY);

    /* ��EHRPD���أ�ֱ�ӷ��ػ�ȡʧ�� */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    /* ��ʵ���б�����һ���ң��ҵ�����ʹ�õģ��ҳ���ID��ͬ�����سɹ�����������ֵ */
    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        if ((PS_TRUE == pstPdnEntity->ucUsedFlag)
          &&(ulEpsbId == pstPdnEntity->stEhPdnContextInfo.ulEpsbId))
        {
            *pulIndex                   = i;
            return NAS_ESM_SUCCESS;
        }
    }

    /* δ�ҵ�������ʧ�� */
    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId: Not find same EpsbId.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedEpsbId_ENUM, ESM_EHSM_NOT_FIND_SAME_EPSBID);
    return NAS_ESM_FAILURE;
}

/*****************************************************************************
 Function Name  : NAS_ESM_GetEhrpdPdnEntityIndexBasedCid
 Description    : ����CID��EHRPDʵ���л�ȡ��Ӧ��PDNʵ������
 Input          : VOS_UINT32            CID��Ϣ
 Output         : VOS_UINT32*           ��ȡ��������ֵ��ַ
 Return Value   : VOS_UINT32            ��ȡ���: 0�ɹ���1ʧ��

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_GetEhrpdPdnEntityIndexBasedCid(
    VOS_UINT32                          ulCid,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    VOS_UINT32                          ulBitCid;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedCid is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedCid_ENUM, LNAS_ENTRY);

    /* ��EHRPD���أ�ֱ�ӷ��ػ�ȡʧ�� */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedCid: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedCid_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    /* ת����ulBitCid */
    ulBitCid        = ((VOS_UINT32)NAS_ESM_BIT_0 << ulCid);

    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* ��ʵ���б�����һ���ң��ҵ�����ʹ�õģ���CID��ͬ�����سɹ�����������ֵ */
        if ((PS_TRUE == pstPdnEntity->ucUsedFlag)
          &&(ulBitCid == pstPdnEntity->stEhPdnContextInfo.ulBitCid))
        {
            *pulIndex                   = i;
            return NAS_ESM_SUCCESS;
        }
    }

    /* δ�ҵ�������ʧ�� */
    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedApn: Not find same CID.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedCid_ENUM, ESM_EHSM_NOT_FIND_SAME_CID);
    return NAS_ESM_FAILURE;
}


/*****************************************************************************
 Function Name  : NAS_ESM_GetEhrpdPdnEntityIndexBasedApn
 Description    : ����APN��Ϣ��EHRPDʵ���л�ȡ��Ӧ��PDNʵ������
 Input          : APP_ESM_APN_INFO_STRU*          APN��Ϣ
 Output         : VOS_UINT32*                     ��ȡ��������ֵ��ַ
 Return Value   : VOS_UINT32                      ��ȡ���: 0�ɹ���1ʧ��

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_GetEhrpdPdnEntityIndexBasedApn(
    const APP_ESM_APN_INFO_STRU        *pstApn,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedApn is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedApn_ENUM, LNAS_ENTRY);

    /* ��EHRPD���أ�ֱ�ӷ��ػ�ȡʧ�� */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedApn: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedApn_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    /* APN����Ϊ0��99��ֱ�ӷ��ػ�ȡʧ�� */
    if ((0 == pstApn->ucApnLen)
      ||(APP_MAX_APN_LEN < pstApn->ucApnLen))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedApn: APN len is 0.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedApn_ENUM, ESM_EHSM_APN_LEN_0);
        return NAS_ESM_FAILURE;
    }

    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* ��ʵ���б�����һ���ң��ҵ�����ʹ�õģ���APN��ͬ�����سɹ�����������ֵ */
        if ((PS_TRUE == pstPdnEntity->ucUsedFlag)
          &&(NAS_ESM_OP_TRUE == pstPdnEntity->stEhPdnContextInfo.bitOpApn))
        {
            if ((pstApn->ucApnLen == pstPdnEntity->stEhPdnContextInfo.stApn.ucApnLen)
              &&(NAS_ESM_SUCCESS == NAS_ESM_MEM_CMP(pstApn->aucApnName,                   \
                                        pstPdnEntity->stEhPdnContextInfo.stApn.aucApnName,\
                                        pstApn->ucApnLen)))
            {
                *pulIndex               = i;
                return NAS_ESM_SUCCESS;
            }
        }
    }

    /* δ�ҵ�������ʧ�� */
    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedApn: Not find same APN.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedApn_ENUM, ESM_EHSM_NOT_FIND_SAME_APN);
    return NAS_ESM_FAILURE;
}

/*****************************************************************************
 Function Name  : NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId
 Description    : ����OPID��EHRPDʵ���в��Ҷ�Ӧ��PDNʵ������
 Input          : VOS_UINT32            OPIDֵ
 Output         : VOS_UINT32*           ��ȡ��������ֵ��ַ
 Return Value   : VOS_UINT32            ��ȡ���: 0�ɹ���1ʧ��

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId(
    VOS_UINT32                          ulOpId,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId_ENUM, LNAS_ENTRY);

    /* ��EHRPD���أ�ֱ�ӷ��ػ�ȡʧ�� */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* ��ʵ���б�����һ���ң��ҵ�����ʹ�õģ���OPID��ͬ�����سɹ�����������ֵ */
        if ((PS_TRUE == pstPdnEntity->ucUsedFlag)
          &&(ulOpId == pstPdnEntity->stNwMsgRecord.ulNwMsgOpId))
        {
            *pulIndex                   = i;
            return NAS_ESM_SUCCESS;
        }
    }

    /* δ�ҵ�������ʧ�� */
    NAS_ESM_INFO_LOG("NAS_ESM_GetEhrpdPdnEntityIndexBasedApn: Not find same OPID.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId_ENUM, ESM_EHSM_NOT_FIND_SAME_OPID);
    return NAS_ESM_FAILURE;
}


/*****************************************************************************
 Function Name  : NAS_ESM_GetAttachPdnInEhrpdEntity
 Description    : ��EHRPDʵ���в���ע��PDN
 Input          : None
 Output         : VOS_UINT32*           ������Ӧ��PDNʵ������
 Return Value   : VOS_UINT32            ��ȡ���: 0�ɹ���1ʧ��

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_GetAttachPdnInEhrpdEntity(
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_GetAttachPdnInEhrpdEntity is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetAttachPdnInEhrpdEntity_ENUM, LNAS_ENTRY);

    /* ��EHRPD���أ�ֱ�ӷ��ػ�ȡʧ�� */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetAttachPdnInEhrpdEntity: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetAttachPdnInEhrpdEntity_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    /* ��EHRPD PDNʵ���н���ѭ������ */
    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* �ҵ������Ϊע��PDN��ʵ�� */
        if ((PS_TRUE == pstPdnEntity->ucUsedFlag)
          &&(PS_TRUE == pstPdnEntity->ucAttachPdnFlag))
        {
            *pulIndex                   = i;
            return NAS_ESM_SUCCESS;
        }
    }

    /* δ�ҵ���˵�����ܱ�ȥ������ˣ�ֱ������һ��PDN��ΪATTACH PDN */
    NAS_ESM_INFO_LOG("NAS_ESM_GetAttachPdnInEhrpdEntity: NO attachflag PDN, get next reconnect PDN.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetAttachPdnInEhrpdEntity_ENUM, ESM_EHSM_NO_PDN_GET_NEXT_PND);
    if (NAS_ESM_SUCCESS ==  NAS_ESM_GetNextReconnectEhrpdPdn(pulIndex))
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(*pulIndex);
        pstPdnEntity->ucAttachPdnFlag   = PS_TRUE;
    }

    return NAS_ESM_FAILURE;
}


/*****************************************************************************
 Function Name  : NAS_ESM_GetAttachCidInEhrpdEntity
 Description    : ��EHRPDʵ���в���ע��PDN��Ӧ��CID
 Input          : None
 Output         : VOS_UINT32*           ����ע���õ�CID
 Return Value   : VOS_UINT32            ��ȡ���: 0�ɹ���1ʧ��

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_GetAttachCidInEhrpdEntity(
    VOS_UINT32                         *pulCid
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulCid;
    VOS_UINT32                          ulBitCid;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_GetAttachCidInEhrpdEntity is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetAttachCidInEhrpdEntity_ENUM, LNAS_ENTRY);

    /* �ҵ������Ϊע��PDN��ʵ�� */
    if (NAS_ESM_SUCCESS != NAS_ESM_GetAttachPdnInEhrpdEntity(&ulIndex))
    {
        return NAS_ESM_FAILURE;
    }

    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    ulBitCid        = pstPdnEntity->stEhPdnContextInfo.ulBitCid;

    /* CIDת�� */
    ulCid           = NAS_ESM_ConvertBitCidToCid(ulBitCid);

    /* ��ЧCID������ʧ�� */
    if (NAS_ESM_ILL_CID == ulCid)
    {
        return NAS_ESM_FAILURE;
    }

    *pulCid         = ulCid;

    return NAS_ESM_SUCCESS;

}


/*****************************************************************************
 Function Name  : NAS_ESM_GetNextReconnectEhrpdPdn
 Description    : ��EHRPDʵ���в�����һ�����Իָ���EHRPD PDN
 Input          : None
 Output         : VOS_UINT32*           ��һ��EHRPDʵ������
 Return Value   : VOS_UINT32            ��ȡ���: 0�ɹ���1ʧ��

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_GetNextReconnectEhrpdPdn(
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT8                           i;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity = VOS_NULL_PTR;

    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];

    NAS_ESM_INFO_LOG("NAS_ESM_GetNextReconnectEhrpdPdn is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetNextReconnectEhrpdPdn_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_SET_S(aulEpsId, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32), 0, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32));

    /* ��EHRPD���أ�ֱ�ӷ��ػ�ȡʧ�� */
    if(0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_GetNextReconnectEhrpdPdn: No EHRPD PDN info.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_GetNextReconnectEhrpdPdn_ENUM, ESM_EHSM_NO_PDN);
        return NAS_ESM_FAILURE;
    }

    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        /* ��ʵ���б�����һ���ң��ҵ�����ʹ�õ� */
        if (PS_TRUE == pstPdnEntity->ucUsedFlag)
        {
            /* ��������Ϊ������������ѡ����һ�� */
            if (NAS_ESM_SUCCESS != NAS_ESM_CheckAllowedPdnEntityToReconnect(pstPdnEntity))
            {
                /* ��APS�ϱ����ػָ�ʧ�� */
                NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(i, NAS_ESM_PDN_RECONNECT_RESULT_FAIL);

                /* ��EHRPDʵ�����ҵ���EHRPD����ID��֪ͨERABM�ͷŴ˳��� */
                pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);
                aulEpsId[0]  = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
                NAS_ESM_SndEsmRabmDeactIndMsg(1, aulEpsId, ESM_ERABM_BEARER_RAT_EHRPD);

                /* ɾ������EHRPD������Ϣ��¼ */
                NAS_ESM_DeleteEhrpdPdnEntityInfo(i);

                continue;
            }

            *pulIndex                   = i;

            /* ��ά�ɲ⣬�ϱ�HIDSʵ��״̬ */
            NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo();
            return NAS_ESM_SUCCESS;
        }
    }

    NAS_ESM_INFO_LOG("NAS_ESM_GetNextReconnectEhrpdPdn: Get next PDN failed.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_GetNextReconnectEhrpdPdn_ENUM, ESM_EHSM_NO_NEXT_PDN);
    return NAS_ESM_FAILURE;
}

/*****************************************************************************
 Function Name  : NAS_ESM_PerformEhrpdPdnReconnect
 Description    : ִ��EHRPD PDN�ָ�����
 Input          : None
 Output         : VOS_UINT32           EHRPDʵ������
 Return Value   : VOS_UINT32           0 ִ�гɹ��� 1 ִ��ʧ��

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_PerformEhrpdPdnReconnect(
    VOS_UINT32                          ulIndex
)
{
    VOS_UINT32                          ulPti;
    VOS_UINT32                          ulCid;
    VOS_UINT32                          ulBitCid;
    VOS_UINT32                          ulStateTblIndex;
    NAS_ESM_ENCODE_INFO_STRU            stEncodeInfo;
    NAS_ESM_STATE_INFO_STRU            *pstStateAddr        = VOS_NULL_PTR;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara          = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_PerformEhrpdPdnReconnect is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_PerformEhrpdPdnReconnect_ENUM, LNAS_ENTRY);

    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    ulBitCid        = pstPdnEntity->stEhPdnContextInfo.ulBitCid;

    /* LģΪ����̬��ֹͣEHRPD���ػָ����� */
    if (NAS_ESM_L_MODE_STATUS_NORMAL != NAS_ESM_GetLModeStatus())
    {
        NAS_ESM_WARN_LOG("NAS_ESM_PerformEhrpdPdnReconnect: L mode is already suspended!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_PerformEhrpdPdnReconnect_ENUM, ESM_EHSM_NOT_SUSPEND_STATE);
        return NAS_ESM_FAILURE;
    }

    /* CIDת�� */
    ulCid           = NAS_ESM_ConvertBitCidToCid(ulBitCid);

    /* ��ЧCID������ʧ�� */
    if (NAS_ESM_ILL_CID == ulCid)
    {
        return NAS_ESM_FAILURE;
    }

    /* ���䶯̬��ID */
    if (NAS_ESM_FAILURE == NAS_ESM_GetStateTblIndexByCid(ulCid, &ulStateTblIndex))
    {
        /* ��ӡ�쳣��Ϣ��״̬�������߸�CID�Ѿ��ڱ��� */
        NAS_ESM_WARN_LOG("NAS_ESM_PerformEhrpdPdnReconnect: Cid is dealing or resource is insufficient!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_PerformEhrpdPdnReconnect_ENUM, ESM_EHSM_TABLE_FULL_OR_CID_ALREADY_IN);
        return NAS_ESM_FAILURE;
    }

    /* ��EHRPD���ؼ�¼�е�APN��Ϣд���ӦCID��SDF���� */
    pstSdfPara                          = NAS_ESM_GetSdfParaAddr(ulCid);
    NAS_ESM_SetEhrpdPdnInfoToSdf(pstSdfPara, pstPdnEntity);

    /* ���ö�̬���в�������״̬����� */
    pstStateAddr                        = NAS_ESM_GetStateTblAddr(ulStateTblIndex);
    pstStateAddr->enBearerCntxtState    = NAS_ESM_BEARER_STATE_INACTIVE;
    pstStateAddr->enBearerCntxtType     = NAS_ESM_BEARER_TYPE_DEFAULT;
    pstStateAddr->enPdnReqType          = NAS_ESM_PDN_REQ_TYPE_HANDOVER;

    /* ����PTI�������������Ϣ�� */
    NAS_ESM_AssignPTI(&ulPti);
    pstStateAddr->stNwMsgRecord.ucPti   = (VOS_UINT8)ulPti;

    /* ���NAS_ESM_ENCODE_INFO_STRU */
    NAS_ESM_MEM_SET_S(  (VOS_VOID*)&stEncodeInfo,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_ESM_ENCODE_INFO_STRU));

    stEncodeInfo.bitOpESMCau            = NAS_ESM_OP_FALSE;
    stEncodeInfo.ulCid                  = pstStateAddr->ulCid;
    stEncodeInfo.ucPti                  = (VOS_UINT8)ulPti;
    stEncodeInfo.enPdnReqType           = pstStateAddr->enPdnReqType;

    /* ��װPDN_Connect_Req��Ϣ */
    if (NAS_ESM_FAILURE == NAS_ESM_EncodePdnConReqMsg(stEncodeInfo,             \
                                        pstStateAddr->stNwMsgRecord.aucMsgBuff, \
                                        &pstStateAddr->stNwMsgRecord.ulMsgLength))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_PerformEhrpdPdnReconnect:EncodePdnConReqMsg fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_PerformEhrpdPdnReconnect_ENUM, ESM_EHSM_ENCODE_PND_CONN_REQ_FAIL);

        /* ����ʧ�ܣ��ͷŶ�̬����Դ */
        NAS_ESM_RelStateTblResource(ulStateTblIndex);
        return NAS_ESM_FAILURE;
    }

    /* ����OPID����¼�տ���Ϣ���� */
    pstStateAddr->bitOpNwMsgRecord                = NAS_ESM_OP_TRUE;
    pstStateAddr->stNwMsgRecord.ulOpId            = NAS_ESM_AllocEmmEsmOpId();
    pstStateAddr->stNwMsgRecord.enEsmCnMsgType    = NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ;

    /* �����Ƿ�Ϊ����PDN�������� */
    pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq     = PS_FALSE;

    #if (FEATURE_ON == FEATURE_DSDS)
    pstStateAddr->enEsmBearerDataCnf              = NAS_ESM_BEARER_DATA_CNF_SENDING;
    NAS_ESM_SendBeginSessionNotify();
    #endif

    /* ���ú�����ESM->EMM������Ϣ:ID_EMM_ESM_DATA_REQ(NAS_ESMCN_MSG_TYPE_PDN_CONNECT_REQ) */
    NAS_ESM_SndEsmEmmDataReqMsg(pstStateAddr->stNwMsgRecord.ulOpId,                         \
                                                  pstStateAddr->stNwMsgRecord.ucIsEmcPdnReq,\
                                                  pstStateAddr->stNwMsgRecord.ulMsgLength,  \
                                                  pstStateAddr->stNwMsgRecord.aucMsgBuff);

    /* ��¼�տ���Ϣ */
    NAS_ESM_SndAirMsgReportInd(pstStateAddr->stNwMsgRecord.aucMsgBuff,                      \
                                                  pstStateAddr->stNwMsgRecord.ulMsgLength,  \
                                                  NAS_ESM_AIR_MSG_DIR_ENUM_UP,              \
                                                  ESM_PDN_CONNECT_REQ);

    /* ����T3482��ʱ�� */
    NAS_ESM_TimerStart(ulStateTblIndex, TI_NAS_ESM_T3482);

    /* ״̬ת�� */
    NAS_ESM_SetProcTransState(ulStateTblIndex, NAS_ESM_BEARER_PROC_TRANS_STATE_PENDING);

    /* ��EHRPD��PDNʵ�������ػָ������� */
    pstPdnEntity->ucIsOnReconnFlag = PS_TRUE;

    return NAS_ESM_SUCCESS;
}


/*****************************************************************************
 Function Name  : NAS_ESM_SetEhrpdPdnInfoToSdf
 Description    : ��EHRPD��PDNʵ���е���Ϣ���õ�SDF��
 Input          : NAS_ESM_SDF_PARA_STRU*          SDFָ��
                  NAS_ESM_EHRPD_PDN_ENTITY_STRU*  PDNʵ��ָ��
 Output         : None
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SetEhrpdPdnInfoToSdf(
    NAS_ESM_SDF_PARA_STRU              *pstSdfPara,
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity
)
{
    /* ȡ��ʵ���е�APN�����õ�SDF�� */
    if (NAS_ESM_OP_TRUE == pstPdnEntity->stEhPdnContextInfo.bitOpApn)
    {
        pstSdfPara->bitOpApn            = NAS_ESM_OP_TRUE;

        pstSdfPara->stApnInfo.ucApnLen  = pstPdnEntity->stEhPdnContextInfo.stApn.ucApnLen;

        NAS_ESM_MEM_CPY_S(  pstSdfPara->stApnInfo.aucApnName,
                            APP_MAX_APN_LEN,
                            pstPdnEntity->stEhPdnContextInfo.stApn.aucApnName,
                            pstPdnEntity->stEhPdnContextInfo.stApn.ucApnLen);
    }

    /* ȡ��ʵ���е�PDN���ͣ����õ�SDF�� */
    if ((EHSM_ESM_PDN_TYPE_IPV4 <= pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType)
      &&(EHSM_ESM_PDN_TYPE_IPV4V6 >= pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType))
    {
        pstSdfPara->bitOpPdnType         = NAS_ESM_OP_TRUE;
        pstSdfPara->enPdnType            = pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType;
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SetEhrpdPdnInfoToSyncPdnInfoMsg
 Description     : ��ֵEHRPD������Ϣ��PDNͬ����Ϣ��
 Input           : NAS_ESM_EPSB_CNTXT_INFO_STRU*            ESM������Ϣָ��
                   ESM_EHSM_SYNC_PDN_INFO_IND_STRU*         ESM��EHSM�ӿ��еĳ�����Ϣָ��
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SetEhrpdPdnInfoToSyncPdnInfoMsg
(
    const NAS_ESM_EPSB_CNTXT_INFO_STRU *pstEpsbCntxtInfo,
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstPdnInfoInd
)
{
    NAS_ESM_CONTEXT_APN_STRU            stTmpApnInfo;

    NAS_ESM_MEM_SET_S(  &stTmpApnInfo,
                        sizeof(NAS_ESM_CONTEXT_APN_STRU),
                        0,
                        sizeof(NAS_ESM_CONTEXT_APN_STRU));

    NAS_ESM_INFO_LOG("NAS_ESM_SetEhrpdPdnInfo is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_SetEhrpdPdnInfoToSyncPdnInfoMsg_ENUM, LNAS_ENTRY);

    /* ��ֵ����CID */
    pstPdnInfoInd->ulBitCid             = pstEpsbCntxtInfo->ulBitCId;

    /* ��ֵ����ID */
    pstPdnInfoInd->ulEpsbId             = pstEpsbCntxtInfo->ulEpsbId;

    /* �������APN��Ϣת��δ�����APN��Ϣ */
    if(APP_SUCCESS != NAS_ESM_ApnTransformaton(&stTmpApnInfo,
                                        &pstEpsbCntxtInfo->stApnInfo))
    {
        pstPdnInfoInd->bitOpApn         = NAS_ESM_OP_FALSE;
    }
    else
    {
        /* ��ֵAPN */
        pstPdnInfoInd->bitOpApn         = NAS_ESM_OP_TRUE;
        pstPdnInfoInd->stApn.ucApnLen   = stTmpApnInfo.ucApnLen;

        NAS_ESM_MEM_CPY_S(  pstPdnInfoInd->stApn.aucApn,
                            EHSM_ESM_MAX_APN_LEN,
                            stTmpApnInfo.aucApnName,
                            stTmpApnInfo.ucApnLen);
    }

    /* ��ֵPDN ADDRESS */
    NAS_ESM_MEM_CPY_S(  &pstPdnInfoInd->stPdnAddr,
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU),
                        &pstEpsbCntxtInfo->stPdnAddrInfo,
                        sizeof(NAS_ESM_CONTEXT_IP_ADDR_STRU));

    /* ��ֵAPN-AMBR����ʱ�Ȳ��� */

    /* ��ֵPCO����ʱ�Ȳ��� */

    return;
}


/*****************************************************************************
 Function Name  : NAS_ESM_ConvertBitCidToCid
 Description    : ��ֻ��һ��CID�������ulBitCid��Cid��ת��
 Input          : VOS_UINT32            ulBitCid
 Output         : None
 Return Value   : VOS_UINT32            ��ȡCID���

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_ConvertBitCidToCid(
    VOS_UINT32                          ulBitCid
)
{
    VOS_UINT8                           i;

    NAS_ESM_INFO_LOG1("NAS_ESM_ConvertBitCidToCid: ulBitCid = ", ulBitCid);
    TLPS_PRINT2LAYER_INFO1(NAS_ESM_ConvertBitCidToCid_ENUM, LNAS_ENTRY, ulBitCid);

    /* ѭ����λ�ҵ�CID��Ŀǰ�����ڳ��ػ�ۣ����ֻ����1��CID */
    for (i = 0; i <= NAS_ESM_MAX_CID; i++)
    {
        /* ���Ƽ�λ֮��Ľ��Ϊ1��CID���Ǽ����ҵ��󷵻سɹ� */
        if (NAS_ESM_OP_TRUE == ((ulBitCid >> i) & 0x00000001))
        {
            return i;
        }
    }

    return NAS_ESM_ILL_CID;
}

/*****************************************************************************
 Function Name  : NAS_ESM_IsBackOffAllowedToReconn
 Description    : BACK OFF�㷨�Ƿ���������ػָ��տ������ж�
 Input          : NAS_ESM_EHRPD_PDN_ENTITY_STRU*  PDNʵ��ָ��
 Output         : None
 Return Value   : VOS_UINT32            �ж����: 0�ɹ���1ʧ��

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_IsBackOffAllowedToReconn(
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity
)
{
    NAS_BACKOFF_JUDGMENT_PARA_STRU      stJudgmentPara;

    NAS_ESM_MEM_SET_S(  &stJudgmentPara,
                        sizeof(NAS_BACKOFF_JUDGMENT_PARA_STRU),
                        0,
                        sizeof(NAS_BACKOFF_JUDGMENT_PARA_STRU));

    /* ȱʡ��������APN��Back-off�㷨�ж��������������ֱ�Ӹ�APP��ʧ�� */
    if(NAS_ESM_OP_TRUE == pstPdnEntity->stEhPdnContextInfo.bitOpApn)
    {
        NAS_ESM_MEM_CPY_S(  &stJudgmentPara,
                            sizeof(APP_ESM_APN_INFO_STRU),
                            &pstPdnEntity->stEhPdnContextInfo.stApn,
                            sizeof(APP_ESM_APN_INFO_STRU));
    }
    else
    {
        /* ��APNֱ�������� */
        return NAS_ESM_SUCCESS;
    }

    if(NAS_BACKOFF_SUCC != NAS_BACKOFF_OperateJudgment(NAS_BACKOFF_NETRAT_LTE, &stJudgmentPara))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_IsBackOffAllowedToReconn: Back-off not allowed send PDN req.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_IsBackOffAllowedToReconn_ENUM, ESM_EHSM_BACKOFF_NOT_ALLOW_PDN_REQ);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}


/*****************************************************************************
 Function Name  : NAS_ESM_CheckAllowedPdnEntityToReconnect
 Description    : ����Ƿ�����ǰPDNʵ�巢����ػָ�����
 Input          : NAS_ESM_EHRPD_PDN_ENTITY_STRU*  PDNʵ��ָ��
 Output         : None
 Return Value   : VOS_UINT32            �����: 0������1��������

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_CheckAllowedPdnEntityToReconnect(
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity
)
{
    VOS_UINT32                          ulCid;

    NAS_ESM_INFO_LOG("NAS_ESM_CheckAllowedPdnEntityToReconnect is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAllowedPdnEntityToReconnect_ENUM, LNAS_ENTRY);

    /* Back-off�㷨�ж�������������𣬷���ʧ�� */
    if (NAS_ESM_SUCCESS != NAS_ESM_IsBackOffAllowedToReconn(pstPdnEntity))
    {
        return NAS_ESM_FAILURE;
    }

    /* �ھܾ�ԭ��ֵ#66�б��У��ҵ�ǰפ��PLMN��#66�б��PLMN������ʧ��*/
    if (VOS_TRUE == NAS_ESM_IsCurrentApnHas66Rej(pstPdnEntity->stEhPdnContextInfo.bitOpApn,\
                                        &pstPdnEntity->stEhPdnContextInfo.stApn))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_CheckAllowedPdnEntityToReconnect: in #66 list.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAllowedPdnEntityToReconnect_ENUM, ESM_EHSM_APN_IN_66_REJ_LIST);
        return NAS_ESM_FAILURE;
    }

    ulCid = NAS_ESM_ConvertBitCidToCid(pstPdnEntity->stEhPdnContextInfo.ulBitCid);

    /* CID��Ч������ʧ�� */
    if (NAS_ESM_ILL_CID == ulCid)
    {
        return NAS_ESM_FAILURE;
    }

    /* ����PDN���ͣ�����ʧ�� */
    if ((EHSM_ESM_PDN_TYPE_IPV4 > pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType)
      ||(EHSM_ESM_PDN_TYPE_IPV4V6 < pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_CheckAllowedPdnEntityToReconnect:PDN type err.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAllowedPdnEntityToReconnect_ENUM, ESM_EHSM_PDN_TYPE_ERROR);
        return NAS_ESM_FAILURE;
    }

    /* �����ǰʹ�õ�APN��#50�ܾ��б��У�����ʧ�� */
    if (VOS_TRUE == NAS_ESM_IsCurrentApnHas50Rej(pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType, \
                                        pstPdnEntity->stEhPdnContextInfo.bitOpApn,\
                                        &pstPdnEntity->stEhPdnContextInfo.stApn))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_CheckAllowedPdnEntityToReconnect: in #50 list.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAllowedPdnEntityToReconnect_ENUM, ESM_EHSM_APN_IN_50_REJ_LIST);
        return NAS_ESM_FAILURE;
    }

    /* �����ǰʹ�õ�APN��#51�ܾ��б��У�����ʧ�� */
    if (VOS_TRUE == NAS_ESM_IsCurrentApnHas51Rej(pstPdnEntity->stEhPdnContextInfo.stPdnAddr.enPdnType,  \
                                        pstPdnEntity->stEhPdnContextInfo.bitOpApn,\
                                        &pstPdnEntity->stEhPdnContextInfo.stApn))
    {
        NAS_ESM_INFO_LOG("NAS_ESM_CheckAllowedPdnEntityToReconnect: in #51 list.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_CheckAllowedPdnEntityToReconnect_ENUM, ESM_EHSM_APN_IN_51_REJ_LIST);
        return NAS_ESM_FAILURE;
    }

    return NAS_ESM_SUCCESS;
}


/*****************************************************************************
 Function Name  : NAS_ESM_EhrpdPdnConnectHandOverSuccProc
 Description    : EHRPD���ػָ��ɹ��Ĵ���
 Input          : VOS_UINT32            PDNʵ������
 Output         : None
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhrpdPdnConnectHandOverSuccProc(
    VOS_UINT32                          ulIndex
)
{
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity = VOS_NULL_PTR;
    VOS_UINT32                          ulEpsbId;
    VOS_UINT32                          ulEhrpdBearerId;
    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];

    NAS_ESM_INFO_LOG("NAS_ESM_EhrpdPdnConnectHandOverSuccProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhrpdPdnConnectHandOverSuccProc_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_SET_S(aulEpsId, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32), 0, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32));

    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* ȡ����LTE�»ָ����������ĳ���ID��ȡ��ԭEHRPD�·���ĳ���ID */
    ulEpsbId        = pstPdnEntity->ulHandoverEpsbId;
    ulEhrpdBearerId = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;

    /* ��RABM����ID_ESM_ERABM_ACT_IND, ��дLTE�»ָ����������ĳ���ID�����뼼������ΪLTE���ǻָ����̣���дԭEHRPD����ID */
    NAS_ESM_SndEsmRabmActIndMsg(ulEpsbId, ESM_ERABM_BEARER_RAT_LTE, PS_TRUE, ulEhrpdBearerId);

    /* ��APS�ϱ�ע����ػָ��ɹ� */
    NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(ulIndex, NAS_ESM_PDN_RECONNECT_RESULT_SUCC);

    /* ɾ������EHRPD������Ϣ��¼ */
    NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);

    /* Ѱ����һ��EHRPD����ִ�лָ����� */
    NAS_ESM_PerformNextEhrpdPdnReconnectProc();

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_EhrpdPdnConnectHandOverFailProc
 Description    : EHRPD���ػָ�ʧ�ܵĴ���
 Input          : VOS_UINT32            PDNʵ������
 Output         : None
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhrpdPdnConnectHandOverFailProc(
    VOS_UINT32                          ulIndex
)
{
    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EhrpdPdnConnectHandOverFailProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhrpdPdnConnectHandOverFailProc_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_SET_S(aulEpsId, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32), 0, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32));

    /* ��APS�ϱ����ػָ�ʧ�� */
    NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(ulIndex, NAS_ESM_PDN_RECONNECT_RESULT_FAIL);

    /* ��EHRPDʵ�����ҵ���EHRPD����ID��֪ͨERABM�ͷŴ˳��� */
    pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);
    aulEpsId[0]  = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
    NAS_ESM_SndEsmRabmDeactIndMsg(1, aulEpsId, ESM_ERABM_BEARER_RAT_EHRPD);

    /* ɾ������EHRPD������Ϣ��¼ */
    NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);

    /* Ѱ����һ��EHRPD����ִ�лָ����� */
    NAS_ESM_PerformNextEhrpdPdnReconnectProc();

    return;
}


/*****************************************************************************
 Function Name  : NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc
 Description    : EHRPDʵ���EMM����DATA REQ��Ϣ�ɹ��Ĵ���
 Input          : VOS_UINT32            OPID
 Output         : None
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc(
    VOS_UINT32                          ulOpId
)
{
    VOS_UINT32                          ulIndex;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    NAS_ESM_INFO_LOG("NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc_ENUM, LNAS_ENTRY);

    /* ����OPID���Ҷ�Ӧ��PDNʵ������ */
    if (NAS_ESM_SUCCESS != NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId(ulOpId, &ulIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc: Get PDN index failed.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EhrpdEntityProcEmmSendDataReqSucc_ENUM, ESM_EHSM_GET_PDN_IDX_FAIL);
        return;
    }

    pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* �ҵ�PDNʵ�壬����Ǽ���ȱʡ����ACP���ͳɹ���ִ�лָ��ɹ��Ĵ��� */
    if (NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_ACC == pstPdnEntity->stNwMsgRecord.enEsmCnMsgType)
    {
        NAS_ESM_EhrpdPdnConnectHandOverSuccProc(ulIndex);
    }
    else
    {
        /* ֻ��PDN REQ���ͳɹ����޶��� */
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_EhrpdEntityProcEmmSendDataReqFail
 Description    : EHRPDʵ���EMM����DATA REQ��Ϣʧ�ܵĴ���
 Input          : const EMM_ESM_DATA_CNF_STRU*
 Output         : None
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhrpdEntityProcEmmSendDataReqFail(
    const EMM_ESM_DATA_CNF_STRU        *pEmmEsmDataCnfMsg
)
{
    VOS_UINT32                          ulIndex;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity = VOS_NULL_PTR;

    #if (FEATURE_ON == FEATURE_DSDS)
    VOS_UINT32                          i;
    VOS_UINT32                          ulEpsIdNum = 0;
    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];

    NAS_ESM_MEM_SET_S(aulEpsId, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32), 0, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32));
    #endif

    NAS_ESM_INFO_LOG("NAS_ESM_EhrpdEntityProcEmmSendDataReqFail is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhrpdEntityProcEmmSendDataReqFail_ENUM, LNAS_ENTRY);

    /* �������NO RF���͵�ʧ�ܣ���ʣ��δ�ָ���EHRPD���ض����ٻָ��� */
    #if (FEATURE_ON == FEATURE_DSDS)
    if (EMM_ESM_SEND_RSLT_NORF == pEmmEsmDataCnfMsg->enDataCnfRst)
    {
        for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
        {
            /* ��EHRPDʵ�����ҵ�����δ�ָ���EHRPD����ID */
            pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

            if (PS_TRUE == pstPdnEntity->ucUsedFlag)
            {
                aulEpsId[ulEpsIdNum] = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
                ulEpsIdNum++;
            }
        }

        /* ֪ͨERABM�ͷ�����δ�ָ���EHRPD���� */
        NAS_ESM_SndEsmRabmDeactIndMsg(ulEpsIdNum, aulEpsId, ESM_ERABM_BEARER_RAT_EHRPD);

        /* �������EHRPD��PDN��¼ */
        NAS_ESM_ClearAllEhrpdPdnInfoProc();
        return;
    }
    #endif

    /* ����OPID���Ҷ�Ӧ��PDNʵ������ */
    if (NAS_ESM_SUCCESS != NAS_ESM_GetEhrpdPdnEntityIndexBasedOpId(pEmmEsmDataCnfMsg->ulEsmEmmOpId, &ulIndex))
    {
        NAS_ESM_WARN_LOG("NAS_ESM_EhrpdEntityProcEmmSendDataReqFail: Get PDN index failed.");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_EhrpdEntityProcEmmSendDataReqFail_ENUM, ESM_EHSM_GET_PDN_IDX_FAIL);
        return;
    }

    pstPdnEntity                        = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* �ҵ�PDNʵ�壬����Ǽ���ȱʡ����ACP����ʧ�ܣ�������ʧ�ܽ�������Ĵ��� */
    if (NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_ACC == pstPdnEntity->stNwMsgRecord.enEsmCnMsgType)
    {
        pstPdnEntity->stNwMsgRecord.ucSendFailTimes ++;

        /* ��һ�η���ʧ��ʱ�����ȴ��ָ����سɹ���ʱ������ֹ���಻�ٷ���ȱʡ���ؼ��������¹���
        �˶�ʱ����ɾ���˳��ؼ�¼ʱֹͣ�������ʱ��ɾ���˳��ؽ�����һ��EHRPD���ػָ����� */
        if (NAS_ESM_FIRST_FAIL_TIME == pstPdnEntity->stNwMsgRecord.ucSendFailTimes)
        {
            NAS_ESM_TimerStart(ulIndex, TI_NAS_ESM_WAIT_EHRPD_PDN_RECONN_SUCC);
        }

        /* ʧ�ܴ����������Ϊ���ػָ�ʧ�� */
        if (NAS_ESM_EHRPD_ALLOW_MAX_SND_FAIL_TIMES <= pstPdnEntity->stNwMsgRecord.ucSendFailTimes)
        {
            NAS_ESM_EhrpdPdnConnectHandOverFailProc(ulIndex);
            return;
        }

    }
    else
    {
        /* ֻ��PDN REQ����ʧ�ܣ��޶������ȴ�T3482��ʱ����ʱ�ط� */
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_PerformNextEhrpdPdnReconnectProc
 Description    : ִ����һ��EHRPD PDN�Ļָ�����
 Input          : None
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.sunjitan 00193151      2016-01-14  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_PerformNextEhrpdPdnReconnectProc(VOS_VOID)
{
    VOS_UINT32                          ulIndex      = 0;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity = VOS_NULL_PTR;
    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];

    NAS_ESM_INFO_LOG("NAS_ESM_PerformNextEhrpdPdnReconnectProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_PerformNextEhrpdPdnReconnectProc_ENUM, LNAS_ENTRY);

    /* ���PDNʵ����Ϊ0��˵���ָ��������̽���������EHRPDʵ��Ϊ�ȴ��ָ�̬ */
    if (0 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
    {
        NAS_ESM_INFO_LOG("NAS_ESM_PerformNextEhrpdPdnReconnectProc: PDN entity is 0.");
        TLPS_PRINT2LAYER_INFO(NAS_ESM_PerformNextEhrpdPdnReconnectProc_ENUM, ESM_EHSM_NO_PDN);
        NAS_ESM_SET_EHRPD_ENTITY_STATE(NAS_ESM_EHRPD_ENTITY_STATE_WAIT_HANDOVER);

        #if (FEATURE_ON == FEATURE_DSDS)
        NAS_ESM_SendEndSessionNotify();
        #endif

        return;
    }

    /* ȡ��һ������ */
    while (NAS_ESM_SUCCESS == NAS_ESM_GetNextReconnectEhrpdPdn(&ulIndex))
    {
        /* ��ȡ�ɹ���ִ����һ�����ػָ��������ִ�гɹ������� */
        if (NAS_ESM_SUCCESS == NAS_ESM_PerformEhrpdPdnReconnect(ulIndex))
        {
            return;
        }

        /* ִ��ʧ�� */

        /* ��APS�ϱ����ػָ�ʧ�� */
        NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(ulIndex, NAS_ESM_PDN_RECONNECT_RESULT_FAIL);

        /* ��EHRPDʵ�����ҵ���EHRPD����ID��֪ͨERABM�ͷŴ˳��� */
        pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);
        aulEpsId[0]  = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
        NAS_ESM_SndEsmRabmDeactIndMsg(1, aulEpsId, ESM_ERABM_BEARER_RAT_EHRPD);

        /* ɾ������EHRPD������Ϣ��¼ */
        NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);
    }

    /* ��ȡ��һ��ʧ�� */
    #if (FEATURE_ON == FEATURE_DSDS)
    NAS_ESM_SendEndSessionNotify();
    #endif

    return;
}


/*****************************************************************************
 Function Name  : NAS_ESM_WaitHandoverEhrpdPdnRcvApsPdpReleaseProc
 Description    : �ȴ��ָ���EHRPD�����յ�APS��PDP�ͷ�����Ĵ���
 Input          : const APP_ESM_PDP_RELEASE_REQ_STRU*  APS���ͷ���Ϣ
                  VOS_UINT32                           ���ͷŵ�PDNʵ������
 Output         : None
 Return Value   : VOS_UINT32

 History        :
      1.sunjitan 00193151      2016-01-14  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_WaitHandoverEhrpdPdnRcvApsPdpReleaseProc(
    const APP_ESM_PDP_RELEASE_REQ_STRU *pstAppEsmPdpRelReqMsg,
    VOS_UINT32                          ulIndex
)
{
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity = VOS_NULL_PTR;
    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];
    NAS_ESM_APP_CNF_MSG_STRU            stEsmAppCnfMsg;
    VOS_UINT32                          ulStateTblIndex = 0;

    NAS_ESM_INFO_LOG("NAS_ESM_WaitHandoverEhrpdPdnRcvApsPdpReleaseProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_WaitHandoverEhrpdPdnRcvApsPdpReleaseProc_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_SET_S(aulEpsId, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32),
                                        0, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32));

    /*��װ�ṹ��pstEsmAppCnfMsg*/
    NAS_ESM_MEM_SET_S(&stEsmAppCnfMsg, sizeof(NAS_ESM_APP_CNF_MSG_STRU),
                                        0, sizeof(NAS_ESM_APP_CNF_MSG_STRU));

    stEsmAppCnfMsg.bitOpEpsbId          = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.bitOpCId             = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpOpId            = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.bitOpMid             = NAS_ESM_OP_TRUE;
    stEsmAppCnfMsg.ulCId                = pstAppEsmPdpRelReqMsg->ulCid;
    stEsmAppCnfMsg.ulOpId               = pstAppEsmPdpRelReqMsg->ulOpId;
    stEsmAppCnfMsg.usOriginalId         = pstAppEsmPdpRelReqMsg->usOriginalId;
    stEsmAppCnfMsg.usTerminalId         = pstAppEsmPdpRelReqMsg->usTerminalId;
    stEsmAppCnfMsg.bitOpErrorCode       = NAS_ESM_OP_FALSE;
    stEsmAppCnfMsg.ulRst                = NAS_ESM_FAILURE;

    pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* ���ֻ��1��EHRPD PDNʵ�壬�ҵ�ǰLTE������ע��״̬��˵������Ψһ�ĳ��� */
    if ((1 == NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM())
      &&(NAS_ESM_PS_REGISTER_STATUS_ATTACHED != NAS_ESM_GetEmmStatus()))
    {
        /* ֱ�Ӹ�APS�ظ�ʧ�ܣ�����ǿ�лָ���LTE�²�����û�г��� */
        NAS_ESM_WARN_LOG("NAS_ESM_WaitHandoverEhrpdPdnRcvApsPdpReleaseProc:WARNING1:The Last PDN CONNECT can not be disconnect!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_WaitHandoverEhrpdPdnRcvApsPdpReleaseProc_ENUM, LNAS_FUNCTION_LABEL1);

        /* ��APP���س����ͷ�ʧ�ܣ�ԭ��ֵΪ:NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED */
        stEsmAppCnfMsg.ulRst          = NAS_ESM_FAILURE;
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode    = NAS_ESM_GetAppErrorByEsmCause(NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED);
        stEsmAppCnfMsg.bitOpEpsbId    = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulEpsbId       = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
        NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);
        return;
    }

    /* Ҫ�ͷŵĲ������һ������ */

    /* �����ǰPDNʵ�廹δ����ָ����̣�ֱ��ɾ����¼���� */
    if (PS_FALSE == pstPdnEntity->ucIsOnReconnFlag)
    {
        /* ֪ͨRABM����RABM����ID_ESM_ERABM_DEACT_IND��ֻȥ����1��EHRPD���� */
        aulEpsId[0] = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
        NAS_ESM_SndEsmRabmDeactIndMsg(1, aulEpsId, ESM_ERABM_BEARER_RAT_EHRPD);

        /* ɾ����PDNʵ���¼ */
        NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);

        /* ��APS�ϱ�PDP�ͷųɹ� */
        stEsmAppCnfMsg.ulRst = NAS_ESM_SUCCESS;
        NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);
        return;
    }

    /* ��ǰPDNʵ���Ѿ�����ָ����� */

    /* �����ǰҪ�ͷŵ���handover ATTACH�����е�����PDN�������Ѿ���ATTACH�տ����̣��޷�ֹͣ����APS����ʧ�� */
    if (PS_TRUE == pstPdnEntity->ucAttachPdnFlag)
    {
        /* ֱ�Ӹ�APS�ظ�ʧ�ܣ�����ǿ�лָ���LTE�²�����û�г��� */
        NAS_ESM_WARN_LOG("NAS_ESM_WaitHandoverEhrpdPdnRcvApsPdpReleaseProc:WARNING2:The Last PDN CONNECT can not be disconnect!");
        TLPS_PRINT2LAYER_WARNING(NAS_ESM_WaitHandoverEhrpdPdnRcvApsPdpReleaseProc_ENUM, LNAS_FUNCTION_LABEL2);

        /* ��APP���س����ͷ�ʧ�ܣ�ԭ��ֵΪ:NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED */
        stEsmAppCnfMsg.ulRst          = NAS_ESM_FAILURE;
        stEsmAppCnfMsg.bitOpErrorCode = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulErrorCode    = NAS_ESM_GetAppErrorByEsmCause(NAS_ESM_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED);
        stEsmAppCnfMsg.bitOpEpsbId    = NAS_ESM_OP_TRUE;
        stEsmAppCnfMsg.ulEpsbId       = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
        NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);
        return;
    }

    /* ��ǰҪ�ͷŵĲ���handover ATTACH������PDN���һ�δ�յ�����ظ����ؼ�������ֱ���ͷŶ�̬��ɾ����¼ */
    if (NAS_ESMCN_MSG_TYPE_ACT_DEFLT_EPS_BEARER_CNTXT_ACC != pstPdnEntity->stNwMsgRecord.enEsmCnMsgType)
    {
        /* �ҵ�ʹ�õĶ�̬��һ���ҵĵ� */
        if(NAS_ESM_SUCCESS == NAS_ESM_QueryStateTblIndexByCid(pstAppEsmPdpRelReqMsg->ulCid, &ulStateTblIndex))
        {
            /* �ͷ�״̬����Դ���������յ�������ؼ���������Ȼֱ�ӻ�REJ */
            NAS_ESM_RelStateTblResource(ulStateTblIndex);
        }

        /* ֪ͨRABM����RABM����ID_ESM_ERABM_DEACT_IND��ֻȥ����1��EHRPD���� */
        aulEpsId[0] = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
        NAS_ESM_SndEsmRabmDeactIndMsg(1, aulEpsId, ESM_ERABM_BEARER_RAT_EHRPD);

        /* ɾ����PDNʵ���¼ */
        NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);

        /* ��APS�ϱ�PDP�ͷųɹ� */
        stEsmAppCnfMsg.ulRst = NAS_ESM_SUCCESS;
        NAS_ESM_SndEsmAppSdfRelCnfMsg(&stEsmAppCnfMsg);

        /* Ѱ����һ��EHRPD���������ָ����� */
        NAS_ESM_PerformNextEhrpdPdnReconnectProc();
    }

    /* �����Ѿ������ֻ�ǻ�δ�յ����ͼ������ACP��EMM��DATA CNF��Ϣ */

    /* ��ʱ��Ӧ�ĳ�����ESM���������Ѿ����ڼ���̬�ĳ��أ��˴���������
    ����ԭESM�յ�APS�ͷŵĴ�������տڵ�DISCONN���� */

    return;
}

/*****************************************************************************
 Function Name  : NAS_ESM_EhrpdPdnHandoverSuccRcvApsPdpReleaseProc
 Description    : EHRPD���ػָ��ɹ��յ�APS��PDP�ͷ�����Ĵ���
 Input          : const APP_ESM_PDP_RELEASE_REQ_STRU*  APS���ͷ���Ϣ
                  VOS_UINT32                           ���ͷŵ�PDNʵ������
 Output         : None
 Return Value   : VOS_UINT32

 History        :
      1.sunjitan 00193151      2016-01-14  Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_EhrpdPdnHandoverSuccRcvApsPdpReleaseProc(
    const APP_ESM_PDP_RELEASE_REQ_STRU *pstAppEsmPdpRelReqMsg,
    VOS_UINT32                          ulIndex
)
{
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity = VOS_NULL_PTR;
    VOS_UINT32                          aulEpsId[ESM_ERABM_MAX_EPSB_NUM];

    NAS_ESM_INFO_LOG("NAS_ESM_EhrpdPdnHandoverSuccRcvApsPdpReleaseProc is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_ESM_EhrpdPdnHandoverSuccRcvApsPdpReleaseProc_ENUM, LNAS_ENTRY);

    NAS_ESM_MEM_SET_S(aulEpsId, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32), 0, ESM_ERABM_MAX_EPSB_NUM*sizeof(VOS_UINT32));

    pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* ��ǰҪ�ͷŵ���handover ATTACH������PDN����ATTACH CMP��δ���ͳɹ���
    ��ʱֻ��һ�����أ�ԭ������Ȼ���ʧ�ܣ����ô��� */
    if ((PS_TRUE == pstPdnEntity->ucAttachPdnFlag)
      &&(NAS_ESM_PS_REGISTER_STATUS_ATTACHED != NAS_ESM_GetEmmStatus()))
    {
        return;
    }

    /* ����ATTACH��PDN��ԭ���̻���Ȼִ�г���ȥ�������̣�
    �˴�ֻ��Ҫ֪ͨERABM�ͷ�EHRPD������Դ��������һ��EHRPD���ػָ����� */

    /* ֪ͨERABM�ͷŴ�EHRPD���� */
    pstPdnEntity = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);
    aulEpsId[0]  = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
    NAS_ESM_SndEsmRabmDeactIndMsg(1, aulEpsId, ESM_ERABM_BEARER_RAT_EHRPD);

    /* ɾ����EHRPD��PDNʵ�� */
    NAS_ESM_DeleteEhrpdPdnEntityInfo(ulIndex);

    /* Ѱ����һ��EHRPD����ִ�лָ����� */
    NAS_ESM_PerformNextEhrpdPdnReconnectProc();
    return;
}

/*lint -specific(-e433)*/
/*****************************************************************************
 Function Name   : NAS_ESM_SndEhsmSyncPdnInfoIndMsg
 Description     : ��EHSM���ͳ��ؼ���ͬ����Ϣ
 Input           : VOS_UINT32           ���غ�
                   VOS_UINT32           AttachPdn��ʶ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
    2.sunjitan 00193151    2016-01-14   Mofify for CL��ģ���������׶�
*****************************************************************************/
VOS_VOID NAS_ESM_SndEhsmSyncPdnInfoConnIndMsg(
    VOS_UINT32                          ulEpsbId
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstPdnInfoInd       = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstPdnInfoInd = (ESM_EHSM_SYNC_PDN_INFO_IND_STRU*)NAS_ESM_ALLOC_MSG(        \
                                        sizeof(ESM_EHSM_SYNC_PDN_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstPdnInfoInd)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEhsmSyncPdnInfoConnIndMsg:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEhsmSyncPdnInfoConnIndMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return ;
    }

    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_EHSM_MSG_ENTITY(pstPdnInfoInd),
                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstPdnInfoInd),
                        0,
                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstPdnInfoInd));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EHSM_MSG_HEAD(pstPdnInfoInd, ID_ESM_EHSM_SYNC_PDN_INFO_IND);

    /*��ȡ��ӦEpsbCntxtTbl���ַ*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    pstPdnInfoInd->enPdnOption          = EHSM_ESM_PDN_OPT_CONNECTED;

    /* ����ǵ�һ��PDN���ӣ�����Ҫ��֪ͨEHSM������Ϣʱ����Attach flagΪtrue */
    if (1 == NAS_ESM_GetCurPdnNum())
    {
        pstPdnInfoInd->ulAttachFlag = VOS_TRUE;
    }
    else
    {
        pstPdnInfoInd->ulAttachFlag = VOS_FALSE;
    }

    /* ��ֵ������Ϣ */
    NAS_ESM_SetEhrpdPdnInfoToSyncPdnInfoMsg(pstEpsbCntxtInfo, pstPdnInfoInd);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstPdnInfoInd);
    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndEhsmSyncPdnInfoModIndMsg
 Description     : ��EHSM���ͳ����޸�ͬ����Ϣ
 Input           : VOS_UINT32           ���غ�
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndEhsmSyncPdnInfoModIndMsg(
    VOS_UINT32                          ulEpsbId
)
{
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstPdnInfoInd       = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstPdnInfoInd   = (ESM_EHSM_SYNC_PDN_INFO_IND_STRU*)NAS_ESM_ALLOC_MSG(      \
                                        sizeof(ESM_EHSM_SYNC_PDN_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstPdnInfoInd)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEhsmSyncPdnInfoModIndMsg:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEhsmSyncPdnInfoModIndMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return ;
    }

    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_EHSM_MSG_ENTITY(pstPdnInfoInd),
                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstPdnInfoInd),
                        0,
                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstPdnInfoInd));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EHSM_MSG_HEAD(pstPdnInfoInd, ID_ESM_EHSM_SYNC_PDN_INFO_IND);

    /*��ȡ��ӦEpsbCntxtTbl���ַ*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    pstPdnInfoInd->enPdnOption          = EHSM_ESM_PDN_OPT_MODIFIED;
    pstPdnInfoInd->ulAttachFlag         = PS_FALSE;

    /* ��ֵ������Ϣ */
    NAS_ESM_SetEhrpdPdnInfoToSyncPdnInfoMsg(pstEpsbCntxtInfo, pstPdnInfoInd);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstPdnInfoInd);
    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg
 Description     : ��EHSM���ͳ���ȥ����ͬ����Ϣ
 Input           : VOS_UINT32           ���غ�
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg(
    VOS_UINT32                          ulEpsbId
)
{
    ESM_EHSM_SYNC_PDN_INFO_IND_STRU    *pstPdnInfoInd       = VOS_NULL_PTR;
    NAS_ESM_EPSB_CNTXT_INFO_STRU       *pstEpsbCntxtInfo    = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstPdnInfoInd = (ESM_EHSM_SYNC_PDN_INFO_IND_STRU*)NAS_ESM_ALLOC_MSG(        \
                                        sizeof(ESM_EHSM_SYNC_PDN_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstPdnInfoInd)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEhsmSyncPdnInfoDisconnIndMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return ;
    }

    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_EHSM_MSG_ENTITY(pstPdnInfoInd),
                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstPdnInfoInd),
                        0,
                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstPdnInfoInd));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EHSM_MSG_HEAD(pstPdnInfoInd, ID_ESM_EHSM_SYNC_PDN_INFO_IND);

    pstPdnInfoInd->enPdnOption          = EHSM_ESM_PDN_OPT_DISCONNECTED;
    pstPdnInfoInd->ulEpsbId             = ulEpsbId;

    /*��ȡ��ӦEpsbCntxtTbl���ַ*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    /* ��ֵ����CID */
    pstPdnInfoInd->ulBitCid             = pstEpsbCntxtInfo->ulBitCId;

    /*��ȡ��ӦEpsbCntxtTbl���ַ*/
    pstEpsbCntxtInfo = NAS_ESM_GetEpsbCntxtInfoAddr(ulEpsbId);

    /* ��ֵ����CID */
    pstPdnInfoInd->ulBitCid             = pstEpsbCntxtInfo->ulBitCId;

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstPdnInfoInd);
    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndEhsmClearAllBearerNotifyMsg
 Description     : ��EHSM����������г���ָʾ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndEhsmClearAllBearerNotifyMsg(VOS_VOID)
{
    ESM_EHSM_CLEAR_ALL_BEARER_NOTIFY_STRU        *pstClearNtfMsg = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstClearNtfMsg = (ESM_EHSM_CLEAR_ALL_BEARER_NOTIFY_STRU*)NAS_ESM_ALLOC_MSG( \
                                                  sizeof(ESM_EHSM_CLEAR_ALL_BEARER_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstClearNtfMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEhsmClearAllBearerNotifyMsg:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEhsmClearAllBearerNotifyMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return ;
    }

    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_EHSM_MSG_ENTITY(pstClearNtfMsg),
                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstClearNtfMsg),
                        0,
                        NAS_ESM_GET_EHSM_MSG_LENGTH(pstClearNtfMsg));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EHSM_MSG_HEAD(pstClearNtfMsg, ID_ESM_EHSM_CLEAR_ALL_BEARER_NOTIFY);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstClearNtfMsg);
    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndApsEhrpdPdnReconnSuccMsg
 Description     : ��APS����EHRPD���ػָ��ɹ���Ϣ
 Input           : VOS_UINT32           PDNʵ������ֵ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndApsEhrpdPdnReconnSuccMsg(
    VOS_UINT32                          ulIndex
)
{
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity       = VOS_NULL_PTR;

    /* ��ȡ��ӦPDNʵ���ַ */
    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /* �ָ��ɹ�����SM���ͳ���modify ind���ӿ���Ϣ���� */
    NAS_ESM_SndSmEspBearerMdfIndMsg(pstPdnEntity->ulHandoverEpsbId);

    return;
}


/*****************************************************************************
 Function Name   : NAS_ESM_SndApsEhrpdPdnReconnFailMsg
 Description     : ��APS����EHRPD���ػָ�ʧ����Ϣ
 Input           : VOS_UINT32           PDNʵ������ֵ
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndApsEhrpdPdnReconnFailMsg(
    VOS_UINT32                          ulIndex
)
{
    SM_ESM_EPS_BEARER_INFO_IND_STRU    *pstEpsBearInfoInd  = VOS_NULL_PTR;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity       = VOS_NULL_PTR;

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstEpsBearInfoInd = (SM_ESM_EPS_BEARER_INFO_IND_STRU*)NAS_ESM_ALLOC_MSG(    \
                                        sizeof(SM_ESM_EPS_BEARER_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstEpsBearInfoInd)
    {
        NAS_ESM_ERR_LOG("NAS_ESM_SndApsEhrpdPdnReconnFailMsg:ERROR:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndApsEhrpdPdnReconnFailMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return;
    }

    /* ��ȡ��ӦPDNʵ���ַ */
    pstPdnEntity    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(ulIndex);

    /*���*/
    NAS_ESM_MEM_SET_S(  NAS_ESM_GET_MSG_ENTITY(pstEpsBearInfoInd),
                        NAS_ESM_GET_MSG_LENGTH(pstEpsBearInfoInd),
                        0,
                        NAS_ESM_GET_MSG_LENGTH(pstEpsBearInfoInd));

    /* ȥ���ֻ�����ID��Cid���� */
    pstEpsBearInfoInd->enPdpOption      = SM_ESM_PDP_OPT_DEACTIVATE;
    pstEpsBearInfoInd->ulEpsbId         = pstPdnEntity->stEhPdnContextInfo.ulEpsbId;
    pstEpsBearInfoInd->ulBitCid         = pstPdnEntity->stEhPdnContextInfo.ulBitCid;

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_SM_MSG_HEAD(pstEpsBearInfoInd, ID_ESM_SM_EPS_BEARER_INFO_IND);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstEpsBearInfoInd);
    return;
}


/*****************************************************************************
 Function Name   : NAS_ESM_SndApsEhrpdPdnReconnectResultMsg
 Description     : ��EHSM���ͳ���ȥ����ͬ����Ϣ
 Input           : VOS_UINT32                               EHRPD���ؼ�¼����
                   NAS_ESM_PDN_RECONNECT_RESULT_ENUM_UINT8  �ָ����
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndApsEhrpdPdnReconnectResultMsg(
    VOS_UINT32                                    ulIndex,
    NAS_ESM_PDN_RECONNECT_RESULT_ENUM_UINT8       enResult
)
{

    if (NAS_ESM_PDN_RECONNECT_RESULT_SUCC == enResult)
    {
        /* �ָ��ɹ�����APS���ͳ���modify ind   */
        NAS_ESM_SndApsEhrpdPdnReconnSuccMsg(ulIndex);
    }
    else
    {
        /* �ָ�ʧ�ܣ���APS���ͳ���deactive ind */
        NAS_ESM_SndApsEhrpdPdnReconnFailMsg(ulIndex);
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndEmmClLocalDetachNotifyMsg
 Description     : ��EMM����local DETACHָʾ
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndEmmClLocalDetachNotifyMsg(VOS_VOID)
{
    EMM_ESM_CL_LOCAL_DETACH_NOTIFY_STRU          *pstDetachMsg        = VOS_NULL_PTR;

    /*����ռ䲢��������Ƿ�ɹ�*/
    pstDetachMsg    = (EMM_ESM_CL_LOCAL_DETACH_NOTIFY_STRU*)NAS_ESM_ALLOC_MSG(  \
                                                  sizeof(EMM_ESM_CL_LOCAL_DETACH_NOTIFY_STRU));

    if (VOS_NULL_PTR == pstDetachMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndEmmClLocalDetachNotifyMsg:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndEmmClLocalDetachNotifyMsg_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return ;
    }

    NAS_ESM_MEM_SET_S(NAS_ESM_GET_MSG_ENTITY(pstDetachMsg),
                      NAS_ESM_GET_MSG_LENGTH(pstDetachMsg),
                      0,
                      NAS_ESM_GET_MSG_LENGTH(pstDetachMsg));

    /*��д��Ϣͷ*/
    NAS_ESM_WRITE_EMM_MSG_HEAD(pstDetachMsg, ID_EMM_ESM_CL_LOCAL_DETACH_NOTIFY);

    /* ������Ϣ���ͺ��� */
    NAS_ESM_SND_MSG(pstDetachMsg);
    return;
}

/*****************************************************************************
 Function Name   : NAS_ESM_SndOmEhrpdUsedPdnEntityNum
 Description     : ��ά�ɲ⣬��OM��������ʹ�õ�PDNʵ������
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndOmEhrpdUsedPdnEntityNum(VOS_VOID)
{
    NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU         *pstEntityOmMsg      = VOS_NULL_PTR;

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstEntityOmMsg  = (NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU*)NAS_ESM_MEM_ALLOC( \
                                                  sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU));

    if (VOS_NULL_PTR == pstEntityOmMsg)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_ESM_ERR_LOG("NAS_ESM_SndOmEhrpdUsedPdnEntityNum:Alloc Msg fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndOmEhrpdUsedPdnEntityNum_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
        return;
    }

    NAS_ESM_MEM_SET_S(  pstEntityOmMsg,
                        sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU),
                        0,
                        sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU));

    pstEntityOmMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstEntityOmMsg->stMsgHeader.ulSenderPid         = PS_PID_ESM;
    pstEntityOmMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstEntityOmMsg->stMsgHeader.ulReceiverPid       = PS_PID_ESM;
    pstEntityOmMsg->stMsgHeader.ulLength            = sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_NUM_STRU) - 20;

    pstEntityOmMsg->stMsgHeader.ulMsgName           = NAS_ESM_OM_LOG_EHRPD_PDN_ENTITY_NUM;

    /* ���EHRPDʵ�嵱ǰ״̬ */
    pstEntityOmMsg->ulEhrpdPdnTotalNum              = NAS_ESM_GET_EHRPD_PDN_ENTITY_TOTAL_NUM();

    /* ��Ϣ�ϱ�HIDS */
    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstEntityOmMsg);
    NAS_ESM_MEM_FREE(pstEntityOmMsg);

    return;
}


/*****************************************************************************
 Function Name   : NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo
 Description     : ��ά�ɲ⣬��OM��������ʹ�õ�PDNʵ��״̬
 Input           : VOS_VOID
 Output          : None
 Return          : VOS_VOID

 History         :
    1.sunjitan 00193151    2015-06-16   Draft Enact
*****************************************************************************/
VOS_VOID NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU   *pstEntityOmMsg      = VOS_NULL_PTR;
    NAS_ESM_EHRPD_PDN_ENTITY_STRU      *pstPdnEntity        = VOS_NULL_PTR;

    /* ���ϱ�һ������ʹ�õ�PDNʵ������ */
    NAS_ESM_SndOmEhrpdUsedPdnEntityNum();

    /* �����ϱ�����ʹ�õ�PDNʵ����Ϣ */
    for (i = 0; i < NAS_ESM_EHRPD_PDN_MAX_NUM; i++)
    {
        pstPdnEntity                    = NAS_ESM_GET_EHRPD_PDN_ENTITY_ADDR(i);

        if (PS_TRUE == pstPdnEntity->ucUsedFlag)
        {
            /* ����ռ䲢��������Ƿ�ɹ� */
            pstEntityOmMsg = (NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU*)NAS_ESM_MEM_ALLOC(\
                                        sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU));

            if (VOS_NULL_PTR == pstEntityOmMsg)
            {
                /*��ӡ�쳣��Ϣ*/
                NAS_ESM_ERR_LOG("NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo:Alloc Msg fail!");
                TLPS_PRINT2LAYER_ERROR(NAS_ESM_SndOmEhrpdUsedPdnEntityStateInfo_ENUM, ESM_EHSM_ALLOC_MSG_FAIL);
                return;
            }

            NAS_ESM_MEM_SET_S(  pstEntityOmMsg,
                                sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU),
                                0,
                                sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU));

            pstEntityOmMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
            pstEntityOmMsg->stMsgHeader.ulSenderPid         = PS_PID_ESM;
            pstEntityOmMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
            pstEntityOmMsg->stMsgHeader.ulReceiverPid       = PS_PID_ESM;
            pstEntityOmMsg->stMsgHeader.ulLength            = sizeof(NAS_ESM_OM_EHRPD_PDN_ENTITY_STRU) - 20;

            pstEntityOmMsg->stMsgHeader.ulMsgName           = NAS_ESM_OM_LOG_EHRPD_PDN_ENTITY_INFO;

            /* ���EHRPDʵ�嵱ǰ״̬ */
            pstEntityOmMsg->enEntityState                   = NAS_ESM_GET_EHRPD_ENTITY_STATE();

            /* ���η���Ϣ�����PDNʵ�������� */
            pstEntityOmMsg->ucEntityIndex                   = (VOS_UINT8)i;
            NAS_ESM_MEM_CPY_S(  &pstEntityOmMsg->stEhPdnEntityInfo,
                                sizeof(NAS_ESM_EHRPD_PDN_ENTITY_STRU),
                                pstPdnEntity,
                                sizeof(NAS_ESM_EHRPD_PDN_ENTITY_STRU));

            /* ��Ϣ�ϱ�HIDS */
            (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstEntityOmMsg);
            NAS_ESM_MEM_FREE(pstEntityOmMsg);
        }
    }

    return;
}


/*lint -specific(+e433)*/
#endif


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

