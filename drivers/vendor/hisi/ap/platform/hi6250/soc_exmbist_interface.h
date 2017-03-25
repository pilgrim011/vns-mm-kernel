/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_exmbist_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-07-15 15:56:38
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��7��15��
    ��    ��   : s00249479
    �޸�����   : �ӡ�Hi6250V100 SOC�Ĵ����ֲ�_EXMBIST.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_EXMBIST_INTERFACE_H__
#define __SOC_EXMBIST_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) register_exmbist
 ****************************************************************************/
/* �Ĵ���˵��������CMD�Ĵ�����
   λ����UNION�ṹ:  SOC_EXMBIST_CMD_ADDR_UNION */
#define SOC_EXMBIST_CMD_ADDR_ADDR(base)               ((base) + (0x0000))

/* �Ĵ���˵����CMDЯ����������Ϣ��
   λ����UNION�ṹ:  SOC_EXMBIST_DAT_ADDR_UNION */
#define SOC_EXMBIST_DAT_ADDR_ADDR(base)               ((base) + (0x0004))

/* �Ĵ���˵����exmbistʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_EXMBIST_EN_UNION */
#define SOC_EXMBIST_EN_ADDR(base)                     ((base) + (0x0008))

/* �Ĵ���˵����ʱ���ſؼĴ�����
   λ����UNION�ṹ:  SOC_EXMBIST_CLKEN0_UNION */
#define SOC_EXMBIST_CLKEN0_ADDR(base)                 ((base) + (0x000C))

/* �Ĵ���˵����ʱ���ſؼĴ�����
   λ����UNION�ṹ:  SOC_EXMBIST_CLKEN1_UNION */
#define SOC_EXMBIST_CLKEN1_ADDR(base)                 ((base) + (0x0010))

/* �Ĵ���˵����MUXѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_EXMBIST_MUX_SEL_UNION */
#define SOC_EXMBIST_MUX_SEL_ADDR(base)                ((base) + (0x0014))

/* �Ĵ���˵������дoutstandingˮ�߿��ƼĴ�����
   λ����UNION�ṹ:  SOC_EXMBIST_OTS_LINE_UNION */
#define SOC_EXMBIST_OTS_LINE_ADDR(base)               ((base) + (0x0018))

/* �Ĵ���˵������ȫ����ʹ�ܡ�
   λ����UNION�ṹ:  SOC_EXMBIST_SECUER_EN_UNION */
#define SOC_EXMBIST_SECUER_EN_ADDR(base)              ((base) + (0x001C))

/* �Ĵ���˵������дQOS���üĴ�����
   λ����UNION�ṹ:  SOC_EXMBIST_QOS_UNION */
#define SOC_EXMBIST_QOS_ADDR(base)                    ((base) + (0x0020))

/* �Ĵ���˵��������ϲ����üĴ�����
   λ����UNION�ṹ:  SOC_EXMBIST_CMD_MERGE_UNION */
#define SOC_EXMBIST_CMD_MERGE_ADDR(base)              ((base) + (0x0024))

/* �Ĵ���˵�������Ƶ�ÿ��RANK��DDR�������üĴ�����
   λ����UNION�ṹ:  SOC_EXMBIST_RANK_VOL_UNION */
#define SOC_EXMBIST_RANK_VOL_ADDR(base, i)            ((base) + (0x0028+0x4*(i)))

/* �Ĵ���˵����EXMBIST��ǰɨ���rank���üĴ�����
   λ����UNION�ṹ:  SOC_EXMBIST_TEST_RANK_UNION */
#define SOC_EXMBIST_TEST_RANK_ADDR(base)              ((base) + (0x0048))

/* �Ĵ���˵�����Խ�DDR������λ�����üĴ�����
   λ����UNION�ṹ:  SOC_EXMBIST_DRAM_WIDTH_UNION */
#define SOC_EXMBIST_DRAM_WIDTH_ADDR(base)             ((base) + (0x004C))

/* �Ĵ���˵����DDR CHAN��Ϣ���üĴ�����
   λ����UNION�ṹ:  SOC_EXMBIST_CHAN_INFO_UNION */
#define SOC_EXMBIST_CHAN_INFO_ADDR(base)              ((base) + (0x0050))

/* �Ĵ���˵������ַ��֯ģʽ��
   λ����UNION�ṹ:  SOC_EXMBIST_ADDR_INTLV_UNION */
#define SOC_EXMBIST_ADDR_INTLV_ADDR(base)             ((base) + (0x0054))

/* �Ĵ���˵����EXMBISTģ���״̬����Ĵ�����
   λ����UNION�ṹ:  SOC_EXMBIST_STATUS_UNION */
#define SOC_EXMBIST_STATUS_ADDR(base)                 ((base) + (0x0058))

/* �Ĵ���˵����DFX��Ϣ�Ĵ�����
   λ����UNION�ṹ:  SOC_EXMBIST_DFX_INFO_UNION */
#define SOC_EXMBIST_DFX_INFO_ADDR(base)               ((base) + (0x005C))

/* �Ĵ���˵����pclk��̬ʱ���ſء�
   λ����UNION�ṹ:  SOC_EXMBIST_PCLK_GATE_UNION */
#define SOC_EXMBIST_PCLK_GATE_ADDR(base)              ((base) + (0x0060))

/* �Ĵ���˵����mem_ctrl�Ĵ�����
   λ����UNION�ṹ:  SOC_EXMBIST_MEM_CTRL_UNION */
#define SOC_EXMBIST_MEM_CTRL_ADDR(base)               ((base) + (0x0064))

/* �Ĵ���˵����ͨ�ÿ��ƼĴ���0��
   λ����UNION�ṹ:  SOC_EXMBIST_COMMON_CTRL0_UNION */
#define SOC_EXMBIST_COMMON_CTRL0_ADDR(base)           ((base) + (0x0068))

/* �Ĵ���˵����ͨ�ÿ��ƼĴ���1��
   λ����UNION�ṹ:  SOC_EXMBIST_COMMON_CTRL1_UNION */
#define SOC_EXMBIST_COMMON_CTRL1_ADDR(base)           ((base) + (0x006C))

/* �Ĵ���˵����ͨ�ÿ��ƼĴ���2��
   λ����UNION�ṹ:  SOC_EXMBIST_COMMON_CTRL2_UNION */
#define SOC_EXMBIST_COMMON_CTRL2_ADDR(base)           ((base) + (0x0070))

/* �Ĵ���˵����ͨ�ÿ��ƼĴ���3��
   λ����UNION�ṹ:  SOC_EXMBIST_COMMON_CTRL3_UNION */
#define SOC_EXMBIST_COMMON_CTRL3_ADDR(base)           ((base) + (0x0074))

/* �Ĵ���˵������дmid���üĴ�����
   λ����UNION�ṹ:  SOC_EXMBIST_RW_MID_UNION */
#define SOC_EXMBIST_RW_MID_ADDR(base)                 ((base) + (0x0078))

/* �Ĵ���˵����DDR��ϵͳ��APB��ȫȨ�����á�
   λ����UNION�ṹ:  SOC_EXMBIST_DDRSYS_APB_SECURE_UNION */
#define SOC_EXMBIST_DDRSYS_APB_SECURE_ADDR(base)      ((base) + (0x0100))





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
                     (1/1) register_exmbist
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_CMD_ADDR_UNION
 �ṹ˵��  : CMD_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����CMD�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_info      : 8;  /* bit[0-7] : ����д�������֣�
                                                        д�Ĵ�����ָʾ��Ҫ���õ�cmdָ�����ָ�����ο�EXMBIST FS�ĵ���
                                                        ���Ĵ�������Ӧ��ָ���������ݡ� */
        unsigned int  data_info_cmd : 24; /* bit[8-31]: ����д�������֣�
                                                        д�Ĵ�������cmdЯ����������ϢС�ڵ���24bitʱ�������Ϊcmdָ����Я����������Ϣ����cmdЯ����������Ϣ����24bit��cmdЯ����������Ϣ��0x0004�Ĵ������룬�������Ч��
                                                        ���Ĵ�������Ӧ��ָ���������ݡ� */
    } reg;
} SOC_EXMBIST_CMD_ADDR_UNION;
#endif
#define SOC_EXMBIST_CMD_ADDR_cmd_info_START       (0)
#define SOC_EXMBIST_CMD_ADDR_cmd_info_END         (7)
#define SOC_EXMBIST_CMD_ADDR_data_info_cmd_START  (8)
#define SOC_EXMBIST_CMD_ADDR_data_info_cmd_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_DAT_ADDR_UNION
 �ṹ˵��  : DAT_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: CMDЯ����������Ϣ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  data_info : 32; /* bit[0-31]: ��cmdЯ����������Ϣ����24bit���˼Ĵ������ڸ�������������Ϣ����Ӧ��EXMBIST�е�DIN����˿ڡ� */
    } reg;
} SOC_EXMBIST_DAT_ADDR_UNION;
#endif
#define SOC_EXMBIST_DAT_ADDR_data_info_START  (0)
#define SOC_EXMBIST_DAT_ADDR_data_info_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_EN_UNION
 �ṹ˵��  : EN �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: exmbistʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_exmbist_en : 1;  /* bit[0]   : exmbistʹ�ܼĴ�����
                                                         0���ر�exmbist��
                                                         1��ʹ��exmbist�� */
        unsigned int  reserved       : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_EXMBIST_EN_UNION;
