/************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : MmGsmDifMsg.c
  Author       : s46746
  Version      : V200R001
  Date         : 2005-08-19
  Description  : ��C�ļ�������MMģ��GSM�в�����Ϣ��ʵ��
  Function List:
        1) MM_AnalyNtModeofSysInfo
        2) MM_AnalyRacofSysInfo
        3) MM_ChangeRegState
        4) MM_GasAttachReq
        5) MM_GasDelKeyReq
        6) MM_GasRrAbortReq
        7) MM_GasRrDataReq
        8) MM_GasRrEstReq
        9) MM_GasRrRelReq
       10) MM_GasSecurityKeyChgReq
       11) MM_GasTmsiLaiChgReq
       12) MM_GasUsimStatusReq
       13) MM_GetSecurityInfo
       14) MM_NasSendGasMsg
       15) MM_RcvGsmRrcPagingInd
       16) MM_RcvGsmRrcSyncInd
       17) MM_RcvMmcGsmSysInfoInd

  History      :
  1. Date:
     Author: ---
     Modification:Create
  2. Date:
     Author: ---
     Modification:Add function ... ���ⵥ��:
  3. s46746 2006-03-14 �������ⵥA32D02479�޸�
  4. s46746 2006-03-29  �������ⵥA32D02486�޸�
  5. s46746 2006-03-31  �������ⵥA32D02790�޸�
  6. x51137  2006/4/14 A32D02955
  7. l40632  2006-07-07  �������ⵥA32D04776�޸�
  8. s46746  2006-07-27 �������ⵥA32D03975�޸�
  9. x51137  2006/11/2  A32D06628
 10. ��    ��   : 2006��11��22��
     ��    ��   : s46746
     �޸�����   : ���ⵥ��:A32D07372
 11.��    ��   : 2007��03��30��
    ��    ��   : luojian 60022475
    �޸�����   : Maps3000�ӿ��޸�
 12.��    ��   : 2007��9��21��
    ��    ��   : luojian id:107747
    �޸�����   : ���ⵥ�ţ�AT2D01703,MMCMM_COMBINED_RAU_ACCEPTED��Ϣ����
                 RealFlag��־
 13.��    ��   : 2007��9��27��
    ��    ��   : s46746
    �޸�����   : ������Ч��Ϣ��RRMM_NAS_INFO_CHANGE��Ϣ���õ�
 14.��    ��   : 2008��05��13��
    ��    ��   : luojian id:107747
    �޸�����   : �������ⵥ�ţ�AT2D03371,MM IDLE ATTEMPTING TO UPDATE״̬��
                 LAI�ı����̷���LAU.
 15.��    ��   : 2008��05��13��
    ��    ��   : luojian id:107747
    �޸�����   : �������ⵥ�ţ�AT2D03612,MM_GasRrEstReq IDDN����û�г�ʼֵ
 16.��    ��   : 2008��7��25��
    ��    ��   : luojian 00107747
    �޸�����   : �������ⵥ��AT2D04142/AT2D04677,�޸�RAU ATTEMPT��������5�εĴ���
 17.��    ��   : 2008��12��02��
    ��    ��   : x00115505
    �޸�����   : AT2D07170:CREG,CGREG�����ϱ�����
 18.��    ��   : 2009��07��17��
   ��    ��   : z40661
   �޸�����   : AT2D12971,��֧��EDGE������ģʽI��С����ѡ��֧��EDGE������ģʽII��С��ʧ��
 19.��    ��   : 2009��8��14��
    ��    ��   : f62575
    �޸�����   : AT2D13631, CS���Ž���ʧ�ܵ����⣬CS�����Է�����ʱ�����ͳɹ������ǽ���ʱ�ظ�CP error��ԭ����msg not compatible with protocl state

************************************************************************/

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "MM_Inc.h"
#include "MmGsmDifMsg.h"


#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_GSMDIFMSG_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/



