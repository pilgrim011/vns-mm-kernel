/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcFsmSwitchOn.c
  �� �� ��   : ����
  ��    ��   : luokaihui /l00167671
  ��������   : 2011��03��19��
  ����޸�   :
  ��������   : ��������״̬��������Ϣ�Ĵ�����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��03��19��
    ��    ��   : luokaihui /00167671
    �޸�����   : �����ļ�
  2.��    ��   : 2011��07��13��
    ��    ��   : w00176964
    �޸�����   : GUNAS V7R1 PhaseII �׶ε���

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmSublayerDef.h"
#include "NasMmcCtx.h"
#include "NasMmlLib.h"
#include "NasMmcSndLmm.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndInternalMsg.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndMscc.h"
#include "NasMmcSndOm.h"
#include "NasMmcFsmSwitchOn.h"
#include "NasMmcFsmSwitchOnTbl.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmcProcNvim.h"
#include "NasMmcProcUsim.h"
#include "NasComm.h"
#include "NasMmcProcRegRslt.h"
#include "NasMmcPlmnSelectionStrategy.h"
#include "NasMmcComFunc.h"
#include "NasMmlCtx.h"
#include "NasMmcComFunc.h"

/* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, begin */
#include "MsccMmcInterface.h"
/* Added by l00167671 for �����ϱ�AT�������������C��, 2013-3-30, end */
#include "NasUsimmApi.h"

#include "PsRrmInterface.h"

#include "NasUtranCtrlInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_SWITCHON_C


/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : NAS_MMC_SaveCardStatus_SwitchOn
 ��������  : ��MSCC�·��Ŀ�״̬��Ϣת����MMCʹ�õ���ʽ
             ���浽ȫ�ֱ�����.
 �������  : ucCardStatus��״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2011��04��07��
   ��    ��   : luokaihui / 00167671
   �޸�����   : �����ɺ���
 2.��    ��   : 2011��7��25��
   ��    ��   : w00176964
   �޸�����   : V7R1 PhaseII ȫ�ֱ��� ״̬������
 3.��    ��   : 2013��3��30��
   ��    ��   : l00167671
   �޸�����   : �����ϱ�AT�������������C��
*****************************************************************************/
/* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
VOS_VOID NAS_MMC_SaveCardStatus_SwitchOn(NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enCardStatus)
/* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/
{
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus;

    pstSimStatus    = NAS_MML_GetSimStatus();

    if ( NAS_MSCC_PIF_CARD_STATUS_SIM_PRESENT == enCardStatus )
    {
        pstSimStatus->enSimType = NAS_MML_SIM_TYPE_SIM;

        NAS_MML_SetSimPresentStatus(VOS_TRUE);
    }
    else if ( NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT == enCardStatus)
    {
        pstSimStatus->enSimType = NAS_MML_SIM_TYPE_USIM;

        NAS_MML_SetSimPresentStatus(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetSimPresentStatus(VOS_FALSE);
    }
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SetCsPsAttachAllowFlagAccordingToRegDomain_SwitchOn
 ��������  : ����ע��������CS/PS attach��־
             ���浽ȫ�ֱ�����.
 �������  : enRegDomain -- ע����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��04��21��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_SetCsPsAttachAllowFlagAccordingToRegDomain_SwitchOn(
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8 enRegDomain
)
{
    switch (enRegDomain)
    {
        case NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_PS:
            NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);
            break;

        case NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_CS:
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            break;

        case NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_CS_PS:
            NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            break;

        case NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_NULL:
        default:
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            break;
    }
}

/* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvStartReq_SwitchOn_Init
 ��������  : ����״̬���������������������ļ�����MM/GMM��������
 �������  : ulEventType:��Ϣ����
             pstMsg:TAFMMC_START_REQ��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32: VOS_TRUE, VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��19��
    ��    ��   : luokaihui /l00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��25��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII ȫ�ֱ��� ״̬������
  3.��    ��   : 2011��11��15��
    ��    ��   : zhoujun /40661
    �޸�����   : V3R2�汾RPLMN�жϳ���DTS2011111502732
  4.��    ��   : 2012��4��24��
    ��    ��   : l00171473
    �޸�����   : DTS2012041805606
  5.��    ��   : 2012��6��11��
    ��    ��   : w00166186
    �޸�����   : AT&T&DCM��Ŀ
  6.��    ��   : 2012��6��28��
    ��    ��   : L60609
    �޸�����   : AT&T&DCM:����������뼼��
  7.��    ��   : 2012��8��7��
    ��    ��   : w00167002
    �޸�����   : V7R1C50_GUTL_PhaseII: �����ǰ��ǰ�û�û��ͨ��NV����EHPLMN��
                  ����Ч��EHplmn�ĸ���Ϊ0������IMSI�е�HOME PLMN���µ�EHplmn�б��С�
  8.��    ��   : 2012��10��13��
    ��    ��   : w00167002
    �޸�����   : DTS2012101300714:������ȡHOME PLMNʱ����û�ж�ȡָʾ�����
                 �����ļ�ʱ6FADʱ��Ĭ�ϰ�������ų���Ϊ3λ������������ų���
                 Ϊ2ʱ����;������ڴ���EHplmn���ļ������ڿ��ļ��ж�ȡEHPLMN��
                 ��������ڣ����ڶ�ȡ�ļ�������,�ٶ�ȡEHPLMN��

  9.��    ��   : 2012��10��25��
    ��    ��   : w00167002
    �޸�����   : DTS2012101300714:������ʼ��EHPLMN ��Ϣ���������9102NV/6FD9���ļ�/4F34���ļ���
                 ��ȡ�û����õ�EHPLMN.�ڳ�ʼ��֮ǰ���ж�EHplmn��Ϣ���г�ʼ����
  10.��    ��   : 2013��2��25��
    ��    ��   : w00167002
    �޸�����   : DTS2013022500811:LAST RPLMN rat���Կ�������λ�����û��ʹ
                  ��SYSCFG���õ�˳����RPLMN��
  11.��    ��   : 2013��3��30��
     ��    ��   : l00167671
     �޸�����   : �����ϱ�AT�������������C��

  12.��    ��   : 2014��1��20��
     ��    ��   : w00167002
     �޸�����   : SVLTE��������Ŀ:����ʱ��MMC֪ͨRRM����ע��������Ϣ��������RRM��Դ
                  ����ʱ��RRM��֪ͨ��ע���Modem���ڹػ�ʱ�����ȥע�ᡣ
  13.��    ��   : 2013��3��28��
     ��    ��   : y00176023
     �޸�����   : DSDS GUNAS II��Ŀ:ȡ������ʱ��RRM��ע�ᶯ����Ŀǰ�ķ������յ�NO RF��Ϣע��
  14.��    ��   : 2014��1��28��
     ��    ��   : s00246516
     �޸�����   : L-C��������Ŀ:������ϵͳ��HRPD�Ĵ���

  15.��    ��   : 2014��4��3��
     ��    ��   : s00261364
     �޸�����   : V3R360_eCall��Ŀ
  16.��    ��   : 2014��11��3��
     ��    ��   : z00161729
     �޸�����   : ��������������Ŀ�޸�
  17.��    ��   : 2015��04��21��
    ��    ��    : y00245242
    �޸�����    : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvStartReq_SwitchOn_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMC_START_REQ_STRU              *pstStartReq     = VOS_NULL_PTR;
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity   = VOS_NULL_PTR;
    VOS_UINT8                           aucImsi[NAS_MAX_IMSI_LENGTH];
    VOS_UINT8                           aucPsLocInfo[NAS_MML_PS_LOCI_SIM_FILE_LEN];

    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;



    pstMsIdentity                       = NAS_MML_GetSimMsIdentity();
    pstStartReq                         = (MSCC_MMC_START_REQ_STRU*)pstMsg;
    pstRplmnCfgInfo                     = NAS_MML_GetRplmnCfg();

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-3, begin */
    /* ����ģʽ��Ϣ��mmlȫ�ֱ��� */
#if (FEATURE_ON == FEATURE_ECALL)
    NAS_MML_SetCallMode((NAS_MML_CALL_MODE_ENUM_UINT8)(pstStartReq->enCallMode));
#endif
    /* Added by s00261364 for V3R360_eCall��Ŀ, 2014-4-3, end */



    /* ������뼼�� */
    NAS_MMC_SavePlmnRatPrio_SwitchOn(&(pstStartReq->stPlmnRatPrio));

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
    /* ����֧��3GPP2�Ľ��뼼����MMLȫ�ֱ��� */
    NAS_MMC_Save3Gpp2RatPrio_SwitchOn(&(pstStartReq->st3Gpp2Rat));

    /* ��������ע����Ƶ�MMCȫ�ֱ��� */
    NAS_MMC_SetRegCtrl(pstStartReq->enRegCtrl);

    /* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */

    NAS_MMC_SaveAllowRegDomain_SwitchOn(pstStartReq->enRegDomain);

    /* ����SIM��״̬��Ϣ */
    /* Added by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, begin*/
    NAS_MMC_SaveCardStatus_SwitchOn(pstStartReq->enUsimStatus);

    NAS_MML_InitSimPlmnInfoCtx(NAS_MML_INIT_CTX_STARTUP, NAS_MML_GetSimPlmnInfo());

    /* ���뱣֤SIM����ǰ�����,��Ϊ��ȡNV��Ҫ�жϿ�����,��ȡNV�������Ϣ */
    if ( VOS_TRUE == NAS_MML_GetSimPresentStatus())
    {
        PS_MEM_CPY( pstMsIdentity->aucImsi, pstStartReq->aucImsi, NAS_MAX_IMSI_LENGTH );
    }
    NAS_MMC_ReadNvimInfo_SwitchOn();


    NAS_MMC_LogRplmnCfgInfo();


    /* ��NV�б�����ϴε�IMSI���浽�����������У����ڿ���״̬����IMSI�Ƿ�ı���о� */
    PS_MEM_CPY( NAS_MMC_GetLastImsi_SwitchOn(),
                pstRplmnCfgInfo->aucLastImsi, NAS_MAX_IMSI_LENGTH );

    /* SIM�����ڣ���ȡ����ļ����ļ���ȡ�ɹ����֪ͨMM/GMM��ʼ�� */
    if ( VOS_TRUE == NAS_MML_GetSimPresentStatus())
    {

        /* ������� ���߻���������TIN���� */
        if ( VOS_TRUE == NAS_MMC_IsImsiChange_SwitchOn())
        {
#if (FEATURE_ON == FEATURE_LTE)
            NAS_MMC_WriteTinInfoNvim(NAS_MML_TIN_TYPE_INVALID, pstStartReq->aucImsi);

            NAS_MML_SetTinType(NAS_MML_TIN_TYPE_INVALID);
#else
            NAS_MMC_UpdateLastImsi();
#endif
            /* ����Ps Loc file��Ч*/
            PS_MEM_SET(aucPsLocInfo, (VOS_CHAR)0xFF, sizeof(aucPsLocInfo));

            /* routing area update statusӦ��Ϊ02 */
            aucPsLocInfo[NAS_MML_PS_LOCI_SIM_FILE_LEN-1] = NAS_MML_ROUTING_UPDATE_STATUS_PLMN_NOT_ALLOWED;

            /* LACӦ��ΪOXFFFE*/
            aucPsLocInfo[NAS_MML_PS_LOCI_SIM_FILE_LEN-3] = NAS_MML_LAC_HIGH_BYTE_INVALID;

            NAS_MMC_WritePsLociNvim((NAS_NVIM_PS_LOCI_SIM_FILES_STRU*)aucPsLocInfo);

            /* ��NAS_MMC_WritePsLociNvim���۳��� */
            /* ����PTMSI��������Ч */
            NAS_MEM_CPY_S(NAS_MML_GetUeIdPtmsi(), NAS_MML_MAX_PTMSI_LEN, aucPsLocInfo, NAS_MML_MAX_PTMSI_LEN);

            /* ����PTMSI SIGNATURE��������Ч */
            NAS_MEM_CPY_S(NAS_MML_GetUeIdPtmsiSignature(),
                          NAS_MML_MAX_PTMSI_SIGNATURE_LEN,
                          &aucPsLocInfo[NAS_MML_PTMSI_SIGNATRUE_POS_EFPSLOCI_FILE],
                          NAS_MML_MAX_PTMSI_SIGNATURE_LEN);

            /* ����RAI������ */
            NAS_MMC_UpdateRaiFormPsLociFile(aucPsLocInfo);

            /* ����GPRS��״̬ */
            NAS_MML_SetPsUpdateStatus(aucPsLocInfo[NAS_MML_PS_LOCI_SIM_FILE_LEN - 1]);
        }

        /* ��ȡUSIM�ļ� */
        NAS_MMC_SndUsimReadFileReq();

        /* ����������ʱ����������MMC_READ_AGENT_PRO_TIMER��ʱǰ��ȡ�ļ��ɹ� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_SWITCH_ON_STA_WAIT_SIM_FILES_CNF);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_READ_SIM_FILES,TI_NAS_MMC_WAIT_READ_SIM_FILES_LEN);
    }
    /* SIM�������� */
    else
    {
        /* ������ЧIMSI���� */
        PS_MEM_SET(aucImsi, (VOS_CHAR)0xFF, NAS_MAX_IMSI_LENGTH);


        /* ��MM���Ϳ������� */
        NAS_MMC_SndMmStartReq();
        NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn(NAS_MMC_WAIT_MMCMM_START_CNF);

        /* ��GMM���Ϳ������� */
        NAS_MMC_SndGmmStartReq();
        NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn(NAS_MMC_WAIT_MMCGMM_START_CNF);

        /* ����������ʱ���������ڶ�ʱ����ʱǰ����MM��GMM�ĳ�ʼ���ظ���Ϣ */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_SWITCH_ON_STA_WAIT_MM_START_CNF);

        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_START_CNF,TI_NAS_MMC_WAIT_MM_START_CNF_LEN);
    }

#ifndef __PS_WIN32_RECUR__

    if ( VOS_TRUE == NAS_MML_IsSndOmPcRecurMsgValid() )
    {
        NAS_MMC_SndOutsideFixedContextData();
        NAS_MMC_SndOutsideContextData();
    }

#endif

    NAS_MMC_SetCsPsAttachAllowFlagAccordingToRegDomain_SwitchOn(pstStartReq->enRegDomain);

    return VOS_TRUE;
}
/* Modified by l00167671 for �����ϱ�AT�������������C�� , 2013-04-01, end*/

