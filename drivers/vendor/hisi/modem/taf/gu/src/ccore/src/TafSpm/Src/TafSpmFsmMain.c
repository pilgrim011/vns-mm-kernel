/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafSpmFsmMain.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2013��5��8��
  ����޸�   :
  ��������   : TafSpmFsmMain.C�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��5��7��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "AtMnInterface.h"
#include "TafTypeDef.h"
#include "TafSpmCtx.h"
#include "TafSpmFsmMain.h"
#include "TafSpmFsmMainTbl.h"
#include "SsInclude.h"
#include "TafSpmFsmServiceCtrlTbl.h"
#include "TafSpmSndInternalMsg.h"
#include "MnErrorCode.h"
#include "TafLog.h"
#include "AtMnInterface.h"

/* Modified by z00161729 for V9R1 STK����, 2013-7-24, begin */
#include "NasStkInterface.h"
/* Modified by z00161729 for V9R1 STK����, 2013-7-24, end */
/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
#include "MnCallMnccProc.h"
/* Deleted by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-18, begin */
/* Deleted by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-18, end */
#include "TafSpmServiceDomainSelProc.h"
#include "TafSdcLib.h"
#include "MnCallApi.h"
/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-18, begin */
#include "TafAgentInterface.h"
/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-18, end */

#include "TafSpmRedial.h"
#include "TafSpmComFunc.h"
#include "TafSpmServiceDomainSelProc.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_FSM_MAIN_C

/*lint -save -e958 */

/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-31, begin */
/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvAtSSReqMsg_Main
 ��������  : MAIN״̬����ʼ��״̬�յ�AT��ע��SSҵ�����Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��7��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��07��23��
   ��    ��   : y00245242
   �޸�����   : VOLTE����, ��main״̬�µ�FDN��call control����Ƶ�service״̬
                ���¿���
 3.��    ��   : 2013��12��30��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseIII��Ŀ
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvAppReqMsg_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           ucIdleFsmIndex;

    (VOS_VOID)TAF_SPM_GetClientIdWithAppMsg(pstMsg, &usClientId);
    TAF_SPM_GetOpIdWithAppMsg(pstMsg, &ucOpId);

    /* �ж��Ƿ��д��ڿ���״̬�� */
    ucIdleFsmIndex = TAF_SPM_GetIdleEntityFsmIndex();

    if (TAF_SPM_INVALID_CLIENT_ID_ENTITY_FSM_INDEX == ucIdleFsmIndex)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_SPM_RcvAppReqMsg_Main():WARNING: No Idle Entiy Fsm Exist!");
        /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-30, begin */
        /* ��ʱ��Ӧ��Ϊ��ʽ��Ӧ */
        TAF_SPM_SendServiceRequetFail_Main(ulEventType, pstMsg, MN_ERR_CLASS_SPM_BEYOND_CONCURRENCY_CAPABILITY);
        /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-30, end */

#if (FEATURE_ON == FEATURE_IMS)
        TAF_SPM_SetEconfPreRslt(TAF_CS_CAUSE_UNKNOWN);

        TAF_SPM_ReportEconfCheckRslt();
#endif
    }
    else
    {
        /* ���õ�ǰ״̬�������� */
        TAF_SPM_SetCurrEntityFsmAddr(ucIdleFsmIndex);

        /* ���õ�ǰclient IDʵ��״̬����client ID */
        TAF_SPM_SetCurrEntityFsmClientId(usClientId);

        /* ����service ctrl״̬��,����fdn&CALL control��� */
        TAF_SPM_FSM_InitEntityFsm(TAF_SPM_FSM_SERVICE_CTRL,
                                      TAF_SPM_GetServiceCtrlFsmDescAddr(),
                                      TAF_SPM_SERVICE_CTRL_STA_INIT);
    }

    return VOS_TRUE;
}
/* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-31, end */

