/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXCallMain.c
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2014��09��03��
  ��������   : TAF X CALLģ���ʼ������ں�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��09��03��
    ��    ��   : l60609
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXCallMain.h"
#include "TafXCallProcApp.h"
#include "TafXCallProcXcc.h"
#include "TafXCallProcMma.h"
#include "TafXCallProcVc.h"
#include "TafXCallMntn.h"
#include "AtMnInterface.h"
#include "xcc_xcall_pif.h"
#include "VcCallInterface.h"
#include "TafXCallProcTimer.h"
#include "TafXCallProcUsim.h"

#include "TafAppCall.h"
#include "TafXCallProcXsms.h"
#include "TafXCallProcCttf.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* TAF XCALL ģ�鴦������AT/STK��Ϣ������Ӧ��*/
const TAF_XCALL_MSG_PROC_STRU g_astTafXcallMsgProcAppTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
    {MN_CALL_APP_ORIG_REQ,                    TAF_XCALL_RcvAppCallOrigReq},
    {MN_CALL_APP_SUPS_CMD_REQ,                TAF_XCALL_RcvAppSupsCmdReq},
    {TAF_CALL_APP_SEND_FLASH_REQ,             TAF_XCALL_RcvAppSendFlashReq},
    {TAF_CALL_APP_SEND_BURST_DTMF_REQ,        TAF_XCALL_RcvAppSendBurstDTMFReq},
    {ID_TAFAGENT_MN_GET_CALL_INFO_REQ,        TAF_XCALL_RcvAgentGetCallInfoReq},
    {MN_CALL_APP_GET_INFO_REQ,                TAF_XCALL_RcvAppGetCallInfoReq},
    {MN_CALL_APP_XLEMA_REQ,                   TAF_XCALL_RcvAppXlemaReq},
    {TAF_CALL_APP_SEND_CUSTOM_DIAL_REQ,       TAF_XCALL_RcvAppCustomDialReq},
    {TAF_CALL_APP_SEND_CONT_DTMF_REQ,         TAF_XCALL_RcvAppSendContDTMFReq},
    {TAF_CALL_APP_SEND_CCLPR_REQ,             TAF_XCALL_RcvAtCclprGetReq},

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    {ID_TAF_CALL_APP_ENCRYPT_VOICE_REQ,       TAF_XCALL_RcvAppEncryptVoiceReq},
    {ID_TAF_CALL_APP_REMOTE_CTRL_ANSWER_REQ,  TAF_XCALL_RcvAppRemoteCtrlAnswerReq},
    {ID_TAF_CALL_APP_ECC_SRV_CAP_CFG_REQ,     TAF_XCALL_RcvAppEccSrvCapCfgReq},
    {ID_TAF_CALL_APP_ECC_SRV_CAP_QRY_REQ,     TAF_XCALL_RcvAppEccSrvCapQryReq},
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
    {ID_TAF_CALL_APP_GET_EC_TEST_MODE_REQ,    TAF_XCALL_RcvAppEccTestModeQryReq},
    {ID_TAF_CALL_APP_SET_EC_TEST_MODE_REQ,    TAF_XCALL_RcvAppEccTestModeCfgReq},
    {ID_TAF_CALL_APP_GET_EC_KMC_REQ,          TAF_XCALL_RcvAppEccKmcKeyQryReq},
    {ID_TAF_CALL_APP_SET_EC_KMC_REQ,          TAF_XCALL_RcvAppEccKmcKeyCfgReq},
    {ID_TAF_CALL_APP_GET_EC_RANDOM_REQ,       TAF_XCALL_RcvAppEccRandomQryReq},
#endif
#endif

    {ID_TAF_CALL_APP_PRIVACY_MODE_SET_REQ,    TAF_XCALL_RcvAppPrivacyModeSetReq},

    {ID_TAF_CALL_APP_PRIVACY_MODE_QRY_REQ,    TAF_XCALL_RcvAppPrivacyModeQryReq},
    {MN_CALL_APP_CUSTOM_ECC_NUM_REQ,          TAF_XCALL_RcvAppEccNumSetReq},
};

/* TAF XCALL ģ�鴦������XCC��Ϣ������Ӧ��*/
const TAF_XCALL_MSG_PROC_STRU g_astTafXcallMsgProcXccTab[]=
{
    /* ��ϢID */                                /* ��Ϣ������ */
    {ID_XCC_XCALL_ORIG_CALL_CNF,              TAF_XCALL_RcvXccCallOrigCnf},

    {ID_XCC_XCALL_HANGUP_CALL_CNF,            TAF_XCALL_RcvXccCallHangUpCnf},

    {ID_XCC_XCALL_CALL_DISC_IND,              TAF_XCALL_RcvXccCallDiscInd},

    {ID_XCC_XCALL_INCOMING_CALL_IND,          TAF_XCALL_RcvXccCallIncomingInd},
    {ID_XCC_XCALL_ANSWER_CALL_CNF,            TAF_XCALL_RcvXccCallAnswerCnf},
    {ID_XCC_XCALL_CALL_CONNECT_IND,           TAF_XCALL_RcvXccCallConnectInd},

    {ID_XCC_XCALL_SEND_FLASH_CNF,             TAF_XCALL_RcvXccSendFlashCnf},

    {ID_XCC_XCALL_INFO_REC_IND,               TAF_XCALL_RcvXccInfoRecInd},

    {ID_XCC_XCALL_SEND_BURST_DTMF_CNF,        TAF_XCALL_RcvXccSendBurstDTMFCnf},

    {ID_XCC_XCALL_CODEC_OPEN_IND,             TAF_XCALL_RcvXccCodecOpenInd},
    {ID_XCC_XCALL_CODEC_CLOSE_IND,            TAF_XCALL_RcvXccCodecCloseInd},
    {ID_XCC_XCALL_CODEC_CHANGED_IND,          TAF_XCALL_RcvXccCodecChangedInd},
    {ID_XCC_XCALL_SO_CTRL_MSG_IND,            TAF_XCALL_RcvXccSoCtrlMsgInd},
    {ID_XCC_XCALL_SO_CTRL_ORDER_IND,          TAF_XCALL_RcvXccSoCtrlOrderInd},

    {ID_XCC_XCALL_NDSS_RESULT_IND,            TAF_XCALL_RcvXccNdssResultInd},

    {ID_XCC_XCALL_SEND_CONT_DTMF_CNF,         TAF_XCALL_RcvXccSendContDTMFCnf},

    {ID_XCC_XCALL_BURST_DTMF_IND,             TAF_XCALL_RcvXccBurstDtmfInd},

    {ID_XCC_XCALL_CONT_DTMF_IND,             TAF_XCALL_RcvXccContDtmfInd},

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    {ID_XCC_XCALL_ECC_SERVICE_CNF,           TAF_XCALL_RcvXccEccServiceCnf},

    {ID_XCC_XCALL_TCH_ASSIGN_CMPL_IND,       TAF_XCALL_RcvXccTchAssignCmplInd},
#endif

    {ID_XCC_XCALL_PRIVACY_MODE_SET_CNF,      TAF_XCALL_RcvXccPrivacyModeSetCnf},

    {ID_XCC_XCALL_PRIVACY_MODE_QRY_CNF,      TAF_XCALL_RcvXccPrivacyModeQryCnf},

    {ID_XCC_XCALL_PRIVACY_MODE_IND,          TAF_XCALL_RcvXccPrivacyModeInd},
};

/* TAF XCALL ģ�鴦������MMA��Ϣ������Ӧ��*/
const TAF_XCALL_MSG_PROC_STRU g_astTafXcallMsgProcMmaTab[]=
{
    {MMA_TAF_POWER_OFF_IND,                   TAF_XCALL_RcvMmaPowerOffInd},
    {ID_MMA_TAF_1X_SERVICE_STATUS_IND,        TAF_XCALL_RcvMmaServiceStatusInd},
    {ID_MMA_TAF_SYS_CFG_INFO_IND,             TAF_XCALL_RcvMmaSysCfgInfoInd},
};

/* TAF XCALL ģ�鴦������VC��Ϣ������Ӧ��*/
const TAF_XCALL_MSG_PROC_STRU g_astTafXcallMsgProcVcTab[]=
{
    /* ��ϢID */                              /* ��Ϣ������ */
    {VC_CALL_END_CALL,                      TAF_XCALL_RcvVcEndCall},
};

const TAF_XCALL_MSG_PROC_STRU g_astTafXcallMsgProcTimerTab[]=
{
    /* ��ϢID */                                                /* ��Ϣ������ */
    {TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD,                      TAF_XCALL_RcvTiWaitCallRedialPeriodExpired},

    {TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL,                    TAF_XCALL_RcvTiWaitCallRedialIntervalExpired},

    {TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL,            TAF_XCALL_RcvTiStartAndStopContDtmfIntervalExpired},

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    {TI_TAF_XCALL_VOICE_ENCRYPT_WAIT_ORIG_REQ_TIMER,            TAF_XCALL_RcvTiVoiceEncryptWaitOrigReqExpired},

    {TI_TAF_XCALL_DELAY_SEND_ENCRYPT_REQ,                       TAF_XCALL_RcvTiDelayEncryptReqExpired},

    {TI_TAF_XCALL_TX01_TIMER,                                   TAF_XCALL_RcvTiTx01Expired},

    {TI_TAF_XCALL_TX02_TIMER,                                   TAF_XCALL_RcvTiTx02Expired},

    {TI_TAF_XCALL_REMOTE_CTRL_WAIT_AP_ANSWER_TIMER,             TAF_XCALL_RcvTiRemoteCtrlWaitApAnswerExpired},

    {TI_TAF_XCALL_PUB_KEY_UPDATE_WAIT_ACK_TIMER,                TAF_XCALL_RcvTiPubKeyUpdateWaitAckExpired},
#endif
};


#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
const TAF_XCALL_MSG_PROC_STRU g_astTafXcallMsgProcXsmsTab[]=
{
    {ID_XSMS_XCALL_KMC_MSG_RCV_IND,                         TAF_XCALL_RcvXsmsKmcMsgRcvInd},

    {ID_XSMS_XCALL_KMC_MSG_SEND_CNF,                        TAF_XCALL_RcvXsmsKmcMsgSendCnf}
};

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
const TAF_XCALL_MSG_PROC_STRU g_astTafXcallMsgProcCttfTab[]=
{
    {ID_CTTF_CNAS_1X_DECRYPT_VOICE_DATA_REPORT_IND,         TAF_XCALL_RcvCttfDecryptVoiceDataReportInd},

    {ID_CTTF_CNAS_1X_DECRYPT_VOICE_STATISTICS_REPORT_IND,   TAF_XCALL_RcvCttfDecryptVoiceStatReportInd},

    {ID_CTTF_CNAS_1X_ENCRYPT_VOICE_DATA_REPORT_IND,         TAF_XCALL_RcvCttfEncryptVoiceDataReportInd},

    {ID_CTTF_CNAS_1X_ENCRYPT_VOICE_STATISTICS_REPORT_IND,   TAF_XCALL_RcvCttfEncryptVoiceStatReportInd}
};
#endif
#endif


const VOS_UINT32 g_ulTafXcallMsgProcAppTabSize  = sizeof(g_astTafXcallMsgProcAppTab) / sizeof(g_astTafXcallMsgProcAppTab[0]);

const VOS_UINT32 g_ulTafXcallMsgProcXccTabSize  = sizeof(g_astTafXcallMsgProcXccTab) / sizeof(g_astTafXcallMsgProcXccTab[0]);

const VOS_UINT32 g_ulTafXcallMsgProcMmaTabSize  = sizeof(g_astTafXcallMsgProcMmaTab) / sizeof(g_astTafXcallMsgProcMmaTab[0]);

const VOS_UINT32 g_ulTafXcallMsgProcVcTabSize   = sizeof(g_astTafXcallMsgProcVcTab) / sizeof(g_astTafXcallMsgProcVcTab[0]);

const VOS_UINT32 g_ulTafXcallMsgProcTimerTabSize = sizeof(g_astTafXcallMsgProcTimerTab) / sizeof(g_astTafXcallMsgProcTimerTab[0]);


