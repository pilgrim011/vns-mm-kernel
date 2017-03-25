/******************************************************************************

                  ��Ȩ���� (C), 2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : BST_PAL_Sync.c
  �� �� ��   : ����
  ��    ��   : d00173029
  ��������   : 2014��06��28��
  ����޸�   :
  ��������   : ʵ��WIN32����ϵͳ�߳�ͨ�����䡢�ź���
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��06��28��
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
#include "BST_PAL_Sync.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_PAL_SYNC_C
/*lint +e767*/

/******************************************************************************
   2 ����ʵ��
******************************************************************************/

/*****************************************************************************
 �� �� ��  : BST_OS_PalRecvSem
 ��������  : ��ȡ�ź���ƽ̨����ʵ��
 �������  : BST_OS_PAL_SEM_T stSemHandle,  �ź������
             BST_UINT32 ulTimeOut           �ȴ���ʱʱ��
 �������  : ��
 �� �� ֵ  : BST_ERR_ENUM_UINT8             BST_ERR_ILLEGAL_PARAM   �������
                                            BST_ERR_SYNC_TIMEOUT    �ȴ���ʱ
                                            BST_NO_ERROR_MSG        �ɹ���ȡ
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_ERR_ENUM_UINT8 BST_OS_PalRecvSem(
    BST_OS_PAL_SEM_T    stSemHandle,
    BST_UINT32          ulTimeOut )
{

    if( BST_PAL_IsSemInValid( stSemHandle ) )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }
    
#if (VOS_RTOSCK == VOS_OS_VER)
    if( VOS_OK == VOS_SmP(stSemHandle, ulTimeOut))
#else
    if( OK == semTake(stSemHandle, (BST_INT32)ulTimeOut))
#endif
    {
        return BST_NO_ERROR_MSG;
    }
    else
    {
        return BST_ERR_SYNC_TIMEOUT;
    }
}
/*****************************************************************************
 �� �� ��  : BST_OS_PalSendSem
 ��������  : �����ź���ƽ̨����ʵ��
 �������  : BST_OS_PAL_SEM_T stSemHandle,  �ź������
             BST_VOID *pvArg                ���Ͳ���(Balongƽ̨����Ҫ)
 �������  : ��
 �� �� ֵ  : BST_ERR_ENUM_UINT8             BST_ERR_ILLEGAL_PARAM   �������
                                            BST_NO_ERROR_MSG        �ɹ�����
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_OS_PalSendSem(
    BST_OS_PAL_SEM_T    stSemHandle,
    BST_VOID           *pvArg )
{
    if( BST_PAL_IsSemInValid( stSemHandle ) )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }
    
#if (VOS_RTOSCK == VOS_OS_VER)
    if( VOS_OK == VOS_SmV(stSemHandle) )
#else
    if( OK == semGive(stSemHandle) )
#endif
    {
        return BST_NO_ERROR_MSG;
    }
    else
    {
        return BST_ERR_ILLEGAL_PARAM;
    }
}
/*****************************************************************************
 �� �� ��  : BST_OS_PalDeleteSem
 ��������  : ɾ��һ���ź���ƽ̨����ʵ��
 �������  : BST_OS_PAL_SEM_T stSemHandle   �ź������
 �������  : ��
 �� �� ֵ  : BST_ERR_ENUM_UINT8             BST_ERR_ILLEGAL_PARAM   �������
                                            BST_NO_ERROR_MSG        �ɹ�ɾ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_ERR_ENUM_UINT8  BST_OS_PalDeleteSem( BST_OS_PAL_SEM_T stSemHandle )
{
    if( BST_PAL_IsSemInValid( stSemHandle ) )
    {
        return BST_ERR_ILLEGAL_PARAM;
    }
    
#if (VOS_RTOSCK == VOS_OS_VER)
    VOS_SmDelete( stSemHandle );
#else
    semDelete( stSemHandle );
#endif

    return BST_NO_ERROR_MSG;
}
/*****************************************************************************
 �� �� ��  : BST_OS_PalCreateSem
 ��������  :����һ���ź���
 �������  : BST_OS_PAL_SEM_T stSemHandle   �ź������
 �������  : ��
 �� �� ֵ  : BST_ERR_ENUM_UINT8             BST_ERR_ILLEGAL_PARAM   �������
                                            BST_NO_ERROR_MSG        �ɹ�����
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_OS_PAL_SEM_T  BST_OS_PalCreateSem( BST_UINT32 ulSmInit )
{
    #if (VOS_RTOSCK == VOS_OS_VER) 
    BST_OS_PAL_SEM_T stSemHandle;
    if(VOS_OK != VOS_SmCCreate("BST",ulSmInit,VOS_SEMA4_PRIOR,&stSemHandle))
    {
        return BST_NULL_PTR;
    }
    else
    {
        return stSemHandle;
    }
    #else
    return semCCreate(SEM_Q_PRIORITY, (BST_INT32)ulSmInit);
    #endif
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


