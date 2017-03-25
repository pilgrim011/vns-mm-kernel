/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dhcpc_block.c
  �� �� ��   : ����
  ��    ��   : tianyang 00144555
  ��������   : 2012��7��13��
  ����޸�   :
  ��������   : DHCP���ƿ����
  �����б�   :
*
*       1.                DHCPC_AddDhcpcContextToPool
*       2.                DHCPC_CreateDhcpcContext
*       3.                DHCPC_FreeDhcpcContext
*       4.                DHCPC_InsertIdleTable
*       5.                DHCPC_QueryDhcpcContext
*
#include "dhcp_inc.h"
  �޸���ʷ   :
  1.��    ��   : 2012��7��13��
    ��    ��   : tianyang 00144555
    �޸�����   : �����ļ�

******************************************************************************/
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpc.h"
#include "dhcpc_cdb.h"
#include "dhcpc_func.h"
#include "dhcpc_table.h"
#include "dhcpc_var.h"
#include "dhcpc_comp.h"
#include "dhcpc_dbg.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPC_BLOCK_C
/*lint +e767*/

ULONG g_ulDhcpcBlkUsedNum = 0; /* ��¼��ʹ�õĿ��ƿ���� */
ULONG g_ulDhcpcBlkIdleNum = 0; /* ��¼�ѿɹ�ʹ�õĿ��п��ƿ���� */
ULONG g_ulDhcpcManageMemNum = 0; /* ����Ĺ����ڴ�ĸ��� */
DHCPC_CTRLBLK               *g_pstDhcpIdleTableHead = NULL;
DHCPC_MANAGEBLK           *g_pstDhcpcWaitFreeTableHead = NULL;
DHCPC_MANAGEBLK           *g_pstScanWaitFreeTablePos = NULL;
DHCPC_MANAGEBLK           *g_pstPreScanWaitFreeTablePos = NULL;


/*****************************************************************************
 �� �� ��  : DHCPC_CreateDhcpcContext
 ��������  : ����DHCPC���ƿ�
 �������  : DHCPC_CTRLBLK **ppstDhcpcContext
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��13��
    ��    ��   : tianyang 00144555
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_CreateDhcpcContext(DHCPC_CTRLBLK **ppstDhcpcContext)
{
    ULONG ulRet = 0;

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_CRT_NUM);

    if ( NULL == ppstDhcpcContext )
    {
        VOS_DBGASSERT(0);
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_CRT_INPUT_NULL);
        return VOS_ERR;
    }

    /* Ϊ���ƿ������ڴ� */
    ulRet = DHCPC_CreateNewDhcpcBlock();
    if ( VOS_OK != ulRet )
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_CRT_CRTNEW_FAIL);
        return VOS_ERR;
    }

    /* �ӿ��п��ƿ��л�ȡ���ÿ��ƿ� */
    *ppstDhcpcContext = DHCPC_GetDhcpcBlockfromIdleTable();
    if ( NULL == *ppstDhcpcContext )
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_CRT_GETBLK_FAIL);
        return VOS_ERR;
    }

    /* ���� */

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : DHCPC_GetDhcpcBlockfromIdleTable
 ��������  : ��IDLE���ƿ����л�ȡ���õĿ��ƿ�
 �������  : VOID
 �������  : ��
 �� �� ֵ  : DHCPC_CTRLBLK *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��19��
    ��    ��   : tianyang 00144555
    �޸�����   : �����ɺ���

