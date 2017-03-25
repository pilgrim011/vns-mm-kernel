/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : bbp_dbg_trig_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-09-19 17:08:21
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��9��19��
    ��    ��   : d00245230
    �޸�����   : �ӡ�Hi6250V100 MODEM�Ĵ����ֲ�_DBG_TRIG.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#ifndef __BBP_DBG_TRIG_INTERFACE_H__
#define __BBP_DBG_TRIG_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/***======================================================================***
                     (1/2) register_define_dbg_trig
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:20]  ����
 bit[19:8]   W1�ߵ�ַ�ε�ַ
 bit[7:5]    ����
 bit[4]      W1���µ�ʹ�ܣ�OAM����W1ģ���µ�������ã�
 bit[3:1]    ����
 bit[0]      W1��ַ����Чʹ�ܣ����ݲ���Ŀ�Ĺ��߹�ѡʹ�ܣ�
   UNION�ṹ:  DBG_TRIG_W1_CONFIG1_UNION */
#define DBG_TRIG_W1_CONFIG1_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8000)

/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20:12]  W1 TRACE ADDR RAM����
 bit[11:9]   ����
 bit[8:0]    W1 TRACE ADDR RAM��ʼ��ַ
   UNION�ṹ:  DBG_TRIG_W1_CONFIG2_UNION */
#define DBG_TRIG_W1_CONFIG2_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8004)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   W1 TRACE��ʱ��ʼλ�ã���λchip��
             bit[7:0]��symbol��chip������������Χ0~255chip��
             bit[11:8]��slot��symbol������������Χ0~9symbol��
             bit[15:12]��֡��slot������������Χ0~14slot
   UNION�ṹ:  DBG_TRIG_W1_START_POS_UNION */
#define DBG_TRIG_W1_START_POS_ADDR                    (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8008)

/* �Ĵ���˵����
 bit[31:20]  ����
 bit[19:8]   W2�ߵ�ַ�ε�ַ
 bit[7:5]    ����
 bit[4]      W2���µ�ʹ�ܣ�OAM����W1ģ���µ�������ã�
 bit[3:1]    ����
 bit[0]      W2��ַ����Чʹ�ܣ����ݲ���Ŀ�Ĺ��߹�ѡʹ�ܣ�
   UNION�ṹ:  DBG_TRIG_W2_CONFIG1_UNION */
#define DBG_TRIG_W2_CONFIG1_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC800C)

/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20:12]  W2 TRACE ADDR RAM����
 bit[11:9]   ����
 bit[8:0]    W2 TRACE ADDR RAM��ʼ��ַ
   UNION�ṹ:  DBG_TRIG_W2_CONFIG2_UNION */
#define DBG_TRIG_W2_CONFIG2_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8010)

/* �Ĵ���˵����
 bit[31:16]  ����
 bit[15:0]   W2 TRACE��ʱ��ʼλ�ã���λchip��
             bit[7:0]��symbol��chip������������Χ0~255chip��
             bit[11:8]��slot��symbol������������Χ0~9symbol��
             bit[15:12]��֡��slot������������Χ0~14slot
   UNION�ṹ:  DBG_TRIG_W2_START_POS_UNION */
#define DBG_TRIG_W2_START_POS_ADDR                    (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8014)

/* �Ĵ���˵����
 bit[31:20]  ����
 bit[19:8]   C1�ߵ�ַ�ε�ַ
 bit[7:5]    ����
 bit[4]      C1���µ�ʹ�ܣ�OAM����W1ģ���µ�������ã�
 bit[3:1]    ����
 bit[0]      C1��ַ����Чʹ�ܣ����ݲ���Ŀ�Ĺ��߹�ѡʹ�ܣ�
   UNION�ṹ:  DBG_TRIG_C1_CONFIG1_UNION */
#define DBG_TRIG_C1_CONFIG1_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8018)

/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20:12]  C1 TRACE ADDR RAM����
 bit[11:9]   ����
 bit[8:0]    C1 TRACE ADDR RAM��ʼ��ַ
   UNION�ṹ:  DBG_TRIG_C1_CONFIG2_UNION */
#define DBG_TRIG_C1_CONFIG2_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC801C)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   C1 TRACE��ʱ��ʼλ�ã���λchip��
             EVDO��
             bit[14:0]��֡��chip������������Χ0~32767chip��ʱ�䳤��80/3ms��
             1X��
             bit[10:0]��PCG��chip������������Χ0~1535chip��ʱ�䳤��80/64��
             bit[14:11]��PCG������������Χ0~15��ʱ�䳤��20ms��
   UNION�ṹ:  DBG_TRIG_C1_START_POS_UNION */
#define DBG_TRIG_C1_START_POS_ADDR                    (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8020)

/* �Ĵ���˵����
 bit[31:20]  ����
 bit[19:8]   C2�ߵ�ַ�ε�ַ
 bit[7:5]    ����
 bit[4]      C2���µ�ʹ�ܣ�OAM����W1ģ���µ�������ã�
 bit[3:1]    ����
 bit[0]      C2��ַ����Чʹ�ܣ����ݲ���Ŀ�Ĺ��߹�ѡʹ�ܣ�
   UNION�ṹ:  DBG_TRIG_C2_CONFIG1_UNION */
#define DBG_TRIG_C2_CONFIG1_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8024)

/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20:12]  C2 TRACE ADDR RAM����
 bit[11:9]   ����
 bit[8:0]    C2 TRACE ADDR RAM��ʼ��ַ
   UNION�ṹ:  DBG_TRIG_C2_CONFIG2_UNION */
#define DBG_TRIG_C2_CONFIG2_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8028)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:0]   C2 TRACE��ʱ��ʼλ�ã���λchip��
             EVDO��
             bit[14:0]��֡��chip������������Χ0~32767chip��ʱ�䳤��80/3ms��
             1X��
             bit[10:0]��PCG��chip������������Χ0~1535chip��ʱ�䳤��80/64��
             bit[14:11]��PCG������������Χ0~15��ʱ�䳤��20ms��
   UNION�ṹ:  DBG_TRIG_C2_START_POS_UNION */
#define DBG_TRIG_C2_START_POS_ADDR                    (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC802C)

/* �Ĵ���˵����
 bit[31:20]  ����
 bit[19:8]   G1�ߵ�ַ�ε�ַ
 bit[7:5]    ����
 bit[4]      G1���µ�ʹ�ܣ�OAM����W1ģ���µ�������ã�
 bit[3:1]    ����
 bit[0]      G1��ַ����Чʹ�ܣ����ݲ���Ŀ�Ĺ��߹�ѡʹ�ܣ�
   UNION�ṹ:  DBG_TRIG_G1_CONFIG1_UNION */
#define DBG_TRIG_G1_CONFIG1_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8030)

/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20:12]  G1 TRACE ADDR RAM����
 bit[11:9]   ����
 bit[8:0]    G1 TRACE ADDR RAM��ʼ��ַ
   UNION�ṹ:  DBG_TRIG_G1_CONFIG2_UNION */
#define DBG_TRIG_G1_CONFIG2_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8034)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:0]   G1 TRACE��ʱ��ʼλ�ã���λQb��
             bit[12:0]��gtc_tdma_qb�ϵ�֡��Qb������������Χ0~4999Qb��
             
   UNION�ṹ:  DBG_TRIG_G1_START_POS_UNION */
#define DBG_TRIG_G1_START_POS_ADDR                    (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8038)

/* �Ĵ���˵����
 bit[31:20]  ����
 bit[19:8]   G2�ߵ�ַ�ε�ַ
 bit[7:5]    ����
 bit[4]      G2���µ�ʹ�ܣ�OAM����W1ģ���µ�������ã�
 bit[3:1]    ����
 bit[0]      G2��ַ����Чʹ�ܣ����ݲ���Ŀ�Ĺ��߹�ѡʹ�ܣ�
   UNION�ṹ:  DBG_TRIG_G2_CONFIG1_UNION */
#define DBG_TRIG_G2_CONFIG1_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC803C)

/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20:12]  G2 TRACE ADDR RAM����
 bit[11:9]   ����
 bit[8:0]    G2 TRACE ADDR RAM��ʼ��ַ
   UNION�ṹ:  DBG_TRIG_G2_CONFIG2_UNION */
#define DBG_TRIG_G2_CONFIG2_ADDR                      (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8040)

/* �Ĵ���˵����
 bit[31:13]  ����
 bit[12:0]   G2 TRACE��ʱ��ʼλ�ã���λQb��
             bit[12:0]��gtc_tdma_qb�ϵ�֡��Qb������������Χ0~4999Qb��
             
   UNION�ṹ:  DBG_TRIG_G2_START_POS_UNION */
#define DBG_TRIG_G2_START_POS_ADDR                    (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8044)

/* �Ĵ���˵����
 bit[31:16]  1w2r˫�˿�ram��ʱ���ơ�
 bit[15:0]   ���˿�ram��ʱ���ơ�
   UNION�ṹ:  DBG_TRIG_MEM_CTRL0_DBG_UNION */
#define DBG_TRIG_MEM_CTRL0_DBG_ADDR                   (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8048)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  rom��ʱ���ơ�
 bit[15:0]   1rw2rw˫�˿�ram��ʱ���ơ�
   UNION�ṹ:  DBG_TRIG_MEM_CTRL1_DBG_UNION */
#define DBG_TRIG_MEM_CTRL1_DBG_ADDR                   (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC804C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      ��ʱ�����������壬6ģ���á�
   UNION�ṹ:  DBG_TRIG_OVERTIME_CLR_UNION */
#define DBG_TRIG_OVERTIME_CLR_ADDR                    (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8050)

/* �Ĵ���˵����
 bit[31:22]  ����
 bit[21:20]  G2 ��ѯ����״̬���ϱ�
 bit[19:18]  ����
 bit[17:16]  G1 ��ѯ����״̬���ϱ�
 bit[15:14]  ����
 bit[13:12]  C2 ��ѯ����״̬���ϱ�
 bit[11:10]  ����
 bit[9:8]    C1 ��ѯ����״̬���ϱ�
 bit[7:6]    ����
 bit[5:4]    W2 ��ѯ����״̬���ϱ�
 bit[3:2]    ����
 bit[1:0]    W1 ��ѯ����״̬���ϱ�
   UNION�ṹ:  DBG_TRIG_CTRL_CURR_STATE_RPT_UNION */
#define DBG_TRIG_CTRL_CURR_STATE_RPT_ADDR             (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8100)

/* �Ĵ���˵����
 bit[31:15]  ����
 bit[14:12]  ��ǰ��ѭռ�õ�ͨ�����ϱ�
 bit[11:8]   ��LbusArbiter����״̬���ϱ�
 bit[7:5]    ����
 bit[4]      CMD FIFO�ձ�־�ϱ�
 bit[3:1]    ����
 bit[0]      CMD FIFO����־�ϱ�
   UNION�ṹ:  DBG_TRIG_ARBIT_INTF_STATE_RPT_UNION */
#define DBG_TRIG_ARBIT_INTF_STATE_RPT_ADDR            (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8104)

/* �Ĵ���˵����
 bit[31:21]  ����
 bit[20]     G2 ��ʱ״̬�ϱ�����ƽ�źţ������ѯ״̬����Ҫ�����㴦��
 bit[19:17]  ����
 bit[16]     G1 ��ʱ״̬�ϱ�����ƽ�źţ������ѯ״̬����Ҫ�����㴦��
 bit[15:13]  ����
 bit[12]     C2 ��ʱ״̬�ϱ�����ƽ�źţ������ѯ״̬����Ҫ�����㴦��
 bit[11:9]   ����
 bit[8]      C1 ��ʱ״̬�ϱ�����ƽ�źţ������ѯ״̬����Ҫ�����㴦��
 bit[7:5]    ����
 bit[4]      W2 ��ʱ״̬�ϱ�����ƽ�źţ������ѯ״̬����Ҫ�����㴦��
 bit[3:1]    ����
 bit[0]      W1 ��ʱ״̬�ϱ�����ƽ�źţ������ѯ״̬����Ҫ�����㴦��
   UNION�ṹ:  DBG_TRIG_OVERTIME_RPT_UNION */
#define DBG_TRIG_OVERTIME_RPT_ADDR                    (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8108)



/***======================================================================***
                     (2/2) register_define_dbg_trig_mem
 ***======================================================================***/
/* �Ĵ���˵�����Ĵ�����ַ��
 bit[31:28]  ����
 bit[27:8]   �������Ĵ�������ʼ��ַ��Ϊ32bit�Ĵ�����ַ�ĵ�20bit��W1��W2����TRACE_ADDR_RAM��ͬ��ַ�Σ�G1��G2����TRACE_ADDR_RAM��ͬ��ַ�Σ�C1��C2����TRACE_ADDR_RAM��ͬ��ַ��
 bit[7:0]    �������Ĵ����ĸ�������Χ0~255��0��ʾ1���Ĵ�����255����ʾ256���Ĵ���
   UNION�ṹ:  DBG_TRIG_TRACE_ADDR_RAM_UNION */
