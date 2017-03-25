#ifndef _TSENSOR_BALONG_H_
#define _TSENSOR_BALONG_H_

#include <osl_types.h>
#include <drv_nv_def.h>
#include <bsp_om.h>
#include <bsp_icc.h>
#include <bsp_softtimer.h>
#include <bsp_shared_ddr.h>

typedef union
{
    struct                  /* efuse trim��ʽ,512~522 reference temp;523~533 soc temp */
    {   
        u32 data_base       :11;
        u32 data_tsen       :11;
        u32 reserved        :10;
    }bits;
    unsigned int u32;
}TSEN_EFUSE_INFO;

typedef struct tsensor_info
{
    struct softtimer_list softtimer;
    DRV_TSENSOR_TEMP_THRESHOLD temp_threshold;    /* �¶ȸ澯���ޣ����Ǹ��£�Ҳ�ǵ��� */     
    u32 reg_base_addr;
    
    u32 init_timestamp;                     /* ��ʼ��ʱ��� */
    u32 int_en_timestamp;                   /* �ж�ʹ��ʱ��� */

    u32 int_msp_callback_stamp;             /* �жϴ������̵��ù��Ӻ�����ʱ��� */
    u32 int_msp_callback_count;             /* �жϴ������̵��ù��Ӻ����Ĵ��� */
    
    u32 resume_msp_callback_stamp;          /* �������̵��ù��Ӻ�����ʱ��� */
    u32 resume_msp_callback_count;          /* �������̵��ù��Ӻ����Ĵ��� */

    u32 timer_msp_callback_stamp;           /* timer��ʱ���ù��Ӻ�����ʱ��� */
    u32 timer_msp_callback_count;           /* timer��ʱ���ù��Ӻ����Ĵ��� */
    
    s32 trim_tem;                           /* �¶�����ֵ */
    s32 inited;                             /* �����Ƿ��ʼ����ɡ�0 - δ��ʼ����1 - �ѳ�ʼ�� */    
}TSENSOR_INFO;

#define TSEN_CODE2TEMP(c)       ((c-116)*165/806-40)
#define TSEN_TEMP2CODE(T)       ((T+40)*806/165+116) 
#define TSENSOR_DEBUG(a,b)      ((a) = (b))

#define TSENSOR_SHM_BASE                ((u32)SHM_BASE_ADDR + SHM_OFFSET_TSENSOR_STAMP)
#define TSENSOR_ENABLE_STAMP            TSENSOR_SHM_BASE
#define TSENSOR_ICC_SEND_STAMP          (TSENSOR_SHM_BASE + 4)

#define CODE_DATA_MASK          0x3FF   /* bit0~9 is data */
#define CODE_SIGN_MASK          0x400   /* bit11 is signal */

#define DEFAULT_TEMP_HIGH_THRESHODE     15      /* ���¸澯���� */
#define DEFAULT_TEMP_LOW_THRESHODE      10      /* ���¸澯���� */

#define TIMER_TIME_OUT                  5       /* 5ms,����2.24*2�ĵ�һ������ */
#define DELAY_SLICE_NEED                147     /* 4480/30.5 = 147 ��ʼ�����ѯ�¶���Ҫ���4.48ms����147��slice */

#define TSENSOR_ICC_CHAN            (ICC_CHN_MCORE_CCORE << 16 | MCORE_CCORE_FUNC_TSENSOR)
#define CALIB_REG_MASK              0x3FF
#define LOCAL_SEN_ERR_SIGN_OFFSET   9

#define  tsensor_print_error(fmt, ...)   (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_TSENSOR, "[tsensor]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  tsensor_print_info(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_INFO, BSP_MODU_TSENSOR, "[tsensor]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))
#define  tsensor_print_always(fmt, ...)  (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_TSENSOR, fmt, ##__VA_ARGS__))

#define TSEN_OK 0
#define TSEN_ERR -1

/*lint -save -e762*/
s32 tsensor_init(void);
/*lint -restore*/

s32 tsensor_temp_get(s32 *temp);

#endif
