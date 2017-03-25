/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallProcEccSrv.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2015��10��21��
  ��������   : TAF X CALL����ECCҵ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXCallProcEccSrv.h"
#include "cprocstime.h"
#include "TafStdlib.h"
#include "TafLog.h"
#include "TafXCallMntn.h"
#include "TafXCallSndApp.h"
#include "TafXCallSndXsms.h"
#include "TafXCallEccCipher.h"
#include "TafXCallEncKmcMsg.h"
#include "TafXCallSndCttf.h"
#include "taf_xcall_xsms_pif.h"
#include "TafXCallProcNvim.h"
#include "TafXCallSndXcc.h"
#include "TafSdcCtx.h"
#include "TafXCallEccCipher.h"
#include "TafSdcCtx.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_PROC_ECC_SRV_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/***************************************************************************************************
 * �ܻ��¼������
 * ע: �¼�������У��¼������ǰ���ö�ٶ����˳����Ҵ�����������¼������밴��ö�����͵Ĵ�С�ŵ�
 *     ���ж�Ӧλ��!!!
 **************************************************************************************************/
TAF_XCALL_ECC_EVENT_PROC_STRU  g_astTafXcallVoiceEncEventProcTab[TAF_XCALL_VOICE_ENC_MSG_EVENT_MAX] =
{
    /* APP��Ϣ�¼����� */
    {TAF_XCALL_APP_MSG_EVENT_ENC_VOICE_REQ,                     TAF_XCALL_ProcVoiceEncEventAppEncVoiceReq        },
    {TAF_XCALL_APP_MSG_EVENT_ORIG_REQ,                          TAF_XCALL_ProcVoiceEncEventAppOrigReq            },
    {TAF_XCALL_APP_MSG_EVENT_HANG_UP_REQ,                       TAF_XCALL_ProcVoiceEncEventAppHangUpReq          },

    /* KMC��Ϣ�¼� */
    {TAF_XCALL_KMC_MSG_EVENT_MO_KEY_RSP,                        TAF_XCALL_ProcVoiceEncEventKmcMoKeyRsp           },
    {TAF_XCALL_KMC_MSG_EVENT_MT_ENCRYPT_IND,                    TAF_XCALL_ProcVoiceEncEventKmcMtEncryptInd       },
    {TAF_XCALL_KMC_MSG_EVENT_MT_KEY_RSP,                        TAF_XCALL_ProcVoiceEncEventKmcMtKeyRsp           },
    {TAF_XCALL_KMC_MSG_EVENT_ERR_IND,                           TAF_XCALL_ProcVoiceEncEventKmcErrInd             },

    /* XCC��Ϣ�¼����� */
    {TAF_XCALL_XCC_MSG_EVENT_INCOMING_CALL_IND,                 TAF_XCALL_ProcVoiceEncEventIncomingCallInd       },
    {TAF_XCALL_XCC_MSG_EVENT_DISC_IND,                          TAF_XCALL_ProcVoiceEncEventXccDiscInd            },
    {TAF_XCALL_XCC_MSG_EVENT_TCH_ASSIGN_CMPL_IND,               TAF_XCALL_ProcVoiceEncEventXccTchAssignCmplInd   },
    {TAF_XCALL_XCC_MSG_EVENT_ECC_SERVICE_CNF,                   TAF_XCALL_ProcVoiceEncEventXccEccServiceCnf      },
    {TAF_XCALL_XCC_MSG_EVENT_ANSWER_CALL_CNF,                   TAF_XCALL_ProcVoiceEncEventXccAnswerCnf          },

    /* XSMS��Ϣ�¼� */
    {TAF_XCALL_XSMS_MSG_EVENT_ENC_VOICE_XSMS_SEND_CNF,           TAF_XCALL_ProcVoiceEncEventXsmsSendCnf          },

    /* ��ʱ���¼� */
    {TAF_XCALL_TIMER_MSG_EVENT_WAIT_ORIG_REQ,                   TAF_XCALL_ProcVoiceEncEventTimerWaitOrigReq      },
    {TAF_XCALL_TIMER_MSG_EVENT_DELAY_SEND_ENCRYPT_REQ,          TAF_XCALL_ProcVoiceEncEventTimerDelaySendEncReq  },
    {TAF_XCALL_TIMER_MSG_EVENT_TX01,                            TAF_XCALL_ProcVoiceEncEventTimerTx01             },
    {TAF_XCALL_TIMER_MSG_EVENT_TX02,                            TAF_XCALL_ProcVoiceEncEventTimerTx02             },

    /* �ڲ������¼� */
    {TAF_XCALL_XCC_MSG_EVENT_INT_CALL_REL_IND,                  TAF_XCALL_ProcVoiceEncEventIntCallRelInd         }
};

/***************************************************************************************************
 * ��Կ�����¼��������
 * ע: �¼�������У��¼������ǰ���ö�ٶ����˳����Ҵ�����������¼������밴��ö�����͵Ĵ�С�ŵ�
 *     ���ж�Ӧλ��!!!
 **************************************************************************************************/
TAF_XCALL_ECC_EVENT_PROC_STRU  g_astTafXcallPubKeyEventProcTab[TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_MAX] =
{
    /* KMC��Ϣ�¼� */
    {TAF_XCALL_KMC_MSG_EVENT_PUB_KEY_UPDATE_IND,                TAF_XCALL_ProcPubKeyEventKmcUpdateInd              },
    {TAF_XCALL_KMC_MSG_EVENT_PUB_KEY_UPDATE_ACK,                TAF_XCALL_ProcPubKeyEventKmcUpdateAck              },

    /* XSMS��Ϣ�¼� */
    {TAF_XCALL_XCC_MSG_EVENT_PUB_KEY_UPDATE_XSMS_SEND_CNF,      TAF_XCALL_ProcPubKeyEventXsmsSendCnf               },

    /* ��ʱ���¼� */
    {TAF_XCALL_TIMER_MSG_EVENT_PUB_KEY_UPDATE_WAIT_ACK,         TAF_XCALL_ProcPubKeyEventTimerWaitAck              }
};

/***************************************************************************************************
 * Զ�̿��Ʋ����¼������
 * ע: �¼�������У��¼������ǰ���ö�ٶ����˳����Ҵ�����������¼������밴��ö�����͵Ĵ�С�ŵ�
 *     ���ж�Ӧλ��!!!
 **************************************************************************************************/
