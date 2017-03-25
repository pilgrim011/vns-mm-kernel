/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnCall.c
  �� �� ��   : ����
  ��    ��   : ���� 49431
  ��������   : 2007��9��20��
  ����޸�   : 2007��9��20��
  ��������   : ʵ��CCA��TAF����ģ���ṩ���ⲿ�ӿ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ļ�

  2.��    ��   : 2010��3��2��
    ��    ��   : zhoujun /z40661
    �޸�����   : NAS R7Э������

  3.��    ��   : 2010��4��8��
    ��    ��   : zhoujun /z40661
    �޸�����   : �����õ�ǰCODEC����

  4.��    ��   : 2010��8��9��
    ��    ��   : zhoujun /40661
    �޸�����   : ֧��UUS1
  2.��    ��   : 2010��11��11��
    ��    ��   : h44270
    �޸�����   : ���ⵥ�ţ�DTS2010102202190/DTS2010110600922������ERROR��ӡ
******************************************************************************/
/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "MnCallProcNvim.h"
#include "MnCall.h"
#include "MnCallReqProc.h"
#include "MnCallMnccProc.h"
#include "MnCallMgmt.h"
#include "MnCallApi.h"
#include "MnCallBcProc.h"
#include "NasCc.h"
#include "PsNvId.h"
#include "NVIM_Interface.h"
#include "VcCallInterface.h"
#include "UsimPsInterface.h"
#include "MnCallCstProc.h"
#include "MnCallTimer.h"
#include "CstNasInterface.h"
#include "RabmTafInterface.h"
#include "NasOmInterface.h"

#include "MnCallSendCc.h"
#include "MnComm.h"
#include "MnCallMgmt.h"
#include "NVIM_Interface.h"
#include "MnCallCtx.h"

/* Added by l00167671 for NV�����Ŀ , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV�����Ŀ , 2013-05-17, end*/
#include "NasUsimmApi.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "NasComm.h"
#endif
#include "TafSdcCtx.h"
#include "TafSdcLib.h"

/* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-2, begin */
#include "MnCallProcVc.h"
#include "MnCallMnccProc.h"
#include "MnCallProcTaf.h"
#include "MnCallProcMma.h"
/* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-2, end */

#include "TafMmaInterface.h"
#include "TafInternalInterface.h"

#include "TafCsCallMain.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

/* Deleted by z00234330 for pclint ����  ��Ŀ, 2014-07-03, begin */
/* Deleted by z00234330 for pclint ����  ��Ŀ, 2014-07-03, end */

/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, begin */
/* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-16, end */

/*****************************************************************************
   2 ��������
*****************************************************************************/
/* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, begin */
/* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-9, end */

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */

extern    VOS_VOID MN_CALL_SetTchStatus(
    VOS_BOOL                            bAvailable
);
/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-11, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2014-2-11, end */

/*lint -save -e958 */


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : MN_CALL_Init
 ��������  : ִ��CCAģ��ĳ�ʼ�����������к���״̬�ĸ�λ��ȫ����Դ�ĳ�ʼ��
             TAFӦ����ϵͳ����ʱ��Resetʱ���øýӿ�
 �������  : enPowerState - ������ػ�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��4��20��
    ��    ��   : z00161729
    �޸�����   : ���ⵥAT2D18405
  3.��    ��   : 2010��8��22��
    ��    ��   : z00161729
    �޸�����   : ���ⵥATD2010081901568:��ػ����δ֮ͣǰ�������Ķ�ʱ��
  4.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ :nvim��ʼ��
  4.��    ��   : 2012��3��2��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : C50_IPC Project, CS ���г�ʼ����������FDN�������û�ȡ

  5.��    ��   : 2012��6��11��
    ��    ��   : w00166186
    �޸�����   : AT&T&DCM��Ŀ
  6.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  7.��    ��   : 2012��10��29��
    ��    ��   : z00161729
    �޸�����   : DTS2012083102536:֧��cc�����ؽ�
  8.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
  9.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
 10.��    ��   : 2014��04��18��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature�޸�

  12.��    ��   : 2014��7��2��
    ��    ��   : z00234330
    �޸�����   : PCLINT����
*****************************************************************************/
VOS_VOID  MN_CALL_Init(MN_CALL_POWER_STATE_ENUM_U8 enPowerState)
{

    MN_CALL_InitCtx();

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    /*��ȡNIM��Ϣ*/
    MN_CALL_ReadNvimInfo();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    MN_CALL_InitAllTimers(enPowerState);

    MN_CALL_CapaProcInit();

    /* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
    /* �Ƹô�ʵ�ֵ�power off ���� */
    /* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, end */

    MN_CALL_ResetAllCalls(enPowerState);
    MN_CALL_SetTchStatus(VOS_FALSE);

    /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-18, begin */
    /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-18, end */

    /* Deleted by z00234330 for pclint ����  ��Ŀ, 2014-07-03, begin */
    /* Deleted by z00234330 for pclint ����  ��Ŀ, 2014-07-03, end */


    /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */

    /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */

    /* Added by l00198894 for V9R1 STK����, 2013/07/11, begin */
    TAF_CALL_InitDtmfCtx();
    /* Added by l00198894 for V9R1 STK����, 2013/07/11, end */

    return;
}


