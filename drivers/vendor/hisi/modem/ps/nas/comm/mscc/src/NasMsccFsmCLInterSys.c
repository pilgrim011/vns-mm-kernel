/******************************************************************************

            Copyright 2014, Huawei Technologies Co. Ltd.

 ******************************************************************************
File Name       :   NasMsccFsmCLInterSys.c
Author          :   W00176964
Version         :
Date            :   2015-11-05
Description     :   CL��ϵͳ����״̬����״̬����Ϣ�����ļ�
Function list   :
History         :
    1) Date :
       Author:
       Modification:
******************************************************************************/


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasMsccFsmCLInterSys.h"
#include "NasMntn.h"
#include "NasMsccFsmCLInterSysTbl.h"
#include "NasMsccSndInternalMsg.h"
#include "NasMsccComFunc.h"
#include "NasMsccSndMmc.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MSCC_FSM_CL_INTER_SYS_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/

/*****************************************************************************
  6 ����ʵ��
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
  Function Name   :   NAS_MSCC_RcvHsdInterSysStartInd_CLInterSys_Init
  Description     :   CL��ϵͳ��INIT״̬�յ�HSD����ϵͳ��ʼָʾ
  Input parameters:   VOS_UINT32                          ulEventType,
                      struct MsgCB                       *pstMsg
  Outout parameters:  VOS_VOID
  Return Value    :   VOS_TRUE----��Ϣ�������
                      VOS_FALSE----��Ϣδ�������
  Modify History:
      1)  Date    :   2015-11-05
          Author  :   w00176964
          Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdInterSysStartInd_CLInterSys_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Save the entry message */
    NAS_MSCC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ��״̬Ǩ������ϵͳ����ָʾ */
    NAS_MSCC_SetCurrFsmState(NAS_MSCC_CL_INTERSYS_STA_WAIT_INTERSYS_END_IND);

    /* C2L��ѡ������ѡ�Ķ�ʱ��:67s */
    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND, TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND_C2L_RESEL_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
  Function Name   :   NAS_MSCC_RcvMmcInterSysStartInd_CLInterSys_Init
  Description     :   CL��ϵͳ��INIT״̬�յ�MMC����ϵͳ��ʼָʾ
  Input parameters:   VOS_UINT32                          ulEventType,
                      struct MsgCB                       *pstMsg
  Outout parameters:  VOS_VOID
  Return Value    :   VOS_TRUE----��Ϣ�������
                      VOS_FALSE----��Ϣδ�������
  Modify History:
      1)  Date    :   2015-11-05
          Author  :   w00176964
          Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcInterSysStartInd_CLInterSys_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_INTERSYS_START_IND_STRU   *pstInterSysStartInd;

     /* Save the entry message */
    NAS_MSCC_SaveCurEntryMsg(ulEventType, pstMsg);

    pstInterSysStartInd = (MMC_MSCC_INTERSYS_START_IND_STRU *)pstMsg;

    /* ��״̬Ǩ������ϵͳ����ָʾ */
    NAS_MSCC_SetCurrFsmState(NAS_MSCC_CL_INTERSYS_STA_WAIT_INTERSYS_END_IND);

    if (NAS_MSCC_PIF_INTERSYS_CAUSE_RESELECT == pstInterSysStartInd->enInterSysCause)
    {
        /* ����ѡ������ʱ��:37s */
        NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND, TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND_L2C_RESEL_LEN);
    }
    else
    {
        /* ���ض��򱣻���ʱ��:182s */
        NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND, TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND_L2C_REDIR_LEN);
    }

    return VOS_TRUE;
}


/*****************************************************************************
  Function Name   :   NAS_MSCC_RcvMmcPowerSaveCnf_CLInterSys_WaitMmcPowerSaveCnf
  Description     :   CL��ϵ��mmc power save cnf״̬�յ�mmc power save cnf
  Input parameters:   VOS_UINT32                          ulEventType,
                      struct MsgCB                       *pstMsg
  Outout parameters:  VOS_VOID
  Return Value    :   VOS_TRUE----��Ϣ�������
                      VOS_FALSE----��Ϣδ�������
  Modify History:
      1)  Date    :   2015-11-05
          Author  :   w00176964
          Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPowerSaveCnf_CLInterSys_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
     /* ֹͣ��Ӧ�Ķ�ʱ�� */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF);

    /* �����ڲ���ϵͳ���:��� */
    NAS_MSCC_SndCLInterSysRsltCnf(NAS_MSCC_CL_INTERSYS_RESULT_ABORTED);

    /* �˳����״̬�� */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}