/*****************************************************************************
 �� �� ��  : NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn_WaitSimFilesCnf
 ��������  : ���������������ȡSIM���ļ��ظ����
 �������  : usEfId - SIM���ļ��ظ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��5��12��
    ��    ��   : z00161729
    �޸�����   : �����ɺ���
  2.��    ��   : 2012��6��20��
    ��    ��   : w00166186
    �޸�����   : AT&T&DCM��Ŀ
  3.��    ��   : 2015��03��09��
    ��    ��   : y00245242
    �޸�����   : ����9����
*****************************************************************************/
VOS_VOID NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn_WaitSimFilesCnf(
    USIMM_DEF_FILEID_ENUM_UINT32        enEfId
)
{
    switch ( enEfId )
    {
        case USIMM_USIM_EFHPLMNwACT_ID:
        case USIMM_GSM_EFHPLMNACT_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_HPLMN_SEL_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFFPLMN_ID:
        case USIMM_GSM_EFFPLMN_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_FORBIDDEN_PLMN_LIST_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFPLMNWACT_ID:
        case USIMM_GSM_EFPLMNWACT_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_UPLMN_SEL_FILE_ID_FLG);
            break;
        case USIMM_USIM_EFOPLMNWACT_ID:
        case USIMM_GSM_EFOPLMNWACT_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_OPLMN_SEL_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFHPPLMN_ID:
        case USIMM_GSM_EFHPLMN_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_HPLMN_PERI_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFAD_ID:
        case USIMM_GSM_EFAD_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_MNC_LENGTH_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFLOCI_ID:
        case USIMM_GSM_EFLOCI_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_CS_LOC_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFKEYS_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_CS_CKIK_FILE_ID_FLG);
            break;

        /* ���Ӷ�SIM���е�cskc�ļ���ȡ */
        case USIMM_GSM_EFKC_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_CS_KC_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFKEYSPS_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_PS_KEY_FILE_ID_FLG);
            break;

        /* ���Ӷ�SIM���е�PSkc�ļ���ȡ���� */
        case USIMM_GSM_EFKCGPRS_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_PS_KC_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFPSLOCI_ID:
        case USIMM_GSM_EFLOCIGPRS_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_PS_LOC_FILE_ID_FLG);
            break;

        /* ���Ӷ�SIM���е�cskc�ļ���ȡ */
        case USIMM_GSM_EFPLMNSEL_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_PLMN_SEL_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFEHPLMN_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_EHPLMN_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFEHPLMNPI_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_EHPLMNPI_FILE_ID_FLG);
            break;

        case USIMM_USIM_EFLRPLMNSI_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_LRPLMNSI_FILE_ID_FLG);
            break;

        case USIMM_ATTGSM_EFACTINGHPLMN_ID:
        case USIMM_ATTUSIM_EFACTINGHPLMN_ID:
            NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn(NAS_MML_READ_ACTING_HPLMN_FILE_ID_FLG);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn_WaitSimFilesCnf:WARNING: File Id Abnormal");
            break;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvUsimGetFileRsp_SwitchOn_WaitSimFilesCnf
 ��������  : ����USIM�Ķ��ļ�ȷ����Ϣ
 �������  : ulEventType:��Ϣ����
             pstMst:��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32: VOS_TRUE��VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��19��
    ��    ��   : luokaihui /l00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��25��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII ȫ�ֱ��� ״̬������
  3.��    ��   : 2012��4��12��
    ��    ��   : w00176964
    �޸�����   : DTS2012051600755:NAS_MMC_RcvAgentUsimReadFileCnf������
                 Ԥ�����յ�usim refresh��ϢҲ����ã����ܵ���switch on״̬�������ĺ���
  4.��    ��   : 2012��6��4��
    ��    ��   : l00130025
    �޸�����   : DTS2012052908019:LastRplmnRatFlag������ʱ��LastRplmnRat����д�����¿���ѡȡ��Rplmn����

  5.��    ��   : 2012��10��13��
    ��    ��   : w00167002
    �޸�����   : DTS2012101300714:������ȡHOME PLMNʱ����û�ж�ȡָʾ�����
                 �����ļ�ʱ6FADʱ��Ĭ�ϰ�������ų���Ϊ3λ������������ų���
                 Ϊ2ʱ����
  6.��    ��   : 2013��04��24��
    ��    ��   : l65478
    �޸�����   : DTS2013040209717:����SIM�����Ҵ���RPLMNʱ,פ���ٶ���

  7.��    ��   : 2015��03��09��
    ��    ��   : y00245242
    �޸�����   : ����9����

  8.��    ��   : 2015��04��14��
    ��    ��   : w00176964
    �޸�����   : CDMA 1x Itetation 10 Modified:֪ͨMSCC��ѡPLMN��Ϣ
  9.��    ��   : 2016��1��20��
    ��    ��   : c00318887
    �޸�����   : DTS2015123110917: usim����GSM����2G��Ȩ��csfb��3G�¼�Ȩ����
 10.��    ��   : 2016��04��10��
    ��    ��   : j00174725
    �޸�����   : DTS2016040901340
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvUsimGetFileRsp_SwitchOn_WaitSimFilesCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU                   *pstRcvMsg           = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo   = VOS_NULL_PTR;

    NAS_MML_SIM_MS_IDENTITY_STRU                           *pstMsIdentity       = VOS_NULL_PTR;
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstSimEhplmnInfo    = VOS_NULL_PTR;
    USIMM_DEF_FILEID_ENUM_UINT32                            enEfId;
    VOS_UINT8                                               aucImsi[NAS_MAX_IMSI_LENGTH];

    NAS_MEM_SET_S(aucImsi, sizeof(aucImsi), 0x0, sizeof(aucImsi));

    pstSimEhplmnInfo                    = NAS_MML_GetSimEhplmnList();
    pstMsIdentity                       = NAS_MML_GetSimMsIdentity();

    pstRcvMsg                           = (PS_USIM_GET_FILE_RSP_FOR_PCLINT_STRU*)pstMsg;
    pstForbidPlmnInfo                   = NAS_MML_GetForbidPlmnInfo();

    NAS_MMC_RcvAgentUsimReadFileCnf(pstRcvMsg);

    if (VOS_OK != USIMM_ChangePathToDefFileID(USIMM_GUTL_APP, pstRcvMsg->stFilePath.ulPathLen, pstRcvMsg->stFilePath.acPath, &enEfId))
    {
        return VOS_FALSE;
    }

    NAS_MMC_ClearWaitSimFilesCnfFlg_SwitchOn_WaitSimFilesCnf(enEfId);

    /* δ������agientҪ�����Ӧ�������ȴ� */
    if (NAS_MML_READ_USIM_FILE_FLG_NULL != NAS_MMC_GetWaitSimFilesCnfFlg_SwitchOn())
    {
        return VOS_TRUE;
    }

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_READ_SIM_FILES);
    
    /* ���ļ���ȡ��ɣ������û�л������жϿ��Ƿ��ڱ���ֻ���ʹ�ù� */
    if (VOS_FALSE == NAS_MMC_IsImsiChange_SwitchOn())
    {
        if (VOS_TRUE == NAS_MMC_IsSimCardUsedOtherUe_SwitchOn())
        {
            NAS_TRACE_HIGH("NAS_MMC_ProcReadUsimFilesComplete_SwitchOn: Card Used Other UE");
            NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_ProcReadUsimFilesComplete_SwitchOn: Card Used Other UE");

            NAS_MEM_CPY_S(aucImsi, sizeof(aucImsi), NAS_MML_GetSimMsIdentity()->aucImsi, NAS_MML_MAX_IMSI_LEN);

            NAS_MMC_WriteTinInfoNvim(NAS_MML_TIN_TYPE_INVALID, aucImsi);

            NAS_MML_SetTinType(NAS_MML_TIN_TYPE_INVALID);
        }
    }
  


    NAS_MMC_InitLastRplmnRat_SwitchOn();



    /* �����ǰ��EHplmn�ĸ���Ϊ0��������Ҫ����ȡIMSI�е�HOME PLMN����NV���û�
       ���õ�HOME PLMN */
    if ( 0 == pstSimEhplmnInfo->ucEhPlmnNum)
    {
        NAS_MMC_UpdateEhplmnInfo_SwitchOn(pstMsIdentity->aucImsi);
    }

    /* ֪ͨMSCC��ѡPLMN��Ϣ */
    NAS_MMC_SndMsccPrefPlmnInfoInd(NAS_MSCC_PREF_PLMN_OPLMN);

    if (VOS_FALSE == NAS_MML_Get3GPP2UplmnNotPrefFlg())
    {
        NAS_MMC_SndMsccPrefPlmnInfoInd(NAS_MSCC_PREF_PLMN_UPLMN);
    }

    /* ����֪ͨEHPLMN��Ϣ,������Ҫ��EHPLMN��Ϣδ���ǰ֪ͨ */
    NAS_MMC_SndMsccPrefPlmnInfoInd(NAS_MSCC_PREF_PLMN_HPLMN);

    /* ����HPLMN���뼼�� */
    NAS_MMC_UpdateEhplmnRat();

    /* ���꿨�ļ��󣬸���NV�����û����õ�Forb PLMN��Ϣ����ȫ�ֱ����Ϳ��ļ� */
    NAS_MMC_UpdateForbPlmnInfo_SwitchOn();

    /* ɾ��FPLMN�е���ЧPLMN */
    (VOS_VOID)NAS_MML_DelInvalidPlmnFromList(pstForbidPlmnInfo->ucForbPlmnNum, pstForbidPlmnInfo->astForbPlmnIdList);

    /* ɾ��FPLMN�е�HPLMN */
    NAS_MMC_DelHplmnInFplmn();

    /* ��USIM����2G������2g��Ȩ�����¿�����ucUsimDoneGsmCsAuthFlg ucUsimDoneGsmPsAuthFlg ��Ч��
       �����ڿ���ʱ��Cs PS ��Ȩ�����true�����ڼ�Ȩʱ��CKSN */
    if (VOS_TRUE == NAS_MMC_IsNeedClearCksn_SwitchOn())
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvUsimGetFileRsp_SwitchOn_WaitSimFilesCnf Set UsimDoneGsm Cs PS AuthFlg TO ture");

        NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_TRUE);
        NAS_MML_SetUsimDoneGsmPsAuthFlg(VOS_TRUE);
    }


    /* ��MM���Ϳ������� */
    NAS_MMC_SndMmStartReq();

    NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn(NAS_MMC_WAIT_MMCMM_START_CNF);

    /* ��GMM���Ϳ������� */
    NAS_MMC_SndGmmStartReq();
    NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn(NAS_MMC_WAIT_MMCGMM_START_CNF);

    /*����������ʱ���������ڶ�ʱ����ʱǰ����MM��GMM�ĳ�ʼ���ظ���Ϣ*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_SWITCH_ON_STA_WAIT_MM_START_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_START_CNF,TI_NAS_MMC_WAIT_MM_START_CNF_LEN);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiReadSimFilesExpired_SwitchOn_WaitSimFilesCnf
 ��������  : ��ȡSIM���ļ���ʱ�Ĵ���ֻ��MMC_READ_HPLMN_PERI_FILE_ID(0x6F31)
             ��Ҫ�����⴦��
 �������  : ulEventType:��Ϣ����
             pstMsg:timer�����ĳ�ʱ��Ϣ��ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32: VOS_TRUE��VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��19��
    ��    ��   : luokaihui /l00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��25��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII ȫ�ֱ��� ״̬������
  3.��    ��   : 2012��6��4��
    ��    ��   : l00130025
    �޸�����   : DTS2012052908019:LastRplmnRatFlag������ʱ��LastRplmnRat����д�����¿���ѡȡ��Rplmn����
  4.��    ��   : 2012��10��13��
    ��    ��   : w00167002
    �޸�����   : DTS2012101300714:������ȡHOME PLMNʱ����û�ж�ȡָʾ�����
                 �����ļ�ʱ6FADʱ��Ĭ�ϰ�������ų���Ϊ3λ������������ų���
                 Ϊ2ʱ����
 5.��    ��   : 2016��1��20��
   ��    ��   : c00318887
   �޸�����   : DTS2015123110917: usim����GSM����2G��Ȩ��csfb��3G�¼�Ȩ����
 6.��    ��   : 2016��04��10��
   ��    ��   : j00174725
   �޸�����   : DTS2016040901340   
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiReadSimFilesExpired_SwitchOn_WaitSimFilesCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo   = VOS_NULL_PTR;
    NAS_MML_RPLMN_CFG_INFO_STRU                            *pstRplmnCfgInfo     = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                             *pstPrioRatList      = VOS_NULL_PTR;

    NAS_MML_SIM_MS_IDENTITY_STRU                           *pstMsIdentity       = VOS_NULL_PTR;
    NAS_MML_SIM_EHPLMN_INFO_STRU                           *pstSimEhplmnInfo    = VOS_NULL_PTR;

    VOS_UINT8                                               aucImsi[NAS_MAX_IMSI_LENGTH];

    NAS_MEM_SET_S(aucImsi, sizeof(aucImsi), 0x0, sizeof(aucImsi));
    pstSimEhplmnInfo                    = NAS_MML_GetSimEhplmnList();
    pstMsIdentity                       = NAS_MML_GetSimMsIdentity();

    pstForbidPlmnInfo                   = NAS_MML_GetForbidPlmnInfo();
    pstRplmnCfgInfo                     = NAS_MML_GetRplmnCfg();
    pstPrioRatList                      = NAS_MML_GetMsPrioRatList();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiReadSimFilesExpired_SwitchOn_WaitSimFilesCnf:ENTERED");

    /* δ��ȡ������plmnʱ�䣬ʹ��Ĭ�ϵ�60���� */
    if ( NAS_MML_READ_HPLMN_PERI_FILE_ID_FLG
        == (NAS_MML_READ_HPLMN_PERI_FILE_ID_FLG & NAS_MMC_GetWaitSimFilesCnfFlg_SwitchOn()))
    {
        NAS_MML_SetSimHplmnTimerLen(TI_NAS_MMC_HPLMN_TIMER_DEFAULT_LEN);
    }

    /* ����ȴ�����SIM���ļ���־λ */
    NAS_MMC_ClearAllWaitSimFilesCnfFlg_SwitchOn();


    /* IMSI�ı�ʱ��enLastRplmnRat��Ҫ����ΪSYSCFG���õ�������ȼ��� */
    if ((VOS_TRUE   == NAS_MMC_IsImsiChange_SwitchOn())
     || (NAS_MML_NET_RAT_TYPE_BUTT == pstRplmnCfgInfo->enLastRplmnRat))
    {
        pstRplmnCfgInfo->enLastRplmnRat = pstPrioRatList->aucRatPrio[0];
    }



    /* �����ǰ��EHplmn�ĸ���Ϊ0��������Ҫ����ȡIMSI�е�HOME PLMN����NV���û�
       ���õ�HOME PLMN */
    if ( 0 == pstSimEhplmnInfo->ucEhPlmnNum)
    {
        NAS_MMC_UpdateEhplmnInfo_SwitchOn(pstMsIdentity->aucImsi);
    }

    /* ����HPLMN���뼼�� */
    NAS_MMC_UpdateEhplmnRat();

    /* ���꿨�ļ��󣬸���NV�����û����õ�Forb PLMN��Ϣ����ȫ�ֱ����Ϳ��ļ� */
    NAS_MMC_UpdateForbPlmnInfo_SwitchOn();

    /* ɾ��FPLMN�е���ЧPLMN */
    (VOS_VOID)NAS_MML_DelInvalidPlmnFromList(pstForbidPlmnInfo->ucForbPlmnNum, pstForbidPlmnInfo->astForbPlmnIdList);

    /* ɾ��FPLMN�е�HPLMN */
    NAS_MMC_DelHplmnInFplmn();

    /* ��USIM����2G������2g��Ȩ�����¿�����ucUsimDoneGsmCsAuthFlg ucUsimDoneGsmPsAuthFlg ��Ч��
       �����ڿ���ʱ��Cs PS ��Ȩ�����true�����ڼ�Ȩʱ��CKSN */
    if (VOS_TRUE == NAS_MMC_IsNeedClearCksn_SwitchOn())
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiReadSimFilesExpired_SwitchOn_WaitSimFilesCnf Set UsimDoneGsm Cs PS AuthFlg TO ture");

        NAS_MML_SetUsimDoneGsmCsAuthFlg(VOS_TRUE);
        NAS_MML_SetUsimDoneGsmPsAuthFlg(VOS_TRUE);
    }

    /* ���ļ���ȡ��ɣ������û�л������жϿ��Ƿ��ڱ���ֻ���ʹ�ù� */
    if (VOS_FALSE == NAS_MMC_IsImsiChange_SwitchOn())
    {
        if (VOS_TRUE == NAS_MMC_IsSimCardUsedOtherUe_SwitchOn())
        {
            NAS_TRACE_HIGH("NAS_MMC_RcvTiReadSimFilesExpired_SwitchOn_WaitSimFilesCnf: Card Used Other UE");

            NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiReadSimFilesExpired_SwitchOn_WaitSimFilesCnf: Card Used Other UE");

            NAS_MEM_CPY_S(aucImsi, sizeof(aucImsi), NAS_MML_GetSimMsIdentity()->aucImsi, NAS_MML_MAX_IMSI_LEN);

            NAS_MMC_WriteTinInfoNvim(NAS_MML_TIN_TYPE_INVALID, aucImsi);

            NAS_MML_SetTinType(NAS_MML_TIN_TYPE_INVALID);
        }
    }

    /* ��MM���Ϳ������� */
    NAS_MMC_SndMmStartReq();
    NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn(NAS_MMC_WAIT_MMCMM_START_CNF);

    /* ��GMM���Ϳ������� */
    NAS_MMC_SndGmmStartReq();
    NAS_MMC_SetWaitMmStartCnfFlg_SwitchOn(NAS_MMC_WAIT_MMCGMM_START_CNF);

    /* ����������ʱ���������ڶ�ʱ����ʱǰ����MM��GMM�ĳ�ʼ���ظ���Ϣ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_SWITCH_ON_STA_WAIT_MM_START_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_START_CNF,TI_NAS_MMC_WAIT_MM_START_CNF_LEN);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvMmStartCnf_SwitchOn_WaitMmStartCnf
 ��������  : ����MM����ȷ����Ϣ
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32: VOS_TRUE��VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��19��
    ��    ��   : luokaihui /l00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��25��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII ȫ�ֱ��� ״̬������

  3.��    ��   : 2011��12��19��
    ��    ��   : w00167002
    �޸�����   : DTS2011121202535:TDS����:NAS����ʱ��������㷢�͵Ŀ���˳��Ϊ
                  G->L->W;
                  ���TDS����δ��:���͵Ŀ���˳��Ϊ�ȸ�GUģ���Ϳ�������
                  ��Lģ֧�֣����ٸ�Lģ���Ϳ�������

  4.��    ��   : 2012��8��3��
    ��    ��   : w00167002
    �޸�����   : V7R1C50_GUTL_PhaseII:��ʼ�������㷢�Ϳ������Ⱥ�˳�� :G->L->W,
                  �����㷢�Ϳ�������
  5.��    ��   : 2013��1��7��
    ��    ��   : s00217060
    �޸�����   : for DSDA GUNAS C CORE�����쳣��������жϣ���ӡ�쳣���˳�״̬��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvMmStartCnf_SwitchOn_WaitMmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU        *pstSwitchOnSettingRecord = VOS_NULL_PTR;
    NAS_MMC_ClearMmStartCnfFlg_SwitchOn(NAS_MMC_WAIT_MMCMM_START_CNF);

    /* δ����MM��GMM�Ŀ����ظ���Ϣ,�����ȴ� */
    if (NAS_MMC_WAIT_MMGMM_START_CNF_NULL != NAS_MMC_GetWaitMmStartCnfFlg_SwitchOn())
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MM_START_CNF);


    /* ��ʼ�������㷢�Ϳ������Ⱥ�˳�� :G->L->W */
    NAS_MMC_SetSwitchOnSendingAsOrder_SwitchOn();
    pstSwitchOnSettingRecord            = NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn();

    /* ����˳��������ɺ󣬶��쳣��������ж� */
    /* �쳣������·������Ľ�������Ϊ0����ӡ�쳣����MSCC�ظ�����ʧ�ܣ���״̬�� */
    if (0 == pstSwitchOnSettingRecord->ucTotalSwitchOnRatNum)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmStartCnf_SwitchOn_WaitMmStartCnf,ERROR:Switch On Rat Num 0");

        NAS_TRACE_HIGH("Switch On Rat Num 0!");

        /* ��TAF���Ϳ���ʧ�� */
        NAS_Mmc_SndMsccStartCnf(TAF_FAILURE);

        NAS_MMC_SndSwitchOnRlst(VOS_FALSE);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �����㷢�Ϳ������� */
    NAS_MMC_SndRatModeSwitchOnReq_SwitchOn( NAS_MMC_GetNextSendingRat_SwitchOn() );

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGmmStartCnf_SwitchOn_WaitMmStartCnf
 ��������  : ����GMM����ȷ����Ϣ
 �������  : ulEventType:��Ϣ����
              pstMsg:��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32: VOS_TRUE��VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��19��
    ��    ��   : luokaihui /l00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��25��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII ȫ�ֱ��� ״̬������

  3.��    ��   : 2011��12��19��
    ��    ��   : w00167002
    �޸�����   : DTS2011121202535:TDS����:NAS����ʱ��������㷢�͵Ŀ���˳��Ϊ
                  G->L->W;
                  ���TDS����δ��:���͵Ŀ���˳��Ϊ�ȸ�GUģ���Ϳ�������
                  ��Lģ֧�֣����ٸ�Lģ���Ϳ�������
  4.��    ��   : 2012��8��3��
    ��    ��   : w00167002
    �޸�����   : V7R1C50_GUTL_PhaseII:��ʼ�������㷢�Ϳ������Ⱥ�˳�� :G->L->W,
                  �����㷢�Ϳ�������
  5.��    ��   : 2013��1��7��
    ��    ��   : s00217060
    �޸�����   : for DSDA GUNAS C CORE�����쳣��������жϣ���ӡ�쳣���˳�״̬��
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGmmStartCnf_SwitchOn_WaitMmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SENDING_AS_SWITCH_ON_SEQUENCE_CTRL_STRU        *pstSwitchOnSettingRecord = VOS_NULL_PTR;
    /* ����PID����ȴ�MM����GMM�ı�־ */
    NAS_MMC_ClearMmStartCnfFlg_SwitchOn(NAS_MMC_WAIT_MMCGMM_START_CNF);

    /* δ����MM��GMM�Ŀ����ظ���Ϣ,�����ȴ� */
    if ( NAS_MMC_WAIT_MMGMM_START_CNF_NULL != NAS_MMC_GetWaitMmStartCnfFlg_SwitchOn() )
    {
        return VOS_TRUE;
    }

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MM_START_CNF);


    /* ��ʼ�������㷢�Ϳ������Ⱥ�˳�� :G->L->W */
    NAS_MMC_SetSwitchOnSendingAsOrder_SwitchOn();
    pstSwitchOnSettingRecord            = NAS_MMC_GetSwitchOnSequenceRecord_SwitchOn();
    /* ����˳��������ɺ󣬶��쳣��������ж� */
    /* �쳣������·������Ľ�������Ϊ0����ӡ�쳣����MSCC�ظ�����ʧ�ܣ���״̬�� */
    if (0 == pstSwitchOnSettingRecord->ucTotalSwitchOnRatNum)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvGmmStartCnf_SwitchOn_WaitMmStartCnf,ERROR:Switch On Rat Num 0");

        NAS_TRACE_HIGH("Switch On Rat Num 0!");

        /* ��TAF���Ϳ���ʧ�� */
        NAS_Mmc_SndMsccStartCnf(TAF_FAILURE);

        NAS_MMC_SndSwitchOnRlst(VOS_FALSE);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �����㷢�Ϳ������� */
    NAS_MMC_SndRatModeSwitchOnReq_SwitchOn( NAS_MMC_GetNextSendingRat_SwitchOn() );

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiMmStartCnfExpired_SwitchOn_WaitMmStartCnf
 ��������  : MM/GMM�ػ�ȷ����Ϣ��ʱ����
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32: VOS_TRUE��VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��19��
    ��    ��   : luokaihui /l00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��25��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII ȫ�ֱ��� ״̬������

