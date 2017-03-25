/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasRabmmMsgProc.c
  �� �� ��   : ����
  ��    ��   : anhuiqing / 00165503
  ��������   : 2011��03��30��
  ����޸�   :
  ��������   :
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2011��03��30��
    ��    ��   : anhuiqing / 00165503
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"

#include "PsCommonDef.h"
#include "rabminclude.h"
#include "NasRabmMain.h"
#include "NasRabmMsgProc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_RABM_MSG_PROC_C



/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* WCDMAϵͳģʽ�ĺ�������� */
NAS_RABM_PROC_FUNC_TBL_STRU             g_stNasRabmWProcFuncTbl;

/* GPRSϵͳģʽ�ĺ�������� */
NAS_RABM_PROC_FUNC_TBL_STRU             g_stNasRabmGProcFuncTbl;

#if (FEATURE_ON == FEATURE_LTE)
/* LTEϵͳģʽ�ĺ�������� */
NAS_RABM_PROC_FUNC_TBL_STRU             g_stNasRabmLProcFuncTbl;
#endif

/* ����ҵ������־ */
VOS_BOOL                                g_bNasRabmDataSuspendFlg;

/* ϵͳģʽ�ı䴦������ */
NAS_RABM_SYS_CHG_TBL_STRU               g_astRabmSysModeChgTbl[] =
{
    {NAS_MML_NET_RAT_TYPE_GSM   ,   NAS_MML_NET_RAT_TYPE_GSM    ,   VOS_NULL_PTR                        },
    {NAS_MML_NET_RAT_TYPE_GSM   ,   NAS_MML_NET_RAT_TYPE_WCDMA  ,   NAS_RABM_GProcSysModeChangeToWcdma  },
#if (FEATURE_ON == FEATURE_LTE)
    {NAS_MML_NET_RAT_TYPE_GSM   ,   NAS_MML_NET_RAT_TYPE_LTE    ,   NAS_RABM_GProcSysModeChangeToLte    },
#endif
    {NAS_MML_NET_RAT_TYPE_WCDMA ,   NAS_MML_NET_RAT_TYPE_GSM    ,   NAS_RABM_WProcSysModeChangeToGprs   },
    {NAS_MML_NET_RAT_TYPE_WCDMA ,   NAS_MML_NET_RAT_TYPE_WCDMA  ,   VOS_NULL_PTR                        },
#if (FEATURE_ON == FEATURE_LTE)
    {NAS_MML_NET_RAT_TYPE_WCDMA ,   NAS_MML_NET_RAT_TYPE_LTE    ,   NAS_RABM_WProcSysModeChangeToLte    },
    {NAS_MML_NET_RAT_TYPE_LTE   ,   NAS_MML_NET_RAT_TYPE_GSM    ,   NAS_RABM_LProcSysModeChangeToGprs   },
    {NAS_MML_NET_RAT_TYPE_LTE   ,   NAS_MML_NET_RAT_TYPE_WCDMA  ,   NAS_RABM_LProcSysModeChangeToWcdma  },
    {NAS_MML_NET_RAT_TYPE_LTE   ,   NAS_MML_NET_RAT_TYPE_LTE    ,   VOS_NULL_PTR                        }
#endif
};


/*****************************************************************************
  3 ��������������
*****************************************************************************/


/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : NAS_RABM_ProcSysModeChgInd
 ��������  : WCDMAϵͳģʽ����ϵͳģʽ�ı�ָʾ
 �������  : enOldSysMode   - RABM�ɵ�ϵͳģʽ
             enNewSysMode   - RABM�µ�ϵͳģʽ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��11��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_RABM_ProcSysModeChgInd(
    GMM_RABM_NET_RAT_ENUM_UINT32        enOldSysMode,
    GMM_RABM_NET_RAT_ENUM_UINT32        enNewSysMode
)
{
    NAS_RABM_SYS_MODE_CHG_PROC_FUNC     pSysModeChgProcFunc;
    VOS_UINT32                          ulIndex;

    NAS_NORMAL_LOG2(WUEPS_PID_RABM,
        "NAS_RABM_ProcSysModeChgInd: OldMode, NewMode:",
        enOldSysMode, enNewSysMode);

    /* ��ʼ��ϵͳģʽ������ָ�� */
    pSysModeChgProcFunc = VOS_NULL_PTR;

    /* ���ݾ�ϵͳģʽ����ϵͳģʽ���Ҵ����� */
    for (ulIndex = 0; ulIndex < NAS_RABM_GetSysModeChgTblSize(); ulIndex++)
    {
        if ( (enOldSysMode == NAS_RABM_GetSysModeChgTblOldMode(ulIndex))
          && (enNewSysMode == NAS_RABM_GetSysModeChgTblNewMode(ulIndex)) )
        {
            pSysModeChgProcFunc = NAS_RABM_GetSysModeChgTblProcFunc(ulIndex);
            break;
        }
    }

    if (VOS_NULL_PTR != pSysModeChgProcFunc)
    {
        pSysModeChgProcFunc();
    }
    else
    {
        NAS_NORMAL_LOG(WUEPS_PID_RABM,
            "NAS_RABM_ProcSysModeChgInd: pSysModeChgProcFunc is NULL.");
    }

}

/*****************************************************************************
 �� �� ��  : NAS_RABM_WProcSysModeChgToGprs
 ��������  : ����Wģ�л���Gģ��RABMʵ��״̬ת��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��24��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��6��01��
    ��    ��   : y00213812
    �޸�����   : ������ⵥDTS2012052903196�����Wʵ�����Ϣ

*****************************************************************************/
VOS_VOID NAS_RABM_WProcSysModeChangeToGprs(VOS_VOID)
{
    VOS_UINT8                           ucEntId;

    NAS_NORMAL_LOG(WUEPS_PID_RABM,
        "NAS_RABM_WProcSysModeChangeToGprs: Build GPRS state machine.");

    /* ���RAB�ؽ���־:��ֹͣRAB�ؽ���ʱ��, ���ʵ���RAB�ؽ���־ */
    NAS_RABM_ClearRabReestFlg();

    /* RABMʵ��״̬ת������ */
    for (ucEntId = 0; ucEntId < RABM_3G_PS_MAX_ENT_NUM; ucEntId++)
    {
        switch (NAS_RABM_GetWPsEntState(ucEntId))
        {
            case RABM_NULL:
                /* Gʵ��״̬��ΪRABM_2G_NULL */
                RABM_SetGState((RABM_NSAPI_ENUM)ucEntId, RABM_2G_NULL);

                /* ���Wʵ����Ϣ */
                NAS_RABM_ClearRabmWPsEnt(ucEntId);
                break;

            case RABM_NSAPI_ACTIVE_WITH_RAB:
            case RABM_NSAPI_ACTIVE_NO_RAB:
            case RABM_DATA_TRANSFER_STOP:
                NAS_NORMAL_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_WProcSysModeChangeToGprs: State change to RABM_DATA_TRANS_STOP. NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));

                /* Gʵ��״̬��ΪRABM_DATA_TRANS_STOP */
                RABM_SetGState((RABM_NSAPI_ENUM)ucEntId, RABM_DATA_TRANS_STOP);
                NAS_RABM_UpdateGPsEntFromWPsEnt(ucEntId);

                /* Wʵ��״̬��ΪRABM_NULL */
                RABM_SetWState(ucEntId, RABM_NULL);

                /* ���Wʵ����Ϣ */
                NAS_RABM_ClearRabmWPsEnt(ucEntId);
                break;

            default:
                NAS_ERROR_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_WProcSysModeChangeToGprs: This NSAPI's state is WRONG! NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));
                break;
        }
    }
}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_RABM_WProcSysModeChgToLte
 ��������  : ����Wģ�л���Lģ��RABMʵ��״̬ת��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��24��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��6��01��
    ��    ��   : y00213812
    �޸�����   : ������ⵥDTS2012052903196�����Wʵ���RAB��Ϣ

*****************************************************************************/
VOS_VOID NAS_RABM_WProcSysModeChangeToLte(VOS_VOID)
{
    VOS_UINT8                           ucEntId;

    NAS_NORMAL_LOG(WUEPS_PID_RABM,
        "NAS_RABM_WProcSysModeChangeToLte: Proc system mode change W->L.");

    /* ���RAB�ؽ���־: �ر�RAB�ؽ���ʱ��, ���ʵ���RAB�ؽ���־ */
    NAS_RABM_ClearRabReestFlg();

    /* RABMʵ��״̬ת������ */
    for (ucEntId = 0; ucEntId < RABM_3G_PS_MAX_ENT_NUM; ucEntId++)
    {
        switch (NAS_RABM_GetWPsEntState(ucEntId))
        {
            case RABM_NULL:
                break;

            case RABM_NSAPI_ACTIVE_PENDING:
                NAS_NORMAL_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_WProcSysModeChangeToGprs: State change to RABM_DATA_TRANS_STOP. NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));

                /* Wʵ��״̬��ΪRABM_NULL */
                RABM_SetWState(ucEntId, RABM_NULL);

                /* ���Wʵ��RAB��Ϣ */
                NAS_RABM_ClearRabmWPsEnt(ucEntId);
                break;

            case RABM_NSAPI_ACTIVE_WITH_RAB:
            case RABM_NSAPI_ACTIVE_NO_RAB:
            case RABM_DATA_TRANSFER_STOP:
                NAS_NORMAL_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_WProcSysModeChangeToGprs: State change to RABM_DATA_TRANS_STOP. NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));

                /* Wʵ��״̬��ΪRABM_DATA_TRANSFER_STOP */
                RABM_SetWState(ucEntId, RABM_DATA_TRANSFER_STOP);

                /* ���Wģ��RAB��Ϣ */
                NAS_RABM_ClearRabInfo(ucEntId);
                break;

            default:
                NAS_ERROR_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_WProcSysModeChangeToGprs: This NSAPI's state is WRONG! NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));
                break;
        }
    }
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_RABM_WProcDataSuspendInd
 ��������  : WCDMAϵͳģʽ�´������ָʾ
 �������  : bRatChangeFlg  - ��ϵͳ�л���־
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��11��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_RABM_WProcDataSuspendInd(
    VOS_BOOL                            bRatChangeFlg
)
{
    if (VOS_TRUE == bRatChangeFlg)
    {
        /* ��PDCP����RABM_PDCP_SAVE_DATA_IND_STRU��Ϣ */
        if (VOS_OK == NAS_RabmSndPdcpSaveDataInd())
        {
            /* ����NSAPI��RB�Ķ�Ӧ��ϵ */
            NAS_RabmSaveNsapiMapRbInfo();
        }
    }

    /* �������־�Ƿ�������ΪTRUE */
    if (VOS_TRUE == NAS_RABM_GetDataSuspendFlg())
    {
        NAS_NORMAL_LOG(WUEPS_PID_RABM,
            "NAS_RABM_WProcDataSuspendInd: DataSupendFlg is TRUE, do nothing.");
        return;
    }

    /* ���ù����־ΪTRUE */
    NAS_RABM_SetDataSuspendFlg();

    /* �̳�ԭ��W2G�������� */
    NAS_RabmDeal3GTo2GSuspendIndMsg();

}

/*****************************************************************************
 �� �� ��  : NAS_RABM_WProcDataResumeInd
 ��������  : WCDMAϵͳģʽ�´���ָ�ָʾ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��11��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��7��13��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII�׶ε�������RABMָʾRAB�Ƿ���Ҫ�ؽ�

  3.��    ��   : 2011��12��19��
    ��    ��   : o00132663
    �޸�����   : PS�ں���Ŀ������ָ���֪ͨCDS

  4.��    ��   : 2012��1��3��
    ��    ��   : A00165503
    �޸�����   : PS Projec: ɾ���ϱ�APSϵͳģʽ�л�ָʾ��Ϣ

  5.��    ��   : 2012��3��5��
    ��    ��   : A00165503
    �޸�����   : DTS2012022302899, ������ź�˥��ֱ������, PC�������������
                 ���, �����Ȼ���ָ�λ

  6.��    ��   : 2012��3��29��
    ��    ��   : f00179208
    �޸�����   : DTS2012032804992: G2W��ѡ�������Գ���1���ӲŻָ�PING��

  7.��    ��   : 2012��5��6��
    ��    ��   : A00165503
    �޸�����   : DTS2012050600216: �����ͷ�RRC���Ӻ�, �����޷��ָ�

  8.��    ��   : 2013��04��12��
    ��    ��   : l65478
    �޸�����   : DTS2013031901654:���Ų�������ʧ��
*****************************************************************************/
VOS_VOID NAS_RABM_WProcDataResumeInd(
    VOS_UINT8                           ucRebuildRabFlag
)
{
    RABM_ENTITY_PS_STRU                *pstWPsEnt;
    VOS_UINT8                           ucEntId;

    /* �������־�Ƿ�������ΪFALSE */
    if (VOS_FALSE == NAS_RABM_GetDataSuspendFlg())
    {
        NAS_NORMAL_LOG(WUEPS_PID_RABM,
            "NAS_RABM_WProcDataResumeInd: DataSupendFlg is FALSE, do nothing.");
        return;
    }

    /*-----------------------------------------------------
       �û�ָ��������^SYSCFG�����ϵͳģʽ�л�, ������
       ��������, �ָ����̴�����Ҫ�������־
    -----------------------------------------------------*/
    NAS_RABM_ClearDataSuspendFlg();

    /* �ͷ���3G��2G�л���ʼʱPDCP��������� */
    SN_RabmClear3G2Share();

    /* �����ڹ���״̬��ʵ�� */
    for (ucEntId = 0; ucEntId < RABM_3G_PS_MAX_ENT_NUM; ucEntId++)
    {
        pstWPsEnt = NAS_RABM_GetWPsEntAddr(ucEntId);

        switch (pstWPsEnt->ucState)
        {
            case RABM_NULL:
                /* �ж�SM��״̬�Ƿ���SM_PDP_ACTIVE_PENDING */
                if (VOS_OK == SM_IsActivePending(ucEntId + RABM_2G_NSAPI_OFFSET))
                {
                    if (VOS_OK == RABM_ResumeFirstActIndStatus(RABM_3G_ENUM, ucEntId))
                    {
                        NAS_NORMAL_LOG2(WUEPS_PID_RABM,
                            "NAS_RABM_WProcDataResumeInd: State RABM_2G_NULL change to RABM_NSAPI_ACTIVE_PENDING. NSAPI, STATE:",
                            ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));

                        /* ����3G�еĶ�ӦNSAPI��״̬�� */
                        if (0 != pstWPsEnt->RabInfo.ucRbNum)
                        {
                            RABM_SetWState(ucEntId, RABM_ACT_PENDING_WITH_RAB);
                        }
                        else
                        {
                            RABM_SetWState(ucEntId, RABM_NSAPI_ACTIVE_PENDING);
                        }
                    }
                }
                break;

            case RABM_DATA_TRANSFER_STOP:
                NAS_NORMAL_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_WProcDataResumeInd: State change to RABM_NSAPI_ACTIVE_NO_RAB. NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));

                /* ����3G�еĶ�ӦNSAPI��״̬�� */
                if (0 != pstWPsEnt->RabInfo.ucRbNum)
                {
                    RABM_SetWState(ucEntId, RABM_NSAPI_ACTIVE_WITH_RAB);

                    /* ֪ͨCDS���ͻ�������, ���CDS��ģʽ����NULL:
                       ��Ҫ�ȴ�MMC֪ͨCDSģʽ�л���GU���ٷ��ͻ���
                    */
                    NAS_RABM_SndCdsSendBuffDataInd(ucEntId + RABM_NSAPI_OFFSET,
                                                   CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_SERVICE_SUCC);
                }
                else
                {
                    RABM_SetWState(ucEntId, RABM_NSAPI_ACTIVE_NO_RAB);

                    /* �������Ҫ����RAB�ؽ�������RB����������ʱ��,
                       �ȴ�������ϱ�RB��Ϣ
                    */
                    if (VOS_FALSE == ucRebuildRabFlag)
                    {
                        NAS_RABM_SetWPsEntRabReestFlg(ucEntId);
                        NAS_RABM_StartReestRabPendingTmr(ucEntId + RABM_NSAPI_OFFSET);
                    }
                    else
                    {
                        NAS_RABM_SndCdsSendBuffDataInd(ucEntId + RABM_NSAPI_OFFSET,
                                                       CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_SERVICE_SUCC);
                    }
                }
                break;

            default:
                NAS_ERROR_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_WProcDataResumeInd: This NSAPI's state is WRONG! NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));
                break;
        }
    }


}


/*****************************************************************************
 �� �� ��  : NAS_RABM_GProcSysModeChgToWcdma
 ��������  : ����Gģ�л���Wģ��RABMʵ��״̬ת��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��24��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��3��26��
    ��    ��   : A00165503
    �޸�����   : DTS2012032604109: L->G(ȷ��ģʽ)��, �����޷��ָ�
*****************************************************************************/
VOS_VOID NAS_RABM_GProcSysModeChangeToWcdma(VOS_VOID)
{
    VOS_UINT8                           ucEntId;

    NAS_NORMAL_LOG(WUEPS_PID_RABM,
        "NAS_RABM_GProcSysModeChangeToWcdma: Build WCDMA state machine.");

    /* �ر�rout.area.update.T1��ʱ�� */
    NAS_RABM_StopGprsRaT1Timer();

    /* �ر�Rabm.sys.3To2.T3��ʱ�� */
    NAS_RABM_Stop3GTo2GT3Timer();

    /* ���WģCS��ʵ����Ϣ */
    NAS_RABM_ClearRabmCsEnt();

    for (ucEntId = 0; ucEntId < RABM_2G_MAX_ENT_NUM; ucEntId++)
    {
        switch (NAS_RABM_GetGPsEntState(ucEntId))
        {
            case RABM_2G_NULL:
                /* Wʵ��״̬��ΪRABM_NULL */
                RABM_SetWState(ucEntId, RABM_NULL);
                break;

            case RABM_NSAPI_OK_TRANSMODE_NO:
            case RABM_DATA_TRANS_READY:
            case RABM_ROUT_AREA_UPDATE:
            case RABM_DATA_TRANS_STOP:
                NAS_NORMAL_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_GProcSysModeChangeToWcdma: State RABM_DATA_TRANS_STOP change to RABM_NSAPI_ACTIVE_NO_RAB. NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));

                /* Wʵ��״̬��ΪRABM_DATA_TRANSFER_STOP */
                RABM_SetWState(ucEntId, RABM_DATA_TRANSFER_STOP);
                NAS_RABM_UpdateWPsEntFromGPsEnt(ucEntId);

                /* Gʵ��״̬��ΪRABM_2G_NULL */
                RABM_SetGState((RABM_NSAPI_ENUM)ucEntId, RABM_2G_NULL);

                /* ���Gʵ����Ϣ */
                NAS_RABM_ClearRabmGPsEnt(ucEntId);
                break;

            default:
                NAS_ERROR_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_GProcSysModeChangeToWcdma: ERROR:This NSAPI's state is WRONG!: NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));
                break;
        }
    }

#if (FEATURE_ON == FEATURE_LTE)
    /* ���L->G���̱�� */
    NAS_RABM_ClearL2GFlg();
#endif

}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_RABM_GProcSysModeChgToLte
 ��������  : ����Gģ�л���Lģ��RABMʵ��״̬ת��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��24��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��3��26��
    ��    ��   : A00165503
    �޸�����   : DTS2012032604109: L->G(ȷ��ģʽ)��, �����޷��ָ�
  3.��    ��   : 2012��6��01��
    ��    ��   : y00213812
    �޸�����   : ������ⵥDTS2012052903196��ΪWģ����ʵ����Ϣ

*****************************************************************************/
VOS_VOID NAS_RABM_GProcSysModeChangeToLte(VOS_VOID)
{
    VOS_UINT8                           ucEntId;

    NAS_NORMAL_LOG(WUEPS_PID_RABM,
        "NAS_RABM_GProcSysModeChangeToLte: Build WCDMA state machine.");

    /* �ر�rout.area.update.T1��ʱ�� */
    NAS_RABM_StopGprsRaT1Timer();

    /* �ر�Rabm.sys.3To2.T3��ʱ�� */
    NAS_RABM_Stop3GTo2GT3Timer();

    /* ���WģCS��ʵ����Ϣ */
    NAS_RABM_ClearRabmCsEnt();

    for (ucEntId = 0; ucEntId < RABM_2G_MAX_ENT_NUM; ucEntId++)
    {
        switch (NAS_RABM_GetGPsEntState(ucEntId))
        {
            case RABM_2G_NULL:
                /* Wʵ��״̬��ΪRABM_NULL */
                RABM_SetWState(ucEntId, RABM_NULL);
                break;

            case RABM_NSAPI_OK_TRANSMODE_NO:
            case RABM_DATA_TRANS_READY:
            case RABM_ROUT_AREA_UPDATE:
            case RABM_DATA_TRANS_STOP:
                NAS_NORMAL_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_GProcSysModeChangeToLte: State RABM_DATA_TRANS_STOP change to RABM_NSAPI_ACTIVE_NO_RAB. NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));

                /* Wʵ��״̬��ΪRABM_DATA_TRANSFER_STOP */
                RABM_SetWState(ucEntId, RABM_DATA_TRANSFER_STOP);
				/* ΪWģ����ʵ����Ϣ */
                NAS_RABM_UpdateWPsEntFromGPsEnt(ucEntId);

                /* Gʵ��״̬��ΪRABM_2G_NULL */
                RABM_SetGState((RABM_NSAPI_ENUM)ucEntId, RABM_2G_NULL);

                /* ���Gʵ����Ϣ */
                NAS_RABM_ClearRabmGPsEnt(ucEntId);
                break;

            default:
                NAS_ERROR_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_GProcSysModeChangeToLte: ERROR:This NSAPI's state is WRONG!: NSAPI, STATE:",
                    ucEntId + RABM_NSAPI_OFFSET, NAS_RABM_GetWPsEntState(ucEntId));
                break;
        }
    }

    /* ���L->G���̱�� */
    NAS_RABM_ClearL2GFlg();

}
#endif

/*****************************************************************************
 �� �� ��  : NAS_RABM_GProcDataSuspendInd
 ��������  : GPRSϵͳģʽ�´������ָʾ
 �������  : bRatChangeFlg  - ��ϵͳ�л���־
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��11��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_RABM_GProcDataSuspendInd(
    VOS_BOOL                            bRatChangeFlg
)
{
    if (VOS_TRUE == bRatChangeFlg)
    {
        /* ��SNDCP����RABM_SNDCP_SAVE_DATA_IND��Ϣ */
        NAS_RabmSndSnSaveDataInd();
    }

    /* �������־�Ƿ�������ΪTRUE */
    if (VOS_TRUE == NAS_RABM_GetDataSuspendFlg())
    {
        NAS_NORMAL_LOG(WUEPS_PID_RABM,
            "NAS_RABM_GProcDataSuspendInd: DataSupendFlg is TRUE, do nothing.");
        return;
    }

    /* ���ù����־ΪTRUE */
    NAS_RABM_SetDataSuspendFlg();

    /* �̳�ԭ��G2W�������� */
    NAS_RabmDeal2GTo3GSuspendIndMsg();

}

/*****************************************************************************
 �� �� ��  : NAS_RABM_GProcDataResumeInd
 ��������  : GPRSϵͳģʽ�´���ָ�ָʾ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��11��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��7��13��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII�׶ε�������RABMָʾRAB�Ƿ���Ҫ�ؽ�

  3.��    ��   : 2011��12��19��
    ��    ��   : o00132663
    �޸�����   : PS�ں���Ŀ������ָ���֪ͨCDS

  4.��    ��   : 2012��3��5��
    ��    ��   : A00165503
    �޸�����   : DTS2012022302899, ������ź�˥��ֱ������, PC�������������
                 ���, �����Ȼ���ָ�λ

  5.��    ��   : 2012��3��19��
    ��    ��   : A00165503
    �޸�����   : DTS2012031404116: Gģ����������LU, LU������1���������Żָ�

  6.��    ��   : 2013��04��12��
    ��    ��   : l65478
    �޸�����   : DTS2013031901654:���Ų�������ʧ��

  7.��    ��   : 2013��09��23��
    ��    ��   : z60575
    �޸�����   : DTS2013092205675, ��ȡģʽ

*****************************************************************************/
VOS_VOID NAS_RABM_GProcDataResumeInd(
    VOS_UINT8                           ucRebuildRabFlag
)
{
    VOS_UINT8                           ucEntId;
    RABM_TRANS_MODE_ENUM                enTransMode;

    enTransMode     = RABM_ADM_ENUM;

    /* ���ù����־ΪFALSE */
    NAS_RABM_ClearDataSuspendFlg();

    /* ��λG2Wʹ�õ������ָ���־ */
    NAS_RABM_ClearG2WDataResumeFlg();

    /* �ͷ���2G��3G�л���ʼʱSNDCP��������� */
    SN_RabmClear2G3Share();

    /* �����ڹ���״̬��ʵ�� */
    for (ucEntId = 0; ucEntId < RABM_2G_MAX_ENT_NUM; ucEntId++)
    {
        switch (NAS_RABM_GetGPsEntState(ucEntId))
        {
            case RABM_2G_NULL:
                break;

            case RABM_DATA_TRANS_STOP:
                NAS_NORMAL_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_GProcDataResumeInd: State change to RABM_NSAPI_OK_TRANSMODE_NO. NSAPI, STATE:",
                    ucEntId + RABM_2G_NSAPI_OFFSET, NAS_RABM_GetGPsEntState(ucEntId));

                if (VOS_TRUE == Taf_ApsIsSndcpActive(ucEntId + RABM_2G_NSAPI_OFFSET, &enTransMode))
                {
                    gastRabm2GEntity[ucEntId].TransMode = enTransMode;

                    /* Gģ��ѡ���˵ĳ�����, ״̬��ΪRABM_DATA_TRANS_READY */
                    RABM_SetGState((RABM_NSAPI_ENUM)ucEntId, RABM_DATA_TRANS_READY);

                    /* ֪ͨCDS���ͻ�������, ���CDS��ģʽ����NULL:
                       ��Ҫ�ȴ�MMC֪ͨCDSģʽ�л���GU���ٷ��ͻ���
                    */
                    NAS_RABM_SndCdsSendBuffDataInd(ucEntId + RABM_NSAPI_OFFSET,
                                                   CDS_RABM_SEND_BUFF_DATA_ALLOWED_TYPE_SERVICE_SUCC);
                }
                else
                {
                    /* ״̬��ΪRABM_NSAPI_OK_TRANSMODE_NO */
                    RABM_SetGState((RABM_NSAPI_ENUM)ucEntId, RABM_NSAPI_OK_TRANSMODE_NO);
                }
                break;

            default:
                NAS_ERROR_LOG2(WUEPS_PID_RABM,
                    "NAS_RABM_GProcDataResumeInd: This NSAPI's state is WRONG! NSAPI, STATE:",
                    ucEntId + RABM_2G_NSAPI_OFFSET, NAS_RABM_GetGPsEntState(ucEntId));
                break;
        }
    }

    /* ����ID_RABM_APS_SYS_CHG_TO_GPRS��Ϣ��APS, ����SNDCP */
    NAS_RABM_SendApsSysChgInd(ID_RABM_APS_SYS_CHG_TO_GPRS_IND);

}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_RABM_LProcSysModeChgToGprs
 ��������  : ����Wģ�л���Gģ��RABMʵ��״̬ת��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��24��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_RABM_LProcSysModeChangeToWcdma(VOS_VOID)
{
    /* ϵͳģʽ�л���Lģʱ, RABM�Ѿ����ڹ���״̬, ���л���Wģʱ, ���账�� */
    NAS_NORMAL_LOG(WUEPS_PID_RABM,
        "NAS_RABM_LProcSysModeChangeToWcdma: Build WCDMA state machine.");

}

/*****************************************************************************
 �� �� ��  : NAS_RABM_LProcSysModeChgToLte
 ��������  : ����Lģ�л���Gģ��RABMʵ��״̬ת��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��24��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��3��26��
    ��    ��   : A00165503
    �޸�����   : DTS2012032604109: L->G(ȷ��ģʽ)��, �����޷��ָ�
*****************************************************************************/
VOS_VOID NAS_RABM_LProcSysModeChangeToGprs(VOS_VOID)
{
    /* ϵͳģʽ��Lģ�л���Gģʱ, ����ͬWģ�л�֮Gģ */
    NAS_RABM_WProcSysModeChangeToGprs();

    /* ����L->G���̱�־ΪTRUE */
    NAS_RABM_SetL2GFlg();

}

/*****************************************************************************
 �� �� ��  : NAS_RABM_LProcDataSuspendInd
 ��������  : LTEϵͳģʽ�´������ָʾ
 �������  : bRatChangeFlg  - ��ϵͳ�л���־
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��11��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��5��17��
    ��    ��   : A00165503
    �޸�����   : DTS2012051707907: L�¿�����L2U�ض����, PING���޷��ָ�
*****************************************************************************/
VOS_VOID NAS_RABM_LProcDataSuspendInd(
    VOS_BOOL                            bRatChangeFlg
)
{
    /* ���ù����־ΪTRUE: Lģ����ʱ, GUģ��������ҵ���ڹ���״̬ */
    NAS_RABM_SetDataSuspendFlg();

    /* �ͷ���2G��3G�л���ʼʱSNDCP��������� */
    SN_RabmClear2G3Share();

    /* �ͷ���3G��2G�л���ʼʱPDCP��������� */
    SN_RabmClear3G2Share();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_RABM_LProcDataResumeInd
 ��������  : LTEϵͳģʽ�´���ָ�ָʾ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��11��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��7��13��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII�׶ε�������RABMָʾRAB�Ƿ���Ҫ�ؽ�

  3.��    ��   : 2012��1��3��
    ��    ��   : A00165503
    �޸�����   : PS Projec: ɾ���ϱ�APSϵͳģʽ�л�ָʾ��Ϣ

*****************************************************************************/
VOS_VOID NAS_RABM_LProcDataResumeInd(
    VOS_UINT8                           ucRebuildRabFlag
)
{
    /* ���ù����־ΪTRUE: Lģ����ʱ, GUģ��������ҵ���ڹ���״̬ */
    NAS_RABM_SetDataSuspendFlg();

    /* �ͷ���2G��3G�л���ʼʱSNDCP��������� */
    SN_RabmClear2G3Share();

    /* �ͷ���3G��2G�л���ʼʱPDCP��������� */
    SN_RabmClear3G2Share();

}

/*****************************************************************************
 �� �� ��  : NAS_RABM_LProcCommMsg
 ��������  : LTEģʽ�´���WRR����Ϣ
 �������  : struct MsgCB                       *pMsg
 �������  : VOS_VOID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��6��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_RABM_LProcCommMsg(
    struct MsgCB                       *pMsg
)
{
    MSG_HEADER_STRU                    *pstHeader;

    pstHeader = (MSG_HEADER_STRU*)pMsg;

    switch (pstHeader->ulSenderPid)
    {
        case  WUEPS_PID_WRR:
            if (RRRABM_HANDOVER_RAB_IND == pstHeader->ulMsgName)
            {
                NAS_RabmDealHandoverRabInd((RRRABM_HANDOVER_RAB_IND_STRU *)pMsg);
            }
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_RABM,
                "NAS_RABM_LProcCommMsg: Wrong message received in LTE mode.");
            break;
    }
}
#endif

/*****************************************************************************
 �� �� ��  : NAS_RABM_InitWProcFuncTbl
 ��������  : ��ʼ��WCDMA�������б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_RABM_InitWProcFuncTbl(VOS_VOID)
{
    NAS_RABM_PROC_FUNC_TBL_STRU        *pstWProcFuncTbl;

    pstWProcFuncTbl = NAS_RABM_GetWProFuncTblAddr();

    PS_MEM_SET(pstWProcFuncTbl, 0x00, sizeof(NAS_RABM_PROC_FUNC_TBL_STRU));

    pstWProcFuncTbl->pSmActivateIndProcFunc     = RABM_RcvSmActInd;
    pstWProcFuncTbl->pSmDeactivateIndProcFunc   = RABM_RcvSmDeactInd;
    pstWProcFuncTbl->pSmModifyIndProcFunc       = RABM_RcvSmModInd;

    pstWProcFuncTbl->pGmmReestablishCnfProcFunc = RABM_RcvGmmReestCnf;

    pstWProcFuncTbl->pDataSuspendIndProcFunc    = NAS_RABM_WProcDataSuspendInd;
    pstWProcFuncTbl->pDataResumeIndProcFunc     = NAS_RABM_WProcDataResumeInd;
    pstWProcFuncTbl->pSysModeChgIndProcFunc     = NAS_RABM_ProcSysModeChgInd;

    pstWProcFuncTbl->pTaskEntry                 = Rabm_3GTaskEntry;

}

/*****************************************************************************
 �� �� ��  : NAS_RABM_InitGProcFuncTbl
 ��������  : ��ʼ��GPRS�������б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_RABM_InitGProcFuncTbl(VOS_VOID)
{
    NAS_RABM_PROC_FUNC_TBL_STRU        *pstGProcFuncTbl;

    pstGProcFuncTbl = NAS_RABM_GetGProFuncTblAddr();

    PS_MEM_SET(pstGProcFuncTbl, 0x00, sizeof(NAS_RABM_PROC_FUNC_TBL_STRU));

    pstGProcFuncTbl->pSmActivateIndProcFunc     = NAS_RabmSmPdpActivateIndMsg;
    pstGProcFuncTbl->pSmDeactivateIndProcFunc   = NAS_RabmSmPdpDeactivateIndMsg;
    pstGProcFuncTbl->pSmModifyIndProcFunc       = NAS_RabmSmPdpModifyIndMsg;

    pstGProcFuncTbl->pGmmReestablishCnfProcFunc = VOS_NULL_PTR;

    pstGProcFuncTbl->pDataSuspendIndProcFunc    = NAS_RABM_GProcDataSuspendInd;
    pstGProcFuncTbl->pDataResumeIndProcFunc     = NAS_RABM_GProcDataResumeInd;
    pstGProcFuncTbl->pSysModeChgIndProcFunc     = NAS_RABM_ProcSysModeChgInd;

    pstGProcFuncTbl->pTaskEntry                 = NAS_Rabm2GMsgDispatch;

}

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : NAS_RABM_InitLProcFuncTbl
 ��������  : ��ʼ��LTE�������б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��1��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_RABM_InitLProcFuncTbl(VOS_VOID)
{
    NAS_RABM_PROC_FUNC_TBL_STRU        *pstLProcFuncTbl;

    pstLProcFuncTbl = NAS_RABM_GetLProFuncTblAddr();

    PS_MEM_SET(pstLProcFuncTbl, 0x00, sizeof(NAS_RABM_PROC_FUNC_TBL_STRU));

    pstLProcFuncTbl->pSmActivateIndProcFunc     = VOS_NULL_PTR;
    pstLProcFuncTbl->pSmDeactivateIndProcFunc   = VOS_NULL_PTR;
    pstLProcFuncTbl->pSmModifyIndProcFunc       = VOS_NULL_PTR;

    pstLProcFuncTbl->pGmmReestablishCnfProcFunc = VOS_NULL_PTR;

    pstLProcFuncTbl->pDataSuspendIndProcFunc    = NAS_RABM_LProcDataSuspendInd;
    pstLProcFuncTbl->pDataResumeIndProcFunc     = NAS_RABM_LProcDataResumeInd;
    pstLProcFuncTbl->pSysModeChgIndProcFunc     = NAS_RABM_ProcSysModeChgInd;

    pstLProcFuncTbl->pTaskEntry                 = NAS_RABM_LProcCommMsg;

}
#endif

/*****************************************************************************
 �� �� ��  : NAS_RABM_InitProcFuncTbl
 ��������  : ��ʼ����ע�����ϵͳģʽ�Ĵ�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��27��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_RABM_InitProcFuncTbl(VOS_VOID)
{
    /* ��ʼ����ע��WCDMAϵͳģʽ�������� */
    NAS_RABM_InitWProcFuncTbl();
    NAS_RABM_RegProcFuncTbl(NAS_MML_NET_RAT_TYPE_WCDMA,
                            NAS_RABM_GetWProFuncTblAddr());

    /* ��ʼ����ע��GPRSϵͳģʽ�������� */
    NAS_RABM_InitGProcFuncTbl();
    NAS_RABM_RegProcFuncTbl(NAS_MML_NET_RAT_TYPE_GSM,
                            NAS_RABM_GetGProFuncTblAddr());

#if (FEATURE_ON == FEATURE_LTE)
    /* ��ʼ����ע��LTEϵͳģʽ�������� */
    NAS_RABM_InitLProcFuncTbl();
    NAS_RABM_RegProcFuncTbl(NAS_MML_NET_RAT_TYPE_LTE,
                            NAS_RABM_GetLProFuncTblAddr());
#endif

}

/*****************************************************************************
 �� �� ��  : NAS_RABM_ClearRabInfo
 ��������  : ���ָ��ʵ��ID��WģRAB��Ϣ
 �������  : ucEntId    - ʵ��ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��31��
    ��    ��   : y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_RABM_ClearRabInfo(
    VOS_UINT8                           ucEntId
)
{
    RABM_ENTITY_PS_STRU                *pstWPsEnt;

    pstWPsEnt = NAS_RABM_GetWPsEntAddr(ucEntId);

    /* ��ʼ��RAB, PDP����, �Լ�QOS */
    pstWPsEnt->RabInfo.ucRbNum  = 0;
}

/*****************************************************************************
 �� �� ��  : NAS_RABM_ClearRabmWPsEnt
 ��������  : ���ָ��ʵ��ID��WģPS��ʵ����Ϣ
 �������  : VOS_UINT8                           ucEntId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��27��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��6��01��
    ��    ��   : y00213812
    �޸�����   : ������ⵥDTS2012052903196�����Wģʵ����Ϣʱ�ͷ�Qos������ڴ�

  3.��    ��   : 2012��8��22��
    ��    ��   : A00165503
    �޸�����   : RABM�����QOS�ɶ�̬�ڴ��Ϊ��̬����
*****************************************************************************/
VOS_VOID NAS_RABM_ClearRabmWPsEnt(
    VOS_UINT8                           ucEntId
)
{
    RABM_ENTITY_PS_STRU                *pstWPsEnt;

    pstWPsEnt = NAS_RABM_GetWPsEntAddr(ucEntId);

    /* ��ʼ��RAB, PPP��ʶ, �Լ�QOS��Ϣ */
    pstWPsEnt->RabInfo.ucRbNum = 0;
    pstWPsEnt->ucPppFlg        = RABM_SM_IP_PROT;
    pstWPsEnt->QoS.ulQosLength = 0;
    PS_MEM_SET(pstWPsEnt->QoS.aucQosValue, 0x00, sizeof(pstWPsEnt->QoS.aucQosValue));

    /* �ͷŻ�������������� */
    RABM_RelSaveData(&pstWPsEnt->DlDataSave, RABM_DOWNLINK);
    RABM_RelSaveData(&pstWPsEnt->UlDataSave, RABM_UPLINK);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_RABM_ClearRabmGPsEnt
 ��������  : ���ָ��ʵ��ID��GģPS��ʵ����Ϣ
 �������  : VOS_UINT8                           ucEntId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��27��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��6��01��
    ��    ��   : y00213812
    �޸�����   : ������ⵥDTS2012052903196�����Gģʵ����Ϣʱ�ͷ�Qos������ڴ�

  3.��    ��   : 2012��8��22��
    ��    ��   : A00165503
    �޸�����   : RABM�����QOS�ɶ�̬�ڴ��Ϊ��̬����
*****************************************************************************/
VOS_VOID NAS_RABM_ClearRabmGPsEnt(
    VOS_UINT8                           ucEntId
)
{
    RABM_2G_ENTITY_ST                  *pstGPsEnt;

    pstGPsEnt = NAS_RABM_GetGPsEntAddr(ucEntId);

    /* ��ʼ��STATE, NSAPI, ����ģʽ, �Լ�QOS����Ϣ */
    pstGPsEnt->ucNsapi           = ucEntId + RABM_2G_NSAPI_OFFSET;
    pstGPsEnt->TransMode         = RABM_ADM_ENUM;
    pstGPsEnt->RAUpdateCause     = RABM_RA_UPDATE_CAUSE_BUTT;
    pstGPsEnt->stQos.ulQosLength = 0;
    PS_MEM_SET(pstGPsEnt->stQos.aucQosValue, 0x00, sizeof(pstGPsEnt->stQos.aucQosValue));

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_RABM_ClearRabmCsEnt
 ��������  : ���CS�����ʵ����Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��27��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_RABM_ClearRabmCsEnt(VOS_VOID)
{
    RABM_ENTITY_CS_STRU                *pstCsEnt;
    VOS_UINT8                           ucEntId;

    /* ���SI��RABMʵ���ӳ���ϵ */
    NAS_RABM_ClearSiMapEnt();

    /* ���CS��ʵ����Ϣ */
    for (ucEntId = 0; ucEntId < RABM_CS_MAX_ENT_NUM; ucEntId++)
    {
        pstCsEnt = NAS_RABM_GetCsEntAddr(ucEntId);

        pstCsEnt->ucState           = RABM_NULL;
        pstCsEnt->RabInfo.ucRbNum   = 0;
        pstCsEnt->RabInfo.ucRabId   = NAS_RABM_INVALID_RAB_ID;
    }
}

/*****************************************************************************
 �� �� ��  : NAS_RABM_ClearRabReestFlg
 ��������  : ֹͣRAB�ؽ���ʱ��, ���RAB�ؽ���־
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��27��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��6��13��
    ��    ��   : A00165503
    �޸�����   : DTS2012061302495: �޸ĵ��ú������
  3.��    ��   : 2013��04��12��
    ��    ��   : l65478
    �޸�����   : DTS2013031901654:���Ų�������ʧ��
*****************************************************************************/
VOS_VOID NAS_RABM_ClearRabReestFlg(VOS_VOID)
{
    VOS_UINT8                           ucEntId;

    /* ֹͣRAB�ؽ���ʱ�� */
    if (VOS_TRUE == NAS_RABM_GetRabRsestTimerFlg())
    {
        RABM_TimerStop(0);
        NAS_RabmStopTimer(RABM_TIMER_NAME_COMMON, RABM_TIMER_RESEND_EST_REQ);
        NAS_RABM_ClearRabRsestTimerFlg();
    }

    /* ���RABMʵ���RAB�ؽ���־ */
    for (ucEntId = 0; ucEntId < RABM_3G_PS_MAX_ENT_NUM; ucEntId++)
    {
        NAS_RABM_StopReestRabPendingTmr(ucEntId + RABM_NSAPI_OFFSET);
        NAS_RABM_ClearWPsEntRabReestFlg(ucEntId);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_RABM_StopGprsRaT1Timer
 ��������  : ֹͣrout.area.update.T1��ʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��27��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_RABM_StopGprsRaT1Timer(VOS_VOID)
{
    if (RABM_ROUTING_AREA_UPDATE_T1_ON == NAS_RABM_GetRauT1Flg())
    {
        /* ֹͣrout.area.update.T1��ʱ�� */
        NAS_RabmStopTimer(RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_ROUT_AREA_UPDATE_T1);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_RABM_Stop3GTo2GT3Timer
 ��������  : ֹͣRabm.sys.3To2.T3��ʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��27��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_RABM_Stop3GTo2GT3Timer(VOS_VOID)
{
    if (RABM_3G_TO_2G_T3_ON == NAS_RABM_GetW2GT3Flg())
    {
        /* ֹͣRabm.sys.3To2.T3��ʱ�� */
        NAS_RabmStopTimer( RABM_TIMER_NAME_COMMON, RABM_TIMER_PARA_3_TO_2_T3);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_RABM_UpdateWPsEntFromGPsEnt
 ��������  : PS��ʵ����Ϣת��, G->W
 �������  : VOS_UINT8                           ucEntId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��27��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��6��01��
    ��    ��   : y00213812
    �޸�����   : ������ⵥDTS2012052903196������Wģʵ����Ϣʱ��ΪQos�����ڴ棬������Gģ����

  3.��    ��   : 2012��8��22��
    ��    ��   : A00165503
    �޸�����   : RABM�����QOS�ɶ�̬�ڴ��Ϊ��̬����
*****************************************************************************/
VOS_VOID NAS_RABM_UpdateWPsEntFromGPsEnt(
    VOS_UINT8                           ucEntId
)
{
    RABM_ENTITY_PS_STRU                *pstWPsEnt;
    RABM_2G_ENTITY_ST                  *pstGPsEnt;

    pstWPsEnt = NAS_RABM_GetWPsEntAddr(ucEntId);
    pstGPsEnt = NAS_RABM_GetGPsEntAddr(ucEntId);

    pstWPsEnt->ucPppFlg              = pstGPsEnt->ucPppFlg;
    pstWPsEnt->ucReEstFlg            = VOS_FALSE;
    pstWPsEnt->RabInfo.ucRbNum       = 0;

    pstWPsEnt->QoS.ulQosLength       = pstGPsEnt->stQos.ulQosLength;

    PS_MEM_CPY(pstWPsEnt->QoS.aucQosValue,
               pstGPsEnt->stQos.aucQosValue,
               NAS_RABM_MAX_QOS_LEN);

    pstWPsEnt->ucStpFlg              = VOS_TRUE;
    pstWPsEnt->DlDataSave.ucNum      = 0;
    pstWPsEnt->DlDataSave.Data.pData = VOS_NULL_PTR;
    pstWPsEnt->DlDataSave.Data.pNxt  = VOS_NULL_PTR;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_RABM_UpdateGPsEntFromWPsEnt
 ��������  : PS��ʵ����Ϣת��, W->G
 �������  : VOS_UINT8                           ucEntId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��27��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��6��01��
    ��    ��   : y00213812
    �޸�����   : ������ⵥDTS2012052903196������Gģʵ����Ϣʱ��ΪQos�����ڴ棬������Gģ����

  3.��    ��   : 2012��8��22��
    ��    ��   : A00165503
    �޸�����   : RABM�����QOS�ɶ�̬�ڴ��Ϊ��̬����
*****************************************************************************/
VOS_VOID NAS_RABM_UpdateGPsEntFromWPsEnt(
    VOS_UINT8                           ucEntId
)
{
    RABM_ENTITY_PS_STRU                *pstWPsEnt;
    RABM_2G_ENTITY_ST                  *pstGPsEnt;

    pstWPsEnt = NAS_RABM_GetWPsEntAddr(ucEntId);
    pstGPsEnt = NAS_RABM_GetGPsEntAddr(ucEntId);

    pstGPsEnt->ucNsapi             = ucEntId + RABM_2G_NSAPI_OFFSET;
    pstGPsEnt->TransMode           = RABM_ADM_ENUM;

    pstGPsEnt->stQos.ulQosLength   = pstWPsEnt->QoS.ulQosLength;

    PS_MEM_CPY(pstGPsEnt->stQos.aucQosValue,
               pstWPsEnt->QoS.aucQosValue,
               NAS_RABM_MAX_QOS_LEN);

    pstGPsEnt->RAUpdateCause       = RABM_RA_UPDATE_CAUSE_BUTT;
    pstGPsEnt->ucPppFlg            = pstWPsEnt->ucPppFlg;

    return;
}

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


