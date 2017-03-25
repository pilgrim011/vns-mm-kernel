
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallEncKmcMsg.c
  �� �� ��   : ����
  ��    ��   : l00359089
  ��������   : 2015��10��20��
  ��������   : Taf X Call ����������ݱ����KMC��user data
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��10��20��
    ��    ��   : l00359089
    �޸�����   : �����ļ� for CDMA 1X Iteration 19
******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "TafXCallEncKmcMsg.h"
#include "TafXCallMntn.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_ENC_KMC_MSG_C
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* TAF XCALL ģ�鴦������XCC��Ϣ������Ӧ��*/
const TAF_XCALL_ENC_KMC_MSG_PROC_STRU g_astTafXcallEncKmcMsgProcTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
    TAF_XCALL_KMC_ENC_TBL_ITEM(TAF_XCALL_KMC_MSG_TYPE_MO_KEY_REQ,                     TAF_XCALL_EncKeyReqMsg),
    TAF_XCALL_KMC_ENC_TBL_ITEM(TAF_XCALL_KMC_MSG_TYPE_MT_KEY_REQ,                     TAF_XCALL_EncKeyReqMsg),
    TAF_XCALL_KMC_ENC_TBL_ITEM(TAF_XCALL_KMC_MSG_TYPE_PUB_KEY_UPDATE_RSP,             TAF_XCALL_EncPubKeyUpdateRspMsg),
    TAF_XCALL_KMC_ENC_TBL_ITEM(TAF_XCALL_KMC_MSG_TYPE_ROMOTE_CTRL_CMD_RSP,            TAF_XCALL_EncRemoteCtrlCmdRspMsg),
#ifdef VOS_WIN32
    TAF_XCALL_KMC_ENC_TBL_ITEM(TAF_XCALL_KMC_MSG_TYPE_MO_KEY_RSP,                     TAF_XCALL_EncKeyRspMsg),
    TAF_XCALL_KMC_ENC_TBL_ITEM(TAF_XCALL_KMC_MSG_TYPE_MT_ENCRYPT_IND,                 TAF_XCALL_EncMtEncryptIndMsg),
    TAF_XCALL_KMC_ENC_TBL_ITEM(TAF_XCALL_KMC_MSG_TYPE_MT_KEY_RSP,                     TAF_XCALL_EncKeyRspMsg),
    TAF_XCALL_KMC_ENC_TBL_ITEM(TAF_XCALL_KMC_MSG_TYPE_ERR_IND,                        TAF_XCALL_EncErrIndMsg),
    TAF_XCALL_KMC_ENC_TBL_ITEM(TAF_XCALL_KMC_MSG_TYPE_PUB_KEY_UPDATE_IND,             TAF_XCALL_EncPubKeyUpdateMsg),
    TAF_XCALL_KMC_ENC_TBL_ITEM(TAF_XCALL_KMC_MSG_TYPE_PUB_KEY_UPDATE_ACK,             TAF_XCALL_EncPubKeyUpdateAckMsg),
    TAF_XCALL_KMC_ENC_TBL_ITEM(TAF_XCALL_KMC_MSG_TYPE_ROMOTE_CTRL_CMD_IND,            TAF_XCALL_EncRemoteCtrlCmdMsg),
#endif
};

/*****************************************************************************
  3 ��������
*****************************************************************************/

/**********************************************
��������TAF_XCALL_FillReservedFld
���ܣ� ��䱣���ֶ�
Input����
Output��VOS_UINT8 *pucMsgData ������ֶΣ�
        VOS_UINT16 *pusMsgDataLen���ĳ���
 1.����:      20151026
   ����:      l00359089
   �޸����ݣ��½�
*****************************************************/

VOS_VOID TAF_XCALL_FillReservedFld(
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
)
{
    /* reserved field */
    *pucMsgData++  = 0x00;
    (*pusMsgDataLen)++;

    /* the length of reserved field */
    *pucMsgData    = 0x00;
    (*pusMsgDataLen)++;

}
/**********************************************
��������TAF_XCALL_EncKeyReqMsg
���ܣ���װ��Կ�����User Data��
Input��TAF_XCALL_KMC_MSG_STRU *pstEncodeData�ض��ṹ�Ĵ��������ݣ�
Output��VOS_UINT8 *pucMsgData ��װ���User Data��
        VOS_UINT16 *pusMsgDataLen��װ���User Data�ĳ���
���أ�����ľ�����ֵ
 1.����:      20151021
   ����:      l00359089
   �޸����ݣ��½�
*****************************************************/
TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncKeyReqMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
)
{
    /* mode type. */
    *pucMsgData++  = pstEncodeData->u.stKeyReq.enTriggerMode;        /* buffer size 5 */
    (*pusMsgDataLen)++;

    /* kmc public key version. */
    *pucMsgData++  = pstEncodeData->u.stKeyReq.ucKeyVersion;        /* buffer size 6 */
    (*pusMsgDataLen)++;

    /* temp public key length. */
    *pucMsgData++  = pstEncodeData->u.stKeyReq.stTmpPubKey.ucKeyLen;           /* buffer size 7 */
    (*pusMsgDataLen)++;

    /* temp public key . */
    PS_MEM_CPY(pucMsgData, pstEncodeData->u.stKeyReq.stTmpPubKey.aucKey, pstEncodeData->u.stKeyReq.stTmpPubKey.ucKeyLen);
    pucMsgData       += pstEncodeData->u.stKeyReq.stTmpPubKey.ucKeyLen;
    (*pusMsgDataLen) += pstEncodeData->u.stKeyReq.stTmpPubKey.ucKeyLen;


    /* Cipher length. */
    *pucMsgData++ = (VOS_UINT8)(pstEncodeData->u.stKeyReq.stCipher.usCipherLen & 0x00FF);
    *pucMsgData++ = (VOS_UINT8)((pstEncodeData->u.stKeyReq.stCipher.usCipherLen & 0xFF00) >> 8);
    (*pusMsgDataLen) += 2;

    (*pusMsgDataLen) += (VOS_UINT8)(pstEncodeData->u.stKeyReq.stCipher.usCipherLen & 0x00FF);
    (*pusMsgDataLen) += TAF_XCALL_KMC_MSG_ADDITIONAL_INFO_LEN_BYTES;
    (*pusMsgDataLen) += TAF_XCALL_KMC_MSG_RSVD1_BYTES;

    if (TAF_XCALL_KMC_MSG_WMS_CDMA_USER_DATA_MAX < (*pusMsgDataLen))
    {
        return TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENC_LEN_OVER_MAX_ERR;
    }

    /*copy cipher  */
    PS_MEM_CPY(pucMsgData, pstEncodeData->u.stKeyReq.stCipher.aucCipher, pstEncodeData->u.stKeyReq.stCipher.usCipherLen);
    pucMsgData       += pstEncodeData->u.stKeyReq.stCipher.usCipherLen;

    /* reserved field */
    *pucMsgData++  = 0x00;

    /* additional info field*/
    if ((0 == pstEncodeData->u.stKeyReq.stAdditionalInfo.usSid)
     && (0 == pstEncodeData->u.stKeyReq.stAdditionalInfo.usNid)
     && (0 == pstEncodeData->u.stKeyReq.stAdditionalInfo.usBsid))
    {
        /* fill_additional_info len*/
        *pucMsgData = 0x00;
        return TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
    }

    (*pusMsgDataLen) += TAF_XCALL_KMC_MSG_ADDITIONAL_INFO_LEN;

    if (TAF_XCALL_KMC_MSG_WMS_CDMA_USER_DATA_MAX < (*pusMsgDataLen))
    {
        return TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENC_LEN_OVER_MAX_ERR;
    }

    /* fill_additional_info len*/
    *pucMsgData++  = TAF_XCALL_KMC_MSG_ADDITIONAL_INFO_LEN;

    /*fill high 8bit of sid*/
    *pucMsgData++ = (VOS_UINT8)((pstEncodeData->u.stKeyReq.stAdditionalInfo.usSid & 0xFF00) >> 8);

    /*fill low 8bit of sid*/
    *pucMsgData++ = (VOS_UINT8)(pstEncodeData->u.stKeyReq.stAdditionalInfo.usSid & 0x00FF);

    /*fill high 8bit of nid*/
    *pucMsgData++ = (VOS_UINT8)((pstEncodeData->u.stKeyReq.stAdditionalInfo.usNid & 0xFF00) >> 8);

    /*fill low 8bit of nid*/
    *pucMsgData++ = (VOS_UINT8)(pstEncodeData->u.stKeyReq.stAdditionalInfo.usNid & 0x00FF);

    /*fill high 8bit of bsid*/
    *pucMsgData++ = (VOS_UINT8)((pstEncodeData->u.stKeyReq.stAdditionalInfo.usBsid & 0xFF00) >> 8);

    /*fill low 8bit of bsid*/
    *pucMsgData   = (VOS_UINT8)(pstEncodeData->u.stKeyReq.stAdditionalInfo.usBsid & 0x00FF);

    return TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
}
/**********************************************
�������� TAF_XCALL_EncPubKeyUpdateRspMsg;
���ܣ���װ��Կ������Ӧ��User Data��
Input��TAF_XCALL_KMC_MSG_STRU *pstEncodeData�ض��ṹ�Ĵ��������ݣ�
Output��VOS_UINT8 *pucMsgData ��װ���User Data��
        VOS_UINT16 *pusMsgDataLen��װ���User Data�ĳ���
���أ�����ľ�����ֵ
 1.����:      20151021
   ����:      l00359089
   �޸����ݣ��½�

*****************************************************/
TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncPubKeyUpdateRspMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
)
{

    PS_MEM_CPY(pucMsgData, pstEncodeData->u.stPubKeyUpdateRsp.aucRandomData, TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN);
    pucMsgData       += TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN;
    (*pusMsgDataLen) += TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN;

    /* reserved field */
    TAF_XCALL_FillReservedFld(pucMsgData,pusMsgDataLen);

    return TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;

}
/**********************************************
�������� TAF_XCALL_EncRemoteCtrlCmdRspMsg
���ܣ���װ��Կ������Ӧ��User Data��
Input��TAF_XCALL_KMC_MSG_STRU *pstEncodeData�ض��ṹ�Ĵ��������ݣ�
Output��VOS_UINT8 *pucMsgData ��װ���User Data��
        VOS_UINT16 *pusMsgDataLen��װ���User Data�ĳ���

���أ�����ľ�����ֵ
 1.����:      20151021
   ����:      l00359089
   �޸����ݣ��½�
*****************************************************/
TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncRemoteCtrlCmdRspMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
)
{
    /* remote cmd type. */
    *pucMsgData++ = pstEncodeData->u.stRemoteCtrlRsp.enRomoteCtrlCmdType;
    (*pusMsgDataLen)++;

    /* result. */
    *pucMsgData++ = pstEncodeData->u.stRemoteCtrlRsp.enExecuteRslt;
    (*pusMsgDataLen)++;

    /* kmc public key version. */
    *pucMsgData++ = pstEncodeData->u.stRemoteCtrlRsp.ucKeyVersion;
    (*pusMsgDataLen)++;

    /* reserved field */
    TAF_XCALL_FillReservedFld(pucMsgData,pusMsgDataLen);

    return TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
}

