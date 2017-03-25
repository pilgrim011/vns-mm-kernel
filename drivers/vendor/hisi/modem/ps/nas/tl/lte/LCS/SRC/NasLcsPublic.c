/******************************************************************************

@(#)Copyright(C)2008,Hisilicon Co. LTD.

******************************************************************************
File name   : NasLcsPublic.c
Description : LCS�Ĺ�������
History     :
1.lihong  00150010       2015-09-28  Draft Enact
******************************************************************************/

/*****************************************************************************
1 Include HeadFile
*****************************************************************************/

#include    "PsCommonDef.h"
#include    "PsTypeDef.h"
#include    "NasCommPrint.h"
#include    "PsLogdef.h"
#include    "NasMmlCtx.h"
#include    "NasUtranCtrlInterface.h"
#include    "NasLcsOm.h"
#include    "LcsLppInterface.h"
#include    "NasLcsMain.h"
#include    "NasMmlLib.h"
#include    "NasLcsTafMsgProc.h"
#include    "NasLcsEncode.h"
#include    "NasLcsMmMsgProc.h"
#include    "NasLcsEmmMsgProc.h"
#include    "NasLcsLppMsgProc.h"
#include    "NasLcsPublic.h"
#include    "LNasNvInterface.h"
#include    "LNvCommon.h"
#include    "ImsaInterface.h"

#define    THIS_FILE_ID            PS_FILE_ID_NASLCSPUBLIC_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLCSPUBLIC_C
/*****************************************************************************
1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_LPP == FEATURE_ON)


/*****************************************************************************
2 Declare the Global Variable
*****************************************************************************/
NAS_LCS_PUB_INFO_STRU   g_stLcsInfo; /* LCSȫ����Ϣ */
NAS_LCS_PUB_INFO_STRU  *pg_stLcsInfo = &g_stLcsInfo;



/*****************************************************************************
3 Function
*****************************************************************************/

/*****************************************************************************
Function Name  : NAS_LCS_IsLteSupportEpcLcs
Discription    : �ж�LTE�Ƿ�֧��EPC-LCS
Input          : None
Output         : None
Return         : VOS_UINT32
History:
1.lihong 00150010 2015-9-30 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LCS_IsLteSupportEpcLcs( VOS_VOID )
{
    NAS_LCS_NW_CAP_INFO_STRU           *pstNwLcsCap     = NAS_LCS_NULL_PTR;
    NAS_MML_UE_NETWORK_CAPABILITY_STRU *pstUeNwCap      = NAS_LCS_NULL_PTR;

    pstNwLcsCap = NAS_LCS_GetNwLcsCap();
    pstUeNwCap  = NAS_MML_GetUeNetWorkCapability();

    /* UE NETWORK CAP�ﲻ����LCS��LPP����������Ϊ��֧�� */
    if (pstUeNwCap->ucUeNetCapLen < NAS_LCS_UE_NW_CAP_LEN_INCLUDE_LCS)
    {
        return PS_FALSE;
    }

    /* ���UE��֧��LCS��LPP������Ϊ��֧��,��ʽ����:
    ProSe-dd ProSe H.245-ASH ACC-CSFB LPP LCS 1xSRVCC NF */
    if ((0 == (pstUeNwCap->aucUeNetCap[NAS_LCS_LPP_CAP_INDEX_UE_NW_CAP] & 0x08))
        || (0 == (pstUeNwCap->aucUeNetCap[NAS_LCS_LPP_CAP_INDEX_UE_NW_CAP] & 0x04)))
    {
        return PS_FALSE;
    }

    /* �������֧��EPC-LCS */
    if (NAS_LCS_NW_EPC_LCS_SUPPORT != pstNwLcsCap->enNwEpcLcs)
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}

/*****************************************************************************
Function Name  : NAS_LCS_IsMoLr
Discription    : �ж��Ƿ���MO-LR
Input          : None
Output         : None
Return         : VOS_UINT32
History:
1.lihong 00150010 2015-10-08 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LCS_IsMoLr
(
    VOS_UINT32                          ulIndex
)
{
    if ((NAS_LCS_MO_LR_LPP_INDEX == ulIndex)
        || (NAS_LCS_MO_LR_TAF_INDEX == ulIndex))
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
Function Name  : NAS_LCS_IsClassmark2SupportLcs
Discription    : �ж�CLASSMARK2�Ƿ�֧��CS-LCS
Input          : None
Output         : None
Return         : VOS_UINT32
History:
1.lihong 00150010 2015-10-13 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LCS_IsClassmark2SupportLcs( VOS_VOID )
{
    VOS_UINT8                           aucMsClassMark2[NAS_MML_CLASSMARK2_LEN] = {0};

    NAS_MML_Fill_IE_ClassMark2(aucMsClassMark2);

    /* ���CLASSMARK2�ĳ���δ����LCS��������Ĭ����Ϊ��֧�� */
    if (aucMsClassMark2[0] < NAS_LCS_CLASSMARK2_LEN_INCLUDE_LCS)
    {
        return PS_FALSE;
    }

    /* ���CLASSMARK2��֧�ֲ�֧��LCS������Ϊ��֧�֣���ʽ����:
    CM3 space LCSVACAP UCS2 SoLSA CMSP A5/3 A5/2 */
    if (0 == (aucMsClassMark2[3] & 0x20))
    {
        return PS_FALSE;
    }

    return PS_TRUE;
}


/*****************************************************************************
Function Name  : NAS_LCS_IsLteSupportCsLcs
Discription    : �ж�LTE�Ƿ�֧��CS-LCS
Input          : None
Output         : None
Return         : VOS_UINT32
History:
1.lihong 00150010 2015-9-30 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LCS_IsLteSupportCsLcs( VOS_VOID )
{
    NAS_LCS_NW_CAP_INFO_STRU           *pstNwLcsCap     = NAS_LCS_NULL_PTR;

    /* �������IMSҵ������ѡ��CS-LCS */
    if (PS_TRUE == IMSA_IsExitImsService())
    {
        return PS_FALSE;
    }

    /* ���CLASSMARK2��֧��CS-LCS������Ϊ��֧�� */
    if (PS_FALSE == NAS_LCS_IsClassmark2SupportLcs())
    {
        return PS_FALSE;
    }

    pstNwLcsCap = NAS_LCS_GetNwLcsCap();

    /* �������֧��CS-LCS������CS-LCS */
    if ((NAS_LCS_NW_CS_LCS_NO_INFORMATION == pstNwLcsCap->enNwCsLcs)
        || (NAS_LCS_NW_CS_LCS_SUPPORT == pstNwLcsCap->enNwCsLcs))
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
Function Name  : NAS_LCS_SelectMolrDomain
Discription    : MO-LR��ѡ��
Input          : None
Output         : None
Return         : NAS_LCS_DOMAIN_TYPE_ENUM_UINT8
History:
1.lihong 00150010 2015-9-29 Draft Enact
*****************************************************************************/
NAS_LCS_DOMAIN_TYPE_ENUM_UINT8 NAS_LCS_SelectMolrDomain( VOS_VOID )
{
    VOS_UINT32                          i               = 0;
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity    = NAS_LCS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat       = NAS_MML_NET_RAT_TYPE_BUTT;

    /* ��ǰ�Ƿ��������LCSʵ�壬������ڣ���ѡ������LCSʵ����� */
    for (i = 0; i < NAS_LCS_MAX_ENTITY_NUM; i++)
    {
        pstLcsEntity = NAS_LCS_GetLcsEntity(i);
        if (NAS_LCS_ENTITY_NOT_USED == pstLcsEntity->enUsedFlag)
        {
            continue;
        }

        return pstLcsEntity->enCurLcsDomain;
    }

    enCurrRat = NAS_MML_GetCurrNetRatType();

    /* ��ǰ���뼼����֧��LCS */
    if ((NAS_MML_NET_RAT_TYPE_LTE < enCurrRat)
        || ((NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat) && (NAS_UTRANCTRL_UTRAN_MODE_FDD != NAS_UTRANCTRL_GetCurrUtranMode())))
    {
        return NAS_LCS_DOMAIN_TYPE_BUTT;
    }

    /* ��ʼ��ѡ�� */
    if (NAS_MML_NET_RAT_TYPE_LTE == enCurrRat)
    {
        /* ���UE֧��LCS��LPP������֧��EPC-LCS������EPC-LCS */
        if (PS_TRUE == NAS_LCS_IsLteSupportEpcLcs())
        {
            return NAS_LCS_DOMAIN_TYPE_EPC_LCS;
        }

        /* ���UE֧��LCS������֧��CS-LCS������CS-LCS */
        if (PS_TRUE == NAS_LCS_IsLteSupportCsLcs())
        {
            return NAS_LCS_DOMAIN_TYPE_CS_LCS;
        }

        return NAS_LCS_DOMAIN_TYPE_BUTT;
    }
    else
    {
        /* ���UE֧��LCS������CS-LCS */
        if (PS_TRUE == NAS_LCS_IsClassmark2SupportLcs())
        {
            return NAS_LCS_DOMAIN_TYPE_CS_LCS;
        }

        return NAS_LCS_DOMAIN_TYPE_BUTT;
    }
}

/*****************************************************************************
Function Name   : NAS_LCS_IsCurrRatSupportLcs
Description     : �жϵ�ǰ���뼼���Ƿ�֧��LCS
Input           : NONE
Output          : None
Return          : VOS_UINT32

History         :
1.leixiantiao 00258641 2015-9-29 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LCS_IsCurrRatSupportLcs(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat       = NAS_MML_NET_RAT_TYPE_BUTT;
    enCurrRat = NAS_MML_GetCurrNetRatType();

    /* TDS/WCDMA��֧��LCS */
    if ((NAS_MML_NET_RAT_TYPE_LTE < enCurrRat)
        || ((NAS_MML_NET_RAT_TYPE_WCDMA == enCurrRat) && (NAS_UTRANCTRL_UTRAN_MODE_FDD != NAS_UTRANCTRL_GetCurrUtranMode())))
    {
        return PS_FALSE;
    }

    if (NAS_MML_NET_RAT_TYPE_LTE == enCurrRat)
    {
        /* ���UE��ǰפ����LTE��, ��֧��LCS��LPP, ����ΪUE��ǰ���뼼��֧��LCS */
        if (PS_TRUE == NAS_LCS_IsLteSupportEpcLcs())
        {
            return PS_TRUE;
        }
    }
    else
    {
        /* ���UE��ǰפ����GU��, ��֧��CS LCS, ����ΪUE��ǰ���뼼��֧��LCS */
        if (PS_TRUE == NAS_LCS_IsClassmark2SupportLcs())
        {
            return PS_TRUE;
        }
    }

    return PS_FALSE;
}

/*****************************************************************************
Function Name   : NAS_LCS_IsTimerNameValid
Description     : �ж϶�ʱ�����Ƿ�Ϸ�
Input           : ulIndex---------------------ʵ������
                  enLcsTimerType--------------��ʱ������
Output          : None
Return          : VOS_UINT32

History         :
1.lihong 00150010 2015-9-29 Draft Enact
*****************************************************************************/
VOS_UINT32  NAS_LCS_IsTimerNameValid
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType
)
{
    if (enLcsTimerType >= TI_NAS_LCS_TIMER_BUTT)
    {
        return PS_FALSE;
    }

    if (ulIndex < NAS_LCS_MAX_ENTITY_NUM)
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
Function Name   : NAS_LCS_GetTimer
Description     : ��ȡ��ʱ��
Input           : ulIndex---------------------ʵ������
                  enLcsTimerType--------------��ʱ������
Output          : None
Return          : NAS_LCS_TIMER_INFO_STRU*

History         :
1.lihong00150010      2015-9-29  Draft Enact

*****************************************************************************/
NAS_LCS_TIMER_INFO_STRU*  NAS_LCS_GetTimer
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType
)
{
    NAS_LCS_TIMER_INFO_STRU            *pstTimerInfo = NAS_LCS_NULL_PTR;

    /*���ݶ�ʱ����ͬ���ͣ���ȡ��ʱ��*/
    switch(enLcsTimerType)
    {
    case TI_NAS_LCS_WAIT_NW_RSP_TIMER:
    case TI_NAS_LCS_WAIT_UE_RSP_TIMER:
    case TI_NAS_LCS_PERIOD_INTERVAL_TIMER:
        pstTimerInfo = NAS_LCS_GetStateTimer(ulIndex);
        break;

    case TI_NAS_LCS_WATI_REEST_TIMER:
        pstTimerInfo = NAS_LCS_GetWaitResetTimer(ulIndex);
        break;

    default :
        break;
    }

    return pstTimerInfo;
}

