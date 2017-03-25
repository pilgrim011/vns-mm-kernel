
/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallDecKmcMsg.c
  �� �� ��   : ����
  ��    ��   : l00359089
  ��������   : 2015��10��20��
  ��������   : Taf X Call ��KMC��user data���н���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��10��20��
    ��    ��   : l00359089
    �޸�����   : �����ļ� for CDMA 1X Iteration 19
******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXCallDecKmcMsg.h"
#include "TafLog.h"
#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_DEC_KMC_MSG_C
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************
�������� TAF_XCALL_ConvertBcdToDecimal;
���ܣ���bcd��ʽ����ת����ʮ����
Input��
        VOS_UINT8                                              *pucSrcData,
        VOS_UINT16                                             *pusDestData
Output����
���أ�  VOS_UINT32
        VOS_FALSE  ת��ʧ��
        VOS_TRUE   ת���ɹ�
 ����:      20151102
 ����:      l00359089
 �޸����ݣ��½�
*******************************************/
VOS_UINT32 TAF_XCALL_ConvertBcdToDecimal(
    VOS_UINT8                                              *pucSrcData,
    VOS_UINT16                                             *pusDestData
)
{
    VOS_UINT8                           ucHigh;
    VOS_UINT8                           ucLow;

    ucHigh                              =0x00;
    ucLow                               =0x00;

    ucHigh = (VOS_UINT8)(((*pucSrcData) & 0xF0) >> 4);
    ucLow  = (*pucSrcData) & 0x0F;

    /*���BCD��ʽ�е����ֲ���0-9,�򷵻�ʧ��*/
    if ((0x09 < ucHigh)
     || (0x09 < ucLow))
    {
        return VOS_FALSE;
    }

    *pusDestData = ucHigh * 10 + ucLow;

    return VOS_TRUE;
}
/*****************************************
�������� TAF_XCALL_ConvertBcdTimeStampToDecimalTimeStamp;
���ܣ�   ��BCD��ʽ��ʱ���ת����ʮ���Ƶ�ʱ���
Input��
        VOS_UINT8                                              *pucSrcData,
        TAF_STD_TIME_ZONE_TYPE_STRU                            *pstTimeStamp
Output����
���أ�  VOS_UINT32
        VOS_FALSE  ת��ʧ��
        VOS_TRUE   ת���ɹ�
 ����:      20151102
 ����:      l00359089
 �޸����ݣ��½�
*******************************************/
VOS_UINT32 TAF_XCALL_ConvertBcdTimeStampToDecimalTimeStamp(
    VOS_UINT8                                              *pucSrcData,
    TAF_STD_TIME_ZONE_TYPE_STRU                            *pstTimeStamp
)
{
    VOS_UINT16                          usYearTmp;

    usYearTmp = 0;

    if (VOS_FALSE == TAF_XCALL_ConvertBcdToDecimal(pucSrcData, &usYearTmp))
    {
        return VOS_FALSE;
    }

    pstTimeStamp->usYear   = (VOS_UINT16)(usYearTmp * 100);
    pucSrcData++;
    usYearTmp = 0;

    if (VOS_FALSE == TAF_XCALL_ConvertBcdToDecimal(pucSrcData, &usYearTmp))
    {
        return VOS_FALSE;
    }

    pstTimeStamp->usYear   +=usYearTmp;
    pucSrcData++;

    if (VOS_FALSE == TAF_XCALL_ConvertBcdToDecimal(pucSrcData,
                                                   &pstTimeStamp->usMonth))
    {
        return VOS_FALSE;
    }

    pucSrcData++;

    if (VOS_FALSE == TAF_XCALL_ConvertBcdToDecimal(pucSrcData,
                                                   &pstTimeStamp->usDay))
    {
        return VOS_FALSE;
    }

    pucSrcData++;

    if (VOS_FALSE == TAF_XCALL_ConvertBcdToDecimal(pucSrcData,
                                                   &pstTimeStamp->usHour))
    {
        return VOS_FALSE;
    }

    pucSrcData++;

    if (VOS_FALSE == TAF_XCALL_ConvertBcdToDecimal(pucSrcData,
                                                   &pstTimeStamp->usMinute))
    {
        return VOS_FALSE;
    }

    pucSrcData++;

    if (VOS_FALSE == TAF_XCALL_ConvertBcdToDecimal(pucSrcData,
                                                   &pstTimeStamp->usSecond))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
/*****************************************
�������� TAF_XCALL_DecKeyRspMsg;
���ܣ���� User Data��
Input��VOS_UINT8 *pucMsgData�� ����ֵ�User Data��
        VOS_UINT16 usMsgDataLen�� User Data�ĳ���
        VOS_UINT8 *pucdata_ptr�� ����ֵ�User Data����ʱָ�룻
Output��TAF_XCALL_KMC_MSG_STRU *pstDecodedData���User Data���γɵ��ض��ṹ�����ݣ�
���أ���
 ����:      20151020
 ����:      l00359089
 �޸����ݣ��½�
*******************************************/
VOS_VOID TAF_XCALL_DecKeyRspMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
)
{
    TAF_XCALL_KMC_MSG_KEY_RSP_STRU     *pstKeyRsp = VOS_NULL_PTR;

    pstKeyRsp = &pstDecodedData->u.stKeyRsp;

    /*���ĳ���*/
    pstKeyRsp->stCipher.usCipherLen = ((VOS_UINT16)(*pucdata_ptr++)) & 0x00FF;

    /* ���ĳ��ȵ���0����������ֵ ���� ��ַ���� User Data �ķ�Χ
    ����û�м��뱣���ֶγ��ȵ��ж�,����Ϊ������Ϣ���������û����䱣���ֶ�,���жϱ����ֶγ���,�ͻᵼ�½���ʧ��.
    ����,�ٺ����Ĵ�����,�����ֶ�Ŀǰû���õ�*/
    if ((0 == pstKeyRsp->stCipher.usCipherLen)
     || ((pucdata_ptr + pstKeyRsp->stCipher.usCipherLen) >= (pucMsgData + usMsgDataLen)))
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_CIPHER_LEN_ERR;
        return ;
    }

    /*����*/
    PS_MEM_CPY(pstKeyRsp->stCipher.aucCipher, pucdata_ptr, pstKeyRsp->stCipher.usCipherLen);
    pucdata_ptr = pucdata_ptr + pstKeyRsp->stCipher.usCipherLen;

    /*KMCǩ����Ϣ����*/
    pstKeyRsp->stSignInfo.ucSignInfoLen = *pucdata_ptr++;

    /* ǩ����Ϣ���ȴ�������ֵ ���� ��ַ���� User Data �ķ�Χ */
    if ((0 == pstKeyRsp->stSignInfo.ucSignInfoLen)
     || ((pucdata_ptr + pstKeyRsp->stSignInfo.ucSignInfoLen) > (pucMsgData + usMsgDataLen)))
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_SIGN_INFO_LEN_ERR;
        return ;
    }

    /* ǩ����Ϣ*/
    PS_MEM_CPY(pstKeyRsp->stSignInfo.aucSignInfo, pucdata_ptr, pstKeyRsp->stSignInfo.ucSignInfoLen);
    pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
}
/*****************************************
��������TAF_XCALL_DecMtEncryptIndMsg
���ܣ���� User Data��
Input��VOS_UINT8 *pucMsgData�� ����ֵ�User Data��
        VOS_UINT16 usMsgDataLen�� User Data�ĳ���
        VOS_UINT8 *pucdata_ptr�� ����ֵ�User Data����ʱָ�룻
Output��TAF_XCALL_KMC_MSG_STRU *pstDecodedData���User Data���γɵ��ض��ṹ�����ݣ�
���أ���
 ����:      20151020
 ����:      l00359089
 �޸����ݣ��½�
*******************************************/
VOS_VOID TAF_XCALL_DecMtEncryptIndMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
)
{
    /*���к��볤��*/
    pstDecodedData->u.stMtEncryptInd.ucRemoteNumberLen = *pucdata_ptr++;

    /* ���к��볤�ȵ���0����������ֵ ���� ��ַ���� User Data �ķ�Χ */
    if ((0 == pstDecodedData->u.stMtEncryptInd.ucRemoteNumberLen)
     || (TAF_XCALL_KMC_MSG_MAX_REMOTE_NUMBER_LEN < pstDecodedData->u.stMtEncryptInd.ucRemoteNumberLen)
     || ((pucdata_ptr + pstDecodedData->u.stMtEncryptInd.ucRemoteNumberLen) > (pucMsgData + usMsgDataLen)))
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_REMOTE_NUMBER_LEN_ERR;
        return ;
    }

    /*Ϊ�˿��Ǽ����ԣ�������Ȳ�����6���ֽڣ���ӡһ���澯��Ϣ���ڳ�����ɷ�Χ�ڣ��ɼ�����������*/
    if (TAF_XCALL_KMC_MSG_MAX_REMOTE_NUMBER_LEN > pstDecodedData->u.stMtEncryptInd.ucRemoteNumberLen)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_XCALL_DecMtEncryptIndMsg():RemoteNumberLen < Max len (6)!");
    }

    PS_MEM_CPY(pstDecodedData->u.stMtEncryptInd.aucRemoteNumber, pucdata_ptr, pstDecodedData->u.stMtEncryptInd.ucRemoteNumberLen);

    pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
}
/*****************************************
��������TAF_XCALL_DecErrIndMsg
���ܣ���� User Data��
Input��VOS_UINT8 *pucMsgData�� ����ֵ�User Data��
        VOS_UINT16 usMsgDataLen�� User Data�ĳ���
        VOS_UINT8 *pucdata_ptr�� ����ֵ�User Data����ʱָ�룻
Output��TAF_XCALL_KMC_MSG_STRU *pstDecodedData���User Data���γɵ��ض��ṹ�����ݣ�
���أ���
 ����:      20151020
 ����:      l00359089
 �޸����ݣ��½�
*******************************************/
VOS_VOID TAF_XCALL_DecErrIndMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
)
{
    /*����ԭ��ֵ */
    pstDecodedData->u.stErrInd.enErrCause = *pucdata_ptr;

    if (TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_BUTT <= pstDecodedData->u.stErrInd.enErrCause)
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_ERR_IND_CAUSE_ERR;
        return ;
    }

    pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
}
/*****************************************
��������TAF_XCALL_DecPubKeyUpdateReqMsg
���ܣ���� User Data��
Input��VOS_UINT8 *pucMsgData�� ����ֵ�User Data��
        VOS_UINT16 usMsgDataLen�� User Data�ĳ���
        VOS_UINT8 *pucdata_ptr�� ����ֵ�User Data����ʱָ�룻
Output��TAF_XCALL_KMC_MSG_STRU *pstDecodedData���User Data���γɵ��ض��ṹ�����ݣ�
���أ���
 ����:      20151020
 ����:      l00359089
 �޸����ݣ��½�
*******************************************/
VOS_VOID TAF_XCALL_DecPubKeyUpdateMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
)
{
    if (TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_REQ_HEADER_LEN >= usMsgDataLen)
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_MSG_NOT_ENOUGH;
        return ;
    }

    /*KMC��Կ�汾*/
    pstDecodedData->u.stPubKeyUpdateInd.ucKeyVersion        = *pucdata_ptr++;

    /*KMC��Կ����*/
    pstDecodedData->u.stPubKeyUpdateInd.stPubKey.ucKeyLen            = *pucdata_ptr++;

    /* ��Կ���ȴ�������ֵ ���� ��ַ���� User Data �ķ�Χ */
    if ((0 == pstDecodedData->u.stPubKeyUpdateInd.stPubKey.ucKeyLen)
     || (TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN < pstDecodedData->u.stPubKeyUpdateInd.stPubKey.ucKeyLen)
     || ((pucdata_ptr + pstDecodedData->u.stPubKeyUpdateInd.stPubKey.ucKeyLen) >= (pucMsgData + usMsgDataLen)))
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_PUB_KEY_LEN_ERR;
        return ;
    }

    PS_MEM_CPY(pstDecodedData->u.stPubKeyUpdateInd.stPubKey.aucKey,
               pucdata_ptr,
               pstDecodedData->u.stPubKeyUpdateInd.stPubKey.ucKeyLen);
    pucdata_ptr = pucdata_ptr + pstDecodedData->u.stPubKeyUpdateInd.stPubKey.ucKeyLen;

    /*KMCǩ����Ϣ����*/
    pstDecodedData->u.stPubKeyUpdateInd.stSignInfo.ucSignInfoLen       = *pucdata_ptr++;

    /* ǩ����Ϣ���ȵ���0����������ֵ ���� ��ַ���� User Data �ķ�Χ */
    if ((0 == pstDecodedData->u.stPubKeyUpdateInd.stSignInfo.ucSignInfoLen )
     || ((pucdata_ptr + pstDecodedData->u.stPubKeyUpdateInd.stSignInfo.ucSignInfoLen) > (pucMsgData + usMsgDataLen)))
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_SIGN_INFO_LEN_ERR;
        return ;
    }

    PS_MEM_CPY(pstDecodedData->u.stPubKeyUpdateInd.stSignInfo.aucSignInfo,
               pucdata_ptr,
               pstDecodedData->u.stPubKeyUpdateInd.stSignInfo.ucSignInfoLen);
    pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
}
/*****************************************
�������� TAF_XCALL_DecPubKeyUpdateAckMsg
���ܣ���� User Data��
Input��VOS_UINT8 *pucMsgData�� ����ֵ�User Data��
       VOS_UINT16 usMsgDataLen�� User Data�ĳ���
        VOS_UINT8 *pucdata_ptr�� ����ֵ�User Data����ʱָ�룻
Output��TAF_XCALL_KMC_MSG_STRU *pstDecodedData���User Data���γɵ��ض��ṹ�����ݣ�
���أ���
 ����:      20151020
 ����:      l00359089
 �޸����ݣ��½�
*******************************************/
VOS_VOID TAF_XCALL_DecPubKeyUpdateAckMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
)
{
    if ((TAF_XCALL_KMC_MSG_HEADER_LEN + TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN) > usMsgDataLen)
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_MSG_NOT_ENOUGH;
        return ;
    }

    /*�����*/
    PS_MEM_CPY(pstDecodedData->u.stPubKeyUpdateAck.aucRandomData, pucdata_ptr, TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN);
    pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
}
/*****************************************
�������� TAF_XCALL_DecRemoteCtrlCmdMsg
���ܣ���� User Data��
Input��VOS_UINT8 *pucMsgData�� ����ֵ�User Data��
        VOS_UINT16 usMsgDataLen�� User Data�ĳ���
        VOS_UINT8 *pucdata_ptr�� ����ֵ�User Data����ʱָ�룻
Output��TAF_XCALL_KMC_MSG_STRU *pstDecodedData���User Data���γɵ��ض��ṹ�����ݣ�
���أ���
 ����:      20151020
 ����:      l00359089
 �޸����ݣ��½�
*******************************************/
VOS_VOID TAF_XCALL_DecRemoteCtrlCmdMsg(
    VOS_UINT8                                              *pucMsgData,
    VOS_UINT16                                              usMsgDataLen,
    VOS_UINT8                                              *pucdata_ptr,
    TAF_XCALL_KMC_MSG_STRU                                 *pstDecodedData
)
{

    if (TAF_XCALL_KMC_MSG_REMOTE_CTRL_HEADER_LEN > usMsgDataLen)
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_MSG_NOT_ENOUGH;
        return ;
    }

    /*KMC��Կ�汾*/
    pstDecodedData->u.stRemoteCtrlInd.ucKeyVersion = *pucdata_ptr++;

    /*ʱ���*/
    if ( VOS_FALSE == TAF_XCALL_ConvertBcdTimeStampToDecimalTimeStamp(pucdata_ptr,
                                                                      &pstDecodedData->u.stRemoteCtrlInd.stTimeStamp))
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_TIME_STAMP_ERR;
        return ;
    }

    pucdata_ptr += TAF_XCALL_KMC_MSG_TIME_STAMP_LEN;

    /*Զ�̿���ָ������*/
    pstDecodedData->u.stRemoteCtrlInd.enRomoteCtrlCmdType   = *pucdata_ptr++;

    if (TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_BUTT <= pstDecodedData->u.stRemoteCtrlInd.enRomoteCtrlCmdType)
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_ROMOTE_CTRL_CMD_TYPE_ERR;
        return ;
    }

     /*KMCǩ����Ϣ����*/
    pstDecodedData->u.stRemoteCtrlInd.stSignInfo.ucSignInfoLen = *pucdata_ptr++;


    /* ǩ����Ϣ���ȵ���0����������ֵ ���� ��ַ���� User Data �ķ�Χ */
    if ((0 == pstDecodedData->u.stRemoteCtrlInd.stSignInfo.ucSignInfoLen)
     || ((pucdata_ptr + pstDecodedData->u.stRemoteCtrlInd.stSignInfo.ucSignInfoLen) > (pucMsgData + usMsgDataLen)))
    {
        pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_SIGN_INFO_LEN_ERR;
        return ;
    }

    PS_MEM_CPY(pstDecodedData->u.stRemoteCtrlInd.stSignInfo.aucSignInfo,
               pucdata_ptr,
               pstDecodedData->u.stRemoteCtrlInd.stSignInfo.ucSignInfoLen);
    pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS;
}


