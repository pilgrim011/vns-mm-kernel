/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MtcMain.c
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2013��07��30��
  ����޸�   :
  ��������   : MTCģ����Ϣ��������Ӧ����ع���������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��7��30��
    ��    ��   : l60609
    �޸�����   : ������

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MtcMain.h"
#include "MtcComm.h"
#include "MtcCtx.h"
#include "MtcIntrusion.h"
#include "MtcPsTransfer.h"
#include "CmmcaMtcInterface.h"
#include "MtcRfLcdIntrusion.h"
/* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */
#include "TafMtcApi.h"
/* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, End */

#include "ImsaMtcInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 �޸���: l00198894; */
#define    THIS_FILE_ID        PS_FILE_ID_MTC_MAIN_C
/*lint +e767 �޸���: l00198894; */


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* MTCģ�鴦������Modem0 Mma��Ϣ������Ӧ��*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem0MmaTab[] =
{
    {ID_MMA_MTC_POWER_STATE_IND,            MTC_RcvMmaPowerStateInd},           /* Modem0���ػ�״̬֪ͨ */
    {ID_MMA_MTC_RAT_MODE_IND,               MTC_RcvMmaRatModeInd},              /* ����ģʽ֪ͨ */

    {ID_MMA_MTC_CURR_CAMP_PLMN_INFO_IND,    MTC_RcvMmaCurrCampPlmnInfoInd},

    {ID_MMA_MTC_EPLMN_INFO_IND,             MTC_RcvMmaEplmnInfoInd},

    {ID_MMA_MTC_REG_STATUS_IND,             MTC_RcvMmaRegStatusInd},

    {ID_MMA_MTC_IMSA_STATE_IND,             MTC_RcvMmaImsaStateInd},

    {ID_MMA_MTC_IMS_VOICE_CAP_IND,          MTC_RcvMmaImsVoiceCapInd},

    {ID_MMA_MTC_RAT_CFG_IND,                MTC_RcvMmaRatCfgInd},
};

/* MTCģ�鴦������Modem1 Mma��Ϣ������Ӧ��*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem1MmaTab[] =
{
    {ID_MMA_MTC_POWER_STATE_IND,            MTC_RcvMmaPowerStateInd},           /* Modem1���ػ�״̬֪ͨ */
    {ID_MMA_MTC_RAT_MODE_IND,               MTC_RcvMmaRatModeInd},              /* ����ģʽ֪ͨ */

    {ID_MMA_MTC_CURR_CAMP_PLMN_INFO_IND,    MTC_RcvMmaCurrCampPlmnInfoInd},

    {ID_MMA_MTC_EPLMN_INFO_IND,             MTC_RcvMmaEplmnInfoInd},

    {ID_MMA_MTC_REG_STATUS_IND,             MTC_RcvMmaRegStatusInd},

    {ID_MMA_MTC_RAT_CFG_IND,                MTC_RcvMmaRatCfgInd},
};

#if (3 == MULTI_MODEM_NUMBER)

/* MTCģ�鴦������Modem2 Mma��Ϣ������Ӧ��*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem2MmaTab[] =
{
    {ID_MMA_MTC_POWER_STATE_IND,            MTC_RcvMmaPowerStateInd},           /* Modem2���ػ�״̬֪ͨ */
    {ID_MMA_MTC_RAT_MODE_IND,               MTC_RcvMmaRatModeInd},              /* ����ģʽ֪ͨ */
    {ID_MMA_MTC_CURR_CAMP_PLMN_INFO_IND,    MTC_RcvMmaCurrCampPlmnInfoInd},
    {ID_MMA_MTC_EPLMN_INFO_IND,             MTC_RcvMmaEplmnInfoInd},
    {ID_MMA_MTC_REG_STATUS_IND,             MTC_RcvMmaRegStatusInd},
    {ID_MMA_MTC_RAT_CFG_IND,                MTC_RcvMmaRatCfgInd},
};

#endif

/* MTCģ�鴦������Modem0 Taf��Ϣ������Ӧ��*/
const MTC_MSG_PROC_STRU g_astMtcMsgProcModem0TafTab[] =
{
    {ID_MTC_CS_SERVICE_INFO_IND,            MTC_RcvTafCsSrvInfoInd},            /* CS��ҵ��״̬֪ͨ */
};

/* MTCģ�鴦������Modem1 Taf��Ϣ������Ӧ��*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem1TafTab[] =
{
    {ID_MTC_CS_SERVICE_INFO_IND,            MTC_RcvTafCsSrvInfoInd},            /* CS��ҵ��״̬֪ͨ */
};

/* MTCģ�鴦������Modem2 Taf��Ϣ������Ӧ��*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem2TafTab[] =
{
    {ID_MTC_CS_SERVICE_INFO_IND,            MTC_RcvTafCsSrvInfoInd},            /* CS��ҵ��״̬֪ͨ */
};

/* MTCģ�鴦������Modem1 GAS��Ϣ������Ӧ��*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem1GasTab[] =
{
    {ID_RRC_MTC_INTRUSION_ACTION_SET_CNF,   MTC_RcvIntrusionActionSetCnf},      /* ���ſ��ƿ������ûظ� */
    {ID_RRC_MTC_INTRUSION_BAND_SET_CNF,     MTC_RcvIntrusionBandSetCnf},        /* ���ſ��ƽ���Ƶ�����ûظ� */
    {ID_RRC_MTC_INTRUSION_BAND_INFO_IND,    MTC_RcvIntrusionBandInfoInd},       /* Ƶ����Ϣ�����ϱ� */

    {ID_RRC_MTC_NCELL_INFO_IND,             MTC_RcvRrcNcellInfoInd},
    /* Added by Y00213812 for RF&LCD���Ź��, 2014-02-07, begin */
    {ID_RRC_MTC_USING_FREQ_IND,             MTC_RcvRrcUsingFreqInd},            /* ����������ϱ�Ƶ��仯��Ϣ */
    /* Added by Y00213812 for RF&LCD���Ź��, 2014-02-07, end */
    /* Added by Y00213812 for ����������ѡ, 2014-04-10, begin */
    {ID_RRC_MTC_GSM_CELL_INFO_IND,          MTC_RcvGsmCellInfoInd},             /* �ϱ�Ƶ����ź�ǿ����Ϣ */
    /* Added by Y00213812 for ����������ѡ, 2014-04-10, end */

    {ID_RRC_MTC_GSM_CELL_INFO_EX_IND,       MTC_RcvGsmCellInfoExInd},           /* GAS�ϱ�С����չ��Ϣ��Ϣ */

};

const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem2GasTab[] =
{
    {ID_RRC_MTC_NCELL_INFO_IND,             MTC_RcvRrcNcellInfoInd},
   // {ID_RRC_MTC_USING_FREQ_IND,             MTC_RcvRrcUsingFreqInd},            /* ����������ϱ�Ƶ��仯��Ϣ */
   // {ID_RRC_MTC_GSM_CELL_INFO_IND,          MTC_RcvGsmCellInfoInd},             /* �ϱ�Ƶ����ź�ǿ����Ϣ */
    {ID_RRC_MTC_GSM_CELL_INFO_EX_IND,       MTC_RcvGsmCellInfoExInd},           /* GAS�ϱ�С����չ��Ϣ��Ϣ */

};


/* MTCģ�鴦������Modem0 TD-SCDMA��Ϣ������Ӧ��*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem0TdsTab[] =
{
    {ID_RRC_MTC_INTRUSION_ACTION_SET_CNF,   MTC_RcvIntrusionActionSetCnf},      /* ���ſ��ƿ������ûظ� */
    {ID_RRC_MTC_INTRUSION_BAND_SET_CNF,     MTC_RcvIntrusionBandSetCnf},        /* ���ſ��ƽ���Ƶ�����ûظ� */
    {ID_RRC_MTC_INTRUSION_BAND_INFO_IND,    MTC_RcvIntrusionBandInfoInd},       /* Ƶ����Ϣ�����ϱ� */
    {ID_RRC_MTC_AREA_LOST_IND,              MTC_RcvRrcAreaLostInd},             /* ����㶪����Ϣ�����ϱ� */
    /* Added by Y00213812 for RF&LCD���Ź��, 2014-02-07, begin */
    {ID_RRC_MTC_USING_FREQ_IND,             MTC_RcvRrcUsingFreqInd},            /* ����������ϱ�Ƶ��仯��Ϣ */
    /* Added by Y00213812 for RF&LCD���Ź��, 2014-02-07, end */

    /* Added by Y00213812 for ����������ѡ, 2014-02-07, begin */
    {ID_RRC_MTC_AREA_AVALIABLE_IND,         MTC_RcvRrcAreaAvaliableInd},        /* ���������ָ���Ϣ�����ϱ� */
    /* Added by Y00213812 for ����������ѡ, 2014-02-07, end */
};

