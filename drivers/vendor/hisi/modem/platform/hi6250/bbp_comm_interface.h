/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : bbp_comm_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-05-11 11:35:35
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��5��11��
    ��    ��   : l00165286
    �޸�����   : �ӡ�Hi6250V100 MODEM�Ĵ����ֲ�_COMM.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#ifndef __BBP_COMM_INTERFACE_H__
#define __BBP_COMM_INTERFACE_H__

#include "bbp_comm_fe_interface.h"
#include "bbp_guc_bbpmst_interface.h"

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/***======================================================================***
                     (1/3) register_define_irm_cs
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    ����irm_csģʽѡ��Ӱ��irm_cs�ڲ�ʱ���л���ģʽ�л���Ĭ�϶�Ϊ0��
             3'b001��UMTSģʽ���������⣬����R99���RAM����
             3'b010��LTEģʽ������HARQ���֣���
             3'b100��CDMAģʽ��
             3'b000���ޣ�default����
   UNION�ṹ:  BBPCOMM_IRM_CS_RAM_CTRL_UNION */
#define BBPCOMM_IRM_CS_RAM_CTRL_ADDR                  (SOC_BBP_COMM_2_BASE_ADDR + 0xA000)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      irm_csģ��ʱ���ſ���·���ء�Ĭ��Ϊ0��������ʱ���ſء�����1������·���ܣ�ʱ���ſ�ʧЧ��
   UNION�ṹ:  BBPCOMM_IRM_CS_CLK_BYPASS_UNION */
#define BBPCOMM_IRM_CS_CLK_BYPASS_ADDR                (SOC_BBP_COMM_2_BASE_ADDR + 0xA004)

/* �Ĵ���˵����
 bit[31:16]  1w2r˫�˿�ram��ʱ���ơ�
 bit[15:0]   ���˿�ram��ʱ���ơ�
   UNION�ṹ:  BBPCOMM_MEM_CTRL0_CS_UNION */
#define BBPCOMM_MEM_CTRL0_CS_ADDR                     (SOC_BBP_COMM_2_BASE_ADDR + 0xA00C)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  rom��ʱ���ơ�
 bit[15:0]   1rw2rw˫�˿�ram��ʱ���ơ�
   UNION�ṹ:  BBPCOMM_MEM_CTRL1_CS_UNION */
#define BBPCOMM_MEM_CTRL1_CS_ADDR                     (SOC_BBP_COMM_2_BASE_ADDR + 0xA010)



/***======================================================================***
                     (2/3) register_define_irm_ps
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5:0]    ����irm_ps����ģʽѡ��Ӱ��irm_ps�ڲ�ʱ���л���ģʽ�л���Ĭ�϶�Ϊ0��.
             6'b000001��GBBP1ģʽ��
             6'b000110��UMTSģʽ��
             6'b001000��LTEģʽ��
             6'b010000��TDS-CDMAģʽ��
             6'b100000��CDMAģʽ��
             ע��GBBP1�̶�Ϊ������G0/U/L/T����
   UNION�ṹ:  BBPCOMM_IRM_PS_RAM_CTRL_UNION */
#define BBPCOMM_IRM_PS_RAM_CTRL_ADDR                  (SOC_BBP_COMM_2_BASE_ADDR + 0xB000)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      GBBP2��Ĭ��Ϊ0��1Ϊʹ�ܡ�
             ע��GBBP2�̶�Ϊ������
             V8R1��ʹ�á�
   UNION�ṹ:  BBPCOMM_IRM_PS_GSM2_CTRL_UNION */
#define BBPCOMM_IRM_PS_GSM2_CTRL_ADDR                 (SOC_BBP_COMM_2_BASE_ADDR + 0xB004)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      irm_psģ��ʱ���ſ���·���ء�Ĭ��Ϊ0��������ʱ���ſء�����1������·���ܣ�ʱ���ſ�ʧЧ��
   UNION�ṹ:  BBPCOMM_IRM_PS_CLK_BYPASS_UNION */
#define BBPCOMM_IRM_PS_CLK_BYPASS_ADDR                (SOC_BBP_COMM_2_BASE_ADDR + 0xB008)

/* �Ĵ���˵����
 bit[31:16]  1w2r˫�˿�ram��ʱ���ơ�
 bit[15:0]   ���˿�ram��ʱ���ơ�
   UNION�ṹ:  BBPCOMM_MEM_CTRL0_TURBO_UNION */
#define BBPCOMM_MEM_CTRL0_TURBO_ADDR                  (SOC_BBP_COMM_2_BASE_ADDR + 0xB010)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  rom��ʱ���ơ�
 bit[15:0]   1rw2rw˫�˿�ram��ʱ���ơ�
   UNION�ṹ:  BBPCOMM_MEM_CTRL1_TURBO_UNION */
#define BBPCOMM_MEM_CTRL1_TURBO_ADDR                  (SOC_BBP_COMM_2_BASE_ADDR + 0xB014)

