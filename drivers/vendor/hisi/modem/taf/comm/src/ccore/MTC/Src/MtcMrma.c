/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MtcMrma.c
  �� �� ��   : ����
  ��    ��   : j00174725
  ��������   : 2014��06��16��
  ����޸�   :
  ��������   : ��ģ��������ع��ܺ�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : ������
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MtcRcmInterface.h"
#include "ImsaMtcInterface.h"
#include "MtcCtx.h"
#include "MtcDebug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 �޸���: j00174725; */
#define    THIS_FILE_ID        PS_FILE_ID_MTC_MRMA_C
/*lint +e767 �޸���: j00174725; */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : MTC_SndRcmModemStateInd
 ��������  : MTCģ��֪ͨRCMģ�����Modem״̬
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������
  2.��    ��   : 2015��07��20��
    ��    ��   : zwx247453
    �޸�����   : 3 modem TAS
*****************************************************************************/
VOS_VOID MTC_SndRcmModemStateInd(VOS_VOID)
{
    MTC_RCM_MODEM_STATE_NOTIFY_STRU    *pstModemState;
    MODEM_ID_ENUM_UINT16                enModemId;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvStatus;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enPsSrvStatus;

    enPsSrvStatus                       = TAF_MTC_SRV_CONN_STATE_BUTT;

    /* ������Ϣ�� */
    pstModemState = (MTC_RCM_MODEM_STATE_NOTIFY_STRU *)MTC_ALLOC_MSG_WITH_HDR(sizeof(MTC_RCM_MODEM_STATE_NOTIFY_STRU));
    if (VOS_NULL_PTR == pstModemState)
    {
        MTC_ERROR_LOG("MTC_SndRcmModemStateInd: Alloc Msg Fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstModemState) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MTC_RCM_MODEM_STATE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    MTC_CFG_RCM_MSG_HDR(&pstModemState->stMsgHeader, ID_MTC_RCM_MODEM_STATUS_NOTIFY);

    /* ��д��modem��״̬��Ϣ */
    for (enModemId = 0; enModemId < MODEM_ID_BUTT ; enModemId++)
    {
        enPsSrvStatus           = MTC_GetPsSrvState(enModemId);
        if ((PS_TRUE           == MTC_IsPsSessionInfoExit(enModemId))
         || (TAF_MTC_SRV_EXIST == enPsSrvStatus))
        {
            pstModemState->astModemState[enModemId].enPsSrvConnState        = TAF_MTC_SRV_EXIST;
        }
        else
        {
            pstModemState->astModemState[enModemId].enPsSrvConnState        = TAF_MTC_SRV_NO_EXIST;
        }
        pstModemState->astModemState[enModemId].enModemPowerState       = MTC_GetModemPowerState(enModemId);

        pstModemState->astModemState[enModemId].enModemType             = MTC_RCM_MODEM_0 + enModemId;
        enCsSrvStatus                                                   = MTC_GetCsSrvState(enModemId);

        pstModemState->astModemState[enModemId].enModemRatCfg           = MTC_ConvertToRcmRatCfg(MTC_GetUsimStateInfo(enModemId),
                                                                                                 MTC_GetRatCfgByModemId(enModemId));
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if ((MTC_RCM_MODEM_RAT_CFG_CL == pstModemState->astModemState[enModemId].enModemRatCfg)
         || (MTC_RCM_MODEM_RAT_CFG_C  == pstModemState->astModemState[enModemId].enModemRatCfg))
        {
            pstModemState->astModemState[enModemId].enUsimmCardState    = MTC_GetCsimStateInfo(enModemId);
        }
        else
#endif
        {
            pstModemState->astModemState[enModemId].enUsimmCardState    = MTC_GetUsimStateInfo(enModemId);
        }

        if ( (PS_TRUE           == MTC_IsCsSessionInfoExit(enModemId))
          || (TAF_MTC_SRV_EXIST == enCsSrvStatus) )
        {
            pstModemState->astModemState[enModemId].enCsSrvConnState        = TAF_MTC_SRV_EXIST;
        }
        else
        {
            pstModemState->astModemState[enModemId].enCsSrvConnState        = TAF_MTC_SRV_NO_EXIST;
        }
    }

    /* ��дCDMA״̬��Ϣ */
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enCsSrvConnState   = MTC_GetOutSideCsConnStateInfo(MTC_OUTSIDE_MODEM_CDMA);
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enPsSrvConnState   = MTC_GetOutSidePsConnStateInfo(MTC_OUTSIDE_MODEM_CDMA);
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enModemPowerState  = MTC_GetOutSideModemPowerState(MTC_OUTSIDE_MODEM_CDMA);
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enUsimmCardState   = MTC_GetOutSideModemUsimmState(MTC_OUTSIDE_MODEM_CDMA);
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enModemType        = MTC_RCM_MODEM_OTHER;
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enModemRatCfg      = MTC_RCM_MODEM_RAT_CFG_C;

    /* ������Ϣ */
    MTC_SEND_MSG(pstModemState);

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_SndImsaModem1InfoInd
 ��������  : MTCģ��֪ͨIMSAģ��Modem1��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��05��
    ��    ��   : l00198894
    �޸�����   : VOLTE Rank1������Ŀ
*****************************************************************************/
VOS_VOID MTC_SndImsaModem1InfoInd(VOS_VOID)
{
    MTC_IMSA_MODEM1_INFO_IND_STRU      *pstModem1Info = VOS_NULL_PTR;

    /* IMSAû��Start����Ҫ����Ϣ */
    if (MTC_MODEM_POWER_ON != MTC_GetModemImsaState(MODEM_ID_0))
    {
        return;
    }

    /* ������Ϣ�� */
    pstModem1Info = (MTC_IMSA_MODEM1_INFO_IND_STRU *)MTC_ALLOC_MSG_WITH_HDR(sizeof(MTC_IMSA_MODEM1_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstModem1Info)
    {
        MTC_ERROR_LOG("MTC_SndImsaModem1InfoInd: Alloc Msg Fail!");
        return;
    }

    /* �����Ϣ���� */
    PS_MEM_SET(MTC_GET_MSG_ENTITY(pstModem1Info), 0x00, MTC_GET_MSG_LENGTH(pstModem1Info));

    /* �����Ϣͷ */
    MTC_CFG_IMSA_MSG_HDR(pstModem1Info, ID_MTC_IMSA_MODEM1_INFO_IND);

    /* ��дModem1����Ϣ */
    pstModem1Info->enPowerState = MTC_GetModemPowerState(MODEM_ID_1);

    /* ������Ϣ */
    MTC_SEND_MSG(pstModem1Info);

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_SndRcmModemImsVoiceCapInd
 ��������  : MTCģ��֪ͨRCM IMS���ػ�״̬��IMS��������״̬
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��17��
    ��    ��   : w00316404
    �޸�����   : NEXT Band26��Ŀ
*****************************************************************************/
VOS_VOID MTC_SndRcmModemImsVoiceCapInd(VOS_VOID)
{
    MTC_RCM_IMS_STATE_NOTIFY_STRU              *pstImsStateNotify   = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstImsStateNotify = (MTC_RCM_IMS_STATE_NOTIFY_STRU *)MTC_ALLOC_MSG_WITH_HDR(sizeof(MTC_RCM_IMS_STATE_NOTIFY_STRU));
    if (VOS_NULL_PTR == pstImsStateNotify)
    {
        MTC_ERROR_LOG("MTC_SndRcmModemImsVoiceCapInd: Alloc Msg Fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstImsStateNotify) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MTC_RCM_IMS_STATE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    MTC_CFG_RCM_MSG_HDR(pstImsStateNotify, ID_MTC_RCM_IMS_STATUS_NOTIFY);

    /* �����Ϣ */
    pstImsStateNotify->enIMSPowerState      = MTC_GetModemImsaState(MODEM_ID_0);
    pstImsStateNotify->enIMSVoiceCapState   = MTC_GetModemImsVoiceCap(MODEM_ID_0);

    /* ������Ϣ */
    MTC_SEND_MSG(pstImsStateNotify);

    return;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : MTC_SndRcmTcStatusNtf
 ��������  : MTCģ��֪ͨRCM���ز���״̬
 �������  : MTC_RCM_TC_STATUS_ENUM_UINT16       enTcStatus ���ز���״̬
             MODEM_ID_ENUM_UINT16                enModemId  Modem Id
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��24��
    ��    ��   : h00313353
    �޸�����   : Iteration 19 TAS
*****************************************************************************/
VOS_VOID MTC_SndRcmTcStatusNtf(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_RCM_TC_STATUS_ENUM_UINT16       enTcStatus
)
{
    MTC_RCM_TC_STATUS_NOTIFY_STRU      *pstTcStatus = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstTcStatus = (MTC_RCM_TC_STATUS_NOTIFY_STRU *)MTC_ALLOC_MSG_WITH_HDR(sizeof(MTC_RCM_TC_STATUS_NOTIFY_STRU));
    if (VOS_NULL_PTR == pstTcStatus)
    {
        MTC_ERROR_LOG("MTC_SndRcmTcStatusNtf: Alloc Msg Fail!");
        return;
    }

    /* �����Ϣ���� */
    PS_MEM_SET(MTC_GET_MSG_ENTITY(pstTcStatus), 0x00, MTC_GET_MSG_LENGTH(pstTcStatus));

    /* �����Ϣͷ */
    MTC_CFG_RCM_MSG_HDR(&pstTcStatus->stMsgHeader, ID_MTC_RCM_TC_STATUS_NOTIFY);

    /* �����Ϣ���� */
    pstTcStatus->enModemId            = (MTC_RCM_MODEM_TYPE_ENUM_UINT16)enModemId;
    pstTcStatus->enRatMode            = MTC_RCM_RAT_MODE_CDMA;
    pstTcStatus->enTcStatus           = enTcStatus;

    /* ������Ϣ */
    MTC_SEND_MSG(pstTcStatus);

    return;
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

