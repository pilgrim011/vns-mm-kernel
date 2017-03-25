/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_isp_subctrl_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-09-22 14:01:14
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��9��22��
    ��    ��   : s00249479
    �޸�����   : �ӡ�Hi6250V100 SOC�Ĵ����ֲ�_ISP_SUBCTRL.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ISP_SUBCTRL_INTERFACE_H__
#define __SOC_ISP_SUBCTRL_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) ISP SUB_CTRL
 ****************************************************************************/
/* �Ĵ���˵����SUBSYS config register
   λ����UNION�ṹ:  SOC_ISP_SUBCTRL_SUBSYS_CFG_UNION */
#define SOC_ISP_SUBCTRL_SUBSYS_CFG_ADDR(base)         ((base) + (0x0))

/* �Ĵ���˵����configure register
   λ����UNION�ṹ:  SOC_ISP_SUBCTRL_ISP_CORE_CFG_UNION */
#define SOC_ISP_SUBCTRL_ISP_CORE_CFG_ADDR(base)       ((base) + (0x4))

/* �Ĵ���˵����ERROR information register0
   λ����UNION�ṹ:  SOC_ISP_SUBCTRL_ISP_AXI_BUS_0_UNION */
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_0_ADDR(base)      ((base) + (0x8))

/* �Ĵ���˵����ERROR information register1
   λ����UNION�ṹ:  SOC_ISP_SUBCTRL_ISP_AXI_BUS_1_UNION */
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_1_ADDR(base)      ((base) + (0xC))

/* �Ĵ���˵����ERROR information register2
   λ����UNION�ṹ:  SOC_ISP_SUBCTRL_ISP_AXI_BUS_2_UNION */
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_2_ADDR(base)      ((base) + (0x10))

/* �Ĵ���˵����ERROR information register3
   λ����UNION�ṹ:  SOC_ISP_SUBCTRL_ISP_AXI_BUS_3_UNION */
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_3_ADDR(base)      ((base) + (0x14))

/* �Ĵ���˵����ERROR clear register
   λ����UNION�ṹ:  SOC_ISP_SUBCTRL_ISP_AXI_BUS_4_UNION */
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_4_ADDR(base)      ((base) + (0x18))

/* �Ĵ���˵����readonly register
   λ����UNION�ṹ:  SOC_ISP_SUBCTRL_ISP_AXI_BUS_5_UNION */
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_5_ADDR(base)      ((base) + (0x1C))

/* �Ĵ���˵����cfg register group0
   λ����UNION�ṹ:  SOC_ISP_SUBCTRL_ISP_core_ctrl_0_UNION */
#define SOC_ISP_SUBCTRL_ISP_core_ctrl_0_ADDR(base)    ((base) + (0x20))

/* �Ĵ���˵����cfg register group1
   λ����UNION�ṹ:  SOC_ISP_SUBCTRL_ISP_core_ctrl_1_UNION */
#define SOC_ISP_SUBCTRL_ISP_core_ctrl_1_ADDR(base)    ((base) + (0x24))

/* �Ĵ���˵����readonly register vic0
   λ����UNION�ṹ:  SOC_ISP_SUBCTRL_vic0_out0_UNION */
#define SOC_ISP_SUBCTRL_vic0_out0_ADDR(base)          ((base) + (0x28))

/* �Ĵ���˵����vic0 contgrol reg group0
   λ����UNION�ṹ:  SOC_ISP_SUBCTRL_vic0_in0_UNION */
#define SOC_ISP_SUBCTRL_vic0_in0_ADDR(base)           ((base) + (0x2C))

/* �Ĵ���˵����vic0 contgrol reg group1
   λ����UNION�ṹ:  SOC_ISP_SUBCTRL_vic0_in1_UNION */
#define SOC_ISP_SUBCTRL_vic0_in1_ADDR(base)           ((base) + (0x30))

/* �Ĵ���˵����readonly register vic1
   λ����UNION�ṹ:  SOC_ISP_SUBCTRL_vic1_out0_UNION */
#define SOC_ISP_SUBCTRL_vic1_out0_ADDR(base)          ((base) + (0x34))

/* �Ĵ���˵����vic1 contgrol reg group0
   λ����UNION�ṹ:  SOC_ISP_SUBCTRL_vic1_in0_UNION */
