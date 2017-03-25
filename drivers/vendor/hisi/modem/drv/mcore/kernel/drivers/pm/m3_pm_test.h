
#ifndef __M3_PM_TEST_H__
#define __M3_PM_TEST_H__


#include <soc_memmap.h>

/* c->m send ipc_int  addr & bit  */
#define  PM_C2M_IPC_ADDR       (HI_IPCM_REGBASE_ADDR+IPC_CPU_RAW_INT_M3)
#define  PM_C2M_IPC_BIT        (0x1<<IPC_MCU_INT_SRC_CCPU_PD)
/* a->m send ipc_int  addr & bit  */
#define  PM_A2M_IPC_ADDR       (HI_IPCM_REGBASE_ADDR+IPC_CPU_RAW_INT_M3)
#define  PM_A2M_IPC_BIT        (0x1<<IPC_MCU_INT_SRC_ACPU_PD)


/* === ����˯״̬���Ļ���ʱ������������ ===
** ˯��ʱ���趨����timer��Ȼ����loop
** loopֵ��Сʱ loopʱ��̣�״̬���ܽ���˯
** loopֵ�ϴ�ʱ loopʱ�䳤��״̬��û���㹻��ʱ�����˯
** ͨ������ loopֵ����֤��״̬���Ļ���ʱ������������
**
** �ڲ�����ʹ�ã�loop����Ĭ�Ϲر�
** min,maxֵ��ͬƽ̨�в��죬�����������ֶ�����:ʹ�ܡ�����min maxֵ
*/
struct pm_test_state_machine
{
    u32 enable;     /* �����Ƿ�ʹ�� */
    u32 loop_min;   /* loopֵ��Сֵ */
    u32 loop_max;   /* loopֵ��Сֵ */
    u32 loop_temp;  /* ��ǰloopֵ����ʼ��Ϊloop_min */
    u32 first_no_sm;/* ��¼��һ��״̬��������˯��loopֵ */
    u32 tmp_no_sm;  /* loopֵΪmaxʱ�����㡣֮���¼��һ��״̬��������˯��loopֵ */
};



#ifdef CONFIG_M3PM_TEST
extern u32 debug_can_sleep(void);
extern void pm_test_add_timer(void);
extern void pm_test_loop(void);
extern void pm_test_add_timer_and_loop(void);
extern void pm_test_no_sm_record(void);

#else
static inline u32 debug_can_sleep(void){return 1;}
static inline void pm_test_add_timer(void){return;}
static inline void pm_test_loop(void){return;}
static inline void pm_test_no_sm_record(void){return;}

#endif


#endif


        