#endif
#define SOC_EXMBIST_EN_cfg_exmbist_en_START  (0)
#define SOC_EXMBIST_EN_cfg_exmbist_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_CLKEN0_UNION
 �ṹ˵��  : CLKEN0 �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: ʱ���ſؼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dmc_clk_en_0        : 1;  /* bit[0]    : DMC0ʱ���ſ�ʹ�ܣ�
                                                               0���رո�ģ���ʱ�ӡ�
                                                               1��ʹ�ܸ�ģ���ʱ�ӡ� */
        unsigned int  reserved_0          : 1;  /* bit[1]    : ���� */
        unsigned int  rdr_clk_en_0        : 1;  /* bit[2]    : RBUFFER0ʱ���ſ�ʹ�ܣ�
                                                               0���رո�ģ���ʱ�ӡ�
                                                               1��ʹ�ܸ�ģ���ʱ�ӡ� */
        unsigned int  apb_clken_0         : 1;  /* bit[3]    : DDRC0 APBʱ���ſ�ʹ�ܣ�
                                                               0���رո�ģ���ʱ�ӡ�
                                                               1��ʹ�ܸ�ģ���ʱ�ӡ� */
        unsigned int  reserved_1          : 6;  /* bit[4-9]  : ���� */
        unsigned int  exmbist_wrap_clk_en : 1;  /* bit[10]   : exmbist_wrapʱ���ſ�ʹ�ܣ�
                                                               0���رո�ģ���ʱ�ӡ�
                                                               1��ʹ�ܸ�ģ���ʱ�ӡ� */
        unsigned int  reserved_2          : 5;  /* bit[11-15]: ������ */
        unsigned int  clk_wr_en           : 16; /* bit[16-31]: clk_enÿ��bit��ʹ��λ��
                                                               ֻ�е�clk_wr_en��Ӧ��bitΪ1'b1��clk_en��Ӧ��bit�������á�
                                                               clk_wr_en[31:16]��clk_en[15:0]ÿһbitΪһһ��Ӧ��ϵ�� */
    } reg;
} SOC_EXMBIST_CLKEN0_UNION;
#endif
#define SOC_EXMBIST_CLKEN0_dmc_clk_en_0_START         (0)
#define SOC_EXMBIST_CLKEN0_dmc_clk_en_0_END           (0)
#define SOC_EXMBIST_CLKEN0_rdr_clk_en_0_START         (2)
#define SOC_EXMBIST_CLKEN0_rdr_clk_en_0_END           (2)
#define SOC_EXMBIST_CLKEN0_apb_clken_0_START          (3)
#define SOC_EXMBIST_CLKEN0_apb_clken_0_END            (3)
#define SOC_EXMBIST_CLKEN0_exmbist_wrap_clk_en_START  (10)
#define SOC_EXMBIST_CLKEN0_exmbist_wrap_clk_en_END    (10)
#define SOC_EXMBIST_CLKEN0_clk_wr_en_START            (16)
#define SOC_EXMBIST_CLKEN0_clk_wr_en_END              (31)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_CLKEN1_UNION
 �ṹ˵��  : CLKEN1 �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: ʱ���ſؼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0        : 1;  /* bit[0]    : ������ */
        unsigned int  pack_apb_clk_en_0 : 1;  /* bit[1]    : PACK0 APBʱ���ſ�ʹ�ܣ�
                                                             0���رո�ģ���ʱ�ӡ�
                                                             1��ʹ�ܸ�ģ���ʱ�ӡ� */
        unsigned int  reserved_1        : 14; /* bit[2-15] : ������ */
        unsigned int  clk_wr_en         : 16; /* bit[16-31]: clk_enÿ��bit��ʹ��λ��
                                                             ֻ�е�clk_wr_en��Ӧ��bitΪ1'b1��clk_en��Ӧ��bit�������á�
                                                             clk_wr_en[31:16]��clk_en[15:0]ÿһbitΪһһ��Ӧ��ϵ�� */
    } reg;
} SOC_EXMBIST_CLKEN1_UNION;
#endif
#define SOC_EXMBIST_CLKEN1_pack_apb_clk_en_0_START  (1)
#define SOC_EXMBIST_CLKEN1_pack_apb_clk_en_0_END    (1)
#define SOC_EXMBIST_CLKEN1_clk_wr_en_START          (16)
#define SOC_EXMBIST_CLKEN1_clk_wr_en_END            (31)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_MUX_SEL_UNION
 �ṹ˵��  : MUX_SEL �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000001�����:32
 �Ĵ���˵��: MUXѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  mux_sel  : 1;  /* bit[0]   : muxѡ��Ĵ�����
                                                   0��ѡ��EXMBIST WRAP��AXI_MST�ڴ�MUX�����
                                                   1��ѡ��IVP��AXI_MST�ڴ�MUX����� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_EXMBIST_MUX_SEL_UNION;
#endif
#define SOC_EXMBIST_MUX_SEL_mux_sel_START   (0)
#define SOC_EXMBIST_MUX_SEL_mux_sel_END     (0)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_OTS_LINE_UNION
 �ṹ˵��  : OTS_LINE �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x003F003F�����:32
 �Ĵ���˵��: ��дoutstandingˮ�߿��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_wr_ots_line : 6;  /* bit[0-5]  : д����outstandingˮ�ߣ�outstanding���ֵΪ64��������ֵ����64ʱ����64Ϊ׼��
                                                           ������ֵΪ0ʱ��д�����������ƣ��޷��·�д������ */
        unsigned int  reserved_0      : 10; /* bit[6-15] : ������ */
        unsigned int  cfg_rd_ots_line : 6;  /* bit[16-21]: ������outstandingˮ�ߣ�outstanding���ֵΪ64��������ֵ����64ʱ����64Ϊ׼��
                                                           ������ֵΪ0ʱ���������������ƣ��޷��·��������� */
        unsigned int  reserved_1      : 10; /* bit[22-31]: ������ */
    } reg;
} SOC_EXMBIST_OTS_LINE_UNION;
#endif
#define SOC_EXMBIST_OTS_LINE_cfg_wr_ots_line_START  (0)
#define SOC_EXMBIST_OTS_LINE_cfg_wr_ots_line_END    (5)
#define SOC_EXMBIST_OTS_LINE_cfg_rd_ots_line_START  (16)
#define SOC_EXMBIST_OTS_LINE_cfg_rd_ots_line_END    (21)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_SECUER_EN_UNION
 �ṹ˵��  : SECUER_EN �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000001�����:32
 �Ĵ���˵��: ��ȫ����ʹ�ܡ�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_secure_en : 1;  /* bit[0]   : ��ȫ����ʹ��λ��
                                                        0����axi�����Ĳ�����Ϊ��ȫ������
                                                        1:��axi�����Ĳ�����Ϊ�ǰ�ȫ������
                                                        ע�⣺��д�üĴ�����Ҫ��ȫ���Է��ʣ����üĴ���û������Ҫ�� */
        unsigned int  reserved      : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_EXMBIST_SECUER_EN_UNION;