#define SOC_ISP_SUBCTRL_vic1_in0_ADDR(base)           ((base) + (0x38))

/* �Ĵ���˵����vic1 contgrol reg group1
   λ����UNION�ṹ:  SOC_ISP_SUBCTRL_vic1_in1_UNION */
#define SOC_ISP_SUBCTRL_vic1_in1_ADDR(base)           ((base) + (0x3C))





/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/



/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/



/*****************************************************************************
  6 STRUCT����
*****************************************************************************/



/*****************************************************************************
  7 UNION����
*****************************************************************************/

/****************************************************************************
                     (1/1) ISP SUB_CTRL
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ISP_SUBCTRL_SUBSYS_CFG_UNION
 �ṹ˵��  : SUBSYS_CFG �Ĵ����ṹ���塣��ַƫ����:0x0����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: SUBSYS config register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isp_wdt_apm_clken     : 1;  /* bit[0]    : isp subsys watchdog clock enable */
        unsigned int  isp_ipc_apm_clken     : 1;  /* bit[1]    : isp subsys IPC clock enable */
        unsigned int  isp_tim_apm_clken     : 1;  /* bit[2]    : isp subsys timer clock enable (apm clock) */
        unsigned int  sub_ctrl_reg0_7to3b   : 5;  /* bit[3-7]  : [3] isp subsys timer clock enable (sys clock)
                                                                 [7:4] reserved */
        unsigned int  sub_ctrl_reg0_15to8b  : 8;  /* bit[8-15] :  */
        unsigned int  sub_ctrl_reg0_23to16b : 8;  /* bit[16-23]:  */
        unsigned int  sub_ctrl_reg0_31to24b : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_SUBCTRL_SUBSYS_CFG_UNION;
