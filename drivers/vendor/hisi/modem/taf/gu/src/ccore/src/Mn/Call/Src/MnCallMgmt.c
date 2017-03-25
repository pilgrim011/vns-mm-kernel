/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MNCallMgmt.c
  �� �� ��   : ����
  ��    ��   : ���� 49431
  ��������   : 2007��9��20��
  ����޸�   : 2007��9��20��
  ��������   : ʵ�ֺ��еĹ���, ����������Ϣ����, ����ҵ����������DTMF���̹���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ļ�
  2.��    ��   : 2008��7��12��
    ��    ��   : ���� 44270
    �޸�����   : ���ⵥ��:AT2D04057

  3.��    ��   : 2010��3��2��
    ��    ��   : zhoujun /z40661
    �޸�����   : NAS R7Э������

  4.��    ��   : 2010��7��27��
    ��    ��   : zhoujun /40661
    �޸�����   : ֧��UUS1
******************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafTypeDef.h"

#include "MnCallApi.h"

#include "MnComm.h"
#include "MnCallReqProc.h"
#include "MnCallSendCc.h"
#include "UsimPsInterface.h"
#include "MnCallFacilityEncode.h"
#include "NVIM_Interface.h"
#include "NasOmInterface.h"

#include "MnErrorCode.h"
#include "MnCall.h"
/* Added by w00199382 for PS Project��2011-12-06,  Begin*/
#include "AtTafAgentInterface.h"
/* Added by w00199382 for PS Project��2011-12-06,  End*/
#include "MnCallProcNvim.h"
#include "MnCallMgmt.h"
#include "MnComm.h"

/* Modified by z00161729 for V9R1 STK����, 2013-7-24, begin */
#include "NasStkInterface.h"
/* Modified by z00161729 for V9R1 STK����, 2013-7-24, end */

#include "NasIeUtil.h"

#include "MnCallTimer.h"

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, begin */
#include "TafSdcLib.h"
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, end */

#include "NasUsimmApi.h"

/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-25, begin */
#if (FEATURE_ON == FEATURE_IMS)
#include "SpmImsaInterface.h"
#include "CallImsaInterface.h"
#endif
/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-25, end */

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-18, begin */
#include "MnCallSendApp.h"
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-18, end */

#include "RabmTafInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_MGMT_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

/*****************************************************************************
   2 �ڲ��������Ͷ���
*****************************************************************************/

/*****************************************************************************
   3 ȫ�ֱ����;�̬��������
*****************************************************************************/
/* ���й���ʵ�� */
/* Deleted by l00198894 for V9R1 STK����, 2013/07/11 */
LOCAL MN_CALL_MGMT_STRU                     f_astCallMgmtEntities[MN_CALL_MAX_NUM];

/* Added by l00198894 for V9R1 STK����, 2013/07/11, begin */
/* CALLģ��DTMF״̬��������Ϣ */
LOCAL TAF_CALL_DTMF_CTX_STRU                f_stCallDtmfCtx;
/* Added by l00198894 for V9R1 STK����, 2013/07/11, end */

LOCAL VOS_BOOL                              f_abCallReleaseFlag[MN_CALL_MAX_NUM];

/* ����ҵ��������� */
LOCAL MN_CALL_SUPS_CMD_ENUM_U8_MGMT_STRU    f_stCallSupsCmdMgmt;

/*CCBS���ܴ�ʱ,������Setup��Ϣ */
LOCAL NAS_CC_MSG_SETUP_MO_STRU              f_stCcbsSetup;

/* ����CallId�����Ǵ�1��ʼ�ģ��ʸñ���Ҳ��1��ʼ */
/* ���мƷ������Ϣ */
LOCAL MN_CALL_TIMER_CALC_ST            gastCallTimerCalc[CALL_MAX_ENT_NUM + 1];

/*ALS���ܴ�ʱ,��������·�� */
LOCAL MN_CALL_ALS_LINE_NO_ENUM_U8           f_enAlsLineNo = MN_CALL_ALS_LINE_NO_1;

LOCAL MN_CALL_MATCH_MSG_TYPE_STRU           f_stCallMsgType[] =
{
    {MN_CALL_UUS1_MSG_SETUP             ,NAS_CC_MSG_SETUP},
    {MN_CALL_UUS1_MSG_ALERT             ,NAS_CC_MSG_ALERTING},
    {MN_CALL_UUS1_MSG_CONNECT           ,NAS_CC_MSG_CONNECT},
    {MN_CALL_UUS1_MSG_DISCONNECT        ,NAS_CC_MSG_DISCONNECT},
    {MN_CALL_UUS1_MSG_RELEASE           ,NAS_CC_MSG_RELEASE},
    {MN_CALL_UUS1_MSG_RELEASE_COMPLETE  ,NAS_CC_MSG_RELEASE_COMPLETE},
    {MN_CALL_UUS1_MSG_PROGRESS          ,NAS_CC_MSG_PROGRESS}
};


extern    VOS_VOID MN_CALL_SetTchStatus(
    VOS_BOOL                            bAvailable
);


/*lint -save -e958 */


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/

/* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
/*****************************************************************************
 �� �� ��  : TAF_CALL_DeRegRelCallSsKeyEvent
 ��������  : ɾ������ҵ������Ĺ�ע�¼�
 �������  : callId     - ��ʶ�����¼��ĺ���
             enEvt      - ����Ҫ��ע���¼�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  2.��    ��   : 2014��5��8��
    ��    ��   : z00161729
    �޸�����   : DTS2014051404686:һ·activeͨ��һ·holdͨ����at+chld=2,�����緢��hold req
	           ��retrieve req�󣬹Ҷ�active�绰������ָ�retrieve rej��call״̬�쳣����
			   ����Ӧat+chld=2,�����޷��ָ�
  3.��    ��   : 2014��6��17��
    ��    ��   : z00234330
    �޸�����   : TQE����
*****************************************************************************/
VOS_VOID  TAF_CALL_DeRegRelCallSsKeyEvent(
    MN_CALL_ID_T                        callId
)
{

    VOS_UINT8                           ucNumOfKeyEvt;
    VOS_UINT16                          ulLoop;

    /* ɾ����Ӧ��ע���¼� */
    /* Modified by z00234330 for coverity����, 2014-06-16, begin */
    ucNumOfKeyEvt = TAF_SDC_MIN(f_stCallSupsCmdMgmt.ucNumOfKeyEvt, (MN_CALL_MAX_SS_CMD_KEY_EVT_NUM-1));
    /* Modified by z00234330 for coverity����, 2014-06-16, end */

    for (ulLoop = 0; ulLoop < ucNumOfKeyEvt;)
    {
        if (callId == f_stCallSupsCmdMgmt.astKeyEvts[ulLoop].callId)
        {
            PS_MEM_CPY(&f_stCallSupsCmdMgmt.astKeyEvts[ulLoop],
                &f_stCallSupsCmdMgmt.astKeyEvts[ulLoop + 1],
                ((ucNumOfKeyEvt - ulLoop) - 1) * sizeof(MN_CALL_SUPS_CMD_ENUM_U8_KEY_EVT_STRU));

            f_stCallSupsCmdMgmt.ucNumOfKeyEvt--;
            ucNumOfKeyEvt--;
            PS_MEM_SET(&f_stCallSupsCmdMgmt.astKeyEvts[ucNumOfKeyEvt], 0, sizeof(MN_CALL_SUPS_CMD_ENUM_U8_KEY_EVT_STRU));
        }
        else
        {
            ulLoop++;
        }
    }

}

/*****************************************************************************
 �� �� ��  : TAF_CALL_CountMptyCallNum
 ��������  : ����෽ͨ��������CALL ID����
 �������  : ��
 �������  : ��
 �� �� ֵ  : �෽ͨ��������CALL ID����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  2.��    ��   : 2013��8��19��
    ��    ��   : f62575
    �޸�����   : DTS2013071808373��coverity������
*****************************************************************************/
VOS_UINT32 TAF_CALL_CountMptyCallNum(VOS_VOID)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMptyCallNum;
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;

    ulMptyCallNum = 0;

    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    for (ulLoop = 0; ulLoop < MN_CALL_MAX_NUM; ulLoop++)
    {
        MN_CALL_GetCallState((VOS_UINT8)(ulLoop + 1), &enCallState, &enMptyState);
        if (MN_CALL_IN_MPTY == enMptyState)
        {
            ulMptyCallNum++;
        }
    }

    return ulMptyCallNum;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetFirstMptyCallID
 ��������  : ��ȡ���˵�ǰcall id�����һ���෽ͨ����call id
 �������  : callId - ��ǰ����id
 �������  : ��
 �� �� ֵ  : ��һ���෽ͨ����call id
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��31��
    ��    ��   : z00161729
    �޸�����   : ��������
*****************************************************************************/
VOS_UINT8 TAF_CALL_GetFirstMptyCallID(MN_CALL_ID_T  callId)
{
    VOS_UINT8                           ucLoop;
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    for (ucLoop = 0; ucLoop < MN_CALL_MAX_NUM; ucLoop++)
    {
        if ((ucLoop + 1) == callId)
        {
            continue;
        }

        MN_CALL_GetCallState((ucLoop + 1), &enCallState, &enMptyState);
        if (MN_CALL_IN_MPTY == enMptyState)
        {
            return (VOS_UINT8)(ucLoop + 1);
        }
    }

    return MN_CALL_MAX_NUM;
}


/*****************************************************************************
 �� �� ��  : TAF_CALL_SetCsCallExistFlg
 ��������  : ���õ�ǰ�Ƿ���CS CALL �ͽ��������
 �������  : ucCallExitFlg - �Ƿ���call
             enCallType    - call type
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��10��9��
   ��    ��   : c00318887
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID    TAF_CALL_SetCsCallExistFlg(
    VOS_UINT8                           ucCallExitFlg,
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    /* �޵绰���϶��޽����� */
    if (VOS_FALSE == ucCallExitFlg)
    {
        TAF_SDC_SetCsCallExistFlg(VOS_FALSE);
        TAF_SDC_SetCsEccExistFlg(VOS_FALSE);
        return;
    }

    /* �е绰������call type���ý�������� */
    TAF_SDC_SetCsCallExistFlg(VOS_TRUE);
    
    if (MN_CALL_TYPE_EMERGENCY == enCallType)
    {
        TAF_SDC_SetCsEccExistFlg(VOS_TRUE);
    }
    else
    {
        TAF_SDC_SetCsEccExistFlg(VOS_FALSE);
    }
    
    return;
}


/*****************************************************************************
 �� �� ��  : TAF_CALL_ProcRelCallHoldRetrieveSsKeyEvent
 ��������  : ɾ���ͷź��еĲ���ҵ������Ĺ�ע�¼�
 �������  : callId     - ��ʶ�����¼��ĺ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  2.��    ��   : 2013��8��19��
    ��    ��   : f62575
    �޸�����   : DTS2013071808373��coverity������
  3.��    ��   : 2013��11��04��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseII��Ŀ
  4.��    ��   : 2014��5��31��
    ��    ��   : z00161729
    �޸�����   : DTS2014060402388:һ·active���У�һ·hold��mpty���У�at+chld=1�����ж������к��ж����ͷź�call״̬�쳣������hold mpty�����޷��ָ�
*****************************************************************************/
VOS_VOID TAF_CALL_ProcRelCallHoldRetrieveSsKeyEvent(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvt
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;

    VOS_UINT8                           ucFirstMptyCallId;

    /* ��ȡ�ͷź��еĶ෽�������ԣ��Ƕ෽ͨ��CALL ID��ֱ���ͷź��й������¼� */
    enMptyState = MN_CALL_MPYT_STATE_BUTT;
    MN_CALL_GetCallState(callId, &enCallState, &enMptyState);
    if (MN_CALL_IN_MPTY != enMptyState)
    {
        TAF_CALL_DeRegRelCallSsKeyEvent(callId);
    }
    else
    {
        TAF_CALL_DeRegRelCallSsKeyEvent(callId);

        ucFirstMptyCallId = TAF_CALL_GetFirstMptyCallID(callId);

        if (MN_CALL_MAX_NUM != ucFirstMptyCallId)
        {
            if (MN_CALL_SS_PROG_EVT_HOLD_CNF == enEvt)
            {
                MN_CALL_RegSsKeyEvent(ucFirstMptyCallId,
                                      MN_CALL_SS_PROG_EVT_HOLD_CNF,
                                      MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

                MN_CALL_RegSsKeyEvent(ucFirstMptyCallId,
                                  MN_CALL_SS_PROG_EVT_HOLD_REJ,
                                  MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

            }
            else
            {
                MN_CALL_RegSsKeyEvent(ucFirstMptyCallId,
                                      MN_CALL_SS_PROG_EVT_RETRIEVE_CNF,
                                      MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

                MN_CALL_RegSsKeyEvent(ucFirstMptyCallId,
                                  MN_CALL_SS_PROG_EVT_RETRIEVE_REJ,
                                  MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);
            }
        }
    }

    if (0 == f_stCallSupsCmdMgmt.ucNumOfKeyEvt)
    {
        f_stCallSupsCmdMgmt.bInProgress = VOS_FALSE;
        f_astCallMgmtEntities[callId - 1].stCallInfo.enSsResult = MN_CALL_SS_RES_SUCCESS;
        /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, begin */
        MN_CALL_ReportEvent(callId, MN_CALL_EVT_SS_CMD_RSLT);
        /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, end */

        MN_CALL_ClearSsKeyEvent();
    }

    return;
}

/* Added by f62575 for V9R1 STK����, 2013-6-26, end */

/* ������3��������MnCallMnccProc.c����ֲ���˴� */
/*****************************************************************************
 �� �� ��  : MN_CALL_CleanStartLinkTime
 ��������  : ��ָ��CALL ID����Ӧ��ͳ��ʱ��ṹ��Ŀ�ʼ����ʱ���ֶ�����
 �������  : VOS_UINT8 ucCallId
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009-09-01
    ��    ��   : s62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��05��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ
  3.��    ��   : 2013��11��21��
    ��    ��   : j00174725
    �޸�����   : ROTS �޸�
*****************************************************************************/
VOS_VOID MN_CALL_CleanStartLinkTime( VOS_UINT8 ucCallId)
{
    /*�����������:*/
    gastCallTimerCalc[ucCallId].ulStartCallTime = 0;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_StartFluxCalculate
 ��������  : ��ʼͳ��ͨ��ʱ��
 �������  : VOS_UINT8 ucCallId
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009-09-01
    ��    ��   : s62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��05��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ
  3.��    ��   : 2013��11��21��
    ��    ��   : j00174725
    �޸�����   : ROTS �޸�
*****************************************************************************/
VOS_VOID  MN_CALL_StartFluxCalculate( VOS_UINT8 ucCallId)
{

    /*��ȡ��ǰϵͳʱ�䲢���ýṹ���еĵ�ǰ���ӿ�ʼʱ����Ϊ��ǰϵͳʱ��:*/
    gastCallTimerCalc[ucCallId].ulStartCallTime = VOS_GetTick() / PRE_SECOND_TO_TICK ;

    /*��λ��NSAPI����Ӧ�������ṹ���NSAPI�����־:*/
    gastCallTimerCalc[ucCallId].CallidActiveSwitch = MN_CALL_ACTIVE_SWITCH_ON;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_StopFluxCalculate
 ��������  : ֹͣͳ��ͨ��ʱ��
 �������  : VOS_UINT8 ucCallId
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009-09-01
    ��    ��   : s62952
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��05��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ
  3.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  4.��    ��   : 2013��11��21��
    ��    ��   : j00174725
    �޸�����   : ROTS �޸�
*****************************************************************************/
VOS_VOID  MN_CALL_StopFluxCalculate( VOS_UINT8 ucCallId)
{
    VOS_UINT32                      	ulCurCallTime = 0;
    VOS_UINT32                          ulCurSysTime;               /*���ڱ��浱ǰϵͳʱ��ı���*/
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    ulCurSysTime = 0;

    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    if (gastCallTimerCalc[ucCallId].CallidActiveSwitch == MN_CALL_ACTIVE_SWITCH_OFF )
    {
         return;
    }

    /*��λ��CALL ID����Ӧ�������ṹ���CALL ID�����־:*/
    gastCallTimerCalc[ucCallId].CallidActiveSwitch   = MN_CALL_ACTIVE_SWITCH_OFF;

    /*��ȡ��ǰϵͳʱ��:*/
    ulCurSysTime = VOS_GetTick() / PRE_SECOND_TO_TICK;


    MN_CALL_GetCallState(ucCallId, &enCallState, &enMptyState);
    /*����״̬Ϊactive��held�����������ʱ��*/
    if ((MN_CALL_S_ACTIVE == enCallState) || (MN_CALL_S_HELD == enCallState))
    {
        /*��ṹ���п�ʼ����ʱ�����㣬�õ�����������ʱ��:*/
        if ( VOS_OK != TAF_CalcTime(gastCallTimerCalc[ucCallId].ulStartCallTime,
                                    ulCurSysTime,
                                    &ulCurCallTime ) )
        {
             MN_WARN_LOG( "MN_CALL_StopFluxCalculate:WARNING:Calculate the last  link time FAIL!");
        }
        else
        {
            /*������������ʱ�丳��"�ϴ�����ʱ��"�ֶ�:*/
            gastCallTimerCalc[ucCallId].ulPreCallTime = ulCurCallTime;
            /*������������ʱ���ۼ���"�ۼ�����ʱ��"�ֶ�:*/
            gastCallTimerCalc[ucCallId].ulTotalCallTime  += ulCurCallTime;
        }
    }
    else
    {
    }

    f_astCallMgmtEntities[ucCallId-1].stCallInfo.ulPreCallTime = gastCallTimerCalc[ucCallId].ulPreCallTime;
    f_astCallMgmtEntities[ucCallId-1].stCallInfo.ulTotalCallTime = gastCallTimerCalc[ucCallId].ulTotalCallTime;

    /*��"��ʼ����ʱ��"�ֶ�����:*/
    gastCallTimerCalc[ucCallId].ulPreCallTime = 0;
    MN_CALL_CleanStartLinkTime( ucCallId );

}

/*****************************************************************************
 �� �� ��  : MN_CALL_ResetAllCalls
 ��������  : ��λ���к���, �����п�����Ϣ��Ϊ��ʼ״̬
 �������  : enPowerState - ������ػ�̬��λ���к���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��3��1��
    ��    ��   : zhoujun /z40661
    �޸�����   : ��ػ�ʱ�ͷ�Invoke Id
  3.��    ��   : 2010��4��20��
    ��    ��   : z00161729
    �޸�����   : ���ⵥ:AT2D18405��ػ�������ں�����Ҫ�ϱ��ͷ��¼�
  4.��    ��   : 2011��10��15��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ
  5.��    ��   : 2012��03��02��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ��:DTS2012020206417��ʹ��ATD117;����绰��һ��ʱ���Ҷϵ绰��
                 ���������ϱ���CEND�У�ͨ��ʱ����ʾΪ0

  6.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  7.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  8.��    ��   : 2012��11��19��
    ��    ��   : Y00213812
    �޸�����   : DTS2012111401720,��ǰ����з�IDLE̬�ĺ���ʵ�壬���ϱ�367ԭ��ֵ
  9.��    ��   : 2013��01��18��
    ��    ��   : Y00213812
    �޸�����   : DTS2013011201560�޸Ĵ���ԭ��ֵ�ϱ�
 10.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ��SS FDN&Call Control�ƶ���TAF
 11.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ����ػ�ʱ����DTMF״̬������
 12.��    ��   : 2013��11��04��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseII��Ŀ
 13.��    ��   : 2014��03��01��
    ��    ��   : s00217060
    �޸�����   : CS��ҵ��״̬�仯ʱ֪ͨMTC
 14.��    ��   : 2014��4��15��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature�޸�
 15.��    ��   :2014��9��28��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
 16.��    ��   : 2015��10��10��
    ��    ��   : c00318887
    �޸�����   : DTS2015090607329
*****************************************************************************/
VOS_VOID   MN_CALL_ResetAllCalls(MN_CALL_POWER_STATE_ENUM_U8 enPowerState)
{
    VOS_UINT32                          i;

    MN_CALL_MSG_BUFF_STRU              *pstMsgBuff = VOS_NULL_PTR;
    TAF_CS_CAUSE_ENUM_UINT32            enCause;

    pstMsgBuff = MN_CALL_GetBufferedMsg();

    if (MN_CALL_POWER_STATE_OFF == enPowerState)
    {
        /*��ػ�ʱ��Ҫ�жϵ�ǰ�Ƿ��з�IDLE̬�ĺ��У��������Ҫ�ϱ�MN_CALL_EVT_RELEASED�¼�*/
        for (i = 0; i < MN_CALL_MAX_NUM; i++)
        {
            if (f_astCallMgmtEntities[i].stCallInfo.enCallState != MN_CALL_S_IDLE)
            {

                /*��causeֵ127*/
                MN_CALL_UpdateCcCause((VOS_UINT8)(i + 1), MN_CALL_INTERWORKING_UNSPECIFIED);

                MN_INFO_LOG1("MN_CALL_ResetAllCalls: callid.", f_astCallMgmtEntities[i].stCallInfo.callId);

                /* ��Ҫ��ͳ��ͨ��ʱ�䣬���ϱ�RELEASED�¼� */
                /* ֹͣͳ��ͨ��ʱ�� */
                MN_CALL_StopFluxCalculate(f_astCallMgmtEntities[i].stCallInfo.callId);

                MN_CALL_ReportEvent(f_astCallMgmtEntities[i].stCallInfo.callId,
                                    MN_CALL_EVT_RELEASED);

                TAF_CALL_ProcCallStatusFail(f_astCallMgmtEntities[i].stCallInfo.callId, f_astCallMgmtEntities[i].stCallInfo.enCallState);

                if ((VOS_TRUE == pstMsgBuff->bitOpBufferedSetupMsg)
                 && (pstMsgBuff->stBufferedSetupMsg.ucCallId == f_astCallMgmtEntities[i].stCallInfo.callId))
                {
                    MN_CALL_ClearBufferedMsg();
                    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */
                    TAF_CALL_StopAllRedialTimers(pstMsgBuff->stBufferedSetupMsg.ucCallId);
                    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-8, end */
                }

#if (FEATURE_ON == FEATURE_PTM)
                /* ��¼CS�����쳣log */
                MN_CALL_CsCallErrRecord(f_astCallMgmtEntities[i].stCallInfo.callId, TAF_CS_CAUSE_POWER_OFF);
#endif

                /* �绰�Ҷ�ʱ������Ӧ���¼������������������ǿ�ָ�룬���ĸ�����������0�������¼�������ȥ */
                enCause = TAF_CS_CAUSE_POWER_OFF;

                if(MN_CALL_DIR_MO == f_astCallMgmtEntities[i].stCallInfo.enCallDir)
                {
                    NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_CC_MO_DISCONNECT,
                                    &enCause, sizeof(TAF_CS_CAUSE_ENUM_UINT32));
                }
                else
                {
                    NAS_EventReport(WUEPS_PID_TAF, NAS_OM_EVENT_CC_MT_DISCONNECT,
                                    &enCause, sizeof(TAF_CS_CAUSE_ENUM_UINT32));
                }
            }
        }

        /*��f_stWaitSendAlertȫ�ֱ���*/
        MN_CALL_SetWaitSendAlertStatus(VOS_FALSE, 0);

        /* ���к��ж�RELEASED���ϱ����к��ж���RELEASED */
        MN_CALL_ReportEvent(f_astCallMgmtEntities[0].stCallInfo.callId,
                            MN_CALL_EVT_ALL_RELEASED);
        /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, begin */
        
        TAF_CALL_SetCsCallExistFlg(VOS_FALSE, MN_CALL_TYPE_BUTT);
        
        /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, end */

        /* Added by s00217060 for CS��ҵ��״̬�仯ʱ֪ͨMTC, 2014/03/01, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* ��MTCģ���ϱ���ǰCS��ҵ��״̬ */
        TAF_SendMtcCsSrvInfoInd();
#endif
        /* Added by s00217060 for CS��ҵ��״̬�仯ʱ֪ͨMTC, 2014/03/01, end */

        /* Added by l00198894 for V9R1 STK����, 2013/07/11, begin */
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_POWER_OFF);
        /* Added by l00198894 for V9R1 STK����, 2013/07/11, end */

     }
     else
     {
     }

    /*
    �����к���ʵ����Ϊδʹ�õ�,
    ������ҵ���������ṹ��Ϊ�޲������ڽ���
    ������ҵ���������ṹ�еĹ�ע�¼�������Ϊ0
    */
    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        f_astCallMgmtEntities[i].bUsed = VOS_FALSE;
        f_astCallMgmtEntities[i].stCallInfo.enCallState = MN_CALL_S_IDLE;
        f_astCallMgmtEntities[i].stCallInfo.clientId = MN_CLIENT_ALL;
    }

    f_stCallSupsCmdMgmt.bInProgress = VOS_FALSE;
    f_stCallSupsCmdMgmt.ucInvokeId = 0;
    f_stCallSupsCmdMgmt.ucNumOfKeyEvt = 0;

    for ( i = 0 ; i < MN_CALL_MAX_INVOKE_NUM; i++ )
    {
        MN_CALL_InvokeId_Free((VOS_UINT8)i);
    }

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
    MN_CALL_VoicePreferSendRabmVoiceCallIndMsg(VOS_FALSE);
#endif
}


/*****************************************************************************
 �� �� ��  : MN_CALL_AllocCallId
 ��������  : �����Ӧ��Call Id
 �������  : pCallId  - ��Ҫ����ĺ���ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��6��23��
    ��    ��   : z00161729
    �޸�����   : DSDS III����
*****************************************************************************/
VOS_UINT32 MN_CALL_AllocCallId(
    MN_CALL_ID_T                        *pCallId
)
{
    VOS_UINT16                          i;

    (VOS_VOID)VOS_TaskLock();

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        /* �����δ�����ʵ�壬���ص�Call id ��ֵΪʵ�������±�ֵ��1 */
        if (VOS_FALSE == f_astCallMgmtEntities[i].bUsed)
        {
            *pCallId = (VOS_UINT8)i + 1;
            f_astCallMgmtEntities[i].bUsed = VOS_TRUE;
            f_astCallMgmtEntities[i].stCallInfo.enCallState = MN_CALL_S_IDLE;

            f_astCallMgmtEntities[i].stCallInfo.enCallSubState = TAF_CALL_SUB_STATE_NULL;

            (VOS_VOID)VOS_TaskUnlock();
            return  VOS_OK;
        }

    }

    (VOS_VOID)VOS_TaskUnlock();
    return VOS_ERR;

}

/*****************************************************************************
 �� �� ��  : MN_CALL_FreeCallId
 ��������  : �ͷź���ID
 �������  : callId  - ��Ҫ�ͷŵĺ���ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ��SS FDN&Call Control�ƶ���TAF
  4.��    ��   : 2013��08��19��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ����MTC�ϱ�����״̬
  5.��    ��   : 2013��11��04��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseII��Ŀ
  6.��    ��   : 2014��04��08��
    ��    ��   : y00245242
    �޸�����   : ΪeCall���Թ����޸�
  7.��    ��   : 2014��6��24��
    ��    ��   : z00161729
    �޸�����   : DSDS III����
  8.��    ��   : 2015��10��10��
    ��    ��   : c00318887
    �޸�����   : DTS2015090607329
*****************************************************************************/
VOS_VOID   MN_CALL_FreeCallId(
    MN_CALL_ID_T                        callId
)
{
    VOS_UINT32                          i;

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_FreeCallId: callId error!");
        return;
    }

    (VOS_VOID)VOS_TaskLock();

    /* ����Ӧ�ĺ���ʵ���ֵ��0 */
    PS_MEM_SET(&f_astCallMgmtEntities[callId - 1], 0, sizeof(MN_CALL_MGMT_STRU));
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallState = MN_CALL_S_IDLE;
    f_astCallMgmtEntities[callId - 1].stCallInfo.clientId = MN_CLIENT_ALL;

    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-21, begin */
    f_astCallMgmtEntities[callId - 1].stCallInfo.stDiscDir.ucDiscCallFlag = VOS_FALSE;
    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-5-21, end */

    /* ���������״̬Ϊnull */
    TAF_CALL_SetCallSubState(callId, TAF_CALL_SUB_STATE_NULL);

    (VOS_VOID)VOS_TaskUnlock();

    /*�������к��п���ʵ��*/
    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == f_astCallMgmtEntities[i].bUsed)
         && (MN_CALL_S_IDLE != f_astCallMgmtEntities[i].stCallInfo.enCallState))

        {
            break;
        }
    }

    if (MN_CALL_MAX_NUM == i)
    {
        /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, begin */
        TAF_CALL_SetCsCallExistFlg(VOS_FALSE, MN_CALL_TYPE_BUTT);
        /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, end */

        /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* ��MTCģ���ϱ���ǰCS��ҵ��״̬ */
        TAF_SendMtcCsSrvInfoInd();
#endif
        /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, end */
    }

