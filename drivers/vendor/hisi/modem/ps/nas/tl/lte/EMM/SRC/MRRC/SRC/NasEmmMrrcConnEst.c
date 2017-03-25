/******************************************************************************

        @(#)Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
    File name   : NasEmmMrrcConnEst.c
    Description : ������EMM-MRRCģ�����������ݹ����д���RRC���ӽ���
                  �����Ѿ�������RRC��·�Ϸ����������ݵĹ���
    History     :
      1.  zangyalan 57968  2008-09-10  Draft Enact

******************************************************************************/


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasEmmGIMComm.h"
#include  "NasEmmMrrc.h"
#include  "NasEmmAttDetInclude.h"
#if (FEATURE_LPP == FEATURE_ON)
#include  "NasEmmLppMsgProc.h"
#include  "NasEmmSsMsgProc.h"
#endif

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASEMMMRRCCONNEST_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASEMMMRRCCONNEST_C
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

NAS_EMM_MRRC_MGMT_DATA_STRU     g_stEmmMrrcMgmtData[NAS_LMM_RRC_SAVE_MSG_MAX_NUM];

VOS_UINT32              g_ulSaveMsgNum = 0;

static  VOS_UINT32              gulMmRrcOpId = 0;


/*RRC��������ֱ��NAS��Ϣ�������� */
NAS_LMM_SEND_MSG_RESULT_ACT_STRU  gstEmmMrrcSendMsgResultActTbl[]=
{
    {NAS_EMM_MSG_ATTACH_REQ,                NAS_EMM_SndAttachReqFailProc,           VOS_NULL_PTR},
    {NAS_EMM_MSG_ATTACH_CMP,                NAS_EMM_SndAttachCmpFailProc,           NAS_EMM_SndAttachCmpSuccProc},
    {NAS_EMM_MSG_DETACH_REQ,                NAS_EMM_SndDetachReqFailProc,           NAS_EMM_SndDetachReqSuccProc},
    {NAS_EMM_MSG_DETACH_ACP,                NAS_EMM_SndMtDetachAccFailProc,         VOS_NULL_PTR},
    {NAS_EMM_MSG_LOAD_BALANCING_TAU,        NAS_EMM_SndTauReqFailProc,              VOS_NULL_PTR},
    {NAS_EMM_MSG_NOT_LOAD_BALANCING_TAU,    NAS_EMM_SndTauReqFailProc,              VOS_NULL_PTR},
    {NAS_EMM_MSG_TAU_CMP,                   NAS_EMM_SndTauCompleteFailProc,         NAS_EMM_SndTauCmpSuccProc},
    {NAS_EMM_MSG_SMC_COMPL,                 NAS_EMM_SndCommonProcedureMsgFailProc,  VOS_NULL_PTR},
    {NAS_EMM_MAS_SMC_REJ,                   NAS_EMM_SndCommonProcedureMsgFailProc,  VOS_NULL_PTR},
    {NAS_EMM_MSG_AUTH_RSP,                  NAS_EMM_SndCommonProcedureMsgFailProc,  VOS_NULL_PTR},
    {NAS_EMM_MSG_AUTH_FAIL,                 NAS_EMM_SndCommonProcedureMsgFailProc,  VOS_NULL_PTR},
    {NAS_EMM_MSG_IDEN_RSP,                  NAS_EMM_SndCommonProcedureMsgFailProc,  VOS_NULL_PTR},
    {NAS_EMM_NAS_UPLINK_NAS_TRANSPORT,      NAS_EMM_SndSmsdataFailProc,             VOS_NULL_PTR},
    {NAS_EMM_MSG_GUTI_CMP,                  NAS_EMM_SndCommonProcedureMsgFailProc,  VOS_NULL_PTR},
    {NAS_EMM_MSG_SERVICE_REQ,               NAS_EMM_SndServiceReqFailProc,          VOS_NULL_PTR},
    {NAS_EMM_MSG_EXTENDED_SERVICE_REQ,      NAS_EMM_SndExtendedServiceReqFailProc,  NAS_EMM_SndExtendedServiceReqSuccProc},
    #if (FEATURE_LPP == FEATURE_ON)
    {NAS_EMM_NAS_UPLINK_GENERIC_NAS_TRANSPORT, NAS_EMM_SndUplinkGenericTransportFailProc, NAS_EMM_SndUplinkGenericTransportSuccProc},
    #endif
    {NAS_EMM_MSG_ESM,                       NAS_EMM_SndEsmMsgFailProc,              NAS_EMM_SndEsmMsgSuccProc}
};
VOS_UINT32        g_ulSendMsgResultActTblLen = sizeof(gstEmmMrrcSendMsgResultActTbl)
                                                / sizeof(NAS_LMM_SEND_MSG_RESULT_ACT_STRU);
/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : NAS_EMM_MrrcInit
 Discription    : MRRCģ���ʼ������
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968 2008-10-16  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_MrrcInit(VOS_VOID)
{
    /*���ý������ͷ���·ģ��ĳ�ʼ������ */
    NAS_EMM_MrrcEstInit();
    NAS_EMM_MrrcRelInit();
    NAS_EMM_MrrcMgmtDataInit();
    NAS_EMM_INIT_MM_RRC_OPID();
    return;
}


VOS_VOID  NAS_EMM_FreeMrrcDyn( VOS_VOID )
{
    /* ��ʱΪ�� */
    return;
}


/*****************************************************************************
 Function Name  : NAS_EMM_MrrcEstInit
 Discription    : MRRC ����ģ���ʼ������
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968 2008-10-16  Draft Enact
*****************************************************************************/
VOS_VOID NAS_EMM_MrrcEstInit(VOS_VOID)
{
    /*����Դ*/
    NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF);

    return;
}
/*****************************************************************************
 Function Name  : NAS_EMM_MrrcConnectFailInd
 Discription    : �����ڲ���ϢMRRC_CONNECT_FAIL_IND
 Input          :
 Output         : None
 Return         : None
 History:
      1.zangyalan   57968    2008-09-23  Draft Enact
      2.zhengjunyan 00148421 2009.03.09  add rel cause
      3.X00148705            2009-09-23  �޸�Ϊת���ڲ���CONNECT_FAIL
*****************************************************************************/
/*lint -e960*/
/*lint -e961*/
VOS_VOID NAS_EMM_MrrcConnectFailInd(LRRC_LNAS_EST_RESULT_ENUM_UINT32 enEstResult)
{
    NAS_EMM_MRRC_CONNECT_FAIL_IND_STRU            *pstMrrcConnectFailIndMsg;
    VOS_UINT32                                    ulMsgLen;

    /*���㳤��*/
    ulMsgLen  = NAS_EMM_MRRC_CONNECT_FAIL_IND_LEN;

    /*��ȡ�ڲ���Ϣ��ַ*/
    pstMrrcConnectFailIndMsg = (NAS_EMM_MRRC_CONNECT_FAIL_IND_STRU *)NAS_LMM_GetSendIntraMsgBuffAddr(ulMsgLen);
    if(NAS_EMM_NULL_PTR == pstMrrcConnectFailIndMsg)
    {
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_MrrcConnectFailInd: Alloc Msg Fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_MrrcConnectFailInd_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*���VOS��Ϣͷ*/
    NAS_EMM_INTRA_MSG_HEADER(pstMrrcConnectFailIndMsg, ulMsgLen);

    /*��ֵ��Ϣ ID*/
    pstMrrcConnectFailIndMsg->ulMsgId = ID_NAS_LMM_INTRA_MRRC_CONNECT_FAIL_IND;

    /*��ֵ���ӽ���ʧ�ܵ�ԭ��*/
    pstMrrcConnectFailIndMsg->enEstResult = enEstResult;

    /* �����ڲ���Ϣ����� */
    NAS_EMM_SEND_INTRA_MSG(             pstMrrcConnectFailIndMsg);

    return;
}

/*****************************************************************************
 Function Name  : NAS_EMM_ChangeRrcConnStateToEstSignal
 Discription    : ��RRC����״̬��Ϊ����״̬
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968  2008-11-27  Draft Enact
      2.  zhengjunyan 00148421 2011-5-09 MOD
*****************************************************************************/
VOS_VOID  NAS_EMM_ChangeRrcConnStateToEstSignal( VOS_VOID )
{
    /*�жϵ�ǰ����״̬ΪNOT_EXIST�����ϱ�MMC������������̬*/
    if(MMC_LMM_CONNECTED_SIG != NAS_EMM_GetConnState())
    {
        NAS_EMM_SendMmcStatusInd(       MMC_LMM_STATUS_TYPE_CONN_STATE,
                                        MMC_LMM_CONNECTED_SIG);
    }

    /*��RRC����״̬��Ϊ����״̬*/
    /* coverity[mixed_enums] */
    NAS_EMM_SetConnState(NAS_EMM_CONN_SIG);
}

/*****************************************************************************
 Function Name  : NAS_EMM_ChangeRrcConnStateToEsting
 Discription    : ��RRC����״̬��Ϊ����״̬
 Input          :
 Output         : None
 Return         : None
 History:
      1.  leili 00132387  2009-07-08  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ChangeRrcConnStateToEsting( VOS_VOID )
{
    /*�жϵ�ǰ����״̬ΪNOT_EXIST�����ϱ�MMC������������̬*/
    if(MMC_LMM_CONN_ESTING != NAS_EMM_GetConnState())
    {
        NAS_EMM_SendMmcStatusInd(       MMC_LMM_STATUS_TYPE_CONN_STATE,
                                        MMC_LMM_CONN_ESTING);
    }

    /*��RRC����״̬��Ϊ����״̬*/
    /* coverity[mixed_enums] */
    NAS_EMM_SetConnState(NAS_EMM_CONN_ESTING);
}