/* �Ĵ���˵����
 bit[31:14]  ����
 bit[13:8]   LTE��ͨ��ѡ���źţ�0��ʾѡ��ͨ��0,1��ʾѡ��ͨ��1
             bit[8]����ʾgrp0
             bit[9]����ʾgrp1
             bit[10]����ʾgrp2
             bit[11]����ʾgrp3
             bit[12]����ʾgrp4
             bit[13]����ʾgrp5
 bit[7:6]    ����
 bit[5:0]    1��ʾѡ�����õ�lte_irm_grp_clk_over_val��0��ʾѡ���LTE�����grp_clk_sel
             bit[0]����ʾgrp0
             bit[1]����ʾgrp1
             bit[2]����ʾgrp2
             bit[3]����ʾgrp3
             bit[4]����ʾgrp4
             bit[5]����ʾgrp5
   UNION�ṹ:  BBPCOMM_LTE_IRM_GRP_SEL_UNION */
#define BBPCOMM_LTE_IRM_GRP_SEL_ADDR                  (SOC_BBP_COMM_2_BASE_ADDR + 0xB018)

/* �Ĵ���˵����
 bit[31:16]  1w2r˫�˿�ram��ʱ���ơ�
 bit[15:0]   ���˿�ram��ʱ���ơ�
   UNION�ṹ:  BBPCOMM_MEM_CTRL0_PS_UNION */
#define BBPCOMM_MEM_CTRL0_PS_ADDR                     (SOC_BBP_COMM_2_BASE_ADDR + 0xB020)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  rom��ʱ���ơ�
 bit[15:0]   1rw2rw˫�˿�ram��ʱ���ơ�
   UNION�ṹ:  BBPCOMM_MEM_CTRL1_PS_UNION */
#define BBPCOMM_MEM_CTRL1_PS_ADDR                     (SOC_BBP_COMM_2_BASE_ADDR + 0xB024)

/* �Ĵ���˵����
 bit[31:16]  turbo������ģ�鼶�ſ���·ʹ�ܣ��ߵ�ƽ��Ч��
 bit[15:0]   turbo������ģ�鼶�ſ���·ʹ�ܣ��ߵ�ƽ��Ч��
   UNION�ṹ:  BBPCOMM_TUBO_CKG_UNION */
#define BBPCOMM_TUBO_CKG_ADDR                         (SOC_BBP_COMM_2_BASE_ADDR + 0xB028)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      Turbo����ģʽѡ���źţ�Lģ����
             {U_C_TYPE, U_T_TYPE, U_L_TYPE}��������bitƴ����Ϻ������£�
             3'b000��Uģ��
             3'b001��Lģ��
             3'b010��Tģ��
             3'b100��Cģ��
             �����������塣
   UNION�ṹ:  BBPCOMM_U_L_TYPE_UNION */
#define BBPCOMM_U_L_TYPE_ADDR                         (SOC_BBP_COMM_2_BASE_ADDR + 0xB02C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      Turbo����ģʽѡ���źţ�Tģ����
             {U_C_TYPE, U_T_TYPE, U_L_TYPE}��������bitƴ����Ϻ������£�
             3'b000��Uģ��
             3'b001��Lģ��
             3'b010��Tģ��
             3'b100��Cģ��
             �����������塣
   UNION�ṹ:  BBPCOMM_U_T_TYPE_UNION */
#define BBPCOMM_U_T_TYPE_ADDR                         (SOC_BBP_COMM_2_BASE_ADDR + 0xB030)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      Turbo����ģʽѡ���źţ�Cģ����
             {U_C_TYPE, U_T_TYPE, U_L_TYPE}��������bitƴ����Ϻ������£�
             3'b000��Uģ��
             3'b001��Lģ��
             3'b010��Tģ��
             3'b100��Cģ��
             �����������塣
   UNION�ṹ:  BBPCOMM_U_C_TYPE_UNION */
#define BBPCOMM_U_C_TYPE_ADDR                         (SOC_BBP_COMM_2_BASE_ADDR + 0xB034)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:14]  SOC AP���ø�ps ram��occupy�����źš�
 bit[13:12]  
 bit[11:10]  
 bit[9:8]    
 bit[7:6]    
 bit[5:4]    
 bit[3:2]    
 bit[1:0]    
   UNION�ṹ:  BBPCOMM_SOC_AP_OCCUPY_GRP_UNION */
#define BBPCOMM_SOC_AP_OCCUPY_GRP_ADDR                (SOC_BBP_COMM_2_BASE_ADDR + 0xB038)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1]      W SDRģʽ������ʱ��ѡ��0���������122mʱ�ӣ�1���������245mʱ�ӡ�
 bit[0]      W SDRģʽ����ʹ�ܡ�
   UNION�ṹ:  BBPCOMM_PS_W_SDR_EN_UNION */
#define BBPCOMM_PS_W_SDR_EN_ADDR                      (SOC_BBP_COMM_2_BASE_ADDR + 0xB03C)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4]      turbo������ͨ��Ӳ�бȶ��ж������������л����أ�Ĭ�ϴ�
             0���Ƚ��������εĵ�����������һ������Ϊ������
             1���Ƚ��������εĵ�����������һ������Ϊ������
 bit[3:1]    ����
 bit[0]      Turbo������Ӳ�бȶ���ǰֹͣ����ʹ�ܣ�Ĭ��ʹ��CRCУ�����ǰֹͣ����
             0����ֹ
             1��ʹ��
   UNION�ṹ:  BBPCOMM_TURBO_HD_JUDGE_EN_UNION */