/*****************************************
�������� TAF_XCALL_DecodeKmcMsg
���ܣ���� User Data��
Input��VOS_UINT8 *pucUserData�� ����ֵ�User Data��
        VOS_UINT16 usUserDataLen�� User Data�ĳ���
Output��TAF_XCALL_KMC_MSG_STRU *pstDecodedData���User Data���γɵ��ض��ṹ�����ݣ�
���أ���
 ����:      20151020
 ����:      l00359089
 �޸����ݣ��½�
*******************************************/
VOS_VOID TAF_XCALL_DecodeKmcMsg(
    VOS_UINT8                          *pucMsgData,
    VOS_UINT16                          usMsgDataLen,
    TAF_XCALL_KMC_MSG_STRU             *pstDecodedData
)
{
    VOS_UINT8                          *pucdata_ptr = VOS_NULL_PTR;

    if (TAF_XCALL_KMC_MSG_HEADER_LEN > usMsgDataLen)
    {
        pstDecodedData->enRslt    = TAF_XCALL_KMC_MSG_PROCESS_RSLT_MSG_NOT_ENOUGH;
        pstDecodedData->enSmsType = TAF_XCALL_KMC_MSG_TYPE_UNKNOWN;
        return;
    }

    pucdata_ptr = pucMsgData ;

    /* specific msg identifier*/
    pstDecodedData->ucSpecSmsID = *pucdata_ptr++;

    /* extended control field*/
    PS_MEM_CPY(pstDecodedData->aucExtCtrlField, pucdata_ptr, TAF_XCALL_KMC_MSG_EXT_CTRL_BYTES);
    pucdata_ptr = pucdata_ptr+ TAF_XCALL_KMC_MSG_EXT_CTRL_BYTES;

    /*��Ϣ����*/
    pstDecodedData->enSmsType = *pucdata_ptr++;

    switch(pstDecodedData->enSmsType)
    {
        case TAF_XCALL_KMC_MSG_TYPE_MO_KEY_RSP:
        case TAF_XCALL_KMC_MSG_TYPE_MT_KEY_RSP:
        {
            TAF_XCALL_DecKeyRspMsg(pucMsgData, usMsgDataLen, pucdata_ptr, pstDecodedData);
            break;
        }
        case TAF_XCALL_KMC_MSG_TYPE_MT_ENCRYPT_IND:
        {
            TAF_XCALL_DecMtEncryptIndMsg(pucMsgData, usMsgDataLen, pucdata_ptr, pstDecodedData);
            break;
        }
        case TAF_XCALL_KMC_MSG_TYPE_ERR_IND:
        {
            TAF_XCALL_DecErrIndMsg(pucMsgData, usMsgDataLen, pucdata_ptr, pstDecodedData);
            break;
        }
        case TAF_XCALL_KMC_MSG_TYPE_PUB_KEY_UPDATE_IND:
        {
            TAF_XCALL_DecPubKeyUpdateMsg(pucMsgData, usMsgDataLen, pucdata_ptr, pstDecodedData);
            break;
        }
        case TAF_XCALL_KMC_MSG_TYPE_PUB_KEY_UPDATE_ACK:
        {
            TAF_XCALL_DecPubKeyUpdateAckMsg(pucMsgData, usMsgDataLen, pucdata_ptr, pstDecodedData);
            break;
        }
        case TAF_XCALL_KMC_MSG_TYPE_ROMOTE_CTRL_CMD_IND:
        {
            TAF_XCALL_DecRemoteCtrlCmdMsg(pucMsgData, usMsgDataLen, pucdata_ptr, pstDecodedData);
            break;
        }
        default:
        {
            pstDecodedData->enRslt = TAF_XCALL_KMC_MSG_PROCESS_RSLT_MSG_TYPE_UNKNOWN;
            break;
        }
    }

}

#endif

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */














