/*****************************************************************************
 �� �� ��  : MN_CALL_LineInfo
 ��������  : �յ�����λ��Ϣ���NVIM�л�ȡ��ǰѡ�����·
 �������  : enUsimStatus:��ǰ���Ƿ���λ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��1��25��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  3.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
  4.��    ��   : 2013��6��5��
    ��    ��   : w00242748
    �޸�����   : SVLTE��USIM�ӿ�����
*****************************************************************************/
VOS_VOID MN_CALL_LineInfo(
    MNPH_USIM_STATUS_ENUM_U32           enUsimStatus
)
{
    MN_CALL_ALS_LINE_INFO_STRU          stAlsInfo;
    VOS_UINT8                           aucMmaImsi[9];
    VOS_BOOL                            bWriteNvim;
    VOS_UINT32                          ulLength;
    VOS_UINT32                          ulGetCardImsiRslt;

    ulGetCardImsiRslt   = USIMM_API_RESULT_BUTT;

    ulLength = 0;
    stAlsInfo.enAlsLine = MN_CALL_ALS_LINE_NO_BUTT;
    PS_MEM_SET(stAlsInfo.aucMmaImsi, 0x00, sizeof(stAlsInfo.aucMmaImsi));

    if ( MNPH_USIM_STATUS_AVILABLE == enUsimStatus )
    {
        bWriteNvim = VOS_FALSE;

        if ( NV_OK != NV_Read(en_NV_Item_ALS_LINE_Config,&stAlsInfo,sizeof(stAlsInfo)))
        {
            return;
        }

        ulGetCardImsiRslt   = NAS_USIMMAPI_GetCardIMSI(aucMmaImsi);
        if ( USIMM_API_SUCCESS !=  ulGetCardImsiRslt)
        {
            if (VOS_TRUE == TAF_SDC_IsImsiAvailableInCurrSimStatus(TAF_SDC_GetSimStatus()))
            {

#if (FEATURE_ON == FEATURE_PTM)
                /* ��¼��ȡ��IMSI�쳣log */
                TAF_SDC_GetCardImsiFailRecord(ulGetCardImsiRslt, aucMmaImsi);
#endif
            }

            return ;
        }

        /*��·��ֵ����ȡֵ��Χ��*/
        if  ( ( MN_CALL_ALS_LINE_NO_1 != stAlsInfo.enAlsLine )
           && ( MN_CALL_ALS_LINE_NO_2 != stAlsInfo.enAlsLine ) )
        {
            stAlsInfo.enAlsLine = MN_CALL_ALS_LINE_NO_1;
            bWriteNvim = VOS_TRUE;
        }

        /*�ж�NV�е�ǰʹ����·�Ŷ�Ӧ��IMSI��SIM����IMSI�Ƿ���ͬ������ͬ����NV
          �������Ĭ����·��1*/
        if ( 0 != VOS_StrCmp( (VOS_CHAR *)aucMmaImsi,
                               (VOS_CHAR *)stAlsInfo.aucMmaImsi) )
        {
            stAlsInfo.enAlsLine = MN_CALL_ALS_LINE_NO_1;
            PS_MEM_CPY(stAlsInfo.aucMmaImsi,aucMmaImsi,9);
            bWriteNvim = VOS_TRUE;
        }

        /*��Ҫ����NVIM*/
        if ( VOS_TRUE == bWriteNvim )
        {
            (VOS_VOID)NV_GetLength(en_NV_Item_ALS_LINE_Config, &ulLength);
            if (NV_OK != NV_Write(en_NV_Item_ALS_LINE_Config,
                     &stAlsInfo,
                     ulLength) )
            {
                TAF_WARNING_LOG(WUEPS_PID_TAF, "MN_CALL_LineInfo: en_NV_Item_ALS_LINE_Config NV Write Fail!");
            }
        }

        (VOS_VOID)MN_CALL_UpdateAlsLineInfo(stAlsInfo.enAlsLine,VOS_FALSE);
    }
}

/*****************************************************************************
 �� �� ��  : MN_CALL_ProcAppReqMsg
 ��������  : ��������Ӧ�ò��������Ϣ
             �ú���������������ͽ���Ϣ�ַ�����Ӧ����������ȥ����
 �������  : pstMsg - Ӧ�ò����TAF APIʱ��API���������������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��10��06��
    ��    ��   : f00179208
    �޸�����   : AT��ֲ��Ŀ,������Ϣ�����֧
  3.��    ��   : 2012��06��11��
    ��    ��   : w00166186
    �޸�����   : AT&T&DCM���ӽ����������ϱ�
  4.��    ��   : 2012��09��18��
    ��    ��   : y00213812
    �޸�����   : STK&DCM��Ŀ�� �����¼�����
  5.��    ��   : 2013��4��8��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
  6.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  7.��    ��   : 2014��04��15��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature�����޸�
*****************************************************************************/
VOS_VOID  MN_CALL_ProcAppReqMsg(
    const VOS_VOID                      *pstMsg
)
{

    MN_CALL_APP_REQ_MSG_STRU            *pstCallMsg;

    pstCallMsg = (MN_CALL_APP_REQ_MSG_STRU*)pstMsg;

    MN_NORM_LOG1("MN_CALL_ProcAppReqMsg: enAppReq:", (VOS_INT32)pstCallMsg->enReq);
    /* ������Ϣ�е�Ӧ���������ͣ�����Ϣ������Ӧ�������������� */

/*�طŹ��ָ̻�ȫ�ֱ���*/
#ifdef __PS_WIN32_RECUR__
    if ( VOS_TRUE == NAS_CALL_RestoreContextData((struct MsgCB*)pstMsg))
    {
        return;
    }
#endif

    switch (pstCallMsg->enReq)
    {
    case MN_CALL_APP_ORIG_REQ:
/*PC�طŵ���ȫ�ֱ���ʹ��*/
#ifndef __PS_WIN32_RECUR__
        NAS_CALL_SndOutsideContextData();
#endif
        MN_CALL_CallOrigReqProc(pstCallMsg->clientId,
                                pstCallMsg->opId,
                                pstCallMsg->callId,
                                (MN_CALL_ORIG_PARAM_STRU*)&pstCallMsg->unParm);
        break;

    case MN_CALL_APP_END_REQ:
        MN_CALL_CallEndReqProc(pstCallMsg->clientId,
                               pstCallMsg->opId,
                               pstCallMsg->callId,
                               (MN_CALL_END_PARAM_STRU*)&pstCallMsg->unParm);
        break;

    case MN_CALL_APP_ANSWER_REQ:
        MN_CALL_CallAnswerReqProc(pstCallMsg->clientId,
                                  pstCallMsg->opId,
                                  pstCallMsg->callId,
                                  (MN_CALL_ANS_PARAM_STRU*)&pstCallMsg->unParm);
        break;

    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    case MN_CALL_APP_START_DTMF_REQ:
        TAF_CALL_RcvStartDtmfReq((struct MsgCB *)pstCallMsg);
        break;

    case MN_CALL_APP_STOP_DTMF_REQ:
        TAF_CALL_RcvStopDtmfReq((struct MsgCB *)pstCallMsg);
        break;

    case MN_CALL_APP_SUPS_CMD_REQ:
        MN_CALL_CallSupsCmdReqProc((struct MsgCB *)pstCallMsg);
        break;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

    case MN_CALL_APP_GET_INFO_REQ:
        MN_CALL_CallInfoReqProc(pstCallMsg->clientId,
                                pstCallMsg->opId);
        break;

    case MN_CALL_APP_GET_CDUR_REQ:
        MN_CALL_GetCdur(pstCallMsg->clientId,
                        pstCallMsg->opId,
                        pstCallMsg->callId);
        break;
    case MN_CALL_APP_SET_UUSINFO_REQ:
        MN_CALL_SetUus1Info(pstCallMsg->clientId,
                            pstCallMsg->opId,
                            (MN_CALL_UUS1_PARAM_STRU*)&pstCallMsg->unParm);
        break;
    case MN_CALL_APP_QRY_UUSINFO_REQ:
        MN_CALL_QryUus1Info(pstCallMsg->clientId,
                            pstCallMsg->opId);
        break;
    case MN_CALL_APP_SET_ALS_REQ:
        MN_CALL_SetAls(pstCallMsg->clientId,
                       pstCallMsg->opId,
                       (MN_CALL_SET_ALS_PARAM_STRU*)&pstCallMsg->unParm);
        break;
    case MN_CALL_APP_QRY_ALS_REQ:
        MN_CALL_QryAls(pstCallMsg->clientId,
                       pstCallMsg->opId);
        break;

    /* Added by w00199382 for PS Project��2011-12-06,  Begin*/

    /*AT��ȡCALLINFO��ͬ��API��Ϣ����*/
    case ID_TAFAGENT_MN_GET_CALL_INFO_REQ:
        MN_CALL_RcvTafAgentGetCallInfo();
        break;

    /* Added by w00199382 for PS Project��2011-12-06,  End*/

    case MN_CALL_APP_CUSTOM_ECC_NUM_REQ:
        MN_CALL_RcvTafEccNumReq((MN_CALL_APP_CUSTOM_ECC_NUM_REQ_STRU*)&pstCallMsg->unParm);
        break;

    case MN_CALL_APP_CLPR_GET_REQ:
        MN_CALL_RcvAtClprGetReq(pstCallMsg);
        break;

    /* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-8, begin */
    case MN_CALL_APP_SET_CSSN_REQ:
        MN_CALL_RcvAtCssnSetReq(pstCallMsg->clientId,
                                pstCallMsg->opId,
                                (MN_CALL_SET_CSSN_REQ_STRU*)&pstCallMsg->unParm);
        break;
    /* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-8, begin */

    case MN_CALL_APP_XLEMA_REQ:
        MN_CALL_RcvAtXlemaReq(pstCallMsg);
        break;

    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-3-29, begin */
#if (FEATURE_ON == FEATURE_ECALL)
    case MN_CALL_QRY_ECALL_INFO_REQ:
        TAF_CALL_RcvQryEcallInfoReq((MN_CALL_QRY_ECALL_INFO_REQ_STRU *)pstCallMsg);
        break;
#endif
    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-3-29, end */

    case TAF_CALL_APP_CCWAI_SET_REQ:
        TAF_CALL_RcvCcwaiSetReq(pstCallMsg);
        break;

    default:
        MN_WARN_LOG("MN_CALL_ProcAppReqMsg:Invalid Msg Name");
        break;

    }


}

