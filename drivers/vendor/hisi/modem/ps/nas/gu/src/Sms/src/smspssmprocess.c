/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name:          SmsPsSmProcess.c
  Description:        PS DOMAIN��SM����
  Function List:
               1. SMC_RcvPsMtData
               2. SMC_RcvPsMoData
               3. SMC_RcvGmmEstCnf
               4. SMC_ComPsMtErr
               5. SMC_ComPsMoErr
               6. SMC_ComPsWaitAckSta
               7. SMC_RcvGmmStaInd
               8. SMC_RcvGmmErrInd
               9. SMC_SndGmmDataReq
              10. SMC_SndGmmMsg

  History:
  1.��    ��   : 2009��5��23��
    ��    ��   : f62575
    �޸�����   : AT2D10986, 2G��PS���Ͷ����������η���ʧ�ܺ�
                 CP���ٴγ�ʱ�¼���RP�㳬ʱ�¼�ͬʱ����SMSģ���ڴ�Ĵ��������
                 ���µ���ĸ�λ
  2.��    ��   : 2009��5��10��
    ��    ��   : f62575
    �޸�����   : AT2D12319, NAS R6������
  3.��    ��   : 2010��1��26��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��AT2D16564
                 PS �������������δ���ã�����GCF������������Ҫ����AT ������
                 ��PS������������ܣ�������ԣ�

   4.��    ��   : 2010��04��28��
     ��    ��   : z40661
     �޸�����   : ���ⵥ��AT2D16570
                  ���յ�DATA-IND��Ϣ����Ч����Ϣ���ͣ�Ӧ�ظ�CP-ERROR����ԭ��ֵ97
                  ���յ�DATA-IND��Ϣ����CP-USER-DATA��Ӧ�ظ�CP-ERROR����ԭ��ֵ96
                  ��SMC_MO_WAIT_FOR_CP_ACK״̬��Ӧ�ظ�CP-ERROR����ԭ��ֵ98
*******************************************************************************/
#include "smsinclude.h"
#include "LLInterface.h"
#include "NasGmmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "LmmSmsInterface.h"
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_SMS_PSSMPROCESS_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/
extern VOS_UINT8  Smt_StartMemNotification( VOS_VOID );

/*lint -save -e958 */

/* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
/*****************************************************************************
 �� �� ��  : NAS_SMS_ResendPsRpData
 ��������  : �ط�RP-DATA��Ϣ
 �������  : ucRetransFlg �Ƿ�Ҫ���޸�TP-RD��־����SUBMIT����Ҫ�޸�TP-RD��־ʱΪVOS_TRUE
 �������  : ��
 �� �� ֵ  : VOS_UINT32 VOS_FALSE ��Ϣ����ʧ��
                        VOS_TRUE  ��Ϣ���ͳɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��6��26��
   ��    ��   : f62575
   �޸�����   : V9R1 STK����
 2.��    ��   : 2015��1��29��
   ��    ��   : s00217060
   �޸�����   : DTS2015011309518�޸�
*****************************************************************************/
VOS_UINT32 NAS_SMS_ResendPsRpData(VOS_UINT8 ucRetransFlg)
{
    VOS_UINT8                           ucRdPos;
    VOS_UINT8                           ucTpType;

    if ((VOS_NULL_PTR == g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg)
     || (0 == g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen))
    {
        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
    {

        if (SMS_TRUE != g_SmrEnt.SmrMo.ucMemAvailFlg)
        {
            ucRdPos = (VOS_UINT8)(SMS_TPDU_MTI_LTE_PS + *((VOS_UINT8 *)g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg + SMS_TPDU_SCLEN_LTE_PS));
            ucTpType = (*((VOS_UINT8 *)g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg + ucRdPos)) & NAS_SMS_TP_MTI_MASK;
            if ((NAS_SMS_TP_MTI_SUBMIT == ucTpType)
             && (VOS_TRUE == ucRetransFlg))
            {
                *((VOS_UINT8 *)g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg + ucRdPos) |= SMT_TP_RD_RETRANS;
            }
        }

        NAS_SMS_ReSendLmmCpDataReq(VOS_TRUE);
    }
    else
#endif
    {
        if (SMS_TRUE != g_SmrEnt.SmrMo.ucMemAvailFlg)
        {
            ucRdPos = SMS_TPDU_MTI_PS + *((VOS_UINT8 *)g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg + SMS_TPDU_SCLEN_PS);
            ucTpType = (*((VOS_UINT8 *)g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg + ucRdPos)) & NAS_SMS_TP_MTI_MASK;

            if ((NAS_SMS_TP_MTI_SUBMIT == ucTpType)
             && (VOS_TRUE == ucRetransFlg))
            {
                *((VOS_UINT8 *)g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg + ucRdPos) |= SMT_TP_RD_RETRANS;
            }
        }

        NAS_SMS_ReSendGmmCpDataReq(VOS_TRUE);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_SMS_ResendPsRpData
 ��������  : �ط�RP-DATA��Ϣ
 �������  : ucRetransFlg �Ƿ�Ҫ���޸�TP-RD��־����SUBMIT����Ҫ�޸�TP-RD��־ʱΪVOS_TRUE
 �������  : ��
 �� �� ֵ  : VOS_UINT32 VOS_FALSE ��Ϣ����ʧ��
                        VOS_TRUE  ��Ϣ���ͳɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��6��26��
   ��    ��   : f62575
   �޸�����   : V9R1 STK����
*****************************************************************************/
VOS_UINT32 NAS_SMS_ResendPsRpReport(VOS_VOID)
{
    if ((VOS_NULL_PTR == g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg)
     || (0 == g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen))
    {
        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
    {
        NAS_SMS_ReSendLmmCpDataReq(VOS_FALSE);
    }
    else
#endif
    {
        NAS_SMS_ReSendGmmCpDataReq(VOS_FALSE);
    }

    return VOS_TRUE;
}

/* Added by f62575 for V9R1 STK����, 2013-6-26, end */

/*******************************************************************************
  Module:      SMC_ReportM2NOtaMsg
  Function:    ��trace�й�ȡSMS�Ŀտ���Ϣ
  Input:       NAS_MSG_STRU*   pNasMsg     SMS�տ���Ϣ
  NOTE:
  Return:      VOS_VOID
  History:
      1. ³��    2009.07.11   �¹�����
*******************************************************************************/

VOS_VOID SMC_ReportM2NOtaMsg(NAS_MSG_STRU *pNasMsg)
{
    NAS_OTA_MSG_ID_ENUM_UINT16 usNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;

    PS_NAS_LOG1(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_INFO, "SMC_ReportM2NOtaMsg:NORMAL: msg type is ", pNasMsg->aucNasMsg[1]);

    switch(pNasMsg->aucNasMsg[1])
    {
        case SMC_DATA_TYPE_CP_DATA:
            usNasOtaMsyId = NAS_OTA_MSG_SMS_DATA_TYPE_CP_DATA_UP;
            break;

        case SMC_DATA_TYPE_CP_ACK:
            usNasOtaMsyId = NAS_OTA_MSG_SMS_DATA_TYPE_CP_ACK_UP;
            break;

        case SMC_DATA_TYPE_CP_ERR:
            usNasOtaMsyId = NAS_OTA_MSG_SMS_DATA_TYPE_CP_ERROR_UP;
            break;

        default:
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_ReportM2NOtaMsg:WARNING: invalid msg id");
            /*������SMS�Ŀտ���Ϣ������trace����ʾ*/
            return;
    }

    if (VOS_FALSE == GUNAS_GetSmsFilterFlg())
    {
        NAS_SendAirMsgToOM(WUEPS_PID_SMS, usNasOtaMsyId, NAS_OTA_DIRECTION_UP, pNasMsg->ulNasMsgSize + 4, (VOS_UINT8*)pNasMsg);
    }
}
/*******************************************************************************
  Module:   SMC_RcvPsMtData
  Function: mtʵ����յ�ps�����ݵĴ���
  Input:    VOS_UINT8*  pucCpdu   --- ָ�����ϢCPDU��ָ��
            VOS_UINT32   ulCpduLen --- ����ϢCPDU�ĳ���
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
  1. Date         : 2004-03-09
     Author       : g41091
     Modification : �¹�����
  2. Date         : 2006-02-22
     Author       : g41091
     Modification : ������ͨ��GPRS���Ͷ��ŵĹ���,���ⵥ��:A32D02833
  3. Date         : 2007-04-06
     Author       : h44270
     Modification : ���ⵥ��:A32D10113

  4.��    ��   : 2010��04��28��
    ��    ��   : z40661
    �޸�����   : ���ⵥ��AT2D16570
                 ���յ�DATA-IND��Ϣ����Ч����Ϣ���ͣ�Ӧ�ظ�CP-ERROR����ԭ��ֵ97
                 ���յ�DATA-IND��Ϣ����CP-USER-DATA��Ӧ�ظ�CP-ERROR����ԭ��ֵ96
                 ��SMC_MO_WAIT_FOR_CP_ACK״̬��Ӧ�ظ�CP-ERROR����ԭ��ֵ98

  5.��    ��   : 2010��8��21��
    ��    ��   : zhoujun /40661
    �޸�����   : DTS2010081901387,�����·��ĳ��ȹ���ʱ,�����п����ڴ�Խ��
  6.��    ��   : 2011��11��28��
    ��    ��   : z00161729
    �޸�����   : ���Ӹ�Lģ����SMS_LMM_DATA_REQ�Ĵ���
  7.��    ��   : 2012��8��29��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�
  8.��    ��   : 2013��6��4��
    ��    ��   : s00217060
    �޸�����   : for V9R1_SVLTE:���ն���ʱ���ѽ�������CS����PS�����ȥ��MSGҪ��
  9.��    ��   : 2013��07��11��
    ��    ��   : l00198894
    �޸�����   : V9R1 STK������Ŀ
 10.��    ��   : 2014��6��24��
    ��    ��   : w00167002
    �޸�����   : DSDS III��Ŀ
*******************************************************************************/
VOS_VOID SMC_RcvPsMtData(
                     VOS_UINT8* pucCpdu,
                     VOS_UINT32  ulCpduLen
                     )
{
    VOS_UINT8                           ucResult;
    VOS_UINT32                          ulRet ;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                           ucTi;
#endif

    ucResult = SMC_ComNwMsgChk( pucCpdu, ulCpduLen );                           /* ��Ϣ���                                 */

#if (FEATURE_ON == FEATURE_LTE)
    ucTi     = (pucCpdu[0] & NAS_SMS_MSG_SND_FROM_SIDE_THAT_ORIGINATES_THE_TI) >> 4;
#endif

    if(SMC_MSG_VALID != ucResult)
    {                                                                           /* �������                                 */
        if(SMC_CP_ERR_MSG_INVALID != ucResult)
        {
#if (FEATURE_ON == FEATURE_LTE)
            if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
            {
                /* ��ǰפ����Lģ,����SMS_LMM_DATA_REQ��Ϣ��ͨ��NAS_SMS_SndLmmDataReq���� */
                NAS_SMS_SndLmmDataReq(SMC_DATA_TYPE_CP_ERR, ucResult, ucTi);
            }
            else
#endif
            {
                SMC_SndGmmDataReq( SMC_DATA_TYPE_CP_ERR,
                                   ucResult,
                                   (pucCpdu[0] & 0xf0) >> 4);                      /* ������ش���ָʾ                         */
            }
        }
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_RcvPsMtData:WARNING:SMC_MSG_VALID != ucResult ");
        return;
    }

    switch(pucCpdu[1])
    {                                                                           /* ��Ϣ����                                 */
    case SMC_DATA_TYPE_CP_DATA:
        if( ( SMC_MT_IDLE == g_SmcPsEnt.SmcMt.ucState )
            || ((SMC_MT_WAIT_FOR_CP_ACK == g_SmcPsEnt.SmcMt.ucState )
             &&(g_SmcPsEnt.SmcMt.ucTi != (pucCpdu[0] >> 4))) )
        {                                                                       /* ʵ��״̬�ǿ��л��ڵȴ�����ȷ��           */
            if( 0 != g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen )
            {                                                                   /* �л������Ϣ                             */
                SMC_ComPsWaitAckSta(SMS_TRUE);                                  /* ���ù�������                             */
            }
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_RcvPsMtData:NORMAL: SMS state = SMC_MT_WAIT_FOR_RP_ACK");

            NAS_SMS_ChangePsMtEntityState(SMC_MT_WAIT_FOR_RP_ACK);

            g_SmcPsEnt.SmcMt.ucTi = pucCpdu[0] >> 4;                            /* �洢ti                                   */

            if ( ulCpduLen > (SMC_MSG_HDR_LEN + 2)  )
            {
                g_SmcPsEnt.SmcMt.ucMr = pucCpdu[SMC_MSG_HDR_LEN + 2];               /* �洢mr                                   */
            }

#if (FEATURE_ON == FEATURE_LTE)
            if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
            {
                /* ��ǰפ����Lģ,����SMS_LMM_DATA_REQ��Ϣ��ͨ��NAS_SMS_SndLmmDataReq���� */
                NAS_SMS_SndLmmDataReq(SMC_DATA_TYPE_CP_ACK, 0XFF, g_SmcPsEnt.SmcMt.ucTi);
            }
            else
#endif
            {
                SMC_SndGmmDataReq( SMC_DATA_TYPE_CP_ACK,
                                   0XFF ,
                                   g_SmcPsEnt.SmcMt.ucTi );                         /* �������ȷ��                             */
            }
            ulRet = SMR_SmcApiEstInd( &(pucCpdu[3]),
                              (ulCpduLen - SMC_MSG_HDR_LEN) - 1,
                              SMS_CN_PS );                /* ��߲��ύ����                           */
            if (VOS_OK != ulRet)
            {
                if (SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR == ulRet)
                {
                    NAS_SMS_ChangePsMtEntityState(SMC_MT_IDLE);
                }
                else
                {
                    NAS_SMS_ChangePsMtEntityState(SMC_MT_WAIT_FOR_CP_ACK);
                }
            }
        }
        else if((SMC_MT_WAIT_FOR_CP_ACK == g_SmcPsEnt.SmcMt.ucState )
             &&(g_SmcPsEnt.SmcMt.ucTi == (pucCpdu[0] >> 4)))
        {
#if (FEATURE_ON == FEATURE_LTE)
            if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
            {
                /* ��ǰפ����Lģ,����SMS_LMM_DATA_REQ��Ϣ��ͨ��NAS_SMS_SndLmmDataReq���� */
                NAS_SMS_SndLmmDataReq(SMC_DATA_TYPE_CP_ERR, SMS_CP_ERR_INVALID_TI, ucTi);
            }
            else
#endif
            {
                SMC_SndGmmDataReq( SMC_DATA_TYPE_CP_ERR,
                                   SMS_CP_ERR_INVALID_TI,
                                   (pucCpdu[0] & 0xf0) >> 4);                       /* ������ָʾ����                           */
            }
        }

        else if( SMC_MT_WAIT_FOR_RP_ACK == g_SmcPsEnt.SmcMt.ucState )
        {                                                                       /* ʵ���ڵȴ�����ȷ��                       */
#if (FEATURE_ON == FEATURE_LTE)
            if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
            {
                /* ��ǰפ����Lģ,����SMS_LMM_DATA_REQ��Ϣ��ͨ��NAS_SMS_SndLmmDataReq���� */
                NAS_SMS_SndLmmDataReq(SMC_DATA_TYPE_CP_ERR, SMS_CP_ERR_MSG_INCOMP_WITH_PROT_STA, ucTi);
            }
            else
#endif
            {
                SMC_SndGmmDataReq( SMC_DATA_TYPE_CP_ERR,
                                   SMS_CP_ERR_MSG_INCOMP_WITH_PROT_STA,
                                   (pucCpdu[0] & 0xf0) >> 4);                       /* ������ָʾ����                           */
            }
        }
        else
        {

        }
        break;
    case SMC_DATA_TYPE_CP_ACK:
        if( SMC_MT_WAIT_FOR_CP_ACK == g_SmcPsEnt.SmcMt.ucState )
        {                                                                       /* ��ʵ���״̬����                         */
            SMC_ComPsWaitAckSta(SMS_TRUE);                                      /* ���ù�������                             */
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_RcvPsMtData:NORMAL: SMS state = SMC_MT_IDLE ");

            NAS_SMS_ChangePsMtEntityState(SMC_MT_IDLE);

        }
        else
        {
#if (FEATURE_ON == FEATURE_LTE)
            if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
            {
                /* ��ǰפ����Lģ,����SMS_LMM_DATA_REQ��Ϣ��ͨ��NAS_SMS_SndLmmDataReq���� */
                NAS_SMS_SndLmmDataReq(SMC_DATA_TYPE_CP_ERR,
                                      SMS_CP_ERR_MSG_INCOMP_WITH_PROT_STA, ucTi);
            }
            else
#endif
            {
                SMC_SndGmmDataReq( SMC_DATA_TYPE_CP_ERR,
                                   SMS_CP_ERR_MSG_INCOMP_WITH_PROT_STA,
                                   (pucCpdu[0] & 0xf0) >> 4);                       /* ������ָʾ����                           */
            }
        }
        break;
    case SMC_DATA_TYPE_CP_ERR:
        if( SMC_MT_IDLE != g_SmcPsEnt.SmcMt.ucState )
        {                                                                       /* ��ʵ���״̬����                         */
            /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
            SMR_SmcApiErrorInd( (SMR_SMT_ERROR_CP_ERROR_BEGIN | pucCpdu[SMC_MSG_HDR_LEN]), SMS_TRUE);                                     /* ���ϲ㱨��                               */
            /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

            if( 0 != g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen )
            {                                                                   /* ���ù�������                             */
                SMC_ComPsWaitAckSta(SMS_TRUE);                                  /* ���ù�������                             */
            }
            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_RcvPsMtData:NORMAL: SMS state = SMC_MT_IDLE ");

            NAS_SMS_ChangePsMtEntityState(SMC_MT_IDLE);
        }
        else
        {

        }
        break;
    default:

#if (FEATURE_ON == FEATURE_LTE)
        if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
        {
            /* ��ǰפ����Lģ,����SMS_LMM_DATA_REQ��Ϣ��ͨ��NAS_SMS_SndLmmDataReq���� */
            NAS_SMS_SndLmmDataReq(SMC_DATA_TYPE_CP_ERR,
                                  SMS_CP_ERR_MSG_TYPE_NOT_IMPLEMENT, ucTi);
        }
        else
#endif
        {
            SMC_SndGmmDataReq( SMC_DATA_TYPE_CP_ERR,
                               SMS_CP_ERR_MSG_TYPE_NOT_IMPLEMENT,
                               (pucCpdu[0] & 0xf0) >> 4);                           /* ������ָʾ����                           */
        }
        break;
    }
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_SMC_BufferPsCpAck
 ��������  : �жϵ�ǰ���ú����绷����PS���Ƿ���Ҫ����CP-ACK��Ϣ
 �������  : ��
 �������  : VOS_BOOL                            *pbBufferFlag ����CP-ACK��Ϣ��־
                    VOS_TRUE    ��Ҫ������Ϣ��
                    VOS_FALSE   ����Ҫ������Ϣ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��13��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��12��05��
    ��    ��   : z00161729
    �޸�����   : V7R1 phaseIV�޸�
  3.��    ��   : 2015��05��18��
    ��    ��   : j00174725
    �޸�����   : DTS2015051106584
*****************************************************************************/
VOS_VOID NAS_SMC_BufferPsCpAck(
    VOS_BOOL                            *pbBufferFlag
)
{
    VOS_INT8                            cVersion;
    VOS_UINT8                           ucAccessTech;

    /*PS������������ܹر�: ֱ�ӷ��ز���Ҫ����CP-ACK��Ϣ;*/
    if (NAS_SMS_PS_CONCATENATE_DISABLE == SMS_GetSmsPsConcatenateFlag())
    {
        *pbBufferFlag = VOS_FALSE;
        return;
    }

    /*PS������������ܿ���: ���ݵ�ǰ֧�ֵ�Э��汾�ж��Ƿ���Ҫ����CP-ACK��Ϣ;
        1��UE���õ�Э��汾ΪR4���°汾������Ҫ����CP-ACK��Ϣ;
        2������UE���õ�Э��汾ΪR4�����ϰ汾:
            UE֧��R6�����ϰ汾
                3G���뼼��, ��Ҫ����CP-ACK��Ϣ;
                2G���뼼��
                    UE���õ�Э��汾ΪR6�����ϰ汾, ��Ҫ����CP-ACK��Ϣ;
                    ���򣬲���Ҫ����CP-ACK��Ϣ;
            UE��֧��R6�����ϰ汾
                3G���뼼��, ��Ҫ����CP-ACK��Ϣ;
                2G���뼼��, ����Ҫ����CP-ACK��Ϣ;
    */
    cVersion = NAS_Common_Get_Supported_3GPP_Version(SMS_MM_COM_SRVDOMAIN_PS);
    #if (PS_UE_REL_VER >= PS_PTL_VER_R6)
    if (cVersion >= PS_PTL_VER_R6)
    {
        *pbBufferFlag = VOS_TRUE;
        return;
    }
    else if (cVersion >= PS_PTL_VER_R4)
    #else
    if (cVersion >= PS_PTL_VER_R4)
    #endif
    {
        ucAccessTech = GMM_GetCurNetwork();
        if (NAS_GMM_NET_RAT_TYPE_GSM == ucAccessTech)
        {
            *pbBufferFlag = VOS_FALSE;
            return;
        }
        else
        {
            *pbBufferFlag = VOS_TRUE;
            return;
        }
    }
    else
    {
        *pbBufferFlag = VOS_FALSE;
        return;
    }

}

/*******************************************************************************
  Module:   SMC_RcvPsMoCpData
  Function: moʵ����յ�ps��CP-DATA���ݵĴ���
  Input:    VOS_UINT8*  pucCpdu   --- ָ�����ϢCPDU��ָ��
            VOS_UINT32   ulCpduLen --- ����ϢCPDU�ĳ���
  Output:   VOS_VOID
  NOTE:
            Э��24011 R4�汾֧����Iu ģʽ�¶���PS����Ż��ڴ����֪ͨ��һ�����������Ϸ��͡�
                            ��CS����������������޸ģ����¶��ŷ���ǰ���뷢�͵�ǰ����RP-ACK��Ϣ��ȷ����Ϣ��Ҫ���޸�Ϊ��ѡ�ģ�
            Э��24011 R4�汾R6�汾֧����A/Gbģʽ�¶���PS����Ż��ڴ����֪ͨ��һ��RR�����Ϸ��͡�
  Return:   VOS_VOID
  History:
  1. Date         : 2009-05-11
     Author       : f62575
     Modification : �¹�����
  2.��    ��   : 2010��1��26��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��AT2D16564
                 PS �������������δ���ã�����GCF������������Ҫ����AT ������
                 ��PS������������ܣ�������ԣ�
  3. ��    ��   : 2011��11��28��
     ��    ��   : z00161729
     �޸�����   : ���Ӹ�Lģ����SMS_LMM_DATA_REQ�Ĵ���
  4.��    ��   : 2014��6��24��
    ��    ��   : w00167002
    �޸�����   : DSDS III��Ŀ
*******************************************************************************/
VOS_VOID SMC_RcvPsMoCpData(
                     VOS_UINT8* pucCpdu,
                     VOS_UINT32  ulCpduLen
                    )
{
    VOS_BOOL                            bBufferFlag;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucOrigStatus;

    if ( (g_SmcPsEnt.SmcMo.ucState != SMC_MO_WAIT_FOR_CP_DATA)
      && (g_SmcPsEnt.SmcMo.ucState != SMC_MO_WAIT_FOR_CP_ACK) )
    {
        return;
    }

    ucOrigStatus = g_SmcPsEnt.SmcMo.ucState;
    NAS_SMC_BufferPsCpAck(&bBufferFlag);
    if (VOS_TRUE == bBufferFlag)
    {
        PS_NAS_LOG(WUEPS_PID_SMS,
               VOS_NULL,
               PS_LOG_LEVEL_NORMAL,
               "SMC_RcvPsMoCpData: SMS state = SMC_MO_WAIT_TO_SND_CP_ACK ");

        NAS_SMS_ChangePsMoEntityState(SMC_MO_WAIT_TO_SND_CP_ACK);

        g_SmcPsEnt.SmcMo.ucCpAckFlg = SMS_TRUE;                                 /* ������Ҫ����CP-ACK��־                   */
    }
    else
    {
#if (FEATURE_ON == FEATURE_LTE)
        if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
        {
            /* ��ǰפ����Lģ,����SMS_LMM_DATA_REQ��Ϣ��ͨ��NAS_SMS_SndLmmDataReq���� */
            NAS_SMS_SndLmmDataReq(SMC_DATA_TYPE_CP_ACK, 0XFF, g_SmcPsEnt.SmcMo.ucTi);
        }
        else
#endif
        {
            SMC_SndGmmDataReq( SMC_DATA_TYPE_CP_ACK,
                               0XFF,
                               g_SmcPsEnt.SmcMo.ucTi );                             /* �������ȷ��                             */
        }
        PS_NAS_LOG(WUEPS_PID_SMS,
               VOS_NULL,
               PS_LOG_LEVEL_NORMAL,
               "SMC_RcvPsMoCpData: SMS state = SMC_MO_IDLE ");

        NAS_SMS_ChangePsMoEntityState(SMC_MO_IDLE);

        SMS_SendMnMoLinkCloseInd();
    }

    ulRet = SMR_SmcApiDataInd( &(pucCpdu[3] ),
                              (ulCpduLen - SMC_MSG_HDR_LEN) -1 );                /* ��߲��ύ����                           */
    if(VOS_OK == ulRet)
    {
        /*MO����SMC_MO_WAIT_FOR_CP_ACK״̬˵��û�н��յ�CP-ACKֱ�ӽ���RP-ACK/ERR*/
        if (SMC_MO_WAIT_FOR_CP_ACK == ucOrigStatus)
        {
            /* ֹͣtimer TC1M */
            SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_RcvPsMoCpData: TimerStop: TC1M" );
            if (SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_CS_TC1M_MO ) )
            {
                SMS_LOG( PS_LOG_LEVEL_WARNING, "SMS:SMC_RcvPsMoCpData: fail to Stop TC1M" );
            }

            if (0 != g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen)
            {                                                                   /* �д洢�ķ�����Ϣ                         */
                SMS_Free(g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg);                     /* �ͷŴ洢����Ϣ                           */
                g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;                       /* �����Ϣ����                             */
                g_SmcPsEnt.SmcMo.enHoldSndMsgType    = NAS_SMS_HOLD_MSG_BUTT;
            }

            g_SmcPsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;                        /* ���timer��ʱ����                        */
        }
    }
    else
    {
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_RcvPsMoCpData:Invalid Data,so change State ");
        if (SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR != ulRet)
        {
            NAS_SMS_ChangePsMoEntityState(SMC_MO_WAIT_FOR_CP_ACK);
        }
        else
        {
            NAS_SMS_ChangePsMoEntityState(ucOrigStatus);
        }

        g_SmcPsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;
        return;
    }

    return;
}

/*******************************************************************************
  Module:   SMC_RcvPsMoData
  Function: moʵ����յ�ps�����ݵĴ���
  Input:    VOS_UINT8*  pucCpdu   --- ָ�����ϢCPDU��ָ��
            VOS_UINT32   ulCpduLen --- ����ϢCPDU�ĳ���
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
  1. Date         : 2004-03-09
     Author       : g41091
     Modification : �¹�����
  2. Date         : 2006-02-22
     Author       : g41091
     Modification : ������ͨ��GPRS���Ͷ��ŵĹ���,���ⵥ��:A32D02833
  3. Date         : 2007-04-06
     Author       : h44270
     Modification : ���ⵥ��:A32D10113
  4. ��    ��   : 2011��11��28��
     ��    ��   : z00161729
     �޸�����   : ���Ӹ�Lģ����SMS_LMM_DATA_REQ�Ĵ���
  5.��    ��   : 2014��6��24��
    ��    ��   : w00167002
    �޸�����   : DSDS III��Ŀ
*******************************************************************************/
VOS_VOID SMC_RcvPsMoData(
                     VOS_UINT8* pucCpdu,
                     VOS_UINT32  ulCpduLen
                    )
{
    VOS_UINT8                           ucResult;

#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                           ucTi;
#endif

    ucResult = SMC_ComNwMsgChk( pucCpdu, ulCpduLen );                           /* ��Ϣ���                                 */

#if (FEATURE_ON == FEATURE_LTE)
    ucTi     = (pucCpdu[0] & NAS_SMS_MSG_SND_FROM_SIDE_THAT_ORIGINATES_THE_TI) >> 4;
#endif

    if (SMC_MSG_VALID != ucResult)
    {                                                                           /* �������                                 */
        if (SMC_CP_ERR_MSG_INVALID != ucResult)
        {
#if (FEATURE_ON == FEATURE_LTE)
            if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
            {
                /* ��ǰפ����Lģ,����SMS_LMM_DATA_REQ��Ϣ��ͨ��NAS_SMS_SndLmmDataReq���� */
                NAS_SMS_SndLmmDataReq(SMC_DATA_TYPE_CP_ERR, ucResult, ucTi);
            }
            else
#endif
            {
                SMC_SndGmmDataReq( SMC_DATA_TYPE_CP_ERR,
                                   ucResult,
                                   (pucCpdu[0] & 0xf0) >> 4);                       /* ������ش���ָʾ                         */
            }
        }
        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_WARNING, "SMC_RcvPsMtData:WARNING:SMC_MSG_VALID != ucResult ");
        return;
    }

    switch(pucCpdu[1])
    {                                                                           /* ��Ϣ����                                 */
    case SMC_DATA_TYPE_CP_DATA:
        SMC_RcvPsMoCpData(pucCpdu, ulCpduLen);
        break;
    case SMC_DATA_TYPE_CP_ACK:
        if( SMC_MO_WAIT_FOR_CP_ACK == g_SmcPsEnt.SmcMo.ucState )
        {                                                                       /* ״̬��ȷ                                 */
            SMC_ComPsWaitAckSta(SMS_FALSE);                                     /* ���ù�������                             */

            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_RcvPsMoData:NORMAL: SMS state = SMC_MO_WAIT_FOR_CP_DATA ");

            NAS_SMS_ChangePsMoEntityState(SMC_MO_WAIT_FOR_CP_DATA);
        }
        else
        {                                                                       /* �ڵȴ������������Ϣ                     */
#if (FEATURE_ON == FEATURE_LTE)
            if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
            {
                /* ��ǰפ����Lģ,����SMS_LMM_DATA_REQ��Ϣ��ͨ��NAS_SMS_SndLmmDataReq���� */
                NAS_SMS_SndLmmDataReq(SMC_DATA_TYPE_CP_ERR,
                                SMS_CP_ERR_MSG_INCOMP_WITH_PROT_STA, ucTi);
            }
            else
#endif
            {
                SMC_SndGmmDataReq( SMC_DATA_TYPE_CP_ERR,
                                   SMS_CP_ERR_MSG_INCOMP_WITH_PROT_STA,
                                   (pucCpdu[0] & 0xf0) >> 4);                       /* ������ָʾ����                           */
            }
        }
        break;
    case SMC_DATA_TYPE_CP_ERR:
        if( g_SmcPsEnt.SmcMo.ucState == SMC_MO_WAIT_FOR_CP_ACK )
        {                                                                       /* ״̬�ǵȴ�CP-ACK                         */
            SMC_ComPsWaitAckSta(SMS_FALSE);                                     /* ���ù�������                             */

            /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
            SMR_SmcApiErrorInd( (SMR_SMT_ERROR_CP_ERROR_BEGIN | pucCpdu[2]), SMS_FALSE);                        /* ���ϲ㱨��                               */
            /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_RcvPsMoData:NORMAL: SMS state = SMC_MO_IDLE ");

            NAS_SMS_ChangePsMoEntityState(SMC_MO_IDLE);
        }
        else if( SMC_MO_WAIT_FOR_CP_DATA == g_SmcPsEnt.SmcMo.ucState )
        {                                                                       /* ״̬�ǵȴ�CP-DAT                         */
            /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
            if( SMS_CP_ERR_INVALID_TI == pucCpdu[2] )
            {
                SMR_SmcApiErrorInd( (SMR_SMT_ERROR_CP_ERROR_BEGIN | SMS_CP_ERR_PROT_ERR_UNSPEC), SMS_FALSE );
            }
            else
            {
                SMR_SmcApiErrorInd( (SMR_SMT_ERROR_CP_ERROR_BEGIN | pucCpdu[2]), SMS_FALSE );
            }
            /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

            PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_RcvPsMoData:NORMAL: SMS state = SMC_MO_IDLE ");

            NAS_SMS_ChangePsMoEntityState(SMC_MO_IDLE);
        }
        else
        {

        }
        break;
    default:

#if (FEATURE_ON == FEATURE_LTE)
        if (NAS_GMM_NET_RAT_TYPE_LTE == GMM_GetCurNetwork())
        {
            /* ��ǰפ����Lģ,����SMS_LMM_DATA_REQ��Ϣ��ͨ��NAS_SMS_SndLmmDataReq���� */
            NAS_SMS_SndLmmDataReq(SMC_DATA_TYPE_CP_ERR,
                                  SMS_CP_ERR_MSG_TYPE_NOT_IMPLEMENT, ucTi);
        }
        else
#endif
        {
            SMC_SndGmmDataReq( SMC_DATA_TYPE_CP_ERR,
                               SMS_CP_ERR_MSG_TYPE_NOT_IMPLEMENT,
                               (pucCpdu[0] & 0xf0) >> 4);                           /* ���ϲ㱨��                               */
        }
        break;
    }
}

/*******************************************************************************
  Module:   SMC_RcvGmmEstCnf
  Function: ���ͻ��������
  Input:    VOS_VOID
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��      2004.03.09   �¹�����
      2.
      3.��    ��   : 2012��12��28��
        ��    ��   : f62575
        �޸�����   : DTS2012122700666, ���TR1M��ʱ����TC1M��ʱ��ǰ��ʱ����GCF������������CP-ERROR����
      6.��    ��   : 2014��6��24��
        ��    ��   : w00167002
        �޸�����   : DSDS III��Ŀ
*******************************************************************************/
VOS_VOID SMC_RcvGmmEstCnf()
{
    VOS_UINT16 usMsgLen;
    VOS_UINT8 *pucData = SMS_POINTER_NULL;
    VOS_UINT8  aucTempMsg[255];

    if( 0 != g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen )
    {                                                                           /* �л������Ϣ                             */
        if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TR1M ) )
        {
            SMS_LOG( PS_LOG_LEVEL_ERROR,
                     "SMC_RcvGmmEstCnf: SMC_TIMER_ID_TR1M Timer stop fails" );
        }

        if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_TR1M ) )
        {
            SMS_LOG( PS_LOG_LEVEL_WARNING, "SMC_RcvGmmEstCnf: TimerStart: TR1M Failed" );
        }

        g_SmcPsEnt.SmcMo.ucTi = ((g_SmcPsEnt.SmcMo.ucTi + 1) % 7) | 0X08;

        g_SmcPsEnt.SmcMo.ucMr = ((VOS_UINT8 *)g_SmcPsEnt.SmcMo.HoldRcvMsg.pMsg)[2]; /* ��¼MR                                   */
        g_SmrEnt.SmrMo.ucMr   = ((VOS_UINT8 *)g_SmcPsEnt.SmcMo.HoldRcvMsg.pMsg)[2]; /* ��¼MR                                   */

        usMsgLen = (VOS_UINT16)(((sizeof(PMMSMS_UNITDATA_REQ_STRU) - 4)
                     + g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen)
                     + SMC_MSG_HDR_LEN);                                         /* �����Ϣ�ĳ���                           */

        if( g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen < SMC_SND_MSG_MIN_LEN )
        {                                                                       /* ��Ϣ�ĳ��Ƚ�С                           */
           usMsgLen = sizeof(PMMSMS_UNITDATA_REQ_STRU);
        }
        /* pucSnd = (VOS_UINT8 *)Sms_AllocMsg(usMsgLen);                                �����ڴ�                                 */
        SMS_Memset( aucTempMsg,0,usMsgLen );                                        /* ��ʼ������                               */

        pucData = ((PMMSMS_UNITDATA_REQ_STRU *)aucTempMsg)->SmsMsg.aucNasMsg;       /* �õ������׵�ַ                           */

        pucData[0] = (VOS_UINT8)((g_SmcPsEnt.SmcMo.ucTi & 0Xf7) << 4);                       /* ��дTI                                   */
        pucData[0] |= NAS_PD_SMS;                                               /* ��дPD                                   */
        pucData[1] = SMC_DATA_TYPE_CP_DATA;                                     /* ��д��Ϣ����                             */

        SMS_Memcpy( (VOS_UINT8 *)(pucData + 2),
                    (VOS_UINT8 *)g_SmcPsEnt.SmcMo.HoldRcvMsg.pMsg,
                    g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen );                     /* ��������                                 */

        pucData[2] = (VOS_UINT8)(g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen - 1);         /* ��д��Ϣ����                             */

        ((PMMSMS_UNITDATA_REQ_STRU *)aucTempMsg)->SmsMsg.ulNasMsgSize
              = g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen + SMC_MSG_HDR_LEN;         /* ��ֵ��Ϣ����                             */

        SMS_Free(g_SmcPsEnt.SmcMo.HoldRcvMsg.pMsg);                             /* �ͷ���Ϣ                                 */

        g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen = 0;                               /* �����Ϣ����                             */

        g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg     = (VOS_VOID *)SMS_Malloc(usMsgLen);
        if ( VOS_NULL_PTR == g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg )
        {
            SMS_LOG( PS_LOG_LEVEL_ERROR,
                     "SMS:SMC_RcvGmmEstCnf: Memory allocation fails" );

            return;
        }
        SMS_Memcpy(g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg, aucTempMsg, usMsgLen);         /* ������Ϣ                                 */
        g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen = usMsgLen;                        /* ������Ϣ����                             */
        g_SmcPsEnt.SmcMo.enHoldSndMsgType    = NAS_SMS_HOLD_MSG_GU_MO_RP_DATA;

        /* ������ʱ��TC1M */
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_RcvGmmEstCnf: TimerStart: TC1M" );
        if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_PS_TC1M_MO ) )
        {
            SMS_LOG( PS_LOG_LEVEL_WARNING,
                     "SMS:SMC_RcvGmmEstCnf: TimerStart: TC1M Failed" );
            SMS_Free(g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg);
            g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;                               /* �����Ϣ����                             */
            g_SmcPsEnt.SmcMo.enHoldSndMsgType    = NAS_SMS_HOLD_MSG_BUTT;
            return;
        }

        /* g_SmcPsEnt.SmcMo.TimerInfo.ucTimerSta    = SMS_TIMER_STATUS_RUN;         ��ʼ��TIMER״̬                          */
        g_SmcPsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;

        SMC_SndGmmMsg( aucTempMsg, PMMSMS_UNITDATA_REQ, usMsgLen ) ;                /* ������Ϣ                                 */

        PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_RcvGmmEstCnf:NORMAL: SMS state = SMC_MO_WAIT_FOR_CP_ACK ");

        NAS_SMS_ChangePsMoEntityState(SMC_MO_WAIT_FOR_CP_ACK);
    }
}
/*******************************************************************************
  Module:   SMC_ComPsMtErr
  Function: �ͷ�PS���MTʵ�壬�������
  Input:    VOS_UINT8     ucCause     ����ԭ��
                          enErrType   ��������
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��      2004.03.09   �¹�����
      2. Date         : 2006-04-14
         Author       : ۬����
         Modification : �޸��������ϱ�ERROR������,���ⵥ��:A32D03078
      3. Date         : 2007-04-06
         Author       : h44270
         Modification : ���ⵥ��:A32D10113
      4.��    ��   : 2012��8��29��
        ��    ��   : z00161729
        �޸�����   : DCM������������������޸�,�������
      5.��    ��   : 2013��07��11��
        ��    ��   : f62575
        �޸�����   : V9R1 STK������Ŀ
      6.��    ��   : 2014��6��24��
        ��    ��   : w00167002
        �޸�����   : DSDS III��Ŀ
*******************************************************************************/
VOS_VOID SMC_ComPsMtErr(SMR_SMT_ERROR_ENUM_UINT32           enErrorCode)
{
    if( SMC_MT_WAIT_FOR_CP_ACK == g_SmcPsEnt.SmcMt.ucState )
    {                                                                           /* MTʵ���ڵȴ�����ȷ��                     */
        SMC_ComPsWaitAckSta(SMS_TRUE);                                          /* ���ù�������                             */
        /* SMR_SmcApiErrorInd(ucCause, SMS_TRUE);                                   �ϱ�����                                 */
    }
    else if( SMC_MT_WAIT_FOR_RP_ACK == g_SmcPsEnt.SmcMt.ucState )
    {                                                                           /* MTʵ���ڵȴ��߲�ȷ��                     */
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        SMR_SmcApiErrorInd(enErrorCode, SMS_TRUE);                       /* �ϱ�����                                 */
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    }
    else
    {

    }

    PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_ComPsMtErr:NORMAL:SMS state = SMC_MT_IDLE");

    NAS_SMS_ChangePsMtEntityState(SMC_MT_IDLE);

    return;
}
/*******************************************************************************
  Module:   SMC_ComPsMoErr
  Function: �ͷ�PS���MOʵ�壬�������
  Input:    VOS_UINT8     ucCause     ����ԭ��
                          enErrType   ��������
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��      2004.03.09   �¹�����
      2.  ��    ��   : 2012��8��26��
          ��    ��   : z00161729
          �޸�����   : DCM������������������޸�,�������enErrType
      3.  ��    ��   : 2013��07��11��
          ��    ��   : f62575
          �޸�����   : V9R1 STK������Ŀ
      4.��    ��   : 2014��6��24��
        ��    ��   : w00167002
        �޸�����   : DSDS III��Ŀ
*******************************************************************************/
VOS_VOID SMC_ComPsMoErr(SMR_SMT_ERROR_ENUM_UINT32           enCause)
{
    switch(g_SmcPsEnt.SmcMo.ucState)
    {
    case SMC_MO_WAIT_FOR_CP_ACK:
        SMC_ComPsWaitAckSta(SMS_FALSE);                                         /* ���ù�������                             */
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        SMR_SmcApiErrorInd(enCause, SMS_FALSE);                                 /* �ϱ�����                                 */
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
        break;
    case SMC_MO_GMM_CONN_PENDING:
        if (0 != g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen)
        {
            SMS_Free(g_SmcPsEnt.SmcMo.HoldRcvMsg.pMsg);                             /* �ͷ���Ϣ                                 */
            g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen = 0;                               /* ��ʼ����Ϣ����                           */
        }
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        SMR_SmcApiErrorInd(enCause, SMS_FALSE);                                 /* �ϱ�����                                 */
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
        break;
    case SMC_MO_WAIT_FOR_CP_DATA:
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        SMR_SmcApiErrorInd(enCause, SMS_FALSE);                                 /* �ϱ�����                                 */
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
        break;
    case SMC_MO_WAIT_TO_SND_CP_ACK:
        if (SMS_TRUE == g_SmcPsEnt.SmcMo.ucCpAckFlg)
        {
            g_SmcPsEnt.SmcMo.ucCpAckFlg = SMS_FALSE;                             /* ������Ҫ����CP-ACK��־                   */
            SMS_SendMnMoLinkCloseInd();
        }
        break;
    default:
        break;
    }

    PS_NAS_LOG(WUEPS_PID_SMS, VOS_NULL, PS_LOG_LEVEL_NORMAL, "SMC_ComPsMoErr:NORMAL:SMS state = SMC_MO_IDLE");

    NAS_SMS_ChangePsMoEntityState(SMC_MO_IDLE);

}
/*******************************************************************************
  Module:   SMC_ComPsWaitAckSta
  Function: ��ʼ����Ӧ����Դ
  Input:    VOS_UINT8   ucMtFlg   MT��ʶ
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��      2004.03.09   �¹�����
      2.
*******************************************************************************/
VOS_VOID SMC_ComPsWaitAckSta(
                         VOS_UINT8   ucMtFlg                                        /* ��mt����                                 */
                         )
{
    if( SMS_FALSE == ucMtFlg )
    {                                                                           /* ����mt����                               */
        if (0 != g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen)
        {
            SMS_Free( g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg );                           /* �ͷŻ������Ϣ                           */
            g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen     = 0;                           /* ��ʼ����Ϣ����                           */
            g_SmcPsEnt.SmcMo.enHoldSndMsgType        = NAS_SMS_HOLD_MSG_BUTT;
        }

        g_SmcPsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;                           /* ���timer��ʱ����                        */

        /* ֹͣtimer TC1M */
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_ComPsWaitAckSta: TimerStop: TC1M" );
        if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_PS_TC1M_MO ) )
        {
            return;
        }

        /* g_SmcPsEnt.SmcMo.TimerInfo.ucTimerSta = SMS_TIMER_STATUS_STOP; */
    }
    else
    {
        if (0 != g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen)
        {
            SMS_Free( g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg );                           /* �ͷŻ������Ϣ                           */
            g_SmcPsEnt.SmcMt.HoldSndMsg.ulMsgLen     = 0;                           /* ��ʼ����Ϣ����                           */
            g_SmcPsEnt.SmcMt.enHoldSndMsgType       = NAS_SMS_HOLD_MSG_BUTT;
        }

        g_SmcPsEnt.SmcMt.TimerInfo.ucExpireTimes = 0;                           /* ���timer��ʱ����                        */

        /* ֹͣtimer TC1M */
        SMS_LOG( PS_LOG_LEVEL_NORMAL, "SMS:SMC_ComPsWaitAckSta: TimerStop: TC1M" );
        if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_PS_TC1M_MT ) )
        {
            return;
        }

        /* g_SmcPsEnt.SmcMt.TimerInfo.ucTimerSta = SMS_TIMER_STATUS_STOP; */
    }
    return;
}

