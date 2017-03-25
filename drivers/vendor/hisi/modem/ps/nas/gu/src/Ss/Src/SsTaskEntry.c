/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsTaskEntry.c
  Description  : SS TASK����
  Function List:
      1.  Ss_TaskEntry_T    SSģ��TASK��ڴ���
      2.  Ss_TaskInit       TASK ��ʼ������
      3.  WuepsSsPidInit    WUEPS SS PID�ĳ�ʼ������
  History:
      1.  ��־�� 2004.03.08   �°�����
      2.  ��  �� 2006.11.07   ���ⵥA32D07063
*******************************************************************************/

#include "SsInclude.h"
#include "MnComm.h"
#include "NVIM_Interface.h"

/* Added by l00167671 for NV�����Ŀ , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV�����Ŀ , 2013-05-17, end*/
#include "TafSdcLib.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_SS_TASKENTRY_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/


/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : SSA_ReportErrorEvent
 ��������  : �����USIM������FDN�������Ϣ
 �������  : pstMsg - �յ�����Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��23��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK�������޸���Ϣ�ַ�����
*****************************************************************************/
VOS_VOID SSA_ReportErrorEvent(
    VOS_UINT16                          ClientId,
    VOS_UINT8                           OpId,
    TAF_SS_ERROR                        ErrorCode
)
{
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstSsEvent = VOS_NULL_PTR;

    pstSsEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_SS,
                            sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
    if (VOS_NULL_PTR == pstSsEvent)
    {
        SSA_LOG( ERROR_PRINT, "TAF_SSA_ReportEvtError: Alloc Mem Fail");
        return;
    }

    /* �����¼���OP���ʼ�� */
    PS_MEM_SET(pstSsEvent, 0, sizeof(VOS_UINT32));
    pstSsEvent->OP_Error = VOS_TRUE;

    pstSsEvent->SsEvent  = TAF_SS_EVT_ERROR;

    pstSsEvent->ClientId = ClientId;
    pstSsEvent->OpId     = OpId;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

    pstSsEvent->ErrorCode = ErrorCode;

    TAF_SsEventReport(pstSsEvent);

    PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);

    return;
}


/*****************************************************************************
 �� �� ��  : SSA_ReportUssdDataSnd
 ��������  : �ϱ�TAF_SS_EVT_USSD_DATA_SND�¼���AT
 �������  : ucTi   Tiֵ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��02��23��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID SSA_ReportUssdDataSndEvent(VOS_UINT8 ucTi)
{
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstSsEvent;

    pstSsEvent = (TAF_SS_CALL_INDEPENDENT_EVENT_STRU *)PS_MEM_ALLOC(WUEPS_PID_SS,
                                                                    sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));
    if (VOS_NULL_PTR == pstSsEvent)
    {
        SSA_LOG(ERROR_PRINT, "SSA_ReportUssdDataSndEvent:ERROR: Alloc Mem Fail");
        SSA_TiFree(ucTi);
        return;
    }

    /*���¼��ϱ������ݸ���ֵ*/
    PS_MEM_SET(pstSsEvent, 0 , 4);
    pstSsEvent->SsEvent               =  TAF_SS_EVT_USSD_DATA_SND;
    pstSsEvent->OpId                  = gastSsaStatetable[ucTi].OpId;
    pstSsEvent->ClientId              = gastSsaStatetable[ucTi].ClientId;

    MN_SendClientEvent(pstSsEvent->ClientId,
                       MN_CALLBACK_SS,
                       pstSsEvent->SsEvent,
                       pstSsEvent);

    PS_MEM_FREE(WUEPS_PID_SS, pstSsEvent);

    return;

}


/*****************************************************************************
 �� �� ��  : SSA_GetUssdMode
 ��������  : ��ȡSSAģ���USSD����ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��05��08��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���DTS2012050801468: ֧��^USSDMODE��������ͬ����C��
  2.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
  3.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
*****************************************************************************/
VOS_VOID SSA_GetUssdMode(VOS_VOID)
{
    TAF_USSD_NVIM_TRANS_MODE_STRU       stUssdTranMode;
    VOS_UINT32                          ulLength;

    ulLength = 0;


    PS_MEM_SET(&stUssdTranMode, 0x00, sizeof(stUssdTranMode));

    (VOS_VOID)NV_GetLength(en_NV_Item_CUST_USSD_MODE, &ulLength);

    /*��ȡUSSD�Ƿ�͸������ */
    if (NV_OK == NV_Read(en_NV_Item_CUST_USSD_MODE,
                          &stUssdTranMode,
                          ulLength))
    {
        if (TAF_SSA_NVIM_ITEM_ACTIVE == stUssdTranMode.ucStatus)
        {
            g_usTafSsaUssdTransMode = stUssdTranMode.ucUssdTransMode;
        }
        else
        {
            g_usTafSsaUssdTransMode = AT_USSD_TRAN_MODE;
        }
    }
    else
    {
        g_usTafSsaUssdTransMode = AT_USSD_TRAN_MODE;
    }

    return;
}

/* ɾ��FDN��麯���Ĵ���,�Ƶ�SPM�� */


/***********************************************************************
*  MODULE   : Ss_TaskEntry_T
*  FUNCTION : SSģ��TASK��ڴ���
*  INPUT    : VOS_VOID      *pRcvMsg        ��Ϣָ��
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
* 1.  ��־��   05-01-28  �°�����

* 2.  ��־��   05-03-08  ʹ��PID���зַ�����

  3.��    ��   : 2011��11��13��
    ��    ��   : A00165503
    �޸�����   : AT�ں���Ŀ��TAF PID��ΪAT PID
  4.��    ��   : 2012��02��24��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : C50_IPC Project    Ϊ����FDNҵ��USIM��Ϣ������̰��ͻ����ദ��
  5.��    ��   : 2012��4��25��
    ��    ��   : f62575
    �޸�����   : DTS2012042500352: ���STK�����USSDҵ��֧������
  6.��    ��   : 2013��5��14��
    ��    ��   : w00176964
    �޸�����   : SS FDN&Call Control��Ŀ: USIM����Ϣͳһ��SPMģ�鴦��,����TAF
                 ����Ϣ����
  7.��    ��   : 2013��6��4��
    ��    ��   : z00161729
    �޸�����   : SVLTE ��usim�ӿڵ����޸�
************************************************************************/
VOS_VOID Ss_TaskEntry_T( struct MsgCB* pMsg )
{
    MSG_HEADER_STRU         *pMsgHeader;
    REL_TIMER_MSG           *pTimer;                                            /* ����TIMER��Ϣָ��                        */
    VOS_UINT16               usMsgType;
    VOS_UINT16               usClientId;
    VOS_UINT8                ucOpId;
    MN_APP_REQ_MSG_STRU     *pMnAppReqMsg;

    pMsgHeader = ( MSG_HEADER_STRU* )pMsg;                                      /* �õ���Ϣͷ                               */
    pTimer     = ( REL_TIMER_MSG* ) pMsg;                                       /* ��ȡTIMER��Ϣָ��                        */
    pMnAppReqMsg = ( MN_APP_REQ_MSG_STRU* )pMsg;

    if (VOS_TRUE == TAF_SDC_GetSvlteSupportFlag())
    {
        /* svlte���Կ���ʱ��modem1�����յ�usim0����Ϣ����Ҫ����Ϣ��send pid����ת�� */
        pMsg->ulSenderPid = TAF_SDC_ConvertOamSendPid(pMsg->ulSenderPid);
    }

    if ( VOS_PID_TIMER == pMsg->ulSenderPid )
    {
        Ss_RcvTimerOut((VOS_UINT8)pTimer->ulPara , (VOS_UINT8)pTimer->ulName);      /* TIMER�����Ϣ�ַ�����                    */
    }
    else
    {
        switch( pMsgHeader->ulSenderPid )
        {                                                                   /* ����Src Tsk Id�ַ���Ϣ                   */
            case WUEPS_PID_MM:                                                  /* MM ��������Ϣ                            */
                Ss_RcvMmMsg( pMsg );                                            /* ����MM��Ϣ����                           */
                break;

            case WUEPS_PID_ADMIN:
                break;

            /* Delete MAPS_STK_PID and WUEPS_PID_AT */
            case WUEPS_PID_TAF:
                usMsgType = pMnAppReqMsg->usMsgName;

                /*usClientId*/
                usClientId = pMnAppReqMsg->clientId;

                /*ucOpId*/
                ucOpId = pMnAppReqMsg->opId;

                Taf_SsaProc(usMsgType, usClientId, ucOpId, pMnAppReqMsg->aucContent);
                break;
            default :                                                           /* ����TASK��������Ϣ                       */
                SS_WARN_LOG( "\n [Error]SenderPid Error! \r" );
                break;
        }
    }

}


/***********************************************************************
*  MODULE   : Ss_Init
*  FUNCTION : Ss ��ʼ������
*  INPUT    : VOS_VOID
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
  3.��    ��   : 2015��9��18��
    ��    ��   : c00318887
    �޸�����   : �°�����
************************************************************************/

VOS_VOID Ss_Init( VOS_VOID )
{
    VOS_UINT8   i;                                                                  /* ����ѭ��                                 */

    for( i = 0 ; i < SS_MAX_ENTITY_NUM ; i++ )
    {                                                                           /* ��ʼ��SSʵ����Ϣ                         */
        g_SsEntity[i].ucState = SS_S_NULL;
        SS_NORM_LOG( "\n SS state = SS_S_NULL \r" );
        g_SsEntity[i].ucCr = SS_NONE_CR;
    }

    for( i = 0 ; i < SS_MO_ENTITY_NUM ; i++ )
    {                                                                           /* ��ʼ����Ϣ����BUFFER                     */
        g_SsSaveMsg[i].ulMsgLen = 0;
        if (VOS_NULL_PTR != g_SsSaveMsg[i].pucMsg)
        {
            PS_MEM_FREE(WUEPS_PID_SS, g_SsSaveMsg[i].pucMsg);
            g_SsSaveMsg[i].pucMsg = VOS_NULL_PTR;
        }
    }
}


/***********************************************************************
*  MODULE   : Ss_TaskInit
*  FUNCTION : TASK ��ʼ������
*  INPUT    : VOS_VOID
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־��   04-03-08  �°�����
*     2.  ��־��   �޸�TAF ID��TAF�����ĳ�ʼ��
  3.��    ��   : 2012��3��2��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : C50_IPC Project, ����ҵ���ʼ����������FDN�������û�ȡ
  4.��    ��   : 2012��05��08��
    ��    ��   : f00179208
    �޸�����   : DTS2012050801468: ֧��^USSDMODE��������ͬ����C��
  5.��    ��   : 2013��05��30��
    ��    ��   : w00176964
    �޸�����   : SS FDN&Call Control��Ŀ:ɾ����ȡen_NV_Item_FDN_Info�Ĵ���
************************************************************************/

VOS_VOID Ss_TaskInit( VOS_VOID )
{
    Ss_Init();
    

    SSA_GetUssdMode();
/*=>A32D07063*/
#if 0
    for( i = 0 ; i < SS_MAX_ENTITY_NUM ; i++ )
    {                                                                           /* ��ʼ��TIMER������Ϣ                      */
        Ss_MemSet(&g_SsTimerMng[i].SsTimerId,0,sizeof(HTIMER));
        g_SsTimerMng[i].ucTimerState = SS_TIMER_IDLE;
    }
#endif
/*<=A32D07063*/
}

/******************************************************************************
 * �������� �� WuepsSsPidInit
 * �������� �� WUEPS SS PID�ĳ�ʼ������
 * ����˵�� �� ��
 * ��    ע ��
 * �� �� ֵ �� VOS_UINT32 ��ʼ�������
 *             0  : �ɹ�
 *             ��0: ʧ��
 *
 * �����ʷ ��
 *           No.  ����      ���                                    ��   ��
 *           1    ��־��    �½�                                   2005.02.24
 *****************************************************************************/
VOS_UINT32 WuepsSsPidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch( ip )
    {
    case VOS_IP_LOAD_CONFIG:
        Ss_TaskInit();                                                      /* CC TASK��ʼ������Ӧ����                  */
        break;
    case VOS_IP_FARMALLOC:
    case VOS_IP_INITIAL:
    case VOS_IP_ENROLLMENT:
    case VOS_IP_LOAD_DATA:
    case VOS_IP_FETCH_DATA:
    case VOS_IP_STARTUP:
    case VOS_IP_RIVAL:
    case VOS_IP_KICKOFF:
    case VOS_IP_STANDBY:
    case VOS_IP_BROADCAST_STATE:
    case VOS_IP_RESTART:
    case VOS_IP_BUTT:
        break;
    default:
        break;
    }

    return VOS_OK;
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


