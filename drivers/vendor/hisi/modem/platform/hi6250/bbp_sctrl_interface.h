/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : bbp_sctrl_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-08-28 11:55:13
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��8��28��
    ��    ��   : l00165286
    �޸�����   : �ӡ�Dallas ��Ӳ���ӿ�˵����_SCTRL.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __BBP_SCTRL_INTERFACE_H__
#define __BBP_SCTRL_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/***======================================================================***
                     (1/1) register_define_BBP_SYSCTRL
 ***======================================================================***/
/* �Ĵ���˵����BBP��Դ����ʹ��(C��)
 bit[31:3]   ������
 bit[2]      IRM��Դ���ϵ���λ��
             д1��λ��д0��Ч��
 bit[1]      WTC��Դ���ϵ���λ��
             д1��λ��д0��Ч��
 bit[0]      LTE��Դ���ϵ���λ��
             д1��λ��д0��Ч��
   UNION�ṹ:  BBPSCTRL_BBP_MTCMOS_SET_UNION */
#define BBPSCTRL_BBP_MTCMOS_SET_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x0)

/* �Ĵ���˵����BBP��Դ���ƹر�(C��)
 bit[31:3]   ������
 bit[2]      IRM��Դ���ϵ������
             д1���㣬д0��Ч��
 bit[1]      WTC��Դ���ϵ������
             д1���㣬д0��Ч��
 bit[0]      LTE��Դ���ϵ������
             д1���㣬д0��Ч��
   UNION�ṹ:  BBPSCTRL_BBP_MTCMOS_CLR_UNION */
#define BBPSCTRL_BBP_MTCMOS_CLR_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x4)

/* �Ĵ���˵����BBP��Դ����״̬(C��)
 bit[31:3]   ������
 bit[2]      IRM��Դ���Դ״̬��
             1���ϵ�
             0���µ�
 bit[1]      WTC��Դ���Դ״̬��
             1���ϵ�
             0���µ�
 bit[0]      LTE��Դ���Դ״̬��
             1���ϵ�
             0���µ�
   UNION�ṹ:  BBPSCTRL_BBP_MTCMOS_STATUS_UNION */
#define BBPSCTRL_BBP_MTCMOS_STATUS_ADDR               (SOC_BBP_SCTRL_BASE_ADDR + 0x8)

/* �Ĵ���˵����BBP��Դ�������ʹ��(C��)
 bit[31:3]   ������
 bit[2]      IRM��Դ�������λ��
             д1��λ��д0��Ч��
 bit[1]      WTC��Դ�������λ��
             д1��λ��д0��Ч��
 bit[0]      LTE��Դ�������λ��
             д1��λ��д0��Ч��
   UNION�ṹ:  BBPSCTRL_BBP_ISO_EN_SET_UNION */
#define BBPSCTRL_BBP_ISO_EN_SET_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x10)

/* �Ĵ���˵����BBP��Դ������ƹر�(C��)
 bit[31:3]   ������
 bit[2]      IRM��Դ����������
             д1���㣬д0��Ч��
 bit[1]      WTC��Դ����������
             д1���㣬д0��Ч��
 bit[0]      LTE��Դ����������
             д1���㣬д0��Ч��
   UNION�ṹ:  BBPSCTRL_BBP_ISO_EN_CLR_UNION */
#define BBPSCTRL_BBP_ISO_EN_CLR_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x14)

/* �Ĵ���˵����BBP��Դ�������״̬(C��)
 bit[31:3]   ������
 bit[2]      IRM��Դ�����״̬��
             1�����룻
             0��������룻
 bit[1]      WTC��Դ�����״̬��
             1�����룻
             0��������룻
 bit[0]      LTE��Դ�����״̬��
             1�����룻
             0��������룻
   UNION�ṹ:  BBPSCTRL_BBP_ISO_EN_STATUS_UNION */
#define BBPSCTRL_BBP_ISO_EN_STATUS_ADDR               (SOC_BBP_SCTRL_BASE_ADDR + 0x18)

/* �Ĵ���˵����BBP��Դ��ʱ��ʹ��(C��)
 bit[31:3]   ������
 bit[2]      IRM��Դ��ʱ��ʹ�ܡ�
             д1��λ��д0��Ч��
 bit[1]      WTC��Դ��ʱ��ʹ�ܡ�
             д1��λ��д0��Ч��
 bit[0]      LTE��Դ��ʱ��ʹ�ܡ�
             д1��λ��д0��Ч��
   UNION�ṹ:  BBPSCTRL_BBP_PD_CLK_SET_UNION */
#define BBPSCTRL_BBP_PD_CLK_SET_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x20)

/* �Ĵ���˵����BBP��Դ��ʱ�ӹر�(C��)
 bit[31:3]   ������
 bit[2]      IRM��Դ��ʱ�ӹرա�
             д1�رգ�д0��Ч��
 bit[1]      WTC��Դ��ʱ�ӹرա�
             д1�رգ�д0��Ч��
 bit[0]      LTE��Դ��ʱ�ӹرա�
             д1�رգ�д0��Ч��
   UNION�ṹ:  BBPSCTRL_BBP_PD_CLK_CLR_UNION */
#define BBPSCTRL_BBP_PD_CLK_CLR_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x24)

/* �Ĵ���˵����BBP��Դ��ʱ���ſ�״̬(C��)
 bit[31:3]   ������
 bit[2]      IRM��Դ��ʱ��״̬��
             1��ʱ��ʹ��
             0��ʱ�ӹر�
 bit[1]      WTC��Դ��ʱ��״̬��
             1��ʱ��ʹ��
             0��ʱ�ӹر�
 bit[0]      LTE��Դ��ʱ��״̬��
             1��ʱ��ʹ��
             0��ʱ�ӹر�
   UNION�ṹ:  BBPSCTRL_BBP_PD_CLK_STATUS_UNION */
#define BBPSCTRL_BBP_PD_CLK_STATUS_ADDR               (SOC_BBP_SCTRL_BASE_ADDR + 0x28)

/* �Ĵ���˵����BBP��Դ��λ����ʹ��(C��)
 bit[31:3]   ������
 bit[2]      IRM��Դ��λ����
             д1��λ��д0��Ч��
 bit[1]      WTC��Դ��λ����
             д1��λ��д0��Ч��
 bit[0]      LTE��Դ��λ����
             д1��λ��д0��Ч��
   UNION�ṹ:  BBPSCTRL_BBP_PD_SRST_SET_UNION */
#define BBPSCTRL_BBP_PD_SRST_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x30)

/* �Ĵ���˵����BBP��Դ��λ����ر�(C��)
 bit[31:3]   ������
 bit[2]      IRM��Դ��λ�����
             д1�����λ��д0��Ч��
 bit[1]      WTC��Դ��λ�����
             д1�����λ��д0��Ч��
 bit[0]      LTE��Դ��λ�����
             д1�����λ��д0��Ч��
   UNION�ṹ:  BBPSCTRL_BBP_PD_SRST_CLR_UNION */
#define BBPSCTRL_BBP_PD_SRST_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x34)

/* �Ĵ���˵����BBP��Դ��λ����״̬(C��)
 bit[31:3]   ������
 bit[2]      IRM��Դ��λ״̬��
             1����λ��
             0�������λ��
 bit[1]      WTC��Դ��λ״̬��
             1����λ��
             0�������λ��
 bit[0]      LTE��Դ��λ״̬��
             1����λ��
             0�������λ��
   UNION�ṹ:  BBPSCTRL_BBP_PD_SRST_STATUS_UNION */
#define BBPSCTRL_BBP_PD_SRST_STATUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x38)

/* �Ĵ���˵����BBP��Դ���Ƶ��ʱ��ʹ��(lte/wtc/irm)
 bit[31:27]  ������Debugʹ�á�
 bit[26]     
 bit[25]     
 bit[24]     
 bit[23]     
 bit[22]     
 bit[21]     
 bit[20]     
 bit[19]     
 bit[18]     
 bit[17]     
 bit[16]     
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      BLV7R5�汾�����ź�ͬʱ����LTE PD��IRM PD��
             DALLAS�汾�����ź���LTE PDȡ������ʹ�ã�ֻ������IRM PD
 bit[8]      BLV7R5�汾�����ź�ͬʱ����LTE PD��IRM PD��
             DALLAS�汾�����ź���LTE PDȡ������ʹ�ã�ֻ������IRM PD
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_BBP_CLK0_SET_UNION */
#define BBPSCTRL_BBP_CLK0_SET_ADDR                    (SOC_BBP_SCTRL_BASE_ADDR + 0x40)

/* �Ĵ���˵����BBP��Դ���Ƶ��ʱ�ӹر�(lte/wtc/irm)
 bit[31:27]  ������Debugʹ�á�
 bit[26]     
 bit[25]     
 bit[24]     
 bit[23]     
 bit[22]     
 bit[21]     
 bit[20]     
 bit[19]     
 bit[18]     
 bit[17]     
 bit[16]     
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      BLV7R5�汾�����ź�ͬʱ����LTE PD��IRM PD��
             DALLAS�汾�����ź���LTE PDȡ������ʹ�ã�ֻ��IRM PD��Ч
 bit[8]      BLV7R5�汾�����ź�ͬʱ����LTE PD��IRM PD��
             DALLAS�汾�����ź���LTE PDȡ������ʹ�ã�ֻ��IRM PD��Ч
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_BBP_CLK0_CLR_UNION */
#define BBPSCTRL_BBP_CLK0_CLR_ADDR                    (SOC_BBP_SCTRL_BASE_ADDR + 0x44)

/* �Ĵ���˵����BBP��Դ���Ƶ��ʱ���ſ�״̬(lte/wtc/irm)
 bit[31:27]  ������Debugʹ�á�
 bit[26]     
 bit[25]     
 bit[24]     
 bit[23]     
 bit[22]     
 bit[21]     
 bit[20]     
 bit[19]     
 bit[18]     
 bit[17]     
 bit[16]     
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      BLV7R5�汾�����ź�ͬʱ����LTE PD��IRM PD��
             DALLAS�汾�����ź���LTE PDȡ������ʹ�ã�ֻ��IRM PD��Ч
 bit[8]      BLV7R5�汾�����ź�ͬʱ����LTE PD��IRM PD��
             DALLAS�汾�����ź���LTE PDȡ������ʹ�ã�ֻ��IRM PD��Ч
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_BBP_CLK0_STATUS_UNION */
#define BBPSCTRL_BBP_CLK0_STATUS_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x48)

/* �Ĵ���˵����BBP��Դ���Ƶ��ʱ��ʹ��(com)
 bit[31:15]  ������Debugʹ�á�
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_BBP_CLK1_SET_UNION */
#define BBPSCTRL_BBP_CLK1_SET_ADDR                    (SOC_BBP_SCTRL_BASE_ADDR + 0x50)

/* �Ĵ���˵����BBP��Դ���Ƶ��ʱ�ӹر�(com)
 bit[31:15]  ������Debugʹ�á�
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_BBP_CLK1_CLR_UNION */
#define BBPSCTRL_BBP_CLK1_CLR_ADDR                    (SOC_BBP_SCTRL_BASE_ADDR + 0x54)

/* �Ĵ���˵����BBP��Դ���Ƶ��ʱ���ſ�״̬(com)
 bit[31:15]  ������Debugʹ�á�
 bit[14]     
 bit[13]     C2
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      PDF
 bit[6]      ULHB
 bit[5]      PDT
 bit[4]      TDS
 bit[3]      WTC
 bit[2]      G
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_BBP_CLK1_STATUS_UNION */
#define BBPSCTRL_BBP_CLK1_STATUS_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x58)

/* �Ĵ���˵����BBPϵͳ������6��λ(UC2_CLK_EN)
 bit[31:7]   ������
 bit[6]      UC2��TCXOʱ��ʹ��
             д1��λ��д0��Ч��
 bit[5]      UC2��WCģ����245Mʱ��ʹ��
             д1��λ��д0��Ч��
 bit[4]      UC2��WCģ����122Mʱ��ʹ��
             д1��λ��д0��Ч��
 bit[3]      UC2��WCģ����122Mʱ��ʹ��
             д1��λ��д0��Ч��
 bit[2]      UC2��Cģ122Mʱ��ʹ��
             д1��λ��д0��Ч��
 bit[1]      UC2��Wģ122Mʱ��ʹ�ܣ�dallas����Ҫʹ��
             д1��λ��д0��Ч��
 bit[0]      UC2��Wģ61Mʱ��ʹ�ܣ�dallas����Ҫʹ��
             д1��λ��д0��Ч��
   UNION�ṹ:  BBPSCTRL_BBP_SCTRL6_SET_UNION */
#define BBPSCTRL_BBP_SCTRL6_SET_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x60)

/* �Ĵ���˵����BBPϵͳ������6����(UC2_CLK_DIS)
 bit[31:7]   ������
 bit[6]      UC2��TCXOʱ�ӹر�
             д1�رգ�д0��Ч��
 bit[5]      UC2��WCģ����245Mʱ�ӹر�
             д1�رգ�д0��Ч��
 bit[4]      UC2��WCģ����122Mʱ�ӹر�
             д1�رգ�д0��Ч��
 bit[3]      UC2��WCģ����122Mʱ�ӹر�
             д1�رգ�д0��Ч��
 bit[2]      UC2��Cģ122Mʱ�ӹر�
             д1�رգ�д0��Ч��
 bit[1]      UC2��Wģ122Mʱ�ӹر�
             д1�رգ�д0��Ч��
 bit[0]      UC2��Wģ61Mʱ�ӹر�
             д1�رգ�д0��Ч��
   UNION�ṹ:  BBPSCTRL_BBP_SCTRL6_CLR_UNION */
#define BBPSCTRL_BBP_SCTRL6_CLR_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x64)

/* �Ĵ���˵����BBPϵͳ������6״̬(UC2_CLK_STATUS)
 bit[31:7]   ������
 bit[6]      UC2��TCXOʱ��״̬
             1��ʱ��ʹ��
             0��ʱ�ӹر�
 bit[5]      UC2��WCģ����245Mʱ��״̬
             1��ʱ��ʹ��
             0��ʱ�ӹر�
 bit[4]      UC2��WCģ����122Mʱ��״̬
             1��ʱ��ʹ��
             0��ʱ�ӹر�
 bit[3]      UC2��WCģ����122Mʱ��״̬
             1��ʱ��ʹ��
             0��ʱ�ӹر�
 bit[2]      UC2��Cģ122Mʱ��״̬
             1��ʱ��ʹ��
             0��ʱ�ӹر�
 bit[1]      UC2��Wģ122Mʱ��״̬
             1��ʱ��ʹ��
             0��ʱ�ӹر�
 bit[0]      UC2��Wģ61Mʱ��״̬
             1��ʱ��ʹ��
             0��ʱ�ӹر�
   UNION�ṹ:  BBPSCTRL_BBP_SCTRL6_STSTUS_UNION */
#define BBPSCTRL_BBP_SCTRL6_STSTUS_ADDR               (SOC_BBP_SCTRL_BASE_ADDR + 0x68)

/* �Ĵ���˵����BBPϵͳ������7��λ(UC2_RST_REQ)
 bit[31:8]   ������
 bit[7]      UC2��32K��λ����
             д1��λ��д0��Ч��
 bit[6]      UC2��TCXO��λ����
             д1��λ��д0��Ч��
 bit[5]      UC2��WCģ����245M��λ����
             д1��λ��д0��Ч��
 bit[4]      UC2��WCģ����122M��λ����
             д1��λ��д0��Ч��
 bit[3]      UC2��WCģ����122M��λ����
             д1��λ��д0��Ч��
 bit[2]      UC2��Cģ122M��λ����
             д1��λ��д0��Ч��
 bit[1]      UC2��Wģ122M��λ����
             д1��λ��д0��Ч��
 bit[0]      UC2��Wģ61M��λ����
             д1��λ��д0��Ч��
   UNION�ṹ:  BBPSCTRL_BBP_SCTRL7_SET_UNION */
#define BBPSCTRL_BBP_SCTRL7_SET_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x70)

/* �Ĵ���˵����BBPϵͳ������7����(UC2_RST_CLR)
 bit[31:8]   ������
 bit[7]      UC2��32K��λ�����
             д1�����λ��д0��Ч��
 bit[6]      UC2��TCXO��λ�����
             д1�����λ��д0��Ч��
 bit[5]      UC2��WCģ����245M��λ�����
             д1�����λ��д0��Ч��
 bit[4]      UC2��WCģ����122M��λ�����
             д1�����λ��д0��Ч��
 bit[3]      UC2��WCģ����122M��λ�����
             д1�����λ��д0��Ч��
 bit[2]      UC2��Cģ122M��λ�����
             д1�����λ��д0��Ч��
 bit[1]      UC2��Wģ122M��λ�����
             д1�����λ��д0��Ч��
 bit[0]      UC2��Wģ61M��λ�����
             д1�����λ��д0��Ч��
   UNION�ṹ:  BBPSCTRL_BBP_SCTRL7_CLR_UNION */
#define BBPSCTRL_BBP_SCTRL7_CLR_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x74)

/* �Ĵ���˵����BBPϵͳ������7״̬(UC2_RST_STATUS)
 bit[31:8]   ������
 bit[7]      UC2��32K��λ״̬��
             1����λ��
             0�������λ��
 bit[6]      UC2��TCXO��λ״̬��
             1����λ��
             0�������λ��
 bit[5]      UC2��WCģ����245M��λ״̬��
             1����λ��
             0�������λ��
 bit[4]      UC2��WCģ����122M��λ״̬��
             1����λ��
             0�������λ��
 bit[3]      UC2��WCģ����122M��λ״̬��
             1����λ��
             0�������λ��
 bit[2]      UC2��Cģ122M��λ״̬��
             1����λ��
             0�������λ��
 bit[1]      UC2��Wģ122M��λ״̬��
             1����λ��
             0�������λ��
 bit[0]      UC2��Wģ61M��λ״̬��
             1����λ��
             0�������λ��
   UNION�ṹ:  BBPSCTRL_BBP_SCTRL7_STSTUS_UNION */
#define BBPSCTRL_BBP_SCTRL7_STSTUS_ADDR               (SOC_BBP_SCTRL_BASE_ADDR + 0x78)

/* �Ĵ���˵����LTE��Դ��ʱ��ʹ��
 bit[31:24]  ������
 bit[23]     
 bit[22]     
 bit[21]     
 bit[20]     
 bit[19]     ��������ʹ�á�
 bit[18]     ��������ʹ�á�
 bit[17]     ��������ʹ�á�
 bit[16]     ��������ʹ�á�
 bit[15]     ��������ʹ�á�
 bit[14]     ��������ʹ�á�
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      ��������ʹ�á�
 bit[1]      ��������ʹ�á�
 bit[0]      ��������ʹ�á�
   UNION�ṹ:  BBPSCTRL_LTE_PD_CLK_EN_UNION */
#define BBPSCTRL_LTE_PD_CLK_EN_ADDR                   (SOC_BBP_SCTRL_BASE_ADDR + 0x80)

/* �Ĵ���˵����LTE��Դ��ʱ�ӹر�
 bit[31:24]  ������
 bit[23]     
 bit[22]     
 bit[21]     
 bit[20]     
 bit[19]     
 bit[18]     
 bit[17]     
 bit[16]     
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_LTE_PD_CLK_DIS_UNION */
#define BBPSCTRL_LTE_PD_CLK_DIS_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0x84)

/* �Ĵ���˵����LTE��Դ��ʱ���ſ�״̬
 bit[31:24]  ������
 bit[23]     
 bit[22]     
 bit[21]     
 bit[20]     
 bit[19]     
 bit[18]     
 bit[17]     
 bit[16]     
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_LTE_PD_CLK_STSTUS_UNION */
#define BBPSCTRL_LTE_PD_CLK_STSTUS_ADDR               (SOC_BBP_SCTRL_BASE_ADDR + 0x88)

/* �Ĵ���˵����LTE��Դ��λ����ʹ��
 bit[31:24]  ������
 bit[23]     
 bit[22]     
 bit[21:14]  
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_LTE_PD_SRST_REQ_UNION */
#define BBPSCTRL_LTE_PD_SRST_REQ_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x90)

/* �Ĵ���˵����LTE��Դ��λ�������
 bit[31:24]  ������
 bit[23]     
 bit[22]     
 bit[21:16]  
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_LTE_PD_SRST_DIS_UNION */
#define BBPSCTRL_LTE_PD_SRST_DIS_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x94)

/* �Ĵ���˵����LTE��Դ��λ����״̬
 bit[31:24]  ������
 bit[23]     
 bit[22]     
 bit[21:16]  
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_LTE_PD_SRST_STSTUS_UNION */
#define BBPSCTRL_LTE_PD_SRST_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x98)

/* �Ĵ���˵����WTC��Դ��ʱ��ʹ��
 bit[31:15]  ������
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_WTC_PD_CLK_EN_UNION */
#define BBPSCTRL_WTC_PD_CLK_EN_ADDR                   (SOC_BBP_SCTRL_BASE_ADDR + 0xA0)

/* �Ĵ���˵����WTC��Դ��ʱ�ӹر�
 bit[31:15]  ������
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_WTC_PD_CLK_DIS_UNION */
#define BBPSCTRL_WTC_PD_CLK_DIS_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0xA4)

/* �Ĵ���˵����WTC��Դ��ʱ���ſ�״̬
 bit[31:15]  ������
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_WTC_PD_CLK_STSTUS_UNION */
#define BBPSCTRL_WTC_PD_CLK_STSTUS_ADDR               (SOC_BBP_SCTRL_BASE_ADDR + 0xA8)

/* �Ĵ���˵����WTC��Դ��λ����ʹ��
 bit[31:16]  ������
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_WTC_PD_SRST_REQ_UNION */
#define BBPSCTRL_WTC_PD_SRST_REQ_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0xB0)

/* �Ĵ���˵����WTC��Դ��λ�������
 bit[31:16]  ������
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_WTC_PD_SRST_DIS_UNION */
#define BBPSCTRL_WTC_PD_SRST_DIS_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0xB4)

/* �Ĵ���˵����WTC��Դ��λ����״̬
 bit[31:16]  ������
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_WTC_PD_SRST_STATUS_UNION */
#define BBPSCTRL_WTC_PD_SRST_STATUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0xB8)

/* �Ĵ���˵����IRM��Դ��ʱ��ʹ��
 bit[31:11]  ������
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_IRM_PD_CLK_EN_UNION */
#define BBPSCTRL_IRM_PD_CLK_EN_ADDR                   (SOC_BBP_SCTRL_BASE_ADDR + 0xC0)

/* �Ĵ���˵����IRM��Դ��ʱ�ӹر�
 bit[31:11]  ������
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_IRM_PD_CLK_DIS_UNION */
#define BBPSCTRL_IRM_PD_CLK_DIS_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0xC4)

/* �Ĵ���˵����IRM��Դ��ʱ���ſ�״̬
 bit[31:11]  ������
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_IRM_PD_CLK_STATUS_UNION */
#define BBPSCTRL_IRM_PD_CLK_STATUS_ADDR               (SOC_BBP_SCTRL_BASE_ADDR + 0xC8)

/* �Ĵ���˵����IRM��Դ��λ����ʹ��
 bit[31:11]  ������
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_IRM_PD_SRST_REQ_UNION */
#define BBPSCTRL_IRM_PD_SRST_REQ_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0xD0)

/* �Ĵ���˵����IRM��Դ��λ�������
 bit[31:11]  ������
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_IRM_PD_SRST_DIS_UNION */
#define BBPSCTRL_IRM_PD_SRST_DIS_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0xD4)

/* �Ĵ���˵����IRM��Դ��λ����״̬
 bit[31:11]  ������
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_IRM_PD_SRST_STATUS_UNION */
#define BBPSCTRL_IRM_PD_SRST_STATUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0xD8)

/* �Ĵ���˵����COMʱ��ʹ��
 bit[31:27]  ������
 bit[26]     BBP_COMM_FE�У�Cģʽʱ��ʹ��
 bit[25]     BBP_COMM_FE�У�Tģʽʱ��ʹ��
 bit[24]     BBP_COMM_FE�У�Wģʽʱ��ʹ�ܡ�
 bit[23]     GUC DBGʱ��ʹ�ܡ�
 bit[22]     BBP_COMM_FE��mipiʱ��ʹ�ܡ���ʱ������19.2M����245.76M��ѡ���źż�bbp_clk_ctrl��
 bit[21]     ����ET��Wʱ��ʹ��
 bit[20]     ����ET��Lʱ��ʹ��
 bit[19]     ����ET����ʱ��ʹ��
 bit[18]     C2ģʽtxʱ��ʹ�ܡ����ź���Ҫͬʱ��C_SYS_CLK_EN��
 bit[17]     Tģʽtxʱ��ʹ�ܡ����ź���Ҫͬʱ��T_SYS_CLK_EN��
 bit[16]     Wģʽtxʱ��ʹ�ܡ����ź���Ҫͬʱ��W_SYS_CLK_EN��
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     ��λû��ʱ��ʹ�ܡ�
 bit[11]     ��λû��ʱ��ʹ�ܡ�
 bit[10]     
 bit[9]      
 bit[8]      ��λû��ʱ��ʹ�ܡ�
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      l sdrģ��ʱ�Ӵ򿪡�
             ע�⣬��tl_dbg_clk_en��ʱ��ͬ�����l sdrģ���ʱ�ӡ�
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_COM_CLK_EN_UNION */
#define BBPSCTRL_COM_CLK_EN_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0xE0)

/* �Ĵ���˵����COMʱ�ӹر�
 bit[31:27]  ������
 bit[26]     BBP_COMM_FE�У�Cģʽʱ�ӹر�
 bit[25]     BBP_COMM_FE�У�Tģʽʱ�ӹر�
 bit[24]     BBP_COMM_FE�У�Wģʽʱ�ӹر�
 bit[23]     GUC DBGʱ�ӹر�
 bit[22]     BBP_COMM_FE��mipiʱ�ӹر�
 bit[21]     ����ET��Wʱ�ӹر�
 bit[20]     ����ET��Lʱ�ӹر�
 bit[19]     ����ET����ʱ�ӹر�
 bit[18]     
 bit[17]     
 bit[16]     
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     ��λû��ʱ��ʹ�ܡ�
 bit[11]     ��λû��ʱ��ʹ�ܡ�
 bit[10]     
 bit[9]      
 bit[8]      ��λû��ʱ��ʹ�ܡ�
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_COM_CLK_DIS_UNION */
#define BBPSCTRL_COM_CLK_DIS_ADDR                     (SOC_BBP_SCTRL_BASE_ADDR + 0xE4)

/* �Ĵ���˵����COMʱ���ſ�״̬
 bit[31:27]  ������
 bit[26]     BBP_COMM_FE�У�Cģʽʱ��״̬
 bit[25]     BBP_COMM_FE�У�Tģʽʱ��״̬
 bit[24]     BBP_COMM_FE�У�Wģʽʱ��״̬
 bit[23]     GUC DBGʱ��״̬
 bit[22]     BBP_COMM_FE��mipiʱ��״̬
 bit[21]     ����ET��Wʱ��״̬
 bit[20]     ����ET��Lʱ��״̬
 bit[19]     ����ET����ʱ��״̬
 bit[18]     
 bit[17]     
 bit[16]     
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     ����ϵ�ʱ��״̬��0xE0/0xE4��Ӧbitλ����ʱ��ʹ��
 bit[11]     ����ϵ�ʱ��״̬��0xE0/0xE4��Ӧbitλ����ʱ��ʹ��
 bit[10]     
 bit[9]      
 bit[8]      ����ϵ�ʱ��״̬��0xE0/0xE4��Ӧbitλ����ʱ��ʹ��
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_COM_CLK_STATUS_UNION */
#define BBPSCTRL_COM_CLK_STATUS_ADDR                  (SOC_BBP_SCTRL_BASE_ADDR + 0xE8)

/* �Ĵ���˵����COM��λ����ʹ��
 bit[31:27]  ������
 bit[26]     BBP_COMM_FE�У�Cģʽ��λ����
 bit[25]     BBP_COMM_FE�У�Tģʽ��λ����
 bit[24]     BBP_COMM_FE�У�Wģʽ��λ����
 bit[23]     GUC DBG��λ����
 bit[22]     BBP_COMM_FE��mipiʱ����λ������Ч��
 bit[21:20]  ����
 bit[19]     ����ET���߸�λ
 bit[18:16]  
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_COM_SRST_REQ_UNION */
#define BBPSCTRL_COM_SRST_REQ_ADDR                    (SOC_BBP_SCTRL_BASE_ADDR + 0xF0)

/* �Ĵ���˵����COM��λ�������
 bit[31:27]  ������
 bit[26]     BBP_COMM_FE�У�Cģʽ��λ���
 bit[25]     BBP_COMM_FE�У�Tģʽ��λ���
 bit[24]     BBP_COMM_FE�У�Wģʽ��λ���
 bit[23]     GUC DBG��λ���
 bit[22]     BBP_COMM_FE��mipiʱ����⸴λ��д1���㡣
 bit[21:20]  ����
 bit[19]     ����ET���߸�λ�ر�
 bit[18:16]  
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_COM_SRST_DIS_UNION */
#define BBPSCTRL_COM_SRST_DIS_ADDR                    (SOC_BBP_SCTRL_BASE_ADDR + 0xF4)

/* �Ĵ���˵����COM��λ����״̬
 bit[31:27]  ������
 bit[26]     BBP_COMM_FE�У�Cģʽ��λ״̬
 bit[25]     BBP_COMM_FE�У�Tģʽ��λ״̬
 bit[24]     BBP_COMM_FE�У�Wģʽ��λ״̬
 bit[23]     GUC DBG��λ״̬
 bit[22]     BBP_COMM_FE��mipiʱ����λ״̬���߸�λ���ͽ⸴λ��
 bit[21:20]  ����
 bit[19]     ����ET���߸�λ״̬
 bit[18:16]  ����
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_COM_SRST_STATUS_UNION */
#define BBPSCTRL_COM_SRST_STATUS_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0xF8)

/* �Ĵ���˵����BBP��Դ����ʹ��(DSP��)
 bit[31:3]   ������
 bit[2]      IRM��Դ���ϵ���λ��
             д1��λ��д0��Ч��
 bit[1]      WTC��Դ���ϵ���λ��
             д1��λ��д0��Ч��
 bit[0]      LTE��Դ���ϵ���λ��
             д1��λ��д0��Ч��
   UNION�ṹ:  BBPSCTRL_BBP_MTCMOS_SET_DSP_UNION */
#define BBPSCTRL_BBP_MTCMOS_SET_DSP_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x100)

/* �Ĵ���˵����BBP��Դ���ƹر�(DSP��)
 bit[31:3]   ������
 bit[2]      IRM��Դ���ϵ������
             д1���㣬д0��Ч��
 bit[1]      WTC��Դ���ϵ������
             д1���㣬д0��Ч��
 bit[0]      LTE��Դ���ϵ������
             д1���㣬д0��Ч��
   UNION�ṹ:  BBPSCTRL_BBP_MTCMOS_CLR_DSP_UNION */
#define BBPSCTRL_BBP_MTCMOS_CLR_DSP_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x104)

/* �Ĵ���˵����BBP��Դ����״̬(DSP��)
 bit[31:3]   ������
 bit[2]      IRM��Դ���Դ״̬��
             1���ϵ�
             0���µ�
 bit[1]      WTC��Դ���Դ״̬��
             1���ϵ�
             0���µ�
 bit[0]      LTE��Դ���Դ״̬��
             1���ϵ�
             0���µ�
   UNION�ṹ:  BBPSCTRL_BBP_MTCMOS_STATUS_DSP_UNION */
#define BBPSCTRL_BBP_MTCMOS_STATUS_DSP_ADDR           (SOC_BBP_SCTRL_BASE_ADDR + 0x108)

/* �Ĵ���˵����BBP��Դ�������ʹ��(DSP��)
 bit[31:3]   ������
 bit[2]      IRM��Դ�������λ��
             д1��λ��д0��Ч��
 bit[1]      WTC��Դ�������λ��
             д1��λ��д0��Ч��
 bit[0]      LTE��Դ�������λ��
             д1��λ��д0��Ч��
   UNION�ṹ:  BBPSCTRL_BBP_ISO_EN_SET_DSP_UNION */
#define BBPSCTRL_BBP_ISO_EN_SET_DSP_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x110)

/* �Ĵ���˵����BBP��Դ������ƹر�(DSP��)
 bit[31:3]   ������
 bit[2]      IRM��Դ����������
             д1���㣬д0��Ч��
 bit[1]      WTC��Դ����������
             д1���㣬д0��Ч��
 bit[0]      LTE��Դ����������
             д1���㣬д0��Ч��
   UNION�ṹ:  BBPSCTRL_BBP_ISO_EN_CLR_DSP_UNION */
#define BBPSCTRL_BBP_ISO_EN_CLR_DSP_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x114)

/* �Ĵ���˵����BBP��Դ�������״̬(DSP��)
 bit[31:3]   ������
 bit[2]      IRM��Դ�����״̬��
             1�����룻
             0��������룻
 bit[1]      WTC��Դ�����״̬��
             1�����룻
             0��������룻
 bit[0]      LTE��Դ�����״̬��
             1�����룻
             0��������룻
   UNION�ṹ:  BBPSCTRL_BBP_ISO_EN_STATUS_DSP_UNION */
#define BBPSCTRL_BBP_ISO_EN_STATUS_DSP_ADDR           (SOC_BBP_SCTRL_BASE_ADDR + 0x118)

/* �Ĵ���˵����BBP��Դ��ʱ��ʹ��(DSP��)
 bit[31:3]   ������
 bit[2]      IRM��Դ��ʱ��ʹ�ܡ�
             д1��λ��д0��Ч��
 bit[1]      WTC��Դ��ʱ��ʹ�ܡ�
             д1��λ��д0��Ч��
 bit[0]      LTE��Դ��ʱ��ʹ�ܡ�
             д1��λ��д0��Ч��
   UNION�ṹ:  BBPSCTRL_BBP_PD_CLK_SET_DSP_UNION */
#define BBPSCTRL_BBP_PD_CLK_SET_DSP_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x120)

/* �Ĵ���˵����BBP��Դ��ʱ�ӹر�(DSP��)
 bit[31:3]   ������
 bit[2]      IRM��Դ��ʱ�ӹرա�
             д1�رգ�д0��Ч��
 bit[1]      WTC��Դ��ʱ�ӹرա�
             д1�رգ�д0��Ч��
 bit[0]      LTE��Դ��ʱ�ӹرա�
             д1�رգ�д0��Ч��
   UNION�ṹ:  BBPSCTRL_BBP_PD_CLK_CLR_DSP_UNION */
#define BBPSCTRL_BBP_PD_CLK_CLR_DSP_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x124)

/* �Ĵ���˵����BBP��Դ��ʱ���ſ�״̬(DSP��)
 bit[31:3]   ������
 bit[2]      IRM��Դ��ʱ��״̬��
             1��ʱ��ʹ��
             0��ʱ�ӹر�
 bit[1]      WTC��Դ��ʱ��״̬��
             1��ʱ��ʹ��
             0��ʱ�ӹر�
 bit[0]      LTE��Դ��ʱ��״̬��
             1��ʱ��ʹ��
             0��ʱ�ӹر�
   UNION�ṹ:  BBPSCTRL_BBP_PD_CLK_STATUS_DSP_UNION */
#define BBPSCTRL_BBP_PD_CLK_STATUS_DSP_ADDR           (SOC_BBP_SCTRL_BASE_ADDR + 0x128)

/* �Ĵ���˵����BBP��Դ��λ����ʹ��(DSP��)
 bit[31:3]   ������
 bit[2]      IRM��Դ��λ����
             д1��λ��д0��Ч��
 bit[1]      WTC��Դ��λ����
             д1��λ��д0��Ч��
 bit[0]      LTE��Դ��λ����
             д1��λ��д0��Ч��
   UNION�ṹ:  BBPSCTRL_BBP_PD_SRST_SET_DSP_UNION */
#define BBPSCTRL_BBP_PD_SRST_SET_DSP_ADDR             (SOC_BBP_SCTRL_BASE_ADDR + 0x130)

/* �Ĵ���˵����BBP��Դ��λ����ر�(DSP��)
 bit[31:3]   ������
 bit[2]      IRM��Դ��λ�����
             д1�����λ��д0��Ч��
 bit[1]      WTC��Դ��λ�����
             д1�����λ��д0��Ч��
 bit[0]      LTE��Դ��λ�����
             д1�����λ��д0��Ч��
   UNION�ṹ:  BBPSCTRL_BBP_PD_SRST_CLR_DSP_UNION */
#define BBPSCTRL_BBP_PD_SRST_CLR_DSP_ADDR             (SOC_BBP_SCTRL_BASE_ADDR + 0x134)

/* �Ĵ���˵����BBP��Դ��λ����״̬(DSP��)
 bit[31:3]   ������
 bit[2]      IRM��Դ��λ״̬��
             1����λ��
             0�������λ��
 bit[1]      WTC��Դ��λ״̬��
             1����λ��
             0�������λ��
 bit[0]      LTE��Դ��λ״̬��
             1����λ��
             0�������λ��
   UNION�ṹ:  BBPSCTRL_BBP_PD_SRST_STATUS_DSP_UNION */
#define BBPSCTRL_BBP_PD_SRST_STATUS_DSP_ADDR          (SOC_BBP_SCTRL_BASE_ADDR + 0x138)

/* �Ĵ���˵����BBPϵͳ������14��λ
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL14_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x140)

/* �Ĵ���˵����BBPϵͳ������14����
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL14_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x144)

/* �Ĵ���˵����BBPϵͳ������14״̬
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL14_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x148)

/* �Ĵ���˵����BBPϵͳ������15��λ
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL15_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x150)

/* �Ĵ���˵����BBPϵͳ������15����
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL15_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x154)

/* �Ĵ���˵����BBPϵͳ������15״̬
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL15_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x158)

/* �Ĵ���˵����BBPϵͳ������16��λ
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL16_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x160)

/* �Ĵ���˵����BBPϵͳ������16����
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL16_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x164)

/* �Ĵ���˵����BBPϵͳ������16״̬
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL16_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x168)

/* �Ĵ���˵����BBPϵͳ������17��λ
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL17_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x170)

/* �Ĵ���˵����BBPϵͳ������17����
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL17_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x174)

/* �Ĵ���˵����BBPϵͳ������17״̬
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL17_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x178)

/* �Ĵ���˵����BBPϵͳ������18��λ
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL18_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x180)

/* �Ĵ���˵����BBPϵͳ������18����
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL18_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x184)

/* �Ĵ���˵����BBPϵͳ������18״̬
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL18_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x188)

/* �Ĵ���˵����BBPϵͳ������19��λ
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL19_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x190)

/* �Ĵ���˵����BBPϵͳ������19����
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL19_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x194)

/* �Ĵ���˵����BBPϵͳ������19״̬
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL19_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x198)

/* �Ĵ���˵����BBPϵͳ������1A��λ��UC2 CLK FORCE ENA��
   ��      ����������Debugʹ�á�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL1a_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1A0)

/* �Ĵ���˵����BBPϵͳ������1A����
   ��      ����������Debugʹ�á�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL1a_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1A4)

/* �Ĵ���˵����BBPϵͳ������1A״̬
   ��      ����������Debugʹ�á�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL1a_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x1A8)

/* �Ĵ���˵����BBPϵͳ������1B��λ(LTE PD CLK FORCE ENA)
   ��      ����������Debugʹ�á�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL1b_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1B0)

/* �Ĵ���˵����BBPϵͳ������1B����
   ��      ����������Debugʹ�á�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL1b_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1B4)

/* �Ĵ���˵����BBPϵͳ������1B״̬
   ��      ����������Debugʹ�á�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL1b_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x1B8)

/* �Ĵ���˵����BBPϵͳ������1C��λ(WTC PD CLK FORCE ENA)
   ��      ����������Debugʹ�á�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL1c_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1C0)

/* �Ĵ���˵����BBPϵͳ������1C����
   ��      ����������Debugʹ�á�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL1c_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1C4)

/* �Ĵ���˵����BBPϵͳ������1C״̬
   ��      ����������Debugʹ�á�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL1c_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x1C8)

/* �Ĵ���˵����BBPϵͳ������1D��λ(IRM PD CLK FORCE ENA)
   ��      ����������Debugʹ�á�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL1d_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1D0)

/* �Ĵ���˵����BBPϵͳ������1D����
   ��      ����������Debugʹ�á�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL1d_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1D4)

/* �Ĵ���˵����BBPϵͳ������1D״̬
   ��      ����������Debugʹ�á�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL1d_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x1D8)

/* �Ĵ���˵����BBPϵͳ������1E��λ(COM CLK FORCE ENA)
   ��      ����������Debugʹ�á�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL1e_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1E0)

/* �Ĵ���˵����BBPϵͳ������1E����
   ��      ����������Debugʹ�á�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL1e_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1E4)

/* �Ĵ���˵����BBPϵͳ������1E״̬
   ��      ����������Debugʹ�á�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL1e_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x1E8)

/* �Ĵ���˵����BBPϵͳ������1F��λ(PD PWR AND PD CLK FORCE ENA)
 bit[31:15]  ������Debugʹ�á�
 bit[14]     д1��ǿ�ƽ⸴λ��
 bit[13]     д1��ǿ�ƽ⸴λ��
 bit[12]     д1��ǿ�ƽ⸴λ��
 bit[11]     
 bit[10]     д1��ǿ�ƿ��ӡ�
 bit[9]      д1��ǿ�ƿ��ӡ�
 bit[8]      д1��ǿ�ƿ��ӡ�
 bit[7]      
 bit[6]      д1��ǿ�ƽ���롣
 bit[5]      д1��ǿ�ƽ���롣
 bit[4]      д1��ǿ�ƽ���롣
 bit[3]      
 bit[2]      д1��ǿ���ϵ硣
 bit[1]      д1��ǿ���ϵ硣
 bit[0]      д1��ǿ���ϵ硣
   UNION�ṹ:  BBPSCTRL_BBP_SCTRL1f_SET_UNION */
#define BBPSCTRL_BBP_SCTRL1f_SET_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1F0)

/* �Ĵ���˵����BBPϵͳ������1F���㣨���force)
   ��      ����������Debugʹ�á�Bit������0x1F0��Ӧ
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL1f_CLR_ADDR                 (SOC_BBP_SCTRL_BASE_ADDR + 0x1F4)

/* �Ĵ���˵����BBPϵͳ������1F״̬(force״̬)
   ��      ����������Debugʹ�á�Bit������0x1F0��Ӧ
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTRL1f_STSTUS_ADDR              (SOC_BBP_SCTRL_BASE_ADDR + 0x1F8)

/* �Ĵ���˵����LBUS����������
 bit[31:27]  ������
 bit[26:25]  
 bit[24]     
 bit[23]     
 bit[22:21]  
 bit[20]     
 bit[19]     
 bit[18:17]  
 bit[16]     
 bit[15]     
 bit[14:13]  
 bit[12]     
 bit[11]     
 bit[10:9]   
 bit[8]      
 bit[7]      
 bit[6:5]    
 bit[4]      
 bit[3]      
 bit[2:1]    
 bit[0]      
   UNION�ṹ:  BBPSCTRL_BBP_SCTR20_UNION */
#define BBPSCTRL_BBP_SCTR20_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x200)

/* �Ĵ���˵����BBPϵͳ������21(dw_axi_bbp ����)
 bit[31:14]  ������
 bit[13]     
 bit[12:11]  
 bit[10:9]   
 bit[8:7]    
 bit[6:5]    
 bit[4:3]    
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_BBP_SCTR21_UNION */
#define BBPSCTRL_BBP_SCTR21_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x204)

/* �Ĵ���˵����BBPϵͳ������22(dw_axi_bbp dlock)
 bit[31:1]   ������
 bit[0]      �Ĵ���23��Ӧ��dlock����update
   UNION�ṹ:  BBPSCTRL_BBP_SCTR22_UNION */
#define BBPSCTRL_BBP_SCTR22_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x208)

/* �Ĵ���˵����BBPϵͳ������23(dw_axi_bbp_dlock)
 bit[31:16]  ����ʹ�á�
 bit[15:8]   ����
 bit[7:0]    ����ʹ�á�
   UNION�ṹ:  BBPSCTRL_BBP_SCTR23_UNION */
#define BBPSCTRL_BBP_SCTR23_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x20C)

/* �Ĵ���˵����BBPϵͳ������24(LBUS���߷������ж�����)
 bit[31]     ������
 bit[30]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[29]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[28]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[27]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[26]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[25]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[24]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[23]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[22]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[21]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[20]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[19]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[18]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[17]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[16]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[15]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[14]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[13]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[12]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[11]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[10]     0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[9]      0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[8]      0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[7]      0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[6]      0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[5]      0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[4]      0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[3]      0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[2]      0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[1]      0���ж�������Ч��
             1���ж�����ʹ�ܡ�
 bit[0]      0���ж�������Ч��
             1���ж�����ʹ�ܡ�
   UNION�ṹ:  BBPSCTRL_BBP_SCTR24_UNION */
#define BBPSCTRL_BBP_SCTR24_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x210)

/* �Ĵ���˵����BBPϵͳ������25(reserved)
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTR25_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x214)

/* �Ĵ���˵����BBPϵͳ������26(reserved)
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTR26_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x218)

/* �Ĵ���˵����BBPϵͳ������27(reserved)
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTR27_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x21C)

/* �Ĵ���˵����BBPϵͳ������28(reserved)
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTR28_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x220)

/* �Ĵ���˵����BBPϵͳ������29(COM2LTE_TBD)
   ��      ����COM��LTE��Ԥ��ECO�ӿ��źš�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTR29_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x224)

/* �Ĵ���˵����BBPϵͳ������2A(BBPʱ��ѡ��)
 bit[31:22]  ������
 bit[21]     0: ѡ��AP��ĵ͹��Ŀ����ź�(Ĭ�ϣ��µ硢��λ���Ϊ��ֵ)��
             1��ѡ��BBP��ĵ͹��Ŀ����źš�
             Modemʹ��IRM��ʱ����Ҫ����Ϊ1. ��
 bit[20]     tdl����ʱ��Ƶ��120/240MHz����240/480MHzѡ���ź�,��bitΪ��
             0��ʹ�ñ��Ĵ�����ַbit��11:10�����������ֵ��ѡ�񡣣��ϵ縴λĬ�ϴ˷�ʽ��
             1��tdl�߼��˿�ѡ���źš�
 bit[19]     bbp tdl clkʹ�ܡ���ʱ�����ڵ�Դ��ΪIRM/LTE��Դ��
 bit[18:14]  UART�ķ�Ƶ������
 bit[13:12]  ����
 bit[11]     ��ֵ����ʱ��Ƶ�ʳ����£�ch1 tdl clk��Ƶ������
             1��ch1��ʱ��480/240MHz(Ĭ��);
             0��ch1��ʱ��240/120MHz
             ע���ò����ڱ��Ĵ���bit20Ϊ0ʱ��Ч��
 bit[10]     ��ֵ����ʱ��Ƶ�ʳ����£�ch0 tdl clk��Ƶ������
             1��ch0��ʱ��480/240MHz(Ĭ��);
             0��ch0��ʱ��240/120MHz
             ע���ò����ڱ��Ĵ���bit20Ϊ0ʱ��Ч��
 bit[9:8]    LTE tx1 clkѡ��
             00��ѡ��245M(1��Ƶ)
             01��ѡ��122M(2��Ƶ��
             10��ѡ��61.44M(4��Ƶ)
             11��ѡ��30.72M(8��Ƶ)
 bit[7:6]    LTE tx0 clkѡ��
             00��ѡ��245M(1��Ƶ)
             01��ѡ��122M(2��Ƶ��
             10��ѡ��61.44M(4��Ƶ)
             11��ѡ��30.72M(8��Ƶ)
 bit[5]      pdt clkѡ��
             0��ѡ��122M��
             1��ѡ��245M��
 bit[4]      bbp clkѡ��
             0��ѡ��122M;
             1��ѡ��245M��
 bit[3]      scpll_uc2_clkѡ���źţ�
             0����ʾѡ��bbppll_clk_sc0
             1����ʾѡ��bbppll_clk_sc1
 bit[2]      scpll_clkѡ���źţ�
             0����ʾѡ��bbppll_clk_sc0
             1����ʾѡ��bbppll_clk_sc1
 bit[1]      mipiʱ����Դ��
             0��ѡ�� 19.2MHz ��עBBP�˿�����ʱ�ӣ�
             1��ѡ�� 40.96MHz��עBBP�ڲ�245MHz��Ƶʱ�ӣ�
 bit[0]      uartʱ��ѡ��
             1��ѡ��480MHz��Ƶ��
             0��ѡ��245MHz��Ƶ��
   UNION�ṹ:  BBPSCTRL_BBP_SCTR2A_UNION */
#define BBPSCTRL_BBP_SCTR2A_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x228)

/* �Ĵ���˵����BBPϵͳ������2B(REV)
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTR2B_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x22C)

/* �Ĵ���˵����BBPϵͳ������2C(REV)
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_SCTR2C_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x230)

/* �Ĵ���˵����BBPϵͳ������2D(REV)
 bit[31:4]   ������
 bit[3]      MST ERR״̬�ж�д��ַ��Ϣѡ��
             0��ѡ�����ַ��
             1��ѡ��д��ַ��
 bit[2]      MST ERR״̬�ж�д��ַ��Ϣѡ��
             0��ѡ�����ַ��
             1��ѡ��д��ַ��
 bit[1]      MST ERR״̬�ж�д��ַ��Ϣѡ��
             0��ѡ�����ַ��
             1��ѡ��д��ַ��
 bit[0]      MST ERR״̬�ж�д��ַ��Ϣѡ��
             0��ѡ�����ַ��
             1��ѡ��д��ַ��
   UNION�ṹ:  BBPSCTRL_BBP_SCTR2D_UNION */
#define BBPSCTRL_BBP_SCTR2D_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x234)

/* �Ĵ���˵����BBPϵͳ������2E��gģ����ͬ�����ԣ�
 bit[31:1]   ������
 bit[0]      G_LBUSѡ�񡣱�����debugʹ�á�
             0����Arbiter�������
             1����Arbiterǰ�����
   UNION�ṹ:  BBPSCTRL_BBP_SCTR2E_UNION */
#define BBPSCTRL_BBP_SCTR2E_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x238)

/* �Ĵ���˵����BBPϵͳ������2F(ģʽѡ��)
 bit[31:10]  ����
 bit[9]      W ETѡ��оƬ�汾��֧������ET�����Ը�ֵ����Ҫ�޸ģ�
             0��������ET��
             1������ET��
 bit[8]      L ETѡ��оƬ�汾��֧������ET�����Ը�ֵ����Ҫ�޸ģ���
             0��������ET��
             1������ET��
 bit[7]      ����
 bit[6:4]    UC2ģʽѡ��one-hot���롣
             001��WCDMAģʽ��
             010��������
             100��CDMAģʽ��
             default��CDMAģʽ��
             ����ֵ����Ч���澯��
 bit[3]      ����
 bit[2:0]    WTCģʽѡ��one-hot���롣
             001��WCDMAģʽ��
             010��TDS-CDMAģʽ��
             100��CDMAģʽ��
             default��TDS_CDMAģʽ��
             ����ֵ����Ч���澯��
   UNION�ṹ:  BBPSCTRL_BBP_SCTR2F_UNION */
#define BBPSCTRL_BBP_SCTR2F_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x23C)

/* �Ĵ���˵����BBP��Դ��״̬�Ĵ�����mtcmos rdy)
 bit[31:3]   ������
 bit[2]      IRM��Դ���ϵ�״̬��
             1���ϵ磻
             0���µ�
 bit[1]      WTC��Դ���ϵ�״̬��
             1���ϵ磻
             0���µ�
 bit[0]      LTE��Դ���ϵ�״̬��
             1���ϵ磻
             0���µ�
   UNION�ṹ:  BBPSCTRL_BBP_STAT00_UNION */
#define BBPSCTRL_BBP_STAT00_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x300)

/* �Ĵ���˵����irm��Դ��ʱ��״̬(�ſغ�,��0x00C0 IRM PD�ſ�ʹ���źŶ�Ӧ)
   ��      ���������������ù۲�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT01_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x304)

/* �Ĵ���˵����lte��Դ��ʱ��״̬(�ſغ�,��0x0080 LTE PD�ſ�ʹ���źŶ�Ӧ)
   ��      ���������� �����ù۲�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT02_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x308)

/* �Ĵ���˵����com��ʱ��״̬(�ſغ�,��COM PD  0x00E0 �ſ�ʹ���źŶ�Ӧ)
   ��      ���������������ù۲�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT03_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x30C)

/* �Ĵ���˵����BBP��Ƶ��ʱ��״̬(LTE/WTC/IRM����0x0040��ַ��clk_en��Ӧ���ſغ�)
   ��      ���������� �����ù۲�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT04_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x310)

/* �Ĵ���˵����BBP��Ƶ��ʱ��״̬(COM����0x0050��ַ��clk_en��Ӧ���ſغ�)
   ��      ���������������ù۲�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT05_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x314)

/* �Ĵ���˵����BBP MST״̬�Ĵ���
 bit[31:8]   ������
 bit[7:0]    bbp��dw_axi_mst��error�ź�
   UNION�ṹ:  BBPSCTRL_BBP_STAT06_UNION */
#define BBPSCTRL_BBP_STAT06_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x318)

/* �Ĵ���˵����BBP MST M1��д�����ַ�Ĵ���
   ��      ����Debugʹ�á�
               ��Ҫ����0x234��ַ��bit0ѡ�������д��ַ��
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT07_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x31C)

/* �Ĵ���˵����BBP MST M2��д�����ַ�Ĵ���
   ��      ����Debugʹ�á�
               ��Ҫ����0x234��ַ��bit1ѡ�������д��ַ��
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT08_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x320)

/* �Ĵ���˵����BBP MST M3��д�����ַ�Ĵ���
   ��      ����Debugʹ�á�
               ��Ҫ����0x234��ַ��bit2ѡ�������д��ַ��
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT09_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x324)

/* �Ĵ���˵����BBP MST M4��д�����ַ�Ĵ���
   ��      ����Debugʹ�á�
               ��Ҫ����0x234��ַ��bit3ѡ�������д��ַ��
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT0A_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x328)

/* �Ĵ���˵����BBP MST DLOCK״̬�Ĵ���
 bit[31:12]  ������
 bit[11]     DLOCK IRQ��
 bit[10]     DLOCK�Ķ�д������
 bit[9:4]    DLOCK ID��
 bit[3:2]    DLOCK SLV��š�
 bit[1:0]    DLOCK MST��š�
   UNION�ṹ:  BBPSCTRL_BBP_STAT0B_UNION */
#define BBPSCTRL_BBP_STAT0B_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x32C)

/* �Ĵ���˵����BBP MST DLOCK��ַ�Ĵ���
   ��      ����������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT0C_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x330)

/* �Ĵ���˵����BBP״̬�Ĵ���0D(IRM2COM_TBD)
 bit[31:16]  ������
 bit[15:0]   IRM��COM��Ԥ��eco�źš�
   UNION�ṹ:  BBPSCTRL_BBP_STAT0D_UNION */
#define BBPSCTRL_BBP_STAT0D_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x334)

/* �Ĵ���˵����BBP״̬�Ĵ���0E(LTE2COM_TBD)
   ��      ����LTE��COM��Ԥ��ECO�źš�
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT0E_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x338)

/* �Ĵ���˵����BBP״̬�Ĵ���0F(LBUS�������ж�״̬)
 bit[31]     0������
             1����ʱ
             ���������ᴥ���жϡ�
             �������ᴥ���жϡ�
             д�üĴ������Ӧbite���㡣
 bit[30]     0��������
             1����ʱ��
 bit[29]     0��������
             1����ʱ��
 bit[28]     0��������
             1����ʱ��
 bit[27]     0��������
             1����ʱ��
 bit[26]     0��������
             1����λ��
 bit[25]     0��������
             1��ʱ�ӹرա�
 bit[24]     0��������
             1����Դ�رա�
 bit[23]     0��������
             1����ʱ��
 bit[22]     0��������
             1����ʱ��
 bit[21]     0��������
             1����λ��
 bit[20]     0��������
             1��ʱ�ӹرա�
 bit[19]     0��������
             1����ʱ��
 bit[18]     0��������
             1����λ��
 bit[17]     0��������
             1��ʱ�ӹرա�
 bit[16]     0��������
             1����Դ�رա�
 bit[15]     0��������
             1����ʱ��
 bit[14]     0��������
             1����λ��
 bit[13]     0��������
             1��ʱ�ӹرա�
 bit[12]     0��������
             1����Դ�رա�
 bit[11]     0��������
             1����ʱ��
 bit[10]     0��������
             1����λ��
 bit[9]      0��������
             1��ʱ�ӹرա�
 bit[8]      0��������
             1����Դ�رա�
 bit[7]      0��������
             1����ʱ��
 bit[6]      0��������
             1����λ��
 bit[5]      0��������
             1��ʱ�ӹرա�
 bit[4]      0��������
             1����Դ�رա�
 bit[3]      0��������
             1����ʱ��
 bit[2]      0��������
             1����λ��
 bit[1]      0��������
             1��ʱ�ӹرա�
 bit[0]      0��������
             1����Դ�رա�
   UNION�ṹ:  BBPSCTRL_BBP_STAT0F_UNION */
#define BBPSCTRL_BBP_STAT0F_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x33C)

/* �Ĵ���˵����BBP״̬�Ĵ���10(COM��ʱ��״̬����clk_en�Գ�)
 bit[31:21]  ������
             ��Щ����COM_TOP�е�ʱ��״̬��
 bit[20]     0����ʱ��
             1����ʱ��
             WTC 122 LBUSʱ��״̬
 bit[19]     0����ʱ��
             1����ʱ��
 bit[18]     0����ʱ��
             1����ʱ��
 bit[17]     0����ʱ��
             1����ʱ��
             TDS 245 LBUSʱ��״̬
 bit[16]     0����ʱ��
             1����ʱ��
             û��ʹ�á�
 bit[15]     0����ʱ��
             1����ʱ��
 bit[14]     0����ʱ��
             1����ʱ��
             LTE ULHB LBUSʱ��״̬
 bit[13]     0����ʱ��
             1����ʱ��
             LTE PDT LBUSʱ��״̬��
 bit[12]     0����ʱ��
             1����ʱ��
             LTE PDF LBUSʱ��״̬��
 bit[11]     0����ʱ��
             1����ʱ��
 bit[10]     0����ʱ��
             1����ʱ��
 bit[9]      0����ʱ��
             1����ʱ��
             Gģ������G1��GSDR�Ĺ����߼���104Mʱ��״̬��
 bit[8]      0����ʱ��
             1����ʱ��
             Gģ��������LBUSʱ��״̬��
 bit[7]      0����ʱ��
             1����ʱ��
             Gģ������19.2Mʱ�ӵ�״̬
 bit[6]      0����ʱ��
             1����ʱ��
             Gģ������32Kʱ�ӵ�״̬��
 bit[5]      0����ʱ��
             1����ʱ��
 bit[4]      0����ʱ��
             1����ʱ��
 bit[3]      ����
 bit[2]      ����
 bit[1]      ����
 bit[0]      ����
   UNION�ṹ:  BBPSCTRL_BBP_STAT10_UNION */
#define BBPSCTRL_BBP_STAT10_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x340)

/* �Ĵ���˵����BBP״̬�Ĵ���11
   ��      ��������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT11_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x344)

/* �Ĵ���˵����BBP״̬�Ĵ���12
   ��      ��������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT12_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x348)

/* �Ĵ���˵����BBP״̬�Ĵ���13
   ��      ��������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT13_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x34C)

/* �Ĵ���˵����BBP״̬�Ĵ���14
   ��      ��������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT14_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x350)

/* �Ĵ���˵����BBP״̬�Ĵ���15
   ��      ��������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT15_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x354)

/* �Ĵ���˵����BBP״̬�Ĵ���16
   ��      ��������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT16_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x358)

/* �Ĵ���˵����BBP״̬�Ĵ���17
   ��      ��������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT17_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x35C)

/* �Ĵ���˵����BBP״̬�Ĵ���18
   ��      ��������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT18_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x360)

/* �Ĵ���˵����BBP״̬�Ĵ���19
   ��      ��������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT19_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x364)

/* �Ĵ���˵����BBP״̬�Ĵ���1A
   ��      ��������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT1A_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x368)

/* �Ĵ���˵����BBP״̬�Ĵ���1B
   ��      ��������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT1B_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x36C)

/* �Ĵ���˵����BBP״̬�Ĵ���1C
   ��      ��������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT1C_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x370)

/* �Ĵ���˵����BBP״̬�Ĵ���1D
   ��      ��������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT1D_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x374)

/* �Ĵ���˵����BBP״̬�Ĵ���1E
   ��      ��������
   UNION�ṹ ���� */
#define BBPSCTRL_BBP_STAT1E_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x378)

/* �Ĵ���˵��������Դ�����ʱ�ӵ�ʱ��״̬��ÿ��PDһ��ʱ��ʹ�ܣ�������ÿ��PD�����ʱ��ȫ���򿪡�
 bit[31:17]  ����
 bit[16]     
 bit[15]     
 bit[14]     
 bit[13]     
 bit[12]     
 bit[11]     
 bit[10]     
 bit[9]      
 bit[8]      
 bit[7]      
 bit[6]      
 bit[5]      
 bit[4]      
 bit[3]      
 bit[2]      
 bit[1]      
 bit[0]      
   UNION�ṹ:  BBPSCTRL_BBP_STAT1F_UNION */
#define BBPSCTRL_BBP_STAT1F_ADDR                      (SOC_BBP_SCTRL_BASE_ADDR + 0x37C)





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
                     (1/1) register_define_BBP_SYSCTRL
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_MTCMOS_SET_UNION
 �ṹ˵��  : BBP_MTCMOS_SET �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ����ʹ��(C��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_mtcmos_set_reg;
    struct
    {
        unsigned int  lte_mtcmos_ctrl_set : 1;  /* bit[0]   : LTE��Դ���ϵ���λ��
                                                              д1��λ��д0��Ч�� */
        unsigned int  wtc_mtcmos_ctrl_set : 1;  /* bit[1]   : WTC��Դ���ϵ���λ��
                                                              д1��λ��д0��Ч�� */
        unsigned int  irm_mtcmos_ctrl_set : 1;  /* bit[2]   : IRM��Դ���ϵ���λ��
                                                              д1��λ��д0��Ч�� */
        unsigned int  reserved            : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_MTCMOS_SET_UNION;
#define BBPSCTRL_BBP_MTCMOS_SET_lte_mtcmos_ctrl_set_START  (0)
#define BBPSCTRL_BBP_MTCMOS_SET_lte_mtcmos_ctrl_set_END    (0)
#define BBPSCTRL_BBP_MTCMOS_SET_wtc_mtcmos_ctrl_set_START  (1)
#define BBPSCTRL_BBP_MTCMOS_SET_wtc_mtcmos_ctrl_set_END    (1)
#define BBPSCTRL_BBP_MTCMOS_SET_irm_mtcmos_ctrl_set_START  (2)
#define BBPSCTRL_BBP_MTCMOS_SET_irm_mtcmos_ctrl_set_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_MTCMOS_CLR_UNION
 �ṹ˵��  : BBP_MTCMOS_CLR �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ���ƹر�(C��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_mtcmos_clr_reg;
    struct
    {
        unsigned int  lte_mtcmos_ctrl_clr : 1;  /* bit[0]   : LTE��Դ���ϵ������
                                                              д1���㣬д0��Ч�� */
        unsigned int  wtc_mtcmos_ctrl_clr : 1;  /* bit[1]   : WTC��Դ���ϵ������
                                                              д1���㣬д0��Ч�� */
        unsigned int  irm_mtcmos_ctrl_clr : 1;  /* bit[2]   : IRM��Դ���ϵ������
                                                              д1���㣬д0��Ч�� */
        unsigned int  reserved            : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_MTCMOS_CLR_UNION;
#define BBPSCTRL_BBP_MTCMOS_CLR_lte_mtcmos_ctrl_clr_START  (0)
#define BBPSCTRL_BBP_MTCMOS_CLR_lte_mtcmos_ctrl_clr_END    (0)
#define BBPSCTRL_BBP_MTCMOS_CLR_wtc_mtcmos_ctrl_clr_START  (1)
#define BBPSCTRL_BBP_MTCMOS_CLR_wtc_mtcmos_ctrl_clr_END    (1)
#define BBPSCTRL_BBP_MTCMOS_CLR_irm_mtcmos_ctrl_clr_START  (2)
#define BBPSCTRL_BBP_MTCMOS_CLR_irm_mtcmos_ctrl_clr_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_MTCMOS_STATUS_UNION
 �ṹ˵��  : BBP_MTCMOS_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ����״̬(C��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_mtcmos_status_reg;
    struct
    {
        unsigned int  lte_mtcmos_ctrl_status : 1;  /* bit[0]   : LTE��Դ���Դ״̬��
                                                                 1���ϵ�
                                                                 0���µ� */
        unsigned int  wtc_mtcmos_ctrl_status : 1;  /* bit[1]   : WTC��Դ���Դ״̬��
                                                                 1���ϵ�
                                                                 0���µ� */
        unsigned int  irm_mtcmos_ctrl_status : 1;  /* bit[2]   : IRM��Դ���Դ״̬��
                                                                 1���ϵ�
                                                                 0���µ� */
        unsigned int  reserved               : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_MTCMOS_STATUS_UNION;
#define BBPSCTRL_BBP_MTCMOS_STATUS_lte_mtcmos_ctrl_status_START  (0)
#define BBPSCTRL_BBP_MTCMOS_STATUS_lte_mtcmos_ctrl_status_END    (0)
#define BBPSCTRL_BBP_MTCMOS_STATUS_wtc_mtcmos_ctrl_status_START  (1)
#define BBPSCTRL_BBP_MTCMOS_STATUS_wtc_mtcmos_ctrl_status_END    (1)
#define BBPSCTRL_BBP_MTCMOS_STATUS_irm_mtcmos_ctrl_status_START  (2)
#define BBPSCTRL_BBP_MTCMOS_STATUS_irm_mtcmos_ctrl_status_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_ISO_EN_SET_UNION
 �ṹ˵��  : BBP_ISO_EN_SET �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ�������ʹ��(C��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_iso_en_set_reg;
    struct
    {
        unsigned int  lte_iso_en_set : 1;  /* bit[0]   : LTE��Դ�������λ��
                                                         д1��λ��д0��Ч�� */
        unsigned int  wtc_iso_en_set : 1;  /* bit[1]   : WTC��Դ�������λ��
                                                         д1��λ��д0��Ч�� */
        unsigned int  irm_iso_en_set : 1;  /* bit[2]   : IRM��Դ�������λ��
                                                         д1��λ��д0��Ч�� */
        unsigned int  reserved       : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_ISO_EN_SET_UNION;
#define BBPSCTRL_BBP_ISO_EN_SET_lte_iso_en_set_START  (0)
#define BBPSCTRL_BBP_ISO_EN_SET_lte_iso_en_set_END    (0)
#define BBPSCTRL_BBP_ISO_EN_SET_wtc_iso_en_set_START  (1)
#define BBPSCTRL_BBP_ISO_EN_SET_wtc_iso_en_set_END    (1)
#define BBPSCTRL_BBP_ISO_EN_SET_irm_iso_en_set_START  (2)
#define BBPSCTRL_BBP_ISO_EN_SET_irm_iso_en_set_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_ISO_EN_CLR_UNION
 �ṹ˵��  : BBP_ISO_EN_CLR �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ������ƹر�(C��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_iso_en_clr_reg;
    struct
    {
        unsigned int  lte_iso_en_clr : 1;  /* bit[0]   : LTE��Դ����������
                                                         д1���㣬д0��Ч�� */
        unsigned int  wtc_iso_en_clr : 1;  /* bit[1]   : WTC��Դ����������
                                                         д1���㣬д0��Ч�� */
        unsigned int  irm_iso_en_clr : 1;  /* bit[2]   : IRM��Դ����������
                                                         д1���㣬д0��Ч�� */
        unsigned int  reserved       : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_ISO_EN_CLR_UNION;
#define BBPSCTRL_BBP_ISO_EN_CLR_lte_iso_en_clr_START  (0)
#define BBPSCTRL_BBP_ISO_EN_CLR_lte_iso_en_clr_END    (0)
#define BBPSCTRL_BBP_ISO_EN_CLR_wtc_iso_en_clr_START  (1)
#define BBPSCTRL_BBP_ISO_EN_CLR_wtc_iso_en_clr_END    (1)
#define BBPSCTRL_BBP_ISO_EN_CLR_irm_iso_en_clr_START  (2)
#define BBPSCTRL_BBP_ISO_EN_CLR_irm_iso_en_clr_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_ISO_EN_STATUS_UNION
 �ṹ˵��  : BBP_ISO_EN_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000007�����:32
 �Ĵ���˵��: BBP��Դ�������״̬(C��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_iso_en_status_reg;
    struct
    {
        unsigned int  lte_iso_en_status : 1;  /* bit[0]   : LTE��Դ�����״̬��
                                                            1�����룻
                                                            0��������룻 */
        unsigned int  wtc_iso_en_status : 1;  /* bit[1]   : WTC��Դ�����״̬��
                                                            1�����룻
                                                            0��������룻 */
        unsigned int  irm_iso_en_status : 1;  /* bit[2]   : IRM��Դ�����״̬��
                                                            1�����룻
                                                            0��������룻 */
        unsigned int  reserved          : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_ISO_EN_STATUS_UNION;
#define BBPSCTRL_BBP_ISO_EN_STATUS_lte_iso_en_status_START  (0)
#define BBPSCTRL_BBP_ISO_EN_STATUS_lte_iso_en_status_END    (0)
#define BBPSCTRL_BBP_ISO_EN_STATUS_wtc_iso_en_status_START  (1)
#define BBPSCTRL_BBP_ISO_EN_STATUS_wtc_iso_en_status_END    (1)
#define BBPSCTRL_BBP_ISO_EN_STATUS_irm_iso_en_status_START  (2)
#define BBPSCTRL_BBP_ISO_EN_STATUS_irm_iso_en_status_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_PD_CLK_SET_UNION
 �ṹ˵��  : BBP_PD_CLK_SET �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ��ʱ��ʹ��(C��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_clk_set_reg;
    struct
    {
        unsigned int  lte_pd_clk_ena : 1;  /* bit[0]   : LTE��Դ��ʱ��ʹ�ܡ�
                                                         д1��λ��д0��Ч�� */
        unsigned int  wtc_pd_clk_ena : 1;  /* bit[1]   : WTC��Դ��ʱ��ʹ�ܡ�
                                                         д1��λ��д0��Ч�� */
        unsigned int  irm_pd_clk_ena : 1;  /* bit[2]   : IRM��Դ��ʱ��ʹ�ܡ�
                                                         д1��λ��д0��Ч�� */
        unsigned int  reserved       : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_PD_CLK_SET_UNION;
#define BBPSCTRL_BBP_PD_CLK_SET_lte_pd_clk_ena_START  (0)
#define BBPSCTRL_BBP_PD_CLK_SET_lte_pd_clk_ena_END    (0)
#define BBPSCTRL_BBP_PD_CLK_SET_wtc_pd_clk_ena_START  (1)
#define BBPSCTRL_BBP_PD_CLK_SET_wtc_pd_clk_ena_END    (1)
#define BBPSCTRL_BBP_PD_CLK_SET_irm_pd_clk_ena_START  (2)
#define BBPSCTRL_BBP_PD_CLK_SET_irm_pd_clk_ena_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_PD_CLK_CLR_UNION
 �ṹ˵��  : BBP_PD_CLK_CLR �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ��ʱ�ӹر�(C��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_clk_clr_reg;
    struct
    {
        unsigned int  lte_pd_clk_dis : 1;  /* bit[0]   : LTE��Դ��ʱ�ӹرա�
                                                         д1�رգ�д0��Ч�� */
        unsigned int  wtc_pd_clk_dis : 1;  /* bit[1]   : WTC��Դ��ʱ�ӹرա�
                                                         д1�رգ�д0��Ч�� */
        unsigned int  irm_pd_clk_dis : 1;  /* bit[2]   : IRM��Դ��ʱ�ӹرա�
                                                         д1�رգ�д0��Ч�� */
        unsigned int  reserved       : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_PD_CLK_CLR_UNION;
#define BBPSCTRL_BBP_PD_CLK_CLR_lte_pd_clk_dis_START  (0)
#define BBPSCTRL_BBP_PD_CLK_CLR_lte_pd_clk_dis_END    (0)
#define BBPSCTRL_BBP_PD_CLK_CLR_wtc_pd_clk_dis_START  (1)
#define BBPSCTRL_BBP_PD_CLK_CLR_wtc_pd_clk_dis_END    (1)
#define BBPSCTRL_BBP_PD_CLK_CLR_irm_pd_clk_dis_START  (2)
#define BBPSCTRL_BBP_PD_CLK_CLR_irm_pd_clk_dis_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_PD_CLK_STATUS_UNION
 �ṹ˵��  : BBP_PD_CLK_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ��ʱ���ſ�״̬(C��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_clk_status_reg;
    struct
    {
        unsigned int  lte_pd_clk_status : 1;  /* bit[0]   : LTE��Դ��ʱ��״̬��
                                                            1��ʱ��ʹ��
                                                            0��ʱ�ӹر� */
        unsigned int  wtc_pd_clk_status : 1;  /* bit[1]   : WTC��Դ��ʱ��״̬��
                                                            1��ʱ��ʹ��
                                                            0��ʱ�ӹر� */
        unsigned int  irm_pd_clk_status : 1;  /* bit[2]   : IRM��Դ��ʱ��״̬��
                                                            1��ʱ��ʹ��
                                                            0��ʱ�ӹر� */
        unsigned int  reserved          : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_PD_CLK_STATUS_UNION;
#define BBPSCTRL_BBP_PD_CLK_STATUS_lte_pd_clk_status_START  (0)
#define BBPSCTRL_BBP_PD_CLK_STATUS_lte_pd_clk_status_END    (0)
#define BBPSCTRL_BBP_PD_CLK_STATUS_wtc_pd_clk_status_START  (1)
#define BBPSCTRL_BBP_PD_CLK_STATUS_wtc_pd_clk_status_END    (1)
#define BBPSCTRL_BBP_PD_CLK_STATUS_irm_pd_clk_status_START  (2)
#define BBPSCTRL_BBP_PD_CLK_STATUS_irm_pd_clk_status_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_PD_SRST_SET_UNION
 �ṹ˵��  : BBP_PD_SRST_SET �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ��λ����ʹ��(C��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_srst_set_reg;
    struct
    {
        unsigned int  lte_pd_srst_req : 1;  /* bit[0]   : LTE��Դ��λ����
                                                          д1��λ��д0��Ч�� */
        unsigned int  wtc_pd_srst_req : 1;  /* bit[1]   : WTC��Դ��λ����
                                                          д1��λ��д0��Ч�� */
        unsigned int  irm_pd_srst_req : 1;  /* bit[2]   : IRM��Դ��λ����
                                                          д1��λ��д0��Ч�� */
        unsigned int  reserved        : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_PD_SRST_SET_UNION;
#define BBPSCTRL_BBP_PD_SRST_SET_lte_pd_srst_req_START  (0)
#define BBPSCTRL_BBP_PD_SRST_SET_lte_pd_srst_req_END    (0)
#define BBPSCTRL_BBP_PD_SRST_SET_wtc_pd_srst_req_START  (1)
#define BBPSCTRL_BBP_PD_SRST_SET_wtc_pd_srst_req_END    (1)
#define BBPSCTRL_BBP_PD_SRST_SET_irm_pd_srst_req_START  (2)
#define BBPSCTRL_BBP_PD_SRST_SET_irm_pd_srst_req_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_PD_SRST_CLR_UNION
 �ṹ˵��  : BBP_PD_SRST_CLR �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ��λ����ر�(C��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_srst_clr_reg;
    struct
    {
        unsigned int  lte_pd_srst_dis : 1;  /* bit[0]   : LTE��Դ��λ�����
                                                          д1�����λ��д0��Ч�� */
        unsigned int  wtc_pd_srst_dis : 1;  /* bit[1]   : WTC��Դ��λ�����
                                                          д1�����λ��д0��Ч�� */
        unsigned int  irm_pd_srst_dis : 1;  /* bit[2]   : IRM��Դ��λ�����
                                                          д1�����λ��д0��Ч�� */
        unsigned int  reserved        : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_PD_SRST_CLR_UNION;
#define BBPSCTRL_BBP_PD_SRST_CLR_lte_pd_srst_dis_START  (0)
#define BBPSCTRL_BBP_PD_SRST_CLR_lte_pd_srst_dis_END    (0)
#define BBPSCTRL_BBP_PD_SRST_CLR_wtc_pd_srst_dis_START  (1)
#define BBPSCTRL_BBP_PD_SRST_CLR_wtc_pd_srst_dis_END    (1)
#define BBPSCTRL_BBP_PD_SRST_CLR_irm_pd_srst_dis_START  (2)
#define BBPSCTRL_BBP_PD_SRST_CLR_irm_pd_srst_dis_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_PD_SRST_STATUS_UNION
 �ṹ˵��  : BBP_PD_SRST_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x00000007�����:32
 �Ĵ���˵��: BBP��Դ��λ����״̬(C��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_srst_status_reg;
    struct
    {
        unsigned int  lte_pd_srst_status : 1;  /* bit[0]   : LTE��Դ��λ״̬��
                                                             1����λ��
                                                             0�������λ�� */
        unsigned int  wtc_pd_srst_status : 1;  /* bit[1]   : WTC��Դ��λ״̬��
                                                             1����λ��
                                                             0�������λ�� */
        unsigned int  irm_pd_srst_status : 1;  /* bit[2]   : IRM��Դ��λ״̬��
                                                             1����λ��
                                                             0�������λ�� */
        unsigned int  reserved           : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_PD_SRST_STATUS_UNION;
#define BBPSCTRL_BBP_PD_SRST_STATUS_lte_pd_srst_status_START  (0)
#define BBPSCTRL_BBP_PD_SRST_STATUS_lte_pd_srst_status_END    (0)
#define BBPSCTRL_BBP_PD_SRST_STATUS_wtc_pd_srst_status_START  (1)
#define BBPSCTRL_BBP_PD_SRST_STATUS_wtc_pd_srst_status_END    (1)
#define BBPSCTRL_BBP_PD_SRST_STATUS_irm_pd_srst_status_START  (2)
#define BBPSCTRL_BBP_PD_SRST_STATUS_irm_pd_srst_status_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_CLK0_SET_UNION
 �ṹ˵��  : BBP_CLK0_SET �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ���Ƶ��ʱ��ʹ��(lte/wtc/irm)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_clk0_set_reg;
    struct
    {
        unsigned int  pdlte_32k_clk_en           : 1;  /* bit[0]    :  */
        unsigned int  pdlte_19m_clk_en           : 1;  /* bit[1]    :  */
        unsigned int  pdlte_pdt_122m_clk_en      : 1;  /* bit[2]    :  */
        unsigned int  pdlte_pdt_245m_122m_clk_en : 1;  /* bit[3]    :  */
        unsigned int  pdlte_pdf_245_122m_clk_en  : 1;  /* bit[4]    :  */
        unsigned int  reserved_0                 : 1;  /* bit[5]    :  */
        unsigned int  reserved_1                 : 1;  /* bit[6]    :  */
        unsigned int  reserved_2                 : 1;  /* bit[7]    :  */
        unsigned int  pdlte_lte_abb0_tx_mclk_en  : 1;  /* bit[8]    : BLV7R5�汾�����ź�ͬʱ����LTE PD��IRM PD��
                                                                      DALLAS�汾�����ź���LTE PDȡ������ʹ�ã�ֻ������IRM PD */
        unsigned int  pdlte_lte_abb1_tx_mclk_en  : 1;  /* bit[9]    : BLV7R5�汾�����ź�ͬʱ����LTE PD��IRM PD��
                                                                      DALLAS�汾�����ź���LTE PDȡ������ʹ�ã�ֻ������IRM PD */
        unsigned int  pdlte_axim_clk_en          : 1;  /* bit[10]   :  */
        unsigned int  pdwtc_32k_clk_en           : 1;  /* bit[11]   :  */
        unsigned int  pdwtc_19m_clk_en           : 1;  /* bit[12]   :  */
        unsigned int  pdwtc_61m_clk_en           : 1;  /* bit[13]   :  */
        unsigned int  pdwtc_122m_clk_en          : 1;  /* bit[14]   :  */
        unsigned int  pdwtc_245m_clk_en          : 1;  /* bit[15]   :  */
        unsigned int  reserved_3                 : 1;  /* bit[16]   :  */
        unsigned int  reserved_4                 : 1;  /* bit[17]   :  */
        unsigned int  reserved_5                 : 1;  /* bit[18]   :  */
        unsigned int  pdirm_122m_clk_en          : 1;  /* bit[19]   :  */
        unsigned int  pdirm_245m_clk_en          : 1;  /* bit[20]   :  */
        unsigned int  reserved_6                 : 1;  /* bit[21]   :  */
        unsigned int  pduc2_32k_clk_en           : 1;  /* bit[22]   :  */
        unsigned int  pduc2_19m_clk_en           : 1;  /* bit[23]   :  */
        unsigned int  pduc2_61m_clk_en           : 1;  /* bit[24]   :  */
        unsigned int  pduc2_122m_clk_en          : 1;  /* bit[25]   :  */
        unsigned int  pduc2_245m_clk_en          : 1;  /* bit[26]   :  */
        unsigned int  reserved_7                 : 5;  /* bit[27-31]: ������Debugʹ�á� */
    } reg;
} BBPSCTRL_BBP_CLK0_SET_UNION;
#define BBPSCTRL_BBP_CLK0_SET_pdlte_32k_clk_en_START            (0)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_32k_clk_en_END              (0)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_19m_clk_en_START            (1)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_19m_clk_en_END              (1)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_pdt_122m_clk_en_START       (2)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_pdt_122m_clk_en_END         (2)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_pdt_245m_122m_clk_en_START  (3)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_pdt_245m_122m_clk_en_END    (3)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_pdf_245_122m_clk_en_START   (4)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_pdf_245_122m_clk_en_END     (4)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_lte_abb0_tx_mclk_en_START   (8)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_lte_abb0_tx_mclk_en_END     (8)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_lte_abb1_tx_mclk_en_START   (9)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_lte_abb1_tx_mclk_en_END     (9)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_axim_clk_en_START           (10)
#define BBPSCTRL_BBP_CLK0_SET_pdlte_axim_clk_en_END             (10)
#define BBPSCTRL_BBP_CLK0_SET_pdwtc_32k_clk_en_START            (11)
#define BBPSCTRL_BBP_CLK0_SET_pdwtc_32k_clk_en_END              (11)
#define BBPSCTRL_BBP_CLK0_SET_pdwtc_19m_clk_en_START            (12)
#define BBPSCTRL_BBP_CLK0_SET_pdwtc_19m_clk_en_END              (12)
#define BBPSCTRL_BBP_CLK0_SET_pdwtc_61m_clk_en_START            (13)
#define BBPSCTRL_BBP_CLK0_SET_pdwtc_61m_clk_en_END              (13)
#define BBPSCTRL_BBP_CLK0_SET_pdwtc_122m_clk_en_START           (14)
#define BBPSCTRL_BBP_CLK0_SET_pdwtc_122m_clk_en_END             (14)
#define BBPSCTRL_BBP_CLK0_SET_pdwtc_245m_clk_en_START           (15)
#define BBPSCTRL_BBP_CLK0_SET_pdwtc_245m_clk_en_END             (15)
#define BBPSCTRL_BBP_CLK0_SET_pdirm_122m_clk_en_START           (19)
#define BBPSCTRL_BBP_CLK0_SET_pdirm_122m_clk_en_END             (19)
#define BBPSCTRL_BBP_CLK0_SET_pdirm_245m_clk_en_START           (20)
#define BBPSCTRL_BBP_CLK0_SET_pdirm_245m_clk_en_END             (20)
#define BBPSCTRL_BBP_CLK0_SET_pduc2_32k_clk_en_START            (22)
#define BBPSCTRL_BBP_CLK0_SET_pduc2_32k_clk_en_END              (22)
#define BBPSCTRL_BBP_CLK0_SET_pduc2_19m_clk_en_START            (23)
#define BBPSCTRL_BBP_CLK0_SET_pduc2_19m_clk_en_END              (23)
#define BBPSCTRL_BBP_CLK0_SET_pduc2_61m_clk_en_START            (24)
#define BBPSCTRL_BBP_CLK0_SET_pduc2_61m_clk_en_END              (24)
#define BBPSCTRL_BBP_CLK0_SET_pduc2_122m_clk_en_START           (25)
#define BBPSCTRL_BBP_CLK0_SET_pduc2_122m_clk_en_END             (25)
#define BBPSCTRL_BBP_CLK0_SET_pduc2_245m_clk_en_START           (26)
#define BBPSCTRL_BBP_CLK0_SET_pduc2_245m_clk_en_END             (26)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_CLK0_CLR_UNION
 �ṹ˵��  : BBP_CLK0_CLR �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ���Ƶ��ʱ�ӹر�(lte/wtc/irm)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_clk0_clr_reg;
    struct
    {
        unsigned int  pdlte_32k_clk_dis           : 1;  /* bit[0]    :  */
        unsigned int  pdlte_19m_clk_dis           : 1;  /* bit[1]    :  */
        unsigned int  pdlte_pdt_122m_clk_dis      : 1;  /* bit[2]    :  */
        unsigned int  pdlte_pdt_245m_122m_clk_dis : 1;  /* bit[3]    :  */
        unsigned int  pdlte_pdf_245_122m_clk_dis  : 1;  /* bit[4]    :  */
        unsigned int  reserved_0                  : 1;  /* bit[5]    :  */
        unsigned int  reserved_1                  : 1;  /* bit[6]    :  */
        unsigned int  reserved_2                  : 1;  /* bit[7]    :  */
        unsigned int  pdlte_lte_abb0_tx_mclk_dis  : 1;  /* bit[8]    : BLV7R5�汾�����ź�ͬʱ����LTE PD��IRM PD��
                                                                       DALLAS�汾�����ź���LTE PDȡ������ʹ�ã�ֻ��IRM PD��Ч */
        unsigned int  pdlte_lte_abb1_tx_mclk_dis  : 1;  /* bit[9]    : BLV7R5�汾�����ź�ͬʱ����LTE PD��IRM PD��
                                                                       DALLAS�汾�����ź���LTE PDȡ������ʹ�ã�ֻ��IRM PD��Ч */
        unsigned int  pdlte_axim_clk_dis          : 1;  /* bit[10]   :  */
        unsigned int  pdwtc_32k_clk_dis           : 1;  /* bit[11]   :  */
        unsigned int  pdwtc_19m_clk_dis           : 1;  /* bit[12]   :  */
        unsigned int  pdwtc_61m_clk_dis           : 1;  /* bit[13]   :  */
        unsigned int  pdwtc_122m_clk_dis          : 1;  /* bit[14]   :  */
        unsigned int  pdwtc_245m_clk_dis          : 1;  /* bit[15]   :  */
        unsigned int  reserved_3                  : 1;  /* bit[16]   :  */
        unsigned int  reserved_4                  : 1;  /* bit[17]   :  */
        unsigned int  reserved_5                  : 1;  /* bit[18]   :  */
        unsigned int  pdirm_122m_clk_dis          : 1;  /* bit[19]   :  */
        unsigned int  pdirm_245m_clk_dis          : 1;  /* bit[20]   :  */
        unsigned int  reserved_6                  : 1;  /* bit[21]   :  */
        unsigned int  pduc2_32k_clk_dis           : 1;  /* bit[22]   :  */
        unsigned int  pduc2_19m_clk_dis           : 1;  /* bit[23]   :  */
        unsigned int  pduc2_61m_clk_dis           : 1;  /* bit[24]   :  */
        unsigned int  pduc2_122m_clk_dis          : 1;  /* bit[25]   :  */
        unsigned int  pduc2_245m_clk_dis          : 1;  /* bit[26]   :  */
        unsigned int  reserved_7                  : 5;  /* bit[27-31]: ������Debugʹ�á� */
    } reg;
} BBPSCTRL_BBP_CLK0_CLR_UNION;
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_32k_clk_dis_START            (0)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_32k_clk_dis_END              (0)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_19m_clk_dis_START            (1)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_19m_clk_dis_END              (1)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_pdt_122m_clk_dis_START       (2)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_pdt_122m_clk_dis_END         (2)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_pdt_245m_122m_clk_dis_START  (3)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_pdt_245m_122m_clk_dis_END    (3)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_pdf_245_122m_clk_dis_START   (4)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_pdf_245_122m_clk_dis_END     (4)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_lte_abb0_tx_mclk_dis_START   (8)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_lte_abb0_tx_mclk_dis_END     (8)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_lte_abb1_tx_mclk_dis_START   (9)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_lte_abb1_tx_mclk_dis_END     (9)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_axim_clk_dis_START           (10)
#define BBPSCTRL_BBP_CLK0_CLR_pdlte_axim_clk_dis_END             (10)
#define BBPSCTRL_BBP_CLK0_CLR_pdwtc_32k_clk_dis_START            (11)
#define BBPSCTRL_BBP_CLK0_CLR_pdwtc_32k_clk_dis_END              (11)
#define BBPSCTRL_BBP_CLK0_CLR_pdwtc_19m_clk_dis_START            (12)
#define BBPSCTRL_BBP_CLK0_CLR_pdwtc_19m_clk_dis_END              (12)
#define BBPSCTRL_BBP_CLK0_CLR_pdwtc_61m_clk_dis_START            (13)
#define BBPSCTRL_BBP_CLK0_CLR_pdwtc_61m_clk_dis_END              (13)
#define BBPSCTRL_BBP_CLK0_CLR_pdwtc_122m_clk_dis_START           (14)
#define BBPSCTRL_BBP_CLK0_CLR_pdwtc_122m_clk_dis_END             (14)
#define BBPSCTRL_BBP_CLK0_CLR_pdwtc_245m_clk_dis_START           (15)
#define BBPSCTRL_BBP_CLK0_CLR_pdwtc_245m_clk_dis_END             (15)
#define BBPSCTRL_BBP_CLK0_CLR_pdirm_122m_clk_dis_START           (19)
#define BBPSCTRL_BBP_CLK0_CLR_pdirm_122m_clk_dis_END             (19)
#define BBPSCTRL_BBP_CLK0_CLR_pdirm_245m_clk_dis_START           (20)
#define BBPSCTRL_BBP_CLK0_CLR_pdirm_245m_clk_dis_END             (20)
#define BBPSCTRL_BBP_CLK0_CLR_pduc2_32k_clk_dis_START            (22)
#define BBPSCTRL_BBP_CLK0_CLR_pduc2_32k_clk_dis_END              (22)
#define BBPSCTRL_BBP_CLK0_CLR_pduc2_19m_clk_dis_START            (23)
#define BBPSCTRL_BBP_CLK0_CLR_pduc2_19m_clk_dis_END              (23)
#define BBPSCTRL_BBP_CLK0_CLR_pduc2_61m_clk_dis_START            (24)
#define BBPSCTRL_BBP_CLK0_CLR_pduc2_61m_clk_dis_END              (24)
#define BBPSCTRL_BBP_CLK0_CLR_pduc2_122m_clk_dis_START           (25)
#define BBPSCTRL_BBP_CLK0_CLR_pduc2_122m_clk_dis_END             (25)
#define BBPSCTRL_BBP_CLK0_CLR_pduc2_245m_clk_dis_START           (26)
#define BBPSCTRL_BBP_CLK0_CLR_pduc2_245m_clk_dis_END             (26)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_CLK0_STATUS_UNION
 �ṹ˵��  : BBP_CLK0_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: BBP��Դ���Ƶ��ʱ���ſ�״̬(lte/wtc/irm)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_clk0_status_reg;
    struct
    {
        unsigned int  pdlte_32k_clk_status           : 1;  /* bit[0]    :  */
        unsigned int  pdlte_19m_clk_status           : 1;  /* bit[1]    :  */
        unsigned int  pdlte_pdt_122m_clk_status      : 1;  /* bit[2]    :  */
        unsigned int  pdlte_pdt_245m_122m_clk_status : 1;  /* bit[3]    :  */
        unsigned int  pdlte_pdf_245_122m_clk_status  : 1;  /* bit[4]    :  */
        unsigned int  reserved_0                     : 1;  /* bit[5]    :  */
        unsigned int  reserved_1                     : 1;  /* bit[6]    :  */
        unsigned int  reserved_2                     : 1;  /* bit[7]    :  */
        unsigned int  pdlte_lte_abb0_tx_mclk_status  : 1;  /* bit[8]    : BLV7R5�汾�����ź�ͬʱ����LTE PD��IRM PD��
                                                                          DALLAS�汾�����ź���LTE PDȡ������ʹ�ã�ֻ��IRM PD��Ч */
        unsigned int  pdlte_lte_abb1_tx_mclk_status  : 1;  /* bit[9]    : BLV7R5�汾�����ź�ͬʱ����LTE PD��IRM PD��
                                                                          DALLAS�汾�����ź���LTE PDȡ������ʹ�ã�ֻ��IRM PD��Ч */
        unsigned int  pdlte_axim_clk_status          : 1;  /* bit[10]   :  */
        unsigned int  pdwtc_32k_clk_status           : 1;  /* bit[11]   :  */
        unsigned int  pdwtc_19m_clk_status           : 1;  /* bit[12]   :  */
        unsigned int  pdwtc_61m_clk_status           : 1;  /* bit[13]   :  */
        unsigned int  pdwtc_122m_clk_status          : 1;  /* bit[14]   :  */
        unsigned int  pdwtc_245m_clk_status          : 1;  /* bit[15]   :  */
        unsigned int  reserved_3                     : 1;  /* bit[16]   :  */
        unsigned int  reserved_4                     : 1;  /* bit[17]   :  */
        unsigned int  reserved_5                     : 1;  /* bit[18]   :  */
        unsigned int  pdirm_122m_clk_status          : 1;  /* bit[19]   :  */
        unsigned int  pdirm_245m_clk_status          : 1;  /* bit[20]   :  */
        unsigned int  reserved_6                     : 1;  /* bit[21]   :  */
        unsigned int  pduc2_32k_clk_status           : 1;  /* bit[22]   :  */
        unsigned int  pduc2_19m_clk_status           : 1;  /* bit[23]   :  */
        unsigned int  pduc2_61m_clk_status           : 1;  /* bit[24]   :  */
        unsigned int  pduc2_122m_clk_status          : 1;  /* bit[25]   :  */
        unsigned int  pduc2_245m_clk_status          : 1;  /* bit[26]   :  */
        unsigned int  reserved_7                     : 5;  /* bit[27-31]: ������Debugʹ�á� */
    } reg;
} BBPSCTRL_BBP_CLK0_STATUS_UNION;
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_32k_clk_status_START            (0)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_32k_clk_status_END              (0)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_19m_clk_status_START            (1)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_19m_clk_status_END              (1)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_pdt_122m_clk_status_START       (2)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_pdt_122m_clk_status_END         (2)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_pdt_245m_122m_clk_status_START  (3)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_pdt_245m_122m_clk_status_END    (3)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_pdf_245_122m_clk_status_START   (4)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_pdf_245_122m_clk_status_END     (4)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_lte_abb0_tx_mclk_status_START   (8)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_lte_abb0_tx_mclk_status_END     (8)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_lte_abb1_tx_mclk_status_START   (9)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_lte_abb1_tx_mclk_status_END     (9)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_axim_clk_status_START           (10)
#define BBPSCTRL_BBP_CLK0_STATUS_pdlte_axim_clk_status_END             (10)
#define BBPSCTRL_BBP_CLK0_STATUS_pdwtc_32k_clk_status_START            (11)
#define BBPSCTRL_BBP_CLK0_STATUS_pdwtc_32k_clk_status_END              (11)
#define BBPSCTRL_BBP_CLK0_STATUS_pdwtc_19m_clk_status_START            (12)
#define BBPSCTRL_BBP_CLK0_STATUS_pdwtc_19m_clk_status_END              (12)
#define BBPSCTRL_BBP_CLK0_STATUS_pdwtc_61m_clk_status_START            (13)
#define BBPSCTRL_BBP_CLK0_STATUS_pdwtc_61m_clk_status_END              (13)
#define BBPSCTRL_BBP_CLK0_STATUS_pdwtc_122m_clk_status_START           (14)
#define BBPSCTRL_BBP_CLK0_STATUS_pdwtc_122m_clk_status_END             (14)
#define BBPSCTRL_BBP_CLK0_STATUS_pdwtc_245m_clk_status_START           (15)
#define BBPSCTRL_BBP_CLK0_STATUS_pdwtc_245m_clk_status_END             (15)
#define BBPSCTRL_BBP_CLK0_STATUS_pdirm_122m_clk_status_START           (19)
#define BBPSCTRL_BBP_CLK0_STATUS_pdirm_122m_clk_status_END             (19)
#define BBPSCTRL_BBP_CLK0_STATUS_pdirm_245m_clk_status_START           (20)
#define BBPSCTRL_BBP_CLK0_STATUS_pdirm_245m_clk_status_END             (20)
#define BBPSCTRL_BBP_CLK0_STATUS_pduc2_32k_clk_status_START            (22)
#define BBPSCTRL_BBP_CLK0_STATUS_pduc2_32k_clk_status_END              (22)
#define BBPSCTRL_BBP_CLK0_STATUS_pduc2_19m_clk_status_START            (23)
#define BBPSCTRL_BBP_CLK0_STATUS_pduc2_19m_clk_status_END              (23)
#define BBPSCTRL_BBP_CLK0_STATUS_pduc2_61m_clk_status_START            (24)
#define BBPSCTRL_BBP_CLK0_STATUS_pduc2_61m_clk_status_END              (24)
#define BBPSCTRL_BBP_CLK0_STATUS_pduc2_122m_clk_status_START           (25)
#define BBPSCTRL_BBP_CLK0_STATUS_pduc2_122m_clk_status_END             (25)
#define BBPSCTRL_BBP_CLK0_STATUS_pduc2_245m_clk_status_START           (26)
#define BBPSCTRL_BBP_CLK0_STATUS_pduc2_245m_clk_status_END             (26)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_CLK1_SET_UNION
 �ṹ˵��  : BBP_CLK1_SET �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ���Ƶ��ʱ��ʹ��(com)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_clk1_set_reg;
    struct
    {
        unsigned int  bbc_19m_clk_en           : 1;  /* bit[0]    :  */
        unsigned int  com_g_32k_clk_en         : 1;  /* bit[1]    :  */
        unsigned int  bbc_g_104m_clk_en        : 1;  /* bit[2]    :  */
        unsigned int  bbc_wtc_122m_clk_en      : 1;  /* bit[3]    :  */
        unsigned int  bbc_wtc_245m_clk_en      : 1;  /* bit[4]    :  */
        unsigned int  com_pdt_122m_clk_en      : 1;  /* bit[5]    :  */
        unsigned int  com_pdt_245m_122m_clk_en : 1;  /* bit[6]    :  */
        unsigned int  com_pdf_245m_122m_clk_en : 1;  /* bit[7]    :  */
        unsigned int  com_wtc_61m_clk_en       : 1;  /* bit[8]    :  */
        unsigned int  com_lte_245m_clk_en      : 1;  /* bit[9]    :  */
        unsigned int  com_wc_abb_122m_clk_en   : 1;  /* bit[10]   :  */
        unsigned int  com_wc_abb_61m_clk_en    : 1;  /* bit[11]   :  */
        unsigned int  com_uc2_61m_clk_en       : 1;  /* bit[12]   :  */
        unsigned int  bbc_uc2_122m_clk_en      : 1;  /* bit[13]   :  */
        unsigned int  com_uc2_245m_clk_en      : 1;  /* bit[14]   :  */
        unsigned int  reserved                 : 17; /* bit[15-31]: ������Debugʹ�á� */
    } reg;
} BBPSCTRL_BBP_CLK1_SET_UNION;
#define BBPSCTRL_BBP_CLK1_SET_bbc_19m_clk_en_START            (0)
#define BBPSCTRL_BBP_CLK1_SET_bbc_19m_clk_en_END              (0)
#define BBPSCTRL_BBP_CLK1_SET_com_g_32k_clk_en_START          (1)
#define BBPSCTRL_BBP_CLK1_SET_com_g_32k_clk_en_END            (1)
#define BBPSCTRL_BBP_CLK1_SET_bbc_g_104m_clk_en_START         (2)
#define BBPSCTRL_BBP_CLK1_SET_bbc_g_104m_clk_en_END           (2)
#define BBPSCTRL_BBP_CLK1_SET_bbc_wtc_122m_clk_en_START       (3)
#define BBPSCTRL_BBP_CLK1_SET_bbc_wtc_122m_clk_en_END         (3)
#define BBPSCTRL_BBP_CLK1_SET_bbc_wtc_245m_clk_en_START       (4)
#define BBPSCTRL_BBP_CLK1_SET_bbc_wtc_245m_clk_en_END         (4)
#define BBPSCTRL_BBP_CLK1_SET_com_pdt_122m_clk_en_START       (5)
#define BBPSCTRL_BBP_CLK1_SET_com_pdt_122m_clk_en_END         (5)
#define BBPSCTRL_BBP_CLK1_SET_com_pdt_245m_122m_clk_en_START  (6)
#define BBPSCTRL_BBP_CLK1_SET_com_pdt_245m_122m_clk_en_END    (6)
#define BBPSCTRL_BBP_CLK1_SET_com_pdf_245m_122m_clk_en_START  (7)
#define BBPSCTRL_BBP_CLK1_SET_com_pdf_245m_122m_clk_en_END    (7)
#define BBPSCTRL_BBP_CLK1_SET_com_wtc_61m_clk_en_START        (8)
#define BBPSCTRL_BBP_CLK1_SET_com_wtc_61m_clk_en_END          (8)
#define BBPSCTRL_BBP_CLK1_SET_com_lte_245m_clk_en_START       (9)
#define BBPSCTRL_BBP_CLK1_SET_com_lte_245m_clk_en_END         (9)
#define BBPSCTRL_BBP_CLK1_SET_com_wc_abb_122m_clk_en_START    (10)
#define BBPSCTRL_BBP_CLK1_SET_com_wc_abb_122m_clk_en_END      (10)
#define BBPSCTRL_BBP_CLK1_SET_com_wc_abb_61m_clk_en_START     (11)
#define BBPSCTRL_BBP_CLK1_SET_com_wc_abb_61m_clk_en_END       (11)
#define BBPSCTRL_BBP_CLK1_SET_com_uc2_61m_clk_en_START        (12)
#define BBPSCTRL_BBP_CLK1_SET_com_uc2_61m_clk_en_END          (12)
#define BBPSCTRL_BBP_CLK1_SET_bbc_uc2_122m_clk_en_START       (13)
#define BBPSCTRL_BBP_CLK1_SET_bbc_uc2_122m_clk_en_END         (13)
#define BBPSCTRL_BBP_CLK1_SET_com_uc2_245m_clk_en_START       (14)
#define BBPSCTRL_BBP_CLK1_SET_com_uc2_245m_clk_en_END         (14)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_CLK1_CLR_UNION
 �ṹ˵��  : BBP_CLK1_CLR �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ���Ƶ��ʱ�ӹر�(com)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_clk1_clr_reg;
    struct
    {
        unsigned int  bbc_19m_clk_dis           : 1;  /* bit[0]    :  */
        unsigned int  com_g_32k_clk_dis         : 1;  /* bit[1]    :  */
        unsigned int  bbc_g_104m_clk_dis        : 1;  /* bit[2]    :  */
        unsigned int  bbc_wtc_122m_clk_dis      : 1;  /* bit[3]    :  */
        unsigned int  bbc_wtc_245m_clk_dis      : 1;  /* bit[4]    :  */
        unsigned int  com_pdt_122m_clk_dis      : 1;  /* bit[5]    :  */
        unsigned int  com_pdt_245m_122m_clk_dis : 1;  /* bit[6]    :  */
        unsigned int  com_pdf_245m_122m_clk_dis : 1;  /* bit[7]    :  */
        unsigned int  com_wtc_61m_clk_dis       : 1;  /* bit[8]    :  */
        unsigned int  com_lte_245m_clk_dis      : 1;  /* bit[9]    :  */
        unsigned int  com_wc_abb_122m_clk_dis   : 1;  /* bit[10]   :  */
        unsigned int  com_wc_abb_61m_clk_dis    : 1;  /* bit[11]   :  */
        unsigned int  com_uc2_61m_clk_dis       : 1;  /* bit[12]   :  */
        unsigned int  bbc_uc2_122m_clk_dis      : 1;  /* bit[13]   :  */
        unsigned int  com_uc2_245m_clk_dis      : 1;  /* bit[14]   :  */
        unsigned int  reserved                  : 17; /* bit[15-31]: ������Debugʹ�á� */
    } reg;
} BBPSCTRL_BBP_CLK1_CLR_UNION;
#define BBPSCTRL_BBP_CLK1_CLR_bbc_19m_clk_dis_START            (0)
#define BBPSCTRL_BBP_CLK1_CLR_bbc_19m_clk_dis_END              (0)
#define BBPSCTRL_BBP_CLK1_CLR_com_g_32k_clk_dis_START          (1)
#define BBPSCTRL_BBP_CLK1_CLR_com_g_32k_clk_dis_END            (1)
#define BBPSCTRL_BBP_CLK1_CLR_bbc_g_104m_clk_dis_START         (2)
#define BBPSCTRL_BBP_CLK1_CLR_bbc_g_104m_clk_dis_END           (2)
#define BBPSCTRL_BBP_CLK1_CLR_bbc_wtc_122m_clk_dis_START       (3)
#define BBPSCTRL_BBP_CLK1_CLR_bbc_wtc_122m_clk_dis_END         (3)
#define BBPSCTRL_BBP_CLK1_CLR_bbc_wtc_245m_clk_dis_START       (4)
#define BBPSCTRL_BBP_CLK1_CLR_bbc_wtc_245m_clk_dis_END         (4)
#define BBPSCTRL_BBP_CLK1_CLR_com_pdt_122m_clk_dis_START       (5)
#define BBPSCTRL_BBP_CLK1_CLR_com_pdt_122m_clk_dis_END         (5)
#define BBPSCTRL_BBP_CLK1_CLR_com_pdt_245m_122m_clk_dis_START  (6)
#define BBPSCTRL_BBP_CLK1_CLR_com_pdt_245m_122m_clk_dis_END    (6)
#define BBPSCTRL_BBP_CLK1_CLR_com_pdf_245m_122m_clk_dis_START  (7)
#define BBPSCTRL_BBP_CLK1_CLR_com_pdf_245m_122m_clk_dis_END    (7)
#define BBPSCTRL_BBP_CLK1_CLR_com_wtc_61m_clk_dis_START        (8)
#define BBPSCTRL_BBP_CLK1_CLR_com_wtc_61m_clk_dis_END          (8)
#define BBPSCTRL_BBP_CLK1_CLR_com_lte_245m_clk_dis_START       (9)
#define BBPSCTRL_BBP_CLK1_CLR_com_lte_245m_clk_dis_END         (9)
#define BBPSCTRL_BBP_CLK1_CLR_com_wc_abb_122m_clk_dis_START    (10)
#define BBPSCTRL_BBP_CLK1_CLR_com_wc_abb_122m_clk_dis_END      (10)
#define BBPSCTRL_BBP_CLK1_CLR_com_wc_abb_61m_clk_dis_START     (11)
#define BBPSCTRL_BBP_CLK1_CLR_com_wc_abb_61m_clk_dis_END       (11)
#define BBPSCTRL_BBP_CLK1_CLR_com_uc2_61m_clk_dis_START        (12)
#define BBPSCTRL_BBP_CLK1_CLR_com_uc2_61m_clk_dis_END          (12)
#define BBPSCTRL_BBP_CLK1_CLR_bbc_uc2_122m_clk_dis_START       (13)
#define BBPSCTRL_BBP_CLK1_CLR_bbc_uc2_122m_clk_dis_END         (13)
#define BBPSCTRL_BBP_CLK1_CLR_com_uc2_245m_clk_dis_START       (14)
#define BBPSCTRL_BBP_CLK1_CLR_com_uc2_245m_clk_dis_END         (14)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_CLK1_STATUS_UNION
 �ṹ˵��  : BBP_CLK1_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: BBP��Դ���Ƶ��ʱ���ſ�״̬(com)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_clk1_status_reg;
    struct
    {
        unsigned int  bbc_19m_clk_status           : 1;  /* bit[0]    :  */
        unsigned int  com_g_32k_clk_status         : 1;  /* bit[1]    :  */
        unsigned int  bbc_g_104m_clk_status        : 1;  /* bit[2]    : G */
        unsigned int  bbc_wtc_122m_clk_status      : 1;  /* bit[3]    : WTC */
        unsigned int  bbc_wtc_245m_clk_status      : 1;  /* bit[4]    : TDS */
        unsigned int  com_pdt_122m_clk_status      : 1;  /* bit[5]    : PDT */
        unsigned int  com_pdt_245m_122m_clk_status : 1;  /* bit[6]    : ULHB */
        unsigned int  com_pdf_245m_122m_clk_status : 1;  /* bit[7]    : PDF */
        unsigned int  com_wtc_61m_clk_status       : 1;  /* bit[8]    :  */
        unsigned int  com_lte_245m_clk_status      : 1;  /* bit[9]    :  */
        unsigned int  com_wc_abb_122m_clk_status   : 1;  /* bit[10]   :  */
        unsigned int  com_wc_abb_61m_clk_status    : 1;  /* bit[11]   :  */
        unsigned int  com_uc2_61m_clk_status       : 1;  /* bit[12]   :  */
        unsigned int  bbc_uc2_122m_clk_status      : 1;  /* bit[13]   : C2 */
        unsigned int  com_uc2_245m_clk_status      : 1;  /* bit[14]   :  */
        unsigned int  reserved                     : 17; /* bit[15-31]: ������Debugʹ�á� */
    } reg;
} BBPSCTRL_BBP_CLK1_STATUS_UNION;
#define BBPSCTRL_BBP_CLK1_STATUS_bbc_19m_clk_status_START            (0)
#define BBPSCTRL_BBP_CLK1_STATUS_bbc_19m_clk_status_END              (0)
#define BBPSCTRL_BBP_CLK1_STATUS_com_g_32k_clk_status_START          (1)
#define BBPSCTRL_BBP_CLK1_STATUS_com_g_32k_clk_status_END            (1)
#define BBPSCTRL_BBP_CLK1_STATUS_bbc_g_104m_clk_status_START         (2)
#define BBPSCTRL_BBP_CLK1_STATUS_bbc_g_104m_clk_status_END           (2)
#define BBPSCTRL_BBP_CLK1_STATUS_bbc_wtc_122m_clk_status_START       (3)
#define BBPSCTRL_BBP_CLK1_STATUS_bbc_wtc_122m_clk_status_END         (3)
#define BBPSCTRL_BBP_CLK1_STATUS_bbc_wtc_245m_clk_status_START       (4)
#define BBPSCTRL_BBP_CLK1_STATUS_bbc_wtc_245m_clk_status_END         (4)
#define BBPSCTRL_BBP_CLK1_STATUS_com_pdt_122m_clk_status_START       (5)
#define BBPSCTRL_BBP_CLK1_STATUS_com_pdt_122m_clk_status_END         (5)
#define BBPSCTRL_BBP_CLK1_STATUS_com_pdt_245m_122m_clk_status_START  (6)
#define BBPSCTRL_BBP_CLK1_STATUS_com_pdt_245m_122m_clk_status_END    (6)
#define BBPSCTRL_BBP_CLK1_STATUS_com_pdf_245m_122m_clk_status_START  (7)
#define BBPSCTRL_BBP_CLK1_STATUS_com_pdf_245m_122m_clk_status_END    (7)
#define BBPSCTRL_BBP_CLK1_STATUS_com_wtc_61m_clk_status_START        (8)
#define BBPSCTRL_BBP_CLK1_STATUS_com_wtc_61m_clk_status_END          (8)
#define BBPSCTRL_BBP_CLK1_STATUS_com_lte_245m_clk_status_START       (9)
#define BBPSCTRL_BBP_CLK1_STATUS_com_lte_245m_clk_status_END         (9)
#define BBPSCTRL_BBP_CLK1_STATUS_com_wc_abb_122m_clk_status_START    (10)
#define BBPSCTRL_BBP_CLK1_STATUS_com_wc_abb_122m_clk_status_END      (10)
#define BBPSCTRL_BBP_CLK1_STATUS_com_wc_abb_61m_clk_status_START     (11)
#define BBPSCTRL_BBP_CLK1_STATUS_com_wc_abb_61m_clk_status_END       (11)
#define BBPSCTRL_BBP_CLK1_STATUS_com_uc2_61m_clk_status_START        (12)
#define BBPSCTRL_BBP_CLK1_STATUS_com_uc2_61m_clk_status_END          (12)
#define BBPSCTRL_BBP_CLK1_STATUS_bbc_uc2_122m_clk_status_START       (13)
#define BBPSCTRL_BBP_CLK1_STATUS_bbc_uc2_122m_clk_status_END         (13)
#define BBPSCTRL_BBP_CLK1_STATUS_com_uc2_245m_clk_status_START       (14)
#define BBPSCTRL_BBP_CLK1_STATUS_com_uc2_245m_clk_status_END         (14)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_SCTRL6_SET_UNION
 �ṹ˵��  : BBP_SCTRL6_SET �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBPϵͳ������6��λ(UC2_CLK_EN)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctrl6_set_reg;
    struct
    {
        unsigned int  clk_61m_r99w2_en      : 1;  /* bit[0]   : UC2��Wģ61Mʱ��ʹ�ܣ�dallas����Ҫʹ��
                                                                д1��λ��д0��Ч�� */
        unsigned int  clk_122m_r99w2_en     : 1;  /* bit[1]   : UC2��Wģ122Mʱ��ʹ�ܣ�dallas����Ҫʹ��
                                                                д1��λ��д0��Ч�� */
        unsigned int  clk_122m_cbbp2_en     : 1;  /* bit[2]   : UC2��Cģ122Mʱ��ʹ��
                                                                д1��λ��д0��Ч�� */
        unsigned int  clk_122m_wc2_en       : 1;  /* bit[3]   : UC2��WCģ����122Mʱ��ʹ��
                                                                д1��λ��д0��Ч�� */
        unsigned int  clk_122m_wc2_turbo_en : 1;  /* bit[4]   : UC2��WCģ����122Mʱ��ʹ��
                                                                д1��λ��д0��Ч�� */
        unsigned int  clk_245m_wc2_turbo_en : 1;  /* bit[5]   : UC2��WCģ����245Mʱ��ʹ��
                                                                д1��λ��д0��Ч�� */
        unsigned int  clk_19m_uc2_en        : 1;  /* bit[6]   : UC2��TCXOʱ��ʹ��
                                                                д1��λ��д0��Ч�� */
        unsigned int  reserved              : 25; /* bit[7-31]: ������ */
    } reg;
} BBPSCTRL_BBP_SCTRL6_SET_UNION;
#define BBPSCTRL_BBP_SCTRL6_SET_clk_61m_r99w2_en_START       (0)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_61m_r99w2_en_END         (0)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_122m_r99w2_en_START      (1)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_122m_r99w2_en_END        (1)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_122m_cbbp2_en_START      (2)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_122m_cbbp2_en_END        (2)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_122m_wc2_en_START        (3)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_122m_wc2_en_END          (3)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_122m_wc2_turbo_en_START  (4)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_122m_wc2_turbo_en_END    (4)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_245m_wc2_turbo_en_START  (5)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_245m_wc2_turbo_en_END    (5)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_19m_uc2_en_START         (6)
#define BBPSCTRL_BBP_SCTRL6_SET_clk_19m_uc2_en_END           (6)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_SCTRL6_CLR_UNION
 �ṹ˵��  : BBP_SCTRL6_CLR �Ĵ����ṹ���塣��ַƫ����:0x0064����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBPϵͳ������6����(UC2_CLK_DIS)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctrl6_clr_reg;
    struct
    {
        unsigned int  clk_61m_r99w2_dis      : 1;  /* bit[0]   : UC2��Wģ61Mʱ�ӹر�
                                                                 д1�رգ�д0��Ч�� */
        unsigned int  clk_122m_r99w2_dis     : 1;  /* bit[1]   : UC2��Wģ122Mʱ�ӹر�
                                                                 д1�رգ�д0��Ч�� */
        unsigned int  clk_122m_cbbp2_dis     : 1;  /* bit[2]   : UC2��Cģ122Mʱ�ӹر�
                                                                 д1�رգ�д0��Ч�� */
        unsigned int  clk_122m_wc2_dis       : 1;  /* bit[3]   : UC2��WCģ����122Mʱ�ӹر�
                                                                 д1�رգ�д0��Ч�� */
        unsigned int  clk_122m_wc2_turbo_dis : 1;  /* bit[4]   : UC2��WCģ����122Mʱ�ӹر�
                                                                 д1�رգ�д0��Ч�� */
        unsigned int  clk_245m_wc2_turbo_dis : 1;  /* bit[5]   : UC2��WCģ����245Mʱ�ӹر�
                                                                 д1�رգ�д0��Ч�� */
        unsigned int  clk_19m_uc2_dis        : 1;  /* bit[6]   : UC2��TCXOʱ�ӹر�
                                                                 д1�رգ�д0��Ч�� */
        unsigned int  reserved               : 25; /* bit[7-31]: ������ */
    } reg;
} BBPSCTRL_BBP_SCTRL6_CLR_UNION;
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_61m_r99w2_dis_START       (0)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_61m_r99w2_dis_END         (0)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_122m_r99w2_dis_START      (1)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_122m_r99w2_dis_END        (1)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_122m_cbbp2_dis_START      (2)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_122m_cbbp2_dis_END        (2)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_122m_wc2_dis_START        (3)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_122m_wc2_dis_END          (3)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_122m_wc2_turbo_dis_START  (4)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_122m_wc2_turbo_dis_END    (4)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_245m_wc2_turbo_dis_START  (5)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_245m_wc2_turbo_dis_END    (5)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_19m_uc2_dis_START         (6)
#define BBPSCTRL_BBP_SCTRL6_CLR_clk_19m_uc2_dis_END           (6)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_SCTRL6_STSTUS_UNION
 �ṹ˵��  : BBP_SCTRL6_STSTUS �Ĵ����ṹ���塣��ַƫ����:0x0068����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBPϵͳ������6״̬(UC2_CLK_STATUS)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctrl6_ststus_reg;
    struct
    {
        unsigned int  clk_61m_r99w2_status      : 1;  /* bit[0]   : UC2��Wģ61Mʱ��״̬
                                                                    1��ʱ��ʹ��
                                                                    0��ʱ�ӹر� */
        unsigned int  clk_122m_r99w2_status     : 1;  /* bit[1]   : UC2��Wģ122Mʱ��״̬
                                                                    1��ʱ��ʹ��
                                                                    0��ʱ�ӹر� */
        unsigned int  clk_122m_cbbp2_status     : 1;  /* bit[2]   : UC2��Cģ122Mʱ��״̬
                                                                    1��ʱ��ʹ��
                                                                    0��ʱ�ӹر� */
        unsigned int  clk_122m_wc2_status       : 1;  /* bit[3]   : UC2��WCģ����122Mʱ��״̬
                                                                    1��ʱ��ʹ��
                                                                    0��ʱ�ӹر� */
        unsigned int  clk_122m_wc2_turbo_status : 1;  /* bit[4]   : UC2��WCģ����122Mʱ��״̬
                                                                    1��ʱ��ʹ��
                                                                    0��ʱ�ӹر� */
        unsigned int  clk_245m_wc2_turbo_status : 1;  /* bit[5]   : UC2��WCģ����245Mʱ��״̬
                                                                    1��ʱ��ʹ��
                                                                    0��ʱ�ӹر� */
        unsigned int  clk_19m_uc2_status        : 1;  /* bit[6]   : UC2��TCXOʱ��״̬
                                                                    1��ʱ��ʹ��
                                                                    0��ʱ�ӹر� */
        unsigned int  reserved                  : 25; /* bit[7-31]: ������ */
    } reg;
} BBPSCTRL_BBP_SCTRL6_STSTUS_UNION;
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_61m_r99w2_status_START       (0)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_61m_r99w2_status_END         (0)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_122m_r99w2_status_START      (1)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_122m_r99w2_status_END        (1)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_122m_cbbp2_status_START      (2)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_122m_cbbp2_status_END        (2)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_122m_wc2_status_START        (3)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_122m_wc2_status_END          (3)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_122m_wc2_turbo_status_START  (4)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_122m_wc2_turbo_status_END    (4)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_245m_wc2_turbo_status_START  (5)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_245m_wc2_turbo_status_END    (5)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_19m_uc2_status_START         (6)
#define BBPSCTRL_BBP_SCTRL6_STSTUS_clk_19m_uc2_status_END           (6)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_SCTRL7_SET_UNION
 �ṹ˵��  : BBP_SCTRL7_SET �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBPϵͳ������7��λ(UC2_RST_REQ)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctrl7_set_reg;
    struct
    {
        unsigned int  rst_61m_r99w2_req      : 1;  /* bit[0]   : UC2��Wģ61M��λ����
                                                                 д1��λ��д0��Ч�� */
        unsigned int  rst_122m_r99w2_req     : 1;  /* bit[1]   : UC2��Wģ122M��λ����
                                                                 д1��λ��д0��Ч�� */
        unsigned int  rst_122m_cbbp2_req     : 1;  /* bit[2]   : UC2��Cģ122M��λ����
                                                                 д1��λ��д0��Ч�� */
        unsigned int  rst_122m_wc2_req       : 1;  /* bit[3]   : UC2��WCģ����122M��λ����
                                                                 д1��λ��д0��Ч�� */
        unsigned int  rst_122m_wc2_turbo_req : 1;  /* bit[4]   : UC2��WCģ����122M��λ����
                                                                 д1��λ��д0��Ч�� */
        unsigned int  rst_245m_wc2_turbo_req : 1;  /* bit[5]   : UC2��WCģ����245M��λ����
                                                                 д1��λ��д0��Ч�� */
        unsigned int  rst_19m_uc2_req        : 1;  /* bit[6]   : UC2��TCXO��λ����
                                                                 д1��λ��д0��Ч�� */
        unsigned int  rst_32k_uc2_req        : 1;  /* bit[7]   : UC2��32K��λ����
                                                                 д1��λ��д0��Ч�� */
        unsigned int  reserved               : 24; /* bit[8-31]: ������ */
    } reg;
} BBPSCTRL_BBP_SCTRL7_SET_UNION;
#define BBPSCTRL_BBP_SCTRL7_SET_rst_61m_r99w2_req_START       (0)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_61m_r99w2_req_END         (0)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_122m_r99w2_req_START      (1)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_122m_r99w2_req_END        (1)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_122m_cbbp2_req_START      (2)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_122m_cbbp2_req_END        (2)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_122m_wc2_req_START        (3)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_122m_wc2_req_END          (3)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_122m_wc2_turbo_req_START  (4)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_122m_wc2_turbo_req_END    (4)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_245m_wc2_turbo_req_START  (5)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_245m_wc2_turbo_req_END    (5)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_19m_uc2_req_START         (6)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_19m_uc2_req_END           (6)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_32k_uc2_req_START         (7)
#define BBPSCTRL_BBP_SCTRL7_SET_rst_32k_uc2_req_END           (7)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_SCTRL7_CLR_UNION
 �ṹ˵��  : BBP_SCTRL7_CLR �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBPϵͳ������7����(UC2_RST_CLR)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctrl7_clr_reg;
    struct
    {
        unsigned int  rst_61m_r99w2_clr      : 1;  /* bit[0]   : UC2��Wģ61M��λ�����
                                                                 д1�����λ��д0��Ч�� */
        unsigned int  rst_122m_r99w2_clr     : 1;  /* bit[1]   : UC2��Wģ122M��λ�����
                                                                 д1�����λ��д0��Ч�� */
        unsigned int  rst_122m_cbbp2_clr     : 1;  /* bit[2]   : UC2��Cģ122M��λ�����
                                                                 д1�����λ��д0��Ч�� */
        unsigned int  rst_122m_wc2_clr       : 1;  /* bit[3]   : UC2��WCģ����122M��λ�����
                                                                 д1�����λ��д0��Ч�� */
        unsigned int  rst_122m_wc2_turbo_clr : 1;  /* bit[4]   : UC2��WCģ����122M��λ�����
                                                                 д1�����λ��д0��Ч�� */
        unsigned int  rst_245m_wc2_turbo_clr : 1;  /* bit[5]   : UC2��WCģ����245M��λ�����
                                                                 д1�����λ��д0��Ч�� */
        unsigned int  rst_19m_uc2_clr        : 1;  /* bit[6]   : UC2��TCXO��λ�����
                                                                 д1�����λ��д0��Ч�� */
        unsigned int  rst_32k_uc2_clr        : 1;  /* bit[7]   : UC2��32K��λ�����
                                                                 д1�����λ��д0��Ч�� */
        unsigned int  reserved               : 24; /* bit[8-31]: ������ */
    } reg;
} BBPSCTRL_BBP_SCTRL7_CLR_UNION;
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_61m_r99w2_clr_START       (0)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_61m_r99w2_clr_END         (0)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_122m_r99w2_clr_START      (1)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_122m_r99w2_clr_END        (1)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_122m_cbbp2_clr_START      (2)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_122m_cbbp2_clr_END        (2)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_122m_wc2_clr_START        (3)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_122m_wc2_clr_END          (3)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_122m_wc2_turbo_clr_START  (4)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_122m_wc2_turbo_clr_END    (4)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_245m_wc2_turbo_clr_START  (5)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_245m_wc2_turbo_clr_END    (5)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_19m_uc2_clr_START         (6)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_19m_uc2_clr_END           (6)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_32k_uc2_clr_START         (7)
#define BBPSCTRL_BBP_SCTRL7_CLR_rst_32k_uc2_clr_END           (7)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_SCTRL7_STSTUS_UNION
 �ṹ˵��  : BBP_SCTRL7_STSTUS �Ĵ����ṹ���塣��ַƫ����:0x0078����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: BBPϵͳ������7״̬(UC2_RST_STATUS)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctrl7_ststus_reg;
    struct
    {
        unsigned int  rst_61m_r99w2_status      : 1;  /* bit[0]   : UC2��Wģ61M��λ״̬��
                                                                    1����λ��
                                                                    0�������λ�� */
        unsigned int  rst_122m_r99w2_status     : 1;  /* bit[1]   : UC2��Wģ122M��λ״̬��
                                                                    1����λ��
                                                                    0�������λ�� */
        unsigned int  rst_122m_cbbp2_status     : 1;  /* bit[2]   : UC2��Cģ122M��λ״̬��
                                                                    1����λ��
                                                                    0�������λ�� */
        unsigned int  rst_122m_wc2_status       : 1;  /* bit[3]   : UC2��WCģ����122M��λ״̬��
                                                                    1����λ��
                                                                    0�������λ�� */
        unsigned int  rst_122m_wc2_turbo_status : 1;  /* bit[4]   : UC2��WCģ����122M��λ״̬��
                                                                    1����λ��
                                                                    0�������λ�� */
        unsigned int  rst_245m_wc2_turbo_status : 1;  /* bit[5]   : UC2��WCģ����245M��λ״̬��
                                                                    1����λ��
                                                                    0�������λ�� */
        unsigned int  rst_19m_uc2_status        : 1;  /* bit[6]   : UC2��TCXO��λ״̬��
                                                                    1����λ��
                                                                    0�������λ�� */
        unsigned int  rst_32k_uc2_status        : 1;  /* bit[7]   : UC2��32K��λ״̬��
                                                                    1����λ��
                                                                    0�������λ�� */
        unsigned int  reserved                  : 24; /* bit[8-31]: ������ */
    } reg;
} BBPSCTRL_BBP_SCTRL7_STSTUS_UNION;
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_61m_r99w2_status_START       (0)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_61m_r99w2_status_END         (0)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_122m_r99w2_status_START      (1)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_122m_r99w2_status_END        (1)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_122m_cbbp2_status_START      (2)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_122m_cbbp2_status_END        (2)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_122m_wc2_status_START        (3)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_122m_wc2_status_END          (3)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_122m_wc2_turbo_status_START  (4)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_122m_wc2_turbo_status_END    (4)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_245m_wc2_turbo_status_START  (5)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_245m_wc2_turbo_status_END    (5)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_19m_uc2_status_START         (6)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_19m_uc2_status_END           (6)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_32k_uc2_status_START         (7)
#define BBPSCTRL_BBP_SCTRL7_STSTUS_rst_32k_uc2_status_END           (7)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_LTE_PD_CLK_EN_UNION
 �ṹ˵��  : LTE_PD_CLK_EN �Ĵ����ṹ���塣��ַƫ����:0x0080����ֵ:0x00000000�����:32
 �Ĵ���˵��: LTE��Դ��ʱ��ʹ��
*****************************************************************************/
typedef union
{
    unsigned int      lte_pd_clk_en_reg;
    struct
    {
        unsigned int  lte_sys_clk_en        : 1;  /* bit[0]    : ��������ʹ�á� */
        unsigned int  lte_slp_clk_en        : 1;  /* bit[1]    : ��������ʹ�á� */
        unsigned int  lte_axim_clk_en       : 1;  /* bit[2]    : ��������ʹ�á� */
        unsigned int  lte_pdt_clk_en        : 1;  /* bit[3]    :  */
        unsigned int  lte_rfin_clk_en       : 1;  /* bit[4]    :  */
        unsigned int  lte_fpu_clk_en        : 1;  /* bit[5]    :  */
        unsigned int  lte_ul_clk_en         : 1;  /* bit[6]    :  */
        unsigned int  lte_ul_clk_x2_en      : 1;  /* bit[7]    :  */
        unsigned int  lte_pdu_clk_en        : 1;  /* bit[8]    :  */
        unsigned int  lte_cqi_clk_en        : 1;  /* bit[9]    :  */
        unsigned int  lte_pdf_clk_en        : 1;  /* bit[10]   :  */
        unsigned int  lte_pb_clk_en         : 1;  /* bit[11]   :  */
        unsigned int  lte_vdl_clk_en        : 1;  /* bit[12]   :  */
        unsigned int  lte_tdl_ch0_clk_en    : 1;  /* bit[13]   :  */
        unsigned int  lte_tdl_ch0_2x_clk_en : 1;  /* bit[14]   : ��������ʹ�á� */
        unsigned int  lte_tdl_ch1_clk_en    : 1;  /* bit[15]   : ��������ʹ�á� */
        unsigned int  lte_abb0_rx_clk_en    : 1;  /* bit[16]   : ��������ʹ�á� */
        unsigned int  lte_abb1_rx_clk_en    : 1;  /* bit[17]   : ��������ʹ�á� */
        unsigned int  lte_abb2_rx_clk_en    : 1;  /* bit[18]   : ��������ʹ�á� */
        unsigned int  lte_abb3_rx_clk_en    : 1;  /* bit[19]   : ��������ʹ�á� */
        unsigned int  lte_abb0_tx_clk_en    : 1;  /* bit[20]   :  */
        unsigned int  lte_abb1_tx_clk_en    : 1;  /* bit[21]   :  */
        unsigned int  lte_int_clk_en        : 1;  /* bit[22]   :  */
        unsigned int  uart_clk_en           : 1;  /* bit[23]   :  */
        unsigned int  reserved              : 8;  /* bit[24-31]: ������ */
    } reg;
} BBPSCTRL_LTE_PD_CLK_EN_UNION;
#define BBPSCTRL_LTE_PD_CLK_EN_lte_sys_clk_en_START         (0)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_sys_clk_en_END           (0)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_slp_clk_en_START         (1)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_slp_clk_en_END           (1)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_axim_clk_en_START        (2)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_axim_clk_en_END          (2)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_pdt_clk_en_START         (3)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_pdt_clk_en_END           (3)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_rfin_clk_en_START        (4)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_rfin_clk_en_END          (4)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_fpu_clk_en_START         (5)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_fpu_clk_en_END           (5)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_ul_clk_en_START          (6)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_ul_clk_en_END            (6)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_ul_clk_x2_en_START       (7)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_ul_clk_x2_en_END         (7)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_pdu_clk_en_START         (8)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_pdu_clk_en_END           (8)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_cqi_clk_en_START         (9)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_cqi_clk_en_END           (9)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_pdf_clk_en_START         (10)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_pdf_clk_en_END           (10)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_pb_clk_en_START          (11)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_pb_clk_en_END            (11)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_vdl_clk_en_START         (12)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_vdl_clk_en_END           (12)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_tdl_ch0_clk_en_START     (13)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_tdl_ch0_clk_en_END       (13)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_tdl_ch0_2x_clk_en_START  (14)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_tdl_ch0_2x_clk_en_END    (14)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_tdl_ch1_clk_en_START     (15)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_tdl_ch1_clk_en_END       (15)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb0_rx_clk_en_START     (16)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb0_rx_clk_en_END       (16)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb1_rx_clk_en_START     (17)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb1_rx_clk_en_END       (17)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb2_rx_clk_en_START     (18)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb2_rx_clk_en_END       (18)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb3_rx_clk_en_START     (19)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb3_rx_clk_en_END       (19)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb0_tx_clk_en_START     (20)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb0_tx_clk_en_END       (20)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb1_tx_clk_en_START     (21)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_abb1_tx_clk_en_END       (21)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_int_clk_en_START         (22)
#define BBPSCTRL_LTE_PD_CLK_EN_lte_int_clk_en_END           (22)
#define BBPSCTRL_LTE_PD_CLK_EN_uart_clk_en_START            (23)
#define BBPSCTRL_LTE_PD_CLK_EN_uart_clk_en_END              (23)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_LTE_PD_CLK_DIS_UNION
 �ṹ˵��  : LTE_PD_CLK_DIS �Ĵ����ṹ���塣��ַƫ����:0x0084����ֵ:0x00000000�����:32
 �Ĵ���˵��: LTE��Դ��ʱ�ӹر�
*****************************************************************************/
typedef union
{
    unsigned int      lte_pd_clk_dis_reg;
    struct
    {
        unsigned int  lte_sys_clk_dis        : 1;  /* bit[0]    :  */
        unsigned int  lte_slp_clk_dis        : 1;  /* bit[1]    :  */
        unsigned int  lte_axim_clk_dis       : 1;  /* bit[2]    :  */
        unsigned int  lte_pdt_clk_dis        : 1;  /* bit[3]    :  */
        unsigned int  lte_rfin_clk_dis       : 1;  /* bit[4]    :  */
        unsigned int  lte_fpu_clk_dis        : 1;  /* bit[5]    :  */
        unsigned int  lte_ul_clk_dis         : 1;  /* bit[6]    :  */
        unsigned int  lte_ul_clk_x2_dis      : 1;  /* bit[7]    :  */
        unsigned int  lte_pdu_clk_dis        : 1;  /* bit[8]    :  */
        unsigned int  lte_cqi_clk_dis        : 1;  /* bit[9]    :  */
        unsigned int  lte_pdf_clk_dis        : 1;  /* bit[10]   :  */
        unsigned int  lte_pb_clk_dis         : 1;  /* bit[11]   :  */
        unsigned int  lte_vdl_clk_dis        : 1;  /* bit[12]   :  */
        unsigned int  lte_tdl_ch0_clk_dis    : 1;  /* bit[13]   :  */
        unsigned int  lte_tdl_ch0_2x_clk_dis : 1;  /* bit[14]   :  */
        unsigned int  lte_tdl_ch1_clk_dis    : 1;  /* bit[15]   :  */
        unsigned int  lte_abb0_rx_clk_dis    : 1;  /* bit[16]   :  */
        unsigned int  lte_abb1_rx_clk_dis    : 1;  /* bit[17]   :  */
        unsigned int  lte_abb2_rx_clk_dis    : 1;  /* bit[18]   :  */
        unsigned int  lte_abb3_rx_clk_dis    : 1;  /* bit[19]   :  */
        unsigned int  lte_abb0_tx_clk_dis    : 1;  /* bit[20]   :  */
        unsigned int  lte_abb1_tx_clk_dis    : 1;  /* bit[21]   :  */
        unsigned int  lte_int_clk_dis        : 1;  /* bit[22]   :  */
        unsigned int  uart_clk_dis           : 1;  /* bit[23]   :  */
        unsigned int  reserved               : 8;  /* bit[24-31]: ������ */
    } reg;
} BBPSCTRL_LTE_PD_CLK_DIS_UNION;
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_sys_clk_dis_START         (0)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_sys_clk_dis_END           (0)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_slp_clk_dis_START         (1)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_slp_clk_dis_END           (1)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_axim_clk_dis_START        (2)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_axim_clk_dis_END          (2)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_pdt_clk_dis_START         (3)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_pdt_clk_dis_END           (3)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_rfin_clk_dis_START        (4)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_rfin_clk_dis_END          (4)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_fpu_clk_dis_START         (5)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_fpu_clk_dis_END           (5)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_ul_clk_dis_START          (6)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_ul_clk_dis_END            (6)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_ul_clk_x2_dis_START       (7)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_ul_clk_x2_dis_END         (7)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_pdu_clk_dis_START         (8)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_pdu_clk_dis_END           (8)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_cqi_clk_dis_START         (9)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_cqi_clk_dis_END           (9)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_pdf_clk_dis_START         (10)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_pdf_clk_dis_END           (10)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_pb_clk_dis_START          (11)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_pb_clk_dis_END            (11)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_vdl_clk_dis_START         (12)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_vdl_clk_dis_END           (12)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_tdl_ch0_clk_dis_START     (13)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_tdl_ch0_clk_dis_END       (13)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_tdl_ch0_2x_clk_dis_START  (14)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_tdl_ch0_2x_clk_dis_END    (14)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_tdl_ch1_clk_dis_START     (15)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_tdl_ch1_clk_dis_END       (15)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb0_rx_clk_dis_START     (16)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb0_rx_clk_dis_END       (16)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb1_rx_clk_dis_START     (17)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb1_rx_clk_dis_END       (17)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb2_rx_clk_dis_START     (18)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb2_rx_clk_dis_END       (18)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb3_rx_clk_dis_START     (19)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb3_rx_clk_dis_END       (19)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb0_tx_clk_dis_START     (20)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb0_tx_clk_dis_END       (20)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb1_tx_clk_dis_START     (21)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_abb1_tx_clk_dis_END       (21)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_int_clk_dis_START         (22)
#define BBPSCTRL_LTE_PD_CLK_DIS_lte_int_clk_dis_END           (22)
#define BBPSCTRL_LTE_PD_CLK_DIS_uart_clk_dis_START            (23)
#define BBPSCTRL_LTE_PD_CLK_DIS_uart_clk_dis_END              (23)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_LTE_PD_CLK_STSTUS_UNION
 �ṹ˵��  : LTE_PD_CLK_STSTUS �Ĵ����ṹ���塣��ַƫ����:0x0088����ֵ:0x00000000�����:32
 �Ĵ���˵��: LTE��Դ��ʱ���ſ�״̬
*****************************************************************************/
typedef union
{
    unsigned int      lte_pd_clk_ststus_reg;
    struct
    {
        unsigned int  lte_sys_clk_status        : 1;  /* bit[0]    :  */
        unsigned int  lte_slp_clk_status        : 1;  /* bit[1]    :  */
        unsigned int  lte_axim_clk_status       : 1;  /* bit[2]    :  */
        unsigned int  lte_pdt_clk_status        : 1;  /* bit[3]    :  */
        unsigned int  lte_rfin_clk_status       : 1;  /* bit[4]    :  */
        unsigned int  lte_fpu_clk_status        : 1;  /* bit[5]    :  */
        unsigned int  lte_ul_clk_status         : 1;  /* bit[6]    :  */
        unsigned int  lte_ul_clk_x2_status      : 1;  /* bit[7]    :  */
        unsigned int  lte_pdu_clk_status        : 1;  /* bit[8]    :  */
        unsigned int  lte_cqi_clk_status        : 1;  /* bit[9]    :  */
        unsigned int  lte_pdf_clk_status        : 1;  /* bit[10]   :  */
        unsigned int  lte_pb_clk_status         : 1;  /* bit[11]   :  */
        unsigned int  lte_vdl_clk_status        : 1;  /* bit[12]   :  */
        unsigned int  lte_tdl_ch0_clk_status    : 1;  /* bit[13]   :  */
        unsigned int  lte_tdl_ch0_2x_clk_status : 1;  /* bit[14]   :  */
        unsigned int  lte_tdl_ch1_clk_status    : 1;  /* bit[15]   :  */
        unsigned int  lte_abb0_rx_clk_status    : 1;  /* bit[16]   :  */
        unsigned int  lte_abb1_rx_clk_status    : 1;  /* bit[17]   :  */
        unsigned int  lte_abb2_rx_clk_status    : 1;  /* bit[18]   :  */
        unsigned int  lte_abb3_rx_clk_status    : 1;  /* bit[19]   :  */
        unsigned int  lte_abb0_tx_clk_status    : 1;  /* bit[20]   :  */
        unsigned int  lte_abb1_tx_clk_status    : 1;  /* bit[21]   :  */
        unsigned int  lte_int_clk_status        : 1;  /* bit[22]   :  */
        unsigned int  uart_clk_status           : 1;  /* bit[23]   :  */
        unsigned int  reserved                  : 8;  /* bit[24-31]: ������ */
    } reg;
} BBPSCTRL_LTE_PD_CLK_STSTUS_UNION;
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_sys_clk_status_START         (0)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_sys_clk_status_END           (0)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_slp_clk_status_START         (1)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_slp_clk_status_END           (1)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_axim_clk_status_START        (2)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_axim_clk_status_END          (2)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_pdt_clk_status_START         (3)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_pdt_clk_status_END           (3)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_rfin_clk_status_START        (4)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_rfin_clk_status_END          (4)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_fpu_clk_status_START         (5)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_fpu_clk_status_END           (5)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_ul_clk_status_START          (6)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_ul_clk_status_END            (6)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_ul_clk_x2_status_START       (7)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_ul_clk_x2_status_END         (7)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_pdu_clk_status_START         (8)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_pdu_clk_status_END           (8)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_cqi_clk_status_START         (9)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_cqi_clk_status_END           (9)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_pdf_clk_status_START         (10)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_pdf_clk_status_END           (10)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_pb_clk_status_START          (11)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_pb_clk_status_END            (11)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_vdl_clk_status_START         (12)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_vdl_clk_status_END           (12)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_tdl_ch0_clk_status_START     (13)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_tdl_ch0_clk_status_END       (13)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_tdl_ch0_2x_clk_status_START  (14)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_tdl_ch0_2x_clk_status_END    (14)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_tdl_ch1_clk_status_START     (15)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_tdl_ch1_clk_status_END       (15)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb0_rx_clk_status_START     (16)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb0_rx_clk_status_END       (16)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb1_rx_clk_status_START     (17)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb1_rx_clk_status_END       (17)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb2_rx_clk_status_START     (18)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb2_rx_clk_status_END       (18)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb3_rx_clk_status_START     (19)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb3_rx_clk_status_END       (19)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb0_tx_clk_status_START     (20)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb0_tx_clk_status_END       (20)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb1_tx_clk_status_START     (21)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_abb1_tx_clk_status_END       (21)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_int_clk_status_START         (22)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_lte_int_clk_status_END           (22)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_uart_clk_status_START            (23)
#define BBPSCTRL_LTE_PD_CLK_STSTUS_uart_clk_status_END              (23)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_LTE_PD_SRST_REQ_UNION
 �ṹ˵��  : LTE_PD_SRST_REQ �Ĵ����ṹ���塣��ַƫ����:0x0090����ֵ:0x00000000�����:32
 �Ĵ���˵��: LTE��Դ��λ����ʹ��
*****************************************************************************/
typedef union
{
    unsigned int      lte_pd_srst_req_reg;
    struct
    {
        unsigned int  reserved_0           : 1;  /* bit[0]    :  */
        unsigned int  lte_slp_srst_req     : 1;  /* bit[1]    :  */
        unsigned int  lte_axim_srst_req    : 1;  /* bit[2]    :  */
        unsigned int  lte_pdt_srst_req     : 1;  /* bit[3]    :  */
        unsigned int  lte_rfin_srst_req    : 1;  /* bit[4]    :  */
        unsigned int  lte_fpu_srst_req     : 1;  /* bit[5]    :  */
        unsigned int  lte_ul_srst_req      : 1;  /* bit[6]    :  */
        unsigned int  reserved_1           : 1;  /* bit[7]    :  */
        unsigned int  lte_pdu_srst_req     : 1;  /* bit[8]    :  */
        unsigned int  lte_cqi_srst_req     : 1;  /* bit[9]    :  */
        unsigned int  lte_pdf_srst_req     : 1;  /* bit[10]   :  */
        unsigned int  lte_pb_srst_req      : 1;  /* bit[11]   :  */
        unsigned int  lte_vdl_srst_req     : 1;  /* bit[12]   :  */
        unsigned int  lte_tdl_ch0_srst_req : 1;  /* bit[13]   :  */
        unsigned int  reserved_2           : 8;  /* bit[14-21]:  */
        unsigned int  lte_int_srst_req     : 1;  /* bit[22]   :  */
        unsigned int  uart_srst_req        : 1;  /* bit[23]   :  */
        unsigned int  reserved_3           : 8;  /* bit[24-31]: ������ */
    } reg;
} BBPSCTRL_LTE_PD_SRST_REQ_UNION;
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_slp_srst_req_START      (1)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_slp_srst_req_END        (1)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_axim_srst_req_START     (2)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_axim_srst_req_END       (2)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_pdt_srst_req_START      (3)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_pdt_srst_req_END        (3)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_rfin_srst_req_START     (4)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_rfin_srst_req_END       (4)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_fpu_srst_req_START      (5)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_fpu_srst_req_END        (5)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_ul_srst_req_START       (6)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_ul_srst_req_END         (6)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_pdu_srst_req_START      (8)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_pdu_srst_req_END        (8)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_cqi_srst_req_START      (9)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_cqi_srst_req_END        (9)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_pdf_srst_req_START      (10)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_pdf_srst_req_END        (10)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_pb_srst_req_START       (11)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_pb_srst_req_END         (11)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_vdl_srst_req_START      (12)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_vdl_srst_req_END        (12)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_tdl_ch0_srst_req_START  (13)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_tdl_ch0_srst_req_END    (13)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_int_srst_req_START      (22)
#define BBPSCTRL_LTE_PD_SRST_REQ_lte_int_srst_req_END        (22)
#define BBPSCTRL_LTE_PD_SRST_REQ_uart_srst_req_START         (23)
#define BBPSCTRL_LTE_PD_SRST_REQ_uart_srst_req_END           (23)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_LTE_PD_SRST_DIS_UNION
 �ṹ˵��  : LTE_PD_SRST_DIS �Ĵ����ṹ���塣��ַƫ����:0x0094����ֵ:0x00000000�����:32
 �Ĵ���˵��: LTE��Դ��λ�������
*****************************************************************************/
typedef union
{
    unsigned int      lte_pd_srst_dis_reg;
    struct
    {
        unsigned int  reserved_0              : 1;  /* bit[0]    :  */
        unsigned int  lte_slp_srst_dis        : 1;  /* bit[1]    :  */
        unsigned int  lte_axim_srst_dis       : 1;  /* bit[2]    :  */
        unsigned int  lte_pdt_srst_dis        : 1;  /* bit[3]    :  */
        unsigned int  lte_rfin_srst_dis       : 1;  /* bit[4]    :  */
        unsigned int  lte_fpu_srst_dis        : 1;  /* bit[5]    :  */
        unsigned int  lte_ul_srst_dis         : 1;  /* bit[6]    :  */
        unsigned int  reserved_1              : 1;  /* bit[7]    :  */
        unsigned int  lte_pdu_srst_dis        : 1;  /* bit[8]    :  */
        unsigned int  lte_cqi_srst_dis        : 1;  /* bit[9]    :  */
        unsigned int  lte_pdf_srst_dis        : 1;  /* bit[10]   :  */
        unsigned int  lte_pb_srst_dis         : 1;  /* bit[11]   :  */
        unsigned int  lte_vdl_srst_dis        : 1;  /* bit[12]   :  */
        unsigned int  lte_tdl_ch0_srst_dis    : 1;  /* bit[13]   :  */
        unsigned int  lte_tdl_ch0_2x_srst_dis : 1;  /* bit[14]   :  */
        unsigned int  lte_tdl_ch1_srst_dis    : 1;  /* bit[15]   :  */
        unsigned int  reserved_2              : 6;  /* bit[16-21]:  */
        unsigned int  lte_int_srst_dis        : 1;  /* bit[22]   :  */
        unsigned int  uart_srst_dis           : 1;  /* bit[23]   :  */
        unsigned int  reserved_3              : 8;  /* bit[24-31]: ������ */
    } reg;
} BBPSCTRL_LTE_PD_SRST_DIS_UNION;
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_slp_srst_dis_START         (1)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_slp_srst_dis_END           (1)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_axim_srst_dis_START        (2)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_axim_srst_dis_END          (2)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_pdt_srst_dis_START         (3)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_pdt_srst_dis_END           (3)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_rfin_srst_dis_START        (4)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_rfin_srst_dis_END          (4)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_fpu_srst_dis_START         (5)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_fpu_srst_dis_END           (5)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_ul_srst_dis_START          (6)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_ul_srst_dis_END            (6)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_pdu_srst_dis_START         (8)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_pdu_srst_dis_END           (8)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_cqi_srst_dis_START         (9)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_cqi_srst_dis_END           (9)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_pdf_srst_dis_START         (10)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_pdf_srst_dis_END           (10)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_pb_srst_dis_START          (11)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_pb_srst_dis_END            (11)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_vdl_srst_dis_START         (12)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_vdl_srst_dis_END           (12)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_tdl_ch0_srst_dis_START     (13)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_tdl_ch0_srst_dis_END       (13)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_tdl_ch0_2x_srst_dis_START  (14)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_tdl_ch0_2x_srst_dis_END    (14)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_tdl_ch1_srst_dis_START     (15)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_tdl_ch1_srst_dis_END       (15)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_int_srst_dis_START         (22)
#define BBPSCTRL_LTE_PD_SRST_DIS_lte_int_srst_dis_END           (22)
#define BBPSCTRL_LTE_PD_SRST_DIS_uart_srst_dis_START            (23)
#define BBPSCTRL_LTE_PD_SRST_DIS_uart_srst_dis_END              (23)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_LTE_PD_SRST_STSTUS_UNION
 �ṹ˵��  : LTE_PD_SRST_STSTUS �Ĵ����ṹ���塣��ַƫ����:0x0098����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: LTE��Դ��λ����״̬
*****************************************************************************/
typedef union
{
    unsigned int      lte_pd_srst_ststus_reg;
    struct
    {
        unsigned int  reserved_0                 : 1;  /* bit[0]    :  */
        unsigned int  lte_slp_srst_status        : 1;  /* bit[1]    :  */
        unsigned int  lte_axim_srst_status       : 1;  /* bit[2]    :  */
        unsigned int  lte_pdt_srst_status        : 1;  /* bit[3]    :  */
        unsigned int  lte_rfin_srst_status       : 1;  /* bit[4]    :  */
        unsigned int  lte_fpu_srst_status        : 1;  /* bit[5]    :  */
        unsigned int  lte_ul_srst_status         : 1;  /* bit[6]    :  */
        unsigned int  reserved_1                 : 1;  /* bit[7]    :  */
        unsigned int  lte_pdu_srst_status        : 1;  /* bit[8]    :  */
        unsigned int  lte_cqi_srst_status        : 1;  /* bit[9]    :  */
        unsigned int  lte_pdf_srst_status        : 1;  /* bit[10]   :  */
        unsigned int  lte_pb_srst_status         : 1;  /* bit[11]   :  */
        unsigned int  lte_vdl_srst_status        : 1;  /* bit[12]   :  */
        unsigned int  lte_tdl_ch0_srst_status    : 1;  /* bit[13]   :  */
        unsigned int  lte_tdl_ch0_2x_srst_status : 1;  /* bit[14]   :  */
        unsigned int  lte_tdl_ch1_srst_status    : 1;  /* bit[15]   :  */
        unsigned int  reserved_2                 : 6;  /* bit[16-21]:  */
        unsigned int  lte_int_srst_status        : 1;  /* bit[22]   :  */
        unsigned int  uart_srst_status           : 1;  /* bit[23]   :  */
        unsigned int  reserved_3                 : 8;  /* bit[24-31]: ������ */
    } reg;
} BBPSCTRL_LTE_PD_SRST_STSTUS_UNION;
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_slp_srst_status_START         (1)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_slp_srst_status_END           (1)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_axim_srst_status_START        (2)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_axim_srst_status_END          (2)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_pdt_srst_status_START         (3)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_pdt_srst_status_END           (3)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_rfin_srst_status_START        (4)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_rfin_srst_status_END          (4)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_fpu_srst_status_START         (5)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_fpu_srst_status_END           (5)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_ul_srst_status_START          (6)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_ul_srst_status_END            (6)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_pdu_srst_status_START         (8)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_pdu_srst_status_END           (8)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_cqi_srst_status_START         (9)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_cqi_srst_status_END           (9)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_pdf_srst_status_START         (10)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_pdf_srst_status_END           (10)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_pb_srst_status_START          (11)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_pb_srst_status_END            (11)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_vdl_srst_status_START         (12)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_vdl_srst_status_END           (12)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_tdl_ch0_srst_status_START     (13)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_tdl_ch0_srst_status_END       (13)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_tdl_ch0_2x_srst_status_START  (14)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_tdl_ch0_2x_srst_status_END    (14)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_tdl_ch1_srst_status_START     (15)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_tdl_ch1_srst_status_END       (15)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_int_srst_status_START         (22)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_lte_int_srst_status_END           (22)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_uart_srst_status_START            (23)
#define BBPSCTRL_LTE_PD_SRST_STSTUS_uart_srst_status_END              (23)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_WTC_PD_CLK_EN_UNION
 �ṹ˵��  : WTC_PD_CLK_EN �Ĵ����ṹ���塣��ַƫ����:0x00A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: WTC��Դ��ʱ��ʹ��
*****************************************************************************/
typedef union
{
    unsigned int      wtc_pd_clk_en_reg;
    struct
    {
        unsigned int  clk_61m_wbbp_top2_en  : 1;  /* bit[0]    :  */
        unsigned int  clk_122m_wbbp_top2_en : 1;  /* bit[1]    :  */
        unsigned int  clk_245m_wbbp_top2_en : 1;  /* bit[2]    :  */
        unsigned int  clk_122m_tw_en        : 1;  /* bit[3]    :  */
        unsigned int  clk_122m_twc_en       : 1;  /* bit[4]    :  */
        unsigned int  clk_122m_tds_en       : 1;  /* bit[5]    :  */
        unsigned int  clk_245m_tds_en       : 1;  /* bit[6]    :  */
        unsigned int  clk_245m_cbbp_en      : 1;  /* bit[7]    :  */
        unsigned int  clk_61m_wbbp_cs_en    : 1;  /* bit[8]    :  */
        unsigned int  clk_122m_wbbp_cs_en   : 1;  /* bit[9]    :  */
        unsigned int  clk_122m_cbbp_en      : 1;  /* bit[10]   :  */
        unsigned int  clk_122m_wc_en        : 1;  /* bit[11]   :  */
        unsigned int  clk_61m_tw_en         : 1;  /* bit[12]   :  */
        unsigned int  clk_245m_tw_en        : 1;  /* bit[13]   :  */
        unsigned int  clk_19m_cs_en         : 1;  /* bit[14]   :  */
        unsigned int  reserved              : 17; /* bit[15-31]: ������ */
    } reg;
} BBPSCTRL_WTC_PD_CLK_EN_UNION;
#define BBPSCTRL_WTC_PD_CLK_EN_clk_61m_wbbp_top2_en_START   (0)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_61m_wbbp_top2_en_END     (0)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_wbbp_top2_en_START  (1)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_wbbp_top2_en_END    (1)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_245m_wbbp_top2_en_START  (2)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_245m_wbbp_top2_en_END    (2)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_tw_en_START         (3)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_tw_en_END           (3)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_twc_en_START        (4)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_twc_en_END          (4)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_tds_en_START        (5)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_tds_en_END          (5)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_245m_tds_en_START        (6)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_245m_tds_en_END          (6)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_245m_cbbp_en_START       (7)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_245m_cbbp_en_END         (7)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_61m_wbbp_cs_en_START     (8)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_61m_wbbp_cs_en_END       (8)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_wbbp_cs_en_START    (9)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_wbbp_cs_en_END      (9)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_cbbp_en_START       (10)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_cbbp_en_END         (10)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_wc_en_START         (11)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_122m_wc_en_END           (11)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_61m_tw_en_START          (12)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_61m_tw_en_END            (12)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_245m_tw_en_START         (13)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_245m_tw_en_END           (13)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_19m_cs_en_START          (14)
#define BBPSCTRL_WTC_PD_CLK_EN_clk_19m_cs_en_END            (14)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_WTC_PD_CLK_DIS_UNION
 �ṹ˵��  : WTC_PD_CLK_DIS �Ĵ����ṹ���塣��ַƫ����:0x00A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: WTC��Դ��ʱ�ӹر�
*****************************************************************************/
typedef union
{
    unsigned int      wtc_pd_clk_dis_reg;
    struct
    {
        unsigned int  clk_61m_wbbp_top2_dis  : 1;  /* bit[0]    :  */
        unsigned int  clk_122m_wbbp_top2_dis : 1;  /* bit[1]    :  */
        unsigned int  clk_245m_wbbp_top2_dis : 1;  /* bit[2]    :  */
        unsigned int  clk_122m_tw_dis        : 1;  /* bit[3]    :  */
        unsigned int  clk_122m_twc_dis       : 1;  /* bit[4]    :  */
        unsigned int  clk_122m_tds_dis       : 1;  /* bit[5]    :  */
        unsigned int  clk_245m_tds_dis       : 1;  /* bit[6]    :  */
        unsigned int  clk_245m_cbbp_dis      : 1;  /* bit[7]    :  */
        unsigned int  clk_61m_wbbp_cs_dis    : 1;  /* bit[8]    :  */
        unsigned int  clk_122m_wbbp_cs_dis   : 1;  /* bit[9]    :  */
        unsigned int  clk_122m_cbbp_dis      : 1;  /* bit[10]   :  */
        unsigned int  clk_122m_wc_dis        : 1;  /* bit[11]   :  */
        unsigned int  clk_61m_tw_dis         : 1;  /* bit[12]   :  */
        unsigned int  clk_245m_tw_dis        : 1;  /* bit[13]   :  */
        unsigned int  clk_19m_cs_dis         : 1;  /* bit[14]   :  */
        unsigned int  reserved               : 17; /* bit[15-31]: ������ */
    } reg;
} BBPSCTRL_WTC_PD_CLK_DIS_UNION;
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_61m_wbbp_top2_dis_START   (0)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_61m_wbbp_top2_dis_END     (0)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_wbbp_top2_dis_START  (1)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_wbbp_top2_dis_END    (1)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_245m_wbbp_top2_dis_START  (2)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_245m_wbbp_top2_dis_END    (2)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_tw_dis_START         (3)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_tw_dis_END           (3)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_twc_dis_START        (4)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_twc_dis_END          (4)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_tds_dis_START        (5)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_tds_dis_END          (5)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_245m_tds_dis_START        (6)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_245m_tds_dis_END          (6)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_245m_cbbp_dis_START       (7)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_245m_cbbp_dis_END         (7)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_61m_wbbp_cs_dis_START     (8)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_61m_wbbp_cs_dis_END       (8)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_wbbp_cs_dis_START    (9)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_wbbp_cs_dis_END      (9)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_cbbp_dis_START       (10)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_cbbp_dis_END         (10)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_wc_dis_START         (11)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_122m_wc_dis_END           (11)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_61m_tw_dis_START          (12)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_61m_tw_dis_END            (12)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_245m_tw_dis_START         (13)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_245m_tw_dis_END           (13)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_19m_cs_dis_START          (14)
#define BBPSCTRL_WTC_PD_CLK_DIS_clk_19m_cs_dis_END            (14)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_WTC_PD_CLK_STSTUS_UNION
 �ṹ˵��  : WTC_PD_CLK_STSTUS �Ĵ����ṹ���塣��ַƫ����:0x00A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: WTC��Դ��ʱ���ſ�״̬
*****************************************************************************/
typedef union
{
    unsigned int      wtc_pd_clk_ststus_reg;
    struct
    {
        unsigned int  clk_61m_wbbp_top2_status  : 1;  /* bit[0]    :  */
        unsigned int  clk_122m_wbbp_top2_status : 1;  /* bit[1]    :  */
        unsigned int  clk_245m_wbbp_top2_status : 1;  /* bit[2]    :  */
        unsigned int  clk_122m_tw_status        : 1;  /* bit[3]    :  */
        unsigned int  clk_122m_twc_status       : 1;  /* bit[4]    :  */
        unsigned int  clk_122m_tds_status       : 1;  /* bit[5]    :  */
        unsigned int  clk_245m_tds_status       : 1;  /* bit[6]    :  */
        unsigned int  clk_245m_cbbp_status      : 1;  /* bit[7]    :  */
        unsigned int  clk_61m_wbbp_cs_status    : 1;  /* bit[8]    :  */
        unsigned int  clk_122m_wbbp_cs_status   : 1;  /* bit[9]    :  */
        unsigned int  clk_122m_cbbp_status      : 1;  /* bit[10]   :  */
        unsigned int  clk_122m_wc_status        : 1;  /* bit[11]   :  */
        unsigned int  clk_61m_tw_status         : 1;  /* bit[12]   :  */
        unsigned int  clk_245m_tw_status        : 1;  /* bit[13]   :  */
        unsigned int  clk_19m_cs_status         : 1;  /* bit[14]   :  */
        unsigned int  reserved                  : 17; /* bit[15-31]: ������ */
    } reg;
} BBPSCTRL_WTC_PD_CLK_STSTUS_UNION;
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_61m_wbbp_top2_status_START   (0)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_61m_wbbp_top2_status_END     (0)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_wbbp_top2_status_START  (1)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_wbbp_top2_status_END    (1)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_245m_wbbp_top2_status_START  (2)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_245m_wbbp_top2_status_END    (2)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_tw_status_START         (3)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_tw_status_END           (3)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_twc_status_START        (4)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_twc_status_END          (4)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_tds_status_START        (5)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_tds_status_END          (5)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_245m_tds_status_START        (6)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_245m_tds_status_END          (6)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_245m_cbbp_status_START       (7)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_245m_cbbp_status_END         (7)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_61m_wbbp_cs_status_START     (8)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_61m_wbbp_cs_status_END       (8)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_wbbp_cs_status_START    (9)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_wbbp_cs_status_END      (9)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_cbbp_status_START       (10)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_cbbp_status_END         (10)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_wc_status_START         (11)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_122m_wc_status_END           (11)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_61m_tw_status_START          (12)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_61m_tw_status_END            (12)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_245m_tw_status_START         (13)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_245m_tw_status_END           (13)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_19m_cs_status_START          (14)
#define BBPSCTRL_WTC_PD_CLK_STSTUS_clk_19m_cs_status_END            (14)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_WTC_PD_SRST_REQ_UNION
 �ṹ˵��  : WTC_PD_SRST_REQ �Ĵ����ṹ���塣��ַƫ����:0x00B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: WTC��Դ��λ����ʹ��
*****************************************************************************/
typedef union
{
    unsigned int      wtc_pd_srst_req_reg;
    struct
    {
        unsigned int  rst_61m_wbbp_top2_req  : 1;  /* bit[0]    :  */
        unsigned int  rst_122m_wbbp_top2_req : 1;  /* bit[1]    :  */
        unsigned int  rst_245m_wbbp_top2_req : 1;  /* bit[2]    :  */
        unsigned int  rst_122m_tw_req        : 1;  /* bit[3]    :  */
        unsigned int  rst_122m_twc_req       : 1;  /* bit[4]    :  */
        unsigned int  rst_122m_tds_req       : 1;  /* bit[5]    :  */
        unsigned int  rst_245m_tds_req       : 1;  /* bit[6]    :  */
        unsigned int  rst_245m_cbbp_req      : 1;  /* bit[7]    :  */
        unsigned int  rst_61m_wbbp_cs_req    : 1;  /* bit[8]    :  */
        unsigned int  rst_122m_wbbp_cs_req   : 1;  /* bit[9]    :  */
        unsigned int  rst_122m_cbbp_req      : 1;  /* bit[10]   :  */
        unsigned int  rst_122m_wc_req        : 1;  /* bit[11]   :  */
        unsigned int  rst_61m_tw_req         : 1;  /* bit[12]   :  */
        unsigned int  rst_245m_tw_req        : 1;  /* bit[13]   :  */
        unsigned int  rst_19m_cs_req         : 1;  /* bit[14]   :  */
        unsigned int  rst_32k_cs_req         : 1;  /* bit[15]   :  */
        unsigned int  reserved               : 16; /* bit[16-31]: ������ */
    } reg;
} BBPSCTRL_WTC_PD_SRST_REQ_UNION;
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_61m_wbbp_top2_req_START   (0)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_61m_wbbp_top2_req_END     (0)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_wbbp_top2_req_START  (1)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_wbbp_top2_req_END    (1)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_245m_wbbp_top2_req_START  (2)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_245m_wbbp_top2_req_END    (2)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_tw_req_START         (3)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_tw_req_END           (3)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_twc_req_START        (4)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_twc_req_END          (4)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_tds_req_START        (5)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_tds_req_END          (5)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_245m_tds_req_START        (6)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_245m_tds_req_END          (6)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_245m_cbbp_req_START       (7)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_245m_cbbp_req_END         (7)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_61m_wbbp_cs_req_START     (8)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_61m_wbbp_cs_req_END       (8)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_wbbp_cs_req_START    (9)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_wbbp_cs_req_END      (9)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_cbbp_req_START       (10)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_cbbp_req_END         (10)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_wc_req_START         (11)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_122m_wc_req_END           (11)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_61m_tw_req_START          (12)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_61m_tw_req_END            (12)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_245m_tw_req_START         (13)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_245m_tw_req_END           (13)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_19m_cs_req_START          (14)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_19m_cs_req_END            (14)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_32k_cs_req_START          (15)
#define BBPSCTRL_WTC_PD_SRST_REQ_rst_32k_cs_req_END            (15)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_WTC_PD_SRST_DIS_UNION
 �ṹ˵��  : WTC_PD_SRST_DIS �Ĵ����ṹ���塣��ַƫ����:0x00B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: WTC��Դ��λ�������
*****************************************************************************/
typedef union
{
    unsigned int      wtc_pd_srst_dis_reg;
    struct
    {
        unsigned int  rst_61m_wbbp_top2_dis  : 1;  /* bit[0]    :  */
        unsigned int  rst_122m_wbbp_top2_dis : 1;  /* bit[1]    :  */
        unsigned int  rst_245m_wbbp_top2_dis : 1;  /* bit[2]    :  */
        unsigned int  rst_122m_tw_dis        : 1;  /* bit[3]    :  */
        unsigned int  rst_122m_twc_dis       : 1;  /* bit[4]    :  */
        unsigned int  rst_122m_tds_dis       : 1;  /* bit[5]    :  */
        unsigned int  rst_245m_tds_dis       : 1;  /* bit[6]    :  */
        unsigned int  rst_245m_cbbp_dis      : 1;  /* bit[7]    :  */
        unsigned int  rst_61m_wbbp_cs_dis    : 1;  /* bit[8]    :  */
        unsigned int  rst_122m_wbbp_cs_dis   : 1;  /* bit[9]    :  */
        unsigned int  rst_122m_cbbp_dis      : 1;  /* bit[10]   :  */
        unsigned int  rst_122m_wc_dis        : 1;  /* bit[11]   :  */
        unsigned int  rst_61m_tw_dis         : 1;  /* bit[12]   :  */
        unsigned int  rst_245m_tw_dis        : 1;  /* bit[13]   :  */
        unsigned int  rst_19m_cs_dis         : 1;  /* bit[14]   :  */
        unsigned int  rst_32k_cs_dis         : 1;  /* bit[15]   :  */
        unsigned int  reserved               : 16; /* bit[16-31]: ������ */
    } reg;
} BBPSCTRL_WTC_PD_SRST_DIS_UNION;
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_61m_wbbp_top2_dis_START   (0)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_61m_wbbp_top2_dis_END     (0)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_wbbp_top2_dis_START  (1)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_wbbp_top2_dis_END    (1)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_245m_wbbp_top2_dis_START  (2)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_245m_wbbp_top2_dis_END    (2)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_tw_dis_START         (3)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_tw_dis_END           (3)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_twc_dis_START        (4)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_twc_dis_END          (4)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_tds_dis_START        (5)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_tds_dis_END          (5)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_245m_tds_dis_START        (6)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_245m_tds_dis_END          (6)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_245m_cbbp_dis_START       (7)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_245m_cbbp_dis_END         (7)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_61m_wbbp_cs_dis_START     (8)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_61m_wbbp_cs_dis_END       (8)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_wbbp_cs_dis_START    (9)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_wbbp_cs_dis_END      (9)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_cbbp_dis_START       (10)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_cbbp_dis_END         (10)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_wc_dis_START         (11)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_122m_wc_dis_END           (11)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_61m_tw_dis_START          (12)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_61m_tw_dis_END            (12)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_245m_tw_dis_START         (13)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_245m_tw_dis_END           (13)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_19m_cs_dis_START          (14)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_19m_cs_dis_END            (14)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_32k_cs_dis_START          (15)
#define BBPSCTRL_WTC_PD_SRST_DIS_rst_32k_cs_dis_END            (15)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_WTC_PD_SRST_STATUS_UNION
 �ṹ˵��  : WTC_PD_SRST_STATUS �Ĵ����ṹ���塣��ַƫ����:0x00B8����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: WTC��Դ��λ����״̬
*****************************************************************************/
typedef union
{
    unsigned int      wtc_pd_srst_status_reg;
    struct
    {
        unsigned int  rst_61m_wbbp_top2_status  : 1;  /* bit[0]    :  */
        unsigned int  rst_122m_wbbp_top2_status : 1;  /* bit[1]    :  */
        unsigned int  rst_245m_wbbp_top2_status : 1;  /* bit[2]    :  */
        unsigned int  rst_122m_tw_status        : 1;  /* bit[3]    :  */
        unsigned int  rst_122m_twc_status       : 1;  /* bit[4]    :  */
        unsigned int  rst_122m_tds_status       : 1;  /* bit[5]    :  */
        unsigned int  rst_245m_tds_status       : 1;  /* bit[6]    :  */
        unsigned int  rst_245m_cbbp_status      : 1;  /* bit[7]    :  */
        unsigned int  rst_61m_wbbp_cs_status    : 1;  /* bit[8]    :  */
        unsigned int  rst_122m_wbbp_cs_status   : 1;  /* bit[9]    :  */
        unsigned int  rst_122m_cbbp_status      : 1;  /* bit[10]   :  */
        unsigned int  rst_122m_wc_status        : 1;  /* bit[11]   :  */
        unsigned int  rst_61m_tw_status         : 1;  /* bit[12]   :  */
        unsigned int  rst_245m_tw_status        : 1;  /* bit[13]   :  */
        unsigned int  rst_19m_cs_status         : 1;  /* bit[14]   :  */
        unsigned int  rst_32k_cs_status         : 1;  /* bit[15]   :  */
        unsigned int  reserved                  : 16; /* bit[16-31]: ������ */
    } reg;
} BBPSCTRL_WTC_PD_SRST_STATUS_UNION;
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_61m_wbbp_top2_status_START   (0)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_61m_wbbp_top2_status_END     (0)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_wbbp_top2_status_START  (1)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_wbbp_top2_status_END    (1)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_245m_wbbp_top2_status_START  (2)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_245m_wbbp_top2_status_END    (2)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_tw_status_START         (3)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_tw_status_END           (3)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_twc_status_START        (4)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_twc_status_END          (4)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_tds_status_START        (5)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_tds_status_END          (5)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_245m_tds_status_START        (6)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_245m_tds_status_END          (6)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_245m_cbbp_status_START       (7)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_245m_cbbp_status_END         (7)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_61m_wbbp_cs_status_START     (8)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_61m_wbbp_cs_status_END       (8)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_wbbp_cs_status_START    (9)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_wbbp_cs_status_END      (9)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_cbbp_status_START       (10)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_cbbp_status_END         (10)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_wc_status_START         (11)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_122m_wc_status_END           (11)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_61m_tw_status_START          (12)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_61m_tw_status_END            (12)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_245m_tw_status_START         (13)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_245m_tw_status_END           (13)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_19m_cs_status_START          (14)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_19m_cs_status_END            (14)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_32k_cs_status_START          (15)
#define BBPSCTRL_WTC_PD_SRST_STATUS_rst_32k_cs_status_END            (15)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_IRM_PD_CLK_EN_UNION
 �ṹ˵��  : IRM_PD_CLK_EN �Ĵ����ṹ���塣��ַƫ����:0x00C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: IRM��Դ��ʱ��ʹ��
*****************************************************************************/
typedef union
{
    unsigned int      irm_pd_clk_en_reg;
    struct
    {
        unsigned int  irm_comm_122m_clk_en   : 1;  /* bit[0]    :  */
        unsigned int  irm_imi_clk_en         : 1;  /* bit[1]    :  */
        unsigned int  irm_tdl_ch0_clk_en     : 1;  /* bit[2]    :  */
        unsigned int  irm_tdl_ch1_clk_en     : 1;  /* bit[3]    :  */
        unsigned int  irm_mst_ram_clk_en     : 1;  /* bit[4]    :  */
        unsigned int  irm_comm_245m_clk_en   : 1;  /* bit[5]    :  */
        unsigned int  irm_tubo_lte_2x_clk_en : 1;  /* bit[6]    :  */
        unsigned int  irm_tubo_lte_clk_en    : 1;  /* bit[7]    :  */
        unsigned int  irm_tubo_tuc_2x_clk_en : 1;  /* bit[8]    :  */
        unsigned int  irm_tubo_tuc_clk_en    : 1;  /* bit[9]    :  */
        unsigned int  irm_soc_ap_ram_clk_en  : 1;  /* bit[10]   :  */
        unsigned int  reserved               : 21; /* bit[11-31]: ������ */
    } reg;
} BBPSCTRL_IRM_PD_CLK_EN_UNION;
#define BBPSCTRL_IRM_PD_CLK_EN_irm_comm_122m_clk_en_START    (0)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_comm_122m_clk_en_END      (0)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_imi_clk_en_START          (1)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_imi_clk_en_END            (1)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tdl_ch0_clk_en_START      (2)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tdl_ch0_clk_en_END        (2)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tdl_ch1_clk_en_START      (3)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tdl_ch1_clk_en_END        (3)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_mst_ram_clk_en_START      (4)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_mst_ram_clk_en_END        (4)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_comm_245m_clk_en_START    (5)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_comm_245m_clk_en_END      (5)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tubo_lte_2x_clk_en_START  (6)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tubo_lte_2x_clk_en_END    (6)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tubo_lte_clk_en_START     (7)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tubo_lte_clk_en_END       (7)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tubo_tuc_2x_clk_en_START  (8)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tubo_tuc_2x_clk_en_END    (8)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tubo_tuc_clk_en_START     (9)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_tubo_tuc_clk_en_END       (9)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_soc_ap_ram_clk_en_START   (10)
#define BBPSCTRL_IRM_PD_CLK_EN_irm_soc_ap_ram_clk_en_END     (10)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_IRM_PD_CLK_DIS_UNION
 �ṹ˵��  : IRM_PD_CLK_DIS �Ĵ����ṹ���塣��ַƫ����:0x00C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: IRM��Դ��ʱ�ӹر�
*****************************************************************************/
typedef union
{
    unsigned int      irm_pd_clk_dis_reg;
    struct
    {
        unsigned int  irm_comm_122m_clk_dis   : 1;  /* bit[0]    :  */
        unsigned int  irm_imi_clk_dis         : 1;  /* bit[1]    :  */
        unsigned int  irm_tdl_ch0_clk_dis     : 1;  /* bit[2]    :  */
        unsigned int  irm_tdl_ch1_clk_dis     : 1;  /* bit[3]    :  */
        unsigned int  irm_mst_ram_clk_dis     : 1;  /* bit[4]    :  */
        unsigned int  irm_comm_245m_clk_dis   : 1;  /* bit[5]    :  */
        unsigned int  irm_tubo_lte_2x_clk_dis : 1;  /* bit[6]    :  */
        unsigned int  irm_tubo_lte_clk_dis    : 1;  /* bit[7]    :  */
        unsigned int  irm_tubo_tuc_2x_clk_dis : 1;  /* bit[8]    :  */
        unsigned int  irm_tubo_tuc_clk_dis    : 1;  /* bit[9]    :  */
        unsigned int  irm_soc_ap_ram_clk_dis  : 1;  /* bit[10]   :  */
        unsigned int  reserved                : 21; /* bit[11-31]: ������ */
    } reg;
} BBPSCTRL_IRM_PD_CLK_DIS_UNION;
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_comm_122m_clk_dis_START    (0)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_comm_122m_clk_dis_END      (0)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_imi_clk_dis_START          (1)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_imi_clk_dis_END            (1)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tdl_ch0_clk_dis_START      (2)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tdl_ch0_clk_dis_END        (2)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tdl_ch1_clk_dis_START      (3)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tdl_ch1_clk_dis_END        (3)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_mst_ram_clk_dis_START      (4)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_mst_ram_clk_dis_END        (4)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_comm_245m_clk_dis_START    (5)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_comm_245m_clk_dis_END      (5)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tubo_lte_2x_clk_dis_START  (6)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tubo_lte_2x_clk_dis_END    (6)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tubo_lte_clk_dis_START     (7)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tubo_lte_clk_dis_END       (7)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tubo_tuc_2x_clk_dis_START  (8)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tubo_tuc_2x_clk_dis_END    (8)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tubo_tuc_clk_dis_START     (9)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_tubo_tuc_clk_dis_END       (9)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_soc_ap_ram_clk_dis_START   (10)
#define BBPSCTRL_IRM_PD_CLK_DIS_irm_soc_ap_ram_clk_dis_END     (10)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_IRM_PD_CLK_STATUS_UNION
 �ṹ˵��  : IRM_PD_CLK_STATUS �Ĵ����ṹ���塣��ַƫ����:0x00C8����ֵ:0x00000000�����:32
 �Ĵ���˵��: IRM��Դ��ʱ���ſ�״̬
*****************************************************************************/
typedef union
{
    unsigned int      irm_pd_clk_status_reg;
    struct
    {
        unsigned int  irm_comm_122m_clk_status   : 1;  /* bit[0]    :  */
        unsigned int  irm_imi_clk_status         : 1;  /* bit[1]    :  */
        unsigned int  irm_tdl_ch0_clk_status     : 1;  /* bit[2]    :  */
        unsigned int  irm_tdl_ch1_clk_status     : 1;  /* bit[3]    :  */
        unsigned int  irm_mst_ram_clk_status     : 1;  /* bit[4]    :  */
        unsigned int  irm_comm_245m_clk_status   : 1;  /* bit[5]    :  */
        unsigned int  irm_tubo_lte_2x_clk_status : 1;  /* bit[6]    :  */
        unsigned int  irm_tubo_lte_clk_status    : 1;  /* bit[7]    :  */
        unsigned int  irm_tubo_tuc_2x_clk_status : 1;  /* bit[8]    :  */
        unsigned int  irm_tubo_tuc_clk_status    : 1;  /* bit[9]    :  */
        unsigned int  irm_soc_ap_ram_clk_status  : 1;  /* bit[10]   :  */
        unsigned int  reserved                   : 21; /* bit[11-31]: ������ */
    } reg;
} BBPSCTRL_IRM_PD_CLK_STATUS_UNION;
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_comm_122m_clk_status_START    (0)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_comm_122m_clk_status_END      (0)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_imi_clk_status_START          (1)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_imi_clk_status_END            (1)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tdl_ch0_clk_status_START      (2)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tdl_ch0_clk_status_END        (2)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tdl_ch1_clk_status_START      (3)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tdl_ch1_clk_status_END        (3)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_mst_ram_clk_status_START      (4)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_mst_ram_clk_status_END        (4)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_comm_245m_clk_status_START    (5)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_comm_245m_clk_status_END      (5)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tubo_lte_2x_clk_status_START  (6)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tubo_lte_2x_clk_status_END    (6)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tubo_lte_clk_status_START     (7)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tubo_lte_clk_status_END       (7)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tubo_tuc_2x_clk_status_START  (8)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tubo_tuc_2x_clk_status_END    (8)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tubo_tuc_clk_status_START     (9)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_tubo_tuc_clk_status_END       (9)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_soc_ap_ram_clk_status_START   (10)
#define BBPSCTRL_IRM_PD_CLK_STATUS_irm_soc_ap_ram_clk_status_END     (10)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_IRM_PD_SRST_REQ_UNION
 �ṹ˵��  : IRM_PD_SRST_REQ �Ĵ����ṹ���塣��ַƫ����:0x00D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: IRM��Դ��λ����ʹ��
*****************************************************************************/
typedef union
{
    unsigned int      irm_pd_srst_req_reg;
    struct
    {
        unsigned int  irm_comm_122m_srst_req   : 1;  /* bit[0]    :  */
        unsigned int  irm_imi_srst_req         : 1;  /* bit[1]    :  */
        unsigned int  irm_tdl_ch0_srst_req     : 1;  /* bit[2]    :  */
        unsigned int  irm_tdl_ch1_srst_req     : 1;  /* bit[3]    :  */
        unsigned int  irm_mst_ram_srst_req     : 1;  /* bit[4]    :  */
        unsigned int  irm_comm_245m_srst_req   : 1;  /* bit[5]    :  */
        unsigned int  irm_tubo_lte_2x_srst_req : 1;  /* bit[6]    :  */
        unsigned int  irm_tubo_lte_srst_req    : 1;  /* bit[7]    :  */
        unsigned int  irm_tubo_tuc_2x_srst_req : 1;  /* bit[8]    :  */
        unsigned int  irm_tubo_tuc_srst_req    : 1;  /* bit[9]    :  */
        unsigned int  irm_soc_ap_ram_srst_req  : 1;  /* bit[10]   :  */
        unsigned int  reserved                 : 21; /* bit[11-31]: ������ */
    } reg;
} BBPSCTRL_IRM_PD_SRST_REQ_UNION;
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_comm_122m_srst_req_START    (0)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_comm_122m_srst_req_END      (0)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_imi_srst_req_START          (1)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_imi_srst_req_END            (1)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tdl_ch0_srst_req_START      (2)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tdl_ch0_srst_req_END        (2)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tdl_ch1_srst_req_START      (3)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tdl_ch1_srst_req_END        (3)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_mst_ram_srst_req_START      (4)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_mst_ram_srst_req_END        (4)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_comm_245m_srst_req_START    (5)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_comm_245m_srst_req_END      (5)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tubo_lte_2x_srst_req_START  (6)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tubo_lte_2x_srst_req_END    (6)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tubo_lte_srst_req_START     (7)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tubo_lte_srst_req_END       (7)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tubo_tuc_2x_srst_req_START  (8)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tubo_tuc_2x_srst_req_END    (8)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tubo_tuc_srst_req_START     (9)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_tubo_tuc_srst_req_END       (9)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_soc_ap_ram_srst_req_START   (10)
#define BBPSCTRL_IRM_PD_SRST_REQ_irm_soc_ap_ram_srst_req_END     (10)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_IRM_PD_SRST_DIS_UNION
 �ṹ˵��  : IRM_PD_SRST_DIS �Ĵ����ṹ���塣��ַƫ����:0x00D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: IRM��Դ��λ�������
*****************************************************************************/
typedef union
{
    unsigned int      irm_pd_srst_dis_reg;
    struct
    {
        unsigned int  irm_comm_122m_srst_dis   : 1;  /* bit[0]    :  */
        unsigned int  irm_imi_srst_dis         : 1;  /* bit[1]    :  */
        unsigned int  irm_tdl_ch0_srst_dis     : 1;  /* bit[2]    :  */
        unsigned int  irm_tdl_ch1_srst_dis     : 1;  /* bit[3]    :  */
        unsigned int  irm_mst_ram_srst_dis     : 1;  /* bit[4]    :  */
        unsigned int  irm_comm_245m_srst_dis   : 1;  /* bit[5]    :  */
        unsigned int  irm_tubo_lte_2x_srst_dis : 1;  /* bit[6]    :  */
        unsigned int  irm_tubo_lte_srst_dis    : 1;  /* bit[7]    :  */
        unsigned int  irm_tubo_tuc_2x_srst_dis : 1;  /* bit[8]    :  */
        unsigned int  irm_tubo_tuc_srst_dis    : 1;  /* bit[9]    :  */
        unsigned int  irm_soc_ap_ram_srst_dis  : 1;  /* bit[10]   :  */
        unsigned int  reserved                 : 21; /* bit[11-31]: ������ */
    } reg;
} BBPSCTRL_IRM_PD_SRST_DIS_UNION;
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_comm_122m_srst_dis_START    (0)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_comm_122m_srst_dis_END      (0)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_imi_srst_dis_START          (1)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_imi_srst_dis_END            (1)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tdl_ch0_srst_dis_START      (2)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tdl_ch0_srst_dis_END        (2)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tdl_ch1_srst_dis_START      (3)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tdl_ch1_srst_dis_END        (3)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_mst_ram_srst_dis_START      (4)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_mst_ram_srst_dis_END        (4)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_comm_245m_srst_dis_START    (5)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_comm_245m_srst_dis_END      (5)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tubo_lte_2x_srst_dis_START  (6)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tubo_lte_2x_srst_dis_END    (6)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tubo_lte_srst_dis_START     (7)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tubo_lte_srst_dis_END       (7)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tubo_tuc_2x_srst_dis_START  (8)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tubo_tuc_2x_srst_dis_END    (8)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tubo_tuc_srst_dis_START     (9)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_tubo_tuc_srst_dis_END       (9)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_soc_ap_ram_srst_dis_START   (10)
#define BBPSCTRL_IRM_PD_SRST_DIS_irm_soc_ap_ram_srst_dis_END     (10)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_IRM_PD_SRST_STATUS_UNION
 �ṹ˵��  : IRM_PD_SRST_STATUS �Ĵ����ṹ���塣��ַƫ����:0x00D8����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: IRM��Դ��λ����״̬
*****************************************************************************/
typedef union
{
    unsigned int      irm_pd_srst_status_reg;
    struct
    {
        unsigned int  irm_comm_122m_srst_status   : 1;  /* bit[0]    :  */
        unsigned int  irm_imi_srst_status         : 1;  /* bit[1]    :  */
        unsigned int  irm_tdl_ch0_srst_status     : 1;  /* bit[2]    :  */
        unsigned int  irm_tdl_ch1_srst_status     : 1;  /* bit[3]    :  */
        unsigned int  irm_mst_ram_srst_status     : 1;  /* bit[4]    :  */
        unsigned int  irm_comm_245m_srst_status   : 1;  /* bit[5]    :  */
        unsigned int  irm_tubo_lte_2x_srst_status : 1;  /* bit[6]    :  */
        unsigned int  irm_tubo_lte_srst_status    : 1;  /* bit[7]    :  */
        unsigned int  irm_tubo_tuc_2x_srst_status : 1;  /* bit[8]    :  */
        unsigned int  irm_tubo_tuc_srst_status    : 1;  /* bit[9]    :  */
        unsigned int  irm_soc_ap_ram_srst_status  : 1;  /* bit[10]   :  */
        unsigned int  reserved                    : 21; /* bit[11-31]: ������ */
    } reg;
} BBPSCTRL_IRM_PD_SRST_STATUS_UNION;
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_comm_122m_srst_status_START    (0)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_comm_122m_srst_status_END      (0)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_imi_srst_status_START          (1)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_imi_srst_status_END            (1)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tdl_ch0_srst_status_START      (2)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tdl_ch0_srst_status_END        (2)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tdl_ch1_srst_status_START      (3)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tdl_ch1_srst_status_END        (3)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_mst_ram_srst_status_START      (4)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_mst_ram_srst_status_END        (4)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_comm_245m_srst_status_START    (5)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_comm_245m_srst_status_END      (5)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tubo_lte_2x_srst_status_START  (6)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tubo_lte_2x_srst_status_END    (6)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tubo_lte_srst_status_START     (7)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tubo_lte_srst_status_END       (7)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tubo_tuc_2x_srst_status_START  (8)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tubo_tuc_2x_srst_status_END    (8)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tubo_tuc_srst_status_START     (9)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_tubo_tuc_srst_status_END       (9)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_soc_ap_ram_srst_status_START   (10)
#define BBPSCTRL_IRM_PD_SRST_STATUS_irm_soc_ap_ram_srst_status_END     (10)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_COM_CLK_EN_UNION
 �ṹ˵��  : COM_CLK_EN �Ĵ����ṹ���塣��ַƫ����:0x00E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: COMʱ��ʹ��
*****************************************************************************/
typedef union
{
    unsigned int      com_clk_en_reg;
    struct
    {
        unsigned int  com_g1_clk_en       : 1;  /* bit[0]    :  */
        unsigned int  com_g2_clk_en       : 1;  /* bit[1]    :  */
        unsigned int  reserved_0          : 1;  /* bit[2]    :  */
        unsigned int  com_g_sdr_clk_en    : 1;  /* bit[3]    :  */
        unsigned int  com_l_sdr_clk_en    : 1;  /* bit[4]    : l sdrģ��ʱ�Ӵ򿪡�
                                                               ע�⣬��tl_dbg_clk_en��ʱ��ͬ�����l sdrģ���ʱ�ӡ� */
        unsigned int  com_tl_dma_clk_en   : 1;  /* bit[5]    :  */
        unsigned int  com_tl_dbg_clk_en   : 1;  /* bit[6]    :  */
        unsigned int  com_gu_mst_clk_en   : 1;  /* bit[7]    :  */
        unsigned int  reserved_1          : 1;  /* bit[8]    : ��λû��ʱ��ʹ�ܡ� */
        unsigned int  com_et_clk_en       : 1;  /* bit[9]    :  */
        unsigned int  com_cs_clk_en       : 1;  /* bit[10]   :  */
        unsigned int  com_sys_clk_en      : 1;  /* bit[11]   : ��λû��ʱ��ʹ�ܡ� */
        unsigned int  com_lte_cs_clk_en   : 1;  /* bit[12]   : ��λû��ʱ��ʹ�ܡ� */
        unsigned int  com_wc_clk_en       : 1;  /* bit[13]   :  */
        unsigned int  com_uc2_122m_clk_en : 1;  /* bit[14]   :  */
        unsigned int  com_dbg_trig_clk_en : 1;  /* bit[15]   :  */
        unsigned int  com_w_tx_clk_en     : 1;  /* bit[16]   : Wģʽtxʱ��ʹ�ܡ����ź���Ҫͬʱ��W_SYS_CLK_EN�� */
        unsigned int  com_t_tx_clk_en     : 1;  /* bit[17]   : Tģʽtxʱ��ʹ�ܡ����ź���Ҫͬʱ��T_SYS_CLK_EN�� */
        unsigned int  com_c_tx_clk_en     : 1;  /* bit[18]   : C2ģʽtxʱ��ʹ�ܡ����ź���Ҫͬʱ��C_SYS_CLK_EN�� */
        unsigned int  com_et_sub_clk_en   : 1;  /* bit[19]   : ����ET����ʱ��ʹ�� */
        unsigned int  com_l_et_clk_en     : 1;  /* bit[20]   : ����ET��Lʱ��ʹ�� */
        unsigned int  com_w_et_clk_en     : 1;  /* bit[21]   : ����ET��Wʱ��ʹ�� */
        unsigned int  com_mipi_clk_en     : 1;  /* bit[22]   : BBP_COMM_FE��mipiʱ��ʹ�ܡ���ʱ������19.2M����245.76M��ѡ���źż�bbp_clk_ctrl�� */
        unsigned int  com_guc_dbg_clk_en  : 1;  /* bit[23]   : GUC DBGʱ��ʹ�ܡ� */
        unsigned int  com_w_sys_clk_en    : 1;  /* bit[24]   : BBP_COMM_FE�У�Wģʽʱ��ʹ�ܡ� */
        unsigned int  com_t_sys_clk_en    : 1;  /* bit[25]   : BBP_COMM_FE�У�Tģʽʱ��ʹ�� */
        unsigned int  com_c_sys_clk_en    : 1;  /* bit[26]   : BBP_COMM_FE�У�Cģʽʱ��ʹ�� */
        unsigned int  reserved_2          : 5;  /* bit[27-31]: ������ */
    } reg;
} BBPSCTRL_COM_CLK_EN_UNION;
#define BBPSCTRL_COM_CLK_EN_com_g1_clk_en_START        (0)
#define BBPSCTRL_COM_CLK_EN_com_g1_clk_en_END          (0)
#define BBPSCTRL_COM_CLK_EN_com_g2_clk_en_START        (1)
#define BBPSCTRL_COM_CLK_EN_com_g2_clk_en_END          (1)
#define BBPSCTRL_COM_CLK_EN_com_g_sdr_clk_en_START     (3)
#define BBPSCTRL_COM_CLK_EN_com_g_sdr_clk_en_END       (3)
#define BBPSCTRL_COM_CLK_EN_com_l_sdr_clk_en_START     (4)
#define BBPSCTRL_COM_CLK_EN_com_l_sdr_clk_en_END       (4)
#define BBPSCTRL_COM_CLK_EN_com_tl_dma_clk_en_START    (5)
#define BBPSCTRL_COM_CLK_EN_com_tl_dma_clk_en_END      (5)
#define BBPSCTRL_COM_CLK_EN_com_tl_dbg_clk_en_START    (6)
#define BBPSCTRL_COM_CLK_EN_com_tl_dbg_clk_en_END      (6)
#define BBPSCTRL_COM_CLK_EN_com_gu_mst_clk_en_START    (7)
#define BBPSCTRL_COM_CLK_EN_com_gu_mst_clk_en_END      (7)
#define BBPSCTRL_COM_CLK_EN_com_et_clk_en_START        (9)
#define BBPSCTRL_COM_CLK_EN_com_et_clk_en_END          (9)
#define BBPSCTRL_COM_CLK_EN_com_cs_clk_en_START        (10)
#define BBPSCTRL_COM_CLK_EN_com_cs_clk_en_END          (10)
#define BBPSCTRL_COM_CLK_EN_com_sys_clk_en_START       (11)
#define BBPSCTRL_COM_CLK_EN_com_sys_clk_en_END         (11)
#define BBPSCTRL_COM_CLK_EN_com_lte_cs_clk_en_START    (12)
#define BBPSCTRL_COM_CLK_EN_com_lte_cs_clk_en_END      (12)
#define BBPSCTRL_COM_CLK_EN_com_wc_clk_en_START        (13)
#define BBPSCTRL_COM_CLK_EN_com_wc_clk_en_END          (13)
#define BBPSCTRL_COM_CLK_EN_com_uc2_122m_clk_en_START  (14)
#define BBPSCTRL_COM_CLK_EN_com_uc2_122m_clk_en_END    (14)
#define BBPSCTRL_COM_CLK_EN_com_dbg_trig_clk_en_START  (15)
#define BBPSCTRL_COM_CLK_EN_com_dbg_trig_clk_en_END    (15)
#define BBPSCTRL_COM_CLK_EN_com_w_tx_clk_en_START      (16)
#define BBPSCTRL_COM_CLK_EN_com_w_tx_clk_en_END        (16)
#define BBPSCTRL_COM_CLK_EN_com_t_tx_clk_en_START      (17)
#define BBPSCTRL_COM_CLK_EN_com_t_tx_clk_en_END        (17)
#define BBPSCTRL_COM_CLK_EN_com_c_tx_clk_en_START      (18)
#define BBPSCTRL_COM_CLK_EN_com_c_tx_clk_en_END        (18)
#define BBPSCTRL_COM_CLK_EN_com_et_sub_clk_en_START    (19)
#define BBPSCTRL_COM_CLK_EN_com_et_sub_clk_en_END      (19)
#define BBPSCTRL_COM_CLK_EN_com_l_et_clk_en_START      (20)
#define BBPSCTRL_COM_CLK_EN_com_l_et_clk_en_END        (20)
#define BBPSCTRL_COM_CLK_EN_com_w_et_clk_en_START      (21)
#define BBPSCTRL_COM_CLK_EN_com_w_et_clk_en_END        (21)
#define BBPSCTRL_COM_CLK_EN_com_mipi_clk_en_START      (22)
#define BBPSCTRL_COM_CLK_EN_com_mipi_clk_en_END        (22)
#define BBPSCTRL_COM_CLK_EN_com_guc_dbg_clk_en_START   (23)
#define BBPSCTRL_COM_CLK_EN_com_guc_dbg_clk_en_END     (23)
#define BBPSCTRL_COM_CLK_EN_com_w_sys_clk_en_START     (24)
#define BBPSCTRL_COM_CLK_EN_com_w_sys_clk_en_END       (24)
#define BBPSCTRL_COM_CLK_EN_com_t_sys_clk_en_START     (25)
#define BBPSCTRL_COM_CLK_EN_com_t_sys_clk_en_END       (25)
#define BBPSCTRL_COM_CLK_EN_com_c_sys_clk_en_START     (26)
#define BBPSCTRL_COM_CLK_EN_com_c_sys_clk_en_END       (26)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_COM_CLK_DIS_UNION
 �ṹ˵��  : COM_CLK_DIS �Ĵ����ṹ���塣��ַƫ����:0x00E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: COMʱ�ӹر�
*****************************************************************************/
typedef union
{
    unsigned int      com_clk_dis_reg;
    struct
    {
        unsigned int  com_g1_clk_dis       : 1;  /* bit[0]    :  */
        unsigned int  com_g2_clk_dis       : 1;  /* bit[1]    :  */
        unsigned int  reserved_0           : 1;  /* bit[2]    :  */
        unsigned int  com_g_sdr_clk_dis    : 1;  /* bit[3]    :  */
        unsigned int  com_l_sdr_clk_dis    : 1;  /* bit[4]    :  */
        unsigned int  com_tl_dma_clk_dis   : 1;  /* bit[5]    :  */
        unsigned int  com_tl_dbg_clk_dis   : 1;  /* bit[6]    :  */
        unsigned int  com_gu_mst_clk_dis   : 1;  /* bit[7]    :  */
        unsigned int  reserved_1           : 1;  /* bit[8]    : ��λû��ʱ��ʹ�ܡ� */
        unsigned int  com_et_clk_dis       : 1;  /* bit[9]    :  */
        unsigned int  com_cs_clk_dis       : 1;  /* bit[10]   :  */
        unsigned int  com_sys_clk_dis      : 1;  /* bit[11]   : ��λû��ʱ��ʹ�ܡ� */
        unsigned int  com_lte_cs_clk_dis   : 1;  /* bit[12]   : ��λû��ʱ��ʹ�ܡ� */
        unsigned int  com_wc_clk_dis       : 1;  /* bit[13]   :  */
        unsigned int  com_uc2_122m_clk_dis : 1;  /* bit[14]   :  */
        unsigned int  com_dbg_trig_clk_dis : 1;  /* bit[15]   :  */
        unsigned int  com_w_tx_clk_dis     : 1;  /* bit[16]   :  */
        unsigned int  com_t_tx_clk_dis     : 1;  /* bit[17]   :  */
        unsigned int  com_c_tx_clk_dis     : 1;  /* bit[18]   :  */
        unsigned int  com_et_sub_clk_dis   : 1;  /* bit[19]   : ����ET����ʱ�ӹر� */
        unsigned int  com_l_et_clk_dis     : 1;  /* bit[20]   : ����ET��Lʱ�ӹر� */
        unsigned int  com_w_et_clk_dis     : 1;  /* bit[21]   : ����ET��Wʱ�ӹر� */
        unsigned int  com_mipi_clk_dis     : 1;  /* bit[22]   : BBP_COMM_FE��mipiʱ�ӹر� */
        unsigned int  com_guc_dbg_clk_dis  : 1;  /* bit[23]   : GUC DBGʱ�ӹر� */
        unsigned int  com_w_sys_clk_dis    : 1;  /* bit[24]   : BBP_COMM_FE�У�Wģʽʱ�ӹر� */
        unsigned int  com_t_sys_clk_dis    : 1;  /* bit[25]   : BBP_COMM_FE�У�Tģʽʱ�ӹر� */
        unsigned int  com_c_sys_clk_dis    : 1;  /* bit[26]   : BBP_COMM_FE�У�Cģʽʱ�ӹر� */
        unsigned int  reserved_2           : 5;  /* bit[27-31]: ������ */
    } reg;
} BBPSCTRL_COM_CLK_DIS_UNION;
#define BBPSCTRL_COM_CLK_DIS_com_g1_clk_dis_START        (0)
#define BBPSCTRL_COM_CLK_DIS_com_g1_clk_dis_END          (0)
#define BBPSCTRL_COM_CLK_DIS_com_g2_clk_dis_START        (1)
#define BBPSCTRL_COM_CLK_DIS_com_g2_clk_dis_END          (1)
#define BBPSCTRL_COM_CLK_DIS_com_g_sdr_clk_dis_START     (3)
#define BBPSCTRL_COM_CLK_DIS_com_g_sdr_clk_dis_END       (3)
#define BBPSCTRL_COM_CLK_DIS_com_l_sdr_clk_dis_START     (4)
#define BBPSCTRL_COM_CLK_DIS_com_l_sdr_clk_dis_END       (4)
#define BBPSCTRL_COM_CLK_DIS_com_tl_dma_clk_dis_START    (5)
#define BBPSCTRL_COM_CLK_DIS_com_tl_dma_clk_dis_END      (5)
#define BBPSCTRL_COM_CLK_DIS_com_tl_dbg_clk_dis_START    (6)
#define BBPSCTRL_COM_CLK_DIS_com_tl_dbg_clk_dis_END      (6)
#define BBPSCTRL_COM_CLK_DIS_com_gu_mst_clk_dis_START    (7)
#define BBPSCTRL_COM_CLK_DIS_com_gu_mst_clk_dis_END      (7)
#define BBPSCTRL_COM_CLK_DIS_com_et_clk_dis_START        (9)
#define BBPSCTRL_COM_CLK_DIS_com_et_clk_dis_END          (9)
#define BBPSCTRL_COM_CLK_DIS_com_cs_clk_dis_START        (10)
#define BBPSCTRL_COM_CLK_DIS_com_cs_clk_dis_END          (10)
#define BBPSCTRL_COM_CLK_DIS_com_sys_clk_dis_START       (11)
#define BBPSCTRL_COM_CLK_DIS_com_sys_clk_dis_END         (11)
#define BBPSCTRL_COM_CLK_DIS_com_lte_cs_clk_dis_START    (12)
#define BBPSCTRL_COM_CLK_DIS_com_lte_cs_clk_dis_END      (12)
#define BBPSCTRL_COM_CLK_DIS_com_wc_clk_dis_START        (13)
#define BBPSCTRL_COM_CLK_DIS_com_wc_clk_dis_END          (13)
#define BBPSCTRL_COM_CLK_DIS_com_uc2_122m_clk_dis_START  (14)
#define BBPSCTRL_COM_CLK_DIS_com_uc2_122m_clk_dis_END    (14)
#define BBPSCTRL_COM_CLK_DIS_com_dbg_trig_clk_dis_START  (15)
#define BBPSCTRL_COM_CLK_DIS_com_dbg_trig_clk_dis_END    (15)
#define BBPSCTRL_COM_CLK_DIS_com_w_tx_clk_dis_START      (16)
#define BBPSCTRL_COM_CLK_DIS_com_w_tx_clk_dis_END        (16)
#define BBPSCTRL_COM_CLK_DIS_com_t_tx_clk_dis_START      (17)
#define BBPSCTRL_COM_CLK_DIS_com_t_tx_clk_dis_END        (17)
#define BBPSCTRL_COM_CLK_DIS_com_c_tx_clk_dis_START      (18)
#define BBPSCTRL_COM_CLK_DIS_com_c_tx_clk_dis_END        (18)
#define BBPSCTRL_COM_CLK_DIS_com_et_sub_clk_dis_START    (19)
#define BBPSCTRL_COM_CLK_DIS_com_et_sub_clk_dis_END      (19)
#define BBPSCTRL_COM_CLK_DIS_com_l_et_clk_dis_START      (20)
#define BBPSCTRL_COM_CLK_DIS_com_l_et_clk_dis_END        (20)
#define BBPSCTRL_COM_CLK_DIS_com_w_et_clk_dis_START      (21)
#define BBPSCTRL_COM_CLK_DIS_com_w_et_clk_dis_END        (21)
#define BBPSCTRL_COM_CLK_DIS_com_mipi_clk_dis_START      (22)
#define BBPSCTRL_COM_CLK_DIS_com_mipi_clk_dis_END        (22)
#define BBPSCTRL_COM_CLK_DIS_com_guc_dbg_clk_dis_START   (23)
#define BBPSCTRL_COM_CLK_DIS_com_guc_dbg_clk_dis_END     (23)
#define BBPSCTRL_COM_CLK_DIS_com_w_sys_clk_dis_START     (24)
#define BBPSCTRL_COM_CLK_DIS_com_w_sys_clk_dis_END       (24)
#define BBPSCTRL_COM_CLK_DIS_com_t_sys_clk_dis_START     (25)
#define BBPSCTRL_COM_CLK_DIS_com_t_sys_clk_dis_END       (25)
#define BBPSCTRL_COM_CLK_DIS_com_c_sys_clk_dis_START     (26)
#define BBPSCTRL_COM_CLK_DIS_com_c_sys_clk_dis_END       (26)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_COM_CLK_STATUS_UNION
 �ṹ˵��  : COM_CLK_STATUS �Ĵ����ṹ���塣��ַƫ����:0x00E8����ֵ:0x00000000�����:32
 �Ĵ���˵��: COMʱ���ſ�״̬
*****************************************************************************/
typedef union
{
    unsigned int      com_clk_status_reg;
    struct
    {
        unsigned int  com_g1_clk_status       : 1;  /* bit[0]    :  */
        unsigned int  com_g2_clk_status       : 1;  /* bit[1]    :  */
        unsigned int  reserved_0              : 1;  /* bit[2]    :  */
        unsigned int  com_g_sdr_clk_status    : 1;  /* bit[3]    :  */
        unsigned int  com_l_sdr_clk_status    : 1;  /* bit[4]    :  */
        unsigned int  com_tl_dma_clk_status   : 1;  /* bit[5]    :  */
        unsigned int  com_tl_dbg_clk_status   : 1;  /* bit[6]    :  */
        unsigned int  com_gu_mst_clk_status   : 1;  /* bit[7]    :  */
        unsigned int  wcs_245_clk_status      : 1;  /* bit[8]    : ����ϵ�ʱ��״̬��0xE0/0xE4��Ӧbitλ����ʱ��ʹ�� */
        unsigned int  com_et_clk_status       : 1;  /* bit[9]    :  */
        unsigned int  com_cs_clk_status       : 1;  /* bit[10]   :  */
        unsigned int  com_sys_clk_status      : 1;  /* bit[11]   : ����ϵ�ʱ��״̬��0xE0/0xE4��Ӧbitλ����ʱ��ʹ�� */
        unsigned int  com_lte_cs_clk_status   : 1;  /* bit[12]   : ����ϵ�ʱ��״̬��0xE0/0xE4��Ӧbitλ����ʱ��ʹ�� */
        unsigned int  com_wc_clk_status       : 1;  /* bit[13]   :  */
        unsigned int  com_uc2_122m_clk_status : 1;  /* bit[14]   :  */
        unsigned int  com_dbg_trig_clk_status : 1;  /* bit[15]   :  */
        unsigned int  com_w_tx_clk_status     : 1;  /* bit[16]   :  */
        unsigned int  com_t_tx_clk_status     : 1;  /* bit[17]   :  */
        unsigned int  com_c_tx_clk_status     : 1;  /* bit[18]   :  */
        unsigned int  com_et_sub_clk_status   : 1;  /* bit[19]   : ����ET����ʱ��״̬ */
        unsigned int  com_l_et_clk_status     : 1;  /* bit[20]   : ����ET��Lʱ��״̬ */
        unsigned int  com_w_et_clk_status     : 1;  /* bit[21]   : ����ET��Wʱ��״̬ */
        unsigned int  com_mipi_clk_status     : 1;  /* bit[22]   : BBP_COMM_FE��mipiʱ��״̬ */
        unsigned int  com_guc_dbg_clk_status  : 1;  /* bit[23]   : GUC DBGʱ��״̬ */
        unsigned int  com_w_sys_clk_status    : 1;  /* bit[24]   : BBP_COMM_FE�У�Wģʽʱ��״̬ */
        unsigned int  com_t_sys_clk_status    : 1;  /* bit[25]   : BBP_COMM_FE�У�Tģʽʱ��״̬ */
        unsigned int  com_c_sys_clk_status    : 1;  /* bit[26]   : BBP_COMM_FE�У�Cģʽʱ��״̬ */
        unsigned int  reserved_1              : 5;  /* bit[27-31]: ������ */
    } reg;
} BBPSCTRL_COM_CLK_STATUS_UNION;
#define BBPSCTRL_COM_CLK_STATUS_com_g1_clk_status_START        (0)
#define BBPSCTRL_COM_CLK_STATUS_com_g1_clk_status_END          (0)
#define BBPSCTRL_COM_CLK_STATUS_com_g2_clk_status_START        (1)
#define BBPSCTRL_COM_CLK_STATUS_com_g2_clk_status_END          (1)
#define BBPSCTRL_COM_CLK_STATUS_com_g_sdr_clk_status_START     (3)
#define BBPSCTRL_COM_CLK_STATUS_com_g_sdr_clk_status_END       (3)
#define BBPSCTRL_COM_CLK_STATUS_com_l_sdr_clk_status_START     (4)
#define BBPSCTRL_COM_CLK_STATUS_com_l_sdr_clk_status_END       (4)
#define BBPSCTRL_COM_CLK_STATUS_com_tl_dma_clk_status_START    (5)
#define BBPSCTRL_COM_CLK_STATUS_com_tl_dma_clk_status_END      (5)
#define BBPSCTRL_COM_CLK_STATUS_com_tl_dbg_clk_status_START    (6)
#define BBPSCTRL_COM_CLK_STATUS_com_tl_dbg_clk_status_END      (6)
#define BBPSCTRL_COM_CLK_STATUS_com_gu_mst_clk_status_START    (7)
#define BBPSCTRL_COM_CLK_STATUS_com_gu_mst_clk_status_END      (7)
#define BBPSCTRL_COM_CLK_STATUS_wcs_245_clk_status_START       (8)
#define BBPSCTRL_COM_CLK_STATUS_wcs_245_clk_status_END         (8)
#define BBPSCTRL_COM_CLK_STATUS_com_et_clk_status_START        (9)
#define BBPSCTRL_COM_CLK_STATUS_com_et_clk_status_END          (9)
#define BBPSCTRL_COM_CLK_STATUS_com_cs_clk_status_START        (10)
#define BBPSCTRL_COM_CLK_STATUS_com_cs_clk_status_END          (10)
#define BBPSCTRL_COM_CLK_STATUS_com_sys_clk_status_START       (11)
#define BBPSCTRL_COM_CLK_STATUS_com_sys_clk_status_END         (11)
#define BBPSCTRL_COM_CLK_STATUS_com_lte_cs_clk_status_START    (12)
#define BBPSCTRL_COM_CLK_STATUS_com_lte_cs_clk_status_END      (12)
#define BBPSCTRL_COM_CLK_STATUS_com_wc_clk_status_START        (13)
#define BBPSCTRL_COM_CLK_STATUS_com_wc_clk_status_END          (13)
#define BBPSCTRL_COM_CLK_STATUS_com_uc2_122m_clk_status_START  (14)
#define BBPSCTRL_COM_CLK_STATUS_com_uc2_122m_clk_status_END    (14)
#define BBPSCTRL_COM_CLK_STATUS_com_dbg_trig_clk_status_START  (15)
#define BBPSCTRL_COM_CLK_STATUS_com_dbg_trig_clk_status_END    (15)
#define BBPSCTRL_COM_CLK_STATUS_com_w_tx_clk_status_START      (16)
#define BBPSCTRL_COM_CLK_STATUS_com_w_tx_clk_status_END        (16)
#define BBPSCTRL_COM_CLK_STATUS_com_t_tx_clk_status_START      (17)
#define BBPSCTRL_COM_CLK_STATUS_com_t_tx_clk_status_END        (17)
#define BBPSCTRL_COM_CLK_STATUS_com_c_tx_clk_status_START      (18)
#define BBPSCTRL_COM_CLK_STATUS_com_c_tx_clk_status_END        (18)
#define BBPSCTRL_COM_CLK_STATUS_com_et_sub_clk_status_START    (19)
#define BBPSCTRL_COM_CLK_STATUS_com_et_sub_clk_status_END      (19)
#define BBPSCTRL_COM_CLK_STATUS_com_l_et_clk_status_START      (20)
#define BBPSCTRL_COM_CLK_STATUS_com_l_et_clk_status_END        (20)
#define BBPSCTRL_COM_CLK_STATUS_com_w_et_clk_status_START      (21)
#define BBPSCTRL_COM_CLK_STATUS_com_w_et_clk_status_END        (21)
#define BBPSCTRL_COM_CLK_STATUS_com_mipi_clk_status_START      (22)
#define BBPSCTRL_COM_CLK_STATUS_com_mipi_clk_status_END        (22)
#define BBPSCTRL_COM_CLK_STATUS_com_guc_dbg_clk_status_START   (23)
#define BBPSCTRL_COM_CLK_STATUS_com_guc_dbg_clk_status_END     (23)
#define BBPSCTRL_COM_CLK_STATUS_com_w_sys_clk_status_START     (24)
#define BBPSCTRL_COM_CLK_STATUS_com_w_sys_clk_status_END       (24)
#define BBPSCTRL_COM_CLK_STATUS_com_t_sys_clk_status_START     (25)
#define BBPSCTRL_COM_CLK_STATUS_com_t_sys_clk_status_END       (25)
#define BBPSCTRL_COM_CLK_STATUS_com_c_sys_clk_status_START     (26)
#define BBPSCTRL_COM_CLK_STATUS_com_c_sys_clk_status_END       (26)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_COM_SRST_REQ_UNION
 �ṹ˵��  : COM_SRST_REQ �Ĵ����ṹ���塣��ַƫ����:0x00F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: COM��λ����ʹ��
*****************************************************************************/
typedef union
{
    unsigned int      com_srst_req_reg;
    struct
    {
        unsigned int  com_g1_srst_req       : 1;  /* bit[0]    :  */
        unsigned int  com_g2_srst_req       : 1;  /* bit[1]    :  */
        unsigned int  reserved_0            : 1;  /* bit[2]    :  */
        unsigned int  com_g_sdr_srst_req    : 1;  /* bit[3]    :  */
        unsigned int  com_l_sdr_srst_req    : 1;  /* bit[4]    :  */
        unsigned int  com_tl_dma_srst_req   : 1;  /* bit[5]    :  */
        unsigned int  com_tl_dbg_srst_req   : 1;  /* bit[6]    :  */
        unsigned int  com_gu_mst_srst_req   : 1;  /* bit[7]    :  */
        unsigned int  reserved_1            : 1;  /* bit[8]    :  */
        unsigned int  com_et_srst_req       : 1;  /* bit[9]    :  */
        unsigned int  com_cs_srst_req       : 1;  /* bit[10]   :  */
        unsigned int  com_sys_srst_req      : 1;  /* bit[11]   :  */
        unsigned int  com_lte_cs_srst_req   : 1;  /* bit[12]   :  */
        unsigned int  com_wc_srst_req       : 1;  /* bit[13]   :  */
        unsigned int  com_uc2_122m_srst_req : 1;  /* bit[14]   :  */
        unsigned int  com_dbg_trig_srst_req : 1;  /* bit[15]   :  */
        unsigned int  reserved_2            : 3;  /* bit[16-18]:  */
        unsigned int  com_et_sub_srst_req   : 1;  /* bit[19]   : ����ET���߸�λ */
        unsigned int  reserved_3            : 2;  /* bit[20-21]: ���� */
        unsigned int  com_mipi_srst_req     : 1;  /* bit[22]   : BBP_COMM_FE��mipiʱ����λ������Ч�� */
        unsigned int  com_guc_dbg_srst_req  : 1;  /* bit[23]   : GUC DBG��λ���� */
        unsigned int  com_w_sys_srst_req    : 1;  /* bit[24]   : BBP_COMM_FE�У�Wģʽ��λ���� */
        unsigned int  com_t_sys_srst_req    : 1;  /* bit[25]   : BBP_COMM_FE�У�Tģʽ��λ���� */
        unsigned int  com_c_sys_srst_req    : 1;  /* bit[26]   : BBP_COMM_FE�У�Cģʽ��λ���� */
        unsigned int  reserved_4            : 5;  /* bit[27-31]: ������ */
    } reg;
} BBPSCTRL_COM_SRST_REQ_UNION;
#define BBPSCTRL_COM_SRST_REQ_com_g1_srst_req_START        (0)
#define BBPSCTRL_COM_SRST_REQ_com_g1_srst_req_END          (0)
#define BBPSCTRL_COM_SRST_REQ_com_g2_srst_req_START        (1)
#define BBPSCTRL_COM_SRST_REQ_com_g2_srst_req_END          (1)
#define BBPSCTRL_COM_SRST_REQ_com_g_sdr_srst_req_START     (3)
#define BBPSCTRL_COM_SRST_REQ_com_g_sdr_srst_req_END       (3)
#define BBPSCTRL_COM_SRST_REQ_com_l_sdr_srst_req_START     (4)
#define BBPSCTRL_COM_SRST_REQ_com_l_sdr_srst_req_END       (4)
#define BBPSCTRL_COM_SRST_REQ_com_tl_dma_srst_req_START    (5)
#define BBPSCTRL_COM_SRST_REQ_com_tl_dma_srst_req_END      (5)
#define BBPSCTRL_COM_SRST_REQ_com_tl_dbg_srst_req_START    (6)
#define BBPSCTRL_COM_SRST_REQ_com_tl_dbg_srst_req_END      (6)
#define BBPSCTRL_COM_SRST_REQ_com_gu_mst_srst_req_START    (7)
#define BBPSCTRL_COM_SRST_REQ_com_gu_mst_srst_req_END      (7)
#define BBPSCTRL_COM_SRST_REQ_com_et_srst_req_START        (9)
#define BBPSCTRL_COM_SRST_REQ_com_et_srst_req_END          (9)
#define BBPSCTRL_COM_SRST_REQ_com_cs_srst_req_START        (10)
#define BBPSCTRL_COM_SRST_REQ_com_cs_srst_req_END          (10)
#define BBPSCTRL_COM_SRST_REQ_com_sys_srst_req_START       (11)
#define BBPSCTRL_COM_SRST_REQ_com_sys_srst_req_END         (11)
#define BBPSCTRL_COM_SRST_REQ_com_lte_cs_srst_req_START    (12)
#define BBPSCTRL_COM_SRST_REQ_com_lte_cs_srst_req_END      (12)
#define BBPSCTRL_COM_SRST_REQ_com_wc_srst_req_START        (13)
#define BBPSCTRL_COM_SRST_REQ_com_wc_srst_req_END          (13)
#define BBPSCTRL_COM_SRST_REQ_com_uc2_122m_srst_req_START  (14)
#define BBPSCTRL_COM_SRST_REQ_com_uc2_122m_srst_req_END    (14)
#define BBPSCTRL_COM_SRST_REQ_com_dbg_trig_srst_req_START  (15)
#define BBPSCTRL_COM_SRST_REQ_com_dbg_trig_srst_req_END    (15)
#define BBPSCTRL_COM_SRST_REQ_com_et_sub_srst_req_START    (19)
#define BBPSCTRL_COM_SRST_REQ_com_et_sub_srst_req_END      (19)
#define BBPSCTRL_COM_SRST_REQ_com_mipi_srst_req_START      (22)
#define BBPSCTRL_COM_SRST_REQ_com_mipi_srst_req_END        (22)
#define BBPSCTRL_COM_SRST_REQ_com_guc_dbg_srst_req_START   (23)
#define BBPSCTRL_COM_SRST_REQ_com_guc_dbg_srst_req_END     (23)
#define BBPSCTRL_COM_SRST_REQ_com_w_sys_srst_req_START     (24)
#define BBPSCTRL_COM_SRST_REQ_com_w_sys_srst_req_END       (24)
#define BBPSCTRL_COM_SRST_REQ_com_t_sys_srst_req_START     (25)
#define BBPSCTRL_COM_SRST_REQ_com_t_sys_srst_req_END       (25)
#define BBPSCTRL_COM_SRST_REQ_com_c_sys_srst_req_START     (26)
#define BBPSCTRL_COM_SRST_REQ_com_c_sys_srst_req_END       (26)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_COM_SRST_DIS_UNION
 �ṹ˵��  : COM_SRST_DIS �Ĵ����ṹ���塣��ַƫ����:0x00F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: COM��λ�������
*****************************************************************************/
typedef union
{
    unsigned int      com_srst_dis_reg;
    struct
    {
        unsigned int  com_g1_srst_dis       : 1;  /* bit[0]    :  */
        unsigned int  com_g2_srst_dis       : 1;  /* bit[1]    :  */
        unsigned int  reserved_0            : 1;  /* bit[2]    :  */
        unsigned int  com_g_sdr_srst_dis    : 1;  /* bit[3]    :  */
        unsigned int  com_l_sdr_srst_dis    : 1;  /* bit[4]    :  */
        unsigned int  com_tl_dma_srst_dis   : 1;  /* bit[5]    :  */
        unsigned int  com_tl_dbg_srst_dis   : 1;  /* bit[6]    :  */
        unsigned int  com_gu_mst_srst_dis   : 1;  /* bit[7]    :  */
        unsigned int  reserved_1            : 1;  /* bit[8]    :  */
        unsigned int  com_et_srst_dis       : 1;  /* bit[9]    :  */
        unsigned int  com_cs_srst_dis       : 1;  /* bit[10]   :  */
        unsigned int  com_sys_srst_dis      : 1;  /* bit[11]   :  */
        unsigned int  com_lte_cs_srst_dis   : 1;  /* bit[12]   :  */
        unsigned int  com_wc_srst_dis       : 1;  /* bit[13]   :  */
        unsigned int  com_uc2_122m_srst_dis : 1;  /* bit[14]   :  */
        unsigned int  com_dbg_trig_srst_dis : 1;  /* bit[15]   :  */
        unsigned int  reserved_2            : 3;  /* bit[16-18]:  */
        unsigned int  com_et_sub_srst_dis   : 1;  /* bit[19]   : ����ET���߸�λ�ر� */
        unsigned int  reserved_3            : 2;  /* bit[20-21]: ���� */
        unsigned int  com_mipi_srst_dis     : 1;  /* bit[22]   : BBP_COMM_FE��mipiʱ����⸴λ��д1���㡣 */
        unsigned int  com_guc_dbg_srst_dis  : 1;  /* bit[23]   : GUC DBG��λ��� */
        unsigned int  com_w_sys_srst_dis    : 1;  /* bit[24]   : BBP_COMM_FE�У�Wģʽ��λ��� */
        unsigned int  com_t_sys_srst_dis    : 1;  /* bit[25]   : BBP_COMM_FE�У�Tģʽ��λ��� */
        unsigned int  com_c_sys_srst_dis    : 1;  /* bit[26]   : BBP_COMM_FE�У�Cģʽ��λ��� */
        unsigned int  reserved_4            : 5;  /* bit[27-31]: ������ */
    } reg;
} BBPSCTRL_COM_SRST_DIS_UNION;
#define BBPSCTRL_COM_SRST_DIS_com_g1_srst_dis_START        (0)
#define BBPSCTRL_COM_SRST_DIS_com_g1_srst_dis_END          (0)
#define BBPSCTRL_COM_SRST_DIS_com_g2_srst_dis_START        (1)
#define BBPSCTRL_COM_SRST_DIS_com_g2_srst_dis_END          (1)
#define BBPSCTRL_COM_SRST_DIS_com_g_sdr_srst_dis_START     (3)
#define BBPSCTRL_COM_SRST_DIS_com_g_sdr_srst_dis_END       (3)
#define BBPSCTRL_COM_SRST_DIS_com_l_sdr_srst_dis_START     (4)
#define BBPSCTRL_COM_SRST_DIS_com_l_sdr_srst_dis_END       (4)
#define BBPSCTRL_COM_SRST_DIS_com_tl_dma_srst_dis_START    (5)
#define BBPSCTRL_COM_SRST_DIS_com_tl_dma_srst_dis_END      (5)
#define BBPSCTRL_COM_SRST_DIS_com_tl_dbg_srst_dis_START    (6)
#define BBPSCTRL_COM_SRST_DIS_com_tl_dbg_srst_dis_END      (6)
#define BBPSCTRL_COM_SRST_DIS_com_gu_mst_srst_dis_START    (7)
#define BBPSCTRL_COM_SRST_DIS_com_gu_mst_srst_dis_END      (7)
#define BBPSCTRL_COM_SRST_DIS_com_et_srst_dis_START        (9)
#define BBPSCTRL_COM_SRST_DIS_com_et_srst_dis_END          (9)
#define BBPSCTRL_COM_SRST_DIS_com_cs_srst_dis_START        (10)
#define BBPSCTRL_COM_SRST_DIS_com_cs_srst_dis_END          (10)
#define BBPSCTRL_COM_SRST_DIS_com_sys_srst_dis_START       (11)
#define BBPSCTRL_COM_SRST_DIS_com_sys_srst_dis_END         (11)
#define BBPSCTRL_COM_SRST_DIS_com_lte_cs_srst_dis_START    (12)
#define BBPSCTRL_COM_SRST_DIS_com_lte_cs_srst_dis_END      (12)
#define BBPSCTRL_COM_SRST_DIS_com_wc_srst_dis_START        (13)
#define BBPSCTRL_COM_SRST_DIS_com_wc_srst_dis_END          (13)
#define BBPSCTRL_COM_SRST_DIS_com_uc2_122m_srst_dis_START  (14)
#define BBPSCTRL_COM_SRST_DIS_com_uc2_122m_srst_dis_END    (14)
#define BBPSCTRL_COM_SRST_DIS_com_dbg_trig_srst_dis_START  (15)
#define BBPSCTRL_COM_SRST_DIS_com_dbg_trig_srst_dis_END    (15)
#define BBPSCTRL_COM_SRST_DIS_com_et_sub_srst_dis_START    (19)
#define BBPSCTRL_COM_SRST_DIS_com_et_sub_srst_dis_END      (19)
#define BBPSCTRL_COM_SRST_DIS_com_mipi_srst_dis_START      (22)
#define BBPSCTRL_COM_SRST_DIS_com_mipi_srst_dis_END        (22)
#define BBPSCTRL_COM_SRST_DIS_com_guc_dbg_srst_dis_START   (23)
#define BBPSCTRL_COM_SRST_DIS_com_guc_dbg_srst_dis_END     (23)
#define BBPSCTRL_COM_SRST_DIS_com_w_sys_srst_dis_START     (24)
#define BBPSCTRL_COM_SRST_DIS_com_w_sys_srst_dis_END       (24)
#define BBPSCTRL_COM_SRST_DIS_com_t_sys_srst_dis_START     (25)
#define BBPSCTRL_COM_SRST_DIS_com_t_sys_srst_dis_END       (25)
#define BBPSCTRL_COM_SRST_DIS_com_c_sys_srst_dis_START     (26)
#define BBPSCTRL_COM_SRST_DIS_com_c_sys_srst_dis_END       (26)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_COM_SRST_STATUS_UNION
 �ṹ˵��  : COM_SRST_STATUS �Ĵ����ṹ���塣��ַƫ����:0x00F8����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: COM��λ����״̬
*****************************************************************************/
typedef union
{
    unsigned int      com_srst_status_reg;
    struct
    {
        unsigned int  com_g1_srst_status       : 1;  /* bit[0]    :  */
        unsigned int  com_g2_srst_status       : 1;  /* bit[1]    :  */
        unsigned int  reserved_0               : 1;  /* bit[2]    :  */
        unsigned int  com_g_sdr_srst_status    : 1;  /* bit[3]    :  */
        unsigned int  com_l_sdr_srst_status    : 1;  /* bit[4]    :  */
        unsigned int  com_tl_dma_srst_status   : 1;  /* bit[5]    :  */
        unsigned int  com_tl_dbg_srst_status   : 1;  /* bit[6]    :  */
        unsigned int  com_gu_mst_srst_status   : 1;  /* bit[7]    :  */
        unsigned int  reserved_1               : 1;  /* bit[8]    :  */
        unsigned int  com_et_srst_status       : 1;  /* bit[9]    :  */
        unsigned int  com_cs_srst_status       : 1;  /* bit[10]   :  */
        unsigned int  com_sys_srst_status      : 1;  /* bit[11]   :  */
        unsigned int  com_lte_cs_srst_status   : 1;  /* bit[12]   :  */
        unsigned int  com_wc_srst_status       : 1;  /* bit[13]   :  */
        unsigned int  com_uc2_122m_srst_status : 1;  /* bit[14]   :  */
        unsigned int  com_dbg_trig_srst_status : 1;  /* bit[15]   :  */
        unsigned int  reserved_2               : 3;  /* bit[16-18]: ���� */
        unsigned int  com_et_sub_srst_status   : 1;  /* bit[19]   : ����ET���߸�λ״̬ */
        unsigned int  reserved_3               : 2;  /* bit[20-21]: ���� */
        unsigned int  com_mipi_srst_status     : 1;  /* bit[22]   : BBP_COMM_FE��mipiʱ����λ״̬���߸�λ���ͽ⸴λ�� */
        unsigned int  com_guc_dbg_srst_status  : 1;  /* bit[23]   : GUC DBG��λ״̬ */
        unsigned int  com_w_sys_srst_status    : 1;  /* bit[24]   : BBP_COMM_FE�У�Wģʽ��λ״̬ */
        unsigned int  com_t_sys_srst_status    : 1;  /* bit[25]   : BBP_COMM_FE�У�Tģʽ��λ״̬ */
        unsigned int  com_c_sys_srst_status    : 1;  /* bit[26]   : BBP_COMM_FE�У�Cģʽ��λ״̬ */
        unsigned int  reserved_4               : 5;  /* bit[27-31]: ������ */
    } reg;
} BBPSCTRL_COM_SRST_STATUS_UNION;
#define BBPSCTRL_COM_SRST_STATUS_com_g1_srst_status_START        (0)
#define BBPSCTRL_COM_SRST_STATUS_com_g1_srst_status_END          (0)
#define BBPSCTRL_COM_SRST_STATUS_com_g2_srst_status_START        (1)
#define BBPSCTRL_COM_SRST_STATUS_com_g2_srst_status_END          (1)
#define BBPSCTRL_COM_SRST_STATUS_com_g_sdr_srst_status_START     (3)
#define BBPSCTRL_COM_SRST_STATUS_com_g_sdr_srst_status_END       (3)
#define BBPSCTRL_COM_SRST_STATUS_com_l_sdr_srst_status_START     (4)
#define BBPSCTRL_COM_SRST_STATUS_com_l_sdr_srst_status_END       (4)
#define BBPSCTRL_COM_SRST_STATUS_com_tl_dma_srst_status_START    (5)
#define BBPSCTRL_COM_SRST_STATUS_com_tl_dma_srst_status_END      (5)
#define BBPSCTRL_COM_SRST_STATUS_com_tl_dbg_srst_status_START    (6)
#define BBPSCTRL_COM_SRST_STATUS_com_tl_dbg_srst_status_END      (6)
#define BBPSCTRL_COM_SRST_STATUS_com_gu_mst_srst_status_START    (7)
#define BBPSCTRL_COM_SRST_STATUS_com_gu_mst_srst_status_END      (7)
#define BBPSCTRL_COM_SRST_STATUS_com_et_srst_status_START        (9)
#define BBPSCTRL_COM_SRST_STATUS_com_et_srst_status_END          (9)
#define BBPSCTRL_COM_SRST_STATUS_com_cs_srst_status_START        (10)
#define BBPSCTRL_COM_SRST_STATUS_com_cs_srst_status_END          (10)
#define BBPSCTRL_COM_SRST_STATUS_com_sys_srst_status_START       (11)
#define BBPSCTRL_COM_SRST_STATUS_com_sys_srst_status_END         (11)
#define BBPSCTRL_COM_SRST_STATUS_com_lte_cs_srst_status_START    (12)
#define BBPSCTRL_COM_SRST_STATUS_com_lte_cs_srst_status_END      (12)
#define BBPSCTRL_COM_SRST_STATUS_com_wc_srst_status_START        (13)
#define BBPSCTRL_COM_SRST_STATUS_com_wc_srst_status_END          (13)
#define BBPSCTRL_COM_SRST_STATUS_com_uc2_122m_srst_status_START  (14)
#define BBPSCTRL_COM_SRST_STATUS_com_uc2_122m_srst_status_END    (14)
#define BBPSCTRL_COM_SRST_STATUS_com_dbg_trig_srst_status_START  (15)
#define BBPSCTRL_COM_SRST_STATUS_com_dbg_trig_srst_status_END    (15)
#define BBPSCTRL_COM_SRST_STATUS_com_et_sub_srst_status_START    (19)
#define BBPSCTRL_COM_SRST_STATUS_com_et_sub_srst_status_END      (19)
#define BBPSCTRL_COM_SRST_STATUS_com_mipi_srst_status_START      (22)
#define BBPSCTRL_COM_SRST_STATUS_com_mipi_srst_status_END        (22)
#define BBPSCTRL_COM_SRST_STATUS_com_guc_dbg_srst_status_START   (23)
#define BBPSCTRL_COM_SRST_STATUS_com_guc_dbg_srst_status_END     (23)
#define BBPSCTRL_COM_SRST_STATUS_com_w_sys_srst_status_START     (24)
#define BBPSCTRL_COM_SRST_STATUS_com_w_sys_srst_status_END       (24)
#define BBPSCTRL_COM_SRST_STATUS_com_t_sys_srst_status_START     (25)
#define BBPSCTRL_COM_SRST_STATUS_com_t_sys_srst_status_END       (25)
#define BBPSCTRL_COM_SRST_STATUS_com_c_sys_srst_status_START     (26)
#define BBPSCTRL_COM_SRST_STATUS_com_c_sys_srst_status_END       (26)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_MTCMOS_SET_DSP_UNION
 �ṹ˵��  : BBP_MTCMOS_SET_DSP �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ����ʹ��(DSP��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_mtcmos_set_dsp_reg;
    struct
    {
        unsigned int  lte_mtcmos_ctrl_set : 1;  /* bit[0]   : LTE��Դ���ϵ���λ��
                                                              д1��λ��д0��Ч�� */
        unsigned int  wtc_mtcmos_ctrl_set : 1;  /* bit[1]   : WTC��Դ���ϵ���λ��
                                                              д1��λ��д0��Ч�� */
        unsigned int  irm_mtcmos_ctrl_set : 1;  /* bit[2]   : IRM��Դ���ϵ���λ��
                                                              д1��λ��д0��Ч�� */
        unsigned int  reserved            : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_MTCMOS_SET_DSP_UNION;
#define BBPSCTRL_BBP_MTCMOS_SET_DSP_lte_mtcmos_ctrl_set_START  (0)
#define BBPSCTRL_BBP_MTCMOS_SET_DSP_lte_mtcmos_ctrl_set_END    (0)
#define BBPSCTRL_BBP_MTCMOS_SET_DSP_wtc_mtcmos_ctrl_set_START  (1)
#define BBPSCTRL_BBP_MTCMOS_SET_DSP_wtc_mtcmos_ctrl_set_END    (1)
#define BBPSCTRL_BBP_MTCMOS_SET_DSP_irm_mtcmos_ctrl_set_START  (2)
#define BBPSCTRL_BBP_MTCMOS_SET_DSP_irm_mtcmos_ctrl_set_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_MTCMOS_CLR_DSP_UNION
 �ṹ˵��  : BBP_MTCMOS_CLR_DSP �Ĵ����ṹ���塣��ַƫ����:0x0104����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ���ƹر�(DSP��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_mtcmos_clr_dsp_reg;
    struct
    {
        unsigned int  lte_mtcmos_ctrl_clr : 1;  /* bit[0]   : LTE��Դ���ϵ������
                                                              д1���㣬д0��Ч�� */
        unsigned int  wtc_mtcmos_ctrl_clr : 1;  /* bit[1]   : WTC��Դ���ϵ������
                                                              д1���㣬д0��Ч�� */
        unsigned int  irm_mtcmos_ctrl_clr : 1;  /* bit[2]   : IRM��Դ���ϵ������
                                                              д1���㣬д0��Ч�� */
        unsigned int  reserved            : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_MTCMOS_CLR_DSP_UNION;
#define BBPSCTRL_BBP_MTCMOS_CLR_DSP_lte_mtcmos_ctrl_clr_START  (0)
#define BBPSCTRL_BBP_MTCMOS_CLR_DSP_lte_mtcmos_ctrl_clr_END    (0)
#define BBPSCTRL_BBP_MTCMOS_CLR_DSP_wtc_mtcmos_ctrl_clr_START  (1)
#define BBPSCTRL_BBP_MTCMOS_CLR_DSP_wtc_mtcmos_ctrl_clr_END    (1)
#define BBPSCTRL_BBP_MTCMOS_CLR_DSP_irm_mtcmos_ctrl_clr_START  (2)
#define BBPSCTRL_BBP_MTCMOS_CLR_DSP_irm_mtcmos_ctrl_clr_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_MTCMOS_STATUS_DSP_UNION
 �ṹ˵��  : BBP_MTCMOS_STATUS_DSP �Ĵ����ṹ���塣��ַƫ����:0x0108����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ����״̬(DSP��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_mtcmos_status_dsp_reg;
    struct
    {
        unsigned int  lte_mtcmos_ctrl_status : 1;  /* bit[0]   : LTE��Դ���Դ״̬��
                                                                 1���ϵ�
                                                                 0���µ� */
        unsigned int  wtc_mtcmos_ctrl_status : 1;  /* bit[1]   : WTC��Դ���Դ״̬��
                                                                 1���ϵ�
                                                                 0���µ� */
        unsigned int  irm_mtcmos_ctrl_status : 1;  /* bit[2]   : IRM��Դ���Դ״̬��
                                                                 1���ϵ�
                                                                 0���µ� */
        unsigned int  reserved               : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_MTCMOS_STATUS_DSP_UNION;
#define BBPSCTRL_BBP_MTCMOS_STATUS_DSP_lte_mtcmos_ctrl_status_START  (0)
#define BBPSCTRL_BBP_MTCMOS_STATUS_DSP_lte_mtcmos_ctrl_status_END    (0)
#define BBPSCTRL_BBP_MTCMOS_STATUS_DSP_wtc_mtcmos_ctrl_status_START  (1)
#define BBPSCTRL_BBP_MTCMOS_STATUS_DSP_wtc_mtcmos_ctrl_status_END    (1)
#define BBPSCTRL_BBP_MTCMOS_STATUS_DSP_irm_mtcmos_ctrl_status_START  (2)
#define BBPSCTRL_BBP_MTCMOS_STATUS_DSP_irm_mtcmos_ctrl_status_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_ISO_EN_SET_DSP_UNION
 �ṹ˵��  : BBP_ISO_EN_SET_DSP �Ĵ����ṹ���塣��ַƫ����:0x0110����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ�������ʹ��(DSP��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_iso_en_set_dsp_reg;
    struct
    {
        unsigned int  lte_iso_en_set : 1;  /* bit[0]   : LTE��Դ�������λ��
                                                         д1��λ��д0��Ч�� */
        unsigned int  wtc_iso_en_set : 1;  /* bit[1]   : WTC��Դ�������λ��
                                                         д1��λ��д0��Ч�� */
        unsigned int  irm_iso_en_set : 1;  /* bit[2]   : IRM��Դ�������λ��
                                                         д1��λ��д0��Ч�� */
        unsigned int  reserved       : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_ISO_EN_SET_DSP_UNION;
#define BBPSCTRL_BBP_ISO_EN_SET_DSP_lte_iso_en_set_START  (0)
#define BBPSCTRL_BBP_ISO_EN_SET_DSP_lte_iso_en_set_END    (0)
#define BBPSCTRL_BBP_ISO_EN_SET_DSP_wtc_iso_en_set_START  (1)
#define BBPSCTRL_BBP_ISO_EN_SET_DSP_wtc_iso_en_set_END    (1)
#define BBPSCTRL_BBP_ISO_EN_SET_DSP_irm_iso_en_set_START  (2)
#define BBPSCTRL_BBP_ISO_EN_SET_DSP_irm_iso_en_set_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_ISO_EN_CLR_DSP_UNION
 �ṹ˵��  : BBP_ISO_EN_CLR_DSP �Ĵ����ṹ���塣��ַƫ����:0x0114����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ������ƹر�(DSP��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_iso_en_clr_dsp_reg;
    struct
    {
        unsigned int  lte_iso_en_clr : 1;  /* bit[0]   : LTE��Դ����������
                                                         д1���㣬д0��Ч�� */
        unsigned int  wtc_iso_en_clr : 1;  /* bit[1]   : WTC��Դ����������
                                                         д1���㣬д0��Ч�� */
        unsigned int  irm_iso_en_clr : 1;  /* bit[2]   : IRM��Դ����������
                                                         д1���㣬д0��Ч�� */
        unsigned int  reserved       : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_ISO_EN_CLR_DSP_UNION;
#define BBPSCTRL_BBP_ISO_EN_CLR_DSP_lte_iso_en_clr_START  (0)
#define BBPSCTRL_BBP_ISO_EN_CLR_DSP_lte_iso_en_clr_END    (0)
#define BBPSCTRL_BBP_ISO_EN_CLR_DSP_wtc_iso_en_clr_START  (1)
#define BBPSCTRL_BBP_ISO_EN_CLR_DSP_wtc_iso_en_clr_END    (1)
#define BBPSCTRL_BBP_ISO_EN_CLR_DSP_irm_iso_en_clr_START  (2)
#define BBPSCTRL_BBP_ISO_EN_CLR_DSP_irm_iso_en_clr_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_ISO_EN_STATUS_DSP_UNION
 �ṹ˵��  : BBP_ISO_EN_STATUS_DSP �Ĵ����ṹ���塣��ַƫ����:0x0118����ֵ:0x0000003F�����:32
 �Ĵ���˵��: BBP��Դ�������״̬(DSP��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_iso_en_status_dsp_reg;
    struct
    {
        unsigned int  lte_iso_en_status : 1;  /* bit[0]   : LTE��Դ�����״̬��
                                                            1�����룻
                                                            0��������룻 */
        unsigned int  wtc_iso_en_status : 1;  /* bit[1]   : WTC��Դ�����״̬��
                                                            1�����룻
                                                            0��������룻 */
        unsigned int  irm_iso_en_status : 1;  /* bit[2]   : IRM��Դ�����״̬��
                                                            1�����룻
                                                            0��������룻 */
        unsigned int  reserved          : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_ISO_EN_STATUS_DSP_UNION;
#define BBPSCTRL_BBP_ISO_EN_STATUS_DSP_lte_iso_en_status_START  (0)
#define BBPSCTRL_BBP_ISO_EN_STATUS_DSP_lte_iso_en_status_END    (0)
#define BBPSCTRL_BBP_ISO_EN_STATUS_DSP_wtc_iso_en_status_START  (1)
#define BBPSCTRL_BBP_ISO_EN_STATUS_DSP_wtc_iso_en_status_END    (1)
#define BBPSCTRL_BBP_ISO_EN_STATUS_DSP_irm_iso_en_status_START  (2)
#define BBPSCTRL_BBP_ISO_EN_STATUS_DSP_irm_iso_en_status_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_PD_CLK_SET_DSP_UNION
 �ṹ˵��  : BBP_PD_CLK_SET_DSP �Ĵ����ṹ���塣��ַƫ����:0x0120����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ��ʱ��ʹ��(DSP��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_clk_set_dsp_reg;
    struct
    {
        unsigned int  lte_pd_clk_ena : 1;  /* bit[0]   : LTE��Դ��ʱ��ʹ�ܡ�
                                                         д1��λ��д0��Ч�� */
        unsigned int  wtc_pd_clk_ena : 1;  /* bit[1]   : WTC��Դ��ʱ��ʹ�ܡ�
                                                         д1��λ��д0��Ч�� */
        unsigned int  irm_pd_clk_ena : 1;  /* bit[2]   : IRM��Դ��ʱ��ʹ�ܡ�
                                                         д1��λ��д0��Ч�� */
        unsigned int  reserved       : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_PD_CLK_SET_DSP_UNION;
#define BBPSCTRL_BBP_PD_CLK_SET_DSP_lte_pd_clk_ena_START  (0)
#define BBPSCTRL_BBP_PD_CLK_SET_DSP_lte_pd_clk_ena_END    (0)
#define BBPSCTRL_BBP_PD_CLK_SET_DSP_wtc_pd_clk_ena_START  (1)
#define BBPSCTRL_BBP_PD_CLK_SET_DSP_wtc_pd_clk_ena_END    (1)
#define BBPSCTRL_BBP_PD_CLK_SET_DSP_irm_pd_clk_ena_START  (2)
#define BBPSCTRL_BBP_PD_CLK_SET_DSP_irm_pd_clk_ena_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_PD_CLK_CLR_DSP_UNION
 �ṹ˵��  : BBP_PD_CLK_CLR_DSP �Ĵ����ṹ���塣��ַƫ����:0x0124����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ��ʱ�ӹر�(DSP��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_clk_clr_dsp_reg;
    struct
    {
        unsigned int  lte_pd_clk_dis : 1;  /* bit[0]   : LTE��Դ��ʱ�ӹرա�
                                                         д1�رգ�д0��Ч�� */
        unsigned int  wtc_pd_clk_dis : 1;  /* bit[1]   : WTC��Դ��ʱ�ӹرա�
                                                         д1�رգ�д0��Ч�� */
        unsigned int  irm_pd_clk_dis : 1;  /* bit[2]   : IRM��Դ��ʱ�ӹرա�
                                                         д1�رգ�д0��Ч�� */
        unsigned int  reserved       : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_PD_CLK_CLR_DSP_UNION;
#define BBPSCTRL_BBP_PD_CLK_CLR_DSP_lte_pd_clk_dis_START  (0)
#define BBPSCTRL_BBP_PD_CLK_CLR_DSP_lte_pd_clk_dis_END    (0)
#define BBPSCTRL_BBP_PD_CLK_CLR_DSP_wtc_pd_clk_dis_START  (1)
#define BBPSCTRL_BBP_PD_CLK_CLR_DSP_wtc_pd_clk_dis_END    (1)
#define BBPSCTRL_BBP_PD_CLK_CLR_DSP_irm_pd_clk_dis_START  (2)
#define BBPSCTRL_BBP_PD_CLK_CLR_DSP_irm_pd_clk_dis_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_PD_CLK_STATUS_DSP_UNION
 �ṹ˵��  : BBP_PD_CLK_STATUS_DSP �Ĵ����ṹ���塣��ַƫ����:0x0128����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ��ʱ���ſ�״̬(DSP��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_clk_status_dsp_reg;
    struct
    {
        unsigned int  lte_pd_clk_status : 1;  /* bit[0]   : LTE��Դ��ʱ��״̬��
                                                            1��ʱ��ʹ��
                                                            0��ʱ�ӹر� */
        unsigned int  wtc_pd_clk_status : 1;  /* bit[1]   : WTC��Դ��ʱ��״̬��
                                                            1��ʱ��ʹ��
                                                            0��ʱ�ӹر� */
        unsigned int  irm_pd_clk_status : 1;  /* bit[2]   : IRM��Դ��ʱ��״̬��
                                                            1��ʱ��ʹ��
                                                            0��ʱ�ӹر� */
        unsigned int  reserved          : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_PD_CLK_STATUS_DSP_UNION;
#define BBPSCTRL_BBP_PD_CLK_STATUS_DSP_lte_pd_clk_status_START  (0)
#define BBPSCTRL_BBP_PD_CLK_STATUS_DSP_lte_pd_clk_status_END    (0)
#define BBPSCTRL_BBP_PD_CLK_STATUS_DSP_wtc_pd_clk_status_START  (1)
#define BBPSCTRL_BBP_PD_CLK_STATUS_DSP_wtc_pd_clk_status_END    (1)
#define BBPSCTRL_BBP_PD_CLK_STATUS_DSP_irm_pd_clk_status_START  (2)
#define BBPSCTRL_BBP_PD_CLK_STATUS_DSP_irm_pd_clk_status_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_PD_SRST_SET_DSP_UNION
 �ṹ˵��  : BBP_PD_SRST_SET_DSP �Ĵ����ṹ���塣��ַƫ����:0x0130����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ��λ����ʹ��(DSP��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_srst_set_dsp_reg;
    struct
    {
        unsigned int  lte_pd_srst_req : 1;  /* bit[0]   : LTE��Դ��λ����
                                                          д1��λ��д0��Ч�� */
        unsigned int  wtc_pd_srst_req : 1;  /* bit[1]   : WTC��Դ��λ����
                                                          д1��λ��д0��Ч�� */
        unsigned int  irm_pd_srst_req : 1;  /* bit[2]   : IRM��Դ��λ����
                                                          д1��λ��д0��Ч�� */
        unsigned int  reserved        : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_PD_SRST_SET_DSP_UNION;
#define BBPSCTRL_BBP_PD_SRST_SET_DSP_lte_pd_srst_req_START  (0)
#define BBPSCTRL_BBP_PD_SRST_SET_DSP_lte_pd_srst_req_END    (0)
#define BBPSCTRL_BBP_PD_SRST_SET_DSP_wtc_pd_srst_req_START  (1)
#define BBPSCTRL_BBP_PD_SRST_SET_DSP_wtc_pd_srst_req_END    (1)
#define BBPSCTRL_BBP_PD_SRST_SET_DSP_irm_pd_srst_req_START  (2)
#define BBPSCTRL_BBP_PD_SRST_SET_DSP_irm_pd_srst_req_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_PD_SRST_CLR_DSP_UNION
 �ṹ˵��  : BBP_PD_SRST_CLR_DSP �Ĵ����ṹ���塣��ַƫ����:0x0134����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ��λ����ر�(DSP��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_srst_clr_dsp_reg;
    struct
    {
        unsigned int  lte_pd_srst_dis : 1;  /* bit[0]   : LTE��Դ��λ�����
                                                          д1�����λ��д0��Ч�� */
        unsigned int  wtc_pd_srst_dis : 1;  /* bit[1]   : WTC��Դ��λ�����
                                                          д1�����λ��д0��Ч�� */
        unsigned int  irm_pd_srst_dis : 1;  /* bit[2]   : IRM��Դ��λ�����
                                                          д1�����λ��д0��Ч�� */
        unsigned int  reserved        : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_PD_SRST_CLR_DSP_UNION;
#define BBPSCTRL_BBP_PD_SRST_CLR_DSP_lte_pd_srst_dis_START  (0)
#define BBPSCTRL_BBP_PD_SRST_CLR_DSP_lte_pd_srst_dis_END    (0)
#define BBPSCTRL_BBP_PD_SRST_CLR_DSP_wtc_pd_srst_dis_START  (1)
#define BBPSCTRL_BBP_PD_SRST_CLR_DSP_wtc_pd_srst_dis_END    (1)
#define BBPSCTRL_BBP_PD_SRST_CLR_DSP_irm_pd_srst_dis_START  (2)
#define BBPSCTRL_BBP_PD_SRST_CLR_DSP_irm_pd_srst_dis_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_PD_SRST_STATUS_DSP_UNION
 �ṹ˵��  : BBP_PD_SRST_STATUS_DSP �Ĵ����ṹ���塣��ַƫ����:0x0138����ֵ:0x00000007�����:32
 �Ĵ���˵��: BBP��Դ��λ����״̬(DSP��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_pd_srst_status_dsp_reg;
    struct
    {
        unsigned int  lte_pd_srst_status : 1;  /* bit[0]   : LTE��Դ��λ״̬��
                                                             1����λ��
                                                             0�������λ�� */
        unsigned int  wtc_pd_srst_status : 1;  /* bit[1]   : WTC��Դ��λ״̬��
                                                             1����λ��
                                                             0�������λ�� */
        unsigned int  irm_pd_srst_status : 1;  /* bit[2]   : IRM��Դ��λ״̬��
                                                             1����λ��
                                                             0�������λ�� */
        unsigned int  reserved           : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_PD_SRST_STATUS_DSP_UNION;
#define BBPSCTRL_BBP_PD_SRST_STATUS_DSP_lte_pd_srst_status_START  (0)
#define BBPSCTRL_BBP_PD_SRST_STATUS_DSP_lte_pd_srst_status_END    (0)
#define BBPSCTRL_BBP_PD_SRST_STATUS_DSP_wtc_pd_srst_status_START  (1)
#define BBPSCTRL_BBP_PD_SRST_STATUS_DSP_wtc_pd_srst_status_END    (1)
#define BBPSCTRL_BBP_PD_SRST_STATUS_DSP_irm_pd_srst_status_START  (2)
#define BBPSCTRL_BBP_PD_SRST_STATUS_DSP_irm_pd_srst_status_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_SCTRL1f_SET_UNION
 �ṹ˵��  : BBP_SCTRL1f_SET �Ĵ����ṹ���塣��ַƫ����:0x01F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBPϵͳ������1F��λ(PD PWR AND PD CLK FORCE ENA)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctrl1f_set_reg;
    struct
    {
        unsigned int  lte_pd_pwr_force_ena : 1;  /* bit[0]    : д1��ǿ���ϵ硣 */
        unsigned int  wtc_pd_pwr_force_ena : 1;  /* bit[1]    : д1��ǿ���ϵ硣 */
        unsigned int  irm_pd_pwr_force_ena : 1;  /* bit[2]    : д1��ǿ���ϵ硣 */
        unsigned int  reserved_0           : 1;  /* bit[3]    :  */
        unsigned int  lte_pd_iso_force_dis : 1;  /* bit[4]    : д1��ǿ�ƽ���롣 */
        unsigned int  wtc_pd_iso_force_dis : 1;  /* bit[5]    : д1��ǿ�ƽ���롣 */
        unsigned int  irm_pd_iso_force_dis : 1;  /* bit[6]    : д1��ǿ�ƽ���롣 */
        unsigned int  reserved_1           : 1;  /* bit[7]    :  */
        unsigned int  wtc_pd_clk_force_ena : 1;  /* bit[8]    : д1��ǿ�ƿ��ӡ� */
        unsigned int  lte_pd_clk_force_ena : 1;  /* bit[9]    : д1��ǿ�ƿ��ӡ� */
        unsigned int  irm_pd_clk_force_ena : 1;  /* bit[10]   : д1��ǿ�ƿ��ӡ� */
        unsigned int  reserved_2           : 1;  /* bit[11]   :  */
        unsigned int  lte_pd_rst_force_ena : 1;  /* bit[12]   : д1��ǿ�ƽ⸴λ�� */
        unsigned int  wtc_pd_rst_force_ena : 1;  /* bit[13]   : д1��ǿ�ƽ⸴λ�� */
        unsigned int  irm_pd_rst_force_ena : 1;  /* bit[14]   : д1��ǿ�ƽ⸴λ�� */
        unsigned int  reserved_3           : 17; /* bit[15-31]: ������Debugʹ�á� */
    } reg;
} BBPSCTRL_BBP_SCTRL1f_SET_UNION;
#define BBPSCTRL_BBP_SCTRL1f_SET_lte_pd_pwr_force_ena_START  (0)
#define BBPSCTRL_BBP_SCTRL1f_SET_lte_pd_pwr_force_ena_END    (0)
#define BBPSCTRL_BBP_SCTRL1f_SET_wtc_pd_pwr_force_ena_START  (1)
#define BBPSCTRL_BBP_SCTRL1f_SET_wtc_pd_pwr_force_ena_END    (1)
#define BBPSCTRL_BBP_SCTRL1f_SET_irm_pd_pwr_force_ena_START  (2)
#define BBPSCTRL_BBP_SCTRL1f_SET_irm_pd_pwr_force_ena_END    (2)
#define BBPSCTRL_BBP_SCTRL1f_SET_lte_pd_iso_force_dis_START  (4)
#define BBPSCTRL_BBP_SCTRL1f_SET_lte_pd_iso_force_dis_END    (4)
#define BBPSCTRL_BBP_SCTRL1f_SET_wtc_pd_iso_force_dis_START  (5)
#define BBPSCTRL_BBP_SCTRL1f_SET_wtc_pd_iso_force_dis_END    (5)
#define BBPSCTRL_BBP_SCTRL1f_SET_irm_pd_iso_force_dis_START  (6)
#define BBPSCTRL_BBP_SCTRL1f_SET_irm_pd_iso_force_dis_END    (6)
#define BBPSCTRL_BBP_SCTRL1f_SET_wtc_pd_clk_force_ena_START  (8)
#define BBPSCTRL_BBP_SCTRL1f_SET_wtc_pd_clk_force_ena_END    (8)
#define BBPSCTRL_BBP_SCTRL1f_SET_lte_pd_clk_force_ena_START  (9)
#define BBPSCTRL_BBP_SCTRL1f_SET_lte_pd_clk_force_ena_END    (9)
#define BBPSCTRL_BBP_SCTRL1f_SET_irm_pd_clk_force_ena_START  (10)
#define BBPSCTRL_BBP_SCTRL1f_SET_irm_pd_clk_force_ena_END    (10)
#define BBPSCTRL_BBP_SCTRL1f_SET_lte_pd_rst_force_ena_START  (12)
#define BBPSCTRL_BBP_SCTRL1f_SET_lte_pd_rst_force_ena_END    (12)
#define BBPSCTRL_BBP_SCTRL1f_SET_wtc_pd_rst_force_ena_START  (13)
#define BBPSCTRL_BBP_SCTRL1f_SET_wtc_pd_rst_force_ena_END    (13)
#define BBPSCTRL_BBP_SCTRL1f_SET_irm_pd_rst_force_ena_START  (14)
#define BBPSCTRL_BBP_SCTRL1f_SET_irm_pd_rst_force_ena_END    (14)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_SCTR20_UNION
 �ṹ˵��  : BBP_SCTR20 �Ĵ����ṹ���塣��ַƫ����:0x0200����ֵ:0x02222222�����:32
 �Ĵ���˵��: LBUS����������
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctr20_reg;
    struct
    {
        unsigned int  ulhb_bypass       : 1;  /* bit[0]    :  */
        unsigned int  ulhb_rd_prot      : 2;  /* bit[1-2]  :  */
        unsigned int  reserved_0        : 1;  /* bit[3]    :  */
        unsigned int  pdf_bypas         : 1;  /* bit[4]    :  */
        unsigned int  pdf_rd_prot       : 2;  /* bit[5-6]  :  */
        unsigned int  reserved_1        : 1;  /* bit[7]    :  */
        unsigned int  pdt_bypass        : 1;  /* bit[8]    :  */
        unsigned int  pdt_rd_prot       : 2;  /* bit[9-10] :  */
        unsigned int  reserved_2        : 1;  /* bit[11]   :  */
        unsigned int  tds245_bypass     : 1;  /* bit[12]   :  */
        unsigned int  tds245_rd_prot    : 2;  /* bit[13-14]:  */
        unsigned int  reserved_3        : 1;  /* bit[15]   :  */
        unsigned int  ux_tds122_bypass  : 1;  /* bit[16]   :  */
        unsigned int  ux_tds122_rd_prot : 2;  /* bit[17-18]:  */
        unsigned int  reserved_4        : 1;  /* bit[19]   :  */
        unsigned int  g_bypass          : 1;  /* bit[20]   :  */
        unsigned int  g_rd_prot         : 2;  /* bit[21-22]:  */
        unsigned int  reserved_5        : 1;  /* bit[23]   :  */
        unsigned int  uc2_bypass        : 1;  /* bit[24]   :  */
        unsigned int  uc2_rd_prot       : 2;  /* bit[25-26]:  */
        unsigned int  reserved_6        : 5;  /* bit[27-31]: ������ */
    } reg;
} BBPSCTRL_BBP_SCTR20_UNION;
#define BBPSCTRL_BBP_SCTR20_ulhb_bypass_START        (0)
#define BBPSCTRL_BBP_SCTR20_ulhb_bypass_END          (0)
#define BBPSCTRL_BBP_SCTR20_ulhb_rd_prot_START       (1)
#define BBPSCTRL_BBP_SCTR20_ulhb_rd_prot_END         (2)
#define BBPSCTRL_BBP_SCTR20_pdf_bypas_START          (4)
#define BBPSCTRL_BBP_SCTR20_pdf_bypas_END            (4)
#define BBPSCTRL_BBP_SCTR20_pdf_rd_prot_START        (5)
#define BBPSCTRL_BBP_SCTR20_pdf_rd_prot_END          (6)
#define BBPSCTRL_BBP_SCTR20_pdt_bypass_START         (8)
#define BBPSCTRL_BBP_SCTR20_pdt_bypass_END           (8)
#define BBPSCTRL_BBP_SCTR20_pdt_rd_prot_START        (9)
#define BBPSCTRL_BBP_SCTR20_pdt_rd_prot_END          (10)
#define BBPSCTRL_BBP_SCTR20_tds245_bypass_START      (12)
#define BBPSCTRL_BBP_SCTR20_tds245_bypass_END        (12)
#define BBPSCTRL_BBP_SCTR20_tds245_rd_prot_START     (13)
#define BBPSCTRL_BBP_SCTR20_tds245_rd_prot_END       (14)
#define BBPSCTRL_BBP_SCTR20_ux_tds122_bypass_START   (16)
#define BBPSCTRL_BBP_SCTR20_ux_tds122_bypass_END     (16)
#define BBPSCTRL_BBP_SCTR20_ux_tds122_rd_prot_START  (17)
#define BBPSCTRL_BBP_SCTR20_ux_tds122_rd_prot_END    (18)
#define BBPSCTRL_BBP_SCTR20_g_bypass_START           (20)
#define BBPSCTRL_BBP_SCTR20_g_bypass_END             (20)
#define BBPSCTRL_BBP_SCTR20_g_rd_prot_START          (21)
#define BBPSCTRL_BBP_SCTR20_g_rd_prot_END            (22)
#define BBPSCTRL_BBP_SCTR20_uc2_bypass_START         (24)
#define BBPSCTRL_BBP_SCTR20_uc2_bypass_END           (24)
#define BBPSCTRL_BBP_SCTR20_uc2_rd_prot_START        (25)
#define BBPSCTRL_BBP_SCTR20_uc2_rd_prot_END          (26)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_SCTR21_UNION
 �ṹ˵��  : BBP_SCTR21 �Ĵ����ṹ���塣��ַƫ����:0x0204����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBPϵͳ������21(dw_axi_bbp ����)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctr21_reg;
    struct
    {
        unsigned int  mst_priority_update  : 1;  /* bit[0]    :  */
        unsigned int  xdcdr_sel            : 1;  /* bit[1]    :  */
        unsigned int  mst_err_srst_req     : 1;  /* bit[2]    :  */
        unsigned int  slv_active           : 2;  /* bit[3-4]  :  */
        unsigned int  mst_priority_m1      : 2;  /* bit[5-6]  :  */
        unsigned int  mst_priority_m2      : 2;  /* bit[7-8]  :  */
        unsigned int  mst_priority_m3      : 2;  /* bit[9-10] :  */
        unsigned int  mst_priority_m4      : 2;  /* bit[11-12]:  */
        unsigned int  dw_axi_gatedclock_en : 1;  /* bit[13]   :  */
        unsigned int  reserved             : 18; /* bit[14-31]: ������ */
    } reg;
} BBPSCTRL_BBP_SCTR21_UNION;
#define BBPSCTRL_BBP_SCTR21_mst_priority_update_START   (0)
#define BBPSCTRL_BBP_SCTR21_mst_priority_update_END     (0)
#define BBPSCTRL_BBP_SCTR21_xdcdr_sel_START             (1)
#define BBPSCTRL_BBP_SCTR21_xdcdr_sel_END               (1)
#define BBPSCTRL_BBP_SCTR21_mst_err_srst_req_START      (2)
#define BBPSCTRL_BBP_SCTR21_mst_err_srst_req_END        (2)
#define BBPSCTRL_BBP_SCTR21_slv_active_START            (3)
#define BBPSCTRL_BBP_SCTR21_slv_active_END              (4)
#define BBPSCTRL_BBP_SCTR21_mst_priority_m1_START       (5)
#define BBPSCTRL_BBP_SCTR21_mst_priority_m1_END         (6)
#define BBPSCTRL_BBP_SCTR21_mst_priority_m2_START       (7)
#define BBPSCTRL_BBP_SCTR21_mst_priority_m2_END         (8)
#define BBPSCTRL_BBP_SCTR21_mst_priority_m3_START       (9)
#define BBPSCTRL_BBP_SCTR21_mst_priority_m3_END         (10)
#define BBPSCTRL_BBP_SCTR21_mst_priority_m4_START       (11)
#define BBPSCTRL_BBP_SCTR21_mst_priority_m4_END         (12)
#define BBPSCTRL_BBP_SCTR21_dw_axi_gatedclock_en_START  (13)
#define BBPSCTRL_BBP_SCTR21_dw_axi_gatedclock_en_END    (13)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_SCTR22_UNION
 �ṹ˵��  : BBP_SCTR22 �Ĵ����ṹ���塣��ַƫ����:0x0208����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBPϵͳ������22(dw_axi_bbp dlock)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctr22_reg;
    struct
    {
        unsigned int  dlock_cnt_update : 1;  /* bit[0]   : �Ĵ���23��Ӧ��dlock����update */
        unsigned int  reserved         : 31; /* bit[1-31]: ������ */
    } reg;
} BBPSCTRL_BBP_SCTR22_UNION;
#define BBPSCTRL_BBP_SCTR22_dlock_cnt_update_START  (0)
#define BBPSCTRL_BBP_SCTR22_dlock_cnt_update_END    (0)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_SCTR23_UNION
 �ṹ˵��  : BBP_SCTR23 �Ĵ����ṹ���塣��ַƫ����:0x020C����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBPϵͳ������23(dw_axi_bbp_dlock)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctr23_reg;
    struct
    {
        unsigned int  dlock_cnt_clk_div_num : 8;  /* bit[0-7]  : ����ʹ�á� */
        unsigned int  reserved              : 8;  /* bit[8-15] : ���� */
        unsigned int  dlock_cnt_max         : 16; /* bit[16-31]: ����ʹ�á� */
    } reg;
} BBPSCTRL_BBP_SCTR23_UNION;
#define BBPSCTRL_BBP_SCTR23_dlock_cnt_clk_div_num_START  (0)
#define BBPSCTRL_BBP_SCTR23_dlock_cnt_clk_div_num_END    (7)
#define BBPSCTRL_BBP_SCTR23_dlock_cnt_max_START          (16)
#define BBPSCTRL_BBP_SCTR23_dlock_cnt_max_END            (31)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_SCTR24_UNION
 �ṹ˵��  : BBP_SCTR24 �Ĵ����ṹ���塣��ַƫ����:0x0210����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBPϵͳ������24(LBUS���߷������ж�����)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctr24_reg;
    struct
    {
        unsigned int  ulhb_err_power_int_mask           : 1;  /* bit[0] : 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  ulhb_err_clk_int_mask             : 1;  /* bit[1] : 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  ulhb_err_rst_int_mask             : 1;  /* bit[2] : 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  ulhb_err_rd_timeout_int_mask      : 1;  /* bit[3] : 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  pdf_err_power_int_mask            : 1;  /* bit[4] : 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  pdf_err_clk_int_mask              : 1;  /* bit[5] : 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  pdf_err_rst_int_mask              : 1;  /* bit[6] : 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  pdf_err_rd_timeout_int_mask       : 1;  /* bit[7] : 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  pdt_err_power_int_mask            : 1;  /* bit[8] : 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  pdt_err_clk_int_mask              : 1;  /* bit[9] : 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  pdt_err_rst_int_mask              : 1;  /* bit[10]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  pdt_err_rd_timeout_int_mask       : 1;  /* bit[11]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  tds245_err_power_int_mask         : 1;  /* bit[12]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  tds245_err_clk_int_mask           : 1;  /* bit[13]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  tds245_err_rst_int_mask           : 1;  /* bit[14]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  tds245_err_rd_timeout_int_mask    : 1;  /* bit[15]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  ux_tds122_err_power_int_mask      : 1;  /* bit[16]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  ux_tds122_err_clk_int_mask        : 1;  /* bit[17]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  ux_tds122_err_rst_int_mask        : 1;  /* bit[18]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  ux_tds122_err_rd_timeout_int_mask : 1;  /* bit[19]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  g_err_clk_int_mask                : 1;  /* bit[20]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  g_err_rst_int_mask                : 1;  /* bit[21]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  g_err_rd_timeout_int_mask         : 1;  /* bit[22]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  b2s_err_rd_timeout_int_mask       : 1;  /* bit[23]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  uc2_err_power_int_mask            : 1;  /* bit[24]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  uc2_err_clk_int_mask              : 1;  /* bit[25]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  uc2_err_rst_int_mask              : 1;  /* bit[26]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  uc2_err_rd_timeout_int_mask       : 1;  /* bit[27]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  axi_arb_overtime_int_mask         : 1;  /* bit[28]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  dma_arb_overtime_int_mask         : 1;  /* bit[29]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  dbgtrig_arb_overtime_int_mask     : 1;  /* bit[30]: 0���ж�������Ч��
                                                                          1���ж�����ʹ�ܡ� */
        unsigned int  reserved                          : 1;  /* bit[31]: ������ */
    } reg;
} BBPSCTRL_BBP_SCTR24_UNION;
#define BBPSCTRL_BBP_SCTR24_ulhb_err_power_int_mask_START            (0)
#define BBPSCTRL_BBP_SCTR24_ulhb_err_power_int_mask_END              (0)
#define BBPSCTRL_BBP_SCTR24_ulhb_err_clk_int_mask_START              (1)
#define BBPSCTRL_BBP_SCTR24_ulhb_err_clk_int_mask_END                (1)
#define BBPSCTRL_BBP_SCTR24_ulhb_err_rst_int_mask_START              (2)
#define BBPSCTRL_BBP_SCTR24_ulhb_err_rst_int_mask_END                (2)
#define BBPSCTRL_BBP_SCTR24_ulhb_err_rd_timeout_int_mask_START       (3)
#define BBPSCTRL_BBP_SCTR24_ulhb_err_rd_timeout_int_mask_END         (3)
#define BBPSCTRL_BBP_SCTR24_pdf_err_power_int_mask_START             (4)
#define BBPSCTRL_BBP_SCTR24_pdf_err_power_int_mask_END               (4)
#define BBPSCTRL_BBP_SCTR24_pdf_err_clk_int_mask_START               (5)
#define BBPSCTRL_BBP_SCTR24_pdf_err_clk_int_mask_END                 (5)
#define BBPSCTRL_BBP_SCTR24_pdf_err_rst_int_mask_START               (6)
#define BBPSCTRL_BBP_SCTR24_pdf_err_rst_int_mask_END                 (6)
#define BBPSCTRL_BBP_SCTR24_pdf_err_rd_timeout_int_mask_START        (7)
#define BBPSCTRL_BBP_SCTR24_pdf_err_rd_timeout_int_mask_END          (7)
#define BBPSCTRL_BBP_SCTR24_pdt_err_power_int_mask_START             (8)
#define BBPSCTRL_BBP_SCTR24_pdt_err_power_int_mask_END               (8)
#define BBPSCTRL_BBP_SCTR24_pdt_err_clk_int_mask_START               (9)
#define BBPSCTRL_BBP_SCTR24_pdt_err_clk_int_mask_END                 (9)
#define BBPSCTRL_BBP_SCTR24_pdt_err_rst_int_mask_START               (10)
#define BBPSCTRL_BBP_SCTR24_pdt_err_rst_int_mask_END                 (10)
#define BBPSCTRL_BBP_SCTR24_pdt_err_rd_timeout_int_mask_START        (11)
#define BBPSCTRL_BBP_SCTR24_pdt_err_rd_timeout_int_mask_END          (11)
#define BBPSCTRL_BBP_SCTR24_tds245_err_power_int_mask_START          (12)
#define BBPSCTRL_BBP_SCTR24_tds245_err_power_int_mask_END            (12)
#define BBPSCTRL_BBP_SCTR24_tds245_err_clk_int_mask_START            (13)
#define BBPSCTRL_BBP_SCTR24_tds245_err_clk_int_mask_END              (13)
#define BBPSCTRL_BBP_SCTR24_tds245_err_rst_int_mask_START            (14)
#define BBPSCTRL_BBP_SCTR24_tds245_err_rst_int_mask_END              (14)
#define BBPSCTRL_BBP_SCTR24_tds245_err_rd_timeout_int_mask_START     (15)
#define BBPSCTRL_BBP_SCTR24_tds245_err_rd_timeout_int_mask_END       (15)
#define BBPSCTRL_BBP_SCTR24_ux_tds122_err_power_int_mask_START       (16)
#define BBPSCTRL_BBP_SCTR24_ux_tds122_err_power_int_mask_END         (16)
#define BBPSCTRL_BBP_SCTR24_ux_tds122_err_clk_int_mask_START         (17)
#define BBPSCTRL_BBP_SCTR24_ux_tds122_err_clk_int_mask_END           (17)
#define BBPSCTRL_BBP_SCTR24_ux_tds122_err_rst_int_mask_START         (18)
#define BBPSCTRL_BBP_SCTR24_ux_tds122_err_rst_int_mask_END           (18)
#define BBPSCTRL_BBP_SCTR24_ux_tds122_err_rd_timeout_int_mask_START  (19)
#define BBPSCTRL_BBP_SCTR24_ux_tds122_err_rd_timeout_int_mask_END    (19)
#define BBPSCTRL_BBP_SCTR24_g_err_clk_int_mask_START                 (20)
#define BBPSCTRL_BBP_SCTR24_g_err_clk_int_mask_END                   (20)
#define BBPSCTRL_BBP_SCTR24_g_err_rst_int_mask_START                 (21)
#define BBPSCTRL_BBP_SCTR24_g_err_rst_int_mask_END                   (21)
#define BBPSCTRL_BBP_SCTR24_g_err_rd_timeout_int_mask_START          (22)
#define BBPSCTRL_BBP_SCTR24_g_err_rd_timeout_int_mask_END            (22)
#define BBPSCTRL_BBP_SCTR24_b2s_err_rd_timeout_int_mask_START        (23)
#define BBPSCTRL_BBP_SCTR24_b2s_err_rd_timeout_int_mask_END          (23)
#define BBPSCTRL_BBP_SCTR24_uc2_err_power_int_mask_START             (24)
#define BBPSCTRL_BBP_SCTR24_uc2_err_power_int_mask_END               (24)
#define BBPSCTRL_BBP_SCTR24_uc2_err_clk_int_mask_START               (25)
#define BBPSCTRL_BBP_SCTR24_uc2_err_clk_int_mask_END                 (25)
#define BBPSCTRL_BBP_SCTR24_uc2_err_rst_int_mask_START               (26)
#define BBPSCTRL_BBP_SCTR24_uc2_err_rst_int_mask_END                 (26)
#define BBPSCTRL_BBP_SCTR24_uc2_err_rd_timeout_int_mask_START        (27)
#define BBPSCTRL_BBP_SCTR24_uc2_err_rd_timeout_int_mask_END          (27)
#define BBPSCTRL_BBP_SCTR24_axi_arb_overtime_int_mask_START          (28)
#define BBPSCTRL_BBP_SCTR24_axi_arb_overtime_int_mask_END            (28)
#define BBPSCTRL_BBP_SCTR24_dma_arb_overtime_int_mask_START          (29)
#define BBPSCTRL_BBP_SCTR24_dma_arb_overtime_int_mask_END            (29)
#define BBPSCTRL_BBP_SCTR24_dbgtrig_arb_overtime_int_mask_START      (30)
#define BBPSCTRL_BBP_SCTR24_dbgtrig_arb_overtime_int_mask_END        (30)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_SCTR2A_UNION
 �ṹ˵��  : BBP_SCTR2A �Ĵ����ṹ���塣��ַƫ����:0x0228����ֵ:0x0000C148�����:32
 �Ĵ���˵��: BBPϵͳ������2A(BBPʱ��ѡ��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctr2a_reg;
    struct
    {
        unsigned int  uart_clk_sel           : 1;  /* bit[0]    : uartʱ��ѡ��
                                                                  1��ѡ��480MHz��Ƶ��
                                                                  0��ѡ��245MHz��Ƶ�� */
        unsigned int  mipi_clk_sel           : 1;  /* bit[1]    : mipiʱ����Դ��
                                                                  0��ѡ�� 19.2MHz ��עBBP�˿�����ʱ�ӣ�
                                                                  1��ѡ�� 40.96MHz��עBBP�ڲ�245MHz��Ƶʱ�ӣ� */
        unsigned int  scpll_sel              : 1;  /* bit[2]    : scpll_clkѡ���źţ�
                                                                  0����ʾѡ��bbppll_clk_sc0
                                                                  1����ʾѡ��bbppll_clk_sc1 */
        unsigned int  scpll_uc2_sel          : 1;  /* bit[3]    : scpll_uc2_clkѡ���źţ�
                                                                  0����ʾѡ��bbppll_clk_sc0
                                                                  1����ʾѡ��bbppll_clk_sc1 */
        unsigned int  pdt_clk_sel            : 1;  /* bit[4]    : bbp clkѡ��
                                                                  0��ѡ��122M;
                                                                  1��ѡ��245M�� */
        unsigned int  pdf_clk_sel            : 1;  /* bit[5]    : pdt clkѡ��
                                                                  0��ѡ��122M��
                                                                  1��ѡ��245M�� */
        unsigned int  tx0_clk_sel            : 2;  /* bit[6-7]  : LTE tx0 clkѡ��
                                                                  00��ѡ��245M(1��Ƶ)
                                                                  01��ѡ��122M(2��Ƶ��
                                                                  10��ѡ��61.44M(4��Ƶ)
                                                                  11��ѡ��30.72M(8��Ƶ) */
        unsigned int  tx1_clk_sel            : 2;  /* bit[8-9]  : LTE tx1 clkѡ��
                                                                  00��ѡ��245M(1��Ƶ)
                                                                  01��ѡ��122M(2��Ƶ��
                                                                  10��ѡ��61.44M(4��Ƶ)
                                                                  11��ѡ��30.72M(8��Ƶ) */
        unsigned int  ch0_tdl_clk_div_sel    : 1;  /* bit[10]   : ��ֵ����ʱ��Ƶ�ʳ����£�ch0 tdl clk��Ƶ������
                                                                  1��ch0��ʱ��480/240MHz(Ĭ��);
                                                                  0��ch0��ʱ��240/120MHz
                                                                  ע���ò����ڱ��Ĵ���bit20Ϊ0ʱ��Ч�� */
        unsigned int  ch1_tdl_clk_div_sel    : 1;  /* bit[11]   : ��ֵ����ʱ��Ƶ�ʳ����£�ch1 tdl clk��Ƶ������
                                                                  1��ch1��ʱ��480/240MHz(Ĭ��);
                                                                  0��ch1��ʱ��240/120MHz
                                                                  ע���ò����ڱ��Ĵ���bit20Ϊ0ʱ��Ч�� */
        unsigned int  reserved_0             : 2;  /* bit[12-13]: ���� */
        unsigned int  uart_clk_div_sel       : 5;  /* bit[14-18]: UART�ķ�Ƶ������ */
        unsigned int  bbp_tdl_clk_lte_irm_en : 1;  /* bit[19]   : bbp tdl clkʹ�ܡ���ʱ�����ڵ�Դ��ΪIRM/LTE��Դ�� */
        unsigned int  tdl_clk_div_ctrl_sw_en : 1;  /* bit[20]   : tdl����ʱ��Ƶ��120/240MHz����240/480MHzѡ���ź�,��bitΪ��
                                                                  0��ʹ�ñ��Ĵ�����ַbit��11:10�����������ֵ��ѡ�񡣣��ϵ縴λĬ�ϴ˷�ʽ��
                                                                  1��tdl�߼��˿�ѡ���źš� */
        unsigned int  bbp_irm_ps_ctrl_sel    : 1;  /* bit[21]   : 0: ѡ��AP��ĵ͹��Ŀ����ź�(Ĭ�ϣ��µ硢��λ���Ϊ��ֵ)��
                                                                  1��ѡ��BBP��ĵ͹��Ŀ����źš�
                                                                  Modemʹ��IRM��ʱ����Ҫ����Ϊ1. �� */
        unsigned int  reserved_1             : 10; /* bit[22-31]: ������ */
    } reg;
} BBPSCTRL_BBP_SCTR2A_UNION;
#define BBPSCTRL_BBP_SCTR2A_uart_clk_sel_START            (0)
#define BBPSCTRL_BBP_SCTR2A_uart_clk_sel_END              (0)
#define BBPSCTRL_BBP_SCTR2A_mipi_clk_sel_START            (1)
#define BBPSCTRL_BBP_SCTR2A_mipi_clk_sel_END              (1)
#define BBPSCTRL_BBP_SCTR2A_scpll_sel_START               (2)
#define BBPSCTRL_BBP_SCTR2A_scpll_sel_END                 (2)
#define BBPSCTRL_BBP_SCTR2A_scpll_uc2_sel_START           (3)
#define BBPSCTRL_BBP_SCTR2A_scpll_uc2_sel_END             (3)
#define BBPSCTRL_BBP_SCTR2A_pdt_clk_sel_START             (4)
#define BBPSCTRL_BBP_SCTR2A_pdt_clk_sel_END               (4)
#define BBPSCTRL_BBP_SCTR2A_pdf_clk_sel_START             (5)
#define BBPSCTRL_BBP_SCTR2A_pdf_clk_sel_END               (5)
#define BBPSCTRL_BBP_SCTR2A_tx0_clk_sel_START             (6)
#define BBPSCTRL_BBP_SCTR2A_tx0_clk_sel_END               (7)
#define BBPSCTRL_BBP_SCTR2A_tx1_clk_sel_START             (8)
#define BBPSCTRL_BBP_SCTR2A_tx1_clk_sel_END               (9)
#define BBPSCTRL_BBP_SCTR2A_ch0_tdl_clk_div_sel_START     (10)
#define BBPSCTRL_BBP_SCTR2A_ch0_tdl_clk_div_sel_END       (10)
#define BBPSCTRL_BBP_SCTR2A_ch1_tdl_clk_div_sel_START     (11)
#define BBPSCTRL_BBP_SCTR2A_ch1_tdl_clk_div_sel_END       (11)
#define BBPSCTRL_BBP_SCTR2A_uart_clk_div_sel_START        (14)
#define BBPSCTRL_BBP_SCTR2A_uart_clk_div_sel_END          (18)
#define BBPSCTRL_BBP_SCTR2A_bbp_tdl_clk_lte_irm_en_START  (19)
#define BBPSCTRL_BBP_SCTR2A_bbp_tdl_clk_lte_irm_en_END    (19)
#define BBPSCTRL_BBP_SCTR2A_tdl_clk_div_ctrl_sw_en_START  (20)
#define BBPSCTRL_BBP_SCTR2A_tdl_clk_div_ctrl_sw_en_END    (20)
#define BBPSCTRL_BBP_SCTR2A_bbp_irm_ps_ctrl_sel_START     (21)
#define BBPSCTRL_BBP_SCTR2A_bbp_irm_ps_ctrl_sel_END       (21)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_SCTR2D_UNION
 �ṹ˵��  : BBP_SCTR2D �Ĵ����ṹ���塣��ַƫ����:0x0234����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBPϵͳ������2D(REV)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctr2d_reg;
    struct
    {
        unsigned int  m1_mst_err_sel : 1;  /* bit[0]   : MST ERR״̬�ж�д��ַ��Ϣѡ��
                                                         0��ѡ�����ַ��
                                                         1��ѡ��д��ַ�� */
        unsigned int  m2_mst_err_sel : 1;  /* bit[1]   : MST ERR״̬�ж�д��ַ��Ϣѡ��
                                                         0��ѡ�����ַ��
                                                         1��ѡ��д��ַ�� */
        unsigned int  m3_mst_err_sel : 1;  /* bit[2]   : MST ERR״̬�ж�д��ַ��Ϣѡ��
                                                         0��ѡ�����ַ��
                                                         1��ѡ��д��ַ�� */
        unsigned int  m4_mst_err_sel : 1;  /* bit[3]   : MST ERR״̬�ж�д��ַ��Ϣѡ��
                                                         0��ѡ�����ַ��
                                                         1��ѡ��д��ַ�� */
        unsigned int  reserved       : 28; /* bit[4-31]: ������ */
    } reg;
} BBPSCTRL_BBP_SCTR2D_UNION;
#define BBPSCTRL_BBP_SCTR2D_m1_mst_err_sel_START  (0)
#define BBPSCTRL_BBP_SCTR2D_m1_mst_err_sel_END    (0)
#define BBPSCTRL_BBP_SCTR2D_m2_mst_err_sel_START  (1)
#define BBPSCTRL_BBP_SCTR2D_m2_mst_err_sel_END    (1)
#define BBPSCTRL_BBP_SCTR2D_m3_mst_err_sel_START  (2)
#define BBPSCTRL_BBP_SCTR2D_m3_mst_err_sel_END    (2)
#define BBPSCTRL_BBP_SCTR2D_m4_mst_err_sel_START  (3)
#define BBPSCTRL_BBP_SCTR2D_m4_mst_err_sel_END    (3)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_SCTR2E_UNION
 �ṹ˵��  : BBP_SCTR2E �Ĵ����ṹ���塣��ַƫ����:0x0238����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBPϵͳ������2E��gģ����ͬ�����ԣ�
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctr2e_reg;
    struct
    {
        unsigned int  g_mode_lbus_sel : 1;  /* bit[0]   : G_LBUSѡ�񡣱�����debugʹ�á�
                                                          0����Arbiter�������
                                                          1����Arbiterǰ����� */
        unsigned int  reserved        : 31; /* bit[1-31]: ������ */
    } reg;
} BBPSCTRL_BBP_SCTR2E_UNION;
#define BBPSCTRL_BBP_SCTR2E_g_mode_lbus_sel_START  (0)
#define BBPSCTRL_BBP_SCTR2E_g_mode_lbus_sel_END    (0)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_SCTR2F_UNION
 �ṹ˵��  : BBP_SCTR2F �Ĵ����ṹ���塣��ַƫ����:0x023C����ֵ:0x00000042�����:32
 �Ĵ���˵��: BBPϵͳ������2F(ģʽѡ��)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_sctr2f_reg;
    struct
    {
        unsigned int  wtc_mode_sel : 3;  /* bit[0-2]  : WTCģʽѡ��one-hot���롣
                                                        001��WCDMAģʽ��
                                                        010��TDS-CDMAģʽ��
                                                        100��CDMAģʽ��
                                                        default��TDS_CDMAģʽ��
                                                        ����ֵ����Ч���澯�� */
        unsigned int  reserved_0   : 1;  /* bit[3]    : ���� */
        unsigned int  uc2_mode_sel : 3;  /* bit[4-6]  : UC2ģʽѡ��one-hot���롣
                                                        001��WCDMAģʽ��
                                                        010��������
                                                        100��CDMAģʽ��
                                                        default��CDMAģʽ��
                                                        ����ֵ����Ч���澯�� */
        unsigned int  reserved_1   : 1;  /* bit[7]    : ���� */
        unsigned int  l_et_sel     : 1;  /* bit[8]    : L ETѡ��оƬ�汾��֧������ET�����Ը�ֵ����Ҫ�޸ģ���
                                                        0��������ET��
                                                        1������ET�� */
        unsigned int  w_et_sel     : 1;  /* bit[9]    : W ETѡ��оƬ�汾��֧������ET�����Ը�ֵ����Ҫ�޸ģ�
                                                        0��������ET��
                                                        1������ET�� */
        unsigned int  reserved_2   : 22; /* bit[10-31]: ���� */
    } reg;
} BBPSCTRL_BBP_SCTR2F_UNION;
#define BBPSCTRL_BBP_SCTR2F_wtc_mode_sel_START  (0)
#define BBPSCTRL_BBP_SCTR2F_wtc_mode_sel_END    (2)
#define BBPSCTRL_BBP_SCTR2F_uc2_mode_sel_START  (4)
#define BBPSCTRL_BBP_SCTR2F_uc2_mode_sel_END    (6)
#define BBPSCTRL_BBP_SCTR2F_l_et_sel_START      (8)
#define BBPSCTRL_BBP_SCTR2F_l_et_sel_END        (8)
#define BBPSCTRL_BBP_SCTR2F_w_et_sel_START      (9)
#define BBPSCTRL_BBP_SCTR2F_w_et_sel_END        (9)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_STAT00_UNION
 �ṹ˵��  : BBP_STAT00 �Ĵ����ṹ���塣��ַƫ����:0x0300����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP��Դ��״̬�Ĵ�����mtcmos rdy)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_stat00_reg;
    struct
    {
        unsigned int  lte_mtcmos_rdy : 1;  /* bit[0]   : LTE��Դ���ϵ�״̬��
                                                         1���ϵ磻
                                                         0���µ� */
        unsigned int  wtc_mtcmos_rdy : 1;  /* bit[1]   : WTC��Դ���ϵ�״̬��
                                                         1���ϵ磻
                                                         0���µ� */
        unsigned int  irm_mtcmos_rdy : 1;  /* bit[2]   : IRM��Դ���ϵ�״̬��
                                                         1���ϵ磻
                                                         0���µ� */
        unsigned int  reserved       : 29; /* bit[3-31]: ������ */
    } reg;
} BBPSCTRL_BBP_STAT00_UNION;
#define BBPSCTRL_BBP_STAT00_lte_mtcmos_rdy_START  (0)
#define BBPSCTRL_BBP_STAT00_lte_mtcmos_rdy_END    (0)
#define BBPSCTRL_BBP_STAT00_wtc_mtcmos_rdy_START  (1)
#define BBPSCTRL_BBP_STAT00_wtc_mtcmos_rdy_END    (1)
#define BBPSCTRL_BBP_STAT00_irm_mtcmos_rdy_START  (2)
#define BBPSCTRL_BBP_STAT00_irm_mtcmos_rdy_END    (2)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_STAT06_UNION
 �ṹ˵��  : BBP_STAT06 �Ĵ����ṹ���塣��ַƫ����:0x0318����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP MST״̬�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      bbp_stat06_reg;
    struct
    {
        unsigned int  mst_err  : 8;  /* bit[0-7] : bbp��dw_axi_mst��error�ź� */
        unsigned int  reserved : 24; /* bit[8-31]: ������ */
    } reg;
} BBPSCTRL_BBP_STAT06_UNION;
#define BBPSCTRL_BBP_STAT06_mst_err_START   (0)
#define BBPSCTRL_BBP_STAT06_mst_err_END     (7)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_STAT0B_UNION
 �ṹ˵��  : BBP_STAT0B �Ĵ����ṹ���塣��ַƫ����:0x032C����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP MST DLOCK״̬�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      bbp_stat0b_reg;
    struct
    {
        unsigned int  dlock_mst : 2;  /* bit[0-1]  : DLOCK MST��š� */
        unsigned int  dlock_slv : 2;  /* bit[2-3]  : DLOCK SLV��š� */
        unsigned int  dlock_id  : 6;  /* bit[4-9]  : DLOCK ID�� */
        unsigned int  dlock_wr  : 1;  /* bit[10]   : DLOCK�Ķ�д������ */
        unsigned int  dlock_irq : 1;  /* bit[11]   : DLOCK IRQ�� */
        unsigned int  reserved  : 20; /* bit[12-31]: ������ */
    } reg;
} BBPSCTRL_BBP_STAT0B_UNION;
#define BBPSCTRL_BBP_STAT0B_dlock_mst_START  (0)
#define BBPSCTRL_BBP_STAT0B_dlock_mst_END    (1)
#define BBPSCTRL_BBP_STAT0B_dlock_slv_START  (2)
#define BBPSCTRL_BBP_STAT0B_dlock_slv_END    (3)
#define BBPSCTRL_BBP_STAT0B_dlock_id_START   (4)
#define BBPSCTRL_BBP_STAT0B_dlock_id_END     (9)
#define BBPSCTRL_BBP_STAT0B_dlock_wr_START   (10)
#define BBPSCTRL_BBP_STAT0B_dlock_wr_END     (10)
#define BBPSCTRL_BBP_STAT0B_dlock_irq_START  (11)
#define BBPSCTRL_BBP_STAT0B_dlock_irq_END    (11)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_STAT0D_UNION
 �ṹ˵��  : BBP_STAT0D �Ĵ����ṹ���塣��ַƫ����:0x0334����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP״̬�Ĵ���0D(IRM2COM_TBD)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_stat0d_reg;
    struct
    {
        unsigned int  irm2com_tbd : 16; /* bit[0-15] : IRM��COM��Ԥ��eco�źš� */
        unsigned int  reserved    : 16; /* bit[16-31]: ������ */
    } reg;
} BBPSCTRL_BBP_STAT0D_UNION;
#define BBPSCTRL_BBP_STAT0D_irm2com_tbd_START  (0)
#define BBPSCTRL_BBP_STAT0D_irm2com_tbd_END    (15)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_STAT0F_UNION
 �ṹ˵��  : BBP_STAT0F �Ĵ����ṹ���塣��ַƫ����:0x033C����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP״̬�Ĵ���0F(LBUS�������ж�״̬)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_stat0f_reg;
    struct
    {
        unsigned int  ulhb_err_power_int_status           : 1;  /* bit[0] : 0��������
                                                                            1����Դ�رա� */
        unsigned int  ulhb_err_clk_int_status             : 1;  /* bit[1] : 0��������
                                                                            1��ʱ�ӹرա� */
        unsigned int  ulhb_err_rst_int_status             : 1;  /* bit[2] : 0��������
                                                                            1����λ�� */
        unsigned int  ulhb_err_rd_timeout_int_status      : 1;  /* bit[3] : 0��������
                                                                            1����ʱ�� */
        unsigned int  pdf_err_power_int_status            : 1;  /* bit[4] : 0��������
                                                                            1����Դ�رա� */
        unsigned int  pdf_err_clk_int_status              : 1;  /* bit[5] : 0��������
                                                                            1��ʱ�ӹرա� */
        unsigned int  pdf_err_rst_int_status              : 1;  /* bit[6] : 0��������
                                                                            1����λ�� */
        unsigned int  pdf_err_rd_timeout_int_status       : 1;  /* bit[7] : 0��������
                                                                            1����ʱ�� */
        unsigned int  pdt_err_power_int_status            : 1;  /* bit[8] : 0��������
                                                                            1����Դ�رա� */
        unsigned int  pdt_err_clk_int_status              : 1;  /* bit[9] : 0��������
                                                                            1��ʱ�ӹرա� */
        unsigned int  pdt_err_rst_int_status              : 1;  /* bit[10]: 0��������
                                                                            1����λ�� */
        unsigned int  pdt_err_rd_timeout_int_status       : 1;  /* bit[11]: 0��������
                                                                            1����ʱ�� */
        unsigned int  tds245_err_power_int_status         : 1;  /* bit[12]: 0��������
                                                                            1����Դ�رա� */
        unsigned int  tds245_err_clk_int_status           : 1;  /* bit[13]: 0��������
                                                                            1��ʱ�ӹرա� */
        unsigned int  tds245_err_rst_int_status           : 1;  /* bit[14]: 0��������
                                                                            1����λ�� */
        unsigned int  tds245_err_rd_timeout_int_status    : 1;  /* bit[15]: 0��������
                                                                            1����ʱ�� */
        unsigned int  ux_tds122_err_power_int_status      : 1;  /* bit[16]: 0��������
                                                                            1����Դ�رա� */
        unsigned int  ux_tds122_err_clk_int_status        : 1;  /* bit[17]: 0��������
                                                                            1��ʱ�ӹرա� */
        unsigned int  ux_tds122_err_rst_int_status        : 1;  /* bit[18]: 0��������
                                                                            1����λ�� */
        unsigned int  ux_tds122_err_rd_timeout_int_status : 1;  /* bit[19]: 0��������
                                                                            1����ʱ�� */
        unsigned int  g_err_clk_int_status                : 1;  /* bit[20]: 0��������
                                                                            1��ʱ�ӹرա� */
        unsigned int  g_err_rst_int_status                : 1;  /* bit[21]: 0��������
                                                                            1����λ�� */
        unsigned int  g_err_rd_timeout_int_status         : 1;  /* bit[22]: 0��������
                                                                            1����ʱ�� */
        unsigned int  b2s_err_rd_timeout_int_status       : 1;  /* bit[23]: 0��������
                                                                            1����ʱ�� */
        unsigned int  uc2_err_power_int_status            : 1;  /* bit[24]: 0��������
                                                                            1����Դ�رա� */
        unsigned int  uc2_err_clk_int_status              : 1;  /* bit[25]: 0��������
                                                                            1��ʱ�ӹرա� */
        unsigned int  uc2_err_rst_int_status              : 1;  /* bit[26]: 0��������
                                                                            1����λ�� */
        unsigned int  uc2_err_rd_timeout_int_status       : 1;  /* bit[27]: 0��������
                                                                            1����ʱ�� */
        unsigned int  axi_arb_overtime_int_status         : 1;  /* bit[28]: 0��������
                                                                            1����ʱ�� */
        unsigned int  dma_arb_overtime_int_status         : 1;  /* bit[29]: 0��������
                                                                            1����ʱ�� */
        unsigned int  dbgtrig_arb_overtime_int_status     : 1;  /* bit[30]: 0��������
                                                                            1����ʱ�� */
        unsigned int  reserved                            : 1;  /* bit[31]: 0������
                                                                            1����ʱ
                                                                            ���������ᴥ���жϡ�
                                                                            �������ᴥ���жϡ�
                                                                            д�üĴ������Ӧbite���㡣 */
    } reg;
} BBPSCTRL_BBP_STAT0F_UNION;
#define BBPSCTRL_BBP_STAT0F_ulhb_err_power_int_status_START            (0)
#define BBPSCTRL_BBP_STAT0F_ulhb_err_power_int_status_END              (0)
#define BBPSCTRL_BBP_STAT0F_ulhb_err_clk_int_status_START              (1)
#define BBPSCTRL_BBP_STAT0F_ulhb_err_clk_int_status_END                (1)
#define BBPSCTRL_BBP_STAT0F_ulhb_err_rst_int_status_START              (2)
#define BBPSCTRL_BBP_STAT0F_ulhb_err_rst_int_status_END                (2)
#define BBPSCTRL_BBP_STAT0F_ulhb_err_rd_timeout_int_status_START       (3)
#define BBPSCTRL_BBP_STAT0F_ulhb_err_rd_timeout_int_status_END         (3)
#define BBPSCTRL_BBP_STAT0F_pdf_err_power_int_status_START             (4)
#define BBPSCTRL_BBP_STAT0F_pdf_err_power_int_status_END               (4)
#define BBPSCTRL_BBP_STAT0F_pdf_err_clk_int_status_START               (5)
#define BBPSCTRL_BBP_STAT0F_pdf_err_clk_int_status_END                 (5)
#define BBPSCTRL_BBP_STAT0F_pdf_err_rst_int_status_START               (6)
#define BBPSCTRL_BBP_STAT0F_pdf_err_rst_int_status_END                 (6)
#define BBPSCTRL_BBP_STAT0F_pdf_err_rd_timeout_int_status_START        (7)
#define BBPSCTRL_BBP_STAT0F_pdf_err_rd_timeout_int_status_END          (7)
#define BBPSCTRL_BBP_STAT0F_pdt_err_power_int_status_START             (8)
#define BBPSCTRL_BBP_STAT0F_pdt_err_power_int_status_END               (8)
#define BBPSCTRL_BBP_STAT0F_pdt_err_clk_int_status_START               (9)
#define BBPSCTRL_BBP_STAT0F_pdt_err_clk_int_status_END                 (9)
#define BBPSCTRL_BBP_STAT0F_pdt_err_rst_int_status_START               (10)
#define BBPSCTRL_BBP_STAT0F_pdt_err_rst_int_status_END                 (10)
#define BBPSCTRL_BBP_STAT0F_pdt_err_rd_timeout_int_status_START        (11)
#define BBPSCTRL_BBP_STAT0F_pdt_err_rd_timeout_int_status_END          (11)
#define BBPSCTRL_BBP_STAT0F_tds245_err_power_int_status_START          (12)
#define BBPSCTRL_BBP_STAT0F_tds245_err_power_int_status_END            (12)
#define BBPSCTRL_BBP_STAT0F_tds245_err_clk_int_status_START            (13)
#define BBPSCTRL_BBP_STAT0F_tds245_err_clk_int_status_END              (13)
#define BBPSCTRL_BBP_STAT0F_tds245_err_rst_int_status_START            (14)
#define BBPSCTRL_BBP_STAT0F_tds245_err_rst_int_status_END              (14)
#define BBPSCTRL_BBP_STAT0F_tds245_err_rd_timeout_int_status_START     (15)
#define BBPSCTRL_BBP_STAT0F_tds245_err_rd_timeout_int_status_END       (15)
#define BBPSCTRL_BBP_STAT0F_ux_tds122_err_power_int_status_START       (16)
#define BBPSCTRL_BBP_STAT0F_ux_tds122_err_power_int_status_END         (16)
#define BBPSCTRL_BBP_STAT0F_ux_tds122_err_clk_int_status_START         (17)
#define BBPSCTRL_BBP_STAT0F_ux_tds122_err_clk_int_status_END           (17)
#define BBPSCTRL_BBP_STAT0F_ux_tds122_err_rst_int_status_START         (18)
#define BBPSCTRL_BBP_STAT0F_ux_tds122_err_rst_int_status_END           (18)
#define BBPSCTRL_BBP_STAT0F_ux_tds122_err_rd_timeout_int_status_START  (19)
#define BBPSCTRL_BBP_STAT0F_ux_tds122_err_rd_timeout_int_status_END    (19)
#define BBPSCTRL_BBP_STAT0F_g_err_clk_int_status_START                 (20)
#define BBPSCTRL_BBP_STAT0F_g_err_clk_int_status_END                   (20)
#define BBPSCTRL_BBP_STAT0F_g_err_rst_int_status_START                 (21)
#define BBPSCTRL_BBP_STAT0F_g_err_rst_int_status_END                   (21)
#define BBPSCTRL_BBP_STAT0F_g_err_rd_timeout_int_status_START          (22)
#define BBPSCTRL_BBP_STAT0F_g_err_rd_timeout_int_status_END            (22)
#define BBPSCTRL_BBP_STAT0F_b2s_err_rd_timeout_int_status_START        (23)
#define BBPSCTRL_BBP_STAT0F_b2s_err_rd_timeout_int_status_END          (23)
#define BBPSCTRL_BBP_STAT0F_uc2_err_power_int_status_START             (24)
#define BBPSCTRL_BBP_STAT0F_uc2_err_power_int_status_END               (24)
#define BBPSCTRL_BBP_STAT0F_uc2_err_clk_int_status_START               (25)
#define BBPSCTRL_BBP_STAT0F_uc2_err_clk_int_status_END                 (25)
#define BBPSCTRL_BBP_STAT0F_uc2_err_rst_int_status_START               (26)
#define BBPSCTRL_BBP_STAT0F_uc2_err_rst_int_status_END                 (26)
#define BBPSCTRL_BBP_STAT0F_uc2_err_rd_timeout_int_status_START        (27)
#define BBPSCTRL_BBP_STAT0F_uc2_err_rd_timeout_int_status_END          (27)
#define BBPSCTRL_BBP_STAT0F_axi_arb_overtime_int_status_START          (28)
#define BBPSCTRL_BBP_STAT0F_axi_arb_overtime_int_status_END            (28)
#define BBPSCTRL_BBP_STAT0F_dma_arb_overtime_int_status_START          (29)
#define BBPSCTRL_BBP_STAT0F_dma_arb_overtime_int_status_END            (29)
#define BBPSCTRL_BBP_STAT0F_dbgtrig_arb_overtime_int_status_START      (30)
#define BBPSCTRL_BBP_STAT0F_dbgtrig_arb_overtime_int_status_END        (30)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_STAT10_UNION
 �ṹ˵��  : BBP_STAT10 �Ĵ����ṹ���塣��ַƫ����:0x0340����ֵ:0x00000000�����:32
 �Ĵ���˵��: BBP״̬�Ĵ���10(COM��ʱ��״̬����clk_en�Գ�)
*****************************************************************************/
typedef union
{
    unsigned int      bbp_stat10_reg;
    struct
    {
        unsigned int  reserved_0                     : 1;  /* bit[0]    : ���� */
        unsigned int  reserved_1                     : 1;  /* bit[1]    : ���� */
        unsigned int  reserved_2                     : 1;  /* bit[2]    : ���� */
        unsigned int  reserved_3                     : 1;  /* bit[3]    : ���� */
        unsigned int  com_g12com_abb0_tx_mclk_status : 1;  /* bit[4]    : 0����ʱ��
                                                                          1����ʱ�� */
        unsigned int  com_g22com_abb0_tx_mclk_status : 1;  /* bit[5]    : 0����ʱ��
                                                                          1����ʱ�� */
        unsigned int  com_g_sleep_clk_status         : 1;  /* bit[6]    : 0����ʱ��
                                                                          1����ʱ��
                                                                          Gģ������32Kʱ�ӵ�״̬�� */
        unsigned int  com_g_sys_clk_status           : 1;  /* bit[7]    : 0����ʱ��
                                                                          1����ʱ��
                                                                          Gģ������19.2Mʱ�ӵ�״̬ */
        unsigned int  com_g_com_clk_status           : 1;  /* bit[8]    : 0����ʱ��
                                                                          1����ʱ��
                                                                          Gģ��������LBUSʱ��״̬�� */
        unsigned int  com_g1_sdr_com_clk_status      : 1;  /* bit[9]    : 0����ʱ��
                                                                          1����ʱ��
                                                                          Gģ������G1��GSDR�Ĺ����߼���104Mʱ��״̬�� */
        unsigned int  com_l2com_abb0_tx_mclk_status  : 1;  /* bit[10]   : 0����ʱ��
                                                                          1����ʱ�� */
        unsigned int  com_l2com_abb1_tx_mclk_status  : 1;  /* bit[11]   : 0����ʱ��
                                                                          1����ʱ�� */
        unsigned int  com_lte_pdf_clk_status         : 1;  /* bit[12]   : 0����ʱ��
                                                                          1����ʱ��
                                                                          LTE PDF LBUSʱ��״̬�� */
        unsigned int  com_lte_pdt_clk_status         : 1;  /* bit[13]   : 0����ʱ��
                                                                          1����ʱ��
                                                                          LTE PDT LBUSʱ��״̬�� */
        unsigned int  com_lte_ulhb_clk_status        : 1;  /* bit[14]   : 0����ʱ��
                                                                          1����ʱ��
                                                                          LTE ULHB LBUSʱ��״̬ */
        unsigned int  com_axim_clk_status            : 1;  /* bit[15]   : 0����ʱ��
                                                                          1����ʱ�� */
        unsigned int  com_tds_122_clk_status         : 1;  /* bit[16]   : 0����ʱ��
                                                                          1����ʱ��
                                                                          û��ʹ�á� */
        unsigned int  com_tds_245_clk_status         : 1;  /* bit[17]   : 0����ʱ��
                                                                          1����ʱ��
                                                                          TDS 245 LBUSʱ��״̬ */
        unsigned int  com_tds_dbg_clk_status         : 1;  /* bit[18]   : 0����ʱ��
                                                                          1����ʱ�� */
        unsigned int  com_tl_dbg_sys_clk_status      : 1;  /* bit[19]   : 0����ʱ��
                                                                          1����ʱ�� */
        unsigned int  com_wtc_122_clk_status         : 1;  /* bit[20]   : 0����ʱ��
                                                                          1����ʱ��
                                                                          WTC 122 LBUSʱ��״̬ */
        unsigned int  reserved_4                     : 11; /* bit[21-31]: ������
                                                                          ��Щ����COM_TOP�е�ʱ��״̬�� */
    } reg;
} BBPSCTRL_BBP_STAT10_UNION;
#define BBPSCTRL_BBP_STAT10_com_g12com_abb0_tx_mclk_status_START  (4)
#define BBPSCTRL_BBP_STAT10_com_g12com_abb0_tx_mclk_status_END    (4)
#define BBPSCTRL_BBP_STAT10_com_g22com_abb0_tx_mclk_status_START  (5)
#define BBPSCTRL_BBP_STAT10_com_g22com_abb0_tx_mclk_status_END    (5)
#define BBPSCTRL_BBP_STAT10_com_g_sleep_clk_status_START          (6)
#define BBPSCTRL_BBP_STAT10_com_g_sleep_clk_status_END            (6)
#define BBPSCTRL_BBP_STAT10_com_g_sys_clk_status_START            (7)
#define BBPSCTRL_BBP_STAT10_com_g_sys_clk_status_END              (7)
#define BBPSCTRL_BBP_STAT10_com_g_com_clk_status_START            (8)
#define BBPSCTRL_BBP_STAT10_com_g_com_clk_status_END              (8)
#define BBPSCTRL_BBP_STAT10_com_g1_sdr_com_clk_status_START       (9)
#define BBPSCTRL_BBP_STAT10_com_g1_sdr_com_clk_status_END         (9)
#define BBPSCTRL_BBP_STAT10_com_l2com_abb0_tx_mclk_status_START   (10)
#define BBPSCTRL_BBP_STAT10_com_l2com_abb0_tx_mclk_status_END     (10)
#define BBPSCTRL_BBP_STAT10_com_l2com_abb1_tx_mclk_status_START   (11)
#define BBPSCTRL_BBP_STAT10_com_l2com_abb1_tx_mclk_status_END     (11)
#define BBPSCTRL_BBP_STAT10_com_lte_pdf_clk_status_START          (12)
#define BBPSCTRL_BBP_STAT10_com_lte_pdf_clk_status_END            (12)
#define BBPSCTRL_BBP_STAT10_com_lte_pdt_clk_status_START          (13)
#define BBPSCTRL_BBP_STAT10_com_lte_pdt_clk_status_END            (13)
#define BBPSCTRL_BBP_STAT10_com_lte_ulhb_clk_status_START         (14)
#define BBPSCTRL_BBP_STAT10_com_lte_ulhb_clk_status_END           (14)
#define BBPSCTRL_BBP_STAT10_com_axim_clk_status_START             (15)
#define BBPSCTRL_BBP_STAT10_com_axim_clk_status_END               (15)
#define BBPSCTRL_BBP_STAT10_com_tds_122_clk_status_START          (16)
#define BBPSCTRL_BBP_STAT10_com_tds_122_clk_status_END            (16)
#define BBPSCTRL_BBP_STAT10_com_tds_245_clk_status_START          (17)
#define BBPSCTRL_BBP_STAT10_com_tds_245_clk_status_END            (17)
#define BBPSCTRL_BBP_STAT10_com_tds_dbg_clk_status_START          (18)
#define BBPSCTRL_BBP_STAT10_com_tds_dbg_clk_status_END            (18)
#define BBPSCTRL_BBP_STAT10_com_tl_dbg_sys_clk_status_START       (19)
#define BBPSCTRL_BBP_STAT10_com_tl_dbg_sys_clk_status_END         (19)
#define BBPSCTRL_BBP_STAT10_com_wtc_122_clk_status_START          (20)
#define BBPSCTRL_BBP_STAT10_com_wtc_122_clk_status_END            (20)


/*****************************************************************************
 �ṹ��    : BBPSCTRL_BBP_STAT1F_UNION
 �ṹ˵��  : BBP_STAT1F �Ĵ����ṹ���塣��ַƫ����:0x037C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����Դ�����ʱ�ӵ�ʱ��״̬��ÿ��PDһ��ʱ��ʹ�ܣ�������ÿ��PD�����ʱ��ȫ���򿪡�
*****************************************************************************/
typedef union
{
    unsigned int      bbp_stat1f_reg;
    struct
    {
        unsigned int  bbc_104m_clk_pstat        : 1;  /* bit[0]    :  */
        unsigned int  bbc_19m_clk_pstat         : 1;  /* bit[1]    :  */
        unsigned int  bbc_32k_clk_pstat         : 1;  /* bit[2]    :  */
        unsigned int  bbc_scpll_uc2_clk_pstat   : 1;  /* bit[3]    :  */
        unsigned int  bbc_scpll_clk_pstat       : 1;  /* bit[4]    :  */
        unsigned int  pd3gp_19m_clk_pstat       : 1;  /* bit[5]    :  */
        unsigned int  pd3gp_32k_clk_pstat       : 1;  /* bit[6]    :  */
        unsigned int  pd3gp_scpll_uc2_clk_pstat : 1;  /* bit[7]    :  */
        unsigned int  pd3gp_scpll_clk_pstat     : 1;  /* bit[8]    :  */
        unsigned int  pdirm_axis_clk_pstat      : 1;  /* bit[9]    :  */
        unsigned int  pdirm_scpll_clk_pstat     : 1;  /* bit[10]   :  */
        unsigned int  pdirm_tdl_clk_pstat       : 1;  /* bit[11]   :  */
        unsigned int  pdlte_19m_clk_pstat       : 1;  /* bit[12]   :  */
        unsigned int  pdlte_32k_clk_pstat       : 1;  /* bit[13]   :  */
        unsigned int  pdlte_axim_clk_pstat      : 1;  /* bit[14]   :  */
        unsigned int  pdlte_scpll_clk_pstat     : 1;  /* bit[15]   :  */
        unsigned int  pdlte_tdl_clk_pstat       : 1;  /* bit[16]   :  */
        unsigned int  reserved                  : 15; /* bit[17-31]: ���� */
    } reg;
} BBPSCTRL_BBP_STAT1F_UNION;
#define BBPSCTRL_BBP_STAT1F_bbc_104m_clk_pstat_START         (0)
#define BBPSCTRL_BBP_STAT1F_bbc_104m_clk_pstat_END           (0)
#define BBPSCTRL_BBP_STAT1F_bbc_19m_clk_pstat_START          (1)
#define BBPSCTRL_BBP_STAT1F_bbc_19m_clk_pstat_END            (1)
#define BBPSCTRL_BBP_STAT1F_bbc_32k_clk_pstat_START          (2)
#define BBPSCTRL_BBP_STAT1F_bbc_32k_clk_pstat_END            (2)
#define BBPSCTRL_BBP_STAT1F_bbc_scpll_uc2_clk_pstat_START    (3)
#define BBPSCTRL_BBP_STAT1F_bbc_scpll_uc2_clk_pstat_END      (3)
#define BBPSCTRL_BBP_STAT1F_bbc_scpll_clk_pstat_START        (4)
#define BBPSCTRL_BBP_STAT1F_bbc_scpll_clk_pstat_END          (4)
#define BBPSCTRL_BBP_STAT1F_pd3gp_19m_clk_pstat_START        (5)
#define BBPSCTRL_BBP_STAT1F_pd3gp_19m_clk_pstat_END          (5)
#define BBPSCTRL_BBP_STAT1F_pd3gp_32k_clk_pstat_START        (6)
#define BBPSCTRL_BBP_STAT1F_pd3gp_32k_clk_pstat_END          (6)
#define BBPSCTRL_BBP_STAT1F_pd3gp_scpll_uc2_clk_pstat_START  (7)
#define BBPSCTRL_BBP_STAT1F_pd3gp_scpll_uc2_clk_pstat_END    (7)
#define BBPSCTRL_BBP_STAT1F_pd3gp_scpll_clk_pstat_START      (8)
#define BBPSCTRL_BBP_STAT1F_pd3gp_scpll_clk_pstat_END        (8)
#define BBPSCTRL_BBP_STAT1F_pdirm_axis_clk_pstat_START       (9)
#define BBPSCTRL_BBP_STAT1F_pdirm_axis_clk_pstat_END         (9)
#define BBPSCTRL_BBP_STAT1F_pdirm_scpll_clk_pstat_START      (10)
#define BBPSCTRL_BBP_STAT1F_pdirm_scpll_clk_pstat_END        (10)
#define BBPSCTRL_BBP_STAT1F_pdirm_tdl_clk_pstat_START        (11)
#define BBPSCTRL_BBP_STAT1F_pdirm_tdl_clk_pstat_END          (11)
#define BBPSCTRL_BBP_STAT1F_pdlte_19m_clk_pstat_START        (12)
#define BBPSCTRL_BBP_STAT1F_pdlte_19m_clk_pstat_END          (12)
#define BBPSCTRL_BBP_STAT1F_pdlte_32k_clk_pstat_START        (13)
#define BBPSCTRL_BBP_STAT1F_pdlte_32k_clk_pstat_END          (13)
#define BBPSCTRL_BBP_STAT1F_pdlte_axim_clk_pstat_START       (14)
#define BBPSCTRL_BBP_STAT1F_pdlte_axim_clk_pstat_END         (14)
#define BBPSCTRL_BBP_STAT1F_pdlte_scpll_clk_pstat_START      (15)
#define BBPSCTRL_BBP_STAT1F_pdlte_scpll_clk_pstat_END        (15)
#define BBPSCTRL_BBP_STAT1F_pdlte_tdl_clk_pstat_START        (16)
#define BBPSCTRL_BBP_STAT1F_pdlte_tdl_clk_pstat_END          (16)




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

#endif /* end of bbp_sctrl_interface.h */
