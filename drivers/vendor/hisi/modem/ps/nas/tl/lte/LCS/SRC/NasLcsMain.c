/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : NasLcsMain.c
  Description     : ��C�ļ�������LCS_MAINģ���ʵ��
  History           :
        1.lihong  00150010       2015-09-28  Draft Enact
******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "vos.h"
#include    "PsTypeDef.h"
#include    "NasLcsMain.h"
#include    "NasLcsPublic.h"
#include    "NasLcsEmmMsgProc.h"
#include    "NasLcsMmMsgProc.h"
#include    "NasLcsLppMsgProc.h"
#include    "NasLcsOm.h"

#define    THIS_FILE_ID            PS_FILE_ID_NASLCSMAIN_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLCSMAIN_C

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/



/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
 Function Name  : NAS_LCS_TaskEntry
 Description    : LCSģ��TASK��ڴ���,���ݽ��յ�����Ϣ������ģ�飬����Ϣ�ַ��������ģ����Ϣ����ģ�顣
 Input          : struct MsgCB* pMsg-----------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.lihong 00150010 2015-9-28 Draft Enact
 *****************************************************************************/
VOS_VOID  NAS_LCS_TaskEntry(MsgBlock * pMsg)
{
    /* ������Ϣͷָ��*/
#if (FEATURE_LPP == FEATURE_ON)
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    NAS_LCS_NORM_LOG("NAS_LCS_TaskEntry is entered!");
    TLPS_PRINT2LAYER_INFO(NAS_LCS_TaskEntry_ENUM, LNAS_ENTRY);

    /* �ж���ڲ����Ƿ�Ϸ�*/
    if( VOS_NULL_PTR == pMsg)
    {
        NAS_LCS_ERR_LOG("NAS_LCS_TaskEntry:ERROR: No Msg!");
        TLPS_PRINT2LAYER_ERROR(NAS_LCS_TaskEntry_ENUM, LNAS_NULL_PTR);
        return;
    }

    /* ��ȡ��Ϣͷָ��*/
    pHeader = (PS_MSG_HEADER_STRU *) pMsg;

    NAS_LCS_PrintLcsRevMsg(pHeader,NAS_COMM_GET_LCS_PRINT_BUF());

    switch(pHeader->ulSenderPid)
    {
        /*�����EMM��Ϣ������EMM������*/
        case PS_PID_MM:
            NAS_LCS_EmmMsgDistr(pMsg);
            break;

        /*�����MM��Ϣ������MM������*/
        case WUEPS_PID_MM:
            NAS_LCS_MmMsgDistr(pMsg);
            break;

        /*�����TAF��Ϣ������TAF������*/
        case WUEPS_PID_TAF:
            NAS_LCS_TafMsgDistr(pMsg);
            break;

        /*�����Timer��Ϣ������Timer���������*/
        case VOS_PID_TIMER:
            NAS_LCS_TimerMsgDistr(pMsg);
            break;

        /*�����LPP����Ϣ������LPP�Ĵ�����*/
        case PS_PID_LPP:
            NAS_LCS_LppMsgDistr(pMsg);
            break;

        default:
            NAS_LCS_WARN_LOG("NAS_LCS_TaskEntry:NORM: Error SenderPid!");
            TLPS_PRINT2LAYER_ERROR(NAS_LCS_TaskEntry_ENUM, LNAS_LCS_InvalidRsvPid);
            break;
    }
#endif
    return;
}