#ifdef VOS_WIN32

/**********************************************
�������� TAF_XCALL_EncKeyRspMsg
���ܣ���װ��Կ��Ӧ��User Data��
Input��TAF_XCALL_KMC_MSG_STRU *pstEncodeData�ض��ṹ�Ĵ��������ݣ�
Output��VOS_UINT8 *pucMsgData ��װ���User Data��
        VOS_UINT16 *pusMsgDataLen��װ���User Data�ĳ���

���أ�����ľ�����ֵ
 1.����:      20151026
   ����:      l00359089
   �޸����ݣ��½�
*****************************************************/

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncKeyRspMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
)
{
    TAF_XCALL_KMC_MSG_KEY_RSP_STRU       stKeyRsp;

    PS_MEM_SET(&stKeyRsp, 0, sizeof(stKeyRsp));
    PS_MEM_CPY(&stKeyRsp,&pstEncodeData->u.stKeyRsp,sizeof(stKeyRsp));

    /* ���ĳ���. */
    *pucMsgData++  = (VOS_UINT8)(stKeyRsp.stCipher.usCipherLen & 0x00FF);
    (*pusMsgDataLen)++;

     /* ���� */
    (*pusMsgDataLen) += (VOS_UINT8)(stKeyRsp.stCipher.usCipherLen & 0x00FF);

    if (TAF_XCALL_KMC_MSG_WMS_CDMA_USER_DATA_MAX <= (*pusMsgDataLen))
    {
        return TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENC_LEN_OVER_MAX_ERR;
    }

    PS_MEM_CPY(pucMsgData, stKeyRsp.stCipher.aucCipher, stKeyRsp.stCipher.usCipherLen);
    pucMsgData       += stKeyRsp.stCipher.usCipherLen;

    /* ǩ����Ϣ���� */
    *pucMsgData++  = stKeyRsp.stSignInfo.ucSignInfoLen;
    (*pusMsgDataLen)++;

    (*pusMsgDataLen) += stKeyRsp.stSignInfo.ucSignInfoLen;

    if (TAF_XCALL_KMC_MSG_WMS_CDMA_USER_DATA_MAX <
        (*pusMsgDataLen + TAF_XCALL_KMC_MSG_RSVD1_BYTES + TAF_XCALL_KMC_MSG_RSVD1_BYTES))
    {
        return TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENC_LEN_OVER_MAX_ERR;
    }

    /* ǩ����Ϣ. */
    PS_MEM_CPY(pucMsgData, stKeyRsp.stSignInfo.aucSignInfo, stKeyRsp.stSignInfo.ucSignInfoLen);
    pucMsgData       += stKeyRsp.stSignInfo.ucSignInfoLen;

    /* reserved field */
    TAF_XCALL_FillReservedFld(pucMsgData,pusMsgDataLen);

    return TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
}

