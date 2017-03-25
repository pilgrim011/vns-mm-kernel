/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : Aps_DealSndcpMsg.c
  Author       : ��³��
  Version      : V200R001
  Date         : 2005-0
  Description  :
  Function List:
        ---Aps_DealAllFromSndcp
        ---Aps_SnMsgModSnActRsp
        ---Aps_SnMsgModSnActRspParaCheck
        ---Aps_SnMsgModSnMdfRsp
        ---Aps_SnMsgModSnMdfRspParaCheck

        ---Aps_SnMsgModSnDeActRsp
        ---Aps_SnMsgModSnDeActRspParaCheck
        ---Aps_SnMsgModSnStatusReq
        ---Aps_SnMsgModSnStatusReqParaCheck
        ---Aps_FindSapiPdp

        ---Aps_FindSapiTransModePdp
        ---Aps_Nsapi2PdpId
        ---
  History      :
  1. Date:2005-10-30
     Author: ��³��
     Modification:Create
  2. 2006-02-23 modify by ��³�� FOR A32D02144
  3. 2006-02-28 modify by ��³�� for A32D02265

  4.��    ��   : 2006��4��4��
    ��    ��   : liuyang id:48197
    �޸�����   : ���ⵥ��:A32D01738
  5.��    ��   : 2006��7��6��
    ��    ��   : L47619
    �޸�����   : ���ⵥ��:A32D04774
************************************************************************/


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "Taf_Aps.h"
#include "MnApsComm.h"
#include "TafApsMain.h"
#include "TafApsCtx.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APSDEALSNDCPMSG_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/


/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/


/*****************************************************************************
 Prototype      : Aps_SnMsgModSnActRspParaCheck()
 Description    : SNDCP�ļ���RSP���޸�RSP����Ϣ������ͬ,��ʹ��ͬһ������������
                  �������.
 Input          : pSnActRsp
 Output         :
 Return Value   : #define APS_PARA_VALID                  0
                  #define APS_PARA_INVALID                1
 Data Access    :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_SnMsgModSnActRspParaCheck( APS_SNDCP_ACTIVATE_RSP_ST* pSnActRsp)
{
    if ( pSnActRsp->XidParameter.ucMask & SN_XID_PARA_P_CMPR)
    {
        if ( !(APS_SN_P_CMP_VALID(pSnActRsp->XidParameter.ucPCmprAlgrth)) )
        {
            return  APS_PARA_INVALID;
        }
    }

    if ( pSnActRsp->XidParameter.ucMask & SN_XID_PARA_D_CMPR)
    {
        if ( !(APS_SN_H_CMP_VALID(pSnActRsp->XidParameter.ucDCmprAlgrth)) )
        {
            return  APS_PARA_INVALID;
        }
    }
    return  APS_PARA_VALID;

}

/*****************************************************************************
 Prototype      : Aps_SnActRspChngEntity()
 Description    : �յ�SN_ACT_RSP���޸�״̬������,����XID����,TRANSMODE,״̬
 Input          : pSnMdfRsp
 Output         : NO
 Return Value   :
 Data Access    :
 Data Update    :
 Calls          : Rabm_SetTransMode();
                  Aps_DealEntityTrans();
 Called By      : Aps_DealAllFromSndcp()
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_SnActRspChngEntity(     APS_SNDCP_ACTIVATE_RSP_ST*  pSnActRsp,
                                        VOS_UINT8                   ucPdpId)
{
    RABM_TRANS_MODE_ENUM                TansMode;

    /*��������XID����״̬��*/
    if ( pSnActRsp->XidParameter.ucMask & SN_XID_PARA_P_CMPR)
    {
        g_PdpEntity[ucPdpId].PdpGprsParaFlag        = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.Op_Xid_PCmp   = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.ucPCmprAlgrth
                                        = pSnActRsp->XidParameter.ucPCmprAlgrth;
    }

    if ( pSnActRsp->XidParameter.ucMask & SN_XID_PARA_D_CMPR)
    {
        g_PdpEntity[ucPdpId].PdpGprsParaFlag        = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.Op_Xid_DCmp   = VOS_TRUE;
        g_PdpEntity[ucPdpId].GprsPara.ucDCmprAlgrth
                                        = pSnActRsp->XidParameter.ucDCmprAlgrth;
    }

    Aps_DecideTransMode( ucPdpId, &TansMode );

    /*��д״̬���е�TRANSMODE*/
    g_PdpEntity[ucPdpId].GprsPara.Op_TransMode  = VOS_TRUE;
    g_PdpEntity[ucPdpId].GprsPara.TransMode     = TansMode;

    return;
}