/*******************************************************************************
  Module:   SMC_RcvGmmServStatusInd
  Function: ���ݽ�������ͷŻ�ά��ps���ʵ��
  Input:    GMMSMS_SERVICE_STATUS_IND_STRU  *pRcvMsg   �յ�����Ϣ�׵�ַ
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
    1. Date         : 2009-06-30
       Author       : f62575
       Modification : �¹�����
     4.��    ��   : 2012��8��13��
       ��    ��   : z00161729
       �޸�����   : DCM������������������޸�
*******************************************************************************/
VOS_VOID SMC_RcvGmmServStatusInd(
                      GMMSMS_SERVICE_STATUS_IND_STRU  *pRcvMsg                  /* �յ�����Ϣ�׵�ַ                         */
                      )
{
    if (GMM_SMS_NORMAL_SERVICE == pRcvMsg->enServiceSts)
    {                                                                           /* ״̬ΪATTACH                             */
        g_ucPsServiceStatus = SMS_TRUE;                                         /* ��¼��״̬                               */
        g_ucCurSendDomain = SMS_SEND_DOMAIN_PS;
    }
    else
    {
        g_ucPsServiceStatus = SMS_FALSE;                                        /* ��¼��״̬                               */

        /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
        SMC_ComPsMtErr(SMR_SMT_ERROR_NO_SERVICE);                                  /* ����PS��MTʵ��Ĵ���                     */
        SMC_ComPsMoErr(SMR_SMT_ERROR_NO_SERVICE);
        /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

        /* ����PS��MOʵ��Ĵ���                     */
    }
    /*֪ͨTAF��*/
    SMS_AttachFlag(SMS_SEND_DOMAIN_PS,g_ucPsServiceStatus);
    return;
}
/*******************************************************************************
  Module:   SMC_RcvGmmErrInd
  Function: ����ʵ��ĳ�ʼ��
  Input:    PMMSMS_ERROR_IND_STRU  *pRcvMsg   �յ�����Ϣ�׵�ַ
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.  ��־��      2004.03.09   �¹�����
     4.��    ��   : 2012��8��13��
       ��    ��   : z00161729
       �޸�����   : DCM������������������޸�GMM�ϱ�����ԭ����Ҫ��SMRԭ��ֵͳһ����:
                    #define    GMM_SMS_SIGN_NO_EXIST          201
                    #define    GMM_SMS_SPEC_PROC_ONGOING      202
*******************************************************************************/
VOS_VOID SMC_RcvGmmErrInd(
                      PMMSMS_ERROR_IND_STRU  *pRcvMsg                           /* �յ�����Ϣ�׵�ַ                         */
                      )
{

    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    SMC_ComPsMtErr(SMR_SMT_ERROR_PS_ERROR_BEGIN | pRcvMsg->ulCause);                                  /* ����PS��MTʵ��Ĵ���                     */
    SMC_ComPsMoErr(SMR_SMT_ERROR_PS_ERROR_BEGIN | pRcvMsg->ulCause);                                  /* ����PS��MOʵ��Ĵ���                     */
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

}