#define DBG_TRIG_TRACE_ADDR_RAM_ADDR                  (SOC_BBP_DBG_TRIG_BASE_ADDR + 0xFC8800)
#define DBG_TRIG_TRACE_ADDR_RAM_MEMDEPTH  (384)





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
                     (1/2) register_define_dbg_trig
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : DBG_TRIG_W1_CONFIG1_UNION
 �ṹ˵��  : W1_CONFIG1 �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      w1_config1_reg;
    struct
    {
        unsigned int  cpu_w1_dbg_trig_sel   : 1;  /* bit[0]    : W1��ַ����Чʹ�ܣ����ݲ���Ŀ�Ĺ��߹�ѡʹ�ܣ� */
        unsigned int  reserved_0            : 3;  /* bit[1-3]  : ���� */
        unsigned int  cpu_w1_dbg_trig_ready : 1;  /* bit[4]    : W1���µ�ʹ�ܣ�OAM����W1ģ���µ�������ã� */
        unsigned int  reserved_1            : 3;  /* bit[5-7]  : ���� */
        unsigned int  cpu_w1_base_addr      : 12; /* bit[8-19] : W1�ߵ�ַ�ε�ַ */
        unsigned int  reserved_2            : 12; /* bit[20-31]: ���� */
    } reg;
} DBG_TRIG_W1_CONFIG1_UNION;
#define DBG_TRIG_W1_CONFIG1_cpu_w1_dbg_trig_sel_START    (0)
#define DBG_TRIG_W1_CONFIG1_cpu_w1_dbg_trig_sel_END      (0)
#define DBG_TRIG_W1_CONFIG1_cpu_w1_dbg_trig_ready_START  (4)
#define DBG_TRIG_W1_CONFIG1_cpu_w1_dbg_trig_ready_END    (4)
#define DBG_TRIG_W1_CONFIG1_cpu_w1_base_addr_START       (8)
#define DBG_TRIG_W1_CONFIG1_cpu_w1_base_addr_END         (19)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_W1_CONFIG2_UNION
 �ṹ˵��  : W1_CONFIG2 �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      w1_config2_reg;
    struct
    {
        unsigned int  cpu_w1_start_addr   : 9;  /* bit[0-8]  : W1 TRACE ADDR RAM��ʼ��ַ */
        unsigned int  reserved_0          : 3;  /* bit[9-11] : ���� */
        unsigned int  cpu_w1_dbg_trig_num : 9;  /* bit[12-20]: W1 TRACE ADDR RAM���� */
        unsigned int  reserved_1          : 11; /* bit[21-31]: ���� */
    } reg;
} DBG_TRIG_W1_CONFIG2_UNION;
#define DBG_TRIG_W1_CONFIG2_cpu_w1_start_addr_START    (0)
#define DBG_TRIG_W1_CONFIG2_cpu_w1_start_addr_END      (8)
#define DBG_TRIG_W1_CONFIG2_cpu_w1_dbg_trig_num_START  (12)
#define DBG_TRIG_W1_CONFIG2_cpu_w1_dbg_trig_num_END    (20)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_W1_START_POS_UNION
 �ṹ˵��  : W1_START_POS �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      w1_start_pos_reg;
    struct
    {
        unsigned int  cpu_w1_trig_start_pos : 16; /* bit[0-15] : W1 TRACE��ʱ��ʼλ�ã���λchip��
                                                                 bit[7:0]��symbol��chip������������Χ0~255chip��
                                                                 bit[11:8]��slot��symbol������������Χ0~9symbol��
                                                                 bit[15:12]��֡��slot������������Χ0~14slot */
        unsigned int  reserved              : 16; /* bit[16-31]: ���� */
    } reg;
} DBG_TRIG_W1_START_POS_UNION;
#define DBG_TRIG_W1_START_POS_cpu_w1_trig_start_pos_START  (0)
#define DBG_TRIG_W1_START_POS_cpu_w1_trig_start_pos_END    (15)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_W2_CONFIG1_UNION
 �ṹ˵��  : W2_CONFIG1 �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      w2_config1_reg;
    struct
    {
        unsigned int  cpu_w2_dbg_trig_sel   : 1;  /* bit[0]    : W2��ַ����Чʹ�ܣ����ݲ���Ŀ�Ĺ��߹�ѡʹ�ܣ� */
        unsigned int  reserved_0            : 3;  /* bit[1-3]  : ���� */
        unsigned int  cpu_w2_dbg_trig_ready : 1;  /* bit[4]    : W2���µ�ʹ�ܣ�OAM����W1ģ���µ�������ã� */
        unsigned int  reserved_1            : 3;  /* bit[5-7]  : ���� */
        unsigned int  cpu_w2_base_addr      : 12; /* bit[8-19] : W2�ߵ�ַ�ε�ַ */
        unsigned int  reserved_2            : 12; /* bit[20-31]: ���� */
    } reg;
} DBG_TRIG_W2_CONFIG1_UNION;
#define DBG_TRIG_W2_CONFIG1_cpu_w2_dbg_trig_sel_START    (0)
#define DBG_TRIG_W2_CONFIG1_cpu_w2_dbg_trig_sel_END      (0)
#define DBG_TRIG_W2_CONFIG1_cpu_w2_dbg_trig_ready_START  (4)
#define DBG_TRIG_W2_CONFIG1_cpu_w2_dbg_trig_ready_END    (4)
#define DBG_TRIG_W2_CONFIG1_cpu_w2_base_addr_START       (8)
#define DBG_TRIG_W2_CONFIG1_cpu_w2_base_addr_END         (19)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_W2_CONFIG2_UNION
 �ṹ˵��  : W2_CONFIG2 �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      w2_config2_reg;
    struct
    {
        unsigned int  cpu_w2_start_addr   : 9;  /* bit[0-8]  : W2 TRACE ADDR RAM��ʼ��ַ */
        unsigned int  reserved_0          : 3;  /* bit[9-11] : ���� */
        unsigned int  cpu_w2_dbg_trig_num : 9;  /* bit[12-20]: W2 TRACE ADDR RAM���� */
        unsigned int  reserved_1          : 11; /* bit[21-31]: ���� */
    } reg;
} DBG_TRIG_W2_CONFIG2_UNION;
#define DBG_TRIG_W2_CONFIG2_cpu_w2_start_addr_START    (0)
#define DBG_TRIG_W2_CONFIG2_cpu_w2_start_addr_END      (8)
#define DBG_TRIG_W2_CONFIG2_cpu_w2_dbg_trig_num_START  (12)
#define DBG_TRIG_W2_CONFIG2_cpu_w2_dbg_trig_num_END    (20)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_W2_START_POS_UNION
 �ṹ˵��  : W2_START_POS �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      w2_start_pos_reg;
    struct
    {
        unsigned int  cpu_w2_trig_start_pos : 16; /* bit[0-15] : W2 TRACE��ʱ��ʼλ�ã���λchip��
                                                                 bit[7:0]��symbol��chip������������Χ0~255chip��
                                                                 bit[11:8]��slot��symbol������������Χ0~9symbol��
                                                                 bit[15:12]��֡��slot������������Χ0~14slot */
        unsigned int  reserved              : 16; /* bit[16-31]: ���� */
    } reg;
} DBG_TRIG_W2_START_POS_UNION;
#define DBG_TRIG_W2_START_POS_cpu_w2_trig_start_pos_START  (0)
#define DBG_TRIG_W2_START_POS_cpu_w2_trig_start_pos_END    (15)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_C1_CONFIG1_UNION
 �ṹ˵��  : C1_CONFIG1 �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      c1_config1_reg;
    struct
    {
        unsigned int  cpu_c1_dbg_trig_sel   : 1;  /* bit[0]    : C1��ַ����Чʹ�ܣ����ݲ���Ŀ�Ĺ��߹�ѡʹ�ܣ� */
        unsigned int  reserved_0            : 3;  /* bit[1-3]  : ���� */
        unsigned int  cpu_c1_dbg_trig_ready : 1;  /* bit[4]    : C1���µ�ʹ�ܣ�OAM����W1ģ���µ�������ã� */
        unsigned int  reserved_1            : 3;  /* bit[5-7]  : ���� */
        unsigned int  cpu_c1_base_addr      : 12; /* bit[8-19] : C1�ߵ�ַ�ε�ַ */
        unsigned int  reserved_2            : 12; /* bit[20-31]: ���� */
    } reg;
} DBG_TRIG_C1_CONFIG1_UNION;
#define DBG_TRIG_C1_CONFIG1_cpu_c1_dbg_trig_sel_START    (0)
#define DBG_TRIG_C1_CONFIG1_cpu_c1_dbg_trig_sel_END      (0)
#define DBG_TRIG_C1_CONFIG1_cpu_c1_dbg_trig_ready_START  (4)
#define DBG_TRIG_C1_CONFIG1_cpu_c1_dbg_trig_ready_END    (4)
#define DBG_TRIG_C1_CONFIG1_cpu_c1_base_addr_START       (8)
#define DBG_TRIG_C1_CONFIG1_cpu_c1_base_addr_END         (19)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_C1_CONFIG2_UNION
 �ṹ˵��  : C1_CONFIG2 �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      c1_config2_reg;
    struct
    {
        unsigned int  cpu_c1_start_addr   : 9;  /* bit[0-8]  : C1 TRACE ADDR RAM��ʼ��ַ */
        unsigned int  reserved_0          : 3;  /* bit[9-11] : ���� */
        unsigned int  cpu_c1_dbg_trig_num : 9;  /* bit[12-20]: C1 TRACE ADDR RAM���� */
        unsigned int  reserved_1          : 11; /* bit[21-31]: ���� */
    } reg;
} DBG_TRIG_C1_CONFIG2_UNION;
#define DBG_TRIG_C1_CONFIG2_cpu_c1_start_addr_START    (0)
#define DBG_TRIG_C1_CONFIG2_cpu_c1_start_addr_END      (8)
#define DBG_TRIG_C1_CONFIG2_cpu_c1_dbg_trig_num_START  (12)
#define DBG_TRIG_C1_CONFIG2_cpu_c1_dbg_trig_num_END    (20)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_C1_START_POS_UNION
 �ṹ˵��  : C1_START_POS �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      c1_start_pos_reg;
    struct
    {
        unsigned int  cpu_c1_trig_start_pos : 15; /* bit[0-14] : C1 TRACE��ʱ��ʼλ�ã���λchip��
                                                                 EVDO��
                                                                 bit[14:0]��֡��chip������������Χ0~32767chip��ʱ�䳤��80/3ms��
                                                                 1X��
                                                                 bit[10:0]��PCG��chip������������Χ0~1535chip��ʱ�䳤��80/64��
                                                                 bit[14:11]��PCG������������Χ0~15��ʱ�䳤��20ms�� */
        unsigned int  reserved              : 17; /* bit[15-31]: ���� */
    } reg;
} DBG_TRIG_C1_START_POS_UNION;
#define DBG_TRIG_C1_START_POS_cpu_c1_trig_start_pos_START  (0)
#define DBG_TRIG_C1_START_POS_cpu_c1_trig_start_pos_END    (14)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_C2_CONFIG1_UNION
 �ṹ˵��  : C2_CONFIG1 �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      c2_config1_reg;
    struct
    {
        unsigned int  cpu_c2_dbg_trig_sel   : 1;  /* bit[0]    : C2��ַ����Чʹ�ܣ����ݲ���Ŀ�Ĺ��߹�ѡʹ�ܣ� */
        unsigned int  reserved_0            : 3;  /* bit[1-3]  : ���� */
        unsigned int  cpu_c2_dbg_trig_ready : 1;  /* bit[4]    : C2���µ�ʹ�ܣ�OAM����W1ģ���µ�������ã� */
        unsigned int  reserved_1            : 3;  /* bit[5-7]  : ���� */
        unsigned int  cpu_c2_base_addr      : 12; /* bit[8-19] : C2�ߵ�ַ�ε�ַ */
        unsigned int  reserved_2            : 12; /* bit[20-31]: ���� */
    } reg;
} DBG_TRIG_C2_CONFIG1_UNION;
#define DBG_TRIG_C2_CONFIG1_cpu_c2_dbg_trig_sel_START    (0)
#define DBG_TRIG_C2_CONFIG1_cpu_c2_dbg_trig_sel_END      (0)
#define DBG_TRIG_C2_CONFIG1_cpu_c2_dbg_trig_ready_START  (4)
#define DBG_TRIG_C2_CONFIG1_cpu_c2_dbg_trig_ready_END    (4)
#define DBG_TRIG_C2_CONFIG1_cpu_c2_base_addr_START       (8)
#define DBG_TRIG_C2_CONFIG1_cpu_c2_base_addr_END         (19)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_C2_CONFIG2_UNION
 �ṹ˵��  : C2_CONFIG2 �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      c2_config2_reg;
    struct
    {
        unsigned int  cpu_c2_start_addr   : 9;  /* bit[0-8]  : C2 TRACE ADDR RAM��ʼ��ַ */
        unsigned int  reserved_0          : 3;  /* bit[9-11] : ���� */
        unsigned int  cpu_c2_dbg_trig_num : 9;  /* bit[12-20]: C2 TRACE ADDR RAM���� */
        unsigned int  reserved_1          : 11; /* bit[21-31]: ���� */
    } reg;
} DBG_TRIG_C2_CONFIG2_UNION;
#define DBG_TRIG_C2_CONFIG2_cpu_c2_start_addr_START    (0)
#define DBG_TRIG_C2_CONFIG2_cpu_c2_start_addr_END      (8)
#define DBG_TRIG_C2_CONFIG2_cpu_c2_dbg_trig_num_START  (12)
#define DBG_TRIG_C2_CONFIG2_cpu_c2_dbg_trig_num_END    (20)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_C2_START_POS_UNION
 �ṹ˵��  : C2_START_POS �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      c2_start_pos_reg;
    struct
    {
        unsigned int  cpu_c2_trig_start_pos : 15; /* bit[0-14] : C2 TRACE��ʱ��ʼλ�ã���λchip��
                                                                 EVDO��
                                                                 bit[14:0]��֡��chip������������Χ0~32767chip��ʱ�䳤��80/3ms��
                                                                 1X��
                                                                 bit[10:0]��PCG��chip������������Χ0~1535chip��ʱ�䳤��80/64��
                                                                 bit[14:11]��PCG������������Χ0~15��ʱ�䳤��20ms�� */
        unsigned int  reserved              : 17; /* bit[15-31]: ���� */
    } reg;
} DBG_TRIG_C2_START_POS_UNION;
#define DBG_TRIG_C2_START_POS_cpu_c2_trig_start_pos_START  (0)
#define DBG_TRIG_C2_START_POS_cpu_c2_trig_start_pos_END    (14)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_G1_CONFIG1_UNION
 �ṹ˵��  : G1_CONFIG1 �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g1_config1_reg;
    struct
    {
        unsigned int  cpu_g1_dbg_trig_sel   : 1;  /* bit[0]    : G1��ַ����Чʹ�ܣ����ݲ���Ŀ�Ĺ��߹�ѡʹ�ܣ� */
        unsigned int  reserved_0            : 3;  /* bit[1-3]  : ���� */
        unsigned int  cpu_g1_dbg_trig_ready : 1;  /* bit[4]    : G1���µ�ʹ�ܣ�OAM����W1ģ���µ�������ã� */
        unsigned int  reserved_1            : 3;  /* bit[5-7]  : ���� */
        unsigned int  cpu_g1_base_addr      : 12; /* bit[8-19] : G1�ߵ�ַ�ε�ַ */
        unsigned int  reserved_2            : 12; /* bit[20-31]: ���� */
    } reg;
} DBG_TRIG_G1_CONFIG1_UNION;
#define DBG_TRIG_G1_CONFIG1_cpu_g1_dbg_trig_sel_START    (0)
#define DBG_TRIG_G1_CONFIG1_cpu_g1_dbg_trig_sel_END      (0)
#define DBG_TRIG_G1_CONFIG1_cpu_g1_dbg_trig_ready_START  (4)
#define DBG_TRIG_G1_CONFIG1_cpu_g1_dbg_trig_ready_END    (4)
#define DBG_TRIG_G1_CONFIG1_cpu_g1_base_addr_START       (8)
#define DBG_TRIG_G1_CONFIG1_cpu_g1_base_addr_END         (19)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_G1_CONFIG2_UNION
 �ṹ˵��  : G1_CONFIG2 �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g1_config2_reg;
    struct
    {
        unsigned int  cpu_g1_start_addr   : 9;  /* bit[0-8]  : G1 TRACE ADDR RAM��ʼ��ַ */
        unsigned int  reserved_0          : 3;  /* bit[9-11] : ���� */
        unsigned int  cpu_g1_dbg_trig_num : 9;  /* bit[12-20]: G1 TRACE ADDR RAM���� */
        unsigned int  reserved_1          : 11; /* bit[21-31]: ���� */
    } reg;
} DBG_TRIG_G1_CONFIG2_UNION;
#define DBG_TRIG_G1_CONFIG2_cpu_g1_start_addr_START    (0)
#define DBG_TRIG_G1_CONFIG2_cpu_g1_start_addr_END      (8)
#define DBG_TRIG_G1_CONFIG2_cpu_g1_dbg_trig_num_START  (12)
#define DBG_TRIG_G1_CONFIG2_cpu_g1_dbg_trig_num_END    (20)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_G1_START_POS_UNION
 �ṹ˵��  : G1_START_POS �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g1_start_pos_reg;
    struct
    {
        unsigned int  cpu_g1_trig_start_pos : 13; /* bit[0-12] : G1 TRACE��ʱ��ʼλ�ã���λQb��
                                                                 bit[12:0]��gtc_tdma_qb�ϵ�֡��Qb������������Χ0~4999Qb�� */
        unsigned int  reserved              : 19; /* bit[13-31]: ���� */
    } reg;
} DBG_TRIG_G1_START_POS_UNION;
#define DBG_TRIG_G1_START_POS_cpu_g1_trig_start_pos_START  (0)
#define DBG_TRIG_G1_START_POS_cpu_g1_trig_start_pos_END    (12)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_G2_CONFIG1_UNION
 �ṹ˵��  : G2_CONFIG1 �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g2_config1_reg;
    struct
    {
        unsigned int  cpu_g2_dbg_trig_sel   : 1;  /* bit[0]    : G2��ַ����Чʹ�ܣ����ݲ���Ŀ�Ĺ��߹�ѡʹ�ܣ� */
        unsigned int  reserved_0            : 3;  /* bit[1-3]  : ���� */
        unsigned int  cpu_g2_dbg_trig_ready : 1;  /* bit[4]    : G2���µ�ʹ�ܣ�OAM����W1ģ���µ�������ã� */
        unsigned int  reserved_1            : 3;  /* bit[5-7]  : ���� */
        unsigned int  cpu_g2_base_addr      : 12; /* bit[8-19] : G2�ߵ�ַ�ε�ַ */
        unsigned int  reserved_2            : 12; /* bit[20-31]: ���� */
    } reg;
} DBG_TRIG_G2_CONFIG1_UNION;
#define DBG_TRIG_G2_CONFIG1_cpu_g2_dbg_trig_sel_START    (0)
#define DBG_TRIG_G2_CONFIG1_cpu_g2_dbg_trig_sel_END      (0)
#define DBG_TRIG_G2_CONFIG1_cpu_g2_dbg_trig_ready_START  (4)
#define DBG_TRIG_G2_CONFIG1_cpu_g2_dbg_trig_ready_END    (4)
#define DBG_TRIG_G2_CONFIG1_cpu_g2_base_addr_START       (8)
#define DBG_TRIG_G2_CONFIG1_cpu_g2_base_addr_END         (19)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_G2_CONFIG2_UNION
 �ṹ˵��  : G2_CONFIG2 �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g2_config2_reg;
    struct
    {
        unsigned int  cpu_g2_start_addr   : 9;  /* bit[0-8]  : G2 TRACE ADDR RAM��ʼ��ַ */
        unsigned int  reserved_0          : 3;  /* bit[9-11] : ���� */
        unsigned int  cpu_g2_dbg_trig_num : 9;  /* bit[12-20]: G2 TRACE ADDR RAM���� */
        unsigned int  reserved_1          : 11; /* bit[21-31]: ���� */
    } reg;
} DBG_TRIG_G2_CONFIG2_UNION;
#define DBG_TRIG_G2_CONFIG2_cpu_g2_start_addr_START    (0)
#define DBG_TRIG_G2_CONFIG2_cpu_g2_start_addr_END      (8)
#define DBG_TRIG_G2_CONFIG2_cpu_g2_dbg_trig_num_START  (12)
#define DBG_TRIG_G2_CONFIG2_cpu_g2_dbg_trig_num_END    (20)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_G2_START_POS_UNION
 �ṹ˵��  : G2_START_POS �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      g2_start_pos_reg;
    struct
    {
        unsigned int  cpu_g2_trig_start_pos : 13; /* bit[0-12] : G2 TRACE��ʱ��ʼλ�ã���λQb��
                                                                 bit[12:0]��gtc_tdma_qb�ϵ�֡��Qb������������Χ0~4999Qb�� */
        unsigned int  reserved              : 19; /* bit[13-31]: ���� */
    } reg;
} DBG_TRIG_G2_START_POS_UNION;
#define DBG_TRIG_G2_START_POS_cpu_g2_trig_start_pos_START  (0)
#define DBG_TRIG_G2_START_POS_cpu_g2_trig_start_pos_END    (12)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_MEM_CTRL0_DBG_UNION
 �ṹ˵��  : MEM_CTRL0_DBG �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x03501050�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mem_ctrl0_dbg_reg;
    struct
    {
        unsigned int  mem_ctrl_s_dbg      : 16; /* bit[0-15] : ���˿�ram��ʱ���ơ� */
        unsigned int  mem_ctrl_d_1w2r_dbg : 16; /* bit[16-31]: 1w2r˫�˿�ram��ʱ���ơ� */
    } reg;
} DBG_TRIG_MEM_CTRL0_DBG_UNION;
#define DBG_TRIG_MEM_CTRL0_DBG_mem_ctrl_s_dbg_START       (0)
#define DBG_TRIG_MEM_CTRL0_DBG_mem_ctrl_s_dbg_END         (15)
#define DBG_TRIG_MEM_CTRL0_DBG_mem_ctrl_d_1w2r_dbg_START  (16)
#define DBG_TRIG_MEM_CTRL0_DBG_mem_ctrl_d_1w2r_dbg_END    (31)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_MEM_CTRL1_DBG_UNION
 �ṹ˵��  : MEM_CTRL1_DBG �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x00700057�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mem_ctrl1_dbg_reg;
    struct
    {
        unsigned int  mem_ctrl_d_1rw2rw_dbg : 16; /* bit[0-15] : 1rw2rw˫�˿�ram��ʱ���ơ� */
        unsigned int  rom_ctrl_dbg          : 8;  /* bit[16-23]: rom��ʱ���ơ� */
        unsigned int  reserved              : 8;  /* bit[24-31]: ���� */
    } reg;
} DBG_TRIG_MEM_CTRL1_DBG_UNION;
#define DBG_TRIG_MEM_CTRL1_DBG_mem_ctrl_d_1rw2rw_dbg_START  (0)
#define DBG_TRIG_MEM_CTRL1_DBG_mem_ctrl_d_1rw2rw_dbg_END    (15)
#define DBG_TRIG_MEM_CTRL1_DBG_rom_ctrl_dbg_START           (16)
#define DBG_TRIG_MEM_CTRL1_DBG_rom_ctrl_dbg_END             (23)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_OVERTIME_CLR_UNION
 �ṹ˵��  : OVERTIME_CLR �Ĵ����ṹ���塣��ַƫ����:0x050����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      overtime_clr_reg;
    struct
    {
        unsigned int  cpu_overtime_clr : 1;  /* bit[0]   : ��ʱ�����������壬6ģ���á� */
        unsigned int  reserved         : 31; /* bit[1-31]: ���� */
    } reg;
} DBG_TRIG_OVERTIME_CLR_UNION;
#define DBG_TRIG_OVERTIME_CLR_cpu_overtime_clr_START  (0)
#define DBG_TRIG_OVERTIME_CLR_cpu_overtime_clr_END    (0)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_CTRL_CURR_STATE_RPT_UNION
 �ṹ˵��  : CTRL_CURR_STATE_RPT �Ĵ����ṹ���塣��ַƫ����:0x100����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      ctrl_curr_state_rpt_reg;
    struct
    {
        unsigned int  w1_curr_st : 2;  /* bit[0-1]  : W1 ��ѯ����״̬���ϱ� */
        unsigned int  reserved_0 : 2;  /* bit[2-3]  : ���� */
        unsigned int  w2_curr_st : 2;  /* bit[4-5]  : W2 ��ѯ����״̬���ϱ� */
        unsigned int  reserved_1 : 2;  /* bit[6-7]  : ���� */
        unsigned int  c1_curr_st : 2;  /* bit[8-9]  : C1 ��ѯ����״̬���ϱ� */
        unsigned int  reserved_2 : 2;  /* bit[10-11]: ���� */
        unsigned int  c2_curr_st : 2;  /* bit[12-13]: C2 ��ѯ����״̬���ϱ� */
        unsigned int  reserved_3 : 2;  /* bit[14-15]: ���� */
        unsigned int  g1_curr_st : 2;  /* bit[16-17]: G1 ��ѯ����״̬���ϱ� */
        unsigned int  reserved_4 : 2;  /* bit[18-19]: ���� */
        unsigned int  g2_curr_st : 2;  /* bit[20-21]: G2 ��ѯ����״̬���ϱ� */
        unsigned int  reserved_5 : 10; /* bit[22-31]: ���� */
    } reg;
} DBG_TRIG_CTRL_CURR_STATE_RPT_UNION;
#define DBG_TRIG_CTRL_CURR_STATE_RPT_w1_curr_st_START  (0)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_w1_curr_st_END    (1)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_w2_curr_st_START  (4)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_w2_curr_st_END    (5)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_c1_curr_st_START  (8)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_c1_curr_st_END    (9)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_c2_curr_st_START  (12)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_c2_curr_st_END    (13)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_g1_curr_st_START  (16)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_g1_curr_st_END    (17)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_g2_curr_st_START  (20)
#define DBG_TRIG_CTRL_CURR_STATE_RPT_g2_curr_st_END    (21)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_ARBIT_INTF_STATE_RPT_UNION
 �ṹ˵��  : ARBIT_INTF_STATE_RPT �Ĵ����ṹ���塣��ַƫ����:0x104����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      arbit_intf_state_rpt_reg;
    struct
    {
        unsigned int  cfifo_full  : 1;  /* bit[0]    : CMD FIFO����־�ϱ� */
        unsigned int  reserved_0  : 3;  /* bit[1-3]  : ���� */
        unsigned int  cfifo_empty : 1;  /* bit[4]    : CMD FIFO�ձ�־�ϱ� */
        unsigned int  reserved_1  : 3;  /* bit[5-7]  : ���� */
        unsigned int  lbus_st     : 4;  /* bit[8-11] : ��LbusArbiter����״̬���ϱ� */
        unsigned int  req_num     : 3;  /* bit[12-14]: ��ǰ��ѭռ�õ�ͨ�����ϱ� */
        unsigned int  reserved_2  : 17; /* bit[15-31]: ���� */
    } reg;
} DBG_TRIG_ARBIT_INTF_STATE_RPT_UNION;
#define DBG_TRIG_ARBIT_INTF_STATE_RPT_cfifo_full_START   (0)
#define DBG_TRIG_ARBIT_INTF_STATE_RPT_cfifo_full_END     (0)
#define DBG_TRIG_ARBIT_INTF_STATE_RPT_cfifo_empty_START  (4)
#define DBG_TRIG_ARBIT_INTF_STATE_RPT_cfifo_empty_END    (4)
#define DBG_TRIG_ARBIT_INTF_STATE_RPT_lbus_st_START      (8)
#define DBG_TRIG_ARBIT_INTF_STATE_RPT_lbus_st_END        (11)
#define DBG_TRIG_ARBIT_INTF_STATE_RPT_req_num_START      (12)
#define DBG_TRIG_ARBIT_INTF_STATE_RPT_req_num_END        (14)


/*****************************************************************************
 �ṹ��    : DBG_TRIG_OVERTIME_RPT_UNION
 �ṹ˵��  : OVERTIME_RPT �Ĵ����ṹ���塣��ַƫ����:0x108����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      overtime_rpt_reg;
    struct
    {
        unsigned int  w1_overtime_rpt : 1;  /* bit[0]    : W1 ��ʱ״̬�ϱ�����ƽ�źţ������ѯ״̬����Ҫ�����㴦�� */
        unsigned int  reserved_0      : 3;  /* bit[1-3]  : ���� */
        unsigned int  w2_overtime_rpt : 1;  /* bit[4]    : W2 ��ʱ״̬�ϱ�����ƽ�źţ������ѯ״̬����Ҫ�����㴦�� */
        unsigned int  reserved_1      : 3;  /* bit[5-7]  : ���� */
        unsigned int  c1_overtime_rpt : 1;  /* bit[8]    : C1 ��ʱ״̬�ϱ�����ƽ�źţ������ѯ״̬����Ҫ�����㴦�� */
        unsigned int  reserved_2      : 3;  /* bit[9-11] : ���� */
        unsigned int  c2_overtime_rpt : 1;  /* bit[12]   : C2 ��ʱ״̬�ϱ�����ƽ�źţ������ѯ״̬����Ҫ�����㴦�� */
        unsigned int  reserved_3      : 3;  /* bit[13-15]: ���� */
        unsigned int  g1_overtime_rpt : 1;  /* bit[16]   : G1 ��ʱ״̬�ϱ�����ƽ�źţ������ѯ״̬����Ҫ�����㴦�� */
        unsigned int  reserved_4      : 3;  /* bit[17-19]: ���� */
        unsigned int  g2_overtime_rpt : 1;  /* bit[20]   : G2 ��ʱ״̬�ϱ�����ƽ�źţ������ѯ״̬����Ҫ�����㴦�� */
        unsigned int  reserved_5      : 11; /* bit[21-31]: ���� */
    } reg;
} DBG_TRIG_OVERTIME_RPT_UNION;
#define DBG_TRIG_OVERTIME_RPT_w1_overtime_rpt_START  (0)
#define DBG_TRIG_OVERTIME_RPT_w1_overtime_rpt_END    (0)
#define DBG_TRIG_OVERTIME_RPT_w2_overtime_rpt_START  (4)
#define DBG_TRIG_OVERTIME_RPT_w2_overtime_rpt_END    (4)
#define DBG_TRIG_OVERTIME_RPT_c1_overtime_rpt_START  (8)
#define DBG_TRIG_OVERTIME_RPT_c1_overtime_rpt_END    (8)
#define DBG_TRIG_OVERTIME_RPT_c2_overtime_rpt_START  (12)
#define DBG_TRIG_OVERTIME_RPT_c2_overtime_rpt_END    (12)
#define DBG_TRIG_OVERTIME_RPT_g1_overtime_rpt_START  (16)
#define DBG_TRIG_OVERTIME_RPT_g1_overtime_rpt_END    (16)
#define DBG_TRIG_OVERTIME_RPT_g2_overtime_rpt_START  (20)
#define DBG_TRIG_OVERTIME_RPT_g2_overtime_rpt_END    (20)


