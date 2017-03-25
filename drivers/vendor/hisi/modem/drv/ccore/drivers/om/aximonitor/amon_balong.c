/*************************************************************************
*   ��Ȩ����(C) 2008-2012, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  amon_balong.c
*
*   ��    �� :  z00212940
*
*   ��    �� :  ��ά�ɲ�AXI Monitor
*
*   �޸ļ�¼ :  2013��1��29��  v1.00  z00212940  ����
*
*************************************************************************/

#ifdef __cplusplus
extern "C"
{
#endif
/*lint -save -e537*/
#include <securec.h>
#include "osl_irq.h"
#include <osl_thread.h>
#include <osl_malloc.h>
#include "bsp_memmap.h"
#include "bsp_socp.h"
#include "bsp_sysctrl.h"
#include "bsp_om_api.h"
#include "bsp_version.h"
#include "amon_balong.h"
#include "osl_malloc.h"
#include "of.h"
#include "bsp_om_api.h"
#include "securec.h"
#include <socp_balong.h>
#include "bsp_socp.h"

/*lint -restore*/
/******************************ȫ�ֱ�������***********************************/
/*lint -save -e40*/
u32 g_amon_base_addr[AXI_CTRL_ADDR_BUTT];
u32 g_amon_irq = 0;
struct amon_sysctrl_struct g_amon_sysctrl;

/**********************************�궨��***********************************/
/* ��ʼ�����궨�� */
/* AXI״̬��飬�Ƿ��������У�������ʱ�����������û��߻�ȡͳ������ */
#define AXI_CHECK_STATE(config) \
do{\
    if(MDRV_OK != axi_state_check(config))\
    {\
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: AXI %d is running\n", __FUNCTION__, config);\
        return MDRV_ERROR;\
    }\
}while(0)

/* MODE��飬ֻ֧��SOC��CPUFAST */


/*****************************************************************************
 �� �� ��  : axi_reg_read
 ��������  : AXI�Ĵ���������, һ��ֻ�ܶ�һ��Ĵ�����CPUFAST/SOC��
 �������  : axi_config_enum_uint32 config
             u32 reg
 �������  : u32 * value
 �� �� ֵ  : void
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_reg_read(axi_config_enum_uint32 config, u32 reg, u32 * value)
{
    /* ��������Ŀ���ȡ��Ӧ�Ĵ��� */
    switch(config)
    {
        /* ��ȡCPUFAST�Ĵ��� */
        case AXI_CPUFAST_CONFIG:
            *value = readl(AXI_MON_CPUFAST_BASE_ADDR + reg);
            break;

        /* ��ȡSOC�Ĵ��� */
        case AXI_SOC_CONFIG:
            *value = readl(AXI_MON_SOC_BASE_ADDR + reg);
            break;

        default:
            break;
    }
}

/*****************************************************************************
 �� �� ��  : axi_reg_write
 ��������  : AXI�Ĵ���д������һ��ֻ��дһ��Ĵ�����CPUFAST/SOC��
 �������  : axi_config_enum_uint32 config
             u32 reg
             u32 value
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_reg_write(axi_config_enum_uint32 config, u32 reg, u32 value)
{
    /* ��������Ŀ��д����Ӧ�Ĵ��� */
    switch(config)
    {
        /* дCPUFAST�Ĵ��� */
        case AXI_CPUFAST_CONFIG:
            writel(value, AXI_MON_CPUFAST_BASE_ADDR + reg);
            break;

        /* дSOC�Ĵ��� */
        case AXI_SOC_CONFIG:
            writel(value, AXI_MON_SOC_BASE_ADDR + reg);
            break;

        default:
            break;
    }
}

/*****************************************************************************
 �� �� ��  : axi_reg_getbits
 ��������  : AXI�Ĵ�����λ������һ��ֻ�ܶ�һ��Ĵ�����CPUFAST/SOC��
 �������  : axi_config_enum_uint32 config
             u32 reg
             u32 pos
             u32 bits
 �������  : u32 * value
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_reg_getbits(axi_config_enum_uint32 config, u32 reg, u32 pos, u32 bits, u32 * value)
{
    u32 reg_value = 0;

    /* ��������Ŀ���ȡ��Ӧ�Ĵ��� */
    axi_reg_read(config, reg, &reg_value);
    /* ���ݼĴ���ֵȡ��Ӧλ */
    *value = (reg_value >> pos) & (((u32)1 << (bits)) - 1);
}

