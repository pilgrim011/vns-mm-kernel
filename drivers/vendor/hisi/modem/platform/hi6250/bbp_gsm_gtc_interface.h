/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : bbp_gsm_gtc_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-09-02 16:48:16
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��9��2��
    ��    ��   : h00286049
    �޸�����   : �ӡ�оƬ���V3660 BBP�Ĵ����ֲ�_GSM_GTC.xml���Զ����ɣ�����
	             ��ǰ��ʹ���������ɾ��

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "soc_interface.h"

#ifndef __BBP_GSM_GTC_INTERFACE_H__
#define __BBP_GSM_GTC_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/***======================================================================***
                     (1/9) register_define_fe_ctrl_auto
 ***======================================================================***/
/* �Ĵ���˵����
   ��      ����bit7~0��GTC SPI���ڴ�����������SPI DATA RAM�е���ʼλ��.
   UNION�ṹ ���� */
#define GBBP_GTC_SPI_RD_START_ADDR                    (SOC_BBP_GSM_GTC_BASE_ADDR + 0xA0)

/* �Ĵ���˵����
 bit[7:5]
 bit[4:0]    bit4~bit0��������Ҫ���͵�SPI����������
             00001 ��ʾ1������
             10000 ��ʾ16������
   UNION�ṹ:  GBBP_GTC_SPI_TRANS_DATA_NUM_UNION */
#define GBBP_GTC_SPI_TRANS_DATA_NUM_ADDR              (SOC_BBP_GSM_GTC_BASE_ADDR + 0xA1)

/* �Ĵ���˵����
 bit[7:1]    
 bit[0]      GTC��������SPI��������
   UNION�ṹ:  GBBP_GTC_SPI_RD_EN_UNION */
#define GBBP_GTC_SPI_RD_EN_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xA2)

/* �Ĵ���˵����
 bit[7:1]    
 bit[0]      �л���G���ߣ��л���GTC�ڲ��Ĵ���27�µ�ѡ��5��2M�����ź�
   UNION�ṹ:  GBBP_GTC_W2G_CTRL_UNION */
#define GBBP_GTC_W2G_CTRL_ADDR                        (SOC_BBP_GSM_GTC_BASE_ADDR + 0xB8)

/* �Ĵ���˵����
   ��      ����31bit�߿��������壬����bit[7:0]
               0����ʾ��Ӧ��bit��������
               1����ʾ��Ӧ��bitλ��0��
   UNION�ṹ ���� */
#define GBBP_GTC_LINE1_CTRL_BITWISE_CLR_ADDR          (SOC_BBP_GSM_GTC_BASE_ADDR + 0xB9)

/* �Ĵ���˵����
   ��      ����31bit�߿���Ч���壬����bit[7:0]
               0����ʾ��Ӧ��bit�����κδ���
               1����ʾ��Ӧ��bitλ��1��
   UNION�ṹ ���� */
#define GBBP_GTC_LINE1_CTRL_BITWISE_SET_ADDR          (SOC_BBP_GSM_GTC_BASE_ADDR + 0xBA)

/* �Ĵ���˵����
   ��      ����31bit�߿��������壬����bit[15:8]
               0����ʾ��Ӧ��bit��������
               1����ʾ��Ӧ��bitλ��0��
   UNION�ṹ ���� */
#define GBBP_GTC_LINE2_CTRL_BITWISE_CLR_ADDR          (SOC_BBP_GSM_GTC_BASE_ADDR + 0xEE)

/* �Ĵ���˵����
   ��      ����31bit�߿���Ч���壬����bit[15:8]
               0����ʾ��Ӧ��bit�����κδ���
               1����ʾ��Ӧ��bitλ��1��
   UNION�ṹ ���� */
#define GBBP_GTC_LINE2_CTRL_BITWISE_SET_ADDR          (SOC_BBP_GSM_GTC_BASE_ADDR + 0xEF)

/* �Ĵ���˵����
 bit[7:1]    GSM����MIPI����д����ʱ����Ӧ�����üĴ�������ʼ��ַ����ע�����źŰ���mipi-asm,mipi-pa���ܡ���Gģ�����߿��ء���GBBP����W�����ص�G�����߿���ʱ��Ҫ���ô�ֵ��
 bit[0]      GSM����MIPI����д���������źţ������źţ�GTC�߼�������
   UNION�ṹ:  GBBP_GTC_MIPI_START_INI_UNION */
#define GBBP_GTC_MIPI_START_INI_ADDR                  (SOC_BBP_GSM_GTC_BASE_ADDR + 0xF0)

/* �Ĵ���˵����
 bit[7]
 bit[6:0]    GSM����MIPI����д����ʱ�����β�����Ӧ�����ø�����
             ȡֵ��Χ��1~63����ʹ��ƹ������ʱ��ȡֵ��ΧΪ��1~31����
             ��ע�����źŰ���mipi-asm,mipi-pa���ܡ���Gģ�����߿��ء���GBBP����W�����ص�G�����߿���ʱ��Ҫ���ô�ֵ��
   UNION�ṹ:  GBBP_GTC_MIPI_NUM_UNION */
#define GBBP_GTC_MIPI_NUM_ADDR                        (SOC_BBP_GSM_GTC_BASE_ADDR + 0xF1)

/* �Ĵ���˵����
   ��      ����31bit�߿��������壬����bit[23:16]
               0����ʾ��Ӧ��bit��������
               1����ʾ��Ӧ��bitλ��0��
   UNION�ṹ ���� */
#define GBBP_GTC_LINE3_CTRL_BITWISE_CLR_ADDR          (SOC_BBP_GSM_GTC_BASE_ADDR + 0xF2)

/* �Ĵ���˵����
   ��      ����31bit�߿���Ч���壬����bit[23:16]
               0����ʾ��Ӧ��bit�����κδ���
               1����ʾ��Ӧ��bitλ��1��
   UNION�ṹ ���� */
#define GBBP_GTC_LINE3_CTRL_BITWISE_SET_ADDR          (SOC_BBP_GSM_GTC_BASE_ADDR + 0xF3)

/* �Ĵ���˵����
 bit[7]
 bit[6:0]    31bit�߿��������壬����bit[30:24]
             0����ʾ��Ӧ��bit��������
             1����ʾ��Ӧ��bitλ��0��
   UNION�ṹ:  GBBP_GTC_LINE4_CTRL_BITWISE_CLR_UNION */
#define GBBP_GTC_LINE4_CTRL_BITWISE_CLR_ADDR          (SOC_BBP_GSM_GTC_BASE_ADDR + 0xF4)

/* �Ĵ���˵����
 bit[7]
 bit[6:0]    31bit�߿���Ч���壬����bit[30:24]
             0����ʾ��Ӧ��bit�����κδ���
             1����ʾ��Ӧ��bitλ��1��
   UNION�ṹ:  GBBP_GTC_LINE4_CTRL_BITWISE_SET_UNION */
#define GBBP_GTC_LINE4_CTRL_BITWISE_SET_ADDR          (SOC_BBP_GSM_GTC_BASE_ADDR + 0xF5)

/* �Ĵ���˵����
 bit[7]
 bit[6]      �����߿�gtc_auxdac_enͨ�����������ź�
 bit[5]      �����߿�gtc_abb_tx_en���������ź�
 bit[4]      �����߿�gtc_abb_rxb_en���������ź�
 bit[3]      �����߿�gtc_abb_rxa_en���������ź�
 bit[2]      �����߿�gtc_flash_ctrl���������ź�
 bit[1]      �����߿�gtc_gps_ctrl���������ź�
 bit[0]      �����߿�gtc_rf_trcv_on���������ź�
   UNION�ṹ:  GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_UNION */
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_ADDR       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xF6)

/* �Ĵ���˵����
 bit[7]
 bit[6]      �����߿�gtc_auxdac_en����
 bit[5]      �����߿�gtc_abb_tx_en����ʹ���ź�
 bit[4]      �����߿�gtc_abb_rxb_en����ʹ���ź�
 bit[3]      �����߿�gtc_abb_rxa_en����ʹ���ź�
 bit[2]      �����߿�gtc_flash_ctrl����ʹ���ź�
 bit[1]      �����߿�gtc_gps_ctrl����ʹ���ź�
 bit[0]      �����߿�gtc_rf_trcv_on����ʹ���ź�
   UNION�ṹ:  GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_UNION */
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_ADDR       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xF7)


/* �Ĵ���˵����
 bit[7:2]    ����
 bit[1]      txblank��Ч����
 bit[0]      rxblank��Ч����
   UNION�ṹ:  GBBP_G_BLANK_SET_UNION
 ����1��Ч������0������*/
#define GBBP_G_BLANK_SET_ADDR                         (SOC_BBP_GSM_GTC_BASE_ADDR + 0xFC)

/* �Ĵ���˵����
 bit[7:2]    ����
 bit[1]      txblank��������
 bit[0]      rxblank��������
   UNION�ṹ:  GBBP_G_BLANK_CLR_UNION
����1��Ч������0������*/
#define GBBP_G_BLANK_CLR_ADDR                         (SOC_BBP_GSM_GTC_BASE_ADDR + 0xFB)

/***======================================================================***
                     (2/9) register_define_gtc_dlfe
 ***======================================================================***/
/* �Ĵ���˵����
 bit[7:2]    
 bit[1]      DAGC����ģʽѡ��1Ϊ����ģʽ��0ΪNB���ģʽ����ģʽ�źŵ��л�ʱ��Ҫ����ÿ������������������֮ǰ������ϡ�
 bit[0]      
   UNION�ṹ:  GBBP_GTC_DAGC_CTRL_UNION */
#define GBBP_GTC_DAGC_CTRL_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xA3)

/* �Ĵ���˵����
 bit[7]      AGC��λ���÷�ʽѡ��0����agc_init_gain���ã�1����agc_next_gain���á�
 bit[6]      
 bit[5]      ����AGC��������ģʽѡ���źš�
             0������AGC�������޲��ò�������A��
             1������AGC�������޲��ò�������B��
             ���ź���Ч���μ�CPU�����ź�cpu_fast_threshold_sel����cpu_fast_threshold_sel=1ʱ��gsp_agc_measure_mode��Ч��
 bit[4:1]    ֱ��ƫ�ú�ǰ��ͨ���������RAM��ַ����ѡ���źš�
             ���ڿ�����ʵ���д���һ��TDMA֡�л����Ƶ��Ŀ��ܣ�������Ƶ���ֱ��ƫ��ֵ��ǰ��ͨ��������������ͬ���������ͨ��3bit��ѡ��ѡ��8��ֱ��ƫ�ôֵ�ֵ��8��ǰ��ͨ������ֵ��
             AGC��λ���÷�ʽѡ��0����agc_init_gain���ã�1����agc_next_gain���á�
 bit[0]      AGCģ�鹤��ʹ���źš�
             1��DCR&AGC����������
             0��DCR&AGCֹͣ������
             ��ע����ź�ͨ�����һֱ����Ϊ�ߣ�������Ҫ�쳣��ֹAGC������
             
   UNION�ṹ:  GBBP_GTC_AGC_CTRL1_UNION */
#define GBBP_GTC_AGC_CTRL1_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xB4)

/* �Ĵ���˵����
 bit[7]      ʱ϶ǰ����ֱ��ģʽ������
             1������ʱ϶ǰֱ������ģʽ�����źű�����������������ʱ�Ĳ����ж�֮ǰ���ͣ�
             0����ʹ��ʱ϶ǰֱ������ģʽ��
 bit[6]      �ֵ�ֱ��ѡ��
             1��ѡ��ʱ϶ǰ����ֱ��������Ҫ�Ƚ���ʱ϶ǰֱ�����㣬����ʹ�øù��ܣ�
             0��ѡ��NV������ֱ����
 bit[5:4]    AGC���������ۼӴ��������á�
             [5:4] ��ʾ�����ۼӼ���ʱ�����ִ����ȣ�0��16symbol��1��32symbol��2��64symbol��3��128symbol��
 bit[3:2]    AGC���������ۼӴ��������á�
             [3:2] ��ʾ�����ۼӼ���ʱ�ڶ��ִ����ȣ�0��16symbol��1��32symbol��2��64symbol��3��128symbol��
 bit[1:0]    AGC���������ۼӴ��������á�
             [1:0] ��ʾ�����ۼӼ���ʱ��һ�ִ����ȣ�0��16symbol��1��32symbol��2��64symbol��3��128symbol��
   UNION�ṹ:  GBBP_GTC_AGC_CTRL2_UNION */
#define GBBP_GTC_AGC_CTRL2_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xB5)

/* �Ĵ���˵����
 bit[7]      AGCģ����ٲ�����ʼָʾ�źţ�1��ϵͳ���ڵ������źš��ڹ�����ʼָʾ�źŷ���֮ǰ��Ҫ���ú�AGC�ı�ʱ϶�ĳ�ʼ��λ�����ٲ��������н����������
 bit[6:5]    AGCģ��SSI����ͨ��ָʾ�źţ������ź�ƴ�ӵ�gagc_ssi_data�źŵĸ�2bitʹ�á�
 bit[4]      ���������ͨ��ֱ��ƫ������ϸ��������ߵ�ƽ��Ч�����ź���Чʱ���൱������ϸ���������ʱ�޷�������·���ܡ�
 bit[3]      ʱ϶ǰֱ�����������źš�
 bit[2]      ʱ϶ǰֱ���ۼ�ϸ���������ź�
 bit[1]      AGC����ʱ϶��ʼ��λ������Чָʾ��1��ϵͳ���ڵ������źš�����ǰ���ݽ���ʱ��100us�������źţ�����gsp_init_gain��gsp_gain_sel�ź����ʹ�á������ź���Чʱ���ⲿagc_init_gain���ڲ�agc_next_gain�ĵ�λֵ�Ż����뵽��ǰ������λ
 bit[0]      ��·����ϸ����ƫ�üĴ������㣬1��ϵͳ���ڵ������źš��Ĵ����ڵ�ֵ��Ҫ���ڱ��棬��UE�ػ�ʱ��Ҫ����ϵ�ɴ洢�Ĵ洢���ʵ��б��棬�ȵ�UE�ٹ���ʱ�ָ�ԭ���������ṩ��һ����λ��ѡ�����ȷʵ��Ҫ��λ�����ø��źż��ɣ�Ĭ����������踴λ��
   UNION�ṹ:  GBBP_GTC_AGC_START_UNION */
#define GBBP_GTC_AGC_START_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xB6)

/* �Ĵ���˵����
   ��      ������ǰ������RSSI��Ӧ��Ƶ��ŵ�8bit
   UNION�ṹ ���� */
#define GBBP_GTC_RSSI_FRQ_LOW_ADDR                    (SOC_BBP_GSM_GTC_BASE_ADDR + 0xE3)

/* �Ĵ���˵����
 bit[7]      
 bit[6:4]    �˲���ϵ��ѡ���źš�
             000��32��90K������̶��˲�ϵ����
             100��32�׿������˲�ϵ����
             010��64�׿������˲�ϵ����
             011��64��135K�̶��˲���ϵ����
             101��64��BPF�̶��˲�ϵ������ͨ��Χ46.4K~89.7K��
             110��64��80K�̶��˲�ϵ����
 bit[3:0]    ��ǰ������RSSI��Ӧ��Ƶ��Ÿ�4bit��GSP_RSSI_FRQ_LOW��GSP_RSSI_FRQ_HIGH���gsp_rssi_frq[11:0]
   UNION�ṹ:  GBBP_GTC_RSSI_FRQ_HIGH_UNION */
#define GBBP_GTC_RSSI_FRQ_HIGH_ADDR                   (SOC_BBP_GSM_GTC_BASE_ADDR + 0xE4)

/* �Ĵ���˵����
 bit[7]      8����Ƶ������ѡ���źţ���BBP�ڲ�ʵ��������Ƶ�����ֱ��֣�����ʵ����Ƶ�Եȹ��ܡ�
             1:ѡ��Ĵ���0x5068~5084
             0:ѡ��Ĵ���0x513c,0x5088~0x50a0
 bit[6]      ʱ϶ȥֱ���򿪿��أ��ߵ�ƽ��Ч,���ź���Чʱ����ʾʱ϶ȥֱ�����ܿ���������ͬʱʱ϶ȥֱ���Ƿ�����������Ҫ�ο�cpu����ȥֱ������cpu_slot_dcr_rssi_threshold
 bit[5:3]    
 bit[2:0]    bit2~0: RFÿʱ϶����ĳ�ʼ��λ��
   UNION�ṹ:  GBBP_GTC_INIT_GAIN_RFIC_UNION */
#define GBBP_GTC_INIT_GAIN_RFIC_ADDR                  (SOC_BBP_GSM_GTC_BASE_ADDR + 0xE7)

/* �Ĵ���˵����
 bit[7:6]    
 bit[5:3]    DAGC��������ϸ������λλ��Ĭ��ֵ3��d3��                                        
             3��d0��8��                                  
             3��d1��10��                                  
             3��d2��12��                                  3'd3��14��                                  
             3��d4��4��                                  
             3��d5��6��
             3'd6: 9
bit[2:0]    AGC��������ϸ������λλ��Ĭ��ֵ3��d3��                                        
             3��d0��8��                                  
             3��d1��10��                                 
             3��d2��12��                                 
             3��d3��14��                                  
             3��d4��4��                                  
             3��d5��6
             3��d6: 9
   UNION�ṹ:  GBBP_GTC_AGC_TRUNC_WIDTH_UNION */
#define GBBP_GTC_AGC_TRUNC_WIDTH_ADDR                 (SOC_BBP_GSM_GTC_BASE_ADDR + 0xED)

/* �Ĵ���˵����
 bit[7:4]    
 bit[3:1]    IQMismatchģ�鲹��ʹ���źţ��ߵ�ƽ��Ч����AGCģ������ǰ���á�
 bit[0]      RX IQMismatchУ׼���ò������ѡ���źš�����ָʾ��ǰʱ϶ʹ����һ����λУ׼�������ֵ��A��Pֵ�����ο�iq_comp_amp0~ iq_comp_amp4��
   UNION�ṹ:  GBBP_GTC_RX_IQ_COMPL_UNION */
#define GBBP_GTC_RX_IQ_COMPL_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xF9)

/* �Ĵ���˵����
 bit[7:2]    
 bit[1]      ��AGCʹ��3�ֿ��ٲ���ģʽʱ�����ٲ����ĵڶ��ֺ͵�����֮�䲻���е�λ���£����ڶ��ֺ͵����ֵĵ�λ����һ�£��ߵ�ƽ��Ч��
 bit[0]      AGC���ٲ������һ�֣�2�ֲ�����Ӧ�ڶ��֣�3�ֲ�����Ӧ�����֣���λ����ģʽѡ���źţ�1����ʾ���һ�ֲ������ò������޲��ò�������A���е�λ�о���0��ʾ���һ�ֲ�������ԭ���ٲ����������ޡ�
   UNION�ṹ:  GBBP_GTC_FAST_MEAS_SEL_CFG_UNION */
#define GBBP_GTC_FAST_MEAS_SEL_CFG_ADDR               (SOC_BBP_GSM_GTC_BASE_ADDR + 0xFD)



/***======================================================================***
                     (3/9) register_define_gtc_gsrch
 ***======================================================================***/
/* �Ĵ���˵����
 bit[7]      ���ǿ������DRSSI��ʹ�ܿ��أ���ʹ����Чʱ���������DRSSIֵ��Ч��
             CPU�ӿ��������òμ���ַ0x01124�Ĵ�������
             ��λĬ��ֵΪ0

 bit[6:4]    CPU��FB������λ�õĵ�������ҪΪ�����Ʒ��ն���Ƶġ�
             000:��������001������1(symbol)��
             010������2��011������3
             111����ǰ��1��110����ǰ��2��
             101����ǰ��3��100����ǰ��4
             ��λĬ��ֵΪ3��b000
             ������������ģʽ����Ϊ111��101ʱ��Ч���������õ���FBλ�ø���gtc_fb_pos_adjֵ����������һ֡����sb������

 bit[3:1]    ����ģʽ���ã�
             111(FB+AFC+SB)����BBP�����FB�������Զ�����AFC��SBͬ����Ӧ�ó���Ϊ��ʼС��ͬ����
			 100��FB����������FB��������cpu_fb_peak_window��ֻ����FB������Ӧ�ó���Ϊר��̬�½���BSIC����
             110(FB+AFC)�����г�ʼС��ͬ�������FB������AFC�����о���
			 101(FB+SB)������FB������SB������������AFC��Ӧ�ó���Ϊ��С��������ע����������Ҳ������"100+001"ģʽ�������ģʽ����
             001��SB������ֻ����SBͬ����������FB������AFC����ʱgsp_srch_starat��λ������ǰ������ʷ��Ϣ����100ģʽ����ó���FBλ�ã����������SB��λ��34�����ţ�������FB����λ����34�����ŵ���������Ӱ�졣Ӧ�ó���ΪBSIC��֤��
             010����ʾֻ����AFC����ʱgsp_srch_start��λ�ü�ΪFB��λ�ã�Ӧ�ó���ΪIDLE̬�µ�������AFC��
             011�����ʾֻ����AFC��SB����ʱgsp_srch_start��λ�ü�ΪFB��λ�ã�Ӧ�ó���ΪNB���ǰ��AFC��SBͬ��
             ��λĬ��ֵΪ3��b000

 bit[0]      ����ʹ���źţ������������ڼ䶼����Ϊ�ߵ�ƽ��
             CPU�ӿ��������üĴ�������
             ��λĬ��ֵΪ0
             �����������У����Խ����ź����ͣ�������������
             ����������ж����͸��ź�
   UNION�ṹ:  GBBP_GTC_SRCH_CFG_UNION */
#define GBBP_GTC_SRCH_CFG_ADDR                        (SOC_BBP_GSM_GTC_BASE_ADDR + 0xC3)

/* �Ĵ���˵����
 bit[7]      1��ʶ��ǰ������������0��ʶ��ǰ�Ƿ�����������������������ʱ���������ø��źš�
 bit[6]      ������ƫʹ�ܣ�0��ʾ�رվ�ƫ��1��ʾ�򿪡�Ҳ�������ڶ�����NB��ƫ�����Ƿ���������ʱ������ʹ�þ�ƫ�����������������Ƶ��һ����Ҳ���ܴ򿪾�ƫ�������Ӱ��VCTXO��
 bit[5:1]
 bit[0]      cpu�������������źţ������źš�ÿ����������ʱ��Ҫ��һ�Σ�1��Ч����ͬ��,GTCģ���ڲ���������ʹ������Ҫ��qb�ڵĵ�һ��clk_sys����Ч,GTC�߼������㡣��gsp_srch_mod=001ʱ��gsp_srch_start������ǰ��ǰĬ�ϵ�SBλ��34�����Ų�����
             ע����������ʱ��������gsp_nb_afc_en=0��
   UNION�ṹ:  GBBP_GTC_SRCH_START_UNION */
#define GBBP_GTC_SRCH_START_ADDR                      (SOC_BBP_GSM_GTC_BASE_ADDR + 0xC4)

/* �Ĵ���˵����
 bit[7:3]    
 bit[2]      ����FB��SBģʽʹ���źţ��������������Զ�����
 bit[1]      �����źţ�����RAM�е����ݣ�����SB���������ź�û�пտ���ʱ����Ч����������001�����Ĳ���
 bit[0]      �����������SB���ݴ洢��ʱ�̣�GTCָ�����á���DAGC���ݱȿտ������ӳ�1slot�����ģ���ڲ�ʵ�ʿ�ʼ�洢��ʱ��Ӧ�ӳ�1slot��
             ע����������ʱ��������gsp_nb_afc_en=0��
   UNION�ṹ:  GBBP_GTC_SB_SAVE_START_UNION */
#define GBBP_GTC_SB_SAVE_START_ADDR                   (SOC_BBP_GSM_GTC_BASE_ADDR + 0xD0)

/* �Ĵ���˵����
   ��      ����������ô洢SB���ݵķ�����������ֵΪ156~224֮�䣬��Ҫ��gsp_start_save_sb֮ǰ�������
   UNION�ṹ ���� */
#define GBBP_GTC_SB_SAVE_LEN_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xD1)



/***======================================================================***
                     (4/9) register_define_gtc_dem
 ***======================================================================***/
/* �Ĵ���˵����
 bit[7]      1��ʾ�Ƿ���С��
             0��ʾ����С��
             ����TOAֵ��·�ϱ�
 bit[6:4]    �������ʱ��ʱ϶�ţ�����TOAֵ��·�ϱ�
 bit[3:1]    ѵ���������
             000��0�飻001��1�飻
             010��2�飻011��3�飻
             100��4�飻101��5�飻
             110��6�飻111��7��
             ��λĬ��ֵΪ0
 bit[0]      NB���ʹ���źţ��ߵ�ƽ��Ч����NB���������һֱΪ�ߣ�����������ǰҲ��Ҫ�����ź���1
             CPU�ӿ��������òμ���ַ0x01124�Ĵ�������
             ע�⣺����ҪNB�����ʱ����ر�gsp_srch_en(����μ�0x01124�Ĵ���)��������̬ʱ����������FB/SB����ʱ������ά��gsp_nb_demod_enΪ�ߣ������������ȼ����ڽ����
             ��λĬ��ֵΪ0
   UNION�ṹ:  GBBP_GTC_DEMOD_PARA1_UNION */
#define GBBP_GTC_DEMOD_PARA1_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xB0)

/* �Ĵ���˵����
 bit[7:3]    PS��DATAҵ����
             ����ä����־�洢λ�ö�ʱ϶�ĵ�һ,�ڶ���������
             ���ģ����壬������ʱ϶������BURST����ä����־����
             �洢��3��0��7��4��11��8��15��12��23��20��27��24λ�ã���ÿ�����ĵ�һ��BURSTä����־�ֱ�����0��4��8��12��20��24λ��,ÿ�����ĵڶ���BURSTä����־�ֱ�����1��5��9��13��21��25λ��,������������
             ��λĬ��ֵΪ0
             �����CS�����PS�̶�λ�õĿ����ŵ������������Ϊ16��19
 bit[2]      LSȥֱ��ʹ���źţ�0��ʾ�رգ�1��ʾ�򿪡�Ϊ��֤���ܣ�����26M��Ƶ��򿪣�����Ƶ����رա��Ҵ򿪸ù���ʱ����Ҫͬʱ��AGCģ���ʱ϶ƽ��ȥֱ��������8PSK���Ʒ�ʽ��Ч��
 bit[1:0]    ���е��Ʒ�ʽָʾ 00 GMSK���� 01 8PSK����,10��ʾ���е��Ʒ�ʽδ֪��11 �����壻
             ������ͬһ������������burstͬʱ���д�ĸ��ʷǳ�С��������ͬһ����ǰ����ʱ϶����Ϊͬһ�ֵ���ģʽ�����ڽ�������͵��ĸ�burstʱֱ������ǰ����burst�о��ĵ��Ʒ�ʽ���н�������ǰ����ʱ϶�����ĵ��Ʒ�ʽ��ͬ������Ҫ�о�������burst��������Ҫ�о����ĸ�burst��ǰ����burst�п϶�������burst��ͬһ�ֵ���ģʽ�����ڽ�����ĸ�burstʱֱ������ǰ����burst�о����ռ�����ĵ��Ʒ�ʽ���н��.
             ��λĬ��ֵΪ2��b00
   UNION�ṹ:  GBBP_GTC_DEMOD_PARA2_UNION */
#define GBBP_GTC_DEMOD_PARA2_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xB1)

/* �Ĵ���˵����
 bit[7]      
 bit[6:0]    ���BURST���ݴ洢��ʼλ��ָʾ�������CS��ҵ����ʼλ�ö�ӦΪ26��֡��ӳ��λ�ã�ӳ�䵽36��36��gsp_dl_burst_sav_cycle-1�ڵı�ţ������EGPRS/GPRSҵ�񣬲����ǵ�ʱ϶���Ƕ�ʱ϶��ʱ϶�����еĵ�һ��ʱ϶��������ݹ̶������0��3��6��9��ʱ϶�����еĵڶ���ʱ϶��������ݹ̶������12��15��18��21��ʱ϶�����еĵ�����ʱ϶��������ݹ̶������24��27��30��33��ʱ϶�����еĵ��ĸ�ʱ϶��������ݹ̶������36��39��42��45��λ�ã�ʱ϶�����еĵ����ʱ϶��������ݹ̶������81��84��87��90��ʱ϶�����еĵ�����ʱ϶��������ݹ̶������93��96��99��102���������PCCCH��PBCCH����BCCH��CCCH��SDCCH�ȣ����Դ����68��71��SACCH�����72��75λ�ã�PTCCH�����76��79λ�ã����������ŵ������������������ҵ���BURST���ѭ�����ڣ��μ������GTC���ã�gsp_dl_burst_sav_cycle���������ƣ������SCH�������ݴ����80λ�á���λĬ��ֵΪ80��
   UNION�ṹ:  GBBP_GTC_DEM_PARA3_UNION */
#define GBBP_GTC_DEM_PARA3_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xB2)

/* �Ĵ���˵����
 bit[7:4]    
 bit[3:2]    �˲���ϵ��ѡ��λ
             2��b00���˲���0���޸���
             2��b01���˲���1��+200Khz����
             2��b10���˲���2��-200Khz����
             2��b11���˲���3��
             200Khz����
 bit[1]      ��Ƶ���ģ��ʹ���źš���Ƶ���ƹ��ܽ������NB�����ʹ�ã�����ģʽ�£�FB��SB����������Ƶ��⡣
 bit[0]      ����NB��������źţ������źţ�
             GTCģ���ڲ���������ʹ������Ҫ��qb�ڵĵ�һ��clk_sys����Ч,GTC�߼�������
   UNION�ṹ:  GBBP_GTC_DEMOD_START_UNION */
#define GBBP_GTC_DEMOD_START_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xB3)

/* �Ĵ���˵����
 bit[7]      NB-AFCʹ���źţ�1��Ч��
             Ĭ��ֵΪ0��
             ע������������ʱ�����źű�������Ϊ�㣬CPU�ӿ��������òμ���ַ0x01124�Ĵ������á�
 bit[6]      ������NBʱ����ƫʹ���źš�
             1��ʾ���о�ƫ��
             0��ʾ����ƫ
             ���ø��ź�ʹ��ʱ����ͬʱ����gsp_nco_ini_value
 bit[5]      ������㵱ǰNBλ�õ�ѡ���źš�
             1��d1����ʾѡ���������ĵ�ǰNBλ�õ���ֵ��
             1��d0����ʾѡ��GBBP����ĵ�ǰNBλ�õ���ֵ������ģʽ������ؽ����ź�����Ϊ0,������ģʽ����Ҫͬʱ����gsp_nb_pos����
             Ĭ��ֵΪ0
 bit[4]      ѡ���Ƿ��ڱ�ʱ϶��������Alpha�˲�����ƽ�źš�
             1����������Alpha�˲���ϵ��Ϊcpu_alpha_parameter;
             0������������Alpha�˲���
             Ĭ��ֵΪ1
 bit[3:0]    ������ģʽ�����������ĵ�ǰNBλ�õĵ���ֵ������ģʽ�¸��źſ�������Ϊ0
             �����ȡֵ��Χ��-1~7����λΪ���š������ʾ���磺
             4��b1111����ʾ��ǰ��NBλ�ýϵ�ǰ��ʱ϶ͷҪ��ǰ1�����ţ�
             4��b0000����ʾ��ǰ��NBλ�����õ��ڵ�ǰ��ʱ϶ͷ��
             4��b0001����ʾ��ǰ��NBλ�ýϵ�ǰ��ʱ϶ͷҪ�ӳ�1�����ţ�
             4��b0010����ʾ��ǰ��NBλ�ýϵ�ǰ��ʱ϶ͷҪ�ӳ�2�����ţ�
             ������������
             4��b0111����ʾ��ǰ��NBλ�ýϵ�ǰ��ʱ϶ͷҪ�ӳ�7�����š�
             
   UNION�ṹ:  GBBP_GTC_TOA_PARA_UNION */
#define GBBP_GTC_TOA_PARA_ADDR                        (SOC_BBP_GSM_GTC_BASE_ADDR + 0xBD)

/* �Ĵ���˵����
   ��      ��������Ƶƫ��ֵ�ĵ�8bit�����÷���ͬGSP_NCO_INI_VALUE_HI��
   UNION�ṹ ���� */
#define GBBP_GTC_NCO_INI_VALUE_LOW_ADDR               (SOC_BBP_GSM_GTC_BASE_ADDR + 0xCD)

/* �Ĵ���˵����
   ��      ��������Ƶƫ��ֵ�ĸ�8bit��ÿ����������ǰ��PHY�����øó�ֵ����һ������ĳ������������Ϊ0��
               ÿ������ͬ����ɺ�PHY��Ӧ�����жϣ���ȡncell_nco_cpu����ȡ���µ�Ƶƫ�������棬����һ������ͬһ����ʱ�����ø�gtc_nco_ini_value_hi����������Ĳο�����ͼ��
   UNION�ṹ ���� */
#define GBBP_GTC_NCO_INI_VALUE_HI_ADDR                (SOC_BBP_GSM_GTC_BASE_ADDR + 0xCE)



/***======================================================================***
                     (5/9) register_define_gtc_gcipher
 ***======================================================================***/
/* �Ĵ���˵����
 bit[7]      1��ʾ��������A5���ܡ�ÿ���м��ܲ������źű������á�
 bit[6]      
 bit[5:4]    ����֡�ŵ�����־
             11��ʾ���뵽����ģ���FN��Ҫ����1������01��ʾ���뵽����ģ���FN��Ҫ����1����;
             10��00��ʾ�޼ӣ���1����;
             ��λĬ��ֵΪ00������ʹ����Ӧ������Ϊ00��01��11�ǳ���ʱ�Ĺ��ģʽ.
 bit[3:1]    ������A51����A52,A53�㷨ѡ��
             gtc_ul_gsm_alg_sel[2:0] =1��ʾѡ��A51�㷨 
             gtc_ul_gsm_alg_sel[2:0] =7��ʾѡ��A53�㷨
 bit[0]      ���н���ģ�鹤��ģʽѡ��,
             1��ʾ���з�����Ҫ����
             0��ʾ���з��䲻��Ҫ
             Ĭ��ֵΪ0
   UNION�ṹ:  GBBP_GTC_A5_CIPH_CFG_UNION */
#define GBBP_GTC_A5_CIPH_CFG_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xC6)

/* �Ĵ���˵����
 bit[7:6]    
 bit[5:4]    ����֡�ŵ�����־��
             11��ʾ���뵽����ģ���FN��Ҫ����1������01��ʾ���뵽����ģ���FN��Ҫ����1������
             10��00��ʾ�޼ӣ���1������
             ��λĬ��ֵΪ00������ʹ����Ӧ������Ϊ00��01��11�ǳ���ʱ�Ĺ��ģʽ
 bit[3:1]    ����A51����A52,A53�㷨ѡ��
             gtc_dl_gsm_alg_sel[2:0] =1��ʾѡ��A51�㷨��
             gtc_dl_gsm_alg_sel[2:0] =7��ʾѡ��A53�㷨
 bit[0]      ���н���ģ�鹤��ģʽѡ��
             1��ʾ������Ҫ���ܣ�
             0��ʾ���в����ܣ�
             Ĭ��ֵΪ0
             ���PS��ҵ���SCH��BURSTʱ������Ϊ0 
   UNION�ṹ:  GBBP_GTC_A5_DECIPH_CFG_UNION */
#define GBBP_GTC_A5_DECIPH_CFG_ADDR                   (SOC_BBP_GSM_GTC_BASE_ADDR + 0xC5)



/***======================================================================***
                     (6/9) register_define_gtc_gdec
 ***======================================================================***/
/* �Ĵ���˵����
 bit[7]      1��ʾѭ���ϱ�ģʽʹ�ܣ���ʱ��������������ϱ��жϣ�
             0��ʾ�����ϱ�ģʽʹ�ܣ�����������󻺴��ϱ��жϡ�
 bit[6:0]    һ������±�ʾ����ҵ�����.������Ϊ120��123��ʾ����ҵ����� 
             120 ��ʾCS���AFSҵ��
             121 ��ʾCS���AHSҵ��
             122 ��ʾPS��ҵ��HARQ���������ش���
             123 ��ʾHARQ�ϲ�����
             ��λĬ��ֵΪ7��d0
             
   UNION�ṹ:  GBBP_GTC_DL_CB_INDEX_UNION */
#define GBBP_GTC_DL_CB_INDEX_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xC7)

/* �Ĵ���˵����
 bit[7]      1��ʾ����AMR ��SPEECH̬
             0��ʾ����AMR ��DTX̬
             Ĭ��ֵΪ1
 bit[6:0]    ��ʾ���������ĵ�һ��BURST��VALPP��ֵ�洢RAM�е�λ�ñ�š������CS��ҵ����ʼλ����36��36��gsp_dl_burst_sav_cycle-1���������������ڸ�֡��ӳ����ʼλ�����ã��������EGPRS/GPRSҵ�񣬲����ǵ�ʱ϶���Ƕ�ʱ϶������Ե�һ��ʱ϶���õ�������룬������Ϊ0������Եڶ���ʱ϶���õ�������룬������Ϊ12������Ե�����ʱ϶���õ�������룬������Ϊ24������Ե��ĸ�ʱ϶���õ�������룬������Ϊ36������Ե���ʱ϶���õ�������룬������Ϊ81������Ե�����ʱ϶���õ�������룬������Ϊ93����SDCCH��PBCCH��BCCH��CCCH����Ϊ68������SACCH����Ϊ72��PTCCH������Ϊ76���ر�ע�⣺����ǰ�����ҵ�񣬼��赱ǰ��������ʱ����λ��Ϊa���ҵ���ǰ�����ϱ�����ʧ��ԭ��ΪFACCH_Hǰ�ĸ�BURSTʱ�����´���������Ӧ�ý���������Ȼ����Ϊa�����´�������ɺ��������´�����ʱӦ������Ϊa��4��gsp_dl_burst_sav_cycle��ȡģ��Ȼ�����36��ֵ������δ����λ�ã����������ҵ����Ҫ������á���λĬ��ֵδ80
   UNION�ṹ:  GBBP_GTC_DEC_BURST_POS_UNION */
#define GBBP_GTC_DEC_BURST_POS_ADDR                   (SOC_BBP_GSM_GTC_BASE_ADDR + 0xC8)

/* �Ĵ���˵����
 bit[7]      FACCH����ģʽѡ��AFS��FS��EFS��1 ��ʾ����������ж��Ƿ�ΪFACCH͵֡�������,���߼�����FACCH����,�������,���߼���������������룻0 ��ʾֱ������FACCH������������CRCУ�����ж��Ƿ�ΪFACCH͵֡��
             AHS��HS��1 ��ʾ����������ж��Ƿ�ΪFACCH͵֡�������,���߼�����FACCH����,�������,���߼���������������룻0��ʶֱ����ΪFACCH���롣
             Ĭ��ֵΪ1
 bit[6:5]    ������õ���ʷCMIֵ
             Ĭ��ֵΪ0x0
 bit[4]      ��ʾ��ǰ֡�ŵ�CMI��CMCָʾ��0��ʾ��CMI֡��1��ʾ��CMC֡����λĬ��ֵΪ0
 bit[3:2]    
 bit[1:0]    gtc_enhanced_dec_mode[1]��1��ʾ��ǿ������ģʽʹ�ܣ�0��ʾ���ô�ͳVTB����ģʽ
             gtc_enhanced_dec_mode[0]��1��ʾ����ǿ������ģʽ��MCS5-69ҵ����ô�ͳVTB����ģʽ��0��ʾMCS5-69ҵ�������ǿ������ģʽ��
             MCS7~9������֧����ǿ�����롣
             ʵ��ʹ���У�
             1������MCS5~9������Ϊ��ǿ�����룬���о���ҵ��ΪMCS7~9ʱ����ʱBBP���ô�ͳVTB����ģʽ��ͬʱcb1_crc_result[7:0]��cb2_crc_result[7:0]��cb3_crc_result[7:0]�ϱ��������Ч��
             
             2���ش�MCS7~9����Ϊ��ǿ�����룬��ʱMCS7~9������ǿ�����룬ͬʱcb1_crc_result[7:0]��cb2_crc_result[7:0]��cb3_crc_result[7:0]�ϱ��������Ч��
             Ĭ��Ϊ2��b10
             
   UNION�ṹ:  GBBP_GTC_DEC_TYPE1_UNION */
#define GBBP_GTC_DEC_TYPE1_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xC9)

/* �Ĵ���˵����
 bit[7]      1��ʾ�������HARQ����ʹ�ܣ�0��ʾ�ù�������
             Ĭ��ֵΪ0
 bit[6]      1��ʾ����bit ib��ID_MARKER bit������������ͳ��
             0��ʾ����bit ib��ID_MARKER bit��������������ͳ��
             Ĭ��ֵΪ0
 bit[5]      1��ʾ��bepͳ�ƹ��ܣ�0��ʾ�ر�bepͳ�ƹ��ܣ�Ĭ��ֵΪ0
 bit[4]      1��ʾ EDGEҵ����USF����BER��BEPͳ�ƣ�Ĭ��ֵΪ0
 bit[3:2]    
 bit[1:0]    00 ��ʾ��GPRS���磬�������������Ϣ����CS4��MCS1234����ΪCS4
             01 ��ʾ��EGPRS���磬�����������Ϣ����CS4��MCS1234����ΪMCS1234���ù��������ã�
             10 ��ʾ����MCS1234��HEADER�����룬�����������CRCУ����ȷ����ΪMCS1234��������ΪCS4
             Ĭ��ֵΪ0x2
             
   UNION�ṹ:  GBBP_GTC_DEC_TYPE2_UNION */
#define GBBP_GTC_DEC_TYPE2_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xCA)

/* �Ĵ���˵����
 bit[7]      
 bit[6:0]    ��HARQ��������б�ʾ��Ҫ��harq�ϲ��ĵ�һ�����Ķ���ʼλ�ã���HARQ��ֵ���������Ϊ��һ������д��ʼλ�á���Repeat FACCH/SACCHҵ��ȡֵֻ��Ϊ0~7������ҵ��ȡֵ��Χ��0~127����V3R3��V8R1��HARQ���ư汾�������÷�Χͳһ��Ϊ0~127����
             Ĭ��ֵΪ0
   UNION�ṹ:  GBBP_GTC_HARQ_POS1_UNION */
#define GBBP_GTC_HARQ_POS1_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xCB)

/* �Ĵ���˵����
 bit[7]      
 bit[6:0]    ��HARQ��������б�ʾ��Ҫ��harq�ϲ��ĵڶ������Ķ���ʼλ�ã���HARQ��ֵ���������Ϊ�ڶ�������д��ʼλ�á�
             Ĭ��ֵΪ1
   UNION�ṹ:  GBBP_GTC_HARQ_POS2_UNION */
#define GBBP_GTC_HARQ_POS2_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xCC)

/* �Ĵ���˵����
 bit[7]      
 bit[6:0]    bit6��bit0������HARQ�ϲ����������һ����飨Ӧ��ΪDATA�飩��CB_INDEX����λĬ��ֵΪ7��d52�������MCS6��9��MCS5��7�ϲ�����ô����ѡ������һ����飨Ӧ��ΪDATA�飩��cb_index��������
   UNION�ṹ:  GBBP_GTC_HARQ1_CB_INDEX_UNION */
#define GBBP_GTC_HARQ1_CB_INDEX_ADDR                  (SOC_BBP_GSM_GTC_BASE_ADDR + 0xCF)

/* �Ĵ���˵����
 bit[7]      ��������BERģ��ʹ���źţ��ߵ�ƽ��Ч������Ҫʱ�ضϣ��Խ�ʡ���ģ�
             Ĭ��ֵΪ1
 bit[6]      ��������BLERģ��ʹ���źţ��ߵ�ƽ��Ч������Ҫʱ�ضϣ��Խ�ʡ���ģ�
             ��λĬ��ֵΪ1
             
 bit[5:0]    ����������BURSTѭ�����ڣ��ò���ֻ��CS��ҵ����Ч������λĬ��ֵΪ24����ʾ����Ϊ24����22BURST��֯��ҵ������Ҫ��������������á�
             000000��ʾ����Ϊ0,
             ����
             100000��ʾ����Ϊ32
             ��������Ϊ44
             ��λĬ��ֵΪ6��d24
   UNION�ṹ:  GBBP_GTC_DL_BURST_CYCLE_UNION */
#define GBBP_GTC_DL_BURST_CYCLE_ADDR                  (SOC_BBP_GSM_GTC_BASE_ADDR + 0xD2)

/* �Ĵ���˵����
 bit[7]      ���������ϱ�BER�����źţ������ź�,GTC�߼�������
 bit[6]      ���������ϱ�BLER�����źţ������ź�,GTC�߼�������
 bit[5]      
 bit[4:2]    ������������ʱ��Ӧ��ʱ϶��
 bit[1]      1��ʾ����������Ҫ�ϱ��жϣ��������ж�ģʽֻ��gtc_cycle_rpt_enΪ0����Ч
 bit[0]      NB����ҵ������������ź�,GTC�߼�������
   UNION�ṹ:  GBBP_GTC_DEC_START_UNION */
#define GBBP_GTC_DEC_START_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xD3)

/* �Ĵ���˵����
 bit[7:4]    bit3~bit0���ֱ��ʾ��ǰ����Ѱ������ʱ��Ч��BURST�Ƿ���ڣ���0011��ʶ��һ�����ڶ���BURST���ڣ����������ĸ�BURST�������ݲ��㡣
             1100��ʶ�����������ĸ�BURST���ڣ���һ���ڶ���BURST�������ݲ��㡣
             Ĭ��ֵΪ0xF
 bit[3:2]    
 bit[1]      1��ʾ����ǿ�������UT��֤ģʽ�������ã�Ĭ��ֵΪ0
 bit[0]      1��ʾ����ģʽ�ǲ���ģʽ����ʱ����ģ�鲻��֡�����о�
   UNION�ṹ:  GBBP_GTC_DEC_TEST_MODE_EN_UNION */
#define GBBP_GTC_DEC_TEST_MODE_EN_ADDR                (SOC_BBP_GSM_GTC_BASE_ADDR + 0xE0)

/* �Ĵ���˵����
   ��      ������������8��BURST�Ƿ���Ҫ�����ֵ�������������ʹ�����ã�bit0��7�ֱ��ʾBURST0��7��ʹ�����ã�0��ʾ�����ֵ����ʹ�ã�1��ʾʹ��VALPP RAM�ж��������ݣ�����о���Ѱ������ä�����쵼�µ���ֵ������Ȼ����Ч��
               �������Ҫ��������ǰ�����ֵ���㹦�ܣ��ò���һ��Ҫ����Ϊ8��hff��xx1ģʽ��������ǰ�ò���Ҳһ��Ҫ����Ϊ8��hff
   UNION�ṹ ���� */
#define GBBP_GTC_DEC_BURST_MAP_INFO_ADDR              (SOC_BBP_GSM_GTC_BASE_ADDR + 0xE8)



/***======================================================================***
                     (7/9) register_define_gtc_gglb
 ***======================================================================***/
/* �Ĵ���˵����
   ��      ����bit7~bit0����ʾ8��CPU�ɱ���ж�,bitλ��1�Ļ�����ʾ�ڵ�ǰʱ�̲���һ���ɱ���жϣ�������ͬʱ��8���ɱ���жϲ�����
   UNION�ṹ ���� */
#define GBBP_GTC_CPU_GRM_INT_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xBC)

/* �Ĵ���˵����
   ��      ����GRIFģ�鵱ǰburst����ֵ��8bit�������GTC_RX_LEN_HIGH,��λĬ��ֵΪ8'd0
   UNION�ṹ ���� */
#define GBBP_GTC_RX_LEN_LOW_ADDR                      (SOC_BBP_GSM_GTC_BASE_ADDR + 0xC0)

/* �Ĵ���˵����
   ��      ����GRIFģ�鵱ǰburst����ֵ��8bit�����8bit��ͬ��ʾ���ճ��ȣ������õ�λΪ���㣬��λĬ��ֵΪ8'd0.
   UNION�ṹ ���� */
#define GBBP_GTC_RX_LEN_HIGH_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xC1)

/* �Ĵ���˵����
 bit[7:3]    
 bit[2]      GRIFģ�����ֹͣ�źţ�һ��ϵͳʱ�����ڿ��.��gsp_rx_low_len��gsp_rx_high_len������Ϊ0ʱ,��ʾ��������,��ʱ������gsp_rx_stop��ֹͣ����.����gsp_rx_stop�������򰴳��Ƚ��յ�ģʽ����1���ᵼ�½�����ֹ
 bit[1]      GRIFģ����������źţ�һ��ϵͳʱ�����ڿ��
 bit[0]      
   UNION�ṹ:  GBBP_GTC_GRIF_CTRL_UNION */
#define GBBP_GTC_GRIF_CTRL_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xC2)



/***======================================================================***
                     (8/9) register_define_gtc_gul
 ***======================================================================***/
/* �Ĵ���˵����
 bit[7:5]    
 bit[4]      ����ABB�ڲ�GAPC DAC����ѡ���źš�                1��TXAGC DAC��          0��RAMP DAC��             ע����ǰRF C02�汾�У�GMSKʱ����Ϊ0��ʾ���£�8pskʱ����Ϊ1��ʾ���£�0��ʾVBIAS��
 bit[3]      target������APC�������������źš�д1����һ��target�����õ�APC����������Ӧ���ڶ�ʱ϶���ʱ仯�����ڲ�����һ��104M���壨������frac_cnt=46��������GTC�ڲ���������note������������16����������������źţ�����μ�����������ʱ��ͼ��
 bit[2]      ����APC���������źš�д1����Ŀ�깦�ʵ�ѹֵΪgsp_pa_init�ĵ���APC�������ڲ�����һ��104M���塣���߼��ڲ�һ�δﵽ��Ŀ�깦�ʵ�ѹֵ�������ø������ź�������APC���TXAGC DAC����Ŀ�����
 bit[1]      GSPֹͣAPC�����������źš�д1ֹͣAPC�����������ڲ�����һ��104M���塣���ø������ź�������APC���RAMP DAC����Ŀ�����
 bit[0]      GSP����APC������1��104M�����壨������frac_cnt=94��������GTC�ڲ����������ø������ź�������APC���RAMP DAC����Ŀ�����
   UNION�ṹ:  GBBP_GTC_PA_CTRL_CFG_UNION */
#define GBBP_GTC_PA_CTRL_CFG_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xA4)

/* �Ĵ���˵����
   ��      ����APC������������ʱ�䳤�ȣ�����ָ�״������µ�Ŀ��ֵgsp_pa_targetʱ��ʼ������ʼ�����µ���ʼֵ��ʱ�����ʱ�䣨����μ�����ʱ��ͼ���źŵĺ��壩����λQb��Ĭ��ֵΪ4��burst���ȡ����ź����õ��ǵ�8bit
   UNION�ṹ ���� */
#define GBBP_GTC_PA_LEN_LOW_CFG_ADDR                  (SOC_BBP_GSM_GTC_BASE_ADDR + 0xA5)

/* �Ĵ���˵����
 bit[7:5]    
 bit[4:0]    APC������������ʱ�䳤�ȣ�����ָ�״������µ�Ŀ��ֵgsp_pa_targetʱ��ʼ������ʼ�����µ���ʼֵ��ʱ�����ʱ�䣨����μ�����ʱ��ͼ���źŵĺ��壩����λQb��Ĭ��ֵΪ4��burst���ȡ����ź����õ��Ǹ�5bit
   UNION�ṹ:  GBBP_GTC_PA_LEN_HIGH_CFG_UNION */
#define GBBP_GTC_PA_LEN_HIGH_CFG_ADDR                 (SOC_BBP_GSM_GTC_BASE_ADDR + 0xA6)

/* �Ĵ���˵����
   ��      ����GSP����APCĿ���ѹֵ�����ź����õ��ǵ�8bit
   UNION�ṹ ���� */
#define GBBP_GTC_PA_TARGET_LOW_CFG_ADDR               (SOC_BBP_GSM_GTC_BASE_ADDR + 0xA7)

/* �Ĵ���˵����
 bit[7:5]    ָʾ�������µ�����ϵ�������ţ�ȷ����gsp_pa_start����gsp_pa_change��Чʱ,��ֵ�Ѿ����á���������ȡֵ��Χ��0��3��note������gsp_pa_changeʱ��ramp-down��ϵ��gsp_pa_coeff_index[1:0]��gsp_pa_change��Ӧ��ϵ�������ž�������������gsp_pa_start��Ӧ��ϵ��gsp_pa_coeff_index[1:0]������
 bit[4:2]    
 bit[1:0]    GSP����APCĿ���ѹֵ�����ź����õ��Ǹ�2bit
   UNION�ṹ:  GBBP_GTC_PA_TARGET_HIGH_CFG_UNION */
#define GBBP_GTC_PA_TARGET_HIGH_CFG_ADDR              (SOC_BBP_GSM_GTC_BASE_ADDR + 0xA8)

/* �Ĵ���˵����
   ��      ����APC���³�ʼ���ʵ�ѹֵ��Ҳ����Ϊ����APC������Ŀ�깦�ʵ�ѹֵ�����ź����õ��ǵ�8bit,���ź�Ҳ��������Vbias���ܵĿ��Ƶ�ѹֵ��Ϊ���źŵĵ�8bit��
   UNION�ṹ ���� */
#define GBBP_GTC_PA_INIT_LOW_CFG_ADDR                 (SOC_BBP_GSM_GTC_BASE_ADDR + 0xA9)

/* �Ĵ���˵����
 bit[7]      
 bit[6:2]    ָʾ��ǰ���µĵ��������º����µ�����ͬ�����䷶Χֵ��8��16��Ĭ��ֵΪ16��
 bit[1:0]    APC���³�ʼ���ʵ�ѹֵ��Ҳ����Ϊ����APC������Ŀ�깦�ʵ�ѹֵ�����ź����õ��Ǹ�2bit
   UNION�ṹ:  GBBP_GTC_PA_INIT_HIGH_CFG_UNION */
#define GBBP_GTC_PA_INIT_HIGH_CFG_ADDR                (SOC_BBP_GSM_GTC_BASE_ADDR + 0xAA)

/* �Ĵ���˵����
 bit[7]      ��gsp_mod_symbol_l_length[7:0]���9bit�ĵ��Ƴ��ȣ��ñ���Ϊ���λ��gsp_mod_symbol_l_length[7:0]Ϊ��8bit��ѭ������0��������Ҳ��źš�ֻ��ʹ��gsp_mod_stopֹͣ��
 bit[6:0]    bit6~0: ���źű�ʾgsp_mod_start��Ҫ��QB�ڲ���λ����Ϣ(������QB��96����һ�ĵ�λ�ò���)��λ����Ϣ����Ϊ0~95(ע���ֵӦ������Ϊλ�ü�1��ֵ,����47~0~46),����gsp_mod_start�������ø��ź�(���λ�ò���,���Բ�������).��λĬ��ֵΪ77;
   UNION�ṹ:  GBBP_GTC_MOD_START_POS_UNION */
#define GBBP_GTC_MOD_START_POS_ADDR                   (SOC_BBP_GSM_GTC_BASE_ADDR + 0xAC)

/* �Ĵ���˵����
   ��      �������Ʒ��Ÿ���(��1��burst�����ڼ��ǳ�������Χ��0��148*2)��������ʱ�����ż�������gtc_mod_symbol_lengthʱ������ģ��ֹͣ�����
               ��gtc_mod_symbol_length =0ʱ��ѭ������0��������Ҳ��źš�ֻ��ʹ��gtc_mod_stopֹͣ��
               ��λĬ��ֵΪ0�����ƹ����У��ò���Ӧ����
   UNION�ṹ ���� */
#define GBBP_GTC_MOD_SYMBOL_LENGTH_ADDR               (SOC_BBP_GSM_GTC_BASE_ADDR + 0xAD)

/* �Ĵ���˵����
 bit[7:1]    
 bit[0]      �������ͣ�1��ʾ8PSK��0��ʾGMSK����λĬ��ֵΪ0�����ƹ����У��ò���Ӧ���֡�HUASHAN�汾���������0
   UNION�ṹ:  GBBP_GTC_MOD_TYPE_UNION */
#define GBBP_GTC_MOD_TYPE_ADDR                        (SOC_BBP_GSM_GTC_BASE_ADDR + 0xAE)

/* �Ĵ���˵����
 bit[7:2]    
 bit[1]      bit1: CPU ����GTCֹͣ���ƣ�һ�����塣��gsp_mod_symbol_length=0ʱ��ѭ������ָ��λ�ã���ʱֻ����gsp_mod_stopֹͣ���ơ�,GTC�߼�������
 bit[0]      bit0: CPU����GTC�������ƣ�һ�����壬������ʱ϶ʱ��CPU����Ҫÿ��ʱ϶������һ�Σ�����ʱ���߼��������Ƿ��Ƕ�ʱ϶.���������ø�ָ��֮ǰ������һ����ʱָ���֤�����һ��QB��ǰ���ʱ��Ϳ�ʼ����gsp_mod_startָ��Ӷ���֤������������һ��BURST��ͷλ�ö��룬GTC�߼������㡣��Ҫ����Ԥ���Ƴ����Լ�����ͨ������ʱ
   UNION�ṹ:  GBBP_GTC_MOD_CTRL_UNION */
#define GBBP_GTC_MOD_CTRL_ADDR                        (SOC_BBP_GSM_GTC_BASE_ADDR + 0xAF)

/* �Ĵ���˵����
 bit[7]      
 bit[6:0]    ����ҵ��������
   UNION�ṹ:  GBBP_UL_CB1_INDEX_UNION */
#define GBBP_UL_CB1_INDEX_ADDR                        (SOC_BBP_GSM_GTC_BASE_ADDR + 0xD4)

/* �Ĵ���˵����
 bit[7:6]    FACCH͵֡��־��           01: ��ʾ��ǰ����֮ǰ������һ��FACCH/H���룬��֯ʱ���ܸ���͵֡λ�á�         10: ��ʾ��ǰ����֮ǰ������һ��FACCH/F���룬��֯ʱ���ܸ���͵֡λ�á�      00/11����ʾ��ǰ����֮ǰû������FACCH�������FACCH͵֡�Ե�ǰ����û��Ӱ�죬����������֯��              ע���ñ�־�������22��BURST��֯��ȵ�����ҵ�񣨰���F9.6/F4.8/H4.8/H2.4/F14.4���£���Ҫ���ã�����ҵ�����������ã���FACCH������ҵ��֮�����SACCHҵ�񣨵����洢��ʱ����͵֡��־����������ҵ��֮ǰ������Ա���
 bit[5:4]    ���д����������ʼλ��ָʾ��־��                   00: ��ʾ���0����ʼλ�ñ�־��                     01:��ʾ���1����ʼλ�ñ�־��                    10: ��ʾ���2����ʼλ�ñ�־��                    11: ��ʾ���3����ʼλ�ñ�־��                     ��λĬ��ֵΪ2��b00
 bit[3:0]    
   UNION�ṹ:  GBBP_GTC_UL_CB_NUM_UNION */
#define GBBP_GTC_UL_CB_NUM_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xD7)

/* �Ĵ���˵����
 bit[7:6]    [7:6]��ʾDATA2�Ĵ�׷�
             00����
             01��P1
             10��P2
             11��P3
             ��λĬ��ֵΪ4��b0000
 bit[5:4]    [5:4]��ʾDATA1��DATA���Ĵ�׷�ʽ��                00���ޣ�                   01��P1��                 10��P2��                11��P3��                 ��λĬ��ֵΪ4��b0000��
 bit[3:2]    [3:2]����ʾ���ڱ���id1��Ϣ��       00:CODEC_MODE_1��01:CODEC_MODE_2��10:CODEC_MODE_3��11:CODEC_MODE_4��        ��λĬ��ֵΪ4'b0000�����Э����û�б���id0,id1,���õ���id��ע����ô��idֵ������id0�ϣ�����ʱ�ǵ�2bit��Ч��������Ա�����id1,��ô��������id1����ʱ��2bit��Ч��
 bit[1:0]    [1:0]����ʾ���ڱ���id0��Ϣ00:CODEC_MODE_1��01:CODEC_MODE_2��10:CODEC_MODE_3��11:CODEC_MODE_4��    
   UNION�ṹ:  GBBP_GTC_UL_PARA21_UNION */
#define GBBP_GTC_UL_PARA21_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xD8)

/* �Ĵ���˵����
 bit[7:6]    
 bit[5:0]    RACHҵ����BS����վ����BSIC���أ���λĬ��ֵΪ6��b000000��ע��BSIC��MSB��bit0,LSB��bit5��
   UNION�ṹ:  GBBP_GTC_RACH_BSIC_UNION */
#define GBBP_GTC_RACH_BSIC_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xD9)

/* �Ĵ���˵����
 bit[7]      
 bit[6:0]    ��ʾ��ǰ�������ݵ�һ��BURST�ڱ���洢RAM��ram611x16s���е�λ�ñ��:��λĬ��ֵΪ7��d0��   �ο��������£�0��12��24��36��                      PS��ҵ�񣺶�Ӧ�ڵ�һ����飬����Ϊ0����ʱmap���4��burst���δ�����׵�ַΪ0��3��6��9��ram�У�Ϊ������gsp_ map_burst_pos���ã���                   �ڶ����������Ϊ12��map���4��burst���δ����12��15��18��21��             �������������Ϊ24��map���4��burst���δ����24��27��30��33��             ���ĸ��������Ϊ36��map���4��burst���δ����36��39��42��45��36 �� 59�� CS��ҵ��64 �� 67�� SACCH��68 �� 71�� PTCCH��72 �� 75�����������ŵ���76      �� RACH��                �ر�ע�⣺����ǰ�����ҵ�񣬼��赱ǰ��������ʱ����λ��Ϊa������һ��FACCH/H���룬��Ҫ����2��SPEECH�ı��룬�����´�ֱ����a+4λ�á�
   UNION�ṹ:  GBBP_GTC_COD_BURST_POS_UNION */
#define GBBP_GTC_COD_BURST_POS_ADDR                   (SOC_BBP_GSM_GTC_BASE_ADDR + 0xDA)

/* �Ĵ���˵����
 bit[7]      ���б�����̵�ʹ���źš� ��λĬ��ֵΪ0
 bit[6]      
 bit[5:0]    ���б�����BURSTѭ�����ڣ��ò���ֻ��CS��ҵ����Ч������CS��ҵ��ӳ��ĸ�֡���ڣ�.��λĬ��ֵΪ24��
   UNION�ṹ:  GBBP_GTC_UL_BURST_CYCLE_UNION */
#define GBBP_GTC_UL_BURST_CYCLE_ADDR                  (SOC_BBP_GSM_GTC_BASE_ADDR + 0xDB)

/* �Ĵ���˵����
 bit[7:1]    
 bit[0]      ���б��������źţ������ź�,GTC�߼�������
   UNION�ṹ:  GBBP_GTC_UL_COD_START_UNION */
#define GBBP_GTC_UL_COD_START_ADDR                    (SOC_BBP_GSM_GTC_BASE_ADDR + 0xDC)

/* �Ĵ���˵����
 bit[7]      1 ��ʾ��CPU�����Ƶ���ǰRAM���ݵ�д�롣0 ��ʾ�����б��������Ƶ���ǰRAM���ݵ�д�롣��λĬ��ֵΪ0
 bit[6]      
 bit[5:2]    ����NB�Ӽ�1ѵ���������0000���Ӽ�1��0��ѵ������0001���Ӽ�1��1��ѵ������0010���Ӽ�1��2��ѵ������0011���Ӽ�1��3��ѵ������0100���Ӽ�1��4��ѵ������0101���Ӽ�1��5��ѵ������0110���Ӽ�1��6��ѵ������0111���Ӽ�1��7��ѵ����������NB�Ӽ�2ѵ���������1000���Ӽ�2��0��ѵ������1001���Ӽ�2��1��ѵ������1010���Ӽ�2��2��ѵ������1011���Ӽ�2��3��ѵ������1100���Ӽ�2��4��ѵ������1101���Ӽ�2��5��ѵ������1110���Ӽ�2��6��ѵ������1111���Ӽ�2��7��ѵ������AB������������ã�����ֻ��0000��0001��0010������Ч��λĬ��ֵΪ4��b0000
 bit[1]      BURST���ͱ�־��1��ʾNB��0��ʾAB����λĬ��ֵΪ0��
 bit[0]      �������ͱ�־��0��ʾGMSK���ƣ�1��ʾ8PSK���ơ���λĬ��ֵΪ0��HUASHAN�汾���������Ϊ0��
   UNION�ṹ:  GBBP_GTC_UL_MAP_PARA_UNION */
#define GBBP_GTC_UL_MAP_PARA_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xDD)

/* �Ĵ���˵����
 bit[7]      1��ʾʹ��MAP��RAM(����ģ����������RAM)ƹ���л�ʹ�ܣ�0��ʾ����ģ��̶���ƹRAM(��ʱCPUд����������RAMҲֻ��д��ƹRAM)����λĬ��ֵΪ1
 bit[6:0]    ��Ҫ��ȥ��BURST�����ݴ洢λ��ָʾ����ѡ��Ϊ����RAM��ÿ��BURST�洢����ʼ��ַ���ο�gsp_ul_cod_burst_pos[6:0]��λ�ñ�ŷ�ʽ������ͬ���ǣ����ź��·����ǵ�ǰ׼�����Ƶ�BURSTλ�ñ�ţ��������������������ʼBURST��λ�ñ�š���
             Ĭ��ֵΪ0
   UNION�ṹ:  GBBP_GTC_MAP_BURST_POS_UNION */
#define GBBP_GTC_MAP_BURST_POS_ADDR                   (SOC_BBP_GSM_GTC_BASE_ADDR + 0xDE)

/* �Ĵ���˵����
 bit[7:1]    
 bit[0]      ��BURSTӳ�������źţ��ߵ�ƽ�����źţ���ǰ���������ź�6.25��Symble��,GTC�߼�������
   UNION�ṹ:  GBBP_GTC_MAP_START_UNION */
#define GBBP_GTC_MAP_START_ADDR                       (SOC_BBP_GSM_GTC_BASE_ADDR + 0xDF)

/* �Ĵ���˵����
   ��      ����bit[0]:����ʹ�ܡ�0Ϊԭʼ���ģʽ��1Ϊ����ģʽ��bit[2:1]:������λ���ơ�0Ϊֹͣ���ƣ����0����1Ϊ�������һ��ֵ��״̬��2Ϊ��������ȫ0��3Ϊ��������ȫ1�� bit[3]:��ʼ��λ���ơ�0Ϊ���´��㿪ʼ��1Ϊ�ӵ�ǰ��λ��ʼ��                bit[4]:1ΪУ׼ģʽ������ģ      �������cpu_i_mod_data��cpu_q_mod_data���ơ�bit[5]:�����ֶ�,��������ģʽ��                  bit[6]:��burstģʽ��1��ʾ֧�ִ���148��burst��0��ʾburst�������Ϊ148������Ԥ���Ƴ��ȣ��� ���ڶ�ʱ϶ģʽ�����Ƴ��ȳ���148ʱ����������ȫ0����ȫ1����bit[2:1]�Ŀ���0��1��bit[7]: Ԥ��������ѡ��1��ʾGMSK����ȫ1��8PSK��Ӧ001����0��ʾGMSK����ȫ0��8PSK��Ӧ111��
   UNION�ṹ ���� */
#define GBBP_GTC_ULMOD_TEST_MOD_LOW_ADDR              (SOC_BBP_GSM_GTC_BASE_ADDR + 0xE5)

/* �Ĵ���˵����
 bit[7:4]    
 bit[3:0]    bit[3:0]:Ԥ���Ƴ��ȣ�0��ʾ������Ԥ���ƣ�Ĭ��ֵΪ4�����ƹ����У��ò���Ӧ����
   UNION�ṹ:  GBBP_GTC_ULMOD_TEST_MOD_HIGH_UNION */
#define GBBP_GTC_ULMOD_TEST_MOD_HIGH_ADDR             (SOC_BBP_GSM_GTC_BASE_ADDR + 0xE6)

/* �Ĵ���˵����
 bit[7:5]    
 bit[4]      IQ������·ָʾ��1��ʾIQ������·��ֻ���HD3/HD5��������GTC���á������Ҫ��·HD35���ܣ�����Ҫ����cpu_hd35_cal_bypass��
 bit[3:1]    ȥ3��5��г��ģ������ʹ�ò���ѡ���źţ�GTC���á�Ϊ��ȷ��У׼������ʱ��Ч����gsp_mod_start֮ǰ���ô�ѡ���ź���Ч��
 bit[0]      ȥ3��5��г��ģ������ʹ�ܣ�GTC���á��ڵ�������ǰ���á�
   UNION�ṹ:  GBBP_GTC_HD35_CAL_UNION */
#define GBBP_GTC_HD35_CAL_ADDR                        (SOC_BBP_GSM_GTC_BASE_ADDR + 0xFA)



/***======================================================================***
                     (9/9) register_define_gtc_timing
 ***======================================================================***/
/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define GBBP_TIMING_SLOT_LOW_ADDR                     (SOC_BBP_GSM_GTC_BASE_ADDR + 0xBE)

/* �Ĵ���˵����
 bit[7:2]    
 bit[1:0]    
   UNION�ṹ:  GBBP_TIMING_SLOT_HIGH_UNION */
#define GBBP_TIMING_SLOT_HIGH_ADDR                    (SOC_BBP_GSM_GTC_BASE_ADDR + 0xBF)



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
                     (1/9) register_define_fe_ctrl_auto
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : GBBP_GTC_SPI_TRANS_DATA_NUM_UNION
 �ṹ˵��  : GTC_SPI_TRANS_DATA_NUM �Ĵ����ṹ���塣��ַƫ����:0xA1����ֵ:0x04�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_spi_trans_data_num_reg;
    struct
    {
        unsigned char  gtc_spi_trans_data_num : 5;  /* bit[0-4]: bit4~bit0��������Ҫ���͵�SPI����������
                                                                 00001 ��ʾ1������
                                                                 10000 ��ʾ16������ */
        unsigned char  reserved               : 3;  /* bit[5-7]:  */
    } reg;
} GBBP_GTC_SPI_TRANS_DATA_NUM_UNION;
#define GBBP_GTC_SPI_TRANS_DATA_NUM_gtc_spi_trans_data_num_START  (0)
#define GBBP_GTC_SPI_TRANS_DATA_NUM_gtc_spi_trans_data_num_END    (4)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_SPI_RD_EN_UNION
 �ṹ˵��  : GTC_SPI_RD_EN �Ĵ����ṹ���塣��ַƫ����:0xA2����ֵ:0x00�����:8
 �Ĵ���˵��:
*****************************************************************************/
typedef union
{
    unsigned char      gtc_spi_rd_en_reg;
    struct
    {
        unsigned char  gtc_spi_rd_en : 1;  /* bit[0]  : GTC��������SPI�������� */
        unsigned char  reserved      : 7;  /* bit[1-7]:  */
    } reg;
} GBBP_GTC_SPI_RD_EN_UNION;
#define GBBP_GTC_SPI_RD_EN_gtc_spi_rd_en_START  (0)
#define GBBP_GTC_SPI_RD_EN_gtc_spi_rd_en_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_W2G_CTRL_UNION
 �ṹ˵��  : GTC_W2G_CTRL �Ĵ����ṹ���塣��ַƫ����:0xB8����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_w2g_ctrl_reg;
    struct
    {
        unsigned char  gtc_w2g_ctrl : 1;  /* bit[0]  : �л���G���ߣ��л���GTC�ڲ��Ĵ���27�µ�ѡ��5��2M�����ź� */
        unsigned char  reserved     : 7;  /* bit[1-7]:  */
    } reg;
} GBBP_GTC_W2G_CTRL_UNION;
#define GBBP_GTC_W2G_CTRL_gtc_w2g_ctrl_START  (0)
#define GBBP_GTC_W2G_CTRL_gtc_w2g_ctrl_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_MIPI_START_INI_UNION
 �ṹ˵��  : GTC_MIPI_START_INI �Ĵ����ṹ���塣��ַƫ����:0xF0����ֵ:0x00�����:8
 �Ĵ���˵��:
*****************************************************************************/
typedef union
{
    unsigned char      gtc_mipi_start_ini_reg;
    struct
    {
        unsigned char  gtc_mipi_start_ind : 1;  /* bit[0]  : GSM����MIPI����д���������źţ������źţ�GTC�߼������� */
        unsigned char  gtc_mipi_ini_addr  : 7;  /* bit[1-7]: GSM����MIPI����д����ʱ����Ӧ�����üĴ�������ʼ��ַ����ע�����źŰ���mipi-asm,mipi-pa���ܡ���Gģ�����߿��ء���GBBP����W�����ص�G�����߿���ʱ��Ҫ���ô�ֵ�� */
    } reg;
} GBBP_GTC_MIPI_START_INI_UNION;
#define GBBP_GTC_MIPI_START_INI_gtc_mipi_start_ind_START  (0)
#define GBBP_GTC_MIPI_START_INI_gtc_mipi_start_ind_END    (0)
#define GBBP_GTC_MIPI_START_INI_gtc_mipi_ini_addr_START   (1)
#define GBBP_GTC_MIPI_START_INI_gtc_mipi_ini_addr_END     (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_MIPI_NUM_UNION
 �ṹ˵��  : GTC_MIPI_NUM �Ĵ����ṹ���塣��ַƫ����:0xF1����ֵ:0x00�����:8
 �Ĵ���˵��:
*****************************************************************************/
typedef union
{
    unsigned char      gtc_mipi_num_reg;
    struct
    {
        unsigned char  gtc_mipi_ini_num : 6;  /* bit[0-5]: GSM����MIPI����д����ʱ�����β�����Ӧ�����ø��� */
        unsigned char  reserved         : 2;  /* bit[6-7]:  */
    } reg;
} GBBP_GTC_MIPI_NUM_UNION;
#define GBBP_GTC_MIPI_NUM_gtc_mipi_ini_num_START  (0)
#define GBBP_GTC_MIPI_NUM_gtc_mipi_ini_num_END    (5)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_UNION
 �ṹ˵��  : GTC_EXT_LINE_CTRL_BITWISE_CLR �Ĵ����ṹ���塣��ַƫ����:0xF6����ֵ:0x00�����:8
 �Ĵ���˵��:
*****************************************************************************/
typedef union
{
    unsigned char      gtc_ext_line_ctrl_bitwise_clr_reg;
    struct
    {
        unsigned char  gtc_rf_trcv_on_clr : 1;  /* bit[0]: �����߿�gtc_rf_trcv_on���������ź� */
        unsigned char  gtc_gps_ctrl_clr   : 1;  /* bit[1]: �����߿�gtc_gps_ctrl���������ź� */
        unsigned char  gtc_flash_ctrl_clr : 1;  /* bit[2]: �����߿�gtc_flash_ctrl���������ź� */
        unsigned char  gtc_abb_rxa_en_clr : 1;  /* bit[3]: �����߿�gtc_abb_rxa_en���������ź� */
        unsigned char  gtc_abb_rxb_en_clr : 1;  /* bit[4]: �����߿�gtc_abb_rxb_en���������ź� */
        unsigned char  gtc_abb_tx_en_clr  : 1;  /* bit[5]: �����߿�gtc_abb_tx_en���������ź� */
        unsigned char  gtc_auxdac_en_clr  : 1;  /* bit[6]: �����߿�gtc_auxdac_en���������ź� */
        unsigned char  reserved           : 1;  /* bit[7]:  */
    } reg;
} GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_UNION;
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_rf_trcv_on_clr_START  (0)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_rf_trcv_on_clr_END    (0)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_gps_ctrl_clr_START    (1)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_gps_ctrl_clr_END      (1)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_flash_ctrl_clr_START  (2)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_flash_ctrl_clr_END    (2)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_abb_rxa_en_clr_START  (3)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_abb_rxa_en_clr_END    (3)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_abb_rxb_en_clr_START  (4)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_abb_rxb_en_clr_END    (4)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_abb_tx_en_clr_START   (5)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_abb_tx_en_clr_END     (5)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_auxdac_en_clr_START   (6)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_CLR_gtc_auxdac_en_clr_END     (6)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_UNION
 �ṹ˵��  : GTC_EXT_LINE_CTRL_BITWISE_SET �Ĵ����ṹ���塣��ַƫ����:0xF7����ֵ:0x00�����:8
 �Ĵ���˵��:
*****************************************************************************/
typedef union
{
    unsigned char      gtc_ext_line_ctrl_bitwise_set_reg;
    struct
    {
        unsigned char  gtc_rf_trcv_on_set : 1;  /* bit[0]: �����߿�gtc_rf_trcv_on����ʹ���ź� */
        unsigned char  gtc_gps_ctrl_set   : 1;  /* bit[1]: �����߿�gtc_gps_ctrl����ʹ���ź� */
        unsigned char  gtc_flash_ctrl_set : 1;  /* bit[2]: �����߿�gtc_flash_ctrl����ʹ���ź� */
        unsigned char  gtc_abb_rxa_en_set : 1;  /* bit[3]: �����߿�gtc_abb_rxa_en����ʹ���ź� */
        unsigned char  gtc_abb_rxb_en_set : 1;  /* bit[4]: �����߿�gtc_abb_rxb_en����ʹ���ź� */
        unsigned char  gtc_abb_tx_en_set  : 1;  /* bit[5]: �����߿�gtc_abb_tx_en����ʹ���ź� */
        unsigned char  gtc_auxdac_en_set  : 1;  /* bit[6]: �����߿�gtc_auxdac_en���� */
        unsigned char  reserved           : 1;  /* bit[7]:  */
    } reg;
} GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_UNION;
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_rf_trcv_on_set_START  (0)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_rf_trcv_on_set_END    (0)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_gps_ctrl_set_START    (1)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_gps_ctrl_set_END      (1)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_flash_ctrl_set_START  (2)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_flash_ctrl_set_END    (2)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_abb_rxa_en_set_START  (3)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_abb_rxa_en_set_END    (3)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_abb_rxb_en_set_START  (4)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_abb_rxb_en_set_END    (4)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_abb_tx_en_set_START   (5)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_abb_tx_en_set_END     (5)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_auxdac_en_set_START   (6)
#define GBBP_GTC_EXT_LINE_CTRL_BITWISE_SET_gtc_auxdac_en_set_END     (6)


/***======================================================================***
                     (2/9) register_define_gtc_dlfe
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : GBBP_GTC_DAGC_CTRL_UNION
 �ṹ˵��  : GTC_DAGC_CTRL �Ĵ����ṹ���塣��ַƫ����:0xA3����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_dagc_ctrl_reg;
    struct
    {
        unsigned char  reserved_0           : 1;  /* bit[0]  :  */
        unsigned char  gtc_dagc_process_sel : 1;  /* bit[1]  : DAGC����ģʽѡ��1Ϊ����ģʽ��0ΪNB���ģʽ����ģʽ�źŵ��л�ʱ��Ҫ����ÿ������������������֮ǰ������ϡ� */
        unsigned char  reserved_1           : 6;  /* bit[2-7]:  */
    } reg;
} GBBP_GTC_DAGC_CTRL_UNION;
#define GBBP_GTC_DAGC_CTRL_gtc_dagc_process_sel_START  (1)
#define GBBP_GTC_DAGC_CTRL_gtc_dagc_process_sel_END    (1)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_AGC_CTRL1_UNION
 �ṹ˵��  : GTC_AGC_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0xB4����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_agc_ctrl1_reg;
    struct
    {
        unsigned char  gtc_agc_en           : 1;  /* bit[0]  : AGCģ�鹤��ʹ���źš�
                                                               1��DCR&AGC����������
                                                               0��DCR&AGCֹͣ������
                                                               ��ע����ź�ͨ�����һֱ����Ϊ�ߣ�������Ҫ�쳣��ֹAGC������ */
        unsigned char  gtc_frq_sel          : 3;  /* bit[1-3]: ֱ��ƫ�ú�ǰ��ͨ���������RAM��ַ����ѡ���źš�
                                                               ���ڿ�����ʵ���д���һ��TDMA֡�л����Ƶ��Ŀ��ܣ�������Ƶ���ֱ��ƫ��ֵ��ǰ��ͨ��������������ͬ���������ͨ��3bit��ѡ��ѡ��8��ֱ��ƫ�ôֵ�ֵ��8��ǰ��ͨ������ֵ��
                                                               AGC��λ���÷�ʽѡ��0����agc_init_gain���ã�1����agc_next_gain���á� */
        unsigned char  reserved             : 1;  /* bit[4]  :  */
        unsigned char  gtc_agc_measure_mode : 1;  /* bit[5]  : ����AGC��������ģʽѡ���źš�
                                                               0������AGC�������޲��ò�������A��
                                                               1������AGC�������޲��ò�������B��
                                                               ���ź���Ч���μ�CPU�����ź�cpu_fast_threshold_sel����cpu_fast_threshold_sel=1ʱ��gsp_agc_measure_mode��Ч�� */
        unsigned char  gtc_fast_agc_mode    : 1;  /* bit[6]  : ����AGC����ʱ��ģʽѡ���źš�
                                                               0������AGC��������3��ģʽ��
                                                               1������AGC��������2��ģʽ�����൱��3��ģʽ�ĵ�1�����3�֡�������gsp_agc_average_time[5:0]ʱ����Ҫ�������е�[1:0]��[5:4]�����������2��ģʽ32��64������Ҫ����gsp_agc_average_time[5:0]Ϊ6��b10xx01������xx��ʾ�����������á� */
        unsigned char  gtc_gain_sel         : 1;  /* bit[7]  : AGC��λ���÷�ʽѡ��0����agc_init_gain���ã�1����agc_next_gain���á� */
    } reg;
} GBBP_GTC_AGC_CTRL1_UNION;
#define GBBP_GTC_AGC_CTRL1_gtc_agc_en_START            (0)
#define GBBP_GTC_AGC_CTRL1_gtc_agc_en_END              (0)
#define GBBP_GTC_AGC_CTRL1_gtc_frq_sel_START           (1)
#define GBBP_GTC_AGC_CTRL1_gtc_frq_sel_END             (3)
#define GBBP_GTC_AGC_CTRL1_gtc_agc_measure_mode_START  (5)
#define GBBP_GTC_AGC_CTRL1_gtc_agc_measure_mode_END    (5)
#define GBBP_GTC_AGC_CTRL1_gtc_fast_agc_mode_START     (6)
#define GBBP_GTC_AGC_CTRL1_gtc_fast_agc_mode_END       (6)
#define GBBP_GTC_AGC_CTRL1_gtc_gain_sel_START          (7)
#define GBBP_GTC_AGC_CTRL1_gtc_gain_sel_END            (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_AGC_CTRL2_UNION
 �ṹ˵��  : GTC_AGC_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0xB5����ֵ:0x03�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_agc_ctrl2_reg;
    struct
    {
        unsigned char  gtc_agc_average_time_round1 : 2;  /* bit[0-1]: AGC���������ۼӴ��������á�
                                                                      [1:0] ��ʾ�����ۼӼ���ʱ��һ�ִ����ȣ�0��16symbol��1��32symbol��2��64symbol��3��128symbol�� */
        unsigned char  gtc_agc_average_time_round2 : 2;  /* bit[2-3]: AGC���������ۼӴ��������á�
                                                                      [3:2] ��ʾ�����ۼӼ���ʱ�ڶ��ִ����ȣ�0��16symbol��1��32symbol��2��64symbol��3��128symbol�� */
        unsigned char  gtc_agc_average_time_round3 : 2;  /* bit[4-5]: AGC���������ۼӴ��������á�
                                                                      [5:4] ��ʾ�����ۼӼ���ʱ�����ִ����ȣ�0��16symbol��1��32symbol��2��64symbol��3��128symbol�� */
        unsigned char  gtc_dcr_nv_sel              : 1;  /* bit[6]  : �ֵ�ֱ��ѡ��
                                                                      1��ѡ��ʱ϶ǰ����ֱ��������Ҫ�Ƚ���ʱ϶ǰֱ�����㣬����ʹ�øù��ܣ�
                                                                      0��ѡ��NV������ֱ���� */
        unsigned char  gtc_slot_dcr_mode           : 1;  /* bit[7]  : ʱ϶ǰ����ֱ��ģʽ������
                                                                      1������ʱ϶ǰֱ������ģʽ�����źű�����������������ʱ�Ĳ����ж�֮ǰ���ͣ�
                                                                      0����ʹ��ʱ϶ǰֱ������ģʽ�� */
    } reg;
} GBBP_GTC_AGC_CTRL2_UNION;
#define GBBP_GTC_AGC_CTRL2_gtc_agc_average_time_round1_START  (0)
#define GBBP_GTC_AGC_CTRL2_gtc_agc_average_time_round1_END    (1)
#define GBBP_GTC_AGC_CTRL2_gtc_agc_average_time_round2_START  (2)
#define GBBP_GTC_AGC_CTRL2_gtc_agc_average_time_round2_END    (3)
#define GBBP_GTC_AGC_CTRL2_gtc_agc_average_time_round3_START  (4)
#define GBBP_GTC_AGC_CTRL2_gtc_agc_average_time_round3_END    (5)
#define GBBP_GTC_AGC_CTRL2_gtc_dcr_nv_sel_START               (6)
#define GBBP_GTC_AGC_CTRL2_gtc_dcr_nv_sel_END                 (6)
#define GBBP_GTC_AGC_CTRL2_gtc_slot_dcr_mode_START            (7)
#define GBBP_GTC_AGC_CTRL2_gtc_slot_dcr_mode_END              (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_AGC_START_UNION
 �ṹ˵��  : GTC_AGC_START �Ĵ����ṹ���塣��ַƫ����:0xB6����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_agc_start_reg;
    struct
    {
        unsigned char  gtc_register_clr       : 1;  /* bit[0]  : ��·����ϸ����ƫ�üĴ������㣬1��ϵͳ���ڵ������źš��Ĵ����ڵ�ֵ��Ҫ���ڱ��棬��UE�ػ�ʱ��Ҫ����ϵ�ɴ洢�Ĵ洢���ʵ��б��棬�ȵ�UE�ٹ���ʱ�ָ�ԭ���������ṩ��һ����λ��ѡ�����ȷʵ��Ҫ��λ�����ø��źż��ɣ�Ĭ����������踴λ�� */
        unsigned char  gtc_init_gain_en       : 1;  /* bit[1]  : AGC����ʱ϶��ʼ��λ������Чָʾ��1��ϵͳ���ڵ������źš�����ǰ���ݽ���ʱ��100us�������źţ�����gsp_init_gain��gsp_gain_sel�ź����ʹ�á������ź���Чʱ���ⲿagc_init_gain���ڲ�agc_next_gain�ĵ�λֵ�Ż����뵽��ǰ������λ */
        unsigned char  gtc_burst_register_clr : 1;  /* bit[2]  : ʱ϶ǰֱ���ۼ�ϸ���������ź� */
        unsigned char  gtc_dc_cal_start       : 1;  /* bit[3]  : ʱ϶ǰֱ�����������źš� */
        unsigned char  gtc_dcr_recv_active    : 1;  /* bit[4]  : ���������ͨ��ֱ��ƫ������ϸ��������ߵ�ƽ��Ч�����ź���Чʱ���൱������ϸ���������ʱ�޷�������·���ܡ� */
        unsigned char  gtc_rf_ssi_ch_sel      : 2;  /* bit[5-6]: AGCģ��SSI����ͨ��ָʾ�źţ������ź�ƴ�ӵ�gagc_ssi_data�źŵĸ�2bitʹ�á� */
        unsigned char  gtc_agc_fast_start     : 1;  /* bit[7]  : AGCģ����ٲ�����ʼָʾ�źţ�1��ϵͳ���ڵ������źš��ڹ�����ʼָʾ�źŷ���֮ǰ��Ҫ���ú�AGC�ı�ʱ϶�ĳ�ʼ��λ�����ٲ��������н���������� */
    } reg;
} GBBP_GTC_AGC_START_UNION;
#define GBBP_GTC_AGC_START_gtc_register_clr_START        (0)
#define GBBP_GTC_AGC_START_gtc_register_clr_END          (0)
#define GBBP_GTC_AGC_START_gtc_init_gain_en_START        (1)
#define GBBP_GTC_AGC_START_gtc_init_gain_en_END          (1)
#define GBBP_GTC_AGC_START_gtc_burst_register_clr_START  (2)
#define GBBP_GTC_AGC_START_gtc_burst_register_clr_END    (2)
#define GBBP_GTC_AGC_START_gtc_dc_cal_start_START        (3)
#define GBBP_GTC_AGC_START_gtc_dc_cal_start_END          (3)
#define GBBP_GTC_AGC_START_gtc_dcr_recv_active_START     (4)
#define GBBP_GTC_AGC_START_gtc_dcr_recv_active_END       (4)
#define GBBP_GTC_AGC_START_gtc_rf_ssi_ch_sel_START       (5)
#define GBBP_GTC_AGC_START_gtc_rf_ssi_ch_sel_END         (6)
#define GBBP_GTC_AGC_START_gtc_agc_fast_start_START      (7)
#define GBBP_GTC_AGC_START_gtc_agc_fast_start_END        (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_RSSI_FRQ_HIGH_UNION
 �ṹ˵��  : GTC_RSSI_FRQ_HIGH �Ĵ����ṹ���塣��ַƫ����:0xE4����ֵ:0x40�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_rssi_frq_high_reg;
    struct
    {
        unsigned char  gtc_rssi_frq_high       : 4;  /* bit[0-3]: ��ǰ������RSSI��Ӧ��Ƶ��Ÿ�4bit��GSP_RSSI_FRQ_LOW��GSP_RSSI_FRQ_HIGH���gsp_rssi_frq[11:0] */
        unsigned char  gtc_rrc_filter_para_sel : 3;  /* bit[4-6]: �˲���ϵ��ѡ���źš�
                                                                  000��32��90K������̶��˲�ϵ����
                                                                  100��32�׿������˲�ϵ����
                                                                  010��64�׿������˲�ϵ����
                                                                  011��64��135K�̶��˲���ϵ����
                                                                  101��64��BPF�̶��˲�ϵ������ͨ��Χ46.4K~89.7K��
                                                                  110��64��80K�̶��˲�ϵ���� */
        unsigned char  reserved                : 1;  /* bit[7]  :  */
    } reg;
} GBBP_GTC_RSSI_FRQ_HIGH_UNION;
#define GBBP_GTC_RSSI_FRQ_HIGH_gtc_rssi_frq_high_START        (0)
#define GBBP_GTC_RSSI_FRQ_HIGH_gtc_rssi_frq_high_END          (3)
#define GBBP_GTC_RSSI_FRQ_HIGH_gtc_rrc_filter_para_sel_START  (4)
#define GBBP_GTC_RSSI_FRQ_HIGH_gtc_rrc_filter_para_sel_END    (6)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_INIT_GAIN_RFIC_UNION
 �ṹ˵��  : GTC_INIT_GAIN_RFIC �Ĵ����ṹ���塣��ַƫ����:0xE7����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_init_gain_rfic_reg;
    struct
    {
        unsigned char  gtc_init_gain        : 3;  /* bit[0-2]: bit2~0: RFÿʱ϶����ĳ�ʼ��λ�� */
        unsigned char  reserved             : 3;  /* bit[3-5]:  */
        unsigned char  gtc_dcr_burst_mode   : 1;  /* bit[6]  : ʱ϶ȥֱ���򿪿��أ��ߵ�ƽ��Ч,���ź���Чʱ����ʾʱ϶ȥֱ�����ܿ���������ͬʱʱ϶ȥֱ���Ƿ�����������Ҫ�ο�cpu����ȥֱ������cpu_slot_dcr_rssi_threshold */
        unsigned char  gtc_rf_gain_word_sel : 1;  /* bit[7]  : 8����Ƶ������ѡ���źţ���BBP�ڲ�ʵ��������Ƶ�����ֱ��֣�����ʵ����Ƶ�Եȹ��ܡ�
                                                               1:ѡ��Ĵ���0x5068~5084
                                                               0:ѡ��Ĵ���0x513c,0x5088~0x50a0 */
    } reg;
} GBBP_GTC_INIT_GAIN_RFIC_UNION;
#define GBBP_GTC_INIT_GAIN_RFIC_gtc_init_gain_START         (0)
#define GBBP_GTC_INIT_GAIN_RFIC_gtc_init_gain_END           (2)
#define GBBP_GTC_INIT_GAIN_RFIC_gtc_dcr_burst_mode_START    (6)
#define GBBP_GTC_INIT_GAIN_RFIC_gtc_dcr_burst_mode_END      (6)
#define GBBP_GTC_INIT_GAIN_RFIC_gtc_rf_gain_word_sel_START  (7)
#define GBBP_GTC_INIT_GAIN_RFIC_gtc_rf_gain_word_sel_END    (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_AGC_TRUNC_WIDTH_UNION
 �ṹ˵��  : GTC_AGC_TRUNC_WIDTH �Ĵ����ṹ���塣��ַƫ����:0xED����ֵ:0x1B�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_agc_trunc_width_reg;
    struct
    {
        unsigned char  gtc_agc_trunc_width  : 3;  /* bit[0-2]: AGC��������ϸ������λλ��Ĭ��ֵ3��d3��                                        
                                                               3��d0��8��                                  
                                                               3��d1��10��                                 
                                                               3��d2��12��                                 
                                                               3��d3��14��                                  
                                                               3��d4��4��                                  
                                                               3��d5��6
                                                               3��d6: 9 */
        unsigned char  gtc_dagc_trunc_width : 3;  /* bit[3-5]: DAGC��������ϸ������λλ��Ĭ��ֵ3��d3��                                        
                                                               3��d0��8��                                  
                                                               3��d1��10��                                  
                                                               3��d2��12��                                  3'd3��14��                                  
                                                               3��d4��4��                                  
                                                               3��d5��6��
                                                               3'd6: 9 */
        unsigned char  reserved             : 2;  /* bit[6-7]:  */
    } reg;
} GBBP_GTC_AGC_TRUNC_WIDTH_UNION;
#define GBBP_GTC_AGC_TRUNC_WIDTH_gtc_agc_trunc_width_START   (0)
#define GBBP_GTC_AGC_TRUNC_WIDTH_gtc_agc_trunc_width_END     (2)
#define GBBP_GTC_AGC_TRUNC_WIDTH_gtc_dagc_trunc_width_START  (3)
#define GBBP_GTC_AGC_TRUNC_WIDTH_gtc_dagc_trunc_width_END    (5)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_RX_IQ_COMPL_UNION
 �ṹ˵��  : GTC_RX_IQ_COMPL �Ĵ����ṹ���塣��ַƫ����:0xF9����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_rx_iq_compl_reg;
    struct
    {
        unsigned char  gtc_iq_comp_en  : 1;  /* bit[0]  : RX IQMismatchУ׼���ò������ѡ���źš�����ָʾ��ǰʱ϶ʹ����һ����λУ׼�������ֵ��A��Pֵ�����ο�iq_comp_amp0~ iq_comp_amp4�� */
        unsigned char  gtc_iq_comp_sel : 3;  /* bit[1-3]: IQMismatchģ�鲹��ʹ���źţ��ߵ�ƽ��Ч����AGCģ������ǰ���á� */
        unsigned char  reserved        : 4;  /* bit[4-7]:  */
    } reg;
} GBBP_GTC_RX_IQ_COMPL_UNION;
#define GBBP_GTC_RX_IQ_COMPL_gtc_iq_comp_en_START   (0)
#define GBBP_GTC_RX_IQ_COMPL_gtc_iq_comp_en_END     (0)
#define GBBP_GTC_RX_IQ_COMPL_gtc_iq_comp_sel_START  (1)
#define GBBP_GTC_RX_IQ_COMPL_gtc_iq_comp_sel_END    (3)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_FAST_MEAS_SEL_CFG_UNION
 �ṹ˵��  : GTC_FAST_MEAS_SEL_CFG �Ĵ����ṹ���塣��ַƫ����:0xFD����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_fast_meas_sel_cfg_reg;
    struct
    {
        unsigned char  gtc_rx_fast_gain_sel    : 1;  /* bit[0]  : AGC���ٲ������һ�֣�2�ֲ�����Ӧ�ڶ��֣�3�ֲ�����Ӧ�����֣���λ����ģʽѡ���źţ�1����ʾ���һ�ֲ������ò������޲��ò�������A���е�λ�о���0��ʾ���һ�ֲ�������ԭ���ٲ����������ޡ� */
        unsigned char  gtc_agc_r23_gain_no_upd : 1;  /* bit[1]  : ��AGCʹ��3�ֿ��ٲ���ģʽʱ�����ٲ����ĵڶ��ֺ͵�����֮�䲻���е�λ���£����ڶ��ֺ͵����ֵĵ�λ����һ�£��ߵ�ƽ��Ч�� */
        unsigned char  reserved                : 6;  /* bit[2-7]:  */
    } reg;
} GBBP_GTC_FAST_MEAS_SEL_CFG_UNION;
#define GBBP_GTC_FAST_MEAS_SEL_CFG_gtc_rx_fast_gain_sel_START     (0)
#define GBBP_GTC_FAST_MEAS_SEL_CFG_gtc_rx_fast_gain_sel_END       (0)
#define GBBP_GTC_FAST_MEAS_SEL_CFG_gtc_agc_r23_gain_no_upd_START  (1)
#define GBBP_GTC_FAST_MEAS_SEL_CFG_gtc_agc_r23_gain_no_upd_END    (1)


/***======================================================================***
                     (3/9) register_define_gtc_gsrch
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : GBBP_GTC_SRCH_CFG_UNION
 �ṹ˵��  : GTC_SRCH_CFG �Ĵ����ṹ���塣��ַƫ����:0xC3����ֵ:0x00�����:8
 �Ĵ���˵��:
*****************************************************************************/
typedef union
{
    unsigned char      gtc_srch_cfg_reg;
    struct
    {
        unsigned char  gtc_srch_en                : 1;  /* bit[0]  : ����ʹ���źţ������������ڼ䶼����Ϊ�ߵ�ƽ��
                                                                     CPU�ӿ��������üĴ�������
                                                                     ��λĬ��ֵΪ0
                                                                     �����������У����Խ����ź����ͣ�������������
                                                                     ����������ж����͸��ź� */
        unsigned char  gtc_srch_mod               : 3;  /* bit[1-3]: ����ģʽ���ã�
                                                                     111(FB+AFC+SB)����BBP�����FB�������Զ�����AFC��SBͬ����Ӧ�ó���Ϊ��ʼС��ͬ����
			                                                         100��FB����������FB��������cpu_fb_peak_window��ֻ����FB������Ӧ�ó���Ϊר��̬�½���BSIC����
                                                                     110(FB+AFC)�����г�ʼС��ͬ�������FB������AFC�����о���
			                                                         101(FB+SB)������FB������SB������������AFC��Ӧ�ó���Ϊ��С��������ע����������Ҳ������"100+001"ģʽ�������ģʽ����
                                                                     001��SB������ֻ����SBͬ����������FB������AFC����ʱgsp_srch_starat��λ������ǰ������ʷ��Ϣ����100ģʽ����ó���FBλ�ã����������SB��λ��34�����ţ�������FB����λ����34�����ŵ���������Ӱ�졣Ӧ�ó���ΪBSIC��֤��
                                                                     010����ʾֻ����AFC����ʱgsp_srch_start��λ�ü�ΪFB��λ�ã�Ӧ�ó���ΪIDLE̬�µ�������AFC��
                                                                     011�����ʾֻ����AFC��SB����ʱgsp_srch_start��λ�ü�ΪFB��λ�ã�Ӧ�ó���ΪNB���ǰ��AFC��SBͬ��
                                                                     ��λĬ��ֵΪ3��b000 */
		unsigned char  gtc_fb_pos_adj             : 3;  /* bit[4-6]: CPU��FB������λ�õĵ�������ҪΪ�����Ʒ��ն���Ƶġ�
                                                                     000:��������001������1(symbol)��
                                                                     010������2��011������3
                                                                     111����ǰ��1��110����ǰ��2��
                                                                     101����ǰ��3��100����ǰ��4
                                                                     ��λĬ��ֵΪ3��b000
                                                                     ������������ģʽ����Ϊ111��101ʱ��Ч���������õ���FBλ�ø���gtc_fb_pos_adjֵ����������һ֡����sb������*/
		unsigned char  gtc_soft_agc_drssi_25db_en : 1;  /* bit[7]   : ���ǿ������DRSSI��ʹ�ܿ��أ���ʹ����Чʱ���������DRSSIֵ��Ч */
    } reg;
} GBBP_GTC_SRCH_CFG_UNION;
#define GBBP_GTC_SRCH_CFG_gtc_srch_en_START                 (0)
#define GBBP_GTC_SRCH_CFG_gtc_srch_en_END                   (0)
#define GBBP_GTC_SRCH_CFG_gtc_srch_mod_START                (1)
#define GBBP_GTC_SRCH_CFG_gtc_srch_mod_END                  (3)
#define GBBP_GTC_SRCH_CFG_gtc_fb_pos_adj_START              (4)
#define GBBP_GTC_SRCH_CFG_gtc_fb_pos_adj_END                (6)
#define GBBP_GTC_SRCH_CFG_gtc_soft_agc_drssi_25db_en_START  (7)
#define GBBP_GTC_SRCH_CFG_gtc_soft_agc_drssi_25db_en_END    (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_SRCH_START_UNION
 �ṹ˵��  : GTC_SRCH_START �Ĵ����ṹ���塣��ַƫ����:0xC4����ֵ:0x00�����:8
 �Ĵ���˵��:
*****************************************************************************/
typedef union
{
    unsigned char      gtc_srch_start_reg;
    struct
    {
        unsigned char  gtc_srch_start      : 1;  /* bit[0]  : �����������źţ������źš�ÿ����������ʱ��Ҫ��һ�Σ�1��Ч����ͬ��,GTCģ���ڲ���������ʹ������Ҫ��qb�ڵĵ�һ��clk_sys����Ч,GTC�߼������㡣��gsp_srch_mod=001ʱ��gsp_srch_start������ǰ��ǰĬ�ϵ�SBλ��34�����Ų�����
                                                              ע����������ʱ�������� */
        unsigned char  reserved            : 5;  /* bit[1-5]:  */
		unsigned char  gtc_nco_en          : 1;  /* bit[6]  : ������ƫʹ�ܣ�0��ʾ�رվ�ƫ��1��ʾ�򿪡�Ҳ�������ڶ�����NB��ƫ�����Ƿ���������ʱ������ʹ�þ�ƫ�����������������Ƶ��һ����Ҳ���ܴ򿪾�ƫ�������Ӱ��VCTXO�� */
		unsigned char  gtc_ncell_srch_flag : 1;  /* bit[7]  : 1��ʶ��ǰ������������0��ʶ��ǰ�Ƿ�����������������������ʱ���������ø��źš� */
    } reg;
} GBBP_GTC_SRCH_START_UNION;
#define GBBP_GTC_SRCH_START_gtc_srch_start_START       (0)
#define GBBP_GTC_SRCH_START_gtc_srch_start_END         (0)
#define GBBP_GTC_SRCH_START_gtc_nco_en_START           (6)
#define GBBP_GTC_SRCH_START_gtc_nco_en_END             (6)
#define GBBP_GTC_SRCH_START_gtc_ncell_srch_flag_START  (7)
#define GBBP_GTC_SRCH_START_gtc_ncell_srch_flag_END    (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_SB_SAVE_START_UNION
 �ṹ˵��  : GTC_SB_SAVE_START �Ĵ����ṹ���塣��ַƫ����:0xD0����ֵ:0x00�����:8
 �Ĵ���˵��:
*****************************************************************************/
typedef union
{
    unsigned char      gtc_sb_save_start_reg;
    struct
    {
        unsigned char  gtc_sb_save_start     : 1;  /* bit[0]  : �����������SB���ݴ洢��ʱ�̣�GTCָ�����á���DAGC���ݱȿտ������ӳ�1slot�����ģ���ڲ�ʵ�ʿ�ʼ�洢��ʱ��Ӧ�ӳ�1slot��
                                                                ע����������ʱ��������gsp_nb_afc_en=0�� */
        unsigned char  gtc_sb_start_from_ram : 1;  /* bit[1]  : �����źţ�����RAM�е����ݣ�����SB���������ź�û�пտ���ʱ����Ч����������001�����Ĳ��� */
        unsigned char  gtc_fast_101_en       : 1;  /* bit[2]  : ����FB��SBģʽʹ���źţ��������������Զ����� */
        unsigned char  reserved              : 5;  /* bit[3-7]:  */
    } reg;
} GBBP_GTC_SB_SAVE_START_UNION;
#define GBBP_GTC_SB_SAVE_START_gtc_sb_save_start_START      (0)
#define GBBP_GTC_SB_SAVE_START_gtc_sb_save_start_END        (0)
#define GBBP_GTC_SB_SAVE_START_gtc_sb_start_from_ram_START  (1)
#define GBBP_GTC_SB_SAVE_START_gtc_sb_start_from_ram_END    (1)
#define GBBP_GTC_SB_SAVE_START_gtc_fast_101_en_START        (2)
#define GBBP_GTC_SB_SAVE_START_gtc_fast_101_en_END          (2)


/***======================================================================***
                     (4/9) register_define_gtc_dem
 ***======================================================================***/
 /*****************************************************************************
 �ṹ��    : GBBP_GTC_DEMOD_PARA1_UNION
 �ṹ˵��  : GTC_DEMOD_PARA1 �Ĵ����ṹ���塣��ַƫ����:0xB0����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_demod_para1_reg;
    struct
    {
        unsigned char  gtc_nb_demod_en           : 1;  /* bit[0]  : NB���ʹ���źţ��ߵ�ƽ��Ч����NB���������һֱΪ�ߣ�����������ǰҲ��Ҫ�����ź���1
                                                                    CPU�ӿ��������òμ���ַ0x01124�Ĵ�������
                                                                    ע�⣺����ҪNB�����ʱ����ر�gsp_srch_en(����μ�0x01124�Ĵ���)��������̬ʱ����������FB/SB����ʱ������ά��gsp_nb_demod_enΪ�ߣ������������ȼ����ڽ����
                                                                    ��λĬ��ֵΪ0 */
        unsigned char  gtc_dl_tsc_group_num_3pre : 3;  /* bit[1-3]: ѵ���������
                                                                    000��0�飻001��1�飻
                                                                    010��2�飻011��3�飻
                                                                    100��4�飻101��5�飻
                                                                    110��6�飻111��7��
                                                                    ��λĬ��ֵΪ0 */
        unsigned char  gtc_demod_slot_3pre       : 3;  /* bit[4-6]: �������ʱ��ʱ϶�ţ�����TOAֵ��·�ϱ� */
        unsigned char  gtc_nserv_cell_ind_3pre   : 1;  /* bit[7]  : 1��ʾ�Ƿ���С��
                                                                    0��ʾ����С��
                                                                    ����TOAֵ��·�ϱ� */
    } reg;
} GBBP_GTC_DEMOD_PARA1_UNION;
#define GBBP_GTC_DEMOD_PARA1_gtc_nb_demod_en_START            (0)
#define GBBP_GTC_DEMOD_PARA1_gtc_nb_demod_en_END              (0)
#define GBBP_GTC_DEMOD_PARA1_gtc_dl_tsc_group_num_3pre_START  (1)
#define GBBP_GTC_DEMOD_PARA1_gtc_dl_tsc_group_num_3pre_END    (3)
#define GBBP_GTC_DEMOD_PARA1_gtc_demod_slot_3pre_START        (4)
#define GBBP_GTC_DEMOD_PARA1_gtc_demod_slot_3pre_END          (6)
#define GBBP_GTC_DEMOD_PARA1_gtc_nserv_cell_ind_3pre_START    (7)
#define GBBP_GTC_DEMOD_PARA1_gtc_nserv_cell_ind_3pre_END      (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_DEMOD_PARA2_UNION
 �ṹ˵��  : GTC_DEMOD_PARA2 �Ĵ����ṹ���塣��ַƫ����:0xB1����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_demod_para2_reg;
    struct
    {
        unsigned char  gtc_demod_type_3pre         : 2;  /* bit[0-1]: ���е��Ʒ�ʽָʾ 00 GMSK���� 01 8PSK����,10��ʾ���е��Ʒ�ʽδ֪��11 �����壻
                                                                      ������ͬһ������������burstͬʱ���д�ĸ��ʷǳ�С��������ͬһ����ǰ����ʱ϶����Ϊͬһ�ֵ���ģʽ�����ڽ�������͵��ĸ�burstʱֱ������ǰ����burst�о��ĵ��Ʒ�ʽ���н�������ǰ����ʱ϶�����ĵ��Ʒ�ʽ��ͬ������Ҫ�о�������burst��������Ҫ�о����ĸ�burst��ǰ����burst�п϶�������burst��ͬһ�ֵ���ģʽ�����ڽ�����ĸ�burstʱֱ������ǰ����burst�о����ռ�����ĵ��Ʒ�ʽ���н��.
                                                                      ��λĬ��ֵΪ2��b00 */
        unsigned char  gtc_ls_dcr_en_3pre          : 1;  /* bit[2]  : LSȥֱ��ʹ���źţ�0��ʾ�رգ�1��ʾ�򿪡�Ϊ��֤���ܣ�����26M��Ƶ��򿪣�����Ƶ����رա��Ҵ򿪸ù���ʱ����Ҫͬʱ��AGCģ���ʱ϶ƽ��ȥֱ��������8PSK���Ʒ�ʽ��Ч�� */
        unsigned char  gtc_demod_flag_sav_pos_3pre : 5;  /* bit[3-7]: PS��DATAҵ����
                                                                      ����ä����־�洢λ�ö�ʱ϶�ĵ�һ,�ڶ���������
                                                                      ���ģ����壬������ʱ϶������BURST����ä����־����
                                                                      �洢��3��0��7��4��11��8��15��12��23��20��27��24λ�ã���ÿ�����ĵ�һ��BURSTä����־�ֱ�����0��4��8��12��20��24λ��,ÿ�����ĵڶ���BURSTä����־�ֱ�����1��5��9��13��21��25λ��,������������
                                                                      ��λĬ��ֵΪ0
                                                                      �����CS�����PS�̶�λ�õĿ����ŵ������������Ϊ16��19 */
    } reg;
} GBBP_GTC_DEMOD_PARA2_UNION;
#define GBBP_GTC_DEMOD_PARA2_gtc_demod_type_3pre_START          (0)
#define GBBP_GTC_DEMOD_PARA2_gtc_demod_type_3pre_END            (1)
#define GBBP_GTC_DEMOD_PARA2_gtc_ls_dcr_en_3pre_START           (2)
#define GBBP_GTC_DEMOD_PARA2_gtc_ls_dcr_en_3pre_END             (2)
#define GBBP_GTC_DEMOD_PARA2_gtc_demod_flag_sav_pos_3pre_START  (3)
#define GBBP_GTC_DEMOD_PARA2_gtc_demod_flag_sav_pos_3pre_END    (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_DEM_PARA3_UNION
 �ṹ˵��  : GTC_DEM_PARA3 �Ĵ����ṹ���塣��ַƫ����:0xB2����ֵ:0x50�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_dem_para3_reg;
    struct
    {
        unsigned char  gtc_dem_burst_pos_3pre : 7;  /* bit[0-6]: ���BURST���ݴ洢��ʼλ��ָʾ�������CS��ҵ����ʼλ�ö�ӦΪ26��֡��ӳ��λ�ã�ӳ�䵽36��36��gsp_dl_burst_sav_cycle-1�ڵı�ţ������EGPRS/GPRSҵ�񣬲����ǵ�ʱ϶���Ƕ�ʱ϶��ʱ϶�����еĵ�һ��ʱ϶��������ݹ̶������0��3��6��9��ʱ϶�����еĵڶ���ʱ϶��������ݹ̶������12��15��18��21��ʱ϶�����еĵ�����ʱ϶��������ݹ̶������24��27��30��33��ʱ϶�����еĵ��ĸ�ʱ϶��������ݹ̶������36��39��42��45��λ�ã�ʱ϶�����еĵ����ʱ϶��������ݹ̶������81��84��87��90��ʱ϶�����еĵ�����ʱ϶��������ݹ̶������93��96��99��102���������PCCCH��PBCCH����BCCH��CCCH��SDCCH�ȣ����Դ����68��71��SACCH�����72��75λ�ã�PTCCH�����76��79λ�ã����������ŵ������������������ҵ���BURST���ѭ�����ڣ��μ������GTC���ã�gsp_dl_burst_sav_cycle���������ƣ������SCH�������ݴ����80λ�á���λĬ��ֵΪ80�� */
        unsigned char  reserved               : 1;  /* bit[7]  :  */
    } reg;
} GBBP_GTC_DEM_PARA3_UNION;
#define GBBP_GTC_DEM_PARA3_gtc_dem_burst_pos_3pre_START  (0)
#define GBBP_GTC_DEM_PARA3_gtc_dem_burst_pos_3pre_END    (6)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_DEMOD_START_UNION
 �ṹ˵��  : GTC_DEMOD_START �Ĵ����ṹ���塣��ַƫ����:0xB3����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_demod_start_reg;
    struct
    {
        unsigned char  gtc_demod_start     : 1;  /* bit[0]  : ����NB��������źţ������źţ�
                                                              GTCģ���ڲ���������ʹ������Ҫ��qb�ڵĵ�һ��clk_sys����Ч,GTC�߼������� */
        unsigned char  gtc_gaci_en_2pre    : 1;  /* bit[1]  : ��Ƶ���ģ��ʹ���źš���Ƶ���ƹ��ܽ������NB�����ʹ�ã�����ģʽ�£�FB��SB����������Ƶ��⡣ */
        unsigned char  gtc_gaci_index_2pre : 2;  /* bit[2-3]: �˲���ϵ��ѡ��λ
                                                              2��b00���˲���0���޸���
                                                              2��b01���˲���1��+200Khz����
                                                              2��b10���˲���2��-200Khz����
                                                              2��b11���˲���3��
                                                              200Khz���� */
        unsigned char  reserved            : 4;  /* bit[4-7]:  */
    } reg;
} GBBP_GTC_DEMOD_START_UNION;
#define GBBP_GTC_DEMOD_START_gtc_demod_start_START      (0)
#define GBBP_GTC_DEMOD_START_gtc_demod_start_END        (0)
#define GBBP_GTC_DEMOD_START_gtc_gaci_en_2pre_START     (1)
#define GBBP_GTC_DEMOD_START_gtc_gaci_en_2pre_END       (1)
#define GBBP_GTC_DEMOD_START_gtc_gaci_index_2pre_START  (2)
#define GBBP_GTC_DEMOD_START_gtc_gaci_index_2pre_END    (3)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_TOA_PARA_UNION
 �ṹ˵��  : GTC_TOA_PARA �Ĵ����ṹ���塣��ַƫ����:0xBD����ֵ:0x10�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_toa_para_reg;
    struct
    {
        unsigned char  gtc_nb_pos_3pre           : 4;  /* bit[0-3]: ������ģʽ�����������ĵ�ǰNBλ�õĵ���ֵ������ģʽ�¸��źſ�������Ϊ0
                                                                    �����ȡֵ��Χ��-1~7����λΪ���š������ʾ���磺
                                                                    4��b1111����ʾ��ǰ��NBλ�ýϵ�ǰ��ʱ϶ͷҪ��ǰ1�����ţ�
                                                                    4��b0000����ʾ��ǰ��NBλ�����õ��ڵ�ǰ��ʱ϶ͷ��
                                                                    4��b0001����ʾ��ǰ��NBλ�ýϵ�ǰ��ʱ϶ͷҪ�ӳ�1�����ţ�
                                                                    4��b0010����ʾ��ǰ��NBλ�ýϵ�ǰ��ʱ϶ͷҪ�ӳ�2�����ţ�
                                                                    ������������
                                                                    4��b0111����ʾ��ǰ��NBλ�ýϵ�ǰ��ʱ϶ͷҪ�ӳ�7�����š� */
        unsigned char  gtc_nb_toa_alpha_sel_3pre : 1;  /* bit[4]  : ѡ���Ƿ��ڱ�ʱ϶��������Alpha�˲�����ƽ�źš�
                                                                    1����������Alpha�˲���ϵ��Ϊcpu_alpha_parameter;
                                                                    0������������Alpha�˲���
                                                                    Ĭ��ֵΪ1 */
        unsigned char  gtc_nb_pos_sel_3pre       : 1;  /* bit[5]  : ������㵱ǰNBλ�õ�ѡ���źš�
                                                                    1��d1����ʾѡ���������ĵ�ǰNBλ�õ���ֵ��
                                                                    1��d0����ʾѡ��GBBP����ĵ�ǰNBλ�õ���ֵ������ģʽ������ؽ����ź�����Ϊ0,������ģʽ����Ҫͬʱ����gsp_nb_pos����
                                                                    Ĭ��ֵΪ0 */
        unsigned char  gtc_nb_nco_en_2pre        : 1;  /* bit[6]  : ������NBʱ����ƫʹ���źš�
                                                                    1��ʾ���о�ƫ��
                                                                    0��ʾ����ƫ
                                                                    ���ø��ź�ʹ��ʱ����ͬʱ����gsp_nco_ini_value */
        unsigned char  gtc_nb_afc_en_3pre        : 1;  /* bit[7]  : NB-AFCʹ���źţ�1��Ч��
                                                                    Ĭ��ֵΪ0��
                                                                    ע������������ʱ�����źű�������Ϊ�㣬CPU�ӿ��������òμ���ַ0x01124�Ĵ������á� */
    } reg;
} GBBP_GTC_TOA_PARA_UNION;
#define GBBP_GTC_TOA_PARA_gtc_nb_pos_3pre_START            (0)
#define GBBP_GTC_TOA_PARA_gtc_nb_pos_3pre_END              (3)
#define GBBP_GTC_TOA_PARA_gtc_nb_toa_alpha_sel_3pre_START  (4)
#define GBBP_GTC_TOA_PARA_gtc_nb_toa_alpha_sel_3pre_END    (4)
#define GBBP_GTC_TOA_PARA_gtc_nb_pos_sel_3pre_START        (5)
#define GBBP_GTC_TOA_PARA_gtc_nb_pos_sel_3pre_END          (5)
#define GBBP_GTC_TOA_PARA_gtc_nb_nco_en_2pre_START         (6)
#define GBBP_GTC_TOA_PARA_gtc_nb_nco_en_2pre_END           (6)
#define GBBP_GTC_TOA_PARA_gtc_nb_afc_en_3pre_START         (7)
#define GBBP_GTC_TOA_PARA_gtc_nb_afc_en_3pre_END           (7)


/***======================================================================***
                     (5/9) register_define_gtc_gcipher
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : GBBP_GTC_A5_CIPH_CFG_UNION
 �ṹ˵��  : GTC_A5_CIPH_CFG �Ĵ����ṹ���塣��ַƫ����:0xC6����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_a5_ciph_cfg_reg;
    struct
    {
        unsigned char  gtc_ul_ciph_en       : 1;  /* bit[0]  : ���н���ģ�鹤��ģʽѡ��,
                                                               1��ʾ���з�����Ҫ����
                                                               0��ʾ���з��䲻��Ҫ
                                                               Ĭ��ֵΪ0 */
        unsigned char  gtc_ul_gsm_alg_sel   : 3;  /* bit[1-3]: ������A51����A52,A53�㷨ѡ��
                                                               gtc_ul_gsm_alg_sel[2:0] =1��ʾѡ��A51�㷨 
                                                               gtc_ul_gsm_alg_sel[2:0] =7��ʾѡ��A53�㷨 */
        unsigned char  gtc_ul_fn_adj_flag   : 2;  /* bit[4-5]: ����֡�ŵ�����־
                                                               11��ʾ���뵽����ģ���FN��Ҫ����1������01��ʾ���뵽����ģ���FN��Ҫ����1����;
                                                               10��00��ʾ�޼ӣ���1����;
                                                               ��λĬ��ֵΪ00������ʹ����Ӧ������Ϊ00��01��11�ǳ���ʱ�Ĺ��ģʽ. */
        unsigned char  reserved             : 1;  /* bit[6]  :  */
        unsigned char  gtc_ul_a5_ciph_start : 1;  /* bit[7]  : 1��ʾ��������A5���ܡ�ÿ���м��ܲ������źű������á� */
    } reg;
} GBBP_GTC_A5_CIPH_CFG_UNION;
#define GBBP_GTC_A5_CIPH_CFG_gtc_ul_ciph_en_START        (0)
#define GBBP_GTC_A5_CIPH_CFG_gtc_ul_ciph_en_END          (0)
#define GBBP_GTC_A5_CIPH_CFG_gtc_ul_gsm_alg_sel_START    (1)
#define GBBP_GTC_A5_CIPH_CFG_gtc_ul_gsm_alg_sel_END      (3)
#define GBBP_GTC_A5_CIPH_CFG_gtc_ul_fn_adj_flag_START    (4)
#define GBBP_GTC_A5_CIPH_CFG_gtc_ul_fn_adj_flag_END      (5)
#define GBBP_GTC_A5_CIPH_CFG_gtc_ul_a5_ciph_start_START  (7)
#define GBBP_GTC_A5_CIPH_CFG_gtc_ul_a5_ciph_start_END    (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_A5_DECIPH_CFG_UNION
 �ṹ˵��  : GTC_A5_DECIPH_CFG �Ĵ����ṹ���塣��ַƫ����:0xC5����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_a5_deciph_cfg_reg;
    struct
    {
        unsigned char  gtc_dl_deciph_en_3pre   : 1;  /* bit[0]  : ���н���ģ�鹤��ģʽѡ��
                                                                  1��ʾ������Ҫ���ܣ�
                                                                  0��ʾ���в����ܣ�
                                                                  Ĭ��ֵΪ0
                                                                  ���PS��ҵ���SCH��BURSTʱ������Ϊ0  */
        unsigned char  gtc_dl_gsm_alg_sel_3pre : 3;  /* bit[1-3]: ����A51����A52,A53�㷨ѡ��
                                                                  gtc_dl_gsm_alg_sel[2:0] =1��ʾѡ��A51�㷨��
                                                                  gtc_dl_gsm_alg_sel[2:0] =7��ʾѡ��A53�㷨 */
        unsigned char  gtc_dl_fn_adj_flag_3pre : 2;  /* bit[4-5]: ����֡�ŵ�����־��
                                                                  11��ʾ���뵽����ģ���FN��Ҫ����1������01��ʾ���뵽����ģ���FN��Ҫ����1������
                                                                  10��00��ʾ�޼ӣ���1������
                                                                  ��λĬ��ֵΪ00������ʹ����Ӧ������Ϊ00��01��11�ǳ���ʱ�Ĺ��ģʽ */
        unsigned char  reserved                : 2;  /* bit[6-7]:  */
    } reg;
} GBBP_GTC_A5_DECIPH_CFG_UNION;
#define GBBP_GTC_A5_DECIPH_CFG_gtc_dl_deciph_en_3pre_START    (0)
#define GBBP_GTC_A5_DECIPH_CFG_gtc_dl_deciph_en_3pre_END      (0)
#define GBBP_GTC_A5_DECIPH_CFG_gtc_dl_gsm_alg_sel_3pre_START  (1)
#define GBBP_GTC_A5_DECIPH_CFG_gtc_dl_gsm_alg_sel_3pre_END    (3)
#define GBBP_GTC_A5_DECIPH_CFG_gtc_dl_fn_adj_flag_3pre_START  (4)
#define GBBP_GTC_A5_DECIPH_CFG_gtc_dl_fn_adj_flag_3pre_END    (5)


/***======================================================================***
                     (6/9) register_define_gtc_gdec
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : GBBP_GTC_DL_CB_INDEX_UNION
 �ṹ˵��  : GTC_DL_CB_INDEX �Ĵ����ṹ���塣��ַƫ����:0xC7����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_dl_cb_index_reg;
    struct
    {
        unsigned char  gtc_dl_cb_index  : 7;  /* bit[0-6]: һ������±�ʾ����ҵ�����.������Ϊ120��123��ʾ����ҵ����� 
                                                           120 ��ʾCS���AFSҵ��
                                                           121 ��ʾCS���AHSҵ��
                                                           122 ��ʾPS��ҵ��HARQ���������ش���
                                                           123 ��ʾHARQ�ϲ�����
                                                           ��λĬ��ֵΪ7��d0 */
        unsigned char  gtc_cycle_rpt_en : 1;  /* bit[7]  : 1��ʾѭ���ϱ�ģʽʹ�ܣ���ʱ��������������ϱ��жϣ�
                                                           0��ʾ�����ϱ�ģʽʹ�ܣ�����������󻺴��ϱ��жϡ� */
    } reg;
} GBBP_GTC_DL_CB_INDEX_UNION;
#define GBBP_GTC_DL_CB_INDEX_gtc_dl_cb_index_START   (0)
#define GBBP_GTC_DL_CB_INDEX_gtc_dl_cb_index_END     (6)
#define GBBP_GTC_DL_CB_INDEX_gtc_cycle_rpt_en_START  (7)
#define GBBP_GTC_DL_CB_INDEX_gtc_cycle_rpt_en_END    (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_DEC_BURST_POS_UNION
 �ṹ˵��  : GTC_DEC_BURST_POS �Ĵ����ṹ���塣��ַƫ����:0xC8����ֵ:0xD0�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_dec_burst_pos_reg;
    struct
    {
        unsigned char  gtc_dec_burst_pos  : 7;  /* bit[0-6]: ��ʾ���������ĵ�һ��BURST��VALPP��ֵ�洢RAM�е�λ�ñ�š������CS��ҵ����ʼλ����36��36��gsp_dl_burst_sav_cycle-1���������������ڸ�֡��ӳ����ʼλ�����ã��������EGPRS/GPRSҵ�񣬲����ǵ�ʱ϶���Ƕ�ʱ϶������Ե�һ��ʱ϶���õ�������룬������Ϊ0������Եڶ���ʱ϶���õ�������룬������Ϊ12������Ե�����ʱ϶���õ�������룬������Ϊ24������Ե��ĸ�ʱ϶���õ�������룬������Ϊ36������Ե���ʱ϶���õ�������룬������Ϊ81������Ե�����ʱ϶���õ�������룬������Ϊ93����SDCCH��PBCCH��BCCH��CCCH����Ϊ68������SACCH����Ϊ72��PTCCH������Ϊ76���ر�ע�⣺����ǰ�����ҵ�񣬼��赱ǰ��������ʱ����λ��Ϊa���ҵ���ǰ�����ϱ�����ʧ��ԭ��ΪFACCH_Hǰ�ĸ�BURSTʱ�����´���������Ӧ�ý���������Ȼ����Ϊa�����´�������ɺ��������´�����ʱӦ������Ϊa��4��gsp_dl_burst_sav_cycle��ȡģ��Ȼ�����36��ֵ������δ����λ�ã����������ҵ����Ҫ������á���λĬ��ֵδ80 */
        unsigned char  gtc_amr_state_flag : 1;  /* bit[7]  : 1��ʾ����AMR ��SPEECH̬
                                                             0��ʾ����AMR ��DTX̬
                                                             Ĭ��ֵΪ1 */
    } reg;
} GBBP_GTC_DEC_BURST_POS_UNION;
#define GBBP_GTC_DEC_BURST_POS_gtc_dec_burst_pos_START   (0)
#define GBBP_GTC_DEC_BURST_POS_gtc_dec_burst_pos_END     (6)
#define GBBP_GTC_DEC_BURST_POS_gtc_amr_state_flag_START  (7)
#define GBBP_GTC_DEC_BURST_POS_gtc_amr_state_flag_END    (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_DEC_TYPE1_UNION
 �ṹ˵��  : GTC_DEC_TYPE1 �Ĵ����ṹ���塣��ַƫ����:0xC9����ֵ:0x82�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_dec_type1_reg;
    struct
    {
        unsigned char  gtc_enhanced_dec_mode : 2;  /* bit[0-1]: gtc_enhanced_dec_mode[1]��1��ʾ��ǿ������ģʽʹ�ܣ�0��ʾ���ô�ͳVTB����ģʽ
                                                                gtc_enhanced_dec_mode[0]��1��ʾ����ǿ������ģʽ��MCS5-69ҵ����ô�ͳVTB����ģʽ��0��ʾMCS5-69ҵ�������ǿ������ģʽ��
                                                                MCS7~9������֧����ǿ�����롣
                                                                ʵ��ʹ���У�
                                                                1������MCS5~9������Ϊ��ǿ�����룬���о���ҵ��ΪMCS7~9ʱ����ʱBBP���ô�ͳVTB����ģʽ��ͬʱcb1_crc_result[7:0]��cb2_crc_result[7:0]��cb3_crc_result[7:0]�ϱ��������Ч��
                                                                
                                                                2���ش�MCS7~9����Ϊ��ǿ�����룬��ʱMCS7~9������ǿ�����룬ͬʱcb1_crc_result[7:0]��cb2_crc_result[7:0]��cb3_crc_result[7:0]�ϱ��������Ч��
                                                                Ĭ��Ϊ2��b10 */
        unsigned char  reserved              : 2;  /* bit[2-3]:  */
        unsigned char  gtc_dl_amr_cmc_frame  : 1;  /* bit[4]  : ��ʾ��ǰ֡�ŵ�CMI��CMCָʾ��0��ʾ��CMI֡��1��ʾ��CMC֡����λĬ��ֵΪ0 */
        unsigned char  gtc_dl_amr_cmi_value  : 2;  /* bit[5-6]: ������õ���ʷCMIֵ
                                                                Ĭ��ֵΪ0x0 */
        unsigned char  gtc_facch_dec_mode    : 1;  /* bit[7]  : FACCH����ģʽѡ��AFS��FS��EFS��1 ��ʾ����������ж��Ƿ�ΪFACCH͵֡�������,���߼�����FACCH����,�������,���߼���������������룻0 ��ʾֱ������FACCH������������CRCУ�����ж��Ƿ�ΪFACCH͵֡��
                                                                AHS��HS��1 ��ʾ����������ж��Ƿ�ΪFACCH͵֡�������,���߼�����FACCH����,�������,���߼���������������룻0��ʶֱ����ΪFACCH���롣
                                                                Ĭ��ֵΪ1 */
    } reg;
} GBBP_GTC_DEC_TYPE1_UNION;
#define GBBP_GTC_DEC_TYPE1_gtc_enhanced_dec_mode_START  (0)
#define GBBP_GTC_DEC_TYPE1_gtc_enhanced_dec_mode_END    (1)
#define GBBP_GTC_DEC_TYPE1_gtc_dl_amr_cmc_frame_START   (4)
#define GBBP_GTC_DEC_TYPE1_gtc_dl_amr_cmc_frame_END     (4)
#define GBBP_GTC_DEC_TYPE1_gtc_dl_amr_cmi_value_START   (5)
#define GBBP_GTC_DEC_TYPE1_gtc_dl_amr_cmi_value_END     (6)
#define GBBP_GTC_DEC_TYPE1_gtc_facch_dec_mode_START     (7)
#define GBBP_GTC_DEC_TYPE1_gtc_facch_dec_mode_END       (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_DEC_TYPE2_UNION
 �ṹ˵��  : GTC_DEC_TYPE2 �Ĵ����ṹ���塣��ַƫ����:0xCA����ֵ:0x02�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_dec_type2_reg;
    struct
    {
        unsigned char  gtc_cs4_judge_mode     : 2;  /* bit[0-1]: 00 ��ʾ��GPRS���磬�������������Ϣ����CS4��MCS1234����ΪCS4
                                                                 01 ��ʾ��EGPRS���磬�����������Ϣ����CS4��MCS1234����ΪMCS1234���ù��������ã�
                                                                 10 ��ʾ����MCS1234��HEADER�����룬�����������CRCУ����ȷ����ΪMCS1234��������ΪCS4
                                                                 Ĭ��ֵΪ0x2 */
        unsigned char  reserved               : 2;  /* bit[2-3]:  */
        unsigned char  gtc_edge_usf_rxqual_en : 1;  /* bit[4]  : 1��ʾ EDGEҵ����USF����BER��BEPͳ�ƣ�Ĭ��ֵΪ0 */
        unsigned char  gtc_bep_en             : 1;  /* bit[5]  : 1��ʾ��bepͳ�ƹ��ܣ�0��ʾ�ر�bepͳ�ƹ��ܣ�Ĭ��ֵΪ0 */
        unsigned char  gtc_ib_im_rxqual_en    : 1;  /* bit[6]  : 1��ʾ����bit ib��ID_MARKER bit������������ͳ��
                                                                 0��ʾ����bit ib��ID_MARKER bit��������������ͳ��
                                                                 Ĭ��ֵΪ0 */
        unsigned char  gtc_harq_func_en       : 1;  /* bit[7]  : 1��ʾ�������HARQ����ʹ�ܣ�0��ʾ�ù�������
                                                                 Ĭ��ֵΪ0 */
    } reg;
} GBBP_GTC_DEC_TYPE2_UNION;
#define GBBP_GTC_DEC_TYPE2_gtc_cs4_judge_mode_START      (0)
#define GBBP_GTC_DEC_TYPE2_gtc_cs4_judge_mode_END        (1)
#define GBBP_GTC_DEC_TYPE2_gtc_edge_usf_rxqual_en_START  (4)
#define GBBP_GTC_DEC_TYPE2_gtc_edge_usf_rxqual_en_END    (4)
#define GBBP_GTC_DEC_TYPE2_gtc_bep_en_START              (5)
#define GBBP_GTC_DEC_TYPE2_gtc_bep_en_END                (5)
#define GBBP_GTC_DEC_TYPE2_gtc_ib_im_rxqual_en_START     (6)
#define GBBP_GTC_DEC_TYPE2_gtc_ib_im_rxqual_en_END       (6)
#define GBBP_GTC_DEC_TYPE2_gtc_harq_func_en_START        (7)
#define GBBP_GTC_DEC_TYPE2_gtc_harq_func_en_END          (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_HARQ_POS1_UNION
 �ṹ˵��  : GTC_HARQ_POS1 �Ĵ����ṹ���塣��ַƫ����:0xCB����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_harq_pos1_reg;
    struct
    {
        unsigned char  gtc_harq1_pos : 7;  /* bit[0-6]: ��HARQ��������б�ʾ��Ҫ��harq�ϲ��ĵ�һ�����Ķ���ʼλ�ã���HARQ��ֵ���������Ϊ��һ������д��ʼλ�á���Repeat FACCH/SACCHҵ��ȡֵֻ��Ϊ0~7������ҵ��ȡֵ��Χ��0~127����V3R3��V8R1��HARQ���ư汾�������÷�Χͳһ��Ϊ0~127����
                                                        Ĭ��ֵΪ0 */
        unsigned char  reserved      : 1;  /* bit[7]  :  */
    } reg;
} GBBP_GTC_HARQ_POS1_UNION;
#define GBBP_GTC_HARQ_POS1_gtc_harq1_pos_START  (0)
#define GBBP_GTC_HARQ_POS1_gtc_harq1_pos_END    (6)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_HARQ_POS2_UNION
 �ṹ˵��  : GTC_HARQ_POS2 �Ĵ����ṹ���塣��ַƫ����:0xCC����ֵ:0x01�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_harq_pos2_reg;
    struct
    {
        unsigned char  gtc_harq2_pos : 7;  /* bit[0-6]: ��HARQ��������б�ʾ��Ҫ��harq�ϲ��ĵڶ������Ķ���ʼλ�ã���HARQ��ֵ���������Ϊ�ڶ�������д��ʼλ�á�
                                                        Ĭ��ֵΪ1 */
        unsigned char  reserved      : 1;  /* bit[7]  :  */
    } reg;
} GBBP_GTC_HARQ_POS2_UNION;
#define GBBP_GTC_HARQ_POS2_gtc_harq2_pos_START  (0)
#define GBBP_GTC_HARQ_POS2_gtc_harq2_pos_END    (6)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_HARQ1_CB_INDEX_UNION
 �ṹ˵��  : GTC_HARQ1_CB_INDEX �Ĵ����ṹ���塣��ַƫ����:0xCF����ֵ:0x34�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_harq1_cb_index_reg;
    struct
    {
        unsigned char  gtc_harq1_cb_index : 7;  /* bit[0-6]: bit6��bit0������HARQ�ϲ����������һ����飨Ӧ��ΪDATA�飩��CB_INDEX����λĬ��ֵΪ7��d52�������MCS6��9��MCS5��7�ϲ�����ô����ѡ������һ����飨Ӧ��ΪDATA�飩��cb_index�������� */
        unsigned char  reserved           : 1;  /* bit[7]  :  */
    } reg;
} GBBP_GTC_HARQ1_CB_INDEX_UNION;
#define GBBP_GTC_HARQ1_CB_INDEX_gtc_harq1_cb_index_START  (0)
#define GBBP_GTC_HARQ1_CB_INDEX_gtc_harq1_cb_index_END    (6)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_DL_BURST_CYCLE_UNION
 �ṹ˵��  : GTC_DL_BURST_CYCLE �Ĵ����ṹ���塣��ַƫ����:0xD2����ֵ:0xD8�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_dl_burst_cycle_reg;
    struct
    {
        unsigned char  gtc_dl_burst_sav_cycle : 6;  /* bit[0-5]: ����������BURSTѭ�����ڣ��ò���ֻ��CS��ҵ����Ч������λĬ��ֵΪ24����ʾ����Ϊ24����22BURST��֯��ҵ������Ҫ��������������á�
                                                                 000000��ʾ����Ϊ0,
                                                                 ����
                                                                 100000��ʾ����Ϊ32
                                                                 ��������Ϊ44
                                                                 ��λĬ��ֵΪ6��d24 */
        unsigned char  gtc_bler_en            : 1;  /* bit[6]  : ��������BLERģ��ʹ���źţ��ߵ�ƽ��Ч������Ҫʱ�ضϣ��Խ�ʡ���ģ�
                                                                 ��λĬ��ֵΪ1 */
        unsigned char  gtc_ber_en             : 1;  /* bit[7]  : ��������BERģ��ʹ���źţ��ߵ�ƽ��Ч������Ҫʱ�ضϣ��Խ�ʡ���ģ�
                                                                 Ĭ��ֵΪ1 */
    } reg;
} GBBP_GTC_DL_BURST_CYCLE_UNION;
#define GBBP_GTC_DL_BURST_CYCLE_gtc_dl_burst_sav_cycle_START  (0)
#define GBBP_GTC_DL_BURST_CYCLE_gtc_dl_burst_sav_cycle_END    (5)
#define GBBP_GTC_DL_BURST_CYCLE_gtc_bler_en_START             (6)
#define GBBP_GTC_DL_BURST_CYCLE_gtc_bler_en_END               (6)
#define GBBP_GTC_DL_BURST_CYCLE_gtc_ber_en_START              (7)
#define GBBP_GTC_DL_BURST_CYCLE_gtc_ber_en_END                (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_DEC_START_UNION
 �ṹ˵��  : GTC_DEC_START �Ĵ����ṹ���塣��ַƫ����:0xD3����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_dec_start_reg;
    struct
    {
        unsigned char  gtc_dec_start     : 1;  /* bit[0]  : NB����ҵ������������ź�,GTC�߼������� */
        unsigned char  gtc_last_dec_flag : 1;  /* bit[1]  : 1��ʾ����������Ҫ�ϱ��жϣ��������ж�ģʽֻ��gtc_cycle_rpt_enΪ0����Ч */
        unsigned char  gtc_dec_slot      : 3;  /* bit[2-4]: ������������ʱ��Ӧ��ʱ϶�� */
        unsigned char  reserved          : 1;  /* bit[5]  :  */
        unsigned char  gtc_bler_clr      : 1;  /* bit[6]  : ���������ϱ�BLER�����źţ������ź�,GTC�߼������� */
        unsigned char  gtc_ber_clr       : 1;  /* bit[7]  : ���������ϱ�BER�����źţ������ź�,GTC�߼������� */
    } reg;
} GBBP_GTC_DEC_START_UNION;
#define GBBP_GTC_DEC_START_gtc_dec_start_START      (0)
#define GBBP_GTC_DEC_START_gtc_dec_start_END        (0)
#define GBBP_GTC_DEC_START_gtc_last_dec_flag_START  (1)
#define GBBP_GTC_DEC_START_gtc_last_dec_flag_END    (1)
#define GBBP_GTC_DEC_START_gtc_dec_slot_START       (2)
#define GBBP_GTC_DEC_START_gtc_dec_slot_END         (4)
#define GBBP_GTC_DEC_START_gtc_bler_clr_START       (6)
#define GBBP_GTC_DEC_START_gtc_bler_clr_END         (6)
#define GBBP_GTC_DEC_START_gtc_ber_clr_START        (7)
#define GBBP_GTC_DEC_START_gtc_ber_clr_END          (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_DEC_TEST_MODE_EN_UNION
 �ṹ˵��  : GTC_DEC_TEST_MODE_EN �Ĵ����ṹ���塣��ַƫ����:0xE0����ֵ:0xF0�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_dec_test_mode_en_reg;
    struct
    {
        unsigned char  gtc_dec_test_mode_en : 1;  /* bit[0]  : 1��ʾ����ģʽ�ǲ���ģʽ����ʱ����ģ�鲻��֡�����о� */
        unsigned char  gtc_enhanced_ut_en   : 1;  /* bit[1]  : 1��ʾ����ǿ�������UT��֤ģʽ�������ã�Ĭ��ֵΪ0 */
        unsigned char  reserved             : 2;  /* bit[2-3]:  */
        unsigned char  gtc_reduce_page_mode : 4;  /* bit[4-7]: bit3~bit0���ֱ��ʾ��ǰ����Ѱ������ʱ��Ч��BURST�Ƿ���ڣ���0011��ʶ��һ�����ڶ���BURST���ڣ����������ĸ�BURST�������ݲ��㡣
                                                               1100��ʶ�����������ĸ�BURST���ڣ���һ���ڶ���BURST�������ݲ��㡣
                                                               Ĭ��ֵΪ0xF */
    } reg;
} GBBP_GTC_DEC_TEST_MODE_EN_UNION;
#define GBBP_GTC_DEC_TEST_MODE_EN_gtc_dec_test_mode_en_START  (0)
#define GBBP_GTC_DEC_TEST_MODE_EN_gtc_dec_test_mode_en_END    (0)
#define GBBP_GTC_DEC_TEST_MODE_EN_gtc_enhanced_ut_en_START    (1)
#define GBBP_GTC_DEC_TEST_MODE_EN_gtc_enhanced_ut_en_END      (1)
#define GBBP_GTC_DEC_TEST_MODE_EN_gtc_reduce_page_mode_START  (4)
#define GBBP_GTC_DEC_TEST_MODE_EN_gtc_reduce_page_mode_END    (7)


/***======================================================================***
                     (7/9) register_define_gtc_gglb
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : GBBP_GTC_GRIF_CTRL_UNION
 �ṹ˵��  : GTC_GRIF_CTRL �Ĵ����ṹ���塣��ַƫ����:0xC2����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_grif_ctrl_reg;
    struct
    {
        unsigned char  reserved_0   : 1;  /* bit[0]  :  */
        unsigned char  gtc_rx_start : 1;  /* bit[1]  : GRIFģ����������źţ�һ��ϵͳʱ�����ڿ�� */
        unsigned char  gtc_rx_stop  : 1;  /* bit[2]  : GRIFģ�����ֹͣ�źţ�һ��ϵͳʱ�����ڿ��.��gsp_rx_low_len��gsp_rx_high_len������Ϊ0ʱ,��ʾ��������,��ʱ������gsp_rx_stop��ֹͣ����.����gsp_rx_stop�������򰴳��Ƚ��յ�ģʽ����1���ᵼ�½�����ֹ */
        unsigned char  reserved_1   : 5;  /* bit[3-7]:  */
    } reg;
} GBBP_GTC_GRIF_CTRL_UNION;
#define GBBP_GTC_GRIF_CTRL_gtc_rx_start_START  (1)
#define GBBP_GTC_GRIF_CTRL_gtc_rx_start_END    (1)
#define GBBP_GTC_GRIF_CTRL_gtc_rx_stop_START   (2)
#define GBBP_GTC_GRIF_CTRL_gtc_rx_stop_END     (2)


/***======================================================================***
                     (8/9) register_define_gtc_gul
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : GBBP_GTC_PA_CTRL_CFG_UNION
 �ṹ˵��  : GTC_PA_CTRL_CFG �Ĵ����ṹ���塣��ַƫ����:0xA4����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_pa_ctrl_cfg_reg;
    struct
    {
        unsigned char  gtc_pa_start        : 1;  /* bit[0]  : GSP����APC������1��104M�����壨������frac_cnt=94��������GTC�ڲ����������ø������ź�������APC���RAMP DAC����Ŀ����� */
        unsigned char  gtc_pa_stop         : 1;  /* bit[1]  : GSPֹͣAPC�����������źš�д1ֹͣAPC�����������ڲ�����һ��104M���塣���ø������ź�������APC���RAMP DAC����Ŀ����� */
        unsigned char  gtc_pa_single_start : 1;  /* bit[2]  : ����APC���������źš�д1����Ŀ�깦�ʵ�ѹֵΪgsp_pa_init�ĵ���APC�������ڲ�����һ��104M���塣���߼��ڲ�һ�δﵽ��Ŀ�깦�ʵ�ѹֵ�������ø������ź�������APC���TXAGC DAC����Ŀ����� */
        unsigned char  gtc_pa_change       : 1;  /* bit[3]  : target������APC�������������źš�д1����һ��target�����õ�APC����������Ӧ���ڶ�ʱ϶���ʱ仯�����ڲ�����һ��104M���壨������frac_cnt=46��������GTC�ڲ���������note������������16����������������źţ�����μ�����������ʱ��ͼ�� */
        unsigned char  gtc_pa_dac_sel_pre  : 1;  /* bit[4]  : ����ABB�ڲ�GAPC DAC����ѡ���źš�                1��TXAGC DAC��          0��RAMP DAC��             ע����ǰRF C02�汾�У�GMSKʱ����Ϊ0��ʾ���£�8pskʱ����Ϊ1��ʾ���£�0��ʾVBIAS�� */
        unsigned char  reserved            : 3;  /* bit[5-7]:  */
    } reg;
} GBBP_GTC_PA_CTRL_CFG_UNION;
#define GBBP_GTC_PA_CTRL_CFG_gtc_pa_start_START         (0)
#define GBBP_GTC_PA_CTRL_CFG_gtc_pa_start_END           (0)
#define GBBP_GTC_PA_CTRL_CFG_gtc_pa_stop_START          (1)
#define GBBP_GTC_PA_CTRL_CFG_gtc_pa_stop_END            (1)
#define GBBP_GTC_PA_CTRL_CFG_gtc_pa_single_start_START  (2)
#define GBBP_GTC_PA_CTRL_CFG_gtc_pa_single_start_END    (2)
#define GBBP_GTC_PA_CTRL_CFG_gtc_pa_change_START        (3)
#define GBBP_GTC_PA_CTRL_CFG_gtc_pa_change_END          (3)
#define GBBP_GTC_PA_CTRL_CFG_gtc_pa_dac_sel_pre_START   (4)
#define GBBP_GTC_PA_CTRL_CFG_gtc_pa_dac_sel_pre_END     (4)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_PA_LEN_HIGH_CFG_UNION
 �ṹ˵��  : GTC_PA_LEN_HIGH_CFG �Ĵ����ṹ���塣��ַƫ����:0xA6����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_pa_len_high_cfg_reg;
    struct
    {
        unsigned char  gtc_pa_len_high : 5;  /* bit[0-4]: APC������������ʱ�䳤�ȣ�����ָ�״������µ�Ŀ��ֵgsp_pa_targetʱ��ʼ������ʼ�����µ���ʼֵ��ʱ�����ʱ�䣨����μ�����ʱ��ͼ���źŵĺ��壩����λQb��Ĭ��ֵΪ4��burst���ȡ����ź����õ��Ǹ�5bit */
        unsigned char  reserved        : 3;  /* bit[5-7]:  */
    } reg;
} GBBP_GTC_PA_LEN_HIGH_CFG_UNION;
#define GBBP_GTC_PA_LEN_HIGH_CFG_gtc_pa_len_high_START  (0)
#define GBBP_GTC_PA_LEN_HIGH_CFG_gtc_pa_len_high_END    (4)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_PA_TARGET_HIGH_CFG_UNION
 �ṹ˵��  : GTC_PA_TARGET_HIGH_CFG �Ĵ����ṹ���塣��ַƫ����:0xA8����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_pa_target_high_cfg_reg;
    struct
    {
        unsigned char  gtc_pa_target_high : 2;  /* bit[0-1]: GSP����APCĿ���ѹֵ�����ź����õ��Ǹ�2bit */
        unsigned char  reserved_0         : 3;  /* bit[2-4]:  */
        unsigned char  gtc_pa_coeff_index : 2;  /* bit[5-6]: ָʾ�������µ�����ϵ�������ţ�ȷ����gsp_pa_start����gsp_pa_change��Чʱ,��ֵ�Ѿ����á���������ȡֵ��Χ��0��3��note������gsp_pa_changeʱ��ramp-down��ϵ��gsp_pa_coeff_index[1:0]��gsp_pa_change��Ӧ��ϵ�������ž�������������gsp_pa_start��Ӧ��ϵ��gsp_pa_coeff_index[1:0]������ */
        unsigned char  reserved_1         : 1;  /* bit[7]  :  */
    } reg;
} GBBP_GTC_PA_TARGET_HIGH_CFG_UNION;
#define GBBP_GTC_PA_TARGET_HIGH_CFG_gtc_pa_target_high_START  (0)
#define GBBP_GTC_PA_TARGET_HIGH_CFG_gtc_pa_target_high_END    (1)
#define GBBP_GTC_PA_TARGET_HIGH_CFG_gtc_pa_coeff_index_START  (5)
#define GBBP_GTC_PA_TARGET_HIGH_CFG_gtc_pa_coeff_index_END    (6)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_PA_INIT_HIGH_CFG_UNION
 �ṹ˵��  : GTC_PA_INIT_HIGH_CFG �Ĵ����ṹ���塣��ַƫ����:0xAA����ֵ:0x40�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_pa_init_high_cfg_reg;
    struct
    {
        unsigned char  gtc_pa_init_high : 2;  /* bit[0-1]: APC���³�ʼ���ʵ�ѹֵ��Ҳ����Ϊ����APC������Ŀ�깦�ʵ�ѹֵ�����ź����õ��Ǹ�2bit */
        unsigned char  gtc_ramp_point   : 5;  /* bit[2-6]: ָʾ��ǰ���µĵ��������º����µ�����ͬ�����䷶Χֵ��8��16��Ĭ��ֵΪ16�� */
        unsigned char  reserved         : 1;  /* bit[7]  :  */
    } reg;
} GBBP_GTC_PA_INIT_HIGH_CFG_UNION;
#define GBBP_GTC_PA_INIT_HIGH_CFG_gtc_pa_init_high_START  (0)
#define GBBP_GTC_PA_INIT_HIGH_CFG_gtc_pa_init_high_END    (1)
#define GBBP_GTC_PA_INIT_HIGH_CFG_gtc_ramp_point_START    (2)
#define GBBP_GTC_PA_INIT_HIGH_CFG_gtc_ramp_point_END      (6)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_MOD_START_POS_UNION
 �ṹ˵��  : GTC_MOD_START_POS �Ĵ����ṹ���塣��ַƫ����:0xAC����ֵ:0x4D�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_mod_start_pos_reg;
    struct
    {
        unsigned char  gtc_mod_start_pos          : 7;  /* bit[0-6]: bit6~0: ���źű�ʾgsp_mod_start��Ҫ��QB�ڲ���λ����Ϣ(������QB��96����һ�ĵ�λ�ò���)��λ����Ϣ����Ϊ0~95(ע���ֵӦ������Ϊλ�ü�1��ֵ,����47~0~46),����gsp_mod_start�������ø��ź�(���λ�ò���,���Բ�������).��λĬ��ֵΪ77; */
        unsigned char  gtc_mod_symbol_length_high : 1;  /* bit[7]  : ��gsp_mod_symbol_l_length[7:0]���9bit�ĵ��Ƴ��ȣ��ñ���Ϊ���λ��gsp_mod_symbol_l_length[7:0]Ϊ��8bit��ѭ������0��������Ҳ��źš�ֻ��ʹ��gsp_mod_stopֹͣ�� */
    } reg;
} GBBP_GTC_MOD_START_POS_UNION;
#define GBBP_GTC_MOD_START_POS_gtc_mod_start_pos_START           (0)
#define GBBP_GTC_MOD_START_POS_gtc_mod_start_pos_END             (6)
#define GBBP_GTC_MOD_START_POS_gtc_mod_symbol_length_high_START  (7)
#define GBBP_GTC_MOD_START_POS_gtc_mod_symbol_length_high_END    (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_MOD_TYPE_UNION
 �ṹ˵��  : GTC_MOD_TYPE �Ĵ����ṹ���塣��ַƫ����:0xAE����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_mod_type_reg;
    struct
    {
        unsigned char  gtc_mod_type : 1;  /* bit[0]  : �������ͣ�1��ʾ8PSK��0��ʾGMSK����λĬ��ֵΪ0�����ƹ����У��ò���Ӧ���֡�HUASHAN�汾���������0 */
        unsigned char  reserved     : 7;  /* bit[1-7]:  */
    } reg;
} GBBP_GTC_MOD_TYPE_UNION;
#define GBBP_GTC_MOD_TYPE_gtc_mod_type_START  (0)
#define GBBP_GTC_MOD_TYPE_gtc_mod_type_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_MOD_CTRL_UNION
 �ṹ˵��  : GTC_MOD_CTRL �Ĵ����ṹ���塣��ַƫ����:0xAF����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_mod_ctrl_reg;
    struct
    {
        unsigned char  gtc_mod_start : 1;  /* bit[0]  : bit0: CPU����GTC�������ƣ�һ�����壬������ʱ϶ʱ��CPU����Ҫÿ��ʱ϶������һ�Σ�����ʱ���߼��������Ƿ��Ƕ�ʱ϶.���������ø�ָ��֮ǰ������һ����ʱָ���֤�����һ��QB��ǰ���ʱ��Ϳ�ʼ����gsp_mod_startָ��Ӷ���֤������������һ��BURST��ͷλ�ö��룬GTC�߼������㡣��Ҫ����Ԥ���Ƴ����Լ�����ͨ������ʱ */
        unsigned char  gtc_mod_stop  : 1;  /* bit[1]  : bit1: CPU ����GTCֹͣ���ƣ�һ�����塣��gsp_mod_symbol_length=0ʱ��ѭ������ָ��λ�ã���ʱֻ����gsp_mod_stopֹͣ���ơ�,GTC�߼������� */
        unsigned char  reserved      : 6;  /* bit[2-7]:  */
    } reg;
} GBBP_GTC_MOD_CTRL_UNION;
#define GBBP_GTC_MOD_CTRL_gtc_mod_start_START  (0)
#define GBBP_GTC_MOD_CTRL_gtc_mod_start_END    (0)
#define GBBP_GTC_MOD_CTRL_gtc_mod_stop_START   (1)
#define GBBP_GTC_MOD_CTRL_gtc_mod_stop_END     (1)