*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiMmStartCnfExpired_SwitchOn_WaitMmStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiMmStartCnfExpired_SwitchOn_WaitMmStartCnf:ENTERED");

    NAS_TRACE_HIGH("Enter!");

    /* ����ȴ�MM/GMM�����ظ���Ϣ�ı�־λ */
    NAS_MMC_ClearAllWaitMmStartCnfFlg_SwitchOn();

    /* δ�յ�MM��GMM�Ļظ�Ҳ��Ϊ����ʧ�� */
    NAS_Mmc_SndMsccStartCnf(TAF_FAILURE);

    NAS_MMC_SndSwitchOnRlst(VOS_FALSE);

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvGasStartCnf_SwitchOn_WaitGUStartCnf
 ��������  : Gģ����㿪���ظ���Ϣ�Ĵ���
 �������  : RRMM_START_CNF��Ϣ�Ľṹ����ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32: VOS_TRUE��VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��19��
    ��    ��   : luokaihui /l00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��25��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII ȫ�ֱ��� ״̬������
  3.��    ��   : 2011��12��19��
    ��    ��   : w00167002
    �޸�����   : DTS2011121202535:TDS����:NAS����ʱ��������㷢�͵Ŀ���˳��Ϊ
                  G->L->W;
                  ���TDS����δ��:���͵Ŀ���˳��Ϊ�ȸ�GUģ���Ϳ�������
                  ��Lģ֧�֣����ٸ�Lģ���Ϳ�������

  4.��    ��   : 2012��8��4��
    ��    ��   : w00167002
    �޸�����   : V7R1C50_GUTL_PhaseII:���ĺ�����������״̬����������ͬʱ�޸Ŀ���˳��ͳһ�޸�ΪG->L->W;
  5.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ
  6.��    ��   : 2015��1��8��
    ��    ��   : s00217060
    �޸�����   : Service_State_Optimize_PhaseI�޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvGasStartCnf_SwitchOn_WaitGasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_START_CNF_STRU                        *pstRrStartCnfMsg          = VOS_NULL_PTR;

    pstRrStartCnfMsg          = (RRMM_START_CNF_STRU *)pstMsg;

    (VOS_VOID)vos_printf("NAS_MMC_RcvGasStartCnf_SwitchOn_WaitGasStartCnf.ulResult = %d.\n ", pstRrStartCnfMsg->ulResult);

    NAS_TRACE_HIGH("ulResult = %d", pstRrStartCnfMsg->ulResult);

    if (MMC_START_FAILURE == pstRrStartCnfMsg->ulResult)
    {
        /* ��WAS����GAS��һ������ʧ����ֱ��Ǩ�Ƶ��ػ�״̬ */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_START_CNF);

        /* ��TAF���Ϳ���ʧ�� */
        NAS_Mmc_SndMsccStartCnf(TAF_FAILURE);

        NAS_MMC_SndSwitchOnRlst(VOS_FALSE);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }


    /* �յ�GAS�Ŀ����ظ���ֹͣ�ȴ�GAS�ظ��Ķ�ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_START_CNF);

    /* �������δ��ɣ����������һ��ģ���Ϳ������� */
    if ( NAS_MML_NET_RAT_TYPE_BUTT != NAS_MMC_GetNextSendingRat_SwitchOn() )
    {
        /* �����㷢�Ϳ�������:Ŀǰ�����ķ���˳��ΪG->L->W;���յ�Gģ�ĳɹ��ظ������Lģ���Ϳ������� */
        NAS_MMC_SndRatModeSwitchOnReq_SwitchOn( NAS_MMC_GetNextSendingRat_SwitchOn() );
        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
    {
        NAS_MMC_SndAsHplmnReq(WUEPS_PID_WRR);

        NAS_MMC_SndAsHplmnReq(UEPS_PID_GAS);


        /* ������ʱ���жϿ���IMSI�Ƿ��ڽ�ֹ�б����ʼ��IMSI�Ľ�ֹ״̬ */
        NAS_MMC_RcvStartCnf_SwitchOn_InitRatForbidListCfg();

        NAS_MMC_RcvStartCnf_SwitchOn_ProcAsRatCapabilityStatus();

    }

    /* ������ɣ���ʼ���û�ָ����PLMN */
    NAS_MMC_InitUserSpecPlmnId_SwitchOn();

    /* ������ɣ���SIM���е�RPLMN����NV�е�RPLMN */
    NAS_MMC_UpdateNvRplmnWithSimRplmn_SwitchOn();

    /* ������ɣ����µ�ЧPLMN */
    NAS_MMC_UpdateEplmn_SwitchOn();

    /* ������ɣ�����AT�����ϱ� */
    NAS_MMC_SndGasInfoReportReq();

    NAS_MMC_SndWasInfoReportReq();

    /* ֪ͨLMM�ź������ϱ���ʱ���������� */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SndLmmCellSignReportNotify();
#endif

    /* ������ɣ���TAF���ͳɹ���TAFMMC_START_CNF */
    NAS_Mmc_SndMsccStartCnf(TAF_SUCCESS);

    /* ������ɣ���ʼ�������ȼ������б���Ϣ */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  NAS_MMC_GetHighPrioPlmnList());

    NAS_MMC_SndSwitchOnRlst(VOS_TRUE);

    /* ������ɣ��˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvWasStartCnf_SwitchOn_WaitWasStartCnf
 ��������  : Wģ����㿪���ظ���Ϣ�Ĵ���
 �������  : ulEventType: ��Ϣ����,
              pstMsg: RRMM_START_CNF��Ϣ�Ľṹ����ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32: VOS_TRUE��VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��19��
    ��    ��   : luokaihui /l00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��25��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII ȫ�ֱ��� ״̬������
  3.��    ��   : 2011��12��19��
    ��    ��   : w00167002
    �޸�����   : DTS2011121202535:TDS����:NAS����ʱ��������㷢�͵Ŀ���˳��Ϊ
                  G->L->W;
                  ���TDS����δ��:���͵Ŀ���˳��Ϊ�ȸ�GUģ���Ϳ�������
                  ��Lģ֧�֣����ٸ�Lģ���Ϳ�������
  4.��    ��   : 2011��12��31��
    ��    ��   : w00166186
    �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������
  5.��    ��   : 2012��8��4��
    ��    ��   : w00167002
    �޸�����   : V7R1C50_GUTL_PhaseII:���ĺ�����������״̬���������򣬿���˳��ͳһ�޸�ΪG->L->W;
  6.��    ��   : 2013��7��4��
    ��    ��   : z00234330
    �޸�����   : ���ӿ���LOG
  7.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ
  8.��    ��   : 2015��1��8��
    ��    ��   : s00217060
    �޸�����   : Service_State_Optimize_PhaseI�޸�

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvWasStartCnf_SwitchOn_WaitWasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_START_CNF_STRU                        *pstRrStartCnfMsg = VOS_NULL_PTR;

    pstRrStartCnfMsg          = (RRMM_START_CNF_STRU *)pstMsg;

    (VOS_VOID)vos_printf("NAS_MMC_RcvWasStartCnf_SwitchOn_WaitWasStartCnf.ulResult = %d.tick=0x%x\n ", pstRrStartCnfMsg->ulResult,VOS_GetSlice());

    NAS_TRACE_HIGH("%s ulResult = %d",
        (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode()) ? "FDD" : "TDD", pstRrStartCnfMsg->ulResult);

    if (MMC_START_FAILURE == pstRrStartCnfMsg->ulResult)
    {
        /* ��WAS����GAS��һ������ʧ����ֱ��Ǩ�Ƶ��ػ�״̬ */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_START_CNF);

        /* ��TAF���Ϳ���ʧ�� */
        NAS_Mmc_SndMsccStartCnf(TAF_FAILURE);

        NAS_MMC_SndSwitchOnRlst(VOS_FALSE);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }


    /* �յ�WAS�Ŀ����ظ���ֹͣ�ȴ�WAS�ظ��Ķ�ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_START_CNF);

    /* �������δ��ɣ����������һ��ģ���Ϳ������� */
    if ( NAS_MML_NET_RAT_TYPE_BUTT != NAS_MMC_GetNextSendingRat_SwitchOn() )
    {
        /* �����㷢�Ϳ�������:Ŀǰ�����ķ���˳��ΪG->L->W;���յ�Wģ�ĳɹ��ظ������Lģ���Ϳ������� */
        NAS_MMC_SndRatModeSwitchOnReq_SwitchOn( NAS_MMC_GetNextSendingRat_SwitchOn() );
        return VOS_TRUE;
    }


    if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
    {
        NAS_MMC_SndAsHplmnReq(WUEPS_PID_WRR);

        NAS_MMC_SndAsHplmnReq(UEPS_PID_GAS);


        /* ������ʱ���жϿ���IMSI�Ƿ��ڽ�ֹ�б����ʼ��IMSI�Ľ�ֹ״̬ */
        NAS_MMC_RcvStartCnf_SwitchOn_InitRatForbidListCfg();

        NAS_MMC_RcvStartCnf_SwitchOn_ProcAsRatCapabilityStatus();

    }

    /* ������ɣ���SIM���е�RPLMN����NV�е�RPLMN */
    NAS_MMC_UpdateNvRplmnWithSimRplmn_SwitchOn();

    /* ������ɣ���ʼ���û�ָ����PLMN */
    NAS_MMC_InitUserSpecPlmnId_SwitchOn();

    /* ������ɣ����µ�ЧPLMN */
    NAS_MMC_UpdateEplmn_SwitchOn();

    /* ������ɣ�����AT�����ϱ� */
    NAS_MMC_SndWasInfoReportReq();

    NAS_MMC_SndGasInfoReportReq();

    /* ֪ͨLMM�ź������ϱ���ʱ���������� */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SndLmmCellSignReportNotify();
