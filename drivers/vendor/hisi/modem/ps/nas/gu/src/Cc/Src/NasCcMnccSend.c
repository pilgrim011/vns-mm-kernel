/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasCcMnccSend.c
  �� �� ��   : ����
  ��    ��   : ���� 49431
  ��������   : 2007��10��17��
  ����޸�   : 2007��10��17��
  ��������   : ����MNCCԭ��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��10��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasCcInclude.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* ȡ��MNCCԭ��(CC -> MN)��ͷ������ */
#define NAS_CC_MNCC_IND_HDR_LEN   \
    (sizeof(MNCC_IND_PRIM_MSG_STRU) - sizeof(MNCC_IND_PARAM_UNION))

/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define THIS_FILE_ID PS_FILE_ID_NASCC_MNCCSEND_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

/*lint -save -e958 */

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : NAS_CC_SendMnccMsg
 ��������  : ���ϲ㷢��MNCCԭ����Ϣ
 �������  : entityId     - CCʵ��ID
              enPrimName   - ԭ������
              pParam       - ԭ��������μ�MNCC_IND_PARAM_UNION
              ulParamLen   - ԭ������ĳ���
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/
VOS_VOID  NAS_CC_SendMnccMsg(
    NAS_CC_ENTITY_ID_T                  entityId,
    MNCC_PRIM_NAME_ENUM_U16             enPrimName,
    const VOS_VOID                      *pParam,
    VOS_UINT32                          ulParamLen
)
{
    MsgBlock                            *pstTmpMsg;
    MNCC_IND_PRIM_MSG_STRU              *pstMsg;

    /* ����VOS��Ϣ */


    pstTmpMsg = PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_CC, NAS_CC_MNCC_IND_HDR_LEN + sizeof(pstMsg->unParam));
    if (VOS_NULL_PTR == pstTmpMsg)
    {
        NAS_CC_ERR_LOG("NAS_CC_SendMnccMsg: Failed to alloc VOS message.");
        return;
    }

    /* ��дVOS��Ϣͷ */
    pstMsg = (MNCC_IND_PRIM_MSG_STRU*)pstTmpMsg;
    pstMsg->ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid = WUEPS_PID_CC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid = WUEPS_PID_TAF;

    /* ��дԭ���ײ� */
    pstMsg->enPrimName = enPrimName;
    if(NAS_CC_MAX_ENTITY_NUM != entityId )
    {
        pstMsg->ucTi = NAS_CC_GetEntityTi(entityId);
        pstMsg->ucCallId = NAS_CC_GetCallId(entityId);
    }

    pstMsg->ulParamLen = ulParamLen;
    PS_MEM_SET(&pstMsg->unParam, 0 ,sizeof(pstMsg->unParam));
    /* �����ԭ���������дԭ����� */
    if ((pParam != VOS_NULL_PTR)
     && (ulParamLen != 0))
    {
        PS_MEM_CPY(&pstMsg->unParam, pParam, ulParamLen);
    }

    /* ����VOS��Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_CC, pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_CC, "NAS_CC_SendMnccMsgs():WARNING:SEND MSG FIAL");
    }        
}

/*****************************************************************************
 �� �� ��  : API_CcSyncInd
 ��������  : ���ϲ㷢��MNCCԭ����Ϣ
 �������  : ucActType    - CCʵ��ID
             enPrimName   - ԭ������
             pParam       - ԭ��������μ�MNCC_IND_PARAM_UNION
             ulParamLen   - ԭ������ĳ���
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��17��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
*****************************************************************************/
VOS_VOID  API_CcSyncInd(VOS_UINT8  ucActType, VOS_UINT32 ucRabId)
{
    MMCC_SYNC_IND_STRU* pstMsg;

    /* ����Ϣֻ����RAB�ͷ���Ϣ�����ڽ��������䣬��MM�ϱ� */
    if(ucActType != 2)
    {
        return;
    }

    /* ����VOS��Ϣ */
    pstMsg = (MMCC_SYNC_IND_STRU *)
        PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_CC, sizeof(MMCC_SYNC_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_CC_ERR_LOG("API_CcSyncInd: Failed to alloc VOS message.");
        return;
    }

    /* ��дVOS��Ϣͷ */
    pstMsg->MsgHeader.ulSenderCpuId = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid = WUEPS_PID_MM;
    pstMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid = WUEPS_PID_CC;

    pstMsg->MsgHeader.ulMsgName= MMCC_SYNC_IND;
    /* message content, default value */
    pstMsg->enChannelMode= 0;

    pstMsg->ulRabNum = 1;
    pstMsg->syncInfo[0].ulRabId = ucRabId;
    pstMsg->syncInfo[0].ulRabSyncInfo = ucRabId;
    pstMsg->enSyncReason = MMCC_WCDMA_RAB_RELEASED;

    /* ����VOS��Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_CC, pstMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_CC, "API_CcSyncInd():WARNING:SEND MSG FIAL");
    }        
}

/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-10, begin */
#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : NAS_CC_SendMnccSrvccStatusIndMsg
 ��������  : ���ϲ㷢��MNCCԭ����ϢMNCC_SRVCC_STATUS_IND
 �������  : enSrvccSta----SRVCC״̬
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��10��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_CC_SendMnccSrvccStatusIndMsg(
    NAS_MNCC_SRVCC_STATUS_ENUM_UINT32   enSrvccSta
)
{
    MNCC_SRVCC_STATUS_IND_STRU          stSrvccStaInd;
    
    PS_MEM_SET((VOS_INT8*)&stSrvccStaInd,0x0, sizeof(MNCC_SRVCC_STATUS_IND_STRU));
  
    stSrvccStaInd.enSrvccStatus  = enSrvccSta;

    /* ����ͳһ���͵�CALL����Ϣ����,entity ID��CALLģ�鲻��ע */
    NAS_CC_SendMnccMsg(0,
                       MNCC_SRVCC_STATUS_IND,
                       &stSrvccStaInd,
                       sizeof(MNCC_SRVCC_STATUS_IND_STRU));

    return;
}
#endif
/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-10-10, end */

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