#endif
#define SOC_ISP_SUBCTRL_SUBSYS_CFG_isp_wdt_apm_clken_START      (0)
#define SOC_ISP_SUBCTRL_SUBSYS_CFG_isp_wdt_apm_clken_END        (0)
#define SOC_ISP_SUBCTRL_SUBSYS_CFG_isp_ipc_apm_clken_START      (1)
#define SOC_ISP_SUBCTRL_SUBSYS_CFG_isp_ipc_apm_clken_END        (1)
#define SOC_ISP_SUBCTRL_SUBSYS_CFG_isp_tim_apm_clken_START      (2)
#define SOC_ISP_SUBCTRL_SUBSYS_CFG_isp_tim_apm_clken_END        (2)
#define SOC_ISP_SUBCTRL_SUBSYS_CFG_sub_ctrl_reg0_7to3b_START    (3)
#define SOC_ISP_SUBCTRL_SUBSYS_CFG_sub_ctrl_reg0_7to3b_END      (7)
#define SOC_ISP_SUBCTRL_SUBSYS_CFG_sub_ctrl_reg0_15to8b_START   (8)
#define SOC_ISP_SUBCTRL_SUBSYS_CFG_sub_ctrl_reg0_15to8b_END     (15)
#define SOC_ISP_SUBCTRL_SUBSYS_CFG_sub_ctrl_reg0_23to16b_START  (16)
#define SOC_ISP_SUBCTRL_SUBSYS_CFG_sub_ctrl_reg0_23to16b_END    (23)
#define SOC_ISP_SUBCTRL_SUBSYS_CFG_sub_ctrl_reg0_31to24b_START  (24)
#define SOC_ISP_SUBCTRL_SUBSYS_CFG_sub_ctrl_reg0_31to24b_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SUBCTRL_ISP_CORE_CFG_UNION
 �ṹ˵��  : ISP_CORE_CFG �Ĵ����ṹ���塣��ַƫ����:0x4����ֵ:0x000000FF�����:32
 �Ĵ���˵��: configure register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sub_ctrl_reg1_7to0b     : 8;  /* bit[0-7]  :  */
        unsigned int  sub_ctrl_reg1_15to8b    : 8;  /* bit[8-15] : [15:9] reserved;
                                                                   [8]: isp core soft reset, set 1 to reset core, then set 0 to clear reset state. */
        unsigned int  isp_dec_bus_err_irq_msk : 1;  /* bit[16]   : write 1 into this bit to mask the irq of isp decoding bus overtime error */
        unsigned int  sub_ctrl_reg1_23to17b   : 7;  /* bit[17-23]:  */
        unsigned int  sub_ctrl_reg1_31to24b   : 8;  /* bit[24-31]:  */
    } reg;
} SOC_ISP_SUBCTRL_ISP_CORE_CFG_UNION;
#endif
#define SOC_ISP_SUBCTRL_ISP_CORE_CFG_sub_ctrl_reg1_7to0b_START      (0)
#define SOC_ISP_SUBCTRL_ISP_CORE_CFG_sub_ctrl_reg1_7to0b_END        (7)
#define SOC_ISP_SUBCTRL_ISP_CORE_CFG_sub_ctrl_reg1_15to8b_START     (8)
#define SOC_ISP_SUBCTRL_ISP_CORE_CFG_sub_ctrl_reg1_15to8b_END       (15)
#define SOC_ISP_SUBCTRL_ISP_CORE_CFG_isp_dec_bus_err_irq_msk_START  (16)
#define SOC_ISP_SUBCTRL_ISP_CORE_CFG_isp_dec_bus_err_irq_msk_END    (16)
#define SOC_ISP_SUBCTRL_ISP_CORE_CFG_sub_ctrl_reg1_23to17b_START    (17)
#define SOC_ISP_SUBCTRL_ISP_CORE_CFG_sub_ctrl_reg1_23to17b_END      (23)
#define SOC_ISP_SUBCTRL_ISP_CORE_CFG_sub_ctrl_reg1_31to24b_START    (24)
#define SOC_ISP_SUBCTRL_ISP_CORE_CFG_sub_ctrl_reg1_31to24b_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SUBCTRL_ISP_AXI_BUS_0_UNION
 �ṹ˵��  : ISP_AXI_BUS_0 �Ĵ����ṹ���塣��ַƫ����:0x8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ERROR information register0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isp_axi_m1_waddr_err : 32; /* bit[0-31]: error isp_axi master1 write address[33:2] */
    } reg;
} SOC_ISP_SUBCTRL_ISP_AXI_BUS_0_UNION;
#endif
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_0_isp_axi_m1_waddr_err_START  (0)
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_0_isp_axi_m1_waddr_err_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SUBCTRL_ISP_AXI_BUS_1_UNION
 �ṹ˵��  : ISP_AXI_BUS_1 �Ĵ����ṹ���塣��ַƫ����:0xC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ERROR information register1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isp_axi_m1_raddr_err : 32; /* bit[0-31]: error isp_axi master1 read address[33:2] */
    } reg;
} SOC_ISP_SUBCTRL_ISP_AXI_BUS_1_UNION;
#endif
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_1_isp_axi_m1_raddr_err_START  (0)
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_1_isp_axi_m1_raddr_err_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SUBCTRL_ISP_AXI_BUS_2_UNION
 �ṹ˵��  : ISP_AXI_BUS_2 �Ĵ����ṹ���塣��ַƫ����:0x10����ֵ:0x00000000�����:32
 �Ĵ���˵��: ERROR information register2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isp_axi_m2_waddr_err : 32; /* bit[0-31]: error isp_axi master2 write address[33:2] */
    } reg;
} SOC_ISP_SUBCTRL_ISP_AXI_BUS_2_UNION;
#endif
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_2_isp_axi_m2_waddr_err_START  (0)
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_2_isp_axi_m2_waddr_err_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SUBCTRL_ISP_AXI_BUS_3_UNION
 �ṹ˵��  : ISP_AXI_BUS_3 �Ĵ����ṹ���塣��ַƫ����:0x14����ֵ:0x00000000�����:32
 �Ĵ���˵��: ERROR information register3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isp_axi_m2_raddr_err : 32; /* bit[0-31]: error isp_axi master2 read address[33:2] */
    } reg;
} SOC_ISP_SUBCTRL_ISP_AXI_BUS_3_UNION;
#endif
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_3_isp_axi_m2_raddr_err_START  (0)
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_3_isp_axi_m2_raddr_err_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SUBCTRL_ISP_AXI_BUS_4_UNION
 �ṹ˵��  : ISP_AXI_BUS_4 �Ĵ����ṹ���塣��ַƫ����:0x18����ֵ:0x00000000�����:32
 �Ĵ���˵��: ERROR clear register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  isp_axi_mst_err_srst_req_apm : 1;  /* bit[0]   : clear ISP_AXI_BUS master error information (apm clock domain) */
        unsigned int  isp_dec_bus_err_irq_clr      : 1;  /* bit[1]   : write 1 into this bit to clear the irq of isp decoding bus overtime error */
        unsigned int  isp_dec_bus_err_irq_force    : 1;  /* bit[2]   : write 1 into this bit to force the irq of isp decoding bus overtime error */
        unsigned int  reserved_0                   : 5;  /* bit[3-7] : reserved */
        unsigned int  reserved_1                   : 1;  /* bit[8]   : reserved */
        unsigned int  reserved_2                   : 23; /* bit[9-31]: reserved */
    } reg;
} SOC_ISP_SUBCTRL_ISP_AXI_BUS_4_UNION;
#endif
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_4_isp_axi_mst_err_srst_req_apm_START  (0)
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_4_isp_axi_mst_err_srst_req_apm_END    (0)
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_4_isp_dec_bus_err_irq_clr_START       (1)
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_4_isp_dec_bus_err_irq_clr_END         (1)
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_4_isp_dec_bus_err_irq_force_START     (2)
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_4_isp_dec_bus_err_irq_force_END       (2)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SUBCTRL_ISP_AXI_BUS_5_UNION
 �ṹ˵��  : ISP_AXI_BUS_5 �Ĵ����ṹ���塣��ַƫ����:0x1C����ֵ:0x00000000�����:32
 �Ĵ���˵��: readonly register
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sub_ctrl_ro_reg : 32; /* bit[0-31]: sub_ctrl_ro_reg[1:0]:isp_axi_m1_waddr_err[1:0];
                                                          sub_ctrl_ro_reg[3:2]:isp_axi_m1_raddr_err[1:0];
                                                          sub_ctrl_ro_reg[5:4]:isp_axi_m2_waddr_err[1:0];
                                                          sub_ctrl_ro_reg[7:6]:isp_axi_m2_raddr_err[1:0];
                                                          sub_ctrl_ro_reg[11:8]:isp_axi_mst_err[3:0]({m2_rd_err,m2_wr_err,m1_rd_err,m1_wr_err});
                                                          sub_ctrl_ro_reg[12]: isp_dec_bus_err_irq_clr/ the irq of isp decoding bus overtime error state
                                                          sub_ctrl_ro_reg[31:13]: reserved */
    } reg;
} SOC_ISP_SUBCTRL_ISP_AXI_BUS_5_UNION;
#endif
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_5_sub_ctrl_ro_reg_START  (0)
#define SOC_ISP_SUBCTRL_ISP_AXI_BUS_5_sub_ctrl_ro_reg_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SUBCTRL_ISP_core_ctrl_0_UNION
 �ṹ˵��  : ISP_core_ctrl_0 �Ĵ����ṹ���塣��ַƫ����:0x20����ֵ:0x00000000�����:32
 �Ĵ���˵��: cfg register group0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  subctrl_to_core_grp0 : 32; /* bit[0-31]: [1:0]: overf_prot used for isp bus module;
                                                                00:disable overtime protect function;
                                                                01:start overtime protection after 512cycles;
                                                                10:start overtime protection after 1024cycles;
                                                                11:start overtime protection after 2048cycles;
                                                               [2]: gatedclock_en used for isp bus module; //not used by bus module now;
                                                               [3]: dw_axi_gs_gatedclock_en used for gs dynamic clock control inisp bus module;//should be always set to be 1'b0;
                                                               [4]: dw_axi_rs_gatedclock_en used for clock enable for configuration cycles issued by isp bus module; 
                                                                1'b0: always high, will always enable the related clock;
                                                                1'b1: enable dynamci clock control;
                                                               [31:5]reserved */
    } reg;
} SOC_ISP_SUBCTRL_ISP_core_ctrl_0_UNION;
#endif
#define SOC_ISP_SUBCTRL_ISP_core_ctrl_0_subctrl_to_core_grp0_START  (0)
#define SOC_ISP_SUBCTRL_ISP_core_ctrl_0_subctrl_to_core_grp0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SUBCTRL_ISP_core_ctrl_1_UNION
 �ṹ˵��  : ISP_core_ctrl_1 �Ĵ����ṹ���塣��ַƫ����:0x24����ֵ:0x00000000�����:32
 �Ĵ���˵��: cfg register group1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  subctrl_to_core_grp1 : 32; /* bit[0-31]: reserved */
    } reg;
} SOC_ISP_SUBCTRL_ISP_core_ctrl_1_UNION;
#endif
#define SOC_ISP_SUBCTRL_ISP_core_ctrl_1_subctrl_to_core_grp1_START  (0)
#define SOC_ISP_SUBCTRL_ISP_core_ctrl_1_subctrl_to_core_grp1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SUBCTRL_vic0_out0_UNION
 �ṹ˵��  : vic0_out0 �Ĵ����ṹ���塣��ַƫ����:0x28����ֵ:0x00000000�����:32
 �Ĵ���˵��: readonly register vic0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vic0_out_irq_mask : 32; /* bit[0-31]:  */
    } reg;
} SOC_ISP_SUBCTRL_vic0_out0_UNION;
#endif
#define SOC_ISP_SUBCTRL_vic0_out0_vic0_out_irq_mask_START  (0)
#define SOC_ISP_SUBCTRL_vic0_out0_vic0_out_irq_mask_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SUBCTRL_vic0_in0_UNION
 �ṹ˵��  : vic0_in0 �Ĵ����ṹ���塣��ַƫ����:0x2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: vic0 contgrol reg group0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vic0_in_irq_level_mask : 32; /* bit[0-31]:  */
    } reg;
} SOC_ISP_SUBCTRL_vic0_in0_UNION;
#endif
#define SOC_ISP_SUBCTRL_vic0_in0_vic0_in_irq_level_mask_START  (0)
#define SOC_ISP_SUBCTRL_vic0_in0_vic0_in_irq_level_mask_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SUBCTRL_vic0_in1_UNION
 �ṹ˵��  : vic0_in1 �Ĵ����ṹ���塣��ַƫ����:0x30����ֵ:0x00000000�����:32
 �Ĵ���˵��: vic0 contgrol reg group1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vic0_in_irq_level_force : 32; /* bit[0-31]:  */
    } reg;
} SOC_ISP_SUBCTRL_vic0_in1_UNION;
#endif
#define SOC_ISP_SUBCTRL_vic0_in1_vic0_in_irq_level_force_START  (0)
#define SOC_ISP_SUBCTRL_vic0_in1_vic0_in_irq_level_force_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SUBCTRL_vic1_out0_UNION
 �ṹ˵��  : vic1_out0 �Ĵ����ṹ���塣��ַƫ����:0x34����ֵ:0x00000000�����:32
 �Ĵ���˵��: readonly register vic1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vic1_out_irq_mask : 32; /* bit[0-31]:  */
    } reg;
} SOC_ISP_SUBCTRL_vic1_out0_UNION;
#endif
#define SOC_ISP_SUBCTRL_vic1_out0_vic1_out_irq_mask_START  (0)
#define SOC_ISP_SUBCTRL_vic1_out0_vic1_out_irq_mask_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SUBCTRL_vic1_in0_UNION
 �ṹ˵��  : vic1_in0 �Ĵ����ṹ���塣��ַƫ����:0x38����ֵ:0x00000000�����:32
 �Ĵ���˵��: vic1 contgrol reg group0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vic1_in_irq_level_mask : 32; /* bit[0-31]:  */
    } reg;
} SOC_ISP_SUBCTRL_vic1_in0_UNION;
#endif
#define SOC_ISP_SUBCTRL_vic1_in0_vic1_in_irq_level_mask_START  (0)
#define SOC_ISP_SUBCTRL_vic1_in0_vic1_in_irq_level_mask_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ISP_SUBCTRL_vic1_in1_UNION
 �ṹ˵��  : vic1_in1 �Ĵ����ṹ���塣��ַƫ����:0x3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: vic1 contgrol reg group1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vic1_in_irq_level_force : 32; /* bit[0-31]:  */
    } reg;
} SOC_ISP_SUBCTRL_vic1_in1_UNION;
#endif
#define SOC_ISP_SUBCTRL_vic1_in1_vic1_in_irq_level_force_START  (0)
#define SOC_ISP_SUBCTRL_vic1_in1_vic1_in_irq_level_force_END    (31)






/*****************************************************************************
  8 OTHERS����
*****************************************************************************/



/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of soc_isp_subctrl_interface.h */