/*****************************************************************************
 Function Name  : NAS_EMM_ChangeRrcConnStateToEstData
 Discription    : ��RRC����״̬��Ϊ����״̬
 Input          :
 Output         : None
 Return         : None
 History:
      1.  leili 00132387  2011-06-16  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_ChangeRrcConnStateToEstData( VOS_VOID )
{
    /*�жϵ�ǰ����״̬ΪDATA�����ϱ�MMC������������̬*/
    if(NAS_EMM_CONN_DATA != NAS_EMM_GetConnState())
    {
        NAS_EMM_SendMmcStatusInd(       MMC_LMM_STATUS_TYPE_CONN_STATE,
                                        MMC_LMM_CONNECTED_DATA);
    }

    /*��RRC����״̬��Ϊ����״̬*/
    NAS_EMM_SetConnState( NAS_EMM_CONN_DATA );
}

/*****************************************************************************
 Function Name  : NAS_EMM_SndUplinkNasMsg
 Discription    : ��LRRC����������Ϣ
 Input          :
 Output         : None
 Return         : None
 History:
      1.  leili 00132387  2012-09-12  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_SndUplinkNasMsg
(
    VOS_VOID *pMsgStru
)
{
    NAS_EMM_MRRC_DATA_REQ_STRU         *pstMrrcDataRqMsg = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulMmRrcOpId = NAS_LMM_RRC_OPID_NOT_VAILID;

#if(VOS_WIN32 == VOS_OS_VER)
    #ifdef PS_ITT_PC_TEST_NAS_ST
    VOS_UINT32                          ulRslt = VOS_FALSE;
    #endif
#endif

    NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_SndUplinkNasMsg is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_SndUplinkNasMsg_ENUM,LNAS_ENTRY);

    /* ��μ�� */
    if ( NAS_EMM_NULL_PTR == pMsgStru)
    {
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_SndUplinkNasMsg:input ptr null!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndUplinkNasMsg_ENUM,LNAS_NULL_PTR);
        return;
    }

    /* �ṹת�� */
    pstMrrcDataRqMsg = (NAS_EMM_MRRC_DATA_REQ_STRU *)pMsgStru;

    /* ��ӡ�տ���Ϣ */
    NAS_LMM_PrintCnMsgAndData(           &(pstMrrcDataRqMsg->stNasMsg));

    /* ��������ͷŹ����У����ٸ�RRC��������Ϣ����Ϊ���Լ����ڲ�����ʧ�� */
    if((NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
        || (NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState()))
    {
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_SndUplinkNasMsg:Releasing,rrc is cell searching,can't est.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndUplinkNasMsg_ENUM,LNAS_EMM_CANT_EST);

        /*��MRRC_CONNECT_FAIL_IND*/
        NAS_EMM_MrrcConnectFailInd(LRRC_EST_CELL_SEARCHING);
        return;
    }




    /* �������ܺ������Ա���֮ǰ���������������̬��������������̬��
    �򻺴�δ���ܵ�����ֱ����Ϣ,���ܻ�ʹNAS COUNT��1 */
    if((NAS_EMM_CONN_SIG == NAS_EMM_GetConnState()) ||
        (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState()))
    {
        ulMmRrcOpId                 = NAS_EMM_MrrcAllocMmRrcOpId();

        NAS_EMM_SaveMrrcDataReqMsg(pstMrrcDataRqMsg, ulMmRrcOpId);
    }

    /* �Կտ���Ϣ�ӱ���:��������͵��ڲ���Ϣ*/
    if( NAS_EMM_SMC_OPEN == g_ulSmcControl)
    {
        if(NAS_EMM_FAIL == NAS_EMM_SecuProtect(pstMrrcDataRqMsg))
        {
            NAS_EMM_GIM_ERROR_LOG("NAS_EMM_SndUplinkNasMsg:PROT ERR.");
            TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndUplinkNasMsg_ENUM,LNAS_ERROR);
            return;
        }
    }

    /* �쿴RRC�����Ƿ���� */
    if((NAS_EMM_CONN_SIG == NAS_EMM_GetConnState()) ||
        (NAS_EMM_CONN_DATA == NAS_EMM_GetConnState()))
    {
        NAS_EMM_RrcDataReq(pstMrrcDataRqMsg, ulMmRrcOpId);
    }
    else if(NAS_EMM_CONN_WAIT_SYS_INFO == NAS_EMM_GetConnState())
    {
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_SndUplinkNasMsg: WAIT_SYS_INFO");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_SndUplinkNasMsg_ENUM,LNAS_FUNCTION_LABEL1);
    }
    else
    {
        NAS_EMM_IntraEstReq(pstMrrcDataRqMsg);
    }

    return;
}