/*****************************************************************************
 �� �� ��  : MN_CALL_ModifyCallId
 ��������  : ����INCOMING״̬���յ���CC��Ϣ��CALLID
             ���CC���յ�CALL CONFIRM��Ϣǰ��CC��CALLģ��CALL ID��ͬ������
 �������  : MNCC_IND_PRIM_MSG_STRU           *pstMsg
 �������  : MNCC_IND_PRIM_MSG_STRU           *pstMsg
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��3��15��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALL_ModifyCallId(MNCC_IND_PRIM_MSG_STRU           *pstMsg)
{
    VOS_UINT32                          ulLoop;
    MN_CALL_MGMT_STRU                  *pstMgmtEntity;

    /* ��Ϣ��CALL ID����Ч��Χ����Ҫ�޸� */
    if ((pstMsg->ucCallId > 0)
     && (pstMsg->ucCallId <= MN_CALL_MAX_NUM))
    {
        return;
    }

    pstMgmtEntity = PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_CALL_MGMT_STRU));
    if (VOS_NULL_PTR == pstMgmtEntity)
    {
        return;
    }

    /*
       ��ȡCALL��������ϢTIƥ���ʵ�壬����CALL ID����Ϣ��
       ʹ�ù����еĺ���ʵ�壬״̬��INCOMING״̬����TI��ͬ������ʵ���CALL ID����Ϣ
    */
    for (ulLoop = 0; ulLoop < MN_CALL_MAX_NUM; ulLoop++)
    {
        MN_CALL_GetMgmtEntityInfoByCallId((VOS_UINT8)(ulLoop + 1), pstMgmtEntity);
        if (VOS_TRUE != pstMgmtEntity->bUsed)
        {
            continue;
        }

        if (MN_CALL_S_INCOMING != pstMgmtEntity->stCallInfo.enCallState)
        {
            continue;
        }

        if ((VOS_UINT8)pstMgmtEntity->ulTi == pstMsg->ucTi)
        {
            pstMsg->ucCallId = (VOS_UINT8)pstMgmtEntity->stCallInfo.callId;
            break;
        }
    }

    PS_MEM_FREE(WUEPS_PID_TAF, pstMgmtEntity);

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_ProcMnccPrimMsg
 ��������  : ��������CC��MNCCԭ����Ϣ
             �ú�������ԭ��������Ϣ�ַ�����Ӧ��MNCCԭ�ﴦ����ȥ����
 �������  : pMsg - ����CC��MNCCԭ����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��6��11��
    ��    ��   : w00166186
    �޸�����   : AT&T&DCM��Ŀ
  3.��    ��   : 2012��09��20��
    ��    ��   : f62575
    �޸�����   : STK&DCM ��Ŀ
  4.��    ��   : 2013��01��29��
    ��    ��   : Y00213812
    �޸�����   : DTS2013012909872,��¼CALL�Ҷϵķ���
  5.��    ��   : 2013��03��18��
    ��    ��   : f62575
    �޸�����   : DTS2013031502471,���CC���յ�CALL CONFIRM��Ϣǰ��CC��CALLģ��CALL ID��ͬ������
  6.��    ��   : 2013��04��12��
    ��    ��   : f62575
    �޸�����   : DTS2013041503184,���3G��RADIO LINK FAILUREû�а�Э��Ҫ����������ͷ��¼�����
                 ���ں����ؽ�ʧ�ܺ��ϱ���UICC���˴�ɾ��MNCC_RADIO_LINK_FAILURE��֧
  7.��    ��   : 2013��09��24��
    ��    ��   : w00176964
    �޸�����   : VoLTE_PhaseII ��Ŀ�޸�:����SRVCC��״̬֪ͨ��Ϣ�Ĵ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcMnccPrimMsg(
    const VOS_VOID                      *pMsg
)
{
    MNCC_IND_PRIM_MSG_STRU              *pstMnccMsg;
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    pstMnccMsg = (MNCC_IND_PRIM_MSG_STRU*)pMsg;
    MN_NORM_LOG1("MN_CALL_ProcAppReqMsg: enPrimName:", pstMnccMsg->enPrimName);

    /* ������Ϣ�е�ԭ����������Ϣ������Ӧ��MNCCԭ�ﴦ�������� */
    switch(pstMnccMsg->enPrimName)
    {
    case MNCC_SETUP_IND:
/*PC�طŵ���ȫ�ֱ���ʹ��*/
#ifndef __PS_WIN32_RECUR__
        NAS_CALL_SndOutsideContextData();
#endif
        MN_CALL_ProcMnccSetupInd(pstMnccMsg);
        break;

    case MNCC_SETUP_CNF:
        MN_CALL_ProcMnccSetupCnf(pstMnccMsg);
        break;

    case MNCC_SETUP_COMPL_IND:
        MN_CALL_ProcMnccSetupComplInd(pstMnccMsg);
        break;

    case MNCC_CALL_PROC_IND:
        MN_CALL_ProcMnccCallProcInd(pstMnccMsg);
        break;

    case MNCC_ALERT_IND:
        MN_CALL_ProcMnccAlertInd(pstMnccMsg);
        break;

    case MNCC_DISC_IND:
        MN_CALL_ProcMnccDiscInd(pstMnccMsg);
        break;

    case MNCC_REL_IND:
        MN_CALL_ProcMnccRelInd(pstMnccMsg);
        break;

    case MNCC_REL_CNF:
        MN_CALL_ModifyCallId(pstMnccMsg);
        MN_CALL_ProcMnccRelCnf(pstMnccMsg);
        break;

    case MNCC_REJ_IND:
        MN_CALL_ProcMnccRejInd(pstMnccMsg);
        break;

    case MNCC_FACILITY_IND:
        MN_CALL_ProcMnccFacilityInd(pstMnccMsg);
        break;

    case MNCC_FACILITY_LOCAL_REJ:
        MN_CALL_ProcMnccFacilityLocalRej(pstMnccMsg);
        break;

    case MNCC_HOLD_CNF:
        MN_CALL_ProcMnccHoldCnf(pstMnccMsg);
        break;

    case MNCC_HOLD_REJ:
        MN_CALL_ProcMnccHoldRej(pstMnccMsg);
        break;

    case MNCC_RETRIEVE_CNF:
        MN_CALL_ProcMnccRetrieveCnf(pstMnccMsg);
        break;

    case MNCC_RETRIEVE_REJ:
        MN_CALL_ProcMnccRetrieveRej(pstMnccMsg);
        break;

    /* Modified by l00198894 for V9R1 STK����, 2013/07/11, begin */
    case MNCC_START_DTMF_CNF:
        TAF_CALL_RcvCcStartDtmfCnf(pstMnccMsg);
        break;

    case MNCC_START_DTMF_REJ:
        TAF_CALL_RcvCcStartDtmfRej(pstMnccMsg);
        break;

    case MNCC_STOP_DTMF_CNF:
        TAF_CALL_RcvCcStopDtmfCnf(pstMnccMsg);
        break;
    /* Modified by l00198894 for V9R1 STK����, 2013/07/11, end */

    case MNCC_MODIFY_IND:
        /* in-call modification, CC�ݲ�֧�� */
        break;

    case MNCC_MODIFY_CNF:
        /* in-call modification, CC�ݲ�֧�� */
        break;

    case MNCC_MODIFY_REJ_IND:
        /* in-call modification, CC�ݲ�֧�� */
        break;

    case MNCC_SYNC_IND:
        MN_CALL_ProcMnccSyncInd(pstMnccMsg);
        break;

    case MNCC_PROGRESS_IND:
        MN_CALL_ProcMnccProgressInd(pstMnccMsg);
        break;

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    case MNCC_CC_EST_IND:

        /*�������CCBS��NV�򿪣�����*/
        if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
        {
            MN_CALL_ProcMnccEstInd(pstMnccMsg);
        }
        break;

    case MNCC_RECALL_IND:

        /*�������CCBS��NV�򿪣�����*/
        if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
        {
            MN_CALL_ProcMnccRecallInd(pstMnccMsg);
        }
        break;
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    case MNCC_UUSINFO_IND:
        MN_CALL_ProcUusInfoInd(pstMnccMsg);
        break;

    case MNCC_EMERGENCY_LIST_IND:
        MN_CALL_ProcEmergencyListInd(pstMnccMsg);
        break;

    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-24, begin */
#if (FEATURE_ON == FEATURE_IMS)
    case MNCC_SRVCC_STATUS_IND:
        TAF_CALL_ProcMnccSrvccStatusInd((MNCC_SRVCC_STATUS_IND_STRU*)&(pstMnccMsg->unParam.stSrvccStaInd));
        break;
#endif
    /* Added by w00176964 for VoLTE_PhaseII ��Ŀ, 2013-9-24, end */

    default:
        MN_WARN_LOG("MN_CALL_ProcAppReqMsg:Invalid Msg Name");
        break;
    }

}

/* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, begin */
/* ɾ���ú��� */
/* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-29, end */

/*****************************************************************************
 �� �� ��  : MN_CALL_ProcVCMsg
 ��������  : ��������VCģ�����Ϣ
 �������  : pstMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��1��10��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��09��18��
    ��    ��   : y00213812
    �޸�����   : STK&DCM ��ĿCS��������ϱ����޸��ϱ���ʼֵ
  3.��    ��   : 2013��9��17��
    ��    ��   : f62575
    �޸�����   : DTS2013091104858���һ�ǰ������ɵ��û�����
  4.��    ��   : 2014��04��15��
    ��    ��   : y00245242
    �޸�����   : ΪeCall feature�����޸�
*****************************************************************************/
VOS_VOID  MN_CALL_ProcVCMsg (VOS_VOID * pstMsg)
{
    VC_CALL_MSG_STRU                    *pstTmpMsg;
    /* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-4, begin */
    /* Deleted by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-4, end */

    pstTmpMsg = (VC_CALL_MSG_STRU*)pstMsg;

    switch(pstTmpMsg->enMsgName)
    {
        case VC_CALL_END_CALL:
            /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-4, begin */
            TAF_CALL_RcvVcCallEndCall(pstTmpMsg);
            /* Modified by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-4, end */
            break;

        /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-1, begin */
#if (FEATURE_ON == FEATURE_ECALL)
        case VC_CALL_ECALL_TRANS_STATUS_NTF:
            TAF_CALL_RcvVcEcallTransStatusNtf((VC_CALL_ECALL_TRANS_STATUS_NTF_STRU *)pstMsg);
            break;
#endif
        /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-1, end */

        default:
            MN_WARN_LOG1("MN_CALL_ProcVCMsg:Wrong Msg.", pstTmpMsg->enMsgName);
            break;
    }
}

/* Deleted by wx270776 for OM�ں�, 2015-7-10, begin */


