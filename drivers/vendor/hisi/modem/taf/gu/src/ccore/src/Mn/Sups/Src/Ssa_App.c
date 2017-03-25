/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SSA_Decode.c
  Author       : ---
  Version      : V200R001
  Date         : 2008-08-16
  Description  : ��C�ļ�������SSAģ���ڴ�������APP�Ĳ����ĺ���ʵ��
  Function List:
        ---
        ---
        ---
  History      :
  1. Date:2005-08-16
     Author: ---
     Modification:Create
  2. Date:2006-04-11
     Author: h44270
     Modification: ���ⵥ��:A32D02911, A32D03003
  3. Date:2006-04-13
     Author: h44270
     Modification: ���ⵥ��:A32D02881

  4.��    ��   : 2006��4��4��
    ��    ��   : liuyang id:48197
    �޸�����   : ���ⵥ��:A32D01738
  5. Date:2006-06-08
     Author: h44270
     Modification: ���ⵥ��:A32D04190
  6.��    ��   : 2006��10��8��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ��:A32D06583��SSA��ʱ�����Ƶ�SS
  7.��    ��   : 2006��10��28��
    ��    ��   : h44270
    �޸�����   : ���ⵥ��:A32D06864������*00*012345678#�ִ���������
  8.��    ��   : 2006��12��09��
    ��    ��   : h44270
    �޸�����   : ���ⵥ��:A32D07867������һ���ӿڣ������ж��ִ��Ĳ�������
  9.Date:2007-01-19
    Author: h44270
    Modification: ���ⵥ��:A32D08448
 10.��    ��   : 2007��6��28��
    ��    ��   : h44270
    �޸�����   : modified for A32D11949

 11.��    ��   : 2010��3��2��
    ��    ��   : zhoujun /z40661
    �޸�����   : NAS R7Э������
************************************************************************/

#include "Ssa_Define.h"
#include "Taf_Tafm_Remote.h"
#include "Taf_Common.h"
#include "Taf_Ssa_EncodeDef.h"
#include "UsimPsInterface.h"
#include "SsInclude.h"
/* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, begin */
#include "TafClientApi.h"
/* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, end */
#include "MnComm.h"
#include "MnErrorCode.h"
#include "Taf_Ssa_DecodeDef.h"
#include "siapppb.h"
#include "TafSdcCtx.h"

#include "Ssa_Define.h"

#include "TafInterface.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_SSA_APP_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

extern TAF_UINT32 MMA_GetUsimStatusFromUsim(TAF_UINT8 *pucCardStatus,
                                         TAF_UINT8 *pucCardType);
/*******************GLOBAL DEFINE BEGIN****************************************/


/* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
TAF_SSA_SERV_REQ_PROC_FUNC_MAP_STRU     g_astTafSsaServProcFuncMap[] =
{
    { TAF_MSG_REGISTERSS_MSG,     {0, 0}, SSA_RegisterSSReq},
    { TAF_MSG_ERASESS_MSG ,       {0, 0}, SSA_EraseSSReq },
    { TAF_MSG_ACTIVATESS_MSG ,    {0, 0}, SSA_ActivateSSReq },
    { TAF_MSG_DEACTIVATESS_MSG ,  {0, 0}, SSA_DeactivateSSReq },
    { TAF_MSG_INTERROGATESS_MSG , {0, 0}, SSA_InterrogateSSReq },
    { TAF_MSG_REGPWD_MSG ,        {0, 0}, SSA_RegisterPasswordReq },
    { TAF_MSG_PROCESS_USS_MSG ,   {0, 0}, TAF_SSA_ProcUssdUnstructuredMsg },
    { TAF_MSG_ERASECCENTRY_MSG ,  {0, 0}, SSA_EraseCCEntryReq },
    { TAF_MSG_RLEASE_MSG ,        {0, 0}, SSA_ReleaseComplete }
};
/* Added by f62575 for V9R1 STK����, 2013-6-26, end */

VOS_UINT8  gucMmiBSInfo[SSA_MMI_BS_NUM][3] =
{
{SSA_MMI_BS_ALL_TELESERVICE,            TAF_ALL_TELESERVICES_TSCODE,                    TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_TELEPHONY,                  TAF_ALL_SPEECH_TRANSMISSION_SERVICES_TSCODE,    TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_ALL_DATA_TELESERVICE,       TAF_ALL_DATA_TELESERVICES_TSCODE,               TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_ALL_FACSIMILE_TELESERVICE,  TAF_ALL_FACSIMILE_TRANSMISSION_SERVICES_TSCODE, TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_ALL_SMS_TELESERVICE,        TAF_ALL_SMS_SERVICES_TSCODE,                    TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_ALL_EX_SMS_TELESERVICE,     TAF_ALL_TELESERVICES_EXEPTSMS_TSCODE,           TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_ALL_VGCS_TELESERVICE,       TAF_VOICE_GROUP_CALL_TSCODE,                    TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_ALL_VBS_TELESERVICE,        TAF_VOICE_BROADCAST_CALL_TSCODE,                TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_ALL_BEARER_SERVICES,        TAF_ALL_BEARERSERVICES_BSCODE,                  TAF_SS_BEARER_SERVICE},
{SSA_MMI_BS_ALL_ASYNC_SERVICES,         TAF_ALL_ASYNCHRONOUS_SERVICES_BSCODE,           TAF_SS_BEARER_SERVICE},
{SSA_MMI_BS_ALL_SYNC_SERVICES,          TAF_ALL_SYNCHRONOUS_SERVICES_BSCODE,            TAF_SS_BEARER_SERVICE},
{SSA_MMI_BS_ALL_DATA_CIRCUIT_SYNC,      TAF_ALL_DATA_CIRCUIT_SYNCHRONOUS_BSCODE,        TAF_SS_BEARER_SERVICE},
{SSA_MMI_BS_ALL_DATA_CIRCUIT_ASYNC,     TAF_ALL_DATA_CIRCUIT_ASYNCHRONOUS_BSCODE,       TAF_SS_BEARER_SERVICE},
{SSA_MMI_BS_ALL_PLMN_SPECIFICTS_TS,     TAF_ALL_PLMN_SPECIFICTS_TSCODE,                 TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_1_TS,       TAF_PLMN_SPECIFICTS_1_TSCODE,                   TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_2_TS,       TAF_PLMN_SPECIFICTS_2_TSCODE,                   TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_3_TS,       TAF_PLMN_SPECIFICTS_3_TSCODE,                   TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_4_TS,       TAF_PLMN_SPECIFICTS_4_TSCODE,                   TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_5_TS,       TAF_PLMN_SPECIFICTS_5_TSCODE,                   TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_6_TS,       TAF_PLMN_SPECIFICTS_6_TSCODE,                   TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_7_TS,       TAF_PLMN_SPECIFICTS_7_TSCODE,                   TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_8_TS,       TAF_PLMN_SPECIFICTS_8_TSCODE,                   TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_9_TS,       TAF_PLMN_SPECIFICTS_9_TSCODE,                   TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_10_TS,      TAF_PLMN_SPECIFICTS_A_TSCODE,                   TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_11_TS,      TAF_PLMN_SPECIFICTS_B_TSCODE,                   TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_12_TS,      TAF_PLMN_SPECIFICTS_C_TSCODE,                   TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_13_TS,      TAF_PLMN_SPECIFICTS_D_TSCODE,                   TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_14_TS,      TAF_PLMN_SPECIFICTS_E_TSCODE,                   TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_15_TS,      TAF_PLMN_SPECIFICTS_F_TSCODE,                   TAF_SS_TELE_SERVICE},
{SSA_MMI_BS_ALL_PLMN_SPECIFICTS_BS,     TAF_ALL_PLMN_SPECIFICBS_BSCODE,                 TAF_SS_BEARER_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_1_BS,       TAF_PLMN_SPECIFICBS_1_BSCODE,                   TAF_SS_BEARER_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_2_BS,       TAF_PLMN_SPECIFICBS_2_BSCODE,                   TAF_SS_BEARER_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_3_BS,       TAF_PLMN_SPECIFICBS_3_BSCODE,                   TAF_SS_BEARER_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_4_BS,       TAF_PLMN_SPECIFICBS_4_BSCODE,                   TAF_SS_BEARER_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_5_BS,       TAF_PLMN_SPECIFICBS_5_BSCODE,                   TAF_SS_BEARER_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_6_BS,       TAF_PLMN_SPECIFICBS_6_BSCODE,                   TAF_SS_BEARER_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_7_BS,       TAF_PLMN_SPECIFICBS_7_BSCODE,                   TAF_SS_BEARER_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_8_BS,       TAF_PLMN_SPECIFICBS_8_BSCODE,                   TAF_SS_BEARER_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_9_BS,       TAF_PLMN_SPECIFICBS_9_BSCODE,                   TAF_SS_BEARER_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_10_BS,      TAF_PLMN_SPECIFICBS_A_BSCODE,                   TAF_SS_BEARER_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_11_BS,      TAF_PLMN_SPECIFICBS_B_BSCODE,                   TAF_SS_BEARER_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_12_BS,      TAF_PLMN_SPECIFICBS_C_BSCODE,                   TAF_SS_BEARER_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_13_BS,      TAF_PLMN_SPECIFICBS_D_BSCODE,                   TAF_SS_BEARER_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_14_BS,      TAF_PLMN_SPECIFICBS_E_BSCODE,                   TAF_SS_BEARER_SERVICE},
{SSA_MMI_BS_PLMN_SPECIFICTS_15_BS,      TAF_PLMN_SPECIFICBS_F_BSCODE,                   TAF_SS_BEARER_SERVICE}
};

/*******************GLOBAL DEFINE END****************************************/

/* Deleted by f62575 for V9R1 STK����, 2013-6-26, begin */
/* Deleted TAF_SSA_ConvertStkMsgType */
/* Deleted by f62575 for V9R1 STK����, 2013-6-26, end */

/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : TAF_SSA_ProcUssdMode
 ��������  : ��������USSD����ģʽ
 �������  : USSD_TRANS_MODE_STRU                *pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��05��08��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���DTS2012050801468: ֧��^USSDMODE��������ͬ����C��
  2.��    ��   : 2013��05��22��
    ��    ��   : w00176964
    �޸�����   : SS FDN&Call Control��Ŀ:����SDC�е�USSD��ģʽ
*****************************************************************************/
VOS_VOID TAF_SSA_ProcUssdMode(
    USSD_TRANS_MODE_STRU                *pstMsg
)
{
    g_usTafSsaUssdTransMode = pstMsg->ucUssdTransMode;

    TAF_SDC_SetUssdTransMode(pstMsg->ucUssdTransMode);

    return;
}

/*****************************************************************************
 Prototype      : Taf_SsaProc
 Description    : TAFM������Ϣ���ͣ�����Ssҵ�񣬽���TAFM���Ľ��룬����TAF_CallIndependentOp
 Input          : ucMsgType - SS��Ϣ����
                  ClientId  - APP/AT�ͻ��˱�ʶ
                  CallId    -   ���б�ʶ
                  usIeMask  - ��Ϣ��Ie���ڵı��λ
                  pMsg      -     ���뻺����ָ��
 Output         : ��
 Return Value   : �������
 Calls          : TAF_CallIndependentOp
 Called By      : Taf_AppMsgProc

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.��    ��   : 2007��6��28��
    ��    ��   : h44270
    �޸�����   : modified for A32D11949
  3.��    ��   : 2012��4��25��
    ��    ��   : f62575
    �޸�����   : DTS2012042500352: ���STK�����USSDҵ��֧������
  4.��    ��   : 2012��05��08��
    ��    ��   : f00179208
    �޸�����   : DTS2012050801468: ֧��^USSDMODE��������ͬ����C��
  5.��    ��   : 2012��12��11��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  6.��    ��   : 2013��4��8��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C��
  7.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ��SS�������Ƶ�SSģ��
  8.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  9.��    ��   : 2013��12��30��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ
*****************************************************************************/
VOS_VOID Taf_SsaProc(VOS_UINT16 usMsgType, VOS_UINT16 ClientId,VOS_UINT8 OpId, VOS_UINT8 *pMsg)
{
    /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-30, begin */
    /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-30, end */
    VOS_UINT32                          ulRslt;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulFuncNum;
    TAF_SSA_SERV_REQ_PROC_FUNC          pMsgProcFunc  = VOS_NULL_PTR;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, end */

    /* ���޹ص��������� */
    if (TAF_MSG_SET_USSDMODE_MSG == usMsgType)
    {
        TAF_SSA_ProcUssdMode((USSD_TRANS_MODE_STRU *)pMsg);

        return;
    }

    /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-30, begin */
    /* ��״̬�ж����Ƶ�SPM */
    /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-30, end */

    /* ����ֻ�����Ϣ�ַ��������������̾��޸�Ϊ�ڴ�������ʵ�� */
    /* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
    ulFuncNum = sizeof(g_astTafSsaServProcFuncMap) / sizeof(g_astTafSsaServProcFuncMap[0]);

    for (ulLoop = 0; ulLoop < ulFuncNum; ulLoop ++ )
    {
        if (usMsgType == g_astTafSsaServProcFuncMap[ulLoop].usMsgType)
        {
            pMsgProcFunc = g_astTafSsaServProcFuncMap[ulLoop].pMsgProcFunc;
            break;
        }
    }

    if (VOS_NULL_PTR == pMsgProcFunc)
    {
        SSA_LOG( WARNING_PRINT, "Taf_SsaProc:WARNING: unknown message type");
        SSA_ReportErrorEvent(ClientId, OpId, TAF_ERR_PARA_ERROR);
        return;
    }

    ulRslt = pMsgProcFunc(ClientId, OpId, usMsgType, pMsg);

    if (ulRslt != TAF_ERR_NO_ERROR)
    {
        SSA_ReportErrorEvent(ClientId, OpId, (VOS_UINT16)ulRslt);
    }

    return;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, end */
}