#endif

    /* ������ɣ���TAF���ͳɹ���TAFMMC_START_CNF */
    NAS_Mmc_SndMsccStartCnf(MMC_START_SUCCESS);

    /* �����ɹ�����ʼ�������ȼ������б� */
    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  NAS_MMC_GetHighPrioPlmnList());

    NAS_MMC_SndSwitchOnRlst(VOS_TRUE);

    /* ������ɣ��˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitGasStartCnfExpired_SwitchOn_WaitGasStartCnf
 ��������  : �����Э��ջ��ʼ��ȷ����Ϣ��ʱδ�ظ���Ϊ����ʧ��
 �������  : ulEventType:��Ϣ����
             pstMsg:�����ظ�������Ϣ����ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32: VOS_TRUE��VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��19��
    ��    ��   : luokaihui /l00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��25��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII ȫ�ֱ��� ״̬������
  3.��    ��   : 2012��8��4��
    ��    ��   : w00167002
    �޸�����   : V7R1C50_GUTL_PhaseII:���ĺ�������ɾ����������ظ���ʶ;
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitGasStartCnfExpired_SwitchOn_WaitGasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Enter!");

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasStartCnfExpired_SwitchOn_WaitGasStartCnf:ENTERED");

    /* ��ʱ��Ϊʧ�� */
    NAS_Mmc_SndMsccStartCnf(TAF_FAILURE);

    NAS_MMC_SndSwitchOnRlst(VOS_FALSE);

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiWaitWasStartCnfExpired_SwitchOn_WaitWasStartCnf
 ��������  : WAS�����ظ���ʱ������Ϊ����ʧ��
 �������  : ulEventType:��Ϣ����
             pstMsg:�����ظ�������Ϣ����ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32: VOS_TRUE��VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��4��
    ��    ��   : w00167002
    �޸�����   : V7R1C50_GUTL_PhaseII:��������;
*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiWaitWasStartCnfExpired_SwitchOn_WaitWasStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("%s", (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode()) ? "FDD" : "TDD");

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasStartCnfExpired_SwitchOn_WaitWasStartCnf:ENTERED");

    /* ��ʱ��Ϊʧ�� */
    NAS_Mmc_SndMsccStartCnf(TAF_FAILURE);

    NAS_MMC_SndSwitchOnRlst(VOS_FALSE);

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


#if   (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvLmmStartCnf_SwitchOn_WaitLStartCnf
 ��������  : �յ�Lģ�������ȷ�Ϻ�Ĵ���,����ִ�е��˺���ʱGUģ�Ѿ�
             �ɹ������������յ�Lģ�ĳɹ���Ϣ����Ϊ�����ɹ����յ�Lģ
             �Ŀ���ʧ����Ϣ����Ϊ����ʧ��
 �������  : ulEventType:��Ϣ����
             pstMsg: Lģ�ظ���Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32: VOS_TRUE��VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��19��
    ��    ��   : luokaihui /l00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��25��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII ȫ�ֱ��� ״̬������
  3.��    ��   : 2011��12��19��
    ��    ��   : w00167002
    �޸�����   : DTS2011121202535:TDS����:NAS����ʱ��������㷢�͵Ŀ���˳��Ϊ
                  G->L->W;
                  ���TDS����δ��:���͵Ŀ���˳��Ϊ�ȸ�GUģ���Ϳ�������
                  ��Lģ֧�֣����ٸ�Lģ���Ϳ�������
  4.��    ��   : 2011��12��31��
    ��    ��   : w00166186
    �޸�����   : DTS2011082902017,ON PLMN��ע�ᱻ��,����״̬���ظ�����������
  5.��    ��   : 2012��6��11��
    ��    ��   : w00166186
  6.��    ��   : 2012��7��20��
    ��    ��   : w00167002
    �޸�����   : WUEPS_PID_RRCF����ΪWUEPS_PID_WRR��
  7.��    ��   : 2012��8��4��
    ��    ��   : w00167002
    �޸�����   : V7R1C50_GUTL_PhaseII:����˳��ͳһ�޸�ΪG->L->W;
  8.��    ��   : 2013��7��4��
    ��    ��   : z00234330
    �޸�����   : ���ӿ���LOG
  9.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ
 10.��    ��   : 2015��1��8��
    ��    ��   : s00217060
    �޸�����   : Service_State_Optimize_PhaseI
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmStartCnf_SwitchOn_WaitLStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_START_CNF_STRU                     *pstRrStartCnfMsg          = VOS_NULL_PTR;

    pstRrStartCnfMsg          = (LMM_MMC_START_CNF_STRU *)pstMsg;

    /* ֹͣ������ʱ�����˶�ʱ���ڸ�Lģ����������Ϣʱ���� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_START_CNF);

    (VOS_VOID)vos_printf("NAS_MMC_RcvLmmStartCnf_SwitchOn_WaitLStartCnf.ulResult = %d,tick=0x%x\r\n ", pstRrStartCnfMsg->ulRst,VOS_GetSlice());

    NAS_TRACE_HIGH("ulResult = %d", pstRrStartCnfMsg->ulRst);

    /* L�¿������ɹ����򿪻�ʧ�ܣ��˳�״̬�� */
    if (MMC_LMM_SUCC != pstRrStartCnfMsg->ulRst)
    {
        /* ��TAF����TAFMMC_START_CNF */
        NAS_Mmc_SndMsccStartCnf(TAF_FAILURE);

        NAS_MMC_SndSwitchOnRlst(VOS_FALSE);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �������δ��ɣ����������һ��ģ���Ϳ������� */
    if ( NAS_MML_NET_RAT_TYPE_BUTT != NAS_MMC_GetNextSendingRat_SwitchOn() )
    {
        /* �����㷢�Ϳ�������:Ŀǰ�����ķ���˳��ΪG->L->W;���յ�Lģ�ĳɹ��ظ������Wģ���Ϳ������� */
        NAS_MMC_SndRatModeSwitchOnReq_SwitchOn( NAS_MMC_GetNextSendingRat_SwitchOn() );

        return VOS_TRUE;
    }

    /* ������ɣ���ʼ���û�ָ����PLMN */
    NAS_MMC_InitUserSpecPlmnId_SwitchOn();

    /* ������ɣ���SIM���е�RPLMN����NV�е�RPLMN */
    NAS_MMC_UpdateNvRplmnWithSimRplmn_SwitchOn();

    /* ������ɣ����µ�ЧPLMN */
    NAS_MMC_UpdateEplmn_SwitchOn();

    if (VOS_TRUE == NAS_MML_GetSimPresentStatus())
    {
        NAS_MMC_SndAsHplmnReq(WUEPS_PID_WRR);

        NAS_MMC_SndAsHplmnReq(UEPS_PID_GAS);


        /* ������ʱ���жϿ���IMSI�Ƿ��ڽ�ֹ�б����ʼ��IMSI�Ľ�ֹ״̬ */
        NAS_MMC_RcvStartCnf_SwitchOn_InitRatForbidListCfg();

        NAS_MMC_RcvStartCnf_SwitchOn_ProcAsRatCapabilityStatus();

    }

    /* ������ɣ�����AT�����ϱ� */
    NAS_MMC_SndGasInfoReportReq();

    NAS_MMC_SndWasInfoReportReq();

    /* ֪ͨLMM�ź������ϱ���ʱ���������� */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_SndLmmCellSignReportNotify();
#endif

    /* ������ɣ���TAF���ͳɹ���TAFMMC_START_CNF */
    NAS_Mmc_SndMsccStartCnf(TAF_SUCCESS);

    NAS_MMC_InitPlmnSelectionList(NAS_MMC_PLMN_SEARCH_SCENE_HIGH_PRIO_PLMN_SEARCH,
                                  VOS_NULL_PTR,
                                  NAS_MMC_GetHighPrioPlmnList());

    NAS_MMC_SndSwitchOnRlst(VOS_TRUE);

    /* ������ɣ��˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvTiLmmStartCnfExpired_SwitchOn_WaitLStartCnf
 ��������  : �ȴ�LMM�����ظ���Ϣ��ʱ��������ʧ��
 �������  : ulEventType:��Ϣ����
             pstMsg:��Ϣ���׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_UINT32: VOS_TRUE��VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��3��19��
    ��    ��   : luokaihui /l00167671
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��25��
    ��    ��   : w00176964
    �޸�����   : V7R1 PhaseII ȫ�ֱ��� ״̬������

*****************************************************************************/
VOS_UINT32  NAS_MMC_RcvTiLmmStartCnfExpired_SwitchOn_WaitLStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Enter!");

    /* ��ʱ��Ϊ����ʧ�� */
    NAS_Mmc_SndMsccStartCnf(TAF_FAILURE);

    NAS_MMC_SndSwitchOnRlst(VOS_FALSE);

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

#endif

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsSimRplmnInNvRplmn_SwitchOn
 ��������  : Sim����Rplmn�Ƿ��ڵ�ǰ֧�ֽ��뼼����NV�� Rplmn��
 �������  : pstSimRplmnId: SIM���е�RPLMN
 �������  : ��
 �� �� ֵ  : VOS_TRUE:NV������SIM������ͬ��RPLMN
             VOS_FALSE:NV��������SIM������ͬ��RPLMN
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��19��
    ��    ��   : z00161729
    �޸�����   : V7R1 phase II�滻ȫ�ֱ����޸�
*****************************************************************************/
VOS_UINT32  NAS_MMC_IsSimRplmnInNvRplmn_SwitchOn(
    NAS_MML_PLMN_ID_STRU               *pstSimRplmnId
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulExistSamePlmn;
    NAS_MML_PLMN_ID_STRU               *pstNVRplmn      = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    pstRplmnCfgInfo         = NAS_MML_GetRplmnCfg();
    ulExistSamePlmn         = VOS_FALSE;

    pstPrioRatList = NAS_MML_GetMsPrioRatList();

    /* �Ե�ǰ֧�ֵ����н��뼼����������м�� */
    pstNVRplmn = &(pstRplmnCfgInfo->stGRplmnInNV);

    for ( i = 0 ; i < pstPrioRatList->ucRatNum ; i++ )
    {
        switch (pstPrioRatList->aucRatPrio[i] )
        {
            case NAS_MML_NET_RAT_TYPE_GSM:
                pstNVRplmn = &(pstRplmnCfgInfo->stGRplmnInNV);
                break;

            case NAS_MML_NET_RAT_TYPE_WCDMA:
                pstNVRplmn = &(pstRplmnCfgInfo->stWRplmnInNV);
                break;

            default:
                continue;
        }

        /* �ж�NV�и���Rplmn�Ƿ�����SimRplmn��ͬ�ģ�
        ����ͬ�ģ�����ʹ�ø�NV�е�Rplmn;����ͳһʹ�� Sim����Rplmn*/
        if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(pstNVRplmn, pstSimRplmnId))
        {
            ulExistSamePlmn = VOS_TRUE;
        }

    }

    return ulExistSamePlmn;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateNvRplmnWithSimRplmn_SwitchOn
 ��������  : ֧��ģʽ�е�NV�е�����Rplmn�� Sim���е�Rplmn����ͬ
             ��ǰ����Ϊֻ֧�ֵ���Rplmn
             ��NV�е� rplmn��Чʱ,
             ʹ��Sim���е�Plmn����NV���Ӧ��Rplmn
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��7��18��
    ��    ��   : z00161729
    �޸�����   : V7R1 phase II����ȫ�ֱ����޸�

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateNvRplmnWithSimRplmn_SwitchOn(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstPrioRatList  = VOS_NULL_PTR;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU               *pstNVRplmn      = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stRplmn;
    VOS_UINT32                          ulExistSamePlmn;
    VOS_UINT32                          ulRplmnExistFlg;
    VOS_UINT32                          i;

    pstPrioRatList          = NAS_MML_GetMsPrioRatList();
    pstRplmnCfgInfo         = NAS_MML_GetRplmnCfg();
    ulRplmnExistFlg         = VOS_TRUE;

#if (FEATURE_ON == FEATURE_LTE)
    /* ��֧�ֵ�Rplmn,��lastRplmnRatΪLte,����Ҫʹ��LRplmn����stGRplmnInNV,stWRplmnInNV,����ʹ��GU Rplmn����NV */
    if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetLastRplmnRat())
    && (VOS_FALSE  == pstRplmnCfgInfo->ucMultiRATRplmnFlg))
    {
        ulRplmnExistFlg = NAS_MML_GetLteRPlmn(&stRplmn);
    }
    else
#endif
    {
        ulRplmnExistFlg = NAS_MML_GetGURPlmn(&stRplmn);
    }

    /* ��ȡRPLMNʧ�ܻ���IMSI�ı�ʱ�����NV�е�RPLMN��Ϣ */
    if ((VOS_TRUE   == NAS_MMC_IsImsiChange_SwitchOn())
     || (VOS_FALSE  == ulRplmnExistFlg))
    {
        pstRplmnCfgInfo->stGRplmnInNV.ulMcc = NAS_MML_INVALID_MCC;
        pstRplmnCfgInfo->stGRplmnInNV.ulMnc = NAS_MML_INVALID_MNC;
        pstRplmnCfgInfo->stWRplmnInNV.ulMcc = NAS_MML_INVALID_MCC;
        pstRplmnCfgInfo->stWRplmnInNV.ulMnc = NAS_MML_INVALID_MNC;

        return;
    }

    /* Sim����Rplmn�Ƿ���NV�е�Plmn��  */
    ulExistSamePlmn = NAS_MMC_IsSimRplmnInNvRplmn_SwitchOn(&stRplmn);

    /* �Ե�ǰ֧�ֵ����н��뼼��������������� */
    pstNVRplmn = &(pstRplmnCfgInfo->stGRplmnInNV);

    for ( i = 0 ; i < pstPrioRatList->ucRatNum; i++ )
    {
        switch (pstPrioRatList->aucRatPrio[i] )
        {
            case NAS_MML_NET_RAT_TYPE_GSM:
                pstNVRplmn = &(pstRplmnCfgInfo->stGRplmnInNV);
                break;

            case NAS_MML_NET_RAT_TYPE_WCDMA:
                pstNVRplmn = &(pstRplmnCfgInfo->stWRplmnInNV);
                break;

            default:
                /* Lģʹ��EPSLoci�е����ݣ�����Ҫ�ٶ��⴦�� */
                continue;
        }

        /* NV��Rplmn ��Ч��ǰֻ֧��һ��Rplmn������NV��Rplmn�뿨��Plmn��ͬ����ʹ��Sim�е�Rplmn */
        if ((VOS_FALSE  == NAS_MML_IsPlmnIdValid(pstNVRplmn))
         || (VOS_FALSE  == ulExistSamePlmn)
         || (VOS_FALSE  == pstRplmnCfgInfo->ucMultiRATRplmnFlg))
        {
            pstNVRplmn->ulMcc = stRplmn.ulMcc;
            pstNVRplmn->ulMnc = stRplmn.ulMnc;
        }

    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateLastRplmnRat_LastRplmnRatInvalid_SwitchOn
 ��������  : last rplmn rat��Чʱ����last rplmn rate
 �������  : pstLasRplmn         :last rplmn��Ϣ
             ucLastRplmnExistFlag:last rplmn�Ƿ���ڱ�ʶ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��5��16��
    ��    ��   : z00161729
    �޸�����   : DTS2014051500129:ʹ����ͨ�����ֶ���vodafoneע��ɹ����ػ�����һ�ű�����Ӫ��EE�Ŀ�����ע��EE���ٹػ���
                 �ٻ���֮ǰ��ͨ��������������ע�����磬��ȡl��rplmn������û�л�ȡgu��rplmn
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateLastRplmnRat_LastRplmnRatInvalid_SwitchOn(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstLasRplmn,
    VOS_UINT8                           ucLastRplmnExistFlag
)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatOrder     = VOS_NULL_PTR;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();
    pstRatOrder     = NAS_MML_GetMsPrioRatList();

    /* ���������Ὣlast rplmn rat����Ϊbutt����ȡ��rplmn����Ҫ����last rplmn ratȫ�ֱ��� */
    if (NAS_MML_NET_RAT_TYPE_BUTT != pstRplmnCfgInfo->enLastRplmnRat)
    {
        return;
    }

    /* ���l��gu��rplmn�������ڣ���last rplmn rat����Ϊsyscfg���õ�������ȼ����� */
    if (VOS_FALSE == ucLastRplmnExistFlag)
    {
        pstRplmnCfgInfo->enLastRplmnRat = pstRatOrder->aucRatPrio[0];
        return;
    }

#if   (FEATURE_ON == FEATURE_LTE)
    if (NAS_MML_NET_RAT_TYPE_LTE == pstLasRplmn->enRat)
    {
        pstRplmnCfgInfo->enLastRplmnRat = pstLasRplmn->enRat;
        return;
    }
#endif

    if (VOS_TRUE == NAS_MML_IsWcdmaPrioGsm(pstRatOrder))
    {
        pstRplmnCfgInfo->enLastRplmnRat = NAS_MML_NET_RAT_TYPE_WCDMA;
        return;
    }

    pstRplmnCfgInfo->enLastRplmnRat = NAS_MML_NET_RAT_TYPE_GSM;
    return;

}