/*****************************************************************************
 �� �� ��  : axi_reg_setbits
 ��������  : AXI�Ĵ���дλ������һ��ֻ��дһ��Ĵ�����CPUFAST/SOC��
 �������  : axi_config_enum_uint32 config
             u32 reg
             u32 pos
             u32 bits
             u32 value
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_reg_setbits(axi_config_enum_uint32 config, u32 reg, u32 pos, u32 bits, u32 value)
{
    u32 reg_value = 0;

    /* ��������Ŀ���ȡ��Ӧ�Ĵ��� */
    axi_reg_read(config, reg, &reg_value);
    /* ����д��Ĵ�����Ŀ��ֵ */
    reg_value = (reg_value & (~((((u32)1 << (bits)) - 1) << (pos)))) | ((u32)((value) & (((u32)1 << (bits)) - 1)) << (pos));
    /* д��Ŀ�ļĴ��� */
    axi_reg_write(config, reg, reg_value);
}
/*****************************************************************************
 �� �� ��  : axi_sc_mon_start
 ��������  : AXI Monitor����ͨ��ϵͳ����������
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_sc_mon_start(axi_config_enum_uint32 config)
{
    /* ����CPUFAST */
    if(AXI_CPUFAST_CONFIG == config)
    {
        amon_cpufast_start();
    }
    /* ����SOC */
    else if(AXI_SOC_CONFIG == config)
    {
        amon_soc_start();
    }
    else
    {
        return;
    }
}

/*****************************************************************************
 �� �� ��  : axi_sc_mon_stop
 ��������  : AXI Monitorֹͣͨ��ϵͳ����������
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_sc_mon_stop(axi_config_enum_uint32 config)
{
    /* ֹͣCPUFAST */
    if(AXI_CPUFAST_CONFIG == config)
    {
        amon_cpufast_stop();
    }
    /* ֹͣSOC */
    else if(AXI_SOC_CONFIG == config)
    {
        amon_soc_stop();
    }
    else
    {
        return;
    }
}

/*****************************************************************************
 �� �� ��  : axi_get_state
 ��������  : ��ȡAXI monitor����/��λ״̬������ͬʱ��ȡCPUFAST/SOC״̬
 �������  : axi_config_enum_uint32 config
             axi_get_state_req_enum_uint32 state_req
 �������  : ��
 �� �� ֵ  : axi_state_enum_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
axi_state_enum_uint32 axi_get_state(axi_config_enum_uint32 config, axi_get_state_req_enum_uint32 state_req)
{
    u32 reg_value = 0;

    /* ��״̬�Ĵ�����ȡ����״̬ */
    AXI_REG_READ(config, AXI_MON_CNT_STATE_INT, &reg_value);
    /* ��ȡ����״̬���� */
    if(AXI_GET_RUN_STATE_REQ == state_req)
    {
        reg_value = reg_value & AXI_RUN_STATE_MASK;
    }
    /* ��ȡ��λ״̬���� */
    else if(AXI_GET_RESET_STATE_REQ == state_req)
    {
        reg_value = reg_value & AXI_RESET_STATE_MASK;
    }
    /* ��Ч���� */
    else
    {
        return (axi_state_enum_uint32)AXI_STATE_BUTT;
    }

    return reg_value;
}