/*****************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/

/* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-4, begin */

/* Deleted by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-4, end */

/*lint -save -e958 */


/*****************************************************************************
 Prototype      : MM_RcvGsmRrcPagingInd
 Description    : GSM �� Paging ��Ϣ�ṹ�Ĵ���
 Input          : pRcvMsg �յ���ԭ��ͷָ��
 Output         :
 Return Value   : MM_TRUE ��Ϣ���ճɹ�
                  MM_FALSE ��Ϣ����ʧ��
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2005-08-19
    Author      : s46746
    Modification: Created function
*****************************************************************************/
VOS_UINT8 MM_RcvGsmRrcPagingInd(VOS_VOID *pRcvMsg)
{

    /* ����ֵ���� */
    VOS_UINT8                           ucRet = MM_TRUE;

    /* ������յ�����Ϣ����ָ�� */
    GRRMM_PAGING_IND_ST                *pMsg;

    /* ��Ϣת�� */
    pMsg = (GRRMM_PAGING_IND_ST *)pRcvMsg;

    /* ����Ϣ�Ϸ��Լ�� */
    if ((MM_CONST_NUM_1 < pMsg->ucPagingType)
        || (MM_CONST_NUM_2 < pMsg->ucMSIDType)) /* ��Ϣ�е�ȡֵ���Ϸ� */
    {
        /* ������Ϣ���ʧ�� */
        ucRet = MM_FALSE;

        /* ��ӡ������Ϣ */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_RcvGsmRrcPagingInd: ERROR: Receive GRRMM_PAGING_IND error.");

    }
    else /* ��Ϣ�Ϸ� */
    {
        /* �洢��Ϣ�������Ϣ */
        if ((GAS_TMSI == pMsg->ucMSIDType)
            || (GAS_PTMSI == pMsg->ucMSIDType)) /* ��������Ϊ GAS_TMSI �� GAS_PTMSI */
        {
            /* ����ȫ�ֺ�������Ϊ MM_TMSI_PAGING */
            g_MmGlobalInfo.ucPagingRecordTypeId = MM_TMSI_PAGING;
        }
        else if (GAS_IMSI == pMsg->ucMSIDType) /* ��������Ϊ GAS_IMSI */
        {
            /* ����ȫ�ֺ�������Ϊ MM_IMSI_PAGING */
            g_MmGlobalInfo.ucPagingRecordTypeId = MM_IMSI_PAGING;
        }
        else
        {

        }
    }

    /* ���ؼ���� */
    return ucRet;
}

/* 4 GSM��Ϣ GAS_RR_SYNC_IND ��ʵ�� */
/* �޸� MAPS1000 �к��� Mm_RcvRrcSyncInd */
/*VOS_UINT8 Mm_RcvRrcSyncInd(void *pRcvMsg             �յ���ԭ��ͷָ�� * ) */
/* ���ļ� Mm_Rcv.c                                                            */

