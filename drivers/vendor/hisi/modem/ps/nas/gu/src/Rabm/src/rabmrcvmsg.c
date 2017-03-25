/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : RabmRcvMsg.c
  Description  : Rabm�Ľ��պ���
  Function List:
                 1.  RABM_RcvGmmReestCnf
                 2.  RABM_RcvSmActInd
                 3.  RABM_SaveDataProcess
                 4.  RABM_RcvSmDeactInd
                 5.  RABM_RcvSmModInd
                 6.  RABM_RcvRrcStatusInd
                 7.  RABM_RcvPsTcDataInd
                 8.  RABM_RcvRrcRabInd
                 9.  RABM_RcvPsDataReq
                10.  RABM_RcvCsDataReq
                11.  RABM_RcvRlcDataInd
                12.  RABM_RcvTcTestReq
                13.  RABM_RcvTcTestLoopReq
  History:
      1.   ��־��      2003.12.11   �¹�����
      2.   L47619   2005.12.12   A32D01107���ⵥ
      3.   L47619   2005.12.22   A32D00885���ⵥ
      4.   L47619   2006.01.10   ���ⵥ:A32D01571
      5.   L47619   2006.02.23   ���ⵥ:A32D02155
      6.   L47619   2006.06.12   ���ⵥ:A32D04258
      7.   l47619   2006.08.21:  ���ⵥ:A32D05592
      8.   L47619   2006.06.26   ���ⵥ:A32D05709
      9. ��    ��   : 2007��06��08��
         ��    ��   : luojian 60022475
         �޸�����   : �������ⵥ��A32D11570
*******************************************************************************/
#include "rabminclude.h"
#include "NasRabmMsgProc.h"
#include "NasRabmMain.h"
#include "NasUtranCtrlInterface.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_RABM_RCVMSG_C

/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/


/*��ʶ�����ϱ���ʱ���Ƿ�����*/
extern RABM_FLUX_WRITE_NV_TIMER_SWITCH_ENUM_U32  g_stRabmWriteFluxToNvTimerSwitch;


/*******************************************************************************
  Module:      RABM_RcvGmmReestCnf
  Function:    ������Ϣ���������Ӧ�Ĵ���
  Input:       VOS_VOID                *pMsg        ��ǰ�������Ϣ
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
  1.  ��־��      2003.12.11   �¹�����

  2.��    ��   : 2011��12��19��
    ��    ��   : o00132663
    �޸�����   : PS�ں���Ŀ�����յ�RAB�ؽ������֪ͨCDS
  3.��    ��   : 2012��10��31��
    ��    ��   : z60575
    �޸�����   : DTS2012101906800������ԭ��ֵʱ����0.5s��ʱ
  4.��    ��   : 2013��2��18��
    ��    ��   : A00165503
    �޸�����   : DTS2013021805741: RB���������Ż�
  5.��    ��   : 2013��04��12��
    ��    ��   : l65478
    �޸�����   : DTS2013031901654:���Ų�������ʧ��
*******************************************************************************/
VOS_VOID RABM_RcvGmmReestCnf(
                         VOS_VOID  *pMsg                                            /* ��ǰ�������Ϣ                           */
                         )
{
    GMMRABM_REESTABLISH_CNF_STRU          *pTempMsg;                            /* ����ֲ�����                             */
    VOS_UINT8                                 i;                                    /* ѭ������                                 */

    pTempMsg = (GMMRABM_REESTABLISH_CNF_STRU *)pMsg;

    if( RABM_FALSE == g_ucReestTimerFlg )
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_WARNING, "RABM_RcvGmmReestCnf:WARNING:GMM->RABM g_ucReestTimerFlg Error!");
        return;
    }

    /* ֹͣ�ȴ�REESTABLISH_CNF��Ϣ�Ķ�ʱ�� */
    RABM_TimerStop(0);
    g_ucReestTimerFlg = RABM_FALSE;

    if( GMM_RABM_SERVICEREQ_FAILURE == pTempMsg->ulResult )
    {                                                                           /* ʧ��                                     */
        for( i = 0; i < RABM_PS_MAX_ENT_NUM; i++ )
        {                                                                       /* ����PS��RABMʵ��                         */
            switch( g_aRabmPsEnt[i].ucState )
            {                                                                   /* RABMʵ���״̬                           */
                case RABM_NSAPI_ACTIVE_NO_RAB:

                    if (VOS_TRUE == NAS_RABM_GetWPsEntRabReestFlg(i))
                    {
                        /* ���RABMʵ����ؽ���ʶ */
                        NAS_RABM_ClearWPsEntRabReestFlg(i);

                        /* ֪ͨCDSģ��RAB�ؽ�ʧ�� */
                        NAS_RABM_SndCdsFreeBuffDataInd(i + RABM_NSAPI_OFFSET);
                    }

                    if(0 != g_aRabmPsEnt[i].UlDataSave.ucNum)
                    {
                        RABM_RelSaveData(&g_aRabmPsEnt[i].UlDataSave, RABM_UPLINK); /* �ͷŴ洢����������                       */
                    }
                    g_aRabmPsEnt[i].ucStpFlg = RABM_FALSE;
                    break;
                case RABM_NULL:
                case RABM_NSAPI_ACTIVE_PENDING:
                case RABM_NSAPI_ACTIVE_WITH_RAB:
                case RABM_ACT_PENDING_WITH_RAB:
                case RABM_DATA_TRANSFER_STOP:
                    break;
                default:
                    break;
            }
        }

        /*��λ2G��3G�л�ʹ�õ������ָ���־:*/
        if ( VOS_TRUE == gRabm2GTo3GDataResume )
        {
            gRabm2GTo3GDataResume = VOS_FALSE;

            /*�ͷ���2G��3G�л���ʼʱSNDCP���������:*/
            SN_RabmClear2G3Share();
        }
    }
    else if ((GMM_RABM_SERVICEREQ_DELAYED == pTempMsg->ulResult)
          || (GMM_RABM_SERVICEREQ_OOS == pTempMsg->ulResult))
    {
        NAS_RABM_SetRabRsestTimerFlg();
        NAS_RabmStartTimer(RABM_TIMER_NAME_COMMON, RABM_TIMER_RESEND_EST_REQ);
    }
    else
    {
        /* ����RB����������ʱ�� */
        for (i = 0; i < RABM_3G_PS_MAX_ENT_NUM; i++)
        {
            if ( (RABM_NSAPI_ACTIVE_NO_RAB == NAS_RABM_GetWPsEntState(i))
              && (VOS_TRUE == NAS_RABM_GetWPsEntRabReestFlg(i)) )
            {
                NAS_RABM_StartReestRabPendingTmr(i + RABM_NSAPI_OFFSET);
            }
        }
    }
    return;
}