/*****************************************************************************
 Prototype      : Aps_SnMsgModSnMdfRsp()
 Description    : APS�޸�ָʾSNDCP��,SNDCPӦ�÷���APS��Ӧ��Ϣ.�ú������ڴ�����
                  ����Ӧ��Ϣ.������RABM�ṩ�ĺ�������RABM��TRANSMODE,Ȼ���ϱ�
                  APP�޸��Ƿ�ɹ����¼���
 Input          : pSnMdfRsp
 Output         : NO
 Return Value   :
 Data Access    :
 Data Update    :
 Calls          : Rabm_SetTransMode();
                  Aps_DealEntityTrans();
 Called By      : Aps_DealAllFromSndcp()
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_SnMsgModSnMdfRsp  ( APS_SNDCP_MODIFY_RSP_ST*  pSnMdfRsp )
{
    VOS_UINT8                       ucPdpId;
    RABM_APS_SET_TRANS_MODE_ST      ApsRabmSetTRansMod;

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    Aps_SnMdfRspChngEntity(pSnMdfRsp, ucPdpId);

    ApsRabmSetTRansMod.ucNsapi      = pSnMdfRsp->ucNsapi;
    ApsRabmSetTRansMod.TransMode    = g_PdpEntity[ucPdpId].GprsPara.TransMode;

    /*����RABM�Ĵ���ģʽ*/
    if ( TAF_APS_SUCC != Aps_SetRabmTransMode(&ApsRabmSetTRansMod))
    {
        APS_WARN_LOG("NAS_RabmSetTransMode ERR ");
        return;
    }

    return;
}

/*****************************************************************************
 Prototype      : Aps_SnMsgModSnMdfRspParaCheck()
 Description    :
 Input          : pSnActRsp
 Output         :
 Return Value   : #define APS_PARA_VALID                  0
                  #define APS_PARA_INVALID                1
                  APS_NSAPI_INVALID
 Data Access    :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_SnMsgModSnMdfRspParaCheck( APS_SNDCP_MODIFY_RSP_ST*   pSnActRsp)
{
    if ( !(APS_JUDGE_NSAPI_VALID(pSnActRsp->ucNsapi)))
    {
        return  APS_NSAPI_INVALID;
    }

    return  APS_PARA_VALID;
}

/*****************************************************************************
 Prototype      : Aps_SnMdfRspChngEntity()
 Description    : �յ�SN_MDF_RSP���޸�״̬������,TRANSMODE,״̬
 Input          : pSnMdfRsp
 Output         : NO
 Return Value   :
 Data Access    :
 Data Update    :
 Calls          : Rabm_SetTransMode();
                  Aps_DealEntityTrans();
 Called By      : Aps_DealAllFromSndcp()
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
 2.��    ��   : 2011��12��17��
   ��    ��   : s62952
   �޸�����   : PS�ں���Ŀ�޸� :ɾ��״̬����
*****************************************************************************/
VOS_VOID    Aps_SnMdfRspChngEntity(
    APS_SNDCP_MODIFY_RSP_ST            *pSnMdfRsp,
    VOS_UINT8                           ucPdpId
)
{
    RABM_TRANS_MODE_ENUM                TansMode;

    Aps_DecideTransMode( ucPdpId, &TansMode );

    /*��д״̬���е�TRANSMODE*/
    g_PdpEntity[ucPdpId].GprsPara.Op_TransMode  = VOS_TRUE;
    g_PdpEntity[ucPdpId].GprsPara.TransMode     = TansMode;

    return;
}


