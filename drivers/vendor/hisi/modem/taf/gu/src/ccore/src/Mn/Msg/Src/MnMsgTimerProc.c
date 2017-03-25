/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnMsgTimerProc.c
  �� �� ��   : ����
  ��    ��   : �ܾ� 40661
  ��������   : 2008��2��21��
  ����޸�   :
  ��������   : ʵ��MSGģ����յ�Timer���͹�����Ϣ�ĺ����ӿ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��2��21��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ļ�
  2.��    ��   : 2008��8��14��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : ���ⵥ�� AT2D03741,��̹淶���⣺   1��ö�����Ͷ���   2��ȫ�ֱ������ⲿ����   3���ļ�������ע�����⣻   ��ӡ��Ϣ������   1�����ӵ��Դ�ӡ����
  3.��    ��   : 2008��8��29��
    ��    ��   : fuyingjun
    �޸�����   : ���ⵥ��:AT2D05344, ����Ϣģ���ʼ�����̽��������SDT�����뵥�巴���������ӺͶϿ�����,Э��ջ���ظ��ϱ���ʼ������¼�;
  4.��    ��   : 2009��3��3��
    ��    ��   : z40661
    �޸�����   : ���ⵥ�ţ�AT2D07942��AT2D09557��, �������ĺ����ϱ�ʱ��ϳ�
  5.��    ��   : 2009��3��3��
    ��    ��   : z40661
    �޸�����   : ���ⵥ�ţ�AT2D08974, ���Ŵ�ӡ�������
  6.��    ��   : 2009��3��23��
    ��    ��   : f62575
    �޸�����   : AT2D08752, W���뷽ʽ�£��źŽ���ʱ�������Ͷ������Ż�����Գ��ַ��Ͳ���ʧ�ܣ�
  7.��    ��   : 2009��4��1��
    ��    ��   : �ܾ� 40661
    �޸�����   : ���ⵥ��:AT2D09786, ��AT+CMGD=,4ɾ������ʱ����ʱ�䲻��Ӧ�������Զ����ű���ⲻ������
  8.��    ��   : 2009��7��18��
    ��    ��   : z40661
    �޸�����   : �ն˿������������
  9.��    ��   : 2009��8��21��
    ��    ��   : f62575
    �޸�����   : ���ⵥ��:AT2D13974, ʵ�������绷���·�����ΪPS Only�����·�����ʧ��

 10.��    ��   : 2010��5��7��
    ��    ��   : zhoujun /z40661
    �޸�����   : AT2D19153���ط�ʱ�䲻��ʱ��δ��ֹͣ��ʱ��
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "MnMsgInclude.h"
#include  "TafSdcCtx.h"

#include "MnMsgSendSpm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_MNMSG_TIMERPROC_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

/*****************************************************************************
  2 ���Ͷ���
*****************************************************************************/
typedef struct
{
    HTIMER                              hTimer;
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId;
}MN_MSG_TIMER_HANDLE_STRU;

/* ��ʱ�����������Ͷ��� */
typedef VOS_VOID (* MN_MSG_TIMEOUT_PROC_FUNC)(VOS_UINT32 ulParam);

/* ��ʱ����Ϣ�ṹ */
typedef struct
{
    VOS_UINT32                          ulTimeout;
    MN_MSG_TIMEOUT_PROC_FUNC            pfnTimeoutProc;
} MN_MSG_TIMER_INFO_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    VOS_UINT32                          ulTimeLen;
}MN_MSG_TIMER_OPERATION_STRU;

LOCAL MN_CLIENT_ID_T                    g_clientId;
LOCAL MN_OPERATION_ID_T                 g_opId;
LOCAL VOS_UINT32                        g_ulLeftReportNum;
LOCAL MN_MSG_LIST_PARM_STRU             g_stList;

/*****************************************************************************
  3 ��������
*****************************************************************************/
LOCAL VOS_VOID  MSG_GetEfCnfTimeout(
    VOS_UINT32                          ulParam
);

LOCAL VOS_VOID  MSG_LinkCtrlTimeout(
    VOS_UINT32                          ulParam
);

LOCAL VOS_VOID MSG_WaitUsimTimeout(
    VOS_UINT32                          ulParam
);

LOCAL VOS_VOID MSG_WaitRetryPeriodTimeout(
    VOS_UINT32                          ulParam
);

LOCAL VOS_VOID MSG_WaitRetryIntervalTimeout(
    VOS_UINT32                          ulParam
);


LOCAL VOS_VOID MSG_WaitFdnCheckTimeout(
    VOS_UINT32                          ulParam
);


LOCAL VOS_VOID  MSG_WaitSmsMoControlCheckTimeout(
    VOS_UINT32                          ulParam
);

/*****************************************************************************
  4 ��������
*****************************************************************************/
/* ���п��õĶ�ʱ����Դ */
MN_MSG_TIMER_HANDLE_STRU                f_astMsgTimerHandle[MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG];

/*��ʱ����Ϣ���ñ��м�¼��ÿ�ֶ�ʱ���ĳ�ʱʱ��ͳ�ʱ������ */
MN_MSG_TIMER_INFO_STRU                  f_astMsgTimerInfoTbl[MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG] = {
    {60000, MSG_GetEfCnfTimeout},
    {3500, MSG_LinkCtrlTimeout},
    {10000,MSG_WaitUsimTimeout},
    {30000,MSG_WaitRetryPeriodTimeout},
    {5000,MSG_WaitRetryIntervalTimeout},
    {5000, MSG_WaitFdnCheckTimeout},
    {5000, MSG_WaitSmsMoControlCheckTimeout},
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    {60000,  TAF_CBA_RcvTiWaitGetCbEfRspTimerExpired},
#if (FEATURE_ON == FEATURE_ETWS)
    {600000, TAF_CBA_RcvTiEtwsTempEnableCbsTimerExpired}                        /* �յ���֪ͨʱ��ʱʹ��CBS�Ķ�ʱ�� */
#endif
#endif
};

/*lint -save -e958 */

/*****************************************************************************
  5 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : MN_MSG_PrintTimerInfo
 ��������  : ��ʱ�����ݵĴ�ӡ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��7��14��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_MSG_PrintTimerInfo(VOS_VOID)
{
    VOS_UINT32                          ulLoop;

    for (ulLoop = 0; ulLoop < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); ulLoop++)
    {
        MN_INFO_LOG1("MN_MSG_PrintTimerInfo:Timer No           ", (VOS_INT32)ulLoop);
        MN_INFO_LOG1("MN_MSG_PrintTimerInfo:Timer handle id    ", (VOS_INT32)f_astMsgTimerHandle[ulLoop].enTimerId);
        MN_INFO_LOG1("MN_MSG_PrintTimerInfo:Timer handle hTimer", (VOS_INT32)f_astMsgTimerHandle[ulLoop].hTimer);
        MN_INFO_LOG1("MN_MSG_PrintTimerInfo:Timer Table Length ", (VOS_INT32)f_astMsgTimerInfoTbl[ulLoop].ulTimeout);
        MN_INFO_LOG1("MN_MSG_PrintTimerInfo:Timer Table handle ", (VOS_INT32)f_astMsgTimerInfoTbl[ulLoop].pfnTimeoutProc);
    }
}

/*****************************************************************************
 �� �� ��  : MSG_GetEfSmsTimerout
 ��������  : �ȴ�EFSMS�ļ�ʱ,��ʱ����ʱ�������ǰ�����ļ�δ�ܶ�ȡ,�������ȡ��һ
             ��EFSMS�ļ�,����,���������ļ���USIM�еĴ��������USIM���������ļ���
             ��ȡ,���������ļ�����,���ϱ���ʼ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��21��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ɺ���
 2.��    ��   : 2013��8��3��
   ��    ��   : z60575
   �޸�����   : TQE�޸�

*****************************************************************************/
VOS_VOID MSG_GetEfSmsTimerout(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    MN_MSG_USIM_EFUST_INFO_STRU         stUstInfo;
    VOS_UINT8                           ucCurrRec;
    VOS_UINT32                          ulFileId[2];

    if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
    {
        ulFileId[0]    = USIMM_USIM_EFSMS_ID;
        ulFileId[1]    = USIMM_USIM_EFSMSR_ID;
    }
    else
    {
        ulFileId[0]    = USIMM_TELE_EFSMS_ID;
        ulFileId[1]    = USIMM_TELE_EFSMSR_ID;
    }

    PS_MEM_SET(&stUstInfo, 0, sizeof(stUstInfo));

    /*��ȡ��һ����¼*/
    ucCurrRec = MN_MSG_GetSmCurrRecFromUsim();
    if (ucCurrRec < MN_MSG_GetSmCapacity(MN_MSG_MEM_STORE_SIM))
    {
        /*lint -e961*/
        MN_MSG_SetSmCurrRecFromUsim(++ucCurrRec);
        /*lint +e961*/
        ulRet = MN_MSG_SndUsimGetFileReq((VOS_UINT16)ulFileId[0], ucCurrRec);
        if (USIMM_API_SUCCESS == ulRet)
        {
            return;
        }
    }
    else
    {
        MN_MSG_SetSmCurrRecFromUsim(0);
    }

    MN_MSG_ReadUstInfo(&stUstInfo);
    if (VOS_TRUE == stUstInfo.bEfSmsrFlag)
    {
        ulRet =  MN_MSG_SndUsimGetFileReq((VOS_UINT16)ulFileId[1], 0);;
        if (USIMM_API_SUCCESS == ulRet)
        {
            return;
        }
    }

    /*���ļ���Ҫ��ȡ,��Ϊ�ϵ����*/
    MN_MSG_UpdateUsimStateInfo(MN_MSG_USIM_POWER_ON);

    /*��Ӧ���ϱ���ʼ�����*/
    MN_MSG_SmInitFinish(MN_CLIENT_ALL);
}