#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
const VOS_UINT32 g_ulTafXcallMsgProcXsmsTabSize  = sizeof(g_astTafXcallMsgProcXsmsTab) / sizeof(g_astTafXcallMsgProcXsmsTab[0]);
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
const VOS_UINT32 g_ulTafXcallMsgProcCttfTabSize  = sizeof(g_astTafXcallMsgProcCttfTab) / sizeof(g_astTafXcallMsgProcCttfTab[0]);
#endif
#endif


/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/


/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcAppReqMsg
 ��������  : 1x Call��������Ӧ�ò��������Ϣ
 �������  : struct MsgCB* pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��3��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_ProcAppReqMsg(struct MsgCB* pstMsg)
{
    VOS_UINT32                          ulIndex;
    TAF_XCALL_MSG_PROC_FUNC             pProcMsgFunc = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    /* ��g_astTafXcallMsgProcAppTab�в��Ҷ�Ӧ����Ϣ������ */
    for (ulIndex = 0; ulIndex < g_ulTafXcallMsgProcAppTabSize; ulIndex++)
    {
        if (g_astTafXcallMsgProcAppTab[ulIndex].ulMsgType == pstMsgHeader->ulMsgName)
        {
            /* Msg Id ƥ�� */
            pProcMsgFunc = g_astTafXcallMsgProcAppTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* ������������������ */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        /* ��Ϣ����ǰ��һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();

        pProcMsgFunc(pstMsg);

        /* ��Ϣ�����һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcXccMsg
 ��������  : ��������XCC����Ϣ
 �������  : struct MsgCB* pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��3��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_ProcXccMsg(struct MsgCB* pstMsg)
{
    VOS_UINT32                          ulIndex;
    TAF_XCALL_MSG_PROC_FUNC             pProcMsgFunc = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    /* ��g_astTafXcallMsgProcXccTab�в��Ҷ�Ӧ����Ϣ������ */
    for (ulIndex = 0; ulIndex < g_ulTafXcallMsgProcXccTabSize; ulIndex++)
    {
        if (g_astTafXcallMsgProcXccTab[ulIndex].ulMsgType == pstMsgHeader->ulMsgName)
        {
            /* Msg Id ƥ�� */
            pProcMsgFunc = g_astTafXcallMsgProcXccTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* ������������������ */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        /* ��Ϣ����ǰ��һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();

        pProcMsgFunc(pstMsg);

        /* ��Ϣ�����һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcVcMsg
 ��������  : ��������VC����Ϣ
 �������  : struct MsgCB* pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��3��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_ProcVcMsg(struct MsgCB* pstMsg)
{
    VOS_UINT32                          ulIndex;
    TAF_XCALL_MSG_PROC_FUNC             pProcMsgFunc = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    /* ��g_astTafXcallMsgProcVcTab�в��Ҷ�Ӧ����Ϣ������ */
    for (ulIndex = 0; ulIndex < g_ulTafXcallMsgProcVcTabSize; ulIndex++)
    {
        if (g_astTafXcallMsgProcVcTab[ulIndex].ulMsgType == pstMsgHeader->ulMsgName)
        {
            /* Msg Id ƥ�� */
            pProcMsgFunc = g_astTafXcallMsgProcVcTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* ������������������ */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        pProcMsgFunc(pstMsg);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcMmaMsg
 ��������  : ��������MMA����Ϣ
 �������  : struct MsgCB* pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��11��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_ProcMmaMsg(struct MsgCB* pstMsg)
{
    VOS_UINT32                          ulIndex;
    TAF_XCALL_MSG_PROC_FUNC             pProcMsgFunc = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    /* ��g_astTafXcallMsgProcMmaTab�в��Ҷ�Ӧ����Ϣ������ */
    for (ulIndex = 0; ulIndex < g_ulTafXcallMsgProcMmaTabSize; ulIndex++)
    {
        if (g_astTafXcallMsgProcMmaTab[ulIndex].ulMsgType == pstMsgHeader->ulMsgName)
        {
            /* Msg Id ƥ�� */
            pProcMsgFunc = g_astTafXcallMsgProcMmaTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* ������������������ */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        /* ��Ϣ����ǰ��һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();

        pProcMsgFunc(pstMsg);

        /* ��Ϣ�����һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcTimerOutMsg
 ��������  : 1x Call��������timer out��Ϣ
 �������  : struct MsgCB* pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��17��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_ProcTimerOutMsg(
    REL_TIMER_MSG                      *pTmrMsg
)
{
    VOS_UINT32                          ulIndex;
    TAF_XCALL_MSG_PROC_FUNC             pProcMsgFunc = VOS_NULL_PTR;
    TAF_XCALL_TIMER_ID_ENUM_UINT32      enTimerId;

    enTimerId = pTmrMsg->ulName;

    /* ��g_astTafXcallMsgProcTimerTab�в��Ҷ�Ӧ����Ϣ������ */
    for (ulIndex = 0; ulIndex < g_ulTafXcallMsgProcTimerTabSize; ulIndex++)
    {
        if (g_astTafXcallMsgProcTimerTab[ulIndex].ulMsgType == enTimerId)
        {
            /* Msg Id ƥ�� */
            pProcMsgFunc = g_astTafXcallMsgProcTimerTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* ������������������ */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        /* ��Ϣ����ǰ��һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();

        TAF_XCALL_StopTimer(enTimerId, (VOS_UINT8)pTmrMsg->ulPara);

        pProcMsgFunc(pTmrMsg);

        /* ��Ϣ�����һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcUsimMsg
 ��������  : ��������USIM����Ϣ
 �������  : struct MsgCB* pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��18��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_ProcUsimMsg(struct MsgCB* pstMsg)
{

    return;
}



#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcXsmsMsg
 ��������  : ��������XSMS����Ϣ
 �������  : struct MsgCB* pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��24��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcXsmsMsg(struct MsgCB* pstMsg)
{
    VOS_UINT32                          ulIndex;
    TAF_XCALL_MSG_PROC_FUNC             pProcMsgFunc = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    /* ��g_astTafXcallMsgProcXsmsTab�в��Ҷ�Ӧ����Ϣ������ */
    for (ulIndex = 0; ulIndex < g_ulTafXcallMsgProcXsmsTabSize; ulIndex++)
    {
        if (g_astTafXcallMsgProcXsmsTab[ulIndex].ulMsgType == pstMsgHeader->ulMsgName)
        {
            /* Msg Id ƥ�� */
            pProcMsgFunc = g_astTafXcallMsgProcXsmsTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* ������������������ */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        /* ��Ϣ����ǰ��һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();

        pProcMsgFunc(pstMsg);

        /* ��Ϣ�����һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();
    }

    return;
}

#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
/*****************************************************************************
 �� �� ��  : TAF_XCALL_ProcCttfMsg
 ��������  : ��������CTTF����Ϣ
 �������  : struct MsgCB* pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��24��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XCALL_ProcCttfMsg(struct MsgCB* pstMsg)
{
    VOS_UINT32                          ulIndex;
    TAF_XCALL_MSG_PROC_FUNC             pProcMsgFunc = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    /* ��g_astTafXcallMsgProcXsmsTab�в��Ҷ�Ӧ����Ϣ������ */
    for (ulIndex = 0; ulIndex < g_ulTafXcallMsgProcCttfTabSize; ulIndex++)
    {
        if (g_astTafXcallMsgProcCttfTab[ulIndex].ulMsgType == pstMsgHeader->ulMsgName)
        {
            /* Msg Id ƥ�� */
            pProcMsgFunc = g_astTafXcallMsgProcCttfTab[ulIndex].pProcMsgFunc;

            break;
        }
    }

    /* ������������������ */
    if ( VOS_NULL_PTR != pProcMsgFunc )
    {
        /* ��Ϣ����ǰ��һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();

        pProcMsgFunc(pstMsg);

        /* ��Ϣ�����һ�º���ʵ����Ϣ */
        TAF_XCALL_MNTN_LogCallInfo();
    }

    return;
}
#endif

#endif

/*lint -restore*/
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