/*****************************************************************************
 Prototype      : MM_RcvGsmRrcSyncInd
 Description    : GSM �� sync ��Ϣ�ṹ�Ĵ���
 Input          : pRcvMsg  �յ���ԭ��ͷָ��
 Output         :
 Return Value   : MM_TRUE ��Ϣ���ճɹ�
                  MM_FALSE ��Ϣ����ʧ��
 Calls          :
 Called By      :

 History        : ---
  1.Date        : 2005-08-19
    Author      : s46746
    Modification: Created function
*****************************************************************************/
VOS_UINT8 MM_RcvGsmRrcSyncInd(VOS_VOID *pRcvMsg)
{

    /* ����ֵ���� */
    VOS_UINT8                           ucRet = MM_TRUE;

    /* ������յ�����Ϣ����ָ�� */
    GAS_RR_SYNC_IND_ST                 *pMsg;

    /* ��Ϣת�� */
    pMsg = (GAS_RR_SYNC_IND_ST *)pRcvMsg;

    /* ��ͬ����Ϣ�ķ������� */
    if (RR_SYN_CIPH == pMsg->ucSynCause) /* �����Ѿ����� */
    {
        g_RrMmSyncInd.ulRabCnt                              = MM_CONST_NUM_0;

        g_MmGlobalInfo.CsSecutityInfo.ucSecurityType        = RR_SYN_CIPH;

        /*g_MmGlobalInfo.CsSecutityInfo.ucSecutityFlg         = RRC_CIPHER_START;*/

        /* ���� ucSynValue ����ȫ�ּ����㷨 */
        g_MmGlobalInfo.ucCsCipherAlgor                      = pMsg->ucSynValue;
    }
#if 0
    else if (RR_SYN_TCH == pMsg->ucSynCause) /* ҵ��ͨ���Ѿ�ָ�� */
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_NORMAL,
                    "MM_RcvGsmRrcSyncInd: NORMAL: Sync channal mode res.");

        g_MmGlobalInfo.CsSecutityInfo.ucSecurityType        = RR_SYN_TCH;
    }
    else if (RR_SYN_TCH_MODIFY == pMsg->ucSynCause) /* ҵ��ͨ��ģʽ�޸� */
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_NORMAL,
                    "MM_RcvGsmRrcSyncInd: NORMAL: Sync channal mode change.");

        g_MmGlobalInfo.CsSecutityInfo.ucSecurityType        = RR_SYN_TCH_MODIFY;
    }
    else if ((RR_SYN_GSM_GSM_HANDOVER == pMsg->ucSynCause)
          || (RR_SYN_WCDMA_GSM_HANDOVER == pMsg->ucSynCause))
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_NORMAL,
                    "MM_RcvGsmRrcSyncInd: NORMAL: Sync channal mode change.");

        g_MmGlobalInfo.CsSecutityInfo.ucSecurityType        = RR_SYN_TCH_MODIFY;
    }
    else /* ������� */
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_RcvGsmRrcSyncInd: ERROR: Sync cause is unexpected!");

        ucRet = MM_FALSE;
    }

    if ((MM_FALSE != ucRet) && (RR_SYN_CIPH != pMsg->ucSynCause))
    {
        g_RrMmSyncInd.ulRabCnt                     = MM_CONST_NUM_1;
        g_RrMmSyncInd.NasSyncInfo[0].ulRabId       = MM_CONST_NUM_1;
        g_RrMmSyncInd.NasSyncInfo[0].ulCnDomainId  = RRC_NAS_CS_DOMAIN;
        /* ��MMCC_SYNC_IND��Ϣ��ԭ��ֵ����һ�� */
        g_RrMmSyncInd.NasSyncInfo[0].ulReason      = (VOS_UINT32)(pMsg->ucSynCause - 1);
        g_RrMmSyncInd.ulChannelMode                = (VOS_UINT32)pMsg->ucSynValue;
        g_RrMmSyncInd.ulTchRate                    = (VOS_UINT32)pMsg->ucTchRate;

        /* �Ƿ�����Ϣ�е�ͬ��ԭ�򣬴������� */
        g_RrMmSyncInd.NasSyncInfo[0].ulRabSyncInfo = MM_CONST_NUM_1;
    }
#endif

    /* ���ؽ�� */
    return ucRet;
}


/*****************************************************************************
 Prototype      : MM_SupplementNsdInfo
 Description    : ��MM��CC��SS��Ϣ���������� NSD ��Ϣ
 Input          : pData ��������ָ��
 Output         : ---
 Return Value   : ��
 Calls          : ---
 Called By      : NAS �� MM

 History        : ---
  1.Date        : 2006-03-27
    Author      : s46746
    Modification: Creation
  2.��    ��   : 2006��11��22��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:A32D07372
*****************************************************************************/
VOS_UINT32 MM_SupplementNsdInfo(VOS_UINT8 *pData)
{
    VOS_UINT8 ucPd;

    ucPd = pData[0] & MM_IE_PD_MASK;
    if ((MM_IE_PD_MM_MSG == ucPd) || (MM_IE_PD_CALL_CONTROL == ucPd)
       || (MM_IE_PD_NON_CALL_RLT_SS_MSG == ucPd))
    {
        pData[1] |= (VOS_UINT8)(g_stMmNsd.ucNsd << 6);
        return MM_TRUE;
    }

    return MM_FALSE;
}