/**********************************************************
 Function:     Taf_SsMsgReq
 Description:  Ssaģ����Ҫ��ss������Ϣʱ���ô˺���
 Calls:        Ssaģ��
 Data Accessed:
 Data Updated:
 Input:        p��������Э��ջ����Ϣ
 Output:
 Return:
 Others:
 2.��    ��   :2013��9��10��
   ��    ��   :z00161729
   �޸�����   :DTS2013082903019:֧��ss�ط�����
 3.��    ��   : 2014?6?17?
   ��    ��   : z00234330
   �޸�����   : coverity����
**********************************************************/
VOS_VOID  Taf_SsMsgReq(ST_SSP_MSG *pMsg)
{
    VOS_UINT8                           ucTi;

    /*����������*/
    if (VOS_NULL_PTR == pMsg)
    {
        TAF_PRINT(TAF_TAFM, ERROR_PRINT, "Taf_SsMsgReq:Input pointer p is null");
        return;
    }

    ucTi = pMsg->ucCr;

    /* �������Ϸ��� */
    if ( ucTi > TAF_MAX_SSA_TI  )
    {
        return;
    }
    if ( (pMsg->ucCr > (TAF_MIDDLE_SSA_TI)) &&
         (pMsg->ucCr <= TAF_MAX_SSA_TI) )
    {   /*Cr��Χ��8-14,ת����128-134*/
        pMsg->ucCr += 120;
    }

    pMsg->ucRedialFlg   = VOS_FALSE;

    /* ֧��ss�ط�������Ҫ����D_SMC_BEGIN_REQ��Ϣ */
    if ((VOS_TRUE == TAF_SSA_GetSsRetrySupportFlg())
     && (D_SMC_BEGIN_REQ == pMsg->SspmsgCore.ucChoice))
    {
        gastSsaStatetable[ucTi].enSsaState = TAF_SSA_STATE_CONN_PENDING;
        gastSsaStatetable[ucTi].stSsaBufferedMsg.bitOpBufferedBeginReqMsg = VOS_TRUE;
        PS_MEM_CPY(&gastSsaStatetable[ucTi].stSsaBufferedMsg.stBufferedBeginReqMsg, pMsg, sizeof(ST_SSP_MSG));
        (VOS_VOID)TAF_SSA_StartTimer(TI_TAF_SSA_RETRY_PERIOD_TIMER,
                          TAF_SSA_GetSsRetryPeriodTimerLen(), ucTi);
    }

    /*����Э��ջ�ӿ�*/
    Ss_RcvSsaMsg(pMsg);
    return;
}



/*lint -e438 -e830*/

/*****************************************************************************
 Prototype      : SSA_MmiGetPwd
 Description    : ���ע��������������ִ����н���
 Input          : *pMMIStr--����Ĵ��������ִ�
 Output         : *pstPara--����Ĳ���
 Return Value   : �������
 Calls          : ---
 Called By      : SSA_DealMsgFromSS

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_UINT32   SSA_MmiGetPwd(SSA_MMI_PARA_STRU *pstPara,  VOS_UINT8  *pMMIStr, VOS_UINT8  ucStrLen)
{
    VOS_UINT8                       *pucTmp;
    VOS_UINT32                      i;

    pucTmp = pMMIStr;

    /*����ͷ���ļ����ֽ�*/
    for (i = 2; i < ucStrLen; i++)
    {
        if (('*' == *((pucTmp + i) - 2)) && ('0' == *((pucTmp + i) - 1)) && ('3' == *(pucTmp + i)))
        {
            break;
        }
    }

    pucTmp = pMMIStr + i + 1;
    ucStrLen = ucStrLen - (VOS_UINT8)i;

    /*�������**��˵��service codeӦ����all service code*/
    if (('*' == *pucTmp)&&('*' == *(pucTmp + 1)))
    {
        pstPara->ucScFlg = SSA_FIELD_EXIST;
        pstPara->ulSc = SSA_MMI_ALL_SS_CODE;
        pucTmp = pucTmp + 2;
    }
    else if ('*' == *pucTmp)
    {
        /*��ȡ��Ӧ��service code*/
        pucTmp++;
        while('*' != *pucTmp)
        {
            if (isdigit(*pucTmp))
            {
                /*lint -e961*/
                pstPara->ulSc = ((pstPara->ulSc * 10) + *(pucTmp++)) - '0';
                /*lint +e961*/
            }
            else
            {
                SSA_LOG( WARNING_PRINT, "SSA_MmiGetPwd:WARNING:Input para error,sc err,not num");
                return TAF_ERR_PARA_ERROR;
            }
        }
        pucTmp++;
    }
    else
    {
        /*�쳣�����ִ�*/
        SSA_LOG( WARNING_PRINT, "SSA_MmiGetPwd:WARNING:Input para error,sc err, not '*'");
        return TAF_ERR_PARA_ERROR;
    }

    /*����������*/
    (VOS_VOID)VOS_MemCpy(pstPara->aucOldPwd, pucTmp, 4);
    pucTmp = pucTmp + 4;

    if ('*' != *pucTmp)
    {
        SSA_LOG( WARNING_PRINT, "SSA_MmiGetPwd:WARNING:Input para error,old pwd err");
        return TAF_ERR_PARA_ERROR;
    }

    pucTmp++;

    /*����������*/
    (VOS_VOID)VOS_MemCpy(pstPara->aucNewPwd, pucTmp, 4);
    pucTmp = pucTmp + 4;

    if ('*' != *pucTmp)
    {
        SSA_LOG( WARNING_PRINT, "SSA_MmiGetPwd:WARNING:Input para error,new pwd err");
        return TAF_ERR_PARA_ERROR;
    }

    pucTmp++;

    /*����ȷ������*/
    (VOS_VOID)VOS_MemCpy(pstPara->aucNewPwdCnf, pucTmp, 4);
    pucTmp = pucTmp + 4;

    /*�жϽ�β�Ƿ�������#*/
    if ('#' != *pucTmp)
    {
        SSA_LOG( WARNING_PRINT, "SSA_MmiGetPwd:WARNING:Input para error,end err");
        return TAF_ERR_PARA_ERROR;
    }

    return SSA_SUCCESS;
}
/*lint +e438 +e830*/


/*****************************************************************************
 Prototype      : SSA_GetMmiPara
 Description    : ���ִ����н�������ȡ��Ӧ�Ĳ���
 Input          : *pMMIStr--�����ִ�            ucStrLen--�����ִ�����
 Output         : *pstPara--�������
 Return Value   : �������
 Calls          : ---
 Called By      : SSA_DealMsgFromSS

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.Date        : 2006-10-28
    Author      : ---
    Modification: modified by h44279 for  A32D06864
*****************************************************************************/
VOS_UINT32   SSA_GetMmiPara(SSA_MMI_PARA_STRU *pstPara,  VOS_UINT8  *pMMIStr, VOS_UINT8  ucStrLen)
{

    VOS_UINT8                       *pucTmp;
    /* VOS_UINT8                        ucOpMode; */
    /* TAF_SS_PROCESS_USS_REQ_STRU      stProcessUssReq; */

    pucTmp = pMMIStr;

    /*����'#'�ַ���β��, ������USSD����*/
    if ('#' != *((pMMIStr + ucStrLen) - 1))
    {
        pstPara->ucOpMode = TAF_SS_PROCESS_USS_REQ;
        return SSA_SUCCESS;
    }

    /*�����ע���µ�����*/
    if ((('*' == *pucTmp) && ('0' == *(pucTmp + 1)) && ('3' == *(pucTmp + 2)))
        ||(('*' == *pucTmp) && ('*' == *(pucTmp + 1)) && ('0' == *(pucTmp + 2)) && ('3' == *(pucTmp + 3))))
    {
        if (SSA_SUCCESS != SSA_MmiGetPwd(pstPara, pMMIStr,ucStrLen))
        {
            SSA_LOG( WARNING_PRINT, "SSA_GetMmiPara:WARNING:Input para error");
            return TAF_ERR_PARA_ERROR;
        }
        pstPara->ucOpMode = TAF_SS_REGISTERPASSWORD;
        pstPara->ucPwdFlg = SSA_FIELD_EXIST;
        return SSA_SUCCESS;
    }

    /*��ȡ���еĲ���,SC,SI*/
    /*lint -e961*/
    while (ucStrLen-- > 0)
    /*lint +e961*/
    {
        /*�ж��Ƿ���'0'~'9'�������ַ�,���ǵĻ�,��Ȼ��'*'����'#'�ı�־��*/
        if (('*' == *pucTmp) || ('#' == *pucTmp))
        {

            /*��ǰ��δ�ҵ�Scʱ,����*/
            if (VOS_FALSE == pstPara->ucScFlg)
            {
                pucTmp++;
                continue;
            }
            /*��ǰ��δ�ҵ�Siaʱ,�������'*'��,�����Ѿ�������Sia�ı�ʶ��*/
            else if ((VOS_FALSE == pstPara->ucSiaFlg) && ('*' == *pucTmp))
            {
                pstPara->ucSiaFlg = 1;
                pucTmp++;
                continue;
            }
            /*��ǰ��δ�ҵ�Sibʱ,�������'*'��,�����Ѿ�������Sia�ı�ʶ��*/
            else if ((VOS_FALSE == pstPara->ucSibFlg) && ('*' == *pucTmp))
            {
                /*��ǰ��'*'֮ǰҲ��һ��'*'��ʱ,����������Sia*/
                if ('*' == *(pucTmp-1))
                {
                    pstPara->ucSiaFlg = 2;
                }
                pstPara->ucSibFlg = 1;
                pucTmp++;
                continue;
            }
            /*��ǰ��δ�ҵ�Sicʱ,�������'*'��,�����Ѿ�������Sic�ı�ʶ��*/
            else if ((VOS_FALSE == pstPara->ucSicFlg) && ('*' == *pucTmp))
            {
                /*��ǰ��'*'֮ǰҲ��һ��'*'��ʱ,����������Sib*/
                if ('*' == *(pucTmp-1))
                {
                    pstPara->ucSibFlg = 2;
                }
                pstPara->ucSicFlg = 1;
                pucTmp++;
                continue;
            }
            /*����'#',�����ִ�����*/
            else if (('#' == *pucTmp)&&(ucStrLen != 0))
            {
                SSA_LOG( WARNING_PRINT, "SSA_GetMmiPara:WARNING:Input para end wrong");
                return SSA_FAILURE;
            }
            else
            {
                ;
            }
            pucTmp ++;
        }
        /*lint -e731*/
        else if ((isdigit(*pucTmp)) || ('+' == *pucTmp))
        /*lint +e731*/
        {
            /*������δ��ȡ��Sc��ֵ*/
            if (VOS_FALSE == pstPara->ucScFlg)
            {
                pstPara->ucScFlg = 1;
            }
            /*��ȡSC��ֵ*/
            if (VOS_FALSE == pstPara->ucSiaFlg)
            {
                pstPara->ulSc = ((pstPara->ulSc * 10) + *(pucTmp)) - '0';
                /* Modified by z00234330 for PCLINT����, 2014-06-24, begin */
                pucTmp++;
                /* Modified by z00234330 for PCLINT����, 2014-06-24, end */
                continue;
            }
            /*��ȡSia��ֵ*/
            if (VOS_FALSE == pstPara->ucSibFlg)
            {
                pstPara->aucSia[pstPara->ucSiaLen] = *pucTmp;
                /* Modified by z00234330 for PCLINT����, 2014-06-24, begin */
                pucTmp++;
                pstPara->ucSiaLen++;
                /* Modified by z00234330 for PCLINT����, 2014-06-24, end */
                continue;
            }
            /*��ȡSib��ֵ*/
            if (VOS_FALSE == pstPara->ucSicFlg)
            {
                pstPara->ucSib = (VOS_UINT8)(((pstPara->ucSib * 10) + *(pucTmp)) - '0');
                /* Modified by z00234330 for PCLINT����, 2014-06-24, begin */
                pucTmp++;
                /* Modified by z00234330 for PCLINT����, 2014-06-24, end */
                continue;
            }

            /*��ȡSic��ֵ*/
            pstPara->ucSic = (VOS_UINT8)(((pstPara->ucSic * 10) + *(pucTmp)) - '0');
            /* Modified by z00234330 for PCLINT����, 2014-06-24, begin */
            pucTmp++;
            /* Modified by z00234330 for PCLINT����, 2014-06-24, end */

            continue;
        }
        else
        {
            SSA_LOG( WARNING_PRINT, "SSA_GetMmiPara:WARNING:Input para error");
            return SSA_FAILURE;
        }
    }

    /*���ulSc��ֵΪ0����Ϊ��USSD����,������Ϊԭ�������������ʱ��,��ֵΪ0�����*/
    if (0 == pstPara->ulSc)
    {
        pstPara->ucOpMode = TAF_SS_PROCESS_USS_REQ;
        return SSA_SUCCESS;
    }

    pucTmp = pMMIStr;

    /*�жϲ�����ʽ*/
    if ((*pucTmp == '*')&&(*(pucTmp+1) == '#')&&(*(pucTmp+2) != '*')&&(*(pucTmp+2) != '#'))
    {
        pstPara->ucOpMode = TAF_SS_INTERROGATESS;
    }
    else if ((*pucTmp == '#')&&(*(pucTmp+1) == '#')&&(*(pucTmp+2) != '*')&&(*(pucTmp+2) != '#'))
    {
        pstPara->ucOpMode = TAF_SS_ERASESS;
    }
    else if ((*pucTmp == '*')&&(*(pucTmp+1) == '*')&&(*(pucTmp+2) != '*')&&(*(pucTmp+2) != '#'))
    {
        pstPara->ucOpMode = TAF_SS_REGISTERSS;
    }
    else if ((*pucTmp == '#')&&(*(pucTmp+1) != '#')&&(*(pucTmp+1) != '*'))
    {
        pstPara->ucOpMode = TAF_SS_DEACTIVATESS;
    }
    else if ((*pucTmp == '*')&&(*(pucTmp+1) != '#')&&(*(pucTmp+1) != '*'))
    {

        pstPara->ucOpMode = TAF_SS_ACTIVATESS;
    }
    else
    {
        pstPara->ucOpMode = TAF_SS_PROCESS_USS_REQ;
        return SSA_SUCCESS;
    }

    return  SSA_SUCCESS;

}