/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateEplmn_SwitchOn
 ��������  : ���µ�ЧPLMN
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��7��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��8��04��
    ��    ��   : w00176964
    �޸�����   : V7R1 Phase II ȫ�ֱ�������
  3.��    ��   : 2012��10��26��
    ��    ��   : W00176964
    �޸�����   : DTS2012090303157:����EPLMN��Ч���
  4.��    ��   : 2013��1��11��
    ��    ��   : W00176964
    �޸�����   : DTS2013010706662:RPLMN������ʱ����EPLMN

  5.��    ��   : 2014��1��9��
    ��    ��   : w00167002
    �޸�����   : DTS2014010305488:��������EPLMNΪ��Ч���翪��ָ����24005�ɹ���24003ΪEPLMN;
                 �ػ��󿪻���24005ʧ�ܣ�Я��24003�����磬���ʱ��Ҳ�ǿ�����24003��
                 ����ע��ġ�
  6.��    ��   : 2014��5��16��
    ��    ��   : z00161729
    �޸�����   : DTS2014051500129:ʹ����ͨ�����ֶ���vodafoneע��ɹ����ػ�����һ�ű�����Ӫ��EE�Ŀ�����ע��EE���ٹػ���
                 �ٻ���֮ǰ��ͨ��������������ע�����磬��ȡl��rplmn������û�л�ȡgu��rplmn