/* Deleted by wx270776 for OM�ں�, 2015-7-10, end */
/*****************************************************************************
 �� �� ��  : MN_CALL_ProcOmConfigGsmCodec
 ��������  : �����ظ�OM���͹���������GSM CODEC���͵�����
 �������  : pstMsg - OM ���͹�����������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��9��
    ��    ��   : zhoujun /z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��07��24��
    ��    ��   : wx270776
    �޸�����   : OM�ں�
*****************************************************************************/
VOS_VOID MN_CALL_ProcOmConfigGsmCodec(
    ID_NAS_OM_INQUIRE_STRU              *pstMsg
)
{
    /* Modified by wx270776 for OM�ں�, 2015-7-25, begin */
    NAS_OM_SET_GSM_CODEC_CONFIG_REQ_STRU *pstCodecConfigReq = VOS_NULL_PTR;
    NAS_OM_SET_GSM_CODEC_CONFIG_CNF_STRU *pstCodecConfigCnf = VOS_NULL_PTR;
    VOS_UINT32                            ulMsgLen;
    VOS_UINT32                            ulRet;

    /* ������Ϣ */
    ulMsgLen          = sizeof(NAS_OM_SET_GSM_CODEC_CONFIG_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstCodecConfigCnf = (NAS_OM_SET_GSM_CODEC_CONFIG_CNF_STRU*)PS_ALLOC_MSG(WUEPS_PID_TAF, ulMsgLen);
    if (VOS_NULL_PTR == pstCodecConfigCnf)
    {
         MN_ERR_LOG("MN_CALL_ProcOmConfigGsmCodec:Error: Memory Alloc fail");
         return;
    }

    /* ��ʼ�� */
    PS_MEM_SET((VOS_UINT8*)pstCodecConfigCnf + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLen);

    pstCodecConfigReq = (NAS_OM_SET_GSM_CODEC_CONFIG_REQ_STRU*)pstMsg;

    /* ��д��Ϣ���� */
    pstCodecConfigCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstCodecConfigCnf->ulMsgId          = ID_NAS_OM_SET_CODEC_TYPE_CONFIRM;
    pstCodecConfigCnf->usOriginalId     = pstMsg->usOriginalId;
    pstCodecConfigCnf->usTerminalId     = pstMsg->usTerminalId;
    pstCodecConfigCnf->ulTimeStamp      = pstMsg->ulTimeStamp;
    pstCodecConfigCnf->ulSN             = pstMsg->ulSN;

    /* ���ð汾��ֹ�����ã���ֻ����֧�ֲ�����������ģʽʱֱ�ӷ���ʧ�� */
    if (NAS_OM_GSM_CODEC_FR_EFR_HR_AMR != pstCodecConfigReq->enGsmCodec)
    {
        MN_WARN_LOG("MN_CALL_ProcOmConfigGsmCodec:GsmCodec is not NAS_OM_GSM_CODEC_FR_EFR_HR_AMR");

        pstCodecConfigCnf->ulRet = VOS_ERR;

        /* ������Ϣ */
        PS_SEND_MSG(WUEPS_PID_TAF, pstCodecConfigCnf);

        return;
    }

    ulRet = MN_CALL_ConfigGsmCapaProc(pstCodecConfigReq->enGsmCodec);
    if ( VOS_OK ==  ulRet)
    {
        pstCodecConfigCnf->ulRet = VOS_OK;
    }
    else
    {
        pstCodecConfigCnf->ulRet = VOS_ERR;
    }

    /* ������Ϣ */
    PS_SEND_MSG(WUEPS_PID_TAF, pstCodecConfigCnf);

    return;
    /* Modified by wx270776 for OM�ں�, 2015-7-25, end */
}

/*****************************************************************************
 �� �� ��  : MN_CALL_ProcOmCodecRpt
 ��������  : ����OM���͹����Ĳ�ѯ��ǰCODEC���ͺ����õ�GSM��CODEC����
 �������  : pstMsg - OM ���͹����Ĳ�ѯ��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��9��
    ��    ��   : zhoujun /z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  3.��    ��   : 2015��7��13��
    ��    ��   : wx270776
    �޸�����   : OM�ں�
*****************************************************************************/
VOS_VOID MN_CALL_ProcOmCodecRpt(
    ID_NAS_OM_INQUIRE_STRU              *pstMsg
)
{
    /* Modified by wx270776 for OM�ں�, 2015-7-13, begin */
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulRet;
    NAS_OM_CODEC_TYPE_CNF_STRU         *pstCodecTypeCnf = VOS_NULL_PTR;
    MN_CALL_CHANNEL_PARAM_STRU          stChannParm;



    /* �����ڴ� */
    ulMsgLen        = sizeof(NAS_OM_CODEC_TYPE_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstCodecTypeCnf = (NAS_OM_CODEC_TYPE_CNF_STRU*)PS_ALLOC_MSG(WUEPS_PID_TAF, ulMsgLen);
    if (VOS_NULL_PTR == pstCodecTypeCnf)
    {
        MN_ERR_LOG("MN_CALL_ProcOmCodecRpt:Error: Memory Alloc fail");
        return;
    }

    /* ��ʼ�� */
    PS_MEM_SET((VOS_UINT8*)pstCodecTypeCnf + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLen);

    /* �����Ϣ */
    pstCodecTypeCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstCodecTypeCnf->ulMsgId          = ID_NAS_OM_CODEC_TYPE_CONFIRM;
    pstCodecTypeCnf->usOriginalId     = pstMsg->usOriginalId;
    pstCodecTypeCnf->usTerminalId     = pstMsg->usTerminalId;
    pstCodecTypeCnf->ulTimeStamp      = pstMsg->ulTimeStamp;
    pstCodecTypeCnf->ulSN             = pstMsg->ulSN;

    ulRet = MN_CALL_GetTchParm(&stChannParm);
    if( VOS_OK == ulRet )
    {
        pstCodecTypeCnf->enCurrCodec = MN_CALL_ConvertMnCodecToOmCodec(stChannParm.enCodecType);
    }
    else
    {
        pstCodecTypeCnf->enCurrCodec  = NAS_OM_CODEC_TYPE_BUTT;
    }

    pstCodecTypeCnf->enGsmCodecConfig = MN_CALL_ConvertSpeechVers();

    /* ������Ϣ */
    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstCodecTypeCnf);
    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("MN_CALL_ProcOmCodecRpt:Warning Send msg fail.");
    }

    return;
    /* Modified by wx270776 for OM�ں�, 2015-7-13, end */
}


