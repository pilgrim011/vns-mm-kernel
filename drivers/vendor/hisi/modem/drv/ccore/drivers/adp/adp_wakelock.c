/*************************************************************************
*   ��Ȩ����(C) 2008-2012, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  adp_wakelock.c
*
*   ��    �� :  xujingcui x00221564
*
*   ��    �� :  ˯��ͶƱģ�������ļ�
*
*   �޸ļ�¼ :
*
*************************************************************************/
#include "mdrv_pm.h"
#include "bsp_wakelock.h"

unsigned int mdrv_pm_wake_lock(PWC_CLIENT_ID_E id)
{
    struct wake_lock lock;
    lock.lockid = id;
    wake_lock(&lock);
    return 0;
}
unsigned int mdrv_pm_wake_unlock(PWC_CLIENT_ID_E id)
{
    struct wake_lock lock;
    lock.lockid = id;
    wake_unlock(&lock);
    return 0;
}

