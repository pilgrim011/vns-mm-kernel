#ifndef __MDRV_CCORE_NVIM_H__
#define __MDRV_CCORE_NVIM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_nvim_comm.h"

/*****************************************************************************
* �� �� ��  : mdrv_nv_flush
*
* ��������  : ���ڴ��е�nv����ˢ��flash �ļ�ϵͳ��
*
* �������  :
* �������  : ��
*
* �� �� ֵ  : OK
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_flush(void);

/*****************************************************************************
* �� �� ��  : mdrv_nv_restore_result
*
* ��������  :  �ָ�������
*
* �������  :
* �������  : ��
*
* �� �� ֵ  : OK
*
* �޸ļ�¼  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_restore_result(void);


#define NV_Backup()	                                (0)
#define NV_SpecialNvIdBackup(a,b,c)                 (0)
#define NV_RestoreManufactureExt()                  (1)
#define NV_BackupCheck()                            (0)
#define NVM_BackUpFNV()                             (0)
#define NVM_RevertFNV()                             (0)
#define NV_RestoreAll()                             (0)
#define NV_RestoreManufactureDefault()              (0)

#define NVM_Flush()                                 mdrv_nv_flush()
#define NV_Flush()	                                mdrv_nv_flush()
#define NV_QueryRestoreResult()                     mdrv_nv_restore_result()

#ifdef __cplusplus
}
#endif
#endif