/* MTCģ�鴦������Modem0 LTE��Ϣ������Ӧ��*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem0LteTab[] =
{
    {ID_RRC_MTC_INTRUSION_ACTION_SET_CNF,   MTC_RcvIntrusionActionSetCnf},      /* ���ſ��ƿ������ûظ� */
    {ID_RRC_MTC_INTRUSION_BAND_SET_CNF,     MTC_RcvIntrusionBandSetCnf},        /* ���ſ��ƽ���Ƶ�����ûظ� */
    {ID_RRC_MTC_INTRUSION_BAND_INFO_IND,    MTC_RcvIntrusionBandInfoInd},       /* Ƶ����Ϣ�����ϱ� */
    {ID_RRC_MTC_AREA_LOST_IND,              MTC_RcvRrcAreaLostInd},             /* ����㶪����Ϣ�����ϱ� */
    {ID_RRC_MTC_AREA_AVALIABLE_IND,         MTC_RcvRrcAreaAvaliableInd},        /* ���������ָ���Ϣ�����ϱ� */
    /* Added by Y00213812 for RF&LCD���Ź��, 2014-02-07, begin */
    {ID_RRC_MTC_USING_FREQ_IND,             MTC_RcvRrcUsingFreqInd},            /* ����������ϱ�Ƶ��仯��Ϣ */
    /* Added by Y00213812 for RF&LCD���Ź��, 2014-02-07, end */
};

/* Added by Y00213812 for RF&LCD���Ź��, 2014-02-07, begin */
/* MTCģ�鴦������Modem0Gas��Ϣ������Ӧ��*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem0GasTab[] =
{
    {ID_RRC_MTC_USING_FREQ_IND,             MTC_RcvRrcUsingFreqInd},            /* ����������ϱ�Ƶ��仯��Ϣ */
};

/* MTCģ�鴦������Modem0 Was��Ϣ������Ӧ��*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem0WasTab[] =
{
    {ID_RRC_MTC_USING_FREQ_IND,             MTC_RcvRrcUsingFreqInd},            /* ����������ϱ�Ƶ��仯��Ϣ */
};
/* Added by Y00213812 for RF&LCD���Ź��, 2014-02-07, end */

/* Added by l60609 for L-C��������Ŀ, 2014-02-19, Begin */
/* MTCģ�鴦������CMMCA��Ϣ������Ӧ��*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcCmmcaTab[] =
{
    {ID_CMMCA_MTC_OTHER_RAT_INFO_IND,       MTC_RcvCmmcaOtherRatInfoInd},
};
/* Added by l60609 for L-C��������Ŀ, 2014-02-19, End */

/* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcMtcTab[] =
{
    {ID_MSG_MTC_CDMA_CONN_STATE_IND,          MTC_ProcSetCdmaExtModemConnStateInfo},
    {ID_MSG_MTC_MODEM_SERVICE_CONN_STATE_IND, MTC_ProcModemServiceConnStateInd},
    {ID_MSG_MTC_USIMM_STATE_IND,              MTC_ProcUsimmStateInd},
    {ID_MSG_MTC_BEGIN_SESSION_IND,            MTC_ProcBeginSessionInd},
    {ID_MSG_MTC_END_SESSION_IND,              MTC_ProcEndSessionInd},
};

/* MTCģ�鴦������Modem0 Mta��Ϣ������Ӧ��*/
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem0MtaTab[] =
{
    {ID_MTA_MTC_GSM_CELLINFO_QRY_REQ,       MTC_RcvMtaGsmCellInfoQryReq},
};

#if (FEATURE_ON == FEATURE_IMS)
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcImsaTab[] =
{
    {ID_IMSA_MTC_SRV_CONN_STATUS_NOTIFY,   MTC_ProcImsaSrvConnStateInfo},
};
#endif
/* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, End */

const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem0TcStatTab[] =
{
    {ID_NAS_MTC_TC_STATUS_INFO_IND,        MTC_RcvTcStatusInfo},                /* TC����״̬֪ͨ */
};
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem1TcStatTab[] =
{
    {ID_NAS_MTC_TC_STATUS_INFO_IND,        MTC_RcvTcStatusInfo},                /* TC����״̬֪ͨ */
};
#if (3 == MULTI_MODEM_NUMBER)
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem2TcStatTab[] =
{
    {ID_NAS_MTC_TC_STATUS_INFO_IND,        MTC_RcvTcStatusInfo},                /* TC����״̬֪ͨ */
};
#endif
const MTC_MSG_PROC_STRU                 g_astMtcMsgProcModem0ETcStatTab[] =
{
    {ID_NAS_MTC_TC_STATUS_INFO_IND,        MTC_RcvTcStatusInfo},                /* TC����״̬֪ͨ */
};

/*****************************************************************************
  3 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : MTC_SearchMsgProcTab
 ��������  : ������Ϣ������
 �������  : ulMsgCnt       ��Ϣ�б�Ĵ�С
             *pstMsg        ������Ϣ
             pstMsgProcTab  ��Ϣ�б�
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : j00174725
    �޸�����   : V9R1 ���ſ�����Ŀ
  2.��    ��   : 2014��02��13��
    ��    ��   : f00179208
    �޸�����   : Jazz Narrow Band dcs��Ŀ
*****************************************************************************/
VOS_UINT32 MTC_SearchMsgProcTab(
    VOS_UINT32                          ulMsgCnt,
    VOS_VOID                           *pstMsg,
    const MTC_MSG_PROC_STRU            *pstMsgProcTab
)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulMsgName;

    /* ����Ϣ���л�ȡMSG ID */
    ulMsgName  = ((MSG_HEADER_STRU*)pstMsg)->ulMsgName;

    /* ���������Ϣ�ַ� */
    for (ulLoop = 0; ulLoop < ulMsgCnt; ulLoop++)
    {
        if (pstMsgProcTab[ulLoop].ulMsgType == ulMsgName)
        {
            /* �쳣���� */
            if (VOS_NULL_PTR != pstMsgProcTab[ulLoop].pProcMsgFunc)
            {
                pstMsgProcTab[ulLoop].pProcMsgFunc(pstMsg);
            }
            break;
        }
    }

    /* û���ҵ�ƥ�����Ϣ */
    if (ulMsgCnt == ulLoop)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : MTC_RcvModem0MmaMsg
 ��������  : ��������Modem0 Mma����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : j00174725
    �޸�����   : V9R1 ���ſ�����Ŀ

*****************************************************************************/
VOS_VOID MTC_RcvModem0MmaMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtcMsgProcModem0MmaTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem0MmaTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem0MmaTab���������Ϣ�ַ�*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem0MmaTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem0MmaMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_RcvModem1MmaMsg
 ��������  : ��������Modem1 Mma����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : j00174725
    �޸�����   : V9R1 ���ſ�����Ŀ

*****************************************************************************/
VOS_VOID MTC_RcvModem1MmaMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtcMsgProcModem1MmaTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem1MmaTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem1MmaTab���������Ϣ�ַ�*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem1MmaTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem1MmaMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_RcvModem0TafMsg
 ��������  : ��������Modem0 Taf����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ

*****************************************************************************/
VOS_VOID MTC_RcvModem0TafMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtcMsgProcModem0TafTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem0TafTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem0TafTab���������Ϣ�ַ�*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem0TafTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem0TafMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_RcvModem1TafMsg
 ��������  : ��������Modem1 Taf����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ

*****************************************************************************/
VOS_VOID MTC_RcvModem1TafMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtcMsgProcModem1TafTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem1TafTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem1TafTab���������Ϣ�ַ�*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem1TafTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem1TafMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_RcvModem1GasMsg
 ��������  : ��������Modem1 Gas����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ

*****************************************************************************/
VOS_VOID MTC_RcvModem1GasMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtcMsgProcModem1GasTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem1GasTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem1GasTab���������Ϣ�ַ�*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem1GasTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem1GasMsg: Msg Id is invalid!");
    }

    return;
}

#if (3 == MULTI_MODEM_NUMBER)
/*****************************************************************************
 �� �� ��  : MTC_RcvModem2MmaMsg
 ��������  : ��������Modem2 Mma����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��30��
    ��    ��   : w00281933
    �޸�����   : �����������������������Ӵ���Modem2��MMA��Ϣ

*****************************************************************************/
VOS_VOID MTC_RcvModem2MmaMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtcMsgProcModem2MmaTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem2MmaTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem2MmaTab���������Ϣ�ַ�*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem2MmaTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem2MmaMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_RcvModem2TafMsg
 ��������  : ��������Modem2 Taf����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��30��
    ��    ��   : w00281933
    �޸�����   : �����������������������Ӵ���Modem2��TAF��Ϣ

*****************************************************************************/
VOS_VOID MTC_RcvModem2TafMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtcMsgProcModem2TafTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem2TafTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem2TafTab���������Ϣ�ַ�*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem2TafTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem2TafMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_RcvModem2GasMsg
 ��������  : ��������Modem2 Gas����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��30��
    ��    ��   : w00281933
    �޸�����   : �����������������������Ӵ���Modem2��GAS��Ϣ

*****************************************************************************/
VOS_VOID MTC_RcvModem2GasMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtcMsgProcModem2GasTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem2GasTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem2GasTab���������Ϣ�ַ�*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem2GasTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem2GasMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_RcvModem2TcMsg
 ��������  : ��������Tc����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��20��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MTC_RcvModem2TcMsg(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtcMsgProcModem2TcStatTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem2TcStatTab) / sizeof(MTC_MSG_PROC_STRU);

    /* g_astMtcMsgProcModem2TcStatTab���������Ϣ�ַ� */
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem2TcStatTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem2TcMsg: Msg Id is invalid!");
    }

    return;
}
#endif

/*****************************************************************************
 �� �� ��  : MTC_RcvModem0TdsMsg
 ��������  : ��������Modem0 TD-SCDMA����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ

*****************************************************************************/
VOS_VOID MTC_RcvModem0TdsMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtcMsgProcModem0TdsTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem0TdsTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem0TdsTab���������Ϣ�ַ�*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem0TdsTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem0TdsMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_RcvModem0LteMsg
 ��������  : ��������Modem0 Lte����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ

*****************************************************************************/
VOS_VOID MTC_RcvModem0LteMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtcMsgProcModem0LteTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem0LteTab)/sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem0LteTab���������Ϣ�ַ�*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem0LteTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem0LteMsg: Msg Id is invalid!");
    }

    return;
}

/* Added by l60609 for L-C��������Ŀ, 2014-02-19, Begin */
/*****************************************************************************
 �� �� ��  : MTC_RcvCmmcaMsg
 ��������  : ��������CMMCA����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��19��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MTC_RcvCmmcaMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtcMsgProcCmmcaTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtcMsgProcCmmcaTab)/sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcCmmcaTab���������Ϣ�ַ�*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcCmmcaTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvCmmcaMsg: Msg Id is invalid!");
    }

    return;
}
/* Added by l60609 for L-C��������Ŀ, 2014-02-19, End */

/* Added by Y00213812 for RF&LCD���Ź��, 2014-02-07, begin */
/*****************************************************************************
 �� �� ��  : MTC_RcvModem0GasMsg
 ��������  : ��������Modem0Gas����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��03��07��
    ��    ��   : Y00213812
    �޸�����   : RF&LCD���Ź����Ŀ

*****************************************************************************/
VOS_VOID MTC_RcvModem0GasMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtcMsgProcModem0GasTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem0GasTab)/sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem0GasTab���������Ϣ�ַ�*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem0GasTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem0GasMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_RcvModem0WasMsg
 ��������  : ��������Modem0Was����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��03��07��
    ��    ��   : Y00213812
    �޸�����   : RF&LCD���Ź����Ŀ

