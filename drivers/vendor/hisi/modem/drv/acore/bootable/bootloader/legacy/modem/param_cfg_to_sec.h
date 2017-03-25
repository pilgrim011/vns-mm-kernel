
#ifndef  __PARAM_TO_SEC_OS_H__
#define  __PARAM_TO_SEC_OS_H__

#ifdef __cplusplus
extern "C"
{
#endif

void set_param_cfg_to_sec(void);

#define BALONG_PARAM_BASE_ADDR        (0x365FF800)    /* 0x365FF800--0x365FF8FF */
#define PARAM_MAGIC_OFFSET            (0x0)           /* ħ��:�жϲ�����Ч�� */
#define PARAM_CFG_OFFSET              (0x8)           /* ���ò�����Ż���ַ*/

typedef struct tag_PARAM_CFG
{
    unsigned int   magic;                   /* ħ������ʶ���ò�����״̬ */
    unsigned int   protect_barrier_size;    /* Ԥ��(4K)��ֹ���ȣ���ʼ��ΪȫF */
    unsigned int   param_cfg_size;          /* ���ò���Ԥ��(16K)��С */
    unsigned int   icc_channel_base_addr;
    unsigned int   icc_channel_max_size;

}g_param_cfg;


#ifdef __cplusplus
}
#endif

#endif   /* __PARAM_TO_SEC_OS_H__ */