/*****************************************************************************
 �� �� ��  : axi_state_check
 ��������  : ״̬�ж��������Ƿ���������
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_state_check(axi_config_enum_uint32 config)
{
    axi_state_enum_uint32 axi_state;

    axi_state = axi_get_state(config, AXI_GET_RUN_STATE_REQ);
    /* AXI monitor�������� */
    if(axi_state != AXI_IDLE && axi_state != AXI_STOP)
    {
        return MDRV_ERROR;
    }

    return MDRV_OK;
}
/*****************************************************************************
 �� �� ��  : axi_reset
 ��������  : AXI monitor��λ
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_reset(axi_config_enum_uint32 config)
{
    axi_state_enum_uint32 axi_state;
    int i = 0;

    /* �������״̬ */
    AXI_CHECK_STATE(config);

    /* ��λ */
    AXI_REG_WRITE(config, AXI_MON_CNT_RESET, AXI_SOFT_RESET);
    /* ��λ�����ж���AXI monitor״̬�Ĵ���ָʾ��λ���� */
    do
    {
        axi_state = axi_get_state(config, AXI_GET_RESET_STATE_REQ);
        if(AXI_RESET_FINISH == axi_state)
        {
            return MDRV_OK;
        }
    }while(i++ < AXI_WAIT_CNT);

    /* ��λ��ʱ�쳣 */
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: time out\n", __FUNCTION__);
    return MDRV_ERROR;
}
s32 axi_get_irq_and_iomap(void)
{
	struct device_node *dev[AXI_CTRL_ADDR_BUTT] = {};
	const char *name[AXI_CTRL_ADDR_BUTT] = {"hisilicon,amon_fast1_balong", "hisilicon,amon_soc1_balong"};
#ifndef BSP_CONFIG_PHONE_TYPE
    char fast_reg_name[amon_cpufast_dts_butt][32] = {"amon_cpufast_srst_en","amon_cpufast_srst_dis", "amon_cpufast_monitor_start"};
#endif
    char soc_reg_name[amon_soc_dts_butt][32] = {"amon_soc_srst_en","amon_soc_srst_dis", "amon_soc_monitor_start"};
    u32 i = 0;
    u32 reg_addr[3] = {};
#ifdef BSP_CONFIG_PHONE_TYPE
    if(g_amon_base_addr[AXI_SOC_ADDR_ENUM] != 0)
    {
        return MDRV_OK;
    }

    dev[AXI_SOC_ADDR_ENUM] = of_find_compatible_node(NULL, NULL, name[AXI_SOC_ADDR_ENUM]);

    if(NULL == dev[AXI_SOC_ADDR_ENUM])
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: device node not found\n", __FUNCTION__);
        return MDRV_ERROR;
    }
    g_amon_base_addr[AXI_SOC_ADDR_ENUM] = (u32)of_iomap(dev[AXI_SOC_ADDR_ENUM], 0);

    if (0 == g_amon_base_addr[AXI_SOC_ADDR_ENUM])
    {
        amon_error("remap amon fail\n fast base addr = 0x%x soc base addr = 0x%x\n", g_amon_base_addr[AXI_FAST_ADDR_ENUM], g_amon_base_addr[AXI_SOC_ADDR_ENUM]);
        return MDRV_ERROR;
    }

    g_amon_irq = irq_of_parse_and_map(dev[AXI_SOC_ADDR_ENUM], 0);
    /*SOC���ϵͳ��������Ϣ��ʼ��*/
    for(i = 0; i < amon_soc_dts_butt; i++)
    {
        if(of_property_read_u32_array(dev[AXI_SOC_ADDR_ENUM], soc_reg_name[i], reg_addr, 3))
        {
            amon_error("Get amon dts fail, i = 0x%x\n", i);
            return MDRV_ERROR;
        }
        g_amon_sysctrl.amon_sysctrl_soc[i].base_addr = (u32)bsp_sysctrl_addr_get((void *)reg_addr[AMON_BASE_ADDR]);
        g_amon_sysctrl.amon_sysctrl_soc[i].start_bit = reg_addr[AMON_START_BIT];
        g_amon_sysctrl.amon_sysctrl_soc[i].end_bit = reg_addr[AMON_END_BIT];
    }
