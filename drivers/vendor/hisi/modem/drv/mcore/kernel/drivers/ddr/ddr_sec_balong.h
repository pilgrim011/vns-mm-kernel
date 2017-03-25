


#ifndef __DDR_SEC_BALONG_H__
#define __DDR_SEC_BALONG_H__

#include <osl_common.h>


#ifndef NULL
#define NULL (void *)0
#endif

#ifndef ERROR
#define ERROR (-1)
#endif

#ifndef OK
#define OK (0)
#endif



#define DDRC_INTST                  (0xEC)                  /*�ж�״̬*/
#define SEC_RTL_INF(port)           (0x400+0x200*(port))   /*����������Ϣ              */
#define SEC_BYPASS(port)            (0x404+0x200*(port))   /*��ȫ����ʹ��              */
#define SEC_LOCKDOWN_SELECT(port)   (0x410+0x200*(port))   /*������ȫ����������üĴ���*/
#define SEC_INT_EN(port)            (0x420+0x200*(port))   /*�ж�ʹ��                  */
#define SEC_INT_STATUS(port)        (0x424+0x200*(port))   /*�ж�״̬                  */
#define SEC_INT_CLEAR(port)         (0x428+0x200*(port))   /*�ж���� д������ֵ �������ж�״̬�Ĵ���int_status */ 
#define SEC_FAIL_CMD_INF_0(port)    (0x480+0x200*(port))   /*��¼�׸�ԽȨ�������Ϣ0   */
#define SEC_FAIL_CMD_INF_1(port)    (0x484+0x200*(port))   /*��¼�׸�ԽȨ�������Ϣ1   reserved*/
#define SEC_FAIL_CMD_INF_2(port)    (0x488+0x200*(port))   /*��¼�׸�ԽȨ�������Ϣ2   */

#define SEC_FAIL_CMD_INF_2_ID       (0xFF000000)
#define SEC_FAIL_CMD_INF_2_MID      (  0xFFFFFF)
#define SEC_FAIL_CMD_INF_2_MID_SHIFT      (24)


struct ddr_sec_port_info{
    //u32 num;
    u32 cmd_id;
    u32 mid;
    u32 low_address;
};

#define NUM_OF_PORTS 2

struct ddr_security_info{
    u32 inited;
    void * base_addr;
    u32 irq_no;

    struct ddr_sec_port_info port_info[NUM_OF_PORTS];
};


#ifdef CONFIG_DDR_SECURITY
extern s32 ddr_sec_int_init(void);
#else
static inline s32 ddr_sec_int_init(void){return 0;}
#endif


#endif


