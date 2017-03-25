/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasUsimmApi.c
  �� �� ��   : ����
  ��    ��   : z00161729
  ��������   : 2013��6��3��
  ����޸�   :
  ��������   : NasUsimmApi.c�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��6��3��
    ��    ��   : z00161729
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasUsimmApi.h"
#include "NasSndUsimm.h"
#include "NasUsimmApiMntn.h"
#include "NasMmlCtx.h"

    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-29, begin */
#include "MM_Share.h"
    /* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-29, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_USIMMAPI_C

TAF_USIMM_VSIM_INFO_STRU             g_stNasVsimInfo;

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/


/*****************************************************************************
  5 ��������
*****************************************************************************/
/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-30, begin */
NAS_USIMM_SRVICES_TYPE_STRU g_NasUsimSrviceTypeTab[NAS_USIM_SVR_MAX_SERVICE] =
{
    {NAS_USIM_SVR_NONE,                     UICC_SVR_NONE,                  UICC_SVR_NONE},                 /* 0 */

    {NAS_USIM_SVR_LOCAL_PHONEBOOK,          UICC_SVR_NONE,                  USIM_SVR_LOCAL_PHONEBOOK},      /* 1 */
    {NAS_USIM_SVR_FDN,                      SIM_SVR_FDN,                    USIM_SVR_FDN},
    {NAS_USIM_SVR_EXT2,                     SIM_SVR_EXT2,                   USIM_SVR_EXT2},
    {NAS_USIM_SVR_SDN,                      SIM_SVR_SDN,                    USIM_SVR_SDN},
    {NAS_USIM_SVR_EXT3,                     SIM_SVR_EXT3,                   USIM_SVR_EXT3},
    {NAS_USIM_SVR_BDN,                      SIM_SVR_BDN,                    USIM_SVR_BDN},
    {NAS_USIM_SVR_EXT4,                     SIM_SVR_EXT4,                   USIM_SVR_EXT4},
    {NAS_USIM_SVR_OCI_OCT,                  UICC_SVR_NONE,                  USIM_SVR_OCI_OCT},
    {NAS_USIM_SVR_ICI_ICT,                  UICC_SVR_NONE,                  USIM_SVR_ICI_ICT},

    {NAS_USIM_SVR_SMS,                      SIM_SVR_SMS,                    USIM_SVR_SMS},                  /* 10 */
    {NAS_USIM_SVR_SMSR,                     SIM_SVR_SMS_REPORTS,            USIM_SVR_SMSR},
    {NAS_USIM_SVR_SMSP,                     SIM_SVR_SMS_PARA,               USIM_SVR_SMSP},
    {NAS_USIM_SVR_AOC,                      SIM_SVR_AOC,                    USIM_SVR_AOC},
    {NAS_USIM_SVR_CCP,                      SIM_SVR_CCP,                    USIM_SVR_CCP},
    {NAS_USIM_SVR_CBMI,                     SIM_SVR_CBMID,                  USIM_SVR_CBMI},
    {NAS_USIM_SVR_CBMIR,                    SIM_SVR_CBMIR,                  USIM_SVR_CBMIR},
    {NAS_USIM_SVR_GID1,                     SIM_SVR_GIDL1,                  USIM_SVR_GID1},
    {NAS_USIM_SVR_GID2,                     SIM_SVR_GIDL2,                  USIM_SVR_GID2},
    {NAS_USIM_SVR_SPN,                      SIM_SVR_SERVICE_PRO_NAME,       USIM_SVR_SPN},

    {NAS_USIM_SVR_UPLMN_SEL_WACT,           SIM_SVR_USER_CTRL_PLMN,         USIM_SVR_UPLMN_SEL_WACT},       /* 20 */
    {NAS_USIM_SVR_MSISDN,                   SIM_SVR_MSISDN,                 USIM_SVR_MSISDN},
    {NAS_USIM_SVR_IMAGE,                    SIM_SVR_IMG,                    USIM_SVR_IMAGE},
    {NAS_USIM_SVR_SOLSA,                    SIM_SVR_SOLSA,                  USIM_SVR_SOLSA},
    {NAS_USIM_SVR_ENH_ML_SVC,               SIM_SVR_ENH_ML_SVC,             USIM_SVR_ENH_ML_SVC},
    {NAS_USIM_SVR_AA_EMLPP,                 SIM_SVR_AUTO_ANSWER_FOR_EMLPP,  USIM_SVR_AA_EMLPP},
    {NAS_USIM_SVR_RFU1,                     SIM_SVR_RFU1,                   USIM_SVR_RFU1},
    {NAS_USIM_SVR_GSM_ACCESS_IN_USIM,       UICC_SVR_NONE,                  USIM_SVR_GSM_ACCESS_IN_USIM},
    {NAS_USIM_SVR_DATA_DL_SMSPP,            SIM_SVR_DD_VIA_SMS_PP,          USIM_SVR_DATA_DL_SMSPP},
    {NAS_USIM_SVR_DATA_DL_SMSCB,            SIM_SVR_DD_VIA_SMS_CB,          USIM_SVR_DATA_DL_SMSCB},

    {NAS_USIM_SVR_CALL_CONTROL,             SIM_SVR_CALL_CONTROL,           USIM_SVR_CALL_CONTROL},         /* 30 */
    {NAS_USIM_SVR_MOSMS_CONTROL,            SIM_SVR_MOSMC,                  USIM_SVR_MOSMS_CONTROL},
    {NAS_USIM_SVR_RUN_AT_CMD,               SIM_SVR_RUN_AT_CMD,             USIM_SVR_RUN_AT_CMD},
    {NAS_USIM_SVR_SET_ONE,                  UICC_SVR_NONE,                  USIM_SVR_SET_ONE},
    {NAS_USIM_SVR_EST,                      UICC_SVR_NONE,                  USIM_SVR_EST},
    {NAS_USIM_SVR_ACL,                      UICC_SVR_NONE,                  USIM_SVR_ACL},
    {NAS_USIM_SVR_DEPERSON_KEYS,            SIM_SVR_DPCK,                   USIM_SVR_DEPERSON_KEYS},
    {NAS_USIM_SVR_COOP_NETWK_LIST,          SIM_SVR_CONL,                   USIM_SVR_COOP_NETWK_LIST},
    {NAS_USIM_SVR_GSM_SECURITY_CONTEXT,     UICC_SVR_NONE,                  USIM_SVR_GSM_SECURITY_CONTEXT},
    {NAS_USIM_SVR_CPBCCH,                   SIM_SVR_CPBCCHI,                USIM_SVR_CPBCCH},

    {NAS_USIM_SVR_INV_SCAN,                 SIM_SVR_INV_SCAN,               USIM_SVR_INV_SCAN},             /* 40 */
    {NAS_USIM_SVR_MEXE,                     SIM_SVR_MEXE,                   USIM_SVR_MEXE},
    {NAS_USIM_SVR_OPLMN_SEL_WACT,           SIM_SVR_OPERATOR_CTRL_PLMN,     USIM_SVR_OPLMN_SEL_WACT},
    {NAS_USIM_SVR_HPLMN_WACT,               SIM_SVR_HPLMN,                  USIM_SVR_HPLMN_WACT},
    {NAS_USIM_SVR_EXT5,                     UICC_SVR_NONE,                  USIM_SVR_EXT5},
    {NAS_USIM_SVR_PLMN_NTWRK_NAME,          SIM_SVR_PLMNNN,                 USIM_SVR_PLMN_NTWRK_NAME},
    {NAS_USIM_SVR_OPLMN_LIST,               SIM_SVR_OPLMNL,                 USIM_SVR_OPLMN_LIST},
    {NAS_USIM_SVR_MAILBOX_DIAL,             SIM_SVR_MDN,                    USIM_SVR_MAILBOX_DIAL},
    {NAS_USIM_SVR_MSG_WAIT,                 SIM_SVR_MWIS,                   USIM_SVR_MSG_WAIT},
    {NAS_USIM_SVR_CALL_FWD_IND,             SIM_SVR_CFIS,                   USIM_SVR_CALL_FWD_IND},

    {NAS_USIM_SVR_RFU2,                     SIM_SVR_RFU2,                   USIM_SVR_RFU2},                  /* 50 */
    {NAS_USIM_SVR_SP_DISP_INFO,             SIM_SVR_SPDI,                   USIM_SVR_SP_DISP_INFO},
    {NAS_USIM_SVR_MMS,                      SIM_SVR_MMS,                    USIM_SVR_MMS},
    {NAS_USIM_SVR_EXT8,                     SIM_SVR_EXT8,                   USIM_SVR_EXT8},
    {NAS_USIM_SVR_GPRS_USIM,                UICC_SVR_NONE,                  USIM_SVR_GPRS_USIM},
    {NAS_USIM_SVR_MMS_USR_P,                SIM_SVR_MMS_UCP,                USIM_SVR_MMS_USR_P},
    {NAS_USIM_SVR_NIA,                      SIM_SVR_NID,                    USIM_SVR_NIA},
    {NAS_USIM_SVR_VGCS_GID_LIST,            SIM_SVR_EFVGCS_EFVGCSS,         USIM_SVR_VGCS_GID_LIST},
    {NAS_USIM_SVR_VBS_GID_LIST,             SIM_SVR_FVBS_EFVBSS,            USIM_SVR_VBS_GID_LIST},
    {NAS_USIM_SVR_PSEUDONYM,                UICC_SVR_NONE,                  USIM_SVR_PSEUDONYM},

    {NAS_USIM_SVR_UPLMN_WLAN_ACC,           UICC_SVR_NONE,                  USIM_SVR_UPLMN_WLAN_ACC},       /* 60 */
    {NAS_USIM_SVR_OPLMN_WLAN_ACC,           UICC_SVR_NONE,                  USIM_SVR_OPLMN_WLAN_ACC},
    {NAS_USIM_SVR_USER_CTRL_WSID,           UICC_SVR_NONE,                  USIM_SVR_USER_CTRL_WSID},
    {NAS_USIM_SVR_OPER_CTRL_WSID,           UICC_SVR_NONE,                  USIM_SVR_OPER_CTRL_WSID},
    {NAS_USIM_SVR_VGCS_SECURITY,            UICC_SVR_NONE,                  USIM_SVR_VGCS_SECURITY},
    {NAS_USIM_SVR_VBS_SECURITY,             UICC_SVR_NONE,                  USIM_SVR_VBS_SECURITY},
    {NAS_USIM_SVR_WLAN_REAUTH_ID,           UICC_SVR_NONE,                  USIM_SVR_WLAN_REAUTH_ID},
    {NAS_USIM_SVR_MM_STORAGE,               UICC_SVR_NONE,                  USIM_SVR_MM_STORAGE},
    {NAS_USIM_SVR_GBA,                      UICC_SVR_NONE,                  USIM_SVR_GBA},
    {NAS_USIM_SVR_MBMS_SECURITY,            UICC_SVR_NONE,                  USIM_SVR_MBMS_SECURITY},

    {NAS_USIM_SVR_DATA_DL_USSD,             UICC_SVR_NONE,                  USIM_SVR_DATA_DL_USSD},         /* 70 */
    {NAS_USIM_SVR_EHPLMN,                   UICC_SVR_NONE,                  USIM_SVR_EHPLMN},
    {NAS_USIM_SVR_TP_AFTER_UICC_ACT,        UICC_SVR_NONE,                  USIM_SVR_TP_AFTER_UICC_ACT},
    {NAS_USIM_SVR_EHPLMN_IND,               UICC_SVR_NONE,                  USIM_SVR_EHPLMN_IND},
    {NAS_USIM_SVR_RPLMN_LACT,               UICC_SVR_NONE,                  USIM_SVR_RPLMN_LACT},
    {NAS_USIM_SVR_OMA_BCAST_PROFILE,        UICC_SVR_NONE,                  USIM_SVR_OMA_BCAST_PROFILE},
    {NAS_USIM_SVR_GBAKEY_EM,                UICC_SVR_NONE,                  USIM_SVR_GBAKEY_EM},
    {NAS_USIM_SVR_TERMINAL_APP,             UICC_SVR_NONE,                  USIM_SVR_TERMINAL_APP},
    {NAS_USIM_SVR_SPN_ICON,                 UICC_SVR_NONE,                  USIM_SVR_SPN_ICON},
    {NAS_USIM_SVR_PNN_ICON,                 UICC_SVR_NONE,                  USIM_SVR_PNN_ICON},

    {NAS_USIM_SVR_CONNECT_SIM_IP,           UICC_SVR_NONE,                  USIM_SVR_CONNECT_SIM_IP},       /* 80 */
    {NAS_USIM_SVR_IWLEN_ID_LIST,            UICC_SVR_NONE,                  USIM_SVR_IWLEN_ID_LIST},
    {NAS_USIM_SVR_IWLEN_EHPLMN_IND,         UICC_SVR_NONE,                  USIM_SVR_IWLEN_EHPLMN_IND},
    {NAS_USIM_SVR_IWLEN_HPLMN_IND,          UICC_SVR_NONE,                  USIM_SVR_IWLEN_HPLMN_IND},
    {NAS_USIM_SVR_IWLEN_RPLMN,              UICC_SVR_NONE,                  USIM_SVR_IWLEN_RPLMN},
    {NAS_USIM_SVR_EPS_INFO,                 UICC_SVR_NONE,                  USIM_SVR_EPS_INFO},
    {NAS_USIM_SVR_CSG_COR_IND,              UICC_SVR_NONE,                  USIM_SVR_CSG_COR_IND},
    {NAS_USIM_SVR_CALL_CTRL_EPS,            UICC_SVR_NONE,                  USIM_SVR_CALL_CTRL_EPS},
    {NAS_USIM_SVR_HPLMN_DIR_ACCESS,         UICC_SVR_NONE,                  USIM_SVR_HPLMN_DIR_ACCESS},
    {NAS_USIM_SVR_ECALL_DATA,               UICC_SVR_NONE,                  USIM_SVR_ECALL_DATA},

    {NAS_USIM_SVR_OP_CGS ,                  UICC_SVR_NONE,                  USIM_SVR_OP_CGS},               /* 90 */
    {NAS_USIM_SVR_SM_VOER_IP ,              UICC_SVR_NONE,                  USIM_SVR_SM_VOER_IP},

    {NAS_USIM_SVR_CSG_CTRL ,              UICC_SVR_NONE,                    USIM_SVR_CSG_CTRL},

    {NAS_USIM_SVR_CHV1_DISABLE,             SIM_SVR_CHV1,                   UICC_SVR_NONE},
    {NAS_USIM_SVR_ADN,                      SIM_SVR_ADN,                    UICC_SVR_NONE},
    {NAS_USIM_SVR_PLMN_SELECTOR,            SIM_SVR_PLMN_SELECTOR,          UICC_SVR_NONE},
    {NAS_USIM_SVR_EXT1,                     SIM_SVR_EXT1,                   UICC_SVR_NONE},
    {NAS_USIM_SVR_LND,                      SIM_SVR_LND,                    UICC_SVR_NONE},
    {NAS_USIM_SVR_MENU_SEL,                 SIM_SVR_MENU_SELECTION,         UICC_SVR_NONE},
    {NAS_USIM_SVR_PROACTIVE_SIM,            SIM_SVR_PRO_SIM,                UICC_SVR_NONE},
    {NAS_USIM_SVR_MO_SMS_BY_SIM,            SIM_SVR_MOSMC,                  UICC_SVR_NONE},

    {NAS_USIM_SVR_GPRS ,                    SIM_SVR_GPRS,                   UICC_SVR_NONE},                 /* 100 */
    {NAS_USIM_SVR_USSD ,                    SIM_SVR_USSD,                   UICC_SVR_NONE},
    {NAS_USIM_SVR_EXT_CCP ,                 SIM_SVR_ECCP,                   UICC_SVR_NONE},
};
/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-30, end */