#if (FEATURE_ON == FEATURE_HUAWEI_VP)
    MN_CALl_VoicePreferJudgeVoiceCallExist();
#endif
}


/*****************************************************************************
 �� �� ��  : MN_CALL_IsAllowToMakeNewCall
 ��������  : ����Ƿ���Է���/����һ���µĺ���
 �������  : callId    - ��Ҫ���ĺ��е�ID
              enCallDir - ���еķ���(����/����)
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_BOOL   MN_CALL_IsAllowToMakeNewCall(
    MN_CALL_ID_T                        callId,
    MN_CALL_DIR_ENUM_U8                 enCallDir
)
{
    VOS_UINT16                          i;


    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_IsAllowToMakeNewCall: callId error!");
        return VOS_FALSE;
    }

    /* CallId��Ӧʵ��δ��ʹ�ã��򷵻� */
    if ( VOS_FALSE == f_astCallMgmtEntities[callId - 1].bUsed )
    {
        return VOS_FALSE;
    }

    if ( MN_CALL_DIR_MO == enCallDir )
    {
        /* ����CallId��Ӧʵ��ĺ���״̬��ΪIDLE */
        if ( MN_CALL_S_IDLE != f_astCallMgmtEntities[callId - 1].stCallInfo.enCallState )
        {
            return VOS_FALSE;
        }
    }
    else
    {
        /* ����CallId��Ӧʵ��ĺ���״̬��ΪINCOMING��WAITING */
        if (( MN_CALL_S_INCOMING != f_astCallMgmtEntities[callId - 1].stCallInfo.enCallState )
          &&( MN_CALL_S_WAITING != f_astCallMgmtEntities[callId - 1].stCallInfo.enCallState ))
        {
            return VOS_FALSE;
        }
    }

    /*�������к���ʵ��,ʵ�屻ʹ����״̬����HELD��IDLE */
    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if ( i == (callId - 1) )
        {
            continue;
        }

        if (( VOS_TRUE == f_astCallMgmtEntities[i].bUsed)
          &&( MN_CALL_S_IDLE != f_astCallMgmtEntities[i].stCallInfo.enCallState )
          &&( MN_CALL_S_HELD != f_astCallMgmtEntities[i].stCallInfo.enCallState ))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_CreateMoCallEntity
 ��������  : �½�һ�����к��й���ʵ�壬��������Ӧ�����ݵ�ȫ�ֱ���
 �������  : callId         - ���е�ID
             clientId       - ���Ƹú��е�Client, ���ڱ��ж���, ���ڴ���ʵ��ʱClient
             pstOrigParam   - ����������Я���Ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��23��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��05��21��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ��:DTS2012052100994,������ӵ绰����������ĳ������Ͳ���
  3.��    ��   : 2012��09��18��
    ��    ��   : y00213812
    �޸�����   : STK&DCM ��Ŀ��������
  4.��    ��   : 2012��09��20��
    ��    ��   : f62575
    �޸�����   : STK&DCM ��Ŀ
  5.��    ��   : 2012��10��29��
    ��    ��   : l00198894
    �޸�����   : DTS2012100901666: �޸ı��к���ṹ��
  6.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ��SS FDN&Call Control�ƶ���TAF
  7.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
  8.��    ��   : 2013��08��19��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ����MTC�ϱ�����״̬
  9.��    ��   : 2013��9��20��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseII ���Ӻ�������Ϣ
  10.��    ��   : 2014��4��26��
     ��    ��   : z00161729
     �޸�����   : DTS2014042604200:f_abCallReleaseFlag��ʶά�����ԣ����µڶ����绰����ʱ�������·�disconnect event
 11.��    ��   : 2015��10��10��
    ��    ��   : c00318887
    �޸�����   : DTS2015090607329
*****************************************************************************/
VOS_VOID  MN_CALL_CreateMoCallEntity(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    MN_CALL_ORIG_PARAM_STRU            *pstOrigParam
)
{
    if (( callId > MN_CALL_MAX_NUM )
     || ( callId == 0 ))
    {
        MN_WARN_LOG("MN_CALL_CreateMoCallEntity: Invalid Msg Type");
        return;
    }

    /* �������������дCallId��Ӧ����ʵ���е�CallInfo���� */
    /* �������ж���,����CCʵ�廹δ����, CCʵ���е�Tiֵ������, ������ظ��ϱ�ʱ�ټ�¼ */
    PS_MEM_SET(&f_astCallMgmtEntities[callId - 1],
               0,
               sizeof(f_astCallMgmtEntities[callId - 1]));

    f_astCallMgmtEntities[callId - 1].bUsed                 = VOS_TRUE;
    f_astCallMgmtEntities[callId - 1].stCallInfo.clientId   = clientId;
    f_astCallMgmtEntities[callId - 1].stCallInfo.opId       = opId;
    f_astCallMgmtEntities[callId - 1].stCallInfo.callId     = callId;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType = pstOrigParam->enCallType;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallMode = pstOrigParam->enCallMode;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallDir  = MN_CALL_DIR_MO;
    f_astCallMgmtEntities[callId - 1].enClirCfg             = pstOrigParam->enClirCfg;

    /* Added by Y00213812 for VoLTE_PhaseII ��Ŀ, 2013-9-12, begin */
    /* ������������Ϣ */
    f_astCallMgmtEntities[callId - 1].stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP;                                  /* VOICE DOMAIN */
    /* Added by Y00213812 for VoLTE_PhaseII ��Ŀ, 2013-9-12, end */

    PS_MEM_CPY(&f_astCallMgmtEntities[callId - 1].stCugCfg,
               &pstOrigParam->stCugCfg,
               sizeof(f_astCallMgmtEntities[callId - 1].stCugCfg));

    PS_MEM_CPY(&(f_astCallMgmtEntities[callId - 1].stCallInfo.stDataCfgInfo),
               &pstOrigParam->stDataCfg,
               sizeof(MN_CALL_CS_DATA_CFG_STRU));

    PS_MEM_CPY(&f_astCallMgmtEntities[callId - 1].stCallInfo.stCalledNumber,
               &pstOrigParam->stDialNumber,
               sizeof(pstOrigParam->stDialNumber));

    /* ��CallInfo�е�ת�ƺ�������Ӻ����еĳ����ֶζ�����Ϊ0 */
    f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectNumber.ucNumLen = 0;
    f_astCallMgmtEntities[callId - 1].stCallInfo.stConnectNumber.ucNumLen = 0;

    PS_MEM_CPY(&f_astCallMgmtEntities[callId - 1].stCallInfo.stCalledSubAddr,
               &pstOrigParam->stSubaddr,
               sizeof(MN_CALL_SUBADDR_STRU));

    /* Deleted by l00198894 for V9R1 STK����, 2013/07/11 */

    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, begin */
    TAF_CALL_SetCsCallExistFlg(VOS_TRUE, f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType);
    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, end */

    MN_CALL_UpdateCallReleaseFlag(callId, VOS_FALSE);

    /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* ��MTCģ���ϱ���ǰCS��ҵ��״̬ */
    TAF_SendMtcCsSrvInfoInd();
#endif
    /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, end */

    return;
}

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-4, begin */
#if (FEATURE_ON == FEATURE_ECALL)
/*****************************************************************************
 �� �� ��  : TAF_CALL_IsCallTypeEcall
 ��������  : ����ucCallId��ȡ��ǰeCall��־
 �������  : ucCallId - ���е�ID
 �������  : ��
 �� �� ֵ  : ����eCall flag.
             VOS_TRUE  -- ��ǰ��������eCall
             VOS_FALSE -- ��ǰ���в�����eCall
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��04��04��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_UINT8 TAF_CALL_IsCallTypeEcall(MN_CALL_ID_T ucCallId)
{
    if ( (ucCallId == 0) || ( ucCallId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_IsCallTypeEcall: ucCallId is illegal!");
        return VOS_FALSE;
    }

    if ((MN_CALL_TYPE_MIEC         == (f_astCallMgmtEntities[ucCallId-1].stCallInfo.enCallType))
     || (MN_CALL_TYPE_AIEC         == (f_astCallMgmtEntities[ucCallId-1].stCallInfo.enCallType))
     || (MN_CALL_TYPE_TEST         == (f_astCallMgmtEntities[ucCallId-1].stCallInfo.enCallType))
     || (MN_CALL_TYPE_RECFGURATION == (f_astCallMgmtEntities[ucCallId-1].stCallInfo.enCallType))
     || (MN_CALL_TYPE_PSAP_ECALL   == (f_astCallMgmtEntities[ucCallId-1].stCallInfo.enCallType)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_CALL_IsCallTypeEmgencyCall
 ��������  : ����ucCallIdȷ�ϵ�ǰ�����Ƿ�ʱ������
 �������  : ucCallId - ���е�ID
 �������  : ��
 �� �� ֵ  :
             VOS_TRUE  -- ��ǰ�������ڽ�����
             VOS_FALSE -- ��ǰ���в����ڽ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��04��26��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_UINT8 TAF_CALL_IsCallTypeEmgencyCall(MN_CALL_ID_T ucCallId)
{
    if ( (ucCallId == 0) || ( ucCallId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_IsCallTypeEcall: ucCallId is illegal!");
        return VOS_FALSE;
    }

    if ((MN_CALL_TYPE_EMERGENCY == f_astCallMgmtEntities[ucCallId-1].stCallInfo.enCallType)
#if (FEATURE_ON == FEATURE_ECALL)
     || (MN_CALL_TYPE_MIEC      == f_astCallMgmtEntities[ucCallId-1].stCallInfo.enCallType)
     || (MN_CALL_TYPE_AIEC      == f_astCallMgmtEntities[ucCallId-1].stCallInfo.enCallType)
#endif
       )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_UpdateCallInfo
 ��������  : ����ucCallId��ȡ��ǰeCall��־
 �������  : usClientId - �û���ʶ
             ucOpId     - ������ʶ
             ucCallId   - ���е�ID
             enCause    - ԭ��ֵ

 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��04��04��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature����
*****************************************************************************/
VOS_VOID TAF_CALL_UpdateCallInfo(
    MN_CALL_ID_T                        ucCallId,
    MN_CALL_INFO_STRU                  *pstCallInfo
)
{
    if ( (ucCallId == 0) || ( ucCallId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_UpdateCallInfo: ucCallId is illegal!");
        return;
    }

        /* ���������ϱ����ȫ�ֱ�����ֵ */
    PS_MEM_CPY(&(f_astCallMgmtEntities[ucCallId - 1].stCallInfo),
               pstCallInfo,
               sizeof(MN_CALL_INFO_STRU));

}
/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-4, end */

/*****************************************************************************
 �� �� ��  : MN_CALL_GetSpecificCallInfo
 ��������  : �½�һ�����й���ʵ�壬��дʵ���е�һЩ��ʼ��Ϣ
 �������  : callId         - ���е�ID
 �������  : pstCallInfo    -
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��23��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MN_CALL_GetSpecificCallInfo(
    MN_CALL_ID_T                        CallId,
    MN_CALL_MGMT_STRU                  *pstCallInfo
)
{
    if ((CallId > MN_CALL_MAX_NUM )
     || (0 == CallId))
    {
        return VOS_ERR;
    }

    PS_MEM_CPY(pstCallInfo, &f_astCallMgmtEntities[CallId - 1], sizeof(MN_CALL_MGMT_STRU));

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_CcIeCallingNumToApiCallingNum
 ��������  : ���տڵ����к���ṹת����APIҪ��Ľṹ
 �������  : pstCcIeNum - ����CC�Ŀտڽṹ�����к���
 �������  : pstNum     - API��������к���ṹ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��29��
    ��    ��   : l00198894
    �޸�����   : DTS2012100901666: ��������
*****************************************************************************/
LOCAL VOS_VOID  MN_CALL_CcIeCallingNumToApiCallingNum(
    NAS_CC_IE_CALLING_NUM_STRU          *pstCcIeNum,
    MN_CALL_BCD_NUM_STRU                *pstNum
)
{
    PS_MEM_SET(pstNum, 0, sizeof(MN_CALL_BCD_NUM_STRU));

    if (VOS_FALSE == NAS_IE_IS_PRESENT(pstCcIeNum))
    {
        return;
    }

    pstNum->ucNumLen = (VOS_UINT8)NAS_IE_GET_BLOCK_SIZE(pstCcIeNum, BCDNum);

    pstNum->enNumType = *((VOS_UINT8*)&pstCcIeNum->Octet3);

    PS_MEM_CPY(pstNum->aucBcdNum, pstCcIeNum->BCDNum, pstNum->ucNumLen);

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_CcIeCalledNumtoApiCalledNum
 ��������  : ���տڵı��к���ṹת����APIҪ��Ľṹ
 �������  : pstCcIeNum - ����CC�Ŀտڽṹ�ı��к���
 �������  : pstNum     - API����ĺ���ṹ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��29��
    ��    ��   : l00198894
    �޸�����   : DTS2012100901666: ��������
*****************************************************************************/
LOCAL VOS_VOID  MN_CALL_CcIeCalledNumtoApiCalledNum(
    NAS_CC_IE_CALLED_NUM_STRU          *pstCcIeNum,
    MN_CALL_CALLED_NUM_STRU            *pstNum
)
{
    PS_MEM_SET(pstNum, 0, sizeof(MN_CALL_CALLED_NUM_STRU));

    if (VOS_FALSE == NAS_IE_IS_PRESENT(pstCcIeNum))
    {
        return;
    }

    pstNum->ucNumLen = (VOS_UINT8)NAS_IE_GET_BLOCK_SIZE(pstCcIeNum, BCDNum);

    pstNum->enNumType = *((VOS_UINT8*)&pstCcIeNum->Octet3);

    PS_MEM_CPY(pstNum->aucBcdNum, pstCcIeNum->BCDNum, pstNum->ucNumLen);

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_CcIeCalledSubAddrtoApiSubAddr
 ��������  : ���տڵı����ӵ�ַ�ṹת����APIҪ��Ľṹ
 �������  : pstCcIeSubAddr - ����CC�Ŀտڽṹ�ı��к���
 �������  : pstSubAddr     - API����ĺ���ṹ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��29��
    ��    ��   : l00198894
    �޸�����   : DTS2012100901666: ��������
*****************************************************************************/
LOCAL VOS_VOID  MN_CALL_CcIeCalledSubAddrtoApiSubAddr(
    NAS_CC_IE_CALLED_SUBADDR_STRU      *pstCcIeSubAddr,
    MN_CALL_SUBADDR_STRU               *pstSubAddr
)
{
    VOS_UINT8                           ucLen;

    PS_MEM_SET(pstSubAddr, 0, sizeof(MN_CALL_SUBADDR_STRU));

    if (VOS_FALSE == NAS_IE_IS_PRESENT(pstCcIeSubAddr))
    {
        return;
    }

    ucLen = pstCcIeSubAddr->LastOctOffset - sizeof(NAS_CC_IE_CALLED_SUBADDR_OCTET3_STRU);

    if (ucLen <= MN_CALL_MAX_SUBADDR_INFO_LEN)
    {
        pstSubAddr->IsExist         = VOS_TRUE;
        pstSubAddr->LastOctOffset   = pstCcIeSubAddr->LastOctOffset;
        pstSubAddr->Octet3          = *((VOS_UINT8*)&pstCcIeSubAddr->Octet3);

        PS_MEM_CPY(pstSubAddr->SubAddrInfo, pstCcIeSubAddr->SubAddrInfo, ucLen);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_CcIeCallingSubAddrtoApiSubAddr
 ��������  : ���տڵ������ӵ�ַ�ṹת����APIҪ��Ľṹ
 �������  : pstCcIeSubAddr - ����CC�Ŀտڽṹ�ı��к���
 �������  : pstSubAddr     - API����ĺ���ṹ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��29��
    ��    ��   : l00198894
    �޸�����   : DTS2012100901666: ��������
*****************************************************************************/
LOCAL VOS_VOID  MN_CALL_CcIeCallingSubAddrtoApiSubAddr(
    NAS_CC_IE_CALLING_SUBADDR_STRU     *pstCcIeSubAddr,
    MN_CALL_SUBADDR_STRU               *pstSubAddr
)
{
    VOS_UINT8                           ucLen;

    PS_MEM_SET(pstSubAddr, 0, sizeof(MN_CALL_SUBADDR_STRU));

    if (VOS_FALSE == NAS_IE_IS_PRESENT(pstCcIeSubAddr))
    {
        return;
    }

    ucLen = pstCcIeSubAddr->LastOctOffset - sizeof(NAS_CC_IE_CALLING_SUBADDR_OCTET3_STRU);

    if (ucLen <= MN_CALL_MAX_SUBADDR_INFO_LEN)
    {
        pstSubAddr->IsExist         = VOS_TRUE;
        pstSubAddr->LastOctOffset   = pstCcIeSubAddr->LastOctOffset;
        pstSubAddr->Octet3          = *((VOS_UINT8*)&pstCcIeSubAddr->Octet3);

        PS_MEM_CPY(pstSubAddr->SubAddrInfo, pstCcIeSubAddr->SubAddrInfo, ucLen);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_CreateMtCallEntity
 ��������  : �½�һ�����к��й���ʵ�壬��������Ӧ�����ݵ�ȫ�ֱ���
 �������  : callId         - ���е�ID
             ucTi           - ����ʵ���Ӧ��Ti
             pstSetup       - ����������Я���Ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��29��
    ��    ��   : l00198894
    �޸�����   : DTS2012100901666: ��������
  2.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ��SS FDN&Call Control�ƶ���TAF
  3.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
  4.��    ��   : 2013��08��19��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ����MTC�ϱ�����״̬
  5.��    ��   : 2013��9��20��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseII ���Ӻ�������Ϣ
  6.��    ��   : 2015��10��10��
    ��    ��   : c00318887
    �޸�����   : DTS2015090607329
*****************************************************************************/
VOS_VOID  MN_CALL_CreateMtCallEntity(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucTi,
    NAS_CC_MSG_SETUP_MT_STRU           *pstSetup
)
{
    MN_CALL_BCD_NUM_STRU                stCallingNum;
    MN_CALL_CALLED_NUM_STRU             stCalledNum;
    MN_CALL_SUBADDR_STRU                stSubAddr;

    /* ��ʼ�� */
    PS_MEM_SET(&stCallingNum, 0, sizeof(stCallingNum));
    PS_MEM_SET(&stCalledNum, 0, sizeof(stCalledNum));
    PS_MEM_SET(&stSubAddr, 0, sizeof(stSubAddr));

    /* �ж�callId�ĺϷ��� */
    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_CreateMtCallEntity: callId error!");
        return;
    }

    /* �������������дCallId��Ӧ����ʵ���е�CallInfo���� */
    f_astCallMgmtEntities[callId - 1].ulTi                  = ucTi;
    f_astCallMgmtEntities[callId - 1].bUsed                 = VOS_TRUE;
    f_astCallMgmtEntities[callId - 1].stCallInfo.clientId   = MN_CLIENT_ALL;
    f_astCallMgmtEntities[callId - 1].stCallInfo.callId     = callId;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType = MN_CALL_TYPE_VOICE;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallMode = MN_CALL_MODE_SINGLE;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallDir  = MN_CALL_DIR_MT;

    /* Added by Y00213812 for VoLTE_PhaseII ��Ŀ, 2013-9-12, begin */
    /* ������������Ϣ */
    f_astCallMgmtEntities[callId - 1].stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP;                                  /* VOICE DOMAIN */
    /* Added by Y00213812 for VoLTE_PhaseII ��Ŀ, 2013-9-12, end */

    /* ת�����к��� */
    MN_CALL_CcIeCallingNumToApiCallingNum(&pstSetup->stCallingNum, &stCallingNum);
    MN_CALL_UpdateCallNumber(callId, &stCallingNum);

    /* ת�������ӵ�ַ */
    MN_CALL_CcIeCallingSubAddrtoApiSubAddr(&pstSetup->stCallingSubaddr, &stSubAddr);
    PS_MEM_CPY(&f_astCallMgmtEntities[callId-1].stCallInfo.stSubCallNumber,
               &stSubAddr,
               sizeof(stSubAddr));

    /* ת�����к��� */
    MN_CALL_CcIeCalledNumtoApiCalledNum(&pstSetup->stCalledNum, &stCalledNum);
    MN_CALL_UpdateCalledNumber(callId, &stCalledNum);

    /* ת�������ӵ�ַ */
    MN_CALL_CcIeCalledSubAddrtoApiSubAddr(&pstSetup->stCalledSubaddr, &stSubAddr);
    PS_MEM_CPY(&f_astCallMgmtEntities[callId-1].stCallInfo.stCalledSubAddr,
               &stSubAddr,
               sizeof(stSubAddr));

    /* ��¼����Դ��Ϣ */
    MN_CALL_RecordCallEntityRedirectInfo(callId, pstSetup);

    PS_MEM_SET(&f_astCallMgmtEntities[callId - 1].stCallInfo.stDataCfgInfo,
               0,
               sizeof(MN_CALL_CS_DATA_CFG_INFO_STRU));

    /* Deleted by l00198894 for V9R1 STK����, 2013/07/11 */

    MN_CALL_UpdateCallReleaseFlag(callId, VOS_FALSE);

    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, begin */
    TAF_CALL_SetCsCallExistFlg(VOS_TRUE, f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType);
    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, end */

    /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* ��MTCģ���ϱ���ǰCS��ҵ��״̬ */
    TAF_SendMtcCsSrvInfoInd();
#endif
    /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, end */

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_CreateCallEntity
 ��������  : �½�һ�����й���ʵ�壬��дʵ���е�һЩ��ʼ��Ϣ
 �������  : callId     - ���е�ID
              ulTi       - �ú��ж�Ӧ��CCʵ���е�Tiֵ.�������ж���,����CCʵ�廹δ
                          ����, �ò�����������, ������ظ��ϱ�ʱ�ټ�¼
              clientId   - ���Ƹú��е�Client, ���ڱ��ж���, ���ڴ���ʵ��ʱClient
                          δȷ��, �ò�����������
              enCallType - �ú��еĺ�������
              enCallMode - �ú��еĺ���ģʽ
              enCallDir  - �ú��еĺ��з���(����/����)
              pstDataCfgInfo - �ú��е���������. ������������, �ò�����������.
              pstNumber  - �ú��еĶԷ�����. ����ʱ���Setup��Ϣ��û�жԷ�����,
                          �ò�����ΪNULL
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2012��09��18��
    ��    ��   : y00213812
    �޸�����   : STK&DCM ��Ŀ��������
  4.��    ��   : 2012��09��20��
    ��    ��   : f62575
    �޸�����   : STK&DCM ��Ŀ, ��������ͷű��
  5.��    ��   : 2012��10��29��
    ��    ��   : l00198894
    �޸�����   : DTS2012100901666: ��������ʵ��ǰ������ղ���
  6.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ��SS FDN&Call Control�ƶ���TAF
  7.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
  8.��    ��   : 2013��08��19��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ����MTC�ϱ�����״̬
  9.��    ��   : 2013��9��20��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseII ���Ӻ�������Ϣ
*****************************************************************************/
VOS_VOID  MN_CALL_CreateCallEntity(
    MN_CALL_ID_T                        callId,
    VOS_UINT32                          ulTi,
    MN_CLIENT_ID_T                      clientId,
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_MODE_ENUM_U8                enCallMode,
    MN_CALL_DIR_ENUM_U8                 enCallDir,
    const MN_CALL_CS_DATA_CFG_INFO_STRU *pstDataCfgInfo,
    const MN_CALL_BCD_NUM_STRU          *pstNumber
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_CreateCallEntity: callId error!");
        return;
    }

    /* �������������дCallId��Ӧ����ʵ���е�CallInfo���� */
    f_astCallMgmtEntities[callId - 1].ulTi = ulTi;
    f_astCallMgmtEntities[callId - 1].stCallInfo.clientId = clientId;
    f_astCallMgmtEntities[callId - 1].stCallInfo.callId = callId;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType = enCallType;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallMode = enCallMode;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallDir = enCallDir;

    /* Added by Y00213812 for VoLTE_PhaseII ��Ŀ, 2013-9-12, begin */
    /* ������������Ϣ */
    f_astCallMgmtEntities[callId - 1].stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP;                                  /* VOICE DOMAIN */
    /* Added by Y00213812 for VoLTE_PhaseII ��Ŀ, 2013-9-12, end */

    if (VOS_NULL_PTR != pstDataCfgInfo)
    {
        PS_MEM_CPY(&(f_astCallMgmtEntities[callId - 1].stCallInfo.stDataCfgInfo),
                   pstDataCfgInfo,
                   sizeof(MN_CALL_CS_DATA_CFG_INFO_STRU));
    }

    if ( VOS_NULL_PTR == pstNumber )
    {
        f_astCallMgmtEntities[callId - 1].stCallInfo.stCallNumber.ucNumLen = 0;
    }
    else
    {
        f_astCallMgmtEntities[callId - 1].stCallInfo.stCallNumber = *pstNumber;
    }

    PS_MEM_SET(&f_astCallMgmtEntities[callId - 1].stCallInfo.stCalledNumber,
               0,
               sizeof(MN_CALL_CALLED_NUM_STRU));

    /* ��CallInfo�е����Ӻ����еĳ����ֶ�����Ϊ0 */
    f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectNumber.ucNumLen = 0;
    f_astCallMgmtEntities[callId - 1].stCallInfo.stConnectNumber.ucNumLen  = 0;

    /* ��CallInfo�е�ת�ƺ����ת�ƺ�����ӵ�ַ�ĳ�����Ϊ0 */
    f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectNumber.ucNumLen       = 0;
    f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectSubaddr.LastOctOffset = 0;
    f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectSubaddr.IsExist       = VOS_FALSE;

    /* Deleted by l00198894 for V9R1 STK����, 2013/07/11 */

    MN_CALL_UpdateCallReleaseFlag(callId, VOS_FALSE);

    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, begin */
    TAF_CALL_SetCsCallExistFlg(VOS_TRUE, f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType);
    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, end */

    /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* ��MTCģ���ϱ���ǰCS��ҵ��״̬ */
    TAF_SendMtcCsSrvInfoInd();
#endif
    /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, end */

    return;

}


/*****************************************************************************
 �� �� ��  : MN_CALL_DeleteCallEntity
 ��������  : ���һ�����й���ʵ��
 �������  : callId - ��Ҫ����ĺ��е�ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_DeleteCallEntity(
    MN_CALL_ID_T                        callId
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_DeleteCallEntity: callId error!");
        return;
    }

    /* ��CallId��Ӧ�ĺ��п���ʵ������Ϊδʹ�õ� */
    f_astCallMgmtEntities[callId - 1].bUsed = VOS_FALSE;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallState = MN_CALL_S_IDLE;
    f_astCallMgmtEntities[callId - 1].stCallInfo.clientId = MN_CLIENT_ALL;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_GetCcTi
 ��������  : ����CallId��ȡEntityId
 �������  : callId - ���е�ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_UINT32 MN_CALL_GetCcTi(MN_CALL_ID_T callId)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_GetCcTi: callId error!");
        return 0;
    }

    return f_astCallMgmtEntities[callId-1].ulTi;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_GetCcCallDir
 ��������  : ����CallId��ȡEntityId
 �������  : callId - ���е�ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/

VOS_UINT32 MN_CALL_GetCcCallDir(MN_CALL_ID_T callId)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_GetCcCallDir: callId error!");
        return MN_CALL_DIR_BUTT;
    }

    return f_astCallMgmtEntities[callId-1].stCallInfo.enCallDir;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_ReportEvent
 ��������  : ������Client�ϱ������¼�
 �������  : callId      - ��Ҫ�ϱ��¼��ĺ��е�ID
              enEventType - �¼�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��14��
    ��    ��   : ³��/l60609
    �޸�����   : AT Project:incoming��release�¼����ݺ��п��Ʊ�־�ж��Ƿ��ϱ�
  3.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  4.��    ��   : 2012��12��31��
    ��    ��   : l65478
    �޸�����   : DTS2012122900264:DTMF����ʧ��
  5.��    ��   : 2013��4��3��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
*****************************************************************************/
VOS_VOID  MN_CALL_ReportEvent(
    MN_CALL_ID_T                        callId,
    MN_CALL_EVENT_ENUM_U32              enEventType
)
{
    /* Modified by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, begin */
    TAF_SDC_CURC_RPT_CTRL_STRU          *pstCurcRptCtrl           = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU   *pstUnsolicitedRptCtrl    = VOS_NULL_PTR;

    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();


    if ( (callId == 0)
      || ( callId > MN_CALL_MAX_NUM ))
    {
        TAF_ERROR_LOG1(WUEPS_PID_TAF, "MN_CALL_ReportEvent: callId error!", callId);
        return;
    }

    if ((MN_CALL_EVT_ALL_RELEASED != enEventType)
     && (VOS_FALSE == f_astCallMgmtEntities[callId - 1].bUsed))
    {
        TAF_ERROR_LOG2(WUEPS_PID_TAF, "MN_CALL_ReportEvent: callid or enEventType error!", callId, enEventType);
        return;
    }

    MN_INFO_LOG1("MN_CALL_ReportEvent: event.", (VOS_INT32)enEventType);

    /* Modified by l60609 for AT Project��2011-11-14,  Begin*/
    /* Modified by z00234330 for PCLINT����, 2014-06-24, begin */
    if (VOS_FALSE == TAF_CALL_GetCallStatusControl())
    /* Modified by z00234330 for PCLINT����, 2014-06-24, end */
    {
        /*����Ҫ�ϱ��������е�incoming�¼�*/
        if ((MN_CALL_EVT_INCOMING == enEventType)
          &&(MN_CALL_TYPE_VOICE == f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType))
        {

#if (FEATURE_ON == FEATURE_PTM)
            /* setup��Ϣ��Э����ʧ�ܵ��쳣��¼ */
            MN_CALL_CsMtCallFailRecord(NAS_ERR_LOG_CS_MT_CALL_CAUSE_CALL_STATE_CTRL_NOT_SUPPORT);
#endif

            return;
        }

        /*����Ҫ�ϱ�release�¼�*/
        if (MN_CALL_EVT_RELEASED == enEventType)
        {
            return;
        }
    }
    /* Modified by l60609 for AT Project��2011-11-14,  End*/

    /* ���������ϱ����ȫ�ֱ�����ֵ */
    PS_MEM_CPY(f_astCallMgmtEntities[callId - 1].stCallInfo.aucCurcRptCfg,
                pstCurcRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    PS_MEM_CPY(f_astCallMgmtEntities[callId - 1].stCallInfo.aucUnsolicitedRptCfg,
                pstUnsolicitedRptCtrl->aucRptCfg,
                MN_CALL_RPT_CFG_MAX_SIZE);

    /* Modified by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, end */

    /* ������ע����CS������¼��ص�������Client���ûص����� */
    MN_SendClientEvent(MN_CLIENT_ALL,
                       MN_CALLBACK_CS_CALL,
                       enEventType,
                       &f_astCallMgmtEntities[callId - 1].stCallInfo);
}


/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateClientId
 ��������  : ����ָ�����е�Client ID��Ϣ
 �������  : callId   - ��Ҫ����Client ID�ĺ��е�ID
              clientId - �µ�Client IDֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateClientId(
    MN_CALL_ID_T                        callId,
    MN_CLIENT_ID_T                      clientId
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateClientId: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.clientId = clientId;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateCallState
 ��������  : ����ָ�����еĺ���״̬��Ϣ
 �������  : callId      - ��Ҫ����״̬�ĺ��е�ID
              enCallState - �µĺ���״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCallState(
    MN_CALL_ID_T                        callId,
    MN_CALL_STATE_ENUM_U8               enCallState
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateCallState: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallState = enCallState;

    MN_INFO_LOG1("MN_CALL_UpdateCallState: CallState,", enCallState);
}

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateMptyState
 ��������  : ����ָ�����е�MPTY״̬��Ϣ
 �������  : callId      - ��Ҫ����MPTY״̬�ĺ��е�ID
              enMptyState - �µ�MPTY״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateMptyState(
    MN_CALL_ID_T                        callId,
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateMptyState: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.enMptyState = enMptyState;

}


/*****************************************************************************
 �� �� ��  : MN_CALL_GetCallType
 ��������  : ��ȡָ�����еĺ���������Ϣ
 �������  : callId     - ��Ҫ���º������͵ĺ��е�ID
              enCallType - �µĺ�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
MN_CALL_TYPE_ENUM_U8  MN_CALL_GetCallType(
    MN_CALL_ID_T                        callId
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_GetCallType: callId error!");
        return MN_CALL_TYPE_BUTT;
    }

    return f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateCallType
 ��������  : ����ָ�����еĺ���������Ϣ
 �������  : callId     - ��Ҫ���º������͵ĺ��е�ID
              enCallType - �µĺ�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCallType(
    MN_CALL_ID_T                        callId,
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateCallType: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType = enCallType;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateCallMode
 ��������  : ����ָ�����еĺ���ģʽ��Ϣ
 �������  : callId     - ��Ҫ���º���ģʽ�ĺ��е�ID
              enCallMode - �µĺ���ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCallMode(
    MN_CALL_ID_T                        callId,
    MN_CALL_MODE_ENUM_U8                enCallMode
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateCallMode: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallMode = enCallMode;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateDataCallCfgInfo
 ��������  : ����ָ�����е����ݺ���������Ϣ
 �������  : callId     - ��Ҫ�������ݺ������õĺ��е�ID
             pstDataCfgInfo - �µ����ݺ�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateDataCallCfgInfo(
    MN_CALL_ID_T                        callId,
    const MN_CALL_CS_DATA_CFG_INFO_STRU *pstDataCfgInfo
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateRecallSupsProgress: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId-1].stCallInfo.stDataCfgInfo= *pstDataCfgInfo;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_GetDataCallCfgInfo
 ��������  : ��ȡָ�����е����ݺ���������Ϣ
 �������  : callId     - ��Ҫ�������ݺ������õĺ��е�ID
              pstDataCfgInfo - �µ����ݺ�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_GetDataCallCfgInfo(
    MN_CALL_ID_T                        callId,
    MN_CALL_CS_DATA_CFG_INFO_STRU       *pstDataCfgInfo
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_GetDataCallCfgInfo: callId error!");
        return;
    }

    *pstDataCfgInfo = f_astCallMgmtEntities[callId-1].stCallInfo.stDataCfgInfo;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_GetMgmtEntityInfoByCallId
 ��������  : ��ȡָ��CallId��Ӧ�ĺ�����Ϣ
 �������  : callId        - ����ID
              pstMgmtEntity - �µ����ݺ�������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_GetMgmtEntityInfoByCallId(
    MN_CALL_ID_T                        callId,
    MN_CALL_MGMT_STRU                   *pstMgmtEntity
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_GetMgmtEntityInfoByCallId: callId error!");
        return;
    }

    *pstMgmtEntity = f_astCallMgmtEntities[callId-1];
}

/*****************************************************************************
 �� �� ��  : MN_CALL_GetCallInfoByCallId
 ��������  : ���ݺ���Id����ȡ��Ӧ��ʵ����й�����Ϣ
 �������  : callId      - ��Ҫ�������ݺ������õĺ��е�ID
              pstCallInfo - ���й���ʵ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_GetCallInfoByCallId(
    MN_CALL_ID_T                        callId,
    MN_CALL_INFO_STRU                   *pstCallInfo
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_GetCallInfoByCallId: callId error!");
        return;
    }

    *pstCallInfo = f_astCallMgmtEntities[callId-1].stCallInfo;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateRedirNumber
 ��������  : ����ָ�����е�ת�ƺ�����Ϣ
 �������  : callId         - ��Ҫ����ת�ƺ���ĺ��е�ID
              pstRedirNumber - �µ�ת�ƺ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateRedirNumber(
    MN_CALL_ID_T                        callId,
    const MN_CALL_BCD_NUM_STRU          *pstRedirNumber
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateRedirNumber: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId-1].stCallInfo.stRedirectNumber = *pstRedirNumber;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateConnNumber
 ��������  : ����ָ�����е����Ӻ�����Ϣ
 �������  : callId        - ��Ҫ�������Ӻ���ĺ��е�ID
              pstConnNumber - �µ����Ӻ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateConnNumber(
    MN_CALL_ID_T                        callId,
    const MN_CALL_BCD_NUM_STRU          *pstConnNumber
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateConnNumber: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId-1].stCallInfo.stConnectNumber = *pstConnNumber;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateCallNumber
 ��������  : ����ָ���������������Ϣ
 �������  : callId        - ��Ҫ�������Ӻ���ĺ��е�ID
              pstCallNumber - �µ����Ӻ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCallNumber(
    MN_CALL_ID_T                        callId,
    const MN_CALL_BCD_NUM_STRU          *pstCallNumber
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateCallNumber: callId error!");
        return;
    }


    f_astCallMgmtEntities[callId-1].stCallInfo.stCallNumber = *pstCallNumber;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateCalledNumber
 ��������  : ����ָ�����б��к�����Ϣ
 �������  : callId             - ��Ҫ�������Ӻ���ĺ��е�ID
             pstCalledNumber    - �µ����ӱ��к���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��29��
    ��    ��   : l00198894
    �޸�����   : DTS2012100901666: �����ɺ���

*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCalledNumber(
    MN_CALL_ID_T                        callId,
    const MN_CALL_CALLED_NUM_STRU      *pstCalledNumber
)
{
    if ( (0 == callId) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateCalledNumber: callId error!");
        return;
    }

    PS_MEM_CPY(&f_astCallMgmtEntities[callId-1].stCallInfo.stCalledNumber,
               pstCalledNumber,
               sizeof(MN_CALL_CALLED_NUM_STRU));
    return;
}






#if 0
/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateSsCmd
 ��������  : ����ָ�����еĲ���ҵ��������Ϣ
 �������  : callId      - ��Ҫ���²���ҵ������ĺ��е�ID
             pConnNumber - �µĲ���ҵ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateSsCmd(
    MN_CALL_ID_T       callId,
    MN_CALL_SUPS_CMD_ENUM_U8     SsCmd,
    MN_CALL_SS_RESULT_ENUM_U8  SsResult
);
#endif

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateSsNotify
 ��������  : ����ָ�����еĲ���ҵ��֪ͨ��Ϣ
 �������  : callId    - ��Ҫ���²���ҵ������ĺ��е�ID
              pstSsInfo - �µĲ���ҵ��֪ͨ��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateSsNotify(
    MN_CALL_ID_T                        callId,
    const MN_CALL_SS_NOTIFY_STRU        *pstSsInfo
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateSsNotify: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId-1].stCallInfo.stSsNotify = *pstSsInfo;

    MN_INFO_LOG1("MN_CALL_UpdateSsNotify: enCode.", pstSsInfo->enCode);
}


/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateCcCause
 ��������  : ����ָ�����е�CCԭ��ֵ��Ϣ
 �������  : callId    - ��Ҫ����CCԭ��ֵ�ĺ��е�ID
              enCcCause - �µ�CCԭ��ֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2013��07��17��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCcCause(
    MN_CALL_ID_T                        callId,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCcCause
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateCcCause: callId error!");
        return;
    }

    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-17, begin */
    f_astCallMgmtEntities[callId-1].stCallInfo.enCause = enCcCause;
    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-17, end */
}

/*****************************************************************************
 �� �� ��  : MN_CALL_GetCcCause
 ��������  : ��ȡָ�����е�CCԭ��ֵ��Ϣ
 �������  : callId    - ��Ҫ����CCԭ��ֵ�ĺ��е�ID
 �������  : ��
 �� �� ֵ  : MN_CALL_CC_CAUSE_ENUM_U8 -CCԭ��ֵ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��01��18��
    ��    ��   : Y00213812
    �޸�����   : DTS2013011201560��������
  2.��    ��   : 2013��07��09��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ,����ֵ������MN_CALL_CC_CAUSE_ENUM_U8���TAF_CS_CAUSE_ENUM_UINT32
                 ��������ΪMN_CALL_GetCsCause
*****************************************************************************/
TAF_CS_CAUSE_ENUM_UINT32  MN_CALL_GetCsCause(
    MN_CALL_ID_T                        callId
)
{
    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-17, begin */
    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_GetCsCause: callId error!");
        return TAF_CS_CAUSE_SUCCESS;
    }

    return f_astCallMgmtEntities[callId-1].stCallInfo.enCause;
    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-17, end */
}

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateNoCliCause
 ��������  : ����ָ�����е��޺�����ʾԭ����Ϣ
 �������  : callId       - ��Ҫ�����޺�����ʾԭ��ĺ��е�ID
              enNoCliCause - �µ��޺�����ʾԭ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateNoCliCause(
    MN_CALL_ID_T                        callId,
    MN_CALL_NO_CLI_CAUSE_ENUM_U8        enNoCliCause
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateNoCliCause: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId-1].stCallInfo.enNoCliCause = enNoCliCause;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateRabId
 ��������  : ����ָ�����е�RAB ID��Ϣ
 �������  : callId  - ��Ҫ����RAB ID�ĺ��е�ID
              ucRabId - �µ�RAB ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateRabId(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucRabId
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateRabId: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.ucRabId = ucRabId;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateTi
 ��������  : ����ָ�����е�TI��Ϣ
 �������  : callId  - ��Ҫ����RAB ID�ĺ��е�ID
              ucTi    - �µ�Tiֵ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateTi(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucTi
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateTi: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].ulTi = ucTi;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetSrvccLocalAlertedFlagByCallId
 ��������  : ��ȡSRVCCʱ���������״̬
 �������  : MN_CALL_ID_T                        callId
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��25��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_CALL_GetSrvccLocalAlertedFlagByCallId(
    MN_CALL_ID_T                        callId
)
{
    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_GetCallState: callId error!");
        return VOS_FALSE;
    }

    return f_astCallMgmtEntities[callId - 1].ucSrvccLocalAlertedFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_SetSrvccLocalAlertedFlagByCallId
 ��������  : ����SRVCCʱ���������״̬
 �������  : MN_CALL_ID_T                        callId
             VOS_UINT8                           ucSrvccLocalAlertedFlag
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��26��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_CALL_SetSrvccLocalAlertedFlagByCallId(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucSrvccLocalAlertedFlag
)
{
    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_GetCallState: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].ucSrvccLocalAlertedFlag = ucSrvccLocalAlertedFlag;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_GetCallState
 ��������  : ��ȡָ�����е�״̬��Ϣ
 �������  : callId       - ��Ҫ��ȡ״̬��Ϣ�ĺ��е�ID
 �������  : penCallState - ��õĺ���״̬
              penMptyState - ��õ�MPTY״̬
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_GetCallState(
    MN_CALL_ID_T                        callId,
    MN_CALL_STATE_ENUM_U8               *penCallState,
    MN_CALL_MPTY_STATE_ENUM_U8          *penMptyState
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_GetCallState: callId error!");
        return;
    }


    *penCallState = f_astCallMgmtEntities[callId - 1].stCallInfo.enCallState;
    *penMptyState = f_astCallMgmtEntities[callId - 1].stCallInfo.enMptyState;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetCallSubState
 ��������  : ��ȡָ�����е���״̬��Ϣ
 �������  : callId       - ��Ҫ��ȡ״̬��Ϣ�ĺ��е�ID
 �������  : ��
 �� �� ֵ  : ������״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��13��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_CALL_SUB_STATE_ENUM_UINT8 TAF_CALL_GetCallSubState(
    MN_CALL_ID_T                        callId
)
{
    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_GetCallSubState: callId error!");
        return TAF_CALL_SUB_STATE_NULL;
    }

    return f_astCallMgmtEntities[callId - 1].stCallInfo.enCallSubState;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_SetCallSubState
 ��������  : ����ָ�����е���״̬��Ϣ
 �������  : callId         - ��Ҫ����״̬��Ϣ�ĺ��е�ID
             enCallSubState - ������״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��13��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_CALL_SetCallSubState(
    MN_CALL_ID_T                        callId,
    TAF_CALL_SUB_STATE_ENUM_UINT8       enCallSubState
)
{
    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_SetCallSubState: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallSubState = enCallSubState;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_GetCallsByState
 ��������  : ��ȡ�ض�����״̬�����к���
 �������  : enCallState     - ָ���ĺ���״̬
 �������  : pulNumOfCalls - ָ��״̬�ĺ��и���
              pCallIds      - ָ��״̬�ĺ���ID�б�(����Ļ�����������7����¼)
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_GetCallsByState(
    MN_CALL_STATE_ENUM_U8               enCallState,
    VOS_UINT32                          *pulNumOfCalls,
    MN_CALL_ID_T                        *pCallIds
)
{
    VOS_UINT16                          i;

    *pulNumOfCalls = 0;

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if (enCallState == f_astCallMgmtEntities[i].stCallInfo.enCallState)
        {
            /*lint -e961*/
            *pCallIds++ = (VOS_UINT8)i + 1;
            /*lint +e961*/
            (*pulNumOfCalls)++;
        }
    }
}


/* Deleted by l00198894 for V9R1 STK����, 2013/07/11 */

/*****************************************************************************
 �� �� ��  : MN_CALL_GetNotIdleStateCalls
 ��������  : ��ȡ������Idle״̬��Call
 �������  : ��
 �������  : pulNumOfCalls - ���и���
              pCallIds - ��Ӧ�ĺ���Id
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_GetNotIdleStateCalls(
    VOS_UINT32                          *pulNumOfCalls,
    MN_CALL_ID_T                        *pCallIds
)
{
    VOS_UINT16                          i;

    *pulNumOfCalls = 0;

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if (MN_CALL_S_IDLE != f_astCallMgmtEntities[i].stCallInfo.enCallState)
        {
            /*lint -e961*/
            *pCallIds++ = (VOS_UINT8)i + 1;
            /*lint +e961*/
            (*pulNumOfCalls)++;
        }
    }
}

/*****************************************************************************
 �� �� ��  : MN_CALL_GetCallsByMptyState
 ��������  : ��ȡ�ض�MPTY״̬�����к���
 �������  : enMptyState   - ָ����MPTY״̬
 �������  : pulNumOfCalls - ָ��״̬�ĺ��и���
              pCallIds      - ָ��״̬�ĺ���ID�б�(����Ļ�����������7����¼)
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_GetCallsByMptyState(
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState,
    VOS_UINT32                          *pulNumOfCalls,
    MN_CALL_ID_T                        *pCallIds
)
{
    VOS_UINT16                          i;

    *pulNumOfCalls = 0;

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
    if (enMptyState == f_astCallMgmtEntities[i].stCallInfo.enMptyState)
        {
            /*lint -e961*/
            *pCallIds++ = (VOS_UINT8)i + 1;
            /*lint +e961*/
            (*pulNumOfCalls)++;
        }
    }

}