*****************************************************************************/
DHCPC_CTRLBLK *DHCPC_GetDhcpcBlockfromIdleTable(VOID)
{
    DHCPC_CTRLBLK *pstDhcpcContext = NULL;

    if ( NULL == g_pstDhcpIdleTableHead )
    {
        VOS_DBGASSERT(0);
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_CRT_CRTNEW_FAIL);
        return NULL;
    }

    /* ���п��ƿ��������п��ƿ飬��ӿ��п��ƿ�����ֱ�ӻ�ȡ���ƿ� */
    pstDhcpcContext = g_pstDhcpIdleTableHead;

    /* ���ýڵ�ӿ��п��ƿ���ɾ�� */
    g_pstDhcpIdleTableHead = g_pstDhcpIdleTableHead->pstNextNode;

    if ( NULL != g_pstDhcpIdleTableHead )
    {
        g_pstDhcpIdleTableHead->pstPreNode = NULL;
    }

    pstDhcpcContext->pstNextNode = NULL;
    pstDhcpcContext->ucUsedFlag = DHCPC_BLOCK_USED;

    /* ��¼��ʹ�ÿ��ƿ�ĸ��� */
    g_ulDhcpcBlkUsedNum++;

    g_ulDhcpcBlkIdleNum--;

    /* ���� */

    return pstDhcpcContext;
}

/*****************************************************************************
 �� �� ��  : DHCPC_CreateNewDhcpcBlock
 ��������  : �������ڴ������ƿ飬�����ڴ��������
 �������  : VOID
 �������  : ��
 �� �� ֵ  : DHCPC_CTRLBLK *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��19��
    ��    ��   : tianyang 00144555
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_CreateNewDhcpcBlock(VOID)
{
    DHCPC_MANAGEBLK *pstTempManageBlk = NULL;

    if ( NULL != g_pstDhcpIdleTableHead )
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_CRTNEW_NOTMALLOC);
        return VOS_OK;
    }

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_CRTNEW_MALLOC);

    pstTempManageBlk = DHCP_Malloc(DHCPC_HANDLE, sizeof(DHCPC_MANAGEBLK));
    if ( NULL == pstTempManageBlk )
    {
        VOS_DBGASSERT(0);
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_CRTNEW_MALLOC_FAIL);
        return VOS_ERR;
    }

    g_ulDhcpcManageMemNum++;

    DHCP_MemZero(pstTempManageBlk, sizeof(DHCPC_MANAGEBLK));

    /* �����ڴ�ͳһ���������Ա����ú��ͷ� */
    DHCPC_MangeNewBlock(pstTempManageBlk);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : DHCPC_MangeNewBlock
 ��������  : ��������Ŀ��ƿ��ڴ��������п��ƿ����͵ȴ��ͷ�����
 �������  : DHCPC_CTRLBLK *pstDchpcContext
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��19��
    ��    ��   : tianyang 00144555
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID DHCPC_MangeNewBlock(DHCPC_MANAGEBLK *pstManageBlk)
{
    ULONG ulBlockIndex = 0;

    if ( NULL == pstManageBlk )
    {
        VOS_DBGASSERT(0);
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_MANAGE_INPUT_NULL);
        return;
    }
    /* �����ƿ����IDLE���У����ں���ʹ�� */
    for ( ulBlockIndex = 0 ; ulBlockIndex < DHCP_MAX_MALLBLOCKNUM ; ulBlockIndex++ )
    {
        /* ������п��ƿ��� */
        DHCPC_InsertIdleTable(&(pstManageBlk->stDhcpcBlk[ulBlockIndex]));
    }

    /* �������Ƭ�ڴ����ȴ��ͷŵ������� */
    DHCPC_InsertWaitFreeTable(pstManageBlk);

    return;
}

