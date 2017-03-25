/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafSpmServiceDomainSelProc.h
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2013��7��16��
  ����޸�   :
  ��������   : TafSpmServiceDomainSelProc.h��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��7��16��
    ��    ��   : y00245242
    �޸�����   : �����ļ�

******************************************************************************/
#ifndef _TAF_SPM_SERVICE_DOMAIN_SEL_PROC_H_
#define _TAF_SPM_SERVICE_DOMAIN_SEL_PROC_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "PsTypeDef.h"
/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-10-17, begin */
#include  "MnCallApi.h"
/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-10-17, end */
#include "TafSpmCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define TAF_SPM_IS_PS_VIDEO(CallType, CsVpCfgState, VoiceDomain)    \
           (((MN_CALL_TYPE_VIDEO_TX    == CallType)                 \
          || (MN_CALL_TYPE_VIDEO_RX    == CallType)                 \
          || (MN_CALL_TYPE_VIDEO       == CallType))                \
         && ((TAF_SPM_VP_NONE          == CsVpCfgState)             \
          || (TAF_SPM_VP_MT_ONLY       == CsVpCfgState))            \
         && (TAF_CALL_VOICE_DOMAIN_IMS == VoiceDomain))


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8
 ö��˵��  : ��ѡ��������
 1.��    ��   : 2013��9��24��
   ��    ��   : y00245242
   �޸�����   : �½�
 2.��    ��   : 2014��7��08��
   ��    ��   : w00176964
   �޸�����   : DSDS III�޸�
*****************************************************************************/
enum
{
    TAF_SPM_DOMAIN_SEL_RESULT_NAS_SIGNALLING,   /* result of domain selection: over nas signalling */
    TAF_SPM_DOMAIN_SEL_RESULT_CS_OVER_IP,       /* result of domain selection: over IP */
    TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE,   /* result of domain selection: buffer message */
    TAF_SPM_DOMAIN_SEL_RESULT_SELECT_FAIL,      /* result of domain selection: select fail */

    TAF_SPM_DOMAIN_SEL_RESULT_BUTT
};
typedef VOS_UINT8 TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8;

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-16, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-16, end */

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/


/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : TAF_SPM_ProcReqMsgBasedOnCsOverIp
 ��������  : �������SIP������ص�������Ϣ��ͨ����Ϣ��ת��ѡ���Ӧ����Ϣ����
             ����

 �������  : ulEventType -- ��PID��message name���
             pstMsg      -- ��Ϣ��ַ

 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�Ѿ�����
             VOS_FALSE: ��Ϣδ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcReqMsgBasedOnCsOverIp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvRegisterSsReqBasedOnCsOverIp
 ��������  : ��������AT��STK��register SS������Ϣ
 �������  : pstRcvMsg  ��Ϣָ��

 �������  : ��
 �� �� ֵ  : VOS_TRUE  ��Ϣ�Ѵ���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��23��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvRegisterSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvEraseSsReqBasedOnCsOverIp
 ��������  : ��������AT��STK��SS erase������Ϣ
 �������  : pstRcvMsg  ��Ϣָ��

 �������  : ��
 �� �� ֵ  : VOS_TRUE  ��Ϣ�Ѵ���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��23��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvEraseSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvActivateSsReqBasedOnSipSignallingType
 ��������  : ��������AT��STK��SS activate������Ϣ
 �������  : pstRcvMsg  ��Ϣָ��

 �������  : ��
 �� �� ֵ  : VOS_TRUE  ��Ϣ�Ѵ���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��23��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvActivateSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvDeactivateSsReqBasedOnSipSignallingType
 ��������  : ��������AT��STK��SS deactivate������Ϣ
 �������  : pstRcvMsg  ��Ϣָ��

 �������  : ��
 �� �� ֵ  : VOS_TRUE  ��Ϣ�Ѵ���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��23��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvDeactivateSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvInterrogateSsReqBasedOnCsOverIp
 ��������  : ��������AT��STK��SS interrogate������Ϣ
 �������  : pstRcvMsg  ��Ϣָ��

 �������  : ��
 �� �� ֵ  : VOS_TRUE  ��Ϣ�Ѵ���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��23��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvInterrogateSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvProcUssSsReqBasedOnCsOverIp
 ��������  : ��������AT��STK��SS process Ussd������Ϣ
 �������  : pstRcvMsg  ��Ϣָ��

 �������  : ��
 �� �� ֵ  : VOS_TRUE  ��Ϣ�Ѵ���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��23��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvProcUssSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvRleaseSsReqBasedOnCsOverIp
 ��������  : ��������AT��STK��SS release������Ϣ
 �������  : pstRcvMsg  ��Ϣָ��

 �������  : ��
 �� �� ֵ  : VOS_TRUE  ��Ϣ�Ѵ���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��23��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvRleaseSsReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvAppOrigReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppSupsCmdReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppGetInfoReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppStartDtmfReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppStopDtmfReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppGetCdurReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvStkOrigReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvStkSupsCmdReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvStkStartDtmfReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvStkStopDtmfReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-18, begin */
VOS_UINT32 TAF_SPM_RcvAppGetCallInfoReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvAppGetClprReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcSmsDomainSelection(VOS_VOID);

VOS_UINT32 TAF_SPM_ProcImsaNormalRegStatusNotify(
    struct MsgCB                       *pstMsg
);

/* �����ŵ�IMS������ */

VOS_VOID TAF_SPM_ProcMmaPowerOffInd(VOS_VOID);

/* �����ŵ�IMS������ */

/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-18, end */

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvSendRpdataDirectBasedOnCsOverIp
 ��������  : ��������AT��STK��SMS RP DATA��Ϣ��������Ϣ·������ΪIMS
 �������  : pstRcvMsg  ��Ϣָ��

 �������  : ��
 �� �� ֵ  : VOS_TRUE  ��Ϣ�Ѵ���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��11��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvSendRpdataDirectBasedOnCsOverIp(
    struct MsgCB                       *pstRcvMsg
);

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvSendRpdataFromMemBasedOnCsOverIp
 ��������  : �����memory�з��͵�SMS����Ϣ��������Ϣ·������ΪIMS
 �������  : pstRcvMsg  ��Ϣָ��

 �������  : ��
 �� �� ֵ  : VOS_TRUE  ��Ϣ�Ѵ���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��11��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvSendRpdataFromMemBasedOnCsOverIp(
    struct MsgCB                       *pstRcvMsg
);

/* �Ƶ�IMS���뿪��֮�� */

TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcCcDomainSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcSsDomainSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_VOID TAF_SPM_ProcSmmaIndDomainSelectionResult(
    VOS_UINT32                                              ulEventType,
    struct MsgCB                                           *pstMsg,
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt
);

/* �����ŵ�IMS������ */

VOS_UINT8 TAF_SPM_IsNeedtoWaitImsRegStatus(
    TAF_SPM_SERVICE_STATUS_ENUM_UINT8   enLastPsStatus
);

VOS_UINT32 TAF_SPM_RcvAppCallModifyReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);
VOS_UINT32 TAF_SPM_RcvAppCallAnswerRemoteModifyReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvAppEconfDialReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_RcvAppGetEconfInfoReqBasedOnCsOverIp(
    struct MsgCB                       *pstMsg
);

#endif

TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcServiceRequestDomainSelection(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_ProcInitialDomainSelectionResult
(
    VOS_UINT32                                              ulEventType,
    struct MsgCB                                           *pstMsg,
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt
);

/* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-23, begin */
VOS_UINT32 TAF_SPM_ProcCcSrvReqProtectTimerExpired(VOS_VOID);

VOS_UINT32 TAF_SPM_ProcSsSrvReqProtectTimerExpired(VOS_VOID);

VOS_UINT32 TAF_SPM_ProcSmsSrvReqProtectTimerExpired(
    struct MsgCB                       *pstMsg
);
/* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-23, end */

VOS_VOID TAF_SPM_SendCcServiceRequetFail(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
);
VOS_VOID TAF_SPM_SendSmsServiceRequetFail(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    VOS_UINT32                          ulCause
);
VOS_VOID TAF_SPM_SendSsServiceRequetFail(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_SS_ERROR                        errorCode
);

/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */

/*****************************************************************************
 �� �� ��  : TAF_SPM_ProcReqMsgBasedOnNasSignalling
 ��������  : ��������GUL����͵�APP��������Ϣ
 �������  : ulEventType -- ��PID��message name���
             pstRcvMsg   -- ��Ϣָ��

 �������  : ��
 �� �� ֵ  : VOS_FALSE  ��Ϣδ�������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��31��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/

VOS_UINT32 TAF_SPM_ProcReqMsgBasedOnNasSignalling(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstRcvMsg
);

/* �����ŵ�IMS������ */
VOS_UINT32 TAF_SPM_ProcServiceRequestFail(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_ProcBufferedMsgInQueue(VOS_VOID);

VOS_UINT32 TAF_SPM_BufferAppRequestMessage(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

VOS_UINT32 TAF_SPM_ProcSmsMsgQueue(TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 *pEnDomainSelRslt);

TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcCcDomainSelectionByProtectTimerLen(VOS_VOID);
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcSmsDomainSelectionByProtectTimerLen(VOS_VOID);
TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8 TAF_SPM_ProcSsDomainSelectionByProtectTimerLen(VOS_VOID);

#if (FEATURE_ON == FEATURE_ECALL)
VOS_UINT32 TAF_SPM_IsEcallAllowedSelNasSignalling(
    MN_CALL_TYPE_ENUM_U8                enCallType
);
#endif



#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* _TAF_SPM_IMS_DOMAIN_SEL_PROC_H_ end */

