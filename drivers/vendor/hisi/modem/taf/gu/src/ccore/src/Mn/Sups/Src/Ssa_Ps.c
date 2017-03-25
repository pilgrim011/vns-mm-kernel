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
  2. Date:2006-02-25
     Author: h44270
     Modification: ���ⵥ��:A32D02143
  3. Date:2006-04-11
     Author: h44270
     Modification: ���ⵥ��:A32D03014
  4. Date:2006-04-04
     Author: liuyang id:48197
     Modification: ���ⵥ��:A32D01738
  5. Date:2006-10-18
     Author: d49431
     Modification: ���ⵥ��:A32D06608
  6. Date:2006-11-08
     Author: d49431
     Modification: ���ⵥ��:A32D07063
  7. Date:2006-11-23
     Author: d49431
     Modification: ���ⵥ��:A32D07452
  8. Date:2006-12-26
     Author: d49431
     Modification: ���ⵥ��:A32D07990
  9. Date:2007-01-19
     Author: h44270
     Modification: ���ⵥ��:A32D08448
 10. Date:2007-04-18
     Author: l60827
     Modification: ���ⵥ��:A32D10439
 11. Date:2007-05-30
     Author: d49431
     Modification: ���ⵥ��:A32D11329
 12. Date:2008-07-23
     Author: l00130025
     Modification: ���ⵥ��:AT2D04595
************************************************************************/


#include "Ssa_Define.h"
#include "Taf_Tafm_Remote.h"
#include "Taf_Common.h"
#include "Taf_Ssa_DecodeDef.h"
#include "Taf_Ssa_EncodeDef.h"
#include "MnComm.h"
#include "SsDef.h"
#include "SsInclude.h"
/* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, begin */
#include "TafClientApi.h"
/* Modified by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-11-04, end */
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, begin */
#include "TafSdcLib.h"
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-3, end */
#include "TafStdlib.h"

#include "Ssa_Define.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_SSA_PS_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

/*lint -save -e958 */

/*****************************************************************************
 Prototype      : SSA_DecodeUssdDataCodeScheme
 Description    : ��TAFM����������SSģ�����Ϣ��Ȼ����ò�ͬ�ĺ�������ͬ������
                  SS����Ϣ
 Input          : *pMsg--������ִ�
 Output         : ��
 Return Value   : ��
 Calls          : SSA_RegisterInd
                  SSA_FacilityInd
                  SSA_RelCompleteInd
 Called By      : Taf_PsMsgProc

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
    ���÷�ʽSSA_DealMsgFromSS(&pPsMsg->u.SsMsg)
    Taf_Tafm_Ps.c�е��ã�ԭ����Ԥ��
  2.��    ��   :2013��9��10��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
*****************************************************************************/
VOS_VOID SSA_DealMsgFromSS(ST_SSP_MSG  *pMsg)
{
    /*����������,Ϊ�յĻ�����*/
    if (VOS_NULL_PTR == pMsg)
    {
        SSA_LOG(ERROR_PRINT, "SSA_DealMsgFromSS:ERROR: pMsg is NULL");
        return;

    }

    /*��������SS��������Ϣ��ST_BEGIN_IND,ST_SSP_MSGS_FACILITY_IND,ST_END_IND*/
    switch( pMsg->SspmsgCore.ucChoice )
    {
        case D_SMC_BEGIN_IND:
             SSA_RegisterIndProc(pMsg);
             break;

        case D_SMC_FACILITY_IND:
             SSA_FacilityIndProc(pMsg);
             break;

        case D_SMC_END_IND:
             SSA_RelCompleteIndProc(pMsg);
             break;

        case SSA_SS_CS_CONN_IND:
             TAF_SSA_RcvSsCsConnInd(pMsg);

        default:
             SSA_LOG(WARNING_PRINT, "SSA_DealMsgFromSS:WARNING: Receive Msg is Unknow");
             return;
    }

    return;
}

