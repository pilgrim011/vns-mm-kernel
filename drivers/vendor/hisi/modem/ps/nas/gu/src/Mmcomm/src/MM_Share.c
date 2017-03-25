/*******************************************************************************
  Copyright   : 2005-2007, Huawei Tech. Co., Ltd.
  File name   : MM_Share.c
  Description :
  Function List:
              Mm_AtTest
              Mm_AtTest_GetGmmRegState
              Mm_AtTest_GetGmmState
              Mm_AtTest_GetGprsState
              Mm_AtTest_GetMmRegState
              Mm_AtTest_GetMmState
              Mm_StartRelTimer
              Mm_StopRelTimer
  History     :
      1.��־��   2004.03.10 �¹�����
      2.��    ��   : 2008��5��7��
        ��    ��   : luojian id:107747
        �޸�����  : �������ⵥ��AT2D03294,����MM��������
      3.��    ��   : 2008��09��03��
        ��    ��   : o00132663
        �޸�����  : ���ⵥ�ţ�AT2D05469,��չ^CMM����.
      4.��    ��   : 2009��05��04��
        ��    ��   : l00130025
        �޸�����   : ���ⵥ�ţ�AT2D11646,����������T3212��ֵΪ255ʱ,MM����18Сʱ��ʱ��,���µ��帴λ.
*******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "MM_Share_inc.h"
#include "NVIM_Interface.h"

#include "MnComm.h"
#include "NasMmcCtx.h"
/* Added by f62575 for V9R1 STK����, 2013-6-26, begin */
#include "TafStdlib.h"
/* Added by f62575 for V9R1 STK����, 2013-6-26, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 �޸���:luojian 107747;������:sunshaohua65952;ԭ��:LOG���������Ҫ*/
#define    THIS_FILE_ID        PS_FILE_ID_MM_SHARE_C
/*lint +e767 �޸���:luojian 107747;������:sunshaohua*/