/*****************************************************************************
 Prototype      : MM_WasRrDataReq
 Description    : NAS��AS��������������
                  ������Ϣԭ��RRMM_DATA_REQ��API����
 Input          : ucCnDomain CN DOMAIN
                  ucPriority �����������ȼ�
                  ulSize �������ݳ���
                  pData ��������ָ��
 Output         : ---
 Return Value   : MM_TRUE �ɹ�
                  MM_FALSE ʧ��
 Calls          : ---
 Called By      : NAS �� MM

 History        : ---
  1.Date        : 2006-03-27
    Author      : s46746
    Modification: Creation
  2.��    ��   : 2006��11��22��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:A32D07372
*****************************************************************************/
VOS_INT32 MM_WasRrDataReq(VOS_UINT8 ucCnDomain, VOS_UINT8 ucPriority,
                          VOS_UINT32 ulSize, VOS_INT8 *pData)
{

    VOS_INT32                           lRet;
    VOS_UINT32                          ulRet = MM_FALSE;

    if (VOS_NULL_PTR != pData)
    {
        ulRet = MM_SupplementNsdInfo((VOS_UINT8 *)pData);
    }

    lRet = As_RrDataReq(ucCnDomain, ucPriority, ulSize, pData);

    if ((MM_TRUE == ulRet) && (MM_TRUE == lRet))
    {
        g_stMmNsd.ucNsd ++;
        g_stMmNsd.ucNsd = g_stMmNsd.ucNsd % g_stMmNsd.ucNsdMod;
    }

    return lRet;
}


/*****************************************************************************
 Prototype      : MM_GasRrDataReq
 Description    : NAS��AS��������������
                  ������Ϣԭ��RRMM_DATA_REQ��API����
 Input          : ucCnDomain CN DOMAIN
                  ucPriority �����������ȼ�
                  ulSize �������ݳ���
                  pData ��������ָ��
 Output         : ---
 Return Value   : MM_TRUE �ɹ�
                  MM_FALSE ʧ��
 Calls          : ---
 Called By      : NAS �� MM

 History        : ---
  1.Date        : 2005-09-09
    Author      : s46746
    Modification: Creation
  2.��    ��   : 2006��11��22��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:A32D07372
*****************************************************************************/
VOS_INT32 MM_GasRrDataReq(VOS_UINT8 ucCnDomain, VOS_UINT8 ucPriority,
                          VOS_UINT32 ulSize, VOS_INT8 *pData)
{
    /* �������VOS���ͺ����ķ���ֵ               */
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulTmp = MM_FALSE;

    /* �������ݳ���                              */
    VOS_UINT32                          ulTmpSize;

    /* ����ԭ������ָ��                          */
    RRMM_DATA_REQ_STRU                 *pMsg;

    /* ���β��л�����ݳ���                      */
    ulTmpSize       = ulSize;
    /* ���ٷ����ĸ��ֽ�����                      */
    if (ulTmpSize < 4)
    {
        ulTmpSize   = 4;
    }

    /* PS ����������                             */
    if (RRC_NAS_PS_DOMAIN == ucCnDomain)
    {
        /* ��ӡ������Ϣ */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_GasRrDataReq: ERROR: Ps data req.");

        /* ����                                  */
        return MM_FALSE;
    }

    /* CS ����������                             */
    /* �����ڴ�ռ�                              */
    pMsg = (RRMM_DATA_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                       (sizeof(RRMM_DATA_REQ_STRU) + ulTmpSize) - 4);

    /* �����ڴ�ʧ��                              */
    if (VOS_NULL_PTR == pMsg)
    {
        /* ��ӡ������Ϣ */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_GasRrDataReq: ERROR: Alloc memory fail.");

        /* ����                                  */
        return MM_FALSE;
    }

    /* �����Ϣͷ                                */
    pMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid       = UEPS_PID_GAS;
    pMsg->MsgHeader.ulMsgName           = RRMM_DATA_REQ;

    /* CN ��                                     */
    pMsg->ulCnDomainId                  = ucCnDomain;
    /* ���ȼ�                                    */
    pMsg->ulPriorityInd                 = ucPriority;
    /* ���ݳ���                                  */
    pMsg->SendNasMsg.ulNasMsgSize       = ulSize;
    /* �����ݿ�������Ϣ��                        */

    if (VOS_NULL_PTR != pData)
    {
        PS_MEM_CPY(pMsg->SendNasMsg.aucNasMsg, pData, ulSize);
        ulTmp = MM_SupplementNsdInfo(pMsg->SendNasMsg.aucNasMsg);
    }

    /* ������Ϣ                                  */
    ulRet = PS_SEND_MSG(WUEPS_PID_MM, pMsg);
    /* ����ʧ��                                  */
    if (VOS_OK != ulRet)
    {
        /* ��ӡ������Ϣ */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_GasRrDataReq: ERROR: Send Msg fail.");

        /* ����                                  */
        return MM_FALSE;
    }

    if (MM_TRUE == ulTmp)
    {
        g_stMmNsd.ucNsd ++;
        g_stMmNsd.ucNsd = g_stMmNsd.ucNsd % g_stMmNsd.ucNsdMod;
    }

    /* ����                                      */
    return MM_TRUE;
}