/*lint -save -e958 */

/*****************************************************************************
  6 ��������
*****************************************************************************/


/*****************************************************************************
 �� �� ��  : NAS_USIMMAPI_SetFileReq
 ��������  : ��USIMMģ���NAS_SndUsimmUpdateFileReq��NAS_SndUsimmUpdateFileReq_Instance���з�װ��
             SVLTEģʽ�µ���NAS_SndUsimmUpdateFileReq_Instance��
             ��SVLTEģʽ�µ���NAS_SndUsimmUpdateFileReq
 �������  : ulSenderPid:���������pId��
             ulSendPara :���͵Ĳ�����
             pstSetFileInfo:���õ��ļ���Ϣ��
 �������  : ��
 �� �� ֵ  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
 *****************************************************************************/
VOS_UINT32 NAS_USIMMAPI_SetFileReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    NAS_USIMM_UPDATEFILE_INFO_STRU     *pstSetFileInfo
)
{
    VOS_UINT32                          ulRslt;

    /* ��USIMM����UpdateFile��Ϣ */
    ulRslt = NAS_SndUsimmUpdateFileReq(ulSenderPid,
                                       ulSendPara,
                                      (NAS_USIMM_UPDATEFILE_DATA_STRU *)pstSetFileInfo);

    /* ���ÿ�ά�ɲ� */
    NAS_LogUsimmApiSetFileReq(ulRslt, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, (NAS_USIMM_MNTN_SETFILE_INFO_STRU *)pstSetFileInfo);

    return ulRslt;
}

