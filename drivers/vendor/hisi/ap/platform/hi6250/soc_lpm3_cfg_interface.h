/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_lpm3_cfg_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-07-15 16:01:13
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��7��15��
    ��    ��   : s00249479
    �޸�����   : �ӡ�Hi6250V100 SOC�Ĵ����ֲ�_LPM3_CFG.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_LPM3_CFG_INTERFACE_H__
#define __SOC_LPM3_CFG_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) register_define
 ****************************************************************************/
/* �Ĵ���˵����M3����DDR�Ļ����������üĴ�����
   λ����UNION�ṹ:  SOC_LPM3_CFG_ACCESS_WIN_UNION */
#define SOC_LPM3_CFG_ACCESS_WIN_ADDR(base)            ((base) + (0x000))

/* �Ĵ���˵����M3 halt״̬bypass���ƼĴ�����
   λ����UNION�ṹ:  SOC_LPM3_CFG_HALT_BYPASS_UNION */
#define SOC_LPM3_CFG_HALT_BYPASS_ADDR(base)           ((base) + (0x004))

/* �Ĵ���˵����Lp_ram multi-cycle���ƼĴ�����
   λ����UNION�ṹ:  SOC_LPM3_CFG_LPRAM_MULTI_CTRL_UNION */
#define SOC_LPM3_CFG_LPRAM_MULTI_CTRL_ADDR(base)      ((base) + (0x008))

/* �Ĵ���˵�����������߼�bypass���ƼĴ�����
   λ����UNION�ṹ:  SOC_LPM3_CFG_DLOCK_BYPASS_UNION */
#define SOC_LPM3_CFG_DLOCK_BYPASS_ADDR(base)          ((base) + (0x00C))

/* �Ĵ���˵����Timer��Wdog����ʱ��ʹ��bypass���ƼĴ�����
   λ����UNION�ṹ:  SOC_LPM3_CFG_TIMCLKEN_BYPASS_UNION */
#define SOC_LPM3_CFG_TIMCLKEN_BYPASS_ADDR(base)       ((base) + (0x010))

/* �Ĵ���˵����test pin��ʹ������Ĵ�����
   λ����UNION�ṹ:  SOC_LPM3_CFG_TESTPIN_EN_UNION */
#define SOC_LPM3_CFG_TESTPIN_EN_ADDR(base)            ((base) + (0x014))

/* �Ĵ���˵����Harq memory����0�Ĵ�����
   λ����UNION�ṹ:  SOC_LPM3_CFG_HARQMEM_CTRL0_UNION */
#define SOC_LPM3_CFG_HARQMEM_CTRL0_ADDR(base)         ((base) + (0x020))

/* �Ĵ���˵����Harq memory����1�Ĵ�����
   λ����UNION�ṹ:  SOC_LPM3_CFG_HARQMEM_CTRL1_UNION */
#define SOC_LPM3_CFG_HARQMEM_CTRL1_ADDR(base)         ((base) + (0x024))

/* �Ĵ���˵����NMI���жϼĴ�����
   λ����UNION�ṹ:  SOC_LPM3_CFG_NMI_SOFT_UNION */
#define SOC_LPM3_CFG_NMI_SOFT_ADDR(base)              ((base) + (0x028))

/* �Ĵ���˵����Harq memory����2�Ĵ�����
   λ����UNION�ṹ:  SOC_LPM3_CFG_HARQMEM_CTRL2_UNION */
#define SOC_LPM3_CFG_HARQMEM_CTRL2_ADDR(base)         ((base) + (0x030))

/* �Ĵ���˵����Harq memory����3�Ĵ�����
   λ����UNION�ṹ:  SOC_LPM3_CFG_HARQMEM_CTRL3_UNION */
#define SOC_LPM3_CFG_HARQMEM_CTRL3_ADDR(base)         ((base) + (0x034))

/* �Ĵ���˵�������������Ĵ�����
   λ����UNION�ṹ:  SOC_LPM3_CFG_LOCK_UNION */