/*****************************************************************************
 �� �� ��  : MN_CALL_RegSsKeyEvent
 ��������  : ע�Ჹ��ҵ������Ĺ�ע�¼�
             ����ע�ĺ����Ϸ�����ע���¼�ʱ��ע��ĺ�������(enSubseqOp)
             ����ִ��; �����¼��ڷ���ʱ���������κβ���, ��������
 �������  : callId     - ��ʶ�����¼��ĺ���
              enEvt      - ��ע���¼�����
              enSubseqOp - ���¼�������Ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_RegSsKeyEvent(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvt,
    MN_CALL_SS_SUBSEQ_OP_ENUM           enSubseqOp
)
{
    VOS_UINT8   ucNumOfKeyEvt = f_stCallSupsCmdMgmt.ucNumOfKeyEvt;

    if (ucNumOfKeyEvt >= MN_CALL_MAX_SS_CMD_KEY_EVT_NUM)
    {
        MN_WARN_LOG("MN_CALL_RegSsKeyEvent: NumOfKeyEvt beyond");
        return;
    }

    /* ���һ����ע�¼�, �������������д�¼����� */
    f_stCallSupsCmdMgmt.astKeyEvts[ucNumOfKeyEvt].callId = callId;
    f_stCallSupsCmdMgmt.astKeyEvts[ucNumOfKeyEvt].enEvt = enEvt;
    f_stCallSupsCmdMgmt.astKeyEvts[ucNumOfKeyEvt].enSubseqOp = enSubseqOp;

    f_stCallSupsCmdMgmt.ucNumOfKeyEvt++;


}

/*****************************************************************************
 �� �� ��  : MN_CALL_DeRegSsKeyEvent
 ��������  : ɾ������ҵ������Ĺ�ע�¼�
 �������  : callId     - ��ʶ�����¼��ĺ���
             enEvt      - ����Ҫ��ע���¼�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2009��12��31��
    ��    ��   : z40661
    �޸�����   :�±����
*****************************************************************************/
VOS_VOID  MN_CALL_DeRegSsKeyEvent(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvt
)
{

    VOS_UINT8       ucNumOfKeyEvt = f_stCallSupsCmdMgmt.ucNumOfKeyEvt;
    VOS_UINT16      i;

    MN_CALL_ASSERT ( ucNumOfKeyEvt != 0 );

    /* ɾ����Ӧ��ע���¼� */
    for (i = 0; i < ucNumOfKeyEvt; i++)
    {
        if ((callId == f_stCallSupsCmdMgmt.astKeyEvts[i].callId)
           &&(enEvt == f_stCallSupsCmdMgmt.astKeyEvts[i].enEvt ))
        {
            break;
        }
    }

    if (i != ucNumOfKeyEvt)
    {
        PS_MEM_CPY(&f_stCallSupsCmdMgmt.astKeyEvts[i],
                   &f_stCallSupsCmdMgmt.astKeyEvts[i+1],
                   ((ucNumOfKeyEvt - i) - 1) * sizeof(MN_CALL_SUPS_CMD_ENUM_U8_KEY_EVT_STRU));
        f_stCallSupsCmdMgmt.ucNumOfKeyEvt--;
    }



}


/*****************************************************************************
 �� �� ��  : MN_CALL_ClearSsKeyEvent
 ��������  : ������еĹ�ע�¼�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ClearSsKeyEvent(VOS_VOID)
{
    f_stCallSupsCmdMgmt.ucNumOfKeyEvt = 0;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_BeginCallSupsCmdProgress
 ��������  : ��ʼ���в���ҵ�����, ��¼��ʼ��Ϣ, ���ò���ҵ����б�־
 �������  : clientId - ����ò���ҵ�������Client��ID
              enCallMgmtCmd    - ����Ĳ���ҵ�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_BeginCallSupsCmdProgress(
    MN_CLIENT_ID_T                      clientId,
    MN_CALL_SUPS_CMD_ENUM_U8            enCallSupsCmd
)
{
    /* ������ҵ�����ṹ�е�bInProgress��־��ΪTRUE
       �������ClientId��enCallMgmtCmd��¼������ҵ�����ṹ�� */
    f_stCallSupsCmdMgmt.bInProgress = VOS_TRUE;
    f_stCallSupsCmdMgmt.enCallSupsCmd = enCallSupsCmd;
    f_stCallSupsCmdMgmt.clientId = clientId;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_IsCallSupsCmdInProgress
 ��������  : �鿴��ǰ�Ƿ��ڽ��в���ҵ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE - ���ڽ��в���ҵ�����,  VOS_FALSE - û�н��в���ҵ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL  MN_CALL_IsCallSupsCmdInProgress(VOS_VOID)
{
    return  f_stCallSupsCmdMgmt.bInProgress;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateCallSupsProgress
 ��������  : �������˲���ҵ�������ص��¼�ʱ, ���²���ҵ������Ľ�չ.
             �ú������ݷ������¼�����ע��Ĺ�ע�¼��������ض�����.
 �������  : callId  - ��ʶ�����¼��ĺ���
             enEvt   - �������¼�����
             ulErrno - ����ǲ����ܾ�����¼�, ��ҪЯ�������룬�ò���ֻ����
                       ���ϲ��ϱ�����ʧ��ʱ����Ч.
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2013��07��09��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ

  4.��    ��   : 2013��12��28��
    ��    ��   : j00174725
    �޸�����   : HSUART PHASE III
  5.��    ��   : 2014��7��29��
    ��    ��   : b00269685
    �޸�����   : ����澯����
  6.��    ��   : 2014��12��17��
    ��    ��   : l00198894
    �޸�����   : DTS2014121602595: AT+CHLD=2�쳣���̴���
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCallSupsProgress(
    MN_CALL_ID_T                        callId,
    MN_CALL_SS_PROGRESS_EVT_ENUM        enEvt,
    VOS_UINT32                          ulErrno
)
{
    VOS_UINT16                          i;
    VOS_BOOL                            bOpCmplt = VOS_FALSE;
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateCallSupsProgress: callId error!");
        return;
    }

    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));


    MN_INFO_LOG3("MN_CALL_UpdateCallSupsProgress: callId, event, ulErrno", callId, (VOS_INT32)enEvt, (VOS_INT32)ulErrno);

    /* �ж��Ƿ��Ѿ������к�����ز���ҵ�� */
    if (VOS_FALSE == MN_CALL_IsCallSupsCmdInProgress())
    {
        MN_WARN_LOG("MN_CALL_UpdateCallSupsProgress: No Cmd In Progress");
        return;
    }

    /* ����ע��Ĺ�ע�¼���Ѱ���������CallId��enEvtƥ����¼� */
    for (i = 0; i < f_stCallSupsCmdMgmt.ucNumOfKeyEvt; i++)
    {
        if (( callId == f_stCallSupsCmdMgmt.astKeyEvts[i].callId )
          &&( enEvt == f_stCallSupsCmdMgmt.astKeyEvts[i].enEvt ))
        {
            break;
        }
    }

    if ( i == f_stCallSupsCmdMgmt.ucNumOfKeyEvt )
    {
        MN_NORM_LOG("MN_CALL_UpdateCallSupsProgress: No Key Evt");
        return;
    }

    MN_INFO_LOG1("MN_CALL_UpdateCallSupsProgress: SubseqOp, ", f_stCallSupsCmdMgmt.astKeyEvts[i].enSubseqOp);

    switch(f_stCallSupsCmdMgmt.astKeyEvts[i].enSubseqOp)
    {
        case MN_CALL_SS_SUBSEQ_OP_RPT_SUCC:
            f_astCallMgmtEntities[callId - 1].stCallInfo.enSsResult = MN_CALL_SS_RES_SUCCESS;
            bOpCmplt = VOS_TRUE;
            break;

        case MN_CALL_SS_SUBSEQ_OP_RPT_FAIL:
            f_astCallMgmtEntities[callId - 1].stCallInfo.enSsResult = MN_CALL_SS_RES_FAIL;
            f_astCallMgmtEntities[callId - 1].stCallInfo.enSsErrCode = (VOS_UINT8)ulErrno;
            bOpCmplt = VOS_TRUE;
            break;

        case MN_CALL_SS_SUBSEQ_OP_ACCPT_OTH:
            MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aCallIds);
            if (0 != ulNumOfCalls)
            {
                /* ����HOLD_CNF��REL�¼�����������һ·�绰����Ҫȥע����һ���¼� */
                if (MN_CALL_SS_PROG_EVT_HOLD_CNF == enEvt)
                {
                    MN_CALL_DeRegSsKeyEvent(callId, MN_CALL_SS_PROG_EVT_REL);
                }

                if (MN_CALL_SS_PROG_EVT_REL == enEvt)
                {
                    MN_CALL_DeRegSsKeyEvent(callId, MN_CALL_SS_PROG_EVT_HOLD_CNF);
                }

                MN_INFO_LOG2("MN_CALL_UpdateCallSupsProgress: accept other: waiting, NumOfCalls, callId",(VOS_INT32)ulNumOfCalls, aCallIds[0]);
                /*�����ڵȴ��ĺ���, �����ú���*/
                MN_CALL_CallAnswerReqProc(f_stCallSupsCmdMgmt.clientId,
                                          f_stCallSupsCmdMgmt.opId,
                                          aCallIds[0],
                                          VOS_NULL_PTR);

                /* ֹͣMN_CALL_TID_RING��ʱ�� */
                MN_CALL_StopTimer(MN_CALL_TID_RING);

                /* ���¸ú��е�Client��Ϣ */
                MN_CALL_UpdateClientId(aCallIds[0], f_stCallSupsCmdMgmt.clientId);

                /* ��ע�ú��е����ӽ����ɹ��¼�, ��������Ϊ�ϱ������ɹ� */
                MN_CALL_RegSsKeyEvent(aCallIds[0],
                                      MN_CALL_SS_PROG_EVT_SETUP_COMPL,
                                      MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);
                /* ��ע�ú��еĹҶ�����¼�, ��������Ϊ�ϱ�����ʧ�� */
                MN_CALL_RegSsKeyEvent(aCallIds[0],
                                      MN_CALL_SS_PROG_EVT_REL,
                                      MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);
                break;
            }

            MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfCalls, aCallIds);
            if ( 0 != ulNumOfCalls )
            {
                enMptyState = MN_CALL_MPYT_STATE_BUTT;
                MN_CALL_GetCallState(aCallIds[0], &enCallState, &enMptyState);
                if ( MN_CALL_IN_MPTY == enMptyState)
                {
                    MN_INFO_LOG2("MN_CALL_UpdateCallSupsProgress: accept other: held in mpty NumOfCalls, callId",(VOS_INT32)ulNumOfCalls, aCallIds[0]);
                    /* �ָ�MPTY */
                    MN_CALL_SendCcSimpleFacility(aCallIds[0],
                                                 MN_CALL_SS_RETRIEVEMPTY_OPERATION);
                }
                else
                {
                    MN_INFO_LOG2("MN_CALL_UpdateCallSupsProgress: accept other: held not in mpty NumOfCalls, callId",(VOS_INT32)ulNumOfCalls, aCallIds[0]);
                    /* �ָ��ú��� */
                    MN_CALL_SendCcRetrieveReq(aCallIds[0]);
                }

                /* ���¸ú��е�Client��Ϣ */
                MN_CALL_UpdateClientId(aCallIds[0], f_stCallSupsCmdMgmt.clientId);

                /* ��ע�ú��еĻָ��ɹ��¼�, ��������Ϊ�ϱ������ɹ� */
                MN_CALL_RegSsKeyEvent(aCallIds[0],
                                  MN_CALL_SS_PROG_EVT_RETRIEVE_CNF,
                                  MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);
                /* ��ע�ú��еĻָ����ܾ��¼�, ��������Ϊ�ϱ�����ʧ�� */
                MN_CALL_RegSsKeyEvent(aCallIds[0],
                                  MN_CALL_SS_PROG_EVT_RETRIEVE_REJ,
                                  MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);
                break;
            }

            f_astCallMgmtEntities[callId - 1].stCallInfo.enSsResult = MN_CALL_SS_RES_SUCCESS;
            bOpCmplt = VOS_TRUE;
            break;

        default:
            MN_NORM_LOG("MN_CALL_UpdateCallSupsProgress: wrong enSubseqOp");
            return;
    }

    if ( VOS_TRUE == bOpCmplt )
    {
        /* ����ҵ�������� */
        /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
        MN_CALL_ReportEvent(callId, MN_CALL_EVT_SS_CMD_RSLT);
        /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */
        MN_CALL_ClearSsKeyEvent();
        f_stCallSupsCmdMgmt.bInProgress = VOS_FALSE;
        MN_INFO_LOG("MN_CALL_UpdateCallSupsProgress: clear event & not in progress");
    }
    else
    {
        MN_CALL_DeRegSsKeyEvent(callId, enEvt);
        MN_CALL_ReportEvent(callId, MN_CALL_EVT_SS_CMD_PROGRESS);
        MN_INFO_LOG("MN_CALL_UpdateCallSupsProgress: DeReg event");
    }

}


/*****************************************************************************
 �� �� ��  : MN_CALL_GetCallInfoList
 ��������  : ��ȡ��ǰ����״̬��ΪIDLE�ĺ�����Ϣ
 �������  : pucNumOfCalls - �����������ܴ洢�ĺ�����Ϣ����
 �������  : pucNumOfCalls - ʵ�������(״̬��ΪIDLE��)������Ϣ����
              pstCallInfos  - ����ĺ�����Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_GetCallInfoList(
    TAF_UINT8                           *pucNumOfCalls,
    MN_CALL_INFO_STRU                   *pstCallInfos
)
{
    VOS_UINT16                          i;

    *pucNumOfCalls = 0;

    /*�������к��п���ʵ��*/
    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == f_astCallMgmtEntities[i].bUsed)
          &&(MN_CALL_S_IDLE != f_astCallMgmtEntities[i].stCallInfo.enCallState))

        {

            PS_MEM_CPY(pstCallInfos,
                       &(f_astCallMgmtEntities[i].stCallInfo),
                       sizeof(MN_CALL_INFO_STRU));
            (*pucNumOfCalls)++;
            pstCallInfos++;
        }

        /*
        if ���и������������������ܴ洢�ĺ�����Ϣ����
            �˳�ѭ��
        */
    }


}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetCallNum
 ��������  :��ȡ��ǰ�������е���Ŀ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ucNumOfCalls
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��03��08��
    ��    ��   : l00356716
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8  TAF_CALL_GetCallNum(VOS_VOID)
{
    VOS_UINT8           ucNumOfCalls = 0;
    VOS_UINT8           i;

    /*�������к��п���ʵ��*/
    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if ( (VOS_TRUE == f_astCallMgmtEntities[i].bUsed)
        && (MN_CALL_S_IDLE != f_astCallMgmtEntities[i].stCallInfo.enCallState) )
        {
            ucNumOfCalls++;
        }
    }

    return ucNumOfCalls;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_TiUsedCheck
 ��������  : ��鵱ǰTi�Ƿ�����ĳ������ʵ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE - Ti�Ѿ���ʹ��,  VOS_FALSE - Ti��δʹ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL  MN_CALL_TiUsedCheck(
    VOS_UINT32                          ulTi
)
{
    VOS_UINT16                          i;

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        /* �����ǰ��Ti������ĳ���Ѿ����ڵĺ��У����� TRUE */
        if ((VOS_TRUE == f_astCallMgmtEntities[i].bUsed)
          &&(f_astCallMgmtEntities[i].ulTi == ulTi))
        {
            return  VOS_TRUE;
        }
    }
    return VOS_FALSE;

}


/*****************************************************************************
 �� �� ��  : MN_CALL_CheckNotIdleStateExist
 ��������  : �ж���ǰ�Ƿ��з�Idle̬��ʵ�����
 �������  : CallState     - ָ���ĺ���״̬
 �������  : pulNumOfCalls - ָ��״̬�ĺ��и���
             pCallIds      - ָ��״̬�ĺ���ID�б�(����Ļ�����������7����¼)
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL  MN_CALL_CheckNotIdleStateExist( VOS_VOID )
{
    VOS_UINT16                          i;

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        /* �����ǰ��ǰ����ʹ�õ�ʵ�� */
        if ((VOS_TRUE == f_astCallMgmtEntities[i].bUsed)
          &&(MN_CALL_S_IDLE != f_astCallMgmtEntities[i].stCallInfo.enCallState))
        {
            return  VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_CheckCallEntityExist
 ��������  : �ж���ǰָ��call id��ʵ���Ƿ����
 �������  : callId     - ָ���ĺ���ID
 �������  :
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_BOOL  MN_CALL_CheckCallEntityExist(
    MN_CALL_ID_T                        callId
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_CheckCallEntityExist: callId error!");
        return VOS_FALSE;
    }

    if (VOS_TRUE == f_astCallMgmtEntities[callId - 1].bUsed)
    {
        return  VOS_TRUE;
    }

    return VOS_FALSE;
}



/*****************************************************************************
 Prototype      : MN_CALL_InvokeIdAlloc()
 Description    : ����InvokeId���˺���Ϊԭ���Ĵ��������ֲ
 Input          : ucCallId: ���б�ʶ
 Output         : *pInvokeId: �����InvokeId
 Return Value   : VOS_OK    ����ɹ�
                : VOS_ERR ����ʧ��
 Calls          :
 Called By      :

 History        :
  1.Date        : 2005-08-19
    Author      : cjh
    Modification: Created function
*****************************************************************************/
VOS_INT32 MN_CALL_InvokeIdAlloc(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           *pInvokeId,
    VOS_UINT8                           ucOperateCode
)
{
    VOS_UINT8                          i;

    /* �ӵ�ǰ��index��ʼ����InvokeId */
    for (i=f_stCallSupsCmdMgmt.ucInvokeId; i<MN_CALL_MAX_INVOKE_NUM; i++)
    {
        if (VOS_FALSE == g_stCallInvokeIdTable[i].bUsed)
        {
            *pInvokeId = (VOS_UINT8)i;
            g_stCallInvokeIdTable[i].bUsed = VOS_TRUE;
            g_stCallInvokeIdTable[i].ucCallId = ucCallId;
            g_stCallInvokeIdTable[i].ucInvokeId = (VOS_UINT8)i;
            g_stCallInvokeIdTable[i].ucOperateCode = ucOperateCode;

            f_stCallSupsCmdMgmt.ucInvokeId = i+1;

            return VOS_OK;
        }
    }

    /* ��ת���������0��ʼ */
    for(i=0; i<f_stCallSupsCmdMgmt.ucInvokeId; i++)
    {
        if( VOS_FALSE == g_stCallInvokeIdTable[i].bUsed )
        {
            *pInvokeId = (VOS_UINT8)i;
            g_stCallInvokeIdTable[i].bUsed = VOS_TRUE;
            g_stCallInvokeIdTable[i].ucCallId = ucCallId;
            g_stCallInvokeIdTable[i].ucInvokeId = (VOS_UINT8)i;
            g_stCallInvokeIdTable[i].ucOperateCode = ucOperateCode;

            f_stCallSupsCmdMgmt.ucInvokeId = i+1;

            return VOS_OK;
        }
    }

    return VOS_ERR;
}
/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateAlsLineInfo
 ��������  : �����ڴ��NVIM�е�LINE��Ϣ
 �������  : enAlsLine :ѡ�����·��
 �������  : ��
 �� �� ֵ  : VOS_OK:�ɹ�
             VOS_ERR:ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��22��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
  3.��    ��   : 2013��6��5��
    ��    ��   : w00242748
    �޸�����   : SVLTE��USIM�ӿ�����
*****************************************************************************/
VOS_UINT32 MN_CALL_UpdateAlsLineInfo(
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLine,
    VOS_BOOL                            bUpdateNvim
)
{
    MN_CALL_ALS_LINE_INFO_STRU          stAlsLineInfo;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulGetCardImsiRslt;

    ulGetCardImsiRslt   = USIMM_API_RESULT_BUTT;

    ulLength = 0;
    PS_MEM_SET(&stAlsLineInfo,0,sizeof(stAlsLineInfo));

    if ( VOS_FALSE == bUpdateNvim )
    {
        f_enAlsLineNo = enAlsLine;
        return VOS_OK;
    }

    /* ��ȡIMSI�� */
    ulGetCardImsiRslt   = NAS_USIMMAPI_GetCardIMSI(stAlsLineInfo.aucMmaImsi);
    if ( USIMM_API_SUCCESS !=  ulGetCardImsiRslt)
    {
        if (VOS_TRUE == TAF_SDC_IsImsiAvailableInCurrSimStatus(TAF_SDC_GetSimStatus()))
        {

#if (FEATURE_ON == FEATURE_PTM)
            /* ��¼��ȡ��IMSI�쳣log */
            TAF_SDC_GetCardImsiFailRecord(ulGetCardImsiRslt, stAlsLineInfo.aucMmaImsi);
#endif
        }

        return VOS_ERR;
    }

    stAlsLineInfo.enAlsLine = enAlsLine;

     /* д��NVIM��*/
     (VOS_VOID)NV_GetLength(en_NV_Item_ALS_LINE_Config, &ulLength);
    if ( NV_OK != NV_Write(en_NV_Item_ALS_LINE_Config, &stAlsLineInfo, ulLength) )
    {
        return VOS_ERR;
    }

    f_enAlsLineNo = enAlsLine;

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_GetAlsLineInfo
 ��������  : ��ȡ��ǰʹ����·��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �û���ǰʹ�õ���·��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��22��
    ��    ��   : z40661
    �޸�����   : �����ɺ���

*****************************************************************************/
MN_CALL_ALS_LINE_NO_ENUM_U8  MN_CALL_GetAlsLineInfo( VOS_VOID )
{
    return f_enAlsLineNo;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateAlsLineNbr
 ��������  : ����ָ������ʹ�õ���·����Ϣ
 �������  : callId - ��Ҫ����״̬�ĺ��е�ID
             enAlsLineNbr - �µ���·��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��25��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateAlsLineNbr(
    MN_CALL_ID_T                        callId,
    MN_CALL_ALS_LINE_NO_ENUM_U8         enAlsLineNbr
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateAlsLineNbr: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.enAlsLineNo = enAlsLineNbr;

    MN_INFO_LOG1("MN_CALL_UpdateAlsLineNbr: LineNumber,", enAlsLineNbr);

}

/*****************************************************************************
 Prototype      : MN_CALL_CallCtrlProcess
 Description    : ����USIMģ���ṩ��call control�ӿڣ�����Envelop�����USIMģ��
 Input          : pstParam - ���е���Ϣ��������дEnvelop�����е���Ӧ����
 Output         :
 Return Value   : VOS_OK    - �����ɹ�
                : VOS_ERR - ����ʧ��
 Calls          :
 Called By      :

 History        :
  1.Date        : 2008-08-19
    Author      : huwen
    Modification: Created function
*****************************************************************************/
VOS_UINT32 MN_CALL_CallCtrlProcess(
    MN_CALL_ORIG_PARAM_STRU             *pstParam
)
{
    /* �ú�����Ҫ�ȴ������ṩ�ӿ� */
    return VOS_OK;
}

/*****************************************************************************
 Prototype      : MN_CALL_SsOpCodeTransToSsEvent
 Description    : ��������ת���ɶ�Ӧ���¼�
 Input          : sSOpCode - ������
 Output         : penEvent - ��Ӧ���¼�
 Return Value   : VOS_OK    - ת���ɹ�
                : VOS_ERR   - ת��ʧ��
 Calls          :
 Called By      :

 History        :
  1.Date        : 2007-03-26
    Author      : h44270
    Modification: Created function
*****************************************************************************/
VOS_UINT32  MN_CALL_SsOpCodeTransToSsEvent(
    MN_CALL_SS_OPERATION_CODE_T         sSOpCode,
    MN_CALL_SS_PROGRESS_EVT_ENUM        *penEvent
)
{
    switch (sSOpCode)
    {
    case MN_CALL_SS_SPLITMPTY_OPERATION:
        *penEvent = MN_CALL_SS_PROG_EVT_SPLIT_MPTY_REJ;
        break;

    case MN_CALL_SS_RETRIEVEMPTY_OPERATION:
        *penEvent = MN_CALL_SS_PROG_EVT_RETRIEVE_REJ;
        break;

    case MN_CALL_SS_HOLDMPTY_OPERATION:
        *penEvent = MN_CALL_SS_PROG_EVT_HOLD_REJ;
        break;

    case MN_CALL_SS_BUILDMPTY_OPERATION:
        *penEvent = MN_CALL_SS_PROG_EVT_BUILD_MPTY_REJ;
        break;

    /* �ݲ�֧��AOC
    case MN_CALL_SS_AOC_OPERATION:

        break;
    */

    case MN_CALL_SS_ECT_OPERATION:
        *penEvent = MN_CALL_SS_PROG_EVT_ECT_REJ;
        break;

    default:
        MN_WARN_LOG("MN_CALL_SsOpCodeTransToSsEvent: Op Code Error");
        return VOS_ERR;
    }

    return VOS_OK;
}
/*****************************************************************************
 Prototype      : MN_CALL_InCall
 Description    : �ж���ǰ�Ƿ���ں���
 Input          : ��
 Output         : ��
 Return Value   : VOS_TRUE    - ���ں���
                : VOS_FALSE   - �����ں���
 Calls          :
 Called By      :

 History        :
  1.Date        : 2007-03-26
    Author      : h44270
    Modification: Created function
*****************************************************************************/
VOS_BOOL  MN_CALL_InCall(VOS_VOID)
{
    VOS_UINT8                   i;

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == f_astCallMgmtEntities[i].bUsed) &&
            (MN_CALL_S_IDLE != f_astCallMgmtEntities[i].stCallInfo.enCallState))

        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 Prototype      : TAF_CALL_ProcRelCallSsKeyEvent
 Description    : ����ҵ���ڽ����ж��쳣״̬����Ӧ����
 Input          : callId
 Output         : ��
 Return Value   : ��
 Calls          :
 Called By      :

 History        :
  1.��    ��   : 2008��7��12��
    ��    ��   : ���� 44270
    �޸�����   : �����ɺ��������ⵥ��:AT2D04057
  2.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
*****************************************************************************/
VOS_VOID  TAF_CALL_ProcRelCallSsKeyEvent(
    MN_CALL_ID_T                        callId
)
{
    VOS_UINT32                          i;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT32                          ulNumOfCalls;


    /*Ѱ����Ҫ�����Ӧ�¼���CallID*/
    /* ����ע��Ĺ�ע�¼���Ѱ���������CallId��enEvtƥ����¼� */
    for (i = 0; i < f_stCallSupsCmdMgmt.ucNumOfKeyEvt; i++)
    {
        if ( callId == f_stCallSupsCmdMgmt.astKeyEvts[i].callId )
        {
            switch(f_stCallSupsCmdMgmt.astKeyEvts[i].enEvt)
            {
             case MN_CALL_SS_PROG_EVT_HOLD_CNF:

                /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
                TAF_CALL_ProcRelCallHoldRetrieveSsKeyEvent(callId, MN_CALL_SS_PROG_EVT_HOLD_CNF);
                /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
                break;

            case MN_CALL_SS_PROG_EVT_RETRIEVE_CNF:
                /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
                TAF_CALL_ProcRelCallHoldRetrieveSsKeyEvent(callId, MN_CALL_SS_PROG_EVT_RETRIEVE_CNF);
                /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
                break;

            case MN_CALL_SS_PROG_EVT_BUILD_MPTY_CNF:
                MN_CALL_UpdateCallSupsProgress(callId,
                                               MN_CALL_SS_PROG_EVT_BUILD_MPTY_REJ,
                                               MN_CALL_ERR_SS_UNSPECIFIC);
                break;

            case MN_CALL_SS_PROG_EVT_SPLIT_MPTY_CNF:
                MN_CALL_UpdateCallSupsProgress(callId,
                                               MN_CALL_SS_PROG_EVT_SPLIT_MPTY_REJ,
                                               MN_CALL_ERR_SS_UNSPECIFIC);
                break;

            case MN_CALL_SS_PROG_EVT_DEFLECT_CNF:
                MN_CALL_UpdateCallSupsProgress(callId,
                                               MN_CALL_SS_PROG_EVT_DEFLECT_REJ,
                                               MN_CALL_ERR_SS_UNSPECIFIC);
                break;

            case MN_CALL_SS_PROG_EVT_ACT_CCBS_CNF:
                MN_CALL_UpdateCallSupsProgress(callId,
                                               MN_CALL_SS_PROG_EVT_ACT_CCBS_REJ,
                                               MN_CALL_ERR_SS_UNSPECIFIC);
                break;

            case MN_CALL_SS_PROG_EVT_ECT_CNF:
                /*ECT����������callId,�Բ�ͬ��callIdע���˲�ͬ�Ĺ�ע�¼���ֻ��Ҫ
                �����ӦcallId��ע���¼� */
                MN_CALL_GetNotIdleStateCalls(&ulNumOfCalls, aCallIds);
                if (2 == ulNumOfCalls)
                {
                    MN_CALL_DeRegSsKeyEvent(callId,MN_CALL_SS_PROG_EVT_ECT_CNF);
                    MN_CALL_DeRegSsKeyEvent(callId,MN_CALL_SS_PROG_EVT_ECT_REJ);
                }
                else
                {
                    MN_CALL_UpdateCallSupsProgress(callId,
                                                   MN_CALL_SS_PROG_EVT_ECT_REJ,
                                                   MN_CALL_ERR_SS_UNSPECIFIC);
                }
                break;

            default:
                break;
            }
        }
    }

}

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateCcbsSetup
 ��������  : ����ȫ�ֱ���f_stCcbsSetup������
 �������  : pstCcbsSetup - Mo setup����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
  1.��    ��  : 2009-12-25
    ��    ��  : z00161729
    �޸�����  : �����ɺ�����
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCcbsSetup(
    const NAS_CC_MSG_SETUP_MO_STRU   *pstCcbsSetup
)
{
    PS_MEM_CPY(&f_stCcbsSetup, pstCcbsSetup, sizeof(NAS_CC_MSG_SETUP_MO_STRU));
}
/*****************************************************************************
 �� �� ��  : MN_CALL_GetCcbsSetup
 ��������  :��ȡȫ�ֱ���f_stCcbsSetup������
 �������  :pstCcbsSetup - Mo setup����
 �������  :��
 �� �� ֵ  :��
 ���ú���  :
 ��������  :

 �޸���ʷ       :
  1.��    ��    : 2009-12-25
    ��    ��    : z00161729
    �޸�����    : �����ɺ�����
*****************************************************************************/
VOS_VOID  MN_CALL_GetCcbsSetup(
    NAS_CC_MSG_SETUP_MO_STRU   *pstCcbsSetup
)
{
    PS_MEM_CPY(pstCcbsSetup, &f_stCcbsSetup, sizeof(NAS_CC_MSG_SETUP_MO_STRU));
}

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateCcCallDir
 ��������  : ���º��еķ���
 �������  : callId - ���е�ID
             enCallDir - ���еķ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009-12-25
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID MN_CALL_UpdateCcCallDir(
    MN_CALL_ID_T                        callId,
    MN_CALL_DIR_ENUM_U8                 enCallDir
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateCcCallDir: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId-1].stCallInfo.enCallDir = enCallDir;
}
/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateCcbsSupsProgress
 ��������  : �������˲���ҵ�������ص��¼�ʱ, ���²���ҵ������Ľ�չ.
             �ú������ݷ������¼�����ע��Ĺ�ע�¼��������ض�����.
 �������  : callId     - ��ʶ�����¼��ĺ���
             ulErrno    - ����ǲ����ܾ�����¼�, ��ҪЯ�������룬�ò���ֻ����
                          ���ϲ��ϱ�����ʧ��ʱ����Ч.
             enSsResult - �������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009-12-25
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateCcbsSupsProgress(
    MN_CALL_ID_T                        callId,
    VOS_UINT32                          ulErrno,
    MN_CALL_SS_RESULT_ENUM_U8           enSsResult
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateCcbsSupsProgress: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.enSsResult = enSsResult;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enSsErrCode = (VOS_UINT8)ulErrno;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallSupsCmd
                = MN_CALL_SUPS_CMD_ACT_CCBS;
    MN_CALL_ReportEvent(callId, MN_CALL_EVT_TIME_EXPIRED);
    f_stCallSupsCmdMgmt.bInProgress = VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateRecallSupsProgress
 ��������  : �������˲���ҵ�������ص��¼�ʱ, ���²���ҵ������Ľ�չ.
             �ú������ݷ������¼�����ע��Ĺ�ע�¼��������ض�����.
 �������  : callId  - ��ʶ�����¼��ĺ���
             ulErrno - ����ǲ����ܾ�����¼�, ��ҪЯ�������룬�ò���ֻ����
                       ���ϲ��ϱ�����ʧ��ʱ����Ч.
             enSsResult - �������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009-12-25
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2013��07��09��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateRecallSupsProgress(
    MN_CALL_ID_T                        callId,
    VOS_UINT32                          ulErrno,
    MN_CALL_SS_RESULT_ENUM_U8           enSsResult
)
{

    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateRecallSupsProgress: callId error!");
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.enSsResult = enSsResult;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enSsErrCode = (VOS_UINT8)ulErrno;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallSupsCmd
            = MN_CALL_SUPS_CMD_ACT_CCBS;
    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */
    MN_CALL_ReportEvent(callId, MN_CALL_EVT_SS_CMD_RSLT);
    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */
    f_stCallSupsCmdMgmt.bInProgress = VOS_FALSE;

}


/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateRbId
 ��������  : ˢ��RbId
 �������  : ��
 �������  : pulNumOfCalls - ���и���
              pCallIds - ��Ӧ�ĺ���Id
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_UpdateRbId(
    MN_CALL_ID_T                        callId,
    VOS_UINT32                          ulRbId
)
{
    f_astCallMgmtEntities[callId - 1].bRbSet = VOS_TRUE;
    f_astCallMgmtEntities[callId - 1].ulRbId = ulRbId;

}

/*****************************************************************************
 �� �� ��  : MN_CALL_GetRbId
 ��������  : ����CallId��ȡRbId
 �������  : callId - ���е�ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 MN_CALL_GetRbId(MN_CALL_ID_T callId)
{
    return f_astCallMgmtEntities[callId - 1].ulRbId;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_SetVideoCallChannelOpenFlg
 ��������  : ���ÿ��ӵ绰ҵ���ŵ��Ѿ�������ʶ
 �������  : bVideoCallChannelOpenFlg - ���ӵ绰�ŵ��򿪱�־
             callId                   - ����ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��6��1��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALL_SetVideoCallChannelOpenFlg(
    VOS_BOOL                            bVideoCallChannelOpenFlg,
    MN_CALL_ID_T                        callId
)
{
    f_astCallMgmtEntities[callId - 1].bVpChannelOpenFlg = bVideoCallChannelOpenFlg;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_GetVideoCallChannelOpenFlg
 ��������  : ��ѯ���ӵ绰ҵ���ŵ��Ƿ�򿪱�ʶ
 �������  : callId                   - ����ID
 �������  : ��
 �� �� ֵ  : VOS_TRUE - ���ӵ绰ҵ���ŵ���
             VOS_FALSE - ���ӵ绰ҵ���ŵ�δ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��6��1��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL MN_CALL_GetVideoCallChannelOpenFlg(
    MN_CALL_ID_T                        callId
)
{
    return f_astCallMgmtEntities[callId - 1].bVpChannelOpenFlg;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_ConCallMsgTypeToCcMsgType
 ��������  : ��CALLL�Ķ������Ϣ����ת��ΪCC�������Ϣ����
 �������  : enCallMsgType :  CALL������Я��UUS1����Ϣ
 �������  : penCcMsgType  :  CC�������Ϣ����
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��27��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 MN_CALL_ConCallMsgTypeToCcMsgType(
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      enCallMsgType,
    NAS_CC_MSG_TYPE_ENUM_U8             *penCcMsgType
)
{
    VOS_UINT32                          i;

    /* ��MNCALLAPI�������Ϣ����ת��ΪCC�������Ϣ���� */
    for ( i = 0 ; i < (sizeof(f_stCallMsgType)/sizeof(MN_CALL_MATCH_MSG_TYPE_STRU)) ; i++ )
    {
        if ( enCallMsgType == f_stCallMsgType[i].enCallMsgType)
        {
            *penCcMsgType = f_stCallMsgType[i].enCcMsgType;
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_ConCcMsgTypeToCallMsgType
 ��������  : ��CC����Ϣ����ת��ΪCALL����Ϣ����
 �������  : enCcMsgType    :CC�������Ϣ����
 �������  : penCallMsgType :CALL�������Ϣ����
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��28��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 MN_CALL_ConCcMsgTypeToCallMsgType(
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgType,
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      *penCallMsgType
)
{
    VOS_UINT32                          i;

    /* ��CC�������Ϣ����ת��ΪMNCALLAPI�������Ϣ���� */
    for ( i = 0 ; i < (sizeof(f_stCallMsgType)/sizeof(MN_CALL_MATCH_MSG_TYPE_STRU)) ; i++ )
    {
        if ( enCcMsgType == f_stCallMsgType[i].enCcMsgType)
        {
            *penCallMsgType = f_stCallMsgType[i].enCallMsgType;
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateRptUus1Info
 ��������  : �����ϱ�Call��Ϣ��UUS1ֵ
 �������  : callId         :����ID
             enCcMsgType    :����µ���Ϣ����
             pstUserUser    :UUS1��Ϣ

 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��28��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_CALL_UpdateRptUus1Info(
    MN_CALL_ID_T                        callId,
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgType,
    NAS_CC_IE_USER_USER_STRU            *pstUserUser
)
{
    MN_CALL_ConCcUusInfoToCall(enCcMsgType,
                               pstUserUser,
                               &f_astCallMgmtEntities[callId - 1].stCallInfo.stUusInfo);

    return;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_ConCcUusInfoToCall
 ��������  : ��CC��UUS��Ϣ��ʽת��Ϊ���ϱ�����Ϣ��ʽ
 �������  : enCcMsgType        :��ת������Ϣ����
             pstUserUser        :CC�ϱ���UUS����Ϣ��ʽ
 �������  : pstUus1Info        :ת�����ϱ���UUS����Ϣ��ʽ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��28��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_CALL_ConCcUusInfoToCall(
    NAS_CC_MSG_TYPE_ENUM_U8             enCcMsgType,
    NAS_CC_IE_USER_USER_STRU            *pstUserUser,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info
)
{
    VOS_UINT32                          ulRet;

    /* �Ƚ�CC����Ϣ����ת��ΪCALL����Ϣ���� */
    ulRet = MN_CALL_ConCcMsgTypeToCallMsgType(enCcMsgType,
            &pstUus1Info->enMsgType);

    if ( VOS_OK != ulRet )
    {
        pstUus1Info->enMsgType = MN_CALL_UUS1_MSG_ANY;
    }

    pstUus1Info->aucUuie[MN_CALL_IEI_POS] = MN_CALL_UUS_IEI;

    pstUus1Info->aucUuie[MN_CALL_LEN_POS] = pstUserUser->LastOctOffset;

    pstUus1Info->aucUuie[MN_CALL_PD_POS]  = pstUserUser->UserUserPD;

    PS_MEM_CPY(&(pstUus1Info->aucUuie[MN_CALL_CONTENT_POS]),
               pstUserUser->UserUserInfo,
               sizeof(pstUserUser->UserUserInfo));

    return;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_ConCallUusInfoToCc
 ��������  : ��伤��UUS1�����Ϣ
 �������  : enMsgType    :  ��ת������Ϣ����
             pstUus1Info  :  �û���Ҫ����UUS1�����Ϣ
 �������  : pstUuieInfo  :  ���͵�����UUIE��Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��7��27��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  MN_CALL_ConCallUusInfoToCc(
    MN_CALL_UUS1_MSG_TYPE_ENUM_U32      enMsgType,
    MN_CALL_UUS1_INFO_STRU              *pstUus1Info,
    NAS_CC_IE_USER_USER_STRU            *pstUuieInfo
)
{
    pstUuieInfo->IsExist = VOS_TRUE;
    pstUuieInfo->LastOctOffset = pstUus1Info->aucUuie[MN_CALL_LEN_POS];
    if ( ( MN_CALL_UUS1_MSG_SETUP  == enMsgType )
      && ( ( pstUuieInfo->LastOctOffset > MN_CALL_MAX_SETUP_UUIE_CONTEND_LEN )
        || (pstUuieInfo->LastOctOffset < MN_CALL_MIN_UUIE_CONTEND_LEN)))
    {
        return VOS_ERR;
    }
    else if ( ( pstUuieInfo->LastOctOffset > MN_CALL_MAX_OTHER_UUIE_CONTEND_LEN )
           || (pstUuieInfo->LastOctOffset < MN_CALL_MIN_UUIE_CONTEND_LEN))
    {
        return VOS_ERR;
    }
    else
    {
        ;
    }

    pstUuieInfo->UserUserPD = pstUus1Info->aucUuie[MN_CALL_PD_POS];
    if ( pstUuieInfo->LastOctOffset > 0 )
    {
        /* �˴���1��Ŀ��������ǰ��PID��ʹ��һ���ֽ� */
        PS_MEM_CPY(pstUuieInfo->UserUserInfo,
                  (pstUus1Info->aucUuie + MN_CALL_CONTENT_POS),
                  (pstUuieInfo->LastOctOffset - MN_CALL_MIN_UUIE_CONTEND_LEN));
    }

    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : NAS_CALL_SndOutsideContextData
 ��������  : ��CALL�ⲿ��������ΪSDT��Ϣ���ͳ�ȥ���Ա��ڻط�ʱͨ��׮������ԭ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��11��30��
    ��    ��   : ��ë 00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��03��
   ��    ��   : s62952
   �޸�����   : BalongV300R002 Build�Ż���Ŀ
*****************************************************************************/
VOS_VOID NAS_CALL_SndOutsideContextData()
{
    NAS_CALL_SDT_MSG_ST                      *pSndMsgCB     = VOS_NULL_PTR;
    NAS_CALL_OUTSIDE_RUNNING_CONTEXT_ST      *pstOutsideCtx;

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */


    pSndMsgCB = (NAS_CALL_SDT_MSG_ST *)PS_ALLOC_MSG(WUEPS_PID_TAF, sizeof(NAS_CALL_SDT_MSG_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        MN_ERR_LOG("NAS_CALL_SndOutsideContextData:ERROR: Alloc Memory Fail.");
        return;
    }

    pstOutsideCtx = &pSndMsgCB->stOutsideCtx;

    PS_MEM_CPY(pstOutsideCtx->pc_g_f_astCallMgmtEntities,f_astCallMgmtEntities,MN_CALL_MAX_NUM * sizeof(MN_CALL_MGMT_STRU));
    PS_MEM_CPY(&pstOutsideCtx->pc_g_f_stCallSupsCmdMgmt, &f_stCallSupsCmdMgmt,sizeof(MN_CALL_SUPS_CMD_ENUM_U8_MGMT_STRU));

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    /*CCBS���ܴ�ʱ,������Setup��Ϣ */
    if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
    {
        PS_MEM_CPY(&pstOutsideCtx->pc_g_f_stCcbsSetup, &f_stCcbsSetup,sizeof(NAS_CC_MSG_SETUP_MO_STRU));
    }

    if ( MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucAlsSupportFlg )
    {
        pstOutsideCtx->pc_g_f_enAlsLineNo                   = f_enAlsLineNo;
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */
    /* Modified by z00234330 for PCLINT����, 2014-06-24, begin */
    pstOutsideCtx->pc_g_gucTafCallStatusControl         = TAF_CALL_GetCallStatusControl();
    pstOutsideCtx->pc_g_gucTafMultiSimCallStatusControl = TAF_CALL_GetMultiSimCallStatusControl();
    pstOutsideCtx->pc_g_g_enVpNvCfgState                = TAF_CALL_GetVpCfgState();
    /* Modified by z00234330 for PCLINT����, 2014-06-24, end */

    pSndMsgCB->MsgHeader.ulReceiverPid   = WUEPS_PID_TAF;
    pSndMsgCB->MsgHeader.ulSenderPid     = WUEPS_PID_TAF;
    pSndMsgCB->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pSndMsgCB->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;

    pSndMsgCB->MsgHeader.ulLength  = sizeof(NAS_CALL_OUTSIDE_RUNNING_CONTEXT_ST) + 4;
    pSndMsgCB->MsgHeader.ulMsgName = EVT_NAS_CALL_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY;

    DIAG_TraceReport(pSndMsgCB);
    PS_FREE_MSG(WUEPS_PID_TAF, pSndMsgCB);

    return;
}

#ifdef __PS_WIN32_RECUR__
/*****************************************************************************
 �� �� ��  : NAS_CALL_RestoreContextData
 ��������  : �ָ�CALLȫ�ֱ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��12��1��
    ��    ��   : ��ë 00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ
  3.��    ��   : 2015��10��08��
    ��    ��   : zwx247453
    �޸�����   : ���cppcheck�澯

*****************************************************************************/
VOS_UINT32 NAS_CALL_RestoreContextData(struct MsgCB * pMsg)
{
    NAS_CALL_SDT_MSG_ST                      *pRcvMsgCB;
    NAS_CALL_OUTSIDE_RUNNING_CONTEXT_ST      *pstOutsideCtx;
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    MN_CALL_CUSTOM_CFG_INFO_STRU             *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */


    pRcvMsgCB     = (NAS_CALL_SDT_MSG_ST *)pMsg;

    pstOutsideCtx = &pRcvMsgCB->stOutsideCtx;

    if (EVT_NAS_CALL_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY == pRcvMsgCB->MsgHeader.ulMsgName)
    {
        PS_MEM_CPY(f_astCallMgmtEntities,pstOutsideCtx->pc_g_f_astCallMgmtEntities,MN_CALL_MAX_NUM * sizeof(MN_CALL_MGMT_STRU));
        PS_MEM_CPY(&f_stCallSupsCmdMgmt,&pstOutsideCtx->pc_g_f_stCallSupsCmdMgmt,sizeof(MN_CALL_SUPS_CMD_ENUM_U8_MGMT_STRU));

        /*CCBS���ܴ�ʱ,������Setup��Ϣ */
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
        if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
        {
            PS_MEM_CPY(&f_stCcbsSetup,&pstOutsideCtx->pc_g_f_stCcbsSetup,sizeof(NAS_CC_MSG_SETUP_MO_STRU));
        }

        if ( MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucAlsSupportFlg)
        {
            f_enAlsLineNo                   = pstOutsideCtx->pc_g_f_enAlsLineNo;
        }
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
		/* Modified by z00234330 for PCLINT����, 2014-06-24, begin */
        TAF_CALL_SetCallStatusControl(pstOutsideCtx->pc_g_gucTafCallStatusControl);
        TAF_CALL_SetMultiSimCallStatusControl(pstOutsideCtx->pc_g_gucTafMultiSimCallStatusControl);
        TAF_CALL_SetVpCfgState(pstOutsideCtx->pc_g_g_enVpNvCfgState);
        /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

        TAF_LOG(WUEPS_PID_TAF, VOS_NULL, PS_LOG_LEVEL_INFO,"CALL: NAS_CALL_RestoreContextData - data is restored.");
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#endif

/*****************************************************************************
 �� �� ��  : MN_CALL_InfoReqProc
 ��������  : ��ȡ��ǰ���к��е���Ϣ
 �������  : clientId           - ����������Client��ID
             opId               - Operation ID, ��ʶ���β���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��17��
    ��    ��   : ����/00179208
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��04��06��
    ��    ��   : l65478
    �޸�����   : DTS2012032802031:ʹ��CLCC��ѯʱ����û����ʾ
  3.��    ��   : 2012��10��29��
    ��    ��   : l00198894
    �޸�����   : DTS2012100901666: ���ӱ��к���
  4.��    ��   : 2012��12��22��
    ��    ��   : z00220246
    �޸�����   : DSDA Phase II,����SenderPid����ϱ���ClientId
  5.��    ��   : 2013��07��27��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ
  6.��    ��   : 2013��09��18��
    ��    ��   : Y00213812
    �޸�����   : ����������������Ϣ

*****************************************************************************/
VOS_VOID  MN_CALL_CallInfoReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
)
{
    MN_CALL_INFO_QRY_CNF_STRU          *pstAppCnfMsg;
    VOS_UINT16                          usLength;
    VOS_UINT16                          i;

    /* ��ʼ�� */
    usLength     = 0;

    pstAppCnfMsg = (MN_CALL_INFO_QRY_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                    sizeof(MN_CALL_INFO_QRY_CNF_STRU));

    if (VOS_NULL_PTR == pstAppCnfMsg)
    {
        return;
    }
    /* ��ȡ��ǰ����״̬��ΪIDLE�ĺ�����Ϣ */
    /*�������к��п���ʵ��*/
    (VOS_VOID)VOS_MemSet(pstAppCnfMsg, 0x00, sizeof(MN_CALL_INFO_QRY_CNF_STRU));

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == f_astCallMgmtEntities[i].bUsed)
         && (MN_CALL_S_IDLE != f_astCallMgmtEntities[i].stCallInfo.enCallState))

        {
            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-27, begin */
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].callId      = f_astCallMgmtEntities[i].stCallInfo.callId;
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].enCallDir   = f_astCallMgmtEntities[i].stCallInfo.enCallDir;
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].enCallState = f_astCallMgmtEntities[i].stCallInfo.enCallState;
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].enMptyState = f_astCallMgmtEntities[i].stCallInfo.enMptyState;
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].enCallType  = f_astCallMgmtEntities[i].stCallInfo.enCallType;
            pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].enVoiceDomain = f_astCallMgmtEntities[i].stCallInfo.enVoiceDomain;

            PS_MEM_CPY(&(pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].stCallNumber),
                       &(f_astCallMgmtEntities[i].stCallInfo.stCallNumber),
                       sizeof(MN_CALL_BCD_NUM_STRU));

            PS_MEM_CPY(&(pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].stConnectNumber),
                       &(f_astCallMgmtEntities[i].stCallInfo.stConnectNumber),
                       sizeof(MN_CALL_BCD_NUM_STRU));

            PS_MEM_CPY(&(pstAppCnfMsg->astCallInfos[pstAppCnfMsg->ucNumOfCalls].stCalledNumber),
                       &(f_astCallMgmtEntities[i].stCallInfo.stCalledNumber),
                       sizeof(MN_CALL_CALLED_NUM_STRU));
            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-27, end */

            (pstAppCnfMsg->ucNumOfCalls)++;
        }
    }

    /* ��д�¼����� */
    pstAppCnfMsg->enEvent  = MN_CALL_EVT_CLCC_INFO;
    pstAppCnfMsg->clientId = MN_GetRealClientId(clientId, WUEPS_PID_TAF);

    /* ȷ����Ϣ���� */
    usLength = (TAF_UINT16)sizeof(MN_CALL_INFO_QRY_CNF_STRU);

    /* ͨ���첽��Ϣ���͸�AT */
    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (TAF_UINT8 *)pstAppCnfMsg, usLength);

    PS_MEM_FREE(WUEPS_PID_TAF, pstAppCnfMsg);
    return;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_GetCdur
 ��������  : ��ȡָ�����е�ͨ��ʱ��
 �������  : MN_CLIENT_ID_T                      clientId  ����������Client��ID
             MN_OPERATION_ID_T                   opId      Operation ID, ��ʶ���β���
             MN_CALL_ID_T                        callId    ���е�ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��6��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��04��24��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ��:DTS2012031402745, ����ͨ�������У�at^cdur=1����ֵ��û��index

  3.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
  4.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  5.��    ��   : 2013��07��09��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseI��Ŀ
*****************************************************************************/
VOS_VOID  MN_CALL_GetCdur(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId
)
{
    VOS_UINT32                          ulCurCallTime = 0;
    VOS_UINT32                          ulCurSysTime;               /*���ڱ��浱ǰϵͳʱ��ı���*/
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    enCallState     = MN_CALL_S_BUTT;
    enMptyState     = MN_CALL_MPYT_STATE_BUTT;

    ulCurSysTime    = 0;

    if (MN_CALL_ACTIVE_SWITCH_ON != gastCallTimerCalc[callId].CallidActiveSwitch)
    {
        /* ���ڼ���̬�� ���AT_CME_INCORRECT_PARAMETERS */
        MN_WARN_LOG("MN_CALL_GetCdur: call is inactive!");

        /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-17, begin */
        /* ʧ��ʱֻ��ԭ��ֵ���ɹ�ʱ�ſ�ulCurCallTime������ʧ��ʱ���ø���ulCurCallTime */
        f_astCallMgmtEntities[callId -1].stCallInfo.enCause      = TAF_CS_CAUSE_STATE_ERROR;

        /* ���¸ú��е�Client��Ϣ */
        MN_SendClientEvent(clientId,
                           MN_CALLBACK_CS_CALL,
                           MN_CALL_EVT_GET_CDUR_CNF,
                           &f_astCallMgmtEntities[callId - 1].stCallInfo);
        /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-17, end */

        return;
    }

    /* ��ȡ��ǰϵͳʱ��: */
    ulCurSysTime = VOS_GetTick() / PRE_SECOND_TO_TICK;

    MN_CALL_GetCallState(callId, &enCallState, &enMptyState);

    if ((MN_CALL_S_ACTIVE == enCallState) || (MN_CALL_S_HELD == enCallState))
    {
        /* ��ṹ���п�ʼ����ʱ�����㣬�õ�ͨ��ʱ��: ����ʧ�����AT_ERROR */
        if ( VOS_OK != TAF_CalcTime(gastCallTimerCalc[callId].ulStartCallTime,
                                    ulCurSysTime,
                                    &ulCurCallTime ) )
        {
            MN_WARN_LOG("MN_CALL_GetCdur: Calculate the last  link time FAIL!");

            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-17, begin */
            f_astCallMgmtEntities[callId - 1].stCallInfo.enCause      = TAF_CS_CAUSE_UNKNOWN;
            /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-17, end */

            /* ���¸ú��е�Client��Ϣ */
            MN_SendClientEvent(clientId,
                               MN_CALLBACK_CS_CALL,
                               MN_CALL_EVT_GET_CDUR_CNF,
                               &f_astCallMgmtEntities[callId - 1].stCallInfo);

            return;
        }
    }
    else
    {
        /* ����ͨ��״̬��ͨ������״̬ ���AT_ERROR */
        MN_WARN_LOG("MN_CALL_GetCdur: invalid enCallState!");

        /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-17, begin */
        f_astCallMgmtEntities[callId - 1].stCallInfo.enCause      = TAF_CS_CAUSE_STATE_ERROR;
        /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-17, end */

        /* ���¸ú��е�Client��Ϣ */
        MN_SendClientEvent(clientId,
                           MN_CALLBACK_CS_CALL,
                           MN_CALL_EVT_GET_CDUR_CNF,
                           &f_astCallMgmtEntities[callId -1].stCallInfo);

        return;
    }

    /* �ϱ�Ӧ������ȷ�� */
    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, begin */

    f_astCallMgmtEntities[callId - 1].stCallInfo.ulCurCallTime = ulCurCallTime;

    f_astCallMgmtEntities[callId - 1].stCallInfo.callId        = callId;

    f_astCallMgmtEntities[callId - 1].stCallInfo.enCause       = TAF_CS_CAUSE_SUCCESS;

    /* ���¸ú��е�Client��Ϣ */
    MN_SendClientEvent(clientId,
                       MN_CALLBACK_CS_CALL,
                       MN_CALL_EVT_GET_CDUR_CNF,
                       &f_astCallMgmtEntities[callId - 1].stCallInfo);
    /* Modified by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-09, end */

    MN_NORM_LOG("MN_CALL_GetCdur: get cdur normal.");

    return;
}

/* Added by w00199382 for PS Project��2011-12-06,  Begin*/

/*****************************************************************************
 �� �� ��  : MN_CALL_RcvTafAgentGetCallInfo
 ��������  : ��ȡCID�Ĳ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��12��17��
    ��    ��   : c00173809
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��8��29��
    ��    ��   : w00242748
    �޸�����   : DTS2014082707275:��һ·���У��������ڶ�·���У����壬��ʱ�Ҷϵ�һ·����
                 (����Ҷϻ����û������Ҷ�)��ʹ��ATA�����ڶ�·�绰�������޷�������

*****************************************************************************/
VOS_VOID MN_CALL_RcvTafAgentGetCallInfo(VOS_VOID)
{
    TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU                    *pstCnf;
    VOS_UINT32                                              i;

    pstCnf = (TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                                              sizeof(TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstCnf)
    {
        MN_ERR_LOG("MN_CALL_RcvTafAgentGetCallInfo:alloc msg failed.");
        return;
    }

    PS_MEM_SET(pstCnf, 0x00, sizeof(TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU));

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if ((VOS_TRUE == f_astCallMgmtEntities[i].bUsed)
         && (MN_CALL_S_IDLE != f_astCallMgmtEntities[i].stCallInfo.enCallState))

        {
            pstCnf->stCallInfo[pstCnf->ucNumOfCalls].callId       = f_astCallMgmtEntities[i].stCallInfo.callId;
            pstCnf->stCallInfo[pstCnf->ucNumOfCalls].enCallType   = f_astCallMgmtEntities[i].stCallInfo.enCallType;
            pstCnf->stCallInfo[pstCnf->ucNumOfCalls].enCallState  = f_astCallMgmtEntities[i].stCallInfo.enCallState;

            (pstCnf->ucNumOfCalls)++;
        }
    }

    pstCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pstCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pstCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pstCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pstCnf->ulLength                      = sizeof(TAFAGERNT_MN_GET_CALL_INFO_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstCnf->enMsgId                       = ID_TAFAGENT_MN_GET_CALL_INFO_CNF;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstCnf))
    {
        MN_ERR_LOG("TAF_APS_RcvFindCidForDialReq_PreProc:send msg failed.");

        return;
    }

    return;

}

/* Added by w00199382 for PS Project��2011-12-06,  End*/