/*****************************************************************************
 Prototype      : MM_WasRrEstReq
 Description    : NAS ��������ĳ�� CN �����������
                  ��Ϣԭ�� RRMM_EST_REQ �� API ����
 Input          : ulOpId ������ʶ
                  ucCnDomain CN ���ʶ
                  ulEstCause ����ԭ��
                  pIdnnsInfo ����δʹ��
                  ulSize NAS��Ϣ����
                  pFisrstMsg �� CN Domain �ĵ�һ�� NAS ��Ϣ
 Output         : ---
 Return Value   : MM_TRUE �ɹ�
                  MM_FALSE ʧ��
 Calls          : ---
 Called By      : NAS �� MM

 History        : ---
  1.Date        : 2006-03-27
    Author      : s46746
    Modification: Created
  2.��    ��   : 2006��11��22��
    ��    ��   : s46746
    �޸�����   : ���ⵥ��:A32D07372

  3.��    ��   : 2010��3��2��
    ��    ��   : zhoujun /z40661
    �޸�����   : NAS R7Э������

  4.��    ��   : 2010��8��26��
    ��    ��   : ŷ����
    �޸�����   : DTS2010082600921��MM����ע��/ȥע��Ľ�������call type��
                 ��Ϊother.
  5.��    ��   : 2012��10��22��
    ��    ��   : t00212959
    �޸�����   : DTS2012101907218:NAS�����㷢�ͽ�������ʱ��Establishment cause����Э��дΪRegistration
*****************************************************************************/
VOS_INT32 MM_WasRrEstReq(VOS_UINT32 ulOpId, VOS_UINT8 ucCnDomain,
                         VOS_UINT32 ulEstCause, IDNNS_STRU *pIdnnsInfo, RRC_PLMN_ID_STRU *pstPlmnId,
                         VOS_UINT32 ulSize, VOS_INT8 *pFisrstMsg)
{
    VOS_INT32                           lRet;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulCallType;

    g_stMmNsd.ucNsd = MM_NSD_INITAL_VALUE;

    ulRet = MM_FALSE;
    if (VOS_NULL_PTR != pFisrstMsg)
    {
        ulRet = MM_SupplementNsdInfo((VOS_UINT8 *)pFisrstMsg);
    }

    if ( ( RRC_EST_CAUSE_ORIGIN_CONVERSAT_CALL == ulEstCause )
      || ( RRC_EST_CAUSE_CALL_RE_ESTABLISH == ulEstCause ))
    {
        ulCallType = g_MmCcEstReq.ulCallMode;
    }
    else if (( RRC_EST_CAUSE_REGISTRATION == ulEstCause )
          || ( RRC_EST_CAUSE_DETACH == ulEstCause ))
    {
        ulCallType = RRC_NAS_CALL_TYPE_OTHER;
    }
    else
    {
        ulCallType = RRC_NAS_CALL_TYPE_SPEECH;
    }

    lRet = As_RrEstReq(ulOpId, ucCnDomain, ulEstCause,ulCallType, pIdnnsInfo, pstPlmnId, ulSize, pFisrstMsg);

    if ((MM_TRUE == ulRet) && (MM_TRUE == lRet))
    {
        g_stMmNsd.ucNsd ++;
    }

    return lRet;
}