/*****************************************************************************
 �� �� ��  : NAS_USIMMAPI_GetFileReq
 ��������  : ��USIMMģ���USIMM_GetFileReq��USIMM_GetFileReq_Instance���з�װ��
             SVLTEģʽ�µ���USIMM_GetFileReq_Instance��
             ��SVLTEģʽ�µ���NAS_SndUsimmUpdateFileReq
 �������  : ulSenderPid:���������pId��
             ulSendPara :���͵Ĳ�����
             pstGetFileInfo:��ȡ���ļ���Ϣ��
 �������  : ��
 �� �� ֵ  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_USIMMAPI_GetFileReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    NAS_USIMM_GETFILE_INFO_STRU        *pstGetFileInfo
)
{
    VOS_UINT32                          ulRet;

    /* ��USIMM����ReadFile��Ϣ */
    ulRet = NAS_SndUsimmReadFileReq(ulSenderPid,
                                    ulSendPara,
                                   (NAS_USIMM_GETFILE_DATA_STRU *)pstGetFileInfo);

    /* ���ÿ�ά�ɲ� */
    NAS_LogUsimmApiGetFileReq(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, (NAS_USIMM_MNTN_GETFILE_INFO_STRU *)pstGetFileInfo);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : NAS_USIMMAPI_AuthReq
 ��������  : ��USIMMģ���NAS_SndUsimmAuthReq��NAS_SndUsimmAuthReq_Instance���з�װ��
             SVLTEģʽ�µ���NAS_SndUsimmAuthReq_Instance��
             ��SVLTEģʽ�µ���NAS_SndUsimmAuthReq
 �������  : ulSenderPid:���������pId��
             ucChallengeType:��Ȩ����
             pucRand:��Ȩ�����
             pucAutn:��Ȩ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
 2.��    ��  : 2013��11��30��
   ��    ��  : l65478
   �޸�����  : DTS2013121919477,�����յ������������Ȩ��Ϣ,����ѵ�һ����Ϣ����Ӧ��Ϊ�ڶ����������Ӧ,���¼�Ȩʧ��
 3.��    ��   : 2013��7��17��
   ��    ��   : y00245242
   �޸�����   : ����USIM�ӿ��޸ģ�����������
*****************************************************************************/
VOS_VOID NAS_USIMMAPI_AuthReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT8                           ucChallengeType,
    VOS_UINT8                          *pucRand,
    VOS_UINT8                          *pucAutn,
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          ulRet;

    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-22, begin */
    USIMM_CARDAPP_ENUM_UINT32           enAppType;
    NAS_USIMM_AUTH_DATA_STRU            stAuthData;

    PS_MEM_SET(&stAuthData, 0x00, sizeof(NAS_USIMM_AUTH_DATA_STRU));



    ulRet     = 0;
    enAppType = USIMM_GUTL_APP;


    if (AUTHENTICATION_REQ_GSM_CHALLENGE == ucChallengeType)
    {
        stAuthData.enAuthType = USIMM_2G_AUTH;
        PS_MEM_CPY(stAuthData.unAuthPara.st2GAuth.stRand.aucData,
                   pucRand,
                   NAS_MAX_AUTH_RAND_LEN);
        stAuthData.unAuthPara.st2GAuth.stRand.ucDataLen = NAS_MAX_AUTH_RAND_LEN;
    }
    else
    {
        stAuthData.enAuthType = USIMM_3G_AUTH;
        PS_MEM_CPY(stAuthData.unAuthPara.st3GAuth.stRand.aucData,
                   pucRand,
                   NAS_MAX_AUTH_RAND_LEN);
        stAuthData.unAuthPara.st3GAuth.stRand.ucDataLen = NAS_MAX_AUTH_RAND_LEN;
        /* skip the first byte since the first byte is length in Autn parameter */
        PS_MEM_CPY(stAuthData.unAuthPara.st3GAuth.stAutn.aucData,
                   (pucAutn + 1),
                   NAS_MAX_AUTH_AUTN_LEN);
        stAuthData.unAuthPara.st3GAuth.stAutn.ucDataLen = NAS_MAX_AUTH_AUTN_LEN;
    }

    /* ��USIMM���ͼ�Ȩ��Ϣ */
    ulRet = NAS_SndUsimmAuthReq(ulSenderPid, enAppType, &stAuthData, ucOpId);
    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-17, end */

    /* ���ÿ�ά�ɲ� */
    NAS_LogUsimmApiAuthReq(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, ucChallengeType, pucRand, pucAutn);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_USIMMAPI_PinReq
 ��������  : ��USIMMģ���USIMM_PinReq��USIMM_PinReq_Instance���з�װ��
             SVLTEģʽ�µ���USIMM_PinReq_Instance��
             ��SVLTEģʽ�µ���USIMM_PinReq
 �������  : ulSenderPid:���������pId��
             ucCmdType:��������
             ucPINType:PIN����
             pucOldPIN:PIN������
             pucNewPIN:��PIN������
 �������  : ��
 �� �� ֵ  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_USIMMAPI_PinReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT8                           ucCmdType,
    VOS_UINT8                           ucPINType,
    VOS_UINT8                          *pucOldPIN,
    VOS_UINT8                          *pucNewPIN
)
{
    VOS_UINT32                          ulRet;
    NAS_LOG_USIMM_PIN_INFO_STRU         stPinInfo;

    PS_MEM_SET(&stPinInfo, 0, sizeof(stPinInfo));

    stPinInfo.enCmdType = ucCmdType;
    stPinInfo.enPINType = ucPINType;

    if (VOS_NULL_PTR != pucOldPIN)
    {
        PS_MEM_CPY(stPinInfo.aucOldPIN, pucOldPIN, sizeof(stPinInfo.aucOldPIN));
    }

    if (VOS_NULL_PTR != pucNewPIN)
    {
        PS_MEM_CPY(stPinInfo.aucNewPIN, pucNewPIN, sizeof(stPinInfo.aucNewPIN));
    }

    /* ��USIMM����Pin��Ϣ */
    ulRet = NAS_SndUsimmPinReq(ulSenderPid, ucCmdType, ucPINType, pucOldPIN, pucNewPIN);

    /* ���ÿ�ά�ɲ� */
    NAS_LogUsimmApiPinReq(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, &stPinInfo);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : NAS_USIMMAPI_MaxEFRecordNumReq
 ��������  : ��USIMMģ���USIMM_MaxEFRecordNumReq��USIMM_MaxEFRecordNumReq_Instance���з�װ��
             SVLTEģʽ�µ���USIMM_MaxEFRecordNumReq_Instance��
             ��SVLTEģʽ�µ���USIMM_MaxEFRecordNumReq
 �������  : ulSenderPid:���������pId��
             enAppType  :usimmӦ������
             usEFid     :�ļ�id
 �������  : ��
 �� �� ֵ  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_USIMMAPI_MaxEFRecordNumReq(
    VOS_UINT32                          ulSenderPid,
    USIMM_CARDAPP_ENUM_UINT32           enAppType,
    VOS_UINT16                          usEFid
)
{
    VOS_UINT32                          ulRet;

    /* ��USIMM����QueryFile��Ϣ */
    ulRet = NAS_SndUsimmQueryFileReq(ulSenderPid, enAppType, usEFid);

    /* ���ÿ�ά�ɲ� */
    NAS_LogUsimmApiMaxEFRecordNumReq(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, enAppType, usEFid);

    return ulRet;
}

/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-29, begin */
/*****************************************************************************
 �� �� ��  : NAS_CovertUsimSrvTypeToUiccSrvType
 ��������  : ת��NAS�ڲ���(U)SIM service type��USIM�ӿ�UICC service type

 �������  : enUsimSrvType ���� NAS�ڲ������USIM service type
 �������  : enUiccSrvType ���� ����USIM�ӿڵ�service type��ַ
 �� �� ֵ  : VOS_FALSE  �޶�Ӧ��UICCҵ������
             VOS_TRUE   ��table���з���UICCҵ������

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��29��
   ��    ��   : y00245242
   �޸�����   : ����
 2.��    ��   : 2014��2��19��
   ��    ��   : s00217060
   �޸�����   : coverity����
*****************************************************************************/
VOS_UINT32  NAS_CovertUsimSrvTypeToUiccSrvType(
    NAS_USIMM_SERVICES_TYPE_ENUM_UINT32 enUsimSrvType,
    UICC_SERVICES_TYPE_ENUM_UINT32     *enUiccSrvType
)
{
    VOS_UINT32                          ulRst;
    VOS_UINT8                           ucCardType;

    ulRst = VOS_FALSE;

    /* Added by s00217060 for coverity����, 2014-02-19, begin */
    ucCardType  = USIMM_CARD_NOCARD;
    /* Added by s00217060 for coverity����, 2014-02-19, end */

    /* �˴���Ҫ����API��ȡ,��Ϊ��ʱ���ȫ�ֱ�����δ����ʱ��δ���� */
    (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucCardType);

    if (NAS_USIM_SVR_MAX_SERVICE > enUsimSrvType)
    {
        if (USIMM_CARD_SIM == ucCardType)
        {
            /* Get UICC SRV type from SIM SRV type */
            *enUiccSrvType = g_NasUsimSrviceTypeTab[enUsimSrvType].enSimSrvType;
        }
        else
        {
            /* Get UICC SRV type from USIM SRV type */
            *enUiccSrvType = g_NasUsimSrviceTypeTab[enUsimSrvType].enUsimSrvType;
        }

        if (NAS_USIM_SVR_NONE != *enUiccSrvType)
        {
            ulRst = VOS_TRUE;
        }
    }

    return ulRst;
}

/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-29, end */
/*****************************************************************************
 �� �� ��  : NAS_USIMMAPI_IsServiceAvailable
 ��������  : ��USIMMģ���USIMM_IsServiceAvailable��USIMM_IsServiceAvailable_Instance���з�װ��
             SVLTEģʽ�µ���USIMM_IsServiceAvailable_Instance��
             ��SVLTEģʽ�µ���USIMM_IsServiceAvailable
 �������  : enService:����ID��
 �������  : ��
 �� �� ֵ  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��7��22��
   ��    ��   : y00245242
   �޸�����   : �����µ�USIM�ӿ�
*****************************************************************************/
VOS_UINT32  NAS_USIMMAPI_IsServiceAvailable(
    NAS_USIMM_SERVICES_TYPE_ENUM_UINT32 enService
)
{
    VOS_UINT32                          ulRst;

    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-29, begin */
    UICC_SERVICES_TYPE_ENUM_UINT32      enUiccSrvType;

    if (VOS_FALSE == NAS_CovertUsimSrvTypeToUiccSrvType(enService, &enUiccSrvType))
    {
        return PS_USIM_SERVICE_NOT_AVAILIABLE;
    }

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRst = USIMM_IsServiceAvailable_Instance(MODEM_ID_0, enUiccSrvType);
        NAS_LogUsimmApiIsServiceAvailable(ulRst,
                                          NAS_USIMM_API_TYPE_WITH_INSTANCE, enUiccSrvType);
        return ulRst;
    }

    /* ������DSDA */
    ulRst = USIMM_IsServiceAvailable(enUiccSrvType);

    NAS_LogUsimmApiIsServiceAvailable(ulRst,
                                      NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, enUiccSrvType);
    /* Modified by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-29, end */

    return ulRst;
}

