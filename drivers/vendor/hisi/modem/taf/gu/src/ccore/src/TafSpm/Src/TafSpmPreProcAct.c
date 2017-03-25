/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafSpmPreProcAct.c
  �� �� ��   : ����
  ��    ��   : s00217060
  ��������   : 2013��12��14��
  ����޸�   :
  ��������   :Ԥ����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��12��14��
    ��    ��   : s00217060
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "PsCommonDef.h"
#include "MnCallApi.h"
#include "MnCallReqProc.h"
#include "TafLog.h"
/* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-18, begin */
#include "MnCallSendApp.h"
/* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-18, end */
#include "MnCallMnccProc.h"
#include "TafSpmServiceDomainSelProc.h"
#include "TafMmaCtx.h"
#include "TafSdcLib.h"
#include "TafSpmSndInternalMsg.h"
#include "SpmImsaInterface.h"
#include "TafSpmPreProcTbl.h"
#include "TafSpmPreProcAct.h"
#include "TafAgentInterface.h"
#include "TafSpmComFunc.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "CallImsaInterface.h"
#endif

#include "TafSpmRedial.h"
#include "TafSpmCtx.h"
#include "NasSms.h"
#include "TafSpmMntn.h"
#include "MnMsgApi.h"

#include "MnCall.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_PREPROC_ACT_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-22, begin */
/*****************************************************************************
 �� �� ��  : TAF_SPM_IsCallAllowedInCurrentPhoneMode
 ��������  : ���ݺ��������Լ���ǰ��״̬��ȷ���Ƿ�������ú���
 �������  : pstMsg -- ����������Ϣ��ַ

 �������  : ��
 �� �� ֵ  : VOS_FALSE �� ���в�������
             VOS_TRUE  �� ����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��04��22��
   ��    ��   : y00245242
   �޸�����   : ΪeCall��������
*****************************************************************************/
VOS_UINT32 TAF_SPM_IsCallAllowedInCurrentPhoneMode(MN_CALL_APP_REQ_MSG_STRU *pstMsg)
{
#if (FEATURE_ON == FEATURE_ECALL)
    MN_CALL_TYPE_ENUM_U8                enCallType;
#endif
    TAF_SDC_PHONE_MODE_ENUM_UINT8       enPhMode;

    enPhMode   = TAF_SDC_GetCurPhoneMode();

    if (TAF_PH_MODE_FULL == enPhMode)
    {
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_ECALL)
    /* �����±�ģʽ��MIEC��AIEC��Ҫ�������� */
    if (TAF_PH_MODE_LOWPOWER == enPhMode)
    {
        enCallType = pstMsg->unParm.stOrig.enCallType;

        if ((MN_CALL_TYPE_MIEC == enCallType)
         || (MN_CALL_TYPE_AIEC == enCallType))
        {
            return VOS_TRUE;
        }
    }
#endif

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 �� �� ��  : TAF_SPM_ProcMiecAndAiecReqInLowPower
 ��������  : �ڵ͹���״̬�£�����MIEC��AIEC Ecall���������ڵ͹���ʱ��������Ϣ��
             ����������

 �������  : ulEventType   - �¼�����
             pstMsg        - ��Ϣ��ַ

 �������  :
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��22��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_VOID TAF_SPM_ProcMiecAndAiecReqInLowPower(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRst;
    TAF_MMA_PHONE_MODE_PARA_STRU        stPhoneModePara;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppReq = VOS_NULL_PTR;

    pstAppReq = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    /* ����eCall���󣬲�����������ʱ��TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER */
    ulRst = TAF_SPM_PutMessageToCcQueue(ulEventType, pstMsg);
    if (VOS_TRUE != ulRst)
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_ECALL_CACHE_MSG_FAIL);
        return;
    }

    /* ����API�ӿ�TAF_MMA_PhoneModeSetReq(full mode)���Ϳ�����Ϣ��MMA */
    PS_MEM_SET(&stPhoneModePara, 0x00, sizeof(TAF_MMA_PHONE_MODE_PARA_STRU));
    stPhoneModePara.PhMode  = TAF_PH_MODE_FULL;
    stPhoneModePara.PhReset = TAF_PH_OP_MODE_UNRESET;
    if (VOS_TRUE != TAF_MMA_PhoneModeSetReq(WUEPS_PID_TAF, INTERNAL_CLIENT_ID_SPM, 0, &stPhoneModePara))
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_ECALL_LOWERPOWER_POWER_ON_FAIL);

        /* ��Ϊ������һ����Ϣ������ͷŶ������׸���Ϣ */
        TAF_SPM_FreeSpecificedIndexMessageInCcQueue(0);
        return;
    }

    TAF_SPM_StartTimer(TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER,
                       TI_TAF_SPM_CC_ECALL_REQ_PROTECT_TIMER_VAL,
                       pstAppReq->clientId);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_ProcMiecAndAiecReqInOtherCallRunning
 ��������  : ���к��д��ڳ����£�����MIEC��AIEC Ecall��������
 �������  : ulEventType   - �¼�����
             pstMsg        - ��Ϣ��ַ

 �������  :
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��22��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_VOID TAF_SPM_ProcMiecAndAiecReqInOtherCallRunning(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCachedMsg = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppReq    = VOS_NULL_PTR;

    pstAppReq = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    /* �����������Ϣ��������棬ȷ��eCall���еķ��� */
    if (TAF_SPM_GetCcMsgQueueNum() > 0)
    {
        pstCachedMsg = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(0);

        /* �������ʱ����֪ͨӦ�ã�����ĺ��з���ʧ�� */
        TAF_SPM_SendCcServiceRequetFail(pstCachedMsg->stMsgEntry.ulEventType,
                                        (struct MsgCB *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]),
                                        TAF_CS_CAUSE_DOMAIN_SELECTION_TIMER_EXPIRED);

        TAF_SPM_FreeSpecificedIndexMessageInCcQueue(0);
    }

    /* ���浱ǰeCall������Ϣ */
    (VOS_VOID)TAF_SPM_PutMessageToCcQueue(ulEventType, pstMsg);

    /* ��������ҵ�����󱣻���ʱ���������ʱ��ʱ��������棬֪ͨAPP����ʧ�� */
    TAF_SPM_StartTimer(TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER,
                       TI_TAF_SPM_CC_ECALL_REQ_PROTECT_TIMER_VAL,
                       pstAppReq->clientId);

    /* �ͷ����зǽ������У�ȷ������eCall��������������, �յ�TAF_CALL_TAF_REL_CALL_CNF�󣬷��ͻ����
     * ��������
     */
    TAF_SPM_SndTafRelCallReq(pstAppReq->clientId, pstAppReq->opId, TAF_CALL_REL_CALL_ALL_NORMAL);
}

#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
 �� �� ��  : TAF_SPM_ProcMiecAndAiecReqInImsCallRunning
 ��������  : ����IMS���д��ڳ����£�����MIEC��AIEC Ecall��������
 �������  : ulEventType   - �¼�����
             pstMsg        - ��Ϣ��ַ

 �������  :
 �� �� ֵ  : VOS_VOID

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��04��
    ��    ��   : j00174725
    �޸�����   : DTS2015021000591
*****************************************************************************/
VOS_VOID  TAF_SPM_ProcMiecAndAiecReqInImsCallRunning(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCachedMsg = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppReq    = VOS_NULL_PTR;

    pstAppReq = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    /* �����������Ϣ��������棬ȷ��eCall���еķ��� */
    if (TAF_SPM_GetCcMsgQueueNum() > 0)
    {
        pstCachedMsg = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(0);

        /* �������ʱ����֪ͨӦ�ã�����ĺ��з���ʧ�� */
        TAF_SPM_SendCcServiceRequetFail(pstCachedMsg->stMsgEntry.ulEventType,
                                        (struct MsgCB *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]),
                                        TAF_CS_CAUSE_DOMAIN_SELECTION_TIMER_EXPIRED);

        TAF_SPM_FreeSpecificedIndexMessageInCcQueue(0);
    }

    /* �жϵ�ǰIMS�绰���Ƿ��н����� */
    if (VOS_TRUE == TAF_SPM_IsImsCallTypeEmgencyCall())
    {
        /* ��ǰ�н��������ڣ�ֱ�ӻظ�ʧ�� */
        TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_NOT_ALLOW);
        return;
    }

    /* ���浱ǰeCall������Ϣ */
    (VOS_VOID)TAF_SPM_PutMessageToCcQueue(ulEventType, pstMsg);

    /* ��������ҵ�����󱣻���ʱ���������ʱ��ʱ��������棬֪ͨAPP����ʧ�� */
    TAF_SPM_StartTimer(TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER,
                       TI_TAF_SPM_CC_ECALL_REQ_PROTECT_TIMER_VAL,
                       pstAppReq->clientId);

    /* �ͷ�����IMS�µķǽ������� */
    TAF_SPM_SndImsRelAllCall(pstAppReq->clientId, pstAppReq->opId);

    /* ��¼��� */
    TAF_SPM_SetEcallHangUpImsFlag(VOS_TRUE);

    return;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_SPM_ProcMiecAndAiecReq_PreProc
 ��������  : ����MIEC��AIEC Ecall��������
 �������  : ulEventType   - �¼�����
             pstMsg        - ��Ϣ��ַ

 �������  :
 �� �� ֵ  : VOS_TRUE --  ��Ϣ�������
             VOS_FALSE -- ��Ϣ��Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��22��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcMiecAndAiecReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstAppReq = VOS_NULL_PTR;

    pstAppReq = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    pstAppReq->unParm.stOrig.stEmergencyCat.bExist = VOS_TRUE;

    /* ��дcategory���� */
    if (MN_CALL_TYPE_MIEC == pstAppReq->unParm.stOrig.enCallType)
    {
        pstAppReq->unParm.stOrig.stEmergencyCat.ucEmergencyCat = MN_CALL_EMER_CATEGORG_MAN_INIT_ECALL;
    }
    else
    {
        pstAppReq->unParm.stOrig.stEmergencyCat.ucEmergencyCat = MN_CALL_EMER_CATEGORG_AUTO_INIT_ECALL;
    }

    if (TAF_PH_MODE_LOWPOWER == TAF_SDC_GetCurPhoneMode())
    {
        /* ��������±��ػ�״̬, eCall��������Ҫ�������� */
        TAF_SPM_ProcMiecAndAiecReqInLowPower(ulEventType, pstMsg);

        return VOS_TRUE;
    }

    /* ���δ������IMSҲ�к��д��ڣ��˴�����IMS call�����ͷŴ��� */
    if (VOS_TRUE == TAF_SDC_GetCsCallExistFlg())
    {
        TAF_SPM_ProcMiecAndAiecReqInOtherCallRunning(ulEventType, pstMsg);

        return VOS_TRUE;
    }

#if (FEATURE_IMS == FEATURE_ON)
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        TAF_SPM_ProcMiecAndAiecReqInImsCallRunning(ulEventType, pstMsg);

        return VOS_TRUE;
    }
#endif

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_ProcTestAndRecfgReq_PreProc
 ��������  : ����test��reconfiguration eCall����
 �������  : ulEventType -- �¼�����
             pstMsg -- ����������Ϣ��ַ

 �������  : ��
 �� �� ֵ  : VOS_TRUE --  ��Ϣ�������
             VOS_FALSE -- ��Ϣ��Ҫ��������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��04��22��
   ��    ��   : y00245242
   �޸�����   : ΪeCall��������
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcTestAndRecfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SDC_ECALL_NUM_STRU             *pstEcallNum = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppReq = VOS_NULL_PTR;

    pstAppReq = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    if (0 != pstAppReq->unParm.stOrig.stDialNumber.ucNumLen)
    {
        return VOS_FALSE;
    }

    if (MN_CALL_TYPE_TEST == pstAppReq->unParm.stOrig.enCallType)
    {
        /* ��ȡtest number */
        pstEcallNum = TAF_SDC_GetEcallTestNumber();
    }
    else
    {
        /* ��ȡreconfiguration number */
        pstEcallNum = TAF_SDC_GetEcallRecfgNumber();
    }

    /* ���벻���ڣ��쳣���� */
    if (0 == pstEcallNum->ucLength)
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_CALL_NUMBER_NOT_EXIST);
        return VOS_TRUE;
    }

    if (TAF_SDC_ECALL_BCD_NUM_MAX_LEN < pstEcallNum->ucLength)
    {
        pstAppReq->unParm.stOrig.stDialNumber.ucNumLen = TAF_SDC_ECALL_BCD_NUM_MAX_LEN;
    }
    else
    {
        pstAppReq->unParm.stOrig.stDialNumber.ucNumLen = pstEcallNum->ucLength;
    }

    pstAppReq->unParm.stOrig.stDialNumber.enNumType = pstEcallNum->ucNumType;

    PS_MEM_CPY(&(pstAppReq->unParm.stOrig.stDialNumber.aucBcdNum[0]),
               &(pstEcallNum->aucCallNumber[0]),
               pstAppReq->unParm.stOrig.stDialNumber.ucNumLen);

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_ProcEcallReq_PreProc
 ��������  : ����eCall����
 �������  : ulEventType -- �¼�����
             pstMsg      -- ����������Ϣ��ַ

 �������  : ��
 �� �� ֵ  : VOS_FALSE �� ��Ϣ����δ���
             VOS_TRUE  �� ��Ϣ���������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��04��22��
   ��    ��   : y00245242
   �޸�����   : ΪeCall��������
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcEcallReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstAppReq = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    pstAppReq = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    switch (pstAppReq->unParm.stOrig.enCallType)
    {
        case MN_CALL_TYPE_MIEC:
        case MN_CALL_TYPE_AIEC:
            ulRst = TAF_SPM_ProcMiecAndAiecReq_PreProc(ulEventType, pstMsg);
            break;

        case MN_CALL_TYPE_TEST:
        case MN_CALL_TYPE_RECFGURATION:
            ulRst = TAF_SPM_ProcTestAndRecfgReq_PreProc(ulEventType, pstMsg);
            break;

        default:
            ulRst = VOS_FALSE;
            break;
    }

    return ulRst;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_IsEcallAllowedInCurrentSysMode
 ��������  : ���ݵ�ǰϵͳģʽ������eCall�����Ƿ�����
 �������  : enCallType -- ��������

 �������  : ��
 �� �� ֵ  : VOS_FALSE �� ���в�������
             VOS_TRUE  �� ����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��04��22��
   ��    ��   : y00245242
   �޸�����   : ΪeCall��������
*****************************************************************************/
VOS_UINT32 TAF_SPM_IsEcallAllowedInCurrentSysMode(
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    TAF_SDC_RAT_PRIO_STRU              *pstRatPrio = VOS_NULL_PTR;

    pstRatPrio = TAF_SDC_GetMsPrioRatList();

    if ((VOS_TRUE          == TAF_SDC_IsLteOnlyMode(pstRatPrio))
     && ((MN_CALL_TYPE_MIEC         == enCallType)
      || (MN_CALL_TYPE_AIEC         == enCallType)
      || (MN_CALL_TYPE_TEST         == enCallType)
      || (MN_CALL_TYPE_RECFGURATION == enCallType)))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_IsEcallAllowedInCurrentCallMode
 ��������  : ���ݺ���ģʽ���Ƿ�������eall
 �������  : enCallType -- ��������

 �������  : ��
 �� �� ֵ  : VOS_FALSE �� ���в�������
             VOS_TRUE  �� ����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��03��02��
   ��    ��   : j00174725
   �޸�����   :
*****************************************************************************/
VOS_UINT32 TAF_SPM_IsEcallAllowedInCurrentCallMode(
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    TAF_SDC_CALL_MODE_ENUM_UINT8        enEcallMode;

    enEcallMode = TAF_SDC_GetCurCallMode();

    if ((TAF_SDC_CALL_MODE_BUTT     == enEcallMode)
     && ((MN_CALL_TYPE_MIEC         == enCallType)
      || (MN_CALL_TYPE_AIEC         == enCallType)
      || (MN_CALL_TYPE_TEST         == enCallType)
      || (MN_CALL_TYPE_RECFGURATION == enCallType)))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#endif
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-22, end */

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvAppOrigReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT�ĺ����������Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��14��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��04��22��
   ��    ��   : y00245242
   �޸�����   : ΪeCall�����޸�
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppOrigReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg     = VOS_NULL_PTR;
    MN_CALL_EMERGENCY_CAT_STRU          stEmergencyCat;

    pstAppMsg                 = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    PS_MEM_SET(&stEmergencyCat, 0, sizeof(MN_CALL_EMERGENCY_CAT_STRU));

    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-22, begin */
    /* call is allowed if phone mode is power on */
    if (VOS_TRUE != TAF_SPM_IsCallAllowedInCurrentPhoneMode(pstAppMsg))
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-22, end */
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_POWER_OFF);

        return VOS_TRUE;
    }

    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-22, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_FALSE == TAF_SPM_IsEcallAllowedInCurrentSysMode(pstAppMsg->unParm.stOrig.enCallType))
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_NOT_ALLOW);

        return VOS_TRUE;
    }

    if (VOS_FALSE == TAF_SPM_IsEcallAllowedInCurrentCallMode(pstAppMsg->unParm.stOrig.enCallType))
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_NOT_ALLOW);

        return VOS_TRUE;
    }

    if (VOS_TRUE == TAF_SPM_ProcEcallReq_PreProc(ulEventType, pstMsg))
    {
        /* ��Ϣ������ϣ����� */
        return VOS_TRUE;
    }

    /* �����ecal������������Ҫ������һ����� */
    if ((MN_CALL_TYPE_MIEC == pstAppMsg->unParm.stOrig.enCallType)
     || (MN_CALL_TYPE_AIEC == pstAppMsg->unParm.stOrig.enCallType))
    {
        return VOS_FALSE;
    }
#endif
    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-22, end */

    /* VIDEO call������ͨ���д������������к����� */
    if ((MN_CALL_TYPE_VIDEO    != pstAppMsg->unParm.stOrig.enCallType)
     && (MN_CALL_TYPE_VIDEO_RX != pstAppMsg->unParm.stOrig.enCallType)
     && (MN_CALL_TYPE_VIDEO_TX != pstAppMsg->unParm.stOrig.enCallType))
    {
        /* �ж��ǽ��������½������е�CAT��Ϣ */
        if (VOS_TRUE  == TAF_SPM_IsEmergencyNum(&pstAppMsg->unParm.stOrig.stDialNumber,
                                                VOS_TRUE,
                                                &stEmergencyCat))
        {
            pstAppMsg->unParm.stOrig.enCallType  = MN_CALL_TYPE_EMERGENCY;

            PS_MEM_CPY(&(pstAppMsg->unParm.stOrig.stEmergencyCat),
                        &stEmergencyCat,
                        sizeof(MN_CALL_EMERGENCY_CAT_STRU));

            return VOS_FALSE;
        }
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* CDMA inside�����ҵ�ǰ��CLģʽ */
    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        /* �������Ч���ܾ���ͨ�� */
        if (VOS_FALSE == TAF_SPM_IsCsimServiceAvailable())
        {
            TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_SIM_NOT_EXIST);
            return VOS_TRUE;
        }
    }
    else
#endif
    {
        /* forbid normal call when USIM service is not available */
        if (VOS_FALSE == TAF_SPM_IsUsimServiceAvailable())
        {
            TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_SIM_NOT_EXIST);
            return VOS_TRUE;
        }

        /* ��Ҫ�ж���������Ч,��Ϊ������Ч������ܻ�disable LTE��GU��,��Ҫ��GU�¼������� */
        if (VOS_FALSE == TAF_SDC_IsUsimStausValid())
        {
            TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_SIM_INVALID);
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvAppSupsCmdReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��MN_CALL_APP_SUPS_CMD_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��14��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppSupsCmdReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
#if (FEATURE_ON == FEATURE_IMS)
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg = VOS_NULL_PTR;
#endif

    ulRet           = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* ����Ѿ�IMS����д��ڣ�ֱ��ѡ��IMS�������������VOS_FALSE����CALLģ�鴦�� */
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
    }
    else
    {
        /* �ó����������SRVCC���л��ɹ��������ʱ�û�����Ҷ���Ӧ��callʱ����Ҫ
         * ����ز������б����call������Ϣ��������GU���ַ����ز�
         */
        pstAppMsg = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

        /* �û��һ�������ж�Ӧ���ز�������ڣ������ */
        switch (pstAppMsg->unParm.stCallMgmtCmd.enCallSupsCmd)
        {
            case MN_CALL_SUPS_CMD_REL_CALL_X:
                TAF_SPM_FreeCallRedialBufferWithCallId(pstAppMsg->callId);
                break;

            case MN_CALL_SUPS_CMD_REL_ALL_CALL:
            case MN_CALL_SUPS_CMD_REL_ALL_EXCEPT_WAITING_CALL:
                TAF_SPM_FreeCallRedialBufferWithClientId(pstAppMsg->clientId);
                break;

            default:
                break;
        }
    }
#endif

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvAppGetInfoReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��MN_CALL_APP_GET_INFO_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��14��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppGetInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulRet;
    ulRet           = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* ����Ѿ�IMS����д��ڣ�ֱ��ѡ��IMS�������������VOS_FALSE����CALLģ�鴦�� */
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
    }
#endif

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvAppStartDtmfReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��MN_CALL_APP_START_DTMF_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��14��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppStartDtmfReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulRet;
    ulRet           = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* ����Ѿ�IMS����д��ڣ�ֱ��ѡ��IMS�������������VOS_FALSE����CALLģ�鴦�� */
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
    }
#endif

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvAppStopDtmfReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��MN_CALL_APP_STOP_DTMF_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��14��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppStopDtmfReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulRet;
    ulRet           = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* ����Ѿ�IMS����д��ڣ�ֱ��ѡ��IMS�������������VOS_FALSE����CALLģ�鴦�� */
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
    }
#endif

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvAppGetCdurReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��MN_CALL_APP_GET_CDUR_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��14��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppGetCdurReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulRet;
    ulRet           = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* ����Ѿ�IMS����д��ڣ�ֱ��ѡ��IMS�������������VOS_FALSE����CALLģ�鴦�� */
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
    }
#endif

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvAppGetCallInfoReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�TAFAGENT��ID_TAFAGENT_MN_GET_CALL_INFO_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��14��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppGetCallInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulRet;
    ulRet           = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* ����Ѿ�IMS����д��ڣ�ֱ��ѡ��IMS�������������VOS_FALSE����CALLģ�鴦�� */
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
    }
#endif

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvAppGetClprReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��MN_CALL_APP_CLPR_GET_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��14��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppGetClprReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                                              ulRet;
    ulRet           = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* ����Ѿ�IMS����д��ڣ�ֱ��ѡ��IMS�������������VOS_FALSE����CALLģ�鴦�� */
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
    }
#endif

    return ulRet;
}

#if (FEATURE_ON == FEATURE_ECALL)
/* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-1, begin */
/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvMmaPhoneModeSetCnf_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�MMA��ID_TAF_MMA_PHONE_MODE_SET_CNF��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��1��
   ��    ��   : s00261364
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvMmaPhoneModeSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstMsgInfo = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg  = VOS_NULL_PTR;
    TAF_MMA_PHONE_MODE_SET_CNF_STRU    *pstCnfMsg  = VOS_NULL_PTR;

    pstMsgInfo      = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(0);
    pstAppMsg       = (MN_CALL_APP_REQ_MSG_STRU *)&(pstMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]);
    pstCnfMsg       = (TAF_MMA_PHONE_MODE_SET_CNF_STRU *)pstMsg;

    /* ���client id */
    if (INTERNAL_CLIENT_ID_SPM != pstCnfMsg->usClientId)
    {
        return VOS_TRUE;
    }

    /* �������Ϊ�գ����涨ʱ���Ѿ���ʱ���˳���Ϣ���� */
    if (0 == TAF_SPM_GetCcMsgQueueNum())
    {
        return VOS_TRUE;
    }

    /* 1. ��黺����Ϣ�����Ƿ���ecall���У�������ǣ��򷵻�
     * 2. ����Ƿ��ǿ�����Ӧ��Ϣ����ucPhMode�Ƿ���TAF_PH_MODE_FULL��������ǣ��򷵻�
     */
    if (((MN_CALL_TYPE_MIEC != pstAppMsg->unParm.stOrig.enCallType)
      && (MN_CALL_TYPE_AIEC != pstAppMsg->unParm.stOrig.enCallType))
     || (TAF_PH_MODE_FULL  != pstCnfMsg->ucPhMode))
    {
        return VOS_TRUE;
    }

    /* ֹͣ������ʱ��TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER */
    TAF_SPM_StopTimer(TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER, pstAppMsg->clientId);

    /* ����ʧ�ܣ�֪ͨAT eCall����ʧ��  */
    if ( TAF_MMA_APP_OPER_RESULT_SUCCESS != pstCnfMsg->enRslt )
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType,
                                        (struct MsgCB *)pstAppMsg,
                                        TAF_CS_CAUSE_ECALL_LOWERPOWER_POWER_ON_FAIL);

        /* ������� */
        TAF_SPM_FreeSpecificedIndexMessageInCcQueue(0);

        return VOS_TRUE;
    }

    /* �����Ϊ�ɹ����ø��������Ϣ��ǲ������޸ĺ�������Ϣ��ȫ�ֱ����� */
    TAF_SPM_UpdateServiceCtrlEntryMsg(pstMsgInfo->stMsgEntry.ulEventType, (struct MsgCB *)pstAppMsg);

    TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

    /* ������� */
    TAF_SPM_FreeSpecificedIndexMessageInCcQueue(0);

    return VOS_FALSE;
}
/* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-1, end */

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-26, begin */
/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvTafRelCallCnf_PreProc
 ��������  : �����ڲ�normal�����ͷ�ȷ����Ϣ

 �������  : pstMsg      -- ����������Ϣ��ַ
             ulEventType �� �¼�����

 �������  : ��
 �� �� ֵ  : VOS_FALSE �� ����δ�������
             VOS_TRUE  �� ���д������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��04��22��
   ��    ��   : y00245242
   �޸�����   : ΪeCall��������
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvTafRelCallCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CALL_TAF_REL_CALL_CNF_STRU     *pstCnfMsg  = VOS_NULL_PTR;
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstMsgInfo = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulRst;

    /* �������Ϊ�գ����涨ʱ���Ѿ���ʱ���˳���Ϣ���� */
    if (0 == TAF_SPM_GetCcMsgQueueNum())
    {
        return VOS_TRUE;
    }

    pstMsgInfo      = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(0);
    pstAppMsg       = (MN_CALL_APP_REQ_MSG_STRU *)&(pstMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]);

    /* ֹͣ������ʱ��TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER */
    TAF_SPM_StopTimer(TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER, pstAppMsg->clientId);

    pstCnfMsg = (TAF_CALL_TAF_REL_CALL_CNF_STRU *)pstMsg;
    if (TAF_CS_CAUSE_SUCCESS == pstCnfMsg->enCause)
    {
        /* �����Ϊ�ɹ����ø��������Ϣ��ǲ������޸ĺ�������Ϣ��ȫ�ֱ����� */
        TAF_SPM_UpdateServiceCtrlEntryMsg(pstMsgInfo->stMsgEntry.ulEventType, (struct MsgCB *)pstAppMsg);

        TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

        ulRst = VOS_FALSE;
    }
    else
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType,
                                        (struct MsgCB *)pstAppMsg,
                                        pstCnfMsg->enCause);
        ulRst = VOS_TRUE;
    }

    /* ������� */
    TAF_SPM_FreeSpecificedIndexMessageInCcQueue(0);

    return ulRst;
}
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-26, end */

/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, begin */
/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvPbECallInitInd_PreProc
 ��������  : �յ�PB��ʼ�����ָʾ
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��23��
    ��    ��   : w00176964
    �޸�����   : eCall��Ŀ����
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvPbECallInitInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucFdnRecordNum;
    VOS_UINT8                           ucSdnRecordNum;
    SI_PB_ECALLINIT_IND_STRU           *pstECallInitInd = VOS_NULL_PTR;

    pstECallInitInd = (SI_PB_ECALLINIT_IND_STRU *)pstMsg;

    ucFdnRecordNum = (VOS_UINT8)pstECallInitInd->usFdnRecordNum;
    ucSdnRecordNum = (VOS_UINT8)pstECallInitInd->usSdnRecordNum;;

    /* ���ecall number */
    TAF_SDC_InitECallNumber(TAF_SDC_GetEcallRecfgNumber());
    TAF_SDC_InitECallNumber(TAF_SDC_GetEcallTestNumber());

    TAF_SPM_ReadEcallNumber(ucFdnRecordNum, ucSdnRecordNum);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_SPM_ProcPbQryFdnECallNumCnf_PreProc
 ��������  : �յ�PBģ���ȡFDN��ecall��غ���Ĵ���
 �������  : pstPbMsg-----PB�Ĳ�ѯ��Ϣ

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��26��
    ��    ��   : w00176964
    �޸�����   : eCall��Ŀ����
*****************************************************************************/
VOS_VOID TAF_SPM_ProcPbQryFdnECallNumCnf_PreProc(
    SI_PB_ECALLQRY_CNF_STRU            *pstPbMsg
)
{
    TAF_SDC_ECALL_NUM_STRU             *pstTestNum  = VOS_NULL_PTR;
    TAF_SDC_ECALL_NUM_STRU             *pstRecfgNum = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;

    pstTestNum  = TAF_SDC_GetEcallTestNumber();
    pstRecfgNum = TAF_SDC_GetEcallRecfgNumber();

    for (ucIndex = 0; ucIndex < (VOS_UINT8)pstPbMsg->ulRecordNum; ucIndex++)
    {
        /* ��һ������Ϊtest number */
        if ((TAF_SPM_USIM_FILE_FIRST_RECORD == pstPbMsg->astECallNumber[ucIndex].ucIndex)
         && (0                              < pstPbMsg->astECallNumber[ucIndex].ucLength))
        {
            pstTestNum->ucNumType = pstPbMsg->astECallNumber[ucIndex].ucTon;

            if (PB_NUMBER_TYPE_INTERNATIONAL != pstTestNum->ucNumType)
            {
                pstTestNum->ucNumType = PB_NUMBER_TYPE_NORMAL;
            }

            pstTestNum->ucLength  = pstPbMsg->astECallNumber[ucIndex].ucLength;

            if (TAF_SDC_ECALL_BCD_NUM_MAX_LEN < pstTestNum->ucLength)
            {
                pstTestNum->ucLength = TAF_SDC_ECALL_BCD_NUM_MAX_LEN;
            }

            PS_MEM_CPY(pstTestNum->aucCallNumber, pstPbMsg->astECallNumber[ucIndex].aucCallNumber, pstTestNum->ucLength);
        }

        /* �ڶ�������Ϊrecfg number */
        if ((TAF_SPM_USIM_FILE_SECOND_RECORD == pstPbMsg->astECallNumber[ucIndex].ucIndex)
         && (0                               < pstPbMsg->astECallNumber[ucIndex].ucLength))
        {
            pstRecfgNum->ucNumType = pstPbMsg->astECallNumber[ucIndex].ucTon;

            if (PB_NUMBER_TYPE_INTERNATIONAL != pstRecfgNum->ucNumType)
            {
                pstRecfgNum->ucNumType = PB_NUMBER_TYPE_NORMAL;
            }

            pstRecfgNum->ucLength  = pstPbMsg->astECallNumber[ucIndex].ucLength;

            if (TAF_SDC_ECALL_BCD_NUM_MAX_LEN < pstRecfgNum->ucLength)
            {
                pstRecfgNum->ucLength = TAF_SDC_ECALL_BCD_NUM_MAX_LEN;
            }

            PS_MEM_CPY(pstRecfgNum->aucCallNumber, pstPbMsg->astECallNumber[ucIndex].aucCallNumber, pstRecfgNum->ucLength);

            break;
        }
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_SPM_ProcPbQrySdnECallNumCnf_PreProc
 ��������  : �յ�PBģ���ȡSDN��ecall��غ���Ĵ���
 �������  : pstPbMsg-----PB�Ĳ�ѯ��Ϣ

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��26��
    ��    ��   : w00176964
    �޸�����   : eCall��Ŀ����
*****************************************************************************/
VOS_VOID TAF_SPM_ProcPbQrySdnECallNumCnf_PreProc(
    SI_PB_ECALLQRY_CNF_STRU            *pstPbMsg
)
{
    TAF_SDC_ECALL_NUM_STRU             *pstTestNum  = VOS_NULL_PTR;
    TAF_SDC_ECALL_NUM_STRU             *pstRecfgNum = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucTmpIndex;

    pstTestNum  = TAF_SDC_GetEcallTestNumber();
    pstRecfgNum = TAF_SDC_GetEcallRecfgNumber();

    for (ucIndex = (VOS_UINT8)pstPbMsg->ulRecordNum; ucIndex > 0; ucIndex--)
    {
        ucTmpIndex = (VOS_UINT8)pstPbMsg->ulRecordNum;

        /* ���������Ϊrecfg number */
        if ((ucTmpIndex == pstPbMsg->astECallNumber[ucIndex].ucIndex)
         && (0          < pstPbMsg->astECallNumber[ucIndex].ucLength))
        {
            pstRecfgNum->ucNumType = pstPbMsg->astECallNumber[ucIndex].ucTon;

            if (PB_NUMBER_TYPE_INTERNATIONAL != pstRecfgNum->ucNumType)
            {
                pstRecfgNum->ucNumType = PB_NUMBER_TYPE_NORMAL;
            }

            pstRecfgNum->ucLength  = pstPbMsg->astECallNumber[ucIndex].ucLength;

            if (TAF_SDC_ECALL_BCD_NUM_MAX_LEN < pstRecfgNum->ucLength)
            {
                pstRecfgNum->ucLength = TAF_SDC_ECALL_BCD_NUM_MAX_LEN;
            }

            PS_MEM_CPY(pstRecfgNum->aucCallNumber, pstPbMsg->astECallNumber[ucIndex].aucCallNumber, pstRecfgNum->ucLength);
        }

        /* �����ڶ�������Ϊtest number */
        ucTmpIndex = (VOS_UINT8)pstPbMsg->ulRecordNum - 1;

        if ((ucTmpIndex == pstPbMsg->astECallNumber[ucIndex].ucIndex)
         && (0          < pstPbMsg->astECallNumber[ucIndex].ucLength))
        {
            pstTestNum->ucNumType = pstPbMsg->astECallNumber[ucIndex].ucTon;

            if (PB_NUMBER_TYPE_INTERNATIONAL != pstTestNum->ucNumType)
            {
                pstTestNum->ucNumType = PB_NUMBER_TYPE_NORMAL;
            }

            pstTestNum->ucLength  = pstPbMsg->astECallNumber[ucIndex].ucLength;

            if (TAF_SDC_ECALL_BCD_NUM_MAX_LEN < pstTestNum->ucLength)
            {
                pstTestNum->ucLength = TAF_SDC_ECALL_BCD_NUM_MAX_LEN;
            }

            PS_MEM_CPY(pstTestNum->aucCallNumber, pstPbMsg->astECallNumber[ucIndex].aucCallNumber, pstTestNum->ucLength);

            break;
        }
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvPbQryECallNumCnf_PreProc
 ��������  : �յ�PBģ���ȡecall��غ���Ĵ���
 �������  : ulEventType
             pstMsg

 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��23��
    ��    ��   : w00176964
    �޸�����   : eCall��Ŀ����
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvPbQryECallNumCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SI_PB_ECALLQRY_CNF_STRU            *pstPbMsg    = VOS_NULL_PTR;

    pstPbMsg = (SI_PB_ECALLQRY_CNF_STRU *)pstMsg;

    if (VOS_OK != pstPbMsg->ulRslt)
    {
        return VOS_TRUE;
    }
    if (SI_PB_STORAGE_FD == pstPbMsg->enStorage)
    {
        TAF_SPM_ProcPbQryFdnECallNumCnf_PreProc(pstPbMsg);

        return VOS_TRUE;
    }
    if (SI_PB_STORAGE_SD == pstPbMsg->enStorage)
    {
        TAF_SPM_ProcPbQrySdnECallNumCnf_PreProc(pstPbMsg);
    }

    return VOS_TRUE;
}

/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-5-4, end */


#endif





/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvAppSendRpdataDirect_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��MN_MSG_MSGTYPE_SEND_RPDATA_DIRECT��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��14��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppSendRpdataDirect_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulCause;

    /* ��鵱ǰ��״̬�����ػ�״̬�Ƿ�������SMSҵ�� */
    if (VOS_FALSE == TAF_SPM_IsSmsServiceReqAllowed_PreProc(ulEventType, pstMsg, &ulCause))
    {
        /* �����������SMSҵ�񣬸�AT�ظ�ʧ�ܣ�����Ӧ��ԭ��ֵ */
        TAF_SPM_SendSmsServiceRequetFail(ulEventType, pstMsg, ulCause);

        return VOS_TRUE;
    }

    /* ������SMSҵ��ʱ��Ҫ����FDN&CALL CONTROL��� */
    return VOS_FALSE;

}



/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvProcUssSsReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��TAF_MSG_PROCESS_USS_MSG��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��14��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvProcUssSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MN_APP_REQ_MSG_STRU                *pstRcvMsg   = VOS_NULL_PTR;
    TAF_SS_PROCESS_USS_REQ_STRU        *pstSsReqMsg = VOS_NULL_PTR;
    TAF_ERROR_CODE_ENUM_UINT32          enCause;

    pstRcvMsg   = (MN_APP_REQ_MSG_STRU *)pstMsg;
    pstSsReqMsg = (TAF_SS_PROCESS_USS_REQ_STRU *)&(pstRcvMsg->aucContent[0]);

    /* configure CUSD setting */
    if (TAF_SS_CUSD_TYPE_ENABLE == pstSsReqMsg->enCusdType)
    {
        TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUSD, VOS_TRUE);
    }
    else
    {
        TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUSD, VOS_FALSE);
    }

    /* check whether or not USSD string exists */
    if (0 == pstSsReqMsg->UssdStr.usCnt)
    {
        /* ���ֻ��CUSD�Ƿ������ϱ�������AT���Ѿ��ͷţ�����Ҫ�ȴ�C�˻ظ� */
        return VOS_TRUE;
    }

    /* ��鵱ǰ��״̬�����ػ�״̬�Ƿ�������SSҵ�� */
    if (VOS_FALSE == TAF_SPM_IsSsServiceReqAllowed_PreProc(ulEventType, pstMsg, &enCause))
    {
        /* �����������SSҵ�񣬸�AT�ظ�ʧ�ܣ�����Ӧ��ԭ��ֵ */
        TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, (TAF_SS_ERROR)enCause);

        return VOS_TRUE;
    }

    /* ������SSҵ��ʱ��Ҫ����FDN&CALL CONTROL��� */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvRegisterSsReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��TAF_MSG_REGISTERSS_MSG��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��14��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvRegisterSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_ERROR_CODE_ENUM_UINT32          enCause;

    /* ��鵱ǰ��״̬�����ػ�״̬�Ƿ�������SSҵ�� */
    if (VOS_FALSE == TAF_SPM_IsSsServiceReqAllowed_PreProc(ulEventType, pstMsg, &enCause))
    {
        /* �����������SSҵ�񣬸�AT�ظ�ʧ�ܣ�����Ӧ��ԭ��ֵ */
        TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, (TAF_SS_ERROR)enCause);

        return VOS_TRUE;
    }

    /* ������SSҵ��ʱ��Ҫ����FDN&CALL CONTROL��� */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvEraseSsReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��TAF_MSG_ERASESS_MSG��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��14��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvEraseSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_ERROR_CODE_ENUM_UINT32          enCause;

    /* ��鵱ǰ��״̬�����ػ�״̬�Ƿ�������SSҵ�� */
    if (VOS_FALSE == TAF_SPM_IsSsServiceReqAllowed_PreProc(ulEventType, pstMsg, &enCause))
    {
        /* �����������SSҵ�񣬸�AT�ظ�ʧ�ܣ�����Ӧ��ԭ��ֵ */
        TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, (TAF_SS_ERROR)enCause);

        return VOS_TRUE;
    }

    /* ������SSҵ��ʱ��Ҫ����FDN&CALL CONTROL��� */
    return VOS_FALSE;
}




/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvActivateSsReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��TAF_MSG_ACTIVATESS_MSG��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��14��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvActivateSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_ERROR_CODE_ENUM_UINT32          enCause;

    /* ��鵱ǰ��״̬�����ػ�״̬�Ƿ�������SSҵ�� */
    if (VOS_FALSE == TAF_SPM_IsSsServiceReqAllowed_PreProc(ulEventType, pstMsg, &enCause))
    {
        /* �����������SSҵ�񣬸�AT�ظ�ʧ�ܣ�����Ӧ��ԭ��ֵ */
        TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, (TAF_SS_ERROR)enCause);

        return VOS_TRUE;
    }

    /* ������SSҵ��ʱ��Ҫ����FDN&CALL CONTROL��� */
    return VOS_FALSE;
}



/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvDeactivateSsReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��TAF_MSG_DEACTIVATESS_MSG��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��14��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvDeactivateSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_ERROR_CODE_ENUM_UINT32          enCause;

    /* ��鵱ǰ��״̬�����ػ�״̬�Ƿ�������SSҵ�� */
    if (VOS_FALSE == TAF_SPM_IsSsServiceReqAllowed_PreProc(ulEventType, pstMsg, &enCause))
    {
        /* �����������SSҵ�񣬸�AT�ظ�ʧ�ܣ�����Ӧ��ԭ��ֵ */
        TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, (TAF_SS_ERROR)enCause);

        return VOS_TRUE;
    }

    /* ������SSҵ��ʱ��Ҫ����FDN&CALL CONTROL��� */
    return VOS_FALSE;
}



/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvInterrogateSsReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��TAF_MSG_INTERROGATESS_MSG��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��14��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvInterrogateSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_ERROR_CODE_ENUM_UINT32          enCause;

    /* ��鵱ǰ��״̬�����ػ�״̬�Ƿ�������SSҵ�� */
    if (VOS_FALSE == TAF_SPM_IsSsServiceReqAllowed_PreProc(ulEventType, pstMsg, &enCause))
    {
        /* �����������SSҵ�񣬸�AT�ظ�ʧ�ܣ�����Ӧ��ԭ��ֵ */
        TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, (TAF_SS_ERROR)enCause);

        return VOS_TRUE;
    }

    /* ������SSҵ��ʱ��Ҫ����FDN&CALL CONTROL��� */
    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvRegPwdSsReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��TAF_MSG_REGPWD_MSG��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��01��07��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvRegPwdSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_ERROR_CODE_ENUM_UINT32          enCause;

    /* ��鵱ǰ��״̬�����ػ�״̬�Ƿ�������SSҵ�� */
    if (VOS_FALSE == TAF_SPM_IsSsServiceReqAllowed_PreProc(ulEventType, pstMsg, &enCause))
    {
        /* �����������SSҵ�񣬸�AT�ظ�ʧ�ܣ�����Ӧ��ԭ��ֵ */
        TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, (TAF_SS_ERROR)enCause);

        return VOS_TRUE;
    }

    /* ������SSҵ��ʱ��Ҫ����FDN&CALL CONTROL��� */
    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvEraseCCentrySsReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��TAF_MSG_ERASECCENTRY_MSG��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��01��07��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvEraseCCentrySsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_ERROR_CODE_ENUM_UINT32          enCause;

    /* ��鵱ǰ��״̬�����ػ�״̬�Ƿ�������SSҵ�� */
    if (VOS_FALSE == TAF_SPM_IsSsServiceReqAllowed_PreProc(ulEventType, pstMsg, &enCause))
    {
        /* �����������SSҵ�񣬸�AT�ظ�ʧ�ܣ�����Ӧ��ԭ��ֵ */
        TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, (TAF_SS_ERROR)enCause);

        return VOS_TRUE;
    }

    /* ������SSҵ��ʱ��Ҫ����FDN&CALL CONTROL��� */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvRleaseSsReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��TAF_MSG_RLEASE_MSG��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��14��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvRleaseSsReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;

    ulRet               = VOS_FALSE;

#if (FEATURE_ON == FEATURE_IMS)
    /* ����Ѿ�IMS��USSDҵ����ڣ�ֱ��ѡ��IMS�������������VOS_FALSE����NAS�������̴��� */
    if (VOS_TRUE == TAF_SDC_GetImsSsSrvExistFlg())
    {
        ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
    }
#endif

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvStkOrigReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�STK�ĺ����������Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��14��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvStkOrigReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    MN_CALL_EMERGENCY_CAT_STRU          stEmergencyCat;
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT32                          ulExistBc;
    MN_APP_CALL_CALLORIG_REQ_STRU      *pstOrigParam = VOS_NULL_PTR;

    pstOrigParam = (MN_APP_CALL_CALLORIG_REQ_STRU *)pstMsg;

    PS_MEM_SET(&stEmergencyCat, 0, sizeof(MN_CALL_EMERGENCY_CAT_STRU));
    enCallType  = MN_CALL_TYPE_VOICE;
    ulExistBc   = VOS_TRUE;

    /* call is allowed if phone mode is power on */
    if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_POWER_OFF);
        return VOS_TRUE;
    }

    if (0 == pstOrigParam->stBc.ucLen)
    {
        ulExistBc    = VOS_FALSE;
    }

    /* ����BC������ȡ�������� */
    ulRet = TAF_SPM_GetBcCallType(ulExistBc,
                                  pstOrigParam->stBc.ucLen,
                                  pstOrigParam->stBc.aucBc,
                                  &enCallType);
    if (VOS_TRUE != ulRet)
    {
        MN_WARN_LOG("MN_CALL_StkCallOrigReqProc: Fail to TAF_SPM_GetBcCallType.");

        TAF_CALL_SendCallOrigCnf(pstOrigParam->usClientId,
                                 pstOrigParam->opID,
                                 pstOrigParam->callID,
                                 TAF_CS_CAUSE_CALL_CTRL_BEYOND_CAPABILITY);

#if (FEATURE_ON == FEATURE_PTM)
        /* ��¼CS�����쳣log */
        MN_CALL_CsCallErrRecord(pstOrigParam->callID, TAF_CS_CAUSE_CALL_CTRL_BEYOND_CAPABILITY);
#endif

        return VOS_TRUE;
    }

    /* VIDEO call������ͨ���д������������к����� */
    pstOrigParam->enCallType = enCallType;
    if ((MN_CALL_TYPE_VIDEO    != pstOrigParam->enCallType)
     && (MN_CALL_TYPE_VIDEO_RX != pstOrigParam->enCallType)
     && (MN_CALL_TYPE_VIDEO_TX != pstOrigParam->enCallType))
    {
        /* �ж��ǽ��������½������е�CAT��Ϣ */
        if (VOS_TRUE  == TAF_SPM_IsEmergencyNum((MN_CALL_CALLED_NUM_STRU *)&pstOrigParam->stCalledAddr,
                                                  VOS_FALSE,
                                                  &stEmergencyCat))
        {
            pstOrigParam->enCallType        = MN_CALL_TYPE_EMERGENCY;

            PS_MEM_CPY(&(pstOrigParam->stEmergencyCat),
                        &stEmergencyCat,
                        sizeof(MN_CALL_EMERGENCY_CAT_STRU));

            return VOS_FALSE;
        }
        else
        {
            PS_MEM_SET(&(pstOrigParam->stEmergencyCat),
                       0,
                       sizeof(MN_CALL_EMERGENCY_CAT_STRU));

        }
    }

    /* forbid normal call when USIM service is not available */
    if (VOS_FALSE == TAF_SPM_IsUsimServiceAvailable())
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_SIM_NOT_EXIST);
        return VOS_TRUE;
    }

    /* ��Ҫ�ж���������Ч,��Ϊ������Ч������ܻ�disable LTE��GU��,��Ҫ��GU�¼������� */
    if (VOS_FALSE == TAF_SDC_IsUsimStausValid())
    {
        TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, TAF_CS_CAUSE_SIM_INVALID);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvMsgSmmaInd_PreProc
 ��������  : MAIN״̬����ʼ��״̬�յ�ID_TAF_SPM_SMMA_IND����Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��9��24��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��12��31��
   ��    ��   : y00245242
   �޸�����   : ����IMS-->CS�����ز�����
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvMsgSmmaInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt;

    /* ������ѡ�� */
    enDomainSelRslt = TAF_SPM_ProcSmsDomainSelection();

    TAF_SPM_ProcSmmaIndDomainSelectionResult(ulEventType, pstMsg, enDomainSelRslt);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvMsgReportInd_PreProc
 ��������  : MAIN״̬����ʼ��״̬�յ�ID_TAF_SPM_MSG_REPORT_IND����Ϣ����.
             ����Ϣ֪ͨSPM���ŷ��ͽ��
             �յ�����Ϣ��check��Ϣ��Я����causeֵ:
             1) causeֵ�����ز�causeֵ��SPM�������ز�������Ϣ��ת����MSGģ�飻
             2) causeֵ�������ز�causeֵ��֪ͨ�ϲ���ŷ���ʧ��
             �����������������ز�����


 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE :��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��12��10��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��4��13��
   ��    ��   : s00217060
   �޸�����   : DTS2015041007878:ID_TAF_SPM_MSG_REPORT_IND�е�client id���ԣ��ز�����δ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvMsgReportInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_MSG_REPORT_IND_STRU                            *pstMsgReportInd = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU                                 *pstCacheMsg     = VOS_NULL_PTR;
    VOS_UINT8                                               ucIndex;
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt;
    VOS_UINT32                                              ulRst;
    VOS_UINT8                                               ucImsSmsSndFlg;

    pstMsgReportInd = (TAF_SPM_MSG_REPORT_IND_STRU *)pstMsg;

    /* ���IMS�������ڷ��ͱ�־ */
    TAF_SPM_SetImsSmsSendingFlg(VOS_FALSE);

    TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvMsgReportInd_PreProc: ImsSmsSendingFlg IS FALSE.");

    if (VOS_TRUE == TAF_SDC_GetSmsRedailFromImsToCsSupportFlag())
    {
        /* �Ӷ����ز�������ȡ��������Ϣ */
        pstCacheMsg = TAF_SPM_GetSmsRedialBufferWithClientId(&ucIndex, pstMsgReportInd->usClientId);

        if (VOS_NULL_PTR != pstCacheMsg)
        {
            if (VOS_TRUE == TAF_MSG_IsSmsRedialCauseValueFromImsDomain(pstMsgReportInd->stRptEvtInfo.enErrorCode))
            {
                if (TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_SPM_SMMA_IND) == pstCacheMsg->ulEventType)
                {
                    /* SMMA��Ϣ����Ҫ�����ⲿ��Ϣ��MSGģ�� */
                    TAF_SPM_SendMsgSmmaRsp(TAF_MSG_SIGNALLING_TYPE_NAS_SIGNALLING,
                                           (struct MsgCB*)&(pstCacheMsg->aucEntryMsgBuffer[0]));

                    TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvMsgReportInd_PreProc: SendMsgSmmaRsp.");
                }
                else
                {
                    /* �޸���Ϣ�е��������� */
                    (VOS_VOID)TAF_SPM_ProcReqMsgBasedOnNasSignalling(pstCacheMsg->ulEventType,
                                                           (struct MsgCB*)&(pstCacheMsg->aucEntryMsgBuffer[0]));

                    /* ���������Ϣ */
                    TAF_SPM_UpdateServiceCtrlEntryMsg(pstCacheMsg->ulEventType,
                                                      (struct MsgCB*)&(pstCacheMsg->aucEntryMsgBuffer[0]));

                    TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);
                }

                /* ����ز����� */
                TAF_SPM_FreeSpecificedIndexSmsRedialBuffer(ucIndex);

                /* �����ʱ��ѡ�񻺴�����Ϣ���ڣ���Ҫ����Ϣת����MSGģ�� */
                if (0 != TAF_SPM_GetSmsMsgQueueNum())
                {
                    /* �����ڲ���ѡ���SPM */
                    TAF_SPM_SndInternalDomainSelectionInd();
                }

                TAF_SPM_LogSrvDomainSelRedialInfo();

                return VOS_FALSE;
            }

            /* ����ز����� */
            TAF_SPM_FreeSpecificedIndexSmsRedialBuffer(ucIndex);

            TAF_SPM_LogSrvDomainSelRedialInfo();
        }

        TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvMsgReportInd_PreProc: VOS_NULL_PTR == pstCacheMsg.");
    }

    TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvMsgReportInd_PreProc: Redail not support.");

    /* ��֧�ֻ����ز�������ϱ����ŷ��ͱ��� */
    TAF_SPM_ProcSmsRptEvent(pstMsgReportInd);

    /* �������������ѡ��queue */
    if (0 != TAF_SPM_GetSmsMsgQueueNum())
    {
        enDomainSelRslt = TAF_SPM_DOMAIN_SEL_RESULT_BUTT;

        ulRst = TAF_SPM_ProcSmsMsgQueue(&enDomainSelRslt);

        /* check if domain selection type is buffer message */
        if (TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE != enDomainSelRslt)
        {
            /* ���������ѡ�񻺴治Ϊ�գ��ҵ�ǰ��IMS�����ڷ��ͣ��������������ѡ�񻺴� */
            ucImsSmsSndFlg = TAF_SPM_GetImsSmsSendingFlg();
            if ((0         != TAF_SPM_GetSmsMsgQueueNum())
             && (VOS_FALSE == ucImsSmsSndFlg))
            {
                TAF_SPM_SndInternalDomainSelectionInd();
            }

            /* log service domain selection infomation */
            TAF_SPM_LogSrvDomainSelQueueInfo();

            return ulRst;
        }
    }

    TAF_SPM_LogSrvDomainSelRedialInfo();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvMsgCheckRsltInd_PreProc
 ��������  : MAIN״̬����ʼ��״̬�յ�ID_TAF_SPM_MSG_CHECK_RESULT_IND����Ϣ����.
             ����Ϣ֪ͨSPM����FDN or CONTROL�����,�յ�����Ϣ�������
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE :��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��11��14��
   ��    ��   : j00174725
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvMsgCheckRsltInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_MSG_CHECK_RESULT_IND_STRU                      *pstMsgCheckRsltInd  = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU                                 *pstCacheMsg         = VOS_NULL_PTR;
    VOS_UINT32                                              ulRst;
    VOS_UINT8                                               ucIndex;
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt;

    pstMsgCheckRsltInd = (TAF_SPM_MSG_CHECK_RESULT_IND_STRU *)pstMsg;

    if ( (pstMsgCheckRsltInd->enRslt != TAF_MSG_ERROR_FDN_CHECK_FAIL)
      && (pstMsgCheckRsltInd->enRslt != TAF_MSG_ERROR_FDN_CHECK_TIMEROUT)
      && (pstMsgCheckRsltInd->enRslt != TAF_MSG_ERROR_CTRL_CHECK_FAIL)
      && (pstMsgCheckRsltInd->enRslt != TAF_MSG_ERROR_CTRL_CHECK_TIMEOUT) )
    {
        return VOS_TRUE;
    }

#if (FEATURE_IMS == FEATURE_ON)
    /* ���IMS�������ڷ��ͱ�־ */
    TAF_SPM_SetImsSmsSendingFlg(VOS_FALSE);

    TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvMsgCheckRsltInd_PreProc: ImsSmsSendingFlg FDN Or SMS CONTROL fail.");

    if (VOS_TRUE == TAF_SDC_GetSmsRedailFromImsToCsSupportFlag())
    {
        /* �Ӷ����ز�������ȡ��������Ϣ */
        pstCacheMsg = TAF_SPM_GetSmsRedialBufferWithClientId(&ucIndex, pstMsgCheckRsltInd->usClientId);

        if (VOS_NULL_PTR != pstCacheMsg)
        {
            /* ����ز����� */
            TAF_SPM_FreeSpecificedIndexSmsRedialBuffer(ucIndex);
        }
    }
#endif

    /* �������������ѡ��queue */
    if (0 != TAF_SPM_GetSmsMsgQueueNum())
    {
        enDomainSelRslt = TAF_SPM_DOMAIN_SEL_RESULT_BUTT;

        ulRst = TAF_SPM_ProcSmsMsgQueue(&enDomainSelRslt);

        /* check if domain selection type is buffer message */
        if (TAF_SPM_DOMAIN_SEL_RESULT_BUFFER_MESSAGE != enDomainSelRslt)
        {
            if (0 != TAF_SPM_GetSmsMsgQueueNum())
            {
                /* �������������ѡ�񻺴� */
                TAF_SPM_SndInternalDomainSelectionInd();
            }

            /* log service domain selection infomation */
            TAF_SPM_LogSrvDomainSelQueueInfo();
        }

        return ulRst;
    }

    TAF_SPM_LogSrvDomainSelRedialInfo();
    TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvMsgCheckRsltInd_PreProc");

    return VOS_TRUE;
}



/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallOrigCnf_PreProc
 ��������  : SPM�յ�IMSA��MN_CALL_EVT_CALL_ORIG_CNF�¼��Ĵ���
 �������  : pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��30��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��09��23��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseII��Ŀ,����IMS��ҵ���ʶ
  3.��    ��   : 2013��12��12��
    ��    ��   : y00245242
    �޸�����   : ����IMS��CS��Ļ����ز�����
  4.��    ��   : 2014��11��06��
    ��    ��   : s00217060
    �޸�����   : DTS2014110608091:IMS�绰ʱ������cs���paging ind
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallOrigCnf_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg           = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU             *pstCacheInfo             = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstImsaCallMsg          = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    /* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-23, begin */
    /* ֻҪMO�ɹ�ʱ��������IMS����д��ڱ�ʶ */
    if (TAF_CS_CAUSE_SUCCESS == stCallInfo.enCause)
    {
        TAF_SDC_SetImsCallExistFlg(VOS_TRUE);
        TAF_SndMmaImsSrvInfoNotify(VOS_TRUE);

        /* �����ز�������Ϣ��call ID��������Ϣ���ͷ�ʱ���� */
        TAF_SPM_UpdateCallRedialBufferMsgWithCallId(stCallInfo.clientId, stCallInfo.callId);
    }
    /* Added by y00245242 for VoLTE_PhaseIII ��Ŀ, 2013-12-12, begin */
    else
    {
        /* IMSA����д���з��򣬱����޸�һ�¸��Ϊ�����ز��ж�ʹ�� */
        stCallInfo.enCallDir = MN_CALL_DIR_MO;

        if (VOS_TRUE == TAF_SPM_IsCsCallRedialAllowed(&stCallInfo))
        {
            /* ��ȡ�����ز�������Ϣ */
            pstCacheInfo = TAF_SPM_GetSpecificedIndexFromCallRedialBuffer(0);

            /* ���������Ϣ */
            TAF_SPM_UpdateServiceCtrlEntryMsg(pstCacheInfo->ulEventType,
                                              (struct MsgCB*)&(pstCacheInfo->aucEntryMsgBuffer[0]));

            TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

            /* ����ز����� */
            TAF_SPM_FreeSpecificedIndexCallRedialBuffer(0);

#if (FEATURE_ON == FEATURE_PTM)
            TAF_SDC_SetErrLogImsCallFailFlag(VOS_TRUE);
            TAF_SDC_SetErrLogImsCallFailCause(stCallInfo.enCause);
#endif

            return VOS_FALSE;
        }

        /* ����ز����� */
        TAF_SPM_FreeSpecificedIndexCallRedialBuffer(0);
    }
    /* Added by y00245242 for VoLTE_PhaseIII ��Ŀ, 2013-12-12, end */
    /* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-23, end */

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* ����һ��MN_CALL_EVT_CALL_ORIG_CNF��Ϣ������Ӧ��cliendId�ظ� */
    MN_SendClientEvent(stCallInfo.clientId,
                        MN_CALLBACK_CS_CALL,
                        MN_CALL_EVT_CALL_ORIG_CNF,
                        &stCallInfo);

#if (FEATURE_ON == FEATURE_PTM)
    /* ��¼CS�����쳣log */
    MN_CALL_CsCallErrRecord(0, stCallInfo.enCause);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallOrig_PreProc
 ��������  : SPM�յ�IMSA��MN_CALL_EVT_ORIG�¼��Ĵ���
 �������  : pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��30��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��12��13��
    ��    ��   : y00245242
    �޸�����   : ����IMS��CS��Ļ����ز�����
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallOrig_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg           = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstImsaCallMsg          = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* ����һ��MN_CALL_EVT_ORIG��Ϣ������Ӧ��cliendId�ظ� */
    MN_SendClientEvent(pstImsaCallMsg->usClientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_ORIG,
                       &stCallInfo);

    /* �����ز�������Ϣ��call ID��������Ϣ���ͷ�ʱ���� */
    TAF_SPM_UpdateCallRedialBufferMsgWithCallId(stCallInfo.clientId, stCallInfo.callId);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallProc_PreProc
 ��������  : SPM�յ�IMSA��MN_CALL_EVT_CALL_PROC�¼��Ĵ���
             ע: call proceeding�¼���IMS�ڲ������������緢�͹������¼������
                 �յ����¼�ʱ���������call ģ����ز�����

 �������  : pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��30��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallProc_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg           = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstImsaCallMsg          = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* ����һ��MN_CALL_EVT_CALL_PROC��Ϣ������Ӧ��cliendId�ظ� */
    MN_SendClientEvent(pstImsaCallMsg->usClientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_CALL_PROC,
                       &stCallInfo);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallAlerting_PreProc
 ��������  : SPM�յ�IMSA��MN_CALL_EVT_ALERTING�¼��Ĵ���
 �������  : pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��30��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��12��13��
    ��    ��   : y00245242
    �޸�����   : ���ӻ����ز�����
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallAlerting_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg           = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstImsaCallMsg          = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* ����һ��MN_CALL_EVT_ALERTING��Ϣ������Ӧ��cliendId�ظ� */
    MN_SendClientEvent(pstImsaCallMsg->usClientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_ALERTING,
                       &stCallInfo);

    /* ����ز����� */
    TAF_SPM_FreeCallRedialBufferWithCallId(pstImsaCallMsg->stCallInfo.callId);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallConnect_PreProc
 ��������  : SPM�յ�IMSA��MN_CALL_EVT_CONNECT�¼��Ĵ���
 �������  : pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��30��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallConnect_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg           = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstImsaCallMsg          = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* ����һ��MN_CALL_EVT_CONNECT��Ϣ������Ӧ��cliendId�ظ� */
    MN_SendClientEvent(pstImsaCallMsg->usClientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_CONNECT,
                       &stCallInfo);

    /* ����ز����� */
    TAF_SPM_FreeCallRedialBufferWithCallId(pstImsaCallMsg->stCallInfo.callId);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallSupsCmdCnf_PreProc
 ��������  : SPM�յ�IMSA��MN_CALL_EVT_SUPS_CMD_CNF�¼��Ĵ���
 �������  : pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��30��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallSupsCmdCnf_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg           = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstImsaCallMsg          = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* ����һ��MN_CALL_EVT_SUPS_CMD_CNF��Ϣ������Ӧ��cliendId�ظ� */
    MN_SendClientEvent(stCallInfo.clientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_SUPS_CMD_CNF,
                       &stCallInfo);


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallRelease_PreProc
 ��������  : SPM�յ�IMSA��MN_CALL_EVT_RELEASED�¼��Ĵ���
 �������  : pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��30��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��12��12��
    ��    ��   : y00245242
    �޸�����   : ����IMS��CS��Ļ����ز�����
  3.��    ��   :2014��9��28��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallRelease_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg           = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    TAF_SPM_ENTRY_MSG_STRU             *pstCacheInfo             = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstImsaCallMsg          = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    /* Added by y00245242 for VoLTE_PhaseIII ��Ŀ, 2013-12-12, begin */
    if (VOS_TRUE == TAF_SPM_IsCsCallRedialAllowed(&stCallInfo))
    {
        /* ��ȡ�����ز�������Ϣ */
        pstCacheInfo = TAF_SPM_GetCallRedialBufferWithCallId(stCallInfo.callId);
        if (VOS_NULL_PTR != pstCacheInfo)
        {
            /* ���������Ϣ */
            TAF_SPM_UpdateServiceCtrlEntryMsg(pstCacheInfo->ulEventType,
                                              (struct MsgCB*)&(pstCacheInfo->aucEntryMsgBuffer[0]));

            TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

            /* ����ز����� */
            TAF_SPM_FreeCallRedialBufferWithCallId(stCallInfo.callId);

#if (FEATURE_ON == FEATURE_PTM)
            TAF_SDC_SetErrLogImsCallFailFlag(VOS_TRUE);
            TAF_SDC_SetErrLogImsCallFailCause(stCallInfo.enCause);
#endif

            return VOS_FALSE;
        }
    }

    /* ����ز����� */
    TAF_SPM_FreeCallRedialBufferWithCallId(stCallInfo.callId);
    /* Added by y00245242 for VoLTE_PhaseIII ��Ŀ, 2013-12-12, end */

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* ����һ��MN_CALL_EVT_RELEASED��Ϣ������Ӧ��cliendId�ظ� */
    MN_SendClientEvent(pstImsaCallMsg->usClientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_RELEASED,
                       &stCallInfo);

#if (FEATURE_ON == FEATURE_PTM)
    /* ��¼CS�����쳣log */
    MN_CALL_CsCallErrRecord(0, stCallInfo.enCause);
#endif

    /* �绰�Ҷ�ʱ������Ӧ���¼������������������ǿ�ָ�룬���ĸ�����������0�������¼�������ȥ */
    if(MN_CALL_DIR_MO == stCallInfo.enCallDir)
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MO_DISCONNECT,
                        &(stCallInfo.enCause),
                        sizeof(TAF_CS_CAUSE_ENUM_UINT32));
    }
    else
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MT_DISCONNECT,
                        &(stCallInfo.enCause),
                        sizeof(TAF_CS_CAUSE_ENUM_UINT32));
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallIncoming_PreProc
 ��������  : SPM�յ�IMSA��MN_CALL_EVT_INCOMING�¼��Ĵ���
 �������  : pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��30��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��09��23��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseII��Ŀ,����IMS��ҵ���ʶ
  3.��    ��   : 2014��11��06��
    ��    ��   : s00217060
    �޸�����   : DTS2014110608091:IMS�绰ʱ������cs���paging ind
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallIncoming_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg           = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstImsaCallMsg          = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    /* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-23, begin */
    /* ����IMS����д��ڱ�ʶ */
    TAF_SDC_SetImsCallExistFlg(VOS_TRUE);
    TAF_SndMmaImsSrvInfoNotify(VOS_TRUE);
    /* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-23, end */

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* ����һ��MN_CALL_EVT_INCOMING��Ϣ������Ӧ��cliendId�ظ� */
    MN_SendClientEvent(pstImsaCallMsg->usClientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_INCOMING,
                       &stCallInfo);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallStartDtmfCnf_PreProc
 ��������  : SPM�յ�IMSA��MN_CALL_EVT_START_DTMF_CNF�¼��Ĵ���
 �������  : pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��30��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  1.��    ��   : 2013��10��25��
    ��    ��   : y00245242
    �޸�����   : �����µ�DTMF�ӿ�
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallStartDtmfCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_START_DTMF_CNF_STRU  *pstStartDtmfCnfMsg       = VOS_NULL_PTR;
    TAF_CALL_EVT_DTMF_CNF_STRU          stDtmfCnf;

    pstStartDtmfCnfMsg      = (IMSA_SPM_CALL_START_DTMF_CNF_STRU *)pstMsg;

    PS_MEM_SET(&stDtmfCnf, 0, sizeof(TAF_CALL_EVT_DTMF_CNF_STRU));

    stDtmfCnf.callId        = pstStartDtmfCnfMsg->ucCallId;
    stDtmfCnf.usClientId    = pstStartDtmfCnfMsg->usClientId;
    stDtmfCnf.opId          = pstStartDtmfCnfMsg->ucOpId;
    stDtmfCnf.enCause       = pstStartDtmfCnfMsg->enCause;
    stDtmfCnf.enDtmfState   = pstStartDtmfCnfMsg->enDtmfState;
    stDtmfCnf.ucDtmfCnt     = pstStartDtmfCnfMsg->ucDtmfCnt;


    TAF_CALL_SendMsg(pstStartDtmfCnfMsg->usClientId,
                     MN_CALL_EVT_START_DTMF_CNF,
                     &stDtmfCnf,
                     sizeof(TAF_CALL_EVT_DTMF_CNF_STRU));

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallStartDtmfRsltInd_PreProc
 ��������  : SPM�յ�IMSA��MN_CALL_EVT_START_DTMF_RSLT_IND�¼��Ĵ���
 �������  : ulEventType:�¼�����
             pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��25��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallStartDtmfRsltInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_START_DTMF_RSLT_IND_STRU                 *pstDtmfRsltIndMsg       = VOS_NULL_PTR;
    TAF_CALL_EVT_DTMF_CNF_STRU                              stDtmfCnf;

    pstDtmfRsltIndMsg      = (IMSA_SPM_CALL_START_DTMF_RSLT_IND_STRU *)pstMsg;

    PS_MEM_SET(&stDtmfCnf, 0, sizeof(TAF_CALL_EVT_DTMF_CNF_STRU));

    stDtmfCnf.callId        = pstDtmfRsltIndMsg->ucCallId;
    stDtmfCnf.usClientId    = pstDtmfRsltIndMsg->usClientId;
    stDtmfCnf.opId          = pstDtmfRsltIndMsg->ucOpId;
    stDtmfCnf.enCause       = pstDtmfRsltIndMsg->enCause;
    stDtmfCnf.enDtmfState   = pstDtmfRsltIndMsg->enDtmfState;
    stDtmfCnf.ucDtmfCnt     = pstDtmfRsltIndMsg->ucDtmfCnt;


    TAF_CALL_SendMsg(pstDtmfRsltIndMsg->usClientId,
                     MN_CALL_EVT_START_DTMF_RSLT,
                     &stDtmfCnf,
                     sizeof(TAF_CALL_EVT_DTMF_CNF_STRU));

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallStopDtmfCnf_PreProc
 ��������  : SPM�յ�IMSA��MN_CALL_EVT_STOP_DTMF_CNF�¼��Ĵ���
 �������  : ulEventType:�¼�����
             pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��30��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  1.��    ��   : 2013��10��25��
    ��    ��   : y00245242
    �޸�����   : �����µ�DTMF�ӿ�
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallStopDtmfCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_STOP_DTMF_CNF_STRU   *pstStopDtmfCnfMsg       = VOS_NULL_PTR;
    TAF_CALL_EVT_DTMF_CNF_STRU          stDtmfCnf;

    pstStopDtmfCnfMsg      = (IMSA_SPM_CALL_STOP_DTMF_CNF_STRU *)pstMsg;

    PS_MEM_SET(&stDtmfCnf, 0, sizeof(TAF_CALL_EVT_DTMF_CNF_STRU));

    stDtmfCnf.callId       = pstStopDtmfCnfMsg->ucCallId;
    stDtmfCnf.usClientId   = pstStopDtmfCnfMsg->usClientId;
    stDtmfCnf.opId         = pstStopDtmfCnfMsg->ucOpId;
    stDtmfCnf.enCause      = pstStopDtmfCnfMsg->enCause;
    stDtmfCnf.enDtmfState  = pstStopDtmfCnfMsg->enDtmfState;
    stDtmfCnf.ucDtmfCnt    = pstStopDtmfCnfMsg->ucDtmfCnt;


    TAF_CALL_SendMsg(pstStopDtmfCnfMsg->usClientId,
                     MN_CALL_EVT_STOP_DTMF_CNF,
                     &stDtmfCnf,
                     sizeof(TAF_CALL_EVT_DTMF_CNF_STRU));

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallStopDtmfRsltInd_PreProc
 ��������  : SPM�յ�IMSA��MN_CALL_EVT_STOP_DTMF_RSLT_IND��Ϣ����
 �������  : ulEventType:�¼�����
             pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��25��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallStopDtmfRsltInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_STOP_DTMF_RSLT_IND_STRU                  *pstDtmfRsltIndMsg       = VOS_NULL_PTR;
    TAF_CALL_EVT_DTMF_CNF_STRU                              stDtmfCnf;

    pstDtmfRsltIndMsg      = (IMSA_SPM_CALL_STOP_DTMF_RSLT_IND_STRU *)pstMsg;

    PS_MEM_SET(&stDtmfCnf, 0, sizeof(TAF_CALL_EVT_DTMF_CNF_STRU));

    stDtmfCnf.callId        = pstDtmfRsltIndMsg->ucCallId;
    stDtmfCnf.usClientId    = pstDtmfRsltIndMsg->usClientId;
    stDtmfCnf.opId          = pstDtmfRsltIndMsg->ucOpId;
    stDtmfCnf.enCause       = pstDtmfRsltIndMsg->enCause;
    stDtmfCnf.enDtmfState   = pstDtmfRsltIndMsg->enDtmfState;
    stDtmfCnf.ucDtmfCnt     = pstDtmfRsltIndMsg->ucDtmfCnt;


    TAF_CALL_SendMsg(pstDtmfRsltIndMsg->usClientId,
                     MN_CALL_EVT_STOP_DTMF_RSLT,
                     &stDtmfCnf,
                     sizeof(TAF_CALL_EVT_DTMF_CNF_STRU));

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallSsCmdRslt_PreProc
 ��������  : SPM�յ�IMSA��MN_CALL_EVT_SS_CMD_RSLT�¼��Ĵ���
 �������  : pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��30��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallSsCmdRslt_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg           = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstImsaCallMsg      = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

#if ( (FEATURE_ON == FEATURE_ECALL)&& (FEATURE_ON == FEATURE_IMS) )
    if (VOS_TRUE == TAF_SPM_GetEcallHangUpImsFlag())
    {
        return VOS_TRUE;
    }
#endif

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* ����һ��MN_CALL_EVT_SS_CMD_RSLT��Ϣ������Ӧ��cliendId�ظ� */
    MN_SendClientEvent(pstImsaCallMsg->usClientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_SS_CMD_RSLT,
                       &stCallInfo);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallSsNotify_PreProc
 ��������  : SPM�յ�IMSA��MN_CALL_EVT_SS_NOTIFY�¼��Ĵ���
 �������  : pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��30��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallSsNotify_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg           = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstImsaCallMsg          = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* ����һ��MN_CALL_EVT_SS_NOTIFY��Ϣ������Ӧ��cliendId�ظ� */
    MN_SendClientEvent(pstImsaCallMsg->usClientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_SS_NOTIFY,
                       &stCallInfo);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallAllRelease_PreProc
 ��������  : SPM�յ�IMSA��MN_CALL_EVT_ALL_RELEASED�¼��Ĵ���
 �������  : pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��30��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��09��23��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseII��Ŀ,����IMS��ҵ���ʶ
  3.��    ��   : 2014��01��24��
    ��    ��   : y00245242
    �޸�����   : Ϊ���л����ز������޸�
  4.��    ��   : 2014��11��06��
    ��    ��   : s00217060
    �޸�����   : DTS2014110608091:IMS�绰ʱ������cs���paging ind
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallAllRelease_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg          = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_ECALL)
#if (FEATURE_IMS == FEATURE_ON)
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstMsgInfo              = VOS_NULL_PTR;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg               = VOS_NULL_PTR;
#endif
#endif
    MN_CALL_INFO_STRU                   stCallInfo;

    /* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-23, begin */
    /* ����IMS����д��ڱ�ʶ */
    TAF_SDC_SetImsCallExistFlg(VOS_FALSE);
    TAF_SndMmaImsSrvInfoNotify(VOS_FALSE);
    /* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-23, end */

    /* ������ز���GU�·�����Ҫ�ϱ�call all release�¼���Ӧ�� */
    if (VOS_FALSE == TAF_SDC_GetCsCallExistFlg())
    {
        pstImsaCallMsg          = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

        pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
        pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

        PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

        PS_MEM_CPY(&stCallInfo, &(pstImsaCallMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

        /* ���������ϱ����ȫ�ֱ�����ֵ */
        PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                    pstCurcRptCtrl->aucRptCfg,
                    MN_CALL_RPT_CFG_MAX_SIZE);

        PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                    pstUnsolicitedRptCtrl->aucRptCfg,
                    MN_CALL_RPT_CFG_MAX_SIZE);

        /* ����һ��MN_CALL_EVT_ALL_RELEASED��Ϣ������Ӧ��cliendId�ظ� */
        MN_SendClientEvent(pstImsaCallMsg->usClientId,
                           MN_CALLBACK_CS_CALL,
                           MN_CALL_EVT_ALL_RELEASED,
                           &stCallInfo);
    }

#if (FEATURE_ON == FEATURE_ECALL)
#if (FEATURE_IMS == FEATURE_ON)
    if (VOS_TRUE == TAF_SPM_GetEcallHangUpImsFlag())
    {
        TAF_SPM_SetEcallHangUpImsFlag(VOS_FALSE);

        /* �������Ϊ�գ����涨ʱ���Ѿ���ʱ���˳���Ϣ���� */
        if (0 == TAF_SPM_GetCcMsgQueueNum())
        {
            return VOS_TRUE;
        }

        pstMsgInfo      = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(0);
        pstAppMsg       = (MN_CALL_APP_REQ_MSG_STRU *)&(pstMsgInfo->stMsgEntry.aucEntryMsgBuffer[0]);

        /* ֹͣ������ʱ��TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER */
        TAF_SPM_StopTimer(TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER, pstAppMsg->clientId);

        /* �����Ϊ�ɹ����ø��������Ϣ��ǲ������޸ĺ�������Ϣ��ȫ�ֱ����� */
        TAF_SPM_UpdateServiceCtrlEntryMsg(pstMsgInfo->stMsgEntry.ulEventType, (struct MsgCB *)pstAppMsg);

        TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

        /* ������� */
        TAF_SPM_FreeSpecificedIndexMessageInCcQueue(0);
        return VOS_FALSE;
    }
#endif
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallMsg_PreProc
 ��������  : SPM�յ�ID_IMSA_SPM_CALL_MSG�Ĵ���
 �������  : ulEventType:�¼�����
             pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��11��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallMsg_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulRetFlg;
    TAF_SPM_PROC_IMSA_CALL_MSG_STRU    *pstTabHeader    = VOS_NULL_PTR;
    IMSA_SPM_CALL_MSG_STRU             *pstImsaCallMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulTabSize;

    pstImsaCallMsg      = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    /* ��ȡ�������ı���׵�ַ */
    pstTabHeader = TAF_SPM_GetImsaCallMsgTabAddr();

    ulRetFlg     = VOS_TRUE;
    ulTabSize    = TAF_SPM_GetImsaCallMsgTabSize();

    /* ����EventType��� */
    for (i = 0; i < ulTabSize; i++)
    {
        if (pstImsaCallMsg->enEventType == pstTabHeader->ulMsgEvtType)
        {
            ulRetFlg = pstTabHeader->pfMsgFun(pstMsg);

            break;
        }

        pstTabHeader++;
    }

    return ulRetFlg;
}


/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaGetCallInfoCnf_PreProc
 ��������  : SPM�յ�ID_IMSA_SPM_CALL_GET_CALL_INFO_CNF�Ĵ���
 �������  : ulEventType:�¼�����
             pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��11��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��09��18��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseII��Ŀ������״̬�ı�ʱ֪ͨSPM
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaGetCallInfoCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_GET_CALL_INFO_CNF_STRU                   *pstImsaMsg  = VOS_NULL_PTR;

    pstImsaMsg = (IMSA_SPM_CALL_GET_CALL_INFO_CNF_STRU *)pstMsg;

    if (MN_CALL_MAX_NUM < pstImsaMsg->ucNumOfCalls)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvImsaGetCallInfoCnf_PreProc: call numbers is abnormal!");

        return VOS_TRUE;
    }

    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-18, begin */
    if (CALL_IMSA_GET_CALL_INFO_REQ_TYPE_ATA == pstImsaMsg->enReqType)
    {
        /* ����������ATAʱ����TAFAGENT API��ѯ������Ϣ,��TAFAGENT�ظ� */
        TAF_SPM_SendTafAgentGetCallInfoCnf(pstImsaMsg);
    }
    else
    {
        /* ����������CLCC��ѯ������Ϣ,��AT�ظ� */
        TAF_SPM_SendAtGetCallInfoCnf(pstImsaMsg);
    }
    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-18, end */

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaChannelInfoInd_PreProc
 ��������  : SPM�յ�ID_IMSA_SPM_CHANNEL_INFO_IND�Ĵ���
 �������  : ulEventType:�¼�����
             pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��11��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��3��29��
    ��    ��   : W00176964
    �޸�����   : DTS2014032901140:�ӿ��Ż�����
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaChannelInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CHANNEL_INFO_IND_STRU     *pstImsaMsg  = VOS_NULL_PTR;
    MN_CALL_EVT_CHANNEL_INFO_STRU       stChannelEvt;

    pstImsaMsg  = (IMSA_SPM_CHANNEL_INFO_IND_STRU *)pstMsg;

    /* ����һ����Ϣ����AT�ظ� */
    PS_MEM_SET(&stChannelEvt, 0x00, sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU));

    stChannelEvt.enEvent                = MN_CALL_EVT_CHANNEL_INFO_IND;
    stChannelEvt.usClientId             = MN_GetRealClientId(pstImsaMsg->usClientId, WUEPS_PID_TAF);
    stChannelEvt.ucIsLocalAlertingFlag  = pstImsaMsg->ucIsLocalAlertingFlag;
    stChannelEvt.enVoiceDomain          = TAF_CALL_VOICE_DOMAIN_IMS;
    stChannelEvt.enCodecType            = pstImsaMsg->enCodecType;

    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stChannelEvt, sizeof(MN_CALL_EVT_CHANNEL_INFO_STRU));

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaGetClprCnf_PreProc
 ��������  : ID_IMSA_SPM_CALL_GET_CLPR_CNF������
 �������  : ulEventType
             pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��18��
    ��    ��   : Y00213812
    �޸�����   : ��������

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaGetClprCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_GET_CLPR_CNF_STRU    *pstImsaMsg  = VOS_NULL_PTR;
    MN_CALL_CLPR_GET_CNF_STRU           stClprCnf;

    pstImsaMsg  = (IMSA_SPM_CALL_GET_CLPR_CNF_STRU *)pstMsg;

    /* ����һ����Ϣ����AT�ظ� */
    PS_MEM_SET(&stClprCnf, 0x00, sizeof(MN_CALL_CLPR_GET_CNF_STRU));

    stClprCnf.enEvent                   = MN_CALL_EVT_CLPR_SET_CNF;
    stClprCnf.stAppCtrl.usClientId      = pstImsaMsg->usClientId;
    stClprCnf.ulRet                     = pstImsaMsg->ulRet;
    stClprCnf.stRedirectInfo            = pstImsaMsg->stRedirectInfo;

    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stClprCnf, sizeof(MN_CALL_CLPR_GET_CNF_STRU));

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallHold_PreProc
 ��������  : SPM�յ�ID_IMSA_SPM_CALL_HOLD�Ĵ���
 �������  : pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��11��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��10��31��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseII
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallHold_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaMsg              = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;
    MN_CALL_EVT_HOLD_STRU               stEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();


    pstImsaMsg  = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    PS_MEM_SET(&stEvent, 0, sizeof(MN_CALL_EVT_HOLD_STRU));
    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stEvent.enEvent         = MN_CALL_EVT_HOLD;
    stEvent.usClientId      = MN_GetRealClientId(pstImsaMsg->usClientId, WUEPS_PID_TAF);
    stEvent.ucCallNum       = 1;
    stEvent.aucCallId[0]    = pstImsaMsg->stCallInfo.callId;
    /* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-10-31, begin */
    stEvent.enVoiceDomain   = pstImsaMsg->stCallInfo.enVoiceDomain;
    /* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-10-31, end */

    PS_MEM_CPY(stEvent.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                sizeof(stEvent.aucCurcRptCfg));
    PS_MEM_CPY(stEvent.aucUnsolicitedRptCfg,
            pstUnsolicitedRptCtrl->aucRptCfg,
            sizeof(stEvent.aucUnsolicitedRptCfg));

    /* ��HOLD�¼����͵�AT */
    if (VOS_TRUE == TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CALLSTATE))
    {
        MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stEvent, sizeof(MN_CALL_EVT_HOLD_STRU));
    }

    /* ��HOLD�¼����͵�OAM */
    PS_MEM_CPY(&stCallInfo, &(pstImsaMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    MN_CS_SendMsgToOam(MN_CLIENT_ALL,
                       MN_CALL_EVT_HOLD,
                       MAPS_STK_PID,
                       &stCallInfo);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallRetrieve_PreProc
 ��������  : SPM�յ�ID_IMSA_SPM_CALL_RETRIEVE�Ĵ���
 �������  : pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��11��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��10��31��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseII
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallRetrieve_PreProc(
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MSG_STRU             *pstImsaMsg              = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl          = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;
    MN_CALL_EVT_RETRIEVE_STRU           stEvent;
    MN_CALL_INFO_STRU                   stCallInfo;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    pstImsaMsg  = (IMSA_SPM_CALL_MSG_STRU *)pstMsg;

    PS_MEM_SET(&stEvent, 0, sizeof(MN_CALL_EVT_RETRIEVE_STRU));
    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stEvent.enEvent         = MN_CALL_EVT_RETRIEVE;
    stEvent.usClientId      = MN_GetRealClientId(pstImsaMsg->usClientId, WUEPS_PID_TAF);
    stEvent.ucCallNum       = 1;
    stEvent.aucCallId[0]    = pstImsaMsg->stCallInfo.callId;
    /* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-10-31, begin */
    stEvent.enVoiceDomain   = pstImsaMsg->stCallInfo.enVoiceDomain;
    /* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-10-31, end */

    PS_MEM_CPY(stEvent.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                sizeof(stEvent.aucCurcRptCfg));
    PS_MEM_CPY(stEvent.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                sizeof(stEvent.aucUnsolicitedRptCfg));

    /* ��RETRIEVE�¼����͵�AT */
    if (VOS_TRUE == TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CALLSTATE))
    {
        MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stEvent, sizeof(MN_CALL_EVT_RETRIEVE_STRU));
    }

    /* ��RETRIEVE�¼����͵�OAM */
    PS_MEM_CPY(&stCallInfo, &(pstImsaMsg->stCallInfo), sizeof(MN_CALL_INFO_STRU));

    MN_CS_SendMsgToOam(MN_CLIENT_ALL,
                       MN_CALL_EVT_RETRIEVE,
                       MAPS_STK_PID,
                       &stCallInfo);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaSsMsg_PreProc
 ��������  : ����IMSA������message: ID_IMSA_SPM_SS_MSG
 �������  : ulEventType  ��Ϣ�¼�����
             pstRcvMsg    ��Ϣָ��

 �������  : ��
 �� �� ֵ  : VOS_FALSE  ��Ϣδ����
             VOS_FALSE  ��Ϣ�Ѵ���

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��11��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaSsMsg_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstRcvMsg
)
{
    IMSA_SPM_SS_MSG_STRU               *pstImsaMsg = VOS_NULL_PTR;


    pstImsaMsg = (IMSA_SPM_SS_MSG_STRU *)pstRcvMsg;

    MN_SendClientEvent(pstImsaMsg->usClientId,
                       MN_CALLBACK_SS,
                       (VOS_UINT32)(pstImsaMsg->stSsEventInfo.SsEvent),
                       (VOS_VOID *)&(pstImsaMsg->stSsEventInfo));

    switch(pstImsaMsg->stSsEventInfo.SsEvent)
    {
        /* �������������SSҵ����Ҫ���ϱ�־ */
        case TAF_SS_EVT_REGISTERSS_CNF:
        case TAF_SS_EVT_USS_NOTIFY_IND:

            TAF_SDC_SetImsSsSrvExistFlg(VOS_TRUE);

            break;

        /* �����¼���Ҫ�����־ */
        case TAF_SS_EVT_ERROR:
        case TAF_SS_EVT_ERASESS_CNF:
        case TAF_SS_EVT_ACTIVATESS_CNF:
        case TAF_SS_EVT_DEACTIVATESS_CNF:
        case TAF_SS_EVT_INTERROGATESS_CNF:
        case TAF_SS_EVT_PROCESS_USS_REQ_CNF:
        case TAF_SS_EVT_USS_RELEASE_COMPLETE_IND:
        case TAF_SS_EVT_ERASE_CC_ENTRY_CNF:
        case TAF_SS_EVT_PROBLEM:

            TAF_SDC_SetImsSsSrvExistFlg(VOS_FALSE);

            break;

        /* �����¼�ʱ����Ҫ����/�����־ */
        default:

            break;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaNormalRegStatusNotify_PreProc
 ��������  : �յ�ID_IMSA_NORMAL_REG_STATUS_NOTIFY��Ϣ�Ĵ���, ����Ϣ֪ͨSPM��ǰ
             IMSע��״̬�����յ�����Ϣʱ��SPM���ر���IMSע��״̬����check����
             ������У�����������л�����Ϣ����������ѡ�񣬴�������Ϣ����
             ��Ӧ��ֹͣ��ض�ʱ��

 �������  : ulEventType  ��Ϣ�¼�����
             pstRcvMsg    ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaNormalRegStatusNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRst;

    /* ���������Ϣ */
    ulRst = TAF_SPM_ProcImsaNormalRegStatusNotify(pstMsg);

    return ulRst;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvInternalDomainSelInd_PreProc
 ��������  : �յ�ID_SPM_SPM_INTERNAL_DOMAIN_SEL_IND�Ĵ����յ�����Ϣʱ�����������Ϣ

 �������  : ulEventType  ��Ϣ�¼�����
             pstRcvMsg    ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvInternalDomainSelInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRst;

    /* ���������Ϣ */
    ulRst = TAF_SPM_ProcBufferedMsgInQueue();

    return ulRst;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvMmaServiceStatusChangeNotify_PreProc
 ��������  : �յ�MMA ID_MMA_TAF_SERVICE_STATUS_CHANGE_NOTIFY��Ϣ�Ĵ���
 �������  : ulEventType  ��Ϣ�¼�����
             pstRcvMsg    ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��18��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��1��2��
    ��    ��   : y00245242
    �޸�����   : ���Ӷ�IMSע�����⴦����
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvMmaServiceStatusChangeNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRlst;
    TAF_SPM_SERVICE_STATUS_ENUM_UINT8   enLastPsStatus;
    TAF_SPM_SERVICE_STATUS_ENUM_UINT8   enCurrPsStatus;

    /* ��ȡ�ϴ�PS����״̬ */
    enLastPsStatus = TAF_SPM_GetLastPsServiceStatus();

    /* ���µ�ǰ��PS����״̬��SPM CONTEXT�� */
    enCurrPsStatus = (TAF_SPM_SERVICE_STATUS_ENUM_UINT8)TAF_SDC_GetPsServiceStatus();
    if (TAF_SPM_SERVICE_STATUS_BUTT < enCurrPsStatus)
    {
        return  VOS_FALSE;
    }
    TAF_SPM_SetLastPsServiceStatus(enCurrPsStatus);

    if (VOS_TRUE == TAF_SPM_IsNeedtoWaitImsRegStatus(enLastPsStatus))
    {
        /* �ȴ���IMSע���� */
        return VOS_TRUE;
    }

    /* ���������Ϣ */
    ulRlst = TAF_SPM_ProcBufferedMsgInQueue();

    return ulRlst;

}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvMmaNetworkCapabilityChangeNotify_PreProc
 ��������  : �յ�MMA ID_MMA_TAF_NETWORK_CAPABILITY_CHANGE_NOTIFY��Ϣ�Ĵ���
 �������  : ulEventType  ��Ϣ�¼�����
             pstRcvMsg    ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��18��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvMmaNetworkCapabilityChangeNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRlst;

    /* ���������Ϣ */
    ulRlst = TAF_SPM_ProcBufferedMsgInQueue();

    return ulRlst;

}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvMmaRatChangeNotify_PreProc
 ��������  : �յ�MMA ID_MMA_TAF_RAT_CHANGE_NOTIFY��Ϣ�Ĵ���
 �������  : ulEventType  ��Ϣ�¼�����
             pstRcvMsg    ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��18��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvMmaRatChangeNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRlst;

    /* ���������Ϣ�������������仯ʱ�Ĵ���һ�� */
    ulRlst = TAF_SPM_ProcBufferedMsgInQueue();

    return ulRlst;
}

/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-31, begin */

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvMmaImsVoiceCapInd_PreProc
 ��������  : �յ�MMA ID_MMA_TAF_IMS_VOICE_CAP_IND��Ϣ�Ĵ���
 �������  : ulEventType  ��Ϣ�¼�����
             pstRcvMsg    ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��31��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvMmaImsVoiceCapInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRlst;

    /* ���������Ϣ�������������仯ʱ�Ĵ���һ�� */
    ulRlst = TAF_SPM_ProcBufferedMsgInQueue();

    return ulRlst;
}
/* Added by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-31, end */


/*****************************************************************************
  �� �� ��  : TAF_SPM_RcvImsaCallMsgSyncInd_PreProc
  ��������  : �յ�IMSA�ĺ�����Ϣͬ��ָʾ��Ϣ���յ�����Ϣ������ز�����

  �������  : ulEventType -- ��Ϣ�¼�����
              pstMsg      -- ��Ϣָ��

  �������  : ��
  �� �� ֵ  : VOS_TRUE  -- ��Ϣ�������
              VOS_FALSE -- ��Ϣδ�������

  ���ú���  :
  ��������  :

  �޸���ʷ      :
   1.��    ��   : 2013��12��18��
     ��    ��   : y00245242
     �޸�����   : �����ɺ���
 *****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallMsgSyncInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucNum;
    VOS_UINT8                           i;

    /* �����ز�δ�򿪣�ֱ�ӷ��� */
    if (VOS_TRUE == TAF_SDC_GetCallRedailFromImsToCsSupportFlag())
    {
        /* ����SRVCC����ǰ�ĺ��������߻����ز����̣�IMSA��֤�ڸ���Ϣǰ�ȷ���SPM,
         * ��ˣ�����յ�����Ϣʱ���ز���������Ȼ����Ϣ����һ������SRVCC�������յ���
         * ������������ز����棬����������Ϣ��callģ�鸺����
         */
        ucNum = TAF_SPM_GetNumberOfCallRedialBuffer();

        for (i = 0; i < ucNum; i++)
        {
            TAF_SPM_FreeSpecificedIndexCallRedialBuffer(i);
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
  �� �� ��  : TAF_SPM_RcvImsaCallInviteNewPtptCnf_PreProc
  ��������  : �������������ͨ�������ȷ����Ϣ

  �������  : ulEventType -- ��Ϣ�¼�����
              pstMsg      -- ��Ϣָ��

  �������  : ��
  �� �� ֵ  : VOS_TRUE  -- ��Ϣ�������
              VOS_FALSE -- ��Ϣδ�������

  ���ú���  :
  ��������  :

  �޸���ʷ      :
   1.��    ��   : 2014��2��13��
     ��    ��   : y00245242
     �޸�����   : �����ɺ���
 *****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallInviteNewPtptCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_INVITE_NEW_PTPT_CNF_STRU                 *pstNewPtptCnf         = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU                             *pstCurcRptCtrl        = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU                      *pstUnsolicitedRptCtrl = VOS_NULL_PTR;
    MN_CALL_INFO_STRU                                       stCallInfo;

    pstNewPtptCnf = (IMSA_SPM_CALL_INVITE_NEW_PTPT_CNF_STRU *)pstMsg;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stCallInfo, 0, sizeof(MN_CALL_INFO_STRU));

    stCallInfo.clientId = pstNewPtptCnf->usClientId;
    stCallInfo.opId     = pstNewPtptCnf->ucOpId;
    stCallInfo.enCause  = pstNewPtptCnf->enCause;

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    PS_MEM_CPY(stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* ����һ��MN_CALL_EVT_CALL_ORIG_CNF��Ϣ������Ӧ��cliendId�ظ� */
    MN_SendClientEvent(stCallInfo.clientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_CALL_ORIG_CNF,
                       &stCallInfo);

#if (FEATURE_ON == FEATURE_PTM)
    /* ��¼CS�����쳣log */
    MN_CALL_CsCallErrRecord(0, stCallInfo.enCause);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallTypeChangeInfoInd_PreProc
 ��������  : SPM�յ�IMSA��ID_IMSA_SPM_CALL_TYPE_CHANGE_INFO_IND�¼��Ĵ���
 �������  : pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��17��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallTypeChangeInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_TYPE_CHANGE_INFO_IND_STRU                 *pstImsaCallMsg           = VOS_NULL_PTR;

    pstImsaCallMsg  = (IMSA_SPM_CALL_TYPE_CHANGE_INFO_IND_STRU *)pstMsg;

    /* �����·��Ľ������б���û�д�110������110ʱ������ͨ���з���ȥ��IMSָʾ��Ҫ�����������أ��Խ��������·��𣬲�Я��ԭ��ֵ#380
       IMSA�����������أ��Խ��������������ز�����ʱ�ϱ�ID_IMSA_SPM_CALL_TYPE_CHANGE_INFO_IND��ָʾ�������ͱ�� */

    /* Modified by s00217060 for ���ƶ�VoLTE����, 2014-10-17, begin */
    /* �����ز�������Ϣ��call type���ڻ����ز�ʱ���Խ�������CS���ز� */
    TAF_SPM_UpdateCallRedialBufferMsgWithCallType(pstImsaCallMsg->usClientId,
                                                  pstImsaCallMsg->enDestCallType,
                                                  &(pstImsaCallMsg->stEmergencyCat));
    /* Modified by s00217060 for ���ƶ�VoLTE����, 2014-10-17, End */

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvAppCallModifyReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��MN_CALL_APP_CALL_MODIFY_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��06��16��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppCallModifyReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    MN_CALL_MODIFY_CNF_STRU             stModifyCnf;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg;

    /* ����Ϣ�����뵽״̬������ */
    ulRet     = VOS_TRUE;
    pstAppMsg = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    /* ����һ����Ϣ����AT�ظ� */
    PS_MEM_SET(&stModifyCnf, 0x00, sizeof(MN_CALL_MODIFY_CNF_STRU));

    /* ����Ѿ�IMS����д��ڣ�ֱ��ѡ��IMS�������������VOS_FALSE��ʧ�ܴ��� */
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
    }
    else
    {
        /* �����ѡ��ΪCS����ֱ�Ӹ�AT�ظ�ʧ�� */
        stModifyCnf.enEvent                 = MN_CALL_EVT_CALL_MODIFY_CNF;
        stModifyCnf.usClientId              = pstAppMsg->clientId;
        stModifyCnf.ucOpId                  = pstAppMsg->opId;
        stModifyCnf.ucCallId                = pstAppMsg->callId;
        stModifyCnf.enCause                 = TAF_CS_CAUSE_DOMAIN_SELECTION_FAILURE;

        MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stModifyCnf, sizeof(MN_CALL_MODIFY_CNF_STRU));
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvAppCallAnswerRemoteModifyReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��MN_CALL_APP_CALL_ANSWER_REMOTE_MODIFY_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��06��16��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppCallAnswerRemoteModifyReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    MN_CALL_MODIFY_CNF_STRU             stModifyCnf;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg;

    /* ����Ϣ�����뵽״̬������ */
    ulRet     = VOS_TRUE;
    pstAppMsg = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    /* ����һ����Ϣ����AT�ظ� */
    PS_MEM_SET(&stModifyCnf, 0x00, sizeof(MN_CALL_MODIFY_CNF_STRU));

    /* ����Ѿ�IMS����д��ڣ�ֱ��ѡ��IMS�������������VOS_FALSE��ʧ�ܴ��� */
    if (VOS_TRUE == TAF_SDC_GetImsCallExistFlg())
    {
        ulRet = TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);
    }
    else
    {
        /* �����ѡ��ΪCS����ֱ�Ӹ�AT�ظ�ʧ�� */
        stModifyCnf.enEvent                 = MN_CALL_EVT_CALL_ANSWER_REMOTE_MODIFY_CNF;
        stModifyCnf.usClientId              = pstAppMsg->clientId;
        stModifyCnf.ucOpId                  = pstAppMsg->opId;
        stModifyCnf.ucCallId                = pstAppMsg->callId;
        stModifyCnf.enCause                 = TAF_CS_CAUSE_DOMAIN_SELECTION_FAILURE;

        MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stModifyCnf, sizeof(MN_CALL_MODIFY_CNF_STRU));
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallModifyCnf_PreProc
 ��������  : SPM�յ�ID_IMSA_SPM_CALL_MODIFY_CNF�Ĵ���
 �������  : ulEventType:�¼�����
             pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallModifyCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MODIFY_CNF_STRU      *pstImsaMsg  = VOS_NULL_PTR;
    MN_CALL_MODIFY_CNF_STRU             stModifyCnf;

    pstImsaMsg  = (IMSA_SPM_CALL_MODIFY_CNF_STRU *)pstMsg;

    /* ����һ����Ϣ����AT�ظ� */
    PS_MEM_SET(&stModifyCnf, 0x00, sizeof(MN_CALL_MODIFY_CNF_STRU));

    stModifyCnf.enEvent                 = MN_CALL_EVT_CALL_MODIFY_CNF;
    stModifyCnf.usClientId              = pstImsaMsg->usClientId;
    stModifyCnf.ucOpId                  = pstImsaMsg->ucOpId;
    stModifyCnf.ucCallId                = pstImsaMsg->callId;
    stModifyCnf.enCause                 = pstImsaMsg->enCause;

    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stModifyCnf, sizeof(MN_CALL_MODIFY_CNF_STRU));

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallAnswerRemoteModifyCnf_PreProc
 ��������  : SPM�յ�ID_IMSA_SPM_CALL_ANSWER_REMOTE_MODIFY_CNF�Ĵ���
 �������  : ulEventType:�¼�����
             pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallAnswerRemoteModifyCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_ANSWER_REMOTE_MODIFY_CNF_STRU    *pstImsaMsg  = VOS_NULL_PTR;
    MN_CALL_MODIFY_CNF_STRU                         stModifyCnf;

    pstImsaMsg  = (IMSA_SPM_CALL_ANSWER_REMOTE_MODIFY_CNF_STRU *)pstMsg;

    /* ����һ����Ϣ����AT�ظ� */
    PS_MEM_SET(&stModifyCnf, 0x00, sizeof(MN_CALL_MODIFY_CNF_STRU));

    stModifyCnf.enEvent                 = MN_CALL_EVT_CALL_ANSWER_REMOTE_MODIFY_CNF;
    stModifyCnf.usClientId              = pstImsaMsg->usClientId;
    stModifyCnf.ucOpId                  = pstImsaMsg->ucOpId;
    stModifyCnf.ucCallId                = pstImsaMsg->callId;
    stModifyCnf.enCause                 = pstImsaMsg->enCause;

    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stModifyCnf, sizeof(MN_CALL_MODIFY_CNF_STRU));

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaCallModifyStatusInd_PreProc
 ��������  : SPM�յ�ID_IMSA_SPM_CALL_MODIFY_STATUS_IND�Ĵ���
 �������  : ulEventType:�¼�����
             pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaCallModifyStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_MODIFY_STATUS_IND_STRU   *pstImsaMsg  = VOS_NULL_PTR;
    MN_CALL_EVT_MODIFY_STATUS_IND_STRU      stModifyInd;

    pstImsaMsg  = (IMSA_SPM_CALL_MODIFY_STATUS_IND_STRU *)pstMsg;

    /* ����һ����Ϣ����AT�ظ� */
    PS_MEM_SET(&stModifyInd, 0x00, sizeof(MN_CALL_EVT_MODIFY_STATUS_IND_STRU));

    stModifyInd.enEvent                 = MN_CALL_EVT_CALL_MODIFY_STATUS_IND;
    stModifyInd.usClientId              = MN_GetRealClientId(pstImsaMsg->usClientId, WUEPS_PID_TAF);
    stModifyInd.ucOpId                  = pstImsaMsg->ucOpId;
    stModifyInd.ucCallId                = pstImsaMsg->callId;
    stModifyInd.enModifyStatus          = (MN_CALL_MODIFY_STATUS_ENUM_UINT8)pstImsaMsg->enModifyStatus;
    stModifyInd.enVoiceDomain           = pstImsaMsg->enVoiceDomain;
    stModifyInd.enCurrCallType          = pstImsaMsg->enCurrCallType;
    stModifyInd.enExpectCallType        = pstImsaMsg->enExpectCallType;
    stModifyInd.enCause                 = pstImsaMsg->enCause;

    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)&stModifyInd, sizeof(MN_CALL_EVT_MODIFY_STATUS_IND_STRU));

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvAppEconfDialReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��TAF_CALL_APP_ECONF_DIAL_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��28��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppEconfDialReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg;

    pstAppMsg   = (MN_CALL_APP_REQ_MSG_STRU *)pstMsg;

    /* ��ʼ��Econf����Ϣ */
    TAF_SPM_InitEconfInfo();

    /* �����绰���������Ϣ */
    TAF_SPM_ParseEconfDailInfoFromMsg(pstMsg);

    /* call is allowed if phone mode is power on */
    if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        TAF_SPM_SendAtEconfDialCnf(pstAppMsg->clientId,
                                   pstAppMsg->opId,
                                   pstAppMsg->callId,
                                   TAF_CS_CAUSE_POWER_OFF);
        /* ��¼״̬ */
        TAF_SPM_SetEconfPreRslt(TAF_CS_CAUSE_POWER_OFF);

        /* �ϱ�Notify Ind */
        TAF_SPM_ReportEconfCheckRslt();

        return VOS_TRUE;
    }

    /* ��ǿ�Ͷ෽ͨ��ֻ��MN_CALL_TYPE_VOICE���� */
    if (MN_CALL_TYPE_VOICE != pstAppMsg->unParm.stEconfDial.enCallType)
    {
        TAF_SPM_SendAtEconfDialCnf(pstAppMsg->clientId,
                                   pstAppMsg->opId,
                                   pstAppMsg->callId,
                                   TAF_CS_CAUSE_NOT_ALLOW);
        /* ��¼״̬ */
        TAF_SPM_SetEconfPreRslt(TAF_CS_CAUSE_NOT_ALLOW);

        /* �ϱ�Notify Ind */
        TAF_SPM_ReportEconfCheckRslt();

        return VOS_TRUE;
    }

    /* forbid normal call when USIM service is not available */
    if (VOS_FALSE == TAF_SPM_IsUsimServiceAvailable())
    {
        TAF_SPM_SendAtEconfDialCnf(pstAppMsg->clientId,
                                   pstAppMsg->opId,
                                   pstAppMsg->callId,
                                   TAF_CS_CAUSE_SIM_NOT_EXIST);
        /* ��¼״̬ */
        TAF_SPM_SetEconfPreRslt(TAF_CS_CAUSE_SIM_NOT_EXIST);

        /* �ϱ�Notify Ind */
        TAF_SPM_ReportEconfCheckRslt();

        return VOS_TRUE;
    }

    /* ��Ҫ�ж���������Ч,��Ϊ������Ч������ܻ�disable LTE��GU�� */
    if (VOS_FALSE == TAF_SDC_IsUsimStausValid())
    {
        TAF_SPM_SendAtEconfDialCnf(pstAppMsg->clientId,
                                   pstAppMsg->opId,
                                   pstAppMsg->callId,
                                   TAF_CS_CAUSE_SIM_INVALID);

        /* ��¼״̬ */
        TAF_SPM_SetEconfPreRslt(TAF_CS_CAUSE_SIM_INVALID);

        /* �ϱ�Notify Ind */
        TAF_SPM_ReportEconfCheckRslt();

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaEconfDialCnf_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��ID_IMSA_SPM_CALL_ECONF_DIAL_CNF��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��28��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaEconfDialCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_ECONF_DIAL_CNF_STRU     *pstImsaMsg  = VOS_NULL_PTR;

    pstImsaMsg  = (IMSA_SPM_CALL_ECONF_DIAL_CNF_STRU *)pstMsg;

    /* ֻҪMO�ɹ�ʱ��������IMS����д��ڱ�ʶ */
    if (TAF_CS_CAUSE_SUCCESS == pstImsaMsg->enCause)
    {
        TAF_SDC_SetImsCallExistFlg(VOS_TRUE);
        TAF_SndMmaImsSrvInfoNotify(VOS_TRUE);
    }

    /* ����һ����Ϣ����AT�ظ� */
    TAF_SPM_SendAtEconfDialCnf(pstImsaMsg->usClientId,
                               pstImsaMsg->ucOpId,
                               pstImsaMsg->ucCallId,
                               pstImsaMsg->enCause);

#if (FEATURE_ON == FEATURE_PTM)
    /* ��¼CS�����쳣log */
    MN_CALL_CsCallErrRecord(0, pstImsaMsg->enCause);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaEconfAddUsersCnf_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��ID_IMSA_SPM_CALL_ECONF_ADD_USERS_CNF��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��28��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaEconfAddUsersCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_ECONF_ADD_USERS_CNF_STRU     *pstImsaMsg  = VOS_NULL_PTR;

    pstImsaMsg  = (IMSA_SPM_CALL_ECONF_ADD_USERS_CNF_STRU *)pstMsg;

    /* ����һ����Ϣ����AT�ظ� */
    TAF_SPM_SendAtEconfDialCnf(pstImsaMsg->usClientId,
                               pstImsaMsg->ucOpId,
                               pstImsaMsg->ucOpId,
                               pstImsaMsg->enCause);

#if (FEATURE_ON == FEATURE_PTM)
    /* ��¼CS�����쳣log */
    MN_CALL_CsCallErrRecord(0, pstImsaMsg->enCause);
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaEconfNotifyInd_PreProc
 ��������  : SPM�յ�IMSA��ID_IMSA_SPM_CALL_ECONF_NOTIFY_IND�¼��Ĵ���
 �������  : pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��11��28��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaEconfNotifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_ECONF_NOTIFY_IND_STRU    *pstImsaMsg      = VOS_NULL_PTR;
    TAF_CALL_EVT_ECONF_NOTIFY_IND_STRU     *pstNotifyInd    = VOS_NULL_PTR;

    pstNotifyInd = (TAF_CALL_EVT_ECONF_NOTIFY_IND_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_CALL_EVT_ECONF_NOTIFY_IND_STRU));
    if (VOS_NULL_PTR == pstNotifyInd)
    {
        return VOS_TRUE;
    }

    pstImsaMsg  = (IMSA_SPM_CALL_ECONF_NOTIFY_IND_STRU *)pstMsg;

    /* ����һ����Ϣ����AT�ظ� */
    PS_MEM_SET(pstNotifyInd, 0x00, sizeof(TAF_CALL_EVT_ECONF_NOTIFY_IND_STRU));

    pstNotifyInd->enEvent          = TAF_CALL_EVT_ECONF_NOTIFY_IND;
    pstNotifyInd->usClientId       = MN_GetRealClientId(pstImsaMsg->usClientId, WUEPS_PID_TAF);
    pstNotifyInd->ucOpId           = pstImsaMsg->ucOpId;

    if (pstImsaMsg->ucNumOfCalls > TAF_CALL_MAX_ECONF_CALLED_NUM)
    {
        pstNotifyInd->ucNumOfCalls = TAF_CALL_MAX_ECONF_CALLED_NUM;
    }
    else
    {
        pstNotifyInd->ucNumOfCalls = pstImsaMsg->ucNumOfCalls;
    }

    PS_MEM_CPY(pstNotifyInd->astCallInfo,
               pstImsaMsg->astCallInfo,
               sizeof(TAF_CALL_ECONF_INFO_PARAM_STRU) * pstImsaMsg->ucNumOfCalls);

    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8 *)pstNotifyInd, sizeof(TAF_CALL_EVT_ECONF_NOTIFY_IND_STRU));

    PS_MEM_FREE(WUEPS_PID_TAF, pstNotifyInd);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvAppGetEconfInfoReq_PreProc
 ��������  : Ԥ����״̬����ʼ��״̬�յ�AT��MN_CALL_APP_GET_ECONF_CALLED_INFO_REQ��Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��11��28��
   ��    ��   : j00174725
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppGetEconfInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �ϲ��������ѯ����״̬��������IMSAȥ��ѯ */
    (VOS_VOID)TAF_SPM_ProcReqMsgBasedOnCsOverIp(ulEventType, pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvImsaGetEconfInfoCnf_PreProc
 ��������  : SPM�յ�ID_IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF�Ĵ���
 �������  : ulEventType:�¼�����
             pstMsg     :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��28��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvImsaGetEconfInfoCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF_STRU   *pstImsaMsg  = VOS_NULL_PTR;

    pstImsaMsg = (IMSA_SPM_CALL_GET_ECONF_CALLED_INFO_CNF_STRU *)pstMsg;

    /* ��������Ϊ5�� */
    if (pstImsaMsg->ucNumOfCalls > TAF_CALL_MAX_ECONF_CALLED_NUM)
    {
        pstImsaMsg->ucNumOfCalls = TAF_CALL_MAX_ECONF_CALLED_NUM;
    }

    if (CALL_IMSA_GET_CALL_INFO_REQ_TYPE_CLCC == pstImsaMsg->enReqType)
    {
        /* ����������CLCC��ѯ������Ϣ,��AT�ظ� */
        TAF_SPM_SendAtGetEconfCallInfoCnf(pstImsaMsg);
    }

    return VOS_TRUE;
}