/*****************************************************************************
 Prototype      : SSA_ReturnError
 Description    : ����Return Error���͵�Component,������صı��뺯��,������������
                  ����SS
 Input          : ucErrCode -- ������, ucTi -- Tiֵ
                  ucMsgType -- ��Ϣ����(REGISTER, FACILITY, RELEASE COMPLETE)
 Output         : ��
 Return Value   : ��
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID SSA_ReturnError(VOS_UINT16 usErrCode, VOS_UINT8 ucTi, VOS_UINT8 ucMsgType, VOS_UINT8 ucCause)
{
    ST_SSP_MSG             stSsMsg;

    /*�������ݳ�ʼ��*/
    PS_MEM_SET(&stSsMsg, 0, sizeof(ST_SSP_MSG));

    /*ȷ��Ti����Ϣ����*/
    stSsMsg.ucCr = ucTi;


    /*�����release complete��Ϣ����Ҫȷ��cause�Ƿ���ֵ���еĻ����и�ֵ*/
    if (ucMsgType == TAF_SS_MSG_TYPE_RLCOMPLETE)
    {
        stSsMsg.SspmsgCore.ucChoice = D_SMC_END_REQ;
        if (ucCause == 0)
        {
            stSsMsg.SspmsgCore.u.EndReq.OP_Cause = SSA_FIELD_NOT_EXIST;
        }
        else
        {
            stSsMsg.SspmsgCore.u.EndReq.OP_Cause = SSA_FIELD_EXIST;
            stSsMsg.SspmsgCore.u.EndReq.Cause.Cause[0] = 0xe0;           /*��׼���뷽ʽ*/
            stSsMsg.SspmsgCore.u.EndReq.Cause.Cause[1]= ucCause;
            stSsMsg.SspmsgCore.u.EndReq.Cause.ulCnt = 2;
        }
    }
    else
    {
        stSsMsg.SspmsgCore.ucChoice = D_SMC_FACILITY_REQ;
    }



    /*��װparameter֮���ͷ��*/
    if (ucMsgType == TAF_SS_MSG_TYPE_RLCOMPLETE)
    {
        if (usErrCode != VOS_NULL)
        {
            if (SSA_SUCCESS != SSA_PackMsgHeader(&(stSsMsg.SspmsgCore.u.EndReq.Facility), VOS_NULL,
                                                 ucMsgType, ucTi, usErrCode, VOS_NULL))
            {
                SSA_LOG( WARNING_PRINT, "SSA_ReturnError:WARNING: Encode Msg Header Error");
                return;
            }
            stSsMsg.SspmsgCore.u.EndReq.OP_Facility = 1;
        }
        else if (stSsMsg.SspmsgCore.u.EndReq.OP_Cause == SSA_FIELD_NOT_EXIST)
        {
            SSA_LOG( WARNING_PRINT, "SSA_ReturnError:WARNING: CAUSE Not Exist");

            SSA_TiFree(ucTi);
            return;
        }
        else
        {
            stSsMsg.SspmsgCore.u.EndReq.OP_Facility = 0;
        }

    }
    else
    {
        if (usErrCode == VOS_NULL)
        {
            SSA_LOG( WARNING_PRINT, "SSA_ReturnError:WARNING: Error Code Not Exist");
            return;
        }
        if (SSA_SUCCESS != SSA_PackMsgHeader(&(stSsMsg.SspmsgCore.u.FacilityReq.Facility), VOS_NULL,
                                             ucMsgType, ucTi, usErrCode, VOS_NULL))
        {
            SSA_LOG( WARNING_PRINT, "SSA_ReturnError:WARNING: Encode Msg Header Error");
            return;
        }

    }
    /*��SS������Ϣ*/
    Taf_SsMsgReq(&stSsMsg);

    /*�����release complete��Ϣ���ͷ�Ti*/
    if (ucMsgType == TAF_SS_MSG_TYPE_RLCOMPLETE)
    {
        SSA_TiFree(ucTi);
    }

    return;

}

/*****************************************************************************
 Prototype      : SSA_ReturnReject
 Description    : ����Reject���͵�Component,,������صı��뺯��,������������
                  ����SS
 Input          : ucErrCode -- ������, ucTi -- Tiֵ
                  ucMsgType -- ��Ϣ����(REGISTER, FACILITY, RELEASE COMPLETE)
 Output         : ��
 Return Value   : ��
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID SSA_ReturnReject(VOS_UINT8 ucRejCode, VOS_UINT8 ucTi, VOS_UINT8 ucMsgType, VOS_UINT8 ucCause)
{
    ST_SSP_MSG             stSsMsg;

    /*�������ݳ�ʼ��*/
    PS_MEM_SET(&stSsMsg, 0, sizeof(ST_SSP_MSG));

    /*ȷ��Ti����Ϣ����*/
    stSsMsg.ucCr = ucTi;

    /*�����release complete��Ϣ����Ҫȷ��cause�Ƿ���ֵ���еĻ����и�ֵ*/
    if (ucMsgType == TAF_SS_MSG_TYPE_RLCOMPLETE)
    {
        stSsMsg.SspmsgCore.ucChoice = D_SMC_END_REQ;
        if (ucCause == 0)
        {
            stSsMsg.SspmsgCore.u.EndReq.OP_Cause = SSA_FIELD_NOT_EXIST;
        }
        else
        {
            stSsMsg.SspmsgCore.u.EndReq.OP_Cause = SSA_FIELD_EXIST;
            stSsMsg.SspmsgCore.u.EndReq.Cause.Cause[0] = 0x60;           /*��׼���뷽ʽ*/
            stSsMsg.SspmsgCore.u.EndReq.Cause.Cause[1]= ucCause;
            stSsMsg.SspmsgCore.u.EndReq.Cause.ulCnt = 2;
        }
    }
    else
    {
        stSsMsg.SspmsgCore.ucChoice = D_SMC_FACILITY_REQ;
    }

    /*��װparameter֮���ͷ��*/
    if (ucMsgType == TAF_SS_MSG_TYPE_RLCOMPLETE)
    {
        if (ucRejCode != VOS_NULL)
        {
            if (SSA_SUCCESS != SSA_PackMsgHeader(&(stSsMsg.SspmsgCore.u.EndReq.Facility), VOS_NULL,
                                                 ucMsgType, ucTi, VOS_NULL, ucRejCode))
            {
                SSA_LOG( WARNING_PRINT, "SSA_ReturnReject:WARNING: Encode Msg Header Error");
                return;
            }
            stSsMsg.SspmsgCore.u.EndReq.OP_Facility = 1;
        }
        else if (stSsMsg.SspmsgCore.u.EndReq.OP_Cause == SSA_FIELD_NOT_EXIST)
        {
            SSA_LOG( WARNING_PRINT, "SSA_ReturnReject:WARNING: CAUSE Not Exist");
            SSA_TiFree(ucTi);
            return;
        }
        else
        {
            stSsMsg.SspmsgCore.u.EndReq.OP_Facility = 0;
        }
    }
    else
    {
        if (ucRejCode == VOS_NULL)
        {
            SSA_LOG( WARNING_PRINT, "SSA_ReturnReject:WARNING: Error Code Not Exist");
            return;
        }
        if (SSA_SUCCESS != SSA_PackMsgHeader(&(stSsMsg.SspmsgCore.u.FacilityReq.Facility), VOS_NULL,
                                             ucMsgType, ucTi, VOS_NULL, ucRejCode))
        {
            SSA_LOG( WARNING_PRINT, "SSA_ReturnReject:WARNING: Encode Msg Header Error");
            return;
        }
    }

    /*��SS������Ϣ*/
    Taf_SsMsgReq(&stSsMsg);

    /*�����release complete��Ϣ���ͷ�Ti*/
    if (ucMsgType == TAF_SS_MSG_TYPE_RLCOMPLETE)
    {
        SSA_TiFree(ucTi);
    }

    return;
}

/*****************************************************************************
 Prototype      : SSA_RegisterSSReq
 Description    : ����APP/AT�����RegisterSS����,���б��룬�������������ݷ���SS
 Input          : *para -- RegisterSS�����Ĳ���,������صı��뺯��
                  ucTi -- �����Ti
 Output         : ��
 Return Value   : �������
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.��    ��   : 2006��10��8��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ��:A32D06583��SSA��ʱ�����Ƶ�SS
 3.��    ��   : 2012��4��28��
   ��    ��   : f62575
   �޸�����   : DTS2012042601441,+CUSD=2��ʱ��δ�������
  4.��    ��   : 2013��5��6��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C��
  5.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  6.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
*****************************************************************************/
VOS_UINT32 SSA_RegisterSSReq(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                           *pMsg
)
{
    ST_SSP_MSG                          stRegisterMsg;
    VOS_UINT32                          ulRslt;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
    VOS_UINT8                           ucTi;
    TAF_SS_REGISTERSS_REQ_STRU         *pstRegisterSsReqInfo = VOS_NULL_PTR;

    /* ����USSDҵ�����������������SSҵ�� */
    if (VOS_TRUE != TAF_SSA_IsUssdStateIdle())
    {
        return TAF_ERR_BUSY_ON_USSD;
    }

    /*��ȡ����ʹ�õ�Ti*/
    if (SSA_SUCCESS != SSA_TiAlloc(ClientId, OpId, &ucTi))
    {
        SSA_LOG( WARNING_PRINT, "SSA_RegisterSSReq: RegisterSS Ti alloc fail");
        return TAF_ERR_TI_ALLOC_FAIL;
    }

    pstRegisterSsReqInfo = (TAF_SS_REGISTERSS_REQ_STRU *)pMsg;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, end */

    /*�������ݳ�ʼ��*/
    PS_MEM_SET(&stRegisterMsg, 0, sizeof(ST_SSP_MSG));

    /*ȷ��Ti����Ϣ����*/
    stRegisterMsg.ucCr                = ucTi;
    stRegisterMsg.SspmsgCore.ucChoice = D_SMC_BEGIN_REQ;

    /*��MS�෢��ķ����RegisterSS�����Ĳ������ݽ��б���*/
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    ulRslt = SSA_EncodeRegisterSSReq(stRegisterMsg.SspmsgCore.u.BeginReq.Facility.Facility,
                                     (VOS_UINT8*)&(stRegisterMsg.SspmsgCore.u.BeginReq.Facility.ulCnt),
                                     (TAF_SS_REGISTERSS_REQ_STRU *)pstRegisterSsReqInfo);
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG( WARNING_PRINT, "SSA_RegisterSSReq:WARNING: Encode RegisterSSReq Error!");
        SSA_TiFree(ucTi);
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        /* ͳһ�����룬����ʧ�ܰ����������� */
        return TAF_ERR_PARA_ERROR;
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    }

    /*��װpstRegisterSsReqInfometer֮���ͷ��*/
    if (SSA_SUCCESS != SSA_PackMsgHeader(&(stRegisterMsg.SspmsgCore.u.BeginReq.Facility),TAF_SS_REGISTERSS,
                                         TAF_SS_MSG_TYPE_REGISTER, ucTi, VOS_NULL, VOS_NULL))
    {
        SSA_LOG( WARNING_PRINT, "SSA_RegisterSSReq:WARNING: Encode MsgHeader Error!");
        SSA_TiFree(ucTi);
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        /* ͳһ�����룬�滻SSA_FAILUREΪTAF_ERR_ERROR */
        return TAF_ERR_ERROR;
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    }

    /*�Ƿ�����SS version indicator,Ŀǰ��1*/
    stRegisterMsg.SspmsgCore.u.BeginReq.OP_Sspversion = 1;
    stRegisterMsg.SspmsgCore.u.BeginReq.Sspversion.ulCnt = 1;
    stRegisterMsg.SspmsgCore.u.BeginReq.Sspversion.Sspversion[0] = 0;

    /*������ʱ�����ȴ������Ļظ�*/
    if (VOS_TRUE !=  TAF_SSA_StartTimer(TI_TAF_SSA_WAIT_NETWORK_RSP_TIMER,
                                        NAS_SSA_TIMER_LENGTH_WAIT_NETWORK_RSP,
                                        ucTi))
    {
        SSA_LOG( ERROR_PRINT, "SSA_RegisterSSReq:ERROR: VOS_StartRelTimer runs failed");
        SSA_TiFree(ucTi);
        return TAF_ERR_ERROR;
    }

    /*��SS������Ϣ*/
    Taf_SsMsgReq(&stRegisterMsg);

    /*��״̬���м��뵱ǰTi�������Ϣ*/
    gastSsaStatetable[ucTi].ucOperationCode = TAF_SS_REGISTERSS;
    gastSsaStatetable[ucTi].ucSsCode = pstRegisterSsReqInfo->SsCode;
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, begin */
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, end */
    gastSsaStatetable[ucTi].ucState = SSA_USED;
    gastSsaStatetable[ucTi].ucMsgType = TAF_SS_MSG_TYPE_REGISTER;

    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    /* ͳһ�����룬�滻SSA_SUCCESSΪTAF_ERR_NO_ERROR */
    return TAF_ERR_NO_ERROR;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
}


/*****************************************************************************
 Prototype      : SSA_EraseSSReq
 Description    : ����APP/AT�����EraseSS����,�������������ݷ���SS
 Input          : *para--EraseSS�����Ĳ���,������صı��뺯��
                  ucTi -- �����Ti
 Output         : ��
 Return Value   : �������
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.��    ��   : 2006��10��8��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ��:A32D06583��SSA��ʱ�����Ƶ�SS
  3.��    ��   : 2012��4��28��
    ��    ��   : f62575
    �޸�����   : DTS2012042601441,+CUSD=2��ʱ��δ�������
  4.��    ��   : 2013��5��6��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C��
  5.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  6.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����  :DTS2013082903019:֧��ss�ط�����
*****************************************************************************/
VOS_UINT32 SSA_EraseSSReq(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                           *pMsg
)
{
    ST_SSP_MSG                          stRegisterMsg;
    VOS_UINT32                          ulRslt;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
    VOS_UINT8                           ucTi;
    TAF_SS_ERASESS_REQ_STRU            *pstEraseSSReqInfo = VOS_NULL_PTR;

    /* ����USSDҵ�����������������SSҵ�� */
    if (VOS_TRUE != TAF_SSA_IsUssdStateIdle())
    {
        return TAF_ERR_BUSY_ON_USSD;
    }

    /*��ȡ����ʹ�õ�Ti*/
    if (SSA_SUCCESS != SSA_TiAlloc(ClientId, OpId, &ucTi))
    {
        SSA_LOG( WARNING_PRINT, "SSA_EraseSSReq: EraseSS Ti alloc fail");
        return TAF_ERR_TI_ALLOC_FAIL;
    }

    pstEraseSSReqInfo =  (TAF_SS_ERASESS_REQ_STRU *)pMsg;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, end */

    /*�������ݳ�ʼ��*/
    PS_MEM_SET(&stRegisterMsg, 0, sizeof(ST_SSP_MSG));

    /*ȷ��Ti����Ϣ����*/
    stRegisterMsg.ucCr = ucTi;
    stRegisterMsg.SspmsgCore.ucChoice = D_SMC_BEGIN_REQ;

    /*��MS�෢��ķ����RegisterSS�����Ĳ������ݽ��б���*/
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    ulRslt = SSA_EncodeEraseSSReq(stRegisterMsg.SspmsgCore.u.BeginReq.Facility.Facility,
                                  (VOS_UINT8*)&(stRegisterMsg.SspmsgCore.u.BeginReq.Facility.ulCnt),
                                  (TAF_SS_ERASESS_REQ_STRU *)pMsg);
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG( WARNING_PRINT, "SSA_EraseSSReq:WARNING: Encode EraseSSReq Error!");
        SSA_TiFree(ucTi);
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        /* ͳһ�����룬����ʧ�ܰ����������� */
        return TAF_ERR_PARA_ERROR;
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    }

    /*��װparameter֮���ͷ��*/
    if (SSA_SUCCESS != SSA_PackMsgHeader(&(stRegisterMsg.SspmsgCore.u.BeginReq.Facility), TAF_SS_ERASESS,
                                        TAF_SS_MSG_TYPE_REGISTER, ucTi, VOS_NULL, VOS_NULL))
    {
        SSA_LOG( WARNING_PRINT, "SSA_EraseSSReq:WARNING: Encode MsgHeader Error!");
        SSA_TiFree(ucTi);
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        /* ͳһ�����룬�滻SSA_FAILUREΪTAF_ERR_ERROR */
        return TAF_ERR_ERROR;
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    }

    /*�Ƿ�����SS version indicator,Ŀǰ��ʱ����*/
    stRegisterMsg.SspmsgCore.u.BeginReq.OP_Sspversion = 1;
    stRegisterMsg.SspmsgCore.u.BeginReq.Sspversion.ulCnt = 1;
    stRegisterMsg.SspmsgCore.u.BeginReq.Sspversion.Sspversion[0] = 0;

    /*������ʱ�����ȴ������Ļظ�*/
    if (VOS_TRUE !=  TAF_SSA_StartTimer(TI_TAF_SSA_WAIT_NETWORK_RSP_TIMER,
                                        NAS_SSA_TIMER_LENGTH_WAIT_NETWORK_RSP,
                                        ucTi))
    {
        SSA_LOG( ERROR_PRINT, "SSA_EraseSSReq:ERROR: VOS_StartRelTimer runs failed");
        SSA_TiFree(ucTi);
        return TAF_ERR_ERROR;
    }

    /*��SS������Ϣ*/
    Taf_SsMsgReq(&stRegisterMsg);

    /*��״̬���м��뵱ǰTi�������Ϣ*/
    gastSsaStatetable[ucTi].ucOperationCode = TAF_SS_ERASESS;
    gastSsaStatetable[ucTi].ucSsCode = pstEraseSSReqInfo->SsCode;
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, begin */
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, end */
    gastSsaStatetable[ucTi].ucState = SSA_USED;
    gastSsaStatetable[ucTi].ucMsgType = TAF_SS_MSG_TYPE_REGISTER;

    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    /* ͳһ�����룬�滻SSA_SUCCESSΪTAF_ERR_NO_ERROR */
    return TAF_ERR_NO_ERROR;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

}

/*****************************************************************************
 Prototype      : SSA_ActivateSSReq
 Description    : ����APP/AT�����ActivateSS����,�������������ݷ���SS
 Input          : *para--ActivateSS�����Ĳ���,������صı��뺯��
                  ucTi -- �����Ti
 Output         : ��
 Return Value   : �������
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.��    ��   : 2006��10��8��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ��:A32D06583��SSA��ʱ�����Ƶ�SS
  3.��    ��   : 2012��4��28��
    ��    ��   : f62575
    �޸�����   : DTS2012042601441,+CUSD=2��ʱ��δ�������
  4.��    ��   : 2013��5��6��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C��
  5.��    ��   : 2013��05��06��
   ��    ��   : f62575
   �޸�����   : SS FDN&Call Control��Ŀ��SS�������Ƶ�SSģ��
  6.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  7.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
*****************************************************************************/
VOS_UINT32 SSA_ActivateSSReq(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                           *pMsg
)
{
    ST_SSP_MSG                          stRegisterMsg;
    VOS_UINT32                          ulRslt;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
    VOS_UINT8                           ucTi;
    TAF_SS_ACTIVATESS_REQ_STRU         *pstActiveSsReq = VOS_NULL_PTR;
    TAF_CALL_NVIM_CCWA_CTRL_MODE_STRU   stCcwaCtrlMode;
    TAF_CALL_CCWAI_MODE_ENUM_UINT8      enCcwaiMode;
    VOS_UINT32                          ulRst;

    /* ����USSDҵ�����������������SSҵ�� */
    if (VOS_TRUE != TAF_SSA_IsUssdStateIdle())
    {
        return TAF_ERR_BUSY_ON_USSD;
    }

    /*��ȡ����ʹ�õ�Ti*/
    if (SSA_SUCCESS != SSA_TiAlloc(ClientId, OpId, &ucTi))
    {
        SSA_LOG( WARNING_PRINT, "SSA_ActivateSSReq: ActivateSS Ti alloc fail");
        return TAF_ERR_TI_ALLOC_FAIL;
    }

    pstActiveSsReq = (TAF_SS_ACTIVATESS_REQ_STRU *)pMsg;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, end */

    if (TAF_CW_SS_CODE == pstActiveSsReq->SsCode)
    {
        enCcwaiMode = TAF_GetCcwaiMode();

        /* ��CCWAI����д��NV */
        PS_MEM_SET(&stCcwaCtrlMode, 0, sizeof(stCcwaCtrlMode));
        stCcwaCtrlMode.enCcwaCtrlMode = TAF_CALL_CCWA_CTRL_BY_NW;
        stCcwaCtrlMode.enCcwaiMode = enCcwaiMode;

        ulRst = NV_Write(en_NV_Item_Ccwa_Ctrl_Mode,
                         (VOS_VOID *)&stCcwaCtrlMode,
                         sizeof(TAF_CALL_NVIM_CCWA_CTRL_MODE_STRU));

        /* ���дNVʧ�ܣ���CCWAI����ʧ�� */
        if (NV_OK != ulRst)
        {
            MN_ERR_LOG("SSA_ActivateSSReq:Write NVIM Error");
        }
        else
        {
            TAF_SetCcwaCtrlMode(TAF_CALL_CCWA_CTRL_BY_NW);
            TAF_WARNING_LOG2(WUEPS_PID_TAF, "SSA_ActivateSSReq ", TAF_CALL_CCWA_CTRL_BY_NW, enCcwaiMode);
        }
    }

    /*�������ݳ�ʼ��*/
    PS_MEM_SET(&stRegisterMsg, 0, sizeof(ST_SSP_MSG));

    /*ȷ��Ti����Ϣ����*/
    stRegisterMsg.ucCr = ucTi;
    stRegisterMsg.SspmsgCore.ucChoice = D_SMC_BEGIN_REQ;

    /*��MS�෢��ķ����RegisterSS�����Ĳ������ݽ��б���*/
    ulRslt = SSA_EncodeActivateSSReq(stRegisterMsg.SspmsgCore.u.BeginReq.Facility.Facility,
                                     (VOS_UINT8*)&(stRegisterMsg.SspmsgCore.u.BeginReq.Facility.ulCnt),
                                     pstActiveSsReq);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG( WARNING_PRINT, "SSA_ActivateSSReq:WARNING: Encode ActivateSSReq Error!");
        SSA_TiFree(ucTi);
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        /* ͳһ�����룬����ʧ�ܰ����������� */
        return TAF_ERR_PARA_ERROR;
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    }

    /*��װpstActiveSsReqmeter֮���ͷ��*/
    if (SSA_SUCCESS != SSA_PackMsgHeader(&(stRegisterMsg.SspmsgCore.u.BeginReq.Facility),TAF_SS_ACTIVATESS,
                                        TAF_SS_MSG_TYPE_REGISTER, ucTi, VOS_NULL, VOS_NULL))
    {
        SSA_LOG( WARNING_PRINT, "SSA_ActivateSSReq:WARNING: Encode MsgHeader Error!");
        SSA_TiFree(ucTi);
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        /* ͳһ�����룬�滻SSA_FAILUREΪTAF_ERR_ERROR */
        return TAF_ERR_ERROR;
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    }

    if ((VOS_TRUE != pstActiveSsReq->OP_Password)
     && (TAF_ALL_BARRING_SS_CODE == (pstActiveSsReq->SsCode & TAF_SS_CODE_MASK)))
    {
        SSA_LOG( NORMAL_PRINT, "SSA_ActivateSSReq: NO required password.");
        SSA_TiFree(ucTi);
        return TAF_ERR_SS_NO_PASSWORD;
    }

    /*�Ƿ�����SS version indicator,Ŀǰ��ʱ����*/
    stRegisterMsg.SspmsgCore.u.BeginReq.OP_Sspversion = 1;
    stRegisterMsg.SspmsgCore.u.BeginReq.Sspversion.ulCnt = 1;
    stRegisterMsg.SspmsgCore.u.BeginReq.Sspversion.Sspversion[0] = 0;

    /*������ʱ�����ȴ������Ļظ�*/
    if (VOS_TRUE !=  TAF_SSA_StartTimer(TI_TAF_SSA_WAIT_NETWORK_RSP_TIMER,
                                        NAS_SSA_TIMER_LENGTH_WAIT_NETWORK_RSP,
                                        ucTi))
    {
        SSA_LOG( ERROR_PRINT, "SSA_ActivateSSReq:ERROR: VOS_StartRelTimer runs failed");
        SSA_TiFree(ucTi);
        return TAF_ERR_ERROR;
    }

    /*��SS������Ϣ*/
    Taf_SsMsgReq(&stRegisterMsg);

    /*��״̬���м��뵱ǰTi�������Ϣ*/
    /* ������б���ҵ�񼤻��ȥ���������е����뵽����ȫ�ֱ��� */
    if (VOS_TRUE == pstActiveSsReq->OP_Password)
    {
        PS_MEM_CPY(gastSsaStatetable[ucTi].aucOldPwdStr, pstActiveSsReq->aucPassword, TAF_SS_MAX_PASSWORD_LEN);
        gastSsaStatetable[ucTi].ucPwdFlag = SSA_PASSWORD_VALID;
    }

    gastSsaStatetable[ucTi].ucOperationCode = TAF_SS_ACTIVATESS;
    gastSsaStatetable[ucTi].ucSsCode = pstActiveSsReq->SsCode;
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, begin */
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, end */
    gastSsaStatetable[ucTi].ucState = SSA_USED;
    gastSsaStatetable[ucTi].ucMsgType = TAF_SS_MSG_TYPE_REGISTER;

    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    /* ͳһ�����룬�滻SSA_SUCCESSΪTAF_ERR_NO_ERROR */
    return TAF_ERR_NO_ERROR;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

}
/*****************************************************************************
 Prototype      : SSA_DeactivateSSReq
 Description    : ����APP/AT�����DeactivateSS����,�������������ݷ���SS
 Input          : *para--DeactivateSS�����Ĳ��� ,������صı��뺯��
                  ucTi -- �����Ti
 Output         : ��
 Return Value   : �������
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.��    ��   : 2006��10��8��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ��:A32D06583��SSA��ʱ�����Ƶ�SS
  3.��    ��   : 2012��4��28��
    ��    ��   : f62575
    �޸�����   : DTS2012042601441,+CUSD=2��ʱ��δ�������
  4.��    ��   : 2013��5��6��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C��
  5.��    ��   : 2013��05��06��
   ��    ��   : f62575
   �޸�����   : SS FDN&Call Control��Ŀ��SS�������Ƶ�SSģ��
  6.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  7.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
*****************************************************************************/
VOS_UINT32 SSA_DeactivateSSReq(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                           *pMsg
)
{
    ST_SSP_MSG                          stRegisterMsg;
    VOS_UINT32                          ulRslt;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
    VOS_UINT8                           ucTi;
    TAF_SS_DEACTIVATESS_REQ_STRU       *pstDeactiveSsReq = VOS_NULL_PTR;
    TAF_CALL_NVIM_CCWA_CTRL_MODE_STRU   stCcwaCtrlMode;
    TAF_CALL_CCWAI_MODE_ENUM_UINT8      enCcwaiMode;
    VOS_UINT32                          ulRst;

    /* ����USSDҵ�����������������SSҵ�� */
    if (VOS_TRUE != TAF_SSA_IsUssdStateIdle())
    {
        return TAF_ERR_BUSY_ON_USSD;
    }

    /*��ȡ����ʹ�õ�Ti*/
    if (SSA_SUCCESS != SSA_TiAlloc(ClientId, OpId, &ucTi))
    {
        SSA_LOG( WARNING_PRINT, "SSA_DeactivateSSReq: DeactivateSS Ti alloc fail");
        return TAF_ERR_TI_ALLOC_FAIL;
    }

    pstDeactiveSsReq = (TAF_SS_DEACTIVATESS_REQ_STRU *)pMsg;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, end */

    if (TAF_CW_SS_CODE == pstDeactiveSsReq->SsCode)
    {
        enCcwaiMode = TAF_GetCcwaiMode();

        /* ��CCWAI����д��NV */
        PS_MEM_SET(&stCcwaCtrlMode, 0, sizeof(stCcwaCtrlMode));
        stCcwaCtrlMode.enCcwaCtrlMode = TAF_CALL_CCWA_CTRL_BY_NW;
        stCcwaCtrlMode.enCcwaiMode = enCcwaiMode;

        ulRst = NV_Write(en_NV_Item_Ccwa_Ctrl_Mode,
                         (VOS_VOID *)&stCcwaCtrlMode,
                         sizeof(TAF_CALL_NVIM_CCWA_CTRL_MODE_STRU));

        /* ���дNVʧ�ܣ���CCWAI����ʧ�� */
        if (NV_OK != ulRst)
        {
            MN_ERR_LOG("SSA_ActivateSSReq:Write NVIM Error");
        }
        else
        {
            TAF_SetCcwaCtrlMode(TAF_CALL_CCWA_CTRL_BY_NW);
            TAF_WARNING_LOG2(WUEPS_PID_TAF, "SSA_DeactivateSSReq ", TAF_CALL_CCWA_CTRL_BY_NW, enCcwaiMode);
        }
    }

    /*�������ݳ�ʼ��*/
    PS_MEM_SET(&stRegisterMsg, 0, sizeof(ST_SSP_MSG));

    /*ȷ��Ti����Ϣ����*/
    stRegisterMsg.ucCr = ucTi;
    stRegisterMsg.SspmsgCore.ucChoice = D_SMC_BEGIN_REQ;

    /*��MS�෢��ķ����RegisterSS�����Ĳ������ݽ��б���*/
    ulRslt = SSA_EncodeDeactivateSSReq(stRegisterMsg.SspmsgCore.u.BeginReq.Facility.Facility,
                                       (VOS_UINT8*)&(stRegisterMsg.SspmsgCore.u.BeginReq.Facility.ulCnt),
                                       pstDeactiveSsReq);
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG( WARNING_PRINT, "SSA_DeactivateSSReq:WARNING: Encode DeactivateSSReq Error!");
        SSA_TiFree(ucTi);
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        /* ͳһ�����룬����ʧ�ܰ����������� */
        return TAF_ERR_PARA_ERROR;
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    }

    /*��װpstDeactiveSsReqmeter֮���ͷ��*/
    if (SSA_SUCCESS != SSA_PackMsgHeader(&(stRegisterMsg.SspmsgCore.u.BeginReq.Facility),TAF_SS_DEACTIVATESS,
                                         TAF_SS_MSG_TYPE_REGISTER, ucTi, VOS_NULL, VOS_NULL))
    {
        SSA_LOG( WARNING_PRINT, "SSA_DeactivateSSReq:WARNING: Encode MsgHeader Error!");
        SSA_TiFree(ucTi);
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        /* ͳһ�����룬�滻SSA_FAILUREΪTAF_ERR_ERROR */
        return TAF_ERR_ERROR;
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

    }

    /* ������б���ҵ�񼤻��ȥ���������е����뵽����ȫ�ֱ��� */
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    if ((VOS_TRUE != pstDeactiveSsReq->OP_Password)
     && (TAF_ALL_BARRING_SS_CODE == (pstDeactiveSsReq->SsCode & TAF_SS_CODE_MASK)))
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    {
        SSA_LOG( NORMAL_PRINT, "SSA_DeactivateSSReq: NO required password.");
        SSA_TiFree(ucTi);
        return TAF_ERR_SS_NO_PASSWORD;
    }

    /*�Ƿ�����SS version indicator,Ŀǰ��ʱ����*/
    stRegisterMsg.SspmsgCore.u.BeginReq.OP_Sspversion = 1;
    stRegisterMsg.SspmsgCore.u.BeginReq.Sspversion.ulCnt = 1;
    stRegisterMsg.SspmsgCore.u.BeginReq.Sspversion.Sspversion[0] = 0;

    /*������ʱ�����ȴ������Ļظ�*/
    if (VOS_TRUE !=  TAF_SSA_StartTimer(TI_TAF_SSA_WAIT_NETWORK_RSP_TIMER,
                                        NAS_SSA_TIMER_LENGTH_WAIT_NETWORK_RSP,
                                        ucTi))
    {
        SSA_LOG( ERROR_PRINT, "SSA_DeactivateSSReq:ERROR: VOS_StartRelTimer runs failed");
        SSA_TiFree(ucTi);
        return TAF_ERR_ERROR;
    }

    /*��SS������Ϣ*/
    Taf_SsMsgReq(&stRegisterMsg);

    /*��״̬���м��뵱ǰTi�������Ϣ*/
    /* ������б���ҵ�񼤻��ȥ���������е����뵽����ȫ�ֱ��� */
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    if (VOS_TRUE == pstDeactiveSsReq->OP_Password)
    {
        PS_MEM_CPY(gastSsaStatetable[ucTi].aucOldPwdStr, pstDeactiveSsReq->aucPassword, TAF_SS_MAX_PASSWORD_LEN);
        gastSsaStatetable[ucTi].ucPwdFlag = SSA_PASSWORD_VALID;
    }
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

    gastSsaStatetable[ucTi].ucOperationCode = TAF_SS_DEACTIVATESS;
    gastSsaStatetable[ucTi].ucSsCode = pstDeactiveSsReq->SsCode;
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, begin */
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, end */
    gastSsaStatetable[ucTi].ucState = SSA_USED;
    gastSsaStatetable[ucTi].ucMsgType = TAF_SS_MSG_TYPE_REGISTER;

    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    /* ͳһ�����룬�滻SSA_SUCCESSΪTAF_ERR_NO_ERROR */
    return TAF_ERR_NO_ERROR;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
}

/*****************************************************************************
 Prototype      : SSA_InterrogateSSReq
 Description    : ����APP/AT�����InterrogateSS����,������صı��뺯��,����
                  ���������ݷ���SS
 Input          : *para--InterrogateSS�����Ĳ���
                  ucTi -- �����Ti
 Output         : ��
 Return Value   : �������
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.��    ��   : 2006��10��8��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ��:A32D06583��SSA��ʱ�����Ƶ�SS

  3.��    ��   : 2010��3��1��
    ��    ��   : zhoujun /z40661
    �޸�����   : NAS R7Э�������޸ķ��͵�����Version
  4.��    ��   : 2012��4��28��
    ��    ��   : f62575
    �޸�����   : DTS2012042601441,+CUSD=2��ʱ��δ�������
  5.��    ��   : 2013��5��6��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C��
  6.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  7.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
*****************************************************************************/
VOS_UINT32 SSA_InterrogateSSReq(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                           *pMsg
)
{
    ST_SSP_MSG                          stRegisterMsg;
    VOS_UINT32                          ulRslt;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
    VOS_UINT8                           ucTi;
    TAF_SS_INTERROGATESS_REQ_STRU      *pstInterrogateSsReq = VOS_NULL_PTR;

    /* ����USSDҵ�����������������SSҵ�� */
    if (VOS_TRUE != TAF_SSA_IsUssdStateIdle())
    {
        return TAF_ERR_BUSY_ON_USSD;
    }

    /*��ȡ����ʹ�õ�Ti*/
    if (SSA_SUCCESS != SSA_TiAlloc(ClientId, OpId, &ucTi))
    {
        SSA_LOG( WARNING_PRINT, "SSA_InterrogateSSReq: InterrogateSS Ti alloc fail");
        return TAF_ERR_TI_ALLOC_FAIL;
    }

    pstInterrogateSsReq = (TAF_SS_INTERROGATESS_REQ_STRU *)pMsg;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, end */

    /*�������ݳ�ʼ��*/
    PS_MEM_SET(&stRegisterMsg, 0, sizeof(ST_SSP_MSG));

    /*ȷ��Ti����Ϣ����*/
    stRegisterMsg.ucCr = ucTi;
    stRegisterMsg.SspmsgCore.ucChoice = D_SMC_BEGIN_REQ;

    /*��MS�෢��ķ����RegisterSS�����Ĳ������ݽ��б���*/
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    ulRslt = SSA_EncodeInterrogateSsReq(stRegisterMsg.SspmsgCore.u.BeginReq.Facility.Facility,
                                        (VOS_UINT8*)&(stRegisterMsg.SspmsgCore.u.BeginReq.Facility.ulCnt),
                                        pstInterrogateSsReq);
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    if (SSA_SUCCESS != ulRslt)
    {
        SSA_LOG( WARNING_PRINT, "SSA_InterrogateSSReq:WARNING: Encode InterrogateSSReq Error!");
        SSA_TiFree(ucTi);
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        /* ͳһ�����룬����ʧ�ܰ����������� */
        return TAF_ERR_PARA_ERROR;
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    }

    /* ��װparameter֮���ͷ��  */
    if (SSA_SUCCESS != SSA_PackMsgHeader(&(stRegisterMsg.SspmsgCore.u.BeginReq.Facility),TAF_SS_INTERROGATESS,
                                        TAF_SS_MSG_TYPE_REGISTER, ucTi, VOS_NULL, VOS_NULL))
    {
        SSA_LOG( WARNING_PRINT, "SSA_InterrogateSSReq:WARNING: Encode MsgHeader Error!");
        SSA_TiFree(ucTi);
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        /* ͳһ�����룬�滻SSA_FAILUREΪTAF_ERR_ERROR */
        return TAF_ERR_ERROR;
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    }

    /*�Ƿ�����SS version indicator,�����CCBSҵ����SS Version��ֵΪ2��2���ϣ��������
    SS Version��ʱ������*/
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    if (( pstInterrogateSsReq->SsCode == TAF_CCBS_A_SS_CODE )
     || ( pstInterrogateSsReq->SsCode == TAF_CCBS_B_SS_CODE ))
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    {
        stRegisterMsg.SspmsgCore.u.BeginReq.OP_Sspversion = 1;
        stRegisterMsg.SspmsgCore.u.BeginReq.Sspversion.ulCnt = 1;
        stRegisterMsg.SspmsgCore.u.BeginReq.Sspversion.Sspversion[0] = 1;
    }
    else
    {
        stRegisterMsg.SspmsgCore.u.BeginReq.OP_Sspversion = 1;
        stRegisterMsg.SspmsgCore.u.BeginReq.Sspversion.ulCnt = 1;
        stRegisterMsg.SspmsgCore.u.BeginReq.Sspversion.Sspversion[0] = 0;
    }

    /*������ʱ�����ȴ������Ļظ�*/
    if (VOS_TRUE !=  TAF_SSA_StartTimer(TI_TAF_SSA_WAIT_NETWORK_RSP_TIMER,
                                        NAS_SSA_TIMER_LENGTH_WAIT_NETWORK_RSP,
                                        ucTi))
    {
        SSA_LOG( ERROR_PRINT, "SSA_InterrogateSSReq:ERROR: VOS_StartRelTimer runs failed");
        SSA_TiFree(ucTi);
        return TAF_ERR_ERROR;
    }

    /*��SS������Ϣ*/
    Taf_SsMsgReq(&stRegisterMsg);

    /*��״̬���м��뵱ǰTi�������Ϣ*/
    gastSsaStatetable[ucTi].ucOperationCode = TAF_SS_INTERROGATESS;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    gastSsaStatetable[ucTi].ucSsCode        = pstInterrogateSsReq->SsCode;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, begin */
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, end */
    gastSsaStatetable[ucTi].ucState = SSA_USED;
    gastSsaStatetable[ucTi].ucMsgType = TAF_SS_MSG_TYPE_REGISTER;

    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    /* ͳһ�����룬�滻SSA_SUCCESSΪTAF_ERR_NO_ERROR */
    return TAF_ERR_NO_ERROR;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
}