/*****************************************************************************
 �� �� ��  : MSG_LinkCtrlTimeout
 ��������  : �յ������м���·���ƶ�ʱ����ʱָʾSMS�ͷ���·
 �������  : ��
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_VOID MSG_LinkCtrlTimeout(
    VOS_UINT32                          ulParam
)
{
    MN_MSG_LINK_CTRL_U8                 enLinkCtrl;
    MN_MSG_MO_STATE_ENUM_U8             enMoState;

    enMoState = MN_MSG_GetMoState();
    enLinkCtrl = MN_MSG_GetLinkCtrlParam();
    if ((MN_MSG_LINK_CTRL_ONEOFF_ENABLE == enLinkCtrl)
     && (MN_MSG_MO_STATE_WAIT_REPORT_IND != enMoState))
    {
        (VOS_VOID)MN_MSG_UpdateLinkCtrlParam(MN_MSG_LINK_CTRL_DISABLE);
    }

    MN_MSG_SendSmsCpAckReq();
    return;
}

/*****************************************************************************
 �� �� ��  : MSG_WaitUsimTimeout
 ��������  : �ȴ�USIM����һЩ�ڵ��,������USIM���ͽڵ���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��10��15��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2013��8��3��
    ��    ��   : z60575
    �޸�����   : TQE�޸�
*****************************************************************************/
LOCAL VOS_VOID MSG_WaitUsimTimeout(
    VOS_UINT32                          ulParam
)
{
    VOS_UINT32                          ulRealRec;
    VOS_BOOL                            bNeedSendUsim[255];
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           aucSmContent[MN_MSG_EFSMS_LEN];
    VOS_UINT32                          ulTotalNum = 0;
    VOS_BOOL                            bNeedStartTimer = VOS_FALSE;
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;

    enSimType = TAF_SDC_GetSimType();

    PS_MEM_SET(bNeedSendUsim, 0, sizeof(bNeedSendUsim));

    MN_MSG_GetNeedSendUsim(&ulRealRec, bNeedSendUsim);
    for (i = 0; i < ulRealRec; i++)
    {
        if (VOS_TRUE == bNeedSendUsim[i])
        {
            PS_MEM_SET(aucSmContent,(VOS_CHAR)0xFF,MN_MSG_EFSMS_LEN);
            ulRet = MN_MSG_ReadSmsInfo(MN_MSG_MEM_STORE_SIM,i,aucSmContent);
            if (MN_ERR_NO_ERROR != ulRet)
            {
                MN_MSG_UpdateNeedSendUsim(i,VOS_FALSE);
                continue;
            }
            if (EF_SMS_STATUS_MT_READ != (aucSmContent[0] & 0x03))
            {
                MN_MSG_UpdateNeedSendUsim(i,VOS_FALSE);
                continue;
            }
            aucSmContent[0] = EF_SMS_STATUS_MT_READ;

            if (TAF_SDC_SIM_TYPE_SIM == enSimType)
            {
                ulRet = MN_MSG_SndUsimSetFileReq(USIMM_TELE_EFSMS_ID, aucSmContent, MN_MSG_EFSMS_LEN, (VOS_UINT8)(i + 1));
            }
            else if (TAF_SDC_SIM_TYPE_USIM == enSimType)
            {
                ulRet = MN_MSG_SndUsimSetFileReq(USIMM_USIM_EFSMS_ID, aucSmContent, MN_MSG_EFSMS_LEN, (VOS_UINT8)(i + 1));
            }
            else
            {
                ulRet = USIMM_API_FAILED;
            }

            if (USIMM_API_SUCCESS != ulRet)
            {
                MN_WARN_LOG("MSG_WaitUsimTimeout:Add Usim Node Failed");
                bNeedStartTimer = VOS_TRUE;
                break;
            }
            ulTotalNum++;
            MN_MSG_UpdateNeedSendUsim(i,VOS_FALSE);
        }
        if (ulTotalNum >=  MN_MSG_MAX_CHG_SM_STATE_NUM)
        {
            break;
        }
    }

    if ( (i + 1) < ulRealRec)
    {
        bNeedStartTimer = VOS_TRUE;
    }

    if (VOS_TRUE == bNeedStartTimer)
    {
        MN_MSG_StartTimer(MN_MSG_TID_WAIT_USIM,0);
    }
}

