/******************************************************************************

                  ��Ȩ���� (C), 1998-2010, ��Ϊ�������޹�˾

******************************************************************************
  �� �� ��   : ftm_api.c
  �� �� ��   : V1.0
  ��    ��   : ���ķ�/00149739
  ��������   : 2010-05-12
  ��������   : TODO: ...

  �����б�   : TODO: ...
  �޸���ʷ   :
  1.��    �� : 2010-05-12
    ��    �� : ���ķ�/00149739
    �޸����� : �����ļ�

******************************************************************************/

/******************************************************************************
 PROJECT   :
 SUBSYSTEM :
 MODULE    :
 OWNER     :
******************************************************************************/
#include "ftm_errno.h"
#include "taf_drx.h"
#include "osm.h"
#include "gen_msg.h"
#include <ftm.h>
#include "ftm_ct.h"
#include "ftm_mntn.h"

/*lint --e{830,539,525}*/

/*lint -e767*/
#define    THIS_FILE_ID        MSP_FILE_ID_FTM_COMMON_API_C
/*lint -e767*/

/* �¶ȶ�ʱ��ѯ��ʱ��ID */
VOS_UINT32 g_ulFtmCmTmsTimer;


/*****************************************************************************
�� �� ��  : ftm_comm_starttimer
��������  : ����FTMģ�鳬ʱ��ʱ��
�������  : reqID ʹ������ϢID
�������  : pulTimer ��ʱ��ID
�� �� ֵ  : �ɹ�����ERR_FTM_SUCCESS, ʧ�ܷ���ERR_FTM_FAILURE
*****************************************************************************/
VOS_UINT32 ftm_comm_starttimer(VOS_UINT32* pulTimer, VOS_UINT32 reqId)
{
    VOS_UINT32 ulRet = ERR_FTM_SUCCESS;

    /* ���������ʱ����ʱ��û�ͷţ���ɻ��� */
    if(0 != (*pulTimer))
    {
    	/*lint -save -e740*/
		(VOS_VOID)VOS_StopRelTimer((HTIMER*)pulTimer);
		/*lint -restore*/
        *pulTimer = 0;
    }
	/*lint -save -e740*/
    ulRet = VOS_StartRelTimer((HTIMER*)pulTimer, MSP_SYS_FTM_PID, FTM_CT_OVER_TIME,
        0, reqId, (VOS_UINT8)VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION);
	/*lint -restore*/
    if(ulRet != ERR_FTM_SUCCESS)
    {
        ulRet = ERR_FTM_FAILURE;
    }

    return ulRet;
}

/*****************************************************************************
�� �� ��  : ftm_comm_stoptimer
��������  : ֹͣFTMģ�鳬ʱ��ʱ��
�������  : pulTier ��ʱ��ID
�������  : ��
�� �� ֵ  : �ɹ�����ERR_FTM_SUCCESS, ���򷵻�ERR_FTM_FAILURE
****************************************************************************/
VOS_UINT32 ftm_comm_stoptimer(VOS_UINT32* pulTimer)
{
    VOS_UINT32 ulRet = ERR_FTM_SUCCESS;

    if(*pulTimer != 0)
    {
    	/*lint -save -e740*/
        ulRet     = VOS_StopRelTimer((HTIMER*)pulTimer);
		/*lint -restore*/
        *pulTimer = 0;
    }

    if(ulRet != ERR_FTM_SUCCESS)
    {
        ulRet = ERR_FTM_FAILURE;
    }

    return ulRet;
}

/*****************************************************************************
 �� �� ��  : ftm_comm_send
 ��������  : ��MSP_SYS_FTM_PID��������Ϣ��UEPS_PID_AT����
 �������  : ulMsgId ��ϢID
             ulParam1 ��Ϣ����
             ulParam1  ��Ϣ����
 �������  : ��
 �� �� ֵ  : �ɹ�����ERR_FTM_SUCCESS, ���򷵻�ERR_FTM_FAILURE
*****************************************************************************/
VOS_UINT32 ftm_comm_send(VOS_UINT32 ulMsgId, VOS_UINT32 ulParam1, VOS_UINT32 ulParam2)
{
    VOS_UINT32 ulRet = ftm_SendDataMsg(MSP_SYS_FTM_PID, WUEPS_PID_AT, ulMsgId, ulParam1, ulParam2);

    if(ulRet != ERR_FTM_SUCCESS)
    {
        ulRet = ERR_FTM_FAILURE;
    }

    return ulRet;
}

VOS_UINT32 ftm_MsgProcInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ulRet = 0;

    if (ip == VOS_IP_RESTART)
    {
        drx_taf_init();
		
        /* ��ʼ��FTMģ����Ϣ */
        ftm_MainInfoInit();


        /* ��ʼ������  */
		/*lint -save -e746*/
        (VOS_VOID)ftm_mailbox_init();
		/*lint -restore*/

    }

    return ulRet;
}

VOS_VOID ftm_MsgProc(MsgBlock *pMsgBlock)
{
	/*lint -save -e830*/
	VOS_UINT32 ret = ERR_FTM_SUCCESS;
	/*lint -restore*/

    OS_MSG_STRU* pMsg = NULL;
    OS_MSG_STRU stEvent = { 0 };

    if (NULL == pMsgBlock)
    {
        return;
    }

	/*vote lock */
	drx_taf_fid_vote_lock(DRX_FTM_VOTE);
    if (pMsgBlock->ulSenderPid == DOPRA_PID_TIMER)   /* ��ʱ��ʱ����Ϣ */
    {
        stEvent.ulMsgId  = ID_MSG_FTM_TIME_OUT;
        stEvent.ulParam1 =  VOS_MemAlloc(MSP_SYS_FTM_PID, (DYNAMIC_MEM_PT), sizeof(OSM_MSG_TIMER_STRU));

        if (NULL != stEvent.ulParam1)/* [false alarm]:fortify */
        {
			/*lint -save -e740*/
			((OSM_MSG_TIMER_STRU*)(stEvent.ulParam1))->ulPara = ((REL_TIMER_MSG*)pMsgBlock)->ulPara;/* [false alarm]:fortify */
			((OSM_MSG_TIMER_STRU*)(stEvent.ulParam1))->ulTimeId = (VOS_UINT32) (((REL_TIMER_MSG*)pMsgBlock)->hTm);/* [false alarm]:fortify */
			/*lint -restore*/
            stEvent.ulParam2 = sizeof(OSM_MSG_TIMER_STRU);/* [false alarm]:fortify */
            ret              = ftm_TaskMsg(&stEvent);/* [false alarm]:fortify */
        }/* [false alarm]:fortify */
    }
    else if (pMsgBlock->ulSenderPid == WUEPS_PID_AT)   /* A�˷���������Ϣ */
    {
        ret = FTM_MsgConvert(pMsgBlock, &stEvent);/* [false alarm]:fortify */
        if (ERR_FTM_SUCCESS == ret)/* [false alarm]:fortify */
        {
            ret  = ftm_TaskMsg(&stEvent);/* [false alarm]:fortify */
        }/* [false alarm]:fortify */
    }
    else   /* LRTT��TRTT��������Ϣ */
    {
        pMsg = (OS_MSG_STRU*)(pMsgBlock->aucValue);
        ret  = ftm_TaskMsg(pMsg);/* [false alarm]:fortify */
    }/* [false alarm]:fortify */
	/* vote unlock */
	drx_taf_fid_vote_unlock(DRX_FTM_VOTE);
/*lint -save -e438*/
}
/*lint -restore*/
/*****************************************************************************
 ��������: FTM_FidInit
 ��������: ϵͳ���� ����ϵͳ����

 ����˵��:
   VOS_INIT_PHASE_DEFINE ip [in/out] : ����Ĳ������


 �� �� ֵ:
    �ɹ���VOS_OK: ��ʾ�����ɹ�
    ʧ�ܣ�OTHER
          ����ʧ��

 ����Ҫ��: TODO: ...
 ���þ���: TODO: ...
 ��    ��: ���ķ�/00149739 [2011-01-22]
*****************************************************************************/
VOS_UINT32 MSP_FtmFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ulRelVal;

    switch (ip)
    {
    case VOS_IP_LOAD_CONFIG:

        ulRelVal = VOS_RegisterPIDInfo(MSP_SYS_FTM_PID, (Init_Fun_Type) ftm_MsgProcInit, (Msg_Fun_Type) ftm_MsgProc);
        if (ulRelVal != VOS_OK)
        {
            HAL_SDMLOG("In MSP_FtmFidInit Failed,  VOS_RegisterPIDInfo\n");
            return VOS_ERR;
        }

        ulRelVal = VOS_RegisterMsgTaskPrio(MSP_FTM_FID, VOS_PRIORITY_M2);

        if (ulRelVal != VOS_OK)
        {
            HAL_SDMLOG("In MSP_FtmFidInit Failed,  VOS_RegisterMsgTaskPrio\n");/* [false alarm]:fortify */
            return VOS_ERR;/* [false alarm]:fortify */
        }

        ulRelVal = VOS_RegisterSelfTask(MSP_FTM_FID, ftm_mailbox_taskproc, VOS_PRIORITY_M2, 4096);/* [false alarm]:fortify */
        if (VOS_NULL_BYTE  == ulRelVal)/* [false alarm]:fortify */
        {
            HAL_SDMLOG("In MSP_FtmFidInit Failed,  VOS_RegisterSelfTask\n");/* [false alarm]:fortify*/
            return VOS_ERR;/* [false alarm]:fortify */
        }/* [false alarm]:fortify */

        break;

    default:
        break;
    }

    return VOS_OK;
}
