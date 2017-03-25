/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnMsgSendSms.c
  �� �� ��   : ����
  ��    ��   : �ܾ� 40661
  ��������   : 2008��2��21��
  ����޸�   :
  ��������   : ʵ��MSGģ�鷢����Ϣ��nas��smsģ��ĺ����ӿ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��2��21��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ļ�
  2.��    ��   : 2009��3��23��
    ��    ��   : f62575
    �޸�����   : AT2D08752, W���뷽ʽ�£��źŽ���ʱ�������Ͷ������Ż�����Գ��ַ��Ͳ���ʧ�ܣ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "MnMsgInclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_MNMSG_SENDSMS_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

/*lint -save -e958 */


/*****************************************************************************
  2 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : MN_MSG_SendSmsRpDataReq
 ��������  : ����Rp-Data���ݵ�NAS���SMSģ��
 �������  : enSendDomain:Rp-Data�ķ�����
             pucSendMsg:�������ݵ�����,����ΪЭ��24011��RP-Data������
             ucSendLen:pucSendMsg�ĳ���
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��7��10��
    ��    ��   : y00245242
    �޸�����   : ����SMS����·���жϣ�����SMS���͸�IMSջ����PSջ    
*****************************************************************************/
VOS_UINT32 MN_MSG_SendSmsRpDataReq(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain,
    const VOS_UINT8                     *pucSendMsg ,
    VOS_UINT8                           ucSendLen,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType    
)
{
    VOS_UINT32                          ulLen;
    SMT_SMR_DATA_STRU                   *pstSendMsg ;

    ulLen = ((ucSendLen + sizeof(MN_MSG_SEND_DOMAIN_ENUM_U8)) + sizeof(SMT_SMR_DATA_STRU)) - 4;
    pstSendMsg = (SMT_SMR_DATA_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,ulLen);
    if (VOS_NULL_PTR == pstSendMsg)
    {
        MN_WARN_LOG("MN_MSG_SendSmsRpDataReq:ERROR: VOS_AllocMsg fails");
        return VOS_ERR;
    }

/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-10, begin */
    pstSendMsg->ulSenderCpuId = VOS_LOCAL_CPUID;
    pstSendMsg->ulSenderPid = WUEPS_PID_TAF;
    pstSendMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSendMsg->ulDataLen = ucSendLen;
    pstSendMsg->aucData[0] = enSendDomain;
    if(0 != ucSendLen)
    {
        PS_MEM_CPY(&pstSendMsg->aucData[1] ,pucSendMsg,ucSendLen);
    }

#if (FEATURE_ON == FEATURE_IMS)
    if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP == enMsgSignallingType)
    {
        pstSendMsg->ulReceiverPid = PS_PID_IMSA;
        pstSendMsg->ulMsgName     = ID_MSG_IMSA_RP_DATA_REQ;
    }
    else
#endif    
    {
        pstSendMsg->ulReceiverPid = WUEPS_PID_SMS;
        pstSendMsg->ulMsgName = SMT_SMR_DATA_REQ;    
    }

    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_TAF, pstSendMsg ) )
    {
        MN_WARN_LOG( "MN_MSG_SendSmsRpDataReq:WARNING:SEND SMT_SMR_DATA_STRU msg FAIL!" );
        return VOS_ERR;
    }    
/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-10, end */

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_SendSmsCpAckReq
 ��������  : ����CP-ACK���ݵ�NAS���SMSģ��
 �������  : enSendDomain:Rp-Data�ķ�����
             pucSendMsg:�������ݵ�����,����ΪЭ��24011��RP-Data������
             ucSendLen:pucSendMsg�ĳ���
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_SendSmsCpAckReq(VOS_VOID)
{
    SMT_SMR_DATA_STRU                   *pstSendMsg ;

    pstSendMsg = (SMT_SMR_DATA_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF, sizeof(SMT_SMR_DATA_STRU));
    if (VOS_NULL_PTR == pstSendMsg)
    {
        MN_WARN_LOG("MN_MSG_SendSmsRpDataReq:ERROR: VOS_AllocMsg fails");
        return;
    }
    PS_MEM_SET(pstSendMsg->aucData, 0x00, 4);
    pstSendMsg->ulSenderCpuId = VOS_LOCAL_CPUID;
    pstSendMsg->ulSenderPid = WUEPS_PID_TAF;
    pstSendMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSendMsg->ulReceiverPid = WUEPS_PID_SMS;
    pstSendMsg->ulMsgName = SMT_SMR_CP_ACK_REQ;
    pstSendMsg->ulDataLen = 0;

    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_SMS, pstSendMsg ) )
    {
        MN_WARN_LOG( "MN_MSG_SendSmsRpDataReq:WARNING:SEND SMT_SMR_DATA_STRU msg FAIL!" );
        return;
    }
    return;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_SendSmsRpReportReq
 ��������  : ����Rp-Report���ݵ�NAS���SMSģ��
 �������  : pSendMsg:�������ݵ�����,����ΪЭ��24011��RP-ACK��RP-ERROR������
             ucSendLen:�������ݵĳ���
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��7��10��
    ��    ��   : y00245242
    �޸�����   : ����SMS����·���жϣ�����SMS���͸�IMSջ����PSջ