/*******************************************************************************
  Module:      RABM_RcvSmActInd
  Function:    ����������ά��ʵ���״̬
  Input:       VOS_VOID                *pMsg        ��ǰ�������Ϣ
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
  1.  ��־��      2003.12.11   �¹�����
  2.��    ��   : 2010��12��13��
    ��    ��   : lijun 00171473
    �޸�����   : DTS2010112903583, ���Timer, ��������ÿ10���ӱ���һ��NV
                 PDP�������TIMER
  3.��    ��   : 2011��10��21��
    ��    ��   : h44270
    �޸�����   : V7R1 FAST DORMANCY���ԣ�����PDP����״̬�ı仯����û�м���м����PDP
  4.��    ��   : 2011��12��19��
    ��    ��   : o00132663
    �޸�����   : PS�ں���Ŀ��PDP����ɹ������CDS�ṩ�����ؽӿڽ�QOS��Ϣ֪ͨ-
                 CDS
  5.��    ��   : 2012��04��01��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ��:DTS2012032603501, PDP���ųɹ���,��CDS��QOS�ȼ�����ȷ

  6.��    ��   : 2012��08��07��
    ��    ��   : f00179208
    �޸�����   : ���ⵥ:DTS2012080604402, PDP����ȥ��������ڴ�й¶

  7.��    ��   : 2012��8��22��
    ��    ��   : A00165503
    �޸�����   : RABM�����QOS�ɶ�̬�ڴ��Ϊ��̬����

  8.��    ��   : 2013��8��2��
    ��    ��   : A00165503
    �޸�����   : DTS2013040906296: Secondary PDP���������޷��ҵ������ĳ���ID
*******************************************************************************/
VOS_VOID RABM_RcvSmActInd(
    VOS_VOID                           *pMsg                                    /* ��ǰ�������Ϣ                           */
)
{
    RABMSM_ACTIVATE_IND_STRU           *pTempMsg;                               /* ����ֲ�����                             */
    VOS_UINT8                           ucRabUpdFlg;                            /* ����RAB����                              */
    VOS_UINT8                           ucEntId;                                /* ����ֲ�����                             */
    QCI_TYPE_ENUM_UINT8                 enQci;

    pTempMsg = (RABMSM_ACTIVATE_IND_STRU *)pMsg;                                /* ָ��ǰ�������Ϣ                       */

    ucRabUpdFlg = RABM_FALSE;                                                   /* ��ʼ����־                               */
    ucEntId = (VOS_UINT8)(pTempMsg->ulNsapi - RABM_NSAPI_OFFSET);                   /* ���PS��RABMʵ������                     */
    switch(g_aRabmPsEnt[ucEntId].ucState)
    {                                                                           /* ����ʵ���״̬������Ӧ�Ĵ���             */
    case RABM_NULL:
        PS_NAS_LOG1(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_RcvSmActInd:NORMAL:Create RABM entity(EntId):",ucEntId);

        g_aRabmPsEnt[ucEntId].QoS.ulQosLength = pTempMsg->Qos.ulLength;         /* �������QoS����                          */
        PS_MEM_CPY(g_aRabmPsEnt[ucEntId].QoS.aucQosValue,
                   pTempMsg->Qos.aucQosValue,
                   NAS_RABM_MAX_QOS_LEN);                                      /* �������QoS��RABMʵ��                    */

        if ((RABMSM_ACT_MSG_2 == pTempMsg->ulActMsgType)
         && (VOS_TRUE == NAS_RABM_GetDataSuspendFlg()))
        {
            if ( (g_aRabmPsEnt[ucEntId].QoS.aucQosValue[3] & NAS_RABM_QOS_DELIVERY_ERRORNEOUS_SDU_MASK)
                 != (pTempMsg->Qos.aucQosValue[3] & NAS_RABM_QOS_DELIVERY_ERRORNEOUS_SDU_MASK) )
            {                                                                       /* ����DeliveryErrSdu�����ı�               */
                ucRabUpdFlg = RABM_TRUE;                                            /* ����RAB���������ı��־                  */
            }
            if( g_aRabmPsEnt[ucEntId].ucPppFlg != pTempMsg->ulPppFlag )
            {                                                                       /* û�в���PPPЭ��                          */
                ucRabUpdFlg = RABM_TRUE;                                            /* ����RAB���������ı��־                  */
            }

            g_aRabmPsEnt[ucEntId].QoS.ulQosLength = pTempMsg->Qos.ulLength;         /* �������QoS����                          */
            PS_MEM_CPY(g_aRabmPsEnt[ucEntId].QoS.aucQosValue,
                       pTempMsg->Qos.aucQosValue,
                       NAS_RABM_MAX_QOS_LEN);                      /* �������QoS��RABMʵ��                    */

            /* data suspend״̬�յ��ڶ���pdp������Ϣ������w״̬ΪRABM_DATA_TRANSFER_STOP */
            RABM_SetWState(ucEntId, RABM_DATA_TRANSFER_STOP);                      /* ״̬Ǩ�Ƶ�RABM_DATA_TRANSFER_STOP       */
            PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_RcvSmActInd:NORMAL:RABM_NULL ==> RABM_DATA_TRANSFER_STOP");

            if( RABM_TRUE == ucRabUpdFlg )
            {                                                                       /* RAB���������ı�                          */
                RABM_SndRrcQosUpdReq(ucEntId);                                      /* ֪ͨRRC                                  */
            }

            /*����RAB_MAPӳ��ʵ��*/
            NAS_RABM_CreateRabMapEntity((VOS_UINT8)(pTempMsg->ulNsapi),
                                        (VOS_UINT8)(pTempMsg->ulLinkdNsapi),
                                        (VOS_UINT8)(pTempMsg->ulNsapi));

            /* ��CDS������Ϣ֪ͨCDS QOS��Ϣ */
            enQci = NAS_RABM_GetQciFromQos(g_aRabmPsEnt[ucEntId].QoS.ulQosLength,
                                           g_aRabmPsEnt[ucEntId].QoS.aucQosValue);

            NAS_RABM_SndCdsQosFcRabCreateInd(ucEntId + RABM_NSAPI_OFFSET, enQci);
        }
        else
        {
            RABM_SetWState(ucEntId, RABM_NSAPI_ACTIVE_PENDING);                     /* ״̬Ǩ�Ƶ�RABM_NSAPI_ACTIVE_PENDING      */
            PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_RcvSmActInd:NORMAL:RABM state: RABM_NULL ==> RABM_NSAPI_ACTIVE_PENDING");
        }

        if(RABM_SM_PPP_PROT == pTempMsg->ulPppFlag)
        {
            g_aRabmPsEnt[ucEntId].ucPppFlg = RABM_SM_PPP_PROT;
        }
        else
        {
            g_aRabmPsEnt[ucEntId].ucPppFlg = RABM_SM_IP_PROT;
        }

        break;
    case RABM_NSAPI_ACTIVE_PENDING:
        if(RABMSM_ACT_MSG_1 == pTempMsg->ulActMsgType)
        {
            break;
        }

        if ( (g_aRabmPsEnt[ucEntId].QoS.aucQosValue[3] & NAS_RABM_QOS_DELIVERY_ERRORNEOUS_SDU_MASK)
             != (pTempMsg->Qos.aucQosValue[3] & NAS_RABM_QOS_DELIVERY_ERRORNEOUS_SDU_MASK) )
        {                                                                       /* ����DeliveryErrSdu�����ı�               */
            ucRabUpdFlg = RABM_TRUE;                                            /* ����RAB���������ı��־                  */
        }
        if( g_aRabmPsEnt[ucEntId].ucPppFlg != pTempMsg->ulPppFlag )
        {                                                                       /* û�в���PPPЭ��                          */
            ucRabUpdFlg = RABM_TRUE;                                            /* ����RAB���������ı��־                  */
        }

        g_aRabmPsEnt[ucEntId].QoS.ulQosLength = pTempMsg->Qos.ulLength;         /* �������QoS����                          */
        PS_MEM_CPY(g_aRabmPsEnt[ucEntId].QoS.aucQosValue,
                   pTempMsg->Qos.aucQosValue,
                   NAS_RABM_MAX_QOS_LEN);                      /* �������QoS��RABMʵ��                    */

        RABM_SetWState(ucEntId, RABM_NSAPI_ACTIVE_NO_RAB);                      /* ״̬Ǩ�Ƶ�RABM_NSAPI_ACTIVE_NO_RAB       */

        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_RcvSmActInd:NORMAL:RABM_NSAPI_ACTIVE_PENDING ==> RABM_NSAPI_ACTIVE_NO_RAB");
        if( RABM_TRUE == ucRabUpdFlg )
        {                                                                       /* RAB���������ı�                          */
            RABM_SndRrcQosUpdReq(ucEntId);                                      /* ֪ͨRRC                                  */
        }

        /*����RAB_MAPӳ��ʵ��*/
        NAS_RABM_CreateRabMapEntity((VOS_UINT8)(pTempMsg->ulNsapi),
                                    (VOS_UINT8)(pTempMsg->ulLinkdNsapi),
                                    (VOS_UINT8)(pTempMsg->ulNsapi));

        /* ��CDS������Ϣ֪ͨCDS QOS��Ϣ */
        enQci = NAS_RABM_GetQciFromQos(g_aRabmPsEnt[ucEntId].QoS.ulQosLength,
                                       g_aRabmPsEnt[ucEntId].QoS.aucQosValue);

        NAS_RABM_SndCdsQosFcRabCreateInd(ucEntId + RABM_NSAPI_OFFSET, enQci);

        break;
    case RABM_ACT_PENDING_WITH_RAB:

        /* �������QoS���� */
        g_aRabmPsEnt[ucEntId].QoS.ulQosLength = pTempMsg->Qos.ulLength;

        PS_MEM_CPY(g_aRabmPsEnt[ucEntId].QoS.aucQosValue,
                   pTempMsg->Qos.aucQosValue,
                   NAS_RABM_MAX_QOS_LEN);


        /* ״̬Ǩ�Ƶ�RABM_NSAPI_ACTIVE_WITH_RAB     */
        RABM_SetWState(ucEntId, RABM_NSAPI_ACTIVE_WITH_RAB);

        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_RcvSmActInd:NORMAL:RABM state: RABM_ACT_PENDING_WITH_RAB ==> RABM_NSAPI_ACTIVE_WITH_RAB ");
        if(0 != g_aRabmPsEnt[ucEntId].DlDataSave.ucNum)
        {
            RABM_SaveDataProcess(ucEntId,RABM_DOWNLINK);
        }

        /*����RAB_MAPӳ��ʵ��*/
        NAS_RABM_CreateRabMapEntity((VOS_UINT8)(pTempMsg->ulNsapi),
                                    (VOS_UINT8)(pTempMsg->ulLinkdNsapi),
                                    g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[0]);

        /* ��CDS������Ϣ֪ͨCDS QOS��Ϣ */
        enQci = NAS_RABM_GetQciFromQos(g_aRabmPsEnt[ucEntId].QoS.ulQosLength,
                                       g_aRabmPsEnt[ucEntId].QoS.aucQosValue);

        NAS_RABM_SndCdsQosFcRabCreateInd(ucEntId + RABM_NSAPI_OFFSET, enQci);

        break;
    case RABM_NSAPI_ACTIVE_WITH_RAB:
    case RABM_NSAPI_ACTIVE_NO_RAB:
        break;
    case RABM_DATA_TRANSFER_STOP:
        if(RABM_FALSE == g_aRabmPsEnt[ucEntId].ucStpFlg)
        {
            g_aRabmPsEnt[ucEntId].ucStpFlg = RABM_TRUE;
            g_aRabmPsEnt[ucEntId].QoS.ulQosLength = pTempMsg->Qos.ulLength;     /* �������QoS����                          */
            PS_MEM_CPY(g_aRabmPsEnt[ucEntId].QoS.aucQosValue,
                       pTempMsg->Qos.aucQosValue,
                       NAS_RABM_MAX_QOS_LEN);                  /* �������QoS��RABMʵ��                    */
        }
        break;
    default:
        break;
    }

    return;
}

/*******************************************************************************
  Module:      RABM_SaveDataProcess
  Function:    �����������
  Input:       VOS_UINT8 ucEntId        ʵ��ID
               VOS_UINT8 ucUlFlg        �Ƿ�����������
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
      1.  ��־��     2003.12.11   �¹�����
*******************************************************************************/
VOS_VOID RABM_SaveDataProcess(
                          VOS_UINT8  ucEntId,                                       /* ʵ��ID                                   */
                          VOS_UINT8  ucUlFlg                                        /* �Ƿ�����������                         */
                          )
{
    PDCP_RABM_DATA_BUF_STRU  *pTempData1 = RABM_POINTER_NULL;                   /* ����ֲ�����                             */
    TAFRABM_PS_DATA_REQ_STRU *pTempData3 = RABM_POINTER_NULL;                   /* ����ֲ�����                             */
    RABM_DATA_LINK_STRU      *pTempData2 = RABM_POINTER_NULL;                   /* ����ֲ�����                             */
    RABM_DATA_SAVE_STRU      *pTemp = RABM_POINTER_NULL;
    VOS_UINT8                    i;

    if( RABM_UPLINK == ucUlFlg )
    {
        pTemp = &(g_aRabmPsEnt[ucEntId].UlDataSave);
        for( i = 0; i < pTemp->ucNum; i++ )
        {                                                                       /* ���������������Ϣ                       */
            pTempData3=(TAFRABM_PS_DATA_REQ_STRU *)pTemp->Data.pData;                                       /* �����׵�ַ                               */
            pTempData2=pTemp->Data.pNxt;                                        /* ��һ�����ݽڵ��ַ                       */
            RABM_SndPdcpDataReq(ucEntId,pTempData3);                            /* ��Ͳ㷢������                           */
            RABM_Free(pTempData3);                                              /* �ͷŻ������Ϣ                           */
            if( pTempData2 == RABM_POINTER_NULL )
            {
                pTemp->ucNum = 0;                                               /* �����������Ϣ������0                    */
                pTemp->Data.pData = RABM_POINTER_NULL;                          /* ָ����0                                  */
                pTemp->Data.pNxt = RABM_POINTER_NULL;                           /* ָ����0                                  */
            }
            else
            {
                pTemp->Data.pNxt = pTempData2->pNxt;                            /* ���»�������ݵ�ַ                       */
                pTemp->Data.pData = pTempData2->pData;                          /* ���»�������ݵ�ַ                       */
                RABM_Free(pTempData2);
            }
        }
    }
    else
    {
        pTemp = &(g_aRabmPsEnt[ucEntId].DlDataSave);
        for( i = 0; i < pTemp->ucNum; i++ )
        {                                                                       /* ���������������Ϣ                       */
            pTempData1=(PDCP_RABM_DATA_BUF_STRU *)pTemp->Data.pData;            /* �����׵�ַ                               */
            pTempData2=pTemp->Data.pNxt;                                        /* ��һ�����ݽڵ��ַ                       */
            RABM_SndTafPsDataInd(ucEntId, pTempData1);                          /* ��߲㷢������                           */
            RABM_PdcpFree(pTempData1->pucData);                                 /* �ͷŻ��������                           */
            RABM_PdcpFree(pTempData1);                                          /* �ͷŻ������Ϣ                           */
            if( pTempData2 == RABM_POINTER_NULL )
            {
                pTemp->ucNum = 0;                                               /* �����������Ϣ������0                    */
                pTemp->Data.pData = RABM_POINTER_NULL;                          /* ָ����0                                  */
                pTemp->Data.pNxt = RABM_POINTER_NULL;                           /* ָ����0                                  */
            }
            else
            {
                pTemp->Data.pNxt = pTempData2->pNxt;                            /* ���»�������ݵ�ַ                       */
                pTemp->Data.pData = pTempData2->pData;                          /* ���»�������ݵ�ַ                       */
                RABM_Free(pTempData2);
            }
        }
    }
}

/*******************************************************************************
  Module:      RABM_RcvSmDeactInd
  Function:    �ͷ���Դ��ά��ʵ���״̬
  Input:       VOS_VOID                *pMsg        ��ǰ�������Ϣ
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
  1.  ��־��      2003.12.11   �¹�����
  2.��    ��   : 2010��12��13��
    ��    ��   : lijun 00171473
    �޸�����   : DTS2010112903583, ���Timer, ��������ÿ10���ӱ���һ��NV
                 PDPȥ����� ��TIMER, дNV

  3.��    ��   : 2011��10��21��
    ��    ��   : h44270
    �޸�����   : V7R1 FAST DORMANCY���ԣ�����PDP����״̬�ı仯�����м��û�м����PDP

  4.��    ��   : 2011��12��19��
    ��    ��   : o00132663
    �޸�����   : PS�ں���Ŀ��PDPȥ�������Ҫ����CDS�ṩ�����ؽӿ�֪ͨCDS

  5.��    ��   : 2012��8��22��
    ��    ��   : A00165503
    �޸�����   : RABM�����QOS�ɶ�̬�ڴ��Ϊ��̬����

  6.��    ��   : 2013��04��12��
    ��    ��   : l65478
    �޸�����   : DTS2013031901654:���Ų�������ʧ��

  7.��    ��   : 2015��1��9��
    ��    ��   : A00165503
    �޸�����   : DTS2014123000271: RRC�ͷ���������ֹͣ����
*******************************************************************************/
VOS_VOID RABM_RcvSmDeactInd(VOS_VOID *pMsg)
{
    RABMSM_DEACTIVATE_IND_STRU         *pTempMsg;                                    /* ����ֲ�����                             */
    VOS_UINT8                           i;
    VOS_UINT32                          ulNsapi;                                      /* ����ֲ�����                             */
    VOS_UINT32                          ulEntId;
    VOS_UINT32                          ulRabmEntNum;
    VOS_UINT8                           ucState;

    pTempMsg = (RABMSM_DEACTIVATE_IND_STRU *)pMsg;                              /* ָ��ǰ�������Ϣ                       */
    for( i = 0; i < pTempMsg->ulDeactiveNum; i++ )
    {                                                                           /* ����ȥ�����Nsapi                        */
        ulNsapi = pTempMsg->aulNsapiList[i];                                    /* ���NSAPI                                */
        if(ulNsapi < RABM_NSAPI_OFFSET)
        {
            continue;
        }

        if(RABM_NULL == g_aRabmPsEnt[ulNsapi-RABM_NSAPI_OFFSET].ucState)
        {                                                                       /* ʵ���״̬Ϊ�Ǽ���                       */
            ;
        }
        else
        {
            RABM_SetWState((VOS_UINT8)(ulNsapi-RABM_NSAPI_OFFSET), RABM_NULL);               /* ״̬���                                 */
            PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_RcvSmDeactInd:NORMAL:RABM state = RABM_NULL ");
            PS_NAS_LOG1(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_RcvSmDeactInd:NORMAL:Destroy RABM entity(EntId): ",(VOS_INT32)(ulNsapi-RABM_NSAPI_OFFSET));
            g_aRabmPsEnt[ulNsapi-RABM_NSAPI_OFFSET].RabInfo.ucRbNum = 0;        /* ��ʼ��RB�ĸ���Ϊ0                        */
            g_aRabmPsEnt[ulNsapi-RABM_NSAPI_OFFSET].ucPppFlg = RABM_SM_IP_PROT; /* �ϲ�Э�����ͳ�ʼ��ΪIP                   */

            if (VOS_TRUE == NAS_RABM_GetWPsEntRabReestFlg(ulNsapi - RABM_NSAPI_OFFSET))
            {
                /* ֹͣ���RB����������ʱ�� */
                NAS_RABM_StopReestRabPendingTmr((VOS_UINT8)ulNsapi);

                /* ���RABMʵ����ؽ���ʶ */
                NAS_RABM_ClearWPsEntRabReestFlg(ulNsapi - RABM_NSAPI_OFFSET);
            }

            /*���QoS:*/
            g_aRabmPsEnt[ulNsapi-RABM_NSAPI_OFFSET].QoS.ulQosLength = 0;        /* ���QoS                                  */
            PS_MEM_SET(g_aRabmPsEnt[ulNsapi-RABM_NSAPI_OFFSET].QoS.aucQosValue,
                       0x00,
                       sizeof(g_aRabmPsEnt[ulNsapi-RABM_NSAPI_OFFSET].QoS.aucQosValue));

            RABM_RelSaveData(&g_aRabmPsEnt[ulNsapi-RABM_NSAPI_OFFSET].DlDataSave, RABM_DOWNLINK);
            RABM_RelSaveData(&g_aRabmPsEnt[ulNsapi-RABM_NSAPI_OFFSET].UlDataSave, RABM_UPLINK);

            /* ������Ϣ��CDS֪ͨCDS PDP��ȥ���� */
            NAS_RABM_SndCdsQosFcRabReleaseInd((VOS_UINT8)ulNsapi);

            /* ֪ͨCDS�ͷŻ������� */
            NAS_RABM_SndCdsFreeBuffDataInd((VOS_UINT8)ulNsapi);
        }

        /*ɾ��RAB_MAPʵ��*/
        RABM_DelRabMap((VOS_UINT8)ulNsapi);
    }

    /*�����ǰ�Ѿ�û��PDP�����ʵ�壬�����FAST DORMANCY*/
    ulRabmEntNum = 0;
    for (ulEntId = 0; ulEntId < RABM_3G_PS_MAX_ENT_NUM; ulEntId++)
    {
        ucState = NAS_RABM_GetWPsEntState(ulEntId);
        if ( (RABM_NSAPI_ACTIVE_NO_RAB == ucState)
          || (RABM_NSAPI_ACTIVE_WITH_RAB == ucState)
          || (RABM_DATA_TRANSFER_STOP == ucState) )
        {
            ulRabmEntNum++;
        }
    }

    if (0 == ulRabmEntNum)
    {
        NAS_RABM_SuspendFastDorm();

        NAS_RABM_AbortRelRrcProcedure();

        /* ֹͣRAB�ؽ�������ʱ�� */
        if (VOS_TRUE == NAS_RABM_GetRabRsestTimerFlg())
        {
            RABM_TimerStop(0);
            NAS_RabmStopTimer(RABM_TIMER_NAME_COMMON, RABM_TIMER_RESEND_EST_REQ);
            NAS_RABM_ClearRabRsestTimerFlg();
        }
    }

    return;
}

/*******************************************************************************
  Module:      RABM_RcvSmModInd
  Function:    ����������ά��ʵ���״̬
  Input:       VOS_VOID                *pMsg        ��ǰ�������Ϣ
  Output:      VOS_VOID
  NOTE:
  Return:      VOS_VOID
  History:
  1.��־��     2003.12.11   �¹�����

  2.��    ��   : 2011��12��19��
    ��    ��   : o00132663
    �޸�����   : PS�ں���Ŀ��PDP����ɹ������CDS�ṩ�����ؽӿڽ�QOS��Ϣ֪ͨ-
                 CDS

  3.��    ��   : 2012��8��22��
    ��    ��   : A00165503
    �޸�����   : RABM�����QOS�ɶ�̬�ڴ��Ϊ��̬����
*******************************************************************************/
VOS_VOID RABM_RcvSmModInd(
    VOS_VOID                           *pMsg                                               /* ��ǰ�������Ϣ                           */
)
{
    RABMSM_MODIFY_IND_STRU             *pTempMsg;                               /* ����ֲ�����                             */
    VOS_UINT8                           ucRabUpdFlg;                            /* ����RAB����                              */
    VOS_UINT8                           ucEntIndex;                             /* ����ֲ�����                             */
    QCI_TYPE_ENUM_UINT8                 enQci;

    pTempMsg = (RABMSM_MODIFY_IND_STRU *)pMsg;                                  /* ָ��ǰ�������Ϣ                       */

    ucRabUpdFlg = RABM_FALSE;                                                   /* ��ʼ����־                               */
    ucEntIndex = (VOS_UINT8)(pTempMsg->ulNsapi-RABM_NSAPI_OFFSET);                  /* ���PS��RABMʵ������                     */
    switch(g_aRabmPsEnt[ucEntIndex].ucState)
    {                                                                           /* ����ʵ���״̬������Ӧ�Ĵ���             */
    case RABM_NULL:
        break;
    case RABM_NSAPI_ACTIVE_PENDING:
    case RABM_NSAPI_ACTIVE_NO_RAB:
        g_aRabmPsEnt[ucEntIndex].QoS.ulQosLength = pTempMsg->Qos.ulLength;      /* �������QoS����                          */
        PS_MEM_CPY(g_aRabmPsEnt[ucEntIndex].QoS.aucQosValue,
                   pTempMsg->Qos.aucQosValue,
                   NAS_RABM_MAX_QOS_LEN);                      /* �������QoS��RABMʵ��                    */

        /* ��CDS������Ϣ֪ͨCDS QOS��Ϣ */
        enQci = NAS_RABM_GetQciFromQos(g_aRabmPsEnt[ucEntIndex].QoS.ulQosLength,
                                       g_aRabmPsEnt[ucEntIndex].QoS.aucQosValue);

        NAS_RABM_SndCdsQosFcRabCreateInd(ucEntIndex + RABM_NSAPI_OFFSET, enQci);

        break;

    case RABM_NSAPI_ACTIVE_WITH_RAB:
    case RABM_DATA_TRANSFER_STOP:
    case RABM_ACT_PENDING_WITH_RAB:

        if ( (g_aRabmPsEnt[ucEntIndex].QoS.aucQosValue[3] & NAS_RABM_QOS_DELIVERY_ERRORNEOUS_SDU_MASK)
             != (pTempMsg->Qos.aucQosValue[3] & NAS_RABM_QOS_DELIVERY_ERRORNEOUS_SDU_MASK))
        {                                                                       /* ����DeliveryErrSdu�����ı�               */
            ucRabUpdFlg = RABM_TRUE;                                            /* ����RAB���������ı��־                  */
        }

        g_aRabmPsEnt[ucEntIndex].QoS.ulQosLength = pTempMsg->Qos.ulLength;      /* �������QoS����                          */
        PS_MEM_CPY(g_aRabmPsEnt[ucEntIndex].QoS.aucQosValue,
                   pTempMsg->Qos.aucQosValue,
                   NAS_RABM_MAX_QOS_LEN);                      /* �������QoS��RABMʵ��                    */

        if( RABM_TRUE == ucRabUpdFlg )
        {                                                                       /* RAB���������ı�                          */
            RABM_SndRrcQosUpdReq(ucEntIndex);                                   /* ֪ͨRRC                                  */
        }

        /* ��CDS������Ϣ֪ͨCDS QOS��Ϣ */
        enQci = NAS_RABM_GetQciFromQos(g_aRabmPsEnt[ucEntIndex].QoS.ulQosLength,
                                       g_aRabmPsEnt[ucEntIndex].QoS.aucQosValue);

        NAS_RABM_SndCdsQosFcRabCreateInd(ucEntIndex + RABM_NSAPI_OFFSET, enQci);

        break;
    default:
        break;
    }

    return;
}

/*******************************************************************************
  Module:   RABM_RcvRrcStatusInd
  Function: ����RAB��CN��RABMʵ���״̬��������Ӧ�Ĵ���
  Input:    VOS_VOID    *pMsg           �յ�����Ϣ
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
  1. ��־��      2003.12.11   �¹�����

  2.��    ��   : 2012��6��1��
    ��    ��   : A00165503
    �޸�����   : DTS2012052606995: ��RNCӦ�л��������������ָ̻�
*******************************************************************************/
VOS_VOID RABM_RcvRrcStatusInd(
                          VOS_VOID  *pMsg
                          )
{
    RRRABM_STATUS_IND_STRU *pTempMsg = RABM_POINTER_NULL;
    VOS_UINT8  ucNsapi;
    VOS_UINT8  ucEntId;
    VOS_UINT8  i;

    pTempMsg = (RRRABM_STATUS_IND_STRU *)pMsg;

    if(RRC_RAB_STATUS_STOP == pTempMsg->ulStatus)
    {                                                                           /* ֹͣ���ݴ���                             */
        for(i = 0; i < pTempMsg->ulRabCnt; i++)
        {                                                                       /* ִ��ָʾֹͣ���ݴ��������rb             */
            if(RABM_CN_PS == pTempMsg->aRab[i].enCnDomainId)
            {                                                                   /* ��ps���rabmʵ��                         */
                ucNsapi = (VOS_UINT8)(pTempMsg->aRab[i].ulRabId & 0x0f);            /* �õ�NSAPI                                */
                ucEntId = (VOS_UINT8)(ucNsapi - RABM_NSAPI_OFFSET);                 /* �õ�ʵ���±�                             */
                switch(g_aRabmPsEnt[ucEntId].ucState)
                {                                                               /* PSʵ���״̬                             */
                case RABM_NULL:
                case RABM_NSAPI_ACTIVE_PENDING:
                case RABM_DATA_TRANSFER_STOP:
                case RABM_NSAPI_ACTIVE_NO_RAB:
                    break;
                case RABM_ACT_PENDING_WITH_RAB:
                    RABM_SetWState(ucEntId, RABM_DATA_TRANSFER_STOP);
                    PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_RcvRrcStatusInd:NORMAL:RABM state: RABM_ACT_PENDING_WITH_RAB ==> RABM_DATA_TRANSFER_STOP");
                    g_aRabmPsEnt[ucEntId].ucStpFlg = RABM_FALSE;
                    break;
                case RABM_NSAPI_ACTIVE_WITH_RAB:
                    RABM_SetWState(ucEntId, RABM_DATA_TRANSFER_STOP);
                    PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_RcvRrcStatusInd:NORMAL:RABM state: RABM_NSAPI_ACTIVE_WITH_RAB ==> RABM_DATA_TRANSFER_STOP");
                    g_aRabmPsEnt[ucEntId].ucStpFlg = RABM_TRUE;
                    break;
                case RABM_TC_STATE_NULL:
                    break;
                default:
                    break;
                }
                if(RABM_TC_NO_START != g_RabmTcInf.ucTcStartSta)
                {
                    RABM_TcRbStatus(pTempMsg, i, TC_RAB_RELEASE);
                }
            }
        }
    }
    else
    {                                                                           /* �����������ݴ���                         */
        for(i = 0; i < pTempMsg->ulRabCnt; i++)
        {
            if(RABM_CN_PS == pTempMsg->aRab[i].enCnDomainId)
            {                                                                   /* ��ps���rabmʵ��                         */
                ucNsapi = (VOS_UINT8)(pTempMsg->aRab[i].ulRabId & 0x0f);            /* �õ�NSAPI                                */
                ucEntId = (VOS_UINT8)(ucNsapi - RABM_NSAPI_OFFSET);                 /* �õ�ʵ���±�                             */
                switch(g_aRabmPsEnt[ucEntId].ucState)
                {                                                               /* ��ps���rabmʵ��                         */
                case RABM_NULL:
                case RABM_NSAPI_ACTIVE_PENDING:
                case RABM_NSAPI_ACTIVE_WITH_RAB:
                case RABM_NSAPI_ACTIVE_NO_RAB:
                case RABM_ACT_PENDING_WITH_RAB:
                    break;
                case RABM_DATA_TRANSFER_STOP:
                    if(RABM_TRUE == g_aRabmPsEnt[ucEntId].ucStpFlg)
                    {
                        if(0 != g_aRabmPsEnt[ucEntId].UlDataSave.ucNum)
                        {                                                       /* �л������������                         */
                            RABM_SaveDataProcess(ucEntId,RABM_UPLINK);          /* ���������������                       */
                        }
                        if(0 != g_aRabmPsEnt[ucEntId].DlDataSave.ucNum)
                        {                                                       /* �л������������                         */
                            RABM_SaveDataProcess(ucEntId,RABM_DOWNLINK);        /* ���������������                       */
                        }
                        RABM_SetWState(ucEntId, RABM_NSAPI_ACTIVE_WITH_RAB);
                        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_RcvRrcStatusInd:NORMAL:RABM state: RABM_DATA_TRANSFER_STOP ==> RABM_NSAPI_ACTIVE_WITH_RAB");
                        g_aRabmPsEnt[ucEntId].ucStpFlg = RABM_FALSE;

                        /* ֪ͨCDS���Է������� */
                        NAS_RABM_SndCdsSendBuffDataInd(ucEntId + RABM_NSAPI_OFFSET,
                                                       CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_SERVICE_SUCC);

                    }
                    else
                    {
                        RABM_SetWState(ucEntId, RABM_ACT_PENDING_WITH_RAB);
                        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_RcvRrcStatusInd:NORMAL:RABM state: RABM_DATA_TRANSFER_STOP ==> RABM_ACT_PENDING_WITH_RAB");
                    }
                    break;
                case RABM_TC_STATE_NULL:
                    break;
                default:
                    break;
                }
            }
            if(RABM_TC_NO_START != g_RabmTcInf.ucTcStartSta)
            {
                RABM_TcRbStatus(pTempMsg, i, TC_RAB_SETUP);
            }
        }
    }

}

/*******************************************************************************
  Module:   RABM_TcDataQInit
  Function: ���ز����У�PDCP->RABM���ݶ��еĳ�ʼ��
  Input:    VOS_VOID
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:

*******************************************************************************/
VOS_VOID RABM_TcDataQInit(VOS_VOID)
{
    RABM_Memset(&g_stPdcpRabmTcDataQ, 0, sizeof(g_stPdcpRabmTcDataQ));

    TTF_LinkInit(WUEPS_PID_RABM, &g_stPdcpRabmTcDataQ.stDataQ);

    g_stPdcpRabmTcDataQ.stCfg.ulOnceDealMaxCnt = RABM_PDCP_ONCE_DEAL_MAX_CNT;
}

/*******************************************************************************
  Module:   RABM_ClearTcDataQ
  Function: ���ز����У����PDCP->RABM���ݶ�������
  Input:    VOS_VOID
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:

*******************************************************************************/
VOS_VOID RABM_ClearTcDataQ(VOS_VOID)
{
    VOS_INT32       lLockKey;
    VOS_UINT32      ulRemainCnt;
    PDCP_RABM_TC_DATA_Q_NODE_STRU *pstNode;

    for(;;)
    {
        lLockKey    = VOS_SplIMP();

        if ( 0 == TTF_Q_CNT(&g_stPdcpRabmTcDataQ.stDataQ) )
        {
            VOS_Splx(lLockKey);
            break;
        }

        VOS_Splx(lLockKey);

        pstNode  = (PDCP_RABM_TC_DATA_Q_NODE_STRU *)TTF_LinkSafeRemoveHead(WUEPS_PID_RABM, &g_stPdcpRabmTcDataQ.stDataQ, &ulRemainCnt);

        TTF_MemFree(WUEPS_PID_RABM, pstNode->pstDataMem);
        RABM_Free(pstNode);

    }
} /* RABM_ClearTcDataQ */

/*****************************************************************************
 �� �� ��  : RABM_ProcessTcPsData
 ��������  : ��������PS�򻷻�����
 �������  : pstNode --- ���ݽڵ�
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��1��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID RABM_ProcessTcPsData(PDCP_RABM_TC_DATA_Q_NODE_STRU *pstNode)
{
    PDCP_RABM_TC_DATA_STRU             *pstDataPacket = VOS_NULL_PTR;
    PDCP_RABM_TC_DATA_STRU              stDataPacket;
    VOS_UINT8                           ucEntId;

    /*���µ�NAS�û���ܹ��£��ǻ���ģʽ���ݲ��پ���RABM����ֱ�ӵ����쳣����*/
    if(RABM_TC_NO_START == g_RabmTcInf.ucTcStartSta)
    {
        RABM_LOG_WARNING("RABM_ProcessTcPsData: Rx Data in not tc mode ");
        TTF_MemFree(WUEPS_PID_RABM, pstNode->pstDataMem);
        RABM_Free(pstNode);
        return;
    }

    /*========����ý��============*/
    /* �ȹ���PDCP_RABM_TC_DATA_STRU���ڲ�����ṹ */
    pstDataPacket = &stDataPacket;
    pstDataPacket->ucRbId       = pstNode->ucRbId;
    pstDataPacket->ulDataBitLen = pstNode->ulDataBitLen;
    pstDataPacket->pstDataMem   = pstNode->pstDataMem;

    /* ����CRC��Ϣ(������PS�򻷻�ģʽ��) */
    (VOS_VOID)mdrv_memcpy(&pstDataPacket->stCrcInfo, &pstNode->stCrcInfo, sizeof(pstNode->stCrcInfo));

    /* RABMģ��ֻ��غͷǻ�����������ֱ���PDCP������ */
    if ( (RABM_TC_LOOP_CLOSE == g_RabmTcInf.ucTcStartSta)
      && (VOS_FALSE == g_RabmTcInf.bFlowCtrlFlg) )
    {
        if (0 == g_RabmTcInf.ucLbCnt)
        {
            RABM_SndTcPsData(0, pstDataPacket);
        }
        else
        {
            for (ucEntId = 0; ucEntId < TC_LB_MAX_RBNUM; ucEntId++)
            {
                if ( (pstDataPacket->ucRbId == g_RabmTcInf.aRbInf[ucEntId].ucRbId)
                  && (RABM_TRUE == g_RabmTcInf.aRbInf[ucEntId].ucEstFlg))
                {
                    RABM_SndTcPsData(ucEntId, pstDataPacket);
                }
            }

            if(ucEntId == g_RabmTcInf.ucLbCnt)
            {
                RABM_LOG1_ERROR("RABM_ProcessTcPsData: Can't find match Rb id <1>",
                                 pstDataPacket->ucRbId);
            }
        }
    }

    if (VOS_NULL_PTR != pstDataPacket->pstDataMem)
    {
        TTF_MemFree(WUEPS_PID_RABM, pstDataPacket->pstDataMem);
    }

    /* �ͷŽ�� */
    RABM_Free(pstNode);

    return;
}

/*******************************************************************************
  Module:   RABM_EnqueueTcData
  Function: ���ز����У����������ݷ���PDCP->RABM���ݶ��У�������дӿյ��ǿգ���������Ϣ֪ͨRABMģ��
  Input:    VOS_VOID
  Output:   VOS_VOID
  NOTE:
  Return:   PS_SUCC   --- �ɹ�
            PS_FAIL   --- ʧ��
  History:
  1.��    ��   : 2012��7��20��
    ��    ��   : L00171473
    �޸�����   : V7R1 C50 GUTL PhaseI����: �ӿں�����Rabm�ļ����Ƶ�UTRANCTRL�ļ���
  2.��    ��   : 2012��12��13��
    ��    ��   : L00171473
    �޸�����   : DTS2012121802573, TQE����
*******************************************************************************/
VOS_UINT32 RABM_EnqueueTcData(PDCP_RABM_TC_DATA_Q_NODE_STRU *pstNode)
{
#if 0
    VOS_UINT32  ulNonEmptyEvent;    /* ��¼�����Ƿ������ɿյ��ǿյ�ת�� */
    TTF_LINK_ST *pstDataQ;
    VOS_UINT32  ulResult;


    ulNonEmptyEvent = PS_FALSE;

    pstDataQ        = &g_stPdcpRabmTcDataQ.stDataQ;

    /*��TTF_MEM_ST���������β��*/
    ulResult    = TTF_LinkSafeInsertTail(WUEPS_PID_RABM, pstDataQ, &(pstNode->stQNode), &ulNonEmptyEvent);
    if(PS_SUCC != ulResult)
    {
        TTF_MemFree(WUEPS_PID_RABM, pstNode->pstDataMem);
        RABM_Free(pstNode);
        RABM_LOG_WARNING("RABM_EnqueueTcData:WARNING:Insert Node fail!");
        return PS_FAIL;
    }

    if (TTF_LINK_CNT(pstDataQ) > g_stPdcpRabmTcDataQ.stStat.ulQMaxCnt)
    {
        g_stPdcpRabmTcDataQ.stStat.ulQMaxCnt = TTF_LINK_CNT(pstDataQ);
    }

    if (PS_TRUE == ulNonEmptyEvent)
    {
        /*��RABM�������ݴ���ָʾ*/
       if (PS_SUCC != NAS_UTRANCTRL_RABM_SendTcDataNotify())
       {
            /* ������Ϣ֪ͨʧ�ܣ���Ҫ����������� */
            RABM_ClearTcDataQ();
            return PS_FAIL;
       }
    }

    /*ͳ����Ϣ*/
    g_stPdcpRabmTcDataQ.stStat.ulDlTotalCnt++;
#else
    RABM_ProcessTcPsData(pstNode);

    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_RABM_GetCurrentSysMode())
    {
        NAS_RABM_INC_FD_DLDATA_CNT();
        NAS_RABM_ProcFastDormStatusInTransfer();
    }
#endif

    return PS_SUCC;
} /* RABM_EnqueueTcData */