/*****************************************************************************
 Prototype      : SSA_RegisterPasswordReq
 Description    : ����APP/AT�����RegisterPassWord����,������صı��뺯��,����
                  ���������ݷ���SS
 Input          : *para--RegisterPassWord�����Ĳ���
                  ucTi -- �����Ti
 Output         : ��
 Return Value   : �������
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.��    ��   : 2006��10��8��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ��:A32D06583��SSA��ʱ�����Ƶ�SS
  3.��    ��   : 2010��6��21��
    ��    ��   : z00161729
    �޸�����   : ���ⵥ��:DTS2010061900253
  4.��    ��   : 2012��4��28��
    ��    ��   : f62575
    �޸�����   : DTS2012042601441,+CUSD=2��ʱ��δ�������
  5.��    ��   : 2013��5��6��
    ��    ��   : s00217060
    �޸�����  : �����ϱ�AT�������������C��
  6.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  7.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
*****************************************************************************/
VOS_UINT32 SSA_RegisterPasswordReq(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                           *pMsg
)
{
    ST_SSP_MSG                          stRegisterMsg;
    VOS_UINT32                          ulRslt;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
    VOS_UINT8                           ucTi;
    TAF_SS_REGPWD_REQ_STRU             *pstRegPassWord = VOS_NULL_PTR;

    /* ����USSDҵ�����������������SSҵ�� */
    if (VOS_TRUE != TAF_SSA_IsUssdStateIdle())
    {
        return TAF_ERR_BUSY_ON_USSD;
    }

    /*��ȡ����ʹ�õ�Ti*/
    if (SSA_SUCCESS != SSA_TiAlloc(ClientId, OpId, &ucTi))
    {
        SSA_LOG( WARNING_PRINT, "SSA_RegisterPasswordReq: RegisterPassword Ti alloc fail");
        return TAF_ERR_TI_ALLOC_FAIL;
    }

    pstRegPassWord = (TAF_SS_REGPWD_REQ_STRU *)pMsg;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, end */

    if (TAF_ALL_BARRING_SS_CODE == (pstRegPassWord->SsCode & 0xf0))
    {
        pstRegPassWord->SsCode = TAF_ALL_BARRING_SS_CODE;
    }

    /*�������ݳ�ʼ��*/
    PS_MEM_SET(&stRegisterMsg, 0, sizeof(ST_SSP_MSG));

    /*ȷ��Ti����Ϣ����*/
    stRegisterMsg.ucCr = ucTi;
    stRegisterMsg.SspmsgCore.ucChoice = D_SMC_BEGIN_REQ;

    /*��MS�෢��ķ����RegisterPassword�����Ĳ������ݽ��б���*/
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    ulRslt = SSA_EncodeRegPwdReq(stRegisterMsg.SspmsgCore.u.BeginReq.Facility.Facility,
                                 (VOS_UINT8*)&(stRegisterMsg.SspmsgCore.u.BeginReq.Facility.ulCnt),
                                 pstRegPassWord);
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

    if (SSA_SUCCESS != ulRslt)
    {
        /*Ӧ�������������󣬳������ϱ���Ӧ�ã����ýӿں���*/
        /*�ͷ�״̬��ǰTi������*/
        SSA_LOG( WARNING_PRINT, "SSA_RegisterPasswordReq:WARNING: Encode RegisterPasswordReq Error!");
        SSA_TiFree(ucTi);
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        /* ͳһ�����룬����ʧ�ܰ����������� */
        return TAF_ERR_PARA_ERROR;
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    }

    /*��װpstRegPassWordmeter֮���ͷ��*/
    if (SSA_SUCCESS != SSA_PackMsgHeader(&(stRegisterMsg.SspmsgCore.u.BeginReq.Facility), TAF_SS_REGISTERPASSWORD,
                                        TAF_SS_MSG_TYPE_REGISTER, ucTi, VOS_NULL, VOS_NULL))
    {
        SSA_LOG( WARNING_PRINT, "SSA_RegisterPasswordReq:WARNING: Encode MsgHeader Error!");
        SSA_TiFree(ucTi);
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        /* ͳһ�����룬�滻SSA_FAILUREΪTAF_ERR_ERROR */
        return TAF_ERR_ERROR;
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    }

    /*�Ƿ�����SS version indicator,Ŀǰ��ʱ����*/
    stRegisterMsg.SspmsgCore.u.BeginReq.OP_Sspversion = 1;
    stRegisterMsg.SspmsgCore.u.BeginReq.Sspversion.ulCnt = 1;
    stRegisterMsg.SspmsgCore.u.BeginReq.Sspversion.Sspversion[0] = 0;

    /*������ʱ�����ȴ������Ļظ�*/
    if (VOS_TRUE != TAF_SSA_StartTimer(TI_TAF_SSA_WAIT_NETWORK_RSP_TIMER,
                                        NAS_SSA_TIMER_LENGTH_WAIT_NETWORK_RSP,
                                        ucTi))
    {
        SSA_LOG( ERROR_PRINT, "SSA_RegisterPasswordReq:ERROR: VOS_StartRelTimer runs failed");
        SSA_TiFree(ucTi);
        return TAF_ERR_ERROR;
    }

    /*��SS������Ϣ*/
    Taf_SsMsgReq(&stRegisterMsg);

    /*��״̬���м��뵱ǰTi�������Ϣ,��password����״̬����*/
    gastSsaStatetable[ucTi].ucOperationCode = TAF_SS_REGISTERPASSWORD;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    gastSsaStatetable[ucTi].ucSsCode        = pstRegPassWord->SsCode;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, begin */
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, end */
    gastSsaStatetable[ucTi].ucState = SSA_USED;
    gastSsaStatetable[ucTi].ucMsgType = TAF_SS_MSG_TYPE_REGISTER;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    PS_MEM_CPY(gastSsaStatetable[ucTi].aucOldPwdStr, pstRegPassWord->aucOldPwdStr ,TAF_SS_MAX_PASSWORD_LEN);
    PS_MEM_CPY(gastSsaStatetable[ucTi].aucNewPwdStr, pstRegPassWord->aucNewPwdStr, TAF_SS_MAX_PASSWORD_LEN);
    PS_MEM_CPY(gastSsaStatetable[ucTi].aucNewPwdStrCnf, pstRegPassWord->aucNewPwdStrCnf, TAF_SS_MAX_PASSWORD_LEN);
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    gastSsaStatetable[ucTi].ucPwdFlag = SSA_PASSWORD_VALID;

    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    /* ͳһ�����룬�滻SSA_SUCCESSΪTAF_ERR_NO_ERROR */
    return TAF_ERR_NO_ERROR;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

}

/*****************************************************************************
 Prototype      : SSA_GetPasswordInd
 Description    : ����APP/AT�����Ķ�GetPassWord��������Ӧ,������صı��뺯��,����
                  ���������ݷ���SS
 Input          : *para--GetPassWord�����Ĳ���
                  ucTi -- �����Ti
 Output         : ��
 Return Value   : ��
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
*****************************************************************************/
VOS_VOID SSA_GetPasswordRsp (TAF_SS_GETPWD_RSP_STRU  *para, VOS_UINT8 ucTi)
{

    ST_SSP_MSG             stFacilityMsg;
    VOS_UINT32             ulRslt;

    /*�������ݳ�ʼ��*/
    PS_MEM_SET(&stFacilityMsg, 0, sizeof(ST_SSP_MSG));

    /*ȷ��Ti����Ϣ����*/
    stFacilityMsg.ucCr = ucTi;
    stFacilityMsg.SspmsgCore.ucChoice = D_SMC_FACILITY_REQ;

    /*��MS�෢��ķ����RegisterPassword�����Ĳ������ݽ��б���*/
    ulRslt = SSA_EncodeGetPwdRsp(stFacilityMsg.SspmsgCore.u.FacilityReq.Facility.Facility,
                                 (VOS_UINT8*)&(stFacilityMsg.SspmsgCore.u.FacilityReq.Facility.ulCnt),
                                 para);

    if (SSA_SUCCESS != ulRslt)
    {
        /*Ӧ�������������󣬷���*/
        SSA_LOG( WARNING_PRINT, "SSA_GetPasswordRsp:WARNING: Encode GetPasswordRsp Error!");
        return;
    }

    /*��װparameter֮���ͷ��*/
    if (SSA_SUCCESS != SSA_PackMsgHeader(&(stFacilityMsg.SspmsgCore.u.FacilityReq.Facility), TAF_SS_GETPASSWORD,
                                         TAF_SS_MSG_TYPE_FACILITY, ucTi, VOS_NULL, VOS_NULL))
    {
        SSA_LOG( WARNING_PRINT, "SSA_GetPasswordRsp:WARNING: Encode MsgHeader Error!");
        SSA_TiFree(ucTi);
        return;
    }

    /*��SS������Ϣ*/
    Taf_SsMsgReq(&stFacilityMsg);

    /*�رռ�ʱ��*/

    return;
}

/*****************************************************************************
 �� �� ��  : SSA_SendUnstructuredSSReq
 ��������  : ����USSD����MM
 �������  : VOS_UINT8 ucTi
 �� �� ֵ  : ����USSD����MM���
                TAF_ERR_NO_ERROR            ���ͳɹ�
                ������                      ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��23��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 SSA_SendUnstructuredSSReq(VOS_UINT8 ucTi)
{
    ST_SSP_MSG                          stRegisterMsg;
    VOS_UINT32                          ulRslt;

    /*�������ݳ�ʼ��*/
    PS_MEM_SET(&stRegisterMsg, 0, sizeof(ST_SSP_MSG));

    /*ȷ��Ti����Ϣ����*/
    stRegisterMsg.ucCr                = ucTi;
    stRegisterMsg.SspmsgCore.ucChoice = D_SMC_BEGIN_REQ;

    /*��MS�෢��ķ����RegisterSS�����Ĳ������ݽ��б���*/
    ulRslt = SSA_EncodeProcessUntructuredSSReq(stRegisterMsg.SspmsgCore.u.BeginReq.Facility.Facility,
                                               (VOS_UINT8*)&(stRegisterMsg.SspmsgCore.u.BeginReq.Facility.ulCnt),
                                               ucTi);
    if (SSA_SUCCESS != ulRslt)
    {
        /*Ӧ�������������󣬷����ͷ�״̬��ǰTi������*/
        SSA_LOG( WARNING_PRINT, "SSA_SendUnstructuredSSReq:WARNING: Encode ProcessUnstructuredSSReq Error!");
        return TAF_ERR_UNSPECIFIED_ERROR;
    }

    /*��װparameter֮���ͷ��*/
    if (SSA_SUCCESS != SSA_PackMsgHeader(&(stRegisterMsg.SspmsgCore.u.BeginReq.Facility), TAF_SS_PROCESS_USS_REQ,
                                         TAF_SS_MSG_TYPE_REGISTER, ucTi, VOS_NULL, VOS_NULL))
    {
        SSA_LOG( WARNING_PRINT, "SSA_ProcessUnstructuredSSReq:WARNING: Encode MsgHeader Error!");
        return TAF_ERR_UNSPECIFIED_ERROR;
    }

    /*�Ƿ�����SS version indicator,Ŀǰ��ʱ����*/
    stRegisterMsg.SspmsgCore.u.BeginReq.OP_Sspversion = 1;
    stRegisterMsg.SspmsgCore.u.BeginReq.Sspversion.ulCnt = 1;
    stRegisterMsg.SspmsgCore.u.BeginReq.Sspversion.Sspversion[0] = 0;

    /*��SS������Ϣ*/
    Taf_SsMsgReq(&stRegisterMsg);

    return TAF_ERR_NO_ERROR;
}

/*****************************************************************************
 �� �� ��  : SSA_RequireUnpackSscStr
 ��������  : ��7BIT�����SSC�ַ�������
 �������  : VOS_UINT8 ucTi Tiֵ
 �������  : ��
 �� �� ֵ  : VOS_UINT32
                VOS_TRUE            ����Ҫ����
                VOS_FALSE           ��Ҫ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��23��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 SSA_RequireUnpackSscStr(
    TAF_SS_DATA_CODING_SCHEME           ucDatacodingScheme
)
{
    if (AT_USSD_TRAN_MODE == SSA_GetUssdTransMode())
    {
        if ((TAF_SS_7bit_LANGUAGE_UNSPECIFIED == ucDatacodingScheme)
         || (TAF_SS_7BIT_DATA_CODING          == ucDatacodingScheme))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : SSA_ProcessUnstructuredSSReq
 ��������  : ����APP/AT�����ProcessUnstructuredSS-Request����,������صı��뺯��,
 �������  : MN_CLIENT_ID_T                      clientId   ����������Client��ID
              TAF_SS_PROCESS_USS_REQ_STRU        *para       USSD ���뻺����ָ��
              VOS_UINT8                           ucTi       ���ط����TI����������SSʵ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2005��8��15��
    ��    ��   :
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��8��16��
    ��    ��   : ��ë/00166186
    �޸�����   : DTS2010081702586 �¹�����USSD PHASE1 ����������
  3.��    ��   : 2012��02��24��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : C50_IPC Project  �û������USSDҵ�����FDN���
  4.��    ��   : 2012��4��28��
    ��    ��   : f62575
    �޸�����   : DTS2012042601441,+CUSD=2��ʱ��δ�������
  5.��    ��   : 2013��5��14��
    ��    ��   : w00176964
    �޸�����   : SS FDN&Call Control��Ŀ:FDN����߼��Ƶ�SPMģ�鴦��
  6.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
*****************************************************************************/
VOS_UINT32 SSA_ProcessUnstructuredSSReq(
    VOS_UINT16                          ClientId,
    TAF_SS_PROCESS_USS_REQ_STRU        *para,
    VOS_UINT8                           ucTi
)
{
    VOS_UINT32                          ulRet;

    gastSsaStatetable[ucTi].pstUssdBuf = (TAF_SS_USSD_STRING_STRU*)PS_MEM_ALLOC(WUEPS_PID_SS, sizeof(TAF_SS_USSD_STRING_STRU));

    if (VOS_NULL_PTR == gastSsaStatetable[ucTi].pstUssdBuf)
    {
        SSA_LOG( ERROR_PRINT, "SSA_ProcessUnstructuredSSReq:ERROR: Fail to alloc memory.");
        SSA_TiFree(ucTi);
        return TAF_ERR_INTERNAL;
    }

    gastSsaStatetable[ucTi].pstUssdBuf->usCnt = para->UssdStr.usCnt;
    PS_MEM_CPY(gastSsaStatetable[ucTi].pstUssdBuf->aucUssdStr,
               para->UssdStr.aucUssdStr,
               para->UssdStr.usCnt);
    gastSsaStatetable[ucTi].DatacodingScheme = para->DatacodingScheme;
    gastSsaStatetable[ucTi].OP_AlertingPattern = para->OP_AlertingPattern;
    gastSsaStatetable[ucTi].OP_Msisdn = para->OP_Msisdn;
    gastSsaStatetable[ucTi].AlertingPattern = para->AlertingPattern;
    PS_MEM_CPY(gastSsaStatetable[ucTi].aucMsisdn, para->aucMsisdn, (TAF_SS_MAX_MSISDN_LEN + 1));

    /* ɾ��FDN������� */

    ulRet = SSA_SendUnstructuredSSReq(ucTi);
    if (TAF_ERR_NO_ERROR != ulRet)
    {
        SSA_LOG( ERROR_PRINT, "SSA_ProcessUnstructuredSSReq:ERROR: SSA_SendUnstructuredSSReq failed");
        SSA_TiFree(ucTi);
        return ulRet;
    }

    /*������ʱ�����ȴ������Ļظ�*/
    if (VOS_TRUE !=  TAF_SSA_StartTimer(TI_TAF_SSA_WAIT_NETWORK_RSP_TIMER,
                                        NAS_SSA_TIMER_LENGTH_WAIT_NETWORK_RSP,
                                        ucTi))
    {
        SSA_LOG( ERROR_PRINT, "SSA_ProcessUnstructuredSSReq:ERROR: VOS_StartRelTimer runs failed");
        SSA_TiFree(ucTi);
        return TAF_ERR_ERROR;
    }

    /*��״̬���м��뵱ǰTi�������Ϣ*/
    gastSsaStatetable[ucTi].ucOperationCode = TAF_SS_PROCESS_USS_REQ;
    gastSsaStatetable[ucTi].ucUssdFlag      = TAF_SSA_USSD_MO_CONN_STATE;
    gastSsaStatetable[ucTi].ucState         = SSA_USED;
    gastSsaStatetable[ucTi].ucMsgType       = TAF_SS_MSG_TYPE_REGISTER;

    SSA_ReportUssdDataSndEvent(ucTi);

    return TAF_ERR_NO_ERROR;
}