#endif
#define SOC_EXMBIST_SECUER_EN_cfg_secure_en_START  (0)
#define SOC_EXMBIST_SECUER_EN_cfg_secure_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_QOS_UNION
 �ṹ˵��  : QOS �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��дQOS���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_rd_qos : 4;  /* bit[0-3]  : ��������QoSֵ�� 
                                                      0x0��0xF��QoS��ӦΪ0~15��0Ϊ��ͣ�15Ϊ��ߡ� */
        unsigned int  reserved_0 : 12; /* bit[4-15] : ���� */
        unsigned int  cfg_wr_qos : 4;  /* bit[16-19]: д������QoSֵ�� 
                                                      0x0��0xF��QoS��ӦΪ0~15��0Ϊ��ͣ�15Ϊ��ߡ� */
        unsigned int  reserved_1 : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_EXMBIST_QOS_UNION;
#endif
#define SOC_EXMBIST_QOS_cfg_rd_qos_START  (0)
#define SOC_EXMBIST_QOS_cfg_rd_qos_END    (3)
#define SOC_EXMBIST_QOS_cfg_wr_qos_START  (16)
#define SOC_EXMBIST_QOS_cfg_wr_qos_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_CMD_MERGE_UNION
 �ṹ˵��  : CMD_MERGE �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x0000000E�����:32
 �Ĵ���˵��: ����ϲ����üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_cmd_merge_bypass : 1;  /* bit[0]   : merge����bypass���أ�
                                                               0���ر�merge bypass���ܡ�
                                                               1��ʹ��merge bypass���ܡ� */
        unsigned int  cfg_cmd_wait_timeout : 3;  /* bit[1-3] : ��������кϲ��ĳ�ʱ���á�
                                                               �������߼�rs�д���һ�����ݣ�����ʱcmd fifo�Ѿ�Ϊ�գ���ô���ȴ�һ��ʱ�䣬���û�г����ȴ�ʱ�䣬��cmd fifo�й�����������Ȼ����ƴ�ӣ���������ȴ�ʱ�䣬�������������������ƴ�ӡ����У�cfg_cmd_wait_timeout��Ϊ�ȴ���cycle���� */
        unsigned int  reserved             : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_EXMBIST_CMD_MERGE_UNION;
#endif
#define SOC_EXMBIST_CMD_MERGE_cfg_cmd_merge_bypass_START  (0)
#define SOC_EXMBIST_CMD_MERGE_cfg_cmd_merge_bypass_END    (0)
#define SOC_EXMBIST_CMD_MERGE_cfg_cmd_wait_timeout_START  (1)
#define SOC_EXMBIST_CMD_MERGE_cfg_cmd_wait_timeout_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_RANK_VOL_UNION
 �ṹ˵��  : RANK_VOL �Ĵ����ṹ���塣��ַƫ����:0x0028+0x4*(i)����ֵ:0x00000012�����:32
 �Ĵ���˵��: ���Ƶ�ÿ��RANK��DDR�������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_col_bit  : 3;  /* bit[0-2] : ��ƬSDRAM�е�ַλ�����á�
                                                       000��8 bit��
                                                       001��9 bit��
                                                       010��10 bit��
                                                       011��11 bit��
                                                       100��12 bit��
                                                       ���������� */
        unsigned int  cfg_row_bit  : 3;  /* bit[3-5] : ��ƬSDRAM�е�ַλ�����á�
                                                       000��11 bit��
                                                       001��12 bit��
                                                       010��13 bit��
                                                       011��14 bit��
                                                       100��15 bit��
                                                       101��16 bit��
                                                       110: 17 bit��
                                                       111: 18 bit�� */
        unsigned int  cfg_bank_bit : 2;  /* bit[6-7] : ��ƬSDRAM Bank����
                                                       00��2bit��
                                                       01��3bit��
                                                       10��4bit��
                                                       11��������
                                                       ע�⣺����DDR4�����������ó�����bank group�е�bank֮�͡� */
        unsigned int  reserved     : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_EXMBIST_RANK_VOL_UNION;
#endif
#define SOC_EXMBIST_RANK_VOL_cfg_col_bit_START   (0)
#define SOC_EXMBIST_RANK_VOL_cfg_col_bit_END     (2)
#define SOC_EXMBIST_RANK_VOL_cfg_row_bit_START   (3)
#define SOC_EXMBIST_RANK_VOL_cfg_row_bit_END     (5)
#define SOC_EXMBIST_RANK_VOL_cfg_bank_bit_START  (6)
#define SOC_EXMBIST_RANK_VOL_cfg_bank_bit_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_TEST_RANK_UNION
 �ṹ˵��  : TEST_RANK �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x00000000�����:32
 �Ĵ���˵��: EXMBIST��ǰɨ���rank���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_test_rank : 3;  /* bit[0-2] : ��ǰɨ���rank��
                                                        000��ѡ��ɨ��rank0��
                                                        001��ѡ��ɨ��rank1��
                                                        010��ѡ��ɨ��rank2��
                                                        011��ѡ��ɨ��rank3��
                                                        100��ѡ��ɨ��rank4��
                                                        101��ѡ��ɨ��rank5��
                                                        110��ѡ��ɨ��rank6��
                                                        111��ѡ��ɨ��rank7�� */
        unsigned int  reserved      : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_EXMBIST_TEST_RANK_UNION;
#endif
#define SOC_EXMBIST_TEST_RANK_cfg_test_rank_START  (0)
#define SOC_EXMBIST_TEST_RANK_cfg_test_rank_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_DRAM_WIDTH_UNION
 �ṹ˵��  : DRAM_WIDTH �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Խ�DDR������λ�����üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_dram_width : 1;  /* bit[0]   : �Խӵ�DDR�������͡�
                                                         0:�Խ�DDR����λ��Ϊ16��
                                                         1���Խ�DDR������λ��Ϊ32�� */
        unsigned int  reserved       : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_EXMBIST_DRAM_WIDTH_UNION;
#endif
#define SOC_EXMBIST_DRAM_WIDTH_cfg_dram_width_START  (0)
#define SOC_EXMBIST_DRAM_WIDTH_cfg_dram_width_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_CHAN_INFO_UNION
 �ṹ˵��  : CHAN_INFO �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: DDR CHAN��Ϣ���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_chan_type : 2;  /* bit[0-1] : �Խ�DDRΪ��ͨ����˫ͨ��������ͨ����
                                                        0���Խ�DDRΪ��ͨ����
                                                        1���Խ�DDRΪ˫ͨ����
                                                        2���Խ�DDRΪ��ͨ���� */
        unsigned int  cfg_test_chan : 2;  /* bit[2-3] : ��ǰѡ��ɨ���channel��
                                                        00��ѡ��channel 0��
                                                        01��ѡ��channel 1��
                                                        10��ѡ��channel 2��
                                                        11��ѡ��channel 3�� */
        unsigned int  reserved      : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_EXMBIST_CHAN_INFO_UNION;
#endif
#define SOC_EXMBIST_CHAN_INFO_cfg_chan_type_START  (0)
#define SOC_EXMBIST_CHAN_INFO_cfg_chan_type_END    (1)
#define SOC_EXMBIST_CHAN_INFO_cfg_test_chan_START  (2)
#define SOC_EXMBIST_CHAN_INFO_cfg_test_chan_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_ADDR_INTLV_UNION
 �ṹ˵��  : ADDR_INTLV �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ַ��֯ģʽ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cfg_intlv_gran : 3;  /* bit[0-2] : ��ַ��֯���ȣ�
                                                         0x0��128Byte��
                                                         0x1��256Byte��
                                                         0x2��512Byte��
                                                         0x3��1KByte��
                                                         0x4��2KByte��
                                                         0x5��4KByte��
                                                         ע�⣺��ַ��֯���ȱ�����DMSSģ��������ͬ����ģʽ������channel��ַ�ĵ�ַӳ�䡣 */
        unsigned int  reserved       : 29; /* bit[3-31]: ������ */
    } reg;
} SOC_EXMBIST_ADDR_INTLV_UNION;
#endif
#define SOC_EXMBIST_ADDR_INTLV_cfg_intlv_gran_START  (0)
#define SOC_EXMBIST_ADDR_INTLV_cfg_intlv_gran_END    (2)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_STATUS_UNION
 �ṹ˵��  : STATUS �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x00005002�����:32
 �Ĵ���˵��: EXMBISTģ���״̬����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bist_done      : 1;  /* bit[0]    : ��ʾEXMBIST�Ĺ���״̬��
                                                          1 : current execution finished��
                                                          0 : current execution in progress�� */
        unsigned int  bist_pass      : 1;  /* bit[1]    : Bist��������Ƿ���ȷ��
                                                          1 : test passes, no errors found��
                                                          0 : found errors�� */
        unsigned int  reserved_0     : 2;  /* bit[2-3]  : ���� */
        unsigned int  parity_error   : 1;  /* bit[4]    : ������ */
        unsigned int  watchdog_error : 1;  /* bit[5]    : watchdog״ָ̬ʾ��
                                                          1 : watchdog error fired��
                                                          0 : not fired�� */
        unsigned int  diag_fifo_last : 1;  /* bit[6]    : Diag_fifo��״ָ̬ʾ��
                                                          1 �� have reached the last element in the DIAG FIFO��
                                                          0 �� not yet�� */
        unsigned int  reserved_1     : 1;  /* bit[7]    : ���� */
        unsigned int  diag_ip        : 3;  /* bit[8-10] : Instruction # that catches the current fault (saved in the Diag FIFO)�� */
        unsigned int  reserved_2     : 1;  /* bit[11]   : ���� */
        unsigned int  fingerprint    : 4;  /* bit[12-15]: tie to 4��b0101, used for sanity check�� */
        unsigned int  iter_cnt       : 16; /* bit[16-31]: # of iterations that have been executed, meaningful when cfg_loop_en=1�� */
    } reg;
} SOC_EXMBIST_STATUS_UNION;
#endif
#define SOC_EXMBIST_STATUS_bist_done_START       (0)
#define SOC_EXMBIST_STATUS_bist_done_END         (0)
#define SOC_EXMBIST_STATUS_bist_pass_START       (1)
#define SOC_EXMBIST_STATUS_bist_pass_END         (1)
#define SOC_EXMBIST_STATUS_parity_error_START    (4)
#define SOC_EXMBIST_STATUS_parity_error_END      (4)
#define SOC_EXMBIST_STATUS_watchdog_error_START  (5)
#define SOC_EXMBIST_STATUS_watchdog_error_END    (5)
#define SOC_EXMBIST_STATUS_diag_fifo_last_START  (6)
#define SOC_EXMBIST_STATUS_diag_fifo_last_END    (6)
#define SOC_EXMBIST_STATUS_diag_ip_START         (8)
#define SOC_EXMBIST_STATUS_diag_ip_END           (10)
#define SOC_EXMBIST_STATUS_fingerprint_START     (12)
#define SOC_EXMBIST_STATUS_fingerprint_END       (15)
#define SOC_EXMBIST_STATUS_iter_cnt_START        (16)
#define SOC_EXMBIST_STATUS_iter_cnt_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_DFX_INFO_UNION
 �ṹ˵��  : DFX_INFO �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0x00000007�����:32
 �Ĵ���˵��: DFX��Ϣ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cmd_fifo_empty   : 1;  /* bit[0]    : cmd fifo��״̬��
                                                            0��cmd fifoΪ�ǿա�
                                                            1��cmd fifoΪ�ա� */
        unsigned int  wdata_fifo_empty : 1;  /* bit[1]    : wdata fifo��״̬��
                                                            0��wdata fifoΪ�ǿա�
                                                            1��wdata fifoΪ�ա� */
        unsigned int  cnt_fifo_empty   : 1;  /* bit[2]    : cnt fifo��״̬��
                                                            0��cnt fifoΪ�ǿա�
                                                            1��cnt fifoΪ�ա� */
        unsigned int  cmd_fifo_full    : 1;  /* bit[3]    : cmd fifo��״̬��
                                                            0��cmd fifoΪ������
                                                            1��cmd fifoΪ���� */
        unsigned int  wdata_fifo_full  : 1;  /* bit[4]    : wdata fifo��״̬��
                                                            0��wdata fifoΪ������
                                                            1��wdata fifoΪ���� */
        unsigned int  cnt_fifo_full    : 1;  /* bit[5]    : cnt fifo��״̬��
                                                            0��cnt fifoΪ������
                                                            1��cnt fifoΪ���� */
        unsigned int  wr_ots_cnt       : 6;  /* bit[6-11] : ��ǰ��δ����bresp��д������ */
        unsigned int  rd_ots_cnt       : 6;  /* bit[12-17]: ��ǰ��δ����rresp�Ķ������� */
        unsigned int  reserved         : 14; /* bit[18-31]: ������ */
    } reg;
} SOC_EXMBIST_DFX_INFO_UNION;
#endif
#define SOC_EXMBIST_DFX_INFO_cmd_fifo_empty_START    (0)
#define SOC_EXMBIST_DFX_INFO_cmd_fifo_empty_END      (0)
#define SOC_EXMBIST_DFX_INFO_wdata_fifo_empty_START  (1)
#define SOC_EXMBIST_DFX_INFO_wdata_fifo_empty_END    (1)
#define SOC_EXMBIST_DFX_INFO_cnt_fifo_empty_START    (2)
#define SOC_EXMBIST_DFX_INFO_cnt_fifo_empty_END      (2)
#define SOC_EXMBIST_DFX_INFO_cmd_fifo_full_START     (3)
#define SOC_EXMBIST_DFX_INFO_cmd_fifo_full_END       (3)
#define SOC_EXMBIST_DFX_INFO_wdata_fifo_full_START   (4)
#define SOC_EXMBIST_DFX_INFO_wdata_fifo_full_END     (4)
#define SOC_EXMBIST_DFX_INFO_cnt_fifo_full_START     (5)
#define SOC_EXMBIST_DFX_INFO_cnt_fifo_full_END       (5)
#define SOC_EXMBIST_DFX_INFO_wr_ots_cnt_START        (6)
#define SOC_EXMBIST_DFX_INFO_wr_ots_cnt_END          (11)
#define SOC_EXMBIST_DFX_INFO_rd_ots_cnt_START        (12)
#define SOC_EXMBIST_DFX_INFO_rd_ots_cnt_END          (17)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_PCLK_GATE_UNION
 �ṹ˵��  : PCLK_GATE �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000000�����:32
 �Ĵ���˵��: pclk��̬ʱ���ſء�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apb_gt_en : 1;  /* bit[0]   : pclkʱ�Ӿ�̬ʱ���ſأ�
                                                    0���ر�pclkʱ�ӡ�
                                                    1������pclkʱ�ӡ� */
        unsigned int  reserved  : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_EXMBIST_PCLK_GATE_UNION;
#endif
#define SOC_EXMBIST_PCLK_GATE_apb_gt_en_START  (0)
#define SOC_EXMBIST_PCLK_GATE_apb_gt_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_MEM_CTRL_UNION
 �ṹ˵��  : MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x000001A8�����:32
 �Ĵ���˵��: mem_ctrl�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  slp      : 1;  /* bit[0]    : ������ */
        unsigned int  dslp     : 1;  /* bit[1]    : ������ */
        unsigned int  sd       : 1;  /* bit[2]    : ������ */
        unsigned int  rct      : 2;  /* bit[3-4]  : ������ */
        unsigned int  wct      : 2;  /* bit[5-6]  : ������ */
        unsigned int  kp       : 3;  /* bit[7-9]  : ������ */
        unsigned int  reserved_0: 6;  /* bit[10-15]: ���� */
        unsigned int  reserved_1: 16; /* bit[16-31]: ������ */
    } reg;
} SOC_EXMBIST_MEM_CTRL_UNION;
#endif
#define SOC_EXMBIST_MEM_CTRL_slp_START       (0)
#define SOC_EXMBIST_MEM_CTRL_slp_END         (0)
#define SOC_EXMBIST_MEM_CTRL_dslp_START      (1)
#define SOC_EXMBIST_MEM_CTRL_dslp_END        (1)
#define SOC_EXMBIST_MEM_CTRL_sd_START        (2)
#define SOC_EXMBIST_MEM_CTRL_sd_END          (2)
#define SOC_EXMBIST_MEM_CTRL_rct_START       (3)
#define SOC_EXMBIST_MEM_CTRL_rct_END         (4)
#define SOC_EXMBIST_MEM_CTRL_wct_START       (5)
#define SOC_EXMBIST_MEM_CTRL_wct_END         (6)
#define SOC_EXMBIST_MEM_CTRL_kp_START        (7)
#define SOC_EXMBIST_MEM_CTRL_kp_END          (9)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_COMMON_CTRL0_UNION
 �ṹ˵��  : COMMON_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x0068����ֵ:0x00000010�����:32
 �Ĵ���˵��: ͨ�ÿ��ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  sel_clk_ddrphy_rs_wr : 2;  /* bit[0-1] : ����RS��дʱ�����������á�
                                                               0������ʱ�ӡ�
                                                               1������ʱ�ӡ� */
        unsigned int  sel_clk_ddrphy_rs_rd : 2;  /* bit[2-3] : ����RS�Ķ�ʱ�����������á�
                                                               0������ʱ�ӡ�
                                                               1������ʱ�ӡ� */
        unsigned int  apb_wr_buf_bypass    : 1;  /* bit[4]   : APB write buf bypass��
                                                               0��no bypass��
                                                               1��bypass�� */
        unsigned int  common_ctrl          : 27; /* bit[5-31]: DDRPHY��Ԥ�����ƽӿڡ� */
    } reg;
} SOC_EXMBIST_COMMON_CTRL0_UNION;
#endif
#define SOC_EXMBIST_COMMON_CTRL0_sel_clk_ddrphy_rs_wr_START  (0)
#define SOC_EXMBIST_COMMON_CTRL0_sel_clk_ddrphy_rs_wr_END    (1)
#define SOC_EXMBIST_COMMON_CTRL0_sel_clk_ddrphy_rs_rd_START  (2)
#define SOC_EXMBIST_COMMON_CTRL0_sel_clk_ddrphy_rs_rd_END    (3)
#define SOC_EXMBIST_COMMON_CTRL0_apb_wr_buf_bypass_START     (4)
#define SOC_EXMBIST_COMMON_CTRL0_apb_wr_buf_bypass_END       (4)
#define SOC_EXMBIST_COMMON_CTRL0_common_ctrl_START           (5)
#define SOC_EXMBIST_COMMON_CTRL0_common_ctrl_END             (31)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_COMMON_CTRL1_UNION
 �ṹ˵��  : COMMON_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x006C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ�ÿ��ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pack_apb_deadlock_avoid : 1;  /* bit[0]   : PACKʱ���ſغ�ķ���������bypass��
                                                                  0���򿪷��������ܡ�
                                                                  1�����÷��������ܡ� */
        unsigned int  reserved                : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_EXMBIST_COMMON_CTRL1_UNION;
