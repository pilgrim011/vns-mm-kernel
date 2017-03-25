/******************************************************************************

                 ��Ȩ���� (C), 2001-2012, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : phy_abb_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2012-12-26 14:48:06
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��12��26��
    ��    ��   : w60237
    �޸�����   : �ӡ�ComstarV300�Ĵ�������_update_1226.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __ABB_INTERFACE_V300_H__
#define __ABB_INTERFACE_V300_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define ABB_BASE_ADDR               ( 0x0000 )

/***======================================================================***
                     (1/1) register_define_ssi_reg
 ***======================================================================***/
/* �Ĵ���˵����RX 2Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G_SC
             010��4G
             011��3G_DC
             Others��reserved
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G,   3G_SC,    4G,   3G_DC,      
             00�� 2.167M,15.36M, 61.44M,30.72M(Ĭ��)
             01�� 4.33MHz,------,30.72M,------
             10�� ------, ------,15.36M,------
             11�� ------, ------, 7.68M,------
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      Reserved
   UNION�ṹ:  ABB_RX_2G_DIG_1_UNION */
#define ABB_RX_2G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x0)

/* �Ĵ���˵����RX 2Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6]      RX��DBB���ݽӿ�ʱ�����ã�
             1'b0��SDR�ӿڣ�
             1'b1��DDR�ӿڡ�
 bit[5]      Reserved
 bit[4]      RXͨ�������˲���bypass���ƣ�
             0����bypass
             1��bypass(Ĭ��)
 bit[3:2]    RXͨ����������ѡ��
             00��gainΪ0.5(Ĭ��)
             01��gainΪ0.75
             10��gainΪ0.85
             11��Reserved
 bit[1]      RXBͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر�
 bit[0]      RXAͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_RX_2G_DIG_2_UNION */
#define ABB_RX_2G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x1)

/* �Ĵ���˵����TX 2Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G
             001��3G(Ĭ��)
             010��4G &amp; ET &amp; APT
             Others��reserved
 bit[4:2]    TXͨ��CIC�˲���������ʿ��ƣ�
                  2G,     3G,     4G,     
                 (78M) (153.6M) (307.2M) 
             0��4.33MHz,30.72MHz,61.44MHz(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz
             2��-------,--------,15.36MHz
             3��-------,--------, 7.68MHz
             4��-------,--------, 3.84MHz
             Others��Reserved
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate(Ĭ��)
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_2G_DIG_1_UNION */
#define ABB_TX_2G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x2)

/* �Ĵ���˵����TX 2Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB ��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ(Ĭ��)
             1��ʹ��DWAģʽ 
 bit[4]      Reserved
 bit[3:2]    TXͨ��DEM constϵ����Ĭ��ֵ2(��demģ���е�����ֵΪdem_const_xx * 2)
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_2G_DIG_2_UNION */
#define ABB_TX_2G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x3)

/* �Ĵ���˵����TX 2Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:2]    ����
 bit[1]      TX��DBB���ݽӿ�ʱ�����ã�
             1'b0��SDR�ӿڣ�
             1'b1��DDR�ӿڡ�
 bit[0]      Reserved
   UNION�ṹ:  ABB_TX_2G_DIG_3_UNION */
#define ABB_TX_2G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x4)

/* �Ĵ���˵����RX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G
             001��3G_SC(Ĭ��)
             010��4G
             011��3G_DC
             Others��reserved
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G,   3G_SC,    4G,   3G_DC,      
             00�� 2.167M,15.36M, 61.44M,30.72M(Ĭ��)
             01�� 4.33MHz,------,30.72M,------
             10�� ------, ------,15.36M,------
             11�� ------, ------, 7.68M,------
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      Reserved
   UNION�ṹ:  ABB_RX_3G_DIG_1_UNION */
#define ABB_RX_3G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x5)

/* �Ĵ���˵����RX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6]      RX��DBB���ݽӿ�ʱ�����ã�
             1'b0��SDR�ӿڣ�
             1'b1��DDR�ӿڡ�
 bit[5]      Reserved
 bit[4]      RXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
 bit[3:2]    RXͨ����������ѡ��
             00��gainΪ0.5(Ĭ��)
             01��gainΪ0.75
             10��gainΪ0.85
             11��Reserved
 bit[1]      RXBͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر�
 bit[0]      RXAͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_RX_3G_DIG_2_UNION */
#define ABB_RX_3G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x6)

/* �Ĵ���˵����TX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G
             001��3G(Ĭ��)
             010��4G &amp; ET &amp; APT
             Others��reserved
 bit[4:2]    TXͨ��CIC�˲���������ʿ��ƣ�
                  2G,     3G,     4G,     
                 (78M) (153.6M) (307.2M) 
             0��4.33MHz,30.72MHz,61.44MHz(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz
             2��-------,--------,15.36MHz
             3��-------,--------, 7.68MHz
             4��-------,--------, 3.84MHz
             Others��Reserved
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_3G_DIG_1_UNION */
#define ABB_TX_3G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x7)

/* �Ĵ���˵����TX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB ��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ(Ĭ��)
             1��ʹ��DWAģʽ 
 bit[4]      Reserved
 bit[3:2]    TXͨ��DEM constϵ����Ĭ��ֵ2(��demģ���е�����ֵΪdem_const_xx * 2)
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_3G_DIG_2_UNION */
#define ABB_TX_3G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x8)

/* �Ĵ���˵����TX 3Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:2]    ����
 bit[1]      TX��DBB���ݽӿ�ʱ�����ã�
             1'b0��SDR�ӿڣ�
             1'b1��DDR�ӿڡ�
 bit[0]      Reserved
   UNION�ṹ:  ABB_TX_3G_DIG_3_UNION */
#define ABB_TX_3G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x9)

/* �Ĵ���˵����RX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G
             001��3G_SC
             010��4G(Ĭ��)
             011��3G_DC
             Others��reserved
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G,   3G_SC,    4G,   3G_DC,      
             00�� 2.167M,15.36M, 61.44M,30.72M(Ĭ��)
             01�� 4.33MHz,------,30.72M,------
             10�� ------, ------,15.36M,------
             11�� ------, ------, 7.68M,------
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      Reserved
   UNION�ṹ:  ABB_RX_4G_DIG_1_UNION */
#define ABB_RX_4G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0xA)

/* �Ĵ���˵����RX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6]      RX��DBB���ݽӿ�ʱ�����ã�
             1'b0��SDR�ӿڣ�
             1'b1��DDR�ӿڡ�
 bit[5]      Reserved
 bit[4]      RXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
 bit[3:2]    RXͨ����������ѡ��
             00��gainΪ0.5(Ĭ��)
             01��gainΪ0.75
             10��gainΪ0.85
             11��Reserved
 bit[1]      RXBͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر�
 bit[0]      RXAͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_RX_4G_DIG_2_UNION */
#define ABB_RX_4G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0xB)

/* �Ĵ���˵����TX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G
             001��3G
             010��4G &amp; ET &amp; APT(Ĭ��)
             Others��reserved
 bit[4:2]    TXͨ��CIC�˲���������ʿ��ƣ�
                  2G,     3G,     4G,     
                 (78M) (153.6M) (307.2M) 
             0��4.33MHz,30.72MHz,61.44MHz(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz
             2��-------,--------,15.36MHz
             3��-------,--------, 7.68MHz
             4��-------,--------, 3.84MHz
             Others��Reserved
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_4G_DIG_1_UNION */
#define ABB_TX_4G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0xC)

/* �Ĵ���˵����TX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB ��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ(Ĭ��)
             1��ʹ��DWAģʽ 
 bit[4]      Reserved
 bit[3:2]    TXͨ��DEM constϵ����Ĭ��ֵ2(��demģ���е�����ֵΪdem_const_xx * 2)
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_4G_DIG_2_UNION */
#define ABB_TX_4G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0xD)

/* �Ĵ���˵����TX 4Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:2]    ����
 bit[1]      TX��DBB���ݽӿ�ʱ�����ã�
             1'b0��SDR�ӿڣ�
             1'b1��DDR�ӿڡ�
 bit[0]      Reserved
   UNION�ṹ:  ABB_TX_4G_DIG_3_UNION */
#define ABB_TX_4G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0xE)

/* �Ĵ���˵����RX TDSģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    Reserved
 bit[4:3]    Reserved
 bit[2]      Reserved
 bit[1]      Reserved
 bit[0]      Reserved
   UNION�ṹ:  ABB_RX_TDS_DIG_1_UNION */
#define ABB_RX_TDS_DIG_1_ADDR                         (ABB_BASE_ADDR + 0xF)

/* �Ĵ���˵����RX TDSģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6]      TXͨ��CFR bypass���ƣ�
             0����bypass
             1��bypass(Ĭ��)
 bit[5]      RXͨ�������˲���bypass���ƣ�
             0����bypass
             1��bypass(Ĭ��)
 bit[4]      RXͨ����������ѡ��
             00��gainΪ0.5(Ĭ��)
             01��gainΪ0.75
             10��gainΪ0.85
             11��Reserved
 bit[3:2]    RXBͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر�
 bit[1]      
 bit[0]      RXAͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_RX_TDS_DIG_2_UNION */
#define ABB_RX_TDS_DIG_2_ADDR                         (ABB_BASE_ADDR + 0x10)

/* �Ĵ���˵����TX TDSģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXģʽ���ƣ�
             000��2G
             001��3G
             010��4G &amp; ET &amp; APT
             011��TDS(Ĭ��)
             Others��CA
 bit[4:2]    TXͨ��CIC�˲���������ʿ��ƣ�
                  2G,     3G,     4G,      TDS,      CA
                 (78M) (153.6M) (307.2M) (153.6M) (614.4M)
             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,122.88MHz(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2��-------,--------,15.36MHz,--------,--------
             3��-------,--------, 7.68MHz,--------,--------
             4��-------,--------, 3.84MHz,--------,--------
             Others��Reserved
 bit[1]      TXͨ������˲�����bypass�ź�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_TDS_DIG_1_UNION */
#define ABB_TX_TDS_DIG_1_ADDR                         (ABB_BASE_ADDR + 0x11)

/* �Ĵ���˵����TX TDSģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ(Ĭ��)
             1��ʹ��DWAģʽ 
 bit[4]      TXͨ��SDM Dither���ƣ�
             0����ʹ��
             1��ʹ��
 bit[3]      TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
             0����ʹ��
             1��ʹ��
 bit[2]      TXͨ��DEM constϵ����
             0��2(Ĭ��)
             1��4
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_TDS_DIG_2_UNION */
#define ABB_TX_TDS_DIG_2_ADDR                         (ABB_BASE_ADDR + 0x12)

/* �Ĵ���˵����TX TDSģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:2]    ����
 bit[1]      TX��DBB���ݽӿ�ʱ�����ã�
             1'b0��SDR�ӿڣ�
             1'b1��DDR�ӿڡ�
 bit[0]      Reserved
   UNION�ṹ:  ABB_TX_TDS_DIG_3_UNION */
#define ABB_TX_TDS_DIG_3_ADDR                         (ABB_BASE_ADDR + 0x13)

/* �Ĵ���˵����TX ETģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G
             001��3G
             010��4G &amp; ET &amp; APT(Ĭ��)
             Others��reserved
 bit[4:2]    TXͨ��CIC�˲���������ʿ��ƣ�
                  2G,     3G,     4G,     
                 (78M) (153.6M) (307.2M) 
             0��4.33MHz,30.72MHz,61.44MHz(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz
             2��-------,--------,15.36MHz
             3��-------,--------, 7.68MHz
             4��-------,--------, 3.84MHz
             Others��Reserved
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_ET_DIG_1_UNION */
#define ABB_TX_ET_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x14)

/* �Ĵ���˵����TX ETģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB ��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ(Ĭ��)
             1��ʹ��DWAģʽ 
 bit[4]      Reserved
 bit[3:2]    TXͨ��DEM constϵ����Ĭ��ֵ2(��demģ���е�����ֵΪdem_const_xx * 2)
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_ET_DIG_2_UNION */
#define ABB_TX_ET_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x15)

/* �Ĵ���˵����TX ETģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:2]    ����
 bit[1]      TX��DBB���ݽӿ�ʱ�����ã�
             1'b0��SDR�ӿڣ�
             1'b1��DDR�ӿڡ�
 bit[0]      Reserved
   UNION�ṹ:  ABB_TX_ET_DIG_3_UNION */
#define ABB_TX_ET_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x16)

/* �Ĵ���˵����TX APTģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G
             001��3G
             010��4G &amp; ET &amp; APT(Ĭ��)
             Others��reserved
 bit[4:2]    TXͨ��CIC�˲���������ʿ��ƣ�
                  2G,     3G,     4G,     
                 (78M) (153.6M) (307.2M) 
             0��4.33MHz,30.72MHz,61.44MHz(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz
             2��-------,--------,15.36MHz
             3��-------,--------, 7.68MHz
             4��-------,--------, 3.84MHz
             Others��Reserved
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_APT_DIG_1_UNION */
#define ABB_TX_APT_DIG_1_ADDR                         (ABB_BASE_ADDR + 0x17)

/* �Ĵ���˵����TX APTģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB ��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ(Ĭ��)
             1��ʹ��DWAģʽ 
 bit[4]      Reserved
 bit[3:2]    TXͨ��DEM constϵ����Ĭ��ֵ2(��demģ���е�����ֵΪdem_const_xx * 2)
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_APT_DIG_2_UNION */
#define ABB_TX_APT_DIG_2_ADDR                         (ABB_BASE_ADDR + 0x18)

/* �Ĵ���˵����TX APTģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:2]    ����
 bit[1]      TX��DBB���ݽӿ�ʱ�����ã�
             1'b0��SDR�ӿڣ�
             1'b1��DDR�ӿڡ�
 bit[0]      Reserved
   UNION�ṹ:  ABB_TX_APT_DIG_3_UNION */
#define ABB_TX_APT_DIG_3_ADDR                         (ABB_BASE_ADDR + 0x19)

/* �Ĵ���˵����RX CAģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G
             001��3G_SC
             010��4G &amp; ET &amp; APT
             011��3G_DC
             100��TDS
             Others��CA(Ĭ��)
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G,   3G_SC,  4G,  3G_DC,   TDS,   CA
             00�� 2.167M,15.36M,61.44M,30.72M,30.72M,122.88M(Ĭ��)
             01�� ------,------,30.72M,15.36M,10.24M,------
             10�� ------,------,15.36M,------,------,------
             11�� ------,------, 7.68M,------,------,------
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      RXͨ�������˲��������̶�ϵ��ѡ��
             0���̶�ϵ��1
             1���̶�ϵ��2
   UNION�ṹ:  ABB_RX_CA_DIG_1_UNION */
#define ABB_RX_CA_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x1A)

/* �Ĵ���˵����RX CAģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7:6]    ����
 bit[5]      TXͨ��CFR bypass���ƣ�
             0����bypass
             1��bypass(Ĭ��)
 bit[4]      RXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
 bit[3:2]    RXͨ����������ѡ��
             00��gainΪ0.5(Ĭ��)
             01��gainΪ0.75
             10��gainΪ0.85
             11��Reserved
 bit[1]      RXBͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر�
 bit[0]      RXAͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_RX_CA_DIG_2_UNION */
#define ABB_RX_CA_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x1B)

/* �Ĵ���˵����TX CAģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G
             001��3G
             010��4G &amp; ET &amp; APT
             011��TDS
             others��CA(Ĭ��)
 bit[4:2]    TXͨ��CIC�˲���������ʿ��ƣ�
                  2G,     3G,     4G,      TDS,      CA
                 (78M) (153.6M) (307.2M) (153.6M) (614.4M)
             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,122.88MHz(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
             2��-------,--------,15.36MHz,--------,--------
             3��-------,--------, 7.68MHz,--------,--------
             4��-------,--------, 3.84MHz,--------,--------
             Others��Reserved
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_CA_DIG_1_UNION */
#define ABB_TX_CA_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x1C)

/* �Ĵ���˵����TX CAģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ(Ĭ��)
             1��ʹ��DWAģʽ 
 bit[4]      TXͨ��SDM Dither���ƣ�
             0����ʹ��
             1��ʹ��
 bit[3]      TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
             0����ʹ��
             1��ʹ��
 bit[2]      TXͨ��DEM constϵ����
             0��2(Ĭ��)
             1��4
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_CA_DIG_2_UNION */
#define ABB_TX_CA_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x1D)

/* �Ĵ���˵����TX CAģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:2]    ����
 bit[1]      TX��DBB���ݽӿ�ʱ�����ã�
             1'b0��SDR�ӿڣ�
             1'b1��DDR�ӿڡ�
 bit[0]      Reserved
   UNION�ṹ:  ABB_TX_CA_DIG_3_UNION */
#define ABB_TX_CA_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x1E)

/* �Ĵ���˵����RX IDLEģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G_SC
             010��4G
             011��3G_DC
             Others��reserved
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G,   3G_SC,    4G,   3G_DC,      
             00�� 2.167M,15.36M, 61.44M,30.72M(Ĭ��)
             01�� 4.33MHz,------,30.72M,------
             10�� ------, ------,15.36M,------
             11�� ------, ------, 7.68M,------
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      Reserved
   UNION�ṹ:  ABB_RX_IDLE_DIG_1_UNION */
#define ABB_RX_IDLE_DIG_1_ADDR                        (ABB_BASE_ADDR + 0x1F)

/* �Ĵ���˵����RX IDLEģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6]      RX��DBB���ݽӿ�ʱ�����ã�
             1'b0��SDR�ӿڣ�
             1'b1��DDR�ӿڡ�
 bit[5]      Reserved
 bit[4]      RXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
 bit[3:2]    RXͨ����������ѡ��
             00��gainΪ0.5(Ĭ��)
             01��gainΪ0.75
             10��gainΪ0.85
             11��Reserved
 bit[1]      RXBͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر�
 bit[0]      RXAͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_RX_IDLE_DIG_2_UNION */
#define ABB_RX_IDLE_DIG_2_ADDR                        (ABB_BASE_ADDR + 0x20)

/* �Ĵ���˵����TX IDLEģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G
             001��3G
             010��4G &amp; ET &amp; APT(Ĭ��)
             Others��reserved
 bit[4:2]    TXͨ��CIC�˲���������ʿ��ƣ�
                  2G,     3G,     4G,     
                 (78M) (153.6M) (307.2M) 
             0��4.33MHz,30.72MHz,61.44MHz(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz
             2��-------,--------,15.36MHz
             3��-------,--------, 7.68MHz
             4��-------,--------, 3.84MHz
             Others��Reserved
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_IDLE_DIG_1_UNION */
#define ABB_TX_IDLE_DIG_1_ADDR                        (ABB_BASE_ADDR + 0x21)

/* �Ĵ���˵����TX IDLEģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6]      1'b0��SDR
             1'b1��DDR
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ(Ĭ��)
             1��ʹ��DWAģʽ 
 bit[4]      Reserved
 bit[3:2]    TXͨ��DEM constϵ����Ĭ��ֵ2(��ģ����*2��
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_IDLE_DIG_2_UNION */
#define ABB_TX_IDLE_DIG_2_ADDR                        (ABB_BASE_ADDR + 0x22)

/* �Ĵ���˵����TX IDLEģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:2]    ����
 bit[1]      TX��DBB���ݽӿ�ʱ�����ã�
             1'b0��SDR�ӿڣ�
             1'b1��DDR�ӿڡ�
 bit[0]      Reserved
   UNION�ṹ:  ABB_TX_IDLE_DIG_3_UNION */
#define ABB_TX_IDLE_DIG_3_ADDR                        (ABB_BASE_ADDR + 0x23)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼��������reg_analog_wr00��
 bit[7]      RXA_I ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[6]      RXA_Q ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[5]      RXB_I ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[4]      RXB_Q ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!RXQ_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[3]      Reserved
 bit[2:1]    ģʽ���ƣ�
             00��4G 
             01��3G
             10��3G_DC
             11��2G(Ĭ��)
 bit[0]      Reserved
   UNION�ṹ:  ABB_RX_2G_ANA_1_UNION */
#define ABB_RX_2G_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x24)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼��������reg_analog_wr01��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_RX_2G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x25)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼��������reg_analog_wr48��
 bit[7:6]    TX filter��ֹƵ��ѡ��
             00: 10MHz(Ĭ��)
             01: 20MHz;
             11:40MHz;
             10:reserved
 bit[5:4]    TX Mode ʱ�ӿ��ƣ�
             00: 1��Ƶ
             01: 2��Ƶ
             10: 3��Ƶ
             11: 4��Ƶ(Ĭ��)
 bit[3]      TX_I DAC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!TX_I_PD)|WG_TX_EN = 1ʱ����������ر�
 bit[2]      TX_Q DAC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر�
 bit[1:0]    ģʽ���ƣ�
             00��4G &amp; ET &amp; APT
             01��3G 
             10��--
             11��2G(Ĭ��)
   UNION�ṹ:  ABB_TX_2G_ANA_1_UNION */
#define ABB_TX_2G_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x26)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼��������reg_analog_wr49��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_TX_2G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x27)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼��������reg_analog_wr00��
 bit[7]      RXA_I ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[6]      RXA_Q ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!RXA_Q_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[5]      RXB_I ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[4]      RXB_Q ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!RXB_Q_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[3]      Reserved
 bit[2:1]    ģʽ���ƣ�
             00��4G 
             01��3G
             10��3G_DC
             11��2G(Ĭ��)
 bit[0]      Reserved
   UNION�ṹ:  ABB_RX_3G_ANA_1_UNION */
#define ABB_RX_3G_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x28)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼��������reg_analog_wr01��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_RX_3G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x29)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼��������reg_analog_wr48��
 bit[7:6]    TX filter��ֹƵ��ѡ��
             00: 10MHz(Ĭ��)
             01: 20MHz;
             11:40MHz;
             10:reserved
 bit[5:4]    TX Mode ʱ�ӿ��ƣ�
             00: 1��Ƶ
             01: 2��Ƶ(Ĭ��)
             10: 3��Ƶ
             11: 4��Ƶ
 bit[3]      TX_I DAC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!TX_I_PD)|XX_TX_EN = 1ʱ����������ر�
 bit[2]      TX_Q DAC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر�
 bit[1:0]    ģʽ���ƣ�
             00��4G &amp; ET &amp; APT
             01��3G (Ĭ��)
             10��--
             11��2G
   UNION�ṹ:  ABB_TX_3G_ANA_1_UNION */
#define ABB_TX_3G_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x2A)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼��������reg_analog_wr49��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_TX_3G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x2B)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼��������reg_analog_wr00��
 bit[7]      RXA_I ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[6]      RXA_Q ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!RXA_Q_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[5]      RXB_I ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[4]      RXB_Q ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!RXB_Q_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[3]      Reserved
 bit[2:1]    ģʽ���ƣ�
             00��4G (Ĭ��)
             01��3G
             10��3G_DC
             11��2G
 bit[0]      Reserved
   UNION�ṹ:  ABB_RX_4G_ANA_1_UNION */
#define ABB_RX_4G_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x2C)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼��������reg_analog_wr01��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_RX_4G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x2D)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼��������reg_analog_wr48��
 bit[7:6]    TX filter��ֹƵ��ѡ��
             00: 10MHz;
             01: 20MHz;(Ĭ��)
             11:40MHz;
             10:reserved
 bit[5:4]    TX Mode ʱ�ӿ��ƣ�
             00: 1��Ƶ(Ĭ��)
             01: 2��Ƶ
             10: 3��Ƶ
             11: 4��Ƶ
 bit[3]      TX_I DAC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!TX_I_PD)|XX_TX_EN = 1ʱ����������ر�
 bit[2]      TX_Q DAC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر�
 bit[1:0]    ģʽ���ƣ�
             00��4G &amp; ET &amp; APT(Ĭ��)
             01��3G 
             10��--
             11��2G
   UNION�ṹ:  ABB_TX_4G_ANA_1_UNION */
#define ABB_TX_4G_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x2E)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼��������reg_analog_wr49��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_TX_4G_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x2F)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼��������reg_analog_wr00��
 bit[7]      RXA_I ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[6]      RXA_Q ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!RXA_Q_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[5]      RXB_I ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[4]      RXB_Q ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!RXB_Q_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[3]      RX DEM Mode Selection,bit 1
             000: DWA
             001: CLA1
             010: CLA2
             011: CLA3
             100: CLA4
             101: CLA5
             110: CLA6
             111: CLA7
 bit[2:1]    ģʽ���ƣ�
             00��4G &amp; ET &amp; APT
             01��3G
             10��3G_DC &amp; TDS(Ĭ��)
             11��2G
 bit[0]      RX DEM Mode Selection,bit 0
             000: DWA
             001: CLA1
             010: CLA2
             011: CLA3
             100: CLA4
             101: CLA5
             110: CLA6
             111: CLA7
   UNION�ṹ:  ABB_RX_TDS_ANA_1_UNION */
#define ABB_RX_TDS_ANA_1_ADDR                         (ABB_BASE_ADDR + 0x30)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼��������reg_analog_wr01��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_RX_TDS_ANA_2_ADDR                         (ABB_BASE_ADDR + 0x31)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼��������reg_analog_wr48��
 bit[7]      TX filter��ֹƵ��ѡ��
             0: 10MHz
             1: 20MHz(Ĭ��)
 bit[6:5]    TX Mode ʱ�ӿ��ƣ�
             00: 1��Ƶ
             01: 2��Ƶ(Ĭ��)
             10: 3��Ƶ
             11: 4��Ƶ
 bit[4]      TX_I DAC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!TX_I_PD)|XX_TX_EN = 1ʱ����������ر�
 bit[3]      TX_Q DAC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر�
 bit[2]      Reserved
 bit[1:0]    ģʽ���ƣ�
             00��4G &amp; ET &amp; APT
             01��3G &amp; TDS(Ĭ��)
             10��--
             11��2G
   UNION�ṹ:  ABB_TX_TDS_ANA_1_UNION */
#define ABB_TX_TDS_ANA_1_ADDR                         (ABB_BASE_ADDR + 0x32)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼��������reg_analog_wr49��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_TX_TDS_ANA_2_ADDR                         (ABB_BASE_ADDR + 0x33)

/* �Ĵ���˵����TX ET���üĴ����������߿��߼��������reg_analog_wr48��
 bit[7:6]    TX filter��ֹƵ��ѡ��
             00: 10MHz;
             01: 20MHz;(Ĭ��)
             11:40MHz;
             10:reserved
 bit[5:4]    TX Mode ʱ�ӿ��ƣ�
             00: 1��Ƶ(Ĭ��)
             01: 2��Ƶ
             10: 3��Ƶ
             11: 4��Ƶ
 bit[3]      TX_I DAC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!TX_I_PD)|WG_TX_EN = 1ʱ����������ر�
 bit[2]      TX_Q DAC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!TX_Q_PD)|(WG_TX_EN &amp;&amp; WG_LINE_CONTROL_MODE~
             =ET &amp;&amp; WG_LINE_CONTROL_MODE~=APT) = 1ʱ����������ر�
 bit[1:0]    ģʽ���ƣ�
             00��4G &amp; ET &amp; APT(Ĭ��)
             01��3G 
             10��--
             11��2G
   UNION�ṹ:  ABB_TX_ET_ANA_1_UNION */
#define ABB_TX_ET_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x34)

/* �Ĵ���˵����RX ET���üĴ����������߿��߼��������reg_analog_wr49��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_TX_ET_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x35)

/* �Ĵ���˵����TX APT���üĴ����������߿��߼��������reg_analog_wr48��
 bit[7:6]    TX filter��ֹƵ��ѡ��
             00: 10MHz;
             01: 20MHz;(Ĭ��)
             11:40MHz;
             10:reserved
 bit[5:4]    TX Mode ʱ�ӿ��ƣ�
             00: 1��Ƶ
             01: 2��Ƶ
             10: 3��Ƶ
             11: 4��Ƶ(Ĭ��)
 bit[3]      TX_I DAC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!TX_I_PD)|(XX_TX_EN &amp;&amp; ET_SEL) = 1ʱ����������ر�
 bit[2]      TX_Q DAC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!TX_Q_PD)|(XX_TX_EN &amp;&amp; ~ET_SEL) = 1ʱ����������ر�
 bit[1:0]    ģʽ���ƣ�
             00��4G &amp; ET &amp; APT(Ĭ��)
             01��3G 
             10��--
             11��2G
   UNION�ṹ:  ABB_TX_APT_ANA_1_UNION */
#define ABB_TX_APT_ANA_1_ADDR                         (ABB_BASE_ADDR + 0x36)

/* �Ĵ���˵����RX APT���üĴ����������߿��߼��������reg_analog_wr49��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_TX_APT_ANA_2_ADDR                         (ABB_BASE_ADDR + 0x37)

/* �Ĵ���˵����RX CA���üĴ����������߿��߼��������reg_analog_wr00��
 bit[7]      RXA_I ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[6]      RXA_Q ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!RXA_Q_PD)|XX_RXA_EN = 1ʱ����������ر�
 bit[5]      RXB_I ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[4]      RXB_Q ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!RXB_Q_PD)|XX_RXB_EN = 1ʱ����������ر�
 bit[3]      RX DEM Mode Selection,bit 1
             000: DWA
             001: CLA1
             010: CLA2
             011: CLA3
             100: CLA4
             101: CLA5
             110: CLA6
             111: CLA7
 bit[2:1]    ģʽ���ƣ�
             00��4G &amp; ET &amp; APT(Ĭ��)
             01��3G
             10��3G_DC &amp; TDS
             11��2G
 bit[0]      RX DEM Mode Selection,bit 0
             000: DWA
             001: CLA1
             010: CLA2
             011: CLA3
             100: CLA4
             101: CLA5
             110: CLA6
             111: CLA7
   UNION�ṹ:  ABB_RX_CA_ANA_1_UNION */
#define ABB_RX_CA_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x38)

/* �Ĵ���˵����RX CA���üĴ����������߿��߼��������reg_analog_wr01��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_RX_CA_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x39)

/* �Ĵ���˵����TX CA���üĴ����������߿��߼��������reg_analog_wr48��
 bit[7]      TX filter��ֹƵ��ѡ��
             0: 10MHz
             1: 20MHz(Ĭ��)
 bit[6:5]    TX Mode ʱ�ӿ��ƣ�
             00: 1��Ƶ
             01: 2��Ƶ
             10: 3��Ƶ
             11: 4��Ƶ(Ĭ��)
 bit[4]      TX_I DAC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!TX_I_PD)|(XX_TX_EN &amp;&amp; ET_SEL) = 1ʱ����������ر�
 bit[3]      TX_Q DAC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!TX_Q_PD)|(XX_TX_EN &amp;&amp; ~ET_SEL) = 1ʱ����������ر�
 bit[2]      Reserved
 bit[1:0]    ģʽ���ƣ�
             00��4G &amp; ET &amp; APT(Ĭ��)
             01��3G &amp; TDS
             10��--
             11��2G
   UNION�ṹ:  ABB_TX_CA_ANA_1_UNION */
#define ABB_TX_CA_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x3A)

/* �Ĵ���˵����RX CA���üĴ����������߿��߼��������reg_analog_wr49��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_TX_CA_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x3B)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼��������reg_analog_wr00��
 bit[7]      RXA_I ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
 bit[6]      RXA_Q ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
 bit[5]      RXB_I ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
 bit[4]      RXB_Q ADC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
 bit[3]      Reserved
 bit[2:1]    ģʽ���ƣ�
             00��4G (Ĭ��)
             01��3G
             10��3G_DC
             11��2G
 bit[0]      Reserved
   UNION�ṹ:  ABB_RX_IDLE_ANA_1_UNION */
#define ABB_RX_IDLE_ANA_1_ADDR                        (ABB_BASE_ADDR + 0x3C)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼��������reg_analog_wr01��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_RX_IDLE_ANA_2_ADDR                        (ABB_BASE_ADDR + 0x3D)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼��������reg_analog_wr48��
 bit[7:6]    TX filter��ֹƵ��ѡ��
             00: 10MHz;
             01: 20MHz;(Ĭ��)
             11:40MHz;
             10:reserved
 bit[5:4]    TX Mode ʱ�ӿ��ƣ�
             00: 1��Ƶ(Ĭ��)
             01: 2��Ƶ
             10: 3��Ƶ
             11: 4��Ƶ
 bit[3]      TX_I DAC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!TX_I_PD)|XX_TX_EN = 1ʱ����������ر�
 bit[2]      TX_Q DAC Power Down����
             0:Power On
             1:Power Down(Ĭ��)
             (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر�
 bit[1:0]    ģʽ���ƣ�
             00��4G &amp; ET &amp; APT(Ĭ��)
             01��3G 
             10��--
             11��2G
   UNION�ṹ:  ABB_TX_IDLE_ANA_1_UNION */
#define ABB_TX_IDLE_ANA_1_ADDR                        (ABB_BASE_ADDR + 0x3E)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼��������reg_analog_wr49��
   ��      ����TBD
   UNION�ṹ ���� */
#define ABB_TX_IDLE_ANA_2_ADDR                        (ABB_BASE_ADDR + 0x3F)

/* �Ĵ���˵����version�Ĵ�����
   ��      ������ģ�ⲿ�־����汾�Ĵ���ֵ
   UNION�ṹ ���� */
#define ABB_CH1_VERSION_ADDR                          (ABB_BASE_ADDR + 0x40)

/* �Ĵ���˵��������ģʽ�Ĵ�����
 bit[7]      ����
 bit[6]      ���õ���λ�źţ�
             0�������������λ(Ĭ��)
             1�����������λ
 bit[5:3]    bit[4:3]����ģʽ���ƣ�
             00������ģʽ(Ĭ��)
             01�������㷨�߼�����ģʽ
             10��RXģ�����ģʽ(bypass RX�����˲���)
             11�����ֽӿڻ���ģʽ
             bit[5]��reserved
 bit[2:1]    RXģ�����ģʽ��ͨ��ѡ��
             00�����RXA Iģ�����������(Ĭ��)
             01�����RXA Qģ�����������
             10�����RXB Iģ�����������
             11�����RXB Qģ�����������
 bit[0]      ����
   UNION�ṹ:  ABB_CH1_TESTMODE_UNION */
#define ABB_CH1_TESTMODE_ADDR                         (ABB_BASE_ADDR + 0x41)

/* �Ĵ���˵����ͨ�����ƼĴ�����
 bit[7:1]    ����
 bit[0]      ET/APTͨ��ѡ��
             0��ѡ��TXͨ��I·��ET/APT
             1��ѡ��TXͨ��Q·��ET/APT
   UNION�ṹ:  ABB_CH1_CTRL_UNION */
#define ABB_CH1_CTRL_ADDR                             (ABB_BASE_ADDR + 0x42)

/* �Ĵ���˵����CFR��ֵ��ⴰ���Ĵ�����
 bit[7:4]    CFR��������
 bit[3]      ����
 bit[2]      CFR�˲���ѡ��
             0��bypass�˲���
             1����bypass�˲���
 bit[1:0]    CFR��ֵ��ⷽʽ��
             00���������
             01���������
             10���������
             11��ȫ����ֵ
   UNION�ṹ:  ABB_CH1_CFR_CTRL_UNION */
#define ABB_CH1_CFR_CTRL_ADDR                         (ABB_BASE_ADDR + 0x43)

/* �Ĵ���˵�����߿�ѡ��
 bit[7]      ѡ��RXA_EN�߿أ�0: tie to 0(Ĭ�ϣ�
             1: from line control
 bit[6]      ѡ��RXB_EN�߿أ�0: tie to 0(Ĭ�ϣ�
             1: from line control
 bit[5]      ѡ��TX_EN�߿أ�0: tie to 0(Ĭ�ϣ�
             1: from line control
 bit[4]      ѡ��ET�߿�ģʽ��0: tie to 0(Ĭ�ϣ�
             1: from line control
 bit[3]      ѡ��APT�߿�ģʽ��0: tie to 0(Ĭ�ϣ�
             1: from line control
 bit[2]      ѡ��4G�߿�ģʽ��0: tie to 0(Ĭ�ϣ�
             1: from line control
 bit[1]      ѡ��3G�߿�ģʽ��0: tie to 0(Ĭ�ϣ�
             1: from line control
 bit[0]      ѡ��2G�߿�ģʽ��0: tie to 0(Ĭ�ϣ�
             1: from line control
   UNION�ṹ:  ABB_CH1_LINE_CTRL_SEL_UNION */
#define ABB_CH1_LINE_CTRL_SEL_ADDR                    (ABB_BASE_ADDR + 0x44)

/* �Ĵ���˵����RX���ֹ���ģʽ�ϱ��Ĵ�����
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G
             001��3G_SC
             010��4G
             011��3G_DC
             Others��reserved
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G,   3G_SC,    4G,   3G_DC,      
             00�� 2.167M,15.36M, 61.44M,30.72M
             01�� 4.33MHz,------,30.72M,------
             10�� ------, ------,15.36M,------
             11�� ------, ------, 7.68M,------
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      Reserved
   UNION�ṹ:  ABB_CH1_RX_DIG_RPT_UNION */
#define ABB_CH1_RX_DIG_RPT_ADDR                       (ABB_BASE_ADDR + 0x45)

/* �Ĵ���˵����TX���ֹ���ģʽ�ϱ��Ĵ�����
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G
             001��3G
             010��4G &amp; ET &amp; APT
             Others��reserved
 bit[4:2]    TXͨ��CIC�˲���������ʿ��ƣ�
                  2G,     3G,     4G,     
                 (78M) (153.6M) (307.2M) 
             0��4.33MHz,30.72MHz,61.44MHz
             1��2.16MHz,15.36MHz,30.72MHz
             2��-------,--------,15.36MHz
             3��-------,--------, 7.68MHz
             4��-------,--------, 3.84MHz
             Others��Reserved
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass
             1��bypass
   UNION�ṹ:  ABB_CH1_TX_DIG_RPT_UNION */
#define ABB_CH1_TX_DIG_RPT_ADDR                       (ABB_BASE_ADDR + 0x46)

/* �Ĵ���˵����TXͨ��offset�Ĵ�����
   ��      ����TXͨ��I·dc offset����
   UNION�ṹ ���� */
#define ABB_CH1_TX_I_OFFSET_ADDR                      (ABB_BASE_ADDR + 0x48)

/* �Ĵ���˵����TXͨ��offset�Ĵ�����
   ��      ����TXͨ��Q·dc offset����
   UNION�ṹ ���� */
#define ABB_CH1_TX_Q_OFFSET_ADDR                      (ABB_BASE_ADDR + 0x49)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXA_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4A)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXAͨ��I·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXAͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH1_RXA_I_COEF1_UNION */
#define ABB_CH1_RXA_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x4B)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH1_RXA_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x4C)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXAͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH1_RXA_I_COEF3_UNION */
#define ABB_CH1_RXA_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x4D)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXA_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x4E)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��Q·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXA_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4F)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXAͨ��Q·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXAͨ��Q·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH1_RXA_Q_COEF1_UNION */
#define ABB_CH1_RXA_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x50)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��Q·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH1_RXA_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x51)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXAͨ��Q·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH1_RXA_Q_COEF3_UNION */
#define ABB_CH1_RXA_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x52)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��Q·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXA_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x53)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXB_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x54)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXBͨ��I·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXBͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH1_RXB_I_COEF1_UNION */
#define ABB_CH1_RXB_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x55)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH1_RXB_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x56)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXBͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH1_RXB_I_COEF3_UNION */
#define ABB_CH1_RXB_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x57)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXB_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x58)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��Q·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXB_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x59)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXBͨ��Q·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXBͨ��Q·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH1_RXB_Q_COEF1_UNION */
#define ABB_CH1_RXB_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x5A)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��Q·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH1_RXB_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x5B)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXBͨ��Q·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH1_RXB_Q_COEF3_UNION */
#define ABB_CH1_RXB_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x5C)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��Q·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXB_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x5D)

/* �Ĵ���˵����RXAͨ��BLOCKING DCR���üĴ�����
 bit[7:5]    RXA����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ��
 bit[4:0]    RXA����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣
   UNION�ṹ:  ABB_CH1_REG_RXA_DCR_CFG_UNION */
#define ABB_CH1_REG_RXA_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x5E)

/* �Ĵ���˵����RXBͨ��BLOCKING DCR���üĴ�����
 bit[7:5]    RXB����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ��
 bit[4:0]    RXB����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣
   UNION�ṹ:  ABB_CH1_REG_RXB_DCR_CFG_UNION */
#define ABB_CH1_REG_RXB_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x5F)

/* �Ĵ���˵����BLOCKING DCR���ܿ��ƼĴ�����
 bit[7:2]    ����
 bit[1]      RXB����BLOCKING DCR����bypass���ơ�
             0��DCR���ܲ�bypasss��
             1��DCR����bypass��
 bit[0]      RXA����BLOCKING DCR����bypass���ơ�
             0��DCR���ܲ�bypasss��
             1��DCR����bypass��
   UNION�ṹ:  ABB_CH1_REG_RX_DCR_CTRL_UNION */
#define ABB_CH1_REG_RX_DCR_CTRL_ADDR                  (ABB_BASE_ADDR + 0x60)

/* �Ĵ���˵����RXAͨ��BLOCKING�ϱ��Ĵ�����
 bit[7:5]    RXA����BLOCKING�ϱ�ֵ,������СN
 bit[4:0]    RXA����BLOCKING�ϱ�ֵ��ϵ����2��M�η�
   UNION�ṹ:  ABB_CH1_RXA_BLOCKING_UNION */
#define ABB_CH1_RXA_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x61)

/* �Ĵ���˵����RXBͨ��BLOCKING�ϱ��Ĵ�����
 bit[7:5]    RXB����BLOCKING�ϱ�ֵ,������СN
 bit[4:0]    RXB����BLOCKING�ϱ�ֵ��ϵ����2��M�η�
   UNION�ṹ:  ABB_CH1_RXB_BLOCKING_UNION */
#define ABB_CH1_RXB_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x62)

/* �Ĵ���˵����RXAͨ��I·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXA����I·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH1_REG_RXA_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x63)

/* �Ĵ���˵����RXAͨ��I·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXA����I·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH1_REG_RXA_DC_I_2_UNION */
#define ABB_CH1_REG_RXA_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x64)

/* �Ĵ���˵����RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH1_REG_RXA_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x65)

/* �Ĵ���˵����RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH1_REG_RXA_DC_Q_2_UNION */
#define ABB_CH1_REG_RXA_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x66)

/* �Ĵ���˵����RXBͨ��I·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXB����I·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH1_REG_RXB_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x67)

/* �Ĵ���˵����RXBͨ��I·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXB����I·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH1_REG_RXB_DC_I_2_UNION */
#define ABB_CH1_REG_RXB_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x68)

/* �Ĵ���˵����RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH1_REG_RXB_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x69)

/* �Ĵ���˵����RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH1_REG_RXB_DC_Q_2_UNION */
#define ABB_CH1_REG_RXB_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x6A)

/* �Ĵ���˵�������ֵ��ԼĴ�����
 bit[7:5]    ����
 bit[4]      Reserved
 bit[3:2]    Reserved
 bit[1]      TXͨ��DEMУ׼����ģʽ
             0����������
             1��У׼̬��DEM���Ϊdem_code_man
 bit[0]      TXͨ��SDMģ���쳣ʱ��λ����
             0��ֻ��λSDMģ��
             1����λ����TXͨ��
   UNION�ṹ:  ABB_CH1_REG_DEBUG_DIG0_UNION */
#define ABB_CH1_REG_DEBUG_DIG0_ADDR                   (ABB_BASE_ADDR + 0x6B)

/* �Ĵ���˵�������ֵ��ԼĴ�����
   ��      ����TXͨ��DEM����ֹ����ã�ֻ��DEMУ׼̬��������,��λ
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_DIG1_ADDR                   (ABB_BASE_ADDR + 0x6C)

/* �Ĵ���˵�������ֵ��ԼĴ�����
   ��      ����TXͨ��DEM����ֹ����ã�ֻ��DEMУ׼̬��������,��λ
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_DIG2_ADDR                   (ABB_BASE_ADDR + 0x6D)

/* �Ĵ���˵�������ֵ��ԼĴ�����
   ��      ����TXͨ��SDMģ���쳣��λ����
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_DIG3_ADDR                   (ABB_BASE_ADDR + 0x6E)

/* �Ĵ���˵�������ֵ��ԼĴ�����
 bit[7]      div_en���Ʒ�Ƶ��bypass�źţ�0��div_en���Ʒ�Ƶ����1��div_en�����Ʒ�Ƶ������Ƶ��ʹ��ʼ��Ϊ1��.
 bit[6]      �л���λbypass�źš�1��ʾ�л���λ������·��
 bit[5]      �л��ſ�ʹ��bypass�źš�1��ʾ�ſ�ʹ�ܹ�����·��
 bit[4]      RXͨ��CIC4/CIC6�˲���ѡ��
             0: ѡ��CIC4�˲���
             1: ѡ��CIC6�˲���
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH1_REG_DEBUG_DIG4_UNION */
#define ABB_CH1_REG_DEBUG_DIG4_ADDR                   (ABB_BASE_ADDR + 0x6F)

/* �Ĵ���˵����Power Down���ƼĴ�����
 bit[7:4]    Reserved
 bit[3]      PLLV1 Power Down����
             0:Power On(Ĭ��)
             1:Power Down
 bit[2]      PLLV2 Power Down����
             0:Power On
             1:Power Down(Ĭ��)
 bit[1]      Reserved
 bit[0]      Reserved
   UNION�ṹ:  ABB_CH1_REG_ANALOG_WR02_UNION */
#define ABB_CH1_REG_ANALOG_WR02_ADDR                  (ABB_BASE_ADDR + 0x70)

/* �Ĵ���˵������ģ�ӿ�ʱ�ӿ��ƼĴ�����
 bit[7]      Reserved
 bit[6]      245M������ƣ�
             0: �����
             1: ���
 bit[5]      CLK_52M Power Down����
             0:Power On
             1:Power Down(Ĭ��)
 bit[4]      CLK_61D44M Power Down����
             0:Power On
             1:Power Down(Ĭ��)
 bit[3]      TX ����ʱ����ѡ��
             0: ����
             1: ����(Ĭ��)
 bit[2:0]    Reserved
   UNION�ṹ:  ABB_CH1_REG_ANALOG_WR03_UNION */
#define ABB_CH1_REG_ANALOG_WR03_ADDR                  (ABB_BASE_ADDR + 0x71)

/* �Ĵ���˵����Other���ƼĴ�����
 bit[7:4]    Reserved
 bit[3]      RX ADC�Զ�tuning����
             0���ֶ�tuning��tuningѡ��RX_TUNE1,RX_TUNE2,RX_TUNE3��ֵ(Ĭ��)
             1���Զ�tuning��RXͨ����calibrationֵΪCAL_VALUE
 bit[2]      TX ADC�Զ�tuning����
             0���ֶ�tuning��tuningѡ��TX_TUNE1,TX_TUNE2,TX_TUNE3��ֵ(Ĭ��)
             1���Զ�tuning��TXͨ����calibrationֵΪCAL_VALUE
 bit[1]      Reserved
 bit[0]      Calibration enable��Ĭ��Ϊ0��
             ����������Calibration����
   UNION�ṹ:  ABB_CH1_REG_ANALOG_WR04_UNION */
#define ABB_CH1_REG_ANALOG_WR04_ADDR                  (ABB_BASE_ADDR + 0x72)

/* �Ĵ���˵����ADC��һ������������tuning�Ĵ�����
 bit[7]      Reserved
 bit[6:0]    ADC��һ������������tuning
   UNION�ṹ:  ABB_CH1_REG_ANALOG_WR05_UNION */
#define ABB_CH1_REG_ANALOG_WR05_ADDR                  (ABB_BASE_ADDR + 0x73)

/* �Ĵ���˵����ADC�ڶ�������������tuning�Ĵ�����
 bit[7]      Reserved
 bit[6:0]    ADC�ڶ�������������tuning
   UNION�ṹ:  ABB_CH1_REG_ANALOG_WR06_UNION */
#define ABB_CH1_REG_ANALOG_WR06_ADDR                  (ABB_BASE_ADDR + 0x74)

/* �Ĵ���˵����ADC����������������tuning�Ĵ�����
 bit[7]      Reserved
 bit[6:0]    ADC����������������tuning
   UNION�ṹ:  ABB_CH1_REG_ANALOG_WR07_UNION */
#define ABB_CH1_REG_ANALOG_WR07_ADDR                  (ABB_BASE_ADDR + 0x75)

/* �Ĵ���˵����DAC Tuning���ƼĴ�����
 bit[7]      Reserved
 bit[6:0]    TX_TUNE1�����ź�
   UNION�ṹ:  ABB_CH1_REG_ANALOG_WR08_UNION */
#define ABB_CH1_REG_ANALOG_WR08_ADDR                  (ABB_BASE_ADDR + 0x76)

/* �Ĵ���˵����DAC Tuning���ƼĴ�����
 bit[7]      Reserved
 bit[6:0]    TX_TUNE2�����ź�
   UNION�ṹ:  ABB_CH1_REG_ANALOG_WR09_UNION */
#define ABB_CH1_REG_ANALOG_WR09_ADDR                  (ABB_BASE_ADDR + 0x77)

/* �Ĵ���˵����DAC Tuning���ƼĴ�����
 bit[7]      Reserved
 bit[6:0]    TX_TUNE3�����ź�
   UNION�ṹ:  ABB_CH1_REG_ANALOG_WR10_UNION */
#define ABB_CH1_REG_ANALOG_WR10_ADDR                  (ABB_BASE_ADDR + 0x78)

/* �Ĵ���˵������ģ��ƽ���ƼĴ�����
 bit[7]      Reserved
 bit[6:5]    Reserved
 bit[4]      Reserved
 bit[3]      Reserved
 bit[2:0]    Reserved
   UNION�ṹ:  ABB_CH1_REG_ANALOG_WR38_UNION */
#define ABB_CH1_REG_ANALOG_WR38_ADDR                  (ABB_BASE_ADDR + 0x79)

/* �Ĵ���˵����DUM���ƼĴ�����
 bit[7]      RX DEM Mode Selection,bit 2
             000: DWA
             001: CLA1
             010: CLA2
             011: CLA3
             100: CLA4
             101: CLA5
             110: CLA6
             111: CLA7
 bit[6:2]    Reserved
 bit[1]      TX I channel  dummy logic control signal
             1: enable(Ĭ��)
             0: disable
 bit[0]      TX Q channel  dummy logic control signal
             1: enable(Ĭ��)
             0: disable
   UNION�ṹ:  ABB_CH1_REG_ANALOG_WR39_UNION */
#define ABB_CH1_REG_ANALOG_WR39_ADDR                  (ABB_BASE_ADDR + 0x7A)

/* �Ĵ���˵������־λֻ���Ĵ�����
 bit[7]      WPLL��LOCK�ź�
 bit[6]      GPLL��LOCK�ź�
 bit[5]      RC Calibration Done�ź�
 bit[4:0]    Reserved
   UNION�ṹ:  ABB_CH1_REG_ANALOG_RO0_UNION */
#define ABB_CH1_REG_ANALOG_RO0_ADDR                   (ABB_BASE_ADDR + 0x7B)

/* �Ĵ���˵����RCУ׼ֻ���Ĵ�����
 bit[7]      Reserved
 bit[6:0]    RC CalibrationУ׼ֵ
   UNION�ṹ:  ABB_CH1_REG_ANALOG_RO1_UNION */
#define ABB_CH1_REG_ANALOG_RO1_ADDR                   (ABB_BASE_ADDR + 0x7C)

/* �Ĵ���˵����Reserved RO�Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_ANALOG_RO2_ADDR                   (ABB_BASE_ADDR + 0x7D)

/* �Ĵ���˵����Reserved RO�Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_ANALOG_RO3_ADDR                   (ABB_BASE_ADDR + 0x7E)

/* �Ĵ���˵����Reserved RO�Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_ANALOG_RO4_ADDR                   (ABB_BASE_ADDR + 0x7F)

/* �Ĵ���˵����ģ����ԼĴ�����
 bit[7:6]    Reserved
 bit[5:4]    PLL��Ƶ����������
             x0����Ƶ������һֱ���Up�ź�
             01: ��Ƶ������һֱ���Down�ź�
             11����Ƶ��������������
 bit[3:1]    ����ʱ��ѡ��
             001��ѡ��������PLL��ʱ����Ϊ����ʱ��
             010��ѡ��������CLKIN_SYSTEM�����ʱ����Ϊ����ʱ��
             100��ѡ��������TCXO_IN��ʱ����Ϊ����ʱ��
 bit[0]      PLL�Ĳο�ʱ��ѡ��
             1: CLKIN_SYSTEM��ΪPLL�Ĳο�ʱ��
             0: TCXO Buffer�����ΪPLL�ο�ʱ��
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA0_UNION */
#define ABB_CH1_REG_DEBUG_ANA0_ADDR                   (ABB_BASE_ADDR + 0x80)

/* �Ĵ���˵����PLL LOCK���ƼĴ�����
 bit[7:6]    Reserved
 bit[5]      WPLL�������ʹ��
             0�����ֹͣ
             1����⿪ʼ
 bit[4]      GPLL�������ʹ��
             0�����ֹͣ
             1����⿪ʼ
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA1_UNION */
#define ABB_CH1_REG_DEBUG_ANA1_ADDR                   (ABB_BASE_ADDR + 0x81)

/* �Ĵ���˵����PLL���ƼĴ�����
 bit[7]      ����ʱ�ӿ���
             1: ����ʱ�Ӵ�
             0: ����ʱ�ӹر�
 bit[6:2]    Reserved
 bit[1:0]    PLL CP PowerDown���ƣ�������
             00����������
             01: PowerDown WPLL CP 
             10: PowerDown GPLL CP 
             11: PowerDown WPLL CP��GPLL CP
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA2_UNION */
#define ABB_CH1_REG_DEBUG_ANA2_ADDR                   (ABB_BASE_ADDR + 0x82)

/* �Ĵ���˵����PLL���ƼĴ�����
 bit[7:4]    GPLL��ɱõ�������(����Ч)
             Basic: 0.25*Icp
             Bit0:  0.25*Icp
             Bit1:  0.25*Icp
             Bit2:  0.5*Icp
             Bit3:  0.5*Icp
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA3_UNION */
#define ABB_CH1_REG_DEBUG_ANA3_ADDR                   (ABB_BASE_ADDR + 0x83)

/* �Ĵ���˵����PLL���ƼĴ�����
 bit[7:4]    WPLL��ɱõ�������(����Ч)
             Basic: 0.25*Icp
             Bit0:  0.25*Icp
             Bit1:  0.25*Icp
             Bit2:  0.5*Icp
             Bit3:  0.5*Icp
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA4_UNION */
#define ABB_CH1_REG_DEBUG_ANA4_ADDR                   (ABB_BASE_ADDR + 0x84)

/* �Ĵ���˵���������������ƼĴ�����
 bit[7]      0 disable
             1 enable
 bit[6:0]    Reserved
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA5_UNION */
#define ABB_CH1_REG_DEBUG_ANA5_ADDR                   (ABB_BASE_ADDR + 0x85)

/* �Ĵ���˵����Bandgap��TCXO���ƼĴ�����
 bit[7]      Sleepģʽʱ�Ƿ񱣳�Bandgap�����Ŀ����źţ�����refgenģ�������PD_BG�źŹ�ͬ����Bandgap��״̬
             0: Bandgap״̬��PD_BG�źſ��ƣ�������Sleepģʽʱ��Bandgap���رգ�����Bandgap����
             1: Bandgapʼ�չ���
 bit[6]      TEST CLK INPUT�µ����
             0: ����
             1: �ر�
 bit[5:4]    TCXO BUFFER��������
             00: 1x
             01: 2x
             10: 3x
             11: 4x
 bit[3:1]    Reserved
 bit[0]      GPLL�ο�Ƶ������
             1: 19.2MHz�ο�ʱ�ӣ�����ģʽ
             0: 26MHz�ο�ʱ�ӣ�����ģʽ
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA6_UNION */
#define ABB_CH1_REG_DEBUG_ANA6_ADDR                   (ABB_BASE_ADDR + 0x86)

/* �Ĵ���˵�����������ƼĴ�����
 bit[7:6]    Reserved
 bit[5:3]    �����ο���������
             000��5u
             001��2u
             010��3u
             011��4u
             100��6u
             101��7u
             110��8u
             111��9u
 bit[2:0]    L/W/G ����ADC ���Buffer�������ڿ���
             000: 1.0x��Ĭ�ϣ�
             001: 0.2x
             010: 0.6x
             011: 0.3x
             100: 0.4x
             101: 0.8x
             110: 1.4x
             111: 1.6x
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA7_UNION */
#define ABB_CH1_REG_DEBUG_ANA7_ADDR                   (ABB_BASE_ADDR + 0x87)

/* �Ĵ���˵�����������ƼĴ�����
 bit[7:5]    Reserved
 bit[4]      ������ģʽѡ��
 bit[3:0]    ����TXͨ��LPF��·��������
             0000��1.0x
             0001��0.9x
             0010��0.8x
             0011��0.7x
             0100��2.0x
             0101��1.8x
             0110��1.6x
             0111��1.4x
             1xxx��Reserved
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA8_UNION */
#define ABB_CH1_REG_DEBUG_ANA8_ADDR                   (ABB_BASE_ADDR + 0x88)

/* �Ĵ���˵����ADC���ƼĴ�����
 bit[7:5]    RX����sub_DAC��������
             000: 1.0x
             001: 0.2x
             010: 0.6x
             011: 0.3x
             100: 0.4x
             101: 0.8x
             110: 1.4x
             111: 1.6x
 bit[4]      LTE ADCģ��Tuning���ѡ��
             0��ѡ��Tuningģ��������ΪLTE ADC��Tuning��
             1��ѡ��Ĵ����������ΪLTE ADC��Tuning��
 bit[3]      LTE ADC DEM���ܹر��ź�
             0��DEMʹ��
             1��DEM��ʹ��
 bit[2]      ���������������ĵ����Ƿ�ɵ�
             0�����ɵ�
             1���ɵ�
 bit[1]      LTE ADCģ������ģʽѡ��
             0���Զ�ģʽ
             1�����üĴ���ģʽ
 bit[0]      RX����sub_DAC Dummy��Ԫ���ƣ���һλ
             0������
             1���ر�
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA9_UNION */
#define ABB_CH1_REG_DEBUG_ANA9_ADDR                   (ABB_BASE_ADDR + 0x89)

/* �Ĵ���˵����ADC��λ���ƼĴ�����
 bit[7]      LTE ADC��DACģ��Powerup����
             0��Powerdown
             1��Powerup
 bit[6]      LTE ADC��OPģ��Powerup����
             0��Powerdown
             1��Powerup
 bit[5]      LTE ADC��CKGENģ��Powerup����
             0��Powerdown
             1��Powerup
 bit[4]      LTE ADC�е��������������ݸ�λ����
             0: ����λ
             1����λ
 bit[3]      LTE ADC�еڶ������������ݸ�λ����
             0������λ
             1����λ
 bit[2]      LTE ADC�е�һ�����������ݸ�λ����
             0������λ
             1����λ
 bit[1:0]    RX����sub_DAC Dummy��Ԫ���ƣ�����λ
             0������
             1���ر�
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA10_UNION */
#define ABB_CH1_REG_DEBUG_ANA10_ADDR                  (ABB_BASE_ADDR + 0x8A)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA11_ADDR                  (ABB_BASE_ADDR + 0x8B)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA12_ADDR                  (ABB_BASE_ADDR + 0x8C)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA13_ADDR                  (ABB_BASE_ADDR + 0x8D)

/* �Ĵ���˵����ADC���ƼĴ�����
 bit[7:6]    LTE SYNCʱ�����
             00��No delay
             01��250ps delay
             10��500ps delay
             11��1000ps delay
 bit[5:3]    LTE ADC ����ƫ�õ���
             000: 1.0x
             001: 0.2x
             010: 0.6x
             011: 0.3x
             100: 0.4x
             101: 0.8x
             110: 1.4x
             111: 1.6x
 bit[2:0]    LTE Overloadģ������
             00��16����������������С��
             01��8����������������С��
             10��4����������������С��
             11���ر�Overload���
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA14_UNION */
#define ABB_CH1_REG_DEBUG_ANA14_ADDR                  (ABB_BASE_ADDR + 0x8E)

/* �Ĵ���˵����ADC�ӳٿ��ƼĴ�����
   ��      ����LTE CLKGENʱ�����
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA15_ADDR                  (ABB_BASE_ADDR + 0x8F)

/* �Ĵ���˵����ADC���ƼĴ�����
 bit[7]      Gģʽ��������
             0��������˷�����
             1��������˷�����
 bit[6]      RX���PDM�������
             0��adder encoder
             1��de-bubble encoder
 bit[5:3]    RX ADC Stage 3��������
             000: 1.0x
             001: 0.2x
             010: 0.6x
             011: 0.3x
             100: 0.4x
             101: 0.8x
             110: 1.4x
             111: 1.6x
 bit[2:0]    RX ADC Stage 12��������
             000: 1.0x
             001: 0.2x
             010: 0.6x
             011: 0.3x
             100: 0.4x
             101: 0.8x
             110: 1.4x
             111: 1.6x
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA16_UNION */
#define ABB_CH1_REG_DEBUG_ANA16_ADDR                  (ABB_BASE_ADDR + 0x90)

/* �Ĵ���˵����PLL���ԼĴ�����
 bit[7:6]    PLL���Ƶ�ѹ����PAD�ź�ѡ��
             00�����Ƶ�ѹ����PAD����
             01��WPLL������Ƶ�ѹ��PAD
             10��GPLL������Ƶ�ѹ��PAD
 bit[5:4]    PLLʱ�Ӳ���PAD�ź�ѡ��
             00��ʱ�Ӳ���PAD����
             01��WPLL���ʱ�ӵ�PAD
             10��GPLL���ʱ�ӵ�PAD
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA17_UNION */
#define ABB_CH1_REG_DEBUG_ANA17_ADDR                  (ABB_BASE_ADDR + 0x91)

/* �Ĵ���˵����TX�ֹ���Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA18_ADDR                  (ABB_BASE_ADDR + 0x92)

/* �Ĵ���˵����ʱ�ӷ��ؿ��ƼĴ�����
 bit[7:6]    Reserved
 bit[5]      PLLģ��307.2MHzʱ��ʹ���ź�
             0��ʱ�ӹر�
             1��ʱ��ʹ��
 bit[4]      PLLģ��307.2MHzʱ��ʹ���ź�
             0��ʱ�ӹر�
             1��ʱ��ʹ��
 bit[3]      PLLģ��153.6MHzʱ��ʹ���ź�
             0��ʱ�ӹر�
             1��ʱ��ʹ��
 bit[2]      HKADC��Tuningģ��ʱ��ʹ���ź�
             0��ʱ�ӹر�
             1��ʱ��ʹ��
 bit[1:0]    ���Թܽ����ʱ��Ƶ�ʿ���
             00: ������ʱ��
             01��WPLL�������
             10��GPLL�������
             11��WPLL��GPLL�������
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA19_UNION */
#define ABB_CH1_REG_DEBUG_ANA19_ADDR                  (ABB_BASE_ADDR + 0x93)

/* �Ĵ���˵����ģ����ԼĴ�����
 bit[7]      Tuning��·����ѡ��
             0: �����
             1: С����
 bit[6:5]    ���������������ݵ���
 bit[4]      �ⲿBandGapʹ���ź�
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_CH1_REG_DEBUG_ANA20_UNION */
#define ABB_CH1_REG_DEBUG_ANA20_ADDR                  (ABB_BASE_ADDR + 0x94)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA21_ADDR                  (ABB_BASE_ADDR + 0x95)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA22_ADDR                  (ABB_BASE_ADDR + 0x96)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA23_ADDR                  (ABB_BASE_ADDR + 0x97)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA24_ADDR                  (ABB_BASE_ADDR + 0x98)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA25_ADDR                  (ABB_BASE_ADDR + 0x99)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA26_ADDR                  (ABB_BASE_ADDR + 0x9A)

/* �Ĵ���˵����ģ�����ֻ���Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ARO0_ADDR                   (ABB_BASE_ADDR + 0x9B)

/* �Ĵ���˵����2gģʽRX��·ʱ���ӳٵ�����
 bit[7:6]    ����
 bit[5]      rx_clk���delay bypass���أ�
             1'b0��rx_clk ���delay ��bypass
             1'b1��rx_clk ���delay bypass
 bit[4]      rx_clk���������ƣ�
             1'b0��rx_clk bypass���
             1'b1��rx_clk�������
 bit[3:0]    RX_MCLKʱ����ʱѡ��
                 2G(ns) 3G(ns) 4G(ns)
             0 : 12.8  3.3  1.6 
             1 : 25.6  6.5  3.3 
             2 : 38.5  9.8  4.9 
             3 : 51.3  13.0  6.5 
             4 : 64.1  16.3  8.1 
             5 : 76.9  19.5  9.8 
             6 : 89.7  22.8  11.4 
             7 : 102.6  26.0  13.0 
             8 : 115.4  29.3  14.6 
             9 : 128.2  32.6  16.3 
             10 : 141.0  35.8  17.9 
             11 : 153.8  39.1  19.5 
             12 : 166.7  42.3  21.2 
             13 : 179.5  45.6  22.8 
             14 : 192.3  48.8  24.4 
             15 : 205.1  52.1  26.0 
             
   UNION�ṹ:  ABB_CH1_2G_RX_DELAY_UNION */
#define ABB_CH1_2G_RX_DELAY_ADDR                      (ABB_BASE_ADDR + 0x9C)

/* �Ĵ���˵����3gģʽRX��·ʱ���ӳٵ�����
 bit[7:6]    ����
 bit[5]      rx_clk���delay bypass���أ�
             1'b0��rx_clk ���delay ��bypass
             1'b1��rx_clk ���delay bypass
 bit[4]      rx_clk���������ƣ�
             1'b0��rx_clk bypass���
             1'b1��rx_clk�������
 bit[3:0]    RX_MCLKʱ����ʱѡ��
                 2G(ns) 3G(ns) 4G(ns)
             0 : 12.8  3.3  1.6 
             1 : 25.6  6.5  3.3 
             2 : 38.5  9.8  4.9 
             3 : 51.3  13.0  6.5 
             4 : 64.1  16.3  8.1 
             5 : 76.9  19.5  9.8 
             6 : 89.7  22.8  11.4 
             7 : 102.6  26.0  13.0 
             8 : 115.4  29.3  14.6 
             9 : 128.2  32.6  16.3 
             10 : 141.0  35.8  17.9 
             11 : 153.8  39.1  19.5 
             12 : 166.7  42.3  21.2 
             13 : 179.5  45.6  22.8 
             14 : 192.3  48.8  24.4 
             15 : 205.1  52.1  26.0 
             
   UNION�ṹ:  ABB_CH1_3G_RX_DELAY_UNION */
#define ABB_CH1_3G_RX_DELAY_ADDR                      (ABB_BASE_ADDR + 0x9D)

/* �Ĵ���˵����4gģʽRX��·ʱ���ӳٵ�����
 bit[7:6]    ����
 bit[5]      rx_clk���delay bypass���أ�
             1'b0��rx_clk ���delay ��bypass
             1'b1��rx_clk ���delay bypass
 bit[4]      rx_clk���������ƣ�
             1'b0��rx_clk bypass���
             1'b1��rx_clk�������
 bit[3:0]    RX_MCLKʱ����ʱѡ��
                 2G(ns) 3G(ns) 4G(ns)
             0 : 12.8  3.3  1.6 
             1 : 25.6  6.5  3.3 
             2 : 38.5  9.8  4.9 
             3 : 51.3  13.0  6.5 
             4 : 64.1  16.3  8.1 
             5 : 76.9  19.5  9.8 
             6 : 89.7  22.8  11.4 
             7 : 102.6  26.0  13.0 
             8 : 115.4  29.3  14.6 
             9 : 128.2  32.6  16.3 
             10 : 141.0  35.8  17.9 
             11 : 153.8  39.1  19.5 
             12 : 166.7  42.3  21.2 
             13 : 179.5  45.6  22.8 
             14 : 192.3  48.8  24.4 
             15 : 205.1  52.1  26.0 
             
   UNION�ṹ:  ABB_CH1_4G_RX_DELAY_UNION */
#define ABB_CH1_4G_RX_DELAY_ADDR                      (ABB_BASE_ADDR + 0x9E)

/* �Ĵ���˵����version�Ĵ�����
   ��      ������ģ�ⲿ�־����汾�Ĵ���ֵ
   UNION�ṹ ���� */
#define ABB_CH0_VERSION_ADDR                          (ABB_BASE_ADDR + 0xA0)

/* �Ĵ���˵��������ģʽ�Ĵ�����
 bit[7]      ����
 bit[6]      ���õ���λ�źţ�
             0�������������λ(Ĭ��)
             1�����������λ
 bit[5:3]    bit[4:3]����ģʽ���ƣ�
             00������ģʽ(Ĭ��)
             01�������㷨�߼�����ģʽ
             10��RXģ�����ģʽ(bypass RX�����˲���)
             11�����ֽӿڻ���ģʽ
             bit[5]��reserved
 bit[2:1]    RXģ�����ģʽ��ͨ��ѡ��
             00�����RXA Iģ�����������(Ĭ��)
             01�����RXA Qģ�����������
             10�����RXB Iģ�����������
             11�����RXB Qģ�����������
 bit[0]      ����
   UNION�ṹ:  ABB_CH0_TESTMODE_UNION */
#define ABB_CH0_TESTMODE_ADDR                         (ABB_BASE_ADDR + 0xA1)

/* �Ĵ���˵����ͨ�����ƼĴ�����
 bit[7:1]    ����
 bit[0]      ET/APTͨ��ѡ��
             0��ѡ��TXͨ��I·��ET/APT
             1��ѡ��TXͨ��Q·��ET/APT
   UNION�ṹ:  ABB_CH0_CTRL_UNION */
#define ABB_CH0_CTRL_ADDR                             (ABB_BASE_ADDR + 0xA2)

/* �Ĵ���˵����CFR��ֵ��ⴰ���Ĵ�����
 bit[7:4]    CFR��������
 bit[3]      ����
 bit[2]      CFR�˲���ѡ��
             0��bypass�˲���
             1����bypass�˲���
 bit[1:0]    CFR��ֵ��ⷽʽ��
             00���������
             01���������
             10���������
             11��ȫ����ֵ
   UNION�ṹ:  ABB_CH0_CFR_CTRL_UNION */
#define ABB_CH0_CFR_CTRL_ADDR                         (ABB_BASE_ADDR + 0xA3)

/* �Ĵ���˵�����߿�ѡ��
 bit[7]      ѡ��RXA_EN�߿أ�0: tie to 0(Ĭ�ϣ�
             1: from line control
 bit[6]      ѡ��RXB_EN�߿أ�0: tie to 0(Ĭ�ϣ�
             1: from line control
 bit[5]      ѡ��TX_EN�߿أ�0: tie to 0(Ĭ�ϣ�
             1: from line control
 bit[4]      ѡ��ET�߿�ģʽ��0: tie to 0(Ĭ�ϣ�
             1: from line control
 bit[3]      ѡ��APT�߿�ģʽ��0: tie to 0(Ĭ�ϣ�
             1: from line control
 bit[2]      ѡ��4G�߿�ģʽ��0: tie to 0(Ĭ�ϣ�
             1: from line control
 bit[1]      ѡ��3G�߿�ģʽ��0: tie to 0(Ĭ�ϣ�
             1: from line control
 bit[0]      ѡ��2G�߿�ģʽ��0: tie to 0(Ĭ�ϣ�
             1: from line control
   UNION�ṹ:  ABB_CH0_LINE_CTRL_SEL_UNION */
#define ABB_CH0_LINE_CTRL_SEL_ADDR                    (ABB_BASE_ADDR + 0xA4)

/* �Ĵ���˵����RX���ֹ���ģʽ�ϱ��Ĵ�����
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G
             001��3G_SC
             010��4G
             011��3G_DC
             Others��reserved
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G,   3G_SC,    4G,   3G_DC,      
             00�� 2.167M,15.36M, 61.44M,30.72M
             01�� 4.33MHz,------,30.72M,------
             10�� ------, ------,15.36M,------
             11�� ------, ------, 7.68M,------
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      Reserved
   UNION�ṹ:  ABB_CH0_RX_DIG_RPT_UNION */
#define ABB_CH0_RX_DIG_RPT_ADDR                       (ABB_BASE_ADDR + 0xA5)

/* �Ĵ���˵����TX���ֹ���ģʽ�ϱ��Ĵ�����
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G
             001��3G
             010��4G &amp; ET &amp; APT
             Others��reserved
 bit[4:2]    TXͨ��CIC�˲���������ʿ��ƣ�
                  2G,     3G,     4G,     
                 (78M) (153.6M) (307.2M) 
             0��4.33MHz,30.72MHz,61.44MHz
             1��2.16MHz,15.36MHz,30.72MHz
             2��-------,--------,15.36MHz
             3��-------,--------, 7.68MHz
             4��-------,--------, 3.84MHz
             Others��Reserved
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass
             1��bypass
   UNION�ṹ:  ABB_CH0_TX_DIG_RPT_UNION */
#define ABB_CH0_TX_DIG_RPT_ADDR                       (ABB_BASE_ADDR + 0xA6)

/* �Ĵ���˵����TXͨ��offset�Ĵ�����
   ��      ����TXͨ��I·dc offset����
   UNION�ṹ ���� */
#define ABB_CH0_TX_I_OFFSET_ADDR                      (ABB_BASE_ADDR + 0xA8)

/* �Ĵ���˵����TXͨ��offset�Ĵ�����
   ��      ����TXͨ��Q·dc offset����
   UNION�ṹ ���� */
#define ABB_CH0_TX_Q_OFFSET_ADDR                      (ABB_BASE_ADDR + 0xA9)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0xAA)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXAͨ��I·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXAͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH0_RXA_I_COEF1_UNION */
#define ABB_CH0_RXA_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0xAB)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0xAC)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXAͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH0_RXA_I_COEF3_UNION */
#define ABB_CH0_RXA_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0xAD)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0xAE)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��Q·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0xAF)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXAͨ��Q·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXAͨ��Q·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH0_RXA_Q_COEF1_UNION */
#define ABB_CH0_RXA_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0xB0)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��Q·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0xB1)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXAͨ��Q·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH0_RXA_Q_COEF3_UNION */
#define ABB_CH0_RXA_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0xB2)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��Q·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0xB3)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0xB4)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXBͨ��I·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXBͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH0_RXB_I_COEF1_UNION */
#define ABB_CH0_RXB_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0xB5)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0xB6)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXBͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH0_RXB_I_COEF3_UNION */
#define ABB_CH0_RXB_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0xB7)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0xB8)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��Q·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0xB9)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXBͨ��Q·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXBͨ��Q·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH0_RXB_Q_COEF1_UNION */
#define ABB_CH0_RXB_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0xBA)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��Q·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0xBB)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXBͨ��Q·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH0_RXB_Q_COEF3_UNION */
#define ABB_CH0_RXB_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0xBC)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��Q·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0xBD)

/* �Ĵ���˵����RXAͨ��BLOCKING DCR���üĴ�����
 bit[7:5]    RXA����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ��
 bit[4:0]    RXA����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣
   UNION�ṹ:  ABB_CH0_REG_RXA_DCR_CFG_UNION */
#define ABB_CH0_REG_RXA_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0xBE)

/* �Ĵ���˵����RXBͨ��BLOCKING DCR���üĴ�����
 bit[7:5]    RXB����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ��
 bit[4:0]    RXB����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣
   UNION�ṹ:  ABB_CH0_REG_RXB_DCR_CFG_UNION */
#define ABB_CH0_REG_RXB_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0xBF)

/* �Ĵ���˵����BLOCKING DCR���ܿ��ƼĴ�����
 bit[7:2]    ����
 bit[1]      RXB����BLOCKING DCR����bypass���ơ�
             0��DCR���ܲ�bypasss��
             1��DCR����bypass��
 bit[0]      RXA����BLOCKING DCR����bypass���ơ�
             0��DCR���ܲ�bypasss��
             1��DCR����bypass��
   UNION�ṹ:  ABB_CH0_REG_RX_DCR_CTRL_UNION */
#define ABB_CH0_REG_RX_DCR_CTRL_ADDR                  (ABB_BASE_ADDR + 0xC0)

/* �Ĵ���˵����RXAͨ��BLOCKING�ϱ��Ĵ�����
 bit[7:5]    RXA����BLOCKING�ϱ�ֵ,������СN
 bit[4:0]    RXA����BLOCKING�ϱ�ֵ��ϵ����2��M�η�
   UNION�ṹ:  ABB_CH0_RXA_BLOCKING_UNION */
#define ABB_CH0_RXA_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0xC1)

/* �Ĵ���˵����RXBͨ��BLOCKING�ϱ��Ĵ�����
 bit[7:5]    RXB����BLOCKING�ϱ�ֵ,������СN
 bit[4:0]    RXB����BLOCKING�ϱ�ֵ��ϵ����2��M�η�
   UNION�ṹ:  ABB_CH0_RXB_BLOCKING_UNION */
#define ABB_CH0_RXB_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0xC2)

/* �Ĵ���˵����RXAͨ��I·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXA����I·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH0_REG_RXA_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0xC3)

/* �Ĵ���˵����RXAͨ��I·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXA����I·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH0_REG_RXA_DC_I_2_UNION */
#define ABB_CH0_REG_RXA_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0xC4)

/* �Ĵ���˵����RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH0_REG_RXA_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0xC5)

/* �Ĵ���˵����RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH0_REG_RXA_DC_Q_2_UNION */
#define ABB_CH0_REG_RXA_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0xC6)

/* �Ĵ���˵����RXBͨ��I·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXB����I·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH0_REG_RXB_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0xC7)

/* �Ĵ���˵����RXBͨ��I·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXB����I·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH0_REG_RXB_DC_I_2_UNION */
#define ABB_CH0_REG_RXB_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0xC8)

/* �Ĵ���˵����RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH0_REG_RXB_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0xC9)

/* �Ĵ���˵����RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH0_REG_RXB_DC_Q_2_UNION */
#define ABB_CH0_REG_RXB_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0xCA)

/* �Ĵ���˵�������ֵ��ԼĴ�����
 bit[7:5]    ����
 bit[4]      Reserved
 bit[3:2]    Reserved
 bit[1]      TXͨ��DEMУ׼����ģʽ
             0����������
             1��У׼̬��DEM���Ϊdem_code_man
 bit[0]      TXͨ��SDMģ���쳣ʱ��λ����
             0��ֻ��λSDMģ��
             1����λ����TXͨ��
   UNION�ṹ:  ABB_CH0_REG_DEBUG_DIG0_UNION */
#define ABB_CH0_REG_DEBUG_DIG0_ADDR                   (ABB_BASE_ADDR + 0xCB)

/* �Ĵ���˵�������ֵ��ԼĴ�����
   ��      ����TXͨ��DEM����ֹ����ã�ֻ��DEMУ׼̬��������,��λ
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_DIG1_ADDR                   (ABB_BASE_ADDR + 0xCC)

/* �Ĵ���˵�������ֵ��ԼĴ�����
   ��      ����TXͨ��DEM����ֹ����ã�ֻ��DEMУ׼̬��������,��λ
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_DIG2_ADDR                   (ABB_BASE_ADDR + 0xCD)

/* �Ĵ���˵�������ֵ��ԼĴ�����
   ��      ����TXͨ��SDMģ���쳣��λ����
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_DIG3_ADDR                   (ABB_BASE_ADDR + 0xCE)

/* �Ĵ���˵�������ֵ��ԼĴ�����
 bit[7]      div_en���Ʒ�Ƶ��bypass�źţ�0��div_en���Ʒ�Ƶ����1��div_en�����Ʒ�Ƶ������Ƶ��ʹ��ʼ��Ϊ1��.
 bit[6]      �л���λbypass�źš�1��ʾ�л���λ������·��
 bit[5]      �л��ſ�ʹ��bypass�źš�1��ʾ�ſ�ʹ�ܹ�����·��
 bit[4]      RXͨ��CIC4/CIC6�˲���ѡ��
             0: ѡ��CIC4�˲���
             1: ѡ��CIC6�˲���
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH0_REG_DEBUG_DIG4_UNION */
#define ABB_CH0_REG_DEBUG_DIG4_ADDR                   (ABB_BASE_ADDR + 0xCF)

/* �Ĵ���˵����Power Down���ƼĴ�����
 bit[7:4]    Reserved
 bit[3]      WPLL Power Down����
             0:Power On(Ĭ��)
             1:Power Down
 bit[2]      GPLL Power Down����
             0:Power On
             1:Power Down(Ĭ��)
 bit[1]      Reserved
 bit[0]      Reserved
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR02_UNION */
#define ABB_CH0_REG_ANALOG_WR02_ADDR                  (ABB_BASE_ADDR + 0xD0)

/* �Ĵ���˵������ģ�ӿ�ʱ�ӿ��ƼĴ�����
 bit[7]      Reserved
 bit[6]      245M������ƣ�
             0: �����
             1: ���
 bit[5]      CLK_52M Power Down����
             0:Power On
             1:Power Down(Ĭ��)
 bit[4]      CLK_61D44M Power Down����
             0:Power On
             1:Power Down(Ĭ��)
 bit[3]      TX ����ʱ����ѡ��
             0: ����
             1: ����(Ĭ��)
 bit[2:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR03_UNION */
#define ABB_CH0_REG_ANALOG_WR03_ADDR                  (ABB_BASE_ADDR + 0xD1)

/* �Ĵ���˵����Other���ƼĴ�����
 bit[7:4]    Reserved
 bit[3]      RX ADC�Զ�tuning����
             0���ֶ�tuning��tuningѡ��RX_TUNE1,RX_TUNE2,RX_TUNE3��ֵ(Ĭ��)
             1���Զ�tuning��RXͨ����calibrationֵΪCAL_VALUE
 bit[2]      TX ADC�Զ�tuning����
             0���ֶ�tuning��tuningѡ��TX_TUNE1,TX_TUNE2,TX_TUNE3��ֵ(Ĭ��)
             1���Զ�tuning��TXͨ����calibrationֵΪCAL_VALUE
 bit[1]      Reserved
 bit[0]      Calibration enable��Ĭ��Ϊ0��
             ����������Calibration����
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR04_UNION */
#define ABB_CH0_REG_ANALOG_WR04_ADDR                  (ABB_BASE_ADDR + 0xD2)

/* �Ĵ���˵����ADC��һ������������tuning�Ĵ�����
 bit[7]      Reserved
 bit[6:0]    ADC��һ������������tuning
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR05_UNION */
#define ABB_CH0_REG_ANALOG_WR05_ADDR                  (ABB_BASE_ADDR + 0xD3)

/* �Ĵ���˵����ADC�ڶ�������������tuning�Ĵ�����
 bit[7]      Reserved
 bit[6:0]    ADC�ڶ�������������tuning
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR06_UNION */
#define ABB_CH0_REG_ANALOG_WR06_ADDR                  (ABB_BASE_ADDR + 0xD4)

/* �Ĵ���˵����ADC����������������tuning�Ĵ�����
 bit[7]      Reserved
 bit[6:0]    ADC����������������tuning
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR07_UNION */
#define ABB_CH0_REG_ANALOG_WR07_ADDR                  (ABB_BASE_ADDR + 0xD5)

/* �Ĵ���˵����DAC Tuning���ƼĴ�����
 bit[7]      Reserved
 bit[6:0]    TX_TUNE1�����ź�
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR08_UNION */
#define ABB_CH0_REG_ANALOG_WR08_ADDR                  (ABB_BASE_ADDR + 0xD6)

/* �Ĵ���˵����DAC Tuning���ƼĴ�����
 bit[7]      Reserved
 bit[6:0]    TX_TUNE2�����ź�
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR09_UNION */
#define ABB_CH0_REG_ANALOG_WR09_ADDR                  (ABB_BASE_ADDR + 0xD7)

/* �Ĵ���˵����DAC Tuning���ƼĴ�����
 bit[7]      Reserved
 bit[6:0]    TX_TUNE3�����ź�
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR10_UNION */
#define ABB_CH0_REG_ANALOG_WR10_ADDR                  (ABB_BASE_ADDR + 0xD8)

/* �Ĵ���˵������ģ��ƽ���ƼĴ�����
 bit[7]      Reserved
 bit[6:5]    Reserved
 bit[4]      Reserved
 bit[3]      Reserved
 bit[2:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR38_UNION */
#define ABB_CH0_REG_ANALOG_WR38_ADDR                  (ABB_BASE_ADDR + 0xD9)

/* �Ĵ���˵����DUM���ƼĴ�����
 bit[7:5]    RX DEM Mode Selection,bit 2
             000: DWA
             001: CLA1
             010: CLA2
             011: CLA3
             100: CLA4
             101: CLA5
             110: CLA6
             111: CLA7
 bit[4:2]    Reserved
 bit[1]      TX I channel  dummy logic control signal
             1: enable(Ĭ��)
             0: disable
 bit[0]      TX Q channel  dummy logic control signal
             1: enable(Ĭ��)
             0: disable
   UNION�ṹ:  ABB_CH0_REG_ANALOG_WR39_UNION */
#define ABB_CH0_REG_ANALOG_WR39_ADDR                  (ABB_BASE_ADDR + 0xDA)

/* �Ĵ���˵������־λֻ���Ĵ�����
 bit[7]      WPLL��LOCK�ź�
 bit[6]      GPLL��LOCK�ź�
 bit[5]      RC Calibration Done�ź�
 bit[4:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_ANALOG_RO0_UNION */
#define ABB_CH0_REG_ANALOG_RO0_ADDR                   (ABB_BASE_ADDR + 0xDB)

/* �Ĵ���˵����RCУ׼ֻ���Ĵ�����
 bit[7]      Reserved
 bit[6:0]    RC CalibrationУ׼ֵ
   UNION�ṹ:  ABB_CH0_REG_ANALOG_RO1_UNION */
#define ABB_CH0_REG_ANALOG_RO1_ADDR                   (ABB_BASE_ADDR + 0xDC)

/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH0_REG_ANALOG_RO2_ADDR                   (ABB_BASE_ADDR + 0xDD)

/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH0_REG_ANALOG_RO3_ADDR                   (ABB_BASE_ADDR + 0xDE)

/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH0_REG_ANALOG_RO4_ADDR                   (ABB_BASE_ADDR + 0xDF)

/* �Ĵ���˵����ģ����ԼĴ�����
 bit[7:6]    Reserved
 bit[5:4]    PLL��Ƶ����������
             x0����Ƶ������һֱ���Up�ź�
             01: ��Ƶ������һֱ���Down�ź�
             11����Ƶ��������������
 bit[3:1]    ����ʱ��ѡ��
             001��ѡ��������PLL��ʱ����Ϊ����ʱ��
             010��ѡ��������CLKIN_SYSTEM�����ʱ����Ϊ����ʱ��
             100��ѡ��������TCXO_IN��ʱ����Ϊ����ʱ��
 bit[0]      PLL�Ĳο�ʱ��ѡ��
             1: CLKIN_SYSTEM��ΪPLL�Ĳο�ʱ��
             0: TCXO Buffer�����ΪPLL�ο�ʱ��
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA0_UNION */
#define ABB_CH0_REG_DEBUG_ANA0_ADDR                   (ABB_BASE_ADDR + 0xE0)

/* �Ĵ���˵����PLL LOCK���ƼĴ�����
 bit[7:6]    Reserved
 bit[5]      WPLL�������ʹ��
             0�����ֹͣ
             1����⿪ʼ
 bit[4]      GPLL�������ʹ��
             0�����ֹͣ
             1����⿪ʼ
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA1_UNION */
#define ABB_CH0_REG_DEBUG_ANA1_ADDR                   (ABB_BASE_ADDR + 0xE1)

/* �Ĵ���˵����PLL���ƼĴ�����
 bit[7]      ����ʱ�ӿ���
             1: ����ʱ�Ӵ�
             0: ����ʱ�ӹر�
 bit[6:2]    Reserved
 bit[1:0]    PLL CP PowerDown���ƣ�������
             00����������
             01: PowerDown WPLL CP 
             10: PowerDown GPLL CP 
             11: PowerDown WPLL CP��GPLL CP
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA2_UNION */
#define ABB_CH0_REG_DEBUG_ANA2_ADDR                   (ABB_BASE_ADDR + 0xE2)

/* �Ĵ���˵����PLL���ƼĴ�����
 bit[7:4]    GPLL��ɱõ�������(����Ч)
             Basic: 0.25*Icp
             Bit0:  0.25*Icp
             Bit1:  0.25*Icp
             Bit2:  0.5*Icp
             Bit3:  0.5*Icp
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA3_UNION */
#define ABB_CH0_REG_DEBUG_ANA3_ADDR                   (ABB_BASE_ADDR + 0xE3)

/* �Ĵ���˵����PLL���ƼĴ�����
 bit[7:4]    WPLL��ɱõ�������(����Ч)
             Basic: 0.25*Icp
             Bit0:  0.25*Icp
             Bit1:  0.25*Icp
             Bit2:  0.5*Icp
             Bit3:  0.5*Icp
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA4_UNION */
#define ABB_CH0_REG_DEBUG_ANA4_ADDR                   (ABB_BASE_ADDR + 0xE4)

/* �Ĵ���˵���������������ƼĴ�����
 bit[7]      0 disable
             1 enable
 bit[6:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA5_UNION */
#define ABB_CH0_REG_DEBUG_ANA5_ADDR                   (ABB_BASE_ADDR + 0xE5)

/* �Ĵ���˵����Bandgap��TCXO���ƼĴ�����
 bit[7]      Sleepģʽʱ�Ƿ񱣳�Bandgap�����Ŀ����źţ�����refgenģ�������PD_BG�źŹ�ͬ����Bandgap��״̬
             0: Bandgap״̬��PD_BG�źſ��ƣ�������Sleepģʽʱ��Bandgap���رգ�����Bandgap����
             1: Bandgapʼ�չ���
 bit[6]      TEST CLK INPUT�µ����
             0: ����
             1: �ر�
 bit[5:4]    TCXO BUFFER��������
             00: 1x
             01: 2x
             10: 3x
             11: 4x
 bit[3:1]    Reserved
 bit[0]      GPLL�ο�Ƶ������
             1: 19.2MHz�ο�ʱ�ӣ�����ģʽ
             0: 26MHz�ο�ʱ�ӣ�����ģʽ
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA6_UNION */
#define ABB_CH0_REG_DEBUG_ANA6_ADDR                   (ABB_BASE_ADDR + 0xE6)

/* �Ĵ���˵�����������ƼĴ�����
 bit[7:6]    Reserved
 bit[5:3]    �����ο���������
             000��5u
             001��2u
             010��3u
             011��4u
             100��6u
             101��7u
             110��8u
             111��9u
 bit[2:0]    L/W/G ����ADC ���Buffer�������ڿ���
             000: 1.0x��Ĭ�ϣ�
             001: 0.2x
             010: 0.6x
             011: 0.3x
             100: 0.4x
             101: 0.8x
             110: 1.4x
             111: 1.6x
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA7_UNION */
#define ABB_CH0_REG_DEBUG_ANA7_ADDR                   (ABB_BASE_ADDR + 0xE7)

/* �Ĵ���˵�����������ƼĴ�����
 bit[7:5]    Reserved
 bit[4]      ������ģʽѡ��
 bit[3:0]    ����TXͨ��LPF��·��������
             0000��1.0x
             0001��0.9x
             0010��0.8x
             0011��0.7x
             0100��2.0x
             0101��1.8x
             0110��1.6x
             0111��1.4x
             1xxx��Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA8_UNION */
#define ABB_CH0_REG_DEBUG_ANA8_ADDR                   (ABB_BASE_ADDR + 0xE8)

/* �Ĵ���˵����ADC���ƼĴ�����
 bit[7:5]    RX����sub_DAC��������
             000: 1.0x
             001: 0.2x
             010: 0.6x
             011: 0.3x
             100: 0.4x
             101: 0.8x
             110: 1.4x
             111: 1.6x
 bit[4]      LTE ADCģ��Tuning���ѡ��
             0��ѡ��Tuningģ��������ΪLTE ADC��Tuning��
             1��ѡ��Ĵ����������ΪLTE ADC��Tuning��
 bit[3]      LTE ADC DEM���ܹر��ź�
             0��DEMʹ��
             1��DEM��ʹ��
 bit[2]      ���������������ĵ����Ƿ�ɵ�
             0�����ɵ�
             1���ɵ�
 bit[1]      LTE ADCģ������ģʽѡ��
             0���Զ�ģʽ
             1�����üĴ���ģʽ
 bit[0]      RX����sub_DAC Dummy��Ԫ���ƣ���һλ
             0������
             1���ر�
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA9_UNION */
#define ABB_CH0_REG_DEBUG_ANA9_ADDR                   (ABB_BASE_ADDR + 0xE9)

/* �Ĵ���˵����ADC��λ���ƼĴ�����
 bit[7]      LTE ADC��DACģ��Powerup����
             0��Powerdown
             1��Powerup
 bit[6]      LTE ADC��OPģ��Powerup����
             0��Powerdown
             1��Powerup
 bit[5]      LTE ADC��CKGENģ��Powerup����
             0��Powerdown
             1��Powerup
 bit[4]      LTE ADC�е��������������ݸ�λ����
             0: ����λ
             1����λ
 bit[3]      LTE ADC�еڶ������������ݸ�λ����
             0������λ
             1����λ
 bit[2]      LTE ADC�е�һ�����������ݸ�λ����
             0������λ
             1����λ
 bit[1:0]    RX����sub_DAC Dummy��Ԫ���ƣ�����λ
             0������
             1���ر�
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA10_UNION */
#define ABB_CH0_REG_DEBUG_ANA10_ADDR                  (ABB_BASE_ADDR + 0xEA)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA11_ADDR                  (ABB_BASE_ADDR + 0xEB)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA12_ADDR                  (ABB_BASE_ADDR + 0xEC)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA13_ADDR                  (ABB_BASE_ADDR + 0xED)

/* �Ĵ���˵����ADC���ƼĴ�����
 bit[7:6]    LTE SYNCʱ�����
             00��No delay
             01��250ps delay
             10��500ps delay
             11��1000ps delay
 bit[5:3]    ����������ƫ�õ���
             000: 1.0x
             001: 0.2x
             010: 0.6x
             011: 0.3x
             100: 0.4x
             101: 0.8x
             110: 1.4x
             111: 1.6x
 bit[2:0]    LTE Overloadģ������
             00��16����������������С��
             01��8����������������С��
             10��4����������������С��
             11���ر�Overload���
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA14_UNION */
#define ABB_CH0_REG_DEBUG_ANA14_ADDR                  (ABB_BASE_ADDR + 0xEE)

/* �Ĵ���˵����ADC�ӳٿ��ƼĴ�����
   ��      ����LTE CLKGENʱ�����
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA15_ADDR                  (ABB_BASE_ADDR + 0xEF)

/* �Ĵ���˵����ADC���ƼĴ�����
 bit[7]      Gģʽ��������
             0��������˷�����
             1��������˷�����
 bit[6]      RX���PDM�������
             0��adder encoder
             1��de-bubble encoder
 bit[5:3]    RX ADC Stage 3��������
             000: 1.0x
             001: 0.2x
             010: 0.6x
             011: 0.3x
             100: 0.4x
             101: 0.8x
             110: 1.4x
             111: 1.6x
 bit[2:0]    RX ADC Stage 12��������
             000: 1.0x
             001: 0.2x
             010: 0.6x
             011: 0.3x
             100: 0.4x
             101: 0.8x
             110: 1.4x
             111: 1.6x
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA16_UNION */
#define ABB_CH0_REG_DEBUG_ANA16_ADDR                  (ABB_BASE_ADDR + 0xF0)

/* �Ĵ���˵����PLL���ԼĴ�����
 bit[7:6]    PLL���Ƶ�ѹ����PAD�ź�ѡ��
             00�����Ƶ�ѹ����PAD����
             01��WPLL������Ƶ�ѹ��PAD
             10��GPLL������Ƶ�ѹ��PAD
 bit[5:4]    PLLʱ�Ӳ���PAD�ź�ѡ��
             00��ʱ�Ӳ���PAD����
             01��WPLL���ʱ�ӵ�PAD
             10��GPLL���ʱ�ӵ�PAD
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA17_UNION */
#define ABB_CH0_REG_DEBUG_ANA17_ADDR                  (ABB_BASE_ADDR + 0xF1)

/* �Ĵ���˵����TX�ֹ���Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA18_ADDR                  (ABB_BASE_ADDR + 0xF2)

/* �Ĵ���˵����ʱ�ӷ��ؿ��ƼĴ�����
 bit[7:6]    Reserved
 bit[5]      PLLģ��307.2MHzʱ��ʹ���ź�
             0��ʱ�ӹر�
             1��ʱ��ʹ��
 bit[4]      PLLģ��307.2MHzʱ��ʹ���ź�
             0��ʱ�ӹر�
             1��ʱ��ʹ��
 bit[3]      PLLģ��153.6MHzʱ��ʹ���ź�
             0��ʱ�ӹر�
             1��ʱ��ʹ��
 bit[2]      HKADC��Tuningģ��ʱ��ʹ���ź�
             0��ʱ�ӹر�
             1��ʱ��ʹ��
 bit[1:0]    ���Թܽ����ʱ��Ƶ�ʿ���
             00: ������ʱ��
             01��WPLL�������
             10��GPLL�������
             11��WPLL��GPLL�������
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA19_UNION */
#define ABB_CH0_REG_DEBUG_ANA19_ADDR                  (ABB_BASE_ADDR + 0xF3)

/* �Ĵ���˵����ģ����ԼĴ�����
 bit[7]      Tuning��·����ѡ��
             0: �����
             1: С����
 bit[6:5]    ���������������ݵ���
 bit[4]      �ⲿBandGapʹ���ź�
 bit[3:0]    Reserved
   UNION�ṹ:  ABB_CH0_REG_DEBUG_ANA20_UNION */
#define ABB_CH0_REG_DEBUG_ANA20_ADDR                  (ABB_BASE_ADDR + 0xF4)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA21_ADDR                  (ABB_BASE_ADDR + 0xF5)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA22_ADDR                  (ABB_BASE_ADDR + 0xF6)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA23_ADDR                  (ABB_BASE_ADDR + 0xF7)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA24_ADDR                  (ABB_BASE_ADDR + 0xF8)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA25_ADDR                  (ABB_BASE_ADDR + 0xF9)

/* �Ĵ���˵����ģ����ԼĴ�����
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA26_ADDR                  (ABB_BASE_ADDR + 0xFA)

/* �Ĵ���˵����ģ�����ֻ���Ĵ�����
   ��      ����Reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ARO0_ADDR                   (ABB_BASE_ADDR + 0xFB)

/* �Ĵ���˵����2gģʽRX��·ʱ���ӳٵ�����
 bit[7:6]    ����
 bit[5]      rx_clk���delay bypass���أ�
             1'b0��rx_clk ���delay ��bypass
             1'b1��rx_clk ���delay bypass
 bit[4]      rx_clk���������ƣ�
             1'b0��rx_clk bypass���
             1'b1��rx_clk�������
 bit[3:0]    RX_MCLKʱ����ʱѡ��
                 2G(ns) 3G(ns) 4G(ns)
             0 : 12.8  3.3  1.6 
             1 : 25.6  6.5  3.3 
             2 : 38.5  9.8  4.9 
             3 : 51.3  13.0  6.5 
             4 : 64.1  16.3  8.1 
             5 : 76.9  19.5  9.8 
             6 : 89.7  22.8  11.4 
             7 : 102.6  26.0  13.0 
             8 : 115.4  29.3  14.6 
             9 : 128.2  32.6  16.3 
             10 : 141.0  35.8  17.9 
             11 : 153.8  39.1  19.5 
             12 : 166.7  42.3  21.2 
             13 : 179.5  45.6  22.8 
             14 : 192.3  48.8  24.4 
             15 : 205.1  52.1  26.0 
             
   UNION�ṹ:  ABB_CH0_2G_RX_DELAY_UNION */
#define ABB_CH0_2G_RX_DELAY_ADDR                      (ABB_BASE_ADDR + 0xFC)

/* �Ĵ���˵����3gģʽRX��·ʱ���ӳٵ�����
 bit[7:6]    ����
 bit[5]      rx_clk���delay bypass���أ�
             1'b0��rx_clk ���delay ��bypass
             1'b1��rx_clk ���delay bypass
 bit[4]      rx_clk���������ƣ�
             1'b0��rx_clk bypass���
             1'b1��rx_clk�������
 bit[3:0]    RX_MCLKʱ����ʱѡ��
                 2G(ns) 3G(ns) 4G(ns)
             0 : 12.8  3.3  1.6 
             1 : 25.6  6.5  3.3 
             2 : 38.5  9.8  4.9 
             3 : 51.3  13.0  6.5 
             4 : 64.1  16.3  8.1 
             5 : 76.9  19.5  9.8 
             6 : 89.7  22.8  11.4 
             7 : 102.6  26.0  13.0 
             8 : 115.4  29.3  14.6 
             9 : 128.2  32.6  16.3 
             10 : 141.0  35.8  17.9 
             11 : 153.8  39.1  19.5 
             12 : 166.7  42.3  21.2 
             13 : 179.5  45.6  22.8 
             14 : 192.3  48.8  24.4 
             15 : 205.1  52.1  26.0 
             
   UNION�ṹ:  ABB_CH0_3G_RX_DELAY_UNION */
#define ABB_CH0_3G_RX_DELAY_ADDR                      (ABB_BASE_ADDR + 0xFD)

/* �Ĵ���˵����4gģʽRX��·ʱ���ӳٵ�����
 bit[7:6]    ����
 bit[5]      rx_clk���delay bypass���أ�
             1'b0��rx_clk ���delay ��bypass
             1'b1��rx_clk ���delay bypass
 bit[4]      rx_clk���������ƣ�
             1'b0��rx_clk bypass���
             1'b1��rx_clk�������
 bit[3:0]    RX_MCLKʱ����ʱѡ��
                 2G(ns) 3G(ns) 4G(ns)
             0 : 12.8  3.3  1.6 
             1 : 25.6  6.5  3.3 
             2 : 38.5  9.8  4.9 
             3 : 51.3  13.0  6.5 
             4 : 64.1  16.3  8.1 
             5 : 76.9  19.5  9.8 
             6 : 89.7  22.8  11.4 
             7 : 102.6  26.0  13.0 
             8 : 115.4  29.3  14.6 
             9 : 128.2  32.6  16.3 
             10 : 141.0  35.8  17.9 
             11 : 153.8  39.1  19.5 
             12 : 166.7  42.3  21.2 
             13 : 179.5  45.6  22.8 
             14 : 192.3  48.8  24.4 
             15 : 205.1  52.1  26.0 
             
   UNION�ṹ:  ABB_CH0_4G_RX_DELAY_UNION */
#define ABB_CH0_4G_RX_DELAY_ADDR                      (ABB_BASE_ADDR + 0xFE)

#define ABB_CH0_TX_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0x108)
#define ABB_CH0_TX_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0x109)
#define ABB_CH0_TX_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0x10A)




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
                     (1/1) register_define_ssi_reg
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : ABB_RX_2G_DIG_1_UNION
 �ṹ˵��  : rx_2g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x00����ֵ:0x02�����:8
 �Ĵ���˵��: RX 2Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      rx_2g_dig_1_reg;
    struct
    {
        unsigned long  rx_comp_sel_2g : 1;  /* bit[0]  : Reserved */
        unsigned long  rx_comp_fix_2g : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                         0��ϵ�����̶����ɼĴ�������
                                                         1��ϵ���̶� */
        unsigned long  rx_hb_bp_2g    : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                         0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                         1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  rx_rate_2g     : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                             2G,   3G_SC,    4G,   3G_DC,      
                                                         00�� 2.167M,15.36M, 61.44M,30.72M(Ĭ��)
                                                         01�� 4.33MHz,------,30.72M,------
                                                         10�� ------, ------,15.36M,------
                                                         11�� ------, ------, 7.68M,------ */
        unsigned long  rx_mode_dig_2g : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                         000��2G(Ĭ��)
                                                         001��3G_SC
                                                         010��4G
                                                         011��3G_DC
                                                         Others��reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_DIG_1_UNION;
#define ABB_RX_2G_DIG_1_rx_comp_sel_2g_START  (0)
#define ABB_RX_2G_DIG_1_rx_comp_sel_2g_END    (0)
#define ABB_RX_2G_DIG_1_rx_comp_fix_2g_START  (1)
#define ABB_RX_2G_DIG_1_rx_comp_fix_2g_END    (1)
#define ABB_RX_2G_DIG_1_rx_hb_bp_2g_START     (2)
#define ABB_RX_2G_DIG_1_rx_hb_bp_2g_END       (2)
#define ABB_RX_2G_DIG_1_rx_rate_2g_START      (3)
#define ABB_RX_2G_DIG_1_rx_rate_2g_END        (4)
#define ABB_RX_2G_DIG_1_rx_mode_dig_2g_START  (5)
#define ABB_RX_2G_DIG_1_rx_mode_dig_2g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_2G_DIG_2_UNION
 �ṹ˵��  : rx_2g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x01����ֵ:0x13�����:8
 �Ĵ���˵��: RX 2Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      rx_2g_dig_2_reg;
    struct
    {
        unsigned long  rxa_pd_2g     : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                        0����CLOCK GATING
                                                        1��CLOCK GATING(Ĭ��)
                                                        (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_2g     : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                        0����CLOCK GATING
                                                        1��CLOCK GATING(Ĭ��)
                                                        (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_2g   : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                        00��gainΪ0.5(Ĭ��)
                                                        01��gainΪ0.75
                                                        10��gainΪ0.85
                                                        11��Reserved */
        unsigned long  rx_comp_bp_2g : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                        0����bypass
                                                        1��bypass(Ĭ��) */
        unsigned long  rx_clk_inv_2g : 1;  /* bit[5]  : Reserved */
        unsigned long  rx_ddr_sdr_2g : 1;  /* bit[6]  : RX��DBB���ݽӿ�ʱ�����ã�
                                                        1'b0��SDR�ӿڣ�
                                                        1'b1��DDR�ӿڡ� */
        unsigned long  reserved      : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_DIG_2_UNION;
#define ABB_RX_2G_DIG_2_rxa_pd_2g_START      (0)
#define ABB_RX_2G_DIG_2_rxa_pd_2g_END        (0)
#define ABB_RX_2G_DIG_2_rxb_pd_2g_START      (1)
#define ABB_RX_2G_DIG_2_rxb_pd_2g_END        (1)
#define ABB_RX_2G_DIG_2_gain_sel_2g_START    (2)
#define ABB_RX_2G_DIG_2_gain_sel_2g_END      (3)
#define ABB_RX_2G_DIG_2_rx_comp_bp_2g_START  (4)
#define ABB_RX_2G_DIG_2_rx_comp_bp_2g_END    (4)
#define ABB_RX_2G_DIG_2_rx_clk_inv_2g_START  (5)
#define ABB_RX_2G_DIG_2_rx_clk_inv_2g_END    (5)
#define ABB_RX_2G_DIG_2_rx_ddr_sdr_2g_START  (6)
#define ABB_RX_2G_DIG_2_rx_ddr_sdr_2g_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_TX_2G_DIG_1_UNION
 �ṹ˵��  : tx_2g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x02����ֵ:0x02�����:8
 �Ĵ���˵��: TX 2Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_2g_dig_1_reg;
    struct
    {
        unsigned long  tx_comp_bp_2g  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                         0����bypass(Ĭ��)
                                                         1��bypass */
        unsigned long  tx_hb_bp_2g    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                         0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2
                                                         1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate(Ĭ��) */
        unsigned long  tx_rate_2g     : 3;  /* bit[2-4]: TXͨ��CIC�˲���������ʿ��ƣ�
                                                              2G,     3G,     4G,     
                                                             (78M) (153.6M) (307.2M) 
                                                         0��4.33MHz,30.72MHz,61.44MHz(Ĭ��)
                                                         1��2.16MHz,15.36MHz,30.72MHz
                                                         2��-------,--------,15.36MHz
                                                         3��-------,--------, 7.68MHz
                                                         4��-------,--------, 3.84MHz
                                                         Others��Reserved */
        unsigned long  tx_mode_dig_2g : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                         000��2G
                                                         001��3G(Ĭ��)
                                                         010��4G &amp; ET &amp; APT
                                                         Others��reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_DIG_1_UNION;
#define ABB_TX_2G_DIG_1_tx_comp_bp_2g_START   (0)
#define ABB_TX_2G_DIG_1_tx_comp_bp_2g_END     (0)
#define ABB_TX_2G_DIG_1_tx_hb_bp_2g_START     (1)
#define ABB_TX_2G_DIG_1_tx_hb_bp_2g_END       (1)
#define ABB_TX_2G_DIG_1_tx_rate_2g_START      (2)
#define ABB_TX_2G_DIG_1_tx_rate_2g_END        (4)
#define ABB_TX_2G_DIG_1_tx_mode_dig_2g_START  (5)
#define ABB_TX_2G_DIG_1_tx_mode_dig_2g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_2G_DIG_2_UNION
 �ṹ˵��  : tx_2g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x03����ֵ:0x0B�����:8
 �Ĵ���˵��: TX 2Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_2g_dig_2_reg;
    struct
    {
        unsigned long  tx_q_pd_2g       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  tx_i_pd_2g       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  dem_const_2g     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����Ĭ��ֵ2(��demģ���е�����ֵΪdem_const_xx * 2) */
        unsigned long  uddwa_dith_en_2g : 1;  /* bit[4]  : Reserved */
        unsigned long  dem_dwa_en_2g    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                           0��ʹ��CLAģʽ(Ĭ��)
                                                           1��ʹ��DWAģʽ  */
        unsigned long  dem_lsb_bp_2g    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                           0��DEM LSB ��(Ĭ��)
                                                           1��DEM LSB bypass */
        unsigned long  dem_msb_bp_2g    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                           0��DEM MSB ��(Ĭ��)
                                                           1��DEM MSB bypass */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_DIG_2_UNION;
#define ABB_TX_2G_DIG_2_tx_q_pd_2g_START        (0)
#define ABB_TX_2G_DIG_2_tx_q_pd_2g_END          (0)
#define ABB_TX_2G_DIG_2_tx_i_pd_2g_START        (1)
#define ABB_TX_2G_DIG_2_tx_i_pd_2g_END          (1)
#define ABB_TX_2G_DIG_2_dem_const_2g_START      (2)
#define ABB_TX_2G_DIG_2_dem_const_2g_END        (3)
#define ABB_TX_2G_DIG_2_uddwa_dith_en_2g_START  (4)
#define ABB_TX_2G_DIG_2_uddwa_dith_en_2g_END    (4)
#define ABB_TX_2G_DIG_2_dem_dwa_en_2g_START     (5)
#define ABB_TX_2G_DIG_2_dem_dwa_en_2g_END       (5)
#define ABB_TX_2G_DIG_2_dem_lsb_bp_2g_START     (6)
#define ABB_TX_2G_DIG_2_dem_lsb_bp_2g_END       (6)
#define ABB_TX_2G_DIG_2_dem_msb_bp_2g_START     (7)
#define ABB_TX_2G_DIG_2_dem_msb_bp_2g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_2G_DIG_3_UNION
 �ṹ˵��  : tx_2g_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x04����ֵ:0x00�����:8
 �Ĵ���˵��: TX 2Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_2g_dig_3_reg;
    struct
    {
        unsigned long  tx_cfr_bp_2g  : 1;  /* bit[0]  : Reserved */
        unsigned long  tx_ddr_sdr_2g : 1;  /* bit[1]  : TX��DBB���ݽӿ�ʱ�����ã�
                                                        1'b0��SDR�ӿڣ�
                                                        1'b1��DDR�ӿڡ� */
        unsigned long  reserved      : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_DIG_3_UNION;
#define ABB_TX_2G_DIG_3_tx_cfr_bp_2g_START   (0)
#define ABB_TX_2G_DIG_3_tx_cfr_bp_2g_END     (0)
#define ABB_TX_2G_DIG_3_tx_ddr_sdr_2g_START  (1)
#define ABB_TX_2G_DIG_3_tx_ddr_sdr_2g_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_RX_3G_DIG_1_UNION
 �ṹ˵��  : rx_3g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x05����ֵ:0x26�����:8
 �Ĵ���˵��: RX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      rx_3g_dig_1_reg;
    struct
    {
        unsigned long  rx_comp_sel_3g : 1;  /* bit[0]  : Reserved */
        unsigned long  rx_comp_fix_3g : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                         0��ϵ�����̶����ɼĴ�������
                                                         1��ϵ���̶� */
        unsigned long  rx_hb_bp_3g    : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                         0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                         1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  rx_rate_3g     : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                             2G,   3G_SC,    4G,   3G_DC,      
                                                         00�� 2.167M,15.36M, 61.44M,30.72M(Ĭ��)
                                                         01�� 4.33MHz,------,30.72M,------
                                                         10�� ------, ------,15.36M,------
                                                         11�� ------, ------, 7.68M,------ */
        unsigned long  rx_mode_dig_3g : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                         000��2G
                                                         001��3G_SC(Ĭ��)
                                                         010��4G
                                                         011��3G_DC
                                                         Others��reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_3G_DIG_1_UNION;
#define ABB_RX_3G_DIG_1_rx_comp_sel_3g_START  (0)
#define ABB_RX_3G_DIG_1_rx_comp_sel_3g_END    (0)
#define ABB_RX_3G_DIG_1_rx_comp_fix_3g_START  (1)
#define ABB_RX_3G_DIG_1_rx_comp_fix_3g_END    (1)
#define ABB_RX_3G_DIG_1_rx_hb_bp_3g_START     (2)
#define ABB_RX_3G_DIG_1_rx_hb_bp_3g_END       (2)
#define ABB_RX_3G_DIG_1_rx_rate_3g_START      (3)
#define ABB_RX_3G_DIG_1_rx_rate_3g_END        (4)
#define ABB_RX_3G_DIG_1_rx_mode_dig_3g_START  (5)
#define ABB_RX_3G_DIG_1_rx_mode_dig_3g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_3G_DIG_2_UNION
 �ṹ˵��  : rx_3g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x06����ֵ:0x03�����:8
 �Ĵ���˵��: RX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      rx_3g_dig_2_reg;
    struct
    {
        unsigned long  rxa_pd_3g     : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                        0����CLOCK GATING
                                                        1��CLOCK GATING(Ĭ��)
                                                        (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_3g     : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                        0����CLOCK GATING
                                                        1��CLOCK GATING(Ĭ��)
                                                        (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_3g   : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                        00��gainΪ0.5(Ĭ��)
                                                        01��gainΪ0.75
                                                        10��gainΪ0.85
                                                        11��Reserved */
        unsigned long  rx_comp_bp_3g : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                        0����bypass(Ĭ��)
                                                        1��bypass */
        unsigned long  rx_clk_inv_3g : 1;  /* bit[5]  : Reserved */
        unsigned long  rx_ddr_sdr_3g : 1;  /* bit[6]  : RX��DBB���ݽӿ�ʱ�����ã�
                                                        1'b0��SDR�ӿڣ�
                                                        1'b1��DDR�ӿڡ� */
        unsigned long  reserved      : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_3G_DIG_2_UNION;
#define ABB_RX_3G_DIG_2_rxa_pd_3g_START      (0)
#define ABB_RX_3G_DIG_2_rxa_pd_3g_END        (0)
#define ABB_RX_3G_DIG_2_rxb_pd_3g_START      (1)
#define ABB_RX_3G_DIG_2_rxb_pd_3g_END        (1)
#define ABB_RX_3G_DIG_2_gain_sel_3g_START    (2)
#define ABB_RX_3G_DIG_2_gain_sel_3g_END      (3)
#define ABB_RX_3G_DIG_2_rx_comp_bp_3g_START  (4)
#define ABB_RX_3G_DIG_2_rx_comp_bp_3g_END    (4)
#define ABB_RX_3G_DIG_2_rx_clk_inv_3g_START  (5)
#define ABB_RX_3G_DIG_2_rx_clk_inv_3g_END    (5)
#define ABB_RX_3G_DIG_2_rx_ddr_sdr_3g_START  (6)
#define ABB_RX_3G_DIG_2_rx_ddr_sdr_3g_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_TX_3G_DIG_1_UNION
 �ṹ˵��  : tx_3g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x07����ֵ:0x20�����:8
 �Ĵ���˵��: TX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_3g_dig_1_reg;
    struct
    {
        unsigned long  tx_comp_bp_3g  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                         0����bypass(Ĭ��)
                                                         1��bypass */
        unsigned long  tx_hb_bp_3g    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                         0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                         1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  tx_rate_3g     : 3;  /* bit[2-4]: TXͨ��CIC�˲���������ʿ��ƣ�
                                                              2G,     3G,     4G,     
                                                             (78M) (153.6M) (307.2M) 
                                                         0��4.33MHz,30.72MHz,61.44MHz(Ĭ��)
                                                         1��2.16MHz,15.36MHz,30.72MHz
                                                         2��-------,--------,15.36MHz
                                                         3��-------,--------, 7.68MHz
                                                         4��-------,--------, 3.84MHz
                                                         Others��Reserved */
        unsigned long  tx_mode_dig_3g : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                         000��2G
                                                         001��3G(Ĭ��)
                                                         010��4G &amp; ET &amp; APT
                                                         Others��reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_3G_DIG_1_UNION;
#define ABB_TX_3G_DIG_1_tx_comp_bp_3g_START   (0)
#define ABB_TX_3G_DIG_1_tx_comp_bp_3g_END     (0)
#define ABB_TX_3G_DIG_1_tx_hb_bp_3g_START     (1)
#define ABB_TX_3G_DIG_1_tx_hb_bp_3g_END       (1)
#define ABB_TX_3G_DIG_1_tx_rate_3g_START      (2)
#define ABB_TX_3G_DIG_1_tx_rate_3g_END        (4)
#define ABB_TX_3G_DIG_1_tx_mode_dig_3g_START  (5)
#define ABB_TX_3G_DIG_1_tx_mode_dig_3g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_3G_DIG_2_UNION
 �ṹ˵��  : tx_3g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x08����ֵ:0x0B�����:8
 �Ĵ���˵��: TX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_3g_dig_2_reg;
    struct
    {
        unsigned long  tx_q_pd_3g       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  tx_i_pd_3g       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  dem_const_3g     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����Ĭ��ֵ2(��demģ���е�����ֵΪdem_const_xx * 2) */
        unsigned long  uddwa_dith_en_3g : 1;  /* bit[4]  : Reserved */
        unsigned long  dem_dwa_en_3g    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                           0��ʹ��CLAģʽ(Ĭ��)
                                                           1��ʹ��DWAģʽ  */
        unsigned long  dem_lsb_bp_3g    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                           0��DEM LSB ��(Ĭ��)
                                                           1��DEM LSB bypass */
        unsigned long  dem_msb_bp_3g    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                           0��DEM MSB ��(Ĭ��)
                                                           1��DEM MSB bypass */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_3G_DIG_2_UNION;
#define ABB_TX_3G_DIG_2_tx_q_pd_3g_START        (0)
#define ABB_TX_3G_DIG_2_tx_q_pd_3g_END          (0)
#define ABB_TX_3G_DIG_2_tx_i_pd_3g_START        (1)
#define ABB_TX_3G_DIG_2_tx_i_pd_3g_END          (1)
#define ABB_TX_3G_DIG_2_dem_const_3g_START      (2)
#define ABB_TX_3G_DIG_2_dem_const_3g_END        (3)
#define ABB_TX_3G_DIG_2_uddwa_dith_en_3g_START  (4)
#define ABB_TX_3G_DIG_2_uddwa_dith_en_3g_END    (4)
#define ABB_TX_3G_DIG_2_dem_dwa_en_3g_START     (5)
#define ABB_TX_3G_DIG_2_dem_dwa_en_3g_END       (5)
#define ABB_TX_3G_DIG_2_dem_lsb_bp_3g_START     (6)
#define ABB_TX_3G_DIG_2_dem_lsb_bp_3g_END       (6)
#define ABB_TX_3G_DIG_2_dem_msb_bp_3g_START     (7)
#define ABB_TX_3G_DIG_2_dem_msb_bp_3g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_3G_DIG_3_UNION
 �ṹ˵��  : tx_3g_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x09����ֵ:0x00�����:8
 �Ĵ���˵��: TX 3Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_3g_dig_3_reg;
    struct
    {
        unsigned long  tx_cfr_bp_3g  : 1;  /* bit[0]  : Reserved */
        unsigned long  tx_ddr_sdr_3g : 1;  /* bit[1]  : TX��DBB���ݽӿ�ʱ�����ã�
                                                        1'b0��SDR�ӿڣ�
                                                        1'b1��DDR�ӿڡ� */
        unsigned long  reserved      : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_3G_DIG_3_UNION;
#define ABB_TX_3G_DIG_3_tx_cfr_bp_3g_START   (0)
#define ABB_TX_3G_DIG_3_tx_cfr_bp_3g_END     (0)
#define ABB_TX_3G_DIG_3_tx_ddr_sdr_3g_START  (1)
#define ABB_TX_3G_DIG_3_tx_ddr_sdr_3g_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_RX_4G_DIG_1_UNION
 �ṹ˵��  : rx_4g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x0A����ֵ:0x40�����:8
 �Ĵ���˵��: RX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      rx_4g_dig_1_reg;
    struct
    {
        unsigned long  rx_comp_sel_4g : 1;  /* bit[0]  : Reserved */
        unsigned long  rx_comp_fix_4g : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                         0��ϵ�����̶����ɼĴ�������
                                                         1��ϵ���̶� */
        unsigned long  rx_hb_bp_4g    : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                         0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                         1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  rx_rate_4g     : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                             2G,   3G_SC,    4G,   3G_DC,      
                                                         00�� 2.167M,15.36M, 61.44M,30.72M(Ĭ��)
                                                         01�� 4.33MHz,------,30.72M,------
                                                         10�� ------, ------,15.36M,------
                                                         11�� ------, ------, 7.68M,------ */
        unsigned long  rx_mode_dig_4g : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                         000��2G
                                                         001��3G_SC
                                                         010��4G(Ĭ��)
                                                         011��3G_DC
                                                         Others��reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_4G_DIG_1_UNION;
#define ABB_RX_4G_DIG_1_rx_comp_sel_4g_START  (0)
#define ABB_RX_4G_DIG_1_rx_comp_sel_4g_END    (0)
#define ABB_RX_4G_DIG_1_rx_comp_fix_4g_START  (1)
#define ABB_RX_4G_DIG_1_rx_comp_fix_4g_END    (1)
#define ABB_RX_4G_DIG_1_rx_hb_bp_4g_START     (2)
#define ABB_RX_4G_DIG_1_rx_hb_bp_4g_END       (2)
#define ABB_RX_4G_DIG_1_rx_rate_4g_START      (3)
#define ABB_RX_4G_DIG_1_rx_rate_4g_END        (4)
#define ABB_RX_4G_DIG_1_rx_mode_dig_4g_START  (5)
#define ABB_RX_4G_DIG_1_rx_mode_dig_4g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_4G_DIG_2_UNION
 �ṹ˵��  : rx_4g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x0B����ֵ:0x43�����:8
 �Ĵ���˵��: RX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      rx_4g_dig_2_reg;
    struct
    {
        unsigned long  rxa_pd_4g     : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                        0����CLOCK GATING
                                                        1��CLOCK GATING(Ĭ��)
                                                        (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_4g     : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                        0����CLOCK GATING
                                                        1��CLOCK GATING(Ĭ��)
                                                        (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_4g   : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                        00��gainΪ0.5(Ĭ��)
                                                        01��gainΪ0.75
                                                        10��gainΪ0.85
                                                        11��Reserved */
        unsigned long  rx_comp_bp_4g : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                        0����bypass(Ĭ��)
                                                        1��bypass */
        unsigned long  rx_clk_inv_4g : 1;  /* bit[5]  : Reserved */
        unsigned long  rx_ddr_sdr_4g : 1;  /* bit[6]  : RX��DBB���ݽӿ�ʱ�����ã�
                                                        1'b0��SDR�ӿڣ�
                                                        1'b1��DDR�ӿڡ� */
        unsigned long  reserved      : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_4G_DIG_2_UNION;
#define ABB_RX_4G_DIG_2_rxa_pd_4g_START      (0)
#define ABB_RX_4G_DIG_2_rxa_pd_4g_END        (0)
#define ABB_RX_4G_DIG_2_rxb_pd_4g_START      (1)
#define ABB_RX_4G_DIG_2_rxb_pd_4g_END        (1)
#define ABB_RX_4G_DIG_2_gain_sel_4g_START    (2)
#define ABB_RX_4G_DIG_2_gain_sel_4g_END      (3)
#define ABB_RX_4G_DIG_2_rx_comp_bp_4g_START  (4)
#define ABB_RX_4G_DIG_2_rx_comp_bp_4g_END    (4)
#define ABB_RX_4G_DIG_2_rx_clk_inv_4g_START  (5)
#define ABB_RX_4G_DIG_2_rx_clk_inv_4g_END    (5)
#define ABB_RX_4G_DIG_2_rx_ddr_sdr_4g_START  (6)
#define ABB_RX_4G_DIG_2_rx_ddr_sdr_4g_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_TX_4G_DIG_1_UNION
 �ṹ˵��  : tx_4g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x0C����ֵ:0x40�����:8
 �Ĵ���˵��: TX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_4g_dig_1_reg;
    struct
    {
        unsigned long  tx_comp_bp_4g  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                         0����bypass(Ĭ��)
                                                         1��bypass */
        unsigned long  tx_hb_bp_4g    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                         0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                         1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  tx_rate_4g     : 3;  /* bit[2-4]: TXͨ��CIC�˲���������ʿ��ƣ�
                                                              2G,     3G,     4G,     
                                                             (78M) (153.6M) (307.2M) 
                                                         0��4.33MHz,30.72MHz,61.44MHz(Ĭ��)
                                                         1��2.16MHz,15.36MHz,30.72MHz
                                                         2��-------,--------,15.36MHz
                                                         3��-------,--------, 7.68MHz
                                                         4��-------,--------, 3.84MHz
                                                         Others��Reserved */
        unsigned long  tx_mode_dig_4g : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                         000��2G
                                                         001��3G
                                                         010��4G &amp; ET &amp; APT(Ĭ��)
                                                         Others��reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_4G_DIG_1_UNION;
#define ABB_TX_4G_DIG_1_tx_comp_bp_4g_START   (0)
#define ABB_TX_4G_DIG_1_tx_comp_bp_4g_END     (0)
#define ABB_TX_4G_DIG_1_tx_hb_bp_4g_START     (1)
#define ABB_TX_4G_DIG_1_tx_hb_bp_4g_END       (1)
#define ABB_TX_4G_DIG_1_tx_rate_4g_START      (2)
#define ABB_TX_4G_DIG_1_tx_rate_4g_END        (4)
#define ABB_TX_4G_DIG_1_tx_mode_dig_4g_START  (5)
#define ABB_TX_4G_DIG_1_tx_mode_dig_4g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_4G_DIG_2_UNION
 �ṹ˵��  : tx_4g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x0D����ֵ:0x0B�����:8
 �Ĵ���˵��: TX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_4g_dig_2_reg;
    struct
    {
        unsigned long  tx_q_pd_4g       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  tx_i_pd_4g       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  dem_const_4g     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����Ĭ��ֵ2(��demģ���е�����ֵΪdem_const_xx * 2) */
        unsigned long  uddwa_dith_en_4g : 1;  /* bit[4]  : Reserved */
        unsigned long  dem_dwa_en_4g    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                           0��ʹ��CLAģʽ(Ĭ��)
                                                           1��ʹ��DWAģʽ  */
        unsigned long  dem_lsb_bp_4g    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                           0��DEM LSB ��(Ĭ��)
                                                           1��DEM LSB bypass */
        unsigned long  dem_msb_bp_4g    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                           0��DEM MSB ��(Ĭ��)
                                                           1��DEM MSB bypass */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_4G_DIG_2_UNION;
#define ABB_TX_4G_DIG_2_tx_q_pd_4g_START        (0)
#define ABB_TX_4G_DIG_2_tx_q_pd_4g_END          (0)
#define ABB_TX_4G_DIG_2_tx_i_pd_4g_START        (1)
#define ABB_TX_4G_DIG_2_tx_i_pd_4g_END          (1)
#define ABB_TX_4G_DIG_2_dem_const_4g_START      (2)
#define ABB_TX_4G_DIG_2_dem_const_4g_END        (3)
#define ABB_TX_4G_DIG_2_uddwa_dith_en_4g_START  (4)
#define ABB_TX_4G_DIG_2_uddwa_dith_en_4g_END    (4)
#define ABB_TX_4G_DIG_2_dem_dwa_en_4g_START     (5)
#define ABB_TX_4G_DIG_2_dem_dwa_en_4g_END       (5)
#define ABB_TX_4G_DIG_2_dem_lsb_bp_4g_START     (6)
#define ABB_TX_4G_DIG_2_dem_lsb_bp_4g_END       (6)
#define ABB_TX_4G_DIG_2_dem_msb_bp_4g_START     (7)
#define ABB_TX_4G_DIG_2_dem_msb_bp_4g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_4G_DIG_3_UNION
 �ṹ˵��  : tx_4g_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x0E����ֵ:0x02�����:8
 �Ĵ���˵��: TX 4Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_4g_dig_3_reg;
    struct
    {
        unsigned long  tx_cfr_bp_4g  : 1;  /* bit[0]  : Reserved */
        unsigned long  tx_ddr_sdr_4g : 1;  /* bit[1]  : TX��DBB���ݽӿ�ʱ�����ã�
                                                        1'b0��SDR�ӿڣ�
                                                        1'b1��DDR�ӿڡ� */
        unsigned long  reserved      : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_4G_DIG_3_UNION;
#define ABB_TX_4G_DIG_3_tx_cfr_bp_4g_START   (0)
#define ABB_TX_4G_DIG_3_tx_cfr_bp_4g_END     (0)
#define ABB_TX_4G_DIG_3_tx_ddr_sdr_4g_START  (1)
#define ABB_TX_4G_DIG_3_tx_ddr_sdr_4g_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_DIG_1_UNION
 �ṹ˵��  : rx_tds_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x0F����ֵ:0x80�����:8
 �Ĵ���˵��: RX TDSģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      rx_tds_dig_1_reg;
    struct
    {
        unsigned long  rx_comp_sel_tds : 1;  /* bit[0]  : Reserved */
        unsigned long  rx_comp_fix_tds : 1;  /* bit[1]  : Reserved */
        unsigned long  rx_hb_bp_tds    : 1;  /* bit[2]  : Reserved */
        unsigned long  rx_rate_tds     : 2;  /* bit[3-4]: Reserved */
        unsigned long  rx_mode_dig_tds : 3;  /* bit[5-7]: Reserved */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_DIG_1_UNION;
#define ABB_RX_TDS_DIG_1_rx_comp_sel_tds_START  (0)
#define ABB_RX_TDS_DIG_1_rx_comp_sel_tds_END    (0)
#define ABB_RX_TDS_DIG_1_rx_comp_fix_tds_START  (1)
#define ABB_RX_TDS_DIG_1_rx_comp_fix_tds_END    (1)
#define ABB_RX_TDS_DIG_1_rx_hb_bp_tds_START     (2)
#define ABB_RX_TDS_DIG_1_rx_hb_bp_tds_END       (2)
#define ABB_RX_TDS_DIG_1_rx_rate_tds_START      (3)
#define ABB_RX_TDS_DIG_1_rx_rate_tds_END        (4)
#define ABB_RX_TDS_DIG_1_rx_mode_dig_tds_START  (5)
#define ABB_RX_TDS_DIG_1_rx_mode_dig_tds_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_DIG_2_UNION
 �ṹ˵��  : rx_tds_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x10����ֵ:0x65�����:8
 �Ĵ���˵��: RX TDSģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      rx_tds_dig_2_reg;
    struct
    {
        unsigned long  rxa_pd_2g     : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                        0����CLOCK GATING
                                                        1��CLOCK GATING(Ĭ��)
                                                        (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_2g     : 1;  /* bit[1]  :  */
        unsigned long  gain_sel_2g   : 2;  /* bit[2-3]: RXBͨ��CLOCK GATING���ƣ�
                                                        0����CLOCK GATING
                                                        1��CLOCK GATING(Ĭ��)
                                                        (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  rx_comp_bp_2g : 1;  /* bit[4]  : RXͨ����������ѡ��
                                                        00��gainΪ0.5(Ĭ��)
                                                        01��gainΪ0.75
                                                        10��gainΪ0.85
                                                        11��Reserved */
        unsigned long  tx_cfr_bp_2g  : 1;  /* bit[5]  : RXͨ�������˲���bypass���ƣ�
                                                        0����bypass
                                                        1��bypass(Ĭ��) */
        unsigned long  rx_ddr_sdr_2g : 1;  /* bit[6]  : TXͨ��CFR bypass���ƣ�
                                                        0����bypass
                                                        1��bypass(Ĭ��) */
        unsigned long  reserved      : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_DIG_2_UNION;
#define ABB_RX_TDS_DIG_2_rxa_pd_2g_START      (0)
#define ABB_RX_TDS_DIG_2_rxa_pd_2g_END        (0)
#define ABB_RX_TDS_DIG_2_rxb_pd_2g_START      (1)
#define ABB_RX_TDS_DIG_2_rxb_pd_2g_END        (1)
#define ABB_RX_TDS_DIG_2_gain_sel_2g_START    (2)
#define ABB_RX_TDS_DIG_2_gain_sel_2g_END      (3)
#define ABB_RX_TDS_DIG_2_rx_comp_bp_2g_START  (4)
#define ABB_RX_TDS_DIG_2_rx_comp_bp_2g_END    (4)
#define ABB_RX_TDS_DIG_2_tx_cfr_bp_2g_START   (5)
#define ABB_RX_TDS_DIG_2_tx_cfr_bp_2g_END     (5)
#define ABB_RX_TDS_DIG_2_rx_ddr_sdr_2g_START  (6)
#define ABB_RX_TDS_DIG_2_rx_ddr_sdr_2g_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_TX_TDS_DIG_1_UNION
 �ṹ˵��  : tx_tds_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x11����ֵ:0x60�����:8
 �Ĵ���˵��: TX TDSģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_tds_dig_1_reg;
    struct
    {
        unsigned long  tx_comp_bp_tds  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                          0����bypass(Ĭ��)
                                                          1��bypass */
        unsigned long  tx_hb_bp_tds    : 1;  /* bit[1]  : TXͨ������˲�����bypass�ź�
                                                          0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                          1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  tx_rate_tds     : 3;  /* bit[2-4]: TXͨ��CIC�˲���������ʿ��ƣ�
                                                               2G,     3G,     4G,      TDS,      CA
                                                              (78M) (153.6M) (307.2M) (153.6M) (614.4M)
                                                          0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,122.88MHz(Ĭ��)
                                                          1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                          2��-------,--------,15.36MHz,--------,--------
                                                          3��-------,--------, 7.68MHz,--------,--------
                                                          4��-------,--------, 3.84MHz,--------,--------
                                                          Others��Reserved */
        unsigned long  tx_mode_dig_tds : 3;  /* bit[5-7]: TXģʽ���ƣ�
                                                          000��2G
                                                          001��3G
                                                          010��4G &amp; ET &amp; APT
                                                          011��TDS(Ĭ��)
                                                          Others��CA */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_DIG_1_UNION;
#define ABB_TX_TDS_DIG_1_tx_comp_bp_tds_START   (0)
#define ABB_TX_TDS_DIG_1_tx_comp_bp_tds_END     (0)
#define ABB_TX_TDS_DIG_1_tx_hb_bp_tds_START     (1)
#define ABB_TX_TDS_DIG_1_tx_hb_bp_tds_END       (1)
#define ABB_TX_TDS_DIG_1_tx_rate_tds_START      (2)
#define ABB_TX_TDS_DIG_1_tx_rate_tds_END        (4)
#define ABB_TX_TDS_DIG_1_tx_mode_dig_tds_START  (5)
#define ABB_TX_TDS_DIG_1_tx_mode_dig_tds_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_TDS_DIG_2_UNION
 �ṹ˵��  : tx_tds_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x12����ֵ:0x03�����:8
 �Ĵ���˵��: TX TDSģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_tds_dig_2_reg;
    struct
    {
        unsigned long  tx_q_pd_tds       : 1;  /* bit[0]: TXͨ��Q·CLOCK GATING���ƣ�
                                                          0����CLOCK GATING
                                                          1��CLOCK GATING(Ĭ��)
                                                          (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  tx_i_pd_tds       : 1;  /* bit[1]: TXͨ��I·CLOCK GATING���ƣ�
                                                          0����CLOCK GATING
                                                          1��CLOCK GATING(Ĭ��)
                                                          (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  dem_const_tds     : 1;  /* bit[2]: TXͨ��DEM constϵ����
                                                          0��2(Ĭ��)
                                                          1��4 */
        unsigned long  uddwa_dith_en_tds : 1;  /* bit[3]: TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                          0����ʹ��
                                                          1��ʹ�� */
        unsigned long  dither_en_tds     : 1;  /* bit[4]: TXͨ��SDM Dither���ƣ�
                                                          0����ʹ��
                                                          1��ʹ�� */
        unsigned long  dem_dwa_en_tds    : 1;  /* bit[5]: TXͨ��DEMģʽ���ƣ�
                                                          0��ʹ��CLAģʽ(Ĭ��)
                                                          1��ʹ��DWAģʽ  */
        unsigned long  dem_lsb_bp_tds    : 1;  /* bit[6]: TXͨ��DEM LSB bypass��
                                                          0��DEM LSB ��(Ĭ��)
                                                          1��DEM LSB bypass */
        unsigned long  dem_msb_bp_tds    : 1;  /* bit[7]: TXͨ��DEM MSB bypass��
                                                          0��DEM MSB��(Ĭ��)
                                                          1��DEM MSB bypass */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_DIG_2_UNION;
#define ABB_TX_TDS_DIG_2_tx_q_pd_tds_START        (0)
#define ABB_TX_TDS_DIG_2_tx_q_pd_tds_END          (0)
#define ABB_TX_TDS_DIG_2_tx_i_pd_tds_START        (1)
#define ABB_TX_TDS_DIG_2_tx_i_pd_tds_END          (1)
#define ABB_TX_TDS_DIG_2_dem_const_tds_START      (2)
#define ABB_TX_TDS_DIG_2_dem_const_tds_END        (2)
#define ABB_TX_TDS_DIG_2_uddwa_dith_en_tds_START  (3)
#define ABB_TX_TDS_DIG_2_uddwa_dith_en_tds_END    (3)
#define ABB_TX_TDS_DIG_2_dither_en_tds_START      (4)
#define ABB_TX_TDS_DIG_2_dither_en_tds_END        (4)
#define ABB_TX_TDS_DIG_2_dem_dwa_en_tds_START     (5)
#define ABB_TX_TDS_DIG_2_dem_dwa_en_tds_END       (5)
#define ABB_TX_TDS_DIG_2_dem_lsb_bp_tds_START     (6)
#define ABB_TX_TDS_DIG_2_dem_lsb_bp_tds_END       (6)
#define ABB_TX_TDS_DIG_2_dem_msb_bp_tds_START     (7)
#define ABB_TX_TDS_DIG_2_dem_msb_bp_tds_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_TDS_DIG_3_UNION
 �ṹ˵��  : tx_tds_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x13����ֵ:0x00�����:8
 �Ĵ���˵��: TX TDSģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_tds_dig_3_reg;
    struct
    {
        unsigned long  tx_cfr_bp_tds  : 1;  /* bit[0]  : Reserved */
        unsigned long  tx_ddr_sdr_tds : 1;  /* bit[1]  : TX��DBB���ݽӿ�ʱ�����ã�
                                                         1'b0��SDR�ӿڣ�
                                                         1'b1��DDR�ӿڡ� */
        unsigned long  reserved       : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_DIG_3_UNION;
#define ABB_TX_TDS_DIG_3_tx_cfr_bp_tds_START   (0)
#define ABB_TX_TDS_DIG_3_tx_cfr_bp_tds_END     (0)
#define ABB_TX_TDS_DIG_3_tx_ddr_sdr_tds_START  (1)
#define ABB_TX_TDS_DIG_3_tx_ddr_sdr_tds_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_TX_ET_DIG_1_UNION
 �ṹ˵��  : tx_et_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x14����ֵ:0x40�����:8
 �Ĵ���˵��: TX ETģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_et_dig_1_reg;
    struct
    {
        unsigned long  tx_comp_bp_et  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                         0����bypass(Ĭ��)
                                                         1��bypass */
        unsigned long  tx_hb_bp_et    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                         0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                         1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  tx_rate_et     : 3;  /* bit[2-4]: TXͨ��CIC�˲���������ʿ��ƣ�
                                                              2G,     3G,     4G,     
                                                             (78M) (153.6M) (307.2M) 
                                                         0��4.33MHz,30.72MHz,61.44MHz(Ĭ��)
                                                         1��2.16MHz,15.36MHz,30.72MHz
                                                         2��-------,--------,15.36MHz
                                                         3��-------,--------, 7.68MHz
                                                         4��-------,--------, 3.84MHz
                                                         Others��Reserved */
        unsigned long  tx_mode_dig_et : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                         000��2G
                                                         001��3G
                                                         010��4G &amp; ET &amp; APT(Ĭ��)
                                                         Others��reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_DIG_1_UNION;
#define ABB_TX_ET_DIG_1_tx_comp_bp_et_START   (0)
#define ABB_TX_ET_DIG_1_tx_comp_bp_et_END     (0)
#define ABB_TX_ET_DIG_1_tx_hb_bp_et_START     (1)
#define ABB_TX_ET_DIG_1_tx_hb_bp_et_END       (1)
#define ABB_TX_ET_DIG_1_tx_rate_et_START      (2)
#define ABB_TX_ET_DIG_1_tx_rate_et_END        (4)
#define ABB_TX_ET_DIG_1_tx_mode_dig_et_START  (5)
#define ABB_TX_ET_DIG_1_tx_mode_dig_et_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_ET_DIG_2_UNION
 �ṹ˵��  : tx_et_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x15����ֵ:0x0B�����:8
 �Ĵ���˵��: TX ETģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_et_dig_2_reg;
    struct
    {
        unsigned long  tx_q_pd_et       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  tx_i_pd_et       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  dem_const_et     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����Ĭ��ֵ2(��demģ���е�����ֵΪdem_const_xx * 2) */
        unsigned long  uddwa_dith_en_et : 1;  /* bit[4]  : Reserved */
        unsigned long  dem_dwa_en_et    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                           0��ʹ��CLAģʽ(Ĭ��)
                                                           1��ʹ��DWAģʽ  */
        unsigned long  dem_lsb_bp_et    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                           0��DEM LSB ��(Ĭ��)
                                                           1��DEM LSB bypass */
        unsigned long  dem_msb_bp_et    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                           0��DEM MSB ��(Ĭ��)
                                                           1��DEM MSB bypass */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_DIG_2_UNION;
#define ABB_TX_ET_DIG_2_tx_q_pd_et_START        (0)
#define ABB_TX_ET_DIG_2_tx_q_pd_et_END          (0)
#define ABB_TX_ET_DIG_2_tx_i_pd_et_START        (1)
#define ABB_TX_ET_DIG_2_tx_i_pd_et_END          (1)
#define ABB_TX_ET_DIG_2_dem_const_et_START      (2)
#define ABB_TX_ET_DIG_2_dem_const_et_END        (3)
#define ABB_TX_ET_DIG_2_uddwa_dith_en_et_START  (4)
#define ABB_TX_ET_DIG_2_uddwa_dith_en_et_END    (4)
#define ABB_TX_ET_DIG_2_dem_dwa_en_et_START     (5)
#define ABB_TX_ET_DIG_2_dem_dwa_en_et_END       (5)
#define ABB_TX_ET_DIG_2_dem_lsb_bp_et_START     (6)
#define ABB_TX_ET_DIG_2_dem_lsb_bp_et_END       (6)
#define ABB_TX_ET_DIG_2_dem_msb_bp_et_START     (7)
#define ABB_TX_ET_DIG_2_dem_msb_bp_et_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_ET_DIG_3_UNION
 �ṹ˵��  : tx_et_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x16����ֵ:0x02�����:8
 �Ĵ���˵��: TX ETģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_et_dig_3_reg;
    struct
    {
        unsigned long  tx_cfr_bp_et  : 1;  /* bit[0]  : Reserved */
        unsigned long  tx_ddr_sdr_et : 1;  /* bit[1]  : TX��DBB���ݽӿ�ʱ�����ã�
                                                        1'b0��SDR�ӿڣ�
                                                        1'b1��DDR�ӿڡ� */
        unsigned long  reserved      : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_DIG_3_UNION;
#define ABB_TX_ET_DIG_3_tx_cfr_bp_et_START   (0)
#define ABB_TX_ET_DIG_3_tx_cfr_bp_et_END     (0)
#define ABB_TX_ET_DIG_3_tx_ddr_sdr_et_START  (1)
#define ABB_TX_ET_DIG_3_tx_ddr_sdr_et_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_TX_APT_DIG_1_UNION
 �ṹ˵��  : tx_apt_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x17����ֵ:0x40�����:8
 �Ĵ���˵��: TX APTģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_apt_dig_1_reg;
    struct
    {
        unsigned long  tx_comp_bp_apt  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                          0����bypass(Ĭ��)
                                                          1��bypass */
        unsigned long  tx_hb_bp_apt    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                          0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                          1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  tx_rate_apt     : 3;  /* bit[2-4]: TXͨ��CIC�˲���������ʿ��ƣ�
                                                               2G,     3G,     4G,     
                                                              (78M) (153.6M) (307.2M) 
                                                          0��4.33MHz,30.72MHz,61.44MHz(Ĭ��)
                                                          1��2.16MHz,15.36MHz,30.72MHz
                                                          2��-------,--------,15.36MHz
                                                          3��-------,--------, 7.68MHz
                                                          4��-------,--------, 3.84MHz
                                                          Others��Reserved */
        unsigned long  tx_mode_dig_apt : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                          000��2G
                                                          001��3G
                                                          010��4G &amp; ET &amp; APT(Ĭ��)
                                                          Others��reserved */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_APT_DIG_1_UNION;
#define ABB_TX_APT_DIG_1_tx_comp_bp_apt_START   (0)
#define ABB_TX_APT_DIG_1_tx_comp_bp_apt_END     (0)
#define ABB_TX_APT_DIG_1_tx_hb_bp_apt_START     (1)
#define ABB_TX_APT_DIG_1_tx_hb_bp_apt_END       (1)
#define ABB_TX_APT_DIG_1_tx_rate_apt_START      (2)
#define ABB_TX_APT_DIG_1_tx_rate_apt_END        (4)
#define ABB_TX_APT_DIG_1_tx_mode_dig_apt_START  (5)
#define ABB_TX_APT_DIG_1_tx_mode_dig_apt_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_APT_DIG_2_UNION
 �ṹ˵��  : tx_apt_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x18����ֵ:0x0B�����:8
 �Ĵ���˵��: TX APTģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_apt_dig_2_reg;
    struct
    {
        unsigned long  tx_q_pd_apt       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                            0����CLOCK GATING
                                                            1��CLOCK GATING(Ĭ��)
                                                            (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  tx_i_pd_apt       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                            0����CLOCK GATING
                                                            1��CLOCK GATING(Ĭ��)
                                                            (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  dem_const_apt     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����Ĭ��ֵ2(��demģ���е�����ֵΪdem_const_xx * 2) */
        unsigned long  uddwa_dith_en_apt : 1;  /* bit[4]  : Reserved */
        unsigned long  dem_dwa_en_apt    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                            0��ʹ��CLAģʽ(Ĭ��)
                                                            1��ʹ��DWAģʽ  */
        unsigned long  dem_lsb_bp_apt    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                            0��DEM LSB ��(Ĭ��)
                                                            1��DEM LSB bypass */
        unsigned long  dem_msb_bp_apt    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                            0��DEM MSB ��(Ĭ��)
                                                            1��DEM MSB bypass */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_TX_APT_DIG_2_UNION;
#define ABB_TX_APT_DIG_2_tx_q_pd_apt_START        (0)
#define ABB_TX_APT_DIG_2_tx_q_pd_apt_END          (0)
#define ABB_TX_APT_DIG_2_tx_i_pd_apt_START        (1)
#define ABB_TX_APT_DIG_2_tx_i_pd_apt_END          (1)
#define ABB_TX_APT_DIG_2_dem_const_apt_START      (2)
#define ABB_TX_APT_DIG_2_dem_const_apt_END        (3)
#define ABB_TX_APT_DIG_2_uddwa_dith_en_apt_START  (4)
#define ABB_TX_APT_DIG_2_uddwa_dith_en_apt_END    (4)
#define ABB_TX_APT_DIG_2_dem_dwa_en_apt_START     (5)
#define ABB_TX_APT_DIG_2_dem_dwa_en_apt_END       (5)
#define ABB_TX_APT_DIG_2_dem_lsb_bp_apt_START     (6)
#define ABB_TX_APT_DIG_2_dem_lsb_bp_apt_END       (6)
#define ABB_TX_APT_DIG_2_dem_msb_bp_apt_START     (7)
#define ABB_TX_APT_DIG_2_dem_msb_bp_apt_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_APT_DIG_3_UNION
 �ṹ˵��  : tx_apt_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x19����ֵ:0x02�����:8
 �Ĵ���˵��: TX APTģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_apt_dig_3_reg;
    struct
    {
        unsigned long  tx_cfr_bp_apt  : 1;  /* bit[0]  : Reserved */
        unsigned long  tx_ddr_sdr_apt : 1;  /* bit[1]  : TX��DBB���ݽӿ�ʱ�����ã�
                                                         1'b0��SDR�ӿڣ�
                                                         1'b1��DDR�ӿڡ� */
        unsigned long  reserved       : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_APT_DIG_3_UNION;
#define ABB_TX_APT_DIG_3_tx_cfr_bp_apt_START   (0)
#define ABB_TX_APT_DIG_3_tx_cfr_bp_apt_END     (0)
#define ABB_TX_APT_DIG_3_tx_ddr_sdr_apt_START  (1)
#define ABB_TX_APT_DIG_3_tx_ddr_sdr_apt_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_RX_CA_DIG_1_UNION
 �ṹ˵��  : rx_ca_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x1A����ֵ:0xA0�����:8
 �Ĵ���˵��: RX CAģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      rx_ca_dig_1_reg;
    struct
    {
        unsigned long  rx_comp_sel_ca : 1;  /* bit[0]  : RXͨ�������˲��������̶�ϵ��ѡ��
                                                         0���̶�ϵ��1
                                                         1���̶�ϵ��2 */
        unsigned long  rx_comp_fix_ca : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                         0��ϵ�����̶����ɼĴ�������
                                                         1��ϵ���̶� */
        unsigned long  rx_hb_bp_ca    : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                         0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                         1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  rx_rate_ca     : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                             2G,   3G_SC,  4G,  3G_DC,   TDS,   CA
                                                         00�� 2.167M,15.36M,61.44M,30.72M,30.72M,122.88M(Ĭ��)
                                                         01�� ------,------,30.72M,15.36M,10.24M,------
                                                         10�� ------,------,15.36M,------,------,------
                                                         11�� ------,------, 7.68M,------,------,------ */
        unsigned long  rx_mode_dig_ca : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                         000��2G
                                                         001��3G_SC
                                                         010��4G &amp; ET &amp; APT
                                                         011��3G_DC
                                                         100��TDS
                                                         Others��CA(Ĭ��) */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CA_DIG_1_UNION;
#define ABB_RX_CA_DIG_1_rx_comp_sel_ca_START  (0)
#define ABB_RX_CA_DIG_1_rx_comp_sel_ca_END    (0)
#define ABB_RX_CA_DIG_1_rx_comp_fix_ca_START  (1)
#define ABB_RX_CA_DIG_1_rx_comp_fix_ca_END    (1)
#define ABB_RX_CA_DIG_1_rx_hb_bp_ca_START     (2)
#define ABB_RX_CA_DIG_1_rx_hb_bp_ca_END       (2)
#define ABB_RX_CA_DIG_1_rx_rate_ca_START      (3)
#define ABB_RX_CA_DIG_1_rx_rate_ca_END        (4)
#define ABB_RX_CA_DIG_1_rx_mode_dig_ca_START  (5)
#define ABB_RX_CA_DIG_1_rx_mode_dig_ca_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CA_DIG_2_UNION
 �ṹ˵��  : rx_ca_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x1B����ֵ:0x23�����:8
 �Ĵ���˵��: RX CAģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      rx_ca_dig_2_reg;
    struct
    {
        unsigned long  rxa_pd_ca     : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                        0����CLOCK GATING
                                                        1��CLOCK GATING(Ĭ��)
                                                        (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_ca     : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                        0����CLOCK GATING
                                                        1��CLOCK GATING(Ĭ��)
                                                        (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_ca   : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                        00��gainΪ0.5(Ĭ��)
                                                        01��gainΪ0.75
                                                        10��gainΪ0.85
                                                        11��Reserved */
        unsigned long  rx_comp_bp_ca : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                        0����bypass(Ĭ��)
                                                        1��bypass */
        unsigned long  tx_cfr_bp_ca  : 1;  /* bit[5]  : TXͨ��CFR bypass���ƣ�
                                                        0����bypass
                                                        1��bypass(Ĭ��) */
        unsigned long  reserved      : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CA_DIG_2_UNION;
#define ABB_RX_CA_DIG_2_rxa_pd_ca_START      (0)
#define ABB_RX_CA_DIG_2_rxa_pd_ca_END        (0)
#define ABB_RX_CA_DIG_2_rxb_pd_ca_START      (1)
#define ABB_RX_CA_DIG_2_rxb_pd_ca_END        (1)
#define ABB_RX_CA_DIG_2_gain_sel_ca_START    (2)
#define ABB_RX_CA_DIG_2_gain_sel_ca_END      (3)
#define ABB_RX_CA_DIG_2_rx_comp_bp_ca_START  (4)
#define ABB_RX_CA_DIG_2_rx_comp_bp_ca_END    (4)
#define ABB_RX_CA_DIG_2_tx_cfr_bp_ca_START   (5)
#define ABB_RX_CA_DIG_2_tx_cfr_bp_ca_END     (5)


/*****************************************************************************
 �ṹ��    : ABB_TX_CA_DIG_1_UNION
 �ṹ˵��  : tx_ca_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x1C����ֵ:0x80�����:8
 �Ĵ���˵��: TX CAģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_ca_dig_1_reg;
    struct
    {
        unsigned long  tx_comp_bp_ca  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                         0����bypass(Ĭ��)
                                                         1��bypass */
        unsigned long  tx_hb_bp_ca    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                         0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                         1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  tx_rate_ca     : 3;  /* bit[2-4]: TXͨ��CIC�˲���������ʿ��ƣ�
                                                              2G,     3G,     4G,      TDS,      CA
                                                             (78M) (153.6M) (307.2M) (153.6M) (614.4M)
                                                         0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,122.88MHz(Ĭ��)
                                                         1��2.16MHz,15.36MHz,30.72MHz,10.24MHz,--------
                                                         2��-------,--------,15.36MHz,--------,--------
                                                         3��-------,--------, 7.68MHz,--------,--------
                                                         4��-------,--------, 3.84MHz,--------,--------
                                                         Others��Reserved */
        unsigned long  tx_mode_dig_ca : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                         000��2G
                                                         001��3G
                                                         010��4G &amp; ET &amp; APT
                                                         011��TDS
                                                         others��CA(Ĭ��) */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CA_DIG_1_UNION;
#define ABB_TX_CA_DIG_1_tx_comp_bp_ca_START   (0)
#define ABB_TX_CA_DIG_1_tx_comp_bp_ca_END     (0)
#define ABB_TX_CA_DIG_1_tx_hb_bp_ca_START     (1)
#define ABB_TX_CA_DIG_1_tx_hb_bp_ca_END       (1)
#define ABB_TX_CA_DIG_1_tx_rate_ca_START      (2)
#define ABB_TX_CA_DIG_1_tx_rate_ca_END        (4)
#define ABB_TX_CA_DIG_1_tx_mode_dig_ca_START  (5)
#define ABB_TX_CA_DIG_1_tx_mode_dig_ca_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CA_DIG_2_UNION
 �ṹ˵��  : tx_ca_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x1D����ֵ:0x03�����:8
 �Ĵ���˵��: TX CAģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_ca_dig_2_reg;
    struct
    {
        unsigned long  tx_q_pd_ca       : 1;  /* bit[0]: TXͨ��Q·CLOCK GATING���ƣ�
                                                         0����CLOCK GATING
                                                         1��CLOCK GATING(Ĭ��)
                                                         (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  tx_i_pd_ca       : 1;  /* bit[1]: TXͨ��I·CLOCK GATING���ƣ�
                                                         0����CLOCK GATING
                                                         1��CLOCK GATING(Ĭ��)
                                                         (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  dem_const_ca     : 1;  /* bit[2]: TXͨ��DEM constϵ����
                                                         0��2(Ĭ��)
                                                         1��4 */
        unsigned long  uddwa_dith_en_ca : 1;  /* bit[3]: TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                         0����ʹ��
                                                         1��ʹ�� */
        unsigned long  dither_en_ca     : 1;  /* bit[4]: TXͨ��SDM Dither���ƣ�
                                                         0����ʹ��
                                                         1��ʹ�� */
        unsigned long  dem_dwa_en_ca    : 1;  /* bit[5]: TXͨ��DEMģʽ���ƣ�
                                                         0��ʹ��CLAģʽ(Ĭ��)
                                                         1��ʹ��DWAģʽ  */
        unsigned long  dem_lsb_bp_ca    : 1;  /* bit[6]: TXͨ��DEM LSB bypass��
                                                         0��DEM LSB ��(Ĭ��)
                                                         1��DEM LSB bypass */
        unsigned long  dem_msb_bp_ca    : 1;  /* bit[7]: TXͨ��DEM MSB bypass��
                                                         0��DEM MSB��(Ĭ��)
                                                         1��DEM MSB bypass */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CA_DIG_2_UNION;
#define ABB_TX_CA_DIG_2_tx_q_pd_ca_START        (0)
#define ABB_TX_CA_DIG_2_tx_q_pd_ca_END          (0)
#define ABB_TX_CA_DIG_2_tx_i_pd_ca_START        (1)
#define ABB_TX_CA_DIG_2_tx_i_pd_ca_END          (1)
#define ABB_TX_CA_DIG_2_dem_const_ca_START      (2)
#define ABB_TX_CA_DIG_2_dem_const_ca_END        (2)
#define ABB_TX_CA_DIG_2_uddwa_dith_en_ca_START  (3)
#define ABB_TX_CA_DIG_2_uddwa_dith_en_ca_END    (3)
#define ABB_TX_CA_DIG_2_dither_en_ca_START      (4)
#define ABB_TX_CA_DIG_2_dither_en_ca_END        (4)
#define ABB_TX_CA_DIG_2_dem_dwa_en_ca_START     (5)
#define ABB_TX_CA_DIG_2_dem_dwa_en_ca_END       (5)
#define ABB_TX_CA_DIG_2_dem_lsb_bp_ca_START     (6)
#define ABB_TX_CA_DIG_2_dem_lsb_bp_ca_END       (6)
#define ABB_TX_CA_DIG_2_dem_msb_bp_ca_START     (7)
#define ABB_TX_CA_DIG_2_dem_msb_bp_ca_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CA_DIG_3_UNION
 �ṹ˵��  : tx_ca_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x1E����ֵ:0x02�����:8
 �Ĵ���˵��: TX CAģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_ca_dig_3_reg;
    struct
    {
        unsigned long  tx_cfr_bp_ca  : 1;  /* bit[0]  : Reserved */
        unsigned long  tx_ddr_sdr_ca : 1;  /* bit[1]  : TX��DBB���ݽӿ�ʱ�����ã�
                                                        1'b0��SDR�ӿڣ�
                                                        1'b1��DDR�ӿڡ� */
        unsigned long  reserved      : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CA_DIG_3_UNION;
#define ABB_TX_CA_DIG_3_tx_cfr_bp_ca_START   (0)
#define ABB_TX_CA_DIG_3_tx_cfr_bp_ca_END     (0)
#define ABB_TX_CA_DIG_3_tx_ddr_sdr_ca_START  (1)
#define ABB_TX_CA_DIG_3_tx_ddr_sdr_ca_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_RX_IDLE_DIG_1_UNION
 �ṹ˵��  : rx_idle_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x1F����ֵ:0x40�����:8
 �Ĵ���˵��: RX IDLEģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      rx_idle_dig_1_reg;
    struct
    {
        unsigned long  rx_comp_sel_idle : 1;  /* bit[0]  : Reserved */
        unsigned long  rx_comp_fix_idle : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                           0��ϵ�����̶����ɼĴ�������
                                                           1��ϵ���̶� */
        unsigned long  rx_hb_bp_idle    : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                           0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                           1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  rx_rate_idle     : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                               2G,   3G_SC,    4G,   3G_DC,      
                                                           00�� 2.167M,15.36M, 61.44M,30.72M(Ĭ��)
                                                           01�� 4.33MHz,------,30.72M,------
                                                           10�� ------, ------,15.36M,------
                                                           11�� ------, ------, 7.68M,------ */
        unsigned long  rx_mode_dig_idle : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                           000��2G(Ĭ��)
                                                           001��3G_SC
                                                           010��4G
                                                           011��3G_DC
                                                           Others��reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_DIG_1_UNION;
#define ABB_RX_IDLE_DIG_1_rx_comp_sel_idle_START  (0)
#define ABB_RX_IDLE_DIG_1_rx_comp_sel_idle_END    (0)
#define ABB_RX_IDLE_DIG_1_rx_comp_fix_idle_START  (1)
#define ABB_RX_IDLE_DIG_1_rx_comp_fix_idle_END    (1)
#define ABB_RX_IDLE_DIG_1_rx_hb_bp_idle_START     (2)
#define ABB_RX_IDLE_DIG_1_rx_hb_bp_idle_END       (2)
#define ABB_RX_IDLE_DIG_1_rx_rate_idle_START      (3)
#define ABB_RX_IDLE_DIG_1_rx_rate_idle_END        (4)
#define ABB_RX_IDLE_DIG_1_rx_mode_dig_idle_START  (5)
#define ABB_RX_IDLE_DIG_1_rx_mode_dig_idle_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_IDLE_DIG_2_UNION
 �ṹ˵��  : rx_idle_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x20����ֵ:0x43�����:8
 �Ĵ���˵��: RX IDLEģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      rx_idle_dig_2_reg;
    struct
    {
        unsigned long  rxa_pd_idle     : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                          0����CLOCK GATING
                                                          1��CLOCK GATING(Ĭ��)
                                                          (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_idle     : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                          0����CLOCK GATING
                                                          1��CLOCK GATING(Ĭ��)
                                                          (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_idle   : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                          00��gainΪ0.5(Ĭ��)
                                                          01��gainΪ0.75
                                                          10��gainΪ0.85
                                                          11��Reserved */
        unsigned long  rx_comp_bp_idle : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                          0����bypass(Ĭ��)
                                                          1��bypass */
        unsigned long  rx_clk_inv_idle : 1;  /* bit[5]  : Reserved */
        unsigned long  rx_ddr_sdr_idle : 1;  /* bit[6]  : RX��DBB���ݽӿ�ʱ�����ã�
                                                          1'b0��SDR�ӿڣ�
                                                          1'b1��DDR�ӿڡ� */
        unsigned long  reserved        : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_DIG_2_UNION;
#define ABB_RX_IDLE_DIG_2_rxa_pd_idle_START      (0)
#define ABB_RX_IDLE_DIG_2_rxa_pd_idle_END        (0)
#define ABB_RX_IDLE_DIG_2_rxb_pd_idle_START      (1)
#define ABB_RX_IDLE_DIG_2_rxb_pd_idle_END        (1)
#define ABB_RX_IDLE_DIG_2_gain_sel_idle_START    (2)
#define ABB_RX_IDLE_DIG_2_gain_sel_idle_END      (3)
#define ABB_RX_IDLE_DIG_2_rx_comp_bp_idle_START  (4)
#define ABB_RX_IDLE_DIG_2_rx_comp_bp_idle_END    (4)
#define ABB_RX_IDLE_DIG_2_rx_clk_inv_idle_START  (5)
#define ABB_RX_IDLE_DIG_2_rx_clk_inv_idle_END    (5)
#define ABB_RX_IDLE_DIG_2_rx_ddr_sdr_idle_START  (6)
#define ABB_RX_IDLE_DIG_2_rx_ddr_sdr_idle_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_TX_IDLE_DIG_1_UNION
 �ṹ˵��  : tx_idle_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x21����ֵ:0x40�����:8
 �Ĵ���˵��: TX IDLEģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_idle_dig_1_reg;
    struct
    {
        unsigned long  tx_comp_bp_idle  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                           0����bypass(Ĭ��)
                                                           1��bypass */
        unsigned long  tx_hb_bp_idle    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                           0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                           1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  tx_rate_idle     : 3;  /* bit[2-4]: TXͨ��CIC�˲���������ʿ��ƣ�
                                                                2G,     3G,     4G,     
                                                               (78M) (153.6M) (307.2M) 
                                                           0��4.33MHz,30.72MHz,61.44MHz(Ĭ��)
                                                           1��2.16MHz,15.36MHz,30.72MHz
                                                           2��-------,--------,15.36MHz
                                                           3��-------,--------, 7.68MHz
                                                           4��-------,--------, 3.84MHz
                                                           Others��Reserved */
        unsigned long  tx_mode_dig_idle : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                           000��2G
                                                           001��3G
                                                           010��4G &amp; ET &amp; APT(Ĭ��)
                                                           Others��reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_DIG_1_UNION;
#define ABB_TX_IDLE_DIG_1_tx_comp_bp_idle_START   (0)
#define ABB_TX_IDLE_DIG_1_tx_comp_bp_idle_END     (0)
#define ABB_TX_IDLE_DIG_1_tx_hb_bp_idle_START     (1)
#define ABB_TX_IDLE_DIG_1_tx_hb_bp_idle_END       (1)
#define ABB_TX_IDLE_DIG_1_tx_rate_idle_START      (2)
#define ABB_TX_IDLE_DIG_1_tx_rate_idle_END        (4)
#define ABB_TX_IDLE_DIG_1_tx_mode_dig_idle_START  (5)
#define ABB_TX_IDLE_DIG_1_tx_mode_dig_idle_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_IDLE_DIG_2_UNION
 �ṹ˵��  : tx_idle_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x22����ֵ:0x4B�����:8
 �Ĵ���˵��: TX IDLEģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_idle_dig_2_reg;
    struct
    {
        unsigned long  tx_q_pd_idle       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                             0����CLOCK GATING
                                                             1��CLOCK GATING(Ĭ��)
                                                             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  tx_i_pd_idle       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                             0����CLOCK GATING
                                                             1��CLOCK GATING(Ĭ��)
                                                             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  dem_const_idle     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����Ĭ��ֵ2(��ģ����*2�� */
        unsigned long  uddwa_dith_en_idle : 1;  /* bit[4]  : Reserved */
        unsigned long  dem_dwa_en_idle    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                             0��ʹ��CLAģʽ(Ĭ��)
                                                             1��ʹ��DWAģʽ  */
        unsigned long  tx_ddr_sdr_idle    : 1;  /* bit[6]  : 1'b0��SDR
                                                             1'b1��DDR */
        unsigned long  reserved           : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_DIG_2_UNION;
#define ABB_TX_IDLE_DIG_2_tx_q_pd_idle_START        (0)
#define ABB_TX_IDLE_DIG_2_tx_q_pd_idle_END          (0)
#define ABB_TX_IDLE_DIG_2_tx_i_pd_idle_START        (1)
#define ABB_TX_IDLE_DIG_2_tx_i_pd_idle_END          (1)
#define ABB_TX_IDLE_DIG_2_dem_const_idle_START      (2)
#define ABB_TX_IDLE_DIG_2_dem_const_idle_END        (3)
#define ABB_TX_IDLE_DIG_2_uddwa_dith_en_idle_START  (4)
#define ABB_TX_IDLE_DIG_2_uddwa_dith_en_idle_END    (4)
#define ABB_TX_IDLE_DIG_2_dem_dwa_en_idle_START     (5)
#define ABB_TX_IDLE_DIG_2_dem_dwa_en_idle_END       (5)
#define ABB_TX_IDLE_DIG_2_tx_ddr_sdr_idle_START     (6)
#define ABB_TX_IDLE_DIG_2_tx_ddr_sdr_idle_END       (6)


/*****************************************************************************
 �ṹ��    : ABB_TX_IDLE_DIG_3_UNION
 �ṹ˵��  : tx_idle_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x23����ֵ:0x02�����:8
 �Ĵ���˵��: TX IDLEģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      tx_idle_dig_3_reg;
    struct
    {
        unsigned long  tx_cfr_bp_idle  : 1;  /* bit[0]  : Reserved */
        unsigned long  tx_ddr_sdr_idle : 1;  /* bit[1]  : TX��DBB���ݽӿ�ʱ�����ã�
                                                          1'b0��SDR�ӿڣ�
                                                          1'b1��DDR�ӿڡ� */
        unsigned long  reserved        : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_DIG_3_UNION;
#define ABB_TX_IDLE_DIG_3_tx_cfr_bp_idle_START   (0)
#define ABB_TX_IDLE_DIG_3_tx_cfr_bp_idle_END     (0)
#define ABB_TX_IDLE_DIG_3_tx_ddr_sdr_idle_START  (1)
#define ABB_TX_IDLE_DIG_3_tx_ddr_sdr_idle_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_RX_2G_ANA_1_UNION
 �ṹ˵��  : rx_2g_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x24����ֵ:0xF6�����:8
 �Ĵ���˵��: RX 2G���üĴ����������߿��߼��������reg_analog_wr00��
*****************************************************************************/
typedef union
{
    unsigned long      rx_2g_ana_1_reg;
    struct
    {
        unsigned long  DEM_MOD_B0_2G  : 1;  /* bit[0]  : Reserved */
        unsigned long  RX_MODE_CLK_2G : 2;  /* bit[1-2]: ģʽ���ƣ�
                                                         00��4G 
                                                         01��3G
                                                         10��3G_DC
                                                         11��2G(Ĭ��) */
        unsigned long  DEM_MOD_B1_2G  : 1;  /* bit[3]  : Reserved */
        unsigned long  RXB_Q_PD_2G    : 1;  /* bit[4]  : RXB_Q ADC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!RXQ_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXB_I_PD_2G    : 1;  /* bit[5]  : RXB_I ADC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXA_Q_PD_2G    : 1;  /* bit[6]  : RXA_Q ADC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!RXB_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  RXA_I_PD_2G    : 1;  /* bit[7]  : RXA_I ADC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_ANA_1_UNION;
#define ABB_RX_2G_ANA_1_DEM_MOD_B0_2G_START   (0)
#define ABB_RX_2G_ANA_1_DEM_MOD_B0_2G_END     (0)
#define ABB_RX_2G_ANA_1_RX_MODE_CLK_2G_START  (1)
#define ABB_RX_2G_ANA_1_RX_MODE_CLK_2G_END    (2)
#define ABB_RX_2G_ANA_1_DEM_MOD_B1_2G_START   (3)
#define ABB_RX_2G_ANA_1_DEM_MOD_B1_2G_END     (3)
#define ABB_RX_2G_ANA_1_RXB_Q_PD_2G_START     (4)
#define ABB_RX_2G_ANA_1_RXB_Q_PD_2G_END       (4)
#define ABB_RX_2G_ANA_1_RXB_I_PD_2G_START     (5)
#define ABB_RX_2G_ANA_1_RXB_I_PD_2G_END       (5)
#define ABB_RX_2G_ANA_1_RXA_Q_PD_2G_START     (6)
#define ABB_RX_2G_ANA_1_RXA_Q_PD_2G_END       (6)
#define ABB_RX_2G_ANA_1_RXA_I_PD_2G_START     (7)
#define ABB_RX_2G_ANA_1_RXA_I_PD_2G_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_2G_ANA_1_UNION
 �ṹ˵��  : tx_2g_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x26����ֵ:0x3F�����:8
 �Ĵ���˵��: TX 2G���üĴ����������߿��߼��������reg_analog_wr48��
*****************************************************************************/
typedef union
{
    unsigned long      tx_2g_ana_1_reg;
    struct
    {
        unsigned long  TX_MODE_CLK_2G : 2;  /* bit[0-1]: ģʽ���ƣ�
                                                         00��4G &amp; ET &amp; APT
                                                         01��3G 
                                                         10��--
                                                         11��2G(Ĭ��) */
        unsigned long  TX_Q_PD_A_2G   : 1;  /* bit[2]  : TX_Q DAC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_I_PD_A_2G   : 1;  /* bit[3]  : TX_I DAC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!TX_I_PD)|WG_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_DIV_MODE_2G : 2;  /* bit[4-5]: TX Mode ʱ�ӿ��ƣ�
                                                         00: 1��Ƶ
                                                         01: 2��Ƶ
                                                         10: 3��Ƶ
                                                         11: 4��Ƶ(Ĭ��) */
        unsigned long  FC_2G          : 2;  /* bit[6-7]: TX filter��ֹƵ��ѡ��
                                                         00: 10MHz(Ĭ��)
                                                         01: 20MHz;
                                                         11:40MHz;
                                                         10:reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_ANA_1_UNION;
#define ABB_TX_2G_ANA_1_TX_MODE_CLK_2G_START  (0)
#define ABB_TX_2G_ANA_1_TX_MODE_CLK_2G_END    (1)
#define ABB_TX_2G_ANA_1_TX_Q_PD_A_2G_START    (2)
#define ABB_TX_2G_ANA_1_TX_Q_PD_A_2G_END      (2)
#define ABB_TX_2G_ANA_1_TX_I_PD_A_2G_START    (3)
#define ABB_TX_2G_ANA_1_TX_I_PD_A_2G_END      (3)
#define ABB_TX_2G_ANA_1_TX_DIV_MODE_2G_START  (4)
#define ABB_TX_2G_ANA_1_TX_DIV_MODE_2G_END    (5)
#define ABB_TX_2G_ANA_1_FC_2G_START           (6)
#define ABB_TX_2G_ANA_1_FC_2G_END             (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_3G_ANA_1_UNION
 �ṹ˵��  : rx_3g_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x28����ֵ:0xF2�����:8
 �Ĵ���˵��: RX 3G���üĴ����������߿��߼��������reg_analog_wr00��
*****************************************************************************/
typedef union
{
    unsigned long      rx_3g_ana_1_reg;
    struct
    {
        unsigned long  DEM_MOD_B0_3G  : 1;  /* bit[0]  : Reserved */
        unsigned long  RX_MODE_CLK_3G : 2;  /* bit[1-2]: ģʽ���ƣ�
                                                         00��4G 
                                                         01��3G
                                                         10��3G_DC
                                                         11��2G(Ĭ��) */
        unsigned long  DEM_MOD_B1_3G  : 1;  /* bit[3]  : Reserved */
        unsigned long  RXB_Q_PD_3G    : 1;  /* bit[4]  : RXB_Q ADC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!RXB_Q_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXB_I_PD_3G    : 1;  /* bit[5]  : RXB_I ADC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXA_Q_PD_3G    : 1;  /* bit[6]  : RXA_Q ADC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!RXA_Q_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  RXA_I_PD_3G    : 1;  /* bit[7]  : RXA_I ADC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_3G_ANA_1_UNION;
#define ABB_RX_3G_ANA_1_DEM_MOD_B0_3G_START   (0)
#define ABB_RX_3G_ANA_1_DEM_MOD_B0_3G_END     (0)
#define ABB_RX_3G_ANA_1_RX_MODE_CLK_3G_START  (1)
#define ABB_RX_3G_ANA_1_RX_MODE_CLK_3G_END    (2)
#define ABB_RX_3G_ANA_1_DEM_MOD_B1_3G_START   (3)
#define ABB_RX_3G_ANA_1_DEM_MOD_B1_3G_END     (3)
#define ABB_RX_3G_ANA_1_RXB_Q_PD_3G_START     (4)
#define ABB_RX_3G_ANA_1_RXB_Q_PD_3G_END       (4)
#define ABB_RX_3G_ANA_1_RXB_I_PD_3G_START     (5)
#define ABB_RX_3G_ANA_1_RXB_I_PD_3G_END       (5)
#define ABB_RX_3G_ANA_1_RXA_Q_PD_3G_START     (6)
#define ABB_RX_3G_ANA_1_RXA_Q_PD_3G_END       (6)
#define ABB_RX_3G_ANA_1_RXA_I_PD_3G_START     (7)
#define ABB_RX_3G_ANA_1_RXA_I_PD_3G_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_3G_ANA_1_UNION
 �ṹ˵��  : tx_3g_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x2A����ֵ:0x1D�����:8
 �Ĵ���˵��: TX 3G���üĴ����������߿��߼��������reg_analog_wr48��
*****************************************************************************/
typedef union
{
    unsigned long      tx_3g_ana_1_reg;
    struct
    {
        unsigned long  TX_MODE_CLK_3G : 2;  /* bit[0-1]: ģʽ���ƣ�
                                                         00��4G &amp; ET &amp; APT
                                                         01��3G (Ĭ��)
                                                         10��--
                                                         11��2G */
        unsigned long  TX_Q_PD_A_3G   : 1;  /* bit[2]  : TX_Q DAC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_I_PD_A_3G   : 1;  /* bit[3]  : TX_I DAC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!TX_I_PD)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_DIV_MODE_3G : 2;  /* bit[4-5]: TX Mode ʱ�ӿ��ƣ�
                                                         00: 1��Ƶ
                                                         01: 2��Ƶ(Ĭ��)
                                                         10: 3��Ƶ
                                                         11: 4��Ƶ */
        unsigned long  FC_3G          : 2;  /* bit[6-7]: TX filter��ֹƵ��ѡ��
                                                         00: 10MHz(Ĭ��)
                                                         01: 20MHz;
                                                         11:40MHz;
                                                         10:reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_3G_ANA_1_UNION;
#define ABB_TX_3G_ANA_1_TX_MODE_CLK_3G_START  (0)
#define ABB_TX_3G_ANA_1_TX_MODE_CLK_3G_END    (1)
#define ABB_TX_3G_ANA_1_TX_Q_PD_A_3G_START    (2)
#define ABB_TX_3G_ANA_1_TX_Q_PD_A_3G_END      (2)
#define ABB_TX_3G_ANA_1_TX_I_PD_A_3G_START    (3)
#define ABB_TX_3G_ANA_1_TX_I_PD_A_3G_END      (3)
#define ABB_TX_3G_ANA_1_TX_DIV_MODE_3G_START  (4)
#define ABB_TX_3G_ANA_1_TX_DIV_MODE_3G_END    (5)
#define ABB_TX_3G_ANA_1_FC_3G_START           (6)
#define ABB_TX_3G_ANA_1_FC_3G_END             (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_4G_ANA_1_UNION
 �ṹ˵��  : rx_4g_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x2C����ֵ:0xF0�����:8
 �Ĵ���˵��: RX 4G���üĴ����������߿��߼��������reg_analog_wr00��
*****************************************************************************/
typedef union
{
    unsigned long      rx_4g_ana_1_reg;
    struct
    {
        unsigned long  DEM_MOD_B0_4G  : 1;  /* bit[0]  : Reserved */
        unsigned long  RX_MODE_CLK_4G : 2;  /* bit[1-2]: ģʽ���ƣ�
                                                         00��4G (Ĭ��)
                                                         01��3G
                                                         10��3G_DC
                                                         11��2G */
        unsigned long  DEM_MOD_B1_4G  : 1;  /* bit[3]  : Reserved */
        unsigned long  RXB_Q_PD_4G    : 1;  /* bit[4]  : RXB_Q ADC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!RXB_Q_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXB_I_PD_4G    : 1;  /* bit[5]  : RXB_I ADC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXA_Q_PD_4G    : 1;  /* bit[6]  : RXA_Q ADC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!RXA_Q_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  RXA_I_PD_4G    : 1;  /* bit[7]  : RXA_I ADC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_4G_ANA_1_UNION;
#define ABB_RX_4G_ANA_1_DEM_MOD_B0_4G_START   (0)
#define ABB_RX_4G_ANA_1_DEM_MOD_B0_4G_END     (0)
#define ABB_RX_4G_ANA_1_RX_MODE_CLK_4G_START  (1)
#define ABB_RX_4G_ANA_1_RX_MODE_CLK_4G_END    (2)
#define ABB_RX_4G_ANA_1_DEM_MOD_B1_4G_START   (3)
#define ABB_RX_4G_ANA_1_DEM_MOD_B1_4G_END     (3)
#define ABB_RX_4G_ANA_1_RXB_Q_PD_4G_START     (4)
#define ABB_RX_4G_ANA_1_RXB_Q_PD_4G_END       (4)
#define ABB_RX_4G_ANA_1_RXB_I_PD_4G_START     (5)
#define ABB_RX_4G_ANA_1_RXB_I_PD_4G_END       (5)
#define ABB_RX_4G_ANA_1_RXA_Q_PD_4G_START     (6)
#define ABB_RX_4G_ANA_1_RXA_Q_PD_4G_END       (6)
#define ABB_RX_4G_ANA_1_RXA_I_PD_4G_START     (7)
#define ABB_RX_4G_ANA_1_RXA_I_PD_4G_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_4G_ANA_1_UNION
 �ṹ˵��  : tx_4g_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x2E����ֵ:0x4C�����:8
 �Ĵ���˵��: TX 4G���üĴ����������߿��߼��������reg_analog_wr48��
*****************************************************************************/
typedef union
{
    unsigned long      tx_4g_ana_1_reg;
    struct
    {
        unsigned long  TX_MODE_CLK_4G : 2;  /* bit[0-1]: ģʽ���ƣ�
                                                         00��4G &amp; ET &amp; APT(Ĭ��)
                                                         01��3G 
                                                         10��--
                                                         11��2G */
        unsigned long  TX_Q_PD_A_4G   : 1;  /* bit[2]  : TX_Q DAC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_I_PD_A_4G   : 1;  /* bit[3]  : TX_I DAC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!TX_I_PD)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_DIV_MODE_4G : 2;  /* bit[4-5]: TX Mode ʱ�ӿ��ƣ�
                                                         00: 1��Ƶ(Ĭ��)
                                                         01: 2��Ƶ
                                                         10: 3��Ƶ
                                                         11: 4��Ƶ */
        unsigned long  FC_4G          : 2;  /* bit[6-7]: TX filter��ֹƵ��ѡ��
                                                         00: 10MHz;
                                                         01: 20MHz;(Ĭ��)
                                                         11:40MHz;
                                                         10:reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_4G_ANA_1_UNION;
#define ABB_TX_4G_ANA_1_TX_MODE_CLK_4G_START  (0)
#define ABB_TX_4G_ANA_1_TX_MODE_CLK_4G_END    (1)
#define ABB_TX_4G_ANA_1_TX_Q_PD_A_4G_START    (2)
#define ABB_TX_4G_ANA_1_TX_Q_PD_A_4G_END      (2)
#define ABB_TX_4G_ANA_1_TX_I_PD_A_4G_START    (3)
#define ABB_TX_4G_ANA_1_TX_I_PD_A_4G_END      (3)
#define ABB_TX_4G_ANA_1_TX_DIV_MODE_4G_START  (4)
#define ABB_TX_4G_ANA_1_TX_DIV_MODE_4G_END    (5)
#define ABB_TX_4G_ANA_1_FC_4G_START           (6)
#define ABB_TX_4G_ANA_1_FC_4G_END             (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_ANA_1_UNION
 �ṹ˵��  : rx_tds_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x30����ֵ:0xF4�����:8
 �Ĵ���˵��: RX TDS���üĴ����������߿��߼��������reg_analog_wr00��
*****************************************************************************/
typedef union
{
    unsigned long      rx_tds_ana_1_reg;
    struct
    {
        unsigned long  DEM_MOD_B0_TDS  : 1;  /* bit[0]  : RX DEM Mode Selection,bit 0
                                                          000: DWA
                                                          001: CLA1
                                                          010: CLA2
                                                          011: CLA3
                                                          100: CLA4
                                                          101: CLA5
                                                          110: CLA6
                                                          111: CLA7 */
        unsigned long  RX_MODE_CLK_TDS : 2;  /* bit[1-2]: ģʽ���ƣ�
                                                          00��4G &amp; ET &amp; APT
                                                          01��3G
                                                          10��3G_DC &amp; TDS(Ĭ��)
                                                          11��2G */
        unsigned long  DEM_MOD_B1_TDS  : 1;  /* bit[3]  : RX DEM Mode Selection,bit 1
                                                          000: DWA
                                                          001: CLA1
                                                          010: CLA2
                                                          011: CLA3
                                                          100: CLA4
                                                          101: CLA5
                                                          110: CLA6
                                                          111: CLA7 */
        unsigned long  RXB_Q_PD_TDS    : 1;  /* bit[4]  : RXB_Q ADC Power Down����
                                                          0:Power On
                                                          1:Power Down(Ĭ��)
                                                          (!RXB_Q_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXB_I_PD_TDS    : 1;  /* bit[5]  : RXB_I ADC Power Down����
                                                          0:Power On
                                                          1:Power Down(Ĭ��)
                                                          (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXA_Q_PD_TDS    : 1;  /* bit[6]  : RXA_Q ADC Power Down����
                                                          0:Power On
                                                          1:Power Down(Ĭ��)
                                                          (!RXA_Q_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  RXA_I_PD_TDS    : 1;  /* bit[7]  : RXA_I ADC Power Down����
                                                          0:Power On
                                                          1:Power Down(Ĭ��)
                                                          (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_ANA_1_UNION;
#define ABB_RX_TDS_ANA_1_DEM_MOD_B0_TDS_START   (0)
#define ABB_RX_TDS_ANA_1_DEM_MOD_B0_TDS_END     (0)
#define ABB_RX_TDS_ANA_1_RX_MODE_CLK_TDS_START  (1)
#define ABB_RX_TDS_ANA_1_RX_MODE_CLK_TDS_END    (2)
#define ABB_RX_TDS_ANA_1_DEM_MOD_B1_TDS_START   (3)
#define ABB_RX_TDS_ANA_1_DEM_MOD_B1_TDS_END     (3)
#define ABB_RX_TDS_ANA_1_RXB_Q_PD_TDS_START     (4)
#define ABB_RX_TDS_ANA_1_RXB_Q_PD_TDS_END       (4)
#define ABB_RX_TDS_ANA_1_RXB_I_PD_TDS_START     (5)
#define ABB_RX_TDS_ANA_1_RXB_I_PD_TDS_END       (5)
#define ABB_RX_TDS_ANA_1_RXA_Q_PD_TDS_START     (6)
#define ABB_RX_TDS_ANA_1_RXA_Q_PD_TDS_END       (6)
#define ABB_RX_TDS_ANA_1_RXA_I_PD_TDS_START     (7)
#define ABB_RX_TDS_ANA_1_RXA_I_PD_TDS_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_TDS_ANA_1_UNION
 �ṹ˵��  : tx_tds_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x32����ֵ:0x39�����:8
 �Ĵ���˵��: TX TDS���üĴ����������߿��߼��������reg_analog_wr48��
*****************************************************************************/
typedef union
{
    unsigned long      tx_tds_ana_1_reg;
    struct
    {
        unsigned long  TX_MODE_CLK_TDS : 2;  /* bit[0-1]: ģʽ���ƣ�
                                                          00��4G &amp; ET &amp; APT
                                                          01��3G &amp; TDS(Ĭ��)
                                                          10��--
                                                          11��2G */
        unsigned long  reserved        : 1;  /* bit[2]  : Reserved */
        unsigned long  TX_Q_PD_A_TDS   : 1;  /* bit[3]  : TX_Q DAC Power Down����
                                                          0:Power On
                                                          1:Power Down(Ĭ��)
                                                          (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_I_PD_A_TDS   : 1;  /* bit[4]  : TX_I DAC Power Down����
                                                          0:Power On
                                                          1:Power Down(Ĭ��)
                                                          (!TX_I_PD)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_DIV_MODE_TDS : 2;  /* bit[5-6]: TX Mode ʱ�ӿ��ƣ�
                                                          00: 1��Ƶ
                                                          01: 2��Ƶ(Ĭ��)
                                                          10: 3��Ƶ
                                                          11: 4��Ƶ */
        unsigned long  FC_TDS          : 1;  /* bit[7]  : TX filter��ֹƵ��ѡ��
                                                          0: 10MHz
                                                          1: 20MHz(Ĭ��) */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_ANA_1_UNION;
#define ABB_TX_TDS_ANA_1_TX_MODE_CLK_TDS_START  (0)
#define ABB_TX_TDS_ANA_1_TX_MODE_CLK_TDS_END    (1)
#define ABB_TX_TDS_ANA_1_TX_Q_PD_A_TDS_START    (3)
#define ABB_TX_TDS_ANA_1_TX_Q_PD_A_TDS_END      (3)
#define ABB_TX_TDS_ANA_1_TX_I_PD_A_TDS_START    (4)
#define ABB_TX_TDS_ANA_1_TX_I_PD_A_TDS_END      (4)
#define ABB_TX_TDS_ANA_1_TX_DIV_MODE_TDS_START  (5)
#define ABB_TX_TDS_ANA_1_TX_DIV_MODE_TDS_END    (6)
#define ABB_TX_TDS_ANA_1_FC_TDS_START           (7)
#define ABB_TX_TDS_ANA_1_FC_TDS_END             (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_ET_ANA_1_UNION
 �ṹ˵��  : tx_et_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x34����ֵ:0x4C�����:8
 �Ĵ���˵��: TX ET���üĴ����������߿��߼��������reg_analog_wr48��
*****************************************************************************/
typedef union
{
    unsigned long      tx_et_ana_1_reg;
    struct
    {
        unsigned long  TX_MODE_CLK_ET : 2;  /* bit[0-1]: ģʽ���ƣ�
                                                         00��4G &amp; ET &amp; APT(Ĭ��)
                                                         01��3G 
                                                         10��--
                                                         11��2G */
        unsigned long  TX_Q_PD_A_ET   : 1;  /* bit[2]  : TX_Q DAC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!TX_Q_PD)|(WG_TX_EN &amp;&amp; WG_LINE_CONTROL_MODE~
                                                         =ET &amp;&amp; WG_LINE_CONTROL_MODE~=APT) = 1ʱ����������ر� */
        unsigned long  TX_I_PD_A_ET   : 1;  /* bit[3]  : TX_I DAC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!TX_I_PD)|WG_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_DIV_MODE_ET : 2;  /* bit[4-5]: TX Mode ʱ�ӿ��ƣ�
                                                         00: 1��Ƶ(Ĭ��)
                                                         01: 2��Ƶ
                                                         10: 3��Ƶ
                                                         11: 4��Ƶ */
        unsigned long  FC_ET          : 2;  /* bit[6-7]: TX filter��ֹƵ��ѡ��
                                                         00: 10MHz;
                                                         01: 20MHz;(Ĭ��)
                                                         11:40MHz;
                                                         10:reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_ANA_1_UNION;
#define ABB_TX_ET_ANA_1_TX_MODE_CLK_ET_START  (0)
#define ABB_TX_ET_ANA_1_TX_MODE_CLK_ET_END    (1)
#define ABB_TX_ET_ANA_1_TX_Q_PD_A_ET_START    (2)
#define ABB_TX_ET_ANA_1_TX_Q_PD_A_ET_END      (2)
#define ABB_TX_ET_ANA_1_TX_I_PD_A_ET_START    (3)
#define ABB_TX_ET_ANA_1_TX_I_PD_A_ET_END      (3)
#define ABB_TX_ET_ANA_1_TX_DIV_MODE_ET_START  (4)
#define ABB_TX_ET_ANA_1_TX_DIV_MODE_ET_END    (5)
#define ABB_TX_ET_ANA_1_FC_ET_START           (6)
#define ABB_TX_ET_ANA_1_FC_ET_END             (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_APT_ANA_1_UNION
 �ṹ˵��  : tx_apt_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x36����ֵ:0x7C�����:8
 �Ĵ���˵��: TX APT���üĴ����������߿��߼��������reg_analog_wr48��
*****************************************************************************/
typedef union
{
    unsigned long      tx_apt_ana_1_reg;
    struct
    {
        unsigned long  TX_MODE_CLK_APT : 2;  /* bit[0-1]: ģʽ���ƣ�
                                                          00��4G &amp; ET &amp; APT(Ĭ��)
                                                          01��3G 
                                                          10��--
                                                          11��2G */
        unsigned long  TX_Q_PD_A_APT   : 1;  /* bit[2]  : TX_Q DAC Power Down����
                                                          0:Power On
                                                          1:Power Down(Ĭ��)
                                                          (!TX_Q_PD)|(XX_TX_EN &amp;&amp; ~ET_SEL) = 1ʱ����������ر� */
        unsigned long  TX_I_PD_A_APT   : 1;  /* bit[3]  : TX_I DAC Power Down����
                                                          0:Power On
                                                          1:Power Down(Ĭ��)
                                                          (!TX_I_PD)|(XX_TX_EN &amp;&amp; ET_SEL) = 1ʱ����������ر� */
        unsigned long  TX_DIV_MODE_APT : 2;  /* bit[4-5]: TX Mode ʱ�ӿ��ƣ�
                                                          00: 1��Ƶ
                                                          01: 2��Ƶ
                                                          10: 3��Ƶ
                                                          11: 4��Ƶ(Ĭ��) */
        unsigned long  FC_APT          : 2;  /* bit[6-7]: TX filter��ֹƵ��ѡ��
                                                          00: 10MHz;
                                                          01: 20MHz;(Ĭ��)
                                                          11:40MHz;
                                                          10:reserved */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_APT_ANA_1_UNION;
#define ABB_TX_APT_ANA_1_TX_MODE_CLK_APT_START  (0)
#define ABB_TX_APT_ANA_1_TX_MODE_CLK_APT_END    (1)
#define ABB_TX_APT_ANA_1_TX_Q_PD_A_APT_START    (2)
#define ABB_TX_APT_ANA_1_TX_Q_PD_A_APT_END      (2)
#define ABB_TX_APT_ANA_1_TX_I_PD_A_APT_START    (3)
#define ABB_TX_APT_ANA_1_TX_I_PD_A_APT_END      (3)
#define ABB_TX_APT_ANA_1_TX_DIV_MODE_APT_START  (4)
#define ABB_TX_APT_ANA_1_TX_DIV_MODE_APT_END    (5)
#define ABB_TX_APT_ANA_1_FC_APT_START           (6)
#define ABB_TX_APT_ANA_1_FC_APT_END             (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_CA_ANA_1_UNION
 �ṹ˵��  : rx_ca_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x38����ֵ:0xF0�����:8
 �Ĵ���˵��: RX CA���üĴ����������߿��߼��������reg_analog_wr00��
*****************************************************************************/
typedef union
{
    unsigned long      rx_ca_ana_1_reg;
    struct
    {
        unsigned long  DEM_MOD_B0_CA  : 1;  /* bit[0]  : RX DEM Mode Selection,bit 0
                                                         000: DWA
                                                         001: CLA1
                                                         010: CLA2
                                                         011: CLA3
                                                         100: CLA4
                                                         101: CLA5
                                                         110: CLA6
                                                         111: CLA7 */
        unsigned long  RX_MODE_CLK_CA : 2;  /* bit[1-2]: ģʽ���ƣ�
                                                         00��4G &amp; ET &amp; APT(Ĭ��)
                                                         01��3G
                                                         10��3G_DC &amp; TDS
                                                         11��2G */
        unsigned long  DEM_MOD_B1_CA  : 1;  /* bit[3]  : RX DEM Mode Selection,bit 1
                                                         000: DWA
                                                         001: CLA1
                                                         010: CLA2
                                                         011: CLA3
                                                         100: CLA4
                                                         101: CLA5
                                                         110: CLA6
                                                         111: CLA7 */
        unsigned long  RXB_Q_PD_CA    : 1;  /* bit[4]  : RXB_Q ADC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!RXB_Q_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXB_I_PD_CA    : 1;  /* bit[5]  : RXB_I ADC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!RXB_I_PD)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  RXA_Q_PD_CA    : 1;  /* bit[6]  : RXA_Q ADC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!RXA_Q_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  RXA_I_PD_CA    : 1;  /* bit[7]  : RXA_I ADC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!RXA_I_PD)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_CA_ANA_1_UNION;
#define ABB_RX_CA_ANA_1_DEM_MOD_B0_CA_START   (0)
#define ABB_RX_CA_ANA_1_DEM_MOD_B0_CA_END     (0)
#define ABB_RX_CA_ANA_1_RX_MODE_CLK_CA_START  (1)
#define ABB_RX_CA_ANA_1_RX_MODE_CLK_CA_END    (2)
#define ABB_RX_CA_ANA_1_DEM_MOD_B1_CA_START   (3)
#define ABB_RX_CA_ANA_1_DEM_MOD_B1_CA_END     (3)
#define ABB_RX_CA_ANA_1_RXB_Q_PD_CA_START     (4)
#define ABB_RX_CA_ANA_1_RXB_Q_PD_CA_END       (4)
#define ABB_RX_CA_ANA_1_RXB_I_PD_CA_START     (5)
#define ABB_RX_CA_ANA_1_RXB_I_PD_CA_END       (5)
#define ABB_RX_CA_ANA_1_RXA_Q_PD_CA_START     (6)
#define ABB_RX_CA_ANA_1_RXA_Q_PD_CA_END       (6)
#define ABB_RX_CA_ANA_1_RXA_I_PD_CA_START     (7)
#define ABB_RX_CA_ANA_1_RXA_I_PD_CA_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_CA_ANA_1_UNION
 �ṹ˵��  : tx_ca_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x3A����ֵ:0xF8�����:8
 �Ĵ���˵��: TX CA���üĴ����������߿��߼��������reg_analog_wr48��
*****************************************************************************/
typedef union
{
    unsigned long      tx_ca_ana_1_reg;
    struct
    {
        unsigned long  TX_MODE_CLK_CA : 2;  /* bit[0-1]: ģʽ���ƣ�
                                                         00��4G &amp; ET &amp; APT(Ĭ��)
                                                         01��3G &amp; TDS
                                                         10��--
                                                         11��2G */
        unsigned long  reserved       : 1;  /* bit[2]  : Reserved */
        unsigned long  TX_Q_PD_A_CA   : 1;  /* bit[3]  : TX_Q DAC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!TX_Q_PD)|(XX_TX_EN &amp;&amp; ~ET_SEL) = 1ʱ����������ر� */
        unsigned long  TX_I_PD_A_CA   : 1;  /* bit[4]  : TX_I DAC Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��)
                                                         (!TX_I_PD)|(XX_TX_EN &amp;&amp; ET_SEL) = 1ʱ����������ر� */
        unsigned long  TX_DIV_MODE_CA : 2;  /* bit[5-6]: TX Mode ʱ�ӿ��ƣ�
                                                         00: 1��Ƶ
                                                         01: 2��Ƶ
                                                         10: 3��Ƶ
                                                         11: 4��Ƶ(Ĭ��) */
        unsigned long  FC_CA          : 1;  /* bit[7]  : TX filter��ֹƵ��ѡ��
                                                         0: 10MHz
                                                         1: 20MHz(Ĭ��) */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_CA_ANA_1_UNION;
#define ABB_TX_CA_ANA_1_TX_MODE_CLK_CA_START  (0)
#define ABB_TX_CA_ANA_1_TX_MODE_CLK_CA_END    (1)
#define ABB_TX_CA_ANA_1_TX_Q_PD_A_CA_START    (3)
#define ABB_TX_CA_ANA_1_TX_Q_PD_A_CA_END      (3)
#define ABB_TX_CA_ANA_1_TX_I_PD_A_CA_START    (4)
#define ABB_TX_CA_ANA_1_TX_I_PD_A_CA_END      (4)
#define ABB_TX_CA_ANA_1_TX_DIV_MODE_CA_START  (5)
#define ABB_TX_CA_ANA_1_TX_DIV_MODE_CA_END    (6)
#define ABB_TX_CA_ANA_1_FC_CA_START           (7)
#define ABB_TX_CA_ANA_1_FC_CA_END             (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_IDLE_ANA_1_UNION
 �ṹ˵��  : rx_idle_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x3C����ֵ:0xF0�����:8
 �Ĵ���˵��: RX IDLE���üĴ����������߿��߼��������reg_analog_wr00��
*****************************************************************************/
typedef union
{
    unsigned long      rx_idle_ana_1_reg;
    struct
    {
        unsigned long  DEM_MOD_B0_IDLE  : 1;  /* bit[0]  : Reserved */
        unsigned long  RX_MODE_CLK_IDLE : 2;  /* bit[1-2]: ģʽ���ƣ�
                                                           00��4G (Ĭ��)
                                                           01��3G
                                                           10��3G_DC
                                                           11��2G */
        unsigned long  DEM_MOD_B1_IDLE  : 1;  /* bit[3]  : Reserved */
        unsigned long  RXB_Q_PD_IDLE    : 1;  /* bit[4]  : RXB_Q ADC Power Down����
                                                           0:Power On
                                                           1:Power Down(Ĭ��) */
        unsigned long  RXB_I_PD_IDLE    : 1;  /* bit[5]  : RXB_I ADC Power Down����
                                                           0:Power On
                                                           1:Power Down(Ĭ��) */
        unsigned long  RXA_Q_PD_IDLE    : 1;  /* bit[6]  : RXA_Q ADC Power Down����
                                                           0:Power On
                                                           1:Power Down(Ĭ��) */
        unsigned long  RXA_I_PD_IDLE    : 1;  /* bit[7]  : RXA_I ADC Power Down����
                                                           0:Power On
                                                           1:Power Down(Ĭ��) */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_ANA_1_UNION;
#define ABB_RX_IDLE_ANA_1_DEM_MOD_B0_IDLE_START   (0)
#define ABB_RX_IDLE_ANA_1_DEM_MOD_B0_IDLE_END     (0)
#define ABB_RX_IDLE_ANA_1_RX_MODE_CLK_IDLE_START  (1)
#define ABB_RX_IDLE_ANA_1_RX_MODE_CLK_IDLE_END    (2)
#define ABB_RX_IDLE_ANA_1_DEM_MOD_B1_IDLE_START   (3)
#define ABB_RX_IDLE_ANA_1_DEM_MOD_B1_IDLE_END     (3)
#define ABB_RX_IDLE_ANA_1_RXB_Q_PD_IDLE_START     (4)
#define ABB_RX_IDLE_ANA_1_RXB_Q_PD_IDLE_END       (4)
#define ABB_RX_IDLE_ANA_1_RXB_I_PD_IDLE_START     (5)
#define ABB_RX_IDLE_ANA_1_RXB_I_PD_IDLE_END       (5)
#define ABB_RX_IDLE_ANA_1_RXA_Q_PD_IDLE_START     (6)
#define ABB_RX_IDLE_ANA_1_RXA_Q_PD_IDLE_END       (6)
#define ABB_RX_IDLE_ANA_1_RXA_I_PD_IDLE_START     (7)
#define ABB_RX_IDLE_ANA_1_RXA_I_PD_IDLE_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_IDLE_ANA_1_UNION
 �ṹ˵��  : tx_idle_ana_1 �Ĵ����ṹ���塣��ַƫ����:0x3E����ֵ:0x4C�����:8
 �Ĵ���˵��: TX IDLE���üĴ����������߿��߼��������reg_analog_wr48��
*****************************************************************************/
typedef union
{
    unsigned long      tx_idle_ana_1_reg;
    struct
    {
        unsigned long  TX_MODE_CLK_IDLE : 2;  /* bit[0-1]: ģʽ���ƣ�
                                                           00��4G &amp; ET &amp; APT(Ĭ��)
                                                           01��3G 
                                                           10��--
                                                           11��2G */
        unsigned long  TX_Q_PD_A_IDLE   : 1;  /* bit[2]  : TX_Q DAC Power Down����
                                                           0:Power On
                                                           1:Power Down(Ĭ��)
                                                           (!TX_Q_PD)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_I_PD_A_IDLE   : 1;  /* bit[3]  : TX_I DAC Power Down����
                                                           0:Power On
                                                           1:Power Down(Ĭ��)
                                                           (!TX_I_PD)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  TX_DIV_MODE_IDLE : 2;  /* bit[4-5]: TX Mode ʱ�ӿ��ƣ�
                                                           00: 1��Ƶ(Ĭ��)
                                                           01: 2��Ƶ
                                                           10: 3��Ƶ
                                                           11: 4��Ƶ */
        unsigned long  FC_IDLE          : 2;  /* bit[6-7]: TX filter��ֹƵ��ѡ��
                                                           00: 10MHz;
                                                           01: 20MHz;(Ĭ��)
                                                           11:40MHz;
                                                           10:reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_ANA_1_UNION;
#define ABB_TX_IDLE_ANA_1_TX_MODE_CLK_IDLE_START  (0)
#define ABB_TX_IDLE_ANA_1_TX_MODE_CLK_IDLE_END    (1)
#define ABB_TX_IDLE_ANA_1_TX_Q_PD_A_IDLE_START    (2)
#define ABB_TX_IDLE_ANA_1_TX_Q_PD_A_IDLE_END      (2)
#define ABB_TX_IDLE_ANA_1_TX_I_PD_A_IDLE_START    (3)
#define ABB_TX_IDLE_ANA_1_TX_I_PD_A_IDLE_END      (3)
#define ABB_TX_IDLE_ANA_1_TX_DIV_MODE_IDLE_START  (4)
#define ABB_TX_IDLE_ANA_1_TX_DIV_MODE_IDLE_END    (5)
#define ABB_TX_IDLE_ANA_1_FC_IDLE_START           (6)
#define ABB_TX_IDLE_ANA_1_FC_IDLE_END             (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TESTMODE_UNION
 �ṹ˵��  : ch1_testmode �Ĵ����ṹ���塣��ַƫ����:0x41����ֵ:0x00�����:8
 �Ĵ���˵��: ����ģʽ�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_testmode_reg;
    struct
    {
        unsigned long  reserved_0      : 1;  /* bit[0]  : ���� */
        unsigned long  ch1_rx_chnl_sel : 2;  /* bit[1-2]: RXģ�����ģʽ��ͨ��ѡ��
                                                          00�����RXA Iģ�����������(Ĭ��)
                                                          01�����RXA Qģ�����������
                                                          10�����RXB Iģ�����������
                                                          11�����RXB Qģ����������� */
        unsigned long  ch1_test_mode   : 3;  /* bit[3-5]: bit[4:3]����ģʽ���ƣ�
                                                          00������ģʽ(Ĭ��)
                                                          01�������㷨�߼�����ģʽ
                                                          10��RXģ�����ģʽ(bypass RX�����˲���)
                                                          11�����ֽӿڻ���ģʽ
                                                          bit[5]��reserved */
        unsigned long  ch1_sw_rst      : 1;  /* bit[6]  : ���õ���λ�źţ�
                                                          0�������������λ(Ĭ��)
                                                          1�����������λ */
        unsigned long  reserved_1      : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TESTMODE_UNION;
#define ABB_CH1_TESTMODE_ch1_rx_chnl_sel_START  (1)
#define ABB_CH1_TESTMODE_ch1_rx_chnl_sel_END    (2)
#define ABB_CH1_TESTMODE_ch1_test_mode_START    (3)
#define ABB_CH1_TESTMODE_ch1_test_mode_END      (5)
#define ABB_CH1_TESTMODE_ch1_sw_rst_START       (6)
#define ABB_CH1_TESTMODE_ch1_sw_rst_END         (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_CTRL_UNION
 �ṹ˵��  : ch1_ctrl �Ĵ����ṹ���塣��ַƫ����:0x42����ֵ:0x00�����:8
 �Ĵ���˵��: ͨ�����ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_ctrl_reg;
    struct
    {
        unsigned long  ch1_et_sel : 1;  /* bit[0]  : ET/APTͨ��ѡ��
                                                     0��ѡ��TXͨ��I·��ET/APT
                                                     1��ѡ��TXͨ��Q·��ET/APT */
        unsigned long  reserved   : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_CTRL_UNION;
#define ABB_CH1_CTRL_ch1_et_sel_START  (0)
#define ABB_CH1_CTRL_ch1_et_sel_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_CH1_CFR_CTRL_UNION
 �ṹ˵��  : ch1_cfr_ctrl �Ĵ����ṹ���塣��ַƫ����:0x43����ֵ:0x44�����:8
 �Ĵ���˵��: CFR��ֵ��ⴰ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_cfr_ctrl_reg;
    struct
    {
        unsigned long  ch1_cfr_pdet_sel : 2;  /* bit[0-1]: CFR��ֵ��ⷽʽ��
                                                           00���������
                                                           01���������
                                                           10���������
                                                           11��ȫ����ֵ */
        unsigned long  ch1_cfr_fir_sel  : 1;  /* bit[2]  : CFR�˲���ѡ��
                                                           0��bypass�˲���
                                                           1����bypass�˲��� */
        unsigned long  reserved         : 1;  /* bit[3]  : ���� */
        unsigned long  ch1_cfr_fir_fac  : 4;  /* bit[4-7]: CFR�������� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_CFR_CTRL_UNION;
#define ABB_CH1_CFR_CTRL_ch1_cfr_pdet_sel_START  (0)
#define ABB_CH1_CFR_CTRL_ch1_cfr_pdet_sel_END    (1)
#define ABB_CH1_CFR_CTRL_ch1_cfr_fir_sel_START   (2)
#define ABB_CH1_CFR_CTRL_ch1_cfr_fir_sel_END     (2)
#define ABB_CH1_CFR_CTRL_ch1_cfr_fir_fac_START   (4)
#define ABB_CH1_CFR_CTRL_ch1_cfr_fir_fac_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_LINE_CTRL_SEL_UNION
 �ṹ˵��  : ch1_line_ctrl_sel �Ĵ����ṹ���塣��ַƫ����:0x44����ֵ:0xFF�����:8
 �Ĵ���˵��: �߿�ѡ��
*****************************************************************************/
typedef union
{
    unsigned long      ch1_line_ctrl_sel_reg;
    struct
    {
        unsigned long  ch1_line_ctrl_2g_sel  : 1;  /* bit[0]: ѡ��2G�߿�ģʽ��0: tie to 0(Ĭ�ϣ�
                                                              1: from line control */
        unsigned long  ch1_line_ctrl_3g_sel  : 1;  /* bit[1]: ѡ��3G�߿�ģʽ��0: tie to 0(Ĭ�ϣ�
                                                              1: from line control */
        unsigned long  ch1_line_ctrl_4g_sel  : 1;  /* bit[2]: ѡ��4G�߿�ģʽ��0: tie to 0(Ĭ�ϣ�
                                                              1: from line control */
        unsigned long  ch1_line_ctrl_apt_sel : 1;  /* bit[3]: ѡ��APT�߿�ģʽ��0: tie to 0(Ĭ�ϣ�
                                                              1: from line control */
        unsigned long  ch1_line_ctrl_et_sel  : 1;  /* bit[4]: ѡ��ET�߿�ģʽ��0: tie to 0(Ĭ�ϣ�
                                                              1: from line control */
        unsigned long  ch1_line_ctrl_tx_sel  : 1;  /* bit[5]: ѡ��TX_EN�߿أ�0: tie to 0(Ĭ�ϣ�
                                                              1: from line control */
        unsigned long  ch1_line_ctrl_rxb_sel : 1;  /* bit[6]: ѡ��RXB_EN�߿أ�0: tie to 0(Ĭ�ϣ�
                                                              1: from line control */
        unsigned long  ch1_line_ctrl_rxa_en  : 1;  /* bit[7]: ѡ��RXA_EN�߿أ�0: tie to 0(Ĭ�ϣ�
                                                              1: from line control */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_LINE_CTRL_SEL_UNION;
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_2g_sel_START   (0)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_2g_sel_END     (0)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_3g_sel_START   (1)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_3g_sel_END     (1)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_4g_sel_START   (2)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_4g_sel_END     (2)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_apt_sel_START  (3)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_apt_sel_END    (3)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_et_sel_START   (4)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_et_sel_END     (4)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_tx_sel_START   (5)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_tx_sel_END     (5)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_rxb_sel_START  (6)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_rxb_sel_END    (6)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_rxa_en_START   (7)
#define ABB_CH1_LINE_CTRL_SEL_ch1_line_ctrl_rxa_en_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RX_DIG_RPT_UNION
 �ṹ˵��  : ch1_rx_dig_rpt �Ĵ����ṹ���塣��ַƫ����:0x45����ֵ:0x00�����:8
 �Ĵ���˵��: RX���ֹ���ģʽ�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_rx_dig_rpt_reg;
    struct
    {
        unsigned long  ch1_rx_comp_sel_rpt : 1;  /* bit[0]  : Reserved */
        unsigned long  ch1_rx_comp_fix_rpt : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                              0��ϵ�����̶����ɼĴ�������
                                                              1��ϵ���̶� */
        unsigned long  ch1_rx_hb_bp_rpt    : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                              0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2
                                                              1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  ch1_rx_rate_rpt     : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                                  2G,   3G_SC,    4G,   3G_DC,      
                                                              00�� 2.167M,15.36M, 61.44M,30.72M
                                                              01�� 4.33MHz,------,30.72M,------
                                                              10�� ------, ------,15.36M,------
                                                              11�� ------, ------, 7.68M,------ */
        unsigned long  ch1_rx_mode_dig_rpt : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                              000��2G
                                                              001��3G_SC
                                                              010��4G
                                                              011��3G_DC
                                                              Others��reserved */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_DIG_RPT_UNION;
#define ABB_CH1_RX_DIG_RPT_ch1_rx_comp_sel_rpt_START  (0)
#define ABB_CH1_RX_DIG_RPT_ch1_rx_comp_sel_rpt_END    (0)
#define ABB_CH1_RX_DIG_RPT_ch1_rx_comp_fix_rpt_START  (1)
#define ABB_CH1_RX_DIG_RPT_ch1_rx_comp_fix_rpt_END    (1)
#define ABB_CH1_RX_DIG_RPT_ch1_rx_hb_bp_rpt_START     (2)
#define ABB_CH1_RX_DIG_RPT_ch1_rx_hb_bp_rpt_END       (2)
#define ABB_CH1_RX_DIG_RPT_ch1_rx_rate_rpt_START      (3)
#define ABB_CH1_RX_DIG_RPT_ch1_rx_rate_rpt_END        (4)
#define ABB_CH1_RX_DIG_RPT_ch1_rx_mode_dig_rpt_START  (5)
#define ABB_CH1_RX_DIG_RPT_ch1_rx_mode_dig_rpt_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TX_DIG_RPT_UNION
 �ṹ˵��  : ch1_tx_dig_rpt �Ĵ����ṹ���塣��ַƫ����:0x46����ֵ:0x02�����:8
 �Ĵ���˵��: TX���ֹ���ģʽ�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_tx_dig_rpt_reg;
    struct
    {
        unsigned long  ch1_tx_comp_bp_tpr  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                              0����bypass
                                                              1��bypass */
        unsigned long  ch1_tx_hb_bp_rpt    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                              0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2
                                                              1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  ch1_tx_rate_rpt     : 3;  /* bit[2-4]: TXͨ��CIC�˲���������ʿ��ƣ�
                                                                   2G,     3G,     4G,     
                                                                  (78M) (153.6M) (307.2M) 
                                                              0��4.33MHz,30.72MHz,61.44MHz
                                                              1��2.16MHz,15.36MHz,30.72MHz
                                                              2��-------,--------,15.36MHz
                                                              3��-------,--------, 7.68MHz
                                                              4��-------,--------, 3.84MHz
                                                              Others��Reserved */
        unsigned long  ch1_tx_mode_dig_rpt : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                              000��2G
                                                              001��3G
                                                              010��4G &amp; ET &amp; APT
                                                              Others��reserved */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_DIG_RPT_UNION;
#define ABB_CH1_TX_DIG_RPT_ch1_tx_comp_bp_tpr_START   (0)
#define ABB_CH1_TX_DIG_RPT_ch1_tx_comp_bp_tpr_END     (0)
#define ABB_CH1_TX_DIG_RPT_ch1_tx_hb_bp_rpt_START     (1)
#define ABB_CH1_TX_DIG_RPT_ch1_tx_hb_bp_rpt_END       (1)
#define ABB_CH1_TX_DIG_RPT_ch1_tx_rate_rpt_START      (2)
#define ABB_CH1_TX_DIG_RPT_ch1_tx_rate_rpt_END        (4)
#define ABB_CH1_TX_DIG_RPT_ch1_tx_mode_dig_rpt_START  (5)
#define ABB_CH1_TX_DIG_RPT_ch1_tx_mode_dig_rpt_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXA_I_COEF1_UNION
 �ṹ˵��  : ch1_rxa_i_coef1 �Ĵ����ṹ���塣��ַƫ����:0x4B����ֵ:0xF4�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_rxa_i_coef1_reg;
    struct
    {
        unsigned long  ch1_rxa_i_c1     : 7;  /* bit[0-6]: RXAͨ��I·�����˲���ϵ��C1,�з����� */
        unsigned long  ch1_rxa_i_c3_msb : 1;  /* bit[7]  : RXAͨ��I·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXA_I_COEF1_UNION;
#define ABB_CH1_RXA_I_COEF1_ch1_rxa_i_c1_START      (0)
#define ABB_CH1_RXA_I_COEF1_ch1_rxa_i_c1_END        (6)
#define ABB_CH1_RXA_I_COEF1_ch1_rxa_i_c3_msb_START  (7)
#define ABB_CH1_RXA_I_COEF1_ch1_rxa_i_c3_msb_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXA_I_COEF3_UNION
 �ṹ˵��  : ch1_rxa_i_coef3 �Ĵ����ṹ���塣��ַƫ����:0x4D����ֵ:0x74�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_rxa_i_coef3_reg;
    struct
    {
        unsigned long  ch1_rxa_i_c5 : 7;  /* bit[0-6]: RXAͨ��I·�����˲���ϵ��C5,�з����� */
        unsigned long  reserved     : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXA_I_COEF3_UNION;
#define ABB_CH1_RXA_I_COEF3_ch1_rxa_i_c5_START  (0)
#define ABB_CH1_RXA_I_COEF3_ch1_rxa_i_c5_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXA_Q_COEF1_UNION
 �ṹ˵��  : ch1_rxa_q_coef1 �Ĵ����ṹ���塣��ַƫ����:0x50����ֵ:0xF4�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_rxa_q_coef1_reg;
    struct
    {
        unsigned long  ch1_rxa_q_c1     : 7;  /* bit[0-6]: RXAͨ��Q·�����˲���ϵ��C1,�з����� */
        unsigned long  ch1_rxa_q_c3_msb : 1;  /* bit[7]  : RXAͨ��Q·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXA_Q_COEF1_UNION;
#define ABB_CH1_RXA_Q_COEF1_ch1_rxa_q_c1_START      (0)
#define ABB_CH1_RXA_Q_COEF1_ch1_rxa_q_c1_END        (6)
#define ABB_CH1_RXA_Q_COEF1_ch1_rxa_q_c3_msb_START  (7)
#define ABB_CH1_RXA_Q_COEF1_ch1_rxa_q_c3_msb_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXA_Q_COEF3_UNION
 �ṹ˵��  : ch1_rxa_q_coef3 �Ĵ����ṹ���塣��ַƫ����:0x52����ֵ:0x74�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_rxa_q_coef3_reg;
    struct
    {
        unsigned long  ch1_rxa_q_c5 : 7;  /* bit[0-6]: RXAͨ��Q·�����˲���ϵ��C5,�з����� */
        unsigned long  reserved     : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXA_Q_COEF3_UNION;
#define ABB_CH1_RXA_Q_COEF3_ch1_rxa_q_c5_START  (0)
#define ABB_CH1_RXA_Q_COEF3_ch1_rxa_q_c5_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXB_I_COEF1_UNION
 �ṹ˵��  : ch1_rxb_i_coef1 �Ĵ����ṹ���塣��ַƫ����:0x55����ֵ:0xF4�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_rxb_i_coef1_reg;
    struct
    {
        unsigned long  ch1_rxb_i_c1     : 7;  /* bit[0-6]: RXBͨ��I·�����˲���ϵ��C1,�з����� */
        unsigned long  ch1_rxb_i_c3_msb : 1;  /* bit[7]  : RXBͨ��I·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXB_I_COEF1_UNION;
#define ABB_CH1_RXB_I_COEF1_ch1_rxb_i_c1_START      (0)
#define ABB_CH1_RXB_I_COEF1_ch1_rxb_i_c1_END        (6)
#define ABB_CH1_RXB_I_COEF1_ch1_rxb_i_c3_msb_START  (7)
#define ABB_CH1_RXB_I_COEF1_ch1_rxb_i_c3_msb_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXB_I_COEF3_UNION
 �ṹ˵��  : ch1_rxb_i_coef3 �Ĵ����ṹ���塣��ַƫ����:0x57����ֵ:0x74�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_rxb_i_coef3_reg;
    struct
    {
        unsigned long  ch1_rxb_i_c5 : 7;  /* bit[0-6]: RXBͨ��I·�����˲���ϵ��C5,�з����� */
        unsigned long  reserved     : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXB_I_COEF3_UNION;
#define ABB_CH1_RXB_I_COEF3_ch1_rxb_i_c5_START  (0)
#define ABB_CH1_RXB_I_COEF3_ch1_rxb_i_c5_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXB_Q_COEF1_UNION
 �ṹ˵��  : ch1_rxb_q_coef1 �Ĵ����ṹ���塣��ַƫ����:0x5A����ֵ:0xF4�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_rxb_q_coef1_reg;
    struct
    {
        unsigned long  ch1_rxb_q_c1     : 7;  /* bit[0-6]: RXBͨ��Q·�����˲���ϵ��C1,�з����� */
        unsigned long  ch1_rxb_q_c3_msb : 1;  /* bit[7]  : RXBͨ��Q·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXB_Q_COEF1_UNION;
#define ABB_CH1_RXB_Q_COEF1_ch1_rxb_q_c1_START      (0)
#define ABB_CH1_RXB_Q_COEF1_ch1_rxb_q_c1_END        (6)
#define ABB_CH1_RXB_Q_COEF1_ch1_rxb_q_c3_msb_START  (7)
#define ABB_CH1_RXB_Q_COEF1_ch1_rxb_q_c3_msb_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXB_Q_COEF3_UNION
 �ṹ˵��  : ch1_rxb_q_coef3 �Ĵ����ṹ���塣��ַƫ����:0x5C����ֵ:0x74�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_rxb_q_coef3_reg;
    struct
    {
        unsigned long  ch1_rxb_q_c5 : 7;  /* bit[0-6]: RXBͨ��Q·�����˲���ϵ��C5,�з����� */
        unsigned long  reserved     : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXB_Q_COEF3_UNION;
#define ABB_CH1_RXB_Q_COEF3_ch1_rxb_q_c5_START  (0)
#define ABB_CH1_RXB_Q_COEF3_ch1_rxb_q_c5_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_RXA_DCR_CFG_UNION
 �ṹ˵��  : ch1_reg_rxa_dcr_cfg �Ĵ����ṹ���塣��ַƫ����:0x5E����ֵ:0x46�����:8
 �Ĵ���˵��: RXAͨ��BLOCKING DCR���üĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_rxa_dcr_cfg_reg;
    struct
    {
        unsigned long  ch1_cfg_rxa_dcr_dly    : 5;  /* bit[0-4]: RXA����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣 */
        unsigned long  ch1_cfg_rxa_dcr_l_para : 3;  /* bit[5-7]: RXA����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ�� */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RXA_DCR_CFG_UNION;
#define ABB_CH1_REG_RXA_DCR_CFG_ch1_cfg_rxa_dcr_dly_START     (0)
#define ABB_CH1_REG_RXA_DCR_CFG_ch1_cfg_rxa_dcr_dly_END       (4)
#define ABB_CH1_REG_RXA_DCR_CFG_ch1_cfg_rxa_dcr_l_para_START  (5)
#define ABB_CH1_REG_RXA_DCR_CFG_ch1_cfg_rxa_dcr_l_para_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_RXB_DCR_CFG_UNION
 �ṹ˵��  : ch1_reg_rxb_dcr_cfg �Ĵ����ṹ���塣��ַƫ����:0x5F����ֵ:0x46�����:8
 �Ĵ���˵��: RXBͨ��BLOCKING DCR���üĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_rxb_dcr_cfg_reg;
    struct
    {
        unsigned long  ch1_cfg_rxb_dcr_dly    : 5;  /* bit[0-4]: RXB����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣 */
        unsigned long  ch1_cfg_rxb_dcr_l_para : 3;  /* bit[5-7]: RXB����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ�� */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RXB_DCR_CFG_UNION;
#define ABB_CH1_REG_RXB_DCR_CFG_ch1_cfg_rxb_dcr_dly_START     (0)
#define ABB_CH1_REG_RXB_DCR_CFG_ch1_cfg_rxb_dcr_dly_END       (4)
#define ABB_CH1_REG_RXB_DCR_CFG_ch1_cfg_rxb_dcr_l_para_START  (5)
#define ABB_CH1_REG_RXB_DCR_CFG_ch1_cfg_rxb_dcr_l_para_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_RX_DCR_CTRL_UNION
 �ṹ˵��  : ch1_reg_rx_dcr_ctrl �Ĵ����ṹ���塣��ַƫ����:0x60����ֵ:0x00�����:8
 �Ĵ���˵��: BLOCKING DCR���ܿ��ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_rx_dcr_ctrl_reg;
    struct
    {
        unsigned long  ch1_cfg_rxa_dcr_bypass : 1;  /* bit[0]  : RXA����BLOCKING DCR����bypass���ơ�
                                                                 0��DCR���ܲ�bypasss��
                                                                 1��DCR����bypass�� */
        unsigned long  ch1_cfg_rxb_dcr_bypass : 1;  /* bit[1]  : RXB����BLOCKING DCR����bypass���ơ�
                                                                 0��DCR���ܲ�bypasss��
                                                                 1��DCR����bypass�� */
        unsigned long  reserved               : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RX_DCR_CTRL_UNION;
#define ABB_CH1_REG_RX_DCR_CTRL_ch1_cfg_rxa_dcr_bypass_START  (0)
#define ABB_CH1_REG_RX_DCR_CTRL_ch1_cfg_rxa_dcr_bypass_END    (0)
#define ABB_CH1_REG_RX_DCR_CTRL_ch1_cfg_rxb_dcr_bypass_START  (1)
#define ABB_CH1_REG_RX_DCR_CTRL_ch1_cfg_rxb_dcr_bypass_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXA_BLOCKING_UNION
 �ṹ˵��  : ch1_rxa_blocking �Ĵ����ṹ���塣��ַƫ����:0x61����ֵ:0x00�����:8
 �Ĵ���˵��: RXAͨ��BLOCKING�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_rxa_blocking_reg;
    struct
    {
        unsigned long  ch1_rxa_blk_coeff : 5;  /* bit[0-4]: RXA����BLOCKING�ϱ�ֵ��ϵ����2��M�η� */
        unsigned long  ch1_rxa_blk_power : 3;  /* bit[5-7]: RXA����BLOCKING�ϱ�ֵ,������СN */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXA_BLOCKING_UNION;
#define ABB_CH1_RXA_BLOCKING_ch1_rxa_blk_coeff_START  (0)
#define ABB_CH1_RXA_BLOCKING_ch1_rxa_blk_coeff_END    (4)
#define ABB_CH1_RXA_BLOCKING_ch1_rxa_blk_power_START  (5)
#define ABB_CH1_RXA_BLOCKING_ch1_rxa_blk_power_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXB_BLOCKING_UNION
 �ṹ˵��  : ch1_rxb_blocking �Ĵ����ṹ���塣��ַƫ����:0x62����ֵ:0x00�����:8
 �Ĵ���˵��: RXBͨ��BLOCKING�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_rxb_blocking_reg;
    struct
    {
        unsigned long  ch1_rxb_blk_coeff : 5;  /* bit[0-4]: RXB����BLOCKING�ϱ�ֵ��ϵ����2��M�η� */
        unsigned long  ch1_rxb_blk_power : 3;  /* bit[5-7]: RXB����BLOCKING�ϱ�ֵ,������СN */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXB_BLOCKING_UNION;
#define ABB_CH1_RXB_BLOCKING_ch1_rxb_blk_coeff_START  (0)
#define ABB_CH1_RXB_BLOCKING_ch1_rxb_blk_coeff_END    (4)
#define ABB_CH1_RXB_BLOCKING_ch1_rxb_blk_power_START  (5)
#define ABB_CH1_RXB_BLOCKING_ch1_rxb_blk_power_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_RXA_DC_I_2_UNION
 �ṹ˵��  : ch1_reg_rxa_dc_i_2 �Ĵ����ṹ���塣��ַƫ����:0x64����ֵ:0x00�����:8
 �Ĵ���˵��: RXAͨ��I·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_rxa_dc_i_2_reg;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: ���� */
        unsigned long  ch1_rxa_dc_i_2 : 4;  /* bit[4-7]: RXA����I·�ź�BLOCKING DC�ϱ�ֵ��4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RXA_DC_I_2_UNION;
#define ABB_CH1_REG_RXA_DC_I_2_ch1_rxa_dc_i_2_START  (4)
#define ABB_CH1_REG_RXA_DC_I_2_ch1_rxa_dc_i_2_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_RXA_DC_Q_2_UNION
 �ṹ˵��  : ch1_reg_rxa_dc_q_2 �Ĵ����ṹ���塣��ַƫ����:0x66����ֵ:0x00�����:8
 �Ĵ���˵��: RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_rxa_dc_q_2_reg;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: ���� */
        unsigned long  ch1_rxa_dc_q_2 : 4;  /* bit[4-7]: RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RXA_DC_Q_2_UNION;
#define ABB_CH1_REG_RXA_DC_Q_2_ch1_rxa_dc_q_2_START  (4)
#define ABB_CH1_REG_RXA_DC_Q_2_ch1_rxa_dc_q_2_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_RXB_DC_I_2_UNION
 �ṹ˵��  : ch1_reg_rxb_dc_i_2 �Ĵ����ṹ���塣��ַƫ����:0x68����ֵ:0x00�����:8
 �Ĵ���˵��: RXBͨ��I·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_rxb_dc_i_2_reg;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: ���� */
        unsigned long  ch1_rxb_dc_i_2 : 4;  /* bit[4-7]: RXB����I·�ź�BLOCKING DC�ϱ�ֵ��4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RXB_DC_I_2_UNION;
#define ABB_CH1_REG_RXB_DC_I_2_ch1_rxb_dc_i_2_START  (4)
#define ABB_CH1_REG_RXB_DC_I_2_ch1_rxb_dc_i_2_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_RXB_DC_Q_2_UNION
 �ṹ˵��  : ch1_reg_rxb_dc_q_2 �Ĵ����ṹ���塣��ַƫ����:0x6A����ֵ:0x00�����:8
 �Ĵ���˵��: RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_rxb_dc_q_2_reg;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: ���� */
        unsigned long  ch1_rxb_dc_q_2 : 4;  /* bit[4-7]: RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_RXB_DC_Q_2_UNION;
#define ABB_CH1_REG_RXB_DC_Q_2_ch1_rxb_dc_q_2_START  (4)
#define ABB_CH1_REG_RXB_DC_Q_2_ch1_rxb_dc_q_2_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_DIG0_UNION
 �ṹ˵��  : ch1_reg_debug_dig0 �Ĵ����ṹ���塣��ַƫ����:0x6B����ֵ:0x00�����:8
 �Ĵ���˵��: ���ֵ��ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_dig0_reg;
    struct
    {
        unsigned long  ch1_sdm_rst_ctrl : 1;  /* bit[0]  : TXͨ��SDMģ���쳣ʱ��λ����
                                                           0��ֻ��λSDMģ��
                                                           1����λ����TXͨ�� */
        unsigned long  ch1_dem_mode     : 1;  /* bit[1]  : TXͨ��DEMУ׼����ģʽ
                                                           0����������
                                                           1��У׼̬��DEM���Ϊdem_code_man */
        unsigned long  ch1_tx_dem_sat   : 2;  /* bit[2-3]: Reserved */
        unsigned long  ch1_dither_en    : 1;  /* bit[4]  : Reserved */
        unsigned long  reserved         : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_DIG0_UNION;
#define ABB_CH1_REG_DEBUG_DIG0_ch1_sdm_rst_ctrl_START  (0)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_sdm_rst_ctrl_END    (0)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_dem_mode_START      (1)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_dem_mode_END        (1)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_tx_dem_sat_START    (2)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_tx_dem_sat_END      (3)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_dither_en_START     (4)
#define ABB_CH1_REG_DEBUG_DIG0_ch1_dither_en_END       (4)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_DIG4_UNION
 �ṹ˵��  : ch1_reg_debug_dig4 �Ĵ����ṹ���塣��ַƫ����:0x6F����ֵ:0x00�����:8
 �Ĵ���˵��: ���ֵ��ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_dig4_reg;
    struct
    {
        unsigned long  reserved          : 4;  /* bit[0-3]: ���� */
        unsigned long  ch1_cic4_cic6_sel : 1;  /* bit[4]  : RXͨ��CIC4/CIC6�˲���ѡ��
                                                            0: ѡ��CIC4�˲���
                                                            1: ѡ��CIC6�˲��� */
        unsigned long  ch1_sw_gate_bp    : 1;  /* bit[5]  : �л��ſ�ʹ��bypass�źš�1��ʾ�ſ�ʹ�ܹ�����·�� */
        unsigned long  ch1_cic_rst_bp    : 1;  /* bit[6]  : �л���λbypass�źš�1��ʾ�л���λ������·�� */
        unsigned long  ch1_div_en_bp     : 1;  /* bit[7]  : div_en���Ʒ�Ƶ��bypass�źţ�0��div_en���Ʒ�Ƶ����1��div_en�����Ʒ�Ƶ������Ƶ��ʹ��ʼ��Ϊ1��. */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_DIG4_UNION;
#define ABB_CH1_REG_DEBUG_DIG4_ch1_cic4_cic6_sel_START  (4)
#define ABB_CH1_REG_DEBUG_DIG4_ch1_cic4_cic6_sel_END    (4)
#define ABB_CH1_REG_DEBUG_DIG4_ch1_sw_gate_bp_START     (5)
#define ABB_CH1_REG_DEBUG_DIG4_ch1_sw_gate_bp_END       (5)
#define ABB_CH1_REG_DEBUG_DIG4_ch1_cic_rst_bp_START     (6)
#define ABB_CH1_REG_DEBUG_DIG4_ch1_cic_rst_bp_END       (6)
#define ABB_CH1_REG_DEBUG_DIG4_ch1_div_en_bp_START      (7)
#define ABB_CH1_REG_DEBUG_DIG4_ch1_div_en_bp_END        (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_WR02_UNION
 �ṹ˵��  : ch1_reg_analog_wr02 �Ĵ����ṹ���塣��ַƫ����:0x70����ֵ:0x0F�����:8
 �Ĵ���˵��: Power Down���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr02_reg;
    struct
    {
        unsigned long  CH1_RXC_Q_PD   : 1;  /* bit[0]  : Reserved */
        unsigned long  CH1_RXC_I_PD   : 1;  /* bit[1]  : Reserved */
        unsigned long  CH1_PLL624_PD  : 1;  /* bit[2]  : PLLV2 Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��) */
        unsigned long  CH1_PLL6144_PD : 1;  /* bit[3]  : PLLV1 Power Down����
                                                         0:Power On(Ĭ��)
                                                         1:Power Down */
        unsigned long  reserved       : 4;  /* bit[4-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR02_UNION;
#define ABB_CH1_REG_ANALOG_WR02_CH1_RXC_Q_PD_START    (0)
#define ABB_CH1_REG_ANALOG_WR02_CH1_RXC_Q_PD_END      (0)
#define ABB_CH1_REG_ANALOG_WR02_CH1_RXC_I_PD_START    (1)
#define ABB_CH1_REG_ANALOG_WR02_CH1_RXC_I_PD_END      (1)
#define ABB_CH1_REG_ANALOG_WR02_CH1_PLL624_PD_START   (2)
#define ABB_CH1_REG_ANALOG_WR02_CH1_PLL624_PD_END     (2)
#define ABB_CH1_REG_ANALOG_WR02_CH1_PLL6144_PD_START  (3)
#define ABB_CH1_REG_ANALOG_WR02_CH1_PLL6144_PD_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_WR03_UNION
 �ṹ˵��  : ch1_reg_analog_wr03 �Ĵ����ṹ���塣��ַƫ����:0x71����ֵ:0x30�����:8
 �Ĵ���˵��: ��ģ�ӿ�ʱ�ӿ��ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr03_reg;
    struct
    {
        unsigned long  reserved_0        : 3;  /* bit[0-2]: Reserved */
        unsigned long  CH1_TX_CLKD_CTRL  : 1;  /* bit[3]  : TX ����ʱ����ѡ��
                                                            0: ����
                                                            1: ����(Ĭ��) */
        unsigned long  CH1_CLK_61D44M_PD : 1;  /* bit[4]  : CLK_61D44M Power Down����
                                                            0:Power On
                                                            1:Power Down(Ĭ��) */
        unsigned long  CH1_CLK_52M_PD    : 1;  /* bit[5]  : CLK_52M Power Down����
                                                            0:Power On
                                                            1:Power Down(Ĭ��) */
        unsigned long  CH1_245M_EN       : 1;  /* bit[6]  : 245M������ƣ�
                                                            0: �����
                                                            1: ��� */
        unsigned long  reserved_1        : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR03_UNION;
#define ABB_CH1_REG_ANALOG_WR03_CH1_TX_CLKD_CTRL_START   (3)
#define ABB_CH1_REG_ANALOG_WR03_CH1_TX_CLKD_CTRL_END     (3)
#define ABB_CH1_REG_ANALOG_WR03_CH1_CLK_61D44M_PD_START  (4)
#define ABB_CH1_REG_ANALOG_WR03_CH1_CLK_61D44M_PD_END    (4)
#define ABB_CH1_REG_ANALOG_WR03_CH1_CLK_52M_PD_START     (5)
#define ABB_CH1_REG_ANALOG_WR03_CH1_CLK_52M_PD_END       (5)
#define ABB_CH1_REG_ANALOG_WR03_CH1_245M_EN_START        (6)
#define ABB_CH1_REG_ANALOG_WR03_CH1_245M_EN_END          (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_WR04_UNION
 �ṹ˵��  : ch1_reg_analog_wr04 �Ĵ����ṹ���塣��ַƫ����:0x72����ֵ:0x0C�����:8
 �Ĵ���˵��: Other���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr04_reg;
    struct
    {
        unsigned long  CH1_EN_CAL       : 1;  /* bit[0]  : Calibration enable��Ĭ��Ϊ0��
                                                           ����������Calibration���� */
        unsigned long  reserved_0       : 1;  /* bit[1]  : Reserved */
        unsigned long  CH1_TX_AUTO_TUNE : 1;  /* bit[2]  : TX ADC�Զ�tuning����
                                                           0���ֶ�tuning��tuningѡ��TX_TUNE1,TX_TUNE2,TX_TUNE3��ֵ(Ĭ��)
                                                           1���Զ�tuning��TXͨ����calibrationֵΪCAL_VALUE */
        unsigned long  CH1_RX_AUTO_TUNE : 1;  /* bit[3]  : RX ADC�Զ�tuning����
                                                           0���ֶ�tuning��tuningѡ��RX_TUNE1,RX_TUNE2,RX_TUNE3��ֵ(Ĭ��)
                                                           1���Զ�tuning��RXͨ����calibrationֵΪCAL_VALUE */
        unsigned long  reserved_1       : 4;  /* bit[4-7]: Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR04_UNION;
#define ABB_CH1_REG_ANALOG_WR04_CH1_EN_CAL_START        (0)
#define ABB_CH1_REG_ANALOG_WR04_CH1_EN_CAL_END          (0)
#define ABB_CH1_REG_ANALOG_WR04_CH1_TX_AUTO_TUNE_START  (2)
#define ABB_CH1_REG_ANALOG_WR04_CH1_TX_AUTO_TUNE_END    (2)
#define ABB_CH1_REG_ANALOG_WR04_CH1_RX_AUTO_TUNE_START  (3)
#define ABB_CH1_REG_ANALOG_WR04_CH1_RX_AUTO_TUNE_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_WR05_UNION
 �ṹ˵��  : ch1_reg_analog_wr05 �Ĵ����ṹ���塣��ַƫ����:0x73����ֵ:0x40�����:8
 �Ĵ���˵��: ADC��һ������������tuning�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr05_reg;
    struct
    {
        unsigned long  CH1_RX_TUNE1 : 7;  /* bit[0-6]: ADC��һ������������tuning */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR05_UNION;
#define ABB_CH1_REG_ANALOG_WR05_CH1_RX_TUNE1_START  (0)
#define ABB_CH1_REG_ANALOG_WR05_CH1_RX_TUNE1_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_WR06_UNION
 �ṹ˵��  : ch1_reg_analog_wr06 �Ĵ����ṹ���塣��ַƫ����:0x74����ֵ:0x40�����:8
 �Ĵ���˵��: ADC�ڶ�������������tuning�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr06_reg;
    struct
    {
        unsigned long  CH1_RX_TUNE2 : 7;  /* bit[0-6]: ADC�ڶ�������������tuning */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR06_UNION;
#define ABB_CH1_REG_ANALOG_WR06_CH1_RX_TUNE2_START  (0)
#define ABB_CH1_REG_ANALOG_WR06_CH1_RX_TUNE2_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_WR07_UNION
 �ṹ˵��  : ch1_reg_analog_wr07 �Ĵ����ṹ���塣��ַƫ����:0x75����ֵ:0x40�����:8
 �Ĵ���˵��: ADC����������������tuning�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr07_reg;
    struct
    {
        unsigned long  CH1_RX_TUNE3 : 7;  /* bit[0-6]: ADC����������������tuning */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR07_UNION;
#define ABB_CH1_REG_ANALOG_WR07_CH1_RX_TUNE3_START  (0)
#define ABB_CH1_REG_ANALOG_WR07_CH1_RX_TUNE3_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_WR08_UNION
 �ṹ˵��  : ch1_reg_analog_wr08 �Ĵ����ṹ���塣��ַƫ����:0x76����ֵ:0x40�����:8
 �Ĵ���˵��: DAC Tuning���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr08_reg;
    struct
    {
        unsigned long  CH1_TX_TUNE1 : 7;  /* bit[0-6]: TX_TUNE1�����ź� */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR08_UNION;
#define ABB_CH1_REG_ANALOG_WR08_CH1_TX_TUNE1_START  (0)
#define ABB_CH1_REG_ANALOG_WR08_CH1_TX_TUNE1_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_WR09_UNION
 �ṹ˵��  : ch1_reg_analog_wr09 �Ĵ����ṹ���塣��ַƫ����:0x77����ֵ:0x40�����:8
 �Ĵ���˵��: DAC Tuning���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr09_reg;
    struct
    {
        unsigned long  CH1_TX_TUNE2 : 7;  /* bit[0-6]: TX_TUNE2�����ź� */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR09_UNION;
#define ABB_CH1_REG_ANALOG_WR09_CH1_TX_TUNE2_START  (0)
#define ABB_CH1_REG_ANALOG_WR09_CH1_TX_TUNE2_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_WR10_UNION
 �ṹ˵��  : ch1_reg_analog_wr10 �Ĵ����ṹ���塣��ַƫ����:0x78����ֵ:0x40�����:8
 �Ĵ���˵��: DAC Tuning���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr10_reg;
    struct
    {
        unsigned long  CH1_TX_TUNE3 : 7;  /* bit[0-6]: TX_TUNE3�����ź� */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR10_UNION;
#define ABB_CH1_REG_ANALOG_WR10_CH1_TX_TUNE3_START  (0)
#define ABB_CH1_REG_ANALOG_WR10_CH1_TX_TUNE3_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_WR38_UNION
 �ṹ˵��  : ch1_reg_analog_wr38 �Ĵ����ṹ���塣��ַƫ����:0x79����ֵ:0x60�����:8
 �Ĵ���˵��: ��ģ��ƽ���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr38_reg;
    struct
    {
        unsigned long  reserved              : 3;  /* bit[0-2]: Reserved */
        unsigned long  CH1_OFFSET_CAL_DAC_EN : 1;  /* bit[3]  : Reserved */
        unsigned long  CH1_SARADC_REF_RANGE  : 1;  /* bit[4]  : Reserved */
        unsigned long  CH1_TX_CM_CON_MODE    : 2;  /* bit[5-6]: Reserved */
        unsigned long  CH1_RX_ADC_CM_CON_EN  : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR38_UNION;
#define ABB_CH1_REG_ANALOG_WR38_CH1_OFFSET_CAL_DAC_EN_START  (3)
#define ABB_CH1_REG_ANALOG_WR38_CH1_OFFSET_CAL_DAC_EN_END    (3)
#define ABB_CH1_REG_ANALOG_WR38_CH1_SARADC_REF_RANGE_START   (4)
#define ABB_CH1_REG_ANALOG_WR38_CH1_SARADC_REF_RANGE_END     (4)
#define ABB_CH1_REG_ANALOG_WR38_CH1_TX_CM_CON_MODE_START     (5)
#define ABB_CH1_REG_ANALOG_WR38_CH1_TX_CM_CON_MODE_END       (6)
#define ABB_CH1_REG_ANALOG_WR38_CH1_RX_ADC_CM_CON_EN_START   (7)
#define ABB_CH1_REG_ANALOG_WR38_CH1_RX_ADC_CM_CON_EN_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_WR39_UNION
 �ṹ˵��  : ch1_reg_analog_wr39 �Ĵ����ṹ���塣��ַƫ����:0x7A����ֵ:0x03�����:8
 �Ĵ���˵��: DUM���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_wr39_reg;
    struct
    {
        unsigned long  CH1_DUM_EN_Q   : 1;  /* bit[0]  : TX Q channel  dummy logic control signal
                                                         1: enable(Ĭ��)
                                                         0: disable */
        unsigned long  CH1_DUM_EN_I   : 1;  /* bit[1]  : TX I channel  dummy logic control signal
                                                         1: enable(Ĭ��)
                                                         0: disable */
        unsigned long  reserved       : 5;  /* bit[2-6]: Reserved */
        unsigned long  CH1_DEM_MOD_B2 : 1;  /* bit[7]  : RX DEM Mode Selection,bit 2
                                                         000: DWA
                                                         001: CLA1
                                                         010: CLA2
                                                         011: CLA3
                                                         100: CLA4
                                                         101: CLA5
                                                         110: CLA6
                                                         111: CLA7 */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_WR39_UNION;
#define ABB_CH1_REG_ANALOG_WR39_CH1_DUM_EN_Q_START    (0)
#define ABB_CH1_REG_ANALOG_WR39_CH1_DUM_EN_Q_END      (0)
#define ABB_CH1_REG_ANALOG_WR39_CH1_DUM_EN_I_START    (1)
#define ABB_CH1_REG_ANALOG_WR39_CH1_DUM_EN_I_END      (1)
#define ABB_CH1_REG_ANALOG_WR39_CH1_DEM_MOD_B2_START  (7)
#define ABB_CH1_REG_ANALOG_WR39_CH1_DEM_MOD_B2_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_RO0_UNION
 �ṹ˵��  : ch1_reg_analog_ro0 �Ĵ����ṹ���塣��ַƫ����:0x7B����ֵ:0x00�����:8
 �Ĵ���˵��: ��־λֻ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_ro0_reg;
    struct
    {
        unsigned long  reserved     : 5;  /* bit[0-4]: Reserved */
        unsigned long  CH1_CAL_DONE : 1;  /* bit[5]  : RC Calibration Done�ź� */
        unsigned long  CH1_LOCK2    : 1;  /* bit[6]  : GPLL��LOCK�ź� */
        unsigned long  CH1_LOCK1    : 1;  /* bit[7]  : WPLL��LOCK�ź� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_RO0_UNION;
#define ABB_CH1_REG_ANALOG_RO0_CH1_CAL_DONE_START  (5)
#define ABB_CH1_REG_ANALOG_RO0_CH1_CAL_DONE_END    (5)
#define ABB_CH1_REG_ANALOG_RO0_CH1_LOCK2_START     (6)
#define ABB_CH1_REG_ANALOG_RO0_CH1_LOCK2_END       (6)
#define ABB_CH1_REG_ANALOG_RO0_CH1_LOCK1_START     (7)
#define ABB_CH1_REG_ANALOG_RO0_CH1_LOCK1_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_ANALOG_RO1_UNION
 �ṹ˵��  : ch1_reg_analog_ro1 �Ĵ����ṹ���塣��ַƫ����:0x7C����ֵ:0x00�����:8
 �Ĵ���˵��: RCУ׼ֻ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_analog_ro1_reg;
    struct
    {
        unsigned long  CH1_RX_CAL_VALUE : 7;  /* bit[0-6]: RC CalibrationУ׼ֵ */
        unsigned long  reserved         : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_ANALOG_RO1_UNION;
#define ABB_CH1_REG_ANALOG_RO1_CH1_RX_CAL_VALUE_START  (0)
#define ABB_CH1_REG_ANALOG_RO1_CH1_RX_CAL_VALUE_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA0_UNION
 �ṹ˵��  : ch1_reg_debug_ana0 �Ĵ����ṹ���塣��ַƫ����:0x80����ֵ:0x32�����:8
 �Ĵ���˵��: ģ����ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana0_reg;
    struct
    {
        unsigned long  CH1_CLK_REF_SEL  : 1;  /* bit[0]  : PLL�Ĳο�ʱ��ѡ��
                                                           1: CLKIN_SYSTEM��ΪPLL�Ĳο�ʱ��
                                                           0: TCXO Buffer�����ΪPLL�ο�ʱ�� */
        unsigned long  CH1_PLL_OCLK_SEL : 3;  /* bit[1-3]: ����ʱ��ѡ��
                                                           001��ѡ��������PLL��ʱ����Ϊ����ʱ��
                                                           010��ѡ��������CLKIN_SYSTEM�����ʱ����Ϊ����ʱ��
                                                           100��ѡ��������TCXO_IN��ʱ����Ϊ����ʱ�� */
        unsigned long  CH1_PLL_PFD_CTRL : 2;  /* bit[4-5]: PLL��Ƶ����������
                                                           x0����Ƶ������һֱ���Up�ź�
                                                           01: ��Ƶ������һֱ���Down�ź�
                                                           11����Ƶ�������������� */
        unsigned long  reserved         : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA0_UNION;
#define ABB_CH1_REG_DEBUG_ANA0_CH1_CLK_REF_SEL_START   (0)
#define ABB_CH1_REG_DEBUG_ANA0_CH1_CLK_REF_SEL_END     (0)
#define ABB_CH1_REG_DEBUG_ANA0_CH1_PLL_OCLK_SEL_START  (1)
#define ABB_CH1_REG_DEBUG_ANA0_CH1_PLL_OCLK_SEL_END    (3)
#define ABB_CH1_REG_DEBUG_ANA0_CH1_PLL_PFD_CTRL_START  (4)
#define ABB_CH1_REG_DEBUG_ANA0_CH1_PLL_PFD_CTRL_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA1_UNION
 �ṹ˵��  : ch1_reg_debug_ana1 �Ĵ����ṹ���塣��ַƫ����:0x81����ֵ:0x00�����:8
 �Ĵ���˵��: PLL LOCK���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana1_reg;
    struct
    {
        unsigned long  reserved_0     : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH1_GPLL_LK_EN : 1;  /* bit[4]  : GPLL�������ʹ��
                                                         0�����ֹͣ
                                                         1����⿪ʼ */
        unsigned long  CH1_WPLL_LK_EN : 1;  /* bit[5]  : WPLL�������ʹ��
                                                         0�����ֹͣ
                                                         1����⿪ʼ */
        unsigned long  reserved_1     : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA1_UNION;
#define ABB_CH1_REG_DEBUG_ANA1_CH1_GPLL_LK_EN_START  (4)
#define ABB_CH1_REG_DEBUG_ANA1_CH1_GPLL_LK_EN_END    (4)
#define ABB_CH1_REG_DEBUG_ANA1_CH1_WPLL_LK_EN_START  (5)
#define ABB_CH1_REG_DEBUG_ANA1_CH1_WPLL_LK_EN_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA2_UNION
 �ṹ˵��  : ch1_reg_debug_ana2 �Ĵ����ṹ���塣��ַƫ����:0x82����ֵ:0x80�����:8
 �Ĵ���˵��: PLL���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana2_reg;
    struct
    {
        unsigned long  CH1_PLL_CP_PD : 2;  /* bit[0-1]: PLL CP PowerDown���ƣ�������
                                                        00����������
                                                        01: PowerDown WPLL CP 
                                                        10: PowerDown GPLL CP 
                                                        11: PowerDown WPLL CP��GPLL CP */
        unsigned long  reserved      : 5;  /* bit[2-6]: Reserved */
        unsigned long  CH1_CLKN_EN   : 1;  /* bit[7]  : ����ʱ�ӿ���
                                                        1: ����ʱ�Ӵ�
                                                        0: ����ʱ�ӹر� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA2_UNION;
#define ABB_CH1_REG_DEBUG_ANA2_CH1_PLL_CP_PD_START  (0)
#define ABB_CH1_REG_DEBUG_ANA2_CH1_PLL_CP_PD_END    (1)
#define ABB_CH1_REG_DEBUG_ANA2_CH1_CLKN_EN_START    (7)
#define ABB_CH1_REG_DEBUG_ANA2_CH1_CLKN_EN_END      (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA3_UNION
 �ṹ˵��  : ch1_reg_debug_ana3 �Ĵ����ṹ���塣��ַƫ����:0x83����ֵ:0x80�����:8
 �Ĵ���˵��: PLL���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana3_reg;
    struct
    {
        unsigned long  reserved         : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH1_GPLL_CP_CTRL : 4;  /* bit[4-7]: GPLL��ɱõ�������(����Ч)
                                                           Basic: 0.25*Icp
                                                           Bit0:  0.25*Icp
                                                           Bit1:  0.25*Icp
                                                           Bit2:  0.5*Icp
                                                           Bit3:  0.5*Icp */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA3_UNION;
#define ABB_CH1_REG_DEBUG_ANA3_CH1_GPLL_CP_CTRL_START  (4)
#define ABB_CH1_REG_DEBUG_ANA3_CH1_GPLL_CP_CTRL_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA4_UNION
 �ṹ˵��  : ch1_reg_debug_ana4 �Ĵ����ṹ���塣��ַƫ����:0x84����ֵ:0x80�����:8
 �Ĵ���˵��: PLL���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana4_reg;
    struct
    {
        unsigned long  reserved         : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH1_WPLL_CP_CTRL : 4;  /* bit[4-7]: WPLL��ɱõ�������(����Ч)
                                                           Basic: 0.25*Icp
                                                           Bit0:  0.25*Icp
                                                           Bit1:  0.25*Icp
                                                           Bit2:  0.5*Icp
                                                           Bit3:  0.5*Icp */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA4_UNION;
#define ABB_CH1_REG_DEBUG_ANA4_CH1_WPLL_CP_CTRL_START  (4)
#define ABB_CH1_REG_DEBUG_ANA4_CH1_WPLL_CP_CTRL_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA5_UNION
 �ṹ˵��  : ch1_reg_debug_ana5 �Ĵ����ṹ���塣��ַƫ����:0x85����ֵ:0x00�����:8
 �Ĵ���˵��: �����������ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana5_reg;
    struct
    {
        unsigned long  reserved         : 7;  /* bit[0-6]: Reserved */
        unsigned long  CH1_BG_FASTUP_EN : 1;  /* bit[7]  : 0 disable
                                                           1 enable */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA5_UNION;
#define ABB_CH1_REG_DEBUG_ANA5_CH1_BG_FASTUP_EN_START  (7)
#define ABB_CH1_REG_DEBUG_ANA5_CH1_BG_FASTUP_EN_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA6_UNION
 �ṹ˵��  : ch1_reg_debug_ana6 �Ĵ����ṹ���塣��ַƫ����:0x86����ֵ:0x41�����:8
 �Ĵ���˵��: Bandgap��TCXO���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana6_reg;
    struct
    {
        unsigned long  CH1_G_FREF_SEL : 1;  /* bit[0]  : GPLL�ο�Ƶ������
                                                         1: 19.2MHz�ο�ʱ�ӣ�����ģʽ
                                                         0: 26MHz�ο�ʱ�ӣ�����ģʽ */
        unsigned long  reserved       : 3;  /* bit[1-3]: Reserved */
        unsigned long  CH1_TCXO_DRV   : 2;  /* bit[4-5]: TCXO BUFFER��������
                                                         00: 1x
                                                         01: 2x
                                                         10: 3x
                                                         11: 4x */
        unsigned long  CH1_CLKIN_PD   : 1;  /* bit[6]  : TEST CLK INPUT�µ����
                                                         0: ����
                                                         1: �ر� */
        unsigned long  CH1_HOLD_BG    : 1;  /* bit[7]  : Sleepģʽʱ�Ƿ񱣳�Bandgap�����Ŀ����źţ�����refgenģ�������PD_BG�źŹ�ͬ����Bandgap��״̬
                                                         0: Bandgap״̬��PD_BG�źſ��ƣ�������Sleepģʽʱ��Bandgap���رգ�����Bandgap����
                                                         1: Bandgapʼ�չ��� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA6_UNION;
#define ABB_CH1_REG_DEBUG_ANA6_CH1_G_FREF_SEL_START  (0)
#define ABB_CH1_REG_DEBUG_ANA6_CH1_G_FREF_SEL_END    (0)
#define ABB_CH1_REG_DEBUG_ANA6_CH1_TCXO_DRV_START    (4)
#define ABB_CH1_REG_DEBUG_ANA6_CH1_TCXO_DRV_END      (5)
#define ABB_CH1_REG_DEBUG_ANA6_CH1_CLKIN_PD_START    (6)
#define ABB_CH1_REG_DEBUG_ANA6_CH1_CLKIN_PD_END      (6)
#define ABB_CH1_REG_DEBUG_ANA6_CH1_HOLD_BG_START     (7)
#define ABB_CH1_REG_DEBUG_ANA6_CH1_HOLD_BG_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA7_UNION
 �ṹ˵��  : ch1_reg_debug_ana7 �Ĵ����ṹ���塣��ַƫ����:0x87����ֵ:0x00�����:8
 �Ĵ���˵��: �������ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana7_reg;
    struct
    {
        unsigned long  CH1_DRVBUF_CT : 3;  /* bit[0-2]: L/W/G ����ADC ���Buffer�������ڿ���
                                                        000: 1.0x��Ĭ�ϣ�
                                                        001: 0.2x
                                                        010: 0.6x
                                                        011: 0.3x
                                                        100: 0.4x
                                                        101: 0.8x
                                                        110: 1.4x
                                                        111: 1.6x */
        unsigned long  CH1_IREF_CTRL : 3;  /* bit[3-5]: �����ο���������
                                                        000��5u
                                                        001��2u
                                                        010��3u
                                                        011��4u
                                                        100��6u
                                                        101��7u
                                                        110��8u
                                                        111��9u */
        unsigned long  reserved      : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA7_UNION;
#define ABB_CH1_REG_DEBUG_ANA7_CH1_DRVBUF_CT_START  (0)
#define ABB_CH1_REG_DEBUG_ANA7_CH1_DRVBUF_CT_END    (2)
#define ABB_CH1_REG_DEBUG_ANA7_CH1_IREF_CTRL_START  (3)
#define ABB_CH1_REG_DEBUG_ANA7_CH1_IREF_CTRL_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA8_UNION
 �ṹ˵��  : ch1_reg_debug_ana8 �Ĵ����ṹ���塣��ַƫ����:0x88����ֵ:0x00�����:8
 �Ĵ���˵��: �������ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana8_reg;
    struct
    {
        unsigned long  CH1_TX_CURRENT : 4;  /* bit[0-3]: ����TXͨ��LPF��·��������
                                                         0000��1.0x
                                                         0001��0.9x
                                                         0010��0.8x
                                                         0011��0.7x
                                                         0100��2.0x
                                                         0101��1.8x
                                                         0110��1.6x
                                                         0111��1.4x
                                                         1xxx��Reserved */
        unsigned long  CH1_QU_MODE    : 1;  /* bit[4]  : ������ģʽѡ�� */
        unsigned long  reserved       : 3;  /* bit[5-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA8_UNION;
#define ABB_CH1_REG_DEBUG_ANA8_CH1_TX_CURRENT_START  (0)
#define ABB_CH1_REG_DEBUG_ANA8_CH1_TX_CURRENT_END    (3)
#define ABB_CH1_REG_DEBUG_ANA8_CH1_QU_MODE_START     (4)
#define ABB_CH1_REG_DEBUG_ANA8_CH1_QU_MODE_END       (4)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA9_UNION
 �ṹ˵��  : ch1_reg_debug_ana9 �Ĵ����ṹ���塣��ַƫ����:0x89����ֵ:0x00�����:8
 �Ĵ���˵��: ADC���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana9_reg;
    struct
    {
        unsigned long  CH1_DAC_DUM_B0   : 1;  /* bit[0]  : RX����sub_DAC Dummy��Ԫ���ƣ���һλ
                                                           0������
                                                           1���ر� */
        unsigned long  CH1_L_PUP_MODE   : 1;  /* bit[1]  : LTE ADCģ������ģʽѡ��
                                                           0���Զ�ģʽ
                                                           1�����üĴ���ģʽ */
        unsigned long  CH1_IB_SEL       : 1;  /* bit[2]  : ���������������ĵ����Ƿ�ɵ�
                                                           0�����ɵ�
                                                           1���ɵ� */
        unsigned long  CH1_L_DEM_PD     : 1;  /* bit[3]  : LTE ADC DEM���ܹر��ź�
                                                           0��DEMʹ��
                                                           1��DEM��ʹ�� */
        unsigned long  CH1_L_TUNING_SEL : 1;  /* bit[4]  : LTE ADCģ��Tuning���ѡ��
                                                           0��ѡ��Tuningģ��������ΪLTE ADC��Tuning��
                                                           1��ѡ��Ĵ����������ΪLTE ADC��Tuning�� */
        unsigned long  CH1_RX_IBCT_DAC  : 3;  /* bit[5-7]: RX����sub_DAC��������
                                                           000: 1.0x
                                                           001: 0.2x
                                                           010: 0.6x
                                                           011: 0.3x
                                                           100: 0.4x
                                                           101: 0.8x
                                                           110: 1.4x
                                                           111: 1.6x */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA9_UNION;
#define ABB_CH1_REG_DEBUG_ANA9_CH1_DAC_DUM_B0_START    (0)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_DAC_DUM_B0_END      (0)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_L_PUP_MODE_START    (1)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_L_PUP_MODE_END      (1)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_IB_SEL_START        (2)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_IB_SEL_END          (2)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_L_DEM_PD_START      (3)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_L_DEM_PD_END        (3)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_L_TUNING_SEL_START  (4)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_L_TUNING_SEL_END    (4)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_RX_IBCT_DAC_START   (5)
#define ABB_CH1_REG_DEBUG_ANA9_CH1_RX_IBCT_DAC_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA10_UNION
 �ṹ˵��  : ch1_reg_debug_ana10 �Ĵ����ṹ���塣��ַƫ����:0x8A����ֵ:0x00�����:8
 �Ĵ���˵��: ADC��λ���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana10_reg;
    struct
    {
        unsigned long  CH1_DAC_DUM_B2B1 : 2;  /* bit[0-1]: RX����sub_DAC Dummy��Ԫ���ƣ�����λ
                                                           0������
                                                           1���ر� */
        unsigned long  CH1_L_PUP_CTRL0  : 1;  /* bit[2]  : LTE ADC�е�һ�����������ݸ�λ����
                                                           0������λ
                                                           1����λ */
        unsigned long  CH1_L_PUP_CTRL1  : 1;  /* bit[3]  : LTE ADC�еڶ������������ݸ�λ����
                                                           0������λ
                                                           1����λ */
        unsigned long  CH1_L_PUP_CTRL2  : 1;  /* bit[4]  : LTE ADC�е��������������ݸ�λ����
                                                           0: ����λ
                                                           1����λ */
        unsigned long  CH1_L_PUP_CTRL3  : 1;  /* bit[5]  : LTE ADC��CKGENģ��Powerup����
                                                           0��Powerdown
                                                           1��Powerup */
        unsigned long  CH1_L_PUP_CTRL4  : 1;  /* bit[6]  : LTE ADC��OPģ��Powerup����
                                                           0��Powerdown
                                                           1��Powerup */
        unsigned long  CH1_L_PUP_CTRL5  : 1;  /* bit[7]  : LTE ADC��DACģ��Powerup����
                                                           0��Powerdown
                                                           1��Powerup */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA10_UNION;
#define ABB_CH1_REG_DEBUG_ANA10_CH1_DAC_DUM_B2B1_START  (0)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_DAC_DUM_B2B1_END    (1)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL0_START   (2)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL0_END     (2)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL1_START   (3)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL1_END     (3)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL2_START   (4)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL2_END     (4)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL3_START   (5)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL3_END     (5)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL4_START   (6)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL4_END     (6)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL5_START   (7)
#define ABB_CH1_REG_DEBUG_ANA10_CH1_L_PUP_CTRL5_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA14_UNION
 �ṹ˵��  : ch1_reg_debug_ana14 �Ĵ����ṹ���塣��ַƫ����:0x8E����ֵ:0x00�����:8
 �Ĵ���˵��: ADC���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana14_reg;
    struct
    {
        unsigned long  CH1_L_OL_CT   : 3;  /* bit[0-2]: LTE Overloadģ������
                                                        00��16����������������С��
                                                        01��8����������������С��
                                                        10��4����������������С��
                                                        11���ر�Overload��� */
        unsigned long  CH1_L_ADC_ICT : 3;  /* bit[3-5]: LTE ADC ����ƫ�õ���
                                                        000: 1.0x
                                                        001: 0.2x
                                                        010: 0.6x
                                                        011: 0.3x
                                                        100: 0.4x
                                                        101: 0.8x
                                                        110: 1.4x
                                                        111: 1.6x */
        unsigned long  CH1_L_CK_CT   : 2;  /* bit[6-7]: LTE SYNCʱ�����
                                                        00��No delay
                                                        01��250ps delay
                                                        10��500ps delay
                                                        11��1000ps delay */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA14_UNION;
#define ABB_CH1_REG_DEBUG_ANA14_CH1_L_OL_CT_START    (0)
#define ABB_CH1_REG_DEBUG_ANA14_CH1_L_OL_CT_END      (2)
#define ABB_CH1_REG_DEBUG_ANA14_CH1_L_ADC_ICT_START  (3)
#define ABB_CH1_REG_DEBUG_ANA14_CH1_L_ADC_ICT_END    (5)
#define ABB_CH1_REG_DEBUG_ANA14_CH1_L_CK_CT_START    (6)
#define ABB_CH1_REG_DEBUG_ANA14_CH1_L_CK_CT_END      (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA16_UNION
 �ṹ˵��  : ch1_reg_debug_ana16 �Ĵ����ṹ���塣��ַƫ����:0x90����ֵ:0x00�����:8
 �Ĵ���˵��: ADC���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana16_reg;
    struct
    {
        unsigned long  CH1_IBCT_STG12 : 3;  /* bit[0-2]: RX ADC Stage 12��������
                                                         000: 1.0x
                                                         001: 0.2x
                                                         010: 0.6x
                                                         011: 0.3x
                                                         100: 0.4x
                                                         101: 0.8x
                                                         110: 1.4x
                                                         111: 1.6x */
        unsigned long  CH1_IBCT_STG3  : 3;  /* bit[3-5]: RX ADC Stage 3��������
                                                         000: 1.0x
                                                         001: 0.2x
                                                         010: 0.6x
                                                         011: 0.3x
                                                         100: 0.4x
                                                         101: 0.8x
                                                         110: 1.4x
                                                         111: 1.6x */
        unsigned long  CH1_PDM_CTRL   : 1;  /* bit[6]  : RX���PDM�������
                                                         0��adder encoder
                                                         1��de-bubble encoder */
        unsigned long  CH1_G_I_CTRL   : 1;  /* bit[7]  : Gģʽ��������
                                                         0��������˷�����
                                                         1��������˷����� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA16_UNION;
#define ABB_CH1_REG_DEBUG_ANA16_CH1_IBCT_STG12_START  (0)
#define ABB_CH1_REG_DEBUG_ANA16_CH1_IBCT_STG12_END    (2)
#define ABB_CH1_REG_DEBUG_ANA16_CH1_IBCT_STG3_START   (3)
#define ABB_CH1_REG_DEBUG_ANA16_CH1_IBCT_STG3_END     (5)
#define ABB_CH1_REG_DEBUG_ANA16_CH1_PDM_CTRL_START    (6)
#define ABB_CH1_REG_DEBUG_ANA16_CH1_PDM_CTRL_END      (6)
#define ABB_CH1_REG_DEBUG_ANA16_CH1_G_I_CTRL_START    (7)
#define ABB_CH1_REG_DEBUG_ANA16_CH1_G_I_CTRL_END      (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA17_UNION
 �ṹ˵��  : ch1_reg_debug_ana17 �Ĵ����ṹ���塣��ַƫ����:0x91����ֵ:0x00�����:8
 �Ĵ���˵��: PLL���ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana17_reg;
    struct
    {
        unsigned long  reserved          : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH1_PLL1_CLK_TEST : 2;  /* bit[4-5]: PLLʱ�Ӳ���PAD�ź�ѡ��
                                                            00��ʱ�Ӳ���PAD����
                                                            01��WPLL���ʱ�ӵ�PAD
                                                            10��GPLL���ʱ�ӵ�PAD */
        unsigned long  CH1_PLL1_ANA_TEST : 2;  /* bit[6-7]: PLL���Ƶ�ѹ����PAD�ź�ѡ��
                                                            00�����Ƶ�ѹ����PAD����
                                                            01��WPLL������Ƶ�ѹ��PAD
                                                            10��GPLL������Ƶ�ѹ��PAD */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA17_UNION;
#define ABB_CH1_REG_DEBUG_ANA17_CH1_PLL1_CLK_TEST_START  (4)
#define ABB_CH1_REG_DEBUG_ANA17_CH1_PLL1_CLK_TEST_END    (5)
#define ABB_CH1_REG_DEBUG_ANA17_CH1_PLL1_ANA_TEST_START  (6)
#define ABB_CH1_REG_DEBUG_ANA17_CH1_PLL1_ANA_TEST_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA19_UNION
 �ṹ˵��  : ch1_reg_debug_ana19 �Ĵ����ṹ���塣��ַƫ����:0x93����ֵ:0x3C�����:8
 �Ĵ���˵��: ʱ�ӷ��ؿ��ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana19_reg;
    struct
    {
        unsigned long  CH1_CLK_PADF_SEL : 2;  /* bit[0-1]: ���Թܽ����ʱ��Ƶ�ʿ���
                                                           00: ������ʱ��
                                                           01��WPLL�������
                                                           10��GPLL�������
                                                           11��WPLL��GPLL������� */
        unsigned long  CH1_HK_CLK_EN    : 1;  /* bit[2]  : HKADC��Tuningģ��ʱ��ʹ���ź�
                                                           0��ʱ�ӹر�
                                                           1��ʱ��ʹ�� */
        unsigned long  CH1_AUX_CLK_EN   : 1;  /* bit[3]  : PLLģ��153.6MHzʱ��ʹ���ź�
                                                           0��ʱ�ӹر�
                                                           1��ʱ��ʹ�� */
        unsigned long  CH1_DAC_CLK_EN   : 1;  /* bit[4]  : PLLģ��307.2MHzʱ��ʹ���ź�
                                                           0��ʱ�ӹر�
                                                           1��ʱ��ʹ�� */
        unsigned long  CH1_ADC_CLK_EN   : 1;  /* bit[5]  : PLLģ��307.2MHzʱ��ʹ���ź�
                                                           0��ʱ�ӹر�
                                                           1��ʱ��ʹ�� */
        unsigned long  reserved         : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA19_UNION;
#define ABB_CH1_REG_DEBUG_ANA19_CH1_CLK_PADF_SEL_START  (0)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_CLK_PADF_SEL_END    (1)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_HK_CLK_EN_START     (2)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_HK_CLK_EN_END       (2)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_AUX_CLK_EN_START    (3)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_AUX_CLK_EN_END      (3)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_DAC_CLK_EN_START    (4)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_DAC_CLK_EN_END      (4)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_ADC_CLK_EN_START    (5)
#define ABB_CH1_REG_DEBUG_ANA19_CH1_ADC_CLK_EN_END      (5)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_DEBUG_ANA20_UNION
 �ṹ˵��  : ch1_reg_debug_ana20 �Ĵ����ṹ���塣��ַƫ����:0x94����ֵ:0x20�����:8
 �Ĵ���˵��: ģ����ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_reg_debug_ana20_reg;
    struct
    {
        unsigned long  reserved      : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH1_EXT_BG_EN : 1;  /* bit[4]  : �ⲿBandGapʹ���ź� */
        unsigned long  CH1_CAP_MULT  : 2;  /* bit[5-6]: ���������������ݵ��� */
        unsigned long  CH1_CAP_SEL   : 1;  /* bit[7]  : Tuning��·����ѡ��
                                                        0: �����
                                                        1: С���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_REG_DEBUG_ANA20_UNION;
#define ABB_CH1_REG_DEBUG_ANA20_CH1_EXT_BG_EN_START  (4)
#define ABB_CH1_REG_DEBUG_ANA20_CH1_EXT_BG_EN_END    (4)
#define ABB_CH1_REG_DEBUG_ANA20_CH1_CAP_MULT_START   (5)
#define ABB_CH1_REG_DEBUG_ANA20_CH1_CAP_MULT_END     (6)
#define ABB_CH1_REG_DEBUG_ANA20_CH1_CAP_SEL_START    (7)
#define ABB_CH1_REG_DEBUG_ANA20_CH1_CAP_SEL_END      (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_2G_RX_DELAY_UNION
 �ṹ˵��  : ch1_2g_rx_delay �Ĵ����ṹ���塣��ַƫ����:0x9C����ֵ:0x20�����:8
 �Ĵ���˵��: 2gģʽRX��·ʱ���ӳٵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_2g_rx_delay_reg;
    struct
    {
        unsigned long  ch1_rx_delay        : 4;  /* bit[0-3]: RX_MCLKʱ����ʱѡ��
                                                                  2G(ns) 3G(ns) 4G(ns)
                                                              0 : 12.8  3.3  1.6 
                                                              1 : 25.6  6.5  3.3 
                                                              2 : 38.5  9.8  4.9 
                                                              3 : 51.3  13.0  6.5 
                                                              4 : 64.1  16.3  8.1 
                                                              5 : 76.9  19.5  9.8 
                                                              6 : 89.7  22.8  11.4 
                                                              7 : 102.6  26.0  13.0 
                                                              8 : 115.4  29.3  14.6 
                                                              9 : 128.2  32.6  16.3 
                                                              10 : 141.0  35.8  17.9 
                                                              11 : 153.8  39.1  19.5 
                                                              12 : 166.7  42.3  21.2 
                                                              13 : 179.5  45.6  22.8 
                                                              14 : 192.3  48.8  24.4 
                                                              15 : 205.1  52.1  26.0  */
        unsigned long  ch1_rx_clk_inv      : 1;  /* bit[4]  : rx_clk���������ƣ�
                                                              1'b0��rx_clk bypass���
                                                              1'b1��rx_clk������� */
        unsigned long  ch1_rx_clk_delay_bp : 1;  /* bit[5]  : rx_clk���delay bypass���أ�
                                                              1'b0��rx_clk ���delay ��bypass
                                                              1'b1��rx_clk ���delay bypass */
        unsigned long  reserved            : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_2G_RX_DELAY_UNION;
#define ABB_CH1_2G_RX_DELAY_ch1_rx_delay_START         (0)
#define ABB_CH1_2G_RX_DELAY_ch1_rx_delay_END           (3)
#define ABB_CH1_2G_RX_DELAY_ch1_rx_clk_inv_START       (4)
#define ABB_CH1_2G_RX_DELAY_ch1_rx_clk_inv_END         (4)
#define ABB_CH1_2G_RX_DELAY_ch1_rx_clk_delay_bp_START  (5)
#define ABB_CH1_2G_RX_DELAY_ch1_rx_clk_delay_bp_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CH1_3G_RX_DELAY_UNION
 �ṹ˵��  : ch1_3g_rx_delay �Ĵ����ṹ���塣��ַƫ����:0x9D����ֵ:0x20�����:8
 �Ĵ���˵��: 3gģʽRX��·ʱ���ӳٵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_3g_rx_delay_reg;
    struct
    {
        unsigned long  ch1_rx_delay        : 4;  /* bit[0-3]: RX_MCLKʱ����ʱѡ��
                                                                  2G(ns) 3G(ns) 4G(ns)
                                                              0 : 12.8  3.3  1.6 
                                                              1 : 25.6  6.5  3.3 
                                                              2 : 38.5  9.8  4.9 
                                                              3 : 51.3  13.0  6.5 
                                                              4 : 64.1  16.3  8.1 
                                                              5 : 76.9  19.5  9.8 
                                                              6 : 89.7  22.8  11.4 
                                                              7 : 102.6  26.0  13.0 
                                                              8 : 115.4  29.3  14.6 
                                                              9 : 128.2  32.6  16.3 
                                                              10 : 141.0  35.8  17.9 
                                                              11 : 153.8  39.1  19.5 
                                                              12 : 166.7  42.3  21.2 
                                                              13 : 179.5  45.6  22.8 
                                                              14 : 192.3  48.8  24.4 
                                                              15 : 205.1  52.1  26.0  */
        unsigned long  ch1_rx_clk_inv      : 1;  /* bit[4]  : rx_clk���������ƣ�
                                                              1'b0��rx_clk bypass���
                                                              1'b1��rx_clk������� */
        unsigned long  ch1_rx_clk_delay_bp : 1;  /* bit[5]  : rx_clk���delay bypass���أ�
                                                              1'b0��rx_clk ���delay ��bypass
                                                              1'b1��rx_clk ���delay bypass */
        unsigned long  reserved            : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_3G_RX_DELAY_UNION;
#define ABB_CH1_3G_RX_DELAY_ch1_rx_delay_START         (0)
#define ABB_CH1_3G_RX_DELAY_ch1_rx_delay_END           (3)
#define ABB_CH1_3G_RX_DELAY_ch1_rx_clk_inv_START       (4)
#define ABB_CH1_3G_RX_DELAY_ch1_rx_clk_inv_END         (4)
#define ABB_CH1_3G_RX_DELAY_ch1_rx_clk_delay_bp_START  (5)
#define ABB_CH1_3G_RX_DELAY_ch1_rx_clk_delay_bp_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CH1_4G_RX_DELAY_UNION
 �ṹ˵��  : ch1_4g_rx_delay �Ĵ����ṹ���塣��ַƫ����:0x9E����ֵ:0x30�����:8
 �Ĵ���˵��: 4gģʽRX��·ʱ���ӳٵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch1_4g_rx_delay_reg;
    struct
    {
        unsigned long  ch1_rx_delay        : 4;  /* bit[0-3]: RX_MCLKʱ����ʱѡ��
                                                                  2G(ns) 3G(ns) 4G(ns)
                                                              0 : 12.8  3.3  1.6 
                                                              1 : 25.6  6.5  3.3 
                                                              2 : 38.5  9.8  4.9 
                                                              3 : 51.3  13.0  6.5 
                                                              4 : 64.1  16.3  8.1 
                                                              5 : 76.9  19.5  9.8 
                                                              6 : 89.7  22.8  11.4 
                                                              7 : 102.6  26.0  13.0 
                                                              8 : 115.4  29.3  14.6 
                                                              9 : 128.2  32.6  16.3 
                                                              10 : 141.0  35.8  17.9 
                                                              11 : 153.8  39.1  19.5 
                                                              12 : 166.7  42.3  21.2 
                                                              13 : 179.5  45.6  22.8 
                                                              14 : 192.3  48.8  24.4 
                                                              15 : 205.1  52.1  26.0  */
        unsigned long  ch1_rx_clk_inv      : 1;  /* bit[4]  : rx_clk���������ƣ�
                                                              1'b0��rx_clk bypass���
                                                              1'b1��rx_clk������� */
        unsigned long  ch1_rx_clk_delay_bp : 1;  /* bit[5]  : rx_clk���delay bypass���أ�
                                                              1'b0��rx_clk ���delay ��bypass
                                                              1'b1��rx_clk ���delay bypass */
        unsigned long  reserved            : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_4G_RX_DELAY_UNION;
#define ABB_CH1_4G_RX_DELAY_ch1_rx_delay_START         (0)
#define ABB_CH1_4G_RX_DELAY_ch1_rx_delay_END           (3)
#define ABB_CH1_4G_RX_DELAY_ch1_rx_clk_inv_START       (4)
#define ABB_CH1_4G_RX_DELAY_ch1_rx_clk_inv_END         (4)
#define ABB_CH1_4G_RX_DELAY_ch1_rx_clk_delay_bp_START  (5)
#define ABB_CH1_4G_RX_DELAY_ch1_rx_clk_delay_bp_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TESTMODE_UNION
 �ṹ˵��  : ch0_testmode �Ĵ����ṹ���塣��ַƫ����:0xA1����ֵ:0x00�����:8
 �Ĵ���˵��: ����ģʽ�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_testmode_reg;
    struct
    {
        unsigned long  reserved_0      : 1;  /* bit[0]  : ���� */
        unsigned long  ch0_rx_chnl_sel : 2;  /* bit[1-2]: RXģ�����ģʽ��ͨ��ѡ��
                                                          00�����RXA Iģ�����������(Ĭ��)
                                                          01�����RXA Qģ�����������
                                                          10�����RXB Iģ�����������
                                                          11�����RXB Qģ����������� */
        unsigned long  ch0_test_mode   : 3;  /* bit[3-5]: bit[4:3]����ģʽ���ƣ�
                                                          00������ģʽ(Ĭ��)
                                                          01�������㷨�߼�����ģʽ
                                                          10��RXģ�����ģʽ(bypass RX�����˲���)
                                                          11�����ֽӿڻ���ģʽ
                                                          bit[5]��reserved */
        unsigned long  ch0_sw_rst      : 1;  /* bit[6]  : ���õ���λ�źţ�
                                                          0�������������λ(Ĭ��)
                                                          1�����������λ */
        unsigned long  reserved_1      : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TESTMODE_UNION;
#define ABB_CH0_TESTMODE_ch0_rx_chnl_sel_START  (1)
#define ABB_CH0_TESTMODE_ch0_rx_chnl_sel_END    (2)
#define ABB_CH0_TESTMODE_ch0_test_mode_START    (3)
#define ABB_CH0_TESTMODE_ch0_test_mode_END      (5)
#define ABB_CH0_TESTMODE_ch0_sw_rst_START       (6)
#define ABB_CH0_TESTMODE_ch0_sw_rst_END         (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_CTRL_UNION
 �ṹ˵��  : ch0_ctrl �Ĵ����ṹ���塣��ַƫ����:0xA2����ֵ:0x00�����:8
 �Ĵ���˵��: ͨ�����ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_ctrl_reg;
    struct
    {
        unsigned long  ch0_et_sel : 1;  /* bit[0]  : ET/APTͨ��ѡ��
                                                     0��ѡ��TXͨ��I·��ET/APT
                                                     1��ѡ��TXͨ��Q·��ET/APT */
        unsigned long  reserved   : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_CTRL_UNION;
#define ABB_CH0_CTRL_ch0_et_sel_START  (0)
#define ABB_CH0_CTRL_ch0_et_sel_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_CH0_CFR_CTRL_UNION
 �ṹ˵��  : ch0_cfr_ctrl �Ĵ����ṹ���塣��ַƫ����:0xA3����ֵ:0x44�����:8
 �Ĵ���˵��: CFR��ֵ��ⴰ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_cfr_ctrl_reg;
    struct
    {
        unsigned long  ch0_cfr_pdet_sel : 2;  /* bit[0-1]: CFR��ֵ��ⷽʽ��
                                                           00���������
                                                           01���������
                                                           10���������
                                                           11��ȫ����ֵ */
        unsigned long  ch0_cfr_fir_sel  : 1;  /* bit[2]  : CFR�˲���ѡ��
                                                           0��bypass�˲���
                                                           1����bypass�˲��� */
        unsigned long  reserved         : 1;  /* bit[3]  : ���� */
        unsigned long  ch0_cfr_fir_fac  : 4;  /* bit[4-7]: CFR�������� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_CFR_CTRL_UNION;
#define ABB_CH0_CFR_CTRL_ch0_cfr_pdet_sel_START  (0)
#define ABB_CH0_CFR_CTRL_ch0_cfr_pdet_sel_END    (1)
#define ABB_CH0_CFR_CTRL_ch0_cfr_fir_sel_START   (2)
#define ABB_CH0_CFR_CTRL_ch0_cfr_fir_sel_END     (2)
#define ABB_CH0_CFR_CTRL_ch0_cfr_fir_fac_START   (4)
#define ABB_CH0_CFR_CTRL_ch0_cfr_fir_fac_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_LINE_CTRL_SEL_UNION
 �ṹ˵��  : ch0_line_ctrl_sel �Ĵ����ṹ���塣��ַƫ����:0xA4����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�ѡ��
*****************************************************************************/
typedef union
{
    unsigned long      ch0_line_ctrl_sel_reg;
    struct
    {
        unsigned long  ch0_line_ctrl_2g_sel  : 1;  /* bit[0]: ѡ��2G�߿�ģʽ��0: tie to 0(Ĭ�ϣ�
                                                              1: from line control */
        unsigned long  ch0_line_ctrl_3g_sel  : 1;  /* bit[1]: ѡ��3G�߿�ģʽ��0: tie to 0(Ĭ�ϣ�
                                                              1: from line control */
        unsigned long  ch0_line_ctrl_4g_sel  : 1;  /* bit[2]: ѡ��4G�߿�ģʽ��0: tie to 0(Ĭ�ϣ�
                                                              1: from line control */
        unsigned long  ch0_line_ctrl_apt_sel : 1;  /* bit[3]: ѡ��APT�߿�ģʽ��0: tie to 0(Ĭ�ϣ�
                                                              1: from line control */
        unsigned long  ch0_line_ctrl_et_sel  : 1;  /* bit[4]: ѡ��ET�߿�ģʽ��0: tie to 0(Ĭ�ϣ�
                                                              1: from line control */
        unsigned long  ch0_line_ctrl_tx_sel  : 1;  /* bit[5]: ѡ��TX_EN�߿أ�0: tie to 0(Ĭ�ϣ�
                                                              1: from line control */
        unsigned long  ch0_line_ctrl_rxb_sel : 1;  /* bit[6]: ѡ��RXB_EN�߿أ�0: tie to 0(Ĭ�ϣ�
                                                              1: from line control */
        unsigned long  ch0_line_ctrl_rxa_en  : 1;  /* bit[7]: ѡ��RXA_EN�߿أ�0: tie to 0(Ĭ�ϣ�
                                                              1: from line control */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_LINE_CTRL_SEL_UNION;
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_2g_sel_START   (0)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_2g_sel_END     (0)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_3g_sel_START   (1)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_3g_sel_END     (1)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_4g_sel_START   (2)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_4g_sel_END     (2)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_apt_sel_START  (3)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_apt_sel_END    (3)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_et_sel_START   (4)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_et_sel_END     (4)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_tx_sel_START   (5)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_tx_sel_END     (5)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_rxb_sel_START  (6)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_rxb_sel_END    (6)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_rxa_en_START   (7)
#define ABB_CH0_LINE_CTRL_SEL_ch0_line_ctrl_rxa_en_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RX_DIG_RPT_UNION
 �ṹ˵��  : ch0_rx_dig_rpt �Ĵ����ṹ���塣��ַƫ����:0xA5����ֵ:0x00�����:8
 �Ĵ���˵��: RX���ֹ���ģʽ�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_rx_dig_rpt_reg;
    struct
    {
        unsigned long  ch0_rx_comp_sel_rpt : 1;  /* bit[0]  : Reserved */
        unsigned long  ch0_rx_comp_fix_rpt : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                              0��ϵ�����̶����ɼĴ�������
                                                              1��ϵ���̶� */
        unsigned long  ch0_rx_hb_bp_rpt    : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                              0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2
                                                              1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  ch0_rx_rate_rpt     : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                                  2G,   3G_SC,    4G,   3G_DC,      
                                                              00�� 2.167M,15.36M, 61.44M,30.72M
                                                              01�� 4.33MHz,------,30.72M,------
                                                              10�� ------, ------,15.36M,------
                                                              11�� ------, ------, 7.68M,------ */
        unsigned long  ch0_rx_mode_dig_rpt : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                              000��2G
                                                              001��3G_SC
                                                              010��4G
                                                              011��3G_DC
                                                              Others��reserved */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_DIG_RPT_UNION;
#define ABB_CH0_RX_DIG_RPT_ch0_rx_comp_sel_rpt_START  (0)
#define ABB_CH0_RX_DIG_RPT_ch0_rx_comp_sel_rpt_END    (0)
#define ABB_CH0_RX_DIG_RPT_ch0_rx_comp_fix_rpt_START  (1)
#define ABB_CH0_RX_DIG_RPT_ch0_rx_comp_fix_rpt_END    (1)
#define ABB_CH0_RX_DIG_RPT_ch0_rx_hb_bp_rpt_START     (2)
#define ABB_CH0_RX_DIG_RPT_ch0_rx_hb_bp_rpt_END       (2)
#define ABB_CH0_RX_DIG_RPT_ch0_rx_rate_rpt_START      (3)
#define ABB_CH0_RX_DIG_RPT_ch0_rx_rate_rpt_END        (4)
#define ABB_CH0_RX_DIG_RPT_ch0_rx_mode_dig_rpt_START  (5)
#define ABB_CH0_RX_DIG_RPT_ch0_rx_mode_dig_rpt_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TX_DIG_RPT_UNION
 �ṹ˵��  : ch0_tx_dig_rpt �Ĵ����ṹ���塣��ַƫ����:0xA6����ֵ:0x02�����:8
 �Ĵ���˵��: TX���ֹ���ģʽ�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_tx_dig_rpt_reg;
    struct
    {
        unsigned long  ch0_tx_comp_bp_tpr  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                              0����bypass
                                                              1��bypass */
        unsigned long  ch0_tx_hb_bp_rpt    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                              0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2
                                                              1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  ch0_tx_rate_rpt     : 3;  /* bit[2-4]: TXͨ��CIC�˲���������ʿ��ƣ�
                                                                   2G,     3G,     4G,     
                                                                  (78M) (153.6M) (307.2M) 
                                                              0��4.33MHz,30.72MHz,61.44MHz
                                                              1��2.16MHz,15.36MHz,30.72MHz
                                                              2��-------,--------,15.36MHz
                                                              3��-------,--------, 7.68MHz
                                                              4��-------,--------, 3.84MHz
                                                              Others��Reserved */
        unsigned long  ch0_tx_mode_dig_rpt : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                              000��2G
                                                              001��3G
                                                              010��4G &amp; ET &amp; APT
                                                              Others��reserved */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_DIG_RPT_UNION;
#define ABB_CH0_TX_DIG_RPT_ch0_tx_comp_bp_tpr_START   (0)
#define ABB_CH0_TX_DIG_RPT_ch0_tx_comp_bp_tpr_END     (0)
#define ABB_CH0_TX_DIG_RPT_ch0_tx_hb_bp_rpt_START     (1)
#define ABB_CH0_TX_DIG_RPT_ch0_tx_hb_bp_rpt_END       (1)
#define ABB_CH0_TX_DIG_RPT_ch0_tx_rate_rpt_START      (2)
#define ABB_CH0_TX_DIG_RPT_ch0_tx_rate_rpt_END        (4)
#define ABB_CH0_TX_DIG_RPT_ch0_tx_mode_dig_rpt_START  (5)
#define ABB_CH0_TX_DIG_RPT_ch0_tx_mode_dig_rpt_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXA_I_COEF1_UNION
 �ṹ˵��  : ch0_rxa_i_coef1 �Ĵ����ṹ���塣��ַƫ����:0xAB����ֵ:0xF4�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_rxa_i_coef1_reg;
    struct
    {
        unsigned long  ch0_rxa_i_c1     : 7;  /* bit[0-6]: RXAͨ��I·�����˲���ϵ��C1,�з����� */
        unsigned long  ch0_rxa_i_c3_msb : 1;  /* bit[7]  : RXAͨ��I·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_I_COEF1_UNION;
#define ABB_CH0_RXA_I_COEF1_ch0_rxa_i_c1_START      (0)
#define ABB_CH0_RXA_I_COEF1_ch0_rxa_i_c1_END        (6)
#define ABB_CH0_RXA_I_COEF1_ch0_rxa_i_c3_msb_START  (7)
#define ABB_CH0_RXA_I_COEF1_ch0_rxa_i_c3_msb_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXA_I_COEF3_UNION
 �ṹ˵��  : ch0_rxa_i_coef3 �Ĵ����ṹ���塣��ַƫ����:0xAD����ֵ:0x74�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_rxa_i_coef3_reg;
    struct
    {
        unsigned long  ch0_rxa_i_c5 : 7;  /* bit[0-6]: RXAͨ��I·�����˲���ϵ��C5,�з����� */
        unsigned long  reserved     : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_I_COEF3_UNION;
#define ABB_CH0_RXA_I_COEF3_ch0_rxa_i_c5_START  (0)
#define ABB_CH0_RXA_I_COEF3_ch0_rxa_i_c5_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXA_Q_COEF1_UNION
 �ṹ˵��  : ch0_rxa_q_coef1 �Ĵ����ṹ���塣��ַƫ����:0xB0����ֵ:0xF4�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_rxa_q_coef1_reg;
    struct
    {
        unsigned long  ch0_rxa_q_c1     : 7;  /* bit[0-6]: RXAͨ��Q·�����˲���ϵ��C1,�з����� */
        unsigned long  ch0_rxa_q_c3_msb : 1;  /* bit[7]  : RXAͨ��Q·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_Q_COEF1_UNION;
#define ABB_CH0_RXA_Q_COEF1_ch0_rxa_q_c1_START      (0)
#define ABB_CH0_RXA_Q_COEF1_ch0_rxa_q_c1_END        (6)
#define ABB_CH0_RXA_Q_COEF1_ch0_rxa_q_c3_msb_START  (7)
#define ABB_CH0_RXA_Q_COEF1_ch0_rxa_q_c3_msb_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXA_Q_COEF3_UNION
 �ṹ˵��  : ch0_rxa_q_coef3 �Ĵ����ṹ���塣��ַƫ����:0xB2����ֵ:0x74�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_rxa_q_coef3_reg;
    struct
    {
        unsigned long  ch0_rxa_q_c5 : 7;  /* bit[0-6]: RXAͨ��Q·�����˲���ϵ��C5,�з����� */
        unsigned long  reserved     : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_Q_COEF3_UNION;
#define ABB_CH0_RXA_Q_COEF3_ch0_rxa_q_c5_START  (0)
#define ABB_CH0_RXA_Q_COEF3_ch0_rxa_q_c5_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXB_I_COEF1_UNION
 �ṹ˵��  : ch0_rxb_i_coef1 �Ĵ����ṹ���塣��ַƫ����:0xB5����ֵ:0xF4�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_rxb_i_coef1_reg;
    struct
    {
        unsigned long  ch0_rxb_i_c1     : 7;  /* bit[0-6]: RXBͨ��I·�����˲���ϵ��C1,�з����� */
        unsigned long  ch0_rxb_i_c3_msb : 1;  /* bit[7]  : RXBͨ��I·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_I_COEF1_UNION;
#define ABB_CH0_RXB_I_COEF1_ch0_rxb_i_c1_START      (0)
#define ABB_CH0_RXB_I_COEF1_ch0_rxb_i_c1_END        (6)
#define ABB_CH0_RXB_I_COEF1_ch0_rxb_i_c3_msb_START  (7)
#define ABB_CH0_RXB_I_COEF1_ch0_rxb_i_c3_msb_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXB_I_COEF3_UNION
 �ṹ˵��  : ch0_rxb_i_coef3 �Ĵ����ṹ���塣��ַƫ����:0xB7����ֵ:0x74�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_rxb_i_coef3_reg;
    struct
    {
        unsigned long  ch0_rxb_i_c5 : 7;  /* bit[0-6]: RXBͨ��I·�����˲���ϵ��C5,�з����� */
        unsigned long  reserved     : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_I_COEF3_UNION;
#define ABB_CH0_RXB_I_COEF3_ch0_rxb_i_c5_START  (0)
#define ABB_CH0_RXB_I_COEF3_ch0_rxb_i_c5_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXB_Q_COEF1_UNION
 �ṹ˵��  : ch0_rxb_q_coef1 �Ĵ����ṹ���塣��ַƫ����:0xBA����ֵ:0xF4�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_rxb_q_coef1_reg;
    struct
    {
        unsigned long  ch0_rxb_q_c1     : 7;  /* bit[0-6]: RXBͨ��Q·�����˲���ϵ��C1,�з����� */
        unsigned long  ch0_rxb_q_c3_msb : 1;  /* bit[7]  : RXBͨ��Q·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_Q_COEF1_UNION;
#define ABB_CH0_RXB_Q_COEF1_ch0_rxb_q_c1_START      (0)
#define ABB_CH0_RXB_Q_COEF1_ch0_rxb_q_c1_END        (6)
#define ABB_CH0_RXB_Q_COEF1_ch0_rxb_q_c3_msb_START  (7)
#define ABB_CH0_RXB_Q_COEF1_ch0_rxb_q_c3_msb_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXB_Q_COEF3_UNION
 �ṹ˵��  : ch0_rxb_q_coef3 �Ĵ����ṹ���塣��ַƫ����:0xBC����ֵ:0x74�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_rxb_q_coef3_reg;
    struct
    {
        unsigned long  ch0_rxb_q_c5 : 7;  /* bit[0-6]: RXBͨ��Q·�����˲���ϵ��C5,�з����� */
        unsigned long  reserved     : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_Q_COEF3_UNION;
#define ABB_CH0_RXB_Q_COEF3_ch0_rxb_q_c5_START  (0)
#define ABB_CH0_RXB_Q_COEF3_ch0_rxb_q_c5_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_RXA_DCR_CFG_UNION
 �ṹ˵��  : ch0_reg_rxa_dcr_cfg �Ĵ����ṹ���塣��ַƫ����:0xBE����ֵ:0x46�����:8
 �Ĵ���˵��: RXAͨ��BLOCKING DCR���üĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_rxa_dcr_cfg_reg;
    struct
    {
        unsigned long  ch0_cfg_rxa_dcr_dly    : 5;  /* bit[0-4]: RXA����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣 */
        unsigned long  ch0_cfg_rxa_dcr_l_para : 3;  /* bit[5-7]: RXA����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ�� */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RXA_DCR_CFG_UNION;
#define ABB_CH0_REG_RXA_DCR_CFG_ch0_cfg_rxa_dcr_dly_START     (0)
#define ABB_CH0_REG_RXA_DCR_CFG_ch0_cfg_rxa_dcr_dly_END       (4)
#define ABB_CH0_REG_RXA_DCR_CFG_ch0_cfg_rxa_dcr_l_para_START  (5)
#define ABB_CH0_REG_RXA_DCR_CFG_ch0_cfg_rxa_dcr_l_para_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_RXB_DCR_CFG_UNION
 �ṹ˵��  : ch0_reg_rxb_dcr_cfg �Ĵ����ṹ���塣��ַƫ����:0xBF����ֵ:0x46�����:8
 �Ĵ���˵��: RXBͨ��BLOCKING DCR���üĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_rxb_dcr_cfg_reg;
    struct
    {
        unsigned long  ch0_cfg_rxb_dcr_dly    : 5;  /* bit[0-4]: RXB����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣 */
        unsigned long  ch0_cfg_rxb_dcr_l_para : 3;  /* bit[5-7]: RXB����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ�� */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RXB_DCR_CFG_UNION;
#define ABB_CH0_REG_RXB_DCR_CFG_ch0_cfg_rxb_dcr_dly_START     (0)
#define ABB_CH0_REG_RXB_DCR_CFG_ch0_cfg_rxb_dcr_dly_END       (4)
#define ABB_CH0_REG_RXB_DCR_CFG_ch0_cfg_rxb_dcr_l_para_START  (5)
#define ABB_CH0_REG_RXB_DCR_CFG_ch0_cfg_rxb_dcr_l_para_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_RX_DCR_CTRL_UNION
 �ṹ˵��  : ch0_reg_rx_dcr_ctrl �Ĵ����ṹ���塣��ַƫ����:0xC0����ֵ:0x00�����:8
 �Ĵ���˵��: BLOCKING DCR���ܿ��ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_rx_dcr_ctrl_reg;
    struct
    {
        unsigned long  ch0_cfg_rxa_dcr_bypass : 1;  /* bit[0]  : RXA����BLOCKING DCR����bypass���ơ�
                                                                 0��DCR���ܲ�bypasss��
                                                                 1��DCR����bypass�� */
        unsigned long  ch0_cfg_rxb_dcr_bypass : 1;  /* bit[1]  : RXB����BLOCKING DCR����bypass���ơ�
                                                                 0��DCR���ܲ�bypasss��
                                                                 1��DCR����bypass�� */
        unsigned long  reserved               : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RX_DCR_CTRL_UNION;
#define ABB_CH0_REG_RX_DCR_CTRL_ch0_cfg_rxa_dcr_bypass_START  (0)
#define ABB_CH0_REG_RX_DCR_CTRL_ch0_cfg_rxa_dcr_bypass_END    (0)
#define ABB_CH0_REG_RX_DCR_CTRL_ch0_cfg_rxb_dcr_bypass_START  (1)
#define ABB_CH0_REG_RX_DCR_CTRL_ch0_cfg_rxb_dcr_bypass_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXA_BLOCKING_UNION
 �ṹ˵��  : ch0_rxa_blocking �Ĵ����ṹ���塣��ַƫ����:0xC1����ֵ:0x00�����:8
 �Ĵ���˵��: RXAͨ��BLOCKING�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_rxa_blocking_reg;
    struct
    {
        unsigned long  ch0_rxa_blk_coeff : 5;  /* bit[0-4]: RXA����BLOCKING�ϱ�ֵ��ϵ����2��M�η� */
        unsigned long  ch0_rxa_blk_power : 3;  /* bit[5-7]: RXA����BLOCKING�ϱ�ֵ,������СN */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_BLOCKING_UNION;
#define ABB_CH0_RXA_BLOCKING_ch0_rxa_blk_coeff_START  (0)
#define ABB_CH0_RXA_BLOCKING_ch0_rxa_blk_coeff_END    (4)
#define ABB_CH0_RXA_BLOCKING_ch0_rxa_blk_power_START  (5)
#define ABB_CH0_RXA_BLOCKING_ch0_rxa_blk_power_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXB_BLOCKING_UNION
 �ṹ˵��  : ch0_rxb_blocking �Ĵ����ṹ���塣��ַƫ����:0xC2����ֵ:0x00�����:8
 �Ĵ���˵��: RXBͨ��BLOCKING�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_rxb_blocking_reg;
    struct
    {
        unsigned long  ch0_rxb_blk_coeff : 5;  /* bit[0-4]: RXB����BLOCKING�ϱ�ֵ��ϵ����2��M�η� */
        unsigned long  ch0_rxb_blk_power : 3;  /* bit[5-7]: RXB����BLOCKING�ϱ�ֵ,������СN */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_BLOCKING_UNION;
#define ABB_CH0_RXB_BLOCKING_ch0_rxb_blk_coeff_START  (0)
#define ABB_CH0_RXB_BLOCKING_ch0_rxb_blk_coeff_END    (4)
#define ABB_CH0_RXB_BLOCKING_ch0_rxb_blk_power_START  (5)
#define ABB_CH0_RXB_BLOCKING_ch0_rxb_blk_power_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_RXA_DC_I_2_UNION
 �ṹ˵��  : ch0_reg_rxa_dc_i_2 �Ĵ����ṹ���塣��ַƫ����:0xC4����ֵ:0x00�����:8
 �Ĵ���˵��: RXAͨ��I·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_rxa_dc_i_2_reg;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: ���� */
        unsigned long  ch0_rxa_dc_i_2 : 4;  /* bit[4-7]: RXA����I·�ź�BLOCKING DC�ϱ�ֵ��4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RXA_DC_I_2_UNION;
#define ABB_CH0_REG_RXA_DC_I_2_ch0_rxa_dc_i_2_START  (4)
#define ABB_CH0_REG_RXA_DC_I_2_ch0_rxa_dc_i_2_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_RXA_DC_Q_2_UNION
 �ṹ˵��  : ch0_reg_rxa_dc_q_2 �Ĵ����ṹ���塣��ַƫ����:0xC6����ֵ:0x00�����:8
 �Ĵ���˵��: RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_rxa_dc_q_2_reg;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: ���� */
        unsigned long  ch0_rxa_dc_q_2 : 4;  /* bit[4-7]: RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RXA_DC_Q_2_UNION;
#define ABB_CH0_REG_RXA_DC_Q_2_ch0_rxa_dc_q_2_START  (4)
#define ABB_CH0_REG_RXA_DC_Q_2_ch0_rxa_dc_q_2_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_RXB_DC_I_2_UNION
 �ṹ˵��  : ch0_reg_rxb_dc_i_2 �Ĵ����ṹ���塣��ַƫ����:0xC8����ֵ:0x00�����:8
 �Ĵ���˵��: RXBͨ��I·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_rxb_dc_i_2_reg;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: ���� */
        unsigned long  ch0_rxb_dc_i_2 : 4;  /* bit[4-7]: RXB����I·�ź�BLOCKING DC�ϱ�ֵ��4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RXB_DC_I_2_UNION;
#define ABB_CH0_REG_RXB_DC_I_2_ch0_rxb_dc_i_2_START  (4)
#define ABB_CH0_REG_RXB_DC_I_2_ch0_rxb_dc_i_2_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_RXB_DC_Q_2_UNION
 �ṹ˵��  : ch0_reg_rxb_dc_q_2 �Ĵ����ṹ���塣��ַƫ����:0xCA����ֵ:0x00�����:8
 �Ĵ���˵��: RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_rxb_dc_q_2_reg;
    struct
    {
        unsigned long  reserved       : 4;  /* bit[0-3]: ���� */
        unsigned long  ch0_rxb_dc_q_2 : 4;  /* bit[4-7]: RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_RXB_DC_Q_2_UNION;
#define ABB_CH0_REG_RXB_DC_Q_2_ch0_rxb_dc_q_2_START  (4)
#define ABB_CH0_REG_RXB_DC_Q_2_ch0_rxb_dc_q_2_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_DIG0_UNION
 �ṹ˵��  : ch0_reg_debug_dig0 �Ĵ����ṹ���塣��ַƫ����:0xCB����ֵ:0x00�����:8
 �Ĵ���˵��: ���ֵ��ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_dig0_reg;
    struct
    {
        unsigned long  ch0_sdm_rst_ctrl : 1;  /* bit[0]  : TXͨ��SDMģ���쳣ʱ��λ����
                                                           0��ֻ��λSDMģ��
                                                           1����λ����TXͨ�� */
        unsigned long  ch0_dem_mode     : 1;  /* bit[1]  : TXͨ��DEMУ׼����ģʽ
                                                           0����������
                                                           1��У׼̬��DEM���Ϊdem_code_man */
        unsigned long  ch0_tx_dem_sat   : 2;  /* bit[2-3]: Reserved */
        unsigned long  ch0_dither_en    : 1;  /* bit[4]  : Reserved */
        unsigned long  reserved         : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_DIG0_UNION;
#define ABB_CH0_REG_DEBUG_DIG0_ch0_sdm_rst_ctrl_START  (0)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_sdm_rst_ctrl_END    (0)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_dem_mode_START      (1)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_dem_mode_END        (1)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_tx_dem_sat_START    (2)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_tx_dem_sat_END      (3)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_dither_en_START     (4)
#define ABB_CH0_REG_DEBUG_DIG0_ch0_dither_en_END       (4)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_DIG4_UNION
 �ṹ˵��  : ch0_reg_debug_dig4 �Ĵ����ṹ���塣��ַƫ����:0xCF����ֵ:0x00�����:8
 �Ĵ���˵��: ���ֵ��ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_dig4_reg;
    struct
    {
        unsigned long  reserved          : 4;  /* bit[0-3]: ���� */
        unsigned long  ch0_cic4_cic6_sel : 1;  /* bit[4]  : RXͨ��CIC4/CIC6�˲���ѡ��
                                                            0: ѡ��CIC4�˲���
                                                            1: ѡ��CIC6�˲��� */
        unsigned long  ch0_sw_gate_bp    : 1;  /* bit[5]  : �л��ſ�ʹ��bypass�źš�1��ʾ�ſ�ʹ�ܹ�����·�� */
        unsigned long  ch0_cic_rst_bp    : 1;  /* bit[6]  : �л���λbypass�źš�1��ʾ�л���λ������·�� */
        unsigned long  ch0_div_en_bp     : 1;  /* bit[7]  : div_en���Ʒ�Ƶ��bypass�źţ�0��div_en���Ʒ�Ƶ����1��div_en�����Ʒ�Ƶ������Ƶ��ʹ��ʼ��Ϊ1��. */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_DIG4_UNION;
#define ABB_CH0_REG_DEBUG_DIG4_ch0_cic4_cic6_sel_START  (4)
#define ABB_CH0_REG_DEBUG_DIG4_ch0_cic4_cic6_sel_END    (4)
#define ABB_CH0_REG_DEBUG_DIG4_ch0_sw_gate_bp_START     (5)
#define ABB_CH0_REG_DEBUG_DIG4_ch0_sw_gate_bp_END       (5)
#define ABB_CH0_REG_DEBUG_DIG4_ch0_cic_rst_bp_START     (6)
#define ABB_CH0_REG_DEBUG_DIG4_ch0_cic_rst_bp_END       (6)
#define ABB_CH0_REG_DEBUG_DIG4_ch0_div_en_bp_START      (7)
#define ABB_CH0_REG_DEBUG_DIG4_ch0_div_en_bp_END        (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR02_UNION
 �ṹ˵��  : ch0_reg_analog_wr02 �Ĵ����ṹ���塣��ַƫ����:0xD0����ֵ:0x0F�����:8
 �Ĵ���˵��: Power Down���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_analog_wr02_reg;
    struct
    {
        unsigned long  CH1_RXC_Q_PD   : 1;  /* bit[0]  : Reserved */
        unsigned long  CH1_RXC_I_PD   : 1;  /* bit[1]  : Reserved */
        unsigned long  CH0_PLL624_PD  : 1;  /* bit[2]  : GPLL Power Down����
                                                         0:Power On
                                                         1:Power Down(Ĭ��) */
        unsigned long  CH0_PLL6144_PD : 1;  /* bit[3]  : WPLL Power Down����
                                                         0:Power On(Ĭ��)
                                                         1:Power Down */
        unsigned long  reserved       : 4;  /* bit[4-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR02_UNION;
#define ABB_CH0_REG_ANALOG_WR02_CH1_RXC_Q_PD_START    (0)
#define ABB_CH0_REG_ANALOG_WR02_CH1_RXC_Q_PD_END      (0)
#define ABB_CH0_REG_ANALOG_WR02_CH1_RXC_I_PD_START    (1)
#define ABB_CH0_REG_ANALOG_WR02_CH1_RXC_I_PD_END      (1)
#define ABB_CH0_REG_ANALOG_WR02_CH0_PLL624_PD_START   (2)
#define ABB_CH0_REG_ANALOG_WR02_CH0_PLL624_PD_END     (2)
#define ABB_CH0_REG_ANALOG_WR02_CH0_PLL6144_PD_START  (3)
#define ABB_CH0_REG_ANALOG_WR02_CH0_PLL6144_PD_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR03_UNION
 �ṹ˵��  : ch0_reg_analog_wr03 �Ĵ����ṹ���塣��ַƫ����:0xD1����ֵ:0x30�����:8
 �Ĵ���˵��: ��ģ�ӿ�ʱ�ӿ��ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_analog_wr03_reg;
    struct
    {
        unsigned long  reserved_0        : 3;  /* bit[0-2]: Reserved */
        unsigned long  CH0_TX_CLKD_CTRL  : 1;  /* bit[3]  : TX ����ʱ����ѡ��
                                                            0: ����
                                                            1: ����(Ĭ��) */
        unsigned long  CH0_CLK_61D44M_PD : 1;  /* bit[4]  : CLK_61D44M Power Down����
                                                            0:Power On
                                                            1:Power Down(Ĭ��) */
        unsigned long  CH0_CLK_52M_PD    : 1;  /* bit[5]  : CLK_52M Power Down����
                                                            0:Power On
                                                            1:Power Down(Ĭ��) */
        unsigned long  CH0_245M_EN       : 1;  /* bit[6]  : 245M������ƣ�
                                                            0: �����
                                                            1: ��� */
        unsigned long  reserved_1        : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR03_UNION;
#define ABB_CH0_REG_ANALOG_WR03_CH0_TX_CLKD_CTRL_START   (3)
#define ABB_CH0_REG_ANALOG_WR03_CH0_TX_CLKD_CTRL_END     (3)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK_61D44M_PD_START  (4)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK_61D44M_PD_END    (4)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK_52M_PD_START     (5)
#define ABB_CH0_REG_ANALOG_WR03_CH0_CLK_52M_PD_END       (5)
#define ABB_CH0_REG_ANALOG_WR03_CH0_245M_EN_START        (6)
#define ABB_CH0_REG_ANALOG_WR03_CH0_245M_EN_END          (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR04_UNION
 �ṹ˵��  : ch0_reg_analog_wr04 �Ĵ����ṹ���塣��ַƫ����:0xD2����ֵ:0x0C�����:8
 �Ĵ���˵��: Other���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_analog_wr04_reg;
    struct
    {
        unsigned long  CH0_EN_CAL       : 1;  /* bit[0]  : Calibration enable��Ĭ��Ϊ0��
                                                           ����������Calibration���� */
        unsigned long  reserved_0       : 1;  /* bit[1]  : Reserved */
        unsigned long  CH0_TX_AUTO_TUNE : 1;  /* bit[2]  : TX ADC�Զ�tuning����
                                                           0���ֶ�tuning��tuningѡ��TX_TUNE1,TX_TUNE2,TX_TUNE3��ֵ(Ĭ��)
                                                           1���Զ�tuning��TXͨ����calibrationֵΪCAL_VALUE */
        unsigned long  CH0_RX_AUTO_TUNE : 1;  /* bit[3]  : RX ADC�Զ�tuning����
                                                           0���ֶ�tuning��tuningѡ��RX_TUNE1,RX_TUNE2,RX_TUNE3��ֵ(Ĭ��)
                                                           1���Զ�tuning��RXͨ����calibrationֵΪCAL_VALUE */
        unsigned long  reserved_1       : 4;  /* bit[4-7]: Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR04_UNION;
#define ABB_CH0_REG_ANALOG_WR04_CH0_EN_CAL_START        (0)
#define ABB_CH0_REG_ANALOG_WR04_CH0_EN_CAL_END          (0)
#define ABB_CH0_REG_ANALOG_WR04_CH0_TX_AUTO_TUNE_START  (2)
#define ABB_CH0_REG_ANALOG_WR04_CH0_TX_AUTO_TUNE_END    (2)
#define ABB_CH0_REG_ANALOG_WR04_CH0_RX_AUTO_TUNE_START  (3)
#define ABB_CH0_REG_ANALOG_WR04_CH0_RX_AUTO_TUNE_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR05_UNION
 �ṹ˵��  : ch0_reg_analog_wr05 �Ĵ����ṹ���塣��ַƫ����:0xD3����ֵ:0x40�����:8
 �Ĵ���˵��: ADC��һ������������tuning�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_analog_wr05_reg;
    struct
    {
        unsigned long  CH0_RX_TUNE1 : 7;  /* bit[0-6]: ADC��һ������������tuning */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR05_UNION;
#define ABB_CH0_REG_ANALOG_WR05_CH0_RX_TUNE1_START  (0)
#define ABB_CH0_REG_ANALOG_WR05_CH0_RX_TUNE1_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR06_UNION
 �ṹ˵��  : ch0_reg_analog_wr06 �Ĵ����ṹ���塣��ַƫ����:0xD4����ֵ:0x40�����:8
 �Ĵ���˵��: ADC�ڶ�������������tuning�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_analog_wr06_reg;
    struct
    {
        unsigned long  CH0_RX_TUNE2 : 7;  /* bit[0-6]: ADC�ڶ�������������tuning */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR06_UNION;
#define ABB_CH0_REG_ANALOG_WR06_CH0_RX_TUNE2_START  (0)
#define ABB_CH0_REG_ANALOG_WR06_CH0_RX_TUNE2_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR07_UNION
 �ṹ˵��  : ch0_reg_analog_wr07 �Ĵ����ṹ���塣��ַƫ����:0xD5����ֵ:0x40�����:8
 �Ĵ���˵��: ADC����������������tuning�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_analog_wr07_reg;
    struct
    {
        unsigned long  CH0_RX_TUNE3 : 7;  /* bit[0-6]: ADC����������������tuning */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR07_UNION;
#define ABB_CH0_REG_ANALOG_WR07_CH0_RX_TUNE3_START  (0)
#define ABB_CH0_REG_ANALOG_WR07_CH0_RX_TUNE3_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR08_UNION
 �ṹ˵��  : ch0_reg_analog_wr08 �Ĵ����ṹ���塣��ַƫ����:0xD6����ֵ:0x40�����:8
 �Ĵ���˵��: DAC Tuning���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_analog_wr08_reg;
    struct
    {
        unsigned long  CH0_TX_TUNE1 : 7;  /* bit[0-6]: TX_TUNE1�����ź� */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR08_UNION;
#define ABB_CH0_REG_ANALOG_WR08_CH0_TX_TUNE1_START  (0)
#define ABB_CH0_REG_ANALOG_WR08_CH0_TX_TUNE1_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR09_UNION
 �ṹ˵��  : ch0_reg_analog_wr09 �Ĵ����ṹ���塣��ַƫ����:0xD7����ֵ:0x40�����:8
 �Ĵ���˵��: DAC Tuning���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_analog_wr09_reg;
    struct
    {
        unsigned long  CH0_TX_TUNE2 : 7;  /* bit[0-6]: TX_TUNE2�����ź� */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR09_UNION;
#define ABB_CH0_REG_ANALOG_WR09_CH0_TX_TUNE2_START  (0)
#define ABB_CH0_REG_ANALOG_WR09_CH0_TX_TUNE2_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR10_UNION
 �ṹ˵��  : ch0_reg_analog_wr10 �Ĵ����ṹ���塣��ַƫ����:0xD8����ֵ:0x40�����:8
 �Ĵ���˵��: DAC Tuning���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_analog_wr10_reg;
    struct
    {
        unsigned long  CH0_TX_TUNE3 : 7;  /* bit[0-6]: TX_TUNE3�����ź� */
        unsigned long  reserved     : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR10_UNION;
#define ABB_CH0_REG_ANALOG_WR10_CH0_TX_TUNE3_START  (0)
#define ABB_CH0_REG_ANALOG_WR10_CH0_TX_TUNE3_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR38_UNION
 �ṹ˵��  : ch0_reg_analog_wr38 �Ĵ����ṹ���塣��ַƫ����:0xD9����ֵ:0x60�����:8
 �Ĵ���˵��: ��ģ��ƽ���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_analog_wr38_reg;
    struct
    {
        unsigned long  reserved              : 3;  /* bit[0-2]: Reserved */
        unsigned long  CH0_OFFSET_CAL_DAC_EN : 1;  /* bit[3]  : Reserved */
        unsigned long  CH0_SARADC_REF_RANGE  : 1;  /* bit[4]  : Reserved */
        unsigned long  CH0_TX_CM_CON_MODE    : 2;  /* bit[5-6]: Reserved */
        unsigned long  CH0_RX_ADC_CM_CON_EN  : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR38_UNION;
#define ABB_CH0_REG_ANALOG_WR38_CH0_OFFSET_CAL_DAC_EN_START  (3)
#define ABB_CH0_REG_ANALOG_WR38_CH0_OFFSET_CAL_DAC_EN_END    (3)
#define ABB_CH0_REG_ANALOG_WR38_CH0_SARADC_REF_RANGE_START   (4)
#define ABB_CH0_REG_ANALOG_WR38_CH0_SARADC_REF_RANGE_END     (4)
#define ABB_CH0_REG_ANALOG_WR38_CH0_TX_CM_CON_MODE_START     (5)
#define ABB_CH0_REG_ANALOG_WR38_CH0_TX_CM_CON_MODE_END       (6)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_ADC_CM_CON_EN_START   (7)
#define ABB_CH0_REG_ANALOG_WR38_CH0_RX_ADC_CM_CON_EN_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_WR39_UNION
 �ṹ˵��  : ch0_reg_analog_wr39 �Ĵ����ṹ���塣��ַƫ����:0xDA����ֵ:0x03�����:8
 �Ĵ���˵��: DUM���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_analog_wr39_reg;
    struct
    {
        unsigned long  CH0_DUM_EN_Q : 1;  /* bit[0]  : TX Q channel  dummy logic control signal
                                                       1: enable(Ĭ��)
                                                       0: disable */
        unsigned long  CH0_DUM_EN_I : 1;  /* bit[1]  : TX I channel  dummy logic control signal
                                                       1: enable(Ĭ��)
                                                       0: disable */
        unsigned long  reserved     : 3;  /* bit[2-4]: Reserved */
        unsigned long  CH0_DEM_MOD  : 3;  /* bit[5-7]: RX DEM Mode Selection,bit 2
                                                       000: DWA
                                                       001: CLA1
                                                       010: CLA2
                                                       011: CLA3
                                                       100: CLA4
                                                       101: CLA5
                                                       110: CLA6
                                                       111: CLA7 */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_WR39_UNION;
#define ABB_CH0_REG_ANALOG_WR39_CH0_DUM_EN_Q_START  (0)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DUM_EN_Q_END    (0)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DUM_EN_I_START  (1)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DUM_EN_I_END    (1)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DEM_MOD_START   (5)
#define ABB_CH0_REG_ANALOG_WR39_CH0_DEM_MOD_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_RO0_UNION
 �ṹ˵��  : ch0_reg_analog_ro0 �Ĵ����ṹ���塣��ַƫ����:0xDB����ֵ:0x00�����:8
 �Ĵ���˵��: ��־λֻ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_analog_ro0_reg;
    struct
    {
        unsigned long  reserved     : 5;  /* bit[0-4]: Reserved */
        unsigned long  CH0_CAL_DONE : 1;  /* bit[5]  : RC Calibration Done�ź� */
        unsigned long  CH0_LOCK2    : 1;  /* bit[6]  : GPLL��LOCK�ź� */
        unsigned long  CH0_LOCK1    : 1;  /* bit[7]  : WPLL��LOCK�ź� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_RO0_UNION;
#define ABB_CH0_REG_ANALOG_RO0_CH0_CAL_DONE_START  (5)
#define ABB_CH0_REG_ANALOG_RO0_CH0_CAL_DONE_END    (5)
#define ABB_CH0_REG_ANALOG_RO0_CH0_LOCK2_START     (6)
#define ABB_CH0_REG_ANALOG_RO0_CH0_LOCK2_END       (6)
#define ABB_CH0_REG_ANALOG_RO0_CH0_LOCK1_START     (7)
#define ABB_CH0_REG_ANALOG_RO0_CH0_LOCK1_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_ANALOG_RO1_UNION
 �ṹ˵��  : ch0_reg_analog_ro1 �Ĵ����ṹ���塣��ַƫ����:0xDC����ֵ:0x00�����:8
 �Ĵ���˵��: RCУ׼ֻ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_analog_ro1_reg;
    struct
    {
        unsigned long  CH0_RX_CAL_VALUE : 7;  /* bit[0-6]: RC CalibrationУ׼ֵ */
        unsigned long  reserved         : 1;  /* bit[7]  : Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_ANALOG_RO1_UNION;
#define ABB_CH0_REG_ANALOG_RO1_CH0_RX_CAL_VALUE_START  (0)
#define ABB_CH0_REG_ANALOG_RO1_CH0_RX_CAL_VALUE_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA0_UNION
 �ṹ˵��  : ch0_reg_debug_ana0 �Ĵ����ṹ���塣��ַƫ����:0xE0����ֵ:0x32�����:8
 �Ĵ���˵��: ģ����ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana0_reg;
    struct
    {
        unsigned long  CH0_CLK_REF_SEL  : 1;  /* bit[0]  : PLL�Ĳο�ʱ��ѡ��
                                                           1: CLKIN_SYSTEM��ΪPLL�Ĳο�ʱ��
                                                           0: TCXO Buffer�����ΪPLL�ο�ʱ�� */
        unsigned long  CH0_PLL_OCLK_SEL : 3;  /* bit[1-3]: ����ʱ��ѡ��
                                                           001��ѡ��������PLL��ʱ����Ϊ����ʱ��
                                                           010��ѡ��������CLKIN_SYSTEM�����ʱ����Ϊ����ʱ��
                                                           100��ѡ��������TCXO_IN��ʱ����Ϊ����ʱ�� */
        unsigned long  CH0_PLL_PFD_CTRL : 2;  /* bit[4-5]: PLL��Ƶ����������
                                                           x0����Ƶ������һֱ���Up�ź�
                                                           01: ��Ƶ������һֱ���Down�ź�
                                                           11����Ƶ�������������� */
        unsigned long  reserved         : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA0_UNION;
#define ABB_CH0_REG_DEBUG_ANA0_CH0_CLK_REF_SEL_START   (0)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_CLK_REF_SEL_END     (0)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_PLL_OCLK_SEL_START  (1)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_PLL_OCLK_SEL_END    (3)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_PLL_PFD_CTRL_START  (4)
#define ABB_CH0_REG_DEBUG_ANA0_CH0_PLL_PFD_CTRL_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA1_UNION
 �ṹ˵��  : ch0_reg_debug_ana1 �Ĵ����ṹ���塣��ַƫ����:0xE1����ֵ:0x00�����:8
 �Ĵ���˵��: PLL LOCK���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana1_reg;
    struct
    {
        unsigned long  reserved_0     : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH0_GPLL_LK_EN : 1;  /* bit[4]  : GPLL�������ʹ��
                                                         0�����ֹͣ
                                                         1����⿪ʼ */
        unsigned long  CH0_WPLL_LK_EN : 1;  /* bit[5]  : WPLL�������ʹ��
                                                         0�����ֹͣ
                                                         1����⿪ʼ */
        unsigned long  reserved_1     : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA1_UNION;
#define ABB_CH0_REG_DEBUG_ANA1_CH0_GPLL_LK_EN_START  (4)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_GPLL_LK_EN_END    (4)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WPLL_LK_EN_START  (5)
#define ABB_CH0_REG_DEBUG_ANA1_CH0_WPLL_LK_EN_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA2_UNION
 �ṹ˵��  : ch0_reg_debug_ana2 �Ĵ����ṹ���塣��ַƫ����:0xE2����ֵ:0x80�����:8
 �Ĵ���˵��: PLL���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana2_reg;
    struct
    {
        unsigned long  CH0_PLL_CP_PD : 2;  /* bit[0-1]: PLL CP PowerDown���ƣ�������
                                                        00����������
                                                        01: PowerDown WPLL CP 
                                                        10: PowerDown GPLL CP 
                                                        11: PowerDown WPLL CP��GPLL CP */
        unsigned long  reserved      : 5;  /* bit[2-6]: Reserved */
        unsigned long  CH0_CLKN_EN   : 1;  /* bit[7]  : ����ʱ�ӿ���
                                                        1: ����ʱ�Ӵ�
                                                        0: ����ʱ�ӹر� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA2_UNION;
#define ABB_CH0_REG_DEBUG_ANA2_CH0_PLL_CP_PD_START  (0)
#define ABB_CH0_REG_DEBUG_ANA2_CH0_PLL_CP_PD_END    (1)
#define ABB_CH0_REG_DEBUG_ANA2_CH0_CLKN_EN_START    (7)
#define ABB_CH0_REG_DEBUG_ANA2_CH0_CLKN_EN_END      (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA3_UNION
 �ṹ˵��  : ch0_reg_debug_ana3 �Ĵ����ṹ���塣��ַƫ����:0xE3����ֵ:0x80�����:8
 �Ĵ���˵��: PLL���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana3_reg;
    struct
    {
        unsigned long  reserved         : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH0_GPLL_CP_CTRL : 4;  /* bit[4-7]: GPLL��ɱõ�������(����Ч)
                                                           Basic: 0.25*Icp
                                                           Bit0:  0.25*Icp
                                                           Bit1:  0.25*Icp
                                                           Bit2:  0.5*Icp
                                                           Bit3:  0.5*Icp */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA3_UNION;
#define ABB_CH0_REG_DEBUG_ANA3_CH0_GPLL_CP_CTRL_START  (4)
#define ABB_CH0_REG_DEBUG_ANA3_CH0_GPLL_CP_CTRL_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA4_UNION
 �ṹ˵��  : ch0_reg_debug_ana4 �Ĵ����ṹ���塣��ַƫ����:0xE4����ֵ:0x80�����:8
 �Ĵ���˵��: PLL���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana4_reg;
    struct
    {
        unsigned long  reserved         : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH0_WPLL_CP_CTRL : 4;  /* bit[4-7]: WPLL��ɱõ�������(����Ч)
                                                           Basic: 0.25*Icp
                                                           Bit0:  0.25*Icp
                                                           Bit1:  0.25*Icp
                                                           Bit2:  0.5*Icp
                                                           Bit3:  0.5*Icp */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA4_UNION;
#define ABB_CH0_REG_DEBUG_ANA4_CH0_WPLL_CP_CTRL_START  (4)
#define ABB_CH0_REG_DEBUG_ANA4_CH0_WPLL_CP_CTRL_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA5_UNION
 �ṹ˵��  : ch0_reg_debug_ana5 �Ĵ����ṹ���塣��ַƫ����:0xE5����ֵ:0x00�����:8
 �Ĵ���˵��: �����������ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana5_reg;
    struct
    {
        unsigned long  reserved         : 7;  /* bit[0-6]: Reserved */
        unsigned long  CH0_BG_FASTUP_EN : 1;  /* bit[7]  : 0 disable
                                                           1 enable */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA5_UNION;
#define ABB_CH0_REG_DEBUG_ANA5_CH0_BG_FASTUP_EN_START  (7)
#define ABB_CH0_REG_DEBUG_ANA5_CH0_BG_FASTUP_EN_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA6_UNION
 �ṹ˵��  : ch0_reg_debug_ana6 �Ĵ����ṹ���塣��ַƫ����:0xE6����ֵ:0x41�����:8
 �Ĵ���˵��: Bandgap��TCXO���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana6_reg;
    struct
    {
        unsigned long  CH0_G_FREF_SEL : 1;  /* bit[0]  : GPLL�ο�Ƶ������
                                                         1: 19.2MHz�ο�ʱ�ӣ�����ģʽ
                                                         0: 26MHz�ο�ʱ�ӣ�����ģʽ */
        unsigned long  reserved       : 3;  /* bit[1-3]: Reserved */
        unsigned long  CH0_TCXO_DRV   : 2;  /* bit[4-5]: TCXO BUFFER��������
                                                         00: 1x
                                                         01: 2x
                                                         10: 3x
                                                         11: 4x */
        unsigned long  CH0_CLKIN_PD   : 1;  /* bit[6]  : TEST CLK INPUT�µ����
                                                         0: ����
                                                         1: �ر� */
        unsigned long  CH0_HOLD_BG    : 1;  /* bit[7]  : Sleepģʽʱ�Ƿ񱣳�Bandgap�����Ŀ����źţ�����refgenģ�������PD_BG�źŹ�ͬ����Bandgap��״̬
                                                         0: Bandgap״̬��PD_BG�źſ��ƣ�������Sleepģʽʱ��Bandgap���رգ�����Bandgap����
                                                         1: Bandgapʼ�չ��� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA6_UNION;
#define ABB_CH0_REG_DEBUG_ANA6_CH0_G_FREF_SEL_START  (0)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_G_FREF_SEL_END    (0)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_TCXO_DRV_START    (4)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_TCXO_DRV_END      (5)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_CLKIN_PD_START    (6)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_CLKIN_PD_END      (6)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_HOLD_BG_START     (7)
#define ABB_CH0_REG_DEBUG_ANA6_CH0_HOLD_BG_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA7_UNION
 �ṹ˵��  : ch0_reg_debug_ana7 �Ĵ����ṹ���塣��ַƫ����:0xE7����ֵ:0x00�����:8
 �Ĵ���˵��: �������ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana7_reg;
    struct
    {
        unsigned long  CH0_DRVBUF_CT : 3;  /* bit[0-2]: L/W/G ����ADC ���Buffer�������ڿ���
                                                        000: 1.0x��Ĭ�ϣ�
                                                        001: 0.2x
                                                        010: 0.6x
                                                        011: 0.3x
                                                        100: 0.4x
                                                        101: 0.8x
                                                        110: 1.4x
                                                        111: 1.6x */
        unsigned long  CH0_IREF_CTRL : 3;  /* bit[3-5]: �����ο���������
                                                        000��5u
                                                        001��2u
                                                        010��3u
                                                        011��4u
                                                        100��6u
                                                        101��7u
                                                        110��8u
                                                        111��9u */
        unsigned long  reserved      : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA7_UNION;
#define ABB_CH0_REG_DEBUG_ANA7_CH0_DRVBUF_CT_START  (0)
#define ABB_CH0_REG_DEBUG_ANA7_CH0_DRVBUF_CT_END    (2)
#define ABB_CH0_REG_DEBUG_ANA7_CH0_IREF_CTRL_START  (3)
#define ABB_CH0_REG_DEBUG_ANA7_CH0_IREF_CTRL_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA8_UNION
 �ṹ˵��  : ch0_reg_debug_ana8 �Ĵ����ṹ���塣��ַƫ����:0xE8����ֵ:0x00�����:8
 �Ĵ���˵��: �������ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana8_reg;
    struct
    {
        unsigned long  CH0_TX_CURRENT : 4;  /* bit[0-3]: ����TXͨ��LPF��·��������
                                                         0000��1.0x
                                                         0001��0.9x
                                                         0010��0.8x
                                                         0011��0.7x
                                                         0100��2.0x
                                                         0101��1.8x
                                                         0110��1.6x
                                                         0111��1.4x
                                                         1xxx��Reserved */
        unsigned long  CH0_QU_MODE    : 1;  /* bit[4]  : ������ģʽѡ�� */
        unsigned long  reserved       : 3;  /* bit[5-7]: Reserved */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA8_UNION;
#define ABB_CH0_REG_DEBUG_ANA8_CH0_TX_CURRENT_START  (0)
#define ABB_CH0_REG_DEBUG_ANA8_CH0_TX_CURRENT_END    (3)
#define ABB_CH0_REG_DEBUG_ANA8_CH0_QU_MODE_START     (4)
#define ABB_CH0_REG_DEBUG_ANA8_CH0_QU_MODE_END       (4)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA9_UNION
 �ṹ˵��  : ch0_reg_debug_ana9 �Ĵ����ṹ���塣��ַƫ����:0xE9����ֵ:0x00�����:8
 �Ĵ���˵��: ADC���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana9_reg;
    struct
    {
        unsigned long  CH0_DAC_DUM_B0   : 1;  /* bit[0]  : RX����sub_DAC Dummy��Ԫ���ƣ���һλ
                                                           0������
                                                           1���ر� */
        unsigned long  CH0_L_PUP_MODE   : 1;  /* bit[1]  : LTE ADCģ������ģʽѡ��
                                                           0���Զ�ģʽ
                                                           1�����üĴ���ģʽ */
        unsigned long  CH0_IB_SEL       : 1;  /* bit[2]  : ���������������ĵ����Ƿ�ɵ�
                                                           0�����ɵ�
                                                           1���ɵ� */
        unsigned long  CH0_L_DEM_PD     : 1;  /* bit[3]  : LTE ADC DEM���ܹر��ź�
                                                           0��DEMʹ��
                                                           1��DEM��ʹ�� */
        unsigned long  CH0_L_TUNING_SEL : 1;  /* bit[4]  : LTE ADCģ��Tuning���ѡ��
                                                           0��ѡ��Tuningģ��������ΪLTE ADC��Tuning��
                                                           1��ѡ��Ĵ����������ΪLTE ADC��Tuning�� */
        unsigned long  CH0_RX_IBCT_DAC  : 3;  /* bit[5-7]: RX����sub_DAC��������
                                                           000: 1.0x
                                                           001: 0.2x
                                                           010: 0.6x
                                                           011: 0.3x
                                                           100: 0.4x
                                                           101: 0.8x
                                                           110: 1.4x
                                                           111: 1.6x */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA9_UNION;
#define ABB_CH0_REG_DEBUG_ANA9_CH0_DAC_DUM_B0_START    (0)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_DAC_DUM_B0_END      (0)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_PUP_MODE_START    (1)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_PUP_MODE_END      (1)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_IB_SEL_START        (2)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_IB_SEL_END          (2)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_DEM_PD_START      (3)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_DEM_PD_END        (3)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_TUNING_SEL_START  (4)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_L_TUNING_SEL_END    (4)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_RX_IBCT_DAC_START   (5)
#define ABB_CH0_REG_DEBUG_ANA9_CH0_RX_IBCT_DAC_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA10_UNION
 �ṹ˵��  : ch0_reg_debug_ana10 �Ĵ����ṹ���塣��ַƫ����:0xEA����ֵ:0x00�����:8
 �Ĵ���˵��: ADC��λ���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana10_reg;
    struct
    {
        unsigned long  CH0_DAC_DUM_B2B1 : 2;  /* bit[0-1]: RX����sub_DAC Dummy��Ԫ���ƣ�����λ
                                                           0������
                                                           1���ر� */
        unsigned long  CH0_L_PUP_CTRL0  : 1;  /* bit[2]  : LTE ADC�е�һ�����������ݸ�λ����
                                                           0������λ
                                                           1����λ */
        unsigned long  CH0_L_PUP_CTRL1  : 1;  /* bit[3]  : LTE ADC�еڶ������������ݸ�λ����
                                                           0������λ
                                                           1����λ */
        unsigned long  CH0_L_PUP_CTRL2  : 1;  /* bit[4]  : LTE ADC�е��������������ݸ�λ����
                                                           0: ����λ
                                                           1����λ */
        unsigned long  CH0_L_PUP_CTRL3  : 1;  /* bit[5]  : LTE ADC��CKGENģ��Powerup����
                                                           0��Powerdown
                                                           1��Powerup */
        unsigned long  CH0_L_PUP_CTRL4  : 1;  /* bit[6]  : LTE ADC��OPģ��Powerup����
                                                           0��Powerdown
                                                           1��Powerup */
        unsigned long  CH0_L_PUP_CTRL5  : 1;  /* bit[7]  : LTE ADC��DACģ��Powerup����
                                                           0��Powerdown
                                                           1��Powerup */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA10_UNION;
#define ABB_CH0_REG_DEBUG_ANA10_CH0_DAC_DUM_B2B1_START  (0)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_DAC_DUM_B2B1_END    (1)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL0_START   (2)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL0_END     (2)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL1_START   (3)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL1_END     (3)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL2_START   (4)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL2_END     (4)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL3_START   (5)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL3_END     (5)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL4_START   (6)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL4_END     (6)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL5_START   (7)
#define ABB_CH0_REG_DEBUG_ANA10_CH0_L_PUP_CTRL5_END     (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA14_UNION
 �ṹ˵��  : ch0_reg_debug_ana14 �Ĵ����ṹ���塣��ַƫ����:0xEE����ֵ:0x00�����:8
 �Ĵ���˵��: ADC���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana14_reg;
    struct
    {
        unsigned long  CH0_L_OL_CT   : 3;  /* bit[0-2]: LTE Overloadģ������
                                                        00��16����������������С��
                                                        01��8����������������С��
                                                        10��4����������������С��
                                                        11���ر�Overload��� */
        unsigned long  CH0_L_ADC_ICT : 3;  /* bit[3-5]: ����������ƫ�õ���
                                                        000: 1.0x
                                                        001: 0.2x
                                                        010: 0.6x
                                                        011: 0.3x
                                                        100: 0.4x
                                                        101: 0.8x
                                                        110: 1.4x
                                                        111: 1.6x */
        unsigned long  CH0_L_CK_CT   : 2;  /* bit[6-7]: LTE SYNCʱ�����
                                                        00��No delay
                                                        01��250ps delay
                                                        10��500ps delay
                                                        11��1000ps delay */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA14_UNION;
#define ABB_CH0_REG_DEBUG_ANA14_CH0_L_OL_CT_START    (0)
#define ABB_CH0_REG_DEBUG_ANA14_CH0_L_OL_CT_END      (2)
#define ABB_CH0_REG_DEBUG_ANA14_CH0_L_ADC_ICT_START  (3)
#define ABB_CH0_REG_DEBUG_ANA14_CH0_L_ADC_ICT_END    (5)
#define ABB_CH0_REG_DEBUG_ANA14_CH0_L_CK_CT_START    (6)
#define ABB_CH0_REG_DEBUG_ANA14_CH0_L_CK_CT_END      (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA16_UNION
 �ṹ˵��  : ch0_reg_debug_ana16 �Ĵ����ṹ���塣��ַƫ����:0xF0����ֵ:0x00�����:8
 �Ĵ���˵��: ADC���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana16_reg;
    struct
    {
        unsigned long  CH0_IBCT_STG12 : 3;  /* bit[0-2]: RX ADC Stage 12��������
                                                         000: 1.0x
                                                         001: 0.2x
                                                         010: 0.6x
                                                         011: 0.3x
                                                         100: 0.4x
                                                         101: 0.8x
                                                         110: 1.4x
                                                         111: 1.6x */
        unsigned long  CH0_IBCT_STG3  : 3;  /* bit[3-5]: RX ADC Stage 3��������
                                                         000: 1.0x
                                                         001: 0.2x
                                                         010: 0.6x
                                                         011: 0.3x
                                                         100: 0.4x
                                                         101: 0.8x
                                                         110: 1.4x
                                                         111: 1.6x */
        unsigned long  CH0_PDM_CTRL   : 1;  /* bit[6]  : RX���PDM�������
                                                         0��adder encoder
                                                         1��de-bubble encoder */
        unsigned long  CH0_G_I_CTRL   : 1;  /* bit[7]  : Gģʽ��������
                                                         0��������˷�����
                                                         1��������˷����� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA16_UNION;
#define ABB_CH0_REG_DEBUG_ANA16_CH0_IBCT_STG12_START  (0)
#define ABB_CH0_REG_DEBUG_ANA16_CH0_IBCT_STG12_END    (2)
#define ABB_CH0_REG_DEBUG_ANA16_CH0_IBCT_STG3_START   (3)
#define ABB_CH0_REG_DEBUG_ANA16_CH0_IBCT_STG3_END     (5)
#define ABB_CH0_REG_DEBUG_ANA16_CH0_PDM_CTRL_START    (6)
#define ABB_CH0_REG_DEBUG_ANA16_CH0_PDM_CTRL_END      (6)
#define ABB_CH0_REG_DEBUG_ANA16_CH0_G_I_CTRL_START    (7)
#define ABB_CH0_REG_DEBUG_ANA16_CH0_G_I_CTRL_END      (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA17_UNION
 �ṹ˵��  : ch0_reg_debug_ana17 �Ĵ����ṹ���塣��ַƫ����:0xF1����ֵ:0x00�����:8
 �Ĵ���˵��: PLL���ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana17_reg;
    struct
    {
        unsigned long  reserved          : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH0_PLL1_CLK_TEST : 2;  /* bit[4-5]: PLLʱ�Ӳ���PAD�ź�ѡ��
                                                            00��ʱ�Ӳ���PAD����
                                                            01��WPLL���ʱ�ӵ�PAD
                                                            10��GPLL���ʱ�ӵ�PAD */
        unsigned long  CH0_PLL1_ANA_TEST : 2;  /* bit[6-7]: PLL���Ƶ�ѹ����PAD�ź�ѡ��
                                                            00�����Ƶ�ѹ����PAD����
                                                            01��WPLL������Ƶ�ѹ��PAD
                                                            10��GPLL������Ƶ�ѹ��PAD */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA17_UNION;
#define ABB_CH0_REG_DEBUG_ANA17_CH0_PLL1_CLK_TEST_START  (4)
#define ABB_CH0_REG_DEBUG_ANA17_CH0_PLL1_CLK_TEST_END    (5)
#define ABB_CH0_REG_DEBUG_ANA17_CH0_PLL1_ANA_TEST_START  (6)
#define ABB_CH0_REG_DEBUG_ANA17_CH0_PLL1_ANA_TEST_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA19_UNION
 �ṹ˵��  : ch0_reg_debug_ana19 �Ĵ����ṹ���塣��ַƫ����:0xF3����ֵ:0x3C�����:8
 �Ĵ���˵��: ʱ�ӷ��ؿ��ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana19_reg;
    struct
    {
        unsigned long  CH0_CLK_PADF_SEL : 2;  /* bit[0-1]: ���Թܽ����ʱ��Ƶ�ʿ���
                                                           00: ������ʱ��
                                                           01��WPLL�������
                                                           10��GPLL�������
                                                           11��WPLL��GPLL������� */
        unsigned long  CH0_HK_CLK_EN    : 1;  /* bit[2]  : HKADC��Tuningģ��ʱ��ʹ���ź�
                                                           0��ʱ�ӹر�
                                                           1��ʱ��ʹ�� */
        unsigned long  CH0_AUX_CLK_EN   : 1;  /* bit[3]  : PLLģ��153.6MHzʱ��ʹ���ź�
                                                           0��ʱ�ӹر�
                                                           1��ʱ��ʹ�� */
        unsigned long  CH0_DAC_CLK_EN   : 1;  /* bit[4]  : PLLģ��307.2MHzʱ��ʹ���ź�
                                                           0��ʱ�ӹر�
                                                           1��ʱ��ʹ�� */
        unsigned long  CH0_ADC_CLK_EN   : 1;  /* bit[5]  : PLLģ��307.2MHzʱ��ʹ���ź�
                                                           0��ʱ�ӹر�
                                                           1��ʱ��ʹ�� */
        unsigned long  reserved         : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA19_UNION;
#define ABB_CH0_REG_DEBUG_ANA19_CH0_CLK_PADF_SEL_START  (0)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_CLK_PADF_SEL_END    (1)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_HK_CLK_EN_START     (2)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_HK_CLK_EN_END       (2)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_AUX_CLK_EN_START    (3)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_AUX_CLK_EN_END      (3)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_DAC_CLK_EN_START    (4)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_DAC_CLK_EN_END      (4)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_ADC_CLK_EN_START    (5)
#define ABB_CH0_REG_DEBUG_ANA19_CH0_ADC_CLK_EN_END      (5)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_DEBUG_ANA20_UNION
 �ṹ˵��  : ch0_reg_debug_ana20 �Ĵ����ṹ���塣��ַƫ����:0xF4����ֵ:0x20�����:8
 �Ĵ���˵��: ģ����ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_reg_debug_ana20_reg;
    struct
    {
        unsigned long  reserved      : 4;  /* bit[0-3]: Reserved */
        unsigned long  CH0_EXT_BG_EN : 1;  /* bit[4]  : �ⲿBandGapʹ���ź� */
        unsigned long  CH0_CAP_MULT  : 2;  /* bit[5-6]: ���������������ݵ��� */
        unsigned long  CH0_CAP_SEL   : 1;  /* bit[7]  : Tuning��·����ѡ��
                                                        0: �����
                                                        1: С���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_REG_DEBUG_ANA20_UNION;
#define ABB_CH0_REG_DEBUG_ANA20_CH0_EXT_BG_EN_START  (4)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_EXT_BG_EN_END    (4)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_CAP_MULT_START   (5)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_CAP_MULT_END     (6)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_CAP_SEL_START    (7)
#define ABB_CH0_REG_DEBUG_ANA20_CH0_CAP_SEL_END      (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_2G_RX_DELAY_UNION
 �ṹ˵��  : ch0_2g_rx_delay �Ĵ����ṹ���塣��ַƫ����:0xFC����ֵ:0x20�����:8
 �Ĵ���˵��: 2gģʽRX��·ʱ���ӳٵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_2g_rx_delay_reg;
    struct
    {
        unsigned long  ch0_rx_delay        : 4;  /* bit[0-3]: RX_MCLKʱ����ʱѡ��
                                                                  2G(ns) 3G(ns) 4G(ns)
                                                              0 : 12.8  3.3  1.6 
                                                              1 : 25.6  6.5  3.3 
                                                              2 : 38.5  9.8  4.9 
                                                              3 : 51.3  13.0  6.5 
                                                              4 : 64.1  16.3  8.1 
                                                              5 : 76.9  19.5  9.8 
                                                              6 : 89.7  22.8  11.4 
                                                              7 : 102.6  26.0  13.0 
                                                              8 : 115.4  29.3  14.6 
                                                              9 : 128.2  32.6  16.3 
                                                              10 : 141.0  35.8  17.9 
                                                              11 : 153.8  39.1  19.5 
                                                              12 : 166.7  42.3  21.2 
                                                              13 : 179.5  45.6  22.8 
                                                              14 : 192.3  48.8  24.4 
                                                              15 : 205.1  52.1  26.0  */
        unsigned long  ch0_rx_clk_inv      : 1;  /* bit[4]  : rx_clk���������ƣ�
                                                              1'b0��rx_clk bypass���
                                                              1'b1��rx_clk������� */
        unsigned long  ch0_rx_clk_delay_bp : 1;  /* bit[5]  : rx_clk���delay bypass���أ�
                                                              1'b0��rx_clk ���delay ��bypass
                                                              1'b1��rx_clk ���delay bypass */
        unsigned long  reserved            : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_2G_RX_DELAY_UNION;
#define ABB_CH0_2G_RX_DELAY_ch0_rx_delay_START         (0)
#define ABB_CH0_2G_RX_DELAY_ch0_rx_delay_END           (3)
#define ABB_CH0_2G_RX_DELAY_ch0_rx_clk_inv_START       (4)
#define ABB_CH0_2G_RX_DELAY_ch0_rx_clk_inv_END         (4)
#define ABB_CH0_2G_RX_DELAY_ch0_rx_clk_delay_bp_START  (5)
#define ABB_CH0_2G_RX_DELAY_ch0_rx_clk_delay_bp_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CH0_3G_RX_DELAY_UNION
 �ṹ˵��  : ch0_3g_rx_delay �Ĵ����ṹ���塣��ַƫ����:0xFD����ֵ:0x20�����:8
 �Ĵ���˵��: 3gģʽRX��·ʱ���ӳٵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_3g_rx_delay_reg;
    struct
    {
        unsigned long  ch0_rx_delay        : 4;  /* bit[0-3]: RX_MCLKʱ����ʱѡ��
                                                                  2G(ns) 3G(ns) 4G(ns)
                                                              0 : 12.8  3.3  1.6 
                                                              1 : 25.6  6.5  3.3 
                                                              2 : 38.5  9.8  4.9 
                                                              3 : 51.3  13.0  6.5 
                                                              4 : 64.1  16.3  8.1 
                                                              5 : 76.9  19.5  9.8 
                                                              6 : 89.7  22.8  11.4 
                                                              7 : 102.6  26.0  13.0 
                                                              8 : 115.4  29.3  14.6 
                                                              9 : 128.2  32.6  16.3 
                                                              10 : 141.0  35.8  17.9 
                                                              11 : 153.8  39.1  19.5 
                                                              12 : 166.7  42.3  21.2 
                                                              13 : 179.5  45.6  22.8 
                                                              14 : 192.3  48.8  24.4 
                                                              15 : 205.1  52.1  26.0  */
        unsigned long  ch0_rx_clk_inv      : 1;  /* bit[4]  : rx_clk���������ƣ�
                                                              1'b0��rx_clk bypass���
                                                              1'b1��rx_clk������� */
        unsigned long  ch0_rx_clk_delay_bp : 1;  /* bit[5]  : rx_clk���delay bypass���أ�
                                                              1'b0��rx_clk ���delay ��bypass
                                                              1'b1��rx_clk ���delay bypass */
        unsigned long  reserved            : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_3G_RX_DELAY_UNION;
#define ABB_CH0_3G_RX_DELAY_ch0_rx_delay_START         (0)
#define ABB_CH0_3G_RX_DELAY_ch0_rx_delay_END           (3)
#define ABB_CH0_3G_RX_DELAY_ch0_rx_clk_inv_START       (4)
#define ABB_CH0_3G_RX_DELAY_ch0_rx_clk_inv_END         (4)
#define ABB_CH0_3G_RX_DELAY_ch0_rx_clk_delay_bp_START  (5)
#define ABB_CH0_3G_RX_DELAY_ch0_rx_clk_delay_bp_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CH0_4G_RX_DELAY_UNION
 �ṹ˵��  : ch0_4g_rx_delay �Ĵ����ṹ���塣��ַƫ����:0xFE����ֵ:0x20�����:8
 �Ĵ���˵��: 4gģʽRX��·ʱ���ӳٵ�����
*****************************************************************************/
typedef union
{
    unsigned long      ch0_4g_rx_delay_reg;
    struct
    {
        unsigned long  ch0_rx_delay        : 4;  /* bit[0-3]: RX_MCLKʱ����ʱѡ��
                                                                  2G(ns) 3G(ns) 4G(ns)
                                                              0 : 12.8  3.3  1.6 
                                                              1 : 25.6  6.5  3.3 
                                                              2 : 38.5  9.8  4.9 
                                                              3 : 51.3  13.0  6.5 
                                                              4 : 64.1  16.3  8.1 
                                                              5 : 76.9  19.5  9.8 
                                                              6 : 89.7  22.8  11.4 
                                                              7 : 102.6  26.0  13.0 
                                                              8 : 115.4  29.3  14.6 
                                                              9 : 128.2  32.6  16.3 
                                                              10 : 141.0  35.8  17.9 
                                                              11 : 153.8  39.1  19.5 
                                                              12 : 166.7  42.3  21.2 
                                                              13 : 179.5  45.6  22.8 
                                                              14 : 192.3  48.8  24.4 
                                                              15 : 205.1  52.1  26.0  */
        unsigned long  ch0_rx_clk_inv      : 1;  /* bit[4]  : rx_clk���������ƣ�
                                                              1'b0��rx_clk bypass���
                                                              1'b1��rx_clk������� */
        unsigned long  ch0_rx_clk_delay_bp : 1;  /* bit[5]  : rx_clk���delay bypass���أ�
                                                              1'b0��rx_clk ���delay ��bypass
                                                              1'b1��rx_clk ���delay bypass */
        unsigned long  reserved            : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_4G_RX_DELAY_UNION;
#define ABB_CH0_4G_RX_DELAY_ch0_rx_delay_START         (0)
#define ABB_CH0_4G_RX_DELAY_ch0_rx_delay_END           (3)
#define ABB_CH0_4G_RX_DELAY_ch0_rx_clk_inv_START       (4)
#define ABB_CH0_4G_RX_DELAY_ch0_rx_clk_inv_END         (4)
#define ABB_CH0_4G_RX_DELAY_ch0_rx_clk_delay_bp_START  (5)
#define ABB_CH0_4G_RX_DELAY_ch0_rx_clk_delay_bp_END    (5)




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

#endif /* end of phy_abb_interface.h */