/*****************************************************************************
 �� �� ��  : NAS_USIMMAPI_IsTestCard
 ��������  : ��USIMMģ���USIMM_IsTestCard��USIMM_IsTestCard_Instance���з�װ��
             SVLTEģʽ�µ���USIMM_IsTestCard_Instance��
             ��SVLTEģʽ�µ���USIMM_IsTestCard
 �������  : ulSenderPid - ����pid
 �������  : ��
 �� �� ֵ  : VOS_TRUE:�ǣ�VOS_FALSE:��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_BOOL  NAS_USIMMAPI_IsTestCard(VOS_VOID)
{
    VOS_UINT32                          ulRet;

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRet = USIMM_IsTestCard_Instance(MODEM_ID_0);

        /* ��ά�ɲ� */
        NAS_LogUsimmApiIsTestCard(ulRet, NAS_USIMM_API_TYPE_WITH_INSTANCE);

        return ulRet;
    }

    /* ������DSDA */
    ulRet = USIMM_IsTestCard();

    /* ��ά�ɲ� */
    NAS_LogUsimmApiIsTestCard(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : NAS_USIMMAPI_GetPinStatus
 ��������  : ��USIMMģ���USIMM_GetPinStatus��USIMM_GetPinStatus_Instance���з�װ��
             SVLTEģʽ�µ���USIMM_GetPinStatus_Instance��
             ��SVLTEģʽ�µ���USIMM_GetPinStatus
 �������  : ulSenderPid:����pid
             pucType    :PIN����
 �������  : pucBeEnable:PIN�Ƿ���
             pucBeNeed  :PIN�Ƿ���Ҫ
             pucNum     :PINʣ�����
 �� �� ֵ  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��10��8��
   ��    ��   : w00242748
   �޸�����   : DTS2013090309349 ������Ϊ���Σ���ȡ�ó��α������ٸ�ֵ����ʱ
                �������ٽ��й�������
*****************************************************************************/
VOS_UINT32  NAS_USIMMAPI_GetPinStatus(
    VOS_UINT8                          *pucType,
    VOS_UINT8                          *pucBeEnable,
    VOS_UINT8                          *pucBeNeed,
    VOS_UINT8                          *pucNum
)
{
    VOS_UINT32                          ulRet;
    NAS_PIN_STATUS_STRU                 stPinStatus;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enUsimmApiType;

    if (VOS_NULL_PTR == pucType)
    {
        stPinStatus.ucPinType      = NAS_USIMM_PIN_TYPE_INVALID;
    }
    else
    {
        stPinStatus.ucPinType      = *pucType;
    }

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRet          = USIMM_GetPinStatus_Instance(MODEM_ID_0, pucType, pucBeEnable, pucBeNeed, pucNum);
        enUsimmApiType = NAS_USIMM_API_TYPE_WITH_INSTANCE;
    }
    else
    {
        /* ������DSDA */
        ulRet          = USIMM_GetPinStatus(pucType, pucBeEnable, pucBeNeed, pucNum);
        enUsimmApiType = NAS_USIMM_API_TYPE_WITHOUT_INSTANCE;
    }

    if (VOS_NULL_PTR == pucBeEnable)
    {
        stPinStatus.ucPinBeEnable  = NAS_USIMM_PIN_ENABLE_FLG_INVALID;
    }
    else
    {
        stPinStatus.ucPinBeEnable  = *pucBeEnable;
    }

    if (VOS_NULL_PTR == pucBeNeed)
    {
        stPinStatus.ucPinBeNeed    = NAS_USIMM_PIN_NEED_FLG_INVALID;
    }
    else
    {
        stPinStatus.ucPinBeNeed    = *pucBeNeed;
    }

    if (VOS_NULL_PTR == pucNum)
    {
        stPinStatus.ucPinRemainNum = NAS_USIMM_PIN_NUM_INVALID;
    }
    else
    {
        stPinStatus.ucPinRemainNum = *pucNum;
    }

    /* ��ά�ɲ� */
    NAS_LogUsimmApiGetPinStatus(ulRet, enUsimmApiType, &stPinStatus);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : NAS_USIMMAPI_GetCachedFile
 ��������  : ��USIMMģ���USIMM_GetCachedFile��USIMM_GetCachedFile_Instance���з�װ��
             SVLTEģʽ�µ���USIMM_GetCachedFile_Instance��
             ��SVLTEģʽ�µ���USIMM_GetCachedFile
 �������  : usFileID   :��ȡ�ļ���ID
             enAppType  :USIMM������
 �������  : pulDataLen :�����ļ������ݳ���
             ppucData   :�����ļ����ݵĵ�ַ
 �� �� ֵ  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_USIMMAPI_GetCachedFile(
    VOS_UINT32                          ulFileID,
    VOS_UINT32                         *pulDataLen,
    VOS_UINT8                         **ppucData,
    USIMM_CARDAPP_ENUM_UINT32           enAppType
)
{
    VOS_UINT32                          ulRet;

    VOS_CHAR                           *pucFilePathStr  = VOS_NULL_PTR;
    VOS_UINT32                          ulPathLength;

    ulRet = 0;
    ulPathLength    = 0;

    if (VOS_OK != USIMM_ChangeDefFileToPath(ulFileID, &pucFilePathStr))
    {
        return USIMM_API_FAILED;
    }

    /* �ļ�·�����ȱ��� */
    ulPathLength = VOS_StrLen(pucFilePathStr);
    if (0 == ulPathLength)
    {
        return USIMM_API_WRONG_PARA;
    }

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRet = USIMM_GetCachedFile_Instance(MODEM_ID_0, pucFilePathStr, pulDataLen, ppucData, enAppType);

        /* ���ÿ�ά�ɲ� */
        NAS_LogUsimmApiGetCachedFile(ulRet, NAS_USIMM_API_TYPE_WITH_INSTANCE, *pulDataLen, ppucData);

        return ulRet;
    }

    /* ������DSDA */
    ulRet = USIMM_GetCachedFile(pucFilePathStr, pulDataLen, ppucData, enAppType);

    /* ���ÿ�ά�ɲ� */
    NAS_LogUsimmApiGetCachedFile(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, *pulDataLen, ppucData);

    return ulRet;
}


