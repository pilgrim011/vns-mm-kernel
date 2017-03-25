/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMtaUnsolicitedReport.c
  �� �� ��   : ����
  ��    ��   : ��ѧ��
  ��������   : 2013��4��11��
  ����޸�   :
  ��������   : MTAģ����atģ�齻�������ϱ��������Ĵ�����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��4��11��
    ��    ��   : z00161729
    �޸�����   : �����ϱ�AT�������������C��

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-2, begin */
#include "TafMtaUnSolicitedReport.h"
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-2, end */

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767 */
#define    THIS_FILE_ID                 PS_FILE_ID_TAF_MTA_UNSILICITED_REPORT_C
/*lint +e767 */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-1, begin */
/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtSetCurcNotify
 ��������  : mta�յ�ID_AT_MTA_SET_CURC_NOTIFY��Ϣ������
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��1��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C����������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetCurcNotify(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                            *pstAtMtaMsg             = VOS_NULL_PTR;
    AT_MTA_CURC_SET_NOTIFY_STRU                *pstAtMtaSetCurcNotify   = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU                 *pstCurcRptCtrl          = VOS_NULL_PTR;

    pstAtMtaMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstAtMtaSetCurcNotify   = (AT_MTA_CURC_SET_NOTIFY_STRU *)pstAtMtaMsg->aucContent;
    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();

    /* ����CURCȫ�ֱ��� */
    pstCurcRptCtrl->enStatusRptGeneralControl = pstAtMtaSetCurcNotify->enCurcRptType;
    PS_MEM_CPY(pstCurcRptCtrl->aucRptCfg, pstAtMtaSetCurcNotify->aucRptCfg, sizeof(pstCurcRptCtrl->aucRptCfg));

    /* ��STK������Ϣ֪ͨ����CURC���� */
    TAF_MTA_SndStkCurcRptCfgInfoInd(pstAtMtaSetCurcNotify);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtQryCurcReq
 ��������  : mta�յ�ID_AT_MTA_QRY_CURC_REQ��Ϣ������
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��1��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C����������

*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtQryCurcReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                            *pstAtMtaMsg             = VOS_NULL_PTR;
    TAF_SDC_CURC_RPT_CTRL_STRU                 *pstCurcRptCtrl          = VOS_NULL_PTR;
    MTA_AT_CURC_QRY_CNF_STRU                    stQryCurcCnf;

    pstAtMtaMsg             = (AT_MTA_MSG_STRU *)pMsg;

    /* ��ȡCURCȫ�ֱ��� */
    pstCurcRptCtrl          = TAF_SDC_GetCurcRptCtrl();

    /* �����Ϣ���� */
    PS_MEM_SET(&stQryCurcCnf, 0x00, sizeof(stQryCurcCnf));
    stQryCurcCnf.enResult       = MTA_AT_RESULT_NO_ERROR;
    stQryCurcCnf.enCurcRptType  = (AT_MTA_RPT_GENERAL_CTRL_TYPE_ENUM_UINT8)
                                    pstCurcRptCtrl->enStatusRptGeneralControl;

    PS_MEM_CPY(stQryCurcCnf.aucRptCfg, pstCurcRptCtrl->aucRptCfg, sizeof(stQryCurcCnf.aucRptCfg));

    /* ��AT���Ͳ�ѯCURC�ظ� */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)&(pstAtMtaMsg->stAppCtrl),
                     ID_MTA_AT_CURC_QRY_CNF,
                     sizeof(stQryCurcCnf),
                     (VOS_UINT8*)&stQryCurcCnf);

    return;
}
/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtSetUnsolicitedRptReq
 ��������  : mta�յ�ID_AT_MTA_SET_UNSOLICITED_RPT_REQ��Ϣ������
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��1��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C����������
  2.��    ��   : 2013��5��25��
    ��    ��   : s00217060
    �޸�����   : for DTS2013052406352:
                 DSFLOWRPT��������ͨ��ID_MSG_TAF_PS_CONFIG_DSFLOW_RPT_REQ��APS����
  3.��    ��   : 2014��8��18��
    ��    ��   : w00242748
    �޸�����   : DTS2014082204531:CREG=1��CGREG=1����֮��CREG�����ϱ���CGREG�����ϱ�
                 �����ϱ���
  4.��    ��   : 2015��11��19��
    ��    ��   : h00360002
    �޸�����   : Ϊctzr���ctze�ϱ���ʽ
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtSetUnsolicitedRptReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                            *pstAtMtaMsg             = VOS_NULL_PTR;
    AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU        *pstSetUnsolicitedRptReq = VOS_NULL_PTR;
    MTA_AT_UNSOLICITED_RPT_SET_CNF_STRU         stSetUnsolicitedRptCnf;
    TAF_SDC_RPT_CMD_INDEX_ENUM_UINT8            enRptCmdIndex;
    VOS_UINT32                                  ulRptCmdStatus;

    pstAtMtaMsg             = (AT_MTA_MSG_STRU *)pMsg;
    pstSetUnsolicitedRptReq = (AT_MTA_UNSOLICITED_RPT_SET_REQ_STRU *)pstAtMtaMsg->aucContent;

    /* ���µ����������������ϱ���ȫ�ֱ��� */
    switch (pstSetUnsolicitedRptReq->enReqType)
    {
        case AT_MTA_SET_MODE_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_MODE;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucModeRptFlg;
            break;

        case AT_MTA_SET_SRVST_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_SRVST;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucSrvstRptFlg;
            break;

        case AT_MTA_SET_RSSI_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_RSSI;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucRssiRptFlg;
            break;

        case AT_MTA_SET_TIME_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_TIME;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucTimeRptFlg;
            break;

        case AT_MTA_SET_CTZR_RPT_TYPE:

            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucCtzrRptFlg;

            /* �����CTZE�����CTZE�ϱ�ʹ��,CTZVȥʹ��, �����CTZV�����CTZV�ϱ�ʹ��,CTZEȥʹ��, �����ȥʹ�� */
            if (MTA_TAF_CTZR_CTZE == (MTA_TAF_CTZR_TYPE_ENUM_UINT32)ulRptCmdStatus)
            {
                TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CTZE, VOS_TRUE);
                enRptCmdIndex   = TAF_SDC_RPT_CMD_CTZV;
                ulRptCmdStatus = VOS_FALSE;
            }
            else if (MTA_TAF_CTZR_CTZV == (MTA_TAF_CTZR_TYPE_ENUM_UINT32)ulRptCmdStatus)
            {
                TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CTZV, VOS_TRUE);
                enRptCmdIndex   = TAF_SDC_RPT_CMD_CTZE;
                ulRptCmdStatus = VOS_FALSE;
            }
            else
            {
                TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CTZE, VOS_FALSE);
                enRptCmdIndex   = TAF_SDC_RPT_CMD_CTZV;
                ulRptCmdStatus = VOS_FALSE;
            }
            break;

        /* DSFLOWRPT��������ͨ��ID_MSG_TAF_PS_CONFIG_DSFLOW_RPT_REQ��APS���£��˴�ɾ�� */

        case AT_MTA_SET_SIMST_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_SIMST;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucSimstRptFlg;
            break;


        case AT_MTA_SET_CREG_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_CREG;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucCregRptFlg;

            TAF_SDC_SetCregType(pstSetUnsolicitedRptReq->u.ucCregRptFlg);
            break;

        case AT_MTA_SET_CGREG_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_CGREG;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucCgregRptFlg;

            TAF_SDC_SetCgregType(pstSetUnsolicitedRptReq->u.ucCgregRptFlg);
            break;

        case AT_MTA_SET_CEREG_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_CEREG;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucCeregRptFlg;

            TAF_SDC_SetCeregType(pstSetUnsolicitedRptReq->u.ucCeregRptFlg);
            break;
        case AT_MTA_SET_CSID_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_CSID;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucCsidRptFlg;
            break;
        case AT_MTA_SET_CLOCINFO_RPT_TYPE:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_CLOCINFO;
            ulRptCmdStatus  = (VOS_UINT32)pstSetUnsolicitedRptReq->u.ucClocinfoRptFlg;
            break;
        default:
            enRptCmdIndex   = TAF_SDC_RPT_CMD_BUTT;
            ulRptCmdStatus  = VOS_TRUE;
            break;
    }

    TAF_SDC_UpdateRptCmdStatus(enRptCmdIndex, ulRptCmdStatus);

    /* �����Ϣ���� */
    PS_MEM_SET(&stSetUnsolicitedRptCnf, 0x00, sizeof(stSetUnsolicitedRptCnf));
    stSetUnsolicitedRptCnf.enResult = MTA_AT_RESULT_NO_ERROR;

    /* ��AT�������ûظ� */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)&(pstAtMtaMsg->stAppCtrl),
                     ID_MTA_AT_UNSOLICITED_RPT_SET_CNF,
                     sizeof(stSetUnsolicitedRptCnf),
                     (VOS_UINT8*)&stSetUnsolicitedRptCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvAtQryUnsolicitedRptReq
 ��������  : mta�յ�ID_AT_MTA_QRY_UNSOLICITED_RPT_REQ��Ϣ������
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��1��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C����������
  2.��    ��   : 2015��11��17��
    ��    ��   : h00360002
    �޸�����   : CTZR������CTZE�ϱ�
*****************************************************************************/
VOS_VOID TAF_MTA_RcvAtQryUnsolicitedRptReq(VOS_VOID *pMsg)
{
    AT_MTA_MSG_STRU                            *pstAtMtaMsg             = VOS_NULL_PTR;
    AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU        *pstQryUnsolicitedRptReq = VOS_NULL_PTR;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU          *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;
    MTA_AT_UNSOLICITED_RPT_QRY_CNF_STRU         stQryUnsolicitedRptCnf;

    pstAtMtaMsg                 = (AT_MTA_MSG_STRU *)pMsg;
    pstQryUnsolicitedRptReq     = (AT_MTA_UNSOLICITED_RPT_QRY_REQ_STRU *)pstAtMtaMsg->aucContent;

    /* ��ȡ�������������ϱ���ȫ�ֱ��� */
    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    PS_MEM_SET(&stQryUnsolicitedRptCnf, 0x00, sizeof(stQryUnsolicitedRptCnf));
    stQryUnsolicitedRptCnf.enReqType = pstQryUnsolicitedRptReq->enReqType;
    stQryUnsolicitedRptCnf.enResult  = MTA_AT_RESULT_NO_ERROR;

    switch (pstQryUnsolicitedRptReq->enReqType)
    {
        case AT_MTA_QRY_TIME_RPT_TYPE:
            stQryUnsolicitedRptCnf.u.ucTimeRptFlg =
                        (VOS_UINT8)TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                                TAF_SDC_RPT_CMD_TIME);
            break;

        case AT_MTA_QRY_CTZR_RPT_TYPE:
            if (VOS_TRUE == (VOS_UINT8)TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                    TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                    TAF_SDC_RPT_CMD_CTZV))
            {
                stQryUnsolicitedRptCnf.u.ucCtzrRptFlg = MTA_TAF_CTZR_CTZV;
            }
            else if (VOS_TRUE == (VOS_UINT8)TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                    TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                    TAF_SDC_RPT_CMD_CTZE))
            {
                stQryUnsolicitedRptCnf.u.ucCtzrRptFlg = MTA_TAF_CTZR_CTZE;
            }
            else
            {
                stQryUnsolicitedRptCnf.u.ucCtzrRptFlg = MTA_TAF_CTZR_OFF;
            }
            break;

        case AT_MTA_QRY_CSSN_RPT_TYPE:
            stQryUnsolicitedRptCnf.u.stCssnRptFlg.ucCssiRptFlg =
                    (VOS_UINT8)TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CSSI);

            stQryUnsolicitedRptCnf.u.stCssnRptFlg.ucCssuRptFlg =
                    (VOS_UINT8)TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CSSU);
            break;

        case AT_MTA_QRY_CUSD_RPT_TYPE:
            stQryUnsolicitedRptCnf.u.ucCusdRptFlg =
                    (VOS_UINT8)TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                            TAF_SDC_RPT_CMD_CUSD);
            break;

         default:
            break;
    }

    /* ��AT���Ͳ�ѯ�ظ� */
    TAF_MTA_SndAtMsg((AT_APPCTRL_STRU *)&(pstAtMtaMsg->stAppCtrl),
                     ID_MTA_AT_UNSOLICITED_RPT_QRY_CNF,
                     sizeof(stQryUnsolicitedRptCnf),
                     (VOS_UINT8*)&stQryUnsolicitedRptCnf);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_SysModeTransfer
 ��������  : ���뼼��ģʽת��
 �������  : TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
 �������  : ��
 �� �� ֵ  : TAF_SYS_MODE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��17��
    ��    ��   : zwx247453
    �޸�����   : ��������

*****************************************************************************/
TAF_SYS_MODE_ENUM_UINT8 TAF_MTA_SysModeTransfer(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSdcSysMode
)
{
    TAF_SYS_MODE_ENUM_UINT8             enSysMode;

    enSysMode = TAF_PH_INFO_NONE_RAT;

    switch (enSdcSysMode)
    {
        case TAF_SDC_SYS_MODE_GSM:
            enSysMode = TAF_PH_INFO_GSM_RAT;
            break;

        case TAF_SDC_SYS_MODE_WCDMA:
            if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
            {
                enSysMode = TAF_PH_INFO_WCDMA_RAT;
            }
            else
            {
                enSysMode = TAF_PH_INFO_TD_SCDMA_RAT;
            }
            break;

        case TAF_SDC_SYS_MODE_LTE:
            enSysMode = TAF_PH_INFO_LTE_RAT;
            break;

        case TAF_SDC_SYS_MODE_CDMA_1X:
            enSysMode = TAF_PH_INFO_CDMA_1X_RAT;
            break;

        case TAF_SDC_SYS_MODE_EVDO:
            enSysMode = TAF_PH_INFO_HRPD_RAT;
            break;

        case TAF_SDC_SYS_MODE_HYBRID:
            enSysMode = TAF_PH_INFO_HYBRID_RAT;
            break;

        case TAF_SDC_SYS_MODE_SVLTE:
            enSysMode = TAF_PH_INFO_SVLTE_SRLTE_RAT;
            break;

        default:
            break;
    }

    return enSysMode;
}

/*****************************************************************************
 �� �� ��  : TAF_MTA_RcvTafAgentGetSysModeReq
 ��������  : mta�յ�ID_TAFAGENT_MTA_GET_SYSMODE_REQ��Ϣ������
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��1��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C����������
  2.��    ��   : 2014��11��29��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseI��Ŀ�޸�
  3.��    ��   : 2015��11��17��
    ��    ��   : zwx247453
    �޸�����   : dallas gps�ο�ʱ���麸���

*****************************************************************************/
VOS_VOID TAF_MTA_RcvTafAgentGetSysModeReq(VOS_VOID *pMsg)
{
    TAFAGENT_MTA_GET_SYSMODE_CNF_STRU          *pstGetSysModeCnf    = VOS_NULL_PTR;

    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enSysSubMode;

    /* ��ȡϵͳģʽ */
    /* 1x CDMA�޷���״̬��ע��״̬��ʱ�ϱ�,ȡ��ǰ��ϵͳģʽ��ϵͳ��ģʽ��3GPPʱȡAppNetworkInfo�е�ϵͳģʽ��ϵͳ��ģʽ */
    if (TAF_SDC_SYS_MODE_CDMA_1X == TAF_SDC_GetSysMode())
    {
        enSysMode    = TAF_SDC_SYS_MODE_CDMA_1X;
        enSysSubMode = TAF_SDC_SYS_SUBMODE_CDMA_1X;
    }
    else
    {
        enSysMode    = TAF_SDC_GetAppSysMode();
        enSysSubMode = TAF_SDC_GetAppSysSubMode();
    }


    pstGetSysModeCnf = (TAFAGENT_MTA_GET_SYSMODE_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA,
                                                              sizeof(TAFAGENT_MTA_GET_SYSMODE_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstGetSysModeCnf)
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTafAgentGetSysModeReq:alloc msg failed.");
        return;
    }

    /* ��Ϣͷ */
    pstGetSysModeCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pstGetSysModeCnf->ulSenderPid                   = UEPS_PID_MTA;
    pstGetSysModeCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pstGetSysModeCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;

    /* ��Ϣ���� */
    pstGetSysModeCnf->enMsgId                 = ID_TAFAGENT_MTA_GET_SYSMODE_CNF;
    pstGetSysModeCnf->ulRet                   = VOS_OK;
    pstGetSysModeCnf->stSysMode.enSysSubMode  = enSysSubMode;

    pstGetSysModeCnf->stSysMode.enRatType = TAF_MTA_SysModeTransfer(enSysMode);

    /* ��TAFAGENT���Ͳ�ѯ�ظ� */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstGetSysModeCnf))
    {
        MTA_WARNING_LOG("TAF_MTA_RcvTafAgentGetSysModeReq:send msg failed.");

        return;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MTA_SndStkCurcRptCfgInfoInd
 ��������  : mta��STK����CURC������Ϣ����
 �������  : VOS_VOID *pMsg  --��Ϣ���ݽṹ�׵�ַ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��4��1��
    ��    ��   : s00217060
    �޸�����   : �����ϱ�AT�������������C����������

*****************************************************************************/
VOS_VOID TAF_MTA_SndStkCurcRptCfgInfoInd(AT_MTA_CURC_SET_NOTIFY_STRU *pMsg)
{
    TAF_STK_CURC_RPT_CFG_INFO_MSG_STRU          *pstStkCurcRptInfo  = VOS_NULL_PTR;

    /* �����ڴ� */
    pstStkCurcRptInfo = (TAF_STK_CURC_RPT_CFG_INFO_MSG_STRU *)PS_ALLOC_MSG(UEPS_PID_MTA,
                                                              sizeof(TAF_STK_CURC_RPT_CFG_INFO_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �ڴ�����쳣���� */
    if (VOS_NULL_PTR == pstStkCurcRptInfo)
    {
        MTA_WARNING_LOG("TAF_MTA_SndStkCurcRptCfgInfoInd:alloc msg failed.");
        return;
    }

    /* ��д����Ϣ���� */
    pstStkCurcRptInfo->ulSenderPid      = UEPS_PID_MTA;
    pstStkCurcRptInfo->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstStkCurcRptInfo->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstStkCurcRptInfo->ulReceiverPid    = MAPS_STK_PID;
    pstStkCurcRptInfo->ulMsgId          = TAF_STK_CURC_RPT_CFG_INFO_IND;
    PS_MEM_CPY(pstStkCurcRptInfo->aucCurcRptCfg,
               pMsg->aucRptCfg,
               sizeof(pstStkCurcRptInfo->aucCurcRptCfg));

    /* ������Ϣ�쳣���� */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_MTA, pstStkCurcRptInfo))
    {
        MTA_WARNING_LOG("TAF_MTA_SndStkCurcRptCfgInfoInd: PS_SEND_MSG ERROR");
        return;
    }

    return;
}

/* Added by s00217060 for �����ϱ�AT�������������C��, 2013-4-1, end */
#ifdef DMT
/*****************************************************************************
 �� �� ��  : DMT_GetSysMode
 ��������  : DMT׮����������A�˻�ȡ����ģʽ
 �������  : ��
 �������  : TAF_AGENT_SYS_MODE_STRU *pstSysMode -- ϵͳ��ǰ����ģʽ
 �� �� ֵ  : VOS_OK  ��ȡ�ɹ�
             VOS_ERR ��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��05��21��
    ��    ��   : l00198894
    �޸�����   : TAF&SM�ӿ��Ż���Ŀ��������

*****************************************************************************/
VOS_UINT32 DMT_GetSysMode(TAF_AGENT_SYS_MODE_STRU *pstSysMode)
{
    TAF_SDC_SYS_INFO_STRU                 *pst3gppSysInfo     = VOS_NULL_PTR;

    /* ��ȡϵͳģʽ */
    pst3gppSysInfo   = TAF_SDC_GetSysInfo();

    pstSysMode->enSysSubMode  = pst3gppSysInfo->enSysSubMode;
    pstSysMode->enRatType     = TAF_MTA_SysModeTransfer(pst3gppSysInfo->enSysMode);

    return VOS_OK;
}
#endif

/*lint +e958*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