/*****************************************************************************
 �� �� ��  : RABM_RcvPsTcDataInd
 ��������  : RABMģ�鴦��PDCP�ϱ���PS�򻷻����ݺ���
 �������  : VOS_VOID  *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2003��12��11��
    ��    ��   : ��־��
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��01��13��
    ��    ��   : A00165503
    �޸�����   : ���ⵥ��: DTS2011011302080���������ݴ����Ż�
  3.��    ��   : 2012��7��20��
    ��    ��   : L00171473
    �޸�����   : V7R1 C50 GUTL PhaseI����: �ӿں�����Rabm�ļ����Ƶ�UTRANCTRL�ļ���
  4.��    ��   : 2013��6��05��
    ��    ��   : Y00213812
    �޸�����   : DTS2013060507591,COVERITY��FORITY�޸�
*****************************************************************************/
VOS_VOID RABM_RcvPsTcDataInd(
                       VOS_VOID  *pMsg                                              /* ��ǰ�������Ϣ                           */
                       )
{
    PDCP_RABM_TC_DATA_STRU         *pstDataPacket;
    PDCP_RABM_TC_DATA_STRU          stDataPacket;
    VOS_UINT8                       ucEntId;
    PDCP_RABM_TC_DATA_Q_NODE_STRU  *pstDataQNode;

    VOS_INT32                       lLockKey;
    VOS_UINT32                      ulDealCnt = 0;
    VOS_UINT32                      ulRemainCnt;

    /*���µ�NAS�û���ܹ��£��ǻ���ģʽ���ݲ��پ���RABM����ֱ�ӵ����쳣����*/
    if(RABM_TC_NO_START == g_RabmTcInf.ucTcStartSta)
    {
        RABM_LOG_WARNING("RABM, RABM_RcvPsTcDataInd, Rx Data in not tc mode ");

        /*��ջ������ݶ���*/
        RABM_ClearTcDataQ();

        /*��ջ������ݶ��е�ͳ������*/
        RABM_Memset(&g_stPdcpRabmTcDataQ.stStat, 0, sizeof(PDCP_RABM_TC_DATA_Q_STAT_STRU));

        return;
    }

    for (;;)
    {
        /*ȡ�������еĽ��*/
        lLockKey = VOS_SplIMP();

        /*������Ϊ�գ���ֱ�ӷ���*/
        if ( 0 == TTF_LINK_CNT(&g_stPdcpRabmTcDataQ.stDataQ) )
        {
            VOS_Splx(lLockKey);
            return;
        }

        VOS_Splx(lLockKey);

        pstDataQNode = (PDCP_RABM_TC_DATA_Q_NODE_STRU *)TTF_LinkSafeRemoveHead(WUEPS_PID_RABM, &g_stPdcpRabmTcDataQ.stDataQ, &ulRemainCnt);

        if (VOS_NULL_PTR == pstDataQNode)
        {
            RABM_LOG_ERROR("ERROR: RABM_RcvPsTcDataInd, pstDataQNode is NULL!");
            return;
        }

        /*========����ý��============*/
        /*�ȹ���PDCP_RABM_TC_DATA_STRU���ڲ�����ṹ*/
        pstDataPacket = &stDataPacket;
        pstDataPacket->ucRbId       = pstDataQNode->ucRbId;
        pstDataPacket->ulDataBitLen = pstDataQNode->ulDataBitLen;
        pstDataPacket->pstDataMem   = pstDataQNode->pstDataMem;

        /*����CRC��Ϣ(������PS�򻷻�ģʽ��)*/
        PS_MEM_CPY(&pstDataPacket->stCrcInfo, &pstDataQNode->stCrcInfo, sizeof(pstDataQNode->stCrcInfo));


        /*RABMģ��ֻ��غͷǻ�����������ֱ���PDCP������*/
        if ( (RABM_TC_LOOP_CLOSE == g_RabmTcInf.ucTcStartSta)
          && (VOS_FALSE == g_RabmTcInf.bFlowCtrlFlg) )
        {
            if (0 == g_RabmTcInf.ucLbCnt)
            {
                RABM_SndTcPsData(0, pstDataPacket);
            }
            else
            {
                for (ucEntId = 0; ucEntId < TC_LB_MAX_RBNUM; ucEntId++)
                {
                    if ( (pstDataPacket->ucRbId == g_RabmTcInf.aRbInf[ucEntId].ucRbId)
                      && (RABM_TRUE == g_RabmTcInf.aRbInf[ucEntId].ucEstFlg))
                    {
                        RABM_SndTcPsData(ucEntId, pstDataPacket);
                        break;
                    }
                }

                if(ucEntId == g_RabmTcInf.ucLbCnt)
                {
                    RABM_LOG1_ERROR("RABM, RABM_RcvPsTcDataInd, Can't find match Rb id <1>",
                                     pstDataPacket->ucRbId);
                }
            }
        }

        if (VOS_NULL_PTR != pstDataPacket->pstDataMem)
        {
            TTF_MemFree(WUEPS_PID_RABM, pstDataPacket->pstDataMem);
        }

        /*�ͷŽ��*/
        RABM_Free(pstDataQNode);

        /*ͳ��*/
        ulDealCnt++;

        if ( ulDealCnt > g_stPdcpRabmTcDataQ.stStat.ulMaxCntOnce )
        {
            g_stPdcpRabmTcDataQ.stStat.ulMaxCntOnce = ulDealCnt;
        }

        /* ����ϴδ���������һ�����ݣ����˳�ѭ�� */
        if (0 == ulRemainCnt)
        {
            return;
        }

        /*���ѭ������Ľ����������˶���һ�����������������
          ���˳�ѭ��������PPP_DATA_PROC_NOTIFY��Ϣ*/
        if ( ulDealCnt >= g_stPdcpRabmTcDataQ.stCfg.ulOnceDealMaxCnt )
        {
            ulDealCnt = 0;

            if (PS_SUCC != NAS_UTRANCTRL_RABM_SendTcDataNotify())
            {
                RABM_LOG_WARNING("RABM_RcvPsTcDataInd: WARNING: WTTF_PDCP_SendTcDataNotifyToRabm FAIL");
                continue;
            }
            else
            {
                return;
            }
        }
    } /* for (;;) */
}