/*****************************************************************************
 Prototype      : Aps_SnMsgModSnDeActRspParaCheck()
 Description    : ���SAPI
 Input          : pSnActRsp
 Output         :
 Return Value   : #define APS_PARA_VALID                  0
                  #define APS_PARA_INVALID                1
 Data Access    :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32  Aps_SnMsgModSnStatusReqParaCheck
                            (   APS_SNDCP_STATUS_REQ_ST    *pSnDeActRsp)
{
    if ( APS_SAPI_VALID != APS_JUDGE_SAPI_VALID(pSnDeActRsp->ucSapi))
    {
        return  APS_PARA_INVALID;
    }

    return  APS_PARA_VALID;
}

/*****************************************************************************
 Prototype      : Aps_SetRabmTransMode
 Description    : �����ҵ�NSAPI��Ӧ��PdpId
 Input          : ucNsapi
 Output         :
 Return Value   : ucPdpId: [0,6], [8,14], 0xFF
 Data Access    :
 Data Update    :
 Calls          :
 Called By      :
 History        : ---
  1.Date        : 2005-
    Author      : ---
    Modification: Created function
  2.Date        : 2006-07-06
    Author      : L47619
    Modification: �������ⵥ�޸�:A32D04774
*****************************************************************************/
VOS_UINT32  Aps_SetRabmTransMode(   RABM_APS_SET_TRANS_MODE_ST *pApsRabmSetTRansMod)
{
    VOS_UINT32                      ulRet;
    RABM_APS_SET_TRANSMODE_MSG     *pApsSetRabmTransmodeMsg;

    /*������Ϣ*/
    pApsSetRabmTransmodeMsg = (RABM_APS_SET_TRANSMODE_MSG *)PS_ALLOC_MSG(WUEPS_PID_TAF, (sizeof(RABM_APS_SET_TRANSMODE_MSG) - VOS_MSG_HEAD_LENGTH));
    if ( VOS_NULL_PTR == pApsSetRabmTransmodeMsg )
    {
        APS_ERR_LOG("Aps_SetRabmTransMode VOS_AllocMsg err ");
        return TAF_APS_FAIL;
    }

    /*����RABM����Ϣͷ*/
    pApsSetRabmTransmodeMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pApsSetRabmTransmodeMsg->ulSenderPid      = WUEPS_PID_TAF;
    pApsSetRabmTransmodeMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pApsSetRabmTransmodeMsg->ulReceiverPid    = WUEPS_PID_RABM;

    pApsSetRabmTransmodeMsg->ulLength         = sizeof(RABM_APS_SET_TRANSMODE_MSG) - VOS_MSG_HEAD_LENGTH;

    /*����Ϣ����*/
    pApsSetRabmTransmodeMsg->usMsgType        = RABM_APS_SET_TRANSMODE_MSG_TYPE;

    /*����Ϣ����*/
    pApsSetRabmTransmodeMsg->RabmApsSetTransMode
                                            = *pApsRabmSetTRansMod;

    /*������Ϣ*/
    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pApsSetRabmTransmodeMsg );
    if ( VOS_OK != ulRet )
    {
        APS_WARN_LOG("Aps Send RABM_APS_SET_TRANSMODE_MSG ERR ");
        return  TAF_APS_FAIL;
    }

    APS_NORM_LOG("APS->RABM RABM_APS_SET_TRANSMODE_MSG ");

    return TAF_APS_SUCC;

}

/*****************************************************************************
 Prototype      : Aps_RabmMsgActSndcp
 Description    : �յ�RABM���л���Ϣ����Ҫ����SNDCP���͵��ô˺���.
 Input          : pRabmMsg
 Output         : ---
 Return Value   : ---
 Data Access    :
 Data Update    :
 Calls          : ---
 Called By      : ---
 History        : ---
  1.Date        : 2005-0
    Author      : ��³��
    Modification: Created function
  2.��    ��   : 2011��5��12��
    ��    ��   : A00165503
    �޸�����   : ���ⵥ��: DTS2011050405023, W2G��������з���PDPȥ����, ��ѡ
                 ��G��, APSû�м���SNDCP, ����SNDCP��״̬�뵱ǰPDP״̬��һ��
  3.��    ��   : 2011��12��22��
    ��    ��   : A00165503
    �޸�����   : PS Project: �޸ļ���SNDCP�����߼�, ȥ��������Ϣʧ�ܵĴ���
*****************************************************************************/
VOS_VOID    Aps_RabmMsgActSndcp (   VOS_UINT8    ucPdpId )
{
    APS_INNER_SN_ACT_ST             InnerSnActInd;
    SM_TAF_QOS_STRU                 SmQos;

    if (APS_SNDCP_ACT == g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot)
    {
        /* SNDCP�Ѿ���������ٴμ��� */
        return;
    }

    /*��PdpId*/
    InnerSnActInd.ucPdpId           = ucPdpId;

    /*���ú���Aps_PackSmQos ( &(g_PdpEntity[ucPdpId].PdpQos), &SmQos )��״̬��
    �е�QOSת��Ϊ����SNDCP��Ҫ��QOS�ṹ;*/
    PS_MEM_SET(&SmQos,0x00,sizeof(SmQos));
    Aps_PackSmQos ( &(g_PdpEntity[ucPdpId].PdpQos), &SmQos );
    InnerSnActInd.pQos              = &SmQos;

    Aps_SmMsgModSnActInd(&InnerSnActInd, APS_ACT_SN_SYS_CHNG);

    /*Ϊ�������л�����ļ���SNDCP�������յ�SN�ļ�����Ӧ�����ϱ����ڴ����ñ�ʶ*/
    g_PdpEntity[ucPdpId].PdpProcTrackFlag               = VOS_TRUE;
    g_PdpEntity[ucPdpId].PdpProcTrack.ucHowToInitAct    = APS_SYSCHNG_ACT_SN;
    g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot   = APS_SNDCP_ACT;

    return;
}