/*****************************************************************************
 �� �� ��  : MN_CALL_CreateStkMoCallEntity
 ��������  : �½�һ��STK���к��й���ʵ�壬��������Ӧ�����ݵ�ȫ�ֱ���
 �������  : callId         - ���е�ID
             enCallType     - ���е�����
             pstOrigParam   - ����������Я���Ĳ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��09��20��
    ��    ��   : f62575
    �޸�����   : STK&DCM ��Ŀ

  2.��    ��   : 2012��10��29��
    ��    ��   : l00198894
    �޸�����   : DTS2012100901666: �޸ı��к���ṹ��
  3.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  4.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ��SS FDN&Call Control�ƶ���TAF
  5.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
  6.��    ��   : 2013��08��19��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ����MTC�ϱ�����״̬

  7.��    ��   : 2013��10��18��
    ��    ��   : z00234330
    �޸�����   : dts2013101800405
  8.��    ��   : 2013��9��20��
    ��    ��   : Y00213812
    �޸�����   : VoLTE_PhaseII ���Ӻ�������Ϣ
  9.��    ��   : 2014��4��26��
    ��    ��   : z00161729
    �޸�����   : DTS2014042604200:f_abCallReleaseFlag��ʶά�����ԣ����µڶ����绰����ʱ�������·�disconnect event
 10.��    ��   : 2014��5��7��
    ��    ��   : w00242748
    �޸�����   : DTS2014050602822:STK����绰������BCD�������󣬵��µ绰û��������
                 STK���͵�USSD����������Ҫ�û�ȷ��ʱ��δ��AT�ϱ���ȷ�ϡ�
 11.��    ��   : 2015��10��10��
    ��    ��   : c00318887
    �޸�����   : DTS2015090607329
*****************************************************************************/
VOS_VOID  MN_CALL_CreateStkMoCallEntity(
    MN_CALL_ID_T                        callId,
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_APP_CALL_CALLORIG_REQ_STRU      *pstStkCallOrig
)
{
    NAS_CC_IE_BC_STRU                   stBc1CallCnf;
    MN_CALL_CS_DATA_CFG_INFO_STRU       stDataCfgInfo;
    VOS_UINT8                           ucInternalTonNumType;
    VOS_UINT8                           ucUnknownTonNumType;


    PS_MEM_SET(&stDataCfgInfo, 0x00, sizeof(stDataCfgInfo));

    ucUnknownTonNumType  = (MN_CALL_IS_EXIT | (MN_CALL_TON_UNKNOWN << 4) | MN_CALL_NPI_ISDN);
    ucInternalTonNumType = (MN_CALL_IS_EXIT | (MN_CALL_TON_INTERNATIONAL << 4) | MN_CALL_NPI_ISDN);

    /* ���ݿͻ����͵Ĳ��ֱ��ȡ������Ϣ: */
    /* ���к��� */
    /* Call Type */
    /* Call Mode */
    /* ���к������Ƶ����� */
    /* CUG Configuration */
    /* CS DATA service configration */
    /* Call SubAddress */

    /* �������������дCallId��Ӧ����ʵ���е�CallInfo���� */
    /* �������ж���,����CCʵ�廹δ����, CCʵ���е�Tiֵ������, ������ظ��ϱ�ʱ�ټ�¼ */
    PS_MEM_SET(&f_astCallMgmtEntities[callId - 1],
               0,
               sizeof(f_astCallMgmtEntities[callId - 1]));

    f_astCallMgmtEntities[callId - 1].bUsed                 = VOS_TRUE;
    f_astCallMgmtEntities[callId - 1].stCallInfo.clientId   = pstStkCallOrig->usClientId;
    f_astCallMgmtEntities[callId - 1].stCallInfo.opId       = pstStkCallOrig->opID;
    f_astCallMgmtEntities[callId - 1].stCallInfo.callId     = callId;

    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType = enCallType;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallMode = MN_CALL_MODE_SINGLE;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallDir  = MN_CALL_DIR_MO;
    f_astCallMgmtEntities[callId - 1].enClirCfg             = MN_CALL_CLIR_AS_SUBS;

    /* Added by Y00213812 for VoLTE_PhaseII ��Ŀ, 2013-9-12, begin */
    /* ������������Ϣ */
    f_astCallMgmtEntities[callId - 1].stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP;                                  /* VOICE DOMAIN */
    /* Added by Y00213812 for VoLTE_PhaseII ��Ŀ, 2013-9-12, end */

    PS_MEM_CPY(&f_astCallMgmtEntities[callId - 1].stCallInfo.stCalledNumber,
               (MN_CALL_CALLED_NUM_STRU *)&pstStkCallOrig->stCalledAddr,
               sizeof(pstStkCallOrig->stCalledAddr));

    f_astCallMgmtEntities[callId - 1].stCallInfo.stCalledNumber.enNumType |= ucUnknownTonNumType;
    f_astCallMgmtEntities[callId - 1].stCallInfo.stCalledNumber.enNumType &= ucInternalTonNumType;

    /* ֧�ֱ����ӵ�ַ */
    if ( ( pstStkCallOrig->stSubAddr.ucLen > 0)
       && (pstStkCallOrig->stSubAddr.ucLen < MN_CALL_MAX_SUBADDR_INFO_LEN))
    {
        f_astCallMgmtEntities[callId - 1].stCallInfo.stCalledSubAddr.IsExist = VOS_TRUE;
        f_astCallMgmtEntities[callId - 1].stCallInfo.stCalledSubAddr.LastOctOffset  = pstStkCallOrig->stSubAddr.ucLen;
        f_astCallMgmtEntities[callId - 1].stCallInfo.stCalledSubAddr.Octet3         = pstStkCallOrig->stSubAddr.aucSubAddr[0];
        PS_MEM_CPY(f_astCallMgmtEntities[callId - 1].stCallInfo.stCalledSubAddr.SubAddrInfo,
                  &(pstStkCallOrig->stSubAddr.aucSubAddr[1]),
                   (pstStkCallOrig->stSubAddr.ucLen - 1));
    }



    /* ��CallInfo�е�ת�ƺ�������Ӻ����еĳ����ֶζ�����Ϊ0 */
    f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectNumber.ucNumLen = 0;
    f_astCallMgmtEntities[callId - 1].stCallInfo.stConnectNumber.ucNumLen = 0;

    stBc1CallCnf.IsExist = 1;
    stBc1CallCnf.LastOctOffset = (VOS_UINT8)pstStkCallOrig->stBc.ucLen;
    PS_MEM_CPY(&stBc1CallCnf.Octet3,
               pstStkCallOrig->stBc.aucBc,
               pstStkCallOrig->stBc.ucLen);

    MN_CALL_GetDataCfgInfoFromBc(&stBc1CallCnf, &stDataCfgInfo);

    MN_CALL_UpdateDataCallCfgInfo(callId, &stDataCfgInfo);

    /* Deleted by l00198894 for V9R1 STK����, 2013/07/11 */

    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, begin */
    TAF_CALL_SetCsCallExistFlg(VOS_TRUE, f_astCallMgmtEntities[callId - 1].stCallInfo.enCallType);
    /* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, end */

    MN_CALL_UpdateCallReleaseFlag(callId, VOS_FALSE);

    /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* ��MTCģ���ϱ���ǰCS��ҵ��״̬ */
    TAF_SendMtcCsSrvInfoInd();
#endif
    /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, end */

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_GetCallReleaseFlag
 ��������  : ��ȡ����ʵ����ͷ�״̬
 �������  : VOS_UINT8                           ucCallId  ����ʵ������
 �������  : VOS_BOOL                           *pbReleaseFlag  �����ͷű�־����һ���ͷ�������λ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��20��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALL_GetCallReleaseFlag(
    VOS_UINT8                           ucCallId,
    VOS_BOOL                           *pbReleaseFlag
)
{
    *pbReleaseFlag = f_abCallReleaseFlag[ucCallId - 1];
    return;

}

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateSubAddress
 ��������  : ��ȡ����ʵ����ӵ�ַ
 �������  : VOS_UINT8                           ucCallId         ����ʵ������
             MN_CALL_SUBADDR_STRU               *pstSubCallNumber �ӵ�ַ
 �������  :
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��20��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALL_UpdateSubAddress(
    VOS_UINT8                           ucCallId,
    MN_CALL_SUBADDR_STRU               *pstSubCallNumber
)
{
    PS_MEM_CPY(&f_astCallMgmtEntities[ucCallId - 1].stCallInfo.stSubCallNumber,
               pstSubCallNumber,
               sizeof(f_astCallMgmtEntities[ucCallId - 1].stCallInfo.stSubCallNumber));

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateCallReleaseFlag
 ��������  : ���º���ʵ����ͷű�־
 �������  : VOS_UINT8                           ucCallId         ����ʵ������
 �������  : VOS_BOOL                            bReleaseFlag     ����ʵ����ͷű�־
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��20��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��4��7��
    ��    ��   : A00165503
    �޸�����   : DTS2014040305777: ���������Ч�Լ��, ��ֹ�ڴ��ַԽ��
*****************************************************************************/
VOS_VOID MN_CALL_UpdateCallReleaseFlag(
    VOS_UINT8                           ucCallId,
    VOS_BOOL                            bReleaseFlag
)
{
    if ((ucCallId == 0) || (ucCallId > MN_CALL_MAX_NUM))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateCallReleaseFlag: ucCallId is invalid!");
        return;
    }

    f_abCallReleaseFlag[ucCallId - 1] = bReleaseFlag;
    return;

}

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateOpId
 ��������  : ���º���ʵ���OPID
 �������  : VOS_UINT8                           ucCallId         ����ʵ������
             MN_OPERATION_ID_T                   opId             Operation ID, ��ʶ���β���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��20��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALL_UpdateOpId(
    VOS_UINT8                           ucCallId,
    MN_OPERATION_ID_T                   opId
)
{
    f_astCallMgmtEntities[ucCallId - 1].stCallInfo.opId = opId;
    return;

}

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */

/*****************************************************************************
 �� �� ��  : MN_CALL_GetSpecificStatusCallInfo
 ��������  : ���ݺ���״̬����ȡ��Ӧ��ʵ����й�����Ϣ
 �������  : MN_CALL_STATE_ENUM_U8   enCallStatus- ����״̬
             MN_CALL_INFO_STRU      *pstCallInfo - ���й���ʵ����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��20��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��9��25��
    ��    ��   : A00165503
    �޸�����   : STK&DCM��Ŀ: CS��������ϱ�
*****************************************************************************/
VOS_UINT32  MN_CALL_GetSpecificStatusCallInfo(
    MN_CALL_STATE_ENUM_U8                enCallStatus,
    MN_CALL_INFO_STRU                   *pstCallInfo
)
{
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < MN_CALL_MAX_NUM; ulLoop++)
    {
        if (f_astCallMgmtEntities[ulLoop].stCallInfo.enCallState == enCallStatus)
        {
            *pstCallInfo = f_astCallMgmtEntities[ulLoop].stCallInfo;
            return TAF_CS_CAUSE_SUCCESS;

        }
    }

    return TAF_CS_CAUSE_STATE_ERROR;
}

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */

/* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-18, begin */
/* ���ⲿ�ֺ������ļ�MnCallSendApp.c�ļ��� */
/* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-18, end */