*****************************************************************************/
VOS_VOID MTC_RcvModem0WasMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtcMsgProcModem0WasTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem0WasTab)/sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem0WasTab���������Ϣ�ַ�*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem0WasTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem0WasMsg: Msg Id is invalid!");
    }

    return;
}
/* Added by Y00213812 for RF&LCD���Ź��, 2014-02-07, end */

/*****************************************************************************
 �� �� ��  : MTC_RcvModem0MtaMsg
 ��������  : ��������Modem0 MTA����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��17��
    ��    ��   : l00198894
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MTC_RcvModem0MtaMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtcMsgProcModem0MtaTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem0MtaTab)/sizeof(MTC_MSG_PROC_STRU);

    /* g_astMtcMsgProcModem0MtaTab���������Ϣ�ַ� */
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem0MtaTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem0MtaMsg: Msg Id is invalid!");
    }

    return;
}

/* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */
/*****************************************************************************
 �� �� ��  : MTC_RcvMtcMsg
 ��������  : ��������MTC�ڲ�����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��16��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MTC_RcvMtcMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtcMsgProcMtcTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtcMsgProcMtcTab)/sizeof(MTC_MSG_PROC_STRU);

    /* g_astMtcMsgProcMtcTab���������Ϣ�ַ� */
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcMtcTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvMtcMsg: Msg Id is invalid!");
    }

    return;
}

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : MTC_RcvImsaMsg
 ��������  : ��������IMSA�ڲ�����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��6��16��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MTC_RcvImsaMsg(struct MsgCB *pstMsg)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtcMsgProcImsaTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtcMsgProcImsaTab)/sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcImsaTab���������Ϣ�ַ�*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcImsaTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvImsaMsg: Msg Id is invalid!");
    }

    return;
}
#endif

/*****************************************************************************
 �� �� ��  : MTC_RcvModem0TcMsg
 ��������  : ��������Tc����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��6��
    ��    ��   : wx270776
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MTC_RcvModem0TcMsg(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtcMsgProcModem0TcStatTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem0TcStatTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem0TcStatTab���������Ϣ�ַ�*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem0TcStatTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem0TcMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_RcvModem1TcMsg
 ��������  : ��������Tc����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��6��
    ��    ��   : wx270776
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MTC_RcvModem1TcMsg(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtcMsgProcModem1TcStatTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem1TcStatTab) / sizeof(MTC_MSG_PROC_STRU);

    /*g_astMtcMsgProcModem1TcStatTab���������Ϣ�ַ�*/
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem1TcStatTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem1TcMsg: Msg Id is invalid!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_RcvModem0ETcMsg
 ��������  : ��������Tc����Ϣ
 �������  : struct MsgCB *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��6��
    ��    ��   : wx270776
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MTC_RcvModem0ETcMsg(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulMsgCnt;
    VOS_UINT32                          ulRst;

    /* ��g_astMtcMsgProcModem0ETcStatTab�л�ȡ��Ϣ���� */
    ulMsgCnt = sizeof(g_astMtcMsgProcModem0ETcStatTab) / sizeof(MTC_MSG_PROC_STRU);

    /* g_astMtcMsgProcModem0ETcStatTab���������Ϣ�ַ� */
    ulRst = MTC_SearchMsgProcTab(ulMsgCnt, pstMsg, g_astMtcMsgProcModem0ETcStatTab);

    /* û���ҵ�ƥ�����Ϣ */
    if (VOS_ERR == ulRst)
    {
        MTC_ERROR_LOG("MTC_RcvModem0ETcMsg: Msg Id is invalid!");
    }

    return;
}

/* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, End */