/*****************************************************************************
 Prototype      : Aps_RabmMsgDeActSndcp
 Description    : �յ�RABM���л���Ϣ����Ҫ����ȥ����SNDCP���͵��ô˺���.
 Input          : pRabmMsg
 Output         : ---
 Return Value   : ---
 Data Access    :
 Data Update    :
 Calls          : Aps_SmMsgModSnDeActInd    (   VOS_UINT8    ucPdpId )
 Called By      : ---
 History        : ---
  1.Date        : 2005-0
    Author      : ��³��
    Modification: Created function
*****************************************************************************/
VOS_VOID    Aps_RabmMsgDeActSndcp ( VOS_UINT8    ucPdpId )
{
    if (APS_SNDCP_INACT == g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot)
    {
        /*SNDCPδ������*/
        APS_WARN_LOG("Aps_RabmMsgDeActSndcp: SNDCP has been deactived already!!");
        return;
    }

    (VOS_VOID)Aps_SmMsgModSnDeActInd(ucPdpId);

    g_PdpEntity[ucPdpId].PdpProcTrack.ucSNDCPActOrNot = APS_SNDCP_INACT;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_ValidatePdpForSnStatusReq
 ��������  : ��鵱ǰAPSʵ���е�SAPI�Ƿ�����SN STATUS��Ϣ��ָ����SAPI
 �������  : ucPdpId                    - APSʵ������
             pstSnStatusReq             - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE                   - ����
             VOS_FALSE                  - ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��24��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_ValidatePdpForSnStatusReq(
    VOS_UINT8                           ucPdpId,
    APS_SNDCP_STATUS_REQ_ST            *pstSnStatusReq
)
{
    VOS_UINT32                          ulResult;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    ulResult                            = VOS_FALSE;
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    switch (pstSnStatusReq->usSnCause)
    {
        case SN_CAUSE_NORMAL_REL:           /*Cause "normal release"*/
            /*SM shall then deactivate all PDP contexts for that SAPI requiring
              acknowledged peer-to-peer LLC operation*/

        case SN_CAUSE_DM_RCV:               /*Cause "DM received"*/
            /*SM shall then deactivate all PDP contexts for that SAPI requiring
              acknowledged peer-to-peer LLC operation*/

            if ( (VOS_TRUE               == pstPdpEntity->PdpGprsParaFlag)
              && (VOS_TRUE               == pstPdpEntity->GprsPara.Op_Sapi)
              && (pstSnStatusReq->ucSapi == pstPdpEntity->GprsPara.ucSapi)
              && (VOS_TRUE               == pstPdpEntity->GprsPara.Op_TransMode)
              && (RABM_ABM_ENUM          == pstPdpEntity->GprsPara.TransMode) )
            {
                ulResult = VOS_TRUE;
            }
            break;

        case    SN_CAUSE_NO_PEER_RSP:          /*Cause "no peer response"*/
            /*����ʽͬ�����CASE,�ʲ���break*/

        case    SN_CAUSE_INVALID_XID_RSP:      /*Cause "invalid XID response"*/
            /*SM shall then deactivate all PDP contexts for that SAPI*/
            /*����ʽͬ�����CASE,�ʲ���break*/

        case    SN_CAUSE_INVALID_XID_CMD:       /*Cause "invalid XID command"*/
            /*SM shall then deactivate all PDP contexts for this SAPI*/

            if ( (VOS_TRUE               == pstPdpEntity->PdpGprsParaFlag)
              && (VOS_TRUE               == pstPdpEntity->GprsPara.Op_Sapi)
              && (pstSnStatusReq->ucSapi == pstPdpEntity->GprsPara.ucSapi) )
            {
                ulResult = VOS_TRUE;
            }
            break;

        default :
            APS_WARN_LOG("SNDCP -> Aps : invalid Status Msg Cause !");
            break;
    }

    return ulResult;
}

/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