/*****************************************************************************
 �� �� ��  : MN_CALL_GetUeDiscEventInfo
 ��������  : ��ȡUE�����DISCONNECT, RELEASE, RELEASE COMPLETE��Ϣ��CAUSE,CALLID��TI
 �������  : const MNCC_IND_PRIM_MSG_STRU       *pstMsg DISCONNECT, RELEASE, RELEASE COMPLETE��Ϣ
 �������  : SI_STK_CALL_DISCONNECTED_EVENT_STRU *pstDiscEvent �����ͷ��¼��ṹ
             VOS_UINT8                          *pucTi,     ��Ϣ��Ӧ�ĺ���TI
             VOS_UINT8                          *pucCallId  ��Ϣ��Ӧ��CALL ID
 �� �� ֵ  : VOS_UINT32
                MN_ERR_NO_ERROR     ��ȡ�����ɹ�
                ����                ��ȡ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��21��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��7��13��
    ��    ��   : l00208543
    �޸�����   : STK������Ŀ

*****************************************************************************/
VOS_UINT32 MN_CALL_GetUeDiscEventInfo(
    const MNCC_REQ_PRIM_MSG_STRU       *pstMsg,
    /* Modified by l00208543 for V9R1 STK����, 2013-07-10, begin */
    NAS_STK_CALL_DISC_CAUSE_STRU       *pstDiscEventCause,
    /* Modified by l00208543 for V9R1 STK����, 2013-07-10, end */
    VOS_UINT8                          *pucTi,
    VOS_UINT8                          *pucCallId
)
{
    const NAS_CC_IE_CAUSE_STRU         *pstCause    = VOS_NULL_PTR;

    /* Modified by l00208543 for V9R1 STK����, 2013-07-13, begin */
    VOS_UINT8                           ucPos;
    /* Modified by l00208543 for V9R1 STK����, 2013-07-13, begin */

    /*
        �¼�����                ��Ӧ�����ݽṹ                      ��Ӧ�Ŀտ���Ϣ
        MNCC_DISC_REQ           NAS_CC_MSG_DISCONNECT_MO_STRU           DISCONNECT
        MNCC_REL_REQ            NAS_CC_MSG_RELEASE_MO_STRU              RELEASE
        MNCC_REJ_REQ            NAS_CC_MSG_RELEASE_COMPLETE_MO_STRU     RELEASE COMPLETE
        MNCC_DISC_IND           NAS_CC_MSG_DISCONNECT_MT_STRU           DISCONNECT
        MNCC_REL_IND            NAS_CC_MSG_RELEASE_MT_STRU              RELEASE
        MNCC_REL_CNF            NAS_CC_MSG_RELEASE_COMPLETE_MT_STRU     RELEASE COMPLETE
        MNCC_REJ_IND            none
        MNCC_RADIO_LINK_FAILURE none                                    �����ؽ�
    */

    /* Deleted by l00208543 for V9R1 STK����, 2013-07-10, begin */
    /* Deleted by l00208543 for V9R1 STK����, 2013-07-10, end */

    switch (pstMsg->enPrimName)
    {
        case MNCC_DISC_REQ:
            pstCause    = &pstMsg->unParam.stDisc.stCause;
            break;

        case MNCC_REL_REQ:
            pstCause    = &pstMsg->unParam.stRel.stCause;
            break;

        case MNCC_REJ_REQ:
            pstCause    = &pstMsg->unParam.stRelComp.stCause;
            break;

        default:
            return MN_ERR_INVALIDPARM;

    }

    *pucTi      = pstMsg->ucTi;
    *pucCallId  = pstMsg->ucCallId;

    /* Modified by l00208543 for V9R1 STK����, 2013-07-13, begin */
    ucPos       = 0;

    if (0 != pstCause->IsExist)
    {
        pstDiscEventCause->ucExistFlg      = VOS_TRUE;
        PS_MEM_CPY( &(pstDiscEventCause->aucCause[ucPos]),&(pstCause->Octet3),sizeof( pstCause->Octet3 ));
        ucPos++;

        if (0 == pstCause->Octet3.Ext)
        {
            PS_MEM_CPY( &(pstDiscEventCause->aucCause[ucPos]),&(pstCause->Octet3a),sizeof( pstCause->Octet3a ));
            ucPos++;
        }
        PS_MEM_CPY( &(pstDiscEventCause->aucCause[ucPos]),&(pstCause->Octet4),sizeof( pstCause->Octet4 ));
        ucPos++;

        pstDiscEventCause->ucLength = ucPos;
    }
    /* Modified by l00208543 for V9R1 STK����, 2013-07-13, end */

    return MN_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_GetNetDiscEventInfo
 ��������  : ��ȡUE�����DISCONNECT, RELEASE, RELEASE COMPLETE��Ϣ��CAUSE, CALLID��TI
 �������  : const MNCC_IND_PRIM_MSG_STRU       *pstMsg DISCONNECT, RELEASE, RELEASE COMPLETE��Ϣ
 �������  : SI_STK_CALL_DISCONNECTED_EVENT_STRU *pstDiscEvent �����ͷ��¼��ṹ
             VOS_UINT8                          *pucTi,     ��Ϣ��Ӧ�ĺ���TI
             VOS_UINT8                          *pucCallId  ��Ϣ��Ӧ��CALL ID
 �� �� ֵ  : VOS_UINT32
                MN_ERR_NO_ERROR     ��ȡ�����ɹ�
                ����                ��ȡ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��21��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��01��29��
    ��    ��   : Y00213812
    �޸�����   : DTS2013012909872,callId��ֵ
  3.��    ��   : 2013��04��12��
    ��    ��   : f62575
    �޸�����   : DTS2013041503184,���3G��RADIO LINK FAILUREû�а�Э��Ҫ����������ͷ��¼�����
                 ���ں����ؽ�ʧ�ܺ��ϱ���UICC���˴�ɾ��MNCC_RADIO_LINK_FAILURE��֧
  4.��    ��   : 2013��07��13��
    ��    ��   : l00208543
    �޸�����   : STK������Ŀ
*****************************************************************************/
VOS_UINT32 MN_CALL_GetNetDiscEventInfo(
    const MNCC_IND_PRIM_MSG_STRU       *pstMsg,
    /* Modified by l00208543 for V9R1 STK����, 2013-07-10, begin */
    NAS_STK_CALL_DISC_CAUSE_STRU       *pstDiscEventCause,
    /* Modified by l00208543 for V9R1 STK����, 2013-07-10, end */
    VOS_UINT8                          *pucTi,
    VOS_UINT8                          *pucCallId
)
{
    const NAS_CC_IE_CAUSE_STRU         *pstCause    = VOS_NULL_PTR;
    /* Modified by l00208543 for V9R1 STK����, 2013-07-10, begin */
    VOS_UINT8                           ucPos;
    /* Modified by l00208543 for V9R1 STK����, 2013-07-10, begin */

    /*
        �¼�����                ��Ӧ�����ݽṹ                          ��Ӧ�Ŀտ���Ϣ
        MNCC_DISC_REQ           NAS_CC_MSG_DISCONNECT_MO_STRU           DISCONNECT
        MNCC_REL_REQ            NAS_CC_MSG_RELEASE_MO_STRU              RELEASE
        MNCC_REJ_REQ            NAS_CC_MSG_RELEASE_COMPLETE_MO_STRU     RELEASE COMPLETE
        MNCC_DISC_IND           NAS_CC_MSG_DISCONNECT_MT_STRU           DISCONNECT
        MNCC_REL_IND            NAS_CC_MSG_RELEASE_MT_STRU              RELEASE
        MNCC_REL_CNF            NAS_CC_MSG_RELEASE_COMPLETE_MT_STRU     RELEASE COMPLETE
        MNCC_REJ_IND            none                                    MMCC_REL_IND��MMCC_ERR_IND
    */

    /* Deleted by l00208543 for V9R1 STK����, 2013-07-10, begin */
    /* Deleted by l00208543 for V9R1 STK����, 2013-07-10, end */

    switch (pstMsg->enPrimName)
    {
        case MNCC_DISC_IND:
            pstCause    = &pstMsg->unParam.stDisc.stCause;
            break;

        case MNCC_REL_IND:
            pstCause    = &pstMsg->unParam.stRel.stCause;
            break;

        case MNCC_REL_CNF:
            pstCause    = &pstMsg->unParam.stRelComp.stCause;
            break;

        case MNCC_REJ_IND:
             /*Cause��Ϣ��Դ��DISCONNECT, RELEASE or RELEASE COMPLETE��Ϣ�������Ϣ��û��Cause��Ϣ���򲻰��������Ϣ����������ͷ�ʱ������·��ʱ���£���ҪЯ��Cause��Ϣ�ֶΣ�������0��*/
             /* Modified by l00208543 for V9R1 STK����, 2013-07-13, begin */
             pstDiscEventCause->ucLength     = 0;
             pstDiscEventCause->ucExistFlg   = VOS_TRUE;
             /* Modified by l00208543 for V9R1 STK����, 2013-07-13, end */

            *pucCallId                      = pstMsg->ucCallId;
            return MN_ERR_NO_ERROR;

        default:
            return MN_ERR_INVALIDPARM;

    }

    *pucTi      = pstMsg->ucTi;
    *pucCallId  = pstMsg->ucCallId;

    /* Modified by l00208543 for V9R1 STK����, 2013-07-13, begin */
    ucPos       = 0;

    if (0 != pstCause->IsExist)
    {
        pstDiscEventCause->ucExistFlg      = VOS_TRUE;
        PS_MEM_CPY( &(pstDiscEventCause->aucCause[ucPos]),&(pstCause->Octet3),sizeof( pstCause->Octet3 ));
        ucPos++;

        if (0 == pstCause->Octet3.Ext)
        {
            PS_MEM_CPY( &(pstDiscEventCause->aucCause[ucPos]),&(pstCause->Octet3a),sizeof( pstCause->Octet3a ));
            ucPos++;
        }

        PS_MEM_CPY( &(pstDiscEventCause->aucCause[ucPos]),&(pstCause->Octet4),sizeof( pstCause->Octet4 ));
        ucPos++;

        pstDiscEventCause->ucLength = ucPos;
    }
    /* Modified by l00208543 for V9R1 STK����, 2013-07-13, end */

    return MN_ERR_NO_ERROR;

}

/* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-18, begin */
/* ���ⲿ�ֺ������ļ�MnCallSendApp.c�ļ��� */
/* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-18, end */

/*****************************************************************************
 �� �� ��  : MN_CALL_RecordCallEntityRedirectInfo
 ��������  : ��¼CC����ĺ�����Ϣ������ת�ƺ����ת�ƺŵ��Ӻ����
 �������  : callId     ���е�ID
             pstSetup   ����ĺ�����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��09��18��
    ��    ��   : y00213812
    �޸�����   : STK&DCM ��Ŀ��������

*****************************************************************************/
VOS_VOID  MN_CALL_RecordCallEntityRedirectInfo(
        MN_CALL_ID_T                        callId,
        NAS_CC_MSG_SETUP_MT_STRU            *pstSetup)
{
    VOS_UINT8                           ucLen;

    /* ����������Ч�� */
    if (VOS_NULL_PTR == pstSetup)
    {
        return;
    }

    /* ��ʼ��CALLING_PI��NO_CLI_CAUSE���� */
    f_astCallMgmtEntities[callId - 1].stCallInfo.enCallingPI  = MN_CALL_PRESENTATION_RESERVED;
    f_astCallMgmtEntities[callId - 1].stCallInfo.enNoCliCause = MN_CALL_NO_CLI_BUTT;

    /* ��¼CALLING_PI��NO_CLI_CAUSE���� */
    if (VOS_TRUE == pstSetup->stCallingNum.Octet3a.Ext)
    {
        f_astCallMgmtEntities[callId - 1].stCallInfo.enCallingPI  = pstSetup->stCallingNum.Octet3a.PresentationIndicator;
    }

    if (VOS_TRUE == pstSetup->stNoCLICause.IsExist)
    {
        f_astCallMgmtEntities[callId - 1].stCallInfo.enNoCliCause = pstSetup->stNoCLICause.CauseOfNoCLI;
    }

    /* ��¼Redirect_num */
    if (VOS_TRUE == pstSetup->stRedirectingNum.IsExist)
    {
        /*lint -e961*/
        ucLen = pstSetup->stRedirectingNum.LastOctOffset
                          - sizeof(NAS_CC_IE_REDIRECTING_NUM_OCTET3_STRU)
                          - sizeof(NAS_CC_IE_REDIRECTING_NUM_OCTET3A_STRU);
        /*lint +e961*/

        if (ucLen <= NAS_CC_MAX_REDIRECTING_BCD_NUM_LEN)
        {
            f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectNumber.ucNumLen  = ucLen;

            PS_MEM_CPY(f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectNumber.aucBcdNum,
                       pstSetup->stRedirectingNum.BCDNum,
                       ucLen);

            f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectNumber.enNumType
                        = (MN_CALL_NUM_TYPE_ENUM_U8)(MN_CALL_IS_EXIT
                           | (pstSetup->stRedirectingNum.Octet3.TON << 4)
                           | pstSetup->stRedirectingNum.Octet3.NPI);
        }

        /* ��¼Redirect_subaddr */
        if (VOS_TRUE == pstSetup->stRedirectingSubaddr.IsExist)
        {
            ucLen = pstSetup->stRedirectingSubaddr.LastOctOffset - sizeof(NAS_CC_IE_REDIRECTING_SUBADDR_OCTET3_STRU);

            if (ucLen <= MN_CALL_MAX_SUBADDR_INFO_LEN)
            {
                f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectSubaddr.LastOctOffset
                            = pstSetup->stRedirectingSubaddr.LastOctOffset;

                PS_MEM_CPY(f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectSubaddr.SubAddrInfo,
                           pstSetup->stRedirectingSubaddr.SubAddrInfo,
                           ucLen);

                f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectSubaddr.IsExist = VOS_TRUE;

                /* Ŀǰֻ֧��NSAP�ı��뷽ʽ���ӵ�ַOct3 = MN_CALL_IS_EXIT */
                f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectSubaddr.Octet3  = MN_CALL_IS_EXIT;
            }
        }
    }
    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_ReadCallEntityRedirectInfo
 ��������  : ��ȡת�ƺ��к����ת�ƺ�����ӵ�ַ����Ϣ
 �������  : callId     ���е�ID
             pstSetup   ����ĺ�����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��09��18��
    ��    ��   : y00213812
    �޸�����   : STK&DCM ��Ŀ��������

*****************************************************************************/
VOS_VOID  MN_CALL_ReadCallEntityRedirectInfo(
        MN_CALL_ID_T                        callId,
        MN_CALL_CLPR_GET_CNF_STRU          *pstGetClprCnf)
{

    if (MN_CALL_DIR_MT != f_astCallMgmtEntities[callId - 1].stCallInfo.enCallDir)
    {
        pstGetClprCnf->ulRet = TAF_ERR_ERROR;
        return;
    }

    /* ��д<PI>���� */
    if (MN_CALL_PRESENTATION_RESERVED != f_astCallMgmtEntities[callId - 1].stCallInfo.enCallingPI)
    {
        pstGetClprCnf->stRedirectInfo.bitOpPI = VOS_TRUE;
        pstGetClprCnf->stRedirectInfo.enPI    = f_astCallMgmtEntities[callId - 1].stCallInfo.enCallingPI;
    }
    /* ��д<no_CLI_cause>���� */
    if (MN_CALL_NO_CLI_BUTT != f_astCallMgmtEntities[callId - 1].stCallInfo.enNoCliCause)
    {
        pstGetClprCnf->stRedirectInfo.bitOpNoCLICause  = VOS_TRUE;
        pstGetClprCnf->stRedirectInfo.enNoCLICause     = (VOS_UINT8)f_astCallMgmtEntities[callId - 1].stCallInfo.enNoCliCause;
    }

    /* ��д<redirect_num>��<num_type>���� */
    if (0 != f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectNumber.ucNumLen)
    {
        pstGetClprCnf->stRedirectInfo.bitOpRedirectNum   = VOS_TRUE;
        pstGetClprCnf->stRedirectInfo.stRedirectNum      = f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectNumber;
    }

    /* ��д<redirect_subaddr>��<subaddr_type>���� */
    if (VOS_TRUE == f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectSubaddr.IsExist)
    {
        /* ��д<redirect_num>��<num_type>���� */
        pstGetClprCnf->stRedirectInfo.bitOpRedirectSubaddr = VOS_TRUE;
        pstGetClprCnf->stRedirectInfo.stRedirectSubaddr    = f_astCallMgmtEntities[callId - 1].stCallInfo.stRedirectSubaddr;
    }

    pstGetClprCnf->ulRet = TAF_ERR_NO_ERROR;
    return;
}

/* Deleted by l00198894 for V9R1 STK����, 2013/07/11 */

/*****************************************************************************
 �� �� ��  : MN_CALL_AllowSupsOperation
 ��������  : �жϺ�����صĲ���ҵ������Ƿ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : �Ƿ����������صĲ���ҵ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��11��
    ��    ��   : h44270
    �޸�����   : STK&DCM ��Ŀ��������
  2.��    ��   : 2013��03��23��
    ��    ��   : f62575
    �޸�����   : DTS2013031406373�����DTMF�����к��в��ܹҶ�����
*****************************************************************************/
VOS_UINT32 MN_CALL_AllowSupsOperation(VOS_VOID)
{

    if (VOS_TRUE == f_stCallSupsCmdMgmt.bInProgress)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_IsNeedCallRedial
 ��������  : �ж��Ƿ���������ؽ�����
 �������  : ucCallId - ����ID
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫ�����ؽ�
             VOS_FALSE - ����Ҫ�����ؽ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��10��30��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����

  3.��    ��   : 2013��7��2��
    ��    ��   : z00234330
    �޸�����   : DTS2013062709165,�ж��Ƿ�ǰ���ڽ��йҶ����̣�������ڽ��йҶ����̣�����
                 Ҫ�ز���
  4.��    ��   : 2014��4��8��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature�޸�
  5.��    ��   :2014��9��24��
    ��    ��   :s00217060
    �޸�����   :for cs_err_log
  6.��    ��   :2016��03��08��
    ��    ��   :l00356716
    �޸�����   :NAS���������Ż�
*****************************************************************************/
VOS_UINT32 MN_CALL_IsNeedCallRedial(
    MN_CALL_ID_T                        ucCallId,
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    VOS_UINT32                          ulCallRedialPeriodRemainLen;
    VOS_UINT32                          ulCallRedialSupportFlg;
    VOS_UINT8                            ucCallDisconnectDir;

    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    /*������Ҫ�ڹҶϵĹ�������Ҫ��ʼ���ԣ��������Ҷϲ�����*/
    if ( (ucCallId == 0) || ( ucCallId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_IsNeedCallRedial: callId error!");
        return VOS_FALSE;
    }
    ucCallDisconnectDir = TAF_CALL_GetDisconnectDir(ucCallId);
    /* ��ǰ���ڽ��йҶ�ʱ,����Ҫ�ز� */
    if ( (VOS_TRUE == TAF_CALL_GetDisconnectFlg(ucCallId))
     && (VOS_TRUE == ucCallDisconnectDir) )
    {
        return VOS_FALSE;
    }

    MN_CALL_GetCallState(ucCallId, &enCallState, &enMptyState);

    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-8, begin */
    ulCallRedialSupportFlg      = TAF_CALL_GetRedialSupportFlg(ucCallId);
    ulCallRedialPeriodRemainLen = TAF_CALL_GetRemainRedialPeriodTimerLen(ucCallId);
    /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-8, end */

    if ((MN_CALL_DIR_MO == MN_CALL_GetCcCallDir(ucCallId))
     && (MN_CALL_S_DIALING == enCallState)
     && (VOS_TRUE == ulCallRedialSupportFlg))
    {
        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
        if (ulCallRedialPeriodRemainLen > 0)
        {
#if (FEATURE_ON == FEATURE_ECALL)
            if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(ucCallId))
            {
                /* ����eCall����ʧ�ܣ��������ز� */
                return VOS_TRUE;
            }
#endif

            /*ֻ�ڽ���һ·���е�����´������ԣ���Ӱ��֮ǰeCall������*/
            if (TAF_CALL_GetCallNum() > 1)
            {
                return VOS_FALSE;
            }

            if (VOS_TRUE == TAF_CALL_IsCallRedialCause(enCause))
            {
                return VOS_TRUE;
            }
        }

        /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_UpdateDiscCallDir
 ��������  : ����CALL�Ҷϵķ���
 �������  : callId     - ����ID
             ucIsUser   - �Ƿ����û�����ĹҶ�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��01��29��
    ��    ��   : Y00213812
    �޸�����   : DTS2013012909872�����ɺ���

*****************************************************************************/
VOS_VOID MN_CALL_UpdateDiscCallDir(
    MN_CALL_ID_T                        callId,
    VOS_UINT8                           ucIsUser
)
{
    if ( (callId == 0) || ( callId > MN_CALL_MAX_NUM ) )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_UpdateDiscCallDir: callId error!");
        return;
    }

    if (VOS_TRUE == f_astCallMgmtEntities[callId - 1].stCallInfo.stDiscDir.ucDiscCallFlag)
    {
        return;
    }

    f_astCallMgmtEntities[callId - 1].stCallInfo.stDiscDir.ucIsUser       = ucIsUser;
    f_astCallMgmtEntities[callId - 1].stCallInfo.stDiscDir.ucDiscCallFlag = VOS_TRUE;

    return;
}


/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, begin */
/*****************************************************************************
 �� �� ��  : TAF_CALL_IsOrigNeedRpt
 ��������  : ���й����е��¼�MN_CALL_EVT_ORIG�Ƿ���Ҫ�ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ�ϱ���VOS_TRUE:��Ҫ�ϱ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��3��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C����������
*****************************************************************************/
VOS_UINT32 TAF_CALL_IsOrigNeedRpt(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU          *pstCurcRptCtrl          = VOS_NULL_PTR;
    VOS_UINT32                           ulChkCallStaFlg;
    VOS_UINT32                           ulChkOrigFlg;

    pstCurcRptCtrl  = TAF_SDC_GetCurcRptCtrl();

    ulChkCallStaFlg = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CALLSTATE);

    ulChkOrigFlg    = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_ORIG);

    if ( (VOS_FALSE == ulChkCallStaFlg)
      && (VOS_FALSE == ulChkOrigFlg) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_IsConfNeedRpt
 ��������  : ���й����е��¼�MN_CALL_EVT_CALL_PROC�Ƿ���Ҫ�ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ�ϱ���VOS_TRUE:��Ҫ�ϱ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��3��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C����������
*****************************************************************************/
VOS_UINT32 TAF_CALL_IsConfNeedRpt(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU          *pstCurcRptCtrl          = VOS_NULL_PTR;
    VOS_UINT32                           ulChkCallStaFlg;
    VOS_UINT32                           ulChkConfFlg;

    pstCurcRptCtrl  = TAF_SDC_GetCurcRptCtrl();

    ulChkCallStaFlg = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CALLSTATE);

    ulChkConfFlg    = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CONF);

    if ( (VOS_FALSE == ulChkCallStaFlg)
      && (VOS_FALSE == ulChkConfFlg) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_IsConnNeedRpt
 ��������  : ���й����е��¼�MN_CALL_EVT_CONNECT�Ƿ���Ҫ�ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ�ϱ���VOS_TRUE:��Ҫ�ϱ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��3��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C����������
*****************************************************************************/
VOS_UINT32 TAF_CALL_IsConnNeedRpt(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU          *pstCurcRptCtrl          = VOS_NULL_PTR;
    VOS_UINT32                           ulChkCallStaFlg;
    VOS_UINT32                           ulChkConnFlg;

    pstCurcRptCtrl  = TAF_SDC_GetCurcRptCtrl();

    ulChkCallStaFlg = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CALLSTATE);

    ulChkConnFlg    = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CONN);

    if ( (VOS_FALSE == ulChkCallStaFlg)
      && (VOS_FALSE == ulChkConnFlg) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_IsCendNeedRpt
 ��������  : ���й����е��¼�MN_CALL_EVT_RELEASED�Ƿ���Ҫ�ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:����Ҫ�ϱ���VOS_TRUE:��Ҫ�ϱ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��3��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C����������
*****************************************************************************/
VOS_UINT32 TAF_CALL_IsCendNeedRpt(VOS_VOID)
{
    TAF_SDC_CURC_RPT_CTRL_STRU          *pstCurcRptCtrl          = VOS_NULL_PTR;
    VOS_UINT32                           ulChkCallStaFlg;
    VOS_UINT32                           ulChkCendFlg;

    pstCurcRptCtrl  = TAF_SDC_GetCurcRptCtrl();

    ulChkCallStaFlg = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CALLSTATE);

    ulChkCendFlg    = TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                                TAF_SDC_RPT_CMD_CEND);

    if ( (VOS_FALSE == ulChkCallStaFlg)
      && (VOS_FALSE == ulChkCendFlg) )
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, end */


/*****************************************************************************
 �� �� ��  : TAF_CALL_GetDisconnectFlg
 ��������  : ��ȡ��ǰCALL ID�Ƿ����ڹҶ�
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��2��
    ��    ��   : z00234330
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_CALL_GetDisconnectFlg(
    MN_CALL_ID_T                        callId
)
{
    return f_astCallMgmtEntities[callId - 1].stCallInfo.stDiscDir.ucDiscCallFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetDisconnectDir
 ��������  : ��ȡ��ǰCALL ID�Ҷϵķ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��03��08��
    ��    ��   : l00356716
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_CALL_GetDisconnectDir(
    MN_CALL_ID_T                        callId
)
{
    return f_astCallMgmtEntities[callId - 1].stCallInfo.stDiscDir.ucIsUser;
}

/* Added by l00198894 for V9R1 STK����, 2013/07/11, begin */
/*****************************************************************************
 �� �� ��  : TAF_CALL_InitDtmfCtx
 ��������  : ��ʼ��DTMF״̬��������Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_VOID TAF_CALL_InitDtmfCtx(VOS_VOID)
{
    PS_MEM_SET(&f_stCallDtmfCtx, 0, sizeof(f_stCallDtmfCtx));

    f_stCallDtmfCtx.enDtmfState = TAF_CALL_DTMF_IDLE;

    /*lint -e717*/
    HI_INIT_LIST_HEAD(&f_stCallDtmfCtx.stList);
    /*lint -e717*/

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_ResetDtmfCtx
 ��������  : ����DTMF״̬��������Ϣ
 �������  : enCause        -- ���û����ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
  2.��    ��   : 2013��09��02��
    ��    ��   : f62575
    �޸�����   : DTS2013082307371,�����ʱ����ʱ����STOP DTMF������Ϣ�󣬶�ʱ��������û���������
  3.��    ��   :2013��10��24��
    ��    ��   :z00161729
    �޸�����   :DTS2013102403705:dtmf��֧��off_length������SBM IOT��֤��Ҫstop dtmf req����һ��start dtmf req�������70ms
*****************************************************************************/
VOS_VOID TAF_CALL_ResetDtmfCtx(
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    HI_LIST_S                          *pstMe       = VOS_NULL_PTR;
    HI_LIST_S                          *pstTmp      = VOS_NULL_PTR;
    TAF_CALL_DTMF_NODE_STRU            *pstNode     = VOS_NULL_PTR;
    MN_CALL_EVENT_ENUM_U32              enEventType;

    MN_CALL_StopTimer(TAF_CALL_TID_DTMF_ON_LENGTH);
    MN_CALL_StopTimer(TAF_CALL_TID_DTMF_OFF_LENGTH);

    /* �ͷŻ����ڴ� */
    /*lint -e961 -e424*/
    msp_list_for_each_safe(pstMe, pstTmp, &f_stCallDtmfCtx.stList)
    {
        pstNode = msp_list_entry(pstMe, TAF_CALL_DTMF_NODE_STRU, stList);

        if (0 == pstNode->stDtmf.usOnLength)
        {
            enEventType = MN_CALL_EVT_STOP_DTMF_RSLT;
        }
        else
        {
            enEventType = MN_CALL_EVT_START_DTMF_RSLT;
        }

        /* ����ʱ����Ҫ�������е�����DTMF��Ϣ�ظ���ʽ��Ӧ */
        TAF_CALL_SendDtmfCnf(pstNode->stDtmf.usClientId,
                             pstNode->stDtmf.opId,
                             enEventType,
                             enCause);

        /* �ӹ��˱���ɾ���ڵ� */
        msp_list_del(&pstNode->stList);

        /* �ͷŽڵ��ڴ� */
        PS_MEM_FREE(WUEPS_PID_TAF, pstNode);/*lint !e424*/
    }
    /*lint +e961 +e424*/

    TAF_CALL_InitDtmfCtx();

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_IsAllowDtmf
 ��������  : �жϵ�ǰ�ú���ID�Ƿ�������DTMF����
 �������  : pCallIds       -- ��ǰ��Attach�ĺ���ID
             ulNumOfCalls   -- ��Attach�ĺ��и���
             CallId         -- Ҫ����DTMF�ĺ���ID
 �������  : ��
 �� �� ֵ  : TAF_CS_CAUSE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
TAF_CS_CAUSE_ENUM_UINT32 TAF_CALL_IsAllowDtmf(
    MN_CALL_ID_T                       *pCallIds,
    VOS_UINT32                          ulNumOfCalls,
    MN_CALL_ID_T                        CallId
)
{
    VOS_UINT8                           ucLoop;

    /* �ж�CallID����Ч�� 0Ĭ��Ϊ��ǰ����CallID */
    if (0 != CallId)
    {
        for (ucLoop = 0; ucLoop < ulNumOfCalls; ucLoop++)
        {
            if (pCallIds[ucLoop] == CallId)
            {
                break;
            }
        }

        if (ucLoop == ulNumOfCalls)
        {
            return TAF_CS_CAUSE_NO_CALL_ID;
        }
    }

    return TAF_CS_CAUSE_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetAllowedDtmfCallId
 ��������  : ��ȡ���ڷ���DTMF��CALL ID
 �������  : ��
 �������  : pCallId        -- ������������DTMF��CallID
 �� �� ֵ  : TAF_CS_CAUSE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
  2.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK�������޸Ĳ���������ԭ����������������޸�Ϊ�����������
*****************************************************************************/
TAF_CS_CAUSE_ENUM_UINT32  TAF_CALL_GetAllowedDtmfCallId(
    MN_CALL_ID_T                       *pCallId
)
{
    VOS_UINT8                           ucLoop;

    if (VOS_TRUE != MN_CALL_GetTchStatus())
    {
        return TAF_CS_CAUSE_NOT_IN_SPEECH_CALL;
    }

    /* ��������ʵ�壬�ҳ���Attach�ĺ���ID */
    for (ucLoop = 0; ucLoop < MN_CALL_MAX_NUM; ucLoop++)
    {
        if (VOS_TRUE != f_astCallMgmtEntities[ucLoop].bUsed)
        {
            continue;
        }

        if ( (MN_CALL_S_ACTIVE   == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState)
          || (MN_CALL_S_DIALING  == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState)
          || (MN_CALL_S_ALERTING == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState)
          || (MN_CALL_S_INCOMING == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState) )
        {
            *pCallId = (ucLoop + 1);
            return TAF_CS_CAUSE_SUCCESS;
        }
    }

    return TAF_CS_CAUSE_NOT_IN_SPEECH_CALL;

}

/*****************************************************************************
 �� �� ��  : TAF_CALL_CheckUserDtmfCallId
 ��������  : ��ȡ���ڷ���DTMF��CALL ID
             DTMF��������ӿ�Լ����
             �û������CALL ID����Чֵ0��ָʾʹ������CALL ID����DTMF��Ϣ
             �û������CALL ID������Чֵ0��ָʾ���û��·���CALL ID����DTMF��Ϣ���������CALL ID
             ��Ҫ���㷢��DTMF��Ϣ������
 �������  : CallId        -- �û���DTMF������Ϣ�е�CallID
 �������  : ��
 �� �� ֵ  : TAF_CS_CAUSE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK������
*****************************************************************************/
TAF_CS_CAUSE_ENUM_UINT32  TAF_CALL_CheckUserDtmfCallId(
    MN_CALL_ID_T                        CallId
)
{
    VOS_UINT8                           ucLoop;
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];

    ulNumOfCalls    = 0;
    PS_MEM_SET(aCallIds, 0, sizeof(aCallIds));

    /* ��������ʵ�壬�ҳ���Attach�ĺ���ID */
    for (ucLoop = 0; ucLoop < MN_CALL_MAX_NUM; ucLoop++)
    {
        if (VOS_TRUE != f_astCallMgmtEntities[ucLoop].bUsed)
        {
            continue;
        }

        if ( (MN_CALL_S_ACTIVE   == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState)
          || (MN_CALL_S_DIALING  == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState)
          || (MN_CALL_S_ALERTING == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState)
          || (MN_CALL_S_INCOMING == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState) )
        {
            aCallIds[ulNumOfCalls] = ucLoop + 1;
            ulNumOfCalls++;
        }
    }

    /* ���û����·����Attach�ĺ��и���Ϊ0��������DTMF���� */
    if ( (VOS_TRUE != MN_CALL_GetTchStatus())
      || (0 == ulNumOfCalls) )
    {
        return TAF_CS_CAUSE_NOT_IN_SPEECH_CALL;
    }

    /*
        DTMF��������ӿ�Լ����
        �û������CALL ID����Чֵ0��ָʾʹ������CALL ID����DTMF��Ϣ
        �û������CALL ID������Чֵ0��ָʾ���û��·���CALL ID����DTMF��Ϣ���������CALL ID
        ��Ҫ���㷢��DTMF��Ϣ������
    */
    return TAF_CALL_IsAllowDtmf(aCallIds, ulNumOfCalls, CallId);
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetDtmfCtx
 ��������  : ��ȡCALLģ��DTMF��Ϣ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_CALL_DTMF_CTX_STRU    -- CALLģ��DTMF��Ϣ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
TAF_CALL_DTMF_CTX_STRU* TAF_CALL_GetDtmfCtx(VOS_VOID)
{
    return &f_stCallDtmfCtx;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetDtmfState
 ��������  : ��ȡCALLģ��DTMF��״̬
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_CALL_DTMF_STATE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
TAF_CALL_DTMF_STATE_ENUM_UINT8 TAF_CALL_GetDtmfState(VOS_VOID)
{
    return f_stCallDtmfCtx.enDtmfState;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_SetDtmfState
 ��������  : ����CALLģ��DTMF��״̬
 �������  : enState    -- DTMF״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_VOID TAF_CALL_SetDtmfState(
    TAF_CALL_DTMF_STATE_ENUM_UINT8      enState
)
{
    f_stCallDtmfCtx.enDtmfState = enState;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetDtmfBufCnt
 ��������  : ��ȡCALLģ��DTMF�Ļ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_UINT8 TAF_CALL_GetDtmfBufCnt(VOS_VOID)
{
    return f_stCallDtmfCtx.ucDtmfCnt;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_DtmfBufCntIncrement
 ��������  : CALLģ��DTMF�Ļ����������1
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_VOID TAF_CALL_DtmfBufCntIncrement(VOS_VOID)
{
    f_stCallDtmfCtx.ucDtmfCnt++;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_DtmfBufCntDecrement
 ��������  : CALLģ��DTMF�Ļ�������Լ�1
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_VOID TAF_CALL_DtmfBufCntDecrement(VOS_VOID)
{
    f_stCallDtmfCtx.ucDtmfCnt--;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetDtmfListHead
 ��������  : ��ȡCALLģ��DTMF�Ļ����ͷ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : HI_LIST_S
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
HI_LIST_S* TAF_CALL_GetDtmfListHead(VOS_VOID)
{
    return &(f_stCallDtmfCtx.stList);
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetDtmfCurInfo
 ��������  : ��ȡCALLģ�鵱ǰDTMF��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : HI_LIST_S
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
TAF_CALL_DTMF_INFO_STRU* TAF_CALL_GetDtmfCurInfo(VOS_VOID)
{
    return &(f_stCallDtmfCtx.stCurrDtmf);
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_FillDtmfCnf
 ��������  : ���DTMF�ظ���Ϣ
 �������  : usClientId     -- ClientID
             opId           -- ����ID
             enCause        -- ԭ��ֵ
 �������  : pstDtmfCnf     -- ��Ҫ����DTMF�ظ���Ϣ
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_VOID TAF_CALL_FillDtmfCnf(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   opId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause,
    TAF_CALL_EVT_DTMF_CNF_STRU         *pstDtmfCnf
)
{
    TAF_CALL_DTMF_CTX_STRU             *pstDtmfBuf  = VOS_NULL_PTR;

    pstDtmfBuf = TAF_CALL_GetDtmfCtx();

    pstDtmfCnf->usClientId  = usClientId;
    pstDtmfCnf->opId        = opId;
    pstDtmfCnf->enCause     = enCause;

    pstDtmfCnf->callId      = pstDtmfBuf->stCurrDtmf.CallId;
    pstDtmfCnf->enDtmfState = pstDtmfBuf->enDtmfState;
    pstDtmfCnf->ucDtmfCnt   = pstDtmfBuf->ucDtmfCnt;

    return;
}

/* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-18, begin */
/* ���ⲿ�ֺ������ļ�MnCallSendApp.c�ļ��� */
/* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-18, end */

/*****************************************************************************
 �� �� ��  : TAF_CALL_AddDtmfInfo
 ��������  : ����DTMF��Ϣ��DTMF����
 �������  : pstDtmfInfo   -- ������DTMF��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_VOID TAF_CALL_AddDtmfInfo(
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfInfo
)
{
    /*lint -e429 -e830*/
    TAF_CALL_DTMF_NODE_STRU            *pstNode         = VOS_NULL_PTR;

    /* ������˱�ڵ��ڴ� */
    pstNode = (TAF_CALL_DTMF_NODE_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_CALL_DTMF_NODE_STRU));
    if (VOS_NULL_PTR == pstNode)
    {
        MN_ERR_LOG("TAF_CALL_AddDtmfInfo: Mem Alloc Failed! ");
        return;
    }

    pstNode->stDtmf = *pstDtmfInfo;

    /* ���ڵ����ӵ�DTMF���������� */
    msp_list_add_tail(&pstNode->stList, &f_stCallDtmfCtx.stList);

    return;
    /*lint +e429 +e830*/

}

/*****************************************************************************
 �� �� ��  : TAF_CALL_SaveDtmfInfo
 ��������  : ��DTMF��Ϣ���浽DTMF������
 �������  : pstDtmfInfo    -- ��Ҫ���浽�����е�DTMF��Ϣ
 �������  : ��
 �� �� ֵ  : TAF_CS_CAUSE_ENUM_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
TAF_CS_CAUSE_ENUM_UINT32 TAF_CALL_SaveDtmfInfo(
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfInfo
)
{
    HI_LIST_S                          *pstListHead = VOS_NULL_PTR;
    HI_LIST_S                          *pstListLast = VOS_NULL_PTR;
    TAF_CALL_DTMF_NODE_STRU            *pstNode     = VOS_NULL_PTR;

    /* �жϻ����Ƿ��Ѿ����� */
    if (TAF_CALL_GetDtmfBufCnt() >= TAF_CALL_DTMF_BUF_MAX_CNT)
    {
        return TAF_CS_CAUSE_DTMF_BUF_FULL;
    }

    pstListHead = TAF_CALL_GetDtmfListHead();

    /* ������������������STOP DTMF���� */
    if (0 == pstDtmfInfo->usOnLength)
    {
        pstListLast = pstListHead->prev;

        if (pstListLast != pstListHead)
        {
            /*lint -e961*/
            pstNode = msp_list_entry(pstListLast, TAF_CALL_DTMF_NODE_STRU, stList);
            /*lint +e961*/

            if (0 == pstNode->stDtmf.usOnLength)
            {
                return TAF_CS_CAUSE_DTMF_REPEAT_STOP;
            }
        }
    }

    /* ��DTMF��Ϣ���浽������ */
    TAF_CALL_AddDtmfInfo(pstDtmfInfo);

    TAF_CALL_DtmfBufCntIncrement();

    return TAF_CS_CAUSE_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_DelDtmfNode
 ��������  : ɾ��DTMF���������еĽڵ�
 �������  : pstNode    -- ��Ҫɾ��DTMF���������еĽڵ�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
*****************************************************************************/
VOS_VOID TAF_CALL_DelDtmfNode(
    TAF_CALL_DTMF_NODE_STRU            *pstNode
)
{
    /* �ӹ��˱���ɾ���ڵ� */
    msp_list_del(&pstNode->stList);

    /* �ͷŽڵ��ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstNode);

    TAF_CALL_DtmfBufCntDecrement();

    return;
}

/* Added by l00198894 for V9R1 STK����, 2013/07/11, end */

/*****************************************************************************
 �� �� ��  : TAF_CALL_PreProcRelAllCall
 ��������  : �ͷ����к���ǰ����������ִ�еĲ���ҵ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��17��
    ��    ��   : f62575
    �޸�����   : DTS2013091104858���һ�ǰ������ɵ��û�����
*****************************************************************************/
VOS_VOID TAF_CALL_PreProcRelAllCall(VOS_VOID)
{
    MN_CALL_ID_T                        callId;

    if (VOS_TRUE != f_stCallSupsCmdMgmt.bInProgress)
    {
        return;
    }

    /* ������ǰ�ĺ�����ز���ҵ�� */
    callId                                              = f_stCallSupsCmdMgmt.astKeyEvts[0].callId;
    f_astCallMgmtEntities[callId].stCallInfo.enSsResult = MN_CALL_SS_RES_SUCCESS;
    MN_CALL_ReportEvent(callId, MN_CALL_EVT_SS_CMD_RSLT);

    /* ���������ز���ҵ��ע����Ϣ */
    MN_CALL_ClearSsKeyEvent();
    f_stCallSupsCmdMgmt.bInProgress = VOS_FALSE;
    MN_INFO_LOG("TAF_CALL_PreProcRelAllCall: clear event & not in progress");

    return;
}

/* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-18, begin */
/* ���ⲿ�ֺ������ļ�MnCallSendApp.c�ļ��� */
/* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-18, end */

/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-25, begin */
#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : TAF_CALL_ConvertImsaCallStateToMnCallState
 ��������  : ת��IMSA�ĺ���״̬��CALL�ĺ���״̬
 �������  : enImsaCallSta---IMSA�ĺ���״̬
 �������  : ��
 �� �� ֵ  : MN_CALL_STATE_ENUM_U8---ת�����call״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��25��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��12��14��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
MN_CALL_STATE_ENUM_U8 TAF_CALL_ConvertImsaCallStateToMnCallState(
    CALL_IMSA_SRVCC_CALL_STATE_ENUM_UINT8                   enImsaCallSta
)
{
    MN_CALL_STATE_ENUM_U8               enCallSta;

    switch (enImsaCallSta)
    {
        case CALL_IMSA_SRVCC_CALL_ALERTING:
            enCallSta = MN_CALL_S_ALERTING;
            break;

        case CALL_IMSA_SRVCC_CALL_ACTVING:
            enCallSta = MN_CALL_S_WAITING_ACCEPT;
            break;

        case CALL_IMSA_SRVCC_CALL_ACTIVE:
            enCallSta = MN_CALL_S_ACTIVE;
            break;

        case CALL_IMSA_SRVCC_CALL_HELD:
            enCallSta = MN_CALL_S_HELD;
            break;

        case CALL_IMSA_SRVCC_CALL_INCOMING:
            enCallSta = MN_CALL_S_INCOMING;
            break;

        case CALL_IMSA_SRVCC_CALL_WAITING:
            enCallSta = MN_CALL_S_WAITING;
            break;

        case CALL_IMSA_SRVCC_CALL_DIALING:
        default:
            enCallSta = MN_CALL_S_BUTT;
            break;
    }

    return enCallSta;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_CallStateIsLegal
 ��������  : ʹ��IMS��ĺ�����Ϣ��������ʵ��
 �������  : enCallState -- CALL״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��12��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_CALL_CallStateIsLegal(
    CALL_IMSA_SRVCC_CALL_STATE_ENUM_UINT8                   enCallState
)
{
    VOS_UINT8                           ucRst;
    switch (enCallState)
    {
        case CALL_IMSA_SRVCC_CALL_ACTIVE:
        case CALL_IMSA_SRVCC_CALL_HELD:
        case CALL_IMSA_SRVCC_CALL_INCOMING:
        case CALL_IMSA_SRVCC_CALL_WAITING:
        case CALL_IMSA_SRVCC_CALL_ALERTING:
        case CALL_IMSA_SRVCC_CALL_ACTVING:
            ucRst = VOS_TRUE;
            break;


        case CALL_IMSA_SRVCC_CALL_DIALING:
        default:
            ucRst = VOS_FALSE;
            break;
    }

    return ucRst;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_IsDtmfAllowedInCurrentState
 ��������  : ��ǰ״̬�£�DTMF�Ƿ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��24��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8 TAF_CALL_IsDtmfAllowedInCurrentState(VOS_VOID)
{
    VOS_UINT8                           ucLoop;

    /* ��������ʵ�壬�ҳ���Attach�ĺ���ID */
    for (ucLoop = 0; ucLoop < MN_CALL_MAX_NUM; ucLoop++)
    {
        if (VOS_TRUE != f_astCallMgmtEntities[ucLoop].bUsed)
        {
            continue;
        }

        if ( (MN_CALL_S_ACTIVE   == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState)
          || (MN_CALL_S_DIALING  == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState)
          || (MN_CALL_S_ALERTING == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState)
          || (MN_CALL_S_INCOMING == f_astCallMgmtEntities[ucLoop].stCallInfo.enCallState) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_ProcSrvccDtmfBuffInfo
 ��������  : ������SRVCC�����У�IMSA������Ϣ�е�DTMF������Ϣ
 �������  : pstDtmfBuffInfo -- DTMF����ָ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��14��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_CALL_ProcSrvccDtmfBuffInfo(TAF_CALL_DTMF_BUFF_STRU *pstDtmfBuffInfo)
{
    VOS_UINT8                           i;
    TAF_CALL_DTMF_INFO_STRU             stDtmfInfo;

    if ((0                              == pstDtmfBuffInfo->ucNum)
     || (IMSA_CALL_DTMF_REQ_MSG_MAX_NUM < pstDtmfBuffInfo->ucNum))
    {
        return;
    }

    if (VOS_FALSE == TAF_CALL_IsDtmfAllowedInCurrentState())
    {
        /* DTMF�������ڵ�ǰ����״̬�·���DTMF���������� */
        return;
    }

    PS_MEM_SET(&stDtmfInfo, 0, sizeof(TAF_CALL_DTMF_INFO_STRU));

    /* ����DTMF������Ϣ */
    for (i = 0; i < pstDtmfBuffInfo->ucNum; i++)
    {
        stDtmfInfo.CallId      = pstDtmfBuffInfo->astDtmf[i].CallId;
        stDtmfInfo.cKey        = pstDtmfBuffInfo->astDtmf[i].cKey;
        stDtmfInfo.opId        = pstDtmfBuffInfo->astDtmf[i].opId;
        stDtmfInfo.usClientId  = pstDtmfBuffInfo->astDtmf[i].usClientId;
        stDtmfInfo.usOffLength = pstDtmfBuffInfo->astDtmf[i].usOffLength;
        stDtmfInfo.usOnLength  = pstDtmfBuffInfo->astDtmf[i].usOnLength;

        if (TAF_CS_CAUSE_DTMF_BUF_FULL == TAF_CALL_SaveDtmfInfo(&stDtmfInfo))
        {
            MN_ERR_LOG("TAF_CALL_ProcSrvccDtmfBuffInfo: DTMF buffer is full!");
            break;
        }
    }
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_CreateCallEntitiesWithImsCallInfo
 ��������  : ʹ��IMS��ĺ�����Ϣ��������ʵ��
 �������  : pMsg:��Ϣ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��09��25��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��1��7��
    ��    ��   : y00245242
    �޸�����   : �޸�SRVCC�����е�call����ʵ�崴��
  3.��    ��   : 2015��02��28��
    ��    ��   : f00179208
    �޸�����   : IMS SWITCH��Ŀ
  4.��    ��   : 2015��08��30��
    ��    ��   : n00269697
    �޸�����   : srvcc_alert_DTS2015072500266
*****************************************************************************/
VOS_VOID TAF_CALL_CreateCallEntitiesWithImsCallInfo(
    VOS_UINT8                           ucSrvccCallNum,
    CALL_IMSA_SRVCC_CALL_INFO_STRU     *pstSrvccCallInfo,
    VOS_UINT8                           ucStartedHifiFlag
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucCallNum;
    VOS_UINT8                           ucCallStateValid;
    VOS_UINT8                           ucCallId;

    ucCallNum      =  ucSrvccCallNum;

    /* �߽��飬��������Խ�� */
    if (ucCallNum > CALL_IMSA_MAX_ENTITY_NUM)
    {
        ucCallNum = CALL_IMSA_MAX_ENTITY_NUM;
    }

    /* ��ʼ������ʵ�� */
    for(i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        MN_CALL_DeleteCallEntity(i);
    }

    /* SRVCCͬ��������Ϣʱ����ָʾhifi�Ƿ��Ѿ��򿪣�nas���ٸ��ݺ���״̬��local alerting��־�ж� */
    MN_CALL_SetChannelOpenFlg(ucStartedHifiFlag);

    ucIndex = 0;

    for (i = 0; i < ucCallNum; i++)
    {
        /* ����24007Э��,ֻ��Ҫȡimsaͨ��������TI��5��8bit��ΪCC��TIֵ,����TI FLAG+TI VALUE */
        ucTi = pstSrvccCallInfo[i].ucTi >> 4;
        ucTi &= 0x0F;

        /* ����ͨ�����ǲ����Է�����ǿ�Ͷ෽ͨ����������CALLIDΪ1����ͨ���У�CALLIDΪ2����ǿ�Ͷ෽ͨ��
           ��ǿ�Ͷ෽ͨ��hold�󣬿����ٷ���һ·��ͨ���У�Ҳ������ǿ�Ͷ෽ͨ��active��ͨ����hold
           CALLID��Ӧ��ϵ����:
           ��ǿ�Ͷ෽��CALLIDֵΪ1����ͨ���е�CALLIDΪ2
           TI��Ӧ��ϵ����:
           active����ǿ�Ͷ෽��TIֵΪ0,2,3,4,5 ��hold  ����ͨ���е�TIΪ1
           hold  ����ǿ�Ͷ෽��TIֵΪ1,2,3,4,5 ��active����ͨ���е�TIΪ0

           ����Ƕ�·��ͨ���У���ֱ�Ӹ���ʹ��ͬ��������CALLID
         */
        if (VOS_TRUE == pstSrvccCallInfo[i].ucEConferenceFlag)
        {
            /* Ϊ��֤CallId�������ظ���TIֵ��Ψһ�ģ�CallIdͨ��Ti Value��1�����伴�� */
            /* bit7ΪTi Flag, bit0-bit7ΪTi Value */
            ucCallId = (ucTi & 0x07) + 1;

            /* ���CALLIDΪ2����Ҫ��CALLIDתΪ1 */
            if ((CALL_IMSA_SRVCC_CALL_HELD == pstSrvccCallInfo[i].enCallState)
             && (2 == ucCallId))
            {
                ucCallId = 1;
            }
        }
        else
        {
            ucCallId = pstSrvccCallInfo[i].ucCallId;
        }

        /* �Ƿ�CALL IDֱ�Ӷ��� */
        if ((0               == ucCallId)
         || (MN_CALL_MAX_NUM <  ucCallId))
        {
           continue;
        }

        /* call ID��1Ϊ����ʵ�������±� */
        ucIndex         = ucCallId - 1;

        /* call id�Ϸ�ʱ������ʵ����Ϣ */
        if (VOS_TRUE == f_astCallMgmtEntities[ucIndex].bUsed)
        {
            /* call ID�ظ������� */
            continue;
        }

        f_astCallMgmtEntities[ucIndex].bUsed = VOS_TRUE;

        f_astCallMgmtEntities[ucIndex].ulTi  = ucTi;

        f_astCallMgmtEntities[ucIndex].stCallInfo.clientId    = pstSrvccCallInfo[i].clientId;
        f_astCallMgmtEntities[ucIndex].stCallInfo.opId        = pstSrvccCallInfo[i].opId;
        f_astCallMgmtEntities[ucIndex].stCallInfo.callId      = ucCallId;
        f_astCallMgmtEntities[ucIndex].stCallInfo.enCallType  = pstSrvccCallInfo[i].enCallType;
        f_astCallMgmtEntities[ucIndex].stCallInfo.enCallMode  = pstSrvccCallInfo[i].enCallMode;
        f_astCallMgmtEntities[ucIndex].stCallInfo.enCallDir   = pstSrvccCallInfo[i].enCallDir;

        f_astCallMgmtEntities[ucIndex].stCallInfo.enCallState = TAF_CALL_ConvertImsaCallStateToMnCallState(pstSrvccCallInfo[i].enCallState);
        f_astCallMgmtEntities[ucIndex].stCallInfo.enMptyState = pstSrvccCallInfo[i].enMptyState;

        f_astCallMgmtEntities[ucIndex].stCallInfo.enVoiceDomain = TAF_CALL_VOICE_DOMAIN_3GPP;

        /* ����SRVCC��IMSA�����PI��NoCliCause��ֵ��GU,
           ��MT��ʱ�򣬽�������ֵ��ʾ�ĸ�ֵ��ALLOWED��BUTT.
         */
        if (MN_CALL_DIR_MT == pstSrvccCallInfo[i].enCallDir)
        {
            f_astCallMgmtEntities[ucIndex].stCallInfo.enCallingPI   = MN_CALL_PRESENTATION_ALLOWED;
            f_astCallMgmtEntities[ucIndex].stCallInfo.enNoCliCause  = MN_CALL_NO_CLI_BUTT;

            if (0 == pstSrvccCallInfo[i].stCallNumber.ucNumLen)
            {
                f_astCallMgmtEntities[ucIndex].stCallInfo.enNoCliCause = MN_CALL_NO_CLI_USR_REJ;
            }
        }

        PS_MEM_CPY(&(f_astCallMgmtEntities[ucIndex].stCallInfo.stCalledNumber),
                   &(pstSrvccCallInfo[i].stCalledNumber),
                   sizeof(MN_CALL_CALLED_NUM_STRU));

        PS_MEM_CPY(&(f_astCallMgmtEntities[ucIndex].stCallInfo.stCallNumber),
                   &(pstSrvccCallInfo[i].stCallNumber),
                   sizeof(MN_CALL_BCD_NUM_STRU));

        PS_MEM_CPY(&(f_astCallMgmtEntities[ucIndex].stCallInfo.stRedirectNumber),
                   &(pstSrvccCallInfo[i].stRedirectNumber),
                   sizeof(MN_CALL_BCD_NUM_STRU));

        PS_MEM_CPY(&(f_astCallMgmtEntities[ucIndex].stCallInfo.stConnectNumber),
                   &(pstSrvccCallInfo[i].stConnectNumber),
                   sizeof(MN_CALL_BCD_NUM_STRU));

        /* �ж�ͨ��״̬������DIALING, ��ֱ�ӹҶϵ绰 */
        ucCallStateValid    = TAF_CALL_CallStateIsLegal(pstSrvccCallInfo[i].enCallState);
        if (VOS_FALSE == ucCallStateValid)
        {
            if (VOS_TRUE == pstSrvccCallInfo[i].ucEConferenceFlag)
            {
                /* ֱ�ӹҶ���·�绰 */
                MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_RELEASED);

                TAF_CALL_ProcCallStatusFail(ucCallId, pstSrvccCallInfo[i].enCallState);

                MN_CALL_DeleteCallEntity(ucIndex + 1);
            }
            else
            {
                MN_CALL_DeleteCallEntity(ucIndex + 1);
            }

            continue;
        }

        f_astCallMgmtEntities[ucIndex].ucSrvccLocalAlertedFlag = pstSrvccCallInfo[i].ucLocalAlertedFlag;
    }

}

#endif

/*****************************************************************************
 �� �� ��  : TAF_CALL_GetCallEntityAddr
 ��������  : ��ȡcall entity�����׵�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����call entity�׵�ַ����������MN_CALL_MGMT_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��10��11��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
MN_CALL_MGMT_STRU *TAF_CALL_GetCallEntityAddr(VOS_VOID)
{
    return &f_astCallMgmtEntities[0];
}

/* ɾ����ȡ����ʵ����Ŀ */

/* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-25, end */


/*****************************************************************************
 �� �� ��  : TAF_CALL_IsCallRedialCause_CmSrvRej
 ��������  : ԭ��ֵ�Ƿ���Ҫ�ز�(CM_SRV_REJ)
 �������  : NAS_CC_CAUSE_VALUE_ENUM_U32:����ʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ��Ҫ�ز�
             VOS_FALSE:����Ҫ�ز�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��29��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��8��23��
    ��    ��   : n00355355
    �޸�����   : User_exp_Improve
  3.��    ��   : 2016��03��08��
    ��    ��   : l00356716
    �޸�����   : NAS���������Ż�
*****************************************************************************/
VOS_UINT32 TAF_CALL_IsCallRedialCause_CmSrvRej(
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{


    VOS_UINT8                           ucIndex;
    TAF_CALL_REDIAL_CFG_STRU            *pstCallRedialCfg;

    pstCallRedialCfg = MN_CALL_GetCallRedialCfg();

    for (ucIndex = 0; ucIndex < pstCallRedialCfg->stCallRedialCmSrvRejCfg.ucCallRedialCmSrvRejCauseNum; ucIndex++)
    {
        if (enCause == pstCallRedialCfg->stCallRedialCmSrvRejCfg.aucCallRedialCmSrvRejCause[ucIndex] + NAS_CC_CAUSE_CM_SRV_REJ_BEGIN)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_IsCallRedialCause_Disc
 ��������  : ԭ��ֵ�Ƿ���Ҫ�ز�(DISCONNECT)
 �������  : NAS_CC_CAUSE_VALUE_ENUM_U32:����ʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ��Ҫ�ز�
                        VOS_FALSE:����Ҫ�ز�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��03��08��
    ��    ��   : l00356716
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_CALL_IsCallRedialCause_Disc(
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{
    TAF_CALL_REDIAL_CFG_STRU            *pstCallRedialCfg;
    VOS_UINT8                           ucIndex;

    pstCallRedialCfg = MN_CALL_GetCallRedialCfg();

    for (ucIndex = 0; ucIndex < pstCallRedialCfg->stCallRedialDiscCfg.ucCallRedialDiscCauseNum; ucIndex++)
    {
        if (enCause == pstCallRedialCfg->stCallRedialDiscCfg.aucCallRedialDiscCause[ucIndex] + NAS_CC_CAUSE_NW_SECTION_BEGIN)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_IsCallRedialCause_CsfbSrvRej
 ��������  : ԭ��ֵ�Ƿ���Ҫ�ز�(CSFB_SRV_REJ)
 �������  : NAS_CC_CAUSE_VALUE_ENUM_U32:����ʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ��Ҫ�ز�
             VOS_FALSE:����Ҫ�ز�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��29��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_CALL_IsCallRedialCause_CsfbSrvRej(
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{
    /* CSFBʧ�ܲ���Ҫ�ز�����NAS_MM_EndCsfbFlow��ԭ�������other cause����һ�� */

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_IsCallRedialCause_RrConnFail
 ��������  : ԭ��ֵ�Ƿ���Ҫ�ز�(RR_CONN_FAIL)
 �������  : NAS_CC_CAUSE_VALUE_ENUM_U32:����ʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ��Ҫ�ز�
             VOS_FALSE:����Ҫ�ز�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��29��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��8��19��
    ��    ��   : c00318887
    �޸�����   : DTS2015080505192:  ����ָ�ɱ�����Ҫ�ز�
*****************************************************************************/
VOS_UINT32 TAF_CALL_IsCallRedialCause_RrConnFail(
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{
    /* Modified by c00318887 for DTS2015080505192:  ����ָ�ɱ�����Ҫ�ز�, 2015-8-19, begin */
    if ((NAS_CC_CAUSE_RR_CONN_FAIL_ACCESS_BAR                       == enCause)
     || (NAS_CC_CAUSE_RR_CONN_FAIL_CURRENT_PROTOCOL_NOT_SUPPORT     == enCause)
     || (NAS_CC_CAUSE_RR_CONN_FAIL_INVALID_UE_STATE                 == enCause)
     || (NAS_CC_CAUSE_RR_CONN_FAIL_CELL_BARRED                      == enCause))
    /* Modified by c00318887 for DTS2015080505192:  ����ָ�ɱ�����Ҫ�ز�, 2015-8-19, end */
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_IsCallRedialCause_RrRel
 ��������  : ԭ��ֵ�Ƿ���Ҫ�ز�(RR_REL)
 �������  : NAS_CC_CAUSE_VALUE_ENUM_U32:����ʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ��Ҫ�ز�
             VOS_FALSE:����Ҫ�ز�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��29��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��11��23��
    ��    ��   : w00167002
    �޸�����   : DTS2015112307317:NAS_CC_CAUSE_RR_REL_RL_FAILURE�ز���AS����ѡ��
                 �µ�LAC�ϣ����ӵ绰�ɹ��ʡ�
*****************************************************************************/
VOS_UINT32 TAF_CALL_IsCallRedialCause_RrRel(
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{
    /* NAS_CC_CAUSE_RR_REL_AUTH_REJ
       NAS_CC_CAUSE_RR_REL_NAS_REL_REQ����Ҫ�ز� */
    if ( (NAS_CC_CAUSE_RR_REL_AUTH_REJ    == enCause)        
      || (NAS_CC_CAUSE_RR_REL_NAS_REL_REQ == enCause) )
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_IsCallRedialCause_CsfbLmmFail
 ��������  : ԭ��ֵ�Ƿ���Ҫ�ز�(CSFB_LMM_FAIL)
 �������  : NAS_CC_CAUSE_VALUE_ENUM_U32:����ʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ��Ҫ�ز�
             VOS_FALSE:����Ҫ�ز�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��29��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_CALL_IsCallRedialCause_CsfbLmmFail(
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{
    /* CSFBʧ�ܲ���Ҫ�ز�����NAS_MM_EndCsfbFlow��ԭ�������other cause����һ�� */

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_IsCallRedialCause_MmInterErr
 ��������  : ԭ��ֵ�Ƿ���Ҫ�ز�(MM_INTER_ERR)
 �������  : NAS_CC_CAUSE_VALUE_ENUM_U32:����ʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ��Ҫ�ز�
             VOS_FALSE:����Ҫ�ز�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��29��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_CALL_IsCallRedialCause_MmInterErr(
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{
    /* NAS_CC_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL��GU��resume_indʱucCsResumeResultΪfail, GU������쳣��û��Ҫ���ز�
       NAS_CC_CAUSE_MM_INTER_ERR_BACK_TO_LTE��CSFB��ϵͳʧ���ػ�LTE, MMC��ȥGU����������Ҫ�ز�
       NAS_CC_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL NAS_CC_CAUSE_MM_INTER_ERR_EST_SAPI3_FAIL�Ƕ��ŵĴ��󣬱���CALL��Ϊ�쳣�����ز�
       NAS_CC_CAUSE_MM_INTER_ERR_ECALL_INACTIVE ����Ҫ�ز�
       NAS_CC_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT ����Ҫ�ز� */

    switch (enCause)
    {
        /* cs LAU rej #12������NV������ҵ��ʱ�ᴥ�����������������ز� */
        case NAS_CC_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR:
        case NAS_CC_CAUSE_MM_INTER_ERR_CS_DETACH:
        case NAS_CC_CAUSE_MM_INTER_ERR_CS_SIM_INVALID:
        case NAS_CC_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY:
        case NAS_CC_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL:
        case NAS_CC_CAUSE_MM_INTER_ERR_TI_INVALID:
        case NAS_CC_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT:
        case NAS_CC_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST:
        case NAS_CC_CAUSE_MM_INTER_ERR_UE_INVALID_STATE:
        case NAS_CC_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT:
        case NAS_CC_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL:
        case NAS_CC_CAUSE_MM_INTER_ERR_EST_SAPI3_FAIL:
        case NAS_CC_CAUSE_MM_INTER_ERR_ECALL_INACTIVE:
        case NAS_CC_CAUSE_MM_INTER_ERR_REEST_FAIL:
        case NAS_CC_CAUSE_MM_INTER_ERR_CC_REL_REQ:
        case NAS_CC_CAUSE_MM_INTER_ERR_LTE_LIMITED_SERVICE:

            return VOS_FALSE;

        default:
            return VOS_TRUE;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_IsCallRedialCause_CcInterErr
 ��������  : ԭ��ֵ�Ƿ���Ҫ�ز�(CC_INTER_ERR)
 �������  : NAS_CC_CAUSE_VALUE_ENUM_U32:����ʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ��Ҫ�ز�
             VOS_FALSE:����Ҫ�ز�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��29��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_CALL_IsCallRedialCause_CcInterErr(
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{
    if ((NAS_CC_CAUSE_CC_INTER_ERR_T335_TIME_OUT        == enCause)
     || (NAS_CC_CAUSE_CC_INTER_ERR_WAIT_RAB_TIME_OUT    == enCause))
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_IsCallRedialCause
 ��������  : ԭ��ֵ�Ƿ���Ҫ�ز�
 �������  : NAS_CC_CAUSE_VALUE_ENUM_U32:����ʧ��ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_TRUE: ��Ҫ�ز�
             VOS_FALSE:����Ҫ�ز�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��29��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2016��3��8��
    ��    ��   : l00356716
    �޸�����   : ��ӻ���disconnectԭ��ֵ���ж�
*****************************************************************************/
VOS_UINT32 TAF_CALL_IsCallRedialCause(
    NAS_CC_CAUSE_VALUE_ENUM_U32         enCause
)
{
    VOS_UINT32                          ulRslt;

    ulRslt  = VOS_TRUE;
    /* cm service reject */
    if ((enCause >= NAS_CC_CAUSE_CM_SRV_REJ_BEGIN)
     && (enCause <= NAS_CC_CAUSE_CM_SRV_REJ_END))
    {
        ulRslt = TAF_CALL_IsCallRedialCause_CmSrvRej(enCause);
    }

    /* CSFB Service reject */
    else if ((enCause >= NAS_CC_CAUSE_CSFB_SRV_REJ_BEGIN)
          && (enCause <= NAS_CC_CAUSE_CSFB_SRV_REJ_END))
    {
        ulRslt = TAF_CALL_IsCallRedialCause_CsfbSrvRej(enCause);
    }

    /* est_cnfʧ�ܣ���NAS_MM_IsAbleRecover_EstCnfFailResult�Ĵ����߼�����һ�� */
    else if ((enCause >= NAS_CC_CAUSE_RR_CONN_FAIL_BEGIN)
          && (enCause <= NAS_CC_CAUSE_RR_CONN_FAIL_END))
    {
        ulRslt = TAF_CALL_IsCallRedialCause_RrConnFail(enCause);

    }

    /* rel_ind, ���˼�Ȩ���ܣ�����ԭ��ֵ��NAS_MM_IsNeedCmServiceRetry_RelIndResult�Ĵ����߼�����һ�� */
    else if ((enCause >= NAS_CC_CAUSE_RR_REL_BEGIN)
          && (enCause <= NAS_CC_CAUSE_RR_REL_END))
    {
        ulRslt = TAF_CALL_IsCallRedialCause_RrRel(enCause);
    }

    /* ���˼�Ȩ���ܣ�����ԭ��ֵ��ʱ��Ϊ����Ҫ�ز� */
    else if ((enCause >= NAS_CC_CAUSE_CSFB_LMM_FAIL_BEGIN)
          && (enCause <= NAS_CC_CAUSE_CSFB_LMM_FAIL_END))
    {
        ulRslt = TAF_CALL_IsCallRedialCause_CsfbLmmFail(enCause);
    }

    /* MM INTER ERR */
    else if ((enCause >= NAS_CC_CAUSE_MM_INTER_ERR_BEGIN)
          && (enCause <= NAS_CC_CAUSE_MM_INTER_ERR_END))
    {
        ulRslt = TAF_CALL_IsCallRedialCause_MmInterErr(enCause);
    }

    /* T335��ʱ,�ȴ�RAB��ʱ����Ҫ�ز� */
    else if ((enCause >= NAS_CC_CAUSE_CC_INTER_ERR_BEGIN)
          && (enCause <= NAS_CC_CAUSE_CC_INTER_ERR_END))
    {
        ulRslt = TAF_CALL_IsCallRedialCause_CcInterErr(enCause);
    }
    else if (enCause <= NAS_CC_CAUSE_NW_SECTION_END)
    {
        if (VOS_TRUE == TAF_CALL_GetCallRedialForDiscSupportFlg())
        {
            ulRslt = TAF_CALL_IsCallRedialCause_Disc(enCause);
        }
        else
        {
            ulRslt = VOS_FALSE;
        }
    }
    else
    {
        /* ����Ҷϣ�call�ڲ�����vc���󣬲���Ҫ�ز� */
        ulRslt  = VOS_FALSE;
    }

    return ulRslt;
}



/*lint -restore */
#if (FEATURE_ON == FEATURE_HUAWEI_VP)
/*****************************************************************************
 �� �� ��  : MN_CALl_VoicePreferJudgeVoiceCallExist
 ��������  : �������ȹ���:�жϵ�ǰ�Ƿ���ڼ����/���ֵ�����ҵ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��26��
    ��    ��   : s00273135
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALl_VoicePreferJudgeVoiceCallExist(VOS_VOID)
{
    VOS_UINT32      i;

    /* �������к��п���ʵ��*/
    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        /*�ж��Ƿ��ڼ���̬���߱���̬,��������������*/
        if ((VOS_TRUE == f_astCallMgmtEntities[i].bUsed)
         && (MN_CALL_TYPE_VOICE == f_astCallMgmtEntities[i].stCallInfo.enCallType)
         && ((MN_CALL_S_ACTIVE == f_astCallMgmtEntities[i].stCallInfo.enCallState)
          || (MN_CALL_S_HELD == f_astCallMgmtEntities[i].stCallInfo.enCallState)))
        {
            break;
        }
    }

    if (MN_CALL_MAX_NUM == i)
    {
        MN_CALL_VoicePreferSendRabmVoiceCallIndMsg(VOS_FALSE);
    }
    else
    {
        MN_CALL_VoicePreferSendRabmVoiceCallIndMsg(VOS_TRUE);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_VoicePreferSendRabmVoiceCallIndMsg
 ��������  : ��������:֪ͨRABM�Ƿ���ڼ���Ļ��߱��ֵ�����ҵ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��26��
    ��    ��   : s00273135
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALL_VoicePreferSendRabmVoiceCallIndMsg(VOS_UINT32 ulVoiceFlag)
{
    VOS_UINT32                                              ulRet;              /* �������VOS���ͺ����ķ���ֵ */
    CALL_RABM_VOICE_PREFER_CS_EXIST_IND_STRU               *pstMsg;             /* ����ԭ������ָ�� */
    TAF_SDC_PLMN_ID_STRU                                   *pstPlmnId;
    TAF_SDC_PLMN_ID_STRU                                    stPlmnId;

    /* ��ȡ��ǰע�������PLMN,ת��Ϊʮ������BCD��ʽ���ݸ�rabm*/
    pstPlmnId = TAF_SDC_GetCurrCampPlmnId();
    stPlmnId.ulMcc = pstPlmnId->ulMcc;
    stPlmnId.ulMnc = pstPlmnId->ulMnc;

    TAF_SDC_PlmnId2Bcd(&stPlmnId);

    /* �����ڴ�  */
    pstMsg = (CALL_RABM_VOICE_PREFER_CS_EXIST_IND_STRU *)PS_ALLOC_MSG(WUEPS_PID_RABM,
                                               sizeof(CALL_RABM_VOICE_PREFER_CS_EXIST_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsg)
    {
        /* �ڴ�����ʧ�� */
        MN_ERR_LOG("MN_CALL_VoicePreferSendRabmVoiceCallIndMsg:ERROR: Memory Alloc Error for pstMsg");
        return ;
    }

    /* ��д��ز��� */
    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_TAF;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_RABM;
    pstMsg->MsgHeader.ulLength          = sizeof(CALL_RABM_VOICE_PREFER_CS_EXIST_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = CALL_RABM_VOICEPREFER_CS_EXIST_IND;

    pstMsg->ulVoiceFlag                 = ulVoiceFlag;
    pstMsg->ulCampMcc                   = stPlmnId.ulMcc;
    pstMsg->ulCampMnc                   = stPlmnId.ulMnc;

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstMsg);
    if ( VOS_OK != ulRet )
    {
        MN_ERR_LOG("MN_CALL_VoicePreferSendRabmVoiceCallIndMsg:ERROR:PS_SEND_MSG ");
        return ;
    }

    return;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

