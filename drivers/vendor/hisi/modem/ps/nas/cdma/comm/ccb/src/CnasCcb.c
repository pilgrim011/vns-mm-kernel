/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasCcb.c
  �� �� ��   : ����
  ��    ��   : y00245242
  ��������   : 2014��06��27��
  ��������   : NAS 1x&evdo��ȫ�ֱ�������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��06��27��
    ��    ��   : y00245242
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "CnasCcb.h"
#include  "cas_1x_control_initialstate_nas_pif.h"
#include  "NasMntn.h"
#include  "msp_diag_comm.h"
#include  "Nas_Mem.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_CNAS_CCB_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

#if (FEATURE_ON == FEATURE_MULTI_MODEM)
CNAS_CCB_MODEM_PID_TAB_STRU        g_astCnasCcbModemPidTab[] = {{I0_UEPS_PID_MSCC,           I1_UEPS_PID_MSCC},
                                                                {I0_WUEPS_PID_TAF,           I1_WUEPS_PID_TAF},
                                                                {I0_UEPS_PID_XSMS,           I1_UEPS_PID_XSMS},
                                                                {I0_WUEPS_PID_USIM,          I1_WUEPS_PID_USIM}
                                                               };
#endif



/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
CNAS_CCB_CTX_STRU                       g_stCnasCcbCtx;




/*****************************************************************************
  3 ��������
*****************************************************************************/
/*lint -save -e958 */
/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetCcbCtx
 ��������  : ��ȡ��ǰCCb��CTX
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰCCB��CTX
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��15��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_CTX_STRU*  CNAS_CCB_GetCcbCtxAddr( VOS_VOID )
{
    return &(g_stCnasCcbCtx);
}


/*****************************************************************************
 �� �� ��  : CNAS_CCB_InitUIMID
 ��������  : ��ʼ��UIMID��ز���
 �������  : CNAS_CCB_UIMID_STRU                *pstUIMID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��30��
   ��    ��   : y00346957
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_InitUIMID(VOS_VOID)
{
    CNAS_CCB_UIMID_STRU                 *pstUIMID = VOS_NULL_PTR;
    VOS_UINT32                           i;

    pstUIMID = CNAS_CCB_GetUIMID();

    for (i = 0; i < CNAS_CCB_EFRUIMID_OCTET_LEN_EIGHT; i++)
    {
        pstUIMID->aucEFRUIMID[i] = 0xff;
    }

    /* the first byte EFRUIMID indicates the byte num of UIMID value,if read length fail,
        set the UIMID length to 0, namely invalid UIMID */
    pstUIMID->aucEFRUIMID[0] = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_InitEsnMeidMeInfo
 ��������  : ��ʼ��ESNMEIDME��ز���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��09��30��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_InitEsnMeidMeInfo(VOS_VOID)
{
    CNAS_CCB_ESNMEIDME_INFO_STRU       *pstEsnMeidMeInfo = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstEsnMeidMeInfo = CNAS_CCB_GetEsnMeidMeInfoAddr();

    for (i = 0; i < CNAS_CCB_ESN_OCTET_LEN; i++)
    {
        pstEsnMeidMeInfo->u.aucEsn[i] = 0xFF;
    }

    for (i = 0; i < CNAS_CCB_MEID_OCTET_LEN; i++)
    {
        pstEsnMeidMeInfo->u.aucMeid[i] = 0xFF;
    }

    pstEsnMeidMeInfo->enEsnMeidType = CNAS_CCB_ESN_MEID_TYPE_BUTT;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_InitHrpdAccessAuthInfo
 ��������  : ��ʼ��HrpdUppid��ز���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��09��30��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_InitHrpdAccessAuthInfo(VOS_VOID)
{
    CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU                    *pstHrpdAccessAuthInfo = VOS_NULL_PTR;
    VOS_UINT32                                              i;

    pstHrpdAccessAuthInfo     = CNAS_CCB_GetHrpdAccesAuthInfoAddr();

    NAS_MEM_SET_S(pstHrpdAccessAuthInfo, sizeof(CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU), 0, sizeof(CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU));

    for (i = 0; i < CNAS_CCB_MAX_AUTHDATA_USERNAME_LEN; i++)
    {
        pstHrpdAccessAuthInfo->aucAccessAuthUserName[i] = 0xFF;
    }

    pstHrpdAccessAuthInfo->ucAccessAuthAvailFlag  = VOS_FALSE;
    pstHrpdAccessAuthInfo->ucAccessAuthUserNameLen = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_InitCcbCtx
 ��������  : ��ʼ��CCB������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��15��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��5��30��
   ��    ��   : y00346957
   �޸�����   : ���ӶԿ���Ϣ�е�UIMID�ĳ�ʼ��

*****************************************************************************/
VOS_VOID CNAS_CCB_InitCcbCtx(VOS_VOID)
{
    CNAS_CCB_CTX_STRU                   *pstCcbCtx = VOS_NULL_PTR;

    pstCcbCtx = CNAS_CCB_GetCcbCtxAddr();

    NAS_MEM_SET_S(pstCcbCtx, sizeof(CNAS_CCB_CTX_STRU), 0, sizeof(CNAS_CCB_CTX_STRU));

    /* To Do: ������ʱ��ʼ��Ϊ��AS��ֵͬ6��������AS����NV��ʹ��NV����ֵ */
    pstCcbCtx->stNwInfo.ucPRevInUse                 = P_REV_IN_USE_6;

    pstCcbCtx->stCallInfoCfg.ucIsMtCallInRoamingAcc = VOS_TRUE;

    pstCcbCtx->stNwInfo.enCasSta    = CNAS_CCB_1X_CAS_STATE_BUTT;

    pstCcbCtx->stNwInfo.enCasSubSta    = CNAS_CCB_1X_CAS_SUB_STATE_ENUM_BUTT;
    pstCcbCtx->stNwInfo.enProtocolRev  = CNAS_CCB_1X_CAS_P_REV_ENUM_BUTT;

    pstCcbCtx->stCustomCfg.ucPowerOffCampOnCtrlFlg = VOS_FALSE;

    CNAS_CCB_InitHomeSidNidList(&(pstCcbCtx->stHomeSidNidList));

    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE, CNAS_CCB_1X_SO_TYPE_LOOPBACK);
    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE, CNAS_CCB_1X_SO_TYPE_VOICE);
    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE, CNAS_CCB_1X_SO_TYPE_PS);
    CNAS_CCB_Set1xCallState(CNAS_CCB_1X_CALL_STATE_IDLE, CNAS_CCB_1X_SO_TYPE_SMS);

    CNAS_CCB_Set1XRfAvailFlg(VOS_TRUE);

    CNAS_CCB_InitUIMID();

    CNAS_CCB_InitIccId();

    CNAS_CCB_SetCurrPsRatType(CNAS_CCB_PS_RATTYPE_NULL);
    CNAS_CCB_SetPrevRatType(CNAS_CCB_PS_RATTYPE_NULL);

    CNAS_CCB_InitMntnInfo(&(pstCcbCtx->stMntnInfo));

    /* ���õ�ǰ����������Ϊ0 */
    CNAS_CCB_Set1XCallExistCount((VOS_UINT8)VOS_FALSE);

    CNAS_CCB_SetHomeSidNidDependOnPrlFlg(VOS_FALSE);

    CNAS_CCB_InitCdmaStandardChannels(&(pstCcbCtx->stCdmaStandardChan));

    CNAS_CCB_InitEsnMeidMeInfo();
    CNAS_CCB_InitHrpdAccessAuthInfo();

    CNAS_CCB_SetCur1XSrvStatus(CNAS_CCB_SERVICE_STATUS_NO_SERVICE);
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_SetCsimCardStatus
 ��������  : ����CCB�б���Ŀ�״̬��Ϣ
 �������  : enCardStatus - ��״̬��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��14��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��06��04��
   ��    ��   : z00316370
   �޸�����   : ���ı�����

*****************************************************************************/
VOS_VOID CNAS_CCB_SetCsimCardStatus(
    CNAS_CCB_CARD_STATUS_ENUM_UINT8     enCsimCardStatus
)
{
    CNAS_CCB_GetCcbCtxAddr()->stCardInfo.enCsimCardStatus = enCsimCardStatus;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetCardStatus
 ��������  : ��ȡCCB�б���Ŀ�״̬��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : MML�б���Ŀ�״̬��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��14��
   ��    ��   : h00246512
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��06��04��
   ��    ��   : z00316370
   �޸�����   : ���ı�����

*****************************************************************************/
CNAS_CCB_CARD_STATUS_ENUM_UINT8 CNAS_CCB_GetCsimCardStatus( VOS_VOID )
{
    return CNAS_CCB_GetCcbCtxAddr()->stCardInfo.enCsimCardStatus;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetCasCardStatus
 ��������  : ��ȡ������ǰCAS�Ŀ�״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : rrc��ʽ��SIM��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��7��15��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16  CNAS_CCB_GetCasCardStatus(VOS_VOID)
{
    CNASITF_CARD_STATUS_ENUM_UINT16      enCardStatus;

    /* UIM������ */
    if (CNAS_CCB_CARD_STATUS_UIM_PRESENT  == CNAS_CCB_GetCsimCardStatus())
    {
        enCardStatus = CNASITF_CARD_STATUS_UIM_PRESENT;
    }
    /* CSIM������ */
    else if (CNAS_CCB_CARD_STATUS_CSIM_PRESENT  == CNAS_CCB_GetCsimCardStatus())
    {
        enCardStatus = CNASITF_CARD_STATUS_CSIM_PRESENT;
    }
    else
    {
        enCardStatus = CNASITF_CARD_STATUS_ABSENT;
    }

    return enCardStatus;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetCcbNwInfoAddr
 ��������  : ��ȡ������Ϣ��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ������Ϣ���׵�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��9��15��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_NW_INFO_STRU* CNAS_CCB_GetCcbNwInfoAddr(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stNwInfo);
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetConcurrentSupportedFlag
 ��������  : ��ȡ����ҵ��֧�ֱ�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --֧��
             VOS_FALSE --��֧��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��09��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_CCB_GetConcurrentSupportedFlag(VOS_VOID)
{
    /* ��ȡ����ҵ��֧�ֱ�־ */
    return (CNAS_CCB_GetCcbNwInfoAddr()->ucConcurrentSupported);
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_SetConcurrentSupportedFlag
 ��������  : �����վ����ҵ��֧�ֱ�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  --֧��
             VOS_FALSE --��֧��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��09��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_SetConcurrentSupportedFlag(
    VOS_UINT8                           ucConcurrentSupported
)
{
    /* ���»�վ����ҵ��֧�ֱ�־ */
    CNAS_CCB_GetCcbNwInfoAddr()->ucConcurrentSupported = ucConcurrentSupported;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetPRevInUse
 ��������  : ��ȡ��ǰʹ�õ�Э��汾
 �������  : ��
 �������  : ��
 �� �� ֵ  : ucPRevInUse -- ���ص�ǰ��Э��ʹ�ð汾

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��09��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_CCB_GetPRevInUse(VOS_VOID)
{
    /* ��ȡЭ��ʹ�ð汾 */
    return (CNAS_CCB_GetCcbNwInfoAddr()->ucPRevInUse);
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_SetPRevInUse
 ��������  : ���浱ǰʹ�õ�Э��汾��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ucPRevInUse -- ���ص�ǰ��Э��ʹ�ð汾

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��09��09��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_SetPRevInUse(
    VOS_UINT8                           ucPRevInUse
)
{
    /* ���µ�ǰʹ�õ�Э��汾�� */
    CNAS_CCB_GetCcbNwInfoAddr()->ucPRevInUse = ucPRevInUse;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetCasState
 ��������  : ��ȡ��ǰCAS��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : enCasSta -- ���ص�ǰCAS��״̬

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��18��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_1X_CAS_STATE_ENUM_UINT8 CNAS_CCB_GetCasState(VOS_VOID)
{
    /* ��ȡЭ��ʹ�ð汾 */
    return (CNAS_CCB_GetCcbNwInfoAddr()->enCasSta);
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_SetCasState
 ��������  : ���浱ǰCAS�ϱ���״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : enSta -- CAS�ϱ���״̬

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��18��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_SetCasState(
    CNAS_CCB_1X_CAS_STATE_ENUM_UINT8    enSta
)
{
    CNAS_CCB_GetCcbNwInfoAddr()->enCasSta = enSta;
}



/*****************************************************************************
 �� �� ��  : CNAS_CCB_SetMtCallInRoamingAccFlg
 ��������  : ����CCB�б����MtCallInRoamingAcc��Ϣ
 �������  : ucIsMtCallInRoamingAcc - VOS_UINT8
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��9��15��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_SetMtCallInRoamingAccFlg(
    VOS_UINT8                           ucIsMtCallInRoamingAcc
)
{
    CNAS_CCB_GetCcbCtxAddr()->stCallInfoCfg.ucIsMtCallInRoamingAcc = ucIsMtCallInRoamingAcc;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetMtCallInRoamingAccFlg
 ��������  : ��ȡCCB�б����MtCallInRoamingAcc��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : CCB�б����MtCallInRoamingAcc��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��7��14��
   ��    ��   : w00242748
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_CCB_GetMtCallInRoamingAccFlg( VOS_VOID )
{
    return CNAS_CCB_GetCcbCtxAddr()->stCallInfoCfg.ucIsMtCallInRoamingAcc;
}


/*****************************************************************************
 �� �� ��  : CNAS_CCB_SetPowerOffCampOnCtrlFlg
 ��������  : ���ùػ�פ�����Ʊ��
 �������  : �ػ�פ�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��10��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_SetPowerOffCampOnCtrlFlg(
    VOS_UINT8                           ucPowerOffCampOnFlg
)
{
    CNAS_CCB_GetCcbCtxAddr()->stCustomCfg.ucPowerOffCampOnCtrlFlg = ucPowerOffCampOnFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetPowerOffCampOnCtrlFlg
 ��������  : ��ȡ�ػ�פ�����Ʊ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ػ�פ�����Ʊ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��10��23��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_CCB_GetPowerOffCampOnCtrlFlg( VOS_VOID )
{
    return CNAS_CCB_GetCcbCtxAddr()->stCustomCfg.ucPowerOffCampOnCtrlFlg;
}


/*****************************************************************************
 �� �� ��  : CNAS_CCB_InitHomeSidNidList
 ��������  : ��ʼ��Home SID/NID list
 �������  : pstHomeSidNidList -- home sid/nid listָ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��1��3��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_InitHomeSidNidList(
    CNAS_CCB_1X_HOME_SID_NID_LIST_STRU *pstHomeSidNidList
)
{
    pstHomeSidNidList->ucSysNum = 0;

    NAS_MEM_SET_S(&pstHomeSidNidList->astHomeSidNid[0],
                  CNAS_CCB_MAX_HOME_SID_NID_LIST * sizeof(CNAS_CCB_1X_HOME_SID_NID_STRU),
                  0,
                  CNAS_CCB_MAX_HOME_SID_NID_LIST * sizeof(CNAS_CCB_1X_HOME_SID_NID_STRU));
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetHomeSidNidList
 ��������  : ��ȡHomeSidNid table�׵�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ����HomeSidNid table�׵�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��12��31��
   ��    ��   : h00313353
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_1X_HOME_SID_NID_LIST_STRU* CNAS_CCB_GetHomeSidNidList(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stHomeSidNidList);
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetCasSubState
 ��������  : ��ȡ��ǰCAS����״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : enCasSta -- ���ص�ǰCAS����״̬

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_1X_CAS_SUB_STATE_ENUM_UINT8 CNAS_CCB_GetCasSubState(VOS_VOID)
{
    /* ��ȡCAS��״̬ */
    return (CNAS_CCB_GetCcbNwInfoAddr()->enCasSubSta);
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_SetCasState
 ��������  : ���浱ǰCAS�ϱ�����״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : enSta -- CAS�ϱ���״̬

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_SetCasSubState(
    CNAS_CCB_1X_CAS_SUB_STATE_ENUM_UINT8                    enSubSta
)
{
    CNAS_CCB_GetCcbNwInfoAddr()->enCasSubSta = enSubSta;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetHighProRev
 ��������  : ��ȡ��ǰ�ֻ�֧�ֵ����Э��汾
 �������  : ��
 �������  : ��
 �� �� ֵ  : enProtocolRev -- ���ص�ǰ֧�ֵ�Э��汾

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_1X_CAS_P_REV_ENUM_UINT8 CNAS_CCB_GetHighProRev(VOS_VOID)
{
    /* ��ȡCAS��״̬ */
    return (CNAS_CCB_GetCcbNwInfoAddr()->enProtocolRev);
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_SetHighProRev
 ��������  : ���浱ǰ�ֻ�֧�ֵ����Э��汾
 �������  : ��
 �������  : ��
 �� �� ֵ  : enProtocolRev -- CAS�ϱ���Э��汾

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : z00316370
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_SetHighProRev(
    CNAS_CCB_1X_CAS_P_REV_ENUM_UINT8    enProtocolRev
)
{
    CNAS_CCB_GetCcbNwInfoAddr()->enProtocolRev = enProtocolRev;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_Get1xReturnCause
 ��������  : ��ȡCCB�б����1x��returnCauseֵ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��13��
    ��    ��   : m00312079
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8 CNAS_CCB_Get1xReturnCause(VOS_VOID)
{
    return CNAS_CCB_GetCcbCtxAddr()->en1xReturnCause;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_Set1xReturnCause
 ��������  : ����CCB�б����returnCauseֵ
 �������  : CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8   en1xReturnCause
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��13��
    ��    ��   : m00312079
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_Set1xReturnCause(
    CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8                     en1xReturnCause
)
{
    CNAS_CCB_GetCcbCtxAddr()->en1xReturnCause = en1xReturnCause;
}


/*****************************************************************************
 �� �� ��  : CNAS_CCB_Get1xVoiceCallState
 ��������  : ��ȡCCB�б����1X����״̬
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_CCB_1X_CALL_STATE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��21��
    ��    ��   : y00322978
    �޸�����   : ��ȡ����callstate��Ϣ
*****************************************************************************/
CNAS_CCB_1X_CALL_STATE_ENUM_UINT8 CNAS_CCB_Get1xVoiceCallState(VOS_VOID)
{
    VOS_UINT32                          ulIndex;

    for (ulIndex = 0; ulIndex < CNAS_CCB_MNTN_1X_CALL_STATE_MAX_NUM; ulIndex++)
    {
        if (CNAS_CCB_1X_SO_TYPE_VOICE == CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[ulIndex].en1xSoType)
        {
            return CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[ulIndex].en1xCallState;
        }
    }
    return CNAS_CCB_1X_CALL_STATE_IDLE;
}
/*****************************************************************************
 �� �� ��  : CNAS_CCB_Get1xPsCallState
 ��������  : ��ȡpsҵ��callstate��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_CCB_1X_CALL_STATE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��21��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_1X_CALL_STATE_ENUM_UINT8 CNAS_CCB_Get1xPsCallState(
    VOS_VOID
)
{
    VOS_UINT32                          ulIndex;

    for (ulIndex = 0; ulIndex < CNAS_CCB_MNTN_1X_CALL_STATE_MAX_NUM; ulIndex++)
    {
        if (CNAS_CCB_1X_SO_TYPE_PS == CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[ulIndex].en1xSoType)
        {
            return CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[ulIndex].en1xCallState;
        }
    }
    return CNAS_CCB_1X_CALL_STATE_IDLE;
}
/*****************************************************************************
 �� �� ��  : CNAS_CCB_Get1xPsCallState
 ��������  : ��ȡSMSҵ��callstate��Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_CCB_1X_CALL_STATE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��21��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_1X_CALL_STATE_ENUM_UINT8 CNAS_CCB_Get1xSmsCallState(
    VOS_VOID
)
{
    VOS_UINT32                          ulIndex;

    for (ulIndex = 0; ulIndex < CNAS_CCB_MNTN_1X_CALL_STATE_MAX_NUM; ulIndex++)
    {
        if (CNAS_CCB_1X_SO_TYPE_SMS== CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[ulIndex].en1xSoType)
        {
            return CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[ulIndex].en1xCallState;
        }
    }
    return CNAS_CCB_1X_CALL_STATE_IDLE;
}
/*****************************************************************************
 �� �� ��  : CNAS_CCB_Set1xCallState
 ��������  : ����CCB�б����1X����״̬
 �������  : CNAS_CCB_1X_CALL_STATE_ENUM_UINT8   en1xCallState
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��7��21��
    ��    ��   : y00322978
    �޸�����   : ��¼��ͬso��call state״̬
*****************************************************************************/
VOS_VOID CNAS_CCB_Set1xCallState(
    CNAS_CCB_1X_CALL_STATE_ENUM_UINT8                       en1xCallState,
    CNAS_CCB_1X_SO_TYPE_ENUM_UINT8                          en1xSoType
)
{
    switch (en1xSoType)
    {
        case CNAS_CCB_1X_SO_TYPE_VOICE:
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[0].en1xSoType    = en1xSoType;
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[0].en1xCallState = en1xCallState;
            break;
        case CNAS_CCB_1X_SO_TYPE_SMS:
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[1].en1xSoType    = en1xSoType;
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[1].en1xCallState = en1xCallState;
            break;
        case CNAS_CCB_1X_SO_TYPE_PS:
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[2].en1xSoType    = en1xSoType;
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[2].en1xCallState = en1xCallState;
            break;
        case CNAS_CCB_1X_SO_TYPE_LOOPBACK:
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[3].en1xSoType    = en1xSoType;
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[3].en1xCallState = en1xCallState;
            break;
        default :
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[3].en1xSoType    = en1xSoType;
            CNAS_CCB_GetCcbCtxAddr()->astMntn1xCallState[3].en1xCallState = en1xCallState;
    }


}




/*****************************************************************************
 �� �� ��  : CNAS_CCB_Set1XRfAvailFlg
 ��������  : ���õ�ǰXģ��Ƶ��Դ���ñ�־
 �������  : uc1XRfAvail: RF��Դ���ñ�־
             VOS_TRUE   : ����
             VOS_FALSE  : ������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_Set1XRfAvailFlg(
    VOS_UINT8                           uc1XRfAvailFlg
)
{
    CNAS_CCB_GetCcbCtxAddr()->stNwInfo.uc1XRfAvailFlg = uc1XRfAvailFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_Get1XRfAvailFlg
 ��������  : ��ȡ��ǰXģ��Ƶ��Դ���ñ�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
             VOS_TRUE   : ����
             VOS_FALSE  : ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��20��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_CCB_Get1XRfAvailFlg( VOS_VOID )
{
    return CNAS_CCB_GetCcbCtxAddr()->stNwInfo.uc1XRfAvailFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetUIMID
 ��������  : ��ȡCcbCtx��card info��UIMID
 �������  : ��
 �������  : ��
 �� �� ֵ  : UIMID�ṹ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��05��30��
   ��    ��   : y00346957
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_UIMID_STRU* CNAS_CCB_GetUIMID(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stCardInfo.stUIMID);
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetEsnMeidMeInfoAddr
 ��������  : ��ȡCcbCtx��card info��esn meid me
 �������  : ��
 �������  : ��
 �� �� ֵ  : esn meid me�ṹ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��09��30��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_ESNMEIDME_INFO_STRU* CNAS_CCB_GetEsnMeidMeInfoAddr(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stCardInfo.stEsnMeidMe);
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetHrpdAccesAuthInfoAddr
 ��������  : ��ȡCcbCtx��hrpd�����Ȩ�û���
 �������  : ��
 �������  : ��
 �� �� ֵ  : hrpd upp id�ṹ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��09��30��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_HRPD_ACCESS_AUTH_INFO_STRU* CNAS_CCB_GetHrpdAccesAuthInfoAddr(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stCardInfo.stHrpdAccessAuthInfo);
}


/*****************************************************************************
 �� �� ��  : CNAS_CCB_SetModemId
 ��������  : ������Cģ�Խӵ�modemId
 �������  : enModemId              : modemId
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_SetCdmaModeModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    CNAS_CCB_GetCcbCtxAddr()->stModemInfo.enCdmaModeModemId = enModemId;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetCdmaModeModemId
 ��������  : ��ȡ��Cģ�Խӵ�modemIds
 �������  : ��
 �������  : ��
 �� �� ֵ  : MODEM_ID_0:modem0
             MODEM_ID_1:modem1
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
MODEM_ID_ENUM_UINT16 CNAS_CCB_GetCdmaModeModemId( VOS_VOID )
{
    return CNAS_CCB_GetCcbCtxAddr()->stModemInfo.enCdmaModeModemId;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetPidFromModemId
 ��������  : ��ȡʵ�ʷ��͵�PID
 �������  : MODEM_ID_ENUM_UINT16                enModemId,
             VOS_UINT32                          ulRcvPid
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_CCB_ConvertPidBasedOnModemId(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT32                          ulRcvPid
)
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    VOS_UINT32                          i;

    /* modem 1��ulRcvPid��Ӧ��pid */
    if (MODEM_ID_0 != enModemId)
    {
        for (i = 0; i < (sizeof(g_astCnasCcbModemPidTab)/sizeof(CNAS_CCB_MODEM_PID_TAB_STRU)); i++)
        {
            if (ulRcvPid == g_astCnasCcbModemPidTab[i].ulModem0Pid)
            {
                return g_astCnasCcbModemPidTab[i].ulModem1Pid;
            }
        }

        /* ��������Ҳ�����Ӧ��PIDʱ���п�����Xģ�ڲ�ģ��䷢��Ϣ */
    }
#endif

    return ulRcvPid;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetModem0Pid
 ��������  : ��ȡmodem0��Ӧ��PID
 �������  : MODEM_ID_ENUM_UINT16                enModemId,
             VOS_UINT32                          ulRcvPid
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��22��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 CNAS_CCB_GetModem0Pid(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT32                          ulSenderPid
)
{
#if (FEATURE_ON == FEATURE_MULTI_MODEM)
    VOS_UINT32                          i;

    /* modem 1��ulRcvPid��Ӧ��pid */
    if (MODEM_ID_0 != enModemId)
    {
        for (i = 0; i < (sizeof(g_astCnasCcbModemPidTab)/sizeof(CNAS_CCB_MODEM_PID_TAB_STRU)); i++)
        {
            if (ulSenderPid == g_astCnasCcbModemPidTab[i].ulModem1Pid)
            {
                return g_astCnasCcbModemPidTab[i].ulModem0Pid;
            }
        }

        /* ��������Ҳ�����Ӧ��PIDʱ���п�����Xģ�ڲ�ģ��䷢��Ϣ */
    }
#endif

    return ulSenderPid;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetCardIccIdAddr
 ��������  : ��ȡCcbCtx�еĿ��б����IccId
 �������  : ��
 �������  : ��
 �� �� ֵ  : CcbCtx�е�IccId��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��06��03��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��19��
   ��    ��   : y00307564
   �޸�����   : DTS2015082403731�޸�
*****************************************************************************/
VOS_UINT8* CNAS_CCB_GetCardIccIdAddr(VOS_VOID)
{
    return CNAS_CCB_GetCcbCtxAddr()->stCardInfo.aucCardIccId;
}



/*****************************************************************************
 �� �� ��  : CNAS_CCB_InitIccId
 ��������  : ��ʼ��ICCID��ز���
 �������  : CNAS_CCB_UIMID_STRU                *pstUIMID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��06��08��
   ��    ��   : y00307564
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��10��19��
   ��    ��   : y00307564
   �޸�����   : DTS2015082403731�޸�
*****************************************************************************/
VOS_VOID CNAS_CCB_InitIccId(VOS_VOID)
{
    VOS_UINT8                           *pucCardIccId    = VOS_NULL_PTR;
    VOS_UINT32                           i;

    pucCardIccId = CNAS_CCB_GetCardIccIdAddr();

    for (i = 0; i < CNAS_CCB_ICCID_OCTET_LEN; i++)
    {
        pucCardIccId[i] = 0xFF;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_SetUsimCardStatus
 ��������  : ����CCB�б���Ŀ�״̬��Ϣ
 �������  : enCardStatus - ��״̬��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��06��04��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_SetUsimCardStatus(
    CNAS_CCB_CARD_STATUS_ENUM_UINT8     enUsimCardStatus
)
{
    CNAS_CCB_GetCcbCtxAddr()->stCardInfo.enUsimCardStatus = enUsimCardStatus;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetUsimCardStatus
 ��������  : ��ȡCCB�б���Ŀ�״̬��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : MML�б���Ŀ�״̬��Ϣ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2015��06��04��
   ��    ��   : z00316370
   �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_CARD_STATUS_ENUM_UINT8 CNAS_CCB_GetUsimCardStatus( VOS_VOID )
{
    return CNAS_CCB_GetCcbCtxAddr()->stCardInfo.enUsimCardStatus;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetCurrPsRatType
 ��������  : ��ȡ��ǰʹ�õ�ps rat type
 �������  : ��
 �������  : ��
 �� �� ֵ  : enPRevInUse -- ���ص�ǰ��ps rat type

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���
*****************************************************************************/
CNAS_CCB_PS_RATTYPE_ENUM_UINT32 CNAS_CCB_GetCurrPsRatType(VOS_VOID)
{
    /* ��ȡPS rat type */
    return (CNAS_CCB_GetCcbCtxAddr()->enCurrPsRatType);
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_SetCurrPsRatType
 ��������  : ���浱ǰʹ�õ�ps rat type
             (only ehsm can call this function when receiving ID_APS_EHSM_PS_RAT_TYPE_NOTIFY )

 �������  : ��
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_SetCurrPsRatType(
    CNAS_CCB_PS_RATTYPE_ENUM_UINT32    enPsRatType
)
{
    /* ���µ�ǰʹ�õ�ps rat type */
    CNAS_CCB_GetCcbCtxAddr()->enCurrPsRatType = enPsRatType;
}
/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetPrevPsRatType
 ��������  : get previous ps rat type
 �������  : ��
 �������  : ��
 �� �� ֵ  : enPRevInUse -- ���ص�ǰ��ps rat type

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���
*****************************************************************************/
CNAS_CCB_PS_RATTYPE_ENUM_UINT32 CNAS_CCB_GetPrevPsRatType(VOS_VOID)
{
    /* ��ȡPS rat type */
    return (CNAS_CCB_GetCcbCtxAddr()->enPrevPsRatType);
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_SetPrevRatType
 ��������  : set previous ps rat type
            (only ehsm can call this function when receiving ID_APS_EHSM_PS_RAT_TYPE_NOTIFY )
 �������  : ��
 �������  : ��
 �� �� ֵ  :

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��21��
    ��    ��   : f00279542
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_SetPrevRatType(
    CNAS_CCB_PS_RATTYPE_ENUM_UINT32     enPsRatType
)
{
    /* ���µ�ǰʹ�õ�ps rat type */
    CNAS_CCB_GetCcbCtxAddr()->enPrevPsRatType = enPsRatType;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_CovertReturnCause
 ��������  : ��CNAS��returnCauseö��CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8ת��Ϊ
             CNAS_CAS_1X_RETURN_CAUSE_ENUM_UINT8
 �������  : CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8   en1xReturnCause
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��13��
    ��    ��   : m00312079
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CAS_1X_RETURN_CAUSE_ENUM_UINT8 CNAS_CCB_CovertReturnCause(
    CNAS_CCB_1X_RETURN_CAUSE_ENUM_UINT8   enCnas1xReturnCause
)
{
    CNAS_CAS_1X_RETURN_CAUSE_ENUM_UINT8   enCasReturnCause;

    switch (enCnas1xReturnCause)
    {
        case CNAS_CCB_1X_RETURN_CAUSE_NORMAL_ACCESS :
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_NORMAL_ACCESS;
            break;

        case CNAS_CCB_1X_RETURN_CAUSE_SYSTEM_NOT_ACQ :
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_SYSTEM_NOT_FOUND;
            break;

        case CNAS_CCB_1X_RETURN_CAUSE_PROTOCOL_MISMATCH :
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_PROTOCOL_MISMATCH;
            break;

        case CNAS_CCB_1X_RETURN_CAUSE_REG_REJ :
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_REGISTRATION_REJECTION;
            break;

        case CNAS_CCB_1X_RETURN_CAUSE_WRONG_SID :
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_WRONG_SID;
            break;

        case CNAS_CCB_1X_RETURN_CAUSE_WRONG_NID :
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_WRONG_NID;
            break;

        default:
            enCasReturnCause = CNAS_CAS_1X_RETURN_CAUSE_BUTT;
            break;
    }

    return enCasReturnCause;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_Set1XMtCallExistFlg
 ��������  : ���õ�ǰ�Ƿ��ڱ���״̬�ı�ʶ
 �������  : uc1XCallExistCount: �Ƿ���ڱ��еı�ʶ
             VOS_TRUE   : ���д���
             VOS_FALSE  : ���в�����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_Set1XCallExistCount(
    VOS_UINT8                           uc1XCallExistCount
)
{
    CNAS_CCB_GetCcbCtxAddr()->uc1XCallExistCount = uc1XCallExistCount;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_Get1XMtCallExistFlg
 ��������  : ��ȡ��ǰ�Ƿ��ڱ���״̬�ı�ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
             VOS_TRUE   : ���ڱ���
             VOS_FALSE  : �����ڱ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��02��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_CCB_Get1XCallExistCount( VOS_VOID )
{
    return (CNAS_CCB_GetCcbCtxAddr()->uc1XCallExistCount);
}


/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetHomeSidNidMostPriFlg
 ��������  : ��ȡCCB�б����home sid/nid����ѡ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CNAS_CCB_GetHomeSidNidDependOnPrlFlg(VOS_VOID)
{
    return CNAS_CCB_GetCcbCtxAddr()->ucHomeSidNidDependOnPrlFlg;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_SetHomeSidNidMostPriFlg
 ��������  : ����CCB��HOME SID/NID�ǲ�������ѡ�ı��
 �������  : VOS_UINT8                           ucFlg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_SetHomeSidNidDependOnPrlFlg(
    VOS_UINT8                           ucFlg
)
{
    CNAS_CCB_GetCcbCtxAddr()->ucHomeSidNidDependOnPrlFlg = ucFlg;
}


/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetOperLockWhiteSidList
 ��������  : ��ȡCCB�б���İ������б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_CCB_OPER_LOCK_WHITE_SID_LIST_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_OPER_LOCK_SYS_WHITE_LIST_STRU* CNAS_CCB_GetOperLockSysWhiteList(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stOperLockSysWhiteList);
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetCTCCCustomizeFreqList
 ��������  : ��ȡCCB���й������Զ���Ƶ���б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��3��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_CTCC_CUSTOMIZE_FREQ_LIST_STRU* CNAS_CCB_GetCTCCCustomizeFreqList(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stCTCCCustInfo.stCustFreqList);
}


/*****************************************************************************
 �� �� ��  : CNAS_CCB_InitMntnInfo
 ��������  : ��ʼ��CCBȫ�ֱ���
 �������  : pstMntnInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��2��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_InitMntnInfo(
    CNAS_CCB_MNTN_CTX_STRU             *pstMntnInfo
)
{
    NAS_MEM_SET_S(pstMntnInfo, sizeof(CNAS_CCB_MNTN_CTX_STRU), 0x00, sizeof(CNAS_CCB_MNTN_CTX_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetCdmaStandardChannels
 ��������  : ��ȡCCB��cdma��׼Ƶ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��14��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU* CNAS_CCB_GetCdmaStandardChannels(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stCdmaStandardChan);
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_InitCdmaStandardChannels
 ��������  : ��ʼ��CCB��cdma��׼Ƶ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��14��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_InitCdmaStandardChannels(
    CNAS_CCB_CDMA_STANDARD_CHANNELS_STRU                   *pstCdmaStandardChan
)
{
    /* ��ʼ��Ĭ��Ƶ��ΪЭ�鶨���Ƶ�� */
    /* �ο�CDG 130 4.4.3�½�Table 4-8�еĶ��� */
    pstCdmaStandardChan->usPrimaryA   = 283;

    pstCdmaStandardChan->usSecondaryA = 691;

    pstCdmaStandardChan->usPrimaryB   = 384;

    pstCdmaStandardChan->usSecondaryB = 777;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_Judge1XSoType
 ��������  : SOת����Ӧ�ķ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : CNAS_CCB_1X_SO_TYPE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��21��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_1X_SO_TYPE_ENUM_UINT8 CNAS_CCB_ConvertSoToServiceType(
    CAS_CNAS_1X_SERVICE_OPTION_ENUM_UINT16                  en1xSo
)
{
    CNAS_CCB_1X_SO_TYPE_ENUM_UINT8      en1xSoType;

    switch (en1xSo)
    {
        case CAS_CNAS_1X_SO_3_EVRC:
        case CAS_CNAS_1X_SO_17_VOICE_13K:
        case CAS_CNAS_1X_SO_68_EVRC_B:
        case CAS_CNAS_1X_SO_73_EVRC_NW:
        case CAS_CNAS_1X_SO_18_OTASP:
#if (FEATURE_ON == FEATURE_CHINA_TELECOM_VOICE_ENCRYPT)
        case CAS_CNAS_1X_SO_32944_VOICE_ENCRYPT:
#endif
            en1xSoType =  CNAS_CCB_1X_SO_TYPE_VOICE;
            break;
        case CAS_CNAS_1X_SO_7_PPP_PKT_DATA:
        case CAS_CNAS_1X_SO_33_PPP_PKT_DATA_CDMA2K:
            en1xSoType =  CNAS_CCB_1X_SO_TYPE_PS;
            break;
        case CAS_CNAS_1X_SO_6_SMS_RS1:
        case CAS_CNAS_1X_SO_14_SMS_RS2:
            en1xSoType =  CNAS_CCB_1X_SO_TYPE_SMS;
            break;
        case CAS_CNAS_1X_SO_2_LOOPBACK:
        case CAS_CNAS_1X_SO_9_LOOPBACK:
        case CAS_CNAS_1X_SO_54_MARKOV:
        case CAS_CNAS_1X_SO_55_LOOPBACK:
        case CAS_CNAS_1X_SO_74_LOOPBACK:
        case CAS_CNAS_1X_SO_75_LOOPBACK:
            en1xSoType = CNAS_CCB_1X_SO_TYPE_LOOPBACK;
            break;

        case CAS_CNAS_1X_SO_35_LOC_SERV:
        case CAS_CNAS_1X_SO_36_LOC_SERV:
            en1xSoType = CNAS_CCB_1X_SO_TYPE_AGPS;
            break;

        default :
            en1xSoType =  CNAS_CCB_1X_SO_TYPE_LOOPBACK;
    }
    return en1xSoType;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetCdmaOhmFreq
 ��������  : ��ȡoverheaderƵ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_PRL_FREQENCY_CHANNEL_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��12��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_PRL_FREQENCY_CHANNEL_STRU* CNAS_CCB_GetCdmaOhmFreq(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->stOhmFreq);
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_SetCdmaOhmFreq
 ��������  : ����overheaderƵ��
 �������  : CNAS_PRL_FREQENCY_CHANNEL_STRU*
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��12��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_SetCdmaOhmFreq(
    CNAS_PRL_FREQENCY_CHANNEL_STRU     *pstOhmFreq
)
{
    CNAS_CCB_GetCcbCtxAddr()->stOhmFreq = *pstOhmFreq;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_ClearCdmaOhmFreq
 ��������  : ���cdma overheader��Ϣ�е�Ƶ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��12��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_ClearCdmaOhmFreq(VOS_VOID)
{
    CNAS_CCB_GetCcbCtxAddr()->stOhmFreq.enBandClass = 0;

    CNAS_CCB_GetCcbCtxAddr()->stOhmFreq.usChannel   = 0;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_Set1xSysInfo
 ��������  : CCBģ�����1xϵͳ��Ϣ������Sid/nid/band/freq��Ϣ
 �������  : VOS_UINT16                          usSid
             VOS_UINT16                          usNid
             VOS_UINT16                          usBandClass
             VOS_UINT16                          usChannel
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��27��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_Set1xSysInfo(
    VOS_UINT16                          usSid,
    VOS_UINT16                          usNid,
    VOS_UINT16                          usBandClass,
    VOS_UINT16                          usChannel
)
{
    CNAS_CCB_GetCcbNwInfoAddr()->st1xSysInfo.usSid       = usSid;
    CNAS_CCB_GetCcbNwInfoAddr()->st1xSysInfo.usNid       = usNid;
    CNAS_CCB_GetCcbNwInfoAddr()->st1xSysInfo.usBandClass = usBandClass;
    CNAS_CCB_GetCcbNwInfoAddr()->st1xSysInfo.usChannel   = usChannel;

    return;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_Get1xSysInfo
 ��������  : CCB�ṩ1Xϵͳ��Ϣ�Ĳ�ѯ�ӿ�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_CCB_1X_SYS_INFO_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��27��
    ��    ��   : g00261581
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_1X_SYS_INFO_STRU* CNAS_CCB_Get1xSysInfo(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbNwInfoAddr()->st1xSysInfo);
}


/*****************************************************************************
 �� �� ��  : CNAS_CCB_IsCurCallStateIdle
 ��������  : �ж�CCB�б����1X����״̬�Ƿ�Ϊ����̬,�������������г�Ա�ĺ���״̬��ΪIdleʱ��
             ����TRUE,�����������FALSE
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32: ����TRUE��ʾ��ǰû�к���ҵ�񣬷���FALSE��ʾ��ǰ���ں���ҵ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��30��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 CNAS_CCB_IsCurCallStateIdle( VOS_VOID )
{
    VOS_UINT32                          ulIndex;
    CNAS_CCB_CTX_STRU                  *pstCcbCtx   = VOS_NULL_PTR;

    pstCcbCtx                           = CNAS_CCB_GetCcbCtxAddr();

    for (ulIndex = 0; ulIndex < CNAS_CCB_MNTN_1X_CALL_STATE_MAX_NUM; ulIndex++)
    {
        if (CNAS_CCB_1X_CALL_STATE_IDLE != pstCcbCtx->astMntn1xCallState[ulIndex].en1xCallState)
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetCur1XSrvInfo
 ��������  : ��ȡ��ǰ1X������Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_CCB_1X_SRV_INFO_STRU* ��ǰ1X����״̬��Ϣ�ṹ��ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��01��26��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_1X_SRV_INFO_STRU* CNAS_CCB_GetCur1XSrvInfo(VOS_VOID)
{
    return &(CNAS_CCB_GetCcbCtxAddr()->st1XSrvInfo);
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_GetCur1XSrvStatus
 ��������  : ��ȡ��ǰ1X����״̬
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CNAS_CCB_SERVICE_STATUS_ENUM_UINT32 ��ǰ1X����״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��01��26��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
CNAS_CCB_SERVICE_STATUS_ENUM_UINT32 CNAS_CCB_GetCur1XSrvStatus(VOS_VOID)
{
    CNAS_CCB_1X_SRV_INFO_STRU          *pst1XSrvInfo = VOS_NULL_PTR;

    pst1XSrvInfo = CNAS_CCB_GetCur1XSrvInfo();

    return pst1XSrvInfo->enCurSrvStatus;
}

/*****************************************************************************
 �� �� ��  : CNAS_CCB_SetCur1XSrvStatus
 ��������  : ���õ�ǰ1X����״̬
 �������  : enSrvStatus -- ����״̬
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��01��26��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CNAS_CCB_SetCur1XSrvStatus(
    CNAS_CCB_SERVICE_STATUS_ENUM_UINT32 enSrvStatus
)
{
    CNAS_CCB_1X_SRV_INFO_STRU          *pst1XSrvInfo = VOS_NULL_PTR;

    pst1XSrvInfo = CNAS_CCB_GetCur1XSrvInfo();

    CNAS_INFO_LOG1(UEPS_PID_XSD, "CNAS_CCB_SetCur1XSrvStatus:Cur SrvStatus: ", (VOS_UINT32)pst1XSrvInfo->enCurSrvStatus);

    pst1XSrvInfo->enCurSrvStatus = enSrvStatus;

    CNAS_INFO_LOG1(UEPS_PID_XSD, "CNAS_CCB_SetCur1XSrvStatus:Set SrvStatus To: ", (VOS_UINT32)pst1XSrvInfo->enCurSrvStatus);

    return;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