/*******************************************************************************
  Module:   RABM_RcvRrcRabInd
  Function: ����RAB��CN��RABMʵ���״̬��������Ӧ�Ĵ���
  Input:    VOS_VOID    *pMsg           �յ�����Ϣ
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
  1. ��־��      2003.12.11   �¹�����

  2.��    ��   : 2011��12��15��
    ��    ��   : l65478
    �޸�����   : ���ⵥ��:DTS2011110206160 CCO������RABM��WRR����Ϣ������CCO����ʧ��

  3.��    ��   : 2012��3��24��
    ��    ��   : A00165503
    �޸�����   : DTS2012032305582: CMW500���ؽ���ʧ��, RABID�ڻ���ģʽ��ȡֵ
                 ��Χ�������ϸ�

  4.��    ��   : 2012��9��11��
    ��    ��   : A00165503
    �޸�����   : DTS2012080905905: δ����Ƿ�ΪPS��, �����֪ͨCDS�ָ�����

  5.��    ��   : 2013��04��12��
    ��    ��   : l65478
    �޸�����   : DTS2013031901654: ���Ų�������ʧ��

  6.��    ��   : 2013��7��17��
    ��    ��   : A00165503
    �޸�����   : DTS2013071005164: PDP����ɹ���û������, FD����ʧЧ

  7.��    ��   : 2013��8��29��
    ��    ��   : j00174725
    �޸�����   : clean coverity

  8.��    ��   : 2013��12��2��
    ��    ��   : A00165503
    �޸�����   : DTS2013112919549: ʹ��RB_SETUP_REQUEST�е�RAB��Ϣ���
                 RB_SETUP_RSP��Ϣ

  9.��    ��   : 2014��06��16��
    ��    ��   : m00217266
    �޸�����   : modify for FD Optimize

 10.��    ��   : 2015��1��9��
    ��    ��   : A00165503
    �޸�����   : DTS2014123000271: RRC�ͷ���������ֹͣ����
 11.��    ��   : 2015��7��9��
    ��    ��   : A00165503
    �޸�����   : DTS2015071505434:rau��attach���󲻴�follow on������ظ�attach accept��rau accept��Я��follow on proceed��ʶ��gmm��Ҫ
                �����ж����ps rab���ڻ����rabm�ؽ���smҵ�������cds���ڻ�������������T3340����������t3340���������������
*******************************************************************************/
VOS_VOID RABM_RcvRrcRabInd(VOS_VOID *pMsg)
{
    RRRABM_RAB_IND_STRU                *pTempMsg;
    VOS_UINT8                           ucRabNum = 0;
    VOS_UINT8                           i;
    VOS_UINT8                           ucEntId;
    VOS_UINT8                           ucCsRabCnt;
    VOS_UINT32                          ulRabInfoPsDomainFlg;

    ucCsRabCnt = 0;
    pTempMsg = (RRRABM_RAB_IND_STRU *)pMsg;

    ulRabInfoPsDomainFlg = NAS_RABM_IsRabIndPsDonmain(pTempMsg);

    switch(pTempMsg->ulRabChangeType)
    {
    case NAS_RRC_RAB_SETUP_REQUEST:
        for(i = 0; i < pTempMsg->ulRabCnt; i++)
        {
            if(RABM_CN_PS == pTempMsg->aRabInfo[i].ulCnDomainId)
            {
                if ( (RABM_TC_NO_START != g_RabmTcInf.ucTcStartSta)
                  && ((pTempMsg->aRabInfo[i].ulRabId & 0x0f) < RABM_NSAPI_OFFSET) )
                {
                    ucEntId = (VOS_UINT8)(pTempMsg->aRabInfo[i].ulRabId & 0x0f);
                }
                else
                {
                    if ((pTempMsg->aRabInfo[i].ulRabId & 0x0f) < RABM_NSAPI_OFFSET)
                    {
                        continue;
                    }
                    ucEntId = (VOS_UINT8)((pTempMsg->aRabInfo[i].ulRabId & 0x0f)
                        - RABM_NSAPI_OFFSET);
                }

                if(ucEntId >= RABM_PS_MAX_ENT_NUM)
                {
                    ucRabNum = 0;
                    break;
                }
                switch(g_aRabmPsEnt[ucEntId].ucState)
                {
                case RABM_NULL:
                case RABM_NSAPI_ACTIVE_WITH_RAB:
                case RABM_DATA_TRANSFER_STOP:
                case RABM_ACT_PENDING_WITH_RAB:
                case RABM_NSAPI_ACTIVE_PENDING:
                case RABM_NSAPI_ACTIVE_NO_RAB:
                    ucRabNum++;
                    break;
                case RABM_TC_STATE_NULL:
                    ucRabNum++;
                    break;
                default:
                    break;
                }
            }
            else
            {
                ucCsRabCnt++;
                if(ucCsRabCnt > RABM_CS_MAX_ENT_NUM)
                {
                    ucRabNum = 0;
                }
                else
                {
                    ucRabNum++;
                }
            }
            if(0 == ucRabNum)
            {
                break;
            }
        }

        RABM_SndRrcRabRsp(ucRabNum , pTempMsg);
        break;
    case NAS_RRC_RAB_SETUP_SUCCESS:
        RABM_ComSaveRabPara (pTempMsg);

        if (VOS_TRUE == ulRabInfoPsDomainFlg)
        {
            if (VOS_TRUE == NAS_RABM_GET_FD_ACT_FLG())
            {
                /* ��ԭfd�Ĺ���������ʹ�õĸ��ֱ����Ͷ�ʱ�� */
                NAS_RABM_RevertFastDormEnv();

                NAS_RABM_SET_FD_STATUS(NAS_RABM_FASTDORM_DETECT);
                NAS_RabmStartTimer(RABM_TIMER_NAME_FD_FLUX_DETECT,RABM_TIMER_FASTDORM_FLUX_DETECT);

                NAS_RABM_SndOmFastdormStatus();
            }
            else
            {
                NAS_RABM_AbortRelRrcProcedure();
            }
#if (FEATURE_ON == FEATURE_HUAWEI_VP)
            if (VOS_TRUE == NAS_RABM_VoicePreferGetVpStatus())
            {
                /* vp��Чʱ����յ�ps��Ѱ���������緢����rb������ȥ����VP */
                NAS_RABM_VoicePreferSetVpStatus(VOS_FALSE);
                NAS_RABM_SendVpActIndToOtherModule(VOS_FALSE);
            }
#endif

            NAS_RABM_SndGmmRbSetupInd();

        }

        break;
    case NAS_RRC_RAB_SETUP_FAILURE:
        for(i = 0; i < pTempMsg->ulRabCnt; i++)
        {
            if(RABM_CN_PS == pTempMsg->aRabInfo[i].ulCnDomainId)
            {
                if ( (RABM_TC_NO_START != g_RabmTcInf.ucTcStartSta)
                  && ((pTempMsg->aRabInfo[i].ulRabId & 0x0f) < RABM_NSAPI_OFFSET) )
                {
                    ucEntId = (VOS_UINT8)(pTempMsg->aRabInfo[i].ulRabId & 0x0f);
                }
                else
                {
                    if ((pTempMsg->aRabInfo[i].ulRabId & 0x0f) < RABM_NSAPI_OFFSET)
                    {
                        continue;
                    }
                    ucEntId = (VOS_UINT8)((pTempMsg->aRabInfo[i].ulRabId & 0x0f)
                        - RABM_NSAPI_OFFSET);
                }

                if (VOS_TRUE == NAS_RABM_GetWPsEntRabReestFlg(ucEntId))
                {
                    /* ֹͣRB����������ʱ�� */
                    NAS_RABM_StopReestRabPendingTmr(ucEntId + RABM_NSAPI_OFFSET);

                    /* ���RABMʵ����ؽ���ʶ */
                    NAS_RABM_ClearWPsEntRabReestFlg(ucEntId);

                    RABM_RelSaveData(&g_aRabmPsEnt[ucEntId].DlDataSave,RABM_DOWNLINK);/* �ͷŴ洢����������              */
                    g_aRabmPsEnt[ucEntId].ucStpFlg = RABM_FALSE;

                    /* ֪ͨCDS�ͷŻ������� */
                    NAS_RABM_SndCdsFreeBuffDataInd(ucEntId + RABM_NSAPI_OFFSET);
                }
            }
        }

        /*��λ2G��3G�л�ʹ�õ������ָ���־:*/
        if ( VOS_TRUE == gRabm2GTo3GDataResume )
        {
            gRabm2GTo3GDataResume = VOS_FALSE;

            /*�ͷ���2G��3G�л���ʼʱSNDCP���������:*/
            SN_RabmClear2G3Share();
        }

        break;
    case NAS_RRC_RAB_RECONFIG:
        RABM_ComSaveRabPara(pTempMsg);
        break;
    case NAS_RRC_RAB_RELEASE:

        RABM_ComRlsRabReource(pTempMsg);
        for(i = 0; i < pTempMsg->ulRabCnt; i++)
        {
            if(RABM_CN_CS == pTempMsg->aRabInfo[i].ulCnDomainId)
            {
                API_CcSyncInd(D_RMC_RR_ACTION_RELEASE, pTempMsg->aRabInfo[i].ulRabId);
            }
        }

        break;
    default:
        break;
    }

    return;
}