/*****************************************************************************
 Prototype      : SSA_ProcessUSSDataReq
 Description    : APP/AT�����ProcessUnstructuredSS-Request����,���粻֧�֣�
                  ���� ProcessUSSData������������صı��뺯��,
                  �������������ݷ���SS
 Input          : *para--TAF_SS_PROCESS_USSDATA_REQ_STRU�����Ĳ���
                  ucTi -- �����Ti
 Output         : ��
 Return Value   : �������
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2007-01-22
    Author      : ---
    Modification: Created function for A32D08448
  2.��    ��   : 2012��4��28��
    ��    ��   : f62575
    �޸�����   : DTS2012042601441,+CUSD=2��ʱ��δ�������
  3.��    ��   : 2013��5��6��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C��
  4.��    ��   : 2013��6��17��
    ��    ��   : s00217060
    �޸�����   : V9R1_SVLTE
  5.��    ��   : 2013��08��19��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ����MTC�ϱ�CS��ҵ��״̬
  6.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
*****************************************************************************/
VOS_UINT32 SSA_ProcessUSSDataReq(TAF_SS_PROCESS_USSDATA_REQ_STRU *para, VOS_UINT8 ucTi)
{
    ST_SSP_MSG             stRegisterMsg;
    VOS_UINT32             ulRslt;

    /*�������ݳ�ʼ��*/
    PS_MEM_SET(&stRegisterMsg, 0, sizeof(ST_SSP_MSG));

    /*ȷ��Ti����Ϣ����*/
    stRegisterMsg.ucCr = ucTi;
    stRegisterMsg.SspmsgCore.ucChoice = D_SMC_BEGIN_REQ;

    /*��MS�෢��ķ����RegisterSS�����Ĳ������ݽ��б���*/
    ulRslt = SSA_EncodeUssData(stRegisterMsg.SspmsgCore.u.BeginReq.Facility.Facility,
                               (VOS_UINT8*)&(stRegisterMsg.SspmsgCore.u.BeginReq.Facility.ulCnt),
                               para);
    if (SSA_SUCCESS != ulRslt)
    {
        /*Ӧ�������������󣬷����ͷ�״̬��ǰTi������*/
        SSA_LOG( WARNING_PRINT, "SSA_ProcessUnstructuredSSReq:WARNING: Encode ProcessUnstructuredSSReq Error!");
        SSA_TiFree(ucTi);
        return ulRslt;
    }

    /*��װparameter֮���ͷ��*/
    if (SSA_SUCCESS != SSA_PackMsgHeader(&(stRegisterMsg.SspmsgCore.u.BeginReq.Facility), TAF_SS_PROCESS_USS_DATA,
                                         TAF_SS_MSG_TYPE_REGISTER, ucTi, VOS_NULL, VOS_NULL))
    {
        SSA_LOG( WARNING_PRINT, "SSA_ProcessUnstructuredSSReq:WARNING: Encode MsgHeader Error!");
        SSA_TiFree(ucTi);
        return SSA_FAILURE;
    }

    /*�Ƿ�����SS version indicator,Ŀǰ��ʱ����*/
    stRegisterMsg.SspmsgCore.u.BeginReq.OP_Sspversion = 0;
    stRegisterMsg.SspmsgCore.u.BeginReq.Sspversion.ulCnt = 1;
    stRegisterMsg.SspmsgCore.u.BeginReq.Sspversion.Sspversion[0] = 0;

    /*������ʱ�����ȴ������Ļظ�*/
    if (VOS_TRUE !=  TAF_SSA_StartTimer(TI_TAF_SSA_WAIT_NETWORK_RSP_TIMER,
                                        NAS_SSA_TIMER_LENGTH_WAIT_NETWORK_RSP,
                                        ucTi))
    {
        SSA_LOG( ERROR_PRINT, "SSA_ProcessUnstructuredSSReq:ERROR: VOS_StartRelTimer runs failed");
        SSA_TiFree(ucTi);
        return TAF_ERR_ERROR;
    }

    /*��SS������Ϣ*/
    Taf_SsMsgReq(&stRegisterMsg);

    /*��״̬���м��뵱ǰTi�������Ϣ*/
    /* gastSsaStatetable[ucTi].ucSsCode = para->SsCode; */
    gastSsaStatetable[ucTi].ucOperationCode = TAF_SS_PROCESS_USS_DATA;
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, begin */
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, end */
    gastSsaStatetable[ucTi].ucState = SSA_USED;
    gastSsaStatetable[ucTi].ucMsgType = TAF_SS_MSG_TYPE_REGISTER;

    /* û�е���SSA_TiAlloc��������Ҫ������һ��CS���SSҵ���Ƿ���ڵı�־ */
    TAF_SDC_SetCsSsSrvExistFlg(VOS_TRUE);

    /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* ��MTCģ���ϱ���ǰCS��ҵ��״̬ */
    TAF_SendMtcCsSrvInfoInd();
#endif
    /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, end */

    return SSA_SUCCESS;
}

/*****************************************************************************
 Prototype      : SSA_UnstructuredSSRsp
 Description    : ����APP/AT�����Ķ�UnstructuredSS-Request��������Ӧ,������ص�
                  ���뺯��, �������������ݷ���SS
 Input          : *para--UnstructuredSSReq�����Ĳ���
                  ucTi -- �����Ti
                  ClientId - client id
                  OpId     - operation id
 Output         : ��
 Return Value   : �������
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.��    ��   : 2013��4��10��
    ��    ��   : z00161729
    �޸�����   : �����ϱ�AT�������������C�˼�mma��mmc�ӿڵ���
  3.��    ��   : 2013��8��1��
    ��    ��   : z00161729
    �޸�����   : V9R1 STK�����޸�
  4.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
*****************************************************************************/
VOS_UINT32 SSA_UnstructuredSSRsp(
    TAF_SS_USS_RSP_STRU                *para,
    VOS_UINT8                           ucTi,
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId
)
{

    ST_SSP_MSG                          stFacilityMsg;
    VOS_UINT32                          ulRslt;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *pstSsEvent;
    TAF_UINT8                           ucTmpMsgType;

    /*�������ݳ�ʼ��*/
    PS_MEM_SET(&stFacilityMsg, 0, sizeof(ST_SSP_MSG));

    /*ȷ��Ti����Ϣ����*/
    stFacilityMsg.ucCr = ucTi;
    stFacilityMsg.SspmsgCore.ucChoice = D_SMC_FACILITY_REQ;

    ulRslt = SSA_EncodeUntructuredSSRsp(stFacilityMsg.SspmsgCore.u.FacilityReq.Facility.Facility,
                                        (VOS_UINT8*)&(stFacilityMsg.SspmsgCore.u.FacilityReq.Facility.ulCnt),
                                        para);
    if (SSA_SUCCESS != ulRslt)
    {
        /*Ӧ�������������󣬷���*/
        SSA_LOG( WARNING_PRINT, "SSA_UnstructuredSSRsp:WARNING: Encode ProcessUnstructuredSSReq Error!");
        return ulRslt;
    }

    /*��װparameter֮���ͷ��*/
    if (SSA_SUCCESS != SSA_PackMsgHeader(&(stFacilityMsg.SspmsgCore.u.FacilityReq.Facility), TAF_SS_USS_REQ,
                                         TAF_SS_MSG_TYPE_FACILITY, ucTi, VOS_NULL, VOS_NULL))
    {
        SSA_LOG( WARNING_PRINT, "SSA_UnstructuredSSRsp:WARNING: Encode MsgHeader Error!");
        SSA_TiFree(ucTi);
        return SSA_FAILURE;
    }

    /*������ʱ�����ȴ������Ļظ�*/
    if (VOS_TRUE !=  TAF_SSA_StartTimer(TI_TAF_SSA_WAIT_NETWORK_RSP_TIMER,
                                        NAS_SSA_TIMER_LENGTH_WAIT_NETWORK_RSP,
                                        ucTi))
    {
        SSA_LOG( ERROR_PRINT, "SSA_UnstructuredSSRsp:ERROR: VOS_StartRelTimer runs failed");
        SSA_TiFree(ucTi);
        return SSA_FAILURE;
    }

    /*��SS������Ϣ*/
    Taf_SsMsgReq(&stFacilityMsg);

    /*�رռ�ʱ��*/
    TAF_SSA_StopTimer(TI_TAF_SSA_WAIT_APP_RSP_TIMER, ucTi);

    pstSsEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_SS, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
    if (VOS_NULL_PTR == pstSsEvent)
    {
        SSA_LOG( ERROR_PRINT, "Ss_RcvMnssBeginReq:ERROR: Alloc Mem Fail");
        return SSA_SUCCESS;
    }

    /*���¼��ϱ������ݸ���ֵ*/
    PS_MEM_SET(pstSsEvent, 0 , 4);
    pstSsEvent->SsEvent =  TAF_SS_EVT_USSD_DATA_SND;

    /* Modified by z00161729 for V9R1 STK����, 2013-7-25, begin */
    pstSsEvent->OpId = OpId;
    pstSsEvent->ClientId = ClientId;
    /* Modified by z00161729 for V9R1 STK����, 2013-7-25, end */

    /* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
    gastSsaStatetable[ucTi].ucUssdFlag      = TAF_SSA_USSD_MO_CONN_STATE;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, end */

    ucTmpMsgType = gastSsaStatetable[ucTi].ucMsgType;
    gastSsaStatetable[ucTi].ucMsgType = TAF_SS_MSG_TYPE_FACILITY;
    TAF_SsEventReport(pstSsEvent);
    gastSsaStatetable[ucTi].ucMsgType = ucTmpMsgType;
    PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);

    return SSA_SUCCESS;
}

/*****************************************************************************
 Prototype      : SSA_UssNotifyRsp
 Description    : ����APP/AT�����Ķ�UnstructuredSS-Notify��������Ӧ,������ص�
                  ���뺯��, �������������ݷ���SS
 Input          : *para--UnstructuredSSReq�����Ĳ���
                  ucTi -- �����Ti
 Output         : ��
 Return Value   : ��
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
*****************************************************************************/
VOS_VOID  SSA_UssNotifyRsp(VOS_UINT8 ucTi)
{

    ST_SSP_MSG             stFacilityMsg;

    /*�������ݳ�ʼ��*/
    PS_MEM_SET(&stFacilityMsg, 0, sizeof(ST_SSP_MSG));

    /*ȷ��Ti����Ϣ����*/
    stFacilityMsg.ucCr = ucTi;
    stFacilityMsg.SspmsgCore.ucChoice = D_SMC_FACILITY_REQ;

    /*��װparameter֮���ͷ��*/
    if (SSA_SUCCESS != SSA_PackMsgHeader(&(stFacilityMsg.SspmsgCore.u.FacilityReq.Facility), VOS_NULL,
                                         TAF_SS_MSG_TYPE_FACILITY, ucTi, VOS_NULL, VOS_NULL))
    {
        SSA_LOG( WARNING_PRINT, "SSA_UssNotifyRsp:WARNING: Encode MsgHeader Error!");
        SSA_TiFree(ucTi);
        return;
    }

    /*��SS������Ϣ*/
    Taf_SsMsgReq(&stFacilityMsg);

    return;
}

/*****************************************************************************
 Prototype      : SSA_EraseCCEntryReq
 Description    : ����APP/AT�����ERASECC_ENTRY����,������صı��뺯��, ������
                  �������ݷ���SS
 Input          : *para--ERASECC_ENTRY�����Ĳ���
                  ucTi -- �����Ti
 Output         : ��
 Return Value   : �������
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.��    ��   : 2006��10��8��
    ��    ��   : luojian id:60022475
    �޸�����   : ���ⵥ��:A32D06583��SSA��ʱ�����Ƶ�SS

  3.��    ��   : 2010��3��1��
    ��    ��   : zhoujun /z40661
    �޸�����   : NAS R7Э�������޸ķ��͵������Version
  4.��    ��   : 2012��4��28��
    ��    ��   : f62575
    �޸�����   : DTS2012042601441,+CUSD=2��ʱ��δ�������
  5.��    ��   : 2013��5��6��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C��
  6.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  7.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
*****************************************************************************/
VOS_UINT32 SSA_EraseCCEntryReq(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                           *pMsg
)
{
    /*
    ʹ���µ���ڲ���ʵ��ԭ��������
    ����USSD��������̣�
    ����TI��ȡ���̣�
     */
    ST_SSP_MSG                          stRegisterMsg;
    VOS_UINT32                          ulRslt;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
    VOS_UINT8                           ucTi;
    TAF_SS_ERASECC_ENTRY_REQ_STRU      *pstEraseCc = VOS_NULL_PTR;

    /* ����USSDҵ�����������������SSҵ�� */
    if (VOS_TRUE != TAF_SSA_IsUssdStateIdle())
    {
        return TAF_ERR_BUSY_ON_USSD;
    }

    /* ��ȡ����ʹ�õ�Ti */
    if (SSA_SUCCESS != SSA_TiAlloc(ClientId, OpId, &ucTi))
    {
        SSA_LOG( WARNING_PRINT, "SSA_RegisterPasswordReq: RegisterPassword Ti alloc fail");
        return TAF_ERR_TI_ALLOC_FAIL;
    }

    pstEraseCc = (TAF_SS_ERASECC_ENTRY_REQ_STRU *)pMsg;
    /* Added by f62575 for V9R1 STK����, 2013-6-26, end */

    /*�������ݳ�ʼ��*/
    PS_MEM_SET(&stRegisterMsg, 0, sizeof(ST_SSP_MSG));

    /*ȷ��Ti����Ϣ����*/
    stRegisterMsg.ucCr = ucTi;
    stRegisterMsg.SspmsgCore.ucChoice = D_SMC_BEGIN_REQ;

    /*��MS�෢��EraseCCEntry�����Ĳ������ݽ��б���*/
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    ulRslt = SSA_EncodeEraseCCEntryReq(stRegisterMsg.SspmsgCore.u.BeginReq.Facility.Facility,
                                       (VOS_UINT8*)&(stRegisterMsg.SspmsgCore.u.BeginReq.Facility.ulCnt),
                                       pstEraseCc);
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    if (SSA_SUCCESS != ulRslt)
    {
        /*Ӧ�������������󣬷����ͷ�״̬��ǰTi������*/
        SSA_LOG( WARNING_PRINT, "SSA_EraseCCEntryReq:WARNING: Encode EraseCCEntryReq Error!");
        SSA_TiFree(ucTi);
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        /* ͳһ�����룬����ʧ�ܰ����������� */
        return TAF_ERR_PARA_ERROR;
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    }

    /*��װparameter֮���ͷ��*/
    if (SSA_SUCCESS != SSA_PackMsgHeader(&(stRegisterMsg.SspmsgCore.u.BeginReq.Facility), TAF_SS_ERASECC_ENTRY,
                                         TAF_SS_MSG_TYPE_REGISTER, ucTi, VOS_NULL, VOS_NULL))
    {
        SSA_LOG( WARNING_PRINT, "SSA_EraseCCEntryReq:WARNING: Encode MsgHeader Error!");
        SSA_TiFree(ucTi);
        return SSA_FAILURE;
    }

    /*�Ƿ�����SS version indicator,ĿǰERASECC_ENTRY����Ҫ��ֵΪ3��3����*/
    stRegisterMsg.SspmsgCore.u.BeginReq.OP_Sspversion = 1;
    stRegisterMsg.SspmsgCore.u.BeginReq.Sspversion.ulCnt = 1;
    stRegisterMsg.SspmsgCore.u.BeginReq.Sspversion.Sspversion[0] = 1;

    /*������ʱ�����ȴ������Ļظ�*/
    if (VOS_TRUE !=  TAF_SSA_StartTimer(TI_TAF_SSA_WAIT_NETWORK_RSP_TIMER,
                                        NAS_SSA_TIMER_LENGTH_WAIT_NETWORK_RSP,
                                        ucTi))
    {
        SSA_LOG( ERROR_PRINT, "SSA_RegisterIndProc:ERROR: VOS_StartRelTimer runs failed");
        SSA_TiFree(ucTi);
        return TAF_ERR_ERROR;
    }

    /*��SS������Ϣ*/
    Taf_SsMsgReq(&stRegisterMsg);

    /*��״̬���м��뵱ǰTi�������Ϣ*/
    gastSsaStatetable[ucTi].ucOperationCode = TAF_SS_ERASECC_ENTRY;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    gastSsaStatetable[ucTi].ucSsCode = pstEraseCc->SsCode;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, begin */
    /* Deleted by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, end */
    gastSsaStatetable[ucTi].ucState = SSA_USED;
    gastSsaStatetable[ucTi].ucMsgType = TAF_SS_MSG_TYPE_REGISTER;

    return SSA_SUCCESS;
}