#define BBPCOMM_TURBO_HD_JUDGE_EN_ADDR                (SOC_BBP_COMM_2_BASE_ADDR + 0xB040)



/***======================================================================***
                     (3/3) register_define_glb_bbc
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:2]    bit[1]��0����ʾ�ɼ�GBBP1�����ݣ�1����ʾ�ɼ�GBBP2�����ݡ��������壬������
             bit[0]��0����ʾ�ɼ�W���ݣ�1��ʾ�ɼ�G���ݡ��������壬������
 bit[1:0]    bit[1]��0����ʾ�ɼ�GBBP1�����ݣ�1����ʾ�ɼ�GBBP2�����ݡ�
             bit[0]��0����ʾ�ɼ�W���ݣ�1��ʾ�ɼ�G���ݡ��������壬������
   UNION�ṹ:  BBPCOMM_BBP_DUMP_DBG_MODE_UNION */
#define BBPCOMM_BBP_DUMP_DBG_MODE_ADDR                (SOC_BBP_COMM_2_BASE_ADDR + 0xD800)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2]      WSDRģʽ������ʱ��ѡ��0���������122mʱ�ӣ�1���������245mʱ�ӡ��������壬������
 bit[1]      WSDRģʽ����ʹ�ܡ��������壬������
 bit[0]      GSDRģʽ����ʹ�ܡ��������壬������
   UNION�ṹ:  BBPCOMM_GU_SDR_EN_UNION */
#define BBPCOMM_GU_SDR_EN_ADDR                        (SOC_BBP_COMM_2_BASE_ADDR + 0xD804)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      UC2_SHARE CPU�ӿ�ʱ���Զ��ſ�BYPASS�źš�
 bit[8]      CBBP_TOP_2 CPU�ӿ�ʱ���Զ��ſ�BYPASS�źš�
 bit[7]      WBBP_R99 CPU�ӿ�ʱ���Զ��ſ�BYPASS�źš�
 bit[6]      WTC_SHARE CPU�ӿ�ʱ���Զ��ſ�BYPASS�źš�
 bit[5]      CBBP_TOP CPU�ӿ�ʱ���Զ��ſ�BYPASS�źš�
 bit[4]      WBBP_TOP2 CPU�ӿ�ʱ���Զ��ſ�BYPASS�źš�
 bit[3]      WBBP_TOP1 CPU�ӿ�ʱ���Զ��ſ�BYPASS�źš�
 bit[2]      GBBP_TOP2 CPU�ӿ�ʱ���Զ��ſ�BYPASS�źš�
 bit[1]      GBBP_TOP1 CPU�ӿ�ʱ���Զ��ſ�BYPASS�źš�
 bit[0]      BBC_COMM CPU�ӿ�ʱ���Զ��ſ�BYPASS�źš�
   UNION�ṹ:  BBPCOMM_CPU_CLK_GATE_BYPASS_UNION */
#define BBPCOMM_CPU_CLK_GATE_BYPASS_ADDR              (SOC_BBP_COMM_2_BASE_ADDR + 0xD808)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      CDMA GPSͬ���ź�ѡ��0��ѡ��CBBP_TOP�����GPSͬ���źţ�1��ѡ��CBBP_TOP_2�����GPSͬ���źš�
   UNION�ṹ:  BBPCOMM_CDMA_GPS_SYNC_SEL_UNION */
#define BBPCOMM_CDMA_GPS_SYNC_SEL_ADDR                (SOC_BBP_COMM_2_BASE_ADDR + 0xD80C)





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

/***======================================================================***
                     (1/3) register_define_irm_cs
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : BBPCOMM_IRM_CS_RAM_CTRL_UNION
 �ṹ˵��  : IRM_CS_RAM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      irm_cs_ram_ctrl_reg;
    struct
    {
        unsigned int  irm_cs_ram_ctrl : 3;  /* bit[0-2] : ����irm_csģʽѡ��Ӱ��irm_cs�ڲ�ʱ���л���ģʽ�л���Ĭ�϶�Ϊ0��
                                                          3'b001��UMTSģʽ���������⣬����R99���RAM����
                                                          3'b010��LTEģʽ������HARQ���֣���
                                                          3'b100��CDMAģʽ��
                                                          3'b000���ޣ�default���� */
        unsigned int  reserved        : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_IRM_CS_RAM_CTRL_UNION;
#define BBPCOMM_IRM_CS_RAM_CTRL_irm_cs_ram_ctrl_START  (0)
#define BBPCOMM_IRM_CS_RAM_CTRL_irm_cs_ram_ctrl_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_IRM_CS_CLK_BYPASS_UNION
 �ṹ˵��  : IRM_CS_CLK_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      irm_cs_clk_bypass_reg;
    struct
    {
        unsigned int  irm_cs_clk_bypass : 1;  /* bit[0]   : irm_csģ��ʱ���ſ���·���ء�Ĭ��Ϊ0��������ʱ���ſء�����1������·���ܣ�ʱ���ſ�ʧЧ�� */
        unsigned int  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_IRM_CS_CLK_BYPASS_UNION;
#define BBPCOMM_IRM_CS_CLK_BYPASS_irm_cs_clk_bypass_START  (0)
#define BBPCOMM_IRM_CS_CLK_BYPASS_irm_cs_clk_bypass_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MEM_CTRL0_CS_UNION
 �ṹ˵��  : MEM_CTRL0_CS �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x03501050�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mem_ctrl0_cs_reg;
    struct
    {
        unsigned int  mem_ctrl_s_cs      : 16; /* bit[0-15] : ���˿�ram��ʱ���ơ� */
        unsigned int  mem_ctrl_d_1w2r_cs : 16; /* bit[16-31]: 1w2r˫�˿�ram��ʱ���ơ� */
    } reg;
} BBPCOMM_MEM_CTRL0_CS_UNION;
#define BBPCOMM_MEM_CTRL0_CS_mem_ctrl_s_cs_START       (0)
#define BBPCOMM_MEM_CTRL0_CS_mem_ctrl_s_cs_END         (15)
#define BBPCOMM_MEM_CTRL0_CS_mem_ctrl_d_1w2r_cs_START  (16)
#define BBPCOMM_MEM_CTRL0_CS_mem_ctrl_d_1w2r_cs_END    (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MEM_CTRL1_CS_UNION
 �ṹ˵��  : MEM_CTRL1_CS �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00700057�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mem_ctrl1_cs_reg;
    struct
    {
        unsigned int  mem_ctrl_d_1rw2rw_cs : 16; /* bit[0-15] : 1rw2rw˫�˿�ram��ʱ���ơ� */
        unsigned int  rom_ctrl_cs          : 8;  /* bit[16-23]: rom��ʱ���ơ� */
        unsigned int  reserved             : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_MEM_CTRL1_CS_UNION;
#define BBPCOMM_MEM_CTRL1_CS_mem_ctrl_d_1rw2rw_cs_START  (0)
#define BBPCOMM_MEM_CTRL1_CS_mem_ctrl_d_1rw2rw_cs_END    (15)
#define BBPCOMM_MEM_CTRL1_CS_rom_ctrl_cs_START           (16)
#define BBPCOMM_MEM_CTRL1_CS_rom_ctrl_cs_END             (23)


/***======================================================================***
                     (2/3) register_define_irm_ps
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : BBPCOMM_IRM_PS_RAM_CTRL_UNION
 �ṹ˵��  : IRM_PS_RAM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      irm_ps_ram_ctrl_reg;
    struct
    {
        unsigned int  irm_ps_ram_ctrl : 6;  /* bit[0-5] : ����irm_ps����ģʽѡ��Ӱ��irm_ps�ڲ�ʱ���л���ģʽ�л���Ĭ�϶�Ϊ0��.
                                                          6'b000001��GBBP1ģʽ��
                                                          6'b000110��UMTSģʽ��
                                                          6'b001000��LTEģʽ��
                                                          6'b010000��TDS-CDMAģʽ��
                                                          6'b100000��CDMAģʽ��
                                                          ע��GBBP1�̶�Ϊ������G0/U/L/T���� */
        unsigned int  reserved        : 26; /* bit[6-31]: ���� */
    } reg;
} BBPCOMM_IRM_PS_RAM_CTRL_UNION;
#define BBPCOMM_IRM_PS_RAM_CTRL_irm_ps_ram_ctrl_START  (0)
#define BBPCOMM_IRM_PS_RAM_CTRL_irm_ps_ram_ctrl_END    (5)


/*****************************************************************************
 �ṹ��    : BBPCOMM_IRM_PS_GSM2_CTRL_UNION
 �ṹ˵��  : IRM_PS_GSM2_CTRL �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      irm_ps_gsm2_ctrl_reg;
    struct
    {
        unsigned int  irm_ps_gsm2_ctrl : 1;  /* bit[0]   : GBBP2��Ĭ��Ϊ0��1Ϊʹ�ܡ�
                                                           ע��GBBP2�̶�Ϊ������
                                                           V8R1��ʹ�á� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_IRM_PS_GSM2_CTRL_UNION;
#define BBPCOMM_IRM_PS_GSM2_CTRL_irm_ps_gsm2_ctrl_START  (0)
#define BBPCOMM_IRM_PS_GSM2_CTRL_irm_ps_gsm2_ctrl_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_IRM_PS_CLK_BYPASS_UNION
 �ṹ˵��  : IRM_PS_CLK_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      irm_ps_clk_bypass_reg;
    struct
    {
        unsigned int  irm_ps_clk_bypass : 1;  /* bit[0]   : irm_psģ��ʱ���ſ���·���ء�Ĭ��Ϊ0��������ʱ���ſء�����1������·���ܣ�ʱ���ſ�ʧЧ�� */
        unsigned int  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_IRM_PS_CLK_BYPASS_UNION;
