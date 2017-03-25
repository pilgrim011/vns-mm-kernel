/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MtcCtx.c
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2013��07��30��
  ����޸�   :
  ��������   : MTCģ��������Ĺ���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��7��30��
    ��    ��   : l60609
    �޸�����   : ������

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MtcCtx.h"
#include "MtcDebug.h"
#include "TafNvInterface.h"
#include "NasNvInterface.h"
#include "NVIM_Interface.h"
#include "MtcRfLcdIntrusion.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*lint -e767 �޸���: l00198894; */
#define    THIS_FILE_ID        PS_FILE_ID_MTC_CTX_C
/*lint +e767 �޸���: l00198894; */

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
MTC_CONTEXT_STRU                        g_stMtcCtx;


/*****************************************************************************
  3 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : MTC_GetCtxAddr
 ��������  : ��ȡMTC�����ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : MTC_CONTEXT_STRU* MTC�����ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : j00174725
    �޸�����   : V9R1 ���ſ�����Ŀ
*****************************************************************************/
MTC_CONTEXT_STRU* MTC_GetCtxAddr(VOS_VOID)
{
    return &g_stMtcCtx;
}

/*****************************************************************************
 �� �� ��  : MTC_GetIntrusionCtxAddr
 ��������  : ��ȡƵ�γ�ͻ�����ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : MTC_INTRUSION_CTX_STRU* Ƶ�γ�ͻ�����ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : j00174725
    �޸�����   : V9R1 ���ſ�����Ŀ
*****************************************************************************/
MTC_INTRUSION_CTX_STRU* MTC_GetIntrusionCtxAddr(VOS_VOID)
{
    return &(MTC_GetCtxAddr()->stIntrusionCtx);
}

/*****************************************************************************
 �� �� ��  : MTC_GetModemCtxAddr
 ��������  : ��ȡMTC MODEM��Ϣ�����ĵ�ַ
 �������  : �ڲ��ӿڣ�enModemId �ɵ����߱�֤modemId����Ч��
 �������  : ��
 �� �� ֵ  : MTC_MODEM_INFO_STRU* MODEM��Ϣ�����ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : j00174725
    �޸�����   : V9R1 ���ſ�����Ŀ
*****************************************************************************/
MTC_MODEM_INFO_STRU* MTC_GetModemCtxAddr(MODEM_ID_ENUM_UINT16 enModemId)
{
    return &(MTC_GetCtxAddr()->astModemInfo[enModemId]);
}