/*******************************************************************************
  Module:   RABM_RcvRrcRelAllReq
  Function: RRC�����쳣,ָʾRABM�ͷ�����RAB
  Input:    VOS_VOID
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
    1. L47619      2007.03.27   Modified for MAPS3000

  2.��    ��   : 2011��12��19��
    ��    ��   : o00132663
    �޸�����   : PS�ں���Ŀ���յ�WRR��RAB�����ͷ���Ϣ��֪ͨCDS�ͷ�����

  3.��    ��   : 2012��6��15��
    ��    ��   : A00165503
    �޸�����   : DTS2012061401093: �����ҵ��ʱ, RABM����RB�ͷŵ��߼�����,
                 �п��ܵ���ҵ���ж�

  4.��    ��   : 2012��8��22��
    ��    ��   : A00165503
    �޸�����   : RABM�����QOS�ɶ�̬�ڴ��Ϊ��̬����
  5.��    ��   : 2013��04��12��
    ��    ��   : l65478
    �޸�����   : DTS2013031901654:���Ų�������ʧ��
*******************************************************************************/
VOS_VOID RABM_RcvRrcRelAllReq(VOS_VOID)
{
    VOS_UINT8                           ucEntId;
    VOS_UINT8                           ucChgMask;

    if( RABM_FALSE != g_ucReestTimerFlg )
    {
        RABM_TimerStop(0);
        NAS_RabmStopTimer(RABM_TIMER_NAME_COMMON, RABM_TIMER_RESEND_EST_REQ);
        g_ucReestTimerFlg = RABM_FALSE;
    }

    /*�ͷ�PS�������RAB*/
    for ( ucEntId = 0; ucEntId < RABM_PS_MAX_ENT_NUM; ucEntId++ )
    {
        switch(g_aRabmPsEnt[ucEntId].ucState)
        {
            case RABM_NULL:
            case RABM_NSAPI_ACTIVE_PENDING:
                break;
            case RABM_NSAPI_ACTIVE_NO_RAB:
                if (VOS_TRUE == NAS_RABM_GetWPsEntRabReestFlg(ucEntId))
                {
                    /* ֹͣRB����������ʱ�� */
                    NAS_RABM_StopReestRabPendingTmr(ucEntId + RABM_NSAPI_OFFSET);

                    /* ���RABMʵ����ؽ���ʶ */
                    NAS_RABM_ClearWPsEntRabReestFlg(ucEntId);

                    /* ֪ͨCDS�ͷŻ������� */
                    NAS_RABM_SndCdsFreeBuffDataInd(ucEntId + RABM_NSAPI_OFFSET);
                }
                break;
            case RABM_NSAPI_ACTIVE_WITH_RAB:
            case RABM_DATA_TRANSFER_STOP:
                if ( ((g_aRabmPsEnt[ucEntId].QoS.aucQosValue[3] & NAS_RABM_QOS_TRAFFIC_CLASS_MASK) == RABM_CONVERSATION_CLASS)
                  || ((g_aRabmPsEnt[ucEntId].QoS.aucQosValue[3] & NAS_RABM_QOS_TRAFFIC_CLASS_MASK) == RABM_STREAM_CLASS) )
                {
                    RABM_SndSmDeactReq((VOS_UINT8)(ucEntId + RABM_NSAPI_OFFSET));
                }
                g_aRabmPsEnt[ucEntId].RabInfo.ucRabId = 0xff;
                g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum = 0;
                RABM_SetWState(ucEntId, RABM_NSAPI_ACTIVE_NO_RAB);
                PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_RcvRrcRelAllReq:NORMAL:RABM state = RABM_NSAPI_ACTIVE_NO_RAB");

                /*����RAB_MAP���е�ucAsId*/
                ucChgMask = 0;
                ucChgMask |= RAB_MAP_CHG_MASK_AS_ID;
                RABM_ChgRabMap(ucEntId + RABM_NSAPI_OFFSET,
                               ucChgMask,
                               g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[0],
                               VOS_NULL_PTR,
                               VOS_NULL_PTR);
                break;
            case RABM_ACT_PENDING_WITH_RAB:
                RABM_SetWState(ucEntId, RABM_NSAPI_ACTIVE_PENDING);
                PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_RcvRrcRelAllReq:NORMAL:RABM state: RABM_ACT_PENDING_WITH_RAB ==> RABM_NSAPI_ACTIVE_PENDING");
                g_aRabmPsEnt[ucEntId].RabInfo.ucRabId = 0xff;
                g_aRabmPsEnt[ucEntId].RabInfo.ucRbNum = 0;

                /*����RAB_MAP���е�ucAsId*/
                ucChgMask = 0;
                ucChgMask |= RAB_MAP_CHG_MASK_AS_ID;
                RABM_ChgRabMap(ucEntId + RABM_NSAPI_OFFSET,
                               ucChgMask,
                               g_aRabmPsEnt[ucEntId].RabInfo.aucRbId[0],
                               VOS_NULL_PTR,
                               VOS_NULL_PTR);
                break;
            case RABM_TC_STATE_NULL:
                break;
            default:
                break;
        }

        g_aRabmPsEnt[ucEntId].ucStpFlg = RABM_FALSE;
        if(0 != g_aRabmPsEnt[ucEntId].DlDataSave.ucNum)
        {
            /* �ͷŴ洢����������                       */
            RABM_RelSaveData(&g_aRabmPsEnt[ucEntId].DlDataSave, RABM_DOWNLINK);
        }
    }

    /*�ͷ�CS�������RAB*/
    for ( ucEntId = 0; ucEntId < RABM_CS_MAX_ENT_NUM; ucEntId++ )
    {
        switch(g_aRabmCsEnt[ucEntId].ucState)
        {
            case RABM_NULL:
                break;
            case RABM_SI_ACTIVE_WITH_RAB:
                RABM_SndCcSyncInd(RABMCC_RAB_INACTIVE,
                    (VOS_UINT32)g_aRabmCsEnt[ucEntId].RabInfo.ucRabId);
                g_aRabmCsEnt[ucEntId].ucState = RABM_NULL;
                PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_RcvRrcRelAllReq:NORMAL:RABM state: RABM_SI_ACTIVE_WITH_RAB ==> RABM_NULL ");
                g_aRabmCsEnt[ucEntId].RabInfo.ucRabId = 0xff;
                g_aRabmCsEnt[ucEntId].RabInfo.ucRbNum = 0;
                break;
            default:
                break;
        }
    }

    /*�ͷ�TC��LBʵ��*/
    if(RABM_TC_NO_START != g_RabmTcInf.ucTcStartSta)
    {
        for ( ucEntId = 0; ucEntId < g_RabmTcInf.ucLbCnt; ucEntId++ )
        {
            if(RABM_TRUE == g_RabmTcInf.aRbInf[ucEntId].ucEstFlg)
            {
                g_RabmTcInf.aRbInf[ucEntId].ucEstFlg = RABM_FALSE;                    /* ��־��RB������                           */
                RABM_SndTcRabInd(ucEntId, TC_RAB_RELEASE);                            /* ֪ͨTC��RB�ͷ�                           */
            }
        }
    }

    NAS_RABM_SuspendFastDorm();

    return;
}


/*******************************************************************************
  Module:   RABM_RcvPsDataReq
  Function: ����PS��RABMʵ���״̬��������Ӧ�Ĵ���
  Input:    VOS_VOID    *pMsg           �յ�����Ϣ
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1. ��־��      2003.12.11   �¹�����
*******************************************************************************/
VOS_VOID RABM_RcvPsDataReq(
                       VOS_VOID  *pMsg
                       )
{
    NAS_WARNING_LOG(WUEPS_PID_RABM,
        "RABM_RcvPsDataReq: Receive data in wrong state!");

    /*ֱ�Ӷ������������ݿ�:*/
    TTF_MemFree(WUEPS_PID_RABM, ((TAFRABM_PS_DATA_REQ_STRU *)pMsg)->pData);
}

/*******************************************************************************
  Module:   RABM_RcvCsDataReq
  Function: ����CS��RABMʵ���״̬��������Ӧ�Ĵ���
  Input:    VOS_VOID    *pMsg           �յ�����Ϣ
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1. ��־��      2003.12.11   �¹�����
*******************************************************************************/
VOS_VOID RABM_RcvCsDataReq(
                       VOS_VOID  *pMsg
                       )
{
    VOS_UINT8  ucSi;
    VOS_UINT8  ucEntId;
    VOS_UINT16 usDataLen;

    usDataLen = 0;
    ucSi = (VOS_UINT8)(((TAFRABM_CS_DATA_REQ_STRU *)pMsg)->ulSi);                   /* �õ���Ϣ�е�SI                           */
    ucEntId = g_aucSiMapEnt[ucSi];                                              /* ���ʵ��ID                               */
    if( 0xFF == ucEntId )
    {
        RABM_SndTafInActSiInd(ucSi);                                            /* ��APP�ش���ָʾ                          */
        return;
    }

    switch(g_aRabmCsEnt[ucEntId].ucState)
    {                                                                           /* ����ʵ���״̬������Ӧ�Ĵ���             */
    case RABM_NULL:
        RABM_SndTafInActSiInd(ucSi);                                            /* ��APP�ش���ָʾ                          */
        break;
    case RABM_SI_ACTIVE_WITH_RAB:
        usDataLen = (VOS_UINT16)((TAFRABM_CS_DATA_REQ_STRU *)pMsg)->ulDataLen;      /* usDataLenΪ�ֽڳ���                      */
        (VOS_VOID)NAS_CsDomainDataReq((VOS_INT8)(g_aRabmCsEnt[ucEntId].RabInfo.aucRbId[0]),
            usDataLen,
            ((TAFRABM_CS_DATA_REQ_STRU *)pMsg)->aucData);
        break;
    default:
        break;
    }
    return;
}

/*******************************************************************************
  Module:   RABM_RcvRlcDataInd
  Function: ��rlc���ݵĴ���
  Input:    RABMRLC_CS_DATA_IND_STRU *pRcvData
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   ��־��      2003.12.09   �¹�����
      2.   L47619      2006.06.12   ���ⵥ:A32D04258
*******************************************************************************/
VOS_VOID RABM_RcvRlcDataInd(
                        RLC_RABM_CS_DATA_IND_STRU  *pRcvData
                        )
{
    VOS_UINT8    i;
    VOS_UINT8    j;
    VOS_UINT8    ucDataValid;


    if (RABM_TC_NO_START != g_RabmTcInf.ucTcStartSta)
    {
        if (RABM_TC_LOOP_CLOSE == g_RabmTcInf.ucTcStartSta)
        {
            if (0 == g_RabmTcInf.ucLbCnt)
            {
                RABM_SndTcCsData(0, pRcvData);
            }
            else
            {
                for (i = 0; i < TC_LB_MAX_RBNUM; i++)
                {
                    if ( (pRcvData->ucRbId == g_RabmTcInf.aRbInf[i].ucRbId)
                      && (RABM_TRUE == g_RabmTcInf.aRbInf[i].ucEstFlg))
                    {
                        RABM_SndTcCsData(i, pRcvData);
                    }
                }
            }
        }


        RABM_RlcFree(pRcvData->pucData);

        return;
    }
    ucDataValid = RABM_FALSE;                                                   /* ��ʼ��Ϊ������Ч                         */
    for(i = 0; i < RABM_CS_MAX_ENT_NUM; i++)
    {
        for(j = 0; j < g_aRabmCsEnt[i].RabInfo.ucRbNum; j++)
        {
            if(g_aRabmCsEnt[i].RabInfo.aucRbId[j] == ((VOS_UINT8)pRcvData->ucRbId))
            {
                ucDataValid = RABM_TRUE;                                        /* ����������Ч                             */
                RABM_SndTafCsDataInd(pRcvData, i);                              /* ��APP��������                            */
                break;
            }
        }
        if(ucDataValid == RABM_TRUE)
        {
            break;
        }
    }

    RABM_RlcFree(pRcvData->pucData);

    return;
}



/*******************************************************************************
  Module:   RABM_RcvTcTestReq
  Function: �յ�TC���Լ���/ȥ������Ϣ�Ĵ���
  Input:    TCRABM_TEST_REQ_STRU *pRcvMsg
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
  1.   ��־��      2004.05.09   �¹�����
  2.   l47619      2006.08.21   ���ⵥ: A32D05592
  3.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����
*******************************************************************************/
VOS_VOID RABM_RcvTcTestReq(
                       TCRABM_TEST_REQ_STRU  *pRcvMsg
                       )
{
    VOS_UINT8            *pMsg;
    TCRABM_TEST_CNF_STRU *pSndMsg;
    VOS_UINT8    i;
    VOS_UINT8    j;
    VOS_UINT8    ucRbCnt;
    pMsg = (VOS_UINT8 *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_RABM,
                                            sizeof(TCRABM_TEST_CNF_STRU));
    if (VOS_NULL_PTR == pMsg)
    {
        PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_ERROR, "RABM_RcvTcTestReq:ERROR:Alloc msg fail!");
        return;
    }
    pSndMsg = (TCRABM_TEST_CNF_STRU *)pMsg;

    pSndMsg->ulRabCnt = 0;                                                      /* ��ʼ��RAB�ĸ���                          */

    if(TC_RB_TEST_ACTIVE == pRcvMsg->ulMode)
    {
        g_RabmTcInf.ucTcStartSta = RABM_TC_LOOP_OPEN;                           /* ��¼TC�Ѿ�����                           */
        for(i = 0; i < RABM_PS_MAX_ENT_NUM; i++)
        {                                                                       /* ����PS���RB��Ϣ                         */
            if(RABM_NULL == g_aRabmPsEnt[i].ucState)
            {                                                                   /* RB��û�н���                             */
                RABM_SetWState(i, RABM_TC_STATE_NULL);                          /* ��ʶ���Խ�������TC���Ե�RB               */
                PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_RcvTcTestReq:NORMAL:RABM state: RABM_NULL ==> RABM_TC_STATE_NULL");
            }
            else if((RABM_NSAPI_ACTIVE_WITH_RAB == g_aRabmPsEnt[i].ucState)
                || (RABM_ACT_PENDING_WITH_RAB == g_aRabmPsEnt[i].ucState))
            {                                                                   /* RB�Ѿ�����                               */
                pSndMsg->aRabInfo[pSndMsg->ulRabCnt].ulCnDomainId = RABM_CN_PS; /* ��¼��PS���RB                           */
                pSndMsg->aRabInfo[pSndMsg->ulRabCnt].ulRbId =
                    g_aRabmPsEnt[i].RabInfo.aucRbId[0];                         /* ��¼RB ID                                */
                pSndMsg->aRabInfo[pSndMsg->ulRabCnt].ulRabId =
                    g_aRabmPsEnt[i].RabInfo.ucRabId;                            /* ��¼RAB ID                               */
                pSndMsg->ulRabCnt++;                                            /* ����RB�ĸ���                             */
            }
            else
            {
            }
        }
        for(i = 0; i < RABM_CS_MAX_ENT_NUM; i++)
        {                                                                       /* ����CS���RB��Ϣ                         */
            if(RABM_NULL == g_aRabmCsEnt[i].ucState)
            {                                                                   /* RB��û�н���                             */
                g_aRabmCsEnt[i].ucState = RABM_TC_STATE_NULL;
                PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_RcvTcTestReq:NORMAL:RABM state: RABM_NULL ==> RABM_TC_STATE_NULL");
            }
            if(RABM_SI_ACTIVE_WITH_RAB == g_aRabmCsEnt[i].ucState)
            {                                                                   /* RB�Ѿ�����                               */
                if(g_aRabmCsEnt[i].RabInfo.ucRbNum > 1)
                {                                                               /* ��RAB��Ӧ��RB����һ��                    */
                    continue;
                }
                pSndMsg->aRabInfo[pSndMsg->ulRabCnt].ulCnDomainId = RABM_CN_CS; /* ��¼��CS���RB                           */
                pSndMsg->aRabInfo[pSndMsg->ulRabCnt].ulRbId =
                    g_aRabmCsEnt[i].RabInfo.aucRbId[0];                         /* ��¼RB ID                                */
                pSndMsg->aRabInfo[pSndMsg->ulRabCnt].ulRabId =
                    g_aRabmCsEnt[i].RabInfo.ucRabId;                            /* ��¼RAB ID                               */
                pSndMsg->ulRabCnt++;
            }
        }

        ucRbCnt = (VOS_UINT8)(pSndMsg->ulRabCnt);
        for(i = 0; i < TC_LB_MAX_RBNUM; i++)
        {


            for(j = 0; j < ucRbCnt; j++)
            {
                if(pSndMsg->ulRabCnt >= (TC_LB_MAX_RBNUM))
                {
                    break;
                }

                if(g_RabmTcInf.aRbInf[i].ucRbId != pSndMsg->aRabInfo[i].ulRbId)
                {
                    pSndMsg->aRabInfo[pSndMsg->ulRabCnt].ulCnDomainId
                        = g_RabmTcInf.aRbInf[i].ucDomain;
                    pSndMsg->aRabInfo[pSndMsg->ulRabCnt].ulRbId
                        = g_RabmTcInf.aRbInf[i].ucRbId;
                    pSndMsg->aRabInfo[pSndMsg->ulRabCnt].ulRabId
                        = g_RabmTcInf.aRbInf[i].ucRabId;
                    pSndMsg->ulRabCnt++;
                }
            }
        }
    }
    else
    {
        g_RabmTcInf.ucTcStartSta = RABM_TC_NO_START;                            /* ��¼TC�Ѿ�ֹͣ                           */
        for(i = 0; i < RABM_PS_MAX_ENT_NUM; i++)
        {
            if(RABM_TC_STATE_NULL == g_aRabmPsEnt[i].ucState)
            {
                RABM_SetWState(i, RABM_NULL);                                   /* �ָ���TC����ǰ��״̬                     */
                PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_RcvTcTestReq:NORMAL:RABM state: RABM_TC_STATE_NULL ==> RABM_NULL ");
            }
        }
        for(i = 0; i < RABM_CS_MAX_ENT_NUM; i++)
        {
            if(RABM_TC_STATE_NULL == g_aRabmCsEnt[i].ucState)
            {
                g_aRabmCsEnt[i].ucState = RABM_NULL;                            /* �ָ���TC����ǰ��״̬                     */
                PS_NAS_LOG(WUEPS_PID_RABM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "RABM_RcvTcTestReq:NORMAL:RABM state: RABM_TC_STATE_NULL ==> RABM_NULL");
            }
        }
        for(i = 0; i < TC_LB_MAX_RBNUM; i++)
        {
            g_RabmTcInf.aRbInf[i].ucEstFlg = RABM_FALSE;
            g_RabmTcInf.aRbInf[i].ulRlcSduSize = 0;
            g_RabmTcInf.aRbInf[i].bRlcSduSizeValid = VOS_TRUE;
        }

        g_RabmTcInf.ucLbCnt = 0;
    }

    RABM_SndTcTestCnf(pSndMsg);
}

