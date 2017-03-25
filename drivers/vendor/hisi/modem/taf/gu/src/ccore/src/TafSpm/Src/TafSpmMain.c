/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafSpmMain.c
  �� �� ��   : ����
  ��    ��   : W00176964
  ��������   : 2013��5��8��
  ����޸�   :
  ��������   : TafSpmMain.C�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2013��5��8��
    ��    ��   : w00176964
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "TafSpmCtx.h"
#include "TafSpmMain.h"
#include "TafSpmFsmMainTbl.h"
#include "TafLog.h"
#include "TafSpmFsmServiceCtrlTbl.h"
#include "TafSpmProcNvim.h"
/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-11, begin */
#include "TafSdcCtx.h"
/* Added by s00217060 for VoLTE_PhaseI  ��Ŀ, 2013-07-11, end */

/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-15, begin */
#include "TafSpmServiceDomainSelProc.h"
/* Added by y00245242 for VoLTE_PhaseI  ��Ŀ, 2013-7-15, end */
/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-14, begin */
#include "TafSpmPreProcTbl.h"
/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-14, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_MAIN_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  6 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : TAF_SPM_BuildEventType
 ��������  : ����EventType
 �������  : pstMsg      :  ��Ϣ����
 �������  : ��
 �� �� ֵ  : ulEventType�¼�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��9��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��6��6��
    ��    ��   : l00198894
    �޸�����   : Modem PID��չ
*****************************************************************************/
VOS_UINT32 TAF_SPM_BuildEventType(
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulEventType;
    MSG_HEADER_STRU                    *pstMsgHeader   = VOS_NULL_PTR;
    REL_TIMER_MSG                      *pstRcvTimerMsg = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstMsg;

    /* ���������ʱ����Ϣ���ܿ���Ϣͷ���ƽ������֣�������ṹ���ulName���������
        ���Դ˴����зֱ��� */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;
        ulEventType    = TAF_BuildEventType(pstMsgHeader->ulSenderPid, pstRcvTimerMsg->ulName);

        /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-25, begin */

        /* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-25, end */
    }
    else
    {
        ulEventType  = TAF_BuildEventType(pstMsgHeader->ulSenderPid, pstMsgHeader->ulMsgName);
    }

    return ulEventType;
}


/*****************************************************************************
 �� �� ��  : TAF_SPM_MsgProc
 ��������  : TAF SPM����Ϣ������
 �������  : pstSrcMsg       :SPMģ���յ���ԭʼ��Ϣ
             ppstDestMsg     :SPMģ�鴦����ɺ��Ŀ����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_TRUE :��ǰ��Ϣ��spmģ�鴦����ɣ�����Ҫ����ԭ��MNģ�鴦��
             VOS_FALSE:spmģ�鴦��δ��ɣ���Ҫ����ԭ��MNģ�鴦��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2012��7��14��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��12��17��
   ��    ��   : s00217060
   �޸�����   : VoLTE_PhaseIII��Ŀ
*****************************************************************************/
VOS_UINT32 TAF_SPM_MsgProc(
    struct MsgCB                       *pstSrcMsg,
    struct MsgCB                      **ppstDestMsg
)
{
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          ulRet;
    TAF_SPM_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;

    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-25, begin */
    REL_TIMER_MSG                      *pstRcvTimerMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader    = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU *)pstSrcMsg;

    /* ���������ʱ����Ϣ���ܿ���Ϣͷ���ƽ������֣�������ṹ���ulName���������
        ���Դ˴����зֱ��� */
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        pstRcvTimerMsg = (REL_TIMER_MSG *)pstSrcMsg;

        /* ֹֻͣSPM�Լ��Ķ�ʱ��,����ģ�鶨ʱ�������ڲ��Լ�ֹͣ */
        if (MN_TIMER_CLASS_SPM == (pstRcvTimerMsg->ulName & MN_TIMER_CLASS_MASK))
        {
            TAF_SPM_StopTimer(pstRcvTimerMsg->ulName,(VOS_UINT16)pstRcvTimerMsg->ulPara);
        }
    }
    /* Modified by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-25, end */

    ulEventType = TAF_SPM_BuildEventType(pstSrcMsg);

    /* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-17, begin */
    /* ����Ѿ�Ԥ���������ֱ�ӷ��� */
    if (VOS_TRUE == TAF_SPM_PreProcessMsg(ulEventType, pstSrcMsg))
    {
        return VOS_TRUE;
    }
    /* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-17, end */

    /* ����Ѿ����������ֱ�ӷ��� */
    ulRet = TAF_SPM_ProcessMsgInFsm(ulEventType, pstSrcMsg);

    /* �ж��Ƿ���Ҫ�滻�����Ϣ */
    if (VOS_TRUE == TAF_SPM_GetUpdateEntryMsgFlg())
    {
        pstEntryMsg = TAF_SPM_GetServiceCtrlEntryMsgAddr();
       *ppstDestMsg = (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer;

        /* ��Ϣ�Ѿ�ʹ�ã��ظ����ñ��λ�������������Ϣ��  */
        TAF_SPM_SetUpdateEntryMsgFlg(VOS_FALSE);
    }
    else
    {
       *ppstDestMsg = pstSrcMsg;
    }

    /* ���������� */
    return ulRet;
}