/*****************************************************************************
 �� �� ��  : DHCPC_QueryDhcpcContext
 ��������  : ���ҿ��ƿ�
 �������  : UCHAR ucIpType
             ULONG ulTeidc
             DHCPC_CTRLBLK **ppstDhcpcContext
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��13��
    ��    ��   : tianyang 00144555
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_QueryDhcpcContext(UCHAR ucIpType, ULONG ulTeidc, DHCPC_CTRLBLK **ppstDhcpcContext)
{
    ULONG ulHashKey = 0;
    DHCPC_CTRLBLK *pstCurDchpcContext = NULL;

    if ( NULL == ppstDhcpcContext )
    {
        VOS_DBGASSERT(0);
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_QRY_INPUT_NULL);
        return VOS_ERR;
    }

    ulHashKey = DHCPC_GetCtlBlkHashKey(ulTeidc);

    if ( LAP_IPV4 == ucIpType )
    {
        pstCurDchpcContext = g_pstDhcpcCtrlBlkRec[ulHashKey];
    }
    else
    {
        pstCurDchpcContext = g_pstDhcpcIpv6CtrlBlkRec[ulHashKey];
    }

    /* ��������HASHKEY��ȵĿ��ƿ� */
    while ( NULL != pstCurDchpcContext )
    {
        if ( pstCurDchpcContext->ulTEIDC == ulTeidc)
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_QRY_OK);
            *ppstDhcpcContext = pstCurDchpcContext;

            return VOS_OK;
        }

        pstCurDchpcContext = pstCurDchpcContext->pstNextNode;

    }

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_QRY_FAIL);
    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : DHCPC_AddDhcpcContextToPool
 ��������  : �����ƿ���������
 �������  : DHCPC_CTRLBLK *pstDhcpcContext
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��13��
    ��    ��   : tianyang 00144555
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_AddDhcpcContextToPool(DHCPC_CTRLBLK *pstDhcpcContext)
{
    ULONG ulHashKey = 0;
    DHCPC_CTRLBLK *pstTmpDhcpcContext = NULL;

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_ADD_NUM);

    if ( NULL == pstDhcpcContext )
    {
        VOS_DBGASSERT(0);
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_ADD_INPUT_NULL);
        return VOS_ERR;
    }

    /* ȷ��Ҫ��ӵĽڵ��Ƿ��Ѿ����� */
    (VOID)DHCPC_QueryDhcpcContext(LAP_IPV6, pstDhcpcContext->ulTEIDC, &pstTmpDhcpcContext);
    if ( NULL != pstTmpDhcpcContext )
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_ADD_CONFLICT);
        return VOS_ERR;
    }

    ulHashKey = DHCPC_GetCtlBlkHashKey(pstDhcpcContext->ulTEIDC);

    pstTmpDhcpcContext = g_pstDhcpcIpv6CtrlBlkRec[ulHashKey];

    pstDhcpcContext->pstNextNode = pstTmpDhcpcContext;

    if ( NULL != pstTmpDhcpcContext )
    {
        pstTmpDhcpcContext->pstPreNode = pstDhcpcContext;
    }

    g_pstDhcpcIpv6CtrlBlkRec[ulHashKey] = pstDhcpcContext;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : DHCPC_MallocDhcpcContext
 ��������  : ������ƿ麯��
 �������  : UCHAR ucIpType
             ULONG ulTeidc
             DHCPC_CTRLBLK **ppstDhcpcContext
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��9��3��
    ��    ��   : tianyang 00144555
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_MallocDhcpcContext(UCHAR ucIpType, ULONG ulTeidc, DHCPC_CTRLBLK **ppstDhcpcContext)
{
    ULONG ulRet = 0;

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_MALLOC_NUM);

    if ( NULL == ppstDhcpcContext )
    {
        VOS_DBGASSERT(0);
        return VOS_ERR;
    }

    if ( LAP_IPV4 == ucIpType )
    {
        /* DHCPv4���� */
    }
    else
    {
        /* DHCPv6���� */
        ulRet = DHCPC_CreateDhcpcContext(ppstDhcpcContext);
        if ( ulRet != VOS_OK )
        {
            return VOS_ERR;
        }

        (*ppstDhcpcContext)->ulTEIDC = ulTeidc;

        ulRet = DHCPC_AddDhcpcContextToPool(*ppstDhcpcContext);
        if ( ulRet != VOS_OK )
        {
            g_ulDhcpcBlkUsedNum--;

            DHCPC_InsertIdleTable(*ppstDhcpcContext);

            *ppstDhcpcContext = NULL;

            return VOS_ERR;
        }
    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : DHCPC_FreeDhcpcContext
 ��������  : �ӿ�������ɾ�����ƿ�
 �������  : UCHAR ucIpType, ULONG ulTeidc
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��13��
    ��    ��   : tianyang 00144555
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_FreeDhcpcContext(UCHAR ucIpType, ULONG ulTeidc)
{
    ULONG ulRet = 0;
    ULONG ulHashKey = 0;
    DHCPC_CTRLBLK *pstCurDchpcContext = NULL;

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_DEL_NUM);

    ulHashKey = DHCPC_GetCtlBlkHashKey(ulTeidc);

    if ( LAP_IPV4 == ucIpType )
    {
        pstCurDchpcContext = g_pstDhcpcCtrlBlkRec[ulHashKey];
    }
    else
    {
        pstCurDchpcContext = g_pstDhcpcIpv6CtrlBlkRec[ulHashKey];
    }

    /* ��������HASHKEY��ȵĿ��ƿ� */
    while ( NULL != pstCurDchpcContext )
    {
        if ( pstCurDchpcContext->ulTEIDC != ulTeidc)
        {
            pstCurDchpcContext = pstCurDchpcContext->pstNextNode;

            continue;
        }

        /* ��������ɾ���ڵ� */
        if ( LAP_IPV4 == ucIpType )
        {
            ulRet = DHCPC_DelSingleBlkFromTable(pstCurDchpcContext, &(g_pstDhcpcCtrlBlkRec[ulHashKey]));
        }
        else
        {
            ulRet = DHCPC_DelSingleBlkFromTable(pstCurDchpcContext, &(g_pstDhcpcIpv6CtrlBlkRec[ulHashKey]));
        }

        if ( VOS_OK != ulRet )
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_DEL_FAIL);
            return VOS_ERR;
        }

        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_DEL_OK);

        /* ������п��ƿ��� */
        DHCPC_InsertIdleTable(pstCurDchpcContext);

        if ( g_ulDhcpcBlkUsedNum > 0 )
        {
            g_ulDhcpcBlkUsedNum--;
        }

        return VOS_OK;

    }

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_DEL_NOTFOUND);

    return VOS_ERR;
}

/*****************************************************************************
 �� �� ��  : DHCPC_InsertIdleTable
 ��������  : ���հ׵Ŀ��ƿ������������Ա�����ʹ��
 �������  : DHCPC_CTRLBLK *pstDhcpcContext
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��13��
    ��    ��   : tianyang 00144555
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID DHCPC_InsertIdleTable(DHCPC_CTRLBLK *pstDhcpcContext)
{
    DHCPC_CTRLBLK *pstTmpDhcpcContext = NULL;

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_INSERTIDLE_NUM);

    if ( NULL == pstDhcpcContext )
    {
        VOS_DBGASSERT(0);
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_INSERTIDLE_INPUT_NULL);
        return;
    }

    /* ��տ��ƿ����� */
    DHCP_MemZero(pstDhcpcContext, sizeof(DHCPC_CTRLBLK));

    pstTmpDhcpcContext = g_pstDhcpIdleTableHead;

    pstDhcpcContext->pstNextNode = pstTmpDhcpcContext;

    if ( NULL != pstTmpDhcpcContext )
    {
        pstTmpDhcpcContext->pstPreNode = pstDhcpcContext;
    }

    g_pstDhcpIdleTableHead = pstDhcpcContext;

    g_ulDhcpcBlkIdleNum++;

    return;
}

/*****************************************************************************
 �� �� ��  : DHCPC_DelWholeBlkFromIdleTable
 ��������  : �������ͷŵ������ڴ������еĿ��ƿ�ӿ�������ɾ��
 �������  : DHCPC_CTRLBLK *pstDhcpcContext
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��17��
    ��    ��   : tianyang 00144555
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_DelWholeBlkFromIdleTable(DHCPC_CTRLBLK *pstDhcpcContext)
{
    ULONG ulIndex = 0;
    ULONG ulRet = 0;

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_DELWHOLE_NUM);

    if ( NULL == pstDhcpcContext )
    {
        VOS_DBGASSERT(0);
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_DELWHOLE_INPUT_FAIL);
        return VOS_ERR;
    }

    for ( ulIndex = 0 ; ulIndex < DHCP_MAX_MALLBLOCKNUM ; ulIndex++ )
    {
        ulRet = DHCPC_DelSingleBlkFromTable(pstDhcpcContext + ulIndex, &g_pstDhcpIdleTableHead);
        if ( VOS_OK != ulRet )
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_DELWHOLE_DELSING_FAIL);
            return VOS_ERR;
        }

        if ( g_ulDhcpcBlkIdleNum > 0 )
        {
            g_ulDhcpcBlkIdleNum--;
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : DHCPC_DelSingleBlkFromIdleTable
 ��������  : ���������ƿ�ӿ�������ɾ��
 �������  : DHCPC_CTRLBLK *pstDhcpcContext
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��17��
    ��    ��   : tianyang 00144555
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_DelSingleBlkFromTable(DHCPC_CTRLBLK *pstDhcpcContext, DHCPC_CTRLBLK **ppstDhcpcContextHead)
{
    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_DELSINGLE_NUM);

    if ( (NULL == pstDhcpcContext) || (NULL == ppstDhcpcContextHead) )
    {
        VOS_DBGASSERT(0);
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_DELSINGLE_INPUT_FAIL);
        return VOS_ERR;
    }

    if ( *ppstDhcpcContextHead == pstDhcpcContext )
    {
        /* ͷ�ڵ� */
        *ppstDhcpcContextHead = (*ppstDhcpcContextHead)->pstNextNode;

        if ( NULL != *ppstDhcpcContextHead )
        {
            (*ppstDhcpcContextHead)->pstPreNode = NULL;
        }

    }
    else if ( NULL == pstDhcpcContext->pstNextNode )
    {
        /* β�ڵ� */
        if ( NULL == pstDhcpcContext->pstPreNode )
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_DELSINGLE_TAIL_FAIL);
            return VOS_ERR;
        }

        pstDhcpcContext->pstPreNode->pstNextNode = NULL;
    }
    else
    {
        if ( (NULL == pstDhcpcContext->pstPreNode) || (NULL == pstDhcpcContext->pstNextNode) )
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_DELSINGLE_FAIL);
            return VOS_ERR;
        }

        pstDhcpcContext->pstPreNode->pstNextNode = pstDhcpcContext->pstNextNode;
        pstDhcpcContext->pstNextNode->pstPreNode = pstDhcpcContext->pstPreNode;
    }

    DHCP_MemZero(pstDhcpcContext, sizeof(DHCPC_CTRLBLK));

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : DHCPV6C_QueryDhcpBlockBySeq
 ��������  : ����SeqNo����dhcp���ƿ�
 �������  : USHORT usSeqNo
             DHCPC_CTRLBLK **ppstDhcpcContext
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��11��
    ��    ��   : jixiaoming 00180244
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPV6C_QueryDhcpBlockBySeq(USHORT usSeqNo, DHCPC_CTRLBLK **ppstDhcpcContext)
{
    ULONG   ulReturn = VOS_ERR;
    ULONG   ulTeidc = 0;
    UCHAR   ucIpType = 0;

    ulReturn = DHCPV6C_QuryTeidcBySeqNum(usSeqNo, &ulTeidc, &ucIpType);
    if (VOS_OK != ulReturn)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SERVER_QRY_TEIDC_FAIL);
        return ulReturn;
    }

    ulReturn = DHCPC_QueryDhcpcContext(ucIpType, ulTeidc, ppstDhcpcContext);
    if (VOS_OK != ulReturn)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SERVER_QRY_CONTEXT_FAIL);
        return ulReturn;
    }

    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : DHCPC_InsertWaitFreeTable
 ��������  : ����������ڴ����ȴ��ͷ�����
 �������  : DHCPC_CTRLBLK *pstDhcpcContext
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��13��
    ��    ��   : tianyang 00144555
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID DHCPC_InsertWaitFreeTable(DHCPC_MANAGEBLK *pstManageBlk)
{
    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_INSERTWAIT_NUM);

    if ( NULL == pstManageBlk )
    {
        VOS_DBGASSERT(0);
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_INSERTWAIT_INPUT_NULL);
        return;
    }

    /* ���� */
    pstManageBlk->pstNextNode = g_pstDhcpcWaitFreeTableHead;
    g_pstDhcpcWaitFreeTableHead = pstManageBlk;

    return;
}

/*****************************************************************************
 �� �� ��  : DHCPC_FreeDhcpcCtrlBlkMem
 ��������  : �ͷ��ڴ�
 �������  : VOID
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��14��
    ��    ��   : tianyang 00144555
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID DHCPC_FreeDhcpcCtrlBlkMem(VOID)
{
    ULONG ulScanIndex = 0;
    DHCPC_MANAGEBLK *pstPreWaitFreeBlk = NULL;
    DHCPC_MANAGEBLK *pstCurWaitFreeBlk = NULL;
    DHCPC_MANAGEBLK *pstTmpWaitFreeBlk = NULL;

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_FREEMEM_NUM);

    if ( NULL == g_pstScanWaitFreeTablePos )
    {
        /* ����Ѿ���ѵ��ɣ����ǵ�һ�Σ����ͷ�ڵ㿪ʼ */
        g_pstScanWaitFreeTablePos = g_pstDhcpcWaitFreeTableHead;
        g_pstPreScanWaitFreeTablePos = g_pstDhcpcWaitFreeTableHead;

        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_FREEMEM_ALL);
    }

    pstCurWaitFreeBlk = g_pstScanWaitFreeTablePos;
    pstPreWaitFreeBlk = g_pstPreScanWaitFreeTablePos;

    while ( (NULL != pstCurWaitFreeBlk) && (ulScanIndex < DHCP_BLOCK_MAX_SACNNUM) )
    {
        ulScanIndex++;
        /* �жϸÿ��ڴ��еĿ��ƿ��Ƿ���ʹ�ã����û��ʹ�����ͷ� */
        if ( VOS_TRUE != DHCPC_BlkMemCanbeFree(pstCurWaitFreeBlk->stDhcpcBlk) )
        {
            pstPreWaitFreeBlk = pstCurWaitFreeBlk;
            pstCurWaitFreeBlk = pstCurWaitFreeBlk->pstNextNode;

            continue;
        }

        pstTmpWaitFreeBlk = pstCurWaitFreeBlk;

        /* ����ÿ��ڴ�����ʹ�ã����Ƚ��ÿ��ڴ��е�ÿ�����ƿ��IDLE����ɾ�� */
        if ( VOS_OK != DHCPC_DelWholeBlkFromIdleTable(pstTmpWaitFreeBlk->stDhcpcBlk) )
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_FREEMEM_DELBLK_FAIL);
            pstPreWaitFreeBlk = pstCurWaitFreeBlk;
            pstCurWaitFreeBlk = pstCurWaitFreeBlk->pstNextNode;

            continue;
        }

        /* �ÿ��ڴ�����п��ƿ춼��IDLE����ɾ���󣬽���Ƭ�ڴ�ӵȴ��ͷ�����
           ɾ�� */
        if ( VOS_OK != DHCPC_DelNodeFromWaitFreeTable(&pstPreWaitFreeBlk, pstTmpWaitFreeBlk) )
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_FREEMEM_DELNOD_FAIL);
            pstPreWaitFreeBlk = pstCurWaitFreeBlk;
            pstCurWaitFreeBlk = pstCurWaitFreeBlk->pstNextNode;
            continue;
        }

        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_FREEMEM_OK);

        pstCurWaitFreeBlk = pstCurWaitFreeBlk->pstNextNode;

        DHCP_MemZero(pstTmpWaitFreeBlk, sizeof(DHCPC_MANAGEBLK));

        DHCP_Free(DHCPC_HANDLE, pstTmpWaitFreeBlk);
    }

    /* ��¼�´�ɨ���λ�� */
    g_pstScanWaitFreeTablePos = pstCurWaitFreeBlk;
    g_pstPreScanWaitFreeTablePos = pstPreWaitFreeBlk;

    return;
}