/* Added by l00208543 for V9R1 STK����, 2013-07-24, begin */
/*****************************************************************************
 �� �� ��  : NAS_GetOamReceivePid
 ��������  : ��ȡ��oam���͵�receive pid
 �������  : ���շ�PID
 �������  : ��
 �� �� ֵ  : ����ת����Ľ��շ�PID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��24��
    ��    ��   : l00208543
    �޸�����   : STK������Ŀ����������

*****************************************************************************/
VOS_UINT32 NAS_GetOamReceivePid(VOS_UINT32 ulRcvPid)
{
    if (VOS_FALSE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        return ulRcvPid;
    }

    switch (ulRcvPid)
    {
        case MAPS_STK_PID:
            return I0_MAPS_STK_PID;

        case WUEPS_PID_USIM:
            return I0_WUEPS_PID_USIM;

        case MAPS_PB_PID:
            return I0_MAPS_PB_PID;

        default:
            return ulRcvPid;
    }
}
/* Added by l00208543 for V9R1 STK����, 2013-07-24, end */


/*****************************************************************************
 �� �� ��  : NAS_USIMMAPI_GetCardIMSI
 ��������  : ��USIMMģ���USIMM_GetCardIMSI��USIMM_GetCardIMSI_Instance���з�װ��
             SVLTEģʽ�µ���USIMM_GetCardIMSI_Instance��
             ��SVLTEģʽ�µ���USIMM_GetCardIMSI
 �������  : ��
 �������  : pucImsi :�洢�ļ�������
 �� �� ֵ  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_USIMMAPI_GetCardIMSI(
    VOS_UINT8                          *pucImsi
)
{
    VOS_UINT32                          ulRst;

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRst = USIMM_GetCardIMSI_Instance(MODEM_ID_0, pucImsi);
        NAS_LogUsimmApiGetCardIMSI(ulRst, NAS_USIMM_API_TYPE_WITH_INSTANCE, pucImsi);
        return ulRst;
    }

    /* ������DSDA */
    ulRst  = USIMM_GetCardIMSI(pucImsi);
    NAS_LogUsimmApiGetCardIMSI(ulRst, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, pucImsi);

    return ulRst;
}

/*****************************************************************************
 �� �� ��  : NAS_USIMMAPI_GetCardType
 ��������  : ��USIMMģ���USIMM_GetCardType��USIMM_GetCardType_Instance���з�װ��
             SVLTEģʽ�µ���USIMM_GetCardType_Instance��
             ��SVLTEģʽ�µ���USIMM_GetCardType
 �������  : ��
 �������  : pucCardStatus  :������
             pucCardType    :��״̬
 �� �� ֵ  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��10��8��
   ��    ��   : w00242748
   �޸�����   : DTS2013090309349 ������Ϊ���Σ���ȡ�ó��α������ٸ�ֵ����ʱ
                �������ٽ��й�������
 3.��    ��   : 2015��2��6��
   ��    ��   : h00313353
   �޸�����   : USIMM���ӿڵ���
*****************************************************************************/
VOS_UINT32 NAS_USIMMAPI_GetCardType(
    VOS_UINT8                          *pucCardStatus,
    VOS_UINT8                          *pucCardType
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucCardStatus;
    VOS_UINT16                          usCardType = 0X00;
    NAS_USIMM_API_TYPE_ENUM_UINT8       enUsimmApiType;

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRet          = USIMM_GetCardTypeByAppType_Instance(MODEM_ID_0, pucCardStatus, pucCardType, USIMM_GUTL_APP);
        enUsimmApiType = NAS_USIMM_API_TYPE_WITH_INSTANCE;
    }
    else
    {
        /* ������DSDA */
        ulRet          = USIMM_GetCardTypeByAppType(pucCardStatus, pucCardType, USIMM_GUTL_APP);
        enUsimmApiType = NAS_USIMM_API_TYPE_WITHOUT_INSTANCE;
    }

    /* ��ά�ɲ�ʱ����Ҫȡָ��ָ����������ݣ���ָ��ΪVOS_NULL_PTRʱ��ȡ���ݻ���������ڴ˱��� */
    if (VOS_NULL_PTR == pucCardStatus)
    {
        ucCardStatus = USIMM_CARD_SERVIC_BUTT;
    }
    else
    {
        ucCardStatus = *pucCardStatus;
    }

    if (VOS_NULL_PTR == pucCardType)
    {
        usCardType  = NAS_USIMM_CARD_TYPE_INVALID;
    }
    else
    {
        usCardType  = *pucCardType;
    }

    /* ���ÿ�ά�ɲ� */
    NAS_LogUsimmApiGetCardType(ulRet, enUsimmApiType, ucCardStatus, usCardType);

    return ulRet;
}


