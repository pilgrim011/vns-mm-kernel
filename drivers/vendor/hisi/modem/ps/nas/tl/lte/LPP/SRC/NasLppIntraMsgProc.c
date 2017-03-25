/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasLppIntraMsgProc.c
  �� �� ��   : ����
  ��    ��   : XiaoJun
  ��������   : 2015��7��30��
  ����޸�   :
  ��������   : LPP ģ����ڲ���Ϣ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��7��30��
    ��    ��   : XiaoJun
    �޸�����   : �����ļ�

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "NasLppPublic.h"
#include  "NasLppSendMsg.h"
#include  "NasLppIntraInterface.h"
#include  "NasLppOm.h"

#if (FEATURE_LPP == FEATURE_ON)
extern LPP_UPLINK_MSG_BUF_STRU*  NAS_LPP_GetLppMsgUpBuffByOpId
(
    VOS_UINT32              ulLmmLppOpId
);
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#define    THIS_FILE_ID            PS_FILE_ID_NASLPPINTRAMSGPROC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPINTRAMSGPROC_C


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 Function Name   : NAS_LPP_ReleaseTransactionOrSession
 Description     : �ͷ�transaction����session���߼�
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.lifuxin 00253982      2015-10-22  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_ReleaseTransactionOrSession
(
    VOS_UINT8                       ucSessionIndx,
    VOS_UINT8                       ucSessionTransIndx,
    NAS_LPP_TRANS_ID_STRU          *pstTransId
)
{
    if( PS_FALSE == NAS_LPP_IsThereOtherTransactionRunningInSession(ucSessionIndx, pstTransId) )
    {
        NAS_LPP_WARN_LOG("NAS_LPP_ReleaseTransactionOrSession:No running transaction, Release this session!");
        TLPS_PRINT2LAYER_WARNING(NAS_LPP_ReleaseTransactionOrSession_ENUM, LNAS_LPP_NoRunningTransReleaseSession);
        NAS_LPP_ReleaseSessionEntityByIndex(ucSessionIndx);
    }
    else
    {
        NAS_LPP_WARN_LOG("NAS_LPP_ReleaseTransactionOrSession: Have other transaction, Just release this Transaction!");
        TLPS_PRINT2LAYER_WARNING(NAS_LPP_ReleaseTransactionOrSession_ENUM, LNAS_LPP_HaveOtherTransJustReleaseThisTrans);
        NAS_LPP_ReleaseTransEntity(ucSessionIndx, ucSessionTransIndx);
    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_LPP_RcvIntraDataCnf
 Description     : �����ڲ�data cnf��Ϣ
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-20  Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LPP_RcvIntraDataCnf( NAS_LPP_INTRA_DATA_CNF_STRU *pRcvMsg)
{
    NAS_LPP_TRANSACTION_ELEMENT_ENTITY_STRU    *pstTransEntity;
    VOS_UINT8                                   ucSessionIndex = PS_NULL_UINT8;
    VOS_UINT8                                   ucSessionTransIndx = PS_NULL_UINT8;
    NAS_LPP_SUB_STATE_ENUM_UINT32 enSubState;
    LPP_UPLINK_MSG_BUF_STRU  *pstUplinkMsgBuff = NAS_LPP_NULL_PTR;

    NAS_LPP_NORM_LOG("NAS_LPP_RcvIntraDataCnf enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_Func_Enter);

    NAS_LPP_OmIntraDataCnf(pRcvMsg);

    ucSessionIndex = NAS_LPP_SearchSessionIndx(pRcvMsg->stLppMsgIdentity.ulSessionId);
    if (ucSessionIndex >= NAS_LPP_MAX_SESSION_COUNT)
    {
        NAS_LPP_NORM_LOG("NAS_LPP_RcvIntraDataCnf: can't find the session !");
        TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_CanntFindSession);
        return;
    }

    /*����������Ӧ��SESSION��TRANSACTION*/
    pstTransEntity = NAS_LPP_SearchTransEntity(pRcvMsg->stLppMsgIdentity.ulSessionId,
                                             &(pRcvMsg->stLppMsgIdentity.stTransId),
                                              &ucSessionTransIndx);
    if(NAS_LPP_NULL_PTR == pstTransEntity)
    {
        /* ���յ���ͻ��Ϣʱ(�������ݳ�ͻ)�����������ظ�ACK�����������ʱ��û�д���transaction��ֻ�ͷŻ�����Ϣ�ռ� */
        pstUplinkMsgBuff = NAS_LPP_GetLppMsgUpBuffByOpId(pRcvMsg->ulOpId);
        if(NAS_LPP_NULL_PTR == pstUplinkMsgBuff)
        {
            NAS_LPP_ERR_LOG("NAS_LPP_AckDataCnfSuccHandle: No buffer!");
            TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_CantFindUpBuff);
            return;
        }

        NAS_LPP_RelUpMsgBuffer(&pstUplinkMsgBuff);
        NAS_LPP_NORM_LOG("NAS_LPP_RcvIntraDataCnf: Null!");
        TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_CanntFindTransaction);
        return;
    }

    /*ֹͣ���е�session������*/
    if (NAS_LPP_CONN_MANAGE_FAIL == pRcvMsg->enRslt)
    {
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_ConnManageFail);
        /* NAS_LPP_ReleaseAllSession(); */
        NAS_LPP_ReleaseTransactionOrSession(ucSessionIndex,
                                            ucSessionTransIndx,
                                          &(pstTransEntity->stTransId));

        return;
    }

    pstUplinkMsgBuff = NAS_LPP_GetLppMsgUpBuffByOpId(pRcvMsg->ulOpId);
    if(NAS_LPP_NULL_PTR == pstUplinkMsgBuff)
    {
        NAS_LPP_ERR_LOG("NAS_LPP_AckDataCnfSuccHandle: No buffer!");
        TLPS_PRINT2LAYER_ERROR(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_CantFindUpBuff);
        return;
    }

    /*������������TRANSACTIONȡ��ǰ��״̬��״̬��ȷ���Ƿ���Ҫִ�е���Ϣ:������ǣ��˳�*/
    if (NAS_LPP_SUCCESS != NAS_LPP_TransFsmCheck(pstTransEntity->enLppMainState,
                                                 pstTransEntity->enLppSubState,
                                                 (PS_MSG_HEADER_STRU *)pRcvMsg) )
    {
        NAS_LPP_ERR_LOG2("intra data msg not match fsm, Main State,SubState",
                          pstTransEntity->enLppMainState,
                          pstTransEntity->enLppSubState);
        TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_MainStat);
        TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_SubStat);
        return;
    }

    /*�����transaction���ڵȴ�����LPP ACK(������LPP ABORT /LPP ERROR)������ɵ�״̬*/
    if ( LPP_SS_WAIT_INTRA_DATA_CNF_OF_UP_LPP_ACK == pstTransEntity->enLppSubState )
    {
        /*�����ǰ�յ��ĵ�intra data cnf�Ƕ�Ӧ����abort����error�Ļظ�������ݳ������session��*/
        NAS_LPP_WARN_LOG("NAS_LPP_RcvIntraDataCnf: Dn Abort or Error Msg's Up Lpp Ack!");
        TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_DnAbortOrErrorMsgAndCnfUpLppAck);
        NAS_LPP_AbortAndErrorProcess(ucSessionIndex,
                                     ucSessionTransIndx,
                                     &(pRcvMsg->stLppMsgIdentity.stTransId));
        return;
    }

    /*������transaction��*/
    if (NAS_LPP_SUCCESS != pRcvMsg->enRslt)
    {
        /*�յ���intra data cnf�ǳɹ���ԭ��ֵ�����ͷ�session*/
        NAS_LPP_WARN_LOG("NAS_LPP_RcvIntraDataCnf: Intra Data cnf fail!");
        TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_IntraDataCnfFail);

        NAS_LPP_ReleaseTransactionOrSession(ucSessionIndex,
                                            ucSessionTransIndx,
                                            &(pstUplinkMsgBuff->stLppMsgIdentity.stTransId));
    }
    else if (PS_TRUE == pstTransEntity->ucTransEndFlag)
    {
        /*upbuffer������2��LPPMSG: LPP ACK +  up lpp msg;������������϶�ֻ��
          һ��LPP ACK�ڷ��ͣ�û��������Ϣ, ���������·��������ݵĳ���*/
        if (NAS_LPP_AIR_MSG_UP_LPP_ACK == pstTransEntity->enLastUpMsgId)
        {
            NAS_LPP_WARN_LOG("NAS_LPP_RcvIntraDataCnf: Only One Ack Msg!");
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_OnlyOneAckMsg);
            NAS_LPP_ReleaseTransactionOrSession(ucSessionIndex,
                                                ucSessionTransIndx,
                                                &(pstUplinkMsgBuff->stLppMsgIdentity.stTransId));

            return;
        }

        if(  NAS_LPP_UPLINK_MSG_TYPE_ACK == pstUplinkMsgBuff->stLppMsgIdentity.enUplinkMsgType)
        {
            /*�����֧�ĳ������統ǰ��������·���������UEͬʱ��������ACK���Լ�provideCap��
            ��ʱ�յ�ack��data cnf����Ҫ�ͷŶ�Ӧ��ack��buff*/
            NAS_LPP_WARN_LOG("NAS_LPP_RcvIntraDataCnf: Have two upMsg!");
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_HaveTwoUpMsg);

            NAS_LPP_RelUpMsgBuffer(&pstUplinkMsgBuff);
            return;
        }
    }
    else
    {
        if (  NAS_LPP_UPLINK_MSG_TYPE_ACK == pstUplinkMsgBuff->stLppMsgIdentity.enUplinkMsgType)
        {
            /*transaction��û�н����������ͷŶ�ӦACK��buff����*/
            NAS_LPP_WARN_LOG("NAS_LPP_RcvIntraDataCnf: Not End And Normal Ack Msg!");
            TLPS_PRINT2LAYER_WARNING(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_NotEndNormalAckMsg);

            NAS_LPP_RelUpMsgBuffer(&pstUplinkMsgBuff);
            return;
        }
        else
		{

        }

    }

    /*�ɹ�������:ת��״̬���������ȴ�ACK�Ķ�ʱ��*/
    enSubState = NAS_LPP_GetWaitAckSubState( pstTransEntity->enLastUpMsgId, pstTransEntity->enLppMainState);
    NAS_LPP_INFO_LOG2("NAS_LPP_RcvIntraDataCnf: MainState, SubState", pstTransEntity->enLppMainState, enSubState);
    NAS_LPP_ChangeTransFsmState(ucSessionIndex, ucSessionTransIndx, pstTransEntity->enLppMainState, enSubState );
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_MainStat);
    TLPS_PRINT2LAYER_INFO(NAS_LPP_RcvIntraDataCnf_ENUM, LNAS_LPP_SubStat);
}