/*****************************************************************************
Function Name   : NAS_LCS_GetTimerLen
Description     : ��ȡ��ʱ��ʱ��
Input           : ulIndex---------------------ʵ������
                  enLcsTimerType--------------��ʱ������
Output          : None
Return          : VOS_UINT32

History         :
1.lihong00150010      2015-9-29  Draft Enact

*****************************************************************************/
VOS_UINT32  NAS_LCS_GetTimerLen
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType
)
{
    VOS_UINT32                          ulTimerLen      = 0;
    LCS_MOLR_PARA_STRU                 *pstMolrPara     = NAS_LCS_NULL_PTR;
    NAS_LCS_COMM_NV_PARA_STRU          *pstCommNvPara   = NAS_LCS_NULL_PTR;

    pstMolrPara     = NAS_LCS_GetTafMolrRecord();
    pstCommNvPara   = NAS_LCS_GetCommNvPara();

    /*���ݶ�ʱ����ͬ���ͣ���ʱ��ʱ����ͬ*/
    switch( enLcsTimerType )
    {
        case TI_NAS_LCS_WAIT_NW_RSP_TIMER:
            if (NAS_LCS_MO_LR_LPP_INDEX == ulIndex)
            {
                ulTimerLen = TI_NAS_LCS_LPP_WAIT_NW_RSP_TIMER_LEN;
            }
            else
            {
                ulTimerLen  = pstMolrPara->usTimeOut * 1000;
            }

            break;

        case TI_NAS_LCS_WAIT_UE_RSP_TIMER:
            ulTimerLen = TI_NAS_LCS_LPP_WAIT_USER_RSP_TIMER_LEN;
            break;

        case TI_NAS_LCS_WATI_REEST_TIMER:
            ulTimerLen = pstCommNvPara->usRetryTimerLen * 1000;
            break;

        case TI_NAS_LCS_PERIOD_INTERVAL_TIMER:
            ulTimerLen = pstMolrPara->usInterval * 1000;
            break;

        default :
            break;
    }

    return ulTimerLen;
}


/*****************************************************************************
Function Name  : NAS_LCS_StartTimer
Discription    : ������ʱ��
Input          : ulIndex---------------------ʵ������
                 enLcsTimerType--------------��ʱ������
Output         : None
Return         : None
History:
1.lihong 00150010 2015-9-29 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_StartTimer
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType
)
{
    VOS_UINT32                          ulTimerLen   = NAS_LCS_NULL;
    NAS_LCS_TIMER_INFO_STRU            *pstTimerInfo = NAS_LCS_NULL_PTR;

    /*��ulIndex�Ϸ����ж�*/
    if (PS_FALSE == NAS_LCS_IsTimerNameValid(ulIndex, enLcsTimerType))
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_LCS_WARN_LOG("NAS_LCS_StartTimer: WARN: Input Para(ulIndex) err !");
        TLPS_PRINT2LAYER_WARNING1(NAS_LCS_StartTimer_ENUM, LNAS_PARAM_INVALID, 1);
        return;
    }

    /*������Ϣ��Ӧ�������źͶ�ʱ������,��ȡ������Ķ�ʱ��*/
    pstTimerInfo = NAS_LCS_GetTimer(ulIndex, enLcsTimerType);
    if (pstTimerInfo == VOS_NULL_PTR)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_LCS_ERR_LOG("NAS_LCS_StartTimer:ERROR: Get Timer failed.");
        TLPS_PRINT2LAYER_ERROR1(NAS_LCS_StartTimer_ENUM, LNAS_PARAM_INVALID, 2);
        return;
    }

    /*�ж϶�ʱ���Ƿ�򿪣��Ѵ���ر�*/
    if(VOS_NULL_PTR != pstTimerInfo->hTimer)
    {
        /*�ر�ʧ�ܣ��򱨾�����*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->hTimer)))
        {
            /*��ӡ�쳣��Ϣ*/
            NAS_LCS_WARN_LOG("NAS_LCS_StartTimer:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_WARNING(NAS_LCS_StartTimer_ENUM, LNAS_LCS_StopTimerFail);
            return;
        }

        /*��ӡ�쳣��Ϣ*/
        NAS_LCS_ERR_LOG2("(TimerType) Timer not close!",pstTimerInfo->enLcsTimerType, ulIndex);
        TLPS_PRINT2LAYER_INFO2(NAS_LCS_StartTimer_ENUM, LNAS_LCS_StartTimerWhichIsRunning, pstTimerInfo->enLcsTimerType, ulIndex);
    }

    /*���ݶ�ʱ����ͬ���ͣ���ʱ����Ϣ��ͬ*/
    ulTimerLen = NAS_LCS_GetTimerLen(ulIndex, enLcsTimerType);
    if (ulTimerLen == NAS_LCS_NULL)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_LCS_ERR_LOG("NAS_LCS_StartTimer:ERROR: start unreasonable reltimer.");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_StartTimer_ENUM, LNAS_LCS_TimerLengthInvalid);
        return;
    }

    /*�趨��ʱ��NAME,enLcsTimerType�趨��ʱ��Para����ʧ���򱨾�����*/
    if (VOS_OK !=\
            PS_START_REL_TIMER(&(pstTimerInfo->hTimer),WUEPS_PID_LCS,\
                                ulTimerLen,ulIndex,\
                                (VOS_UINT32)enLcsTimerType,VOS_RELTIMER_NOLOOP))
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_LCS_WARN_LOG("NAS_LCS_StartTimer:WARN: start reltimer error!");
        TLPS_PRINT2LAYER_WARNING(NAS_LCS_StartTimer_ENUM, LNAS_LCS_StartTimerFail);
        return;
    }

    /*���¶�ʱ��������Ϣ�Ͷ�ʱ�����*/
    pstTimerInfo->enLcsTimerType = enLcsTimerType;

    /*������ǰ�Ķ�ʱ����Ϣ */
    NAS_LCS_SndOmTimerStart(ulIndex, enLcsTimerType, ulTimerLen);
}