/*****************************************************************************
 �� �� ��  : TAF_SPM_RegFsm
 ��������  : ����״̬��ע��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��05��8��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2014��01��02��
    ��    ��   : s00217060
    �޸�����   : VoLTE_PhaseIII��Ŀ
*****************************************************************************/
VOS_VOID TAF_SPM_RegFsm( VOS_VOID  )
{
    /* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2014-01-02, begin */
    /* Ԥ����ע�� */
    TAF_FSM_RegisterFsm((TAF_SPM_GetPreFsmDescAddr()),
                         "TAF_SPM:FSM:PreProcess",
                         TAF_SPM_GetPreProcessStaTblSize(),
                         TAF_SPM_GetPreProcessStaTbl(),
                         VOS_NULL_PTR,
                         VOS_NULL_PTR);
    /* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2014-01-02, end */

    /* ������״̬��ע�� */
    TAF_FSM_RegisterFsm(TAF_SPM_GetMainFsmDescAddr(),
                         "TAF_SPM:FSM:MainProcess",
                         TAF_SPM_GetMainProcessStaTblSize(),
                         TAF_SPM_GetMainProcessStaTbl(),
                         VOS_NULL_PTR,
                         TAF_SPM_InitFsmCtx_Main);

    /* service ctrl״̬��ע�� */
    TAF_FSM_RegisterFsm(TAF_SPM_GetServiceCtrlFsmDescAddr(),
                         "TAF_SPM:FSM:ServiceCtrlProcess",
                         TAF_SPM_GetServiceCtrlStaTblSize(),
                         TAF_SPM_GetServiceCtrlProcessStaTbl(),
                         VOS_NULL_PTR,
                         TAF_SPM_InitFsmCtx_ServiceCtrl);


    return;
}

/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-14, begin */
/*****************************************************************************
 �� �� ��  : TAF_SPM_PreProcessMsg
 ��������  : SPM��ϢԤ����
 �������  : ulEventType  :��Ϣ����
             pstMsg       :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:Ԥ�������
             VOS_FALSE:����Ҫ����״̬���д���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��12��14��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_SPM_PreProcessMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_FSM_DESC_STRU                  *pstFsmDesc = VOS_NULL_PTR;
    TAF_ACTION_FUNC                     pActFun;
    VOS_UINT32                          ulRet;

    ulRet   = VOS_TRUE;

    TAF_INFO_LOG1(WUEPS_PID_TAF,"TAF_SPM_PreProcessMsg", ulEventType);

    /* ��ϢԤ���� */
    pstFsmDesc = TAF_SPM_GetPreFsmDescAddr();

    /* ����״̬ת�Ʊ��е���Ӧ�Ķ��������� */
    pActFun = TAF_FSM_FindAct(pstFsmDesc, TAF_SPM_MAIN_STA_PREPROC, ulEventType);

    if (VOS_NULL_PTR != pActFun )
    {
        /* Ԥ������Ϣ,��Ϊ������Ϣ,һ��ΪԤ��������ͷ���,����һ��ΪԤ����
        ������,��Ȼ��Ҫ���е�״̬���м�������,��˴˴�ֱ��ͨ����������Ԥ��
        ��������Ƿ���Ҫ����״̬������*/
        ulRet = (*pActFun) ( ulEventType, (struct MsgCB*)pstMsg);
        return ulRet;
    }

    /* ��Ϣδ������������������ */
    return VOS_FALSE;
}
/* Added by s00217060 for VoLTE_PhaseIII  ��Ŀ, 2013-12-14, end */