/*****************************************************************************
 �� �� ��  : TAF_SPM_RcvSpmServiceCtrlResultInd_Main
 ��������  : MAIN״̬����ʼ��״̬�յ�TAF_SPM_INTERNAL_SERVICE_CTRL_RESULT_IND����Ϣ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                        *pMsg
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��7��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��07��30��
   ��    ��   : y00245242
   �޸�����   : VOLTE����, ����IMS��ѡ����
 3.��    ��   : 2013��12��30��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseIII��Ŀ
*****************************************************************************/
VOS_UINT32 TAF_SPM_RcvSpmServiceCtrlResultInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_SERVICE_CTRL_RSLT_STRU                         *pstServiceCtrlRslt = VOS_NULL_PTR;
    VOS_UINT8                                               ucOpId;
    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-23, begin */
    VOS_UINT32                                              ulRet;
    VOS_UINT32                                              ulAppEventType;
    struct MsgCB                                           *pstAppMsg          = VOS_NULL_PTR;
    TAF_SPM_DOMAIN_SEL_RESULT_ENUM_UINT8                    enDomainSelRslt;

    ulRet   = VOS_TRUE;
    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-23, end */

    pstServiceCtrlRslt = (TAF_SPM_SERVICE_CTRL_RSLT_STRU*)pstMsg;

    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-30, begin */
    TAF_SPM_GetOpIdWithAppMsg((struct MsgCB*)pstServiceCtrlRslt->stEntryMsg.aucEntryMsgBuffer, &ucOpId);

    pstAppMsg      = (struct MsgCB*)&(pstServiceCtrlRslt->stEntryMsg.aucEntryMsgBuffer[0]);
    ulAppEventType = pstServiceCtrlRslt->stEntryMsg.ulEventType;

    /* �����Ϊʧ�� */
    if (TAF_SPM_SERVICE_CTRL_FAIL == pstServiceCtrlRslt->enResult)
    {
        /* ��AT��STK����ʧ�ܽ��,Я��cause,��ʱ��Ӧ�޸�Ϊ��ʽ��Ӧ */
        TAF_SPM_SendServiceRequetFail_Main(ulAppEventType, pstAppMsg, pstServiceCtrlRslt->ulCause);

        return VOS_TRUE;
    }
    /* Modified by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-30, end */

    enDomainSelRslt = TAF_SPM_ProcServiceRequestDomainSelection(ulAppEventType, pstAppMsg);

    ulRet           = TAF_SPM_ProcInitialDomainSelectionResult(ulAppEventType, pstAppMsg, enDomainSelRslt);

    if (VOS_TRUE == ulRet)
    {
        return VOS_TRUE;
    }

    /* �����Ϊ�ɹ����ø��������Ϣ��ǲ������޸ĺ�������Ϣ��ȫ�ֱ����� */
    TAF_SPM_UpdateServiceCtrlEntryMsg(ulAppEventType, pstAppMsg);

    TAF_SPM_SetUpdateEntryMsgFlg(VOS_TRUE);

    return VOS_FALSE;
}

/* ɾ�� */


/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-14, begin */
/* ��IMSA��Ϣ�Ĵ���ŵ�Ԥ������ʵ�� */
/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-14, end */


/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-30, begin */
/*****************************************************************************
 �� �� ��  : TAF_SPM_SendServiceRequetFail_Main
 ��������  : ����ҵ�����͸�AT/STK�ظ�ʧ��

 �������  : ulEventType -- ��Ϣ�¼�����
             pstMsg      -- ��Ϣָ��
             ulCause     -- ʧ��ԭ��ֵ

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��31��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SPM_SendServiceRequetFail_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    VOS_UINT32                          ulCause
)
{
    TAF_SPM_SRV_REQ_TYPE_ENUM_UINT8     enSrvReqType;

    enSrvReqType = TAF_SPM_GetServiceRequestType(pstMsg);

    switch (enSrvReqType)
    {
        case TAF_SPM_SRV_REQ_TYPE_CALL:
            TAF_SPM_SendCcServiceRequetFail(ulEventType, pstMsg, ulCause);
            break;

        case TAF_SPM_SRV_REQ_TYPE_SMS:
            TAF_SPM_SendSmsServiceRequetFail(ulEventType, pstMsg, ulCause);
            break;

        case TAF_SPM_SRV_REQ_TYPE_SS:
            TAF_SPM_SendSsServiceRequetFail(ulEventType, pstMsg, (TAF_SS_ERROR)ulCause);
            break;

        default:
            break;

    }

    return;
}

/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-30, end */

/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