/*****************************************************************************
 Function Name  : NAS_EMM_CcoInterSystemSuccProc
 Discription    : GU->L CCO�ɹ�����
 Input          :
 Output         : None
 Return         : None
 History:
      1.  leili 00132387  2012-03-16  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_CcoInterSystemSuccProc( VOS_VOID )
{
    NAS_MML_PS_BEARER_CONTEXT_STRU  *pstPsBearerCtx = NAS_EMM_NULL_PTR;

    if (NAS_EMM_CCO_CHANGE_TIN_VALID == NAS_LMM_GetEmmInfoTinChagFlag())
    {

        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_CcoInterSystemSuccProc:GET PS BEARER INFO");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_CcoInterSystemSuccProc_ENUM,LNAS_ENTRY);

        pstPsBearerCtx = NAS_EMM_GetPsBearerCtx();
        NAS_EMM_UpdateBearISRFlag(pstPsBearerCtx);

        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
        NAS_LMM_SetTempEmmInfoTinType(MMC_LMM_TIN_BUTT);
        NAS_LMM_SetEmmInfoTinChagFlag(NAS_EMM_CCO_CHANGE_TIN_INVALID);


    }
    return;
}

/*****************************************************************************
 Function Name  : NAS_EMM_CcoInterSystemFailProc
 Discription    : GU->L CCOʧ�ܴ���
 Input          :
 Output         : None
 Return         : None
 History:
      1.  leili 00132387  2012-03-16  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_EMM_CcoInterSystemFailProc( VOS_VOID )
{
    NAS_MML_PS_BEARER_CONTEXT_STRU *pstPsBearerCtx;
    pstPsBearerCtx   =  NAS_EMM_GetPsBearerCtx();
    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_CcoInterSystemFailProc is entry");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_CcoInterSystemFailProc_ENUM,LNAS_ENTRY);

    if (NAS_EMM_CCO_CHANGE_TIN_VALID == NAS_LMM_GetEmmInfoTinChagFlag())
    {
        NAS_EMM_SetTinType(NAS_LMM_GetTempEmmInfoTinType());
        NAS_LMM_SetTempEmmInfoTinType(MMC_LMM_TIN_BUTT);
        NAS_LMM_SetEmmInfoTinChagFlag(NAS_EMM_CCO_CHANGE_TIN_INVALID);

        NAS_EMM_PUBU_LOG_INFO("NAS_EMM_CcoInterSystemFailProc: UPDATE MML PS BEARER INFO:");
        TLPS_PRINT2LAYER_INFO(NAS_EMM_CcoInterSystemFailProc_ENUM,LNAS_FUNCTION_LABEL1);
        NAS_LMM_LogPsBearerCtxInfo(pstPsBearerCtx);
    }

    return;
}



/*****************************************************************************
 Function Name  : NAS_EMM_PreProcMsgRrcMmEstCnf
 Discription    : EMM����Ҫ�����ĳ����£�״̬�յ�RRC_MM_EST_CNFʱ,
                  ʹ�øú�������
 Input          : ��Ϣ
 Output         : None
 Return         : None
 History:
      1.zangyalan   57968    2008-09-10  Draft Enact
      2.zhengjunyan 00148421 2009.03.09  access barred
      3.lifuxin     00253982 2014.10.28  LNAS���������ع�
      4.leixiantiao 00258641 2015-07-09  fix DTS2015062509266
*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgRrcMmEstCnf(MsgBlock * pMsg)
{
    LRRC_LMM_EST_CNF_STRU                *pstEstCnfMsg;
    VOS_UINT32                           ulResult;

    NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_PreProcMsgRrcMmEstCnf is entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgRrcMmEstCnf_ENUM,LNAS_ENTRY);

    /* sunbing 00265702 begin for DTS2015100600547 �ػ����������ͷ�*/
    /* delete ���õ���μ�� */
    /* sunbing 00265702 end for DTS2015100600547 �ػ����������ͷ�*/
    /*��齨���Ƿ�ɹ�*/

    pstEstCnfMsg = (VOS_VOID *)pMsg;
    ulResult = pstEstCnfMsg->enResult;

    /*���ⱳ��:������CSFB���̱��û����ٹҶϵ绰����ʱ��CSFB�������̣�
    ���˵�L��ʱ������TA��TALIST���棬���Բ��ᷢ��TAU�����ཻ��������
    ��ʱ������PS���Ѿ���ʼ��2/3GǨ�ƣ������ᵼ�±��в�ͨ�������ղ�������
    �Ķ�:���ӱ�ʶά��ʶ����������ֳ������ڻص�L��ʱ��֤����TAU*/
    /*�����ɹ�һ�����ESR���͵����࣬CONN FAIL ESR���ܷ��ͳɹ�������������
      ���������ñ�־��������ԭ��ֵ��ESRû�з��͵�����࣬����Ҫ��¼*/
    if((EMM_MS_SER_INIT == NAS_LMM_GetEmmCurFsmMS())
      && ((LRRC_EST_SUCCESS == ulResult)
      || (LRRC_EST_EST_CONN_FAIL == ulResult))
      && (PS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
      /*�п������ͷŹ����д�绰�����������Ҫ����*/
      && (NAS_EMM_CONN_WAIT_SYS_INFO != NAS_EMM_GetConnState()))
    {
        NAS_EMM_SetCsfbProcedureFlag(PS_TRUE);
    }

    switch (ulResult)
    {
        case LRRC_EST_SUCCESS:
        case LRRC_EST_PRESENT:
            NAS_EMM_ChangeRrcConnStateToEstSignal();
            NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3412);
            /*֪ͨGUģT3412ֹͣ*/
            NAS_EMM_SendTimerStateNotify(TI_NAS_EMM_PTL_T3412, LMM_MMC_TIMER_STOP);

            NAS_LMM_StopPtlTimer(TI_NAS_EMM_PTL_T3423);

            /*֪ͨGUģT3423ֹͣ*/
            NAS_EMM_SendTimerStateNotify(TI_NAS_EMM_PTL_T3423, LMM_MMC_TIMER_STOP);

            NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF);
            /*NAS_LMM_WriteEpsSecuContext(NAS_NV_ITEM_DELETE);*/
            NAS_EMM_ClearBarResouce();
            NAS_EMM_CcoInterSystemSuccProc();

            /* ����ATTACH�ɹ�����ע��״̬����ΪATTACH�ѷ��͵��������Ӧ */
            if((EMM_MS_REG_INIT == NAS_LMM_GetEmmCurFsmMS())
                &&(EMM_SS_ATTACH_WAIT_CN_ATTACH_CNF ==NAS_LMM_GetEmmCurFsmSS()))
            {
                NAS_EMM_GLO_AD_SetAttClRegStatus(MMC_LMM_CL_REG_STATUS_ATTACH_SEND_WAIT_CN_RSP);
                /* ������: ��¼ATTACH EST SUCCʱ�� */
                NAS_LMM_SaveAttachEstSuccTimeStamp();
            }
            /* ������: ��¼Ser Est Succʱ�� */
            if((EMM_MS_SER_INIT == NAS_LMM_GetEmmCurFsmMS())
                &&(EMM_SS_SER_WAIT_CN_SER_CNF == NAS_LMM_GetEmmCurFsmSS()))
            {
                NAS_EMM_SaveSerEstSuccTimeStamp();
                /* ESR�����ɹ�,֪ͨLRRC CSFB��������,LRRC�յ�����Ϣ���������ʱ��,����ʱ����ʱ֮ǰδ�յ������ͷ�
                   ��Ϣ,LRRC�����ͷ�,���ڽ��CSFB�������಻�·��ض����ͷŵ�����*/
                if(PS_TRUE == NAS_EMM_SER_IsCsfbProcedure())
                {
                    NAS_EMM_SndLrrcLmmCsfbNotify(LRRC_LNAS_CSFB_STATUS_START);
                }
            }

            /* sunbing 00265702 begin for DTS2015100600547 �ػ����������ͷ�*/
            /*�ػ�״̬�£�ֻҪ�����ܵ�detach������ֱ���߹ػ����̣����õ�������ͷ�*/
            if ((EMM_MS_NULL == NAS_LMM_GetEmmCurFsmMS())
              &&(EMM_SS_NULL_WAIT_SWITCH_OFF == NAS_LMM_GetEmmCurFsmSS()))
            {
                /* ֹͣTI_NAS_EMM_PTL_SWITCH_OFF_TIMER */
                NAS_LMM_StopPtlTimer(               TI_NAS_EMM_PTL_SWITCH_OFF_TIMER);

                #if (FEATURE_ON == FEATURE_DSDS)
                /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
                NAS_LMM_SendRrcDsdsEndNotify(LRRC_LNAS_SESSION_TYPE_PS_DETACH);
                #endif

                NAS_EMM_ProcLocalStop();
            }
            /* sunbing 00265702 end for DTS2015100600547 �ػ����������ͷ�*/
            break;

        case LRRC_EST_ESTING:
            NAS_EMM_GIM_WARNING_LOG("MRRC:LRRC_EST_ESTING is ignore!");
            TLPS_PRINT2LAYER_WARNING(NAS_EMM_PreProcMsgRrcMmEstCnf_ENUM,LNAS_FUNCTION_LABEL1);
            NAS_EMM_ChangeRrcConnStateToEsting();
            break;

        default:
            NAS_LMM_StopStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF);

            NAS_EMM_SecuCurrentContextUpNasCountBack();
            #if (FEATURE_PTM == FEATURE_ON)
            NAS_EMM_ProcErrlogEstCnfOrDataCnfFail((VOS_VOID*)pstEstCnfMsg, EMM_OM_ERRLOG_TYPE_EST_CNF_FAIL);
            #endif

            /*��MRRC_CONNECT_FAIL_IND*/
            NAS_EMM_MrrcConnectFailInd(ulResult);
            break;
    }

     return NAS_LMM_MSG_HANDLED;
}


/*****************************************************************************
 Function Name  : NAS_EMM_PreProcMsgTIWaitRrcConnTO
 Discription    : MRRC�ȴ�RRC���ӽ����Ķ�ʱ��TI_NAS_EMM_WAIT_RRC_CONN��ʱ,
                  ��Ϊ����ʧ��,������Դģ�鷢��MRRC_REL_IND��Ϣ
 Input          : ��ϢID,��Ϣ
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968  2008-09-10  Draft Enact
      2.  lifuxin   00253982 2014.10.28  ���������ع�
*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgTIWaitRrcConnTO(MsgBlock * pMsg)
{

    NAS_EMM_PUBU_LOG_INFO("NAS_EMM_PreProcMsgTIWaitRrcConnTO is entered.");
    TLPS_PRINT2LAYER_WARNING(NAS_EMM_PreProcMsgTIWaitRrcConnTO_ENUM,LNAS_ENTRY);

    (VOS_VOID)(pMsg);

    NAS_EMM_SecuCurrentContextUpNasCountBack();

    /*��MRRC_CONNECT_FAIL_IND*/
    NAS_EMM_MrrcConnectFailInd(LRRC_EST_EST_CONN_FAIL);

    if (NAS_EMM_IS_SUSPEND != NAS_EMM_IsSuspended())
    {
        NAS_EMM_RelReq(NAS_LMM_NOT_BARRED);
    }
    else
    {
        NAS_EMM_SetConnState(NAS_EMM_CONN_IDLE);
    }

    return  NAS_LMM_MSG_HANDLED;
}

/*****************************************************************************
 Function Name  : NAS_EMM_IntraEstReq
 Discription    : �յ�public������mrrc est req��Ϣ��,ѹջ,��rrc_mm_est_req
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968  2008-09-10  Draft Enact
      2.  lifuxin   00253982 2014.10.28  ���������ع�
*****************************************************************************/
VOS_VOID NAS_EMM_IntraEstReq(const NAS_EMM_MRRC_DATA_REQ_STRU *pMsg)
{

    /*����RRC_MM_EST_REQ*/
    NAS_EMM_RrcEstReq(pMsg);

    NAS_EMM_ChangeRrcConnStateToEsting();

    /*������ʱ��*/
    NAS_LMM_StartStateTimer(TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF);

    return ;
}

