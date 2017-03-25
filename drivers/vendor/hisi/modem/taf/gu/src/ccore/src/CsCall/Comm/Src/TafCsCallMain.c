/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafCsCallMain.c
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2014��09��03��
  ��������   : TAF CS CALLģ���ʼ������ں�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��09��03��
    ��    ��   : l60609
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafCsCallMain.h"
#include "TafXCallMain.h"
#include "MnCall.h"
#include "TafSdcLib.h"
#include "TafCsCallCtx.h"
#include "MnCallTimer.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_CS_CALL_MAIN_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958*/

/*****************************************************************************
 �� �� ��  : TAF_CSCALL_Init
 ��������  : CS CALLģ���ʼ��
 �������  : TAF_CSCALL_INIT_TYPE_ENUM_UINT8     enInitCtxType
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��11��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CSCALL_Init(
    TAF_CSCALL_INIT_TYPE_ENUM_UINT8     enInitCtxType
)
{
    /* ��ʼ�������� */
    TAF_CSCALL_InitCtx();
}

/*****************************************************************************
 �� �� ��  : TAF_CSCALL_IsNeedXcallProcAppReqMsg
 ��������  : �Ƿ���XCALL��Ҫ�������Ϣ
 �������  : struct MsgCB* pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��6��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_CSCALL_IsNeedXcallProcAppReqMsg(struct MsgCB* pstMsg)
{
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    switch ( pstMsgHeader->ulMsgName )
    {
        case MN_CALL_APP_SET_UUSINFO_REQ:
        case MN_CALL_APP_QRY_UUSINFO_REQ:
        case MN_CALL_APP_SET_ALS_REQ:
        case MN_CALL_APP_QRY_ALS_REQ:
        case MN_CALL_APP_CLPR_GET_REQ:
        case MN_CALL_APP_SET_CSSN_REQ:
        case MN_CALL_QRY_ECALL_INFO_REQ:
        case MN_CALL_APP_END_REQ:
        case MN_CALL_APP_ANSWER_REQ:
        case MN_CALL_APP_START_DTMF_REQ:
        case MN_CALL_APP_STOP_DTMF_REQ:
        case MN_CALL_APP_GET_CDUR_REQ:
        /* ���������붨��AT^NVM�������XCALL�������� */
            return VOS_FALSE;

        default:
            return VOS_TRUE;

    }
}

/*****************************************************************************
 �� �� ��  : TAF_CSCALL_ProcAppReqMsg
 ��������  : CS CALLģ�鴦������Ӧ�ò��������Ϣ
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
VOS_VOID TAF_CSCALL_ProcAppReqMsg(struct MsgCB* pstMsg)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulRslt;

    /* CL������ģʽ */
    ulRslt = TAF_CSCALL_IsNeedXcallProcAppReqMsg(pstMsg);
    if ((VOS_TRUE == TAF_SDC_IsConfigCLMode())
       &&(VOS_TRUE == ulRslt))
    {
        TAF_XCALL_ProcAppReqMsg(pstMsg);

        return;
    }
#endif


    MN_CALL_ProcAppReqMsg(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_CSCALL_ProcVcMsg
 ��������  : CS CALLģ�鴦������VC����Ϣ
 �������  : struct MsgCB* pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��10��
    ��    ��   : y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CSCALL_ProcVcMsg(struct MsgCB* pstMsg)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        TAF_XCALL_ProcVcMsg(pstMsg);

        return;
    }
#endif

    MN_CALL_ProcVCMsg(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_CSCALL_ProcMmaMsg
 ��������  : CS CALLģ�鴦������MMA����Ϣ
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
VOS_VOID TAF_CSCALL_ProcMmaMsg(struct MsgCB* pstMsg)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_XCALL_ProcMmaMsg(pstMsg);
#endif

    TAF_CALL_ProcMmaMsg(pstMsg);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_CSCALL_ProcTimerOutMsg
 ��������  : CS CALLģ�鴦������timer����Ϣ
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
VOS_VOID TAF_CSCALL_ProcTimerOutMsg(
    REL_TIMER_MSG                       *pTmrMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_XCALL_ProcTimerOutMsg(pTmrMsg);
#endif

    /* ����CCA�Ķ�ʱ����Ϣ������ */
    MN_CALL_ProcTimeoutMsg(pTmrMsg);

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_CSCALL_ProcUsimMsg
 ��������  : CS CALLģ�鴦������usim����Ϣ
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
VOS_VOID TAF_CSCALL_ProcUsimMsg(
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_XCALL_ProcUsimMsg(pstMsg);
#endif

    /* ����CCA��USIM��Ϣ������ */
    MN_CALL_DispatchUsimMsg(pstMsg);

    return;
}


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_CSCALL_ProcXsmsMsg
 ��������  : CS CALLģ�鴦������XSMS����Ϣ
 �������  : struct MsgCB* pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��4��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CSCALL_ProcXsmsMsg(
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
    TAF_XCALL_ProcXsmsMsg(pstMsg);
#endif
}



/*****************************************************************************
 �� �� ��  : TAF_CSCALL_ProcCttfMsg
 ��������  : CS CALLģ�鴦������CTTF����Ϣ
 �������  : struct MsgCB* pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��4��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CSCALL_ProcCttfMsg(
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT_TEST_MODE)
    TAF_XCALL_ProcCttfMsg(pstMsg);
#endif
#endif
}
#endif

/*lint -restore*/


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