#else

    if((g_amon_base_addr[AXI_FAST_ADDR_ENUM] != 0)&&(g_amon_base_addr[AXI_SOC_ADDR_ENUM] != 0))
    {
        return MDRV_OK;
    }
    dev[AXI_FAST_ADDR_ENUM] = of_find_compatible_node(NULL, NULL, name[AXI_FAST_ADDR_ENUM]);
    dev[AXI_SOC_ADDR_ENUM] = of_find_compatible_node(NULL, NULL, name[AXI_SOC_ADDR_ENUM]);

    if((NULL == dev[AXI_FAST_ADDR_ENUM])||(NULL == dev[AXI_SOC_ADDR_ENUM]))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: device node not found\n", __FUNCTION__);
        return MDRV_ERROR;
    }
    g_amon_base_addr[AXI_FAST_ADDR_ENUM] = (u32)of_iomap(dev[AXI_FAST_ADDR_ENUM], 0);
    g_amon_base_addr[AXI_SOC_ADDR_ENUM] = (u32)of_iomap(dev[AXI_SOC_ADDR_ENUM], 0);

    if ((0 == g_amon_base_addr[AXI_FAST_ADDR_ENUM])||(0 == g_amon_base_addr[AXI_SOC_ADDR_ENUM]))
    {
        amon_error("remap amon fail\n fast base addr = 0x%x soc base addr = 0x%x\n", g_amon_base_addr[AXI_FAST_ADDR_ENUM], g_amon_base_addr[AXI_SOC_ADDR_ENUM]);
        return MDRV_ERROR;
    }

    g_amon_irq = irq_of_parse_and_map(dev[AXI_FAST_ADDR_ENUM], 0);
    /*SOC���ϵͳ��������Ϣ��ʼ��*/
    for(i = 0; i < amon_soc_dts_butt; i++)
    {
        if(of_property_read_u32_array(dev[AXI_SOC_ADDR_ENUM], soc_reg_name[i], reg_addr, 3))
        {
            amon_error("soc of_property_read_u32_array error\n");
            return MDRV_ERROR;
        }
        /* coverity[uninit_use_in_call] */
        g_amon_sysctrl.amon_sysctrl_soc[i].base_addr = (u32)bsp_sysctrl_addr_get((void *)reg_addr[AMON_BASE_ADDR]);
        g_amon_sysctrl.amon_sysctrl_soc[i].start_bit = reg_addr[AMON_START_BIT];
        g_amon_sysctrl.amon_sysctrl_soc[i].end_bit = reg_addr[AMON_END_BIT];
    }
    /*cpu fast���ϵͳ��������Ϣ��ʼ��*/
    for(i = 0; i < amon_cpufast_dts_butt; i++)
    {
        if(of_property_read_u32_array(dev[AXI_FAST_ADDR_ENUM], fast_reg_name[i], reg_addr, 3))
        {
            amon_error("fast of_property_read_u32_array error\n");
            return MDRV_ERROR;
        }
        /* coverity[uninit_use_in_call] */
        g_amon_sysctrl.amon_sysctrl_fast[i].base_addr = (u32)bsp_sysctrl_addr_get((void *)reg_addr[AMON_BASE_ADDR]);
        g_amon_sysctrl.amon_sysctrl_fast[i].start_bit = reg_addr[AMON_START_BIT];
        g_amon_sysctrl.amon_sysctrl_fast[i].end_bit = reg_addr[AMON_END_BIT];
    }
#endif
    return MDRV_OK;
}

/*lint -restore +e40*/
/*****************************************************************************
 �� �� ��  : axi_capt_config
 ��������  : ���ɹ��ܲ���
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
*****************************************************************************/
void axi_capt_config(axi_config_enum_uint32 axi_mode,  u32 port,u32 capt_id)
{
    u32 value = 0;

    /*����*/
    if(axi_mode == AXI_SOC_CONFIG)
    {
        amon_soc_clk_enable();
    }
    else if(axi_mode == AXI_CPUFAST_CONFIG)
    {
		amon_cpufast_clk_enable();
    }

    axi_reg_write(axi_mode, AXI_MON_CNT_RESET, 0x4);

    do{
        axi_reg_read(axi_mode, AXI_MON_CNT_RESET, &value);
    }while((value&0x4) == 0x4);

    amon_sc_reset(axi_mode);

    /*�ɼ�port ��������*/
    axi_reg_write(axi_mode, AXI_CAPT_TRAN_CONFIG, port);
    /*ʹ�ܶ�id1�������ݲɼ� */
    axi_reg_write(axi_mode, AXI_CAPT_ID_EN, 0x1);
    /*���ݲɼ�id������*/
    axi_reg_write(axi_mode, AXI_CAPT_ID(0), capt_id);
    /*�����ж�*/
    axi_reg_write(axi_mode, AXI_CAPT_INT_MASK, 0xFF);
    /*���ж�*/
    axi_reg_write(axi_mode, AXI_CAPT_INT_CLR, 0xFF);
}
/*****************************************************************************
 �� �� ��  : axi_capt_start
 ��������  : �������ɹ��ܲ���
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
*****************************************************************************/
void axi_capt_start(axi_config_enum_uint32 axi_mode)
{

    axi_reg_write(axi_mode, AXI_CAPT_INT_CLR, 0xFFFF);

    axi_reg_write(axi_mode, AXI_CAPT_CTRL, 0x1);
}
/*****************************************************************************
 �� �� ��  : axi_capt_stop
 ��������  : ֹͣ���ɹ��ܲ���
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
*****************************************************************************/
void axi_capt_stop(axi_config_enum_uint32 axi_mode)
{
    axi_reg_write(axi_mode, AXI_CAPT_CTRL, 0x2);
}