/*****************************************************************************
Function Name  : NAS_LCS_StopTimer
Discription    : ֹͣĳһ���ض�ʱ��
Input          : ulIndex---------------------ʵ������
                 enLcsTimerType--------------��ʱ������
Output         : VOS_VOID
Return         : None
History:
1.lihong 00150010    2015-09-29  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_StopTimer
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType
)
{
    NAS_LCS_TIMER_INFO_STRU            *pstTimerInfo        = NAS_LCS_NULL_PTR;
    VOS_UINT32                          ulTimerRemainLen    = 0;

    /*��ulIndex�Ϸ����ж�*/
    if (PS_FALSE == NAS_LCS_IsTimerNameValid(ulIndex, enLcsTimerType))
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_LCS_WARN_LOG("NAS_LCS_StopTimer: WARN: Input Para(ulIndex) err !");
        TLPS_PRINT2LAYER_WARNING1(NAS_LCS_StopTimer_ENUM, LNAS_PARAM_INVALID, 1);
        return;
    }

    /*������Ϣ��Ӧ�������źͶ�ʱ������,��ȡ������Ķ�ʱ��*/
    pstTimerInfo = NAS_LCS_GetTimer(ulIndex, enLcsTimerType);
    if (pstTimerInfo == VOS_NULL_PTR)
    {
        /*��ӡ�쳣��Ϣ*/
        NAS_LCS_ERR_LOG("NAS_LCS_StopTimer:ERROR:Get Timer failed.");
        TLPS_PRINT2LAYER_ERROR1(NAS_LCS_StopTimer_ENUM, LNAS_PARAM_INVALID, 2);
        return;
    }

    /*��ʱ�����ڴ�״̬����رգ����򣬺���*/
    if(VOS_NULL_PTR != pstTimerInfo->hTimer)
    {
        /* ��ȡ��ǰ��ʱ����ʣ��ʱ�� */
        if (VOS_OK != VOS_GetRelTmRemainTime(&(pstTimerInfo->hTimer), &ulTimerRemainLen ))
        {
            ulTimerRemainLen = 0;
        }

        /*�ر�ʧ�ܣ��򱨾�����*/
        if (VOS_OK != PS_STOP_REL_TIMER(&(pstTimerInfo->hTimer)))
        {
            /*��ӡ�쳣��Ϣ*/
            NAS_LCS_WARN_LOG("NAS_LCS_StopTimer:WARN: stop reltimer error!");
            TLPS_PRINT2LAYER_WARNING(NAS_LCS_StopTimer_ENUM, LNAS_LCS_StopTimerFail);
            return;
        }

        /*���¶�ʱ����ʱ����*/
        pstTimerInfo->ucExpireTimes = 0;


        /*������ǰ�Ķ�ʱ����Ϣ */
        NAS_LCS_SndOmTimerStop(ulIndex, enLcsTimerType, ulTimerRemainLen);
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_IsTimerRunning
Discription    : �ж�ĳһ��ʱ���Ƿ�����
Input          : ulIndex---------------------ʵ������
                 enLcsTimerType--------------��ʱ������
Output         : VOS_VOID
Return         : NAS_LCS_TIMER_RUN_STA_ENUM_UINT32
History:
1.lihong 00150010    2015-10-10  Draft Enact
*****************************************************************************/
NAS_LCS_TIMER_RUN_STA_ENUM_UINT32  NAS_LCS_IsTimerRunning
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_TIMER_ID_ENUM_UINT8         enLcsTimerType
)
{
    NAS_LCS_TIMER_INFO_STRU            *pstTimerInfo = NAS_LCS_NULL_PTR;

    /*��ȡ��Э�鶨ʱ�����ƿ��ַ*/
    pstTimerInfo = NAS_LCS_GetTimer(ulIndex, enLcsTimerType);
    if ( NAS_LCS_NULL_PTR == pstTimerInfo )
    {
        NAS_LCS_ERR_LOG("NAS_LCS_IsTimerRunning: pstPtlTimer NULL.");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_IsTimerRunning_ENUM, LNAS_NULL_PTR);
        return NAS_LCS_TIMER_INVALID;
    }

    /*����״̬��ʱ���Ƿ�������*/
    if ( NAS_LCS_NULL_PTR != pstTimerInfo->hTimer )
    {
        return NAS_LCS_TIMER_RUNNING;
    }
    else
    {
        return NAS_LCS_TIMER_STOPED;
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_StopAllTimer
Discription    : ֹͣ���ж�ʱ��
Input          : ulIndex---------------------ʵ������
Output         : VOS_VOID
Return         : None
History:
1.lihong 00150010    2015-10-08  Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_StopAllTimer
(
    VOS_UINT32                          ulIndex
)
{
    VOS_UINT8                          i = 0;

    for (i = TI_NAS_LCS_WAIT_NW_RSP_TIMER; i < TI_NAS_LCS_TIMER_BUTT; i++)
    {
        NAS_LCS_StopTimer(ulIndex, i);
    }
}


/*****************************************************************************
Function Name  : NAS_LCS_CreateHandleId
Discription    : ����handlle id
Input          : None
Output         : None
Return         : VOS_UINT8
History:
1.lihong 00150010 2015-9-29 Draft Enact
*****************************************************************************/
VOS_UINT8 NAS_LCS_CreateHandleId(VOS_VOID)
{
    /* ����ﵽ���ֵ�����0��ʼ */
    if (NAS_LCS_MAX_HANDLE_ID == NAS_LCS_GetCurHandleId())
    {
        NAS_LCS_SetCurHandleId(0);
        return 0;
    }

    NAS_LCS_GetCurHandleId() = NAS_LCS_GetCurHandleId() + 1;
    return NAS_LCS_GetCurHandleId();
}

/*****************************************************************************
Function Name  : NAS_LCS_CreateInvokeId
Discription    : ����invoke id
Input          : None
Output         : None
Return         : VOS_UINT8
History:
1.lihong 00150010 2015-10-16 Draft Enact
*****************************************************************************/
VOS_UINT8 NAS_LCS_CreateInvokeId( VOS_VOID )
{
    /* ����ﵽ���ֵ�����0��ʼ */
    if (NAS_LCS_MAX_INVOKE_ID == NAS_LCS_GetCurInvokeId())
    {
        NAS_LCS_SetCurInvokeId(0);
        return 0;
    }

    NAS_LCS_GetCurInvokeId() = NAS_LCS_GetCurInvokeId() + 1;
    return NAS_LCS_GetCurInvokeId();
}

/*****************************************************************************
Function Name  : NAS_LCS_CreateMoTi
Discription    : ����MO TI
�˺���������TIֵ�����пտ��д����MO TIֵ��8��
��������Ŀ����Ϊ������MM�������������������͵�������Ϣ��TI��
ͬʱ����ظ�REGISTERʱ������������пտڵ�TI�����ϼ�8��������ʱͨ��
�յ������·�TIֵ���в�ѯʱ�Ͳ���ת����
Input          : None
Output         : None
Return         : VOS_UINT8
History:
1.lihong 00150010 2015-10-16 Draft Enact
*****************************************************************************/
VOS_UINT8 NAS_LCS_CreateMoTi
(
    VOS_UINT32                          ulIndex
)
{
    /* ����14��13��������8��9����Ϊ�˾�������SS������TI�ظ� */
    if (NAS_LCS_MO_LR_TAF_INDEX == ulIndex)
    {
        return NAS_LCS_TAF_MO_LR_TI;
    }
    else
    {
        return NAS_LCS_LPP_MO_LR_TI;
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_CreateLcsEntity
Discription    : ����LCSʵ��
Input          : enStartSource---------------����Դ
Output         : pulIndex--------------------ʵ������
Return         : VOS_UINT32
History:
1.lihong 00150010 2015-9-29 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LCS_CreateLcsEntity
(
    NAS_LCS_START_SOURCE_ENUM_UINT8     enStartSource,
    VOS_UINT32                         *pulIndex
)
{
    VOS_UINT32                          i = 0;
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity = NAS_LCS_NULL_PTR;

    /* �����MT-LR���ͣ�����Ҫ���±�Ϊ2~4��ʵ���в����Ƿ���ڿ��е�ʵ�� */
    if (NAS_LCS_START_SOURCE_NW == enStartSource)
    {
        for (i = NAS_LCS_MT_LR_ENTITY_INDEX_BEGIN; i <= NAS_LCS_MT_LR_ENTITY_INDEX_END; i++)
        {
            pstLcsEntity = NAS_LCS_GetLcsEntity(i);
            if (NAS_LCS_ENTITY_NOT_USED == pstLcsEntity->enUsedFlag)
            {
                break;
            }
        }

        if (i > NAS_LCS_MT_LR_ENTITY_INDEX_END)
        {
            return NAS_LCS_FAIL;
        }

        /* ��ʼ��MT-LRʵ����Ϣ */
        *pulIndex                   = i;
        pstLcsEntity->enUsedFlag    = NAS_LCS_ENTITY_USED;
        pstLcsEntity->enConnState   = NAS_LCS_CONN_STATE_CONN;
        pstLcsEntity->enEntityState = NAS_LCS_ENTITY_STATE_WAIT_USER_RSP;
        pstLcsEntity->enStartSource = NAS_LCS_START_SOURCE_NW;
        pstLcsEntity->ucHandleId    = NAS_LCS_CreateHandleId();

        return NAS_LCS_SUCC;
    }

    /* �����LPP������MO-LR����ȡ�±�Ϊ0��ʵ�� */
    if (NAS_LCS_START_SOURCE_LPP == enStartSource)
    {
        pstLcsEntity = NAS_LCS_GetLcsEntity(NAS_LCS_MO_LR_LPP_INDEX);

        if (NAS_LCS_ENTITY_NOT_USED != pstLcsEntity->enUsedFlag)
        {
            return NAS_LCS_FAIL;
        }

        /* ��ʼ��MO-LRʵ����Ϣ */
        *pulIndex                   = NAS_LCS_MO_LR_LPP_INDEX;
        pstLcsEntity->enUsedFlag    = NAS_LCS_ENTITY_USED;
        pstLcsEntity->enConnState   = NAS_LCS_CONN_STATE_IDLE;
        pstLcsEntity->enEntityState = NAS_LCS_ENTITY_STATE_WAIT_NW_RSP;
        pstLcsEntity->enStartSource = NAS_LCS_START_SOURCE_LPP;

        return NAS_LCS_SUCC;
    }

    /* �����TAF������MO-LR����ȡ�±�Ϊ0��ʵ�� */
    if (NAS_LCS_START_SOURCE_TAF == enStartSource)
    {
        pstLcsEntity = NAS_LCS_GetLcsEntity(NAS_LCS_MO_LR_TAF_INDEX);

        if (NAS_LCS_ENTITY_NOT_USED != pstLcsEntity->enUsedFlag)
        {
            return NAS_LCS_FAIL;
        }

        /* ��ʼ��MO-LRʵ����Ϣ */
        *pulIndex                   = NAS_LCS_MO_LR_TAF_INDEX;
        pstLcsEntity->enUsedFlag    = NAS_LCS_ENTITY_USED;
        pstLcsEntity->enConnState   = NAS_LCS_CONN_STATE_IDLE;
        pstLcsEntity->enEntityState = NAS_LCS_ENTITY_STATE_WAIT_NW_RSP;
        pstLcsEntity->enStartSource = NAS_LCS_START_SOURCE_TAF;

        return NAS_LCS_SUCC;
    }

    return NAS_LCS_FAIL;
}

/*****************************************************************************
Function Name  : NAS_LCS_ClearSingleLcsEntity
Discription    : �ͷŵ���LCSʵ��
Input          : ulIndex---------------����
                 enCause---------------�ͷ�ԭ��ֵ
Output         : None
Return         : VOS_VOID
History:
1.lihong 00150010 2015-9-29 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_ClearSingleLcsEntity
(
    VOS_UINT32                          ulIndex,
    TAF_LCS_CAUSE_ENUM_UINT32           enCause
)
{
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity = NAS_LCS_NULL_PTR;

    /* �����LPP������MO-LR�ͷţ�����Ҫ֪ͨTAF */
    if (NAS_LCS_MO_LR_LPP_INDEX != ulIndex)
    {
        if (NAS_LCS_MO_LR_TAF_INDEX == ulIndex)
        {
            NAS_LCS_SndTafEndInd(TAF_LCS_LR_TYPE_MO, enCause, 0);
        }
        else
        {
            NAS_LCS_SndTafEndInd(TAF_LCS_LR_TYPE_MT, enCause, NAS_LCS_GetEntityHandleId(ulIndex));
        }
    }

    pstLcsEntity = NAS_LCS_GetLcsEntity(ulIndex);

    /* ֹͣ���ж�ʱ�� */
    NAS_LCS_StopAllTimer(ulIndex);

    NAS_LCS_MEM_SET_S(  pstLcsEntity,
                        sizeof(NAS_LCS_ENTITY_INFO_STRU),
                        0,
                        sizeof(NAS_LCS_ENTITY_INFO_STRU));

    pstLcsEntity->enCurLcsDomain    = NAS_LCS_DOMAIN_TYPE_BUTT;
    pstLcsEntity->enStartSource     = NAS_LCS_START_SOURCE_BUTT;
    pstLcsEntity->enUsedFlag        = NAS_LCS_ENTITY_NOT_USED;
}

/*****************************************************************************
Function Name  : NAS_LCS_SndFacility
Discription    : ����FACILITY������
Input          : ulIndex-----------------ʵ������
Output         : None
Return         : None
History:
1.lihong 00150010 2015-10-17 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_SndFacility
(
    VOS_UINT32                          ulIndex
)
{
    NAS_LCS_ENCODE_INFO_STRU            stEncodeInfo    = {0};
    NAS_LCS_ENCODE_BUFFER_STRU         *pstEncodeBuffer = NAS_LCS_NULL_PTR;

    NAS_LCS_MEM_SET_S(  &stEncodeInfo,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU));

    stEncodeInfo.ucTi           = NAS_LCS_GetEntityTi(ulIndex) - NAS_LCS_TI_OFFSET;
    stEncodeInfo.enStartSource  = NAS_LCS_GetEntityStrartSource(ulIndex);
    stEncodeInfo.enOperType     = NAS_LCS_OPERATION_MO_LR;
    stEncodeInfo.bitOpInvokeId  = NAS_LCS_OP_TRUE;
    stEncodeInfo.ucInvokeId     = NAS_LCS_GetEntityInvokeId(ulIndex);

    pstEncodeBuffer             = NAS_LCS_GetEncodeBuffer();
    if (NAS_LCS_CAUSE_SUCCESS == NAS_LCS_EncodeFacility(    pstEncodeBuffer->aucBuffer,
                                                            &pstEncodeBuffer->ulBufferLen,
                                                            &stEncodeInfo))
    {
        NAS_LCS_SndAirMsgReportInd( pstEncodeBuffer->aucBuffer,
                                    pstEncodeBuffer->ulBufferLen,
                                    NAS_LCS_AIR_MSG_DIR_ENUM_UP,
                                    LCS_FACILITY);

        /* ���������ڵ��򷢸���Ӧģ�� */
        if (NAS_LCS_DOMAIN_TYPE_CS_LCS == NAS_LCS_GetEntityLcsDomain(ulIndex))
        {
            NAS_LCS_SndMmDataReq(   NAS_LCS_GetEntityTi(ulIndex),
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
        else
        {
            NAS_LCS_SndLmmDataReq(  NAS_LCS_GetEntityTi(ulIndex),
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
    }
    else
    {
        /* �ͷ�LCSʵ�� */
        NAS_LCS_ClearLcsEntityAndNotify(ulIndex, TAF_LCS_CAUSE_OTHERS);
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_SndMtlrRspReleaseComplte
Discription    : ͨ��RELEASE COMPLTE��Ϣ��MTLR�û��ظ���������
Input          : ulIndex-----------------ʵ������
               : enLocNtfRsp-------------�û��ظ�MTLR���
Output         : None
Return         : None
History:
1.leixiantiao 00258641 2015-10-24 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_SndMtlrRspReleaseComplte
(
    VOS_UINT32                          ulIndex,
    LCS_MTLRA_OP_ENUM_UINT8             enLocNtfRsp
)
{
    NAS_LCS_ENCODE_INFO_STRU            stEncodeInfo    = {0};
    NAS_LCS_ENCODE_BUFFER_STRU         *pstEncodeBuffer = NAS_LCS_NULL_PTR;

    NAS_LCS_MEM_SET_S(  &stEncodeInfo,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU));

    /* ��д�տ�TIֵ */
    stEncodeInfo.ucTi       = NAS_LCS_GetEntityTi(ulIndex) + NAS_LCS_TI_OFFSET;

    /* ��дMTLR�ظ���� */
    if (LCS_MTLRA_OP_BUTT != enLocNtfRsp)
    {
        stEncodeInfo.bitLocNtfRsp = NAS_LCS_OP_TRUE;
        stEncodeInfo.enLocNtfRsp  = enLocNtfRsp;
    }

    /* ��дInvokeId */
    stEncodeInfo.bitOpInvokeId  = NAS_LCS_OP_TRUE;
    stEncodeInfo.ucInvokeId     = NAS_LCS_GetEntityInvokeId(ulIndex);

    stEncodeInfo.enOperType     = NAS_LCS_OPERATION_LOC_NOTIFICATION;

    pstEncodeBuffer             = NAS_LCS_GetEncodeBuffer();

    /* ����RELEASE COMPLETE */
    if (NAS_LCS_CAUSE_SUCCESS == NAS_LCS_EncodeRelComplete( pstEncodeBuffer->aucBuffer,
                                                            &pstEncodeBuffer->ulBufferLen,
                                                            &stEncodeInfo))
    {
        NAS_LCS_SndAirMsgReportInd( pstEncodeBuffer->aucBuffer,
                                    pstEncodeBuffer->ulBufferLen,
                                    NAS_LCS_AIR_MSG_DIR_ENUM_UP,
                                    LCS_RELEASE_COMPLTE);

        /* ���������ڵ��򷢸���Ӧģ�� */
        if (NAS_LCS_DOMAIN_TYPE_CS_LCS == NAS_LCS_GetEntityLcsDomain(ulIndex))
        {
            NAS_LCS_SndMmDataReq(   NAS_LCS_GetEntityTi(ulIndex),
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
        else
        {
            NAS_LCS_SndLmmDataReq(  NAS_LCS_GetEntityTi(ulIndex),
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_SndReleaseComplte
Discription    : ����RELEASE COMPLTE������
Input          : ulIndex-----------------ʵ������
Output         : None
Return         : None
History:
1.lihong 00150010 2015-10-16 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_SndReleaseComplte
(
    VOS_UINT32                          ulIndex
)
{
    NAS_LCS_ENCODE_INFO_STRU            stEncodeInfo    = {0};
    NAS_LCS_ENCODE_BUFFER_STRU         *pstEncodeBuffer = NAS_LCS_NULL_PTR;

    NAS_LCS_MEM_SET_S(  &stEncodeInfo,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU));

    /* ��д�տ�TIֵ */
    if (PS_TRUE == NAS_LCS_IsMoLr(ulIndex))
    {
        stEncodeInfo.ucTi       = NAS_LCS_GetEntityTi(ulIndex) - NAS_LCS_TI_OFFSET;
    }
    else
    {
        stEncodeInfo.ucTi       = NAS_LCS_GetEntityTi(ulIndex) + NAS_LCS_TI_OFFSET;
    }

    /* ��дInvokeId */
    stEncodeInfo.bitOpInvokeId  = NAS_LCS_OP_TRUE;
    stEncodeInfo.ucInvokeId     = NAS_LCS_GetEntityInvokeId(ulIndex);

    pstEncodeBuffer             = NAS_LCS_GetEncodeBuffer();

    /* ����RELEASE COMPLETE */
    if (NAS_LCS_CAUSE_SUCCESS == NAS_LCS_EncodeRelComplete( pstEncodeBuffer->aucBuffer,
                                                            &pstEncodeBuffer->ulBufferLen,
                                                            &stEncodeInfo))
    {
        NAS_LCS_SndAirMsgReportInd( pstEncodeBuffer->aucBuffer,
                                    pstEncodeBuffer->ulBufferLen,
                                    NAS_LCS_AIR_MSG_DIR_ENUM_UP,
                                    LCS_RELEASE_COMPLTE);

        /* ���������ڵ��򷢸���Ӧģ�� */
        if (NAS_LCS_DOMAIN_TYPE_CS_LCS == NAS_LCS_GetEntityLcsDomain(ulIndex))
        {
            NAS_LCS_SndMmDataReq(   NAS_LCS_GetEntityTi(ulIndex),
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
        else
        {
            NAS_LCS_SndLmmDataReq(  NAS_LCS_GetEntityTi(ulIndex),
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_SndMtlrFailReleaseComplte
Discription    : ����MT LRʧ�ܷ���RELEASE COMPLTE������
Input          : ucDlAirTi---------------���пտ�TI
enLcsDomainType---------��
enCause-----------------ԭ��ֵ
Output         : None
Return         : None
History:
1.lihong 00150010 2015-10-13 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_SndMtlrFailReleaseComplte
(
    VOS_UINT8                           ucDlAirTi,
    VOS_UINT8                           ucInvokeId,
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enLcsDomainType,
    NAS_LCS_NW_CAUSE_ENUM_UINT32        enCause
)
{
    NAS_LCS_ENCODE_INFO_STRU            stEncodeInfo    = {0};
    NAS_LCS_ENCODE_BUFFER_STRU         *pstEncodeBuffer = NAS_LCS_NULL_PTR;

    NAS_LCS_MEM_SET_S(  &stEncodeInfo,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU));

    /* ��д�տ�TIֵ */
    stEncodeInfo.ucTi           = ucDlAirTi + NAS_LCS_TI_OFFSET;

    if (NAS_LCS_NW_CAUSE_BUTT != enCause)
    {
        stEncodeInfo.bitOpCause = NAS_LCS_OP_TRUE;
        stEncodeInfo.enCause    = enCause;
    }

    /* ��дInvokeId */
    stEncodeInfo.bitOpInvokeId  = NAS_LCS_OP_TRUE;
    stEncodeInfo.ucInvokeId     = ucInvokeId;

    pstEncodeBuffer             = NAS_LCS_GetEncodeBuffer();

    /* ����RELEASE COMPLETE */
    if (NAS_LCS_CAUSE_SUCCESS == NAS_LCS_EncodeRelComplete( pstEncodeBuffer->aucBuffer,
                                                            &pstEncodeBuffer->ulBufferLen,
                                                            &stEncodeInfo))
    {
        NAS_LCS_SndAirMsgReportInd( pstEncodeBuffer->aucBuffer,
                                    pstEncodeBuffer->ulBufferLen,
                                    NAS_LCS_AIR_MSG_DIR_ENUM_UP,
                                    LCS_RELEASE_COMPLTE);

        /* ���������ڵ��򷢸���Ӧģ�� */
        if (NAS_LCS_DOMAIN_TYPE_CS_LCS == enLcsDomainType)
        {
            NAS_LCS_SndMmDataReq(   ucDlAirTi,
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
        else
        {
            NAS_LCS_SndLmmDataReq(  ucDlAirTi,
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
    }
}


/*****************************************************************************
Function Name  : NAS_LCS_SndRegister
Discription    : ����REGISTER������
Input          : ulIndex-----------------ʵ������
Output         : None
Return         : None
History:
1.lihong 00150010 2015-10-13 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_SndRegister
(
    VOS_UINT32                          ulIndex
)
{
    NAS_LCS_ENCODE_INFO_STRU            stEncodeInfo    = {0};
    NAS_LCS_ENCODE_BUFFER_STRU         *pstEncodeBuffer = NAS_LCS_NULL_PTR;

    NAS_LCS_MEM_SET_S(  &stEncodeInfo,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU));

    stEncodeInfo.ucTi           = NAS_LCS_GetEntityTi(ulIndex) - NAS_LCS_TI_OFFSET;
    stEncodeInfo.enStartSource  = NAS_LCS_GetEntityStrartSource(ulIndex);
    stEncodeInfo.enOperType     = NAS_LCS_OPERATION_MO_LR;
    stEncodeInfo.bitOpInvokeId  = NAS_LCS_OP_TRUE;
    stEncodeInfo.ucInvokeId     = NAS_LCS_GetEntityInvokeId(ulIndex);

    pstEncodeBuffer             = NAS_LCS_GetEncodeBuffer();
    if (NAS_LCS_CAUSE_SUCCESS == NAS_LCS_EncodeRegister(    pstEncodeBuffer->aucBuffer,
                                                            &pstEncodeBuffer->ulBufferLen,
                                                            &stEncodeInfo))
    {
        NAS_LCS_SndAirMsgReportInd( pstEncodeBuffer->aucBuffer,
                                    pstEncodeBuffer->ulBufferLen,
                                    NAS_LCS_AIR_MSG_DIR_ENUM_UP,
                                    LCS_REGISTER);

        /* ���������ڵ��򷢸���Ӧģ�� */
        if (NAS_LCS_DOMAIN_TYPE_CS_LCS == NAS_LCS_GetEntityLcsDomain(ulIndex))
        {
            NAS_LCS_SndMmDataReq(   NAS_LCS_GetEntityTi(ulIndex),
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
        else
        {
            NAS_LCS_SndLmmDataReq(  NAS_LCS_GetEntityTi(ulIndex),
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
    }
    else
    {
        /* �ͷ�LCSʵ�� */
        NAS_LCS_ClearLcsEntityAndNotify(ulIndex, TAF_LCS_CAUSE_OTHERS);
    }
}


/*****************************************************************************
Function Name  : NAS_LCS_ClearAllEntity
Discription    : �ͷ�����ʵ��
Input          : None
Output         : None
Return         : None
History:
1.lihong 00150010 2015-10-13 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_ClearAllEntity ( VOS_VOID )
{
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity    = NAS_LCS_NULL_PTR;
    VOS_UINT32                          i               = 0;

    for (i = NAS_LCS_MO_LR_LPP_INDEX; i <= NAS_LCS_MT_LR_ENTITY_INDEX_END; i++)
    {
        pstLcsEntity = NAS_LCS_GetLcsEntity(i);
        if (NAS_LCS_ENTITY_USED != pstLcsEntity->enUsedFlag)
        {
            continue ;
        }

        if (NAS_LCS_CONN_STATE_CONN == NAS_LCS_GetEntityConnState(i))
        {
            /* ����RELEASE COMPLTE��Ϣ���������� */
            NAS_LCS_SndReleaseComplte(i);
        }

        NAS_LCS_ClearLcsEntityAndNotify(i, TAF_LCS_CAUSE_SUCCESS);
    }

    return ;
}

/*****************************************************************************
Function Name  : NAS_LCS_ClearResource
Discription    : �����Դ
Input          : None
Output         : None
Return         : None
History:
1.lihong 00150010 2015-10-13 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_ClearResource ( VOS_VOID )
{
    NAS_LCS_ClearAllEntity();

    NAS_LCS_Init();
}


/*****************************************************************************
Function Name  : NAS_LCS_ClearLcsEntityAndNotify
Discription    : �ͷŵ���LCSʵ�岢֪ͨ������
Input          : ulIndex---------------����
                 enCause---------------�ͷ�ԭ��ֵ
Output         : None
Return         : VOS_VOID
History:
1.lihong 00150010 2015-9-29 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_ClearLcsEntityAndNotify
(
    VOS_UINT32                          ulIndex,
    TAF_LCS_CAUSE_ENUM_UINT32           enCause
)
{
    if (NAS_LCS_MO_LR_LPP_INDEX == ulIndex)
    {
        /* ֪ͨLPP��ȡ������Ϣʧ�� */
        if (TAF_LCS_CAUSE_SUCCESS == enCause)
        {
            NAS_LCS_SndLppGnssAssistDataCnf(LCS_LPP_RSLT_SUCC);
        }
        else
        {
            NAS_LCS_SndLppGnssAssistDataCnf(LCS_LPP_RSLT_FAIL);
        }
    }

    /* ֪ͨMM�����ͷ����TI��ص�LCSʵ����Ϣ */
    NAS_LCS_JudgeSndMmRelReq(ulIndex);

    /* �ͷ�LCSʵ�� */
    NAS_LCS_ClearSingleLcsEntity(ulIndex, enCause);
}

/*****************************************************************************
Function Name  : NAS_LCS_QueryMolrEntity
Discription    : ͨ��TI����MO-LRʵ��
Input          : ulTi------------------TI
Output         : pulIndex--------------ʵ������ָ��
Return         : VOS_UINT32
History:
1.lihong 00150010 2015-9-29 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LCS_QueryMolrEntity
(
    VOS_UINT32                          ulTi,
    VOS_UINT32                         *pulIndex
)
{
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity = NAS_LCS_NULL_PTR;

    pstLcsEntity = NAS_LCS_GetLcsEntity(NAS_LCS_MO_LR_LPP_INDEX);
    if ((NAS_LCS_ENTITY_USED == pstLcsEntity->enUsedFlag) && (ulTi == pstLcsEntity->ucTi))
    {
        *pulIndex = NAS_LCS_MO_LR_LPP_INDEX;
        return NAS_LCS_SUCC;
    }

    pstLcsEntity = NAS_LCS_GetLcsEntity(NAS_LCS_MO_LR_TAF_INDEX);
    if ((NAS_LCS_ENTITY_USED == pstLcsEntity->enUsedFlag) && (ulTi == pstLcsEntity->ucTi))
    {
        *pulIndex = NAS_LCS_MO_LR_TAF_INDEX;
        return NAS_LCS_SUCC;
    }

    return NAS_LCS_FAIL;
}

/*****************************************************************************
Function Name  : NAS_LCS_QueryMtLrEntity
Discription    : ͨ��TI����MT-LRʵ��
Input          : ucHandleId------------Handle id
Output         : pulIndex--------------ʵ������ָ��
Return         : VOS_UINT32
History:
1.lihong 00150010 2015-10-10 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LCS_QueryMtLrEntity
(
    VOS_UINT8                           ucHandleId,
    VOS_UINT32                         *pulIndex
)
{
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity    = NAS_LCS_NULL_PTR;
    VOS_UINT32                          i               = 0;

    for (i = NAS_LCS_MT_LR_ENTITY_INDEX_BEGIN; i <= NAS_LCS_MT_LR_ENTITY_INDEX_END; i++)
    {
        pstLcsEntity = NAS_LCS_GetLcsEntity(i);
        if ((NAS_LCS_ENTITY_USED == pstLcsEntity->enUsedFlag) && (ucHandleId == pstLcsEntity->ucHandleId))
        {
            *pulIndex = i;
            return NAS_LCS_SUCC;
        }
    }

    return NAS_LCS_FAIL;
}

/*****************************************************************************
Function Name  : NAS_LCS_QueryLcsEntity
Discription    : ͨ��TI����LCSʵ��
Input          : ulTi------------------TI
Output         : pulIndex--------------ʵ������ָ��
Return         : VOS_UINT32
History:
1.lihong 00150010 2015-10-09 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LCS_QueryLcsEntity
(
    VOS_UINT32                          ulTi,
    VOS_UINT32                         *pulIndex
)
{
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity    = NAS_LCS_NULL_PTR;
    VOS_UINT32                          i               = 0;

    pstLcsEntity = NAS_LCS_GetLcsEntity(NAS_LCS_MO_LR_LPP_INDEX);
    if ((NAS_LCS_ENTITY_USED == pstLcsEntity->enUsedFlag) && (ulTi == pstLcsEntity->ucTi))
    {
        *pulIndex = NAS_LCS_MO_LR_LPP_INDEX;
        return NAS_LCS_SUCC;
    }

    pstLcsEntity = NAS_LCS_GetLcsEntity(NAS_LCS_MO_LR_TAF_INDEX);
    if ((NAS_LCS_ENTITY_USED == pstLcsEntity->enUsedFlag) && (ulTi == pstLcsEntity->ucTi))
    {
        *pulIndex = NAS_LCS_MO_LR_TAF_INDEX;
        return NAS_LCS_SUCC;
    }

    for (i = NAS_LCS_MT_LR_ENTITY_INDEX_BEGIN; i <= NAS_LCS_MT_LR_ENTITY_INDEX_END; i++)
    {
        pstLcsEntity = NAS_LCS_GetLcsEntity(i);
        if ((NAS_LCS_ENTITY_USED == pstLcsEntity->enUsedFlag) && (ulTi == pstLcsEntity->ucTi))
        {
            *pulIndex = i;
            return NAS_LCS_SUCC;
        }
    }

    return NAS_LCS_FAIL;
}

/*****************************************************************************
Function Name  : NAS_LCS_ReadLcsNvCommonConfig
Discription    : ��ȡLCS����NV����
Input          : None
Output         : None
Return         : None
History:
1.lihong 00150010 2015-10-12 Draft Enact
*****************************************************************************/
VOS_VOID  NAS_LCS_ReadLcsNvCommonConfig( VOS_VOID)
{
    VOS_UINT32                          ulRslt              = 0;
    LNAS_LCS_NV_COMMON_CONFIG_STRU      stLcsNvCommonConfig;
    NAS_LCS_COMM_NV_PARA_STRU          *pstCommNvPara       = NAS_LCS_NULL_PTR;

    NAS_LCS_NORM_LOG("NAS_LCS_ReadLcsNvCommonConfig enter.");
    TLPS_PRINT2LAYER_INFO(NAS_LCS_ReadLcsNvCommonConfig_ENUM, LNAS_ENTRY);

    pstCommNvPara = NAS_LCS_GetCommNvPara();

    ulRslt = NAS_LCS_ReadNv(EN_NV_ID_LCS_COMMON_CONFIG, &stLcsNvCommonConfig,\
                                sizeof(LNAS_LCS_NV_COMMON_CONFIG_STRU));

    if(ulRslt == VOS_OK)
    {
        /*����NV��������*/
        pstCommNvPara->bitOpPeriodicRptTimes    = stLcsNvCommonConfig.stLcsFeatureBit.bitOpPeriodicRptTimes;
        pstCommNvPara->ucMaxRetryTimes          = stLcsNvCommonConfig.ucMaxRetryTimes;
        pstCommNvPara->usPeriodicRptTimes       = stLcsNvCommonConfig.usPeriodicRptTimes;
        pstCommNvPara->usRetryTimerLen          = stLcsNvCommonConfig.usRetryTimerLen;
    }
    else
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ReadLcsNvCommonConfig, Read NV Err.");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_ReadLcsNvCommonConfig_ENUM, LNAS_LCS_ReadNvCommonConfigFail);

        pstCommNvPara->bitOpPeriodicRptTimes    = NAS_LCS_OP_FALSE;
        pstCommNvPara->ucMaxRetryTimes          = 2;
        pstCommNvPara->usPeriodicRptTimes       = 0;
        pstCommNvPara->usRetryTimerLen          = 2;
    }

    return;
}


/*****************************************************************************
Function Name  : NAS_LCS_GetLcsEntityNum
Description    : ��ȡLCSʵ�����
Input          : None
Output         : None
Return Value   : VOS_UINT32

History        :
lihong 00150010 2015-10-10  �¿���
*****************************************************************************/
VOS_UINT32  NAS_LCS_GetLcsEntityNum( VOS_VOID )
{
    NAS_LCS_ENTITY_INFO_STRU           *pstLcsEntity    = NAS_LCS_NULL_PTR;
    VOS_UINT32                          i               = 0;
    VOS_UINT32                          ulEntityNum     = 0;

    for (i = NAS_LCS_MO_LR_LPP_INDEX; i <= NAS_LCS_MT_LR_ENTITY_INDEX_END; i++)
    {
        pstLcsEntity = NAS_LCS_GetLcsEntity(i);
        if (NAS_LCS_ENTITY_USED == pstLcsEntity->enUsedFlag)
        {
            ulEntityNum++;
        }
    }

    return ulEntityNum;
}

/*****************************************************************************
Function Name  : NAS_LCS_SetEntityState
Description    : ����ʵ��״̬
Input          : ulIndex-------------ʵ������
                 enEntityState-------ʵ��״̬
Output         : None
Return Value   : VOS_UINT32

History        :
lihong 00150010 2015-10-10  �¿���
*****************************************************************************/
VOS_VOID NAS_LCS_SetEntityState
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_ENTITY_STATE_ENUM_UINT8     enEntityState
)
{
    NAS_LCS_SndOmEntityStateInfo(ulIndex, NAS_LCS_GetEntityState(ulIndex), enEntityState);

    NAS_LCS_GetEntityState(ulIndex) = enEntityState;
}

/*****************************************************************************
Function Name  : NAS_LCS_SetEntityConnState
Description    : ����ʵ������״̬
Input          : ulIndex-------------ʵ������
                 enEntityState-------ʵ��״̬
Output         : None
Return Value   : VOS_UINT32

History        :
lihong 00150010 2015-10-10  �¿���
*****************************************************************************/
VOS_VOID NAS_LCS_SetEntityConnState
(
    VOS_UINT32                          ulIndex,
    NAS_LCS_CONN_STATE_ENUM_UINT8       enConnState
)
{
    NAS_LCS_SndOmEntityConnStateInfo(ulIndex, NAS_LCS_GetEntityConnState(ulIndex), enConnState);

    NAS_LCS_GetEntityConnState(ulIndex) = enConnState;
}


/*****************************************************************************
Function Name  : NAS_LCS_ProcMolrConnAbnormal
Description    : ����MOLR������·�쳣
Input          : ulIndex-------------ʵ������
                 enTafLcsCause-------ԭ��ֵ
Output         : None
Return Value   : VOS_VOID

History        :
lihong 00150010 2015-10-10  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_ProcMolrConnAbnormal
(
    VOS_UINT32                          ulIndex,
    TAF_LCS_CAUSE_ENUM_UINT32           enTafLcsCause
)
{
    /* ���Դ�����1 */
    NAS_LCS_AddEntityEstRetryTimers(ulIndex);

    /* ������Դ����Ѵ���������������ܻ��������򣬷����ͷ�ʵ����Ϣ */
    if (NAS_LCS_GetEntityEstRetryTimers(ulIndex) >= NAS_LCS_GetNvMaxRetryTimes())
    {
        /* ����������Եģ�����Ϊ���ν����������Ի��� */
        if ((NAS_LCS_MO_LR_TAF_INDEX == ulIndex) && (LCS_REP_MODE_PERIODIC_RPT == NAS_LCS_GetMolrMode()))
        {
            /* ���ý������Դ��� */
            NAS_LCS_ResetEntityEstRetryTimers(ulIndex);

            /* ������MO-LR����ʧ�ܴ��� */
            NAS_LCS_ProcPeriodMolrOnceAbnormalEnd(ulIndex, enTafLcsCause);
        }
        else
        {
            /* ���Ի��� */
            NAS_LCS_TryToChangeDomain(ulIndex, enTafLcsCause);
        }

        return ;
    }

    /* ��������״̬ΪIDLE̬ */
    NAS_LCS_SetEntityConnState(ulIndex, NAS_LCS_CONN_STATE_IDLE);

    /* �����ȴ��ؽ���ʱ��������ʱ����ʱ���ٷ��� */
    NAS_LCS_StartTimer(ulIndex, TI_NAS_LCS_WATI_REEST_TIMER);
}


/*****************************************************************************
Function Name  : NAS_LCS_GetPeriodicRptTimesSwtich
Description    : ��ȡ�������ϱ��������Կ���
Input          : pstCnMsgStru----------��������ݽṹָ��
Output         : None
Return Value   : VOS_VOID

History        :
lihong 00150010 2015-10-08  �¿���
*****************************************************************************/
VOS_UINT32  NAS_LCS_GetPeriodicRptTimesSwtich( VOS_VOID )
{
    NAS_LCS_COMM_NV_PARA_STRU          *pstCommNvPara = NAS_LCS_NULL_PTR;

    pstCommNvPara = NAS_LCS_GetCommNvPara();
    if (NAS_LCS_OP_TRUE == pstCommNvPara->bitOpPeriodicRptTimes)
    {
        return PS_TRUE;
    }

    return PS_FALSE;
}

/*****************************************************************************
Function Name  : NAS_LCS_ProcPeriodMolrOnceNormalEnd
Description    : ����������MOLR������������
Input          : ulIndex-------------------------ʵ������
Output         : None
Return Value   : VOS_VOID

History        :
lihong 00150010 2015-10-09  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_ProcPeriodMolrOnceNormalEnd
(
    VOS_UINT32                          ulIndex
)
{
    /* �ж������Լ��������Թ����Ƿ�� */
    if (PS_FALSE == NAS_LCS_GetPeriodicRptTimesSwtich())
    {
        /* ״̬ת�����ڼ�� */
        NAS_LCS_SetEntityState(ulIndex, NAS_LCS_ENTITY_STATE_PERIOD_INTERVAL);

        /* �������ڼ����ʱ�� */
        NAS_LCS_StartTimer(ulIndex, TI_NAS_LCS_PERIOD_INTERVAL_TIMER);

        return ;
    }

    /* ���ڳ��Դ�����1 */
    NAS_LCS_AddEntityPediodRetryTimers(ulIndex);

    /* ������Դ�����δ�ﵽ������ */
    if (NAS_LCS_GetEntityPediodRetryTimers(ulIndex) < NAS_LCS_GetNvMaxPeriodicRptTimes())
    {
        /* ״̬ת�����ڼ�� */
        NAS_LCS_SetEntityState(ulIndex, NAS_LCS_ENTITY_STATE_PERIOD_INTERVAL);

        /* �������ڼ����ʱ�� */
        NAS_LCS_StartTimer(ulIndex, TI_NAS_LCS_PERIOD_INTERVAL_TIMER);

        return ;
    }

    /* ����RELEASE COMPLTE���������� */
    NAS_LCS_SndReleaseComplte(ulIndex);

    /* ֪ͨMM�����ͷ����TI��ص�LCSʵ����Ϣ */
    NAS_LCS_JudgeSndMmRelReq(ulIndex);

    /* �ͷ�LCSʵ�� */
    NAS_LCS_ClearSingleLcsEntity(ulIndex, TAF_LCS_CAUSE_SUCCESS);
}

/*****************************************************************************
Function Name  : NAS_LCS_ProcPeriodMolrOnceAbnormalEnd
Description    : ����������MOLR�����쳣����
Input          : ulIndex-------------------------ʵ������
                 enCause-------------------------�쳣ԭ��
Output         : None
Return Value   : VOS_VOID

History        :
lihong 00150010 2015-10-09  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_ProcPeriodMolrOnceAbnormalEnd
(
    VOS_UINT32                          ulIndex,
    TAF_LCS_CAUSE_ENUM_UINT32           enCause
)
{

    NAS_LCS_StopTimer(ulIndex, NAS_LCS_ENTITY_STATE_WAIT_NW_RSP);

    /* �ж������Լ��������Թ����Ƿ�� */
    if (PS_FALSE == NAS_LCS_GetPeriodicRptTimesSwtich())
    {
        /* ״̬ת�����ڼ�� */
        NAS_LCS_SetEntityState(ulIndex, NAS_LCS_ENTITY_STATE_PERIOD_INTERVAL);

        /* �������ڼ����ʱ�� */
        NAS_LCS_StartTimer(ulIndex, TI_NAS_LCS_PERIOD_INTERVAL_TIMER);

        /* ͨ��LCS_TAF_FACILITY_IND��֪TAF����MO-LR���� */
        NAS_LCS_SndTafFacilityInd(NAS_LCS_NULL_PTR, NAS_LCS_NULL_PTR, enCause);

        return ;
    }

    /* ���ڳ��Դ�����1 */
    NAS_LCS_AddEntityPediodRetryTimers(ulIndex);

    /* ������Դ�����δ�ﵽ������ */
    if (NAS_LCS_GetEntityPediodRetryTimers(ulIndex) < NAS_LCS_GetNvMaxPeriodicRptTimes())
    {
        /* ״̬ת�����ڼ�� */
        NAS_LCS_SetEntityState(ulIndex, NAS_LCS_ENTITY_STATE_PERIOD_INTERVAL);

        /* �������ڼ����ʱ�� */
        NAS_LCS_StartTimer(ulIndex, TI_NAS_LCS_PERIOD_INTERVAL_TIMER);

        /* ͨ��LCS_TAF_FACILITY_IND��֪TAF����MO-LR���� */
        NAS_LCS_SndTafFacilityInd(NAS_LCS_NULL_PTR, NAS_LCS_NULL_PTR, enCause);

        return ;
    }

    /* ֪ͨMM�����ͷ����TI��ص�LCSʵ����Ϣ */
    NAS_LCS_JudgeSndMmRelReq(ulIndex);

    /* �ͷ�LCSʵ�� */
    NAS_LCS_ClearSingleLcsEntity(ulIndex, enCause);
}


/*****************************************************************************
Function Name  : NAS_LCS_ProcAirMsgFacility
Description    : ����տ���ϢFICILITY
Input          : pstCnMsgStru----------��������ݽṹָ��
Output         : None
Return Value   : VOS_VOID

History        :
lihong 00150010 2015-10-08  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_ProcAirMsgFacility
(
    NAS_LCS_CN_MSG_STRU                *pstCnMsgStru
)
{
    VOS_UINT32                          ulRslt              = 0;
    VOS_UINT32                          ulIndex             = 0;
    LOC_COM_COORDINATE_STRU            *pstLocationEstimate = NAS_LCS_NULL_PTR;
    LOC_COM_VELOCITY_STRU              *pstVelocityEstimate = NAS_LCS_NULL_PTR;

    /* ͨ��TI���ҹ���ʵ�� */
    ulRslt = NAS_LCS_QueryMolrEntity(pstCnMsgStru->ucTi, &ulIndex);
    if (NAS_LCS_FAIL == ulRslt)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ProcAirMsgFacility:query entity fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_ProcAirMsgFacility_ENUM, LNAS_LCS_QueryEntityFail);
        NAS_LCS_SndOmEntityInfo();
        return ;
    }

    /* �ж�ʵ��״̬�Ƿ�Ϊ�ȴ�������Ӧ�������ǣ���ֱ�ӷ��� */
    if (NAS_LCS_ENTITY_STATE_WAIT_NW_RSP != NAS_LCS_GetEntityState(ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ProcAirMsgFacility:entity state invalid!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_ProcAirMsgFacility_ENUM, LNAS_LCS_EntityStateInvalid);
        return ;
    }

    /* ֹͣ�ȴ�������Ӧ��ʱ�� */
    NAS_LCS_StopTimer(ulIndex, TI_NAS_LCS_WAIT_NW_RSP_TIMER);

    /* �����LPP������MO-LR�����LPP�ظ��ɹ����ͷ�LCSʵ�� */
    if (NAS_LCS_MO_LR_LPP_INDEX == ulIndex)
    {
        /* ֪ͨLPP��ȡ������Ϣ�ɹ� */
        NAS_LCS_SndLppGnssAssistDataCnf(LCS_LPP_RSLT_SUCC);

        /* ����RELEASE COMPLTE���������� */
        NAS_LCS_SndReleaseComplte(ulIndex);

        /* �ͷ�LCSʵ�� */
        NAS_LCS_ClearSingleLcsEntity(NAS_LCS_MO_LR_LPP_INDEX, TAF_LCS_CAUSE_SUCCESS);

        return ;
    }

    /*�����TAF������MOLR����*/
    if (NAS_LCS_MO_LR_TAF_INDEX == ulIndex)
    {
        /* ��TAF���Ͷ�λ��� */
        if (NAS_LCS_OP_TRUE ==  pstCnMsgStru->stMolrResult.bitOpLocationEstimate)
        {
            pstLocationEstimate = &pstCnMsgStru->stMolrResult.stLocationEstimate;
        }

        if (NAS_LCS_OP_TRUE ==  pstCnMsgStru->stMolrResult.bitOpVelocityEstimate)
        {
            pstVelocityEstimate = &pstCnMsgStru->stMolrResult.stVelocityEstimate;
        }

        NAS_LCS_SndTafFacilityInd(pstLocationEstimate, pstVelocityEstimate, TAF_LCS_CAUSE_SUCCESS);

        /* ��ѡ����ΪEPC LCSʱ��Ҫ֪ͨLPPλ����Ϣ */
        if (NAS_LCS_DOMAIN_TYPE_EPC_LCS == NAS_LCS_GetEntityLcsDomain(ulIndex))
        {
            /* ��LPP����λ����Ϣ */
            NAS_LCS_SndLppLocationInfoNtf(pstLocationEstimate, pstVelocityEstimate);
        }

        /* �����ǵ��λ����������ͣ��ֱ��� */
        if (LCS_REP_MODE_SINGLE_RPT == NAS_LCS_GetMolrMode())
        {
            /* ����RELEASE COMPLTE���������� */
            NAS_LCS_SndReleaseComplte(ulIndex);

            /* ֪ͨMM�����ͷ����TI��ص�LCSʵ����Ϣ */
            NAS_LCS_JudgeSndMmRelReq(ulIndex);

            /* �ͷ�LCSʵ�� */
            NAS_LCS_ClearSingleLcsEntity(ulIndex, TAF_LCS_CAUSE_SUCCESS);

            return ;
        }
        else
        {
            /* ����������MOLR���ν��� */
            NAS_LCS_ProcPeriodMolrOnceNormalEnd(ulIndex);

            return ;
        }
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_ProcAirMsgReleaseComplete
Description    : ����տ���ϢRELEASE COMPLTE
Input          : pstCnMsgStru----------��������ݽṹָ��
Output         : None
Return Value   : VOS_VOID

History        :
lihong 00150010 2015-10-09  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_ProcAirMsgReleaseComplete
(
    NAS_LCS_CN_MSG_STRU                *pstCnMsgStru
)
{
    VOS_UINT32                          ulRslt  = 0;
    VOS_UINT32                          ulIndex = 0;

    /* ͨ��TI���ҹ���ʵ�� */
    ulRslt = NAS_LCS_QueryLcsEntity(pstCnMsgStru->ucTi, &ulIndex);
    if (NAS_LCS_FAIL == ulRslt)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ProcAirMsgReleaseComplete:query entity fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_ProcAirMsgReleaseComplete_ENUM, LNAS_LCS_QueryEntityFail);
        NAS_LCS_SndOmEntityInfo();
        return ;
    }

    /* ֹͣ���ж�ʱ�� */
    NAS_LCS_StopAllTimer(ulIndex);

    /* �ͷŵ���LCSʵ�岢֪ͨ������ */
    if (NAS_LCS_OP_TRUE == pstCnMsgStru->bitOpNwCause)
    {
        NAS_LCS_ClearLcsEntityAndNotify(ulIndex, pstCnMsgStru->enNwCause + TAF_LCS_CAUSE_NW_SECTION_BEGIN);
    }
    else
    {
        NAS_LCS_ClearLcsEntityAndNotify(ulIndex, TAF_LCS_CAUSE_SUCCESS);
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_ValidateAirMsgRegister
Description    : �Ϸ��Լ��տ���ϢGEGISTER
Input          : pstCnMsgStru----------��������ݽṹָ��
Output         : None
Return Value   : VOS_UINT32

History        :
lihong 00150010 2015-10-10  �¿���
*****************************************************************************/
VOS_UINT32  NAS_LCS_ValidateAirMsgRegister
(
    NAS_LCS_CN_MSG_STRU                *pstCnMsgStru
)
{
    /* �ж�OPERATION CODE�Ƿ�Ϸ� */
    if ((NAS_LCS_OP_FALSE == pstCnMsgStru->bitOperationCode)
        || (NAS_LCS_OPERATION_LOC_NOTIFICATION != pstCnMsgStru->ucOperationCode))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ValidateAirMsgRegister:operation code is invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_ValidateAirMsgRegister_ENUM, LNAS_LCS_InvalidOperationCode);

        return NAS_LCS_FAIL;
    }

    /* ���û��locationNotification����operation codeΪ116���򷵻�ʧ�� */
    if (NAS_LCS_OP_FALSE == pstCnMsgStru->bitOpLocNotification)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ValidateAirMsgRegister:LocationNotification not exist");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_ValidateAirMsgRegister_ENUM, LNAS_LCS_LocationNotificationNotExist);

        return NAS_LCS_FAIL;
    }

    /* ���Ϊlocation not allowed���򷵻�ʧ�� */
    if (NAS_LCS_NOTIFY_TYPE_LOC_NOT_ALLOWED == pstCnMsgStru->stLocNotication.enNtfType)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ValidateAirMsgRegister:LocationNotAllowed");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_ValidateAirMsgRegister_ENUM, LNAS_LCS_LocationNotAllowed);

        return NAS_LCS_FAIL;
    }

    /* ���Ϊlocation not allowed���򷵻�ʧ�� */
    if ((NAS_LCS_LOCATION_TYPE_ACT_DEFER_LOC == pstCnMsgStru->stLocNotication.stLocationType.enLocType)
        || (NAS_LCS_LOCATION_TYPE_CANCEL_DEFER_LOC == pstCnMsgStru->stLocNotication.stLocationType.enLocType))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ValidateAirMsgRegister:enLocType Invalid");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_ValidateAirMsgRegister_ENUM, LNAS_LCS_InvalidLocType);

        return NAS_LCS_FAIL;
    }

    return NAS_LCS_SUCC;
}

/*****************************************************************************
Function Name  : NAS_LCS_ProcAirMsgRegister
Description    : ����տ���ϢGEGISTER
Input          : pstCnMsgStru----------��������ݽṹָ��
                 enLcsDomainType-------LCS��
Output         : None
Return Value   : VOS_VOID

History        :
lihong 00150010 2015-10-10  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_ProcAirMsgRegister
(
    NAS_LCS_CN_MSG_STRU                *pstCnMsgStru,
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enLcsDomainType
)
{
    VOS_UINT32                          ulIndex             = 0;
    VOS_UINT8                           ucHandleId          = 0;
    NAS_LCS_NW_MSG_RECORD_STRU         *pstLcsNwMsgRecord   = NAS_LCS_NULL_PTR;

    /* �жϵ�ǰפ�����뼼���Ƿ�֧��LCS */
    if (PS_FALSE == NAS_LCS_IsCurrRatSupportLcs())
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ProcAirMsgRegister:Curr Rat Not Support Lcs!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_ProcAirMsgRegister_ENUM, LNAS_LCS_NotSupportLcs);
        return;
    }

    /* ��Ϣ�Ϸ��Լ�� */
    if (NAS_LCS_FAIL == NAS_LCS_ValidateAirMsgRegister(pstCnMsgStru))
    {
        /* ����RELEASE COMPLTE��Ϣ�������� */
        NAS_LCS_SndMtlrFailReleaseComplte(  pstCnMsgStru->ucTi,
                                            pstCnMsgStru->ucInvokeId,
                                            enLcsDomainType,
                                            NAS_LCS_CAUSE_NW_ERR_UNEXPECT_DATA_VALUE);
        return ;
    }

    /* �������ഥ����MT-LRʵ�壬�������ʧ�ܣ���ֱ�Ӹ�����ظ�RELEASE COMPLTE */
    if (NAS_LCS_FAIL == NAS_LCS_CreateLcsEntity(    NAS_LCS_START_SOURCE_NW,
                                                    &ulIndex))
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ProcAirMsgRegister:create entity fail!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_ProcAirMsgRegister_ENUM, LNAS_LCS_CreateEntityFail);
        NAS_LCS_SndOmEntityInfo();

        /* ����RELEASE COMPLTE��Ϣ�������� */
        NAS_LCS_SndMtlrFailReleaseComplte(  pstCnMsgStru->ucTi,
                                            pstCnMsgStru->ucInvokeId,
                                            enLcsDomainType,
                                            NAS_LCS_NW_CAUSE_BUTT);

        return ;
    }

    /* �洢MT-LRʵ����Ϣ */
    pstLcsNwMsgRecord = NAS_LCS_GetEntityNwMsgRecord(ulIndex);
    pstLcsNwMsgRecord->enNotificationType = pstCnMsgStru->stLocNotication.enNtfType;

    /* �洢Invoke Id */
    NAS_LCS_SetEntityInvokeId(ulIndex, pstCnMsgStru->ucInvokeId);

    /* ��¼ʵ������ϢΪѡ����� */
    NAS_LCS_SetEntityLcsDomain(ulIndex, enLcsDomainType);

    /* �洢TI */
    NAS_LCS_SetEntityTi(ulIndex, pstCnMsgStru->ucTi);

    /* �����ȴ��û���Ӧ��ʱ�� */
    NAS_LCS_StartTimer(ulIndex, TI_NAS_LCS_WAIT_UE_RSP_TIMER);

    /* ��ȡ��ʵ�崴��ʱ���ֵ�HAND ID, ����TAF */
    ucHandleId = NAS_LCS_GetEntityHandleId(ulIndex);

    /* ��TAF��LCS_TAF_BEGIN_IND */
    NAS_LCS_SndTafBeginInd(&pstCnMsgStru->stLocNotication, ucHandleId);

    /* ����ʵ������״̬Ϊ���������� */
    NAS_LCS_SetEntityConnState(ulIndex, NAS_LCS_CONN_STATE_CONN);
}

