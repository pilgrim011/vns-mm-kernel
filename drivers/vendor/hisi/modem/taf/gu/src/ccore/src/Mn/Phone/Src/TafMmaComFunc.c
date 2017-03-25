/******************************************************************************

                  ��Ȩ���� (C), 2005-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMmaComFunc.c
  �� �� ��   : ����
  ��    ��   : f00179208
  ��������   : 2015��02��09��
  ����޸�   :
  ��������   : TafMmaComFunc.c�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��02��09��
    ��    ��   : f00179208
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "TafMmaCtx.h"
#include "TafMmaProcNvim.h"
#include "TafLog.h"
#include "NasUsimmApi.h"
#include "TafMmaMntn.h"
#include "TafMmaComFunc.h"

#include "TafSdcCtx.h"

#include "TafStdlib.h"

#include "NasComm.h"
#include "TafMmaSndApp.h"
#include "Taf_Status.h"


#include "ApsCdsInterface.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_COM_FUNC_C

/*****************************************************************************
  2 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

TAF_MMA_SESSION_STATUS_MAP_STRU          g_astTafMmaSessionStatusMapTbl[] =
{
    {HRPD_SESSION_STATUS_CLOSE,                    HSM_MMA_SESSION_STATUS_CLOSE},
    {HRPD_SESSION_STATUS_OPEN,                     HSM_MMA_SESSION_STATUS_OPEN},
    {HRPD_SESSION_STATUS_BUTT,                     HSM_MMA_SESSION_STATUS_BUTT},
};
TAF_MMA_CDMA_PHONE_MODE_MAP_STRU         g_astTafMmaCdmaPhoneModeMapTbl[] =
{
    {PHONE_MODE_MINI,                        TAF_SDC_PHONE_MODE_MINI},
    {PHONE_MODE_FULL,                        TAF_SDC_PHONE_MODE_FULL},
    {PHONE_MODE_TXOFF,                       TAF_SDC_PHONE_MODE_TXOFF},
    {PHONE_MODE_RXOFF,                       TAF_SDC_PHONE_MODE_RXOFF},
    {PHONE_MODE_RFOFF,                       TAF_SDC_PHONE_MODE_RFOFF},
    {PHONE_MODE_FT,                          TAF_SDC_PHONE_MODE_FT},
    {PHONE_MODE_RESET,                       TAF_SDC_PHONE_MODE_RESET},
    {PHONE_MODE_VDFMINI,                     TAF_SDC_PHONE_MODE_VDFMINI},
    {PHONE_MODE_POWEROFF,                    TAF_SDC_PHONE_MODE_POWEROFF},
    {PHONE_MODE_LOWPOWER,                    TAF_SDC_PHONE_MODE_LOWPOWER},
};
TAF_MMA_SYS_MODE_MAP_STRU          g_astTafMmaSysModeMapTbl[] =
{
    {SYS_MODE_GSM,                       TAF_SDC_SYS_MODE_GSM},
    {SYS_MODE_WCDMA,                     TAF_SDC_SYS_MODE_WCDMA},
    {SYS_MODE_LTE,                       TAF_SDC_SYS_MODE_LTE},
    {SYS_MODE_CDMA_1X,                   TAF_SDC_SYS_MODE_CDMA_1X},
    {SYS_MODE_EVDO,                      TAF_SDC_SYS_MODE_EVDO},
    {SYS_MODE_HYBRID,                    TAF_SDC_SYS_MODE_HYBRID},
    {SYS_MODE_SVLTE,                     TAF_SDC_SYS_MODE_SVLTE},
};

TAF_MMA_SYS_SUBMODE_MAP_STRU          g_astTafMmaSysSubModeMapTbl[] =
{
    {SYS_SUBMODE_NONE,                    TAF_SDC_SYS_SUBMODE_NONE},
    {SYS_SUBMODE_GSM,                     TAF_SDC_SYS_SUBMODE_GSM},
    {SYS_SUBMODE_GPRS,                    TAF_SDC_SYS_SUBMODE_GPRS},
    {SYS_SUBMODE_EDGE,                    TAF_SDC_SYS_SUBMODE_EDGE},
    {SYS_SUBMODE_WCDMA,                   TAF_SDC_SYS_SUBMODE_WCDMA},

    {SYS_SUBMODE_HSDPA,                   TAF_SDC_SYS_SUBMODE_HSDPA},
    {SYS_SUBMODE_HSUPA,                   TAF_SDC_SYS_SUBMODE_HSUPA},
    {SYS_SUBMODE_HSDPA_HSUPA,             TAF_SDC_SYS_SUBMODE_HSDPA_HSUPA},
    {SYS_SUBMODE_TD_SCDMA,                TAF_SDC_SYS_SUBMODE_TD_SCDMA},
    {SYS_SUBMODE_HSPA_PLUS,               TAF_SDC_SYS_SUBMODE_HSPA_PLUS},

    {SYS_SUBMODE_LTE,                     TAF_SDC_SYS_SUBMODE_LTE},
    {SYS_SUBMODE_DC_HSPA_PLUS,            TAF_SDC_SYS_SUBMODE_DC_HSPA_PLUS},
    {SYS_SUBMODE_DC_MIMO,                 TAF_SDC_SYS_SUBMODE_DC_MIMO},
    {SYS_SUBMODE_CDMA_1X,                 TAF_SDC_SYS_SUBMODE_CDMA_1X},
    {SYS_SUBMODE_EVDO_REL_0,              TAF_SDC_SYS_SUBMODE_EVDO_REL_0},

    {SYS_SUBMODE_EVDO_REL_A,              TAF_SDC_SYS_SUBMODE_EVDO_REL_A},
    {SYS_SUBMODE_HYBRID_EVDO_REL_0,       TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0},
    {SYS_SUBMODE_HYBRID_EVDO_REL_A,       TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_A},
    {SYS_SUBMODE_EHRPD,                   TAF_SDC_SYS_SUBMODE_EHRPD},

};

#endif

TAF_MMA_RAT_MODE_TYPE_ENUM_UINT8 g_aenRatModeTypeTab[TAF_MMA_RAT_SET_BUTT][TAF_MMA_RAT_SET_BUTT] =
{
                        /* --> L only               ,        -->GUL              ,        -->CL         */
    /* L only --> */    {TAF_MMA_RAT_MODE_GUL_TO_GUL , TAF_MMA_RAT_MODE_GUL_TO_GUL, TAF_MMA_RAT_MODE_GUL_TO_CL} ,
    /* GUL    --> */    {TAF_MMA_RAT_MODE_GUL_TO_GUL , TAF_MMA_RAT_MODE_GUL_TO_GUL, TAF_MMA_RAT_MODE_GUL_TO_CL},
    /* CL     --> */    {TAF_MMA_RAT_MODE_CL_TO_CL   , TAF_MMA_RAT_MODE_CL_TO_GUL , TAF_MMA_RAT_MODE_CL_TO_CL}
};


/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/

extern TAF_MMA_GLOBAL_VALUE_ST          gstMmaValue;

extern STATUS_CONTEXT_STRU              g_StatusContext;

/*****************************************************************************
  6 ����ʵ��
*****************************************************************************/

#if (FEATURE_IMS == FEATURE_ON)
/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdataVoiceDomain
 ��������  : ����������ѡ��
 �������  :
 �������  : ��
 �� �� ֵ  : VOS_TRUE
             VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ
*****************************************************************************/
VOS_UINT32 TAF_MMA_UpdataVoiceDomain(
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
)
{
    /* ���û�з����仯����Ҫ���� */
    if (enVoiceDomain == TAF_SDC_GetVoiceDomain())
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE != TAF_MMA_UpdataVoiceDomainNv((VOS_UINT32)enVoiceDomain))
    {
        /* warning��ӡ */
        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdataVoiceDomain: updata nv fail!");

        return VOS_FALSE;
    }

    /* ֻ����NV���³ɹ�����ܸ���ȫ�ֱ������������״̬��һ�� */
    TAF_SDC_SetVoiceDomain(enVoiceDomain);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateLteImsSupportFlag
 ��������  : ����LTE IMSʹ�ܱ�ʶ
 �������  : ucFlag ��ʶ
 �������  : ��
 �� �� ֵ  : VOS_TRUE
             VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��02��04��
   ��    ��   : f00179208
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_UpdateLteImsSupportFlag(
    VOS_UINT8                           ucFlag
)
{
    VOS_UINT8                           ucLteImsSupportFlag;
    VOS_UINT8                           ucLteEmsSupportFlag;

    ucLteImsSupportFlag = TAF_SDC_GetLteImsSupportFlag();
    ucLteEmsSupportFlag = TAF_SDC_GetLteEmsSupportFlag();

    /* ���û�з����仯����Ҫ���� */
    if ((ucFlag != ucLteImsSupportFlag)
     || (ucFlag != ucLteEmsSupportFlag))
    {
        if (VOS_TRUE != TAF_MMA_UpdateLteImsSupportNv(ucFlag))
        {
            /* warning��ӡ */
            TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateLteImsSupportFlag: updata Lte Ims support nv fail!");

            return VOS_FALSE;
        }

        TAF_SDC_SetLteImsSupportFlag(ucFlag);
        TAF_SDC_SetLteEmsSupportFlag(ucFlag);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_TransMsccImsStartResultToTafErrorCode
 ��������  : ��MSCC��IMS�򿪽��ֵת��ΪTAF��Ĵ�����
 �������  : enResult
 �������  : penErrorCode
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��15��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_TransMsccImsStartResultToTafErrorCode(
    NAS_MSCC_PIF_IMS_START_RESULT_ENUM_UINT32               enResult,
    TAF_ERROR_CODE_ENUM_UINT32                             *penErrorCode
)
{
    switch (enResult)
    {
        case NAS_MSCC_PIF_IMS_START_RESULT_SUCC:
            *penErrorCode = TAF_ERR_NO_ERROR;
            break;

        case NAS_MSCC_PIF_IMS_START_RESULT_TIMEOUT:
            *penErrorCode = TAF_ERR_IMS_STACK_TIMEOUT;
            break;

        default:
            *penErrorCode = TAF_ERR_UNSPECIFIED_ERROR;
            break;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_TransMsccImsStopResultToTafErrorCode
 ��������  : ��MSCC��IMS�رս��ֵת��ΪTAF��Ĵ�����
 �������  : enResult
 �������  : penErrorCode
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��15��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_TransMsccImsStopResultToTafErrorCode(
    NAS_MSCC_PIF_IMS_STOP_RESULT_ENUM_UINT32                enResult,
    TAF_ERROR_CODE_ENUM_UINT32                             *penErrorCode
)
{
    switch (enResult)
    {
        case NAS_MSCC_PIF_IMS_STOP_RESULT_SUCC:
            *penErrorCode = TAF_ERR_NO_ERROR;
            break;

        case NAS_MSCC_PIF_IMS_STOP_RESULT_TIMEOUT:
            *penErrorCode = TAF_ERR_IMS_STACK_TIMEOUT;
            break;

        default:
            *penErrorCode = TAF_ERR_UNSPECIFIED_ERROR;
            break;
    }

    return;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_MMA_SetSysCfgRatSetFlg
 ��������  : ����SYSCFG��RAT��־
 �������  : TAF_MMA_RAT_TYPE_ENUM_UINT8         enRatType
             VOS_UINT32                         *pucRatExistedFlg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��15��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SetSysCfgRatSetFlg(
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRatType,
    VOS_UINT32                         *pucRatExistedFlg
)
{
    if (TAF_MMA_RAT_GSM == enRatType)
    {
        *pucRatExistedFlg |= TAF_MMA_SYS_CFG_RAT_G_SET;
    }

    if (TAF_MMA_RAT_WCDMA == enRatType)
    {
        *pucRatExistedFlg |= TAF_MMA_SYS_CFG_RAT_W_SET;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (TAF_MMA_RAT_1X == enRatType)
    {
        *pucRatExistedFlg |= TAF_MMA_SYS_CFG_RAT_1X_SET;
    }

    if (TAF_MMA_RAT_HRPD == enRatType)
    {
        *pucRatExistedFlg |= TAF_MMA_SYS_CFG_RAT_DO_SET;
    }
#endif

}


/*****************************************************************************
 �� �� ��  : TAF_MMA_GetSysCfgRatFlag
 ��������  : ��ȡSYS CFG�����е�RAT����Ӧ��Flag ����
 �������  : TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��28��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_GetSysCfgRatFlag(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder,
    VOS_UINT32                         *pulRatExistedFlg
)
{
    VOS_UINT32                          ulPlatformSuppFlg;
    VOS_UINT32                          i;

    /* �ж��û����õĽ��뼼���Ƿ���ƽ̨֧�ֵĽ��뼼�� */
    for (i = 0; i < pstRatOrder->ucRatOrderNum; i++)
    {
        ulPlatformSuppFlg = TAF_MMA_IsPlatformSupportSpecUserRat(pstRatOrder->aenRatOrder[i]);

        /* �����֧�֣�����ʧ�ܣ����֧�֣����������һ�� */
        if (VOS_FALSE == ulPlatformSuppFlg)
        {
            return VOS_FALSE;
        }
        else
        {
            TAF_MMA_SetSysCfgRatSetFlg(pstRatOrder->aenRatOrder[i], pulRatExistedFlg);
        }
    }

    return VOS_TRUE;
}
/*****************************************************************************
 �� �� ��  : TAF_MMA_IsUserSettedSysCfgParaValid
 ��������  : �û����õ�syscfg������Ч�Լ��
 �������  : TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��8��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��4��10��
    ��    ��   : h00313353
    �޸�����   : SysCfg�ع�
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsUserSettedSysCfgParaValid(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                           ucCardType;
    VOS_UINT8                           ucRatBalancingEnableFlg;
#endif
    VOS_UINT32                          ulRatExistedFlg;

#if (FEATURE_ON == FEATURE_LTE)
    ucRatBalancingEnableFlg = TAF_MMA_GetRatBalancingEnableFlg();

    ucCardType = USIMM_CARD_NOCARD;
#endif

    ulRatExistedFlg = TAF_MMA_SYS_CFG_RAT_NONE_SET;

    /* ���뼼���û�����û�� */
    if (0 == pstSysCfgPara->stRatOrder.ucRatOrderNum)
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == TAF_MMA_GetSysCfgRatFlag(&pstSysCfgPara->stRatOrder, &ulRatExistedFlg))
    {
        return VOS_FALSE;
    }

    /* ���UE��֧��GSM�������ó�G��ģʱ������ʧ��;�����óɶ�ģʱ����MSCC��������ʱУ��ȥ��Gģ
        ���UE��֧��GSM�������ó�G��ģʱ������TAF_MMA_IsPlatformSupportSpecUserRat�����з���VOS_FALSE
     */

#if (FEATURE_ON == FEATURE_LTE)
    /* �����SIM���������ó�L��ģʱ������ʧ�ܣ������óɶ�ģʱ����MSCC��������ʱУ��ȥ��Lģ */
    if (VOS_TRUE == MN_MMA_IsLOnlyMode(&(pstSysCfgPara->stRatOrder)))
    {
        (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucCardType) ;

        if ( (USIMM_CARD_SIM == ucCardType)
          && (VOS_TRUE       == ucRatBalancingEnableFlg) )
        {
            return VOS_FALSE;
        }
    }
#endif

    /* 1x/HRPD��G/U�ĳ�ͻ�ж� */
    if (TAF_MMA_SYS_CFG_RAT_NONE_SET != (ulRatExistedFlg & TAF_MMA_SYS_CFG_RAT_C_SET))
    {
        if (TAF_MMA_SYS_CFG_RAT_NONE_SET != (ulRatExistedFlg & TAF_MMA_SYS_CFG_RAT_GU_SET))
        {
            return VOS_FALSE;
        }
    }

    /* �ж��û����õ�Ƶ���Ƿ���Ч */
    if (VOS_TRUE != TAF_MMA_IsUserSettedGuBandValid(&(pstSysCfgPara->stGuBand)))
    {
        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE != TAF_MMA_IsUserSettedLBandValid(&(pstSysCfgPara->stLBand)))
    {
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsUserSettedGuBandValid
 ��������  : �ж��û����õ�GUƵ���Ƿ���Ч
 �������  : TAF_USER_SET_PREF_BAND64           *pstGuBand
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��7��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_MMA_IsUserSettedGuBandValid(
    TAF_USER_SET_PREF_BAND64           *pstGuBand
)
{
    TAF_MMA_USER_BAND_SET_UN           uGuBand;
    TAF_MMA_UE_BAND_CAPA_ST           *pstBandCap = VOS_NULL_PTR;

    /* ��GUƵ�� pstSysCfgPara->stGuBand 64λת��Ϊ32λ�� */
    MN_MMA_Convert64BitBandTo32Bit(pstGuBand, &uGuBand.ulPrefBand);

    MN_MMA_ConvertGUFrequencyBand(&uGuBand.ulPrefBand);

    pstBandCap = TAF_MMA_GetUeSupportBandAddr();
    /* ��ģ���ģʱ,�û����õ�GU��L��Ƶ�α���Ҫ�뵱ǰUE֧�ֵ�GU��L��Ƶ�����ص�Ƶ��
       �����ֹ�û�����Ƶ����ȥ;��UE֧�ֵ�GU��L��Ƶ����Чʱ,������û����õ�Ƶ�� */
    if ((0 == (uGuBand.ulPrefBand & pstBandCap->ulUeGSptBand))
     && (0 != pstBandCap->ulUeGSptBand))
    {
        return VOS_FALSE;
    }

    if ((0 == (uGuBand.ulPrefBand & pstBandCap->ulUeWSptBand))
     && (0 != pstBandCap->ulUeWSptBand))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#if(FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_MMA_IsUserSettedLBandValid
 ��������  : �ж��û����õ�LƵ���Ƿ���Ч
 �������  : TAF_USER_SET_PREF_BAND64           *pstLBand
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��7��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_MMA_IsUserSettedLBandValid(
    TAF_USER_SET_PREF_BAND64           *pstLBand
)
{
    TAF_USER_SET_PREF_BAND64           *pstUeSupportLteBand = VOS_NULL_PTR;

    /* ��ȡ�û����õ�LBand */
    TAF_MMA_ConvertLteFrequencyBand(pstLBand);

    pstUeSupportLteBand = TAF_MMA_GetUeSupportLteBandAddr();

    if ((0 == (pstLBand->ulBandLow & pstUeSupportLteBand->ulBandLow))
     && (0 == (pstLBand->ulBandHigh & pstUeSupportLteBand->ulBandHigh))
     && ((0 != pstUeSupportLteBand->ulBandLow)
      || (0 != pstUeSupportLteBand->ulBandHigh)))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
#endif




/*****************************************************************************
 �� �� ��  : TAF_MMA_SetAttachAllowFlg
 ��������  : ����attach��������attach�Ƿ������־
 �������  : VOS_UINT32                          ulAttachType
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��18��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SetAttachAllowFlg(
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8     ulAttachType
)
{
    if (TAF_MMA_ATTACH_TYPE_GPRS == ulAttachType)
    {
        TAF_SDC_SetPsAttachAllowFlg(VOS_TRUE);
    }

    if (TAF_MMA_ATTACH_TYPE_IMSI == ulAttachType)
    {
        TAF_SDC_SetCsAttachAllowFlg(VOS_TRUE);
    }

    if (TAF_MMA_ATTACH_TYPE_GPRS_IMSI == ulAttachType)
    {
        TAF_SDC_SetPsAttachAllowFlg(VOS_TRUE);

        TAF_SDC_SetCsAttachAllowFlg(VOS_TRUE);
    }

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsRatOrderChange
 ��������  : ��鵱ǰ���������ϴε������Ƿ����仯
 �������  : pstCurrRat -- ��ǰ���õ�RAT
             pstLastRat -- �ϴ����õ�RAT

 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- RAT�����仯
             VOS_FALSE -- RATδ�����仯
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsRatOrderChange(
    TAF_MMA_RAT_ORDER_STRU             *pstCurrRat,
    TAF_MMA_RAT_ORDER_STRU             *pstLastRat
)
{
    if (pstCurrRat->ucRatOrderNum == pstLastRat->ucRatOrderNum)
    {
        if (0 == PS_MEM_CMP(&(pstCurrRat->aenRatOrder[0]),
                            &(pstLastRat->aenRatOrder[0]),
                            pstLastRat->ucRatOrderNum * sizeof(TAF_MMA_RAT_TYPE_ENUM_UINT8)))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_GetValidUserCfgEhplmnInfo
 ��������  : �����û����õ�EHPLMN��Ϣȡ��EHPLMN�б�
 �������  : VOS_UINT8                                               ucHplmnMncLen
             VOS_UINT8                                              *pucImsi
             VOS_UINT8                                              *pucEhplmnListNum
             TAF_SDC_PLMN_ID_STRU                                   *pstEhPlmnList
             NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU             *pstNvimCfgExtEhplmnInfo
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��23��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��12��
    ��    ��   : s00217060
    �޸�����   : DTS2015120901555:pclint�澯����

*****************************************************************************/
VOS_VOID TAF_MMA_GetValidUserCfgEhplmnInfo(
    VOS_UINT8                                               ucHplmnMncLen,
    VOS_UINT8                                              *pucImsi,
    VOS_UINT8                                              *pucEhplmnListNum,
    TAF_SDC_PLMN_ID_STRU                                   *pstEhPlmnList,
    NAS_MMC_NVIM_USER_CFG_EXT_EHPLMN_INFO_STRU             *pstNvimCfgExtEhplmnInfo
)
{
    VOS_UINT32                                  i;
    VOS_UINT32                                  j;
    VOS_UINT32                                  k;
    VOS_UINT32                                  ulUserCfgEhplmnNum;
    TAF_SDC_PLMN_ID_STRU                        stHPlmn;
    TAF_SDC_PLMN_ID_STRU                        stPlmn;

    ulUserCfgEhplmnNum = pstNvimCfgExtEhplmnInfo->ulNvimEhplmnNum;

    /* ��ֹ�ṹ������Խ�� */
    if (ulUserCfgEhplmnNum > NAS_MMC_NVIM_MAX_USER_CFG_EXT_EHPLMN_NUM)
    {
        ulUserCfgEhplmnNum = NAS_MMC_NVIM_MAX_USER_CFG_EXT_EHPLMN_NUM;
    }

    /* Ĭ���û����õ�EHplmn�ĸ���Ϊ0�� */
    *pucEhplmnListNum = 0;

    /* �ӵ�ǰ��IMSI��ȡ��home plmn */
    stHPlmn = TAF_SDC_GetImsiHomePlmn(pucImsi, ucHplmnMncLen);

    /* �����ǰ��IMSI�е�Home Plmn��astImsiPlmnList�У���ȡ��ǰ��EHplmn */
    for (j = 0 ; j < ulUserCfgEhplmnNum; j++)
    {
        for (i = 0 ; i < pstNvimCfgExtEhplmnInfo->astNvimEhplmnInfo[j].ucImsiPlmnListNum; i++)
        {
            /* �û����õ�IMSI plmn������BCCH��ʽ�� */
            TAF_SDC_ConvertSimPlmnToNasPLMN((TAF_SDC_SIM_FORMAT_PLMN_ID *)&(pstNvimCfgExtEhplmnInfo->astNvimEhplmnInfo[j].astImsiPlmnList[i]), &stPlmn);

            if (VOS_TRUE == TAF_SDC_CompareBcchPlmnwithSimPlmn(&stPlmn, &stHPlmn))
            {
                break;
            }
        }

        /* ��ǰNV�����õ�IMSI�б�����plmn��Hplmn��ͬ */
        if (i == pstNvimCfgExtEhplmnInfo->astNvimEhplmnInfo[j].ucImsiPlmnListNum)
        {
            continue;
        }

        *pucEhplmnListNum = pstNvimCfgExtEhplmnInfo->astNvimEhplmnInfo[j].ucEhplmnListNum;

        for (k = 0; k < pstNvimCfgExtEhplmnInfo->astNvimEhplmnInfo[j].ucEhplmnListNum; k++)
        {
            TAF_SDC_ConvertSimPlmnToNasPLMN((TAF_SDC_SIM_FORMAT_PLMN_ID *)&(pstNvimCfgExtEhplmnInfo->astNvimEhplmnInfo[j].astEhPlmnList[k]), &stPlmn);
            pstEhPlmnList[k] = stPlmn;
        }

        break;
    }

    return ;
}



VOS_VOID TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   enCdmaNetworkExist,
    TAF_SDC_SYS_MODE_ENUM_UINT8                            *penOutSysMode,
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                         *penOutSubMode,
    pTafSdcSysmodServiceRegStaUpdateFunc                   *ppTafSdcSysmodServiceRegStaUpdateFunc
)
{
    TAF_SDC_SYS_MODE_ENUM_UINT8         enGetSysmode;
    VOS_UINT32                          ulEntryCnt;
    VOS_UINT32                          i;

    TAF_SDC_MAP_SERVICE_STATUS_TO_SYSMODE_TLB_STRU     astSysModeSearchTable[] =
    {
        /* 1.status ind , 2.old/current mode, 3.dest mode, 4.dest submode */
        {TAF_SDC_HRPD_NETWORK_NOT_EXIST, TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_SUBMODE_NONE,              VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_NOT_EXIST, TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_SUBMODE_CDMA_1X,           VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_NOT_EXIST, TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_MODE_BUTT   , TAF_SDC_SYS_SUBMODE_NONE,              TAF_MMA_UpdateSerRegSta_HrpdToNone},
        {TAF_SDC_HRPD_NETWORK_NOT_EXIST, TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_SUBMODE_CDMA_1X,           TAT_MMA_UpdateSerRegSta_HybridTo1x},
        {TAF_SDC_HRPD_NETWORK_NOT_EXIST, TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_NOT_EXIST, TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},

        {TAF_SDC_HRPD_NETWORK_EXIST,     TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_SUBMODE_EVDO_REL_0,        VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_EXIST,     TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0, VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_EXIST,     TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_SUBMODE_EVDO_REL_0,        VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_EXIST,     TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0, VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_EXIST,     TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_SUBMODE_EVDO_REL_0,        VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_EXIST,     TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0, VOS_NULL_PTR},

        {TAF_SDC_1X_NETWORK_NOT_EXIST,   TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_SUBMODE_NONE,              VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_NOT_EXIST,   TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_SUBMODE_NONE,              TAF_MMA_UpdateSerRegSta_1xToNone},
        {TAF_SDC_1X_NETWORK_NOT_EXIST,   TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_SUBMODE_EVDO_REL_0,        VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_NOT_EXIST,   TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_SUBMODE_EVDO_REL_0,        TAF_MMA_UpdateSerRegSta_HybridToHrpd},
        {TAF_SDC_1X_NETWORK_NOT_EXIST,   TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_NOT_EXIST,   TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_SUBMODE_LTE,               TAF_MMA_UpdateSerRegSta_SvlteToLte},

        {TAF_SDC_1X_NETWORK_EXIST,       TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_SUBMODE_CDMA_1X,           VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_EXIST,       TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_SUBMODE_CDMA_1X,           VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_EXIST,       TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0, VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_EXIST,       TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0, VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_EXIST,       TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_EXIST,       TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},

        {TAF_SDC_LTE_NETWORK_EXIST,      TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_EXIST,      TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_EXIST,      TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_EXIST,      TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_EXIST,      TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_EXIST,      TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},

        {TAF_SDC_LTE_NETWORK_NOT_EXIST,  TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_SUBMODE_NONE,              VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_NOT_EXIST,  TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_SUBMODE_CDMA_1X,           VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_NOT_EXIST,  TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_SUBMODE_EVDO_REL_0,        VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_NOT_EXIST,  TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0, VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_NOT_EXIST,  TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_SUBMODE_BUTT,              TAF_MMA_UpdateSerRegSta_LteToNone},
        {TAF_SDC_LTE_NETWORK_NOT_EXIST,  TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_SUBMODE_CDMA_1X,           TAF_MMA_UpdateSerRegSta_SvlteTo1x},

    };

    /* initialize the output param and the const struct here */
    *penOutSysMode                          = TAF_SDC_SYS_MODE_BUTT;
    *penOutSubMode                          = TAF_SDC_SYS_SUBMODE_NONE;

    enGetSysmode = TAF_SDC_GetSysMode();
    ulEntryCnt   = sizeof(astSysModeSearchTable)/sizeof(TAF_SDC_MAP_SERVICE_STATUS_TO_SYSMODE_TLB_STRU);

    for (i = 0; i < ulEntryCnt; i++)
    {
        if ((enCdmaNetworkExist == astSysModeSearchTable[i].enCdmaNetworkExist)
         && (enGetSysmode == astSysModeSearchTable[i].enCurSysMode))
        {
            *penOutSysMode = astSysModeSearchTable[i].enNewSysMode;
            *penOutSubMode = astSysModeSearchTable[i].enNewSubMode;
            *ppTafSdcSysmodServiceRegStaUpdateFunc = astSysModeSearchTable[i].pfuncSysmodServiceRegStatusUpdate;
            return;
        }
    }
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_UpdateSerRegSta_HrpdToNone
 ��������  : ���´�HRPD��������HRPDʱ�ķ���״̬��ע��״̬
 �������  : TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enServiceStatus
             TAF_SDC_REG_STATUS_ENUM_UINT8       enRegStatus
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��1��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateSerRegSta_HrpdToNone(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* ����������ȫ�ֱ����������ϱ��Ļ���ͨ��Get��ʽ����ȡ�ϵ�״̬ */
    pstSrvInfo->bitOpPsSrvSta  = VOS_TRUE;
    pstSrvInfo->bitOpPsRegSta  = VOS_TRUE;
    pstSrvInfo->bitOpSrvSta    = VOS_TRUE;
    pstSrvInfo->bitOpSrvDomain = VOS_TRUE;

    pstSrvInfo->enPsSrvSta     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enPsRegSta     = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstSrvInfo->enSrvSta       = TAF_SDC_REPORT_SRVSTA_NO_SERVICE;
    pstSrvInfo->enSrvDomain    = TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN;
}


/*****************************************************************************
 �� �� ��  : TAT_SDC_UpdateSerRegSta_HybridTo1x
 ��������  : ���´�Hybrid��1xʱ�ķ���״̬��ע��״̬
 �������  : TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enServiceStatus
             TAF_SDC_REG_STATUS_ENUM_UINT8       enRegStatus
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��1��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAT_MMA_UpdateSerRegSta_HybridTo1x(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* ����������ȫ�ֱ����������ϱ��Ļ���ͨ��Get��ʽ����ȡ�ϵ�״̬ */
    pstSrvInfo->bitOpPsSrvSta = VOS_TRUE;
    pstSrvInfo->bitOpPsRegSta = VOS_TRUE;

    pstSrvInfo->enPsSrvSta    = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enPsRegSta    = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_UpdateSerRegSta_1xToNone
 ��������  : ���´�1X��Noneʱ�ķ���״̬��ע��״̬
 �������  : TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enServiceStatus
             TAF_SDC_REG_STATUS_ENUM_UINT8       enRegStatus
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��1��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateSerRegSta_1xToNone(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* ����������ȫ�ֱ����������ϱ��Ļ���ͨ��Get��ʽ����ȡ�ϵ�״̬ */
    pstSrvInfo->bitOpCsSrvSta  = VOS_TRUE;
    pstSrvInfo->bitOpCsRegSta  = VOS_TRUE;
    pstSrvInfo->bitOpSrvSta    = VOS_TRUE;
    pstSrvInfo->bitOpSrvDomain = VOS_TRUE;

    pstSrvInfo->enCsSrvSta     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enCsRegSta     = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstSrvInfo->enSrvSta       = TAF_SDC_REPORT_SRVSTA_NO_SERVICE;
    pstSrvInfo->enSrvDomain    = TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_UpdateSerRegSta_HybridToHrpd
 ��������  : ���´�Hybrid��HRPDʱ�ķ���״̬��ע��״̬
 �������  : TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enServiceStatus
             TAF_SDC_REG_STATUS_ENUM_UINT8       enRegStatus
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��1��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateSerRegSta_HybridToHrpd(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* ����������ȫ�ֱ����������ϱ��Ļ���ͨ��Get��ʽ����ȡ�ϵ�״̬ */
    pstSrvInfo->bitOpCsSrvSta  = VOS_TRUE;
    pstSrvInfo->bitOpCsRegSta  = VOS_TRUE;
    pstSrvInfo->bitOpSrvDomain = VOS_TRUE;

    pstSrvInfo->enCsSrvSta     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enCsRegSta     = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstSrvInfo->enSrvDomain    = TAF_SDC_SERVICE_DOMAIN_PS;

}

/*****************************************************************************
 �� �� ��  : TAF_SDC_UpdateSerRegSta_SvlteToLte
 ��������  : ���´�svlte��lteʱ�ķ���״̬��ע��״̬
 �������  : TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enServiceStatus
             TAF_SDC_REG_STATUS_ENUM_UINT8       enRegStatus
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��1��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateSerRegSta_SvlteToLte(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* ����������ȫ�ֱ����������ϱ��Ļ���ͨ��Get��ʽ����ȡ�ϵ�״̬ */
    pstSrvInfo->bitOpCsSrvSta  = VOS_TRUE;
    pstSrvInfo->bitOpCsRegSta  = VOS_TRUE;
    pstSrvInfo->bitOpSrvDomain = VOS_TRUE;

    pstSrvInfo->enCsSrvSta     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enCsRegSta     = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstSrvInfo->enSrvDomain    = TAF_SDC_SERVICE_DOMAIN_PS;
}

/*****************************************************************************
 �� �� ��  : TAF_SDC_UpdateSerRegSta_LteToNone
 ��������  : ���´�lte��noneʱ�ķ���״̬��ע��״̬
 �������  : TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enServiceStatus
             TAF_SDC_REG_STATUS_ENUM_UINT8       enRegStatus
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��1��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateSerRegSta_LteToNone(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* ����������ȫ�ֱ����������ϱ��Ļ���ͨ��Get��ʽ����ȡ�ϵ�״̬ */
    pstSrvInfo->bitOpPsSrvSta  = VOS_TRUE;
    pstSrvInfo->bitOpPsRegSta  = VOS_TRUE;
    pstSrvInfo->bitOpSrvSta    = VOS_TRUE;
    pstSrvInfo->bitOpSrvDomain = VOS_TRUE;

    pstSrvInfo->enPsSrvSta     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enPsRegSta     = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstSrvInfo->enSrvSta       = TAF_SDC_REPORT_SRVSTA_NO_SERVICE;
    pstSrvInfo->enSrvDomain    = TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN;

}

/*****************************************************************************
 �� �� ��  : TAF_SDC_UpdateSerRegSta_SvlteTo1x
 ��������  : ���´�svlte��1xʱ�ķ���״̬��ע��״̬
 �������  : TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enServiceStatus
             TAF_SDC_REG_STATUS_ENUM_UINT8       enRegStatus
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��1��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateSerRegSta_SvlteTo1x(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* ����������ȫ�ֱ����������ϱ��Ļ���ͨ��Get��ʽ����ȡ�ϵ�״̬ */
    pstSrvInfo->bitOpPsSrvSta = VOS_TRUE;
    pstSrvInfo->bitOpPsRegSta = VOS_TRUE;

    pstSrvInfo->enPsSrvSta    = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enPsRegSta    = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateSrvRegSta_Main
 ��������  : ���·���״̬����״̬
 �������  : TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo,
             TAF_PH_ACCESS_TECH_ENUM_UINT8       enAct
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��1��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��10��21��
    ��    ��   : l00324781
    �޸�����   : CDMA Iteration 18�޸�
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateSrvRegSta_Main(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo,
    TAF_PH_ACCESS_TECH_ENUM_UINT8       enAct
)
{
    if (VOS_TRUE == pstSrvInfo->bitOpCsSrvSta)
    {
        TAF_SDC_SetCsServiceStatus(pstSrvInfo->enCsSrvSta);
    }

    if (VOS_TRUE == pstSrvInfo->bitOpPsSrvSta)
    {
        TAF_SDC_SetPsServiceStatus(pstSrvInfo->enPsSrvSta);
    }

    if (VOS_TRUE == pstSrvInfo->bitOpSrvDomain)
    {
        TAF_SDC_SetServiceDomain(pstSrvInfo->enSrvDomain);
    }

    if (VOS_TRUE == pstSrvInfo->bitOpSrvSta)
    {
        TAF_SDC_SetServiceStatus(pstSrvInfo->enSrvSta);
    }

    /* �������״̬�仯�Ѿ�������ʱ����ע��״̬�Ͳ���Ҫ�ټ�飬
      ��Ӧ��ע��״̬�Ѿ���������£���ʱ����ʱ����ټ��ע��״̬�Ƿ��ϱ� */
    if (VOS_TRUE == pstSrvInfo->bitOpCsRegSta)
    {
        TAF_MMA_Report1xCregStatus(pstSrvInfo->enCsRegSta);
    }

    if (VOS_TRUE == pstSrvInfo->bitOpPsRegSta)
    {
        TAF_MMA_ReportPsRegStatusInClMode(pstSrvInfo->enPsRegSta);
    }

    if (VOS_TRUE == pstSrvInfo->bitOpSrvSta)
    {
        /* CLģʽ�µķ���״̬�ϱ����Ϊ2��������ʹ��bitOpCsRegSta��bitOpPsRegSta����
            bitOpCsRegSta �� bitOpCsSrvStaͬ������
            bitOpPsRegSta �� bitOpPsSrvStaͬ������
        */
        if (VOS_TRUE == pstSrvInfo->bitOpCsRegSta)
        {
            TAF_MMA_Report1xServiceState();
        }

        if (VOS_TRUE == pstSrvInfo->bitOpPsRegSta)
        {
            TAF_MMA_ReportHrpdAndLteServiceState();
        }
    }

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ChgSysModeAndSrvRegSta
 ��������  : �ú������ڸ���SYS MODE��ע�����״̬
 �������  : TAF_PH_ACCESS_TECH_ENUM_UINT8                           enAct
             TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode
             TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enSubMode
             pTafSdcSysmodServiceRegStaUpdateFunc                    pFuncTafSdcSysmodServiceRegStaUpdate
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��4��
    ��    ��   : w00242748
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ChgSysModeAndSrvRegSta(
    TAF_PH_ACCESS_TECH_ENUM_UINT8                           enAct,
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode,
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enSubMode,
    pTafSdcSysmodServiceRegStaUpdateFunc                    pFuncTafSdcSysmodServiceRegStaUpdate
)
{
    TAF_SDC_SRV_REG_INFO_STRU                               stSrvRegInfo;

    PS_MEM_SET(&stSrvRegInfo, 0x00, sizeof(stSrvRegInfo));

    /* ����״̬��ʱ��ά�ɲ� */
    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_ENTER);

    /* ^MODE�����ϱ����� */
    Mma_ModeChgReport(enSysMode, enSubMode);

    /* ����MMAά����Mode/SubMode */
    TAF_SDC_SetSysMode(enSysMode);

    TAF_SDC_SetSysSubMode(enSubMode);

    /* ִ�и��·���״̬��ע��״̬���� */
    if (VOS_NULL_PTR != pFuncTafSdcSysmodServiceRegStaUpdate)
    {
        pFuncTafSdcSysmodServiceRegStaUpdate(&stSrvRegInfo);

        /* �жϷ���״̬��ע��״̬�Ƿ�仯���仯�Ļ������ϱ� */
        TAF_MMA_UpdateSrvRegSta_Main(&stSrvRegInfo, enAct);
    }

    TAF_MMA_LogCLDelayRptSrvStatusCtx(TAF_MMA_LOG_CL_DELAY_REPORT_CTX_TYPE_EXIT);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_MapHsmSessionStatus
 ��������  : cdma session map table convert
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��6��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_MMA_MapHsmSessionStatus(
    HSM_MMA_SESSION_STATUS_ENUM_UINT8  enSessionStatus
)
{
    TAF_MMA_SESSION_STATUS_MAP_STRU    *pstSessionStatusMapPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulSesionStatusMapTblSize;
    VOS_UINT32                          ulCnt;

    pstSessionStatusMapPtr = TAF_MMA_SESSION_STATUS_MAP_TBL_PTR();
    ulSesionStatusMapTblSize = TAF_MMA_SESSION_STATUS_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulSesionStatusMapTblSize; ulCnt++)
    {
        if (pstSessionStatusMapPtr[ulCnt].enHsmSessionStatus == enSessionStatus)
        {
            return pstSessionStatusMapPtr[ulCnt].enMmaSessionStatus;
        }
    }

    return HSM_MMA_SESSION_STATUS_BUTT;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_MapCdmaPhoneMode
 ��������  : map phone mode for om ind
 �������  : enPhoneMode �ֻ�ģʽ
 �������  : ��
 �� �� ֵ  : NAS_OM_MMA_PHONE_MODE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��10��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_MMA_MapCdmaPhoneMode(
    TAF_SDC_PHONE_MODE_ENUM_UINT8       enPhoneMode
)
{
    TAF_MMA_CDMA_PHONE_MODE_MAP_STRU   *pstCdmaPhoneModeMapPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulCdmaPhoneModeMapTblSize;
    VOS_UINT32                          ulCnt;

    pstCdmaPhoneModeMapPtr = TAF_MMA_CDMA_PHONE_MODE_MAP_TBL_PTR();
    ulCdmaPhoneModeMapTblSize = TAF_MMA_CDMA_PHONE_MODE_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulCdmaPhoneModeMapTblSize; ulCnt++)
    {
        if (pstCdmaPhoneModeMapPtr[ulCnt].enTafCdmaPhoneMode == enPhoneMode)
        {
            return pstCdmaPhoneModeMapPtr[ulCnt].enNasOmCdmaPhoneMode;
        }
    }
    return PHONE_MODE_BUTT;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_MapSysMode
 ��������  : map sys mode for om ind
 �������  : enSysMode פ��ϵͳ����ģʽ
 �������  : ��
 �� �� ֵ  : NAS_OM_MMA_SYS_MODE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��10��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_MMA_MapSysMode(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
)
{
    TAF_MMA_SYS_MODE_MAP_STRU          *pstSysModeMapPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulSysModeMapTblSize;
    VOS_UINT32                          ulCnt;

    pstSysModeMapPtr = TAF_MMA_SYS_MODE_MAP_TBL_PTR();
    ulSysModeMapTblSize = TAF_MMA_SYS_MODE_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulSysModeMapTblSize; ulCnt++)
    {
        if (pstSysModeMapPtr[ulCnt].enTafCdmaSysMode == enSysMode)
        {
            return pstSysModeMapPtr[ulCnt].enNasOmCdmaSysMode;
        }
    }
    return SYS_MODE_BUTT;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_MapSubSysMode
 ��������  : map sub sys mode for om ind
 �������  : TAF_SDC_SYS_SUBMODE_ENUM_UINT8 enSysSubMode  פ���������ϵͳģʽ
 �������  : ��
 �� �� ֵ  : NAS_OM_MMA_SYS_SUBMODE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��10��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_MMA_MapSysSubMode(
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enSysSubMode
)
{
    TAF_MMA_SYS_SUBMODE_MAP_STRU       *pstSysSubModeMapPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulSysSubModeMapTblSize;
    VOS_UINT32                          ulCnt;

    pstSysSubModeMapPtr = TAF_MMA_SYS_SUBMODE_MAP_TBL_PTR();
    ulSysSubModeMapTblSize = TAF_MMA_SYS_SUBMODE_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulSysSubModeMapTblSize; ulCnt++)
    {
        if (pstSysSubModeMapPtr[ulCnt].enTafSysSubMode == enSysSubMode)
        {
            return pstSysSubModeMapPtr[ulCnt].enNasOmSysSubMode;
        }
    }

    return NAS_OM_MMA_SYS_SUBMODE_BUTT;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_MapCdataBearStatus
 ��������  : ӳ��PPP״̬�ϱ�
 �������  : TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8                     enBearStatus
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��20��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_MMA_MapCdataBearStatus(
    TAF_PS_CDATA_BEAR_STATUS_ENUM_UINT8                     enBearStatus
)
{
    NAS_OM_MMA_PPP_STATUS_ENUM_UINT8                        enPppStatus;

    enPppStatus = PPP_STATUS_INACTIVE;

    if (TAF_PS_CDATA_BEAR_STATUS_ACTIVE == enBearStatus)
    {
        enPppStatus = PPP_STATUS_ACTIVE;
    }
    else if (TAF_PS_CDATA_BEAR_STATUS_IDLE == enBearStatus)
    {
        enPppStatus = PPP_STATUS_IDLE;
    }
    else if (TAF_PS_CDATA_BEAR_STATUS_SUSPEND == enBearStatus)
    {
        enPppStatus = PPP_STATUS_IDLE;
    }
    else
    {
        enPppStatus = PPP_STATUS_INACTIVE;
    }
    return enPppStatus;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_ConvertMeidToUl
 ��������  : ��meid 56bitת��Ϊ����uint32��
 �������  : VOS_UINT8                          *pucMeid,
             VOS_UINT32                          ulMeid,
             VOS_UINT32                          ulMeidCnt
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��25��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ConvertMeidToUl(
    VOS_UINT8                          *pucMeid,
    VOS_UINT32                         *pMeid,
    VOS_UINT32                         *pMeidCnt
)
{
    VOS_UINT8                           aucMeid[NAS_OM_MMA_MEID_OCTET_NUM] = {0};
    VOS_UINT32                          ulMeid;
    VOS_UINT32                          ulMeidCnt;

    PS_MEM_CPY(aucMeid, pucMeid, NAS_OM_MMA_MEID_OCTET_NUM);
    ulMeid    = (((VOS_UINT32)aucMeid[0] << TAF_SDC_MOVEMENT_16_BITS) & 0x00ff0000)
               |(((VOS_UINT32)aucMeid[1] << TAF_SDC_MOVEMENT_8_BITS) & 0x0000ff00)
               |( (VOS_UINT32)aucMeid[2] & 0x000000ff);
    ulMeidCnt = (((VOS_UINT32)aucMeid[3] << TAF_SDC_MOVEMENT_24_BITS) & 0xff000000)
               |(((VOS_UINT32)aucMeid[4] << TAF_SDC_MOVEMENT_16_BITS) & 0x00ff0000)
               |(((VOS_UINT32)aucMeid[5] << TAF_SDC_MOVEMENT_8_BITS) & 0x0000ff00)
               |( (VOS_UINT32)aucMeid[6] & 0x000000ff);

    *pMeid = ulMeid;
    *pMeidCnt = ulMeidCnt;

}
/*****************************************************************************
 �� �� ��  : TAF_MMA_ConvertUimidToUl
 ��������  : ��RUIMIDת��Ϊ����32λ�����ϱ�
 �������  : pucUimid
 �������  : VOS_UINT32                         *pulUimidHigh,
             VOS_UINT32                         *pulUimidLow
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��14��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ConvertUimidToUl(
    VOS_UINT8                          *pucUimid,
    VOS_UINT32                         *pulUimidHigh,
    VOS_UINT32                         *pulUimidLow
)
{
    VOS_UINT8                           aucUimid[TAF_SDC_EFRUIMID_OCTET_LEN_EIGHT] = {0};
    VOS_UINT32                          ulUimidHigh;
    VOS_UINT32                          ulUimidLow;

    if ((VOS_NULL_PTR == pucUimid) || ((TAF_SDC_EFRUIMID_OCTET_LEN_EIGHT - 1) < pucUimid[0]))
    {
        return ;
    }

    PS_MEM_CPY(aucUimid, pucUimid, TAF_SDC_EFRUIMID_OCTET_LEN_EIGHT);
    ulUimidHigh = (((VOS_UINT32)aucUimid[4] << TAF_SDC_MOVEMENT_24_BITS) & 0xff000000)
                 |(((VOS_UINT32)aucUimid[3] << TAF_SDC_MOVEMENT_16_BITS) & 0x00ff0000)
                 |(((VOS_UINT32)aucUimid[2] << TAF_SDC_MOVEMENT_8_BITS) & 0x0000ff00)
                 |( (VOS_UINT32)aucUimid[1] & 0x000000ff);
    ulUimidLow  = ((((VOS_UINT32)aucUimid[7] << TAF_SDC_MOVEMENT_16_BITS) & 0x00ff0000)
                 |(((VOS_UINT32)aucUimid[6] << TAF_SDC_MOVEMENT_8_BITS) & 0x0000ff00)
                 |( (VOS_UINT32)aucUimid[5] & 0x000000ff));


    *pulUimidHigh = ulUimidHigh;
    *pulUimidLow  = ulUimidLow;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ConvertImsiToUl
 ��������  : ��RUIMIDת��Ϊ����32λ�����ϱ�
 �������  : pucImsi
 �������  : VOS_UINT32                         *pulImsiHigh,
             VOS_UINT32                         *pulImsiLow
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��14��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ConvertImsiToUl(
    VOS_UINT8                          *pucImsi,
    VOS_UINT32                         *pulImsiHigh,
    VOS_UINT32                         *pulImsiLow
)
{
    if ((VOS_NULL_PTR == pucImsi) || ((TAF_SDC_MAX_IMSI_LEN - 1 )< pucImsi[0]))
    {
        return ;
    }

    /*��ת���ַ���*/
    *pulImsiHigh = ( ((VOS_UINT32)(pucImsi[1]&0xf0) << TAF_SDC_MOVEMENT_20_BITS)
                   | ((VOS_UINT32)(pucImsi[2]&0x0f) << TAF_SDC_MOVEMENT_20_BITS)
                   | ((VOS_UINT32)(pucImsi[2]&0xf0) << TAF_SDC_MOVEMENT_12_BITS)
                   | ((VOS_UINT32)(pucImsi[3]&0x0f) << TAF_SDC_MOVEMENT_12_BITS)
                   | ((VOS_UINT32)(pucImsi[3]&0xf0) << TAF_SDC_MOVEMENT_4_BITS)
                   | ((VOS_UINT32)(pucImsi[4]&0x0f) << TAF_SDC_MOVEMENT_4_BITS)
                   | ((VOS_UINT32)(pucImsi[4]&0xf0) >> TAF_SDC_MOVEMENT_4_BITS));
    *pulImsiLow  = ( ((VOS_UINT32)(pucImsi[5]&0x0f) << TAF_SDC_MOVEMENT_28_BITS)
                   | ((VOS_UINT32)(pucImsi[5]&0xf0) << TAF_SDC_MOVEMENT_20_BITS)
                   | ((VOS_UINT32)(pucImsi[6]&0x0f) << TAF_SDC_MOVEMENT_20_BITS)
                   | ((VOS_UINT32)(pucImsi[6]&0xf0) << TAF_SDC_MOVEMENT_12_BITS)
                   | ((VOS_UINT32)(pucImsi[7]&0x0f) << TAF_SDC_MOVEMENT_12_BITS)
                   | ((VOS_UINT32)(pucImsi[7]&0xf0) << TAF_SDC_MOVEMENT_4_BITS)
                   | ((VOS_UINT32)(pucImsi[8]&0x0f) << TAF_SDC_MOVEMENT_4_BITS)
                   | ((VOS_UINT32)(pucImsi[8]&0xf0) >> TAF_SDC_MOVEMENT_4_BITS));
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_ConvertUatiToUl
 ��������  : ��128bit��uatiת��Ϊ4��32bit������ 4��VOS_UINT8�ϲ���һ��VOS_UINT32��
 �������  : VOS_UINT8                          *pstUati,
             VOS_UINT32                          ulLength
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��4��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_ConvertUatiToUl(
    VOS_UINT8                          *pstUati
)
{
    VOS_UINT8                           aucUati[4] = {0};
    VOS_UINT32                          ulUati;

    ulUati = 0;

    PS_MEM_CPY(aucUati, pstUati, 4);

    ulUati = (((VOS_UINT32)aucUati[0] << TAF_SDC_MOVEMENT_24_BITS) & 0xff000000)
            |(((VOS_UINT32)aucUati[1] << TAF_SDC_MOVEMENT_16_BITS) & 0x00ff0000)
            |(((VOS_UINT32)aucUati[2] << TAF_SDC_MOVEMENT_8_BITS) & 0x0000ff00)
            |( (VOS_UINT32)aucUati[3] & 0x000000ff);


    return ulUati;

}
/*****************************************************************************
 �� �� ��  : TAF_MMA_MapModemId
 ��������  :  modemidӳ��
 �������  : MODEM_ID_ENUM_UINT16                enModemId
 �������  : MODEM_ID_ASN_ENUM_UINT16
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��8��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

*****************************************************************************/
MODEM_ID_ASN_ENUM_UINT16 TAF_MMA_MapModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    MODEM_ID_ASN_ENUM_UINT16            enModemIdAsn;

    switch(enModemId)
    {
        case MODEM_ID_0:
            enModemIdAsn = MODEM_0;
            break;
        case MODEM_ID_1:
            enModemIdAsn = MODEM_1;
            break;
        case MODEM_ID_2:
            enModemIdAsn = MODEM_2;
            break;
        default:
            enModemIdAsn = MODEM_BUTT;
    }
    return enModemIdAsn;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_QryCdmaStatusInfo
 ��������  : ��ά�ɲ�OM��ѯCDMA״̬��Ϣ����
 �������  : NAS_OM_MMA_CDMA_STATUS_COMMON_INFO_STRU             *pstCdmaCommInfo,
             NAS_OM_MMA_1X_SYS_INFO_STRU                         *pst1xSysInfo,
             NAS_OM_MMA_HRPD_SYS_INFO_STRU                       *pstHrpdSysInfo
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��6��
    ��    ��   : y00322978
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��08��24��
    ��    ��   : t00323010
    �޸�����   : DTS2015081904804 clear coverity

*****************************************************************************/
VOS_UINT32 TAF_MMA_QryCdmaStatusInfo(
    NAS_OM_MMA_CDMA_STATUS_COMMON_INFO_STRU             *pstCdmaCommInfo,
    NAS_OM_MMA_1X_SYS_INFO_STRU                         *pst1xSysInfo,
    NAS_OM_MMA_HRPD_SYS_INFO_STRU                       *pstHrpdSysInfo
)
{
    TAF_SDC_SYS_INFO_STRU               *pstSysInfo;
    TAF_SDC_SYS_MODE_ENUM_UINT8          enSysMode;
    VOS_UINT8                            aucUati[NAS_OM_MMA_UATI_OCTET_LENGTH] = {0};

    TAF_SDC_PHONE_MODE_ENUM_UINT8       enCurPhoneMode;

    enCurPhoneMode = TAF_SDC_GetCurPhoneMode();
    pstSysInfo = TAF_SDC_GetSysInfo();
    enSysMode = TAF_SDC_GetSysMode();
    PS_MEM_CPY(aucUati, pstSysInfo->stHrpdSysInfo.aucCurUATI, NAS_OM_MMA_UATI_OCTET_LENGTH);

    /* clear coverity warning */
    if (TAF_SDC_PHONE_MODE_BUTT == enCurPhoneMode)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA,
                        "TAF_MMA_QryCdmaStatusInfo: Curr Phone Mode is BUTT!");
    }

    /* clear coverity warning */
    if(TAF_SDC_SYS_MODE_BUTT == enSysMode)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA,
                        "TAF_MMA_QryCdmaStatusInfo: Curr System Mode is BUTT!");
    }

    /*cdma comm info*/
    pstCdmaCommInfo->enPhoneMode = TAF_MMA_MapCdmaPhoneMode(enCurPhoneMode);
    pstCdmaCommInfo->enSysMode = TAF_MMA_MapSysMode(enSysMode);
    pstCdmaCommInfo->enModemId = TAF_MMA_MapModemId(pstSysInfo->enModemId);
    pstCdmaCommInfo->ulEsn = TAF_SDC_GetSdcCtx()->stPhoneInfo.stHardWareInfo.ulEsn;
    TAF_MMA_ConvertMeidToUl(TAF_SDC_GetSdcCtx()->stPhoneInfo.stHardWareInfo.aucMeId, &pstCdmaCommInfo->ulMeid, &pstCdmaCommInfo->ulMeidCnt);

    TAF_MMA_ConvertUimidToUl( TAF_SDC_GetSdcCtx()->stSimInfo.stCsimInfo.aucRuimid,
                             &pstCdmaCommInfo->ulRuimidHigh,
                             &pstCdmaCommInfo->ulRuimidLow);

    TAF_MMA_ConvertImsiToUl( TAF_SDC_GetCsimImsi(),
                            &pstCdmaCommInfo->ulImsiHigh,
                            &pstCdmaCommInfo->ulImsiLow);

    pstCdmaCommInfo->enPppStatus = TAF_MMA_MapCdataBearStatus(TAF_PS_GetPppStatus());

    //cdma 1x info
    if ((TAF_SDC_SYS_MODE_CDMA_1X == enSysMode)
     || (TAF_SDC_SYS_MODE_HYBRID == enSysMode)
     || (TAF_SDC_SYS_MODE_SVLTE == enSysMode))
    {
        pst1xSysInfo->en1xCallState = TAF_SDC_GetXCallState();
        pst1xSysInfo->lNid = pstSysInfo->st1xSysInfo.lNid;
        pst1xSysInfo->lSid = pstSysInfo->st1xSysInfo.lSid;
        pst1xSysInfo->ulMcc = (VOS_UINT32)TAF_STD_TransformBcdMccToDeciDigit(pstSysInfo->st1xSysInfo.stServiceInfo.ulMcc);
        pst1xSysInfo->usBandClass = pstSysInfo->st1xSysInfo.usBandClass;
        pst1xSysInfo->usMnc = (VOS_UINT32)TAF_STD_TransformBcdMncToDeciDigit(pstSysInfo->st1xSysInfo.stServiceInfo.usImsi11_12);
        pst1xSysInfo->usFreq = pstSysInfo->st1xSysInfo.usFreq;
        pst1xSysInfo->usBaseId = pstSysInfo->st1xSysInfo.stBaseStationInfo.usBaseId;
    }

    //cdma hrpd info
    if ((TAF_SDC_SYS_MODE_EVDO == enSysMode)
     || (TAF_SDC_SYS_MODE_HYBRID == enSysMode))
    {
        pstHrpdSysInfo->usBandClass = pstSysInfo->stHrpdSysInfo.usBandClass;
        pstHrpdSysInfo->ucColorCode = pstSysInfo->stHrpdSysInfo.ucColorCode;
        pstHrpdSysInfo->enSessionStatus = pstSysInfo->stHrpdSysInfo.ucSessionStatus;
        pstHrpdSysInfo->ucSubNetMask = pstSysInfo->stHrpdSysInfo.ucSubNetMask;
        pstHrpdSysInfo->ulMcc = (VOS_UINT32)TAF_STD_TransformBcdMccToDeciDigit(pstSysInfo->stHrpdSysInfo.ulMcc);
        pstHrpdSysInfo->ulSessionSeed = pstSysInfo->stHrpdSysInfo.ulSessionSeed;
        pstHrpdSysInfo->usChannel = pstSysInfo->stHrpdSysInfo.usFreq;
        pstHrpdSysInfo->ulSector24 = pstSysInfo->stHrpdSysInfo.ulSector24;
        pstHrpdSysInfo->enSysSubMode = TAF_MMA_MapSysSubMode(pstSysInfo->enSysSubMode);
        pstHrpdSysInfo->ulCurUATI1 = TAF_MMA_ConvertUatiToUl(aucUati);
        pstHrpdSysInfo->ulCurUATI2 = TAF_MMA_ConvertUatiToUl(&aucUati[4]);
        pstHrpdSysInfo->ulCurUATI3 = TAF_MMA_ConvertUatiToUl(&aucUati[8]);
        pstHrpdSysInfo->ulCurUATI4 = TAF_MMA_ConvertUatiToUl(&aucUati[12]);
    }

    return VOS_TRUE;
}

 VOS_UINT8 TAF_MMA_IsPesnValid(
    NV_PESN_STRU                       *pstPesn
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < PESN_NV_DATA_LEN; ucIndex++)
    {
        if (0x00 != pstPesn->aucPEsn[ucIndex])
        {
           return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


 VOS_UINT8 TAF_MMA_IsMeidValid(
    NV_MEID_STRU                       *pstMeid
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < MEID_NV_DATA_LEN_NEW; ucIndex++)
    {
        if (0x00 != pstMeid->aucMeID[ucIndex])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

VOS_UINT8 TAF_MMA_IsUIMIDValid(
    VOS_UINT8                          *pucEFRUIMID
)
{
    VOS_UINT8                           ucUIMIDByteNum;
    VOS_UINT8                           i;

    /* the first byte of EFRUIMID indicates the bytes num of UIMID (here,the num is 4) in EFRUIMID */
    ucUIMIDByteNum = pucEFRUIMID[0];

    /*
      according to the protocal C.S0023-D_v2.0_R-UIM ,the EF of EFRuimid store the 32-bit UIMID constructed in the following way:

      Bytes              Description                M/O                Length

        1               number of Bytes              M                  1byte

        2               lowest-order byte            M                  1byte

        3                   ...                      M                  1byte

        4                   ...                      M                  1byte

        5                   ...                      M                  1byte

        6                   ...                      O                  1byte

        7                   ...                      O                  1byte

        8               highest-order byte           O                  1byte

        the EF consists of 8 bytes,in which the first byte indicates the bytes num of UIMID (here,the num is 4) in EF,
        so,when check the validity of UIMID,just need to check from the second byte to the fifth byte
        if all the bits of the four bytes which indicates the UIMID value from the second byte to the fifth byte are 1,then UIMID is invalid
        vice versa
    */
    for (i = 1; i <= ucUIMIDByteNum; i++)
    {
        if (0xFF != pucEFRUIMID[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
#endif


#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 �� �� ��  : TAF_MMA_RatFrequentlySwitchRecord
 ��������  : ��¼��ģƵ���л��¼�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��13��
    ��    ��   : zwx247453
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��07��06��
    ��    ��   : n00269697
    �޸�����   : ERR LOG�ϱ����ͷ�Ϊ�����ϱ��͸澯�ϱ�
*****************************************************************************/
VOS_VOID TAF_MMA_RatFrequentlySwitchRecord(VOS_VOID)
{
    NAS_ERR_LOG_RAT_FREQUENTLY_SWITCH_EVENT_STRU           *pstRatFreqSwitchEvent = VOS_NULL_PTR;
    VOS_UINT32                                              ulNvSwitchNum;
    VOS_UINT32                                              ulEventLength;
    VOS_UINT32                                              ulActuallyReadLength;
    VOS_UINT8                                               ucActiveRptFlag;
    VOS_UINT8                                               ucRatSwitchRptFlag;
    VOS_UINT16                                              usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel             = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_RAT_FREQUENTLY_SWITCH);

    ucActiveRptFlag     = TAF_SDC_GetErrlogActiveRptFlag();
    ucRatSwitchRptFlag  = TAF_SDC_GetErrlogRatSwitchRptFlag();
    ulNvSwitchNum       = TAF_SDC_GetErrlogRatSwitchStatisticNum();
    ulEventLength       = sizeof(NAS_ERR_LOG_RAT_FREQUENTLY_SWITCH_EVENT_STRU);

    /* ֻ�е������ϱ���NV�򿪣����ϱ� */
    if ((VOS_FALSE == ucActiveRptFlag)
     || (VOS_FALSE == ucRatSwitchRptFlag))
    {
        return;
    }

    pstRatFreqSwitchEvent = (NAS_ERR_LOG_RAT_FREQUENTLY_SWITCH_EVENT_STRU *)PS_MEM_ALLOC(
                                WUEPS_PID_MMA, ulEventLength);

    if (VOS_NULL_PTR == pstRatFreqSwitchEvent)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_RatFrequentlySwitchRecord(): PS_MEM_ALLOC error.");

        return;
    }

    PS_MEM_SET(pstRatFreqSwitchEvent, 0x00, ulEventLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&(pstRatFreqSwitchEvent->stHeader),
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMA),
                                      NAS_ERR_LOG_ALM_RAT_FREQUENTLY_SWITCH,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulEventLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    pstRatFreqSwitchEvent->ulStatisticTime = TAF_SDC_GetErrlogRatSwitchStatisticTime();
    pstRatFreqSwitchEvent->ulSwitchNum     = ulNvSwitchNum;

    /* ���ṹ����astPositionInfo����Ԫ�� */
    /* �Ӷ�����rearλ�ÿ�ʼ��������frontλ�ÿ�����stGutlFreqSwitchEvent�� */
    ulActuallyReadLength = TAF_SDC_GetRecordFromRatSwitchRingBuf((VOS_CHAR *)pstRatFreqSwitchEvent->astRatSwitchInfo,
                          ulNvSwitchNum * sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU));

    if (ulActuallyReadLength != (ulNvSwitchNum * sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU)))
    {
        PS_MEM_FREE(WUEPS_PID_MMA, pstRatFreqSwitchEvent);

        return;
    }

    TAF_SDC_CleanRatSwitchRingBuf();

    /* ��RATƵ���л���Ϣ���͸�ACPU OMģ�� */
    TAF_SndAcpuOmFaultErrLogInd(pstRatFreqSwitchEvent, ulEventLength, NAS_ERR_LOG_ALM_RAT_FREQUENTLY_SWITCH);

    /* RATƵ���л���ֻ��Ҫ�ϱ�������Ҫ��¼���������С�*/

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_RAT_FREQUENTLY_SWITCH,
                           WUEPS_PID_MMA,
                           (VOS_UINT8 *)pstRatFreqSwitchEvent,
                           ulEventLength);

    PS_MEM_FREE(WUEPS_PID_MMA, pstRatFreqSwitchEvent);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ReportErrlogOosBegin
 ��������  : �ϱ��޷���ʼ��Ϣ
 �������  : enOosCause     -- �޷����ԭ��
             enLostDomain   -- �޷������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��13��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_ReportErrlogOosBegin(
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32   enOosCause,
    NAS_ERR_LOG_OOS_DOMAIN_ENUM_UINT32  enLostDomain
)
{
    NAS_ERR_LOG_OOS_BEGIN_STRU          stOosBeginEvent;
    VOS_UINT32                          ulLength;
    VOS_UINT16                          usLevel;
    VOS_UINT32                          ulIsLogRecord;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_OOS_BEGIN);
    ulIsLogRecord = TAF_SDC_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_OOS_BEGIN_STRU);

    PS_MEM_SET(&stOosBeginEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stOosBeginEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMA),
                                      NAS_ERR_LOG_ALM_OOS_BEGIN,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* ��ȡ��ǰλ����Ϣ */
    NAS_MNTN_OutputPositionInfo(&stOosBeginEvent.stPositionInfo);

    /* ��ȡHPLMN */
    MN_PH_QryApHplmn(&stOosBeginEvent.stHomePlmnId.ulMcc, &stOosBeginEvent.stHomePlmnId.ulMnc);

    stOosBeginEvent.enOosCause      = enOosCause;
    stOosBeginEvent.enLostDomain    = enLostDomain;
    stOosBeginEvent.usGUTCellUlFreq = TAF_SDC_GetAppCellUlFreq();
    stOosBeginEvent.usGUTCellDlFreq = TAF_SDC_GetAppCellDlFreq();
    stOosBeginEvent.ucRssiValue     = TAF_SDC_GetAppRssiValue();

    stOosBeginEvent.ulLteArfcn      = TAF_SDC_GetAppLteArfcn();

    /* �����ϱ���AP */
    TAF_SndAcpuOmFaultErrLogInd(&stOosBeginEvent,
                                ulLength,
                                NAS_ERR_LOG_ALM_OOS_BEGIN);

    /* ��ά�ɲ⹴�� */
    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_OOS_BEGIN,
                           WUEPS_PID_MMA,
                           (VOS_UINT8 *)&stOosBeginEvent,
                           sizeof(stOosBeginEvent));

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_OosEndRecord
 ��������  : �ϱ��޷��������Ϣ
 �������  : enResumeDomain  -- �ָ���
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��13��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_ReportErrlogOosEnd(
    NAS_ERR_LOG_OOS_DOMAIN_ENUM_UINT32  enResumeDomain
)
{
    NAS_ERR_LOG_OOS_END_STRU            stOosEndEvent;
    VOS_UINT32                          ulLength;
    VOS_UINT16                          usLevel;
    VOS_UINT32                          ulIsLogRecord;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_OOS_END);
    ulIsLogRecord = TAF_SDC_IsErrLogNeedRecord(usLevel);

    /* ģ���쳣����Ҫ��¼���쳣ԭ��ֵ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_OOS_END_STRU);

    PS_MEM_SET(&stOosEndEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stOosEndEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMA),
                                      NAS_ERR_LOG_ALM_OOS_END,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* ��ȡ��ǰλ����Ϣ */
    NAS_MNTN_OutputPositionInfo(&stOosEndEvent.stPositionInfo);

    stOosEndEvent.enResumeDomain = enResumeDomain;

    if (NAS_ERR_LOG_OOS_DOMAIN_CS == enResumeDomain)
    {
        stOosEndEvent.ucReportFlag   = TAF_SDC_GetErrLogCsOosReportToAppFlag();

        TAF_SDC_SetErrLogCsOosReportToAppFlag(VOS_FALSE);
    }
    else
    {
        stOosEndEvent.ucReportFlag   = TAF_SDC_GetErrLogPsOosReportToAppFlag();

        TAF_SDC_SetErrLogPsOosReportToAppFlag(VOS_FALSE);
    }

    stOosEndEvent.usGUTCellDlFreq   = TAF_SDC_GetAppCellDlFreq();
    stOosEndEvent.usGUTCellUlFreq   = TAF_SDC_GetAppCellUlFreq();
    stOosEndEvent.ucRssiValue       = TAF_SDC_GetAppRssiValue();

    stOosEndEvent.ulLteArfcn        = TAF_SDC_GetAppLteArfcn();

    /* �����ϱ���AP */
    TAF_SndAcpuOmFaultErrLogInd(&stOosEndEvent,
                                ulLength,
                                NAS_ERR_LOG_ALM_OOS_END);

    /* ��ά�ɲ⹴�� */
    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_OOS_END,
                           WUEPS_PID_MMA,
                           (VOS_UINT8 *)&stOosEndEvent,
                           sizeof(stOosEndEvent));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcErrlogDomainOosReport
 ��������  : ����ERRLOG�������޷�����ϱ�
 �������  : enOldRegState    -- �ɵ�ע��״̬
             enNewRegState    -- �µ�ע��״̬
             ulOosCause       -- �޷����ԭ��
             enOosDomain      -- �޷������
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��16��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_ProcErrlogDomainOosReport(
    TAF_SDC_REG_STATUS_ENUM_UINT8       enOldRegState,
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8   enNewRegState,
    VOS_UINT32                          ulOosCause,
    NAS_ERR_LOG_OOS_DOMAIN_ENUM_UINT32  enOosDomain
)
{
    VOS_UINT8                           ucReportPowerOnBeginFlag;
    VOS_UINT8                           ucReportPowerOffBeginFlag;


    ucReportPowerOnBeginFlag  = TAF_SDC_GetErrLogReportPowerOnBeginFlag();
    ucReportPowerOffBeginFlag = TAF_SDC_GetErrLogReportPowerOffBeginFlag();

    /* ĳ�����뿪ע��״̬(��1����5)ʱ����AP�ϱ�OOS BGEIN��Ϣ��
       ĳ����ص�ע��״̬(��1����5)ʱ����AP�ϱ�OOS END��Ϣ��
     */

    /* �뿪ע��״̬ */
    if (((NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK == enOldRegState)
      || (NAS_MSCC_PIF_REG_REGISTERED_ROAM         == enOldRegState))
     && ((NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK != enNewRegState)
      && (NAS_MSCC_PIF_REG_REGISTERED_ROAM         != enNewRegState)))
    {
        /* ���֮ǰ�Ѿ��ϱ������ػ�Begin�������ϱ��κ�ԭ���Begin */
        if ((VOS_TRUE != ucReportPowerOnBeginFlag)
         && (VOS_TRUE != ucReportPowerOffBeginFlag))
        {
            TAF_MMA_ReportErrlogOosBegin((NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32)ulOosCause,
                                         enOosDomain);
        }

        return;
    }

    /* �ص�ע��״̬ */
    if (((NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK != enOldRegState)
      && (NAS_MSCC_PIF_REG_REGISTERED_ROAM         != enOldRegState))
     && ((NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK == enNewRegState)
      || (NAS_MSCC_PIF_REG_REGISTERED_ROAM         == enNewRegState)))
    {
        TAF_MMA_ReportErrlogOosEnd(enOosDomain);

        TAF_SDC_SetErrLogReportPowerOnBeginFlag(VOS_FALSE);
        TAF_SDC_SetErrLogReportPowerOffBeginFlag(VOS_FALSE);

        return;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcErrlogOosReport
 ��������  : ����ERRLOG�޷�����ϱ�
 �������  : enOldCsRegState  -- �ɵ�CS��ע��״̬
             enOldPsRegState  -- �ɵ�PS��ע��״̬
             pstServiceStatus -- MMC�ϱ��ķ���״̬��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��13��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_ProcErrlogOosReport(
    TAF_SDC_REG_STATUS_ENUM_UINT8       enOldCsRegState,
    TAF_SDC_REG_STATUS_ENUM_UINT8       enOldPsRegState,
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
)
{
    if (NAS_MSCC_PIF_SRVDOMAIN_CS == pstServiceStatus->enCnDomainId)
    {
        TAF_MMA_ProcErrlogDomainOosReport(enOldCsRegState,
                                          pstServiceStatus->enRegState,
                                          pstServiceStatus->ulOosCause,
                                          NAS_ERR_LOG_OOS_DOMAIN_CS);
        return;
    }

    if (NAS_MSCC_PIF_SRVDOMAIN_PS == pstServiceStatus->enCnDomainId)
    {

        TAF_MMA_ProcErrlogDomainOosReport(enOldPsRegState,
                                          pstServiceStatus->enRegState,
                                          pstServiceStatus->ulOosCause,
                                          NAS_ERR_LOG_OOS_DOMAIN_PS);
        return;

    }

    return;
}


#endif

/*****************************************************************************
 �� �� ��  : TAF_MMA_RecordRegStatusReportFlag
 ��������  : ��¼�Ƿ��ϱ���ע��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��16��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_RecordRegStatusReportFlag(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId,
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8   enRegState
)
{
    /* ����ϱ������޷������¼���ϱ��޷��� */
    if ((NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK != enRegState)
     && (NAS_MSCC_PIF_REG_REGISTERED_ROAM         != enRegState))
    {
        if (NAS_MSCC_PIF_SRVDOMAIN_CS == enCnDomainId)
        {
            TAF_SDC_SetErrLogCsOosReportToAppFlag(VOS_TRUE);
        }
        else if (NAS_MSCC_PIF_SRVDOMAIN_PS == enCnDomainId)
        {
            TAF_SDC_SetErrLogPsOosReportToAppFlag(VOS_TRUE);
        }
        else
        {
            return;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsUsimServiceAvailable
 ��������  : ��鿨�ķ���״̬�Ƿ����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��16��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsUsimServiceAvailable(VOS_VOID)
{
    VOS_UINT32                           ulRslt;

    switch (TAF_SDC_GetUsimStatus())
    {
        case TAF_SDC_USIM_STATUS_ROMSIM:
        case TAF_SDC_USIM_STATUS_VALID:
        case TAF_SDC_USIM_STATUS_CS_UNVALID:
        case TAF_SDC_USIM_STATUS_PS_UNVALID:
            ulRslt = VOS_TRUE;
            break;

        case TAF_SDC_USIM_STATUS_SIM_PIN:
        case TAF_SDC_USIM_STATUS_SIM_PUK:
        case TAF_SDC_USIM_STATUS_NET_LCOK:
        case TAF_SDC_USIM_STATUS_IMSI_LCOK:
        case TAF_SDC_USIM_STATUS_UNVALID:
        case TAF_SDC_USIM_STATUS_NO_PRESENT:
        case TAF_SDC_USIM_STATUS_BUTT:
        case TAF_SDC_USIM_STATUS_CS_PS_UNVALID:
        case TAF_SDC_USIM_STATUS_READY_TIMEROUT:
            ulRslt = VOS_FALSE;
            break;

        default:
            ulRslt = VOS_FALSE;
            TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_IsUsimServiceAvailable(): something wrong!");
            break;
    }

    return ulRslt;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateGeoPlmnIdInfo
 ��������  : ����geo��Ϣ
 �������  : VOS_UINT8                           ucRegResult
             TAF_SDC_PLMN_ID_STRU               *pstPlmnid
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��15��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
  2��    ��   : 2015��12��10��
    ��    ��   : l00324781
    �޸�����   : CL_MUTIMODE_OPTIMIZE �������޸�

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateGeoPlmnIdInfo(
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId
)
{
    TAF_MMA_GET_GEO_CTX_STRU            *pstGetGeoCtx = VOS_NULL_PTR;

    pstGetGeoCtx        = TAF_MMA_GetGeoCtxAddr();

    /* get geo NV��ر�ʱ����Ҫ���� */
    if (VOS_FALSE == pstGetGeoCtx->stGetGeoNvCfg.ucCfgGetGeoFlag)
    {
        return;
    }

    pstGetGeoCtx->stGeoPlmnId.ulMcc = pstPlmnId->ulMcc;
    pstGetGeoCtx->stGeoPlmnId.ulMnc = pstPlmnId->ulMnc;
    pstGetGeoCtx->ulGetGeoTickTime  = VOS_GetTick() / PRE_SECOND_TO_TICK;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ConvertSysInfoExSysMode
 ��������  : ת����ǰ��sysmodeΪATģʽ
 �������  : TAF_SDC_SYS_MODE_ENUM_UINT8         enSrcSysMode,
 �������  : MN_PH_SYS_MODE_EX_ENUM_U8          *penDestSysMode
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��26��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��08��21��
    ��    ��   : y00307564
    �޸�����   : DTS2015081005519�޸�
*****************************************************************************/
VOS_VOID TAF_MMA_ConvertSysInfoExSysMode(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSrcSysMode,
    MN_PH_SYS_MODE_EX_ENUM_U8          *penDestSysMode
)
{
    switch(enSrcSysMode)
    {

        case TAF_SDC_SYS_MODE_LTE:
           *penDestSysMode = MN_PH_SYS_MODE_EX_LTE_RAT;
            return;

        case TAF_SDC_SYS_MODE_CDMA_1X:
           *penDestSysMode = MN_PH_SYS_MODE_EX_CDMA_RAT;
            return;

        case TAF_SDC_SYS_MODE_EVDO:
           *penDestSysMode = MN_PH_SYS_MODE_EX_EVDO_RAT;
            return;

        case TAF_SDC_SYS_MODE_HYBRID:
           *penDestSysMode = MN_PH_SYS_MODE_EX_HYBRID_RAT;
            return;

        case TAF_SDC_SYS_MODE_SVLTE:
           *penDestSysMode = MN_PH_SYS_MODE_EX_SVLTE_RAT;
            return;

        case TAF_SDC_SYS_MODE_BUTT:
           *penDestSysMode = MN_PH_SYS_MODE_EX_NONE_RAT;
            return;

        default:
           *penDestSysMode = MN_PH_SYS_MODE_EX_BUTT_RAT;
           return;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ConvertSysInfoExSysSubMode
 ��������  : ת����ǰ��sys sub modeΪATģʽ
 �������  : TAF_SDC_SYS_MODE_ENUM_UINT8         enSrcSysMode,
 �������  : MN_PH_SUB_SYS_MODE_EX_ENUM_U8      *penDestSysSubMode
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��26��
    ��    ��   : c00299063
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_ConvertSysInfoExSysSubMode(
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enSrcSysSubMode,
    MN_PH_SUB_SYS_MODE_EX_ENUM_U8      *penDestSysSubMode
)
{
    MN_PH_ConvertSysSubModeToAtFormat_FDD(enSrcSysSubMode, penDestSysSubMode);

    return;
}




/*****************************************************************************
 �� �� ��  : TAF_MMA_IsSameAsAppServiceStatus
 ��������  : �ж���ķ���״̬�Ƿ����任
 �������  : ulServiceStatus ��service status״̬��ǰָ����ķ���״̬
             ulCnDomainId    ��service status��ָ������
 �������  : ��
 �� �� ֵ  : TRUE ָ����ķ���״̬��APP����ͬ, FALSE:��APP�����״̬��ͬ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��11��
    ��    ��   : w00281933
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_UINT8 TAF_MMA_IsSameAsAppServiceStatus(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enServiceStatus,
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId
)
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ucOldCsAppServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ucOldPsAppServiceStatus;
    VOS_UINT8                           ucIsSameAsAppSrvStatus;

    ucOldCsAppServiceStatus = TAF_SDC_GetAppCsServiceStatus();
    ucOldPsAppServiceStatus = TAF_SDC_GetAppPsServiceStatus();
    ucIsSameAsAppSrvStatus  = VOS_TRUE;


    switch (enCnDomainId)
    {
        case NAS_MSCC_PIF_SRVDOMAIN_CS:
            if (ucOldCsAppServiceStatus != enServiceStatus)
            {
                ucIsSameAsAppSrvStatus = VOS_FALSE;
            }
            break;
        case NAS_MSCC_PIF_SRVDOMAIN_PS:
            if (ucOldPsAppServiceStatus != enServiceStatus)
            {
                ucIsSameAsAppSrvStatus = VOS_FALSE;
            }
            break;

        case NAS_MSCC_PIF_SRVDOMAIN_CS_PS:
        case NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING:
            if ( (ucOldCsAppServiceStatus != enServiceStatus)
               ||(ucOldPsAppServiceStatus != enServiceStatus))
            {
                ucIsSameAsAppSrvStatus = VOS_FALSE;
            }
            break;
        default:
            break;
    }

    return ucIsSameAsAppSrvStatus;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateAppSrvStatusInfo
 ��������  : ����AppNetworkInfo�б���ķ���״̬��Ϣ
 �������  : enCnDomainId:��Ҫ���µ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��10��
    ��    ��   : l00305157
    �޸�����   : �������� Service_State_Optimize_PhaseII
  2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateAppSrvStatusInfo(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId
)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;

    /*��ӡ��ά�ɲ�*/
    TAF_MMA_LogNetworkInfoAndAppNetworkInfo();

    pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    /* פ����Ϣ���µ�AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stAppSysInfo.stServPlmnInfo.stServicePlmnId),
                &(pstCurNwInfo->stSysInfo.st3gppSysInfo.stPlmnId),
                sizeof(TAF_SDC_PLMN_ID_STRU));
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.usServiceLac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.usLac;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRac;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ulServiceCellId        = pstCurNwInfo->stSysInfo.st3gppSysInfo.ulCellId;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRoamFlg       = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRoamFlag;

    /* ϵͳģʽ��ϵͳ��ģʽ���µ�AppNetworkInfo */
    pstAppNwInfo->stAppSysInfo.enSysMode                             = pstCurNwInfo->stSysInfo.enSysMode;
    pstAppNwInfo->stAppSysInfo.enSysSubMode                          = pstCurNwInfo->stSysInfo.enSysSubMode;

    /* �ź��������µ�AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo),
                &(pstCurNwInfo->stSigQuaInfo.st3GppRssiInfo),
                sizeof(TAF_SDC_3GPP_RSSI_INFO_STRU));

    /* ����״̬���µ�AppNetworkInfo */
    switch(enCnDomainId)
    {
        case NAS_MSCC_PIF_SRVDOMAIN_CS:
            TAF_SDC_SetAppCsServiceStatus(pstCurNwInfo->stCsDomainInfo.enCsServiceStatus);
            break;
        case NAS_MSCC_PIF_SRVDOMAIN_PS:
            TAF_SDC_SetAppPsServiceStatus(pstCurNwInfo->stPsDomainInfo.enPsServiceStatus);
            break;
        case NAS_MSCC_PIF_SRVDOMAIN_NO_CHANGE:
        case NAS_MSCC_PIF_SRVDOMAIN_CS_PS:
        case NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING:
            /* �����ַ�����ֻ��MMC�Ż��ϱ������PS/CS����Ҫ���� */
            TAF_SDC_SetAppCsServiceStatus(pstCurNwInfo->stCsDomainInfo.enCsServiceStatus);
            TAF_SDC_SetAppPsServiceStatus(pstCurNwInfo->stPsDomainInfo.enPsServiceStatus);
            break;
        default:
            break;
    }

    /*�����ܵķ���״̬*/
    TAF_MMA_UpdateAppReportSrvStatus();

    /*�����ܵķ�����*/
    TAF_MMA_UpdateAppReportSrvDomain(enCnDomainId);

    return ;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateAppRegStatusInfo
 ��������  : ����AppNetworkInfo�б����ע��״̬��Ϣ
 �������  : enCnDomainId:��Ҫ���µ���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��10��
    ��    ��   : l00305157
    �޸�����   : �������� Service_State_Optimize_PhaseII
  2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateAppRegStatusInfo(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId
)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;

    /*��ӡ��ά�ɲ�*/
    TAF_MMA_LogNetworkInfoAndAppNetworkInfo();

    pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    /* פ����Ϣ���µ�AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stAppSysInfo.stServPlmnInfo.stServicePlmnId),
                &(pstCurNwInfo->stSysInfo.st3gppSysInfo.stPlmnId),
                sizeof(TAF_SDC_PLMN_ID_STRU));
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.usServiceLac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.usLac;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRac;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ulServiceCellId        = pstCurNwInfo->stSysInfo.st3gppSysInfo.ulCellId;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRoamFlg       = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRoamFlag;

    /* ϵͳģʽ��ϵͳ��ģʽ���µ�AppNetworkInfo */
    pstAppNwInfo->stAppSysInfo.enSysMode                             = pstCurNwInfo->stSysInfo.enSysMode;
    pstAppNwInfo->stAppSysInfo.enSysSubMode                          = pstCurNwInfo->stSysInfo.enSysSubMode;

    /* �ź��������µ�AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo),
                &(pstCurNwInfo->stSigQuaInfo.st3GppRssiInfo),
                sizeof(TAF_SDC_3GPP_RSSI_INFO_STRU));

    /* ע��״̬���µ�AppNetworkInfo */
    if (NAS_MSCC_PIF_SRVDOMAIN_CS == enCnDomainId)
    {
        TAF_SDC_SetAppCsRegStatus(pstCurNwInfo->stCsDomainInfo.enCsRegStatus);
    }
    else if (NAS_MSCC_PIF_SRVDOMAIN_PS == enCnDomainId)
    {
        TAF_SDC_SetAppPsRegStatus(pstCurNwInfo->stPsDomainInfo.enPsRegStatus);
    }
    else if(NAS_MSCC_PIF_SRVDOMAIN_CS_PS == enCnDomainId)
    {
        TAF_SDC_SetAppCsRegStatus(pstCurNwInfo->stCsDomainInfo.enCsRegStatus);
        TAF_SDC_SetAppPsRegStatus(pstCurNwInfo->stPsDomainInfo.enPsRegStatus);
    }
    else
    {
        TAF_ERROR_LOG (WUEPS_PID_MMA,
            "TAF_MMA_UpdateAppRegStatusInfo():WARNING:enCurRegStatus is TAF_SDC_REG_STATUS_BUTT");
    }

    return ;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateAppNetworkInfo
 ��������  : ����AppNetworkInfo
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��16��
    ��    ��   : s00217060
    �޸�����   : ��������
  2.��    ��   : 2015��02��11��
    ��    ��   : l00305157
    �޸�����   : Service_State_Optimize_PhaseII
                 ����״̬���µ�AppNetworkInfo
  3.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateAppNetworkInfo(VOS_VOID)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;

    /*��ӡ��ά�ɲ�*/
    TAF_MMA_LogNetworkInfoAndAppNetworkInfo();

    pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    /* פ����Ϣ���µ�AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stAppSysInfo.stServPlmnInfo.stServicePlmnId),
                &(pstCurNwInfo->stSysInfo.st3gppSysInfo.stPlmnId),
                sizeof(TAF_SDC_PLMN_ID_STRU));
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.usServiceLac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.usLac;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRac;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ulServiceCellId        = pstCurNwInfo->stSysInfo.st3gppSysInfo.ulCellId;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRoamFlg       = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRoamFlag;

    /* ϵͳģʽ��ϵͳ��ģʽ���µ�AppNetworkInfo */
    pstAppNwInfo->stAppSysInfo.enSysMode                             = pstCurNwInfo->stSysInfo.enSysMode;
    pstAppNwInfo->stAppSysInfo.enSysSubMode                          = pstCurNwInfo->stSysInfo.enSysSubMode;

    /* �ź��������µ�AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo),
                &(pstCurNwInfo->stSigQuaInfo.st3GppRssiInfo),
                sizeof(TAF_SDC_3GPP_RSSI_INFO_STRU));

    /* ����״̬���µ�AppNetworkInfo */
    TAF_SDC_SetAppCsServiceStatus(pstCurNwInfo->stCsDomainInfo.enCsServiceStatus);
    TAF_SDC_SetAppPsServiceStatus(pstCurNwInfo->stPsDomainInfo.enPsServiceStatus);

    TAF_SDC_SetAppCsRegStatus(pstCurNwInfo->stCsDomainInfo.enCsRegStatus);
    TAF_SDC_SetAppPsRegStatus(pstCurNwInfo->stPsDomainInfo.enPsRegStatus);

    TAF_SDC_SetAppServiceStatus(pstCurNwInfo->enReportSrvsta);
    TAF_SDC_SetAppServiceDomain(pstCurNwInfo->enServiceDomain);

    return ;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateAppServPlmnInfo
 ��������  : ����AppServPlmnInfo
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��14��
    ��    ��   : s00217060
    �޸�����   : ��������
  2.��    ��   : 2015��10��8��
    ��    ��   : l00324781
    �޸�����   : Iteration 18 ,CLģ����״̬��ʾ�Ż�
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateAppServPlmnInfo(VOS_VOID)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;


    pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    /* פ����Ϣ���µ�AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stAppSysInfo.stServPlmnInfo.stServicePlmnId), &(pstCurNwInfo->stSysInfo.st3gppSysInfo.stPlmnId), sizeof(TAF_SDC_PLMN_ID_STRU));
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.usServiceLac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.usLac;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRac;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ulServiceCellId        = pstCurNwInfo->stSysInfo.st3gppSysInfo.ulCellId;
    pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRoamFlg       = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRoamFlag;

    /* ϵͳģʽ��ϵͳ��ģʽ���µ�AppNetworkInfo */
    pstAppNwInfo->stAppSysInfo.enSysMode                             = pstCurNwInfo->stSysInfo.enSysMode;
    pstAppNwInfo->stAppSysInfo.enSysSubMode                          = pstCurNwInfo->stSysInfo.enSysSubMode;

    return ;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateAppReportSrvStatus
 ��������  : ����AppNetworkInfo�б�����ܵķ���״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��10��
    ��    ��   : l00305157
    �޸�����   : �������� Service_State_Optimize_PhaseII

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateAppReportSrvStatus(VOS_VOID)
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ulAppPsServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ulAppCsServiceStatus;


    ulAppCsServiceStatus = TAF_SDC_GetAppCsServiceStatus();
    ulAppPsServiceStatus = TAF_SDC_GetAppPsServiceStatus();

        /* �����ܵķ���״̬ */
    if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppCsServiceStatus)
     && (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppPsServiceStatus))
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE);
    }
    else if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppCsServiceStatus)
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE);
    }
    else if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppPsServiceStatus)
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE);
    }
    else if ((TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE_REGION == ulAppCsServiceStatus)
          || (TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE_REGION == ulAppPsServiceStatus) )
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_REGIONAL_LIMITED_SERVICE);
    }
    else if ((TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE == ulAppCsServiceStatus)
          || (TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE == ulAppPsServiceStatus) )
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE);
    }
    else if ((TAF_SDC_SERVICE_STATUS_NO_IMSI == ulAppCsServiceStatus)
          || (TAF_SDC_SERVICE_STATUS_NO_IMSI == ulAppPsServiceStatus) )
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE);
    }
    else
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_NO_SERVICE);

        if (VOS_TRUE == gstMmaValue.pg_StatusContext->ulTimMaxFlg )
        {
            TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_DEEP_SLEEP);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateAppReportSrvDomain
 ��������  : ����AppNetworkInfo�б�����ܵķ���״̬�ͷ�������Ϣ
 �������  : enCnDomainId:�ϱ��ĵ��ڵķ�������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��10��
    ��    ��   : l00305157
    �޸�����   : �������� Service_State_Optimize_PhaseII

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateAppReportSrvDomain(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId
)
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ulAppPsServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ulAppCsServiceStatus;


    ulAppCsServiceStatus = TAF_SDC_GetAppCsServiceStatus();
    ulAppPsServiceStatus = TAF_SDC_GetAppPsServiceStatus();

     /* �����ܵķ����� */
    if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppCsServiceStatus)
     && (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppPsServiceStatus))
    {
        TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS_PS);
    }
    else if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppCsServiceStatus)
    {
        TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS);
    }
    else if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppPsServiceStatus)
    {
        TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_PS);
    }
    else
    {
    }

    if (TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE != TAF_SDC_GetAppServiceStatus() )
    {
        if(NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING == enCnDomainId)
        {
            TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_SEARCHING);
        }
        else
        {
            switch(gstMmaValue.stSetMsClass.NewMsClassType)
            {
                case TAF_PH_MS_CLASS_A:
                case TAF_PH_MS_CLASS_B:
                    TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS_PS);
                    break;
                case TAF_PH_MS_CLASS_CC:
                    TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS);
                    break;
                case TAF_PH_MS_CLASS_CG:
                    TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_PS);
                    break;
                case TAF_PH_MS_CLASS_NULL:
                    TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN);
                    break;
                default:
                    TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN);
                    break;
            }
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcDelayReport
 ��������  : �����ӳ��ϱ�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��17��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ProcDelayReport(VOS_VOID)
{
    if ( TAF_MMA_TIMER_STATUS_RUNING != TAF_MMA_GetTimerStatus(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS))
    {
        /*��Ҫ��ʱ�ϱ���������ʱ�ϱ���ʱ��*/
        TAF_MMA_StartTimer(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS, (TAF_MMA_GetDelayReportServiceStatusCfgTimerLen()));
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcServiceStatusImmediatelyReport
 ��������  : �������״̬�����ϱ�
 �������  : TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    ucNewSrvSta
             TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    ucOldSrvSta
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��17��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ProcServiceStatusImmediatelyReport(
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
)
{
    /*�ϱ�����״̬��ֹͣ��ʱ��ʱ��������APPINFO*/
    TAF_MMA_ProcServiceStatusReport(TAF_SDC_GetServiceStatus(), TAF_SDC_GetAppServiceStatus());

    if (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == pstServiceStatus->enServiceStatus)
    {
        TAF_MMA_StopTimer(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS);
    }

    TAF_MMA_UpdateAppSrvStatusInfo(pstServiceStatus->enCnDomainId);

    return;
}


/*****************************************************************************
 �� �� ��  : VOS_VOID��TAF_MMA_ProcServiceStatusNotReport
 ��������  : �������״̬���ϱ�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��17��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ProcServiceStatusNotReport(
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
)
{
    /*�뵱ǰAPP����ķ���״̬��ͬ����Ҫ�ϱ�*/
    if (VOS_TRUE == TAF_MMA_IsSameAsAppServiceStatus((TAF_SDC_SERVICE_STATUS_ENUM_UINT8)pstServiceStatus->enServiceStatus, pstServiceStatus->enCnDomainId))
    {
        /* ��ǰ���normal service->normal serviceҲ����һ��פ����Ϣ���ź�ǿ�� */
        if (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == pstServiceStatus->enServiceStatus)
        {
            TAF_MMA_StopTimer(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS);

            TAF_MMA_UpdateAppSrvStatusInfo(pstServiceStatus->enCnDomainId);
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_FillActForAtCmdCregInClMode
 ��������  : CLģʽ��CGREG/CGREG���ֵACT
 �������  : enQryRegStaType-------ע��״̬��ѯ����
 �������  : TAF_PH_ACCESS_TECH_ENUM_UINT8  *pucAct      : ���뼼��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��19��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_FillActForAtCmdCregInClMode(
    TAF_MMA_QRY_REG_STATUS_TYPE_ENUM_UINT32                 enQryRegStaType,
    TAF_PH_ACCESS_TECH_ENUM_UINT8                          *pucAct
)
{
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    enSysMode = TAF_SDC_GetSysMode();

    *pucAct = TAF_PH_ACCESS_TECH_BUTT;

    /* CLģʽ��CREG��ѯ��1X�µ�CSע��״̬ */
    if (TAF_MMA_QRY_REG_STATUS_TYPE_CS == enQryRegStaType)
    {
        if ((TAF_SDC_SYS_MODE_CDMA_1X == enSysMode)
         || (TAF_SDC_SYS_MODE_SVLTE   == enSysMode)
         || (TAF_SDC_SYS_MODE_HYBRID  == enSysMode))
        {
            *pucAct = TAF_PH_ACCESS_TECH_CDMA_1X;
        }
    }
    /* CLģʽ��CGREG��ѯ����LTE��HRPD��PSע��״̬ */
    else if (TAF_MMA_QRY_REG_STATUS_TYPE_PS == enQryRegStaType)
    {
        if ((TAF_SDC_SYS_MODE_LTE   == enSysMode)
         || (TAF_SDC_SYS_MODE_SVLTE == enSysMode))
        {
            *pucAct = TAF_PH_ACCESS_TECH_E_UTRAN;
        }

        if ((TAF_SDC_SYS_MODE_EVDO   == enSysMode)
         || (TAF_SDC_SYS_MODE_HYBRID == enSysMode))
        {
            *pucAct = TAF_PH_ACCESS_TECH_EVDO;
        }
    }
    /* EPS״̬��ѯ */
    else
    {
        if ((TAF_SDC_SYS_MODE_LTE   == enSysMode)
         || (TAF_SDC_SYS_MODE_SVLTE == enSysMode))
        {
            *pucAct = TAF_PH_ACCESS_TECH_E_UTRAN;
        }
    }

    return;
}


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode
 ��������  : ����stAppNetworkInfo�ṹ����ϵͳģʽ��ϵͳ��ģʽ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��23��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode(VOS_VOID)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;

    pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    /* �����ϱ���ϵͳģʽ��ϵͳ��ģʽ */
    pstAppNwInfo->stAppSysInfo.enSysMode    = pstCurNwInfo->stSysInfo.enSysMode;
    pstAppNwInfo->stAppSysInfo.enSysSubMode = pstCurNwInfo->stSysInfo.enSysSubMode;

    return;
}



/*****************************************************************************
 �� �� ��  : TAF_MMA_Add1XToAppSysModeAndSysSubMode
 ��������  : ��1X���뵽ϵͳģʽ��ϵͳ��ģʽ��
 �������  : TAF_SDC_SYS_MODE_ENUM_UINT8                             enCurAppSysMode
             TAF_SYS_SUBMODE_ENUM_UINT8                              enCurAppSubMode
             TAF_SDC_SYS_MODE_ENUM_UINT8                            *penNewAppSysMode
             TAF_SYS_SUBMODE_ENUM_UINT8                             *penNewAppSubMode
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��9��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_Add1XToAppSysModeAndSysSubMode(
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enCurAppSysMode,
    TAF_SYS_SUBMODE_ENUM_UINT8                              enCurAppSubMode,
    TAF_SDC_SYS_MODE_ENUM_UINT8                            *penNewAppSysMode,
    TAF_SYS_SUBMODE_ENUM_UINT8                             *penNewAppSubMode
)
{
    VOS_UINT32                                              i;
    TAF_SDC_MODIFY_SYSMODE_MAP_TLB_STRU                     astAdd1xSysModeMapTlb[] =
    {
        {TAF_SDC_SYS_MODE_EVDO, TAF_SDC_SYS_SUBMODE_EVDO_REL_0, TAF_SDC_SYS_MODE_HYBRID,   TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0},
        {TAF_SDC_SYS_MODE_EVDO, TAF_SDC_SYS_SUBMODE_EVDO_REL_A, TAF_SDC_SYS_MODE_HYBRID,   TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_A},
        {TAF_SDC_SYS_MODE_EVDO, TAF_SDC_SYS_SUBMODE_EHRPD,      TAF_SDC_SYS_MODE_HYBRID,   TAF_SDC_SYS_SUBMODE_EHRPD},
        {TAF_SDC_SYS_MODE_LTE,  TAF_SDC_SYS_SUBMODE_LTE,        TAF_SDC_SYS_MODE_SVLTE,    TAF_SDC_SYS_SUBMODE_LTE},
        {TAF_SDC_SYS_MODE_BUTT, TAF_SDC_SYS_SUBMODE_BUTT,       TAF_SDC_SYS_MODE_CDMA_1X,  TAF_SDC_SYS_SUBMODE_CDMA_1X}
    };

    for (i = 0; i < sizeof(astAdd1xSysModeMapTlb)/sizeof(astAdd1xSysModeMapTlb[0]); i++)
    {
        if ((enCurAppSysMode == astAdd1xSysModeMapTlb[i].enCurAppSysMode)
         && (enCurAppSubMode == astAdd1xSysModeMapTlb[i].enCurAppSubMode))
        {
            *penNewAppSysMode = astAdd1xSysModeMapTlb[i].enNewAppSysMode;
            *penNewAppSubMode = astAdd1xSysModeMapTlb[i].enNewAppSubMode;

            return;
        }
    }

    *penNewAppSysMode = enCurAppSysMode;
    *penNewAppSubMode = enCurAppSubMode;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_Del1XFromAppSysModeAndSysSubMode
 ��������  : ������ϵͳģʽ����ģʽ��ɾ��1X
 �������  : TAF_SDC_SYS_MODE_ENUM_UINT8                             enCurAppSysMode
             TAF_SYS_SUBMODE_ENUM_UINT8                              enCurAppSubMode
             TAF_SDC_SYS_MODE_ENUM_UINT8                            *penNewAppSysMode
             TAF_SYS_SUBMODE_ENUM_UINT8                             *penNewAppSubMode
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��9��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_Del1XFromAppSysModeAndSysSubMode(
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enCurAppSysMode,
    TAF_SYS_SUBMODE_ENUM_UINT8                              enCurAppSubMode,
    TAF_SDC_SYS_MODE_ENUM_UINT8                            *penNewAppSysMode,
    TAF_SYS_SUBMODE_ENUM_UINT8                             *penNewAppSubMode
)
{
    VOS_UINT32                                              i;
    TAF_SDC_MODIFY_SYSMODE_MAP_TLB_STRU                     astDel1xSysModeMapTlb[] =
    {
        {TAF_SDC_SYS_MODE_HYBRID,   TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0, TAF_SDC_SYS_MODE_EVDO, TAF_SDC_SYS_SUBMODE_EVDO_REL_0},
        {TAF_SDC_SYS_MODE_HYBRID,   TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_A, TAF_SDC_SYS_MODE_EVDO, TAF_SDC_SYS_SUBMODE_EVDO_REL_A},
        {TAF_SDC_SYS_MODE_HYBRID,   TAF_SDC_SYS_SUBMODE_EHRPD,             TAF_SDC_SYS_MODE_EVDO, TAF_SDC_SYS_SUBMODE_EHRPD},
        {TAF_SDC_SYS_MODE_SVLTE,    TAF_SDC_SYS_SUBMODE_LTE,               TAF_SDC_SYS_MODE_LTE,  TAF_SDC_SYS_SUBMODE_LTE},
        {TAF_SDC_SYS_MODE_CDMA_1X,  TAF_SDC_SYS_SUBMODE_CDMA_1X,           TAF_SDC_SYS_MODE_BUTT, TAF_SDC_SYS_SUBMODE_BUTT}

    };

    for (i = 0; i < sizeof(astDel1xSysModeMapTlb)/sizeof(astDel1xSysModeMapTlb[0]); i++)
    {
        if ((enCurAppSysMode == astDel1xSysModeMapTlb[i].enCurAppSysMode)
         && (enCurAppSubMode == astDel1xSysModeMapTlb[i].enCurAppSubMode))
        {
            *penNewAppSysMode = astDel1xSysModeMapTlb[i].enNewAppSysMode;
            *penNewAppSubMode = astDel1xSysModeMapTlb[i].enNewAppSubMode;

            return;
        }
    }

    *penNewAppSysMode = enCurAppSysMode;
    *penNewAppSubMode = enCurAppSubMode;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode1x
 ��������  : 1X�仯ʱ����APP�е�ϵͳģʽ��ϵͳ��ģʽ
 �������  : TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   en1xNetworkExist
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��8��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode1x(
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   en1xNetworkExist
)
{
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;

    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    /* 1X���޷����з��� */
    if (TAF_SDC_1X_NETWORK_EXIST == en1xNetworkExist)
    {
        /* PS��ʱ��ʱ��������ʱ�����appnetwork����evdo����lte��APP network����Ҫ����1x */
        if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
        {
            TAF_MMA_Add1XToAppSysModeAndSysSubMode(pstAppNwInfo->stAppSysInfo.enSysMode,
                                                   pstAppNwInfo->stAppSysInfo.enSysSubMode,
                                                   &(pstAppNwInfo->stAppSysInfo.enSysMode),
                                                   &(pstAppNwInfo->stAppSysInfo.enSysSubMode));
        }
        else
        {
            TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode();
        }
    }

    /* 1X���з����޷��� */
    if (TAF_SDC_1X_NETWORK_NOT_EXIST == en1xNetworkExist)
    {
        /* CS��ʱ��ʱ�������У��ȶ�ʱ����ʱ���¡����򣬴�APP network��ɾ��1X */
        if (TAF_MMA_TIMER_STATUS_RUNING != TAF_MMA_GetTimerStatus(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
        {
            /* ���PS�ӳ��ϱ���ʱ�������У���Ҫ��APP network��1Xȥ�� */
            if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
            {
                TAF_MMA_Del1XFromAppSysModeAndSysSubMode(pstAppNwInfo->stAppSysInfo.enSysMode,
                                                         pstAppNwInfo->stAppSysInfo.enSysSubMode,
                                                         &(pstAppNwInfo->stAppSysInfo.enSysMode),
                                                         &(pstAppNwInfo->stAppSysInfo.enSysSubMode));
            }
            else
            {
                TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode();
            }
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateAppSysModeAndSysSubModeInClModeHrpd
 ��������  : Ehrp�仯ʱ����APP�е�ϵͳģʽ��ϵͳ��ģʽ
 �������  : TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   enHrpdNetworkExist
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��8��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateAppSysModeAndSysSubModeInClModeHrpd(
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   enHrpdNetworkExist
)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;

    pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    /* HRPD���޵��� */
    if (TAF_SDC_HRPD_NETWORK_EXIST == enHrpdNetworkExist)
    {
        /* CS��ʱ��ʱ��������ʱ��APP network����Ҫ����evdo */
        if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
        {
            pstAppNwInfo->stAppSysInfo.enSysMode = TAF_SDC_SYS_MODE_HYBRID;

            if (TAF_SDC_SYS_SUBMODE_EVDO_REL_0 == pstCurNwInfo->stSysInfo.enSysSubMode)
            {
                pstAppNwInfo->stAppSysInfo.enSysSubMode = TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0;
            }
            else if (TAF_SDC_SYS_SUBMODE_EVDO_REL_A == pstCurNwInfo->stSysInfo.enSysSubMode)
            {
                pstAppNwInfo->stAppSysInfo.enSysSubMode = TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_A;
            }
            else
            {
                pstAppNwInfo->stAppSysInfo.enSysSubMode = pstCurNwInfo->stSysInfo.enSysSubMode;
            }
        }
        else
        {
            TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode();
        }

    }

    /* HRPD���е��� */
    if (TAF_SDC_HRPD_NETWORK_NOT_EXIST == enHrpdNetworkExist)
    {
        /* PS��ʱ��ʱ��������ʱ���ȳ�ʱ����� */
        if (TAF_MMA_TIMER_STATUS_RUNING != TAF_MMA_GetTimerStatus(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
        {
            /* CS��ʱ��ʱ�������У�APP network��ȥ��evdo */
            if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
            {
                if (TAF_SDC_SYS_MODE_HYBRID == pstAppNwInfo->stAppSysInfo.enSysMode)
                {
                    pstAppNwInfo->stAppSysInfo.enSysMode = TAF_SDC_SYS_MODE_CDMA_1X;

                    pstAppNwInfo->stAppSysInfo.enSysSubMode = TAF_SDC_SYS_SUBMODE_CDMA_1X;
                }
            }
            else
            {
                TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode();
            }
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateAppSysModeAndSysSubModeInClModeLte
 ��������  : Lte�仯ʱ����APP�е�ϵͳģʽ��ϵͳ��ģʽ
 �������  : TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   enLteNetworkExist
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��8��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateAppSysModeAndSysSubModeInClModeLte(
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   enLteNetworkExist
)
{
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;

    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    /* LTE���޵��� */
    if (TAF_SDC_LTE_NETWORK_EXIST == enLteNetworkExist)
    {
        /* CS��ʱ��ʱ��������ʱ�����appnetwork����1x��APP network����Ҫ����lte */
        if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
        {
            pstAppNwInfo->stAppSysInfo.enSysMode = TAF_SDC_SYS_MODE_SVLTE;

            pstAppNwInfo->stAppSysInfo.enSysSubMode = TAF_SDC_SYS_SUBMODE_LTE;
        }
        else
        {
            TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode();
        }

    }

    /* LTE���е��� */
    if (TAF_SDC_LTE_NETWORK_NOT_EXIST == enLteNetworkExist)
    {
        /* PS��ʱ��ʱ��������ʱ���ȳ�ʱ����� */
        if (TAF_MMA_TIMER_STATUS_RUNING != TAF_MMA_GetTimerStatus(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
        {
            /* CS��ʱ��ʱ�������У�APP network��ȥ��LTE */
            if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
            {
                if (TAF_SDC_SYS_MODE_SVLTE == pstAppNwInfo->stAppSysInfo.enSysMode)
                {
                    pstAppNwInfo->stAppSysInfo.enSysMode = TAF_SDC_SYS_MODE_CDMA_1X;

                    pstAppNwInfo->stAppSysInfo.enSysSubMode = TAF_SDC_SYS_SUBMODE_CDMA_1X;
                }
            }
            else
            {
                TAF_MMA_UpdateAppSysModeAndSysSubModeInClMode();
            }
        }
    }

    return;
}




/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateAppCsSrvInfoInClMode
 ��������  : ����stAppNetworkInfo�ṹ����cs��������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 18 �޸�
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateAppCsSrvInfoInClMode(VOS_VOID)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsSrvStatus;

    /*����ϵͳ��Ϣ���ź�ǿ��*/
    pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    PS_MEM_CPY(&(pstAppNwInfo->stAppSysInfo.st3Gpp2SysInfo.st1xSysInfo),
               &(pstCurNwInfo->stSysInfo.st1xSysInfo),
               sizeof(TAF_SDC_1X_SYS_INFO_STRU));

    PS_MEM_CPY(&(pstAppNwInfo->stAppSigQuaInfo.st3Gpp2SigQuaInfo.st1xSigQualityRptInfo),
               &(pstCurNwInfo->stSigQuaInfo.st3Gpp2SigQuaInfo.st1xSigQualityRptInfo),
               sizeof(TAF_SDC_1X_SIG_QUALITY_INFO_STRU));


    /*����CS�����״̬*/
    enCsSrvStatus = TAF_SDC_GetCsServiceStatus();
    TAF_SDC_SetAppCsServiceStatus(enCsSrvStatus);

    TAF_SDC_SetAppCsRegStatus(TAF_SDC_GetCsRegStatus());
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateAppPsSrvInfoInClMode
 ��������  : ����stAppNetworkInfo�ṹ����ps�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 18 �޸�
*****************************************************************************/
VOS_VOID TAF_MMA_UpdateAppPsSrvInfoInClMode(VOS_VOID)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enPsSrvStatus;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    /*LTE�£���Ҫ����plmn��Ϣ���ź�����*/
    enSysMode = TAF_SDC_GetSysMode();

    pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    if ((TAF_SDC_SYS_MODE_LTE == enSysMode)
     || (TAF_SDC_SYS_MODE_SVLTE == enSysMode))
    {
        /* LTE��ص�ϵͳ��Ϣ����Ҫ��PLMN��Ϣ */
        PS_MEM_CPY(&(pstAppNwInfo->stAppSysInfo.stServPlmnInfo.stServicePlmnId),
                   &(pstCurNwInfo->stSysInfo.st3gppSysInfo.stPlmnId),
                   sizeof(TAF_SDC_PLMN_ID_STRU));

        pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();
        pstAppNwInfo->stAppSysInfo.stServPlmnInfo.usServiceLac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.usLac;
        pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRac;
        pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ulServiceCellId        = pstCurNwInfo->stSysInfo.st3gppSysInfo.ulCellId;
        pstAppNwInfo->stAppSysInfo.stServPlmnInfo.ucServiceRoamFlg       = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRoamFlag;

        /* �ź��������µ�AppNetworkInfo */
        PS_MEM_CPY(&(pstAppNwInfo->stAppSigQuaInfo.st3GppRssiInfo),
                &(pstCurNwInfo->stSigQuaInfo.st3GppRssiInfo),
                sizeof(TAF_SDC_3GPP_RSSI_INFO_STRU));
    }


    /*����PS�����״̬*/
    enPsSrvStatus = TAF_SDC_GetPsServiceStatus();
    TAF_SDC_SetAppPsServiceStatus(enPsSrvStatus);
    /*����PSע��״̬*/
    TAF_SDC_SetAppPsRegStatus(TAF_SDC_GetPsRegStatus());
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndCsRegStatusInClMode
 ��������  : CSע��״̬�ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 18 �޸�
*****************************************************************************/
VOS_VOID TAF_MMA_SndCsRegStatusInClMode(VOS_VOID)
{
    TAF_SDC_REG_STATUS_ENUM_UINT8       enCsRegStatus;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enAppCsRegStatus;

    TAF_PH_REG_STATE_STRU               stRegStatus;

    enCsRegStatus      = TAF_SDC_GetCsRegStatus();
    enAppCsRegStatus   = TAF_SDC_GetAppCsRegStatus();
    if (enAppCsRegStatus != enCsRegStatus)
    {
        /*ע��״̬�и��ģ���Ҫ�ϱ�*/
        PS_MEM_SET(&stRegStatus, 0, sizeof(TAF_PH_REG_STATE_STRU));

        stRegStatus.OP_CsRegState = VOS_TRUE;
        stRegStatus.OP_ucAct      = VOS_TRUE;
        stRegStatus.RegState      = enCsRegStatus;
        stRegStatus.ucAct         = TAF_PH_ACCESS_TECH_CDMA_1X;

        if (VOS_TRUE == TAF_MMA_IsRegStatusChangeNeedRpt(&stRegStatus))
        {
            TAF_MMA_SndRegStatusInd(&stRegStatus);
        }
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_Report1xSidInClMode
 ��������  : Sid�ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 18 �޸�
  2.��    ��   : 2015��12��15��
    ��    ��   : l00359089
    �޸�����   : ��������޸ĳ�Я�����  lSid, ��SID ��ֵ������ pstSdcCtx->stNetworkInfo.lSid ��
*****************************************************************************/
VOS_VOID TAF_MMA_Report1xSidInClMode(
    VOS_INT32                          lSid
)
{
    TAF_SDC_CTX_STRU                   *pstSdcCtx = VOS_NULL_PTR;

    pstSdcCtx = TAF_SDC_GetSdcCtx();

    if (VOS_TRUE == TAF_MMA_IsSidChangeNeedRpt())
    {
        if (lSid != pstSdcCtx->stNetworkInfo.lSid)
        {
            /*Sid�и��ģ���Ҫ�ϱ�*/
            TAF_MMA_ReportCSid(lSid);
        }
    }

    pstSdcCtx->stNetworkInfo.lSid = lSid;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_Report1xSigQulityInClMode
 ��������  : �ź������ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 18 �޸�
*****************************************************************************/
VOS_VOID TAF_MMA_Report1xSigQulityInClMode(VOS_VOID)
{
    TAF_SDC_1X_SIG_QUALITY_INFO_STRU   *pstSdc1xSigQualityInfo    = VOS_NULL_PTR;

    pstSdc1xSigQualityInfo    = TAF_SDC_Get1xSigQualityInfo();
    if (TAF_MMA_CDMA_CSQ_MODE_ENABLE == pstSdc1xSigQualityInfo->enMode)
    {
        if(VOS_TRUE == pstSdc1xSigQualityInfo->cDelayRptFLag)
        {
            /*�ӳ��ϱ��ź�ǿ�ȱ�־λΪVOS_TRUE�����־λ�����ϱ�һ���ź�ǿ��*/
            pstSdc1xSigQualityInfo->cDelayRptFLag = VOS_FALSE;

            TAF_MMA_SndCdmaCsqInd(pstSdc1xSigQualityInfo->sCdmaRssi,pstSdc1xSigQualityInfo->sCdmaEcIo);
        }
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_DelayReportCsCmdInClMode
 ��������  : ������Ҫ�ϱ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 18 �޸�
  1.��    ��   : 2015��11��30��
    ��    ��   : l00359089
    �޸�����   : for DTS2015120703071 �޸�
*****************************************************************************/
VOS_VOID TAF_MMA_DelayReportCsReferCmdInClMode(VOS_VOID)
{
    /* �ź������Ƿ��ϱ��Ĵ��� */
    TAF_MMA_Report1xSigQulityInClMode();

    /* CLOCINFO�Ƿ��ϱ��Ĵ��� */
    TAF_MMA_Report1xLocinfoInClMode();
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SndPsRegStatusInClMode
 ��������  : PSע��״̬�ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 18 �޸�
*****************************************************************************/
VOS_VOID TAF_MMA_SndPsRegStatusInClMode(VOS_VOID)
{
    TAF_SDC_REG_STATUS_ENUM_UINT8       enPsRegStatus;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enAppPsRegStatus;

    TAF_PH_REG_STATE_STRU               stRegStatus;

    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    TAF_SDC_PLMN_ID_STRU               *pstPlmnId     = VOS_NULL_PTR;

    enSysMode = TAF_SDC_GetSysMode();

    enPsRegStatus      = TAF_SDC_GetPsRegStatus();
    enAppPsRegStatus   = TAF_SDC_GetAppPsRegStatus();

    /*HRPD��LTEģʽ�µ��ϱ�*/
    /*ע��״̬�и��ģ���Ҫ�ϱ�*/
    if (enAppPsRegStatus == enPsRegStatus)
    {
        return;
    }
    /* ��ʼ�� */
    PS_MEM_SET(&stRegStatus, 0, sizeof(TAF_PH_REG_STATE_STRU));

    if ((TAF_SDC_SYS_MODE_SVLTE == enSysMode)
     || (TAF_SDC_SYS_MODE_LTE == enSysMode))
     {
        /* פ����Ϣ */
        stRegStatus.OP_Lac              = VOS_TRUE;
        stRegStatus.OP_Rac              = VOS_TRUE;
        stRegStatus.OP_CellId           = VOS_TRUE;
        stRegStatus.OP_Plmn             = VOS_TRUE;
        stRegStatus.ucRac               = TAF_SDC_GetCurrCampRac();
        stRegStatus.CellId.ucCellNum    = 1;
        stRegStatus.CellId.aulCellId[0] = TAF_SDC_GetCurrCampCellId();
        stRegStatus.usLac               = TAF_SDC_GetCurrCampLac();

        pstPlmnId     = TAF_SDC_GetCurrCampPlmnId();
        PS_MEM_CPY(&stRegStatus.Plmn, pstPlmnId, sizeof(TAF_PLMN_ID_STRU));

        /* ��MMC�ϱ���ϵͳ��ģʽתΪ+CREG/+CGREG�������[ACT]��Э��涨�Ľ��뼼��ֵ */
        stRegStatus.OP_ucAct        = VOS_TRUE;
        stRegStatus.ucAct           = TAF_PH_ACCESS_TECH_E_UTRAN;

        stRegStatus.OP_PsRegState   = VOS_TRUE;
        stRegStatus.ucPsRegState    = enPsRegStatus;

        stRegStatus.ucRatType       = TAF_PH_INFO_LTE_RAT;
    }
    else if ((TAF_SDC_SYS_MODE_EVDO == enSysMode)
          || (TAF_SDC_SYS_MODE_HYBRID == enSysMode))  /*HRPDģʽ�µ��ϱ�*/
    {
        stRegStatus.OP_PsRegState = VOS_TRUE;
        stRegStatus.OP_ucAct      = VOS_TRUE;
        stRegStatus.ucPsRegState  = enPsRegStatus;
        stRegStatus.ucAct         = TAF_PH_ACCESS_TECH_EVDO;
    }
    else
    {
        stRegStatus.OP_PsRegState = VOS_TRUE;
        stRegStatus.ucPsRegState  = enPsRegStatus;
    }


    if (VOS_TRUE == TAF_MMA_IsRegStatusChangeNeedRpt(&stRegStatus))
    {
        TAF_MMA_SndRegStatusInd(&stRegStatus);
    }
}




/*****************************************************************************
 �� �� ��  : TAF_MMA_IsDelayReportFeatureActiveInClMode
 ��������  : CL�ӳ��ϱ���ʱ���Ƿ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_FALSEû�п����� VOS_TRUE����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 18 �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_MMA_IsDelayReportFeatureActiveInClMode(VOS_VOID)
{
    if (VOS_FALSE == TAF_MMA_GetCLDelayReptSrvStatusFlg())
    {
        /*NV δ������ʱ�ϱ�����*/
        return VOS_FALSE;
    }

    if (0 == TAF_MMA_GetCLDelayReptSrvStatusTimerLen())
    {
        /*��ʱ�ϱ���ʱ��ʱ������Ϊ0,��������ʱ�ϱ�����*/
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsNeedDelayReportServiceStatusInClMode
 ��������  : �Ƿ���Ҫ�ӳ��ϱ�����״̬
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_FALSE����Ҫ�ӳ��ϱ��� VOS_TRUE��Ҫ�ӳ��ϱ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 18 �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsNeedDelayReportServiceStatusInClMode(VOS_VOID)
{
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enNetSrvStatus;
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    enAppNetSrvStatus;

    /*�ӳ��ϱ�NV�Ƿ���,����FALSEΪ�ر� */
    if (VOS_FALSE == TAF_MMA_IsDelayReportFeatureActiveInClMode())
    {
        return VOS_FALSE;
    }

    /* �û��������µķ���״̬�ı�,��������ʱ�ϱ� */
    if (VOS_TRUE == TAF_MMA_IsUserOperate())
    {
        return VOS_FALSE;
    }

    enNetSrvStatus    = TAF_SDC_GetServiceStatus();
    enAppNetSrvStatus = TAF_SDC_GetAppServiceStatus();

    /*AppNetInfo��¼���Ǿɵķ���״̬���뵱ǰ����״̬��һ�£������з���->�޷�������Ʒ�����Ҫ�ӳ��ϱ�*/
    if (TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE == enAppNetSrvStatus)
    {
        if ((TAF_SDC_REPORT_SRVSTA_NO_SERVICE == enNetSrvStatus)
         || (TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE == enNetSrvStatus))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsNeedDelayReportCsRegStatusInClMode
 ��������  : �Ƿ���Ҫ�ӳ��ϱ�1Xע��״̬
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_FALSE����Ҫ�ӳ��ϱ��� VOS_TRUE��Ҫ�ӳ��ϱ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 18 �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsNeedDelayReportCsRegStatusInClMode(VOS_VOID)
{
    TAF_SDC_REG_STATUS_ENUM_UINT8       enNetCsRegStatus;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enAppNetCsRegStatus;

    /*�ӳ��ϱ�NV�Ƿ��� */
    if (VOS_FALSE == TAF_MMA_IsDelayReportFeatureActiveInClMode())
    {
        return VOS_FALSE;
    }

    /* �û��������µķ���״̬�ı�,��������ʱ�ϱ� */
    if (VOS_TRUE == TAF_MMA_IsUserOperate())
    {
        return VOS_FALSE;
    }

    enNetCsRegStatus    = TAF_SDC_GetCsRegStatus();
    enAppNetCsRegStatus = TAF_SDC_GetAppCsRegStatus();

    /*AppNetInfo��¼���Ǿɵ�ע��״̬���뵱ǰע��״̬��һ�£�������ע��->��ע�ᣬ��Ҫ�ӳ��ϱ�*/
    if ((TAF_SDC_REG_REGISTERED_HOME_NETWORK == enAppNetCsRegStatus)
     || (TAF_SDC_REG_REGISTERED_ROAM == enAppNetCsRegStatus))
    {
        if ((TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH == enNetCsRegStatus)
         || (TAF_SDC_REG_NOT_REGISTERED_SEARCHING == enNetCsRegStatus))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsNeedDelayReportPsRegStatusInClMode
 ��������  : �Ƿ���Ҫ�ӳ��ϱ�Psע��״̬
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_FALSE����Ҫ�ӳ��ϱ��� VOS_TRUE��Ҫ�ӳ��ϱ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 18 �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsNeedDelayReportPsRegStatusInClMode(VOS_VOID)
{
    TAF_SDC_REG_STATUS_ENUM_UINT8       enNetPsRegStatus;
    TAF_SDC_REG_STATUS_ENUM_UINT8       enAppNetPsRegStatus;

    /*�ӳ��ϱ�NV�Ƿ���, FALSEΪΪ���� */
    if (VOS_FALSE == TAF_MMA_IsDelayReportFeatureActiveInClMode())
    {
        return VOS_FALSE;
    }

    /* �û��������µķ���״̬�ı�,��������ʱ�ϱ� */
    if (VOS_TRUE == TAF_MMA_IsUserOperate())
    {
        return VOS_FALSE;
    }

    enNetPsRegStatus    = TAF_SDC_GetPsRegStatus();
    enAppNetPsRegStatus = TAF_SDC_GetAppPsRegStatus();

    /*AppNetInfo��¼���Ǿɵ�ע��״̬���뵱ǰע��״̬��һ�£�������ע��->��ע�ᣬ��Ҫ�ӳ��ϱ�*/
    if ((TAF_SDC_REG_REGISTERED_HOME_NETWORK == enAppNetPsRegStatus)
     || (TAF_SDC_REG_REGISTERED_ROAM == enAppNetPsRegStatus))
    {
        if ((TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH == enNetPsRegStatus)
         || (TAF_SDC_REG_NOT_REGISTERED_SEARCHING == enNetPsRegStatus))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_StopDelayReportSeriveStatusTimerInClMode
 ��������  : ����ֹͣ�ӳ��ϱ���ʱ��������,�����ʱ��������ֹͣ�����ұȽ��¾���Ϣ���ж��Ƿ���Ҫ�ϱ�at����
 �������  : enDelayTimerId -- ��Ҫֹͣ�Ķ�ʱ����CS���PS���
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration_18�����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_StopDelayReportSeriveStatusTimerInClMode(
    TAF_MMA_TIMER_ID_ENUM_UINT32        enDelayTimerId
)
{
    /*���������ж���Ҫ�ر�CS����PS���ӳ��ϱ���ʱ��*/
    if (TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE == enDelayTimerId)
    {
        if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
        {
            TAF_MMA_StopTimer(TI_TAF_MMA_CS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE);
        }

        /* ���CS�����AT�����Ƿ���Ҫ�ϱ� */
        TAF_MMA_DelayReportCsReferCmdInClMode();

        /* ��stNetworkInfo����stAppNwInfo,��CS����� */
        TAF_MMA_UpdateAppCsSrvInfoInClMode();
    }
    else if (TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE == enDelayTimerId)
    {
        if (TAF_MMA_TIMER_STATUS_RUNING == TAF_MMA_GetTimerStatus(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE))
        {
            TAF_MMA_StopTimer(TI_TAF_MMA_PS_SERVICE_STATUS_DELAY_REPORT_IN_CL_MODE);
        }

        /* ��stNetworkInfo����stAppNwInfo,��PS�������Ϣ */
        TAF_MMA_UpdateAppPsSrvInfoInClMode();

        /* ���PSҵ��������ʱ�ϱ� */
        TAF_MMA_DelayReportPsCmdInClMode();
    }
    else
    {
        /* do nothing */
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateServiceDomainInClMode
 ��������  : CLģʽ�£�����stNetworkInfo�еķ����򣬸���SysMOde���¡�
            ע��:��1X������£����³�CS_PS
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration_18�����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateServiceDomainInClMode(
    TAF_SDC_SYS_MODE_ENUM_UINT8        enSysMode
)
{
    /* ��1X������£����³�CS_PS */
    if ((TAF_SDC_SYS_MODE_CDMA_1X == enSysMode)
     || (TAF_SDC_SYS_MODE_HYBRID == enSysMode)
     || (TAF_SDC_SYS_MODE_SVLTE == enSysMode))
    {
        TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS_PS);
    }
    else if((TAF_SDC_SYS_MODE_EVDO == enSysMode)
         || (TAF_SDC_SYS_MODE_LTE == enSysMode))
    {
        TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_PS);
    }
    else
    {
        TAF_SDC_SetServiceDomain(TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN);
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_DelayReportPsCmdInClMode
 ��������  : ������Ҫ�ϱ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��30��
    ��    ��   : c00299064
    �޸�����   : PAM CDMA Iteration 2 �޸�
*****************************************************************************/
VOS_VOID TAF_MMA_DelayReportPsCmdInClMode(VOS_VOID)
{
    /*�ź������Ƿ��ϱ��Ĵ���*/
    TAF_MMA_ReportHdrSigQulityInClMode();
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ReportHdrSigQulityInClMode
 ��������  : �ź������ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��30��
    ��    ��   : c00299064
    �޸�����   : PAM CDMA Iteration 2 �޸�
*****************************************************************************/
VOS_VOID TAF_MMA_ReportHdrSigQulityInClMode(VOS_VOID)
{
    TAF_SDC_HRPD_SIG_QUALITY_INFO_STRU   *pstSdcHrpdSigQualityInfo    = VOS_NULL_PTR;

    pstSdcHrpdSigQualityInfo    = TAF_SDC_GetHrpdSigQualityInfo();

    if (TAF_MMA_HDR_CSQ_MODE_ENABLE == pstSdcHrpdSigQualityInfo->enMode)
    {
        if(VOS_TRUE == pstSdcHrpdSigQualityInfo->ucIsDelayReportEnable)
        {
            /*�ӳ��ϱ��ź�ǿ�ȱ�־λΪVOS_TRUE�����־λ�����ϱ�һ���ź�ǿ��*/
            pstSdcHrpdSigQualityInfo->ucIsDelayReportEnable = VOS_FALSE;

            TAF_MMA_SndHdrCsqInd(pstSdcHrpdSigQualityInfo->sHdrRssi,
                pstSdcHrpdSigQualityInfo->sHdrSnr,
                pstSdcHrpdSigQualityInfo->sHdrEcio);
        }
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateAppServiceDomainInClMode
 ��������  : CLģʽ�£�����stAppNetworkInfo�еķ����򣬸���SysMOde���¡�
            ע��:��1X������£����³�CS_PS
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��24��
    ��    ��   : l00324781
    �޸�����   :DTS2015121801944�����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateAppServiceDomainInClMode(
    TAF_SDC_SYS_MODE_ENUM_UINT8        enSysMode
)
{
    /* ��1X������£����³�CS_PS */
    if ((TAF_SDC_SYS_MODE_CDMA_1X == enSysMode)
     || (TAF_SDC_SYS_MODE_HYBRID == enSysMode)
     || (TAF_SDC_SYS_MODE_SVLTE == enSysMode))
    {
        TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS_PS);
    }
    else if((TAF_SDC_SYS_MODE_EVDO == enSysMode)
         || (TAF_SDC_SYS_MODE_LTE == enSysMode))
    {
        TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_PS);
    }
    else
    {
        TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN);
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_Report1xLocinfoInClMode
 ��������  : CLOCINFO�ϱ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��30��
    ��    ��   : l00359089
    �޸�����   : �����ɺ��� for DTS2015120703071
*****************************************************************************/
VOS_VOID TAF_MMA_Report1xLocinfoInClMode(VOS_VOID)
{
    TAF_SDC_1X_SYS_INFO_STRU           *pstSdc1xSysInfo     = VOS_NULL_PTR;
    TAF_SDC_1X_SYS_INFO_STRU           *pstAppSdc1xSysInfo  = VOS_NULL_PTR;
    TAF_MMA_CLOCINFO_PARA_STRU          stClocinfoPara;
    VOS_UINT32                          ulClocinfoNeedRpt;
    VOS_UINT32                          ulMccTmp;
    VOS_UINT16                          usMncTmp;

    pstSdc1xSysInfo    = TAF_SDC_Get1xSysInfo();
    pstAppSdc1xSysInfo = TAF_SDC_GetApp1xSysInfo();
    ulClocinfoNeedRpt  = TAF_MMA_IsClocinfoChangeNeedRpt();

    /* ������CLOCINFO�ϱ������� */
    if (VOS_FALSE == ulClocinfoNeedRpt)
    {
        return;
    }

    if ((pstSdc1xSysInfo->lSid                       != pstAppSdc1xSysInfo->lSid)
     || (pstSdc1xSysInfo->lNid                       != pstAppSdc1xSysInfo->lNid)
     || (pstSdc1xSysInfo->enBaseStationInfoIncl      != pstAppSdc1xSysInfo->enBaseStationInfoIncl)
     || ((PS_TRUE == pstSdc1xSysInfo->enBaseStationInfoIncl)
      && (pstSdc1xSysInfo->stBaseStationInfo.usBaseId != pstAppSdc1xSysInfo->stBaseStationInfo.usBaseId)))
    {
        PS_MEM_SET(&stClocinfoPara, 0, sizeof(TAF_MMA_CLOCINFO_PARA_STRU));
        stClocinfoPara.lSid                 = pstSdc1xSysInfo->lSid;
        stClocinfoPara.lNid                 = pstSdc1xSysInfo->lNid;
        stClocinfoPara.usPrevInUse          = pstSdc1xSysInfo->ucPrevInUse;

        if (PS_TRUE == pstSdc1xSysInfo->enServiceInfoIncl)
        {
            ulMccTmp = pstSdc1xSysInfo->stServiceInfo.ulMcc;
            usMncTmp = pstSdc1xSysInfo->stServiceInfo.usImsi11_12;
        }
        else
        {
            ulMccTmp = MMA_INVALID_MCC;
            usMncTmp = (VOS_UINT16)MMA_INVALID_MNC;
        }

        stClocinfoPara.ulMcc            = (VOS_UINT32)TAF_STD_TransformBcdMccToDeciDigit(ulMccTmp);
        stClocinfoPara.ulMnc            = (VOS_UINT32)TAF_STD_TransformBcdMncToDeciDigit(usMncTmp);

        if (PS_TRUE == pstSdc1xSysInfo->enBaseStationInfoIncl)
        {
            stClocinfoPara.ulBaseId         = pstSdc1xSysInfo->stBaseStationInfo.usBaseId;
            stClocinfoPara.lBaseLatitude    = pstSdc1xSysInfo->stBaseStationInfo.lBaseLatitude;
            stClocinfoPara.lBaseLongitude   = pstSdc1xSysInfo->stBaseStationInfo.lBaseLongitude;
        }
        else
        {
            stClocinfoPara.ulBaseId         = TAF_MMA_INVALID_BASE_ID;
            stClocinfoPara.lBaseLatitude    = TAF_MMA_INVALID_BASE_LATITUDE;
            stClocinfoPara.lBaseLongitude   = TAF_MMA_INVALID_BASE_LONGITUDE;
        }

        TAF_MMA_ReportClocinfo(&stClocinfoPara);
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ConvertCsimCardStatusToTafErrorCode
 ��������  : ת��CSIM״̬��TAF������
 �������  : enCsimStatus -- CSIM��״̬

 �������  : ��
 �� �� ֵ  : TAF_ERROR_CODE_ENUM_UINT32  -- ���ش�����

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_ERROR_CODE_ENUM_UINT32 TAF_MMA_ConvertCsimCardStatusToTafErrorCode(
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enCsimStatus
)
{
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode;

    switch (enCsimStatus)
    {
        case TAF_SDC_USIM_STATUS_VALID:
        case TAF_SDC_USIM_STATUS_ROMSIM:
            enErrorCode = TAF_ERR_NO_ERROR;
            break;

        case TAF_SDC_USIM_STATUS_NO_PRESENT:
            enErrorCode = TAF_ERR_USIM_SIM_CARD_NOTEXIST;
            break;

        case TAF_SDC_USIM_STATUS_SIM_PIN:
            enErrorCode = TAF_ERR_NEED_PIN1;
            break;

        case TAF_SDC_USIM_STATUS_SIM_PUK:
            enErrorCode = TAF_ERR_NEED_PUK1;
            break;

        case TAF_SDC_USIM_STATUS_NET_LCOK:
        case TAF_SDC_USIM_STATUS_IMSI_LCOK:
            enErrorCode = TAF_ERR_SIM_LOCK;
            break;

        case TAF_SDC_USIM_STATUS_READY_TIMEROUT:
            enErrorCode = TAF_ERR_SIM_FAIL;
            break;

        case TAF_SDC_USIM_STATUS_UNVALID:
        case TAF_SDC_USIM_STATUS_CS_UNVALID:
        case TAF_SDC_USIM_STATUS_PS_UNVALID:
        case TAF_SDC_USIM_STATUS_CS_PS_UNVALID:
        default:
            enErrorCode = TAF_ERR_USIM_SIM_INVALIDATION;
            break;
    }

    return enErrorCode;
}
#endif


/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateReportService
 ��������  : CLģʽ�£�����stNetworkInfo�е��ܵķ���״̬������CS�����״̬��PS�����״̬����
 �������  : ��
 �������  : ���ı�
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��30��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration_18�����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateReportService(VOS_VOID)
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCsServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enPsServiceStatus;

    enCsServiceStatus = TAF_SDC_GetCsServiceStatus();
    enPsServiceStatus = TAF_SDC_GetPsServiceStatus();

    /* �����ܵķ���״̬ */
    if ((NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == enCsServiceStatus)
     || (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == enPsServiceStatus) )
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE);
    }
    else if ((NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE_REGION == enCsServiceStatus)
          || (NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE_REGION == enPsServiceStatus) )
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_REGIONAL_LIMITED_SERVICE);
    }
    else if ((NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE == enCsServiceStatus)
          || (NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE == enPsServiceStatus) )
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE);
    }
    else if ((NAS_MSCC_PIF_SERVICE_STATUS_NO_IMSI == enCsServiceStatus)
          || (NAS_MSCC_PIF_SERVICE_STATUS_NO_IMSI == enPsServiceStatus) )
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE);
    }
    else
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_NO_SERVICE);

        /* LTEע��ʹ�� */
        if (VOS_TRUE == gstMmaValue.pg_StatusContext->ulTimMaxFlg)
        {
            TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_DEEP_SLEEP);
        }
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_IsUserOperate
 ��������  : �ж��Ƿ������û���������Ĳ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_TRUE�û���������Ĳ����� VOS_FALSE ���û���������Ĳ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��13��
    ��    ��   : j00354216
    �޸�����   : CDMA Iteration 18 �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsUserOperate(VOS_VOID)
{
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId;

    enFsmId = TAF_MMA_GetCurrFsmId();

    if ((TAF_MMA_FSM_SYS_CFG == enFsmId)
     || (TAF_MMA_FSM_PHONE_MODE == enFsmId)
     || (STA_FSM_ENABLE != g_StatusContext.ulFsmState))
    {
        /* �û��������� */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ProcMsccSystemAcquireEndInd3GppType
 ��������  : MMA�յ�MSCC_MMA_SYSTEM_ACQUIRE_END_IND��Ϣ��enAcqSysTypeΪMSCC_MMA_ACQ_SYS_TYPE_3GPP���ͣ�������Ϣ
 �������  : pstSysAcqEndInd   MSCC_MMA_SYSTEM_ACQUIRE_END_IND_STRU��Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��20��
    ��    ��   : l00324781
    �޸�����   : CDMA Iteration 18 �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_ProcMsccSystemAcquireEndInd3GppType(
    MSCC_MMA_SYSTEM_ACQUIRE_END_IND_STRU    *pstSysAcqEndInd
)
{
    TAF_MMA_PLMN_SELECTION_INFO_STRU                        stTafPlmnSelectInfo;

    PS_MEM_SET(&stTafPlmnSelectInfo, 0, sizeof(TAF_MMA_PLMN_SELECTION_INFO_STRU));

    /* RoamingBroker����ʹ������SIM������Location�¼� */
    if (VOS_TRUE == MN_MMA_GetRoamingBrokerFlg())
    {
        if (( MSCC_MMA_SYSTEM_ACQUIRE_RESULT_LIMITED_SERVICE == pstSysAcqEndInd->enResult)
         || ( MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_SERVICE      == pstSysAcqEndInd->enResult))
        {
            NAS_MMA_ReportLociStatus();
        }
    }
    /* ����������һ�����綼û����������UE�����޷��񣬶����ڿ�����ʼ��ʱ
       ����״̬Ҳ���޷������ͨ������״̬�ı��޷���location status�¼���
       ��Ҫ�ڴ˴���һ��,��AT&T��֤������֤�˳��� */
    else
    {
        if ((VOS_FALSE == g_StatusContext.ucIsReportedLocStatus)
         && ( MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_SERVICE == pstSysAcqEndInd->enResult))
        {
            NAS_MMA_ReportLociStatus();
        }
    }

    stTafPlmnSelectInfo.ulPlmnSelectRlst = TAF_MMA_ConvertServiceTypeToAtType(pstSysAcqEndInd->enResult);

    if (TAF_PH_PLMN_SELECTION_RESULT_INTERRUPT == stTafPlmnSelectInfo.ulPlmnSelectRlst)
    {
        stTafPlmnSelectInfo.ulPlmnSelectFlag = TAF_PH_PLMN_SELECTION_INTERRUPT;
    }
    else
    {
        stTafPlmnSelectInfo.ulPlmnSelectFlag = TAF_PH_PLMN_SELECTION_END;
    }

    if (VOS_TRUE == TAF_MMA_IsPlmnSelectInfoNeedRpt())
    {
        TAF_MMA_SndPlmnSelectionInd(&stTafPlmnSelectInfo);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateRatPrioFromClToGul
 ��������  : ����Start Req��Ϣ��Я���Ľ����������һ���޿�����ʱ�������CLģʽ�����ΪGUl
 �������  : TAF_MMA_RAT_ORDER_STRU     pstSndRatPrioList   ��ǰ֧�ֵĽ��뼼��
 �������  : TAF_MMA_RAT_ORDER_STRU     pstSndRatPrioList   �޸ĺ�ļ��뼼��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��10��
    ��    ��   : l00324781
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateRatPrioFromClToGul(
    TAF_MMA_RAT_ORDER_STRU             *pstSndRatPrioList
)
{
    VOS_UINT8                           ucIsClMode;
    VOS_UINT32                          ulIndex;
    TAF_MMA_GET_GEO_CTX_STRU           *pstGetGeoCtx;

    pstGetGeoCtx            = TAF_MMA_GetGeoCtxAddr();
    /* get geo NV�ر�,����Ҫ���� */
    if (VOS_FALSE == pstGetGeoCtx->stGetGeoNvCfg.ucCfgGetGeoFlag)
    {
        return;
    }

    /* ��ʼ��ΪVOS_FALSE,��ʾ��֧�֣��������VOS_TRUE����ʾ֧�� */
    ucIsClMode   = VOS_FALSE;

    /* ���жϵ�ǰ���뼼���Ƿ���1x+HRPD+LTE */
    for (ulIndex = 0; ulIndex < pstSndRatPrioList->ucRatOrderNum; ulIndex++)
    {
        if ((TAF_MMA_RAT_1X == pstSndRatPrioList->aenRatOrder[ulIndex])
         || (TAF_MMA_RAT_HRPD == pstSndRatPrioList->aenRatOrder[ulIndex]))
        {
            ucIsClMode = VOS_TRUE;
            break;
        }
    }

    /* ����CLģʽ�����޸�ΪGULģʽ */
    if (VOS_TRUE == ucIsClMode)
    {
        pstSndRatPrioList->aenRatOrder[0] = TAF_MMA_RAT_GSM;
        pstSndRatPrioList->aenRatOrder[1] = TAF_MMA_RAT_WCDMA;
        pstSndRatPrioList->aenRatOrder[2] = TAF_MMA_RAT_LTE;

        pstSndRatPrioList->ucRatOrderNum = 3;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsNeedProcessSystemAcquireResult
 ��������  : ����MSCC�ϱ���SYS_ACQ����ж��Ƿ���Ҫ֪ͨAPSģʽ�ı�
 �������  : enResult
 �������  : VOS_VOID
 �� �� ֵ  : VOS_TRUE��VOS_FALSE

  1.��    ��   : 2016��01��18��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsNeedProcessSystemAcquireResult(
    MSCC_MMA_SYSTEM_ACQUIRE_RESULT_ENUM_UINT32              enResult
)
{
    switch (enResult)
    {
        case MSCC_MMA_SYSTEM_ACQUIRE_RESULT_LIMITED_SERVICE:
        case MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_SERVICE:
        case MSCC_MMA_SYSTEM_ACQUIRE_RESULT_NO_RF:

            return VOS_TRUE;

        case MSCC_MMA_SYSTEM_ACQUIRE_RESULT_INTERRUPT:

            return VOS_FALSE;

        default :

            return VOS_FALSE;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetRatModeType
 ��������  : ��ȡRAT�ı�����
 �������  : enLastRatType -- �ϴ�CL RAT����
             enCurrRatType -- ��ǰCL RAT����

 �������  : ��
 �� �� ֵ  : TAF_MMA_RAT_MODE_GUL_TO_GUL ���� GUL���ģʽ�仯
             TAF_MMA_RAT_MODE_GUL_TO_CL  ���� GUL��CL��ģʽ�仯
             TAF_MMA_RAT_MODE_CL_TO_GUL  ���� CL��GUL��ģʽ�仯
             TAF_MMA_RAT_MODE_CL_TO_CL   ���� CL��CL��ģʽ�仯

 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_RAT_MODE_TYPE_ENUM_UINT8 TAF_MMA_GetRatModeType(
    TAF_MMA_RAT_SET_TYPE_ENUM_UINT8     enLastRatType,
    TAF_MMA_RAT_SET_TYPE_ENUM_UINT8     enCurrRatType
)
{
    return (g_aenRatModeTypeTab[enLastRatType][enCurrRatType]);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetRatModeChangeType
 ��������  : ���ݵ�ǰ�����ϴε�RAT���ã���ȡ��ǰRAT����������
 �������  : pstCurrRat -- ��ǰ���õ�RAT
             pstLastRat -- �ϴ����õ�RAT

 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- RAT�����仯
             VOS_FALSE -- RATδ�����仯
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : y00245242
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_RAT_MODE_TYPE_ENUM_UINT8 TAF_MMA_GetRatModeChangeType(
    TAF_MMA_RAT_ORDER_STRU             *pstCurrRat,
    TAF_MMA_RAT_ORDER_STRU             *pstLastRat
)
{
    VOS_UINT16                              i;
    TAF_MMA_RAT_SET_TYPE_ENUM_UINT8         enLastRatFlag;
    TAF_MMA_RAT_SET_TYPE_ENUM_UINT8         enCurrRatFlag;

    enLastRatFlag = TAF_MMA_RAT_SET_L_ONLY;
    enCurrRatFlag = TAF_MMA_RAT_SET_L_ONLY;

    /* ���û���ǰ���õ�syscfg�������Ƿ���1x����HRPD */
    for (i = 0; i < pstCurrRat->ucRatOrderNum; i++)
    {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        /* ���1X��HRPD���ڣ�����CL���� */
        if ((TAF_MMA_RAT_1X   == pstCurrRat->aenRatOrder[i])
         || (TAF_MMA_RAT_HRPD == pstCurrRat->aenRatOrder[i]))
        {
            enCurrRatFlag = TAF_MMA_RAT_SET_CL;
            break;
        }
#endif

        /* ���GSM��UTRAN���ڣ�����GUL���� */
        if ((TAF_MMA_RAT_GSM   == pstCurrRat->aenRatOrder[i])
         || (TAF_MMA_RAT_WCDMA == pstCurrRat->aenRatOrder[i]))
        {
            enCurrRatFlag = TAF_MMA_RAT_SET_GUL;
            break;
        }
    }

    /* ���û��ϴ����õ�syscfg�������Ƿ���1x����HRPD */
    for (i = 0; i < pstLastRat->ucRatOrderNum; i++)
    {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if ((TAF_MMA_RAT_1X   == pstLastRat->aenRatOrder[i])
         || (TAF_MMA_RAT_HRPD == pstLastRat->aenRatOrder[i]))
        {
            enLastRatFlag = TAF_MMA_RAT_SET_CL;
            break;
        }
#endif

        if ((TAF_MMA_RAT_GSM   == pstLastRat->aenRatOrder[i])
         || (TAF_MMA_RAT_WCDMA == pstLastRat->aenRatOrder[i]))
        {
            enLastRatFlag = TAF_MMA_RAT_SET_GUL;
            break;
        }
    }

    /* �����ϴε�RAT�����Լ���ǰ��RAT���ã���ȡRAT�仯������ */
    return (TAF_MMA_GetRatModeType(enLastRatFlag, enCurrRatFlag));
}
#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



