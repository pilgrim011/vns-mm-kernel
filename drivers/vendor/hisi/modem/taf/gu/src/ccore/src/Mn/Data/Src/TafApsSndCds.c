/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafApsSndCds.c
  �� �� ��   : ����
  ��    ��   : y00213812
  ��������   : 2014��09��18��
  ����޸�   :
  ��������   : TAF APSģ�鷢����Ϣ��CDS�ĺ���ʵ���ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��09��18��
    ��    ��   : y00213812
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "PsCommonDef.h"
#include "PsTypeDef.h"
#include "TafLog.h"
#include "Taf_Aps.h"
#include "MnApsComm.h"
#include "ApsCdsInterface.h"
#include "TafApsComFunc.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsCtx.h"
#include "ehsm_aps_pif.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SND_CDS_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 �� �� ��  : TAF_APS_SndCdsSndBuffDataInd
 ��������  : ����ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��18��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndCdsSndBuffDataInd(
    VOS_UINT8                           ucRabId
)
{
    APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU *pstSndBuffData = VOS_NULL_PTR;

    pstSndBuffData = (APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU));

    if (VOS_NULL_PTR == pstSndBuffData)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndCdsSndBuffDataInd: Memory alloc failed");
        return;
    }

    pstSndBuffData->ulReceiverPid       = UEPS_PID_CDS;
    pstSndBuffData->enMsgId             = ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND;
    pstSndBuffData->usOpId              = 0;
    pstSndBuffData->ucRabId             = ucRabId;

    PS_SEND_MSG(WUEPS_PID_TAF, pstSndBuffData);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_SndCdsFreeBuffDataInd
 ��������  : ����ID_APS_CDS_CDATA_FREE_BUFF_DATA_IND��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��18��
    ��    ��   : y00218312
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndCdsFreeBuffDataInd(
    VOS_UINT8                           ucRabId
)
{
    APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU *pstFreeBuffData = VOS_NULL_PTR;

    pstFreeBuffData = (APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU));

    if (VOS_NULL_PTR == pstFreeBuffData)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndCdsFreeBuffDataInd: Memory alloc failed");
        return;
    }

    pstFreeBuffData->ulReceiverPid      = UEPS_PID_CDS;
    pstFreeBuffData->enMsgId            = ID_APS_CDS_CDATA_FREE_BUFF_DATA_IND;
    pstFreeBuffData->usOpId             = 0;
    pstFreeBuffData->ucRabId            = ucRabId;

    PS_SEND_MSG(WUEPS_PID_TAF, pstFreeBuffData);

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_SndCdsModeChangeInd
 ��������  : ֪ͨCDS��ǰ������ģʽ
 �������  : enMode   - ����ģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��24��
    ��    ��   : h00246512
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_SndCdsModeChangeInd(
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrCdataServiceMode
)
{
    APS_CDS_MODE_CHANGE_IND_STRU       *pstSndMsg = VOS_NULL_PTR;
    APS_CDS_MODE_ENUM_UINT32            enMode;

    switch (enCurrCdataServiceMode)
    {
        case TAF_APS_RAT_TYPE_1X:
            enMode = APS_CDS_MODE_1X;
            break;
        case TAF_APS_RAT_TYPE_HRPD:
            enMode = APS_CDS_MODE_EVDO;
            break;
        case TAF_APS_RAT_TYPE_EHRPD:
            enMode = APS_CDS_MODE_EVDO;
            break;
        case TAF_APS_RAT_TYPE_GSM:
        case TAF_APS_RAT_TYPE_WCDMA:
            enMode = APS_CDS_MODE_GU;
            break;
        case TAF_APS_RAT_TYPE_LTE:
            enMode = APS_CDS_MODE_LTE;
            break;
        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndCdsModeChangeInd: Mode Error");
            return;
    }

    pstSndMsg = (APS_CDS_MODE_CHANGE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_CDS_MODE_CHANGE_IND_STRU));

    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndCdsModeChangeInd: Memory alloc failed");
        return;
    }

    pstSndMsg->ulReceiverPid    = UEPS_PID_CDS;
    pstSndMsg->enMsgId          = ID_APS_CDS_MODE_CHANGE_IND;
    pstSndMsg->usOpId           = 0;
    pstSndMsg->enMode           = enMode;

    PS_SEND_MSG(WUEPS_PID_TAF, pstSndMsg);

    return;

}


/*****************************************************************************
 �� �� ��  : TAF_APS_GetCdataBearStatus
 ��������  : ��ȡ1Xģʽ�µĳ��ص�״̬
 �������  : VOS_UINT8                           ucRabId
 �������  : ��
 �� �� ֵ  : APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��28��
    ��    ��   : y00213812
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��1��6��
    ��    ��   : Y00213812
    �޸�����   : �޸�APS״̬������PPP��A�˻�C�˵Ĵ���

  3.��    ��   : 2015��10��20��
    ��    ��   : y00322978
    �޸�����   : ��ѯ��ǰ״̬��װһ����������
*****************************************************************************/
APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8 TAF_APS_GetCdataBearStatus(
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT8                                               ucPdpId;
    APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8                    enBearStatus;

    ucPdpId = TAF_APS_GetPdpIdByNsapi(ucRabId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return APS_CDS_CDATA_BEAR_STATUS_INACTIVE;
    }

    enBearStatus = AT_APS_ConvertPsCdataStatusToCsdCdataStatus(TAF_PS_GetCdataBearStatus(ucPdpId));

    return enBearStatus;
}


/*****************************************************************************
 �� �� ��  : TAF_APS_MapPdnIdToRabId
 ��������  : PDN IDӳ��ΪRABID
 �������  : VOS_UINT8                           ucRabId
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��26��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_APS_MapRabIdToPdnId(
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId = TAF_APS_GetPdpIdByNsapi(ucRabId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return APS_CDS_INVALID_PDN_ID;
    }

    return TAF_APS_GetPdpEntCdataPdnId(ucPdpId);
}

/*****************************************************************************
 �� �� ��  : TAF_APS_MapPdnIdToRabId
 ��������  : PDN ID ӳ��ΪRAB ID
 �������  : VOS_UINT8                           ucPndId
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��26��
    ��    ��   : Y00213812
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_APS_MapPdnIdToRabId(
    VOS_UINT8                           ucPdnId
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId = TAF_APS_GetPdpIdByPndId(ucPdnId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return APS_CDS_INVALID_RAB_ID;
    }

    return TAF_APS_GetPdpEntNsapi(ucPdpId);
}

#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