/*****************************************************************************
 Prototype      : MM_GasRrEstReq
 Description    : NAS ��������ĳ�� CN �����������
                  ��Ϣԭ�� RRMM_EST_REQ �� API ����
 Input          : ulOpId ������ʶ
                  ucCnDomain CN ���ʶ
                  ulEstCause ����ԭ��
                  pIdnnsInfo ����δʹ��
                  ulSize NAS��Ϣ����
                  pFisrstMsg �� CN Domain �ĵ�һ�� NAS ��Ϣ
 Output         : ---
 Return Value   : MM_TRUE �ɹ�
                  MM_FALSE ʧ��
 Calls          : ---
 Called By      : NAS �� MM

 History        : ---
  1.Date        : 2005-09-09
    Author      : s46746
    Modification: Created
  2.��    ��   : 2008��05��13��
    ��    ��   : luojian id:107747
    �޸�����   : �������ⵥ�ţ�AT2D03612
*****************************************************************************/
VOS_INT32 MM_GasRrEstReq(VOS_UINT32 ulOpId, VOS_UINT8 ucCnDomain,
                         VOS_UINT32 ulEstCause, IDNNS_STRU *pIdnnsInfo, RRC_PLMN_ID_STRU *pstPlmnId,
                         VOS_UINT32 ulSize, VOS_INT8 *pFisrstMsg)
{
    /* �������VOS���ͺ����ķ���ֵ               */
    VOS_UINT32                          ulRet;

    /* ����ԭ������ָ��                          */
    RRMM_EST_REQ_STRU                  *pMsg;

    /* �������ݳ���                              */
    VOS_UINT32                          ulTmpSize;

    /* ���β��л�����ݳ���                      */
    ulTmpSize = ulSize;
    /* ���ٷ����ĸ��ֽ�����                      */
    if (ulTmpSize < 4)
    {
        ulTmpSize = 4;
    }

    /* PS ����������                             */
    if (RRC_NAS_PS_DOMAIN == ucCnDomain)
    {
        /* ��ӡ������Ϣ */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_GasRrEstReq: ERROR: Ps data req.");

        /* ����                                  */
        return MM_FALSE;
    }

    /* �����ڴ�ռ�                              */
    pMsg = (RRMM_EST_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                       (sizeof(RRMM_EST_REQ_STRU) + ulTmpSize) - 4);
    if ( VOS_NULL_PTR == pMsg )
    {
        /* ��ӡ������Ϣ */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_GasRrEstReq: ERROR: Alloc memory fail.");

        /* ����                                  */
        return MM_FALSE;
    }

    /* �����Ϣͷ                                */
    pMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid       = UEPS_PID_GAS;
    pMsg->MsgHeader.ulMsgName           = RRMM_EST_REQ;

    /* ������ʶ                                  */
    pMsg->ulOpId                        = ulOpId;
    /* CN ��                                     */
    pMsg->ulCnDomainId                  = ucCnDomain;
    /* ����ԭ��                                  */
    pMsg->ulEstCause                    = ulEstCause;
    pMsg->enCallType                    = RRC_NAS_CALL_TYPE_SPEECH;
    /* IDDN����,GAS��ʹ�ã����ֽӿ�һ�� */
    pMsg->ulIdnnsType                   = pIdnnsInfo->ucIdnnsType;
    pMsg->enSplmnSameRplmn              = pIdnnsInfo->ucEnterPara;

    PS_MEM_CPY(&pMsg->stPlmnId, pstPlmnId, sizeof(RRC_PLMN_ID_STRU));

    /* NAS ��һ����Ϣ����                        */
    pMsg->FisrtNasMsg.ulNasMsgSize      = ulSize;
    /* �����ݿ�������Ϣ��                        */
    if (VOS_NULL_PTR != pFisrstMsg)
    {
        PS_MEM_CPY(pMsg->FisrtNasMsg.aucNasMsg, pFisrstMsg, ulSize);
    }
    else
    {
        PS_MEM_SET(pMsg->FisrtNasMsg.aucNasMsg, 0x00, 4);
    }

    /* ���ú���������Ϣ                          */
    ulRet = PS_SEND_MSG(WUEPS_PID_MM, pMsg);
    /* ����ʧ��                                  */
    if (VOS_OK != ulRet)
    {
        /* ��ӡ������Ϣ */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_GasRrEstReq: ERROR: Send Msg fail.");

        return MM_FALSE;
    }

    g_stMmNsd.ucNsd = MM_NSD_INITAL_VALUE;

    if (VOS_NULL_PTR != pFisrstMsg)
    {
        g_stMmNsd.ucNsd ++;
    }

    /* �ɹ�����                                  */
    return MM_TRUE;
}

