/*************************************************************************
*   ��Ȩ����(C) 2008-2015, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  adp_pm_om.c
*
*   ��    �� :  y00184236
*
*   ��    �� :  pm_om���ϲ������ļ�
*
*   �޸ļ�¼ : 2014��11��17��  v1.00  y00184236  ����
*************************************************************************/
#include <bsp_om.h>
#include <bsp_pm_om.h>

int bsp_pm_log(u32 magic, u32 data_len , void *data)
{
	return -1;
}

int bsp_pm_log_type(u32 magic, u32 type, u32 data_len , void *data)
{
	return -1;
}

void* bsp_pm_log_addr_get(void)
{
	return NULL;
}

void* bsp_pm_dump_get(u32 magic, u32 len)
{
	return NULL;
}

int bsp_pm_om_dump_init(void)
{
	pmom_pr_err("is stub\n");
	return 0;
}

int bsp_pm_om_log_init(void)
{
	pmom_pr_err("is stub\n");
	return 0;
}