/*************************************************************************
*   ��Ȩ����(C) 2008-2015, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  pm_om_debug.h
*
*   ��    �� :  y00184236
*
*   ��    �� :  debug���ͷ�ļ�
*
*   �޸ļ�¼ :  2014��11��17��  v1.00  y00184236  ����
*************************************************************************/
#ifndef __PM_OM_DEBUG_H__
#define __PM_OM_DEBUG_H__

#ifdef __cplusplus
extern "C"
{
#endif

/*lint --e{528}*/
static inline int pm_om_debug_init(void){return 0;}
static inline u32 pm_om_log_time_rec(u32 time_log_start){return 0;}
static inline void pm_om_log_time_print(u32 log_sw){}

#ifdef __cplusplus
}
#endif

#endif  /* __PM_OM_DEBUG_H__ */
