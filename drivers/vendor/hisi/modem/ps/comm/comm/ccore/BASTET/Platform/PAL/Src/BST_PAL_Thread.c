/******************************************************************************

                  ��Ȩ���� (C), 2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : BST_PAL_Thread.c
  �� �� ��   : ����
  ��    ��   : d00173029
  ��������   : 2014��05��04��
  ����޸�   :
  ��������   : ����ϵͳ�̴߳���
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
#include "BST_Typedefine.h"
#include "BST_PAL_Thread.h"
/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_BST_PAL_THREAD_C
/*lint +e767*/
/******************************************************************************
   2 ����ʵ��
******************************************************************************/

/*****************************************************************************
 �� �� ��  : BST_OS_PalInitLock
 ��������  : ��ʼ��ϵͳ��(�սӿڣ�Balongƽ̨����Ҫ)
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_VOID BST_OS_PalInitLock( BST_VOID )
{
}

/*****************************************************************************
 �� �� ��  : BST_OS_PalInitSpinLock
 ��������  : ��ʼ��������
 �������  : BST_OS_PAL_SPINLOCK_T *pSpinLock  ���������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_VOID BST_OS_PalInitSpinLock( BST_OS_PAL_SPINLOCK_T *pSpinLock )
{
    if( BST_NULL_PTR == pSpinLock )
    {
        return;
    }
    VOS_SpinLockInit( pSpinLock );
}
/*****************************************************************************
 �� �� ��  : BST_OS_PalSpinLock
 ��������  : ����������ƽ̨����ʵ��
 �������  : BST_OS_PAL_SPINLOCK_T *pSpinLock   ���������
 �������  : ��
 �� �� ֵ  : BST_UINT32                         �����������
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_UINT32 BST_OS_PalSpinLock( BST_OS_PAL_SPINLOCK_T *pSpinLock )
{
    BST_UINT32                          ulFlags = 0;
    VOS_SpinLockIntLock( pSpinLock, ulFlags );
    return ulFlags;
}
/*****************************************************************************
 �� �� ��  : BST_OS_PalSpinUnLock
 ��������  : ���������ƽ̨����ʵ��
 �������  : BST_OS_PAL_SPINLOCK_T *pSpinLock,  ���������
             BST_UINT32 ulCounter               �������
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_VOID BST_OS_PalSpinUnLock( BST_OS_PAL_SPINLOCK_T *pSpinLock, BST_UINT32 ulCounter )
{
    if( BST_NULL_PTR == pSpinLock )
    {
        return;
    }
    VOS_SpinUnlockIntUnlock( pSpinLock, ulCounter );
}
/*****************************************************************************
 �� �� ��  : BST_OS_PalTaskEntry
 ��������  : ͨ��������ں�����ʵ��4��νӿ�ת��Ϊ2��νӿ�
 �������  : BST_UINT32 ulPara1,    ����ִ�е�����ָ��(BST_OS_THREAD_T)
             BST_UINT32 ulPara2,    �����������(BST_VOID *)
             BST_UINT32 ulPara3,
             BST_UINT32 ulPara4
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_VOID BST_OS_PalTaskEntry( BST_UINT32 ulPara1, BST_UINT32 ulPara2,
                              BST_UINT32 ulPara3, BST_UINT32 ulPara4 )
{
    BST_OS_THREAD_T     pTaskFun;
    BST_VOID           *pArg;

    pTaskFun            = ( BST_OS_THREAD_T )ulPara1;
    pArg                = ( BST_VOID * )ulPara2;

    if ( BST_NULL_PTR == pTaskFun )
    {
        return;
    }

    pTaskFun( pArg );
}

/*****************************************************************************
 �� �� ��  : BST_OS_PalCreateThread
 ��������  : �½��߳�
 �������  : BST_INT8* pacTaskName,         ��������
             BST_OS_THREAD_T  ThreadEntry,  ������ں���
             BST_VOID* pvArg,               �����������
             BST_UINT32 ulStackSize,        �����ջ���
             BST_UINT32 ulPrio              �������ȼ�
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ  :
    1.��    ��   : 2014��06��04��
      ��    ��   : d00173029
      �޸�����   : �����ɺ���
*****************************************************************************/
BST_VOID BST_OS_PalCreateThread (
    BST_INT8       *pacTaskName,
    BST_OS_THREAD_T ThreadEntry,
    BST_VOID       *pvArg,
    BST_UINT32      ulStackSize,
    BST_UINT32      ulPrio )
{
    BST_UINT32  aulTaskParam[ VOS_TARG_NUM ] = { 0 };
    BST_UINT32  ulTaskId;
    BST_UINT32  ulRet;
    BST_UINT32  ulRealPriority;

#if( VOS_TARG_NUM < 2 )

    return;
#endif

    aulTaskParam[0] = ( BST_UINT32 )ThreadEntry;
    aulTaskParam[1] = ( BST_UINT32 )pvArg;

    ulRet           =  VOS_GetFIdRelPri( ( enum VOS_PRIORITY_DEFINE )ulPrio, &ulRealPriority );
    if ( ulRet != VOS_OK )
    {
        BST_RLS_LOG( "BST_OS_PalCreateThread: VOS_GetFIdRelPri Failed!" );
        return;
    }

    VOS_CreateTask( ( BST_CHAR *)pacTaskName, 
                    &ulTaskId,
                    ( VOS_TASK_ENTRY_TYPE )BST_OS_PalTaskEntry,
                    ulRealPriority,
                    ulStackSize,
                    aulTaskParam );

}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


