/*************************************************************************
*   ��Ȩ����(C) 2008-2014, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  reset_balong.h
*
*   ��    �� :  y00184236
*
*   ��    �� :  modem������λ�ڲ�C��ͷ�ļ�
*
*   �޸ļ�¼ :  2014��02��15��  v1.00  y00184236  ����
*************************************************************************/

#ifndef __RESET_BALONG_H__
#define __RESET_BALONG_H__

#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif /* __cplusplus */

#include <osl_common.h>
#include <ipc_center.h>

#define reset_print_err(fmt, ...) (printk("[reset]: <%s> "fmt"\n", __FUNCTION__, ##__VA_ARGS__))
#define AP_TO_LPM3_IPC_FLAG       (OBJ_AP<<24|OBJ_MODEM<<16|CMD_SETTING<<8)

struct mcore_reset_ctrl
{
	u32 boot_mode;
	u32 multicore_msg_switch;
	u32 main_stage;
	u32 mdm_global_bus_err_cnt;
	u32 mdm_sub_bus_err_cnt;
	u32 mdm_ddr_access_err_cnt;
	u32 state;
};

#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */

#endif    /*  __RESET_BALONG_H__ */