/*****************************************************************************
 Function Name  : NAS_EMM_RrcEstReq
 Discription    : ����RRC_MM_EST_REQ
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968  2008-09-10  Draft Enact
      2.  niezhouyu 00108792  2009-05-20 ʹ���������NAS��ȫ���ԵĴ򿪺͹ر�
      3.  X00148705           2009-10-20 ֱ�ӵ���NAS_EMM_SEND_MSG������Ϣ
      4.  z00148421        2010-03-17  ��ȫģ���ع�:�ı��˼ӱ����ĵ���λ��
*****************************************************************************/
VOS_VOID    NAS_EMM_RrcEstReq(const NAS_EMM_MRRC_DATA_REQ_STRU *pMsg)
{
    LRRC_LMM_EST_REQ_STRU              *pstEstReqMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulEstReqLenNoHeader;

    /* ��¼�տ���Ϣ�����ͣ�����Ϣ����ʧ��ʱ�ж�ʹ��*/
    NAS_LMM_GetLastAirMsgType() = pMsg->stNasMsg.aucNasMsg[NAS_EMM_PLAIN_MSG_TYPE_POS];

    /*���㳤��*/
    ulEstReqLenNoHeader             = (sizeof(LRRC_LMM_EST_REQ_STRU)+
                                    (pMsg->stNasMsg.ulNasMsgSize-NAS_EMM_4BYTES_LEN))-
                                    NAS_EMM_LEN_VOS_MSG_HEADER;
    /* �����ڴ�*/
    pstEstReqMsg = (VOS_VOID *)NAS_LMM_ALLOC_MSG(ulEstReqLenNoHeader + NAS_EMM_LEN_VOS_MSG_HEADER);
    if(NAS_EMM_NULL_PTR == pstEstReqMsg)
    {
        /* ��ӡ�ڴ����ʧ��log */
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_RrcEstReq: Alloc Msg ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_RrcEstReq_ENUM,LNAS_NULL_PTR);
        return;
    }

    /*���VOS��Ϣͷ*/
    NAS_EMM_GIM_RRC_MSG_HEADER(pstEstReqMsg, ulEstReqLenNoHeader);

    /*�����ϢID*/
    pstEstReqMsg->enMsgId    = ID_LRRC_LMM_EST_REQ;

    /*���������ԭ��*/
    pstEstReqMsg->enEstCause = pMsg->enEstCaue;
    pstEstReqMsg->enCallType = pMsg->enCallType;
    /*��� NAS������Ϣ*/

    NAS_LMM_MEM_SET_S(  &(pstEstReqMsg->stEstInfo),
                        sizeof(LRRC_LNAS_EST_INFO_STRU),
                        0,
                        sizeof(LRRC_LNAS_EST_INFO_STRU));

    NAS_EMM_FillEstInfo(pstEstReqMsg, pMsg->enEmmMsgType);

    /*�����Ϣ��*/
    pstEstReqMsg->stFirstNasMsg.ulNasMsgSize = pMsg->stNasMsg.ulNasMsgSize;

    NAS_LMM_MEM_CPY_S(  pstEstReqMsg->stFirstNasMsg.aucNasMsg,
                        pMsg->stNasMsg.ulNasMsgSize,
                        pMsg->stNasMsg.aucNasMsg,
                        pMsg->stNasMsg.ulNasMsgSize);


    /*����RRC_MM_EST_REQ*/
    NAS_LMM_SEND_MSG(pstEstReqMsg);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_FillEstInfo
 Description     : ΪLRRC_LMM_EST_REQ��Ϣ��� EstInfo
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-5-12  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_FillEstInfo(
                                LRRC_LMM_EST_REQ_STRU              *pstEstReqMsg,
                                NAS_EMM_MSG_TYPE_ENUM_UINT32        enEmmMsgType )
{
    NAS_EMM_UEID_STRU                  *pstMmUeId = VOS_NULL_PTR;
    NAS_LMM_NETWORK_INFO_STRU           *pMmNetInfo = VOS_NULL_PTR;
    NAS_MM_TA_STRU                      stCurTa;
    NAS_MM_TA_LIST_STRU                 stTaiList;
    NAS_LMM_GUTI_STRU                    stMappedGuti;
    VOS_UINT32                          ulRslt;

    NAS_LMM_MEM_SET_S(  &stMappedGuti,
                        sizeof(NAS_LMM_GUTI_STRU),
                        0,
                        sizeof(NAS_LMM_GUTI_STRU));

    /*��ȡ UE ��ʶ*/
    pstMmUeId                           = NAS_LMM_GetEmmInfoUeidAddr();

    /*TIN = P-TMSI:
      ������� mapped GUTI,��� mapped GUTI�л�ȡ GUMMEI;
      ��������� mapped GUTI,��Ȳ�Я��S_TMSI,Ҳ��Я��GUMMEI*/
    if(NAS_LMM_SUCC ==  NAS_EMM_CheckMutiModeSupport())
    {
        if (MMC_LMM_TIN_P_TMSI == NAS_EMM_GetTinType())
        {
            if(NAS_EMM_SUCC == NAS_EMM_CheckPtmsiAndRaiValidity())
            {
                NAS_EMM_DeriveMappedGuti(&stMappedGuti);
                pstEstReqMsg->stEstInfo.ucBitOpRegGummei = NAS_EMM_BIT_SLCT;
                pstEstReqMsg->stEstInfo.stRegGummei.ucMmec = stMappedGuti.stMmeCode.ucMmeCode;
                pstEstReqMsg->stEstInfo.stRegGummei.usMmeGi = ((stMappedGuti.stMmeGroupId.ucGroupId<< 8)
                                                      | (stMappedGuti.stMmeGroupId.ucGroupIdCnt));

                if (NAS_RELEASE_CTRL)
                {
                    pstEstReqMsg->stEstInfo.stRegGummei.enGummeiType = LRRC_LNAS_GUMMEI_TYPE_MAPPED;
                }

                NAS_LMM_MEM_CPY_S(  &(pstEstReqMsg->stEstInfo.stRegGummei.stPlmnId),
                                    sizeof(NAS_MM_PLMN_ID_STRU),
                                    &(stMappedGuti.stPlmnId),
                                    sizeof(NAS_MM_PLMN_ID_STRU));

            }

            return;
        }
    }

    /*TIN != P-TMSI*/
    if(NAS_EMM_MSG_LOAD_BALANCING_TAU != enEmmMsgType)
    {
        NAS_LMM_MEM_SET_S(&stTaiList, sizeof(NAS_MM_TA_LIST_STRU), 0, sizeof(NAS_MM_TA_LIST_STRU));
        NAS_LMM_MEM_SET_S(&stCurTa, sizeof(NAS_MM_TA_STRU), 0, sizeof(NAS_MM_TA_STRU));

        pMmNetInfo                          = NAS_LMM_GetEmmInfoNetInfoAddr();

        /*Current TA*/
        NAS_LMM_MEM_CPY_S(  &(stCurTa.stPlmnId),
                            sizeof(NAS_MM_PLMN_ID_STRU),
                            &(pMmNetInfo->stPresentNetId.stPlmnId),
                            sizeof(NAS_MM_PLMN_ID_STRU));
        NAS_LMM_MEM_CPY_S(  &(stCurTa.stTac),
                            sizeof(NAS_MM_TAC_STRU),
                            &(pMmNetInfo->stPresentNetId.stTac),
                            sizeof(NAS_MM_TAC_STRU));
        /*��ȡ�ϴ�ע���TA List*/
        NAS_LMM_MEM_CPY_S(  &(stTaiList),
                            sizeof(NAS_MM_TA_LIST_STRU),
                            &(pMmNetInfo->stTaiList),
                            sizeof(NAS_MM_TA_LIST_STRU));

        ulRslt = NAS_LMM_TaMatchTaList(&stCurTa, &stTaiList);

        /*lint -e701*/

        /*��ǰTA����ע���TA�����ҵ�ǰ���̲���attach����
          (detach֮��û��ɾ��ta list������ta listֻ��ע��̬������Ч��)*/
        if((NAS_LMM_MATCH_SUCCESS == ulRslt)
            && (NAS_EMM_MSG_ATTACH_REQ != enEmmMsgType))
        {
            NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_RrcEstReq:provide S-TMSI to RRC ");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_FillEstInfo_ENUM,LNAS_FUNCTION_LABEL1);
            pstEstReqMsg->stEstInfo.ucBitOpSTmsi = pstMmUeId->bitOpGuti;
            pstEstReqMsg->stEstInfo.stStmsi.ucMmec = pstMmUeId->stGuti.stMmeCode.ucMmeCode;
            pstEstReqMsg->stEstInfo.stStmsi.ulMTmsi = (pstMmUeId->stGuti.stMTmsi.ucMTmsi<<24)
                                            |(pstMmUeId->stGuti.stMTmsi.ucMTmsiCnt1<<16)
                                            |(pstMmUeId->stGuti.stMTmsi.ucMTmsiCnt2<<8)
                                            |(pstMmUeId->stGuti.stMTmsi.ucMTmsiCnt3);

        }
        else
        {
            NAS_EMM_GIM_NORMAL_LOG("NAS_EMM_RrcEstReq:provide GUMMEI to RRC");
            TLPS_PRINT2LAYER_INFO(NAS_EMM_FillEstInfo_ENUM,LNAS_FUNCTION_LABEL2);
            pstEstReqMsg->stEstInfo.ucBitOpRegGummei = pstMmUeId->bitOpGuti;
            pstEstReqMsg->stEstInfo.stRegGummei.ucMmec = pstMmUeId->stGuti.stMmeCode.ucMmeCode;
            pstEstReqMsg->stEstInfo.stRegGummei.usMmeGi = ((pstMmUeId->stGuti.stMmeGroupId.ucGroupId<< 8)
                                                  | (pstMmUeId->stGuti.stMmeGroupId.ucGroupIdCnt));
            if (NAS_RELEASE_CTRL)
            {
                pstEstReqMsg->stEstInfo.stRegGummei.enGummeiType = LRRC_LNAS_GUMMEI_TYPE_NATIVE;
            }

            NAS_LMM_MEM_CPY_S(  &(pstEstReqMsg->stEstInfo.stRegGummei.stPlmnId),
                                sizeof(NAS_MM_PLMN_ID_STRU),
                                &(pstMmUeId->stGuti.stPlmnId),
                                sizeof(NAS_MM_PLMN_ID_STRU));
        }

        /*lint +e701*/


    }
}