#define SOC_LPM3_CFG_LOCK_ADDR(base)                  ((base) + (0x0A0))





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
                     (1/1) register_define
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_LPM3_CFG_ACCESS_WIN_UNION
 �ṹ˵��  : ACCESS_WIN �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: M3����DDR�Ļ����������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved      : 28; /* bit[0-27] : Reserved */
        unsigned int  access_window : 4;  /* bit[28-31]: M3��256MB DDR�ռ����ʱ�����ӵĻ������ʴ��ڡ�ȡֵ��ΧΪ0x0~0xD */
    } reg;
} SOC_LPM3_CFG_ACCESS_WIN_UNION;
#endif
#define SOC_LPM3_CFG_ACCESS_WIN_access_window_START  (28)
#define SOC_LPM3_CFG_ACCESS_WIN_access_window_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LPM3_CFG_HALT_BYPASS_UNION
 �ṹ˵��  : HALT_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000001�����:32
 �Ĵ���˵��: M3 halt״̬bypass���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  halt_bypass : 1;  /* bit[0]   : �Ƿ�bypass��M3debug״̬���ڲ�timer��watchdog�ļ���Ӱ��
                                                      0��halt״̬��Ӱ���������debug״̬��ֹͣ����
                                                      1��bypass halt״̬����debug״̬�²�ֹͣ���� */
        unsigned int  reserved    : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_HALT_BYPASS_UNION;
#endif
#define SOC_LPM3_CFG_HALT_BYPASS_halt_bypass_START  (0)
#define SOC_LPM3_CFG_HALT_BYPASS_halt_bypass_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_LPM3_CFG_LPRAM_MULTI_CTRL_UNION
 �ṹ˵��  : LPRAM_MULTI_CTRL �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: Lp_ram multi-cycle���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lpram_multi_ctrl : 1;  /* bit[0]   : AO��LP_RAM multi-cycle���ƼĴ���
                                                           0������ramʱ�򣬶�����2 cycle����
                                                           1��ram���ʽӿڵ�fready��ѹһ�ģ�������3 cycle���� */
        unsigned int  reserved         : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_LPRAM_MULTI_CTRL_UNION;
#endif
#define SOC_LPM3_CFG_LPRAM_MULTI_CTRL_lpram_multi_ctrl_START  (0)
#define SOC_LPM3_CFG_LPRAM_MULTI_CTRL_lpram_multi_ctrl_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_LPM3_CFG_DLOCK_BYPASS_UNION
 �ṹ˵��  : DLOCK_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �������߼�bypass���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bypass_for_ssi1  : 1;  /* bit[0]    : pmussi1���ýӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_ddrc  : 1;  /* bit[1]    : ddrc���ýӿڷ������߼���·���ƣ���Чʱ����·�߼������ǿ������Ϊ1��bypass����Ĭ��Ϊ0��������·�� */
        unsigned int  bypass_for_tsen  : 1;  /* bit[2]    : tsensorc���ýӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_pmc   : 1;  /* bit[3]    : pmc���ýӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_uart  : 1;  /* bit[4]    : uart���ýӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_i2c   : 1;  /* bit[5]    : pmui2c���ýӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_ssi0  : 1;  /* bit[6]    : pmussi0���ýӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_pcrg  : 1;  /* bit[7]    : peri CRG���ýӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_wdog  : 1;  /* bit[8]    : Watchdog���ýӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_timer : 1;  /* bit[9]    : Timer���ýӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  reserved_0       : 1;  /* bit[10]   : Unused */
        unsigned int  bypass_for_cssys : 1;  /* bit[11]   : Cssys���ýӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_pwm   : 1;  /* bit[12]   : PWM���ʽӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_rom   : 1;  /* bit[13]   : ROM���ʽӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_ram   : 1;  /* bit[14]   : RAM���ʽӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  bypass_for_nandc : 1;  /* bit[15]   : Nandc���ʽӿڷ������߼���·���ƣ�Ĭ��Ϊ0 */
        unsigned int  reserved_1       : 16; /* bit[16-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_DLOCK_BYPASS_UNION;
#endif
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ssi1_START   (0)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ssi1_END     (0)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ddrc_START   (1)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ddrc_END     (1)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_tsen_START   (2)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_tsen_END     (2)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pmc_START    (3)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pmc_END      (3)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_uart_START   (4)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_uart_END     (4)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_i2c_START    (5)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_i2c_END      (5)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ssi0_START   (6)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ssi0_END     (6)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pcrg_START   (7)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pcrg_END     (7)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_wdog_START   (8)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_wdog_END     (8)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_timer_START  (9)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_timer_END    (9)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_cssys_START  (11)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_cssys_END    (11)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pwm_START    (12)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_pwm_END      (12)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_rom_START    (13)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_rom_END      (13)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ram_START    (14)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_ram_END      (14)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_nandc_START  (15)
#define SOC_LPM3_CFG_DLOCK_BYPASS_bypass_for_nandc_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_LPM3_CFG_TIMCLKEN_BYPASS_UNION
 �ṹ˵��  : TIMCLKEN_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000000�����:32
 �Ĵ���˵��: Timer��Wdog����ʱ��ʹ��bypass���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  timclken_bypass : 1;  /* bit[0]   : bypass M3��ϵͳ�ڲ�Timer��Wdog�ļ���ʱ��ʹ�ܣ�Ĭ��ֵΪ0����λ��Чʱ������ʱ��ʹ�ܽ���ǿ������Ϊ1���Ա�֤M3������32KHzʱ��ʱ��Timer��Wdog�Կ����������� */
        unsigned int  reserved        : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_TIMCLKEN_BYPASS_UNION;
