/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : bbp_gsdr_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-05-11 11:29:33
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��5��11��
    ��    ��   : l00165286
    �޸�����   : �ӡ�Hi6250V100 MODEM�Ĵ����ֲ�_GSDR.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "soc_interface.h"

#ifndef __BBP_GSDR_INTERFACE_H__
#define __BBP_GSDR_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/***======================================================================***
                     (1/3) register_define_gsdr_glb
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:22]  ����
 bit[21]     G��ǰ������
 bit[20]     G��ǰ�˿���
 bit[19]     G���ж�
 bit[18]     G����ʱ
 bit[17]     G��ʱ�Ӳ���
 bit[16]     ϵͳʱ����CLK���ơ��ڶԸ�ģ�����ʱ�ӿ���ʱ������Ӧbit��1��ʾ�򿪸�ģ���ʱ�ӣ���֮������Ӧbit��0��ʾ�رո�ģ���ʱ�ӡ�
             G����
 bit[15:6]   ����
 bit[5]      G��ǰ������
 bit[4]      G��ǰ�˿���
 bit[3]      G���ж�
 bit[2]      G����ʱ
 bit[1]      G��ʱ�Ӳ���
 bit[0]      ϵͳʱ����RST���ơ��ڶԸ�ģ����и�λʱ������Ӧbit��1��֮���ٽ���Ӧbit��0��
             G����
   UNION�ṹ:  GSDR_SYS_RST_CTRL_GSDR_UNION */
#define GSDR_SYS_RST_CTRL_GSDR_ADDR                   (SOC_BBP_GSDR_BASE_ADDR + 0x0)

/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20]     G��ǰ�˿���
 bit[19]     G���ж�
 bit[18]     G����ʱ
 bit[17]     G��ʱ�Ӳ���
 bit[16]     IMI��ַƬѡ��������ʹ�ܣ��ߵ�ƽ��Ч�����ź���Ч��ʾ��Ӧģ��δ��ѡ��ʱ����BBP�ڲ���ģ��IMI��ַƬѡ���ܡ�
             G����
 bit[15:5]   ����
 bit[4]      G��ǰ�˿���
 bit[3]      G���ж�
 bit[2]      G����ʱ
 bit[1]      G��ʱ�Ӳ���
 bit[0]      IMIʱ����RST���ơ��ڶԸ�ģ����и�λʱ������Ӧbit��1��֮���ٽ���Ӧbit��0��
             G����
   UNION�ṹ:  GSDR_IMI_RST_CTRL_GSDR_UNION */
#define GSDR_IMI_RST_CTRL_GSDR_ADDR                   (SOC_BBP_GSDR_BASE_ADDR + 0x4)



/***======================================================================***
                     (2/3) register_define_g_dump
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31]     ����ͨ������ģʽ��0�������������1��ǰ��AGC������
 bit[30:29]  ����
 bit[28]     ����DMA����ģʽ��0��һ��burst�������32x32bit��1��һ��burst�������16x32bit��
 bit[27:25]  ����
 bit[24]     ���а���ģʽ��0��DMA��ʽ��1��BBPMaster��ʽ��
             �̶�Ϊ1��ʹ��BBPMaster��ʽ������֧��DMA��ʽ��
 bit[23:21]  ����
 bit[20]     ����SDR IFģ�����ֹͣģʽ��0������ֹͣ���������ֹͣ���ˣ�1���ﵽcpu_dlfe_sdr_data_length����İ������������Զ�ֹͣ���ˡ�
 bit[19:17]  ����
 bit[16]     ����SDR IFģ���������ģʽ��0��������������������������ˣ�1��������������󵽴�cpu_dlfe_sdr_start_time�����ʱ���������ˡ�
 bit[15:1]   ����
 bit[0]      ����SDR IFģ��ʹ�ܣ��ߵ�ƽ��Ч��
   UNION�ṹ:  GSDR_DLFE_SDR_EN_UNION */
#define GSDR_DLFE_SDR_EN_ADDR                         (SOC_BBP_GSDR_BASE_ADDR + 0x5000)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ���а���ʱ���ſ�bypass�źţ��ߵ�ƽ��Ч����ʾʱ�ӳ�����
   UNION�ṹ:  GSDR_DLFE_SDR_CKG_BYS_UNION */
#define GSDR_DLFE_SDR_CKG_BYS_ADDR                    (SOC_BBP_GSDR_BASE_ADDR + 0x5004)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12]     ��������BBPMaster���˸�λ���塣
 bit[11:9]   ����
 bit[8]      ������������ǿ��ֹͣ���塣�ڼ�⵽�����������˳�������á�
 bit[7:5]    ����
 bit[4]      ������������ֹͣ���塣
 bit[3:1]    ����
 bit[0]      �������������������塣
   UNION�ṹ:  GSDR_DLFE_SDR_START_STOP_UNION */
#define GSDR_DLFE_SDR_START_STOP_ADDR                 (SOC_BBP_GSDR_BASE_ADDR + 0x5008)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11:0]   ����Buffer��ȣ���λ32word�����ڼ���Buffer�׵�ַ��ʱ�����
             Cģ��Uģ��ʱ��һ��word��Ӧһ��chip��Gģ��ʱ��һ��word��Ӧһ��Qb��
             Cģ/Uģ��������Ч��
   UNION�ṹ:  GSDR_DLFE_SDR_OFFSET_BUFF_DEPTH_UNION */
#define GSDR_DLFE_SDR_OFFSET_BUFF_DEPTH_ADDR          (SOC_BBP_GSDR_BASE_ADDR + 0x500C)

/* �Ĵ���˵����
 bit[31:22]  ����
 bit[21:0]   ���а�������ʱ�̡�
             CģΪc_base_cnt�ϵ�����ʱ�̣���λchip��
             bit[14:0]����Χ0~32767chip��
             bit[16:15]����Χ0~2��
             bit[21:17]����Χ0~24��
             Gģ��Ϊgtc_timebase�ϵ�����ʱ�̣���λQb��
             bit[12:0]��gtc_timebase�ϵ�֡��Qbֵ����Χ0~4999Qb��
             bit[21:13]�������塣
             Uģ��Ϊbase_cnt�ϵ�����ʱ�̣���λchip��
             bit[7:0]��symbol��chipֵ����Χ0~255chip��
             bit[11:8]��slot��symbolֵ����Χ0~9symbol��
             bit[15:12]��֡��slotֵ����Χ0~14slot��
             bit[21:16]�������塣
             �ò�������cpu_dlfe_sdr_start_modeΪ1ʱ��Ч��
             Cģ/Uģ��������Ч��
   UNION�ṹ:  GSDR_DLFE_SDR_TIME_CTRL_UNION */
#define GSDR_DLFE_SDR_TIME_CTRL_ADDR                  (SOC_BBP_GSDR_BASE_ADDR + 0x5010)

/* �Ĵ���˵����
 bit[31:12]  ����
 bit[11:0]   ���а�������������λ32word��
             �ò�������cpu_dlfe_sdr_stop_modeΪ1ʱ��Ч��
   UNION�ṹ:  GSDR_DLFE_SDR_TIME_CTRL2_UNION */
#define GSDR_DLFE_SDR_TIME_CTRL2_ADDR                 (SOC_BBP_GSDR_BASE_ADDR + 0x5014)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   ����Buffer��ȣ���λword��
             Cģ��Uģ��ʱ��һ��word��Ӧһ��chip��Gģ��ʱ��һ��word��Ӧһ��Qb��
             ������Gģ��ʱʹ�á�
             Cģ/Uģ��������Ч��
   UNION�ṹ:  GSDR_DLFE_SDR_WORD_DEPTH_UNION */
#define GSDR_DLFE_SDR_WORD_DEPTH_ADDR                 (SOC_BBP_GSDR_BASE_ADDR + 0x5018)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5:0]    ��������1��ǰ����word����
   UNION�ṹ:  GSDR_DLFE_SDR_AT1_RD_CHIP_RPT_UNION */
#define GSDR_DLFE_SDR_AT1_RD_CHIP_RPT_ADDR            (SOC_BBP_GSDR_BASE_ADDR + 0x5040)

/* �Ĵ���˵����
 bit[31:12]  ��������1��ǰ����ҳ��������cpu_dlfe_sdr_buffer_depthͳ�ơ�
 bit[11:0]   ��������1��ǰ���˿���������cpu_dlfe_sdr_buffer_depthͳ�ơ�
   UNION�ṹ:  GSDR_DLFE_SDR_AT1_RD_RPT_UNION */
#define GSDR_DLFE_SDR_AT1_RD_RPT_ADDR                 (SOC_BBP_GSDR_BASE_ADDR + 0x5044)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:0]   ��������1�������˺��һ�����ݶ�Ӧʱ�����
             Cģʱ���Ϊc_base_cnt����λchip��
             bit[14:0]��������Χ0~32767chip��ʱ�䳤��80/3ms��32768chip����
             bit[16:15]��������Χ0~2��ʱ�䳤��80ms��
             bit[21:17]��������Χ0~24��ʱ�䳤��2s��
             bit[27:22]���̶�Ϊ0��
             Gģ��ʱ���Ϊgtc_tdma_qb�ϵ�֡�ź�gtc_timebase�ϵ�Qb�š�
             bit[12:0]��gtc_timebase�ϵ�֡��Qb������������Χ0~4999Qb��
             bit[23:13]��gtc_tdma_qb�ϵ�fn_low֡������������Χ0~1325֡��
             bit[27:24]���̶�Ϊ0��
             Uģ��ʱ���Ϊbase_cnt��cfn��
             bit[7:0]��symbol��chip������������Χ0~255chip��
             bit[11:8]��slot��symbol������������Χ0~9symbol��
             bit[15:12]��֡��slot������������Χ0~14slot��
             bit[27:16]��cfn��
             Cģ/Uģ��������Ч��
   UNION�ṹ:  GSDR_DLFE_SDR_AT1_1ST_STAMP_RPT_UNION */
#define GSDR_DLFE_SDR_AT1_1ST_STAMP_RPT_ADDR          (SOC_BBP_GSDR_BASE_ADDR + 0x5050)

/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:0]   ��������1�������˺�Buffer�׵�ַ���ݶ�Ӧʱ���������ʱ϶ͷ���档
             ʱ�������ͬ�ϡ�
             Cģ1xʱ϶ͷ��PCGͷ��CģEV-DOʱ϶ͷ��ʵ��ʱ϶ͷ��Gģ��ʱ϶ͷ��gtc_tdma_qb�ϵ�burstͷ��Uģ��ʱ϶ͷ��ʵ��ʱ϶ͷ��
             Cģ/Uģ��������Ч��
   UNION�ṹ:  GSDR_DLFE_SDR_AT1_BUFFER_STAMP_RPT_UNION */
#define GSDR_DLFE_SDR_AT1_BUFFER_STAMP_RPT_ADDR       (SOC_BBP_GSDR_BASE_ADDR + 0x5058)

/* �Ĵ���˵����
   ��      ������������1�������ݡ�
               Cģ��Uģ��ʱ�ɼ�DAGC�����ݣ�һ��word��Ӧһ��chip����ʽ���¡�
               bit[7:0]��chip������0 I·��
               bit[15:8]��chip������0 Q·��
               bit[23:16]��chip������1 I·��
               bit[31:24]��chip������1 Q·��
               Gģ��ʱ�ɼ�AD�����ݣ�һ��word��Ӧһ��Qb����ʽ���¡�
               bit[15:0]��Qb I·��
               bit[31:16]��Qb Q·��
               Cģ/Uģ��������Ч��
   UNION�ṹ ���� */
#define GSDR_DLFE_SDR_AT1_DATA_ADDR                   (SOC_BBP_GSDR_BASE_ADDR + 0x5060)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4]      ��������1���˳���ָʾ��
 bit[3:1]    ����
 bit[0]      ��������1����״̬��
   UNION�ṹ:  GSDR_DLFE_SDR_AT1_DUMP_EN_RPT_UNION */
#define GSDR_DLFE_SDR_AT1_DUMP_EN_RPT_ADDR            (SOC_BBP_GSDR_BASE_ADDR + 0x5070)

/* �Ĵ���˵����
 bit[31:16]  ��������1��ǰ����ҳ��������cpu_dlfe_sdr_word_depthͳ�ơ�
             ������Gģ��ʱʹ�á�
 bit[15:0]   ��������1��ǰ��������������cpu_dlfe_sdr_word_depthͳ�ơ�
             ������Gģ��ʱʹ�á�
   UNION�ṹ:  GSDR_DLFE_SDR_AT1_RD_WORD_RPT_UNION */
#define GSDR_DLFE_SDR_AT1_RD_WORD_RPT_ADDR            (SOC_BBP_GSDR_BASE_ADDR + 0x5078)

/* �Ĵ���˵����
 bit[31:25]  ����
 bit[24]     ���а���ģʽ��0��DMA��ʽ��1��BBPMaster��ʽ��
             �������BBPMaster��ʽ��
 bit[23:17]  ����
 bit[16]     Gģ�����з��Ͷ�ʱѡ��0������gtc_timebase��1������gtc_tdma_qb��
 bit[15:13]  ����
 bit[12]     Gģ�����з���ģʽ��0������ģʽ��1������ģʽ��
 bit[11:1]   ����
 bit[0]      ����SDR IFģ��ʹ�ܣ��ߵ�ƽ��Ч��
   UNION�ṹ:  GSDR_ULFE_SDR_EN_UNION */
#define GSDR_ULFE_SDR_EN_ADDR                         (SOC_BBP_GSDR_BASE_ADDR + 0x5100)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ���а���ʱ���ſ�bypass�źţ��ߵ�ƽ��Ч����ʾʱ�ӳ�����
   UNION�ṹ:  GSDR_ULFE_SDR_CKG_UNION */
#define GSDR_ULFE_SDR_CKG_ADDR                        (SOC_BBP_GSDR_BASE_ADDR + 0x5104)

/* �Ĵ���˵����
 bit[31:6]   ����
 bit[5]      BBPMaster���˸�λ���塣
 bit[4:2]    ����
 bit[1]      ����ȡ������ֹͣ���塣
             �ò�������Gģ��ʱ��Ч��
 bit[0]      ����ȡ�������������塣
             �ò�������Gģ��ʱ��Ч��
   UNION�ṹ:  GSDR_ULFE_SDR_START_UNION */
#define GSDR_ULFE_SDR_START_ADDR                      (SOC_BBP_GSDR_BASE_ADDR + 0x5108)

/* �Ĵ���˵����
 bit[31:27]  ����
 bit[26:16]  Cģʱ����ʾ����ACHʱ϶ͷ���sys_cntʱ϶�߽��ӳ�������λchip��
             Gģ��ʱ��bit[22:16]��ʾ�������ݷ��͵�Qb��clkʱ�̣�bit[26:23]�����塣
             Cģ������Ч��
 bit[15:13]  ����
 bit[12:0]   Cģʱ����ʾ����ʱ϶ͷ���sys_cntʱ϶�߽���ǰ������λ1/4chip��
             Gģ��ʱ����ʾgtc_tdma_qb�ϵ��������ݷ���ʱ�̣���λQb����Χ0~4999��
             Cģ������Ч��
   UNION�ṹ:  GSDR_ULFE_SDR_OFFSET_UNION */
#define GSDR_ULFE_SDR_OFFSET_ADDR                     (SOC_BBP_GSDR_BASE_ADDR + 0x510C)

/* �Ĵ���˵����
 bit[31:29]  ����
 bit[28:16]  Cģʱ����ʾ������λ������ǰʱ϶ͷ��Чλ�ã���λ1/4chip��
             Gģ��ʱ��bit[27:16]��ʾ�����������һ��burst�������㣬ȡֵ��Χ0~2499��bit[28]�����塣
             Cģ������Ч��
 bit[15:13]  ����
 bit[12:0]   Cģʱ����ʾ����dbb��������ǰʱ϶ͷ��Чλ�ã���λ1/4chip��
             Gģ��ʱ��bit[11:0]��ʾ�������ݵ�һ��burst��ʼ���㣬ȡֵ��Χ0~2499��bit[12]�����塣
             Cģ������Ч��
   UNION�ṹ:  GSDR_ULFE_SDR_ACTIVE_TIME_UNION */
#define GSDR_ULFE_SDR_ACTIVE_TIME_ADDR                (SOC_BBP_GSDR_BASE_ADDR + 0x5110)

/* �Ĵ���˵����
 bit[31:3]   ����
 bit[2:0]    Gģ��ʱ���������ݰ�����burst������ȡֵ��Χ0~5������ֵ��1��ʾʵ��burst������
   UNION�ṹ:  GSDR_ULFE_SDR_G_CFG_UNION */
#define GSDR_ULFE_SDR_G_CFG_ADDR                      (SOC_BBP_GSDR_BASE_ADDR + 0x5114)

/* �Ĵ���˵����
 bit[31:9]   ����
 bit[8]      ����BBPMaster�������ָʾ��
 bit[7:5]    ����
 bit[4]      ����BBPMaster���˳���ָʾ��
 bit[3:1]    ����
 bit[0]      ���а���״̬��
   UNION�ṹ:  GSDR_ULFE_SDR_DUMP_EN_RPT_UNION */
#define GSDR_ULFE_SDR_DUMP_EN_RPT_ADDR                (SOC_BBP_GSDR_BASE_ADDR + 0x5140)

/* �Ĵ���˵����
   ��      ����Gǰ��AGC�����������ݡ�
   UNION�ṹ ���� */
#define GSDR_DUMP_DMA_RDATA_G_ADDR                    (SOC_BBP_GSDR_BASE_ADDR + 0x5240)

/* �Ĵ���˵����
   ��      ����Gǰ��AGC������ʼʱ���ϱ���
   UNION�ṹ ���� */
#define GSDR_DUMP_STAMP_G_PART1_CPU_ADDR              (SOC_BBP_GSDR_BASE_ADDR + 0x5250)

/* �Ĵ���˵����
   ��      ����Gǰ��AGC������ʼʱ���ϱ���
   UNION�ṹ ���� */
#define GSDR_DUMP_STAMP_G_PART2_CPU_ADDR              (SOC_BBP_GSDR_BASE_ADDR + 0x5254)



/***======================================================================***
                     (3/3) register_define_g_dump_mem
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:28]  ����
 bit[27:16]  Cģʱ����ʾ����ǰ������Q·��12�����з����������ÿ1/4 PCG��slotдһ�顣
             Gģ��ʱ����ʾ���з�������Q·��12�����з����������ÿ1/5 burstдһ�顣
             Cģ������Ч��
 bit[15:12]  ����
 bit[11:0]   Cģʱ����ʾ����ǰ������I·��12�����з����������ÿ1/4 PCG��slotдһ�顣
             Gģ��ʱ����ʾ���з�������I·��12�����з����������ÿ1/5 burstдһ�顣
             Cģ������Ч��
   UNION�ṹ:  GSDR_ULFE_SDR_RAM_UNION */
#define GSDR_ULFE_SDR_RAM_ADDR                        (SOC_BBP_GSDR_BASE_ADDR + 0x5800)
#define GSDR_ULFE_SDR_RAM_MEMDEPTH  (512)





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
                     (1/3) register_define_gsdr_glb
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : GSDR_SYS_RST_CTRL_GSDR_UNION
 �ṹ˵��  : SYS_RST_CTRL_GSDR �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      sys_rst_ctrl_gsdr_reg;
    struct
    {
        unsigned int  sys_rst_ctrl_gdump           : 1;  /* bit[0]    : ϵͳʱ����RST���ơ��ڶԸ�ģ����и�λʱ������Ӧbit��1��֮���ٽ���Ӧbit��0��
                                                                        G���� */
        unsigned int  sys_rst_ctrl_gsdr_gdrx_gauge : 1;  /* bit[1]    : G��ʱ�Ӳ��� */
        unsigned int  sys_rst_ctrl_gsdr_timing     : 1;  /* bit[2]    : G����ʱ */
        unsigned int  sys_rst_ctrl_gsdr_intr       : 1;  /* bit[3]    : G���ж� */
        unsigned int  sys_rst_ctrl_gsdr_fe_ctrl    : 1;  /* bit[4]    : G��ǰ�˿��� */
        unsigned int  sys_rst_ctrl_gsdr_fe_abb     : 1;  /* bit[5]    : G��ǰ������ */
        unsigned int  reserved_0                   : 10; /* bit[6-15] : ���� */
        unsigned int  sys_clk_ctrl_gdump           : 1;  /* bit[16]   : ϵͳʱ����CLK���ơ��ڶԸ�ģ�����ʱ�ӿ���ʱ������Ӧbit��1��ʾ�򿪸�ģ���ʱ�ӣ���֮������Ӧbit��0��ʾ�رո�ģ���ʱ�ӡ�
                                                                        G���� */
        unsigned int  sys_clk_ctrl_gsdr_gdrx_gauge : 1;  /* bit[17]   : G��ʱ�Ӳ��� */
        unsigned int  sys_clk_ctrl_gsdr_timing     : 1;  /* bit[18]   : G����ʱ */
        unsigned int  sys_clk_ctrl_gsdr_intr       : 1;  /* bit[19]   : G���ж� */
        unsigned int  sys_clk_ctrl_gsdr_fe_ctrl    : 1;  /* bit[20]   : G��ǰ�˿��� */
        unsigned int  sys_clk_ctrl_gsdr_fe_abb     : 1;  /* bit[21]   : G��ǰ������ */
        unsigned int  reserved_1                   : 10; /* bit[22-31]: ���� */
    } reg;
} GSDR_SYS_RST_CTRL_GSDR_UNION;
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gdump_START            (0)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gdump_END              (0)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gsdr_gdrx_gauge_START  (1)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gsdr_gdrx_gauge_END    (1)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gsdr_timing_START      (2)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gsdr_timing_END        (2)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gsdr_intr_START        (3)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gsdr_intr_END          (3)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gsdr_fe_ctrl_START     (4)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gsdr_fe_ctrl_END       (4)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gsdr_fe_abb_START      (5)
#define GSDR_SYS_RST_CTRL_GSDR_sys_rst_ctrl_gsdr_fe_abb_END        (5)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gdump_START            (16)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gdump_END              (16)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gsdr_gdrx_gauge_START  (17)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gsdr_gdrx_gauge_END    (17)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gsdr_timing_START      (18)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gsdr_timing_END        (18)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gsdr_intr_START        (19)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gsdr_intr_END          (19)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gsdr_fe_ctrl_START     (20)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gsdr_fe_ctrl_END       (20)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gsdr_fe_abb_START      (21)
#define GSDR_SYS_RST_CTRL_GSDR_sys_clk_ctrl_gsdr_fe_abb_END        (21)


/*****************************************************************************
 �ṹ��    : GSDR_IMI_RST_CTRL_GSDR_UNION
 �ṹ˵��  : IMI_RST_CTRL_GSDR �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      imi_rst_ctrl_gsdr_reg;
    struct
    {
        unsigned int  imi_rst_ctrl_gdump            : 1;  /* bit[0]    : IMIʱ����RST���ơ��ڶԸ�ģ����и�λʱ������Ӧbit��1��֮���ٽ���Ӧbit��0��
                                                                         G���� */
        unsigned int  imi_rst_ctrl_gsdr_gdrx_gauge  : 1;  /* bit[1]    : G��ʱ�Ӳ��� */
        unsigned int  imi_rst_ctrl_gsdr_timing      : 1;  /* bit[2]    : G����ʱ */
        unsigned int  imi_rst_ctrl_gsdr_intr        : 1;  /* bit[3]    : G���ж� */
        unsigned int  imi_rst_ctrl_gsdr_fe_ctrl     : 1;  /* bit[4]    : G��ǰ�˿��� */
        unsigned int  reserved_0                    : 11; /* bit[5-15] : ���� */
        unsigned int  imi_addr_ctrl_gdump           : 1;  /* bit[16]   : IMI��ַƬѡ��������ʹ�ܣ��ߵ�ƽ��Ч�����ź���Ч��ʾ��Ӧģ��δ��ѡ��ʱ����BBP�ڲ���ģ��IMI��ַƬѡ���ܡ�
                                                                         G���� */
        unsigned int  imi_addr_ctrl_gsdr_gdrx_gauge : 1;  /* bit[17]   : G��ʱ�Ӳ��� */
        unsigned int  imi_addr_ctrl_gsdr_timing     : 1;  /* bit[18]   : G����ʱ */
        unsigned int  imi_addr_ctrl_gsdr_intr       : 1;  /* bit[19]   : G���ж� */
        unsigned int  imi_addr_ctrl_gsdr_fe_ctrl    : 1;  /* bit[20]   : G��ǰ�˿��� */
        unsigned int  reserved_1                    : 11; /* bit[21-31]: ���� */
    } reg;
} GSDR_IMI_RST_CTRL_GSDR_UNION;
#define GSDR_IMI_RST_CTRL_GSDR_imi_rst_ctrl_gdump_START             (0)
#define GSDR_IMI_RST_CTRL_GSDR_imi_rst_ctrl_gdump_END               (0)
#define GSDR_IMI_RST_CTRL_GSDR_imi_rst_ctrl_gsdr_gdrx_gauge_START   (1)
#define GSDR_IMI_RST_CTRL_GSDR_imi_rst_ctrl_gsdr_gdrx_gauge_END     (1)
#define GSDR_IMI_RST_CTRL_GSDR_imi_rst_ctrl_gsdr_timing_START       (2)
#define GSDR_IMI_RST_CTRL_GSDR_imi_rst_ctrl_gsdr_timing_END         (2)
#define GSDR_IMI_RST_CTRL_GSDR_imi_rst_ctrl_gsdr_intr_START         (3)
#define GSDR_IMI_RST_CTRL_GSDR_imi_rst_ctrl_gsdr_intr_END           (3)
#define GSDR_IMI_RST_CTRL_GSDR_imi_rst_ctrl_gsdr_fe_ctrl_START      (4)
#define GSDR_IMI_RST_CTRL_GSDR_imi_rst_ctrl_gsdr_fe_ctrl_END        (4)
#define GSDR_IMI_RST_CTRL_GSDR_imi_addr_ctrl_gdump_START            (16)
#define GSDR_IMI_RST_CTRL_GSDR_imi_addr_ctrl_gdump_END              (16)
#define GSDR_IMI_RST_CTRL_GSDR_imi_addr_ctrl_gsdr_gdrx_gauge_START  (17)
#define GSDR_IMI_RST_CTRL_GSDR_imi_addr_ctrl_gsdr_gdrx_gauge_END    (17)
#define GSDR_IMI_RST_CTRL_GSDR_imi_addr_ctrl_gsdr_timing_START      (18)
#define GSDR_IMI_RST_CTRL_GSDR_imi_addr_ctrl_gsdr_timing_END        (18)
#define GSDR_IMI_RST_CTRL_GSDR_imi_addr_ctrl_gsdr_intr_START        (19)
#define GSDR_IMI_RST_CTRL_GSDR_imi_addr_ctrl_gsdr_intr_END          (19)
#define GSDR_IMI_RST_CTRL_GSDR_imi_addr_ctrl_gsdr_fe_ctrl_START     (20)
#define GSDR_IMI_RST_CTRL_GSDR_imi_addr_ctrl_gsdr_fe_ctrl_END       (20)


/***======================================================================***
                     (2/3) register_define_g_dump
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : GSDR_DLFE_SDR_EN_UNION
 �ṹ˵��  : DLFE_SDR_EN �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x01000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_en_reg;
    struct
    {
        unsigned int  cpu_dlfe_sdr_en         : 1;  /* bit[0]    : ����SDR IFģ��ʹ�ܣ��ߵ�ƽ��Ч�� */
        unsigned int  reserved_0              : 15; /* bit[1-15] : ���� */
        unsigned int  cpu_dlfe_sdr_start_mode : 1;  /* bit[16]   : ����SDR IFģ���������ģʽ��0��������������������������ˣ�1��������������󵽴�cpu_dlfe_sdr_start_time�����ʱ���������ˡ� */
        unsigned int  reserved_1              : 3;  /* bit[17-19]: ���� */
        unsigned int  cpu_dlfe_sdr_stop_mode  : 1;  /* bit[20]   : ����SDR IFģ�����ֹͣģʽ��0������ֹͣ���������ֹͣ���ˣ�1���ﵽcpu_dlfe_sdr_data_length����İ������������Զ�ֹͣ���ˡ� */
        unsigned int  reserved_2              : 3;  /* bit[21-23]: ���� */
        unsigned int  cpu_dlfe_sdr_trans_mode : 1;  /* bit[24]   : ���а���ģʽ��0��DMA��ʽ��1��BBPMaster��ʽ��
                                                                   �̶�Ϊ1��ʹ��BBPMaster��ʽ������֧��DMA��ʽ�� */
        unsigned int  reserved_3              : 3;  /* bit[25-27]: ���� */
        unsigned int  cpu_dlfe_sdr_dma_mode   : 1;  /* bit[28]   : ����DMA����ģʽ��0��һ��burst�������32x32bit��1��һ��burst�������16x32bit�� */
        unsigned int  reserved_4              : 2;  /* bit[29-30]: ���� */
        unsigned int  cpu_dlfe_g_dump_mode    : 1;  /* bit[31]   : ����ͨ������ģʽ��0�������������1��ǰ��AGC������ */
    } reg;
} GSDR_DLFE_SDR_EN_UNION;
#define GSDR_DLFE_SDR_EN_cpu_dlfe_sdr_en_START          (0)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_sdr_en_END            (0)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_sdr_start_mode_START  (16)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_sdr_start_mode_END    (16)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_sdr_stop_mode_START   (20)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_sdr_stop_mode_END     (20)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_sdr_trans_mode_START  (24)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_sdr_trans_mode_END    (24)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_sdr_dma_mode_START    (28)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_sdr_dma_mode_END      (28)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_g_dump_mode_START     (31)
#define GSDR_DLFE_SDR_EN_cpu_dlfe_g_dump_mode_END       (31)


/*****************************************************************************
 �ṹ��    : GSDR_DLFE_SDR_CKG_BYS_UNION
 �ṹ˵��  : DLFE_SDR_CKG_BYS �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_ckg_bys_reg;
    struct
    {
        unsigned int  cpu_dlfe_sdr_ckg_bypass : 1;  /* bit[0]   : ���а���ʱ���ſ�bypass�źţ��ߵ�ƽ��Ч����ʾʱ�ӳ����� */
        unsigned int  reserved                : 31; /* bit[1-31]: ���� */
    } reg;
} GSDR_DLFE_SDR_CKG_BYS_UNION;
#define GSDR_DLFE_SDR_CKG_BYS_cpu_dlfe_sdr_ckg_bypass_START  (0)
#define GSDR_DLFE_SDR_CKG_BYS_cpu_dlfe_sdr_ckg_bypass_END    (0)


/*****************************************************************************
 �ṹ��    : GSDR_DLFE_SDR_START_STOP_UNION
 �ṹ˵��  : DLFE_SDR_START_STOP �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_start_stop_reg;
    struct
    {
        unsigned int  cpu_dlfe_at1_sdr_start      : 1;  /* bit[0]    : �������������������塣 */
        unsigned int  reserved_0                  : 3;  /* bit[1-3]  : ���� */
        unsigned int  cpu_dlfe_at1_sdr_stop       : 1;  /* bit[4]    : ������������ֹͣ���塣 */
        unsigned int  reserved_1                  : 3;  /* bit[5-7]  : ���� */
        unsigned int  cpu_dlfe_at1_sdr_force_stop : 1;  /* bit[8]    : ������������ǿ��ֹͣ���塣�ڼ�⵽�����������˳�������á� */
        unsigned int  reserved_2                  : 3;  /* bit[9-11] : ���� */
        unsigned int  cpu_dlfe_at1_sdr_trans_clr  : 1;  /* bit[12]   : ��������BBPMaster���˸�λ���塣 */
        unsigned int  reserved_3                  : 19; /* bit[13-31]: ���� */
    } reg;
} GSDR_DLFE_SDR_START_STOP_UNION;
#define GSDR_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_start_START       (0)
#define GSDR_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_start_END         (0)
#define GSDR_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_stop_START        (4)
#define GSDR_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_stop_END          (4)
#define GSDR_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_force_stop_START  (8)
#define GSDR_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_force_stop_END    (8)
#define GSDR_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_trans_clr_START   (12)
#define GSDR_DLFE_SDR_START_STOP_cpu_dlfe_at1_sdr_trans_clr_END     (12)


/*****************************************************************************
 �ṹ��    : GSDR_DLFE_SDR_OFFSET_BUFF_DEPTH_UNION
 �ṹ˵��  : DLFE_SDR_OFFSET_BUFF_DEPTH �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x0000007F�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_offset_buff_depth_reg;
    struct
    {
        unsigned int  cpu_dlfe_sdr_buffer_depth : 12; /* bit[0-11] : ����Buffer��ȣ���λ32word�����ڼ���Buffer�׵�ַ��ʱ�����
                                                                     Cģ��Uģ��ʱ��һ��word��Ӧһ��chip��Gģ��ʱ��һ��word��Ӧһ��Qb��
                                                                     Cģ/Uģ��������Ч�� */
        unsigned int  reserved                  : 20; /* bit[12-31]: ���� */
    } reg;
} GSDR_DLFE_SDR_OFFSET_BUFF_DEPTH_UNION;
#define GSDR_DLFE_SDR_OFFSET_BUFF_DEPTH_cpu_dlfe_sdr_buffer_depth_START  (0)
#define GSDR_DLFE_SDR_OFFSET_BUFF_DEPTH_cpu_dlfe_sdr_buffer_depth_END    (11)


/*****************************************************************************
 �ṹ��    : GSDR_DLFE_SDR_TIME_CTRL_UNION
 �ṹ˵��  : DLFE_SDR_TIME_CTRL �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_time_ctrl_reg;
    struct
    {
        unsigned int  cpu_dlfe_sdr_start_time : 22; /* bit[0-21] : ���а�������ʱ�̡�
                                                                   CģΪc_base_cnt�ϵ�����ʱ�̣���λchip��
                                                                   bit[14:0]����Χ0~32767chip��
                                                                   bit[16:15]����Χ0~2��
                                                                   bit[21:17]����Χ0~24��
                                                                   Gģ��Ϊgtc_timebase�ϵ�����ʱ�̣���λQb��
                                                                   bit[12:0]��gtc_timebase�ϵ�֡��Qbֵ����Χ0~4999Qb��
                                                                   bit[21:13]�������塣
                                                                   Uģ��Ϊbase_cnt�ϵ�����ʱ�̣���λchip��
                                                                   bit[7:0]��symbol��chipֵ����Χ0~255chip��
                                                                   bit[11:8]��slot��symbolֵ����Χ0~9symbol��
                                                                   bit[15:12]��֡��slotֵ����Χ0~14slot��
                                                                   bit[21:16]�������塣
                                                                   �ò�������cpu_dlfe_sdr_start_modeΪ1ʱ��Ч��
                                                                   Cģ/Uģ��������Ч�� */
        unsigned int  reserved                : 10; /* bit[22-31]: ���� */
    } reg;
} GSDR_DLFE_SDR_TIME_CTRL_UNION;
#define GSDR_DLFE_SDR_TIME_CTRL_cpu_dlfe_sdr_start_time_START  (0)
#define GSDR_DLFE_SDR_TIME_CTRL_cpu_dlfe_sdr_start_time_END    (21)


/*****************************************************************************
 �ṹ��    : GSDR_DLFE_SDR_TIME_CTRL2_UNION
 �ṹ˵��  : DLFE_SDR_TIME_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_time_ctrl2_reg;
    struct
    {
        unsigned int  cpu_dlfe_sdr_data_length : 12; /* bit[0-11] : ���а�������������λ32word��
                                                                    �ò�������cpu_dlfe_sdr_stop_modeΪ1ʱ��Ч�� */
        unsigned int  reserved                 : 20; /* bit[12-31]: ���� */
    } reg;
} GSDR_DLFE_SDR_TIME_CTRL2_UNION;
#define GSDR_DLFE_SDR_TIME_CTRL2_cpu_dlfe_sdr_data_length_START  (0)
#define GSDR_DLFE_SDR_TIME_CTRL2_cpu_dlfe_sdr_data_length_END    (11)


/*****************************************************************************
 �ṹ��    : GSDR_DLFE_SDR_WORD_DEPTH_UNION
 �ṹ˵��  : DLFE_SDR_WORD_DEPTH �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_word_depth_reg;
    struct
    {
        unsigned int  cpu_dlfe_sdr_word_depth : 16; /* bit[0-15] : ����Buffer��ȣ���λword��
                                                                   Cģ��Uģ��ʱ��һ��word��Ӧһ��chip��Gģ��ʱ��һ��word��Ӧһ��Qb��
                                                                   ������Gģ��ʱʹ�á�
                                                                   Cģ/Uģ��������Ч�� */
        unsigned int  reserved                : 16; /* bit[16-31]: ���� */
    } reg;
} GSDR_DLFE_SDR_WORD_DEPTH_UNION;
#define GSDR_DLFE_SDR_WORD_DEPTH_cpu_dlfe_sdr_word_depth_START  (0)
#define GSDR_DLFE_SDR_WORD_DEPTH_cpu_dlfe_sdr_word_depth_END    (15)


/*****************************************************************************
 �ṹ��    : GSDR_DLFE_SDR_AT1_RD_CHIP_RPT_UNION
 �ṹ˵��  : DLFE_SDR_AT1_RD_CHIP_RPT �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_at1_rd_chip_rpt_reg;
    struct
    {
        unsigned int  dlfe_sdr_at1_rd_chip_cnt_cpu : 6;  /* bit[0-5] : ��������1��ǰ����word���� */
        unsigned int  reserved                     : 26; /* bit[6-31]: ���� */
    } reg;
} GSDR_DLFE_SDR_AT1_RD_CHIP_RPT_UNION;
#define GSDR_DLFE_SDR_AT1_RD_CHIP_RPT_dlfe_sdr_at1_rd_chip_cnt_cpu_START  (0)
#define GSDR_DLFE_SDR_AT1_RD_CHIP_RPT_dlfe_sdr_at1_rd_chip_cnt_cpu_END    (5)


/*****************************************************************************
 �ṹ��    : GSDR_DLFE_SDR_AT1_RD_RPT_UNION
 �ṹ˵��  : DLFE_SDR_AT1_RD_RPT �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_at1_rd_rpt_reg;
    struct
    {
        unsigned int  dlfe_sdr_at1_rd_block_cnt_cpu : 12; /* bit[0-11] : ��������1��ǰ���˿���������cpu_dlfe_sdr_buffer_depthͳ�ơ� */
        unsigned int  dlfe_sdr_at1_rd_page_cnt_cpu  : 20; /* bit[12-31]: ��������1��ǰ����ҳ��������cpu_dlfe_sdr_buffer_depthͳ�ơ� */
    } reg;
} GSDR_DLFE_SDR_AT1_RD_RPT_UNION;
#define GSDR_DLFE_SDR_AT1_RD_RPT_dlfe_sdr_at1_rd_block_cnt_cpu_START  (0)
#define GSDR_DLFE_SDR_AT1_RD_RPT_dlfe_sdr_at1_rd_block_cnt_cpu_END    (11)
#define GSDR_DLFE_SDR_AT1_RD_RPT_dlfe_sdr_at1_rd_page_cnt_cpu_START   (12)
#define GSDR_DLFE_SDR_AT1_RD_RPT_dlfe_sdr_at1_rd_page_cnt_cpu_END     (31)


/*****************************************************************************
 �ṹ��    : GSDR_DLFE_SDR_AT1_1ST_STAMP_RPT_UNION
 �ṹ˵��  : DLFE_SDR_AT1_1ST_STAMP_RPT �Ĵ����ṹ���塣��ַƫ����:0x050����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_at1_1st_stamp_rpt_reg;
    struct
    {
        unsigned int  dlfe_sdr_at1_1st_stamp_cpu : 28; /* bit[0-27] : ��������1�������˺��һ�����ݶ�Ӧʱ�����
                                                                      Cģʱ���Ϊc_base_cnt����λchip��
                                                                      bit[14:0]��������Χ0~32767chip��ʱ�䳤��80/3ms��32768chip����
                                                                      bit[16:15]��������Χ0~2��ʱ�䳤��80ms��
                                                                      bit[21:17]��������Χ0~24��ʱ�䳤��2s��
                                                                      bit[27:22]���̶�Ϊ0��
                                                                      Gģ��ʱ���Ϊgtc_tdma_qb�ϵ�֡�ź�gtc_timebase�ϵ�Qb�š�
                                                                      bit[12:0]��gtc_timebase�ϵ�֡��Qb������������Χ0~4999Qb��
                                                                      bit[23:13]��gtc_tdma_qb�ϵ�fn_low֡������������Χ0~1325֡��
                                                                      bit[27:24]���̶�Ϊ0��
                                                                      Uģ��ʱ���Ϊbase_cnt��cfn��
                                                                      bit[7:0]��symbol��chip������������Χ0~255chip��
                                                                      bit[11:8]��slot��symbol������������Χ0~9symbol��
                                                                      bit[15:12]��֡��slot������������Χ0~14slot��
                                                                      bit[27:16]��cfn��
                                                                      Cģ/Uģ��������Ч�� */
        unsigned int  reserved                   : 4;  /* bit[28-31]: ���� */
    } reg;
} GSDR_DLFE_SDR_AT1_1ST_STAMP_RPT_UNION;
#define GSDR_DLFE_SDR_AT1_1ST_STAMP_RPT_dlfe_sdr_at1_1st_stamp_cpu_START  (0)
#define GSDR_DLFE_SDR_AT1_1ST_STAMP_RPT_dlfe_sdr_at1_1st_stamp_cpu_END    (27)


/*****************************************************************************
 �ṹ��    : GSDR_DLFE_SDR_AT1_BUFFER_STAMP_RPT_UNION
 �ṹ˵��  : DLFE_SDR_AT1_BUFFER_STAMP_RPT �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_at1_buffer_stamp_rpt_reg;
    struct
    {
        unsigned int  dlfe_sdr_at1_bufferhead_stamp_cpu : 28; /* bit[0-27] : ��������1�������˺�Buffer�׵�ַ���ݶ�Ӧʱ���������ʱ϶ͷ���档
                                                                             ʱ�������ͬ�ϡ�
                                                                             Cģ1xʱ϶ͷ��PCGͷ��CģEV-DOʱ϶ͷ��ʵ��ʱ϶ͷ��Gģ��ʱ϶ͷ��gtc_tdma_qb�ϵ�burstͷ��Uģ��ʱ϶ͷ��ʵ��ʱ϶ͷ��
                                                                             Cģ/Uģ��������Ч�� */
        unsigned int  reserved                          : 4;  /* bit[28-31]: ���� */
    } reg;
} GSDR_DLFE_SDR_AT1_BUFFER_STAMP_RPT_UNION;
#define GSDR_DLFE_SDR_AT1_BUFFER_STAMP_RPT_dlfe_sdr_at1_bufferhead_stamp_cpu_START  (0)
#define GSDR_DLFE_SDR_AT1_BUFFER_STAMP_RPT_dlfe_sdr_at1_bufferhead_stamp_cpu_END    (27)


/*****************************************************************************
 �ṹ��    : GSDR_DLFE_SDR_AT1_DUMP_EN_RPT_UNION
 �ṹ˵��  : DLFE_SDR_AT1_DUMP_EN_RPT �Ĵ����ṹ���塣��ַƫ����:0x070����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_at1_dump_en_rpt_reg;
    struct
    {
        unsigned int  dlfe_sdr_at1_dump_en : 1;  /* bit[0]   : ��������1����״̬�� */
        unsigned int  reserved_0           : 3;  /* bit[1-3] : ���� */
        unsigned int  dlfe_sdr_at1_err_sta : 1;  /* bit[4]   : ��������1���˳���ָʾ�� */
        unsigned int  reserved_1           : 27; /* bit[5-31]: ���� */
    } reg;
} GSDR_DLFE_SDR_AT1_DUMP_EN_RPT_UNION;
#define GSDR_DLFE_SDR_AT1_DUMP_EN_RPT_dlfe_sdr_at1_dump_en_START  (0)
#define GSDR_DLFE_SDR_AT1_DUMP_EN_RPT_dlfe_sdr_at1_dump_en_END    (0)
#define GSDR_DLFE_SDR_AT1_DUMP_EN_RPT_dlfe_sdr_at1_err_sta_START  (4)
#define GSDR_DLFE_SDR_AT1_DUMP_EN_RPT_dlfe_sdr_at1_err_sta_END    (4)


/*****************************************************************************
 �ṹ��    : GSDR_DLFE_SDR_AT1_RD_WORD_RPT_UNION
 �ṹ˵��  : DLFE_SDR_AT1_RD_WORD_RPT �Ĵ����ṹ���塣��ַƫ����:0x078����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      dlfe_sdr_at1_rd_word_rpt_reg;
    struct
    {
        unsigned int  dlfe_sdr_at1_rd_word_cnt_cpu : 16; /* bit[0-15] : ��������1��ǰ��������������cpu_dlfe_sdr_word_depthͳ�ơ�
                                                                        ������Gģ��ʱʹ�á� */
        unsigned int  dlfe_sdr_at1_rd_seg_cnt_cpu  : 16; /* bit[16-31]: ��������1��ǰ����ҳ��������cpu_dlfe_sdr_word_depthͳ�ơ�
                                                                        ������Gģ��ʱʹ�á� */
    } reg;
} GSDR_DLFE_SDR_AT1_RD_WORD_RPT_UNION;
#define GSDR_DLFE_SDR_AT1_RD_WORD_RPT_dlfe_sdr_at1_rd_word_cnt_cpu_START  (0)
#define GSDR_DLFE_SDR_AT1_RD_WORD_RPT_dlfe_sdr_at1_rd_word_cnt_cpu_END    (15)
#define GSDR_DLFE_SDR_AT1_RD_WORD_RPT_dlfe_sdr_at1_rd_seg_cnt_cpu_START   (16)
#define GSDR_DLFE_SDR_AT1_RD_WORD_RPT_dlfe_sdr_at1_rd_seg_cnt_cpu_END     (31)


/*****************************************************************************
 �ṹ��    : GSDR_ULFE_SDR_EN_UNION
 �ṹ˵��  : ULFE_SDR_EN �Ĵ����ṹ���塣��ַƫ����:0x100����ֵ:0x01000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      ulfe_sdr_en_reg;
    struct
    {
        unsigned int  cpu_ulfe_sdr_en            : 1;  /* bit[0]    : ����SDR IFģ��ʹ�ܣ��ߵ�ƽ��Ч�� */
        unsigned int  reserved_0                 : 11; /* bit[1-11] : ���� */
        unsigned int  cpu_ulfe_sdr_g_mode        : 1;  /* bit[12]   : Gģ�����з���ģʽ��0������ģʽ��1������ģʽ�� */
        unsigned int  reserved_1                 : 3;  /* bit[13-15]: ���� */
        unsigned int  cpu_ulfe_sdr_g_timing_mode : 1;  /* bit[16]   : Gģ�����з��Ͷ�ʱѡ��0������gtc_timebase��1������gtc_tdma_qb�� */
        unsigned int  reserved_2                 : 7;  /* bit[17-23]: ���� */
        unsigned int  cpu_ulfe_sdr_trans_mode    : 1;  /* bit[24]   : ���а���ģʽ��0��DMA��ʽ��1��BBPMaster��ʽ��
                                                                      �������BBPMaster��ʽ�� */
        unsigned int  reserved_3                 : 7;  /* bit[25-31]: ���� */
    } reg;
} GSDR_ULFE_SDR_EN_UNION;
#define GSDR_ULFE_SDR_EN_cpu_ulfe_sdr_en_START             (0)
#define GSDR_ULFE_SDR_EN_cpu_ulfe_sdr_en_END               (0)
#define GSDR_ULFE_SDR_EN_cpu_ulfe_sdr_g_mode_START         (12)
#define GSDR_ULFE_SDR_EN_cpu_ulfe_sdr_g_mode_END           (12)
#define GSDR_ULFE_SDR_EN_cpu_ulfe_sdr_g_timing_mode_START  (16)
#define GSDR_ULFE_SDR_EN_cpu_ulfe_sdr_g_timing_mode_END    (16)
#define GSDR_ULFE_SDR_EN_cpu_ulfe_sdr_trans_mode_START     (24)
#define GSDR_ULFE_SDR_EN_cpu_ulfe_sdr_trans_mode_END       (24)


/*****************************************************************************
 �ṹ��    : GSDR_ULFE_SDR_CKG_UNION
 �ṹ˵��  : ULFE_SDR_CKG �Ĵ����ṹ���塣��ַƫ����:0x104����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      ulfe_sdr_ckg_reg;
    struct
    {
        unsigned int  cpu_ulfe_sdr_ckg_bypass : 1;  /* bit[0]   : ���а���ʱ���ſ�bypass�źţ��ߵ�ƽ��Ч����ʾʱ�ӳ����� */
        unsigned int  reserved                : 31; /* bit[1-31]: ���� */
    } reg;
} GSDR_ULFE_SDR_CKG_UNION;
#define GSDR_ULFE_SDR_CKG_cpu_ulfe_sdr_ckg_bypass_START  (0)
#define GSDR_ULFE_SDR_CKG_cpu_ulfe_sdr_ckg_bypass_END    (0)


/*****************************************************************************
 �ṹ��    : GSDR_ULFE_SDR_START_UNION
 �ṹ˵��  : ULFE_SDR_START �Ĵ����ṹ���塣��ַƫ����:0x108����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      ulfe_sdr_start_reg;
    struct
    {
        unsigned int  cpu_ulfe_sdr_g_start   : 1;  /* bit[0]   : ����ȡ�������������塣
                                                                 �ò�������Gģ��ʱ��Ч�� */
        unsigned int  cpu_ulfe_sdr_g_stop    : 1;  /* bit[1]   : ����ȡ������ֹͣ���塣
                                                                 �ò�������Gģ��ʱ��Ч�� */
        unsigned int  reserved_0             : 3;  /* bit[2-4] : ���� */
        unsigned int  cpu_ulfe_sdr_trans_clr : 1;  /* bit[5]   : BBPMaster���˸�λ���塣 */
        unsigned int  reserved_1             : 26; /* bit[6-31]: ���� */
    } reg;
} GSDR_ULFE_SDR_START_UNION;
#define GSDR_ULFE_SDR_START_cpu_ulfe_sdr_g_start_START    (0)
#define GSDR_ULFE_SDR_START_cpu_ulfe_sdr_g_start_END      (0)
#define GSDR_ULFE_SDR_START_cpu_ulfe_sdr_g_stop_START     (1)
#define GSDR_ULFE_SDR_START_cpu_ulfe_sdr_g_stop_END       (1)
#define GSDR_ULFE_SDR_START_cpu_ulfe_sdr_trans_clr_START  (5)
#define GSDR_ULFE_SDR_START_cpu_ulfe_sdr_trans_clr_END    (5)


/*****************************************************************************
 �ṹ��    : GSDR_ULFE_SDR_OFFSET_UNION
 �ṹ˵��  : ULFE_SDR_OFFSET �Ĵ����ṹ���塣��ַƫ����:0x10C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      ulfe_sdr_offset_reg;
    struct
    {
        unsigned int  cpu_ulfe_slot_offset : 13; /* bit[0-12] : Cģʱ����ʾ����ʱ϶ͷ���sys_cntʱ϶�߽���ǰ������λ1/4chip��
                                                                Gģ��ʱ����ʾgtc_tdma_qb�ϵ��������ݷ���ʱ�̣���λQb����Χ0~4999��
                                                                Cģ������Ч�� */
        unsigned int  reserved_0           : 3;  /* bit[13-15]: ���� */
        unsigned int  cpu_ulfe_ach_offset  : 11; /* bit[16-26]: Cģʱ����ʾ����ACHʱ϶ͷ���sys_cntʱ϶�߽��ӳ�������λchip��
                                                                Gģ��ʱ��bit[22:16]��ʾ�������ݷ��͵�Qb��clkʱ�̣�bit[26:23]�����塣
                                                                Cģ������Ч�� */
        unsigned int  reserved_1           : 5;  /* bit[27-31]: ���� */
    } reg;
} GSDR_ULFE_SDR_OFFSET_UNION;
#define GSDR_ULFE_SDR_OFFSET_cpu_ulfe_slot_offset_START  (0)
#define GSDR_ULFE_SDR_OFFSET_cpu_ulfe_slot_offset_END    (12)
#define GSDR_ULFE_SDR_OFFSET_cpu_ulfe_ach_offset_START   (16)
#define GSDR_ULFE_SDR_OFFSET_cpu_ulfe_ach_offset_END     (26)


/*****************************************************************************
 �ṹ��    : GSDR_ULFE_SDR_ACTIVE_TIME_UNION
 �ṹ˵��  : ULFE_SDR_ACTIVE_TIME �Ĵ����ṹ���塣��ַƫ����:0x110����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      ulfe_sdr_active_time_reg;
    struct
    {
        unsigned int  cpu_ulfe_dbb_active_time        : 13; /* bit[0-12] : Cģʱ����ʾ����dbb��������ǰʱ϶ͷ��Чλ�ã���λ1/4chip��
                                                                           Gģ��ʱ��bit[11:0]��ʾ�������ݵ�һ��burst��ʼ���㣬ȡֵ��Χ0~2499��bit[12]�����塣
                                                                           Cģ������Ч�� */
        unsigned int  reserved_0                      : 3;  /* bit[13-15]: ���� */
        unsigned int  cpu_ulfe_phase_comp_active_time : 13; /* bit[16-28]: Cģʱ����ʾ������λ������ǰʱ϶ͷ��Чλ�ã���λ1/4chip��
                                                                           Gģ��ʱ��bit[27:16]��ʾ�����������һ��burst�������㣬ȡֵ��Χ0~2499��bit[28]�����塣
                                                                           Cģ������Ч�� */
        unsigned int  reserved_1                      : 3;  /* bit[29-31]: ���� */
    } reg;
} GSDR_ULFE_SDR_ACTIVE_TIME_UNION;
#define GSDR_ULFE_SDR_ACTIVE_TIME_cpu_ulfe_dbb_active_time_START         (0)
#define GSDR_ULFE_SDR_ACTIVE_TIME_cpu_ulfe_dbb_active_time_END           (12)
#define GSDR_ULFE_SDR_ACTIVE_TIME_cpu_ulfe_phase_comp_active_time_START  (16)
#define GSDR_ULFE_SDR_ACTIVE_TIME_cpu_ulfe_phase_comp_active_time_END    (28)


/*****************************************************************************
 �ṹ��    : GSDR_ULFE_SDR_G_CFG_UNION
 �ṹ˵��  : ULFE_SDR_G_CFG �Ĵ����ṹ���塣��ַƫ����:0x114����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      ulfe_sdr_g_cfg_reg;
    struct
    {
        unsigned int  cpu_ulfe_sdr_g_burst_num : 3;  /* bit[0-2] : Gģ��ʱ���������ݰ�����burst������ȡֵ��Χ0~5������ֵ��1��ʾʵ��burst������ */
        unsigned int  reserved                 : 29; /* bit[3-31]: ���� */
    } reg;
} GSDR_ULFE_SDR_G_CFG_UNION;
#define GSDR_ULFE_SDR_G_CFG_cpu_ulfe_sdr_g_burst_num_START  (0)
#define GSDR_ULFE_SDR_G_CFG_cpu_ulfe_sdr_g_burst_num_END    (2)


/*****************************************************************************
 �ṹ��    : GSDR_ULFE_SDR_DUMP_EN_RPT_UNION
 �ṹ˵��  : ULFE_SDR_DUMP_EN_RPT �Ĵ����ṹ���塣��ַƫ����:0x140����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      ulfe_sdr_dump_en_rpt_reg;
    struct
    {
        unsigned int  ulfe_sdr_dump_en   : 1;  /* bit[0]   : ���а���״̬�� */
        unsigned int  reserved_0         : 3;  /* bit[1-3] : ���� */
        unsigned int  ulfe_sdr_err_sta   : 1;  /* bit[4]   : ����BBPMaster���˳���ָʾ�� */
        unsigned int  reserved_1         : 3;  /* bit[5-7] : ���� */
        unsigned int  ulfe_sdr_trans_sta : 1;  /* bit[8]   : ����BBPMaster�������ָʾ�� */
        unsigned int  reserved_2         : 23; /* bit[9-31]: ���� */
    } reg;
} GSDR_ULFE_SDR_DUMP_EN_RPT_UNION;
#define GSDR_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_dump_en_START    (0)
#define GSDR_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_dump_en_END      (0)
#define GSDR_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_err_sta_START    (4)
#define GSDR_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_err_sta_END      (4)
#define GSDR_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_trans_sta_START  (8)
#define GSDR_ULFE_SDR_DUMP_EN_RPT_ulfe_sdr_trans_sta_END    (8)


/***======================================================================***
                     (3/3) register_define_g_dump_mem
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : GSDR_ULFE_SDR_RAM_UNION
 �ṹ˵��  : ULFE_SDR_RAM �Ĵ����ṹ���塣��ַƫ����:0x800����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      ulfe_sdr_ram_reg;
    struct
    {
        unsigned int  ulfe_sdr_data_i : 12; /* bit[0-11] : Cģʱ����ʾ����ǰ������I·��12�����з����������ÿ1/4 PCG��slotдһ�顣
                                                           Gģ��ʱ����ʾ���з�������I·��12�����з����������ÿ1/5 burstдһ�顣
                                                           Cģ������Ч�� */
        unsigned int  reserved_0      : 4;  /* bit[12-15]: ���� */
        unsigned int  ulfe_sdr_data_q : 12; /* bit[16-27]: Cģʱ����ʾ����ǰ������Q·��12�����з����������ÿ1/4 PCG��slotдһ�顣
                                                           Gģ��ʱ����ʾ���з�������Q·��12�����з����������ÿ1/5 burstдһ�顣
                                                           Cģ������Ч�� */
        unsigned int  reserved_1      : 4;  /* bit[28-31]: ���� */
    } reg;
} GSDR_ULFE_SDR_RAM_UNION;
#define GSDR_ULFE_SDR_RAM_ulfe_sdr_data_i_START  (0)
#define GSDR_ULFE_SDR_RAM_ulfe_sdr_data_i_END    (11)
#define GSDR_ULFE_SDR_RAM_ulfe_sdr_data_q_START  (16)
#define GSDR_ULFE_SDR_RAM_ulfe_sdr_data_q_END    (27)




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

#endif /* end of bbp_gsdr_interface.h */