/*****************************************************************************
 �� �� ��  : TAF_SPM_ProcessMsgInFsm
 ��������  : ����Ϣ����״̬������
 �������  : ulEventType: ��Ϣ�¼�����
             pstMsg     : ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��8��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcessMsgInFsm(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucFsmIndex;
    VOS_UINT8                           ucNewFsmIndex;
    VOS_UINT16                          usClientId;

    ulRet       = VOS_FALSE;
    usClientId  = TAF_SPM_INVALID_CLIENT_ID;
    ucFsmIndex  = TAF_SPM_INVALID_CLIENT_ID_ENTITY_FSM_INDEX;

    /* ��ȡ��client ID�����ʵ��״̬���н��в�����ͬ client ID,����ֱ����main״̬���н��д��� */
    if (VOS_TRUE == TAF_SPM_GetClientId(pstMsg, &usClientId))
    {
        ucFsmIndex = TAF_SPM_GetEntityFsmIndexByClientId(usClientId);
    }

    /* ״̬��������Ч,˵������ͬclient ID��ʵ��״̬�������� */
    if (TAF_SPM_INVALID_CLIENT_ID_ENTITY_FSM_INDEX != ucFsmIndex)
    {
        /* ���õ�ǰclient IDʵ��״̬����client ID */
        TAF_SPM_SetCurrEntityFsmClientId(usClientId);

        /* ���õ�ǰclient IDʵ��״̬������������ */
        TAF_SPM_SetCurrEntityFsmAddr(ucFsmIndex);

        /* ��Ϣ����client IDʵ��״̬������ */
        ulRet   = TAF_SPM_ProcessMsgInEntityFsm(ucFsmIndex, ulEventType, pstMsg);

        return ulRet;
    }

    /* ������Ч˵��δ�ҵ���ͬclient id��״̬��,��Ҫ��main�м������� */
    ulRet = TAF_SPM_FSM_ProcessEvent(TAF_SPM_MAIN_STA_IDLE, ulEventType, pstMsg, TAF_SPM_GetMainFsmDescAddr());

    /* �Ѿ�������ɷ��� */
    if (VOS_FALSE == ulRet)
    {
        return VOS_FALSE;
    }

    /* ˵���п���������״̬��,��Ҫ��ȡ�µĿ���client IDʵ��״̬������  */
    ucNewFsmIndex = TAF_SPM_GetEntityFsmIndexByClientId(usClientId);

    /* ������Ч��ȡ��ָ����״̬��ID */
    if (TAF_SPM_INVALID_CLIENT_ID_ENTITY_FSM_INDEX != ucNewFsmIndex)
    {
        /* ���õ�ǰclient IDʵ��״̬����client ID */
        TAF_SPM_SetCurrEntityFsmClientId(usClientId);

        /* ���õ�ǰclient IDʵ��״̬������������ */
        TAF_SPM_SetCurrEntityFsmAddr(ucNewFsmIndex);

        /* ��״̬���п�������״̬��,�������״̬��,��Ϣ����Ҫ����״̬������ */
        ulRet = TAF_SPM_ProcessMsgInEntityFsm(ucNewFsmIndex, ulEventType, pstMsg);
    }

    return ulRet;
}


/*****************************************************************************
 �� �� ��  : TAF_SPM_ProcessMsgInEntityFsm
 ��������  : ��client IDʵ��״̬�������Ϣ���д���
 �������  : ucFsmIndex   :״̬������
             ulEventType  :��Ϣ�¼�����
             pstMsg       :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE:  ��Ϣ�������
             VOS_FALSE: ��Ϣδ������ɣ�����Ҫ��������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��8��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_SPM_ProcessMsgInEntityFsm(
    VOS_UINT8                           ucFsmIndex,
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRet;
    TAF_SPM_FSM_CTX_STRU               *pstCurrSubFsm = VOS_NULL_PTR;

    /*  ��ȡָ��������Sub״̬�� */
    pstCurrSubFsm   = TAF_SPM_GetEntityFsmCtxAddrByFsmIndex(ucFsmIndex);

    ulRet           = TAF_SPM_FSM_ProcessEvent(pstCurrSubFsm->ulState, ulEventType,
                                               pstMsg, pstCurrSubFsm->pstFsmDesc);

    return ulRet;
}


