
/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafMmaCtx.c
  �� �� ��   : ����
  ��    ��   : w00176964
  ��������   : 2013��07��10��
  ����޸�   :
  ��������   : TAF MMA CTX�ļ�
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2013��7��10��
    ��    ��   : W00176964
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "PsLib.h"

#include "PsCommonDef.h"
#include "TafMmaCtx.h"
#include "TafMmaFsmMainTbl.h"
#include "TafMmaFsmPhoneModeTbl.h"
#include "TafLog.h"
#include "TafMmaSndInternalMsg.h"
#include "Taf_Tafm_Remote.h"
#include "TafMmaMntn.h"
#include "TafOamInterface.h"
#include "MmaUphyInterface.h"

#include "TafSdcLib.h"

#include "TafMmaFsmImsSwitchTbl.h"

#include "TafMmaFsmSysCfgTbl.h"
#include "TafSdcCtx.h"
#include "MmaAppLocal.h"
#include "TafCdmaPlusTranslate.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_CTX_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* MMA CTX,���ڱ���MMA״̬��,������ */
TAF_MMA_CONTEXT_STRU                    g_stTafMmaCtx;

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
 �� �� ��  : TAF_MMA_SaveCurEntryMsg
 ��������  : ���浱ǰ״̬���������Ϣ
 �������  : ulEventType            :�����Ϣ����
             pstMsg                 :�����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013-07-19
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ��õ�ǰ����MMA�����Ϣ�Ļ�������ַ */
    pstEntryMsg                 = TAF_MMA_GetCurrFsmMsgAddr();
    pstMsgHeader                = (MSG_HEADER_STRU*)pstMsg;

    ulLen                       = pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH;

    /* ����ǰ����������Ϣ������Context��Ӧ�Ļ����� */
    PS_MEM_CPY( pstEntryMsg->aucEntryMsgBuffer, pstMsg, ulLen );

    /* ��дContext�еĲ��� */
    pstEntryMsg->ulEventType    =   ulEventType;

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_FSM_SetCurrState
 ��������  : ���õ�ǰ��ҪǨ�Ƶ�״̬
 �������  : ulCurrState:��ǰǨ�Ƶ�״̬
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��10��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_MMA_FSM_SetCurrState(
    VOS_UINT32                          ulCurrState
)
{
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    /* ��ȡ��ǰ��״̬��Ϣ */
    pstCurFsm                   = TAF_MMA_GetCurFsmAddr();

    /* ���õ�ǰ״̬ */
    pstCurFsm->ulState          = ulCurrState;

    /*  ��ӡ��ǰ��L1��L2״̬ */
    TAF_MMA_LogFsmInfo();

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_FSM_GetFsmTopState
 ��������  : ��ȡ״̬�������״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬���Ķ���״̬
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��10��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_FSM_GetFsmTopState( VOS_VOID )
{
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;
    VOS_UINT32                          ulState;

    /* ��ȡ��ǰ״̬�� */
    pstCurFsm               = TAF_MMA_GetCurFsmAddr();
    ulState                 = pstCurFsm->ulState;

    return ulState;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetMmaCtxAddr
 ��������  : ��ȡ��ǰMMA��CTX
 �������  : ��
 �������  : ��
 �� �� ֵ  : ���ص�ǰMMA��CTX��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_CONTEXT_STRU* TAF_MMA_GetMmaCtxAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetRegCtrlAddr
 ��������  : ��ȡ��ǰ״̬����ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬����ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��12��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_FSM_CTX_STRU* TAF_MMA_GetCurFsmAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stCurFsm);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetFsmStackAddr
 ��������  : ��ȡ��ǰ״̬��ջ��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬��ջ��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��13��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_FSM_STACK_STRU* TAF_MMA_GetFsmStackAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stFsmStack);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetCurFsmDesc
 ��������  : ��ȡ��ǰ״̬����ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬����ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��12��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_FSM_DESC_STRU* TAF_MMA_GetCurFsmDesc(VOS_VOID)
{
    return (TAF_MMA_GetMmaCtxAddr()->stCurFsm.pstFsmDesc);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetCurrFsmMsgAddr
 ��������  : ��ȡ��ǰ״̬�������Ϣ�ĵ�ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬�������Ϣ�ĵ�ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��13��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_ENTRY_MSG_STRU* TAF_MMA_GetCurrFsmMsgAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.stEntryMsg);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetCurrFsmMsgAddr
 ��������  : ��ȡ��ǰ״̬����ID
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬����ID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_FSM_ID_ENUM_UINT32 TAF_MMA_GetCurrFsmId(VOS_VOID)
{
    return (TAF_MMA_GetMmaCtxAddr()->stCurFsm.enFsmId);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetCachMsgBufferAddr
 ��������  : ��ȡ��ǰ�Ļ�����Ϣ��ַ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF MMA������Ϣ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_MSG_QUEUE_STRU* TAF_MMA_GetCachMsgBufferAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stBufferEntryMsgQueue);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_FSM_PushFsm
 ��������  : ��״̬������ѹջ
 �������  : *pstFsmStack:״̬��ջ
             *pstNewFsm:��Ҫѹ���״̬��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_FSM_PushFsm(
    TAF_MMA_FSM_STACK_STRU              *pstFsmStack,
    TAF_MMA_FSM_CTX_STRU                *pstNewFsm
)
{
    TAF_MMA_FSM_CTX_STRU                *pstCurFsm;

    if ( (VOS_NULL_PTR == pstFsmStack)
      || (VOS_NULL_PTR == pstNewFsm) )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,
                       "TAF_MMA_FSM_PushFsm,Para null ptr,pstFsmStack,pstNewFsm");

        return;
    }

    if ( pstFsmStack->usStackDepth >= TAF_MMA_MAX_STACK_DEPTH )
    {
        TAF_ERROR_LOG1(WUEPS_PID_MMA,
                       "TAF_MMA_FSM_PushFsm,Fsm Stack Depth Error!",
                       pstFsmStack->usStackDepth);

        return;
    }

    pstCurFsm               = &((pstFsmStack->astFsmStack)[pstFsmStack->usStackDepth]);

    /* ����ǰ״̬������CTX����Ҫ�������� */
    PS_MEM_CPY(pstCurFsm, pstNewFsm, sizeof(TAF_MMA_FSM_CTX_STRU));

    pstFsmStack->usStackDepth++;


    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_FSM_PopFsm
 ��������  : ��״̬�����г�ջ
 �������  : ��
             ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_FSM_PopFsm( VOS_VOID )
{
    VOS_UINT16                          usPopFsmPos;
    TAF_MMA_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    /* ���ݲ���״̬��ջ������״̬����ȡ��ǰ״̬��������ַ  */
    pstFsmStack                     = TAF_MMA_GetFsmStackAddr();
    pstCurFsm                       = TAF_MMA_GetCurFsmAddr();

    /* ջ�ѿ� */
    if ( 0 == (pstFsmStack->usStackDepth) )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_FSM_PopFsm,FSM Stack empty");

        return;
    }

    pstFsmStack->usStackDepth--;
    usPopFsmPos   = pstFsmStack->usStackDepth;

    /* ���õ�ǰ״̬�� */
    PS_MEM_CPY(pstCurFsm,
              &((pstFsmStack->astFsmStack)[usPopFsmPos]),
              sizeof(TAF_MMA_FSM_CTX_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_LoadSubFsmInfo
 ��������  : ����L2״̬������Ϣ
 �������  : enFsmId:L2״̬��ID
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��13��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��02��04��
    ��    ��   : f00179208
    �޸�����   : IMS��̬����������Ŀ
*****************************************************************************/
VOS_VOID  TAF_MMA_LoadSubFsm(
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId,
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm
)
{
    switch ( enFsmId )
    {
        case TAF_MMA_FSM_PHONE_MODE :
            pstCurFsm->ulState                  = TAF_MMA_PHONE_MODE_STA_INIT;
            pstCurFsm->pstFsmDesc               = TAF_MMA_GetPhoneModeFsmDescAddr();
            break;

#if (FEATURE_IMS == FEATURE_ON)
        case TAF_MMA_FSM_IMS_SWITCH :
            pstCurFsm->ulState                  = TAF_MMA_IMS_SWITCH_STA_INIT;
            pstCurFsm->pstFsmDesc               = TAF_MMA_GetImsSwitchFsmDescAddr();
            break;
#endif

        case TAF_MMA_FSM_SYS_CFG :
            pstCurFsm->ulState                  = TAF_MMA_SYS_CFG_STA_INIT;
            pstCurFsm->pstFsmDesc               = TAF_MMA_GetSysCfgFsmDescAddr();
            break;


        default:
            TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_LoadSubFsm:Invalid Fsm Id");
            return;
    }


    /*ִ�г�ʼ��sub״̬���ĺ���*/
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_FSM_InitSubFsm
 ��������  : MMA����һ��L2��L3��״̬�����������̵�ͬʱ����״̬�Լ�������ʱ��?
              �ú��������ѹջ����,�������Ҫ����Э��ջѹջ,���뱣֤�˳�ǰ����
 �������  : enFsmId:L2״̬��ID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��12��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_FSM_InitSubFsm(
    TAF_MMA_FSM_ID_ENUM_UINT32          enFsmId
)
{
    TAF_MMA_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;


    pstCurFsm                           = TAF_MMA_GetCurFsmAddr();
    pstFsmStack                         = TAF_MMA_GetFsmStackAddr();

    /*  ��ӡѹջǰ��main��sub״̬ */
    TAF_MMA_LogFsmInfo();

    /* ����ǰ״̬��ѹջ���� */
    TAF_MMA_FSM_PushFsm(pstFsmStack, pstCurFsm);

    /* ���õ�ǰ״̬�� */
    pstCurFsm->enFsmId                  = enFsmId;

    /* ����sub״̬�� */
    TAF_MMA_LoadSubFsm(enFsmId, pstCurFsm);

    /*  ��ӡ��ǰ��main��sub״̬ */
    TAF_MMA_LogFsmInfo();
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_FSM_QuitSubFsm
 ��������  : ����L2״̬��������������̣�״̬������״̬ջ
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��13��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_FSM_QuitSubFsm( VOS_VOID )
{
    TAF_MMA_FSM_CTX_STRU               *pstCurFsm   = VOS_NULL_PTR;

    pstCurFsm                           = TAF_MMA_GetCurFsmAddr();

    /* QUITʱ��յ�ǰsub״̬����CTX */
    if (VOS_NULL_PTR != pstCurFsm->pstFsmDesc->pfInitHandle)
    {
        pstCurFsm->pstFsmDesc->pfInitHandle();
    }

    /*  ��ӡѹջǰ��main��sub״̬ */
    TAF_MMA_LogFsmInfo();

    /* ״̬����ջ���� */
    TAF_MMA_FSM_PopFsm();

    /*  ��ӡ��ǰ��main��sub״̬ */
    TAF_MMA_LogFsmInfo();

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetFsmStackDepth
 ��������  : ��ȡ��ǰЭ��ջ��ջ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ǰ״̬�������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��12��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT16  TAF_MMA_GetFsmStackDepth( VOS_VOID )
{
    TAF_MMA_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = TAF_MMA_GetFsmStackAddr();

    return pstFsmStack->usStackDepth;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsExistCacheMsg
 ��������  : �жϵ�ǰ��Ϣ�Ƿ��Ѿ�����
 �������  : ulEventType:��ϢID
 �������  : pulIndex   :�������Ϣ����
 �� �� ֵ  : VOS_TRUE:���ڻ������Ϣ
             VOS_FALSE:�����ڻ������Ϣ
 ���ú���  :pulIndex
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��30��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_MMA_IsExistCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_UINT32                         *pulIndex
)
{
    TAF_MMA_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstMsgQueue                         = TAF_MMA_GetCachMsgBufferAddr();
   *pulIndex                           = 0;

    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum ; i++ )
    {
        if ( ulEventType == pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType)
        {
            *pulIndex   = i;
            return VOS_TRUE;
        }
    }

    TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_IsExistCacheMsg:not match MSG");

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsNeedCacheMsg
 ��������  : �Ƚϻ�����Ϣ�뵱ǰ��Ϣ�����ȼ�
 �������  : ulEventType:��Ϣ����
             pstMsg     :��Ϣ�׵�ַ
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����Ҫ������
             VOS_TRUE:��Ϣ��Ҫ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��30��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_MMA_IsNeedCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT32                          ulIndex;

    switch (ulEventType)
    {
        /* ��ǰ��״ָ̬ʾ��Ϣ�Ļ���ֻ��Ҫ����һ�� */
        case TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND):

            if (VOS_TRUE == TAF_MMA_IsExistCacheMsg(TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND), &ulIndex))
            {
                return VOS_FALSE;
            }

            break;

        default:
            break;
    }

    /* Ĭ�Ϸ��ر������Ϣ */
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SaveCacheMsgInMsgQueue
 ��������  : ��������Ϣ����Ļ����ڴ����
 �������  : ulEventType:��ϢID+PID
             pMsg      :��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  -- ����ɹ�
             VOS_FALSE -- ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��13��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���

  2.��    ��   : 2015��4��16��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
VOS_UINT32 TAF_MMA_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
)
{
    TAF_MMA_MSG_QUEUE_STRU              *pstMsgQueue   = VOS_NULL_PTR;
    MSG_HEADER_STRU                     *pstMsgHeader  = VOS_NULL_PTR;

    pstMsgHeader = (MSG_HEADER_STRU*)pstMsg;

    pstMsgQueue = TAF_MMA_GetCachMsgBufferAddr();

    if ( pstMsgQueue->ucCacheMsgNum >= TAF_MMA_MAX_MSG_QUEUE_NUM )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SaveCacheMsgInMsgQueue:buffer full");

        TAF_MMA_LogBufferQueueMsg(VOS_TRUE);

        return VOS_FALSE;
    }

    /* �Ƚ���Ϣ���ȼ�,�ж��Ƿ���Ҫ�����ڻ������ */
    if (VOS_FALSE == TAF_MMA_IsNeedCacheMsg(ulEventType, pstMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SaveCacheMsgInMsgQueue:already exist msg");

        return VOS_FALSE;
    }

    pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.ulEventType   = ulEventType;
    PS_MEM_CPY((pstMsgQueue->astMsgQueue[pstMsgQueue->ucCacheMsgNum].stMsgEntry.aucEntryMsgBuffer),
               pstMsg,
               pstMsgHeader->ulLength + VOS_MSG_HEAD_LENGTH);
    pstMsgQueue->ucCacheMsgNum++;

    TAF_MMA_LogBufferQueueMsg(VOS_FALSE);

    TAF_INFO_LOG1(WUEPS_PID_MMA, "TAF_MMA_SaveCacheMsgInMsgQueue:Cache Num", pstMsgQueue->ucCacheMsgNum);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ClearCacheMsg
 ��������  : ���ָ���Ļ�����Ϣ
 �������  : ulEventType:������󻺴����Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��13��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_MMA_ClearCacheMsg(
    VOS_UINT32                          ulEventType
)
{
    TAF_MMA_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_INT8                            i;
    VOS_INT8                            cCachePos;

    pstMsgQueue                         = TAF_MMA_GetCachMsgBufferAddr();
    cCachePos                           = -1;

    /* ���ҵ���Ҫ������Ļ��� */
    for ( i = 0 ; i < pstMsgQueue->ucCacheMsgNum ; i++ )
    {
        if ( ulEventType == pstMsgQueue->astMsgQueue[i].stMsgEntry.ulEventType )
        {
            PS_MEM_SET(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                       0x00,
                       sizeof(TAF_MMA_ENTRY_MSG_STRU));

            cCachePos = (VOS_INT8)i;
        }
    }

    /* δ�ҵ�����Ϣ����ֱ�ӷ��� */
    if ( -1 == cCachePos )
    {
        TAF_INFO_LOG1(WUEPS_PID_MMA, "TAF_MMA_ClearCacheMsg:invalid msg type", ulEventType);
        return;
    }

    /* Ϊ��֤�����ȳ�,��Ҫ���������Ϣ�Ƶ�ǰ�� */
    for ( i = cCachePos ; i < (pstMsgQueue->ucCacheMsgNum - 1) ; i++ )
    {
        /* COPY��Ϣ���� */
        PS_MEM_CPY(&(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                   &(pstMsgQueue->astMsgQueue[i + 1].stMsgEntry),
                   sizeof(TAF_MMA_ENTRY_MSG_STRU));
    }

    /* �����������һ */
    pstMsgQueue->ucCacheMsgNum--;

    /* ����ǰ�������ӡ���� */
    TAF_MMA_LogBufferQueueMsg(VOS_FALSE);

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_InitFsmCtx_PhoneMode
 ��������  : ��ʼ���ֻ�ģʽ״̬��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��13��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID  TAF_MMA_InitFsmCtx_PhoneMode(VOS_VOID)
{
    TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_NO_ERROR);


    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_InitFsmCtx_SysCfg
 ��������  : ��ʼ��SYS CFG״̬����������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��9��
    ��    ��   : l60609
    �޸�����   : �����ɺ���
  2.��    ��   : 2015��12��3��
    ��    ��   : w00176964
    �޸�����   : DTS2015061601845:����ԭʼSYSCFG�����Ĳ�������
*****************************************************************************/
VOS_VOID  TAF_MMA_InitFsmCtx_SysCfg(VOS_VOID)
{
    TAF_MMA_FSM_SYS_CFG_CTX_STRU       *pstSysCfgCtx = VOS_NULL_PTR;

    pstSysCfgCtx = &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx);

    PS_MEM_SET(pstSysCfgCtx, 0 , sizeof(TAF_MMA_FSM_SYS_CFG_CTX_STRU));

    pstSysCfgCtx->usOperType   = 0;
    pstSysCfgCtx->ucAttachOpId = 0xFF;

    pstSysCfgCtx->usOrigOperType = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_InitCurrFsmCtx
 ��������  : ��ʼ����ǰ״̬��������
 �������  : ��
 �������  : pstCurrFsmCtx:��ǰ״̬����������Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��13��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_MMA_InitCurrFsmCtx(
    TAF_MMA_FSM_CTX_STRU                *pstCurrFsmCtx
)
{
    pstCurrFsmCtx->enFsmId                  =   TAF_MMA_FSM_MAIN;
    pstCurrFsmCtx->pstFsmDesc               =   TAF_MMA_GetMainFsmDescAddr();
    pstCurrFsmCtx->ulState                  =   TAF_MMA_MAIN_STA_IDLE;
    pstCurrFsmCtx->stEntryMsg.ulEventType   =   0;

    PS_MEM_SET(pstCurrFsmCtx->stEntryMsg.aucEntryMsgBuffer,
               0x00,
               TAF_MMA_MAX_MSG_BUFFER_LEN);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_InitFsmStackCtx
 ��������  : ��ʼ��״̬��ջ������
 �������  : ��
 �������  : pstFsmStack:״̬��ջ��Ϣ
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��12��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_MMA_InitFsmStackCtx(
    TAF_MMA_FSM_STACK_STRU              *pstFsmStack
)
{
    VOS_UINT32                          i;

    pstFsmStack->usStackDepth   = 0;
    pstFsmStack->usStackPopFlg  = VOS_FALSE;

    for ( i = 0 ; i < TAF_MMA_MAX_STACK_DEPTH ; i++ )
    {
        pstFsmStack->astFsmStack[i].pstFsmDesc  = VOS_NULL_PTR;
        pstFsmStack->astFsmStack[i].enFsmId     = TAF_MMA_FSM_BUTT;
        pstFsmStack->astFsmStack[i].ulState     = TAF_MMA_MAIN_STA_BUTT;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_InitInternalBuffer
 ��������  : ����ڲ�������Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��15��
   ��    ��   : w00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_MMA_InitInternalBuffer(
    TAF_MMA_MSG_QUEUE_STRU             *pstBufferEntryMsgQueue
)
{
    pstBufferEntryMsgQueue->ucCacheMsgNum   = 0;
    PS_MEM_SET(pstBufferEntryMsgQueue->astMsgQueue,
               0x00,
               sizeof(TAF_MMA_CACH_MSG_INFO_STRU)*TAF_MMA_MAX_MSG_QUEUE_NUM);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_InitInternalMsgQueue
 ��������  : ��ʼ��MMA_CTX���ڲ���Ϣ����
 �������  : pstInternalMsgQueue:�ڲ���Ϣ����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��19��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_MMA_InitInternalMsgQueue(
    TAF_MMA_INTERNAL_MSG_QUEUE_STRU     *pstInternalMsgQueue                   /* MMA���ڲ���Ϣ���� */
)
{
    VOS_UINT32                          i;

    pstInternalMsgQueue->ucHeader   = 0;
    pstInternalMsgQueue->ucTail     = 0;

    for ( i = 0 ; i < TAF_MMA_MAX_MSG_QUEUE_SIZE; i++ )
    {
        pstInternalMsgQueue->astMmaMsgQueue[i].usMsgID    = TAF_MMA_INVALID_INTERNAL_MSG_ID;
        PS_MEM_SET(pstInternalMsgQueue->astMmaMsgQueue[i].aucBuf,
                   0x00,
                   TAF_MMA_MAX_MSG_BUFFER_LEN);
    }

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_InitMaintainInfo
 ��������  : ��ʼ��MMA_CTX�п�ά�ɲ���Ϣ
 �������  :
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��9��4��
   ��    ��   : s00217060
   �޸�����   : �����ɺ���

 2.��    ��   : 2014��12��3��
   ��    ��   : w00167002
   �޸�����   : ��ӡ���¿�������Ĭ�ϲ�������ӡ
*****************************************************************************/
VOS_VOID  TAF_MMA_InitMaintainInfo(
    TAF_MMA_MAINTAIN_CTX_STRU          *pstMaintainInfo
)
{
    pstMaintainInfo->ucMmaLogInfoFlag   = VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_InitExternalModuleInitStatus
 ��������  : ��ʼ������������ʼ��״̬
 �������  : ��ʼ��״ָ̬��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2013��3��20��
   ��    ��   : y00176023
   �޸�����   : �����ɺ���
 2.��    ��   : 2014��6��4��
   ��    ��   : w00167002
   �޸�����   : DTS2014060403551:��ʱ�޸�
 3.��    ��   : 2014��7��22��
   ��    ��   : s00217060
   �޸�����   : DTS2014072200696:Phy��ʼ��
 4.��    ��   : 2015��1��28��
   ��    ��   : s00217060
   �޸�����   : DTS2015012808702�޸ģ���������PHY��ʼ����������ܻ�������ʱ���ײ㻹δ��ʼ����ɣ�����λ

*****************************************************************************/
VOS_VOID TAF_MMA_InitExternalModuleInitStatus(
    TAF_MMA_EXTERNAl_MODULE_INIT_STATUS_STRU      *pstInitStatusctx
)
{
    PS_MEM_SET(pstInitStatusctx, 0, sizeof(TAF_MMA_EXTERNAl_MODULE_INIT_STATUS_STRU));

    /* �������ȴ�������ʼ��������DSDS�����һ�� */
    pstInitStatusctx->enPhyInitStatus      = MMA_UPHY_INIT_STATUS_BUTT;

    return;

}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetPhoneModeCtrl
 ��������  : ��ȡ��ǰphone mode ����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : phone mode����������
 ���ú���  :
 ��������  :
 �޸���ʷ      :
 1.��    ��   : 2013-07-12
   ��    ��   : w00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
TAF_MMA_PHONE_MODE_CTRL_CTX_STRU *TAF_MMA_GetPhoneModeCtrl(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stPhoneModeCtrl);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetCacheNum
 ��������  : ��ȡ��ǰ���ڵĻ������
 �������  : ��
 �������  : ��ǰ���ڵĻ������
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��9��29��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_MMA_GetCacheNum( VOS_VOID )
{
    TAF_MMA_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = TAF_MMA_GetCachMsgBufferAddr();

    return pstMsgQueue->ucCacheMsgNum;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetCachedMsgPrio
 ��������  : ��ȡ������Ϣ�����ȼ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  : ������Ϣ�����ȼ�����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��22��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���
 2.��    ��   : 2015��9��8��
   ��    ��   : z00161729
   �޸�����   : ֧��LTE CSG��������
*****************************************************************************/
TAF_MMA_MSG_CACHE_PRIO_ENUM_UINT8   TAF_MMA_GetCachedMsgPrio(
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    TAF_MMA_MSG_CACHE_PRIO_ENUM_UINT8   enPrio;

    switch (pstEntryMsg->ulEventType)
    {
        case TAF_BuildEventType(WUEPS_PID_SPY, OAM_MMA_PHONE_MODE_SET_REQ):
        case TAF_BuildEventType(CCPU_PID_CBT, OAM_MMA_PHONE_MODE_SET_REQ):
        /* Modified by w00167002 for L-C��������Ŀ, 2014-2-14, begin */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ):
        /* Modified by w00167002 for L-C��������Ŀ, 2014-2-14, end */

            enPrio = TAF_MMA_MSG_CACHE_PRIO_HIGH;
            break;

        case TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND):

            enPrio = TAF_MMA_MSG_CACHE_PRIO_MIDDLE;
            break;

        /* Modified by w00167002 for L-C��������Ŀ, 2014-2-14, begin */

        /* ��ѯԤ�����ȷ�����  */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_SYS_CFG_SET_REQ):
        /* Modified by w00167002 for L-C��������Ŀ, 2014-2-14, end */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_LIST_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_ATTACH_REQ):

        /* Modified by w00167002 for L-C��������Ŀ, 2014-2-17, begin */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_DETACH_REQ):
        /* Modified by w00167002 for L-C��������Ŀ, 2014-2-17, end */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PLMN_AUTO_RESEL_REQ):

#if (FEATURE_ON == FEATURE_CSG)
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_CSG_LIST_SEARCH_REQ):
#endif
        default:

            enPrio = TAF_MMA_MSG_CACHE_PRIO_LOW;
            break;
    }

    return enPrio;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_GetNextPrioCachedMsg
 ��������  : ��ȡ�������ȼ��Ļ�����Ϣ
 �������  : ��
 �������  : pstEntryMSg:��ǰ���ȼ��Ļ�����Ϣ
 �� �� ֵ  : VOS_TRUE:��ȡ�ɹ�
             VOS_FALSE:��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��12��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  TAF_MMA_GetNextPrioCachedMsg(
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg,
    TAF_MMA_MSG_CACHE_PRIO_ENUM_UINT8   enPrio
)
{
    TAF_MMA_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstMsgQueue                         = TAF_MMA_GetCachMsgBufferAddr();

    for (i = 0; i < pstMsgQueue->ucCacheMsgNum; i++)
    {
        if (enPrio == TAF_MMA_GetCachedMsgPrio(&pstMsgQueue->astMsgQueue[i].stMsgEntry))
        {
            PS_MEM_CPY(pstEntryMsg,
                       &(pstMsgQueue->astMsgQueue[i].stMsgEntry),
                       sizeof(TAF_MMA_ENTRY_MSG_STRU));

            /* ��Ϣ�Ѿ�ȡ���������ǰ���� */
            TAF_MMA_ClearCacheMsg(pstEntryMsg->ulEventType);

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetNextCachedMsg
 ��������  : ��ȡ��ǰ��Ҫ����Ļ���
 �������  : ��
 �������  : pstEntryMSg:��ǰ���ȼ���ߵĻ�����Ϣ
 �� �� ֵ  : VOS_TRUE:��ȡ�ɹ�
             VOS_FALSE:��ȡʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��12��
   ��    ��   : W00176964
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32  TAF_MMA_GetNextCachedMsg(
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg
)
{
    TAF_MMA_MSG_QUEUE_STRU             *pstMsgQueue = VOS_NULL_PTR;

    pstMsgQueue                         = TAF_MMA_GetCachMsgBufferAddr();

    if (0 == pstMsgQueue->ucCacheMsgNum )
    {
        TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_GetNextCachedMsg:Empty buffer");

        return VOS_FALSE;
    }

    if (VOS_TRUE == TAF_MMA_GetNextPrioCachedMsg(pstEntryMsg, TAF_MMA_MSG_CACHE_PRIO_HIGH))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == TAF_MMA_GetNextPrioCachedMsg(pstEntryMsg, TAF_MMA_MSG_CACHE_PRIO_MIDDLE))
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE == TAF_MMA_GetNextPrioCachedMsg(pstEntryMsg, TAF_MMA_MSG_CACHE_PRIO_LOW))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_SetFsmStackPopFlg
 ��������  : ����״̬��ջpop��־
 �������  : ucStackPopFlg:ջpop��־
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��13��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_MMA_SetFsmStackPopFlg(
    VOS_UINT16                          ucStackPopFlg
)
{
    TAF_MMA_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = TAF_MMA_GetFsmStackAddr();

    pstFsmStack->usStackPopFlg  = ucStackPopFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetFsmStackPopFlg
 ��������  : ��ȡ״̬��ջpop��־
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��13��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT16  TAF_MMA_GetFsmStackPopFlg( VOS_VOID )
{
    TAF_MMA_FSM_STACK_STRU             *pstFsmStack = VOS_NULL_PTR;

    pstFsmStack = TAF_MMA_GetFsmStackAddr();

    return pstFsmStack->usStackPopFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SetAutoInitPsFlg
 ��������  : �����ϵ��Զ���ʼ��Э��ջ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��13��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_MMA_SetAutoInitPsFlg(
    VOS_UINT32                          ulAutoInitPsFlg
)
{
    TAF_MMA_GetPhoneModeCtrl()->ulAutoInitPsFlg = ulAutoInitPsFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetAutoInitPsFlg
 ��������  : ��ȡ�ϵ��Զ���ʼ��Э��ջ���
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��13��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_MMA_GetAutoInitPsFlg(VOS_VOID)
{
    return (TAF_MMA_GetPhoneModeCtrl()->ulAutoInitPsFlg);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SetAutoSwitchOnFlg
 ��������  : �����ϵ��Զ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��13��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_MMA_SetAutoSwitchOnFlg(
    VOS_UINT32                          ulAutoSwitchOnFlg
)
{
    TAF_MMA_GetPhoneModeCtrl()->ulAutoSwitchOnFlg = ulAutoSwitchOnFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetAutoSwitchOnFlg
 ��������  : ��ȡ�ϵ��Զ��������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��13��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_MMA_GetAutoSwitchOnFlg(VOS_VOID)
{
    return (TAF_MMA_GetPhoneModeCtrl()->ulAutoSwitchOnFlg);
}


/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-25, begin */

/* Deleted by w00176964 for VoLTE_PhaseIII ��Ŀ, 2013-12-25, end */

/*****************************************************************************
 �� �� ��  : TAF_MMA_SetCurPhoneErrorCode_PhoneMode
 ��������  : ���õ�ǰ���ػ������еĴ�����
 �������  : usErrorCode--���ػ��Ĵ�����
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��19��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  TAF_MMA_SetCurPhoneErrorCode_PhoneMode(
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode
)
{
    /* �����ǰ״̬������PHONE MODE, �쳣��ӡ */
    if (TAF_MMA_FSM_PHONE_MODE != TAF_MMA_GetCurrFsmId())
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SetCurPhoneErrorCode_PhoneMode,ERROR:FsmId Error");
        return;
    }

    TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stPhoneModeCtx.enPhoneError = enErrorCode;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_GetCurPhoneErrorCode_PhoneMode
 ��������  : ��ȡ��ǰ�Ŀ��ػ������еĴ�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��8��19��
    ��    ��   : W00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_ERROR_CODE_ENUM_UINT32  TAF_MMA_GetCurPhoneErrorCode_PhoneMode(VOS_VOID)
{
    /* �����ǰ״̬������PHONE MODE, �쳣��ӡ */
    if (TAF_MMA_FSM_PHONE_MODE != TAF_MMA_GetCurrFsmId())
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_GetCurPhoneErrorCode_PhoneMode,ERROR:FsmId Error");
    }
    return (TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stPhoneModeCtx.enPhoneError);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetTimerCtxAddr
 ��������  : ��ȡMMA CTXģ���ж�ʱ����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : MMA CTXģ���ж�ʱ����������ָ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��7��23��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_MMA_TIMER_CTX_STRU*  TAF_MMA_GetTimerCtxAddr( VOS_VOID )
{
    return TAF_MMA_GetMmaCtxAddr()->astMmaTimerCtx;
}

/* Added by b00269685 for L-C��������Ŀ, 2014-2-14, begin */

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetOperCtxAddr
 ��������  : ��ȡMMA CTXģ����L-C������������
 �������  : ��
 �������  : ��
 �� �� ֵ  : MMA CTXģ����L-C������������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��14��
    ��    ��   : b00269685
    �޸�����   : �����ɺ���
*****************************************************************************/
TAF_MMA_OPER_CTX_STRU*  TAF_MMA_GetOperCtxAddr( VOS_VOID )
{
    return TAF_MMA_GetMmaCtxAddr()->astMmaOperCtx;
}


/* Added by b00269685 for L-C��������Ŀ, 2014-2-14, end */

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetMmaLogInfoFlag
 ��������  : ��ȡMMA CTXģ���п�ά�ɲ���Ϣ�Ƿ��ӡ��־
 �������  : ��
 �������  : ��
 �� �� ֵ  : MMA CTXģ���п�ά�ɲ���Ϣ�Ƿ��ӡ��־
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��4��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT8  TAF_MMA_GetMmaLogInfoFlag( VOS_VOID )
{
    return TAF_MMA_GetMmaCtxAddr()->stMaintainInfo.ucMmaLogInfoFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SetMmaLogInfoFlag
 ��������  : ����MMA CTXģ���п�ά�ɲ���Ϣ�Ƿ��ӡ��־
 �������  : MMA CTXģ���п�ά�ɲ���Ϣ�Ƿ��ӡ��־
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��9��4��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  TAF_MMA_SetMmaLogInfoFlag(
    VOS_UINT8                           ucMmaLogInfoFlag
)
{
    TAF_MMA_GetMmaCtxAddr()->stMaintainInfo.ucMmaLogInfoFlag = ucMmaLogInfoFlag;
}



/*****************************************************************************
 �� �� ��  : TAF_MMA_SetNetworkCapabilityInfo
 ��������  : ����ϵͳģʽ���¶�Ӧ����������Ϣ

 �������  : enSysMode ���� ϵͳģʽ

 �������  : ��
 �� �� ֵ  : ��������������Ϣ����

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2013��7��31��
   ��    ��   : y00245242
   �޸�����   : �����ɺ���
 2.��    ��   : 2013��10��10��
   ��    ��   : w00176964
   �޸�����   : VOLTE_PhaseII:�޸ĺ�����
*****************************************************************************/
VOS_VOID TAF_MMA_SetNetworkCapabilityInfo(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode,
    TAF_SDC_NETWORK_CAP_INFO_STRU      *pstNwCapInfo
)
{
    if (TAF_SDC_SYS_MODE_LTE == enSysMode)
    {
        TAF_SDC_SetLteNwCapInfo(pstNwCapInfo);
    }
    else
    {
        TAF_SDC_SetGuNwCapInfo(pstNwCapInfo);
    }
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SetPhyInitStatus
 ��������  : ����������ʼ����ɱ�־

 �������  : enFlag ���� ������ʼ����ɱ�־
                       MMA_UPHY_INIT_STATUS_SUCCESS
                       MMA_UPHY_INIT_STATUS_FAIL
                       MMA_UPHY_INIT_STATUS_BUTT

 �������  : ��
 �� �� ֵ  : ��

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��3��19��
   ��    ��   : y00176023
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_MMA_SetPhyInitStatus(
    MMA_UPHY_INIT_STATUS_ENUM_UINT16    enFlag
)
{
    TAF_MMA_GetMmaCtxAddr()->stMmaExternalModuleInitStatusCtx.enPhyInitStatus = enFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetPhyInitStatus
 ��������  : ��ȡ������ʼ����ɱ�־

 �������  : ��

 �������  : ��
 �� �� ֵ  : �ϱ�������ʼ����ɱ�־
                       MMA_UPHY_INIT_STATUS_SUCCESS
                       MMA_UPHY_INIT_STATUS_FAIL
                       MMA_UPHY_INIT_STATUS_BUTT
 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��3��19��
   ��    ��   : y00176023
   �޸�����   : �����ɺ���
*****************************************************************************/
MMA_UPHY_INIT_STATUS_ENUM_UINT16 TAF_MMA_GetPhyInitStatus( VOS_VOID )
{
    return TAF_MMA_GetMmaCtxAddr()->stMmaExternalModuleInitStatusCtx.enPhyInitStatus;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_IsExternalModuleInitCompeleted
 ��������  : ��ȡ��չģ��ʱ��ʼ����ɱ�־

 �������  : ��

 �������  : ��
 �� �� ֵ  : �ϱ���չģ���ʼ����ɱ�־ 1ΪTRUE 0ΪFALSE

 ���ú���  :
 ��������  :

 �޸���ʷ      :
 1.��    ��   : 2014��4��02��
   ��    ��   : y00176023
   �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT16 TAF_MMA_IsExternalModuleInitCompeleted( VOS_VOID )
{
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enUsimstatus;
    MMA_UPHY_INIT_STATUS_ENUM_UINT16    enUphyInitStatus;

    enUsimstatus     = TAF_SDC_GetSimStatus();
    enUphyInitStatus = TAF_MMA_GetPhyInitStatus();

    if((TAF_SDC_USIM_STATUS_BUTT     == enUsimstatus)
    || (MMA_UPHY_INIT_STATUS_BUTT    == enUphyInitStatus))
    {
        return VOS_FALSE;
    }
    else
    {
        return VOS_TRUE;
    }
}

/* Added by b00269685 for L-C��������Ŀ, 2014-2-13, begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_IsOperTypeUsed
 ��������  : ���g_stTafMmaCtx.astMmaOperCtx��oper type���ͽṹ���ڱ�ʹ�ã�
             �ظ��ɹ���index
 �������  : enOperType

 �������  : ��
 �� �� ֵ  : VOS_TRUE/VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��13��
    ��    ��   : b00269685
    �޸�����   : L-C��������Ŀ
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsOperTypeUsed(
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType
)
{
    VOS_UINT32                          ulIndex;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /*  enOperType�Ƿ����ڱ�ʹ��  */
    for (ulIndex = 0; ulIndex < TAF_MMA_MAX_OPER_NUM; ulIndex++)
    {
        if ( (enOperType == pstMmaOperCtx[ulIndex].enOperType)
          && (VOS_TRUE   == pstMmaOperCtx[ulIndex].ucUsedFlag) )
        {
            /* ����ǰOPER_CTX��ϢLOG���� */
            TAF_MMA_LogOperCtxInfo();

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}


/*****************************************************************************
 �� �� ��  : TAF_MMA_GetSpecOperTypeIndex
 ��������  : ���g_stTafMmaCtx.astMmaOperCtx��oper type���ͽṹ���ڱ�ʹ�ã�
             �ظ��ɹ���index
 �������  : enOperType

 �������  : pucCtxIndex
 �� �� ֵ  : VOS_TRUE/VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��13��
    ��    ��   : b00269685
    �޸�����   : L-C��������Ŀ
*****************************************************************************/
VOS_UINT32 TAF_MMA_GetSpecOperTypeIndex(
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType,
    VOS_UINT8                          *pucCtxIndex
)
{
    VOS_UINT32                          ulIndex;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /*  enOperType�Ƿ����ڱ�ʹ��  */
    for (ulIndex = 0; ulIndex < TAF_MMA_MAX_OPER_NUM; ulIndex++)
    {
        if ( (enOperType == pstMmaOperCtx[ulIndex].enOperType)
          && (VOS_TRUE   == pstMmaOperCtx[ulIndex].ucUsedFlag) )
        {
            *pucCtxIndex = (VOS_UINT8)ulIndex;

            return VOS_TRUE;
        }
    }

    return VOS_FALSE;

}


/*****************************************************************************
 �� �� ��  : TAF_MMA_GetUnusedOperCtxIndex
 ��������  : ȡ��δ��ʹ�õ�CTX������
 �������  : ��

 �������  : pucCtxIndex
 �� �� ֵ  : VOS_TRUE/VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��13��
    ��    ��   : b00269685
    �޸�����   : L-C��������Ŀ
*****************************************************************************/
VOS_UINT32 TAF_MMA_GetUnusedOperCtxIndex(
    VOS_UINT8                          *pucCtxIndex
)
{
    VOS_UINT32                          ulIndex;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    /*  �Ƿ��п����Ctx   */
    for (ulIndex = 0; ulIndex < TAF_MMA_MAX_OPER_NUM; ulIndex++)
    {
        /* �ҵ��˿����CTX */
        if (VOS_FALSE == pstMmaOperCtx[ulIndex].ucUsedFlag)
        {
            *pucCtxIndex = (VOS_UINT8)ulIndex;

            return VOS_TRUE;
        }

    }

    /* ����ǰOPER_CTX��ϢLOG���� */
    TAF_MMA_LogOperCtxInfo();

    /* û���ҵ������CTX */
    return VOS_FALSE;

}
/* Added by b00269685 for L-C��������Ŀ, 2014-2-13, end */

/* Added by b00269685 for L-C��������Ŀ, 2014-2-13, begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_SetOperCtx
 ��������  : ������Ӧ��g_stTafMmaCtx.astMmaOperCtx
 �������  : stCtrl
             enOperType
             pucCtxIndex

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��13��
    ��    ��   : b00269685
    �޸�����   : L-C��������Ŀ
*****************************************************************************/
VOS_VOID TAF_MMA_SetOperCtx(
    TAF_MMA_CTRL_STRU                   stCtrl,
    TAF_MMA_OPER_TYPE_ENUM_UINT32       enOperType,
    VOS_UINT8                           ucCtxIndex
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    pstMmaOperCtx[ucCtxIndex].stCtrl.ucOpId     = stCtrl.ucOpId;
    pstMmaOperCtx[ucCtxIndex].stCtrl.usClientId = stCtrl.usClientId;
    pstMmaOperCtx[ucCtxIndex].stCtrl.ulModuleId = stCtrl.ulModuleId;
    pstMmaOperCtx[ucCtxIndex].enOperType        = enOperType;
    pstMmaOperCtx[ucCtxIndex].ucUsedFlag        = VOS_TRUE;

    /* ����ǰOPER_CTX��ϢLOG���� */
    TAF_MMA_LogOperCtxInfo();

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ClearOperCtx
 ��������  : ������Ӧ��g_stTafMmaCtx.astMmaOperCtx
 �������  : stCtrl
             enOperType
             pucCtxIndex

 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��13��
    ��    ��   : b00269685
    �޸�����   : L-C��������Ŀ
*****************************************************************************/
VOS_VOID TAF_MMA_ClearOperCtx(
    VOS_UINT8                           ucCtxIndex
)
{
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    PS_MEM_SET(&(pstMmaOperCtx[ucCtxIndex]), 0, sizeof(TAF_MMA_OPER_CTX_STRU));

    pstMmaOperCtx[ucCtxIndex].ucUsedFlag = VOS_FALSE;
    pstMmaOperCtx[ucCtxIndex].enOperType = TAF_MMA_OPER_BUTT;

    /* ����ǰOPER_CTX��ϢLOG���� */
    TAF_MMA_LogOperCtxInfo();

    return;
}
/* Added by b00269685 for L-C��������Ŀ, 2014-2-13, end */


/*****************************************************************************
 �� �� ��  : TAF_MMA_GetCFreqLockSetPara
 ��������  : ��ȡFREQLOCK��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��29��
    ��    ��   : y00307564
    �޸�����   : ��������
*****************************************************************************/
TAF_MMA_CFREQ_LOCK_SET_PARA_STRU* TAF_MMA_GetCFreqLockSetPara(VOS_VOID)
{
    return &g_stTafMmaCtx.stCFreqLockValue;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_InitCFreqLockPara
 ��������  : ��ʼ��FREQLOCK��Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��29��
    ��    ��   : y00307564
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID TAF_MMA_InitCFreqLockPara(VOS_VOID)
{
    TAF_MMA_CFREQ_LOCK_SET_PARA_STRU   *pstTafMmaCFreqLockPara;

    pstTafMmaCFreqLockPara = TAF_MMA_GetCFreqLockSetPara();

    PS_MEM_SET(pstTafMmaCFreqLockPara, 0x0, sizeof(TAF_MMA_CFREQ_LOCK_SET_PARA_STRU));

    return;
}



/*****************************************************************************
 �� �� ��  : TAF_MMA_SetSysCfgOperType_SysCfg
 ��������  : SYS CFG״̬��������SYS CFG�Ĳ�������
 �������  : TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��10��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SetSysCfgOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
)
{
    TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx.usOperType = usOperType;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SaveSysCfgOrigOperType_SysCfg
 ��������  : ����SYS CFG״̬����SYS CFG��ԭʼ��������
 �������  : TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��3��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SaveSysCfgOrigOperType_SysCfg(
    TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
)
{
    TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx.usOrigOperType = usOperType;

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_GetSysCfgOrigOperType_SysCfg
 ��������  : ��ȡSYS CFG״̬����SYS CFG��ԭʼ��������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_MMA_SYS_CFG_OPER_TYPE           usOperType
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��3��
    ��    ��   : w00176964
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_SYS_CFG_OPER_TYPE TAF_MMA_GetSysCfgOrigOperType_SysCfg(VOS_VOID)
{
    return (TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx.usOrigOperType);
}



/*****************************************************************************
 �� �� ��  : TAF_MMA_SetSysCfgPara_SysCfg
 ��������  : SYS CFG״̬���б�����Ϣ���Ĳ���
 �������  : TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��10��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SetSysCfgPara_SysCfg(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
)
{
    PS_MEM_CPY(&(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx.stSysCfgPara),
                pstSysCfgPara,
                sizeof(TAF_MMA_SYS_CFG_PARA_STRU));
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetSysCfgPara_SysCfg
 ��������  : ��ȡSYS CFG״̬���б�������ò���
 �������  : TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��10��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_SYS_CFG_PARA_STRU *TAF_MMA_GetSysCfgPara_SysCfg(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx.stSysCfgPara);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SetAttachOpId_SysCfg
 ��������  : SYS CFG״̬���б���attach�����opid
 �������  : VOS_UINT8                           ucOpId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��13��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SetAttachOpId_SysCfg(
    VOS_UINT8                           ucOpId
)
{
    TAF_MMA_GetMmaCtxAddr()->stCurFsm.unFsmCtx.stSysCfgCtx.ucAttachOpId = ucOpId;

    return;
}


#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 �� �� ��  : TAF_MMA_GetUserSetLteBandAddr
 ��������  : ��ȡ�û����õ�LTEƵ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_USER_SET_PREF_BAND64 -- LTE band��ַ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
TAF_USER_SET_PREF_BAND64 *TAF_MMA_GetUserSetLteBandAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx.stLastSyscfgSet.stUserSetBand.stUserSetLteBand);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetUeSupportLteBandAddr
 ��������  : ��ȡUE֧�ֵ�LTEƵ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_USER_SET_PREF_BAND64 -- ����UE��LTEƵ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
TAF_USER_SET_PREF_BAND64 *TAF_MMA_GetUeSupportLteBandAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx.stUeBandCap.stUeSupportLteBand);
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetRatPrioListAddr
 ��������  : ��ȡ�ϴ��û�ͨ��syscfg���óɹ��Ľ��뼼�������ȼ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_MMA_RAT_ORDER_STRU -- �û�RAT�����б�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
TAF_MMA_RAT_ORDER_STRU *TAF_MMA_GetRatPrioListAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx.stLastSyscfgSet.stRatPrioList);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetLastSyscfgSetAddr
 ��������  : ��ȡ�ϴ��û�ͨ��syscfg���óɹ��Ĳ���ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU -- �����ϴε�ϵͳ���ò���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
TAF_MMA_LAST_SETTED_SYSCFG_SET_STRU *TAF_MMA_GetLastSyscfgSetAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx.stLastSyscfgSet);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetSyscfgUserSetBandAddr
 ��������  : ��ȡ�ϴ��û�ͨ��syscfg���óɹ���Ƶ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_MMA_SYSCFG_USER_SET_BAND_STRU -- �����ϴε��û���Ƶ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
TAF_MMA_SYSCFG_USER_SET_BAND_STRU *TAF_MMA_GetSyscfgUserSetBandAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx.stLastSyscfgSet.stUserSetBand);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetSyscfgUserSetRoamValue
 ��������  : ��ȡ�ϴ��û�ͨ��syscfg��������ֵ
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_MMA_ROAM_MODE_ENUM_UINT8 -- �����ϴε��û�����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��16��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
TAF_MMA_ROAM_MODE_ENUM_UINT8 TAF_MMA_GetSyscfgUserSetRoamValue(VOS_VOID)
{
    return (g_stTafMmaCtx.stLastSyscfgSet.enRoam);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetUeSupportBandAddr
 ��������  : ��ȡUE֧�ֵ�Ƶ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : TAF_MMA_UE_BAND_CAPA_ST -- ����UE֧�ֵ�Ƶ������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��11��
    ��    ��   : y00245242
    �޸�����   : iteration 13����
*****************************************************************************/
TAF_MMA_UE_BAND_CAPA_ST *TAF_MMA_GetUeSupportBandAddr(VOS_VOID)
{
    return &(g_stTafMmaCtx.stUeBandCap);
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_GetAttachOpId
 ��������  : ��ȡattach������op id
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��4��13��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_MMA_GetAttachOpId(VOS_VOID)
{
    TAF_MMA_CONTEXT_STRU               *pstMmaCtx = VOS_NULL_PTR;
    VOS_UINT8                           ucOpId;

    pstMmaCtx = TAF_MMA_GetMmaCtxAddr();

    ucOpId = pstMmaCtx->stAttachInfo.ucAttachOpId;

    pstMmaCtx->stAttachInfo.ucAttachOpId++;

    pstMmaCtx->stAttachInfo.ucAttachOpId %= 0xFF;

    return ucOpId;
}

#if (FEATURE_ON == FEATURE_CSG)
/*****************************************************************************
 �� �� ��  : TAF_MMA_GetCsgListAbortType
 ��������  : ��ȡCSG LIST Abort����
 �������  : ��
 �������  : ��
 �� �� ֵ  : CSG LIST Abort����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��28��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
TAF_MMA_PLMN_LIST_ABORT_PROC_ENUM_UINT8 TAF_MMA_GetCsgListAbortType(VOS_VOID)
{
    return (TAF_MMA_GetMmaCtxAddr()->stCsgListInfo.enCsgListAbortProc);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SetCsgListAbortType
 ��������  : ����CSG LIST Abort����
 �������  : enCsgListAbortType - CSG LIST Abort����
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��28��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_VOID TAF_MMA_SetCsgListAbortType(
    TAF_MMA_PLMN_LIST_ABORT_PROC_ENUM_UINT8                 enCsgListAbortType
)
{
    TAF_MMA_GetMmaCtxAddr()->stCsgListInfo.enCsgListAbortProc = enCsgListAbortType;
    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_GetCsgListCtxAddr
 ��������  : ��ȡCSG LIST������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��ȡCSG LIST������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��28��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
TAF_MMA_CSG_LIST_CTX_STRU* TAF_MMA_GetCsgListCtxAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stCsgListInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_InitCsgListCtx
 ��������  : ��ʼ��CSG List������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��28��
    ��    ��   : z00161729
    �޸�����   : ֧��LTE CSG��������

*****************************************************************************/
VOS_VOID TAF_MMA_InitCsgListCtx(VOS_VOID)
{
    TAF_MMA_CSG_LIST_CTX_STRU          *pstCsgListCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;

    pstCsgListCtx = TAF_MMA_GetCsgListCtxAddr();

    PS_MEM_SET(pstCsgListCtx, 0x0, sizeof(pstCsgListCtx));

    pstCsgListCtx->enCsgListAbortProc = TAF_MMA_PLMN_LIST_ABORT_BUTT;

    for (ulIndex = 0; ulIndex < TAF_SDC_MAX_CSG_ID_LIST_NUM; ulIndex++)
    {
        pstCsgListCtx->astCsgIdListInfo[ulIndex].stPlmnId.Mcc = TAF_SDC_INVALID_MCC;
        pstCsgListCtx->astCsgIdListInfo[ulIndex].stPlmnId.Mnc = TAF_SDC_INVALID_MNC;
        pstCsgListCtx->astCsgIdListInfo[ulIndex].ulCsgId      = TAF_SDC_INVALID_CSG_ID_VALUE;
    }

    return;
}
#endif

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetGeoCtxAddr
 ��������  : ��ȡ��ȡ��������Ϣ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_MMA_GET_GEO_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��25��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_GET_GEO_CTX_STRU* TAF_MMA_GetGeoCtxAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stGetGeoInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_InitGetGeoCtx
 ��������  : ��ʼ����ȡ��������Ϣ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��25��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_InitGetGeoCtx(VOS_VOID)
{
    TAF_MMA_GET_GEO_CTX_STRU           *pstGetGeoCtx = VOS_NULL_PTR;

    pstGetGeoCtx = TAF_MMA_GetGeoCtxAddr();

    PS_MEM_SET(pstGetGeoCtx, 0x0, sizeof(TAF_MMA_GET_GEO_CTX_STRU));

    pstGetGeoCtx->stGetGeoNvCfg.ucCfgGetGeoFlag        = VOS_FALSE;
    pstGetGeoCtx->stGetGeoNvCfg.ucCcpuResetFlag        = VOS_FALSE;
    pstGetGeoCtx->stGetGeoNvCfg.aucReserved[0]         = 0;
    pstGetGeoCtx->stGetGeoNvCfg.aucReserved[1]         = 10;
    pstGetGeoCtx->stGetGeoNvCfg.ulGetGeoTimerLen       = TAF_MMA_GET_GEO_TIMER_DEFAULT_LEN;
    pstGetGeoCtx->stGetGeoNvCfg.ulGeoEffectiveTimeLen  = TAF_MMA_GEO_EFFECTIVE_TIME_DEFAULT_LEN;

    pstGetGeoCtx->ulGetGeoTickTime       = VOS_GetTick() / PRE_SECOND_TO_TICK;
    pstGetGeoCtx->stGeoPlmnId.ulMcc      = TAF_SDC_INVALID_MCC;
    pstGetGeoCtx->stGeoPlmnId.ulMnc      = TAF_SDC_INVALID_MNC;

    pstGetGeoCtx->ulGetGeoCdmaTickTime   = VOS_GetTick() / PRE_SECOND_TO_TICK;
    pstGetGeoCtx->stGeoCdmaLocInfo.ulMcc = TAF_SDC_INVALID_MCC;
    pstGetGeoCtx->stGeoCdmaLocInfo.lSid  = MMA_INVALID_SID;
    pstGetGeoCtx->stGeoCdmaLocInfo.lNid  = MMA_INVALID_NID;
    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetGeoCtxAddr
 ��������  : ��ȡ��ȡ��������Ϣ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_MMA_GET_GEO_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��25��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_SET_DPLMN_CTX_STRU* TAF_MMA_GetSetDplmnCtxAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stSetDplmnCtx);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_InitSetDplmnCtx
 ��������  : ��ʼ������Dplmn����������Ϣ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��02��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_InitSetDplmnCtx(VOS_VOID)
{

    TAF_MMA_SET_DPLMN_CTX_STRU           *pstSetDplmnCtx = VOS_NULL_PTR;

    pstSetDplmnCtx = TAF_MMA_GetSetDplmnCtxAddr();

    PS_MEM_SET(pstSetDplmnCtx, 0x00, sizeof(TAF_MMA_SET_DPLMN_CTX_STRU));

    pstSetDplmnCtx->enApPresetDplmnScene = TAF_MMA_AP_PRESET_DPLMN_SCENE_BUTT;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SetDplmnUpdateScene
 ��������  : ���ø���Dplmn�ĳ�����Ϣ
 �������  : TAF_MMA_AP_PRESET_DPLMN_SCENE_ENUM_UINT8                enApPresetDplmnScene
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��2��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SetDplmnUpdateScene(
    TAF_MMA_AP_PRESET_DPLMN_SCENE_ENUM_UINT8                enApPresetDplmnScene
)
{
    TAF_MMA_SET_DPLMN_CTX_STRU           *pstSetDplmnCtx = VOS_NULL_PTR;

    pstSetDplmnCtx = TAF_MMA_GetSetDplmnCtxAddr();

    pstSetDplmnCtx->enApPresetDplmnScene = enApPresetDplmnScene;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetDplmnUpdateScene
 ��������  : ��ȡ��ǰ����Dplmn�ĳ�����Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : enApPresetDplmnScene ��ǰ����DPlmn�ĳ���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��2��
    ��    ��   : l00289540
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_AP_PRESET_DPLMN_SCENE_ENUM_UINT8 TAF_MMA_GetDplmnUpdateScene(VOS_VOID)
{
    TAF_MMA_SET_DPLMN_CTX_STRU           *pstSetDplmnCtx = VOS_NULL_PTR;

    pstSetDplmnCtx = TAF_MMA_GetSetDplmnCtxAddr();

    return pstSetDplmnCtx->enApPresetDplmnScene;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_InitGetHplmnInfo
 ��������  : ��ʼ����ȡ��������Ϣ������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��10��28��
    ��    ��   : s00217060
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_InitGetHplmnInfo(VOS_VOID)
{
    TAF_MMA_GET_HPLMN_STRU             *pstGetHplmnInfo = VOS_NULL_PTR;

    pstGetHplmnInfo = TAF_MMA_GetHplmnInfo();

    PS_MEM_SET(pstGetHplmnInfo, 0x0, sizeof(TAF_MMA_GET_HPLMN_STRU));

    pstGetHplmnInfo->ucHplmnMncLen          = 0;
    pstGetHplmnInfo->enWaitSimFileCnfFlg    = TAF_MMA_READ_USIM_FILE_FLG_NULL;
    pstGetHplmnInfo->ulEHplmnNum            = 0;

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_GetHplmnInfo
 ��������  : ��ȡhplmn��Ϣ
 �������  : ��
 �� �� ֵ  : TAF_MMA_GET_HPLMN_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��3��16��
    ��    ��   : z00161729
    �޸�����   : AT&T ֧��EONS�����޸�
*****************************************************************************/
TAF_MMA_GET_HPLMN_STRU *TAF_MMA_GetHplmnInfo(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stGetHplmnInfo);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_InitSdcIccId
 ��������  : ��ʼ������IccId
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��26��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_InitSdcIccId( VOS_VOID )
{
    TAF_SDC_ICCID_INFO_STRU             *pstIccIdInfo   = VOS_NULL_PTR;

    pstIccIdInfo        = TAF_SDC_GetIccIdInfo();

    PS_MEM_SET(pstIccIdInfo, 0xFF, sizeof(TAF_SDC_ICCID_INFO_STRU));

    pstIccIdInfo->ucLen = TAF_SDC_ICC_ID_MAX_NUM + 1;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsValidIccId
 ��������  : �жϵ�ǰ�Ƿ�Ϊ��Ч
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��26��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsValidIccId( VOS_VOID )
{
    TAF_SDC_ICCID_INFO_STRU              stNullIccIdInfo;

    PS_MEM_SET(&stNullIccIdInfo, 0xFF, sizeof(TAF_SDC_ICCID_INFO_STRU));
    stNullIccIdInfo.ucLen   = TAF_SDC_ICC_ID_MAX_NUM + 1;

    if (0 == PS_MEM_CMP(TAF_SDC_GetIccIdInfo(), &stNullIccIdInfo, sizeof(TAF_SDC_ICCID_INFO_STRU)))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetCfgGetGeoFlag
 ��������  : ��ȡ�����Ż��Ż�2.0��ʶ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��25��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8  TAF_MMA_GetCfgGetGeoFlag(VOS_VOID)
{
    return TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.ucCfgGetGeoFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetGeoTimerLen
 ��������  : ��ȡ����λ�ö�ʱ��ʱ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_UINT16
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��25��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_GetGeoTimerLen(VOS_VOID)
{
    return TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.ulGetGeoTimerLen;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SetCcpuResetFlag
 ��������  : ����C�˵�����λ�ı�־
 �������  : VOS_UINT8
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��25��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SetCcpuResetFlag(VOS_UINT8 ucCcpuResetFlag)
{
    TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.ucCcpuResetFlag = ucCcpuResetFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetCcpuResetFlag
 ��������  : ��ȡC�˵�����λ�ı�־
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��25��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_MMA_GetCcpuResetFlag(VOS_VOID)
{
    return TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.ucCcpuResetFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetGeoEffectiveTimeLen
 ��������  : ��ȡ��������Чʱ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��25��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_GetGeoEffectiveTimeLen(VOS_VOID)
{
    return TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.ulGeoEffectiveTimeLen;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsGeoValid
 ��������  : �жϹ������Ƿ���Ч
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ч
             VOS_TRUE:��Ч
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��26��
    ��    ��   : n00269697
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsGeoValid(VOS_VOID)
{
    TAF_MMA_GET_GEO_CTX_STRU           *pstGetGeoCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulCurrTickTime;
    VOS_UINT32                          ulGeoEffectiveTimeLen;
    VOS_UINT32                          ulIsPlmnIdValid;

    ulCurrTickTime          = VOS_GetTick() / PRE_SECOND_TO_TICK;
    ulGeoEffectiveTimeLen   = TAF_MMA_GetGeoEffectiveTimeLen();
    pstGetGeoCtx            = TAF_MMA_GetGeoCtxAddr();
    ulIsPlmnIdValid         = TAF_SDC_IsPlmnIdValid(&pstGetGeoCtx->stGeoPlmnId);

    /* get geo NV�ر�ʱҲ��Ϊ��Ч */
    if (VOS_FALSE == pstGetGeoCtx->stGetGeoNvCfg.ucCfgGetGeoFlag)
    {
        return VOS_FALSE;
    }

    /* ������Ϣ��PLMN��Ч���߳�����Чʱ��������Ϊ����������Ч�� */
    if ((VOS_FALSE == ulIsPlmnIdValid)
     || ((ulCurrTickTime - pstGetGeoCtx->ulGetGeoTickTime) > ulGeoEffectiveTimeLen))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_IsNeedGetGeoNoSimStart
 ��������  : �Ƿ���Ҫ�����ȡ��������޿�����
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��27��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���
  1.��    ��   : 2015��12��28��
    ��    ��   : l00324781
    �޸�����   : CL_MUTIMODE_OPTIMIZE�޸ģ�����Xģ����
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsNeedGetGeoNoSimStart(VOS_VOID)
{
    VOS_UINT8                           ucCfgGetGeoFlag;
    VOS_UINT8                           ucCcpuResetFlag;

    ucCfgGetGeoFlag  = TAF_MMA_GetCfgGetGeoFlag();
    ucCcpuResetFlag  = TAF_MMA_GetCcpuResetFlag();
#if (FEATURE_ON == FEATURE_LTE)
    /* ���ƽ̨��֧��L����ֱ�ӷ��ز�֧�� */
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        if ((VOS_TRUE  == ucCfgGetGeoFlag)
         && (VOS_TRUE  != ucCcpuResetFlag))
        {
            return VOS_TRUE;
        }
    }
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsPlatformSupport1x())
    {
        if ((VOS_TRUE  == ucCfgGetGeoFlag)
         && (VOS_TRUE  != ucCcpuResetFlag))
        {
            return VOS_TRUE;
        }
    }
#endif

    return VOS_FALSE;
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_SetTestRoamFlag
 ��������  : ���ò��Ա�־
 �������  : VOS_UINT8
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��19��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SetTestRoamFlag(VOS_UINT8 ucFlag)
{
    TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.aucReserved[0] = ucFlag;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetTestRoamFlag
 ��������  : ��ȡ���Ա�־
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��19��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_MMA_GetTestRoamFlag(VOS_VOID)
{
    return TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.aucReserved[0];
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SetWaitExtTimerLen
 ��������  : ���õȴ��ⲿģ��Ķ�ʱ��ʱ��
 �������  : VOS_UINT8
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��19��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SetWaitExtTimerLen(VOS_UINT8 ucLen)
{
    TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.aucReserved[1] = ucLen;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetWaitExtTimerLen
 ��������  : ��ȡ�ȴ��ⲿģ��Ķ�ʱ��ʱ��
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��6��19��
    ��    ��   : f00179208
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 TAF_MMA_GetWaitExtTimerLen(VOS_VOID)
{
    return TAF_MMA_GetGeoCtxAddr()->stGetGeoNvCfg.aucReserved[1];
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_GetSrvAcqRatListAddr
 ��������  : ��ȡҵ�񴥷�����������ģʽ�б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : TAF_MMA_SRV_ACQ_RAT_LIST_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��16��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
TAF_MMA_SRV_ACQ_RAT_LIST_STRU* TAF_MMA_GetSrvAcqRatListAddr(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stDsdsInfo.stSrvAcqRatList);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateSrvAcqRatList
 ��������  : ����ҵ�񴥷�����������ģʽ�б�
 �������  : TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatList
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��16��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateSrvAcqRatList(
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatList
)
{
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatListAddr = VOS_NULL_PTR;

    pstSrvAcqRatListAddr = TAF_MMA_GetSrvAcqRatListAddr();

    PS_MEM_CPY(pstSrvAcqRatListAddr, pstSrvAcqRatList, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_ClearSrvAcqRatList
 ��������  : ���ҵ�񴥷�����������ģʽ�б�
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��18��
    ��    ��   : l00301449
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_ClearSrvAcqRatList(VOS_VOID)
{
    TAF_MMA_SRV_ACQ_RAT_LIST_STRU      *pstSrvAcqRatListAddr = VOS_NULL_PTR;

    pstSrvAcqRatListAddr = TAF_MMA_GetSrvAcqRatListAddr();

    PS_MEM_SET(pstSrvAcqRatListAddr, 0, sizeof(TAF_MMA_SRV_ACQ_RAT_LIST_STRU));
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_SetDelayReportServiceStatusFlg
 ��������  : ���õ�ǰ�Ƿ������˶��ݵ�����ʱ�ϱ�����
 �������  : ucDelayReportServiceStatusFlg - ���ݵ�����ʱ�ϱ������Ƿ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��02��11��
   ��    ��   : l00305157
   �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
 2.��    ��   : 2015��09��30��
   ��    ��   : j00354216
   �޸�����   : CDMA Iteration 18 �޸Ľṹ��
*****************************************************************************/
VOS_VOID TAF_MMA_SetDelayReportServiceStatusFlg(
    VOS_UINT8 ucDelayReportServiceStatusFlg
)
{
    TAF_MMA_GetMmaCtxAddr()->stDelayRptCtrlNVInfo.stGulDelayRptCtrlInfo.ucEnable= ucDelayReportServiceStatusFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetDelayReportServiceStatusFlg
 ��������  : ��ȡ��ǰ�Ƿ������˶��ݵ�����ʱ�ϱ�����
 �������  :
 �������  : ��
 �� �� ֵ  : ���ݵ�����ʱ�ϱ������Ƿ�����FLAG
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��02��11��
   ��    ��   : l00305157
   �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
 2.��    ��   : 2015��09��30��
   ��    ��   : j00354216
   �޸�����   : CDMA Iteration 18 �޸Ľṹ��
*****************************************************************************/
VOS_UINT8 TAF_MMA_GetDelayReportServiceStatusFlg(VOS_VOID)
{
    return (TAF_MMA_GetMmaCtxAddr()->stDelayRptCtrlNVInfo.stGulDelayRptCtrlInfo.ucEnable);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SetDelayReportServiceStatusTimerLen
 ��������  : ���õ�ǰ�����˶��ݵ�����ʱ�ϱ����ܵ�ʱ��
 �������  : ulTimerLen -  ʱ������λ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��02��11��
   ��    ��   : l00305157
   �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
 2.��    ��   : 2015��09��30��
   ��    ��   : j00354216
   �޸�����   : CDMA Iteration 18 �޸Ľṹ��
*****************************************************************************/
VOS_VOID TAF_MMA_SetDelayReportServiceStatusTimerLen(
    VOS_UINT32 ulTimerLen
)
{
    TAF_MMA_GetMmaCtxAddr()->stDelayRptCtrlNVInfo.stGulDelayRptCtrlInfo.ulRptSrvStaDelayTimerValue = ulTimerLen;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetDelayReportServiceStatusCfgTimerLen
 ��������  : ��ȡ��ǰ�����˶��ݵ�����ʱ�ϱ����ܵ�ʱ��
 �������  :
 �������  : ��
 �� �� ֵ     :  ʱ������λ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��02��11��
   ��    ��   : l00305157
   �޸�����   : Service_State_Optimize_PhaseII ��Ŀ�޸�
 2.��    ��   : 2015��09��30��
   ��    ��   : j00354216
   �޸�����   : CDMA Iteration 18 �޸Ľṹ��
*****************************************************************************/
VOS_UINT32 TAF_MMA_GetDelayReportServiceStatusCfgTimerLen(VOS_VOID)
{
    return (TAF_MMA_GetMmaCtxAddr()->stDelayRptCtrlNVInfo.stGulDelayRptCtrlInfo.ulRptSrvStaDelayTimerValue);
}


/*****************************************************************************
 �� �� ��  : TAF_MMA_GetCLNoServiceDelayRptInfo
 ��������  : ��ȡCLģʽ�ӳ��ϱ��޷�����Ϣ
 �������  : ��
 �� �� ֵ  : TAF_MMA_CL_NO_SERVICE_DELAY_RPT_STRU
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2016��1��7��
    ��    ��   : h00313353
    �޸�����   : DTS2016010508602
*****************************************************************************/
TAF_MMA_CL_NO_SERVICE_DELAY_RPT_STRU *TAF_MMA_GetCLNoServiceDelayRptInfo(VOS_VOID)
{
    return &(TAF_MMA_GetMmaCtxAddr()->stDelayRptCtrlNVInfo.stCLNoServiceDelayRptInfo);
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_MMA_SetCLDelayReptSrvStatusFlg
 ��������  : ����Cģ�ӳ��ϱ�ʹ�ܱ�ʶ
 �������  : ucCLDelayReptSrvStatusFlg - ����Cģ�ӳ��ϱ�ʹ�ܱ�ʶ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��09��30��
   ��    ��   : j00354216
   �޸�����   : Cģ����״̬�Ż���Ŀ����
*****************************************************************************/
VOS_VOID TAF_MMA_SetCLDelayReptSrvStatusFlg(
    VOS_UINT8 ucCLDelayReptSrvStatusFlg
)
{
    TAF_MMA_GetMmaCtxAddr()->stDelayRptCtrlNVInfo.stClDelayRptCtrlInfo.ucClDelayRptEnable = ucCLDelayReptSrvStatusFlg;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetCLDelayReptSrvStatusFlg
 ��������  : ��ȡCģ�ӳ��ϱ�ʹ�ܱ�ʶ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ʹ�ܱ�ʶ��VOS_TRUEΪ����,VOS_FALSEΪ�ر�
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��09��30��
   ��    ��   : j00354216
   �޸�����   : Cģ����״̬�Ż���Ŀ����
*****************************************************************************/
VOS_UINT8 TAF_MMA_GetCLDelayReptSrvStatusFlg(VOS_VOID)
{
    return (TAF_MMA_GetMmaCtxAddr()->stDelayRptCtrlNVInfo.stClDelayRptCtrlInfo.ucClDelayRptEnable);
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_SetCLDelayReptSrvStatusTimerLen
 ��������  : ����Cģ�ӳ��ϱ���ʱ������
 �������  : ulTimerLen - ��Ҫ���õ�ʱ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��09��30��
   ��    ��   : j00354216
   �޸�����   : Cģ����״̬�Ż���Ŀ����
*****************************************************************************/
VOS_VOID TAF_MMA_SetCLDelayReptSrvStatusTimerLen(
    VOS_UINT32 ulTimerLen
)
{
    TAF_MMA_GetMmaCtxAddr()->stDelayRptCtrlNVInfo.stClDelayRptCtrlInfo.ulClRptSrvStaDelayTimerValue = ulTimerLen;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_GetCLDelayReptSrvStatusTimerLen
 ��������  : ��ȡCģ�ӳ��ϱ���ʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : �ӳ��ϱ���ʱ��ʱ������λ����
 ���ú���  :
 ��������  :

 �޸���ʷ     :
 1.��    ��   : 2015��09��30��
   ��    ��   : j00354216
   �޸�����   : Cģ����״̬�Ż���Ŀ����
*****************************************************************************/
VOS_UINT32 TAF_MMA_GetCLDelayReptSrvStatusTimerLen(VOS_VOID)
{
    return (TAF_MMA_GetMmaCtxAddr()->stDelayRptCtrlNVInfo.stClDelayRptCtrlInfo.ulClRptSrvStaDelayTimerValue);
}
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 �� �� ��  : TAF_MMA_IsGeoCdmaLocValid
 ��������  : �ж�cdma��λ����Ϣ�Ƿ���Ч
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ч
             VOS_TRUE:��Ч
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��10��
    ��    ��   : l00324781
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_MMA_IsGeoCdmaLocValid(VOS_VOID)
{
    TAF_MMA_GET_GEO_CTX_STRU           *pstGetGeoCtx = VOS_NULL_PTR;
    VOS_UINT32                          ulCurrTickTime;
    VOS_UINT32                          ulGeoEffectiveTimeLen;

    ulCurrTickTime          = VOS_GetTick() / PRE_SECOND_TO_TICK;
    ulGeoEffectiveTimeLen   = TAF_MMA_GetGeoEffectiveTimeLen();
    pstGetGeoCtx            = TAF_MMA_GetGeoCtxAddr();

    /* get geo NV�ر�ʱҲ��Ϊ��Ч */
    if (VOS_FALSE == pstGetGeoCtx->stGetGeoNvCfg.ucCfgGetGeoFlag)
    {
        return VOS_FALSE;
    }

    /* ���Mcc����Чֵ������Ϊ����Cdma��λ����Ϣ��Ч */
    /* ��ʱ�������жϣ�λ����Ϣ�Ƿ�ʧЧ */
    if ((TAF_SDC_INVALID_MCC == pstGetGeoCtx->stGeoCdmaLocInfo.ulMcc)
     || ((ulCurrTickTime - pstGetGeoCtx->ulGetGeoCdmaTickTime) > ulGeoEffectiveTimeLen))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_MMA_UpdateGeoCdmaLocInfo
 ��������  : ����GetGeo��1X��λ����Ϣ
 �������  : VOS_INT32     lSid   1x��λ����Ϣ
             VOS_INT32     lNid   1x��λ����Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��12��10��
    ��    ��   : l00324781
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateGeoCdmaLocInfo(
    VOS_INT32                   lSid,
    VOS_INT32                   lNid
)
{
    TAF_MMA_GET_GEO_CTX_STRU            *pstGetGeoCtx = VOS_NULL_PTR;

    pstGetGeoCtx        = TAF_MMA_GetGeoCtxAddr();

    /* get geo NV��ر�ʱ����Ҫ���� */
    if (VOS_FALSE == pstGetGeoCtx->stGetGeoNvCfg.ucCfgGetGeoFlag)
    {
        return;
    }

    pstGetGeoCtx->stGeoCdmaLocInfo.lSid  = lSid;
    pstGetGeoCtx->stGeoCdmaLocInfo.lNid  = lNid;
    /* ʹ��Sid��g_astTafCountryList���в���Mcc��������Ҳ�����������Чֵ��ȫF */
    pstGetGeoCtx->stGeoCdmaLocInfo.ulMcc = TAF_QueryMccWithSid(lSid);

    pstGetGeoCtx->ulGetGeoCdmaTickTime   = VOS_GetTick() / PRE_SECOND_TO_TICK;

    return;
}

#endif
/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