/*****************************************************************************
 Function Name   : NAS_LPP_LppMsgDistr
 Description     : LPPģ���LPPģ���Լ������ڲ���Ϣ�Ĵ�����ں���
 Input           : None
 Output          : None
 Return          : UINT32

 History         :
    1.XiaoJun      2015-7-20  Draft Enact

*****************************************************************************/
VOS_VOID  NAS_LPP_LppMsgDistr( VOS_VOID *pRcvMsg )
{
    NAS_LPP_INTRA_MSG_STRU *pstIntraMsg = NAS_LPP_NULL_PTR;

    NAS_LPP_INFO_LOG("NAS_LPP_LppMsgDistr enter!");
    TLPS_PRINT2LAYER_INFO(NAS_LPP_LppMsgDistr_ENUM, LNAS_LPP_Func_Enter);

    pstIntraMsg = (NAS_LPP_INTRA_MSG_STRU*)pRcvMsg;

    /*������Ϣ����������Ӧ����Ϣ������*/
    switch ( pstIntraMsg->ulMsgId )
    {
        case ID_NAS_LPP_INTRA_DATA_CNF :
            NAS_LPP_RcvIntraDataCnf((NAS_LPP_INTRA_DATA_CNF_STRU *)pstIntraMsg);
            break;

        default:
            NAS_LPP_INFO_LOG("NAS_LPP_LppMsgDistr: Error Msg id!");
            TLPS_PRINT2LAYER_INFO(NAS_LPP_LppMsgDistr_ENUM, LNAS_LPP_ErrorSenderPid);
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