/*****************************************************************************
 �� �� ��  : MSG_GetEfCnfTimeout()
 ��������  : ��ʼ��ʱ��ȡUSIM�е�EFSMSS,EFSMSP,EFSMS,EFSMSR�ļ�ʱ,��ʱ����ʱ��Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2007��2��04��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_VOID  MSG_GetEfCnfTimeout(
    VOS_UINT32                          ulParam
)
{
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;

    MN_MSG_GetUsimPowerState(&enPowerState);
    switch (enPowerState)
    {
        case MN_MSG_USIM_POWER_WAIT_EFSMSS:
            MN_NORM_LOG("MSG_GetEfCnfTimeout:WAIT EFSMSS");
            /*��ȡEFSMSP�ļ�������*/
            if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
            {
                MN_MSG_GetUsimParmReq(USIMM_USIM_EFSMSP_ID);
            }
            else
            {
                MN_MSG_GetUsimParmReq(USIMM_TELE_EFSMSP_ID);
            }
            break;
        case MN_MSG_USIM_POWER_WAIT_EFSMSP:
            /* �ϱ�EFSMSP�ļ���ȡ��� */
            MN_MSG_SmspInitFinish(MN_CLIENT_ALL);
            MN_NORM_LOG("MSG_GetEfCnfTimeout:WAIT EFSMSP");
            /*��ȡEFSMS�ļ�������*/
            if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
            {
                MN_MSG_GetUsimParmReq(USIMM_USIM_EFSMS_ID);
            }
            else
            {
                MN_MSG_GetUsimParmReq(USIMM_TELE_EFSMS_ID);
            }
            break;
        case MN_MSG_USIM_POWER_WAIT_EFSMSREC:
            MN_NORM_LOG("MSG_GetEfCnfTimeout:WAIT EFSMSREC");
            /*��ȡEFSMSR�ļ�������*/
            if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
            {
                MN_MSG_GetUsimParmReq(USIMM_USIM_EFSMSR_ID);
            }
            else
            {
                MN_MSG_GetUsimParmReq(USIMM_TELE_EFSMSR_ID);
            }
            break;
        case MN_MSG_USIM_POWER_WAIT_EFSMS:
            MN_NORM_LOG("MSG_GetEfCnfTimeout:WAIT EFSMS");
            MSG_GetEfSmsTimerout();
            break;
        case MN_MSG_USIM_POWER_WAIT_EFSMSR:
            MN_NORM_LOG("MSG_GetEfCnfTimeout:WAIT EFSMSR");
            /*�ϱ���ʼ�����*/
            MN_MSG_GetUsimParmReq(USIMM_DEF_FILEID_BUTT);
            break;
        default:
            MN_WARN_LOG("MSG_GetEfCnfTimeout:Invalid enPowerState");
            break;
    }
}

/*****************************************************************************
 �� �� ��  : MSG_WaitRetryPeriodTimeout()
 ��������  : �ط����ڶ�ʱ����ʱ,�����κδ���,����¼��־
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2009��7��06��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_VOID MSG_WaitRetryPeriodTimeout(
    VOS_UINT32                          ulParam
)
{
    MN_INFO_LOG("MSG_WaitRetryPeriodTimeout:RetryPeriodTimeout");
}

/*****************************************************************************
 �� �� ��  : MSG_GetRetrySendDomain
 ��������  : ��ȡ���ŷ����ط�������
             ���û�������CS��Ϊ���ͳ�����������������CS���ط�
             ���򣬿�����PS���ط�����
 �������  : MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain �û��������Ͷ��ŵĳ�����
 �������  : MN_MSG_SEND_DOMAIN_ENUM_U8         *penSendDomain    ��ǰ���õķ�����
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��29��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MSG_GetRetrySendDomain(
    MN_MSG_SEND_DOMAIN_ENUM_U8          enHopeSendDomain,
    MN_MSG_SEND_DOMAIN_ENUM_U8         *penSendDomain
)
{
    /* �˴��޸�:
       �޸�ǰ: ֻ��CS�����ط�����,PS�򲻴��ڴ˹���
       �޸ĺ�: ֧����CS���PS���ط� */
    *penSendDomain = MN_MSG_SEND_DOMAIN_NO;

    if ((MN_MSG_SEND_DOMAIN_CS == enHopeSendDomain)
     || (MN_MSG_SEND_DOMAIN_CS_PREFERRED == enHopeSendDomain)
     || (MN_MSG_SEND_DOMAIN_PS_PREFERRED == enHopeSendDomain))
    {
        MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_CS, penSendDomain);
    }

    if (MN_MSG_SEND_DOMAIN_NO != *penSendDomain)
    {
        return;
    }

    if ((MN_MSG_SEND_DOMAIN_PS == enHopeSendDomain)
     || (MN_MSG_SEND_DOMAIN_CS_PREFERRED == enHopeSendDomain)
     || (MN_MSG_SEND_DOMAIN_PS_PREFERRED == enHopeSendDomain))
    {
        MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_PS, penSendDomain);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MSG_WaitRetryIntervalTimeout()
 ��������  : �ط�ʱ������ʱ����ʱ,���·��Ͷ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2009��7��06��
    ��    ��   : z40661
    �޸�����   : �����ɺ���

  2.��    ��   : 2010��5��7��
    ��    ��   : zhoujun /z40661
    �޸�����   : AT2D19153���ط�ʱ�䲻��ʱ��δ��ֹͣ��ʱ��
  3.��    ��   : 2011��3��29��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2011030500602������CS����õ��жϱ�׼��UE������Ϊ��PS
                 ONLY, IMSI��CS����Ч��CS��δ��BAR����¿��Գ����ط���֧����PS���ط�����
  4.��    ��   : 2012��11��08��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2012110604069��TAF���ط���SUBMIT����TP-RDӦ���޸�Ϊ1��
                 ָʾ�������ľܾ������ظ�����
  5.��    ��   : 2012��12��28��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2012122406218, ��������������������: ���ŷ������̲���
  6.��    ��   : 2013��8��3��
    ��    ��   : z60575
    �޸�����   : TQE�޸�
  7.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK����
  8.��    ��   : 2013��7��15��
    ��    ��   : y00245242
    �޸�����   : ������Ϣ·�ɣ���ʱ����ʱʱ������ȷ·��   
*****************************************************************************/
LOCAL VOS_VOID MSG_WaitRetryIntervalTimeout(
    VOS_UINT32                          ulParam
)
{
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    VOS_UINT32                          ulRet;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    SMR_SMT_MO_REPORT_STRU              stRpErrInfo;
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

    PS_MEM_SET(&stMoEntity,0X00,sizeof(stMoEntity));
    MN_MSG_GetMoEntity(&stMoEntity);

    PS_MEM_SET(&stRpErrInfo, 0, sizeof(stRpErrInfo));

    /* ��ǰ���Ƿ��Ͷ��Ź����� */
    if (MN_MSG_MO_STATE_WAIT_REPORT_IND != stMoEntity.enSmaMoState)
    {
        MN_WARN_LOG("MSG_WaitRetryIntervalTimeout:Mo State is NULL");
        return;
    }

    MSG_GetRetrySendDomain(stMoEntity.enHopeSendDomain, &stMoEntity.enSendDomain);

    if (MN_MSG_SEND_DOMAIN_NO != stMoEntity.enSendDomain)
    {
        /* TAF���ط���SUBMIT����TP-RDӦ���޸�Ϊ1��ָʾ�������ľܾ������ظ����� */
        MN_MSG_SetTpRd(&stMoEntity);

        /*��һ��������RP-Data���͸�NAS���SMSģ��*/
        /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, begin */
        ulRet = MN_MSG_SendSmsRpDataReq(stMoEntity.enSendDomain,
                                        stMoEntity.aucRpDataInfo,
                                        stMoEntity.ucRpDataLen,
                                        stMoEntity.enMsgSignallingType);        
        /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, end */
        
        if (VOS_OK == ulRet)
        {
            /* ����MO���� */
            MN_MSG_CreateMoInfo(&stMoEntity);
            return;
        }

    }

    /* �ϱ����Ͷ���ʧ�� */
    MN_MSG_GetRpErrInfo(&stRpErrInfo);
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    MN_MSG_RcvSmsRpRpt(&stRpErrInfo);
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */

    /*  ����Ҫֹͣ��ʱ�� */
    MN_MSG_StopTimer(MN_MSG_ID_WAIT_RETRY_PERIOD);
}

/*****************************************************************************
 �� �� ��  : MSG_WaitFdnCheckTimeout
 ��������  : �ȴ�USIM��FDN�������ʱ����
 �������  : ulParam        ����ģ�鶨ʱ��͸��������FDN����δʹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��02��23��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_VOID MSG_WaitFdnCheckTimeout(
    VOS_UINT32                          ulParam
)
{
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulIndex;
    VOS_BOOL                            bBufferEntity;

    PS_MEM_SET(&stMoEntity,0X00,sizeof(stMoEntity));
    /* ��ȡ�ȴ�FDN�������MOʵ��򻺴� */
    ulRet = MN_MSG_GetSpecificStatusMoEntity(MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP,
                                             &bBufferEntity,
                                             &ulIndex,
                                             &stMoEntity);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MSG_WaitSmsMoControlCheckTimeout: discard SMS MO CONTROL RESPONSE.");
        return;
    }

    /* MO״̬��ƥ��: û�еȴ�SMS MO CONTROL RESPONSE��Ϣ */
    if (MN_MSG_MO_STATE_WAIT_FDN_CHECK_RSP != stMoEntity.enSmaMoState)
    {
        MN_WARN_LOG("MSG_WaitFdnCheckTimeout: Mo State is invalid.");
        return;
    }

    /*
    �ȴ�USIMģ���FDN��Ϣ��ʱ:
            ֪ͨAPP���ŷ������󱻾ܾ���
            �ͷŶ��ŷ���ʵ�壻
    */
    MN_WARN_LOG("MSG_WaitFdnCheckTimeout: wait for FDN check response timeout.");
    MN_SendClientResponse(stMoEntity.clientId,
                          stMoEntity.opId,
                          MN_ERR_CLASS_SMS_INTERNAL);

    /* ���ٵȴ�FDN�������MOʵ��򻺴� */
    MN_MSG_DestroySpecificMoEntity(bBufferEntity, ulIndex);

    /* ֪ͨSPM����� */
    TAF_MSG_SendSpmMsgCheckResultInd(stMoEntity.clientId, stMoEntity.opId,TAF_MSG_ERROR_FDN_CHECK_TIMEROUT);

    return;

}

/*****************************************************************************
 �� �� ��  : MN_MSG_InitAllTimers
 ��������  : ��ʼ�����ж�ʱ����Ӧ�ڳ�ʼ����Resetʱ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��04��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_MSG_InitAllTimers(VOS_VOID)
{
    VOS_UINT32                          i;

    for (i=0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
    {
        f_astMsgTimerHandle[i].hTimer = VOS_NULL_PTR;
        f_astMsgTimerHandle[i].enTimerId = MN_MSG_TID_MAX;
    }
}

/*****************************************************************************
 �� �� ��  : MN_MSG_StartTimer
 ��������  : ����ָ���Ķ�ʱ��
 �������  : enTimerId:ָ����ʱ��TimerId
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��18��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_MSG_StartTimer(
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId,
    VOS_UINT32                          ulParam
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;

    if (enTimerId >= MN_MSG_TID_MAX)
    {
        MN_WARN_LOG("MN_MSG_StartTimer: Invalid enTimerId. ");
        return;
    }

    /* Ѱ�ҿ��еĶ�ʱ����� */
    for (i=0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
    {
        if (VOS_NULL_PTR == f_astMsgTimerHandle[i].hTimer)
        {
            break;
        }
    }

    if (i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG))
    {
        /* ����VOS��ʱ�� */
        ulRet = NAS_StartRelTimer(&f_astMsgTimerHandle[i].hTimer,
                                  WUEPS_PID_TAF,
                                  f_astMsgTimerInfoTbl[enTimerId - MN_TIMER_CLASS_MSG].ulTimeout,
                                  (VOS_UINT32)enTimerId,
                                  ulParam,
                                  VOS_RELTIMER_NOLOOP);
        if (VOS_OK == ulRet)
        {
            /* ��¼��ʱ������ */
            f_astMsgTimerHandle[i].enTimerId = enTimerId;
        }
        else
        {
            MN_WARN_LOG("MN_MSG_StartTimer: VOS_StartRelTimer failed.");
        }
    }
    else
    {
        MN_WARN_LOG("MN_MSG_StartTimer: Can not find free timer handle.");
    }
}

/*****************************************************************************
 �� �� ��  : MN_MSG_StopTimer
 ��������  : ָֹͣ���Ķ�ʱ��
 �������  : enTimerId:ָ����ʱ��TimerId
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��11��26��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_StopTimer(
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;

    if (enTimerId >= MN_MSG_TID_MAX)
    {
        return;
    }

    /* Ѱ��entityId��enTimerId������ƥ��ľ�� */
    for (i = 0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
    {
      if (enTimerId == f_astMsgTimerHandle[i].enTimerId)
      {
          break;
      }
    }

    if (i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG))
    {
        /* ֹͣVOS��ʱ�� */
        ulRet = NAS_StopRelTimer(WUEPS_PID_TAF, enTimerId, &f_astMsgTimerHandle[i].hTimer);
        if (VOS_OK == ulRet)
        {
            f_astMsgTimerHandle[i].hTimer = VOS_NULL_PTR;
            f_astMsgTimerHandle[i].enTimerId = MN_MSG_TID_MAX;
        }
        else
        {
            MN_WARN_LOG("MN_MSG_StopTimer: NAS_StopRelTimer failed.");
        }
    }
    else
    {
        MN_WARN_LOG("MN_MSG_StopTimer: Can not find the timer handle.");
    }
}

/*****************************************************************************
 �� �� ��  : MN_MSG_StopAllRunningTimer
 ��������  : ֹͣ���е�ǰ�����������еĶ�ʱ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��9��1��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_MSG_StopAllRunningTimer(VOS_VOID)
{
    VOS_UINT32                          i;

    for (i = 0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
    {
        if ( (VOS_NULL_PTR      != f_astMsgTimerHandle[i].hTimer)
          && (MN_MSG_TID_MAX    != f_astMsgTimerHandle[i].enTimerId) )
        {
             /* ֹͣVOS��ʱ�� */
            if (VOS_OK == NAS_StopRelTimer(WUEPS_PID_TAF,
                                 f_astMsgTimerHandle[i].enTimerId,
                                 &f_astMsgTimerHandle[i].hTimer))
            {
                f_astMsgTimerHandle[i].hTimer    = VOS_NULL_PTR;
                f_astMsgTimerHandle[i].enTimerId = MN_MSG_TID_MAX;
            }
            else
            {
                MN_WARN_LOG("MN_MSG_StopAllRunningTimer: NAS_StopRelTimer failed.");
            }
        }
    }

    return;
}



