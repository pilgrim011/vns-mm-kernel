/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnMsgComm.c
  �� �� ��   : ����
  ��    ��   : �ܾ� 40661
  ��������   : 2008��2��23��
  ����޸�   :
  ��������   :
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��2��23��
    ��    ��   : �ܾ� 40661
    �޸�����   : �����ļ�
  2.��    ��   : 2008��8��14��
    ��    ��   : ��ӳ�� 62575
    �޸�����   : ���ⵥ�� AT2D03741,��̹淶���⣺   1��ö�����Ͷ���   2��ȫ�ֱ������ⲿ����   3���ļ�������ע�����⣻   ��ӡ��Ϣ������   1�����ӵ��Դ�ӡ����
  3.��    ��   : 2008��10��10��
    ��    ��   : f62575
    �޸�����   : ���ⵥ�ţ�AT2D06152��AT2D06151��, USIMM�Ż������SMSP�ļ���ض�д����ʧ��
  5.��    ��   : 2009��3��3��
    ��    ��   : z40661
    �޸�����   : ���ⵥ�ţ�AT2D07942��AT2D09557��, �������ĺ����ϱ�ʱ��ϳ�
  6.��    ��   : 2009��7��18��
    ��    ��   : z40661
    �޸�����   : �ն˿������������
  7.��    ��   : 2009��7��31��
    ��    ��   : f62575
    �޸�����   : ���ⵥ�ţ�AT2D13420,����TAFģ���ʼ���������
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MnMsgInclude.h"
#include "NasGmmInterface.h"
#include "NVIM_Interface.h"
#include "MnMsgCtx.h"
#include "MnMsgProcNvim.h"

#include "TafCbaCtx.h"

/* Added by l00167671 for NV�����Ŀ , 2013-05-17, begin */
#include "NasNvInterface.h"
#include "TafNvInterface.h"
/* Added by l00167671 for NV�����Ŀ , 2013-05-17, end*/
#include "NasUsimmApi.h"
#include "TafSdcCtx.h"

#if (FEATURE_ON == FEATURE_PTM)
#include "NasComm.h"
#include "TafSdcLib.h"
#endif

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/
/*lint -e767 �޸���:�޽� 107747;������:���ٻ�65952;ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        PS_FILE_ID_MNMSG_COMM_C
/*lint +e767 �޸���:�޽� 107747;������:sunshaohua*/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/* Deleted by l00167671 for NV�����Ŀ , 2013-05-17, begin */
/* Deleted by l00167671 for NV�����Ŀ , 2013-05-17, end*/

typedef struct
{
    VOS_UINT8                           ucActFlg;/* MN_MSG_NVIM_ITEM_ACTIVE */
    VOS_UINT8                           aucReserved[3];
}MN_MSG_CLOSE_SMS_CAPABILITY_MSG_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/

MN_MSG_DISCARD_DELIVER_MSG_STRU         f_stMnMsgDiscardDeliverMsg;
MN_MSG_REPLACE_DELIVER_MSG_STRU         f_stMnMsgReplaceDeliverMsg;

MN_MSG_CLOSE_SMS_CAPABILITY_MSG_STRU    f_stMnMsgCloseSmsCapabilityMsg;

extern VOS_VOID NAS_MM_CsSimValid(VOS_BOOL *pbCsSimValid);
extern VOS_VOID NAS_MM_CsCellBar(VOS_BOOL *pbCsCellBar);


/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : MN_MSG_DeliverMsgNotSupport
 ��������  : �ж�UE��֧�ֵĶ�������
 �������  : const MN_MSG_TS_DATA_INFO_STRU      *pstTsData     ���յ��Ķ��Ž��������ݽṹ
 �������  : VOS_BOOL                            *pbSupportFlag �Ƿ�UE��֧�ֵĶ�������
                                                 VOS_TRUE    UE��֧�ֵĶ���
                                                 VOS_FALSE   UE֧�ֵĶ���
             MN_MSG_TP_CAUSE_ENUM_U8             *penTpCause
                                                 UE��֧�ֵĶ������ͣ�pbSupportFlag����ΪVOS_TRUEʱ��Ч
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��20��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
	               DTS2011061006066, EM���ڶ��Ŷ�������
*****************************************************************************/
VOS_VOID MN_MSG_DeliverMsgNotSupport(
    const MN_MSG_TS_DATA_INFO_STRU      *pstTsData,
    VOS_BOOL                            *pbSupportFlag,
    MN_MSG_TP_CAUSE_ENUM_U8             *penTpCause
)
{
    VOS_UINT32                          ulLoop;
    const MN_MSG_DCS_CODE_STRU         *pstDcs;
    const MN_MSG_USER_DATA_STRU        *pstUserData;

    *penTpCause     = MN_MSG_TP_CAUSE_UNSPECIFIED_ERR;
    *pbSupportFlag  = VOS_TRUE;

    /* �ж��Ƿ����ö��Ŷ������ԣ�����Ӧ�û�UE�಻֧�ֵĶ��� */
    if (MN_MSG_NVIM_ITEM_INACTIVE == f_stMnMsgDiscardDeliverMsg.ucActFlg)
    {
        return;
    }

    /* ����TP-UD�а���Special SMS Message Indication IE�Ķ��ţ��ö���Ӧ�ò�֧�� */
    pstUserData = &pstTsData->u.stDeliver.stUserData;
    for (ulLoop = 0; ulLoop < pstUserData->ucNumofHeaders; ulLoop++)
    {
        if (MN_MSG_UDH_SPECIAL_SM == pstUserData->astUserDataHeader[ulLoop].enHeaderID)
        {
            *pbSupportFlag = VOS_FALSE;
            return;
        }
    }

    /* ����TP-DCS��ʽ��Ϊ00XX��ʽ�Ķ��ţ��ö���Ӧ�ò�֧�� */
    pstDcs = &pstTsData->u.stDeliver.stDcs;
    if ((MN_MSG_MSG_WAITING_DISCARD == pstDcs->enMsgWaiting)
     || (MN_MSG_MSG_WAITING_STORE == pstDcs->enMsgWaiting)
     || (MN_MSG_MSG_WAITING_AUTO_DELETE == pstDcs->enMsgWaiting))
    {
        *pbSupportFlag = VOS_FALSE;
        *penTpCause = MN_MSG_TP_CAUSE_DCS_NOT_SUPPORTED;
        return;
    }

    if (MN_MSG_MSG_WAITING_NONE_1111 == pstDcs->enMsgWaiting)
    {
        *pbSupportFlag = VOS_FALSE;
        *penTpCause = MN_MSG_TP_CAUSE_DCS_NOT_SUPPORTED;
        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_MtSpecificFeatureInit
 ��������  : ��ʼ�����Ž��չ��ܶ���NV��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��20��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
                   DTS2011061006066, EM���ڶ��Ŷ�������
*****************************************************************************/
VOS_VOID MN_MSG_MtSpecificFeatureInit(VOS_VOID)
{
    VOS_UINT32                          ulRet;

    ulRet = NV_Read(en_NV_Item_DISCARD_DELIVER_MSG_FEATURE,
                    &f_stMnMsgDiscardDeliverMsg,
                    sizeof(f_stMnMsgDiscardDeliverMsg));
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_MtSpecificFeatureInit: Read en_NV_Item_Sms_MeStorageEnable Failed");
        f_stMnMsgDiscardDeliverMsg.ucActFlg = MN_MSG_NVIM_ITEM_INACTIVE;
    }

    ulRet = NV_Read(en_NV_Item_REPLACE_DELIVER_MSG_FEATURE,
                    &f_stMnMsgReplaceDeliverMsg,
                    sizeof(f_stMnMsgReplaceDeliverMsg));
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_MtSpecificFeatureInit: Read en_NV_Item_SMS_REPLACEMENT_FEATURE Failed");
        f_stMnMsgReplaceDeliverMsg.ucActFlg = MN_MSG_NVIM_ITEM_ACTIVE;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_GetReplaceFeature
 ��������  : ��ȡ�����滻�������ñ��
 �������  : VOS_UINT8 *pucActFlg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��25��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
                   DTS2011061006066, EM���ڶ��Ŷ�������
*****************************************************************************/
VOS_VOID MN_MSG_GetReplaceFeature(VOS_UINT8 *pucActFlg)
{
    *pucActFlg = f_stMnMsgReplaceDeliverMsg.ucActFlg;
}

/***********************************************************************
�� �� ��  : MN_MSG_Init
��������  : ��ʼ�����ź͹㲥��Ϣ�ľ�̬����
�������  : None
�������  : ��
�� �� ֵ  :
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��15��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��3��20��
   ��    ��   : l00171473
   �޸�����   : for V7R1C50 CSFB&PPAC&ETWS&ISR
************************************************************************/
VOS_VOID MN_MSG_Init(VOS_VOID)
{
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    MN_MSG_ReadNvimInfo();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    MN_MSG_SmInit();
#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    TAF_CBA_Init();
#endif

    return;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_PowerOff
 ��������  : ��ػ�ʱʹ�ã��������MSGģ�����ر���
 �������  : ��
 �������  : ��

 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2009��07��16��
    ��    ��   : z40661
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��30��
    ��    ��   : w00176964
    �޸�����   : ETWS����
  3.��    ��   : 2012��3��30��
    ��    ��   : l00171473
    �޸�����   : for V7R1C50 CSFB&PPAC&ETWS&ISR ,���CBA CTX�ĳ�ʼ��


  4.��    ��   : 2014��9��1��
    ��    ��   : w00167002
    �޸�����   : DTS2014083004404:

*****************************************************************************/
VOS_VOID MN_MSG_PowerOff()
{
    MN_MSG_FinishMoProc();

    MN_MSG_DestroyMtInfo();

    MN_MSG_UpdateSendFailFlag(MN_MSG_SEND_FAIL_NO_DOMAIN);

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* ��ʼ��CBA������Ϣ.  ������Ҫ��ʼ��ΪBUTTֵ��ԭ����: ���ٴ������յ�MMC��NET MODE INDʱ,
       �Ż���AS���ͼ���CBS������ */
    TAF_CBA_InitNetworkInfo();
#endif


    /* ֹͣ�����������еĶ�ʱ�� */
    MN_MSG_StopAllRunningTimer();

    /*��ʼ����ʱ����ز���*/
    MN_MSG_InitAllTimers();
}

/***********************************************************************
�� �� ��  : MN_MSG_CfgDataInit
��������  : TAFģ���յ�USIM����λ������Ϣ��,�Ⱥ�֪ͨ����ģ��͹㲥��Ϣģ��
�������  : ucUsimState:USIM���Ƿ���λ
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2007��10��26��
   ��    ��   : z40661
   �޸�����   : �����ɺ���
 2.��    ��   : 2012��3��20��
   ��    ��   : l00171473
   �޸�����   : for V7R1C50 CSFB&PPAC&ETWS&ISR
************************************************************************/
VOS_VOID MN_MSG_CfgDataInit(
    MNPH_USIM_STATUS_ENUM_U32           enUsimStatus
)
{
    MN_MSG_SmCfgDataInit(enUsimStatus);
}
/***********************************************************************
�� �� ��  : MN_MSG_PrintBcdAddrStru
��������  : ��ӡMN_MSG_BCD_ADDR_STRU�ṹ����
�������  : pstAddr MN_MSG_BCD_ADDR_STRU�ṹ����
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintBcdAddrStru(
    MN_MSG_BCD_ADDR_STRU                *pstAddr
)
{
    VOS_UINT32                          ulLoop;

    MN_INFO_LOG1("MN_MSG_PrintBcdAddrStru: addr len is ", pstAddr->ucBcdLen);
    MN_INFO_LOG1("MN_MSG_PrintBcdAddrStru: addr type is ", pstAddr->addrType);
    for (ulLoop = 0; ulLoop < MN_MSG_MAX_BCD_NUM_LEN; ulLoop++)
    {
        MN_INFO_LOG1("MN_MSG_PrintBcdAddrStru: ", pstAddr->aucBcdNum[ulLoop]);
    }
    return;
}

/***********************************************************************
�� �� ��  : MN_MSG_PrintSrvParamStru
��������  : ��ӡMN_MSG_SRV_PARAM_STRU�ṹ����
�������  : pstSrvParam MN_MSG_SRV_PARAM_STRU�ṹ����
�������  : ��
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ      :
 1.��    ��   : 2008��6��17��
   ��    ��   : f62575
   �޸�����   : �����ɺ���
************************************************************************/
VOS_VOID MN_MSG_PrintSrvParamStru(
    MN_MSG_SRV_PARAM_STRU               *pstSrvParam
)
{

    MN_INFO_LOG("MN_MSG_PrintSrvParamStru: SMS SERVICE PARAM INFO ");
    MN_INFO_LOG1("MN_MSG_PrintSrvParamStru: Parameter indicate ", pstSrvParam->ucParmInd);
    MN_INFO_LOG("MN_MSG_PrintSrvParamStru: SMS DEST ADDRESS");
    MN_MSG_PrintBcdAddrStru(&pstSrvParam->stDestAddr);
    MN_INFO_LOG("MN_MSG_PrintSrvParamStru: SMS SCA ADDRESS");
    MN_MSG_PrintBcdAddrStru(&pstSrvParam->stScAddr);
    MN_INFO_LOG1("MN_MSG_PrintSrvParamStru: ucPid ", pstSrvParam->ucPid);
    MN_INFO_LOG1("MN_MSG_PrintSrvParamStru: ucDcs ", pstSrvParam->ucDcs);
    MN_INFO_LOG1("MN_MSG_PrintSrvParamStru: ucValidPeriod ", pstSrvParam->ucValidPeriod);
    return;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_InitSmsServiceData
 ��������  : ��ʼ������ҵ��������ݽṹ
 �������  : MN_MSG_CONFIG_PARM_STRU  *pstServicePara  ����ҵ��������ݽṹ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��2��11��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_MSG_InitSmsServiceData(MN_MSG_CONFIG_PARM_STRU  *pstServicePara)
{
    pstServicePara->enAppMemStatus = MN_MSG_MEM_FULL_UNSET;
    pstServicePara->enCbmMemStore = MN_MSG_MEM_STORE_NONE;
    pstServicePara->enRcvSmAct = MN_MSG_RCVMSG_ACT_STORE;
    pstServicePara->enSmMemStore = MN_MSG_MEM_STORE_SIM;
    pstServicePara->enRcvStaRptAct = MN_MSG_RCVMSG_ACT_STORE;
    pstServicePara->enStaRptMemStore = MN_MSG_MEM_STORE_SIM;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_CsDomainAvailable
 ��������  : �ж�CS���Ƿ����: ����UE�ķ�������PS ONLY��CS��IMSI��Ч��CS��δ��BAR����¿���
 �������  : ��
 �������  : VOS_BOOL *pbCsDomainAvailable CS���Ƿ����
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��29��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��03��03��
    ��    ��   : s62952
    �޸�����   : BalongV300R002 Build�Ż���Ŀ
  3.��    ��   : 2015��4��10��
    ��    ��   : h00313353
    �޸�����   : SysCfg�ع�
*****************************************************************************/
VOS_VOID MN_MSG_CsDomainAvailable(VOS_BOOL *pbCsDomainAvailable)
{
    VOS_BOOL                            bCsSimValid;
    VOS_BOOL                            bCsCellBar;
    VOS_UINT8                           ucUeServiceDomain;
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    MN_MSG_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_MSG_GetCustomCfgInfo();

    if (MN_MSG_NV_ITEM_DEACTIVE == pstCustomCfgAddr->ucPsOnlyCsServiceSupportFlg)
    {
        ucUeServiceDomain = MN_MMA_GetServiceDomain();
        if (TAF_MMA_SERVICE_DOMAIN_PS == ucUeServiceDomain)
        {
            *pbCsDomainAvailable = VOS_FALSE;
            return;
        }
    }
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */


    NAS_MM_CsSimValid(&bCsSimValid);
    NAS_MM_CsCellBar(&bCsCellBar);

    if ((VOS_TRUE == bCsSimValid) && (VOS_FALSE == bCsCellBar))
    {
        *pbCsDomainAvailable = VOS_TRUE;
    }
    else
    {
        *pbCsDomainAvailable = VOS_FALSE;
        
        MN_NORM_LOG("MN_MSG_CsDomainAvailable: IS FALSE.");
        
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_UpdateMoEntityAccordingToMoSmsCtrl
 ��������  : ����USIM��MO SMS CONTROL��Ӧ��Ϣȷ�Ͼܾ������ͻ��޸ķ��Ͷ���
 �������  : SI_STK_ENVELOPEDWON_CNF_STRU        *pstEnvelope
             MN_MSG_MO_ENTITY_STRU               *pstMoEntity
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��6��16��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : �����ɺ��� DTS2011062201273 MO SMS CONTROL
  2.��    ��   : 2012��09��20��
    ��    ��   : f62575
    �޸�����   : STK&DCM ��Ŀ
  3.��    ��   : 2012��12��08��
    ��    ��   : l00198894
    �޸�����   : DTS2012120607030: �����ͨ�ض����ÿ�MO SMS CONTROL���ܣ�
                 �ڶ��ŷ��͹����У�(U)SIM���ظ���6F 00״̬�ֽ�ֹ���ŷ�������
  4.��    ��   : 2012��12��26��
    ��    ��   : ����/z00214637
    �޸�����   : PS_USIM_SET_FILE_RLT_SUCCESSת��ΪVOS_OK
  5.��    ��   : 2013��6��5��
    ��    ��   : w00242748
    �޸�����   : SVLTE��USIM�ӿ�����
  6.��    ��   : 2013��6��26��
    ��    ��   : f62575
    �޸�����   : V9R1 STK������MO SMS CONTROL��Ӧ��Ϣ���ݴ�ɾ������STKģ��ʵ��
  7.��    ��   : 2013��7��11��
    ��    ��   : y00245242
    �޸�����   :  for VoLTE_PhaseI  ��Ŀ
  8.��    ��   : 2015��02��06��
    ��    ��   : h00313353
    �޸�����   : USIMM���ӿڵ���

*****************************************************************************/
VOS_UINT32 MN_MSG_UpdateMoEntityAccordingToMoSmsCtrl(
    SI_STK_ENVELOPEDWON_CNF_STRU        *pstEnvelope,
    MN_MSG_MO_ENTITY_STRU               *pstMoEntity
)
{
    VOS_UINT32                          ulRet;
    SI_STK_ENVELOPE_RSP_STRU            stMoSmsRsp;

    PS_MEM_SET(&stMoSmsRsp, 0, sizeof(stMoSmsRsp));

    /* Modified by f62575 for V9R1 STK����, 2013-6-26, begin */
    if (VOS_OK != (pstEnvelope->stCmdResult.ulResult))
    /* Modified by f62575 for V9R1 STK����, 2013-6-26, end */
    {
        /*���ŷ���ʧ������*/
        stMoSmsRsp.Result = SI_STK_CTRL_NOT_ALLOW;

        NAS_STKAPI_SMSCtrlResultInd(&stMoSmsRsp);

        return MN_ERR_CLASS_SMS_MO_CTRL_ACTION_NOT_ALLOWED;
    }
    if (0 != pstEnvelope->stCnfData.ulRspDataLen)
    {
        /* ������Ϣ�еĶ������ĺ����Ŀ�ĺ���������װTPDU�������� */
        (VOS_VOID)NAS_STKAPI_EnvelopeRsp_Decode(pstEnvelope->enEnvelopeType, pstEnvelope->stCnfData.ulRspDataLen, pstEnvelope->stCnfData.aucRspData, &stMoSmsRsp);

        /* ��Ӧ��Ϣ�д���RP-DA���¶������ĺ��� */
        if (SI_STK_CTRL_NOT_ALLOW == stMoSmsRsp.Result)
        {

            NAS_STKAPI_SMSCtrlResultInd(&stMoSmsRsp);


            NAS_STKAPI_EnvelopeRspDataFree(&stMoSmsRsp);

            return MN_ERR_CLASS_SMS_MO_CTRL_ACTION_NOT_ALLOWED;
        }

        if(SI_STK_CTRL_ALLOW_MODIFY == stMoSmsRsp.Result)
        {
            ulRet = MN_MSG_MoCtrlAllowedWithModification(&stMoSmsRsp.uResp.MoSmsCtrlRsp,
                                           pstMoEntity);

            if (MN_ERR_NO_ERROR != ulRet)
            {
                stMoSmsRsp.Result = SI_STK_CTRL_NOT_ALLOW;

                NAS_STKAPI_SMSCtrlResultInd(&stMoSmsRsp);


                NAS_STKAPI_EnvelopeRspDataFree(&stMoSmsRsp);

                return ulRet;
            }

            MN_MSG_CreateMoInfo(pstMoEntity);
        }

    }
    else
    {
        stMoSmsRsp.Result = SI_STK_CTRL_ALLOW_NOMODIFY;
    }


    NAS_STKAPI_SMSCtrlResultInd(&stMoSmsRsp);


    NAS_STKAPI_EnvelopeRspDataFree(&stMoSmsRsp);

    /* ���Ͷ��ŵ�SMS�� */
    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, begin */
    ulRet = MN_MSG_SendSmsRpDataReq(pstMoEntity->enSendDomain,
                                    pstMoEntity->aucRpDataInfo,
                                    pstMoEntity->ucRpDataLen,
                                    pstMoEntity->enMsgSignallingType);
    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-11, end */

    if (VOS_ERR == ulRet)
    {
        return MN_ERR_SEND_MSG_ERROR;
    }

    return MN_ERR_NO_ERROR;
}


/*****************************************************************************
 �� �� ��  : MN_MSG_GetCloseSMSFeature
 ��������  : ��ȡ���Źرչ������ñ��
 �������  : VOS_UINT8 *pucActFlg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��9��
    ��    ��   : w00176964
    �޸�����   : DTS20129876543210:EM�رն��Ŷ�������
*****************************************************************************/
VOS_VOID MN_MSG_GetCloseSMSFeature(VOS_UINT8 *pucActFlg)
{
    *pucActFlg = f_stMnMsgCloseSmsCapabilityMsg.ucActFlg;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_CloseSmsCapabilityFeatureInit
 ��������  : ��ʼ���رն��Ź��ܶ���NV��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��3��17��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
                   DTS2012031900095, EM&SBM �رն��Ź��ܶ�������
  2.��    ��   : 2012��4��25��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
                 DTS2012042403564, ��ȡNV�Ȼ�ȡ���Ⱥ��ȡ
  3.��    ��   : 2012��12��11��
    ��    ��   : L00171473
    �޸�����   : DTS201212110930, TQE����
  4.��    ��   : 2013��5��17��
    ��    ��   : l00167671
    �޸�����   : NV������Ŀ, ��NV�������ýṹ������
*****************************************************************************/
VOS_VOID MN_MSG_CloseSmsCapabilityFeatureInit(VOS_VOID)
{
    VOS_UINT32                                              ulRet;
    VOS_UINT32                                              ulLength;

    NAS_NVIM_CLOSE_SMS_CAPABILITY_CFG_STRU                  stCloseSmsCapabilityCfg;

    PS_MEM_SET(&stCloseSmsCapabilityCfg, 0, sizeof(NAS_NVIM_CLOSE_SMS_CAPABILITY_CFG_STRU));

    ulLength = 0;

    /* �Ȼ�ȡNV�ĳ��� */
    (VOS_VOID)NV_GetLength(en_NV_Item_Close_SMS_Capability_Config, &ulLength);

    if (ulLength > sizeof(stCloseSmsCapabilityCfg))
    {
        MN_ERR_LOG("MN_MSG_CloseSmsCapabilityFeatureInit():WARNING: en_NV_Item_Close_SMS_Capability_Config length Error");
        return;
    }

    ulRet = NV_Read(en_NV_Item_Close_SMS_Capability_Config,
                   &stCloseSmsCapabilityCfg,
                    ulLength);

    f_stMnMsgCloseSmsCapabilityMsg.ucActFlg = stCloseSmsCapabilityCfg.ucActFlg;

    /* ��ȡ�رն��Ŷ���NVʧ��,Ĭ�ϲ��رն��Ź��� */
    if (NV_OK != ulRet)
    {
        f_stMnMsgCloseSmsCapabilityMsg.ucActFlg = MN_MSG_NVIM_ITEM_INACTIVE;

        MN_ERR_LOG("MN_MSG_CloseSmsCapabilityFeatureInit: Read en_NV_Item_CLOSE_SMS_Capability_Config Failed");
    }

    return;
}


/*****************************************************************************
 �� �� ��  : MN_MSG_SetCloseSMSFeature
 ��������  : ���ö��Źرչ������ñ��
 �������  : VOS_UINT8 ucActFlg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MN_MSG_SetCloseSMSFeature(VOS_UINT8 ucActFlg)
{
    f_stMnMsgCloseSmsCapabilityMsg.ucActFlg = ucActFlg;
}


/*****************************************************************************
 �� �� ��  : MN_MSG_GetMtCustomizeInfo
 ��������  : ��ȡ���Ž�����Ӫ�̶�������
 �������  : MN_MSG_MT_CUSTOMIZE_ENUM_UINT8 *penMtCustomize  ���Ž�����Ӫ�̶�������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��8��
    ��    ��   : f62575
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��12��11��
    ��    ��   : L00171473
    �޸�����   : DTS201212110930, TQE����
*****************************************************************************/
VOS_VOID MN_MSG_GetMtCustomizeInfo(MN_MSG_MT_CUSTOMIZE_ENUM_UINT8 *penMtCustomize)
{
    VOS_UINT32                          ulRet;
    MN_MSG_MT_CUSTOMIZE_INFO_STRU       stMtCustomize;


    PS_MEM_SET(&stMtCustomize, 0x00, sizeof(stMtCustomize));

    *penMtCustomize = MN_MSG_MT_CUSTOMIZE_NONE;

    ulRet = NV_Read(en_NV_Item_SMS_MT_CUSTOMIZE_INFO,
                    &stMtCustomize,
                    sizeof(stMtCustomize));
    if (NV_OK != ulRet)
    {
        MN_WARN_LOG("MN_MSG_GetMtCustomizeInfo: Fail to read ");
        return;
    }

    if (MN_MSG_NVIM_ITEM_ACTIVE == stMtCustomize.ucActFlag)
    {
        *penMtCustomize = stMtCustomize.enMtCustomize;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_UpdateMemExceedFlag
 ��������  : ���¶��Ŵ洢�����־
 �������  : MN_MSG_MEM_FLAG_ENUM_U8 enMemCapExcNotFlag  �洢�����־
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��10��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_MSG_UpdateMemExceedFlag(MN_MSG_MEM_FLAG_ENUM_U8 enMemCapExcNotFlag)
{
    MN_MSG_SMSS_INFO_STRU               stSmssInfo;
    VOS_UINT32                          ulRet;
    
    PS_MEM_SET(&stSmssInfo, 0, sizeof(MN_MSG_SMSS_INFO_STRU));

    ulRet = MN_MSG_ReadSmssInfo(&stSmssInfo);
    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("MN_MSG_UpdateMemExceedFlag: fail to MN_MSG_ReadSmssInfo. ");
        return;
    }

    if (enMemCapExcNotFlag != stSmssInfo.enMemCapExcNotFlag)
    {
        stSmssInfo.enMemCapExcNotFlag = enMemCapExcNotFlag;
        MN_MSG_WriteSmssFile(&stSmssInfo);
    }

    return;
}


/*****************************************************************************
 �� �� ��  : MN_MSG_SetTpRd
 ��������  : ��λ����ʵ����SUBMIT��Ϣ��TP-RD
 �������  : MN_MSG_MO_ENTITY_STRU *pstMoEntity ����ʵ�����ݽṹ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��10��
    ��    ��   : f62575
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_MSG_SetTpRd(MN_MSG_MO_ENTITY_STRU *pstMoEntity)
{
    VOS_UINT32                          ulPos;
    VOS_UINT8                           ulRpOaLength;
    VOS_UINT8                           ulRpDaLength;

    /* ��ȡTP-RD��λ�� */
    ulPos = 0;

    /* RP��MESSGGE TYPE */
    ulPos++;

    /* RP��RP-MR */
    ulPos++;

    /* RP��RP-OA */
    ulRpOaLength = pstMoEntity->aucRpDataInfo[ulPos];
    ulPos++;
    ulPos       += ulRpOaLength;

    /* RP��RP-DA */
    ulRpDaLength = pstMoEntity->aucRpDataInfo[ulPos];
    ulPos++;
    ulPos       += ulRpDaLength;

    /* RP��RP-USERDATA length */
    ulPos++;

    MN_MSG_EncodeTpRd(VOS_TRUE, &pstMoEntity->aucRpDataInfo[ulPos]);

    return;
}

/*****************************************************************************
 �� �� ��  : MN_MSG_IsProtocolSendDomain
 ��������  : �ж��Ƿ�Э��ķ������Ͷ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE   ��Э��ķ������Ͷ���
             VOS_FALSE  ����Э��ķ������Ͷ��ţ�ѡ�������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��12��08��
    ��    ��   : ��ӳ��/f62575
    �޸�����   : DTS2012123101285,�����ɺ���
  2.��    ��   : 2013��05��20��
    ��    ��   : m00217266
    �޸�����   : nv����
*****************************************************************************/
VOS_UINT32 MN_MSG_IsProtocolSendDomain(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    TAF_NVIM_SMS_SERVICE_PARA_STRU  stSmsSrvParam;

    ulRet = NV_Read(en_NV_Item_SMS_SERVICE_Para, &stSmsSrvParam, MN_MSG_SRV_PARAM_LEN);
    if (NV_OK != ulRet)
    {
        MN_ERR_LOG("MN_MSG_IsProtocolSendDomain: Read Service Parm From Nvim Failed");
        return VOS_FALSE;
    }

    if (MN_MSG_MO_DOMAIN_CUSTOMIZE_PROTOCOL == (stSmsSrvParam.aucSmsServicePara)[MN_MSG_SRV_MO_DOMAIN_PROTOCOL_OFFSET])
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MSG_RcvMmaCsServiceChangeNotify
 ��������  : MSG�յ�MMA CS��������������Ϣ�Ĵ���
 �������  : pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MSG_RcvMmaCsServiceChangeNotify(
    struct MsgCB                       *pstMsg
)
{
    MMA_MSG_CS_SERVICE_IND             *pstCsServInd = VOS_NULL_PTR;
    VOS_UINT8                           ucUsimtatus;
    MN_MSG_USIM_POWER_STATE_ENUM_U8     enPowerState;

    pstCsServInd    = (MMA_MSG_CS_SERVICE_IND*)pstMsg;
    ucUsimtatus     = TAF_MSG_GetUsimStatus();
    MN_MSG_GetUsimPowerState(&enPowerState);

    /* �������ڣ�����Ҫ���¶���������USIM�ļ� */
    if (MN_MSG_SIM_NOT_EXIST == ucUsimtatus)
    {
        return;
    }

    if (TAF_CS_OFF == pstCsServInd->enCSState)
    {
        /* CS������������ʱ����Ϊ���Ź��ܹر� */
        MN_MSG_SetCloseSMSFeature(MN_MSG_NVIM_ITEM_ACTIVE);
    }
    else
    {
        /* CS����������ʱ����Ҫ���¶���NV,��NV��ֵΪ׼ */
        MN_MSG_CloseSmsCapabilityFeatureInit();

        /* ͬ��USIM�ļ���ͬ��USIM�ļ�����˳��ģ��ȶ�EF_SMS_SMSS_ID��
           �յ��ظ��󣬻���MSG_ProcEfSmssGetFileRsp�и���һ���ļ����Ͷ��ļ�����
           Ϊ�˱����ظ���ʼ������Ҫ���ϵ������ʱ��ͬ��USIM�ļ� */
        if (MN_MSG_USIM_POWER_ON == enPowerState)
        {
            if (TAF_SDC_SIM_TYPE_USIM == TAF_SDC_GetSimType())
            {
                MN_MSG_GetUsimParmReq(USIMM_USIM_EFSMSS_ID);
            }
            else
            {
                MN_MSG_GetUsimParmReq(USIMM_TELE_EFSMSS_ID);
            }
        }
    }
    return;

}

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 �� �� ��  : MN_MSG_FailErrRecord
 ��������  : ��¼SMS MO�쳣�¼�
 �������  : TAF_MSG_ERROR_ENUM_UINT32 enErrorCode
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��23��
    ��    ��   : s00190137
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MN_MSG_FailErrRecord(TAF_MSG_ERROR_ENUM_UINT32 enErrorCode)
{
    NAS_ERR_LOG_SMS_MO_FAIL_EVENT_STRU                      stSmsMoFailEvent;
    MN_MSG_SEND_DOMAIN_ENUM_U8                              enAvailableSendDomain;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_SMS_FAIL);
    ulIsLogRecord = TAF_SDC_IsErrLogNeedRecord(usLevel);

    /* ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_SMS_MO_FAIL_EVENT_STRU);

    /* ��д���ŷ���ʧ���¼���Ϣ */
    PS_MEM_SET(&stSmsMoFailEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stSmsMoFailEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_TAF),
                                      NAS_ERR_LOG_ALM_SMS_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* ��ȡ��״̬��Ϣ */
    NAS_MMA_OutputUsimInfo(&stSmsMoFailEvent.stUsimInfo);

    /* ��ȡλ����Ϣ */
    NAS_MNTN_OutputPositionInfo(&stSmsMoFailEvent.stPositionInfo);

    MN_MSG_OutputSmsMoFailureInfo(enErrorCode, &stSmsMoFailEvent.stMoFail);

    MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_PS, &enAvailableSendDomain);
    if (MN_MSG_SEND_DOMAIN_PS == enAvailableSendDomain)
    {
        stSmsMoFailEvent.enPsStatus = NAS_MNTN_SEND_DOMAIN_STATUS_AVAILABLE;
    }
    else
    {
        stSmsMoFailEvent.enPsStatus = NAS_MNTN_SEND_DOMAIN_STATUS_UNAVAILABLE;
    }

    MN_MSG_GetCurSendDomain(MN_MSG_SEND_DOMAIN_CS, &enAvailableSendDomain);
    if (MN_MSG_SEND_DOMAIN_CS == enAvailableSendDomain)
    {
        stSmsMoFailEvent.enCsStatus = NAS_MNTN_SEND_DOMAIN_STATUS_AVAILABLE;
    }
    else
    {
        stSmsMoFailEvent.enCsStatus = NAS_MNTN_SEND_DOMAIN_STATUS_UNAVAILABLE;
    }

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = TAF_SDC_PutErrLogRingBuf((VOS_CHAR *)&stSmsMoFailEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_TAF, "MN_MSG_FailErrRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_SMS_FAIL,
                           WUEPS_PID_TAF,
                           (VOS_UINT8 *)&stSmsMoFailEvent,
                           sizeof(stSmsMoFailEvent));
    return;
}
#endif

/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-24, begin */
/*****************************************************************************
 �� �� ��  : TAF_MSG_RcvSpmSmmaRsp
 ��������  : MSG�յ�SPMģ���SMMA RSP��Ϣ�Ĵ���
 �������  : pstMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��4��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��4��13��
    ��    ��   : s00217060
    �޸�����   : DTS2015041007878:ID_TAF_SPM_MSG_REPORT_IND�е�client id����
                 ���ز�����δ���

*****************************************************************************/
VOS_VOID TAF_MSG_RcvSpmSmmaRsp(
    struct MsgCB                       *pstMsg
)
{
    TAF_SPM_SMMA_RSP_STRU              *pstSmmaMsg  = VOS_NULL_PTR;

    pstSmmaMsg = (TAF_SPM_SMMA_RSP_STRU *)pstMsg;

    /* �����ѡ����ΪBUFFER_MESSAGE��SEND_FAIL,��������ΪBUTT,������������ */
    if (TAF_MSG_SIGNALLING_TYPE_BUTT == pstSmmaMsg->enMsgSignallingType)
    {
        return;
    }

    /* ��SMS/IMSA����SMMA��Ϣ */
    (VOS_VOID)MN_MSG_SendSmma(pstSmmaMsg->clientId, pstSmmaMsg->opId, VOS_FALSE, pstSmmaMsg->enMsgSignallingType);

    return;

}
/* Added by s00217060 for VoLTE_PhaseII  ��Ŀ, 2013-09-24, end */

/* TAF_MSG_SendSpmSmmaInd�Ѿ��Ƶ�MnMsgSendSpm.c�ļ��� */
/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