/*****************************************************************************
  Function Name   :   NAS_MSCC_RcvHsdInterSysEndInd_CLInterSys_WaitInterSysEndInd
  Description     :   CL��ϵͳ����ϵͳ������״̬�յ�hsd����ϵͳ����ָʾ
  Input parameters:   VOS_UINT32                          ulEventType,
                      struct MsgCB                       *pstMsg
  Outout parameters:  VOS_VOID
  Return Value    :   VOS_TRUE----��Ϣ�������
                      VOS_FALSE----��Ϣδ�������
  Modify History:
      1)  Date    :   2015-11-05
          Author  :   w00176964
          Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdInterSysEndInd_CLInterSys_WaitInterSysEndInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MSCC_CL_INTERSYS_RESULT_ENUM_UINT32                 enCLInterSysRslt;

    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND);

    /* �ж���ϵͳ��� */
    enCLInterSysRslt = NAS_MSCC_JudgeCLInterSysRslt();

    NAS_MSCC_SndCLInterSysRsltCnf(enCLInterSysRslt);

    /* �˳����״̬�� */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
  Function Name   :   NAS_MSCC_RcvMsccAbortFsmReq_CLInterSys_WaitInterSysEndInd
  Description     :   CL��ϵͳ��INIT״̬�յ�MMC����ϵͳ��ʼָʾ
  Input parameters:   VOS_UINT32                          ulEventType,
                      struct MsgCB                       *pstMsg
  Outout parameters:  VOS_VOID
  Return Value    :   VOS_TRUE----��Ϣ�������
                      VOS_FALSE----��Ϣδ�������
  Modify History:
      1)  Date    :   2015-11-05
          Author  :   w00176964
          Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMsccAbortFsmReq_CLInterSys_WaitInterSysEndInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSG_STRU                                      *pstEntryMsg;

    pstEntryMsg = NAS_MSCC_GetCurrFsmEntryMsgAddr();

    /* �����L�������ϵͳ,�յ��û�������msccҪ���mmc����ϵͳ����
       �����C�������ϵͳ,�յ��û�������mscc���������Եȴ���ϵͳ����ָʾ*/
    if (pstEntryMsg->ulEventType == NAS_BuildEventType(WUEPS_PID_MMC, ID_MMC_MSCC_INTERSYS_START_IND))
    {
        /* ��ֹͣ����ϵͳ�����Ķ�ʱ�� */
        NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND);

        /* ���L�������ϵͳ */
        NAS_MSCC_SndMmcPowerSaveReq();

        NAS_MSCC_SetCurrFsmState(NAS_MSCC_CL_INTERSYS_STA_WAIT_MMC_POWER_SAVE_CNF);

        NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_MMC_POWER_SAVE_CNF, TI_NAS_MSCC_WAIT_CL_INTERSYS_MMC_POWERSAVE_CNF_LEN);
    }

    return VOS_TRUE;
}



/*****************************************************************************
  Function Name   :   NAS_MSCC_RcvMmcInterSysEndInd_CLInterSys_WaitInterSysEndInd
  Description     :   CL��ϵͳ��INIT״̬�յ�MMC����ϵͳ��ʼָʾ
  Input parameters:   VOS_UINT32                          ulEventType,
                      struct MsgCB                       *pstMsg
  Outout parameters:  VOS_VOID
  Return Value    :   VOS_TRUE----��Ϣ�������
                      VOS_FALSE----��Ϣδ�������
  Modify History:
      1)  Date    :   2015-11-05
          Author  :   w00176964
          Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcInterSysEndInd_CLInterSys_WaitInterSysEndInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_CL_INTERSYS_RESULT_ENUM_UINT32                 enCLInterSysRslt;

    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_CL_INTERSYS_END_IND);

    /* �ж���ϵͳ��� */
    enCLInterSysRslt = NAS_MSCC_JudgeCLInterSysRslt();

    NAS_MSCC_SndCLInterSysRsltCnf(enCLInterSysRslt);

    /* �˳����״̬�� */
    NAS_MSCC_QuitFsmL2();

    return VOS_TRUE;
}


/*****************************************************************************
  Function Name   :   NAS_MSCC_RcvTiWaitCLInterSysEndIndExpired_CLInterSys_WaitInterSysEndInd
  Description     :   CL��ϵͳ��INIT״̬�յ�MMC����ϵͳ��ʼָʾ
  Input parameters:   VOS_UINT32                          ulEventType,
                      struct MsgCB                       *pstMsg
  Outout parameters:  VOS_VOID
  Return Value    :   VOS_TRUE----��Ϣ�������
                      VOS_FALSE----��Ϣδ�������
  Modify History:
      1)  Date    :   2015-11-05
          Author  :   w00176964
          Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitCLInterSysEndIndExpired_CLInterSys_WaitInterSysEndInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSG_STRU                                      *pstEntryMsg;

    pstEntryMsg = NAS_MSCC_GetCurrFsmEntryMsgAddr();

    /* Print Warning Log */
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitCLInterSysEndIndExpired_CLInterSys_WaitInterSysEndInd:time expired!");

    if (pstEntryMsg->ulEventType == NAS_BuildEventType(WUEPS_PID_MMC, ID_MMC_MSCC_INTERSYS_START_IND))
    {
        /* L2C ��ʱ��λ */
        NAS_MSCC_SoftReBoot(NAS_MSCC_REBOOT_SCENE_MSCC_WAIT_CL_INTERSYS_END_L2C_EXPIRED, UEPS_PID_MSCC);
    }
    else
    {
        /* C2L ��ʱ��λ */
        NAS_MSCC_SoftReBoot(NAS_MSCC_REBOOT_SCENE_MSCC_WAIT_CL_INTERSYS_END_C2L_EXPIRED, UEPS_PID_MSCC);
    }

    return VOS_TRUE;
}

/*****************************************************************************
  Function Name   :   NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_CLInterSys_WaitMmcPowerSaveCnf
  Description     :   CL��ϵͳ��power save cnf��ʱ
  Input parameters:   VOS_UINT32                          ulEventType,
                      struct MsgCB                       *pstMsg
  Outout parameters:  VOS_VOID
  Return Value    :   VOS_TRUE----��Ϣ�������
                      VOS_FALSE----��Ϣδ�������
  Modify History:
      1)  Date    :   2015-11-05
          Author  :   w00176964
          Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_CLInterSys_WaitMmcPowerSaveCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Print Warning Log */
    NAS_WARNING_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvTiWaitMmcPowerSaveCnfExpired_CLInterSys_WaitMmcPowerSaveCnf:time expired!");

    /* Reboot */
    NAS_MSCC_SoftReBoot(NAS_MSCC_REBOOT_SCENE_MSCC_WAIT_CL_INTERSYS_MMC_POWER_SAVE_CNF_L2C_EXPIRED, UEPS_PID_MSCC);

    return VOS_TRUE;
}

/*****************************************************************************
  Function Name   :   NAS_MSCC_JudgeCLInterSysRslt
  Description     :   ������ϵͳ���𷽺͵�ǰ���ڼ���̬�Ľ��������ж���ϵͳ���
  Input parameters:   None
  Outout parameters:  None
  Return Value    :   None
  Modify History:
      1)  Date    :   2015-11-09
          Author  :   y00346957
          Modify content :    Create
*****************************************************************************/
NAS_MSCC_CL_INTERSYS_RESULT_ENUM_UINT32 NAS_MSCC_JudgeCLInterSysRslt(VOS_VOID)
{
    NAS_MSCC_MSG_STRU                   *pstEntryMsg = VOS_NULL_PTR;

    pstEntryMsg = NAS_MSCC_GetCurrFsmEntryMsgAddr();

    /* �����L�������ϵͳ,���lte���ڼ���̬����ϵͳʧ�� */
    if (pstEntryMsg->ulEventType == NAS_BuildEventType(WUEPS_PID_MMC, ID_MMC_MSCC_INTERSYS_START_IND))
    {
        if (VOS_TRUE == NAS_MSCC_Get3gppActiveFlg())
        {
            return NAS_MSCC_CL_INTERSYS_RESULT_FAIL;
        }
        else
        {
            return NAS_MSCC_CL_INTERSYS_RESULT_SUCC;
        }
    }
    /* �����C�������ϵͳ,���hrpd���ڼ���̬����ϵͳʧ�� */
    else
    {
        if (VOS_TRUE == NAS_MSCC_GetHrpdActiveFlg())
        {
            return NAS_MSCC_CL_INTERSYS_RESULT_FAIL;
        }
        else
        {
            return NAS_MSCC_CL_INTERSYS_RESULT_SUCC;
        }
    }
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