*****************************************************************************/
VOS_UINT32 MN_MSG_SendSmsRpReportReq(
    const VOS_UINT8                    *pucSendMsg ,
    VOS_UINT8                           ucSendLen,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
)
{
    VOS_UINT32                          ulLen ;
    SMT_SMR_DATA_STRU                   *pstSendMsg;

    ulLen = (sizeof(SMT_SMR_DATA_STRU) - 4) + ucSendLen ;
    pstSendMsg = (SMT_SMR_DATA_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,ulLen);
    if (VOS_NULL_PTR == pstSendMsg)
    {
        MN_WARN_LOG("MN_MSG_SendSmsRpReportReq:ERROR: VOS_AllocMsg fails");
        return VOS_ERR;
    }
    pstSendMsg->ulSenderCpuId = VOS_LOCAL_CPUID;
    pstSendMsg->ulSenderPid = WUEPS_PID_TAF;
    pstSendMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
 
/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-10, begin */
#if (FEATURE_ON == FEATURE_IMS)    
    if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP == enMsgSignallingType)
    {
        pstSendMsg->ulReceiverPid = PS_PID_IMSA;
        pstSendMsg->ulMsgName = ID_MSG_IMSA_REPORT_REQ;
    }
    else
#endif    
    {
        pstSendMsg->ulReceiverPid = WUEPS_PID_SMS;
        pstSendMsg->ulMsgName = SMT_SMR_REPORT_REQ;
    }
/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-10, end */

    pstSendMsg->ulDataLen = ucSendLen;
    PS_MEM_CPY(pstSendMsg->aucData ,pucSendMsg,ucSendLen);

/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-10, begin */
    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_TAF, pstSendMsg ) )
/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-10, end */
    {
        MN_WARN_LOG( "MN_MSG_SendSmsRpReportReq:WARNING:SEND SMT_SMR_DATA_STRU msg FAIL!" );
        return VOS_ERR;
    }
    return VOS_OK;
}

/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-10, begin */
/*****************************************************************************
 �� �� ��  : MN_MSG_SendSmsSmmaReq
 ��������  : ����SMMA��Ϣ��NAS���SMSģ��
 �������  : enSendDomain:Rp-Data�ķ�����
             pSendMsg:�������ݵ�����,����ΪЭ��24011��RP-Data������
             ucSendLen:pucSendMsg�ĳ���
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��28��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2012122406218, ��������������������: ���ŷ������̲���
  3.��    ��   : 2013��7��3��
    ��    ��   : y00245242
    �޸�����   : ����SMS����·���жϣ�����SMS���͸�IMSջ����PSջ    
*****************************************************************************/
VOS_UINT32 MN_MSG_SendSmsSmmaReq(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enSendDomain,
    TAF_MSG_SIGNALLING_TYPE_ENUM_UINT32 enMsgSignallingType
)
{
    SMT_SMR_SMMA_STRU                   *pstSmaMsg;

    pstSmaMsg = (SMT_SMR_SMMA_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,sizeof(SMT_SMR_SMMA_STRU));
    if (VOS_NULL_PTR == pstSmaMsg)
    {
        MN_WARN_LOG("MN_MSG_SendSmsSmmaReq:ERROR: VOS_AllocMsg fails");
        return VOS_ERR;
    }
    pstSmaMsg->ulSenderCpuId = VOS_LOCAL_CPUID;
    pstSmaMsg->ulSenderPid = WUEPS_PID_TAF;
    pstSmaMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSmaMsg->ucSendDomain = enSendDomain;
    pstSmaMsg->ucAbortFlg = SMT_SMR_ABORT_FLG_NO_EXIST;
    PS_MEM_SET(pstSmaMsg->aucReserve1, 0, sizeof(pstSmaMsg->aucReserve1));
    
    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, begin */
#if (FEATURE_ON == FEATURE_IMS)    
    if (TAF_MSG_SIGNALLING_TYPE_CS_OVER_IP == enMsgSignallingType)
    {
        pstSmaMsg->ulReceiverPid = PS_PID_IMSA;
        pstSmaMsg->ulMsgName = ID_MSG_IMSA_SMMA_REQ; 
    }
    else
#endif    
    {
        pstSmaMsg->ulReceiverPid = WUEPS_PID_SMS;
        pstSmaMsg->ulMsgName = SMT_SMR_SMMA_REQ; 
    }

    if ( VOS_OK != PS_SEND_MSG( WUEPS_PID_TAF, pstSmaMsg ) )
    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, end */
    {
        MN_WARN_LOG( "MN_MSG_SendSmsSmmaReq:WARNING:SEND SMT_SMR_SMMA_STRU msg FAIL!" );
        return VOS_ERR;
    }
    return VOS_OK;
}
/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-10, end */