/*****************************************************************************
 �� �� ��  : NAS_USIMMAPI_BdnQuery
 ��������  : ��USIMMģ���USIMM_BdnQuery��USIMM_BdnQuery_Instance���з�װ��
             SVLTEģʽ�µ���USIMM_BdnQuery_Instance��
             ��SVLTEģʽ�µ���USIMM_BdnQuery
 �������  : ��
 �������  : pulState :BDN״̬
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_USIMMAPI_BdnQuery(
    VOS_UINT32                          *pulState
)
{
     /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        USIMM_BdnQuery_Instance(MODEM_ID_0, pulState);

        /* ���ÿ�ά�ɲ� */
        if (VOS_NULL_PTR != pulState)
        {
            NAS_LogUsimmApiBdnQuery(*pulState, NAS_USIMM_API_TYPE_WITH_INSTANCE);
        }

        return;
    }

    /* ������DSDA */
    USIMM_BdnQuery(pulState);

    /* ���ÿ�ά�ɲ� */
    if (VOS_NULL_PTR != pulState)
    {
        NAS_LogUsimmApiBdnQuery(*pulState, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_USIMMAPI_FdnQuery
 ��������  : ��USIMMģ���USIMM_FdnQuery��USIMM_FdnQuery_Instance���з�װ��
             SVLTEģʽ�µ���USIMM_FdnQuery_Instance��
             ��SVLTEģʽ�µ���USIMM_FdnQuery
 �������  : ��
 �������  : pulState :FDN״̬
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_USIMMAPI_FdnQuery(
    VOS_UINT32                         *pulUsimState,
    VOS_UINT32                         *pulCsimState
)
{
    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        USIMM_FdnQuery_Instance(MODEM_ID_0, pulUsimState, pulCsimState);

        /* ���ÿ�ά�ɲ� */
        if ((VOS_NULL_PTR != pulUsimState)
         && (VOS_NULL_PTR != pulCsimState))
        {
            NAS_LogUsimmApiFdnQuery(*pulUsimState, *pulCsimState, NAS_USIMM_API_TYPE_WITH_INSTANCE);
        }

        return;
    }

    /* ������DSDA */
    USIMM_FdnQuery(pulUsimState, pulCsimState);

    /* ���ÿ�ά�ɲ� */
    if ((VOS_NULL_PTR != pulUsimState)
     && (VOS_NULL_PTR != pulCsimState))
    {
        NAS_LogUsimmApiFdnQuery(*pulUsimState, *pulCsimState, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_USIMMAPI_GetPinRemainTime
 ��������  : ��USIMMģ���USIMM_GetPinRemainTime��USIMM_GetPinRemainTime_Instance���з�װ��
             SVLTEģʽ�µ���USIMM_GetPinRemainTime_Instance��
             ��SVLTEģʽ�µ���USIMM_GetPinRemainTime
 �������  : ��
 �������  : pstRemainTime :PINʣ��ʱ��
 �� �� ֵ  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  NAS_USIMMAPI_GetPinRemainTime(
    USIMM_PIN_REMAIN_STRU              *pstRemainTime
)
{
    VOS_UINT32                          ulRet;

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRet = USIMM_GetPinRemainTime_Instance(MODEM_ID_0, pstRemainTime);

        /* ���ÿ�ά�ɲ� */
        NAS_LogUsimmApiGetPinRemainTime(ulRet, NAS_USIMM_API_TYPE_WITH_INSTANCE, pstRemainTime);

        return ulRet;
    }

    /* ������DSDA */
    ulRet = USIMM_GetPinRemainTime(pstRemainTime);

    /* ���ÿ�ά�ɲ� */
    NAS_LogUsimmApiGetPinRemainTime(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, pstRemainTime);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : NAS_USIMMAPI_RestrictedAccessReq
 ��������  :
 �������  : ulSenderPid:���������pId��
             ulSendPara :���͵Ĳ�����
             pstData:��
 �������  : ��
 �� �� ֵ  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��02��15��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
 *****************************************************************************/
VOS_UINT32 NAS_USIMMAPI_RestrictedAccessReq(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulSendPara,
    USIMM_RACCESS_REQ_STRU             *pstData
)
{
    VOS_UINT32                          ulRslt;

    ulRslt = NAS_SndUsimmRestrictedAccessReq(ulSenderPid,
                                             ulSendPara,
                                             pstData);

    return ulRslt;
}

/*****************************************************************************
 �� �� ��  : NAS_USIMMAPI_RestrictedAccessReq
 ��������  : ����λ������
 �������  : ulSenderPid:���������pId��
             pstCMDDetail :Reset��Ϣ
             pstRstInfo:Reset��Ϣ��
 �������  : ��
 �� �� ֵ  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��02��15��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
 *****************************************************************************/
VOS_UINT32 NAS_USIMMAPI_ResetReq(
    VOS_UINT32                          ulSenderPid,
    USIMM_STK_COMMAND_DETAILS_STRU     *pstCMDDetail,
    USIMM_RESET_INFO_STRU              *pstRstInfo
)
{
    VOS_UINT32                          ulRslt;

    ulRslt = NAS_SndUsimmRefreshReq(ulSenderPid,
                                    pstCMDDetail,
                                    pstRstInfo);

    return ulRslt;
}


/*****************************************************************************
 �� �� ��  : NAS_PIHAPI_RegUsimCardStatusIndMsg
 ��������  : ��PIHģ���PIH_RegUsimCardStatusIndMsg��PIH_RegUsimCardStatusIndMsg_Instance���з�װ��
             SVLTEģʽ�µ���PIHAPI_RegUsimCardStatusIndMsg_Instance��
             ��SVLTEģʽ�µ���PIHAPI_RegUsimCardStatusIndMsg
 �������  : ulRegPID:ע���PID
 �������  : ��
 �� �� ֵ  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_PIHAPI_RegUsimCardStatusIndMsg(
    VOS_UINT32                          ulRegPID
)
{
    VOS_UINT32                          ulRet;

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRet = PIH_RegUsimCardStatusIndMsg_Instance(MODEM_ID_0, ulRegPID);

        /* ���ÿ�ά�ɲ� */
        NAS_LogPihApiRegUsimCardStatusInd(ulRet, NAS_USIMM_API_TYPE_WITH_INSTANCE, ulRegPID);

        return ulRet;
    }

    /* ������DSDA */
    ulRet = PIH_RegUsimCardStatusIndMsg(ulRegPID);


    /* ���ÿ�ά�ɲ� */
    NAS_LogPihApiRegUsimCardStatusInd(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, ulRegPID);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : NAS_PIHAPI_DeregUsimCardStatusIndMsg
 ��������  : ��PIHģ���PIH_DeregUsimCardStatusIndMsg��PIH_DeregUsimCardStatusIndMsg_Instance���з�װ��
             SVLTEģʽ�µ���PIHAPI_DeregUsimCardStatusIndMsg_Instance��
             ��SVLTEģʽ�µ���PIHAPI_DeregUsimCardStatusIndMsg
 �������  : ulDeregPID:ȥע���PID
 �������  : ��
 �� �� ֵ  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_PIHAPI_DeregUsimCardStatusIndMsg(
    VOS_UINT32                          ulDeregPID
)
{
    VOS_UINT32                          ulRet;

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRet = PIH_DeregUsimCardStatusIndMsg_Instance(MODEM_ID_0, ulDeregPID);

        /* ���ÿ�ά�ɲ� */
        NAS_LogPihApiDeregUsimCardStatusInd(ulRet, NAS_USIMM_API_TYPE_WITH_INSTANCE, ulDeregPID);

        return ulRet;
    }

    /* ������DSDA */
    ulRet = PIH_DeregUsimCardStatusIndMsg(ulDeregPID);

    /* ���ÿ�ά�ɲ� */
    NAS_LogPihApiDeregUsimCardStatusInd(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, ulDeregPID);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : NAS_PIHAPI_RegCardRefreshIndMsg
 ��������  : ��PIHģ���PIH_RegCardRefreshIndMsg��PIH_RegCardRefreshIndMsg_Instance���з�װ��
             SVLTEģʽ�µ���PIHAPI_RegCardRefreshIndMsg_Instance��
             ��SVLTEģʽ�µ���PIHAPI_RegCardRefreshIndMsg
 �������  : ulRegPID:ע���PID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_PIHAPI_RegCardRefreshIndMsg(
    VOS_UINT32                          ulRegPID
)
{
    VOS_UINT32                          ulRet;

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRet = PIH_RegCardRefreshIndMsg_Instance(MODEM_ID_0, ulRegPID);

        /* ���ÿ�ά�ɲ� */
        NAS_LogPihApiRegCardRefreshInd(ulRet, NAS_USIMM_API_TYPE_WITH_INSTANCE, ulRegPID);

        return;
    }

    /* ������DSDA */
    ulRet = PIH_RegCardRefreshIndMsg(ulRegPID);

    /* ���ÿ�ά�ɲ� */
    NAS_LogPihApiRegCardRefreshInd(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, ulRegPID);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_PIHAPI_DeregCardRefreshIndMsg
 ��������  : ��PIHģ���PIH_DeregCardRefreshIndMsg��PIH_DeregCardRefreshIndMsg_Instance���з�װ��
             SVLTEģʽ�µ���PIHAPI_DeregCardRefreshIndMsg_Instance��
             ��SVLTEģʽ�µ���PIHAPI_DeregCardRefreshIndMsg
 �������  : ulDerecPID:ȥע���PID
 �������  : ��
 �� �� ֵ  : USIMM_API_SUCCESS
             USIMM_API_FAILED
             USIMM_API_WRONG_PARA
             USIMM_API_NOTAVAILABLE
             USIMM_API_NOCARD
             USIMM_API_ALLOCMEM_FAILED
             USIMM_API_SENDMSG_FAILED
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_PIHAPI_DeregCardRefreshIndMsg(
    VOS_UINT32                          ulDeregPID
)
{
    VOS_UINT32                          ulRet;

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRet = PIH_DeregCardRefreshIndMsg_Instance(MODEM_ID_0, ulDeregPID);

        /* ���ÿ�ά�ɲ� */
        NAS_LogPihApiDeregCardRefreshInd(ulRet, NAS_USIMM_API_TYPE_WITH_INSTANCE, ulDeregPID);

        return ulRet;
    }

    /* ������DSDA */
    ulRet = PIH_DeregCardRefreshIndMsg(ulDeregPID);

    /* ���ÿ�ά�ɲ� */
    NAS_LogPihApiDeregCardRefreshInd(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, ulDeregPID);

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : NAS_PBAPI_GetEccNumber
 ��������  : ��PBģ���SI_PB_GetEccNumber��SI_PB_GetEccNumber_Instance���з�װ��
             SVLTEģʽ�µ���SI_PB_GetEccNumber_Instance��
             ��SVLTEģʽ�µ���SI_PB_GetEccNumber
 �������  : ��
 �������  : pstEccData:��ȡECCֵ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_PBAPI_GetEccNumber(
    SI_PB_ECC_DATA_STRU                *pstEccData
)
{
    VOS_UINT32                          ulRet;

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRet = SI_PB_GetEccNumber_Instance(MODEM_ID_0, pstEccData);

        /* ���ÿ�ά�ɲ� */
        NAS_LogPbApiGetEccNumber(ulRet, NAS_USIMM_API_TYPE_WITH_INSTANCE, pstEccData);

        return;
    }

    /* ������DSDA */
    ulRet = SI_PB_GetEccNumber(pstEccData);

    /* ���ÿ�ά�ɲ� */
    NAS_LogPbApiGetEccNumber(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, pstEccData);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_PBAPI_FdnNumCheck
 ��������  : ��STKģ���SI_PB_FdnNumCheck��SI_PB_FdnNumCheck_Instance���з�װ��
             SVLTEģʽ�µ���SI_PB_FdnNumCheck_Instance��
             ��SVLTEģʽ�µ���SI_PB_FdnNumCheck
 �������  : ulPid          ������FDN�����������Pid
             ulContextIndex :����������
             ulSendPara     :���Ͳ���
             pstFdnInfo     :FDN��Ϣ
 �������  : pstEccData:��ȡECCֵ
 �� �� ֵ  : 0:��Ч 1:��Ч
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_PBAPI_FdnNumCheck(
    VOS_UINT32                          ulPid,
    VOS_UINT32                          ulContextIndex,
    VOS_UINT32                          ulSendPara,
    SI_PB_FDN_NUM_STRU                 *pstFdnInfo
)
{
    VOS_UINT32                          ulRslt;

    ulRslt = NAS_SndUsimmFdnNumCheckReq(ulPid, ulContextIndex, ulSendPara, pstFdnInfo);

    /* ���ÿ�ά�ɲ� */
    NAS_LogPbApiFdnNumCheck(ulRslt, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, pstFdnInfo);

    return ulRslt;
}

/*****************************************************************************
 �� �� ��  : NAS_STKAPI_EnvelopeRsp_Decode
 ��������  : ��STKģ���SI_STK_EnvelopeRsp_Decode��SI_STK_EnvelopeRsp_Decode_Instance���з�װ��
             SVLTEģʽ�µ���SI_STK_EnvelopeRsp_Decode_Instance��
             ��SVLTEģʽ�µ���SI_STK_EnvelopeRsp_Decode
 �������  : enDataType: ������ŷ�������������
             ulDataLen : ��Ҫ��������ݳ���
             pucData   : ��Ҫ�������������
 �������  : pstRspData: ��������������
 �� �� ֵ  : 0:��Ч 1:��Ч
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_STKAPI_EnvelopeRsp_Decode(
    SI_STK_ENVELOPE_TYPE_UINT32         enDataType,
    VOS_UINT32                          ulDataLen,
    VOS_UINT8                          *pucCmdData,
    SI_STK_ENVELOPE_RSP_STRU           *pstRspData
)
{
    VOS_UINT32                          ulRslt;

    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulRslt = SI_STK_EnvelopeRsp_Decode_Instance(MODEM_ID_0, enDataType, ulDataLen, pucCmdData, pstRspData);

        /* ���ÿ�ά�ɲ� */
        NAS_LogStkApiEnvelopRspDecode(ulRslt, NAS_USIMM_API_TYPE_WITH_INSTANCE, pstRspData);

        return ulRslt;
    }

    /* ������DSDA */
    ulRslt = SI_STK_EnvelopeRsp_Decode(enDataType, ulDataLen, pucCmdData, pstRspData);

    /* ���ÿ�ά�ɲ� */
    NAS_LogStkApiEnvelopRspDecode(ulRslt, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, pstRspData);

    return ulRslt;

}

/*****************************************************************************
 �� �� ��  : NAS_STKAPI_EnvelopeRspDataFree
 ��������  : ��STKģ���SI_STK_EnvelopeRspDataFree��SI_STK_EnvelopeRspDataFree_Instance���з�װ��
             SVLTEģʽ�µ���SI_STK_EnvelopeRspDataFree_Instance��
             ��SVLTEģʽ�µ���SI_STK_EnvelopeRspDataFree
 �������  : pstData   : ���ӿ�����Ӧ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_STKAPI_EnvelopeRspDataFree(
    SI_STK_ENVELOPE_RSP_STRU           *pstData
)
{
    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        SI_STK_EnvelopeRspDataFree_Instance(MODEM_ID_0, pstData);

        /* ���ÿ�ά�ɲ� */
        NAS_LogStkApiEnvelopRspDataFree(NAS_USIMM_API_TYPE_WITH_INSTANCE, pstData);

        return;
    }

    /* ������DSDA */
    SI_STK_EnvelopeRspDataFree(pstData);

    /* ���ÿ�ά�ɲ� */
    NAS_LogStkApiEnvelopRspDataFree(NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, pstData);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_STKAPI_EnvelopeDownload
 ��������  : ��STKģ���SI_STK_EnvelopeDownload��SI_STK_EnvelopeDownload_Instance���з�װ��
             SVLTEģʽ�µ���SI_STK_EnvelopeDownload_Instance��
             ��SVLTEģʽ�µ���SI_STK_EnvelopeDownload
 �������  : ulSenderPid    : �����ߵ�PID
             usClientId     : ���Ͳ���
             pstENStru      : Envelope����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��6��26��
   ��    ��   : f62575
   �޸�����   : V9R1 STK����
 3.��    ��   : 2015��2��12��
   ��    ��   : h00313353
   �޸�����   : USIMM���ӿڵ���
*****************************************************************************/
VOS_UINT32 NAS_STKAPI_EnvelopeDownload(
    VOS_UINT32                          ulSenderPid,
    VOS_UINT32                          ulClientId,
    SI_STK_ENVELOPE_STRU               *pstENStru
)
{
    VOS_UINT32                          ulRslt;

    ulRslt = 0;


    /* ��USIMM����ReadFile��Ϣ */
    ulRslt =  NAS_SndUsimmEnvelopeDownloadReq(ulSenderPid, ulClientId, pstENStru);

    /* ���ÿ�ά�ɲ� */
    NAS_LogStkApiEnvelopDownload( ulRslt, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, ulClientId, pstENStru);

    return ulRslt;
}

/* Deleted by f62575 for V9R1 STK����, 2013-6-26, begin */
/*
    NAS_STKAPI_MtCallEvent
*/
/* Deleted by f62575 for V9R1 STK����, 2013-6-26, end */


/* Deleted by l00208543 for V9R1 STK����, 2013-7-13, begin */
/* Deleted by l00208543 for V9R1 STK����, 2013-7-13, end */

/*****************************************************************************
 �� �� ��  : NAS_USIMMAPI_DeactiveCardReq
 ��������  : ��USIMM_DeactiveCardReq���з�װ,������svlte
 �������  : ulSenderPid - ����pid
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��4��
   ��    ��   : z00161729
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 NAS_USIMMAPI_DeactiveCardReq(VOS_UINT32 ulSenderPid)
{
    VOS_UINT32                          ulRslt;

    ulRslt = NAS_SndUsimmDeactiveCardReq(ulSenderPid);

    /* ���ÿ�ά�ɲ� */
    NAS_LogUsimmApiDeactiveCardReq(ulRslt, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE);

    return ulRslt;
}