/*****************************************************************************
 �� �� ��  : DHCPC_DelNodeFromWaitFreeTable
 ��������  : ����Ƭ�ڴ�ӵȴ��ͷ�����ɾ��
 �������  : DHCPC_MANAGEBLK *pstWaitDelBlk
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��19��
    ��    ��   : tianyang 00144555
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_DelNodeFromWaitFreeTable(DHCPC_MANAGEBLK **pstPreWaitFreeBlk, DHCPC_MANAGEBLK *pstWaitDelBlk)
{
    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_DELWAITNOD_NUM);

    if ( (NULL == pstWaitDelBlk) || (NULL == pstPreWaitFreeBlk) )
    {
        VOS_DBGASSERT(0);

        return VOS_ERR;
    }
    if ( pstWaitDelBlk == g_pstDhcpcWaitFreeTableHead )
    {
        /* ͷ�ڵ� */
        g_pstDhcpcWaitFreeTableHead = g_pstDhcpcWaitFreeTableHead->pstNextNode;
        *pstPreWaitFreeBlk = g_pstDhcpcWaitFreeTableHead;
    }
    else if ( *pstPreWaitFreeBlk == pstWaitDelBlk )
    {
        //pstWaitDelBlk = pstWaitDelBlk->pstNextNode;
// *pstPreWaitFreeBlk = pstWaitDelBlk;
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_DELWAITNOD_NODEQU);
        /* �˴�������󣬷���errĿ����Ϊ�˽�ǰ��ڵ�ֿ� */
        return VOS_ERR;
    }
    else
    {
        if ( pstWaitDelBlk != (*pstPreWaitFreeBlk)->pstNextNode )
        {
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_DELWAITNOD_ERR);
            return VOS_ERR;
        }

        (*pstPreWaitFreeBlk)->pstNextNode = pstWaitDelBlk->pstNextNode;
    }

    if ( g_ulDhcpcManageMemNum > 0 )
    {
        g_ulDhcpcManageMemNum--;
    }
    else
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_DELWAITNOD_COUNT_ERR);
    }

    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : DHCPC_BlkMemCanbeFree
 ��������  : �жϸ�Ƭ�ڴ��ܷ��ͷ�
 �������  : DHCPC_CTRLBLK *pstDhcpcContext
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��14��
    ��    ��   : tianyang 00144555
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_BlkMemCanbeFree(DHCPC_CTRLBLK *pstDhcpcContext)
{
    ULONG ulIndex = 0;

    if ( NULL == pstDhcpcContext )
    {
        VOS_DBGASSERT(0);
        return VOS_FALSE;
    }

    for ( ulIndex = 0 ; ulIndex < DHCP_MAX_MALLBLOCKNUM ; ulIndex++ )
    {
        if ( DHCPC_BLOCK_USED == (pstDhcpcContext + ulIndex)->ucUsedFlag )
        {
            return VOS_FALSE;
        }
    }

    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_BLK_MEMCANBEFREE_NUM);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : DHCPC_GetCtlBlkUsedNum
 ��������  : ��ȡ��ʹ�õ�DHCPC���ƿ����
 �������  : VOID
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��23��
    ��    ��   : tianyang 00144555
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_GetCtlBlkUsedNum(VOID)
{
    return g_ulDhcpcBlkUsedNum;
}

/*****************************************************************************
 �� �� ��  : DHCPC_GetIdelBlkNum
 ��������  : ��ȡ���е�DHCPC���ƿ����
 �������  : VOID
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��23��
    ��    ��   : tianyang 00144555
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_GetIdelBlkNum(VOID)
{
    return g_ulDhcpcBlkIdleNum;
}

/*****************************************************************************
 �� �� ��  : DHCPC_GetManageMemNum
 ��������  : ��ȡ��������ڴ�ĸ���
 �������  : VOID
 �������  : ��
 �� �� ֵ  : ULONG
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��7��23��
    ��    ��   : tianyang 00144555
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_GetManageMemNum(VOID)
{
    return g_ulDhcpcManageMemNum;
}