/*****************************************************************************
 �� �� ��  : MN_MSG_IsTimerStarting
 ��������  : �ж�ĳ����ʱ����ǰ�Ƿ�ʱ����״̬
 �������  : enTimerId:ָ����ʱ��TimerId
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�ö�ʱ���ѿ���
             VOS_FALSE:�ö�ʱ���ѹر�

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��18��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��4��5��
    ��    ��   : l00171473
    �޸�����   : for V7R1C50 CSFB&PPAC&ETWS&ISR
*****************************************************************************/
VOS_UINT32  MN_MSG_IsTimerStarting(
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId
)
{
    VOS_UINT32                          i;

    if (enTimerId >= MN_MSG_TID_MAX)
    {
        return VOS_FALSE;
    }

    for (i = 0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
    {
      if (enTimerId == f_astMsgTimerHandle[i].enTimerId)
      {
          break;
      }
    }

    if (i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG))
    {
        if (VOS_NULL_PTR != f_astMsgTimerHandle[i].hTimer)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : MN_MSG_GetTimerRemainTime
 ��������  : ��ȡ��ʱ��ʣ���ʱ��
 �������  : enTimerId:ָ����ʱ��TimerId
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��12��18��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��1��30��
    ��    ��   : l00130025
    �޸�����   : DTS2012010500368,����ͬ���ӿ�VOS_GetRelTmRemainTimehTimerʱû���ж�hTimer�Ƿ�Ϊ0���붨ʱ���첽��Ϣ��ͻ�����쳣��ӡ
*****************************************************************************/
VOS_UINT32  MN_MSG_GetTimerRemainTime(
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId
)
{
    VOS_UINT32                          ulTick;
    VOS_UINT32                          i;

    if (enTimerId >= MN_MSG_TID_MAX)
    {
        return 0;
    }
    for (i = 0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
    {
      if (enTimerId == f_astMsgTimerHandle[i].enTimerId)
      {
          break;
      }
    }
    if ( i >= (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG))
    {
        return 0;
    }

    ulTick = 0;

    /* hTimer Ϊ��ʱ��˵���˶�ʱ���ѳ�ʱ��ֹͣ */
    if (VOS_NULL_PTR != f_astMsgTimerHandle[i].hTimer)
    {
        if (VOS_OK != VOS_GetRelTmRemainTime(&(f_astMsgTimerHandle[i].hTimer), &ulTick))
        {
            ulTick = 0;
        }
    }
    return ulTick * MN_MSG_TIMER_TICK;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_UpdateRetryPeriod
 ��������  : ���¶�ʱ��ģ���е�ǰ�����ط�ʱ�����ں�ʱ����
 �������  : enTimerId :��ǰ��ʱ��ID
             ulTimerLen:���º�ʱ����ʱ��
 �� �������  :
 �� �� ֵ  :��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2009��7��06��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_UpdateRetryPeriod(
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId,
    VOS_UINT32                          ulTimerLen
)
{
    VOS_UINT32                          i = (VOS_UINT32)(enTimerId - MN_TIMER_CLASS_MSG);

    if ( i >= (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG) )
    {
        MN_WARN_LOG("MN_MSG_UpdateRetryPeriod: Can not find the timer Id.");
        return;
    }
    f_astMsgTimerInfoTbl[i].ulTimeout = ulTimerLen;
}


/*****************************************************************************
 �� �� ��  : MN_MSG_UpdateListInfo
 ��������  : �����б��ϱ���APPʱ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��15��
    ��    ��   : zhoujun /z40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  MN_MSG_UpdateListInfo(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    VOS_UINT32                          ulLeftReportNum,
    const MN_MSG_LIST_PARM_STRU         *pstList
)
{
    g_clientId = clientId;
    g_opId = opId;
    g_ulLeftReportNum = ulLeftReportNum;
    PS_MEM_CPY(&g_stList,pstList,sizeof(g_stList));

}

/*****************************************************************************
 �� �� ��  : MSG_ListMsgWaitAppTimeout
 ��������  : �б�ʱ����ʱ���ϱ�Ӧ��ʣ�����б�Ķ���
 �������  : ulParam  -  ��ʱ������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��3��15��
    ��    ��   : zhoujun /z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��1��10��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2010010400031 ���AT����AT+CPMS="SM";+CMGL=4����Ӧ
  3.��    ��   : 2012��12��12��
    ��    ��   : z60575
    �޸�����   : TQE�޸�

  4.��    ��   : 2013��9��29��
    ��    ��   : w00167002
    �޸�����   : DTS201309210014:ɾ��C��TASKDELAY������V9�͹���ʱ���ᵼ��
                   TASKDELAY��δ�����ѣ�����AT��Ϣû�лظ���
                 MSG_ListMsgWaitAppTimeout��������ΪTAF_MSG_ListLeftMsg.
                 �����к���λ�õ�����

*****************************************************************************/
VOS_VOID TAF_MSG_ListLeftMsg(VOS_VOID)
{
    MN_MSG_LIST_EVT_INFO_STRU           *pstListEvt;


    pstListEvt = (MN_MSG_LIST_EVT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_MSG_LIST_EVT_INFO_STRU));
    if (VOS_NULL_PTR == pstListEvt)
    {
        MN_ERR_LOG("TAF_MSG_ListLeftMsg:ALLOC MEM FAIL");
        return;
    }
    else
    {
        pstListEvt->bSuccess = VOS_TRUE;
        pstListEvt->bLastListEvt = VOS_TRUE;
        pstListEvt->bFirstListEvt = VOS_FALSE;

        PS_MEM_CPY( &(pstListEvt->stReceivedListPara), &g_stList, sizeof(MN_MSG_LIST_PARM_STRU) );
    }

    if (0 == g_ulLeftReportNum)
    {
        pstListEvt->ulReportNum = 0;
        pstListEvt->ulFailCause = MN_ERR_NO_ERROR;
        MN_MSG_ReportListEvent(g_clientId,g_opId,pstListEvt,MN_MSG_EVT_LIST);
    }
    else
    {
        /* ���ú����ֶ��ϱ����б���� */
        MN_MSG_RptMsg(g_clientId, g_opId, g_ulLeftReportNum, &g_stList, pstListEvt);
    }
    PS_MEM_FREE(WUEPS_PID_TAF, pstListEvt);
}


/*****************************************************************************
 �� �� ��  : MN_MSG_ProcTimeoutMsg
 ��������  : ����ʱ����ʱ��Ϣ��
 �������  : pMsg  - ��ʱ����ʱ��Ϣ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��2��04��
    ��    ��   : �ܾ�40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  MN_MSG_ProcTimeoutMsg(
    REL_TIMER_MSG                       * pTmrMsg
)
{
    MN_MSG_TIMER_HANDLE_STRU            *pstHandle;
    MN_MSG_TIMER_ID_ENUM_U32            enTimerId;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          i;

    enTimerId = (MN_MSG_TIMER_ID_ENUM_U32)pTmrMsg->ulName;
    if (enTimerId < MN_TIMER_CLASS_MSG)
    {
        return;
    }
    else
    {
        for (i=0; i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG); i++)
        {
            if (enTimerId == f_astMsgTimerHandle[i].enTimerId)
            {
                break;
            }
        }

        if ( i < (MN_MSG_TID_MAX - MN_TIMER_CLASS_MSG) )
        {
            ulIndex = enTimerId - MN_TIMER_CLASS_MSG;

        }
        else
        {
            MN_WARN_LOG1("MN_MSG_ProcTimeoutMsg:Invalid Timer ID", (VOS_INT32)enTimerId);
            return;
        }
    }

    MN_NORM_LOG1("TAF SMA Timer expired.", (VOS_INT32)enTimerId);

    /* ��ulName�õ���ʱ����� ���þ����λ */
    pstHandle = (MN_MSG_TIMER_HANDLE_STRU *)&f_astMsgTimerHandle[i];
    pstHandle->hTimer = VOS_NULL_PTR;
    pstHandle->enTimerId = MN_MSG_TID_MAX;

    /* ����Timer ID��Ӧ�ĳ�ʱ������ */
    f_astMsgTimerInfoTbl[ulIndex].pfnTimeoutProc(pTmrMsg->ulPara);
}

/*****************************************************************************
 �� �� ��  : MSG_WaitSmsMoControlCheckTimeout
 ��������  : �ȴ�USIM��SMS MO CONTROL�������ʱ����
 �������  : ulParam        ����ģ�鶨ʱ��͸��������SMS MO CONTROL����δʹ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2012��09��23��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_VOID  MSG_WaitSmsMoControlCheckTimeout(
    VOS_UINT32                          ulParam
)
{
    MN_MSG_MO_ENTITY_STRU               stMoEntity;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulIndex;
    VOS_BOOL                            bBufferEntity;

    PS_MEM_SET(&stMoEntity,0X00,sizeof(stMoEntity));
    /* ��ȡ�ȴ�FDN�������MOʵ��򻺴� */
    ulRet = MN_MSG_GetSpecificStatusMoEntity(MN_MSG_MO_STATE_WAIT_SMS_CTRL_RSP,
                                             &bBufferEntity,
                                             &ulIndex,
                                             &stMoEntity);
    if (MN_ERR_NO_ERROR != ulRet)
    {
        MN_WARN_LOG("MSG_WaitSmsMoControlCheckTimeout: discard SMS MO CONTROL RESPONSE.");
        return;
    }

    /*
    �ȴ�USIMģ���SMS MO CONTROL RESPONSE��Ϣ��ʱ:
            ֪ͨAPP���ŷ������󱻾ܾ���
            �ͷŶ��ŷ���ʵ�壻
    */
    MN_WARN_LOG("MSG_WaitSmsMoControlCheckTimeout: wait for SMS MO CONTROL RESPONSE timeout.");
    MN_SendClientResponse(stMoEntity.clientId,
                          stMoEntity.opId,
                          MN_ERR_CLASS_SMS_INTERNAL);

    /* ���ٵȴ�SMS MO CONTROL�������MOʵ��򻺴� */
    MN_MSG_DestroySpecificMoEntity(bBufferEntity, ulIndex);

    /* ֪ͨSPM����� */
    TAF_MSG_SendSpmMsgCheckResultInd(stMoEntity.clientId, stMoEntity.opId,TAF_MSG_ERROR_CTRL_CHECK_TIMEOUT);

    return;

}

/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