/**********************************************
�������� TAF_XCALL_EncMtEncryptIndMsg
���ܣ���װ���м���֪ͨ��User Data��
Input��TAF_XCALL_KMC_MSG_STRU *pstEncodeData�ض��ṹ�Ĵ��������ݣ�
Output��VOS_UINT8 *pucMsgData ��װ���User Data��
        VOS_UINT16 *pusMsgDataLen��װ���User Data�ĳ���

���أ�����ľ�����ֵ
 1.����:      20151026
   ����:      l00359089
   �޸����ݣ��½�
*****************************************************/

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncMtEncryptIndMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
)
{
    /*���к��볤��*/
    *pucMsgData++  = pstEncodeData->u.stMtEncryptInd.ucRemoteNumberLen;
    (*pusMsgDataLen)++;

    /*���к���*/
    PS_MEM_CPY(pucMsgData, pstEncodeData->u.stMtEncryptInd.aucRemoteNumber, pstEncodeData->u.stMtEncryptInd.ucRemoteNumberLen);
    pucMsgData       += pstEncodeData->u.stMtEncryptInd.ucRemoteNumberLen;
    (*pusMsgDataLen) += pstEncodeData->u.stMtEncryptInd.ucRemoteNumberLen;

    /* reserved field */
    TAF_XCALL_FillReservedFld(pucMsgData,pusMsgDataLen);
    return TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
}

/**********************************************
�������� TAF_XCALL_EncErrIndMsg
���ܣ���װ����֪ͨ��User Data��
Input��TAF_XCALL_KMC_MSG_STRU *pstEncodeData�ض��ṹ�Ĵ��������ݣ�
Output��VOS_UINT8 *pucMsgData ��װ���User Data��
        VOS_UINT16 *pusMsgDataLen��װ���User Data�ĳ���

���أ�����ľ�����ֵ
 1.����:      20151026
   ����:      l00359089
   �޸����ݣ��½�
*****************************************************/

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncErrIndMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
)
{
    *pucMsgData++  = pstEncodeData->u.stErrInd.enErrCause;
    (*pusMsgDataLen)++;

    /* reserved field */
    TAF_XCALL_FillReservedFld(pucMsgData,pusMsgDataLen);
    return TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
}

/**********************************************
�������� TAF_XCALL_EncPubKeyUpdateMsg
���ܣ� ��װ��Կ���µ�User Data��
Input��TAF_XCALL_KMC_MSG_STRU *pstEncodeData�ض��ṹ�Ĵ��������ݣ�
Output��VOS_UINT8 *pucMsgData ��װ���User Data��
        VOS_UINT16 *pusMsgDataLen��װ���User Data�ĳ���

���أ�����ľ�����ֵ
 1.����:      20151026
   ����:      l00359089
   �޸����ݣ��½�
*****************************************************/

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncPubKeyUpdateMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
)
{
    /*KMC��Կ�汾*/
    *pucMsgData++  = pstEncodeData->u.stPubKeyUpdateInd.ucKeyVersion;
    (*pusMsgDataLen)++;

    /*KMC��Կ����*/
    *pucMsgData++  = pstEncodeData->u.stPubKeyUpdateInd.stPubKey.ucKeyLen;
    (*pusMsgDataLen)++;

    /*KMC��Կ*/
    PS_MEM_CPY(pucMsgData,
               pstEncodeData->u.stPubKeyUpdateInd.stPubKey.aucKey,
               pstEncodeData->u.stPubKeyUpdateInd.stPubKey.ucKeyLen);
    pucMsgData       += pstEncodeData->u.stPubKeyUpdateInd.stPubKey.ucKeyLen;
    (*pusMsgDataLen) += pstEncodeData->u.stPubKeyUpdateInd.stPubKey.ucKeyLen;

    /* ǩ����Ϣ���� */
    *pucMsgData++  = pstEncodeData->u.stPubKeyUpdateInd.stSignInfo.ucSignInfoLen;
    (*pusMsgDataLen)++;

    (*pusMsgDataLen) += pstEncodeData->u.stPubKeyUpdateInd.stSignInfo.ucSignInfoLen;

    /* ǩ����Ϣ. */
    PS_MEM_CPY(pucMsgData,
               pstEncodeData->u.stPubKeyUpdateInd.stSignInfo.aucSignInfo,
               pstEncodeData->u.stPubKeyUpdateInd.stSignInfo.ucSignInfoLen);
    pucMsgData     += pstEncodeData->u.stPubKeyUpdateInd.stSignInfo.ucSignInfoLen;

    /* reserved field */
    TAF_XCALL_FillReservedFld(pucMsgData,pusMsgDataLen);

    return TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
}

/**********************************************
�������� TAF_XCALL_EncPubKeyUpdateAckMsg
���ܣ� ��װ��Կ����ȷ�ϵ�User Data��
Input��TAF_XCALL_KMC_MSG_STRU *pstEncodeData�ض��ṹ�Ĵ��������ݣ�
Output��VOS_UINT8 *pucMsgData ��װ���User Data��
        VOS_UINT16 *pusMsgDataLen��װ���User Data�ĳ���

���أ�����ľ�����ֵ
 1.����:      20151026
   ����:      l00359089
   �޸����ݣ��½�
*****************************************************/

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncPubKeyUpdateAckMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
)
{
    PS_MEM_CPY(pucMsgData, pstEncodeData->u.stPubKeyUpdateAck.aucRandomData, TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN);
    pucMsgData       += TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN;
    (*pusMsgDataLen) += TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN;

    /* reserved field */
    TAF_XCALL_FillReservedFld(pucMsgData,pusMsgDataLen);
    return TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
}

/**********************************************
�������� TAF_XCALL_EncRemoteCtrlCmdMsg
���ܣ� ��װԶ�̿���ָ���User Data��
Input��TAF_XCALL_KMC_MSG_STRU *pstEncodeData�ض��ṹ�Ĵ��������ݣ�
Output��VOS_UINT8 *pucMsgData ��װ���User Data��
        VOS_UINT16 *pusMsgDataLen��װ���User Data�ĳ���

���أ�����ľ�����ֵ
 1.����:      20151026
   ����:      l00359089
   �޸����ݣ��½�
*****************************************************/

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncRemoteCtrlCmdMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
)
{
    VOS_UINT8                           ausTmp[4] = {0};

    /*KMC��Կ�汾*/
    *pucMsgData++  = pstEncodeData->u.stRemoteCtrlInd.ucKeyVersion;
    (*pusMsgDataLen)++;

    /*ʱ���*/
    /*Year*/
    ausTmp[0] = (VOS_UINT8)(pstEncodeData->u.stRemoteCtrlInd.stTimeStamp.usYear/1000);
    ausTmp[1] = (VOS_UINT8)((pstEncodeData->u.stRemoteCtrlInd.stTimeStamp.usYear -(ausTmp[0]*1000))/100);
    ausTmp[2] = (VOS_UINT8)((pstEncodeData->u.stRemoteCtrlInd.stTimeStamp.usYear - (ausTmp[0]*1000) - (ausTmp[1]*100))/10);
    ausTmp[3] = (VOS_UINT8)(pstEncodeData->u.stRemoteCtrlInd.stTimeStamp.usYear - (ausTmp[0]*1000) - (ausTmp[1]*100) - (ausTmp[2]*10));
    *pucMsgData++ = ((VOS_UINT8)((ausTmp[0] & 0x0F) << 4)) | ((VOS_UINT8)(ausTmp[1] & 0x0F));
    *pucMsgData++ = ((VOS_UINT8)((ausTmp[2] & 0x0F) << 4)) | ((VOS_UINT8)(ausTmp[3] & 0x0F));

    /*Month*/
    ausTmp[0] = (VOS_UINT8)(pstEncodeData->u.stRemoteCtrlInd.stTimeStamp.usMonth/10);
    ausTmp[1] = (VOS_UINT8)(pstEncodeData->u.stRemoteCtrlInd.stTimeStamp.usMonth - (ausTmp[0]*10));
    *pucMsgData++ = ((VOS_UINT8)((ausTmp[0] & 0x0F) << 4)) | ((VOS_UINT8)(ausTmp[1] & 0x0F));

    /*Day*/
    ausTmp[0] = (VOS_UINT8)(pstEncodeData->u.stRemoteCtrlInd.stTimeStamp.usDay/10);
    ausTmp[1] = (VOS_UINT8)(pstEncodeData->u.stRemoteCtrlInd.stTimeStamp.usDay - (ausTmp[0]*10));
    *pucMsgData++ = ((VOS_UINT8)((ausTmp[0] & 0x0F) << 4)) | ((VOS_UINT8)(ausTmp[1] & 0x0F));

    /*Hour*/
    ausTmp[0] = (VOS_UINT8)(pstEncodeData->u.stRemoteCtrlInd.stTimeStamp.usHour/10);
    ausTmp[1] = (VOS_UINT8)(pstEncodeData->u.stRemoteCtrlInd.stTimeStamp.usHour - (ausTmp[0]*10));
    *pucMsgData++ = ((VOS_UINT8)((ausTmp[0] & 0x0F) << 4)) | ((VOS_UINT8)(ausTmp[1] & 0x0F));

    /*Minute*/
    ausTmp[0] = (VOS_UINT8)(pstEncodeData->u.stRemoteCtrlInd.stTimeStamp.usMinute/10);
    ausTmp[1] = (VOS_UINT8)(pstEncodeData->u.stRemoteCtrlInd.stTimeStamp.usMinute - (ausTmp[0]*10));
    *pucMsgData++ = ((VOS_UINT8)((ausTmp[0] & 0x0F) << 4)) | ((VOS_UINT8)(ausTmp[1] & 0x0F));

    /*Second*/
    ausTmp[0] = (VOS_UINT8)(pstEncodeData->u.stRemoteCtrlInd.stTimeStamp.usSecond/10);
    ausTmp[1] = (VOS_UINT8)(pstEncodeData->u.stRemoteCtrlInd.stTimeStamp.usSecond - (ausTmp[0]*10));
    *pucMsgData++ = ((VOS_UINT8)((ausTmp[0] & 0x0F) << 4)) | ((VOS_UINT8)(ausTmp[1] & 0x0F));

    (*pusMsgDataLen) += TAF_XCALL_KMC_MSG_TIME_STAMP_LEN;

    /*Զ�̿���ָ������*/
    *pucMsgData++  = pstEncodeData->u.stRemoteCtrlInd.enRomoteCtrlCmdType;
    (*pusMsgDataLen)++;

    /* ǩ����Ϣ���� */
    *pucMsgData++  = pstEncodeData->u.stRemoteCtrlInd.stSignInfo.ucSignInfoLen;
    (*pusMsgDataLen)++;

    /* ǩ����Ϣ. */
    (*pusMsgDataLen) += pstEncodeData->u.stRemoteCtrlInd.stSignInfo.ucSignInfoLen;

    PS_MEM_CPY(pucMsgData,
               pstEncodeData->u.stRemoteCtrlInd.stSignInfo.aucSignInfo,
               pstEncodeData->u.stRemoteCtrlInd.stSignInfo.ucSignInfoLen);
    pucMsgData += pstEncodeData->u.stRemoteCtrlInd.stSignInfo.ucSignInfoLen;

    /* reserved field */
    TAF_XCALL_FillReservedFld(pucMsgData,pusMsgDataLen);

    return TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
}
#endif
/**********************************************
�������� TAF_XCALL_EncodeUserData
���ܣ���װUser Data��
Input��TAF_XCALL_KMC_MSG_STRU *pstEncodeData�ض��ṹ�Ĵ��������ݣ�
Output��VOS_UINT8 *pucMsgData ��װ���User Data��
        VOS_UINT16 *pusMsgDataLen��װ���User Data�ĳ���
���أ�����ľ�����ֵ
 1.����:      20151021
   ����:      l00359089
   �޸����ݣ��½�
*****************************************************/

TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32 TAF_XCALL_EncodeKmcMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstEncodeData,
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                         *pusMsgDataLen
)
{
    TAF_XCALL_KMC_MSG_PROCESS_RSLT_ENUM_UINT32              enRst;
    VOS_UINT8                                               i;

    TAF_XCALL_MNTN_LogKmcEncMsg(pstEncodeData);

    enRst = TAF_XCALL_KMC_MSG_PROCESS_RSLT_MSG_TYPE_UNKNOWN;

    /* specific msg identifier, default value: 0x00. */
    *pucMsgData++ = TAF_XCALL_KMC_MSG_SPECIAL_SMS_ID;

    /* extended control field, default value: 0x00,0x00*/
    *pucMsgData++ = TAF_XCALL_KMC_MSG_EXT_CTRL_FIELD1;
    *pucMsgData++ = TAF_XCALL_KMC_MSG_EXT_CTRL_FIELD2;

    /*msg type */
    *pucMsgData++ = pstEncodeData->enSmsType;

    *pusMsgDataLen = TAF_XCALL_KMC_MSG_HEADER_LEN;

    for (i = 0; i < (sizeof(g_astTafXcallEncKmcMsgProcTab)/sizeof(TAF_XCALL_ENC_KMC_MSG_PROC_STRU)); i++)
    {
        if ((pstEncodeData->enSmsType & 0x000000FF) == g_astTafXcallEncKmcMsgProcTab[i].ulMsgType)
        {
            enRst = g_astTafXcallEncKmcMsgProcTab[i].pProcMsgFunc(pstEncodeData, pucMsgData, pusMsgDataLen);
            break;
        }
    }

    return enRst;
}

#endif

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