#define BBPCOMM_IRM_PS_CLK_BYPASS_irm_ps_clk_bypass_START  (0)
#define BBPCOMM_IRM_PS_CLK_BYPASS_irm_ps_clk_bypass_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MEM_CTRL0_TURBO_UNION
 �ṹ˵��  : MEM_CTRL0_TURBO �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x03501050�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mem_ctrl0_turbo_reg;
    struct
    {
        unsigned int  mem_ctrl_s_turbo      : 16; /* bit[0-15] : ���˿�ram��ʱ���ơ� */
        unsigned int  mem_ctrl_d_1w2r_turbo : 16; /* bit[16-31]: 1w2r˫�˿�ram��ʱ���ơ� */
    } reg;
} BBPCOMM_MEM_CTRL0_TURBO_UNION;
#define BBPCOMM_MEM_CTRL0_TURBO_mem_ctrl_s_turbo_START       (0)
#define BBPCOMM_MEM_CTRL0_TURBO_mem_ctrl_s_turbo_END         (15)
#define BBPCOMM_MEM_CTRL0_TURBO_mem_ctrl_d_1w2r_turbo_START  (16)
#define BBPCOMM_MEM_CTRL0_TURBO_mem_ctrl_d_1w2r_turbo_END    (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MEM_CTRL1_TURBO_UNION
 �ṹ˵��  : MEM_CTRL1_TURBO �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00700057�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mem_ctrl1_turbo_reg;
    struct
    {
        unsigned int  mem_ctrl_d_1rw2rw_turbo : 16; /* bit[0-15] : 1rw2rw˫�˿�ram��ʱ���ơ� */
        unsigned int  rom_ctrl_turbo          : 8;  /* bit[16-23]: rom��ʱ���ơ� */
        unsigned int  reserved                : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_MEM_CTRL1_TURBO_UNION;
#define BBPCOMM_MEM_CTRL1_TURBO_mem_ctrl_d_1rw2rw_turbo_START  (0)
#define BBPCOMM_MEM_CTRL1_TURBO_mem_ctrl_d_1rw2rw_turbo_END    (15)
#define BBPCOMM_MEM_CTRL1_TURBO_rom_ctrl_turbo_START           (16)
#define BBPCOMM_MEM_CTRL1_TURBO_rom_ctrl_turbo_END             (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_LTE_IRM_GRP_SEL_UNION
 �ṹ˵��  : LTE_IRM_GRP_SEL �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      lte_irm_grp_sel_reg;
    struct
    {
        unsigned int  lte_irm_grp_clk_sel_overwhelm : 6;  /* bit[0-5]  : 1��ʾѡ�����õ�lte_irm_grp_clk_over_val��0��ʾѡ���LTE�����grp_clk_sel
                                                                         bit[0]����ʾgrp0
                                                                         bit[1]����ʾgrp1
                                                                         bit[2]����ʾgrp2
                                                                         bit[3]����ʾgrp3
                                                                         bit[4]����ʾgrp4
                                                                         bit[5]����ʾgrp5 */
        unsigned int  reserved_0                    : 2;  /* bit[6-7]  : ���� */
        unsigned int  lte_irm_grp_clk_over_val      : 6;  /* bit[8-13] : LTE��ͨ��ѡ���źţ�0��ʾѡ��ͨ��0,1��ʾѡ��ͨ��1
                                                                         bit[8]����ʾgrp0
                                                                         bit[9]����ʾgrp1
                                                                         bit[10]����ʾgrp2
                                                                         bit[11]����ʾgrp3
                                                                         bit[12]����ʾgrp4
                                                                         bit[13]����ʾgrp5 */
        unsigned int  reserved_1                    : 18; /* bit[14-31]: ���� */
    } reg;
} BBPCOMM_LTE_IRM_GRP_SEL_UNION;
#define BBPCOMM_LTE_IRM_GRP_SEL_lte_irm_grp_clk_sel_overwhelm_START  (0)
#define BBPCOMM_LTE_IRM_GRP_SEL_lte_irm_grp_clk_sel_overwhelm_END    (5)
#define BBPCOMM_LTE_IRM_GRP_SEL_lte_irm_grp_clk_over_val_START       (8)
#define BBPCOMM_LTE_IRM_GRP_SEL_lte_irm_grp_clk_over_val_END         (13)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MEM_CTRL0_PS_UNION
 �ṹ˵��  : MEM_CTRL0_PS �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x03501050�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mem_ctrl0_ps_reg;
    struct
    {
        unsigned int  mem_ctrl_s_ps      : 16; /* bit[0-15] : ���˿�ram��ʱ���ơ� */
        unsigned int  mem_ctrl_d_1w2r_ps : 16; /* bit[16-31]: 1w2r˫�˿�ram��ʱ���ơ� */
    } reg;
} BBPCOMM_MEM_CTRL0_PS_UNION;
#define BBPCOMM_MEM_CTRL0_PS_mem_ctrl_s_ps_START       (0)
#define BBPCOMM_MEM_CTRL0_PS_mem_ctrl_s_ps_END         (15)
#define BBPCOMM_MEM_CTRL0_PS_mem_ctrl_d_1w2r_ps_START  (16)
#define BBPCOMM_MEM_CTRL0_PS_mem_ctrl_d_1w2r_ps_END    (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MEM_CTRL1_PS_UNION
 �ṹ˵��  : MEM_CTRL1_PS �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00700057�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mem_ctrl1_ps_reg;
    struct
    {
        unsigned int  mem_ctrl_d_1rw2rw_ps : 16; /* bit[0-15] : 1rw2rw˫�˿�ram��ʱ���ơ� */
        unsigned int  rom_ctrl_ps          : 8;  /* bit[16-23]: rom��ʱ���ơ� */
        unsigned int  reserved             : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_MEM_CTRL1_PS_UNION;
#define BBPCOMM_MEM_CTRL1_PS_mem_ctrl_d_1rw2rw_ps_START  (0)
#define BBPCOMM_MEM_CTRL1_PS_mem_ctrl_d_1rw2rw_ps_END    (15)
#define BBPCOMM_MEM_CTRL1_PS_rom_ctrl_ps_START           (16)
#define BBPCOMM_MEM_CTRL1_PS_rom_ctrl_ps_END             (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TUBO_CKG_UNION
 �ṹ˵��  : TUBO_CKG �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      tubo_ckg_reg;
    struct
    {
        unsigned int  tubo_ram_ckg_en : 16; /* bit[0-15] : turbo������ģ�鼶�ſ���·ʹ�ܣ��ߵ�ƽ��Ч�� */
        unsigned int  tubo_mod_ckg_en : 16; /* bit[16-31]: turbo������ģ�鼶�ſ���·ʹ�ܣ��ߵ�ƽ��Ч�� */
    } reg;
} BBPCOMM_TUBO_CKG_UNION;
#define BBPCOMM_TUBO_CKG_tubo_ram_ckg_en_START  (0)
#define BBPCOMM_TUBO_CKG_tubo_ram_ckg_en_END    (15)
#define BBPCOMM_TUBO_CKG_tubo_mod_ckg_en_START  (16)
#define BBPCOMM_TUBO_CKG_tubo_mod_ckg_en_END    (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_U_L_TYPE_UNION
 �ṹ˵��  : U_L_TYPE �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      u_l_type_reg;
    struct
    {
        unsigned int  u_l_type : 1;  /* bit[0]   : Turbo����ģʽѡ���źţ�Lģ����
                                                   {U_C_TYPE, U_T_TYPE, U_L_TYPE}��������bitƴ����Ϻ������£�
                                                   3'b000��Uģ��
                                                   3'b001��Lģ��
                                                   3'b010��Tģ��
                                                   3'b100��Cģ��
                                                   �����������塣 */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_U_L_TYPE_UNION;
#define BBPCOMM_U_L_TYPE_u_l_type_START  (0)
#define BBPCOMM_U_L_TYPE_u_l_type_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_U_T_TYPE_UNION
 �ṹ˵��  : U_T_TYPE �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      u_t_type_reg;
    struct
    {
        unsigned int  u_t_type : 1;  /* bit[0]   : Turbo����ģʽѡ���źţ�Tģ����
                                                   {U_C_TYPE, U_T_TYPE, U_L_TYPE}��������bitƴ����Ϻ������£�
                                                   3'b000��Uģ��
                                                   3'b001��Lģ��
                                                   3'b010��Tģ��
                                                   3'b100��Cģ��
                                                   �����������塣 */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_U_T_TYPE_UNION;
#define BBPCOMM_U_T_TYPE_u_t_type_START  (0)
#define BBPCOMM_U_T_TYPE_u_t_type_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_U_C_TYPE_UNION
 �ṹ˵��  : U_C_TYPE �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      u_c_type_reg;
    struct
    {
        unsigned int  u_c_type : 1;  /* bit[0]   : Turbo����ģʽѡ���źţ�Cģ����
                                                   {U_C_TYPE, U_T_TYPE, U_L_TYPE}��������bitƴ����Ϻ������£�
                                                   3'b000��Uģ��
                                                   3'b001��Lģ��
                                                   3'b010��Tģ��
                                                   3'b100��Cģ��
                                                   �����������塣 */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_U_C_TYPE_UNION;
#define BBPCOMM_U_C_TYPE_u_c_type_START  (0)
#define BBPCOMM_U_C_TYPE_u_c_type_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_SOC_AP_OCCUPY_GRP_UNION
 �ṹ˵��  : SOC_AP_OCCUPY_GRP �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      soc_ap_occupy_grp_reg;
    struct
    {
        unsigned int  soc_ap_occupy_grp1 : 2;  /* bit[0-1]  :  */
        unsigned int  soc_ap_occupy_grp2 : 2;  /* bit[2-3]  :  */
        unsigned int  soc_ap_occupy_grp3 : 2;  /* bit[4-5]  :  */
        unsigned int  soc_ap_occupy_grp4 : 2;  /* bit[6-7]  :  */
        unsigned int  soc_ap_occupy_grp5 : 2;  /* bit[8-9]  :  */
        unsigned int  soc_ap_occupy_grp6 : 2;  /* bit[10-11]:  */
        unsigned int  soc_ap_occupy_grp7 : 2;  /* bit[12-13]:  */
        unsigned int  soc_ap_occupy_grp8 : 2;  /* bit[14-15]: SOC AP���ø�ps ram��occupy�����źš� */
        unsigned int  reserved           : 16; /* bit[16-31]: ���� */
    } reg;
} BBPCOMM_SOC_AP_OCCUPY_GRP_UNION;
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp1_START  (0)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp1_END    (1)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp2_START  (2)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp2_END    (3)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp3_START  (4)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp3_END    (5)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp4_START  (6)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp4_END    (7)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp5_START  (8)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp5_END    (9)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp6_START  (10)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp6_END    (11)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp7_START  (12)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp7_END    (13)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp8_START  (14)
#define BBPCOMM_SOC_AP_OCCUPY_GRP_soc_ap_occupy_grp8_END    (15)


/*****************************************************************************
 �ṹ��    : BBPCOMM_PS_W_SDR_EN_UNION
 �ṹ˵��  : PS_W_SDR_EN �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      ps_w_sdr_en_reg;
    struct
    {
        unsigned int  ps_w_sdr_en          : 1;  /* bit[0]   : W SDRģʽ����ʹ�ܡ� */
        unsigned int  ps_w_sdr_dec_clk_sel : 1;  /* bit[1]   : W SDRģʽ������ʱ��ѡ��0���������122mʱ�ӣ�1���������245mʱ�ӡ� */
        unsigned int  reserved             : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_PS_W_SDR_EN_UNION;
#define BBPCOMM_PS_W_SDR_EN_ps_w_sdr_en_START           (0)
#define BBPCOMM_PS_W_SDR_EN_ps_w_sdr_en_END             (0)
#define BBPCOMM_PS_W_SDR_EN_ps_w_sdr_dec_clk_sel_START  (1)
#define BBPCOMM_PS_W_SDR_EN_ps_w_sdr_dec_clk_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_TURBO_HD_JUDGE_EN_UNION
 �ṹ˵��  : TURBO_HD_JUDGE_EN �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00000010�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      turbo_hd_judge_en_reg;
    struct
    {
        unsigned int  c_tc_iter_over_en       : 1;  /* bit[0]   : Turbo������Ӳ�бȶ���ǰֹͣ����ʹ�ܣ�Ĭ��ʹ��CRCУ�����ǰֹͣ����
                                                                  0����ֹ
                                                                  1��ʹ�� */
        unsigned int  reserved_0              : 3;  /* bit[1-3] : ���� */
        unsigned int  c_conv_judge_enhance_en : 1;  /* bit[4]   : turbo������ͨ��Ӳ�бȶ��ж������������л����أ�Ĭ�ϴ�
                                                                  0���Ƚ��������εĵ�����������һ������Ϊ������
                                                                  1���Ƚ��������εĵ�����������һ������Ϊ������ */
        unsigned int  reserved_1              : 27; /* bit[5-31]: ���� */
    } reg;
} BBPCOMM_TURBO_HD_JUDGE_EN_UNION;
#define BBPCOMM_TURBO_HD_JUDGE_EN_c_tc_iter_over_en_START        (0)
#define BBPCOMM_TURBO_HD_JUDGE_EN_c_tc_iter_over_en_END          (0)
#define BBPCOMM_TURBO_HD_JUDGE_EN_c_conv_judge_enhance_en_START  (4)
#define BBPCOMM_TURBO_HD_JUDGE_EN_c_conv_judge_enhance_en_END    (4)


/***======================================================================***
                     (3/3) register_define_glb_bbc
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : BBPCOMM_BBP_DUMP_DBG_MODE_UNION
 �ṹ˵��  : BBP_DUMP_DBG_MODE �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbp_dump_dbg_mode_reg;
    struct
    {
        unsigned int  dump_data_mode  : 2;  /* bit[0-1] : bit[1]��0����ʾ�ɼ�GBBP1�����ݣ�1����ʾ�ɼ�GBBP2�����ݡ�
                                                          bit[0]��0����ʾ�ɼ�W���ݣ�1��ʾ�ɼ�G���ݡ��������壬������ */
        unsigned int  debug_data_mode : 2;  /* bit[2-3] : bit[1]��0����ʾ�ɼ�GBBP1�����ݣ�1����ʾ�ɼ�GBBP2�����ݡ��������壬������
                                                          bit[0]��0����ʾ�ɼ�W���ݣ�1��ʾ�ɼ�G���ݡ��������壬������ */
        unsigned int  reserved        : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_BBP_DUMP_DBG_MODE_UNION;
#define BBPCOMM_BBP_DUMP_DBG_MODE_dump_data_mode_START   (0)
#define BBPCOMM_BBP_DUMP_DBG_MODE_dump_data_mode_END     (1)
#define BBPCOMM_BBP_DUMP_DBG_MODE_debug_data_mode_START  (2)
#define BBPCOMM_BBP_DUMP_DBG_MODE_debug_data_mode_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_GU_SDR_EN_UNION
 �ṹ˵��  : GU_SDR_EN �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      gu_sdr_en_reg;
    struct
    {
        unsigned int  g_sdr_en          : 1;  /* bit[0]   : GSDRģʽ����ʹ�ܡ��������壬������ */
        unsigned int  w_sdr_en          : 1;  /* bit[1]   : WSDRģʽ����ʹ�ܡ��������壬������ */
        unsigned int  w_sdr_dec_clk_sel : 1;  /* bit[2]   : WSDRģʽ������ʱ��ѡ��0���������122mʱ�ӣ�1���������245mʱ�ӡ��������壬������ */
        unsigned int  reserved          : 29; /* bit[3-31]: ���� */
    } reg;
} BBPCOMM_GU_SDR_EN_UNION;
#define BBPCOMM_GU_SDR_EN_g_sdr_en_START           (0)
#define BBPCOMM_GU_SDR_EN_g_sdr_en_END             (0)
#define BBPCOMM_GU_SDR_EN_w_sdr_en_START           (1)
#define BBPCOMM_GU_SDR_EN_w_sdr_en_END             (1)
#define BBPCOMM_GU_SDR_EN_w_sdr_dec_clk_sel_START  (2)
#define BBPCOMM_GU_SDR_EN_w_sdr_dec_clk_sel_END    (2)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CPU_CLK_GATE_BYPASS_UNION
 �ṹ˵��  : CPU_CLK_GATE_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cpu_clk_gate_bypass_reg;
    struct
    {
        unsigned int  bbc_cpu_clk_gate_bypass       : 1;  /* bit[0]    : BBC_COMM CPU�ӿ�ʱ���Զ��ſ�BYPASS�źš� */
        unsigned int  g1_cpu_clk_gate_bypass        : 1;  /* bit[1]    : GBBP_TOP1 CPU�ӿ�ʱ���Զ��ſ�BYPASS�źš� */
        unsigned int  g2_cpu_clk_gate_bypass        : 1;  /* bit[2]    : GBBP_TOP2 CPU�ӿ�ʱ���Զ��ſ�BYPASS�źš� */
        unsigned int  w1_cpu_clk_gate_bypass        : 1;  /* bit[3]    : WBBP_TOP1 CPU�ӿ�ʱ���Զ��ſ�BYPASS�źš� */
        unsigned int  w2_cpu_clk_gate_bypass        : 1;  /* bit[4]    : WBBP_TOP2 CPU�ӿ�ʱ���Զ��ſ�BYPASS�źš� */
        unsigned int  c_cpu_clk_gate_bypass         : 1;  /* bit[5]    : CBBP_TOP CPU�ӿ�ʱ���Զ��ſ�BYPASS�źš� */
        unsigned int  wtc_share_cpu_clk_gate_bypass : 1;  /* bit[6]    : WTC_SHARE CPU�ӿ�ʱ���Զ��ſ�BYPASS�źš� */
        unsigned int  r99w2_cpu_clk_gate_bypass     : 1;  /* bit[7]    : WBBP_R99 CPU�ӿ�ʱ���Զ��ſ�BYPASS�źš� */
        unsigned int  c2_cpu_clk_gate_bypass        : 1;  /* bit[8]    : CBBP_TOP_2 CPU�ӿ�ʱ���Զ��ſ�BYPASS�źš� */
        unsigned int  wc2_share_cpu_clk_gate_bypass : 1;  /* bit[9]    : UC2_SHARE CPU�ӿ�ʱ���Զ��ſ�BYPASS�źš� */
        unsigned int  reserved                      : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_CPU_CLK_GATE_BYPASS_UNION;
#define BBPCOMM_CPU_CLK_GATE_BYPASS_bbc_cpu_clk_gate_bypass_START        (0)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_bbc_cpu_clk_gate_bypass_END          (0)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_g1_cpu_clk_gate_bypass_START         (1)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_g1_cpu_clk_gate_bypass_END           (1)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_g2_cpu_clk_gate_bypass_START         (2)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_g2_cpu_clk_gate_bypass_END           (2)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_w1_cpu_clk_gate_bypass_START         (3)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_w1_cpu_clk_gate_bypass_END           (3)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_w2_cpu_clk_gate_bypass_START         (4)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_w2_cpu_clk_gate_bypass_END           (4)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_c_cpu_clk_gate_bypass_START          (5)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_c_cpu_clk_gate_bypass_END            (5)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_wtc_share_cpu_clk_gate_bypass_START  (6)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_wtc_share_cpu_clk_gate_bypass_END    (6)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_r99w2_cpu_clk_gate_bypass_START      (7)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_r99w2_cpu_clk_gate_bypass_END        (7)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_c2_cpu_clk_gate_bypass_START         (8)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_c2_cpu_clk_gate_bypass_END           (8)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_wc2_share_cpu_clk_gate_bypass_START  (9)
#define BBPCOMM_CPU_CLK_GATE_BYPASS_wc2_share_cpu_clk_gate_bypass_END    (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_CDMA_GPS_SYNC_SEL_UNION
 �ṹ˵��  : CDMA_GPS_SYNC_SEL �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00000001�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      cdma_gps_sync_sel_reg;
    struct
    {
        unsigned int  cdma_gps_sync_sel : 1;  /* bit[0]   : CDMA GPSͬ���ź�ѡ��0��ѡ��CBBP_TOP�����GPSͬ���źţ�1��ѡ��CBBP_TOP_2�����GPSͬ���źš� */
        unsigned int  reserved          : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_CDMA_GPS_SYNC_SEL_UNION;
#define BBPCOMM_CDMA_GPS_SYNC_SEL_cdma_gps_sync_sel_START  (0)
#define BBPCOMM_CDMA_GPS_SYNC_SEL_cdma_gps_sync_sel_END    (0)




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

#endif /* end of bbp_comm_interface.h */