/*****************************************************************************
 �� �� ��  : MN_MSG_EncodeRpData
 ��������  : ����24011��Rp-Data�Ľṹ����һ��Rp-Data���ֽ���
 �������  : stRpData:24011��Rp-Data�Ľṹ
 �������  : pucRpduContent:Rp-Data���ֽ���������
             pucRpduLen:Rp-Data���ֽ����ĳ���
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_MSG_EncodeRpData(
    const MN_MSG_RP_DATA_STRU           *pstRpData,
    VOS_UINT8                           *pucRpduContent,
    VOS_UINT8                           *pucRpduLen
)
{
    VOS_UINT32                          ulPos = 0;

    *pucRpduContent = pstRpData->ucRpMsgType;
    ulPos = sizeof(pstRpData->ucRpMsgType);
    *(pucRpduContent + ulPos) = pstRpData->ucRpMr;
    ulPos += sizeof(pstRpData->ucRpMr);
    /*RP Originator Address ���� 1���ֽ�*/
    if (pstRpData->stOrgAddr.ucBcdLen > 0)
    {
        *(pucRpduContent + ulPos) = pstRpData->stOrgAddr.ucBcdLen + 1;
        ulPos += sizeof(pstRpData->stOrgAddr.ucBcdLen);
        *(pucRpduContent + ulPos) = pstRpData->stOrgAddr.addrType;
        ulPos += sizeof(pstRpData->stOrgAddr.addrType);
        PS_MEM_CPY(pucRpduContent + ulPos,pstRpData->stOrgAddr.aucBcdNum,pstRpData->stOrgAddr.ucBcdLen);
        ulPos += pstRpData->stOrgAddr.ucBcdLen;
    }
    else
    {
        *(pucRpduContent + ulPos) = pstRpData->stOrgAddr.ucBcdLen;
        ulPos += sizeof(pstRpData->stOrgAddr.ucBcdLen);
    }

    /*RP Destination Address ���� 1���ֽ�*/
    if (pstRpData->stDestAddr.ucBcdLen > 0)
    {
        *(pucRpduContent + ulPos) = pstRpData->stDestAddr.ucBcdLen + 1;
        ulPos += sizeof(pstRpData->stDestAddr.ucBcdLen);
        *(pucRpduContent + ulPos) = pstRpData->stDestAddr.addrType;
        ulPos += sizeof(pstRpData->stDestAddr.addrType);
        PS_MEM_CPY(pucRpduContent + ulPos,pstRpData->stDestAddr.aucBcdNum,pstRpData->stDestAddr.ucBcdLen);
        ulPos += pstRpData->stDestAddr.ucBcdLen;
    }
    else
    {
        *(pucRpduContent + ulPos) = pstRpData->stDestAddr.ucBcdLen;
        ulPos += sizeof(pstRpData->stDestAddr.ucBcdLen);
    }

    *(pucRpduContent + ulPos) = pstRpData->ucRpUserDataLen;
    ulPos += sizeof(pstRpData->ucRpUserDataLen);
    PS_MEM_CPY(pucRpduContent + ulPos,pstRpData->aucRpUserData,pstRpData->ucRpUserDataLen);
    ulPos += pstRpData->ucRpUserDataLen;

    *pucRpduLen = (VOS_UINT8)ulPos;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_EncodeRpAck
 ��������  : ����24011��Rp-ACK�Ľṹ����һ��Rp-ACK���ֽ���
 �������  : pstRpAck:24011��Rp-ACK�Ľṹ
 �������  : pucRpduContent:Rp-ACK���ֽ���������
             pucRpduLen:Rp-ACK���ֽ����ĳ���
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_MSG_EncodeRpAck(
    const MN_MSG_RP_ACK_STRU            *pstRpAck,
    VOS_UINT8                           *pucRpduContent,
    VOS_UINT8                           *pucRpduLen
)
{
    VOS_UINT32                          ulPos = 0;

    *pucRpduContent = pstRpAck->ucRpMsgType;
    ulPos = sizeof(pstRpAck->ucRpMsgType);
    *(pucRpduContent + ulPos) = pstRpAck->ucRpMr;
    ulPos += sizeof(pstRpAck->ucRpMr);

    /*����RP User Data*/
    if (VOS_TRUE == pstRpAck->bRpUserDataExist)
    {
       *(pucRpduContent + ulPos) = pstRpAck->ucRpUserDataIei;
       ulPos += sizeof(pstRpAck->ucRpUserDataIei);
       *(pucRpduContent + ulPos) = pstRpAck->ucRpUserDataLen;
       ulPos += sizeof(pstRpAck->ucRpUserDataLen);
       PS_MEM_CPY(pucRpduContent + ulPos,pstRpAck->aucRpUserData,pstRpAck->ucRpUserDataLen);
       ulPos += pstRpAck->ucRpUserDataLen;
    }
    *pucRpduLen = (VOS_UINT8)ulPos;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_EncodeRpErr
 ��������  : ����24011��Rp-Error�Ľṹ����һ��Rp-Error���ֽ���
 �������  : pstRpErr:24011��Rp-Error�Ľṹ
 �������  : pucRpduContent:Rp-Error���ֽ���������
             pucRpduLen:Rp-Error���ֽ����ĳ���
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_MSG_EncodeRpErr(
    const MN_MSG_RP_ERR_STRU            *pstRpErr,
    VOS_UINT8                           *pucRpduContent,
    VOS_UINT8                           *pucRpduLen
)
{
    VOS_UINT32                          ulPos = 0;

    *pucRpduContent = pstRpErr->ucRpMsgType;
    ulPos = sizeof(pstRpErr->ucRpMsgType);
    *(pucRpduContent + ulPos) = pstRpErr->ucRpMr;
    ulPos += sizeof(pstRpErr->ucRpMr);
    *(pucRpduContent + ulPos) = pstRpErr->ucRpCauseLen;
    ulPos += sizeof(pstRpErr->ucRpCauseLen);
    *(pucRpduContent + ulPos) = pstRpErr->stRpCause.enRpCause;
    ulPos += sizeof(pstRpErr->stRpCause.enRpCause);
    /*Rp-Cause�д���Diagnostics Field*/
    if (VOS_TRUE == pstRpErr->stRpCause.bDiagnosticsExist)
    {
        *(pucRpduContent + ulPos) = pstRpErr->stRpCause.ucDiagnostics;
        ulPos += sizeof(pstRpErr->stRpCause.ucDiagnostics);
    }
    /*����RP User Data*/
    if (VOS_TRUE == pstRpErr->bRpUserDataExist)
    {
       *(pucRpduContent + ulPos) = pstRpErr->ucRpUserDataIei;
       ulPos += sizeof(pstRpErr->ucRpUserDataIei);
       *(pucRpduContent + ulPos) = pstRpErr->ucRpUserDataLen;
       ulPos += sizeof(pstRpErr->ucRpUserDataLen);
       PS_MEM_CPY(pucRpduContent + ulPos,pstRpErr->aucRpUserData,pstRpErr->ucRpUserDataLen);
       ulPos += pstRpErr->ucRpUserDataLen;
    }
    *pucRpduLen = (VOS_UINT8)ulPos;
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