/*****************************************************************************
Function Name  : NAS_LCS_SndDecodeFailRelComplete
Description    : �տ�����ʧ��,�ظ�����RelComplete
Input          : enCause---------------�ظ�����ԭ��ֵ
Output         : pstCnMsgStru----------��������ݽṹָ��
Return Value   : VOS_VOID

History        :
leixiantiao 00258641 2015-10-08  �¿���
*****************************************************************************/
VOS_VOID NAS_LCS_SndDecodeFailRelComplete
(
    NAS_LCS_NW_CAUSE_ENUM_UINT32        enCause,
    NAS_LCS_CN_MSG_STRU                *pstCnMsgStru,
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enLcsDomainType
)
{
    NAS_LCS_ENCODE_INFO_STRU            stEncodeInfo;
    NAS_LCS_ENCODE_BUFFER_STRU         *pstEncodeBuffer = NAS_LCS_NULL_PTR;

    NAS_LCS_MEM_SET_S(  &stEncodeInfo,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU),
                        0,
                        sizeof(NAS_LCS_ENCODE_INFO_STRU));

    /* ��д�տ�TIֵԭ��ֵ�Լ�InvokeId */
    if (NAS_LCS_TI_OFFSET > pstCnMsgStru->ucTi)
    {
        stEncodeInfo.ucTi   = pstCnMsgStru->ucTi + NAS_LCS_TI_OFFSET;
    }
    else
    {
        stEncodeInfo.ucTi   = pstCnMsgStru->ucTi - NAS_LCS_TI_OFFSET;
    }

    stEncodeInfo.bitOpCause = NAS_LCS_OP_TRUE;
    stEncodeInfo.enCause    = enCause;
    if (NAS_LCS_OP_TRUE == pstCnMsgStru->bitOpInvokeId)
    {
        stEncodeInfo.bitOpInvokeId = NAS_LCS_OP_TRUE;
        stEncodeInfo.ucInvokeId    = pstCnMsgStru->ucInvokeId;
    }

    pstEncodeBuffer             = NAS_LCS_GetEncodeBuffer();

    /* ����RELEASE COMPLETE */
    if (NAS_LCS_CAUSE_SUCCESS == NAS_LCS_EncodeRelComplete( pstEncodeBuffer->aucBuffer,
                                                            &pstEncodeBuffer->ulBufferLen,
                                                            &stEncodeInfo))
    {
        NAS_LCS_SndAirMsgReportInd( pstEncodeBuffer->aucBuffer,
                                    pstEncodeBuffer->ulBufferLen,
                                    NAS_LCS_AIR_MSG_DIR_ENUM_UP,
                                    LCS_RELEASE_COMPLTE);

        /* ���������ڵ��򷢸���Ӧģ�� */
        if (NAS_LCS_DOMAIN_TYPE_CS_LCS == enLcsDomainType)
        {
            NAS_LCS_SndMmDataReq(   pstCnMsgStru->ucTi,
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
        else
        {
            NAS_LCS_SndLmmDataReq(  pstCnMsgStru->ucTi,
                                    pstEncodeBuffer->ulBufferLen,
                                    pstEncodeBuffer->aucBuffer);
        }
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_ProcNwMsgDecodeFail
Description    : ����տ�����ʧ��
Input          : enRslt----------------�տ�������
Output         : pstCnMsgStru----------��������ݽṹָ��
Return Value   : VOS_VOID

History        :
leixiantiao 00258641 2015-10-08  �¿���
*****************************************************************************/
VOS_VOID NAS_LCS_ProcNwMsgDecodeFail
(
    NAS_LCS_CAUSE_ENUM_UINT32           enRslt,
    NAS_LCS_CN_MSG_STRU                *pstCnMsgStru,
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enLcsDomainType
)
{
    NAS_LCS_NW_CAUSE_ENUM_UINT32        enNwCause;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulIndex;

    /* ����ͨʧ�ܲ���Ҫ����,ֱ�Ӷ��� */
    if (NAS_LCS_CAUSE_FAIL == enRslt)
    {
        return;
    }
    else
    {
        /* ֻ�������Facility��Register��Ϣ����ʧ����Ҫ���� */
        if ((NAS_LCS_CN_MSG_FACILITY == pstCnMsgStru->enCnMsgType)
            || (NAS_LCS_CN_MSG_REGISTER == pstCnMsgStru->enCnMsgType))
        {
            switch(enRslt)
            {
                case NAS_LCS_CAUSE_UNRECOGNIZED_COMPONENT:
                    enNwCause = NAS_LCS_NW_CAUSE_UNRECOGNIZED_COMPONENT;
                    break;

                case NAS_LCS_CAUSE_MISTYPED_PARAMETER:
                    if (NAS_LCS_CN_MSG_FACILITY == pstCnMsgStru->enCnMsgType)
                    {
                        enNwCause = NAS_LCS_NW_CAUSE_RETURN_RSLT_MISTYPED_PARAMETER;
                    }
                    else
                    {
                        enNwCause = NAS_LCS_NW_CAUSE_INVOKE_MISTYPED_PARAMETER;
                    }
                    break;

                default:
                    enNwCause = NAS_LCS_CAUSE_NW_ERR_UNEXPECT_DATA_VALUE;
                    break;
            }

            /* �ظ�����Rel Cmp */
            NAS_LCS_SndDecodeFailRelComplete(enNwCause, pstCnMsgStru, enLcsDomainType);
        }

        /* ͨ��TI���ҹ���ʵ�� */
        ulRslt = NAS_LCS_QueryLcsEntity(pstCnMsgStru->ucTi, &ulIndex);
        if (NAS_LCS_FAIL == ulRslt)
        {
            return;
        }

        /* �����ڵ�ǰʵ��, ����Ҫ�ͷŵ���LCSʵ�岢֪ͨ������ */
        NAS_LCS_ClearLcsEntityAndNotify(ulIndex, TAF_LCS_CAUSE_OTHERS);
    }
    return;
}

/*****************************************************************************
Function Name  : NAS_LCS_SndDownAirMsgReportInd
Description    : ��LCS���пտ�
Input          : pucMsg----------------�տ���Ϣָ��
                 ulLen-----------------�տ���Ϣ����
                 enCnMsgType-----------�տ�����
Output         : NONE
Return Value   : VOS_VOID

History        :
lihong 00150010 2015-10-08  �¿���
*****************************************************************************/
VOS_VOID NAS_LCS_SndDownAirMsgReportInd
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                          ulLen,
    NAS_LCS_CN_MSG_TYPE_ENUM_UINT32     enCnMsgType

)
{

    OM_PS_AIR_MSG_ENUM_UINT8            enMsgId;

    if (NAS_LCS_CN_MSG_REL_CML == enCnMsgType)
    {
        enMsgId = LCS_RELEASE_COMPLTE;
    }
    else if (NAS_LCS_CN_MSG_FACILITY == enCnMsgType)
    {
        enMsgId = LCS_FACILITY;
    }
    else if (NAS_LCS_CN_MSG_REGISTER == enCnMsgType)
    {
        enMsgId = LCS_REGISTER;
    }
    else
    {
        TLPS_PRINT2LAYER_ERROR1(NAS_LCS_SndDownAirMsgReportInd_ENUM, LNAS_LCS_MsgTypeInvalid, enCnMsgType);
        NAS_LCS_ERR_LOG1("NAS_LCS_SndDownAirMsgReportInd CnMsgType Error ", enCnMsgType);
        return;
    }

    /* �׳��տڿ�ά�ɲ� */
    NAS_LCS_SndAirMsgReportInd( pucMsg,
                                ulLen,
                                NAS_LCS_AIR_MSG_DIR_ENUM_DOWN,
                                enMsgId);
}
/*****************************************************************************
Function Name  : NAS_LCS_ProcAirMsg
Description    : ����տ���Ϣ
Input          : pucMsg----------------�տ���Ϣָ��
                 ulLen-----------------�տ���Ϣ����
                 enLcsDomainType-------LCS��
Output         : pstCnMsgStru----------��������ݽṹָ��
Return Value   : VOS_VOID

History        :
lihong 00150010 2015-10-08  �¿���
*****************************************************************************/
VOS_VOID  NAS_LCS_ProcAirMsg
(
    VOS_UINT8                          *pucMsg,
    VOS_UINT32                          ulLen,
    NAS_LCS_CN_MSG_STRU                *pstCnMsgStru,
    NAS_LCS_DOMAIN_TYPE_ENUM_UINT8      enLcsDomainType
)
{
    VOS_UINT32                          ulRslt      = 0;
    VOS_UINT32                          ulLenTmp    = ulLen;

    NAS_LCS_MEM_SET_S(  pstCnMsgStru,
                        sizeof(NAS_LCS_CN_MSG_STRU),
                        0,
                        sizeof(NAS_LCS_CN_MSG_STRU));

    /* �������� */
    ulRslt = NAS_LCS_DecodeCnMsg(   pucMsg,
                                    &ulLenTmp,
                                    pstCnMsgStru);

    /* �����տ���Ϣ */
    NAS_LCS_SndDownAirMsgReportInd(pucMsg, ulLen, pstCnMsgStru->enCnMsgType);

    /* ����ʧ�ܣ�������Ϣ������ */
    if (NAS_LCS_CAUSE_SUCCESS != ulRslt)
    {
        NAS_LCS_WARN_LOG("NAS_LCS_ProcAirMsg,Decode fail");
        TLPS_PRINT2LAYER_WARNING(NAS_LCS_ProcAirMsg_ENUM, LNAS_LCS_DecodeFail);
        NAS_LCS_ProcNwMsgDecodeFail(ulRslt, pstCnMsgStru, enLcsDomainType);
        return ;
    }

    /* �Ը��տ���Ϣ���зֱ��� */
    switch (pstCnMsgStru->enCnMsgType)
    {
        case NAS_LCS_CN_MSG_REL_CML:
            NAS_LCS_ProcAirMsgReleaseComplete(pstCnMsgStru);
            break;

        case NAS_LCS_CN_MSG_FACILITY:
            NAS_LCS_ProcAirMsgFacility(pstCnMsgStru);
            break;

        case NAS_LCS_CN_MSG_REGISTER:
            NAS_LCS_ProcAirMsgRegister(pstCnMsgStru, enLcsDomainType);
            break;

        default:
            NAS_LCS_WARN_LOG("NAS_LCS_ProcAirMsg,Invalid Msg");
            TLPS_PRINT2LAYER_WARNING(NAS_LCS_ProcAirMsg_ENUM, LNAS_LCS_InvalidMsg);
            break;
    }
}

/*****************************************************************************
Function Name  : NAS_LCS_LmmEstCnfCauseMap
Description    : ��LMM EST���ת��ΪTAF��LCS֮���ԭ��ֵ
Input          : enCause----------------LMM ESTԭ��ֵ
Output         : NULL
Return Value   : TAF_LCS_CAUSE_ENUM_UINT32: ת����ԭ��ֵ

History        :
leixiantiao 00258641 2015-10-08  �¿���
*****************************************************************************/
TAF_LCS_CAUSE_ENUM_UINT32 NAS_LCS_LmmEstCnfCauseMap(const LMM_LCS_EST_RESULT_ENUM_UINT32 enCause)
{
    TAF_LCS_CAUSE_ENUM_UINT32 enTafCause = TAF_LCS_CAUSE_SUCCESS;

    switch(enCause)
    {
        case LMM_LCS_EST_RSLT_SUCC:
            enTafCause = TAF_LCS_CAUSE_SUCCESS;
            break;

        case LMM_LCS_EST_RSLT_FAIL_PS_NOT_ATTACHED:
            enTafCause = TAF_LCS_CAUSE_LMM_PS_NOT_ATTACHED;
            break;

        case LMM_LCS_EST_RSLT_FAIL_PS_ATTACH_NOT_ALLOWED:
            enTafCause = TAF_LCS_CAUSE_LMM_PS_ATTACH_NOT_ALLOWED;
            break;

        case LMM_LCS_EST_RSLT_FAIL_USIM_PS_INVALID:
            enTafCause = TAF_LCS_CAUSE_LMM_USIM_PS_INVAILD;
            break;

        case LMM_LCS_EST_RSLT_FAIL_ACCESS_BARRED:
            enTafCause = TAF_LCS_CAUSE_LMM_ACCESS_BARRED;
            break;

        case LMM_LCS_EST_RSLT_FAIL_STATE_CANNOT_SERVICE:
            enTafCause = TAF_LCS_CAUSE_LMM_STATE_CANNOT_SERVICE;
            break;

        case LMM_LCS_EST_RSLT_FAIL_EPC_LCS_NOT_SUPPORT:
            enTafCause = TAF_LCS_CAUSE_LMM_EPC_LCS_NOT_SUPPORT;
            break;

        case LMM_LCS_EST_RSLT_FAIL_3411_RUNNING:
            enTafCause = TAF_LCS_CAUSE_LMM_3411_RUNNING;
            break;

        case LMM_LCS_EST_RSLT_FAIL_SERVICE_FAIL:
            enTafCause = TAF_LCS_CAUSE_LMM_SERVICE_FAIL;
            break;

        default:
            enTafCause = TAF_LCS_CAUSE_LMM_OTHERS;
            break;
    }
    return enTafCause;
}

/*****************************************************************************
Function Name  : NAS_LCS_LmmDataCnfCauseMap
Description    : ��LMM Data Cnf���ת��ΪTAF��LCS֮���ԭ��ֵ
Input          : enCause----------------LMM Data Cnfԭ��ֵ
Output         : NULL
Return Value   : TAF_LCS_CAUSE_ENUM_UINT32: ת����ԭ��ֵ

History        :
leixiantiao 00258641 2015-10-08  �¿���
*****************************************************************************/
TAF_LCS_CAUSE_ENUM_UINT32 NAS_LCS_LmmDataCnfCauseMap(const LMM_LCS_SEND_RSLT_ENUM_UINT32 enCause)
{
    TAF_LCS_CAUSE_ENUM_UINT32 enTafCause = TAF_LCS_CAUSE_SUCCESS;

    switch(enCause)
    {
        case LMM_LCS_SEND_RSLT_SUCCESS:
            enTafCause = TAF_LCS_CAUSE_SUCCESS;
            break;

        case LMM_LCS_SEND_RSLT_FAIL_PS_NOT_ATTACHED:
            enTafCause = TAF_LCS_CAUSE_LMM_PS_NOT_ATTACHED;
            break;

        case LMM_LCS_SEND_RSLT_FAIL_PS_ATTACH_NOT_ALLOWED:
            enTafCause = TAF_LCS_CAUSE_LMM_PS_ATTACH_NOT_ALLOWED;
            break;

        case LMM_LCS_SEND_RSLT_FAIL_USIM_PS_INVALID:
            enTafCause = TAF_LCS_CAUSE_LMM_USIM_PS_INVAILD;
            break;

        case LMM_LCS_SEND_RSLT_FAIL_ACCESS_BARRED:
            enTafCause = TAF_LCS_CAUSE_LMM_ACCESS_BARRED;
            break;

        case LMM_LCS_SEND_RSLT_FAIL_RRC_CONN_NOT_EXIST:
            enTafCause = TAF_LCS_CAUSE_LMM_RRC_CONN_NOT_EXIST;
            break;

        case LMM_LCS_SEND_RSLT_FAIL_EPC_LCS_NOT_SUPPORT:
            enTafCause = TAF_LCS_CAUSE_LMM_EPC_LCS_NOT_SUPPORT;
            break;

        case LMM_LCS_SEND_RSLT_RSLT_FAIL_3411_RUNNING:
            enTafCause = TAF_LCS_CAUSE_LMM_3411_RUNNING;
            break;

        case LMM_LCS_SEND_RSLT_FAIL_LOW_LAYER:
            enTafCause = TAF_LCS_CAUSE_LMM_LOW_LAYER;
            break;

        default:
            enTafCause = TAF_LCS_CAUSE_LMM_OTHERS;
            break;
    }
    return enTafCause;
}

/*****************************************************************************
Function Name  : NAS_LCS_LmmRelCauseMap
Description    : ��LMM Relԭ��ֵת��ΪTAF��LCS֮���ԭ��ֵ
Input          : enCause----------------LMM RElԭ��ֵ
Output         : NULL
Return Value   : TAF_LCS_CAUSE_ENUM_UINT32: ת����ԭ��ֵ

History        :
leixiantiao 00258641 2015-10-08  �¿���
*****************************************************************************/
TAF_LCS_CAUSE_ENUM_UINT32 NAS_LCS_LmmRelCauseMap(const LMM_LCS_REL_CAUSE_ENUM_UINT32 enCause)
{
    TAF_LCS_CAUSE_ENUM_UINT32 enTafCause;

    if (LMM_LCS_REL_CAUSE_USER_INACTIVITY == enCause)
    {
        enTafCause = TAF_LCS_CAUSE_LMM_USER_INACTIVITY;
    }
    else
    {
        enTafCause = TAF_LCS_CAUSE_LMM_OTHERS;
    }
    return enTafCause;
}

/*****************************************************************************
Function Name  : NAS_LCS_CheckLcsOperationCode
Description    : ȷ��Operation�Ƿ���LCS��Operation
Input          : enOperaCode----------------��ȷ�ϵ�Operation
Output         : NULL
Return Value   : ���,0:��Operation��LCS��Operation
1:��Operation����LCS��Operation

History        :
leixiantiao 00258641 2015-10-08  �¿���
*****************************************************************************/
VOS_UINT32 NAS_LCS_CheckLcsOperationCode(NAS_LCS_OPERATION_TYPE_UINT32 enOperaCode)
{
    VOS_UINT32                          ulRslt = NAS_LCS_FAIL;

    switch(enOperaCode)
    {
        case NAS_LCS_OPERATION_MO_LR:
        case NAS_LCS_OPERATION_LOC_NOTIFICATION:
        case NAS_LCS_OPERATION_AREA_EVENT_REQUEST:
        case NAS_LCS_OPERATION_AREA_EVENT_REPORT:
        case NAS_LCS_OPERATION_AREA_EVENT_CACELLATION:
        case NAS_LCS_OPERATION_PERIODIDC_LOCATION_REQUEST:
        case NAS_LCS_OPERATION_LOCATION_UPDATE:
        case NAS_LCS_OPERATION_PERIODIDC_LOCATION_CACELLATION:
            ulRslt = NAS_LCS_SUCC;
            break;

        default:
            ulRslt = NAS_LCS_FAIL;
    }
    return ulRslt;
}
#endif
/*****************************************************************************
Function Name  : NAS_LCS_JudgeLcsNwMsg
Description    : �жϿտ���Ϣ�Ƿ�ΪLCS�տ�,���ڵ�MMģ���յ��տ���ϢΪPDΪ0xBʱ
                 �ж��Ƿ�ÿտ���ϢΪLCS�տ���Ϣ
Input          : pucMsg----------------�տ���Ϣ����
                 ulMsgLen--------------�տ���Ϣ��������
Output         : NULL
Return Value   : ���,LCS_MM_NOT_LCS_NW_MSG:�ÿտ���Ϣ����LCS�տ���Ϣ
LCS_MM_LCS_NW_MSG    :�ÿտ���ϢʱLCS�տ���Ϣ

History        :
leixiantiao 00258641 2015-10-08  �¿���
*****************************************************************************/
VOS_UINT32 NAS_LCS_IsLcsNwMsg(VOS_UINT8 *pucMsg, VOS_UINT32 ulMsgLen)
{
    #if (FEATURE_LPP == FEATURE_ON)
    VOS_UINT8                           ucTi;
    VOS_UINT8                           ucSum         = 0;
    NAS_LCS_CN_MSG_TYPE_ENUM_UINT32     enCnMsgType;
    NAS_LCS_OPERATION_TYPE_UINT32       enOperaCode   = 0;
    VOS_UINT32                          ulUndecodeLen = ulMsgLen;
    VOS_UINT32                          ulIndex       = 0;

    if (NAS_LCS_NULL_PTR == pucMsg)
    {
        return LCS_MM_NOT_LCS_NW_MSG;
    }

    if (NAS_LCS_MSG_MIN_LEN > ulUndecodeLen)
    {
        return LCS_MM_NOT_LCS_NW_MSG;
    }

    /* ��ȡ����transaction identifier */
    ucTi = pucMsg[ucSum++] >> NAS_LCS_MOVEMENT_4_BITS;

    /* ��ȡMsg Type */
    enCnMsgType = pucMsg[ucSum++];

    ulUndecodeLen = ulUndecodeLen - ucSum;

    if ((NAS_LCS_CN_MSG_REL_CML == enCnMsgType)
        || (NAS_LCS_CN_MSG_FACILITY == enCnMsgType))
    {
        if (NAS_LCS_SUCC != NAS_LCS_QueryLcsEntity(ucTi, &ulIndex))
        {
            return LCS_MM_NOT_LCS_NW_MSG;
        }
    }
    else if(NAS_LCS_CN_MSG_REGISTER == enCnMsgType)
    {
        enOperaCode = NAS_LCS_GetRegisterOperaCode(&pucMsg[ucSum], ulUndecodeLen);

        if (NAS_LCS_SUCC != NAS_LCS_CheckLcsOperationCode(enOperaCode))
        {
            return LCS_MM_NOT_LCS_NW_MSG;
        }
    }
    else
    {
        return LCS_MM_NOT_LCS_NW_MSG;
    }
    return LCS_MM_LCS_NW_MSG;

    #else
    return LCS_MM_NOT_LCS_NW_MSG;
    #endif

}

/*****************************************************************************
 Function Name   : NAS_LCS_SecuMemCpy
 Description     : ��ȫmemcpy
 Input           : VOS_VOID* pDst, VOS_UINT32 ulMaxBuffer, const VOS_VOID* pSrc,
                   VOS_UINT32  ulLength, VOS_UINT32 ulLineNO, VOS_UINT32 ulFileID
 Output          : None
 Return          : VOS_INT32

 History         :
    1.z00297373    2015-12-28  Draft Enact
*****************************************************************************/
VOS_INT32 NAS_LCS_SecuMemCpy
(
    VOS_VOID            * pDst,
    VOS_UINT32          ulMaxBuffer,
    const VOS_VOID      * pSrc,
    VOS_UINT32          ulLength,
    VOS_UINT32          ulLineNO,
    VOS_UINT32          ulFileID
)
{
    /*���Դ��ַ��Ŀ�ĵ�ַ�ص��������TLPS_MEM_MOVE_S������ȫ����ʧ�� */
    if(((pSrc > pDst) && ((VOS_UINT8 *)pSrc <= ((VOS_UINT8 *)pDst + ulMaxBuffer)))
        ||((pDst> pSrc) && ((VOS_UINT8 *)pDst <= ((VOS_UINT8 *)pSrc + ulLength)))
        || (pSrc == pDst))
    {
        return TLPS_MEM_MOVE_S((pDst), (ulMaxBuffer), (pSrc), (ulLength), (ulLineNO), (ulFileID));
    }
    else
    {
        return TLPS_MEM_CPY_S((pDst), (ulMaxBuffer), (pSrc), (ulLength), (ulLineNO), (ulFileID));
    }
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif
