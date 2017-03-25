/******************************************************************************

                  ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CmmcaCtx.c
  �� �� ��   : ����
  ��    ��   : l60609
  ��������   : 2014��01��08��
  ����޸�   :
  ��������   : CMMCAģ���������ά��
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��01��08��
    ��    ��   : l60609
    �޸�����   : ������

******************************************************************************/
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CmmcaCtx.h"
#include "CmmcaRegMgmt.h"
#include "CmmcaMntn.h"
#include "NVIM_Interface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e767 �޸���: l60609; */
#define    THIS_FILE_ID        PS_FILE_ID_CMMCA_CTX_C
/*lint +e767 �޸���: l60609; */

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
CMMCA_CTX_STRU                          g_stCmmcaCtx;


/*****************************************************************************
  3 ��������
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : CMMCA_REG_GetCtxAddr
 ��������  : ��ȡREG�����ĵ�ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CMMCA_REG_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��13��
    ��    ��   : S00261364
    �޸�����   : �����ɺ���

*****************************************************************************/
CMMCA_REG_CTX_STRU* CMMCA_REG_GetCtxAddr(VOS_VOID)
{
    return &g_stCmmcaCtx.stRegCtx;
}


/*****************************************************************************
 �� �� ��  : CMMCA_REG_InitCtx
 ��������  : ��ʼ��REG��ص�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��13��
    ��    ��   : S00261364
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CMMCA_REG_InitCtx(VOS_VOID)
{
    CMMCA_REG_CTX_STRU                 *pstRegCtx = VOS_NULL_PTR;

    /* ��ʼ��ȫ�ֱ���g_stCmmcaCtx.stRegCtx */
    pstRegCtx = CMMCA_REG_GetCtxAddr();

    PS_MEM_SET(pstRegCtx, 0, sizeof(CMMCA_REG_CTX_STRU));

    /* ��ʼ�����������Ƿ���NVֵ */
    CMMCA_REG_ReadRoamCfgInfoNvim();

    return;
}


/*****************************************************************************
 �� �� ��  : CMMCA_REG_ReadRoamCfgInfoNvim
 ��������  : ��ȡ����NV��ص�����ֵ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��5��
    ��    ��   : w00167002
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CMMCA_REG_ReadRoamCfgInfoNvim(VOS_VOID)
{
    CMMCA_REG_CTX_STRU                 *pstRegCtx = VOS_NULL_PTR;
    NAS_NVIM_ROAM_CFG_INFO_STRU         stRoamFeature;
    MODEM_ID_ENUM_UINT16                enModemId;
    VOS_UINT32                          ulLength;

    pstRegCtx                       = CMMCA_REG_GetCtxAddr();
    enModemId                       = MODEM_ID_0;
    ulLength                        = 0;
    stRoamFeature.ucRoamFeatureFlg  = NV_ITEM_ACTIVE;
    stRoamFeature.ucRoamCapability  = 0;

    (VOS_VOID)NV_GetLength(en_NV_Item_Roam_Capa, &ulLength);
    if (NV_OK != NV_ReadEx(enModemId, en_NV_Item_Roam_Capa,
                         &stRoamFeature, ulLength))
    {
        return;
    }

    if ((NV_ITEM_ACTIVE     != stRoamFeature.ucRoamFeatureFlg)
     && (NV_ITEM_DEACTIVE   != stRoamFeature.ucRoamFeatureFlg))
    {
        return;
    }

    if ( NV_ITEM_DEACTIVE == stRoamFeature.ucRoamFeatureFlg )
    {
        pstRegCtx->stUserCfgInfo.ucIsRoamActive = VOS_FALSE;
    }
    else
    {
        pstRegCtx->stUserCfgInfo.ucIsRoamActive = VOS_TRUE;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : CMMCA_GetTiCtx
 ��������  : ��ȡtimer ctx��ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CMMCA_TIMER_CTX_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��23��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
CMMCA_TIMER_CTX_STRU* CMMCA_GetTiCtx(VOS_VOID)
{
    return CMMCA_GetCtxAddr()->astCmmcaTimer;
}

/*****************************************************************************
 �� �� ��  : CMMCA_InitTiCtx
 ��������  : ��ʼ����ʱ����ص�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��21��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CMMCA_InitTiCtx(VOS_VOID)
{
    CMMCA_TIMER_CTX_STRU               *pstTiCtx = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstTiCtx = CMMCA_GetTiCtx();

    for (i = 0; i < CMMCA_MAX_TIMER_NUM; i++)
    {
        pstTiCtx[i].hTimer        = VOS_NULL_PTR;
        pstTiCtx[i].enTimerId     = TI_CMMCA_TIMER_BUTT;
        pstTiCtx[i].enTimerStatus = CMMCA_TIMER_STATUS_STOP;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CMMCA_InitCtx
 ��������  : CMMCAģ�������ĳ�ʼ��
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��26��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CMMCA_InitCtx(VOS_VOID)
{
    /* ��ʼ��Cur Op Id */
    CMMCA_SetCurMaxOpid(0);

    /* ����Modem��״̬ΪINACTIVE */
    CMMCA_SetModemStatus(CMMCA_MODEM_STATUS_INACTIVE);

    /* ��ʼ����Ϣ������� */
    CMMCA_InitCmdBufferQueue(CMMCA_GetCmdBufferQueueAddr());

    /* ��ʼ����PACKET DATA��ص������� */
    CMMCA_PKT_InitCtx();

    /* Added by s00261364 for L-C��������Ŀ, 2014-2-13, begin */
    /* ��ʼ����ע����ص������� */
    CMMCA_REG_InitCtx();
    /* Added by s00261364 for L-C��������Ŀ, 2014-2-13, end */

    /* ��ʼ����ʱ����ص������� */
    CMMCA_InitTiCtx();

    /* ��ά�ɲ��ʼ�� */
    CMMCA_DEBUG_InitCtx();

    return;
}

/*****************************************************************************
 �� �� ��  : CMMCA_AssignOpid
 ��������  : ����OPID��1-255
 �������  : VOS_UINT8                          *pucOpid
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CMMCA_AssignOpid(
    VOS_UINT8                          *pucOpid
)
{
    VOS_UINT8                           ucOpid;

    /*��ȡ��ǰ���OPID*/
    ucOpid = CMMCA_GetCurMaxOpid();

    /*�����δ�����ֵ��ֱ�Ӽ�1*/
    if( ucOpid < CMMCA_OPID_MAX_VALUE)
    {
        *pucOpid = ucOpid + 1;
    }
    /*����Ѿ������ֵ���ӳ�ֵ��ʼ����*/
    else
    {
        (*pucOpid) = CMMCA_OPID_MIN_VALUE;
    }

    CMMCA_SetCurMaxOpid(*pucOpid);

    return;
}

/*****************************************************************************
 �� �� ��  : CMMCA_GetCmdBufferQueueAddr
 ��������  : ��ȡCMMCA��Ϣ���еĵ�ַ
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : CMMCA_CMD_BUFFER_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
CMMCA_CMD_BUFFER_STRU* CMMCA_GetCmdBufferQueueAddr(VOS_VOID)
{
    return CMMCA_GetCtxAddr()->astCmdBufferQueue;
}

/*****************************************************************************
 �� �� ��  : CMMCA_InitCmdBufferQueue
 ��������  : ��ʼ��CMMC��Ϣ����
 �������  : CMMCA_CMD_BUFFER_STRU              *pstCmdBufferQueue
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��2��12��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CMMCA_InitCmdBufferQueue(
    CMMCA_CMD_BUFFER_STRU              *pstCmdBufferQueue
)
{
    VOS_UINT32                          i;

    for (i = 0; i < CMMCA_MAX_CMD_BUFFER_QUEUE_SIZE; i++)
    {
        pstCmdBufferQueue[i].ucOpId         = CMMCA_OPID_INVILID_VALUE;
        pstCmdBufferQueue[i].pucMsgInfo     = VOS_NULL_PTR;
        pstCmdBufferQueue[i].ulMsgInfoLen   = 0;
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CMMCA_DelItemInCmdBufferQueue
 ��������  : �Ӷ�����ɾ�����Ӧ�ĵȴ���Ϣ
 �������  : VOS_UINT8                           ucOpId
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID CMMCA_DelItemInCmdBufferQueue(
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          i;
    CMMCA_CMD_BUFFER_STRU              *pstCmdBufferQueue = VOS_NULL_PTR;

    pstCmdBufferQueue = CMMCA_GetCmdBufferQueueAddr();

    for ( i = 0; i < CMMCA_MAX_CMD_BUFFER_QUEUE_SIZE; i++ )
    {
        if (ucOpId == pstCmdBufferQueue[i].ucOpId)
        {
            /* ����л������Ϣ���ͷ���Ϣ�ڴ� */
            if (VOS_NULL_PTR != pstCmdBufferQueue[i].pucMsgInfo)
            {
                PS_MEM_FREE(WUEPS_PID_CMMCA, pstCmdBufferQueue[i].pucMsgInfo);
            }

            /* ��ʼ�� */
            pstCmdBufferQueue[i].pucMsgInfo     = VOS_NULL_PTR;
            pstCmdBufferQueue[i].ucOpId         = CMMCA_OPID_INVILID_VALUE;
            pstCmdBufferQueue[i].ulMsgInfoLen   = 0;

            break;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : CMMCA_SaveItemInCmdBufferQueue
 ��������  : �������Ϣ���뵽�ȴ��Ļ��������, �ȴ�����Ľ����Լ��pucMsgInfo��ǰ�����ֽ�ΪCMD ID
 �������  : VOS_UINT8                           ucOpId
             VOS_UINT8                          *pucMsgInfo
             VOS_UINT32                          ulMsgInfoLen
 �������  : ��
 �� �� ֵ  : VOS_UINT8
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT8 CMMCA_SaveItemInCmdBufferQueue(
    VOS_UINT8                           ucOpId,
    VOS_UINT8                          *pucMsgInfo,
    VOS_UINT32                          ulMsgInfoLen
)
{
    VOS_UINT32                          i;
    VOS_UINT8                          *pucMsgBuf = VOS_NULL_PTR;
    CMMCA_CMD_BUFFER_STRU              *pstCmdBufferQueue = VOS_NULL_PTR;

    /* �����Ϣָ��Ϊ�գ�ֱ�ӷ��� */
    if (VOS_NULL_PTR == pucMsgInfo)
    {
        return VOS_ERR;
    }

    pstCmdBufferQueue = CMMCA_GetCmdBufferQueueAddr();

    for (i = 0; i < CMMCA_MAX_CMD_BUFFER_QUEUE_SIZE; i++)
    {
        if (CMMCA_OPID_INVILID_VALUE == pstCmdBufferQueue[i].ucOpId)
        {
            break;
        }
    }

    /* �ж���ǰ��ѭ�������Ƿ��Ѿ����ˣ����������ֱ�ӷ��أ������쳣��ӡ */
    if (i >= CMMCA_MAX_CMD_BUFFER_QUEUE_SIZE)
    {
        /* ����������� */
        CMMCA_WARNING1_LOG("CMMCA_SaveItemInCmdBufferQueue, Buffer Full, Op Id :", ucOpId);

        CMMCA_LogBuffFullInd();

        return VOS_ERR;
    }

    /* �ڶ���������Ӧ����Ϣ�������ڴ棬������Ϣ��ֵ */
    pucMsgBuf = (VOS_UINT8 *)PS_MEM_ALLOC(WUEPS_PID_CMMCA, ulMsgInfoLen);
    if (VOS_NULL_PTR == pucMsgBuf)
    {
        return VOS_ERR;
    }

    /* ��ֵ */
    PS_MEM_CPY((VOS_UINT8 *)pucMsgBuf, pucMsgInfo, ulMsgInfoLen);
    pstCmdBufferQueue[i].pucMsgInfo     = pucMsgBuf;
    pstCmdBufferQueue[i].ucOpId         = ucOpId;
    pstCmdBufferQueue[i].ulMsgInfoLen   = ulMsgInfoLen;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : CMMCA_GetItemFromCmdBufferQueue
 ��������  : �ӵȴ��Ļ�������л�ȡ�����Ϣ
 �������  : VOS_UINT8                           ucOpId
 �������  : ��
 �� �� ֵ  : CMMCA_CMD_BUFFER_STRU*
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��1��27��
    ��    ��   : l60609
    �޸�����   : �����ɺ���

*****************************************************************************/
CMMCA_CMD_BUFFER_STRU* CMMCA_GetItemFromCmdBufferQueue(
    VOS_UINT8                           ucOpId
)
{
    VOS_UINT32                          i;
    CMMCA_CMD_BUFFER_STRU              *pstCmdBufferQueue;

    pstCmdBufferQueue = CMMCA_GetCmdBufferQueueAddr();

    /* ��������, ��ȡenTimerIdָ������Ϣ�ڵ� */
    for (i = 0; i < CMMCA_MAX_CMD_BUFFER_QUEUE_SIZE; i++)
    {
        if (ucOpId == pstCmdBufferQueue[i].ucOpId)
        {
            break;
        }
    }

    /* �ж���ǰ��ѭ�������Ƿ��Ѿ����ˣ����������ֱ�ӷ��أ������쳣��ӡ */
    if (i >= CMMCA_MAX_CMD_BUFFER_QUEUE_SIZE)
    {
        /* δ�ҵ� */
        CMMCA_WARNING1_LOG("CMMCA_GetItemFromCmdBufferQueue, Msg Not Found, ucOpId Id :", ucOpId);

        return VOS_NULL_PTR;
    }

    /* ���������Ϣָ�뷵�� */
    return &pstCmdBufferQueue[i];
}
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif




