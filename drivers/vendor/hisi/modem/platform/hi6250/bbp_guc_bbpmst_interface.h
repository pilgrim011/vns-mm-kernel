/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : bbp_comm_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-06-09 17:33:25
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��6��9��
    ��    ��   : l00165286
    �޸�����   : �ӡ�Hi6250V100 MODEM�Ĵ����ֲ�_GUC_BBPMST.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __BBP_GUC_BBPMST_INTERFACE_H__
#define __BBP_GUC_BBPMST_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/***======================================================================***
                     (1/1) register_define_guc_bbpmst
 ***======================================================================***/
/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��д����ͨ����ʹ�ܣ�
             1��b0���ر�
             1��b1��ʹ��
 bit[8]      1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch0_base_addr��ָ��ĵ�ַ
             1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH0_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH0_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC000)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH0_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC004)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ļ���ַ����ByteΪ��λ��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH0_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC008)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ľ�����ַ����ByteΪ��λ�������ȷ������ַ�ͽ�����ַ֮��ĸÿռ������8byte���������������ݴﵽ������ַʱmaster���Զ��ƻص�����ַ��д���µ�����
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH0_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC00C)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  Uģ����harq���ƣ�ϵͳλ�������ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   Uģ����harq���ƣ�ϵͳλ�������ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00
 bit[7:4]    
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC010)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH0_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH0_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC014)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             �����жϿ��Զ�ʹ�ܡ�
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH0_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH0_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC018)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��д����ͨ����ʹ�ܣ�
             1��b0���ر�
             1��b1��ʹ��
 bit[8]      1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch1_base_addr��ָ��ĵ�ַ
             1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH1_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH1_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC020)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH1_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC024)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ļ���ַ����ByteΪ��λ��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH1_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC028)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ľ�����ַ����ByteΪ��λ�������ȷ������ַ�ͽ�����ַ֮��ĸÿռ������8byte���������������ݴﵽ������ַʱmaster���Զ��ƻص�����ַ��д���µ�����
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH1_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC02C)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  Uģ����harq���ƣ���һУ��λ�������ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   Uģ����harq���ƣ���һУ��λ�������ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x10
 bit[7:4]    
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC030)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH1_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH1_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC034)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             �����жϿ��Զ�ʹ�ܡ�
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH1_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH1_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC038)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��д����ͨ����ʹ�ܣ�
             1��b0���ر�
             1��b1��ʹ��
 bit[8]      1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch2_base_addr��ָ��ĵ�ַ
             1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH2_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH2_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC040)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH2_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC044)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ļ���ַ����ByteΪ��λ��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH2_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC048)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ľ�����ַ����ByteΪ��λ�������ȷ������ַ�ͽ�����ַ֮��ĸÿռ������8byte���������������ݴﵽ������ַʱmaster���Զ��ƻص�����ַ��д���µ�����
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH2_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC04C)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  Uģ����harq���ƣ��ڶ�У��λ�������ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   Uģ����harq���ƣ��ڶ�У��λ�������ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x20
 bit[7:4]    
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC050)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH2_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH2_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC054)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             �����жϿ��Զ�ʹ�ܡ�
             
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH2_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH2_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC058)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��д����ͨ����ʹ�ܣ�
             1��b0���ر�
             1��b1��ʹ��
 bit[8]      1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch3_base_addr��ָ��ĵ�ַ
             1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH3_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH3_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC060)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH3_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC064)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ļ���ַ����ByteΪ��λ��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH3_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC068)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ľ�����ַ����ByteΪ��λ�������ȷ������ַ�ͽ�����ַ֮��ĸÿռ������8byte���������������ݴﵽ������ַʱmaster���Զ��ƻص�����ַ��д���µ�����
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH3_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC06C)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  Uģ�����ϱ����ƣ�data���֣������ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x07
 bit[15:8]   Uģ�����ϱ����ƣ�data���֣������ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x30
 bit[7:4]    
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC070)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH3_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH3_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC074)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             �����жϿ��Զ�ʹ�ܡ�
             
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH3_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH3_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC078)

/* �Ĵ���˵����
 bit[31:16]  ��ͨ���Ŀ���/æµ״̬��
             1'b0��ͨ�����ſգ����ڿ���̬
             1'b1��ͨ������æµ״̬
 bit[15:0]   дͨ���Ŀ���/æµ״̬��
             1'b0��ͨ�����ſգ����ڿ���̬
             1'b1��ͨ������æµ״̬
   UNION�ṹ:  BBPCOMM_BBPMST_CH_BUSY_UNION */
#define BBPCOMM_BBPMST_CH_BUSY_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xC098)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��ͨ��ʹ���źţ�
             1'b0:�رգ�
             1'b1:�򿪣�
 bit[8]      1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch0_base_addr��ָ��ĵ�ַ
             1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH0_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH0_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC100)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH0_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC104)

/* �Ĵ���˵����
   ��      �����ö�ͨ����DDR�ж�Ӧ�ĵ�ַ�ռ�Ļ���ַ����ByteΪ��λ������ͨ����֧��ѭ�������������ÿռ������ַ�����ڶ�ȡ���ݵĳ���Ҳ������������������ȷ����ͨ����Ӧ�ĵ�ַ�ռ䲻������������������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH0_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC108)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  Uģ����harq���ƣ�ϵͳλ�������ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   Uģ����harq���ƣ�ϵͳλ�������ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00
 bit[7:4]    
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC10C)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH0_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH0_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC110)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  �ö�����ͨ�������жϵķ�ʽ��
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH0_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH0_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC114)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ��ͨ��0ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ�
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC118)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��ͨ��ʹ���źţ�
             1'b0:�رգ�
             1'b1:�򿪣�
 bit[8]      1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch1_base_addr��ָ��ĵ�ַ
             1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH1_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH1_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC120)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH1_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC124)

/* �Ĵ���˵����
   ��      �����ö�ͨ����DDR�ж�Ӧ�ĵ�ַ�ռ�Ļ���ַ����ByteΪ��λ������ͨ����֧��ѭ�������������ÿռ������ַ�����ڶ�ȡ���ݵĳ���Ҳ������������������ȷ����ͨ����Ӧ�ĵ�ַ�ռ䲻������������������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH1_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC128)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  Uģ����harq���ƣ���һУ��λ�������ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   Uģ����harq���ƣ���һУ��λ�������ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00
 bit[7:4]    
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC12C)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH1_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH1_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC130)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  �ö�����ͨ�������жϵķ�ʽ��
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH1_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH1_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC134)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ��ͨ��1ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ�
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC138)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��ͨ��ʹ���źţ�
             1'b0:�رգ�
             1'b1:�򿪣�
 bit[8]      1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch2_base_addr��ָ��ĵ�ַ
             1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH2_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH2_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC140)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH2_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC144)

/* �Ĵ���˵����
   ��      �����ö�ͨ����DDR�ж�Ӧ�ĵ�ַ�ռ�Ļ���ַ����ByteΪ��λ������ͨ����֧��ѭ�������������ÿռ������ַ�����ڶ�ȡ���ݵĳ���Ҳ������������������ȷ����ͨ����Ӧ�ĵ�ַ�ռ䲻������������������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH2_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC148)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  Uģ����harq���ƣ��ڶ�У��λ�������ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   Uģ����harq���ƣ��ڶ�У��λ�������ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00
 bit[7:4]    
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC14C)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH2_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH2_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC150)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  �ö�����ͨ�������жϵķ�ʽ��
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH2_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH2_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC154)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ��ͨ��2ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ�
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC158)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��ͨ��ʹ���źţ�
             1'b0:�رգ�
             1'b1:�򿪣�
 bit[8]      1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch3_base_addr��ָ��ĵ�ַ
             1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH3_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH3_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC160)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH3_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC164)

/* �Ĵ���˵����
   ��      �����ö�ͨ����DDR�ж�Ӧ�ĵ�ַ�ռ�Ļ���ַ����ByteΪ��λ������ͨ����֧��ѭ�������������ÿռ������ַ�����ڶ�ȡ���ݵĳ���Ҳ������������������ȷ����ͨ����Ӧ�ĵ�ַ�ռ䲻������������������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH3_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC168)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  CģSDR_TX�����ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   CģSDR_TX�����ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00
 bit[7:4]    
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC16C)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH3_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH3_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC170)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  �ö�����ͨ�������жϵķ�ʽ��
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH3_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH3_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC174)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ��ͨ��3ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ�
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC178)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��д����ͨ����ʹ�ܣ�
             1��b0���ر�
             1��b1��ʹ��
 bit[8]      1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch5_base_addr��ָ��ĵ�ַ
             1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH5_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH5_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC200)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH5_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC204)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ļ���ַ����ByteΪ��λ��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH5_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC208)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ľ�����ַ����ByteΪ��λ�������ȷ������ַ�ͽ�����ַ֮��ĸÿռ������8byte���������������ݴﵽ������ַʱmaster���Զ��ƻص�����ַ��д���µ�����
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH5_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC20C)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  UģRX1_dump�����ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   UģRX1_dump�����ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00
 bit[7:4]    ����
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH5_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH5_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC210)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH5_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH5_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC214)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             �����жϿ��Զ�ʹ�ܡ�
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH5_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH5_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC218)

/* �Ĵ���˵����
 bit[31:16]  �ֱ��Ӧbbpmst��ͨ��0-15ʱ���ſ���·��Ԫ��
             1����·ʱ���ſأ�
             0����ʱ���ſأ�
 bit[15:0]   �ֱ��Ӧbbpmstдͨ��0-15ʱ���ſ���·��Ԫ��
             1����·ʱ���ſأ�
             0����ʱ���ſأ�
   UNION�ṹ:  BBPCOMM_BBPMST_CH_CLK_BYPASS_UNION */
#define BBPCOMM_BBPMST_CH_CLK_BYPASS_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xC224)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10]     axi��0�Ŀ���״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
             1��b0�����У������ѱ��ͷŵ�
             1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/����
             
 bit[9]      axi��0��ͨ���Ŀ���״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
             1��b0�����У������ѱ��ͷŵ�
             1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/����
             
 bit[8]      axi��0дͨ���Ŀ���״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
             1��b0�����У������ѱ��ͷŵ�
             1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/����
             
 bit[7:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_AXI0_STATUS_UNION */
#define BBPCOMM_BBPMST_AXI0_STATUS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC300)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10]     axi��1�Ŀ���״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
             1��b0�����У������ѱ��ͷŵ�
             1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/����
             
 bit[9]      axi��1��ͨ���Ŀ���״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
             1��b0�����У������ѱ��ͷŵ�
             1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/����
             
 bit[8]      axi��1дͨ���Ŀ���״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
             1��b0�����У������ѱ��ͷŵ�
             1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/����
             
 bit[7:0]    ����
             
   UNION�ṹ:  BBPCOMM_BBPMST_AXI1_STATUS_UNION */
#define BBPCOMM_BBPMST_AXI1_STATUS_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC304)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��bbpmstдerror����ʱ���ٽ���burst������0
   UNION�ṹ:  BBPCOMM_BBPMST_ERROR_BURST_BEAT0_UNION */
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT0_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC308)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��bbpmstдerror����ʱ���ٽ���burst������1
   UNION�ṹ:  BBPCOMM_BBPMST_ERROR_BURST_BEAT1_UNION */
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT1_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC30C)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��bbpmstдerror����ʱ���ٽ���burst������2
   UNION�ṹ:  BBPCOMM_BBPMST_ERROR_BURST_BEAT2_UNION */
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT2_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC310)

/* �Ĵ���˵����
 bit[31:4]   ����
 bit[3:0]    ��bbpmstдerror����ʱ���ٽ���burst������3
   UNION�ṹ:  BBPCOMM_BBPMST_ERROR_BURST_BEAT3_UNION */
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT3_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC314)

/* �Ĵ���˵����
   ��      ������bbpmstдerror����ʱ���ٽ���burst�Ļ���ַ0
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_BURST_ERROR_INIT_ADDR0_ADDR    (SOC_BBP_COMM_BASE_ADDR + 0xC318)

/* �Ĵ���˵����
   ��      ������bbpmstдerror����ʱ���ٽ���burst�Ļ���ַ1
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_BURST_ERROR_INIT_ADDR1_ADDR    (SOC_BBP_COMM_BASE_ADDR + 0xC31C)

/* �Ĵ���˵����
   ��      ������bbpmstдerror����ʱ���ٽ���burst�Ļ���ַ2
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_BURST_ERROR_INIT_ADDR2_ADDR    (SOC_BBP_COMM_BASE_ADDR + 0xC320)

/* �Ĵ���˵����
   ��      ������bbpmstдerror����ʱ���ٽ���burst�Ļ���ַ3
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_BURST_ERROR_INIT_ADDR3_ADDR    (SOC_BBP_COMM_BASE_ADDR + 0xC324)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      bbpmst��д�����ж�����Ĵ�������BBPMST��д��������ʱ��bbpmst_error_int��ֱ�����ɵ�ƽ�͸�BBE16\CCPU������յ��жϺ����øüĴ�������жϵ�ƽ��
   UNION�ṹ:  BBPCOMM_BBPMST_ERROR_INT_CLR_UNION */
#define BBPCOMM_BBPMST_ERROR_INT_CLR_ADDR             (SOC_BBP_COMM_BASE_ADDR + 0xC328)

/* �Ĵ���˵����
 bit[31:16]  1w2r˫�˿�ram��ʱ���ơ�
 bit[15:0]   ���˿�ram��ʱ���ơ�
   UNION�ṹ:  BBPCOMM_MEM_CTRL0_BBPMST_UNION */
#define BBPCOMM_MEM_CTRL0_BBPMST_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC32C)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  rom��ʱ���ơ�
 bit[15:0]   1rw2rw˫�˿�ram��ʱ���ơ�
   UNION�ṹ:  BBPCOMM_MEM_CTRL1_BBPMST_UNION */
#define BBPCOMM_MEM_CTRL1_BBPMST_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC330)

/* �Ĵ���˵����
   ��      ����AXI��0������BBPMSTдͨ��д�������Ӧ����ͳ��
   UNION�ṹ ���� */
#define BBPCOMM_AXI_WR0_ACK_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xC334)

/* �Ĵ���˵����
   ��      ����AXI��0������BBPMST��ͨ�����������Ӧ����ͳ��
   UNION�ṹ ���� */
#define BBPCOMM_AXI_RD0_ACK_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xC338)

/* �Ĵ���˵����
   ��      ����AXI��1������BBPMSTдͨ��д�������Ӧ����ͳ��
   UNION�ṹ ���� */
#define BBPCOMM_AXI_WR1_ACK_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xC33C)

/* �Ĵ���˵����
   ��      ����AXI��1������BBPMST��ͨ�����������Ӧ����ͳ��
   UNION�ṹ ���� */
#define BBPCOMM_AXI_RD1_ACK_CNT_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xC340)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:8]   AXI��0��ǰд��ӦID
 bit[7:5]    ����
 bit[4]      AXI��0��ǰд��Ӧ������Чָʾ
 bit[3:1]    ����
 bit[0]      AXI��0��ǰд��Ӧ�ɽ�������ָʾ
   UNION�ṹ:  BBPCOMM_AXI_WR0_STATE_UNION */
#define BBPCOMM_AXI_WR0_STATE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xC344)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:8]   AXI��0��ǰ����ӦID
 bit[7:5]    ����
 bit[4]      AXI��0��ǰ����Ӧ������Чָʾ
 bit[3:1]    ����
 bit[0]      AXI��0��ǰ����Ӧ�ɽ�������ָʾ
   UNION�ṹ:  BBPCOMM_AXI_RD0_STATE_UNION */
#define BBPCOMM_AXI_RD0_STATE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xC348)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:8]   AXI��1��ǰд��ӦID
 bit[7:5]    ����
 bit[4]      AXI��1��ǰд��Ӧ������Чָʾ
 bit[3:1]    ����
 bit[0]      AXI��1��ǰд��Ӧ�ɽ�������ָʾ
   UNION�ṹ:  BBPCOMM_AXI_WR1_STATE_UNION */
#define BBPCOMM_AXI_WR1_STATE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xC34C)

/* �Ĵ���˵����
 bit[31:11]  ����
 bit[10:8]   AXI��1��ǰ����ӦID
 bit[7:5]    ����
 bit[4]      AXI��1��ǰ����Ӧ������Чָʾ
 bit[3:1]    ����
 bit[0]      AXI��1��ǰ����Ӧ�ɽ�������ָʾ
   UNION�ṹ:  BBPCOMM_AXI_RD1_STATE_UNION */
#define BBPCOMM_AXI_RD1_STATE_ADDR                    (SOC_BBP_COMM_BASE_ADDR + 0xC350)

/* �Ĵ���˵����
   ��      ����AXI��0������BBPMSTдͨ�����ݴ������ͳ��
   UNION�ṹ ���� */
#define BBPCOMM_AXI_WR0_DATA_CNT_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC354)

/* �Ĵ���˵����
   ��      ����AXI��0������BBPMST��ͨ�����ݴ������ͳ��
   UNION�ṹ ���� */
#define BBPCOMM_AXI_RD0_DATA_CNT_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC358)

/* �Ĵ���˵����
   ��      ����AXI��1������BBPMSTдͨ�����ݴ������ͳ��
   UNION�ṹ ���� */
#define BBPCOMM_AXI_WR1_DATA_CNT_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC35C)

/* �Ĵ���˵����
   ��      ����AXI��1������BBPMST��ͨ�����ݴ������ͳ��
   UNION�ṹ ���� */
#define BBPCOMM_AXI_RD1_DATA_CNT_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC360)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      BBPMST��д�����ж�ʹ��
   UNION�ṹ:  BBPCOMM_BBPMST_ERROR_INT_EN_UNION */
#define BBPCOMM_BBPMST_ERROR_INT_EN_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC364)

/* �Ĵ���˵����
 bit[31:10]  
 bit[9]      ���п�ά�ɲ⹦�ܵ�ʹ���źţ�Ϊ1ʱ�����п�ά�ɲ�Ĵ�����Ϊ0ʱ�����п�ά�ɲ�Ĵ�����������
 bit[8]      ���ڿ�ά�ɲ⣬���������ź������ڲ�����������������ʱ�Ӻ͸�λ�ź�
 bit[7:4]    
 bit[3:0]    ���ڿ�ά�ɲ⹦�ܣ���bbpmst_maintain_pulse���м���
   UNION�ṹ:  BBPCOMM_BBPMST_MAINTAIN_CFG_UNION */
#define BBPCOMM_BBPMST_MAINTAIN_CFG_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC368)

/* �Ĵ���˵����
 bit[31:24]  
 bit[23:16]  ���ж�2�����������м��������ڿ�ά�ɲ�
 bit[15:8]   ���ж�1�����������м��������ڿ�ά�ɲ�
 bit[7:0]    ���ж�0�����������м��������ڿ�ά�ɲ�
   UNION�ṹ:  BBPCOMM_BBPMST_INT_CNT_UNION */
#define BBPCOMM_BBPMST_INT_CNT_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xC36C)

/* �Ĵ���˵����
   ��      �����ж�0������λ��
               [15:0]���ֱ�Ϊ��������дͨ����Ӧ�жϵ�����λ��1��ʾ���Ρ�
               [31:16]���ֱ�Ϊ��������дͨ������λ��дʹ�ܡ�
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_INT0_MASK_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC370)

/* �Ĵ���˵����
   ��      �����ж�0�����ж�λ��
               [15:0]���ֱ��Ӧ��������дͨ���жϵ����жϣ�������Ч��
               [31:16]���ֱ��Ӧ���������ͨ���жϵ����жϣ�������Ч��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_INT0_CLR_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xC374)

/* �Ĵ���˵����
   ��      �����ж�0���жϱ�־��Ϊ�������κ�Ľ����
               [15:0]���ֱ��Ӧ��������дͨ���жϵ��жϱ�־��
               [31:16]���ֱ��Ӧ���������ͨ���жϵ��жϱ�־��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_INT0_STATE_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xC378)

/* �Ĵ���˵����
   ��      �����ж�0���жϱ�־��Ϊ����ǰ��ԭʼ�жϱ�־��
               [15:0]���ֱ��Ӧ��������дͨ���жϵ��жϱ�־��
               [31:16]���ֱ��Ӧ���������ͨ���жϵ��жϱ�־��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_INT0_STATE_RAW_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC37C)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      BBPMST��дͨ���ж�0ʹ��
   UNION�ṹ:  BBPCOMM_BBPMST_INT0_EN_UNION */
#define BBPCOMM_BBPMST_INT0_EN_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xC380)

/* �Ĵ���˵����
   ��      �����ж�1������λ��
               [15:0]���ֱ�Ϊ��������дͨ����Ӧ�жϵ�����λ��1��ʾ���Ρ�
               [31:16]���ֱ�Ϊ��������дͨ������λ��дʹ�ܡ�
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_INT1_MASK_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC384)

/* �Ĵ���˵����
   ��      �����ж�1�����ж�λ��
               [15:0]���ֱ��Ӧ��������дͨ���жϵ����жϣ�������Ч��
               [31:16]���ֱ��Ӧ���������ͨ���жϵ����жϣ�������Ч��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_INT1_CLR_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xC388)

/* �Ĵ���˵����
   ��      �����ж�1���жϱ�־��Ϊ�������κ�Ľ����
               [15:0]���ֱ��Ӧ��������дͨ���жϵ��жϱ�־��
               [31:16]���ֱ��Ӧ���������ͨ���жϵ��жϱ�־��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_INT1_STATE_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xC38C)

/* �Ĵ���˵����
   ��      �����ж�1���жϱ�־��Ϊ����ǰ��ԭʼ�жϱ�־��
               [15:0]���ֱ��Ӧ��������дͨ���жϵ��жϱ�־��
               [31:16]���ֱ��Ӧ���������ͨ���жϵ��жϱ�־��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_INT1_STATE_RAW_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC390)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      BBPMST��дͨ���ж�1ʹ��
   UNION�ṹ:  BBPCOMM_BBPMST_INT1_EN_UNION */
#define BBPCOMM_BBPMST_INT1_EN_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xC394)

/* �Ĵ���˵����
   ��      �����ж�2������λ��
               [15:0]���ֱ�Ϊ��������дͨ����Ӧ�жϵ�����λ��1��ʾ���Ρ�
               [31:16]���ֱ�Ϊ��������дͨ������λ��дʹ�ܡ�
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_INT2_MASK_ADDR                 (SOC_BBP_COMM_BASE_ADDR + 0xC398)

/* �Ĵ���˵����
   ��      �����ж�2�����ж�λ��
               [15:0]���ֱ��Ӧ��������дͨ���жϵ����жϣ�������Ч��
               [31:16]���ֱ��Ӧ���������ͨ���жϵ����жϣ�������Ч��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_INT2_CLR_ADDR                  (SOC_BBP_COMM_BASE_ADDR + 0xC39C)

/* �Ĵ���˵����
   ��      �����ж�2���жϱ�־��Ϊ�������κ�Ľ����
               [15:0]���ֱ��Ӧ��������дͨ���жϵ��жϱ�־��
               [31:16]���ֱ��Ӧ���������ͨ���жϵ��жϱ�־��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_INT2_STATE_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xC3A0)

/* �Ĵ���˵����
   ��      �����ж�2���жϱ�־��Ϊ����ǰ��ԭʼ�жϱ�־��
               [15:0]���ֱ��Ӧ��������дͨ���жϵ��жϱ�־��
               [31:16]���ֱ��Ӧ���������ͨ���жϵ��жϱ�־��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_INT2_STATE_RAW_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC3A4)

/* �Ĵ���˵����
 bit[31:1]   ����
 bit[0]      BBPMST��дͨ���ж�2ʹ��
   UNION�ṹ:  BBPCOMM_BBPMST_INT2_EN_UNION */
#define BBPCOMM_BBPMST_INT2_EN_ADDR                   (SOC_BBP_COMM_BASE_ADDR + 0xC3A8)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��д����ͨ����ʹ�ܣ�
             1��b0���ر�
             1��b1��ʹ��
 bit[8]      1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch6_base_addr��ָ��ĵ�ַ
             1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH6_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH6_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC3B0)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH6_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC3B4)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ļ���ַ����ByteΪ��λ��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH6_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC3B8)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ľ�����ַ����ByteΪ��λ�������ȷ������ַ�ͽ�����ַ֮��ĸÿռ������8byte���������������ݴﵽ������ַʱmaster���Զ��ƻص�����ַ��д���µ�����
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH6_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC3BC)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  UģRX2_dump�����ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   UģRX2_dump�����ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x10
 bit[7:4]    ����
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH6_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH6_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC3C0)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH6_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH6_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC3C4)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             �����жϿ��Զ�ʹ�ܡ�
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH6_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH6_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC3C8)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��д����ͨ����ʹ�ܣ�
             1��b0���ر�
             1��b1��ʹ��
 bit[8]      1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch7_base_addr��ָ��ĵ�ַ
             1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH7_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH7_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC3D0)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH7_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC3D4)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ļ���ַ����ByteΪ��λ��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH7_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC3D8)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ľ�����ַ����ByteΪ��λ�������ȷ������ַ�ͽ�����ַ֮��ĸÿռ������8byte���������������ݴﵽ������ַʱmaster���Զ��ƻص�����ַ��д���µ�����
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH7_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC3DC)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  Cģ��������harq���������ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   Cģ��������harq���������ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x20
 bit[7:4]    ����
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH7_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH7_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC3E0)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH7_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH7_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC3E4)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             �����жϿ��Զ�ʹ�ܡ�
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH7_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH7_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC3E8)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��д����ͨ����ʹ�ܣ�
             1��b0���ر�
             1��b1��ʹ��
 bit[8]      1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch8_base_addr��ָ��ĵ�ַ
             1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH8_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH8_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC3F0)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH8_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC3F4)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ļ���ַ����ByteΪ��λ��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH8_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC3F8)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ľ�����ַ����ByteΪ��λ�������ȷ������ַ�ͽ�����ַ֮��ĸÿռ������8byte���������������ݴﵽ������ַʱmaster���Զ��ƻص�����ַ��д���µ�����
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH8_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC3FC)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  CģSDR_RX1�����ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   CģSDR_RX1�����ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00
 bit[7:4]    ����
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH8_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH8_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC400)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH8_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH8_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC404)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             �����жϿ��Զ�ʹ�ܡ�
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH8_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH8_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC408)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��д����ͨ����ʹ�ܣ�
             1��b0���ر�
             1��b1��ʹ��
 bit[8]      1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch9_base_addr��ָ��ĵ�ַ
             1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH9_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH9_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC410)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH9_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC414)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ļ���ַ����ByteΪ��λ��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH9_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC418)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ľ�����ַ����ByteΪ��λ�������ȷ������ַ�ͽ�����ַ֮��ĸÿռ������8byte���������������ݴﵽ������ַʱmaster���Զ��ƻص�����ַ��д���µ�����
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH9_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC41C)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  CģSDR_RX2�����ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   CģSDR_RX2�����ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x10
 bit[7:4]    ����
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH9_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH9_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC420)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH9_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH9_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC424)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             �����жϿ��Զ�ʹ�ܡ�
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH9_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH9_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC428)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��д����ͨ����ʹ�ܣ�
             1��b0���ر�
             1��b1��ʹ��
 bit[8]      1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch10_base_addr��ָ��ĵ�ַ
             1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH10_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH10_MODE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC430)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH10_CLK_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC434)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ļ���ַ����ByteΪ��λ��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH10_BASE_ADDR_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC438)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ľ�����ַ����ByteΪ��λ�������ȷ������ַ�ͽ�����ַ֮��ĸÿռ������8byte���������������ݴﵽ������ַʱmaster���Զ��ƻص�����ַ��д���µ�����
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH10_END_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC43C)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  Cģ����harq����/1x_VTB�ض������ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   Cģ����harq����/1x_VTB�ض������ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x20
 bit[7:4]    ����
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH10_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH10_BURST_BEAT_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xC440)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH10_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH10_AXI_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC444)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             �����жϿ��Զ�ʹ�ܡ�
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH10_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH10_INTR_MODE_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC448)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��д����ͨ����ʹ�ܣ�
             1��b0���ر�
             1��b1��ʹ��
 bit[8]      1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch11_base_addr��ָ��ĵ�ַ
             1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH11_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH11_MODE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC450)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH11_CLK_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC454)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ļ���ַ����ByteΪ��λ��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH11_BASE_ADDR_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC458)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ľ�����ַ����ByteΪ��λ�������ȷ������ַ�ͽ�����ַ֮��ĸÿռ������8byte���������������ݴﵽ������ַʱmaster���Զ��ƻص�����ַ��д���µ�����
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH11_END_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC45C)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  G1ģharq���������ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   G1ģharq���������ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00
 bit[7:4]    ����
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH11_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH11_BURST_BEAT_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xC460)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH11_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH11_AXI_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC464)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             �����жϿ��Զ�ʹ�ܡ�
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH11_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH11_INTR_MODE_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC468)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��д����ͨ����ʹ�ܣ�
             1��b0���ر�
             1��b1��ʹ��
 bit[8]      1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch12_base_addr��ָ��ĵ�ַ
             1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH12_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH12_MODE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC470)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH12_CLK_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC474)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ļ���ַ����ByteΪ��λ��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH12_BASE_ADDR_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC478)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ľ�����ַ����ByteΪ��λ�������ȷ������ַ�ͽ�����ַ֮��ĸÿռ������8byte���������������ݴﵽ������ַʱmaster���Զ��ƻص�����ַ��д���µ�����
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH12_END_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC47C)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  G1ģdump�����ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   G1ģdump�����ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x10
 bit[7:4]    ����
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH12_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH12_BURST_BEAT_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xC480)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH12_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH12_AXI_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC484)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             �����жϿ��Զ�ʹ�ܡ�
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH12_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH12_INTR_MODE_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC488)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��д����ͨ����ʹ�ܣ�
             1��b0���ر�
             1��b1��ʹ��
 bit[8]      1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch13_base_addr��ָ��ĵ�ַ
             1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH13_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH13_MODE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC490)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH13_CLK_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC494)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ļ���ַ����ByteΪ��λ��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH13_BASE_ADDR_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC498)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ľ�����ַ����ByteΪ��λ�������ȷ������ַ�ͽ�����ַ֮��ĸÿռ������8byte���������������ݴﵽ������ַʱmaster���Զ��ƻص�����ַ��д���µ�����
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH13_END_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC49C)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  G2ģharq���������ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   G2ģharq���������ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00
 bit[7:4]    ����
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH13_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH13_BURST_BEAT_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xC4A0)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH13_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH13_AXI_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC4A4)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             �����жϿ��Զ�ʹ�ܡ�
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH13_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH13_INTR_MODE_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC4A8)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��д����ͨ����ʹ�ܣ�
             1��b0���ر�
             1��b1��ʹ��
 bit[8]      1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch4_base_addr��ָ��ĵ�ַ
             1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH4_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH4_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC4B0)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH4_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC4B4)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ļ���ַ����ByteΪ��λ��
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH4_BASE_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC4B8)

/* �Ĵ���˵����
   ��      ����дͨ��֧��ѭ���ռ�д�����Ĵ���Ϊ��ͨ����DDR�ж�Ӧ��ѭ����ַ�ռ�Ľ�����ַ����ByteΪ��λ�������ȷ������ַ�ͽ�����ַ֮��ĸÿռ������8byte���������������ݴﵽ������ַʱmaster���Զ��ƻص�����ַ��д���µ�����
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_WR_CH4_END_ADDR_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC4BC)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  Uģ�����ϱ����ƣ�head���֣������ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x07
 bit[15:8]   Uģ�����ϱ����ƣ�head���֣������ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x38
 bit[7:4]    
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC4C0)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH4_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_WR_CH4_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC4C4)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             �����жϿ��Զ�ʹ�ܡ�
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_WR_CH4_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_WR_CH4_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC4C8)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��ͨ��ʹ���źţ�
             1'b0:�رգ�
             1'b1:�򿪣�
 bit[8]      1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch4_base_addr��ָ��ĵ�ַ
             1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH4_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH4_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC4D0)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH4_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC4D4)

/* �Ĵ���˵����
   ��      �����ö�ͨ����DDR�ж�Ӧ�ĵ�ַ�ռ�Ļ���ַ����ByteΪ��λ������ͨ����֧��ѭ�������������ÿռ������ַ�����ڶ�ȡ���ݵĳ���Ҳ������������������ȷ����ͨ����Ӧ�ĵ�ַ�ռ䲻������������������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH4_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC4D8)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  Cģ�����������·������ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   Cģ�����������·������ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x10
 bit[7:4]    
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH4_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH4_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC4DC)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH4_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH4_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC4E0)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  �ö�����ͨ�������жϵķ�ʽ��
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH4_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH4_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC4E4)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ��ͨ��0ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ�
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH4_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH4_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC4E8)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��ͨ��ʹ���źţ�
             1'b0:�رգ�
             1'b1:�򿪣�
 bit[8]      1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch5_base_addr��ָ��ĵ�ַ
             1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH5_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH5_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC4F0)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH5_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC4F4)

/* �Ĵ���˵����
   ��      �����ö�ͨ����DDR�ж�Ӧ�ĵ�ַ�ռ�Ļ���ַ����ByteΪ��λ������ͨ����֧��ѭ�������������ÿռ������ַ�����ڶ�ȡ���ݵĳ���Ҳ������������������ȷ����ͨ����Ӧ�ĵ�ַ�ռ䲻������������������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH5_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC4F8)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  Cģharq���������ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   Cģharq���������ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x20
 bit[7:4]    
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH5_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH5_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC4FC)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH5_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH5_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC500)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  �ö�����ͨ�������жϵķ�ʽ��
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH5_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH5_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC504)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ��ͨ��0ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ�
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH5_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH5_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC508)

/* �Ĵ���˵����
   ��      �����ж�0������λ��
               [15:0]���ֱ�Ϊ���������ͨ����Ӧ�жϵ�����λ��1��ʾ���Ρ�
               [31:16]���ֱ�Ϊ���������ͨ������λ��дʹ�ܡ�
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_INT0_MASK_R_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC514)

/* �Ĵ���˵����
   ��      �����ж�0������λ��
               [0]����ӦGUC_MST AXI0�����жϣ�1��ʾ���Ρ�
               [1]����ӦGUC_MST AXI1�����жϣ�1��ʾ���Ρ�
               [16]����ӦGUC_MST AXI0�����ж�����λ��дʹ�ܡ�
               [17]����ӦGUC_MST AXI1�����ж�����λ��дʹ�ܡ�
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_INT0_MASK_E_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC518)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    �ж�0�����ж�λ��
             [1:0]���ֱ��ӦAXI 0/1�����жϵ����жϣ�������Ч��
   UNION�ṹ:  BBPCOMM_BBPMST_INT0_CLR_E_UNION */
#define BBPCOMM_BBPMST_INT0_CLR_E_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xC51C)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    �ж�0���жϱ�־��Ϊ�������κ�Ľ����
             [1:0]���ֱ��ӦAXI0/1ͨ���жϵ��жϱ�־��
   UNION�ṹ:  BBPCOMM_BBPMST_INT0_STATE_E_UNION */
#define BBPCOMM_BBPMST_INT0_STATE_E_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC520)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    �ж�0���жϱ�־��Ϊ����ǰ��ԭʼ�жϱ�־��
             [1:0]���ֱ��ӦAXI0/1ͨ���жϵ��жϱ�־��
   UNION�ṹ:  BBPCOMM_BBPMST_INT0_STATE_RAW_E_UNION */
#define BBPCOMM_BBPMST_INT0_STATE_RAW_E_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC524)

/* �Ĵ���˵����
   ��      �����ж�1������λ��
               [15:0]���ֱ�Ϊ���������ͨ����Ӧ�жϵ�����λ��1��ʾ���Ρ�
               [31:16]���ֱ�Ϊ���������ͨ������λ��дʹ�ܡ�
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_INT1_MASK_R_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC528)

/* �Ĵ���˵����
   ��      �����ж�1������λ��
               [0]����ӦGUC_MST AXI0�����жϣ�1��ʾ���Ρ�
               [1]����ӦGUC_MST AXI1�����жϣ�1��ʾ���Ρ�
               [16]����ӦGUC_MST AXI0�����ж�����λ��дʹ�ܡ�
               [17]����ӦGUC_MST AXI1�����ж�����λ��дʹ�ܡ�
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_INT1_MASK_E_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC52C)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    �ж�1�����ж�λ��
             [1:0]���ֱ��ӦAXI 0/1�����жϵ����жϣ�������Ч��
   UNION�ṹ:  BBPCOMM_BBPMST_INT1_CLR_E_UNION */
#define BBPCOMM_BBPMST_INT1_CLR_E_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xC530)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    �ж�1���жϱ�־��Ϊ�������κ�Ľ����
             [1:0]���ֱ��ӦAXI0/1ͨ���жϵ��жϱ�־��
   UNION�ṹ:  BBPCOMM_BBPMST_INT1_STATE_E_UNION */
#define BBPCOMM_BBPMST_INT1_STATE_E_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC534)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    �ж�1���жϱ�־��Ϊ����ǰ��ԭʼ�жϱ�־��
             [1:0]���ֱ��ӦAXI0/1ͨ���жϵ��жϱ�־��
   UNION�ṹ:  BBPCOMM_BBPMST_INT1_STATE_RAW_E_UNION */
#define BBPCOMM_BBPMST_INT1_STATE_RAW_E_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC538)

/* �Ĵ���˵����
   ��      �����ж�2������λ��
               [15:0]���ֱ�Ϊ���������ͨ����Ӧ�жϵ�����λ��1��ʾ���Ρ�
               [31:16]���ֱ�Ϊ���������ͨ������λ��дʹ�ܡ�
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_INT2_MASK_R_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC53C)

/* �Ĵ���˵����
   ��      �����ж�2������λ��
               [0]����ӦGUC_MST AXI0�����жϣ�1��ʾ���Ρ�
               [1]����ӦGUC_MST AXI1�����жϣ�1��ʾ���Ρ�
               [16]����ӦGUC_MST AXI0�����ж�����λ��дʹ�ܡ�
               [17]����ӦGUC_MST AXI1�����ж�����λ��дʹ�ܡ�
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_INT2_MASK_E_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC540)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    �ж�2�����ж�λ��
             [1:0]���ֱ��ӦAXI 0/1�����жϵ����жϣ�������Ч��
   UNION�ṹ:  BBPCOMM_BBPMST_INT2_CLR_E_UNION */
#define BBPCOMM_BBPMST_INT2_CLR_E_ADDR                (SOC_BBP_COMM_BASE_ADDR + 0xC544)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    �ж�2���жϱ�־��Ϊ�������κ�Ľ����
             [1:0]���ֱ��ӦAXI0/1ͨ���жϵ��жϱ�־��
   UNION�ṹ:  BBPCOMM_BBPMST_INT2_STATE_E_UNION */
#define BBPCOMM_BBPMST_INT2_STATE_E_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC548)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    �ж�2���жϱ�־��Ϊ����ǰ��ԭʼ�жϱ�־��
             [1:0]���ֱ��ӦAXI0/1ͨ���жϵ��жϱ�־��
   UNION�ṹ:  BBPCOMM_BBPMST_INT2_STATE_RAW_E_UNION */
#define BBPCOMM_BBPMST_INT2_STATE_RAW_E_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC54C)

/* �Ĵ���˵����
 bit[31:5]   ����
 bit[4]      bbpmst sram ifʱ���ſ���·��Ԫ��
             1����·ʱ���ſأ�
             0����ʱ���ſأ�
 bit[3]      bbpmst AXI1�ڶ�ͨ��ʱ���ſ���·��Ԫ��
             1����·ʱ���ſأ�
             0����ʱ���ſأ�
 bit[2]      bbpmst AXI1��дͨ��ʱ���ſ���·��Ԫ��
             1����·ʱ���ſأ�
             0����ʱ���ſأ�
 bit[1]      bbpmst AXI0�ڶ�ͨ��ʱ���ſ���·��Ԫ��
             1����·ʱ���ſأ�
             0����ʱ���ſأ�
 bit[0]      bbpmst AXI0��дͨ��ʱ���ſ���·��Ԫ��
             1����·ʱ���ſأ�
             0����ʱ���ſأ�
   UNION�ṹ:  BBPCOMM_BBPMST_AXI_CLK_BYPASS_UNION */
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC550)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��ͨ��ʹ���źţ�
             1'b0:�رգ�
             1'b1:�򿪣�
 bit[8]      1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch6_base_addr��ָ��ĵ�ַ
             1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH6_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH6_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC560)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH6_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC564)

/* �Ĵ���˵����
   ��      �����ö�ͨ����DDR�ж�Ӧ�ĵ�ַ�ռ�Ļ���ַ����ByteΪ��λ������ͨ����֧��ѭ�������������ÿռ������ַ�����ڶ�ȡ���ݵĳ���Ҳ������������������ȷ����ͨ����Ӧ�ĵ�ַ�ռ䲻������������������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH6_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC568)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  CģSDR_TX�����ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   CģSDR_TX�����ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00
 bit[7:4]    
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH6_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH6_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC56C)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH6_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH6_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC570)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  �ö�����ͨ�������жϵķ�ʽ��
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH6_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH6_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC574)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ��ͨ��0ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ�
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH6_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH6_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC578)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��ͨ��ʹ���źţ�
             1'b0:�رգ�
             1'b1:�򿪣�
 bit[8]      1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch7_base_addr��ָ��ĵ�ַ
             1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH7_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH7_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC580)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH7_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC584)

/* �Ĵ���˵����
   ��      �����ö�ͨ����DDR�ж�Ӧ�ĵ�ַ�ռ�Ļ���ַ����ByteΪ��λ������ͨ����֧��ѭ�������������ÿռ������ַ�����ڶ�ȡ���ݵĳ���Ҳ������������������ȷ����ͨ����Ӧ�ĵ�ַ�ռ䲻������������������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH7_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC588)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  Cģ�����������·������ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   Cģ�����������·������ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x10
 bit[7:4]    
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH7_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH7_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC58C)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH7_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH7_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC590)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  �ö�����ͨ�������жϵķ�ʽ��
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH7_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH7_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC594)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ��ͨ��0ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ�
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH7_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH7_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC598)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��ͨ��ʹ���źţ�
             1'b0:�رգ�
             1'b1:�򿪣�
 bit[8]      1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch8_base_addr��ָ��ĵ�ַ
             1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH8_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH8_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC5A0)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH8_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC5A4)

/* �Ĵ���˵����
   ��      �����ö�ͨ����DDR�ж�Ӧ�ĵ�ַ�ռ�Ļ���ַ����ByteΪ��λ������ͨ����֧��ѭ�������������ÿռ������ַ�����ڶ�ȡ���ݵĳ���Ҳ������������������ȷ����ͨ����Ӧ�ĵ�ַ�ռ䲻������������������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH8_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC5A8)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  Cģharq���������ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   Cģharq���������ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x20
 bit[7:4]    
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH8_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH8_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC5AC)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH8_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH8_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC5B0)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  �ö�����ͨ�������жϵķ�ʽ��
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH8_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH8_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC5B4)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ��ͨ��0ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ�
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH8_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH8_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC5B8)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��ͨ��ʹ���źţ�
             1'b0:�رգ�
             1'b1:�򿪣�
 bit[8]      1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch9_base_addr��ָ��ĵ�ַ
             1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH9_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH9_MODE_ADDR               (SOC_BBP_COMM_BASE_ADDR + 0xC5C0)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH9_CLK_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC5C4)

/* �Ĵ���˵����
   ��      �����ö�ͨ����DDR�ж�Ӧ�ĵ�ַ�ռ�Ļ���ַ����ByteΪ��λ������ͨ����֧��ѭ�������������ÿռ������ַ�����ڶ�ȡ���ݵĳ���Ҳ������������������ȷ����ͨ����Ӧ�ĵ�ַ�ռ䲻������������������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH9_INIT_ADDR_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC5C8)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  G1ģharq���������ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   G1ģharq���������ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00
 bit[7:4]    
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH9_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH9_BURST_BEAT_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC5CC)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH9_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH9_AXI_SEL_ADDR            (SOC_BBP_COMM_BASE_ADDR + 0xC5D0)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  �ö�����ͨ�������жϵķ�ʽ��
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH9_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH9_INTR_MODE_ADDR          (SOC_BBP_COMM_BASE_ADDR + 0xC5D4)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ��ͨ��0ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ�
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH9_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH9_BIT_WIDTH_IND_ADDR      (SOC_BBP_COMM_BASE_ADDR + 0xC5D8)

/* �Ĵ���˵����
 bit[31:10]  ����
 bit[9]      ��ͨ��ʹ���źţ�
             1'b0:�رգ�
             1'b1:�򿪣�
 bit[8]      1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch10_base_addr��ָ��ĵ�ַ
             1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ
 bit[7]      1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
             1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP��
 bit[6:0]    ����
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH10_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH10_MODE_ADDR              (SOC_BBP_COMM_BASE_ADDR + 0xC5E0)

/* �Ĵ���˵����
   ��      ��������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH10_CLK_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC5E4)

/* �Ĵ���˵����
   ��      �����ö�ͨ����DDR�ж�Ӧ�ĵ�ַ�ռ�Ļ���ַ����ByteΪ��λ������ͨ����֧��ѭ�������������ÿռ������ַ�����ڶ�ȡ���ݵĳ���Ҳ������������������ȷ����ͨ����Ӧ�ĵ�ַ�ռ䲻������������������
   UNION�ṹ ���� */
#define BBPCOMM_BBPMST_RD_CH10_INIT_ADDR_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC5E8)

/* �Ĵ���˵����
 bit[31:24]  ����
 bit[23:16]  G2ģharq���������ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f
 bit[15:8]   G2ģharq���������ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00
 bit[7:4]    
 bit[3:0]    ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
             burst_beat==0�� burst1
             burst_beat==3�� burst4
             burst_beat==7�� burst8
             burst_beat==15��burst16
             �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8 
             
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH10_BURST_BEAT_UNION */
#define BBPCOMM_BBPMST_RD_CH10_BURST_BEAT_ADDR        (SOC_BBP_COMM_BASE_ADDR + 0xC5EC)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
             2'b00����ͨ��ʹ��master��1
             2'b01����ͨ��ʹ��master��2
             2'b10����ͨ��ʹ��ram��1
             �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master��
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH10_AXI_SEL_UNION */
#define BBPCOMM_BBPMST_RD_CH10_AXI_SEL_ADDR           (SOC_BBP_COMM_BASE_ADDR + 0xC5F0)

/* �Ĵ���˵����
 bit[31:18]  ����
 bit[17:16]  �ö�����ͨ�������жϵķ�ʽ��
             [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
             [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
             
 bit[15:0]   ������ж�ʹ����Чʱ��N��ȡֵ
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH10_INTR_MODE_UNION */
#define BBPCOMM_BBPMST_RD_CH10_INTR_MODE_ADDR         (SOC_BBP_COMM_BASE_ADDR + 0xC5F4)

/* �Ĵ���˵����
 bit[31:2]   ����
 bit[1:0]    ��ͨ��0ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ�
   UNION�ṹ:  BBPCOMM_BBPMST_RD_CH10_BIT_WIDTH_IND_UNION */
#define BBPCOMM_BBPMST_RD_CH10_BIT_WIDTH_IND_ADDR     (SOC_BBP_COMM_BASE_ADDR + 0xC5F8)





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
                     (1/1) register_define_guc_bbpmst
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH0_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH0_MODE �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch0_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_wr_ch0_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                       1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_wr_ch0_addr_mode     : 1;  /* bit[8]    : 1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch0_base_addr��ָ��ĵ�ַ
                                                                       1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_wr_ch0_en            : 1;  /* bit[9]    : ��д����ͨ����ʹ�ܣ�
                                                                       1��b0���ر�
                                                                       1��b1��ʹ�� */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH0_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH0_MODE_bbpmst_wr_ch0_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH0_MODE_bbpmst_wr_ch0_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH0_MODE_bbpmst_wr_ch0_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH0_MODE_bbpmst_wr_ch0_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH0_MODE_bbpmst_wr_ch0_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH0_MODE_bbpmst_wr_ch0_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_WR_CH0_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x000F0005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch0_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch0_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_wr_ch0_fifo_baddr : 8;  /* bit[8-15] : Uģ����harq���ƣ�ϵͳλ�������ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00 */
        unsigned int  bbpmst_wr_ch0_fifo_depth : 8;  /* bit[16-23]: Uģ����harq���ƣ�ϵͳλ�������ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_bbpmst_wr_ch0_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_bbpmst_wr_ch0_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_bbpmst_wr_ch0_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_bbpmst_wr_ch0_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_bbpmst_wr_ch0_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH0_BURST_BEAT_bbpmst_wr_ch0_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH0_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH0_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch0_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch0_axi_sel : 2;  /* bit[0-1] : ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                2'b00����ͨ��ʹ��master��1
                                                                2'b01����ͨ��ʹ��master��2
                                                                2'b10����ͨ��ʹ��ram��1
                                                                �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH0_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH0_AXI_SEL_bbpmst_wr_ch0_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH0_AXI_SEL_bbpmst_wr_ch0_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH0_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH0_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch0_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch0_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_wr_ch0_intr_mode  : 2;  /* bit[16-17]: ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
                                                                    [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                    [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
                                                                    �����жϿ��Զ�ʹ�ܡ� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH0_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH0_INTR_MODE_bbpmst_wr_ch0_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH0_INTR_MODE_bbpmst_wr_ch0_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH0_INTR_MODE_bbpmst_wr_ch0_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH0_INTR_MODE_bbpmst_wr_ch0_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH1_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH1_MODE �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch1_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_wr_ch1_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                       1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_wr_ch1_addr_mode     : 1;  /* bit[8]    : 1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch1_base_addr��ָ��ĵ�ַ
                                                                       1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_wr_ch1_en            : 1;  /* bit[9]    : ��д����ͨ����ʹ�ܣ�
                                                                       1��b0���ر�
                                                                       1��b1��ʹ�� */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH1_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH1_MODE_bbpmst_wr_ch1_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH1_MODE_bbpmst_wr_ch1_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH1_MODE_bbpmst_wr_ch1_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH1_MODE_bbpmst_wr_ch1_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH1_MODE_bbpmst_wr_ch1_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH1_MODE_bbpmst_wr_ch1_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_WR_CH1_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x0030����ֵ:0x000F1005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch1_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch1_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_wr_ch1_fifo_baddr : 8;  /* bit[8-15] : Uģ����harq���ƣ���һУ��λ�������ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x10 */
        unsigned int  bbpmst_wr_ch1_fifo_depth : 8;  /* bit[16-23]: Uģ����harq���ƣ���һУ��λ�������ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_bbpmst_wr_ch1_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_bbpmst_wr_ch1_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_bbpmst_wr_ch1_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_bbpmst_wr_ch1_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_bbpmst_wr_ch1_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH1_BURST_BEAT_bbpmst_wr_ch1_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH1_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH1_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0034����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch1_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch1_axi_sel : 2;  /* bit[0-1] : ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                2'b00����ͨ��ʹ��master��1
                                                                2'b01����ͨ��ʹ��master��2
                                                                2'b10����ͨ��ʹ��ram��1
                                                                �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH1_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH1_AXI_SEL_bbpmst_wr_ch1_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH1_AXI_SEL_bbpmst_wr_ch1_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH1_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH1_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x0038����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch1_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch1_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_wr_ch1_intr_mode  : 2;  /* bit[16-17]: ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
                                                                    [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                    [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
                                                                    �����жϿ��Զ�ʹ�ܡ� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH1_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH1_INTR_MODE_bbpmst_wr_ch1_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH1_INTR_MODE_bbpmst_wr_ch1_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH1_INTR_MODE_bbpmst_wr_ch1_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH1_INTR_MODE_bbpmst_wr_ch1_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH2_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH2_MODE �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch2_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_wr_ch2_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                       1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_wr_ch2_addr_mode     : 1;  /* bit[8]    : 1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch2_base_addr��ָ��ĵ�ַ
                                                                       1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_wr_ch2_en            : 1;  /* bit[9]    : ��д����ͨ����ʹ�ܣ�
                                                                       1��b0���ر�
                                                                       1��b1��ʹ�� */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH2_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH2_MODE_bbpmst_wr_ch2_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH2_MODE_bbpmst_wr_ch2_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH2_MODE_bbpmst_wr_ch2_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH2_MODE_bbpmst_wr_ch2_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH2_MODE_bbpmst_wr_ch2_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH2_MODE_bbpmst_wr_ch2_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_WR_CH2_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0x000F2005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch2_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch2_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_wr_ch2_fifo_baddr : 8;  /* bit[8-15] : Uģ����harq���ƣ��ڶ�У��λ�������ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x20 */
        unsigned int  bbpmst_wr_ch2_fifo_depth : 8;  /* bit[16-23]: Uģ����harq���ƣ��ڶ�У��λ�������ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_bbpmst_wr_ch2_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_bbpmst_wr_ch2_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_bbpmst_wr_ch2_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_bbpmst_wr_ch2_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_bbpmst_wr_ch2_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH2_BURST_BEAT_bbpmst_wr_ch2_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH2_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH2_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch2_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch2_axi_sel : 2;  /* bit[0-1] : ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                2'b00����ͨ��ʹ��master��1
                                                                2'b01����ͨ��ʹ��master��2
                                                                2'b10����ͨ��ʹ��ram��1
                                                                �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH2_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH2_AXI_SEL_bbpmst_wr_ch2_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH2_AXI_SEL_bbpmst_wr_ch2_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH2_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH2_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch2_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch2_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_wr_ch2_intr_mode  : 2;  /* bit[16-17]: ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
                                                                    [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                    [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
                                                                    �����жϿ��Զ�ʹ�ܡ� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH2_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH2_INTR_MODE_bbpmst_wr_ch2_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH2_INTR_MODE_bbpmst_wr_ch2_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH2_INTR_MODE_bbpmst_wr_ch2_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH2_INTR_MODE_bbpmst_wr_ch2_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH3_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH3_MODE �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch3_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_wr_ch3_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                       1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_wr_ch3_addr_mode     : 1;  /* bit[8]    : 1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch3_base_addr��ָ��ĵ�ַ
                                                                       1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_wr_ch3_en            : 1;  /* bit[9]    : ��д����ͨ����ʹ�ܣ�
                                                                       1��b0���ر�
                                                                       1��b1��ʹ�� */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH3_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH3_MODE_bbpmst_wr_ch3_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH3_MODE_bbpmst_wr_ch3_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH3_MODE_bbpmst_wr_ch3_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH3_MODE_bbpmst_wr_ch3_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH3_MODE_bbpmst_wr_ch3_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH3_MODE_bbpmst_wr_ch3_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_WR_CH3_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x0070����ֵ:0x00073002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch3_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch3_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_wr_ch3_fifo_baddr : 8;  /* bit[8-15] : Uģ�����ϱ����ƣ�data���֣������ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x30 */
        unsigned int  bbpmst_wr_ch3_fifo_depth : 8;  /* bit[16-23]: Uģ�����ϱ����ƣ�data���֣������ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x07 */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_bbpmst_wr_ch3_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_bbpmst_wr_ch3_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_bbpmst_wr_ch3_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_bbpmst_wr_ch3_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_bbpmst_wr_ch3_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH3_BURST_BEAT_bbpmst_wr_ch3_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH3_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH3_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0074����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch3_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch3_axi_sel : 2;  /* bit[0-1] : ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                2'b00����ͨ��ʹ��master��1
                                                                2'b01����ͨ��ʹ��master��2
                                                                2'b10����ͨ��ʹ��ram��1
                                                                �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH3_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH3_AXI_SEL_bbpmst_wr_ch3_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH3_AXI_SEL_bbpmst_wr_ch3_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH3_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH3_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x0078����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch3_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch3_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_wr_ch3_intr_mode  : 2;  /* bit[16-17]: ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
                                                                    [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                    [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
                                                                    �����жϿ��Զ�ʹ�ܡ� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH3_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH3_INTR_MODE_bbpmst_wr_ch3_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH3_INTR_MODE_bbpmst_wr_ch3_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH3_INTR_MODE_bbpmst_wr_ch3_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH3_INTR_MODE_bbpmst_wr_ch3_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_CH_BUSY_UNION
 �ṹ˵��  : BBPMST_CH_BUSY �Ĵ����ṹ���塣��ַƫ����:0x0098����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_ch_busy_reg;
    struct
    {
        unsigned int  wr_ch_busy : 16; /* bit[0-15] : дͨ���Ŀ���/æµ״̬��
                                                      1'b0��ͨ�����ſգ����ڿ���̬
                                                      1'b1��ͨ������æµ״̬ */
        unsigned int  rd_ch_busy : 16; /* bit[16-31]: ��ͨ���Ŀ���/æµ״̬��
                                                      1'b0��ͨ�����ſգ����ڿ���̬
                                                      1'b1��ͨ������æµ״̬ */
    } reg;
} BBPCOMM_BBPMST_CH_BUSY_UNION;
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch_busy_START  (0)
#define BBPCOMM_BBPMST_CH_BUSY_wr_ch_busy_END    (15)
#define BBPCOMM_BBPMST_CH_BUSY_rd_ch_busy_START  (16)
#define BBPCOMM_BBPMST_CH_BUSY_rd_ch_busy_END    (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH0_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH0_MODE �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch0_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_rd_ch0_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                       1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_rd_ch0_addr_mode     : 1;  /* bit[8]    : 1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch0_base_addr��ָ��ĵ�ַ
                                                                       1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_rd_ch0_en            : 1;  /* bit[9]    : ��ͨ��ʹ���źţ�
                                                                       1'b0:�رգ�
                                                                       1'b1:�򿪣� */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH0_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH0_MODE_bbpmst_rd_ch0_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH0_MODE_bbpmst_rd_ch0_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH0_MODE_bbpmst_rd_ch0_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH0_MODE_bbpmst_rd_ch0_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH0_MODE_bbpmst_rd_ch0_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH0_MODE_bbpmst_rd_ch0_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_RD_CH0_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x010C����ֵ:0x000F0005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch0_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch0_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch0_fifo_baddr : 8;  /* bit[8-15] : Uģ����harq���ƣ�ϵͳλ�������ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00 */
        unsigned int  bbpmst_rd_ch0_fifo_depth : 8;  /* bit[16-23]: Uģ����harq���ƣ�ϵͳλ�������ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_bbpmst_rd_ch0_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_bbpmst_rd_ch0_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_bbpmst_rd_ch0_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_bbpmst_rd_ch0_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_bbpmst_rd_ch0_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH0_BURST_BEAT_bbpmst_rd_ch0_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH0_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_RD_CH0_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0110����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch0_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch0_axi_sel : 2;  /* bit[0-1] : ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                2'b00����ͨ��ʹ��master��1
                                                                2'b01����ͨ��ʹ��master��2
                                                                2'b10����ͨ��ʹ��ram��1
                                                                �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH0_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH0_AXI_SEL_bbpmst_rd_ch0_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH0_AXI_SEL_bbpmst_rd_ch0_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH0_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH0_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x0114����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch0_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch0_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_rd_ch0_intr_mode  : 2;  /* bit[16-17]: �ö�����ͨ�������жϵķ�ʽ��
                                                                    [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                    [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù��� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH0_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH0_INTR_MODE_bbpmst_rd_ch0_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH0_INTR_MODE_bbpmst_rd_ch0_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH0_INTR_MODE_bbpmst_rd_ch0_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH0_INTR_MODE_bbpmst_rd_ch0_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_UNION
 �ṹ˵��  : BBPMST_RD_CH0_BIT_WIDTH_IND �Ĵ����ṹ���塣��ַƫ����:0x0118����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch0_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch0_bit_width_ind : 2;  /* bit[0-1] : ��ͨ��0ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ� */
        unsigned int  reserved                    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_bbpmst_rd_ch0_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH0_BIT_WIDTH_IND_bbpmst_rd_ch0_bit_width_ind_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH1_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH1_MODE �Ĵ����ṹ���塣��ַƫ����:0x0120����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch1_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_rd_ch1_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                       1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_rd_ch1_addr_mode     : 1;  /* bit[8]    : 1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch1_base_addr��ָ��ĵ�ַ
                                                                       1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_rd_ch1_en            : 1;  /* bit[9]    : ��ͨ��ʹ���źţ�
                                                                       1'b0:�رգ�
                                                                       1'b1:�򿪣� */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH1_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH1_MODE_bbpmst_rd_ch1_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH1_MODE_bbpmst_rd_ch1_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH1_MODE_bbpmst_rd_ch1_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH1_MODE_bbpmst_rd_ch1_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH1_MODE_bbpmst_rd_ch1_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH1_MODE_bbpmst_rd_ch1_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_RD_CH1_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x012C����ֵ:0x000F1005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch1_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch1_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch1_fifo_baddr : 8;  /* bit[8-15] : Uģ����harq���ƣ���һУ��λ�������ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00 */
        unsigned int  bbpmst_rd_ch1_fifo_depth : 8;  /* bit[16-23]: Uģ����harq���ƣ���һУ��λ�������ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_bbpmst_rd_ch1_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_bbpmst_rd_ch1_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_bbpmst_rd_ch1_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_bbpmst_rd_ch1_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_bbpmst_rd_ch1_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH1_BURST_BEAT_bbpmst_rd_ch1_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH1_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_RD_CH1_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0130����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch1_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch1_axi_sel : 2;  /* bit[0-1] : ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                2'b00����ͨ��ʹ��master��1
                                                                2'b01����ͨ��ʹ��master��2
                                                                2'b10����ͨ��ʹ��ram��1
                                                                �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH1_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH1_AXI_SEL_bbpmst_rd_ch1_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH1_AXI_SEL_bbpmst_rd_ch1_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH1_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH1_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x0134����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch1_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch1_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_rd_ch1_intr_mode  : 2;  /* bit[16-17]: �ö�����ͨ�������жϵķ�ʽ��
                                                                    [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                    [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù��� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH1_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH1_INTR_MODE_bbpmst_rd_ch1_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH1_INTR_MODE_bbpmst_rd_ch1_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH1_INTR_MODE_bbpmst_rd_ch1_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH1_INTR_MODE_bbpmst_rd_ch1_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_UNION
 �ṹ˵��  : BBPMST_RD_CH1_BIT_WIDTH_IND �Ĵ����ṹ���塣��ַƫ����:0x0138����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch1_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch1_bit_width_ind : 2;  /* bit[0-1] : ��ͨ��1ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ� */
        unsigned int  reserved                    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_bbpmst_rd_ch1_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH1_BIT_WIDTH_IND_bbpmst_rd_ch1_bit_width_ind_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH2_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH2_MODE �Ĵ����ṹ���塣��ַƫ����:0x0140����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch2_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_rd_ch2_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                       1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_rd_ch2_addr_mode     : 1;  /* bit[8]    : 1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch2_base_addr��ָ��ĵ�ַ
                                                                       1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_rd_ch2_en            : 1;  /* bit[9]    : ��ͨ��ʹ���źţ�
                                                                       1'b0:�رգ�
                                                                       1'b1:�򿪣� */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH2_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH2_MODE_bbpmst_rd_ch2_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH2_MODE_bbpmst_rd_ch2_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH2_MODE_bbpmst_rd_ch2_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH2_MODE_bbpmst_rd_ch2_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH2_MODE_bbpmst_rd_ch2_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH2_MODE_bbpmst_rd_ch2_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_RD_CH2_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x014C����ֵ:0x000F2005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch2_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch2_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch2_fifo_baddr : 8;  /* bit[8-15] : Uģ����harq���ƣ��ڶ�У��λ�������ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00 */
        unsigned int  bbpmst_rd_ch2_fifo_depth : 8;  /* bit[16-23]: Uģ����harq���ƣ��ڶ�У��λ�������ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_bbpmst_rd_ch2_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_bbpmst_rd_ch2_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_bbpmst_rd_ch2_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_bbpmst_rd_ch2_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_bbpmst_rd_ch2_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH2_BURST_BEAT_bbpmst_rd_ch2_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH2_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_RD_CH2_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0150����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch2_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch2_axi_sel : 2;  /* bit[0-1] : ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                2'b00����ͨ��ʹ��master��1
                                                                2'b01����ͨ��ʹ��master��2
                                                                2'b10����ͨ��ʹ��ram��1
                                                                �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH2_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH2_AXI_SEL_bbpmst_rd_ch2_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH2_AXI_SEL_bbpmst_rd_ch2_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH2_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH2_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x0154����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch2_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch2_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_rd_ch2_intr_mode  : 2;  /* bit[16-17]: �ö�����ͨ�������жϵķ�ʽ��
                                                                    [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                    [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù��� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH2_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH2_INTR_MODE_bbpmst_rd_ch2_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH2_INTR_MODE_bbpmst_rd_ch2_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH2_INTR_MODE_bbpmst_rd_ch2_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH2_INTR_MODE_bbpmst_rd_ch2_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_UNION
 �ṹ˵��  : BBPMST_RD_CH2_BIT_WIDTH_IND �Ĵ����ṹ���塣��ַƫ����:0x0158����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch2_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch2_bit_width_ind : 2;  /* bit[0-1] : ��ͨ��2ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ� */
        unsigned int  reserved                    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_bbpmst_rd_ch2_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH2_BIT_WIDTH_IND_bbpmst_rd_ch2_bit_width_ind_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH3_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH3_MODE �Ĵ����ṹ���塣��ַƫ����:0x0160����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch3_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_rd_ch3_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                       1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_rd_ch3_addr_mode     : 1;  /* bit[8]    : 1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch3_base_addr��ָ��ĵ�ַ
                                                                       1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_rd_ch3_en            : 1;  /* bit[9]    : ��ͨ��ʹ���źţ�
                                                                       1'b0:�رգ�
                                                                       1'b1:�򿪣� */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH3_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH3_MODE_bbpmst_rd_ch3_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH3_MODE_bbpmst_rd_ch3_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH3_MODE_bbpmst_rd_ch3_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH3_MODE_bbpmst_rd_ch3_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH3_MODE_bbpmst_rd_ch3_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH3_MODE_bbpmst_rd_ch3_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_RD_CH3_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x016C����ֵ:0x000F0005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch3_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch3_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch3_fifo_baddr : 8;  /* bit[8-15] : CģSDR_TX�����ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00 */
        unsigned int  bbpmst_rd_ch3_fifo_depth : 8;  /* bit[16-23]: CģSDR_TX�����ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_bbpmst_rd_ch3_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_bbpmst_rd_ch3_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_bbpmst_rd_ch3_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_bbpmst_rd_ch3_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_bbpmst_rd_ch3_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH3_BURST_BEAT_bbpmst_rd_ch3_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH3_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_RD_CH3_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0170����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch3_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch3_axi_sel : 2;  /* bit[0-1] : ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                2'b00����ͨ��ʹ��master��1
                                                                2'b01����ͨ��ʹ��master��2
                                                                2'b10����ͨ��ʹ��ram��1
                                                                �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH3_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH3_AXI_SEL_bbpmst_rd_ch3_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH3_AXI_SEL_bbpmst_rd_ch3_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH3_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH3_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x0174����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch3_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch3_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_rd_ch3_intr_mode  : 2;  /* bit[16-17]: �ö�����ͨ�������жϵķ�ʽ��
                                                                    [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                    [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù��� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH3_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH3_INTR_MODE_bbpmst_rd_ch3_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH3_INTR_MODE_bbpmst_rd_ch3_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH3_INTR_MODE_bbpmst_rd_ch3_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH3_INTR_MODE_bbpmst_rd_ch3_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_UNION
 �ṹ˵��  : BBPMST_RD_CH3_BIT_WIDTH_IND �Ĵ����ṹ���塣��ַƫ����:0x0178����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch3_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch3_bit_width_ind : 2;  /* bit[0-1] : ��ͨ��3ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ� */
        unsigned int  reserved                    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_bbpmst_rd_ch3_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH3_BIT_WIDTH_IND_bbpmst_rd_ch3_bit_width_ind_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH5_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH5_MODE �Ĵ����ṹ���塣��ַƫ����:0x0200����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch5_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_wr_ch5_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                       1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_wr_ch5_addr_mode     : 1;  /* bit[8]    : 1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch5_base_addr��ָ��ĵ�ַ
                                                                       1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_wr_ch5_en            : 1;  /* bit[9]    : ��д����ͨ����ʹ�ܣ�
                                                                       1��b0���ر�
                                                                       1��b1��ʹ�� */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH5_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH5_MODE_bbpmst_wr_ch5_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH5_MODE_bbpmst_wr_ch5_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH5_MODE_bbpmst_wr_ch5_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH5_MODE_bbpmst_wr_ch5_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH5_MODE_bbpmst_wr_ch5_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH5_MODE_bbpmst_wr_ch5_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH5_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_WR_CH5_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x0210����ֵ:0x000F0005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch5_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch5_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  : ���� */
        unsigned int  bbpmst_wr_ch5_fifo_baddr : 8;  /* bit[8-15] : UģRX1_dump�����ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00 */
        unsigned int  bbpmst_wr_ch5_fifo_depth : 8;  /* bit[16-23]: UģRX1_dump�����ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH5_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH5_BURST_BEAT_bbpmst_wr_ch5_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH5_BURST_BEAT_bbpmst_wr_ch5_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH5_BURST_BEAT_bbpmst_wr_ch5_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH5_BURST_BEAT_bbpmst_wr_ch5_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH5_BURST_BEAT_bbpmst_wr_ch5_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH5_BURST_BEAT_bbpmst_wr_ch5_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH5_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH5_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0214����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch5_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch5_axi_sel : 2;  /* bit[0-1] : ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                2'b00����ͨ��ʹ��master��1
                                                                2'b01����ͨ��ʹ��master��2
                                                                2'b10����ͨ��ʹ��ram��1
                                                                �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH5_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH5_AXI_SEL_bbpmst_wr_ch5_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH5_AXI_SEL_bbpmst_wr_ch5_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH5_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH5_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x0218����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch5_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch5_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_wr_ch5_intr_mode  : 2;  /* bit[16-17]: ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
                                                                    [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                    [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
                                                                    �����жϿ��Զ�ʹ�ܡ� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH5_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH5_INTR_MODE_bbpmst_wr_ch5_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH5_INTR_MODE_bbpmst_wr_ch5_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH5_INTR_MODE_bbpmst_wr_ch5_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH5_INTR_MODE_bbpmst_wr_ch5_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_CH_CLK_BYPASS_UNION
 �ṹ˵��  : BBPMST_CH_CLK_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x0224����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_ch_clk_bypass_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch_ckg_bypass : 16; /* bit[0-15] : �ֱ��Ӧbbpmstдͨ��0-15ʱ���ſ���·��Ԫ��
                                                                   1����·ʱ���ſأ�
                                                                   0����ʱ���ſأ� */
        unsigned int  bbpmst_rd_ch_ckg_bypass : 16; /* bit[16-31]: �ֱ��Ӧbbpmst��ͨ��0-15ʱ���ſ���·��Ԫ��
                                                                   1����·ʱ���ſأ�
                                                                   0����ʱ���ſأ� */
    } reg;
} BBPCOMM_BBPMST_CH_CLK_BYPASS_UNION;
#define BBPCOMM_BBPMST_CH_CLK_BYPASS_bbpmst_wr_ch_ckg_bypass_START  (0)
#define BBPCOMM_BBPMST_CH_CLK_BYPASS_bbpmst_wr_ch_ckg_bypass_END    (15)
#define BBPCOMM_BBPMST_CH_CLK_BYPASS_bbpmst_rd_ch_ckg_bypass_START  (16)
#define BBPCOMM_BBPMST_CH_CLK_BYPASS_bbpmst_rd_ch_ckg_bypass_END    (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_AXI0_STATUS_UNION
 �ṹ˵��  : BBPMST_AXI0_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0300����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_axi0_status_reg;
    struct
    {
        unsigned int  reserved_0            : 8;  /* bit[0-7]  : ���� */
        unsigned int  bbpmst_axi0_wr_status : 1;  /* bit[8]    : axi��0дͨ���Ŀ���״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
                                                                 1��b0�����У������ѱ��ͷŵ�
                                                                 1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/���� */
        unsigned int  bbpmst_axi0_rd_status : 1;  /* bit[9]    : axi��0��ͨ���Ŀ���״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
                                                                 1��b0�����У������ѱ��ͷŵ�
                                                                 1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/���� */
        unsigned int  bbpmst_axi0_status    : 1;  /* bit[10]   : axi��0�Ŀ���״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
                                                                 1��b0�����У������ѱ��ͷŵ�
                                                                 1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/���� */
        unsigned int  reserved_1            : 21; /* bit[11-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_AXI0_STATUS_UNION;
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_wr_status_START  (8)
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_wr_status_END    (8)
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_rd_status_START  (9)
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_rd_status_END    (9)
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_status_START     (10)
#define BBPCOMM_BBPMST_AXI0_STATUS_bbpmst_axi0_status_END       (10)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_AXI1_STATUS_UNION
 �ṹ˵��  : BBPMST_AXI1_STATUS �Ĵ����ṹ���塣��ַƫ����:0x0304����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_axi1_status_reg;
    struct
    {
        unsigned int  reserved_0            : 8;  /* bit[0-7]  : ���� */
        unsigned int  bbpmst_axi1_wr_status : 1;  /* bit[8]    : axi��1дͨ���Ŀ���״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
                                                                 1��b0�����У������ѱ��ͷŵ�
                                                                 1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/���� */
        unsigned int  bbpmst_axi1_rd_status : 1;  /* bit[9]    : axi��1��ͨ���Ŀ���״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
                                                                 1��b0�����У������ѱ��ͷŵ�
                                                                 1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/���� */
        unsigned int  bbpmst_axi1_status    : 1;  /* bit[10]   : axi��1�Ŀ���״̬��־�� ����ɸ��ݸ���axi�ڵĿ���״̬�����Ƿ��ܷ������������͹�������
                                                                 1��b0�����У������ѱ��ͷŵ�
                                                                 1��b1���ǿ��У�����δ�ͷţ���״̬��master�����Ը�λ/��ʱ��/���� */
        unsigned int  reserved_1            : 21; /* bit[11-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_AXI1_STATUS_UNION;
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_wr_status_START  (8)
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_wr_status_END    (8)
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_rd_status_START  (9)
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_rd_status_END    (9)
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_status_START     (10)
#define BBPCOMM_BBPMST_AXI1_STATUS_bbpmst_axi1_status_END       (10)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_ERROR_BURST_BEAT0_UNION
 �ṹ˵��  : BBPMST_ERROR_BURST_BEAT0 �Ĵ����ṹ���塣��ַƫ����:0x0308����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_error_burst_beat0_reg;
    struct
    {
        unsigned int  bbpmst_error_burst_beat0 : 4;  /* bit[0-3] : ��bbpmstдerror����ʱ���ٽ���burst������0 */
        unsigned int  reserved                 : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_ERROR_BURST_BEAT0_UNION;
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT0_bbpmst_error_burst_beat0_START  (0)
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT0_bbpmst_error_burst_beat0_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_ERROR_BURST_BEAT1_UNION
 �ṹ˵��  : BBPMST_ERROR_BURST_BEAT1 �Ĵ����ṹ���塣��ַƫ����:0x030C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_error_burst_beat1_reg;
    struct
    {
        unsigned int  bbpmst_error_burst_beat1 : 4;  /* bit[0-3] : ��bbpmstдerror����ʱ���ٽ���burst������1 */
        unsigned int  reserved                 : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_ERROR_BURST_BEAT1_UNION;
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT1_bbpmst_error_burst_beat1_START  (0)
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT1_bbpmst_error_burst_beat1_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_ERROR_BURST_BEAT2_UNION
 �ṹ˵��  : BBPMST_ERROR_BURST_BEAT2 �Ĵ����ṹ���塣��ַƫ����:0x0310����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_error_burst_beat2_reg;
    struct
    {
        unsigned int  bbpmst_error_burst_beat2 : 4;  /* bit[0-3] : ��bbpmstдerror����ʱ���ٽ���burst������2 */
        unsigned int  reserved                 : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_ERROR_BURST_BEAT2_UNION;
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT2_bbpmst_error_burst_beat2_START  (0)
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT2_bbpmst_error_burst_beat2_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_ERROR_BURST_BEAT3_UNION
 �ṹ˵��  : BBPMST_ERROR_BURST_BEAT3 �Ĵ����ṹ���塣��ַƫ����:0x0314����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_error_burst_beat3_reg;
    struct
    {
        unsigned int  bbpmst_error_burst_beat3 : 4;  /* bit[0-3] : ��bbpmstдerror����ʱ���ٽ���burst������3 */
        unsigned int  reserved                 : 28; /* bit[4-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_ERROR_BURST_BEAT3_UNION;
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT3_bbpmst_error_burst_beat3_START  (0)
#define BBPCOMM_BBPMST_ERROR_BURST_BEAT3_bbpmst_error_burst_beat3_END    (3)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_ERROR_INT_CLR_UNION
 �ṹ˵��  : BBPMST_ERROR_INT_CLR �Ĵ����ṹ���塣��ַƫ����:0x0328����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_error_int_clr_reg;
    struct
    {
        unsigned int  bbpmst_error_int_clr : 1;  /* bit[0]   : bbpmst��д�����ж�����Ĵ�������BBPMST��д��������ʱ��bbpmst_error_int��ֱ�����ɵ�ƽ�͸�BBE16\CCPU������յ��жϺ����øüĴ�������жϵ�ƽ�� */
        unsigned int  reserved             : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_ERROR_INT_CLR_UNION;
#define BBPCOMM_BBPMST_ERROR_INT_CLR_bbpmst_error_int_clr_START  (0)
#define BBPCOMM_BBPMST_ERROR_INT_CLR_bbpmst_error_int_clr_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MEM_CTRL0_BBPMST_UNION
 �ṹ˵��  : MEM_CTRL0_BBPMST �Ĵ����ṹ���塣��ַƫ����:0x032C����ֵ:0x03501050�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mem_ctrl0_bbpmst_reg;
    struct
    {
        unsigned int  mem_ctrl_s_bbpmst      : 16; /* bit[0-15] : ���˿�ram��ʱ���ơ� */
        unsigned int  mem_ctrl_d_1w2r_bbpmst : 16; /* bit[16-31]: 1w2r˫�˿�ram��ʱ���ơ� */
    } reg;
} BBPCOMM_MEM_CTRL0_BBPMST_UNION;
#define BBPCOMM_MEM_CTRL0_BBPMST_mem_ctrl_s_bbpmst_START       (0)
#define BBPCOMM_MEM_CTRL0_BBPMST_mem_ctrl_s_bbpmst_END         (15)
#define BBPCOMM_MEM_CTRL0_BBPMST_mem_ctrl_d_1w2r_bbpmst_START  (16)
#define BBPCOMM_MEM_CTRL0_BBPMST_mem_ctrl_d_1w2r_bbpmst_END    (31)


/*****************************************************************************
 �ṹ��    : BBPCOMM_MEM_CTRL1_BBPMST_UNION
 �ṹ˵��  : MEM_CTRL1_BBPMST �Ĵ����ṹ���塣��ַƫ����:0x0330����ֵ:0x00700057�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      mem_ctrl1_bbpmst_reg;
    struct
    {
        unsigned int  mem_ctrl_d_1rw2rw_bbpmst : 16; /* bit[0-15] : 1rw2rw˫�˿�ram��ʱ���ơ� */
        unsigned int  rom_ctrl_bbpmst          : 8;  /* bit[16-23]: rom��ʱ���ơ� */
        unsigned int  reserved                 : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_MEM_CTRL1_BBPMST_UNION;
#define BBPCOMM_MEM_CTRL1_BBPMST_mem_ctrl_d_1rw2rw_bbpmst_START  (0)
#define BBPCOMM_MEM_CTRL1_BBPMST_mem_ctrl_d_1rw2rw_bbpmst_END    (15)
#define BBPCOMM_MEM_CTRL1_BBPMST_rom_ctrl_bbpmst_START           (16)
#define BBPCOMM_MEM_CTRL1_BBPMST_rom_ctrl_bbpmst_END             (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_AXI_WR0_STATE_UNION
 �ṹ˵��  : AXI_WR0_STATE �Ĵ����ṹ���塣��ַƫ����:0x0344����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      axi_wr0_state_reg;
    struct
    {
        unsigned int  axi_wr0_ready  : 1;  /* bit[0]    : AXI��0��ǰд��Ӧ�ɽ�������ָʾ */
        unsigned int  reserved_0     : 3;  /* bit[1-3]  : ���� */
        unsigned int  axi_wr0_valid  : 1;  /* bit[4]    : AXI��0��ǰд��Ӧ������Чָʾ */
        unsigned int  reserved_1     : 3;  /* bit[5-7]  : ���� */
        unsigned int  axi_wr0_cur_id : 3;  /* bit[8-10] : AXI��0��ǰд��ӦID */
        unsigned int  reserved_2     : 21; /* bit[11-31]: ���� */
    } reg;
} BBPCOMM_AXI_WR0_STATE_UNION;
#define BBPCOMM_AXI_WR0_STATE_axi_wr0_ready_START   (0)
#define BBPCOMM_AXI_WR0_STATE_axi_wr0_ready_END     (0)
#define BBPCOMM_AXI_WR0_STATE_axi_wr0_valid_START   (4)
#define BBPCOMM_AXI_WR0_STATE_axi_wr0_valid_END     (4)
#define BBPCOMM_AXI_WR0_STATE_axi_wr0_cur_id_START  (8)
#define BBPCOMM_AXI_WR0_STATE_axi_wr0_cur_id_END    (10)


/*****************************************************************************
 �ṹ��    : BBPCOMM_AXI_RD0_STATE_UNION
 �ṹ˵��  : AXI_RD0_STATE �Ĵ����ṹ���塣��ַƫ����:0x0348����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      axi_rd0_state_reg;
    struct
    {
        unsigned int  axi_rd0_ready  : 1;  /* bit[0]    : AXI��0��ǰ����Ӧ�ɽ�������ָʾ */
        unsigned int  reserved_0     : 3;  /* bit[1-3]  : ���� */
        unsigned int  axi_rd0_valid  : 1;  /* bit[4]    : AXI��0��ǰ����Ӧ������Чָʾ */
        unsigned int  reserved_1     : 3;  /* bit[5-7]  : ���� */
        unsigned int  axi_rd0_cur_id : 3;  /* bit[8-10] : AXI��0��ǰ����ӦID */
        unsigned int  reserved_2     : 21; /* bit[11-31]: ���� */
    } reg;
} BBPCOMM_AXI_RD0_STATE_UNION;
#define BBPCOMM_AXI_RD0_STATE_axi_rd0_ready_START   (0)
#define BBPCOMM_AXI_RD0_STATE_axi_rd0_ready_END     (0)
#define BBPCOMM_AXI_RD0_STATE_axi_rd0_valid_START   (4)
#define BBPCOMM_AXI_RD0_STATE_axi_rd0_valid_END     (4)
#define BBPCOMM_AXI_RD0_STATE_axi_rd0_cur_id_START  (8)
#define BBPCOMM_AXI_RD0_STATE_axi_rd0_cur_id_END    (10)


/*****************************************************************************
 �ṹ��    : BBPCOMM_AXI_WR1_STATE_UNION
 �ṹ˵��  : AXI_WR1_STATE �Ĵ����ṹ���塣��ַƫ����:0x034C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      axi_wr1_state_reg;
    struct
    {
        unsigned int  axi_wr1_ready  : 1;  /* bit[0]    : AXI��1��ǰд��Ӧ�ɽ�������ָʾ */
        unsigned int  reserved_0     : 3;  /* bit[1-3]  : ���� */
        unsigned int  axi_wr1_valid  : 1;  /* bit[4]    : AXI��1��ǰд��Ӧ������Чָʾ */
        unsigned int  reserved_1     : 3;  /* bit[5-7]  : ���� */
        unsigned int  axi_wr1_cur_id : 3;  /* bit[8-10] : AXI��1��ǰд��ӦID */
        unsigned int  reserved_2     : 21; /* bit[11-31]: ���� */
    } reg;
} BBPCOMM_AXI_WR1_STATE_UNION;
#define BBPCOMM_AXI_WR1_STATE_axi_wr1_ready_START   (0)
#define BBPCOMM_AXI_WR1_STATE_axi_wr1_ready_END     (0)
#define BBPCOMM_AXI_WR1_STATE_axi_wr1_valid_START   (4)
#define BBPCOMM_AXI_WR1_STATE_axi_wr1_valid_END     (4)
#define BBPCOMM_AXI_WR1_STATE_axi_wr1_cur_id_START  (8)
#define BBPCOMM_AXI_WR1_STATE_axi_wr1_cur_id_END    (10)


/*****************************************************************************
 �ṹ��    : BBPCOMM_AXI_RD1_STATE_UNION
 �ṹ˵��  : AXI_RD1_STATE �Ĵ����ṹ���塣��ַƫ����:0x0350����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      axi_rd1_state_reg;
    struct
    {
        unsigned int  axi_rd1_ready  : 1;  /* bit[0]    : AXI��1��ǰ����Ӧ�ɽ�������ָʾ */
        unsigned int  reserved_0     : 3;  /* bit[1-3]  : ���� */
        unsigned int  axi_rd1_valid  : 1;  /* bit[4]    : AXI��1��ǰ����Ӧ������Чָʾ */
        unsigned int  reserved_1     : 3;  /* bit[5-7]  : ���� */
        unsigned int  axi_rd1_cur_id : 3;  /* bit[8-10] : AXI��1��ǰ����ӦID */
        unsigned int  reserved_2     : 21; /* bit[11-31]: ���� */
    } reg;
} BBPCOMM_AXI_RD1_STATE_UNION;
#define BBPCOMM_AXI_RD1_STATE_axi_rd1_ready_START   (0)
#define BBPCOMM_AXI_RD1_STATE_axi_rd1_ready_END     (0)
#define BBPCOMM_AXI_RD1_STATE_axi_rd1_valid_START   (4)
#define BBPCOMM_AXI_RD1_STATE_axi_rd1_valid_END     (4)
#define BBPCOMM_AXI_RD1_STATE_axi_rd1_cur_id_START  (8)
#define BBPCOMM_AXI_RD1_STATE_axi_rd1_cur_id_END    (10)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_ERROR_INT_EN_UNION
 �ṹ˵��  : BBPMST_ERROR_INT_EN �Ĵ����ṹ���塣��ַƫ����:0x0364����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_error_int_en_reg;
    struct
    {
        unsigned int  bbpmst_error_int_en : 1;  /* bit[0]   : BBPMST��д�����ж�ʹ�� */
        unsigned int  reserved            : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_ERROR_INT_EN_UNION;
#define BBPCOMM_BBPMST_ERROR_INT_EN_bbpmst_error_int_en_START  (0)
#define BBPCOMM_BBPMST_ERROR_INT_EN_bbpmst_error_int_en_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_MAINTAIN_CFG_UNION
 �ṹ˵��  : BBPMST_MAINTAIN_CFG �Ĵ����ṹ���塣��ַƫ����:0x0368����ֵ:0x00000200�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_maintain_cfg_reg;
    struct
    {
        unsigned int  bbpmst_maintain_cnt   : 4;  /* bit[0-3]  : ���ڿ�ά�ɲ⹦�ܣ���bbpmst_maintain_pulse���м��� */
        unsigned int  reserved_0            : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_maintain_pulse : 1;  /* bit[8]    : ���ڿ�ά�ɲ⣬���������ź������ڲ�����������������ʱ�Ӻ͸�λ�ź� */
        unsigned int  bbpmst_maintain_en    : 1;  /* bit[9]    : ���п�ά�ɲ⹦�ܵ�ʹ���źţ�Ϊ1ʱ�����п�ά�ɲ�Ĵ�����Ϊ0ʱ�����п�ά�ɲ�Ĵ����������� */
        unsigned int  reserved_1            : 22; /* bit[10-31]:  */
    } reg;
} BBPCOMM_BBPMST_MAINTAIN_CFG_UNION;
#define BBPCOMM_BBPMST_MAINTAIN_CFG_bbpmst_maintain_cnt_START    (0)
#define BBPCOMM_BBPMST_MAINTAIN_CFG_bbpmst_maintain_cnt_END      (3)
#define BBPCOMM_BBPMST_MAINTAIN_CFG_bbpmst_maintain_pulse_START  (8)
#define BBPCOMM_BBPMST_MAINTAIN_CFG_bbpmst_maintain_pulse_END    (8)
#define BBPCOMM_BBPMST_MAINTAIN_CFG_bbpmst_maintain_en_START     (9)
#define BBPCOMM_BBPMST_MAINTAIN_CFG_bbpmst_maintain_en_END       (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_INT_CNT_UNION
 �ṹ˵��  : BBPMST_INT_CNT �Ĵ����ṹ���塣��ַƫ����:0x036C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int_cnt_reg;
    struct
    {
        unsigned int  bbpmst_int0_cnt : 8;  /* bit[0-7]  : ���ж�0�����������м��������ڿ�ά�ɲ� */
        unsigned int  bbpmst_int1_cnt : 8;  /* bit[8-15] : ���ж�1�����������м��������ڿ�ά�ɲ� */
        unsigned int  bbpmst_int2_cnt : 8;  /* bit[16-23]: ���ж�2�����������м��������ڿ�ά�ɲ� */
        unsigned int  reserved        : 8;  /* bit[24-31]:  */
    } reg;
} BBPCOMM_BBPMST_INT_CNT_UNION;
#define BBPCOMM_BBPMST_INT_CNT_bbpmst_int0_cnt_START  (0)
#define BBPCOMM_BBPMST_INT_CNT_bbpmst_int0_cnt_END    (7)
#define BBPCOMM_BBPMST_INT_CNT_bbpmst_int1_cnt_START  (8)
#define BBPCOMM_BBPMST_INT_CNT_bbpmst_int1_cnt_END    (15)
#define BBPCOMM_BBPMST_INT_CNT_bbpmst_int2_cnt_START  (16)
#define BBPCOMM_BBPMST_INT_CNT_bbpmst_int2_cnt_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_INT0_EN_UNION
 �ṹ˵��  : BBPMST_INT0_EN �Ĵ����ṹ���塣��ַƫ����:0x0380����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int0_en_reg;
    struct
    {
        unsigned int  bbpmst_int0_en : 1;  /* bit[0]   : BBPMST��дͨ���ж�0ʹ�� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_INT0_EN_UNION;
#define BBPCOMM_BBPMST_INT0_EN_bbpmst_int0_en_START  (0)
#define BBPCOMM_BBPMST_INT0_EN_bbpmst_int0_en_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_INT1_EN_UNION
 �ṹ˵��  : BBPMST_INT1_EN �Ĵ����ṹ���塣��ַƫ����:0x0394����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int1_en_reg;
    struct
    {
        unsigned int  bbpmst_int1_en : 1;  /* bit[0]   : BBPMST��дͨ���ж�1ʹ�� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_INT1_EN_UNION;
#define BBPCOMM_BBPMST_INT1_EN_bbpmst_int1_en_START  (0)
#define BBPCOMM_BBPMST_INT1_EN_bbpmst_int1_en_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_INT2_EN_UNION
 �ṹ˵��  : BBPMST_INT2_EN �Ĵ����ṹ���塣��ַƫ����:0x03A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int2_en_reg;
    struct
    {
        unsigned int  bbpmst_int2_en : 1;  /* bit[0]   : BBPMST��дͨ���ж�2ʹ�� */
        unsigned int  reserved       : 31; /* bit[1-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_INT2_EN_UNION;
#define BBPCOMM_BBPMST_INT2_EN_bbpmst_int2_en_START  (0)
#define BBPCOMM_BBPMST_INT2_EN_bbpmst_int2_en_END    (0)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH6_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH6_MODE �Ĵ����ṹ���塣��ַƫ����:0x03B0����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch6_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_wr_ch6_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                       1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_wr_ch6_addr_mode     : 1;  /* bit[8]    : 1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch6_base_addr��ָ��ĵ�ַ
                                                                       1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_wr_ch6_en            : 1;  /* bit[9]    : ��д����ͨ����ʹ�ܣ�
                                                                       1��b0���ر�
                                                                       1��b1��ʹ�� */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH6_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH6_MODE_bbpmst_wr_ch6_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH6_MODE_bbpmst_wr_ch6_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH6_MODE_bbpmst_wr_ch6_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH6_MODE_bbpmst_wr_ch6_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH6_MODE_bbpmst_wr_ch6_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH6_MODE_bbpmst_wr_ch6_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH6_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_WR_CH6_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x03C0����ֵ:0x000F1005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch6_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch6_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  : ���� */
        unsigned int  bbpmst_wr_ch6_fifo_baddr : 8;  /* bit[8-15] : UģRX2_dump�����ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x10 */
        unsigned int  bbpmst_wr_ch6_fifo_depth : 8;  /* bit[16-23]: UģRX2_dump�����ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH6_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH6_BURST_BEAT_bbpmst_wr_ch6_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH6_BURST_BEAT_bbpmst_wr_ch6_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH6_BURST_BEAT_bbpmst_wr_ch6_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH6_BURST_BEAT_bbpmst_wr_ch6_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH6_BURST_BEAT_bbpmst_wr_ch6_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH6_BURST_BEAT_bbpmst_wr_ch6_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH6_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH6_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x03C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch6_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch6_axi_sel : 2;  /* bit[0-1] : ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                2'b00����ͨ��ʹ��master��1
                                                                2'b01����ͨ��ʹ��master��2
                                                                2'b10����ͨ��ʹ��ram��1
                                                                �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH6_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH6_AXI_SEL_bbpmst_wr_ch6_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH6_AXI_SEL_bbpmst_wr_ch6_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH6_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH6_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x03C8����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch6_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch6_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_wr_ch6_intr_mode  : 2;  /* bit[16-17]: ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
                                                                    [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                    [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
                                                                    �����жϿ��Զ�ʹ�ܡ� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH6_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH6_INTR_MODE_bbpmst_wr_ch6_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH6_INTR_MODE_bbpmst_wr_ch6_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH6_INTR_MODE_bbpmst_wr_ch6_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH6_INTR_MODE_bbpmst_wr_ch6_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH7_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH7_MODE �Ĵ����ṹ���塣��ַƫ����:0x03D0����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch7_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_wr_ch7_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                       1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_wr_ch7_addr_mode     : 1;  /* bit[8]    : 1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch7_base_addr��ָ��ĵ�ַ
                                                                       1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_wr_ch7_en            : 1;  /* bit[9]    : ��д����ͨ����ʹ�ܣ�
                                                                       1��b0���ر�
                                                                       1��b1��ʹ�� */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH7_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH7_MODE_bbpmst_wr_ch7_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH7_MODE_bbpmst_wr_ch7_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH7_MODE_bbpmst_wr_ch7_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH7_MODE_bbpmst_wr_ch7_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH7_MODE_bbpmst_wr_ch7_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH7_MODE_bbpmst_wr_ch7_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH7_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_WR_CH7_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x03E0����ֵ:0x000F2005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch7_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch7_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  : ���� */
        unsigned int  bbpmst_wr_ch7_fifo_baddr : 8;  /* bit[8-15] : Cģ��������harq���������ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x20 */
        unsigned int  bbpmst_wr_ch7_fifo_depth : 8;  /* bit[16-23]: Cģ��������harq���������ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH7_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH7_BURST_BEAT_bbpmst_wr_ch7_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH7_BURST_BEAT_bbpmst_wr_ch7_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH7_BURST_BEAT_bbpmst_wr_ch7_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH7_BURST_BEAT_bbpmst_wr_ch7_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH7_BURST_BEAT_bbpmst_wr_ch7_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH7_BURST_BEAT_bbpmst_wr_ch7_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH7_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH7_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x03E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch7_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch7_axi_sel : 2;  /* bit[0-1] : ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                2'b00����ͨ��ʹ��master��1
                                                                2'b01����ͨ��ʹ��master��2
                                                                2'b10����ͨ��ʹ��ram��1
                                                                �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH7_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH7_AXI_SEL_bbpmst_wr_ch7_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH7_AXI_SEL_bbpmst_wr_ch7_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH7_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH7_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x03E8����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch7_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch7_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_wr_ch7_intr_mode  : 2;  /* bit[16-17]: ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
                                                                    [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                    [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
                                                                    �����жϿ��Զ�ʹ�ܡ� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH7_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH7_INTR_MODE_bbpmst_wr_ch7_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH7_INTR_MODE_bbpmst_wr_ch7_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH7_INTR_MODE_bbpmst_wr_ch7_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH7_INTR_MODE_bbpmst_wr_ch7_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH8_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH8_MODE �Ĵ����ṹ���塣��ַƫ����:0x03F0����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch8_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_wr_ch8_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                       1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_wr_ch8_addr_mode     : 1;  /* bit[8]    : 1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch8_base_addr��ָ��ĵ�ַ
                                                                       1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_wr_ch8_en            : 1;  /* bit[9]    : ��д����ͨ����ʹ�ܣ�
                                                                       1��b0���ر�
                                                                       1��b1��ʹ�� */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH8_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH8_MODE_bbpmst_wr_ch8_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH8_MODE_bbpmst_wr_ch8_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH8_MODE_bbpmst_wr_ch8_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH8_MODE_bbpmst_wr_ch8_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH8_MODE_bbpmst_wr_ch8_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH8_MODE_bbpmst_wr_ch8_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH8_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_WR_CH8_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x0400����ֵ:0x000F0005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch8_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch8_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  : ���� */
        unsigned int  bbpmst_wr_ch8_fifo_baddr : 8;  /* bit[8-15] : CģSDR_RX1�����ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00 */
        unsigned int  bbpmst_wr_ch8_fifo_depth : 8;  /* bit[16-23]: CģSDR_RX1�����ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH8_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH8_BURST_BEAT_bbpmst_wr_ch8_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH8_BURST_BEAT_bbpmst_wr_ch8_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH8_BURST_BEAT_bbpmst_wr_ch8_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH8_BURST_BEAT_bbpmst_wr_ch8_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH8_BURST_BEAT_bbpmst_wr_ch8_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH8_BURST_BEAT_bbpmst_wr_ch8_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH8_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH8_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0404����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch8_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch8_axi_sel : 2;  /* bit[0-1] : ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                2'b00����ͨ��ʹ��master��1
                                                                2'b01����ͨ��ʹ��master��2
                                                                2'b10����ͨ��ʹ��ram��1
                                                                �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH8_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH8_AXI_SEL_bbpmst_wr_ch8_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH8_AXI_SEL_bbpmst_wr_ch8_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH8_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH8_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x0408����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch8_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch8_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_wr_ch8_intr_mode  : 2;  /* bit[16-17]: ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
                                                                    [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                    [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
                                                                    �����жϿ��Զ�ʹ�ܡ� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH8_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH8_INTR_MODE_bbpmst_wr_ch8_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH8_INTR_MODE_bbpmst_wr_ch8_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH8_INTR_MODE_bbpmst_wr_ch8_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH8_INTR_MODE_bbpmst_wr_ch8_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH9_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH9_MODE �Ĵ����ṹ���塣��ַƫ����:0x0410����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch9_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_wr_ch9_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                       1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_wr_ch9_addr_mode     : 1;  /* bit[8]    : 1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch9_base_addr��ָ��ĵ�ַ
                                                                       1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_wr_ch9_en            : 1;  /* bit[9]    : ��д����ͨ����ʹ�ܣ�
                                                                       1��b0���ر�
                                                                       1��b1��ʹ�� */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH9_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH9_MODE_bbpmst_wr_ch9_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH9_MODE_bbpmst_wr_ch9_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH9_MODE_bbpmst_wr_ch9_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH9_MODE_bbpmst_wr_ch9_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH9_MODE_bbpmst_wr_ch9_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH9_MODE_bbpmst_wr_ch9_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH9_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_WR_CH9_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x0420����ֵ:0x000F1005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch9_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch9_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  : ���� */
        unsigned int  bbpmst_wr_ch9_fifo_baddr : 8;  /* bit[8-15] : CģSDR_RX2�����ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x10 */
        unsigned int  bbpmst_wr_ch9_fifo_depth : 8;  /* bit[16-23]: CģSDR_RX2�����ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH9_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH9_BURST_BEAT_bbpmst_wr_ch9_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH9_BURST_BEAT_bbpmst_wr_ch9_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH9_BURST_BEAT_bbpmst_wr_ch9_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH9_BURST_BEAT_bbpmst_wr_ch9_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH9_BURST_BEAT_bbpmst_wr_ch9_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH9_BURST_BEAT_bbpmst_wr_ch9_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH9_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH9_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0424����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch9_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch9_axi_sel : 2;  /* bit[0-1] : ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                2'b00����ͨ��ʹ��master��1
                                                                2'b01����ͨ��ʹ��master��2
                                                                2'b10����ͨ��ʹ��ram��1
                                                                �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH9_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH9_AXI_SEL_bbpmst_wr_ch9_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH9_AXI_SEL_bbpmst_wr_ch9_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH9_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH9_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x0428����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch9_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch9_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_wr_ch9_intr_mode  : 2;  /* bit[16-17]: ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
                                                                    [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                    [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
                                                                    �����жϿ��Զ�ʹ�ܡ� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH9_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH9_INTR_MODE_bbpmst_wr_ch9_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH9_INTR_MODE_bbpmst_wr_ch9_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH9_INTR_MODE_bbpmst_wr_ch9_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH9_INTR_MODE_bbpmst_wr_ch9_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH10_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH10_MODE �Ĵ����ṹ���塣��ַƫ����:0x0430����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch10_mode_reg;
    struct
    {
        unsigned int  reserved_0                   : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_wr_ch10_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                        1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_wr_ch10_addr_mode     : 1;  /* bit[8]    : 1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch10_base_addr��ָ��ĵ�ַ
                                                                        1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_wr_ch10_en            : 1;  /* bit[9]    : ��д����ͨ����ʹ�ܣ�
                                                                        1��b0���ر�
                                                                        1��b1��ʹ�� */
        unsigned int  reserved_1                   : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH10_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH10_MODE_bbpmst_wr_ch10_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH10_MODE_bbpmst_wr_ch10_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH10_MODE_bbpmst_wr_ch10_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH10_MODE_bbpmst_wr_ch10_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH10_MODE_bbpmst_wr_ch10_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH10_MODE_bbpmst_wr_ch10_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH10_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_WR_CH10_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x0440����ֵ:0x000F2005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch10_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch10_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                     burst_beat==0�� burst1
                                                                     burst_beat==3�� burst4
                                                                     burst_beat==7�� burst8
                                                                     burst_beat==15��burst16
                                                                     �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0                : 4;  /* bit[4-7]  : ���� */
        unsigned int  bbpmst_wr_ch10_fifo_baddr : 8;  /* bit[8-15] : Cģ����harq����/1x_VTB�ض������ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x20 */
        unsigned int  bbpmst_wr_ch10_fifo_depth : 8;  /* bit[16-23]: Cģ����harq����/1x_VTB�ض������ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1                : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH10_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH10_BURST_BEAT_bbpmst_wr_ch10_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH10_BURST_BEAT_bbpmst_wr_ch10_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH10_BURST_BEAT_bbpmst_wr_ch10_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH10_BURST_BEAT_bbpmst_wr_ch10_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH10_BURST_BEAT_bbpmst_wr_ch10_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH10_BURST_BEAT_bbpmst_wr_ch10_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH10_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH10_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0444����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch10_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch10_axi_sel : 2;  /* bit[0-1] : ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                 2'b00����ͨ��ʹ��master��1
                                                                 2'b01����ͨ��ʹ��master��2
                                                                 2'b10����ͨ��ʹ��ram��1
                                                                 �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved               : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH10_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH10_AXI_SEL_bbpmst_wr_ch10_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH10_AXI_SEL_bbpmst_wr_ch10_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH10_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH10_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x0448����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch10_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch10_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_wr_ch10_intr_mode  : 2;  /* bit[16-17]: ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
                                                                     [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                     [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
                                                                     �����жϿ��Զ�ʹ�ܡ� */
        unsigned int  reserved                  : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH10_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH10_INTR_MODE_bbpmst_wr_ch10_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH10_INTR_MODE_bbpmst_wr_ch10_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH10_INTR_MODE_bbpmst_wr_ch10_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH10_INTR_MODE_bbpmst_wr_ch10_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH11_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH11_MODE �Ĵ����ṹ���塣��ַƫ����:0x0450����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch11_mode_reg;
    struct
    {
        unsigned int  reserved_0                   : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_wr_ch11_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                        1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_wr_ch11_addr_mode     : 1;  /* bit[8]    : 1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch11_base_addr��ָ��ĵ�ַ
                                                                        1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_wr_ch11_en            : 1;  /* bit[9]    : ��д����ͨ����ʹ�ܣ�
                                                                        1��b0���ر�
                                                                        1��b1��ʹ�� */
        unsigned int  reserved_1                   : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH11_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH11_MODE_bbpmst_wr_ch11_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH11_MODE_bbpmst_wr_ch11_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH11_MODE_bbpmst_wr_ch11_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH11_MODE_bbpmst_wr_ch11_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH11_MODE_bbpmst_wr_ch11_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH11_MODE_bbpmst_wr_ch11_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH11_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_WR_CH11_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x0460����ֵ:0x000F0005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch11_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch11_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                     burst_beat==0�� burst1
                                                                     burst_beat==3�� burst4
                                                                     burst_beat==7�� burst8
                                                                     burst_beat==15��burst16
                                                                     �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0                : 4;  /* bit[4-7]  : ���� */
        unsigned int  bbpmst_wr_ch11_fifo_baddr : 8;  /* bit[8-15] : G1ģharq���������ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00 */
        unsigned int  bbpmst_wr_ch11_fifo_depth : 8;  /* bit[16-23]: G1ģharq���������ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1                : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH11_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH11_BURST_BEAT_bbpmst_wr_ch11_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH11_BURST_BEAT_bbpmst_wr_ch11_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH11_BURST_BEAT_bbpmst_wr_ch11_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH11_BURST_BEAT_bbpmst_wr_ch11_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH11_BURST_BEAT_bbpmst_wr_ch11_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH11_BURST_BEAT_bbpmst_wr_ch11_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH11_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH11_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0464����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch11_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch11_axi_sel : 2;  /* bit[0-1] : ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                 2'b00����ͨ��ʹ��master��1
                                                                 2'b01����ͨ��ʹ��master��2
                                                                 2'b10����ͨ��ʹ��ram��1
                                                                 �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved               : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH11_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH11_AXI_SEL_bbpmst_wr_ch11_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH11_AXI_SEL_bbpmst_wr_ch11_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH11_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH11_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x0468����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch11_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch11_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_wr_ch11_intr_mode  : 2;  /* bit[16-17]: ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
                                                                     [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                     [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
                                                                     �����жϿ��Զ�ʹ�ܡ� */
        unsigned int  reserved                  : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH11_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH11_INTR_MODE_bbpmst_wr_ch11_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH11_INTR_MODE_bbpmst_wr_ch11_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH11_INTR_MODE_bbpmst_wr_ch11_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH11_INTR_MODE_bbpmst_wr_ch11_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH12_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH12_MODE �Ĵ����ṹ���塣��ַƫ����:0x0470����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch12_mode_reg;
    struct
    {
        unsigned int  reserved_0                   : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_wr_ch12_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                        1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_wr_ch12_addr_mode     : 1;  /* bit[8]    : 1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch12_base_addr��ָ��ĵ�ַ
                                                                        1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_wr_ch12_en            : 1;  /* bit[9]    : ��д����ͨ����ʹ�ܣ�
                                                                        1��b0���ر�
                                                                        1��b1��ʹ�� */
        unsigned int  reserved_1                   : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH12_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH12_MODE_bbpmst_wr_ch12_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH12_MODE_bbpmst_wr_ch12_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH12_MODE_bbpmst_wr_ch12_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH12_MODE_bbpmst_wr_ch12_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH12_MODE_bbpmst_wr_ch12_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH12_MODE_bbpmst_wr_ch12_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH12_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_WR_CH12_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x0480����ֵ:0x000F1005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch12_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch12_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                     burst_beat==0�� burst1
                                                                     burst_beat==3�� burst4
                                                                     burst_beat==7�� burst8
                                                                     burst_beat==15��burst16
                                                                     �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0                : 4;  /* bit[4-7]  : ���� */
        unsigned int  bbpmst_wr_ch12_fifo_baddr : 8;  /* bit[8-15] : G1ģdump�����ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x10 */
        unsigned int  bbpmst_wr_ch12_fifo_depth : 8;  /* bit[16-23]: G1ģdump�����ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1                : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH12_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH12_BURST_BEAT_bbpmst_wr_ch12_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH12_BURST_BEAT_bbpmst_wr_ch12_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH12_BURST_BEAT_bbpmst_wr_ch12_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH12_BURST_BEAT_bbpmst_wr_ch12_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH12_BURST_BEAT_bbpmst_wr_ch12_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH12_BURST_BEAT_bbpmst_wr_ch12_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH12_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH12_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0484����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch12_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch12_axi_sel : 2;  /* bit[0-1] : ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                 2'b00����ͨ��ʹ��master��1
                                                                 2'b01����ͨ��ʹ��master��2
                                                                 2'b10����ͨ��ʹ��ram��1
                                                                 �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved               : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH12_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH12_AXI_SEL_bbpmst_wr_ch12_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH12_AXI_SEL_bbpmst_wr_ch12_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH12_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH12_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x0488����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch12_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch12_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_wr_ch12_intr_mode  : 2;  /* bit[16-17]: ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
                                                                     [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                     [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
                                                                     �����жϿ��Զ�ʹ�ܡ� */
        unsigned int  reserved                  : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH12_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH12_INTR_MODE_bbpmst_wr_ch12_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH12_INTR_MODE_bbpmst_wr_ch12_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH12_INTR_MODE_bbpmst_wr_ch12_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH12_INTR_MODE_bbpmst_wr_ch12_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH13_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH13_MODE �Ĵ����ṹ���塣��ַƫ����:0x0490����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch13_mode_reg;
    struct
    {
        unsigned int  reserved_0                   : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_wr_ch13_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                        1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_wr_ch13_addr_mode     : 1;  /* bit[8]    : 1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch13_base_addr��ָ��ĵ�ַ
                                                                        1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_wr_ch13_en            : 1;  /* bit[9]    : ��д����ͨ����ʹ�ܣ�
                                                                        1��b0���ر�
                                                                        1��b1��ʹ�� */
        unsigned int  reserved_1                   : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH13_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH13_MODE_bbpmst_wr_ch13_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH13_MODE_bbpmst_wr_ch13_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH13_MODE_bbpmst_wr_ch13_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH13_MODE_bbpmst_wr_ch13_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH13_MODE_bbpmst_wr_ch13_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH13_MODE_bbpmst_wr_ch13_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH13_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_WR_CH13_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x04A0����ֵ:0x000F0005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch13_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch13_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                     burst_beat==0�� burst1
                                                                     burst_beat==3�� burst4
                                                                     burst_beat==7�� burst8
                                                                     burst_beat==15��burst16
                                                                     �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0                : 4;  /* bit[4-7]  : ���� */
        unsigned int  bbpmst_wr_ch13_fifo_baddr : 8;  /* bit[8-15] : G2ģharq���������ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00 */
        unsigned int  bbpmst_wr_ch13_fifo_depth : 8;  /* bit[16-23]: G2ģharq���������ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1                : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH13_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH13_BURST_BEAT_bbpmst_wr_ch13_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH13_BURST_BEAT_bbpmst_wr_ch13_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH13_BURST_BEAT_bbpmst_wr_ch13_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH13_BURST_BEAT_bbpmst_wr_ch13_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH13_BURST_BEAT_bbpmst_wr_ch13_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH13_BURST_BEAT_bbpmst_wr_ch13_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH13_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH13_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x04A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch13_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch13_axi_sel : 2;  /* bit[0-1] : ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                 2'b00����ͨ��ʹ��master��1
                                                                 2'b01����ͨ��ʹ��master��2
                                                                 2'b10����ͨ��ʹ��ram��1
                                                                 �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved               : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH13_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH13_AXI_SEL_bbpmst_wr_ch13_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH13_AXI_SEL_bbpmst_wr_ch13_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH13_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH13_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x04A8����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch13_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch13_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_wr_ch13_intr_mode  : 2;  /* bit[16-17]: ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
                                                                     [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                     [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
                                                                     �����жϿ��Զ�ʹ�ܡ� */
        unsigned int  reserved                  : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH13_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH13_INTR_MODE_bbpmst_wr_ch13_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH13_INTR_MODE_bbpmst_wr_ch13_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH13_INTR_MODE_bbpmst_wr_ch13_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH13_INTR_MODE_bbpmst_wr_ch13_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH4_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH4_MODE �Ĵ����ṹ���塣��ַƫ����:0x04B0����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch4_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_wr_ch4_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                       1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_wr_ch4_addr_mode     : 1;  /* bit[8]    : 1��b0����д����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_wr_ch4_base_addr��ָ��ĵ�ַ
                                                                       1��b1����д����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_wr_ch4_en            : 1;  /* bit[9]    : ��д����ͨ����ʹ�ܣ�
                                                                       1��b0���ر�
                                                                       1��b1��ʹ�� */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH4_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH4_MODE_bbpmst_wr_ch4_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_WR_CH4_MODE_bbpmst_wr_ch4_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_WR_CH4_MODE_bbpmst_wr_ch4_addr_mode_START      (8)
#define BBPCOMM_BBPMST_WR_CH4_MODE_bbpmst_wr_ch4_addr_mode_END        (8)
#define BBPCOMM_BBPMST_WR_CH4_MODE_bbpmst_wr_ch4_en_START             (9)
#define BBPCOMM_BBPMST_WR_CH4_MODE_bbpmst_wr_ch4_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_WR_CH4_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x04C0����ֵ:0x00073802�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch4_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch4_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_wr_ch4_fifo_baddr : 8;  /* bit[8-15] : Uģ�����ϱ����ƣ�head���֣������ڲ�дͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x38 */
        unsigned int  bbpmst_wr_ch4_fifo_depth : 8;  /* bit[16-23]: Uģ�����ϱ����ƣ�head���֣������ڲ�дͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x07 */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_bbpmst_wr_ch4_burst_beat_START  (0)
#define BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_bbpmst_wr_ch4_burst_beat_END    (3)
#define BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_bbpmst_wr_ch4_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_bbpmst_wr_ch4_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_bbpmst_wr_ch4_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_WR_CH4_BURST_BEAT_bbpmst_wr_ch4_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH4_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_WR_CH4_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x04C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch4_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch4_axi_sel : 2;  /* bit[0-1] : ����дͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                2'b00����ͨ��ʹ��master��1
                                                                2'b01����ͨ��ʹ��master��2
                                                                2'b10����ͨ��ʹ��ram��1
                                                                �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH4_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_WR_CH4_AXI_SEL_bbpmst_wr_ch4_axi_sel_START  (0)
#define BBPCOMM_BBPMST_WR_CH4_AXI_SEL_bbpmst_wr_ch4_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_WR_CH4_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_WR_CH4_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x04C8����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_wr_ch4_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_wr_ch4_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_wr_ch4_intr_mode  : 2;  /* bit[16-17]: ��д����ͨ�������жϵķ�ʽ��ȡֵ��Χ0~3
                                                                    [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                    [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù���
                                                                    �����жϿ��Զ�ʹ�ܡ� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_WR_CH4_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_WR_CH4_INTR_MODE_bbpmst_wr_ch4_intr_thres_START  (0)
#define BBPCOMM_BBPMST_WR_CH4_INTR_MODE_bbpmst_wr_ch4_intr_thres_END    (15)
#define BBPCOMM_BBPMST_WR_CH4_INTR_MODE_bbpmst_wr_ch4_intr_mode_START   (16)
#define BBPCOMM_BBPMST_WR_CH4_INTR_MODE_bbpmst_wr_ch4_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH4_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH4_MODE �Ĵ����ṹ���塣��ַƫ����:0x04D0����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch4_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_rd_ch4_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                       1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_rd_ch4_addr_mode     : 1;  /* bit[8]    : 1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch4_base_addr��ָ��ĵ�ַ
                                                                       1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_rd_ch4_en            : 1;  /* bit[9]    : ��ͨ��ʹ���źţ�
                                                                       1'b0:�رգ�
                                                                       1'b1:�򿪣� */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH4_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH4_MODE_bbpmst_rd_ch4_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH4_MODE_bbpmst_rd_ch4_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH4_MODE_bbpmst_rd_ch4_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH4_MODE_bbpmst_rd_ch4_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH4_MODE_bbpmst_rd_ch4_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH4_MODE_bbpmst_rd_ch4_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH4_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_RD_CH4_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x04DC����ֵ:0x000F1005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch4_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch4_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch4_fifo_baddr : 8;  /* bit[8-15] : Cģ�����������·������ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x10 */
        unsigned int  bbpmst_rd_ch4_fifo_depth : 8;  /* bit[16-23]: Cģ�����������·������ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH4_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH4_BURST_BEAT_bbpmst_rd_ch4_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH4_BURST_BEAT_bbpmst_rd_ch4_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH4_BURST_BEAT_bbpmst_rd_ch4_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH4_BURST_BEAT_bbpmst_rd_ch4_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH4_BURST_BEAT_bbpmst_rd_ch4_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH4_BURST_BEAT_bbpmst_rd_ch4_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH4_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_RD_CH4_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x04E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch4_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch4_axi_sel : 2;  /* bit[0-1] : ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                2'b00����ͨ��ʹ��master��1
                                                                2'b01����ͨ��ʹ��master��2
                                                                2'b10����ͨ��ʹ��ram��1
                                                                �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH4_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH4_AXI_SEL_bbpmst_rd_ch4_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH4_AXI_SEL_bbpmst_rd_ch4_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH4_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH4_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x04E4����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch4_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch4_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_rd_ch4_intr_mode  : 2;  /* bit[16-17]: �ö�����ͨ�������жϵķ�ʽ��
                                                                    [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                    [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù��� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH4_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH4_INTR_MODE_bbpmst_rd_ch4_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH4_INTR_MODE_bbpmst_rd_ch4_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH4_INTR_MODE_bbpmst_rd_ch4_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH4_INTR_MODE_bbpmst_rd_ch4_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH4_BIT_WIDTH_IND_UNION
 �ṹ˵��  : BBPMST_RD_CH4_BIT_WIDTH_IND �Ĵ����ṹ���塣��ַƫ����:0x04E8����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch4_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch4_bit_width_ind : 2;  /* bit[0-1] : ��ͨ��0ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ� */
        unsigned int  reserved                    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH4_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH4_BIT_WIDTH_IND_bbpmst_rd_ch4_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH4_BIT_WIDTH_IND_bbpmst_rd_ch4_bit_width_ind_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH5_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH5_MODE �Ĵ����ṹ���塣��ַƫ����:0x04F0����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch5_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_rd_ch5_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                       1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_rd_ch5_addr_mode     : 1;  /* bit[8]    : 1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch5_base_addr��ָ��ĵ�ַ
                                                                       1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_rd_ch5_en            : 1;  /* bit[9]    : ��ͨ��ʹ���źţ�
                                                                       1'b0:�رգ�
                                                                       1'b1:�򿪣� */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH5_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH5_MODE_bbpmst_rd_ch5_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH5_MODE_bbpmst_rd_ch5_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH5_MODE_bbpmst_rd_ch5_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH5_MODE_bbpmst_rd_ch5_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH5_MODE_bbpmst_rd_ch5_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH5_MODE_bbpmst_rd_ch5_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH5_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_RD_CH5_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x04FC����ֵ:0x000F2005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch5_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch5_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch5_fifo_baddr : 8;  /* bit[8-15] : Cģharq���������ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x20 */
        unsigned int  bbpmst_rd_ch5_fifo_depth : 8;  /* bit[16-23]: Cģharq���������ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH5_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH5_BURST_BEAT_bbpmst_rd_ch5_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH5_BURST_BEAT_bbpmst_rd_ch5_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH5_BURST_BEAT_bbpmst_rd_ch5_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH5_BURST_BEAT_bbpmst_rd_ch5_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH5_BURST_BEAT_bbpmst_rd_ch5_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH5_BURST_BEAT_bbpmst_rd_ch5_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH5_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_RD_CH5_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0500����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch5_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch5_axi_sel : 2;  /* bit[0-1] : ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                2'b00����ͨ��ʹ��master��1
                                                                2'b01����ͨ��ʹ��master��2
                                                                2'b10����ͨ��ʹ��ram��1
                                                                �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH5_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH5_AXI_SEL_bbpmst_rd_ch5_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH5_AXI_SEL_bbpmst_rd_ch5_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH5_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH5_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x0504����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch5_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch5_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_rd_ch5_intr_mode  : 2;  /* bit[16-17]: �ö�����ͨ�������жϵķ�ʽ��
                                                                    [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                    [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù��� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH5_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH5_INTR_MODE_bbpmst_rd_ch5_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH5_INTR_MODE_bbpmst_rd_ch5_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH5_INTR_MODE_bbpmst_rd_ch5_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH5_INTR_MODE_bbpmst_rd_ch5_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH5_BIT_WIDTH_IND_UNION
 �ṹ˵��  : BBPMST_RD_CH5_BIT_WIDTH_IND �Ĵ����ṹ���塣��ַƫ����:0x0508����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch5_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch5_bit_width_ind : 2;  /* bit[0-1] : ��ͨ��0ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ� */
        unsigned int  reserved                    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH5_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH5_BIT_WIDTH_IND_bbpmst_rd_ch5_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH5_BIT_WIDTH_IND_bbpmst_rd_ch5_bit_width_ind_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_INT0_CLR_E_UNION
 �ṹ˵��  : BBPMST_INT0_CLR_E �Ĵ����ṹ���塣��ַƫ����:0x051C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int0_clr_e_reg;
    struct
    {
        unsigned int  bbpmst_int0_clr_e : 2;  /* bit[0-1] : �ж�0�����ж�λ��
                                                            [1:0]���ֱ��ӦAXI 0/1�����жϵ����жϣ�������Ч�� */
        unsigned int  reserved          : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_INT0_CLR_E_UNION;
#define BBPCOMM_BBPMST_INT0_CLR_E_bbpmst_int0_clr_e_START  (0)
#define BBPCOMM_BBPMST_INT0_CLR_E_bbpmst_int0_clr_e_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_INT0_STATE_E_UNION
 �ṹ˵��  : BBPMST_INT0_STATE_E �Ĵ����ṹ���塣��ַƫ����:0x0520����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int0_state_e_reg;
    struct
    {
        unsigned int  bbpmst_int0_state_e : 2;  /* bit[0-1] : �ж�0���жϱ�־��Ϊ�������κ�Ľ����
                                                              [1:0]���ֱ��ӦAXI0/1ͨ���жϵ��жϱ�־�� */
        unsigned int  reserved            : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_INT0_STATE_E_UNION;
#define BBPCOMM_BBPMST_INT0_STATE_E_bbpmst_int0_state_e_START  (0)
#define BBPCOMM_BBPMST_INT0_STATE_E_bbpmst_int0_state_e_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_INT0_STATE_RAW_E_UNION
 �ṹ˵��  : BBPMST_INT0_STATE_RAW_E �Ĵ����ṹ���塣��ַƫ����:0x0524����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int0_state_raw_e_reg;
    struct
    {
        unsigned int  bbpmst_int0_state_raw_e : 2;  /* bit[0-1] : �ж�0���жϱ�־��Ϊ����ǰ��ԭʼ�жϱ�־��
                                                                  [1:0]���ֱ��ӦAXI0/1ͨ���жϵ��жϱ�־�� */
        unsigned int  reserved                : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_INT0_STATE_RAW_E_UNION;
#define BBPCOMM_BBPMST_INT0_STATE_RAW_E_bbpmst_int0_state_raw_e_START  (0)
#define BBPCOMM_BBPMST_INT0_STATE_RAW_E_bbpmst_int0_state_raw_e_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_INT1_CLR_E_UNION
 �ṹ˵��  : BBPMST_INT1_CLR_E �Ĵ����ṹ���塣��ַƫ����:0x0530����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int1_clr_e_reg;
    struct
    {
        unsigned int  bbpmst_int1_clr_e : 2;  /* bit[0-1] : �ж�1�����ж�λ��
                                                            [1:0]���ֱ��ӦAXI 0/1�����жϵ����жϣ�������Ч�� */
        unsigned int  reserved          : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_INT1_CLR_E_UNION;
#define BBPCOMM_BBPMST_INT1_CLR_E_bbpmst_int1_clr_e_START  (0)
#define BBPCOMM_BBPMST_INT1_CLR_E_bbpmst_int1_clr_e_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_INT1_STATE_E_UNION
 �ṹ˵��  : BBPMST_INT1_STATE_E �Ĵ����ṹ���塣��ַƫ����:0x0534����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int1_state_e_reg;
    struct
    {
        unsigned int  bbpmst_int1_state_e : 2;  /* bit[0-1] : �ж�1���жϱ�־��Ϊ�������κ�Ľ����
                                                              [1:0]���ֱ��ӦAXI0/1ͨ���жϵ��жϱ�־�� */
        unsigned int  reserved            : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_INT1_STATE_E_UNION;
#define BBPCOMM_BBPMST_INT1_STATE_E_bbpmst_int1_state_e_START  (0)
#define BBPCOMM_BBPMST_INT1_STATE_E_bbpmst_int1_state_e_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_INT1_STATE_RAW_E_UNION
 �ṹ˵��  : BBPMST_INT1_STATE_RAW_E �Ĵ����ṹ���塣��ַƫ����:0x0538����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int1_state_raw_e_reg;
    struct
    {
        unsigned int  bbpmst_int1_state_raw_e : 2;  /* bit[0-1] : �ж�1���жϱ�־��Ϊ����ǰ��ԭʼ�жϱ�־��
                                                                  [1:0]���ֱ��ӦAXI0/1ͨ���жϵ��жϱ�־�� */
        unsigned int  reserved                : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_INT1_STATE_RAW_E_UNION;
#define BBPCOMM_BBPMST_INT1_STATE_RAW_E_bbpmst_int1_state_raw_e_START  (0)
#define BBPCOMM_BBPMST_INT1_STATE_RAW_E_bbpmst_int1_state_raw_e_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_INT2_CLR_E_UNION
 �ṹ˵��  : BBPMST_INT2_CLR_E �Ĵ����ṹ���塣��ַƫ����:0x0544����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int2_clr_e_reg;
    struct
    {
        unsigned int  bbpmst_int2_clr_e : 2;  /* bit[0-1] : �ж�2�����ж�λ��
                                                            [1:0]���ֱ��ӦAXI 0/1�����жϵ����жϣ�������Ч�� */
        unsigned int  reserved          : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_INT2_CLR_E_UNION;
#define BBPCOMM_BBPMST_INT2_CLR_E_bbpmst_int2_clr_e_START  (0)
#define BBPCOMM_BBPMST_INT2_CLR_E_bbpmst_int2_clr_e_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_INT2_STATE_E_UNION
 �ṹ˵��  : BBPMST_INT2_STATE_E �Ĵ����ṹ���塣��ַƫ����:0x0548����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int2_state_e_reg;
    struct
    {
        unsigned int  bbpmst_int2_state_e : 2;  /* bit[0-1] : �ж�2���жϱ�־��Ϊ�������κ�Ľ����
                                                              [1:0]���ֱ��ӦAXI0/1ͨ���жϵ��жϱ�־�� */
        unsigned int  reserved            : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_INT2_STATE_E_UNION;
#define BBPCOMM_BBPMST_INT2_STATE_E_bbpmst_int2_state_e_START  (0)
#define BBPCOMM_BBPMST_INT2_STATE_E_bbpmst_int2_state_e_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_INT2_STATE_RAW_E_UNION
 �ṹ˵��  : BBPMST_INT2_STATE_RAW_E �Ĵ����ṹ���塣��ַƫ����:0x054C����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_int2_state_raw_e_reg;
    struct
    {
        unsigned int  bbpmst_int2_state_raw_e : 2;  /* bit[0-1] : �ж�2���жϱ�־��Ϊ����ǰ��ԭʼ�жϱ�־��
                                                                  [1:0]���ֱ��ӦAXI0/1ͨ���жϵ��жϱ�־�� */
        unsigned int  reserved                : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_INT2_STATE_RAW_E_UNION;
#define BBPCOMM_BBPMST_INT2_STATE_RAW_E_bbpmst_int2_state_raw_e_START  (0)
#define BBPCOMM_BBPMST_INT2_STATE_RAW_E_bbpmst_int2_state_raw_e_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_AXI_CLK_BYPASS_UNION
 �ṹ˵��  : BBPMST_AXI_CLK_BYPASS �Ĵ����ṹ���塣��ַƫ����:0x0550����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_axi_clk_bypass_reg;
    struct
    {
        unsigned int  bbpmst_wr_axi0_if_ckg_bypass : 1;  /* bit[0]   : bbpmst AXI0��дͨ��ʱ���ſ���·��Ԫ��
                                                                       1����·ʱ���ſأ�
                                                                       0����ʱ���ſأ� */
        unsigned int  bbpmst_rd_axi0_if_ckg_bypass : 1;  /* bit[1]   : bbpmst AXI0�ڶ�ͨ��ʱ���ſ���·��Ԫ��
                                                                       1����·ʱ���ſأ�
                                                                       0����ʱ���ſأ� */
        unsigned int  bbpmst_wr_axi1_if_ckg_bypass : 1;  /* bit[2]   : bbpmst AXI1��дͨ��ʱ���ſ���·��Ԫ��
                                                                       1����·ʱ���ſأ�
                                                                       0����ʱ���ſأ� */
        unsigned int  bbpmst_rd_axi1_if_ckg_bypass : 1;  /* bit[3]   : bbpmst AXI1�ڶ�ͨ��ʱ���ſ���·��Ԫ��
                                                                       1����·ʱ���ſأ�
                                                                       0����ʱ���ſأ� */
        unsigned int  bbpmst_sram_if_ckg_bypass    : 1;  /* bit[4]   : bbpmst sram ifʱ���ſ���·��Ԫ��
                                                                       1����·ʱ���ſأ�
                                                                       0����ʱ���ſأ� */
        unsigned int  reserved                     : 27; /* bit[5-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_AXI_CLK_BYPASS_UNION;
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_bbpmst_wr_axi0_if_ckg_bypass_START  (0)
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_bbpmst_wr_axi0_if_ckg_bypass_END    (0)
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_bbpmst_rd_axi0_if_ckg_bypass_START  (1)
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_bbpmst_rd_axi0_if_ckg_bypass_END    (1)
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_bbpmst_wr_axi1_if_ckg_bypass_START  (2)
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_bbpmst_wr_axi1_if_ckg_bypass_END    (2)
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_bbpmst_rd_axi1_if_ckg_bypass_START  (3)
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_bbpmst_rd_axi1_if_ckg_bypass_END    (3)
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_bbpmst_sram_if_ckg_bypass_START     (4)
#define BBPCOMM_BBPMST_AXI_CLK_BYPASS_bbpmst_sram_if_ckg_bypass_END       (4)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH6_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH6_MODE �Ĵ����ṹ���塣��ַƫ����:0x0560����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch6_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_rd_ch6_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                       1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_rd_ch6_addr_mode     : 1;  /* bit[8]    : 1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch6_base_addr��ָ��ĵ�ַ
                                                                       1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_rd_ch6_en            : 1;  /* bit[9]    : ��ͨ��ʹ���źţ�
                                                                       1'b0:�رգ�
                                                                       1'b1:�򿪣� */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH6_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH6_MODE_bbpmst_rd_ch6_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH6_MODE_bbpmst_rd_ch6_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH6_MODE_bbpmst_rd_ch6_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH6_MODE_bbpmst_rd_ch6_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH6_MODE_bbpmst_rd_ch6_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH6_MODE_bbpmst_rd_ch6_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH6_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_RD_CH6_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x056C����ֵ:0x000F0005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch6_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch6_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch6_fifo_baddr : 8;  /* bit[8-15] : CģSDR_TX�����ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00 */
        unsigned int  bbpmst_rd_ch6_fifo_depth : 8;  /* bit[16-23]: CģSDR_TX�����ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH6_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH6_BURST_BEAT_bbpmst_rd_ch6_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH6_BURST_BEAT_bbpmst_rd_ch6_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH6_BURST_BEAT_bbpmst_rd_ch6_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH6_BURST_BEAT_bbpmst_rd_ch6_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH6_BURST_BEAT_bbpmst_rd_ch6_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH6_BURST_BEAT_bbpmst_rd_ch6_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH6_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_RD_CH6_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0570����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch6_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch6_axi_sel : 2;  /* bit[0-1] : ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                2'b00����ͨ��ʹ��master��1
                                                                2'b01����ͨ��ʹ��master��2
                                                                2'b10����ͨ��ʹ��ram��1
                                                                �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH6_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH6_AXI_SEL_bbpmst_rd_ch6_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH6_AXI_SEL_bbpmst_rd_ch6_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH6_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH6_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x0574����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch6_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch6_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_rd_ch6_intr_mode  : 2;  /* bit[16-17]: �ö�����ͨ�������жϵķ�ʽ��
                                                                    [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                    [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù��� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH6_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH6_INTR_MODE_bbpmst_rd_ch6_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH6_INTR_MODE_bbpmst_rd_ch6_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH6_INTR_MODE_bbpmst_rd_ch6_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH6_INTR_MODE_bbpmst_rd_ch6_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH6_BIT_WIDTH_IND_UNION
 �ṹ˵��  : BBPMST_RD_CH6_BIT_WIDTH_IND �Ĵ����ṹ���塣��ַƫ����:0x0578����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch6_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch6_bit_width_ind : 2;  /* bit[0-1] : ��ͨ��0ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ� */
        unsigned int  reserved                    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH6_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH6_BIT_WIDTH_IND_bbpmst_rd_ch6_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH6_BIT_WIDTH_IND_bbpmst_rd_ch6_bit_width_ind_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH7_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH7_MODE �Ĵ����ṹ���塣��ַƫ����:0x0580����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch7_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_rd_ch7_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                       1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_rd_ch7_addr_mode     : 1;  /* bit[8]    : 1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch7_base_addr��ָ��ĵ�ַ
                                                                       1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_rd_ch7_en            : 1;  /* bit[9]    : ��ͨ��ʹ���źţ�
                                                                       1'b0:�رգ�
                                                                       1'b1:�򿪣� */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH7_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH7_MODE_bbpmst_rd_ch7_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH7_MODE_bbpmst_rd_ch7_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH7_MODE_bbpmst_rd_ch7_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH7_MODE_bbpmst_rd_ch7_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH7_MODE_bbpmst_rd_ch7_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH7_MODE_bbpmst_rd_ch7_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH7_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_RD_CH7_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x058C����ֵ:0x000F1005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch7_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch7_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch7_fifo_baddr : 8;  /* bit[8-15] : Cģ�����������·������ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x10 */
        unsigned int  bbpmst_rd_ch7_fifo_depth : 8;  /* bit[16-23]: Cģ�����������·������ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH7_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH7_BURST_BEAT_bbpmst_rd_ch7_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH7_BURST_BEAT_bbpmst_rd_ch7_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH7_BURST_BEAT_bbpmst_rd_ch7_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH7_BURST_BEAT_bbpmst_rd_ch7_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH7_BURST_BEAT_bbpmst_rd_ch7_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH7_BURST_BEAT_bbpmst_rd_ch7_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH7_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_RD_CH7_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x0590����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch7_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch7_axi_sel : 2;  /* bit[0-1] : ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                2'b00����ͨ��ʹ��master��1
                                                                2'b01����ͨ��ʹ��master��2
                                                                2'b10����ͨ��ʹ��ram��1
                                                                �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH7_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH7_AXI_SEL_bbpmst_rd_ch7_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH7_AXI_SEL_bbpmst_rd_ch7_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH7_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH7_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x0594����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch7_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch7_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_rd_ch7_intr_mode  : 2;  /* bit[16-17]: �ö�����ͨ�������жϵķ�ʽ��
                                                                    [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                    [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù��� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH7_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH7_INTR_MODE_bbpmst_rd_ch7_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH7_INTR_MODE_bbpmst_rd_ch7_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH7_INTR_MODE_bbpmst_rd_ch7_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH7_INTR_MODE_bbpmst_rd_ch7_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH7_BIT_WIDTH_IND_UNION
 �ṹ˵��  : BBPMST_RD_CH7_BIT_WIDTH_IND �Ĵ����ṹ���塣��ַƫ����:0x0598����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch7_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch7_bit_width_ind : 2;  /* bit[0-1] : ��ͨ��0ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ� */
        unsigned int  reserved                    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH7_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH7_BIT_WIDTH_IND_bbpmst_rd_ch7_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH7_BIT_WIDTH_IND_bbpmst_rd_ch7_bit_width_ind_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH8_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH8_MODE �Ĵ����ṹ���塣��ַƫ����:0x05A0����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch8_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_rd_ch8_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                       1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_rd_ch8_addr_mode     : 1;  /* bit[8]    : 1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch8_base_addr��ָ��ĵ�ַ
                                                                       1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_rd_ch8_en            : 1;  /* bit[9]    : ��ͨ��ʹ���źţ�
                                                                       1'b0:�رգ�
                                                                       1'b1:�򿪣� */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH8_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH8_MODE_bbpmst_rd_ch8_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH8_MODE_bbpmst_rd_ch8_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH8_MODE_bbpmst_rd_ch8_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH8_MODE_bbpmst_rd_ch8_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH8_MODE_bbpmst_rd_ch8_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH8_MODE_bbpmst_rd_ch8_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH8_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_RD_CH8_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x05AC����ֵ:0x000F2005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch8_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch8_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch8_fifo_baddr : 8;  /* bit[8-15] : Cģharq���������ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x20 */
        unsigned int  bbpmst_rd_ch8_fifo_depth : 8;  /* bit[16-23]: Cģharq���������ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH8_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH8_BURST_BEAT_bbpmst_rd_ch8_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH8_BURST_BEAT_bbpmst_rd_ch8_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH8_BURST_BEAT_bbpmst_rd_ch8_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH8_BURST_BEAT_bbpmst_rd_ch8_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH8_BURST_BEAT_bbpmst_rd_ch8_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH8_BURST_BEAT_bbpmst_rd_ch8_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH8_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_RD_CH8_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x05B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch8_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch8_axi_sel : 2;  /* bit[0-1] : ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                2'b00����ͨ��ʹ��master��1
                                                                2'b01����ͨ��ʹ��master��2
                                                                2'b10����ͨ��ʹ��ram��1
                                                                �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH8_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH8_AXI_SEL_bbpmst_rd_ch8_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH8_AXI_SEL_bbpmst_rd_ch8_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH8_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH8_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x05B4����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch8_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch8_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_rd_ch8_intr_mode  : 2;  /* bit[16-17]: �ö�����ͨ�������жϵķ�ʽ��
                                                                    [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                    [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù��� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH8_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH8_INTR_MODE_bbpmst_rd_ch8_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH8_INTR_MODE_bbpmst_rd_ch8_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH8_INTR_MODE_bbpmst_rd_ch8_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH8_INTR_MODE_bbpmst_rd_ch8_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH8_BIT_WIDTH_IND_UNION
 �ṹ˵��  : BBPMST_RD_CH8_BIT_WIDTH_IND �Ĵ����ṹ���塣��ַƫ����:0x05B8����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch8_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch8_bit_width_ind : 2;  /* bit[0-1] : ��ͨ��0ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ� */
        unsigned int  reserved                    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH8_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH8_BIT_WIDTH_IND_bbpmst_rd_ch8_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH8_BIT_WIDTH_IND_bbpmst_rd_ch8_bit_width_ind_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH9_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH9_MODE �Ĵ����ṹ���塣��ַƫ����:0x05C0����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch9_mode_reg;
    struct
    {
        unsigned int  reserved_0                  : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_rd_ch9_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                       1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_rd_ch9_addr_mode     : 1;  /* bit[8]    : 1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch9_base_addr��ָ��ĵ�ַ
                                                                       1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_rd_ch9_en            : 1;  /* bit[9]    : ��ͨ��ʹ���źţ�
                                                                       1'b0:�رգ�
                                                                       1'b1:�򿪣� */
        unsigned int  reserved_1                  : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH9_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH9_MODE_bbpmst_rd_ch9_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH9_MODE_bbpmst_rd_ch9_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH9_MODE_bbpmst_rd_ch9_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH9_MODE_bbpmst_rd_ch9_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH9_MODE_bbpmst_rd_ch9_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH9_MODE_bbpmst_rd_ch9_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH9_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_RD_CH9_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x05CC����ֵ:0x000F0005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch9_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch9_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                    burst_beat==0�� burst1
                                                                    burst_beat==3�� burst4
                                                                    burst_beat==7�� burst8
                                                                    burst_beat==15��burst16
                                                                    �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0               : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch9_fifo_baddr : 8;  /* bit[8-15] : G1ģharq���������ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00 */
        unsigned int  bbpmst_rd_ch9_fifo_depth : 8;  /* bit[16-23]: G1ģharq���������ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1               : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH9_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH9_BURST_BEAT_bbpmst_rd_ch9_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH9_BURST_BEAT_bbpmst_rd_ch9_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH9_BURST_BEAT_bbpmst_rd_ch9_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH9_BURST_BEAT_bbpmst_rd_ch9_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH9_BURST_BEAT_bbpmst_rd_ch9_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH9_BURST_BEAT_bbpmst_rd_ch9_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH9_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_RD_CH9_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x05D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch9_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch9_axi_sel : 2;  /* bit[0-1] : ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                2'b00����ͨ��ʹ��master��1
                                                                2'b01����ͨ��ʹ��master��2
                                                                2'b10����ͨ��ʹ��ram��1
                                                                �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved              : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH9_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH9_AXI_SEL_bbpmst_rd_ch9_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH9_AXI_SEL_bbpmst_rd_ch9_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH9_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH9_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x05D4����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch9_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch9_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_rd_ch9_intr_mode  : 2;  /* bit[16-17]: �ö�����ͨ�������жϵķ�ʽ��
                                                                    [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                    [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù��� */
        unsigned int  reserved                 : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH9_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH9_INTR_MODE_bbpmst_rd_ch9_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH9_INTR_MODE_bbpmst_rd_ch9_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH9_INTR_MODE_bbpmst_rd_ch9_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH9_INTR_MODE_bbpmst_rd_ch9_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH9_BIT_WIDTH_IND_UNION
 �ṹ˵��  : BBPMST_RD_CH9_BIT_WIDTH_IND �Ĵ����ṹ���塣��ַƫ����:0x05D8����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch9_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch9_bit_width_ind : 2;  /* bit[0-1] : ��ͨ��0ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ� */
        unsigned int  reserved                    : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH9_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH9_BIT_WIDTH_IND_bbpmst_rd_ch9_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH9_BIT_WIDTH_IND_bbpmst_rd_ch9_bit_width_ind_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH10_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH10_MODE �Ĵ����ṹ���塣��ַƫ����:0x05E0����ֵ:0x00000080�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch10_mode_reg;
    struct
    {
        unsigned int  reserved_0                   : 7;  /* bit[0-6]  : ���� */
        unsigned int  bbpmst_rd_ch10_sta_feedbk_en : 1;  /* bit[7]    : 1'b1:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ��ᷴ�����������bus�ڶԽӵ�IP��
                                                                        1'b0:��ͨ����status��ͨ���Լ�AXI���Ƿ��ͷţ����ᷴ�����������bus�ڶԽӵ�IP�� */
        unsigned int  bbpmst_rd_ch10_addr_mode     : 1;  /* bit[8]    : 1��b0���ö�����ͨ��ÿ�ΰ�������ʼ��ַΪ��bbpmst_rd_ch10_base_addr��ָ��ĵ�ַ
                                                                        1��b1���ö�����ͨ��ÿ�ΰ�������ʼ��ַ��BBP�Ľӿ���·�ṩ */
        unsigned int  bbpmst_rd_ch10_en            : 1;  /* bit[9]    : ��ͨ��ʹ���źţ�
                                                                        1'b0:�رգ�
                                                                        1'b1:�򿪣� */
        unsigned int  reserved_1                   : 22; /* bit[10-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH10_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH10_MODE_bbpmst_rd_ch10_sta_feedbk_en_START  (7)
#define BBPCOMM_BBPMST_RD_CH10_MODE_bbpmst_rd_ch10_sta_feedbk_en_END    (7)
#define BBPCOMM_BBPMST_RD_CH10_MODE_bbpmst_rd_ch10_addr_mode_START      (8)
#define BBPCOMM_BBPMST_RD_CH10_MODE_bbpmst_rd_ch10_addr_mode_END        (8)
#define BBPCOMM_BBPMST_RD_CH10_MODE_bbpmst_rd_ch10_en_START             (9)
#define BBPCOMM_BBPMST_RD_CH10_MODE_bbpmst_rd_ch10_en_END               (9)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH10_BURST_BEAT_UNION
 �ṹ˵��  : BBPMST_RD_CH10_BURST_BEAT �Ĵ����ṹ���塣��ַƫ����:0x05EC����ֵ:0x000F0005�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch10_burst_beat_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch10_burst_beat : 4;  /* bit[0-3]  : ��Master��ʽ���DPA�ϱ�ʱ������burst�����ͣ��������£�
                                                                     burst_beat==0�� burst1
                                                                     burst_beat==3�� burst4
                                                                     burst_beat==7�� burst8
                                                                     burst_beat==15��burst16
                                                                     �������ʹ��burst8�� �����������Ӳ���ڶ�дDDRʱ��̶������߷���burst8����ͬʱӲ��֧�����ݿ��β������һ��������burst8  */
        unsigned int  reserved_0                : 4;  /* bit[4-7]  :  */
        unsigned int  bbpmst_rd_ch10_fifo_baddr : 8;  /* bit[8-15] : G2ģharq���������ڲ���ͨ��ʹ�õ��첽fifoƫ�Ƶ�ַ��Ĭ��ֵΪ0x00 */
        unsigned int  bbpmst_rd_ch10_fifo_depth : 8;  /* bit[16-23]: G2ģharq���������ڲ���ͨ��ʹ�õ��첽fifo��ȣ�Ĭ��ֵΪ0x0f */
        unsigned int  reserved_1                : 8;  /* bit[24-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH10_BURST_BEAT_UNION;
#define BBPCOMM_BBPMST_RD_CH10_BURST_BEAT_bbpmst_rd_ch10_burst_beat_START  (0)
#define BBPCOMM_BBPMST_RD_CH10_BURST_BEAT_bbpmst_rd_ch10_burst_beat_END    (3)
#define BBPCOMM_BBPMST_RD_CH10_BURST_BEAT_bbpmst_rd_ch10_fifo_baddr_START  (8)
#define BBPCOMM_BBPMST_RD_CH10_BURST_BEAT_bbpmst_rd_ch10_fifo_baddr_END    (15)
#define BBPCOMM_BBPMST_RD_CH10_BURST_BEAT_bbpmst_rd_ch10_fifo_depth_START  (16)
#define BBPCOMM_BBPMST_RD_CH10_BURST_BEAT_bbpmst_rd_ch10_fifo_depth_END    (23)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH10_AXI_SEL_UNION
 �ṹ˵��  : BBPMST_RD_CH10_AXI_SEL �Ĵ����ṹ���塣��ַƫ����:0x05F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch10_axi_sel_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch10_axi_sel : 2;  /* bit[0-1] : ������ͨ����ѡ��ʹ�õ�master��ram����ѡ��
                                                                 2'b00����ͨ��ʹ��master��1
                                                                 2'b01����ͨ��ʹ��master��2
                                                                 2'b10����ͨ��ʹ��ram��1
                                                                 �������ͨ��ֻ��Ҫ1��master�ڣ����ڴ����п��ú궨�巽ʽ����һ��master�� */
        unsigned int  reserved               : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH10_AXI_SEL_UNION;
#define BBPCOMM_BBPMST_RD_CH10_AXI_SEL_bbpmst_rd_ch10_axi_sel_START  (0)
#define BBPCOMM_BBPMST_RD_CH10_AXI_SEL_bbpmst_rd_ch10_axi_sel_END    (1)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH10_INTR_MODE_UNION
 �ṹ˵��  : BBPMST_RD_CH10_INTR_MODE �Ĵ����ṹ���塣��ַƫ����:0x05F4����ֵ:0x0000FFFF�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch10_intr_mode_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch10_intr_thres : 16; /* bit[0-15] : ������ж�ʹ����Чʱ��N��ȡֵ */
        unsigned int  bbpmst_rd_ch10_intr_mode  : 2;  /* bit[16-17]: �ö�����ͨ�������жϵķ�ʽ��
                                                                     [1]������жϵ�ʹ�ܿ��أ� 1'b1��ʾһ�ΰ��������У�ÿ����N��byte�Ͳ���һ���жϣ�1'b0��ʾ�رոù���
                                                                     [0]�������жϵ�ʹ�ܿ��أ�1'b1��ʾһ�ΰ�����ȫ���������һ���жϣ�1'b0��ʾ�رոù��� */
        unsigned int  reserved                  : 14; /* bit[18-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH10_INTR_MODE_UNION;
#define BBPCOMM_BBPMST_RD_CH10_INTR_MODE_bbpmst_rd_ch10_intr_thres_START  (0)
#define BBPCOMM_BBPMST_RD_CH10_INTR_MODE_bbpmst_rd_ch10_intr_thres_END    (15)
#define BBPCOMM_BBPMST_RD_CH10_INTR_MODE_bbpmst_rd_ch10_intr_mode_START   (16)
#define BBPCOMM_BBPMST_RD_CH10_INTR_MODE_bbpmst_rd_ch10_intr_mode_END     (17)


/*****************************************************************************
 �ṹ��    : BBPCOMM_BBPMST_RD_CH10_BIT_WIDTH_IND_UNION
 �ṹ˵��  : BBPMST_RD_CH10_BIT_WIDTH_IND �Ĵ����ṹ���塣��ַƫ����:0x05F8����ֵ:0x00000002�����:32
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned int      bbpmst_rd_ch10_bit_width_ind_reg;
    struct
    {
        unsigned int  bbpmst_rd_ch10_bit_width_ind : 2;  /* bit[0-1] : ��ͨ��0ÿ��32���ض�������Ч���ݸ���ָʾ��0����ʾÿ��32���ض����ݺ�5����Ч���ݣ�1����ʾÿ��32���ض����ݺ�8����Ч���ݣ�2����ʾÿ��32���ض����ݺ�1����Ч���ݣ�3����ʾÿ��32���ض����ݺ�4����Ч���ݣ� */
        unsigned int  reserved                     : 30; /* bit[2-31]: ���� */
    } reg;
} BBPCOMM_BBPMST_RD_CH10_BIT_WIDTH_IND_UNION;
#define BBPCOMM_BBPMST_RD_CH10_BIT_WIDTH_IND_bbpmst_rd_ch10_bit_width_ind_START  (0)
#define BBPCOMM_BBPMST_RD_CH10_BIT_WIDTH_IND_bbpmst_rd_ch10_bit_width_ind_END    (1)




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

#endif /* end of bbp_guc_bbpmst_interface.h */