/*****************************************************************************
 Prototype      : SSA_ReleaseComplete
 Description    : ����APP/AT������release���������κβ���
 Input          : *para--UnstructuredSSData�����Ĳ���
                  ucTi -- �����Ti
 Output         : ��
 Return Value   : �������
 Calls          : ---
 Called By      : --

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.��    ��   : 2012��4��28��
    ��    ��   : f62575
    �޸�����   : DTS2012042601441,+CUSD=2��ʱ��δ�������
  3.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  4.��    ��   : 2013��7��13��
    ��    ��   : l00208543
    �޸�����   : V9R1 STK������ʹ���º���TAF_SSA_GetUssdTi��ȡTI
  5.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����  :DTS2013082903019:֧��ss�ط�����

  6.��    ��   : 2014��5��26��
    ��    ��   : z00234330
    �޸�����   : dts2014050800110,app����cancel cusdʱ,���mm����û�н���,��Ҫ���ϲ㷢��abort֪ͨ
*****************************************************************************/
VOS_UINT32 SSA_ReleaseComplete(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                           *pMsg
)
{
    /*
    ʹ���µ���ڲ���ʵ��ԭ��������
    ����TI��ȡ���̣�
     */

    /* Added by l00208543 for V9R1 STK����, 2013-07-10, begin */
    VOS_UINT8                            ucTi;
    /* Added by l00208543 for V9R1 STK����, 2013-07-10, end */


    ST_SSP_MSG             stRelCmplMsg;

    /*�������ݳ�ʼ��*/
    PS_MEM_SET(&stRelCmplMsg, 0, sizeof(ST_SSP_MSG));

    /* Added by l00208543 for V9R1 STK����, 2013-07-10, begin */
    /* ��ȡTI */
    /* release������, û��USSD��ʵ����Ҫ�ͷţ���ֱ�ӷ��� */
    if (SSA_SUCCESS != TAF_SSA_GetUssdTi(&ucTi))
    {
        SSA_LOG( NORMAL_PRINT, "SSA_ReleaseComplete:WARNING: ReleaseComplete Get Ti fail");
        return TAF_ERR_TI_GET_FAIL;
    }
    /* Added by l00208543 for V9R1 STK����, 2013-07-10, end */


    /*ȷ��Ti����Ϣ����*/
    stRelCmplMsg.ucCr = ucTi;
    stRelCmplMsg.SspmsgCore.ucChoice = D_SMC_END_REQ;

    stRelCmplMsg.SspmsgCore.u.EndReq.OP_Facility = 0;

    stRelCmplMsg.SspmsgCore.u.EndReq.OP_SspTaCause = VOS_TRUE;
    stRelCmplMsg.SspmsgCore.u.EndReq.enSspTaCause  = EN_STC_NORMAL;

    /* Deleted by l00208543 for V9R1 STK����, 2013-07-10, begin */
    /* Deleted by l00208543 for V9R1 STK����, 2013-07-10, end */

    /*��SS������Ϣ*/
    Taf_SsMsgReq(&stRelCmplMsg);

    /* Added by l00208543 for V9R1 STK����, 2013-07-15, begin */
    /* Modified by z00161729 for V9R1 STK����, 2013-8-01, begin */
    /* ��ȡTI�ɹ���֪ͨ�ϲ�SS��release��Ϣ */
    if (MN_CLIENT_ALL != gastSsaStatetable[ucTi].ClientId)
    {
        SSA_ReportErrorEvent(gastSsaStatetable[ucTi].ClientId, gastSsaStatetable[ucTi].OpId, TAF_ERR_USSD_TERMINATED_BY_USER);
    }
    /* Modified by z00161729 for V9R1 STK����, 2013-8-02, end */
    /* Added by l00208543 for V9R1 STK����, 2013-07-15, end */

    /*�رռ�ʱ��*/
    TAF_SSA_StopAllTimer(ucTi);
    TAF_SSA_ClearBufferedMsg(ucTi);

    /*�ͷ�Ti*/
    SSA_TiFree(ucTi);

    return SSA_SUCCESS;
}

/* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
/*****************************************************************************
 �� �� ��  : TAF_SSA_IsSsStateIdle
 ��������  : �ж��Ƿ���SSҵ����ִ�У�����USSD��SSҵ��ĳ�ͻ���
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_TRUE:����IDLE̬����û��SSҵ�������У�
             VOS_FALSE:������IDLE̬������SSҵ�������У�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
*****************************************************************************/
VOS_UINT32 TAF_SSA_IsSsStateIdle(VOS_VOID)
{
    VOS_UINT32                          i;

    for (i = 0; i <= TAF_MAX_SSA_TI; i++)
    {
        /*index=7ʱ����*/
        if (TAF_MIDDLE_SSA_TI == i)
        {
            continue;
        }

        /* SS��USSDҵ��ʵ��δʹ�� */
        if (SSA_USED != gastSsaStatetable[i].ucState)
        {
            continue;
        }

        /* USSDҵ��ʵ�� */
        if ( (TAF_SSA_USSD_MO_CONN_STATE == gastSsaStatetable[i].ucUssdFlag)
          || (TAF_SSA_USSD_MT_CONN_STATE == gastSsaStatetable[i].ucUssdFlag) )
        {
            continue;
        }

        /* SSҵ��ʵ����ʹ�ã�����SSҵ��ǿ��� */
        return VOS_FALSE;
    }

    return   VOS_TRUE;
}
/* Added by f62575 for V9R1 STK����, 2013-6-26, end */

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, begin */
/*****************************************************************************
 �� �� ��  : TAF_SSA_ProcUssdUnstructuredMsg
 ��������  : ����AT��������TAF_MSG_PROCESS_USS_MSG��Ϣ
 �������  : ClientId    - APP/AT�ͻ��˱�ʶ
             OpId        -   ���б�ʶ
             pstSsReqMsg - TAF_MSG_PROCESS_USS_MSG��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_UINT32 : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��05��07��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C�������ɺ���
  2.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  3.��    ��   : 2013��7��13��
    ��    ��   : l00208543
    �޸�����   : V9R1 STK����
  4.��    ��   : 2013��8��1��
    ��    ��   : z00161729
    �޸�����   : V9R1 STK�����޸�
  5.��    ��   : 2013��12��30��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ
*****************************************************************************/
VOS_UINT32 TAF_SSA_ProcUssdUnstructuredMsg(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    VOS_UINT16                          usMsgType,
    VOS_VOID                           *pMsg
)
{
    VOS_UINT32                              ulRslt = TAF_ERR_NO_ERROR;
    TAF_SS_USS_RSP_STRU                     stSsRspMsg;
    VOS_UINT8                               ucTi;
    /* Added by l00208543 for V9R1 STK����, 2013-07-10, begin */
    TAF_SS_PROCESS_USS_REQ_STRU            *pstSsReqMsg = VOS_NULL_PTR;

    pstSsReqMsg = (TAF_SS_PROCESS_USS_REQ_STRU *)pMsg;
    /* Added by l00208543 for V9R1 STK����, 2013-07-10, end */

    /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-30, begin */
    /* USSD����Ϊ0�����������ﴦ�����ֱ���˳����Ƶ�SPM���� */
    /* Deleted by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-30, end */

    /* UE�����USSDҵ�� */
    if (VOS_TRUE == TAF_SSA_IsUssdStateIdle())
    {
        /* ��SSҵ����ִ�У�USSD������ִ�� */
        /*
         3GPP 11.14: 6.4.12 send USSD
         1.if the command is rejected because the ME is busy on a USSD transaction, the ME informs the UICC using TERMINAL RESPONSE
         (ME unable to process command - currently busy on USSD transaction);
         2.if the command is rejected because the ME is busy on a SS transaction, the ME informs the UICC using TERMINAL RESPONSE
         (ME unable to process command - currently busy on SS transaction).
         */
        /* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
        if (VOS_TRUE != TAF_SSA_IsSsStateIdle())
        {
            return TAF_ERR_BUSY_ON_SS;
        }
        /* Added by f62575 for V9R1 STK����, 2013-6-26, end */

        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        /* ��ȡ����ʹ�õ�Ti */
        if (SSA_SUCCESS != SSA_TiAlloc(ClientId, OpId,&ucTi))
        {   /*����Tiʧ��*/
            SSA_LOG( WARNING_PRINT, "Taf_SsaProc:WARNING: ProcessUnstructuredSSReq Ti alloc fail");
            return TAF_ERR_TI_ALLOC_FAIL;
        }

        /*����ProcessUnstructuredSSReq��������*/
        ulRslt = SSA_ProcessUnstructuredSSReq(ClientId, pstSsReqMsg, ucTi);
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

    }

    /* Ӧ����� */
    else
    {
        /* Modified by l00208543 for V9R1 STK����, 2013-07-10, begin */

        if (SSA_SUCCESS != TAF_SSA_GetUssdTi(&ucTi))
        {   /* GetTiʧ�� */
            SSA_LOG( WARNING_PRINT, "Taf_SsaProc:WARNING: UnstructuredSS-Req Get Ti fail");
            return TAF_ERR_TI_GET_FAIL;
        }

        /* ��������ȴ��ظ�״̬ʱ����response��Ϣ */
        if (TAF_SSA_USSD_MT_CONN_STATE != gastSsaStatetable[ucTi].ucUssdFlag)
        {
            SSA_LOG( WARNING_PRINT, "Taf_SsaProc:WARNING: UnstructuredSS-Req Get Ti fail");
            return TAF_ERR_BUSY_ON_USSD;
        }

        /* ����stSsRspMsg */
        PS_MEM_SET(&stSsRspMsg, 0, sizeof(TAF_SS_USS_RSP_STRU));
        stSsRspMsg.DataCodeScheme = pstSsReqMsg->DatacodingScheme;
        stSsRspMsg.enCusdType     = pstSsReqMsg->enCusdType;
        stSsRspMsg.UssdStr        = pstSsReqMsg->UssdStr;

        /* ����UnstructuredSS-Req�������� */
        /* Modified by z00161729 for V9R1 STK����, 2013-7-25, begin */
        ulRslt = SSA_UnstructuredSSRsp(&stSsRspMsg, ucTi, ClientId, OpId);
        /* Modified by z00161729 for V9R1 STK����, 2013-7-25, end */

        /* Modified by l00208543 for V9R1 STK����, 2013-07-10, end */
    }

    /* ���¼�¼CUSD�Ƿ������ϱ���ȫ�ֱ��� */
    /* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
    if (TAF_ERR_NO_ERROR == ulRslt)
    {
        TAF_SSA_UpdateUssdRptStatus(pstSsReqMsg);
    }
    /* Added by f62575 for V9R1 STK����, 2013-6-26, end */

    return ulRslt;

}
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, end */

/*****************************************************************************
 �� �� ��  : Taf_SSA_ProcBufferedBeginReqMsg
 ��������  : 5s�ط���ʱ����ʱ�������begin req��Ϣ
 �������  : pMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��9��28��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  Taf_SSA_ProcBufferedBeginReqMsg(ST_SSP_MSG *pMsg)
{
    /*����������*/
    if (VOS_NULL_PTR == pMsg)
    {
        TAF_PRINT(TAF_TAFM, ERROR_PRINT, "Taf_SSA_ProcBufferedBeginReqMsg:Input pointer p is null");
        return;
    }
    if ((pMsg->ucCr > (TAF_MIDDLE_SSA_TI))
     && (pMsg->ucCr <= TAF_MAX_SSA_TI))
    {
        /*Cr��Χ��8-14,ת����128-134*/
        pMsg->ucCr += 120;
    }

    pMsg->ucRedialFlg   = VOS_TRUE;

    /*����Э��ջ�ӿ�*/
    Ss_RcvSsaMsg(pMsg);
    return;
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