*****************************************************************************/
VOS_VOID NAS_MMC_UpdateEplmn_SwitchOn(VOS_VOID)
{
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnList    = VOS_NULL_PTR;

    NAS_MML_PLMN_WITH_RAT_STRU          stTmpPlmn;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo     = VOS_NULL_PTR;

    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEHPlmnInfo   = VOS_NULL_PTR;

    pstEplmnList           = NAS_MML_GetEquPlmnList();


    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /* �����ϴιػ��Ľ��뼼��������ȡ�Ǹ�ģʽ��RPLMN��������ֱ�ӷ��� */
    if  (VOS_FALSE == NAS_MMC_GetLastRplmn_SwitchOn(&stTmpPlmn))
    {
        if (NAS_MML_NET_RAT_TYPE_BUTT == pstRplmnCfgInfo->enLastRplmnRat)
        {
            NAS_MMC_UpdateLastRplmnRat_LastRplmnRatInvalid_SwitchOn(&stTmpPlmn, VOS_FALSE);
        }

        /* EPS/MM/GMM��update status��Чʱ,EPLMN��Ҫ��дһ��ֵ��֤����ע��ʧ��ʱ
           ��RRC����EPLMN������Ϊ0���߲��� */

        pstEHPlmnInfo       = NAS_MML_GetSimEhplmnList();

        pstEplmnList->ucEquPlmnNum = 1;
        pstEplmnList->astEquPlmnAddr[0].ulMcc = pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMcc;
        pstEplmnList->astEquPlmnAddr[0].ulMnc = pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId.ulMnc;

        /* ����EPLMN��Ч��� */
        NAS_MML_SetEplmnValidFlg(VOS_TRUE);

        return;
    }

    if (NAS_MML_NET_RAT_TYPE_BUTT == pstRplmnCfgInfo->enLastRplmnRat)
    {
        NAS_MMC_UpdateLastRplmnRat_LastRplmnRatInvalid_SwitchOn(&stTmpPlmn, VOS_TRUE);
    }

    /* ���RPLMN����EPLMN�У�����EPLMN�б� */
    if ((pstEplmnList->astEquPlmnAddr[0].ulMcc != stTmpPlmn.stPlmnId.ulMcc)
     || (pstEplmnList->astEquPlmnAddr[0].ulMnc != stTmpPlmn.stPlmnId.ulMnc))
    {
        pstEplmnList->ucEquPlmnNum = 1;
        pstEplmnList->astEquPlmnAddr[0].ulMcc = stTmpPlmn.stPlmnId.ulMcc;
        pstEplmnList->astEquPlmnAddr[0].ulMnc = stTmpPlmn.stPlmnId.ulMnc;


    }

    /* ����EPLMN��Ч��� */
    NAS_MML_SetEplmnValidFlg(VOS_TRUE);


    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitUserSpecPlmnId_SwitchOn
 ��������  : ��ʼ���û�ָ��������PLMN ID
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��5��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2011��9��6��
    ��    ��   : s46746
    �޸�����   : ͬ��V3R1�汾���ⵥDTS2011042201907
  3.��    ��   : 2012��6��27��
    ��    ��   : w00176964
    �޸�����   : DTS2012062100495:��LINUX��һ��_NETWORK��ע��һ������������֮��,��������,
                 �����Զ�ע����ԭ���Ѿ�ע�������
  4.��    ��   : 2012��11��18��
    ��    ��   : w00176964
    �޸�����   : DTS2012110206503:USIM�������ڲ���ʼ���û�ָ����PLMN ID
  5.��    ��   : 2014��5��16��
    ��    ��   : z00161729
    �޸�����   : DTS2014051500129:ʹ����ͨ�����ֶ���vodafoneע��ɹ����ػ�����һ�ű�����Ӫ��EE�Ŀ�����ע��EE���ٹػ���
               �ٻ���֮ǰ��ͨ��������������ע�����磬��ȡl��rplmn������û�л�ȡgu��rplmn
*****************************************************************************/
VOS_VOID NAS_MMC_InitUserSpecPlmnId_SwitchOn(VOS_VOID)
{
    NAS_MML_PLMN_WITH_RAT_STRU          stUserPlmn;
    NAS_MML_PLMN_WITH_RAT_STRU         *pstUserPlmnInfo     = VOS_NULL_PTR;
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstEHPlmnInfo       = VOS_NULL_PTR;
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo     = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stGuRplmn;

    VOS_UINT8                           ucLastRplmnExistFlag;

    ucLastRplmnExistFlag = VOS_TRUE;

    /* �ֶ�ģʽ�����û�ָ����PLMN ID */
    if ( NAS_MMC_PLMN_SELECTION_MODE_MANUAL != NAS_MMC_GetPlmnSelectionMode())
    {
        NAS_INFO_LOG(WUEPS_PID_MMC, "NAS_MMC_InitUserSpecPlmnId_SwitchOn:Need not set!");

        return;
    }

    /* SIM�������ڻ����PIN��,ֱ�ӷ��� */
    if (VOS_FALSE == NAS_MML_GetSimPresentStatus())
    {
        return;
    }

    pstUserPlmnInfo     = NAS_MMC_GetUserSpecPlmnId();

    pstRplmnCfgInfo     = NAS_MML_GetRplmnCfg();

    /* �����ϴιػ��Ľ��뼼��,��ȡRPLMN,��������ʹ��HPLMN */
    if (VOS_FALSE == NAS_MMC_GetLastRplmn_SwitchOn(&stUserPlmn))
    {
        ucLastRplmnExistFlag = VOS_FALSE;

        /* ��ȡRPLMNʧ��ʱ,LastRATΪGUʱֱ�ӻ�ȡEFLOCI�ļ��е�PLMN ID */
        if ((VOS_TRUE   == NAS_MML_GetEfLociPlmn(&stGuRplmn))
         && ((NAS_MML_NET_RAT_TYPE_WCDMA == pstRplmnCfgInfo->enLastRplmnRat)
          || (NAS_MML_NET_RAT_TYPE_GSM   == pstRplmnCfgInfo->enLastRplmnRat)))
        {
            stUserPlmn.stPlmnId = stGuRplmn;
            stUserPlmn.enRat    = NAS_MML_NET_RAT_TYPE_WCDMA;
            ucLastRplmnExistFlag = VOS_TRUE;
        }
        else
        {
            pstEHPlmnInfo       = NAS_MML_GetSimEhplmnList();
            stUserPlmn.stPlmnId = pstEHPlmnInfo->astEhPlmnInfo[0].stPlmnId;
        }
    }

    if (NAS_MML_NET_RAT_TYPE_BUTT == pstRplmnCfgInfo->enLastRplmnRat)
    {
        NAS_MMC_UpdateLastRplmnRat_LastRplmnRatInvalid_SwitchOn(&stUserPlmn, ucLastRplmnExistFlag);
    }

    stUserPlmn.enRat    = pstRplmnCfgInfo->enLastRplmnRat;

    /* ����ʱ��ָ������֮ǰ�������������ΪRPLMN, RPLMN������������ΪHPLMN */
    NAS_MMC_SetUserReselPlmnId(&(stUserPlmn.stPlmnId), stUserPlmn.enRat);

    /* �ϴα�����û�ָ����PLMN ID��Ч */
    if ( VOS_TRUE == NAS_MML_IsPlmnIdValid(&(pstUserPlmnInfo->stPlmnId)))
    {
        return;
    }

    NAS_MMC_SetUserSpecPlmnId(&stUserPlmn);

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetLastRplmn_SwitchOn
 ��������  : ��ȡ�ϴιػ�ʱע��ɹ���PLMN ID
 �������  : ��
 �������  : pstLasRplmn:�ϴιػ�ʱע��ɹ���PLMN ID
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��8��5��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��5��16��
    ��    ��   : z00161729
    �޸�����   : DTS2014051500129:ʹ����ͨ�����ֶ���vodafoneע��ɹ����ػ�����һ�ű�����Ӫ��EE�Ŀ�����ע��EE���ٹػ���
               �ٻ���֮ǰ��ͨ��������������ע�����磬��ȡl��rplmn������û�л�ȡgu��rplmn
*****************************************************************************/
VOS_UINT32  NAS_MMC_GetLastRplmn_SwitchOn(
    NAS_MML_PLMN_WITH_RAT_STRU         *pstLasRplmn
)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo     = VOS_NULL_PTR;
    NAS_MML_PLMN_ID_STRU                stGuRplmn;
    VOS_UINT32                          ulGuRplmnExistFlg;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_PLMN_ID_STRU                stLRplmn;
    VOS_UINT32                          ulLRplmnExistFlg;
#endif

    pstRplmnCfgInfo     = NAS_MML_GetRplmnCfg();

    /* �����ϴιػ��Ľ��뼼��������ȡ�Ǹ�ģʽ��RPLMN */
    switch(pstRplmnCfgInfo->enLastRplmnRat)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* ��ȡGU��RPLMN */
            ulGuRplmnExistFlg   = NAS_MML_GetGURPlmn(&stGuRplmn);

            if (VOS_FALSE == ulGuRplmnExistFlg)
            {
                return VOS_FALSE;
            }

            pstLasRplmn->stPlmnId.ulMcc = stGuRplmn.ulMcc;
            pstLasRplmn->stPlmnId.ulMnc = stGuRplmn.ulMnc;
            pstLasRplmn->enRat          = pstRplmnCfgInfo->enLastRplmnRat;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* ��ȡL��RPLMN */
            ulLRplmnExistFlg    = NAS_MML_GetLteRPlmn(&stLRplmn);

            if (VOS_FALSE == ulLRplmnExistFlg)
            {
                return VOS_FALSE;
            }

            pstLasRplmn->stPlmnId.ulMcc = stLRplmn.ulMcc;
            pstLasRplmn->stPlmnId.ulMnc = stLRplmn.ulMnc;
            pstLasRplmn->enRat          = pstRplmnCfgInfo->enLastRplmnRat;
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_BUTT:
#if (FEATURE_ON == FEATURE_LTE)
            /* ��ȡL��RPLMN */
            ulLRplmnExistFlg    = NAS_MML_GetLteRPlmn(&stLRplmn);

            if (VOS_TRUE == ulLRplmnExistFlg)
            {
                pstLasRplmn->stPlmnId.ulMcc = stLRplmn.ulMcc;
                pstLasRplmn->stPlmnId.ulMnc = stLRplmn.ulMnc;
                pstLasRplmn->enRat          = NAS_MML_NET_RAT_TYPE_LTE;

                return VOS_TRUE;
            }
#endif
            /* ��ȡGU��RPLMN */
            ulGuRplmnExistFlg   = NAS_MML_GetGURPlmn(&stGuRplmn);

            if (VOS_FALSE == ulGuRplmnExistFlg)
            {
                return VOS_FALSE;
            }

            pstLasRplmn->stPlmnId.ulMcc = stGuRplmn.ulMcc;
            pstLasRplmn->stPlmnId.ulMnc = stGuRplmn.ulMnc;
            pstLasRplmn->enRat          = NAS_MML_NET_RAT_TYPE_WCDMA;
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_GetLastRplmn_SwitchOn:Unexpected Rat Type!");
            return VOS_FALSE;
    }


    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsImsiChange_SwitchOn
 ��������  : �ж��ϴιػ�ʱ��IMSI��Ŀǰʹ�õ��Ƿ���ͬ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��26��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2012��3��2��
    ��    ��   : z40661
    �޸�����   : DTS2012021703361����ȡlast imsi����

  3.��    ��   : 2013��2��25��
    ��    ��   : w00167002
    �޸�����   : DTS2013022500811:IMSI�ĳ�����ȣ���ӵڶ�λ��ʼ�Ƚ�IMSI��
                  �����Ƿ���ͬ��ԭ���߼�����������û�бȽ�IMSI�����һλ��
                  LAST RPLMN rat���Կ�������λ�����û��ʹ��SYSCFG���õ�˳
                  ����RPLMN,���ڿ���ʱ���Ѿ���LAST IMSI����Ϊ��ǰ��IMSI�ˣ���
                  ���ú����㷵��VOS_TRUE;�޸�Ϊ��last IMSI��Ϣ�����ڿ���״̬
                  �����������С�

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsImsiChange_SwitchOn(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_UINT8                          *pucLastImsi         = VOS_NULL_PTR;
    NAS_MML_SIM_MS_IDENTITY_STRU       *pstMsIdentity       = VOS_NULL_PTR;

    pstMsIdentity       = NAS_MML_GetSimMsIdentity();
    pucLastImsi         = NAS_MMC_GetLastImsi_SwitchOn();


    /* ������ʱ�ж�IMSI���ϴιػ�ǰ��IMSI��ͬʱ��������Ҫ����ȫƵ������ */
    /* ��ȡIMSI���ȣ���IMSI���Ȳ���ʱ����ΪIMSI�����ı� */
    if (pstMsIdentity->aucImsi[0] != pucLastImsi[0])
    {
        return VOS_TRUE;
    }
    else
    {
        /* ����Ҫ�жϳ����Ƿ�Ϸ� */
        if ( pstMsIdentity->aucImsi[0] > NAS_MML_MAX_IMSI_LEN)
        {
            return VOS_TRUE;
        }

        /* IMSI�ĳ�����ȣ���ӵڶ�λ��ʼ�Ƚ�IMSI�������Ƿ���ͬ */
        for (i = 1; i < (pstMsIdentity->aucImsi[0] + 1); i++)
        {
            if (pucLastImsi[i] != pstMsIdentity->aucImsi[i])
            {
                return VOS_TRUE;
            }
        }

    }


    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_IsNeedClearCksn_SwitchOn
 ��������  : ����ʱ���Ƿ���Ҫ���CKSN.
             �����¿���ʱ���ϴο���ʱUSIM����2G������2g��Ȩ��ucUsimDoneGsmCsAuthFlg��Ч�������ڿ���ʱ��CS CKSN����Ч
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE   -- ��Ҫ���CKSN.
             VOS_FALSE  -- ����Ҫ���CKSN.
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��18��
    ��    ��   : c00318887
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_MMC_IsNeedClearCksn_SwitchOn(VOS_VOID)
{
    NAS_MML_SIM_TYPE_ENUM_UINT8         ucSimType;
    VOS_UINT8                           ucUsimGsmAuthNvCfg;
    VOS_UINT32                          ulIsImsiChange;

    ucSimType                           = NAS_MML_GetSimType();
    ulIsImsiChange                      = NAS_MMC_IsImsiChange_SwitchOn();
    ucUsimGsmAuthNvCfg                  = NAS_MML_GetUsimGsmAuthNvCfg();

    if (VOS_FALSE == ulIsImsiChange)
    {
        return VOS_FALSE;
    }

    if (NAS_MML_SIM_TYPE_USIM != ucSimType)
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == ucUsimGsmAuthNvCfg)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvStartCnf_SwitchOn_ProcAsRatCapabilityStatus
 ��������  : �յ�����Confirm��Ϣ�����NV��������GUL�Ƿ��ֹ��������ֹ�б��·��������
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_RcvStartCnf_SwitchOn_ProcAsRatCapabilityStatus (VOS_VOID)
{
    if (VOS_FALSE == NAS_MML_GetImsiInForbiddenListFlg())
    {
        return;
    }

    NAS_MMC_SndAsRatCapabilityStatusChangeInfo();

    #if (FEATURE_ON == FEATURE_LTE)
    /* ���LTE����ֹ������֪ͨLTE */
    if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE == NAS_MML_GetLteForbiddenStatusFlg())
    {
        NAS_MMC_SndLmmDisableLteNotify(MMC_LMM_DISABLE_LTE_REASON_IMSI_IN_FORBIDDEN_LIST);

        /* ����disable LTE������� */
        NAS_MML_SetLteCapabilityStatus(NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_NOTIFIED_AS);

        NAS_MML_SetDisableLteReason(MMC_LMM_DISABLE_LTE_REASON_IMSI_IN_FORBIDDEN_LIST);
    }
    #endif

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_RcvStartCnf_SwitchOn_InitRatForbidListCfg
 ��������  : �ڿ�����ʱ����ݿ���IMSI��ʼ�����ƽ��뼼����������ȫ�ֱ���
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013��11��01��
   ��    ��   : l00208543
   �޸�����   : �����ɺ���

 2.��    ��   : 2013��11��13��
   ��    ��   : w00167002
   �޸�����   : MNC�ĳ�����Ҫ�ȵ����꿨�ļ�����׼ȷȷ��
*****************************************************************************/
VOS_VOID NAS_MMC_RcvStartCnf_SwitchOn_InitRatForbidListCfg (VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MML_RAT_FORBIDDEN_LIST_STRU    *pstBlackList = VOS_NULL_PTR;

    i            = 0;
    pstBlackList = NAS_MML_GetRatForbiddenListCfg();

    if (VOS_FALSE == NAS_MML_IsImsiInForbiddenList())
    {
        NAS_MML_SetImsiInForbiddenListFlg(VOS_FALSE);
        return;
    }

    /* ��ʼ�����Ƿ��ڽ�ֹ�б��ȫ�ֱ��� */
    NAS_MML_SetImsiInForbiddenListFlg(VOS_TRUE);

    /* ��ʼ��ÿ�����뼼���Ľ�ֹ״̬ */
    for (i = 0; i < pstBlackList->ucForbidRatNum; i++)
    {
        if (NAS_MML_NET_RAT_TYPE_GSM         == pstBlackList->aenForbidRatList[i])
        {
            NAS_MML_SetGsmForbiddenStatusFlg(NAS_MML_RAT_CAPABILITY_STATUS_DISABLE);
        }
        else if (NAS_MML_NET_RAT_TYPE_WCDMA  == pstBlackList->aenForbidRatList[i])
        {
            NAS_MML_SetUtranForbiddenStatusFlg(NAS_MML_RAT_CAPABILITY_STATUS_DISABLE);
        }
        else if (NAS_MML_NET_RAT_TYPE_LTE    == pstBlackList->aenForbidRatList[i])
        {
            /* ���UE֧�ֵĽ��뼼��ΪLTE Only�򲻽�ֹLTE */
            if (VOS_FALSE == NAS_MML_IsLteOnlyMode(NAS_MML_GetMsPrioRatList()))
            {
                NAS_MML_SetLteForbiddenStatusFlg(NAS_MML_RAT_CAPABILITY_STATUS_DISABLE);
            }
        }
        else
        {
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_ReadNvimInfo_SwitchOn
 ��������  : ��NV�ж�ȡ��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��26��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2011��11��16��
    ��    ��   : zhoujun 40661
    �޸�����   : ����NV���ȡ֮��������,������Ҫ����˳��

  3.��    ��   : 2011��10��28��
    ��    ��   : z00161729
    �޸�����   : V7R1 phase III����ע���޸�:����Lģms mode��cs service config NV���ȡ
  4.��    ��   : 2012��3��17��
    ��    ��   : w00176964
    �޸�����   : DTS2012031900095 V7R1 C30 SBM&EM��������:���Ӷ��ƹ��ܵ�NV��ȡ
  5.��    ��   : 2012��3��1��
    ��    ��   : w00167002
    �޸�����   : V7R1C50 CSFB&PPAC&ETWS&ISR:����en_NV_Item_Ho_Wait_Sysinfo_Timer_Config
                  �Ķ�ȡ

  5.��    ��   : 2012��5��10��
    ��    ��   : z40661
    �޸�����   : DTS2012041105159,UE Network Capability�����޸�Ϊ��LMM����,ɾ��nvim��д
  6.��    ��   : 2012��5��15��
    ��    ��   : l00130025
    �޸�����   : DTS2012012903053:Ts23.122 ch4.4.3.2.1 Auto user reselecton����֧��
  7.��    ��   : 2012��6��11��
    ��    ��   : w00166186
    �޸�����   : AT&T&DCM��Ŀ
  8.��    ��   : 2012��6��14��
    ��    ��   : L60609
    �޸�����   : AT&T&DCM:������ȡ�������Ʊ�ʶ,���뼼��NV��en_NV_Item_RAT_PRIO_LIST��MSCC����ͨ��TAFMMC_START_REQ֪ͨMMC
  9.��    ��   : 2012��6��9��
    ��    ��   : l00130025
    �޸�����   : DTS2012060400029:��Ӷ�HPLMNAct���Ƚ��뼼���Ķ��ƣ�ĿǰUSim����HPLMNACT�ܶ಻֧��L
 10.��    ��   : 2012��8��13��
    ��    ��   : t00212959
    �޸�����   : DCM�����������������:en_NV_Item_GPRS_Non_Drx_Timer_Length��GMM�Ƶ�MMCά��
 11.��    ��   : 2012��8��14��
    ��    ��   : z00161729
    �޸�����   : DCM������������������޸�,֧��L���������޸�
 12.��    ��   : 2012��8��14��
    ��    ��   : t00212959
    �޸�����   : DCM������������������޸�,MNC��λ�Ƚ�
 13.��    ��   : 2012��10��8��
    ��    ��   : z00161729
    �޸�����   : DTS2012083007796:�޿�֧������ҵ��ʱ����Ӧ����ѡ��gu��anycellפ��
 14.��    ��   : 2012��11��29��
    ��    ��   : w00176964
    �޸�����   : DTS2012112902395:��ȡHPLMNע�����NV
 15.��    ��   : 2012��11��21��
    ��    ��   : z00161729
    �޸�����   : ֧��cerssi��nmr
 16.��    ��   : 2012��12��25��
    ��    ��   : s00217060
    �޸�����   : for DSDA GUNAS C CORE:������ȡƽ̨���뼼��������NV��
 17.��    ��   : 2013��3��14��
    ��    ��   : w00176964
    �޸�����   : ��ȡUCS2�͹رն���������NV
 18.��    ��   : 2013��4��10��
    ��    ��   : w00176964
    �޸�����   : ����H3G��������NV
 19.��    ��   : 2013��6��6��
    ��    ��   : z00161729
    �޸�����   : SVLTE�޸�
 20.��    ��   : 2013��5��25��
    ��    ��   : z00234330
    �޸�����   : DTS2013052301419
 21.��    ��   : 2013��7��25��
    ��    ��   : w00242748
    �޸�����   : DTS2013072200933:vodafone r8����csfb mt��w��cs ps�����ͷź�1.5s����ѡ��l��
                 �������2s���һ������·�paging��Ϣ�����ڶ�Ѱ�����д�ͨ���ο����ʵ�֣�
                 rau req�д�follow on��־,����ȷЭ������
 22.��    ��   : 2013��8��29��
    ��    ��   : f62575
    �޸�����   : VSIM FEATURE
 23.��    ��   : 2013��10��9��
    ��    ��   : l00208543
    �޸�����   : DTS2013100904573
 24.��    ��   : 2013��11��01��
    ��    ��   : l00208543
    �޸�����   : ���ݿ����ͽ�ֹ������ʽ
 25.��    ��   : 2013��11��25��
    ��    ��   : z00161729
    �޸�����   : SVLTE�Ż�G-TL ps�л������޸�
 26.��    ��   : 2013��12��24��
    ��    ��   : w00242748
    �޸�����   : DTS2013101106863:L�±���ԭ��ֵ#35��ֻ����R10����Э�����ϴ������#11
                 ԭ��ֵ������ͬ��������OTHER CAUSE������
 27.��    ��   : 2014��02��10��
    ��    ��   : f62575
    �޸�����   : DTS2014012600456: en_NV_Item_WG_RF_MAIN_BAND�����޸�Ϊ���ڴ��л�ȡ
 28.��    ��   : 2013��12��30��
    ��    ��   : f00261443
    �޸�����   : ���Ӷ�ȡImsVoice�ƶ��Թ������nv
 29.��    ��   : 2014��1��21��
    ��    ��   : w00167002
    �޸�����   : SVLTE��������Ŀ:DSDS�Ƿ�֧��NV��ȡ��
 30.��    ��   : 2014��01��17��
    ��    ��   : l00198894
    �޸�����   : V9R1C53 C+L ������ѡ��Ŀ
 31.��    ��   : 2014��02��13��
    ��    ��   : f62575
    �޸�����   : DTS2014012902032: ��ֹSVLTE��Ʒ����˫PSע��
 32.��    ��   : 2014��2��18��
    ��    ��   : l00215384
 33.��    ��   : 2014��02��25��
    ��    ��   : z00161729
    �޸�����   : DTS2014022206794:GCF 9.2.1.2.1b/9.2.3.2.3/9.2.1.2.1ʧ��disable lte
                 ʱrau��Ҫ��L��ȡ��ȫ������
 34.��    ��   : 2014��2��24��
    ��    ��   : w00176964
    �޸�����   : High_Rat_Hplmn_Search���Ե���
 35.��    ��   : 2014��02��27��
    ��    ��   : w00242748
    �޸�����   : DTS2014022805239: ����FDD �����ϱ�
 36.��    ��   : 2014?5?4?
    ��    ��   : t00173447
    �޸�����   : DTS2014042105390,������������
 37.��    ��   : 2014��5��30��
    ��    ��   : s00217060
    �޸�����   : utran flash csfb NV��Ķ�ȡ
 38.��    ��   : 2013��7��25��
    ��    ��   : w00242748
    �޸�����   : DTS2014053105098:CSFB mo�Ƿ���Ҫ��follow on����NV����
 39.��    ��   : 2014��7��14��
    ��    ��   : w00242748
    �޸�����   : DTS2014063003419:SYSCFG���������ȼ����뼼����������NV����
 40.��    ��   : 2014��7��30��
    ��    ��   : s00217060
    �޸�����   : DTS2014072407584:��0xD20B NV,����SRVCC����
 41.��    ��   : 2014��7��17��
    ��    ��   : b00269685
    �޸�����   : DSDS IV:����end sessionʱ��ʱ
 42.��    ��   : 2014��10��13��
    ��    ��   : b00269685
    �޸�����   : ���Ӷ�ȡ supported codecNV
 43.��    ��   : 2014��10��20��
    ��    ��   : h00285180
    �޸�����   : �ܾ�ԭ��ֵ�Ż�PhaseII DTS2014110307415
 44.��    ��   : 2015��1��5��
    ��    ��   : h00285180
    �޸�����   : LTE #14�ܾ��Ż�:DTS2015010401946

 45.��    ��   : 2015��02��11��
    ��    ��   : w00167002
    �޸�����   : DTS2015021000324:��ǰ��DSDS˫���У�GSM���������ܲ���NAS ����NO RF,��ô
                NAS������ʱ����ʱ�����ϱ��޷����ˡ��޸�Ϊ�ӳ�NAS��ʱ��ʱ��
 46.��    ��   : 2015��1��4��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��DAM�����޸�
 47.��    ��   : 2015��8��13��
    ��    ��   : l00289540
    �޸�����   : User_Exp_Improve�޸�
 48.��    ��   : 2015��8��26��
    ��    ��   : c00318887
    �޸�����   : for Ԥ��Ƶ�������Ż�
 49.��    ��   : 2015��9��30��
    ��    ��   : c00318887
    �޸�����   : DTS2015091700173:

50.��    ��   : 2015��9��17��
   ��    ��   : y00176023
   �޸�����   : DTS2015091602371:�ĵ���������2G/3G anycell����
 51.��    ��   : 2015��9��23��
    ��    ��   : z00359541
    �޸�����   : for CSע��ʧ�ܼ����ֹLA
 52.��    ��   : 2015��10��14��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������
 53.��    ��   : 2016��1��20��
    ��    ��   : c00318887
    �޸�����   : DTS2015123110917: usim����GSM����2G��Ȩ��csfb��3G�¼�Ȩ����
 54.��    ��   : 2016��04��10��
    ��    ��   : j00174725
    �޸�����   : DTS2016040901340
*****************************************************************************/
VOS_VOID NAS_MMC_ReadNvimInfo_SwitchOn()
{
    /* en_NV_Item_Platform_RAT_CAP */
    NAS_MMC_ReadPlatformRatCapNvim();
    /* en_NV_Item_Gsm_Classmark1 */
    NAS_MMC_ReadClassMark1Nvim();

    /* en_NV_Item_Gsm_Classmark2 */
    NAS_MMC_ReadClassMark2Nvim();

    /* en_NV_Item_IMEI en_NV_Item_Imei_Svn */
    NAS_MMC_ReadImeisvNvim();


    NAS_MMC_ReadRoamingRejectNoRetryFlgNvim();

    /* ��NV�ж�ȡЭ��汾 */
    NAS_MMC_ReadSupported3GppReleaseNvim();

    /* en_NV_Item_NetworkCapability */
    NAS_MMC_ReadNetworkCapabilityNvim();

    /* en_NV_Item_MMA_MsClass */
    NAS_MMC_ReadMsModeNvim();

    /* en_NV_Item_Support_Freqbands */
    NAS_MMC_ReadUserSetBandNvim();


    /* en_NV_Item_EFust_Service_Cfg */
    NAS_MMC_ReadGsmForbidAccessInfoNvim();


    /* en_NV_Item_Use_Single_Rplmn_When_Area_Lost */
    NAS_MMC_ReadUseSingleRplmnFlagNvim();

    /* en_NV_Item_RPlmnWithRat */
    NAS_MMC_ReadRplmnWithRatNvim();

    /* en_NV_Item_Standard_EHplmn_Support_Flg */
    NAS_MMC_ReadEHPlmnSupportNvim();

    /* en_NV_Item_SrchHplmnFlg_StartOrAreaLostInAutoMode */
    NAS_MMC_ReadSearchHPlmnFlgAutoModeNvim();

    /* en_NV_Item_SrchHplmnFlg_StartInManualMode */
    NAS_MMC_ReadSearchHPlmnFlgManualModeNvim();

    /* en_NV_Item_Add_EHPLMN_WHEN_SRCH_HPLMN_CFG */
    NAS_MMC_ReadAddEhplmnWhenSrchHplmnNvim();

    /* en_NV_Item_SearchHplmnAtPowerOn */
    NAS_MMC_ReadSearchHplmnFlgPowerOnNvim();

    /* en_NV_Item_Enhanced_Hplmn_Srch_Flg */
    NAS_MMC_ReadEnhancedHPlmnSearchFlagNvim();

    /* en_NV_Item_Special_Roam_Flag */
    NAS_MMC_ReadSpecialRoamFlgNvim();

    /* en_NV_Item_Network_Name_From_MM_Info */
    NAS_MMC_ReadNetworkNameNvim();

#if (FEATURE_ON == FEATURE_LTE)
    /* en_NV_Item_TIN_INFO */
    NAS_MMC_ReadTinInfoNvim();

    /* en_NV_Item_Lte_Cs_Service_Config */
    NAS_MMC_ReadLteCsServiceConfigNvim();


    NAS_MMC_ReadLteRoamConfigNvim();

    /*��������,����ʱ��������RPLMN*/
    NAS_MMC_ReadRPLMNConfigNvim();

    /*�����������ƿ���*/
    NAS_MMC_ReadSBMCustomDualIMSIConfigNvim();

    NAS_MMC_ReadHoWaitSysinfoTimeLenNvim();


    /* ��NV�ж�ȡLЭ��汾 */
    NAS_MMC_ReadLNasReleaseNvim();
#else
    NAS_MMC_ReadLastImsiNvim();
#endif
    /* Modified by z00161729 for DCM�����������������, 2012-8-14, begin */
    /* en_NV_Item_Csfb_Emg_Call_LaiChg_Lau_First_CFG*/
    NAS_MMC_ReadCsfbEmgCallLaiChgLauFirstNvim();
    /* Modified by z00161729 for DCM�����������������, 2012-8-14, end */

    NAS_MMC_ReadDailRejectConfigNvim();

    /* en_NV_Item_HPlmnFirstTimer */
    NAS_MMC_ReadHplmnFirstSearchPeriodNvim();

    /* en_NV_Item_Default_Max_Hplmn_Srch_Peri */
    NAS_MMC_ReadDefaultHplmnSrchPeriodNvim();

    /* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, begin */
    NAS_MMC_ReadHighPrioPlmnRefreshTriggerBGSearchFlagNvim();
    /* Added by c00318887 for file refresh��Ҫ����������, 2015-4-28, end */

    /* en_NV_Item_SearchHplmnTtimerValue */
    NAS_MMC_ReadSrchHplmnTtimerValueNvim();

    /* en_NV_Item_OPERLOCK_PLMN_INFO_WHITE */
    NAS_MMC_ReadWhiteOpeLockPlmnInfoNvim();

    /* en_NV_Item_DISABLED_RAT_PLMN_INFO */
    NAS_MMC_ReadDisabledRatPlmnInfoNvim();

    /* en_NV_Item_User_Cfg_Ext_Ehplmn_Info */
    NAS_MMC_ReadUserCfgExtEhplmnInfoNvim();

    /* en_NV_Item_OperLock_Plmn_Info */
    NAS_MMC_ReadBlackOperLockPlmnInfoNvim();



    /* en_NV_Item_Standard_STK_SteeringOfRoaming_Support_Flg */
    NAS_MMC_ReadStandardSTKSteeringOfRoamingFlgNvim();

    /* en_NV_Item_SteeringofRoaming_SUPPORT_CTRL */
    NAS_MMC_ReadCsRejSearchSupportFlagNvim();

    /* en_NV_Item_Autoattach */
    NAS_MMC_ReadAutoAttachNvim();

    /* en_NV_Item_SelPlmn_Mode */
    NAS_MMC_ReadPlmnSelectionModeNvim();

    /* en_NV_Item_EquivalentPlmn */
    NAS_MMC_ReadEquivalentPlmnNvim();

    /* en_NV_Item_Max_Forb_Roam_La */
    NAS_MMC_ReadMaxForbRoamLaNvim();

    /* en_NV_Item_Register_Fail_Cnt */
    NAS_MMC_ReadRoamBrokerRegisterFailCntNvim();

    NAS_MMC_ReadPsLociNvim();

    NAS_MMC_ReadCsLociNvim();

    NAS_MMC_ReadRoamCfgInfoNvim();

    NAS_MMC_ReadDtSingleDomainPlmnSearchNvim();

    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, begin */
    /* en_NV_Item_NVIM_WCDMA_PRIORITY_GSM_SUPPORT_FLG */
    NAS_MMC_ReaducWcdmaPriorityGsmNvim();

    /* en_NV_Item_NVIM_PS_ONLY_CS_SERVICE_SUPPORT_FLG */
    NAS_MMC_ReadPsOnlyCsServiceSupportNvim();

    /* en_NV_Item_System_APP_Config */
    NAS_MMC_ReadAPPConfigSupportNvim();
    /* Modified by s62952 for BalongV300R002 Build�Ż���Ŀ 2012-02-28, end */

    /* Modified by z40661 for ̩��AIS���� 2012-05-17, begin */
    NAS_MMC_ReadAisRoamingNvim();
    /* Modified by z40661 for ̩��AIS���� 2012-05-17, end */


    NAS_MMC_ReadUserAutoReselCfgNvim();


    NAS_MMC_ReadScanCtrlNvim();

    /* en_NV_Item_ACTING_PLMN_SUPPORT_FLAG */
    NAS_MMC_ReadActingHPlmnSupportNvim();

    /* en_NV_Item_Hplmn_Search_Regardless_Mcc_Support */
    NAS_MMC_ReadHPlmnSearchRegardLessMccNvim();

    /* en_NV_Item_SINGLE_DOMAIN_FAIL_ACTION_LIST */
    NAS_MMC_ReadSingleDomainFailActionListNvim();

    /* en_NV_Item_CS_FAIL_NETWORK_FAILURE_PLMN_SEARCH_FLAG */
    NAS_MMC_ReadRegFailNetWorkFailureCustomFlagNvim();



    /* en_NV_Item_PRIO_HPLMNACT_CFG */
    NAS_MMC_ReadPrioHplmnActCfgNvim();


    /* Added by t00212959 for DCM�����������������, 2012-8-15, begin */
    NAS_MMC_ReadPlmnExactlyCompareNvim();
    /* Added by t00212959 for DCM�����������������, 2012-8-15, end */

    NAS_MMC_ReadCustomizeServiceNvim();

    NAS_MMC_ReadHplmnRegisterCtrlNvim();

    NAS_MMC_ReadCellSignReportCfgNvim();

    /* Added by w00176964 for ����֧��������UC2����NV�Ż�, 2013-3-11, begin */
    NAS_MMC_ReadUcs2CustomizationNvim();

    NAS_MMC_ReadCloseSmsCapabilityConfigNvim();
    /* Added by w00176964 for ����֧��������UC2����NV�Ż�, 2013-3-11, end */

    NAS_MMC_ReadH3gCtrlNvim();

#if  (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_ReadEnableLteTimerLenNvim();

    /* Added by c00318887 for ��ֲT3402 , 2015-6-17, begin */
    NAS_MMC_ReadDisableLteStartT3402EnableLteCfgNvim();
    /* Added by c00318887 for ��ֲT3402 , 2015-6-17, end */

    NAS_MMC_ReadCsfbRauFollowOnFlgNvim();

    NAS_MMC_ReadLteCustomMccInfoNvim();

    NAS_MMC_ReadUltraFlashCsfbSupportFlgNvim();

    /* 0xD20B���NV������aucNetworkCapability�е�srvcc�����������8197�е����ò�һ�£���0xD20B�е�Ϊ׼
       ��NVҪ����8197 NV��֮���ȡ */
    NAS_MMC_ReadSrvccSupportFlgNvim();
#endif

    NAS_MMC_ReadSvlteSupportFlagNvim();

    NAS_MMC_ReadPsTransferCfgNvim();

    NAS_MMC_ReadIsrSupportNvim( );
    NAS_MMC_ReadAccBarPlmnSearchNvim();
    NAS_MMC_ReadUserCfgOPlmnInfoNvim();

#if (FEATURE_ON == FEATURE_PTM)
    NAS_MMC_ReadErrlogCtrlInfoNvim();
    NAS_MMC_ReadErrlogNwSrchRecordcfgNvim();
#endif

    NAS_VSIM_InitVsimCfgInfo();

    NAS_MMC_ReadRatForbiddenListConfigNvim();

     NAS_MMC_ReadDsdaPlmnSearchEnhancedCfgNvim();

#if (FEATURE_ON == FEATURE_DSDS)
    NAS_MMC_ReadModemRfShareCfgNvim();

    NAS_MMC_ReadDsdsEndSessionDelayNvim();
#endif
    NAS_MMC_ReadWgRfMainBandNvim();

    NAS_MMC_ReadImsVoiceMMEnableNvim();

    NAS_MMC_ReadLcCtrlParaNvim();

    NAS_MMC_ReadCsOnlyDataServiceSupportNvim();

    NAS_MMC_ReadIgnoreAuthRejFlgNvim();
    NAS_MMC_ReadLteDisabledUseLteInfoFlagNvim();

    NAS_MMC_ReadHighPrioRatHplmnTimerCfgNvim();

    NAS_MMC_Read3GPP2UplmnNotPrefFlgNvim();

    NAS_MMC_ReadSyscfgTriPlmnSrchCfgNvim();

    NAS_MMC_ReadUmtsCodecTypeNvim();
    NAS_MMC_ReadMedCodecTypeNvim();
    NAS_MMC_ReadDplmnNplmnInfoNvim();
    NAS_MMC_ReadChangeNwCauseCfgNvim( );

    NAS_MMC_ReadRelPsSignalConCfgNvim();

#if  (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_ReadLteRejCause14CfgNvim();
#endif

#if  (FEATURE_ON == FEATURE_IMS)
    NAS_MMC_ReadImsRatSupportNvim();
    NAS_MMC_ReadImsCapNvim();
    NAS_MMC_ReadUssdOnImsNvim();
#endif

    NAS_MMC_ReadDsdsActiveModemModeNvim();

    NAS_MMC_ReadDamCfgNvim();
    NAS_MMC_ReadCsmoSupportedCfgNvim();

    NAS_MMC_ReadT3212TimerCfgNvim();

    NAS_MMC_ReadRoamDisplayCfgNvim();
    NAS_MMC_ReadProtectMtCsfbPagingProcedureLenNvim();

    /* Added by y00176023 for DTS2015091602371 �ĵ�����ȼ�ANYCELL��LTE����, 2015-9-17, begin */
    NAS_MMC_ReadLowPrioAnycellsearchLteCfgNvim();
    /* Added by y00176023 for DTS2015091602371 �ĵ�����ȼ�ANYCELL��LTE����, 2015-9-17, end */
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_ReadLteOos2GPrefPlmnSelCfgNvim();
#endif

#if (FEATURE_ON == FEATURE_CSG)
    NAS_MMC_ReadCsgCfgNvim();
#endif
    NAS_MMC_ReadRoamPlmnSelectionSortCfgNvim();
    NAS_MMC_ReadGetGeoCfgInfoNvim();
    NAS_MMC_ReadNonOosPlmnSearchFeatureSupportCfgNvim();

    NAS_MMC_ReadOosPlmnSearchStrategyCfgNvim();

    NAS_MMC_ReadPsRegFailMaxTimesTrigLauOnceFlgNvim();
    NAS_MMC_ReadKeepSrchHplmnEvenRejByCause13Nvim();
    NAS_MMC_ReadEpsRejByCause14InVplmnAllowPsRegFlgNvim();
    NAS_MMC_ReadCarryEplmnWhenSrchRplmnCfgNvim();
    NAS_MMC_ReadLauRejNeedNoRetryWhenCmSrvExistNvim();
    NAS_MMC_ReadLauRejTrigPlmnSearchNvim();


    NAS_MMC_ReadRefreshRplmnWhenEplmnInvalidCfgNvim();

    NAS_MMC_ReadCsRegFailForbLaTimeCfgNvim();

    NAS_MMC_ReadKeepCsForbInfoWhenPsRegSuccCfgNvim();

    NAS_MMC_ReadClearCksnCfgNvim();

    return;
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_SavePlmnRatPrio_SwitchOn
 ��������  : ����������뼼��
 �������  : MSCC_MMC_PLMN_RAT_PRIO_STRU          *pRcvPlmnRatPrio
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��14��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SavePlmnRatPrio_SwitchOn(
    MSCC_MMC_PLMN_RAT_PRIO_STRU          *pRcvPlmnRatPrio
)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstRatPrioList = VOS_NULL_PTR;

    pstRatPrioList           = NAS_MML_GetMsPrioRatList();
    pstRatPrioList->ucRatNum = pRcvPlmnRatPrio->ucRatNum;

    PS_MEM_CPY(pstRatPrioList->aucRatPrio, pRcvPlmnRatPrio->aucRatPrio, NAS_MML_MAX_RAT_NUM);

    return;
}

/* Added by s00246516 for L-C��������Ŀ, 2014-01-28, Begin */
/*****************************************************************************
 �� �� ��  : NAS_MMC_Save3Gpp2RatPrio_SwitchOn
 ��������  : ��������3GPP2���뼼��
 �������  : MSCC_MMC_3GPP2_RAT_STRU          *pst3Gpp2Rat
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��14��
    ��    ��   : s00246516
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_Save3Gpp2RatPrio_SwitchOn(
    MSCC_MMC_3GPP2_RAT_STRU             *pst3Gpp2Rat
)
{
    NAS_MML_3GPP2_RAT_PRIO_STRU        *pst3Gpp2RatPrioList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pst3Gpp2RatPrioList           = NAS_MML_GetMs3Gpp2PrioRatList();

    /* ������ֵ */
    pst3Gpp2RatPrioList->ucRatNum = pst3Gpp2Rat->ucRatNum;

    /* ��ֹ�����쳣��������Խ�� */
    if ( pst3Gpp2RatPrioList->ucRatNum > NAS_MML_MAX_3GPP2_RAT_NUM )
    {
        pst3Gpp2RatPrioList->ucRatNum = NAS_MML_MAX_3GPP2_RAT_NUM;
    }

    /* ������������ */
    for ( i = 0 ; i < pst3Gpp2RatPrioList->ucRatNum; i++ )
    {
        /* ��MSCC���ݹ�����3GPP2����ת��ΪMML��ʽ */
        NAS_MMC_Convert3GPP2RatType( pst3Gpp2Rat->auc3GPP2Rat[i],
                                     &(pst3Gpp2RatPrioList->aucRatPrio[i]));
    }

    return;
}
/* Added by s00246516 for L-C��������Ŀ, 2014-01-28, End */

/*****************************************************************************
 �� �� ��  : NAS_MMC_SaveAllowRegDomain_SwitchOn
 ��������  : ������������ע��ķ�����
 �������  : MSCC_MMC_ALLOWED_REG_DOMAIN_ENUM_UINT8                   enRegDomain
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��1��
    ��    ��   : s46746
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SaveAllowRegDomain_SwitchOn(
    NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_ENUM_UINT8                   enRegDomain
)
{
    switch (enRegDomain)
    {
        case NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_PS:
            NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);
            NAS_MML_SetCsAttachAllowFlg(VOS_FALSE);
            break;

        case NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_CS:
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);
            break;

        case NAS_MSCC_PIF_ALLOWED_REG_DOMAIN_CS_PS:
            NAS_MML_SetCsAttachAllowFlg(VOS_TRUE);
            NAS_MML_SetPsAttachAllowFlg(VOS_TRUE);
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_SndRatModeSwitchOnReq_SwitchOn
 ��������  : ���ݽ���ģʽ�ж�Ӧ���ĸ�ģ����SwitchOn��������SwitchOn״̬����״̬Ǩ��
 �������  : enCurrRat    - ����ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��5��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_SndRatModeSwitchOnReq_SwitchOn(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrSwitchOnRat
)
{
    /* ���ݽ���ģʽ������SwitchOn������ */
    switch ( enCurrSwitchOnRat )
    {

#if (FEATURE_ON == FEATURE_LTE)

        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_TRACE_HIGH("Send start req to LTE!");

            /* ��Lģ�·�SwitchOn�������� */
            NAS_MMC_SndLmmStartReq();
            NAS_MMC_AddSwitchOnIndex_SwitchOn();

            /* ����SwitchOn״̬������״̬��Ǩ�� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_SWITCH_ON_STA_WAIT_L_START_CNF);

            /* �����ȴ��ظ���ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_START_CNF, TI_NAS_MMC_WAIT_LMM_START_CNF_LEN);
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_TRACE_HIGH("Send start req to %s!",
                (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode()) ? "WRRC" : "TRRC");

            /* ��wģ�·�SwitchOn�������� */
            NAS_MMC_SndAsStartReq(WUEPS_PID_WRR);
            NAS_MMC_AddSwitchOnIndex_SwitchOn();

            /* ����SwitchOn״̬������״̬��Ǩ�� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_SWITCH_ON_STA_WAIT_WAS_START_CNF);

            /* �����ȴ��ظ���ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_START_CNF, TI_NAS_MMC_WAIT_WAS_START_CNF_LEN);
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_TRACE_HIGH("Send start req to GAS!");

            /* ��Gģ�·�SwitchOn�������� */
            NAS_MMC_SndAsStartReq(UEPS_PID_GAS);
            NAS_MMC_AddSwitchOnIndex_SwitchOn();

            /* ����SwitchOn״̬������״̬��Ǩ�� */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_SWITCH_ON_STA_WAIT_GAS_START_CNF);

            /* �����ȴ��ظ���ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_START_CNF, TI_NAS_MMC_WAIT_GAS_START_CNF_LEN);
            break;

        default:
            NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_SndRatModeSwitchOnReq_SwitchOn():Invalid net rat type");
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateEhplmnInfo_SwitchOn
 ��������  : ����ʱ����IMSI������EHplmn��Ϣ
 �������  : pucImsi    - ����IMSI��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��8��5��
   ��    ��   : w00167002
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateEhplmnInfo_SwitchOn(
    VOS_UINT8                           *pucImsi
)
{
    VOS_UINT32                          i;
    VOS_UINT8                           ucUserCfgEhplmnListNum;
    NAS_MML_PLMN_ID_STRU                astUserCfgEhPlmnList[NAS_MML_MAX_USER_CFG_EHPLMN_NUM];
    VOS_UINT16                          usUeSptRat;
    NAS_MML_SIM_EHPLMN_INFO_STRU       *pstSimEhplmnInfo    = VOS_NULL_PTR;

#if (FEATURE_ON == FEATURE_LTE)
    usUeSptRat                          = NAS_MML_SIM_UE_SUPPORT_RAT_SUPPORT_LTE;
#else
    usUeSptRat                          = NAS_MML_SIM_UE_SUPPORT_RAT;
#endif

    pstSimEhplmnInfo                    = NAS_MML_GetSimEhplmnList();
    ucUserCfgEhplmnListNum              = 0;
    PS_MEM_SET(astUserCfgEhPlmnList, (VOS_UINT8)0X00, sizeof(astUserCfgEhPlmnList));

    /* ����IMSI��Ϣ������en_NV_Item_User_Cfg_Ehplmn�е�Ehplmn */
    NAS_MML_GetValidUserCfgEhplmnInfo( pucImsi,
                                       &ucUserCfgEhplmnListNum,
                                       astUserCfgEhPlmnList );

    /* �����ǰ��ǰ�û�û��ͨ��NV����EHPLMN������Ч��EHplmn�ĸ���Ϊ0����
       ��IMSI�е�HOME PLMN���µ�EHplmn�б��� */
    if ( 0 == ucUserCfgEhplmnListNum )
    {
        NAS_MMC_UpdateHomePlmn(pucImsi);

        /* ���µ�ǰHPLMN������ */
        NAS_MML_SetHPlmnType(NAS_MML_HPLMN_TYPE_HPLMN);
    }
    else
    {
        /* ���û����õ�EHplmn�б���Ϣ���뵽USIM/SIM���б����EHplmn��Ϣ�� */
        pstSimEhplmnInfo->ucEhPlmnNum = ucUserCfgEhplmnListNum;
        for ( i = 0; i < ucUserCfgEhplmnListNum; i++ )
        {
            pstSimEhplmnInfo->astEhPlmnInfo[i].stPlmnId = astUserCfgEhPlmnList[i];
            pstSimEhplmnInfo->astEhPlmnInfo[i].usSimRat = usUeSptRat;
        }

        NAS_MML_SetHPlmnType(NAS_MML_HPLMN_TYPE_EHPLMN);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_UpdateForbPlmnInfo_SwitchOn
 ��������  : ���꿨�ļ��󣬸���NV�����û����õ�Forb PLMN��Ϣ����ȫ�ֱ����Ϳ��ļ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��3��31��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID NAS_MMC_UpdateForbPlmnInfo_SwitchOn( VOS_VOID )
{
    VOS_UINT32                                              i;
    VOS_UINT32                                              j;
    VOS_UINT32                                              ulGroupNum;
    VOS_UINT32                                              ulFindForbInfo;
    VOS_UINT32                                              ulForbPlmnChgFlg;
    NAS_MML_SIM_FORMAT_PLMN_ID                              stSimPlmn;
    NAS_MML_PLMN_ID_STRU                                    stPlmn;
    NAS_MML_PLMN_ID_STRU                                    stHPlmn;
    NAS_MMC_NVIM_USER_CFG_FORB_PLMN_INFO_STRU               stNvimCfgForbPlmnInfo;

    PS_MEM_SET(&stNvimCfgForbPlmnInfo, 0x00, sizeof(stNvimCfgForbPlmnInfo));

    /* �ӵ�ǰ��IMSI��ȡ��home plmn */
    stHPlmn = NAS_MML_GetImsiHomePlmn(NAS_MML_GetSimImsi());

    /*ѭ��������ʼ��*/
    ulGroupNum = 0;

    ulForbPlmnChgFlg    = VOS_FALSE;

    if ( NV_OK != NV_Read( en_NV_Item_User_Cfg_Forb_Plmn_Info,
                            &stNvimCfgForbPlmnInfo, sizeof(NAS_MMC_NVIM_USER_CFG_FORB_PLMN_INFO_STRU)) )
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_ReadUserCfgForbPlmnInfoNvim:Read NV Failed");
        return;
    }

    ulGroupNum = stNvimCfgForbPlmnInfo.ulGroupNum;

    /* ��ֹ����Խ�� */
    if ( ulGroupNum > NAS_MMC_NVIM_MAX_USER_CFG_FORB_PLMN_GROUP_NUM )
    {
        ulGroupNum = NAS_MMC_NVIM_MAX_USER_CFG_FORB_PLMN_GROUP_NUM;
    }


    for (j = 0; j < ulGroupNum; j++)
    {
        ulFindForbInfo  = VOS_FALSE;

        /* ��ֹ����Խ�� */
        if (stNvimCfgForbPlmnInfo.astForbPlmnInfo[j].ucImsiPlmnListNum > NAS_MMC_MAX_USER_CFG_IMSI_PLMN_NUM)
        {
            stNvimCfgForbPlmnInfo.astForbPlmnInfo[j].ucImsiPlmnListNum = NAS_MMC_MAX_USER_CFG_IMSI_PLMN_NUM;
        }

        for ( i = 0; i < stNvimCfgForbPlmnInfo.astForbPlmnInfo[j].ucImsiPlmnListNum; i++ )
        {
            PS_MEM_CPY(stSimPlmn.aucSimPlmn, stNvimCfgForbPlmnInfo.astForbPlmnInfo[j].astImsiPlmnList[i].aucSimPlmn, NAS_MML_SIM_PLMN_ID_LEN);
            NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

            /* �û����õ�IMSI plmn������BCCH��ʽ�ģ�����͵�ǰ���ſ���IMSI�Ŷ���ͬ���Ѹ����Ӧ��ForbPlmn��Ϣ�ӵ�forb�б��� */
            if ( VOS_TRUE == NAS_MML_CompareBcchPlmnwithSimPlmn(&stPlmn, &stHPlmn) )
            {
                ulFindForbInfo = VOS_TRUE;
                break;
            }
        }


        /* ����ҵ�һ��forbPlmn��Ϣʱ����forbPlmn�浽ȫ�ֱ��� */
        if (VOS_TRUE == ulFindForbInfo)
        {
            /* ��ֹ����Խ�� */
            if ( stNvimCfgForbPlmnInfo.astForbPlmnInfo[j].ucForbPlmnListNum > NAS_MMC_MAX_BLACK_LOCK_PLMN_WITH_RAT_NUM )
            {
                stNvimCfgForbPlmnInfo.astForbPlmnInfo[j].ucForbPlmnListNum = NAS_MMC_MAX_BLACK_LOCK_PLMN_WITH_RAT_NUM;
            }

            for ( i = 0; i < stNvimCfgForbPlmnInfo.astForbPlmnInfo[j].ucForbPlmnListNum; i++ )
            {
                PS_MEM_CPY(stSimPlmn.aucSimPlmn, stNvimCfgForbPlmnInfo.astForbPlmnInfo[j].astForbPlmnList[i].aucSimPlmn, NAS_MML_SIM_PLMN_ID_LEN);
                NAS_MMC_ConvertSimPlmnToNasPLMN(&stSimPlmn, &stPlmn);

                if (VOS_TRUE == NAS_MML_AddForbPlmn(&stPlmn))
                {
                    ulForbPlmnChgFlg    = VOS_TRUE;
                }
            }

            break;
        }

    }

    /* ForbPlmn�б仯ʱ��д���ļ� */
    if (VOS_TRUE == ulForbPlmnChgFlg)
    {
        NAS_MMC_SndUsimUpdateForbPlmnReq();
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitLastRplmnRat_SwitchOn
 ��������  : ����IMSI�����ı�ʱ,��ʼ���ϴιػ�ʱ��RAT����
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��04��18��
   ��    ��   : L65478
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��5��16��
   ��    ��   : z00161729
   �޸�����   : DTS2014051500129:ʹ����ͨ�����ֶ���vodafoneע��ɹ����ػ�����һ�ű�����Ӫ��EE�Ŀ�����ע��EE���ٹػ���
               �ٻ���֮ǰ��ͨ��������������ע�����磬��ȡl��rplmn������û�л�ȡgu��rplmn
*****************************************************************************/
VOS_VOID NAS_MMC_InitLastRplmnRat_SwitchOn(VOS_VOID)
{
    NAS_MML_RPLMN_CFG_INFO_STRU             *pstRplmnCfgInfo     = VOS_NULL_PTR;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    if (VOS_TRUE   == NAS_MMC_IsImsiChange_SwitchOn())
    {
        /* ��SIM��ʱ,��ʼ��ΪBUTT;
           SIM��ʱ,����LTE ONLYʱ,��Ϊ��Ҫdisable LTE,���Գ�ʼ��Ϊ�θ����ȼ���RAT */
        pstRplmnCfgInfo->enLastRplmnRat = NAS_MML_NET_RAT_TYPE_BUTT;

        /* ����RAT����NV */
        NAS_MMC_WriteRplmnWithRatNvim();
    }


}




/*****************************************************************************
 �� �� ��  : NAS_MMC_IsSimCardUsedOtherUe_SwitchOn
 ��������  : �жϿ��Ƿ��ڱ���ֻ����ù�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��4��10��
    ��    ��   : j00174725
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_IsSimCardUsedOtherUe_SwitchOn(VOS_VOID)
{
    VOS_UINT8                          *pucCsLociFileContent = VOS_NULL_PTR;
    VOS_UINT8                          *pucPsLociFileContent = VOS_NULL_PTR;
    VOS_UINT8                           aucPtmsi[NAS_MML_MAX_PTMSI_LEN];
    VOS_UINT8                           aucTmsi[NAS_MML_MAX_TMSI_LEN];
    VOS_UINT8                           i;

    /*��ʼ��*/
    NAS_MEM_SET_S(aucPtmsi, NAS_MML_MAX_PTMSI_LEN, 0, NAS_MML_MAX_PTMSI_LEN);
    NAS_MEM_SET_S(aucTmsi,   NAS_MML_MAX_TMSI_LEN, 0, NAS_MML_MAX_TMSI_LEN);

    /* ��ȡ������ԭʼ��PTMSI */
    pucPsLociFileContent = NAS_MML_GetSimPsLociFileContent();
    for (i = 0; i < NAS_MML_MAX_PTMSI_LEN; i++)
    {
       aucPtmsi[i] = pucPsLociFileContent[i];
    }

    /* ��ȡ������ԭʼ��TMSI */
    pucCsLociFileContent = NAS_MML_GetSimCsLociFileContent();
    for (i = 0; i < NAS_MML_MAX_TMSI_LEN; i++)
    {
       aucTmsi[i] = pucCsLociFileContent[i];
    }

    /* �Ƚ�PTMSI */
    if (0 != PS_MEM_CMP(aucPtmsi, NAS_MMC_GetLastPtmsi_SwitchOn(), NAS_MML_MAX_PTMSI_LEN))
    {
        NAS_TRACE_HIGH("NAS_MMC_IsSimCardUsedOtherUe_SwitchOn: Ptmsi");

        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsSimCardUsedOtherUe_SwitchOn: Ptmsi");

        return VOS_TRUE;
    }

    /* �Ƚ�TMSI */
    if (0 != PS_MEM_CMP(aucTmsi, NAS_MMC_GetLastTmsi_SwitchOn(), NAS_MML_MAX_TMSI_LEN))
    {
        NAS_TRACE_HIGH("NAS_MMC_IsSimCardUsedOtherUe_SwitchOn: Tmsi");

        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsSimCardUsedOtherUe_SwitchOn: Tmsi");
        
        return VOS_TRUE;
    }

    /* �Ƚ�RAI */
    if (0 != PS_MEM_CMP(NAS_MML_GetSimRai(), NAS_MMC_GetLastRai_SwitchOn(), NAS_MML_SIM_MAX_RAI_LEN))
    {
        NAS_TRACE_HIGH("NAS_MMC_IsSimCardUsedOtherUe_SwitchOn: Rai");

        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsSimCardUsedOtherUe_SwitchOn: Rai");
        
        return VOS_TRUE;
    }

    /* �Ƚ�LAI */
    if (0 != PS_MEM_CMP(NAS_MML_GetSimLai(), NAS_MMC_GetLastLai_SwitchOn(), NAS_MML_SIM_MAX_LAI_LEN))
    {
        NAS_TRACE_HIGH("NAS_MMC_IsSimCardUsedOtherUe_SwitchOn: Lai");

        NAS_NORMAL_LOG(WUEPS_PID_MMC, "NAS_MMC_IsSimCardUsedOtherUe_SwitchOn: Lai");
        
        return VOS_TRUE;
    }

    return VOS_FALSE;
    
}



/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