#endif
#define SOC_LPM3_CFG_TIMCLKEN_BYPASS_timclken_bypass_START  (0)
#define SOC_LPM3_CFG_TIMCLKEN_BYPASS_timclken_bypass_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_LPM3_CFG_TESTPIN_EN_UNION
 �ṹ˵��  : TESTPIN_EN �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000000�����:32
 �Ĵ���˵��: test pin��ʹ������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  testpin_en : 1;  /* bit[0]   : tp_m3lp_hclk test pin�����ʹ�ܿ���λ��
                                                     0��test pin�����Ϊ0
                                                     1��test pin�����Ϊtp_m3lp_hclk */
        unsigned int  reserved   : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_TESTPIN_EN_UNION;
#endif
#define SOC_LPM3_CFG_TESTPIN_EN_testpin_en_START  (0)
#define SOC_LPM3_CFG_TESTPIN_EN_testpin_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_LPM3_CFG_HARQMEM_CTRL0_UNION
 �ṹ˵��  : HARQMEM_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00000000�����:32
 �Ĵ���˵��: Harq memory����0�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  soc_ap_dslp_grp0 : 1;  /* bit[0]    : group0 RAM �͹��Ŀ��ƣ�DSLP�ӿڣ�
                                                            bit[0] RAM DSLP�ӿڣ�
                                                            1:��ʾdeep sleep low powerģʽ��
                                                            0:��ʾ����ģʽ�� */
        unsigned int  soc_ap_dslp_grp1 : 3;  /* bit[1-3]  : group1 RAM �͹��Ŀ��ƣ�DSLP�ӿڣ�
                                                            bit[2:0] RAM2~RAM0 DSLP�ӿڣ�
                                                            1:��ʾdeep sleep low powerģʽ��
                                                            0:��ʾ����ģʽ�� */
        unsigned int  soc_ap_dslp_grp2 : 4;  /* bit[4-7]  : group2 RAM �͹��Ŀ��ƣ�DSLP�ӿڣ�
                                                            bit[3:0] RAM3~RAM0 DSLP�ӿڣ�
                                                            1:��ʾdeep sleep low powerģʽ��
                                                            0:��ʾ����ģʽ�� */
        unsigned int  soc_ap_dslp_grp3 : 5;  /* bit[8-12] : group3 RAM �͹��Ŀ��ƣ�DSLP�ӿڣ�
                                                            bit[4:0] RAM4~RAM0 DSLP�ӿڣ�
                                                            1:��ʾdeep sleep low powerģʽ��
                                                            0:��ʾ����ģʽ�� */
        unsigned int  reserved_0       : 3;  /* bit[13-15]: Reserved */
        unsigned int  soc_ap_sd_grp0   : 1;  /* bit[16]   : group0 RAM �͹��Ŀ��ƣ�DSLP�ӿڣ�
                                                            bit RAM DSLP�ӿڣ�
                                                            1:��ʾshut downģʽ��
                                                            0:��ʾ����ģʽ�� */
        unsigned int  soc_ap_sd_grp1   : 3;  /* bit[17-19]: group1 RAM �͹��Ŀ��ƣ�DSLP�ӿڣ�
                                                            bit[2:0] RAM2~RAM0 DSLP�ӿڣ�
                                                            1:��ʾshut downģʽ��
                                                            0:��ʾ����ģʽ�� */
        unsigned int  soc_ap_sd_grp2   : 4;  /* bit[20-23]: group2 RAM �͹��Ŀ��ƣ�DSLP�ӿڣ�
                                                            bit[3:0] RAM3~RAM0 DSLP�ӿڣ�
                                                            1:��ʾshut downģʽ��
                                                            0:��ʾ����ģʽ�� */
        unsigned int  soc_ap_sd_grp3   : 5;  /* bit[24-28]: group3 RAM �͹��Ŀ��ƣ�DSLP�ӿڣ�
                                                            bit[4:0] RAM4~RAM0 DSLP�ӿڣ�
                                                            1:��ʾshut downģʽ��
                                                            0:��ʾ����ģʽ�� */
        unsigned int  reserved_1       : 3;  /* bit[29-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_HARQMEM_CTRL0_UNION;
#endif
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_dslp_grp0_START  (0)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_dslp_grp0_END    (0)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_dslp_grp1_START  (1)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_dslp_grp1_END    (3)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_dslp_grp2_START  (4)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_dslp_grp2_END    (7)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_dslp_grp3_START  (8)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_dslp_grp3_END    (12)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_sd_grp0_START    (16)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_sd_grp0_END      (16)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_sd_grp1_START    (17)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_sd_grp1_END      (19)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_sd_grp2_START    (20)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_sd_grp2_END      (23)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_sd_grp3_START    (24)
#define SOC_LPM3_CFG_HARQMEM_CTRL0_soc_ap_sd_grp3_END      (28)


/*****************************************************************************
 �ṹ��    : SOC_LPM3_CFG_HARQMEM_CTRL1_UNION
 �ṹ˵��  : HARQMEM_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00000000�����:32
 �Ĵ���˵��: Harq memory����1�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  soc_ap_dslp_grp4 : 4;  /* bit[0-3]  : group4 RAM �͹��Ŀ��ƣ�DSLP�ӿڣ�
                                                            bit[3:0] RAM3~RAM0 DSLP�ӿڣ�
                                                            1:��ʾdeep sleep low powerģʽ��
                                                            0:��ʾ����ģʽ�� */
        unsigned int  soc_ap_dslp_grp5 : 6;  /* bit[4-9]  : group5 RAM �͹��Ŀ��ƣ�DSLP�ӿڣ�
                                                            bit[5:0] RAM5~RAM0 DSLP�ӿڣ�
                                                            1:��ʾdeep sleep low powerģʽ��
                                                            0:��ʾ����ģʽ�� */
        unsigned int  soc_ap_dslp_grp6 : 11; /* bit[10-20]: group6 RAM �͹��Ŀ��ƣ�DSLP�ӿڣ�
                                                            bit[10:0] RAM10~RAM0 DSLP�ӿڣ�
                                                            1:��ʾdeep sleep low powerģʽ��
                                                            0:��ʾ����ģʽ�� */
        unsigned int  soc_ap_dslp_grp7 : 11; /* bit[21-31]: group7 RAM �͹��Ŀ��ƣ�DSLP�ӿڣ�
                                                            bit[10:0] RAM10~RAM0 DSLP�ӿڣ�
                                                            1:��ʾdeep sleep low powerģʽ��
                                                            0:��ʾ����ģʽ�� */
    } reg;
} SOC_LPM3_CFG_HARQMEM_CTRL1_UNION;
#endif
#define SOC_LPM3_CFG_HARQMEM_CTRL1_soc_ap_dslp_grp4_START  (0)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_soc_ap_dslp_grp4_END    (3)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_soc_ap_dslp_grp5_START  (4)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_soc_ap_dslp_grp5_END    (9)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_soc_ap_dslp_grp6_START  (10)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_soc_ap_dslp_grp6_END    (20)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_soc_ap_dslp_grp7_START  (21)
#define SOC_LPM3_CFG_HARQMEM_CTRL1_soc_ap_dslp_grp7_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LPM3_CFG_NMI_SOFT_UNION
 �ṹ˵��  : NMI_SOFT �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x00000000�����:32
 �Ĵ���˵��: NMI���жϼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  nmi_soft : 1;  /* bit[0]   : ����ȥ��IOMCU��nmi���ж�
                                                   0�����ж�
                                                   1�����ж� */
        unsigned int  reserved : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_NMI_SOFT_UNION;