/*****************************************************************************
 �� �� ��  : MTC_InitIntrusionCtx
 ��������  : ��ʼ��Ƶ�γ�ͻ���������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : j00174725
    �޸�����   : V9R1 ���ſ�����Ŀ

  2.��    ��   : 2013��12��21��
    ��    ��   : l00198894
    �޸�����   : V9R1 Notch Bypass��Ŀ

  3.��    ��   : 2014��3��24��
    ��    ��   : A00165503
    �޸�����   : B39&B32 Intrusion
*****************************************************************************/
VOS_VOID MTC_InitIntrusionCtx(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    /* ��ʼ�������� */
    PS_MEM_SET(pstMtcIntrusionCtx, 0, sizeof(MTC_INTRUSION_CTX_STRU));

    /* ��ȡNV�� */
    ulRet = NV_Read(en_NV_Item_RF_INTRUSION_CFG,
                    &pstMtcIntrusionCtx->stIntrusionCfg,
                    sizeof(MTC_NV_RF_INTRUSION_CFG_STRU));
    if (VOS_OK != ulRet)
    {
        MTC_WARNING_LOG("MTC_InitIntrusionCtx: Read Nv Fail.");
    }

    /* Added by l00198894 for V9R1 Notch Bypass��Ŀ, 2013-12-21, begin */
    MTC_SetNotchEnalbeFlag(PS_FALSE);
    /* Added by l00198894 for V9R1 Notch Bypass��Ŀ, 2013-12-21, end */

    MTC_SetNarrowDcsEnalbeFlag(PS_FALSE);

    MTC_SetTlRfCtrlEnalbeFlag(PS_FALSE);

    MTC_SetRseCfgValue(PS_FALSE);

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_InitPsTransferCtx
 ��������  : ��ʼ��PS��Ǩ�����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��01��17��
    ��    ��   : l00198894
    �޸�����   : V9R1C53 C+L ������ѡ��Ŀ
*****************************************************************************/
VOS_VOID MTC_InitPsTransferCtx(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    MTC_PS_TRANSFER_CTX_STRU           *pstPsTransferCtx = VOS_NULL_PTR;

    pstPsTransferCtx = MTC_GetPsTransferCtxAddr();

    /* ��ʼ�������� */
    PS_MEM_SET(pstPsTransferCtx, 0, sizeof(MTC_PS_TRANSFER_CTX_STRU));

    /* Added by Y00213812 for ����������ѡ, 2014-04-10, begin */
    /* ��ʼ��PSTRANSFER���ϱ�״ֵ̬ */
    pstPsTransferCtx->enReportCause     = MTC_PS_TRANSFER_CAUSE_BUTT;
    pstPsTransferCtx->enRrcCause        = MTC_PS_TRANSFER_CAUSE_BUTT;
    /* Added by Y00213812 for ����������ѡ, 2014-04-10, begin */

    /* ��ȡNV�� */
    ulRet = NV_Read(en_NV_Item_PS_TRANSFER_CFG,
                    &pstPsTransferCtx->stPsTransferCfg,
                    sizeof(MTC_NV_PS_TRANSFER_CFG_STRU));
    if (VOS_OK != ulRet)
    {
        MTC_WARNING_LOG("MTC_InitPsTransferCtx: Read Nv Fail.");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_InitOperatorCustSolution
 ��������  : ��ʼ����Ӫ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��01��17��
    ��    ��   : l00198894
    �޸�����   : V9R1C53 C+L ������ѡ��Ŀ
*****************************************************************************/
VOS_VOID MTC_InitOperatorCustSolution(VOS_VOID)
{
    SVLTE_SUPPORT_FLAG_STRU             stSvlteSupportFlag;
    TAF_NV_LC_CTRL_PARA_STRU            stLcCtrlPara;

    PS_MEM_SET(&stSvlteSupportFlag, 0x00, sizeof(stSvlteSupportFlag));
    PS_MEM_SET(&stLcCtrlPara, 0x00, sizeof(stLcCtrlPara));

    /* ��SVLTE����NV */
    if (NV_OK != NV_Read(en_NV_Item_SVLTE_FLAG,
                         &stSvlteSupportFlag,
                         sizeof(SVLTE_SUPPORT_FLAG_STRU)))
    {
        MTC_ERROR_LOG("MTC_InitOperatorCustSolution(): en_NV_Item_SVLTE_FLAG error");
        stSvlteSupportFlag.ucSvlteSupportFlag = VOS_FALSE;
    }

    /* ��LC����NV */
    if (NV_OK != NV_Read(en_NV_Item_LC_Ctrl_PARA,
                         &stLcCtrlPara,
                         sizeof(TAF_NV_LC_CTRL_PARA_STRU)))
    {
        MTC_ERROR_LOG("MTC_InitOperatorCustSolution(): en_NV_Item_LC_Ctrl_PARA error");
        stLcCtrlPara.ucLCEnableFlg = VOS_FALSE;
    }

    if (VOS_TRUE == stSvlteSupportFlag.ucSvlteSupportFlag)
    {
        MTC_SetOperatorCustSolution(MTC_OPERATOR_CUST_CMCC_SVLTE);
    }
    else if (VOS_TRUE == stLcCtrlPara.ucLCEnableFlg)
    {
        MTC_SetOperatorCustSolution(MTC_OPERATOR_CUST_CT_LC);
    }
    else
    {
        MTC_SetOperatorCustSolution(MTC_OPERATOR_CUST_NONE);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_ParsePlatFormRat
 ��������  : �������뼼��
 �������  : pucRat  --MTC������뼼��
 �������  : pstPlatFormRat  -- NV�еĽ�������
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��12��
    ��    ��   : j00174725
    �޸�����  : V9R1 ���ſ�����Ŀ
*****************************************************************************/
VOS_VOID MTC_ParsePlatFormRat(
    VOS_UINT8                          *pucRat,
    PLATAFORM_RAT_CAPABILITY_STRU      *pstPlatFormRat
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT16                          usRatNum;

    usRatNum = pstPlatFormRat->usRatNum;
    *pucRat  = 0;

    /* ����Ӧbit����Ϊ1 */
    for (ulIndex = 0; ulIndex < usRatNum; ulIndex++)
    {
        if (pstPlatFormRat->aenRatList[ulIndex] >= PLATFORM_RAT_BUTT)
        {
            return;
        }

        *pucRat |= (VOS_UINT8)MTC_SET_BIT(pstPlatFormRat->aenRatList[ulIndex]);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_IsSupportRatType
 ��������  : MODEM�Ƿ�֧�ָý��뼼��
 �������  : enRatMode  -- ���뼼��
 �������  : ��
 �� �� ֵ  : VOS_TRUE   -- ֧�ָý��뼼��
              VOS_FALSE  -- ��֧�ָý��뼼��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : j00174725
    �޸�����   : V9R1 ���ſ�����Ŀ
*****************************************************************************/
VOS_UINT32 MTC_IsSupportRatType(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_RATMODE_ENUM_UINT8              enRatMode
)
{
    if (enRatMode >= MTC_RATMODE_BUTT)
    {
        return VOS_FALSE;
    }

    /* �ж�modemId�Ƿ���Ч */
    if (enModemId >= MODEM_ID_BUTT)
    {
        return VOS_FALSE;
    }

    if (0 != (MTC_GetModemCtxAddr(enModemId)->ucRatCap & MTC_SET_BIT(enRatMode)))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : MTC_ResetModemInfo
 ��������  : ��λMTCģ����MODEM��Ϣ
 �������  : enModemId   --modemID
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : j00174725
    �޸�����   : V9R1 ���ſ�����Ŀ

  2.��    ��   : 2014��3��24��
    ��    ��   : A00165503
    �޸�����   : B39&B32 Intrusion

  3.��    ��   : 2014��11��17��
    ��    ��   : l00198894
    �޸�����   : ECID�����Ʒ�߶�������
*****************************************************************************/
VOS_VOID MTC_ResetModemInfo(MODEM_ID_ENUM_UINT16 enModemId)
{
    MTC_MODEM_INFO_STRU                *pstModemInfo = VOS_NULL_PTR;

    pstModemInfo = MTC_GetModemCtxAddr(enModemId);

    PS_MEM_SET(&pstModemInfo->stSerCellBandInfo, 0, sizeof(RRC_MTC_MS_BAND_INFO_STRU));
    PS_MEM_SET(&pstModemInfo->stCurBandInfo, 0, sizeof(RRC_MTC_MS_BAND_INFO_STRU));
    PS_MEM_SET(&pstModemInfo->stSrvInfo, 0, sizeof(MTC_MODEM_SERVICE_INFO_STRU));
    pstModemInfo->enRatMode = MTC_RATMODE_BUTT;

    /* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */
    PS_MEM_SET(&pstModemInfo->stConnStateInfo, 0, sizeof(MTC_MODEM_CONN_STATE_INFO_STRU));
    /* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, End */

    PS_MEM_SET(&pstModemInfo->stGsmCellInfoEx, 0, sizeof(MTC_GSM_CELLINFO_EX_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_InitModemCtx
 ��������  : ��ʼMTCģ����MODEM��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : j00174725
    �޸�����   : V9R1 ���ſ�����Ŀ

  2.��    ��   : 2015��11��3��
    ��    ��   : h00313353
    �޸�����   : Iteration 19
*****************************************************************************/
VOS_VOID MTC_InitModemCtx(VOS_VOID)
{
    VOS_UINT32                          ulRet;
    VOS_UINT16                          usIndex;

    PLATAFORM_RAT_CAPABILITY_STRU       stModemPlatFormRat;
    MTC_MODEM_INFO_STRU                *pastModemCtxAddr    = VOS_NULL_PTR;
    MTC_OUTSIDE_MODEM_INFO_STRU        *pstOutModemCtxAddr  = VOS_NULL_PTR;

    for (usIndex = 0; usIndex < MODEM_ID_BUTT; usIndex++)
    {
        PS_MEM_SET(&stModemPlatFormRat, 0, sizeof(stModemPlatFormRat));

        /* ��ȡModem������ ��ַ */
        pastModemCtxAddr = MTC_GetModemCtxAddr(usIndex);

        PS_MEM_SET(pastModemCtxAddr, 0, sizeof(MTC_MODEM_INFO_STRU));

        PS_MEM_SET(&(pastModemCtxAddr->stRatCfg), 0xFF, sizeof(MTC_MODEM_RAT_CONFIG_STRU));

        pastModemCtxAddr->enCsimState   = TAF_MTC_USIMM_CARD_SERVIC_BUTT;
        pastModemCtxAddr->enUsimState   = TAF_MTC_USIMM_CARD_SERVIC_BUTT;

        /* ��ȡModem��ǰ���뼼��nv�� */
        ulRet = NV_ReadEx(usIndex,
                          en_NV_Item_Platform_RAT_CAP,
                          &stModemPlatFormRat,
                          sizeof(PLATAFORM_RAT_CAPABILITY_STRU));
        if (VOS_OK != ulRet)
        {
            MTC_WARNING_LOG("MTC_InitIntrusionCtx: Read Nv Fail.");
            continue;
        }

        MTC_ParsePlatFormRat(&(pastModemCtxAddr->ucRatCap), &stModemPlatFormRat);

        pastModemCtxAddr->enRatMode = MTC_RATMODE_BUTT;
    }

    /* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */
    /* ��ʼ���ⲿmodem�����ļ���Ϣ */
    for (usIndex = MTC_OUTSIDE_MODEM_CDMA; usIndex < MTC_OUTSIDE_MODEM_BUTT; usIndex++ )
    {
        pstOutModemCtxAddr =  MTC_GetOutSideModemCtxAddr(usIndex);

        PS_MEM_SET(pstOutModemCtxAddr, 0x0, sizeof(MTC_OUTSIDE_MODEM_INFO_STRU));
    }

    /* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, End */

    /* ��ʼ��CDMA Modem Id */
    MTC_GetCtxAddr()->enCdmaModemId = MODEM_ID_BUTT;

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_InitCtx
 ��������  : ��ʼ��MTC������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : j00174725
    �޸�����   : V9R1 ���ſ�����Ŀ
  2.��    ��   : 2014��01��17��
    ��    ��   : l00198894
    �޸�����   : V9R1C53 C+L ������ѡ��Ŀ
*****************************************************************************/
VOS_VOID MTC_InitCtx(VOS_VOID)
{
    /* ��ʼ��MTC������Ϣ������ */
    MTC_InitDebugCtx();

    /* ��ʼ��Ƶ�γ�ͻ��������� */
    MTC_InitIntrusionCtx();

    /* ��ʼ��MTCģ��PS��Ǩ����������� */
    MTC_InitPsTransferCtx();

    /* ��ʼ��MTCģ��Modem��Ϣ������ */
    MTC_InitModemCtx();

    /* ��ʼ��MTCģ����Ӫ�̶������� */
    MTC_InitOperatorCustSolution();

    /* ��ʼ��RF&LCD���Ź�������� */
    MTC_InitRfLcdIntrusionCtx();

    return ;
}

/*****************************************************************************
 �� �� ��  : MTC_GetIntrusionCfg
 ��������  : ��ȡƵ�γ�ͻ������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : MTC_CFG_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : j00174725
    �޸�����   : V9R1 ���ſ�����Ŀ
*****************************************************************************/
MTC_CFG_ENUM_UINT8 MTC_GetIntrusionCfg(VOS_VOID)
{
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    if (0 != (pstMtcIntrusionCtx->stIntrusionCfg.ucSolutionMask & MTC_INTRUSION_CFG_BIT))
    {
        return MTC_CFG_ENABLE;
    }
    else
    {
        return MTC_CFG_DISABLE;
    }
}

/*****************************************************************************
 �� �� ��  : MTC_SetModemPowerState
 ��������  : ���ÿ��ػ�״̬,ModemID��Ч���ɵ����߱�֤
 �������  : enModemId  -- Modem ID
             enState    -- ���ػ�״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : j00174725
    �޸�����   : V9R1 ���ſ�����Ŀ
*****************************************************************************/
VOS_VOID MTC_SetModemPowerState(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enState
)
{
    MTC_GetCtxAddr()->astModemInfo[enModemId].enPowerState = enState;

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_GetModemPowerState
 ��������  : ��ȡ���ػ�״̬��ModemID��Ч���ɵ����߱�֤
 �������  : enModemId  -- Modem ID
 �������  : ��
 �� �� ֵ  : MTC_MODEM_POWER_STATE_ENUM_UINT8 ���ػ�״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : j00174725
    �޸�����   : V9R1 ���ſ�����Ŀ
*****************************************************************************/
MTC_MODEM_POWER_STATE_ENUM_UINT8 MTC_GetModemPowerState(MODEM_ID_ENUM_UINT16 enModemId)
{
    return MTC_GetModemCtxAddr(enModemId)->enPowerState;
}

/*****************************************************************************
 �� �� ��  : MTC_SetModemImsaState
 ��������  : ����IMSA���ػ�״̬, ModemID��Ч���ɵ����߱�֤
 �������  : enModemId  -- Modem ID
             enState    -- IMSA���ػ�״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��13��
    ��    ��   : l00198894
    �޸�����   : VOLTE Rank1������Ŀ
*****************************************************************************/
VOS_VOID MTC_SetModemImsaState(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enState
)
{
    MTC_GetCtxAddr()->astModemInfo[enModemId].enImsaState = enState;

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_GetModemImsaState
 ��������  : ��ȡIMSA���ػ�״̬��ModemID��Ч���ɵ����߱�֤
 �������  : enModemId  -- Modem ID
 �������  : ��
 �� �� ֵ  : MTC_MODEM_POWER_STATE_ENUM_UINT8 IMSA���ػ�״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��13��
    ��    ��   : l00198894
    �޸�����   : VOLTE Rank1������Ŀ

*****************************************************************************/
MTC_MODEM_POWER_STATE_ENUM_UINT8 MTC_GetModemImsaState(MODEM_ID_ENUM_UINT16 enModemId)
{
    return MTC_GetModemCtxAddr(enModemId)->enImsaState;
}

/*****************************************************************************
 �� �� ��  : MTC_SetModemImsVoiceCap
 ��������  : ����IMS��������״̬, ModemID��Ч���ɵ����߱�֤
 �������  : enModemId  -- Modem ID
             enState    -- IMS��������״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��17��
    ��    ��   : w00316404
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID MTC_SetModemImsVoiceCap(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MODEM_IMS_VOICE_CAP_ENUM_UINT8  enState
)
{
    MTC_GetModemCtxAddr(enModemId)->enImsVoiceCap = enState;

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_GetModemImsVoiceCap
 ��������  : ��ȡIMS��������״̬��ModemID��Ч���ɵ����߱�֤
 �������  : enModemId  -- Modem ID
 �������  : ��
 �� �� ֵ  : MTC_MODEM_IMS_VOICE_CAP_ENUM_UINT8 IMS��������״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��17��
    ��    ��   : w00316404
    �޸�����   : ��������
*****************************************************************************/
MTC_MODEM_IMS_VOICE_CAP_ENUM_UINT8 MTC_GetModemImsVoiceCap(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return MTC_GetModemCtxAddr(enModemId)->enImsVoiceCap;
}

/*****************************************************************************
 �� �� ��  : MTC_SetModemUsimValidFlag
 ��������  : ���ÿ�״̬�Ƿ���Ч,ModemID��Ч���ɵ����߱�֤
 �������  : enModemId            -- Modem ID
             ucUsimValidStatus    -- ��״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��23��
    ��    ��   : z00161729
    �޸�����   : DTS2014012305088:svlte���Կ�������Ч����mtc�����ϱ�pstransfer:0

*****************************************************************************/
VOS_VOID MTC_SetModemUsimValidFlag(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucUsimValidStatus
)
{
    MTC_GetCtxAddr()->astModemInfo[enModemId].ucUsimValidFlag = ucUsimValidStatus;

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_GetModemUsimValidFlag
 ��������  : ��ȡ��״̬�Ƿ���Ч��ʶ��ModemID��Ч���ɵ����߱�֤
 �������  : enModemId  -- Modem ID
 �������  : ��
 �� �� ֵ  : ��״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��23��
    ��    ��   : z00161729
    �޸�����   : DTS2014012305088:svlte���Կ�������Ч����mtc�����ϱ�pstransfer:0

*****************************************************************************/
VOS_UINT8 MTC_GetModemUsimValidFlag(MODEM_ID_ENUM_UINT16 enModemId)
{
    return MTC_GetModemCtxAddr(enModemId)->ucUsimValidFlag;
}


/*****************************************************************************
 �� �� ��  : MTC_SetModemRatMode
 ��������  : ���ý���ģʽ��Ϣ,ModemID��Ч���ɵ����߱�֤
 �������  : enModemId  -- Modem ID
             enRatMode  -- ����ģʽ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ
*****************************************************************************/
VOS_VOID MTC_SetModemRatMode(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_RATMODE_ENUM_UINT8              enRatMode
)
{
    MTC_GetModemCtxAddr(enModemId)->enRatMode = enRatMode;

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_GetModemRatMode
 ��������  : ��ȡ����ģʽ��ModemID��Ч���ɵ����߱�֤
 �������  : enModemId  -- Modem ID
 �������  : ��
 �� �� ֵ  : MTC_RATMODE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ
*****************************************************************************/
MTC_RATMODE_ENUM_UINT8 MTC_GetModemRatMode(MODEM_ID_ENUM_UINT16 enModemId)
{
    return MTC_GetCtxAddr()->astModemInfo[enModemId].enRatMode;
}

/*****************************************************************************
 �� �� ��  : MTC_SetModemCallSrvExistFlg
 ��������  : ����Modem CS�����ҵ����ڱ�־λ,ModemID��Ч���ɵ����߱�֤
 �������  : enModemId  -- Modem ID
             ucFlg      -- ��־λ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ
*****************************************************************************/
VOS_VOID MTC_SetModemCallSrvExistFlg(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucFlg
)
{
    MTC_GetCtxAddr()->astModemInfo[enModemId].stSrvInfo.ucCallSrvExistFlg = ucFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_SetModemSmsSrvExistFlg
 ��������  : ����Modem CS�����ҵ����ڱ�־λ��ModemID��Ч���ɵ����߱�֤
 �������  : enModemId  -- Modem ID
             ucFlg      -- ��־λ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ
*****************************************************************************/
VOS_VOID MTC_SetModemSmsSrvExistFlg(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucFlg
)
{
    MTC_GetCtxAddr()->astModemInfo[enModemId].stSrvInfo.ucSmsSrvExistFlg = ucFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_SetModemSsSrvExistFlg
 ��������  : ����Modem CS�򲹳�ҵ����ڱ�־λ��ModemID��Ч���ɵ����߱�֤
 �������  : enModemId  -- Modem ID
             ucFlg      -- ��־λ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ
*****************************************************************************/
VOS_VOID MTC_SetModemSsSrvExistFlg(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucFlg
)
{
    MTC_GetCtxAddr()->astModemInfo[enModemId].stSrvInfo.ucSsSrvExistFlg = ucFlg;

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_GetModemCsSrvExistFlg
 ��������  : ����Modem CS��ҵ����ڱ�־λ��ModemID��Ч���ɵ����߱�֤
 �������  : enModemId  -- Modem ID
 �������  : ��
 �� �� ֵ  : MTC_CS_SERVICE_STATE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ
*****************************************************************************/
MTC_CS_SERVICE_STATE_ENUM_UINT8 MTC_GetModemCsSrvExistFlg(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    MTC_MODEM_SERVICE_INFO_STRU        *pstSrvInfo = VOS_NULL_PTR;

    pstSrvInfo = &(MTC_GetCtxAddr()->astModemInfo[enModemId].stSrvInfo);

    /* ���ڵ�ǰ���С����š�����ҵ�񶼲�����ʱ��ΪCS����񲻴��� */
    if ( (VOS_FALSE == pstSrvInfo->ucCallSrvExistFlg)
      && (VOS_FALSE == pstSrvInfo->ucSmsSrvExistFlg)
      && (VOS_FALSE == pstSrvInfo->ucSsSrvExistFlg) )
    {
        return MTC_CS_NO_SERVICE;
    }

    return MTC_CS_IN_SERVICE;
}

/*****************************************************************************
 �� �� ��  : MTC_GetModemCurBandInfo
 ��������  : ��ȡModem��ǰƵ����Ϣ��ModemID��Ч���ɵ����߱�֤
 �������  : ��
 �������  : ��
 �� �� ֵ  : RRC_MTC_MS_BAND_INFO_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : l00198894
    �޸�����   : V9R1 ���ſ�����Ŀ
*****************************************************************************/
RRC_MTC_MS_BAND_INFO_STRU* MTC_GetModemCurBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(MTC_GetCtxAddr()->astModemInfo[enModemId].stCurBandInfo);
}

/*****************************************************************************
 �� �� ��  : MTC_ResetModemCurBandInfo
 ��������  : ���Modem��ǰƵ����Ϣ��ModemID��Ч���ɵ����߱�֤
 �������  : enModemId   -- modem id
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��05��
    ��    ��   : j00174725
    �޸�����   : DTS2015102706654
*****************************************************************************/
VOS_VOID MTC_ResetModemCurBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    PS_MEM_SET(MTC_GetModemCurBandInfo(enModemId), 0x0, sizeof(RRC_MTC_MS_BAND_INFO_STRU));

    return;
}


/*****************************************************************************
 �� �� ��  : MTC_GetModemNCellBandInfo
 ��������  : ��ȡModem����Ƶ����Ϣ��ModemID��Ч���ɵ����߱�֤
 �������  : enModemId
 �������  : ��
 �� �� ֵ  : RRC_MTC_MS_BAND_INFO_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��05��
    ��    ��   : j00174725
    �޸�����   : DTS2015102706654
*****************************************************************************/
RRC_MTC_MS_BAND_INFO_STRU* MTC_GetModemNCellBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(MTC_GetCtxAddr()->astModemInfo[enModemId].stNCellBandInfo);
}


/*****************************************************************************
 �� �� ��  : MTC_SetModemNCellBandInfo
 ��������  : ����Modem����Ƶ����Ϣ��ModemID��Ч���ɵ����߱�֤
 �������  : enModemId   -- modem id
             enBandNum   -- Band No.
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��05��
    ��    ��   : j00174725
    �޸�����   : DTS2015102706654
*****************************************************************************/
VOS_VOID MTC_SetModemNCellBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_BAND_INFO_ENUM_UINT16           enBandNum
)
{
    VOS_UINT64                          *pulBandInfo;

    /* ���Band����Ч�� */
    if (enBandNum > MTC_FREQ_BAND44)
    {
        return;
    }

    pulBandInfo     = (VOS_UINT64 *)MTC_GetCtxAddr()->astModemInfo[enModemId].stNCellBandInfo.aulBandInfo;

    *pulBandInfo    |= MTC_SET_BIT64(enBandNum);

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_ResetNCellBandInfo
 ��������  : ���Modem����Ƶ����Ϣ��ModemID��Ч���ɵ����߱�֤
 �������  : enModemId   -- modem id
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��05��
    ��    ��   : j00174725
    �޸�����   : DTS2015102706654
*****************************************************************************/
VOS_VOID MTC_ResetNCellBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    PS_MEM_SET(MTC_GetModemNCellBandInfo(enModemId), 0x0, sizeof(RRC_MTC_MS_BAND_INFO_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_GetBufAddr
 ��������  : ��ȡ������Ϣ��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : MTC_MSG_BUF_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��05��
    ��    ��   : j00174725
    �޸�����   : DTS2015102706654
*****************************************************************************/
MTC_MSG_BUF_STRU* MTC_GetBufAddr(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(MTC_GetCtxAddr()->astModemInfo[enModemId].stBufMsg);
}


/*****************************************************************************
 �� �� ��  : MTC_GetModemSerCellBandInfo
 ��������  : ��ȡModem��ǰƵ����Ϣ��ModemID��Ч���ɵ����߱�֤
 �������  : enModemId --- MODEM ID (��Ч���ɵ����߱�֤)
 �������  : ��
 �� �� ֵ  : RRC_MTC_MS_BAND_INFO_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��24��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
RRC_MTC_MS_BAND_INFO_STRU* MTC_GetModemSerCellBandInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(MTC_GetCtxAddr()->astModemInfo[enModemId].stSerCellBandInfo);
}

/*****************************************************************************
 �� �� ��  : MTC_SetNotchEnalbeFlag
 ��������  : ����Notchʹ��״̬��־
 �������  : PS_BOOL_ENUM_UINT8 enFlag
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��21��
    ��    ��   : z60575
    �޸�����   : V9R1 Notch Bypass��Ŀ
*****************************************************************************/
VOS_VOID MTC_SetNotchEnalbeFlag(PS_BOOL_ENUM_UINT8 enFlag)
{
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    pstMtcIntrusionCtx->enNotchEnableFlag = enFlag;

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_GetNotchEnalbeFlag
 ��������  : ��ȡnotchʹ�ܱ�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : PS_BOOL_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��21��
    ��    ��   : z60575
    �޸�����   : V9R1 Notch Bypass��Ŀ
*****************************************************************************/
PS_BOOL_ENUM_UINT8 MTC_GetNotchEnalbeFlag(VOS_VOID)
{
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    return pstMtcIntrusionCtx->enNotchEnableFlag;
}

/*****************************************************************************
 �� �� ��  : MTC_GetNotchCfg
 ��������  : ��ȡNotch Bypass���Ե����ÿ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : MTC_CFG_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��21��
    ��    ��   : z60575
    �޸�����   : V9R1 Notch Bypass��Ŀ
*****************************************************************************/
MTC_CFG_ENUM_UINT8 MTC_GetNotchCfg(VOS_VOID)
{
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    if (0 != (pstMtcIntrusionCtx->stIntrusionCfg.ucSolutionMask & MTC_NOTCH_CFG_BIT))
    {
        return MTC_CFG_ENABLE;
    }
    else
    {
        return MTC_CFG_DISABLE;
    }
}

/*****************************************************************************
 �� �� ��  : MTC_SetNarrowDcsEnalbeFlag
 ��������  : ����NarrowDcsʹ��״̬��־
 �������  : PS_BOOL_ENUM_UINT8 enFlag
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��02��13��
    ��    ��   : f00179208
    �޸�����   : Jazz Narrow Band dcs��Ŀ
*****************************************************************************/
VOS_VOID MTC_SetNarrowDcsEnalbeFlag(PS_BOOL_ENUM_UINT8 enFlag)
{
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    pstMtcIntrusionCtx->enNarrowDcsEnableFlag = enFlag;

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_GetNarrowDcsEnalbeFlag
 ��������  : ��ȡNarrowDcsʹ�ܱ�־
 �������  : ��
 �������  : ��
 �� �� ֵ  : PS_BOOL_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��02��13��
    ��    ��   : f00179208
    �޸�����   : Jazz Narrow Band dcs��Ŀ
*****************************************************************************/
PS_BOOL_ENUM_UINT8 MTC_GetNarrowDcsEnalbeFlag(VOS_VOID)
{
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    return pstMtcIntrusionCtx->enNarrowDcsEnableFlag;
}

/*****************************************************************************
 �� �� ��  : MTC_GetNarrowBandDcsCfg
 ��������  : ��ȡNarrow Band Dcs���Ե����ÿ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : MTC_CFG_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��02��13��
    ��    ��   : f00179208
    �޸�����   : Jazz Narrow Band dcs��Ŀ
*****************************************************************************/
MTC_CFG_ENUM_UINT8 MTC_GetNarrowBandDcsCfg(VOS_VOID)
{
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    if (0 != (pstMtcIntrusionCtx->stIntrusionCfg.ucSolutionMask & MTC_NARROW_BAND_DCS_CFG_BIT))
    {
        return MTC_CFG_ENABLE;
    }
    else
    {
        return MTC_CFG_DISABLE;
    }
}



/*****************************************************************************
 �� �� ��  : MTC_GetTlRfCtrlCfg
 ��������  : ��ȡTL��Ƶ�������Ե����ÿ���
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : MTC_CFG_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��24��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���

  2.��    ��   : 2014��4��24��
    ��    ��   : Y00213812
    �޸�����   : DTS2014042306844: FORTIFY����޸�
*****************************************************************************/
MTC_CFG_ENUM_UINT8 MTC_GetTlRfCtrlCfg(VOS_VOID)
{
    MTC_RF_INTRUSION_CFG_STRU          *pstRfIntrusionCfg = VOS_NULL_PTR;
    MTC_CFG_ENUM_UINT8                  enMtcCfg;

    pstRfIntrusionCfg = (MTC_RF_INTRUSION_CFG_STRU *)&(MTC_GetIntrusionCtxAddr()->stIntrusionCfg);
    enMtcCfg          = (VOS_TRUE == pstRfIntrusionCfg->ucTlRfCtrlCfg) ? MTC_CFG_ENABLE : MTC_CFG_DISABLE;

    return enMtcCfg;
}

/*****************************************************************************
 �� �� ��  : MTC_SetTlRfCtrlEnalbeFlag
 ��������  : ����TL���з�����Ʊ�ʶ
 �������  : PS_BOOL_ENUM_UINT8 enFlag
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��24��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID MTC_SetTlRfCtrlEnalbeFlag(PS_BOOL_ENUM_UINT8 enFlag)
{
    MTC_GetIntrusionCtxAddr()->enTlRfCtrlEnableFlag = enFlag;
    return;
}

/*****************************************************************************
 �� �� ��  : MTC_GetTlRfCtrlEnalbeFlag
 ��������  : ��ȡTL���з�����Ʊ�ʶ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : PS_BOOL_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��24��
    ��    ��   : A00165503
    �޸�����   : �����ɺ���
*****************************************************************************/
PS_BOOL_ENUM_UINT8 MTC_GetTlRfCtrlEnalbeFlag(VOS_VOID)
{
    return MTC_GetIntrusionCtxAddr()->enTlRfCtrlEnableFlag;
}

/*****************************************************************************
 �� �� ��  : MTC_GetPsTransferCfg
 ��������  : ��ȡPS Ǩ�����Ե�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : MTC_PS_TRANSFER_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��21��
    ��    ��   : z60575
    �޸�����   : V9R1 Notch Bypass��Ŀ
*****************************************************************************/
MTC_PS_TRANSFER_ENUM_UINT8 MTC_GetPsTransferCfg(VOS_VOID)
{
    return MTC_GetCtxAddr()->stPsTransferCtx.stPsTransferCfg.enSolutionCfg;
}

/*****************************************************************************
 �� �� ��  : MTC_GetPsTransferCtxAddr
 ��������  : ��ȡPS Ǩ�����������ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : MTC_PS_TRANSFER_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��21��
    ��    ��   : z60575
    �޸�����   : V9R1 Notch Bypass��Ŀ
*****************************************************************************/
MTC_PS_TRANSFER_CTX_STRU* MTC_GetPsTransferCtxAddr(VOS_VOID)
{
    return &(MTC_GetCtxAddr()->stPsTransferCtx);
}

/*****************************************************************************
 �� �� ��  : MTC_GetModemNetworkInfoAddr
 ��������  : ��ȡModem��ǰפ��������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : MTC_MODEM_NETWORK_INFO_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��01��17��
    ��    ��   : l00198894
    �޸�����   : V9R1C53 C+L ������ѡ��Ŀ
*****************************************************************************/
MTC_MODEM_NETWORK_INFO_STRU* MTC_GetModemNetworkInfoAddr(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(MTC_GetCtxAddr()->astModemInfo[enModemId].stNetworkInfo);
}

/*****************************************************************************
 �� �� ��  : MTC_GetOperatorCustSolution
 ��������  : ��ȡ��Ӫ�̶��Ʒ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : MTC_OPERATOR_CUST_SOLUTION_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��01��17��
    ��    ��   : l00198894
    �޸�����   : V9R1C53 C+L ������ѡ��Ŀ
*****************************************************************************/
MTC_OPERATOR_CUST_SOLUTION_ENUM_UINT8 MTC_GetOperatorCustSolution(VOS_VOID)
{
    return MTC_GetCtxAddr()->enOperatorCustSolution;
}

/*****************************************************************************
 �� �� ��  : MTC_SetOperatorCustSolution
 ��������  : ������Ӫ�̶��Ʒ���
 �������  : enOperatorCustSolution
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��01��17��
    ��    ��   : l00198894
    �޸�����   : V9R1C53 C+L ������ѡ��Ŀ
*****************************************************************************/
VOS_VOID MTC_SetOperatorCustSolution(
    MTC_OPERATOR_CUST_SOLUTION_ENUM_UINT8   enOperatorCustSolution
)
{
    MTC_GetCtxAddr()->enOperatorCustSolution = enOperatorCustSolution;
    return;
}


/*****************************************************************************
 �� �� ��  : MTC_GetRfLcdIntrusionCtxAddr
 ��������  : ��ȡRF&LCD���Ź�������ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : MTC_RF_LCD_INTRUSION_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��03��04��
    ��    ��   : j00174725
    �޸�����   : RF&LCD INTRUSION��Ŀ
*****************************************************************************/
MTC_RF_LCD_INTRUSION_CTX_STRU* MTC_GetRfLcdIntrusionCtxAddr(VOS_VOID)
{
    return &(MTC_GetCtxAddr()->stRfLcdIntrusionCtx);
}

/*****************************************************************************
 �� �� ��  : MTC_GetMipiClkRcvPid
 ��������  : ��ȡ^mipiclk�����ϱ����յ�MTA Pid
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��03��04��
    ��    ��   : j00174725
    �޸�����   : RF&LCD INTRUSION��Ŀ
*****************************************************************************/
VOS_UINT32 MTC_GetMipiClkRcvPid(VOS_VOID)
{
    return MTC_GetRfLcdIntrusionCtxAddr()->ulMipiClkReportModemId;
}

/*****************************************************************************
 �� �� ��  : MTC_ReadRfLcdCfgNv
 ��������  : ��ȡRF&LCD����NV��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��03��04��
    ��    ��   : j00174725
    �޸�����   : RF&LCD INTRUSION��Ŀ
*****************************************************************************/
VOS_VOID MTC_ReadRfLcdCfgNv(VOS_VOID)
{
    VOS_UINT16                          j;
    VOS_UINT16                          i;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulFlag;
    MTC_NVIM_RF_LCD_CFG_STRU            stRfLcdCfg;
    MTC_RF_LCD_INTRUSION_CTX_STRU      *pstRfLcdIntrusionCtx = VOS_NULL_PTR;

    /* ���� */
    PS_MEM_SET(&stRfLcdCfg, 0x0, sizeof(MTC_NVIM_RF_LCD_CFG_STRU));

    pstRfLcdIntrusionCtx = MTC_GetRfLcdIntrusionCtxAddr();

    /* ��ȡen_NV_Item_MTC_RF_LCD_CFG NV�� */
    ulRet = NV_Read(en_NV_Item_MTC_RF_LCD_CFG,
                    &stRfLcdCfg,
                    sizeof(MTC_NVIM_RF_LCD_CFG_STRU));
    if (VOS_OK != ulRet)
    {
        pstRfLcdIntrusionCtx->usEnableBitMap = 0x0;
        MTC_WARNING1_LOG("MTC_ReadRfLcdCfgNv: Read Nv Fail.", en_NV_Item_MTC_RF_LCD_CFG);
    }
    else
    {
        pstRfLcdIntrusionCtx->usFreqWidth  = stRfLcdCfg.usFreqWidth;
        pstRfLcdIntrusionCtx->usEnableBitMap = stRfLcdCfg.usEnableBitMap;
    }

    if (0x0 == pstRfLcdIntrusionCtx->usEnableBitMap)
    {
        return;
    }

    /* �ж�Ƶ����Ϣ����ȷ�� */
    for (i = 0; i < MTC_RF_LCD_MIPICLK_MAX_NUM; i++)
    {
        ulFlag = VOS_FALSE;
        pstRfLcdIntrusionCtx->astRfLcdFreqList[i].ulMipiClk     = stRfLcdCfg.astRfMipiClkFreqList[i].ulMipiClk;
        pstRfLcdIntrusionCtx->astRfLcdFreqList[i].ulAvailNum    = 0;

        for(j = 0; j < MTC_RF_LCD_MIPICLK_FREQ_MAX_NUM; j++)
        {
            /* Ƶ��ֵ��Ҫ���ڴ��������ӦMIPICLK�ĺ���Ƶ�ʶ���Ϊ��Чֵ */
            if (stRfLcdCfg.astRfMipiClkFreqList[i].aulFreq[j] >= pstRfLcdIntrusionCtx->usFreqWidth)
            {
                pstRfLcdIntrusionCtx->astRfLcdFreqList[i].aulFreq[j] = stRfLcdCfg.astRfMipiClkFreqList[i].aulFreq[j];
                pstRfLcdIntrusionCtx->astRfLcdFreqList[i].ulAvailNum++;
                ulFlag = VOS_TRUE;
            }
            else
            {
                break;
            }
        }

        if (VOS_TRUE == ulFlag)
        {
            pstRfLcdIntrusionCtx->ucAvailFreqListNum++;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_GetRfCellInfoAddr
 ��������  : ��ȡg_astScellInfo�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : MTC_MODEM_MIPICLK_BITMAP_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��03��06��
    ��    ��   : Y00213812
    �޸�����   : RF&LCD���Ź����Ŀ����
*****************************************************************************/
MTC_MODEM_MIPICLK_BITMAP_STRU* MTC_GetRfCellInfoAddr(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(MTC_GetModemCtxAddr(enModemId)->stRfCellInfo);
}

/*****************************************************************************
 �� �� ��  : MTC_GetMipiClkBitMap
 ��������  : ��ȡg_usMipiClkBitMap����ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��03��06��
    ��    ��   : Y00213812
    �޸�����   : RF&LCD���Ź����Ŀ����
*****************************************************************************/
VOS_UINT16 MTC_GetMipiClkBitMap(VOS_VOID)
{
    return MTC_GetRfLcdIntrusionCtxAddr()->usMipiClkBitMap;
}

/*****************************************************************************
 �� �� ��  : MTC_InitRfCellInfo
 ��������  : ȫ�ֱ�����ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��03��06��
    ��    ��   : Y00213812
    �޸�����   : RF&LCD���Ź����Ŀ����
*****************************************************************************/
VOS_VOID MTC_InitRfCellInfo(MODEM_ID_ENUM_UINT16 enModemId)
{
    MTC_MODEM_MIPICLK_BITMAP_STRU      *pstRfCellInfo = VOS_NULL_PTR;

    pstRfCellInfo = MTC_GetRfCellInfoAddr(enModemId);

    pstRfCellInfo->enCsExistFlag     = PS_FALSE;
    pstRfCellInfo->enPsExistFlag     = PS_FALSE;
    pstRfCellInfo->usScellBitMap     = MTC_GetMipiClkBitMap();
    pstRfCellInfo->usHoppingBitMap   = MTC_GetMipiClkBitMap();
    pstRfCellInfo->usNcellBitMap     = MTC_GetMipiClkBitMap();
}

/*****************************************************************************
 �� �� ��  : MTC_InitRfLcdIntrusionCtx
 ��������  : ��ʼ��Rf&Lcd�������������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��03��04��
    ��    ��   : j00174725
    �޸�����   : RF&LCD INTRUSION��Ŀ
*****************************************************************************/
VOS_VOID MTC_InitRfLcdIntrusionCtx(VOS_VOID)
{
    MTC_RF_LCD_INTRUSION_CTX_STRU      *pstRfLcdIntrusionCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usModemIndex;

    pstRfLcdIntrusionCtx = MTC_GetRfLcdIntrusionCtxAddr();

    /* ��ʼ�������� */
    PS_MEM_SET(pstRfLcdIntrusionCtx, 0x0, sizeof(MTC_RF_LCD_INTRUSION_CTX_STRU));

    /* ��ʼ��Ϊ0xffff,Ϊ�����λ��׼�� */
    pstRfLcdIntrusionCtx->usMipiClkBitMap = 0xFFFF;

    /* ��ȡNV�� */
    MTC_ReadRfLcdCfgNv();

    /* ����LCD MIPICLK��Ч��������λͼ */
    if (pstRfLcdIntrusionCtx->ucAvailFreqListNum <= MTC_RF_LCD_MIPICLK_MAX_NUM)
    {
        ucIndex = 16 - pstRfLcdIntrusionCtx->ucAvailFreqListNum;
        pstRfLcdIntrusionCtx->usMipiClkBitMap >>= ucIndex;
    }

    /* ����^mipiclk�����ϱ����յ�MTA Pid */
    pstRfLcdIntrusionCtx->ulMipiClkReportModemId = I0_UEPS_PID_MTA;             /* ��ǰ����Ĭ�ϴ�Modem0�ϱ� */

    for (usModemIndex = 0; usModemIndex < MODEM_ID_BUTT; usModemIndex++)
    {
        /* ��ʼ��RF&LCDɸѡģ�������� */
        MTC_InitRfCellInfo(usModemIndex);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_GetRfLcdIntrusionCfg
 ��������  : ��ȡRF&LCD���Ź���Ƿ�ʹ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : MTC_CFG_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��08��13��
    ��    ��   : j00174725
    �޸�����   : V9R1 ���ſ�����Ŀ
*****************************************************************************/
MTC_CFG_ENUM_UINT8 MTC_GetRfLcdIntrusionCfg(VOS_VOID)
{
    MTC_RF_LCD_INTRUSION_CTX_STRU      *pstRfLcdIntrusionCtx = VOS_NULL_PTR;

    pstRfLcdIntrusionCtx = MTC_GetRfLcdIntrusionCtxAddr();

    if (0 != pstRfLcdIntrusionCtx->usEnableBitMap)
    {
        return MTC_CFG_ENABLE;
    }
    else
    {
        return MTC_CFG_DISABLE;
    }
}

/*****************************************************************************
 �� �� ��  : MTC_GetRseSupportCfg
 ��������  : RSE��������
 �������  : ��
 �������  : ��
 �� �� ֵ  : MTC_CFG_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��05��12��
    ��    ��   : j00174725
    �޸�����   : RSE��Ŀ
*****************************************************************************/
MTC_CFG_ENUM_UINT8 MTC_GetRseSupportCfg(VOS_VOID)
{
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    if (0 != (pstMtcIntrusionCtx->stIntrusionCfg.ucSolutionMask & MTC_RSE_CFG_BIT))
    {
        return MTC_CFG_ENABLE;
    }
    else
    {
        return MTC_CFG_DISABLE;
    }
}

/*****************************************************************************
 �� �� ��  : MTC_GetRseCfgValue
 ��������  : ���������л�ȡǰһ�����õ�RSEֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : PS_BOOL_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��05��12��
    ��    ��   : j00174725
    �޸�����   : RSE��Ŀ
*****************************************************************************/
PS_BOOL_ENUM_UINT8 MTC_GetRseCfgValue(VOS_VOID)
{
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    return pstMtcIntrusionCtx->enRseCfg;
}

/*lint -e958 �޸���: j00174725 for RSE 2014-06-16 begin */
/*****************************************************************************
 �� �� ��  : MTC_SetRseCfgValue
 ��������  : ����RSEֵ����������
 �������  : enValue
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��05��12��
    ��    ��   : j00174725
    �޸�����   : RSE��Ŀ
*****************************************************************************/
VOS_VOID MTC_SetRseCfgValue(PS_BOOL_ENUM_UINT8 enValue)
{
    MTC_INTRUSION_CTX_STRU             *pstMtcIntrusionCtx = VOS_NULL_PTR;

    pstMtcIntrusionCtx = MTC_GetIntrusionCtxAddr();

    pstMtcIntrusionCtx->enRseCfg = enValue;

    return;
}
/*lint +e958 �޸���: j00174725 for RSE 2014-06-16 end */


/*****************************************************************************
 �� �� ��  : MTC_SetCsSessionInfo
 ��������  : ����CS Session
 �������  : enModemId            -- Modem ID
             enSessionType        -- session type
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��04��
    ��    ��   : j00174725
    �޸�����   : DTS2015082406288
*****************************************************************************/
VOS_VOID MTC_SetCsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
)
{
    MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ulCsSessionInfo |= MTC_SET_BIT(enSessionType);
}

/*****************************************************************************
 �� �� ��  : MTC_SetPsSessionInfo
 ��������  : ����PS Session
 �������  : enModemId            -- Modem ID
             enSessionType        -- session type
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��24��
    ��    ��   : h00313353
    �޸�����   : DTS2015122211114
*****************************************************************************/
VOS_VOID MTC_SetPsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
)
{
    MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ulPsSessionInfo |= MTC_SET_BIT(enSessionType);
}

/*****************************************************************************
 �� �� ��  : MTC_ClearCsSessionInfo
 ��������  : ���CS Session
 �������  : enModemId            -- Modem ID
             enSessionType        -- session type
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��04��
    ��    ��   : j00174725
    �޸�����   : DTS2015082406288
*****************************************************************************/
VOS_VOID MTC_ClearCsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
)
{
    MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ulCsSessionInfo &= ~(MTC_SET_BIT(enSessionType));
}

/*****************************************************************************
 �� �� ��  : MTC_ClearPsSessionInfo
 ��������  : ���PS Session
 �������  : enModemId            -- Modem ID
             enSessionType        -- session type
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��24��
    ��    ��   : h00313353
    �޸�����   : DTS2015122211114
*****************************************************************************/
VOS_VOID MTC_ClearPsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_SESSION_TYPE_ENUM_UINT8         enSessionType
)
{
    MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ulPsSessionInfo &= ~(MTC_SET_BIT(enSessionType));
}

/*****************************************************************************
 �� �� ��  : MTC_IsCsSessionInfoExit
 ��������  : CS Session�Ƿ����
 �������  : enModemId            -- Modem ID
 �������  : ��
 �� �� ֵ  : PS_BOOL_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��04��
    ��    ��   : j00174725
    �޸�����   : DTS2015082406288
*****************************************************************************/
PS_BOOL_ENUM_UINT8 MTC_IsCsSessionInfoExit(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    VOS_UINT32                          ulCsSessionInfo;
    VOS_UINT32                          ulIndex;

    ulCsSessionInfo = MTC_GetCsSessionInfo(enModemId);

    for (ulIndex = MTC_SESSION_TYPE_CS_MO_NORMAL_CALL; ulIndex < MTC_SESSION_TYPE_CS_BUTT; ulIndex++)
    {
        if (MTC_SET_BIT(ulIndex) == (ulCsSessionInfo & MTC_SET_BIT(ulIndex)))
        {
            return PS_TRUE;
        }
    }

    return PS_FALSE;
}
/*****************************************************************************
 �� �� ��  : MTC_GetCsSessionInfo
 ��������  : ��ȡCS Session��¼ֵ
 �������  : enModemId            -- Modem ID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��04��
    ��    ��   : j00174725
    �޸�����   : DTS2015082406288
*****************************************************************************/
VOS_UINT32 MTC_GetCsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return  MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ulCsSessionInfo;
}

/*****************************************************************************
 �� �� ��  : MTC_GetPsSessionInfo
 ��������  : ��ȡPS Session��¼ֵ
 �������  : enModemId            -- Modem ID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��09��04��
    ��    ��   : j00174725
    �޸�����   : DTS2015082406288
*****************************************************************************/
VOS_UINT32 MTC_GetPsSessionInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return  MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ulPsSessionInfo;
}

/*****************************************************************************
 �� �� ��  : MTC_IsPsSessionInfoExit
 ��������  : PS Session�Ƿ����
 �������  : enModemId            -- Modem ID
 �������  : ��
 �� �� ֵ  : PS_BOOL_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��24��
    ��    ��   : h00313353
    �޸�����   : DTS2015122211114
*****************************************************************************/
PS_BOOL_ENUM_UINT8 MTC_IsPsSessionInfoExit(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    VOS_UINT32                          ulPsSessionInfo;
    VOS_UINT32                          ulIndex;

    ulPsSessionInfo = MTC_GetPsSessionInfo(enModemId);

    for (ulIndex = MTC_SESSION_TYPE_PS_CONVERSAT_CALL; ulIndex < MTC_SESSION_TYPE_BUTT; ulIndex++)
    {
        if (MTC_SET_BIT(ulIndex) == (ulPsSessionInfo & MTC_SET_BIT(ulIndex)))
        {
            return PS_TRUE;
        }
    }

    return PS_FALSE;
}


/* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, Begin */
/*****************************************************************************
 �� �� ��  : MTC_SetCsTypeInfo
 ��������  : ����CS����״̬
 �������  : enModemId            -- Modem ID
             ucCsType             -- CS����
             enCsSrvConnState     -- ����״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
VOS_VOID MTC_SetCsTypeInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_CS_TYPE_ENUM_UINT8              enCsType,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvConnState
)
{
    if (TAF_MTC_SRV_EXIST == enCsSrvConnState)
    {
        MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ucCsSrvConnInfo |= (VOS_UINT8)MTC_SET_BIT(enCsType);
    }
    else
    {
        MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ucCsSrvConnInfo &=  (~((VOS_UINT8)MTC_SET_BIT(enCsType)));
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_GetCsTypeInfo
 ��������  : ��ȡCS����״̬
 �������  : enModemId            -- Modem ID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
VOS_UINT8 MTC_GetCsTypeInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return (MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ucCsSrvConnInfo & MTC_CS_TYPE_ALL_VALUE);
}

/*****************************************************************************
 �� �� ��  : MTC_GetCsSrvState
 ��������  : �ж��Ƿ���CS���Ӵ���
 �������  : enModemId            -- Modem ID
 �������  : ��
 �� �� ֵ  : TAF_MTC_SRV_CONN_STATE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
TAF_MTC_SRV_CONN_STATE_ENUM_UINT8 MTC_GetCsSrvState(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucCsTypeInfo;

    ucCsTypeInfo    = MTC_GetCsTypeInfo(enModemId) & MTC_CS_TYPE_ALL_VALUE;

    for (ulIndex = MTC_CS_TYPE_GU; ulIndex < MTC_CS_TYPE_BUTT; ulIndex++)
    {
        if (MTC_SET_BIT(ulIndex) == (ucCsTypeInfo & MTC_SET_BIT(ulIndex)))
        {
            return TAF_MTC_SRV_EXIST;
        }
    }

    return TAF_MTC_SRV_NO_EXIST;
}

/*****************************************************************************
 �� �� ��  : MTC_SetPsTypeInfo
 ��������  : ����PS��������
 �������  : enModemId            -- Modem ID
             ucPsType             -- PS����
             enPsSrvConnState     -- ����״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : j00174725
    �޸�����   : DTS2015093005685
*****************************************************************************/
VOS_VOID MTC_SetPsTypeInfo(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_PS_TYPE_ENUM_UINT8              enPsType,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enPsSrvConnState
)
{
    if (TAF_MTC_SRV_EXIST == enPsSrvConnState)
    {
        MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ucPsSrvConnInfo |= (VOS_UINT8)MTC_SET_BIT(enPsType);
    }
    else
    {
        MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ucPsSrvConnInfo &=  (~((VOS_UINT8)MTC_SET_BIT(enPsType)));
    }

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_GetPsTypeInfo
 ��������  : ��ȡPS����״̬
 �������  : enModemId            -- Modem ID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : j00174725
    �޸�����   : DTS2015093005685
*****************************************************************************/
VOS_UINT8 MTC_GetPsTypeInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return (MTC_GetModemCtxAddr(enModemId)->stConnStateInfo.ucPsSrvConnInfo & MTC_PS_TYPE_ALL_VALUE);
}

/*****************************************************************************
 �� �� ��  : MTC_GetPsSrvState
 ��������  : �ж��Ƿ���PS���Ӵ���
 �������  : enModemId            -- Modem ID
 �������  : ��
 �� �� ֵ  : TAF_MTC_SRV_CONN_STATE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��10��
    ��    ��   : j00174725
    �޸�����   : DTS2015093005685
*****************************************************************************/
TAF_MTC_SRV_CONN_STATE_ENUM_UINT8 MTC_GetPsSrvState(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT8                           ucPsTypeInfo;

    ucPsTypeInfo    = MTC_GetPsTypeInfo(enModemId);

    for (ulIndex = MTC_PS_TYPE_GU; ulIndex < MTC_PS_TYPE_BUTT; ulIndex++)
    {
        if (MTC_SET_BIT(ulIndex) == (ucPsTypeInfo & MTC_SET_BIT(ulIndex)))
        {
            return TAF_MTC_SRV_EXIST;
        }
    }

    return TAF_MTC_SRV_NO_EXIST;
}

/*****************************************************************************
 �� �� ��  : MTC_SetUsimStateInfo
 ��������  : ���ÿ�״̬
 �������  : enModemId            -- Modem ID
             enUsimState          -- Usim��״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������

  2.��    ��   : 2015��10��21��
    ��    ��   : h00313353
    �޸�����   : Iteration 19 TAS
*****************************************************************************/
VOS_VOID MTC_SetUsimStateInfo(
    MODEM_ID_ENUM_UINT16                    enModemId,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enUsimState
)
{
    MTC_GetModemCtxAddr(enModemId)->enUsimState = enUsimState;

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_SetCsimStateInfo
 ��������  : ���ÿ�״̬
 �������  : enModemId            -- Modem ID
             enCsimState          -- Csim��״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : h00313353
    �޸�����   : Iteration 19 TAS
*****************************************************************************/
VOS_VOID MTC_SetCsimStateInfo(
    MODEM_ID_ENUM_UINT16                    enModemId,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enCsimState
)
{
    MTC_GetModemCtxAddr(enModemId)->enCsimState = enCsimState;

    return;
}
/*****************************************************************************
 �� �� ��  : MTC_GetUsimStateInfo
 ��������  : ��ȡUsim��״̬
 �������  : enModemId            -- Modem ID
 �������  : ��
 �� �� ֵ  : TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������

  2.��    ��   : 2015��10��21��
    ��    ��   : h00313353
    �޸�����   : Iteration 19 TAS
*****************************************************************************/
TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16 MTC_GetUsimStateInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return  MTC_GetModemCtxAddr(enModemId)->enUsimState;
}

/*****************************************************************************
 �� �� ��  : MTC_GetCsimStateInfo
 ��������  : ��ȡCsim��״̬
 �������  : enModemId            -- Modem ID
 �������  : ��
 �� �� ֵ  : TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : h00313353
    �޸�����   : Iteration 19 TAS
*****************************************************************************/
TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16 MTC_GetCsimStateInfo(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return MTC_GetModemCtxAddr(enModemId)->enCsimState;
}

/*****************************************************************************
 �� �� ��  : MTC_GetRatCfgByModemId
 ��������  : ����ModemId,��ȡ��ǰModem�Ľ�������
 �������  : enModemId            -- Modem ID
 �������  : ��
 �� �� ֵ  : MTC_RCM_MODEM_RAT_CFG_ENUM_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : h00313353
    �޸�����   : Iteration 19 TAS
*****************************************************************************/
MTC_MODEM_RAT_CONFIG_STRU* MTC_GetRatCfgByModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(MTC_GetModemCtxAddr(enModemId)->stRatCfg);
}

/*****************************************************************************
 �� �� ��  : MTC_SetRatCfgByModemId
 ��������  : ����ModemId,���õ�ǰModem�Ľ�����ʽ
 �������  : enModemId                          -- Modem ID
             MTC_RCM_MODEM_RAT_CFG_ENUM_UINT16  -- ������ʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��21��
    ��    ��   : h00313353
    �޸�����   : Iteration 19 TAS
*****************************************************************************/
VOS_VOID MTC_SetRatCfgByModemId(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_MODEM_RAT_CONFIG_STRU          *pstRatCfg
)
{
    PS_MEM_CPY(MTC_GetRatCfgByModemId(enModemId), pstRatCfg, sizeof(MTC_MODEM_RAT_CONFIG_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_GetOutSideModemCtxAddr
 ��������  : ��ȡ����MODEM��Ϣ�����ĵ�ַ
 �������  : �ڲ��ӿڣ�enModemId �ɵ����߱�֤modemId����Ч��
 �������  : ��
 �� �� ֵ  : MTC_OUTSIDE_MODEM_INFO_STRU* MODEM��Ϣ�����ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��26��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
MTC_OUTSIDE_MODEM_INFO_STRU* MTC_GetOutSideModemCtxAddr(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId
)
{
    return &(MTC_GetCtxAddr()->astOutSideModemInfo[enModemId]);
}


/*****************************************************************************
 �� �� ��  : MTC_SetOutSideCsConnStateInfo
 ��������  : ��������modem CS����״̬
 �������  : enModemId            -- ����Modem ID
             enConnSt             -- ����״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
VOS_VOID MTC_SetOutSideCsConnStateInfo(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enConnSt
)
{
    MTC_GetOutSideModemCtxAddr(enModemId)->stConnStateInfo.enCsSrvConnState = enConnSt;
}

/*****************************************************************************
 �� �� ��  : MTC_GetOutSideCsConnStateInfo
 ��������  : ��ȡCS����״̬
 �������  : enModemId            -- ����Modem ID
 �������  : ��
 �� �� ֵ  : TAF_MTC_SRV_CONN_STATE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
TAF_MTC_SRV_CONN_STATE_ENUM_UINT8 MTC_GetOutSideCsConnStateInfo(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId
)
{
    return MTC_GetOutSideModemCtxAddr(enModemId)->stConnStateInfo.enCsSrvConnState;
}

/*****************************************************************************
 �� �� ��  : MTC_SetOutSidePsConnStateInfo
 ��������  : ��������modem PS����״̬
 �������  : enModemId            -- ����Modem ID
             enConnSt             -- ����״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
VOS_VOID MTC_SetOutSidePsConnStateInfo(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId,
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enConnSt
)
{
    MTC_GetOutSideModemCtxAddr(enModemId)->stConnStateInfo.enPsSrvConnState = enConnSt;
}

/*****************************************************************************
 �� �� ��  : MTC_GetOutSidePsConnStateInfo
 ��������  : ��ȡCS����״̬
 �������  : enModemId            -- ����Modem ID
 �������  : ��
 �� �� ֵ  : TAF_MTC_SRV_CONN_STATE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
TAF_MTC_SRV_CONN_STATE_ENUM_UINT8 MTC_GetOutSidePsConnStateInfo(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId
)
{
    return MTC_GetOutSideModemCtxAddr(enModemId)->stConnStateInfo.enPsSrvConnState;
}

/*****************************************************************************
 �� �� ��  : MTC_SetOutSideModemPowerState
 ��������  : ��������modem ���ػ�״̬
 �������  : enModemId            -- ����Modem ID
             enPowerStatus        -- ���ػ�״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
VOS_VOID MTC_SetOutSideModemPowerState(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId,
    MTC_MODEM_POWER_STATE_ENUM_UINT8    enPowerStatus
)
{
    MTC_GetOutSideModemCtxAddr(enModemId)->enPowerState = enPowerStatus;
}

/*****************************************************************************
 �� �� ��  : MTC_GetOutSideModemPowerState
 ��������  : ��ȡ����modem���ػ�״̬
 �������  : enModemId            -- ����Modem ID
 �������  : ��
 �� �� ֵ  : MTC_MODEM_POWER_STATE_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
MTC_MODEM_POWER_STATE_ENUM_UINT8 MTC_GetOutSideModemPowerState(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId
)
{
    return MTC_GetOutSideModemCtxAddr(enModemId)->enPowerState;
}

/*****************************************************************************
 �� �� ��  : MTC_SetOutSideModemUsimmState
 ��������  : ��������modem ��״̬
 �������  : enModemId            -- ����Modem ID
             enUsimmStatus        -- ��״̬
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
VOS_VOID MTC_SetOutSideModemUsimmState(
    MTC_OUTSIDE_MODEM_ENUM_UINT16           enModemId,
    TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16   enUsimmStatus
)
{
    MTC_GetOutSideModemCtxAddr(enModemId)->enUsimmState = enUsimmStatus;
}

/*****************************************************************************
 �� �� ��  : MTC_GetOutSideModemUsimmState
 ��������  : ��ȡ����modem��״̬
 �������  : enModemId            -- ����Modem ID
 �������  : ��
 �� �� ֵ  : TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��06��16��
    ��    ��   : j00174725
    �޸�����   : K3V3 ��ģ����������
*****************************************************************************/
TAF_MTC_USIMM_CARD_SERVIC_ENUM_UINT16 MTC_GetOutSideModemUsimmState(
    MTC_OUTSIDE_MODEM_ENUM_UINT16       enModemId
)
{
    return MTC_GetOutSideModemCtxAddr(enModemId)->enUsimmState;
}

/* Add by j00174725 for K3V3 ��ģ����������, 2014-06-16, End */

/*****************************************************************************
 �� �� ��  : MTC_GetModemGsmCellInfoEx
 ��������  : ��ȡModem GSMС����չ��Ϣ
 �������  : MODEM_ID_ENUM_UINT16 enModemId
 �������  : ��
 �� �� ֵ  : MTC_GSM_CELLINFO_EX_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��17��
    ��    ��   : l00198894
    �޸�����   : ��������
*****************************************************************************/
MTC_GSM_CELLINFO_EX_STRU* MTC_GetModemGsmCellInfoEx(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return &(MTC_GetCtxAddr()->astModemInfo[enModemId].stGsmCellInfoEx);
}

/*****************************************************************************
 �� �� ��  : MTC_GetCurrentTcStatus
 ��������  : ��ȡTAS���ز���״̬
 �������  : �ڲ��ӿڣ�enModemId �ɵ����߱�֤modemId����Ч��
 �������  : ��
 �� �� ֵ  : MTC_NAS_TC_STATUS_ENUM_UINT16* ���ز���״̬��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��15��
    ��    ��   : wx270776
    �޸�����   : ��������
  2.��    ��   : 2015��7��20��
    ��    ��   : zwx247453
    �޸�����   : 3 modem TAS
*****************************************************************************/
MTC_RCM_TC_STATUS_ENUM_UINT16 MTC_GetCurrentTcStatus(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    return MTC_GetCtxAddr()->astModemInfo[enModemId].enTcStatus;
}

/*****************************************************************************
 �� �� ��  : MTC_SetCurrentTcStatus
 ��������  : ����TAS���ز���״̬
 �������  : MTC_NAS_TC_STATUS_ENUM_UINT16       enTcStatus
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��15��
    ��    ��   : wx270776
    �޸�����   : ��������
  2.��    ��   : 2015��7��20��
    ��    ��   : zwx247453
    �޸�����   : 3 modem TAS
*****************************************************************************/
VOS_VOID MTC_SetCurrentTcStatus(
    MODEM_ID_ENUM_UINT16                enModemId,
    MTC_RCM_TC_STATUS_ENUM_UINT16       enTcStatus
)
{
    MTC_GetCtxAddr()->astModemInfo[enModemId].enTcStatus = enTcStatus;

    return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