#if 0
extern SOCP_GBL_STATE g_strSocpStat;
void * g_dstBuf = NULL;
void * g_srcBuf = NULL;

void axi_capt_socp_config(void)
{
    u32 socpbase = g_strSocpStat.baseAddr;

    if(!g_dstBuf)
    {
        g_dstBuf = osl_malloc(0x400);
        if(!g_dstBuf)
        {
            amon_error("malloc error \n");
            return;
        }
        else
        {
            amon_error("dst buf addr = 0x%x\n", (u32)g_dstBuf);
        }
    }


    if(!g_srcBuf)
    {
        g_srcBuf = osl_malloc(0x100);
        if(!g_srcBuf)
        {
            amon_error("malloc error \n");
            return;
        }
        else
        {
            amon_error("src buf addr = 0x%x\n", (u32)g_srcBuf);
        }
    }

    /*dst*/
    writel((u32)g_dstBuf, socpbase + 0x900 + 0x20 * 2);
    writel((u32)g_dstBuf, socpbase + 0x904 + 0x20 * 2);
    writel((u32)g_dstBuf, socpbase + 0x908 + 0x20 * 2);
    writel((u32)0x400,  socpbase + 0x90C + 0x20 * 2);

    /*src*/
    writel((u32)g_srcBuf, socpbase + 0x100 + 0x40 * 11);
    writel((u32)g_srcBuf, socpbase + 0x104 + 0x40 * 11);
    writel((u32)g_srcBuf, socpbase + 0x108 + 0x40 * 11);
    writel((u32)0x100,  socpbase + 0x10C + 0x40 * 11);


}

void axi_capt_socp_start(u32 times)
{
    u32 socpbase = g_strSocpStat.baseAddr;
    u32 i = 0;

    /*start*/
    writel((u32)0x21,  socpbase + 0x110 + 0x40 * 11);

    for(i = 0; i < times; i++)
    {
        writel((u32)g_dstBuf, socpbase + 0x900 + 0x20 * 2);
        writel((u32)g_dstBuf, socpbase + 0x904 + 0x20 * 2);

        writel(0x48495349, (u32)g_srcBuf);/*hisi*/
        writel(0xF8, (u32)g_srcBuf + 0x4);/*len*/

        writel((u32)g_srcBuf + 0x100, socpbase + 0x100 + 0x40 * 11);
        writel((u32)g_srcBuf,  socpbase + 0x104 + 0x40 * 11);
    }

    /*stop*/
    writel((u32)0x20,  socpbase + 0x110 + 0x40 * 11);

    return;
}

u32 g_axi_capt_edma = 0x80204000;
void axi_capt_edma_config(u32 times)
{

    /*v722  0x80204000*/
    u32 edma_base = g_axi_capt_edma;
    /*Chicago*/
    /*u32 edma_base = 0xE0204000;*/
    u32 i = 0;

    for(i = 0; i < times; i++)
    {
        writel(0x100, edma_base + 0x810);
        writel((u32)SHM_OFFSET_MEMMGR, edma_base + 0x814);
        writel((u32)SHM_OFFSET_MEMMGR + 0x100, edma_base + 0x818);
        writel(0xC0000001, edma_base + 0x81C);
    }

    return;
}
#endif
#ifdef __cplusplus
}
#endif

