/******************************************************************************
  �� �� ��   : BST_PAL_ACom.c
  �� �� ��   : ����
  ��    ��   : d00173029
  ��������   : 2014��4��16��
  ����޸�   :
  ��������   : ʵ��APͨ�ſ������ӿ�
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2014��07��3��
    ��    ��   : d00173029
    �޸�����   : �����ļ�

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "BST_Platform.h"
#include "BST_PAL_Acom.h"
#include "BST_OS_Memory.h"
#include "vos.h"
#if (VOS_RTOSCK == VOS_OS_VER)
#include "sre_sem.h"
#else
#include <semLib.h>
#endif

#include "PsLogdef.h"
#include "PsCommonDef.h"

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_PAL_ACOM_C
/*lint +e767*/
/******************************************************************************
   2 �궨��
******************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/

/******************************************************************************
   4 ˽�ж���
******************************************************************************/

/******************************************************************************
   5 ȫ�ֱ�������
******************************************************************************/
BST_DRV_READ_T                  g_BstPalAcommRcvCb      = BST_NULL_PTR;
/******************************************************************************
   6 ����ʵ��
******************************************************************************/

/*****************************************************************************
 �� �� ��  : BST_Pal_DrvAcomSend
 ��������  : ͨ���ʼ��������ݵ�AP
 �������  : BST_UINT32 ulLength,   ��Ϣ����
             BST_UINT8 *pucData     ��Ϣ����
 �������  : ��
 �� �� ֵ  : BST_ERR_ENUM_UINT8     �̶�NO_ERR��Ϊ�������
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_Pal_DrvAcomSend( BST_UINT32 ulLength, BST_UINT8 *pucData )
{
#ifndef BST_MODEM_SELF
#ifndef BST_PEAK_SPEED_TEST

    BST_ACOM_MSG_STRU          *pstAcorMsg;
    BST_UINT8                  *ulTmpAddr;
    BST_ASSERT_NULL_RTN( pucData, BST_ERR_INVALID_PTR );
    pstAcorMsg                  = BST_ACOMM_ALLOC_MSG_WITH_HDR( ulLength );
    BST_ASSERT_NULL_RTN( pstAcorMsg, BST_ERR_NO_MEMORY );
    ulTmpAddr                   = (pstAcorMsg->aucValue);
    BST_OS_MEMCPY((BST_VOID*)ulTmpAddr, pucData, ulLength);

    pstAcorMsg->ulLen           = ulLength;
    BST_ACOMM_CFG_MSG_HDR( pstAcorMsg, ACPU_PID_BASTET_COMM );
    BST_ACOMM_SEND_MSG( pstAcorMsg );

#endif
#endif
    return BST_NO_ERROR_MSG;
}
/*****************************************************************************
 �� �� ��  : BST_Pal_DrvAcomRecv
 ��������  : �յ�AP���͵�����
 �������  : BST_UINT32 ulLength,   ��Ϣ����
             BST_UINT8 *pucData     ��Ϣ����
 �������  :
 �� �� ֵ  : BST_UINT32             ʱ�䷢�ͳɹ����ݳ���
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_UINT32 BST_Pal_DrvAcomRecv( BST_UINT32 ulLength, BST_UINT8 *pucData )
{
#ifndef BST_MODEM_SELF
    BST_ACOM_MSG_STRU              *pstAcoreMsg;

    if ( BST_NULL_PTR == pucData )
    {
        return 0;
    }

    pstAcoreMsg                     = ( BST_ACOM_MSG_STRU * )pucData;
    if ( 0 == pstAcoreMsg->ulLen )
    {
        return 0;
    }
    BST_DBG_LOG2( "BST_Pal_DrvAcomRecv, Length=%u, data[0]=u%",
                  pstAcoreMsg->ulLen, pstAcoreMsg->aucValue[0] );

    BST_PalAcomRcvCb( pstAcoreMsg->ulLen, pstAcoreMsg->aucValue );
#endif
    return ulLength;
}

/*****************************************************************************
 �� �� ��  : BST_Pal_DrvAcomInit
 ��������  : ��ʼ��APͨ�ſ���ز���
 �������  :  BST_DRV_READ_T pfRcvCb    �յ����ݺ�ص����
 �������  : ��
 �� �� ֵ  : BST_ERR_ENUM_UINT8         �ɹ�:����BST_NO_ERROR_MSG
                                        ʧ��:����BST_ERR_ILLEGAL_PARAM
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_Pal_DrvAcomInit( BST_DRV_READ_T pfRcvCb )
{
    if( BST_NULL_PTR == pfRcvCb )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }
    g_BstPalAcommRcvCb                  = pfRcvCb;
    return BST_NO_ERROR_MSG;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