/*****************************************************************************
 Prototype      : MM_GasRrRelReq
 Description    : NAS ���� GAS �ͷ�ָ�������������
                  ��Ϣԭ�� RRMM_REL_REQ �� API ����
 Input          : ucCnDomain CN ��
 Output         : ---
 Return Value   : MM_TRUE �ɹ�
                  MM_FALSE ʧ��
 Calls          : ---
 Called By      : NAS �� MM

 History        : ---
  1.Date        : 2005-09-09
    Author      : s46746
    Modification: Created
  2.��    ��   : 2007��03��30��
    ��    ��   : luojian 60022475
    �޸�����   : Maps3000�ӿ��޸�
*****************************************************************************/
VOS_INT32 MM_GasRrRelReq(VOS_UINT8 ucCnDomain,RRC_CELL_BAR_ENUM_UINT32 enBarValidFlg)
{
    /* �������VOS���ͺ����ķ���ֵ               */
    VOS_UINT32                          ulRet;

    /* ����ԭ������ָ��                          */
    RRMM_REL_REQ_STRU                  *pMsg;

    /* PS ����������                             */
    if (RRC_NAS_PS_DOMAIN == ucCnDomain)
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_GasRrRelReq: ERROR: Ps release RR connect req.");

        /* ����                                  */
        return MM_FALSE;
    }

    /* �����ڴ�ռ�                              */
    pMsg = (RRMM_REL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MM,
                       sizeof(RRMM_REL_REQ_STRU));
    if (VOS_NULL_PTR == pMsg)
    {
        /* ��ӡ������Ϣ */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_GasRrRelReq: ERROR: Alloc memory fail.");

        /* ����                                  */
        return MM_FALSE;
    }

    /* �����Ϣͷ                                */
    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = UEPS_PID_GAS;
    pMsg->MsgHeader.ulMsgName           = RRMM_REL_REQ;

    /* CN ��                                     */
    pMsg->ulCnDomainId                  = ucCnDomain;
    /* ��ǰС���򼤻С��������־ */
    pMsg->enBarValidFlg                 = enBarValidFlg;
    /* ���ú���������Ϣ                          */
    ulRet = PS_SEND_MSG(WUEPS_PID_MM, pMsg);
    /* ����ʧ��                                  */
    if (VOS_OK != ulRet)
    {
        /* ��ӡ������Ϣ */
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_GasRrRelReq: ERROR: Send Msg fail.");

        /* ����                                  */
        return MM_FALSE;
    }

    /* �ɹ�����                                  */
    return MM_TRUE;
}