/*****************************************************************************
 �� �� ��  : MTC_ProcMsg
 ��������  : MTCģ����Ϣ������
 �������  : MsgBlock* pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��13��
    ��    ��   : j00174725
    �޸�����   :  V9R1 ���ſ�����Ŀ

  2.��    ��   : 2014��11��17��
    ��    ��   : l00198894
    �޸�����   : ECID�����Ʒ�߶�������

  3.��    ��   : 2015��5��6��
    ��    ��   : wx270776
    �޸�����   : TAS���ز���״̬�ϱ�

  4.��    ��   : 2015��05��30��
   ��    ��   : w00281933
   �޸�����   : Modified for The TSTS Project

  5.��    ��   : 2015��7��20��
    ��    ��   : zwx247453
    �޸�����   : 3 mdoem TAS
*****************************************************************************/
VOS_VOID MTC_ProcMsg(MsgBlock* pMsg)
{
    if (VOS_NULL_PTR == pMsg)
    {
        MTC_ERROR_LOG("MTC_ProcMsg: pMsg Null.");
        return;
    }

    /* ��Ϣ�ķַ����� */
    switch (pMsg->ulSenderPid)
    {
        /* ����MMA����Ϣ */
        case I0_WUEPS_PID_MMA:
            MTC_RcvModem0MmaMsg(pMsg);
            break;

        case I1_WUEPS_PID_MMA:
            MTC_RcvModem1MmaMsg(pMsg);
            break;

        /* ����TAF����Ϣ */
        case I0_WUEPS_PID_TAF:
            MTC_RcvModem0TafMsg(pMsg);
            break;

        case I1_WUEPS_PID_TAF:
            MTC_RcvModem1TafMsg(pMsg);
            break;

        case I0_WUEPS_PID_TC:
            MTC_RcvModem0TcMsg(pMsg);
            break;

        case I1_WUEPS_PID_TC:
            MTC_RcvModem1TcMsg(pMsg);
            break;

        case PS_PID_TC:
            MTC_RcvModem0ETcMsg(pMsg);
            break;

        /* ����modem1 G��������Ϣ */
        case I1_UEPS_PID_GAS:
            MTC_RcvModem1GasMsg(pMsg);
            return;
        /* ����modem1 G��������Ϣ */
        case I0_UEPS_PID_GAS:
            MTC_RcvModem0GasMsg(pMsg);
            return;

        /* ����modem1 W��������Ϣ */
        case WUEPS_PID_WRR:
            MTC_RcvModem0WasMsg(pMsg);
            return;

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
        /* ����modem0 T��������Ϣ */
        case TPS_PID_RRC:
            MTC_RcvModem0TdsMsg(pMsg);
            return;
#endif

#if (FEATURE_ON == FEATURE_LTE)
        /* ����modem0 L��������Ϣ */
        case PS_PID_ERRC:
            MTC_RcvModem0LteMsg(pMsg);
            return;
#endif

        /* Added by l60609 for L-C��������Ŀ, 2014-02-19, Begin */
        /* ����CBPCA����Ϣ */
        case WUEPS_PID_CMMCA:
            MTC_RcvCmmcaMsg(pMsg);
            return;
        /* Added by l60609 for L-C��������Ŀ, 2014-02-19, End */

        /* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */
        case UEPS_PID_MTC:
            MTC_RcvMtcMsg(pMsg);
            return;

        case UEPS_PID_MTA:
            MTC_RcvModem0MtaMsg(pMsg);
            return;

#if (FEATURE_ON == FEATURE_IMS)
        case PS_PID_IMSA:
            MTC_RcvImsaMsg(pMsg);
            return;
#endif
        /* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, End */

#if (3 == MULTI_MODEM_NUMBER)
        case I2_WUEPS_PID_MMA:
            MTC_RcvModem2MmaMsg(pMsg);
            break;

        case I2_WUEPS_PID_TAF:
            MTC_RcvModem2TafMsg(pMsg);
            break;

        /* ����modem2 G��������Ϣ */
        case I2_UEPS_PID_GAS:
            MTC_RcvModem2GasMsg(pMsg);
            return;

        case I2_WUEPS_PID_TC:
            MTC_RcvModem2TcMsg(pMsg);
            break;
#endif

        default:
            return;
    }
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