TAF_XCALL_ECC_EVENT_PROC_STRU  g_astTafXcallRemoteCtrlEventProcTab[TAF_XCALL_REMOTE_CTRL_MSG_EVENT_MAX] =
{
    /* APP��Ϣ�¼����� */
    {TAF_XCALL_APP_MSG_EVENT_REMOTE_CTRL_ANSWER_REQ,            TAF_XCALL_ProcRemoteCtrlEventAppRemoteCtrlAnswerReq  },

    /* KMC��Ϣ�¼����� */
    {TAF_XCALL_KMC_MSG_EVENT_ROMOTE_CTRL_CMD_IND,               TAF_XCALL_ProcRemoteCtrlEventKmcRemoteCtrlCmdInd     },

    /* XSMS��Ϣ�¼� */
    {TAF_XCALL_XCC_MSG_EVENT_ROMOTE_CTRL_XSMS_SEND_CNF,         TAF_XCALL_ProcRemoteCtrlEventXsmsSendCnf},

    {TAF_XCALL_TIMER_MSG_EVENT_REMOTE_CTRL_WAIT_AP_ANSWER,      TAF_XCALL_ProcRemoteCtrlEventTimerWaitApAnswer}

};

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_XCALL_FillAdditionalInfo
 ��������  : ���KMC������Ϣ
 �������  : pstKmcMsg -- KMC��Ϣ�ṹ��ַ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_FillAdditionalInfo(
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg
)
{
    VOS_INT32                           lSid;
    VOS_INT32                           lNid;
    VOS_UINT16                          usBaseId;

    lSid            = TAF_SDC_Get1xSid();
    lNid            = TAF_SDC_Get1xNid();
    usBaseId        = TAF_SDC_Get1xBaseId();

    /* �����Ƿ�������丽����Ϣ  */

    /*����Э��������������

    "������Ϣ�ֶΰ������ն˵�ǰ���ε������SID��NID��BSID����������
    �⼸��������˳��Ϊ�� SID ��8bits+SID ��8bis+NID ��8bits+NID ��8bits+BSID ��8bits+BSID��8bits"

    ����ֻ�������ε�ʱ����丨����Ϣ�ֶ�*/
    if (TAF_SDC_SYS_ROAMING_STATUS_OFF == TAF_SDC_Get1xRoamingFlag())
    {
        pstKmcMsg->u.stKeyReq.stAdditionalInfo.usBsid               = 0;
        pstKmcMsg->u.stKeyReq.stAdditionalInfo.usNid                = 0;
        pstKmcMsg->u.stKeyReq.stAdditionalInfo.usSid                = 0;
    }
    else
    {
        pstKmcMsg->u.stKeyReq.stAdditionalInfo.usBsid               = usBaseId;
        pstKmcMsg->u.stKeyReq.stAdditionalInfo.usNid                = (lNid & 0x0000FFFF);
        pstKmcMsg->u.stKeyReq.stAdditionalInfo.usSid                = (lSid & 0x0000FFFF);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_FillKmcReqMsgTempPubKey
 ��������  : ���KMC REQ��ʱ��Կ��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_FillKmcReqMsgTempPubKey(
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg,
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx
)
{
    /* �����ʱ��Կ��Ϣ */
    pstKmcMsg->u.stKeyReq.stTmpPubKey.ucKeyLen = TAF_XCALL_MIN(pstKsNegoCtx->stTmpPubKey.ucKeyLen,
                                                               TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN);

    PS_MEM_CPY(&(pstKmcMsg->u.stKeyReq.stTmpPubKey.aucKey[0]),
               &(pstKsNegoCtx->stTmpPubKey.aucKey[0]),
               pstKsNegoCtx->stTmpPubKey.ucKeyLen);

    /* ��乫Կ�汾�� */
    pstKmcMsg->u.stKeyReq.ucKeyVersion = TAF_XCALL_GetVoiceEncryptPublicKeyAndVersionNumber()->ucVerNum;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ConvertRemoteNumFromStdBcdToKmcBcd
 ��������  : ��Զ�̺���洢��Bcd��ʽת����������Ҫ���BCD��ʽ�ı���
 �������  : VOS_UINT8                          *pucStdBcdContent
             VOS_UINT8                           ucStdBcdLen
             VOS_UINT8                          *pucEncVoiceMsgContent
             VOS_UINT8                           ucEncVoiceMsgLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE: �ɹ�
             VOS_FALSE:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��28��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_ConvertRemoteNumFromStdBcdToKmcBcd(
    VOS_UINT8                          *pucStdBcdContent,
    VOS_UINT8                           ucStdBcdLen,
    VOS_UINT8                          *pucEncVoiceMsgContent,
    VOS_UINT8                           ucEncVoiceMsgLen
)
{
    VOS_UINT32                          i;
    VOS_UINT8                          *pucCurByteAddr  = VOS_NULL_PTR;
    VOS_UINT8                           ucTempByte;
    VOS_UINT8                           ucIsOddNum;

    ucTempByte                          = 0x00;
    i                                   = 0;
    ucIsOddNum                          = VOS_FALSE;

    /* ���ȼ�� */
    if ((ucEncVoiceMsgLen < ucStdBcdLen)
     || (0 == ucStdBcdLen))
    {
        return VOS_FALSE;
    }

    pucCurByteAddr  = pucStdBcdContent + ucStdBcdLen - 1;

    /* ĩλ�ֽ�ΪȫF������ʧ�� */
    if ((0xFF == *pucCurByteAddr)
     || (0x0F == (*pucCurByteAddr & 0x0F)))
    {
        return VOS_FALSE;
    }

    /* ����λΪF,˵�������������룬����ʱ��� */
    if (0xF0 == (*pucCurByteAddr & 0xF0))
    {
        ucIsOddNum                      = VOS_TRUE;
    }

    PS_MEM_SET(pucEncVoiceMsgContent, 0x00, sizeof(VOS_UINT8) * ucEncVoiceMsgLen);

    if (VOS_TRUE == ucIsOddNum)
    {
        for (i = ucStdBcdLen; i >= 1; i--)
        {
            ucTempByte      = 0x00;

            pucCurByteAddr  = pucStdBcdContent + i - 1;

            ucTempByte      = ucTempByte | (*pucCurByteAddr & 0x0F);

            if (i > 1)
            {
                ucTempByte  = ucTempByte | (*(pucCurByteAddr - 1) & 0xF0);
            }

            /* ��ĩβ��ʼ��ǰ��ֵ */
            *(pucEncVoiceMsgContent + ucEncVoiceMsgLen - 1 - ucStdBcdLen + i)   = ucTempByte;
        }

        return VOS_TRUE;
    }

    for (i = ucStdBcdLen; i >= 1; i--)
    {
        ucTempByte      = 0x00;

        pucCurByteAddr  = pucStdBcdContent + i - 1;

        /* ���ߵ�4λ��λ�û��� */
        ucTempByte      = ucTempByte | ((*pucCurByteAddr << 4) & 0xF0);
        ucTempByte      = ucTempByte | ((*pucCurByteAddr >> 4) & 0x0F);

        /* ��ĩβ��ʼ��ǰ��ֵ */
        *(pucEncVoiceMsgContent + ucEncVoiceMsgLen - 1 - ucStdBcdLen + i)   = ucTempByte;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ConvertImsiFromStdBcdToKmcBcd
 ��������  : ��Imsi��ת������������Ҫ��ı����ʽ
             EG: 15λ IMSI = 230 040 680000079
             From StdBcd: 0x08 0x29 0x03 0x40 0x60 0x08 0x00 0x00 0x97 (��λ��4λΪ����λ0x09)
             To   KmcBcd: 0x08 0x02 0x30 0x04 0x06 0x80 0x00 0x00 0x79
 �������  : VOS_UINT8                          *pucStdImsiContent,
             VOS_UINT8                          *pucEncVoiceImsiContent,
             VOS_UINT8                           ucEncVoiceImsiLen
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE: �ɹ�
             VOS_FALSE:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��28��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_ConvertImsiFromStdBcdToKmcBcd(
    VOS_UINT8                          *pucImsiContent,
    VOS_UINT8                          *pucEncVoiceImsiContent,
    VOS_UINT8                           ucEncVoiceImsiLen
)
{
    VOS_UINT32                          i;
    VOS_UINT8                          *pucCurByteAddr  = VOS_NULL_PTR;
    VOS_UINT8                           ucTempByte;
    VOS_UINT8                           ucStdImsiLen;

    ucTempByte                          = 0x00;
    i                                   = 0;
    /* IMSI���ֽڴ洢IMSI�ĳ��ȣ��ڶ����ֽ���洢IMSI���� */
    ucStdImsiLen                        = *pucImsiContent;

    /* ���ȼ�� */
    if (ucEncVoiceImsiLen < ucStdImsiLen)
    {
        return VOS_FALSE;
    }

    /* Imsi���ֽ�Ϊ���ȣ��ӵڶ����ֽڿ�ʼ��ȡ���� */
    pucCurByteAddr  = pucImsiContent + 1;

    /* ��ʼ������ */
    PS_MEM_SET(pucEncVoiceImsiContent, 0x00, sizeof(VOS_UINT8) * ucEncVoiceImsiLen);

    for (i = 0; i < ucStdImsiLen; i++)
    {
        /* ���ߵ�4λ��λ�û��� */
        ucTempByte  = ucTempByte | ((*(pucCurByteAddr + i) << 4) & 0xF0);
        ucTempByte  = ucTempByte | ((*(pucCurByteAddr + i) >> 4) & 0x0F);

        /* ��ĩβ��ʼ��ǰ��ֵ */
        *(pucEncVoiceImsiContent + ucEncVoiceImsiLen - ucStdImsiLen + i)   = ucTempByte;

        ucTempByte  = 0x00;
    }

    /* �����ֽڵ�4λΪ9(Imsi����λ), ��ת����ĸ�4λ��0 */
    if (0x09 == (*pucCurByteAddr & 0x09))
    {
        *(pucEncVoiceImsiContent + ucEncVoiceImsiLen - ucStdImsiLen)   &= 0x0F;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_FillKmcReqMsgCipherText
 ��������  : ���KMC REQ������Ϣ
 �������  : pstKmcMsg     -- KMC��Ϣ
             pstKsNegoCtx  -- �ܻ�Э��������
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE: �ɹ�
             VOS_FALSE:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��28��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_FillKmcReqMsgCipherText(
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg,
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx
)
{
    TAF_XCALL_PLAIN_TEXT_INFO_STRU                          stPlainTextInfo;
    TAF_XCALL_HARDWARE_ID_INFO_STRU                         stHardWareIdInfo;
    TAF_ECC_CALL_BCD_NUM_STRU                               stCalledNumInfo;
    TAF_XCALL_CIPHER_ENCRYPTION_STRU                        stEncryption;
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity = VOS_NULL_PTR;

    PS_MEM_SET(&stPlainTextInfo, 0x00, sizeof(TAF_XCALL_PLAIN_TEXT_INFO_STRU));
    PS_MEM_SET(&stHardWareIdInfo, 0x00, sizeof(TAF_XCALL_HARDWARE_ID_INFO_STRU));
    PS_MEM_SET(&stCalledNumInfo, 0x00, sizeof(TAF_ECC_CALL_BCD_NUM_STRU));
    PS_MEM_SET(&stEncryption, 0x00, sizeof(TAF_XCALL_CIPHER_ENCRYPTION_STRU));

    if (VOS_FALSE == TAF_XCALL_GetHardWareInfo(&stHardWareIdInfo))
    {
        return VOS_FALSE;
    }

    /***********************************************************************************************
     * ����ʱ������ں��н����л�ȡ�������к��루Alert with info ��Ϣ�����к����ֶε�PI λΪ"00"��
     * num_of_char Ϊ"0"����PI λΪ��������ֵ����������ģʽ�ֱ���
     * - �Զ�ģʽ���ɱ��м���֪ͨ���Ŵ�������������Կ������Ϣ�е����к�����д�ӱ��м���֪ͨ��Ϣ�л�
     *   ȡ�����к��룻���ж�"���м���֪ͨ"��Ϣ�е�"���к���"�뵱ǰͨ�����з���ƥ�����⣻
     * - �ֶ�ģʽ�����û��������������ڱ�����Կ������Ϣ�в������к��룬"���к���"�ֶ���ȫ��("���к�
     *   ��"���Ȳ��䣬��11 ��"0")��
     * ����ʱ������û�����ı��к��������ǰ׺�������ȳ�����11 λ����ֱ�Ӷ�ȡ�û������������11
     * λ���к���
     * - �û�ʹ��"��ʱԤԼ���к���ʶ������"ʱ�����������������¿����ڱ��к���ǰ�Ӳ�ǰ׺
     **********************************************************************************************/
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(pstKsNegoCtx->ucCallId);

    if ((VOS_FALSE                                      == TAF_XCALL_IsCallingNumExist(pstCallEntity))
     && (TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MT_MUNAUL_MODE == pstKsNegoCtx->enEccVoiceType))
    {
        stCalledNumInfo.ucNumLen = TAF_ECC_CALL_MAX_BCD_NUM_LEN;

        PS_MEM_SET(&(stCalledNumInfo.aucBcdNum[0]), 0, sizeof(stCalledNumInfo.aucBcdNum));
    }
    else
    {
        stCalledNumInfo.ucNumLen = pstKsNegoCtx->stCallNum.ucNumLen;

        PS_MEM_CPY(stCalledNumInfo.aucBcdNum,
                   pstKsNegoCtx->stCallNum.aucBcdNum,
                   sizeof(stCalledNumInfo.aucBcdNum));
    }


    if (VOS_FALSE == TAF_XCALL_GenerateEncVoicePlainText(TAF_SDC_GetCsimImsi(),
                                                        &stHardWareIdInfo,
                                                        &stCalledNumInfo,
                                                        &stPlainTextInfo))
    {
        return VOS_FALSE;
    }

    TAF_XCALL_MNTN_LogCipherText(&stPlainTextInfo, &stCalledNumInfo);

    stEncryption.ucPubKeyLen            = TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN;
    PS_MEM_CPY(&(stEncryption.aucPubKey[0]),
               &(TAF_XCALL_GetVoiceEncryptPublicKeyAndVersionNumber()->aucPubKey[0]),
               stEncryption.ucPubKeyLen);

    stEncryption.ucPlainDataLen         = stPlainTextInfo.ucNumLen;
    PS_MEM_CPY(&(stEncryption.aucPlainData[0]),
               &(stPlainTextInfo.aucContent[0]),
               stPlainTextInfo.ucNumLen);

    stEncryption.ucCipherDataLen        = TAF_XCALL_KMC_MSG_MAX_CIPHER_LEN;
    stEncryption.pucCipherData          = &(pstKmcMsg->u.stKeyReq.stCipher.aucCipher[0]);

    if (VOS_FALSE == TAF_XCALL_CipherEncrypt(&stEncryption))
    {
        return VOS_FALSE;
    }

    pstKmcMsg->u.stKeyReq.stCipher.usCipherLen   = (VOS_UINT16)stEncryption.ucEncrptionLen;

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_FillKmcKeyReqMsgTypeAndMode
 ��������  : ���KMC KEY�������Ϣ�����Լ�ģʽ
 �������  : pstKmcMsg    -- KMC��Ϣ
             pstKsNegoCtx -- �ܻ�Э����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_FillKmcKeyReqMsgTypeAndMode(
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg,
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx
)
{
    switch (pstKsNegoCtx->enEccVoiceType)
    {
        case TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MO_MUNAUL_MODE:
            {
                pstKmcMsg->enSmsType                  = TAF_XCALL_KMC_MSG_TYPE_MO_KEY_REQ;
                pstKmcMsg->u.stKeyReq.enTriggerMode   = TAF_XCALL_KMC_MSG_TRIGGER_MODE_MANUAL;
            }
            break;

        case TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MO_AUTO_MODE:
            {
                pstKmcMsg->enSmsType                  = TAF_XCALL_KMC_MSG_TYPE_MO_KEY_REQ;
                pstKmcMsg->u.stKeyReq.enTriggerMode   = TAF_XCALL_KMC_MSG_TRIGGER_MODE_AUTO;
            }
            break;

        case TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MT_MUNAUL_MODE:
            {
                pstKmcMsg->enSmsType                  = TAF_XCALL_KMC_MSG_TYPE_MT_KEY_REQ;
                pstKmcMsg->u.stKeyReq.enTriggerMode   = TAF_XCALL_KMC_MSG_TRIGGER_MODE_MANUAL;
            }
            break;

        case TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MT_AUTO_MODE:
            {
                pstKmcMsg->enSmsType                  = TAF_XCALL_KMC_MSG_TYPE_MT_KEY_REQ;
                pstKmcMsg->u.stKeyReq.enTriggerMode   = TAF_XCALL_KMC_MSG_TRIGGER_MODE_AUTO;
            }
            break;

        default:
            /* �ڵ��ú���֮ǰ���Ѿ��������˼�飬���ﲻ�������⴦�� */
            break;
    }
}
/*****************************************************************************
 �� �� ��  : TAF_XCALL_FillKmcUpdateRspMsg
 ��������  : ���KMC Update Rsp Msg
 �������  : VOS_VOID
 �������  :  TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg
 �� �� ֵ  : VOS_FALSE: ʧ�ܣ�
             VOS_TRUE : �ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��27��
    ��    ��   : l00359089
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XCALL_FillKmcUpdateRspMsg(
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg
)
{
    pstKmcMsg->enSmsType = TAF_XCALL_KMC_MSG_TYPE_PUB_KEY_UPDATE_RSP;

    if(VOS_TRUE != TAF_XCALL_CipherGetRandom(TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN, pstKmcMsg->u.stPubKeyUpdateRsp.aucRandomData))
    {
        /*�������ȡʧ��*/
        return VOS_FALSE;
    }
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_GetSendXsmsReqOpId
 ��������  : ��ȡ���䷢��XSMS����opId
 �������  : ��
 �������  : ��

 �� �� ֵ  : usOpIdSeqNum -- ����opId�������к�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT16 TAF_XCALL_GetSendXsmsReqOpId(VOS_VOID)
{
    TAF_XCALL_XSMS_SEND_REQ_OPID_MGMT_CTX                  *pstOpIdMgmt = VOS_NULL_PTR;

    pstOpIdMgmt = TAF_XCALL_GetOpIdMgmtCtxAddr();

    pstOpIdMgmt->usOpIdSeqNum++;

    if (0 == pstOpIdMgmt->usOpIdSeqNum)
    {
        pstOpIdMgmt->usOpIdSeqNum++;
    }

    return (pstOpIdMgmt->usOpIdSeqNum);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_IsCallingNumExist
 ��������  : �ܻ�����ʱ���ж����з������Ƿ����
 �������  : pstCallEntity -- ����ʵ���ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��28��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XCALL_IsCallingNumExist(
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity
)
{
    /****************************************************************************
        ����ʱ������ں��н����л�ȡ�������к��루Alert with info ��Ϣ�����к�����
        �ε�PI λΪ"00"��num_of_char Ϊ"0"����PI λΪ��������ֵ����������ģʽ�ֱ�
        ����
        - �Զ�ģʽ���ɱ��м���֪ͨ���Ŵ�������������Կ������Ϣ�е����к�����д
        �ӱ��м���֪ͨ��Ϣ�л�ȡ�����к��룻���ж�"���м���֪ͨ"��Ϣ�е�"����
        ����"�뵱ǰͨ�����з���ƥ�����⣻
        - �ֶ�ģʽ�����û��������������ڱ�����Կ������Ϣ�в������к��룬"���к�
        ��"�ֶ���ȫ��("���к���"���Ȳ��䣬��11 ��"0")��
     ****************************************************************************/
    if (((0 == pstCallEntity->ucPi)
      && (0 == pstCallEntity->stCallNumber.ucNumLen))
     || (0 != pstCallEntity->ucPi))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_IsEncVoiceNumberSameAsCallNumber
 ��������  : ����ܻ������Ƿ�����к���һ��
 �������  : ucCallNumLen    -- ���к��볤��
             pucCallNum      -- pucCallNum���к�����Ϣ
             pstEccRemoteNum -- ECCԶ�˺��볤��
 �������  : ��
 �� �� ֵ  : VOS_TRUE -- ����һ�£� VOS_FALSE: ���벻һ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XCALL_IsEncVoiceNumberSameAsCallNumber(
    VOS_UINT8                                               ucCallNumLen,
    VOS_UINT8                                              *pucCallNum,
    TAF_ECC_CALL_BCD_NUM_STRU                              *pstEccRemoteNum
)
{
    VOS_INT8                            aucCallNumAsciiNum[TAF_XCALL_MAX_ASCII_NUM_LEN + 1];
    VOS_INT8                            aucEccRemoteAsciiNum[TAF_XCALL_MAX_ENCRYPT_VOICE_NUM + 1];
    VOS_UINT8                           ucCallNumAsciiNumLen;
    VOS_UINT8                           ucEccRemoteAsciiNumLen;

    /* ת���ܻ�������ܻ�ָʾ�ĺ��뵽ascii��ʽ */
    ucEccRemoteAsciiNumLen = 0;
    PS_MEM_SET(&aucEccRemoteAsciiNum[0], 0, sizeof(aucEccRemoteAsciiNum));
    if (MN_ERR_NO_ERROR != TAF_STD_ConvertBcdNumberToAscii(pstEccRemoteNum->aucBcdNum,
                                                           pstEccRemoteNum->ucNumLen,
                                                           (VOS_CHAR*)aucEccRemoteAsciiNum))
    {
        return VOS_FALSE;
    }

    /* ��ȡECC���к��볤�� */
    ucEccRemoteAsciiNumLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)aucEccRemoteAsciiNum);

    /* ת������ʵ���еĺ��뵽ascii��ʽ */
    ucCallNumAsciiNumLen = 0;
    PS_MEM_SET(&aucCallNumAsciiNum[0], 0, sizeof(aucCallNumAsciiNum));
    if (MN_ERR_NO_ERROR != TAF_STD_ConvertBcdNumberToAscii(pucCallNum,
                                                           ucCallNumLen,
                                                           (VOS_CHAR*)aucCallNumAsciiNum))
    {
        return VOS_FALSE;
    }

    /* ��ȡ����ʵ���еĺ��볤�� */
    ucCallNumAsciiNumLen = (VOS_UINT8)VOS_StrLen((VOS_CHAR*)aucCallNumAsciiNum);

    /* ȡҪ�Ƚϵĺ��볤�� */
    if (ucEccRemoteAsciiNumLen <= ucCallNumAsciiNumLen )
    {
        /* ������������бȽ� */
        if (0 != PS_MEM_CMP(&aucCallNumAsciiNum[ucCallNumAsciiNumLen - ucEccRemoteAsciiNumLen],
                            &aucEccRemoteAsciiNum[0],
                            ucEccRemoteAsciiNumLen))
        {
            return VOS_FALSE;
        }
    }
    else
    {
        /* ECC�����Ѿ�ȥ���˺���ǰ׺�������ַ��� ������к���С��ECC���룬���밴��һ�� */
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SendKmcKeyReqMsg
 ��������  : ��ȡMT����״̬
 �������  : pstKsNegoCtx -- �ܻ�Э��������
 �������  : ��
 �� �� ֵ  : TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32 -- ���ط��ͽ��ԭ��ֵ

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32 TAF_XCALL_SendKmcKeyReqMsg(
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx
)
{
    TAF_XCALL_KMC_MSG_STRU             stKmcMsg;
    VOS_UINT8                          aucMsgData[TAF_XCALL_KMC_MSG_WMS_CDMA_USER_DATA_MAX];
    VOS_UINT16                         usMsgDataLen;

    PS_MEM_SET(&stKmcMsg, 0, sizeof(TAF_XCALL_KMC_MSG_STRU));

    /***********************************************************************************
     * ����ܻ�������Ϣ�����Լ�����ģʽ
     **********************************************************************************/
    TAF_XCALL_FillKmcKeyReqMsgTypeAndMode(&stKmcMsg, pstKsNegoCtx);

    /***********************************************************************************
     * ������ʱ��˽Կ�ԣ��������ʧ�ܣ�����δ֪����
     **********************************************************************************/
    PS_MEM_SET(&pstKsNegoCtx->stTmpPubKey,  0, sizeof(TAF_XCALL_KMC_PUB_KEY_STRU));

    PS_MEM_SET(&pstKsNegoCtx->stTmpPrivKey, 0, sizeof(TAF_XCALL_KMC_PRIV_KEY_STRU));

    if (VOS_FALSE == TAF_XCALL_CipherGenTmpKey(&pstKsNegoCtx->stTmpPubKey, &pstKsNegoCtx->stTmpPrivKey))
    {
        return TAF_CALL_APP_ENCRYPT_VOICE_GET_TEMP_PUB_PIVA_KEY_FAILURE;
    }

    /* ���KMC KEY������ʱ��Կ��Ϣ */
    TAF_XCALL_FillKmcReqMsgTempPubKey(&stKmcMsg, pstKsNegoCtx);

    /***********************************************************************************
     * ���������Ϣ
     **********************************************************************************/
    if (VOS_FALSE == TAF_XCALL_FillKmcReqMsgCipherText(&stKmcMsg, pstKsNegoCtx))
    {
        return TAF_CALL_APP_ENCRYPT_VOICE_FILL_CIPHER_TEXT_FAILURE;
    }

    /***********************************************************************************
     * ��丨����Ϣ
     **********************************************************************************/
    TAF_XCALL_FillAdditionalInfo(&stKmcMsg);

    /***********************************************************************************
     * KMC KEY������룬�������ʧ�ܣ������ڲ�����
     **********************************************************************************/
    if (TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS != TAF_XCALL_EncodeKmcMsg(&stKmcMsg, &aucMsgData[0], &usMsgDataLen))
    {
        return TAF_CALL_APP_ENCRYPT_VOICE_MSG_ENCODE_FAILUE;
    }

    /***********************************************************************************
     * ����XSMS���������ӦopId���������ʧ�ܣ������ڲ�����
     **********************************************************************************/
    pstKsNegoCtx->usWaitXsmsCnfOpId = TAF_XCALL_GetSendXsmsReqOpId();

    /***********************************************************************************
     * ����KMC�ܻ�������Ϣ��XSMS
     **********************************************************************************/
    TAF_XCALL_SendXsmsKmcMsgSendReq(pstKsNegoCtx->usWaitXsmsCnfOpId, (VOS_UINT8)usMsgDataLen, &aucMsgData[0]);

    return TAF_CALL_APP_ENCRYPT_VOICE_SUCC;
}
/*****************************************************************************
 �� �� ��  : TAF_XCALL_SendKmcUpdateRspMsg
 ��������  : ���͹�Կ������Ӧ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE :ʧ��
             VOS_TRUE : �ɹ�

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��27��
    ��    ��   : l00359089
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XCALL_SendKmcUpdateRspMsg(
    VOS_UINT16                          usOpId,
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg
)
{
    VOS_UINT8                          aucMsgData[TAF_XCALL_KMC_MSG_WMS_CDMA_USER_DATA_MAX];
    VOS_UINT16                         usMsgDataLen;

    if (VOS_TRUE != TAF_XCALL_FillKmcUpdateRspMsg(pstKmcMsg))
    {
        return VOS_FALSE;
    }

    /***********************************************************************************
    * KMC ��Կ������Ӧ��Ϣ������룬�������ʧ�ܣ������ڲ�����
    **********************************************************************************/
    usMsgDataLen = 0;

    PS_MEM_SET(aucMsgData, 0, sizeof(aucMsgData));

    if (TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS != TAF_XCALL_EncodeKmcMsg(pstKmcMsg, aucMsgData, &usMsgDataLen))
    {
       return VOS_FALSE;
    }

    /***********************************************************************************
    * ����KMC��Կ������Ӧ��Ϣ������Ϣ��XSMS
    **********************************************************************************/
    TAF_XCALL_SendXsmsKmcMsgSendReq(usOpId, usMsgDataLen, aucMsgData);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcEccEvent
 ��������  : ����ECC�ڲ��¼�
 �������  : ulEventType     -- �ڲ��¼�
             VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcEccEvent(
    VOS_UINT32                                              ulEventType,
    TAF_XCALL_ECC_SRV_STATE_MACHINE_ID_ENUM_UINT32          enStateMachine,
    VOS_VOID                                               *pMsg,
    VOS_VOID                                               *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegotiateCtx   = VOS_NULL_PTR;
    TAF_XCALL_PUBLIC_KEY_UPDATE_CTX                        *pstPubkeyUPdateCtx  = VOS_NULL_PTR;
    TAF_XCALL_REMOTE_CTRL_CTX                              *pstRemoteCtrlCtx    = VOS_NULL_PTR;

    switch (enStateMachine)
    {
        case TAF_XCALL_ECC_SRV_STATE_MACHINE_VOICE_ENC:
            {
                pstKsNegotiateCtx                           = TAF_XCALL_GetKsNegotiateCtxAddr();

                TAF_XCALL_MNTN_LogVoiceEncryptState((TAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM_UINT32)ulEventType,
                                                     pstKsNegotiateCtx->enVoiceEncState);

                TAF_XCALL_ProcKmcKsNegotiateProcedure((TAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM_UINT32)ulEventType, pMsg, pKmcDecMsg);

                TAF_XCALL_MNTN_LogVoiceEncryptState((TAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM_UINT32)ulEventType,
                                                     pstKsNegotiateCtx->enVoiceEncState);
                break;
            }
        case TAF_XCALL_ECC_SRV_STATE_MACHINE_PUB_KEY_UPDATE:
            {
                pstPubkeyUPdateCtx                          = TAF_XCALL_GetPubKeyUpdateCtxAddr();

                TAF_XCALL_MNTN_LogEncVoiceKeyUpdateState((TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_TYPE_ENUM_UINT32)ulEventType,
                                                          pstPubkeyUPdateCtx->enK0UpdateState);

                TAF_XCALL_ProcKmcPublicKeyUpdateProcedure((TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_TYPE_ENUM_UINT32)ulEventType, pMsg, pKmcDecMsg);

                TAF_XCALL_MNTN_LogEncVoiceKeyUpdateState((TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_TYPE_ENUM_UINT32)ulEventType,
                                                          pstPubkeyUPdateCtx->enK0UpdateState);
                break;
            }
        case TAF_XCALL_ECC_SRV_STATE_MACHINE_REMOTE_CTRL:
            {
                pstRemoteCtrlCtx                            = TAF_XCALL_GetRemoteCtrlCtxAddr();

                TAF_XCALL_MNTN_LogEncVoiceRemoteCtrlState((TAF_XCALL_REMOTE_CTRL_MSG_EVENT_TYPE_ENUM_UINT32)ulEventType,
                                                           pstRemoteCtrlCtx->enRemoteCtrlState);

                TAF_XCALL_ProcKmcRemoteControlProcedure((TAF_XCALL_REMOTE_CTRL_MSG_EVENT_TYPE_ENUM_UINT32)ulEventType, pMsg, pKmcDecMsg);

                TAF_XCALL_MNTN_LogEncVoiceRemoteCtrlState((TAF_XCALL_REMOTE_CTRL_MSG_EVENT_TYPE_ENUM_UINT32)ulEventType,
                                                           pstRemoteCtrlCtx->enRemoteCtrlState);
                break;
            }
        default:
            break;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcKmcKsNegotiateProcedure
 ��������  : ����KMC��KsЭ������
 �������  : enEventType     -- �ڲ��¼�
             VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcKmcKsNegotiateProcedure(
    TAF_XCALL_VOICE_ENC_MSG_EVENT_TYPE_ENUM_UINT32          enEventType,
    VOS_VOID                                               *pMsg,
    VOS_VOID                                               *pKmcDecMsg
)
{
    /* ��鵱ǰ���¼������Ƿ񳬳���Χ����tab�е��¼������Ƿ�һ�� */
    if ((enEventType >= TAF_XCALL_VOICE_ENC_MSG_EVENT_MAX)
     || (enEventType != g_astTafXcallVoiceEncEventProcTab[enEventType].ulEventType))
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF, "TAF_XCALL_ProcKmcKsNegotiateProcedure: enEventType = ", enEventType);

        return;
    }

    g_astTafXcallVoiceEncEventProcTab[enEventType].pfEventProcFun(pMsg, pKmcDecMsg);


    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcKmcPublicKeyUpdateProcedure
 ��������  : ����KMC��Կ��������
 �������  : enEventType     -- �ڲ��¼�
             VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcKmcPublicKeyUpdateProcedure(
    TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_TYPE_ENUM_UINT32     enEventType,
    VOS_VOID                                               *pMsg,
    VOS_VOID                                               *pKmcDecMsg
)
{
    /* ��鵱ǰ���¼������Ƿ񳬳���Χ����tab�е��¼������Ƿ�һ�� */
    if ((enEventType >= TAF_XCALL_PUB_KEY_UPDATE_MSG_EVENT_MAX)
     || (enEventType != g_astTafXcallPubKeyEventProcTab[enEventType].ulEventType))
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF, "TAF_XCALL_ProcKmcPublicKeyUpdateProcedure: enEventType = ", enEventType);

        return;
    }

    g_astTafXcallPubKeyEventProcTab[enEventType].pfEventProcFun(pMsg, pKmcDecMsg);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcKmcRemoteControlProcedure
 ��������  : ����Զ�̿�������
 �������  : enEventType     -- �ڲ��¼�
             VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcKmcRemoteControlProcedure(
    TAF_XCALL_REMOTE_CTRL_MSG_EVENT_TYPE_ENUM_UINT32        enEventType,
    VOS_VOID                                               *pMsg,
    VOS_VOID                                               *pKmcDecMsg
)
{
    /* ��鵱ǰ���¼������Ƿ񳬳���Χ����tab�е��¼������Ƿ�һ�� */
    if ((enEventType >= TAF_XCALL_REMOTE_CTRL_MSG_EVENT_MAX)
     || (enEventType != g_astTafXcallRemoteCtrlEventProcTab[enEventType].ulEventType))
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF, "TAF_XCALL_ProcKmcRemoteControlProcedure: enEventType = ", enEventType);

        return;
    }

    g_astTafXcallRemoteCtrlEventProcTab[enEventType].pfEventProcFun(pMsg, pKmcDecMsg);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ExitVoiceEncriptProcedure
 ��������  : �˳�������������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��3��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ExitVoiceEncriptProcedure(VOS_VOID)
{
    /* ֹͣ������ص��ܻ���ʱ�� */
    TAF_XCALL_StopTimer(TI_TAF_XCALL_VOICE_ENCRYPT_WAIT_ORIG_REQ_TIMER, 0);
    TAF_XCALL_StopTimer(TI_TAF_XCALL_DELAY_SEND_ENCRYPT_REQ, 0);
    TAF_XCALL_StopTimer(TI_TAF_XCALL_TX01_TIMER, 0);
    TAF_XCALL_StopTimer(TI_TAF_XCALL_TX02_TIMER, 0);

    /* ���֮ǰ�����KEYЭ�̵���������Ϣ */
    TAF_XCALL_InitEncVoiceKeyNegotiateCtx();
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ExitPubKeyUpdateProcedure
 ��������  : �˳���Կ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��3��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ExitPubKeyUpdateProcedure(VOS_VOID)
{
    TAF_XCALL_StopTimer(TI_TAF_XCALL_PUB_KEY_UPDATE_WAIT_ACK_TIMER, 0);

    /* ��ʼ����Կ������������Ϣ */
    TAF_XCALL_InitEncVoiceKmcUpdateCtx();
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ExitRemoteCtrlOpertionProcedure
 ��������  : �˳�Զ�̿��Ʋ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��3��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ExitRemoteCtrlOpertionProcedure(VOS_VOID)
{
    TAF_XCALL_StopTimer(TI_TAF_XCALL_REMOTE_CTRL_WAIT_AP_ANSWER_TIMER, 0);

    /* ��ʼ����Կ������������Ϣ */
    TAF_XCALL_InitEncVoiceRemoteCtrlCtx();
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVoiceEncKmcKeyRsp
 ��������  : ����KMC�·���MT��Կ��Ӧ�¼�
 �������  : *pMsg        -- �¼���Ӧ����Ϣ����
             pKmcDecMsg   -- KMC������Ϣ
             pstKsNegoCtx -- �ܻ���������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XCALL_VerifySignature(
    VOS_UINT8                           ucPubKeyLen,
    VOS_UINT8                          *pucPubKey,
    VOS_UINT8                           ucSignInfoLen,
    VOS_UINT8                          *pucSignInfo,
    VOS_UINT8                           ucSignDataLen,
    VOS_UINT8                          *pucSignData
)
{
    TAF_XCALL_CIPHER_VERIFY_STRU                            stCipherVerify;

    PS_MEM_SET(&stCipherVerify, 0, sizeof(stCipherVerify));

    stCipherVerify.ucPubKeyLen = (VOS_UINT8)TAF_XCALL_MIN(ucPubKeyLen, TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN);
    PS_MEM_CPY(&stCipherVerify.aucPubKey[0], pucPubKey, stCipherVerify.ucPubKeyLen);

    stCipherVerify.ucSigntureInfoLen = (VOS_UINT8)TAF_XCALL_MIN(ucSignInfoLen, TAF_XCALL_KMC_MSG_MAX_SIGN_INFO_LEN);
    PS_MEM_CPY(&stCipherVerify.auSigntureInfo[0], pucSignInfo, stCipherVerify.ucSigntureInfoLen);


    stCipherVerify.ucSigntureDataLen = TAF_XCALL_MIN(ucSignDataLen, TAF_XCALL_KMC_MSG_MAX_SIGN_DATA_LEN);
    PS_MEM_CPY(&stCipherVerify.auSigntureData[0], pucSignData, stCipherVerify.ucSigntureDataLen);

    return TAF_XCALL_CipherVerify(&stCipherVerify);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcMoAutoModeVoiceEncReq
 ��������  : �����û��·���MO�Զ�ģʽ���ܻ�����
 �������  : pstKsNegoCtx      -- �ܻ�Э����������Ϣ
             pstAppEncVoiceReq -- �ܻ�������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcMoAutoModeVoiceEncReq(
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx,
    TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU                    *pstAppEncVoiceReq
)
{
    VOS_UINT32                                              ulCallIdNum;
    VOS_UINT8                                               aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity = VOS_NULL_PTR;

    /***********************************************************************************
     * �ܻ�״̬��ƥ��
     **********************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE != pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_ENC_VOICE_STATE_MISMATCH);

        return;
    }

    PS_MEM_SET(&aucCallIds[0], 0, sizeof(aucCallIds));

    ulCallIdNum = TAF_XCALL_GetAllUsedCallId(&aucCallIds[0]);

    /***********************************************************************************
     * ���������·���У��ܾ��ܻ�
     **********************************************************************************/
    if (TAF_XCALL_CALL_ENTITY_MAX_NUM == ulCallIdNum)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAT_CALL_APP_ENCRYPT_VOICE_TWO_CALL_ENTITY_EXIST);

        return;
    }

    /***********************************************************************************
     * ����޺��д��ڣ��򱣴��ܻ����룬�ȴ���������
     **********************************************************************************/
    if (0 == ulCallIdNum)
    {
        pstKsNegoCtx->enEccVoiceType = pstAppEncVoiceReq->enEccVoiceType;

        PS_MEM_CPY(&pstKsNegoCtx->stCallNum,
                   &pstAppEncVoiceReq->stDialNumber,
                   sizeof(TAF_ECC_CALL_BCD_NUM_STRU));

        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_SUCC);

        TAF_XCALL_StartTimer(TI_TAF_XCALL_VOICE_ENCRYPT_WAIT_ORIG_REQ_TIMER, TI_TAF_XCALL_VOICE_ENCRYPT_WAIT_ORIG_REQ_LEN, 0);

        pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ORIG_REQ;

        return;
    }

    /***********************************************************************************
     * �����з��������ǰ����ΪMT���У����ܻ�����ʧ��
     **********************************************************************************/
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(aucCallIds[0]);

    if (MN_CALL_DIR_MO != pstCallEntity->enCallDir)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_NO_MO_CALL);

        return;
    }

    /***********************************************************************************
     * ���MO���в���DIALING״̬��ACTIVE״̬���򷵻��ܻ�����ʧ��
     **********************************************************************************/
    if ((MN_CALL_S_ACTIVE   != pstCallEntity->enCallState)
     && (MN_CALL_S_DIALING  != pstCallEntity->enCallState)
     && (MN_CALL_S_ALERTING != pstCallEntity->enCallState))
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_CALL_STATE_NOT_ALLOWED);

        return;
    }

    /***********************************************************************************
     * ����ܻ����������ʵ������Ƿ�һ��
     **********************************************************************************/
    if (VOS_FALSE == TAF_XCALL_IsEncVoiceNumberSameAsCallNumber(pstCallEntity->stCalledNumber.ucNumLen,
                                                                &pstCallEntity->stCalledNumber.aucBcdNum[0],
                                                                &(pstAppEncVoiceReq->stDialNumber)))
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_CALL_NUM_MISMATCH);

        return;
    }

    /***********************************************************************************
     * �����ܻ����������Լ��Զ˺���, ֪ͨ�û��ܻ�����ɹ�
     **********************************************************************************/
    pstKsNegoCtx->ucCallId       = aucCallIds[0];
    pstKsNegoCtx->enEccVoiceType = pstAppEncVoiceReq->enEccVoiceType;

    PS_MEM_CPY(&pstKsNegoCtx->stCallNum,
               &pstAppEncVoiceReq->stDialNumber,
               sizeof(TAF_ECC_CALL_BCD_NUM_STRU));

    TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_SUCC);

    /***********************************************************************************
     * �������Ϊactive״̬�����TCH״̬�����TCH��ָ�ɣ���Ǩ�Ƶ�����2s��ʱ��ʱ�����ȴ���
     * �������ͣ�����ȴ�TCHָ��ָʾ״̬
     **********************************************************************************/
    if (VOS_TRUE == pstCallEntity->ucTchAssignInd)
    {
        TAF_XCALL_StartTimer(TI_TAF_XCALL_DELAY_SEND_ENCRYPT_REQ,
                             TAF_XCALL_GetVoiceEncryptReqDelaySendTimerLen() * 1000,
                             0);

        pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_DELAY_SEND_ENCRYPT_REQ;
    }
    else
    {
        pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_TCH_ASSIGN_CMPL;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcMtAutoModeVoiceEncReq
 ��������  : �����û��·���Mt�Զ�ģʽ���ܻ�����
 �������  : pstKsNegoCtx      -- �ܻ�Э����������Ϣ
             pstAppEncVoiceReq -- �ܻ�������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcMtAutoModeVoiceEncReq(
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx,
    TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU                    *pstAppEncVoiceReq
)
{
    VOS_UINT32                                              ulCallIdNum;
    VOS_UINT8                                               aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity = VOS_NULL_PTR;
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enEncVoiceSendRslt;

    /***********************************************************************************
     * �����ǰ�ܻ�״̬���ڵȴ��ܻ�����״̬���ܾ��ܻ�����
     **********************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_AP_ENCRYPT_REQ != pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_ENC_VOICE_STATE_MISMATCH);

        return;
    }

    PS_MEM_SET(&aucCallIds[0], 0, sizeof(aucCallIds));

    ulCallIdNum = TAF_XCALL_GetAllUsedCallId(&aucCallIds[0]);

    /***********************************************************************************
     * ���������·���л��޺��д��ڣ��ܾ��ܻ�����(Ӧ�ò����ڸó�����������һ�±���������callIdΪ�Ƿ�ֵ)
     **********************************************************************************/
    if (TAF_XCALL_CALL_ENTITY_MAX_NUM == ulCallIdNum)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAT_CALL_APP_ENCRYPT_VOICE_TWO_CALL_ENTITY_EXIST);

        return;
    }

    /***********************************************************************************
     * ����޺��д��ڣ��ܾ��ܻ�����(Ӧ�ò����ڸó�����������һ�±���������callIdΪ�Ƿ�ֵ)
     **********************************************************************************/
    if (0 == ulCallIdNum)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_NO_CALL_EXIST);

        return;
    }

    /***********************************************************************************
     * �����з��������ǰ���в���MT���У����ܻ�����ʧ��
     **********************************************************************************/
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(aucCallIds[0]);

    if (MN_CALL_DIR_MT != pstCallEntity->enCallDir)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_NO_MT_CALL);

        return;
    }

    /***********************************************************************************************
     * ����ܻ����������ʵ������Ƿ�һ��, ����MT�Զ��������Ѿ����ܻ�ָʾʱ�������˱Ƚϣ�����ֻҪ��
     * �ܻ�����ĺ��뼴��
     **********************************************************************************************/
    if (VOS_FALSE == TAF_XCALL_IsEncVoiceNumberSameAsCallNumber(pstKsNegoCtx->stCallNum.ucNumLen,
                                                                &(pstKsNegoCtx->stCallNum.aucBcdNum[0]),
                                                                &(pstAppEncVoiceReq->stDialNumber)))
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_CALL_NUM_MISMATCH);

        return;
    }

    /***********************************************************************************************
     * �����ܻ���������(ע: ������벻��Ҫ�����ˣ��յ��ܻ�ָʾʱ���Ѿ�������)
     **********************************************************************************************/
    pstKsNegoCtx->ucCallId       = aucCallIds[0];
    pstKsNegoCtx->enEccVoiceType = pstAppEncVoiceReq->enEccVoiceType;

    /***********************************************************************************
     * �������Ϊactive״̬�������ܻ����󣻷�����incoming״̬���ȴ��û���������
     **********************************************************************************/
    if (MN_CALL_S_ACTIVE == pstCallEntity->enCallState)
    {
        enEncVoiceSendRslt = TAF_XCALL_SendKmcKeyReqMsg(pstKsNegoCtx);

        if (TAF_CALL_APP_ENCRYPT_VOICE_SUCC != enEncVoiceSendRslt)
        {
            TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl,
                                            enEncVoiceSendRslt);

            /* ���֮ǰ�����KEYЭ�̵���������Ϣ */
            TAF_XCALL_ExitVoiceEncriptProcedure();

            return;
        }

        TAF_XCALL_StartTimer(TI_TAF_XCALL_TX01_TIMER, TI_TAF_XCALL_TX01_LEN, 0);

        pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP;

    }
    else
    {
        pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WATIING_CALL_ACCEPT_REQ;
    }

    TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_SUCC);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcMoManualModeVoiceEncReq
 ��������  : �����û��·���MO�Զ�ģʽ���ܻ�����
 �������  : pstKsNegoCtx      -- �ܻ�Э����������Ϣ
             pstAppEncVoiceReq -- �ܻ�������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcMoManualModeVoiceEncReq(
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx,
    TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU                    *pstAppEncVoiceReq
)
{
    VOS_UINT32                                              ulCallIdNum;
    VOS_UINT8                                               aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity = VOS_NULL_PTR;
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enEncVoiceSendRslt;

    /***********************************************************************************
     * �ܻ�״̬��ƥ��
     **********************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE != pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_ENC_VOICE_STATE_MISMATCH);

        return;
    }

    PS_MEM_SET(&aucCallIds[0], 0, sizeof(aucCallIds));

    ulCallIdNum = TAF_XCALL_GetAllUsedCallId(&aucCallIds[0]);

    /***********************************************************************************
     * ���������·���л��޺��д��ڣ��ܾ��ܻ�����
     **********************************************************************************/
    if (TAF_XCALL_CALL_ENTITY_MAX_NUM == ulCallIdNum)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAT_CALL_APP_ENCRYPT_VOICE_TWO_CALL_ENTITY_EXIST);

        return;
    }

    /***********************************************************************************
     * ����޺��д��ڣ��ܾ��ܻ�����
     **********************************************************************************/
    if (0 == ulCallIdNum)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_NO_CALL_EXIST);

        return;
    }

    /***********************************************************************************
     * �����з��������ǰ���в���MO���У����ܻ�����ʧ��
     **********************************************************************************/
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(aucCallIds[0]);

    if (MN_CALL_DIR_MO   != pstCallEntity->enCallDir)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_NO_MO_CALL);

        return;
    }

    /***********************************************************************************
     * �����к���״̬�������ǰ���в��ڼ���̬�����ܻ�����ʧ��
     **********************************************************************************/
    if (MN_CALL_S_ACTIVE != pstCallEntity->enCallState)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_CALL_STATE_NOT_ALLOWED);

        return;
    }

    /***********************************************************************************
     * ����ܻ����������ʵ������Ƿ�һ��
     **********************************************************************************/
    if (VOS_FALSE == TAF_XCALL_IsEncVoiceNumberSameAsCallNumber(pstCallEntity->stCalledNumber.ucNumLen,
                                                                &pstCallEntity->stCalledNumber.aucBcdNum[0],
                                                                &(pstAppEncVoiceReq->stDialNumber)))
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_CALL_NUM_MISMATCH);

        return;
    }

    /***********************************************************************************
     * �����ܻ����������Լ��Զ˺���, �����ܻ�������������ܻ�����ʧ�ܣ�֪ͨ�û��ܻ�ʧ��
     **********************************************************************************/
    pstKsNegoCtx->ucCallId       = aucCallIds[0];
    pstKsNegoCtx->enEccVoiceType = pstAppEncVoiceReq->enEccVoiceType;

    PS_MEM_CPY(&pstKsNegoCtx->stCallNum,
               &pstAppEncVoiceReq->stDialNumber,
               sizeof(TAF_ECC_CALL_BCD_NUM_STRU));

    enEncVoiceSendRslt = TAF_XCALL_SendKmcKeyReqMsg(pstKsNegoCtx);

    if (TAF_CALL_APP_ENCRYPT_VOICE_SUCC != enEncVoiceSendRslt)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl,
                                        enEncVoiceSendRslt);

        /* ���֮ǰ�����KEYЭ�̵���������Ϣ */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    /***********************************************************************************
     * ֪ͨ�û��ܻ�����ɹ���״̬Ǩ�Ƶ��ȴ�KMC�ܻ��ظ�
     **********************************************************************************/
    TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_SUCC);


    TAF_XCALL_StartTimer(TI_TAF_XCALL_TX01_TIMER, TI_TAF_XCALL_TX01_LEN, 0);

    pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP;

}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcMtManualModeVoiceEncReq
 ��������  : �����û��·���MT�Զ�ģʽ���ܻ�����
 �������  : pstKsNegoCtx      -- �ܻ�Э����������Ϣ
             pstAppEncVoiceReq -- �ܻ�������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcMtManualModeVoiceEncReq(
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx,
    TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU                    *pstAppEncVoiceReq
)
{
    VOS_UINT32                                              ulCallIdNum;
    VOS_UINT8                                               aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity = VOS_NULL_PTR;
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enEncVoiceSendRslt;

    /***********************************************************************************
     * �ܻ�״̬��ƥ��
     **********************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE != pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_ENC_VOICE_STATE_MISMATCH);

        return;
    }

    PS_MEM_SET(&aucCallIds[0], 0, sizeof(aucCallIds));

    ulCallIdNum = TAF_XCALL_GetAllUsedCallId(&aucCallIds[0]);

    /***********************************************************************************
     * ���������·���л��޺��д��ڣ��ܾ��ܻ�����
     **********************************************************************************/
    if (TAF_XCALL_CALL_ENTITY_MAX_NUM == ulCallIdNum)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAT_CALL_APP_ENCRYPT_VOICE_TWO_CALL_ENTITY_EXIST);

        return;
    }

    /***********************************************************************************
     * ����޺��д��ڣ��ܾ��ܻ�����
     **********************************************************************************/
    if (0 == ulCallIdNum)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_NO_CALL_EXIST);

        return;
    }

    /***********************************************************************************
     * �����з��������ǰ���в���MT���У����ܻ�����ʧ��
     **********************************************************************************/
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(aucCallIds[0]);

    if (MN_CALL_DIR_MT != pstCallEntity->enCallDir)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_NO_MT_CALL);

        return;
    }

    /***********************************************************************************
     * �����к���״̬�������ǰ���в��ڼ���̬�����ܻ�����ʧ��
     **********************************************************************************/
    if (MN_CALL_S_ACTIVE != pstCallEntity->enCallState)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_CALL_STATE_NOT_ALLOWED);

        return;
    }

    /***********************************************************************************
     * ����ܻ����������ʵ������Ƿ�һ��
     **********************************************************************************/
    /* ������к���(���Զ˺���)����ʱ���Ž��к���Ƚ� */
    if (VOS_TRUE == TAF_XCALL_IsCallingNumExist(pstCallEntity))
    {
        if (VOS_FALSE == TAF_XCALL_IsEncVoiceNumberSameAsCallNumber(pstCallEntity->stCallNumber.ucNumLen,
                                                                    &pstCallEntity->stCallNumber.aucBcdNum[0],
                                                                    &(pstAppEncVoiceReq->stDialNumber)))
        {
            TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_CALL_NUM_MISMATCH);

            return;
        }
    }

    /***********************************************************************************
     * �����ܻ�ģʽ�Լ����룬�����ܻ������������ʧ�ܣ�֪ͨ�û��ܻ�ʧ��
     **********************************************************************************/
    pstKsNegoCtx->ucCallId       = aucCallIds[0];
    pstKsNegoCtx->enEccVoiceType = pstAppEncVoiceReq->enEccVoiceType;

    PS_MEM_CPY(&pstKsNegoCtx->stCallNum,
               &pstAppEncVoiceReq->stDialNumber,
               sizeof(TAF_ECC_CALL_BCD_NUM_STRU));

    enEncVoiceSendRslt = TAF_XCALL_SendKmcKeyReqMsg(pstKsNegoCtx);

    if (TAF_CALL_APP_ENCRYPT_VOICE_SUCC != enEncVoiceSendRslt)
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl,
                                        enEncVoiceSendRslt);

        /* ���֮ǰ�����KEYЭ�̵���������Ϣ */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    /***********************************************************************************
     * �����ܻ����������Լ��Զ˺���, ֪ͨ�û��ܻ�����ɹ���״̬Ǩ�Ƶ��ȴ�KMC�ܻ��ظ�
     **********************************************************************************/
    TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_SUCC);

    TAF_XCALL_StartTimer(TI_TAF_XCALL_TX01_TIMER, TI_TAF_XCALL_TX01_LEN, 0);

    pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVoiceEncKmcKeyRsp
 ��������  : ����KMC�·���MT��Կ��Ӧ�¼�
 �������  : *pMsg        -- �¼���Ӧ����Ϣ����
             pKmcDecMsg   -- KMC������Ϣ
             pstKsNegoCtx -- �ܻ���������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncKmcKeyRsp(
    XSMS_XCALL_KMC_MSG_RCV_IND_STRU    *pstXsmsRcvInd,
    TAF_XCALL_KMC_MSG_STRU             *pKmcDecMsg,
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx
)
{
    TAF_XCALL_CIPHER_DECRYPTION_STRU    stDecryption;

    /***********************************************************************************************
     * �����ǰ�����ڵȴ�KMC���ܻ���Ӧʱ�����������Ϣ
     **********************************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP != pstKsNegoCtx->enVoiceEncState)
    {
        return;
    }

    /* ֹͣ������ص��ܻ���ʱ�� */
    TAF_XCALL_StopTimer(TI_TAF_XCALL_TX01_TIMER, 0);

    /***********************************************************************************************
     * ���յ��Ķ��Ŵ����������ܻ�����ʧ����ʾ
     **********************************************************************************************/

    if (TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS != pKmcDecMsg->enRslt)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_MSG_DECODE_FAILUE,
                                       VOS_NULL_PTR);

        /* �˳��ܻ����� */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    /***********************************************************************************************
     * ���ܻ�RSP��Ϣ����ǩ����֤����֤ʧ�ܣ�֪ͨ�û��ܻ�ʧ��
     **********************************************************************************************/
    if (VOS_FALSE == TAF_XCALL_VerifySignature(TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN,
                                               &(TAF_XCALL_GetVoiceEncryptPublicKeyAndVersionNumber()->aucPubKey[0]),
                                               pKmcDecMsg->u.stKeyRsp.stSignInfo.ucSignInfoLen,
                                               &(pKmcDecMsg->u.stKeyRsp.stSignInfo.aucSignInfo[0]),
                                               (TAF_XCALL_KMC_MSG_HEADER_LEN + (VOS_UINT8)(pKmcDecMsg->u.stKeyRsp.stCipher.usCipherLen) + 1),
                                               &(pstXsmsRcvInd->aucData[0])))
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_SIGNTURE_VERIFY_FAILURE,
                                       VOS_NULL_PTR);

        /* �˳��ܻ����� */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    /***********************************************************************************************
     * ��ȡ�ܻ�KS��Ϣ
     **********************************************************************************************/
    PS_MEM_SET(&stDecryption, 0, sizeof(TAF_XCALL_CIPHER_DECRYPTION_STRU));

    stDecryption.ucCipherKeyLen  = pstKsNegoCtx->stTmpPrivKey.ucKeyLen;
    PS_MEM_CPY(&stDecryption.aucCipherKey[0],
               &pstKsNegoCtx->stTmpPrivKey.aucKey[0],
               sizeof(VOS_UINT8) * TAF_XCALL_KMC_MSG_MAX_KMC_PRIV_KEY_LEN);

    stDecryption.ucCipherDataLen = (VOS_UINT8)pKmcDecMsg->u.stKeyRsp.stCipher.usCipherLen;
    PS_MEM_CPY(&stDecryption.aucCipherData[0],
               &pKmcDecMsg->u.stKeyRsp.stCipher.aucCipher[0],
               sizeof(VOS_UINT8) * TAF_XCALL_KMC_MSG_MAX_CIPHER_LEN);

    stDecryption.ucPlainDataLen  = TAF_XCALL_ECC_KS_DATA_MAX_LEN;
    stDecryption.pucPlainData    = &pstKsNegoCtx->stKsInfo.aucKs[0];

    if (VOS_FALSE == TAF_XCALL_CipherDecrypt(&stDecryption))
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_DECRYPT_KS_FAILURE,
                                       VOS_NULL_PTR);

        /* �˳��ܻ����� */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }
    /* �ɹ��󣬸�����Կ���� */
    pstKsNegoCtx->stKsInfo.ucKsLen = stDecryption.ucEncrptionLen;

    PS_MEM_SET(&pstKsNegoCtx->stTmpPrivKey, 0, sizeof(TAF_XCALL_KMC_PRIV_KEY_STRU));
    PS_MEM_SET(&pstKsNegoCtx->stTmpPubKey,  0, sizeof(TAF_XCALL_KMC_PUB_KEY_STRU));

    /***********************************************************************************************
     * �����ܻ�SOЭ�̣�״̬Ǩ�Ƶ��ȴ�SOЭ��ȷ��
     **********************************************************************************************/
    TAF_XCALL_SendEccServiceReq();

    /* ����������ص��ܻ���ʱ�� */
    TAF_XCALL_StartTimer(TI_TAF_XCALL_TX02_TIMER, TI_TAF_XCALL_TX02_LEN, 0);

    pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ECC_SERVICE_CNF;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVoiceEncEventAppEncVoiceReq
 ��������  : �����û��·����ܻ�����
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventAppEncVoiceReq(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU                    *pstAppEncVoiceReq = VOS_NULL_PTR;
    TAF_XCALL_ECC_SRV_CAP_INFO_STRU                        *pstEccSrvCap      = VOS_NULL_PTR;
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx      = VOS_NULL_PTR;

    pstAppEncVoiceReq = (TAF_CALL_APP_ENCRYPT_VOICE_REQ_STRU *)pMsg;

    /***********************************************************************************************
     * ��鵱ǰ��������ҵ���������������������֧�ֻ�����ҵ��رգ���ܾ���������
     **********************************************************************************************/
    pstEccSrvCap = TAF_XCALL_GetVoiceEncryptCapCfgPara();

    if ((VOS_FALSE == pstEccSrvCap->ucEccSrvCap)
     || (VOS_FALSE == pstEccSrvCap->ucEccSrvStatus))
    {
        TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_ECC_CAP_NOT_SUPPORTED);

        return;
    }

    /***********************************************************************************************
     * �����ǰ�ܻ�״̬����inactive״̬�������ܻ��������ڽ��У��ܾ���ǰ���ܻ�����
     **********************************************************************************************/
    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    switch (pstAppEncVoiceReq->enEccVoiceType)
    {
        case TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MT_AUTO_MODE:
            TAF_XCALL_ProcMtAutoModeVoiceEncReq(pstKsNegoCtx, pstAppEncVoiceReq);
            break;

        case TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MO_AUTO_MODE:
            TAF_XCALL_ProcMoAutoModeVoiceEncReq(pstKsNegoCtx, pstAppEncVoiceReq);
            break;

        case TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MO_MUNAUL_MODE:
            TAF_XCALL_ProcMoManualModeVoiceEncReq(pstKsNegoCtx, pstAppEncVoiceReq);
            break;

        case TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MT_MUNAUL_MODE:
            TAF_XCALL_ProcMtManualModeVoiceEncReq(pstKsNegoCtx, pstAppEncVoiceReq);
            break;

        default:
            TAF_XCALL_SndAppEncryptVoiceCnf(&pstAppEncVoiceReq->stCtrl, TAF_CALL_APP_ENCRYPT_VOICE_ENC_VOICE_MODE_UNKNOWN);
            break;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVoiceEncEventAppOrigReq
 ��������  : �����û��·��ĺ��������¼�
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : l00359089
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventAppOrigReq(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx      = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU                             *pstXcallEntity    = VOS_NULL_PTR;
    VOS_UINT32                                              ulCallIdNum;
    VOS_UINT8                                               aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];

    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    /* �����ǰ״̬����WAITING_ORIG_REQ������Ҫ���� */
    if (TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ORIG_REQ != pstKsNegoCtx->enVoiceEncState)
    {
        return;
    }

    /* ֹͣ��ʱ�� */
    TAF_XCALL_StopTimer(TI_TAF_XCALL_VOICE_ENCRYPT_WAIT_ORIG_REQ_TIMER, 0);

    ulCallIdNum = TAF_XCALL_GetAllUsedCallId(&aucCallIds[0]);

    /***********************************************************************************
     * ���������·���л��޺��д��ڣ��ܾ��ܻ�����
     **********************************************************************************/
    if (TAF_XCALL_CALL_ENTITY_MAX_NUM == ulCallIdNum)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                        TAT_CALL_APP_ENCRYPT_VOICE_TWO_CALL_ENTITY_EXIST,
                                        VOS_NULL_PTR);

        /* �˳��ܻ����� */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    /***********************************************************************************
     * ����޺��д��ڣ��ܾ��ܻ�����
     **********************************************************************************/
    if (0 == ulCallIdNum)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                        TAF_CALL_APP_ENCRYPT_VOICE_NO_CALL_EXIST,
                                        VOS_NULL_PTR);
        /* �˳��ܻ����� */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    pstXcallEntity = TAF_XCALL_GetCallEntityAddr(aucCallIds[0]);

    if (VOS_TRUE == TAF_XCALL_IsEncVoiceNumberSameAsCallNumber(pstXcallEntity->stCalledNumber.ucNumLen,
                                                               &(pstXcallEntity->stCalledNumber.aucBcdNum[0]),
                                                               &pstKsNegoCtx->stCallNum))
    {
        /* ������е�callId��ʶ */
        pstKsNegoCtx->ucCallId        = aucCallIds[0];

        /*����һ�£�״̬Ǩ��*/
        pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_TCH_ASSIGN_CMPL;
    }
    else
    {
        /*���벻һ�£��ϱ��ܻ�����ʧ��*/
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                        TAF_CALL_APP_ENCRYPT_VOICE_CALL_NUM_MISMATCH,
                                        VOS_NULL_PTR);
        /* �˳��ܻ����� */
        TAF_XCALL_ExitVoiceEncriptProcedure();
    }
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVoiceEncEventAppHangUpReq
 ��������  : �����û��·��Ĺһ��¼�
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventAppHangUpReq(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx      = VOS_NULL_PTR;

    /***********************************************************************************************
     * �����ǰ�����ܻ�����������������ܻ�ָʾ����֪ͨ�û��ܻ�ʧ�ܣ�ԭ���Ǻ����ͷ�
     **********************************************************************************************/
    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    if (TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE != pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_CALL_RELEASED,
                                       VOS_NULL_PTR);

        /* �˳��ܻ����� */
        TAF_XCALL_ExitVoiceEncriptProcedure();
    }
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVoiceEncEventKmcMoKeyRsp
 ��������  : ����KMC�·���MO��Կ��Ӧ�¼�
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventKmcMoKeyRsp(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx   = VOS_NULL_PTR;

    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    /***********************************************************************************************
     * ����յ����ܻ���Ϣ���͵�ǰ�ܻ����Ͳ�һ�£���ʾ�ܻ�ʧ��
     **********************************************************************************************/
    if ((TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MO_MUNAUL_MODE != pstKsNegoCtx->enEccVoiceType)
     && (TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MO_AUTO_MODE   != pstKsNegoCtx->enEccVoiceType))
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_ENC_VOICE_MODE_MIMATCH,
                                       VOS_NULL_PTR);

        /* �˳��ܻ����� */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    TAF_XCALL_ProcVoiceEncKmcKeyRsp((XSMS_XCALL_KMC_MSG_RCV_IND_STRU *)pMsg,
                                    (TAF_XCALL_KMC_MSG_STRU *)pKmcDecMsg,
                                    pstKsNegoCtx);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVoiceEncEventKmcMtKeyRsp
 ��������  : ����KMC�·���MT��Կ��Ӧ�¼�
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventKmcMtKeyRsp(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx   = VOS_NULL_PTR;

    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    /***********************************************************************************************
     * ����յ����ܻ���Ϣ���͵�ǰ�ܻ����Ͳ�һ�£���ʾ�ܻ�ʧ��
     **********************************************************************************************/
    if ((TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MT_MUNAUL_MODE != pstKsNegoCtx->enEccVoiceType)
     && (TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MT_AUTO_MODE   != pstKsNegoCtx->enEccVoiceType))
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_ENC_VOICE_MODE_MIMATCH,
                                       VOS_NULL_PTR);

        /* �˳��ܻ����� */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    TAF_XCALL_ProcVoiceEncKmcKeyRsp((XSMS_XCALL_KMC_MSG_RCV_IND_STRU *)pMsg,
                                    (TAF_XCALL_KMC_MSG_STRU *)pKmcDecMsg,
                                    pstKsNegoCtx);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVoiceEncEventKmcMtEncryptInd
 ��������  : ����KMC�·���MT��Կָʾ�¼�
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventKmcMtEncryptInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_ECC_SRV_CAP_INFO_STRU    *pstEccSrvCap  = VOS_NULL_PTR;
    TAF_XCALL_KMC_MSG_STRU             *pstKmcMsg     = VOS_NULL_PTR;
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx  = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    VOS_UINT32                          ulCallIdNum;

    /***********************************************************************************************
     * �����ǰUE��֧���ܻ��������ܻ��رգ������ܻ�ָʾ
     **********************************************************************************************/
    pstEccSrvCap = TAF_XCALL_GetVoiceEncryptCapCfgPara();

    if (VOS_FALSE == pstEccSrvCap->ucEccSrvStatus)
    {
        return;
    }

    /***********************************************************************************************
     * ��Ϣ����ʧ�ܣ������ܻ�ָʾ
     **********************************************************************************************/
    pstKmcMsg = (TAF_XCALL_KMC_MSG_STRU *)pKmcDecMsg;

    if (TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS != pstKmcMsg->enRslt)
    {
        return;
    }

    /***********************************************************************************************
     * �����ǰ�Ѿ������ܻ���������Ը��ܻ�ָʾ
     **********************************************************************************************/
    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    if (TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE != pstKsNegoCtx->enVoiceEncState)
    {
        return;
    }

    /***********************************************************************************
     * ���������·���л��޺��д��ڣ������ܻ�ָʾ
     **********************************************************************************/
    PS_MEM_SET(&aucCallIds[0], 0, sizeof(aucCallIds));

    ulCallIdNum = TAF_XCALL_GetAllUsedCallId(&aucCallIds[0]);

    if ((0                             == ulCallIdNum)
     || (TAF_XCALL_CALL_ENTITY_MAX_NUM == ulCallIdNum))
    {
        return;
    }

    /***********************************************************************************************
     * �����ǰ������MT���У�������ܻ�ָʾ
     **********************************************************************************************/
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(aucCallIds[0]);

    if (MN_CALL_DIR_MT != pstCallEntity->enCallDir)
    {
        return;
    }

    /***********************************************************************************************
     * �������״̬����incoming��active״̬��������ܻ�ָʾ
     **********************************************************************************************/
    if ((MN_CALL_S_INCOMING != pstCallEntity->enCallState)
     && (MN_CALL_S_ACTIVE   != pstCallEntity->enCallState))
    {
        return;
    }

    /***********************************************************************************************
     * ת���ܻ�ָʾ�еĺ��룬������BCD���ʽ����
     **********************************************************************************************/
    pstKsNegoCtx->stCallNum.ucNumLen = TAF_XCALL_ConvertRemoteNumFromKmcBcdToStdBcd(pstKmcMsg->u.stMtEncryptInd.aucRemoteNumber,
                                                                                    pstKmcMsg->u.stMtEncryptInd.ucRemoteNumberLen,
                                                                                    pstKsNegoCtx->stCallNum.aucBcdNum,
                                                                                    TAF_ECC_CALL_MAX_BCD_NUM_LEN);

    /***********************************************************************************************
     * ����ܻ����������ʵ������Ƿ�һ��
     **********************************************************************************************/
    /* ������к���(���Զ˺���)����ʱ���Ž��к���Ƚ� */
    if (VOS_TRUE == TAF_XCALL_IsCallingNumExist(pstCallEntity))
    {
        if (VOS_FALSE == TAF_XCALL_IsEncVoiceNumberSameAsCallNumber(pstCallEntity->stCallNumber.ucNumLen,
                                                                    &pstCallEntity->stCallNumber.aucBcdNum[0],
                                                                    &(pstKsNegoCtx->stCallNum)))
        {
            /* �ܻ�ָʾ�еĺ��������з����벻һ�£����Ը��ܻ�ָʾ */
            TAF_XCALL_ExitVoiceEncriptProcedure();

            return;
        }
    }


    /***********************************************************************************************
     * ֪ͨ�û����и������ܻ�
     **********************************************************************************************/
    TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                   TAF_CALL_APP_ENCRYPT_VOICE_MT_CALL_NOTIFICATION,
                                   &pstKsNegoCtx->stCallNum);

    pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_AP_ENCRYPT_REQ;
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVoiceEncEventKmcErrInd
 ��������  : ����KMC�·���MT��Կ��Ӧ�¼�
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventKmcErrInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx = VOS_NULL_PTR;
    TAF_XCALL_KMC_MSG_STRU                                 *pstKmcMsg    = VOS_NULL_PTR;
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enEncVoiceErrCause;


    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    /***********************************************************************************************
     * �����ǰ�����ڵȴ�KMC���ܻ���Ӧʱ��ֱ�ӷ���
     **********************************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP != pstKsNegoCtx->enVoiceEncState)
    {
        return;
    }

    /***********************************************************************************************
     * ת��ʧ��ԭ��ֵ��֪ͨ�û��ܻ�ʧ�ܣ�ֹͣ��ض�ʱ��
     **********************************************************************************************/
    pstKmcMsg = (TAF_XCALL_KMC_MSG_STRU *)pKmcDecMsg;

    switch (pstKmcMsg->u.stErrInd.enErrCause)
    {
        case TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_LOCAL_NO_PERMISSION:
            enEncVoiceErrCause = TAF_CALL_APP_ENCRYPT_VOICE_LOCAL_TERMINAL_NO_AUTHORITY;
            break;

        case TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_REMOTE_NO_PERMISSION:
            enEncVoiceErrCause = TAF_CALL_APP_ENCRYPT_VOICE_REMOTE_TERMINAL_NO_AUTHORITY;
            break;

        case TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_LOCAL_ILLEGAL:
            enEncVoiceErrCause = TAF_CALL_APP_ENCRYPT_VOICE_LOCAL_TERMINAL_ILLEGAL;
            break;

        case TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_REMOTE_ILLEGAL:
            enEncVoiceErrCause = TAF_CALL_APP_ENCRYPT_VOICE_REMOTE_TERMINAL_ILLEGAL;
            break;

        case TAF_XCALL_KMC_MSG_ERR_IND_CAUSE_ESTABLISH_TIME_OUT:
            enEncVoiceErrCause = TAF_CALL_APP_ENCRYPT_VOICE_TIMEOUT;
            break;

        default:
            enEncVoiceErrCause = TAF_CALL_APP_ENCRYPT_VOICE_UNKNOWN_ERROR;
            break;
    }

    TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                   enEncVoiceErrCause,
                                   VOS_NULL_PTR);

    /* �˳��ܻ����� */
    TAF_XCALL_ExitVoiceEncriptProcedure();
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVoiceEncEventIncomingCallInd
 ��������  : ����XCC�ı���ָʾ
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventIncomingCallInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx = VOS_NULL_PTR;

    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    /***********************************************************************************************
     * �����ͻ����: �ܻ������Ѿ��յ�������δ�յ��û����������������ʱ����յ����У��ܾ���ǰ�ܻ���
     * ��ͨ����
     **********************************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE != pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_FAILURE_CAUSED_BY_INCOMING_CALL,
                                       VOS_NULL_PTR);

        /* �˳��ܻ����� */
        TAF_XCALL_ExitVoiceEncriptProcedure();
    }
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVoiceEncEventXccDiscInd
 ��������  : �����յ�XCC�绰�Ͽ�ָʾ
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventXccDiscInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx      = VOS_NULL_PTR;

    /***********************************************************************************************
     * �����ǰ�����ܻ�����������������ܻ�ָʾ����֪ͨ�û��ܻ�ʧ�ܣ�ԭ���Ǻ����ͷ�
     **********************************************************************************************/
    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    if (TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE != pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_CALL_RELEASED,
                                       VOS_NULL_PTR);

        /* �˳��ܻ����� */
        TAF_XCALL_ExitVoiceEncriptProcedure();
    }
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVoiceEncEventXccTchAssignCmplInd
 ��������  : �����յ�XCC TCHָ�����ָʾ
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventXccTchAssignCmplInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx = VOS_NULL_PTR;

    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    /***********************************************************************************************
     * �����ǰ�ܻ�����״̬���ڵȴ�TCHָ��ָʾ״̬��ֱ�ӷ��أ�
     **********************************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_TCH_ASSIGN_CMPL != pstKsNegoCtx->enVoiceEncState)
    {
        return;
    }

    /***********************************************************************************************
     * ��ǰ״̬Ϊ�ȴ�TCHָ��ָʾ״̬���������ܻ�������ʱ���Ͷ�ʱ����״̬Ǩ�Ƶ���ʱ�ȴ��ܻ�������״
     * ̬
     **********************************************************************************************/
    TAF_XCALL_StartTimer(TI_TAF_XCALL_DELAY_SEND_ENCRYPT_REQ,
                         TAF_XCALL_GetVoiceEncryptReqDelaySendTimerLen() * 1000,
                         0);

    /* Ǩ��״̬��TAF_XCALL_VOICE_ENCRYPT_STA_DELAY_SEND_ENCRYPT_REQ */
    pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_DELAY_SEND_ENCRYPT_REQ;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVoiceEncEventXccEccServiceCnf
 ��������  : �����յ�XCC ECC SOȷ����Ϣ
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventXccEccServiceCnf(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    XCC_XCALL_ECC_SERVICE_CNF_STRU     *pstEccSrvCnf = VOS_NULL_PTR;
    TAF_XCALL_KS_NEGOTIATE_CTX         *pstKsNegoCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulCallDir;

    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    pstEccSrvCnf = (XCC_XCALL_ECC_SERVICE_CNF_STRU *)pMsg;

    /***********************************************************************************************
     * �����ǰ�ܻ�����״̬���ڵȴ�ECC_SERVICE_CNF��ֱ�ӷ���
     **********************************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ECC_SERVICE_CNF != pstKsNegoCtx->enVoiceEncState)
    {
        return;
    }

    /***********************************************************************************************
     * ���ҵ��Э�̲��ɹ�����֪ͨ�û�����ʧ��
     **********************************************************************************************/
    /* ֹͣTX02��ʱ�� */
    TAF_XCALL_StopTimer(TI_TAF_XCALL_TX02_TIMER, 0);

    if (XCC_XCALL_ECC_SERVICE_RESULT_SUCC != pstEccSrvCnf->enRslt)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_SO_NEGO_FAILURE,
                                       VOS_NULL_PTR);

        /* �˳��ܻ����� */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    /***********************************************************************************************
     * ���üӽ���֮ǰ�������ȵ���voice��ʼ��������
     * outgoingcall����ʾ�����ܻ����ն��Ƿ������У�1 Ϊ���У�0 Ϊ���С�
     **********************************************************************************************/
    if ((TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MO_MUNAUL_MODE == pstKsNegoCtx->enEccVoiceType)
     || (TAF_CALL_APP_ENCRYPT_VOICE_TYPE_MO_AUTO_MODE   == pstKsNegoCtx->enEccVoiceType))
    {
        ulCallDir = VOS_TRUE;
    }
    else
    {
        ulCallDir = VOS_FALSE;
    }

    if (VOS_FALSE == TAF_XCALL_CipherInitVoice(&pstKsNegoCtx->stKsInfo.aucKs[0], ulCallDir))
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_INIT_VOICE_FUNC_FAILURE,
                                       VOS_NULL_PTR);

        /* �˳��ܻ����� */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    /***********************************************************************************************
     * �ն��յ��ĻỰ��Կ Ks����������ʱ��˽Կ����ʹ�ý�����Ӧ����ɾ�������ݲ���
    *  �ָ�������0����
     **********************************************************************************************/
    PS_MEM_SET(&pstKsNegoCtx->stKsInfo, 0, sizeof(TAF_XCALL_KS_INFO_STRU));

    TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                   TAF_CALL_APP_ENCRYPT_VOICE_SUCC,
                                   VOS_NULL_PTR);

    TAF_XCALL_SendCttf1xMacEncryptVoiceNtf(MACITF_1X_ECC_VOICE_ENCRYPT_TYPE);

    /* Ǩ��״̬��TAF_XCALL_VOICE_ENCRYPT_STA_ENCRYPT_ACTIVE */
    pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_ENCRYPT_ACTIVE;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVoiceEncEventXccAnswerCnf
 ��������  : �����յ�XCC���н���Ӧ����Ϣ
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventXccAnswerCnf(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    XCC_XCALL_ANSWER_CALL_CNF_STRU                         *pstAnswerCallCnf = VOS_NULL_PTR;
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx     = VOS_NULL_PTR;
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enSendRslt;

    pstAnswerCallCnf = (XCC_XCALL_ANSWER_CALL_CNF_STRU *)pMsg;

    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    /***********************************************************************************************
     * �����ǰ�ܻ�����״̬���ڵȴ��ܻ���������״̬��ֱ���˳�
     **********************************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_WATIING_CALL_ACCEPT_REQ != pstKsNegoCtx->enVoiceEncState)
    {
        return;
    }

    /***********************************************************************************************
     * �������ʧ�ܣ���֪ͨ�û��ܻ�ʧ�ܣ�ԭ��ֵΪ���н���ʧ��
     **********************************************************************************************/
    if (TAF_XCC_CAUSE_SUCCESS != pstAnswerCallCnf->enCause)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_CALL_ANSWER_REQ_FAILURE,
                                       VOS_NULL_PTR);

        /* �˳��ܻ����� */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    /***********************************************************************************************
     * ����KMC�ܻ������������ʧ�ܣ�֪ͨ�û����ܻ�����ʧ�ܣ���������TX01��ʱ������Ǩ��״̬
     **********************************************************************************************/
    /* ����call ID��Ϣ */
    pstKsNegoCtx->ucCallId = pstAnswerCallCnf->ucCallId;

    enSendRslt = TAF_XCALL_SendKmcKeyReqMsg(pstKsNegoCtx);

    if (TAF_CALL_APP_ENCRYPT_VOICE_SUCC != enSendRslt)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       enSendRslt,
                                       VOS_NULL_PTR);

        /* �˳��ܻ����� */
        TAF_XCALL_ExitVoiceEncriptProcedure();

        return;
    }

    /* ����TX01��ʱ�� */
    TAF_XCALL_StartTimer(TI_TAF_XCALL_TX01_TIMER, TI_TAF_XCALL_TX01_LEN, 0);

    /* Ǩ��״̬��TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP */
    pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP;

}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVoiceEncEventXsmsSendCnf
 ��������  : �����յ�XSMS�ܻ�������ȷ����Ϣ
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventXsmsSendCnf(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx   = VOS_NULL_PTR;
    XSMS_XCALL_KMC_MSG_SEND_CNF_STRU                       *pstXsmsSendCnf = VOS_NULL_PTR;
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enEncVoiceStatus;

    pstXsmsSendCnf = (XSMS_XCALL_KMC_MSG_SEND_CNF_STRU *)pMsg;

    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    /***********************************************************************************************
     * �����ǰ�ܻ�����״̬���ڵȴ��ܻ�reponse״̬��ֱ���˳�
     **********************************************************************************************/
    if (TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP != pstKsNegoCtx->enVoiceEncState)
    {
        return;
    }

    /***********************************************************************************************
     * �����ǰ�ܻ�������Ϣ���ͳɹ��������κβ����������ȴ�KMC����Ӧ
     **********************************************************************************************/
    if (XSMS_XCALL_SEND_RESULT_SUCC == pstXsmsSendCnf->enRslt)
    {
        return;
    }

    /***********************************************************************************************
     * �����ǰ�ܻ�������Ϣ����ʧ�ܣ�����XSMS�ϱ���ԭ��ֵ��֪ͨ�û��ܻ�ʧ��
     **********************************************************************************************/
    switch (pstXsmsSendCnf->enRslt)
    {
        case XSMS_XCALL_SEND_RESULT_FAIL:
            enEncVoiceStatus = TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_FAIL;
            break;

        case XSMS_XCALL_SEND_RESULT_POOL_FULL:
            enEncVoiceStatus = TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_POOL_FULL;
            break;

        case XSMS_XCALL_SEND_RESULT_LINK_ERR:
            enEncVoiceStatus = TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_LINK_ERR;
            break;

        case XSMS_XCALL_SEND_RESULT_NO_TL_ACK:
            enEncVoiceStatus = TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_NO_TL_ACK;
            break;

        case XSMS_XCALL_SEND_RESULT_ENCODE_ERR:
            enEncVoiceStatus = TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_ENCODE_ERR;
            break;

        default:
            enEncVoiceStatus = TAF_CALL_APP_ENCRYPT_VOICE_XSMS_SEND_RESULT_UNKNOWN;
            break;
    }

    TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                   enEncVoiceStatus,
                                   VOS_NULL_PTR);

    /* �˳��ܻ����� */
    TAF_XCALL_ExitVoiceEncriptProcedure();
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVoiceEncEventTimerWaitOrigReq
 ��������  : ����ȴ�ORIG����ʱ����ʱ����ʱ
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventTimerWaitOrigReq(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx      = VOS_NULL_PTR;

    /***********************************************************************************************
     * �����ǰ���ڵȴ���������ʱ���ȴ�orig req��ʱ����֪ͨӦ���ܻ�����ʱ
     **********************************************************************************************/
    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    if (TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ORIG_REQ == pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_TIMEOUT,
                                       VOS_NULL_PTR);

        /* �˳��ܻ����� */
        TAF_XCALL_ExitVoiceEncriptProcedure();
    }
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVoiceEncEventTimerDelaySendEncReq
 ��������  : ������ʱ�ܻ�������ʱ����ʱ����ʱ
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventTimerDelaySendEncReq(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx = VOS_NULL_PTR;
    TAF_CALL_APP_ENCRYPT_VOICE_STATUS_ENUM_UINT32           enSendRslt;

    /***********************************************************************************************
     * �����ǰ״̬���ܻ�������ʱ����״̬�������ܻ����󣬷��ͳɹ�������TX01��ʱ����״̬Ǩ�Ƶ�
     * �ȴ��ܻ�������Ӧ״̬
     **********************************************************************************************/
    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    if (TAF_XCALL_VOICE_ENCRYPT_STA_DELAY_SEND_ENCRYPT_REQ == pstKsNegoCtx->enVoiceEncState)
    {
        enSendRslt = TAF_XCALL_SendKmcKeyReqMsg(pstKsNegoCtx);

        if (TAF_CALL_APP_ENCRYPT_VOICE_SUCC != enSendRslt)
        {
            TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                           enSendRslt,
                                           VOS_NULL_PTR);

            /* �˳��ܻ����� */
            TAF_XCALL_ExitVoiceEncriptProcedure();

            return;
        }

        /* ����TX01��ʱ�� */
        TAF_XCALL_StartTimer(TI_TAF_XCALL_TX01_TIMER, TI_TAF_XCALL_T301_LEN, 0);

        /* Ǩ��״̬��TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP */
        pstKsNegoCtx->enVoiceEncState = TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVoiceEncEventTimerTx01
 ��������  : ����TX01��ʱ����ʱ�¼�
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventTimerTx01(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx      = VOS_NULL_PTR;

    /***********************************************************************************************
     * �����ǰ���ڵȴ��ܻ���Ӧ״̬���յ�TX01��ʱ��ʱ��֪ͨӦ���ܻ���ʱ���ͷ��ܻ���������Ϣ
     * ����״̬������
     **********************************************************************************************/
    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    if (TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ENCRYPT_RSP == pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_TX01_TIMEOUT,
                                       VOS_NULL_PTR);

        /* �˳��ܻ����� */
        TAF_XCALL_ExitVoiceEncriptProcedure();
    }
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVoiceEncEventTimerTx02
 ��������  : ����TX02��ʱ����ʱ�¼�
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventTimerTx02(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx      = VOS_NULL_PTR;

    /***********************************************************************************************
     * �����ǰ���ڵȴ�ECC SERVICE CNF״̬���յ�TX02��ʱ��ʱ��֪ͨӦ���ܻ���ʱ���ͷ��ܻ���������Ϣ
     * ����״̬������
     **********************************************************************************************/
    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    if (TAF_XCALL_VOICE_ENCRYPT_STA_WAITING_ECC_SERVICE_CNF == pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_TX02_TIMEOUT,
                                       VOS_NULL_PTR);

        /* �˳��ܻ����� */
        TAF_XCALL_ExitVoiceEncriptProcedure();
    }
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVoiceEncEventIntCallRelInd
 ��������  : �����ڲ���ɵĺ����ͷ�
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVoiceEncEventIntCallRelInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KS_NEGOTIATE_CTX                             *pstKsNegoCtx      = VOS_NULL_PTR;

    /***********************************************************************************************
     * �����ǰ�����ܻ�����������������ܻ�ָʾ����֪ͨ�û��ܻ�ʧ�ܣ�ԭ���Ǻ����ͷ�
     **********************************************************************************************/
    pstKsNegoCtx = TAF_XCALL_GetKsNegotiateCtxAddr();

    if (TAF_XCALL_VOICE_ENCRYPT_STA_INACTIVE != pstKsNegoCtx->enVoiceEncState)
    {
        TAF_XCALL_SndAppEncryptVoiceInd(&pstKsNegoCtx->stCcaCtrl,
                                       TAF_CALL_APP_ENCRYPT_VOICE_CALL_RELEASED,
                                       VOS_NULL_PTR);

        /* �˳��ܻ����� */
        TAF_XCALL_ExitVoiceEncriptProcedure();
    }
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcPubKeyEventKmcUpdateInd
 ��������  : ����KMC�Ĺ�Կ����������Ϣ
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : l00359089
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcPubKeyEventKmcUpdateInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KMC_MSG_STRU                                  stKmcSndMsg;
    TAF_XCALL_KMC_MSG_STRU                                 *pstKmcMsg          = VOS_NULL_PTR;
    TAF_XCALL_ECC_PUB_KEY_INFO_STRU                        *pstEccPubKeyInfo   = VOS_NULL_PTR;
    TAF_XCALL_PUBLIC_KEY_UPDATE_CTX                        *pstPubKeyUpdateCtx = VOS_NULL_PTR;
    XSMS_XCALL_KMC_MSG_RCV_IND_STRU                        *pstXsmsRcvInd      = VOS_NULL_PTR;
    VOS_UINT8                                               ucWaitSignLen;

    pstXsmsRcvInd   = (XSMS_XCALL_KMC_MSG_RCV_IND_STRU *)pMsg;

    /***********************************************************************************************
     * ��Ϣ����ʧ�ܣ����Ը���Ϣ
     **********************************************************************************************/
    pstKmcMsg       = (TAF_XCALL_KMC_MSG_STRU *)pKmcDecMsg;

    if (TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS != pstKmcMsg->enRslt)
    {
        return;
    }

    pstPubKeyUpdateCtx = TAF_XCALL_GetPubKeyUpdateCtxAddr();
    /***********************************************************************************************
     * ����ǰ״̬����δ����״̬��˵����ʱ���и���������ִ�У������µ���Ϣ
     **********************************************************************************************/
    if (TAF_XCALL_K0_UPATE_STA_INACTIVE != pstPubKeyUpdateCtx->enK0UpdateState)
    {
        return;
    }

    /***********************************************************************************************
     * ����ǰ״̬��δ����״̬����ʱ��Ҫ�ж���Ϣ�еİ汾�ź��ն˵�ǰ�İ汾���Ƿ�һ�£�һ�µĻ�������
     **********************************************************************************************/
    /* ��ȡ���ش洢�Ĺ�Կ */
    pstEccPubKeyInfo = TAF_XCALL_GetVoiceEncryptPublicKeyAndVersionNumber();

    if ((pstEccPubKeyInfo->ucVerNum == pstKmcMsg->u.stPubKeyUpdateInd.ucKeyVersion))
    {
        return;
    }

    /* ǩ����֤ */
    ucWaitSignLen = pstKmcMsg->u.stPubKeyUpdateInd.stPubKey.ucKeyLen + TAF_XCALL_KMC_MSG_PUB_KEY_UPDATE_REQ_HEADER_LEN;

    if (VOS_FALSE == TAF_XCALL_VerifySignature(TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN,
                                               &pstEccPubKeyInfo->aucPubKey[0],
                                               pstKmcMsg->u.stPubKeyUpdateInd.stSignInfo.ucSignInfoLen,
                                               &(pstKmcMsg->u.stPubKeyUpdateInd.stSignInfo.aucSignInfo[0]),
                                               ucWaitSignLen,
                                               &(pstXsmsRcvInd->aucData[0])))
    {
        /*ǩ����֤ʧ��*/
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_XCALL_ProcPubKeyEventKmcUpdateInd: signature verify is failure!");

        return;
    }

    /***********************************************************************************
    * ��ȡ��Ϣ����opId, ǩ����֤�ɹ������͸�����Ӧ��Ϣ
    **********************************************************************************/
    pstPubKeyUpdateCtx->usWaitXsmsCnfOpId = TAF_XCALL_GetSendXsmsReqOpId();

    PS_MEM_SET(&stKmcSndMsg, 0, sizeof(TAF_XCALL_KMC_MSG_STRU));

    if (VOS_TRUE != TAF_XCALL_SendKmcUpdateRspMsg(pstPubKeyUpdateCtx->usWaitXsmsCnfOpId, &stKmcSndMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_XCALL_ProcPubKeyEventKmcUpdateInd: send KMC UPDATE RSP failure!");

        return;
    }

    /***********************************************************************************
    * ״̬Ǩ�Ƶ� �ȴ�KMC��Կ����ȷ��
    **********************************************************************************/
    pstPubKeyUpdateCtx->enK0UpdateState = TAF_XCALL_K0_UPATE_STA_WAIT_KMC_RSP;

    /*��KMC��Կ,�汾��,���������*/
    pstPubKeyUpdateCtx->ucPubKeyVerNum = pstKmcMsg->u.stPubKeyUpdateInd.ucKeyVersion;
    PS_MEM_CPY(pstPubKeyUpdateCtx->aucPubKey,
               pstKmcMsg->u.stPubKeyUpdateInd.stPubKey.aucKey,
               TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN);

    PS_MEM_CPY(pstPubKeyUpdateCtx->aucRandomData,
                stKmcSndMsg.u.stPubKeyUpdateRsp.aucRandomData,
                TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN);

    /* �����ȴ���Կ����ȷ����Ϣ��ʱ�� */
    TAF_XCALL_StartTimer(TI_TAF_XCALL_PUB_KEY_UPDATE_WAIT_ACK_TIMER, TI_TAF_XCALL_PUB_KEY_UPDATE_WAIT_ACK_LEN, 0);
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcPubKeyEventKmcUpdateAck
 ��������  : ����KMC�Ĺ�Կ����ȷ����Ϣ
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : l00359089
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcPubKeyEventKmcUpdateAck(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KMC_MSG_STRU                                 *pstKmcMsg       = VOS_NULL_PTR;
    TAF_XCALL_PUBLIC_KEY_UPDATE_CTX                        *pstPubKeyUpdateCtx = VOS_NULL_PTR;
    TAF_XCALL_ECC_PUB_KEY_INFO_STRU                        *pstEccPubKeyInfo   = VOS_NULL_PTR;

    pstKmcMsg          = (TAF_XCALL_KMC_MSG_STRU *)pKmcDecMsg;
    pstPubKeyUpdateCtx = TAF_XCALL_GetPubKeyUpdateCtxAddr();

    /***********************************************************************************
    * ״̬���� �ȴ�KMC��Կ����ȷ�ϣ�˵����ʱû�еȴ�����ȷ�ϣ����账��
    **********************************************************************************/
    if (TAF_XCALL_K0_UPATE_STA_WAIT_KMC_RSP !=pstPubKeyUpdateCtx->enK0UpdateState )
    {
        return;
    }

    /***********************************************************************************************
     * �����Ϣ����ʧ�ܣ��˳�����
     **********************************************************************************************/
    if (TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS != pstKmcMsg->enRslt)
    {
        TAF_XCALL_ExitPubKeyUpdateProcedure();
        return;
    }

    /***********************************************************************************
    * �յ���Ϣ�е�������뱾�ش洢�����������ȣ��˳�����
    **********************************************************************************/
    if (0 != PS_MEM_CMP(pstPubKeyUpdateCtx->aucRandomData, pstKmcMsg->u.stPubKeyUpdateAck.aucRandomData, TAF_XCALL_KMC_MSG_RANDOM_DATA_LEN))
    {
        TAF_XCALL_ExitPubKeyUpdateProcedure();
        return;
    }

    /***********************************************************************************
    * ����NV���͡��ܻ���ص������������еĹ�Կ�汾�ź͹�Կ
    **********************************************************************************/
    TAF_XCALL_WriteVoiceEncryptPublicKeyAndVersionNumber(pstPubKeyUpdateCtx->aucPubKey, pstPubKeyUpdateCtx->ucPubKeyVerNum);

    pstEccPubKeyInfo = TAF_XCALL_GetVoiceEncryptPublicKeyAndVersionNumber();
    PS_MEM_SET(pstEccPubKeyInfo, 0, sizeof(TAF_XCALL_ECC_PUB_KEY_INFO_STRU));
    pstEccPubKeyInfo->ucVerNum = pstPubKeyUpdateCtx->ucPubKeyVerNum;
    PS_MEM_CPY(pstEccPubKeyInfo->aucPubKey, pstPubKeyUpdateCtx->aucPubKey, sizeof(pstEccPubKeyInfo->aucPubKey));

    /***********************************************************************************
    * ���֮ǰ����Ĺ�Կ���������е���������Ϣ
    **********************************************************************************/
    TAF_XCALL_ExitPubKeyUpdateProcedure();
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcPubKeyEventXsmsSendCnf
 ��������  : ����Կ���µ�ȷ����Ϣ����ȷ�Ͻ����Ϣ
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : l00359089
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcPubKeyEventXsmsSendCnf(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    XSMS_XCALL_KMC_MSG_SEND_CNF_STRU   *pstXsmsSendCnf = VOS_NULL_PTR;

    pstXsmsSendCnf  = (XSMS_XCALL_KMC_MSG_SEND_CNF_STRU *)pMsg;

    /*OpId�ıȽ��Ѿ����ⲿ���й��ˣ��˴�����Ҫ�ٱȽ�*/

    /***********************************************************************************
    * ����ȷ�Ͻ�����ʧ�ܣ� ���֮ǰ�����KMC��Կ���µ���������Ϣ���ɹ���ʲôҲ����
    **********************************************************************************/
    if(XSMS_XCALL_SEND_RESULT_SUCC != pstXsmsSendCnf->enRslt)
    {
        TAF_XCALL_ExitPubKeyUpdateProcedure();
    }
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcRemoteCtrlEventAppRemoteCtrlAnswerReq
 ��������  : �����û��·���Զ�̿���Ӧ��������Ϣ
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcRemoteCtrlEventAppRemoteCtrlAnswerReq(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU               *pstAppRemoteAnswerReq = VOS_NULL_PTR;
    TAF_XCALL_REMOTE_CTRL_CTX                              *pstRemoteCtrlCtx      = VOS_NULL_PTR;
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_ENUM_UINT8       enRemoteCtrlRslt;
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM_UINT8       enRemoteCtrlType;

    pstAppRemoteAnswerReq = (TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ_STRU *)pMsg;

    pstRemoteCtrlCtx      = TAF_XCALL_GetRemoteCtrlCtxAddr();
    enRemoteCtrlRslt      = TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_BUTT;
    enRemoteCtrlType      = TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_BUTT;

    /* ֹͣԶ�̿���APӦ��ʱ�� */
    TAF_XCALL_StopTimer(TI_TAF_XCALL_REMOTE_CTRL_WAIT_AP_ANSWER_TIMER, 0);

    /* �쳣���� */
    switch (pstRemoteCtrlCtx->enRemoteCtrlState)
    {
        case TAF_XCALL_REMOTE_CTRL_STA_WAITING_AP_INFO_ERASE_RSP:
            {
                if (TAF_CALL_REMOTE_CTRL_SEC_INFO_ERASE != pstAppRemoteAnswerReq->enRemoteCtrlEvtType)
                {
                    TAF_XCALL_SndAppRemoteCtrlAnswerCnf(&pstAppRemoteAnswerReq->stCtrl, TAF_CALL_SEND_RESULT_OPER_TYPE_ERROR);

                    (VOS_VOID)TAF_XCALL_SendRemoteCtrlEventRsltToKmc(TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_SECURE_INFO_ERASE,
                                                                     TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_OTHER_FAILURE,
                                                                     pstRemoteCtrlCtx);

                    /* �쳣���˳�Զ�̿�������*/
                    TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

                    return;
                }

                enRemoteCtrlType    = TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_SECURE_INFO_ERASE;

                break;
            }
        case TAF_XCALL_REMOTE_CTRL_STA_WAITING_AP_PASSWORD_RESET_RSP:
            {
                if (TAF_CALL_REMOTE_CTRL_PASSWORD_RESET != pstAppRemoteAnswerReq->enRemoteCtrlEvtType)
                {
                    TAF_XCALL_SndAppRemoteCtrlAnswerCnf(&pstAppRemoteAnswerReq->stCtrl, TAF_CALL_SEND_RESULT_OPER_TYPE_ERROR);

                    (VOS_VOID)TAF_XCALL_SendRemoteCtrlEventRsltToKmc(TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_PWD_RESET,
                                                                     TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_OTHER_FAILURE,
                                                                     pstRemoteCtrlCtx);

                    /* �쳣���˳�Զ�̿�������*/
                    TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

                    return;
                }

                enRemoteCtrlType    = TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_PWD_RESET;

                break;
            }
        default:
            {
                TAF_XCALL_SndAppRemoteCtrlAnswerCnf(&pstAppRemoteAnswerReq->stCtrl, TAF_CALL_SEND_RESULT_OPER_NOT_ALLOWED);

                /* �쳣���˳�Զ�̿�������*/
                TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

                return;
            }
    }

    if (TAF_CALL_REMOTE_CTRL_APP_SUCC == pstAppRemoteAnswerReq->enResult)
    {
        enRemoteCtrlRslt    = TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_SUCCESS;

        /* SUCC���ö�Ӧ�������ͣ������յ�SMSȷ��ʱ��ˢ��NV */
        pstRemoteCtrlCtx->enRemoteCtrlCmdType   = enRemoteCtrlType;
    }
    else
    {
        enRemoteCtrlRslt    = TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_OTHER_FAILURE;
    }

    if (VOS_FALSE == TAF_XCALL_SendRemoteCtrlEventRsltToKmc(enRemoteCtrlType,
                                                            enRemoteCtrlRslt,
                                                            pstRemoteCtrlCtx))
    {
        TAF_XCALL_SndAppRemoteCtrlAnswerCnf(&pstAppRemoteAnswerReq->stCtrl, TAF_CALL_SEND_RESULT_INT_ERRROR);

        /* �쳣���˳�Զ�̿�������*/
        TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

        return;
    }

    /* ����Ctrlͷ���ظ���ʱ��ʹ�� */
    PS_MEM_CPY(&(pstRemoteCtrlCtx->stCcaCtrl), &(pstAppRemoteAnswerReq->stCtrl), sizeof(TAF_CCA_CTRL_STRU));

    /* ����״̬ */
    pstRemoteCtrlCtx->enRemoteCtrlState = TAF_XCALL_REMOTE_CTRL_STA_WAITING_RSP_SENT_RSLT;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcRemoteCtrlEventKmcRemoteCtrlCmdInd
 ��������  : ����KMC�·���Զ�̿�������������Ϣ
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcRemoteCtrlEventKmcRemoteCtrlCmdInd(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_KMC_MSG_STRU                                 *pstKmcMsg           = VOS_NULL_PTR;
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU             *pstRemoteCtrlInd    = VOS_NULL_PTR;
    TAF_XCALL_REMOTE_CTRL_CTX                              *pstRemoteCtrlCtx    = VOS_NULL_PTR;
    TAF_XCALL_ECC_PUB_KEY_INFO_STRU                        *pstPubKeyAndVer     = VOS_NULL_PTR;
    XSMS_XCALL_KMC_MSG_RCV_IND_STRU                        *pstXsmsRcvInd       = VOS_NULL_PTR;
    TAF_STD_TIME_ZONE_TYPE_STRU                            *pstLastSysTimeZone  = VOS_NULL_PTR;
    VOS_UINT8                                               aucSignData[TAF_XCALL_SIGN_DATA_INFO_MAX_LEN];
    TAF_XCALL_HARDWARE_ID_INFO_STRU                         stHardWareInfo;

    pstKmcMsg                           = (TAF_XCALL_KMC_MSG_STRU *)pKmcDecMsg;
    pstRemoteCtrlInd                    = (TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_IND_STRU *)(&(pstKmcMsg->u.stRemoteCtrlInd));
    pstXsmsRcvInd                       = (XSMS_XCALL_KMC_MSG_RCV_IND_STRU *)pMsg;
    pstRemoteCtrlCtx                    = TAF_XCALL_GetRemoteCtrlCtxAddr();
    pstPubKeyAndVer                     = TAF_XCALL_GetVoiceEncryptPublicKeyAndVersionNumber();

    PS_MEM_SET(aucSignData, 0x00, sizeof(aucSignData));
    PS_MEM_SET(&stHardWareInfo, 0x00, sizeof(TAF_XCALL_HARDWARE_ID_INFO_STRU));

    /* ״̬��� */
    if (TAF_XCALL_REMOTE_CTRL_STA_INACTIVE != pstRemoteCtrlCtx->enRemoteCtrlState)
    {
        /* ��������״̬��˵�����ڴ����������̣�������Ϣ */

        return;
    }

    /* ��Ϣ������󣬲��������Ϣ */
    if (TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS != pstKmcMsg->enRslt)
    {
        (VOS_VOID)TAF_XCALL_SendRemoteCtrlEventRsltToKmc(pstRemoteCtrlInd->enRomoteCtrlCmdType,
                                                         TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_OTHER_FAILURE,
                                                         pstRemoteCtrlCtx);

        TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

        return;
    }

    /* ��Կ�汾ƥ�� */
    if (pstPubKeyAndVer->ucVerNum != pstRemoteCtrlInd->ucKeyVersion)
    {
        /* ��Կ�汾��ƥ�� */
        (VOS_VOID)TAF_XCALL_SendRemoteCtrlEventRsltToKmc(pstRemoteCtrlInd->enRomoteCtrlCmdType,
                                                         TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_KEY_VERSION_MISMATCH_FAILURE,
                                                         pstRemoteCtrlCtx);

        /* �쳣���˳�Զ�̿�������*/
        TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

        return;
    }

    /* ���ݳ��ȼ�� */
    if (pstXsmsRcvInd->usDataLen < TAF_XCALL_SIGN_DATA_INFO_LEN)
    {
        /* ��Ϣ���Ȳ�ƥ�� */
        (VOS_VOID)TAF_XCALL_SendRemoteCtrlEventRsltToKmc(pstRemoteCtrlInd->enRomoteCtrlCmdType,
                                                         TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_SIGN_VERIFY_FAILURE,
                                                         pstRemoteCtrlCtx);

        /* �쳣���˳�Զ�̿�������*/
        TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

        return;
    }

    PS_MEM_CPY(aucSignData,
               pstXsmsRcvInd + (sizeof(XSMS_XCALL_KMC_MSG_RCV_IND_STRU) - sizeof(pstXsmsRcvInd->aucData)),
               sizeof(VOS_UINT8) * TAF_XCALL_SIGN_DATA_INFO_LEN);

    if (VOS_FALSE == TAF_XCALL_GetHardWareInfo(&stHardWareInfo))
    {
        /* HardWare��Ϣ��ȡʧ�� */
        (VOS_VOID)TAF_XCALL_SendRemoteCtrlEventRsltToKmc(pstRemoteCtrlInd->enRomoteCtrlCmdType,
                                                         TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_SIGN_VERIFY_FAILURE,
                                                         pstRemoteCtrlCtx);

        /* �쳣���˳�Զ�̿�������*/
        TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

        return;
    }

    aucSignData[TAF_XCALL_SIGN_DATA_INFO_LEN]       = TAF_XCALL_ENCVOICE_HARDWARE_ID_LEN + 1;
    aucSignData[TAF_XCALL_SIGN_DATA_INFO_LEN + 1]   = (VOS_UINT8)stHardWareInfo.enHardWareType;

    PS_MEM_CPY(&(aucSignData[TAF_XCALL_SIGN_DATA_INFO_LEN + 2]),
                 stHardWareInfo.aucHardWareIdInfo,
                 sizeof(VOS_UINT8) * TAF_XCALL_ENCVOICE_HARDWARE_ID_LEN);

    if (VOS_FALSE == TAF_XCALL_VerifySignature(TAF_XCALL_KMC_MSG_MAX_KMC_PUB_KEY_LEN,
                                               &(pstPubKeyAndVer->aucPubKey[0]),
                                               pstRemoteCtrlInd->stSignInfo.ucSignInfoLen,
                                               &(pstRemoteCtrlInd->stSignInfo.aucSignInfo[0]),
                                               TAF_XCALL_SIGN_DATA_INFO_MAX_LEN,
                                               &(aucSignData[0])))
    {
        /* ǩ����֤ʧ�� */
        (VOS_VOID)TAF_XCALL_SendRemoteCtrlEventRsltToKmc(pstRemoteCtrlInd->enRomoteCtrlCmdType,
                                                         TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_SIGN_VERIFY_FAILURE,
                                                         pstRemoteCtrlCtx);

        /* ǩ����֤ʧ�ܣ��˳�Զ�̿�������*/
        TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

        return;
    }

    /* ��ȡ��¼����һ�β�����ʱ�� */
    if (TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_SECURE_INFO_ERASE == pstRemoteCtrlInd->enRomoteCtrlCmdType)
    {
        pstLastSysTimeZone               = TAF_XCALL_GetVoiceEncryptSecInfoEraseSysTime();
    }
    else
    {
        pstLastSysTimeZone               = TAF_XCALL_GetVoiceEncryptPassWordResetSysTime();
    }

    /* ʱ������ */
    if (VOS_FALSE == TAF_XCALL_IsTimeStampValid(&(pstRemoteCtrlInd->stTimeStamp),
                                                  pstLastSysTimeZone))
    {
        /* ʱ������ʧ�� */
        (VOS_VOID)TAF_XCALL_SendRemoteCtrlEventRsltToKmc(pstRemoteCtrlInd->enRomoteCtrlCmdType,
                                                         TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_OTHER_FAILURE,
                                                         pstRemoteCtrlCtx);

        /* ���������㣬�˳�Զ�̿�������*/
        TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

        return;
    }

    /* ����ʱ��� */
    pstRemoteCtrlCtx->stTimeStamp       = pstRemoteCtrlInd->stTimeStamp;

    /* INFO ERASE */
    if (TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_SECURE_INFO_ERASE == pstRemoteCtrlInd->enRomoteCtrlCmdType)
    {
        TAF_XCALL_SndAppRemoteCtrlInd(&(pstRemoteCtrlCtx->stCcaCtrl), TAF_CALL_REMOTE_CTRL_SEC_INFO_ERASE);

        pstRemoteCtrlCtx->enRemoteCtrlState     = TAF_XCALL_REMOTE_CTRL_STA_WAITING_AP_INFO_ERASE_RSP;
    }
    else
    {
        /* PASSWD RESET */
        TAF_XCALL_SndAppRemoteCtrlInd(&(pstRemoteCtrlCtx->stCcaCtrl), TAF_CALL_REMOTE_CTRL_PASSWORD_RESET);

        pstRemoteCtrlCtx->enRemoteCtrlState     = TAF_XCALL_REMOTE_CTRL_STA_WAITING_AP_PASSWORD_RESET_RSP;
    }

    /* �����ȴ�APԶ�̿���Ӧ��ʱ�� */
    TAF_XCALL_StartTimer(TI_TAF_XCALL_REMOTE_CTRL_WAIT_AP_ANSWER_TIMER,
                         TAF_XCALL_GetRemoteCtrlWaitApAnswerTimerLen() * 1000,
                         0);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcRemoteCtrlEventXsmsSendCnf
 ��������  : ������Զ�̿�����Ӧ��Ϣ���ͽ���¼�
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcRemoteCtrlEventXsmsSendCnf(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    XSMS_XCALL_KMC_MSG_SEND_CNF_STRU                       *pstKmcMsgCnf            = VOS_NULL_PTR;
    TAF_XCALL_REMOTE_CTRL_CTX                              *pstRemoteCtrlCtx        = VOS_NULL_PTR;
    TAF_STD_TIME_ZONE_TYPE_STRU                            *pstLastRecTime          = VOS_NULL_PTR;

    pstKmcMsgCnf                        = (XSMS_XCALL_KMC_MSG_SEND_CNF_STRU *)pMsg;
    pstRemoteCtrlCtx                    = TAF_XCALL_GetRemoteCtrlCtxAddr();

    /* ��鵱ǰ״̬�Ƿ�ΪWAITING RSP RSLT */
    if (TAF_XCALL_REMOTE_CTRL_STA_WAITING_RSP_SENT_RSLT != pstRemoteCtrlCtx->enRemoteCtrlState)
    {
        /* ��ǰ��������״̬��������Ϣ */

        return;
    }

    /* ���ݽ���ظ�AT��Ϣ */
    if (XSMS_XCALL_SEND_RESULT_SUCC != pstKmcMsgCnf->enRslt)
    {
        TAF_XCALL_SndAppRemoteCtrlAnswerCnf(&(pstRemoteCtrlCtx->stCcaCtrl),
                                           TAF_CALL_SEND_RESULT_FAIL);

        /* ���Զ�̿������̣��˳�Զ�̿�������*/
        TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

        return;
    }

    TAF_XCALL_SndAppRemoteCtrlAnswerCnf(&(pstRemoteCtrlCtx->stCcaCtrl),
                                           TAF_CALL_SEND_RESULT_SUCC);

    /* Answer Req��RsltΪFail,��ˢ��NV */
    if (TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_BUTT == pstRemoteCtrlCtx->enRemoteCtrlCmdType)
    {
        /* ���Զ�̿������̣��˳�Զ�̿�������*/
        TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

        return;
    }

    /* ������������ˢ��NV�Ͷ�Ӧȫ�ֱ��� */
    if (TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_SECURE_INFO_ERASE == pstRemoteCtrlCtx->enRemoteCtrlCmdType)
    {
        pstLastRecTime                  = TAF_XCALL_GetVoiceEncryptSecInfoEraseSysTime();

        /* ��ֵȫ�ֱ��� */
        pstLastRecTime->usYear          = pstRemoteCtrlCtx->stTimeStamp.usYear;
        pstLastRecTime->usMonth         = pstRemoteCtrlCtx->stTimeStamp.usMonth;
        pstLastRecTime->usDay           = pstRemoteCtrlCtx->stTimeStamp.usDay;
        pstLastRecTime->usHour          = pstRemoteCtrlCtx->stTimeStamp.usHour;
        pstLastRecTime->usMinute        = pstRemoteCtrlCtx->stTimeStamp.usMinute;
        pstLastRecTime->usSecond        = pstRemoteCtrlCtx->stTimeStamp.usSecond;

        /* д��NV */
        TAF_XCALL_WriteVoiceEncryptSecInfoEraseSysTime(&(pstRemoteCtrlCtx->stTimeStamp));

        /* ���Զ�̿������̣��˳�Զ�̿�������*/
        TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

        return;
    }

    pstLastRecTime                      = TAF_XCALL_GetVoiceEncryptPassWordResetSysTime();

    /* ��ֵȫ�ֱ��� */
    pstLastRecTime->usYear              = pstRemoteCtrlCtx->stTimeStamp.usYear;
    pstLastRecTime->usMonth             = pstRemoteCtrlCtx->stTimeStamp.usMonth;
    pstLastRecTime->usDay               = pstRemoteCtrlCtx->stTimeStamp.usDay;
    pstLastRecTime->usHour              = pstRemoteCtrlCtx->stTimeStamp.usHour;
    pstLastRecTime->usMinute            = pstRemoteCtrlCtx->stTimeStamp.usMinute;
    pstLastRecTime->usSecond            = pstRemoteCtrlCtx->stTimeStamp.usSecond;

    TAF_XCALL_WriteVoiceEncryptPassWordResetSysTime(&(pstRemoteCtrlCtx->stTimeStamp));

    /* ���Զ�̿������̣��˳�Զ�̿�������*/
    TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcRemoteCtrlEventTimerWaitApAnswer
 ��������  : ������Զ�̿�����Ӧ��Ϣ���ͽ���¼�
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcRemoteCtrlEventTimerWaitApAnswer(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_REMOTE_CTRL_CTX          *pstRemoteCtrlCtx        = VOS_NULL_PTR;

    pstRemoteCtrlCtx = TAF_XCALL_GetRemoteCtrlCtxAddr();

    if ((TAF_XCALL_REMOTE_CTRL_STA_WAITING_AP_INFO_ERASE_RSP     != pstRemoteCtrlCtx->enRemoteCtrlState)
     && (TAF_XCALL_REMOTE_CTRL_STA_WAITING_AP_PASSWORD_RESET_RSP != pstRemoteCtrlCtx->enRemoteCtrlState))
    {
        return;
    }

    if (TAF_XCALL_REMOTE_CTRL_STA_WAITING_AP_INFO_ERASE_RSP == pstRemoteCtrlCtx->enRemoteCtrlState)
    {
        (VOS_VOID)TAF_XCALL_SendRemoteCtrlEventRsltToKmc(TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_SECURE_INFO_ERASE,
                                                         TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_OTHER_FAILURE,
                                                         pstRemoteCtrlCtx);
    }
    else
    {
        (VOS_VOID)TAF_XCALL_SendRemoteCtrlEventRsltToKmc(TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_PWD_RESET,
                                                         TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_OTHER_FAILURE,
                                                         pstRemoteCtrlCtx);
    }

    TAF_XCALL_ExitRemoteCtrlOpertionProcedure();

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_IsMkTimeParaValid
 ��������  : ���TimeZone�ṹ�����Ա��ֵ�Ƿ����MkTime������Ҫ��
 �������  : TAF_STD_TIME_ZONE_TYPE_STRU        *pstTimeZone ʱ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE:  ��Ч
             VOS_FALSE: ��Ч
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_IsMkTimeParaValid(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstTimeZone
)
{
    VOS_UINT8                           aucDaysOfMonth[TAF_XCALL_TIME_MONTHS_OF_ONE_YEAR] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    /* ���[1900,3000] */
    if ((pstTimeZone->usYear < 1900)
     || (pstTimeZone->usYear > 3000))
    {
        return VOS_FALSE;
    }

    /* �·�[1,12] */
    if ((pstTimeZone->usMonth < 1)
     || (pstTimeZone->usMonth > 12))
    {
        return VOS_FALSE;
    }

    /* �����2�·ݣ��ж������2�¼�һ�� */
    if (2 == pstTimeZone->usMonth)
    {
        if (((0 == (pstTimeZone->usYear % 4))
          && (0 != (pstTimeZone->usYear % 100)))
          || (0 == (pstTimeZone->usYear % 400)))
        {
            aucDaysOfMonth[pstTimeZone->usMonth - 1]++;
        }
    }

    /* ��[1,31] */
    if ((pstTimeZone->usDay < 1)
     || (pstTimeZone->usDay > aucDaysOfMonth[pstTimeZone->usMonth - 1]))
    {
        return VOS_FALSE;
    }

    /* Сʱ[0,23] */
    if (pstTimeZone->usHour > 23)
    {
        return VOS_FALSE;
    }

    /* ����[0,59] */
    if (pstTimeZone->usMinute > 59)
    {
        return VOS_FALSE;
    }

    /* ����[0,59] */
    if (pstTimeZone->usSecond > 59)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_GetTimeIntervalSince1970
 ��������  : ��ȡ��ǰʱ��ԭ��������ʱ��֮�������
 �������  : TAF_STD_TIME_ZONE_TYPE_STRU        *pstTimeZone ʱ��
 �������  : VOS_UINT64                         *pullTimeInterval
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE:  �ɹ�
             VOS_FALSE: ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_GetTimeIntervalSince1970(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstTimeZone,
    VOS_UINT64                         *pullTimeInterval
)
{
    TAF_XCALL_STD_TIME_ZONE_STRU        stTMTimeZone;
    VOS_UINT64                          ullRslt;

    ullRslt                             = VOS_FALSE;
    PS_MEM_SET(&stTMTimeZone, 0x00, sizeof(TAF_XCALL_STD_TIME_ZONE_STRU));

    if (VOS_FALSE == TAF_XCALL_IsMkTimeParaValid(pstTimeZone))
    {
        *pullTimeInterval               = 0;

        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_GetTimeIntervalSince1970():WARNING: Invalid Time Zone!");

        return VOS_FALSE;
    }

    stTMTimeZone.ulYear                 = (VOS_UINT32)(pstTimeZone->usYear - TAF_XCALL_TIME_STAMP_ORIG_YEAR);
    stTMTimeZone.ulMonth                = (VOS_UINT32)(pstTimeZone->usMonth - TAF_XCALL_MKTIME_MONTH_OFFSET);
    stTMTimeZone.ulDay                  = (VOS_UINT32)pstTimeZone->usDay;
    stTMTimeZone.ulHour                 = (VOS_UINT32)pstTimeZone->usHour;
    stTMTimeZone.ulMinute               = (VOS_UINT32)pstTimeZone->usMinute;
    stTMTimeZone.ulSecond               = (VOS_UINT32)pstTimeZone->usSecond;

    /* ת���ɴ�1970��1��1��0ʱ0��0��������� */

    /*lint -e571*/
    ullRslt                             = (VOS_UINT64)mktime((TAF_XCALL_MKTIME_TM_STRU *)&stTMTimeZone);
    /*lint +e571*/

    if (TAF_XCALL_STIME_INVALID_VALUE == ullRslt)
    {
        *pullTimeInterval               = 0;

        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_GetTimeIntervalSince1970():WARNING: mktime failed!");

        return VOS_FALSE;
    }

    *pullTimeInterval                   = ullRslt;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ConvertCurSysTime80msToStdTimeIntervalSince1970
 ��������  : ��ϵͳʱ��ת���ɴӵ�ǰʱ��ԭ���������
 �������  : VOS_UINT64 : ��CDMA_Timing_GetSystemTime80ms��ȡ�ĵ�ǰϵͳʱ��(80ms)
 �������  : VOS_UINT64 : *pullStdSysTime
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE:  �ɹ�
             VOS_FASLE: ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_ConvertCurSysTime80msToStdTimeIntervalSince1970(
    VOS_UINT64                          ullCurSysTime,
    VOS_UINT64                         *pullStdSysTime
)
{
    TAF_STD_TIME_ZONE_TYPE_STRU         stOrigTimeZone;
    VOS_UINT64                          ullTimeInterval;

    ullTimeInterval                     = 0;

    /* 1980��1��6��0ʱ0��0�� */
    PS_MEM_SET(&stOrigTimeZone, 0x00, sizeof(TAF_STD_TIME_ZONE_TYPE_STRU));
    stOrigTimeZone.usYear               = TAF_XCALL_SYSTIME_ORIGINAL_YEAR;
    stOrigTimeZone.usMonth              = TAF_XCALL_SYSTIME_ORIGINAL_MONTH;
    stOrigTimeZone.usDay                = TAF_XCALL_SYSTIME_ORIGINAL_DAY;

    /* ���ʱ������������ֹ��ת */
    if (ullCurSysTime > TAF_XCALL_STIME_MAX_INTERVAL_VALUE)
    {
        return VOS_FALSE;
    }

    /* ��ȡ1980��1��6��0ʱ0��0�����1970��1��1��0ʱ0��0������� */
    if (VOS_FALSE == TAF_XCALL_GetTimeIntervalSince1970(&stOrigTimeZone, &ullTimeInterval))
    {
        return VOS_FALSE;
    }

    /* ����ǰ80ms���������1��ĸ�����������1980��1��6�յ�1970��1��1�յ�ʱ���� */
    *pullStdSysTime = ullTimeInterval + (VOS_UINT64)TAF_XCALL_STIME_CONVERT_80MS_TO_1S(ullCurSysTime);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_IsTimeZoneEmpty
 ��������  : �ж�ʱ��ṹ�Ƿ�Ϊ��
 �������  : TAF_STD_TIME_ZONE_TYPE_STRU        *pstTimeZone
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE:  Ϊ��
             VOS_FASLE: ��Ϊ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_IsTimeZoneEmpty(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstTimeZone
)
{
    TAF_STD_TIME_ZONE_TYPE_STRU         stNullTimeZone;

    PS_MEM_SET(&stNullTimeZone, 0x00, sizeof(TAF_STD_TIME_ZONE_TYPE_STRU));

    if (0 == PS_MEM_CMP(pstTimeZone, &stNullTimeZone, sizeof(TAF_STD_TIME_ZONE_TYPE_STRU)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_IsTimeStampValid
 ��������  : �ж�����ʱ����Ƿ����Ҫ��
 �������  : pucTimeStamp: ʱ���
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE:  ʱ�������Ҫ��
             VOS_FALSE: ʱ���������Ҫ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_IsTimeStampValid(
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstTimeStamp,
    TAF_STD_TIME_ZONE_TYPE_STRU        *pstLastSysTimeZone
)
{
    VOS_UINT64                          ullSysTimeInterval80ms;
    VOS_UINT64                          ullStdSysTimeInterval;
    VOS_UINT64                          ullStdMsgTimeInterval;
    VOS_UINT64                          ullStdLastTimeInterval;

    ullSysTimeInterval80ms              = 0;
    ullStdSysTimeInterval               = 0;
    ullStdMsgTimeInterval               = 0;
    ullStdLastTimeInterval              = 0;

    /* ���ԭ��:
       1.����ʱ�䣬����ʱ�䣬���һ�ε�ʱ��
       ��ѯ�ն����һ�εİ�ȫ��Ϣ����������¼�����û�м�¼����ֱ�ӽ������
       ���̣�����ʱ������ڼ�¼�еĲ���ʱ�䣬�����ڼ�¼����ʱ��������ڣ���
       �˳�ָ�����������������

       2.��ʱ����뵱ǰ����ʱ����ȣ���ʱ������ڱ���ʱ��24Сʱ֮�ڣ������
       �������̣������˳�ָ���  */

    /* ��ȡ��1980��1��6�������ϵͳʱ�� */
    ullSysTimeInterval80ms              = CDMA_Timing_GetSystemTime80ms(CDMA_TIMING_RTT_1X);

    if (TAF_XCALL_STIME_INVALID_VALUE == ullSysTimeInterval80ms)
    {
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_IsTimeStampValid():WARNING: ullCurSysTime Invalid!");

        return VOS_FALSE;
    }

    /* ��ϵͳʱ��ת����1970��1��1�յ����� */
    if (VOS_FALSE == TAF_XCALL_ConvertCurSysTime80msToStdTimeIntervalSince1970(ullSysTimeInterval80ms, &ullStdSysTimeInterval))
    {
        /* ϵͳʱ��ת��ʧ�� */
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_IsTimeStampValid():WARNING: Convert Systime Failed!");

        return VOS_FALSE;
    }

    /* ���������ȡ����ʱ��ת�������� */
    if (VOS_FALSE == TAF_XCALL_GetTimeIntervalSince1970(pstTimeStamp, &ullStdMsgTimeInterval))
    {
        /* ����ʱ��ת��ʧ�� */
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_IsTimeStampValid():WARNING: Get Msg Time Interval Failed!");

        return VOS_FALSE;
    }

    /* ��ϵͳ��¼����һ�ε�ʱ��Ϊ�գ��򲻼��˴���Ϣ���ϴβ�����ʱ�����Ƿ���5�������� */
    if (VOS_FALSE == TAF_XCALL_IsTimeZoneEmpty(pstLastSysTimeZone))
    {
        /* �������գ�ʱ����ת������1970��1��1��0ʱ0��0����ļ������ */
        if (VOS_FALSE == TAF_XCALL_GetTimeIntervalSince1970(pstLastSysTimeZone, &ullStdLastTimeInterval))
        {
            /* ����ת��ʧ�� */
            TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_IsTimeStampValid():WARNING: Get Last Time Interval Failed!");

            return VOS_FALSE;
        }

        /* �������5�������ڻ�������һ�μ�¼��ʱ���������Ϊʱ���������Ҫ�� */
        if (ullStdMsgTimeInterval < (ullStdLastTimeInterval + TAF_XCALL_TIME_INTERVAL_5MINUTS))
        {
            TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_IsTimeStampValid():WARNING: Not Over 5 Minutes!");

            return VOS_FALSE;
        }
    }

    /* ����ȡ��ϵͳʱ��������С��1�죬����Ϊ��ȡ�쳣������ʧ�� */
    if (ullStdSysTimeInterval < TAF_XCALL_TIME_INTERVAL_ONEDAY)
    {
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_IsTimeStampValid():WARNING: Sys Time Interval Less Than 1 Day!");

        return VOS_FALSE;
    }

    /* ����Ϣ��ʱ�����ڵ�ǰϵͳʱ��24Сʱ������, �������ڵ�ǰϵͳ��ʱ�䣬����Ϊʱ�����Ч */
    if ((ullStdMsgTimeInterval <= (ullStdSysTimeInterval - TAF_XCALL_TIME_INTERVAL_ONEDAY))
     || (ullStdMsgTimeInterval > ullStdSysTimeInterval))
    {
        TAF_INFO_LOG(WUEPS_PID_TAF, "TAF_XCALL_IsTimeStampValid():WARNING: Not In 24 Hours!");

        return VOS_FALSE;
    }

    /* ��ӡ */
    TAF_XCALL_MNTN_LogTimeStampValidation(pstTimeStamp,
                                          pstLastSysTimeZone,
                                          ullStdSysTimeInterval,
                                          ullStdLastTimeInterval,
                                          ullStdMsgTimeInterval);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_GenerateEncVoicePlainText
 ��������  : ��IMSI, HardWare Id, ���к������BCD����ϲ���һ��������,����������Ϣ
 �������  : VOS_UINT8                                              *pucImsiInfo,
             TAF_XCALL_HARDWARE_ID_INFO_STRU                        *pstHardWareId,
             TAF_ECC_CALL_BCD_NUM_STRU                              *pstCalledNum,
 �������  : TAF_XCALL_PLAIN_TEXT_INFO_STRU                         *pstPlainTextInfo
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE:  �ϲ��ɹ�
             VOS_FALSE: �ϲ�ʧ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_GenerateEncVoicePlainText(
    VOS_UINT8                                              *pucImsiInfo,
    TAF_XCALL_HARDWARE_ID_INFO_STRU                        *pstHardWareId,
    TAF_ECC_CALL_BCD_NUM_STRU                              *pstCalledNum,
    TAF_XCALL_PLAIN_TEXT_INFO_STRU                         *pstPlainTextInfo
)
{
    VOS_UINT8                          *pucPlainTextContent   = VOS_NULL_PTR;
    VOS_UINT8                           ucPlainTextInfoLen;
    VOS_UINT8                           aucStdCalledNum[TAF_XCALL_CALLEDNUM_INFO_MAX_LEN];
    VOS_UINT8                           aucStdImsi[TAF_XCALL_IMSI_INFO_LEN];

    pucPlainTextContent                 = pstPlainTextInfo->aucContent;
    PS_MEM_SET(aucStdCalledNum, 0x00, sizeof(aucStdCalledNum));
    PS_MEM_SET(aucStdImsi, 0x00, sizeof(aucStdImsi));
    ucPlainTextInfoLen                  = 0;

    /* ƴ��Imsi */
    *pucPlainTextContent                = TAF_XCALL_IMSI_INFO_LEN;
    pucPlainTextContent++;
    ucPlainTextInfoLen++;

    /* Imsi����ת�� */
    if (VOS_FALSE == TAF_XCALL_ConvertImsiFromStdBcdToKmcBcd(pucImsiInfo,
                                                             aucStdImsi,
                                                             TAF_XCALL_IMSI_INFO_LEN))
    {
        PS_MEM_SET(pstPlainTextInfo, 0x00, sizeof(TAF_XCALL_PLAIN_TEXT_INFO_STRU));

        return VOS_FALSE;
    }

    PS_MEM_CPY(pucPlainTextContent, aucStdImsi, sizeof(VOS_UINT8) * TAF_XCALL_IMSI_INFO_LEN);
    pucPlainTextContent += TAF_XCALL_IMSI_INFO_LEN;
    ucPlainTextInfoLen  += TAF_XCALL_IMSI_INFO_LEN;

    /* ƴ��HardWareInfo */
    *pucPlainTextContent                = TAF_XCALL_ENCVOICE_HARDWARE_ID_LEN + 1;
    pucPlainTextContent++;
    ucPlainTextInfoLen++;

    *pucPlainTextContent                = (VOS_UINT8)pstHardWareId->enHardWareType;
    pucPlainTextContent++;
    ucPlainTextInfoLen++;

    /* MEIDС�˴洢��ֱ�Ӹ��� */
    PS_MEM_CPY(pucPlainTextContent, pstHardWareId->aucHardWareIdInfo, sizeof(VOS_UINT8) * TAF_XCALL_ENCVOICE_HARDWARE_ID_LEN);
    pucPlainTextContent += TAF_XCALL_ENCVOICE_HARDWARE_ID_LEN;
    ucPlainTextInfoLen  += TAF_XCALL_ENCVOICE_HARDWARE_ID_LEN;

    /* ƴ��CalledNum */
    *pucPlainTextContent                = TAF_XCALL_CALLEDNUM_INFO_MAX_LEN;
    pucPlainTextContent++;
    ucPlainTextInfoLen++;

    /* ���к����ʽת�� */
    if (VOS_FALSE == TAF_XCALL_ConvertRemoteNumFromStdBcdToKmcBcd(pstCalledNum->aucBcdNum,
                                                                  pstCalledNum->ucNumLen,
                                                                  aucStdCalledNum,
                                                                  TAF_XCALL_CALLEDNUM_INFO_MAX_LEN))
    {
        PS_MEM_SET(pstPlainTextInfo, 0x00, sizeof(TAF_XCALL_PLAIN_TEXT_INFO_STRU));

        return VOS_FALSE;
    }

    PS_MEM_CPY(pucPlainTextContent, aucStdCalledNum, sizeof(VOS_UINT8) * TAF_XCALL_CALLEDNUM_INFO_MAX_LEN);
    ucPlainTextInfoLen  += TAF_XCALL_CALLEDNUM_INFO_MAX_LEN;

    pstPlainTextInfo->ucNumLen            = ucPlainTextInfoLen;

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_SendRemoteCtrlEventRsltToKmc
 ��������  : Remote Ctrl Ind��Ϣʧ�ܵĴ���
 �������  : TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM_UINT8       enRemoteCtrlCmdType,  ��������
             TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_ENUM_UINT8       enRemoteCtrlRsltType  Զ�̿�����Ϣ�ظ����
             TAF_XCALL_REMOTE_CTRL_CTX                              *pstRemoteCtrlCtx      Զ�̿�����Ϣ������
 �������  : ��
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE   :���ͳɹ�
             VOS_FALSE  :����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_SendRemoteCtrlEventRsltToKmc(
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_TYPE_ENUM_UINT8       enRemoteCtrlCmdType,
    TAF_XCALL_KMC_MSG_ROMOTE_CTRL_CMD_RSLT_ENUM_UINT8       enRemoteCtrlRsltType,
    TAF_XCALL_REMOTE_CTRL_CTX                              *pstRemoteCtrlCtx
)
{
    TAF_XCALL_KMC_MSG_STRU                                  stKmcMsg;
    VOS_UINT16                                              usKmMsgLen;
    VOS_UINT8                                               aucKmcMsg[TAF_XCALL_KMC_MSG_WMS_CDMA_USER_DATA_MAX];

    PS_MEM_SET(&stKmcMsg, 0x00, sizeof(TAF_XCALL_KMC_MSG_STRU));
    PS_MEM_SET(aucKmcMsg, 0x00, sizeof(aucKmcMsg));
    usKmMsgLen                                              = 0;

    /* ����ظ�����Ϣ */
    stKmcMsg.enSmsType                                      = TAF_XCALL_KMC_MSG_TYPE_ROMOTE_CTRL_CMD_RSP;
    stKmcMsg.u.stRemoteCtrlRsp.enRomoteCtrlCmdType          = enRemoteCtrlCmdType;
    stKmcMsg.u.stRemoteCtrlRsp.enExecuteRslt                = enRemoteCtrlRsltType;
    stKmcMsg.u.stRemoteCtrlRsp.ucKeyVersion                 = TAF_XCALL_GetVoiceEncryptPublicKeyAndVersionNumber()->ucVerNum;

    if (TAF_XCALL_KMC_MSG_PROCESS_RSLT_SUCCESS == TAF_XCALL_EncodeKmcMsg(&stKmcMsg, &aucKmcMsg[0], &usKmMsgLen))
    {
        pstRemoteCtrlCtx->usWaitXsmsCnfOpId = TAF_XCALL_GetSendXsmsReqOpId();

        /* ����KMC��Ϣ��XSMS */
        TAF_XCALL_SendXsmsKmcMsgSendReq(pstRemoteCtrlCtx->usWaitXsmsCnfOpId, usKmMsgLen, aucKmcMsg);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_GetHardWareInfo
 ��������  : ��ȡӲ����Ϣ
 �������  :
 �������  : TAF_XCALL_HARDWARE_ID_INFO_STRU                         stHardWareIdInfo
 �� �� ֵ  : VOS_UINT32
             VOS_TRUE:  ��ȡ�ɹ�
             VOS_FALSE: ��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
VOS_UINT32 TAF_XCALL_GetHardWareInfo(
    TAF_XCALL_HARDWARE_ID_INFO_STRU                        *pstHardWareIdInfo
)
{
    VOS_UINT8                                              *pucHardWareInfo = VOS_NULL_PTR;
    VOS_UINT8                                               aucInvalidHardWareId[TAF_XCALL_ENCVOICE_HARDWARE_ID_LEN];

    PS_MEM_SET(aucInvalidHardWareId, TAF_XCALL_INVALID_HARDWARE_ID, sizeof(VOS_UINT8) * TAF_XCALL_ENCVOICE_HARDWARE_ID_LEN);

    pstHardWareIdInfo->enHardWareType   = TAF_XCALL_HARDWARE_ID_TYPE_MEID;
    pstHardWareIdInfo->ucHardWareIdLen  = TAF_XCALL_HARDWARE_TYPE_MEID_LEN;
    pucHardWareInfo                     = TAF_SDC_GetSdcCtx()->stPhoneInfo.stHardWareInfo.aucMeId;

    if (0 == PS_MEM_CMP(aucInvalidHardWareId, TAF_SDC_GetSdcCtx()->stPhoneInfo.stHardWareInfo.aucMeId, sizeof(VOS_UINT8) * TAF_XCALL_HARDWARE_TYPE_MEID_LEN))
    {
        /* ��Meid��Ч�����ESN�Ƿ���� */
        if (0 == PS_MEM_CMP(aucInvalidHardWareId, &(TAF_SDC_GetSdcCtx()->stPhoneInfo.stHardWareInfo.ulEsn), sizeof(VOS_UINT32)))
        {
            PS_MEM_SET(pstHardWareIdInfo, 0x00, sizeof(TAF_XCALL_HARDWARE_ID_INFO_STRU));

            /* HardWareId��Ч */
            return VOS_FALSE;
        }

        pstHardWareIdInfo->enHardWareType       = TAF_XCALL_HARDWARE_ID_TYPE_ESN;
        pstHardWareIdInfo->ucHardWareIdLen      = TAF_XCALL_HARDWARE_TYPE_ESN_LEN;
        pucHardWareInfo                         = (VOS_UINT8 *)(&(TAF_SDC_GetSdcCtx()->stPhoneInfo.stHardWareInfo.ulEsn));
    }

    PS_MEM_CPY((VOS_UINT8 *)&(pstHardWareIdInfo->aucHardWareIdInfo[TAF_XCALL_ENCVOICE_HARDWARE_ID_LEN - 1]) - pstHardWareIdInfo->ucHardWareIdLen + 1,
               pucHardWareInfo,
               sizeof(VOS_UINT8) * pstHardWareIdInfo->ucHardWareIdLen);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ConvertRemoteNumFromKmcBcdToStdBcd
 ��������  : ��KMC��������BCD ��ʽ�ĺ���ת�ɱ�׼BCD ��ʽ�ĺ���
             eg. 000000012345  --->  2143F5FFFFFF
                 000000123456  --->  214365FFFFFF
 �������  : VOS_UINT8  *pucKmcBcdNum  KMC��������BCD ��ʽ�ĺ���
             VOS_UINT8  ucKmcBcdNumLen  KMC��������BCD ��ʽ�ĺ�����ռ�ֽ���
             VOS_UINT8  ucStdBcdNumLen Ϊ��׼BCD ��ʽ�ĺ��������ֽ���
 �������  : VOS_UINT8  *pucStdBcdNum, ת����ĺ���

 �� �� ֵ  : VOS_UINT32 ת���ɱ�׼BCD ��ʽ����Ч���볤��(����ȥ���OXFF�ĳ���)
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��29��
    ��    ��   : l00359089
    �޸�����   : Iteration 19
*****************************************************************************/
VOS_UINT8 TAF_XCALL_ConvertRemoteNumFromKmcBcdToStdBcd(
    VOS_UINT8                          *pucKmcBcdNum,
    VOS_UINT8                           ucKmcBcdNumLen,
    VOS_UINT8                          *pucStdBcdNum,
    VOS_UINT8                           ucStdBcdNumLen
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;
    VOS_UINT8                           ucIsOddNum;

    ucIsOddNum                          = VOS_FALSE;

    /*�жϺ��볤���Ƿ�Ϊ����,�����һ����Ϊ0�����ĸ��ֽ���0,��Ϊ����*/
    for (i = 0; i < ucKmcBcdNumLen; i++)
    {
        if ( 0 != pucKmcBcdNum[i])
        {
            ucIsOddNum = (pucKmcBcdNum[i] & 0xF0) ? VOS_FALSE : VOS_TRUE;
            break;
        }
    }

    /*1 ��i����ucKmcBcdNumLenʱ,˵�� KMC�������ĺ���ȫΪ0,����Ч�ĺ���,���޷�ת��
      2 ����׼BCD ��ʽ�ĺ������Ŀռ�,С�� KMC�������ĺ������Ч����,���޷�ת��*/
    if ((ucKmcBcdNumLen == i)
     || (ucStdBcdNumLen < (ucKmcBcdNumLen - i)))
    {
        PS_MEM_SET(&pucStdBcdNum[0], 0xFF, ucStdBcdNumLen);
        return 0;
    }

    if (VOS_FALSE == ucIsOddNum)
    {
        /* ���ߵ�4λ��λ�û��� */
        for (j = 0; i < ucKmcBcdNumLen; j++, i++)
        {
            pucStdBcdNum[j]  = (VOS_UINT8)((pucKmcBcdNum[i] & 0x0F) << 4);
            pucStdBcdNum[j] |= (VOS_UINT8)((pucKmcBcdNum[i] & 0xF0) >> 4);
        }
    }
    else
    {
        for (j = 0; i < ucKmcBcdNumLen; j++, i++)
        {
            pucStdBcdNum[j] = (pucKmcBcdNum[i] & 0x0F);
            if ((i + 1) < ucKmcBcdNumLen )
            {
                pucStdBcdNum[j] |= (pucKmcBcdNum[i+1] & 0xF0) ;
            }
            else
            {
                pucStdBcdNum[j] |= 0xF0;
            }
        }
    }

    /*��ʣ��ռ����ΪOxFF*/
    if (j < ucStdBcdNumLen)
    {
        PS_MEM_SET(&pucStdBcdNum[j], 0xFF, (ucStdBcdNumLen - j));
    }

    return j ;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcPubKeyEventTimerWaitAck
 ��������  : ����ȴ���Կ����ȷ����Ϣ��ʱ����ʱ�¼�
 �������  : VOS_VOID *pMsg  -- �¼���Ӧ����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015-11-10
    ��    ��   : l00359089
    �޸�����   : �����ɺ��� for iteration 19
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcPubKeyEventTimerWaitAck(
    VOS_VOID                           *pMsg,
    VOS_VOID                           *pKmcDecMsg
)
{
    TAF_XCALL_PUBLIC_KEY_UPDATE_CTX    *pstPubKeyUpdateCtx = VOS_NULL_PTR;

    pstPubKeyUpdateCtx = TAF_XCALL_GetPubKeyUpdateCtxAddr();

    /***********************************************************************************
    * ״̬���ڵȴ�KMC��Կ����ȷ�ϣ��˳���������
    **********************************************************************************/
    if (TAF_XCALL_K0_UPATE_STA_WAIT_KMC_RSP == pstPubKeyUpdateCtx->enK0UpdateState )
    {
        TAF_XCALL_ExitPubKeyUpdateProcedure();
    }
}

#endif

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