extern VOS_VOID Mm_ComInit (VOS_VOID);
extern VOS_VOID Gmm_TaskInit(VOS_VOID);
extern VOS_VOID MMC_GolbalVarInit(VOS_VOID);


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
MM_SUB_LAYER_SHARE_STRU                 g_MmSubLyrShare = {{0}};
VOS_UINT32                              g_ulGmmDelaySuspendRsp = 0;
/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
 �� �� ��  : Mm_AtTest_GetGprsState
 ��������  : ��ȡGPRS�ƶ��Թ���״̬
 �������  : NAS_TEST_AT_RSLT_STRU *pstAtCmdRslt
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��5��7��
    ��    ��   : luojian id:107747
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 Mm_AtTest_GetGprsState(MM_TEST_AT_RSLT_STRU *pstAtCmdRslt)
{
    pstAtCmdRslt->ulRsltNum = 2;
    /* 0--A/Gb mode ,1--IU mode */
    pstAtCmdRslt->aulRslt[0] = NAS_MML_GetCurrNetRatType();
    /*
    A/Gb mode: 0--IDLE     1--STANDBY  2--READY
    IU mode  : 0--DETACHED 1--IDLE     2--CONNECTED
    */
    pstAtCmdRslt->aulRslt[1] = Gmm_GetGprsState();
    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : Mm_AtTest_GetGmmState
 ��������  :
 �������  : NAS_TEST_AT_RSLT_STRU *pstAtCmdRslt
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��5��7��
    ��    ��   : luojian id:107747
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 Mm_AtTest_GetGmmState(MM_TEST_AT_RSLT_STRU *pstAtCmdRslt)
{
    pstAtCmdRslt->ulRsltNum = 1;
    pstAtCmdRslt->aulRslt[0] = Gmm_GetState();
    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : Mm_AtTest_GetMmState
 ��������  :
 �������  : NAS_TEST_AT_RSLT_STRU *pstAtCmdRslt
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��5��7��
    ��    ��   : luojian id:107747
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 Mm_AtTest_GetMmState(MM_TEST_AT_RSLT_STRU *pstAtCmdRslt)
{
    pstAtCmdRslt->ulRsltNum = 1;
    pstAtCmdRslt->aulRslt[0] = Mm_GetState();
    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : Mm_AtTest_GetMmRegState
 ��������  :
 �������  : NAS_TEST_AT_RSLT_STRU *pstAtCmdRslt
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��5��7��
    ��    ��   : luojian id:107747
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 Mm_AtTest_GetMmRegState(MM_TEST_AT_RSLT_STRU *pstAtCmdRslt)
{
    pstAtCmdRslt->ulRsltNum = 1;
    pstAtCmdRslt->aulRslt[0] = NAS_MML_GetCsRegStatus();
    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : Mm_AtTest_GetGmmRegState
 ��������  :
 �������  : NAS_TEST_AT_RSLT_STRU *pstAtCmdRslt
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��5��7��
    ��    ��   : luojian id:107747
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 Mm_AtTest_GetGmmRegState(MM_TEST_AT_RSLT_STRU *pstAtCmdRslt)
{
    pstAtCmdRslt->ulRsltNum = 1;
    pstAtCmdRslt->aulRslt[0] = NAS_MML_GetPsRegStatus();
    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : Mm_AtTest_SetPlmnSearchMode
 ��������  : ��������NV���������ģʽ
 �������  : TAF_UINT32 ulPlmnSearchMode
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��9��2��
    ��    ��   : ouyangfei id:00132663
    �޸�����   : �����ɺ���,���ⵥ�ţ�AT2D05469,��չ^CMM����.
  2.��    ��   : 2013��05��20��
    ��    ��   : m00217266
    �޸�����   : nv����
*****************************************************************************/
VOS_UINT32 Mm_AtTest_SetPlmnSearchMode(VOS_UINT32 ulPlmnSearchMode)
{
    NAS_NVIM_SELPLMN_MODE_STRU      stPlmnSelMode;

    if ( (ulPlmnSearchMode != 0) && (ulPlmnSearchMode != 1) )
    {
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_AtTest_SetPlmnSearchMode():WARNING: AT^CMM PARA Error!");
        return VOS_ERR;
    }

    if ( ulPlmnSearchMode == 0 )  /* �Զ�����ģʽ */
    {
        stPlmnSelMode.usSelPlmnMode = NAS_MMC_PLMN_SELECTION_MODE_AUTO;
        if (NV_OK != NV_Write (en_NV_Item_SelPlmn_Mode,
                               &stPlmnSelMode,
                               sizeof(NAS_NVIM_SELPLMN_MODE_STRU)))
        {
            PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_AtTest_SetPlmnSearchMode():WARNING: Write en_NV_Item_SelPlmn_Mode Error");
            return VOS_ERR;
        }
    }
    else  /* �ֶ�����ģʽ */
    {
        stPlmnSelMode.usSelPlmnMode = NAS_MMC_PLMN_SELECTION_MODE_MANUAL;
        if (NV_OK != NV_Write (en_NV_Item_SelPlmn_Mode,
                               &stPlmnSelMode,
                               sizeof(NAS_NVIM_SELPLMN_MODE_STRU)))
        {
            PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_AtTest_SetPlmnSearchMode():WARNING: Write en_NV_Item_SelPlmn_Mode Error");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : Mm_AtTest_SetRatMode
 ��������  : ��������NV����ý���ģʽ
 �������  : TAF_UINT32 ulRatMode
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��9��2��
    ��    ��   : ouyangfei id:00132663
    �޸�����   : �����ɺ���,���ⵥ�ţ�AT2D05469,��չ^CMM����.

*****************************************************************************/
VOS_UINT32 Mm_AtTest_SetRatMode(VOS_UINT32 ulRatMode)
{
    NVIM_EQUIVALENT_PLMN_LIST_STRU  stEquivPlmn;
    VOS_UINT32  ulLen;

    if ( (ulRatMode != 0) && (ulRatMode != 1) )
    {
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_AtTest_SetRatMode():WARNING: AT^CMM PARA Error!");
        return VOS_ERR;
    }

    ulLen = sizeof(NVIM_EQUIVALENT_PLMN_LIST_STRU);

    PS_MEM_SET(&stEquivPlmn, 0x00, ulLen );

    /* ��ȡ equivalent PLMN list                 */
    if(NV_OK != NV_Read (en_NV_Item_EquivalentPlmn, &stEquivPlmn, ulLen))
    {
        PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_AtTest_SetRatMode():WARNING: Read en_NV_Item_EquivalentPlmn Error");
        return VOS_ERR;
    }
    else
    {   /* ���ý���ģʽ                 */
        if ( ulRatMode == 0 )  /* GSM */
        {
            stEquivPlmn.struPlmnList[NVIM_MAX_EPLMN_NUM - 1].ucMnc[NVIM_MAX_MNC_SIZE - 1] = NAS_MML_NET_RAT_TYPE_GSM;
        }
        else /* WCDMA */
        {
            stEquivPlmn.struPlmnList[NVIM_MAX_EPLMN_NUM - 1].ucMnc[NVIM_MAX_MNC_SIZE - 1] = NAS_MML_NET_RAT_TYPE_WCDMA;
        }

        /* �洢 equivalent PLMN list                 */
        if (NV_OK != NV_Write(en_NV_Item_EquivalentPlmn, &stEquivPlmn, ulLen))
        {
            PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "Mm_AtTest_SetRatMode():WARNING: Write en_NV_Item_EquivalentPlmn Error");
            return VOS_ERR;
        }
    }

    return VOS_OK;
}

#if ( VOS_WIN32 == VOS_OS_VER )
/*****************************************************************************
 �� �� ��  : Mm_AtTest_SetAdditionalUpdateRsltIe
 ��������  : ����Additional Update Rslt Ie������PC����
 �������  : TAF_UINT32 ulAdditionalUpdateRsltIe
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��19��
    ��    ��   : s46746
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 Mm_AtTest_SetAdditionalUpdateRsltIe(
    VOS_UINT32 AdditionalUpdateRsltIe
)
{
    if (0x0 == AdditionalUpdateRsltIe)
    {
        NAS_MML_SetAdditionUpdateRslt(NAS_MML_ADDITION_UPDATE_RSLT_NO_ADDITION_INFO);
    }
    else if (0x1 == AdditionalUpdateRsltIe)
    {
        NAS_MML_SetAdditionUpdateRslt(NAS_MML_ADDITION_UPDATE_RSLT_CSFB_NOT_PREFERRED);
    }
    else
    {
        NAS_MML_SetAdditionUpdateRslt(NAS_MML_ADDITION_UPDATE_RSLT_SMS_ONLY);
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : Mm_AtTest_SetLteUeUsageSetting
 ��������  : ����LTE�������������ģ�����PC����
 �������  : TAF_UINT32 ulLteUeUsageSetting
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��19��
    ��    ��   : s46746
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 Mm_AtTest_SetLteUeUsageSetting(
    VOS_UINT32 ulLteUeUsageSetting
)
{
    if (0x0 == ulLteUeUsageSetting)
    {
        NAS_MML_SetLteUeUsageSetting(NAS_MML_LTE_UE_USAGE_SETTING_VOICE_CENTRIC);
    }
    else
    {
        NAS_MML_SetLteUeUsageSetting(NAS_MML_LTE_UE_USAGE_SETTING_DATA_CENTRIC);
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : Mm_AtTest_SetGmmDelaySuspendRsp
 ��������  : ����GMM�ӳٸ�MMC�ظ�SUSPEND RSP������PC����
 �������  : TAF_UINT32 ulGmmDelaySuspendRspFlg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��11��23��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 Mm_AtTest_SetGmmDelaySuspendRsp(
    VOS_UINT32 ulGmmDelaySuspendRspFlg
)
{
    if (0x0 == ulGmmDelaySuspendRspFlg)
    {
        g_ulGmmDelaySuspendRsp = 0;
    }
    else
    {
        g_ulGmmDelaySuspendRsp = 1;
    }

    return VOS_OK;
}

/* Modified by z00234330 for �����ϱ�AT�������������C��, 2013-4-16, begin */
/*****************************************************************************
 �� �� ��  : Mm_AtTest_SetLteUeUsageSetting
 ��������  : ����LTE�������������ģ�����PC����
 �������  : TAF_UINT32 ulLteUeUsageSetting
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��06��19��
    ��    ��   : s46746
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 Mm_AtTest_SetCsfbHighPrioFlg(
    VOS_UINT8                       ucFlg
)
{
    if ( VOS_TRUE == ucFlg )
    {
        NAS_MML_SetRelCauseCsfbHighPrioFlg(VOS_TRUE);
    }
    else
    {
        NAS_MML_SetRelCauseCsfbHighPrioFlg(VOS_FALSE);
    }
    return VOS_OK;
}

/* Modified by z00234330 for �����ϱ�AT�������������C��, 2013-4-16, end */

#endif

/*****************************************************************************
 �� �� ��  : Mm_AtTest_SetOriginalRejectCause
 ��������  : ����������·���ԭʼ�ܾ�ԭ��ֵ������PC����
 �������  : VOS_UINT8 ucOriginalUeCause
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��17��
    ��    ��   : g00322017
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 Mm_AtTest_SetOriginalRejectCause(
    VOS_UINT32                          ulOriginalUeCause
)
{
    VOS_UINT8                           ucOriginalUeCause;
    ucOriginalUeCause = (VOS_UINT8)ulOriginalUeCause;
    NAS_MML_SetOriginalRejectCause(ucOriginalUeCause);
    return VOS_OK;
}

/* Modified by z00234330 for C50���ⵥͬ����V9, 2013-4-16, begin */
/*****************************************************************************
 �� �� ��  : Mm_AtTest_ClearUserPlmnId
 ��������  : ����û����õ�PLMN ID������PC����
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��07��20��
    ��    ��   : z00234330
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 Mm_AtTest_ClearUserPlmnId( VOS_VOID )
{
    NAS_MML_PLMN_WITH_RAT_STRU         stUserPlmn;

    stUserPlmn.stPlmnId.ulMcc = NAS_MML_INVALID_MCC;
    stUserPlmn.stPlmnId.ulMnc = NAS_MML_INVALID_MNC;
    NAS_MMC_SetUserSpecPlmnId(&stUserPlmn);

    return VOS_OK;
}

/* Modified by z00234330 for C50���ⵥͬ����V9, 2013-4-16, end */

/*****************************************************************************
 �� �� ��  : Mm_AtTest
 ��������  :
 �������  : NAS_TEST_AT_CMD_STRU *pstAtCmd
             NAS_TEST_AT_RSLT_STRU *pstAtCmdRslt
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��5��7��
    ��    ��   : luojian id:107747
    �޸�����   : �����ɺ���
  2.��    ��   : 2008��09��03��
    ��    ��   : o00132663
    �޸�����  : ���ⵥ�ţ�AT2D05469,��չ^CMM����.
  3.��    ��   : 2012��06��19��
    ��    ��   : s46746
    �޸�����   : For CS/PS mode 1��PC��׮����
  4.��    ��   : 2013��7��20��
    ��    ��   : z00234330
    �޸�����   : �������USER PLMN��AT����
*****************************************************************************/
VOS_UINT32 Mm_AtTest(VOS_VOID* pstAtCmd,VOS_VOID* pstAtCmdRslt)
{
    VOS_UINT32 ulRst;
    ulRst = VOS_OK;
    switch(((MM_TEST_AT_CMD_STRU*)pstAtCmd)->ucCmd)
    {
        case MM_TEST_AT_CMD_MM_STATE:
            ulRst = Mm_AtTest_GetMmState((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt);
            break;
        case MM_TEST_AT_CMD_GMM_STATE:
            ulRst = Mm_AtTest_GetGmmState((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt);
            break;
        case MM_TEST_AT_CMD_GPRS_STATE:
            ulRst = Mm_AtTest_GetGprsState((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt);
            break;
        case MM_TEST_AT_CMD_MM_REG_STATE:
            ulRst = Mm_AtTest_GetMmRegState((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt);
            break;
        case MM_TEST_AT_CMD_GMM_REG_STATE:
            ulRst = Mm_AtTest_GetGmmRegState((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt);
            break;
        case MM_TEST_AT_CMD_PLMN_SEARCH_MODE:
            ulRst = Mm_AtTest_SetPlmnSearchMode(((MM_TEST_AT_CMD_STRU*)pstAtCmd)->aulPara[0]);
            ((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt)->ulRsltNum = 0;
            break;
        case MM_TEST_AT_CMD_SET_RAT_MODE:
            ulRst = Mm_AtTest_SetRatMode(((MM_TEST_AT_CMD_STRU*)pstAtCmd)->aulPara[0]);
            ((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt)->ulRsltNum = 0;
            break;

#if ( VOS_WIN32 == VOS_OS_VER )
        case MM_TEST_AT_CMD_SET_ADDITIONAL_UPDATE_RESULT_IE:
            ulRst = Mm_AtTest_SetAdditionalUpdateRsltIe(((MM_TEST_AT_CMD_STRU*)pstAtCmd)->aulPara[0]);
            ((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt)->ulRsltNum = 0;
            break;

        case MM_TEST_AT_CMD_SET_LTE_UE_USAGE_SETTING:
            ulRst = Mm_AtTest_SetLteUeUsageSetting(((MM_TEST_AT_CMD_STRU*)pstAtCmd)->aulPara[0]);
            ((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt)->ulRsltNum = 0;
            break;

        case MM_TEST_AT_CMD_SET_GMM_DEALY_SUSPENDRSP:
            ulRst = Mm_AtTest_SetGmmDelaySuspendRsp(((MM_TEST_AT_CMD_STRU*)pstAtCmd)->aulPara[0]);
            ((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt)->ulRsltNum = 0;
            break;

/* Modified by z00234330 for �����ϱ�AT�������������C��, 2013-4-16, begin */
        case MM_TEST_AT_CMD_SET_CSFB_HIGH_PRIO_FLG:
            ulRst = Mm_AtTest_SetCsfbHighPrioFlg(((MM_TEST_AT_CMD_STRU*)pstAtCmd)->aulPara[0]);
            ((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt)->ulRsltNum = 0;
            break;
/* Modified by z00234330 for �����ϱ�AT�������������C��, 2013-4-16, end */
/* Modified by z00234330 for C50���ⵥͬ����V9, 2013-4-16, begin */
        case MM_TEST_AT_CMD_CLEAR_USER_PLMN_:
            ulRst = Mm_AtTest_ClearUserPlmnId();
            ((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt)->ulRsltNum = 0;
            break;
/* Modified by z00234330 for C50���ⵥͬ����V9, 2013-4-16, end */

#endif
        case MM_TEST_AT_CMD_SET_ORIGINAL_REJECT_CAUSE:
             ulRst = Mm_AtTest_SetOriginalRejectCause(((MM_TEST_AT_CMD_STRU*)pstAtCmd)->aulPara[0]);
            ((MM_TEST_AT_RSLT_STRU*)pstAtCmdRslt)->ulRsltNum = 0;
            break;
        default:
            ulRst = VOS_ERR;
            break;
    }
    return ulRst;
}

 /*****************************************************************************
  Prototype      : MM_HexAlpha2AsciiString
  Description    : ���16������ת������
  Input          : nptr --- �ַ���
  Output         :
  Return Value   : AT_SUCCESS --- �ɹ�
                   AT_FAILURE --- ʧ��
  Calls          : ---
  Called By      : ---

  History        : ---
   1.Date        : 2005-04-19
     Author      : ---
     Modification: Created function
   2.��    �� : 2007-03-27
     ��    �� : h59254
     �޸����� : ���ⵥ��:A32D09820(PC-Lint�޸�)
 *****************************************************************************/
 VOS_UINT32 MM_HexAlpha2AsciiString(VOS_UINT32 ulDestLength,VOS_UINT8 *pucDst,VOS_UINT8 *pucSrc,VOS_UINT16 usSrcLen)
 {
     VOS_UINT16 usLen = 0;
     VOS_UINT16 usChkLen = 0;
     VOS_UINT8 *pWrite = pucDst;
     VOS_UINT8 *pRead = pucSrc;
     VOS_UINT8  ucHigh = 0;
     VOS_UINT8  ucLow = 0;

     if((2 * usSrcLen)>= ulDestLength)
     {
         PS_NAS_LOG(WUEPS_PID_MMC, VOS_NULL, PS_LOG_LEVEL_WARNING, "MM_HexAlpha2AsciiString too long");
         return 0;
     }
     /*lint -e961*/
     if(0 != usSrcLen)
     {
         /* ɨ�������ִ� */
         while( usChkLen++ < usSrcLen )
         {
             ucHigh = 0x0F & (*pRead >> 4);
             ucLow = 0x0F & *pRead;

             usLen += 2;    /* ��¼���� */

             if(0x09 >= ucHigh)   /* 0-9 */
             {
                 *pWrite++ = ucHigh + 0x30;
             }
             else if(0x0A <= ucHigh)    /* A-F */
             {
                 *pWrite++ = ucHigh + 0x37;
             }
             else
             {

             }

             if(0x09 >= ucLow)   /* 0-9 */
             {
                 *pWrite++ = ucLow + 0x30;
             }
             else if(0x0A <= ucLow)    /* A-F */
             {
                 *pWrite++ = ucLow + 0x37;
             }
             else
             {

             }

             /* ��һ���ַ� */
             pRead++;
         }

     }
     /*lint +e961*/
     return usLen;
 }

/* Deleted by f62575 for V9R1 STK����, 2013-6-26, begin */
/* Deleted Mm_TranslateNtwkName2Str */
/* Deleted by f62575 for V9R1 STK����, 2013-6-26, end */


/*****************************************************************************
 �� �� ��  : MMC_ComGetRatType
 ��������  : ��ȡ��ǰ�Ľ���ģʽ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8 *pucRatType
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2010��5��6��
    ��    ��   : o00132663
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID MMC_ComGetRatType(VOS_UINT8 *pucRatType)
{
    *pucRatType = NAS_MML_GetCurrNetRatType();
    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MM_GetMncLenFromBCCHMnc
 ��������  : ���� BCCH��Mncȷ��Sim���ж�ӦPlmn��Mnc�ĳ��� ��������list�����ϱ�ʱ����
             ���ú�����Ҫ��֤,ulBcchMnc��Ӧ���� ��pstDestPlmnInfo��Ӧ��������ͬ��
 �������  : ��
 �������  : VOS_UINT8
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��2��27��
    ��    ��   : l00130025
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8  NAS_MM_GetMncLenFromBCCHMnc(
    VOS_UINT32                          ulBcchMnc
)
{
    VOS_UINT8                           ucBcchMnc3;
    VOS_UINT8                           ucMncLen;

    ucBcchMnc3 = (VOS_UINT8)((ulBcchMnc & 0x00ff0000) >> 16);

    if (0x0F == ucBcchMnc3)
    {
        ucMncLen = 2;
    }
    else
    {
       ucMncLen = 3;
    }

    return ucMncLen;
}


/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