/*******************************************************************************
  Module:   SMC_SndGmmDataReq
  Function: ��֯����GMM��������
  Input:    VOS_UINT8     ucType   ��������
            VOS_UINT8     ucCause  ����ԭ��
            VOS_UINT8     ucTi     transaction id
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
      1.   ��־��      2004.03.11   �¹�����
      2.
*******************************************************************************/
VOS_VOID SMC_SndGmmDataReq(
                        VOS_UINT8     ucType,                                       /* ��������                                 */
                        VOS_UINT8     ucCause,                                      /* ����ԭ��                                 */
                        VOS_UINT8     ucTi                                          /* transaction id                           */
                      )
{
    /* PMMSMS_UNITDATA_REQ_STRU  *pSndMsg = (PMMSMS_UNITDATA_REQ_STRU *) */
    /* Sms_AllocMsg(sizeof(PMMSMS_UNITDATA_REQ_STRU));                  ����ռ�                                 */
    VOS_UINT8        aucTempMsg[255];

    SMS_Memset( aucTempMsg,0,sizeof(PMMSMS_UNITDATA_REQ_STRU) );                   /* ��ʼ������                               */

    ((PMMSMS_UNITDATA_REQ_STRU *)aucTempMsg)->SmsMsg.aucNasMsg[0] = (VOS_UINT8)((ucTi ^ 0x08) << 4);                 /* ��дti                                   */
    ((PMMSMS_UNITDATA_REQ_STRU *)aucTempMsg)->SmsMsg.aucNasMsg[0] |= NAS_PD_SMS;                                 /* ��дPD                                   */
    ((PMMSMS_UNITDATA_REQ_STRU *)aucTempMsg)->SmsMsg.aucNasMsg[1] = ucType;                                      /* ��д��Ϣ����                             */

    if(SMC_DATA_TYPE_CP_ERR == ucType)
    {                                                                           /* ����������CP_ERROR                       */
        ((PMMSMS_UNITDATA_REQ_STRU *)aucTempMsg)->SmsMsg.ulNasMsgSize = SMC_CP_ERR_LEN;
        ((PMMSMS_UNITDATA_REQ_STRU *)aucTempMsg)->SmsMsg.aucNasMsg[2] = ucCause;
    }
    else
    {                                                                           /* ����������CP_ACK                         */
        ((PMMSMS_UNITDATA_REQ_STRU *)aucTempMsg)->SmsMsg.ulNasMsgSize = SMC_CP_ACK_LEN;
    }
    SMC_SndGmmMsg( aucTempMsg,
                   PMMSMS_UNITDATA_REQ,
                   sizeof(PMMSMS_UNITDATA_REQ_STRU) );                          /* ����GMM��Ϣ                              */

    return;
}
/*******************************************************************************
  Module:   SMC_SndGmmMsg
  Function: ��֯����GMM������Ϣ
  Input:    VOS_UINT8     *pucMsg   ������Ϣ���׵�ַ
            VOS_UINT8     ucType    ��Ϣ����
            VOS_UINT16    usLen     ��Ϣ����
  Output:   VOS_VOID
  NOTE:
  Return:   VOS_VOID
  History:
  1. Date         : 2004-03-11
     Author       : g41091
     Modification : �¹�����
  2. Date         : 2006-02-22
     Author       : g41091
     Modification : ������ͨ��GPRS���Ͷ��ŵĹ���,���ⵥ��:A32D02833

  3. Date         : 2007-02-15
     Author       : x51137
     Modification : A32D08912
  4. Date         : 2007-04-06
     Author       : h44270
     Modification : ���ⵥ��:A32D10113
  5.��    ��   : 2009��05��14��
    ��    ��   : h44270
    �޸�����   : ���ⵥ��:AT2D11898/AT2D11828,��IDLE̬�·���PS����ţ�û�а���ATTACH ACCEPT��Ϣ��Radio Priority for SMS��������Դ
  6.��    ��   : 2012��04��26��
    ��    ��   : w00176964
    �޸�����   : GUL BG��Ŀ����
  7.��    ��  : 2013��03��13��
    ��    ��  : z00214637
    �޸�����  : BodySAR��Ŀ

*******************************************************************************/
VOS_VOID SMC_SndGmmMsg(
                    VOS_UINT8     *pucTempMsg,                                          /* ������Ϣ���׵�ַ                         */
                    VOS_UINT8     ucType,                                           /* ��Ϣ����                                 */
                    VOS_UINT16    usLen                                             /* ��Ϣ����                                 */
                  )
{
    VOS_UINT16      usCpduLen;                          /* CPDU�ĳ��� */
    VOS_UINT8*      pucCpdu;                            /* ָ��CPDU��ָ�� */
    VOS_UINT32  ulRet;
    LL_NAS_UNITDATA_REQ_MSG*    pSndMsg;
    VOS_UINT8      *pucMsg = SMS_POINTER_NULL;

    pucMsg = (VOS_UINT8* )PS_ALLOC_MSG( WUEPS_PID_SMS,
                            usLen - VOS_MSG_HEAD_LENGTH );
    if ( VOS_NULL_PTR == pucMsg )
    {
        SMS_LOG( PS_LOG_LEVEL_ERROR,
                 "SMS:SMC_RcvMmEstCnf: Message allocation fails" );
        return;
    }

    PS_MEM_CPY(pucMsg, pucTempMsg, usLen);

    ((MSG_HEADER_STRU * )pucMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID;
    ((MSG_HEADER_STRU * )pucMsg)->ulSenderPid     = WUEPS_PID_SMS;
    ((MSG_HEADER_STRU * )pucMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;
    ((MSG_HEADER_STRU * )pucMsg)->ulReceiverPid   = WUEPS_PID_GMM;
    ((MSG_HEADER_STRU * )pucMsg)->ulLength        = usLen - VOS_MSG_HEAD_LENGTH;
    ((MSG_HEADER_STRU * )pucMsg)->ulMsgName   = ucType;                         /* ��д��Ϣ����                             */

    if ( NAS_GMM_NET_RAT_TYPE_WCDMA == GMM_GetCurNetwork() )
    {   /* �����ǰ������3Gģʽ */

        /*Report event begin*/
        if ( PMMSMS_UNITDATA_REQ == ucType )
        {
            SMC_ReportM2NOtaMsg(&(((PMMSMS_UNITDATA_REQ_STRU *)pucTempMsg)->SmsMsg));
        }
        /*Report event end*/

        ulRet = PS_SEND_MSG( WUEPS_PID_SMS, pucMsg );
        if (VOS_OK != ulRet)
        {
            /* ��ӡ������Ϣ */
            SMS_LOG( PS_LOG_LEVEL_ERROR, "SMS:SMC_SndGmmMsg:Error: Send msg fails" );
        }
    }
    else
    {   /* �����ǰ������2Gģʽ */
        /* �����Ϣ������PMMSMS_EST_REQ����ô��ģ���GMM��SMC����һ����ϢPMMSMS_EST_CNF */
        if ( PMMSMS_EST_REQ == ucType )
        {
            ((MSG_HEADER_STRU * )pucMsg)->ulSenderPid     = WUEPS_PID_GMM;
            ((MSG_HEADER_STRU * )pucMsg)->ulReceiverPid   = WUEPS_PID_SMS;
            ((MSG_HEADER_STRU * )pucMsg)->ulMsgName       = PMMSMS_EST_CNF;

            ulRet = PS_SEND_MSG( WUEPS_PID_SMS, pucMsg );
            if (VOS_OK != ulRet)
            {
                /* ��ӡ������Ϣ */
                SMS_LOG( PS_LOG_LEVEL_ERROR, "SMS:SMC_SndGmmMsg:Error: Send msg fails" );
            }
        }
        else if ( PMMSMS_UNITDATA_REQ == ucType )
        {
            /* ���PMMSMS_UNITDATA_REQ_STRU��Ϣ�а�����CPDU�ĳ��� */
            usCpduLen = (VOS_UINT16)((PMMSMS_UNITDATA_REQ_STRU*)pucMsg)->SmsMsg.ulNasMsgSize;

            pucCpdu = ((PMMSMS_UNITDATA_REQ_STRU*)pucMsg)->SmsMsg.aucNasMsg;

            /* �����µ�LL_NAS_UNITDATA_REQ_MSG�ṹ�Ŀռ� */
            pSndMsg = (LL_NAS_UNITDATA_REQ_MSG *) PS_ALLOC_MSG( WUEPS_PID_SMS,
                                    ((usLen + sizeof(LL_NAS_UNITDATA_REQ_MSG)) -
                                    sizeof(PMMSMS_UNITDATA_REQ_STRU)) -
                                    VOS_MSG_HEAD_LENGTH );

            if ( VOS_NULL_PTR == pSndMsg )
            {
                SMS_LOG( PS_LOG_LEVEL_ERROR,
                         "SMS:SMC_SndGmmMsg: Message allocation fails" );
                PS_FREE_MSG(WUEPS_PID_SMS, pucMsg);
                return;
            }

            PS_MEM_SET((VOS_UINT8*)(&(pSndMsg->stUnitDataReq)), 0x00, sizeof(LL_NAS_UNITDATA_REQ_ST));

            /* ��CPDU�ĳ��Ƚ��и�ֵ */
            pSndMsg->stUnitDataReq.usPduLen = usCpduLen;
            /* ����ԭ��PMM�ṹ�е�CPDU���µ�LLC�Ľṹ�� */
            SMS_Memcpy( pSndMsg->stUnitDataReq.aucPdu, pucCpdu, usCpduLen );

            /* �Խṹ�е�����Field���и�ֵ */
            pSndMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
            pSndMsg->ulSenderPid     = WUEPS_PID_SMS;
            pSndMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
            pSndMsg->ulReceiverPid   = UEPS_PID_LL;

            pSndMsg->usMsgType       = ID_LL_UNITDATA_REQ;
            pSndMsg->usTransId       = LL_SAPI_SMS;

            pSndMsg->stUnitDataReq.ulTlli     = GMM_GetTlli();          /* ���Tlliֵ */
            pSndMsg->stUnitDataReq.ucRadioPri = GMM_GetRaPrioForSms();         /* ����������ȼ� */
            pSndMsg->stUnitDataReq.ucCiphInd  = Gmm_GetCurrCipherInfo();                      /* ���м��� */

            PS_FREE_MSG(WUEPS_PID_SMS, pucMsg);

            SMC_ReportM2NOtaMsg(&(((PMMSMS_UNITDATA_REQ_STRU *)pucTempMsg)->SmsMsg));


            ulRet = PS_SEND_MSG( UEPS_PID_LL, pSndMsg );
            if ( VOS_OK != ulRet )
            {
                SMS_LOG( PS_LOG_LEVEL_ERROR,
                         "SMS:SMC_SndGmmMsg: Message send fails" );
                return;
            }
        }
        else if (PMMSMS_REL_REQ == ucType)
        {
            ((MSG_HEADER_STRU * )pucMsg)->ulSenderPid     = WUEPS_PID_GMM;
            ((MSG_HEADER_STRU * )pucMsg)->ulReceiverPid   = WUEPS_PID_SMS;
            ((MSG_HEADER_STRU * )pucMsg)->ulMsgName       = PMMSMS_REL_REQ;

            ulRet = PS_SEND_MSG( WUEPS_PID_SMS, pucMsg );
            if (VOS_OK != ulRet)
            {
                /* ��ӡ������Ϣ */
                SMS_LOG( PS_LOG_LEVEL_ERROR, "SMS:SMC_SndGmmMsg:Error: Send msg fails" );
            }
        }
        else
        {
            PS_FREE_MSG(WUEPS_PID_SMS, pucMsg);
        }
    }
    return;
}



#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_SMS_ProcLmmEstCnf
 ��������  : ����LMM��LMM_SMS_EST_CNF��Ϣ
 �������  : pRcvMsg - LMM_SMS_EST_CNF��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��28��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��28��
    ��    ��   : f62575
    �޸�����   : DTS2012122700666, ���TR1M��ʱ����TC1M��ʱ��ǰ��ʱ����GCF������������CP-ERROR����
  3.��    ��   : 2014��6��24��
    ��    ��   : w00167002
    �޸�����   : DSDS III��Ŀ
*****************************************************************************/
VOS_VOID NAS_SMS_ProcLmmEstCnf(
    VOS_VOID                           *pRcvMsg
)
{
    VOS_UINT16                          usMsgLen;
    VOS_UINT8                          *pucData;
    VOS_UINT8                           aucMsg[NAS_SMS_MAX_MSG_SIZE];

    /* �л������Ϣ */
    if( 0 != g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen )
    {
        if ( SMS_FALSE == SMS_TimerStop( SMC_TIMER_ID_TR1M ) )
        {
            SMS_LOG( PS_LOG_LEVEL_ERROR,
                     "NAS_SMS_ProcLmmEstCnf: SMC_TIMER_ID_TR1M Timer stop fails" );
        }

        if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_TR1M ) )
        {
            SMS_LOG( PS_LOG_LEVEL_WARNING, "NAS_SMS_ProcLmmEstCnf: TimerStart: TR1M Failed" );
        }

        g_SmcPsEnt.SmcMo.ucTi = ((g_SmcPsEnt.SmcMo.ucTi + 1) % 7) | NAS_SMS_MSG_SND_TO_SIDE_THAT_ORIGINATES_THE_TI;

        g_SmcPsEnt.SmcMo.ucMr = ((VOS_UINT8 *)g_SmcPsEnt.SmcMo.HoldRcvMsg.pMsg)[2]; /* ��¼MR */
        g_SmrEnt.SmrMo.ucMr   = ((VOS_UINT8 *)g_SmcPsEnt.SmcMo.HoldRcvMsg.pMsg)[2]; /* ��¼MR */

        /* �����Ϣ�ĳ��� */
        usMsgLen = (VOS_UINT16)(((sizeof(SMS_LMM_DATA_REQ_STRU) - 4)
                                + g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen)
                                + SMC_MSG_HDR_LEN);

        /* ��Ϣ�ĳ��Ƚ�С */
        if( g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen < SMC_SND_MSG_MIN_LEN )
        {
           usMsgLen = sizeof(SMS_LMM_DATA_REQ_STRU);
        }

        PS_MEM_SET(aucMsg, 0, usMsgLen);

        pucData = ((SMS_LMM_DATA_REQ_STRU *)aucMsg)->stSmsMsg.aucSmsMsg;        /* �õ������׵�ַ */

        pucData[0] = (VOS_UINT8)((g_SmcPsEnt.SmcMo.ucTi & NAS_SMS_TI_MASK) << 4); /* ��дTI */
        pucData[0] |= NAS_PD_SMS;                                               /* ��дPD */
        pucData[1] = SMC_DATA_TYPE_CP_DATA;                                     /* ��д��Ϣ����*/

        PS_MEM_CPY( (VOS_UINT8 *)(pucData + 2),
                    (VOS_UINT8 *)g_SmcPsEnt.SmcMo.HoldRcvMsg.pMsg,
                    g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen );                     /* ��������*/

        pucData[2] = (VOS_UINT8)(g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen - 1);     /* ��д��Ϣ���� */

        ((SMS_LMM_DATA_REQ_STRU *)aucMsg)->stSmsMsg.ulSmsMsgSize
              = g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen + SMC_MSG_HDR_LEN;         /* ��ֵ��Ϣ���� */

        PS_MEM_FREE(WUEPS_PID_SMS, g_SmcPsEnt.SmcMo.HoldRcvMsg.pMsg);                          /* �ͷ���Ϣ */

        g_SmcPsEnt.SmcMo.HoldRcvMsg.ulMsgLen = 0;                               /* �����Ϣ���� */

        g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg     = (VOS_VOID *)SMS_Malloc(usMsgLen);
        if ( VOS_NULL_PTR == g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg )
        {
            NAS_WARNING_LOG(WUEPS_PID_SMS, "NAS_SMS_ProcLmmEstCnf: Memory allocation fails" );
            return;
        }

        PS_MEM_CPY(g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg, aucMsg, usMsgLen);         /* ������Ϣ                                 */
        g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen = usMsgLen;                        /* ������Ϣ����                             */
        /* ��ǻ������Ϣ���� */
        g_SmcPsEnt.SmcMo.enHoldSndMsgType    = NAS_SMS_HOLD_MSG_LTE_MO_RP_DATA;

        /* ������ʱ��TC1M */
        NAS_INFO_LOG(WUEPS_PID_SMS, "NAS_SMS_ProcLmmEstCnf: TimerStart: TC1M" );
        if ( SMS_FALSE == SMS_TimerStart( SMC_TIMER_ID_PS_TC1M_MO ) )
        {
            NAS_INFO_LOG(WUEPS_PID_SMS, "NAS_SMS_ProcLmmEstCnf: TimerStart: TC1M Failed" );
            PS_MEM_FREE(WUEPS_PID_SMS, g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg);
            g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;                           /* �����Ϣ����                             */
            g_SmcPsEnt.SmcMo.enHoldSndMsgType    = NAS_SMS_HOLD_MSG_BUTT;
            return;
        }

        g_SmcPsEnt.SmcMo.TimerInfo.ucExpireTimes = 0;

        /* ����CP-DATA��Ϣ */
        if ( VOS_FALSE == NAS_SMS_SndLmmCpDataReq(aucMsg, usMsgLen) )
        {
            NAS_INFO_LOG(WUEPS_PID_SMS, "NAS_SMS_ProcLmmEstCnf: Message allocation fails" );
            PS_MEM_FREE(WUEPS_PID_SMS, g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg);
            g_SmcPsEnt.SmcMo.HoldSndMsg.ulMsgLen = 0;
            g_SmcPsEnt.SmcMo.enHoldSndMsgType    = NAS_SMS_HOLD_MSG_BUTT;
            return;
        }


        NAS_SMS_ChangePsMoEntityState(SMC_MO_WAIT_FOR_CP_ACK);

    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_SMS_ProcLmmDataInd
 ��������  : ����LMM��LMM_SMS_DATA_IND��Ϣ
 �������  : pRcvMsg - LMM_SMS_DATA_IND��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��28��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_SMS_ProcLmmDataInd(
    VOS_VOID                           *pRcvMsg
)
{
    LMM_SMS_DATA_IND_STRU              *pstLmmDataInd;
    VOS_UINT8                           ucTi;

    pstLmmDataInd = (LMM_SMS_DATA_IND_STRU *)pRcvMsg;

    ucTi          = pstLmmDataInd->stSmsMsg.aucSmsMsg[0] >> 4;

    SMS_ReportN2MOtaMsg((NAS_MSG_STRU *)&pstLmmDataInd->stSmsMsg);

    /* �����MT���� */
    if ((pstLmmDataInd->stSmsMsg.aucSmsMsg[0] >> 4) < NAS_SMS_MSG_SND_TO_SIDE_THAT_ORIGINATES_THE_TI)
    {
        /* ���ͬʱ������MT���� */
        if (SMC_MT_IDLE != g_SmcCsEnt.SmcMt.ucState)
        {
            /* ��װSMS_LMM_DATA_REQ_STRU�ṹ,������ظ�cp_err,����NAS_SMS_SndLmmDataReq���з��� */
            NAS_SMS_SndLmmDataReq(SMC_DATA_TYPE_CP_ERR, SMS_CP_ERR_CONGEST, ucTi);
        }
        else
        {
            /* ����MT�Ĵ������ */
            SMC_RcvPsMtData(pstLmmDataInd->stSmsMsg.aucSmsMsg,
                            pstLmmDataInd->stSmsMsg.ulSmsMsgSize);
        }
    }
    else
    {
        /* ��MO���̣�����MO�Ĵ������ */
        SMC_RcvPsMoData(pstLmmDataInd->stSmsMsg.aucSmsMsg,
                        pstLmmDataInd->stSmsMsg.ulSmsMsgSize);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_SMS_ProcLmmErrInd
 ��������  : ����LMM��LMM_SMS_ERR_IND��Ϣ
 �������  : pRcvMsg - LMM_SMS_ERR_IND��Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��28��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��8��15��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�
  3.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
*****************************************************************************/
VOS_VOID NAS_SMS_ProcLmmErrInd(
    VOS_VOID                           *pRcvMsg
)
{
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, begin */
    LMM_SMS_ERR_IND_STRU               *pstLmmSmsErrInd;

    pstLmmSmsErrInd = (LMM_SMS_ERR_IND_STRU *)pRcvMsg;
    /* Modified by z00161729 for DCM�����������������, 2012-8-15, end */

    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    SMC_ComPsMtErr(SMR_SMT_ERROR_EPS_ERROR_BEGIN | pstLmmSmsErrInd->enErrCause);    /* ����PS��MTʵ��Ĵ��� */

    SMC_ComPsMoErr(SMR_SMT_ERROR_EPS_ERROR_BEGIN | pstLmmSmsErrInd->enErrCause);    /* ����PS��MOʵ��Ĵ��� */
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_SMS_SndLmmDataReq
 ��������  : ��LMM����SMS_LMM_DATA_REQ��Ϣ
 �������  : ucType  - ��Ϣ����CP_ERROR����CP_ACK
             ucCause - ����ԭ��
             ucTi    - Transaction ID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��28��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_SMS_SndLmmDataReq(
    VOS_UINT8                           ucType,
    VOS_UINT8                           ucCause,
    VOS_UINT8                           ucTi
)
{
    SMS_LMM_DATA_REQ_STRU              *pstSmsLmmDataReq;
    VOS_UINT32                          ulRet;

    /* �����ڴ�  */
    pstSmsLmmDataReq = (SMS_LMM_DATA_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_SMS,
                                     sizeof(SMS_LMM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstSmsLmmDataReq )
    {
        NAS_WARNING_LOG(WUEPS_PID_SMS, "NAS_SMS_SndLmmDataReq():WARNING:PS_ALLOC_MSG FIAL");
        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstSmsLmmDataReq + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(SMS_LMM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��дti */
    pstSmsLmmDataReq->stSmsMsg.aucSmsMsg[0] = (VOS_UINT8)((ucTi ^ NAS_SMS_MSG_SND_TO_SIDE_THAT_ORIGINATES_THE_TI) << 4);
    pstSmsLmmDataReq->stSmsMsg.aucSmsMsg[0] |= NAS_PD_SMS;                       /* ��дPD  */
    pstSmsLmmDataReq->stSmsMsg.aucSmsMsg[1] = ucType;                            /* ��д��Ϣ���� */

    if (SMC_DATA_TYPE_CP_ERR == ucType)
    {
        /* ����������CP_ERROR */
        pstSmsLmmDataReq->stSmsMsg.ulSmsMsgSize = SMC_CP_ERR_LEN;
        pstSmsLmmDataReq->stSmsMsg.aucSmsMsg[2] = ucCause;
    }
    else
    {
        /* ����������CP_ACK */
        pstSmsLmmDataReq->stSmsMsg.ulSmsMsgSize = SMC_CP_ACK_LEN;
    }

    pstSmsLmmDataReq->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstSmsLmmDataReq->ulReceiverPid   = PS_PID_MM;
    pstSmsLmmDataReq->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstSmsLmmDataReq->ulSenderPid     = WUEPS_PID_SMS;
    pstSmsLmmDataReq->ulLength        = sizeof(SMS_LMM_DATA_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSmsLmmDataReq->ulMsgId         = ID_SMS_LMM_DATA_REQ;
    pstSmsLmmDataReq->ulOpId          = 0;

    /* �ϱ�OTA��Ϣ */
    SMC_ReportM2NOtaMsg((NAS_MSG_STRU *)&pstSmsLmmDataReq->stSmsMsg);

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_SMS, pstSmsLmmDataReq);

    if (VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_SMS, "NAS_SMS_SndLmmDataReq():WARNING:SEND LMM DATA REQ FIAL");
        return;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_SMS_SndLmmCpDataReq
 ��������  : ��LMM����SMS_LMM_DATA_REQ��Ϣ
 �������  : pucSndMsg - ������Ϣ����
             ulMsgLen  - ������Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_FALSE - ʧ��
             VOS_TRUE  - �ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��28��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��11��
    ��    ��   : l00167671
    �޸�����   : DTS2012121802573, TQE����

*****************************************************************************/
VOS_UINT32 NAS_SMS_SndLmmCpDataReq(
    VOS_UINT8                          *pucSndMsg,
    VOS_UINT32                          ulMsgLen
)
{
    VOS_UINT8                          *pucCpDataMsg;
    LMM_SMS_MSG_STRU                   *pSmsMsg;

    /* ����CP-DATA��Ϣ */
    pucCpDataMsg = (VOS_UINT8* )PS_ALLOC_MSG( WUEPS_PID_SMS,
                                ulMsgLen - VOS_MSG_HEAD_LENGTH );

    if ( VOS_NULL_PTR == pucCpDataMsg )
    {
        NAS_INFO_LOG(WUEPS_PID_SMS, "NAS_SMS_SndLmmCpDataReq: Message allocation fails" );
        return VOS_FALSE;
    }

    PS_MEM_CPY(pucCpDataMsg, pucSndMsg, ulMsgLen);

    ((MSG_HEADER_STRU * )pucCpDataMsg)->ulSenderCpuId   = VOS_LOCAL_CPUID;
    ((MSG_HEADER_STRU * )pucCpDataMsg)->ulSenderPid     = WUEPS_PID_SMS;
    ((MSG_HEADER_STRU * )pucCpDataMsg)->ulReceiverCpuId = VOS_LOCAL_CPUID;
    ((MSG_HEADER_STRU * )pucCpDataMsg)->ulReceiverPid   = PS_PID_MM;
    ((MSG_HEADER_STRU * )pucCpDataMsg)->ulLength        = ulMsgLen - VOS_MSG_HEAD_LENGTH;
    ((MSG_HEADER_STRU * )pucCpDataMsg)->ulMsgName       = ID_SMS_LMM_DATA_REQ;

    pSmsMsg = &((SMS_LMM_DATA_REQ_STRU *)pucSndMsg)->stSmsMsg;
    SMC_ReportM2NOtaMsg((NAS_MSG_STRU *)pSmsMsg);

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_SMS, pucCpDataMsg))
    {
        NAS_WARNING_LOG(WUEPS_PID_SMS, "NAS_SMS_SndLmmCpDataReq():WARNING:SEND MSG FIAL");
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_SMS_SndLmmEstReq
 ��������  : ��LMM����SMS_LMM_EST_REQ��Ϣ
 �������  : ulEstCause - ����ԭ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��11��28��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_SMS_SndLmmEstReq(
    VOS_UINT32                          ulEstCause
)
{
    VOS_UINT32                          ulRet;
    SMS_LMM_EST_REQ_STRU               *pstEstReqMsg;

    /* �����ڴ�  */
    pstEstReqMsg = (SMS_LMM_EST_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_SMS,
                                         sizeof(SMS_LMM_EST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstEstReqMsg )
    {
        NAS_ERROR_LOG(WUEPS_PID_SMS, "NAS_SMS_SndLmmEstReq():ERROR:Memory Alloc Error for pstEstReqMsg");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstEstReqMsg + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(SMS_LMM_EST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstEstReqMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstEstReqMsg->ulReceiverPid    = PS_PID_MM;
    pstEstReqMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstEstReqMsg->ulSenderPid      = WUEPS_PID_SMS;
    pstEstReqMsg->ulLength         = sizeof(SMS_LMM_EST_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstEstReqMsg->ulMsgId          = ID_SMS_LMM_EST_REQ;
    pstEstReqMsg->ulOpId           = 0;
    pstEstReqMsg->ulEstCause       = ulEstCause;

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_SMS, pstEstReqMsg );

    if( VOS_OK != ulRet )
    {
        NAS_WARNING_LOG(WUEPS_PID_SMS, "NAS_SMS_SndLmmEstReq():WARNING:SEND SMS LMM EST REQ FIAL");
        return;
    }

    return;
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_SMS_SndGmmBeginSessionNotify
 ��������  : ��GMM����begin session notify
 �������  : enSessionType - session type
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��16��
    ��    ��   : z00161729
    �޸�����   : DSDS III����

*****************************************************************************/
VOS_VOID NAS_SMS_SndGmmBeginSessionNotify(
    GMMSMS_SESSION_TYPE_ENUM_UINT8      enSessionType
)
{
    VOS_UINT32                          ulRet;
    GMMSMS_BEGIN_SESSION_NOTIFY_STRU   *pstBeginSessionNotify = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstBeginSessionNotify = (GMMSMS_BEGIN_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_SMS,
                                         sizeof(GMMSMS_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstBeginSessionNotify )
    {
        NAS_ERROR_LOG(WUEPS_PID_SMS, "NAS_SMS_SndGmmBeginSessionNotify():ERROR:Memory Alloc Error ");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstBeginSessionNotify + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(GMMSMS_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstBeginSessionNotify->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulReceiverPid    = WUEPS_PID_GMM;
    pstBeginSessionNotify->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulSenderPid      = WUEPS_PID_SMS;
    pstBeginSessionNotify->stMsgHeader.ulLength         = sizeof(GMMSMS_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBeginSessionNotify->stMsgHeader.ulMsgName        = GMMSMS_BEGIN_SESSION_NOTIFY;
    pstBeginSessionNotify->enSessionType                = enSessionType;

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_SMS, pstBeginSessionNotify );

    if( VOS_OK != ulRet )
    {
        NAS_WARNING_LOG(WUEPS_PID_SMS, "NAS_SMS_SndGmmBeginSessionNotify():WARNING:SEND SMS FAIL");
        return;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_SMS_SndGmmEndSessionNotify
 ��������  : ��GMM����end session notify
 �������  : enSessionType - session type
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��16��
    ��    ��   : z00161729
    �޸�����   : DSDS III����

*****************************************************************************/
VOS_VOID NAS_SMS_SndGmmEndSessionNotify(
    GMMSMS_SESSION_TYPE_ENUM_UINT8      enSessionType
)
{
    VOS_UINT32                          ulRet;
    GMMSMS_END_SESSION_NOTIFY_STRU     *pstEndSessionNotify = VOS_NULL_PTR;

    /* �����ڴ�  */
    pstEndSessionNotify = (GMMSMS_END_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_SMS,
                                         sizeof(GMMSMS_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    if( VOS_NULL_PTR == pstEndSessionNotify )
    {
        NAS_ERROR_LOG(WUEPS_PID_SMS, "NAS_SMS_SndGmmEndSessionNotify():ERROR:Memory Alloc Error ");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstEndSessionNotify + VOS_MSG_HEAD_LENGTH, 0,
                     sizeof(GMMSMS_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    pstEndSessionNotify->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulReceiverPid    = WUEPS_PID_GMM;
    pstEndSessionNotify->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulSenderPid      = WUEPS_PID_SMS;
    pstEndSessionNotify->stMsgHeader.ulLength         = sizeof(GMMSMS_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstEndSessionNotify->stMsgHeader.ulMsgName        = GMMSMS_END_SESSION_NOTIFY;
    pstEndSessionNotify->enSessionType                = enSessionType;

    /* ����VOS����ԭ�� */
    ulRet = PS_SEND_MSG( WUEPS_PID_SMS, pstEndSessionNotify );

    if( VOS_OK != ulRet )
    {
        NAS_WARNING_LOG(WUEPS_PID_SMS, "NAS_SMS_SndGmmEndSessionNotify():WARNING:SEND SMS FAIL");
        return;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_SMS_IsPsDomainIdle
 ��������  : ȷ�϶���PS���Ƿ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE   ����PS���ǿ���;
             VOS_FALSE  ����PS��ռ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��10��20��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  NAS_SMS_IsPsDomainIdle(VOS_VOID)
{
    if ((SMC_MT_IDLE == g_SmcPsEnt.SmcMt.ucState)
     && (SMC_MO_IDLE == g_SmcPsEnt.SmcMo.ucState))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }

}

/*****************************************************************************
 �� �� ��  : NAS_SMS_ReSendLmmCpDataReq
 ��������  : ���ݻ����е���Ϣ����LTE�µ�CP_DATA,�����͸�LMM
 �������  : ��
 �������  : pstLmmMsg:LTE�µ�CP_DATA
             pulMsgLen:CP_DATA��Ϣ����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��28��
    ��    ��   : s00217060
    �޸�����   : DTS2015011309518����
  2.��    ��   : 2015��4��2��
    ��    ��   : w00316404
    �޸�����   : clean coverity

*****************************************************************************/
VOS_VOID  NAS_SMS_ReSendLmmCpDataReq(
    VOS_UINT32                          ulResendMoFlg
)
{
    PMMSMS_UNITDATA_REQ_STRU           *pstHoldGuMsg    = VOS_NULL_PTR;
    SMS_LMM_DATA_REQ_STRU              *pstHoldLmmMsg   = VOS_NULL_PTR;
    SMS_LMM_DATA_REQ_STRU              *pstLmmMsg       = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulNasMsgLen;

    ulMsgLen    = 0;
    ulNasMsgLen = 0;

    /* ���֮ǰ����GU�·���CP_DATA,��Ҫ����һ�½ṹ��ת��,
       ����LTE�µ���Ϣ�ṹ���GU�µ���Ϣ�ṹ�岻һ�������ܵ��¸�λ */

    /* MOʱ */
    if (VOS_TRUE == ulResendMoFlg)
    {
        if (NAS_SMS_HOLD_MSG_GU_MO_RP_DATA  == g_SmcPsEnt.SmcMo.enHoldSndMsgType)
        {
            pstHoldGuMsg    = (PMMSMS_UNITDATA_REQ_STRU *)g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg;
            ulNasMsgLen     = pstHoldGuMsg->SmsMsg.ulNasMsgSize;

            /* LTE�µ���Ϣ�ṹ���GU�µ���Ϣ�ṹ�岻һ������Ҫ���·����ڴ�ռ� */
            ulMsgLen    = sizeof(SMS_LMM_DATA_REQ_STRU) - 4 + ulNasMsgLen;


            pstLmmMsg = PS_MEM_ALLOC(WUEPS_PID_SMS, ulMsgLen);

            if (VOS_NULL_PTR == pstLmmMsg)
            {
                return;
            }

            PS_MEM_SET(pstLmmMsg, 0, ulMsgLen);

            pstLmmMsg->stSmsMsg.ulSmsMsgSize = ulNasMsgLen;
            PS_MEM_CPY(pstLmmMsg->stSmsMsg.aucSmsMsg, pstHoldGuMsg->SmsMsg.aucNasMsg, ulNasMsgLen);
        }
        else if (NAS_SMS_HOLD_MSG_LTE_MO_RP_DATA == g_SmcPsEnt.SmcMo.enHoldSndMsgType)
        {
            pstHoldLmmMsg   = (SMS_LMM_DATA_REQ_STRU *)g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg;
            ulNasMsgLen     = pstHoldLmmMsg->stSmsMsg.ulSmsMsgSize;

            /* ���·����ڴ�ռ� */
            ulMsgLen    = sizeof(SMS_LMM_DATA_REQ_STRU) - 4 + ulNasMsgLen;

            pstLmmMsg = PS_MEM_ALLOC(WUEPS_PID_SMS, ulMsgLen);

            if (VOS_NULL_PTR == pstLmmMsg)
            {
                return;
            }

            PS_MEM_SET(pstLmmMsg, 0, ulMsgLen);

            pstLmmMsg->stSmsMsg.ulSmsMsgSize = ulNasMsgLen;
            PS_MEM_CPY(pstLmmMsg->stSmsMsg.aucSmsMsg, pstHoldLmmMsg->stSmsMsg.aucSmsMsg, ulNasMsgLen);
        }
        else
        {
        }

    }
    /* MTʱ */
    else
    {
        if (NAS_SMS_HOLD_MSG_GU_MT_RP_ACK  == g_SmcPsEnt.SmcMt.enHoldSndMsgType)
        {
            pstHoldGuMsg    = (PMMSMS_UNITDATA_REQ_STRU *)g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg;
            ulNasMsgLen     = pstHoldGuMsg->SmsMsg.ulNasMsgSize;

            /* LTE�µ���Ϣ�ṹ���GU�µ���Ϣ�ṹ�岻һ������Ҫ���·����ڴ�ռ� */
            ulMsgLen    = sizeof(SMS_LMM_DATA_REQ_STRU) - 4 + ulNasMsgLen;


            pstLmmMsg = PS_MEM_ALLOC(WUEPS_PID_SMS, ulMsgLen);

            if (VOS_NULL_PTR == pstLmmMsg)
            {
                return;
            }

            PS_MEM_SET(pstLmmMsg, 0, ulMsgLen);

            pstLmmMsg->stSmsMsg.ulSmsMsgSize = ulNasMsgLen;
            PS_MEM_CPY(pstLmmMsg->stSmsMsg.aucSmsMsg, pstHoldGuMsg->SmsMsg.aucNasMsg, ulNasMsgLen);
        }
        else if (NAS_SMS_HOLD_MSG_LTE_MT_RP_ACK == g_SmcPsEnt.SmcMt.enHoldSndMsgType)
        {
            pstHoldLmmMsg   = (SMS_LMM_DATA_REQ_STRU *)g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg;
            ulNasMsgLen     = pstHoldLmmMsg->stSmsMsg.ulSmsMsgSize;

            /* ���·����ڴ�ռ� */
            ulMsgLen    = sizeof(SMS_LMM_DATA_REQ_STRU) - 4 + ulNasMsgLen;

            pstLmmMsg = PS_MEM_ALLOC(WUEPS_PID_SMS, ulMsgLen);

            if (VOS_NULL_PTR == pstLmmMsg)
            {
                return;
            }

            PS_MEM_SET(pstLmmMsg, 0, ulMsgLen);

            pstLmmMsg->stSmsMsg.ulSmsMsgSize = ulNasMsgLen;
            PS_MEM_CPY(pstLmmMsg->stSmsMsg.aucSmsMsg, pstHoldLmmMsg->stSmsMsg.aucSmsMsg, ulNasMsgLen);
        }
        else
        {
        }
    }

    /* ����CP-DATA��Ϣ */
    if (VOS_NULL_PTR != pstLmmMsg)
    {
        (VOS_VOID)NAS_SMS_SndLmmCpDataReq((VOS_UINT8 *)pstLmmMsg, ulMsgLen);
    }

    /* ǰ���pstLmmMsg��malloc����Ϣ�������֮��Ҫ�ͷ� */
    PS_MEM_FREE(WUEPS_PID_SMS, pstLmmMsg);

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_SMS_BuildGmmCpDataReq
 ��������  : ���ݻ����е���Ϣ����GU�µ�CP_DATA������GMM
 �������  : ��
 �������  : pstLmmMsg:LTE�µ�CP_DATA
             pulMsgLen:CP_DATA��Ϣ����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��28��
    ��    ��   : s00217060
    �޸�����   : DTS2015011309518����

*****************************************************************************/
VOS_VOID  NAS_SMS_ReSendGmmCpDataReq(
    VOS_UINT32                          ulResendMoFlg
)
{
    PMMSMS_UNITDATA_REQ_STRU           *pstHoldGuMsg    = VOS_NULL_PTR;
    SMS_LMM_DATA_REQ_STRU              *pstHoldLmmMsg   = VOS_NULL_PTR;
    PMMSMS_UNITDATA_REQ_STRU           *pstGuMsg        = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulNasMsgLen;

    /* ���֮ǰ����GU�·���CP_DATA,��Ҫ����һ�½ṹ��ת��,
       ����LTE�µ���Ϣ�ṹ���GU�µ���Ϣ�ṹ�岻һ�������ܵ��¸�λ */


    /* MOʱ */
    if (VOS_TRUE == ulResendMoFlg)
    {
        if (NAS_SMS_HOLD_MSG_GU_MO_RP_DATA  == g_SmcPsEnt.SmcMo.enHoldSndMsgType)
        {
            pstHoldGuMsg    = (PMMSMS_UNITDATA_REQ_STRU *)g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg;
            ulNasMsgLen     = pstHoldGuMsg->SmsMsg.ulNasMsgSize;

            ulMsgLen    = sizeof(PMMSMS_UNITDATA_REQ_STRU) - 4 + ulNasMsgLen;


            pstGuMsg = PS_MEM_ALLOC(WUEPS_PID_SMS, ulMsgLen);

            if (VOS_NULL_PTR == pstGuMsg)
            {
                return;
            }

            PS_MEM_SET(pstGuMsg, 0, ulMsgLen);

            pstGuMsg->SmsMsg.ulNasMsgSize   = ulNasMsgLen;
            PS_MEM_CPY(pstGuMsg->SmsMsg.aucNasMsg, pstHoldGuMsg->SmsMsg.aucNasMsg, ulNasMsgLen);
        }
        else
        {
            /* LTE�µ���Ϣ�ṹ���GU�µ���Ϣ�ṹ�岻һ������Ҫ���·����ڴ�ռ� */
            pstHoldLmmMsg   = (SMS_LMM_DATA_REQ_STRU *)g_SmcPsEnt.SmcMo.HoldSndMsg.pMsg;
            ulNasMsgLen     = pstHoldLmmMsg->stSmsMsg.ulSmsMsgSize;

            /* ���·����ڴ�ռ� */
            ulMsgLen    = sizeof(PMMSMS_UNITDATA_REQ_STRU) - 4 + ulNasMsgLen;

            pstGuMsg = PS_MEM_ALLOC(WUEPS_PID_SMS, ulMsgLen);

            if (VOS_NULL_PTR == pstGuMsg)
            {
                return;
            }

            PS_MEM_SET(pstGuMsg, 0, ulMsgLen);

            pstGuMsg->SmsMsg.ulNasMsgSize   = ulNasMsgLen;
            PS_MEM_CPY(pstGuMsg->SmsMsg.aucNasMsg, pstHoldLmmMsg->stSmsMsg.aucSmsMsg, ulNasMsgLen);
        }
    }
    /* MTʱ */
    else
    {
        if (NAS_SMS_HOLD_MSG_GU_MT_RP_ACK  == g_SmcPsEnt.SmcMt.enHoldSndMsgType)
        {
            pstHoldGuMsg    = (PMMSMS_UNITDATA_REQ_STRU *)g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg;
            ulNasMsgLen     = pstHoldGuMsg->SmsMsg.ulNasMsgSize;

            ulMsgLen    = sizeof(PMMSMS_UNITDATA_REQ_STRU) - 4 + ulNasMsgLen;


            pstGuMsg = PS_MEM_ALLOC(WUEPS_PID_SMS, ulMsgLen);

            if (VOS_NULL_PTR == pstGuMsg)
            {
                return;
            }

            PS_MEM_SET(pstGuMsg, 0, ulMsgLen);

            pstGuMsg->SmsMsg.ulNasMsgSize   = ulNasMsgLen;
            PS_MEM_CPY(pstGuMsg->SmsMsg.aucNasMsg, pstHoldGuMsg->SmsMsg.aucNasMsg, ulNasMsgLen);
        }
        else
        {
            /* LTE�µ���Ϣ�ṹ���GU�µ���Ϣ�ṹ�岻һ������Ҫ���·����ڴ�ռ� */
            pstHoldLmmMsg   = (SMS_LMM_DATA_REQ_STRU *)g_SmcPsEnt.SmcMt.HoldSndMsg.pMsg;
            ulNasMsgLen     = pstHoldLmmMsg->stSmsMsg.ulSmsMsgSize;

            /* ���·����ڴ�ռ� */
            ulMsgLen    = sizeof(PMMSMS_UNITDATA_REQ_STRU) - 4 + ulNasMsgLen;

            pstGuMsg = PS_MEM_ALLOC(WUEPS_PID_SMS, ulMsgLen);

            if (VOS_NULL_PTR == pstGuMsg)
            {
                return;
            }

            PS_MEM_SET(pstGuMsg, 0, ulMsgLen);

            pstGuMsg->SmsMsg.ulNasMsgSize   = ulNasMsgLen;
            PS_MEM_CPY(pstGuMsg->SmsMsg.aucNasMsg, pstHoldLmmMsg->stSmsMsg.aucSmsMsg, ulNasMsgLen);
        }

    }

    SMC_SndGmmMsg((VOS_UINT8 *)pstGuMsg,
                  PMMSMS_UNITDATA_REQ,
                  (VOS_UINT16)ulMsgLen) ;             /* �ط���Ϣ                                 */

    /* ǰ���pstGuMsg��malloc����Ϣ�������֮��Ҫ�ͷ� */
    PS_MEM_FREE(WUEPS_PID_SMS, pstGuMsg);

    return;

}


/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