/*****************************************************************************
 �� �� ��  : NAS_STKAPI_CCResultInd
 ��������  : ��SI_STK_CCResultInd��SI_STK_CCResultInd_Instance���з�װ
 �������  : pstRspData - ָ��CALL CONTROL�Ľ��������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��13��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_STKAPI_CCResultInd(
    SI_STK_ENVELOPE_RSP_STRU           *pstRspData
)
{
    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        SI_STK_CCResultInd_Instance(MODEM_ID_0, pstRspData);

        /* ���ÿ�ά�ɲ� */
        NAS_LogSTKApiCCResultInd(NAS_USIMM_API_TYPE_WITH_INSTANCE, pstRspData);

        return;
    }

    /* ������DSDA */
    SI_STK_CCResultInd(pstRspData);

    /* ���ÿ�ά�ɲ� */
    NAS_LogSTKApiCCResultInd(NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, pstRspData);
}

/*****************************************************************************
 �� �� ��  : NAS_STKAPI_SMSCtrlResultInd
 ��������  : ��SI_STK_SMSCtrlResultInd��SI_STK_SMSCtrlResultInd_Instance���з�װ
 �������  : pstRspData - ָ��SMS CONTROL�Ľ��������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��6��13��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_STKAPI_SMSCtrlResultInd(
    SI_STK_ENVELOPE_RSP_STRU           *pstRspData
)
{
    /* SVLTE */
    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        SI_STK_SMSCtrlResultInd_Instance(MODEM_ID_0, pstRspData);

        /* ���ÿ�ά�ɲ� */
        NAS_LogSTKApiSMSCtrlResultInd(NAS_USIMM_API_TYPE_WITH_INSTANCE, pstRspData);

        return;
    }

    /* ������DSDA */
    SI_STK_SMSCtrlResultInd(pstRspData);

    /* ���ÿ�ά�ɲ� */
    NAS_LogSTKApiSMSCtrlResultInd(NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, pstRspData);
}

/*****************************************************************************
 �� �� ��  : NAS_VSIM_SetVsimCtrlFlg
 ��������  : ����NAS�����⿨��������
 �������  : ucVsimCtrlFlg - NAS�����⿨���ƹ��ܱ�־
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��8��29��
   ��    ��   : f62575
   �޸�����   : VSIM FEATURE

*****************************************************************************/
VOS_VOID NAS_VSIM_SetVsimCtrlFlg(
    VOS_UINT8                           ucVsimCtrlFlg
)
{
    g_stNasVsimInfo.ucVsimCtrlFlg = ucVsimCtrlFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_VSIM_ReadNvimVsimCfg
 ��������  : ��ȡen_Item_NAS_VSIM_CTRL_FEATURE���ڴ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��8��29��
   ��    ��   : f62575
   �޸�����   : VSIM FEATURE
*****************************************************************************/
VOS_VOID NAS_VSIM_ReadNvimVsimCfg(VOS_VOID)
{
    TAF_NVIM_VSIM_CFG_STRU              stVsimCfg;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLength;

    ulLength = 0;
    PS_MEM_SET(&stVsimCfg, 0, sizeof(stVsimCfg));

    (VOS_VOID)NV_GetLength(en_Item_NAS_VSIM_CTRL_FEATURE, &ulLength);

    ulRet = NV_Read(en_Item_NAS_VSIM_CTRL_FEATURE, &stVsimCfg, ulLength);
    /* NV���ȡʧ�ܣ�����֧��VSIM���Դ��� */
    if ((NV_OK != ulRet)
     || (VOS_TRUE != stVsimCfg.ucVsimCtrlFlg))
    {
        NAS_VSIM_SetVsimCtrlFlg(VOS_FALSE);
        return;
    }

    NAS_VSIM_SetVsimCtrlFlg(stVsimCfg.ucVsimCtrlFlg);

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_VSIM_InitVsimCfgInfo
 ��������  : VSIM���Գ�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��29��
    ��    ��   : f62575
    �޸�����   : VSIM FEATURE

*****************************************************************************/
VOS_VOID NAS_VSIM_InitVsimCfgInfo(VOS_VOID)
{
    NAS_VSIM_ReadNvimVsimCfg();

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_VSIM_GetVsimCtrlFlg
 ��������  : ��ȡNAS�����⿨��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  Ҫ��NAS����VSIM���ƣ�
             VOS_FALSE ��Ҫ��NAS����VSIM����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��29��
    ��    ��   : f62575
    �޸�����   : VSIM FEATURE

*****************************************************************************/
VOS_UINT8 NAS_VSIM_GetVsimCtrlFlg(VOS_VOID)
{
    return g_stNasVsimInfo.ucVsimCtrlFlg;
}

/*****************************************************************************
 �� �� ��  : NAS_VSIM_IsRequireVsimCtrl
 ��������  : ��ȡVSIM�����������ñ�־��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  ����VSIM��������
             VOS_FALSE ������VSIM��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��29��
    ��    ��   : f62575
    �޸�����   : VSIM FEATURE

*****************************************************************************/
VOS_UINT32 NAS_VSIM_IsRequireVsimCtrl(VOS_VOID)
{

    VOS_UINT32                          ulVsimModem;
    VOS_UINT8                           ucVsimCtrlFlg;

    if (VOS_TRUE == NAS_SNDUSIMM_IsSvlteSupported())
    {
        ulVsimModem     = USIMM_VsimIsActive_Instance(MODEM_ID_0);
    }
    else
    {
        ulVsimModem     = USIMM_VsimIsActive();
    }

    ucVsimCtrlFlg       = NAS_VSIM_GetVsimCtrlFlg();

    /* �˴���Ҫ�������ulVsimModem��ucVsimCtrlFlg���� */
    NAS_LogVsimIsRequireVsimCtrl(ulVsimModem, ucVsimCtrlFlg);

    /* MODEM��VSIM��MODEM��NAS��VSIM���Կ���������VSIM�������� */
    if ((VOS_TRUE == ulVsimModem)
     && (VOS_TRUE == ucVsimCtrlFlg))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-23, begin */
/*****************************************************************************
 �� �� ��  : NAS_PBAPI_QryECallNumber
 ��������  : ��STKģ���SI_PB_QryECallNumber��SI_PB_QryECallNumber_Instance���з�װ��
             SVLTEģʽ�µ���SI_PB_QryECallNumber_Instance��
             ��SVLTEģʽ�µ���SI_PB_QryECallNumber
 �������  : ulPid          �����Ͳ�ѯecall���������Pid
             enPbType       : �绰������
             ucListLen      : ָ�����ļ�������¼����
             pucList        : ָ�����ļ�������¼����
 �������  : ��
 �� �� ֵ  : 0:��Ч 1:��Ч
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_PBAPI_QryECallNumber(
    VOS_UINT32                          ulPid,
    SI_PB_STORAGE_ENUM_UINT32           enPbType,
    VOS_UINT8                           ucListLen,
    VOS_UINT8                          *pucList
)
{
    VOS_UINT32                          ulRslt;

    /* ������DSDA */
    ulRslt = NAS_SndUsimmEcallNumberQry(ulPid, enPbType, ucListLen, pucList);

    /* ���ÿ�ά�ɲ� */
    NAS_LogPbApiQryEcallNumber(ulRslt, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, enPbType, ucListLen, pucList);

    return;
}

/* Added by w00176964 for V3R3C60_eCall��Ŀ, 2014-4-23, end */

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)

/*****************************************************************************
 �� �� ��  : NAS_PBAPI_GetXeccNumber
 ��������  : ��PBģ���SI_PB_GetXeccNumber��SI_PB_GetXeccNumber_Instance���з�װ��
             SVLTEģʽ�µ���SI_PB_GetEccNumber_Instance��
             ��SVLTEģʽ�µ���SI_PB_GetEccNumber
 �������  : ��
 �������  : pstEccData:��ȡECCֵ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��07��28��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_PBAPI_GetXeccNumber(
    SI_PB_ECC_DATA_STRU                *pstEccData
)
{
    VOS_UINT32                          ulRet;

    /* ������DSDA */
    ulRet = SI_PB_GetXeccNumber(pstEccData);

    /* ���ÿ�ά�ɲ� */
    NAS_LogPbApiGetXeccNumber(ulRet, NAS_USIMM_API_TYPE_WITHOUT_INSTANCE, pstEccData);

    return;
}

#endif


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