#endif
#define SOC_EXMBIST_COMMON_CTRL1_pack_apb_deadlock_avoid_START  (0)
#define SOC_EXMBIST_COMMON_CTRL1_pack_apb_deadlock_avoid_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_COMMON_CTRL2_UNION
 �ṹ˵��  : COMMON_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ�ÿ��ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  common_ctrl2 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_EXMBIST_COMMON_CTRL2_UNION;
#endif
#define SOC_EXMBIST_COMMON_CTRL2_common_ctrl2_START  (0)
#define SOC_EXMBIST_COMMON_CTRL2_common_ctrl2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_COMMON_CTRL3_UNION
 �ṹ˵��  : COMMON_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ�ÿ��ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  common_ctrl3 : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_EXMBIST_COMMON_CTRL3_UNION;
#endif
#define SOC_EXMBIST_COMMON_CTRL3_common_ctrl3_START  (0)
#define SOC_EXMBIST_COMMON_CTRL3_common_ctrl3_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_RW_MID_UNION
 �ṹ˵��  : RW_MID �Ĵ����ṹ���塣��ַƫ����:0x0078����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��дmid���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  rw_mid   : 6;  /* bit[0-5] : ��дmid���á� */
        unsigned int  reserved : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_EXMBIST_RW_MID_UNION;
#endif
#define SOC_EXMBIST_RW_MID_rw_mid_START    (0)
#define SOC_EXMBIST_RW_MID_rw_mid_END      (5)


/*****************************************************************************
 �ṹ��    : SOC_EXMBIST_DDRSYS_APB_SECURE_UNION
 �ṹ˵��  : DDRSYS_APB_SECURE �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x00000001�����:32
 �Ĵ���˵��: DDR��ϵͳ��APB��ȫȨ�����á�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ddrsys_apb_secure : 1;  /* bit[0]   : DDR��ϵͳ�����üĴ�����APB��ȫȨ�����ã�
                                                            0��non-secure������ȫ��ǰ�ȫAPB���ʣ�
                                                            1��secure��ֻ����ȫAPB���ʡ�
                                                            ע�⣺
                                                            1.�˼Ĵ���������DMSS��SEC������ص����üĴ�����ʼ����ֻ����ȫAPB���ʣ�
                                                            2.����Ȩ�޵ķǷ�APB����ʱ��������д���ݻ򷵻�ȫ������ݣ����ҷ���pslverrΪ1�� */
        unsigned int  reserved          : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_EXMBIST_DDRSYS_APB_SECURE_UNION;
#endif
#define SOC_EXMBIST_DDRSYS_APB_SECURE_ddrsys_apb_secure_START  (0)
#define SOC_EXMBIST_DDRSYS_APB_SECURE_ddrsys_apb_secure_END    (0)






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

#endif /* end of soc_exmbist_interface.h */
