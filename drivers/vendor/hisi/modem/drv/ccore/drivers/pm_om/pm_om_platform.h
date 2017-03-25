/*************************************************************************
*   ��Ȩ����(C) 2008-2015, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  pm_om_platform.H
*
*   ��    �� :  y00184236
*
*   ��    �� :  ƽ̨���ͷ�ļ�
*
*   �޸ļ�¼ :  2014��11��17��  v1.00  y00184236  ����
*************************************************************************/

#ifndef __PM_OM_PLATFORM_H__
#define __PM_OM_PLATFORM_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include <string.h>
#include <bsp_dump.h>
#include <bsp_icc.h>

#define PM_OM_DUMP_ID           DUMP_CP_PM_OM
#define PM_OM_DUMP_SIZE         (0x10000)
#define PM_OM_ICC_CHN_ID        (ICC_CHANNEL_ID_MAKEUP(ICC_CHN_IFC, IFC_RECV_FUNC_PM_OM))
#define PM_OM_CPUID             (IPC_CORE_CCORE)
#define PM_OM_WAKEUP_INTERVAL   (3000)

struct pm_om_platform
{
	u32 icc_chn_id;
	struct log_usr_info  log_info;
	struct pm_om_ctrl *ctrl;
};

int pm_om_fwrite_trigger(void);
int pm_om_platform_init(void);

#ifdef __cplusplus
}
#endif

#endif  /* __PM_OM_PLATFORM_H__ */