/***======================================================================***
                     (2/2) register_define_dbg_trig_mem
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : DBG_TRIG_TRACE_ADDR_RAM_UNION
 �ṹ˵��  : TRACE_ADDR_RAM �Ĵ����ṹ���塣��ַƫ����:0x800����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ�����ַ��
*****************************************************************************/
typedef union
{
    unsigned int      trace_addr_ram_reg;
    struct
    {
        unsigned int  len        : 8;  /* bit[0-7]  : �������Ĵ����ĸ�������Χ0~255��0��ʾ1���Ĵ�����255����ʾ256���Ĵ��� */
        unsigned int  start_addr : 20; /* bit[8-27] : �������Ĵ�������ʼ��ַ��Ϊ32bit�Ĵ�����ַ�ĵ�20bit��W1��W2����TRACE_ADDR_RAM��ͬ��ַ�Σ�G1��G2����TRACE_ADDR_RAM��ͬ��ַ�Σ�C1��C2����TRACE_ADDR_RAM��ͬ��ַ�� */
        unsigned int  reserved   : 4;  /* bit[28-31]: ���� */
    } reg;
} DBG_TRIG_TRACE_ADDR_RAM_UNION;
#define DBG_TRIG_TRACE_ADDR_RAM_len_START         (0)
#define DBG_TRIG_TRACE_ADDR_RAM_len_END           (7)
#define DBG_TRIG_TRACE_ADDR_RAM_start_addr_START  (8)
#define DBG_TRIG_TRACE_ADDR_RAM_start_addr_END    (27)




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

#endif /* end of bbp_dbg_trig_interface.h */