#endif

/* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-23, begin */
/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvCcSrvReqProtectTimerExpired_PreProc
 ��������  : �յ�CCҵ�񱣻���ʱ����ʱ�¼��Ĵ���, �յ�����Ϣʱ������CC���������
             ����Ϣ������ҵ������ʧ�ܸ���Ӧ��Ӧ��,�����CC��������е���Ϣ

 �������  : ulEventType  ��Ϣ�¼�����
             pstRcvMsg    ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvCcSrvReqProtectTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRst;

    /* ���������Ϣ */
    ulRst = TAF_SPM_ProcCcSrvReqProtectTimerExpired();

    return ulRst;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvSmsSrvReqProtectTimerExpired_PreProc
 ��������  : �յ�SMSҵ�񱣻���ʱ����ʱ�¼��Ĵ���, �յ�����Ϣʱ������CC���������
             ����Ϣ������ҵ������ʧ�ܸ���Ӧ��Ӧ��,�����SMS��������е���Ϣ

 �������  : ulEventType  ��Ϣ�¼�����
             pstRcvMsg    ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvSmsSrvReqProtectTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRst;

    /* ���������Ϣ */
    ulRst = TAF_SPM_ProcSmsSrvReqProtectTimerExpired(pstMsg);

    return ulRst;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvSsSrvReqProtectTimerExpired_PreProc
 ��������  : �յ�SSҵ�񱣻���ʱ����ʱ�¼��Ĵ���, �յ�����Ϣʱ������CC���������
             ����Ϣ������ҵ������ʧ�ܸ���Ӧ��Ӧ��,�����SS��������е���Ϣ

 �������  : ulEventType  ��Ϣ�¼�����
             pstRcvMsg    ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��23��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvSsSrvReqProtectTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRst;

    /* ���������Ϣ */
    ulRst = TAF_SPM_ProcSsSrvReqProtectTimerExpired();

    return ulRst;
}
/* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-23, end */

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvMmaPowerOffInd_PreProc
 ��������  : �յ�power offָʾ����Ϣ����

 �������  : ulEventType -- ��Ϣ�¼�����
             pstMsg -- ��Ϣָ��

 �������  : ��
 �� �� ֵ  : VOS_TRUE -- ��Ϣ�������
             VOS_FALSE -- ��Ϣδ�������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��10��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvMmaPowerOffInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

#if (FEATURE_ON == FEATURE_IMS)
    TAF_SPM_ProcMmaPowerOffInd();
#endif

    /* return VOS_FASLE�� APS also need this message */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvMmaSrvAcqCnf_PreProc
 ��������  : �յ�mma srv cnf��Ϣʱ�����������Ϣ
 �������  : ulEventType  ��Ϣ�¼�����
             pstRcvMsg    ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��19��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvMmaSrvAcqCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRst;
    TAF_MMA_SRV_ACQ_CNF_STRU           *pstSrvAcqCnf = VOS_NULL_PTR;
    TAF_SPM_CACHE_MSG_INFO_STRU        *pstCachedMsg = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstAppMsg    = VOS_NULL_PTR;
    MN_APP_MSG_SEND_REQ_STRU           *pstAppMsgSndReqMsg      = VOS_NULL_PTR;
    VOS_UINT8                           i;

    pstSrvAcqCnf = (TAF_MMA_SRV_ACQ_CNF_STRU *)pstMsg;

    /* ҵ�񴥷������ɹ��������� */
    if (TAF_MMA_SRV_ACQ_RESULT_SUCCESS == pstSrvAcqCnf->enResult)
    {
        /* ���������Ϣ */
        ulRst = TAF_SPM_ProcBufferedMsgInQueue();

        return ulRst;
    }

    /* �������ʧ�ܣ�������cc��ҵ��ظ�ʧ�ܣ�ֹͣCC���涨ʱ�� */
    if (0 != TAF_SPM_GetCcMsgQueueNum())
    {
        /* get first index message address */
        pstCachedMsg = TAF_SPM_GetSpecifiedIndexMessageAddrFromCcQueue(0);
        pstAppMsg    = (MN_APP_REQ_MSG_STRU *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]);

        /* indicate sender that CC service request is failure */
        TAF_SPM_SendCcServiceRequetFail(pstCachedMsg->stMsgEntry.ulEventType,
                                        (struct MsgCB *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]),
                                        TAF_CS_CAUSE_NO_RF);


        TAF_SPM_StopTimer(TI_TAF_SPM_CC_SRV_REQ_PROTECT_TIMER, pstAppMsg->clientId);

        /* clear the first cached message in queue */
        TAF_SPM_FreeSpecificedIndexMessageInCcQueue(0);

        /* log service domain selection infomation */
        TAF_SPM_LogSrvDomainSelQueueInfo();
    }

    /* �������ʧ�ܣ�������ss��ҵ��ظ�ʧ�ܣ�ֹͣss���涨ʱ�� */
    if (0 != TAF_SPM_GetSsMsgQueueNum())
    {
        pstCachedMsg = TAF_SPM_GetSpecifiedIndexMessageAddrFromSsQueue(0);
        pstAppMsg    = (MN_APP_REQ_MSG_STRU *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]);

        TAF_SPM_SendSsServiceRequetFail(pstCachedMsg->stMsgEntry.ulEventType,
                                        (struct MsgCB *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[0]),
                                        TAF_CS_CAUSE_NO_RF);

        TAF_SPM_StopTimer(TI_TAF_SPM_SS_SRV_REQ_PROTECT_TIMER, pstAppMsg->clientId);

        /* clear the first cached message in queue */
        TAF_SPM_FreeSpecificedIndexMessageInSsQueue(0);

        /* log service domain selection infomation */
        TAF_SPM_LogSrvDomainSelQueueInfo();
    }

    /* �������ʧ�ܣ�������sms��ҵ��ظ�ʧ�ܣ�ֹͣsms���涨ʱ�� */
    for (i = 0; i < TAF_SPM_GetSmsMsgQueueNum(); i++)
    {
        pstCachedMsg = TAF_SPM_GetSpecifiedIndexMessageAddrFromSmsQueue(i);

        pstAppMsgSndReqMsg   = (MN_APP_MSG_SEND_REQ_STRU *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[i]);
        ulEventType = pstCachedMsg->stMsgEntry.ulEventType;

        /* ����client ID���һ�����Ϣ, SMMA��Ϣ������ѡ��ʱ������˲�care */
        if (TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_SPM_SMMA_IND) != ulEventType)
        {
            /* send fail indication to user */
            TAF_SPM_SendSmsServiceRequetFail(pstCachedMsg->stMsgEntry.ulEventType,
                                             (struct MsgCB *)&(pstCachedMsg->stMsgEntry.aucEntryMsgBuffer[i]),
                                             TAF_CS_CAUSE_NO_RF);

            TAF_SPM_StopTimer(TI_TAF_SPM_SMS_SRV_REQ_PROTECT_TIMER, pstAppMsgSndReqMsg->usClientId);

            /* clear the first cached message in queue */
            TAF_SPM_FreeSpecificedIndexMessageInSmsQueue(i);

            /* log service domain selection infomation */
            TAF_SPM_LogSrvDomainSelQueueInfo();
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_IsSsServiceReqAllowed_PreProc
 ��������  : �ж�SSҵ���Ƿ�������

 �������  : ulEventType -- ��Ϣ�¼�����
             pstMsg -- ��Ϣָ��

 �������  : penCause -- ҵ����ʧ��ԭ��ֵ
 �� �� ֵ  : VOS_TRUE -- ������SSҵ��
             VOS_FALSE-- ��������SSҵ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��30��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_SPM_IsSsServiceReqAllowed_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_ERROR_CODE_ENUM_UINT32         *penCause
)
{
    VOS_UINT32                          ulIsUsimValid;

    *penCause   = TAF_ERR_NO_ERROR;

    ulIsUsimValid   = TAF_SDC_IsUsimStausValid();

    /* SS is allowed if phone mode is power on */
    if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        *penCause   = TAF_ERR_SS_POWER_OFF;
        return VOS_FALSE;
    }

    /* forbid SS when USIM service is not available */
    /* ��Ҫ�ж���������Ч,��Ϊ������Ч������ܻ�disable LTE��GU��,��Ҫ��GU�¼������� */
    if ( (VOS_FALSE == TAF_SPM_IsUsimServiceAvailable())
      || (VOS_FALSE == ulIsUsimValid) )
    {
        *penCause   = TAF_ERR_USIM_SIM_INVALIDATION;
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_IsSmsServiceReqAllowed_PreProc
 ��������  : �ж�SMSҵ���Ƿ�������

 �������  : ulEventType -- ��Ϣ�¼�����
             pstMsg -- ��Ϣָ��

 �������  : penCause -- ҵ����ʧ��ԭ��ֵ
 �� �� ֵ  : VOS_TRUE -- ������SMSҵ��
             VOS_FALSE-- ��������SMSҵ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��30��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_SPM_IsSmsServiceReqAllowed_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    VOS_UINT32                         *pulCause
)
{
    *pulCause   = MN_ERR_NO_ERROR;

    /* SMS is allowed if phone mode is power on */
    if (TAF_PH_MODE_FULL != TAF_SDC_GetCurPhoneMode())
    {
        *pulCause    = MN_ERR_CLASS_SMS_POWER_OFF;
        return VOS_FALSE;
    }

    /* forbid SMS when USIM service is not available */
    if (VOS_FALSE == TAF_SPM_IsUsimServiceAvailable())
    {
        *pulCause    = MN_ERR_CLASS_SMS_NOUSIM;
        return VOS_FALSE;
    }

    /* �ж���������Чʱ��ֱ�Ӹ�AT�ظ�ʧ�� */
    if (VOS_FALSE == TAF_SDC_IsUsimStausValid())
    {
        *pulCause    = MN_ERR_CLASS_SMS_UNAVAILABLE;
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*lint -restore */



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