/*****************************************************************************
 Function Name  : NAS_LCS_Init
 Discription    : LCS�ĳ�ʼ������
 Input          : None
 Output         : None
 Return         : None
 History:
      1.lihong 00150010 2015-9-28 Draft Enact
*****************************************************************************/
VOS_VOID NAS_LCS_Init ( VOS_VOID )
{
#if (FEATURE_LPP == FEATURE_ON)
    NAS_LCS_PUB_INFO_STRU              *pstLcsInfo  = NAS_LCS_NULL_PTR;
    VOS_UINT32                          i           = 0;

    pstLcsInfo = NAS_LCS_GetLcsInfo();

    NAS_LCS_MEM_SET_S(  pstLcsInfo,
                        sizeof(NAS_LCS_PUB_INFO_STRU),
                        0,
                        sizeof(NAS_LCS_PUB_INFO_STRU));

    /* ��ʼ������������֧��LCS */
    pstLcsInfo->stNwLcsCap.enNwCsLcs = NAS_LCS_NW_CS_LCS_NOT_SUPPORT;
    pstLcsInfo->stNwLcsCap.enNwEpcLcs= NAS_LCS_NW_EPC_LCS_NOT_SUPPORT;

    /* ʵ���ʼ�� */
    pstLcsInfo->astLcsEntity[NAS_LCS_MO_LR_LPP_INDEX].enUsedFlag = NAS_LCS_ENTITY_NOT_USED;
    pstLcsInfo->astLcsEntity[NAS_LCS_MO_LR_LPP_INDEX].enEntityState = NAS_LCS_ENTITY_STATE_NULL;
    pstLcsInfo->astLcsEntity[NAS_LCS_MO_LR_LPP_INDEX].enConnState = NAS_LCS_CONN_STATE_IDLE;
    pstLcsInfo->astLcsEntity[NAS_LCS_MO_LR_LPP_INDEX].enStartSource = NAS_LCS_START_SOURCE_LPP;

    pstLcsInfo->astLcsEntity[NAS_LCS_MO_LR_TAF_INDEX].enUsedFlag = NAS_LCS_ENTITY_NOT_USED;
    pstLcsInfo->astLcsEntity[NAS_LCS_MO_LR_TAF_INDEX].enEntityState = NAS_LCS_ENTITY_STATE_NULL;
    pstLcsInfo->astLcsEntity[NAS_LCS_MO_LR_TAF_INDEX].enConnState = NAS_LCS_CONN_STATE_IDLE;
    pstLcsInfo->astLcsEntity[NAS_LCS_MO_LR_TAF_INDEX].enStartSource = NAS_LCS_START_SOURCE_TAF;

    for (i = NAS_LCS_MT_LR_ENTITY_INDEX_BEGIN; i <= NAS_LCS_MT_LR_ENTITY_INDEX_END; i++)
    {
        pstLcsInfo->astLcsEntity[i].enUsedFlag = NAS_LCS_ENTITY_NOT_USED;
        pstLcsInfo->astLcsEntity[i].enEntityState = NAS_LCS_ENTITY_STATE_NULL;
        pstLcsInfo->astLcsEntity[i].enConnState = NAS_LCS_CONN_STATE_IDLE;
        pstLcsInfo->astLcsEntity[i].enStartSource = NAS_LCS_START_SOURCE_NW;
    }

    /* TAF������ʼ�� */
    pstLcsInfo->stTafMsgRecord.stMolrPara.enMethod = LCS_MOLR_METHOD_BUTT;
    pstLcsInfo->stTafMsgRecord.stMolrPara.enRepMode=LCS_REP_MODE_SINGLE_RPT;

    /* ��ʼ����ǰʹ�õ�HANDLE ID */
    pstLcsInfo->ucCurHandleId = 0;

#endif
    return ;
}


/*****************************************************************************
 Function Name  : NAS_LCS_PidInit
 Discription    : LPP��PID��ʼ������
 Input          :
 Output         : None
 Return         : None
 History:
      1.lihong 00150010 2015-9-28 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_LCS_PidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
#if (FEATURE_LPP == FEATURE_ON)

    switch( ip )
    {
        case    VOS_IP_LOAD_CONFIG:
                {
                    NAS_LCS_Init();
                }
                break;

        case    VOS_IP_FARMALLOC:
        case    VOS_IP_INITIAL:
        case    VOS_IP_ENROLLMENT:
        case    VOS_IP_LOAD_DATA:
        case    VOS_IP_FETCH_DATA:
        case    VOS_IP_STARTUP:
        case    VOS_IP_RIVAL:
        case    VOS_IP_KICKOFF:
        case    VOS_IP_STANDBY:
        case    VOS_IP_BROADCAST_STATE:
        case    VOS_IP_RESTART:
        case    VOS_IP_BUTT:
                break;

        default:
                break;
    }
#endif
    return VOS_OK;
}

/*****************************************************************************
 Function Name  : NAS_LCS_FidInit
 Discription    : LCS��PID��ʼ������
 Input          :
 Output         : None
 Return         : None
 History:
      1.leixiantiao 00258641 2016-01-11 Draft Enact
*****************************************************************************/
VOS_UINT32 NAS_ESM_FidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    VOS_UINT32                              ulRet;

    switch( ip )
    {
        case    VOS_IP_LOAD_CONFIG:

                ulRet = VOS_RegisterPIDInfo(WUEPS_PID_LCS,
                                            NAS_LCS_PidInit,
                                            NAS_LCS_TaskEntry);
                if( VOS_OK != ulRet )
                {
                    return VOS_ERR;
                }

                ulRet = VOS_RegisterMsgTaskPrio(PS_FID_CM, VOS_PRIORITY_M5);
                if( PS_SUCC != ulRet )
                {
                    return ulRet;
                }
                break;

        case    VOS_IP_FARMALLOC:
        case    VOS_IP_INITIAL:
        case    VOS_IP_ENROLLMENT:
        case    VOS_IP_LOAD_DATA:
        case    VOS_IP_FETCH_DATA:
        case    VOS_IP_STARTUP:
        case    VOS_IP_RIVAL:
        case    VOS_IP_KICKOFF:
        case    VOS_IP_STANDBY:
        case    VOS_IP_BROADCAST_STATE:
        case    VOS_IP_RESTART:
        case    VOS_IP_BUTT:
                break;
    }

    return VOS_OK;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of NasLcsMain.c */