#endif
#define SOC_LPM3_CFG_NMI_SOFT_nmi_soft_START  (0)
#define SOC_LPM3_CFG_NMI_SOFT_nmi_soft_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_LPM3_CFG_HARQMEM_CTRL2_UNION
 �ṹ˵��  : HARQMEM_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x00000000�����:32
 �Ĵ���˵��: Harq memory����2�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  soc_ap_sd_grp4 : 4;  /* bit[0-3]  : group4 RAM �͹��Ŀ��ƣ�SD�ӿڣ�
                                                          bit[3:0] RAM3~RAM0 SD�ӿڣ�
                                                          1:��ʾshut downģʽ��
                                                          0:��ʾ����ģʽ�� */
        unsigned int  soc_ap_sd_grp5 : 6;  /* bit[4-9]  : group5 RAM �͹��Ŀ��ƣ�SD�ӿڣ�
                                                          bit[5:0] RAM5~RAM0 SD�ӿڣ�
                                                          1:��ʾshut downģʽ��
                                                          0:��ʾ����ģʽ�� */
        unsigned int  soc_ap_sd_grp6 : 11; /* bit[10-20]: group6 RAM �͹��Ŀ��ƣ�SD�ӿڣ�
                                                          bit[10:0] RAM10~RAM0 SD�ӿڣ�
                                                          1:��ʾshut downģʽ��
                                                          0:��ʾ����ģʽ�� */
        unsigned int  soc_ap_sd_grp7 : 11; /* bit[21-31]: group7 RAM �͹��Ŀ��ƣ�SD�ӿڣ�
                                                          bit[10:0] RAM10~RAM0 SD�ӿڣ�
                                                          1:��ʾshut downģʽ��
                                                          0:��ʾ����ģʽ�� */
    } reg;
} SOC_LPM3_CFG_HARQMEM_CTRL2_UNION;
#endif
#define SOC_LPM3_CFG_HARQMEM_CTRL2_soc_ap_sd_grp4_START  (0)
#define SOC_LPM3_CFG_HARQMEM_CTRL2_soc_ap_sd_grp4_END    (3)
#define SOC_LPM3_CFG_HARQMEM_CTRL2_soc_ap_sd_grp5_START  (4)
#define SOC_LPM3_CFG_HARQMEM_CTRL2_soc_ap_sd_grp5_END    (9)
#define SOC_LPM3_CFG_HARQMEM_CTRL2_soc_ap_sd_grp6_START  (10)
#define SOC_LPM3_CFG_HARQMEM_CTRL2_soc_ap_sd_grp6_END    (20)
#define SOC_LPM3_CFG_HARQMEM_CTRL2_soc_ap_sd_grp7_START  (21)
#define SOC_LPM3_CFG_HARQMEM_CTRL2_soc_ap_sd_grp7_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_LPM3_CFG_HARQMEM_CTRL3_UNION
 �ṹ˵��  : HARQMEM_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x00000000�����:32
 �Ĵ���˵��: Harq memory����3�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  soc_ap_occupy_grp1 : 2;  /* bit[0-1]  : 2'b0x��group 1��BBPռ��
                                                              2'b10��group 1��SOCռ�� */
        unsigned int  soc_ap_occupy_grp2 : 2;  /* bit[2-3]  : 2'b0x��group 2��BBPռ��
                                                              2'b10��group 2��SOCռ�� */
        unsigned int  soc_ap_occupy_grp3 : 2;  /* bit[4-5]  : 2'b0x��group 3��BBPռ��
                                                              2'b10��group 3��SOCռ�� */
        unsigned int  soc_ap_occupy_grp4 : 2;  /* bit[6-7]  : 2'b0x��group 4��BBPռ��
                                                              2'b10��group 4��SOCռ�� */
        unsigned int  soc_ap_occupy_grp5 : 2;  /* bit[8-9]  : 2'b0x��group 5��BBPռ��
                                                              2'b10��group 5��SOCռ�� */
        unsigned int  soc_ap_occupy_grp6 : 2;  /* bit[10-11]: 2'b0x��group 6��BBPռ��
                                                              2'b10��group 6��SOCռ�� */
        unsigned int  soc_ap_occupy_grp7 : 2;  /* bit[12-13]: 2'b0x��group 7��BBPռ��
                                                              2'b10��group 7��SOCռ�� */
        unsigned int  reserved           : 18; /* bit[14-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_HARQMEM_CTRL3_UNION;
#endif
#define SOC_LPM3_CFG_HARQMEM_CTRL3_soc_ap_occupy_grp1_START  (0)
#define SOC_LPM3_CFG_HARQMEM_CTRL3_soc_ap_occupy_grp1_END    (1)
#define SOC_LPM3_CFG_HARQMEM_CTRL3_soc_ap_occupy_grp2_START  (2)
#define SOC_LPM3_CFG_HARQMEM_CTRL3_soc_ap_occupy_grp2_END    (3)
#define SOC_LPM3_CFG_HARQMEM_CTRL3_soc_ap_occupy_grp3_START  (4)
#define SOC_LPM3_CFG_HARQMEM_CTRL3_soc_ap_occupy_grp3_END    (5)
#define SOC_LPM3_CFG_HARQMEM_CTRL3_soc_ap_occupy_grp4_START  (6)
#define SOC_LPM3_CFG_HARQMEM_CTRL3_soc_ap_occupy_grp4_END    (7)
#define SOC_LPM3_CFG_HARQMEM_CTRL3_soc_ap_occupy_grp5_START  (8)
#define SOC_LPM3_CFG_HARQMEM_CTRL3_soc_ap_occupy_grp5_END    (9)
#define SOC_LPM3_CFG_HARQMEM_CTRL3_soc_ap_occupy_grp6_START  (10)
#define SOC_LPM3_CFG_HARQMEM_CTRL3_soc_ap_occupy_grp6_END    (11)
#define SOC_LPM3_CFG_HARQMEM_CTRL3_soc_ap_occupy_grp7_START  (12)
#define SOC_LPM3_CFG_HARQMEM_CTRL3_soc_ap_occupy_grp7_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_LPM3_CFG_LOCK_UNION
 �ṹ˵��  : LOCK �Ĵ����ṹ���塣��ַƫ����:0x0A0����ֵ:0x00000001�����:32
 �Ĵ���˵��: ���������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  lock     : 1;  /* bit[0]   : ��HARQMEM_CTRL0/1/2/3�ķ��������Ĵ������������Ĵ�����Ӱ�죬Ĭ��Ϊ����״̬����Ҫд��0x1ACCE551���н�����д����������ֵ����������
                                                   ���ڶ�������
                                                   0������״̬��HARQMEM_CTRL0/1/2/3ΪRW
                                                   1������״̬��HARQMEM_CTRL0/1/2/3ΪRO */
        unsigned int  reserved : 31; /* bit[1-31]: Reserved */
    } reg;
} SOC_LPM3_CFG_LOCK_UNION;
#endif
#define SOC_LPM3_CFG_LOCK_lock_START      (0)
#define SOC_LPM3_CFG_LOCK_lock_END        (0)






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

#endif /* end of soc_lpm3_cfg_interface.h */
