/******************************************************************************

   Copyright(C)2013,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : CssMain.c
  Description     : ��C�ļ�������CSSģ���ʼ������Ϣ������ڵ�ʵ��
  History           :
     1.wangchen 00209181    2015-05-14  Draft Enact

******************************************************************************/

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include    "CssMain.h"
#include    "CssCloudStrategyPublic.h"


#define    THIS_FILE_ID        PS_FILE_ID_CSSMAIN_C

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
CSS_CONTROL_STRU                        g_stCssControl;
CSS_CONTROL_STRU                       *pgstCssControl = &g_stCssControl;
CSS_CLOUD_PUB_CONTROL_STRU              g_stCloudContrl;

/*****************************************************************************
  3 Function
*****************************************************************************/

/*****************************************************************************
 Function Name  : CSS_Init
 Description    : CSSģ���ϵ��ʼ������
 Input          : VOS_VOID
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.chengmin 00285307   2015-10-15  Draft Enact
*****************************************************************************/
VOS_VOID CSS_Init(VOS_VOID)
{
    /* ������ȫ�ֱ�����ʼ�� */
    CSS_MEM_SET_S(&g_stCloudContrl, sizeof(CSS_CLOUD_PUB_CONTROL_STRU), 0, sizeof(CSS_CLOUD_PUB_CONTROL_STRU));

    /* ��ȡ��ͨ��ʹ��NV */
    if (CSS_SUCC != CSS_ReadNvCloudStrategy())
    {
        /* ���NV��ȡʧ�ܣ�����Ϊ��ͨ�����Բ��� */
        g_stCloudContrl.ucCloudEnable    = VOS_FALSE;
        g_stCloudContrl.ucPrefFreqEnable = VOS_FALSE;
    }
    #if(FEATURE_ON == FEATURE_CSS_CLOUD_MEMORY_IMPROVE)
    /* ��ʼ���ڴ�� */
    CSS_MEM_SET_S(g_acCssCloudFreqMemory, CSS_CLOUD_MEM_TOTAL_LEN, 0, CSS_CLOUD_MEM_TOTAL_LEN);
    #endif

    if (VOS_TRUE == g_stCloudContrl.ucCloudEnable)
    {
        /* ��ȡNV��Ԥ��Ƶ�� */
        CSS_ReadNvCloudPrefArfcn();
    }

    /* ��ʱ����ʼ�� */
    CSS_CloudContrlTimerInit();

    /* ��ʼ���ƶ˰汾�� */
    CSS_InitMccVersion();


}

/*****************************************************************************
 Function Name  : CSS_MsgHandle()
 Description    : CSS������������,���ݽ��յ�����Ϣ������ģ�飬����Ϣ�ַ��������ģ����Ϣ����ģ�顣
 Input          : VOS_VOID *pRcvMsg
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1.wangchen 00209181   2015-05-14  Draft Enact
*****************************************************************************/
VOS_VOID CSS_MsgHandle(const VOS_VOID *pRcvMsg )
{
    /* ������Ϣͷָ��*/
    PS_MSG_HEADER_STRU          *pHeader = VOS_NULL_PTR;

    /* ��ȡ��Ϣͷָ��*/
    pHeader = (PS_MSG_HEADER_STRU *) pRcvMsg;
    #if (VOS_WIN32 != VOS_OS_VER)
    TLPS_ExcLog_SaveMsgList((VOS_VOID *)pHeader);
    #endif

    TLPS_PRINT2LAYER_INFO1(CSS_MsgHandle_ENUM, LNAS_ENTRY, pHeader->ulMsgName);

    CSS_PrintCssRevMsg(pHeader,CSS_GET_CSS_PRINT_BUF());

    switch(pHeader->ulSenderPid)
    {
        case UEPS_PID_GAS:
        case WUEPS_PID_WRR:
        case WUEPS_PID_MMC:
        case PS_PID_ERRC:
        case I1_UEPS_PID_GAS:
        case I1_WUEPS_PID_MMC:
        case WUEPS_PID_WCOM:
        case PS_PID_ERMM:
        case TPS_PID_RRC:
            CSS_ProcCommMsg(pRcvMsg);
            break;

        case PS_PID_MM:
            CSS_ProcLmmMsg(pRcvMsg);
            break;

        case PS_PID_HPA:
            CSS_ProcLphyMsg(pRcvMsg);
            break;

        case VOS_PID_TIMER:
            CSS_ProcTimerMsg((REL_TIMER_MSG *)pRcvMsg);
            break;
        case WUEPS_PID_AT:
            CSS_ProcAtMsg(pRcvMsg);
            break;
        default:
            break;

    }
}

/*****************************************************************************
 Function Name  : CSS_TaskEntry()
 Description    : CSSģ��TASK��ڴ���
 Input          : struct MsgCB* pMsg-----------��Ϣָ��
 Output         : VOS_VOID
 Return Value   : VOS_VOID

 History        :
      1. wangchen 00209181  2015-05-14  Draft Enact

 *****************************************************************************/
VOS_VOID CSS_TaskEntry(MsgBlock * pMsg)/*lint -e818 -e830*/
{
    /* �ж���ڲ����Ƿ�Ϸ�*/
    if( VOS_NULL_PTR == pMsg)
    {
        return;
    }

    /* ��Ϣ���� */
    CSS_MsgHandle((const VOS_VOID *)pMsg);
    /* CSS��Ϣ���������ʹ�ӡ */
    TLPS_SendPrintBufferInfo();

}

/*****************************************************************************
 Function Name  : CSS_PidInit
 Discription    : CSS��PID��ʼ������
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-05-14  Draft Enact

*****************************************************************************/
VOS_UINT32 CSS_PidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch( ip )
    {
        case    VOS_IP_LOAD_CONFIG:
                {
                    CSS_Init();
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

    return VOS_OK;
}

/*****************************************************************************
 Function Name  : CSS_FidInit
 Discription    : CSS��FID��ʼ������
 Input          :
 Output         : None
 Return         : None
 History:
      1. wangchen 00209181  2015-05-14  Draft Enact

*****************************************************************************/
VOS_UINT32 CSS_FidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    VOS_UINT32                              ulRet;

    switch( ip )
    {
        case    VOS_IP_LOAD_CONFIG:

                ulRet = VOS_RegisterPIDInfo(PS_PID_CSS,
                                            CSS_PidInit,
                                            CSS_TaskEntry);

                if( VOS_OK != ulRet )
                {
                    return VOS_ERR;
                }


                ulRet = VOS_RegisterMsgTaskPrio(UEPS_FID_CSS, VOS_PRIORITY_M1);
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