/*****************************************************************************
 Prototype      : SSA_RegisterIndProc
 Description    : ���ദ��,�յ�D_SMC_BEGIN_IND���͵���Ϣ,����Ӧ�Ľ��봦��
 Input          : *pMsg--������ִ�
 Output         : ��
 Return Value   : ��
 Calls          : ---
 Called By      : SSA_DealMsgFromSS

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.Date        : 2006-12-26
    Author      : d49431
    Modification: ���ⵥA32D07990
 3.��    ��   : 2012��1��12��
   ��    ��   : l00130025
   �޸�����   : DTS2012010400685,MT��USSD��SS�ı�����ʱ��ʹ����TAF��FID���û�����Ӧ,��ʱ�󣬴����ߵ�CCA�����̵��µ���ʹ�ÿ�ָ��
 4.��    ��   : 2012��4��28��
   ��    ��   : f62575
   �޸�����   : DTS2012042601441,+CUSD=2��ʱ��δ�������
 5.��    ��   : 2012��5��26��
   ��    ��   : f62575
   �޸�����   : DTS2012052502550,������ϱ��¼�Я������,�����ϱ��ַ���+CUSD��<str>�ֶ���ʾΪ��
 6.��    ��   : 2013��01��09��
   ��    ��   : l00198894
   �޸�����   : DTS2013010907160: SSҵ���쳣����InvokeID��д����
 7.��    ��   : 2013��5��6��
   ��    ��   : s00217060
   �޸�����   : �����ϱ�AT�������������C��
 8.��    ��   : 2013��6��17��
   ��    ��   : s00217060
   �޸�����   : V9R1_SVLTE
 9.��    ��   : 2013��8��01��
   ��    ��   : z00161729
   �޸�����   : V9R1 STK�����޸�
10.��    ��   : 2013��08��19��
   ��    ��   : l00198894
   �޸�����   : V9R1 ���ſ�����Ŀ����MTC�ϱ�CS��ҵ��״̬
 11.��    ��  :2013��9��12��
    ��    ��  :z00161729
    �޸�����  :DTS2013082903019:֧��ss�ط�����
*****************************************************************************/
VOS_VOID SSA_RegisterIndProc(ST_SSP_MSG  *pMsg)
{
    /* VOS_UINT8                                 ucComponetTag; */
    VOS_UINT32                                  ulRslt = SSA_SUCCESS;
    ST_BEGIN_IND                                *pBeginInd;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU          *pstSsEvent;
    VOS_UINT8                                   ucRejectCode;

    pstSsEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_SS, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
    if (VOS_NULL_PTR == pstSsEvent)
    {
        SSA_LOG( ERROR_PRINT, "SSA_RegisterIndProc:ERROR: Alloc Mem Fail");
        return;
    }


    /*���¼��ϱ������ݸ���ֵ*/
    PS_MEM_SET(pstSsEvent, 0 , sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    /*��ȡ��Ϣ����*/
    pBeginInd = &(pMsg->SspmsgCore.u.BeginInd);

    /*��ȡti����Ϣ����,Tiֵ���ü��,��SSģ���Ѿ�������Ӧ�ļ��*/
    gucCurrentTi = pMsg->ucCr;
    if (gucCurrentTi <= TAF_MIDDLE_SSA_TI)
    {
        SSA_LOG(WARNING_PRINT, "SSA_FacilityIndProc:WARNING: Ti Value beyond range");
        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
        return;
    }

    gastSsaStatetable[gucCurrentTi].ucMsgType = TAF_SS_MSG_TYPE_REGISTER;

    /*componet���ֽ���*/
    ulRslt = SSA_DecodeComponent(pstSsEvent, pBeginInd->Facility.Facility);

    if (SSA_SUCCESS == ulRslt)
    {
        switch (pstSsEvent->SsEvent)
        {
            /*TAF_SS_FORWARDCHECKSS_INDICATION�¼��ϱ���APP/AT��ֱ���ͷ�*/
            #if 0
            case TAF_SS_EVT_FORWARDCHECKSS_INDICATION:
                TAF_SsEventReport(&StEvent);
                SSA_ReleaseComplete(gucCurrentTi + 120, VOS_NULL);
                break;
            #endif
            /*TAF_SS_USS_NOTIFY�¼��ϱ���APP/AT��ظ������*/
            case TAF_SS_EVT_USS_NOTIFY_IND:
                if (SSA_USED == SSA_TiIdle())
                {
                    gastSsaStatetable[gucCurrentTi].ucState = SSA_USED;

                    /* �˴����쳣��֧����ucState��ΪSSA_USED��������������ΪSSA_IDLE��
                        ���Բ���Ҫ����һ��CS���SSҵ���Ƿ���ڵı�־ */

                    SSA_ReturnError(TAF_ERR_SS_USSD_BUSY,
                                    gucCurrentTi,
                                    TAF_SS_MSG_TYPE_RLCOMPLETE,
                                    VOS_NULL);

                    gastSsaStatetable[gucCurrentTi].ucState = SSA_IDLE;

                    PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
                    return;
                }
                TAF_SsEventReport(pstSsEvent);

                gastSsaStatetable[gucCurrentTi].ucState = SSA_USED;

                /* û�е���SSA_TiAlloc��������Ҫ������һ��CS���SSҵ���Ƿ���ڵı�־ */
                TAF_SDC_SetCsSsSrvExistFlg(VOS_TRUE);

                /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
                /* ��MTCģ���ϱ���ǰCS��ҵ��״̬ */
                TAF_SendMtcCsSrvInfoInd();
#endif
                /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, end */

                SSA_UssNotifyRsp(gucCurrentTi);

                break;
            case TAF_SS_EVT_USS_REQ_IND:
                /*������ʱ��,�ɹ�,�¼��ϱ���APP/AT,��ʧ����֪ͨ�����,����*/

                if (VOS_TRUE !=  TAF_SSA_StartTimer(TI_TAF_SSA_WAIT_APP_RSP_TIMER,
                                                    NAS_SSA_TIMER_LENGTH_WAIT_APP_RSP,
                                                    gucCurrentTi))

                {
                    gastSsaStatetable[gucCurrentTi].ucState = SSA_USED;

                    /* �˴����쳣��֧����ucState��ΪSSA_USED��������������ΪSSA_IDLE��
                        ���Բ���Ҫ����һ��CS���SSҵ���Ƿ���ڵı�־ */

                    SSA_ReturnError(TAF_ERR_SS_SYSTEM_FAILURE,
                                    gucCurrentTi,
                                    TAF_SS_MSG_TYPE_FACILITY,
                                    VOS_NULL);

                    gastSsaStatetable[gucCurrentTi].ucState = SSA_IDLE;

                    SSA_LOG(ERROR_PRINT, "SSA_RegisterIndProc:ERROR: VOS_StartRelTimer runs failed");
                    PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
                    return;
                }
                TAF_SsEventReport(pstSsEvent);
                /* Added by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, begin */
                gastSsaStatetable[gucCurrentTi].ucUssdFlag  = TAF_SSA_USSD_MT_CONN_STATE;
                /* Added by s00217060 for �����ϱ�AT�������������C��, 2013-5-6, end */
                gastSsaStatetable[gucCurrentTi].ucState     = SSA_USED;

                /* û�е���SSA_TiAlloc��������Ҫ������һ��CS���SSҵ���Ƿ���ڵı�־ */
                TAF_SDC_SetCsSsSrvExistFlg(VOS_TRUE);

                /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, begin */
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
                /* ��MTCģ���ϱ���ǰCS��ҵ��״̬ */
                TAF_SendMtcCsSrvInfoInd();
#endif
                /* Added by l00198894 for V9R1 ���ſ���, 2013/08/19, end */

                break;

           default:
                SSA_LOG(WARNING_PRINT, "SSA_RegisterIndProc:WARNING: wrong operation type");
                PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
                return;
        }
    }
    else
    {
        /*���ݷ��صĴ�����Ϣ���ظ������,ForwardCheckSS-Indication������Ϣ������Release Complete*/
        #if 0
        if (TAF_SS_EVT_FORWARDCHECKSS_INDICATION == StEvent.SsEvent)
        {
            SSA_ReturnReject((VOS_UINT8)ulRslt, gucCurrentTi + 120, TAF_SS_MSG_TYPE_RLCOMPLETE, NULL);
        }
        else
        #endif
        {
            switch(ulRslt)
            {
                case TAF_ERR_SS_USSD_BUSY:

                    gastSsaStatetable[gucCurrentTi].ucState = SSA_USED;

                    /* �˴��ǰ�ucState��ΪSSA_USED��������������ΪSSA_IDLE��
                        ���Բ���Ҫ����һ��CS���SSҵ���Ƿ���ڵı�־ */

                    SSA_ReturnError((VOS_UINT16)ulRslt, gucCurrentTi, TAF_SS_MSG_TYPE_RLCOMPLETE, VOS_NULL);

                    gastSsaStatetable[gucCurrentTi].ucState = SSA_IDLE;

                    SSA_LOG(WARNING_PRINT, "SSA_RegisterIndProc:WARNING: send error ussd busy");
                    break;
                case TAF_ERR_SS_UNKNOWN_ALPHABET:
                case TAF_ERR_SS_UNEXPECTED_DATA_VALUE:

                    gastSsaStatetable[gucCurrentTi].ucState = SSA_USED;

                    /* �˴���ucState��ΪSSA_USED��������������ΪSSA_IDLE��
                        ���Բ���Ҫ����һ��CS���SSҵ���Ƿ���ڵı�־ */

                    SSA_ReturnError((VOS_UINT16)ulRslt, gucCurrentTi, TAF_SS_MSG_TYPE_FACILITY, VOS_NULL);

                    gastSsaStatetable[gucCurrentTi].ucState = SSA_IDLE;

                    SSA_LOG(WARNING_PRINT, "SSA_RegisterIndProc:WARNING: send error");
                    break;

                case TAF_SS_REJ_INVALID_MANDATORY_IE:

                    gastSsaStatetable[gucCurrentTi].ucState = SSA_USED;

                    /* �˴���ucState��ΪSSA_USED��������������ΪSSA_IDLE��
                        ���Բ���Ҫ����һ��CS���SSҵ���Ƿ���ڵı�־ */

                    SSA_ReturnError(0, gucCurrentTi, TAF_SS_MSG_TYPE_RLCOMPLETE, SS_CAUSE_INVALID_MANDATORY_IE);

                    gastSsaStatetable[gucCurrentTi].ucState = SSA_IDLE;

                    SSA_LOG(WARNING_PRINT, "SSA_RegisterIndProc:WARNING: No Invoke Id");
                    break;

                default:
                    ucRejectCode = 0x20|(ulRslt & 0x0f);
                    SSA_ReturnReject(ucRejectCode, gucCurrentTi, TAF_SS_MSG_TYPE_FACILITY, VOS_NULL);
                    SSA_LOG(WARNING_PRINT, "SSA_RegisterIndProc:WARNING: send reject");
                    break;
            }
        }
    }

    PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
    return;
}

/*****************************************************************************
 Prototype      : SSA_FacilityIndProc
 Description    : ���ദ��,�յ�D_SMC_FACILITY_IND���͵���Ϣ,����Ӧ�Ľ��봦��
 Input          : *pMsg--������ִ�
 Output         : ��
 Return Value   : ��
 Calls          : ---
 Called By      : SSA_DealMsgFromSS

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2. Date:  2008-07-23
     Author: l00130025
     Modification: ���ⵥ��:AT2D04595
 3.��    ��   : 2012��5��26��
   ��    ��   : f62575
   �޸�����   : DTS2012052502550,������ϱ��¼�Я������,�����ϱ��ַ���+CUSD��<str>�ֶ���ʾΪ��
  4.��    ��   : 2013��05��06��
    ��    ��   : f62575
    �޸�����   : SS FDN&Call Control��Ŀ��SS�������Ƶ�SSģ��
                 �¼�����ΪTAF_SS_EVT_GET_PASSWORD_IND��������ڱ������룬
                 ��ֱ�ӻظ������򣬴�ӡ�쳣���˳�����������ҵ�������������ɣ�
  5.��    ��   : 2013��8��6��
    ��    ��   : z00161729
    �޸�����   : V9R1 STK�����޸�
  6.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
*****************************************************************************/
VOS_VOID SSA_FacilityIndProc(ST_SSP_MSG  *pMsg)
{
    /* VOS_UINT8                                    ucComponetTag; */
    VOS_UINT32                                   ulRslt = SSA_SUCCESS;
    ST_SSP_MSGS_FACILITY_IND                     *pFacilityInd;
    TAF_SS_GETPWD_RSP_STRU                       stPara;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU           *pstSsEvent;
    VOS_UINT8                                    ucRejectCode;

    pstSsEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_SS, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
    if (VOS_NULL_PTR == pstSsEvent)
    {
        SSA_LOG( ERROR_PRINT, "SSA_FacilityIndProc:ERROR: Alloc Mem Fail");
        return;
    }


    /*���¼��ϱ������ݸ���ֵ*/
    PS_MEM_SET(pstSsEvent, 0 , sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    /*��ȡ��Ϣ����*/
    pFacilityInd = &(pMsg->SspmsgCore.u.FacilityInd);

    /*��ȡti����Ϣ����*/
    gucCurrentTi = pMsg->ucCr;
    if ((gucCurrentTi > TAF_MAX_SSA_TI) || (gucCurrentTi == TAF_MIDDLE_SSA_TI))
    {
        SSA_LOG(WARNING_PRINT, "SSA_FacilityIndProc:WARNING: Ti Value beyond range");
        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
        return;
    }

    gastSsaStatetable[gucCurrentTi].ucMsgType = TAF_SS_MSG_TYPE_FACILITY;

    /*���TI��ֵ�Ƿ���ȷ,Tiֵ����ȷ�Ļ�,����,��ӡwarning��Ϣ*/
    ulRslt = SSA_GetIdByTi(&(pstSsEvent->ClientId), &(pstSsEvent->OpId), gucCurrentTi);
    if (SSA_FAILURE == ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_FacilityIndProc:WARNING: Invalid Ti Value");
        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
        return;
    }

    /*componet���ֽ���*/
    ulRslt = SSA_DecodeComponent(pstSsEvent, pFacilityInd->Facility.Facility);

    if (SSA_SUCCESS == ulRslt)
    {
        /*�������Ҫ��ȡ����,����ǰ״̬�����Ƿ��Ѿ�������ز���������,���еĻ�,
        ����ص����뷢�͸������*/
        if (TAF_SS_EVT_GET_PASSWORD_IND == pstSsEvent->SsEvent)
        {
            if (SSA_PASSWORD_VALID == gastSsaStatetable[gucCurrentTi].ucPwdFlag)
            {
                switch(pstSsEvent->GuidanceInfo)
                {
                    case TAF_SS_ENTER_PASSWORD:
                        PS_MEM_CPY(stPara.aucPwdStr, gastSsaStatetable[gucCurrentTi].aucOldPwdStr, 4);
                        break;
                    case TAF_SS_ENTER_NEW_PASSWORD:
                        PS_MEM_CPY(stPara.aucPwdStr, gastSsaStatetable[gucCurrentTi].aucNewPwdStr, 4);
                        break;
                    case TAF_SS_ENTER_NEW_PASSWORD_AGAIN:
                        PS_MEM_CPY(stPara.aucPwdStr, gastSsaStatetable[gucCurrentTi].aucNewPwdStrCnf, 4);
                        break;
                    default:
                        SSA_LOG(WARNING_PRINT, "SSA_FacilityIndProc: PASSWORD Type Error ");
                        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
                        return;
                }
                SSA_GetPasswordRsp(&stPara, gucCurrentTi);
                PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
                return;
            }
            else
            {
                SSA_LOG( ERROR_PRINT, "SSA_FacilityIndProc: NO network required password.");
                PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
                return;
            }
        }

        if ((TAF_SS_EVT_USS_REQ_IND != pstSsEvent->SsEvent)
         && (TAF_SS_EVT_USS_NOTIFY_IND != pstSsEvent->SsEvent)
         && (TAF_SS_EVT_PROCESS_USS_REQ_CNF != pstSsEvent->SsEvent))
        {
            SSA_ReturnError(0, gucCurrentTi, TAF_SS_MSG_TYPE_RLCOMPLETE, SS_CAUSE_MSG_NOT_COMPATIBLE_STATUS);
            SSA_LOG( ERROR_PRINT, "SSA_FacilityIndProc rcv wrong message");
            PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
            return;
        }

        if (TAF_SS_EVT_USS_NOTIFY_IND == pstSsEvent->SsEvent)
        {
            SSA_UssNotifyRsp(gucCurrentTi);
        }

        /*�رռ�ʱ��*/
        TAF_SSA_StopTimer(TI_TAF_SSA_WAIT_NETWORK_RSP_TIMER, gucCurrentTi);

        /* Modified by z00161729 for V9R1 STK����, 2013-8-6, begin */
        if (TAF_SS_EVT_USS_REQ_IND == pstSsEvent->SsEvent)
        {
            if (VOS_TRUE !=  TAF_SSA_StartTimer(TI_TAF_SSA_WAIT_APP_RSP_TIMER,
                                                NAS_SSA_TIMER_LENGTH_WAIT_APP_RSP,
                                                gucCurrentTi))
            {
                SSA_LOG(ERROR_PRINT, "SSA_FacilityIndProc:ERROR: VOS_StartRelTimer runs failed");
            }

            gastSsaStatetable[gucCurrentTi].ucUssdFlag  = TAF_SSA_USSD_MT_CONN_STATE;
        }
        /* Modified by z00161729 for V9R1 STK����, 2013-8-6, end */


        /*�¼��ϱ���APP/AT*/
        TAF_SsEventReport(pstSsEvent);
    }
    else
    {
        switch(ulRslt)
        {
            case TAF_ERR_SS_UNKNOWN_ALPHABET:
            case TAF_ERR_SS_UNEXPECTED_DATA_VALUE:
                SSA_ReturnError((VOS_UINT8)ulRslt, gucCurrentTi, TAF_SS_MSG_TYPE_FACILITY, VOS_NULL);
                SSA_LOG(WARNING_PRINT, "SSA_FacilityIndProc:WARNING: component error");
                break;
            default:
                if (((ulRslt >> 4) | 0x10) == 0x10)
                {
                    ucRejectCode = (VOS_UINT8)ulRslt;
                }
                else
                {
                    switch (gastSsaStatetable[gucCurrentTi].uComponenttype)
                    {
                        case TAF_SS_COMPONENT_TYPE_INVOKE:
                            ucRejectCode = 0x20|(ulRslt & 0x0f);
                            break;
                        case TAF_SS_COMPONENT_TYPE_RTRNRSLT:
                            ucRejectCode = 0x30|(ulRslt & 0x0f);
                            break;
                        case TAF_SS_COMPONENT_TYPE_RTRNERR:
                            ucRejectCode = 0x40|(ulRslt & 0x0f);
                            break;
                        default:
                            SSA_LOG(WARNING_PRINT, "SSA_FacilityIndProc:WARNING: Component Type Error");
                            PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
                            return;
                    }
                }
                SSA_ReturnReject(ucRejectCode, gucCurrentTi, TAF_SS_MSG_TYPE_FACILITY, VOS_NULL);
                SSA_LOG(WARNING_PRINT, "SSA_FacilityIndProc:WARNING: component reject");
                break;
        }
    }

    PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
    return;
}

/*****************************************************************************
 �� �� ��  : SSA_RelCompleteIndCauseProc
 ��������  : ����release complete��Ϣ��Cause���IE�Ĵ���
 �������  : pEndInd - �ϱ���release complete��Ϣ
 �������  : pstSsEvent -
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��04��01��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID SSA_RelCompleteIndCauseProc(
    ST_END_IND                                   *pEndInd,
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU           *pstSsEvent
)
{
    if (SSA_FIELD_EXIST == pEndInd->OP_Cause)
    {
        /*���޸�,���ݽṹ�Ѿ������仯*/
        /*pstEvent->stCause.ulCnt = pstEndInd->Cause.ulCnt;
        memcpy(pstEvent->stCause.Cause, pstEndInd->Cause.Cause, pstEndInd->Cause.ulCnt);
        */
        /*Cause ֵ��ĵ�һ���ֽ��Ǳ����׼���ڶ����ֽڲ���Cause��ֵ*/
        pstSsEvent->Cause = *(pEndInd->Cause.Cause + 1) & 0x7f;
        pstSsEvent->OP_Cause = SSA_FIELD_EXIST;
    }
    else
    {
        pstSsEvent->OP_Cause = SSA_FIELD_NOT_EXIST;
    }
}

/*****************************************************************************
 �� �� ��  : SSA_RelCompleteIndFacilityProc
 ��������  : ����release complete��Ϣ��Facility���ݵĴ���
 �������  : pEndInd - �ϱ���release complete��Ϣ
 �������  : pstSsEvent - �¼��ϱ������ݽṹ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��04��01��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
2.��    ��   : 2013��11��14��
  ��    ��   : z00161729
  �޸�����   : DTS2013111507527gcf 31.9.2.1����������ussd notify��ϢӦ�ù㲥�ϱ����յ�����release completeӦ���ϱ�cusd:2������0
*****************************************************************************/
VOS_UINT32 SSA_RelCompleteIndFacilityProc(
    ST_END_IND                                   *pEndInd,
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU           *pstSsEvent
)
{
    VOS_UINT32            ulRslt;

    VOS_UINT16                      usSysAppConfigType;

    usSysAppConfigType = TAF_SDC_GetAppCfgSupportType();

    ulRslt = SSA_SUCCESS;

    if (SSA_FIELD_EXIST == pEndInd->OP_Facility)
    {
        ulRslt = SSA_DecodeComponent(pstSsEvent, pEndInd->Facility.Facility);
    }
    else
    {
        pstSsEvent->SsEvent = SSA_GetRepEvtFromOpCode(gastSsaStatetable[gucCurrentTi].ucOperationCode);

        if ((TAF_SS_EVT_PROCESS_USS_REQ_CNF == pstSsEvent->SsEvent)
         || (TAF_SS_EVT_USS_REQ_IND == pstSsEvent->SsEvent)
         || ((TAF_SS_EVT_USS_NOTIFY_IND == pstSsEvent->SsEvent)
          && (SYSTEM_APP_ANDROID == usSysAppConfigType)))
        {
            pstSsEvent->SsEvent = TAF_SS_EVT_USS_RELEASE_COMPLETE_IND;
        }
        else if (TAF_SS_EVT_INTERROGATESS_CNF == pstSsEvent->SsEvent)
        {
            pstSsEvent->OP_Error = SSA_FIELD_EXIST;
            pstSsEvent->ErrorCode = TAF_ERR_ERROR;
        }
        else
        {
            ;
        }
        pstSsEvent->OpId = gastSsaStatetable[gucCurrentTi].OpId;
        pstSsEvent->ClientId = gastSsaStatetable[gucCurrentTi].ClientId;
    }

    return ulRslt;
}



/*****************************************************************************
 �� �� ��  : SSA_RelCompleteIndRtrnErrProc
 ��������  : ����return error�Ĵ���
 �������  : pstSsEvent - �¼��ϱ������ݽṹ
 �������  :
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��04��01��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID SSA_RelCompleteIndRtrnErrProc(
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU           *pstSsEvent
)
{
    /*���ݷ��صĴ�����Ϣ���������ϱ���Ϣ*/
    pstSsEvent->SsEvent = SSA_GetRepEvtFromOpCode(gastSsaStatetable[gucCurrentTi].ucOperationCode);
    if ((TAF_SS_EVT_PROCESS_USS_REQ_CNF == pstSsEvent->SsEvent)
        ||(TAF_SS_EVT_USS_REQ_IND == pstSsEvent->SsEvent)
        ||(TAF_SS_EVT_USS_NOTIFY_IND == pstSsEvent->SsEvent)
        ||(TAF_SS_EVT_USS_RELEASE_COMPLETE_IND == pstSsEvent->SsEvent))
    {
        pstSsEvent->SsEvent = TAF_SS_EVT_PROCESS_USS_REQ_CNF;
    }
    else
    {
        pstSsEvent->SsEvent = TAF_SS_EVT_ERROR;
    }

    TAF_SsEventReport(pstSsEvent);
    SSA_TiFree(gucCurrentTi);


}

/*****************************************************************************
 �� �� ��  : SSA_JudgeUssdNotCompatiblity
 ��������  : �ж���ǰ�Ƿ���USSD����������汾������
 �������  : ulOpRslt - �������
              pstSsEvent - �¼��ϱ������ݽṹ
 �������  : ��
 �� �� ֵ  : VOS_TRUE - USSD�汾�����粻����
              VOS_FALSE - �޲�������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��04��01��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL SSA_JudgeUssdNotCompatiblity(
    VOS_UINT32                                   ulOpRslt,
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU           *pstSsEvent
)
{
    if (((TAF_SS_REJ_UNRECOGNIZED_OPERATION == ulOpRslt)
           &&(VOS_NULL_PTR != gastSsaStatetable[gucCurrentTi].pstUssdBuf)
           &&(TAF_SS_PROCESS_USS_REQ == gastSsaStatetable[gucCurrentTi].ucOperationCode))
         ||((SSA_FIELD_EXIST == pstSsEvent->OP_Cause)
           &&(0x1d == pstSsEvent->Cause)
           &&(TAF_SS_PROCESS_USS_REQ == gastSsaStatetable[gucCurrentTi].ucOperationCode)
            ))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : SSA_RelCompleteIndDefaultProc
 ��������  : ����Release Complete��Ϣ��Ĭ�ϴ���
 �������  : pstSsEvent - �¼��ϱ������ݽṹ
 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��04��01��
    ��    ��   : h44270
    �޸�����   : �����ɺ���
  1.��    ��   : 2014��10��27��
    ��    ��   : l00198894
    �޸�����   : DTS2014092304850 ����������SSҵ��ɹ������ʧ��
*****************************************************************************/
VOS_VOID SSA_RelCompleteIndDefaultProc(
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU           *pstSsEvent
)
{
    /*���ݷ��صĴ�����Ϣ���������ϱ���Ϣ*/
    pstSsEvent->SsEvent = SSA_GetRepEvtFromOpCode(gastSsaStatetable[gucCurrentTi].ucOperationCode);
    if ((TAF_SS_EVT_PROCESS_USS_REQ_CNF == pstSsEvent->SsEvent)
        ||(TAF_SS_EVT_USS_REQ_IND == pstSsEvent->SsEvent)
        ||(TAF_SS_EVT_USS_NOTIFY_IND == pstSsEvent->SsEvent)
        ||(TAF_SS_EVT_USS_RELEASE_COMPLETE_IND == pstSsEvent->SsEvent))
    {
        pstSsEvent->SsEvent = TAF_SS_EVT_PROCESS_USS_REQ_CNF;
    }
    else if ( (TAF_SS_EVT_REGISTERSS_CNF == pstSsEvent->SsEvent)
           || (TAF_SS_EVT_ERASESS_CNF == pstSsEvent->SsEvent)
           || (TAF_SS_EVT_ACTIVATESS_CNF == pstSsEvent->SsEvent)
           || (TAF_SS_EVT_DEACTIVATESS_CNF == pstSsEvent->SsEvent) )
    {
        if ( (VOS_TRUE == pstSsEvent->OP_Cause)
          && (SS_CAUSE_NORMAL_CALL_CLEARING == pstSsEvent->Cause) )
        {
            /* ��������Я���˴���ԭ��ֵ16��SS�¼��������滻�¼����� */
        }
        else
        {
            pstSsEvent->SsEvent = TAF_SS_EVT_ERROR;
        }
    }
    else
    {
        pstSsEvent->SsEvent = TAF_SS_EVT_ERROR;
    }
    pstSsEvent->OP_ProblemCode = SSA_FIELD_EXIST;
    pstSsEvent->ProblemCode = TAF_ERR_ERROR;
    TAF_SsEventReport(pstSsEvent);
    SSA_TiFree(gucCurrentTi);

}

/*****************************************************************************
 �� �� ��  : SSA_RelCompleteIndProc
 ��������  : ���ദ��,�յ�D_SMC_END_IND���͵���Ϣ,����Ӧ�Ľ��봦��
 �������  : ST_SSP_MSG  *pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2005��8��15��
    ��    ��   : ��ë/00166186
    �޸�����   : �����ɺ���
  2.��    ��   : 2010��8��21��
    ��    ��   : ��ë/00166186
    �޸�����   : DTS2010081702586 �¹�����PHASE1����������
  3.��    ��   : 2010��11��18��
    ��    ��   : ��ë/00166186
    �޸�����   : PHASE1 ��͸������������޸�
  4.��    ��   : 2012��06��19��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��:DTS2012061505515��GCF����31.9.1.2ʧ�ܣ�ԭ��Ϊ�����ͷ�
                 ԭ��ֵΪUSSD�����ݷ�͸��ģʽ�£�UE�ط�PHASE1 ��USSD���ݲ���8BIT����
  5.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
  6.��    ��   :2013��9��12��
    ��    ��   :z00161729
    �޸�����   :DTS2013082903019:֧��ss�ط�����
  7.��    ��   : 2013��12��12��
    ��    ��   : l00198894
    �޸�����   : DTS2013121200068: GCF31.9.1.2 �������������Բ���
*****************************************************************************/
VOS_VOID SSA_RelCompleteIndProc(ST_SSP_MSG  *pMsg)
{
    VOS_UINT32                          ulRslt = SSA_SUCCESS;
    ST_END_IND                         *pEndInd;
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstSsEvent;
    TAF_SS_PROCESS_USSDATA_REQ_STRU     stProcDataReq;
    ST_SSP_MSG                          stSsStatusNty;

    pstSsEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_SS, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
    if (VOS_NULL_PTR == pstSsEvent)
    {
        SSA_LOG( ERROR_PRINT, "SSA_RelCompleteIndProc:ERROR: Alloc Mem Fail");
        return;
    }

    /*���¼��ϱ������ݸ���ֵ*/
    PS_MEM_SET(pstSsEvent, 0 , sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    /*��ȡ��Ϣ����*/
    pEndInd = &(pMsg->SspmsgCore.u.EndInd);

    /*��ȡti����Ϣ����*/
    gucCurrentTi = pMsg->ucCr;


    /*���TI��ֵ�Ƿ���ȷ,Tiֵ����ȷ�Ļ�,����,��ӡwarning��Ϣ*/
    ulRslt = SSA_GetIdByTi(&(pstSsEvent->ClientId), &(pstSsEvent->OpId), gucCurrentTi);
    if (SSA_FAILURE == ulRslt)
    {
        SSA_LOG(WARNING_PRINT, "SSA_RelCompleteIndProc:WARNING: Invalie Ti Value");
        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
        return;
    }


    if (VOS_TRUE == TAF_SSA_IsNeedSsRetry(gucCurrentTi, pEndInd->enSsaSsRelCause))
    {
        /* �����ط���ʱ�� */
        (VOS_VOID)TAF_SSA_StartTimer(TI_TAF_SSA_RETRY_INTERVAL_TIMER,
                           TAF_SSA_GetSsRetryIntervalTimerLen(), gucCurrentTi);

        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
        return;
    }

    gastSsaStatetable[gucCurrentTi].ucMsgType = TAF_SS_MSG_TYPE_RLCOMPLETE;


    /* ���������ʱ����������ֹͣ��ʱ�� */
    TAF_SSA_StopAllTimer(gucCurrentTi);
    TAF_SSA_ClearBufferedMsg(gucCurrentTi);

    PS_MEM_SET(&stSsStatusNty, 0, sizeof(ST_SSP_MSG));
    stSsStatusNty.ucCr                                  = pMsg->ucCr;
    stSsStatusNty.SspmsgCore.ucChoice                   = SSA_SS_STATUS_NTY;
    stSsStatusNty.SspmsgCore.u.stSsStatusNty.enSsStatus = SSA_SS_STATUS_SETUP_FAIL;

    /*��SS������Ϣ*/
    Taf_SsMsgReq(&stSsStatusNty);

    SSA_RelCompleteIndCauseProc(pEndInd, pstSsEvent);

    ulRslt = SSA_RelCompleteIndFacilityProc(pEndInd, pstSsEvent);

    /* ���USSD�����ݣ�����Ҫ����ProcessUnstructuredData������� */
    if (VOS_TRUE == SSA_JudgeUssdNotCompatiblity(ulRslt, pstSsEvent))
    {
        if ((0x00 == (gastSsaStatetable[gucCurrentTi].DatacodingScheme>> 4))
           ||(TAF_SS_7BIT_DATA_CODING == gastSsaStatetable[gucCurrentTi].DatacodingScheme))
        {
            if (VOS_TRUE != TAF_STD_AsciiNum2HexString(gastSsaStatetable[gucCurrentTi].pstUssdBuf->aucUssdStr,
                                   &(gastSsaStatetable[gucCurrentTi].pstUssdBuf->usCnt)))
            {
                SSA_LOG(WARNING_PRINT, "SSA_RelCompleteIndProc:WARNING: TAF_STD_AsciiNum2HexString fail");
            }

            SSA_Decode7bit(gastSsaStatetable[gucCurrentTi].pstUssdBuf,
                                   gastSsaStatetable[gucCurrentTi].DatacodingScheme);
        }

        PS_MEM_SET(&stProcDataReq, 0x00, sizeof(stProcDataReq));
        stProcDataReq.ucCnt = (VOS_UINT8)gastSsaStatetable[gucCurrentTi].pstUssdBuf->usCnt;
        PS_MEM_CPY(stProcDataReq.aucUserData,
                   gastSsaStatetable[gucCurrentTi].pstUssdBuf->aucUssdStr,
                   gastSsaStatetable[gucCurrentTi].pstUssdBuf->usCnt);

        /*����ProcessUnstructuredData��������*/
        ulRslt = SSA_ProcessUSSDataReq((TAF_SS_PROCESS_USSDATA_REQ_STRU*)&stProcDataReq,gucCurrentTi);
        if (SSA_SUCCESS != ulRslt)
        {
            SSA_LOG(WARNING_PRINT, "SSA_RelCompleteIndProc:WARNING: Can not encode UssdData");
            pstSsEvent->SsEvent = TAF_SS_EVT_ERROR;
            pstSsEvent->OP_Error = SSA_FIELD_EXIST;
            pstSsEvent->ErrorCode = TAF_ERR_ERROR;
            TAF_SsEventReport(pstSsEvent);
            SSA_TiFree(gucCurrentTi);
        }
        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
        return;
    }

    /* �����û��error��release complete�������ǲ�ѯ�����Ľ�������ϱ���� */
    if ( ( (SSA_SUCCESS == ulRslt)
        && (SSA_FIELD_NOT_EXIST == pstSsEvent->OP_Cause)
        && (SSA_FIELD_NOT_EXIST == pstSsEvent->OP_Error) /*<==A32D10439*/
        && (gastSsaStatetable[gucCurrentTi].uComponenttype != TAF_SS_COMPONENT_TYPE_REJECT))
      || (TAF_SS_EVT_INTERROGATESS_CNF == pstSsEvent->SsEvent)) /*<==A32D11329*/
    {
        /*Only in case there is no cause value, could SS send a positive event to TAF to indicate SUCCESS*/
        /*�¼��ϱ���APP/AT,�رռ�ʱ��*/
        TAF_SsEventReport(pstSsEvent);
        SSA_TiFree(gucCurrentTi);
        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
        return;
    }

    if (((SSA_SUCCESS == ulRslt)
      && (SSA_FIELD_NOT_EXIST == pstSsEvent->OP_Cause)
      && (SSA_FIELD_EXIST == pstSsEvent->OP_Error) ))
    {
        SSA_RelCompleteIndRtrnErrProc(pstSsEvent);
        PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
        return;
    }

    SSA_RelCompleteIndDefaultProc(pstSsEvent);
    PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);
    return;

}

/*****************************************************************************
 �� �� ��  : TAF_SSA_RcvSsCsConnInd
 ��������  : SSA_SS_CS_CONN_IND��Ϣ�Ĵ���
 �������  : *pstMsg - ��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��9��10��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_SSA_RcvSsCsConnInd(ST_SSP_MSG  *pstMsg)
{
    SSA_SS_CS_CONN_IND_STRU            *pstCsConnIndMsg = VOS_NULL_PTR;
    TAF_SSA_MSG_BUFF_STRU              *pstBuffMsg      = VOS_NULL_PTR;
    ST_SSP_MSG                          stSsStatusNty;

    pstCsConnIndMsg = (SSA_SS_CS_CONN_IND_STRU *)&(pstMsg->SspmsgCore.u.stCsConnInd);

    pstBuffMsg = TAF_SSA_GetBufferedMsg(pstMsg->ucCr);

    gastSsaStatetable[pstMsg->ucCr].enSsaState = pstCsConnIndMsg->enConnState;

    if ((VOS_TRUE == TAF_SSA_GetSsRetrySupportFlg())
     && (SSA_SS_CS_CONN_STATE_PRESENT == pstCsConnIndMsg->enConnState)
     && (VOS_TRUE == pstBuffMsg->bitOpBufferedBeginReqMsg))
    {
        TAF_SSA_StopTimer(TI_TAF_SSA_RETRY_PERIOD_TIMER, pstMsg->ucCr);
        TAF_SSA_StopTimer(TI_TAF_SSA_RETRY_INTERVAL_TIMER, pstMsg->ucCr);
        TAF_SSA_ClearBufferedMsg(pstMsg->ucCr);
    }

    PS_MEM_SET(&stSsStatusNty, 0, sizeof(ST_SSP_MSG));
    stSsStatusNty.ucCr                                  = pstMsg->ucCr;
    stSsStatusNty.SspmsgCore.ucChoice                   = SSA_SS_STATUS_NTY;
    stSsStatusNty.SspmsgCore.u.stSsStatusNty.enSsStatus = SSA_SS_STATUS_SETUP_SUCC;

    /*��SS������Ϣ*/
    Taf_SsMsgReq(&stSsStatusNty);

    return;
}

/*****************************************************************************
 �� �� ��  : SSA_IsSsRetryCause_CmSrvRej
 ��������  : ԭ��ֵ�Ƿ���Ҫ�ز�(CM_SRV_REJ)
 �������  : SSA_SS_REL_CAUSE_ENUM_UINT32:SSʧ��ԭ��ֵ
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
VOS_UINT32 SSA_IsSsRetryCause_CmSrvRej(
    SSA_SS_REL_CAUSE_ENUM_UINT32        enCause
)
{


    VOS_UINT8                           ucIndex;
    TAF_SSA_RETRY_CFG_STRU             *pstSsRetryCfg;

    pstSsRetryCfg = TAF_SSA_GetSsaRetryCfgInfo();

    for (ucIndex = 0; ucIndex < pstSsRetryCfg->ucSsRetryCmSrvRejCauseNum; ucIndex++)
    {
        if (enCause == pstSsRetryCfg->aucSsRetryCmSrvRejCause[ucIndex] + SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : SSA_IsSsRetryCause_CsfbSrvRej
 ��������  : ԭ��ֵ�Ƿ���Ҫ�ز�(CSFB_SRV_REJ)
 �������  : SSA_SS_REL_CAUSE_ENUM_UINT32:SSʧ��ԭ��ֵ
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
VOS_UINT32 SSA_IsSsRetryCause_CsfbSrvRej(
    SSA_SS_REL_CAUSE_ENUM_UINT32        enCause
)
{
    /* CSFBʧ�ܲ���Ҫ�ز�����NAS_MM_EndCsfbFlow��ԭ�������other cause����һ�� */

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : SSA_IsSsRetryCause_RrConnFail
 ��������  : ԭ��ֵ�Ƿ���Ҫ�ز�(RR_CONN_FAIL)
 �������  : SSA_SS_REL_CAUSE_ENUM_UINT32:SSʧ��ԭ��ֵ
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
VOS_UINT32 SSA_IsSsRetryCause_RrConnFail(
    SSA_SS_REL_CAUSE_ENUM_UINT32        enCause
)
{
    if ((SSA_SS_REL_CAUSE_RR_CONN_FAIL_IMMEDIATE_ASSIGN_REJECT          == enCause)
     || (SSA_SS_REL_CAUSE_RR_CONN_FAIL_ACCESS_BAR                       == enCause)
     || (SSA_SS_REL_CAUSE_RR_CONN_FAIL_T3122_RUNING                     == enCause)
     || (SSA_SS_REL_CAUSE_RR_CONN_FAIL_CURRENT_PROTOCOL_NOT_SUPPORT     == enCause)
     || (SSA_SS_REL_CAUSE_RR_CONN_FAIL_INVALID_UE_STATE                 == enCause)
     || (SSA_SS_REL_CAUSE_RR_CONN_FAIL_CELL_BARRED                      == enCause))
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}

/*****************************************************************************
 �� �� ��  : SSA_IsSsRetryCause_RrRel
 ��������  : ԭ��ֵ�Ƿ���Ҫ�ز�(RR_REL)
 �������  : SSA_SS_REL_CAUSE_ENUM_UINT32:SSʧ��ԭ��ֵ
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
    �޸�����   : DTS2015112307317:SSA_SS_REL_CAUSE_RR_REL_RL_FAILURE��������
*****************************************************************************/
VOS_UINT32 SSA_IsSsRetryCause_RrRel(
    SSA_SS_REL_CAUSE_ENUM_UINT32        enCause
)
{
    if ( (SSA_SS_REL_CAUSE_RR_REL_AUTH_REJ    == enCause)
      || (SSA_SS_REL_CAUSE_RR_REL_NAS_REL_REQ == enCause) )
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}

/*****************************************************************************
 �� �� ��  : SSA_IsSsRetryCause_CsfbLmmFail
 ��������  : ԭ��ֵ�Ƿ���Ҫ�ز�(CSFB_LMM_FAIL)
 �������  : SSA_SS_REL_CAUSE_ENUM_UINT32:SSʧ��ԭ��ֵ
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
VOS_UINT32 SSA_IsSsRetryCause_CsfbLmmFail(
    SSA_SS_REL_CAUSE_ENUM_UINT32        enCause
)
{
    /* CSFBʧ�ܲ���Ҫ�ز�����NAS_MM_EndCsfbFlow��ԭ�������other cause����һ�� */

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : SSA_IsSsRetryCause_MmInterErr
 ��������  : ԭ��ֵ�Ƿ���Ҫ�ز�(MM_INTER_ERR)
 �������  : SSA_SS_REL_CAUSE_ENUM_UINT32:SSʧ��ԭ��ֵ
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
VOS_UINT32 SSA_IsSsRetryCause_MmInterErr(
    SSA_SS_REL_CAUSE_ENUM_UINT32        enCause
)
{
    /* SSA_SS_REL_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL��GU��resume_indʱucCsResumeResultΪfail, GU������쳣��û��Ҫ���ز�
       SSA_SS_REL_CAUSE_MM_INTER_ERR_BACK_TO_LTE��CSFB��ϵͳʧ���ػ�LTE, MMC��ȥGU����������Ҫ�ز�
       SSA_SS_REL_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL SSA_SS_REL_CAUSE_MM_INTER_ERR_EST_SAPI3_FAIL�Ƕ��ŵ�ʧ��ԭ��ֵ��
       �������SS�����Ϊ���쳣������Ҫ�ز�
       SSA_SS_REL_CAUSE_MM_INTER_ERR_ECALL_INACTIVE ����Ҫ�ز� */

    switch (enCause)
    {
        /* cs LAU rej #12������NV������ҵ��ʱ�ᴥ�����������������ز� */
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_CS_ACCESS_BAR:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_CS_DETACH:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_CS_SIM_INVALID:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_NOT_SUPPORT_CS_CALL_S1_MODE_ONLY:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_RESUME_TO_GU_FAIL:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_TI_INVALID:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_WAIT_EST_CNF_TIME_OUT:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_CC_CONN_REQ_EXIST:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_UE_INVALID_STATE:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_WAIT_CC_REEST_TIME_OUT:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_SND_SAPI3_FAIL:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_EST_SAPI3_FAIL:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_ECALL_INACTIVE:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_REEST_FAIL:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_CC_REL_REQ:
        case SSA_SS_REL_CAUSE_MM_INTER_ERR_LTE_LIMITED_SERVICE:

            return VOS_FALSE;

        default:
            return VOS_TRUE;
    }
}

/*****************************************************************************
 �� �� ��  : SSA_IsSsRetryCause
 ��������  : ԭ��ֵ�Ƿ���Ҫ�ز�
 �������  : SSA_SS_REL_CAUSE_ENUM_UINT32:SSʧ��ԭ��ֵ
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
VOS_UINT32 SSA_IsSsRetryCause(
    SSA_SS_REL_CAUSE_ENUM_UINT32        enCause
)
{
    VOS_UINT32                          ulRslt;

    ulRslt  = VOS_TRUE;

    /* cm service reject */
    if ((enCause >= SSA_SS_REL_CAUSE_CM_SRV_REJ_BEGIN)
     && (enCause <= SSA_SS_REL_CAUSE_CM_SRV_REJ_END))
    {
        ulRslt = SSA_IsSsRetryCause_CmSrvRej(enCause);
    }

    /* CSFB Service reject */
    else if ((enCause >= SSA_SS_REL_CAUSE_CSFB_SRV_REJ_BEGIN)
          && (enCause <= SSA_SS_REL_CAUSE_CSFB_SRV_REJ_END))
    {
        ulRslt = SSA_IsSsRetryCause_CsfbSrvRej(enCause);
    }

    /* est_cnfʧ�ܣ���NAS_MM_IsAbleRecover_EstCnfFailResult�Ĵ����߼�����һ�� */
    else if ((enCause >= SSA_SS_REL_CAUSE_RR_CONN_FAIL_BEGIN)
          && (enCause <= SSA_SS_REL_CAUSE_RR_CONN_FAIL_END))
    {
        ulRslt = SSA_IsSsRetryCause_RrConnFail(enCause);

    }

    /* rel_ind, ���˼�Ȩ���ܣ�����ԭ��ֵ��NAS_MM_IsNeedCmServiceRetry_RelIndResult�Ĵ����߼�����һ�� */
    else if ((enCause >= SSA_SS_REL_CAUSE_RR_REL_BEGIN)
          && (enCause <= SSA_SS_REL_CAUSE_RR_REL_END))
    {
        ulRslt = SSA_IsSsRetryCause_RrRel(enCause);
    }

    /* ���˼�Ȩ���ܣ�����ԭ��ֵ��ʱ��Ϊ����Ҫ�ز� */
    else if ((enCause >= SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_BEGIN)
          && (enCause <= SSA_SS_REL_CAUSE_CSFB_LMM_FAIL_END))
    {
        ulRslt = SSA_IsSsRetryCause_CsfbLmmFail(enCause);
    }

    /* MM INTER ERR */
    else if ((enCause >= SSA_SS_REL_CAUSE_MM_INTER_ERR_BEGIN)
          && (enCause <= SSA_SS_REL_CAUSE_MM_INTER_ERR_END))
    {
        ulRslt = SSA_IsSsRetryCause_MmInterErr(enCause);
    }

    else
    {
        /* �����������Ҫ�ز� */
        ulRslt  = VOS_FALSE;
    }

    return ulRslt;
}

/*****************************************************************************
 �� �� ��  : TAF_SSA_IsNeedSsRetry
 ��������  : �ж��Ƿ�����ss�ط�����
 �������  : ucTi       - transation id
             enRelCause - �����ͷ�ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ��Ҫss�ط�
             VOS_FALSE - ����Ҫss�ط�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��12��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SSA_IsNeedSsRetry(
    VOS_UINT8                           ucTi,
    SSA_SS_REL_CAUSE_ENUM_UINT32        enRelCause
)
{
    VOS_UINT32                          ulSsRetryPeriodRemainLen;
    VOS_UINT32                          ulSsRetryIntervalLen;
    VOS_UINT32                          ulSsRetrySupportFlg;
    VOS_UINT32                          ulIsSsRetryCause;

    ulSsRetryPeriodRemainLen = 0;
    ulSsRetrySupportFlg      = TAF_SSA_GetSsRetrySupportFlg();
    ulSsRetryIntervalLen     = TAF_SSA_GetSsRetryIntervalTimerLen();

    if (TAF_SSA_TIMER_STATUS_RUNING == TAF_SSA_GetTimerStatus(TI_TAF_SSA_RETRY_PERIOD_TIMER, ucTi))
    {
        ulSsRetryPeriodRemainLen = TAF_SSA_GetTimerRemainLen(TI_TAF_SSA_RETRY_PERIOD_TIMER, ucTi);
    }

    ulIsSsRetryCause    = SSA_IsSsRetryCause(enRelCause);

    if ((VOS_TRUE == ulSsRetrySupportFlg)
     && (TAF_SSA_STATE_CONN_PENDING == gastSsaStatetable[ucTi].enSsaState)
     && (VOS_TRUE == ulIsSsRetryCause)
     && (ulSsRetryPeriodRemainLen > ulSsRetryIntervalLen))
    {
        /* �����ط�����:
           1.ss�ط�nv���
           2.״̬�ڵ����ӽ���
           3.�����ͷ�ԭ��ֵ�����ؽ�������ΪSSA_SS_REL_CAUSE_MM_REJ_OTHER_CAUSES��SSA_SS_REL_CAUSE_AS_REJ_OTHER_CAUSES
           4.ʣ��ʱ������ؽ����ʱ�� */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



/*lint -e429 -e830*/

/*****************************************************************************
 Prototype      : TAF_SsEventReport
 Description    : �¼��ϱ����ܺ���,�����޹ز����Ĳ�������APP
 Input          : *pMsg--������ִ�
 Output         : ��
 Return Value   : ��
 Calls          : ---
 Called By      : SSA_DealMsgFromSS

 History        : ---
  1.Date        : 2005-08-15
    Author      : ---
    Modification: Created function
  2.Date:2006-02-25
    Author: h44270
    Modification: ���ⵥ��:A32D02143
  3.Date:2010-04-11
    Author: S62952
    Modification: ���ⵥ��:AT2D18353
  4.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
5.��    ��   : 2013��11��14��
  ��    ��   : z00161729
  �޸�����   : DTS2013111507527:gcf 31.9.2.1����������ussd notify��ϢӦ�ù㲥�ϱ����յ�����release completeӦ���ϱ�cusd:2������0
  6.��    ��   : 2014��5��7��
    ��    ��   : w00242748
    �޸�����   : DTS2014050602822:STK����绰������BCD�������󣬵��µ绰û��������
                 STK���͵�USSD����������Ҫ�û�ȷ��ʱ��δ��AT�ϱ���ȷ�ϡ�
*****************************************************************************/
VOS_VOID TAF_SsEventReport (TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *pEvent)
{
    VOS_UINT32                          ulOamRcvPid;

    if (TAF_SS_MSG_TYPE_REGISTER == gastSsaStatetable[gucCurrentTi].ucMsgType)
    {
        if (1 == pEvent->OP_Error )
        {
            /*�ڳ�������£����㲥�ϱ�,����״̬���м�¼ClientId��OpId*/
            pEvent->OpId = gucCurrentTi + 120;
            gastSsaStatetable[gucCurrentTi].ClientId = pEvent->ClientId;
            gastSsaStatetable[gucCurrentTi].OpId = pEvent->OpId;

            MN_SendClientEvent(pEvent->ClientId,
                MN_CALLBACK_SS,
                pEvent->SsEvent,
                pEvent);

        }
        else
        {
            /*��REGISTER��Ϣ�����£���APP���͹㲥��Ϣ,����״̬���м�¼ClientId��OpId*/
            pEvent->ClientId = MN_CLIENT_ALL;
            pEvent->OpId = gucCurrentTi + 120;
            gastSsaStatetable[gucCurrentTi].ClientId = pEvent->ClientId;
            gastSsaStatetable[gucCurrentTi].OpId = pEvent->OpId;

            MN_SendClientEvent(pEvent->ClientId,
                MN_CALLBACK_SS,
                pEvent->SsEvent,
                pEvent);
        }

    }
    else
    {
        ulOamRcvPid = MN_GetPidFromClientId(pEvent->ClientId);

        if ( MAPS_STK_PID == ulOamRcvPid )
        {
            pEvent->ClientId = MN_CLIENT_ALL;
            pEvent->OpId = gucCurrentTi + 120;
            gastSsaStatetable[gucCurrentTi].ClientId = pEvent->ClientId;
            gastSsaStatetable[gucCurrentTi].OpId = pEvent->OpId;
        }

        MN_SendClientEvent(pEvent->ClientId,
            MN_CALLBACK_SS,
            pEvent->SsEvent,
            pEvent);
    }
    return;
}
/*lint +e429 +e830*/

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