/*****************************************************************************
 �ṹ��    : GBBP_UL_CB1_INDEX_UNION
 �ṹ˵��  : UL_CB1_INDEX �Ĵ����ṹ���塣��ַƫ����:0xD4����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      ul_cb1_index_reg;
    struct
    {
        unsigned char  gtc_ul_cb1_index : 7;  /* bit[0-6]: ����ҵ�������� */
        unsigned char  reserved         : 1;  /* bit[7]  :  */
    } reg;
} GBBP_UL_CB1_INDEX_UNION;
#define GBBP_UL_CB1_INDEX_gtc_ul_cb1_index_START  (0)
#define GBBP_UL_CB1_INDEX_gtc_ul_cb1_index_END    (6)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_UL_CB_NUM_UNION
 �ṹ˵��  : GTC_UL_CB_NUM �Ĵ����ṹ���塣��ַƫ����:0xD7����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_ul_cb_num_reg;
    struct
    {
        unsigned char  reserved              : 4;  /* bit[0-3]:  */
        unsigned char  gtc_ul_cb_start_pos   : 2;  /* bit[4-5]: ���д����������ʼλ��ָʾ��־��                   00: ��ʾ���0����ʼλ�ñ�־��                     01:��ʾ���1����ʼλ�ñ�־��                    10: ��ʾ���2����ʼλ�ñ�־��                    11: ��ʾ���3����ʼλ�ñ�־��                     ��λĬ��ֵΪ2��b00 */
        unsigned char  gtc_facch_stolen_flag : 2;  /* bit[6-7]: FACCH͵֡��־��           01: ��ʾ��ǰ����֮ǰ������һ��FACCH/H���룬��֯ʱ���ܸ���͵֡λ�á�         10: ��ʾ��ǰ����֮ǰ������һ��FACCH/F���룬��֯ʱ���ܸ���͵֡λ�á�      00/11����ʾ��ǰ����֮ǰû������FACCH�������FACCH͵֡�Ե�ǰ����û��Ӱ�죬����������֯��              ע���ñ�־�������22��BURST��֯��ȵ�����ҵ�񣨰���F9.6/F4.8/H4.8/H2.4/F14.4���£���Ҫ���ã�����ҵ�����������ã���FACCH������ҵ��֮�����SACCHҵ�񣨵����洢��ʱ����͵֡��־����������ҵ��֮ǰ������Ա��� */
    } reg;
} GBBP_GTC_UL_CB_NUM_UNION;
#define GBBP_GTC_UL_CB_NUM_gtc_ul_cb_start_pos_START    (4)
#define GBBP_GTC_UL_CB_NUM_gtc_ul_cb_start_pos_END      (5)
#define GBBP_GTC_UL_CB_NUM_gtc_facch_stolen_flag_START  (6)
#define GBBP_GTC_UL_CB_NUM_gtc_facch_stolen_flag_END    (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_UL_PARA21_UNION
 �ṹ˵��  : GTC_UL_PARA21 �Ĵ����ṹ���塣��ַƫ����:0xD8����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_ul_para21_reg;
    struct
    {
        unsigned char  gtc_ul_in_band_data_id0 : 2;  /* bit[0-1]: [1:0]����ʾ���ڱ���id0��Ϣ00:CODEC_MODE_1��01:CODEC_MODE_2��10:CODEC_MODE_3��11:CODEC_MODE_4��     */
        unsigned char  gtc_ul_in_band_data_id1 : 2;  /* bit[2-3]: [3:2]����ʾ���ڱ���id1��Ϣ��       00:CODEC_MODE_1��01:CODEC_MODE_2��10:CODEC_MODE_3��11:CODEC_MODE_4��        ��λĬ��ֵΪ4'b0000�����Э����û�б���id0,id1,���õ���id��ע����ô��idֵ������id0�ϣ�����ʱ�ǵ�2bit��Ч��������Ա�����id1,��ô��������id1����ʱ��2bit��Ч�� */
        unsigned char  gtc_punc_index1         : 2;  /* bit[4-5]: [5:4]��ʾDATA1��DATA���Ĵ�׷�ʽ��                00���ޣ�                   01��P1��                 10��P2��                11��P3��                 ��λĬ��ֵΪ4��b0000�� */
        unsigned char  gtc_punc_index2         : 2;  /* bit[6-7]: [7:6]��ʾDATA2�Ĵ�׷�
                                                                  00����
                                                                  01��P1
                                                                  10��P2
                                                                  11��P3
                                                                  ��λĬ��ֵΪ4��b0000 */
    } reg;
} GBBP_GTC_UL_PARA21_UNION;
#define GBBP_GTC_UL_PARA21_gtc_ul_in_band_data_id0_START  (0)
#define GBBP_GTC_UL_PARA21_gtc_ul_in_band_data_id0_END    (1)
#define GBBP_GTC_UL_PARA21_gtc_ul_in_band_data_id1_START  (2)
#define GBBP_GTC_UL_PARA21_gtc_ul_in_band_data_id1_END    (3)
#define GBBP_GTC_UL_PARA21_gtc_punc_index1_START          (4)
#define GBBP_GTC_UL_PARA21_gtc_punc_index1_END            (5)
#define GBBP_GTC_UL_PARA21_gtc_punc_index2_START          (6)
#define GBBP_GTC_UL_PARA21_gtc_punc_index2_END            (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_RACH_BSIC_UNION
 �ṹ˵��  : GTC_RACH_BSIC �Ĵ����ṹ���塣��ַƫ����:0xD9����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_rach_bsic_reg;
    struct
    {
        unsigned char  gtc_rach_bsic_data : 6;  /* bit[0-5]: RACHҵ����BS����վ����BSIC���أ���λĬ��ֵΪ6��b000000��ע��BSIC��MSB��bit0,LSB��bit5�� */
        unsigned char  reserved           : 2;  /* bit[6-7]:  */
    } reg;
} GBBP_GTC_RACH_BSIC_UNION;
#define GBBP_GTC_RACH_BSIC_gtc_rach_bsic_data_START  (0)
#define GBBP_GTC_RACH_BSIC_gtc_rach_bsic_data_END    (5)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_COD_BURST_POS_UNION
 �ṹ˵��  : GTC_COD_BURST_POS �Ĵ����ṹ���塣��ַƫ����:0xDA����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_cod_burst_pos_reg;
    struct
    {
        unsigned char  gtc_cod_burst_pos : 7;  /* bit[0-6]: ��ʾ��ǰ�������ݵ�һ��BURST�ڱ���洢RAM��ram611x16s���е�λ�ñ��:��λĬ��ֵΪ7��d0��   �ο��������£�0��12��24��36��                      PS��ҵ�񣺶�Ӧ�ڵ�һ����飬����Ϊ0����ʱmap���4��burst���δ�����׵�ַΪ0��3��6��9��ram�У�Ϊ������gsp_ map_burst_pos���ã���                   �ڶ����������Ϊ12��map���4��burst���δ����12��15��18��21��             �������������Ϊ24��map���4��burst���δ����24��27��30��33��             ���ĸ��������Ϊ36��map���4��burst���δ����36��39��42��45��36 �� 59�� CS��ҵ��64 �� 67�� SACCH��68 �� 71�� PTCCH��72 �� 75�����������ŵ���76      �� RACH��                �ر�ע�⣺����ǰ�����ҵ�񣬼��赱ǰ��������ʱ����λ��Ϊa������һ��FACCH/H���룬��Ҫ����2��SPEECH�ı��룬�����´�ֱ����a+4λ�á� */
        unsigned char  reserved          : 1;  /* bit[7]  :  */
    } reg;
} GBBP_GTC_COD_BURST_POS_UNION;
#define GBBP_GTC_COD_BURST_POS_gtc_cod_burst_pos_START  (0)
#define GBBP_GTC_COD_BURST_POS_gtc_cod_burst_pos_END    (6)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_UL_BURST_CYCLE_UNION
 �ṹ˵��  : GTC_UL_BURST_CYCLE �Ĵ����ṹ���塣��ַƫ����:0xDB����ֵ:0x18�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_ul_burst_cycle_reg;
    struct
    {
        unsigned char  gtc_ul_burst_sav_cycle : 6;  /* bit[0-5]: ���б�����BURSTѭ�����ڣ��ò���ֻ��CS��ҵ����Ч������CS��ҵ��ӳ��ĸ�֡���ڣ�.��λĬ��ֵΪ24�� */
        unsigned char  reserved               : 1;  /* bit[6]  :  */
        unsigned char  gtc_ul_cod_en          : 1;  /* bit[7]  : ���б�����̵�ʹ���źš� ��λĬ��ֵΪ0 */
    } reg;
} GBBP_GTC_UL_BURST_CYCLE_UNION;
#define GBBP_GTC_UL_BURST_CYCLE_gtc_ul_burst_sav_cycle_START  (0)
#define GBBP_GTC_UL_BURST_CYCLE_gtc_ul_burst_sav_cycle_END    (5)
#define GBBP_GTC_UL_BURST_CYCLE_gtc_ul_cod_en_START           (7)
#define GBBP_GTC_UL_BURST_CYCLE_gtc_ul_cod_en_END             (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_UL_COD_START_UNION
 �ṹ˵��  : GTC_UL_COD_START �Ĵ����ṹ���塣��ַƫ����:0xDC����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_ul_cod_start_reg;
    struct
    {
        unsigned char  gtc_ul_cod_start : 1;  /* bit[0]  : ���б��������źţ������ź�,GTC�߼������� */
        unsigned char  reserved         : 7;  /* bit[1-7]:  */
    } reg;
} GBBP_GTC_UL_COD_START_UNION;
#define GBBP_GTC_UL_COD_START_gtc_ul_cod_start_START  (0)
#define GBBP_GTC_UL_COD_START_gtc_ul_cod_start_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_UL_MAP_PARA_UNION
 �ṹ˵��  : GTC_UL_MAP_PARA �Ĵ����ṹ���塣��ַƫ����:0xDD����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_ul_map_para_reg;
    struct
    {
        unsigned char  gtc_ul_mod_type        : 1;  /* bit[0]  : �������ͱ�־��0��ʾGMSK���ƣ�1��ʾ8PSK���ơ���λĬ��ֵΪ0��HUASHAN�汾���������Ϊ0�� */
        unsigned char  gtc_ul_burst_type      : 1;  /* bit[1]  : BURST���ͱ�־��1��ʾNB��0��ʾAB����λĬ��ֵΪ0�� */
        unsigned char  gtc_ul_tsc_group_num   : 4;  /* bit[2-5]: ����NB�Ӽ�1ѵ���������0000���Ӽ�1��0��ѵ������0001���Ӽ�1��1��ѵ������0010���Ӽ�1��2��ѵ������0011���Ӽ�1��3��ѵ������0100���Ӽ�1��4��ѵ������0101���Ӽ�1��5��ѵ������0110���Ӽ�1��6��ѵ������0111���Ӽ�1��7��ѵ����������NB�Ӽ�2ѵ���������1000���Ӽ�2��0��ѵ������1001���Ӽ�2��1��ѵ������1010���Ӽ�2��2��ѵ������1011���Ӽ�2��3��ѵ������1100���Ӽ�2��4��ѵ������1101���Ӽ�2��5��ѵ������1110���Ӽ�2��6��ѵ������1111���Ӽ�2��7��ѵ������AB������������ã�����ֻ��0000��0001��0010������Ч��λĬ��ֵΪ4��b0000 */
        unsigned char  gtc_demod_loop_mode_en : 1;  /* bit[6]  : 1��ʾ�����н�����ز���ģʽ��0��ʾ�����������е��ƺ����н������ģʽ
                                                                 ���ź������������н�����ز���������ã������뻷�ز���ģʽ��ֵӦ������Ϊ0,����������ͨ��������õ����б���ʵ�ֻ��� */
        unsigned char  gtc_cpu_wrte_mod_pre   : 1;  /* bit[7]  : 1 ��ʾ��CPU�����Ƶ���ǰRAM���ݵ�д�롣0 ��ʾ�����б��������Ƶ���ǰRAM���ݵ�д�롣��λĬ��ֵΪ0 */
    } reg;
} GBBP_GTC_UL_MAP_PARA_UNION;
#define GBBP_GTC_UL_MAP_PARA_gtc_ul_mod_type_START          (0)
#define GBBP_GTC_UL_MAP_PARA_gtc_ul_mod_type_END            (0)
#define GBBP_GTC_UL_MAP_PARA_gtc_ul_burst_type_START        (1)
#define GBBP_GTC_UL_MAP_PARA_gtc_ul_burst_type_END          (1)
#define GBBP_GTC_UL_MAP_PARA_gtc_ul_tsc_group_num_START     (2)
#define GBBP_GTC_UL_MAP_PARA_gtc_ul_tsc_group_num_END       (5)
#define GBBP_GTC_DEC_MAP_PARA_gtc_demod_loop_mode_en_START  (6)
#define GBBP_GTC_DEC_MAP_PARA_gtc_demod_loop_mode_en_END    (6)
#define GBBP_GTC_UL_MAP_PARA_gtc_cpu_wrte_mod_pre_START     (7)
#define GBBP_GTC_UL_MAP_PARA_gtc_cpu_wrte_mod_pre_END       (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_MAP_BURST_POS_UNION
 �ṹ˵��  : GTC_MAP_BURST_POS �Ĵ����ṹ���塣��ַƫ����:0xDE����ֵ:0x80�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_map_burst_pos_reg;
    struct
    {
        unsigned char  gtc_map_burst_pos     : 7;  /* bit[0-6]: ��Ҫ��ȥ��BURST�����ݴ洢λ��ָʾ����ѡ��Ϊ����RAM��ÿ��BURST�洢����ʼ��ַ���ο�gsp_ul_cod_burst_pos[6:0]��λ�ñ�ŷ�ʽ������ͬ���ǣ����ź��·����ǵ�ǰ׼�����Ƶ�BURSTλ�ñ�ţ��������������������ʼBURST��λ�ñ�š���
                                                                Ĭ��ֵΪ0 */
        unsigned char  gtc_map_ram_switch_en : 1;  /* bit[7]  : 1��ʾʹ��MAP��RAM(����ģ����������RAM)ƹ���л�ʹ�ܣ�0��ʾ����ģ��̶���ƹRAM(��ʱCPUд����������RAMҲֻ��д��ƹRAM)����λĬ��ֵΪ1 */
    } reg;
} GBBP_GTC_MAP_BURST_POS_UNION;
#define GBBP_GTC_MAP_BURST_POS_gtc_map_burst_pos_START      (0)
#define GBBP_GTC_MAP_BURST_POS_gtc_map_burst_pos_END        (6)
#define GBBP_GTC_MAP_BURST_POS_gtc_map_ram_switch_en_START  (7)
#define GBBP_GTC_MAP_BURST_POS_gtc_map_ram_switch_en_END    (7)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_MAP_START_UNION
 �ṹ˵��  : GTC_MAP_START �Ĵ����ṹ���塣��ַƫ����:0xDF����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_map_start_reg;
    struct
    {
        unsigned char  gtc_ul_map_start : 1;  /* bit[0]  : ��BURSTӳ�������źţ��ߵ�ƽ�����źţ���ǰ���������ź�6.25��Symble��,GTC�߼������� */
        unsigned char  reserved         : 7;  /* bit[1-7]:  */
    } reg;
} GBBP_GTC_MAP_START_UNION;
#define GBBP_GTC_MAP_START_gtc_ul_map_start_START  (0)
#define GBBP_GTC_MAP_START_gtc_ul_map_start_END    (0)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_ULMOD_TEST_MOD_HIGH_UNION
 �ṹ˵��  : GTC_ULMOD_TEST_MOD_HIGH �Ĵ����ṹ���塣��ַƫ����:0xE6����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_ulmod_test_mod_high_reg;
    struct
    {
        unsigned char  gtc_ulmod_test_mod_high : 4;  /* bit[0-3]: bit[3:0]:Ԥ���Ƴ��ȣ�0��ʾ������Ԥ���ƣ�Ĭ��ֵΪ4�����ƹ����У��ò���Ӧ���� */
        unsigned char  reserved                : 4;  /* bit[4-7]:  */
    } reg;
} GBBP_GTC_ULMOD_TEST_MOD_HIGH_UNION;
#define GBBP_GTC_ULMOD_TEST_MOD_HIGH_gtc_ulmod_test_mod_high_START  (0)
#define GBBP_GTC_ULMOD_TEST_MOD_HIGH_gtc_ulmod_test_mod_high_END    (3)


/*****************************************************************************
 �ṹ��    : GBBP_GTC_HD35_CAL_UNION
 �ṹ˵��  : GTC_HD35_CAL �Ĵ����ṹ���塣��ַƫ����:0xFA����ֵ:0x80�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      gtc_hd35_cal_reg;
    struct
    {
        unsigned char  gtc_hd35_cal_en         : 1;  /* bit[0]  : ȥ3��5��г��ģ������ʹ�ܣ�GTC���á��ڵ�������ǰ���á� */
        unsigned char  gtc_hd35_cal_sel        : 2;  /* bit[1-2]: ȥ3��5��г��ģ������ʹ�ò���ѡ���źţ�GTC���á�Ϊ��ȷ��У׼������ʱ��Ч����gsp_mod_start֮ǰ���ô�ѡ���ź���Ч�� */
        unsigned char  gtc_hd35_data_iq_bypass : 1;  /* bit[3]  : IQ������·ָʾ��1��ʾIQ������·��ֻ���HD3/HD5��������GTC���á������Ҫ��·HD35���ܣ�����Ҫ����cpu_hd35_cal_bypass�� */
        unsigned char  reserved                : 4;  /* bit[4-7]:  */
    } reg;
} GBBP_GTC_HD35_CAL_UNION;
#define GBBP_GTC_HD35_CAL_gtc_hd35_cal_en_START          (0)
#define GBBP_GTC_HD35_CAL_gtc_hd35_cal_en_END            (0)
#define GBBP_GTC_HD35_CAL_gtc_hd35_cal_sel_START         (1)
#define GBBP_GTC_HD35_CAL_gtc_hd35_cal_sel_END           (2)
#define GBBP_GTC_HD35_CAL_gtc_hd35_data_iq_bypass_START  (3)
#define GBBP_GTC_HD35_CAL_gtc_hd35_data_iq_bypass_END    (3)


/***======================================================================***
                     (9/9) register_define_gtc_timing
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : GBBP_TIMING_SLOT_HIGH_UNION
 �ṹ˵��  : TIMING_SLOT_HIGH �Ĵ����ṹ���塣��ַƫ����:0xBF����ֵ:0x00�����:8
 �Ĵ���˵��: 
*****************************************************************************/
typedef union
{
    unsigned char      timing_slot_high_reg;
    struct
    {
        unsigned char  tdma_slot_int_offset_high : 2;  /* bit[0-1]:  */
        unsigned char  reserved                  : 6;  /* bit[2-7]:  */
    } reg;
} GBBP_TIMING_SLOT_HIGH_UNION;
#define GBBP_TIMING_SLOT_HIGH_tdma_slot_int_offset_high_START  (0)
#define GBBP_TIMING_SLOT_HIGH_tdma_slot_int_offset_high_END    (1)




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

#endif /* end of bbp_gsm_gtc_interface.h */