/*****************************************************************************
 �� �� ��  : RABM_RcvTcTestLoopReq
 ��������  : �յ�TC���Ի�����/�ر���Ϣ�Ĵ���
 �������  : TCRABM_TEST_LOOP_REQ_STRU *pRcvMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2004��5��9��
    ��    ��   : ��־��
    �޸�����   : �����ɺ���

  2.��    ��   : 2006��1��10��
    ��    ��   : L47619
    �޸�����   : ���ⵥ: A32D01571

  3.��    ��   : 2004��5��9��
    ��    ��   : A00165503
    �޸�����   : ���ⵥ��: DTS2010120604951��CMU 2ms �ش���20%����

  4.��    ��   : 2011��01��13��
    ��    ��   : A00165503
    �޸�����   : ���ⵥ��: DTS2011011302080���������ݴ����Ż�

*****************************************************************************/
VOS_VOID RABM_RcvTcTestLoopReq(TCRABM_TEST_LOOP_REQ_STRU *pRcvMsg)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j,k;
    VOS_UINT8                           ucRbFlg;                                /* ��־�Ƿ��ҵ���ͬ��rb                     */
    VOS_UINT8                           aucRbId[TC_LB_MAX_RBNUM];
    VOS_UINT8                           aucDomain[TC_LB_MAX_RBNUM];
    VOS_UINT8                           ucEstCnt = 0;

    PS_MEM_SET( aucRbId, (VOS_CHAR)0xff, TC_LB_MAX_RBNUM );
    PS_MEM_SET( aucDomain, (VOS_CHAR)0xff, TC_LB_MAX_RBNUM);

    if (TC_LOOP_CLOSE == pRcvMsg->ulMode)
    {
        g_RabmTcInf.ucTcStartSta = RABM_TC_LOOP_CLOSE;                          /* ��¼TC�Ѿ�����                           */
        g_RabmTcInf.ucLbCnt = (VOS_UINT8)(pRcvMsg->ulRBNum);

        g_RabmTcInf.ucTestLoopMode = pRcvMsg->ucTestLoopMode;

        if (0 != pRcvMsg->ulRBNum)
        {
            ucEstCnt = 0;
            for (j = 0; j < TC_LB_MAX_RBNUM; j++)
            {
                if (RABM_TRUE == g_RabmTcInf.aRbInf[j].ucEstFlg)
                {
                    aucRbId[ucEstCnt] = g_RabmTcInf.aRbInf[j].ucRbId;
                    aucDomain[ucEstCnt] = g_RabmTcInf.aRbInf[j].ucDomain;
                    ucEstCnt++;
                }
            }

            for (i = 0; i < TC_LB_MAX_RBNUM; i++)
            {
                ucRbFlg = RABM_FALSE;

                for (j = 0; j < pRcvMsg->ulRBNum; j++)
                {
                    if (g_RabmTcInf.aRbInf[i].ucRbId == pRcvMsg->aLBIdList[j].ulRBID)
                    {
                        g_RabmTcInf.aRbInf[i].ulRlcSduSize
                            = pRcvMsg->aLBIdList[j].ulUpRlcSduSize;             /* ��¼����SDU�Ĵ�С                        */
                        if (0 == g_RabmTcInf.aRbInf[i].ulRlcSduSize)
                        {
                            g_RabmTcInf.aRbInf[i].bRlcSduSizeValid = VOS_FALSE;
                        }
                    }
                }

                for(j = 0; j < RABM_PS_MAX_ENT_NUM; j++)
                {
                    if((RABM_NSAPI_ACTIVE_WITH_RAB == g_aRabmPsEnt[j].ucState)
                        || (RABM_ACT_PENDING_WITH_RAB
                            == g_aRabmPsEnt[j].ucState))
                    {
                        for ( k = 0; k < g_aRabmPsEnt[j].RabInfo.ucRbNum; k++ )
                        {
                            if(g_RabmTcInf.aRbInf[i].ucRbId
                                        == g_aRabmPsEnt[j].RabInfo.aucRbId[k])
                            {                                                       /* ��RB��PS��ģ����Ѿ�����                 */
                                g_RabmTcInf.aRbInf[i].ucEstFlg = RABM_TRUE;         /* ��־��RB�Ѿ�������־                     */
                                g_RabmTcInf.aRbInf[i].ucDomain = RABM_CN_PS;
                                ucRbFlg = RABM_TRUE;
                                break;
                            }
                        }
                        if ( RABM_TRUE == ucRbFlg )
                        {
                            break;
                        }
                    }
                }
                if(RABM_FALSE == ucRbFlg)
                {                                                               /* PS��û���ҵ���Ӧ��RB��Ϣ                 */
                    for(j = 0; j < RABM_CS_MAX_ENT_NUM; j++)
                    {
                        if(RABM_SI_ACTIVE_WITH_RAB == g_aRabmCsEnt[j].ucState)
                        {
                            for ( k = 0; k < g_aRabmCsEnt[j].RabInfo.ucRbNum; k++ )
                            {
                                if(g_aRabmCsEnt[j].RabInfo.aucRbId[k]
                                    == g_RabmTcInf.aRbInf[i].ucRbId)
                                {                                                   /* ��RB��CS��ģ����Ѿ�����                 */
                                    g_RabmTcInf.aRbInf[i].ucEstFlg = RABM_TRUE;     /* ��־��RB�Ѿ�������־                     */
                                    g_RabmTcInf.aRbInf[i].ucDomain = RABM_CN_CS;
                                    ucRbFlg = RABM_TRUE;
                                    break;
                                }
                            }
                            if ( RABM_TRUE == ucRbFlg )
                            {
                                break;
                            }
                        }
                    }
                }
            }
            for(i = 0; i < ucEstCnt; i++)
            {
                for(j = 0; j < g_RabmTcInf.ucLbCnt; j++)
                {
                    if(aucRbId[i] == g_RabmTcInf.aRbInf[j].ucRbId)
                    {
                        g_RabmTcInf.aRbInf[j].ucEstFlg = RABM_TRUE;             /* ��־��RB�Ѿ�������־                     */
                        g_RabmTcInf.aRbInf[j].ucDomain = aucDomain[i];
                        break;
                    }
                }
            }
        }
        else
        {
            for(i = 0; i < TC_LB_MAX_RBNUM; i++)
            {
                g_RabmTcInf.aRbInf[i].ulRlcSduSize = 0;
            }
        }
    }
    else
    {
        g_RabmTcInf.ucTcStartSta = RABM_TC_LOOP_OPEN;                           /* ��¼TC�Ѿ��ر�                           */
        g_RabmTcInf.bFlowCtrlFlg = VOS_FALSE;                                   /* ��¼TC�Ѿ��ر�                           */

        for (i = 0; i < TC_LB_MAX_RBNUM; i++)
        {
            g_RabmTcInf.aRbInf[i].ulRlcSduSize = 0;
            g_RabmTcInf.aRbInf[i].bRlcSduSizeValid = VOS_TRUE;
        }

        /*��ջ������ݶ���*/
        RABM_ClearTcDataQ();

        /*��ջ������ݶ��е�ͳ������*/
        RABM_Memset(&g_stPdcpRabmTcDataQ.stStat, 0, sizeof(PDCP_RABM_TC_DATA_Q_STAT_STRU));
    }

    RABM_SndTcTestLoopCnf();
}

/*****************************************************************************
 �� �� ��  : NAS_RABM_SetTcFlowCtrl
 ��������  : ���û������ر�־
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��1��11��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_RABM_SetTcFlowCtrl(VOS_VOID)
{
    g_RabmTcInf.bFlowCtrlFlg = VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_RABM_ClearTcFlowCtrl
 ��������  : ����������ر�־
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��1��11��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_RABM_ClearTcFlowCtrl(VOS_VOID)
{
    g_RabmTcInf.bFlowCtrlFlg = VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_RABM_IsRabIndPsDonmain
 ��������  : �ж�RRRABM_RAB_IND��Ϣ���Ƿ����PS���RAB��Ϣ
 �������  : pstRrcRabInd - RRRABM_RAB_IND��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE     - ����PS��RAB��Ϣ
             VOS_FALSE    - ������PS��RAB��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_RABM_IsRabIndPsDonmain(
    RRRABM_RAB_IND_STRU                *pstRrcRabInd
)
{
    VOS_UINT32                          ulCnt;

    for (ulCnt = 0; ulCnt < pstRrcRabInd->ulRabCnt; ulCnt++)
    {
        if (RABM_CN_PS == pstRrcRabInd->aRabInfo[ulCnt].ulCnDomainId)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