/*****************************************************************************
 �� �� ��    : TAF_SPM_FSM_ProcessEvent
 ��������    : ״̬�����¼�������
 �������    : ulCurState :��ǰ״̬
               ulEventType:�����¼�
               ulMsgID    :��ϢID
               pRcvMsg    :��Ϣָ��
               pstFsmDesc :״̬��������
 �������    :
 ����ֵ      : VOS_UINT32:�����Ƿ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��5��8��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

 *****************************************************************************/
VOS_UINT32 TAF_SPM_FSM_ProcessEvent(
    VOS_UINT32                          ulCurState,
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pRcvMsg,
    TAF_FSM_DESC_STRU                  *pstFsmDesc
)
{
    TAF_ACTION_FUNC                     pActFun = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    TAF_INFO_LOG2(WUEPS_PID_TAF,"TAF_SPM_FSM_ProcessEvent", ulCurState, ulEventType);

    /* ����״̬ת�Ʊ��е���Ӧ�Ķ��������� */
    pActFun = TAF_FSM_FindAct(pstFsmDesc, ulCurState, ulEventType);

    if (VOS_NULL_PTR != pActFun )
    {
        /* ������ص��¼���������Ϊ��,�����������¼����� */
        ulRet   = (*pActFun) ( ulEventType,(struct MsgCB*)pRcvMsg);
        TAF_INFO_LOG1(WUEPS_PID_TAF,"TAF_SPM_FSM_ProcessEvent", ulRet);
        return ulRet;
    }

    /* ��Ϣδ������������������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_Init
 ��������  : SPM��ʼ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��9��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_SPM_Init(VOS_VOID)
{
    /* ��ʼ��SPMģ��CTX */
    TAF_SPM_InitCtx(TAF_SPM_GetSpmCtxAddr());

    /*ע��״̬��*/
    TAF_SPM_RegFsm();

    /* ��ȡNV���� */
    TAF_SPM_ReadNvimInfo();

    /* Ĭ��ֵ����MAIN״̬�� */
    TAF_SPM_FSM_InitMainFsm(TAF_SPM_FSM_MAIN, TAF_SPM_GetMainFsmDescAddr(), TAF_SPM_MAIN_STA_IDLE);
}

/*****************************************************************************
 �� �� ��  : TAF_SPM_InitCtx
 ��������  : SPM CTXģ���ʼ��
 �������  : pstSpmCtx-SPMģ��������
 �������  :
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��5��8��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��11��28��
   ��    ��   : j00174725
   �޸�����   : ��ǿ�Ͷ෽ͨ��
*****************************************************************************/
VOS_VOID  TAF_SPM_InitCtx(
    TAF_SPM_CONTEXT_STRU               *pstSpmCtx
)
{
    /* ��ʼ�����е�ʵ��״̬�� */
    TAF_SPM_InitEntityFsm();

    TAF_SPM_InitMainFsm();

    /* ��ʼ��SPM��ʱ�������� */
    TAF_SPM_InitAllTimers(pstSpmCtx->astSpmTimerCtx);

    TAF_SPM_InitMainCtrlInfo(&(pstSpmCtx->stMainCtrlInfo));

    TAF_SPM_InitServiceCtrlCfgInfo(&(pstSpmCtx->stServiceCtrlCfgInfo));

    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-28, begin */
    TAF_SPM_InitServiceReqBufferMsgQueue();
    /* Added by y00245242 for V3R3C60_eCall��Ŀ, 2014-4-28, end */

    /* Added by y00245242 for VoLTE_PhaseII  ��Ŀ, 2013-9-22, begin */
#if (FEATURE_IMS == FEATURE_ON)
    TAF_SPM_InitDomainSelCtx(&(pstSpmCtx->stDomainSelCtx));

    TAF_SPM_InitEconfInfo();
#endif
    /* Added by y00245242 for VoLTE_PhaseII  ��Ŀ, 2013-9-22, end */
}


/*lint -restore */



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