/*****************************************************************************
 Function Name  : NAS_EMM_RrcDataReq
 Discription    : ����RRC_MM_DATA_REQ
 Input          :
 Output         : None
 Return         : None
 History:
      1.  zangyalan 57968  2008-09-10  Draft Enact
      2.  X00148705        2009-10-20  ֱ�ӵ���NAS_EMM_SEND_MSG������Ϣ
      3.  z00148421        2010-03-17  ��ȫģ���ع�:�ı��˼ӱ����ĵ���λ��
*****************************************************************************/
VOS_VOID    NAS_EMM_RrcDataReq(         const NAS_EMM_MRRC_DATA_REQ_STRU *pMsg,
                                        VOS_UINT32  ulMmRrcOpId)
{
    LRRC_LMM_DATA_REQ_STRU               *pstDataReqMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRrcMmDataReqMsgLen;

    /* ��¼�տ���Ϣ�����ͣ�����Ϣ����ʧ��ʱ�ж�ʹ��*/
    NAS_LMM_GetLastAirMsgType() = pMsg->stNasMsg.aucNasMsg[NAS_EMM_PLAIN_MSG_TYPE_POS];
    ulRrcMmDataReqMsgLen = (sizeof(LRRC_LMM_DATA_REQ_STRU)+
                           pMsg->stNasMsg.ulNasMsgSize)-
                           NAS_EMM_4BYTES_LEN;

    /*�����ڴ�*/
    pstDataReqMsg   = (VOS_VOID *)NAS_LMM_ALLOC_MSG(ulRrcMmDataReqMsgLen);
    if(NAS_EMM_NULL_PTR == pstDataReqMsg)
    {
        /* ��ӡ�ڴ����ʧ��log */
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_RrcDataReq: NAS_LMM_ALLOC_MSG ERR!");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_RrcDataReq_ENUM,LNAS_NULL_PTR);

        return;
    }

    /*���VOS��Ϣͷ*/
    NAS_EMM_GIM_RRC_MSG_HEADER(pstDataReqMsg,(ulRrcMmDataReqMsgLen-NAS_EMM_LEN_VOS_MSG_HEADER));

    /*�����ϢID*/
    pstDataReqMsg->enMsgId  = ID_LRRC_LMM_DATA_REQ;

    /*���OpId*/
    pstDataReqMsg->ulOpId   = ulMmRrcOpId;

    /*���enDataReqCnf*/
    pstDataReqMsg->enDataCnf = pMsg->enDataCnf;

    /*�����Ϣ�� */
    pstDataReqMsg->stNasMsg.ulNasMsgSize = pMsg->stNasMsg.ulNasMsgSize;

    NAS_LMM_MEM_CPY_S(  pstDataReqMsg->stNasMsg.aucNasMsg,
                        pMsg->stNasMsg.ulNasMsgSize,
                        pMsg->stNasMsg.aucNasMsg,
                        pMsg->stNasMsg.ulNasMsgSize);

    NAS_EMM_GIM_INFO_LOG2("NAS_EMM_RrcDataReq,MmRrcOpId ,enDataCnf ",
                                        ulMmRrcOpId,
                                        pMsg->enDataCnf);
    TLPS_PRINT2LAYER_INFO2(NAS_EMM_RrcDataReq_ENUM,LNAS_FUNCTION_LABEL1,
                                        ulMmRrcOpId,
                                        pMsg->enDataCnf);

    /* ����RRC_MM_DATA_REQ */
    NAS_LMM_SEND_MSG(pstDataReqMsg);

    return;
}

/*****************************************************************************
 Function Name   : NAS_EMM_SaveMrrcDataReqMsg
 Description     : ����Ҫ�������Ϣ���뻺������
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen 00209181 2013-03-29  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_SaveMrrcDataReqMsg
(
    const NAS_EMM_MRRC_DATA_REQ_STRU        *pstMsg,
    VOS_UINT32                              ulMmRrcOpId
)
{
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;



    pEmmMrrcMgmtData = NAS_EMM_GET_MRRC_MGMT_DATA_ADDR();

    if ((pstMsg->stNasMsg.ulNasMsgSize > NAS_LMM_MRRC_NAS_MSG_MAX_LEN)
        || (NAS_EMM_NULL == pstMsg->stNasMsg.ulNasMsgSize))
    {
        NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_SaveMrrcDataReqMsg:NAS MSG LENGTH ERROR!,MaxLen: MsgLen:",
                                NAS_LMM_MRRC_NAS_MSG_MAX_LEN, pstMsg->stNasMsg.ulNasMsgSize);
        TLPS_PRINT2LAYER_INFO2(NAS_EMM_SaveMrrcDataReqMsg_ENUM,LNAS_FUNCTION_LABEL1,
                                NAS_LMM_MRRC_NAS_MSG_MAX_LEN, pstMsg->stNasMsg.ulNasMsgSize);
        return;
    }

    /*TC��Ϣ����¼ */
    if (pstMsg->enEmmMsgType != NAS_EMM_MSG_TC)
    {
        /* ����������Ϣ�����ﵽ���Ի�������ֵ,���������Ϣһ��ǰ��*/
        if (NAS_LMM_RRC_SAVE_MSG_MAX_NUM == g_ulSaveMsgNum)
        {
            /* ����Ϣ����ǰ�ƣ���Ҫ�洢�ķ���ĩβ */
            NAS_LMM_MEM_CPY_S(  pEmmMrrcMgmtData,
                                (sizeof(NAS_EMM_MRRC_MGMT_DATA_STRU))*(NAS_LMM_RRC_SAVE_MSG_MAX_NUM -1),
                                (pEmmMrrcMgmtData+1),
                                (sizeof(NAS_EMM_MRRC_MGMT_DATA_STRU))*(NAS_LMM_RRC_SAVE_MSG_MAX_NUM -1));

            pEmmMrrcMgmtData = (pEmmMrrcMgmtData +  NAS_LMM_RRC_SAVE_MSG_MAX_NUM) -1;
        }
        else
        {
            pEmmMrrcMgmtData = pEmmMrrcMgmtData +  g_ulSaveMsgNum;
        }

        /*����OpId */
        pEmmMrrcMgmtData->ulEsmMmOpId = pstMsg->ulEsmMmOpId;
        NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_SaveMrrcDataReqMsg EmmEsmOpId, RrcLmmOpId",
                                pEmmMrrcMgmtData->ulEsmMmOpId, ulMmRrcOpId);
        TLPS_PRINT2LAYER_INFO2(NAS_EMM_SaveMrrcDataReqMsg_ENUM,LNAS_FUNCTION_LABEL2,
                                pEmmMrrcMgmtData->ulEsmMmOpId, ulMmRrcOpId);

        pEmmMrrcMgmtData->ulMmRrcOpId = ulMmRrcOpId;
        #if (FEATURE_LPP == FEATURE_ON)
        pEmmMrrcMgmtData->ulEmmLppOrSsOpId  = pstMsg->ulEmmLppOrSsOpId;
        pEmmMrrcMgmtData->ulLppSsFlag       = pstMsg->ulLppSsFlag;
        #endif

        /*����NAS�տ���ϢID�Լ����� */
        pEmmMrrcMgmtData->enLastMsgId = pstMsg->enEmmMsgType;

        pEmmMrrcMgmtData->ulNasMsgLength = pstMsg->stNasMsg.ulNasMsgSize;

        NAS_LMM_MEM_CPY_S(  pEmmMrrcMgmtData->aucNasMsgContent,
                            NAS_LMM_MRRC_NAS_MSG_MAX_LEN,
                            pstMsg->stNasMsg.aucNasMsg,
                            pstMsg->stNasMsg.ulNasMsgSize);

        if (NAS_LMM_RRC_SAVE_MSG_MAX_NUM != g_ulSaveMsgNum)
        {
            g_ulSaveMsgNum ++;
        }

        NAS_EMM_PUBU_LOG2_INFO(      "NAS_EMM_SaveMrrcDataReqMsg,MmRrcOpId , enEmmMsgType",
                            ulMmRrcOpId, pstMsg->enEmmMsgType);
        TLPS_PRINT2LAYER_INFO2(NAS_EMM_SaveMrrcDataReqMsg_ENUM,LNAS_FUNCTION_LABEL3,
                            ulMmRrcOpId, pstMsg->enEmmMsgType);

        NAS_EMM_PUBU_LOG1_INFO(      "NAS_EMM_SaveMrrcDataReqMsg,g_ulSaveMsgNum =",
                            g_ulSaveMsgNum);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_SaveMrrcDataReqMsg_ENUM,LNAS_FUNCTION_LABEL4,
                            g_ulSaveMsgNum);

    }
    return;
}

VOS_VOID  NAS_EMM_MrrcMgmtDataInit( VOS_VOID )
{
    VOS_UINT32                           ulIndex = 0;

    for (ulIndex = 0; ulIndex < NAS_LMM_RRC_SAVE_MSG_MAX_NUM; ulIndex++)
    {
        g_stEmmMrrcMgmtData[ulIndex].ulMmRrcOpId = NAS_LMM_RRC_OPID_NOT_VAILID;
        g_stEmmMrrcMgmtData[ulIndex].ulEsmMmOpId = NAS_LMM_OPID;
        g_stEmmMrrcMgmtData[ulIndex].enLastMsgId = NAS_EMM_CN_MT_BUTT;
        g_stEmmMrrcMgmtData[ulIndex].ulNasMsgLength = NAS_EMM_NULL;
        g_stEmmMrrcMgmtData[ulIndex].ulHoWaitSysInfoFlag = VOS_FALSE;
        /* ���NO RF����ֱ���ش���־ */
        g_stEmmMrrcMgmtData[ulIndex].ulNoRfWaitSysInfoFlag = VOS_FALSE;
        g_stEmmMrrcMgmtData[ulIndex].ulConnRelWaitSysInfoFlag = VOS_FALSE;
        g_stEmmMrrcMgmtData[ulIndex].ulIsEsmMsgEmcType        = VOS_FALSE;

        NAS_LMM_MEM_SET_S(  g_stEmmMrrcMgmtData[ulIndex].aucNasMsgContent,
                            NAS_LMM_MRRC_NAS_MSG_MAX_LEN,
                            NAS_EMM_NULL,
                            NAS_LMM_MRRC_NAS_MSG_MAX_LEN);
    }

    g_ulSaveMsgNum = 0;

}


VOS_UINT32  NAS_EMM_MrrcAllocMmRrcOpId( VOS_VOID )
{
    gulMmRrcOpId++;
    if(gulMmRrcOpId                     == NAS_LMM_RRC_OPID_NOT_VAILID)
    {
        gulMmRrcOpId                    = 0;
    }
    return(                             gulMmRrcOpId);
}

/*****************************************************************************
 Function Name   : NAS_EMM_FindMsgInDataReqBuffer
 Description     : ����DATA CNFЯ����OPID�����ڻ�����Ϣ�ڴ��ж�Ӧ����Ϣ
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         : wangchen  00209181   2013-03-30  Draft Enact

*****************************************************************************/
NAS_EMM_MRRC_MGMT_DATA_STRU* NAS_EMM_FindMsgInDataReqBuffer(VOS_UINT32 ulOpId)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulRslt = NAS_EMM_FAIL;
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;

    pEmmMrrcMgmtData = NAS_EMM_GET_MRRC_MGMT_DATA_ADDR();

    for (ulIndex = 0; ulIndex <g_ulSaveMsgNum; ulIndex++)
    {
        if (ulOpId == pEmmMrrcMgmtData->ulMmRrcOpId)
        {
            ulRslt = NAS_EMM_SUCC;
            break;
        }
        else
        {
            pEmmMrrcMgmtData++;
        }
    }
    if (NAS_EMM_FAIL == ulRslt)
    {
        return NAS_EMM_NULL_PTR;
    }
    return pEmmMrrcMgmtData;
}


/*****************************************************************************
 Function Name   : NAS_EMM_ClrDataReqBufferMsg
 Description     : �������������Ϣ,���������Ϣ����ǰ��
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen  00209181    2013-04-01  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ClrDataReqBufferMsg
(
    VOS_UINT32                          ulMmRrcOpId
)
{
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulRrcMmDataReqMsgLen;
    VOS_UINT32                          ulLogIndex;

    NAS_EMM_PUBU_LOG1_INFO(      "NAS_EMM_ClrDataReqBufferMsg,g_ulSaveMsgNum =",
                            g_ulSaveMsgNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrDataReqBufferMsg_ENUM,LNAS_FUNCTION_LABEL1,
                            g_ulSaveMsgNum);

    pEmmMrrcMgmtData = NAS_EMM_GET_MRRC_MGMT_DATA_ADDR();

    for (ulIndex = 0; ulIndex < g_ulSaveMsgNum; ulIndex++)
    {
        if (ulMmRrcOpId == pEmmMrrcMgmtData->ulMmRrcOpId)
        {
            /* �����ǰ�Ѿ��洢6��������Ҫɾ���Ĳ��Ƿ��������ĩβ��
            ��Ҫ��Ϣǰ�ƣ�����ĩβ����Ϣ��� */
            if ((g_ulSaveMsgNum - 1)!=ulIndex)
            {
                ulRrcMmDataReqMsgLen = (sizeof(NAS_EMM_MRRC_MGMT_DATA_STRU))*(g_ulSaveMsgNum - (ulIndex+1));

                NAS_LMM_MEM_CPY_S(  pEmmMrrcMgmtData,
                                    ulRrcMmDataReqMsgLen,
                                    (pEmmMrrcMgmtData+1),
                                    ulRrcMmDataReqMsgLen);
            }

            /* ����ǰָ��ָ�򻺴������ĩβ */
            pEmmMrrcMgmtData = pEmmMrrcMgmtData + (g_ulSaveMsgNum - (ulIndex+1));

            pEmmMrrcMgmtData->enLastMsgId = NAS_EMM_CN_MT_BUTT;
            pEmmMrrcMgmtData->ulEsmMmOpId = NAS_LMM_OPID;
            pEmmMrrcMgmtData->ulMmRrcOpId = NAS_LMM_RRC_OPID_NOT_VAILID;
            pEmmMrrcMgmtData->ulHoWaitSysInfoFlag = VOS_FALSE;
            /* �����־ */
            pEmmMrrcMgmtData->ulNoRfWaitSysInfoFlag = VOS_FALSE;
            pEmmMrrcMgmtData->ulConnRelWaitSysInfoFlag = VOS_FALSE;
            pEmmMrrcMgmtData->ulIsEsmMsgEmcType        = VOS_FALSE;
            pEmmMrrcMgmtData->ulNasMsgLength = NAS_EMM_NULL;

            NAS_LMM_MEM_SET_S(  pEmmMrrcMgmtData->aucNasMsgContent,
                                NAS_LMM_MRRC_NAS_MSG_MAX_LEN,
                                NAS_EMM_NULL,
                                NAS_LMM_MRRC_NAS_MSG_MAX_LEN);

            g_ulSaveMsgNum--;


            NAS_EMM_PUBU_LOG1_INFO(      "NAS_EMM_ClrDataReqBufferMsg,g_ulSaveMsgNum =",
                                    g_ulSaveMsgNum);
            TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrDataReqBufferMsg_ENUM,LNAS_FUNCTION_LABEL2,
                                    g_ulSaveMsgNum);

            for (ulLogIndex = 0; ulLogIndex < g_ulSaveMsgNum; ulLogIndex++)
            {
                NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrDataReqBufferMsg,g_stEmmMrrcMgmtData[].enLastMsgId =",
                                       g_stEmmMrrcMgmtData[ulLogIndex].enLastMsgId);
                TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrDataReqBufferMsg_ENUM,LNAS_FUNCTION_LABEL3,
                                       g_stEmmMrrcMgmtData[ulLogIndex].enLastMsgId);

                NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrDataReqBufferMsg,g_stEmmMrrcMgmtData[].ulMmRrcOpId =",
                                       g_stEmmMrrcMgmtData[ulLogIndex].ulMmRrcOpId);
                TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrDataReqBufferMsg_ENUM,LNAS_FUNCTION_LABEL4,
                                       g_stEmmMrrcMgmtData[ulLogIndex].ulMmRrcOpId);

                NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrDataReqBufferMsg,g_stEmmMrrcMgmtData[].ulHoWaitSysInfoFlag =",
                                       g_stEmmMrrcMgmtData[ulLogIndex].ulHoWaitSysInfoFlag);
                TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrDataReqBufferMsg_ENUM,LNAS_FUNCTION_LABEL5,
                                       g_stEmmMrrcMgmtData[ulLogIndex].ulHoWaitSysInfoFlag);
            }


            return;
        }
        pEmmMrrcMgmtData++;
    }
    return;
}
/*****************************************************************************
 Function Name   : NAS_EMM_ClrHoWaitSysInfoBufferMsg
 Description     : ���HoWaitSysInfo��ʶ���ڵĻ�����Ϣ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen  00209181    2013-04-01  Draft Enact
    2.leixiantiao 00258641  2015-02-04
*****************************************************************************/
VOS_UINT32  NAS_EMM_ClrWaitSysInfoBufferMsg( VOS_VOID )
{
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulCurSaveNum;
    VOS_UINT32                          ulRslt = NAS_EMM_FAIL;
    VOS_UINT32                          ulRrcMmDataReqMsgLen;

    NAS_EMM_PUBU_LOG1_INFO(      "NAS_EMM_ClrHoWaitSysInfoBufferMsg,g_ulSaveMsgNum =",
                            g_ulSaveMsgNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrWaitSysInfoBufferMsg_ENUM,LNAS_FUNCTION_LABEL1,
                            g_ulSaveMsgNum);

    ulCurSaveNum = g_ulSaveMsgNum;

    pEmmMrrcMgmtData = NAS_EMM_GET_MRRC_MGMT_DATA_ADDR();

    for (ulIndex = 0; ulIndex < ulCurSaveNum; ulIndex++)
    {
        if ((VOS_TRUE == pEmmMrrcMgmtData->ulHoWaitSysInfoFlag)
            || (VOS_TRUE == pEmmMrrcMgmtData->ulNoRfWaitSysInfoFlag)
            || (VOS_TRUE == pEmmMrrcMgmtData->ulConnRelWaitSysInfoFlag))
        {
#if (FEATURE_LPP == FEATURE_ON)
            if ((VOS_TRUE == pEmmMrrcMgmtData->ulHoWaitSysInfoFlag)
                && (NAS_EMM_NAS_UPLINK_GENERIC_NAS_TRANSPORT == pEmmMrrcMgmtData->enLastMsgId))
            {
                if (0 == pEmmMrrcMgmtData->ulLppSsFlag)
                {
                    NAS_EMM_SendLppDataCnf( LMM_LPP_SEND_RSLT_LOW_LAYER_FAIL,
                                            pEmmMrrcMgmtData->ulEmmLppOrSsOpId);
                }
                else
                {
                    NAS_EMM_SndLcsDataCnf(   LMM_LCS_SEND_RSLT_FAIL_LOW_LAYER,
                                            pEmmMrrcMgmtData->ulEmmLppOrSsOpId);
                }
            }
#endif

            /* �����ǰ�Ѿ��洢6��������Ҫɾ�����Ƿ��������ĩβ��
            ����Ҫ��Ϣǰ�ƣ�ֱ��ɾ������*/
            if ((ulCurSaveNum - 1)!=ulIndex)
            {
                ulRrcMmDataReqMsgLen = (sizeof(NAS_EMM_MRRC_MGMT_DATA_STRU))*(ulCurSaveNum - (ulIndex+1));

                NAS_LMM_MEM_CPY_S(  pEmmMrrcMgmtData,
                                    ulRrcMmDataReqMsgLen,
                                    (pEmmMrrcMgmtData+1),
                                    ulRrcMmDataReqMsgLen);
            }
            /* ����ǰָ��ָ�򻺴������ĩβ */
            pEmmMrrcMgmtData = pEmmMrrcMgmtData + (ulCurSaveNum - (ulIndex+1));

            pEmmMrrcMgmtData->enLastMsgId = NAS_EMM_CN_MT_BUTT;
            pEmmMrrcMgmtData->ulEsmMmOpId = NAS_LMM_OPID;
            pEmmMrrcMgmtData->ulMmRrcOpId = NAS_LMM_RRC_OPID_NOT_VAILID;
            pEmmMrrcMgmtData->ulHoWaitSysInfoFlag = VOS_FALSE;
            /* ���NO RF����ֱ���ش���־ */
            pEmmMrrcMgmtData->ulNoRfWaitSysInfoFlag = VOS_FALSE;
            pEmmMrrcMgmtData->ulConnRelWaitSysInfoFlag = VOS_FALSE;
            pEmmMrrcMgmtData->ulIsEsmMsgEmcType        = VOS_FALSE;
            pEmmMrrcMgmtData->ulNasMsgLength = NAS_EMM_NULL;

            NAS_LMM_MEM_SET_S(  pEmmMrrcMgmtData->aucNasMsgContent,
                                NAS_LMM_MRRC_NAS_MSG_MAX_LEN,
                                NAS_EMM_NULL,
                                NAS_LMM_MRRC_NAS_MSG_MAX_LEN);

            pEmmMrrcMgmtData = pEmmMrrcMgmtData - (ulCurSaveNum - (ulIndex+1));

            g_ulSaveMsgNum--;

            ulRslt = NAS_EMM_SUCC;

        }
        else
        {
            pEmmMrrcMgmtData++;
        }

    }

    NAS_EMM_PUBU_LOG1_INFO(      "NAS_EMM_ClrHoWaitSysInfoBufferMsg,g_ulSaveMsgNum =",
                            g_ulSaveMsgNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrWaitSysInfoBufferMsg_ENUM,LNAS_FUNCTION_LABEL2,
                            g_ulSaveMsgNum);

    for (ulIndex = 0; ulIndex < g_ulSaveMsgNum; ulIndex++)
    {
        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrHoWaitSysInfoBufferMsg,g_stEmmMrrcMgmtData[].enLastMsgId =",
                               g_stEmmMrrcMgmtData[ulIndex].enLastMsgId);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrWaitSysInfoBufferMsg_ENUM,LNAS_FUNCTION_LABEL3,
                               g_stEmmMrrcMgmtData[ulIndex].enLastMsgId);

        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrHoWaitSysInfoBufferMsg,g_stEmmMrrcMgmtData[].ulMmRrcOpId =",
                               g_stEmmMrrcMgmtData[ulIndex].ulMmRrcOpId);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrWaitSysInfoBufferMsg_ENUM,LNAS_FUNCTION_LABEL4,
                               g_stEmmMrrcMgmtData[ulIndex].ulMmRrcOpId);

        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrHoWaitSysInfoBufferMsg,g_stEmmMrrcMgmtData[].ulHoWaitSysInfoFlag =",
                               g_stEmmMrrcMgmtData[ulIndex].ulHoWaitSysInfoFlag);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrWaitSysInfoBufferMsg_ENUM,LNAS_FUNCTION_LABEL5,
                               g_stEmmMrrcMgmtData[ulIndex].ulHoWaitSysInfoFlag);
    }

    return ulRslt;
}

/*****************************************************************************
 Function Name   : NAS_EMM_ClrAllUlDataReqBufferMsg
 Description     : ������л�����Ϣ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen  00209181    2013-04-01  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ClrAllUlDataReqBufferMsg( VOS_VOID )
{
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulIndex;

    NAS_EMM_PUBU_LOG1_INFO(      "NAS_EMM_ClrAllUlDataReqBufferMsg,g_ulSaveMsgNum =",
                            g_ulSaveMsgNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrAllUlDataReqBufferMsg_ENUM,LNAS_FUNCTION_LABEL1,
                            g_ulSaveMsgNum);

    pEmmMrrcMgmtData                    = NAS_EMM_GET_MRRC_MGMT_DATA_ADDR();

    for (ulIndex = 0; ulIndex < g_ulSaveMsgNum; ++ulIndex)
    {
        pEmmMrrcMgmtData->enLastMsgId = NAS_EMM_CN_MT_BUTT;
        pEmmMrrcMgmtData->ulEsmMmOpId = NAS_LMM_OPID;
        pEmmMrrcMgmtData->ulMmRrcOpId = NAS_LMM_RRC_OPID_NOT_VAILID;
        pEmmMrrcMgmtData->ulHoWaitSysInfoFlag = VOS_FALSE;
        /* ���NO RF����ֱ���ش���־ */
        pEmmMrrcMgmtData->ulNoRfWaitSysInfoFlag = VOS_FALSE;
        pEmmMrrcMgmtData->ulConnRelWaitSysInfoFlag = VOS_FALSE;
        pEmmMrrcMgmtData->ulIsEsmMsgEmcType        = VOS_FALSE;
        pEmmMrrcMgmtData->ulNasMsgLength = NAS_EMM_NULL;

        NAS_LMM_MEM_SET_S(  pEmmMrrcMgmtData->aucNasMsgContent,
                            NAS_LMM_MRRC_NAS_MSG_MAX_LEN,
                            NAS_EMM_NULL,
                            NAS_LMM_MRRC_NAS_MSG_MAX_LEN);
    }
    g_ulSaveMsgNum = 0;

    NAS_EMM_PUBU_LOG1_INFO(      "NAS_EMM_ClrAllUlDataReqBufferMsg,g_ulSaveMsgNum =",
                            g_ulSaveMsgNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrAllUlDataReqBufferMsg_ENUM,LNAS_FUNCTION_LABEL2,
                            g_ulSaveMsgNum);
}
/*****************************************************************************
 Function Name   : NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc
 Description     : �����ȥDETACH ACP��Ϣ������л�����Ϣ
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.wangchen  00209181    2013-04-01  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc( VOS_VOID )
{
    NAS_EMM_MRRC_MGMT_DATA_STRU         *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulCurSaveNum;
    VOS_UINT32                          ulRrcMmDataReqMsgLen;

    NAS_EMM_PUBU_LOG1_INFO(      "NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc,g_ulSaveMsgNum =",
                            g_ulSaveMsgNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc_ENUM,LNAS_FUNCTION_LABEL1,
                            g_ulSaveMsgNum);

    ulCurSaveNum = g_ulSaveMsgNum;

    pEmmMrrcMgmtData = NAS_EMM_GET_MRRC_MGMT_DATA_ADDR();

    for (ulIndex = 0; ulIndex < ulCurSaveNum; ulIndex++)
    {
        if (NAS_EMM_MSG_DETACH_ACP != pEmmMrrcMgmtData->enLastMsgId)
        {
            /* �����ǰ�Ѿ��洢6��������Ҫɾ�����Ƿ��������ĩβ��
            ����Ҫ��Ϣǰ�ƣ�ֱ��ɾ������*/
            if ((ulCurSaveNum - 1)!=ulIndex)
            {
                ulRrcMmDataReqMsgLen = (sizeof(NAS_EMM_MRRC_MGMT_DATA_STRU))*(ulCurSaveNum - (ulIndex+1));

                NAS_LMM_MEM_CPY_S(  pEmmMrrcMgmtData,
                                    ulRrcMmDataReqMsgLen,
                                    (pEmmMrrcMgmtData+1),
                                    ulRrcMmDataReqMsgLen);
            }
            /* ����ǰָ��ָ�򻺴������ĩβ */
            pEmmMrrcMgmtData = pEmmMrrcMgmtData + (ulCurSaveNum - (ulIndex+1));

            pEmmMrrcMgmtData->enLastMsgId = NAS_EMM_CN_MT_BUTT;
            pEmmMrrcMgmtData->ulEsmMmOpId = NAS_LMM_OPID;
            pEmmMrrcMgmtData->ulMmRrcOpId = NAS_LMM_RRC_OPID_NOT_VAILID;
            pEmmMrrcMgmtData->ulHoWaitSysInfoFlag = VOS_FALSE;
            /* ���NO RF����ֱ���ش���־ */
            pEmmMrrcMgmtData->ulNoRfWaitSysInfoFlag = VOS_FALSE;
            pEmmMrrcMgmtData->ulConnRelWaitSysInfoFlag = VOS_FALSE;
            pEmmMrrcMgmtData->ulIsEsmMsgEmcType        = VOS_FALSE;
            pEmmMrrcMgmtData->ulNasMsgLength = NAS_EMM_NULL;

            NAS_LMM_MEM_SET_S(  pEmmMrrcMgmtData->aucNasMsgContent,
                                NAS_LMM_MRRC_NAS_MSG_MAX_LEN,
                                NAS_EMM_NULL,
                                NAS_LMM_MRRC_NAS_MSG_MAX_LEN);

            pEmmMrrcMgmtData = pEmmMrrcMgmtData - (ulCurSaveNum - (ulIndex+1));

            g_ulSaveMsgNum--;

        }
        else
        {
            pEmmMrrcMgmtData++;
        }

    }
    NAS_EMM_PUBU_LOG1_INFO(      "NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc,g_ulSaveMsgNum =",
                            g_ulSaveMsgNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc_ENUM,LNAS_FUNCTION_LABEL2,
                            g_ulSaveMsgNum);

    for (ulIndex = 0; ulIndex < g_ulSaveMsgNum; ulIndex++)
    {
        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc,g_stEmmMrrcMgmtData[].enLastMsgId =",
                               g_stEmmMrrcMgmtData[ulIndex].enLastMsgId);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc_ENUM,LNAS_FUNCTION_LABEL3,
                                g_stEmmMrrcMgmtData[ulIndex].enLastMsgId);

        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc,g_stEmmMrrcMgmtData[].ulMmRrcOpId =",
                               g_stEmmMrrcMgmtData[ulIndex].ulMmRrcOpId);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc_ENUM,LNAS_FUNCTION_LABEL4,
                               g_stEmmMrrcMgmtData[ulIndex].ulMmRrcOpId);

        NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc,g_stEmmMrrcMgmtData[].ulHoWaitSysInfoFlag =",
                               g_stEmmMrrcMgmtData[ulIndex].ulHoWaitSysInfoFlag);
        TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrAllUlDataReqBufferMsgExceptMtDetachAcc_ENUM,LNAS_FUNCTION_LABEL5,
                               g_stEmmMrrcMgmtData[ulIndex].ulHoWaitSysInfoFlag);
    }

    return;
}


/*****************************************************************************
 Function Name   : NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg
 Description     : ��RRC����REL_IND֮ǰ������ֱ��������·�ͷŶ�����ʧ�ܵ���Ϣ����Ҫ���յ�ϵͳ��Ϣ�����ط���
                   ����յ�REL_INDʱ������Щ������Ϣɾ��
 Input           : None
 Output          : None
 Return          : VOS_VOID

 History         :
    1.chengmin 00285307    2015-09-01  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg( VOS_VOID )
{
    NAS_EMM_MRRC_MGMT_DATA_STRU        *pEmmMrrcMgmtData = NAS_EMM_NULL_PTR;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulCurSaveNum;
    VOS_UINT32                          ulRrcMmDataReqMsgLen;

    ulCurSaveNum = g_ulSaveMsgNum;

    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg,g_ulSaveMsgNum =",
                            g_ulSaveMsgNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg_ENUM,LNAS_FUNCTION_LABEL1,
                            g_ulSaveMsgNum);

    pEmmMrrcMgmtData = NAS_EMM_GET_MRRC_MGMT_DATA_ADDR();

    for (ulIndex = 0; ulIndex < ulCurSaveNum; ulIndex++)
    {
        if (VOS_TRUE != pEmmMrrcMgmtData->ulConnRelWaitSysInfoFlag)
        {
            /* �����ǰ�Ѿ��洢6��������Ҫɾ�����Ƿ��������ĩβ��
            ����Ҫ��Ϣǰ�ƣ�ֱ��ɾ������*/
            if ((ulCurSaveNum - 1)!=ulIndex)
            {
                ulRrcMmDataReqMsgLen = (sizeof(NAS_EMM_MRRC_MGMT_DATA_STRU))*(ulCurSaveNum - (ulIndex+1));

                NAS_LMM_MEM_CPY_S(  pEmmMrrcMgmtData,
                                    ulRrcMmDataReqMsgLen,
                                    (pEmmMrrcMgmtData+1),
                                    ulRrcMmDataReqMsgLen);
            }
            /* ����ǰָ��ָ�򻺴������ĩβ */
            pEmmMrrcMgmtData = pEmmMrrcMgmtData + (ulCurSaveNum - (ulIndex+1));

            pEmmMrrcMgmtData->enLastMsgId                   = NAS_EMM_CN_MT_BUTT;
            pEmmMrrcMgmtData->ulEsmMmOpId                   = NAS_LMM_OPID;
            pEmmMrrcMgmtData->ulMmRrcOpId                   = NAS_LMM_RRC_OPID_NOT_VAILID;
            pEmmMrrcMgmtData->ulHoWaitSysInfoFlag           = VOS_FALSE;
            pEmmMrrcMgmtData->ulNoRfWaitSysInfoFlag         = VOS_FALSE;
            pEmmMrrcMgmtData->ulConnRelWaitSysInfoFlag      = VOS_FALSE;
            pEmmMrrcMgmtData->ulIsEsmMsgEmcType             = VOS_FALSE;
            pEmmMrrcMgmtData->ulNasMsgLength                = NAS_EMM_NULL;

            NAS_LMM_MEM_SET_S(  pEmmMrrcMgmtData->aucNasMsgContent,
                                NAS_LMM_MRRC_NAS_MSG_MAX_LEN,
                                NAS_EMM_NULL,
                                NAS_LMM_MRRC_NAS_MSG_MAX_LEN);

            pEmmMrrcMgmtData = pEmmMrrcMgmtData - (ulCurSaveNum - (ulIndex+1));

            g_ulSaveMsgNum--;

        }
        else
        {
            pEmmMrrcMgmtData++;
        }

    }


    /* ��ӡ�����еĹؼ����� */
    NAS_EMM_PUBU_LOG1_INFO("NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg,g_ulSaveMsgNum =",
                            g_ulSaveMsgNum);
    TLPS_PRINT2LAYER_INFO1(NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg_ENUM,LNAS_FUNCTION_LABEL2,
                            g_ulSaveMsgNum);

    for (ulIndex = 0; ulIndex < g_ulSaveMsgNum; ulIndex++)
    {
        NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg,enLastMsgId,ulMmRrcOpId:",
                               g_stEmmMrrcMgmtData[ulIndex].enLastMsgId, g_stEmmMrrcMgmtData[ulIndex].ulMmRrcOpId);
        TLPS_PRINT2LAYER_INFO2(NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg_ENUM,LNAS_FUNCTION_LABEL3,
                                g_stEmmMrrcMgmtData[ulIndex].enLastMsgId, g_stEmmMrrcMgmtData[ulIndex].ulMmRrcOpId);

        NAS_EMM_PUBU_LOG2_INFO("NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg,ulConnRelWaitSysInfoFlag,ulIsEsmMsgEmcType:",
                               g_stEmmMrrcMgmtData[ulIndex].ulConnRelWaitSysInfoFlag, g_stEmmMrrcMgmtData[ulIndex].ulIsEsmMsgEmcType);
        TLPS_PRINT2LAYER_INFO2(NAS_EMM_ClrAllUlDataReqBufferMsgExceptConnRelWaitSysInfoMsg_ENUM,LNAS_FUNCTION_LABEL4,
                               g_stEmmMrrcMgmtData[ulIndex].ulConnRelWaitSysInfoFlag, g_stEmmMrrcMgmtData[ulIndex].ulIsEsmMsgEmcType);
    }
}




/*lint +e961*/
/*lint +e960*/
/*****************************************************************************
 Function Name   : NAS_EMM_PreProcMsgRabmDrbSetupInd
 Description     : �յ�ID_EMM_ERABM_DRB_SETUP_IND��֪ͨMMC������������̬,
                   Ȼ���ٽ���״̬������
 Input           : None
 Output          : None
 Return          : VOS_UINT32

 History         :
    1.zhengjunyan 00148421      2011-5-9  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_EMM_PreProcMsgRabmDrbSetupInd( MsgBlock * pMsg )
{
    (VOS_VOID)pMsg;
    NAS_EMM_GIM_INFO_LOG("NAS_EMM_PreProcMsgRabmDrbSetupInd entered.");
    TLPS_PRINT2LAYER_INFO(NAS_EMM_PreProcMsgRabmDrbSetupInd_ENUM,LNAS_ENTRY);

    if(NAS_EMM_CONN_RELEASING == NAS_EMM_GetConnState())
    {
        return NAS_LMM_MSG_HANDLED;
    }
    else
    {
        NAS_LMM_StopStateTimer(TI_NAS_EMM_STATE_T3440);
    }

    /* ���ڸñ������ڷ�ֹ����NAS��������̬��RRC����IDLE̬�����, ����DRB�����ɹ�ʱ�������,
       �ñ�����Reg Update_MM��Limit Service��Normal Service�·�IDLE̬��������յ�ERABM��DRBRESET_REQʱ���ۼ� */
    g_ucConnStateRcvDrbReestTimes = 0;

    /*������,ֻ��RRC��·Ϊ��������̬ʱ,����·״̬�л�����������̬ */
    if (NAS_EMM_NO == NAS_LMM_IsRrcConnectStatusIdle())
    {
        NAS_EMM_ChangeRrcConnStateToEstData();
    }
    else
    {
        NAS_EMM_GIM_ERROR_LOG("NAS_EMM_PreProcMsgRabmDrbSetupInd: idle.");
        TLPS_PRINT2LAYER_ERROR(NAS_EMM_PreProcMsgRabmDrbSetupInd_ENUM,LNAS_FUNCTION_LABEL1);
    }

    return NAS_LMM_MSG_DISCARD;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


/* end of ��ϵͳ+ģ��+�ļ���.c */
