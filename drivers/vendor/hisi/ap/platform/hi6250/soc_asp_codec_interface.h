/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_asp_codec_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-07-15 15:53:00
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��7��15��
    ��    ��   : s00249479
    �޸�����   : �ӡ�Hi6250V100 SOC�Ĵ����ֲ�_ASP_CODEC.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_ASP_CODEC_INTERFACE_H__
#define __SOC_ASP_CODEC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) SoC CODEC
 ****************************************************************************/
/* �Ĵ���˵�����߼���·��λ�����Ĵ����⣬��λ���й����߼���CRG���Ĵ������⡣
   λ����UNION�ṹ:  SOC_ASP_CODEC_SW_RST_N_UNION */
#define SOC_ASP_CODEC_SW_RST_N_ADDR(base)             ((base) + (0x00))

/* �Ĵ���˵����APB IF/DMIC IF/SIF/I2S�ӿ����ģ��ʱ��ʹ������
   λ����UNION�ṹ:  SOC_ASP_CODEC_IF_CLK_EN_CFG_UNION */
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_ADDR(base)        ((base) + (0x04))

/* �Ĵ���˵���������˲���ͨ�����ģ��ʱ��ʹ�����ã�����DACL/DACR/ ADCL/ADCRͨ��
   λ����UNION�ṹ:  SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_UNION */
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_ADDR(base) ((base) + (0x08))

/* �Ĵ���˵��������������
   λ����UNION�ṹ:  SOC_ASP_CODEC_FS_CFG_UNION */
#define SOC_ASP_CODEC_FS_CFG_ADDR(base)               ((base) + (0x0C))

/* �Ĵ���˵����S1/S2�ӿ����üĴ���
   λ����UNION�ṹ:  SOC_ASP_CODEC_I2S_CFG_UNION */
#define SOC_ASP_CODEC_I2S_CFG_ADDR(base)              ((base) + (0x10))

/* �Ĵ���˵����DAC/ADCͨ���ڲ�MIXER��ģ��BYPASSģʽ���üĴ�����
   λ����UNION�ṹ:  SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_UNION */
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_ADDR(base) ((base) + (0x14))

/* �Ĵ���˵����MUX_TOP�����ģ�����ü�״̬
   λ����UNION�ṹ:  SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_UNION */
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_ADDR(base)   ((base) + (0x18))

/* �Ĵ���˵����ADCͨ��PGAģ������
   λ����UNION�ṹ:  SOC_ASP_CODEC_ADC_PGA_CFG_UNION */
#define SOC_ASP_CODEC_ADC_PGA_CFG_ADDR(base)          ((base) + (0x1C))

/* �Ĵ���˵����S1�ӿ�����ͨ��PGA����
   λ����UNION�ṹ:  SOC_ASP_CODEC_S1_INPUT_PGA_CFG_UNION */
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_ADDR(base)     ((base) + (0x20))

/* �Ĵ���˵����S2�ӿ�����ͨ��PGA����
   λ����UNION�ṹ:  SOC_ASP_CODEC_S2_INPUT_PGA_CFG_UNION */
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_ADDR(base)     ((base) + (0x24))

/* �Ĵ���˵����STEREO����ͨ��PGA����
   λ����UNION�ṹ:  SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_UNION */
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_ADDR(base) ((base) + (0x28))

/* �Ĵ���˵����VOICE����ͨ��PGA��SIDETONE PGA����
   λ����UNION�ṹ:  SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_UNION */
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_ADDR(base) ((base) + (0x2C))

/* �Ĵ���˵����APB IF��AFIFO���ü�״̬�ź�
   λ����UNION�ṹ:  SOC_ASP_CODEC_APB_AFIFO_CFG_1_UNION */
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_ADDR(base)      ((base) + (0x30))

/* �Ĵ���˵����APB IF��AFIFO���ü�״̬�ź�
   λ����UNION�ṹ:  SOC_ASP_CODEC_APB_AFIFO_CFG_2_UNION */
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_ADDR(base)      ((base) + (0x34))

/* �Ĵ���˵����STEREO����ͨ��AFIFO ����ˮ������
   λ����UNION�ṹ:  SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_UNION */
#define SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_ADDR(base) ((base) + (0x38))

/* �Ĵ���˵����STEREO����ͨ��AFIFO ����ˮ������
   λ����UNION�ṹ:  SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_UNION */
#define SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_ADDR(base) ((base) + (0x3C))

/* �Ĵ���˵����VOICE����ͨ��AFIFO ����ˮ������
   λ����UNION�ṹ:  SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_UNION */
#define SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_ADDR(base) ((base) + (0x40))

/* �Ĵ���˵�����ж����μĴ���
   λ����UNION�ṹ:  SOC_ASP_CODEC_CODEC_IRQ_MASK_UNION */
#define SOC_ASP_CODEC_CODEC_IRQ_MASK_ADDR(base)       ((base) + (0x44))

/* �Ĵ���˵�����ж�״̬�Ĵ���
   λ����UNION�ṹ:  SOC_ASP_CODEC_CODEC_IRQ_UNION */
#define SOC_ASP_CODEC_CODEC_IRQ_ADDR(base)            ((base) + (0x48))

/* �Ĵ���˵����DACL AGC (�Զ��������)���üĴ���1��
   λ����UNION�ṹ:  SOC_ASP_CODEC_DACL_AGC_CFG_1_UNION */
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_ADDR(base)       ((base) + (0x4C))

/* �Ĵ���˵����DACL AGC (�Զ��������)���üĴ���2��
   λ����UNION�ṹ:  SOC_ASP_CODEC_DACL_AGC_CFG_2_UNION */
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_ADDR(base)       ((base) + (0x50))

/* �Ĵ���˵����DACR AGC (�Զ��������)���üĴ���1��
   λ����UNION�ṹ:  SOC_ASP_CODEC_DACR_AGC_CFG_1_UNION */
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_ADDR(base)       ((base) + (0x54))

/* �Ĵ���˵����DACR AGC (�Զ��������)���üĴ���2��
   λ����UNION�ṹ:  SOC_ASP_CODEC_DACR_AGC_CFG_2_UNION */
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_ADDR(base)       ((base) + (0x58))

/* �Ĵ���˵����DMIC�ӿں�Serial�ӿ�����
   λ����UNION�ṹ:  SOC_ASP_CODEC_DMIC_SIF_CFG_UNION */
#define SOC_ASP_CODEC_DMIC_SIF_CFG_ADDR(base)         ((base) + (0x5C))

/* �Ĵ���˵����Misc Config
   λ����UNION�ṹ:  SOC_ASP_CODEC_MISC_CFG_UNION */
#define SOC_ASP_CODEC_MISC_CFG_ADDR(base)             ((base) + (0x60))

/* �Ĵ���˵����S2�ӿ�SRCģ������
   λ����UNION�ṹ:  SOC_ASP_CODEC_S2_SRC_CFG_UNION */
#define SOC_ASP_CODEC_S2_SRC_CFG_ADDR(base)           ((base) + (0x64))

/* �Ĵ���˵����memory�����ź�
   λ����UNION�ṹ:  SOC_ASP_CODEC_MEM_CFG_UNION */
#define SOC_ASP_CODEC_MEM_CFG_ADDR(base)              ((base) + (0x68))

/* �Ĵ���˵����������modem��I2S
   λ����UNION�ṹ:  SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_UNION */
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_ADDR(base)  ((base) + (0x6C))

/* �Ĵ���˵����������Modem����ͨ��AFIFOˮ��
   λ����UNION�ṹ:  SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_UNION */
#define SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_ADDR(base)  ((base) + (0x70))

/* �Ĵ���˵����S3�ӿڿ�Ƶƫģ��TX���������
   λ����UNION�ṹ:  SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_INC_CNT_UNION */
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_INC_CNT_ADDR(base) ((base) + (0x74))

/* �Ĵ���˵����S3�ӿڿ�Ƶƫģ��TX���������
   λ����UNION�ṹ:  SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_DEC_CNT_UNION */
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_DEC_CNT_ADDR(base) ((base) + (0x78))

/* �Ĵ���˵����S3�ӿڿ�Ƶƫģ��RX���������
   λ����UNION�ṹ:  SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_INC_CNT_UNION */
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_INC_CNT_ADDR(base) ((base) + (0x7C))

/* �Ĵ���˵����S3�ӿڿ�Ƶƫģ��RX���������
   λ����UNION�ṹ:  SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_DEC_CNT_UNION */
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_DEC_CNT_ADDR(base) ((base) + (0x80))

/* �Ĵ���˵������Ƶƫģ��ʹ��ʹ��
   λ����UNION�ṹ:  SOC_ASP_CODEC_ANTI_FREQ_JITTER_EN_UNION */
#define SOC_ASP_CODEC_ANTI_FREQ_JITTER_EN_ADDR(base)  ((base) + (0x84))

/* �Ĵ���˵����12.288Mʱ����Դѡ��
   λ����UNION�ṹ:  SOC_ASP_CODEC_CLK_SEL_UNION */
#define SOC_ASP_CODEC_CLK_SEL_ADDR(base)              ((base) + (0x88))

/* �Ĵ���˵��������ͨ·������ͨ·����ѡ��
   λ����UNION�ṹ:  SOC_ASP_CODEC_UPLINK_TEST_SEL_UNION */
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_ADDR(base)      ((base) + (0x8C))

/* �Ĵ���˵����������Modem����ͨ��
   λ����UNION�ṹ:  SOC_ASP_CODEC_THIRDMD_DLINK_CHANNEL_UNION */
#define SOC_ASP_CODEC_THIRDMD_DLINK_CHANNEL_ADDR(base) ((base) + (0xE8))

/* �Ĵ���˵����������Modem����ͨ��
   λ����UNION�ṹ:  SOC_ASP_CODEC_THIRDMD_UPLINK_CHANNEL_UNION */
#define SOC_ASP_CODEC_THIRDMD_UPLINK_CHANNEL_ADDR(base) ((base) + (0xEC))

/* �Ĵ���˵����VOICE����ͨ��
   λ����UNION�ṹ:  SOC_ASP_CODEC_VOICE_DLINK_CHANNEL_UNION */
#define SOC_ASP_CODEC_VOICE_DLINK_CHANNEL_ADDR(base)  ((base) + (0xF0))

/* �Ĵ���˵������Ƶ����ͨ��
   λ����UNION�ṹ:  SOC_ASP_CODEC_STEREO_DLINK_CHANNEL_UNION */
#define SOC_ASP_CODEC_STEREO_DLINK_CHANNEL_ADDR(base) ((base) + (0xF4))

/* �Ĵ���˵������Ƶ����ͨ��
   λ����UNION�ṹ:  SOC_ASP_CODEC_STEREO_UPLINK_CHANNEL_UNION */
#define SOC_ASP_CODEC_STEREO_UPLINK_CHANNEL_ADDR(base) ((base) + (0xF8))

/* �Ĵ���˵����VOICE����ͨ��
   λ����UNION�ṹ:  SOC_ASP_CODEC_VOICE_UPLINK_CHANNEL_UNION */
#define SOC_ASP_CODEC_VOICE_UPLINK_CHANNEL_ADDR(base) ((base) + (0xFC))





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
                     (1/1) SoC CODEC
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_SW_RST_N_UNION
 �ṹ˵��  : SW_RST_N �Ĵ����ṹ���塣��ַƫ����:0x00����ֵ:0x00000201�����:32
 �Ĵ���˵��: �߼���·��λ�����Ĵ����⣬��λ���й����߼���CRG���Ĵ������⡣
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sw_rst_n  : 1;  /* bit[0]    : �����λCODEC�ڲ����й����߼���
                                                     0����λ��Ч��
                                                     1������������ */
        unsigned int  dig_ro_00 : 7;  /* bit[1-7]  : [7:3]:reserved RO Registers
                                                     [1]: ������Modem����ʱ��TX����Ŀ�Ƶƫ�������ж�״̬����������Ϊ0�ͻᷢ�ж�
                                                     [0]: ������Modem����ʱ��RX����Ŀ�Ƶƫ�������ж�״̬����������Ϊ0�ͻᷢ�ж� */
        unsigned int  version   : 8;  /* bit[8-15] : �汾�Ĵ��� */
        unsigned int  dig_rw_00 : 16; /* bit[16-31]: [31]: ������Modem����ʱ��RX����Ŀ�Ƶƫ�������ж�ʹ��
                                                     [30]: ������Modem����ʱ��TX����Ŀ�Ƶƫ�������ж�ʹ��
                                                     [29:28]: stereo_uplink_wordlength
                                                     [27:26]: thirdmd_uplink_wordlength
                                                     [25:24]: voice_uplink_wordlength
                                                     [23:22]: reserved
                                                     [21:20]: stereo_dlink_wordlength
                                                     [19:18]: thirdmd_dlink_wordlength
                                                     [17:16]: voice_dlink_wordlength
                                                     ͨ������λ������:
                                                     2'b00: 16bit 
                                                     2'b01: 18bit
                                                     2'b10: 20bit 
                                                     2'b11: 24bit */
    } reg;
} SOC_ASP_CODEC_SW_RST_N_UNION;
#endif
#define SOC_ASP_CODEC_SW_RST_N_sw_rst_n_START   (0)
#define SOC_ASP_CODEC_SW_RST_N_sw_rst_n_END     (0)
#define SOC_ASP_CODEC_SW_RST_N_dig_ro_00_START  (1)
#define SOC_ASP_CODEC_SW_RST_N_dig_ro_00_END    (7)
#define SOC_ASP_CODEC_SW_RST_N_version_START    (8)
#define SOC_ASP_CODEC_SW_RST_N_version_END      (15)
#define SOC_ASP_CODEC_SW_RST_N_dig_rw_00_START  (16)
#define SOC_ASP_CODEC_SW_RST_N_dig_rw_00_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_IF_CLK_EN_CFG_UNION
 �ṹ˵��  : IF_CLK_EN_CFG �Ĵ����ṹ���塣��ַƫ����:0x04����ֵ:0x00000000�����:32
 �Ĵ���˵��: APB IF/DMIC IF/SIF/I2S�ӿ����ģ��ʱ��ʹ������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stereo_uplink_l_en : 1;  /* bit[0]    : STEREO������ͨ���첽FIFOʱ��ʹ��:
                                                              0���ر�ʱ�ӣ�
                                                              1����ʱ�ӡ� */
        unsigned int  stereo_uplink_r_en : 1;  /* bit[1]    : STEREO������ͨ���첽FIFOʱ��ʹ��:
                                                              0���ر�ʱ�ӣ�
                                                              1����ʱ�ӡ� */
        unsigned int  voice_uplink_l_en  : 1;  /* bit[2]    : VOICE������ͨ���첽FIFOʱ��ʹ��:
                                                              0���ر�ʱ�ӣ�
                                                              1����ʱ�ӡ� */
        unsigned int  voice_uplink_r_en  : 1;  /* bit[3]    : VOICE������ͨ���첽FIFOʱ��ʹ��:
                                                              0���ر�ʱ�ӣ�
                                                              1����ʱ�ӡ� */
        unsigned int  stereo_dlink_l_en  : 1;  /* bit[4]    : STEREO������ͨ���첽FIFO��PGAʱ��ʹ��:
                                                              0���ر�ʱ�ӣ�
                                                              1����ʱ�ӡ� */
        unsigned int  stereo_dlink_r_en  : 1;  /* bit[5]    : STEREO������ͨ���첽FIFO��PGAʱ��ʹ��:
                                                              0���ر�ʱ�ӣ�
                                                              1����ʱ�ӡ� */
        unsigned int  voice_dlink_en     : 1;  /* bit[6]    : VOICE����ͨ���첽FIFO��PGAʱ��ʹ��:
                                                              0���ر�ʱ�ӣ�
                                                              1����ʱ�ӡ� */
        unsigned int  voice_dlink_src_en : 1;  /* bit[7]    : VOICE����ͨ��SRCʹ�ܣ�ͬʱ����src��bypass��
                                                              0���ر�ʱ�ӣ�src bypass��
                                                              1����ʱ�ӣ�src ���������� */
        unsigned int  s1_if_clk_en       : 1;  /* bit[8]    : S1 I2S�ӿڲ���ʱ��ʹ�ܡ�
                                                              0���ر�ʱ�ӣ�
                                                              1����ʱ�ӡ� */
        unsigned int  s1_il_pga_en       : 1;  /* bit[9]    : I2S S1�ӿڣ�Digital FM���ӿ�������ͨ��PGAʱ��ʹ�ܣ�
                                                              0���ر�ʱ��
                                                              1����ʱ�� */
        unsigned int  s1_ir_pga_en       : 1;  /* bit[10]   : I2S S1�ӿڣ�Digital FM���ӿ�������ͨ��PGAʱ��ʹ�ܣ�
                                                              0���ر�ʱ��
                                                              1����ʱ�� */
        unsigned int  reserved_0         : 1;  /* bit[11]   : reserved */
        unsigned int  s2_il_pga_en       : 1;  /* bit[12]   : I2S S2�ӿڣ�BT���ӿ�������ͨ��PGAʱ��ʹ�ܣ�
                                                              0���ر�ʱ��
                                                              1����ʱ�� */
        unsigned int  s2_ir_pga_en       : 1;  /* bit[13]   : I2S S2�ӿڣ�BT���ӿ�������ͨ��PGAʱ��ʹ�ܣ�
                                                              0���ر�ʱ��
                                                              1����ʱ�� */
        unsigned int  s2_ol_src_en       : 1;  /* bit[14]   : I2S S2�ӿڣ�BT���ӿ������ͨ��SRCʱ��ʹ�ܣ�
                                                              0���ر�ʱ��
                                                              1����ʱ�� */
        unsigned int  s2_ol_mixer_en     : 1;  /* bit[15]   : I2S S2�ӿڣ�BT���ӿ������ͨ��MIXERʱ��ʹ�ܣ�
                                                              0���ر�ʱ��
                                                              1����ʱ�� */
        unsigned int  s2_if_clk_en       : 1;  /* bit[16]   : S2 I2S�ӿڲ���ʱ��ʹ�ܡ�
                                                              0���ر�ʱ�ӣ�
                                                              1����ʱ�ӡ� */
        unsigned int  reserved_1         : 3;  /* bit[17-19]: reserved */
        unsigned int  s3_if_clk_en       : 1;  /* bit[20]   : S3 I2S�ӿڲ���ʱ��ʹ�ܡ�
                                                              0���ر�ʱ�ӣ�
                                                              1����ʱ�ӡ� */
        unsigned int  reserved_2         : 3;  /* bit[21-23]: reserved */
        unsigned int  thirdmd_dlink_en   : 1;  /* bit[24]   : ������MODEAM����ͨ���첽FIFO��PGAʱ��ʹ��:
                                                              0���ر�ʱ�ӣ�
                                                              1����ʱ�ӡ� */
        unsigned int  thirdmd_uplink_en  : 1;  /* bit[25]   : ������MODEAM����ͨ���첽FIFOʱ��ʹ��:
                                                              0���ر�ʱ�ӣ�
                                                              1����ʱ�ӡ� */
        unsigned int  reserved_3         : 6;  /* bit[26-31]: reserved */
    } reg;
} SOC_ASP_CODEC_IF_CLK_EN_CFG_UNION;
#endif
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_stereo_uplink_l_en_START  (0)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_stereo_uplink_l_en_END    (0)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_stereo_uplink_r_en_START  (1)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_stereo_uplink_r_en_END    (1)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_voice_uplink_l_en_START   (2)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_voice_uplink_l_en_END     (2)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_voice_uplink_r_en_START   (3)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_voice_uplink_r_en_END     (3)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_stereo_dlink_l_en_START   (4)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_stereo_dlink_l_en_END     (4)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_stereo_dlink_r_en_START   (5)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_stereo_dlink_r_en_END     (5)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_voice_dlink_en_START      (6)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_voice_dlink_en_END        (6)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_voice_dlink_src_en_START  (7)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_voice_dlink_src_en_END    (7)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s1_if_clk_en_START        (8)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s1_if_clk_en_END          (8)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s1_il_pga_en_START        (9)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s1_il_pga_en_END          (9)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s1_ir_pga_en_START        (10)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s1_ir_pga_en_END          (10)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s2_il_pga_en_START        (12)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s2_il_pga_en_END          (12)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s2_ir_pga_en_START        (13)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s2_ir_pga_en_END          (13)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s2_ol_src_en_START        (14)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s2_ol_src_en_END          (14)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s2_ol_mixer_en_START      (15)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s2_ol_mixer_en_END        (15)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s2_if_clk_en_START        (16)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s2_if_clk_en_END          (16)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s3_if_clk_en_START        (20)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_s3_if_clk_en_END          (20)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_thirdmd_dlink_en_START    (24)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_thirdmd_dlink_en_END      (24)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_thirdmd_uplink_en_START   (25)
#define SOC_ASP_CODEC_IF_CLK_EN_CFG_thirdmd_uplink_en_END     (25)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_UNION
 �ṹ˵��  : DIG_FILTER_CLK_EN_CFG �Ĵ����ṹ���塣��ַƫ����:0x08����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����˲���ͨ�����ģ��ʱ��ʹ�����ã�����DACL/DACR/ ADCL/ADCRͨ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  adcl_pga_en     : 1;  /* bit[0]    : ADCLͨ��PGAģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�
                                                           1����ʱ�ӡ� */
        unsigned int  adcl_hpf_en     : 1;  /* bit[1]    : ADCLͨ��HPFģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�bypass��
                                                           1����ʱ�ӡ� */
        unsigned int  adcl_hbfvd_en   : 1;  /* bit[2]    : ADCLͨ��HBFVDģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�bypass��
                                                           1����ʱ�ӡ� */
        unsigned int  adcl_hbf2d_en   : 1;  /* bit[3]    : ADCLͨ��HBF2Dģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�bypass��
                                                           1����ʱ�ӡ� */
        unsigned int  adcl_compd_en   : 1;  /* bit[4]    : ADCLͨ��COMPDģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�bypass��
                                                           1����ʱ�ӡ� */
        unsigned int  adcl_cic_en     : 1;  /* bit[5]    : ADCLͨ��CICģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�
                                                           1����ʱ�ӡ� */
        unsigned int  sidetone_pga_en : 1;  /* bit[6]    : SIDETONE PGAģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�
                                                           1����ʱ�ӡ� */
        unsigned int  reserved_0      : 1;  /* bit[7]    : reserved */
        unsigned int  adcr_pga_en     : 1;  /* bit[8]    : ADCRͨ��PGAģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�
                                                           1����ʱ�ӡ� */
        unsigned int  adcr_hpf_en     : 1;  /* bit[9]    : ADCRͨ��HPFģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�bypass��
                                                           1����ʱ�ӡ� */
        unsigned int  adcr_hbfvd_en   : 1;  /* bit[10]   : ADCRͨ��HBFVDģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�bypass��
                                                           1����ʱ�ӡ� */
        unsigned int  adcr_hbf2d_en   : 1;  /* bit[11]   : ADCRͨ��HBF2Dģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�bypass��
                                                           1����ʱ�ӡ� */
        unsigned int  adcr_compd_en   : 1;  /* bit[12]   : ADCRͨ��COMPDģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�bypass��
                                                           1����ʱ�ӡ� */
        unsigned int  adcr_cic_en     : 1;  /* bit[13]   : ADCRͨ��CICģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�
                                                           1����ʱ�ӡ� */
        unsigned int  reserved_1      : 2;  /* bit[14-15]: reserved */
        unsigned int  dacl_agc_en     : 1;  /* bit[16]   : DACLͨ��AGCģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�
                                                           1����ʱ�ӡ� */
        unsigned int  dacl_mixer_en   : 1;  /* bit[17]   : DACLͨ��MIXERģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�
                                                           1����ʱ�ӡ� */
        unsigned int  dacl_deemp_en   : 1;  /* bit[18]   : DACLͨ��DEEMPģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�bypass��
                                                           1����ʱ�ӡ� */
        unsigned int  dacl_hbf1i_en   : 1;  /* bit[19]   : DACLͨ��HBF1Iģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�bypass��
                                                           1����ʱ�ӡ� */
        unsigned int  dacl_hbf2i_en   : 1;  /* bit[20]   : DACLͨ��HBF2Iģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�
                                                           1����ʱ�ӡ� */
        unsigned int  dacl_compi_en   : 1;  /* bit[21]   : DACLͨ��COMPIģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�bypass��
                                                           1����ʱ�ӡ� */
        unsigned int  dacl_sdm_en     : 1;  /* bit[22]   : DACLͨ��SDMģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�
                                                           1����ʱ�ӡ� */
        unsigned int  reserved_2      : 1;  /* bit[23]   : reserved */
        unsigned int  dacr_agc_en     : 1;  /* bit[24]   : DACRͨ��AGCģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�
                                                           1����ʱ�ӡ� */
        unsigned int  dacr_mixer_en   : 1;  /* bit[25]   : DACRͨ��MIXERģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�
                                                           1����ʱ�ӡ� */
        unsigned int  dacr_deemp_en   : 1;  /* bit[26]   : DACRͨ��DEEMPģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�bypass��
                                                           1����ʱ�ӡ� */
        unsigned int  dacr_hbf1i_en   : 1;  /* bit[27]   : DACRͨ��HBF1Iģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�bypass��
                                                           1����ʱ�ӡ� */
        unsigned int  dacr_hbf2i_en   : 1;  /* bit[28]   : DACRͨ��HBF2Iģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�bypass��
                                                           1����ʱ�ӡ� */
        unsigned int  dacr_compi_en   : 1;  /* bit[29]   : DACRͨ��COMPIģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�bypass��
                                                           1����ʱ�ӡ� */
        unsigned int  dacr_sdm_en     : 1;  /* bit[30]   : DACRͨ��SDMģ��ʱ��ʹ�ܣ�
                                                           0���ر�ʱ�ӣ�
                                                           1����ʱ�ӡ� */
        unsigned int  reserved_3      : 1;  /* bit[31]   : reserved */
    } reg;
} SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_UNION;
#endif
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_pga_en_START      (0)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_pga_en_END        (0)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_hpf_en_START      (1)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_hpf_en_END        (1)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_hbfvd_en_START    (2)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_hbfvd_en_END      (2)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_hbf2d_en_START    (3)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_hbf2d_en_END      (3)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_compd_en_START    (4)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_compd_en_END      (4)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_cic_en_START      (5)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcl_cic_en_END        (5)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_sidetone_pga_en_START  (6)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_sidetone_pga_en_END    (6)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_pga_en_START      (8)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_pga_en_END        (8)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_hpf_en_START      (9)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_hpf_en_END        (9)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_hbfvd_en_START    (10)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_hbfvd_en_END      (10)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_hbf2d_en_START    (11)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_hbf2d_en_END      (11)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_compd_en_START    (12)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_compd_en_END      (12)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_cic_en_START      (13)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_adcr_cic_en_END        (13)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_agc_en_START      (16)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_agc_en_END        (16)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_mixer_en_START    (17)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_mixer_en_END      (17)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_deemp_en_START    (18)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_deemp_en_END      (18)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_hbf1i_en_START    (19)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_hbf1i_en_END      (19)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_hbf2i_en_START    (20)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_hbf2i_en_END      (20)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_compi_en_START    (21)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_compi_en_END      (21)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_sdm_en_START      (22)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacl_sdm_en_END        (22)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_agc_en_START      (24)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_agc_en_END        (24)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_mixer_en_START    (25)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_mixer_en_END      (25)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_deemp_en_START    (26)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_deemp_en_END      (26)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_hbf1i_en_START    (27)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_hbf1i_en_END      (27)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_hbf2i_en_START    (28)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_hbf2i_en_END      (28)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_compi_en_START    (29)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_compi_en_END      (29)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_sdm_en_START      (30)
#define SOC_ASP_CODEC_DIG_FILTER_CLK_EN_CFG_dacr_sdm_en_END        (30)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_FS_CFG_UNION
 �ṹ˵��  : FS_CFG �Ĵ����ṹ���塣��ַƫ����:0x0C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  fs_voice_dlink    : 3;  /* bit[0-2]  : VOICE����ͨ������������
                                                             0��8KHz�� 1��16KHz��
                                                             2��32KHz�� 3������
                                                             4��48KHz�� 5��96KHz��
                                                             6��192KHz��7������ */
        unsigned int  reserved_0        : 1;  /* bit[3]    : reserved */
        unsigned int  fs_stereo_dlink_l : 3;  /* bit[4-6]  : STEREO������ͨ������������
                                                             0��8KHz�� 1��16KHz��
                                                             2��32KHz�� 3������
                                                             4��48KHz�� 5��96KHz��
                                                             6��192KHz��7������ */
        unsigned int  reserved_1        : 1;  /* bit[7]    : reserved */
        unsigned int  fs_stereo_dlink_r : 3;  /* bit[8-10] : STEREO������ͨ������������
                                                             0��8KHz�� 1��16KHz��
                                                             2��32KHz�� 3������
                                                             4��48KHz�� 5��96KHz��
                                                             6��192KHz��7������ */
        unsigned int  reserved_2        : 5;  /* bit[11-15]: reserved */
        unsigned int  fs_daclr          : 3;  /* bit[16-18]: dacl��dacrͨ����������������
                                                             0��8KHz�� 1��16KHz��
                                                             2��32KHz�� 3������
                                                             4��48KHz�� 5��96KHz��
                                                             6��192KHz��7������ */
        unsigned int  reserved_3        : 1;  /* bit[19]   : reserved */
        unsigned int  fs_adclr          : 3;  /* bit[20-22]: adcl��adcrͨ����������������
                                                             0��8KHz�� 1��16KHz��
                                                             2��32KHz�� 3������
                                                             4��48KHz�� 5��96KHz��
                                                             6��192KHz��7������ */
        unsigned int  reserved_4        : 1;  /* bit[23]   : reserved */
        unsigned int  fs_s1             : 3;  /* bit[24-26]: S1�ӿڲ���������
                                                             0��8KHz�� 1��16KHz��
                                                             2��32KHz�� 3������
                                                             4��48KHz�� 5��96KHz��
                                                             6��192KHz��7������ */
        unsigned int  reserved_5        : 1;  /* bit[27]   : reserved */
        unsigned int  fs_s2             : 3;  /* bit[28-30]: S2�ӿڲ���������
                                                             0��8KHz�� 1��16KHz��
                                                             2��32KHz�� 3������
                                                             4��48KHz�� 5��96KHz��
                                                             6��192KHz��7������ */
        unsigned int  reserved_6        : 1;  /* bit[31]   : reserved */
    } reg;
} SOC_ASP_CODEC_FS_CFG_UNION;
#endif
#define SOC_ASP_CODEC_FS_CFG_fs_voice_dlink_START     (0)
#define SOC_ASP_CODEC_FS_CFG_fs_voice_dlink_END       (2)
#define SOC_ASP_CODEC_FS_CFG_fs_stereo_dlink_l_START  (4)
#define SOC_ASP_CODEC_FS_CFG_fs_stereo_dlink_l_END    (6)
#define SOC_ASP_CODEC_FS_CFG_fs_stereo_dlink_r_START  (8)
#define SOC_ASP_CODEC_FS_CFG_fs_stereo_dlink_r_END    (10)
#define SOC_ASP_CODEC_FS_CFG_fs_daclr_START           (16)
#define SOC_ASP_CODEC_FS_CFG_fs_daclr_END             (18)
#define SOC_ASP_CODEC_FS_CFG_fs_adclr_START           (20)
#define SOC_ASP_CODEC_FS_CFG_fs_adclr_END             (22)
#define SOC_ASP_CODEC_FS_CFG_fs_s1_START              (24)
#define SOC_ASP_CODEC_FS_CFG_fs_s1_END                (26)
#define SOC_ASP_CODEC_FS_CFG_fs_s2_START              (28)
#define SOC_ASP_CODEC_FS_CFG_fs_s2_END                (30)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_I2S_CFG_UNION
 �ṹ˵��  : I2S_CFG �Ĵ����ṹ���塣��ַƫ����:0x10����ֵ:0x03200320�����:32
 �Ĵ���˵��: S1/S2�ӿ����üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s1_func_mode           : 3;  /* bit[0-2]  : S1�ӿ�ģʽѡ��
                                                                  3'b000:I2S
                                                                  3'b010:PCM STD
                                                                  3'b011:PCM USER Defined
                                                                  3'b100:Left Justified
                                                                  3'b101:Right Justified
                                                                  ���������� */
        unsigned int  s1_codec_data_format   : 1;  /* bit[3]    : S1�ӿ�Codec ADC/DAC���ݸ�ʽѡ��
                                                                  0����ʾ�����Ʋ��룻
                                                                  1����ʾ�������루binary offset���� */
        unsigned int  s1_rx_clk_sel          : 1;  /* bit[4]    : S1�ӿ�RX����ʱ��ѡ��
                                                                  1'b0:BCLK�����ؽ�������
                                                                  1'b1:BCLK�½��ؽ������� */
        unsigned int  s1_tx_clk_sel          : 1;  /* bit[5]    : S1�ӿ�TX����ʱ��ѡ��
                                                                  1'b0:BCLK�����ش������
                                                                  1'b1:BCLK�½��ش������ */
        unsigned int  s1_direct_loop         : 2;  /* bit[6-7]  : S1 I2S�ӿڻ���ģʽѡ��
                                                                  2'b00����������ģʽ��
                                                                  2'b01��Sdin->Sdout��
                                                                  2'b10: RX_DATA[23:0] -> TX_IN[23:0]
                                                                  2'b11: SDOUT -> SDIN */
        unsigned int  s1_codec_io_wordlength : 2;  /* bit[8-9]  : S1�ӿ�λ�����ơ�
                                                                  00��16bit��
                                                                  01��18bit��
                                                                  10��20bit��
                                                                  11��24bit�� */
        unsigned int  s1_chnnl_mode          : 1;  /* bit[10]   : S1�ӿ��������ã�
                                                                  1'b0:��������ǰ
                                                                  1'b1:��������ǰ */
        unsigned int  s1_lrclk_mode          : 1;  /* bit[11]   : S1�ӿ�֡ͬ���ź���������ѡ��
                                                                  1'b0:low -> left channel
                                                                  1'b1:low -> right channel */
        unsigned int  s1_mst_slv             : 1;  /* bit[12]   : S1�ӿ�Master/Slaveģʽѡ��
                                                                  1'b0:Materģʽ����masterģʽ��BCLK/SYNC�ſ������
                                                                  1'b1:Slaveģʽ */
        unsigned int  s1_frame_mode          : 1;  /* bit[13]   : S1�ӿ�I2Sģʽ��֡��ʽ���ã�
                                                                  1'b0:I2Sģʽ��64bit frame��PCMģʽ��32bit frame
                                                                  1'b1:I2Sģʽ��32bit frame��PCMģʽ��16bit frame */
        unsigned int  s1_if_rx_ena           : 1;  /* bit[14]   : S1�ӿ�RX����ʹ�ܣ�
                                                                  1'b1:ʹ��
                                                                  1'b0:�ر� */
        unsigned int  s1_if_tx_ena           : 1;  /* bit[15]   : S1�ӿ�TX����ʹ�ܣ�
                                                                  1'b1:ʹ��
                                                                  1'b0:�ر� */
        unsigned int  s2_func_mode           : 3;  /* bit[16-18]: S2�ӿ�ģʽѡ��
                                                                  3'b000:I2S
                                                                  3'b010:PCM STD
                                                                  3'b011:PCM USER Defined
                                                                  3'b100:Left Justified
                                                                  3'b101:Right Justified
                                                                  ���������� */
        unsigned int  s2_codec_data_format   : 1;  /* bit[19]   : S2�ӿ�Codec ADC/DAC���ݸ�ʽѡ��
                                                                  0����ʾ�����Ʋ��룻
                                                                  1����ʾ�������루binary offset���� */
        unsigned int  s2_rx_clk_sel          : 1;  /* bit[20]   : S2�ӿ�RX����ʱ��ѡ��
                                                                  1'b0:BCLK�����ؽ�������
                                                                  1'b1:BCLK�½��ؽ������� */
        unsigned int  s2_tx_clk_sel          : 1;  /* bit[21]   : S2�ӿ�TX����ʱ��ѡ��
                                                                  1'b0:BCLK�����ش������
                                                                  1'b1:BCLK�½��ش������ */
        unsigned int  s2_direct_loop         : 2;  /* bit[22-23]: S2 I2S�ӿڻ���ģʽѡ��
                                                                  2'b00����������ģʽ��
                                                                  2'b01��Sdin->Sdout��
                                                                  2'b10: RX_DATA[23:0] -> TX_IN[23:0]
                                                                  2'b11: SDOUT -> SDIN */
        unsigned int  s2_codec_io_wordlength : 2;  /* bit[24-25]: S2�ӿ�λ�����ơ�
                                                                  00��16bit��
                                                                  01��18bit��
                                                                  10��20bit��
                                                                  11��24bit�� */
        unsigned int  s2_chnnl_mode          : 1;  /* bit[26]   : S2�ӿ��������ã�
                                                                  1'b0:��������ǰ
                                                                  1'b1:��������ǰ */
        unsigned int  s2_lrclk_mode          : 1;  /* bit[27]   : S2�ӿ�֡ͬ���ź���������ѡ��
                                                                  1'b0:low -> left channel
                                                                  1'b1:low -> right channel */
        unsigned int  s2_mst_slv             : 1;  /* bit[28]   : S2�ӿ�Master/Slaveģʽѡ��
                                                                  1'b0:Materģʽ����masterģʽ��BCLK/SYNC�ſ������
                                                                  1'b1:Slaveģʽ */
        unsigned int  s2_frame_mode          : 1;  /* bit[29]   : S2�ӿ�I2Sģʽ��֡��ʽ���ã�
                                                                  1'b0:I2Sģʽ��64bit frame��PCMģʽ��32bit frame
                                                                  1'b1:I2Sģʽ��32bit frame��PCMģʽ��16bit frame */
        unsigned int  s2_if_rx_ena           : 1;  /* bit[30]   : S2�ӿ�RX����ʹ�ܣ�
                                                                  1'b1:ʹ��
                                                                  1'b0:�ر� */
        unsigned int  s2_if_tx_ena           : 1;  /* bit[31]   : S2�ӿ�TX����ʹ�ܣ�
                                                                  1'b1:ʹ��
                                                                  1'b0:�ر� */
    } reg;
} SOC_ASP_CODEC_I2S_CFG_UNION;
#endif
#define SOC_ASP_CODEC_I2S_CFG_s1_func_mode_START            (0)
#define SOC_ASP_CODEC_I2S_CFG_s1_func_mode_END              (2)
#define SOC_ASP_CODEC_I2S_CFG_s1_codec_data_format_START    (3)
#define SOC_ASP_CODEC_I2S_CFG_s1_codec_data_format_END      (3)
#define SOC_ASP_CODEC_I2S_CFG_s1_rx_clk_sel_START           (4)
#define SOC_ASP_CODEC_I2S_CFG_s1_rx_clk_sel_END             (4)
#define SOC_ASP_CODEC_I2S_CFG_s1_tx_clk_sel_START           (5)
#define SOC_ASP_CODEC_I2S_CFG_s1_tx_clk_sel_END             (5)
#define SOC_ASP_CODEC_I2S_CFG_s1_direct_loop_START          (6)
#define SOC_ASP_CODEC_I2S_CFG_s1_direct_loop_END            (7)
#define SOC_ASP_CODEC_I2S_CFG_s1_codec_io_wordlength_START  (8)
#define SOC_ASP_CODEC_I2S_CFG_s1_codec_io_wordlength_END    (9)
#define SOC_ASP_CODEC_I2S_CFG_s1_chnnl_mode_START           (10)
#define SOC_ASP_CODEC_I2S_CFG_s1_chnnl_mode_END             (10)
#define SOC_ASP_CODEC_I2S_CFG_s1_lrclk_mode_START           (11)
#define SOC_ASP_CODEC_I2S_CFG_s1_lrclk_mode_END             (11)
#define SOC_ASP_CODEC_I2S_CFG_s1_mst_slv_START              (12)
#define SOC_ASP_CODEC_I2S_CFG_s1_mst_slv_END                (12)
#define SOC_ASP_CODEC_I2S_CFG_s1_frame_mode_START           (13)
#define SOC_ASP_CODEC_I2S_CFG_s1_frame_mode_END             (13)
#define SOC_ASP_CODEC_I2S_CFG_s1_if_rx_ena_START            (14)
#define SOC_ASP_CODEC_I2S_CFG_s1_if_rx_ena_END              (14)
#define SOC_ASP_CODEC_I2S_CFG_s1_if_tx_ena_START            (15)
#define SOC_ASP_CODEC_I2S_CFG_s1_if_tx_ena_END              (15)
#define SOC_ASP_CODEC_I2S_CFG_s2_func_mode_START            (16)
#define SOC_ASP_CODEC_I2S_CFG_s2_func_mode_END              (18)
#define SOC_ASP_CODEC_I2S_CFG_s2_codec_data_format_START    (19)
#define SOC_ASP_CODEC_I2S_CFG_s2_codec_data_format_END      (19)
#define SOC_ASP_CODEC_I2S_CFG_s2_rx_clk_sel_START           (20)
#define SOC_ASP_CODEC_I2S_CFG_s2_rx_clk_sel_END             (20)
#define SOC_ASP_CODEC_I2S_CFG_s2_tx_clk_sel_START           (21)
#define SOC_ASP_CODEC_I2S_CFG_s2_tx_clk_sel_END             (21)
#define SOC_ASP_CODEC_I2S_CFG_s2_direct_loop_START          (22)
#define SOC_ASP_CODEC_I2S_CFG_s2_direct_loop_END            (23)
#define SOC_ASP_CODEC_I2S_CFG_s2_codec_io_wordlength_START  (24)
#define SOC_ASP_CODEC_I2S_CFG_s2_codec_io_wordlength_END    (25)
#define SOC_ASP_CODEC_I2S_CFG_s2_chnnl_mode_START           (26)
#define SOC_ASP_CODEC_I2S_CFG_s2_chnnl_mode_END             (26)
#define SOC_ASP_CODEC_I2S_CFG_s2_lrclk_mode_START           (27)
#define SOC_ASP_CODEC_I2S_CFG_s2_lrclk_mode_END             (27)
#define SOC_ASP_CODEC_I2S_CFG_s2_mst_slv_START              (28)
#define SOC_ASP_CODEC_I2S_CFG_s2_mst_slv_END                (28)
#define SOC_ASP_CODEC_I2S_CFG_s2_frame_mode_START           (29)
#define SOC_ASP_CODEC_I2S_CFG_s2_frame_mode_END             (29)
#define SOC_ASP_CODEC_I2S_CFG_s2_if_rx_ena_START            (30)
#define SOC_ASP_CODEC_I2S_CFG_s2_if_rx_ena_END              (30)
#define SOC_ASP_CODEC_I2S_CFG_s2_if_tx_ena_START            (31)
#define SOC_ASP_CODEC_I2S_CFG_s2_if_tx_ena_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_UNION
 �ṹ˵��  : DIG_FILTER_MODULE_CFG �Ĵ����ṹ���塣��ַƫ����:0x14����ֵ:0x0F0F0000�����:32
 �Ĵ���˵��: DAC/ADCͨ���ڲ�MIXER��ģ��BYPASSģʽ���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rm_codec_dac2adc    : 3;  /* bit[0-2]  : ADCRͨ��CIC�˲������ػ�·�����ơ�
                                                               000��CIC����ΪADC·��ƫ�ƺ󣨼�4�����룻��
                                                               001��CIC����ΪDACL·�����룻
                                                               010��CIC����ΪDACR·�����룻
                                                               011��CIC����ΪADC·�����루����ʹ�ã���
                                                               100��CIC����ΪDMIC PORT0·�����룻
                                                               101��reserved��
                                                               ����ֵ��CIC����ΪADC·��ƫ�ƺ󣨼�4�����룻�� */
        unsigned int  reserved_0          : 1;  /* bit[3]    : reserved */
        unsigned int  lm_codec_dac2adc    : 3;  /* bit[4-6]  : ADCLͨ��CIC�˲������ػ�·�����ơ�
                                                               000��CIC����ΪADC·��ƫ�ƺ󣨼�4�����룻
                                                               001��CIC����ΪDACL·�����룻
                                                               010��CIC����ΪDACR·�����룻
                                                               011��CIC����ΪADC·�����루����ʹ�ã���
                                                               100��CIC����ΪDMIC PORT0·�����룻
                                                               101��reserved��
                                                               ����ֵ��CIC����ΪADC·��ƫ�ƺ󣨼�4�����룻 */
        unsigned int  reserved_1          : 1;  /* bit[7]    : reserved */
        unsigned int  sw_dacl_sdm_dither  : 1;  /* bit[8]    : DACL SDM dither���á� 
                                                               1��dither��·��Ч�� 
                                                               0��dither��·��Ч�� */
        unsigned int  sw_dacr_sdm_dither  : 1;  /* bit[9]    : DACR SDM dither���á� 
                                                               1��dither��·��Ч�� 
                                                               0��dither��·��Ч�� */
        unsigned int  reserved_2          : 6;  /* bit[10-15]: reserved */
        unsigned int  dacl_mixer_in1_mute : 1;  /* bit[16]   : DACLͨ��mixer��muteʹ�ܣ�
                                                               1'b1:voice dlink src���mute
                                                               1'b0:�������� */
        unsigned int  dacl_mixer_in2_mute : 1;  /* bit[17]   : DACLͨ��mixer��muteʹ�ܣ�
                                                               1'b1:stereo dlink��ͨ��pga���mute
                                                               1'b0:�������� */
        unsigned int  dacl_mixer_in3_mute : 1;  /* bit[18]   : DACLͨ��mixer�� muteʹ�ܣ�
                                                               1'b1:s1������ͨ��pga���mute
                                                               1'b0:�������� */
        unsigned int  dacl_mixer_in4_mute : 1;  /* bit[19]   : DACLͨ��mixer muteʹ�ܣ�
                                                               1'b1:sidetone pga ���mute
                                                               1'b0:�������� */
        unsigned int  dacl_mixer_gain     : 2;  /* bit[20-21]: DACLͨ��MIXER���������ã�
                                                               2'b00:1
                                                               2'b01:����1/2
                                                               2'b10:����1/4
                                                               2'b11:���� */
        unsigned int  reserved_3          : 2;  /* bit[22-23]: reserved */
        unsigned int  dacr_mixer_in1_mute : 1;  /* bit[24]   : DACRͨ��mixer��muteʹ�ܣ�
                                                               1'b1:voice dlink src���mute
                                                               1'b0:�������� */
        unsigned int  dacr_mixer_in2_mute : 1;  /* bit[25]   : DACRͨ��mixer��muteʹ�ܣ�
                                                               1'b1:stereo dlink��ͨ��pga���mute
                                                               1'b0:�������� */
        unsigned int  dacr_mixer_in3_mute : 1;  /* bit[26]   : DACRͨ��mixer�� muteʹ�ܣ�
                                                               1'b1:s1������ͨ��pga���mute
                                                               1'b0:�������� */
        unsigned int  dacr_mixer_in4_mute : 1;  /* bit[27]   : DACRͨ��mixer muteʹ�ܣ�
                                                               1'b1:sidetone pga ���mutemute
                                                               1'b0:�������� */
        unsigned int  dacr_mixer_gain     : 2;  /* bit[28-29]: DACRͨ��MIXER���������ã�
                                                               2'b00:1
                                                               2'b01:����1/2
                                                               2'b10:����1/4
                                                               2'b11:���� */
        unsigned int  reserved_4          : 2;  /* bit[30-31]: reserved */
    } reg;
} SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_UNION;
#endif
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_rm_codec_dac2adc_START     (0)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_rm_codec_dac2adc_END       (2)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_lm_codec_dac2adc_START     (4)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_lm_codec_dac2adc_END       (6)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_sw_dacl_sdm_dither_START   (8)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_sw_dacl_sdm_dither_END     (8)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_sw_dacr_sdm_dither_START   (9)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_sw_dacr_sdm_dither_END     (9)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacl_mixer_in1_mute_START  (16)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacl_mixer_in1_mute_END    (16)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacl_mixer_in2_mute_START  (17)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacl_mixer_in2_mute_END    (17)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacl_mixer_in3_mute_START  (18)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacl_mixer_in3_mute_END    (18)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacl_mixer_in4_mute_START  (19)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacl_mixer_in4_mute_END    (19)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacl_mixer_gain_START      (20)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacl_mixer_gain_END        (21)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacr_mixer_in1_mute_START  (24)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacr_mixer_in1_mute_END    (24)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacr_mixer_in2_mute_START  (25)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacr_mixer_in2_mute_END    (25)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacr_mixer_in3_mute_START  (26)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacr_mixer_in3_mute_END    (26)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacr_mixer_in4_mute_START  (27)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacr_mixer_in4_mute_END    (27)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacr_mixer_gain_START      (28)
#define SOC_ASP_CODEC_DIG_FILTER_MODULE_CFG_dacr_mixer_gain_END        (29)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_UNION
 �ṹ˵��  : MUX_TOP_MODULE_CFG �Ĵ����ṹ���塣��ַƫ����:0x18����ֵ:0x00003300�����:32
 �Ĵ���˵��: MUX_TOP�����ģ�����ü�״̬
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  voice_dlink_src_mode       : 3;  /* bit[0-2]  : VOICE����ͨ��SRC MODEѡ��
                                                                      3'b001: 12 interpolation
                                                                      3'b010: 6 interpolation
                                                                      3'b011: 2 interpolation
                                                                      3'b100: 3 interpolation
                                                                      other: reserved, not work */
        unsigned int  voice_dlink_src_rdy        : 1;  /* bit[3]    : VOICE����ͨ��SRC READY�źţ�
                                                                      1'b1:SRC RAM��ʼ�����
                                                                      1'b0:SRC RAM��ʼ�������У���������ĸüĴ��������ඪʧһ�������㣩 */
        unsigned int  s2_ol_src_mode             : 2;  /* bit[4-5]  : S2 I2S�ӿ�SRC MODEѡ��
                                                                      2'b00: 3��������
                                                                      2'b01:12��������
                                                                      2'b10:6��������
                                                                      2'b11:2�������� */
        unsigned int  s2_ol_src_rdy              : 1;  /* bit[6]    : S2 I2S�ӿ�������ͨ��SRC READY�źţ�
                                                                      1'b1:SRC RAM��ʼ�����
                                                                      1'b0:SRC RAM��ʼ�������У���������ĸüĴ��������ඪʧһ�������㣩 */
        unsigned int  reserved_0                 : 1;  /* bit[7]    : reserved */
        unsigned int  s2_ol_mixer_in1_mute       : 1;  /* bit[8]    : S2�ӿ������ͨ��mixer���muteʹ�ܣ�
                                                                      1'b1: DACL mixer ���mute
                                                                      1'b0:�������� */
        unsigned int  s2_ol_mixer_in2_mute       : 1;  /* bit[9]    : S2�ӿ������ͨ��mixer���muteʹ�ܣ�
                                                                      1'b1:DACR mixer ���mute
                                                                      1'b0:�������� */
        unsigned int  s2_ol_mixer_gain           : 2;  /* bit[10-11]: S2�����ͨ��MIXER���������ã�
                                                                      2'b00:1
                                                                      2'b01:����1/2
                                                                      2'b10:����
                                                                      2'b11:���� */
        unsigned int  voice_dlink_mixer_in1_mute : 1;  /* bit[12]   : voice downlink ͨ��mixer���muteʹ�ܣ�
                                                                      1'b1: DACL mixer ���mute
                                                                      1'b0:�������� */
        unsigned int  voice_dlink_mixer_in2_mute : 1;  /* bit[13]   : voice downlink ͨ��mixer���muteʹ�ܣ�
                                                                      1'b1:DACR mixer ���mute
                                                                      1'b0:�������� */
        unsigned int  voice_dlink_mixer_gain     : 2;  /* bit[14-15]: voice downlink ͨ��MIXER���������ã�
                                                                      2'b00:1
                                                                      2'b01:����1/2
                                                                      2'b10:����
                                                                      2'b11:���� */
        unsigned int  reserved_1                 : 16; /* bit[16-31]: reserved */
    } reg;
} SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_UNION;
#endif
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_voice_dlink_src_mode_START        (0)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_voice_dlink_src_mode_END          (2)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_voice_dlink_src_rdy_START         (3)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_voice_dlink_src_rdy_END           (3)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_s2_ol_src_mode_START              (4)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_s2_ol_src_mode_END                (5)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_s2_ol_src_rdy_START               (6)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_s2_ol_src_rdy_END                 (6)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_s2_ol_mixer_in1_mute_START        (8)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_s2_ol_mixer_in1_mute_END          (8)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_s2_ol_mixer_in2_mute_START        (9)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_s2_ol_mixer_in2_mute_END          (9)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_s2_ol_mixer_gain_START            (10)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_s2_ol_mixer_gain_END              (11)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_voice_dlink_mixer_in1_mute_START  (12)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_voice_dlink_mixer_in1_mute_END    (12)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_voice_dlink_mixer_in2_mute_START  (13)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_voice_dlink_mixer_in2_mute_END    (13)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_voice_dlink_mixer_gain_START      (14)
#define SOC_ASP_CODEC_MUX_TOP_MODULE_CFG_voice_dlink_mixer_gain_END        (15)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_ADC_PGA_CFG_UNION
 �ṹ˵��  : ADC_PGA_CFG �Ĵ����ṹ���塣��ַƫ����:0x1C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ADCͨ��PGAģ������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  adcl_pga_integer_config : 8;  /* bit[0-7]  : ADCL pga���������������:
                                                                   Ĭ�ϣ�0dB
                                                                   ���淶Χ:-72dB~+36dB��
                                                                   ����
                                                                   0010_0100:36dB
                                                                   0010_0011:35dB
                                                                   ����
                                                                   1011_1000��-72dB
                                                                   ����Ϊ1dB,�����ʾ��
                                                                   �㷨��֧���������淶Χ���ֵ�����÷�Χ���ֵ��ģ����Ϊ����Ԥ�⣬���������á�
                                                                   ����ͨ�����üĴ�������Ϊ0x80��ʵ�־����� */
        unsigned int  adcl_pga_frac_config    : 1;  /* bit[8]    : ADCL pga��������С��λ���á�
                                                                   0��0.0dB��
                                                                   1��0.5dB�� */
        unsigned int  adcl_pga_mute           : 1;  /* bit[9]    : ADCL pga muteʹ�ܣ�
                                                                   1'b1: mute��Ч�����0
                                                                   1'b0: �ر�mute */
        unsigned int  reserved_0              : 2;  /* bit[10-11]: reserved */
        unsigned int  adcl_pga_thr_config     : 2;  /* bit[12-13]: ADCL pga������͵�ƽ�������á� 
                                                                   00��-60dB�� 
                                                                   01��-72dB�� 
                                                                   10��-90dB�� 
                                                                   11��-120dB�� */
        unsigned int  reserved_1              : 2;  /* bit[14-15]: reserved */
        unsigned int  adcr_pga_integer_config : 8;  /* bit[16-23]: ADCR pga���������������:
                                                                   Ĭ�ϣ�0dB
                                                                   ���淶Χ:-72dB~+36dB��
                                                                   ����
                                                                   0010_0100:36dB
                                                                   0010_0011:35dB
                                                                   ���� 
                                                                   1011_1000��-72dB
                                                                   ����Ϊ1dB,�����ʾ��
                                                                   �㷨��֧���������淶Χ���ֵ�����÷�Χ���ֵ��ģ����Ϊ����Ԥ�⣬���������á�
                                                                   ����ͨ�����üĴ�������Ϊ0x80��ʵ�־����� */
        unsigned int  adcr_pga_frac_config    : 1;  /* bit[24]   : ADCR pga��������С��λ���á�
                                                                   0��0.0dB��
                                                                   1��0.5dB�� */
        unsigned int  adcr_pga_mute           : 1;  /* bit[25]   : ADCR pga muteʹ�ܣ�
                                                                   1'b1: mute��Ч�����0
                                                                   1'b0: �ر�mute */
        unsigned int  reserved_2              : 2;  /* bit[26-27]: reserved */
        unsigned int  adcr_pga_thr_config     : 2;  /* bit[28-29]: ADCR pga������͵�ƽ�������á� 
                                                                   00��-60dB�� 
                                                                   01��-72dB�� 
                                                                   10��-90dB�� 
                                                                   11��-120dB�� */
        unsigned int  reserved_3              : 2;  /* bit[30-31]: reserved */
    } reg;
} SOC_ASP_CODEC_ADC_PGA_CFG_UNION;
#endif
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcl_pga_integer_config_START  (0)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcl_pga_integer_config_END    (7)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcl_pga_frac_config_START     (8)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcl_pga_frac_config_END       (8)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcl_pga_mute_START            (9)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcl_pga_mute_END              (9)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcl_pga_thr_config_START      (12)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcl_pga_thr_config_END        (13)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcr_pga_integer_config_START  (16)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcr_pga_integer_config_END    (23)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcr_pga_frac_config_START     (24)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcr_pga_frac_config_END       (24)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcr_pga_mute_START            (25)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcr_pga_mute_END              (25)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcr_pga_thr_config_START      (28)
#define SOC_ASP_CODEC_ADC_PGA_CFG_adcr_pga_thr_config_END        (29)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_S1_INPUT_PGA_CFG_UNION
 �ṹ˵��  : S1_INPUT_PGA_CFG �Ĵ����ṹ���塣��ַƫ����:0x20����ֵ:0x00000000�����:32
 �Ĵ���˵��: S1�ӿ�����ͨ��PGA����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s1_il_pga_integer_config : 8;  /* bit[0-7]  : S1 I2S�ӿ�������ͨ��pga���������������:
                                                                    Ĭ�ϣ�0dB
                                                                    ���淶Χ:-72dB~+36dB��
                                                                    ����
                                                                    0010_0100:36dB
                                                                    0010_0011:35dB
                                                                    ����
                                                                    1011_1000��-72dB
                                                                    ����Ϊ1dB,�����ʾ��
                                                                    �㷨��֧���������淶Χ���ֵ�����÷�Χ���ֵ��ģ����Ϊ����Ԥ�⣬���������á�
                                                                    ����ͨ�����üĴ�������Ϊ0x80��ʵ�־����� */
        unsigned int  s1_il_pga_frac_config    : 1;  /* bit[8]    : S1�ӿ� ������ͨ��pga��������С��λ���á�
                                                                    0��0.0dB��
                                                                    1��0.5dB�� */
        unsigned int  s1_il_pga_mute           : 1;  /* bit[9]    : S1�ӿ�������ͨ��pga muteʹ�ܣ�
                                                                    1'b1: mute��Ч�����0
                                                                    1'b0: �ر�mute */
        unsigned int  reserved_0               : 2;  /* bit[10-11]: reserved */
        unsigned int  s1_il_pga_thr_config     : 2;  /* bit[12-13]: S1�ӿ�������ͨ��pga������͵�ƽ�������á� 
                                                                    00��-60dB�� 
                                                                    01��-72dB�� 
                                                                    10��-90dB�� 
                                                                    11��-120dB�� */
        unsigned int  reserved_1               : 2;  /* bit[14-15]: reserved */
        unsigned int  s1_ir_pga_integer_config : 8;  /* bit[16-23]: S1 I2S�ӿ�������ͨ��pga���������������:
                                                                    Ĭ�ϣ�0dB
                                                                    ���淶Χ:-72dB~+36dB��
                                                                    ����
                                                                    0010_0100:36dB
                                                                    0010_0011:35dB
                                                                    ���� 
                                                                    1011_1000��-72dB
                                                                    ����Ϊ1dB,�����ʾ��
                                                                    �㷨��֧���������淶Χ���ֵ�����÷�Χ���ֵ��ģ����Ϊ����Ԥ�⣬���������á�
                                                                    ����ͨ�����üĴ�������Ϊ0x80��ʵ�־����� */
        unsigned int  s1_ir_pga_frac_config    : 1;  /* bit[24]   : S1�ӿ�������ͨ��pga��������С��λ���á�
                                                                    0��0.0dB��
                                                                    1��0.5dB�� */
        unsigned int  s1_ir_pga_mute           : 1;  /* bit[25]   : S1�ӿ�������ͨ��pga muteʹ�ܣ�
                                                                    1'b1: mute��Ч�����0
                                                                    1'b0: �ر�mute */
        unsigned int  reserved_2               : 2;  /* bit[26-27]: reserved */
        unsigned int  s1_ir_pga_thr_config     : 2;  /* bit[28-29]: S1�ӿ�������ͨ��pga������͵�ƽ�������á� 
                                                                    00��-60dB�� 
                                                                    01��-72dB�� 
                                                                    10��-90dB�� 
                                                                    11��-120dB�� */
        unsigned int  reserved_3               : 2;  /* bit[30-31]: reserved */
    } reg;
} SOC_ASP_CODEC_S1_INPUT_PGA_CFG_UNION;
#endif
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_il_pga_integer_config_START  (0)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_il_pga_integer_config_END    (7)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_il_pga_frac_config_START     (8)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_il_pga_frac_config_END       (8)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_il_pga_mute_START            (9)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_il_pga_mute_END              (9)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_il_pga_thr_config_START      (12)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_il_pga_thr_config_END        (13)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_ir_pga_integer_config_START  (16)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_ir_pga_integer_config_END    (23)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_ir_pga_frac_config_START     (24)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_ir_pga_frac_config_END       (24)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_ir_pga_mute_START            (25)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_ir_pga_mute_END              (25)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_ir_pga_thr_config_START      (28)
#define SOC_ASP_CODEC_S1_INPUT_PGA_CFG_s1_ir_pga_thr_config_END        (29)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_S2_INPUT_PGA_CFG_UNION
 �ṹ˵��  : S2_INPUT_PGA_CFG �Ĵ����ṹ���塣��ַƫ����:0x24����ֵ:0x00000000�����:32
 �Ĵ���˵��: S2�ӿ�����ͨ��PGA����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s2_il_pga_integer_config : 8;  /* bit[0-7]  : S2 I2S�ӿ�������ͨ��pga���������������:
                                                                    Ĭ�ϣ�0dB
                                                                    ���淶Χ:-72dB~+36dB��
                                                                    ����
                                                                    0010_0100:36dB
                                                                    0010_0011:35dB
                                                                    ����
                                                                    1011_1000��-72dB
                                                                    ����Ϊ1dB,�����ʾ��
                                                                    �㷨��֧���������淶Χ���ֵ�����÷�Χ���ֵ��ģ����Ϊ����Ԥ�⣬���������á�
                                                                    ����ͨ�����üĴ�������Ϊ0x80��ʵ�־����� */
        unsigned int  s2_il_pga_frac_config    : 1;  /* bit[8]    : S2�ӿ� ������ͨ��pga��������С��λ���á�
                                                                    0��0.0dB��
                                                                    1��0.5dB�� */
        unsigned int  s2_il_pga_mute           : 1;  /* bit[9]    : S2�ӿ�������ͨ��pga muteʹ�ܣ�
                                                                    1'b1: mute��Ч�����0
                                                                    1'b0: �ر�mute */
        unsigned int  reserved_0               : 2;  /* bit[10-11]: reserved */
        unsigned int  s2_il_pga_thr_config     : 2;  /* bit[12-13]: S2�ӿ�������ͨ��pga������͵�ƽ�������á� 
                                                                    00��-60dB�� 
                                                                    01��-72dB�� 
                                                                    10��-90dB�� 
                                                                    11��-120dB�� */
        unsigned int  reserved_1               : 2;  /* bit[14-15]: reserved */
        unsigned int  s2_ir_pga_integer_config : 8;  /* bit[16-23]: S2 I2S�ӿ�������ͨ��pga���������������:
                                                                    Ĭ�ϣ�0dB
                                                                    ���淶Χ:-72dB~+36dB��
                                                                    ����
                                                                    0010_0100:36dB
                                                                    0010_0011:35dB
                                                                    ���� 
                                                                    1011_1000��-72dB
                                                                    ����Ϊ1dB,�����ʾ��
                                                                    �㷨��֧���������淶Χ���ֵ�����÷�Χ���ֵ��ģ����Ϊ����Ԥ�⣬���������á�
                                                                    ����ͨ�����üĴ�������Ϊ0x80��ʵ�־����� */
        unsigned int  s2_ir_pga_frac_config    : 1;  /* bit[24]   : S2�ӿ�������ͨ��pga��������С��λ���á�
                                                                    0��0.0dB��
                                                                    1��0.5dB�� */
        unsigned int  s2_ir_pga_mute           : 1;  /* bit[25]   : S2�ӿ�������ͨ��pga muteʹ�ܣ�
                                                                    1'b1: mute��Ч�����0
                                                                    1'b0: �ر�mute */
        unsigned int  reserved_2               : 2;  /* bit[26-27]: reserved */
        unsigned int  s2_ir_pga_thr_config     : 2;  /* bit[28-29]: S2�ӿ�������ͨ��pga������͵�ƽ�������á� 
                                                                    00��-60dB�� 
                                                                    01��-72dB�� 
                                                                    10��-90dB�� 
                                                                    11��-120dB�� */
        unsigned int  reserved_3               : 2;  /* bit[30-31]: reserved */
    } reg;
} SOC_ASP_CODEC_S2_INPUT_PGA_CFG_UNION;
#endif
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_il_pga_integer_config_START  (0)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_il_pga_integer_config_END    (7)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_il_pga_frac_config_START     (8)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_il_pga_frac_config_END       (8)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_il_pga_mute_START            (9)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_il_pga_mute_END              (9)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_il_pga_thr_config_START      (12)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_il_pga_thr_config_END        (13)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_ir_pga_integer_config_START  (16)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_ir_pga_integer_config_END    (23)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_ir_pga_frac_config_START     (24)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_ir_pga_frac_config_END       (24)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_ir_pga_mute_START            (25)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_ir_pga_mute_END              (25)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_ir_pga_thr_config_START      (28)
#define SOC_ASP_CODEC_S2_INPUT_PGA_CFG_s2_ir_pga_thr_config_END        (29)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_UNION
 �ṹ˵��  : STEREO_DLINK_PGA_CFG �Ĵ����ṹ���塣��ַƫ����:0x28����ֵ:0x00000000�����:32
 �Ĵ���˵��: STEREO����ͨ��PGA����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stereo_dlink_l_pga_integer_config : 8;  /* bit[0-7]  : stereo����������pga���������������:
                                                                             Ĭ�ϣ�0dB
                                                                             ���淶Χ:-72dB~+36dB��
                                                                             ����
                                                                             0010_0100:36dB
                                                                             0010_0011:35dB
                                                                             ����
                                                                             1011_1000��-72dB
                                                                             ����Ϊ1dB,�����ʾ��
                                                                             �㷨��֧���������淶Χ���ֵ�����÷�Χ���ֵ��ģ����Ϊ����Ԥ�⣬���������á�
                                                                             ����ͨ�����üĴ�������Ϊ0x80��ʵ�־����� */
        unsigned int  stereo_dlink_l_pga_frac_config    : 1;  /* bit[8]    : stereo����������pga��������С��λ���á�
                                                                             0��0.0dB��
                                                                             1��0.5dB�� */
        unsigned int  stereo_dlink_l_pga_mute           : 1;  /* bit[9]    : stereo����������pga muteʹ�ܣ�
                                                                             1'b1: mute��Ч�����0
                                                                             1'b0: �ر�mute */
        unsigned int  reserved_0                        : 2;  /* bit[10-11]: reserved */
        unsigned int  stereo_dlink_l_pga_thr_config     : 2;  /* bit[12-13]: stereo����������pga������͵�ƽ�������á� 
                                                                             00��-60dB�� 
                                                                             01��-72dB�� 
                                                                             10��-90dB�� 
                                                                             11��-120dB�� */
        unsigned int  reserved_1                        : 2;  /* bit[14-15]: reserved */
        unsigned int  stereo_dlink_r_pga_integer_config : 8;  /* bit[16-23]: stereo����������pga���������������:
                                                                             Ĭ�ϣ�0dB
                                                                             ���淶Χ:-72dB~+36dB��
                                                                             ����
                                                                             0010_0100:36dB
                                                                             0010_0011:35dB
                                                                             ���� 
                                                                             1011_1000��-72dB
                                                                             ����Ϊ1dB,�����ʾ��
                                                                             �㷨��֧���������淶Χ���ֵ�����÷�Χ���ֵ��ģ����Ϊ����Ԥ�⣬���������á�
                                                                             ����ͨ�����üĴ�������Ϊ0x80��ʵ�־����� */
        unsigned int  stereo_dlink_r_pga_frac_config    : 1;  /* bit[24]   : stereo����������pga��������С��λ���á�
                                                                             0��0.0dB��
                                                                             1��0.5dB�� */
        unsigned int  stereo_dlink_r_pga_mute           : 1;  /* bit[25]   : stereo����������pga muteʹ�ܣ�
                                                                             1'b1: mute��Ч�����0
                                                                             1'b0: �ر�mute */
        unsigned int  reserved_2                        : 2;  /* bit[26-27]: reserved */
        unsigned int  stereo_dlink_r_pga_thr_config     : 2;  /* bit[28-29]: stereo����������pga������͵�ƽ�������á� 
                                                                             00��-60dB�� 
                                                                             01��-72dB�� 
                                                                             10��-90dB�� 
                                                                             11��-120dB�� */
        unsigned int  reserved_3                        : 2;  /* bit[30-31]: reserved */
    } reg;
} SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_UNION;
#endif
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_l_pga_integer_config_START  (0)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_l_pga_integer_config_END    (7)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_l_pga_frac_config_START     (8)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_l_pga_frac_config_END       (8)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_l_pga_mute_START            (9)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_l_pga_mute_END              (9)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_l_pga_thr_config_START      (12)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_l_pga_thr_config_END        (13)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_r_pga_integer_config_START  (16)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_r_pga_integer_config_END    (23)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_r_pga_frac_config_START     (24)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_r_pga_frac_config_END       (24)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_r_pga_mute_START            (25)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_r_pga_mute_END              (25)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_r_pga_thr_config_START      (28)
#define SOC_ASP_CODEC_STEREO_DLINK_PGA_CFG_stereo_dlink_r_pga_thr_config_END        (29)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_UNION
 �ṹ˵��  : VOICE_SIDETONE_DLINK_PGA_CFG �Ĵ����ṹ���塣��ַƫ����:0x2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: VOICE����ͨ��PGA��SIDETONE PGA����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  voice_dlink_pga_integer_config : 8;  /* bit[0-7]  : VOICE����ͨ��pga�������������������:
                                                                          Ĭ�ϣ�0dB
                                                                          ���淶Χ:-72dB~+36dB��
                                                                          ����
                                                                          0010_0100:36dB
                                                                          0010_0011:35dB
                                                                          ����
                                                                          1011_1000��-72dB
                                                                          ����Ϊ1dB,�����ʾ�� */
        unsigned int  voice_dlink_pga_frac_config    : 1;  /* bit[8]    : VOICE����ͨ��pga��������С��λ���á�
                                                                          0��0.0dB��
                                                                          1��0.5dB�� */
        unsigned int  voice_dlink_pga_mute           : 1;  /* bit[9]    : voice��������pga muteʹ�ܣ�
                                                                          1'b1: mute��Ч�����0
                                                                          1'b0: �ر�mute */
        unsigned int  reserved_0                     : 2;  /* bit[10-11]: reserved */
        unsigned int  voice_dlink_pga_thr_config     : 2;  /* bit[12-13]: voice dlinkͨ��pga������͵�ƽ�������á� 
                                                                          00��-60dB�� 
                                                                          01��-72dB�� 
                                                                          10��-90dB�� 
                                                                          11��-120dB�� */
        unsigned int  reserved_1                     : 2;  /* bit[14-15]: reserved */
        unsigned int  sidetone_pga_integer_config    : 8;  /* bit[16-23]: SIDETONE pga�������������������:
                                                                          Ĭ�ϣ�0dB
                                                                          ���淶Χ:-72dB~+36dB��
                                                                          ����
                                                                          0010_0100:36dB
                                                                          0010_0011:35dB
                                                                          ����
                                                                          1011_1000��-72dB
                                                                          ����Ϊ1dB,�����ʾ�� */
        unsigned int  sidetone_pga_frac_config       : 1;  /* bit[24]   : SIDETONE pga��������С��λ���á�
                                                                          0��0.0dB��
                                                                          1��0.5dB�� */
        unsigned int  sidetone_pga_mute              : 1;  /* bit[25]   : SIDETONE pga muteʹ�ܣ�
                                                                          1'b1: mute��Ч�����0
                                                                          1'b0: �ر�mute */
        unsigned int  reserved_2                     : 2;  /* bit[26-27]: reserved */
        unsigned int  sidetone_pga_thr_config        : 2;  /* bit[28-29]: sidetone pga������͵�ƽ�������á� 
                                                                          00��-60dB�� 
                                                                          01��-72dB�� 
                                                                          10��-90dB�� 
                                                                          11��-120dB�� */
        unsigned int  reserved_3                     : 2;  /* bit[30-31]: reserved */
    } reg;
} SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_UNION;
#endif
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_voice_dlink_pga_integer_config_START  (0)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_voice_dlink_pga_integer_config_END    (7)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_voice_dlink_pga_frac_config_START     (8)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_voice_dlink_pga_frac_config_END       (8)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_voice_dlink_pga_mute_START            (9)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_voice_dlink_pga_mute_END              (9)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_voice_dlink_pga_thr_config_START      (12)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_voice_dlink_pga_thr_config_END        (13)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_sidetone_pga_integer_config_START     (16)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_sidetone_pga_integer_config_END       (23)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_sidetone_pga_frac_config_START        (24)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_sidetone_pga_frac_config_END          (24)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_sidetone_pga_mute_START               (25)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_sidetone_pga_mute_END                 (25)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_sidetone_pga_thr_config_START         (28)
#define SOC_ASP_CODEC_VOICE_SIDETONE_DLINK_PGA_CFG_sidetone_pga_thr_config_END           (29)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_APB_AFIFO_CFG_1_UNION
 �ṹ˵��  : APB_AFIFO_CFG_1 �Ĵ����ṹ���塣��ַƫ����:0x30����ֵ:0x00000000�����:32
 �Ĵ���˵��: APB IF��AFIFO���ü�״̬�ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stereo_uplink_l_fifo_clr    : 1;  /* bit[0]   : STEREO UPLINK��ͨ��AFIFO������ã�
                                                                      1'b1: clr��Ч�����FIFO����
                                                                      1'b0: clr��Ч */
        unsigned int  stereo_uplink_r_fifo_clr    : 1;  /* bit[1]   : STEREO UPLINK��ͨ��AFIFO������ã�
                                                                      1'b1: clr��Ч�����FIFO����
                                                                      1'b0: clr��Ч */
        unsigned int  voice_uplink_l_fifo_clr     : 1;  /* bit[2]   : VOICE UPLINK��ͨ��AFIFO������ã�
                                                                      1'b1: clr��Ч�����FIFO����
                                                                      1'b0: clr��Ч */
        unsigned int  voice_uplink_r_fifo_clr     : 1;  /* bit[3]   : VOICE UPLINK��ͨ��AFIFO������ã�
                                                                      1'b1: clr��Ч�����FIFO����
                                                                      1'b0: clr��Ч */
        unsigned int  stereo_dlink_l_fifo_clr     : 1;  /* bit[4]   : STEREO DLINK��ͨ��AFIFO������ã�
                                                                      1'b1: clr��Ч�����FIFO����
                                                                      1'b0: clr��Ч */
        unsigned int  stereo_dlink_r_fifo_clr     : 1;  /* bit[5]   : STEREO DLINK��ͨ��AFIFO������ã�
                                                                      1'b1: clr��Ч�����FIFO����
                                                                      1'b0: clr��Ч */
        unsigned int  voice_dlink_fifo_clr        : 1;  /* bit[6]   : VOICE DLINKͨ��AFIFO������ã�
                                                                      1'b1:clr��Ч�����FIFO����
                                                                      1'b0: clr��Ч */
        unsigned int  thirdmd_dlink_fifo_clr      : 1;  /* bit[7]   :  */
        unsigned int  thirdmd_uplink_fifo_clr     : 1;  /* bit[8]   :  */
        unsigned int  reserved_0                  : 7;  /* bit[9-15]: reserved */
        unsigned int  stereo_uplink_l_fifo_werror : 1;  /* bit[16]  : STEREO UPLINK��ͨ��AFIFOдerror
                                                                      1'b1: FIFO��ʱ������
                                                                      1'b0: ���� */
        unsigned int  stereo_uplink_r_fifo_werror : 1;  /* bit[17]  : STEREO UPLINK��ͨ��AFIFOдerror
                                                                      1'b1: FIFO��ʱ������
                                                                      1'b0: ���� */
        unsigned int  voice_uplink_l_fifo_werror  : 1;  /* bit[18]  : VOICE UPLINK��ͨ��AFIFOдerror
                                                                      1'b1: FIFO��ʱ������
                                                                      1'b0: ���� */
        unsigned int  voice_uplink_r_fifo_werror  : 1;  /* bit[19]  : VOICE UPLINK��ͨ��AFIFOдerror
                                                                      1'b1: FIFO��ʱ������
                                                                      1'b0: ���� */
        unsigned int  stereo_dlink_l_fifo_werror  : 1;  /* bit[20]  : STEREO DLINK��ͨ��AFIFOдerror
                                                                      1'b1: FIFO��ʱ������
                                                                      1'b0: ���� */
        unsigned int  stereo_dlink_r_fifo_werror  : 1;  /* bit[21]  : STEREO DLINK��ͨ��AFIFOдerror
                                                                      1'b1: FIFO��ʱ������
                                                                      1'b0: ���� */
        unsigned int  voice_dlink_fifo_werror     : 1;  /* bit[22]  : VOICE DLINKͨ��AFIFOдerror
                                                                      1'b1: FIFO��ʱд����
                                                                      1'b0: ���� */
        unsigned int  reserved_1                  : 1;  /* bit[23]  : reserved */
        unsigned int  stereo_uplink_l_fifo_rerror : 1;  /* bit[24]  : STEREO UPLINK��ͨ��AFIFO��error
                                                                      1'b1: FIFO��ʱ������
                                                                      1'b0: ���� */
        unsigned int  stereo_uplink_r_fifo_rerror : 1;  /* bit[25]  : STEREO UPLINK��ͨ��AFIFO��error
                                                                      1'b1: FIFO��ʱ������
                                                                      1'b0: ���� */
        unsigned int  voice_uplink_l_fifo_rerror  : 1;  /* bit[26]  : VOICE UPLINK��ͨ��AFIFO��error
                                                                      1'b1: FIFO��ʱ������
                                                                      1'b0: ���� */
        unsigned int  voice_uplink_r_fifo_rerror  : 1;  /* bit[27]  : VOICE UPLINK��ͨ��AFIFO��error
                                                                      1'b1: FIFO��ʱ������
                                                                      1'b0: ���� */
        unsigned int  stereo_dlink_l_fifo_rerror  : 1;  /* bit[28]  : STEREO DLINK��ͨ��AFIFO��error
                                                                      1'b1: FIFO��ʱ������
                                                                      1'b0: ���� */
        unsigned int  stereo_dlink_r_fifo_rerror  : 1;  /* bit[29]  : STEREO DLINK��ͨ��AFIFO��error
                                                                      1'b1: FIFO��ʱ������
                                                                      1'b0: ���� */
        unsigned int  voice_dlink_fifo_rerror     : 1;  /* bit[30]  : VOICE DLINKͨ��AFIFO��error
                                                                      1'b1: FIFO��ʱ������
                                                                      1'b0: ���� */
        unsigned int  reserved_2                  : 1;  /* bit[31]  : reserved */
    } reg;
} SOC_ASP_CODEC_APB_AFIFO_CFG_1_UNION;
#endif
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_l_fifo_clr_START     (0)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_l_fifo_clr_END       (0)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_r_fifo_clr_START     (1)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_r_fifo_clr_END       (1)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_l_fifo_clr_START      (2)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_l_fifo_clr_END        (2)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_r_fifo_clr_START      (3)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_r_fifo_clr_END        (3)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_l_fifo_clr_START      (4)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_l_fifo_clr_END        (4)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_r_fifo_clr_START      (5)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_r_fifo_clr_END        (5)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_dlink_fifo_clr_START         (6)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_dlink_fifo_clr_END           (6)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_thirdmd_dlink_fifo_clr_START       (7)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_thirdmd_dlink_fifo_clr_END         (7)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_thirdmd_uplink_fifo_clr_START      (8)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_thirdmd_uplink_fifo_clr_END        (8)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_l_fifo_werror_START  (16)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_l_fifo_werror_END    (16)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_r_fifo_werror_START  (17)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_r_fifo_werror_END    (17)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_l_fifo_werror_START   (18)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_l_fifo_werror_END     (18)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_r_fifo_werror_START   (19)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_r_fifo_werror_END     (19)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_l_fifo_werror_START   (20)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_l_fifo_werror_END     (20)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_r_fifo_werror_START   (21)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_r_fifo_werror_END     (21)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_dlink_fifo_werror_START      (22)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_dlink_fifo_werror_END        (22)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_l_fifo_rerror_START  (24)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_l_fifo_rerror_END    (24)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_r_fifo_rerror_START  (25)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_uplink_r_fifo_rerror_END    (25)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_l_fifo_rerror_START   (26)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_l_fifo_rerror_END     (26)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_r_fifo_rerror_START   (27)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_uplink_r_fifo_rerror_END     (27)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_l_fifo_rerror_START   (28)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_l_fifo_rerror_END     (28)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_r_fifo_rerror_START   (29)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_stereo_dlink_r_fifo_rerror_END     (29)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_dlink_fifo_rerror_START      (30)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_1_voice_dlink_fifo_rerror_END        (30)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_APB_AFIFO_CFG_2_UNION
 �ṹ˵��  : APB_AFIFO_CFG_2 �Ĵ����ṹ���塣��ַƫ����:0x34����ֵ:0x000F101E�����:32
 �Ĵ���˵��: APB IF��AFIFO���ü�״̬�ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  voice_dlink_fifo_afull_th    : 5;  /* bit[0-4]  : VOICE DLINKͨ��AFIFO������ֵ��fifo����Ч��ֵ�������ڸ�ֵʱ��FIFO almost full�ź���Ч */
        unsigned int  reserved_0                   : 3;  /* bit[5-7]  : reserved */
        unsigned int  voice_dlink_fifo_aempty_th   : 5;  /* bit[8-12] : VOICE DLINKͨ��AFIFO������ֵ��fifo����Ч��ֵ�������ڸ�ֵʱ��FIFO almost empty�ź���Ч */
        unsigned int  reserved_1                   : 3;  /* bit[13-15]: reserved */
        unsigned int  stereo_uplink_l_fifo_din_sel : 1;  /* bit[16]   : STEREO UPLINK��ͨ��AFIFO��������ѡ��
                                                                        1'b1:ADCLͨ���������
                                                                        1'b0:S1�ӿ����������� */
        unsigned int  stereo_uplink_r_fifo_din_sel : 1;  /* bit[17]   : STEREO UPLINK��ͨ��AFIFO��������ѡ��
                                                                        1'b1:ADCRͨ���������
                                                                        1'b0:S1�ӿ����������� */
        unsigned int  voice_uplink_l_fifo_din_sel  : 1;  /* bit[18]   : VOICE UPLINK��ͨ��AFIFO��������ѡ��
                                                                        1'b1:ADCLͨ���������
                                                                        1'b0:S2�ӿ����������� */
        unsigned int  voice_uplink_r_fifo_din_sel  : 1;  /* bit[19]   : VOICE UPLINK��ͨ��AFIFO��������ѡ��
                                                                        1'b1:ADCRͨ���������
                                                                        1'b0:S2�ӿ����������� */
        unsigned int  reserved_2                   : 12; /* bit[20-31]: reserved */
    } reg;
} SOC_ASP_CODEC_APB_AFIFO_CFG_2_UNION;
#endif
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_voice_dlink_fifo_afull_th_START     (0)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_voice_dlink_fifo_afull_th_END       (4)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_voice_dlink_fifo_aempty_th_START    (8)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_voice_dlink_fifo_aempty_th_END      (12)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_stereo_uplink_l_fifo_din_sel_START  (16)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_stereo_uplink_l_fifo_din_sel_END    (16)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_stereo_uplink_r_fifo_din_sel_START  (17)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_stereo_uplink_r_fifo_din_sel_END    (17)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_voice_uplink_l_fifo_din_sel_START   (18)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_voice_uplink_l_fifo_din_sel_END     (18)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_voice_uplink_r_fifo_din_sel_START   (19)
#define SOC_ASP_CODEC_APB_AFIFO_CFG_2_voice_uplink_r_fifo_din_sel_END     (19)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_UNION
 �ṹ˵��  : STEREO_DLINK_FIFO_TH_CFG �Ĵ����ṹ���塣��ַƫ����:0x38����ֵ:0x101E101E�����:32
 �Ĵ���˵��: STEREO����ͨ��AFIFO ����ˮ������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stereo_dlink_l_fifo_afull_th  : 5;  /* bit[0-4]  : STEREO DLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
        unsigned int  reserved_0                    : 3;  /* bit[5-7]  : reserved */
        unsigned int  stereo_dlink_l_fifo_aempty_th : 5;  /* bit[8-12] : STEREO DLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
        unsigned int  reserved_1                    : 3;  /* bit[13-15]: reserved */
        unsigned int  stereo_dlink_r_fifo_afull_th  : 5;  /* bit[16-20]: STEREO DLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
        unsigned int  reserved_2                    : 3;  /* bit[21-23]: reserved */
        unsigned int  stereo_dlink_r_fifo_aempty_th : 5;  /* bit[24-28]: STEREO DLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
        unsigned int  reserved_3                    : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_UNION;
#endif
#define SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_stereo_dlink_l_fifo_afull_th_START   (0)
#define SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_stereo_dlink_l_fifo_afull_th_END     (4)
#define SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_stereo_dlink_l_fifo_aempty_th_START  (8)
#define SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_stereo_dlink_l_fifo_aempty_th_END    (12)
#define SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_stereo_dlink_r_fifo_afull_th_START   (16)
#define SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_stereo_dlink_r_fifo_afull_th_END     (20)
#define SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_stereo_dlink_r_fifo_aempty_th_START  (24)
#define SOC_ASP_CODEC_STEREO_DLINK_FIFO_TH_CFG_stereo_dlink_r_fifo_aempty_th_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_UNION
 �ṹ˵��  : STEREO_UPLINK_FIFO_TH_CFG �Ĵ����ṹ���塣��ַƫ����:0x3C����ֵ:0x01100110�����:32
 �Ĵ���˵��: STEREO����ͨ��AFIFO ����ˮ������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stereo_uplink_l_fifo_afull_th  : 5;  /* bit[0-4]  : STEREO UPLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
        unsigned int  reserved_0                     : 3;  /* bit[5-7]  : reserved */
        unsigned int  stereo_uplink_l_fifo_aempty_th : 5;  /* bit[8-12] : STEREO UPLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
        unsigned int  reserved_1                     : 3;  /* bit[13-15]: reserved */
        unsigned int  stereo_uplink_r_fifo_afull_th  : 5;  /* bit[16-20]: STEREO UPLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
        unsigned int  reserved_2                     : 3;  /* bit[21-23]: reserved */
        unsigned int  stereo_uplink_r_fifo_aempty_th : 5;  /* bit[24-28]: STEREO UPLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
        unsigned int  reserved_3                     : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_UNION;
#endif
#define SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_stereo_uplink_l_fifo_afull_th_START   (0)
#define SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_stereo_uplink_l_fifo_afull_th_END     (4)
#define SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_stereo_uplink_l_fifo_aempty_th_START  (8)
#define SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_stereo_uplink_l_fifo_aempty_th_END    (12)
#define SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_stereo_uplink_r_fifo_afull_th_START   (16)
#define SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_stereo_uplink_r_fifo_afull_th_END     (20)
#define SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_stereo_uplink_r_fifo_aempty_th_START  (24)
#define SOC_ASP_CODEC_STEREO_UPLINK_FIFO_TH_CFG_stereo_uplink_r_fifo_aempty_th_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_UNION
 �ṹ˵��  : VOICE_UPLINK_FIFO_TH_CFG �Ĵ����ṹ���塣��ַƫ����:0x40����ֵ:0x01100110�����:32
 �Ĵ���˵��: VOICE����ͨ��AFIFO ����ˮ������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  voice_uplink_l_fifo_afull_th  : 5;  /* bit[0-4]  : VOICE UPLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
        unsigned int  reserved_0                    : 3;  /* bit[5-7]  : reserved */
        unsigned int  voice_uplink_l_fifo_aempty_th : 5;  /* bit[8-12] : VOICE UPLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
        unsigned int  reserved_1                    : 3;  /* bit[13-15]: reserved */
        unsigned int  voice_uplink_r_fifo_afull_th  : 5;  /* bit[16-20]: VOICE UPLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
        unsigned int  reserved_2                    : 3;  /* bit[21-23]: reserved */
        unsigned int  voice_uplink_r_fifo_aempty_th : 5;  /* bit[24-28]: VOICE UPLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
        unsigned int  reserved_3                    : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_UNION;
#endif
#define SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_voice_uplink_l_fifo_afull_th_START   (0)
#define SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_voice_uplink_l_fifo_afull_th_END     (4)
#define SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_voice_uplink_l_fifo_aempty_th_START  (8)
#define SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_voice_uplink_l_fifo_aempty_th_END    (12)
#define SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_voice_uplink_r_fifo_afull_th_START   (16)
#define SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_voice_uplink_r_fifo_afull_th_END     (20)
#define SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_voice_uplink_r_fifo_aempty_th_START  (24)
#define SOC_ASP_CODEC_VOICE_UPLINK_FIFO_TH_CFG_voice_uplink_r_fifo_aempty_th_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_CODEC_IRQ_MASK_UNION
 �ṹ˵��  : CODEC_IRQ_MASK �Ĵ����ṹ���塣��ַƫ����:0x44����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж����μĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  codec_data_intrp_mask : 6;  /* bit[0-5] : �ж�����λ��
                                                                [5]: thirdmd uplink�ж�����
                                                                [4]: thirdmd dlink �ж�����
                                                                [3]: voice uplink�ж�����
                                                                [2]: stereo uplink�ж�����
                                                                [1]: stereo dlink�ж�����
                                                                [0]: voice dlink�ж����� */
        unsigned int  reserved              : 26; /* bit[6-31]: reserved */
    } reg;
} SOC_ASP_CODEC_CODEC_IRQ_MASK_UNION;
#endif
#define SOC_ASP_CODEC_CODEC_IRQ_MASK_codec_data_intrp_mask_START  (0)
#define SOC_ASP_CODEC_CODEC_IRQ_MASK_codec_data_intrp_mask_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_CODEC_IRQ_UNION
 �ṹ˵��  : CODEC_IRQ �Ĵ����ṹ���塣��ַƫ����:0x48����ֵ:0x00000000�����:32
 �Ĵ���˵��: �ж�״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  codec_data_intrp : 6;  /* bit[0-5] : �ж�״̬λ��
                                                           [5]: thirdmd uplink�жϣ�Ϊ1ʱ��ʾthirdmd uplink����Master������
                                                           [4]: thirdmd dlink �жϣ�Ϊ1ʱ��ʾthirdmd dlink ����Master������
                                                           [3]: voice uplink�жϣ�Ϊ1ʱ��ʾvoice uplink����Master������
                                                           [2]: stereo uplink�жϣ�Ϊ1ʱ��ʾvoice uplink����Master������
                                                           [1]: stereo dlink�жϣ�Ϊ1ʱ��ʾvoice uplink����Master������
                                                           [0]: voice dlink�жϣ�Ϊ1ʱ��ʾvoice uplink����Master������ */
        unsigned int  reserved         : 26; /* bit[6-31]: reserved */
    } reg;
} SOC_ASP_CODEC_CODEC_IRQ_UNION;
#endif
#define SOC_ASP_CODEC_CODEC_IRQ_codec_data_intrp_START  (0)
#define SOC_ASP_CODEC_CODEC_IRQ_codec_data_intrp_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_DACL_AGC_CFG_1_UNION
 �ṹ˵��  : DACL_AGC_CFG_1 �Ĵ����ṹ���塣��ַƫ����:0x4C����ֵ:0x249AAE51�����:32
 �Ĵ���˵��: DACL AGC (�Զ��������)���üĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dacl_agc_gwin_config     : 2;  /* bit[0-1]  : AGC�����µ���ƽ�����������á�
                                                                    00��3.5dB��
                                                                    01��5.5dB��
                                                                    10��9dB��
                                                                    11��15dB�� */
        unsigned int  dacl_agc_levellow_config : 2;  /* bit[2-3]  : AGC�͵�ƽ�����������á�
                                                                    00��-60dB��
                                                                    01��-72dB��
                                                                    10��-90dB��
                                                                    11��-120dB�� */
        unsigned int  dacl_agc_gstepd_config   : 2;  /* bit[4-5]  : AGC�����µ��Ĳ����������á�
                                                                    00��0.5dB��
                                                                    01��1dB��
                                                                    10��1.5dB��
                                                                    11��2dB�� */
        unsigned int  dacl_agc_timemute_config : 2;  /* bit[6-7]  : AGC�����ȴ�ʱ�����á�
                                                                    ����Ƶ��Ϊ48KHz��
                                                                    00��187.5ms��
                                                                    01��375ms��
                                                                    10��750ms��
                                                                    11��1.5s��
                                                                    ����Ƶ��Ϊ96KHz��
                                                                    00��N/A��
                                                                    01��187.5ms��
                                                                    10��375ms��
                                                                    11��750ms��  */
        unsigned int  dacl_agc_ngw_config      : 2;  /* bit[8-9]  : AGC�����жϳ������洰���á�
                                                                    00��0dB��
                                                                    01��1dB��
                                                                    10��2dB��
                                                                    11��4dB�� */
        unsigned int  dacl_agc_ytarget_config  : 3;  /* bit[10-12]: AGC����ź�Ŀ������������á�
                                                                    000��-4dB��
                                                                    001��-6dB��
                                                                    010��-9dB��
                                                                    011��-12dB��
                                                                    100��-15dB��
                                                                    101��-18dB��
                                                                    110��-21dB��
                                                                    111��-24dB�� */
        unsigned int  dacl_agc_t_amin_config   : 2;  /* bit[13-14]: AGC�����µ�����Сʱ�������á�
                                                                    ����Ƶ��Ϊ48KHz��
                                                                    00��1/24ms��
                                                                    01��0.125ms��
                                                                    10��0.75ms��
                                                                    11��1.5ms��
                                                                    ����Ƶ��Ϊ96KHz��
                                                                    00��1/48ms��
                                                                    01��0.0625ms��
                                                                    10��0.375ms��
                                                                    11��0.75ms�� */
        unsigned int  dacl_agc_gsuppress       : 1;  /* bit[15]   : AGC����ѹ��ʹ�ܱ�־���á�
                                                                    0����ѹ����
                                                                    1��ѹ���� */
        unsigned int  dacl_agc_kfslow          : 2;  /* bit[16-17]: AGC�а����������½�����ѡ��
                                                                    00��ѡ��1/2^(10)���ʣ�
                                                                    01��ѡ��1/2^(11)���ʣ�
                                                                    10��ѡ��1/2^(12)���ʣ�
                                                                    11��ѡ��1/2^(13)���ʡ� */
        unsigned int  dacl_agc_kfrapid         : 2;  /* bit[18-19]: AGC�а���������½�����ѡ��
                                                                    00��ѡ��1/2^(6)���ʣ�
                                                                    01��ѡ��1/2^(7)���ʣ�
                                                                    10��ѡ��1/2^(8)���ʣ�
                                                                    11��ѡ��1/2^(9)���ʡ� */
        unsigned int  dacl_agc_ngl_config      : 2;  /* bit[20-21]: AGC������ֵ���ֵ���á�
                                                                    00������������ֵ��ʼֵ���ã�
                                                                    01������������ֵ��ʼֵ���ü�ȥ6dB��
                                                                    10������������ֵ��ʼֵ���ü�ȥ18dB��
                                                                    11������-90dB�� */
        unsigned int  dacl_agc_ngh_config      : 2;  /* bit[22-23]: AGC������ֵ���ֵ���á�
                                                                    00������������ֵ��ʼֵ���ã�
                                                                    01������������ֵ��ʼֵ���ü�12dB��
                                                                    10������������ֵ��ʼֵ���ü�18dB��
                                                                    11������-24dB�� */
        unsigned int  dacl_agc_timer           : 3;  /* bit[24-26]: AGCʱ��ѡ�����á�
                                                                    ����Ƶ��Ϊ48KHzʱ��
                                                                    000��96���������ڣ�
                                                                    001��192���������ڣ�
                                                                    010��384���������ڣ�
                                                                    b011��768���������ڣ�
                                                                    100��1536���������ڣ�
                                                                    101��3072���������ڣ�
                                                                    110��6144���������ڣ�
                                                                    111��12288���������ڡ�
                                                                    ����Ƶ��Ϊ96KHzʱ��
                                                                    000��N/A��
                                                                    001��96���������ڣ�
                                                                    010��192���������ڣ�
                                                                    011��384���������ڣ�
                                                                    100��768���������ڣ�
                                                                    101��1536���������ڣ�
                                                                    110��3072���������ڣ�
                                                                    111��6144���������ڡ� */
        unsigned int  dacl_agc_ngi_config      : 3;  /* bit[27-29]: AGC������ֵ��ʼֵ�������ã����淶Χ��-72dB~-36dB������Ϊ6dB��
                                                                    000��-72dB��
                                                                    001��-66dB��
                                                                    010��-60dB��
                                                                    011��-54dB��
                                                                    100��-51dB��
                                                                    101��-48dB��
                                                                    110��-42dB��
                                                                    111��-36dB�� */
        unsigned int  dacl_agc_timenng_config  : 2;  /* bit[30-31]: AGC������ֵ����ʱ�����á�
                                                                    ����Ƶ��Ϊ48KHz��
                                                                    00��ʱ��ѡ�����õ�1.5����
                                                                    01��ʱ��ѡ�����õ�2����
                                                                    10��ʱ��ѡ�����õ�4����
                                                                    11��ѡ��2�롣
                                                                    ����Ƶ��Ϊ96KHz��
                                                                    00��ʱ��ѡ�����õ�1.5����
                                                                    01��ʱ��ѡ�����õ�2����
                                                                    10��ʱ��ѡ�����õ�4����
                                                                    11��ѡ��1�� */
    } reg;
} SOC_ASP_CODEC_DACL_AGC_CFG_1_UNION;
#endif
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_gwin_config_START      (0)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_gwin_config_END        (1)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_levellow_config_START  (2)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_levellow_config_END    (3)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_gstepd_config_START    (4)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_gstepd_config_END      (5)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_timemute_config_START  (6)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_timemute_config_END    (7)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_ngw_config_START       (8)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_ngw_config_END         (9)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_ytarget_config_START   (10)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_ytarget_config_END     (12)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_t_amin_config_START    (13)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_t_amin_config_END      (14)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_gsuppress_START        (15)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_gsuppress_END          (15)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_kfslow_START           (16)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_kfslow_END             (17)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_kfrapid_START          (18)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_kfrapid_END            (19)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_ngl_config_START       (20)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_ngl_config_END         (21)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_ngh_config_START       (22)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_ngh_config_END         (23)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_timer_START            (24)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_timer_END              (26)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_ngi_config_START       (27)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_ngi_config_END         (29)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_timenng_config_START   (30)
#define SOC_ASP_CODEC_DACL_AGC_CFG_1_dacl_agc_timenng_config_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_DACL_AGC_CFG_2_UNION
 �ṹ˵��  : DACL_AGC_CFG_2 �Ĵ����ṹ���塣��ַƫ����:0x50����ֵ:0x00000059�����:32
 �Ĵ���˵��: DACL AGC (�Զ��������)���üĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dacl_agc_timedecay_config : 2;  /* bit[0-1]  : AGCÿ���ϵ������ʱ�������á�
                                                                     ����Ƶ��Ϊ48KHz��
                                                                     00��ʱ��ѡ�����õ�1/4��
                                                                     01��ʱ��ѡ�����õ�1/8��
                                                                     10��ʱ��ѡ�����õ�1/16��
                                                                     11��0.25ms��
                                                                     ����Ƶ��Ϊ96KHz��
                                                                     00��ʱ��ѡ�����õ�1/4��
                                                                     01��ʱ��ѡ�����õ�1/8��
                                                                     10��ʱ��ѡ�����õ�1/16��
                                                                     11��0.125ms�� */
        unsigned int  dacl_agc_timeghold_config : 2;  /* bit[2-3]  : AGC�����ϵ�֮ǰ�ĵȴ�ʱ�����á�
                                                                     00��ʱ��ѡ�����õ�1/8��
                                                                     01��ʱ��ѡ�����õ�1/4��
                                                                     10��ʱ��ѡ�����õ�1/2��
                                                                     11��ʱ��ѡ�����õ�3/4�� */
        unsigned int  dacl_agc_gmute_config     : 2;  /* bit[4-5]  : AGC����״̬�µ��������á�
                                                                     00��0dB��
                                                                     01��-12dB��
                                                                     10��-24dB��
                                                                     11��-42dB�� */
        unsigned int  dacl_agc_mute_bypass      : 1;  /* bit[6]    : AGC�������ܽ�ֹ��־���á�
                                                                     0��AGC Muteʹ�ܣ�
                                                                     1��AGC Mute bypass */
        unsigned int  dacl_agc_bypass           : 1;  /* bit[7]    : AGC����bypassʹ���źš�
                                                                     1��AGC���ܽ�ֹ��
                                                                     0�������Զ�������ơ� */
        unsigned int  dacl_agc_usr_gdb_integer  : 8;  /* bit[8-15] : AGC����bypassʱ���û�������������ϵ������dB�˷���һ����Ϊ����λ���á�
                                                                     Ĭ�ϣ�0dB����ͨ�������ģ������淶Χ��-72dB��+36dB������
                                                                     0010_0100��36dB��
                                                                     0010_0011��35dB��
                                                                     ����
                                                                     1011_1000��-72dB��
                                                                     ����Ϊ1dB�������ʾ�� */
        unsigned int  dacl_agc_usr_gdb_frac     : 1;  /* bit[16]   : DACL AGC�û���������С��λ���á�
                                                                     0��0.0dB��
                                                                     1��0.5dB�� */
        unsigned int  dacl_agc_sw_clr           : 1;  /* bit[17]   : DACLͨ��AGC��λ���á�
                                                                     0����Ч�� 
                                                                     1����λ�� */
        unsigned int  reserved                  : 14; /* bit[18-31]: reserved */
    } reg;
} SOC_ASP_CODEC_DACL_AGC_CFG_2_UNION;
#endif
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_timedecay_config_START  (0)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_timedecay_config_END    (1)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_timeghold_config_START  (2)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_timeghold_config_END    (3)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_gmute_config_START      (4)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_gmute_config_END        (5)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_mute_bypass_START       (6)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_mute_bypass_END         (6)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_bypass_START            (7)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_bypass_END              (7)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_usr_gdb_integer_START   (8)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_usr_gdb_integer_END     (15)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_usr_gdb_frac_START      (16)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_usr_gdb_frac_END        (16)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_sw_clr_START            (17)
#define SOC_ASP_CODEC_DACL_AGC_CFG_2_dacl_agc_sw_clr_END              (17)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_DACR_AGC_CFG_1_UNION
 �ṹ˵��  : DACR_AGC_CFG_1 �Ĵ����ṹ���塣��ַƫ����:0x54����ֵ:0x249AAE51�����:32
 �Ĵ���˵��: DACR AGC (�Զ��������)���üĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dacr_agc_gwin_config     : 2;  /* bit[0-1]  : AGC�����µ���ƽ�����������á�
                                                                    00��3.5dB��
                                                                    01��5.5dB��
                                                                    10��9dB��
                                                                    11��15dB�� */
        unsigned int  dacr_agc_levellow_config : 2;  /* bit[2-3]  : AGC�͵�ƽ�����������á�
                                                                    00��-60dB��
                                                                    01��-72dB��
                                                                    10��-90dB��
                                                                    11��-120dB�� */
        unsigned int  dacr_agc_gstepd_config   : 2;  /* bit[4-5]  : AGC�����µ��Ĳ����������á�
                                                                    00��0.5dB��
                                                                    01��1dB��
                                                                    10��1.5dB��
                                                                    11��2dB�� */
        unsigned int  dacr_agc_timemute_config : 2;  /* bit[6-7]  : AGC�����ȴ�ʱ�����á�
                                                                    ����Ƶ��Ϊ48KHz��
                                                                    00��187.5ms��
                                                                    01��375ms��
                                                                    10��750ms��
                                                                    11��1.5s��
                                                                    ����Ƶ��Ϊ96KHz��
                                                                    00��N/A��
                                                                    01��187.5ms��
                                                                    10��375ms��
                                                                    11��750ms��  */
        unsigned int  dacr_agc_ngw_config      : 2;  /* bit[8-9]  : AGC�����жϳ������洰���á�
                                                                    00��0dB��
                                                                    01��1dB��
                                                                    10��2dB��
                                                                    11��4dB�� */
        unsigned int  dacr_agc_ytarget_config  : 3;  /* bit[10-12]: AGC����ź�Ŀ������������á�
                                                                    000��-4dB��
                                                                    001��-6dB��
                                                                    010��-9dB��
                                                                    011��-12dB��
                                                                    100��-15dB��
                                                                    101��-18dB��
                                                                    110��-21dB��
                                                                    111��-24dB�� */
        unsigned int  dacr_agc_t_amin_config   : 2;  /* bit[13-14]: AGC�����µ�����Сʱ�������á�
                                                                    ����Ƶ��Ϊ48KHz��
                                                                    00��1/24ms��
                                                                    01��0.125ms��
                                                                    10��0.75ms��
                                                                    11��1.5ms��
                                                                    ����Ƶ��Ϊ96KHz��
                                                                    00��1/48ms��
                                                                    01��0.0625ms��
                                                                    10��0.375ms��
                                                                    11��0.75ms�� */
        unsigned int  dacr_agc_gsuppress       : 1;  /* bit[15]   : AGC����ѹ��ʹ�ܱ�־���á�
                                                                    0����ѹ����
                                                                    1��ѹ���� */
        unsigned int  dacr_agc_kfslow          : 2;  /* bit[16-17]: AGC�а����������½�����ѡ��
                                                                    00��ѡ��1/2^(10)���ʣ�
                                                                    01��ѡ��1/2^(11)���ʣ�
                                                                    10��ѡ��1/2^(12)���ʣ�
                                                                    11��ѡ��1/2^(13)���ʡ� */
        unsigned int  dacr_agc_kfrapid         : 2;  /* bit[18-19]: AGC�а���������½�����ѡ��
                                                                    00��ѡ��1/2^(6)���ʣ�
                                                                    01��ѡ��1/2^(7)���ʣ�
                                                                    10��ѡ��1/2^(8)���ʣ�
                                                                    11��ѡ��1/2^(9)���ʡ� */
        unsigned int  dacr_agc_ngl_config      : 2;  /* bit[20-21]: AGC������ֵ���ֵ���á�
                                                                    00������������ֵ��ʼֵ���ã�
                                                                    01������������ֵ��ʼֵ���ü�ȥ6dB��
                                                                    10������������ֵ��ʼֵ���ü�ȥ18dB��
                                                                    11������-90dB�� */
        unsigned int  dacr_agc_ngh_config      : 2;  /* bit[22-23]: AGC������ֵ���ֵ���á�
                                                                    00������������ֵ��ʼֵ���ã�
                                                                    01������������ֵ��ʼֵ���ü�12dB��
                                                                    10������������ֵ��ʼֵ���ü�18dB��
                                                                    11������-24dB�� */
        unsigned int  dacr_agc_timer           : 3;  /* bit[24-26]: AGCʱ��ѡ�����á�
                                                                    ����Ƶ��Ϊ48KHzʱ��
                                                                    000��96���������ڣ�
                                                                    001��192���������ڣ�
                                                                    010��384���������ڣ�
                                                                    b011��768���������ڣ�
                                                                    100��1536���������ڣ�
                                                                    101��3072���������ڣ�
                                                                    110��6144���������ڣ�
                                                                    111��12288���������ڡ�
                                                                    ����Ƶ��Ϊ96KHzʱ��
                                                                    000��N/A��
                                                                    001��96���������ڣ�
                                                                    010��192���������ڣ�
                                                                    011��384���������ڣ�
                                                                    100��768���������ڣ�
                                                                    101��1536���������ڣ�
                                                                    110��3072���������ڣ�
                                                                    111��6144���������ڡ� */
        unsigned int  dacr_agc_ngi_config      : 3;  /* bit[27-29]: AGC������ֵ��ʼֵ�������ã����淶Χ��-72dB~-36dB������Ϊ6dB��
                                                                    000��-72dB��
                                                                    001��-66dB��
                                                                    010��-60dB��
                                                                    011��-54dB��
                                                                    100��-51dB��
                                                                    101��-48dB��
                                                                    110��-42dB��
                                                                    111��-36dB�� */
        unsigned int  dacr_agc_timenng_config  : 2;  /* bit[30-31]: AGC������ֵ����ʱ�����á�
                                                                    ����Ƶ��Ϊ48KHz��
                                                                    00��ʱ��ѡ�����õ�1.5����
                                                                    01��ʱ��ѡ�����õ�2����
                                                                    10��ʱ��ѡ�����õ�4����
                                                                    11��ѡ��2�롣
                                                                    ����Ƶ��Ϊ96KHz��
                                                                    00��ʱ��ѡ�����õ�1.5����
                                                                    01��ʱ��ѡ�����õ�2����
                                                                    10��ʱ��ѡ�����õ�4����
                                                                    11��ѡ��1�� */
    } reg;
} SOC_ASP_CODEC_DACR_AGC_CFG_1_UNION;
#endif
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_gwin_config_START      (0)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_gwin_config_END        (1)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_levellow_config_START  (2)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_levellow_config_END    (3)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_gstepd_config_START    (4)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_gstepd_config_END      (5)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_timemute_config_START  (6)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_timemute_config_END    (7)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_ngw_config_START       (8)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_ngw_config_END         (9)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_ytarget_config_START   (10)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_ytarget_config_END     (12)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_t_amin_config_START    (13)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_t_amin_config_END      (14)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_gsuppress_START        (15)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_gsuppress_END          (15)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_kfslow_START           (16)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_kfslow_END             (17)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_kfrapid_START          (18)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_kfrapid_END            (19)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_ngl_config_START       (20)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_ngl_config_END         (21)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_ngh_config_START       (22)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_ngh_config_END         (23)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_timer_START            (24)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_timer_END              (26)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_ngi_config_START       (27)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_ngi_config_END         (29)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_timenng_config_START   (30)
#define SOC_ASP_CODEC_DACR_AGC_CFG_1_dacr_agc_timenng_config_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_DACR_AGC_CFG_2_UNION
 �ṹ˵��  : DACR_AGC_CFG_2 �Ĵ����ṹ���塣��ַƫ����:0x58����ֵ:0x00000059�����:32
 �Ĵ���˵��: DACR AGC (�Զ��������)���üĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dacr_agc_timedecay_config : 2;  /* bit[0-1]  : AGCÿ���ϵ������ʱ�������á�
                                                                     ����Ƶ��Ϊ48KHz��
                                                                     00��ʱ��ѡ�����õ�1/4��
                                                                     01��ʱ��ѡ�����õ�1/8��
                                                                     10��ʱ��ѡ�����õ�1/16��
                                                                     11��0.25ms��
                                                                     ����Ƶ��Ϊ96KHz��
                                                                     00��ʱ��ѡ�����õ�1/4��
                                                                     01��ʱ��ѡ�����õ�1/8��
                                                                     10��ʱ��ѡ�����õ�1/16��
                                                                     11��0.125ms�� */
        unsigned int  dacr_agc_timeghold_config : 2;  /* bit[2-3]  : AGC�����ϵ�֮ǰ�ĵȴ�ʱ�����á�
                                                                     00��ʱ��ѡ�����õ�1/8��
                                                                     01��ʱ��ѡ�����õ�1/4��
                                                                     10��ʱ��ѡ�����õ�1/2��
                                                                     11��ʱ��ѡ�����õ�3/4�� */
        unsigned int  dacr_agc_gmute_config     : 2;  /* bit[4-5]  : AGC����״̬�µ��������á�
                                                                     00��0dB��
                                                                     01��-12dB��
                                                                     10��-24dB��
                                                                     11��-42dB�� */
        unsigned int  dacr_agc_mute_bypass      : 1;  /* bit[6]    : AGC�������ܽ�ֹ��־���á�
                                                                     0��AGC Muteʹ�ܣ�
                                                                     1��AGC Mute bypass */
        unsigned int  dacr_agc_bypass           : 1;  /* bit[7]    : AGC����bypassʹ���źš�
                                                                     1��AGC���ܽ�ֹ��
                                                                     0�������Զ�������ơ� */
        unsigned int  dacr_agc_usr_gdb_integer  : 8;  /* bit[8-15] : AGC����bypassʱ���û�������������ϵ������dB�˷���һ����Ϊ����λ���á�
                                                                     Ĭ�ϣ�0dB����ͨ�������ģ������淶Χ��-72dB��+36dB������
                                                                     0010_0100��36dB��
                                                                     0010_0011��35dB��
                                                                     ����
                                                                     1011_1000��-72dB��
                                                                     ����Ϊ1dB�������ʾ�� */
        unsigned int  dacr_agc_usr_gdb_frac     : 1;  /* bit[16]   : DACR AGC�û���������С��λ���á�
                                                                     0��0.0dB��
                                                                     1��0.5dB�� */
        unsigned int  dacr_agc_sw_clr           : 1;  /* bit[17]   : DACRͨ��AGC��λ���á�
                                                                     0����Ч�� 
                                                                     1����λ�� */
        unsigned int  reserved                  : 14; /* bit[18-31]: reserved */
    } reg;
} SOC_ASP_CODEC_DACR_AGC_CFG_2_UNION;
#endif
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_timedecay_config_START  (0)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_timedecay_config_END    (1)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_timeghold_config_START  (2)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_timeghold_config_END    (3)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_gmute_config_START      (4)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_gmute_config_END        (5)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_mute_bypass_START       (6)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_mute_bypass_END         (6)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_bypass_START            (7)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_bypass_END              (7)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_usr_gdb_integer_START   (8)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_usr_gdb_integer_END     (15)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_usr_gdb_frac_START      (16)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_usr_gdb_frac_END        (16)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_sw_clr_START            (17)
#define SOC_ASP_CODEC_DACR_AGC_CFG_2_dacr_agc_sw_clr_END              (17)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_DMIC_SIF_CFG_UNION
 �ṹ˵��  : DMIC_SIF_CFG �Ĵ����ṹ���塣��ַƫ����:0x5C����ֵ:0x0000000F�����:32
 �Ĵ���˵��: DMIC�ӿں�Serial�ӿ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sif_adcl_en      : 1;  /* bit[0]    : SIF ADCL����ʹ�ܣ�
                                                            1�����մ��нӿ��ͽ�������
                                                            0������������ */
        unsigned int  sif_adcr_en      : 1;  /* bit[1]    : SIF ADCR����ʹ�ܣ�
                                                            1�����մ��нӿ��ͽ�������
                                                            0������������ */
        unsigned int  sif_dacl_en      : 1;  /* bit[2]    : SIF DACL����ʹ�ܣ�
                                                            1�����нӿڷ�������
                                                            0������������ */
        unsigned int  sif_dacr_en      : 1;  /* bit[3]    : SIF DACR����ʹ�ܣ�
                                                            1�����нӿڷ�������
                                                            0������������ */
        unsigned int  dac_p2s_loopback : 1;  /* bit[4]    : SIF ���ݻ��أ�
                                                            1��ADC����������ص�DAC�Ĳ�������
                                                            0�������� */
        unsigned int  sif_s2p_loopback : 1;  /* bit[5]    : SIF����������ݻ���ʹ�ܣ�
                                                            1��DAC����������ص�ADC��������
                                                            0�������� */
        unsigned int  sif_edge_sel     : 1;  /* bit[6]    : sifģ��ʱ����ѡ��
                                                            1'b1: SIFʱ���������49.152Mʱ�ӷ���
                                                            1'b0: SIFʱ���������49.152Mʱ��ͬ�� */
        unsigned int  sif_en           : 1;  /* bit[7]    : ��smartStar�ӿ�ʹ�ܣ�
                                                            0���ر�ʱ��
                                                            1����ʱ�� */
        unsigned int  reserved_0       : 8;  /* bit[8-15] : reserved */
        unsigned int  sw_dmic_mode     : 1;  /* bit[16]   : DMIC�������á� 
                                                            0������������������ 
                                                            1���������������� */
        unsigned int  dmic_reverse     : 1;  /* bit[17]   : DMIC����������á� 
                                                            0��0 -> -4, 1 -> +4�� 
                                                            1��0 -> +4, 1 -> -4�� */
        unsigned int  fs_dmic          : 2;  /* bit[18-19]: DMICʱ�����á�
                                                            2'b00���ر�ʱ�ӣ�
                                                            2'b01��2��Ƶ��
                                                            2'b10��3��Ƶ��
                                                            2'b11��4��Ƶ�� */
        unsigned int  dmic_en          : 1;  /* bit[20]   : DMIC�ӿ�ʹ�ܣ�
                                                            0���ر�ʱ��
                                                            1����ʱ�� */
        unsigned int  reserved_1       : 11; /* bit[21-31]: reserved */
    } reg;
} SOC_ASP_CODEC_DMIC_SIF_CFG_UNION;
#endif
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_adcl_en_START       (0)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_adcl_en_END         (0)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_adcr_en_START       (1)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_adcr_en_END         (1)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_dacl_en_START       (2)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_dacl_en_END         (2)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_dacr_en_START       (3)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_dacr_en_END         (3)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_dac_p2s_loopback_START  (4)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_dac_p2s_loopback_END    (4)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_s2p_loopback_START  (5)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_s2p_loopback_END    (5)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_edge_sel_START      (6)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_edge_sel_END        (6)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_en_START            (7)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sif_en_END              (7)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sw_dmic_mode_START      (16)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_sw_dmic_mode_END        (16)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_dmic_reverse_START      (17)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_dmic_reverse_END        (17)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_fs_dmic_START           (18)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_fs_dmic_END             (19)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_dmic_en_START           (20)
#define SOC_ASP_CODEC_DMIC_SIF_CFG_dmic_en_END             (20)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_MISC_CFG_UNION
 �ṹ˵��  : MISC_CFG �Ĵ����ṹ���塣��ַƫ����:0x60����ֵ:0x00000000�����:32
 �Ĵ���˵��: Misc Config
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s2_dout_left_sel                : 1;  /* bit[0]    : S2�ӿڣ�BT�ӿڣ������ͨ��������ݵ�һ��ѡ��MUX6��
                                                                           1'b1: ѡ��voice dlinkͨ��pga�����
                                                                           1'b0: ѡ�񽵲���SRC3����� */
        unsigned int  s1_dout_test_sel                : 1;  /* bit[1]    : S1���ͨ������ѡ������������������ƣ�MUX8/MUX9��
                                                                           1'b1: ������ѡ��adcl�����˲���ͨ�������������ѡ��adcr�����˲���ͨ�����
                                                                           1'b0: ������ѡ��DACL MIXER�����������ѡ��DACR MIXER����� */
        unsigned int  s2_dout_test_sel                : 1;  /* bit[2]    : S2�ӿڣ�BT�ӿڣ����ͨ��������ݵڶ���ѡ�񣬸ı������������MUX7��
                                                                           1'b1: ѡ��DACL MIXER�����
                                                                           1'b0: ѡ����·�����ݣ�voice dlink pga����S2������������� */
        unsigned int  s2_dout_right_sel               : 1;  /* bit[3]    : S2�ӿڣ�BT�ӿڣ������ͨ���������ѡ��
                                                                           1'b1: 0��
                                                                           1'b0: ѡ��DACRͨ��Mixer����� */
        unsigned int  stereo_dlink_test_sel           : 1;  /* bit[4]    : STEREO DLINKͨ����������ѡ��MUX11/MUX12��
                                                                           1'b0:������APB����
                                                                           1'b1:S1�ӿ�����������stereo_dlink_l ,S1�ӿ�����������stereo_dlink_r */
        unsigned int  reserved_0                      : 1;  /* bit[5]    : reserved */
        unsigned int  voice_dlink_din_sel             : 1;  /* bit[6]    : VOICE DLINKͨ����������ѡ��
                                                                           1'b0:������APB����
                                                                           1'b1:S3�ӿ����������� */
        unsigned int  voice_dlink_test_sel            : 1;  /* bit[7]    : VOICE DLINKͨ����������ѡ��MUX10��
                                                                           1'b0:������ǰ��ѡ�����(ȡ����voice_dlink_din_sel����)
                                                                           1'b1:S2�ӿ����������� */
        unsigned int  voice_dlink_src_up_dout_vld_sel : 1;  /* bit[8]    : VOICE����ͨ��SRCģ�����������ѡ��
                                                                           1'b1: ���Ϊ96kHz
                                                                           1'b0: ���Ϊ48kHz */
        unsigned int  reserved_1                      : 3;  /* bit[9-11] : reserved */
        unsigned int  s3_din_test_sel                 : 1;  /* bit[12]   : s3����ѡ��
                                                                           1'b0: ѡ��Left������
                                                                           1'b1: ѡ��Right������ */
        unsigned int  s3_dout_left_sel                : 1;  /* bit[13]   : S3�ӿ������ͨ��ѡ���źţ�
                                                                           1'b0: thirdmd dlink pga�����
                                                                           1'b1: adclͨ��pga��� */
        unsigned int  s3_dout_right_sel               : 2;  /* bit[14-15]: S3�ӿ������ͨ��ѡ���źţ�
                                                                           2'b00: thirdmd dlink pga�����
                                                                           2'b01: adcrͨ��pga���;
                                                                           other: 0; */
        unsigned int  thirdmd_dlink_din_sel           : 1;  /* bit[16]   : thirdmd_dlinkͨ����������ѡ�����룺
                                                                           1'b0: APB thirdmd����ͨ��
                                                                           1'b1: S2���������� */
        unsigned int  thirdmd_dlink_test_sel          : 1;  /* bit[17]   : thirdmd_dlinkͨ����������ѡ�����룺
                                                                           1'b0: ��APB thirdmd����ͨ����S2������ѡ��
                                                                           1'b1: S3���� */
        unsigned int  reserved_2                      : 14; /* bit[18-31]: reserved */
    } reg;
} SOC_ASP_CODEC_MISC_CFG_UNION;
#endif
#define SOC_ASP_CODEC_MISC_CFG_s2_dout_left_sel_START                 (0)
#define SOC_ASP_CODEC_MISC_CFG_s2_dout_left_sel_END                   (0)
#define SOC_ASP_CODEC_MISC_CFG_s1_dout_test_sel_START                 (1)
#define SOC_ASP_CODEC_MISC_CFG_s1_dout_test_sel_END                   (1)
#define SOC_ASP_CODEC_MISC_CFG_s2_dout_test_sel_START                 (2)
#define SOC_ASP_CODEC_MISC_CFG_s2_dout_test_sel_END                   (2)
#define SOC_ASP_CODEC_MISC_CFG_s2_dout_right_sel_START                (3)
#define SOC_ASP_CODEC_MISC_CFG_s2_dout_right_sel_END                  (3)
#define SOC_ASP_CODEC_MISC_CFG_stereo_dlink_test_sel_START            (4)
#define SOC_ASP_CODEC_MISC_CFG_stereo_dlink_test_sel_END              (4)
#define SOC_ASP_CODEC_MISC_CFG_voice_dlink_din_sel_START              (6)
#define SOC_ASP_CODEC_MISC_CFG_voice_dlink_din_sel_END                (6)
#define SOC_ASP_CODEC_MISC_CFG_voice_dlink_test_sel_START             (7)
#define SOC_ASP_CODEC_MISC_CFG_voice_dlink_test_sel_END               (7)
#define SOC_ASP_CODEC_MISC_CFG_voice_dlink_src_up_dout_vld_sel_START  (8)
#define SOC_ASP_CODEC_MISC_CFG_voice_dlink_src_up_dout_vld_sel_END    (8)
#define SOC_ASP_CODEC_MISC_CFG_s3_din_test_sel_START                  (12)
#define SOC_ASP_CODEC_MISC_CFG_s3_din_test_sel_END                    (12)
#define SOC_ASP_CODEC_MISC_CFG_s3_dout_left_sel_START                 (13)
#define SOC_ASP_CODEC_MISC_CFG_s3_dout_left_sel_END                   (13)
#define SOC_ASP_CODEC_MISC_CFG_s3_dout_right_sel_START                (14)
#define SOC_ASP_CODEC_MISC_CFG_s3_dout_right_sel_END                  (15)
#define SOC_ASP_CODEC_MISC_CFG_thirdmd_dlink_din_sel_START            (16)
#define SOC_ASP_CODEC_MISC_CFG_thirdmd_dlink_din_sel_END              (16)
#define SOC_ASP_CODEC_MISC_CFG_thirdmd_dlink_test_sel_START           (17)
#define SOC_ASP_CODEC_MISC_CFG_thirdmd_dlink_test_sel_END             (17)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_S2_SRC_CFG_UNION
 �ṹ˵��  : S2_SRC_CFG �Ĵ����ṹ���塣��ַƫ����:0x64����ֵ:0x00000000�����:32
 �Ĵ���˵��: S2�ӿ�SRCģ������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s2_il_src_up_en        : 1;  /* bit[0]   : S2�ӿ�������ͨ��SRC�������˲���ʱ���źţ�
                                                                 1'b1��ʱ��ʹ�ܣ�
                                                                 1'b0��bypass */
        unsigned int  s2_il_src_down_en      : 1;  /* bit[1]   : S2�ӿ�������ͨ��SRC�������˲���ʱ���źţ�
                                                                 1'b1��ʱ��ʹ�ܣ�
                                                                 1'b0��bypass */
        unsigned int  s2_ir_src_up_en        : 1;  /* bit[2]   : S2�ӿ�������ͨ��SRC�������˲���ʱ���źţ�
                                                                 1'b1��ʱ��ʹ�ܣ�
                                                                 1'b0��bypass */
        unsigned int  s2_ir_src_down_en      : 1;  /* bit[3]   : S2�ӿ�������ͨ��SRC�������˲���ʱ���źţ�
                                                                 1'b1��ʱ��ʹ�ܣ�
                                                                 1'b0��bypass */
        unsigned int  s2_il_src_up_src_rdy   : 1;  /* bit[4]   : S2 I2S�ӿ�������ͨ��SRC������ģ��READY�źţ�
                                                                 1'b1:SRC RAM��ʼ�����
                                                                 1'b0:SRC RAM��ʼ�������� */
        unsigned int  s2_il_src_down_src_rdy : 1;  /* bit[5]   : S2 I2S�ӿ�������ͨ��SRC������ģ��READY�źţ�
                                                                 1'b1:SRC RAM��ʼ�����
                                                                 1'b0:SRC RAM��ʼ�������� */
        unsigned int  s2_ir_src_up_src_rdy   : 1;  /* bit[6]   : S2 I2S�ӿ�������ͨ��SRC������ģ��READY�źţ�
                                                                 1'b1:SRC RAM��ʼ�����
                                                                 1'b0:SRC RAM��ʼ�������� */
        unsigned int  s2_ir_src_down_src_rdy : 1;  /* bit[7]   : S2 I2S�ӿ�������ͨ��SRC������ģ��READY�źţ�
                                                                 1'b1:SRC RAM��ʼ�����
                                                                 1'b0:SRC RAM��ʼ�������� */
        unsigned int  reserved               : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_ASP_CODEC_S2_SRC_CFG_UNION;
#endif
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_il_src_up_en_START         (0)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_il_src_up_en_END           (0)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_il_src_down_en_START       (1)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_il_src_down_en_END         (1)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_ir_src_up_en_START         (2)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_ir_src_up_en_END           (2)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_ir_src_down_en_START       (3)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_ir_src_down_en_END         (3)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_il_src_up_src_rdy_START    (4)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_il_src_up_src_rdy_END      (4)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_il_src_down_src_rdy_START  (5)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_il_src_down_src_rdy_END    (5)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_ir_src_up_src_rdy_START    (6)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_ir_src_up_src_rdy_END      (6)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_ir_src_down_src_rdy_START  (7)
#define SOC_ASP_CODEC_S2_SRC_CFG_s2_ir_src_down_src_rdy_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_MEM_CFG_UNION
 �ṹ˵��  : MEM_CFG �Ĵ����ṹ���塣��ַƫ����:0x68����ֵ:0x01A800A8�����:32
 �Ĵ���˵��: memory�����ź�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mem_ctrl_s     : 16; /* bit[0-15] : SRC�е���memory�����ź� */
        unsigned int  mem_ctrl_d1w2r : 16; /* bit[16-31]: AFIFO��˫��memory�����ź� */
    } reg;
} SOC_ASP_CODEC_MEM_CFG_UNION;
#endif
#define SOC_ASP_CODEC_MEM_CFG_mem_ctrl_s_START      (0)
#define SOC_ASP_CODEC_MEM_CFG_mem_ctrl_s_END        (15)
#define SOC_ASP_CODEC_MEM_CFG_mem_ctrl_d1w2r_START  (16)
#define SOC_ASP_CODEC_MEM_CFG_mem_ctrl_d1w2r_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_UNION
 �ṹ˵��  : THIRDMD_PCM_PGA_CFG �Ĵ����ṹ���塣��ַƫ����:0x6C����ֵ:0x00000320�����:32
 �Ĵ���˵��: ������modem��I2S
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s3_func_mode                     : 3;  /* bit[0-2]  : S1�ӿ�ģʽѡ��
                                                                            3'b000:I2S
                                                                            3'b010:PCM STD
                                                                            3'b011:PCM USER Defined
                                                                            3'b100:Left Justified
                                                                            3'b101:Right Justified
                                                                            ���������� */
        unsigned int  s3_codec_data_format             : 1;  /* bit[3]    : S1�ӿ�Codec ADC/DAC���ݸ�ʽѡ��
                                                                            0����ʾ�����Ʋ��룻
                                                                            1����ʾ�������루binary offset���� */
        unsigned int  s3_rx_clk_sel                    : 1;  /* bit[4]    : S1�ӿ�RX����ʱ��ѡ��
                                                                            1'b0:BCLK�����ؽ�������
                                                                            1'b1:BCLK�½��ؽ������� */
        unsigned int  s3_tx_clk_sel                    : 1;  /* bit[5]    : S1�ӿ�TX����ʱ��ѡ��
                                                                            1'b0:BCLK�����ش������
                                                                            1'b1:BCLK�½��ش������ */
        unsigned int  s3_direct_loop                   : 2;  /* bit[6-7]  : S1 I2S�ӿڻ���ģʽѡ��
                                                                            2'b00����������ģʽ��
                                                                            2'b01��Sdin->Sdout��
                                                                            2'b10: RX_DATA[23:0] -> TX_IN[23:0]
                                                                            2'b11: SDOUT -> SDIN */
        unsigned int  s3_codec_io_wordlength           : 2;  /* bit[8-9]  : S1�ӿ�λ�����ơ�
                                                                            00��16bit��
                                                                            01��18bit��
                                                                            10��20bit��
                                                                            11��24bit�� */
        unsigned int  s3_chnnl_mode                    : 1;  /* bit[10]   : S1�ӿ��������ã�
                                                                            1'b0:��������ǰ
                                                                            1'b1:��������ǰ */
        unsigned int  s3_lrclk_mode                    : 1;  /* bit[11]   : S1�ӿ�֡ͬ���ź���������ѡ��
                                                                            1'b0:low -> left channel
                                                                            1'b1:low -> right channel */
        unsigned int  s3_mst_slv                       : 1;  /* bit[12]   : S1�ӿ�Master/Slaveģʽѡ��
                                                                            1'b0:Materģʽ����masterģʽ��BCLK/SYNC�ſ������
                                                                            1'b1:Slaveģʽ */
        unsigned int  s3_frame_mode                    : 1;  /* bit[13]   : S1�ӿ�I2Sģʽ��֡��ʽ���ã�
                                                                            1'b0:I2Sģʽ��64bit frame��PCMģʽ��32bit frame
                                                                            1'b1:I2Sģʽ��32bit frame��PCMģʽ��16bit frame */
        unsigned int  s3_if_rx_ena                     : 1;  /* bit[14]   : S1�ӿ�RX����ʹ�ܣ�
                                                                            1'b1:ʹ��
                                                                            1'b0:�ر� */
        unsigned int  s3_if_tx_ena                     : 1;  /* bit[15]   : S1�ӿ�TX����ʹ�ܣ�
                                                                            1'b1:ʹ��
                                                                            1'b0:�ر� */
        unsigned int  fs_s3                            : 3;  /* bit[16-18]: S1�ӿڲ���������
                                                                            0��8KHz�� 1��16KHz��
                                                                            2��32KHz�� 3������
                                                                            4��48KHz�� 5��96KHz��
                                                                            6��192KHz��7������ */
        unsigned int  reserved                         : 1;  /* bit[19]   : reserved */
        unsigned int  thirdmd_dlink_pga_integer_config : 8;  /* bit[20-27]: ������modem����ͨ�� pga���������������:
                                                                            Ĭ�ϣ�0dB
                                                                            ���淶Χ:-72dB~+36dB��
                                                                            ����
                                                                            0010_0100:36dB
                                                                            0010_0011:35dB
                                                                            ����
                                                                            1011_1000��-72dB
                                                                            ����Ϊ1dB,�����ʾ��
                                                                            �㷨��֧���������淶Χ���ֵ�����÷�Χ���ֵ��ģ����Ϊ����Ԥ�⣬���������á�
                                                                            ����ͨ�����üĴ�������Ϊ0x80��ʵ�־����� */
        unsigned int  thirdmd_dlink_pga_frac_config    : 1;  /* bit[28]   : ������modem����ͨ�� pga��������С��λ���á�
                                                                            0��0.0dB��
                                                                            1��0.5dB�� */
        unsigned int  thirdmd_dlink_pga_mute           : 1;  /* bit[29]   : ������modem����ͨ�� pga muteʹ�ܣ�
                                                                            1'b1: mute��Ч�����0
                                                                            1'b0: �ر�mute */
        unsigned int  thirdmd_dlink_pga_thr_config     : 2;  /* bit[30-31]: ������modem����ͨ�� pga������͵�ƽ�������á� 
                                                                            00��-60dB�� 
                                                                            01��-72dB�� 
                                                                            10��-90dB�� 
                                                                            11��-120dB�� */
    } reg;
} SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_UNION;
#endif
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_func_mode_START                      (0)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_func_mode_END                        (2)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_codec_data_format_START              (3)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_codec_data_format_END                (3)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_rx_clk_sel_START                     (4)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_rx_clk_sel_END                       (4)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_tx_clk_sel_START                     (5)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_tx_clk_sel_END                       (5)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_direct_loop_START                    (6)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_direct_loop_END                      (7)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_codec_io_wordlength_START            (8)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_codec_io_wordlength_END              (9)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_chnnl_mode_START                     (10)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_chnnl_mode_END                       (10)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_lrclk_mode_START                     (11)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_lrclk_mode_END                       (11)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_mst_slv_START                        (12)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_mst_slv_END                          (12)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_frame_mode_START                     (13)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_frame_mode_END                       (13)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_if_rx_ena_START                      (14)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_if_rx_ena_END                        (14)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_if_tx_ena_START                      (15)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_s3_if_tx_ena_END                        (15)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_fs_s3_START                             (16)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_fs_s3_END                               (18)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_thirdmd_dlink_pga_integer_config_START  (20)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_thirdmd_dlink_pga_integer_config_END    (27)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_thirdmd_dlink_pga_frac_config_START     (28)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_thirdmd_dlink_pga_frac_config_END       (28)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_thirdmd_dlink_pga_mute_START            (29)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_thirdmd_dlink_pga_mute_END              (29)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_thirdmd_dlink_pga_thr_config_START      (30)
#define SOC_ASP_CODEC_THIRDMD_PCM_PGA_CFG_thirdmd_dlink_pga_thr_config_END        (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_UNION
 �ṹ˵��  : THIRD_MODEM_FIFO_TH �Ĵ����ṹ���塣��ַƫ����:0x70����ֵ:0x0110101E�����:32
 �Ĵ���˵��: ������Modem����ͨ��AFIFOˮ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thirdmd_dlink_fifo_afull_th   : 5;  /* bit[0-4]  : Third Modem DLINKͨ��AFIFO������ֵ��fifo����Ч��ֵ�������ڸ�ֵʱ��FIFO almost full�ź���Ч */
        unsigned int  reserved_0                    : 3;  /* bit[5-7]  : reserved */
        unsigned int  thirdmd_dlink_fifo_aempty_th  : 5;  /* bit[8-12] : Third Modem DLINKͨ��AFIFO������ֵ��fifo����Ч��ֵ�������ڸ�ֵʱ��FIFO almost empty�ź���Ч */
        unsigned int  reserved_1                    : 3;  /* bit[13-15]: reserved */
        unsigned int  thirdmd_uplink_fifo_afull_th  : 5;  /* bit[16-20]: Third Modem UPLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
        unsigned int  reserved_2                    : 3;  /* bit[21-23]: reserved */
        unsigned int  thirdmd_uplink_fifo_aempty_th : 5;  /* bit[24-28]: Third Modem UPLINK��ͨ��AFIFO������ֵ��ͬ�ϡ� */
        unsigned int  reserved_3                    : 3;  /* bit[29-31]: reserved */
    } reg;
} SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_UNION;
#endif
#define SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_thirdmd_dlink_fifo_afull_th_START    (0)
#define SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_thirdmd_dlink_fifo_afull_th_END      (4)
#define SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_thirdmd_dlink_fifo_aempty_th_START   (8)
#define SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_thirdmd_dlink_fifo_aempty_th_END     (12)
#define SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_thirdmd_uplink_fifo_afull_th_START   (16)
#define SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_thirdmd_uplink_fifo_afull_th_END     (20)
#define SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_thirdmd_uplink_fifo_aempty_th_START  (24)
#define SOC_ASP_CODEC_THIRD_MODEM_FIFO_TH_thirdmd_uplink_fifo_aempty_th_END    (28)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_INC_CNT_UNION
 �ṹ˵��  : S3_ANTI_FREQ_JITTER_TX_INC_CNT �Ĵ����ṹ���塣��ַƫ����:0x74����ֵ:0x00000000�����:32
 �Ĵ���˵��: S3�ӿڿ�Ƶƫģ��TX���������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s3_tx_inc_cnt : 8;  /* bit[0-7] : S3�ӿ�tx�����������������ȡ�����
                                                        �м���ʱ������S3�ӿ�TX���򻺴������ݸ���������ˮ�ߣ���ҪHiFi�������ݸ�������ζ���ⲿʱ�ӿ졣 */
        unsigned int  reserved      : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_INC_CNT_UNION;
#endif
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_INC_CNT_s3_tx_inc_cnt_START  (0)
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_INC_CNT_s3_tx_inc_cnt_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_DEC_CNT_UNION
 �ṹ˵��  : S3_ANTI_FREQ_JITTER_TX_DEC_CNT �Ĵ����ṹ���塣��ַƫ����:0x78����ֵ:0x00000000�����:32
 �Ĵ���˵��: S3�ӿڿ�Ƶƫģ��TX���������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s3_tx_dec_cnt : 8;  /* bit[0-7] : S3�ӿ�tx�����������������ȡ�����
                                                        �м���ʱ������S3�ӿ�TX���򻺴������ݸ���������ˮ�ߣ���ҪHiFi�������ݸ�������ζ���ⲿʱ������ */
        unsigned int  reserved      : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_DEC_CNT_UNION;
#endif
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_DEC_CNT_s3_tx_dec_cnt_START  (0)
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_TX_DEC_CNT_s3_tx_dec_cnt_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_INC_CNT_UNION
 �ṹ˵��  : S3_ANTI_FREQ_JITTER_RX_INC_CNT �Ĵ����ṹ���塣��ַƫ����:0x7C����ֵ:0x00000000�����:32
 �Ĵ���˵��: S3�ӿڿ�Ƶƫģ��RX���������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s3_rx_inc_cnt : 8;  /* bit[0-7] : S3�ӿ�rx�����������������ȡ�����
                                                        �м���ʱ������S3�ӿ�RX���򻺴������ݸ���������ˮ�ߣ���ҪHiFi�������ݸ�������ζ���ⲿʱ�ӿ졣 */
        unsigned int  reserved      : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_INC_CNT_UNION;
#endif
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_INC_CNT_s3_rx_inc_cnt_START  (0)
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_INC_CNT_s3_rx_inc_cnt_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_DEC_CNT_UNION
 �ṹ˵��  : S3_ANTI_FREQ_JITTER_RX_DEC_CNT �Ĵ����ṹ���塣��ַƫ����:0x80����ֵ:0x00000000�����:32
 �Ĵ���˵��: S3�ӿڿ�Ƶƫģ��RX���������
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s3_rx_dec_cnt : 8;  /* bit[0-7] : S3�ӿ�rx�����������������ȡ�����
                                                        �м���ʱ������S3�ӿ�RX���򻺴������ݸ���������ˮ�ߣ���ҪHiFi�������ݸ�������ζ���ⲿʱ������ */
        unsigned int  reserved      : 24; /* bit[8-31]: reserved */
    } reg;
} SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_DEC_CNT_UNION;
#endif
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_DEC_CNT_s3_rx_dec_cnt_START  (0)
#define SOC_ASP_CODEC_S3_ANTI_FREQ_JITTER_RX_DEC_CNT_s3_rx_dec_cnt_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_ANTI_FREQ_JITTER_EN_UNION
 �ṹ˵��  : ANTI_FREQ_JITTER_EN �Ĵ����ṹ���塣��ַƫ����:0x84����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��Ƶƫģ��ʹ��ʹ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  s3_tx_anti_freq_jitter_en : 1;  /* bit[0]   : S3�ӿ�TX����ANTI_FREQ_JITTERģ��ʹ�� */
        unsigned int  s3_rx_anti_freq_jitter_en : 1;  /* bit[1]   : S3�ӿ�RX����ANTI_FREQ_JITTERģ��ʹ�� */
        unsigned int  reserved                  : 30; /* bit[2-31]: reserved */
    } reg;
} SOC_ASP_CODEC_ANTI_FREQ_JITTER_EN_UNION;
#endif
#define SOC_ASP_CODEC_ANTI_FREQ_JITTER_EN_s3_tx_anti_freq_jitter_en_START  (0)
#define SOC_ASP_CODEC_ANTI_FREQ_JITTER_EN_s3_tx_anti_freq_jitter_en_END    (0)
#define SOC_ASP_CODEC_ANTI_FREQ_JITTER_EN_s3_rx_anti_freq_jitter_en_START  (1)
#define SOC_ASP_CODEC_ANTI_FREQ_JITTER_EN_s3_rx_anti_freq_jitter_en_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_CLK_SEL_UNION
 �ṹ˵��  : CLK_SEL �Ĵ����ṹ���塣��ַƫ����:0x88����ֵ:0x00000000�����:32
 �Ĵ���˵��: 12.288Mʱ����Դѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  external_12288k_sel : 1;  /* bit[0-0]  : �ⲿ12.288Mʱ��ѡ��
                                                               1'b1: ѡ��Ƭ������ģ�12.288Mʱ��
                                                               1'b0: ѡ���ڲ���Ƶ������12.288Mʱ�� */
        unsigned int  i2s_bt_fm_sel       : 1;  /* bit[1-1]  : I2S�ӿڸ���ѡ��
                                                               1'b0: ��BT I2S(S2)��;
                                                               1'b1: ��FM I2S(S1)��. */
        unsigned int  reserved            : 14; /* bit[2-15] : reserved */
        unsigned int  dig_rw_01           : 16; /* bit[16-31]: dig_rw_01 */
    } reg;
} SOC_ASP_CODEC_CLK_SEL_UNION;
#endif
#define SOC_ASP_CODEC_CLK_SEL_external_12288k_sel_START  (0)
#define SOC_ASP_CODEC_CLK_SEL_external_12288k_sel_END    (0)
#define SOC_ASP_CODEC_CLK_SEL_i2s_bt_fm_sel_START        (1)
#define SOC_ASP_CODEC_CLK_SEL_i2s_bt_fm_sel_END          (1)
#define SOC_ASP_CODEC_CLK_SEL_dig_rw_01_START            (16)
#define SOC_ASP_CODEC_CLK_SEL_dig_rw_01_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_UPLINK_TEST_SEL_UNION
 �ṹ˵��  : UPLINK_TEST_SEL �Ĵ����ṹ���塣��ַƫ����:0x8C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ·������ͨ·����ѡ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stereo_uplink_r_test_sel  : 1;  /* bit[0]   : Stereo_Right����ͨ��������ͨ������ѡ��
                                                                    1'b0: ѡ��ADCRͨ��������ݡ���S1�ӿ�������������;
                                                                    1'b1: ѡ���sstereo_right_dnlink��stereo_right_uplink�Ļ���ͨ��; */
        unsigned int  stereo_uplink_l_test_sel  : 1;  /* bit[1]   : Stereo_Left����ͨ��������ͨ������ѡ��
                                                                    1'b0: ѡ��ADCLͨ��������ݡ���S1�ӿ�������������;
                                                                    1'b1: ѡ���stereo_left_dnlink��stereo_left_uplink�Ļ���ͨ��; */
        unsigned int  voice_uplink_l_test_sel   : 1;  /* bit[2]   : Voice����ͨ��������ͨ������ѡ��
                                                                    1'b0: ѡ��ADCLͨ��������ݡ���S2�ӿ�������������;
                                                                    1'b1: ѡ���voice_left_dnlink��voice_left_uplink�Ļ���ͨ��; */
        unsigned int  thirdmd_uplink_l_test_sel : 1;  /* bit[3]   : ������Modem����ͨ��������ͨ������ѡ��
                                                                    1'b0: ѡ��S3�ӿ��������ݡ���S1�ӿ���������������
                                                                    1'b1: ѡ��thirdmd_dnlink��thirdmd_uplink�Ļ���ͨ���� */
        unsigned int  smart_pa_fb_sel           : 1;  /* bit[4]   : SmartPA����ͨ·ѡ��
                                                                    1'b0: ѡ��S3�ӿ���������;
                                                                    1'b1: ѡ��S1�ӿ������������� */
        unsigned int  reserved                  : 27; /* bit[5-31]: reserved */
    } reg;
} SOC_ASP_CODEC_UPLINK_TEST_SEL_UNION;
#endif
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_stereo_uplink_r_test_sel_START   (0)
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_stereo_uplink_r_test_sel_END     (0)
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_stereo_uplink_l_test_sel_START   (1)
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_stereo_uplink_l_test_sel_END     (1)
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_voice_uplink_l_test_sel_START    (2)
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_voice_uplink_l_test_sel_END      (2)
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_thirdmd_uplink_l_test_sel_START  (3)
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_thirdmd_uplink_l_test_sel_END    (3)
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_smart_pa_fb_sel_START            (4)
#define SOC_ASP_CODEC_UPLINK_TEST_SEL_smart_pa_fb_sel_END              (4)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_THIRDMD_DLINK_CHANNEL_UNION
 �ṹ˵��  : THIRDMD_DLINK_CHANNEL �Ĵ����ṹ���塣��ַƫ����:0xE8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������Modem����ͨ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thirdmd_dlink_wdata : 32; /* bit[0-31]: ������Modem����ͨ�� */
    } reg;
} SOC_ASP_CODEC_THIRDMD_DLINK_CHANNEL_UNION;
#endif
#define SOC_ASP_CODEC_THIRDMD_DLINK_CHANNEL_thirdmd_dlink_wdata_START  (0)
#define SOC_ASP_CODEC_THIRDMD_DLINK_CHANNEL_thirdmd_dlink_wdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_THIRDMD_UPLINK_CHANNEL_UNION
 �ṹ˵��  : THIRDMD_UPLINK_CHANNEL �Ĵ����ṹ���塣��ַƫ����:0xEC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ������Modem����ͨ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  thirdmd_uplink_rdata : 32; /* bit[0-31]: ������Modem����ͨ�� */
    } reg;
} SOC_ASP_CODEC_THIRDMD_UPLINK_CHANNEL_UNION;
#endif
#define SOC_ASP_CODEC_THIRDMD_UPLINK_CHANNEL_thirdmd_uplink_rdata_START  (0)
#define SOC_ASP_CODEC_THIRDMD_UPLINK_CHANNEL_thirdmd_uplink_rdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_VOICE_DLINK_CHANNEL_UNION
 �ṹ˵��  : VOICE_DLINK_CHANNEL �Ĵ����ṹ���塣��ַƫ����:0xF0����ֵ:0x00000000�����:32
 �Ĵ���˵��: VOICE����ͨ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  voice_dlink_wdata : 32; /* bit[0-31]: VOICE����ͨ�� */
    } reg;
} SOC_ASP_CODEC_VOICE_DLINK_CHANNEL_UNION;
#endif
#define SOC_ASP_CODEC_VOICE_DLINK_CHANNEL_voice_dlink_wdata_START  (0)
#define SOC_ASP_CODEC_VOICE_DLINK_CHANNEL_voice_dlink_wdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_STEREO_DLINK_CHANNEL_UNION
 �ṹ˵��  : STEREO_DLINK_CHANNEL �Ĵ����ṹ���塣��ַƫ����:0xF4����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��Ƶ����ͨ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stereo_dlink_wdata : 32; /* bit[0-31]: ��������������в��� */
    } reg;
} SOC_ASP_CODEC_STEREO_DLINK_CHANNEL_UNION;
#endif
#define SOC_ASP_CODEC_STEREO_DLINK_CHANNEL_stereo_dlink_wdata_START  (0)
#define SOC_ASP_CODEC_STEREO_DLINK_CHANNEL_stereo_dlink_wdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_STEREO_UPLINK_CHANNEL_UNION
 �ṹ˵��  : STEREO_UPLINK_CHANNEL �Ĵ����ṹ���塣��ַƫ����:0xF8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��Ƶ����ͨ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  stereo_uplink_rdata : 32; /* bit[0-31]: ��������������в��� */
    } reg;
} SOC_ASP_CODEC_STEREO_UPLINK_CHANNEL_UNION;
#endif
#define SOC_ASP_CODEC_STEREO_UPLINK_CHANNEL_stereo_uplink_rdata_START  (0)
#define SOC_ASP_CODEC_STEREO_UPLINK_CHANNEL_stereo_uplink_rdata_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_ASP_CODEC_VOICE_UPLINK_CHANNEL_UNION
 �ṹ˵��  : VOICE_UPLINK_CHANNEL �Ĵ����ṹ���塣��ַƫ����:0xFC����ֵ:0x00000000�����:32
 �Ĵ���˵��: VOICE����ͨ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  voice_uplink_rdata : 32; /* bit[0-31]: ��������������в��� */
    } reg;
} SOC_ASP_CODEC_VOICE_UPLINK_CHANNEL_UNION;
#endif
#define SOC_ASP_CODEC_VOICE_UPLINK_CHANNEL_voice_uplink_rdata_START  (0)
#define SOC_ASP_CODEC_VOICE_UPLINK_CHANNEL_voice_uplink_rdata_END    (31)






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

#endif /* end of soc_asp_codec_interface.h */