/*****************************************************************************
 �� �� ��  : MN_CALL_ProcOmMsg
 ��������  : CALLģ�鴦������OM������
 �������  : pstMsg     - OM���͹�������Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��4��8��
    ��    ��   : zhoujun /z40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_CALL_ProcOmMsg(
    VOS_VOID                            *pstMsg
)
{
    ID_NAS_OM_INQUIRE_STRU              *pstOmInquire;

    pstOmInquire = (ID_NAS_OM_INQUIRE_STRU *)pstMsg;

    switch ( pstOmInquire->ulMsgId)
    {
        case ID_NAS_OM_SET_CODEC_TYPE_REQUIRE :
            MN_CALL_ProcOmConfigGsmCodec(pstOmInquire);
            break;

        case ID_NAS_OM_CODEC_TYPE_INQUIRE :
            MN_CALL_ProcOmCodecRpt(pstOmInquire);
            break;

        default:
            MN_NORM_LOG("MN_CALL_ProcOmMsg:wrong PrimId!");
            break;
    }

}


/*****************************************************************************
 �� �� ��  : MN_CALL_ProcCstCcPrimitive
 ��������  : ����CSTģ�鷢������Ϣԭ��
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcCstCallPrimitive(
    const VOS_VOID                      *pMsg
)
{
    VOS_UINT16                           usMsgType;

    usMsgType =  *((VOS_UINT16*)((VOS_UINT8*)pMsg + VOS_MSG_HEAD_LENGTH));

    MN_INFO_LOG1("MN_CALL_ProcCstCcPrimitive: primitive:", (VOS_INT32)(usMsgType));

    switch ( usMsgType )
    {
        case ID_CST_CALL_ERROR_IND :
            MN_CALL_ProcCstErrorInd(pMsg);
            break;

        case ID_CST_CALL_SETUP_CNF :
            MN_CALL_ProcCstSetupCnf(pMsg);
            break;

        default:
            MN_WARN_LOG1("MN_CALL_ProcCstCcPrimitive: wrong enMsgID:",  (VOS_INT32)(usMsgType));
            break;
    }
}





/*****************************************************************************
 �� �� ��  : MN_CALL_ProcRabmCallSyncInd
 ��������  : ��������Rabm����ϢRABM_CALL_SYNC_IND��
 �������  : pMsg  - ��Ϣ����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��11��11��
    ��    ��   : h44270
    �޸�����   : ���ⵥ�ţ�DTS2010102202190/DTS2010110600922������ERROR��ӡ
  3.��    ��   : 2012��8��10��
    ��    ��   : L00171473
    �޸�����   : DTS2012082204471, TQE����
  4.��    ��   : 2014��6��11��
    ��    ��   : y00245242
    �޸�����   : DTS2014060306029
*****************************************************************************/
VOS_VOID  MN_CALL_ProcRabmCallSyncInd(
    const VOS_VOID                      *pMsg
)
{
    RABM_CALL_SYNC_IND_STRU             *pstSyncMsg;
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           i;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT8                           ucCallId;
    VOS_BOOL                            bWaitSendAlertStatus;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    pstSyncMsg = (RABM_CALL_SYNC_IND_STRU*)pMsg;

    /*
       ��ָʾrab�����RB���ڣ����ҵ�ǰ�к��У����Һ���������video call
       ��ʱ��ˢ�º���ģ�����ʵ���ж�Ӧrbֵ
       ����VP��CC������sync_ind�ϱ����������alerting�ķ���
    */
    if (RABMCALL_RAB_ACTIVE == pstSyncMsg->ulRabState)
    {
        if (0 != pstSyncMsg->ulRbNum)
        {
            MN_CALL_GetNotIdleStateCalls(&ulNumOfCalls, aCallIds);
            for (i = 0; i < ulNumOfCalls; i++)
            {
                enCallType = MN_CALL_GetCallType(aCallIds[i]);
                if ( MN_CALL_TYPE_VIDEO == enCallType )
                {
                    MN_CALL_UpdateRbId(aCallIds[i], pstSyncMsg->aulRbId[0]);
                    MN_CALL_GetWaitSendAlertStatus(&bWaitSendAlertStatus, &ucCallId);
                    if ((MN_CALL_DIR_MT == MN_CALL_GetCcCallDir(aCallIds[i]))
                      &&(VOS_TRUE == bWaitSendAlertStatus)
                      &&(aCallIds[i] == ucCallId))
                    {
                        (VOS_VOID)MN_CALL_SendCcAlertReq(aCallIds[i]);
                        MN_CALL_SetWaitSendAlertStatus(VOS_FALSE, ucCallId);

                        MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_INCOMING);

                        MN_CALL_StartTimer(MN_CALL_TID_RING, 0, 0, VOS_RELTIMER_NOLOOP);
                    }

                    return;
                }
            }
        }
    }
}


/*****************************************************************************
 �� �� ��  : MN_CALL_ProcRabmCallPrimitive
 ��������  : ��������Rabm����Ϣ��
 �������  : pMsg  - ��Ϣ����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��19��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_CALL_ProcRabmCallPrimitive(
    const VOS_VOID                      *pMsg
)
{
    MSG_HEADER_STRU                     *pstTmpMsg;

    pstTmpMsg = (MSG_HEADER_STRU*)pMsg;

    switch ( pstTmpMsg->ulMsgName)
    {
        case RABM_CALL_SYNC_IND:
            MN_CALL_ProcRabmCallSyncInd(pMsg);
            break;

        default:
            /*�쳣��ӡ*/
            MN_WARN_LOG1( "MN_CALL_ProcRabmCallPrimitive: wrong MsgName:",
                          (VOS_INT32)(pstTmpMsg->ulMsgName));
            break;
    }

}

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */


/* MN_CALL_ProcUsimFdnInd */

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-26, begin */
/*****************************************************************************
 �� �� ��  : TAF_CALL_ProcTafMsg
 ��������  : ��������TAF�ڲ������CALL������Ϣ
 �������  : pMsg  - ��Ϣ����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��26��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_CALL_ProcTafMsg (
    const VOS_VOID                      *pMsg
)
{
    MSG_HEADER_STRU                     *pstTmpMsg = VOS_NULL_PTR;

    pstTmpMsg = (MSG_HEADER_STRU*)pMsg;

    switch (pstTmpMsg->ulMsgName)
    {
        case TAF_CALL_TAF_REL_CALL_REQ:
#if (FEATURE_ON == FEATURE_ECALL)
            TAF_CALL_RcvTafRelCallReq((TAF_CALL_TAF_REL_CALL_REQ_STRU *)pMsg);
#endif
            break;

        default:
            TAF_CSCALL_ProcAppReqMsg((struct MsgCB *)pMsg);
            break;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_CALL_ProcMmaMsg
 ��������  : ��������MMA����Ϣ
 �������  : pMsg  - ��Ϣ����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��4��26��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_CALL_ProcMmaMsg (
    const VOS_VOID                      *pMsg
)
{
    MSG_HEADER_STRU                    *pstTmpMsg = VOS_NULL_PTR;

    pstTmpMsg = (MSG_HEADER_STRU*)pMsg;

    switch (pstTmpMsg->ulMsgName)
    {
        case MMA_TAF_POWER_OFF_IND:
            TAF_CALL_RcvMmaPowerOffInd((TAF_MMA_POWER_OFF_IND_STRU *)pMsg);
            break;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case ID_MMA_TAF_SYS_CFG_INFO_IND:
            TAF_CALL_RcvMmaSyscfgInfoInd((MMA_TAF_SYS_CFG_INFO_IND_STRU *)pMsg);
            break;
#endif
        default:
            break;
    }

}

/* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-26, end */