/* 6.MM ʵ���ṩ�� GAS ��ȡ��ȫ��Ϣ��API���� */
/*****************************************************************************
 Prototype      : MM_GetSecurityInfo
 Description    : AS ͨ���˽ӿں�����ȡ CS ��ȫ��Ϣ�� IMSI

 Input          : pCsInfo AS ���ṩ����Ϣ�ṹָ��
 Output         : pCsInfo MM ���ṹ�и���Ա,������ȫ��Ϣ�� IMSI
 Return Value   : ��
 Calls          : ---
 Called By      : WAS/GAS

 History        : ---
  1.Date        : 2005-09-09
    Author      : s46746
    Modification: Creation
 2.��    ��   : 2011��7��25��
   ��    ��   : h44270
   �޸�����   : V7R1 PHASEII �ع�: ���ݽṹ��ȫ�ֱ�����ʼ����ħ�����ֵĵ���
*****************************************************************************/

VOS_VOID MM_GetSecurityInfo(MM_CSPS_INFO_ST *pCsInfo)
{
    VOS_UINT8                          *pucImsi = VOS_NULL_PTR;

    if (VOS_NULL_PTR == pCsInfo)
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_ERROR,
                    "MM_GetSecurityInfo: ERROR: Para check error!");

        return;
    }

    /* ��ȫ�ֽṹ����Ӧ��Ϣ�������ṹ pCsInfo �� */
    /* ��ʼ���ṹ�� InfoMask ���� */
    pCsInfo->ucInfoMask = 0x0;

    if (VOS_FALSE == NAS_MML_GetSimPresentStatus()) /* �������� */
    {
        NAS_LOG(WUEPS_PID_MM, MM_GSMDIFMSG, PS_LOG_LEVEL_INFO,
                    "MM_GetSecurityInfo: INFO: SIM is not present!");

        return;
    }

    /* ���� Ck��Ik �� Kc */
    pCsInfo->ucInfoMask |= 0x1F;
    PS_MEM_CPY(pCsInfo->aucCk, NAS_MML_GetSimCsSecurityUmtsCk(), NAS_MML_UMTS_CK_LEN);

    PS_MEM_CPY(pCsInfo->aucIk, NAS_MML_GetSimCsSecurityUmtsIk(), NAS_MML_UMTS_IK_LEN);

    PS_MEM_CPY(pCsInfo->aucKc, NAS_MML_GetSimCsSecurityGsmKc(), NAS_MML_GSM_KC_LEN);

    /* ��ȡ IMSI */
    pucImsi = NAS_MML_GetSimImsi();
    PS_MEM_CPY(pCsInfo->aucImsi, pucImsi + 1, RRC_NAS_IMSI_MAX_LEN);

    pCsInfo->ucCksn = NAS_MML_GetSimCsSecurityCksn();
    if ( MM_MS_ID_TMSI_PRESENT & g_MmGlobalInfo.MsCsInfo.MobileId.ucMsIdFlg )
    {
        pCsInfo->ucInfoMask |= MM_SECURITY_P_TMSI_MASK;

        PS_MEM_CPY(pCsInfo->aucPTMSI,
                   NAS_MML_GetUeIdTmsi(),
                   NAS_MML_MAX_TMSI_LEN);
    }

    return;
}


/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