/*****************************************************************************
 �� �� ��  : MN_CALL_DispatchUsimMsg
 ��������  : �����USIM��������Ϣ
 �������  : pstMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��23��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��09��20��
    ��    ��   : f62575
    �޸�����   : STK&DCM ��Ŀ
  3.��    ��   : 2013��6��5��
    ��    ��   : z00161729
    �޸�����   : SVLTE ��usim�ӿڵ����޸�
  4.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK���� Deleted PS_USIM_ENVELOPE_CNF
*****************************************************************************/
VOS_VOID MN_CALL_DispatchUsimMsg(struct MsgCB * pstMsg)
{

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */
    /* Ԥ������ʹ�� */
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */

    return;
}




/*****************************************************************************
 �� �� ��  : MN_CALL_SupportMoCallType
 ��������  : ��ȡUE��ָ���������͵�֧��״̬
 �������  : MN_CALL_TYPE_ENUM_U8                enCallType  ��������
 �������  : VOS_BOOL                           *pSupported  UE�Ƿ�֧��ָ���ĺ�������
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��20��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALL_SupportMoCallType(
    MN_CALL_TYPE_ENUM_U8                enCallType,
    VOS_BOOL                           *pSupported
)
{
    if ((MN_CALL_TYPE_VOICE == enCallType)
     || (MN_CALL_TYPE_EMERGENCY == enCallType))
    {
        *pSupported = VOS_TRUE;
    }
    else
    {
        *pSupported = VOS_FALSE;
    }
}


/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-14, end */

/*****************************************************************************
 �� �� ��  : MN_CALL_ReportErrCauseInd
 ��������  : CS��ԭ��ֵ�ϱ�
 �������  :
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��09��18��
    ��    ��   : y00213812
    �޸�����   : STK&DCM ��Ŀ��������

*****************************************************************************/


#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 �� �� ��  : MN_CALL_CsCallErrRecord
 ��������  : ��¼CS�����쳣�¼�
 �������  : MN_CALL_ID_T                        ucCallId,
             TAF_CS_CAUSE_ENUM_UINT32            enCause
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��23��
    ��    ��   : s00190137
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_CALL_CsCallErrRecord(
    MN_CALL_ID_T                        ucCallId,
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    NAS_ERR_LOG_CS_CALL_FAIL_EVENT_STRU                     stCsCallFailEvent;
    MN_CALL_INFO_STRU                                       stCallInfo;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;
    NAS_ERR_LOG_IMS_CALL_FAIL_INFO_STRU                     stImsCallFailInfo;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_CS_CALL_FAIL);
    ulIsLogRecord = TAF_SDC_IsErrLogNeedRecord(usLevel);

    PS_MEM_SET(&stImsCallFailInfo, 0, sizeof(NAS_ERR_LOG_IMS_CALL_FAIL_INFO_STRU));

    /* IMS����ʧ�ܣ���CS���ز���callidһ����1 */
    if (1 == ucCallId)
    {
        stImsCallFailInfo.ucImsCallFailFlag = TAF_SDC_GetErrLogImsCallFailFlag();
        stImsCallFailInfo.ulImsCallFailCause = TAF_SDC_GetErrLogImsCallFailCause();

        TAF_SDC_InitErrLogImsCallFailInfo();
    }

    /* ����Ҫ��¼��û���쳣ʱ���������쳣��Ϣ */
    if ((VOS_FALSE == ulIsLogRecord)
     || (TAF_CS_CAUSE_SUCCESS == enCause)
     || (TAF_CS_CAUSE_CC_NW_NORMAL_CALL_CLEARING == enCause))
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_CS_CALL_FAIL_EVENT_STRU);

    /* ���Cs����ʧ���쳣��Ϣ */
    PS_MEM_SET(&stCsCallFailEvent, 0x00, ulLength);
    PS_MEM_SET(&stCallInfo, 0x00, sizeof(stCallInfo));

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stCsCallFailEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_TAF),
                                      NAS_ERR_LOG_ALM_CS_CALL_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stCsCallFailEvent.ulCcCause = enCause;

    if (0 == ucCallId)
    {
        /* ucCallIdΪ0˵��Ϊ�����쳣���޷���ȫ�ֱ����л�ȡ��Ϣ */
        stCsCallFailEvent.ucCallId            = ucCallId;
        stCsCallFailEvent.enCallState         = NAS_ERR_LOG_CALL_S_IDLE;
        stCsCallFailEvent.stDiscDir.ucIsUser  = VOS_TRUE;
    }
    else
    {
        MN_CALL_GetCallInfoByCallId(ucCallId, &stCallInfo);

        stCsCallFailEvent.ucCallId    = stCallInfo.callId;
        stCsCallFailEvent.enCallState = stCallInfo.enCallState;
        PS_MEM_CPY(&stCsCallFailEvent.stDiscDir, &stCallInfo.stDiscDir, sizeof(NAS_ERR_LOG_MN_CALL_DISC_DIR_STRU) );
    }

    stCsCallFailEvent.enRat = TAF_SDC_GetSysMode();

    /* ��ȡ��ǰλ����Ϣ */
    NAS_MNTN_OutputPositionInfo(&stCsCallFailEvent.stPositionInfo);

    /* ��ȡ��ǰUsim��Ϣ */
    NAS_MMA_OutputUsimInfo(&stCsCallFailEvent.stUsimInfo);

    stCsCallFailEvent.usCellDlFreq = TAF_SDC_GetAppCellDlFreq();
    stCsCallFailEvent.usCellUlFreq = TAF_SDC_GetAppCellUlFreq();

    PS_MEM_CPY(&stCsCallFailEvent.stImsCallFailInfo, &stImsCallFailInfo, sizeof(NAS_ERR_LOG_IMS_CALL_FAIL_INFO_STRU));

    /* �����ǰΪ���У��Ҳ���active״̬���������ϱ����ϲ�ô��쳣 */
    if ((MN_CALL_S_INCOMING       == stCallInfo.enCallState)
     || (MN_CALL_S_WAITING        == stCallInfo.enCallState)
     || (MN_CALL_S_WAITING_ACCEPT == stCallInfo.enCallState))
    {
        TAF_SndAcpuOmFaultErrLogInd(&stCsCallFailEvent, ulLength, NAS_ERR_LOG_ALM_CS_CALL_FAIL);
    }

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = TAF_SDC_PutErrLogRingBuf((VOS_CHAR *)&stCsCallFailEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_CsCallErrRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_CS_CALL_FAIL,
                           WUEPS_PID_TAF,
                           (VOS_UINT8 *)&stCsCallFailEvent,
                           sizeof(stCsCallFailEvent));
    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_CsMtCallFailRecord
 ��������  : ��¼CS MT CALL FAIL�쳣�¼�
 �������  : enCause
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2014��09��22��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��07��06��
   ��    ��   : n00269697
   �޸�����   : ERR LOG�ϱ����ͷ�Ϊ�����ϱ��͸澯�ϱ�
*****************************************************************************/
VOS_VOID MN_CALL_CsMtCallFailRecord(
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_ENUM_U32   enCause
)
{
    NAS_ERR_LOG_CS_MT_CALL_FAIL_EVENT_STRU  stCsMtCallFailEvt;
    VOS_UINT32                              ulLength;
    VOS_UINT16                              usLevel;
    VOS_UINT32                              ulIsLogRecord;
    VOS_UINT32                              ulResult;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_CS_MT_CALL_FAIL);
    ulIsLogRecord = TAF_SDC_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_CS_MT_CALL_FAIL_EVENT_STRU);

    /* ���CS PAGINGʧ���쳣��Ϣ */
    PS_MEM_SET(&stCsMtCallFailEvt, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stCsMtCallFailEvt.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_TAF),
                                      NAS_ERR_LOG_ALM_CS_MT_CALL_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* ��ȡ��ǰλ����Ϣ */
    NAS_MNTN_OutputPositionInfo(&stCsMtCallFailEvt.stPositionInfo);

    /* ��д����ԭ��ֵ */
    stCsMtCallFailEvt.enCause = enCause;

    /* ��CS MT CALLʧ����Ϣ���͸�ACPU OMģ�� */
    TAF_SndAcpuOmFaultErrLogInd(&stCsMtCallFailEvt, ulLength, NAS_ERR_LOG_ALM_CS_MT_CALL_FAIL);

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = TAF_SDC_PutErrLogRingBuf((VOS_CHAR *)&stCsMtCallFailEvt, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_SndAcpuOmCsMtCallFailInd(): Push buffer error.");
    }

    /* ��ά�ɲ⹴�� */
    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_CS_MT_CALL_FAIL,
                           WUEPS_PID_TAF,
                           (VOS_UINT8 *)&stCsMtCallFailEvt,
                           sizeof(stCsMtCallFailEvt));

    return;
}

/*****************************************************************************
 �� �� ��  : MN_CALL_CsCallDiscInfoRecord
 ��������  : ��¼NAS_ERR_LOG_ALM_PORCESS_INFO_IND�쳣�¼�
 �������  : ucCallId
             enCause
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��09��18��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_CALL_CsCallDiscInfoRecord(
    MN_CALL_ID_T                            ucCallId,
    NAS_ERR_LOG_CS_MT_CALL_CAUSE_ENUM_U32   enCause
)
{
    NAS_ERR_LOG_PROCESS_INFO_IND_EVENT_STRU stProcInfoEvent;
    VOS_UINT32                              ulLength;
    VOS_UINT16                              usLevel;
    VOS_UINT32                              ulIsLogRecord;
    VOS_UINT32                              ulResult;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_PORCESS_INFO_IND);
    ulIsLogRecord = TAF_SDC_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_PROCESS_INFO_IND_EVENT_STRU);

    /* ��������Ϣ */
    PS_MEM_SET(&stProcInfoEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stProcInfoEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_TAF),
                                      NAS_ERR_LOG_ALM_PORCESS_INFO_IND,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stProcInfoEvent.enInfoType          = NAS_ERR_LOG_PROCESS_INFO_TYPE_CS_CALL_DISC;
    stProcInfoEvent.stDiscInfo.ucCallId = ucCallId;
    stProcInfoEvent.stDiscInfo.ulCause  = enCause;

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = TAF_SDC_PutErrLogRingBuf((VOS_CHAR *)&stProcInfoEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_CsCallDiscInfoRecord(): Push buffer error.");
    }

    /* ��ά�ɲ⹴�� */
    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_PORCESS_INFO_IND,
                           WUEPS_PID_TAF,
                           (VOS_UINT8 *)&stProcInfoEvent,
                           sizeof(stProcInfoEvent));

    return;
}

#endif
/*lint -restore */


/*****************************************************************************
�� �� ��  : TAF_CALL_GetTTYMode
��������  : ��ȡ��ǰTTY MODE
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2015��02��07��
    ��    ��   : w00316404
    �޸�����   : ��������
*****************************************************************************/
TAF_VC_TTYMODE_ENUM_UINT8 TAF_CALL_GetTTYMode(VOS_VOID)
{
    TAF_NV_TTY_CFG_STRU                 stTTYCfgStru;

    /* ������ʼ�� */
    PS_MEM_SET(&stTTYCfgStru, 0x00, sizeof(TAF_NV_TTY_CFG_STRU));

    /* ��ȡNV�� */
    if (NV_OK != NV_Read(en_NV_Item_TTY_Mode,
                         &stTTYCfgStru,
                         sizeof(TAF_NV_TTY_CFG_STRU)))
    {
        return TAF_VC_TTYMODE_BUTT;
    }

    if ( stTTYCfgStru.ucTTYMode >= TAF_VC_TTYMODE_BUTT )
    {
        return TAF_VC_TTYMODE_BUTT;
    }

    return (TAF_VC_TTYMODE_ENUM_UINT8)stTTYCfgStru.ucTTYMode;
}

/*****************************************************************************
�� �� ��  : TAF_CALL_IsSupportTTYMode
��������  : �ж��Ƿ�֧��TTYģʽ
�������  : ��
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :
�޶���¼  :
1.  ��    ��   : 2015��02��07��
    ��    ��   : l00198894
    �޸�����   : ��������
*****************************************************************************/
VOS_BOOL TAF_CALL_IsSupportTTYMode(VOID)
{
    TAF_VC_TTYMODE_ENUM_UINT8           enTTYMode;

    enTTYMode = TAF_CALL_GetTTYMode();

    if (TAF_VC_TTY_OFF == enTTYMode || TAF_VC_TTYMODE_BUTT <= enTTYMode)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
