/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : phy_abb_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-12-09 09:35:19
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��12��9��
    ��    ��   : w00181973
    �޸�����   : �ӡ�ComstarTV310(V7R22) ABB�Ĵ�������.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __ABB_INTERFACE_TV310_H__
#define __ABB_INTERFACE_TV310_H__

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
                     (1/4) register_define_abb_com
 ***======================================================================***/
/* �Ĵ���˵��������ģʽ�Ĵ�����
 bit[7:6]    ����
 bit[5:4]    bit[4:3]����ģʽ���ƣ�
             00������ģʽ(Ĭ��)
             01�������㷨�߼�����ģʽ
             10��RXģ�����ģʽ(bypass RX�����˲���)
             11������/ģ��ӿڻ���
             bit[5] reserved
 bit[3:2]    ����
 bit[1]
 bit[0]
   UNION�ṹ:  ABB_TESTMODE_UNION */
#define ABB_TESTMODE_ADDR                             (ABB_BASE_ADDR + 0x0)

/* �Ĵ���˵����ATE_TEST_MODE
 bit[7:3]    ����
 bit[2:0]
   UNION�ṹ:  ABB_ATE_TESTMODE_UNION */
#define ABB_ATE_TESTMODE_ADDR                         (ABB_BASE_ADDR + 0x1)

/* �Ĵ���˵����TCXO_RPT
 bit[7:1]    ����
 bit[0]
   UNION�ṹ:  ABB_TCXO_RPT_UNION */
#define ABB_TCXO_RPT_ADDR                             (ABB_BASE_ADDR + 0x2)

/* �Ĵ���˵����ABB���ֲ��ָ�λ�ź�
 bit[7:1]    ����
 bit[0]
   UNION�ṹ:  ABB_ABB_DIG_PWR_RST_UNION */
#define ABB_ABB_DIG_PWR_RST_ADDR                      (ABB_BASE_ADDR + 0x3)

/* �Ĵ���˵�������ֵ��ԼĴ�����
 bit[7:2]    ����
 bit[1:0]    ���ֵ��ԼĴ���
             bit[0]���ܽ�CH0_CLK_52M���ʱ��ѡ��
             1�����GPLL
             0�����SCPLL0
   UNION�ṹ:  ABB_CH0_COMM_REG_DEBUG_DIG_UNION */
#define ABB_CH0_COMM_REG_DEBUG_DIG_ADDR               (ABB_BASE_ADDR + 0x4)

/* �Ĵ���˵�������ֵ��ԼĴ�����
 bit[7:2]    ����
 bit[1:0]    ���ֵ��ԼĴ���
             bit[0]���ܽ�CH1_CLK_52M���ʱ��ѡ��
             1�����GPLL
             0�����SCPLL1
   UNION�ṹ:  ABB_CH1_COMM_REG_DEBUG_DIG_UNION */
#define ABB_CH1_COMM_REG_DEBUG_DIG_ADDR               (ABB_BASE_ADDR + 0x5)

/* �Ĵ���˵����BIST���üĴ���
 bit[7]      bist����ͨ���߿ؿ���ģʽ��
             0��ͨ���߿�bist����ʱȫ������
             1��ͨ���߿�bist����ʱ����ͨ�����ߣ��������͡�
 bit[6:5]    �л�iq��ͨ��ʱ����30����·ʱ����ʱ���ڴ˻��������ӵ���ʱSwitch_delay��ѡ���źţ�
             00��0us��(Ĭ��)
             01��20us��
             10��50us��
             11��200us��
 bit[4:3]    ��ʱʱ��2����ֵ,�ź�ֱ�����������ȶ�ʱ�����á�
             00:20us��Ĭ�ϣ�
             01:50us
             10:200us
             11:500us
 bit[2:1]    ��ʱʱ��1����ֵ,ͨ·ʹ�ܵ����Կ�ʼ����ʱʱ��ѡ��
             00:50us��Ĭ�ϣ�
             01:100us
             10:200us
             11:500us
 bit[0]      BISTʹ�ܡ�
             0����ʹ�ܣ�
             1��ʹ�ܡ�
   UNION�ṹ:  ABB_BIST_CFG_1_UNION */
#define ABB_BIST_CFG_1_ADDR                           (ABB_BASE_ADDR + 0x6)

/* �Ĵ���˵����BIST����ģʽbypass�Ĵ���
   ��      ����ģʽbypass�źţ�ÿ��ģʽռһ��bit
            [0]��1��ʾGģ��BIST��bypass��0��ʾGģ��BIST����������
            [1]��1��ʾW��BIST��bypass��0��ʾWCDMAģ��BIST����������
            [2]��1��ʾTDS��BIST��bypass��0��ʾTDS��BIST����������
            [3]��1��ʾLTEģ��BIST��bypass��0��ʾLTEģ��BIST����������
            [4]��1��ʾCDMAģ��BIST��bypass��0��ʾCDMAģ��BIST����������
            [5]��1��ʾCAģ��BIST��bypass��0��ʾCAģ��BIST����������
            [6]��1��ʾET0ģ��BIST��bypass��0��ʾETģ��BIST����������
            [7]��1��ʾET1ģ��BIST��bypass��0��ʾETģ��BIST����������
   UNION�ṹ ���� */
#define ABB_BIST_CFG_2_ADDR                           (ABB_BASE_ADDR + 0x7)

/* �Ĵ���˵����BIST����ͨ��bypass�Ĵ���
   ��      ����Rx��bypass�źţ�
            [0]��Rx_1��bypass�źţ�0��ʾ��Ҫ��Rx_1��BIST��1��ʾ������
            [1]��Rx_2��bypass�źţ�0��ʾ��Ҫ��Rx_2��BIST��1��ʾ������
            [2]��Rx_3��bypass�źţ�0��ʾ��Ҫ��Rx_3��BIST��1��ʾ������
            [3]��Rx_4��bypass�źţ�0��ʾ��Ҫ��Rx_4��BIST��1��ʾ������
            [4]��Rx_5��bypass�źţ�0��ʾ��Ҫ��Rx_5��BIST��1��ʾ������
            [5]��Rx_6��bypass�źţ�0��ʾ��Ҫ��Rx_6��BIST��1��ʾ������
            [6]��Rx_7��bypass�źţ�0��ʾ��Ҫ��Rx_7��BIST��1��ʾ������
            [7]��Rx_8��bypass�źţ�0��ʾ��Ҫ��Rx_8��BIST��1��ʾ������
   UNION�ṹ ���� */
#define ABB_BIST_CFG_3_ADDR                           (ABB_BASE_ADDR + 0x8)

/* �Ĵ���˵����BIST������Ŀbypass�Ĵ���
 bit[7:6]    ����
 bit[5:0]    ������bypass�źţ�
             [0]:1��ʾDC_Iָ��bypass��0��ʾ��bypass��
             [1]:1��ʾDC_Qָ��bypass��0��ʾ��bypass��
             [2]:1��ʾSNDR_Iָ��bypass��0��ʾ��bypass��
             [3]:1��ʾSNDR_Qָ��bypass��0��ʾ��bypass��
             [4]:1��ʾGAIN_MISMATCHָ��bypass��0��ʾ��bypass��
             [5]:1��ʾGAIN_ERRORָ��bypass��0��ʾ��bypass��
   UNION�ṹ:  ABB_BIST_CFG_4_UNION */
#define ABB_BIST_CFG_4_ADDR                           (ABB_BASE_ADDR + 0x9)

/* �Ĵ���˵����BIST�ֶ��������üĴ���
 bit[7:5]    ����
 bit[4]      0��bistʱ�����ſؿ��ƣ�bist_en���ߺ�bist����ʱ�ӡ���Ĭ�ϣ�
             1��bistʱ�Ӳ����ſؿ��ơ�
 bit[3:1]    �ֶ�����ѡ����������ͨ����
             000��RXA��CH0��
             001��RXB��CH0��
             010��RXA��CH1��
             011��RXB��CH1��
             100��RXA��CH2��
             101��RXB��CH2��
             110��RXA��CH3��
             111��RXB��CH3��
 bit[0]      0���Զ���������
             1���ֶ���������
   UNION�ṹ:  ABB_BIST_CFG_5_UNION */
#define ABB_BIST_CFG_5_ADDR                           (ABB_BASE_ADDR + 0xA)

/* �Ĵ���˵����BIST���״̬�Ĵ���
 bit[7]      BIST���������Ĳ������Ƿ�ͨ������δbypass�Ĳ����Ƿ�ȫ��ͨ����
             0��δͨ����
             1��ͨ����
 bit[6:1]    ����
 bit[0]      SNDR�������״̬��
             0��û����ɣ�
             1����ɡ�
   UNION�ṹ:  ABB_BIST_RPT_1_UNION */
#define ABB_BIST_RPT_1_ADDR                           (ABB_BASE_ADDR + 0xB)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
 bit[7:6]    ����
 bit[5:0]    ÿһ�μ������6�������Ƿ�pass��
             [0]:1��ʾDC_Iָ��pass��0��ʾ��pass��
             [1]:1��ʾDC_Qָ��pass��0��ʾ��pass��
             [2]:1��ʾSNDR_Iָ��pass��0��ʾ��pass��
             [3]:1��ʾSNDR_Qָ��pass��0��ʾ��pass��
             [4]:1��ʾGAIN_MISMATCHָ��pass��0��ʾ��pass��
             [5]:1��ʾGAIN_ERRORָ��pass��0��ʾ��pass��
   UNION�ṹ:  ABB_BIST_RPT_2_UNION */
#define ABB_BIST_RPT_2_ADDR                           (ABB_BASE_ADDR + 0xC)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����Rx_1��Bist��������ÿ��ģʽ1bit��
            [0]��1��ʾGģ��BIST pass��0��ʾGģ��BIST fail��
            [1]��1��ʾWCDMAģ��BIST pass��0��ʾWCDMAģSC��BIST fail��
            [2]��1��ʾTDS��BIST pass��0��ʾTDSģDC��BIST fail��
            [3]��1��ʾLTEģ��BIST pass��0��ʾLTEģ��BIST fail��
            [4]��1��ʾCDMAģ��BIST pass��0��ʾCDMAģ��BIST fail��
            [5]��1��ʾCAģ��BIST pass��0��ʾCAģ��BIST fail��
            [6]��1��ʾET0ģ��BIST pass��0��ʾETģ��BIST fail��
            [7]��1��ʾET1ģ��BIST pass��0��ʾETģ��BIST fail��
   UNION�ṹ ���� */
#define ABB_BIST_RPT_3_ADDR                           (ABB_BASE_ADDR + 0xD)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����Rx_2��Bist��������ÿ��ģʽ1bit��
            [0]��1��ʾGģ��BIST pass��0��ʾGģ��BIST fail��
            [1]��1��ʾWCDMAģ��BIST pass��0��ʾWCDMAģSC��BIST fail��
            [2]��1��ʾTDS��BIST pass��0��ʾTDSģDC��BIST fail��
            [3]��1��ʾLTEģ��BIST pass��0��ʾLTEģ��BIST fail��
            [4]��1��ʾCDMAģ��BIST pass��0��ʾCDMAģ��BIST fail��
            [5]��1��ʾCAģ��BIST pass��0��ʾCAģ��BIST fail��
            [6]��1��ʾET0ģ��BIST pass��0��ʾETģ��BIST fail��
            [7]��1��ʾET1ģ��BIST pass��0��ʾETģ��BIST fail��
   UNION�ṹ ���� */
#define ABB_BIST_RPT_4_ADDR                           (ABB_BASE_ADDR + 0xE)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����Rx_3��Bist��������ÿ��ģʽ1bit��
            [0]��1��ʾGģ��BIST pass��0��ʾGģ��BIST fail��
            [1]��1��ʾWCDMAģ��BIST pass��0��ʾWCDMAģSC��BIST fail��
            [2]��1��ʾTDS��BIST pass��0��ʾTDSģDC��BIST fail��
            [3]��1��ʾLTEģ��BIST pass��0��ʾLTEģ��BIST fail��
            [4]��1��ʾCDMAģ��BIST pass��0��ʾCDMAģ��BIST fail��
            [5]��1��ʾCAģ��BIST pass��0��ʾCAģ��BIST fail��
            [6]��1��ʾET0ģ��BIST pass��0��ʾETģ��BIST fail��
            [7]��1��ʾET1ģ��BIST pass��0��ʾETģ��BIST fail��
   UNION�ṹ ���� */
#define ABB_BIST_RPT_5_ADDR                           (ABB_BASE_ADDR + 0xF)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����Rx_4��Bist��������ÿ��ģʽ1bit��
            [0]��1��ʾGģ��BIST pass��0��ʾGģ��BIST fail��
            [1]��1��ʾWCDMAģ��BIST pass��0��ʾWCDMAģSC��BIST fail��
            [2]��1��ʾTDS��BIST pass��0��ʾTDSģDC��BIST fail��
            [3]��1��ʾLTEģ��BIST pass��0��ʾLTEģ��BIST fail��
            [4]��1��ʾCDMAģ��BIST pass��0��ʾCDMAģ��BIST fail��
            [5]��1��ʾCAģ��BIST pass��0��ʾCAģ��BIST fail��
            [6]��1��ʾET0ģ��BIST pass��0��ʾETģ��BIST fail��
            [7]��1��ʾET1ģ��BIST pass��0��ʾETģ��BIST fail��
   UNION�ṹ ���� */
#define ABB_BIST_RPT_6_ADDR                           (ABB_BASE_ADDR + 0x10)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����Rx_5��Bist��������ÿ��ģʽ1bit��
            [0]��1��ʾGģ��BIST pass��0��ʾGģ��BIST fail��
            [1]��1��ʾWCDMAģ��BIST pass��0��ʾWCDMAģSC��BIST fail��
            [2]��1��ʾTDS��BIST pass��0��ʾTDSģDC��BIST fail��
            [3]��1��ʾLTEģ��BIST pass��0��ʾLTEģ��BIST fail��
            [4]��1��ʾCDMAģ��BIST pass��0��ʾCDMAģ��BIST fail��
            [5]��1��ʾCAģ��BIST pass��0��ʾCAģ��BIST fail��
            [6]��1��ʾET0ģ��BIST pass��0��ʾETģ��BIST fail��
            [7]��1��ʾET1ģ��BIST pass��0��ʾETģ��BIST fail��
   UNION�ṹ ���� */
#define ABB_BIST_RPT_7_ADDR                           (ABB_BASE_ADDR + 0x11)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
 bit[7:3]    ����
 bit[2:0]    I·dc�ϱ�ֵ��λ��
   UNION�ṹ:  ABB_BIST_RPT_8_UNION */
#define ABB_BIST_RPT_8_ADDR                           (ABB_BASE_ADDR + 0x12)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����I·dc�ϱ�ֵ��λ��
   UNION�ṹ ���� */
#define ABB_BIST_RPT_9_ADDR                           (ABB_BASE_ADDR + 0x13)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
 bit[7:3]    ����
 bit[2:0]    Q·dc�ϱ�ֵ��λ��
   UNION�ṹ:  ABB_BIST_RPT_10_UNION */
#define ABB_BIST_RPT_10_ADDR                          (ABB_BASE_ADDR + 0x14)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����Q·dc�ϱ�ֵ��λ��
   UNION�ṹ ���� */
#define ABB_BIST_RPT_11_ADDR                          (ABB_BASE_ADDR + 0x15)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����I·������ϱ���8bit���޷�������
   UNION�ṹ ���� */
#define ABB_BIST_RPT_12_ADDR                          (ABB_BASE_ADDR + 0x16)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����Q·������ϱ���8bit���޷�������
   UNION�ṹ ���� */
#define ABB_BIST_RPT_13_ADDR                          (ABB_BASE_ADDR + 0x17)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����Gain_mismatch�ϱ����޷�������
   UNION�ṹ ���� */
#define ABB_BIST_RPT_14_ADDR                          (ABB_BASE_ADDR + 0x18)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����Gain_error�ϱ����޷�������
   UNION�ṹ ���� */
#define ABB_BIST_RPT_15_ADDR                          (ABB_BASE_ADDR + 0x19)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����Rx_6��Bist��������ÿ��ģʽ1bit��
            [0]��1��ʾGģ��BIST pass��0��ʾGģ��BIST fail��
            [1]��1��ʾWCDMAģ��BIST pass��0��ʾWCDMAģSC��BIST fail��
            [2]��1��ʾTDS��BIST pass��0��ʾTDSģDC��BIST fail��
            [3]��1��ʾLTEģ��BIST pass��0��ʾLTEģ��BIST fail��
            [4]��1��ʾCDMAģ��BIST pass��0��ʾCDMAģ��BIST fail��
            [5]��1��ʾCAģ��BIST pass��0��ʾCAģ��BIST fail��
            [6]��1��ʾET0ģ��BIST pass��0��ʾETģ��BIST fail��
            [7]��1��ʾET1ģ��BIST pass��0��ʾETģ��BIST fail��
   UNION�ṹ ���� */
#define ABB_BIST_RPT_16_ADDR                          (ABB_BASE_ADDR + 0x1A)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����Rx_7��Bist��������ÿ��ģʽ1bit��
            [0]��1��ʾGģ��BIST pass��0��ʾGģ��BIST fail��
            [1]��1��ʾWCDMAģ��BIST pass��0��ʾWCDMAģSC��BIST fail��
            [2]��1��ʾTDS��BIST pass��0��ʾTDSģDC��BIST fail��
            [3]��1��ʾLTEģ��BIST pass��0��ʾLTEģ��BIST fail��
            [4]��1��ʾCDMAģ��BIST pass��0��ʾCDMAģ��BIST fail��
            [5]��1��ʾCAģ��BIST pass��0��ʾCAģ��BIST fail��
            [6]��1��ʾET0ģ��BIST pass��0��ʾETģ��BIST fail��
            [7]��1��ʾET1ģ��BIST pass��0��ʾETģ��BIST fail��
   UNION�ṹ ���� */
#define ABB_BIST_RPT_17_ADDR                          (ABB_BASE_ADDR + 0x1B)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����Rx_8��Bist��������ÿ��ģʽ1bit��
            [0]��1��ʾGģ��BIST pass��0��ʾGģ��BIST fail��
            [1]��1��ʾWCDMAģ��BIST pass��0��ʾWCDMAģSC��BIST fail��
            [2]��1��ʾTDS��BIST pass��0��ʾTDSģDC��BIST fail��
            [3]��1��ʾLTEģ��BIST pass��0��ʾLTEģ��BIST fail��
            [4]��1��ʾCDMAģ��BIST pass��0��ʾCDMAģ��BIST fail��
            [5]��1��ʾCAģ��BIST pass��0��ʾCAģ��BIST fail��
            [6]��1��ʾET0ģ��BIST pass��0��ʾETģ��BIST fail��
            [7]��1��ʾET1ģ��BIST pass��0��ʾETģ��BIST fail��
   UNION�ṹ ���� */
#define ABB_BIST_RPT_18_ADDR                          (ABB_BASE_ADDR + 0x1C)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����I·������ϱ���8bit���޷�������
   UNION�ṹ ���� */
#define ABB_BIST_RPT_19_ADDR                          (ABB_BASE_ADDR + 0x1D)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����Q·������ϱ���8bit���޷�������
   UNION�ṹ ���� */
#define ABB_BIST_RPT_20_ADDR                          (ABB_BASE_ADDR + 0x1E)

/* �Ĵ���˵����BIST�����׼�Ĵ���
 bit[7:6]    ����
 bit[5:0]    BIST DC������޸�6bit���з�������
   UNION�ṹ:  ABB_BIST_CFG_6_UNION */
#define ABB_BIST_CFG_6_ADDR                           (ABB_BASE_ADDR + 0x1F)

/* �Ĵ���˵����BIST�����׼�Ĵ���
   ��      ����BIST DC������޵�8bit���з�������
   UNION�ṹ ���� */
#define ABB_BIST_CFG_7_ADDR                           (ABB_BASE_ADDR + 0x20)

/* �Ĵ���˵����BIST�����׼�Ĵ���
 bit[7:6]    ����
 bit[5:0]    BIST DC������޸�6bit���з�������
   UNION�ṹ:  ABB_BIST_CFG_8_UNION */
#define ABB_BIST_CFG_8_ADDR                           (ABB_BASE_ADDR + 0x21)

/* �Ĵ���˵����BIST�����׼�Ĵ���
   ��      ����BIST DC������޵�8bit���з�������
   UNION�ṹ ���� */
#define ABB_BIST_CFG_9_ADDR                           (ABB_BASE_ADDR + 0x22)

/* �Ĵ���˵����BIST�����׼�Ĵ���
   ��      ����BIST gain mismatch������ޣ��޷�������
   UNION�ṹ ���� */
#define ABB_BIST_CFG_10_ADDR                          (ABB_BASE_ADDR + 0x23)

/* �Ĵ���˵����BIST�����׼�Ĵ���
   ��      ����BIST gain mismatch������ޣ��޷�������
   UNION�ṹ ���� */
#define ABB_BIST_CFG_11_ADDR                          (ABB_BASE_ADDR + 0x24)

/* �Ĵ���˵����BIST�����׼�Ĵ���
   ��      ����BIST gain error������ޣ��޷�������
   UNION�ṹ ���� */
#define ABB_BIST_CFG_12_ADDR                          (ABB_BASE_ADDR + 0x25)

/* �Ĵ���˵����BIST�����׼�Ĵ���
   ��      ����BIST gain error������ޣ��޷�������
   UNION�ṹ ���� */
#define ABB_BIST_CFG_13_ADDR                          (ABB_BASE_ADDR + 0x26)

/* �Ĵ���˵����BIST SNDR 2Gģʽ���ֵ
   ��      ����BIST 2Gģʽ SNDR���ֵ[7:0]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_2G_0_ADDR                       (ABB_BASE_ADDR + 0x27)

/* �Ĵ���˵����BIST SNDR 2Gģʽ���ֵ
   ��      ����BIST 2Gģʽ SNDR���ֵ[15:8]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_2G_1_ADDR                       (ABB_BASE_ADDR + 0x28)

/* �Ĵ���˵����BIST SNDR 2Gģʽ���ֵ
   ��      ����BIST 2Gģʽ SNDR���ֵ[23:16]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_2G_2_ADDR                       (ABB_BASE_ADDR + 0x29)

/* �Ĵ���˵����BIST SNDR 3Gģʽ���ֵ
   ��      ����BIST 3Gģʽ SNDR���ֵ[7:0]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_3G_0_ADDR                       (ABB_BASE_ADDR + 0x2A)

/* �Ĵ���˵����BIST SNDR 3Gģʽ���ֵ
   ��      ����BIST 3Gģʽ SNDR���ֵ[15:8]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_3G_1_ADDR                       (ABB_BASE_ADDR + 0x2B)

/* �Ĵ���˵����BIST SNDR 3Gģʽ���ֵ
   ��      ����BIST 3Gģʽ SNDR���ֵ[23:16]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_3G_2_ADDR                       (ABB_BASE_ADDR + 0x2C)

/* �Ĵ���˵����BIST SNDR TDSģʽ���ֵ
   ��      ����BIST TDSģʽ SNDR���ֵ[7:0]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_TDS_0_ADDR                      (ABB_BASE_ADDR + 0x2D)

/* �Ĵ���˵����BIST SNDR TDSģʽ���ֵ
   ��      ����BIST TDSģʽ SNDR���ֵ[15:8]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_TDS_1_ADDR                      (ABB_BASE_ADDR + 0x2E)

/* �Ĵ���˵����BIST SNDR TDSģʽ���ֵ
   ��      ����BIST TDSģʽ SNDR���ֵ[23:16]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_TDS_2_ADDR                      (ABB_BASE_ADDR + 0x2F)

/* �Ĵ���˵����BIST SNDR 4Gģʽ���ֵ
   ��      ����BIST 4Gģʽ SNDR���ֵ[7:0]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_4G_0_ADDR                       (ABB_BASE_ADDR + 0x30)

/* �Ĵ���˵����BIST SNDR 4Gģʽ���ֵ
   ��      ����BIST 4Gģʽ SNDR���ֵ[15:8]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_4G_1_ADDR                       (ABB_BASE_ADDR + 0x31)

/* �Ĵ���˵����BIST SNDR 4Gģʽ���ֵ
   ��      ����BIST 4Gģʽ SNDR���ֵ[23:16]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_4G_2_ADDR                       (ABB_BASE_ADDR + 0x32)

/* �Ĵ���˵����BIST SNDR CDMAģʽ���ֵ
   ��      ����BIST CDMAģʽ SNDR���ֵ[7:0]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_CDMA_0_ADDR                     (ABB_BASE_ADDR + 0x33)

/* �Ĵ���˵����BIST SNDR CDMAģʽ���ֵ
   ��      ����BIST CDMAģʽ SNDR���ֵ[15:8]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_CDMA_1_ADDR                     (ABB_BASE_ADDR + 0x34)

/* �Ĵ���˵����BIST SNDR CDMAģʽ���ֵ
   ��      ����BIST CDMAģʽ SNDR���ֵ[23:16]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_CDMA_2_ADDR                     (ABB_BASE_ADDR + 0x35)

/* �Ĵ���˵����BIST SNDR CAģʽ���ֵ
   ��      ����BIST CAģʽ SNDR���ֵ[7:0]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_CA_0_ADDR                       (ABB_BASE_ADDR + 0x36)

/* �Ĵ���˵����BIST SNDR CAģʽ���ֵ
   ��      ����BIST CAģʽ SNDR���ֵ[15:8]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_CA_1_ADDR                       (ABB_BASE_ADDR + 0x37)

/* �Ĵ���˵����BIST SNDR CAģʽ���ֵ
   ��      ����BIST CAģʽ SNDR���ֵ[23:16]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_CA_2_ADDR                       (ABB_BASE_ADDR + 0x38)

/* �Ĵ���˵����BIST SNDR ET0ģʽ���ֵ
   ��      ����BIST ET0ģʽ SNDR���ֵ[7:0]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_ET0_0_ADDR                      (ABB_BASE_ADDR + 0x39)

/* �Ĵ���˵����BIST SNDR ET0ģʽ���ֵ
   ��      ����BIST ET0ģʽ SNDR���ֵ[15:8]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_ET0_1_ADDR                      (ABB_BASE_ADDR + 0x3A)

/* �Ĵ���˵����BIST SNDR ET0ģʽ���ֵ
   ��      ����BIST ET0ģʽ SNDR���ֵ[23:16]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_ET0_2_ADDR                      (ABB_BASE_ADDR + 0x3B)

/* �Ĵ���˵����BIST SNDR ET1ģʽ���ֵ
   ��      ����BIST ET1ģʽ SNDR���ֵ[7:0]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_ET1_0_ADDR                      (ABB_BASE_ADDR + 0x3C)

/* �Ĵ���˵����BIST SNDR ET1ģʽ���ֵ
   ��      ����BIST ET1ģʽ SNDR���ֵ[15:8]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_ET1_1_ADDR                      (ABB_BASE_ADDR + 0x3D)

/* �Ĵ���˵����BIST SNDR ET1ģʽ���ֵ
   ��      ����BIST ET1ģʽ SNDR���ֵ[23:16]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_ET1_2_ADDR                      (ABB_BASE_ADDR + 0x3E)

/* �Ĵ���˵����BIST_TCXO_SEL
 bit[7:2]    ����
 bit[1:0]    bist_tcxo_sel:
             0:19.2M
             1:20.48M
             2:30.72M
             3:38.74M
   UNION�ṹ:  ABB_BIST_TCXO_SEL_UNION */
#define ABB_BIST_TCXO_SEL_ADDR                        (ABB_BASE_ADDR + 0x3F)

/* �Ĵ���˵����ABB�汾�Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH0_VERSION_ADDR                          (ABB_BASE_ADDR + 0x40)

/* �Ĵ���˵����ABB�汾�Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH1_VERSION_ADDR                          (ABB_BASE_ADDR + 0xA0)



/***======================================================================***
                     (2/4) register_define_abb_tx
 ***======================================================================***/
/* �Ĵ���˵����TX IDLEģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G
             010��4G
             011��TDS
             100��CDMA
             101��CA
             Others��Reserved
 bit[4:2]    TXͨ��CIC�˲����������ʿ��ƣ�
                  2G,     3G,     4G,      TDS,      CDMA,    CA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz,
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_IDLE_DIG_1_UNION */
#define ABB_TX_IDLE_DIG_1_ADDR                        (ABB_BASE_ADDR + 0x200)

/* �Ĵ���˵����TX IDLEģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ
             1��ʹ��DWAģʽ(Ĭ��)
 bit[4]      TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
             0����ʹ��
             1��ʹ��
 bit[3:2]    TXͨ��DEM constϵ����
             0��0(Ĭ��)
             1��2
             2��4
             3��6
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_IDLE_DIG_2_UNION */
#define ABB_TX_IDLE_DIG_2_ADDR                        (ABB_BASE_ADDR + 0x201)

/* �Ĵ���˵����TX IDLEģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:4]    ����
 bit[3:2]    TXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11������ϵ����
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      ����
   UNION�ṹ:  ABB_TX_IDLE_DIG_3_UNION */
#define ABB_TX_IDLE_DIG_3_ADDR                        (ABB_BASE_ADDR + 0x202)

/* �Ĵ���˵����TX 2Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G
             010��4G
             011��TDS
             100��CDMA
             101��CA
             Others��Reserved
 bit[4:2]    TXͨ��CIC�˲����������ʿ��ƣ�
                  2G,     3G,     4G,      TDS,      CDMA,    CA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz,
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate(Ĭ��)
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_2G_DIG_1_UNION */
#define ABB_TX_2G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x203)

/* �Ĵ���˵����TX 2Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ
             1��ʹ��DWAģʽ (Ĭ��)
 bit[4]      TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
             0����ʹ��
             1��ʹ��
 bit[3:2]    TXͨ��DEM constϵ����
             0��0(Ĭ��)
             1��2
             2��4
             3��6
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_2G_DIG_2_UNION */
#define ABB_TX_2G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x204)

/* �Ĵ���˵����TX 2Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:4]    ����
 bit[3:2]    TXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11������ϵ����
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      ����
   UNION�ṹ:  ABB_TX_2G_DIG_3_UNION */
#define ABB_TX_2G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x205)

/* �Ĵ���˵����TX Cģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G
             010��4G
             011��TDS
             100��CDMA
             101��CA
             Others��Reserved
 bit[4:2]    TXͨ��CIC�˲����������ʿ��ƣ�
                  2G,     3G,     4G,      TDS,      CDMA,    CA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz,
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate(Ĭ��)
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_C_DIG_1_UNION */
#define ABB_TX_C_DIG_1_ADDR                           (ABB_BASE_ADDR + 0x206)

/* �Ĵ���˵����TX Cģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ
             1��ʹ��DWAģʽ (Ĭ��)
 bit[4]      TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
             0����ʹ��
             1��ʹ��
 bit[3:2]    TXͨ��DEM constϵ����
             0��0(Ĭ��)
             1��2
             2��4
             3��6
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_C_DIG_2_UNION */
#define ABB_TX_C_DIG_2_ADDR                           (ABB_BASE_ADDR + 0x207)

/* �Ĵ���˵����TX Cģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:4]    ����
 bit[3:2]    TXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11������ϵ����
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      ����
   UNION�ṹ:  ABB_TX_C_DIG_3_UNION */
#define ABB_TX_C_DIG_3_ADDR                           (ABB_BASE_ADDR + 0x208)

/* �Ĵ���˵����TX TDSģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G
             010��4G
             011��TDS
             100��CDMA
             101��CA
             Others��Reserved
 bit[4:2]    TXͨ��CIC�˲����������ʿ��ƣ�
                  2G,     3G,     4G,      TDS,      CDMA,    CA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz,
 bit[1]      TXͨ������˲�����bypass�ź�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_TDS_DIG_1_UNION */
#define ABB_TX_TDS_DIG_1_ADDR                         (ABB_BASE_ADDR + 0x209)

/* �Ĵ���˵����TX TDSģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ
             1��ʹ��DWAģʽ(Ĭ��)
 bit[4]      TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
             0����ʹ��
             1��ʹ��
 bit[3:2]    TXͨ��DEM constϵ����
             0��0(Ĭ��)
             1��2
             2��4
             3��6
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_TDS_DIG_2_UNION */
#define ABB_TX_TDS_DIG_2_ADDR                         (ABB_BASE_ADDR + 0x20A)

/* �Ĵ���˵����TX TDSģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:4]    ����
 bit[3:2]    TXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11������ϵ����
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      ����
   UNION�ṹ:  ABB_TX_TDS_DIG_3_UNION */
#define ABB_TX_TDS_DIG_3_ADDR                         (ABB_BASE_ADDR + 0x20B)

/* �Ĵ���˵����TX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G
             010��4G
             011��TDS
             100��CDMA
             101��CA
             Others��Reserved
 bit[4:2]    TXͨ��CIC�˲����������ʿ��ƣ�
                  2G,     3G,     4G,      TDS,      CDMA,    CA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz,
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_CH0_TX_3G_DIG_1_UNION */
#define ABB_CH0_TX_3G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x210)

/* �Ĵ���˵����TX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ
             1��ʹ��DWAģʽ(Ĭ��)
 bit[4]      TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
             0����ʹ��
             1��ʹ��
 bit[3:2]    TXͨ��DEM constϵ����
             0��0(Ĭ��)
             1��2
             2��4
             3��6
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_CH0_TX_3G_DIG_2_UNION */
#define ABB_CH0_TX_3G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x211)

/* �Ĵ���˵����TX 3Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:4]    ����
 bit[3:2]    TXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11������ϵ����
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      ����
   UNION�ṹ:  ABB_CH0_TX_3G_DIG_3_UNION */
#define ABB_CH0_TX_3G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x212)

/* �Ĵ���˵����TX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G
             010��4G
             011��TDS
             100��CDMA
             101��CA
             Others��Reserved
 bit[4:2]    TXͨ��CIC�˲����������ʿ��ƣ�
                  2G,     3G,     4G,      TDS,      CDMA,    CA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz,
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_CH1_TX_3G_DIG_1_UNION */
#define ABB_CH1_TX_3G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x213)

/* �Ĵ���˵����TX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ
             1��ʹ��DWAģʽ(Ĭ��)
 bit[4]      TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
             0����ʹ��
             1��ʹ��
 bit[3:2]    TXͨ��DEM constϵ����
             0��0(Ĭ��)
             1��2
             2��4
             3��6
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_CH1_TX_3G_DIG_2_UNION */
#define ABB_CH1_TX_3G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x214)

/* �Ĵ���˵����TX 3Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:4]    ����
 bit[3:2]    TXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11������ϵ����
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      ����
   UNION�ṹ:  ABB_CH1_TX_3G_DIG_3_UNION */
#define ABB_CH1_TX_3G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x215)

/* �Ĵ���˵����TX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G
             010��4G
             011��TDS
             100��CDMA
             101��CA
             Others��Reserved
 bit[4:2]    TXͨ��CIC�˲����������ʿ��ƣ�
                  2G,     3G,     4G,      TDS,      CDMA,    CA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz,
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_CH0_TX_4G_DIG_1_UNION */
#define ABB_CH0_TX_4G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x228)

/* �Ĵ���˵����TX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ
             1��ʹ��DWAģʽ(Ĭ��)
 bit[4]      TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
             0����ʹ��
             1��ʹ��
 bit[3:2]    TXͨ��DEM constϵ����
             0��0(Ĭ��)
             1��2
             2��4
             3��6
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_CH0_TX_4G_DIG_2_UNION */
#define ABB_CH0_TX_4G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x229)

/* �Ĵ���˵����TX 4Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:4]    ����
 bit[3:2]    TXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11������ϵ����
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      ����
   UNION�ṹ:  ABB_CH0_TX_4G_DIG_3_UNION */
#define ABB_CH0_TX_4G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x22A)

/* �Ĵ���˵����TX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    TXͨ��ģʽ���ƣ�
             000��2G(Ĭ��)
             001��3G
             010��4G
             011��TDS
             100��CDMA
             101��CA
             Others��Reserved
 bit[4:2]    TXͨ��CIC�˲����������ʿ��ƣ�
                  2G,     3G,     4G,      TDS,      CDMA,    CA
                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(Ĭ��)
             1��2.16MHz,15.36MHz,30.72MHz,
 bit[1]      TXͨ������˲���bypass���ƣ�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      TXͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_CH1_TX_4G_DIG_1_UNION */
#define ABB_CH1_TX_4G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x22B)

/* �Ĵ���˵����TX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      TXͨ��DEM MSB bypass��
             0��DEM MSB��(Ĭ��)
             1��DEM MSB bypass
 bit[6]      TXͨ��DEM LSB bypass��
             0��DEM LSB ��(Ĭ��)
             1��DEM LSB bypass
 bit[5]      TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ
             1��ʹ��DWAģʽ(Ĭ��)
 bit[4]      TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
             0����ʹ��
             1��ʹ��
 bit[3:2]    TXͨ��DEM constϵ����
             0��0(Ĭ��)
             1��2
             2��4
             3��6
 bit[1]      TXͨ��I·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر�
 bit[0]      TXͨ��Q·CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_CH1_TX_4G_DIG_2_UNION */
#define ABB_CH1_TX_4G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x22C)

/* �Ĵ���˵����TX 4Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:4]    ����
 bit[3:2]    TXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11������ϵ����
 bit[1]      TXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[0]      ����
   UNION�ṹ:  ABB_CH1_TX_4G_DIG_3_UNION */
#define ABB_CH1_TX_4G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x22D)

/* �Ĵ���˵��������ģʽ�Ĵ�����
 bit[7:6]    ����
 bit[5:4]    TX�㷨���أ�����ͨ��ѡ��
             0������CH0 RX
             1������CH1 RX
             2������CH2 RX
             default������CH0 RX
 bit[3:1]    ����
 bit[0]      ���ֲ���TXͨ����λ�źţ�
             0������λ(Ĭ��)
             1����λ
   UNION�ṹ:  ABB_CH0_TX_TESTMODE_UNION */
#define ABB_CH0_TX_TESTMODE_ADDR                      (ABB_BASE_ADDR + 0x240)

/* �Ĵ���˵����SINE���ͼĴ�����
 bit[7:4]    ���Ҳ�����Ƶ�ʿ��ƣ���λ(freq of tx_hb_clk)/32�����䷶ΧΪ1~f
 bit[3:2]    ���Ҳ����ͷ��ȿ���
             00��������
             01��3/4����
             10��1/2����
             11��1/4����
 bit[1]      ����
 bit[0]      ch0���Ҳ�����ʹ��
             0��������
             1������
   UNION�ṹ:  ABB_CH0_SINE_GENERATE_UNION */
#define ABB_CH0_SINE_GENERATE_ADDR                    (ABB_BASE_ADDR + 0x241)

/* �Ĵ���˵����TXͨ��offset�Ĵ�����
   ��      ����TXͨ��I·dc offset����
   UNION�ṹ ���� */
#define ABB_CH0_TX_I_OFFSET_ADDR                      (ABB_BASE_ADDR + 0x242)

/* �Ĵ���˵����TXͨ��offset�Ĵ�����
   ��      ����TXͨ��Q·dc offset����
   UNION�ṹ ���� */
#define ABB_CH0_TX_Q_OFFSET_ADDR                      (ABB_BASE_ADDR + 0x243)

/* �Ĵ���˵����TXͨ������ϵ���Ĵ�����
 bit[7:6]    ����
 bit[5:0]    TX�����˲���ϵ��C0,6bit�з�����
   UNION�ṹ:  ABB_CH0_TX_COEF1_UNION */
#define ABB_CH0_TX_COEF1_ADDR                         (ABB_BASE_ADDR + 0x244)

/* �Ĵ���˵����TXͨ������ϵ���Ĵ�����
   ��      ����TX�����˲���ϵ��C1,8bit�з�����
   UNION�ṹ ���� */
#define ABB_CH0_TX_COEF2_ADDR                         (ABB_BASE_ADDR + 0x245)

/* �Ĵ���˵����TXͨ������ϵ���Ĵ�����
   ��      ����TX�����˲���ϵ��C2��8λ,10bit�з�����
   UNION�ṹ ���� */
#define ABB_CH0_TX_COEF3_ADDR                         (ABB_BASE_ADDR + 0x246)

/* �Ĵ���˵����TXͨ������ϵ���Ĵ�����
 bit[7:2]    ����
 bit[1:0]    TX�����˲���ϵ��C2��2λ,10bit�з�����
   UNION�ṹ:  ABB_CH0_TX_COEF4_UNION */
#define ABB_CH0_TX_COEF4_ADDR                         (ABB_BASE_ADDR + 0x247)

/* �Ĵ���˵����TXͨ������ϵ���Ĵ�����
   ��      ����TX�����˲���ϵ��C3��8λ,10bit�޷�����
   UNION�ṹ ���� */
#define ABB_CH0_TX_COEF5_ADDR                         (ABB_BASE_ADDR + 0x248)

/* �Ĵ���˵����TXͨ������ϵ���Ĵ�����
 bit[7:2]    ����
 bit[1:0]    TX�����˲���ϵ��C3��2λ,10bit�޷�����
   UNION�ṹ:  ABB_CH0_TX_COEF6_UNION */
#define ABB_CH0_TX_COEF6_ADDR                         (ABB_BASE_ADDR + 0x249)

/* �Ĵ���˵����TX���ֹ���ģʽ�ϱ��Ĵ�����
   ��      ����[7:5]��TXͨ��ģʽ���ƣ�
                    000��2G(Ĭ��)
                    001��3G
                    010��4G
                    011��TDS
                    100��CDMA
                    Others��Reserved
            [4:2]��tx rate�ϱ�
            [1]  ��tx_hb_bp�ϱ�
            [0]  ��tx_comp_hp�ϱ�
   UNION�ṹ ���� */
#define ABB_CH0_TX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x24A)

/* �Ĵ���˵����TX���ֹ���״̬�ϱ��Ĵ�����
   ��      ����[7:4]������
            [3]   ��TXͨ��FIFOд��
            [2]   ��TXͨ��FIFO����
            [1]   ��TXͨ�����ָʾ
            [0]   ��TXͨ�����ݷ�תָʾ
   UNION�ṹ ���� */
#define ABB_CH0_TX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x24B)

/* �Ĵ���˵�������ֵ��ԼĴ�����
 bit[7]      ����
 bit[6]      TX SDģ������������·ʹ�ܣ�
             0��������������·��
             1������������·��Ĭ�ϣ���
 bit[5]      ����
 bit[4]      TXͨ��SDM Dither���ƣ�
             0����ʹ��
             1��ʹ��
 bit[3:2]    TX DEM�����������޷���λ��
             00��0.8125
             01��0.796875(Ĭ��)
             10��0.765625
             11��0.75
 bit[1]      TXͨ��DEMУ׼����ģʽ
             0����������
             1��У׼̬��DEM���Ϊdem_code_man
 bit[0]      TXͨ��SDMģ���쳣ʱ��λ����
             0��ֻ��λSDMģ��
             1����λ����TXͨ��
   UNION�ṹ:  ABB_CH0_TX_REG_DEBUG_DIG0_UNION */
#define ABB_CH0_TX_REG_DEBUG_DIG0_ADDR                (ABB_BASE_ADDR + 0x24C)

/* �Ĵ���˵�������ֵ��ԼĴ�����
   ��      ����TXͨ��DEM����ֹ����ã�ֻ��DEMУ׼̬��������,��λ
   UNION�ṹ ���� */
#define ABB_CH0_TX_REG_DEBUG_DIG1_ADDR                (ABB_BASE_ADDR + 0x24D)

/* �Ĵ���˵�������ֵ��ԼĴ�����
   ��      ����TXͨ��DEM����ֹ����ã�ֻ��DEMУ׼̬��������,��λ
   UNION�ṹ ���� */
#define ABB_CH0_TX_REG_DEBUG_DIG2_ADDR                (ABB_BASE_ADDR + 0x24E)

/* �Ĵ���˵�������ֵ��ԼĴ�����
   ��      ����TXͨ��SDMģ���쳣��λ����
   UNION�ṹ ���� */
#define ABB_CH0_TX_REG_DEBUG_DIG3_ADDR                (ABB_BASE_ADDR + 0x24F)

/* �Ĵ���˵�������ֵ��ԼĴ�����
 bit[7]      bit[7]��ģʽ�л���λ��������ʹ��
             0����ʹ��
             1��ʹ��
 bit[6:4]    ģʽ�л���λ��������ֵ����λΪ8 cycles
 bit[3:1]    ����
 bit[0]      TX��Ƶ��ʹ��bypass����
             0����bypass
             1��bypass
   UNION�ṹ:  ABB_CH0_TX_REG_DEBUG_DIG4_UNION */
#define ABB_CH0_TX_REG_DEBUG_DIG4_ADDR                (ABB_BASE_ADDR + 0x250)

/* �Ĵ���˵�����߿�ǿ������ʹ�ܡ�
 bit[7:5]    ����
 bit[4]      TXͨ��ǿ���߿�
 bit[3:1]    ����
 bit[0]      TXͨ���߿�ѡ��ǿ��ʹ��
             0��ѡ���߿�ʹ��
             1��ѡ��ǿ��ʹ��
   UNION�ṹ:  ABB_CH0_TX_LINE_SEL_UNION */
#define ABB_CH0_TX_LINE_SEL_ADDR                      (ABB_BASE_ADDR + 0x251)

/* �Ĵ���˵����ģʽ�߿�ǿ�����á�
 bit[7:4]    ����
 bit[3]      �߿��ź�CH0_TX_LINE_CTRL_MODEǿ������ʹ��
 bit[2:0]    �߿��ź�CH0_TX_LINE_CTRL_MODEǿ������ֵ
             0��IDLE
             1��Gģ
             2��Wģ
             3��LTEģ
             4��TDSģ
             5��Xģʽ
   UNION�ṹ:  ABB_CH0_TX_LINE_CFG_UNION */
#define ABB_CH0_TX_LINE_CFG_ADDR                      (ABB_BASE_ADDR + 0x252)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
 bit[7:3]    ����
 bit[2]      CH0_TX_EN�߿�״̬�ϱ�
 bit[1:0]    ����
   UNION�ṹ:  ABB_CH0_TX_LINE_RPT0_UNION */
#define ABB_CH0_TX_LINE_RPT0_ADDR                     (ABB_BASE_ADDR + 0x253)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
 bit[7:3]    ����
 bit[2:0]    CH0 TX_LINE_CTRL_MODE״̬�ϱ�
             0��IDLE
             1��Gģ
             2��Wģ
             3��LTEģ
             4��TDSģ
             5��Xģ
             others��IDLE
   UNION�ṹ:  ABB_CH0_TX_LINE_RPT1_UNION */
#define ABB_CH0_TX_LINE_RPT1_ADDR                     (ABB_BASE_ADDR + 0x254)

/* �Ĵ���˵��������ģʽ�Ĵ�����
 bit[7:6]    ����
 bit[5:4]    TX�㷨���أ�����ͨ��ѡ��
             0������CH0 RX
             1������CH1 RX
             2������CH2 RX
             default������CH0 RX
 bit[3:1]    ����
 bit[0]      ���ֲ���TXͨ����λ�źţ�
             0������λ(Ĭ��)
             1����λ
   UNION�ṹ:  ABB_CH1_TX_TESTMODE_UNION */
#define ABB_CH1_TX_TESTMODE_ADDR                      (ABB_BASE_ADDR + 0x260)

/* �Ĵ���˵����SINE���ͼĴ�����
 bit[7:4]    ���Ҳ�����Ƶ�ʿ��ƣ���λ(freq of tx_hb_clk)/32�����䷶ΧΪ1~f
 bit[3:2]    ���Ҳ����ͷ��ȿ���
             00��������
             01��3/4����
             10��1/2����
             11��1/4����
 bit[1]      ����
 bit[0]      ch0���Ҳ�����ʹ��
             0��������
             1������
   UNION�ṹ:  ABB_CH1_SINE_GENERATE_UNION */
#define ABB_CH1_SINE_GENERATE_ADDR                    (ABB_BASE_ADDR + 0x261)

/* �Ĵ���˵����TXͨ��offset�Ĵ�����
   ��      ����TXͨ��I·dc offset����
   UNION�ṹ ���� */
#define ABB_CH1_TX_I_OFFSET_ADDR                      (ABB_BASE_ADDR + 0x262)

/* �Ĵ���˵����TXͨ��offset�Ĵ�����
   ��      ����TXͨ��Q·dc offset����
   UNION�ṹ ���� */
#define ABB_CH1_TX_Q_OFFSET_ADDR                      (ABB_BASE_ADDR + 0x263)

/* �Ĵ���˵����TXͨ������ϵ���Ĵ�����
 bit[7:6]    ����
 bit[5:0]    TX�����˲���ϵ��C0,6bit�з�����
   UNION�ṹ:  ABB_CH1_TX_COEF1_UNION */
#define ABB_CH1_TX_COEF1_ADDR                         (ABB_BASE_ADDR + 0x264)

/* �Ĵ���˵����TXͨ������ϵ���Ĵ�����
   ��      ����TX�����˲���ϵ��C1,8bit�з�����
   UNION�ṹ ���� */
#define ABB_CH1_TX_COEF2_ADDR                         (ABB_BASE_ADDR + 0x265)

/* �Ĵ���˵����TXͨ������ϵ���Ĵ�����
   ��      ����TX�����˲���ϵ��C2��8λ,10bit�з�����
   UNION�ṹ ���� */
#define ABB_CH1_TX_COEF3_ADDR                         (ABB_BASE_ADDR + 0x266)

/* �Ĵ���˵����TXͨ������ϵ���Ĵ�����
 bit[7:2]    ����
 bit[1:0]    TX�����˲���ϵ��C2��2λ,10bit�з�����
   UNION�ṹ:  ABB_CH1_TX_COEF4_UNION */
#define ABB_CH1_TX_COEF4_ADDR                         (ABB_BASE_ADDR + 0x267)

/* �Ĵ���˵����TXͨ������ϵ���Ĵ�����
   ��      ����TX�����˲���ϵ��C3��8λ,10bit�޷�����
   UNION�ṹ ���� */
#define ABB_CH1_TX_COEF5_ADDR                         (ABB_BASE_ADDR + 0x268)

/* �Ĵ���˵����TXͨ������ϵ���Ĵ�����
 bit[7:2]    ����
 bit[1:0]    TX�����˲���ϵ��C3��2λ,10bit�޷�����
   UNION�ṹ:  ABB_CH1_TX_COEF6_UNION */
#define ABB_CH1_TX_COEF6_ADDR                         (ABB_BASE_ADDR + 0x269)

/* �Ĵ���˵����TX���ֹ���ģʽ�ϱ��Ĵ�����
   ��      ����[7:5]��TXͨ��ģʽ���ƣ�
                    000��2G(Ĭ��)
                    001��3G
                    010��4G
                    011��TDS
                    100��CDMA
                    Others��Reserved
            [4:2]��tx rate�ϱ�
            [1]  ��tx_hb_bp�ϱ�
            [0]  ��tx_comp_hp�ϱ�
   UNION�ṹ ���� */
#define ABB_CH1_TX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x26A)

/* �Ĵ���˵����TX���ֹ���״̬�ϱ��Ĵ�����
   ��      ����[7:4]������
            [3]   ��TXͨ��FIFOд��
            [2]   ��TXͨ��FIFO����
            [1]   ��TXͨ�����ָʾ
            [0]   ��TXͨ�����ݷ�תָʾ
   UNION�ṹ ���� */
#define ABB_CH1_TX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x26B)

/* �Ĵ���˵�������ֵ��ԼĴ�����
 bit[7]      ����
 bit[6]      TX SDģ������������·ʹ�ܣ�
             0��������������·��
             1������������·��Ĭ�ϣ���
 bit[5]      ����
 bit[4]      TXͨ��SDM Dither���ƣ�
             0����ʹ��
             1��ʹ��
 bit[3:2]    TX DEM�����������޷���λ��
             00��0.8125
             01��0.796875(Ĭ��)
             10��0.765625
             11��0.75
 bit[1]      TXͨ��DEMУ׼����ģʽ
             0����������
             1��У׼̬��DEM���Ϊdem_code_man
 bit[0]      TXͨ��SDMģ���쳣ʱ��λ����
             0��ֻ��λSDMģ��
             1����λ����TXͨ��
   UNION�ṹ:  ABB_CH1_TX_REG_DEBUG_DIG0_UNION */
#define ABB_CH1_TX_REG_DEBUG_DIG0_ADDR                (ABB_BASE_ADDR + 0x26C)

/* �Ĵ���˵�������ֵ��ԼĴ�����
   ��      ����TXͨ��DEM����ֹ����ã�ֻ��DEMУ׼̬��������,��λ
   UNION�ṹ ���� */
#define ABB_CH1_TX_REG_DEBUG_DIG1_ADDR                (ABB_BASE_ADDR + 0x26D)

/* �Ĵ���˵�������ֵ��ԼĴ�����
   ��      ����TXͨ��DEM����ֹ����ã�ֻ��DEMУ׼̬��������,��λ
   UNION�ṹ ���� */
#define ABB_CH1_TX_REG_DEBUG_DIG2_ADDR                (ABB_BASE_ADDR + 0x26E)

/* �Ĵ���˵�������ֵ��ԼĴ�����
   ��      ����TXͨ��SDMģ���쳣��λ����
   UNION�ṹ ���� */
#define ABB_CH1_TX_REG_DEBUG_DIG3_ADDR                (ABB_BASE_ADDR + 0x26F)

/* �Ĵ���˵�������ֵ��ԼĴ�����
 bit[7]      bit[7]��ģʽ�л���λ��������ʹ��
             0����ʹ��
             1��ʹ��
 bit[6:4]    ģʽ�л���λ��������ֵ����λΪ8 cycles
 bit[3:1]    ����
 bit[0]      TX��Ƶ��ʹ��bypass����
             0����bypass
             1��bypass
   UNION�ṹ:  ABB_CH1_TX_REG_DEBUG_DIG4_UNION */
#define ABB_CH1_TX_REG_DEBUG_DIG4_ADDR                (ABB_BASE_ADDR + 0x270)

/* �Ĵ���˵�����߿�ǿ������ʹ�ܡ�
 bit[7:5]    ����
 bit[4]      TXͨ��ǿ���߿�
 bit[3:1]    ����
 bit[0]      TXͨ���߿�ѡ��ǿ��ʹ��
             0��ѡ���߿�ʹ��
             1��ѡ��ǿ��ʹ��
   UNION�ṹ:  ABB_CH1_TX_LINE_SEL_UNION */
#define ABB_CH1_TX_LINE_SEL_ADDR                      (ABB_BASE_ADDR + 0x271)

/* �Ĵ���˵����ģʽ�߿�ǿ�����á�
 bit[7:4]    ����
 bit[3]      �߿��ź�CH1_LINE_CTRL_MODEǿ������ʹ��
 bit[2:0]    �߿��ź�CH1_TX_LINE_CTRL_MODEǿ������ֵ
             0��IDLE
             1��Gģ
             2��Wģ
             3��LTEģ
             4��TDSģ
             5��Xģʽ
   UNION�ṹ:  ABB_CH1_TX_LINE_CFG_UNION */
#define ABB_CH1_TX_LINE_CFG_ADDR                      (ABB_BASE_ADDR + 0x272)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
 bit[7:3]    ����
 bit[2]      CH1_TX_EN�߿�״̬�ϱ�
 bit[1:0]    ����
   UNION�ṹ:  ABB_CH1_TX_LINE_RPT0_UNION */
#define ABB_CH1_TX_LINE_RPT0_ADDR                     (ABB_BASE_ADDR + 0x273)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
 bit[7:3]    ����
 bit[2:0]    CH1 TX_LINE_CTRL_MODE״̬�ϱ�
             0��IDLE
             1��Gģ
             2��Wģ
             3��LTEģ
             4��TDSģ
             5��Xģ
             others��IDLE
   UNION�ṹ:  ABB_CH1_TX_LINE_RPT1_UNION */
#define ABB_CH1_TX_LINE_RPT1_ADDR                     (ABB_BASE_ADDR + 0x274)



/***======================================================================***
                     (3/4) register_define_abb_rx
 ***======================================================================***/
/* �Ĵ���˵����RX IDLEģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6:4]    RXͨ��ģʽ���ƣ�
             000��2G_A
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             110��CA
             111��2G_B(Ĭ��)
 bit[3:1]    ����
 bit[0]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
   UNION�ṹ:  ABB_RX_IDLE_DIG_1_UNION */
#define ABB_RX_IDLE_DIG_1_ADDR                        (ABB_BASE_ADDR + 0x400)

/* �Ĵ���˵����RX IDLEģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6]      RXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[5]      RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
             0������
             1������
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
#define ABB_RX_IDLE_DIG_2_ADDR                        (ABB_BASE_ADDR + 0x401)

/* �Ĵ���˵����RX IDLEģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6:4]    RXͨ�������˲�������ϵ���̶����ƣ�
             000��ϵ�����̶����ɼĴ������ã�
             001���̶�ϵ��1��
             010���̶�ϵ��2��
             011���̶�ϵ��3��
             100���̶�ϵ��4��

 bit[3:2]    ����
 bit[1:0]    W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
             2'b00��2560chip��(WģĬ��)
             2'b01��512chip��
             2'b10��1024chip��(XģĬ��)
             2'b11��2048chip��
   UNION�ṹ:  ABB_RX_IDLE_DIG_3_UNION */
#define ABB_RX_IDLE_DIG_3_ADDR                        (ABB_BASE_ADDR + 0x402)

/* �Ĵ���˵����RX 2Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6:4]    RXͨ��ģʽ���ƣ�
             000��2G_A
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             110��CA
             111��2G_B(Ĭ��)
 bit[3:1]    ����
 bit[0]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
   UNION�ṹ:  ABB_RX_2G_DIG_1_UNION */
#define ABB_RX_2G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x403)

/* �Ĵ���˵����RX 2Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6]      RXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[5]      RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
             0������
             1������
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
#define ABB_RX_2G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x404)

/* �Ĵ���˵����RX 2Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6:4]    RXͨ�������˲�������ϵ���̶����ƣ�
             000��ϵ�����̶����ɼĴ������ã�
             001���̶�ϵ��1��
             010���̶�ϵ��2��
             011���̶�ϵ��3��
             100���̶�ϵ��4��
             101���̶�ϵ��5��
             110���̶�ϵ��6��
             111���̶�ϵ��7��
 bit[3:2]    ����
 bit[1:0]    W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
             2'b00��2560chip��(WģĬ��)
             2'b01��512chip��
             2'b10��1024chip��(XģĬ��)
             2'b11��2048chip��
   UNION�ṹ:  ABB_RX_2G_DIG_3_UNION */
#define ABB_RX_2G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x405)

/* �Ĵ���˵����RX Cģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6:4]    RXͨ��ģʽ���ƣ�
             000��2G_A(Ĭ��)
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             110��CA
             111��2G_B
 bit[3:1]    ����
 bit[0]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
   UNION�ṹ:  ABB_RX_C_DIG_1_UNION */
#define ABB_RX_C_DIG_1_ADDR                           (ABB_BASE_ADDR + 0x406)

/* �Ĵ���˵����RX Cģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6]      RXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[5]      RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
             0������
             1������
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
   UNION�ṹ:  ABB_RX_C_DIG_2_UNION */
#define ABB_RX_C_DIG_2_ADDR                           (ABB_BASE_ADDR + 0x407)

/* �Ĵ���˵����RX Cģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6:4]    RXͨ�������˲�������ϵ���̶����ƣ�
             000��ϵ�����̶����ɼĴ������ã�
             001���̶�ϵ��1��
             010���̶�ϵ��2��
             011���̶�ϵ��3��
             100���̶�ϵ��4��
             101���̶�ϵ��5��
             110���̶�ϵ��6��
             111���̶�ϵ��7��
 bit[3:2]    ����
 bit[1:0]    W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
             2'b00��2560chip��(WģĬ��)
             2'b01��512chip��
             2'b10��1024chip��(XģĬ��)
             2'b11��2048chip��
   UNION�ṹ:  ABB_RX_C_DIG_3_UNION */
#define ABB_RX_C_DIG_3_ADDR                           (ABB_BASE_ADDR + 0x408)

/* �Ĵ���˵����RX TDSģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6:4]    RXͨ��ģʽ���ƣ�
             000��2G_A(Ĭ��)
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             110��CA
             111��2G_B
 bit[3:1]    ����
 bit[0]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
   UNION�ṹ:  ABB_RX_TDS_DIG_1_UNION */
#define ABB_RX_TDS_DIG_1_ADDR                         (ABB_BASE_ADDR + 0x409)

/* �Ĵ���˵����RX TDSģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6]      RXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[5]      RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
             0������
             1������
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
   UNION�ṹ:  ABB_RX_TDS_DIG_2_UNION */
#define ABB_RX_TDS_DIG_2_ADDR                         (ABB_BASE_ADDR + 0x40A)

/* �Ĵ���˵����RX TDSģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6:4]    RXͨ�������˲�������ϵ���̶����ƣ�
             000��ϵ�����̶����ɼĴ������ã�
             001���̶�ϵ��1��
             010���̶�ϵ��2��
             011���̶�ϵ��3��
             100���̶�ϵ��4��
             101���̶�ϵ��5��
             110���̶�ϵ��6��
             111���̶�ϵ��7��
 bit[3:2]    ����
 bit[1:0]    W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
             2'b00��2560chip��(WģĬ��)
             2'b01��512chip��
             2'b10��1024chip��(XģĬ��)
             2'b11��2048chip��
   UNION�ṹ:  ABB_RX_TDS_DIG_3_UNION */
#define ABB_RX_TDS_DIG_3_ADDR                         (ABB_BASE_ADDR + 0x40B)

/* �Ĵ���˵����RX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6:4]    RXͨ��ģʽ���ƣ�
             000��2G_A(Ĭ��)
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             110��CA
             111��2G_B
 bit[3:1]    ����
 bit[0]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
   UNION�ṹ:  ABB_CH0_RX_3G_DIG_1_UNION */
#define ABB_CH0_RX_3G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x410)

/* �Ĵ���˵����RX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6]      RXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[5]      RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
             0������
             1������
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
   UNION�ṹ:  ABB_CH0_RX_3G_DIG_2_UNION */
#define ABB_CH0_RX_3G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x411)

/* �Ĵ���˵����RX 3Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6:4]    RXͨ�������˲�������ϵ���̶����ƣ�
             000��ϵ�����̶����ɼĴ������ã�
             001���̶�ϵ��1��
             010���̶�ϵ��2��
             011���̶�ϵ��3��
             100���̶�ϵ��4��
             101���̶�ϵ��5��
             110���̶�ϵ��6��
             111���̶�ϵ��7��
 bit[3:2]    ����
 bit[1:0]    W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
             2'b00��2560chip��(WģĬ��)
             2'b01��512chip��
             2'b10��1024chip��(XģĬ��)
             2'b11��2048chip��
   UNION�ṹ:  ABB_CH0_RX_3G_DIG_3_UNION */
#define ABB_CH0_RX_3G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x412)

/* �Ĵ���˵����RX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6:4]    RXͨ��ģʽ���ƣ�
             000��2G_A(Ĭ��)
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             110��CA
             111��2G_B
 bit[3:1]    ����
 bit[0]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
   UNION�ṹ:  ABB_CH1_RX_3G_DIG_1_UNION */
#define ABB_CH1_RX_3G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x413)

/* �Ĵ���˵����RX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6]      RXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[5]      RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
             0������
             1������
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
   UNION�ṹ:  ABB_CH1_RX_3G_DIG_2_UNION */
#define ABB_CH1_RX_3G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x414)

/* �Ĵ���˵����RX 3Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6:4]    RXͨ�������˲�������ϵ���̶����ƣ�
             000��ϵ�����̶����ɼĴ������ã�
             001���̶�ϵ��1��
             010���̶�ϵ��2��
             011���̶�ϵ��3��
             100���̶�ϵ��4��
             101���̶�ϵ��5��
             110���̶�ϵ��6��
             111���̶�ϵ��7��
 bit[3:2]    ����
 bit[1:0]    W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
             2'b00��2560chip��(WģĬ��)
             2'b01��512chip��
             2'b10��1024chip��(XģĬ��)
             2'b11��2048chip��
   UNION�ṹ:  ABB_CH1_RX_3G_DIG_3_UNION */
#define ABB_CH1_RX_3G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x415)

/* �Ĵ���˵����RX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6:4]    RXͨ��ģʽ���ƣ�
             000��2G_A(Ĭ��)
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             110��CA
             111��2G_B
 bit[3:1]    ����
 bit[0]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
   UNION�ṹ:  ABB_CH0_RX_4G_DIG_1_UNION */
#define ABB_CH0_RX_4G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x440)

/* �Ĵ���˵����RX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6]      RXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[5]      RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
             0������
             1������
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
   UNION�ṹ:  ABB_CH0_RX_4G_DIG_2_UNION */
#define ABB_CH0_RX_4G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x441)

/* �Ĵ���˵����RX 4Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6:4]    RXͨ�������˲�������ϵ���̶����ƣ�
             000��ϵ�����̶����ɼĴ������ã�
             001���̶�ϵ��1��
             010���̶�ϵ��2��
             011���̶�ϵ��3��
             100���̶�ϵ��4��
             101���̶�ϵ��5��
             110���̶�ϵ��6��
             111���̶�ϵ��7��
 bit[3:2]    ����
 bit[1:0]    W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
             2'b00��2560chip��(WģĬ��)
             2'b01��512chip��
             2'b10��1024chip��(XģĬ��)
             2'b11��2048chip��
   UNION�ṹ:  ABB_CH0_RX_4G_DIG_3_UNION */
#define ABB_CH0_RX_4G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x442)

/* �Ĵ���˵����RX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6:4]    RXͨ��ģʽ���ƣ�
             000��2G_A(Ĭ��)
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             110��CA
             111��2G_B
 bit[3:1]    ����
 bit[0]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
   UNION�ṹ:  ABB_CH1_RX_4G_DIG_1_UNION */
#define ABB_CH1_RX_4G_DIG_1_ADDR                      (ABB_BASE_ADDR + 0x443)

/* �Ĵ���˵����RX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6]      RXͨ��FLUSHʹ�ܣ�
             0����ʹ��
             1��ʹ��
 bit[5]      RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
             0������
             1������
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
   UNION�ṹ:  ABB_CH1_RX_4G_DIG_2_UNION */
#define ABB_CH1_RX_4G_DIG_2_ADDR                      (ABB_BASE_ADDR + 0x444)

/* �Ĵ���˵����RX 4Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7]      ����
 bit[6:4]    RXͨ�������˲�������ϵ���̶����ƣ�
             000��ϵ�����̶����ɼĴ������ã�
             001���̶�ϵ��1��
             010���̶�ϵ��2��
             011���̶�ϵ��3��
             100���̶�ϵ��4��
             101���̶�ϵ��5��
             110���̶�ϵ��6��
             111���̶�ϵ��7��
 bit[3:2]    ����
 bit[1:0]    W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
             2'b00��2560chip��(WģĬ��)
             2'b01��512chip��
             2'b10��1024chip��(XģĬ��)
             2'b11��2048chip��
   UNION�ṹ:  ABB_CH1_RX_4G_DIG_3_UNION */
#define ABB_CH1_RX_4G_DIG_3_ADDR                      (ABB_BASE_ADDR + 0x445)

/* �Ĵ���˵����RXʱ���ſ��ӳٹ������á�
 bit[7:3]    ����
 bit[2:1]    RXʱ���ſ��ӳٵ�19.2MHzʱ�Ӹ�����
                 L/CA/Xģ   W/TDSģ  Gģ
             00��  1          2      32��  (Ĭ��)
             01��  2          4      64��
             10��  4          8      128��
             11��  reserved
 bit[0]      RXʱ���ſ��ӳٹ���ʹ�ܡ��ù��ܴ򿪺�RX����·�����ӱ�RX���ݺ�VLD�ź��ӳٹرա�
   UNION�ṹ:  ABB_RX_EN_DELAY_UNION */
#define ABB_RX_EN_DELAY_ADDR                          (ABB_BASE_ADDR + 0x470)

/* �Ĵ���˵����ģʽ�Ĵ���
 bit[7:1]    ����
 bit[0]
   UNION�ṹ:  ABB_COMB_MODE_UNION */
#define ABB_COMB_MODE_ADDR                            (ABB_BASE_ADDR + 0x471)

/* �Ĵ���˵��������ģʽ�Ĵ�����
 bit[7:6]    ����
 bit[5:4]
 bit[3:2]
 bit[1]
 bit[0]      ���ֲ���RXͨ����λ�źţ�
             0������λ(Ĭ��)
             1����λ
   UNION�ṹ:  ABB_CH0_RX_TESTMODE_UNION */
#define ABB_CH0_RX_TESTMODE_ADDR                      (ABB_BASE_ADDR + 0x480)

/* �Ĵ���˵����PLLѡ��Ĵ���
 bit[7:4]    ����
 bit[3]      C1ģPLLѡ��
             0��ѡ��SCPLL1
             1��ѡ��SCPLL0
 bit[2]      WTLģPLLѡ��
             0��ѡ��SCPLL0
             1��ѡ��SCPLL1
 bit[1:0]    GģPLLѡ��
             0��ѡ��GPLL
             1��ѡ��SCPLL0
             2��ѡ��SCPLL1
   UNION�ṹ:  ABB_CH0_PLL_SEL_UNION */
#define ABB_CH0_PLL_SEL_ADDR                          (ABB_BASE_ADDR + 0x481)

/* �Ĵ���˵����RX���ֹ���ģʽ�ϱ��Ĵ�����
   ��      ����[8:6]��RXͨ��ģʽ�����ϱ���
                    000��2G(Ĭ��)
                    001��3G_SC
                    010��4G &amp; ET &amp; APT
                    011��3G_DC
                    100��TDS
                    Others��CA
            [5:3]��rx_comp_sel
            [2]  ��rx_hb_bp
            [1:0]������
   UNION�ṹ ���� */
#define ABB_CH0_RX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x482)

/* �Ĵ���˵����RX���ֹ���״̬�ϱ��Ĵ�����
   ��      ����[7:4]������
            [3]  ��bͨ�� ���ָʾ
            [2]  ��bͨ�� ���ݷ�תָʾ 1��ʾ��ת 0��ʾ����ת
            [1]  ��aͨ�� ���ָʾ
            [0]  ��aͨ�� ���ݷ�תָʾ 1��ʾ��ת 0��ʾ����ת
   UNION�ṹ ���� */
#define ABB_CH0_RX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x483)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x484)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x485)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7:1]    ����
 bit[0]      RXAͨ��I·�����˲���ϵ��C3,�޷�����,���λ
   UNION�ṹ:  ABB_CH0_RXA_I_COEF2_UNION */
#define ABB_CH0_RXA_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x486)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x487)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x488)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_COEF5_ADDR                      (ABB_BASE_ADDR + 0x489)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x48A)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x48B)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7:1]    ����
 bit[0]      RXAͨ��I·�����˲���ϵ��C3,�޷�����,���λ
   UNION�ṹ:  ABB_CH0_RXA_Q_COEF2_UNION */
#define ABB_CH0_RXA_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x48C)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x48D)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x48E)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_COEF5_ADDR                      (ABB_BASE_ADDR + 0x48F)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x490)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x491)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7:1]    ����
 bit[0]      RXBͨ��I·�����˲���ϵ��C3,�޷�����,���λ
   UNION�ṹ:  ABB_CH0_RXB_I_COEF2_UNION */
#define ABB_CH0_RXB_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x492)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x493)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x494)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_COEF5_ADDR                      (ABB_BASE_ADDR + 0x495)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x496)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x497)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7:1]    ����
 bit[0]      RXBͨ��I·�����˲���ϵ��C3,�޷�����,���λ
   UNION�ṹ:  ABB_CH0_RXB_Q_COEF2_UNION */
#define ABB_CH0_RXB_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x498)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x499)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x49A)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_COEF5_ADDR                      (ABB_BASE_ADDR + 0x49B)

/* �Ĵ���˵����RXAͨ��BLOCKING DCR���üĴ�����
 bit[7:5]    RXA����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ��
 bit[4:0]    RXA����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣
   UNION�ṹ:  ABB_CH0_REG_RXA_DCR_CFG_UNION */
#define ABB_CH0_REG_RXA_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x49C)

/* �Ĵ���˵����RXBͨ��BLOCKING DCR���üĴ�����
 bit[7:5]    RXB����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ��
 bit[4:0]    RXB����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣
   UNION�ṹ:  ABB_CH0_REG_RXB_DCR_CFG_UNION */
#define ABB_CH0_REG_RXB_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x49D)

/* �Ĵ���˵����BLOCKING DCR���ܿ��ƼĴ�����
 bit[7:2]    ����
 bit[1]      RXB����BLOCKING DCR����bypass���ơ�
             0��DCR���ܲ�bypasss��
             1��DCR����bypass��
 bit[0]      RXA����BLOCKING DCR����bypass���ơ�
             0��DCR���ܲ�bypasss��
             1��DCR����bypass��
   UNION�ṹ:  ABB_CH0_REG_RX_DCR_CTRL_UNION */
#define ABB_CH0_REG_RX_DCR_CTRL_ADDR                  (ABB_BASE_ADDR + 0x49E)

/* �Ĵ���˵����RXAͨ��BLOCKING�ϱ��Ĵ�����
 bit[7:5]    RXA����BLOCKING�ϱ�ֵ��ϵ��N��BLOCKING�ϱ����ΪN*2^M
 bit[4:0]    RXA����BLOCKING�ϱ�ֵ,2���ݴ�M
   UNION�ṹ:  ABB_CH0_RXA_BLOCKING_UNION */
#define ABB_CH0_RXA_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x49F)

/* �Ĵ���˵����RXBͨ��BLOCKING�ϱ��Ĵ�����
 bit[7:5]    RXB����BLOCKING�ϱ�ֵ��ϵ��N��BLOCKING�ϱ����ΪN*2^M
 bit[4:0]    RXB����BLOCKING�ϱ�ֵ,2���ݴ�M
   UNION�ṹ:  ABB_CH0_RXB_BLOCKING_UNION */
#define ABB_CH0_RXB_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x4A0)

/* �Ĵ���˵����RXAͨ��I·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXA����I·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH0_REG_RXA_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x4A1)

/* �Ĵ���˵����RXAͨ��I·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXA����I·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH0_REG_RXA_DC_I_2_UNION */
#define ABB_CH0_REG_RXA_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x4A2)

/* �Ĵ���˵����RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH0_REG_RXA_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x4A3)

/* �Ĵ���˵����RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH0_REG_RXA_DC_Q_2_UNION */
#define ABB_CH0_REG_RXA_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x4A4)

/* �Ĵ���˵����RXBͨ��I·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXB����I·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH0_REG_RXB_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x4A5)

/* �Ĵ���˵����RXBͨ��I·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXB����I·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH0_REG_RXB_DC_I_2_UNION */
#define ABB_CH0_REG_RXB_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x4A6)

/* �Ĵ���˵����RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH0_REG_RXB_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x4A7)

/* �Ĵ���˵����RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH0_REG_RXB_DC_Q_2_UNION */
#define ABB_CH0_REG_RXB_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x4A8)

/* �Ĵ���˵����ͨ��0���üĴ�����
   ��      ����ͨ��0 flush���[7:0]����λΪ19.2Mʱ�����ڡ�
   UNION�ṹ ���� */
#define ABB_CH0_FLUSH_CFG0_ADDR                       (ABB_BASE_ADDR + 0x4A9)

/* �Ĵ���˵����ͨ��0���üĴ�����
 bit[7:3]    ͨ��0 FLUSHֵ��Ĭ��Ϊ8��
 bit[2:0]    ͨ��0 flush���[10:8]����λΪ19.2Mʱ�����ڡ�
   UNION�ṹ:  ABB_CH0_FLUSH_CFG1_UNION */
#define ABB_CH0_FLUSH_CFG1_ADDR                       (ABB_BASE_ADDR + 0x4AA)

/* �Ĵ���˵����CH0ͨ��RXA HB�˲������档
   ��      ����CH0ͨ��RXA I· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH0_RXAI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4AB)

/* �Ĵ���˵����CH0ͨ��RXA HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH0ͨ��RXA I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH0_RXAI_HB_GAIN_2_UNION */
#define ABB_CH0_RXAI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4AC)

/* �Ĵ���˵����CH0ͨ��RXA HB�˲������档
   ��      ����CH0ͨ��RXA Q· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH0_RXAQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4AD)

/* �Ĵ���˵����CH0ͨ��RXA HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH0ͨ��RXA Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH0_RXAQ_HB_GAIN_2_UNION */
#define ABB_CH0_RXAQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4AE)

/* �Ĵ���˵����CH0ͨ��RXB HB�˲������档
   ��      ����CH0ͨ��RXB I· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH0_RXBI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4AF)

/* �Ĵ���˵����CH0ͨ��RXB HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH0ͨ��RXB I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH0_RXBI_HB_GAIN_2_UNION */
#define ABB_CH0_RXBI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4B0)

/* �Ĵ���˵����CH0ͨ��RXB HB�˲������档
   ��      ����CH0ͨ��RXB Q· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH0_RXBQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4B1)

/* �Ĵ���˵����CH0ͨ��RXB HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH0ͨ��RXB Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH0_RXBQ_HB_GAIN_2_UNION */
#define ABB_CH0_RXBQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4B2)

/* �Ĵ���˵����ͨ�����ƼĴ�����
 bit[7:2]    ����
 bit[1]      CH0ͨ��RXB������������źţ�0�����ز�����źţ�1������ͬʱ����źţ�
 bit[0]      CH0ͨ��RXA������������źţ�0�����ز�����źţ�1������ͬʱ����źţ�
   UNION�ṹ:  ABB_CH0_CTRL_UNION */
#define ABB_CH0_CTRL_ADDR                             (ABB_BASE_ADDR + 0x4B3)

/* �Ĵ���˵����RX�߿�ǿ������ʹ�ܡ�
 bit[7]      ����
 bit[6]      ����
 bit[5]      RXBͨ��ǿ���߿�
 bit[4]      RXAͨ��ǿ���߿�
 bit[3]      ����
 bit[2]      ����
 bit[1]      RXBͨ���߿�ѡ��ǿ��ʹ��
             0��ѡ���߿�ʹ��
             1��ѡ��ǿ��ʹ��
 bit[0]      RXAͨ���߿�ѡ��ǿ��ʹ��
             0��ѡ���߿�ʹ��
             1��ѡ��ǿ��ʹ��
   UNION�ṹ:  ABB_CH0_RX_LINE_SEL_UNION */
#define ABB_CH0_RX_LINE_SEL_ADDR                      (ABB_BASE_ADDR + 0x4B4)

/* �Ĵ���˵����RXģʽ�߿�ǿ�����á�
 bit[7:4]    ����
 bit[3]      �߿��ź�CH0_RX_LINE_CTRL_MODEǿ������ʹ��
 bit[2:0]    �߿��ź�CH0_RX_LINE_CTRL_MODEǿ������ֵ
             0��IDLE
             1��Gģ
             2��Wģ
             3��LTEģ
             4��TDSģ
             5��Xģ

   UNION�ṹ:  ABB_CH0_RX_LINE_CFG_UNION */
#define ABB_CH0_RX_LINE_CFG_ADDR                      (ABB_BASE_ADDR + 0x4B5)

/* �Ĵ���˵����blk���ƼĴ�����
 bit[7:3]    ����
 bit[2]      �߿��ź�CH0_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ʹ��
 bit[1]      �߿��ź�CH0_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ֵ
 bit[0]      ����
   UNION�ṹ:  ABB_CH0_BLK_CFG_UNION */
#define ABB_CH0_BLK_CFG_ADDR                          (ABB_BASE_ADDR + 0x4B6)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
 bit[7:2]    ����
 bit[1]      CH0_RXB_EN�߿�״̬�ϱ�
 bit[0]      CH0_RXA_EN�߿�״̬�ϱ�
   UNION�ṹ:  ABB_CH0_RX_LINE_RPT0_UNION */
#define ABB_CH0_RX_LINE_RPT0_ADDR                     (ABB_BASE_ADDR + 0x4B7)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
 bit[7]      CH0_RXB_BLK_EN�߿�״̬�ϱ�
 bit[6]      CH0_RXA_BLK_EN�߿�״̬�ϱ�
 bit[5:3]    CH0 RX_LINE_CTRL_MODE״̬�ϱ���
             0��IDLE
             1��Gģ
             2��Wģ
             3��LTEģ
             4��TDSģ
             5��Xģ
             others��IDLE
 bit[2:0]    ����
   UNION�ṹ:  ABB_CH0_RX_LINE_RPT1_UNION */
#define ABB_CH0_RX_LINE_RPT1_ADDR                     (ABB_BASE_ADDR + 0x4B8)

/* �Ĵ���˵�������ֵ��ԼĴ�����
 bit[7]      bit[7]��ģʽ�л���λ��������ʹ��
             0����ʹ��
             1��ʹ��
 bit[6:4]    ģʽ�л���λ��������ֵ����λΪ8 cycles
 bit[3:1]    ����
 bit[0]      RX��Ƶ��ʹ��bypass����
             0����bypass
             1��bypass
   UNION�ṹ:  ABB_CH0_RX_REG_DEBUG_DIG_UNION */
#define ABB_CH0_RX_REG_DEBUG_DIG_ADDR                 (ABB_BASE_ADDR + 0x4B9)

/* �Ĵ���˵��������ģʽ�Ĵ�����
 bit[7:6]    ����
 bit[5:4]
 bit[3:2]    ����
 bit[1]
 bit[0]      ���ֲ���RXͨ����λ�źţ�
             0������λ(Ĭ��)
             1����λ
   UNION�ṹ:  ABB_CH1_RX_TESTMODE_UNION */
#define ABB_CH1_RX_TESTMODE_ADDR                      (ABB_BASE_ADDR + 0x4C0)

/* �Ĵ���˵����PLLѡ��Ĵ���
 bit[7:4]    ����
 bit[3]      C1ģPLLѡ��
             0��ѡ��SCPLL1
             1��ѡ��SCPLL0
 bit[2]      WTLģPLLѡ��
             0��ѡ��SCPLL0
             1��ѡ��SCPLL1
 bit[1:0]    GģPLLѡ��
             0��ѡ��GPLL
             1��ѡ��SCPLL0
             2��ѡ��SCPLL1
   UNION�ṹ:  ABB_CH1_PLL_SEL_UNION */
#define ABB_CH1_PLL_SEL_ADDR                          (ABB_BASE_ADDR + 0x4C1)

/* �Ĵ���˵����RX���ֹ���ģʽ�ϱ��Ĵ�����
   ��      ����[8:6]��RXͨ��ģʽ�����ϱ���
                    000��2G(Ĭ��)
                    001��3G_SC
                    010��4G &amp; ET &amp; APT
                    011��3G_DC
                    100��TDS
                    Others��CA
            [5:3]��rx_comp_sel
            [2]  ��rx_hb_bp
            [1:0]������
   UNION�ṹ ���� */
#define ABB_CH1_RX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x4C2)

/* �Ĵ���˵����RX���ֹ���״̬�ϱ��Ĵ�����
   ��      ����[7:4]������
            [3]  ��bͨ�� ���ָʾ
            [2]  ��bͨ�� ���ݷ�תָʾ 1��ʾ��ת 0��ʾ����ת
            [1]  ��aͨ�� ���ָʾ
            [0]  ��aͨ�� ���ݷ�תָʾ 1��ʾ��ת 0��ʾ����ת
   UNION�ṹ ���� */
#define ABB_CH1_RX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x4C3)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXA_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4C4)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXA_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x4C5)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7:1]    ����
 bit[0]      RXAͨ��I·�����˲���ϵ��C3,�޷�����,���λ
   UNION�ṹ:  ABB_CH1_RXA_I_COEF2_UNION */
#define ABB_CH1_RXA_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x4C6)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH1_RXA_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x4C7)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXA_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x4C8)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXA_I_COEF5_ADDR                      (ABB_BASE_ADDR + 0x4C9)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXA_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4CA)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXA_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x4CB)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7:1]    ����
 bit[0]      RXAͨ��I·�����˲���ϵ��C3,�޷�����,���λ
   UNION�ṹ:  ABB_CH1_RXA_Q_COEF2_UNION */
#define ABB_CH1_RXA_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x4CC)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH1_RXA_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x4CD)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXA_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x4CE)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXA_Q_COEF5_ADDR                      (ABB_BASE_ADDR + 0x4CF)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXB_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4D0)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXB_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x4D1)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7:1]    ����
 bit[0]      RXBͨ��I·�����˲���ϵ��C3,�޷�����,���λ
   UNION�ṹ:  ABB_CH1_RXB_I_COEF2_UNION */
#define ABB_CH1_RXB_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x4D2)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH1_RXB_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x4D3)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXB_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x4D4)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXB_I_COEF5_ADDR                      (ABB_BASE_ADDR + 0x4D5)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXB_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4D6)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXB_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x4D7)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7:1]    ����
 bit[0]      RXBͨ��I·�����˲���ϵ��C3,�޷�����,���λ
   UNION�ṹ:  ABB_CH1_RXB_Q_COEF2_UNION */
#define ABB_CH1_RXB_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x4D8)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH1_RXB_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x4D9)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXB_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x4DA)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXB_Q_COEF5_ADDR                      (ABB_BASE_ADDR + 0x4DB)

/* �Ĵ���˵����RXAͨ��BLOCKING DCR���üĴ�����
 bit[7:5]    RXA����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ��
 bit[4:0]    RXA����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣
   UNION�ṹ:  ABB_CH1_REG_RXA_DCR_CFG_UNION */
#define ABB_CH1_REG_RXA_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x4DC)

/* �Ĵ���˵����RXBͨ��BLOCKING DCR���üĴ�����
 bit[7:5]    RXB����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ��
 bit[4:0]    RXB����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣
   UNION�ṹ:  ABB_CH1_REG_RXB_DCR_CFG_UNION */
#define ABB_CH1_REG_RXB_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x4DD)

/* �Ĵ���˵����BLOCKING DCR���ܿ��ƼĴ�����
 bit[7:2]    ����
 bit[1]      RXB����BLOCKING DCR����bypass���ơ�
             0��DCR���ܲ�bypasss��
             1��DCR����bypass��
 bit[0]      RXA����BLOCKING DCR����bypass���ơ�
             0��DCR���ܲ�bypasss��
             1��DCR����bypass��
   UNION�ṹ:  ABB_CH1_REG_RX_DCR_CTRL_UNION */
#define ABB_CH1_REG_RX_DCR_CTRL_ADDR                  (ABB_BASE_ADDR + 0x4DE)

/* �Ĵ���˵����RXAͨ��BLOCKING�ϱ��Ĵ�����
 bit[7:5]    RXA����BLOCKING�ϱ�ֵ��ϵ��N��BLOCKING�ϱ����ΪN*2^M
 bit[4:0]    RXA����BLOCKING�ϱ�ֵ,2���ݴ�M
   UNION�ṹ:  ABB_CH1_RXA_BLOCKING_UNION */
#define ABB_CH1_RXA_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x4DF)

/* �Ĵ���˵����RXBͨ��BLOCKING�ϱ��Ĵ�����
 bit[7:5]    RXB����BLOCKING�ϱ�ֵ��ϵ��N��BLOCKING�ϱ����ΪN*2^M
 bit[4:0]    RXB����BLOCKING�ϱ�ֵ,2���ݴ�M
   UNION�ṹ:  ABB_CH1_RXB_BLOCKING_UNION */
#define ABB_CH1_RXB_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x4E0)

/* �Ĵ���˵����RXAͨ��I·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXA����I·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH1_REG_RXA_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x4E1)

/* �Ĵ���˵����RXAͨ��I·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXA����I·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH1_REG_RXA_DC_I_2_UNION */
#define ABB_CH1_REG_RXA_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x4E2)

/* �Ĵ���˵����RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH1_REG_RXA_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x4E3)

/* �Ĵ���˵����RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH1_REG_RXA_DC_Q_2_UNION */
#define ABB_CH1_REG_RXA_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x4E4)

/* �Ĵ���˵����RXBͨ��I·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXB����I·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH1_REG_RXB_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x4E5)

/* �Ĵ���˵����RXBͨ��I·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXB����I·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH1_REG_RXB_DC_I_2_UNION */
#define ABB_CH1_REG_RXB_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x4E6)

/* �Ĵ���˵����RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH1_REG_RXB_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x4E7)

/* �Ĵ���˵����RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH1_REG_RXB_DC_Q_2_UNION */
#define ABB_CH1_REG_RXB_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x4E8)

/* �Ĵ���˵����ͨ��1���üĴ�����
   ��      ����ͨ��1 flush���[7:0]����λΪ19.2Mʱ�����ڡ�
   UNION�ṹ ���� */
#define ABB_CH1_FLUSH_CFG0_ADDR                       (ABB_BASE_ADDR + 0x4E9)

/* �Ĵ���˵����ͨ��1���üĴ�����
 bit[7:3]    ͨ��1 FLUSHֵ��Ĭ��Ϊ8��
 bit[2:0]    ͨ��1 flush���[10:8]����λΪ19.2Mʱ�����ڡ�
   UNION�ṹ:  ABB_CH1_FLUSH_CFG1_UNION */
#define ABB_CH1_FLUSH_CFG1_ADDR                       (ABB_BASE_ADDR + 0x4EA)

/* �Ĵ���˵����CH1ͨ��RXA HB�˲������档
   ��      ����CH1ͨ��RXA I· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH1_RXAI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4EB)

/* �Ĵ���˵����CH1ͨ��RXA HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH1ͨ��RXA I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH1_RXAI_HB_GAIN_2_UNION */
#define ABB_CH1_RXAI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4EC)

/* �Ĵ���˵����CH1ͨ��RXA HB�˲������档
   ��      ����CH1ͨ��RXA Q· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH1_RXAQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4ED)

/* �Ĵ���˵����CH1ͨ��RXA HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH1ͨ��RXA Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH1_RXAQ_HB_GAIN_2_UNION */
#define ABB_CH1_RXAQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4EE)

/* �Ĵ���˵����CH1ͨ��RXB HB�˲������档
   ��      ����CH1ͨ��RXB I· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH1_RXBI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4EF)

/* �Ĵ���˵����CH1ͨ��RXB HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH1ͨ��RXB I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH1_RXBI_HB_GAIN_2_UNION */
#define ABB_CH1_RXBI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4F0)

/* �Ĵ���˵����CH1ͨ��RXB HB�˲������档
   ��      ����CH1ͨ��RXB Q· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH1_RXBQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4F1)

/* �Ĵ���˵����CH1ͨ��RXB HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH1ͨ��RXB Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH1_RXBQ_HB_GAIN_2_UNION */
#define ABB_CH1_RXBQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4F2)

/* �Ĵ���˵����ͨ�����ƼĴ�����
 bit[7:2]    ����
 bit[1]      CH1ͨ��RXB������������źţ�0�����ز�����źţ�1������ͬʱ����źţ�
 bit[0]      CH1ͨ��RXA������������źţ�0�����ز�����źţ�1������ͬʱ����źţ�
   UNION�ṹ:  ABB_CH1_CTRL_UNION */
#define ABB_CH1_CTRL_ADDR                             (ABB_BASE_ADDR + 0x4F3)

/* �Ĵ���˵�����߿�ǿ������ʹ�ܡ�
 bit[7:6]    ����
 bit[5]      RXBͨ��ǿ���߿�
 bit[4]      RXAͨ��ǿ���߿�
 bit[3:2]    ����
 bit[1]      RXBͨ���߿�ѡ��ǿ��ʹ��
             0��ѡ���߿�ʹ��
             1��ѡ��ǿ��ʹ��
 bit[0]      RXAͨ���߿�ѡ��ǿ��ʹ��
             0��ѡ���߿�ʹ��
             1��ѡ��ǿ��ʹ��
   UNION�ṹ:  ABB_CH1_RX_LINE_SEL_UNION */
#define ABB_CH1_RX_LINE_SEL_ADDR                      (ABB_BASE_ADDR + 0x4F4)

/* �Ĵ���˵����ģʽ�߿�ǿ�����á�
 bit[7:4]    ����
 bit[3]      �߿��ź�CH1_RX_LINE_CTRL_MODEǿ������ʹ��
 bit[2:0]    �߿��ź�CH1_RX_LINE_CTRL_MODEǿ������ֵ
             0��IDLE
             1��Gģ
             2��Wģ
             3��LTEģ
             4��TDSģ
             5��Xģ
   UNION�ṹ:  ABB_CH1_RX_LINE_CFG_UNION */
#define ABB_CH1_RX_LINE_CFG_ADDR                      (ABB_BASE_ADDR + 0x4F5)

/* �Ĵ���˵����blk���ƼĴ�����
 bit[7:3]    ����
 bit[2]      �߿��ź�CH1_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ʹ��
 bit[1]      �߿��ź�CH1_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ֵ
 bit[0]      ����
   UNION�ṹ:  ABB_CH1_BLK_CFG_UNION */
#define ABB_CH1_BLK_CFG_ADDR                          (ABB_BASE_ADDR + 0x4F6)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
 bit[7:2]    ����
 bit[1]      CH1_RXB_EN�߿�״̬�ϱ�
 bit[0]      CH1_RXA_EN�߿�״̬�ϱ�
   UNION�ṹ:  ABB_CH1_RX_LINE_RPT0_UNION */
#define ABB_CH1_RX_LINE_RPT0_ADDR                     (ABB_BASE_ADDR + 0x4F7)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
 bit[7]      CH1_RXB_BLK_EN�߿�״̬�ϱ�
 bit[6]      CH1_RXA_BLK_EN�߿�״̬�ϱ�
 bit[5:3]    CH1 RX_LINE_CTRL_MODE״̬�ϱ���
             0��IDLE
             1��Gģ
             2��Wģ
             3��LTEģ
             4��TDSģ
             5��Xģ
             others��IDLE
 bit[2:0]    ����
   UNION�ṹ:  ABB_CH1_RX_LINE_RPT1_UNION */
#define ABB_CH1_RX_LINE_RPT1_ADDR                     (ABB_BASE_ADDR + 0x4F8)

/* �Ĵ���˵�������ֵ��ԼĴ�����
 bit[7]      bit[7]��ģʽ�л���λ��������ʹ��
             0����ʹ��
             1��ʹ��
 bit[6:4]    ģʽ�л���λ��������ֵ����λΪ8 cycles
 bit[3:1]    ����
 bit[0]      RX��Ƶ��ʹ��bypass����
             0����bypass
             1��bypass
   UNION�ṹ:  ABB_CH1_RX_REG_DEBUG_DIG_UNION */
#define ABB_CH1_RX_REG_DEBUG_DIG_ADDR                 (ABB_BASE_ADDR + 0x4F9)



/***======================================================================***
                     (4/4) register_define_abb_ana
 ***======================================================================***/
/* �Ĵ���˵����SC_PLL�������ƼĴ���
 bit[7]      ����
 bit[6]      SCPLL0����ָʾ��
 bit[5]      SCPLL0�ȶ�ָʾ��0��ʾSCPLL0δ�ȶ���1��ʾSCPLL0�ȶ���SCPLL0�ȶ�����ʱ�������
 bit[4]      SCPLL0�ſ�ʹ���źš�
 bit[3:1]    SCPLL0ʱ���ȶ��ȴ�ʱ�����ã�����ʱ��Ϊ19.2M��
             000��SCPLL0����10us��ʱ���ȶ���
             001��SCPLL0����20us��ʱ���ȶ���
             010��SCPLL0����50us��ʱ���ȶ���
             011��SCPLL0����75us��ʱ���ȶ���
             100��SCPLL0����100us��ʱ���ȶ���
             101��SCPLL0����115us��ʱ���ȶ���
             110��SCPLL0����125us��ʱ���ȶ���
             default��100us
 bit[0]      SCPLL0ʹ���źš�����ͨ��CFG�ӿ����ô�scpll0��
   UNION�ṹ:  ABB_SCPLL0_LOCK_CTRL_UNION */
#define ABB_SCPLL0_LOCK_CTRL_ADDR                     (ABB_BASE_ADDR + 0x800)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
   ��      ����[7]:Reserved;
            [5:3]��PLL���Ƶ����postdiv2��Ĭ��ֵΪ1��
            [2:0]��PLL���Ƶ����postdiv1��Ĭ��ֵΪ5��
   UNION�ṹ ���� */
#define ABB_SCPLL0_POSTDIV_ADDR                       (ABB_BASE_ADDR + 0x801)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
   ��      ����[7:0]��PLL������Ƶ����fbdiv[11:0]�ĵ�8bit��fbdiv[11:0]Ĭ��ֵΪ64.
   UNION�ṹ ���� */
#define ABB_SCPLL0_FBDIV_L_ADDR                       (ABB_BASE_ADDR + 0x802)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
 bit[7:4]    ����
 bit[3:0]    PLL������Ƶ����fbdiv[11:0]�ĸ�4bit��
   UNION�ṹ:  ABB_SCPLL0_FBDIV_H_UNION */
#define ABB_SCPLL0_FBDIV_H_ADDR                       (ABB_BASE_ADDR + 0x803)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
 bit[7:6]    ����
 bit[5:0]    PLL�ο���Ƶ����refdiv[5:0]��Ĭ��ֵΪ1��
   UNION�ṹ:  ABB_SCPLL0_REFDIV_UNION */
#define ABB_SCPLL0_REFDIV_ADDR                        (ABB_BASE_ADDR + 0x804)

/* �Ĵ���˵����SC_PLL��Ƶ�����ƼĴ���
   ��      ����[7:6]��Reserved��
            [5]��DACPD��Ĭ��ֵΪ0(��)��
            [4]��PLL FOUT4PHASEPD���ƣ�����Ч��Ĭ��ֵ1���رգ���
            [3]��DSMPD��С��ģʽPD�źţ�Ĭ��ֵ0���򿪣���
            [2]��PLL ��·���ƣ�Ĭ��ֵ0��PLL��·����bypass����
            [1]��PLL FOUTPOSTDIVPD���ƣ�����Ч��Ĭ��ֵ0���򿪣���
            [0]��PLL FOUTVCOPD���ƣ�����Ч��Ĭ��ֵ0���򿪣���
   UNION�ṹ ���� */
#define ABB_SCPLL0_FREQ_CTRL_ADDR                     (ABB_BASE_ADDR + 0x805)

/* �Ĵ���˵����SC_PLL�����������üĴ���
   ��      ����[7:0]��PLL������Ƶ����frac[23:0]��[7:0]λ��frac[23:0]Ĭ��ֵ0x0��
   UNION�ṹ ���� */
#define ABB_SCPLL0_FRAC1_ADDR                         (ABB_BASE_ADDR + 0x806)

/* �Ĵ���˵����SC_PLL�����������üĴ���
   ��      ����[7:0]��PLL������Ƶ����frac[23:0]��[15:8]λ��frac[23:0]Ĭ��ֵ0x0��
   UNION�ṹ ���� */
#define ABB_SCPLL0_FRAC2_ADDR                         (ABB_BASE_ADDR + 0x807)

/* �Ĵ���˵����SC_PLL�����������üĴ���
   ��      ����[7:0]��PLL������Ƶ����frac[23:0]��[23:16]λ��frac[23:0]Ĭ��ֵ0x0��
   UNION�ṹ ���� */
#define ABB_SCPLL0_FRAC3_ADDR                         (ABB_BASE_ADDR + 0x808)

/* �Ĵ���˵����SC_PLL�������ƼĴ���
 bit[7:1]    ����
 bit[0]      SCPLL0�������ø���ָʾ��
             scpll0_en�򿪺����������scpll0_postdiv��scpll0_fbdiv��scpll0_frac������������scpll0_sfg_update������ͬʱ���£�scpll0_en����ʱ�����ò����������£�����Ҫ����scpll0_sfg_update��
   UNION�ṹ:  ABB_SCPLL0_CFG_UPDATE_UNION */
#define ABB_SCPLL0_CFG_UPDATE_ADDR                    (ABB_BASE_ADDR + 0x809)

/* �Ĵ���˵����SC_PLL�������ƼĴ���
 bit[7]      ����
 bit[6]      SCPLL1����ָʾ��
 bit[5]      SCPLL1�ȶ�ָʾ��0��ʾSCPLL1δ�ȶ���1��ʾSCPLL1�ȶ���SCPLL1�ȶ�����ʱ�������
 bit[4]      SCPLL1�ſ�ʹ���źš�
 bit[3:1]    SCPLL1ʱ���ȶ��ȴ�ʱ�����ã�����ʱ��Ϊ19.2M��
             000��SCPLL1����10us��ʱ���ȶ���
             001��SCPLL1����20us��ʱ���ȶ���
             010��SCPLL1����50us��ʱ���ȶ���
             011��SCPLL1����75us��ʱ���ȶ���
             100��SCPLL1����100us��ʱ���ȶ���
             101��SCPLL1����115us��ʱ���ȶ���
             110��SCPLL1����125us��ʱ���ȶ���
             default��100us
 bit[0]      SCPLL1ʹ���źš�����ͨ��CFG�ӿ����ô�scpll1��
   UNION�ṹ:  ABB_SCPLL1_LOCK_CTRL_UNION */
#define ABB_SCPLL1_LOCK_CTRL_ADDR                     (ABB_BASE_ADDR + 0x80A)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
   ��      ����[7]:Reserved;
            [5:3]��PLL���Ƶ����postdiv2��Ĭ��ֵΪ1��
            [2:0]��PLL���Ƶ����postdiv1��Ĭ��ֵΪ5��
   UNION�ṹ ���� */
#define ABB_SCPLL1_POSTDIV_ADDR                       (ABB_BASE_ADDR + 0x80B)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
   ��      ����[7:0]��PLL������Ƶ����fbdiv[11:0]�ĵ�8bit��fbdiv[11:0]Ĭ��ֵΪ64.
   UNION�ṹ ���� */
#define ABB_SCPLL1_FBDIV_L_ADDR                       (ABB_BASE_ADDR + 0x80C)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
 bit[7:4]    ����
 bit[3:0]    PLL������Ƶ����fbdiv[11:0]�ĸ�4bit��
   UNION�ṹ:  ABB_SCPLL1_FBDIV_H_UNION */
#define ABB_SCPLL1_FBDIV_H_ADDR                       (ABB_BASE_ADDR + 0x80D)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
 bit[7:6]    ����
 bit[5:0]    PLL�ο���Ƶ����refdiv[5:0]��Ĭ��ֵΪ1��
   UNION�ṹ:  ABB_SCPLL1_REFDIV_UNION */
#define ABB_SCPLL1_REFDIV_ADDR                        (ABB_BASE_ADDR + 0x80E)

/* �Ĵ���˵����SC_PLL��Ƶ�����ƼĴ���
   ��      ����[7:6]��Reserved��
            [5]��DACPD��Ĭ��ֵΪ0(��)��
            [4]��PLL FOUT4PHASEPD���ƣ�����Ч��Ĭ��ֵ1���رգ���
            [3]��DSMPD��С��ģʽPD�źţ�Ĭ��ֵ0���򿪣���
            [2]��PLL ��·���ƣ�Ĭ��ֵ0��PLL��·����bypass����
            [1]��PLL FOUTPOSTDIVPD���ƣ�����Ч��Ĭ��ֵ0���򿪣���
            [0]��PLL FOUTVCOPD���ƣ�����Ч��Ĭ��ֵ0���򿪣���
   UNION�ṹ ���� */
#define ABB_SCPLL1_FREQ_CTRL_ADDR                     (ABB_BASE_ADDR + 0x80F)

/* �Ĵ���˵����SC_PLL�����������üĴ���
   ��      ����[7:0]��PLL������Ƶ����frac[23:0]��[7:0]λ��frac[23:0]Ĭ��ֵ0x0��
   UNION�ṹ ���� */
#define ABB_SCPLL1_FRAC1_ADDR                         (ABB_BASE_ADDR + 0x810)

/* �Ĵ���˵����SC_PLL�����������üĴ���
   ��      ����[7:0]��PLL������Ƶ����frac[23:0]��[15:8]λ��frac[23:0]Ĭ��ֵ0x0��
   UNION�ṹ ���� */
#define ABB_SCPLL1_FRAC2_ADDR                         (ABB_BASE_ADDR + 0x811)

/* �Ĵ���˵����SC_PLL�����������üĴ���
   ��      ����[7:0]��PLL������Ƶ����frac[23:0]��[23:16]λ��frac[23:0]Ĭ��ֵ0x0��
   UNION�ṹ ���� */
#define ABB_SCPLL1_FRAC3_ADDR                         (ABB_BASE_ADDR + 0x812)

/* �Ĵ���˵����SC_PLL�������ƼĴ���
 bit[7:1]    ����
 bit[0]      SCPLL1�������ø���ָʾ��
             scpll1_en�򿪺����������scpll1_postdiv��scpll1_fbdiv��scpll1_frac������������scpll1_sfg_update������ͬʱ���£�scpll1_en����ʱ�����ò����������£�����Ҫ����scpll1_sfg_update��
   UNION�ṹ:  ABB_SCPLL1_CFG_UPDATE_UNION */
#define ABB_SCPLL1_CFG_UPDATE_ADDR                    (ABB_BASE_ADDR + 0x813)

/* �Ĵ���˵����GPLL���ʱ���ſ�ʱ������
 bit[7]      ����
 bit[6]      GPLL����ָʾ��
 bit[5]      GPLL�ȶ�ָʾ��0��ʾGPLLδ�ȶ���1��ʾGPLL�ȶ���GPLL�ȶ�����ʱ�������
 bit[4]      GPLLʱ���ſع���ʹ�ܣ�
             0��gpllʱ���ſع��ܹرգ�
             1��gpllʱ���ſع��ܴ򿪡�
 bit[3:1]    GPLLʱ���ȶ��ȴ�ʱ�����ã�����ʱ��Ϊ19.2M��
             000��GPLL����10us��ʱ���ȶ���
             001��GPLL����20us��ʱ���ȶ���
             010��GPLL����50us��ʱ���ȶ���
             011��GPLL����75us��ʱ���ȶ���
             100��GPLL����100us��ʱ���ȶ���
             101��GPLL����115us��ʱ���ȶ���
             110��GPLL1����125us��ʱ���ȶ���
             default��20us
 bit[0]      GPLLʹ��
   UNION�ṹ:  ABB_GPLL0_GATE_TIME_UNION */
#define ABB_GPLL0_GATE_TIME_ADDR                      (ABB_BASE_ADDR + 0x814)

/* �Ĵ���˵����GPLL���ʱ���ſ�ʱ������
 bit[7:1]    ����
 bit[0]      GPLLʹ�ܸ���
   UNION�ṹ:  ABB_GPL1L_GATE_TIME_UNION */
#define ABB_GPL1L_GATE_TIME_ADDR                      (ABB_BASE_ADDR + 0x815)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7] FREF_SEL
                PLL�Ĳο�ʱ��ѡ��
                1��TCXO_INP��ΪPLL�Ĳο�ʱ��
                0��TCXO Buffer�����ΪPLL�ο�ʱ��
            [6] reserved
            [5:4] WG_VCSEL
                  PLL���Ƶ�ѹ����PAD�ź�ѡ��
                  00/11�����Ƶ�ѹ����PAD����
                  01��GPLL������Ƶ�ѹ��PAD
                  10��WPLL������Ƶ�ѹ��PAD (connect to GND)
            [3:2] WG_CLK_SEL��wpll/gpll ����ʱ��ѡ��
                  PLLʱ�Ӳ���PAD�ź�ѡ��
                  00/11��ʱ�Ӳ���PAD����
                  01��GPLL���ʱ�ӵ�PAD
                  10��WPLL���ʱ�ӵ�PAD
            [1:0] CLK_PADF_SEL������ʱ��ѡ��
                  [1] 0��GPLL�Ĳ���Ƶ��Ϊ312M��Ĭ�ϣ�
                      1��GPLL�Ĳ���Ƶ��Ϊ156M
                  [0] (NC)
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR00_ADDR                      (ABB_BASE_ADDR + 0x880)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7] reserved
            [6:4] FN_GPLL_SEL
                  Gģ����PLLѡ��
                  0��ѡ��GPLL����Ĭ��ѡ��GPLL��
                  1��ѡ��SCPLL��
            [3] reserved
            [2:0] FN_WPLL_SEL
                  WPLL��SCPLLѡ���źš�
                  0��ѡ��SCPLL����Ĭ�ϣ�
                  1��ѡ��WPLL��
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR01_ADDR                      (ABB_BASE_ADDR + 0x881)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:6] reserved
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR02_ADDR                      (ABB_BASE_ADDR + 0x882)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:6] reserved
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR03_ADDR                      (ABB_BASE_ADDR + 0x883)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7] GPLL_CLK104M_PD gpll 104Mʱ��power down����
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR04_ADDR                      (ABB_BASE_ADDR + 0x884)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR05_ADDR                      (ABB_BASE_ADDR + 0x885)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:6] reserved
            [5] CH0_DAC_CLK_EN��ch0 dacʱ�����ʹ��
                  0��ʱ�ӹر�
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR06_ADDR                      (ABB_BASE_ADDR + 0x886)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:6] reserved
            [5] CH1_DAC_CLK_EN��ch1 dacʱ�����ʹ��
                  0��ʱ�ӹر�
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR07_ADDR                      (ABB_BASE_ADDR + 0x887)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR08_ADDR                      (ABB_BASE_ADDR + 0x888)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:2] reserved
            [1:0] CH0_TCXO_DRV��ch0 TCXO BUFFER��������
                  00��1x
                  01��2x
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR09_ADDR                      (ABB_BASE_ADDR + 0x889)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:5] reserved
            [4] EXCLK_PD�����ʱ��power down����
                  0�������ʱ��ģ��
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR10_ADDR                      (ABB_BASE_ADDR + 0x88A)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:5] reserved
            [4] GPLL_LOCK_EN��gpll���lock�ź�ʹ��
                  0����������lock�ź�
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR11_ADDR                      (ABB_BASE_ADDR + 0x88B)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:5] reserved
            [4] REF_FS_EN��ref������������
                 0���ر�(Ĭ��)
                 1������
            [3] reserved
            [1] BG_PD��Refence��ѹģ��ǿ��PD�ź�
                0�� Reference��ѹģ��״̬��BG_EN�źż�����ģ��PD�ź��Զ�����
                1�� Reference��ѹģ��ǿ��Power Down
            [0] BG_EN��Refence��ѹģ��ǿ��EN�ź�
                0�� Reference��ѹģ��״̬��BG_PD�źż�����ģ��PD�ź��Զ�����
                1�� ��BG_EN�ź�Ϊ1ʱ��Reference��ѹģ��ǿ������
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR12_ADDR                      (ABB_BASE_ADDR + 0x88C)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:5] reserved
            [4] RCTUNE_CAP_SEL��rctune����ѡ��
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR13_ADDR                      (ABB_BASE_ADDR + 0x88D)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:6] reserved
            [5:4] GFREF_SEL
                  GPLL����ʱ��Ƶ��ѡ��
                  00��26M
                  01��19.2M(Ĭ��)
                  10��52M
                  11��38.4M
            [3:0] CLK_IBIAS_CTRL
                  PLL�ܵ�������(����Ч)
                  0000��1u
                  0001��1.5u
                  0010��2u
                  0011��2.5u
                  0100��3u
                  0101��3.5u
                  0110��4u
                  0111��4.5u
                  1000��5u(Ĭ��)
                  ����
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR14_ADDR                      (ABB_BASE_ADDR + 0x88E)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7] reserved
            [6:4] ITR_VCM_BIAS:
            L/W/G ����ADC ���buffer�������ڿ���
            000��5u
            001��4u
            010��3u
            011��2u
            100��9u
            101��8u
            110��7u
            111��6u
            [3] reserved
            [2:0] CH0_ITR_ADC_BUF:
            L/W/G ����ADC ���buffer�������ڿ���
            000��5u
            001��4u
            010��3u
            011��2u
            100��9u
            101��8u
            110��7u
            111��6u

   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR15_ADDR                      (ABB_BASE_ADDR + 0x88F)

/* �Ĵ���˵����tuning_val_en
   ��      ����[7:1] reversed
            [0] tuning_val_en: Tuning code��Դѡ��
                0���Ĵ������ã�Ĭ�ϣ�
                1���Զ�����
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR16_ADDR                      (ABB_BASE_ADDR + 0x890)

/* �Ĵ���˵����RX RCTUNE���üĴ���
   ��      ����[7] reversed
            [6:0] RX_RCTUNE ��RX TUNE RCУ׼ֵ
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR17_ADDR                      (ABB_BASE_ADDR + 0x891)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR18_ADDR                      (ABB_BASE_ADDR + 0x892)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR19_ADDR                      (ABB_BASE_ADDR + 0x893)

/* �Ĵ���˵����ģ��commonֻ���Ĵ���
   ��      ����[7:1] reversed
            [0]  RC_TUNE_READY ��RCУ׼����ź�
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_RO00_ADDR                      (ABB_BASE_ADDR + 0x8A0)

/* �Ĵ���˵����ģ��commonֻ���Ĵ���
   ��      ����[7] reversed
            [6:0] RC_TUNE_DOUT ��RCУ׼ֵ
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_RO01_ADDR                      (ABB_BASE_ADDR + 0x8A1)

/* �Ĵ���˵����ģ��commonֻ���Ĵ���
   ��      ����[7] CH1_OPCAL_OK_RXB_Q��ch1 rxb q·op1У׼����ź�
            [6] CH1_OPCAL_OK_RXB_I��ch1 rxb i·op1У׼����ź�
            [5] CH1_OPCAL_OK_RXA_Q��ch1 rxa q·op1У׼����ź�
            [4] CH1_OPCAL_OK_RXA_I��ch1 rxa i·op1У׼����ź�
            [3] CH0_OPCAL_OK_RXB_Q��ch0 rxb q·op1У׼����ź�
            [2] CH0_OPCAL_OK_RXB_I��ch0 rxb i·op1У׼����ź�
            [1] CH0_OPCAL_OK_RXA_Q��ch0 rxa q·op1У׼����ź�
            [0] CH0_OPCAL_OK_RXA_I��ch0 rxa i·op1У׼����ź�
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_RO02_ADDR                      (ABB_BASE_ADDR + 0x8A2)

/* �Ĵ���˵����ģ��commonֻ���Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_RO03_ADDR                      (ABB_BASE_ADDR + 0x8A3)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH0_PD_TX_I��ch0 tx i·power down����
                  0: power ON
   UNION�ṹ ���� */
#define ABB_CH0_TX_2G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xA00)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR01
   ��      ����[7] reserved
            [6:4] CH0_TX_FC��ch0 tx fcѡ��
                  000��20MHz
                  001��40MHz
                  010��13.5MHz
                  011��27MHz
                  100��10MHz(Ĭ��)
                  101��20MHz
                  110��41MHz
                  111��78MHz
                Ĭ�����÷�����
                  CA:001   LTE:101 Others:100
            [3:2] CH0_TX_DIV_MODE��ch0 tx divģʽѡ��
                  00:1��Ƶ��Ĭ�ϣ�
                  01��2��Ƶ
                  10��8��Ƶ
                  11��4��Ƶ
            [1:0] CH0_TX_LPF_MODE��ch0 tx LPF�˷�ƫ�õ�������
                  00��   10u
                  01��    8u
                  10��    5u
                  11��    3u
                Ĭ�����÷�����
                  CA:00   LTE:10   Others:11
   UNION�ṹ ���� */
#define ABB_CH0_TX_2G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA01)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR02
   ��      ����[7] CH0_TX_CLKD_CTRL��ch0 tx����ʱ�ӿ���
   UNION�ṹ ���� */
#define ABB_CH0_TX_2G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA02)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR03
   ��      ����[7:0] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION�ṹ ���� */
#define ABB_CH0_TX_2G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA03)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_2G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA04)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_2G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA05)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_2G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA06)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_2G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA07)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH0_PD_TX_I��ch0 tx i·power down����
                  0: power ON
   UNION�ṹ ���� */
#define ABB_CH0_TX_3G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xA08)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR01
   ��      ����[7] reserved
            [6:4] CH0_TX_FC��ch0 tx fcѡ��
                  000��20MHz
                  001��40MHz
                  010��13.5MHz
                  011��27MHz
                  100��10MHz(Ĭ��)
                  101��20MHz
                  110��41MHz
                  111��78MHz
                Ĭ�����÷�����
                  CA:001   LTE:101 Others:100
            [3:2] CH0_TX_DIV_MODE��ch0 tx divģʽѡ��
                  00:1��Ƶ��Ĭ�ϣ�
                  01��2��Ƶ
                  10��8��Ƶ
                  11��4��Ƶ
            [1:0] CH0_TX_LPF_MODE��ch0 tx LPF�˷�ƫ�õ�������
                  00��   10u
                  01��    8u
                  10��    5u
                  11��    3u
                Ĭ�����÷�����
                  CA:00   LTE:10   Others:11
   UNION�ṹ ���� */
#define ABB_CH0_TX_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA09)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR02
   ��      ����[7] CH0_TX_CLKD_CTRL��ch0 tx����ʱ�ӿ���
   UNION�ṹ ���� */
#define ABB_CH0_TX_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA0A)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR03
   ��      ����[7:0] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION�ṹ ���� */
#define ABB_CH0_TX_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA0B)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA0C)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA0D)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA0E)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA0F)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH0_PD_TX_I��ch0 tx i·power down����
                  0: power ON
   UNION�ṹ ���� */
#define ABB_CH0_TX_4G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xA10)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR01
   ��      ����[7] reserved
            [6:4] CH0_TX_FC��ch0 tx fcѡ��
                  000��20MHz
                  001��40MHz
                  010��13.5MHz
                  011��27MHz
                  100��10MHz(Ĭ��)
                  101��20MHz
                  110��41MHz
                  111��78MHz
                Ĭ�����÷�����
                  CA:001   LTE:101 Others:100
            [3:2] CH0_TX_DIV_MODE��ch0 tx divģʽѡ��
                  00:1��Ƶ��Ĭ�ϣ�
                  01��2��Ƶ
                  10��8��Ƶ
                  11��4��Ƶ
            [1:0] CH0_TX_LPF_MODE��ch0 tx LPF�˷�ƫ�õ�������
                  00��   10u
                  01��    8u
                  10��    5u
                  11��    3u
                Ĭ�����÷�����
                  CA:00   LTE:10   Others:11
   UNION�ṹ ���� */
#define ABB_CH0_TX_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA11)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR02
   ��      ����[7] CH0_TX_CLKD_CTRL��ch0 tx����ʱ�ӿ���
   UNION�ṹ ���� */
#define ABB_CH0_TX_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA12)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR03
   ��      ����[7:2] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION�ṹ ���� */
#define ABB_CH0_TX_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA13)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA14)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA15)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA16)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA17)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH0_PD_TX_I��ch0 tx i·power down����
                  0: power ON
   UNION�ṹ ���� */
#define ABB_CH0_TX_TDS_ANA_0_ADDR                     (ABB_BASE_ADDR + 0xA18)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR01
   ��      ����[7] reserved
            [6:4] CH0_TX_FC��ch0 tx fcѡ��
                  000��20MHz
                  001��40MHz
                  010��13.5MHz
                  011��27MHz
                  100��10MHz(Ĭ��)
                  101��20MHz
                  110��41MHz
                  111��78MHz
                Ĭ�����÷�����
                  CA:001   LTE:101 Others:100
            [3:2] CH0_TX_DIV_MODE��ch0 tx divģʽѡ��
                  00:1��Ƶ��Ĭ�ϣ�
                  01��2��Ƶ
                  10��8��Ƶ
                  11��4��Ƶ
            [1:0] CH0_TX_LPF_MODE��ch0 tx LPF�˷�ƫ�õ�������
                  00��   10u
                  01��    8u
                  10��    5u
                  11��    3u
                Ĭ�����÷�����
                  CA:00   LTE:10   Others:11
   UNION�ṹ ���� */
#define ABB_CH0_TX_TDS_ANA_1_ADDR                     (ABB_BASE_ADDR + 0xA19)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR02
   ��      ����[7] CH0_TX_CLKD_CTRL��ch0 tx����ʱ�ӿ���
   UNION�ṹ ���� */
#define ABB_CH0_TX_TDS_ANA_2_ADDR                     (ABB_BASE_ADDR + 0xA1A)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR03
   ��      ����[7:2] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION�ṹ ���� */
#define ABB_CH0_TX_TDS_ANA_3_ADDR                     (ABB_BASE_ADDR + 0xA1B)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_TDS_ANA_4_ADDR                     (ABB_BASE_ADDR + 0xA1C)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_TDS_ANA_5_ADDR                     (ABB_BASE_ADDR + 0xA1D)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_TDS_ANA_6_ADDR                     (ABB_BASE_ADDR + 0xA1E)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_TDS_ANA_7_ADDR                     (ABB_BASE_ADDR + 0xA1F)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH0_PD_TX_I��ch0 tx i·power down����
                  0: power ON
   UNION�ṹ ���� */
#define ABB_CH0_TX_X_ANA_0_ADDR                       (ABB_BASE_ADDR + 0xA20)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR01
   ��      ����[7] reserved
            [6:4] CH0_TX_FC��ch0 tx fcѡ��
                  000��20MHz
                  001��40MHz
                  010��13.5MHz
                  011��27MHz
                  100��10MHz(Ĭ��)
                  101��20MHz
                  110��41MHz
                  111��78MHz
                Ĭ�����÷�����
                  CA:001   LTE:101 Others:100
            [3:2] CH0_TX_DIV_MODE��ch0 tx divģʽѡ��
                  00:1��Ƶ��Ĭ�ϣ�
                  01��2��Ƶ
                  10��8��Ƶ
                  11��4��Ƶ
            [1:0] CH0_TX_LPF_MODE��ch0 tx LPF�˷�ƫ�õ�������
                  00��   10u
                  01��    8u
                  10��    5u
                  11��    3u
                Ĭ�����÷�����
                  CA:00   LTE:10   Others:11
   UNION�ṹ ���� */
#define ABB_CH0_TX_X_ANA_1_ADDR                       (ABB_BASE_ADDR + 0xA21)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR02
   ��      ����[7] CH0_TX_CLKD_CTRL��ch0 tx����ʱ�ӿ���
   UNION�ṹ ���� */
#define ABB_CH0_TX_X_ANA_2_ADDR                       (ABB_BASE_ADDR + 0xA22)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR03
   ��      ����[7:2] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION�ṹ ���� */
#define ABB_CH0_TX_X_ANA_3_ADDR                       (ABB_BASE_ADDR + 0xA23)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_X_ANA_4_ADDR                       (ABB_BASE_ADDR + 0xA24)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_X_ANA_5_ADDR                       (ABB_BASE_ADDR + 0xA25)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_X_ANA_6_ADDR                       (ABB_BASE_ADDR + 0xA26)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_X_ANA_7_ADDR                       (ABB_BASE_ADDR + 0xA27)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH0_PD_TX_I��ch0 tx i·power down����
                  0: power ON
   UNION�ṹ ���� */
#define ABB_CH0_TX_IDLE_ANA_0_ADDR                    (ABB_BASE_ADDR + 0xA28)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR01
   ��      ����[7] reserved
            [6:4] CH0_TX_FC��ch0 tx fcѡ��
                  000��20MHz
                  001��40MHz
                  010��13.5MHz
                  011��27MHz
                  100��10MHz(Ĭ��)
                  101��20MHz
                  110��41MHz
                  111��78MHz
                Ĭ�����÷�����
                  CA:001   LTE:101 Others:100
            [3:2] CH0_TX_DIV_MODE��ch0 tx divģʽѡ��
                  00:1��Ƶ��Ĭ�ϣ�
                  01��2��Ƶ
                  10��8��Ƶ
                  11��4��Ƶ
            [1:0] CH0_TX_LPF_MODE��ch0 tx LPF�˷�ƫ�õ�������
                  00��   10u
                  01��    8u
                  10��    5u
                  11��    3u
                Ĭ�����÷�����
                  CA:00   LTE:10   Others:11
   UNION�ṹ ���� */
#define ABB_CH0_TX_IDLE_ANA_1_ADDR                    (ABB_BASE_ADDR + 0xA29)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR02
   ��      ����[7] CH0_TX_CLKD_CTRL��ch0 tx����ʱ�ӿ���
   UNION�ṹ ���� */
#define ABB_CH0_TX_IDLE_ANA_2_ADDR                    (ABB_BASE_ADDR + 0xA2A)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR03
   ��      ����[7:2] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION�ṹ ���� */
#define ABB_CH0_TX_IDLE_ANA_3_ADDR                    (ABB_BASE_ADDR + 0xA2B)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_IDLE_ANA_4_ADDR                    (ABB_BASE_ADDR + 0xA2C)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_IDLE_ANA_5_ADDR                    (ABB_BASE_ADDR + 0xA2D)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_IDLE_ANA_6_ADDR                    (ABB_BASE_ADDR + 0xA2E)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_IDLE_ANA_7_ADDR                    (ABB_BASE_ADDR + 0xA2F)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH1_PD_TX_I��ch1 tx i·power down����
                  0: power ON
   UNION�ṹ ���� */
#define ABB_CH1_TX_2G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xA40)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR01
   ��      ����[7] reserved
            [6:4] CH1_TX_FC��ch1 tx fcѡ��
                  000��20MHz
                  001��40MHz
                  010��13.5MHz
                  011��27MHz
                  100��10MHz(Ĭ��)
                  101��20MHz
                  110��41MHz
                  111��78MHz
                Ĭ�����÷�����
                  CA:001   LTE:101 Others:100
            [3:2] CH1_TX_DIV_MODE��ch0 tx divģʽѡ��
                  00:1��Ƶ��Ĭ�ϣ�
                  01��2��Ƶ
                  10��8��Ƶ
                  11��4��Ƶ
            [1:0] CH1_TX_LPF_MODE��ch0 tx LPF�˷�ƫ�õ�������
                  00��   10u
                  01��    8u
                  10��    5u
                  11��    3u
                Ĭ�����÷�����
                  CA:00   LTE:10   Others:11
   UNION�ṹ ���� */
#define ABB_CH1_TX_2G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA41)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR02
   ��      ����[7] CH0_TX_CLKD_CTRL��ch0 tx����ʱ�ӿ���
   UNION�ṹ ���� */
#define ABB_CH1_TX_2G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA42)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR03
   ��      ����[7:2] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION�ṹ ���� */
#define ABB_CH1_TX_2G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA43)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_2G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA44)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_2G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA45)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_2G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA46)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_2G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA47)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH1_PD_TX_I��ch1 tx i·power down����
                  0: power ON
   UNION�ṹ ���� */
#define ABB_CH1_TX_3G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xA48)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR01
   ��      ����[7] reserved
            [6:4] CH1_TX_FC��ch0 tx fcѡ��
                  000��20MHz
                  001��40MHz
                  010��13.5MHz
                  011��27MHz
                  100��10MHz(Ĭ��)
                  101��20MHz
                  110��41MHz
                  111��78MHz
                Ĭ�����÷�����
                  CA:001   LTE:101 Others:100
            [3:2] CH1_TX_DIV_MODE��ch0 tx divģʽѡ��
                  00:1��Ƶ��Ĭ�ϣ�
                  01��2��Ƶ
                  10��8��Ƶ
                  11��4��Ƶ
            [1:0] CH1_TX_LPF_MODE��ch0 tx LPF�˷�ƫ�õ�������
                  00��   10u
                  01��    8u
                  10��    5u
                  11��    3u
                Ĭ�����÷�����
                  CA:00   LTE:10   Others:11
   UNION�ṹ ���� */
#define ABB_CH1_TX_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA49)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR02
   ��      ����[7] CH1_TX_CLKD_CTRL��ch1 tx����ʱ�ӿ���
   UNION�ṹ ���� */
#define ABB_CH1_TX_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA4A)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR03
   ��      ����[7:0] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION�ṹ ���� */
#define ABB_CH1_TX_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA4B)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA4C)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA4D)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA4E)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA4F)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH1_PD_TX_I��ch1 tx i·power down����
                  0: power ON
   UNION�ṹ ���� */
#define ABB_CH1_TX_4G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xA50)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR01
   ��      ����[7] reserved
            [6:4] CH1_TX_FC��ch0 tx fcѡ��
                  000��20MHz
                  001��40MHz
                  010��13.5MHz
                  011��27MHz
                  100��10MHz(Ĭ��)
                  101��20MHz
                  110��41MHz
                  111��78MHz
                Ĭ�����÷�����
                  CA:001   LTE:101 Others:100
            [3:2] CH1_TX_DIV_MODE��ch0 tx divģʽѡ��
                  00:1��Ƶ��Ĭ�ϣ�
                  01��2��Ƶ
                  10��8��Ƶ
                  11��4��Ƶ
            [1:0] CH1_TX_LPF_MODE��ch0 tx LPF�˷�ƫ�õ�������
                  00��   10u
                  01��    8u
                  10��    5u
                  11��    3u
                Ĭ�����÷�����
                  CA:00   LTE:10   Others:11
   UNION�ṹ ���� */
#define ABB_CH1_TX_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA51)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR02
   ��      ����[7] CH1_TX_CLKD_CTRL��ch1 tx����ʱ�ӿ���
   UNION�ṹ ���� */
#define ABB_CH1_TX_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA52)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR03
   ��      ����[7:0] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION�ṹ ���� */
#define ABB_CH1_TX_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA53)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA54)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA55)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA56)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA57)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH1_PD_TX_I��ch1 tx i·power down����
                  0: power ON
   UNION�ṹ ���� */
#define ABB_CH1_TX_TDS_ANA_0_ADDR                     (ABB_BASE_ADDR + 0xA58)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR01
   ��      ����[7] reserved
            [6:4] CH1_TX_FC��ch0 tx fcѡ��
                  000��20MHz
                  001��40MHz
                  010��13.5MHz
                  011��27MHz
                  100��10MHz(Ĭ��)
                  101��20MHz
                  110��41MHz
                  111��78MHz
                Ĭ�����÷�����
                  CA:001   LTE:101 Others:100
            [3:2] CH1_TX_DIV_MODE��ch0 tx divģʽѡ��
                  00:1��Ƶ��Ĭ�ϣ�
                  01��2��Ƶ
                  10��8��Ƶ
                  11��4��Ƶ
            [1:0] CH1_TX_LPF_MODE��ch0 tx LPF�˷�ƫ�õ�������
                  00��   10u
                  01��    8u
                  10��    5u
                  11��    3u
                Ĭ�����÷�����
                  CA:00   LTE:10   Others:11
   UNION�ṹ ���� */
#define ABB_CH1_TX_TDS_ANA_1_ADDR                     (ABB_BASE_ADDR + 0xA59)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR02
   ��      ����[7] CH1_TX_CLKD_CTRL��ch1 tx����ʱ�ӿ���
   UNION�ṹ ���� */
#define ABB_CH1_TX_TDS_ANA_2_ADDR                     (ABB_BASE_ADDR + 0xA5A)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR03
   ��      ����[7:0] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION�ṹ ���� */
#define ABB_CH1_TX_TDS_ANA_3_ADDR                     (ABB_BASE_ADDR + 0xA5B)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_TDS_ANA_4_ADDR                     (ABB_BASE_ADDR + 0xA5C)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_TDS_ANA_5_ADDR                     (ABB_BASE_ADDR + 0xA5D)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_TDS_ANA_6_ADDR                     (ABB_BASE_ADDR + 0xA5E)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_TDS_ANA_7_ADDR                     (ABB_BASE_ADDR + 0xA5F)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH1_PD_TX_I��ch1 tx i·power down����
                  0: power ON
   UNION�ṹ ���� */
#define ABB_CH1_TX_X_ANA_0_ADDR                       (ABB_BASE_ADDR + 0xA60)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR01
   ��      ����[7] reserved
            [6:4] CH1_TX_FC��ch0 tx fcѡ��
                  000��20MHz
                  001��40MHz
                  010��13.5MHz
                  011��27MHz
                  100��10MHz(Ĭ��)
                  101��20MHz
                  110��41MHz
                  111��78MHz
                Ĭ�����÷�����
                  CA:001   LTE:101 Others:100
            [3:2] CH1_TX_DIV_MODE��ch0 tx divģʽѡ��
                  00:1��Ƶ��Ĭ�ϣ�
                  01��2��Ƶ
                  10��8��Ƶ
                  11��4��Ƶ
            [1:0] CH1_TX_LPF_MODE��ch0 tx LPF�˷�ƫ�õ�������
                  00��   10u
                  01��    8u
                  10��    5u
                  11��    3u
                Ĭ�����÷�����
                  CA:00   LTE:10   Others:11
   UNION�ṹ ���� */
#define ABB_CH1_TX_X_ANA_1_ADDR                       (ABB_BASE_ADDR + 0xA61)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR02
   ��      ����[7] CH1_TX_CLKD_CTRL��ch1 tx����ʱ�ӿ���
   UNION�ṹ ���� */
#define ABB_CH1_TX_X_ANA_2_ADDR                       (ABB_BASE_ADDR + 0xA62)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR03
   ��      ����[7:0] reserved
            [1] DUM_EN_Q
            [0] DUM_EN_I
   UNION�ṹ ���� */
#define ABB_CH1_TX_X_ANA_3_ADDR                       (ABB_BASE_ADDR + 0xA63)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_X_ANA_4_ADDR                       (ABB_BASE_ADDR + 0xA64)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_X_ANA_5_ADDR                       (ABB_BASE_ADDR + 0xA65)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_X_ANA_6_ADDR                       (ABB_BASE_ADDR + 0xA66)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_X_ANA_7_ADDR                       (ABB_BASE_ADDR + 0xA67)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH1_PD_TX_I��ch1 tx i·power down����
                  0: power ON
   UNION�ṹ ���� */
#define ABB_CH1_TX_IDLE_ANA_0_ADDR                    (ABB_BASE_ADDR + 0xA68)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR01
   ��      ����[7] reserved
            [6:4] CH1_TX_FC��ch0 tx fcѡ��
                  000��20MHz
                  001��40MHz
                  010��13.5MHz
                  011��27MHz
                  100��10MHz(Ĭ��)
                  101��20MHz
                  110��41MHz
                  111��78MHz
                Ĭ�����÷�����
                  CA:001   LTE:101 Others:100
            [3:2] CH1_TX_DIV_MODE��ch0 tx divģʽѡ��
                  00:1��Ƶ��Ĭ�ϣ�
                  01��2��Ƶ
                  10��8��Ƶ
                  11��4��Ƶ
            [1:0] CH1_TX_LPF_MODE��ch0 tx LPF�˷�ƫ�õ�������
                  00��   10u
                  01��    8u
                  10��    5u
                  11��    3u
                Ĭ�����÷�����
                  CA:00   LTE:10   Others:11
   UNION�ṹ ���� */
#define ABB_CH1_TX_IDLE_ANA_1_ADDR                    (ABB_BASE_ADDR + 0xA69)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR02
   ��      ����[7] CH1_TX_CLKD_CTRL��ch1 tx����ʱ�ӿ���
   UNION�ṹ ���� */
#define ABB_CH1_TX_IDLE_ANA_2_ADDR                    (ABB_BASE_ADDR + 0xA6A)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR03
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_IDLE_ANA_3_ADDR                    (ABB_BASE_ADDR + 0xA6B)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_IDLE_ANA_4_ADDR                    (ABB_BASE_ADDR + 0xA6C)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_IDLE_ANA_5_ADDR                    (ABB_BASE_ADDR + 0xA6D)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_IDLE_ANA_6_ADDR                    (ABB_BASE_ADDR + 0xA6E)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_IDLE_ANA_7_ADDR                    (ABB_BASE_ADDR + 0xA6F)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR08
   ��      ����[7] CH0_PD_RXA_I��ch0 rxa i·power down����
            [6] CH0_PD_RXA_Q��ch0 rxa q·power down����
            [5] CH0_PD_RXB_I��ch0 rxb i·power down����
            [4] CH0_PD_RXB_Q��ch0 rxb q·power down����
            [3] reserved
            [2:0] CH0_RX_MODE��ch0 rxģʽѡ��
                  000��4G
                  001��3G
                  010��3G_DC &amp; TDS
                  011��2G_A(Ĭ��)
                  100��CA
                  101��CDMA
                  110:2G_B
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xC00)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH0_MODE_IBCT3��ch0 op3ģʽѡ��
            [3:2] CH0_MODE_IBCT2��ch0 op2ģʽѡ��
            [1:0] CH0_MODE_IBCT1��ch0 op1ģʽѡ��
                  OP1/OP2/OP3 Current Seting For Mode
                  11��CA mode Current
                  10��LTE mode Current
                  01��DC/TDS/X/2G_B mode Current
                  00��3G/2G_A mode Current
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xC01)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR10
   ��      ����[7:6] reserved
            [5] PDM_CTRL: RX ADC���������ģʽѡ��
                1��Binary Encoder
                0��Add Encoder��default��
            [4] DEM_OUTPUT_SEL: DEM�����߼�����
                0��DEM_IN ADD
                1��DEM_IN ENC
            [3] DEM_ENB: ADC DEM���ܹر��ź�
                0��DEM Enable
                1��DEM Disable
            [2:0] DEM mode
                  RX ADC��DAC DEMģʽѡ��
                  000��DWA��default��
                  001��CLA1
                  010��CLA2
                  011��CLA3
                  100��CLA4
                  101��CLA5
                  110��CLA6
                  111��CLA7
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xC02)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR11
   ��      ����[7:6] CH0_CTRL_RFF��ch0 ǰ������rffѡ��
                  RXģʽ���ƻ�����ǰ������RFF
                  1x��4.865K ohm CA/4G/DC/TDS/X
                  01��9.73K ohm 2G_B
                  00��19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1��ch0 ������1�������rin1ѡ��
                  RXģʽ���ƻ�������һ���������RIN1
                  11��2.8K ohm 2G_B
                  10��5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01��5.6K ohm
                  00��cut off
            [3:2] CH0_CTRL_RIN2��ch0 ������2�������rin2ѡ��
                  RXģʽ���ƻ������ڶ����������RIN2
                  1x��16.6K ohm CA/4G/DC/TDS/X
                  01��33.2K ohm 2G_B
                  00��66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3��ch0 ������3�������rin3ѡ��
                RXģʽ���ƻ������������������RIN3
                1��6.93K ohm CA/4G/DC/TDS/X/2G_B
                0��13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB��ch0 ��������������rfbѡ��
                RXģʽ���ƻ�������������RFB
                1��160K ohm CA/4G/DC/TDS/X/2G_B
                0��320K ohm 3G/2G_A
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xC03)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH0_CTRL_RSIG��ch0 �������ź�ǰ������rsigѡ��
                  RXģʽ���ƻ������ź�ǰ������RSIG
                  1x��46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01��93K ohm 3G/2G_A
                  00��cut off
            [3:0] CH0_CTRL_RZ��ch0 ������3�������rzѡ��
                  RXģʽ���ƻ������������������ݵ������RZ
                  x000��500 ohm��default��
                  x100��167 ohm
                  x010��143 ohm
                  x110��90 ohm
                  xxx1��0 ohm
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xC04)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR13
   ��      ����[7:3] reserved
            [2] CH0_DLY_CTRL2��ch0 0.6tsʱ�����ڿ���ѡ��
                RX ADC 0.6Tsʱ�����
                1��DAC3��ʱ0.6Ts
                0��DAC3��ʱ0.5Ts ��default��
            [1] CH0_DCTRL23��ch0 dac23����ģʽѡ��
                RXģʽ����DAC23������������
                1��Double icell23 current CA/4G/DC/TDS/X/2G_B
                0��Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1��ch0 dac1����ģʽѡ��
                RXģʽ����DAC1������������
                1��Double icell1 current 2G_B
                0��Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xC05)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR14
   ��      ����[7] reserved
            [6:4] CH0_IBCT_QT��ch0 rx QT������С����
                  RX ADC QTƫ�õ�������
                  000�� 5u CA
                  001�� 4u 4G
                  010�� 3u WDC/TDS/2G_B/X
                  011�� 2u 3G/2G_A
                  100�� 10u
                  101�� 9u
                  110�� 8u
                  111�� 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE��ch0 ����������capģʽѡ��
                  RX Integrator Cap Setting For Mode:
                  1x��DC/TDS/X/2G_B/3G/2G_A
                  01��4G
                  00��CA
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xC06)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH0_IBCT_OP2��ch0 rx op2������С����
            RX ADC OP2ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1��ch0 rx op1������С����
            RX ADC OP1ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xC07)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH0_IBCT_DAC��ch0 rx dac������С����
            RX ADC DACƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3��ch0 rx op3������С����
            RX ADC OP3ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xC08)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR17
   ��      ����[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3��ch0 rx������3����cap3�˻�����ѡ��
            RX Integrator Cap3 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
            [1:0] CH0_MULTI_RATE_CAP12��ch0 rx������1����cap1�˻�����ѡ��
            RX Integrator Cap12 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xC09)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR18
   ��      ����[7] CH0_RXA_DCLK_INV��ch0 rxa dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [6] CH0_RXB_DCLK_INV��ch0 rxb dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [5] CH0_CLKDIV2_A2D��ch0 rx a2d clock����Ƶѡ��
                ��������ֵ�ʱ��MCLK�Ķ���Ƶ����
                0������Ƶ CA/2G_A/2G_B
                1������Ƶ 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX��ch0 rx clock����Ƶѡ��
                �����RXADC��ͨ·��ʱ�ӵĶ���Ƶ����
                0������Ƶ 3G
                1������Ƶ CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV��ch0 rx a2d clock����ѡ��
                ��������ֵ�ʱ��MCLK�������ؿ���
                0������(default)
                1������
            [2:0] CH0_CLKMUX_CTRL��ch0 rx ģʽ��Ƶʱ��ѡ��
                  �ṩ���ϵ�ģ���ʱ�ӵķ�Ƶ����
                  000�� CAģʽ
                  100�� 4Gģʽ
                  110�� WDC/TDS/2G_B/Xģʽ
                  111:3G/2G_Aģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xC0A)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR19
   ��      ����[7:4] CH0_RXA_CLK_QT_CTRL��ch0 rxa qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xC0B)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR20
   ��      ����[7:2] reserved
            [1:0] RX_DLY_CTRL��RXA ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xC0C)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR21
   ��      ����[7:4] CH0_RXB_CLK_QT_CTRL��ch0 rxb qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xC0D)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR22
   ��      ����[7:2] reserved
            [1:0] RX_DLY_CTRL��RXB ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xC0E)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR23
   ��      ����[7] CH0_CLKIN3_INV_RXB_Q��ch0 rxb q·clkin3 dff�����ؿ��� 0������ 1������
            [6] CH0_CLKIN3_INV_RXB_I��ch0 rxb i·clkin3 dff�����ؿ��� 0������ 1������
            [5] CH0_CLKIN2_INV_RXB_Q��ch0 rxb q·clkin2 dff�����ؿ��� 0������ 1������
            [4] CH0_CLKIN2_INV_RXB_I��ch0 rxb i·clkin2 dff�����ؿ��� 0������ 1������
            [3] CH0_CLKIN3_INV_RXA_Q��ch0 rxa q·clkin3 dff�����ؿ��� 0������ 1������
            [2] CH0_CLKIN3_INV_RXA_I��ch0 rxa i·clkin3 dff�����ؿ��� 0������ 1������
            [1] CH0_CLKIN2_INV_RXA_Q��ch0 rxa q·clkin2 dff�����ؿ��� 0������ 1������
            [0] CH0_CLKIN2_INV_RXA_I��ch0 rxa i·clkin2 dff�����ؿ��� 0������ 1������
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xC0F)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR08
   ��      ����[7] CH0_PD_RXA_I��ch0 rxa i·power down����
            [6] CH0_PD_RXA_Q��ch0 rxa q·power down����
            [5] CH0_PD_RXB_I��ch0 rxb i·power down����
            [4] CH0_PD_RXB_Q��ch0 rxb q·power down����
            [3] reserved
            [2:0] CH0_RX_MODE��ch0 rxģʽѡ��
                  000��4G
                  001��3G (Ĭ��)
                  010��3G_DC &amp; TDS
                  011��2G_A
                  100��CA
                  101��CDMA
                  110:2G_B
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xC10)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH0_MODE_IBCT3��ch0 op3ģʽѡ��
            [3:2] CH0_MODE_IBCT2��ch0 op2ģʽѡ��
            [1:0] CH0_MODE_IBCT1��ch0 op1ģʽѡ��
                  OP1/OP2/OP3 Current Seting For Mode
                  11��CA mode Current
                  10��LTE mode Current
                  01��DC/TDS/X/2G_B mode Current
                  00��3G/2G_A mode Current
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xC11)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR10
   ��      ����[7:6] reserved
            [5] PDM_CTRL: RX ADC���������ģʽѡ��
                1��Binary Encoder
                0��Add Encoder��default��
            [4] DEM_OUTPUT_SEL: DEM�����߼�����
                0��DEM_IN ADD
                1��DEM_IN ENC
            [3] DEM_ENB: ADC DEM���ܹر��ź�
                0��DEM Enable
                1��DEM Disable
            [2:0] DEM mode
                  RX ADC��DAC DEMģʽѡ��
                  000��DWA��default��
                  001��CLA1
                  010��CLA2
                  011��CLA3
                  100��CLA4
                  101��CLA5
                  110��CLA6
                  111��CLA7
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xC12)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR11
   ��      ����[7:6] CH0_CTRL_RFF��ch0 ǰ������rffѡ��
                  RXģʽ���ƻ�����ǰ������RFF
                  1x��4.865K ohm CA/4G/DC/TDS/X
                  01��9.73K ohm 2G_B
                  00��19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1��ch0 ������1�������rin1ѡ��
                  RXģʽ���ƻ�������һ���������RIN1
                  11��2.8K ohm 2G_B
                  10��5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01��5.6K ohm
                  00��cut off
            [3:2] CH0_CTRL_RIN2��ch0 ������2�������rin2ѡ��
                  RXģʽ���ƻ������ڶ����������RIN2
                  1x��16.6K ohm CA/4G/DC/TDS/X
                  01��33.2K ohm 2G_B
                  00��66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3��ch0 ������3�������rin3ѡ��
                RXģʽ���ƻ������������������RIN3
                1��6.93K ohm CA/4G/DC/TDS/X/2G_B
                0��13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB��ch0 ��������������rfbѡ��
                RXģʽ���ƻ�������������RFB
                1��160K ohm CA/4G/DC/TDS/X/2G_B
                0��320K ohm 3G/2G_A
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xC13)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH0_CTRL_RSIG��ch0 �������ź�ǰ������rsigѡ��
                  RXģʽ���ƻ������ź�ǰ������RSIG
                  1x��46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01��93K ohm 3G/2G_A
                  00��cut off
            [3:0] CH0_CTRL_RZ��ch0 ������3�������rzѡ��
                  RXģʽ���ƻ������������������ݵ������RZ
                  x000��500 ohm��default��
                  x100��167 ohm
                  x010��143 ohm
                  x110��90 ohm
                  xxx1��0 ohm
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xC14)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR13
   ��      ����[7:3] reserved
            [2] CH0_DLY_CTRL2��ch0 0.6tsʱ�����ڿ���ѡ��
                RX ADC 0.6Tsʱ�����
                1��DAC3��ʱ0.6Ts
                0��DAC3��ʱ0.5Ts ��default��
            [1] CH0_DCTRL23��ch0 dac23����ģʽѡ��
                RXģʽ����DAC23������������
                1��Double icell23 current CA/4G/DC/TDS/X/2G_B
                0��Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1��ch0 dac1����ģʽѡ��
                RXģʽ����DAC1������������
                1��Double icell1 current 2G_B
                0��Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xC15)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR14
   ��      ����[7] reserved
            [6:4] CH0_IBCT_QT��ch0 rx QT������С����
                  RX ADC QTƫ�õ�������
                  000�� 5u CA
                  001�� 4u 4G
                  010�� 3u WDC/TDS/2G_B/X
                  011�� 2u 3G/2G_A
                  100�� 10u
                  101�� 9u
                  110�� 8u
                  111�� 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE��ch0 ����������capģʽѡ��
                  RX Integrator Cap Setting For Mode:
                  1x��DC/TDS/X/2G_B/3G/2G_A
                  01��4G
                  00��CA
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xC16)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH0_IBCT_OP2��ch0 rx op2������С����
            RX ADC OP2ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1��ch0 rx op1������С����
            RX ADC OP1ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xC17)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH0_IBCT_DAC��ch0 rx dac������С����
            RX ADC DACƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3��ch0 rx op3������С����
            RX ADC OP3ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xC18)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR17
   ��      ����[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3��ch0 rx������3����cap3�˻�����ѡ��
            RX Integrator Cap3 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
            [1:0] CH0_MULTI_RATE_CAP12��ch0 rx������1����cap1�˻�����ѡ��
            RX Integrator Cap12 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xC19)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR18
   ��      ����[7] CH0_RXA_DCLK_INV��ch0 rxa dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [6] CH0_RXB_DCLK_INV��ch0 rxb dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [5] CH0_CLKDIV2_A2D��ch0 rx a2d clock����Ƶѡ��
                ��������ֵ�ʱ��MCLK�Ķ���Ƶ����
                0������Ƶ CA/2G_A/2G_B
                1������Ƶ 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX��ch0 rx clock����Ƶѡ��
                �����RXADC��ͨ·��ʱ�ӵĶ���Ƶ����
                0������Ƶ 3G
                1������Ƶ CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV��ch0 rx a2d clock����ѡ��
                ��������ֵ�ʱ��MCLK�������ؿ���
                0������(default)
                1������
            [2:0] CH0_CLKMUX_CTRL��ch0 rx ģʽ��Ƶʱ��ѡ��
                  �ṩ���ϵ�ģ���ʱ�ӵķ�Ƶ����
                  000�� CAģʽ
                  100�� 4Gģʽ
                  110�� WDC/TDS/2G_B/Xģʽ
                  111:3G/2G_Aģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xC1A)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR19
   ��      ����[7:4] CH0_RXA_CLK_QT_CTRL��ch0 rxa qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xC1B)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR20
   ��      ����[7:2] reserved
            [1:0] RX_DLY_CTRL��RXA ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xC1C)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR21
   ��      ����[7:4] CH0_RXB_CLK_QT_CTRL��ch0 rxb qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xC1D)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR22
   ��      ����[7:2] reserved
            [1:0] RXB ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xC1E)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR23
   ��      ����[7] CH0_CLKIN3_INV_RXB_Q��ch0 rxb q·clkin3 dff�����ؿ��� 0������ 1������
            [6] CH0_CLKIN3_INV_RXB_I��ch0 rxb i·clkin3 dff�����ؿ��� 0������ 1������
            [5] CH0_CLKIN2_INV_RXB_Q��ch0 rxb q·clkin2 dff�����ؿ��� 0������ 1������
            [4] CH0_CLKIN2_INV_RXB_I��ch0 rxb i·clkin2 dff�����ؿ��� 0������ 1������
            [3] CH0_CLKIN3_INV_RXA_Q��ch0 rxa q·clkin3 dff�����ؿ��� 0������ 1������
            [2] CH0_CLKIN3_INV_RXA_I��ch0 rxa i·clkin3 dff�����ؿ��� 0������ 1������
            [1] CH0_CLKIN2_INV_RXA_Q��ch0 rxa q·clkin2 dff�����ؿ��� 0������ 1������
            [0] CH0_CLKIN2_INV_RXA_I��ch0 rxa i·clkin2 dff�����ؿ��� 0������ 1������
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xC1F)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR08
   ��      ����[7] CH0_PD_RXA_I��ch0 rxa i·power down����
            [6] CH0_PD_RXA_Q��ch0 rxa q·power down����
            [5] CH0_PD_RXB_I��ch0 rxb i·power down����
            [4] CH0_PD_RXB_Q��ch0 rxb q·power down����
            [3] reserved
            [2:0] CH0_RX_MODE��ch0 rxģʽѡ��
                  000��4G
                  001��3G
                  010��3G_DC &amp; TDS
                  011��2G_A(Ĭ��)
                  100��CA
                  101��CDMA
                  110:2G_B
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xC20)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH0_MODE_IBCT3��ch0 op3ģʽѡ��
            [3:2] CH0_MODE_IBCT2��ch0 op2ģʽѡ��
            [1:0] CH0_MODE_IBCT1��ch0 op1ģʽѡ��
                  OP1/OP2/OP3 Current Seting For Mode
                  11��CA mode Current
                  10��LTE mode Current
                  01��DC/TDS/X/2G_B mode Current
                  00��3G/2G_A mode Current
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xC21)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR10
   ��      ����[7:6] reserved
            [5] PDM_CTRL: RX ADC���������ģʽѡ��
                1��Binary Encoder
                0��Add Encoder��default��
            [4] DEM_OUTPUT_SEL: DEM�����߼�����
                0��DEM_IN ADD
                1��DEM_IN ENC
            [3] DEM_ENB: ADC DEM���ܹر��ź�
                0��DEM Enable
                1��DEM Disable
            [2:0] DEM mode
                  RX ADC��DAC DEMģʽѡ��
                  000��DWA��default��
                  001��CLA1
                  010��CLA2
                  011��CLA3
                  100��CLA4
                  101��CLA5
                  110��CLA6
                  111��CLA7
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xC22)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR11
   ��      ����[7:6] CH0_CTRL_RFF��ch0 ǰ������rffѡ��
                  RXģʽ���ƻ�����ǰ������RFF
                  1x��4.865K ohm CA/4G/DC/TDS/X
                  01��9.73K ohm 2G_B
                  00��19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1��ch0 ������1�������rin1ѡ��
                  RXģʽ���ƻ�������һ���������RIN1
                  11��2.8K ohm 2G_B
                  10��5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01��5.6K ohm
                  00��cut off
            [3:2] CH0_CTRL_RIN2��ch0 ������2�������rin2ѡ��
                  RXģʽ���ƻ������ڶ����������RIN2
                  1x��16.6K ohm CA/4G/DC/TDS/X
                  01��33.2K ohm 2G_B
                  00��66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3��ch0 ������3�������rin3ѡ��
                RXģʽ���ƻ������������������RIN3
                1��6.93K ohm CA/4G/DC/TDS/X/2G_B
                0��13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB��ch0 ��������������rfbѡ��
                RXģʽ���ƻ�������������RFB
                1��160K ohm CA/4G/DC/TDS/X/2G_B
                0��320K ohm 3G/2G_A
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xC23)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH0_CTRL_RSIG��ch0 �������ź�ǰ������rsigѡ��
                  RXģʽ���ƻ������ź�ǰ������RSIG
                  1x��46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01��93K ohm 3G/2G_A
                  00��cut off
            [3:0] CH0_CTRL_RZ��ch0 ������3�������rzѡ��
                  RXģʽ���ƻ������������������ݵ������RZ
                  x000��500 ohm��default��
                  x100��167 ohm
                  x010��143 ohm
                  x110��90 ohm
                  xxx1��0 ohm
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xC24)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR13
   ��      ����[7:3] reserved
            [2] CH0_DLY_CTRL2��ch0 0.6tsʱ�����ڿ���ѡ��
                RX ADC 0.6Tsʱ�����
                1��DAC3��ʱ0.6Ts
                0��DAC3��ʱ0.5Ts ��default��
            [1] CH0_DCTRL23��ch0 dac23����ģʽѡ��
                RXģʽ����DAC23������������
                1��Double icell23 current CA/4G/DC/TDS/X/2G_B
                0��Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1��ch0 dac1����ģʽѡ��
                RXģʽ����DAC1������������
                1��Double icell1 current 2G_B
                0��Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xC25)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR14
   ��      ����[7] reserved
            [6:4] CH0_IBCT_QT��ch0 rx QT������С����
                  RX ADC QTƫ�õ�������
                  000�� 5u CA
                  001�� 4u 4G
                  010�� 3u WDC/TDS/2G_B/X
                  011�� 2u 3G/2G_A
                  100�� 10u
                  101�� 9u
                  110�� 8u
                  111�� 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE��ch0 ����������capģʽѡ��
                  RX Integrator Cap Setting For Mode:
                  1x��DC/TDS/X/2G_B/3G/2G_A
                  01��4G
                  00��CA
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xC26)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH0_IBCT_OP2��ch0 rx op2������С����
            RX ADC OP2ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1��ch0 rx op1������С����
            RX ADC OP1ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xC27)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH0_IBCT_DAC��ch0 rx dac������С����
            RX ADC DACƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3��ch0 rx op3������С����
            RX ADC OP3ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xC28)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR17
   ��      ����[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3��ch0 rx������3����cap3�˻�����ѡ��
            RX Integrator Cap3 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
            [1:0] CH0_MULTI_RATE_CAP12��ch0 rx������1����cap1�˻�����ѡ��
            RX Integrator Cap12 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xC29)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR18
   ��      ����[7] CH0_RXA_DCLK_INV��ch0 rxa dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [6] CH0_RXB_DCLK_INV��ch0 rxb dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [5] CH0_CLKDIV2_A2D��ch0 rx a2d clock����Ƶѡ��
                ��������ֵ�ʱ��MCLK�Ķ���Ƶ����
                0������Ƶ CA/2G_A/2G_B
                1������Ƶ 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX��ch0 rx clock����Ƶѡ��
                �����RXADC��ͨ·��ʱ�ӵĶ���Ƶ����
                0������Ƶ 3G
                1������Ƶ CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV��ch0 rx a2d clock����ѡ��
                ��������ֵ�ʱ��MCLK�������ؿ���
                0������(default)
                1������
            [2:0] CH0_CLKMUX_CTRL��ch0 rx ģʽ��Ƶʱ��ѡ��
                  �ṩ���ϵ�ģ���ʱ�ӵķ�Ƶ����
                  000�� CAģʽ
                  100�� 4Gģʽ
                  110�� WDC/TDS/2G_B/Xģʽ
                  111:3G/2G_Aģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xC2A)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR19
   ��      ����[7:4] CH0_RXA_CLK_QT_CTRL��ch0 rxa qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xC2B)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR20
   ��      ����[7:2] reserved
            [1:0] RX_DLY_CTRL��RXA ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xC2C)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR21
   ��      ����[7:4] CH0_RXB_CLK_QT_CTRL��ch0 rxb qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xC2D)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR22
   ��      ����[7:2] reserved
            [1:0] RXB ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xC2E)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR23
   ��      ����[7] CH0_CLKIN3_INV_RXB_Q��ch0 rxb q·clkin3 dff�����ؿ��� 0������ 1������
            [6] CH0_CLKIN3_INV_RXB_I��ch0 rxb i·clkin3 dff�����ؿ��� 0������ 1������
            [5] CH0_CLKIN2_INV_RXB_Q��ch0 rxb q·clkin2 dff�����ؿ��� 0������ 1������
            [4] CH0_CLKIN2_INV_RXB_I��ch0 rxb i·clkin2 dff�����ؿ��� 0������ 1������
            [3] CH0_CLKIN3_INV_RXA_Q��ch0 rxa q·clkin3 dff�����ؿ��� 0������ 1������
            [2] CH0_CLKIN3_INV_RXA_I��ch0 rxa i·clkin3 dff�����ؿ��� 0������ 1������
            [1] CH0_CLKIN2_INV_RXA_Q��ch0 rxa q·clkin2 dff�����ؿ��� 0������ 1������
            [0] CH0_CLKIN2_INV_RXA_I��ch0 rxa i·clkin2 dff�����ؿ��� 0������ 1������
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xC2F)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR08
   ��      ����[7] CH0_PD_RXA_I��ch0 rxa i·power down����
            [6] CH0_PD_RXA_Q��ch0 rxa q·power down����
            [5] CH0_PD_RXB_I��ch0 rxb i·power down����
            [4] CH0_PD_RXB_Q��ch0 rxb q·power down����
            [3] reserved
            [2:0] CH0_RX_MODE��ch0 rxģʽѡ��
                  000��4G
                  001��3G
                  010��3G_DC &amp; TDS (Ĭ��)
                  011��2G_A
                  100��CA
                  101��CDMA
                  110:2G_B
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_0_ADDR                     (ABB_BASE_ADDR + 0xC30)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH0_MODE_IBCT3��ch0 op3ģʽѡ��
            [3:2] CH0_MODE_IBCT2��ch0 op2ģʽѡ��
            [1:0] CH0_MODE_IBCT1��ch0 op1ģʽѡ��
                  OP1/OP2/OP3 Current Seting For Mode
                  11��CA mode Current
                  10��LTE mode Current
                  01��DC/TDS/X/2G_B mode Current
                  00��3G/2G_A mode Current
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_1_ADDR                     (ABB_BASE_ADDR + 0xC31)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR10
   ��      ����[7:6] reserved
            [5] PDM_CTRL: RX ADC���������ģʽѡ��
                1��Binary Encoder
                0��Add Encoder��default��
            [4] DEM_OUTPUT_SEL: DEM�����߼�����
                0��DEM_IN ADD
                1��DEM_IN ENC
            [3] DEM_ENB: ADC DEM���ܹر��ź�
                0��DEM Enable
                1��DEM Disable
            [2:0] DEM mode
                  RX ADC��DAC DEMģʽѡ��
                  000��DWA��default��
                  001��CLA1
                  010��CLA2
                  011��CLA3
                  100��CLA4
                  101��CLA5
                  110��CLA6
                  111��CLA7
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_2_ADDR                     (ABB_BASE_ADDR + 0xC32)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR11
   ��      ����[7:6] CH0_CTRL_RFF��ch0 ǰ������rffѡ��
                  RXģʽ���ƻ�����ǰ������RFF
                  1x��4.865K ohm CA/4G/DC/TDS/X
                  01��9.73K ohm 2G_B
                  00��19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1��ch0 ������1�������rin1ѡ��
                  RXģʽ���ƻ�������һ���������RIN1
                  11��2.8K ohm 2G_B
                  10��5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01��5.6K ohm
                  00��cut off
            [3:2] CH0_CTRL_RIN2��ch0 ������2�������rin2ѡ��
                  RXģʽ���ƻ������ڶ����������RIN2
                  1x��16.6K ohm CA/4G/DC/TDS/X
                  01��33.2K ohm 2G_B
                  00��66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3��ch0 ������3�������rin3ѡ��
                RXģʽ���ƻ������������������RIN3
                1��6.93K ohm CA/4G/DC/TDS/X/2G_B
                0��13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB��ch0 ��������������rfbѡ��
                RXģʽ���ƻ�������������RFB
                1��160K ohm CA/4G/DC/TDS/X/2G_B
                0��320K ohm 3G/2G_A
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_3_ADDR                     (ABB_BASE_ADDR + 0xC33)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH0_CTRL_RSIG��ch0 �������ź�ǰ������rsigѡ��
                  RXģʽ���ƻ������ź�ǰ������RSIG
                  1x��46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01��93K ohm 3G/2G_A
                  00��cut off
            [3:0] CH0_CTRL_RZ��ch0 ������3�������rzѡ��
                  RXģʽ���ƻ������������������ݵ������RZ
                  x000��500 ohm��default��
                  x100��167 ohm
                  x010��143 ohm
                  x110��90 ohm
                  xxx1��0 ohm
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_4_ADDR                     (ABB_BASE_ADDR + 0xC34)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR13
   ��      ����[7:3] reserved
            [2] CH0_DLY_CTRL2��ch0 0.6tsʱ�����ڿ���ѡ��
                RX ADC 0.6Tsʱ�����
                1��DAC3��ʱ0.6Ts
                0��DAC3��ʱ0.5Ts ��default��
            [1] CH0_DCTRL23��ch0 dac23����ģʽѡ��
                RXģʽ����DAC23������������
                1��Double icell23 current CA/4G/DC/TDS/X/2G_B
                0��Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1��ch0 dac1����ģʽѡ��
                RXģʽ����DAC1������������
                1��Double icell1 current 2G_B
                0��Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_5_ADDR                     (ABB_BASE_ADDR + 0xC35)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR14
   ��      ����[7] reserved
            [6:4] CH0_IBCT_QT��ch0 rx QT������С����
                  RX ADC QTƫ�õ�������
                  000�� 5u CA
                  001�� 4u 4G
                  010�� 3u WDC/TDS/2G_B/X
                  011�� 2u 3G/2G_A
                  100�� 10u
                  101�� 9u
                  110�� 8u
                  111�� 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE��ch0 ����������capģʽѡ��
                  RX Integrator Cap Setting For Mode:
                  1x��DC/TDS/X/2G_B/3G/2G_A
                  01��4G
                  00��CA
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_6_ADDR                     (ABB_BASE_ADDR + 0xC36)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH0_IBCT_OP2��ch0 rx op2������С����
            RX ADC OP2ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1��ch0 rx op1������С����
            RX ADC OP1ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_7_ADDR                     (ABB_BASE_ADDR + 0xC37)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH0_IBCT_DAC��ch0 rx dac������С����
            RX ADC DACƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3��ch0 rx op3������С����
            RX ADC OP3ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_8_ADDR                     (ABB_BASE_ADDR + 0xC38)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR17
   ��      ����[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3��ch0 rx������3����cap3�˻�����ѡ��
            RX Integrator Cap3 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
            [1:0] CH0_MULTI_RATE_CAP12��ch0 rx������1����cap1�˻�����ѡ��
            RX Integrator Cap12 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_9_ADDR                     (ABB_BASE_ADDR + 0xC39)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR18
   ��      ����[7] CH0_RXA_DCLK_INV��ch0 rxa dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [6] CH0_RXB_DCLK_INV��ch0 rxb dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [5] CH0_CLKDIV2_A2D��ch0 rx a2d clock����Ƶѡ��
                ��������ֵ�ʱ��MCLK�Ķ���Ƶ����
                0������Ƶ CA/2G_A/2G_B
                1������Ƶ 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX��ch0 rx clock����Ƶѡ��
                �����RXADC��ͨ·��ʱ�ӵĶ���Ƶ����
                0������Ƶ 3G
                1������Ƶ CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV��ch0 rx a2d clock����ѡ��
                ��������ֵ�ʱ��MCLK�������ؿ���
                0������(default)
                1������
            [2:0] CH0_CLKMUX_CTRL��ch0 rx ģʽ��Ƶʱ��ѡ��
                  �ṩ���ϵ�ģ���ʱ�ӵķ�Ƶ����
                  000�� CAģʽ
                  100�� 4Gģʽ
                  110�� WDC/TDS/2G_B/Xģʽ
                  111:3G/2G_Aģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_10_ADDR                    (ABB_BASE_ADDR + 0xC3A)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR19
   ��      ����[7:4] CH0_RXA_CLK_QT_CTRL��ch0 rxa qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_11_ADDR                    (ABB_BASE_ADDR + 0xC3B)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR20
   ��      ����[7:2] reserved
            [1:0] RX_DLY_CTRL��RXA ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_12_ADDR                    (ABB_BASE_ADDR + 0xC3C)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR21
   ��      ����[7:4] CH0_RXB_CLK_QT_CTRL��ch0 rxb qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_13_ADDR                    (ABB_BASE_ADDR + 0xC3D)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR22
   ��      ����[7:2] reserved
            [1:0] RXB ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_14_ADDR                    (ABB_BASE_ADDR + 0xC3E)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR23
   ��      ����[7] CH0_CLKIN3_INV_RXB_Q��ch0 rxb q·clkin3 dff�����ؿ��� 0������ 1������
            [6] CH0_CLKIN3_INV_RXB_I��ch0 rxb i·clkin3 dff�����ؿ��� 0������ 1������
            [5] CH0_CLKIN2_INV_RXB_Q��ch0 rxb q·clkin2 dff�����ؿ��� 0������ 1������
            [4] CH0_CLKIN2_INV_RXB_I��ch0 rxb i·clkin2 dff�����ؿ��� 0������ 1������
            [3] CH0_CLKIN3_INV_RXA_Q��ch0 rxa q·clkin3 dff�����ؿ��� 0������ 1������
            [2] CH0_CLKIN3_INV_RXA_I��ch0 rxa i·clkin3 dff�����ؿ��� 0������ 1������
            [1] CH0_CLKIN2_INV_RXA_Q��ch0 rxa q·clkin2 dff�����ؿ��� 0������ 1������
            [0] CH0_CLKIN2_INV_RXA_I��ch0 rxa i·clkin2 dff�����ؿ��� 0������ 1������
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_15_ADDR                    (ABB_BASE_ADDR + 0xC3F)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR08
   ��      ����[7] CH0_PD_RXA_I��ch0 rxa i·power down����
            [6] CH0_PD_RXA_Q��ch0 rxa q·power down����
            [5] CH0_PD_RXB_I��ch0 rxb i·power down����
            [4] CH0_PD_RXB_Q��ch0 rxb q·power down����
            [3] reserved
            [2:0] CH0_RX_MODE��ch0 rxģʽѡ��
                  000��4G
                  001��3G
                  010��3G_DC &amp; TDS
                  011��2G_A(Ĭ��)
                  100��CA
                  101��CDMA
                  110:2G_B
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_0_ADDR                       (ABB_BASE_ADDR + 0xC40)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH0_MODE_IBCT3��ch0 op3ģʽѡ��
            [3:2] CH0_MODE_IBCT2��ch0 op2ģʽѡ��
            [1:0] CH0_MODE_IBCT1��ch0 op1ģʽѡ��
                  OP1/OP2/OP3 Current Seting For Mode
                  11��CA mode Current
                  10��LTE mode Current
                  01��DC/TDS/X/2G_B mode Current
                  00��3G/2G_A mode Current
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_1_ADDR                       (ABB_BASE_ADDR + 0xC41)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR10
   ��      ����[7:6] reserved
            [5] PDM_CTRL: RX ADC���������ģʽѡ��
                1��Binary Encoder
                0��Add Encoder��default��
            [4] DEM_OUTPUT_SEL: DEM�����߼�����
                0��DEM_IN ADD
                1��DEM_IN ENC
            [3] DEM_ENB: ADC DEM���ܹر��ź�
                0��DEM Enable
                1��DEM Disable
            [2:0] DEM mode
                  RX ADC��DAC DEMģʽѡ��
                  000��DWA��default��
                  001��CLA1
                  010��CLA2
                  011��CLA3
                  100��CLA4
                  101��CLA5
                  110��CLA6
                  111��CLA7
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_2_ADDR                       (ABB_BASE_ADDR + 0xC42)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR11
   ��      ����[7:6] CH0_CTRL_RFF��ch0 ǰ������rffѡ��
                  RXģʽ���ƻ�����ǰ������RFF
                  1x��4.865K ohm CA/4G/DC/TDS/X
                  01��9.73K ohm 2G_B
                  00��19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1��ch0 ������1�������rin1ѡ��
                  RXģʽ���ƻ�������һ���������RIN1
                  11��2.8K ohm 2G_B
                  10��5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01��5.6K ohm
                  00��cut off
            [3:2] CH0_CTRL_RIN2��ch0 ������2�������rin2ѡ��
                  RXģʽ���ƻ������ڶ����������RIN2
                  1x��16.6K ohm CA/4G/DC/TDS/X
                  01��33.2K ohm 2G_B
                  00��66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3��ch0 ������3�������rin3ѡ��
                RXģʽ���ƻ������������������RIN3
                1��6.93K ohm CA/4G/DC/TDS/X/2G_B
                0��13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB��ch0 ��������������rfbѡ��
                RXģʽ���ƻ�������������RFB
                1��160K ohm CA/4G/DC/TDS/X/2G_B
                0��320K ohm 3G/2G_A
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_3_ADDR                       (ABB_BASE_ADDR + 0xC43)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH0_CTRL_RSIG��ch0 �������ź�ǰ������rsigѡ��
                  RXģʽ���ƻ������ź�ǰ������RSIG
                  1x��46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01��93K ohm 3G/2G_A
                  00��cut off
            [3:0] CH0_CTRL_RZ��ch0 ������3�������rzѡ��
                  RXģʽ���ƻ������������������ݵ������RZ
                  x000��500 ohm��default��
                  x100��167 ohm
                  x010��143 ohm
                  x110��90 ohm
                  xxx1��0 ohm
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_4_ADDR                       (ABB_BASE_ADDR + 0xC44)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR13
   ��      ����[7:3] reserved
            [2] CH0_DLY_CTRL2��ch0 0.6tsʱ�����ڿ���ѡ��
                RX ADC 0.6Tsʱ�����
                1��DAC3��ʱ0.6Ts
                0��DAC3��ʱ0.5Ts ��default��
            [1] CH0_DCTRL23��ch0 dac23����ģʽѡ��
                RXģʽ����DAC23������������
                1��Double icell23 current CA/4G/DC/TDS/X/2G_B
                0��Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1��ch0 dac1����ģʽѡ��
                RXģʽ����DAC1������������
                1��Double icell1 current 2G_B
                0��Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_5_ADDR                       (ABB_BASE_ADDR + 0xC45)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR14
   ��      ����[7] reserved
            [6:4] CH0_IBCT_QT��ch0 rx QT������С����
                  RX ADC QTƫ�õ�������
                  000�� 5u CA
                  001�� 4u 4G
                  010�� 3u WDC/TDS/2G_B/X
                  011�� 2u 3G/2G_A
                  100�� 10u
                  101�� 9u
                  110�� 8u
                  111�� 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE��ch0 ����������capģʽѡ��
                  RX Integrator Cap Setting For Mode:
                  1x��DC/TDS/X/2G_B/3G/2G_A
                  01��4G
                  00��CA
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_6_ADDR                       (ABB_BASE_ADDR + 0xC46)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH0_IBCT_OP2��ch0 rx op2������С����
            RX ADC OP2ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1��ch0 rx op1������С����
            RX ADC OP1ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_7_ADDR                       (ABB_BASE_ADDR + 0xC47)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH0_IBCT_DAC��ch0 rx dac������С����
            RX ADC DACƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3��ch0 rx op3������С����
            RX ADC OP3ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_8_ADDR                       (ABB_BASE_ADDR + 0xC48)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR17
   ��      ����[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3��ch0 rx������3����cap3�˻�����ѡ��
            RX Integrator Cap3 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
            [1:0] CH0_MULTI_RATE_CAP12��ch0 rx������1����cap1�˻�����ѡ��
            RX Integrator Cap12 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_9_ADDR                       (ABB_BASE_ADDR + 0xC49)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR18
   ��      ����[7] CH0_RXA_DCLK_INV��ch0 rxa dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [6] CH0_RXB_DCLK_INV��ch0 rxb dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [5] CH0_CLKDIV2_A2D��ch0 rx a2d clock����Ƶѡ��
                ��������ֵ�ʱ��MCLK�Ķ���Ƶ����
                0������Ƶ CA/2G_A/2G_B
                1������Ƶ 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX��ch0 rx clock����Ƶѡ��
                �����RXADC��ͨ·��ʱ�ӵĶ���Ƶ����
                0������Ƶ 3G
                1������Ƶ CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV��ch0 rx a2d clock����ѡ��
                ��������ֵ�ʱ��MCLK�������ؿ���
                0������(default)
                1������
            [2:0] CH0_CLKMUX_CTRL��ch0 rx ģʽ��Ƶʱ��ѡ��
                  �ṩ���ϵ�ģ���ʱ�ӵķ�Ƶ����
                  000�� CAģʽ
                  100�� 4Gģʽ
                  110�� WDC/TDS/2G_B/Xģʽ
                  111:3G/2G_Aģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_10_ADDR                      (ABB_BASE_ADDR + 0xC4A)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR19
   ��      ����[7:4] CH0_RXA_CLK_QT_CTRL��ch0 rxa qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_11_ADDR                      (ABB_BASE_ADDR + 0xC4B)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR20
   ��      ����[7:2] reserved
            [1:0] RX_DLY_CTRL��RXA ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_12_ADDR                      (ABB_BASE_ADDR + 0xC4C)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR21
   ��      ����[7:4] CH0_RXB_CLK_QT_CTRL��ch0 rxb qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_13_ADDR                      (ABB_BASE_ADDR + 0xC4D)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR22
   ��      ����[7:2] reserved
            [1:0] RXB ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_14_ADDR                      (ABB_BASE_ADDR + 0xC4E)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR23
   ��      ����[7] CH0_CLKIN3_INV_RXB_Q��ch0 rxb q·clkin3 dff�����ؿ��� 0������ 1������
            [6] CH0_CLKIN3_INV_RXB_I��ch0 rxb i·clkin3 dff�����ؿ��� 0������ 1������
            [5] CH0_CLKIN2_INV_RXB_Q��ch0 rxb q·clkin2 dff�����ؿ��� 0������ 1������
            [4] CH0_CLKIN2_INV_RXB_I��ch0 rxb i·clkin2 dff�����ؿ��� 0������ 1������
            [3] CH0_CLKIN3_INV_RXA_Q��ch0 rxa q·clkin3 dff�����ؿ��� 0������ 1������
            [2] CH0_CLKIN3_INV_RXA_I��ch0 rxa i·clkin3 dff�����ؿ��� 0������ 1������
            [1] CH0_CLKIN2_INV_RXA_Q��ch0 rxa q·clkin2 dff�����ؿ��� 0������ 1������
            [0] CH0_CLKIN2_INV_RXA_I��ch0 rxa i·clkin2 dff�����ؿ��� 0������ 1������
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_15_ADDR                      (ABB_BASE_ADDR + 0xC4F)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR08
   ��      ����[7] CH0_PD_RXA_I��ch0 rxa i·power down����
            [6] CH0_PD_RXA_Q��ch0 rxa q·power down����
            [5] CH0_PD_RXB_I��ch0 rxb i·power down����
            [4] CH0_PD_RXB_Q��ch0 rxb q·power down����
            [3] reserved
            [2:0] CH0_RX_MODE��ch0 rxģʽѡ��
                  000��4G
                  001��3G
                  010��3G_DC &amp; TDS
                  011��2G_A(Ĭ��)
                  100��CA
                  101��CDMA
                  110:2G_B
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_0_ADDR                    (ABB_BASE_ADDR + 0xC50)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH0_MODE_IBCT3��ch0 op3ģʽѡ��
            [3:2] CH0_MODE_IBCT2��ch0 op2ģʽѡ��
            [1:0] CH0_MODE_IBCT1��ch0 op1ģʽѡ��
                  OP1/OP2/OP3 Current Seting For Mode
                  11��CA mode Current
                  10��LTE mode Current
                  01��DC/TDS/X/2G_B mode Current
                  00��3G/2G_A mode Current
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_1_ADDR                    (ABB_BASE_ADDR + 0xC51)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR10
   ��      ����[7:6] reserved
            [5] PDM_CTRL: RX ADC���������ģʽѡ��
                1��Binary Encoder
                0��Add Encoder��default��
            [4] DEM_OUTPUT_SEL: DEM�����߼�����
                0��DEM_IN ADD
                1��DEM_IN ENC
            [3] DEM_ENB: ADC DEM���ܹر��ź�
                0��DEM Enable
                1��DEM Disable
            [2:0] DEM mode
                  RX ADC��DAC DEMģʽѡ��
                  000��DWA��default��
                  001��CLA1
                  010��CLA2
                  011��CLA3
                  100��CLA4
                  101��CLA5
                  110��CLA6
                  111��CLA7
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_2_ADDR                    (ABB_BASE_ADDR + 0xC52)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR11
   ��      ����[7:6] CH0_CTRL_RFF��ch0 ǰ������rffѡ��
                  RXģʽ���ƻ�����ǰ������RFF
                  1x��4.865K ohm CA/4G/DC/TDS/X
                  01��9.73K ohm 2G_B
                  00��19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1��ch0 ������1�������rin1ѡ��
                  RXģʽ���ƻ�������һ���������RIN1
                  11��2.8K ohm 2G_B
                  10��5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01��5.6K ohm
                  00��cut off
            [3:2] CH0_CTRL_RIN2��ch0 ������2�������rin2ѡ��
                  RXģʽ���ƻ������ڶ����������RIN2
                  1x��16.6K ohm CA/4G/DC/TDS/X
                  01��33.2K ohm 2G_B
                  00��66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3��ch0 ������3�������rin3ѡ��
                RXģʽ���ƻ������������������RIN3
                1��6.93K ohm CA/4G/DC/TDS/X/2G_B
                0��13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB��ch0 ��������������rfbѡ��
                RXģʽ���ƻ�������������RFB
                1��160K ohm CA/4G/DC/TDS/X/2G_B
                0��320K ohm 3G/2G_A
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_3_ADDR                    (ABB_BASE_ADDR + 0xC53)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH0_CTRL_RSIG��ch0 �������ź�ǰ������rsigѡ��
                  RXģʽ���ƻ������ź�ǰ������RSIG
                  1x��46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01��93K ohm 3G/2G_A
                  00��cut off
            [3:0] CH0_CTRL_RZ��ch0 ������3�������rzѡ��
                  RXģʽ���ƻ������������������ݵ������RZ
                  x000��500 ohm��default��
                  x100��167 ohm
                  x010��143 ohm
                  x110��90 ohm
                  xxx1��0 ohm
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_4_ADDR                    (ABB_BASE_ADDR + 0xC54)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR13
   ��      ����[7:3] reserved
            [2] CH0_DLY_CTRL2��ch0 0.6tsʱ�����ڿ���ѡ��
                RX ADC 0.6Tsʱ�����
                1��DAC3��ʱ0.6Ts
                0��DAC3��ʱ0.5Ts ��default��
            [1] CH0_DCTRL23��ch0 dac23����ģʽѡ��
                RXģʽ����DAC23������������
                1��Double icell23 current CA/4G/DC/TDS/X/2G_B
                0��Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1��ch0 dac1����ģʽѡ��
                RXģʽ����DAC1������������
                1��Double icell1 current 2G_B
                0��Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_5_ADDR                    (ABB_BASE_ADDR + 0xC55)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR14
   ��      ����[7] reserved
            [6:4] CH0_IBCT_QT��ch0 rx QT������С����
                  RX ADC QTƫ�õ�������
                  000�� 5u CA
                  001�� 4u 4G
                  010�� 3u WDC/TDS/2G_B/X
                  011�� 2u 3G/2G_A
                  100�� 10u
                  101�� 9u
                  110�� 8u
                  111�� 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE��ch0 ����������capģʽѡ��
                  RX Integrator Cap Setting For Mode:
                  1x��DC/TDS/X/2G_B/3G/2G_A
                  01��4G
                  00��CA
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_6_ADDR                    (ABB_BASE_ADDR + 0xC56)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH0_IBCT_OP2��ch0 rx op2������С����
            RX ADC OP2ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1��ch0 rx op1������С����
            RX ADC OP1ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_7_ADDR                    (ABB_BASE_ADDR + 0xC57)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH0_IBCT_DAC��ch0 rx dac������С����
            RX ADC DACƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3��ch0 rx op3������С����
            RX ADC OP3ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_8_ADDR                    (ABB_BASE_ADDR + 0xC58)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR17
   ��      ����[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3��ch0 rx������3����cap3�˻�����ѡ��
            RX Integrator Cap3 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
            [1:0] CH0_MULTI_RATE_CAP12��ch0 rx������1����cap1�˻�����ѡ��
            RX Integrator Cap12 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_9_ADDR                    (ABB_BASE_ADDR + 0xC59)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR18
   ��      ����[7] CH0_RXA_DCLK_INV��ch0 rxa dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [6] CH0_RXB_DCLK_INV��ch0 rxb dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [5] CH0_CLKDIV2_A2D��ch0 rx a2d clock����Ƶѡ��
                ��������ֵ�ʱ��MCLK�Ķ���Ƶ����
                0������Ƶ CA/2G_A/2G_B
                1������Ƶ 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX��ch0 rx clock����Ƶѡ��
                �����RXADC��ͨ·��ʱ�ӵĶ���Ƶ����
                0������Ƶ 3G
                1������Ƶ CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV��ch0 rx a2d clock����ѡ��
                ��������ֵ�ʱ��MCLK�������ؿ���
                0������(default)
                1������
            [2:0] CH0_CLKMUX_CTRL��ch0 rx ģʽ��Ƶʱ��ѡ��
                  �ṩ���ϵ�ģ���ʱ�ӵķ�Ƶ����
                  000�� CAģʽ
                  100�� 4Gģʽ
                  110�� WDC/TDS/2G_B/Xģʽ
                  111:3G/2G_Aģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_10_ADDR                   (ABB_BASE_ADDR + 0xC5A)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR19
   ��      ����[7:4] CH0_RXA_CLK_QT_CTRL��ch0 rxa qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_11_ADDR                   (ABB_BASE_ADDR + 0xC5B)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR20
   ��      ����[7:2] reserved
            [1:0] RX_DLY_CTRL��RXA ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_12_ADDR                   (ABB_BASE_ADDR + 0xC5C)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR21
   ��      ����[7:4] CH0_RXB_CLK_QT_CTRL��ch0 rxb qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_13_ADDR                   (ABB_BASE_ADDR + 0xC5D)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR22
   ��      ����[7:2] reserved
            [1:0] RXB ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_14_ADDR                   (ABB_BASE_ADDR + 0xC5E)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR23
   ��      ����[7] CH0_CLKIN3_INV_RXB_Q��ch0 rxb q·clkin3 dff�����ؿ��� 0������ 1������
            [6] CH0_CLKIN3_INV_RXB_I��ch0 rxb i·clkin3 dff�����ؿ��� 0������ 1������
            [5] CH0_CLKIN2_INV_RXB_Q��ch0 rxb q·clkin2 dff�����ؿ��� 0������ 1������
            [4] CH0_CLKIN2_INV_RXB_I��ch0 rxb i·clkin2 dff�����ؿ��� 0������ 1������
            [3] CH0_CLKIN3_INV_RXA_Q��ch0 rxa q·clkin3 dff�����ؿ��� 0������ 1������
            [2] CH0_CLKIN3_INV_RXA_I��ch0 rxa i·clkin3 dff�����ؿ��� 0������ 1������
            [1] CH0_CLKIN2_INV_RXA_Q��ch0 rxa q·clkin2 dff�����ؿ��� 0������ 1������
            [0] CH0_CLKIN2_INV_RXA_I��ch0 rxa i·clkin2 dff�����ؿ��� 0������ 1������
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_15_ADDR                   (ABB_BASE_ADDR + 0xC5F)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7:0] CH0_REG_TUNE1��ch0 rx cap1�ֶ����üĴ���
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA16_ADDR                  (ABB_BASE_ADDR + 0xC60)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7:0] CH0_REG_TUNE2��ch0 rx cap2�ֶ����üĴ���
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA17_ADDR                  (ABB_BASE_ADDR + 0xC61)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7:0] CH0_REG_TUNE3��ch0 rx cap3�ֶ����üĴ���
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA18_ADDR                  (ABB_BASE_ADDR + 0xC62)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7] rc tuning ģʽѡ��0.�Ĵ����ֶ����ã�1.�Է�
            [6:0]  reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA19_ADDR                  (ABB_BASE_ADDR + 0xC63)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7] reserved
            [6:4] CH0_OL_CTRL��ch0 rx overload����ѡ��
                  ADC Overloadģ������
                  00��16����������������С��
                  01��8����������������С��
                  10��4����������������С��
                  11���ر�Overload���
            [3:2] reserved
            [1] CH0_PUP_CLK_CTRL��ch0 rx �ϵ�ģ���ʱ�ӿ���
                0���ϵ���ɺ�ر��ϵ�ģ���ʱ�� (default)
                1���ϵ���ɺ󲻹ر��ϵ�ģ��ʱ��
            [0] CH0_PUP_MODE��ch0 rx �����ϵ�ģʽ
                ADCģ���ϵ�ģʽѡ��
                0���Զ�ģʽ
                1�����üĴ����ϵ�ģʽ
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA20_ADDR                  (ABB_BASE_ADDR + 0xC64)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7:0] CH0_PUP_CTRL��ch0 rx �����ϵ����
            [7] ���üĴ����ϵ�ģʽʱADC��RST_CAP����
            0��Reset CAP3
            1����Reset CAP3
            [6]���üĴ����ϵ�ģʽʱADC��RST_CAP����
            0��Reset CAP2
            1����Reset CAP2
            [5]���üĴ����ϵ�ģʽʱADC��RST_CAP����
            0��Reset CAP1
            1����Reset CAP1
            [4]���üĴ����ϵ�ģʽʱADC��OP����
            0��OP Power Down
            1��OP Power On
            [3]���üĴ����ϵ�ģʽʱADC��DAC����
            0��DAC Power Down
            1��DAC Power On
            [2]���üĴ����ϵ�ģʽʱADC��QTУ������
            0��QT Calibration On
            1��QT Calibration Off
            [1]���üĴ����ϵ�ģʽʱADC��CLKGEN����
            0��CLKGEN Power Down
            1��CLKGEN Power On
            [0]���üĴ����ϵ�ģʽʱADC��QT����
            0��QT Power Down
            1��QT Power On
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA21_ADDR                  (ABB_BASE_ADDR + 0xC65)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7:6] RXͨ��OP1У��CAL���ؿ���
            00��
            01��
            10��
            11��
            [5] CH0_CAL_TRIM_SW��ch0 rx op1У׼trim���ؿ���
                RXͨ��OP1У��Trim����
                0��Trim Switch Off
                1��Trim Switch On
            [4] CH0_OPCAL_VCM_SEL��ch0 rx op1У׼��ģѡ��
                0��Disable
                1��Enable���̽ӹ�ģ����OP Calibration��
            [3] CH0_RXB_EN_QTCAL��ch0 rx qtУ׼enable
            [2] CH0_RXA_EN_QTCAL��ch0 rx qtУ׼enable
            [1] CH0_RXB_EN_OPCAL��ch0 rx op1У׼enable
            [0] CH0_RXA_EN_OPCAL��ch0 rx op1У׼enable
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA22_ADDR                  (ABB_BASE_ADDR + 0xC66)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7] reserved
            [6] RXB_PD_CAL ( NC ��
            [5] RXA_PD_CAL ( NC ��
            [4] RX_VCM_ADJ_CTRL
                ���빲ģ��ƽѡ��
                0��0.8V VCM Input
                1��0.5V VCM Input
            [3:1] reserved
            [0] CH0_QT_REF_SEL��ch0 rx qt��refѡ��
                RX��QT��VREFP/VRENѡ��
                0����refģ���ṩ
                1���ɱ��ص����ѹ�ṩ
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA23_ADDR                  (ABB_BASE_ADDR + 0xC67)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA24_ADDR                  (ABB_BASE_ADDR + 0xC68)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA25_ADDR                  (ABB_BASE_ADDR + 0xC69)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA26_ADDR                  (ABB_BASE_ADDR + 0xC6A)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA27_ADDR                  (ABB_BASE_ADDR + 0xC6B)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA28_ADDR                  (ABB_BASE_ADDR + 0xC6C)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA29_ADDR                  (ABB_BASE_ADDR + 0xC6D)

/* �Ĵ���˵����TX ch0���üĴ���
   ��      ����[7] TX rc tuning ģʽѡ��0.�Ĵ����ֶ����ã�1.�Է�
            [6:0]  reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA30_ADDR                  (ABB_BASE_ADDR + 0xC6E)

/* �Ĵ���˵����TX ch0���üĴ���
   ��      ����[7]
            [6:0] TX tuning �����üĴ���
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA31_ADDR                  (ABB_BASE_ADDR + 0xC6F)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR08
   ��      ����[7] CH0_PD_RXA_I��ch0 rxa i·power down����
            [6] CH0_PD_RXA_Q��ch0 rxa q·power down����
            [5] CH0_PD_RXB_I��ch0 rxb i·power down����
            [4] CH0_PD_RXB_Q��ch0 rxb q·power down����
            [3] reserved
            [2:0] CH0_RX_MODE��ch0 rxģʽѡ��
                  000��4G
                  001��3G
                  010��3G_DC &amp; TDS
                  011��2G_A(Ĭ��)
                  100��CA
                  101��CDMA
                  110:2G_B
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xC80)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH0_MODE_IBCT3��ch0 op3ģʽѡ��
            [3:2] CH0_MODE_IBCT2��ch0 op2ģʽѡ��
            [1:0] CH0_MODE_IBCT1��ch0 op1ģʽѡ��
                  OP1/OP2/OP3 Current Seting For Mode
                  11��CA mode Current
                  10��LTE mode Current
                  01��DC/TDS/X/2G_B mode Current
                  00��3G/2G_A mode Current
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xC81)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR10
   ��      ����[7:6] reserved
            [5] PDM_CTRL: RX ADC���������ģʽѡ��
                1��Binary Encoder
                0��Add Encoder��default��
            [4] DEM_OUTPUT_SEL: DEM�����߼�����
                0��DEM_IN ADD
                1��DEM_IN ENC
            [3] DEM_ENB: ADC DEM���ܹر��ź�
                0��DEM Enable
                1��DEM Disable
            [2:0] DEM mode
                  RX ADC��DAC DEMģʽѡ��
                  000��DWA��default��
                  001��CLA1
                  010��CLA2
                  011��CLA3
                  100��CLA4
                  101��CLA5
                  110��CLA6
                  111��CLA7
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xC82)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR11
   ��      ����[7:6] CH0_CTRL_RFF��ch0 ǰ������rffѡ��
                  RXģʽ���ƻ�����ǰ������RFF
                  1x��4.865K ohm CA/4G/DC/TDS/X
                  01��9.73K ohm 2G_B
                  00��19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1��ch0 ������1�������rin1ѡ��
                  RXģʽ���ƻ�������һ���������RIN1
                  11��2.8K ohm 2G_B
                  10��5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01��5.6K ohm
                  00��cut off
            [3:2] CH0_CTRL_RIN2��ch0 ������2�������rin2ѡ��
                  RXģʽ���ƻ������ڶ����������RIN2
                  1x��16.6K ohm CA/4G/DC/TDS/X
                  01��33.2K ohm 2G_B
                  00��66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3��ch0 ������3�������rin3ѡ��
                RXģʽ���ƻ������������������RIN3
                1��6.93K ohm CA/4G/DC/TDS/X/2G_B
                0��13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB��ch0 ��������������rfbѡ��
                RXģʽ���ƻ�������������RFB
                1��160K ohm CA/4G/DC/TDS/X/2G_B
                0��320K ohm 3G/2G_A
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xC83)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH0_CTRL_RSIG��ch0 �������ź�ǰ������rsigѡ��
                  RXģʽ���ƻ������ź�ǰ������RSIG
                  1x��46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01��93K ohm 3G/2G_A
                  00��cut off
            [3:0] CH0_CTRL_RZ��ch0 ������3�������rzѡ��
                  RXģʽ���ƻ������������������ݵ������RZ
                  x000��500 ohm��default��
                  x100��167 ohm
                  x010��143 ohm
                  x110��90 ohm
                  xxx1��0 ohm
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xC84)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR13
   ��      ����[7:3] reserved
            [2] CH0_DLY_CTRL2��ch0 0.6tsʱ�����ڿ���ѡ��
                RX ADC 0.6Tsʱ�����
                1��DAC3��ʱ0.6Ts
                0��DAC3��ʱ0.5Ts ��default��
            [1] CH0_DCTRL23��ch0 dac23����ģʽѡ��
                RXģʽ����DAC23������������
                1��Double icell23 current CA/4G/DC/TDS/X/2G_B
                0��Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1��ch0 dac1����ģʽѡ��
                RXģʽ����DAC1������������
                1��Double icell1 current 2G_B
                0��Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xC85)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR14
   ��      ����[7] reserved
            [6:4] CH0_IBCT_QT��ch0 rx QT������С����
                  RX ADC QTƫ�õ�������
                  000�� 5u CA
                  001�� 4u 4G
                  010�� 3u WDC/TDS/2G_B/X
                  011�� 2u 3G/2G_A
                  100�� 10u
                  101�� 9u
                  110�� 8u
                  111�� 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE��ch0 ����������capģʽѡ��
                  RX Integrator Cap Setting For Mode:
                  1x��DC/TDS/X/2G_B/3G/2G_A
                  01��4G
                  00��CA
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xC86)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH0_IBCT_OP2��ch0 rx op2������С����
            RX ADC OP2ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1��ch0 rx op1������С����
            RX ADC OP1ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xC87)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH0_IBCT_DAC��ch0 rx dac������С����
            RX ADC DACƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3��ch0 rx op3������С����
            RX ADC OP3ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xC88)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR17
   ��      ����[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3��ch0 rx������3����cap3�˻�����ѡ��
            RX Integrator Cap3 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
            [1:0] CH0_MULTI_RATE_CAP12��ch0 rx������1����cap1�˻�����ѡ��
            RX Integrator Cap12 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xC89)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR18
   ��      ����[7] CH0_RXA_DCLK_INV��ch0 rxa dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [6] CH0_RXB_DCLK_INV��ch0 rxb dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [5] CH0_CLKDIV2_A2D��ch0 rx a2d clock����Ƶѡ��
                ��������ֵ�ʱ��MCLK�Ķ���Ƶ����
                0������Ƶ CA/2G_A/2G_B
                1������Ƶ 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX��ch0 rx clock����Ƶѡ��
                �����RXADC��ͨ·��ʱ�ӵĶ���Ƶ����
                0������Ƶ 3G
                1������Ƶ CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV��ch0 rx a2d clock����ѡ��
                ��������ֵ�ʱ��MCLK�������ؿ���
                0������(default)
                1������
            [2:0] CH0_CLKMUX_CTRL��ch0 rx ģʽ��Ƶʱ��ѡ��
                  �ṩ���ϵ�ģ���ʱ�ӵķ�Ƶ����
                  000�� CAģʽ
                  100�� 4Gģʽ
                  110�� WDC/TDS/2G_B/Xģʽ
                  111:3G/2G_Aģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xC8A)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR19
   ��      ����[7:4] CH0_RXA_CLK_QT_CTRL��ch0 rxa qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xC8B)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR20
   ��      ����[7:2] reserved
            [1:0] RX_DLY_CTRL��RXA ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xC8C)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR21
   ��      ����[7:4] CH0_RXB_CLK_QT_CTRL��ch0 rxb qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xC8D)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR22
   ��      ����[7:2] reserved
            [1:0] RXB ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xC8E)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR23
   ��      ����[7] CH0_CLKIN3_INV_RXB_Q��ch0 rxb q·clkin3 dff�����ؿ��� 0������ 1������
            [6] CH0_CLKIN3_INV_RXB_I��ch0 rxb i·clkin3 dff�����ؿ��� 0������ 1������
            [5] CH0_CLKIN2_INV_RXB_Q��ch0 rxb q·clkin2 dff�����ؿ��� 0������ 1������
            [4] CH0_CLKIN2_INV_RXB_I��ch0 rxb i·clkin2 dff�����ؿ��� 0������ 1������
            [3] CH0_CLKIN3_INV_RXA_Q��ch0 rxa q·clkin3 dff�����ؿ��� 0������ 1������
            [2] CH0_CLKIN3_INV_RXA_I��ch0 rxa i·clkin3 dff�����ؿ��� 0������ 1������
            [1] CH0_CLKIN2_INV_RXA_Q��ch0 rxa q·clkin2 dff�����ؿ��� 0������ 1������
            [0] CH0_CLKIN2_INV_RXA_I��ch0 rxa i·clkin2 dff�����ؿ��� 0������ 1������
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xC8F)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR08
   ��      ����[7] CH0_PD_RXA_I��ch0 rxa i·power down����
            [6] CH0_PD_RXA_Q��ch0 rxa q·power down����
            [5] CH0_PD_RXB_I��ch0 rxb i·power down����
            [4] CH0_PD_RXB_Q��ch0 rxb q·power down����
            [3] reserved
            [2:0] CH0_RX_MODE��ch0 rxģʽѡ��
                  000��4G
                  001��3G
                  010��3G_DC &amp; TDS
                  011��2G_A(Ĭ��)
                  100��CA
                  101��CDMA
                  110:2G_B
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xC90)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH0_MODE_IBCT3��ch0 op3ģʽѡ��
            [3:2] CH0_MODE_IBCT2��ch0 op2ģʽѡ��
            [1:0] CH0_MODE_IBCT1��ch0 op1ģʽѡ��
                  OP1/OP2/OP3 Current Seting For Mode
                  11��CA mode Current
                  10��LTE mode Current
                  01��DC/TDS/X/2G_B mode Current
                  00��3G/2G_A mode Current
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xC91)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR10
   ��      ����[7:6] reserved
            [5] PDM_CTRL: RX ADC���������ģʽѡ��
                1��Binary Encoder
                0��Add Encoder��default��
            [4] DEM_OUTPUT_SEL: DEM�����߼�����
                0��DEM_IN ADD
                1��DEM_IN ENC
            [3] DEM_ENB: ADC DEM���ܹر��ź�
                0��DEM Enable
                1��DEM Disable
            [2:0] DEM mode
                  RX ADC��DAC DEMģʽѡ��
                  000��DWA��default��
                  001��CLA1
                  010��CLA2
                  011��CLA3
                  100��CLA4
                  101��CLA5
                  110��CLA6
                  111��CLA7
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xC92)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR11
   ��      ����[7:6] CH0_CTRL_RFF��ch0 ǰ������rffѡ��
                  RXģʽ���ƻ�����ǰ������RFF
                  1x��4.865K ohm CA/4G/DC/TDS/X
                  01��9.73K ohm 2G_B
                  00��19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1��ch0 ������1�������rin1ѡ��
                  RXģʽ���ƻ�������һ���������RIN1
                  11��2.8K ohm 2G_B
                  10��5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01��5.6K ohm
                  00��cut off
            [3:2] CH0_CTRL_RIN2��ch0 ������2�������rin2ѡ��
                  RXģʽ���ƻ������ڶ����������RIN2
                  1x��16.6K ohm CA/4G/DC/TDS/X
                  01��33.2K ohm 2G_B
                  00��66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3��ch0 ������3�������rin3ѡ��
                RXģʽ���ƻ������������������RIN3
                1��6.93K ohm CA/4G/DC/TDS/X/2G_B
                0��13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB��ch0 ��������������rfbѡ��
                RXģʽ���ƻ�������������RFB
                1��160K ohm CA/4G/DC/TDS/X/2G_B
                0��320K ohm 3G/2G_A
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xC93)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH0_CTRL_RSIG��ch0 �������ź�ǰ������rsigѡ��
                  RXģʽ���ƻ������ź�ǰ������RSIG
                  1x��46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01��93K ohm 3G/2G_A
                  00��cut off
            [3:0] CH0_CTRL_RZ��ch0 ������3�������rzѡ��
                  RXģʽ���ƻ������������������ݵ������RZ
                  x000��500 ohm��default��
                  x100��167 ohm
                  x010��143 ohm
                  x110��90 ohm
                  xxx1��0 ohm
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xC94)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR13
   ��      ����[7:3] reserved
            [2] CH0_DLY_CTRL2��ch0 0.6tsʱ�����ڿ���ѡ��
                RX ADC 0.6Tsʱ�����
                1��DAC3��ʱ0.6Ts
                0��DAC3��ʱ0.5Ts ��default��
            [1] CH0_DCTRL23��ch0 dac23����ģʽѡ��
                RXģʽ����DAC23������������
                1��Double icell23 current CA/4G/DC/TDS/X/2G_B
                0��Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1��ch0 dac1����ģʽѡ��
                RXģʽ����DAC1������������
                1��Double icell1 current 2G_B
                0��Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xC95)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR14
   ��      ����[7] reserved
            [6:4] CH0_IBCT_QT��ch0 rx QT������С����
                  RX ADC QTƫ�õ�������
                  000�� 5u CA
                  001�� 4u 4G
                  010�� 3u WDC/TDS/2G_B/X
                  011�� 2u 3G/2G_A
                  100�� 10u
                  101�� 9u
                  110�� 8u
                  111�� 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE��ch0 ����������capģʽѡ��
                  RX Integrator Cap Setting For Mode:
                  1x��DC/TDS/X/2G_B/3G/2G_A
                  01��4G
                  00��CA
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xC96)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH0_IBCT_OP2��ch0 rx op2������С����
            RX ADC OP2ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1��ch0 rx op1������С����
            RX ADC OP1ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xC97)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH0_IBCT_DAC��ch0 rx dac������С����
            RX ADC DACƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3��ch0 rx op3������С����
            RX ADC OP3ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xC98)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR17
   ��      ����[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3��ch0 rx������3����cap3�˻�����ѡ��
            RX Integrator Cap3 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
            [1:0] CH0_MULTI_RATE_CAP12��ch0 rx������1����cap1�˻�����ѡ��
            RX Integrator Cap12 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xC99)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR18
   ��      ����[7] CH0_RXA_DCLK_INV��ch0 rxa dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [6] CH0_RXB_DCLK_INV��ch0 rxb dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [5] CH0_CLKDIV2_A2D��ch0 rx a2d clock����Ƶѡ��
                ��������ֵ�ʱ��MCLK�Ķ���Ƶ����
                0������Ƶ CA/2G_A/2G_B
                1������Ƶ 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX��ch0 rx clock����Ƶѡ��
                �����RXADC��ͨ·��ʱ�ӵĶ���Ƶ����
                0������Ƶ 3G
                1������Ƶ CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV��ch0 rx a2d clock����ѡ��
                ��������ֵ�ʱ��MCLK�������ؿ���
                0������(default)
                1������
            [2:0] CH0_CLKMUX_CTRL��ch0 rx ģʽ��Ƶʱ��ѡ��
                  �ṩ���ϵ�ģ���ʱ�ӵķ�Ƶ����
                  000�� CAģʽ
                  100�� 4Gģʽ
                  110�� WDC/TDS/2G_B/Xģʽ
                  111:3G/2G_Aģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xC9A)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR19
   ��      ����[7:4] CH0_RXA_CLK_QT_CTRL��ch0 rxa qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xC9B)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR20
   ��      ����[7:2] reserved
            [1:0] RX_DLY_CTRL��RXA ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xC9C)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR21
   ��      ����[7:4] CH0_RXB_CLK_QT_CTRL��ch0 rxb qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xC9D)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR22
   ��      ����[7:2] reserved
            [1:0] RXB ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xC9E)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR23
   ��      ����[7] CH0_CLKIN3_INV_RXB_Q��ch0 rxb q·clkin3 dff�����ؿ��� 0������ 1������
            [6] CH0_CLKIN3_INV_RXB_I��ch0 rxb i·clkin3 dff�����ؿ��� 0������ 1������
            [5] CH0_CLKIN2_INV_RXB_Q��ch0 rxb q·clkin2 dff�����ؿ��� 0������ 1������
            [4] CH0_CLKIN2_INV_RXB_I��ch0 rxb i·clkin2 dff�����ؿ��� 0������ 1������
            [3] CH0_CLKIN3_INV_RXA_Q��ch0 rxa q·clkin3 dff�����ؿ��� 0������ 1������
            [2] CH0_CLKIN3_INV_RXA_I��ch0 rxa i·clkin3 dff�����ؿ��� 0������ 1������
            [1] CH0_CLKIN2_INV_RXA_Q��ch0 rxa q·clkin2 dff�����ؿ��� 0������ 1������
            [0] CH0_CLKIN2_INV_RXA_I��ch0 rxa i·clkin2 dff�����ؿ��� 0������ 1������
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xC9F)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR08
   ��      ����[7] CH0_PD_RXA_I��ch0 rxa i·power down����
            [6] CH0_PD_RXA_Q��ch0 rxa q·power down����
            [5] CH0_PD_RXB_I��ch0 rxb i·power down����
            [4] CH0_PD_RXB_Q��ch0 rxb q·power down����
            [3] reserved
            [2:0] CH0_RX_MODE��ch0 rxģʽѡ��
                  000��4G
                  001��3G
                  010��3G_DC &amp; TDS
                  011��2G_A(Ĭ��)
                  100��CA
                  101��CDMA
                  110:2G_B
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_0_ADDR                      (ABB_BASE_ADDR + 0xCA0)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH0_MODE_IBCT3��ch0 op3ģʽѡ��
            [3:2] CH0_MODE_IBCT2��ch0 op2ģʽѡ��
            [1:0] CH0_MODE_IBCT1��ch0 op1ģʽѡ��
                  OP1/OP2/OP3 Current Seting For Mode
                  11��CA mode Current
                  10��LTE mode Current
                  01��DC/TDS/X/2G_B mode Current
                  00��3G/2G_A mode Current
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xCA1)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR10
   ��      ����[7:6] reserved
            [5] PDM_CTRL: RX ADC���������ģʽѡ��
                1��Binary Encoder
                0��Add Encoder��default��
            [4] DEM_OUTPUT_SEL: DEM�����߼�����
                0��DEM_IN ADD
                1��DEM_IN ENC
            [3] DEM_ENB: ADC DEM���ܹر��ź�
                0��DEM Enable
                1��DEM Disable
            [2:0] DEM mode
                  RX ADC��DAC DEMģʽѡ��
                  000��DWA��default��
                  001��CLA1
                  010��CLA2
                  011��CLA3
                  100��CLA4
                  101��CLA5
                  110��CLA6
                  111��CLA7
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xCA2)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR11
   ��      ����[7:6] CH0_CTRL_RFF��ch0 ǰ������rffѡ��
                  RXģʽ���ƻ�����ǰ������RFF
                  1x��4.865K ohm CA/4G/DC/TDS/X
                  01��9.73K ohm 2G_B
                  00��19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1��ch0 ������1�������rin1ѡ��
                  RXģʽ���ƻ�������һ���������RIN1
                  11��2.8K ohm 2G_B
                  10��5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01��5.6K ohm
                  00��cut off
            [3:2] CH0_CTRL_RIN2��ch0 ������2�������rin2ѡ��
                  RXģʽ���ƻ������ڶ����������RIN2
                  1x��16.6K ohm CA/4G/DC/TDS/X
                  01��33.2K ohm 2G_B
                  00��66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3��ch0 ������3�������rin3ѡ��
                RXģʽ���ƻ������������������RIN3
                1��6.93K ohm CA/4G/DC/TDS/X/2G_B
                0��13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB��ch0 ��������������rfbѡ��
                RXģʽ���ƻ�������������RFB
                1��160K ohm CA/4G/DC/TDS/X/2G_B
                0��320K ohm 3G/2G_A
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xCA3)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH0_CTRL_RSIG��ch0 �������ź�ǰ������rsigѡ��
                  RXģʽ���ƻ������ź�ǰ������RSIG
                  1x��46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01��93K ohm 3G/2G_A
                  00��cut off
            [3:0] CH0_CTRL_RZ��ch0 ������3�������rzѡ��
                  RXģʽ���ƻ������������������ݵ������RZ
                  x000��500 ohm��default��
                  x100��167 ohm
                  x010��143 ohm
                  x110��90 ohm
                  xxx1��0 ohm
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xCA4)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR13
   ��      ����[7:3] reserved
            [2] CH0_DLY_CTRL2��ch0 0.6tsʱ�����ڿ���ѡ��
                RX ADC 0.6Tsʱ�����
                1��DAC3��ʱ0.6Ts
                0��DAC3��ʱ0.5Ts ��default��
            [1] CH0_DCTRL23��ch0 dac23����ģʽѡ��
                RXģʽ����DAC23������������
                1��Double icell23 current CA/4G/DC/TDS/X/2G_B
                0��Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1��ch0 dac1����ģʽѡ��
                RXģʽ����DAC1������������
                1��Double icell1 current 2G_B
                0��Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xCA5)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR14
   ��      ����[7] reserved
            [6:4] CH0_IBCT_QT��ch0 rx QT������С����
                  RX ADC QTƫ�õ�������
                  000�� 5u CA
                  001�� 4u 4G
                  010�� 3u WDC/TDS/2G_B/X
                  011�� 2u 3G/2G_A
                  100�� 10u
                  101�� 9u
                  110�� 8u
                  111�� 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE��ch0 ����������capģʽѡ��
                  RX Integrator Cap Setting For Mode:
                  1x��DC/TDS/X/2G_B/3G/2G_A
                  01��4G
                  00��CA
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xCA6)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH0_IBCT_OP2��ch0 rx op2������С����
            RX ADC OP2ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1��ch0 rx op1������С����
            RX ADC OP1ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xCA7)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH0_IBCT_DAC��ch0 rx dac������С����
            RX ADC DACƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3��ch0 rx op3������С����
            RX ADC OP3ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xCA8)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR17
   ��      ����[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3��ch0 rx������3����cap3�˻�����ѡ��
            RX Integrator Cap3 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
            [1:0] CH0_MULTI_RATE_CAP12��ch0 rx������1����cap1�˻�����ѡ��
            RX Integrator Cap12 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xCA9)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR18
   ��      ����[7] CH0_RXA_DCLK_INV��ch0 rxa dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [6] CH0_RXB_DCLK_INV��ch0 rxb dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [5] CH0_CLKDIV2_A2D��ch0 rx a2d clock����Ƶѡ��
                ��������ֵ�ʱ��MCLK�Ķ���Ƶ����
                0������Ƶ CA/2G_A/2G_B
                1������Ƶ 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX��ch0 rx clock����Ƶѡ��
                �����RXADC��ͨ·��ʱ�ӵĶ���Ƶ����
                0������Ƶ 3G
                1������Ƶ CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV��ch0 rx a2d clock����ѡ��
                ��������ֵ�ʱ��MCLK�������ؿ���
                0������(default)
                1������
            [2:0] CH0_CLKMUX_CTRL��ch0 rx ģʽ��Ƶʱ��ѡ��
                  �ṩ���ϵ�ģ���ʱ�ӵķ�Ƶ����
                  000�� CAģʽ
                  100�� 4Gģʽ
                  110�� WDC/TDS/2G_B/Xģʽ
                  111:3G/2G_Aģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xCAA)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR19
   ��      ����[7:4] CH0_RXA_CLK_QT_CTRL��ch0 rxa qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xCAB)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR20
   ��      ����[7:2] reserved
            [1:0] RX_DLY_CTRL��RXA ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xCAC)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR21
   ��      ����[7:4] CH0_RXB_CLK_QT_CTRL��ch0 rxb qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xCAD)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR22
   ��      ����[7:2] reserved
            [1:0] RXB ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xCAE)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR23
   ��      ����[7] CH0_CLKIN3_INV_RXB_Q��ch0 rxb q·clkin3 dff�����ؿ��� 0������ 1������
            [6] CH0_CLKIN3_INV_RXB_I��ch0 rxb i·clkin3 dff�����ؿ��� 0������ 1������
            [5] CH0_CLKIN2_INV_RXB_Q��ch0 rxb q·clkin2 dff�����ؿ��� 0������ 1������
            [4] CH0_CLKIN2_INV_RXB_I��ch0 rxb i·clkin2 dff�����ؿ��� 0������ 1������
            [3] CH0_CLKIN3_INV_RXA_Q��ch0 rxa q·clkin3 dff�����ؿ��� 0������ 1������
            [2] CH0_CLKIN3_INV_RXA_I��ch0 rxa i·clkin3 dff�����ؿ��� 0������ 1������
            [1] CH0_CLKIN2_INV_RXA_Q��ch0 rxa q·clkin2 dff�����ؿ��� 0������ 1������
            [0] CH0_CLKIN2_INV_RXA_I��ch0 rxa i·clkin2 dff�����ؿ��� 0������ 1������
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xCAF)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR08
   ��      ����[7] CH0_PD_RXA_I��ch0 rxa i·power down����
            [6] CH0_PD_RXA_Q��ch0 rxa q·power down����
            [5] CH0_PD_RXB_I��ch0 rxb i·power down����
            [4] CH0_PD_RXB_Q��ch0 rxb q·power down����
            [3] reserved
            [2:0] CH0_RX_MODE��ch0 rxģʽѡ��
                  000��4G
                  001��3G
                  010��3G_DC &amp; TDS
                  011��2G_A(Ĭ��)
                  100��CA
                  101��CDMA
                  110:2G_B
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_0_ADDR                     (ABB_BASE_ADDR + 0xCB0)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH0_MODE_IBCT3��ch0 op3ģʽѡ��
            [3:2] CH0_MODE_IBCT2��ch0 op2ģʽѡ��
            [1:0] CH0_MODE_IBCT1��ch0 op1ģʽѡ��
                  OP1/OP2/OP3 Current Seting For Mode
                  11��CA mode Current
                  10��LTE mode Current
                  01��DC/TDS/X/2G_B mode Current
                  00��3G/2G_A mode Current
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_1_ADDR                     (ABB_BASE_ADDR + 0xCB1)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR10
   ��      ����[7:6] reserved
            [5] PDM_CTRL: RX ADC���������ģʽѡ��
                1��Binary Encoder
                0��Add Encoder��default��
            [4] DEM_OUTPUT_SEL: DEM�����߼�����
                0��DEM_IN ADD
                1��DEM_IN ENC
            [3] DEM_ENB: ADC DEM���ܹر��ź�
                0��DEM Enable
                1��DEM Disable
            [2:0] DEM mode
                  RX ADC��DAC DEMģʽѡ��
                  000��DWA��default��
                  001��CLA1
                  010��CLA2
                  011��CLA3
                  100��CLA4
                  101��CLA5
                  110��CLA6
                  111��CLA7
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_2_ADDR                     (ABB_BASE_ADDR + 0xCB2)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR11
   ��      ����[7:6] CH0_CTRL_RFF��ch0 ǰ������rffѡ��
                  RXģʽ���ƻ�����ǰ������RFF
                  1x��4.865K ohm CA/4G/DC/TDS/X
                  01��9.73K ohm 2G_B
                  00��19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1��ch0 ������1�������rin1ѡ��
                  RXģʽ���ƻ�������һ���������RIN1
                  11��2.8K ohm 2G_B
                  10��5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01��5.6K ohm
                  00��cut off
            [3:2] CH0_CTRL_RIN2��ch0 ������2�������rin2ѡ��
                  RXģʽ���ƻ������ڶ����������RIN2
                  1x��16.6K ohm CA/4G/DC/TDS/X
                  01��33.2K ohm 2G_B
                  00��66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3��ch0 ������3�������rin3ѡ��
                RXģʽ���ƻ������������������RIN3
                1��6.93K ohm CA/4G/DC/TDS/X/2G_B
                0��13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB��ch0 ��������������rfbѡ��
                RXģʽ���ƻ�������������RFB
                1��160K ohm CA/4G/DC/TDS/X/2G_B
                0��320K ohm 3G/2G_A
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_3_ADDR                     (ABB_BASE_ADDR + 0xCB3)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH0_CTRL_RSIG��ch0 �������ź�ǰ������rsigѡ��
                  RXģʽ���ƻ������ź�ǰ������RSIG
                  1x��46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01��93K ohm 3G/2G_A
                  00��cut off
            [3:0] CH0_CTRL_RZ��ch0 ������3�������rzѡ��
                  RXģʽ���ƻ������������������ݵ������RZ
                  x000��500 ohm��default��
                  x100��167 ohm
                  x010��143 ohm
                  x110��90 ohm
                  xxx1��0 ohm
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_4_ADDR                     (ABB_BASE_ADDR + 0xCB4)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR13
   ��      ����[7:3] reserved
            [2] CH0_DLY_CTRL2��ch0 0.6tsʱ�����ڿ���ѡ��
                RX ADC 0.6Tsʱ�����
                1��DAC3��ʱ0.6Ts
                0��DAC3��ʱ0.5Ts ��default��
            [1] CH0_DCTRL23��ch0 dac23����ģʽѡ��
                RXģʽ����DAC23������������
                1��Double icell23 current CA/4G/DC/TDS/X/2G_B
                0��Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1��ch0 dac1����ģʽѡ��
                RXģʽ����DAC1������������
                1��Double icell1 current 2G_B
                0��Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_5_ADDR                     (ABB_BASE_ADDR + 0xCB5)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR14
   ��      ����[7] reserved
            [6:4] CH0_IBCT_QT��ch0 rx QT������С����
                  RX ADC QTƫ�õ�������
                  000�� 5u CA
                  001�� 4u 4G
                  010�� 3u WDC/TDS/2G_B/X
                  011�� 2u 3G/2G_A
                  100�� 10u
                  101�� 9u
                  110�� 8u
                  111�� 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE��ch0 ����������capģʽѡ��
                  RX Integrator Cap Setting For Mode:
                  1x��DC/TDS/X/2G_B/3G/2G_A
                  01��4G
                  00��CA
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_6_ADDR                     (ABB_BASE_ADDR + 0xCB6)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH0_IBCT_OP2��ch0 rx op2������С����
            RX ADC OP2ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1��ch0 rx op1������С����
            RX ADC OP1ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_7_ADDR                     (ABB_BASE_ADDR + 0xCB7)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH0_IBCT_DAC��ch0 rx dac������С����
            RX ADC DACƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3��ch0 rx op3������С����
            RX ADC OP3ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_8_ADDR                     (ABB_BASE_ADDR + 0xCB8)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR17
   ��      ����[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3��ch0 rx������3����cap3�˻�����ѡ��
            RX Integrator Cap3 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
            [1:0] CH0_MULTI_RATE_CAP12��ch0 rx������1����cap1�˻�����ѡ��
            RX Integrator Cap12 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_9_ADDR                     (ABB_BASE_ADDR + 0xCB9)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR18
   ��      ����[7] CH0_RXA_DCLK_INV��ch0 rxa dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [6] CH0_RXB_DCLK_INV��ch0 rxb dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [5] CH0_CLKDIV2_A2D��ch0 rx a2d clock����Ƶѡ��
                ��������ֵ�ʱ��MCLK�Ķ���Ƶ����
                0������Ƶ CA/2G_A/2G_B
                1������Ƶ 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX��ch0 rx clock����Ƶѡ��
                �����RXADC��ͨ·��ʱ�ӵĶ���Ƶ����
                0������Ƶ 3G
                1������Ƶ CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV��ch0 rx a2d clock����ѡ��
                ��������ֵ�ʱ��MCLK�������ؿ���
                0������(default)
                1������
            [2:0] CH0_CLKMUX_CTRL��ch0 rx ģʽ��Ƶʱ��ѡ��
                  �ṩ���ϵ�ģ���ʱ�ӵķ�Ƶ����
                  000�� CAģʽ
                  100�� 4Gģʽ
                  110�� WDC/TDS/2G_B/Xģʽ
                  111:3G/2G_Aģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_10_ADDR                    (ABB_BASE_ADDR + 0xCBA)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR19
   ��      ����[7:4] CH0_RXA_CLK_QT_CTRL��ch0 rxa qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_11_ADDR                    (ABB_BASE_ADDR + 0xCBB)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR20
   ��      ����[7:2] reserved
            [1:0] RX_DLY_CTRL��RXA ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_12_ADDR                    (ABB_BASE_ADDR + 0xCBC)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR21
   ��      ����[7:4] CH0_RXB_CLK_QT_CTRL��ch0 rxb qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_13_ADDR                    (ABB_BASE_ADDR + 0xCBD)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR22
   ��      ����[7:2] reserved
            [1:0] RXB ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_14_ADDR                    (ABB_BASE_ADDR + 0xCBE)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR23
   ��      ����[7] CH0_CLKIN3_INV_RXB_Q��ch0 rxb q·clkin3 dff�����ؿ��� 0������ 1������
            [6] CH0_CLKIN3_INV_RXB_I��ch0 rxb i·clkin3 dff�����ؿ��� 0������ 1������
            [5] CH0_CLKIN2_INV_RXB_Q��ch0 rxb q·clkin2 dff�����ؿ��� 0������ 1������
            [4] CH0_CLKIN2_INV_RXB_I��ch0 rxb i·clkin2 dff�����ؿ��� 0������ 1������
            [3] CH0_CLKIN3_INV_RXA_Q��ch0 rxa q·clkin3 dff�����ؿ��� 0������ 1������
            [2] CH0_CLKIN3_INV_RXA_I��ch0 rxa i·clkin3 dff�����ؿ��� 0������ 1������
            [1] CH0_CLKIN2_INV_RXA_Q��ch0 rxa q·clkin2 dff�����ؿ��� 0������ 1������
            [0] CH0_CLKIN2_INV_RXA_I��ch0 rxa i·clkin2 dff�����ؿ��� 0������ 1������
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_15_ADDR                    (ABB_BASE_ADDR + 0xCBF)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR08
   ��      ����[7] CH0_PD_RXA_I��ch0 rxa i·power down����
            [6] CH0_PD_RXA_Q��ch0 rxa q·power down����
            [5] CH0_PD_RXB_I��ch0 rxb i·power down����
            [4] CH0_PD_RXB_Q��ch0 rxb q·power down����
            [3] reserved
            [2:0] CH0_RX_MODE��ch0 rxģʽѡ��
                  000��4G
                  001��3G
                  010��3G_DC &amp; TDS
                  011��2G_A(Ĭ��)
                  100��CA
                  101��CDMA
                  110:2G_B
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_0_ADDR                       (ABB_BASE_ADDR + 0xCC0)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH0_MODE_IBCT3��ch0 op3ģʽѡ��
            [3:2] CH0_MODE_IBCT2��ch0 op2ģʽѡ��
            [1:0] CH0_MODE_IBCT1��ch0 op1ģʽѡ��
                  OP1/OP2/OP3 Current Seting For Mode
                  11��CA mode Current
                  10��LTE mode Current
                  01��DC/TDS/X/2G_B mode Current
                  00��3G/2G_A mode Current
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_1_ADDR                       (ABB_BASE_ADDR + 0xCC1)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR10
   ��      ����[7:6] reserved
            [5] PDM_CTRL: RX ADC���������ģʽѡ��
                1��Binary Encoder
                0��Add Encoder��default��
            [4] DEM_OUTPUT_SEL: DEM�����߼�����
                0��DEM_IN ADD
                1��DEM_IN ENC
            [3] DEM_ENB: ADC DEM���ܹر��ź�
                0��DEM Enable
                1��DEM Disable
            [2:0] DEM mode
                  RX ADC��DAC DEMģʽѡ��
                  000��DWA��default��
                  001��CLA1
                  010��CLA2
                  011��CLA3
                  100��CLA4
                  101��CLA5
                  110��CLA6
                  111��CLA7
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_2_ADDR                       (ABB_BASE_ADDR + 0xCC2)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR11
   ��      ����[7:6] CH0_CTRL_RFF��ch0 ǰ������rffѡ��
                  RXģʽ���ƻ�����ǰ������RFF
                  1x��4.865K ohm CA/4G/DC/TDS/X
                  01��9.73K ohm 2G_B
                  00��19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1��ch0 ������1�������rin1ѡ��
                  RXģʽ���ƻ�������һ���������RIN1
                  11��2.8K ohm 2G_B
                  10��5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01��5.6K ohm
                  00��cut off
            [3:2] CH0_CTRL_RIN2��ch0 ������2�������rin2ѡ��
                  RXģʽ���ƻ������ڶ����������RIN2
                  1x��16.6K ohm CA/4G/DC/TDS/X
                  01��33.2K ohm 2G_B
                  00��66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3��ch0 ������3�������rin3ѡ��
                RXģʽ���ƻ������������������RIN3
                1��6.93K ohm CA/4G/DC/TDS/X/2G_B
                0��13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB��ch0 ��������������rfbѡ��
                RXģʽ���ƻ�������������RFB
                1��160K ohm CA/4G/DC/TDS/X/2G_B
                0��320K ohm 3G/2G_A
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_3_ADDR                       (ABB_BASE_ADDR + 0xCC3)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH0_CTRL_RSIG��ch0 �������ź�ǰ������rsigѡ��
                  RXģʽ���ƻ������ź�ǰ������RSIG
                  1x��46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01��93K ohm 3G/2G_A
                  00��cut off
            [3:0] CH0_CTRL_RZ��ch0 ������3�������rzѡ��
                  RXģʽ���ƻ������������������ݵ������RZ
                  x000��500 ohm��default��
                  x100��167 ohm
                  x010��143 ohm
                  x110��90 ohm
                  xxx1��0 ohm
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_4_ADDR                       (ABB_BASE_ADDR + 0xCC4)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR13
   ��      ����[7:3] reserved
            [2] CH0_DLY_CTRL2��ch0 0.6tsʱ�����ڿ���ѡ��
                RX ADC 0.6Tsʱ�����
                1��DAC3��ʱ0.6Ts
                0��DAC3��ʱ0.5Ts ��default��
            [1] CH0_DCTRL23��ch0 dac23����ģʽѡ��
                RXģʽ����DAC23������������
                1��Double icell23 current CA/4G/DC/TDS/X/2G_B
                0��Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1��ch0 dac1����ģʽѡ��
                RXģʽ����DAC1������������
                1��Double icell1 current 2G_B
                0��Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_5_ADDR                       (ABB_BASE_ADDR + 0xCC5)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR14
   ��      ����[7] reserved
            [6:4] CH0_IBCT_QT��ch0 rx QT������С����
                  RX ADC QTƫ�õ�������
                  000�� 5u CA
                  001�� 4u 4G
                  010�� 3u WDC/TDS/2G_B/X
                  011�� 2u 3G/2G_A
                  100�� 10u
                  101�� 9u
                  110�� 8u
                  111�� 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE��ch0 ����������capģʽѡ��
                  RX Integrator Cap Setting For Mode:
                  1x��DC/TDS/X/2G_B/3G/2G_A
                  01��4G
                  00��CA
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_6_ADDR                       (ABB_BASE_ADDR + 0xCC6)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH0_IBCT_OP2��ch0 rx op2������С����
            RX ADC OP2ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1��ch0 rx op1������С����
            RX ADC OP1ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_7_ADDR                       (ABB_BASE_ADDR + 0xCC7)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH0_IBCT_DAC��ch0 rx dac������С����
            RX ADC DACƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3��ch0 rx op3������С����
            RX ADC OP3ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_8_ADDR                       (ABB_BASE_ADDR + 0xCC8)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR17
   ��      ����[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3��ch0 rx������3����cap3�˻�����ѡ��
            RX Integrator Cap3 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
            [1:0] CH0_MULTI_RATE_CAP12��ch0 rx������1����cap1�˻�����ѡ��
            RX Integrator Cap12 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_9_ADDR                       (ABB_BASE_ADDR + 0xCC9)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR18
   ��      ����[7] CH0_RXA_DCLK_INV��ch0 rxa dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [6] CH0_RXB_DCLK_INV��ch0 rxb dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [5] CH0_CLKDIV2_A2D��ch0 rx a2d clock����Ƶѡ��
                ��������ֵ�ʱ��MCLK�Ķ���Ƶ����
                0������Ƶ CA/2G_A/2G_B
                1������Ƶ 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX��ch0 rx clock����Ƶѡ��
                �����RXADC��ͨ·��ʱ�ӵĶ���Ƶ����
                0������Ƶ 3G
                1������Ƶ CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV��ch0 rx a2d clock����ѡ��
                ��������ֵ�ʱ��MCLK�������ؿ���
                0������(default)
                1������
            [2:0] CH0_CLKMUX_CTRL��ch0 rx ģʽ��Ƶʱ��ѡ��
                  �ṩ���ϵ�ģ���ʱ�ӵķ�Ƶ����
                  000�� CAģʽ
                  100�� 4Gģʽ
                  110�� WDC/TDS/2G_B/Xģʽ
                  111:3G/2G_Aģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_10_ADDR                      (ABB_BASE_ADDR + 0xCCA)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR19
   ��      ����[7:4] CH0_RXA_CLK_QT_CTRL��ch0 rxa qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_11_ADDR                      (ABB_BASE_ADDR + 0xCCB)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR20
   ��      ����[7:2] reserved
            [1:0] RX_DLY_CTRL��RXA ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_12_ADDR                      (ABB_BASE_ADDR + 0xCCC)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR21
   ��      ����[7:4] CH0_RXB_CLK_QT_CTRL��ch0 rxb qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_13_ADDR                      (ABB_BASE_ADDR + 0xCCD)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR22
   ��      ����[7:2] reserved
            [1:0] RXB ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_14_ADDR                      (ABB_BASE_ADDR + 0xCCE)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR23
   ��      ����[7] CH0_CLKIN3_INV_RXB_Q��ch0 rxb q·clkin3 dff�����ؿ��� 0������ 1������
            [6] CH0_CLKIN3_INV_RXB_I��ch0 rxb i·clkin3 dff�����ؿ��� 0������ 1������
            [5] CH0_CLKIN2_INV_RXB_Q��ch0 rxb q·clkin2 dff�����ؿ��� 0������ 1������
            [4] CH0_CLKIN2_INV_RXB_I��ch0 rxb i·clkin2 dff�����ؿ��� 0������ 1������
            [3] CH0_CLKIN3_INV_RXA_Q��ch0 rxa q·clkin3 dff�����ؿ��� 0������ 1������
            [2] CH0_CLKIN3_INV_RXA_I��ch0 rxa i·clkin3 dff�����ؿ��� 0������ 1������
            [1] CH0_CLKIN2_INV_RXA_Q��ch0 rxa q·clkin2 dff�����ؿ��� 0������ 1������
            [0] CH0_CLKIN2_INV_RXA_I��ch0 rxa i·clkin2 dff�����ؿ��� 0������ 1������
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_15_ADDR                      (ABB_BASE_ADDR + 0xCCF)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR08
   ��      ����[7] CH0_PD_RXA_I��ch0 rxa i·power down����
            [6] CH0_PD_RXA_Q��ch0 rxa q·power down����
            [5] CH0_PD_RXB_I��ch0 rxb i·power down����
            [4] CH0_PD_RXB_Q��ch0 rxb q·power down����
            [3] reserved
            [2:0] CH0_RX_MODE��ch0 rxģʽѡ��
                  000��4G
                  001��3G
                  010��3G_DC &amp; TDS
                  011��2G_A(Ĭ��)
                  100��CA
                  101��CDMA
                  110:2G_B
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_0_ADDR                    (ABB_BASE_ADDR + 0xCD0)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH0_MODE_IBCT3��ch0 op3ģʽѡ��
            [3:2] CH0_MODE_IBCT2��ch0 op2ģʽѡ��
            [1:0] CH0_MODE_IBCT1��ch0 op1ģʽѡ��
                  OP1/OP2/OP3 Current Seting For Mode
                  11��CA mode Current
                  10��LTE mode Current
                  01��DC/TDS/X/2G_B mode Current
                  00��3G/2G_A mode Current
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_1_ADDR                    (ABB_BASE_ADDR + 0xCD1)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR10
   ��      ����[7:6] reserved
            [5] PDM_CTRL: RX ADC���������ģʽѡ��
                1��Binary Encoder
                0��Add Encoder��default��
            [4] DEM_OUTPUT_SEL: DEM�����߼�����
                0��DEM_IN ADD
                1��DEM_IN ENC
            [3] DEM_ENB: ADC DEM���ܹر��ź�
                0��DEM Enable
                1��DEM Disable
            [2:0] DEM mode
                  RX ADC��DAC DEMģʽѡ��
                  000��DWA��default��
                  001��CLA1
                  010��CLA2
                  011��CLA3
                  100��CLA4
                  101��CLA5
                  110��CLA6
                  111��CLA7
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_2_ADDR                    (ABB_BASE_ADDR + 0xCD2)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR11
   ��      ����[7:6] CH0_CTRL_RFF��ch0 ǰ������rffѡ��
                  RXģʽ���ƻ�����ǰ������RFF
                  1x��4.865K ohm CA/4G/DC/TDS/X
                  01��9.73K ohm 2G_B
                  00��19.46K ohm 3G/2G_A
            [5:4] CH0_CTRL_RIN1��ch0 ������1�������rin1ѡ��
                  RXģʽ���ƻ�������һ���������RIN1
                  11��2.8K ohm 2G_B
                  10��5.6K ohm CA/4G/DC/TDS/X/3G/2G_A
                  01��5.6K ohm
                  00��cut off
            [3:2] CH0_CTRL_RIN2��ch0 ������2�������rin2ѡ��
                  RXģʽ���ƻ������ڶ����������RIN2
                  1x��16.6K ohm CA/4G/DC/TDS/X
                  01��33.2K ohm 2G_B
                  00��66.4K ohm 3G/2G_A
            [1] CH0_CTRL_RIN3��ch0 ������3�������rin3ѡ��
                RXģʽ���ƻ������������������RIN3
                1��6.93K ohm CA/4G/DC/TDS/X/2G_B
                0��13.86K ohm 3G/2G_A
            [0] CH0_CTRL_RFB��ch0 ��������������rfbѡ��
                RXģʽ���ƻ�������������RFB
                1��160K ohm CA/4G/DC/TDS/X/2G_B
                0��320K ohm 3G/2G_A
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_3_ADDR                    (ABB_BASE_ADDR + 0xCD3)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH0_CTRL_RSIG��ch0 �������ź�ǰ������rsigѡ��
                  RXģʽ���ƻ������ź�ǰ������RSIG
                  1x��46.5K ohm CA/4G/DC/TDS/X/2G_B
                  01��93K ohm 3G/2G_A
                  00��cut off
            [3:0] CH0_CTRL_RZ��ch0 ������3�������rzѡ��
                  RXģʽ���ƻ������������������ݵ������RZ
                  x000��500 ohm��default��
                  x100��167 ohm
                  x010��143 ohm
                  x110��90 ohm
                  xxx1��0 ohm
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_4_ADDR                    (ABB_BASE_ADDR + 0xCD4)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR13
   ��      ����[7:3] reserved
            [2] CH0_DLY_CTRL2��ch0 0.6tsʱ�����ڿ���ѡ��
                RX ADC 0.6Tsʱ�����
                1��DAC3��ʱ0.6Ts
                0��DAC3��ʱ0.5Ts ��default��
            [1] CH0_DCTRL23��ch0 dac23����ģʽѡ��
                RXģʽ����DAC23������������
                1��Double icell23 current CA/4G/DC/TDS/X/2G_B
                0��Normal icell23 current 3G/2G_A
            [0] CH0_DCTRL1��ch0 dac1����ģʽѡ��
                RXģʽ����DAC1������������
                1��Double icell1 current 2G_B
                0��Normal icell1 current  CA/4G/3G/DC/TDS/X/2G_A
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_5_ADDR                    (ABB_BASE_ADDR + 0xCD5)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR14
   ��      ����[7] reserved
            [6:4] CH0_IBCT_QT��ch0 rx QT������С����
                  RX ADC QTƫ�õ�������
                  000�� 5u CA
                  001�� 4u 4G
                  010�� 3u WDC/TDS/2G_B/X
                  011�� 2u 3G/2G_A
                  100�� 10u
                  101�� 9u
                  110�� 8u
                  111�� 7u
            [3:2] reserved
            [1:0] CH0_RX_CAP_MODE��ch0 ����������capģʽѡ��
                  RX Integrator Cap Setting For Mode:
                  1x��DC/TDS/X/2G_B/3G/2G_A
                  01��4G
                  00��CA
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_6_ADDR                    (ABB_BASE_ADDR + 0xCD6)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH0_IBCT_OP2��ch0 rx op2������С����
            RX ADC OP2ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP1��ch0 rx op1������С����
            RX ADC OP1ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_7_ADDR                    (ABB_BASE_ADDR + 0xCD7)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH0_IBCT_DAC��ch0 rx dac������С����
            RX ADC DACƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
            [3] reserved
            [2:0] CH0_IBCT_OP3��ch0 rx op3������С����
            RX ADC OP3ƫ�õ�������
            000�� 5u(default)
            001�� 4u
            010�� 3u
            011�� 2u
            100�� 10u
            101�� 9u
            110�� 8u
            111�� 7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_8_ADDR                    (ABB_BASE_ADDR + 0xCD8)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR17
   ��      ����[7:4] reserved
            [3:2] CH0_MULTI_RATE_CAP3��ch0 rx������3����cap3�˻�����ѡ��
            RX Integrator Cap3 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
            [1:0] CH0_MULTI_RATE_CAP12��ch0 rx������1����cap1�˻�����ѡ��
            RX Integrator Cap12 Multi Rate:
            11��x1.125
            10��x1.25 ��for X mode��
            01��x1.5
            00��x1
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_9_ADDR                    (ABB_BASE_ADDR + 0xCD9)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR18
   ��      ����[7] CH0_RXA_DCLK_INV��ch0 rxa dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [6] CH0_RXB_DCLK_INV��ch0 rxb dclk�������ѡ��
                �����RX SYNCģ���ʱ�ӵ������ؿ���
                0������(default)
                1������
            [5] CH0_CLKDIV2_A2D��ch0 rx a2d clock����Ƶѡ��
                ��������ֵ�ʱ��MCLK�Ķ���Ƶ����
                0������Ƶ CA/2G_A/2G_B
                1������Ƶ 4G/3G/DC/TDS/X
            [4] CH0_CLKDIV2_RX��ch0 rx clock����Ƶѡ��
                �����RXADC��ͨ·��ʱ�ӵĶ���Ƶ����
                0������Ƶ 3G
                1������Ƶ CA/4G/DC/TDS/2G_A/2G_B/X
            [3] CH0_DCLK_A2D_INV��ch0 rx a2d clock����ѡ��
                ��������ֵ�ʱ��MCLK�������ؿ���
                0������(default)
                1������
            [2:0] CH0_CLKMUX_CTRL��ch0 rx ģʽ��Ƶʱ��ѡ��
                  �ṩ���ϵ�ģ���ʱ�ӵķ�Ƶ����
                  000�� CAģʽ
                  100�� 4Gģʽ
                  110�� WDC/TDS/2G_B/Xģʽ
                  111:3G/2G_Aģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_10_ADDR                   (ABB_BASE_ADDR + 0xCDA)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR19
   ��      ����[7:4] CH0_RXA_CLK_QT_CTRL��ch0 rxa qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_11_ADDR                   (ABB_BASE_ADDR + 0xCDB)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR20
   ��      ����[7:2] reserved
            [1:0] RX_DLY_CTRL��RXA ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_12_ADDR                   (ABB_BASE_ADDR + 0xCDC)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR21
   ��      ����[7:4] CH0_RXB_CLK_QT_CTRL��ch0 rxb qt��ʱѡ��
            RX ADC��QT����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
            [3:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb dac3��ʱѡ��
            RX ADC�з���DAC3����ʱ����
            0000��20ps
            0001��40ps
            ��
            1000:180ps
            1001:200ps
            ��
            1110��300ps
            1111��320ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_13_ADDR                   (ABB_BASE_ADDR + 0xCDD)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR22
   ��      ����[7:2] reserved
            [1:0] RXB ADC���������Ĺ̶���ʱ����
                  11��300ps
                  10��200ps
                  01��100ps
                  00��0ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_14_ADDR                   (ABB_BASE_ADDR + 0xCDE)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR23
   ��      ����[7] CH0_CLKIN3_INV_RXB_Q��ch0 rxb q·clkin3 dff�����ؿ��� 0������ 1������
            [6] CH0_CLKIN3_INV_RXB_I��ch0 rxb i·clkin3 dff�����ؿ��� 0������ 1������
            [5] CH0_CLKIN2_INV_RXB_Q��ch0 rxb q·clkin2 dff�����ؿ��� 0������ 1������
            [4] CH0_CLKIN2_INV_RXB_I��ch0 rxb i·clkin2 dff�����ؿ��� 0������ 1������
            [3] CH0_CLKIN3_INV_RXA_Q��ch0 rxa q·clkin3 dff�����ؿ��� 0������ 1������
            [2] CH0_CLKIN3_INV_RXA_I��ch0 rxa i·clkin3 dff�����ؿ��� 0������ 1������
            [1] CH0_CLKIN2_INV_RXA_Q��ch0 rxa q·clkin2 dff�����ؿ��� 0������ 1������
            [0] CH0_CLKIN2_INV_RXA_I��ch0 rxa i·clkin2 dff�����ؿ��� 0������ 1������
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_15_ADDR                   (ABB_BASE_ADDR + 0xCDF)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7:0] CH1_REG_TUNE1��ch1 rx cap1�ֶ����üĴ���
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA16_ADDR                  (ABB_BASE_ADDR + 0xCE0)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7:0] CH1_REG_TUNE2��ch1 rx cap2�ֶ����üĴ���
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA17_ADDR                  (ABB_BASE_ADDR + 0xCE1)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7:0] CH1_REG_TUNE3��ch1 rx cap3�ֶ����üĴ���
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA18_ADDR                  (ABB_BASE_ADDR + 0xCE2)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7] rc tuning ģʽѡ��0.�Ĵ����ֶ����ã�1.�Է�
            [6:0]  reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA19_ADDR                  (ABB_BASE_ADDR + 0xCE3)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7] reserved
            [6:4] CH0_OL_CTRL��ch0 rx overload����ѡ��
                  ADC Overloadģ������
                  00��16����������������С��
                  01��8����������������С��
                  10��4����������������С��
                  11���ر�Overload���
            [3:2] reserved
            [1] CH0_PUP_CLK_CTRL��ch0 rx �ϵ�ģ���ʱ�ӿ���
                0���ϵ���ɺ�ر��ϵ�ģ���ʱ�� (default)
                1���ϵ���ɺ󲻹ر��ϵ�ģ��ʱ��
            [0] CH0_PUP_MODE��ch0 rx �����ϵ�ģʽ
                ADCģ���ϵ�ģʽѡ��
                0���Զ�ģʽ
                1�����üĴ����ϵ�ģʽ
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA20_ADDR                  (ABB_BASE_ADDR + 0xCE4)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7:0] CH0_PUP_CTRL��ch0 rx �����ϵ����
            [7] ���üĴ����ϵ�ģʽʱADC��RST_CAP����
            0��Reset CAP3
            1����Reset CAP3
            [6]���üĴ����ϵ�ģʽʱADC��RST_CAP����
            0��Reset CAP2
            1����Reset CAP2
            [5]���üĴ����ϵ�ģʽʱADC��RST_CAP����
            0��Reset CAP1
            1����Reset CAP1
            [4]���üĴ����ϵ�ģʽʱADC��OP����
            0��OP Power Down
            1��OP Power On
            [3]���üĴ����ϵ�ģʽʱADC��DAC����
            0��DAC Power Down
            1��DAC Power On
            [2]���üĴ����ϵ�ģʽʱADC��QTУ������
            0��QT Calibration On
            1��QT Calibration Off
            [1]���üĴ����ϵ�ģʽʱADC��CLKGEN����
            0��CLKGEN Power Down
            1��CLKGEN Power On
            [0]���üĴ����ϵ�ģʽʱADC��QT����
            0��QT Power Down
            1��QT Power On
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA21_ADDR                  (ABB_BASE_ADDR + 0xCE5)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7:6] RXͨ��OP1У��CAL���ؿ���
            00��
            01��
            10��
            11��
            [5] CH0_CAL_TRIM_SW��ch0 rx op1У׼trim���ؿ���
                RXͨ��OP1У��Trim����
                0��Trim Switch Off
                1��Trim Switch On
            [4] CH0_OPCAL_VCM_SEL��ch0 rx op1У׼��ģѡ��
                0��Disable
                1��Enable���̽ӹ�ģ����OP Calibration��
            [3] CH0_RXB_EN_QTCAL��ch0 rx qtУ׼enable
            [2] CH0_RXA_EN_QTCAL��ch0 rx qtУ׼enable
            [1] CH0_RXB_EN_OPCAL��ch0 rx op1У׼enable
            [0] CH0_RXA_EN_OPCAL��ch0 rx op1У׼enable
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA22_ADDR                  (ABB_BASE_ADDR + 0xCE6)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7] reserved
            [6] RXB_PD_CAL ( NC ��
            [5] RXA_PD_CAL ( NC ��
            [4] RX_VCM_ADJ_CTRL
                ���빲ģ��ƽѡ��
                0��0.8V VCM Input
                1��0.5V VCM Input
            [3:1] reserved
            [0] CH0_QT_REF_SEL��ch0 rx qt��refѡ��
                RX��QT��VREFP/VRENѡ��
                0����refģ���ṩ
                1���ɱ��ص����ѹ�ṩ
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA23_ADDR                  (ABB_BASE_ADDR + 0xCE7)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA24_ADDR                  (ABB_BASE_ADDR + 0xCE8)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA25_ADDR                  (ABB_BASE_ADDR + 0xCE9)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA26_ADDR                  (ABB_BASE_ADDR + 0xCEA)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA27_ADDR                  (ABB_BASE_ADDR + 0xCEB)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA28_ADDR                  (ABB_BASE_ADDR + 0xCEC)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA29_ADDR                  (ABB_BASE_ADDR + 0xCED)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7] TX rc tuning ģʽѡ��0.�Ĵ����ֶ����ã�1.�Է�
            [6:0]  reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA30_ADDR                  (ABB_BASE_ADDR + 0xCEE)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7]
            [6:0] TX tuning �����üĴ���
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA31_ADDR                  (ABB_BASE_ADDR + 0xCEF)





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
                     (1/4) register_define_abb_com
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : ABB_TESTMODE_UNION
 �ṹ˵��  : TESTMODE �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00�����:8
 �Ĵ���˵��: ����ģʽ�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_iq_chnl_sel : 1;  /* bit[0]  :  */
        unsigned long  rx_ab_chnl_sel : 1;  /* bit[1]  :  */
        unsigned long  reserved_0     : 2;  /* bit[2-3]: ���� */
        unsigned long  test_mode      : 2;  /* bit[4-5]: bit[4:3]����ģʽ���ƣ�
                                                         00������ģʽ(Ĭ��)
                                                         01�������㷨�߼�����ģʽ
                                                         10��RXģ�����ģʽ(bypass RX�����˲���)
                                                         11������/ģ��ӿڻ���
                                                         bit[5] reserved */
        unsigned long  reserved_1     : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TESTMODE_UNION;
#define ABB_TESTMODE_rx_iq_chnl_sel_START  (0)
#define ABB_TESTMODE_rx_iq_chnl_sel_END    (0)
#define ABB_TESTMODE_rx_ab_chnl_sel_START  (1)
#define ABB_TESTMODE_rx_ab_chnl_sel_END    (1)
#define ABB_TESTMODE_test_mode_START       (4)
#define ABB_TESTMODE_test_mode_END         (5)


/*****************************************************************************
 �ṹ��    : ABB_ATE_TESTMODE_UNION
 �ṹ˵��  : ATE_TESTMODE �Ĵ����ṹ���塣��ַƫ����:0x001����ֵ:0x00�����:8
 �Ĵ���˵��: ATE_TEST_MODE
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ate_ch_sel : 3;  /* bit[0-2]:  */
        unsigned long  reserved   : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_ATE_TESTMODE_UNION;
#define ABB_ATE_TESTMODE_ate_ch_sel_START  (0)
#define ABB_ATE_TESTMODE_ate_ch_sel_END    (2)


/*****************************************************************************
 �ṹ��    : ABB_TCXO_RPT_UNION
 �ṹ˵��  : TCXO_RPT �Ĵ����ṹ���塣��ַƫ����:0x002����ֵ:0x00�����:8
 �Ĵ���˵��: TCXO_RPT
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tcxo_en  : 1;  /* bit[0]  :  */
        unsigned long  reserved : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_TCXO_RPT_UNION;
#define ABB_TCXO_RPT_tcxo_en_START   (0)
#define ABB_TCXO_RPT_tcxo_en_END     (0)


/*****************************************************************************
 �ṹ��    : ABB_ABB_DIG_PWR_RST_UNION
 �ṹ˵��  : ABB_DIG_PWR_RST �Ĵ����ṹ���塣��ַƫ����:0x003����ֵ:0x00�����:8
 �Ĵ���˵��: ABB���ֲ��ָ�λ�ź�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  abb_sw_rst_en : 1;  /* bit[0]  :  */
        unsigned long  reserved      : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_ABB_DIG_PWR_RST_UNION;
#define ABB_ABB_DIG_PWR_RST_abb_sw_rst_en_START  (0)
#define ABB_ABB_DIG_PWR_RST_abb_sw_rst_en_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_CH0_COMM_REG_DEBUG_DIG_UNION
 �ṹ˵��  : CH0_COMM_REG_DEBUG_DIG �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00�����:8
 �Ĵ���˵��: ���ֵ��ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  clk_out_sel0 : 2;  /* bit[0-1]: ���ֵ��ԼĴ���
                                                       bit[0]���ܽ�CH0_CLK_52M���ʱ��ѡ��
                                                       1�����GPLL
                                                       0�����SCPLL0 */
        unsigned long  reserved     : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH0_COMM_REG_DEBUG_DIG_UNION;
#define ABB_CH0_COMM_REG_DEBUG_DIG_clk_out_sel0_START  (0)
#define ABB_CH0_COMM_REG_DEBUG_DIG_clk_out_sel0_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH1_COMM_REG_DEBUG_DIG_UNION
 �ṹ˵��  : CH1_COMM_REG_DEBUG_DIG �Ĵ����ṹ���塣��ַƫ����:0x005����ֵ:0x00�����:8
 �Ĵ���˵��: ���ֵ��ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  clk_out_sel1 : 2;  /* bit[0-1]: ���ֵ��ԼĴ���
                                                       bit[0]���ܽ�CH1_CLK_52M���ʱ��ѡ��
                                                       1�����GPLL
                                                       0�����SCPLL1 */
        unsigned long  reserved     : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_CH1_COMM_REG_DEBUG_DIG_UNION;
#define ABB_CH1_COMM_REG_DEBUG_DIG_clk_out_sel1_START  (0)
#define ABB_CH1_COMM_REG_DEBUG_DIG_clk_out_sel1_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_BIST_CFG_1_UNION
 �ṹ˵��  : BIST_CFG_1 �Ĵ����ṹ���塣��ַƫ����:0x006����ֵ:0x00�����:8
 �Ĵ���˵��: BIST���üĴ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_en               : 1;  /* bit[0]  : BISTʹ�ܡ�
                                                                0����ʹ�ܣ�
                                                                1��ʹ�ܡ� */
        unsigned long  bist_delay1           : 2;  /* bit[1-2]: ��ʱʱ��1����ֵ,ͨ·ʹ�ܵ����Կ�ʼ����ʱʱ��ѡ��
                                                                00:50us��Ĭ�ϣ�
                                                                01:100us
                                                                10:200us
                                                                11:500us */
        unsigned long  bist_delay2           : 2;  /* bit[3-4]: ��ʱʱ��2����ֵ,�ź�ֱ�����������ȶ�ʱ�����á�
                                                                00:20us��Ĭ�ϣ�
                                                                01:50us
                                                                10:200us
                                                                11:500us */
        unsigned long  bist_switch_delay_sel : 2;  /* bit[5-6]: �л�iq��ͨ��ʱ����30����·ʱ����ʱ���ڴ˻��������ӵ���ʱSwitch_delay��ѡ���źţ�
                                                                00��0us��(Ĭ��)
                                                                01��20us��
                                                                10��50us��
                                                                11��200us�� */
        unsigned long  bist_ch_en_ctrl       : 1;  /* bit[7]  : bist����ͨ���߿ؿ���ģʽ��
                                                                0��ͨ���߿�bist����ʱȫ������
                                                                1��ͨ���߿�bist����ʱ����ͨ�����ߣ��������͡� */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_CFG_1_UNION;
#define ABB_BIST_CFG_1_bist_en_START                (0)
#define ABB_BIST_CFG_1_bist_en_END                  (0)
#define ABB_BIST_CFG_1_bist_delay1_START            (1)
#define ABB_BIST_CFG_1_bist_delay1_END              (2)
#define ABB_BIST_CFG_1_bist_delay2_START            (3)
#define ABB_BIST_CFG_1_bist_delay2_END              (4)
#define ABB_BIST_CFG_1_bist_switch_delay_sel_START  (5)
#define ABB_BIST_CFG_1_bist_switch_delay_sel_END    (6)
#define ABB_BIST_CFG_1_bist_ch_en_ctrl_START        (7)
#define ABB_BIST_CFG_1_bist_ch_en_ctrl_END          (7)


/*****************************************************************************
 �ṹ��    : ABB_BIST_CFG_4_UNION
 �ṹ˵��  : BIST_CFG_4 �Ĵ����ṹ���塣��ַƫ����:0x009����ֵ:0x00�����:8
 �Ĵ���˵��: BIST������Ŀbypass�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_test_bypass : 6;  /* bit[0-5]: ������bypass�źţ�
                                                           [0]:1��ʾDC_Iָ��bypass��0��ʾ��bypass��
                                                           [1]:1��ʾDC_Qָ��bypass��0��ʾ��bypass��
                                                           [2]:1��ʾSNDR_Iָ��bypass��0��ʾ��bypass��
                                                           [3]:1��ʾSNDR_Qָ��bypass��0��ʾ��bypass��
                                                           [4]:1��ʾGAIN_MISMATCHָ��bypass��0��ʾ��bypass��
                                                           [5]:1��ʾGAIN_ERRORָ��bypass��0��ʾ��bypass�� */
        unsigned long  reserved         : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_CFG_4_UNION;
#define ABB_BIST_CFG_4_bist_test_bypass_START  (0)
#define ABB_BIST_CFG_4_bist_test_bypass_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_BIST_CFG_5_UNION
 �ṹ˵��  : BIST_CFG_5 �Ĵ����ṹ���塣��ַƫ����:0x00A����ֵ:0x00�����:8
 �Ĵ���˵��: BIST�ֶ��������üĴ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_manual    : 1;  /* bit[0]  : 0���Զ���������
                                                         1���ֶ��������� */
        unsigned long  bist_rx_ch_sel : 3;  /* bit[1-3]: �ֶ�����ѡ����������ͨ����
                                                         000��RXA��CH0��
                                                         001��RXB��CH0��
                                                         010��RXA��CH1��
                                                         011��RXB��CH1��
                                                         100��RXA��CH2��
                                                         101��RXB��CH2��
                                                         110��RXA��CH3��
                                                         111��RXB��CH3�� */
        unsigned long  bist_gate_bp   : 1;  /* bit[4]  : 0��bistʱ�����ſؿ��ƣ�bist_en���ߺ�bist����ʱ�ӡ���Ĭ�ϣ�
                                                         1��bistʱ�Ӳ����ſؿ��ơ� */
        unsigned long  reserved       : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_CFG_5_UNION;
#define ABB_BIST_CFG_5_bist_manual_START     (0)
#define ABB_BIST_CFG_5_bist_manual_END       (0)
#define ABB_BIST_CFG_5_bist_rx_ch_sel_START  (1)
#define ABB_BIST_CFG_5_bist_rx_ch_sel_END    (3)
#define ABB_BIST_CFG_5_bist_gate_bp_START    (4)
#define ABB_BIST_CFG_5_bist_gate_bp_END      (4)


/*****************************************************************************
 �ṹ��    : ABB_BIST_RPT_1_UNION
 �ṹ˵��  : BIST_RPT_1 �Ĵ����ṹ���塣��ַƫ����:0x00B����ֵ:0x00�����:8
 �Ĵ���˵��: BIST���״̬�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_done : 1;  /* bit[0]  : SNDR�������״̬��
                                                    0��û����ɣ�
                                                    1����ɡ� */
        unsigned long  reserved  : 6;  /* bit[1-6]: ���� */
        unsigned long  bist_pass : 1;  /* bit[7]  : BIST���������Ĳ������Ƿ�ͨ������δbypass�Ĳ����Ƿ�ȫ��ͨ����
                                                    0��δͨ����
                                                    1��ͨ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_BIST_RPT_1_UNION;
#define ABB_BIST_RPT_1_bist_done_START  (0)
#define ABB_BIST_RPT_1_bist_done_END    (0)
#define ABB_BIST_RPT_1_bist_pass_START  (7)
#define ABB_BIST_RPT_1_bist_pass_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_BIST_RPT_2_UNION
 �ṹ˵��  : BIST_RPT_2 �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x00�����:8
 �Ĵ���˵��: BIST����ϱ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  para_pass_flag : 6;  /* bit[0-5]: ÿһ�μ������6�������Ƿ�pass��
                                                         [0]:1��ʾDC_Iָ��pass��0��ʾ��pass��
                                                         [1]:1��ʾDC_Qָ��pass��0��ʾ��pass��
                                                         [2]:1��ʾSNDR_Iָ��pass��0��ʾ��pass��
                                                         [3]:1��ʾSNDR_Qָ��pass��0��ʾ��pass��
                                                         [4]:1��ʾGAIN_MISMATCHָ��pass��0��ʾ��pass��
                                                         [5]:1��ʾGAIN_ERRORָ��pass��0��ʾ��pass�� */
        unsigned long  reserved       : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_RPT_2_UNION;
#define ABB_BIST_RPT_2_para_pass_flag_START  (0)
#define ABB_BIST_RPT_2_para_pass_flag_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_BIST_RPT_8_UNION
 �ṹ˵��  : BIST_RPT_8 �Ĵ����ṹ���塣��ַƫ����:0x012����ֵ:0x00�����:8
 �Ĵ���˵��: BIST����ϱ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_dc_i_msb : 3;  /* bit[0-2]: I·dc�ϱ�ֵ��λ�� */
        unsigned long  reserved      : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_RPT_8_UNION;
#define ABB_BIST_RPT_8_bist_dc_i_msb_START  (0)
#define ABB_BIST_RPT_8_bist_dc_i_msb_END    (2)


/*****************************************************************************
 �ṹ��    : ABB_BIST_RPT_10_UNION
 �ṹ˵��  : BIST_RPT_10 �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x00�����:8
 �Ĵ���˵��: BIST����ϱ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_dc_q_msb : 3;  /* bit[0-2]: Q·dc�ϱ�ֵ��λ�� */
        unsigned long  reserved      : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_RPT_10_UNION;
#define ABB_BIST_RPT_10_bist_dc_q_msb_START  (0)
#define ABB_BIST_RPT_10_bist_dc_q_msb_END    (2)


/*****************************************************************************
 �ṹ��    : ABB_BIST_CFG_6_UNION
 �ṹ˵��  : BIST_CFG_6 �Ĵ����ṹ���塣��ַƫ����:0x01F����ֵ:0x3E�����:8
 �Ĵ���˵��: BIST�����׼�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  dc_min_msb : 6;  /* bit[0-5]: BIST DC������޸�6bit���з������� */
        unsigned long  reserved   : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_BIST_CFG_6_UNION;
#define ABB_BIST_CFG_6_dc_min_msb_START  (0)
#define ABB_BIST_CFG_6_dc_min_msb_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_BIST_CFG_8_UNION
 �ṹ˵��  : BIST_CFG_8 �Ĵ����ṹ���塣��ַƫ����:0x021����ֵ:0x01�����:8
 �Ĵ���˵��: BIST�����׼�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  dc_max_msb : 6;  /* bit[0-5]: BIST DC������޸�6bit���з������� */
        unsigned long  reserved   : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_BIST_CFG_8_UNION;
#define ABB_BIST_CFG_8_dc_max_msb_START  (0)
#define ABB_BIST_CFG_8_dc_max_msb_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_BIST_TCXO_SEL_UNION
 �ṹ˵��  : BIST_TCXO_SEL �Ĵ����ṹ���塣��ַƫ����:0x03F����ֵ:0x00�����:8
 �Ĵ���˵��: BIST_TCXO_SEL
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  bist_tcxo_sel : 2;  /* bit[0-1]: bist_tcxo_sel:
                                                        0:19.2M
                                                        1:20.48M
                                                        2:30.72M
                                                        3:38.74M */
        unsigned long  reserved      : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_BIST_TCXO_SEL_UNION;
#define ABB_BIST_TCXO_SEL_bist_tcxo_sel_START  (0)
#define ABB_BIST_TCXO_SEL_bist_tcxo_sel_END    (1)


/***======================================================================***
                     (2/4) register_define_abb_tx
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : ABB_TX_IDLE_DIG_1_UNION
 �ṹ˵��  : tx_idle_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x200����ֵ:0x02�����:8
 �Ĵ���˵��: TX IDLEģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_comp_bp_idle  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                           0����bypass(Ĭ��)
                                                           1��bypass */
        unsigned long  tx_hb_bp_idle    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                           0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                           1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  tx_rate_idle     : 3;  /* bit[2-4]: TXͨ��CIC�˲����������ʿ��ƣ�
                                                                2G,     3G,     4G,      TDS,      CDMA,    CA
                                                               (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
                                                           0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(Ĭ��)
                                                           1��2.16MHz,15.36MHz,30.72MHz, */
        unsigned long  tx_mode_dig_idle : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                           000��2G(Ĭ��)
                                                           001��3G
                                                           010��4G
                                                           011��TDS
                                                           100��CDMA
                                                           101��CA
                                                           Others��Reserved */
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
 �ṹ˵��  : tx_idle_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x201����ֵ:0x2B�����:8
 �Ĵ���˵��: TX IDLEģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
        unsigned long  dem_const_idle     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����
                                                             0��0(Ĭ��)
                                                             1��2
                                                             2��4
                                                             3��6 */
        unsigned long  uddwa_dith_en_idle : 1;  /* bit[4]  : TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  dem_dwa_en_idle    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                             0��ʹ��CLAģʽ
                                                             1��ʹ��DWAģʽ(Ĭ��)  */
        unsigned long  dem_lsb_bp_idle    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                             0��DEM LSB ��(Ĭ��)
                                                             1��DEM LSB bypass */
        unsigned long  dem_msb_bp_idle    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                             0��DEM MSB��(Ĭ��)
                                                             1��DEM MSB bypass */
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
#define ABB_TX_IDLE_DIG_2_dem_lsb_bp_idle_START     (6)
#define ABB_TX_IDLE_DIG_2_dem_lsb_bp_idle_END       (6)
#define ABB_TX_IDLE_DIG_2_dem_msb_bp_idle_START     (7)
#define ABB_TX_IDLE_DIG_2_dem_msb_bp_idle_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_IDLE_DIG_3_UNION
 �ṹ˵��  : tx_idle_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x202����ֵ:0x00�����:8
 �Ĵ���˵��: TX IDLEģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0       : 1;  /* bit[0]  : ���� */
        unsigned long  tx_flush_en_idle : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                           0����ʹ��
                                                           1��ʹ�� */
        unsigned long  tx_comp_sel_idle : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                           00���̶�ϵ��1��
                                                           01���̶�ϵ��2��
                                                           10���̶�ϵ��3��
                                                           11������ϵ���� */
        unsigned long  reserved_1       : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_TX_IDLE_DIG_3_UNION;
#define ABB_TX_IDLE_DIG_3_tx_flush_en_idle_START  (1)
#define ABB_TX_IDLE_DIG_3_tx_flush_en_idle_END    (1)
#define ABB_TX_IDLE_DIG_3_tx_comp_sel_idle_START  (2)
#define ABB_TX_IDLE_DIG_3_tx_comp_sel_idle_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_TX_2G_DIG_1_UNION
 �ṹ˵��  : tx_2g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x203����ֵ:0x02�����:8
 �Ĵ���˵��: TX 2Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_comp_bp_2g  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                         0����bypass(Ĭ��)
                                                         1��bypass */
        unsigned long  tx_hb_bp_2g    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                         0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2
                                                         1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate(Ĭ��) */
        unsigned long  tx_rate_2g     : 3;  /* bit[2-4]: TXͨ��CIC�˲����������ʿ��ƣ�
                                                              2G,     3G,     4G,      TDS,      CDMA,    CA
                                                             (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
                                                         0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(Ĭ��)
                                                         1��2.16MHz,15.36MHz,30.72MHz, */
        unsigned long  tx_mode_dig_2g : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                         000��2G(Ĭ��)
                                                         001��3G
                                                         010��4G
                                                         011��TDS
                                                         100��CDMA
                                                         101��CA
                                                         Others��Reserved */
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
 �ṹ˵��  : tx_2g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x204����ֵ:0x2B�����:8
 �Ĵ���˵��: TX 2Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
        unsigned long  dem_const_2g     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����
                                                           0��0(Ĭ��)
                                                           1��2
                                                           2��4
                                                           3��6 */
        unsigned long  uddwa_dith_en_2g : 1;  /* bit[4]  : TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                           0����ʹ��
                                                           1��ʹ�� */
        unsigned long  dem_dwa_en_2g    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                           0��ʹ��CLAģʽ
                                                           1��ʹ��DWAģʽ (Ĭ��) */
        unsigned long  dem_lsb_bp_2g    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                           0��DEM LSB ��(Ĭ��)
                                                           1��DEM LSB bypass */
        unsigned long  dem_msb_bp_2g    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                           0��DEM MSB��(Ĭ��)
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
 �ṹ˵��  : tx_2g_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x205����ֵ:0x00�����:8
 �Ĵ���˵��: TX 2Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0     : 1;  /* bit[0]  : ���� */
        unsigned long  tx_flush_en_2g : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                         0����ʹ��
                                                         1��ʹ�� */
        unsigned long  tx_comp_sel_2g : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                         00���̶�ϵ��1��
                                                         01���̶�ϵ��2��
                                                         10���̶�ϵ��3��
                                                         11������ϵ���� */
        unsigned long  reserved_1     : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_2G_DIG_3_UNION;
#define ABB_TX_2G_DIG_3_tx_flush_en_2g_START  (1)
#define ABB_TX_2G_DIG_3_tx_flush_en_2g_END    (1)
#define ABB_TX_2G_DIG_3_tx_comp_sel_2g_START  (2)
#define ABB_TX_2G_DIG_3_tx_comp_sel_2g_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_TX_C_DIG_1_UNION
 �ṹ˵��  : tx_c_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x206����ֵ:0x82�����:8
 �Ĵ���˵��: TX Cģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_comp_bp_c  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                        0����bypass(Ĭ��)
                                                        1��bypass */
        unsigned long  tx_hb_bp_c    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                        0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2
                                                        1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate(Ĭ��) */
        unsigned long  tx_rate_c     : 3;  /* bit[2-4]: TXͨ��CIC�˲����������ʿ��ƣ�
                                                             2G,     3G,     4G,      TDS,      CDMA,    CA
                                                            (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
                                                        0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(Ĭ��)
                                                        1��2.16MHz,15.36MHz,30.72MHz, */
        unsigned long  tx_mode_dig_c : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                        000��2G(Ĭ��)
                                                        001��3G
                                                        010��4G
                                                        011��TDS
                                                        100��CDMA
                                                        101��CA
                                                        Others��Reserved */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_C_DIG_1_UNION;
#define ABB_TX_C_DIG_1_tx_comp_bp_c_START   (0)
#define ABB_TX_C_DIG_1_tx_comp_bp_c_END     (0)
#define ABB_TX_C_DIG_1_tx_hb_bp_c_START     (1)
#define ABB_TX_C_DIG_1_tx_hb_bp_c_END       (1)
#define ABB_TX_C_DIG_1_tx_rate_c_START      (2)
#define ABB_TX_C_DIG_1_tx_rate_c_END        (4)
#define ABB_TX_C_DIG_1_tx_mode_dig_c_START  (5)
#define ABB_TX_C_DIG_1_tx_mode_dig_c_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_C_DIG_2_UNION
 �ṹ˵��  : tx_c_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x207����ֵ:0x2B�����:8
 �Ĵ���˵��: TX Cģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_q_pd_c       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                          0����CLOCK GATING
                                                          1��CLOCK GATING(Ĭ��)
                                                          (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  tx_i_pd_c       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                          0����CLOCK GATING
                                                          1��CLOCK GATING(Ĭ��)
                                                          (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  dem_const_c     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����
                                                          0��0(Ĭ��)
                                                          1��2
                                                          2��4
                                                          3��6 */
        unsigned long  uddwa_dith_en_c : 1;  /* bit[4]  : TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                          0����ʹ��
                                                          1��ʹ�� */
        unsigned long  dem_dwa_en_c    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                          0��ʹ��CLAģʽ
                                                          1��ʹ��DWAģʽ (Ĭ��) */
        unsigned long  dem_lsb_bp_c    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                          0��DEM LSB ��(Ĭ��)
                                                          1��DEM LSB bypass */
        unsigned long  dem_msb_bp_c    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                          0��DEM MSB��(Ĭ��)
                                                          1��DEM MSB bypass */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_C_DIG_2_UNION;
#define ABB_TX_C_DIG_2_tx_q_pd_c_START        (0)
#define ABB_TX_C_DIG_2_tx_q_pd_c_END          (0)
#define ABB_TX_C_DIG_2_tx_i_pd_c_START        (1)
#define ABB_TX_C_DIG_2_tx_i_pd_c_END          (1)
#define ABB_TX_C_DIG_2_dem_const_c_START      (2)
#define ABB_TX_C_DIG_2_dem_const_c_END        (3)
#define ABB_TX_C_DIG_2_uddwa_dith_en_c_START  (4)
#define ABB_TX_C_DIG_2_uddwa_dith_en_c_END    (4)
#define ABB_TX_C_DIG_2_dem_dwa_en_c_START     (5)
#define ABB_TX_C_DIG_2_dem_dwa_en_c_END       (5)
#define ABB_TX_C_DIG_2_dem_lsb_bp_c_START     (6)
#define ABB_TX_C_DIG_2_dem_lsb_bp_c_END       (6)
#define ABB_TX_C_DIG_2_dem_msb_bp_c_START     (7)
#define ABB_TX_C_DIG_2_dem_msb_bp_c_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_C_DIG_3_UNION
 �ṹ˵��  : tx_c_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x208����ֵ:0x08�����:8
 �Ĵ���˵��: TX Cģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0    : 1;  /* bit[0]  : ���� */
        unsigned long  tx_flush_en_c : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                        0����ʹ��
                                                        1��ʹ�� */
        unsigned long  tx_comp_sel_c : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                        00���̶�ϵ��1��
                                                        01���̶�ϵ��2��
                                                        10���̶�ϵ��3��
                                                        11������ϵ���� */
        unsigned long  reserved_1    : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_TX_C_DIG_3_UNION;
#define ABB_TX_C_DIG_3_tx_flush_en_c_START  (1)
#define ABB_TX_C_DIG_3_tx_flush_en_c_END    (1)
#define ABB_TX_C_DIG_3_tx_comp_sel_c_START  (2)
#define ABB_TX_C_DIG_3_tx_comp_sel_c_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_TX_TDS_DIG_1_UNION
 �ṹ˵��  : tx_tds_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x209����ֵ:0x60�����:8
 �Ĵ���˵��: TX TDSģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_comp_bp_tds  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                          0����bypass(Ĭ��)
                                                          1��bypass */
        unsigned long  tx_hb_bp_tds    : 1;  /* bit[1]  : TXͨ������˲�����bypass�ź�
                                                          0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                          1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  tx_rate_tds     : 3;  /* bit[2-4]: TXͨ��CIC�˲����������ʿ��ƣ�
                                                               2G,     3G,     4G,      TDS,      CDMA,    CA
                                                              (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
                                                          0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(Ĭ��)
                                                          1��2.16MHz,15.36MHz,30.72MHz, */
        unsigned long  tx_mode_dig_tds : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                          000��2G(Ĭ��)
                                                          001��3G
                                                          010��4G
                                                          011��TDS
                                                          100��CDMA
                                                          101��CA
                                                          Others��Reserved */
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
 �ṹ˵��  : tx_tds_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x20A����ֵ:0x2B�����:8
 �Ĵ���˵��: TX TDSģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_q_pd_tds       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                            0����CLOCK GATING
                                                            1��CLOCK GATING(Ĭ��)
                                                            (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  tx_i_pd_tds       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                            0����CLOCK GATING
                                                            1��CLOCK GATING(Ĭ��)
                                                            (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  dem_const_tds     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����
                                                            0��0(Ĭ��)
                                                            1��2
                                                            2��4
                                                            3��6 */
        unsigned long  uddwa_dith_en_tds : 1;  /* bit[4]  : TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                            0����ʹ��
                                                            1��ʹ�� */
        unsigned long  dem_dwa_en_tds    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                            0��ʹ��CLAģʽ
                                                            1��ʹ��DWAģʽ(Ĭ��)  */
        unsigned long  dem_lsb_bp_tds    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                            0��DEM LSB ��(Ĭ��)
                                                            1��DEM LSB bypass */
        unsigned long  dem_msb_bp_tds    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
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
#define ABB_TX_TDS_DIG_2_dem_const_tds_END        (3)
#define ABB_TX_TDS_DIG_2_uddwa_dith_en_tds_START  (4)
#define ABB_TX_TDS_DIG_2_uddwa_dith_en_tds_END    (4)
#define ABB_TX_TDS_DIG_2_dem_dwa_en_tds_START     (5)
#define ABB_TX_TDS_DIG_2_dem_dwa_en_tds_END       (5)
#define ABB_TX_TDS_DIG_2_dem_lsb_bp_tds_START     (6)
#define ABB_TX_TDS_DIG_2_dem_lsb_bp_tds_END       (6)
#define ABB_TX_TDS_DIG_2_dem_msb_bp_tds_START     (7)
#define ABB_TX_TDS_DIG_2_dem_msb_bp_tds_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_TDS_DIG_3_UNION
 �ṹ˵��  : tx_tds_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x20B����ֵ:0x00�����:8
 �Ĵ���˵��: TX TDSģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0      : 1;  /* bit[0]  : ���� */
        unsigned long  tx_flush_en_tds : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                          0����ʹ��
                                                          1��ʹ�� */
        unsigned long  tx_comp_sel_tds : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                          00���̶�ϵ��1��
                                                          01���̶�ϵ��2��
                                                          10���̶�ϵ��3��
                                                          11������ϵ���� */
        unsigned long  reserved_1      : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_TX_TDS_DIG_3_UNION;
#define ABB_TX_TDS_DIG_3_tx_flush_en_tds_START  (1)
#define ABB_TX_TDS_DIG_3_tx_flush_en_tds_END    (1)
#define ABB_TX_TDS_DIG_3_tx_comp_sel_tds_START  (2)
#define ABB_TX_TDS_DIG_3_tx_comp_sel_tds_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TX_3G_DIG_1_UNION
 �ṹ˵��  : ch0_tx_3g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x210����ֵ:0x20�����:8
 �Ĵ���˵��: TX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_comp_bp_3g  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                             0����bypass(Ĭ��)
                                                             1��bypass */
        unsigned long  ch0_tx_hb_bp_3g    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  ch0_tx_rate_3g     : 3;  /* bit[2-4]: TXͨ��CIC�˲����������ʿ��ƣ�
                                                                  2G,     3G,     4G,      TDS,      CDMA,    CA
                                                                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
                                                             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(Ĭ��)
                                                             1��2.16MHz,15.36MHz,30.72MHz, */
        unsigned long  ch0_tx_mode_dig_3g : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                             000��2G(Ĭ��)
                                                             001��3G
                                                             010��4G
                                                             011��TDS
                                                             100��CDMA
                                                             101��CA
                                                             Others��Reserved */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_3G_DIG_1_UNION;
#define ABB_CH0_TX_3G_DIG_1_ch0_tx_comp_bp_3g_START   (0)
#define ABB_CH0_TX_3G_DIG_1_ch0_tx_comp_bp_3g_END     (0)
#define ABB_CH0_TX_3G_DIG_1_ch0_tx_hb_bp_3g_START     (1)
#define ABB_CH0_TX_3G_DIG_1_ch0_tx_hb_bp_3g_END       (1)
#define ABB_CH0_TX_3G_DIG_1_ch0_tx_rate_3g_START      (2)
#define ABB_CH0_TX_3G_DIG_1_ch0_tx_rate_3g_END        (4)
#define ABB_CH0_TX_3G_DIG_1_ch0_tx_mode_dig_3g_START  (5)
#define ABB_CH0_TX_3G_DIG_1_ch0_tx_mode_dig_3g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TX_3G_DIG_2_UNION
 �ṹ˵��  : ch0_tx_3g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x211����ֵ:0x2B�����:8
 �Ĵ���˵��: TX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_q_pd_3g       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                               0����CLOCK GATING
                                                               1��CLOCK GATING(Ĭ��)
                                                               (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  ch0_tx_i_pd_3g       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                               0����CLOCK GATING
                                                               1��CLOCK GATING(Ĭ��)
                                                               (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  ch0_dem_const_3g     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����
                                                               0��0(Ĭ��)
                                                               1��2
                                                               2��4
                                                               3��6 */
        unsigned long  ch0_uddwa_dith_en_3g : 1;  /* bit[4]  : TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                               0����ʹ��
                                                               1��ʹ�� */
        unsigned long  ch0_dem_dwa_en_3g    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                               0��ʹ��CLAģʽ
                                                               1��ʹ��DWAģʽ(Ĭ��)  */
        unsigned long  ch0_dem_lsb_bp_3g    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                               0��DEM LSB ��(Ĭ��)
                                                               1��DEM LSB bypass */
        unsigned long  ch0_dem_msb_bp_3g    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                               0��DEM MSB��(Ĭ��)
                                                               1��DEM MSB bypass */
        unsigned long  reserved_butt        : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_3G_DIG_2_UNION;
#define ABB_CH0_TX_3G_DIG_2_ch0_tx_q_pd_3g_START        (0)
#define ABB_CH0_TX_3G_DIG_2_ch0_tx_q_pd_3g_END          (0)
#define ABB_CH0_TX_3G_DIG_2_ch0_tx_i_pd_3g_START        (1)
#define ABB_CH0_TX_3G_DIG_2_ch0_tx_i_pd_3g_END          (1)
#define ABB_CH0_TX_3G_DIG_2_ch0_dem_const_3g_START      (2)
#define ABB_CH0_TX_3G_DIG_2_ch0_dem_const_3g_END        (3)
#define ABB_CH0_TX_3G_DIG_2_ch0_uddwa_dith_en_3g_START  (4)
#define ABB_CH0_TX_3G_DIG_2_ch0_uddwa_dith_en_3g_END    (4)
#define ABB_CH0_TX_3G_DIG_2_ch0_dem_dwa_en_3g_START     (5)
#define ABB_CH0_TX_3G_DIG_2_ch0_dem_dwa_en_3g_END       (5)
#define ABB_CH0_TX_3G_DIG_2_ch0_dem_lsb_bp_3g_START     (6)
#define ABB_CH0_TX_3G_DIG_2_ch0_dem_lsb_bp_3g_END       (6)
#define ABB_CH0_TX_3G_DIG_2_ch0_dem_msb_bp_3g_START     (7)
#define ABB_CH0_TX_3G_DIG_2_ch0_dem_msb_bp_3g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TX_3G_DIG_3_UNION
 �ṹ˵��  : ch0_tx_3g_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x212����ֵ:0x00�����:8
 �Ĵ���˵��: TX 3Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0         : 1;  /* bit[0]  : ���� */
        unsigned long  ch0_tx_flush_en_3g : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  ch0_tx_comp_sel_3g : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                             00���̶�ϵ��1��
                                                             01���̶�ϵ��2��
                                                             10���̶�ϵ��3��
                                                             11������ϵ���� */
        unsigned long  reserved_1         : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_3G_DIG_3_UNION;
#define ABB_CH0_TX_3G_DIG_3_ch0_tx_flush_en_3g_START  (1)
#define ABB_CH0_TX_3G_DIG_3_ch0_tx_flush_en_3g_END    (1)
#define ABB_CH0_TX_3G_DIG_3_ch0_tx_comp_sel_3g_START  (2)
#define ABB_CH0_TX_3G_DIG_3_ch0_tx_comp_sel_3g_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TX_3G_DIG_1_UNION
 �ṹ˵��  : ch1_tx_3g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x213����ֵ:0x20�����:8
 �Ĵ���˵��: TX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_comp_bp_3g  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                             0����bypass(Ĭ��)
                                                             1��bypass */
        unsigned long  ch1_tx_hb_bp_3g    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  ch1_tx_rate_3g     : 3;  /* bit[2-4]: TXͨ��CIC�˲����������ʿ��ƣ�
                                                                  2G,     3G,     4G,      TDS,      CDMA,    CA
                                                                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
                                                             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(Ĭ��)
                                                             1��2.16MHz,15.36MHz,30.72MHz, */
        unsigned long  ch1_tx_mode_dig_3g : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                             000��2G(Ĭ��)
                                                             001��3G
                                                             010��4G
                                                             011��TDS
                                                             100��CDMA
                                                             101��CA
                                                             Others��Reserved */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_3G_DIG_1_UNION;
#define ABB_CH1_TX_3G_DIG_1_ch1_tx_comp_bp_3g_START   (0)
#define ABB_CH1_TX_3G_DIG_1_ch1_tx_comp_bp_3g_END     (0)
#define ABB_CH1_TX_3G_DIG_1_ch1_tx_hb_bp_3g_START     (1)
#define ABB_CH1_TX_3G_DIG_1_ch1_tx_hb_bp_3g_END       (1)
#define ABB_CH1_TX_3G_DIG_1_ch1_tx_rate_3g_START      (2)
#define ABB_CH1_TX_3G_DIG_1_ch1_tx_rate_3g_END        (4)
#define ABB_CH1_TX_3G_DIG_1_ch1_tx_mode_dig_3g_START  (5)
#define ABB_CH1_TX_3G_DIG_1_ch1_tx_mode_dig_3g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TX_3G_DIG_2_UNION
 �ṹ˵��  : ch1_tx_3g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x214����ֵ:0x2B�����:8
 �Ĵ���˵��: TX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_q_pd_3g       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                               0����CLOCK GATING
                                                               1��CLOCK GATING(Ĭ��)
                                                               (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  ch1_tx_i_pd_3g       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                               0����CLOCK GATING
                                                               1��CLOCK GATING(Ĭ��)
                                                               (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  ch1_dem_const_3g     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����
                                                               0��0(Ĭ��)
                                                               1��2
                                                               2��4
                                                               3��6 */
        unsigned long  ch1_uddwa_dith_en_3g : 1;  /* bit[4]  : TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                               0����ʹ��
                                                               1��ʹ�� */
        unsigned long  ch1_dem_dwa_en_3g    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                               0��ʹ��CLAģʽ
                                                               1��ʹ��DWAģʽ(Ĭ��)  */
        unsigned long  ch1_dem_lsb_bp_3g    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                               0��DEM LSB ��(Ĭ��)
                                                               1��DEM LSB bypass */
        unsigned long  ch1_dem_msb_bp_3g    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                               0��DEM MSB��(Ĭ��)
                                                               1��DEM MSB bypass */
        unsigned long  reserved_butt        : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_3G_DIG_2_UNION;
#define ABB_CH1_TX_3G_DIG_2_ch1_tx_q_pd_3g_START        (0)
#define ABB_CH1_TX_3G_DIG_2_ch1_tx_q_pd_3g_END          (0)
#define ABB_CH1_TX_3G_DIG_2_ch1_tx_i_pd_3g_START        (1)
#define ABB_CH1_TX_3G_DIG_2_ch1_tx_i_pd_3g_END          (1)
#define ABB_CH1_TX_3G_DIG_2_ch1_dem_const_3g_START      (2)
#define ABB_CH1_TX_3G_DIG_2_ch1_dem_const_3g_END        (3)
#define ABB_CH1_TX_3G_DIG_2_ch1_uddwa_dith_en_3g_START  (4)
#define ABB_CH1_TX_3G_DIG_2_ch1_uddwa_dith_en_3g_END    (4)
#define ABB_CH1_TX_3G_DIG_2_ch1_dem_dwa_en_3g_START     (5)
#define ABB_CH1_TX_3G_DIG_2_ch1_dem_dwa_en_3g_END       (5)
#define ABB_CH1_TX_3G_DIG_2_ch1_dem_lsb_bp_3g_START     (6)
#define ABB_CH1_TX_3G_DIG_2_ch1_dem_lsb_bp_3g_END       (6)
#define ABB_CH1_TX_3G_DIG_2_ch1_dem_msb_bp_3g_START     (7)
#define ABB_CH1_TX_3G_DIG_2_ch1_dem_msb_bp_3g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TX_3G_DIG_3_UNION
 �ṹ˵��  : ch1_tx_3g_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x215����ֵ:0x00�����:8
 �Ĵ���˵��: TX 3Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0         : 1;  /* bit[0]  : ���� */
        unsigned long  ch1_tx_flush_en_3g : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  ch1_tx_comp_sel_3g : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                             00���̶�ϵ��1��
                                                             01���̶�ϵ��2��
                                                             10���̶�ϵ��3��
                                                             11������ϵ���� */
        unsigned long  reserved_1         : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_3G_DIG_3_UNION;
#define ABB_CH1_TX_3G_DIG_3_ch1_tx_flush_en_3g_START  (1)
#define ABB_CH1_TX_3G_DIG_3_ch1_tx_flush_en_3g_END    (1)
#define ABB_CH1_TX_3G_DIG_3_ch1_tx_comp_sel_3g_START  (2)
#define ABB_CH1_TX_3G_DIG_3_ch1_tx_comp_sel_3g_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TX_4G_DIG_1_UNION
 �ṹ˵��  : ch0_tx_4g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x228����ֵ:0x40�����:8
 �Ĵ���˵��: TX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_comp_bp_4g  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                             0����bypass(Ĭ��)
                                                             1��bypass */
        unsigned long  ch0_tx_hb_bp_4g    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  ch0_tx_rate_4g     : 3;  /* bit[2-4]: TXͨ��CIC�˲����������ʿ��ƣ�
                                                                  2G,     3G,     4G,      TDS,      CDMA,    CA
                                                                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
                                                             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(Ĭ��)
                                                             1��2.16MHz,15.36MHz,30.72MHz, */
        unsigned long  ch0_tx_mode_dig_4g : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                             000��2G(Ĭ��)
                                                             001��3G
                                                             010��4G
                                                             011��TDS
                                                             100��CDMA
                                                             101��CA
                                                             Others��Reserved */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_4G_DIG_1_UNION;
#define ABB_CH0_TX_4G_DIG_1_ch0_tx_comp_bp_4g_START   (0)
#define ABB_CH0_TX_4G_DIG_1_ch0_tx_comp_bp_4g_END     (0)
#define ABB_CH0_TX_4G_DIG_1_ch0_tx_hb_bp_4g_START     (1)
#define ABB_CH0_TX_4G_DIG_1_ch0_tx_hb_bp_4g_END       (1)
#define ABB_CH0_TX_4G_DIG_1_ch0_tx_rate_4g_START      (2)
#define ABB_CH0_TX_4G_DIG_1_ch0_tx_rate_4g_END        (4)
#define ABB_CH0_TX_4G_DIG_1_ch0_tx_mode_dig_4g_START  (5)
#define ABB_CH0_TX_4G_DIG_1_ch0_tx_mode_dig_4g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TX_4G_DIG_2_UNION
 �ṹ˵��  : ch0_tx_4g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x229����ֵ:0x2B�����:8
 �Ĵ���˵��: TX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_q_pd_4g       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                               0����CLOCK GATING
                                                               1��CLOCK GATING(Ĭ��)
                                                               (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  ch0_tx_i_pd_4g       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                               0����CLOCK GATING
                                                               1��CLOCK GATING(Ĭ��)
                                                               (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  ch0_dem_const_4g     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����
                                                               0��0(Ĭ��)
                                                               1��2
                                                               2��4
                                                               3��6 */
        unsigned long  ch0_uddwa_dith_en_4g : 1;  /* bit[4]  : TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                               0����ʹ��
                                                               1��ʹ�� */
        unsigned long  ch0_dem_dwa_en_4g    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                               0��ʹ��CLAģʽ
                                                               1��ʹ��DWAģʽ(Ĭ��)  */
        unsigned long  ch0_dem_lsb_bp_4g    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                               0��DEM LSB ��(Ĭ��)
                                                               1��DEM LSB bypass */
        unsigned long  ch0_dem_msb_bp_4g    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                               0��DEM MSB��(Ĭ��)
                                                               1��DEM MSB bypass */
        unsigned long  reserved_butt        : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_4G_DIG_2_UNION;
#define ABB_CH0_TX_4G_DIG_2_ch0_tx_q_pd_4g_START        (0)
#define ABB_CH0_TX_4G_DIG_2_ch0_tx_q_pd_4g_END          (0)
#define ABB_CH0_TX_4G_DIG_2_ch0_tx_i_pd_4g_START        (1)
#define ABB_CH0_TX_4G_DIG_2_ch0_tx_i_pd_4g_END          (1)
#define ABB_CH0_TX_4G_DIG_2_ch0_dem_const_4g_START      (2)
#define ABB_CH0_TX_4G_DIG_2_ch0_dem_const_4g_END        (3)
#define ABB_CH0_TX_4G_DIG_2_ch0_uddwa_dith_en_4g_START  (4)
#define ABB_CH0_TX_4G_DIG_2_ch0_uddwa_dith_en_4g_END    (4)
#define ABB_CH0_TX_4G_DIG_2_ch0_dem_dwa_en_4g_START     (5)
#define ABB_CH0_TX_4G_DIG_2_ch0_dem_dwa_en_4g_END       (5)
#define ABB_CH0_TX_4G_DIG_2_ch0_dem_lsb_bp_4g_START     (6)
#define ABB_CH0_TX_4G_DIG_2_ch0_dem_lsb_bp_4g_END       (6)
#define ABB_CH0_TX_4G_DIG_2_ch0_dem_msb_bp_4g_START     (7)
#define ABB_CH0_TX_4G_DIG_2_ch0_dem_msb_bp_4g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TX_4G_DIG_3_UNION
 �ṹ˵��  : ch0_tx_4g_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x22A����ֵ:0x00�����:8
 �Ĵ���˵��: TX 4Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0         : 1;  /* bit[0]  : ���� */
        unsigned long  ch0_tx_flush_en_4g : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  ch0_tx_comp_sel_4g : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                             00���̶�ϵ��1��
                                                             01���̶�ϵ��2��
                                                             10���̶�ϵ��3��
                                                             11������ϵ���� */
        unsigned long  reserved_1         : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_4G_DIG_3_UNION;
#define ABB_CH0_TX_4G_DIG_3_ch0_tx_flush_en_4g_START  (1)
#define ABB_CH0_TX_4G_DIG_3_ch0_tx_flush_en_4g_END    (1)
#define ABB_CH0_TX_4G_DIG_3_ch0_tx_comp_sel_4g_START  (2)
#define ABB_CH0_TX_4G_DIG_3_ch0_tx_comp_sel_4g_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TX_4G_DIG_1_UNION
 �ṹ˵��  : ch1_tx_4g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x22B����ֵ:0x40�����:8
 �Ĵ���˵��: TX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_comp_bp_4g  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                             0����bypass(Ĭ��)
                                                             1��bypass */
        unsigned long  ch1_tx_hb_bp_4g    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  ch1_tx_rate_4g     : 3;  /* bit[2-4]: TXͨ��CIC�˲����������ʿ��ƣ�
                                                                  2G,     3G,     4G,      TDS,      CDMA,    CA
                                                                 (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
                                                             0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(Ĭ��)
                                                             1��2.16MHz,15.36MHz,30.72MHz, */
        unsigned long  ch1_tx_mode_dig_4g : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                             000��2G(Ĭ��)
                                                             001��3G
                                                             010��4G
                                                             011��TDS
                                                             100��CDMA
                                                             101��CA
                                                             Others��Reserved */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_4G_DIG_1_UNION;
#define ABB_CH1_TX_4G_DIG_1_ch1_tx_comp_bp_4g_START   (0)
#define ABB_CH1_TX_4G_DIG_1_ch1_tx_comp_bp_4g_END     (0)
#define ABB_CH1_TX_4G_DIG_1_ch1_tx_hb_bp_4g_START     (1)
#define ABB_CH1_TX_4G_DIG_1_ch1_tx_hb_bp_4g_END       (1)
#define ABB_CH1_TX_4G_DIG_1_ch1_tx_rate_4g_START      (2)
#define ABB_CH1_TX_4G_DIG_1_ch1_tx_rate_4g_END        (4)
#define ABB_CH1_TX_4G_DIG_1_ch1_tx_mode_dig_4g_START  (5)
#define ABB_CH1_TX_4G_DIG_1_ch1_tx_mode_dig_4g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TX_4G_DIG_2_UNION
 �ṹ˵��  : ch1_tx_4g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x22C����ֵ:0x2B�����:8
 �Ĵ���˵��: TX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_q_pd_4g       : 1;  /* bit[0]  : TXͨ��Q·CLOCK GATING���ƣ�
                                                               0����CLOCK GATING
                                                               1��CLOCK GATING(Ĭ��)
                                                               (!tx_q_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  ch1_tx_i_pd_4g       : 1;  /* bit[1]  : TXͨ��I·CLOCK GATING���ƣ�
                                                               0����CLOCK GATING
                                                               1��CLOCK GATING(Ĭ��)
                                                               (!tx_i_pd)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  ch1_dem_const_4g     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����
                                                               0��0(Ĭ��)
                                                               1��2
                                                               2��4
                                                               3��6 */
        unsigned long  ch1_uddwa_dith_en_4g : 1;  /* bit[4]  : TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                               0����ʹ��
                                                               1��ʹ�� */
        unsigned long  ch1_dem_dwa_en_4g    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                               0��ʹ��CLAģʽ
                                                               1��ʹ��DWAģʽ(Ĭ��)  */
        unsigned long  ch1_dem_lsb_bp_4g    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                               0��DEM LSB ��(Ĭ��)
                                                               1��DEM LSB bypass */
        unsigned long  ch1_dem_msb_bp_4g    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                               0��DEM MSB��(Ĭ��)
                                                               1��DEM MSB bypass */
        unsigned long  reserved_butt        : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_4G_DIG_2_UNION;
#define ABB_CH1_TX_4G_DIG_2_ch1_tx_q_pd_4g_START        (0)
#define ABB_CH1_TX_4G_DIG_2_ch1_tx_q_pd_4g_END          (0)
#define ABB_CH1_TX_4G_DIG_2_ch1_tx_i_pd_4g_START        (1)
#define ABB_CH1_TX_4G_DIG_2_ch1_tx_i_pd_4g_END          (1)
#define ABB_CH1_TX_4G_DIG_2_ch1_dem_const_4g_START      (2)
#define ABB_CH1_TX_4G_DIG_2_ch1_dem_const_4g_END        (3)
#define ABB_CH1_TX_4G_DIG_2_ch1_uddwa_dith_en_4g_START  (4)
#define ABB_CH1_TX_4G_DIG_2_ch1_uddwa_dith_en_4g_END    (4)
#define ABB_CH1_TX_4G_DIG_2_ch1_dem_dwa_en_4g_START     (5)
#define ABB_CH1_TX_4G_DIG_2_ch1_dem_dwa_en_4g_END       (5)
#define ABB_CH1_TX_4G_DIG_2_ch1_dem_lsb_bp_4g_START     (6)
#define ABB_CH1_TX_4G_DIG_2_ch1_dem_lsb_bp_4g_END       (6)
#define ABB_CH1_TX_4G_DIG_2_ch1_dem_msb_bp_4g_START     (7)
#define ABB_CH1_TX_4G_DIG_2_ch1_dem_msb_bp_4g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TX_4G_DIG_3_UNION
 �ṹ˵��  : ch1_tx_4g_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x22D����ֵ:0x00�����:8
 �Ĵ���˵��: TX 4Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0         : 1;  /* bit[0]  : ���� */
        unsigned long  ch1_tx_flush_en_4g : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  ch1_tx_comp_sel_4g : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                             00���̶�ϵ��1��
                                                             01���̶�ϵ��2��
                                                             10���̶�ϵ��3��
                                                             11������ϵ���� */
        unsigned long  reserved_1         : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_4G_DIG_3_UNION;
#define ABB_CH1_TX_4G_DIG_3_ch1_tx_flush_en_4g_START  (1)
#define ABB_CH1_TX_4G_DIG_3_ch1_tx_flush_en_4g_END    (1)
#define ABB_CH1_TX_4G_DIG_3_ch1_tx_comp_sel_4g_START  (2)
#define ABB_CH1_TX_4G_DIG_3_ch1_tx_comp_sel_4g_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TX_TESTMODE_UNION
 �ṹ˵��  : CH0_TX_TESTMODE �Ĵ����ṹ���塣��ַƫ����:0x240����ֵ:0x00�����:8
 �Ĵ���˵��: ����ģʽ�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_sw_rst   : 1;  /* bit[0]  : ���ֲ���TXͨ����λ�źţ�
                                                          0������λ(Ĭ��)
                                                          1����λ */
        unsigned long  reserved_0      : 3;  /* bit[1-3]: ���� */
        unsigned long  ch0_tx_loop_sel : 2;  /* bit[4-5]: TX�㷨���أ�����ͨ��ѡ��
                                                          0������CH0 RX
                                                          1������CH1 RX
                                                          2������CH2 RX
                                                          default������CH0 RX */
        unsigned long  reserved_1      : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_TESTMODE_UNION;
#define ABB_CH0_TX_TESTMODE_ch0_tx_sw_rst_START    (0)
#define ABB_CH0_TX_TESTMODE_ch0_tx_sw_rst_END      (0)
#define ABB_CH0_TX_TESTMODE_ch0_tx_loop_sel_START  (4)
#define ABB_CH0_TX_TESTMODE_ch0_tx_loop_sel_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CH0_SINE_GENERATE_UNION
 �ṹ˵��  : CH0_SINE_GENERATE �Ĵ����ṹ���塣��ַƫ����:0x241����ֵ:0x10�����:8
 �Ĵ���˵��: SINE���ͼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_sine_enable : 1;  /* bit[0]  : ch0���Ҳ�����ʹ��
                                                          0��������
                                                          1������ */
        unsigned long  reserved        : 1;  /* bit[1]  : ���� */
        unsigned long  ch0_sine_amp    : 2;  /* bit[2-3]: ���Ҳ����ͷ��ȿ���
                                                          00��������
                                                          01��3/4����
                                                          10��1/2����
                                                          11��1/4���� */
        unsigned long  ch0_sine_freq   : 4;  /* bit[4-7]: ���Ҳ�����Ƶ�ʿ��ƣ���λ(freq of tx_hb_clk)/32�����䷶ΧΪ1~f */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_SINE_GENERATE_UNION;
#define ABB_CH0_SINE_GENERATE_ch0_sine_enable_START  (0)
#define ABB_CH0_SINE_GENERATE_ch0_sine_enable_END    (0)
#define ABB_CH0_SINE_GENERATE_ch0_sine_amp_START     (2)
#define ABB_CH0_SINE_GENERATE_ch0_sine_amp_END       (3)
#define ABB_CH0_SINE_GENERATE_ch0_sine_freq_START    (4)
#define ABB_CH0_SINE_GENERATE_ch0_sine_freq_END      (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TX_COEF1_UNION
 �ṹ˵��  : ch0_tx_coef1 �Ĵ����ṹ���塣��ַƫ����:0x244����ֵ:0x3B�����:8
 �Ĵ���˵��: TXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_comp_c0 : 6;  /* bit[0-5]: TX�����˲���ϵ��C0,6bit�з����� */
        unsigned long  reserved       : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_COEF1_UNION;
#define ABB_CH0_TX_COEF1_ch0_tx_comp_c0_START  (0)
#define ABB_CH0_TX_COEF1_ch0_tx_comp_c0_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TX_COEF4_UNION
 �ṹ˵��  : ch0_tx_coef4 �Ĵ����ṹ���塣��ַƫ����:0x247����ֵ:0x03�����:8
 �Ĵ���˵��: TXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_comp_c2_msb : 2;  /* bit[0-1]: TX�����˲���ϵ��C2��2λ,10bit�з����� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_COEF4_UNION;
#define ABB_CH0_TX_COEF4_ch0_tx_comp_c2_msb_START  (0)
#define ABB_CH0_TX_COEF4_ch0_tx_comp_c2_msb_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TX_COEF6_UNION
 �ṹ˵��  : ch0_tx_coef6 �Ĵ����ṹ���塣��ַƫ����:0x249����ֵ:0x02�����:8
 �Ĵ���˵��: TXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_comp_c3_msb : 2;  /* bit[0-1]: TX�����˲���ϵ��C3��2λ,10bit�޷����� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_COEF6_UNION;
#define ABB_CH0_TX_COEF6_ch0_tx_comp_c3_msb_START  (0)
#define ABB_CH0_TX_COEF6_ch0_tx_comp_c3_msb_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TX_REG_DEBUG_DIG0_UNION
 �ṹ˵��  : ch0_tx_reg_debug_dig0 �Ĵ����ṹ���塣��ַƫ����:0x24C����ֵ:0x64�����:8
 �Ĵ���˵��: ���ֵ��ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_sdm_rst_ctrl  : 1;  /* bit[0]  : TXͨ��SDMģ���쳣ʱ��λ����
                                                            0��ֻ��λSDMģ��
                                                            1����λ����TXͨ�� */
        unsigned long  ch0_dem_mode      : 1;  /* bit[1]  : TXͨ��DEMУ׼����ģʽ
                                                            0����������
                                                            1��У׼̬��DEM���Ϊdem_code_man */
        unsigned long  ch0_tx_dem_sat    : 2;  /* bit[2-3]: TX DEM�����������޷���λ��
                                                            00��0.8125
                                                            01��0.796875(Ĭ��)
                                                            10��0.765625
                                                            11��0.75 */
        unsigned long  ch0_dither_en     : 1;  /* bit[4]  : TXͨ��SDM Dither���ƣ�
                                                            0����ʹ��
                                                            1��ʹ�� */
        unsigned long  reserved_0        : 1;  /* bit[5]  : ���� */
        unsigned long  ch0_tx_main_sd_bp : 1;  /* bit[6]  : TX SDģ������������·ʹ�ܣ�
                                                            0��������������·��
                                                            1������������·��Ĭ�ϣ��� */
        unsigned long  reserved_1        : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_REG_DEBUG_DIG0_UNION;
#define ABB_CH0_TX_REG_DEBUG_DIG0_ch0_sdm_rst_ctrl_START   (0)
#define ABB_CH0_TX_REG_DEBUG_DIG0_ch0_sdm_rst_ctrl_END     (0)
#define ABB_CH0_TX_REG_DEBUG_DIG0_ch0_dem_mode_START       (1)
#define ABB_CH0_TX_REG_DEBUG_DIG0_ch0_dem_mode_END         (1)
#define ABB_CH0_TX_REG_DEBUG_DIG0_ch0_tx_dem_sat_START     (2)
#define ABB_CH0_TX_REG_DEBUG_DIG0_ch0_tx_dem_sat_END       (3)
#define ABB_CH0_TX_REG_DEBUG_DIG0_ch0_dither_en_START      (4)
#define ABB_CH0_TX_REG_DEBUG_DIG0_ch0_dither_en_END        (4)
#define ABB_CH0_TX_REG_DEBUG_DIG0_ch0_tx_main_sd_bp_START  (6)
#define ABB_CH0_TX_REG_DEBUG_DIG0_ch0_tx_main_sd_bp_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TX_REG_DEBUG_DIG4_UNION
 �ṹ˵��  : ch0_tx_reg_debug_dig4 �Ĵ����ṹ���塣��ַƫ����:0x250����ֵ:0x00�����:8
 �Ĵ���˵��: ���ֵ��ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_div_en_bp      : 1;  /* bit[0]  : TX��Ƶ��ʹ��bypass����
                                                                0����bypass
                                                                1��bypass */
        unsigned long  reserved              : 3;  /* bit[1-3]: ���� */
        unsigned long  ch0_tx_sw_rst_num_cfg : 3;  /* bit[4-6]: ģʽ�л���λ��������ֵ����λΪ8 cycles */
        unsigned long  ch0_tx_sw_rst_num_sel : 1;  /* bit[7]  : bit[7]��ģʽ�л���λ��������ʹ��
                                                                0����ʹ��
                                                                1��ʹ�� */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_REG_DEBUG_DIG4_UNION;
#define ABB_CH0_TX_REG_DEBUG_DIG4_ch0_tx_div_en_bp_START       (0)
#define ABB_CH0_TX_REG_DEBUG_DIG4_ch0_tx_div_en_bp_END         (0)
#define ABB_CH0_TX_REG_DEBUG_DIG4_ch0_tx_sw_rst_num_cfg_START  (4)
#define ABB_CH0_TX_REG_DEBUG_DIG4_ch0_tx_sw_rst_num_cfg_END    (6)
#define ABB_CH0_TX_REG_DEBUG_DIG4_ch0_tx_sw_rst_num_sel_START  (7)
#define ABB_CH0_TX_REG_DEBUG_DIG4_ch0_tx_sw_rst_num_sel_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TX_LINE_SEL_UNION
 �ṹ˵��  : CH0_TX_LINE_SEL �Ĵ����ṹ���塣��ַƫ����:0x251����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�ǿ������ʹ�ܡ�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_en_sel : 1;  /* bit[0]  : TXͨ���߿�ѡ��ǿ��ʹ��
                                                        0��ѡ���߿�ʹ��
                                                        1��ѡ��ǿ��ʹ�� */
        unsigned long  reserved_0    : 3;  /* bit[1-3]: ���� */
        unsigned long  ch0_tx_en_cfg : 1;  /* bit[4]  : TXͨ��ǿ���߿� */
        unsigned long  reserved_1    : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_LINE_SEL_UNION;
#define ABB_CH0_TX_LINE_SEL_ch0_tx_en_sel_START  (0)
#define ABB_CH0_TX_LINE_SEL_ch0_tx_en_sel_END    (0)
#define ABB_CH0_TX_LINE_SEL_ch0_tx_en_cfg_START  (4)
#define ABB_CH0_TX_LINE_SEL_ch0_tx_en_cfg_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TX_LINE_CFG_UNION
 �ṹ˵��  : ch0_tx_line_cfg �Ĵ����ṹ���塣��ַƫ����:0x252����ֵ:0x00�����:8
 �Ĵ���˵��: ģʽ�߿�ǿ�����á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_line_ctrl_mode_cfg : 3;  /* bit[0-2]: �߿��ź�CH0_TX_LINE_CTRL_MODEǿ������ֵ
                                                                    0��IDLE
                                                                    1��Gģ
                                                                    2��Wģ
                                                                    3��LTEģ
                                                                    4��TDSģ
                                                                    5��Xģʽ */
        unsigned long  ch0_tx_line_ctrl_mode_sel : 1;  /* bit[3]  : �߿��ź�CH0_TX_LINE_CTRL_MODEǿ������ʹ�� */
        unsigned long  reserved                  : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_LINE_CFG_UNION;
#define ABB_CH0_TX_LINE_CFG_ch0_tx_line_ctrl_mode_cfg_START  (0)
#define ABB_CH0_TX_LINE_CFG_ch0_tx_line_ctrl_mode_cfg_END    (2)
#define ABB_CH0_TX_LINE_CFG_ch0_tx_line_ctrl_mode_sel_START  (3)
#define ABB_CH0_TX_LINE_CFG_ch0_tx_line_ctrl_mode_sel_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TX_LINE_RPT0_UNION
 �ṹ˵��  : ch0_tx_line_rpt0 �Ĵ����ṹ���塣��ַƫ����:0x253����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0    : 2;  /* bit[0-1]: ���� */
        unsigned long  ch0_tx_en_rpt : 1;  /* bit[2]  : CH0_TX_EN�߿�״̬�ϱ� */
        unsigned long  reserved_1    : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_LINE_RPT0_UNION;
#define ABB_CH0_TX_LINE_RPT0_ch0_tx_en_rpt_START  (2)
#define ABB_CH0_TX_LINE_RPT0_ch0_tx_en_rpt_END    (2)


/*****************************************************************************
 �ṹ��    : ABB_CH0_TX_LINE_RPT1_UNION
 �ṹ˵��  : ch0_tx_line_rpt1 �Ĵ����ṹ���塣��ַƫ����:0x254����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_tx_line_ctrl_mode_rpt : 3;  /* bit[0-2]: CH0 TX_LINE_CTRL_MODE״̬�ϱ�
                                                                    0��IDLE
                                                                    1��Gģ
                                                                    2��Wģ
                                                                    3��LTEģ
                                                                    4��TDSģ
                                                                    5��Xģ
                                                                    others��IDLE */
        unsigned long  reserved                  : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_LINE_RPT1_UNION;
#define ABB_CH0_TX_LINE_RPT1_ch0_tx_line_ctrl_mode_rpt_START  (0)
#define ABB_CH0_TX_LINE_RPT1_ch0_tx_line_ctrl_mode_rpt_END    (2)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TX_TESTMODE_UNION
 �ṹ˵��  : CH1_TX_TESTMODE �Ĵ����ṹ���塣��ַƫ����:0x260����ֵ:0x10�����:8
 �Ĵ���˵��: ����ģʽ�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_sw_rst   : 1;  /* bit[0]  : ���ֲ���TXͨ����λ�źţ�
                                                          0������λ(Ĭ��)
                                                          1����λ */
        unsigned long  reserved_0      : 3;  /* bit[1-3]: ���� */
        unsigned long  ch1_tx_loop_sel : 2;  /* bit[4-5]: TX�㷨���أ�����ͨ��ѡ��
                                                          0������CH0 RX
                                                          1������CH1 RX
                                                          2������CH2 RX
                                                          default������CH0 RX */
        unsigned long  reserved_1      : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_TESTMODE_UNION;
#define ABB_CH1_TX_TESTMODE_ch1_tx_sw_rst_START    (0)
#define ABB_CH1_TX_TESTMODE_ch1_tx_sw_rst_END      (0)
#define ABB_CH1_TX_TESTMODE_ch1_tx_loop_sel_START  (4)
#define ABB_CH1_TX_TESTMODE_ch1_tx_loop_sel_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CH1_SINE_GENERATE_UNION
 �ṹ˵��  : CH1_SINE_GENERATE �Ĵ����ṹ���塣��ַƫ����:0x261����ֵ:0x10�����:8
 �Ĵ���˵��: SINE���ͼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_sine_enable : 1;  /* bit[0]  : ch0���Ҳ�����ʹ��
                                                          0��������
                                                          1������ */
        unsigned long  reserved        : 1;  /* bit[1]  : ���� */
        unsigned long  ch1_sine_amp    : 2;  /* bit[2-3]: ���Ҳ����ͷ��ȿ���
                                                          00��������
                                                          01��3/4����
                                                          10��1/2����
                                                          11��1/4���� */
        unsigned long  ch1_sine_freq   : 4;  /* bit[4-7]: ���Ҳ�����Ƶ�ʿ��ƣ���λ(freq of tx_hb_clk)/32�����䷶ΧΪ1~f */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_SINE_GENERATE_UNION;
#define ABB_CH1_SINE_GENERATE_ch1_sine_enable_START  (0)
#define ABB_CH1_SINE_GENERATE_ch1_sine_enable_END    (0)
#define ABB_CH1_SINE_GENERATE_ch1_sine_amp_START     (2)
#define ABB_CH1_SINE_GENERATE_ch1_sine_amp_END       (3)
#define ABB_CH1_SINE_GENERATE_ch1_sine_freq_START    (4)
#define ABB_CH1_SINE_GENERATE_ch1_sine_freq_END      (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TX_COEF1_UNION
 �ṹ˵��  : ch1_tx_coef1 �Ĵ����ṹ���塣��ַƫ����:0x264����ֵ:0x3B�����:8
 �Ĵ���˵��: TXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_comp_c0 : 6;  /* bit[0-5]: TX�����˲���ϵ��C0,6bit�з����� */
        unsigned long  reserved       : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_COEF1_UNION;
#define ABB_CH1_TX_COEF1_ch1_tx_comp_c0_START  (0)
#define ABB_CH1_TX_COEF1_ch1_tx_comp_c0_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TX_COEF4_UNION
 �ṹ˵��  : ch1_tx_coef4 �Ĵ����ṹ���塣��ַƫ����:0x267����ֵ:0x03�����:8
 �Ĵ���˵��: TXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_comp_c2_msb : 2;  /* bit[0-1]: TX�����˲���ϵ��C2��2λ,10bit�з����� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_COEF4_UNION;
#define ABB_CH1_TX_COEF4_ch1_tx_comp_c2_msb_START  (0)
#define ABB_CH1_TX_COEF4_ch1_tx_comp_c2_msb_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TX_COEF6_UNION
 �ṹ˵��  : ch1_tx_coef6 �Ĵ����ṹ���塣��ַƫ����:0x269����ֵ:0x02�����:8
 �Ĵ���˵��: TXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_comp_c3_msb : 2;  /* bit[0-1]: TX�����˲���ϵ��C3��2λ,10bit�޷����� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_COEF6_UNION;
#define ABB_CH1_TX_COEF6_ch1_tx_comp_c3_msb_START  (0)
#define ABB_CH1_TX_COEF6_ch1_tx_comp_c3_msb_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TX_REG_DEBUG_DIG0_UNION
 �ṹ˵��  : CH1_TX_REG_DEBUG_DIG0 �Ĵ����ṹ���塣��ַƫ����:0x26C����ֵ:0x44�����:8
 �Ĵ���˵��: ���ֵ��ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_sdm_rst_ctrl  : 1;  /* bit[0]  : TXͨ��SDMģ���쳣ʱ��λ����
                                                            0��ֻ��λSDMģ��
                                                            1����λ����TXͨ�� */
        unsigned long  ch1_dem_mode      : 1;  /* bit[1]  : TXͨ��DEMУ׼����ģʽ
                                                            0����������
                                                            1��У׼̬��DEM���Ϊdem_code_man */
        unsigned long  ch1_tx_dem_sat    : 2;  /* bit[2-3]: TX DEM�����������޷���λ��
                                                            00��0.8125
                                                            01��0.796875(Ĭ��)
                                                            10��0.765625
                                                            11��0.75 */
        unsigned long  ch1_dither_en     : 1;  /* bit[4]  : TXͨ��SDM Dither���ƣ�
                                                            0����ʹ��
                                                            1��ʹ�� */
        unsigned long  reserved_0        : 1;  /* bit[5]  : ���� */
        unsigned long  ch1_tx_main_sd_bp : 1;  /* bit[6]  : TX SDģ������������·ʹ�ܣ�
                                                            0��������������·��
                                                            1������������·��Ĭ�ϣ��� */
        unsigned long  reserved_1        : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_REG_DEBUG_DIG0_UNION;
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_sdm_rst_ctrl_START   (0)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_sdm_rst_ctrl_END     (0)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_dem_mode_START       (1)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_dem_mode_END         (1)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_tx_dem_sat_START     (2)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_tx_dem_sat_END       (3)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_dither_en_START      (4)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_dither_en_END        (4)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_tx_main_sd_bp_START  (6)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_tx_main_sd_bp_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TX_REG_DEBUG_DIG4_UNION
 �ṹ˵��  : ch1_tx_reg_debug_dig4 �Ĵ����ṹ���塣��ַƫ����:0x270����ֵ:0x00�����:8
 �Ĵ���˵��: ���ֵ��ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_div_en_bp      : 1;  /* bit[0]  : TX��Ƶ��ʹ��bypass����
                                                                0����bypass
                                                                1��bypass */
        unsigned long  reserved              : 3;  /* bit[1-3]: ���� */
        unsigned long  ch1_tx_sw_rst_num_cfg : 3;  /* bit[4-6]: ģʽ�л���λ��������ֵ����λΪ8 cycles */
        unsigned long  ch1_tx_sw_rst_num_sel : 1;  /* bit[7]  : bit[7]��ģʽ�л���λ��������ʹ��
                                                                0����ʹ��
                                                                1��ʹ�� */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_REG_DEBUG_DIG4_UNION;
#define ABB_CH1_TX_REG_DEBUG_DIG4_ch1_tx_div_en_bp_START       (0)
#define ABB_CH1_TX_REG_DEBUG_DIG4_ch1_tx_div_en_bp_END         (0)
#define ABB_CH1_TX_REG_DEBUG_DIG4_ch1_tx_sw_rst_num_cfg_START  (4)
#define ABB_CH1_TX_REG_DEBUG_DIG4_ch1_tx_sw_rst_num_cfg_END    (6)
#define ABB_CH1_TX_REG_DEBUG_DIG4_ch1_tx_sw_rst_num_sel_START  (7)
#define ABB_CH1_TX_REG_DEBUG_DIG4_ch1_tx_sw_rst_num_sel_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TX_LINE_SEL_UNION
 �ṹ˵��  : CH1_TX_LINE_SEL �Ĵ����ṹ���塣��ַƫ����:0x271����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�ǿ������ʹ�ܡ�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_en_sel : 1;  /* bit[0]  : TXͨ���߿�ѡ��ǿ��ʹ��
                                                        0��ѡ���߿�ʹ��
                                                        1��ѡ��ǿ��ʹ�� */
        unsigned long  reserved_0    : 3;  /* bit[1-3]: ���� */
        unsigned long  ch1_tx_en_cfg : 1;  /* bit[4]  : TXͨ��ǿ���߿� */
        unsigned long  reserved_1    : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_LINE_SEL_UNION;
#define ABB_CH1_TX_LINE_SEL_ch1_tx_en_sel_START  (0)
#define ABB_CH1_TX_LINE_SEL_ch1_tx_en_sel_END    (0)
#define ABB_CH1_TX_LINE_SEL_ch1_tx_en_cfg_START  (4)
#define ABB_CH1_TX_LINE_SEL_ch1_tx_en_cfg_END    (4)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TX_LINE_CFG_UNION
 �ṹ˵��  : ch1_tx_line_cfg �Ĵ����ṹ���塣��ַƫ����:0x272����ֵ:0x00�����:8
 �Ĵ���˵��: ģʽ�߿�ǿ�����á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_line_ctrl_mode_cfg : 3;  /* bit[0-2]: �߿��ź�CH1_TX_LINE_CTRL_MODEǿ������ֵ
                                                                    0��IDLE
                                                                    1��Gģ
                                                                    2��Wģ
                                                                    3��LTEģ
                                                                    4��TDSģ
                                                                    5��Xģʽ */
        unsigned long  ch1_tx_line_ctrl_mode_sel : 1;  /* bit[3]  : �߿��ź�CH1_LINE_CTRL_MODEǿ������ʹ�� */
        unsigned long  reserved                  : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_LINE_CFG_UNION;
#define ABB_CH1_TX_LINE_CFG_ch1_tx_line_ctrl_mode_cfg_START  (0)
#define ABB_CH1_TX_LINE_CFG_ch1_tx_line_ctrl_mode_cfg_END    (2)
#define ABB_CH1_TX_LINE_CFG_ch1_tx_line_ctrl_mode_sel_START  (3)
#define ABB_CH1_TX_LINE_CFG_ch1_tx_line_ctrl_mode_sel_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TX_LINE_RPT0_UNION
 �ṹ˵��  : ch1_tx_line_rpt0 �Ĵ����ṹ���塣��ַƫ����:0x273����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0    : 2;  /* bit[0-1]: ���� */
        unsigned long  ch1_tx_en_rpt : 1;  /* bit[2]  : CH1_TX_EN�߿�״̬�ϱ� */
        unsigned long  reserved_1    : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_LINE_RPT0_UNION;
#define ABB_CH1_TX_LINE_RPT0_ch1_tx_en_rpt_START  (2)
#define ABB_CH1_TX_LINE_RPT0_ch1_tx_en_rpt_END    (2)


/*****************************************************************************
 �ṹ��    : ABB_CH1_TX_LINE_RPT1_UNION
 �ṹ˵��  : ch1_tx_line_rpt1 �Ĵ����ṹ���塣��ַƫ����:0x274����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_line_ctrl_mode_rpt : 3;  /* bit[0-2]: CH1 TX_LINE_CTRL_MODE״̬�ϱ�
                                                                    0��IDLE
                                                                    1��Gģ
                                                                    2��Wģ
                                                                    3��LTEģ
                                                                    4��TDSģ
                                                                    5��Xģ
                                                                    others��IDLE */
        unsigned long  reserved                  : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_LINE_RPT1_UNION;
#define ABB_CH1_TX_LINE_RPT1_ch1_tx_line_ctrl_mode_rpt_START  (0)
#define ABB_CH1_TX_LINE_RPT1_ch1_tx_line_ctrl_mode_rpt_END    (2)


/***======================================================================***
                     (3/4) register_define_abb_rx
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : ABB_RX_IDLE_DIG_1_UNION
 �ṹ˵��  : RX_IDLE_DIG_1 �Ĵ����ṹ���塣��ַƫ����:0x400����ֵ:0x70�����:8
 �Ĵ���˵��: RX IDLEģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_hb_bp_idle    : 1;  /* bit[0]  : RXͨ������˲���bypass���ƣ�
                                                           0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                           1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  reserved_0       : 3;  /* bit[1-3]: ���� */
        unsigned long  rx_mode_dig_idle : 3;  /* bit[4-6]: RXͨ��ģʽ���ƣ�
                                                           000��2G_A
                                                           001��3G_SC/TDS_B/4G_C
                                                           010��4G
                                                           011��3G_DC/4G_B
                                                           100��TDS
                                                           101��CDMA
                                                           110��CA
                                                           111��2G_B(Ĭ��) */
        unsigned long  reserved_1       : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_DIG_1_UNION;
#define ABB_RX_IDLE_DIG_1_rx_hb_bp_idle_START     (0)
#define ABB_RX_IDLE_DIG_1_rx_hb_bp_idle_END       (0)
#define ABB_RX_IDLE_DIG_1_rx_mode_dig_idle_START  (4)
#define ABB_RX_IDLE_DIG_1_rx_mode_dig_idle_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_IDLE_DIG_2_UNION
 �ṹ˵��  : RX_IDLE_DIG_2 �Ĵ����ṹ���塣��ַƫ����:0x401����ֵ:0x03�����:8
 �Ĵ���˵��: RX IDLEģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_idle      : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_idle      : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_idle    : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                           00��gainΪ0.5(Ĭ��)
                                                           01��gainΪ0.75
                                                           10��gainΪ0.85
                                                           11��Reserved */
        unsigned long  rx_comp_bp_idle  : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                           0����bypass(Ĭ��)
                                                           1��bypass */
        unsigned long  rx_clk_inv_idle  : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                           0������
                                                           1������ */
        unsigned long  rx_flush_en_idle : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                           0����ʹ��
                                                           1��ʹ�� */
        unsigned long  reserved         : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_DIG_2_UNION;
#define ABB_RX_IDLE_DIG_2_rxa_pd_idle_START       (0)
#define ABB_RX_IDLE_DIG_2_rxa_pd_idle_END         (0)
#define ABB_RX_IDLE_DIG_2_rxb_pd_idle_START       (1)
#define ABB_RX_IDLE_DIG_2_rxb_pd_idle_END         (1)
#define ABB_RX_IDLE_DIG_2_gain_sel_idle_START     (2)
#define ABB_RX_IDLE_DIG_2_gain_sel_idle_END       (3)
#define ABB_RX_IDLE_DIG_2_rx_comp_bp_idle_START   (4)
#define ABB_RX_IDLE_DIG_2_rx_comp_bp_idle_END     (4)
#define ABB_RX_IDLE_DIG_2_rx_clk_inv_idle_START   (5)
#define ABB_RX_IDLE_DIG_2_rx_clk_inv_idle_END     (5)
#define ABB_RX_IDLE_DIG_2_rx_flush_en_idle_START  (6)
#define ABB_RX_IDLE_DIG_2_rx_flush_en_idle_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_IDLE_DIG_3_UNION
 �ṹ˵��  : RX_IDLE_DIG_3 �Ĵ����ṹ���塣��ַƫ����:0x402����ֵ:0x10�����:8
 �Ĵ���˵��: RX IDLEģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  blk_len_sel_idle : 2;  /* bit[0-1]: W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
                                                           2'b00��2560chip��(WģĬ��)
                                                           2'b01��512chip��
                                                           2'b10��1024chip��(XģĬ��)
                                                           2'b11��2048chip�� */
        unsigned long  reserved_0       : 2;  /* bit[2-3]: ���� */
        unsigned long  rx_comp_sel_idle : 3;  /* bit[4-6]: RXͨ�������˲�������ϵ���̶����ƣ�
                                                           000��ϵ�����̶����ɼĴ������ã�
                                                           001���̶�ϵ��1��
                                                           010���̶�ϵ��2��
                                                           011���̶�ϵ��3��
                                                           100���̶�ϵ��4�� */
        unsigned long  reserved_1       : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_DIG_3_UNION;
#define ABB_RX_IDLE_DIG_3_blk_len_sel_idle_START  (0)
#define ABB_RX_IDLE_DIG_3_blk_len_sel_idle_END    (1)
#define ABB_RX_IDLE_DIG_3_rx_comp_sel_idle_START  (4)
#define ABB_RX_IDLE_DIG_3_rx_comp_sel_idle_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_2G_DIG_1_UNION
 �ṹ˵��  : RX_2G_DIG_1 �Ĵ����ṹ���塣��ַƫ����:0x403����ֵ:0x00�����:8
 �Ĵ���˵��: RX 2Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_hb_bp_2g    : 1;  /* bit[0]  : RXͨ������˲���bypass���ƣ�
                                                         0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                         1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  reserved_0     : 3;  /* bit[1-3]: ���� */
        unsigned long  rx_mode_dig_2g : 3;  /* bit[4-6]: RXͨ��ģʽ���ƣ�
                                                         000��2G_A
                                                         001��3G_SC/TDS_B/4G_C
                                                         010��4G
                                                         011��3G_DC/4G_B
                                                         100��TDS
                                                         101��CDMA
                                                         110��CA
                                                         111��2G_B(Ĭ��) */
        unsigned long  reserved_1     : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_DIG_1_UNION;
#define ABB_RX_2G_DIG_1_rx_hb_bp_2g_START     (0)
#define ABB_RX_2G_DIG_1_rx_hb_bp_2g_END       (0)
#define ABB_RX_2G_DIG_1_rx_mode_dig_2g_START  (4)
#define ABB_RX_2G_DIG_1_rx_mode_dig_2g_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_2G_DIG_2_UNION
 �ṹ˵��  : RX_2G_DIG_2 �Ĵ����ṹ���塣��ַƫ����:0x404����ֵ:0x13�����:8
 �Ĵ���˵��: RX 2Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_2g      : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                         0����CLOCK GATING
                                                         1��CLOCK GATING(Ĭ��)
                                                         (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_2g      : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                         0����CLOCK GATING
                                                         1��CLOCK GATING(Ĭ��)
                                                         (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_2g    : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                         00��gainΪ0.5(Ĭ��)
                                                         01��gainΪ0.75
                                                         10��gainΪ0.85
                                                         11��Reserved */
        unsigned long  rx_comp_bp_2g  : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                         0����bypass
                                                         1��bypass(Ĭ��) */
        unsigned long  rx_clk_inv_2g  : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                         0������
                                                         1������ */
        unsigned long  rx_flush_en_2g : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                         0����ʹ��
                                                         1��ʹ�� */
        unsigned long  reserved       : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_DIG_2_UNION;
#define ABB_RX_2G_DIG_2_rxa_pd_2g_START       (0)
#define ABB_RX_2G_DIG_2_rxa_pd_2g_END         (0)
#define ABB_RX_2G_DIG_2_rxb_pd_2g_START       (1)
#define ABB_RX_2G_DIG_2_rxb_pd_2g_END         (1)
#define ABB_RX_2G_DIG_2_gain_sel_2g_START     (2)
#define ABB_RX_2G_DIG_2_gain_sel_2g_END       (3)
#define ABB_RX_2G_DIG_2_rx_comp_bp_2g_START   (4)
#define ABB_RX_2G_DIG_2_rx_comp_bp_2g_END     (4)
#define ABB_RX_2G_DIG_2_rx_clk_inv_2g_START   (5)
#define ABB_RX_2G_DIG_2_rx_clk_inv_2g_END     (5)
#define ABB_RX_2G_DIG_2_rx_flush_en_2g_START  (6)
#define ABB_RX_2G_DIG_2_rx_flush_en_2g_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_2G_DIG_3_UNION
 �ṹ˵��  : RX_2G_DIG_3 �Ĵ����ṹ���塣��ַƫ����:0x405����ֵ:0x00�����:8
 �Ĵ���˵��: RX 2Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  blk_len_sel_2g : 2;  /* bit[0-1]: W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
                                                         2'b00��2560chip��(WģĬ��)
                                                         2'b01��512chip��
                                                         2'b10��1024chip��(XģĬ��)
                                                         2'b11��2048chip�� */
        unsigned long  reserved_0     : 2;  /* bit[2-3]: ���� */
        unsigned long  rx_comp_sel_2g : 3;  /* bit[4-6]: RXͨ�������˲�������ϵ���̶����ƣ�
                                                         000��ϵ�����̶����ɼĴ������ã�
                                                         001���̶�ϵ��1��
                                                         010���̶�ϵ��2��
                                                         011���̶�ϵ��3��
                                                         100���̶�ϵ��4��
                                                         101���̶�ϵ��5��
                                                         110���̶�ϵ��6��
                                                         111���̶�ϵ��7�� */
        unsigned long  reserved_1     : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_DIG_3_UNION;
#define ABB_RX_2G_DIG_3_blk_len_sel_2g_START  (0)
#define ABB_RX_2G_DIG_3_blk_len_sel_2g_END    (1)
#define ABB_RX_2G_DIG_3_rx_comp_sel_2g_START  (4)
#define ABB_RX_2G_DIG_3_rx_comp_sel_2g_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_C_DIG_1_UNION
 �ṹ˵��  : RX_C_DIG_1 �Ĵ����ṹ���塣��ַƫ����:0x406����ֵ:0x51�����:8
 �Ĵ���˵��: RX Cģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_hb_bp_c    : 1;  /* bit[0]  : RXͨ������˲���bypass���ƣ�
                                                        0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                        1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  reserved_0    : 3;  /* bit[1-3]: ���� */
        unsigned long  rx_mode_dig_c : 3;  /* bit[4-6]: RXͨ��ģʽ���ƣ�
                                                        000��2G_A(Ĭ��)
                                                        001��3G_SC/TDS_B/4G_C
                                                        010��4G
                                                        011��3G_DC/4G_B
                                                        100��TDS
                                                        101��CDMA
                                                        110��CA
                                                        111��2G_B */
        unsigned long  reserved_1    : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_DIG_1_UNION;
#define ABB_RX_C_DIG_1_rx_hb_bp_c_START     (0)
#define ABB_RX_C_DIG_1_rx_hb_bp_c_END       (0)
#define ABB_RX_C_DIG_1_rx_mode_dig_c_START  (4)
#define ABB_RX_C_DIG_1_rx_mode_dig_c_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_C_DIG_2_UNION
 �ṹ˵��  : RX_C_DIG_2 �Ĵ����ṹ���塣��ַƫ����:0x407����ֵ:0x03�����:8
 �Ĵ���˵��: RX Cģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_c      : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                        0����CLOCK GATING
                                                        1��CLOCK GATING(Ĭ��)
                                                        (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_c      : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                        0����CLOCK GATING
                                                        1��CLOCK GATING(Ĭ��)
                                                        (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_c    : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                        00��gainΪ0.5(Ĭ��)
                                                        01��gainΪ0.75
                                                        10��gainΪ0.85
                                                        11��Reserved */
        unsigned long  rx_comp_bp_c  : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                        0����bypass
                                                        1��bypass(Ĭ��) */
        unsigned long  rx_clk_inv_c  : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                        0������
                                                        1������ */
        unsigned long  rx_flush_en_c : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                        0����ʹ��
                                                        1��ʹ�� */
        unsigned long  reserved      : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_DIG_2_UNION;
#define ABB_RX_C_DIG_2_rxa_pd_c_START       (0)
#define ABB_RX_C_DIG_2_rxa_pd_c_END         (0)
#define ABB_RX_C_DIG_2_rxb_pd_c_START       (1)
#define ABB_RX_C_DIG_2_rxb_pd_c_END         (1)
#define ABB_RX_C_DIG_2_gain_sel_c_START     (2)
#define ABB_RX_C_DIG_2_gain_sel_c_END       (3)
#define ABB_RX_C_DIG_2_rx_comp_bp_c_START   (4)
#define ABB_RX_C_DIG_2_rx_comp_bp_c_END     (4)
#define ABB_RX_C_DIG_2_rx_clk_inv_c_START   (5)
#define ABB_RX_C_DIG_2_rx_clk_inv_c_END     (5)
#define ABB_RX_C_DIG_2_rx_flush_en_c_START  (6)
#define ABB_RX_C_DIG_2_rx_flush_en_c_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_C_DIG_3_UNION
 �ṹ˵��  : RX_C_DIG_3 �Ĵ����ṹ���塣��ַƫ����:0x408����ֵ:0x12�����:8
 �Ĵ���˵��: RX Cģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  blk_len_sel_c : 2;  /* bit[0-1]: W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
                                                        2'b00��2560chip��(WģĬ��)
                                                        2'b01��512chip��
                                                        2'b10��1024chip��(XģĬ��)
                                                        2'b11��2048chip�� */
        unsigned long  reserved_0    : 2;  /* bit[2-3]: ���� */
        unsigned long  rx_comp_sel_c : 3;  /* bit[4-6]: RXͨ�������˲�������ϵ���̶����ƣ�
                                                        000��ϵ�����̶����ɼĴ������ã�
                                                        001���̶�ϵ��1��
                                                        010���̶�ϵ��2��
                                                        011���̶�ϵ��3��
                                                        100���̶�ϵ��4��
                                                        101���̶�ϵ��5��
                                                        110���̶�ϵ��6��
                                                        111���̶�ϵ��7�� */
        unsigned long  reserved_1    : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_DIG_3_UNION;
#define ABB_RX_C_DIG_3_blk_len_sel_c_START  (0)
#define ABB_RX_C_DIG_3_blk_len_sel_c_END    (1)
#define ABB_RX_C_DIG_3_rx_comp_sel_c_START  (4)
#define ABB_RX_C_DIG_3_rx_comp_sel_c_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_DIG_1_UNION
 �ṹ˵��  : RX_TDS_DIG_1 �Ĵ����ṹ���塣��ַƫ����:0x409����ֵ:0x11�����:8
 �Ĵ���˵��: RX TDSģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_hb_bp_tds    : 1;  /* bit[0]  : RXͨ������˲���bypass���ƣ�
                                                          0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                          1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  reserved_0      : 3;  /* bit[1-3]: ���� */
        unsigned long  rx_mode_dig_tds : 3;  /* bit[4-6]: RXͨ��ģʽ���ƣ�
                                                          000��2G_A(Ĭ��)
                                                          001��3G_SC/TDS_B/4G_C
                                                          010��4G
                                                          011��3G_DC/4G_B
                                                          100��TDS
                                                          101��CDMA
                                                          110��CA
                                                          111��2G_B */
        unsigned long  reserved_1      : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_DIG_1_UNION;
#define ABB_RX_TDS_DIG_1_rx_hb_bp_tds_START     (0)
#define ABB_RX_TDS_DIG_1_rx_hb_bp_tds_END       (0)
#define ABB_RX_TDS_DIG_1_rx_mode_dig_tds_START  (4)
#define ABB_RX_TDS_DIG_1_rx_mode_dig_tds_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_DIG_2_UNION
 �ṹ˵��  : RX_TDS_DIG_2 �Ĵ����ṹ���塣��ַƫ����:0x40A����ֵ:0xD3�����:8
 �Ĵ���˵��: RX TDSģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_tds      : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                          0����CLOCK GATING
                                                          1��CLOCK GATING(Ĭ��)
                                                          (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_tds      : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                          0����CLOCK GATING
                                                          1��CLOCK GATING(Ĭ��)
                                                          (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_tds    : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                          00��gainΪ0.5(Ĭ��)
                                                          01��gainΪ0.75
                                                          10��gainΪ0.85
                                                          11��Reserved */
        unsigned long  rx_comp_bp_tds  : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                          0����bypass
                                                          1��bypass(Ĭ��) */
        unsigned long  rx_clk_inv_tds  : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                          0������
                                                          1������ */
        unsigned long  rx_flush_en_tds : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                          0����ʹ��
                                                          1��ʹ�� */
        unsigned long  reserved        : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_DIG_2_UNION;
#define ABB_RX_TDS_DIG_2_rxa_pd_tds_START       (0)
#define ABB_RX_TDS_DIG_2_rxa_pd_tds_END         (0)
#define ABB_RX_TDS_DIG_2_rxb_pd_tds_START       (1)
#define ABB_RX_TDS_DIG_2_rxb_pd_tds_END         (1)
#define ABB_RX_TDS_DIG_2_gain_sel_tds_START     (2)
#define ABB_RX_TDS_DIG_2_gain_sel_tds_END       (3)
#define ABB_RX_TDS_DIG_2_rx_comp_bp_tds_START   (4)
#define ABB_RX_TDS_DIG_2_rx_comp_bp_tds_END     (4)
#define ABB_RX_TDS_DIG_2_rx_clk_inv_tds_START   (5)
#define ABB_RX_TDS_DIG_2_rx_clk_inv_tds_END     (5)
#define ABB_RX_TDS_DIG_2_rx_flush_en_tds_START  (6)
#define ABB_RX_TDS_DIG_2_rx_flush_en_tds_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_DIG_3_UNION
 �ṹ˵��  : RX_TDS_DIG_3 �Ĵ����ṹ���塣��ַƫ����:0x40B����ֵ:0x10�����:8
 �Ĵ���˵��: RX TDSģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  blk_len_sel_tds : 2;  /* bit[0-1]: W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
                                                          2'b00��2560chip��(WģĬ��)
                                                          2'b01��512chip��
                                                          2'b10��1024chip��(XģĬ��)
                                                          2'b11��2048chip�� */
        unsigned long  reserved_0      : 2;  /* bit[2-3]: ���� */
        unsigned long  rx_comp_sel_tds : 3;  /* bit[4-6]: RXͨ�������˲�������ϵ���̶����ƣ�
                                                          000��ϵ�����̶����ɼĴ������ã�
                                                          001���̶�ϵ��1��
                                                          010���̶�ϵ��2��
                                                          011���̶�ϵ��3��
                                                          100���̶�ϵ��4��
                                                          101���̶�ϵ��5��
                                                          110���̶�ϵ��6��
                                                          111���̶�ϵ��7�� */
        unsigned long  reserved_1      : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_DIG_3_UNION;
#define ABB_RX_TDS_DIG_3_blk_len_sel_tds_START  (0)
#define ABB_RX_TDS_DIG_3_blk_len_sel_tds_END    (1)
#define ABB_RX_TDS_DIG_3_rx_comp_sel_tds_START  (4)
#define ABB_RX_TDS_DIG_3_rx_comp_sel_tds_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RX_3G_DIG_1_UNION
 �ṹ˵��  : CH0_RX_3G_DIG_1 �Ĵ����ṹ���塣��ַƫ����:0x410����ֵ:0x11�����:8
 �Ĵ���˵��: RX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_hb_bp_3g    : 1;  /* bit[0]  : RXͨ������˲���bypass���ƣ�
                                                             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  reserved_0         : 3;  /* bit[1-3]: ���� */
        unsigned long  ch0_rx_mode_dig_3g : 3;  /* bit[4-6]: RXͨ��ģʽ���ƣ�
                                                             000��2G_A(Ĭ��)
                                                             001��3G_SC/TDS_B/4G_C
                                                             010��4G
                                                             011��3G_DC/4G_B
                                                             100��TDS
                                                             101��CDMA
                                                             110��CA
                                                             111��2G_B */
        unsigned long  reserved_1         : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_3G_DIG_1_UNION;
#define ABB_CH0_RX_3G_DIG_1_ch0_rx_hb_bp_3g_START     (0)
#define ABB_CH0_RX_3G_DIG_1_ch0_rx_hb_bp_3g_END       (0)
#define ABB_CH0_RX_3G_DIG_1_ch0_rx_mode_dig_3g_START  (4)
#define ABB_CH0_RX_3G_DIG_1_ch0_rx_mode_dig_3g_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RX_3G_DIG_2_UNION
 �ṹ˵��  : CH0_RX_3G_DIG_2 �Ĵ����ṹ���塣��ַƫ����:0x411����ֵ:0x03�����:8
 �Ĵ���˵��: RX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_pd_3g      : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                             0����CLOCK GATING
                                                             1��CLOCK GATING(Ĭ��)
                                                             (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  ch0_rxb_pd_3g      : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                             0����CLOCK GATING
                                                             1��CLOCK GATING(Ĭ��)
                                                             (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  ch0_gain_sel_3g    : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                             00��gainΪ0.5(Ĭ��)
                                                             01��gainΪ0.75
                                                             10��gainΪ0.85
                                                             11��Reserved */
        unsigned long  ch0_rx_comp_bp_3g  : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                             0����bypass(Ĭ��)
                                                             1��bypass */
        unsigned long  ch0_rx_clk_inv_3g  : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                             0������
                                                             1������ */
        unsigned long  ch0_rx_flush_en_3g : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  reserved           : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_3G_DIG_2_UNION;
#define ABB_CH0_RX_3G_DIG_2_ch0_rxa_pd_3g_START       (0)
#define ABB_CH0_RX_3G_DIG_2_ch0_rxa_pd_3g_END         (0)
#define ABB_CH0_RX_3G_DIG_2_ch0_rxb_pd_3g_START       (1)
#define ABB_CH0_RX_3G_DIG_2_ch0_rxb_pd_3g_END         (1)
#define ABB_CH0_RX_3G_DIG_2_ch0_gain_sel_3g_START     (2)
#define ABB_CH0_RX_3G_DIG_2_ch0_gain_sel_3g_END       (3)
#define ABB_CH0_RX_3G_DIG_2_ch0_rx_comp_bp_3g_START   (4)
#define ABB_CH0_RX_3G_DIG_2_ch0_rx_comp_bp_3g_END     (4)
#define ABB_CH0_RX_3G_DIG_2_ch0_rx_clk_inv_3g_START   (5)
#define ABB_CH0_RX_3G_DIG_2_ch0_rx_clk_inv_3g_END     (5)
#define ABB_CH0_RX_3G_DIG_2_ch0_rx_flush_en_3g_START  (6)
#define ABB_CH0_RX_3G_DIG_2_ch0_rx_flush_en_3g_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RX_3G_DIG_3_UNION
 �ṹ˵��  : CH0_RX_3G_DIG_3 �Ĵ����ṹ���塣��ַƫ����:0x412����ֵ:0x10�����:8
 �Ĵ���˵��: RX 3Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_blk_len_sel_3g : 2;  /* bit[0-1]: W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
                                                             2'b00��2560chip��(WģĬ��)
                                                             2'b01��512chip��
                                                             2'b10��1024chip��(XģĬ��)
                                                             2'b11��2048chip�� */
        unsigned long  reserved_0         : 2;  /* bit[2-3]: ���� */
        unsigned long  ch0_rx_comp_sel_3g : 3;  /* bit[4-6]: RXͨ�������˲�������ϵ���̶����ƣ�
                                                             000��ϵ�����̶����ɼĴ������ã�
                                                             001���̶�ϵ��1��
                                                             010���̶�ϵ��2��
                                                             011���̶�ϵ��3��
                                                             100���̶�ϵ��4��
                                                             101���̶�ϵ��5��
                                                             110���̶�ϵ��6��
                                                             111���̶�ϵ��7�� */
        unsigned long  reserved_1         : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_3G_DIG_3_UNION;
#define ABB_CH0_RX_3G_DIG_3_ch0_blk_len_sel_3g_START  (0)
#define ABB_CH0_RX_3G_DIG_3_ch0_blk_len_sel_3g_END    (1)
#define ABB_CH0_RX_3G_DIG_3_ch0_rx_comp_sel_3g_START  (4)
#define ABB_CH0_RX_3G_DIG_3_ch0_rx_comp_sel_3g_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RX_3G_DIG_1_UNION
 �ṹ˵��  : CH1_RX_3G_DIG_1 �Ĵ����ṹ���塣��ַƫ����:0x413����ֵ:0x11�����:8
 �Ĵ���˵��: RX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rx_hb_bp_3g    : 1;  /* bit[0]  : RXͨ������˲���bypass���ƣ�
                                                             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  reserved_0         : 3;  /* bit[1-3]: ���� */
        unsigned long  ch1_rx_mode_dig_3g : 3;  /* bit[4-6]: RXͨ��ģʽ���ƣ�
                                                             000��2G_A(Ĭ��)
                                                             001��3G_SC/TDS_B/4G_C
                                                             010��4G
                                                             011��3G_DC/4G_B
                                                             100��TDS
                                                             101��CDMA
                                                             110��CA
                                                             111��2G_B */
        unsigned long  reserved_1         : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_3G_DIG_1_UNION;
#define ABB_CH1_RX_3G_DIG_1_ch1_rx_hb_bp_3g_START     (0)
#define ABB_CH1_RX_3G_DIG_1_ch1_rx_hb_bp_3g_END       (0)
#define ABB_CH1_RX_3G_DIG_1_ch1_rx_mode_dig_3g_START  (4)
#define ABB_CH1_RX_3G_DIG_1_ch1_rx_mode_dig_3g_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RX_3G_DIG_2_UNION
 �ṹ˵��  : CH1_RX_3G_DIG_2 �Ĵ����ṹ���塣��ַƫ����:0x414����ֵ:0x03�����:8
 �Ĵ���˵��: RX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_pd_3g      : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                             0����CLOCK GATING
                                                             1��CLOCK GATING(Ĭ��)
                                                             (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  ch1_rxb_pd_3g      : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                             0����CLOCK GATING
                                                             1��CLOCK GATING(Ĭ��)
                                                             (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  ch1_gain_sel_3g    : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                             00��gainΪ0.5(Ĭ��)
                                                             01��gainΪ0.75
                                                             10��gainΪ0.85
                                                             11��Reserved */
        unsigned long  ch1_rx_comp_bp_3g  : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                             0����bypass(Ĭ��)
                                                             1��bypass */
        unsigned long  ch1_rx_clk_inv_3g  : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                             0������
                                                             1������ */
        unsigned long  ch1_rx_flush_en_3g : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  reserved           : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_3G_DIG_2_UNION;
#define ABB_CH1_RX_3G_DIG_2_ch1_rxa_pd_3g_START       (0)
#define ABB_CH1_RX_3G_DIG_2_ch1_rxa_pd_3g_END         (0)
#define ABB_CH1_RX_3G_DIG_2_ch1_rxb_pd_3g_START       (1)
#define ABB_CH1_RX_3G_DIG_2_ch1_rxb_pd_3g_END         (1)
#define ABB_CH1_RX_3G_DIG_2_ch1_gain_sel_3g_START     (2)
#define ABB_CH1_RX_3G_DIG_2_ch1_gain_sel_3g_END       (3)
#define ABB_CH1_RX_3G_DIG_2_ch1_rx_comp_bp_3g_START   (4)
#define ABB_CH1_RX_3G_DIG_2_ch1_rx_comp_bp_3g_END     (4)
#define ABB_CH1_RX_3G_DIG_2_ch1_rx_clk_inv_3g_START   (5)
#define ABB_CH1_RX_3G_DIG_2_ch1_rx_clk_inv_3g_END     (5)
#define ABB_CH1_RX_3G_DIG_2_ch1_rx_flush_en_3g_START  (6)
#define ABB_CH1_RX_3G_DIG_2_ch1_rx_flush_en_3g_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RX_3G_DIG_3_UNION
 �ṹ˵��  : CH1_RX_3G_DIG_3 �Ĵ����ṹ���塣��ַƫ����:0x415����ֵ:0x10�����:8
 �Ĵ���˵��: RX 3Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_blk_len_sel_3g : 2;  /* bit[0-1]: W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
                                                             2'b00��2560chip��(WģĬ��)
                                                             2'b01��512chip��
                                                             2'b10��1024chip��(XģĬ��)
                                                             2'b11��2048chip�� */
        unsigned long  reserved_0         : 2;  /* bit[2-3]: ���� */
        unsigned long  ch1_rx_comp_sel_3g : 3;  /* bit[4-6]: RXͨ�������˲�������ϵ���̶����ƣ�
                                                             000��ϵ�����̶����ɼĴ������ã�
                                                             001���̶�ϵ��1��
                                                             010���̶�ϵ��2��
                                                             011���̶�ϵ��3��
                                                             100���̶�ϵ��4��
                                                             101���̶�ϵ��5��
                                                             110���̶�ϵ��6��
                                                             111���̶�ϵ��7�� */
        unsigned long  reserved_1         : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_3G_DIG_3_UNION;
#define ABB_CH1_RX_3G_DIG_3_ch1_blk_len_sel_3g_START  (0)
#define ABB_CH1_RX_3G_DIG_3_ch1_blk_len_sel_3g_END    (1)
#define ABB_CH1_RX_3G_DIG_3_ch1_rx_comp_sel_3g_START  (4)
#define ABB_CH1_RX_3G_DIG_3_ch1_rx_comp_sel_3g_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RX_4G_DIG_1_UNION
 �ṹ˵��  : CH0_RX_4G_DIG_1 �Ĵ����ṹ���塣��ַƫ����:0x440����ֵ:0x20�����:8
 �Ĵ���˵��: RX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_hb_bp_4g    : 1;  /* bit[0]  : RXͨ������˲���bypass���ƣ�
                                                             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  reserved_0         : 3;  /* bit[1-3]: ���� */
        unsigned long  ch0_rx_mode_dig_4g : 3;  /* bit[4-6]: RXͨ��ģʽ���ƣ�
                                                             000��2G_A(Ĭ��)
                                                             001��3G_SC/TDS_B/4G_C
                                                             010��4G
                                                             011��3G_DC/4G_B
                                                             100��TDS
                                                             101��CDMA
                                                             110��CA
                                                             111��2G_B */
        unsigned long  reserved_1         : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_4G_DIG_1_UNION;
#define ABB_CH0_RX_4G_DIG_1_ch0_rx_hb_bp_4g_START     (0)
#define ABB_CH0_RX_4G_DIG_1_ch0_rx_hb_bp_4g_END       (0)
#define ABB_CH0_RX_4G_DIG_1_ch0_rx_mode_dig_4g_START  (4)
#define ABB_CH0_RX_4G_DIG_1_ch0_rx_mode_dig_4g_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RX_4G_DIG_2_UNION
 �ṹ˵��  : CH0_RX_4G_DIG_2 �Ĵ����ṹ���塣��ַƫ����:0x441����ֵ:0x03�����:8
 �Ĵ���˵��: RX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_pd_4g      : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                             0����CLOCK GATING
                                                             1��CLOCK GATING(Ĭ��)
                                                             (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  ch0_rxb_pd_4g      : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                             0����CLOCK GATING
                                                             1��CLOCK GATING(Ĭ��)
                                                             (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  ch0_gain_sel_4g    : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                             00��gainΪ0.5(Ĭ��)
                                                             01��gainΪ0.75
                                                             10��gainΪ0.85
                                                             11��Reserved */
        unsigned long  ch0_rx_comp_bp_4g  : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                             0����bypass(Ĭ��)
                                                             1��bypass */
        unsigned long  ch0_rx_clk_inv_4g  : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                             0������
                                                             1������ */
        unsigned long  ch0_rx_flush_en_4g : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  reserved           : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_4G_DIG_2_UNION;
#define ABB_CH0_RX_4G_DIG_2_ch0_rxa_pd_4g_START       (0)
#define ABB_CH0_RX_4G_DIG_2_ch0_rxa_pd_4g_END         (0)
#define ABB_CH0_RX_4G_DIG_2_ch0_rxb_pd_4g_START       (1)
#define ABB_CH0_RX_4G_DIG_2_ch0_rxb_pd_4g_END         (1)
#define ABB_CH0_RX_4G_DIG_2_ch0_gain_sel_4g_START     (2)
#define ABB_CH0_RX_4G_DIG_2_ch0_gain_sel_4g_END       (3)
#define ABB_CH0_RX_4G_DIG_2_ch0_rx_comp_bp_4g_START   (4)
#define ABB_CH0_RX_4G_DIG_2_ch0_rx_comp_bp_4g_END     (4)
#define ABB_CH0_RX_4G_DIG_2_ch0_rx_clk_inv_4g_START   (5)
#define ABB_CH0_RX_4G_DIG_2_ch0_rx_clk_inv_4g_END     (5)
#define ABB_CH0_RX_4G_DIG_2_ch0_rx_flush_en_4g_START  (6)
#define ABB_CH0_RX_4G_DIG_2_ch0_rx_flush_en_4g_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RX_4G_DIG_3_UNION
 �ṹ˵��  : CH0_RX_4G_DIG_3 �Ĵ����ṹ���塣��ַƫ����:0x442����ֵ:0x10�����:8
 �Ĵ���˵��: RX 4Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_blk_len_sel_4g : 2;  /* bit[0-1]: W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
                                                             2'b00��2560chip��(WģĬ��)
                                                             2'b01��512chip��
                                                             2'b10��1024chip��(XģĬ��)
                                                             2'b11��2048chip�� */
        unsigned long  reserved_0         : 2;  /* bit[2-3]: ���� */
        unsigned long  ch0_rx_comp_sel_4g : 3;  /* bit[4-6]: RXͨ�������˲�������ϵ���̶����ƣ�
                                                             000��ϵ�����̶����ɼĴ������ã�
                                                             001���̶�ϵ��1��
                                                             010���̶�ϵ��2��
                                                             011���̶�ϵ��3��
                                                             100���̶�ϵ��4��
                                                             101���̶�ϵ��5��
                                                             110���̶�ϵ��6��
                                                             111���̶�ϵ��7�� */
        unsigned long  reserved_1         : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_4G_DIG_3_UNION;
#define ABB_CH0_RX_4G_DIG_3_ch0_blk_len_sel_4g_START  (0)
#define ABB_CH0_RX_4G_DIG_3_ch0_blk_len_sel_4g_END    (1)
#define ABB_CH0_RX_4G_DIG_3_ch0_rx_comp_sel_4g_START  (4)
#define ABB_CH0_RX_4G_DIG_3_ch0_rx_comp_sel_4g_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RX_4G_DIG_1_UNION
 �ṹ˵��  : CH1_RX_4G_DIG_1 �Ĵ����ṹ���塣��ַƫ����:0x443����ֵ:0x20�����:8
 �Ĵ���˵��: RX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rx_hb_bp_4g    : 1;  /* bit[0]  : RXͨ������˲���bypass���ƣ�
                                                             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  reserved_0         : 3;  /* bit[1-3]: ���� */
        unsigned long  ch1_rx_mode_dig_4g : 3;  /* bit[4-6]: RXͨ��ģʽ���ƣ�
                                                             000��2G_A(Ĭ��)
                                                             001��3G_SC/TDS_B/4G_C
                                                             010��4G
                                                             011��3G_DC/4G_B
                                                             100��TDS
                                                             101��CDMA
                                                             110��CA
                                                             111��2G_B */
        unsigned long  reserved_1         : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_4G_DIG_1_UNION;
#define ABB_CH1_RX_4G_DIG_1_ch1_rx_hb_bp_4g_START     (0)
#define ABB_CH1_RX_4G_DIG_1_ch1_rx_hb_bp_4g_END       (0)
#define ABB_CH1_RX_4G_DIG_1_ch1_rx_mode_dig_4g_START  (4)
#define ABB_CH1_RX_4G_DIG_1_ch1_rx_mode_dig_4g_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RX_4G_DIG_2_UNION
 �ṹ˵��  : CH1_RX_4G_DIG_2 �Ĵ����ṹ���塣��ַƫ����:0x444����ֵ:0x03�����:8
 �Ĵ���˵��: RX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_pd_4g      : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                             0����CLOCK GATING
                                                             1��CLOCK GATING(Ĭ��)
                                                             (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  ch1_rxb_pd_4g      : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                             0����CLOCK GATING
                                                             1��CLOCK GATING(Ĭ��)
                                                             (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  ch1_gain_sel_4g    : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                             00��gainΪ0.5(Ĭ��)
                                                             01��gainΪ0.75
                                                             10��gainΪ0.85
                                                             11��Reserved */
        unsigned long  ch1_rx_comp_bp_4g  : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                             0����bypass(Ĭ��)
                                                             1��bypass */
        unsigned long  ch1_rx_clk_inv_4g  : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                             0������
                                                             1������ */
        unsigned long  ch1_rx_flush_en_4g : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  reserved           : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_4G_DIG_2_UNION;
#define ABB_CH1_RX_4G_DIG_2_ch1_rxa_pd_4g_START       (0)
#define ABB_CH1_RX_4G_DIG_2_ch1_rxa_pd_4g_END         (0)
#define ABB_CH1_RX_4G_DIG_2_ch1_rxb_pd_4g_START       (1)
#define ABB_CH1_RX_4G_DIG_2_ch1_rxb_pd_4g_END         (1)
#define ABB_CH1_RX_4G_DIG_2_ch1_gain_sel_4g_START     (2)
#define ABB_CH1_RX_4G_DIG_2_ch1_gain_sel_4g_END       (3)
#define ABB_CH1_RX_4G_DIG_2_ch1_rx_comp_bp_4g_START   (4)
#define ABB_CH1_RX_4G_DIG_2_ch1_rx_comp_bp_4g_END     (4)
#define ABB_CH1_RX_4G_DIG_2_ch1_rx_clk_inv_4g_START   (5)
#define ABB_CH1_RX_4G_DIG_2_ch1_rx_clk_inv_4g_END     (5)
#define ABB_CH1_RX_4G_DIG_2_ch1_rx_flush_en_4g_START  (6)
#define ABB_CH1_RX_4G_DIG_2_ch1_rx_flush_en_4g_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RX_4G_DIG_3_UNION
 �ṹ˵��  : CH1_RX_4G_DIG_3 �Ĵ����ṹ���塣��ַƫ����:0x445����ֵ:0x10�����:8
 �Ĵ���˵��: RX 4Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_blk_len_sel_4g : 2;  /* bit[0-1]: W/XģBlock������ʱ�䡣����W/Xģ�⣬����ģʽ�üĴ�������Ч��
                                                             2'b00��2560chip��(WģĬ��)
                                                             2'b01��512chip��
                                                             2'b10��1024chip��(XģĬ��)
                                                             2'b11��2048chip�� */
        unsigned long  reserved_0         : 2;  /* bit[2-3]: ���� */
        unsigned long  ch1_rx_comp_sel_4g : 3;  /* bit[4-6]: RXͨ�������˲�������ϵ���̶����ƣ�
                                                             000��ϵ�����̶����ɼĴ������ã�
                                                             001���̶�ϵ��1��
                                                             010���̶�ϵ��2��
                                                             011���̶�ϵ��3��
                                                             100���̶�ϵ��4��
                                                             101���̶�ϵ��5��
                                                             110���̶�ϵ��6��
                                                             111���̶�ϵ��7�� */
        unsigned long  reserved_1         : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_4G_DIG_3_UNION;
#define ABB_CH1_RX_4G_DIG_3_ch1_blk_len_sel_4g_START  (0)
#define ABB_CH1_RX_4G_DIG_3_ch1_blk_len_sel_4g_END    (1)
#define ABB_CH1_RX_4G_DIG_3_ch1_rx_comp_sel_4g_START  (4)
#define ABB_CH1_RX_4G_DIG_3_ch1_rx_comp_sel_4g_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_RX_EN_DELAY_UNION
 �ṹ˵��  : RX_EN_DELAY �Ĵ����ṹ���塣��ַƫ����:0x470����ֵ:0x01�����:8
 �Ĵ���˵��: RXʱ���ſ��ӳٹ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_en_dly_enable : 1;  /* bit[0]  : RXʱ���ſ��ӳٹ���ʹ�ܡ��ù��ܴ򿪺�RX����·�����ӱ�RX���ݺ�VLD�ź��ӳٹرա� */
        unsigned long  rx_en_dly_cycle  : 2;  /* bit[1-2]: RXʱ���ſ��ӳٵ�19.2MHzʱ�Ӹ�����
                                                               L/CA/Xģ   W/TDSģ  Gģ
                                                           00��  1          2      32��  (Ĭ��)
                                                           01��  2          4      64��
                                                           10��  4          8      128��
                                                           11��  reserved  */
        unsigned long  reserved         : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_EN_DELAY_UNION;
#define ABB_RX_EN_DELAY_rx_en_dly_enable_START  (0)
#define ABB_RX_EN_DELAY_rx_en_dly_enable_END    (0)
#define ABB_RX_EN_DELAY_rx_en_dly_cycle_START   (1)
#define ABB_RX_EN_DELAY_rx_en_dly_cycle_END     (2)


/*****************************************************************************
 �ṹ��    : ABB_COMB_MODE_UNION
 �ṹ˵��  : COMB_MODE �Ĵ����ṹ���塣��ַƫ����:0x471����ֵ:0x00�����:8
 �Ĵ���˵��: ģʽ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_comb_mode : 1;  /* bit[0]  :  */
        unsigned long  reserved      : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_COMB_MODE_UNION;
#define ABB_COMB_MODE_ch0_comb_mode_START  (0)
#define ABB_COMB_MODE_ch0_comb_mode_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RX_TESTMODE_UNION
 �ṹ˵��  : CH0_RX_TESTMODE �Ĵ����ṹ���塣��ַƫ����:0x480����ֵ:0x00�����:8
 �Ĵ���˵��: ����ģʽ�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_sw_rst   : 1;  /* bit[0]  : ���ֲ���RXͨ����λ�źţ�
                                                          0������λ(Ĭ��)
                                                          1����λ */
        unsigned long  ch0_cic_gate_en : 1;  /* bit[1]  :  */
        unsigned long  ch0_rx_loop_sel : 2;  /* bit[2-3]:  */
        unsigned long  ch0_out_sel     : 2;  /* bit[4-5]:  */
        unsigned long  reserved        : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_TESTMODE_UNION;
#define ABB_CH0_RX_TESTMODE_ch0_rx_sw_rst_START    (0)
#define ABB_CH0_RX_TESTMODE_ch0_rx_sw_rst_END      (0)
#define ABB_CH0_RX_TESTMODE_ch0_cic_gate_en_START  (1)
#define ABB_CH0_RX_TESTMODE_ch0_cic_gate_en_END    (1)
#define ABB_CH0_RX_TESTMODE_ch0_rx_loop_sel_START  (2)
#define ABB_CH0_RX_TESTMODE_ch0_rx_loop_sel_END    (3)
#define ABB_CH0_RX_TESTMODE_ch0_out_sel_START      (4)
#define ABB_CH0_RX_TESTMODE_ch0_out_sel_END        (5)


/*****************************************************************************
 �ṹ��    : ABB_CH0_PLL_SEL_UNION
 �ṹ˵��  : CH0_PLL_SEL �Ĵ����ṹ���塣��ַƫ����:0x481����ֵ:0x00�����:8
 �Ĵ���˵��: PLLѡ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_g_pll_sel   : 2;  /* bit[0-1]: GģPLLѡ��
                                                          0��ѡ��GPLL
                                                          1��ѡ��SCPLL0
                                                          2��ѡ��SCPLL1 */
        unsigned long  ch0_wtl_pll_sel : 1;  /* bit[2]  : WTLģPLLѡ��
                                                          0��ѡ��SCPLL0
                                                          1��ѡ��SCPLL1 */
        unsigned long  ch0_c1_pll_sel  : 1;  /* bit[3]  : C1ģPLLѡ��
                                                          0��ѡ��SCPLL1
                                                          1��ѡ��SCPLL0 */
        unsigned long  reserved        : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_PLL_SEL_UNION;
#define ABB_CH0_PLL_SEL_ch0_g_pll_sel_START    (0)
#define ABB_CH0_PLL_SEL_ch0_g_pll_sel_END      (1)
#define ABB_CH0_PLL_SEL_ch0_wtl_pll_sel_START  (2)
#define ABB_CH0_PLL_SEL_ch0_wtl_pll_sel_END    (2)
#define ABB_CH0_PLL_SEL_ch0_c1_pll_sel_START   (3)
#define ABB_CH0_PLL_SEL_ch0_c1_pll_sel_END     (3)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXA_I_COEF2_UNION
 �ṹ˵��  : CH0_RXA_I_COEF2 �Ĵ����ṹ���塣��ַƫ����:0x486����ֵ:0x01�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_i_c3_msb : 1;  /* bit[0]  : RXAͨ��I·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved         : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_I_COEF2_UNION;
#define ABB_CH0_RXA_I_COEF2_ch0_rxa_i_c3_msb_START  (0)
#define ABB_CH0_RXA_I_COEF2_ch0_rxa_i_c3_msb_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXA_Q_COEF2_UNION
 �ṹ˵��  : CH0_RXA_Q_COEF2 �Ĵ����ṹ���塣��ַƫ����:0x48C����ֵ:0x01�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_q_c3_msb : 1;  /* bit[0]  : RXAͨ��I·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved         : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_Q_COEF2_UNION;
#define ABB_CH0_RXA_Q_COEF2_ch0_rxa_q_c3_msb_START  (0)
#define ABB_CH0_RXA_Q_COEF2_ch0_rxa_q_c3_msb_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXB_I_COEF2_UNION
 �ṹ˵��  : CH0_RXB_I_COEF2 �Ĵ����ṹ���塣��ַƫ����:0x492����ֵ:0x01�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_i_c3_msb : 1;  /* bit[0]  : RXBͨ��I·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved         : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_I_COEF2_UNION;
#define ABB_CH0_RXB_I_COEF2_ch0_rxb_i_c3_msb_START  (0)
#define ABB_CH0_RXB_I_COEF2_ch0_rxb_i_c3_msb_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXB_Q_COEF2_UNION
 �ṹ˵��  : CH0_RXB_Q_COEF2 �Ĵ����ṹ���塣��ַƫ����:0x498����ֵ:0x01�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_q_c3_msb : 1;  /* bit[0]  : RXBͨ��I·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved         : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_Q_COEF2_UNION;
#define ABB_CH0_RXB_Q_COEF2_ch0_rxb_q_c3_msb_START  (0)
#define ABB_CH0_RXB_Q_COEF2_ch0_rxb_q_c3_msb_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_RXA_DCR_CFG_UNION
 �ṹ˵��  : CH0_REG_RXA_DCR_CFG �Ĵ����ṹ���塣��ַƫ����:0x49C����ֵ:0x46�����:8
 �Ĵ���˵��: RXAͨ��BLOCKING DCR���üĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : CH0_REG_RXB_DCR_CFG �Ĵ����ṹ���塣��ַƫ����:0x49D����ֵ:0x46�����:8
 �Ĵ���˵��: RXBͨ��BLOCKING DCR���üĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : CH0_REG_RX_DCR_CTRL �Ĵ����ṹ���塣��ַƫ����:0x49E����ֵ:0x00�����:8
 �Ĵ���˵��: BLOCKING DCR���ܿ��ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : CH0_RXA_BLOCKING �Ĵ����ṹ���塣��ַƫ����:0x49F����ֵ:0x00�����:8
 �Ĵ���˵��: RXAͨ��BLOCKING�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_blk_coeff : 5;  /* bit[0-4]: RXA����BLOCKING�ϱ�ֵ,2���ݴ�M */
        unsigned long  ch0_rxa_blk_power : 3;  /* bit[5-7]: RXA����BLOCKING�ϱ�ֵ��ϵ��N��BLOCKING�ϱ����ΪN*2^M */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXA_BLOCKING_UNION;
#define ABB_CH0_RXA_BLOCKING_ch0_rxa_blk_coeff_START  (0)
#define ABB_CH0_RXA_BLOCKING_ch0_rxa_blk_coeff_END    (4)
#define ABB_CH0_RXA_BLOCKING_ch0_rxa_blk_power_START  (5)
#define ABB_CH0_RXA_BLOCKING_ch0_rxa_blk_power_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXB_BLOCKING_UNION
 �ṹ˵��  : CH0_RXB_BLOCKING �Ĵ����ṹ���塣��ַƫ����:0x4A0����ֵ:0x00�����:8
 �Ĵ���˵��: RXBͨ��BLOCKING�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxb_blk_coeff : 5;  /* bit[0-4]: RXB����BLOCKING�ϱ�ֵ,2���ݴ�M */
        unsigned long  ch0_rxb_blk_power : 3;  /* bit[5-7]: RXB����BLOCKING�ϱ�ֵ��ϵ��N��BLOCKING�ϱ����ΪN*2^M */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXB_BLOCKING_UNION;
#define ABB_CH0_RXB_BLOCKING_ch0_rxb_blk_coeff_START  (0)
#define ABB_CH0_RXB_BLOCKING_ch0_rxb_blk_coeff_END    (4)
#define ABB_CH0_RXB_BLOCKING_ch0_rxb_blk_power_START  (5)
#define ABB_CH0_RXB_BLOCKING_ch0_rxb_blk_power_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_REG_RXA_DC_I_2_UNION
 �ṹ˵��  : CH0_REG_RXA_DC_I_2 �Ĵ����ṹ���塣��ַƫ����:0x4A2����ֵ:0x00�����:8
 �Ĵ���˵��: RXAͨ��I·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : CH0_REG_RXA_DC_Q_2 �Ĵ����ṹ���塣��ַƫ����:0x4A4����ֵ:0x00�����:8
 �Ĵ���˵��: RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : CH0_REG_RXB_DC_I_2 �Ĵ����ṹ���塣��ַƫ����:0x4A6����ֵ:0x00�����:8
 �Ĵ���˵��: RXBͨ��I·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : CH0_REG_RXB_DC_Q_2 �Ĵ����ṹ���塣��ַƫ����:0x4A8����ֵ:0x00�����:8
 �Ĵ���˵��: RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ��    : ABB_CH0_FLUSH_CFG1_UNION
 �ṹ˵��  : CH0_FLUSH_CFG1 �Ĵ����ṹ���塣��ַƫ����:0x4AA����ֵ:0x40�����:8
 �Ĵ���˵��: ͨ��0���üĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_flush_width_msb : 3;  /* bit[0-2]: ͨ��0 flush���[10:8]����λΪ19.2Mʱ�����ڡ� */
        unsigned long  ch0_flush_value     : 5;  /* bit[3-7]: ͨ��0 FLUSHֵ��Ĭ��Ϊ8�� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_FLUSH_CFG1_UNION;
#define ABB_CH0_FLUSH_CFG1_ch0_flush_width_msb_START  (0)
#define ABB_CH0_FLUSH_CFG1_ch0_flush_width_msb_END    (2)
#define ABB_CH0_FLUSH_CFG1_ch0_flush_value_START      (3)
#define ABB_CH0_FLUSH_CFG1_ch0_flush_value_END        (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXAI_HB_GAIN_2_UNION
 �ṹ˵��  : CH0_RXAI_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x4AC����ֵ:0x02�����:8
 �Ĵ���˵��: CH0ͨ��RXA HB�˲������档
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxai_hb_gain_h : 2;  /* bit[0-1]: CH0ͨ��RXA I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512�� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXAI_HB_GAIN_2_UNION;
#define ABB_CH0_RXAI_HB_GAIN_2_ch0_rxai_hb_gain_h_START  (0)
#define ABB_CH0_RXAI_HB_GAIN_2_ch0_rxai_hb_gain_h_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXAQ_HB_GAIN_2_UNION
 �ṹ˵��  : CH0_RXAQ_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x4AE����ֵ:0x02�����:8
 �Ĵ���˵��: CH0ͨ��RXA HB�˲������档
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxaq_hb_gain_h : 2;  /* bit[0-1]: CH0ͨ��RXA Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512�� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXAQ_HB_GAIN_2_UNION;
#define ABB_CH0_RXAQ_HB_GAIN_2_ch0_rxaq_hb_gain_h_START  (0)
#define ABB_CH0_RXAQ_HB_GAIN_2_ch0_rxaq_hb_gain_h_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXBI_HB_GAIN_2_UNION
 �ṹ˵��  : CH0_RXBI_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x4B0����ֵ:0x02�����:8
 �Ĵ���˵��: CH0ͨ��RXB HB�˲������档
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxbi_hb_gain_h : 2;  /* bit[0-1]: CH0ͨ��RXB I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512�� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXBI_HB_GAIN_2_UNION;
#define ABB_CH0_RXBI_HB_GAIN_2_ch0_rxbi_hb_gain_h_START  (0)
#define ABB_CH0_RXBI_HB_GAIN_2_ch0_rxbi_hb_gain_h_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RXBQ_HB_GAIN_2_UNION
 �ṹ˵��  : CH0_RXBQ_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x4B2����ֵ:0x02�����:8
 �Ĵ���˵��: CH0ͨ��RXB HB�˲������档
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxbq_hb_gain_h : 2;  /* bit[0-1]: CH0ͨ��RXB Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512�� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RXBQ_HB_GAIN_2_UNION;
#define ABB_CH0_RXBQ_HB_GAIN_2_ch0_rxbq_hb_gain_h_START  (0)
#define ABB_CH0_RXBQ_HB_GAIN_2_ch0_rxbq_hb_gain_h_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_CTRL_UNION
 �ṹ˵��  : CH0_CTRL �Ĵ����ṹ���塣��ַƫ����:0x4B3����ֵ:0x03�����:8
 �Ĵ���˵��: ͨ�����ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_loop_out : 1;  /* bit[0]  : CH0ͨ��RXA������������źţ�0�����ز�����źţ�1������ͬʱ����źţ� */
        unsigned long  ch0_rxb_loop_out : 1;  /* bit[1]  : CH0ͨ��RXB������������źţ�0�����ز�����źţ�1������ͬʱ����źţ� */
        unsigned long  reserved         : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_CTRL_UNION;
#define ABB_CH0_CTRL_ch0_rxa_loop_out_START  (0)
#define ABB_CH0_CTRL_ch0_rxa_loop_out_END    (0)
#define ABB_CH0_CTRL_ch0_rxb_loop_out_START  (1)
#define ABB_CH0_CTRL_ch0_rxb_loop_out_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RX_LINE_SEL_UNION
 �ṹ˵��  : CH0_RX_LINE_SEL �Ĵ����ṹ���塣��ַƫ����:0x4B4����ֵ:0x00�����:8
 �Ĵ���˵��: RX�߿�ǿ������ʹ�ܡ�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_en_sel : 1;  /* bit[0]: RXAͨ���߿�ѡ��ǿ��ʹ��
                                                       0��ѡ���߿�ʹ��
                                                       1��ѡ��ǿ��ʹ�� */
        unsigned long  ch0_rxb_en_sel : 1;  /* bit[1]: RXBͨ���߿�ѡ��ǿ��ʹ��
                                                       0��ѡ���߿�ʹ��
                                                       1��ѡ��ǿ��ʹ�� */
        unsigned long  reserved_0     : 1;  /* bit[2]: ���� */
        unsigned long  reserved_1     : 1;  /* bit[3]: ���� */
        unsigned long  ch0_rxa_en_cfg : 1;  /* bit[4]: RXAͨ��ǿ���߿� */
        unsigned long  ch0_rxb_en_cfg : 1;  /* bit[5]: RXBͨ��ǿ���߿� */
        unsigned long  reserved_2     : 1;  /* bit[6]: ���� */
        unsigned long  reserved_3     : 1;  /* bit[7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_LINE_SEL_UNION;
#define ABB_CH0_RX_LINE_SEL_ch0_rxa_en_sel_START  (0)
#define ABB_CH0_RX_LINE_SEL_ch0_rxa_en_sel_END    (0)
#define ABB_CH0_RX_LINE_SEL_ch0_rxb_en_sel_START  (1)
#define ABB_CH0_RX_LINE_SEL_ch0_rxb_en_sel_END    (1)
#define ABB_CH0_RX_LINE_SEL_ch0_rxa_en_cfg_START  (4)
#define ABB_CH0_RX_LINE_SEL_ch0_rxa_en_cfg_END    (4)
#define ABB_CH0_RX_LINE_SEL_ch0_rxb_en_cfg_START  (5)
#define ABB_CH0_RX_LINE_SEL_ch0_rxb_en_cfg_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RX_LINE_CFG_UNION
 �ṹ˵��  : CH0_RX_LINE_CFG �Ĵ����ṹ���塣��ַƫ����:0x4B5����ֵ:0x00�����:8
 �Ĵ���˵��: RXģʽ�߿�ǿ�����á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_line_ctrl_mode_cfg : 3;  /* bit[0-2]: �߿��ź�CH0_RX_LINE_CTRL_MODEǿ������ֵ
                                                                    0��IDLE
                                                                    1��Gģ
                                                                    2��Wģ
                                                                    3��LTEģ
                                                                    4��TDSģ
                                                                    5��Xģ */
        unsigned long  ch0_rx_line_ctrl_mode_sel : 1;  /* bit[3]  : �߿��ź�CH0_RX_LINE_CTRL_MODEǿ������ʹ�� */
        unsigned long  reserved                  : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_LINE_CFG_UNION;
#define ABB_CH0_RX_LINE_CFG_ch0_rx_line_ctrl_mode_cfg_START  (0)
#define ABB_CH0_RX_LINE_CFG_ch0_rx_line_ctrl_mode_cfg_END    (2)
#define ABB_CH0_RX_LINE_CFG_ch0_rx_line_ctrl_mode_sel_START  (3)
#define ABB_CH0_RX_LINE_CFG_ch0_rx_line_ctrl_mode_sel_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CH0_BLK_CFG_UNION
 �ṹ˵��  : CH0_BLK_CFG �Ĵ����ṹ���塣��ַƫ����:0x4B6����ֵ:0x00�����:8
 �Ĵ���˵��: blk���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0     : 1;  /* bit[0]  : ���� */
        unsigned long  ch0_blk_en_cfg : 1;  /* bit[1]  : �߿��ź�CH0_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ֵ */
        unsigned long  ch0_blk_en_sel : 1;  /* bit[2]  : �߿��ź�CH0_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ʹ�� */
        unsigned long  reserved_1     : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_BLK_CFG_UNION;
#define ABB_CH0_BLK_CFG_ch0_blk_en_cfg_START  (1)
#define ABB_CH0_BLK_CFG_ch0_blk_en_cfg_END    (1)
#define ABB_CH0_BLK_CFG_ch0_blk_en_sel_START  (2)
#define ABB_CH0_BLK_CFG_ch0_blk_en_sel_END    (2)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RX_LINE_RPT0_UNION
 �ṹ˵��  : CH0_RX_LINE_RPT0 �Ĵ����ṹ���塣��ַƫ����:0x4B7����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_en_rpt : 1;  /* bit[0]  : CH0_RXA_EN�߿�״̬�ϱ� */
        unsigned long  ch0_rxb_en_rpt : 1;  /* bit[1]  : CH0_RXB_EN�߿�״̬�ϱ� */
        unsigned long  reserved       : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_LINE_RPT0_UNION;
#define ABB_CH0_RX_LINE_RPT0_ch0_rxa_en_rpt_START  (0)
#define ABB_CH0_RX_LINE_RPT0_ch0_rxa_en_rpt_END    (0)
#define ABB_CH0_RX_LINE_RPT0_ch0_rxb_en_rpt_START  (1)
#define ABB_CH0_RX_LINE_RPT0_ch0_rxb_en_rpt_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RX_LINE_RPT1_UNION
 �ṹ˵��  : CH0_RX_LINE_RPT1 �Ĵ����ṹ���塣��ַƫ����:0x4B8����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved                  : 3;  /* bit[0-2]: ���� */
        unsigned long  ch0_rx_line_ctrl_mode_rpt : 3;  /* bit[3-5]: CH0 RX_LINE_CTRL_MODE״̬�ϱ���
                                                                    0��IDLE
                                                                    1��Gģ
                                                                    2��Wģ
                                                                    3��LTEģ
                                                                    4��TDSģ
                                                                    5��Xģ
                                                                    others��IDLE */
        unsigned long  ch0_rxa_blk_en_rpt        : 1;  /* bit[6]  : CH0_RXA_BLK_EN�߿�״̬�ϱ� */
        unsigned long  ch0_rxb_blk_en_rpt        : 1;  /* bit[7]  : CH0_RXB_BLK_EN�߿�״̬�ϱ� */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_LINE_RPT1_UNION;
#define ABB_CH0_RX_LINE_RPT1_ch0_rx_line_ctrl_mode_rpt_START  (3)
#define ABB_CH0_RX_LINE_RPT1_ch0_rx_line_ctrl_mode_rpt_END    (5)
#define ABB_CH0_RX_LINE_RPT1_ch0_rxa_blk_en_rpt_START         (6)
#define ABB_CH0_RX_LINE_RPT1_ch0_rxa_blk_en_rpt_END           (6)
#define ABB_CH0_RX_LINE_RPT1_ch0_rxb_blk_en_rpt_START         (7)
#define ABB_CH0_RX_LINE_RPT1_ch0_rxb_blk_en_rpt_END           (7)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RX_REG_DEBUG_DIG_UNION
 �ṹ˵��  : CH0_RX_REG_DEBUG_DIG �Ĵ����ṹ���塣��ַƫ����:0x4B9����ֵ:0x00�����:8
 �Ĵ���˵��: ���ֵ��ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_div_en_bp      : 1;  /* bit[0]  : RX��Ƶ��ʹ��bypass����
                                                                0����bypass
                                                                1��bypass */
        unsigned long  reserved              : 3;  /* bit[1-3]: ���� */
        unsigned long  ch0_rx_sw_rst_num_cfg : 3;  /* bit[4-6]: ģʽ�л���λ��������ֵ����λΪ8 cycles */
        unsigned long  ch0_rx_sw_rst_num_sel : 1;  /* bit[7]  : bit[7]��ģʽ�л���λ��������ʹ��
                                                                0����ʹ��
                                                                1��ʹ�� */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_REG_DEBUG_DIG_UNION;
#define ABB_CH0_RX_REG_DEBUG_DIG_ch0_rx_div_en_bp_START       (0)
#define ABB_CH0_RX_REG_DEBUG_DIG_ch0_rx_div_en_bp_END         (0)
#define ABB_CH0_RX_REG_DEBUG_DIG_ch0_rx_sw_rst_num_cfg_START  (4)
#define ABB_CH0_RX_REG_DEBUG_DIG_ch0_rx_sw_rst_num_cfg_END    (6)
#define ABB_CH0_RX_REG_DEBUG_DIG_ch0_rx_sw_rst_num_sel_START  (7)
#define ABB_CH0_RX_REG_DEBUG_DIG_ch0_rx_sw_rst_num_sel_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RX_TESTMODE_UNION
 �ṹ˵��  : CH1_RX_TESTMODE �Ĵ����ṹ���塣��ַƫ����:0x4C0����ֵ:0x04�����:8
 �Ĵ���˵��: ����ģʽ�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rx_sw_rst   : 1;  /* bit[0]  : ���ֲ���RXͨ����λ�źţ�
                                                          0������λ(Ĭ��)
                                                          1����λ */
        unsigned long  ch1_cic_gate_en : 1;  /* bit[1]  :  */
        unsigned long  ch1_rx_loop_sel : 2;  /* bit[2-3]: ���� */
        unsigned long  ch1_out_sel     : 2;  /* bit[4-5]:  */
        unsigned long  reserved        : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_TESTMODE_UNION;
#define ABB_CH1_RX_TESTMODE_ch1_rx_sw_rst_START    (0)
#define ABB_CH1_RX_TESTMODE_ch1_rx_sw_rst_END      (0)
#define ABB_CH1_RX_TESTMODE_ch1_cic_gate_en_START  (1)
#define ABB_CH1_RX_TESTMODE_ch1_cic_gate_en_END    (1)
#define ABB_CH1_RX_TESTMODE_ch1_rx_loop_sel_START  (2)
#define ABB_CH1_RX_TESTMODE_ch1_rx_loop_sel_END    (3)
#define ABB_CH1_RX_TESTMODE_ch1_out_sel_START      (4)
#define ABB_CH1_RX_TESTMODE_ch1_out_sel_END        (5)


/*****************************************************************************
 �ṹ��    : ABB_CH1_PLL_SEL_UNION
 �ṹ˵��  : CH1_PLL_SEL �Ĵ����ṹ���塣��ַƫ����:0x4C1����ֵ:0x00�����:8
 �Ĵ���˵��: PLLѡ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_g_pll_sel   : 2;  /* bit[0-1]: GģPLLѡ��
                                                          0��ѡ��GPLL
                                                          1��ѡ��SCPLL0
                                                          2��ѡ��SCPLL1 */
        unsigned long  ch1_wtl_pll_sel : 1;  /* bit[2]  : WTLģPLLѡ��
                                                          0��ѡ��SCPLL0
                                                          1��ѡ��SCPLL1 */
        unsigned long  ch1_c1_pll_sel  : 1;  /* bit[3]  : C1ģPLLѡ��
                                                          0��ѡ��SCPLL1
                                                          1��ѡ��SCPLL0 */
        unsigned long  reserved        : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_PLL_SEL_UNION;
#define ABB_CH1_PLL_SEL_ch1_g_pll_sel_START    (0)
#define ABB_CH1_PLL_SEL_ch1_g_pll_sel_END      (1)
#define ABB_CH1_PLL_SEL_ch1_wtl_pll_sel_START  (2)
#define ABB_CH1_PLL_SEL_ch1_wtl_pll_sel_END    (2)
#define ABB_CH1_PLL_SEL_ch1_c1_pll_sel_START   (3)
#define ABB_CH1_PLL_SEL_ch1_c1_pll_sel_END     (3)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXA_I_COEF2_UNION
 �ṹ˵��  : CH1_RXA_I_COEF2 �Ĵ����ṹ���塣��ַƫ����:0x4C6����ֵ:0x01�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_i_c3_msb : 1;  /* bit[0]  : RXAͨ��I·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved         : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXA_I_COEF2_UNION;
#define ABB_CH1_RXA_I_COEF2_ch1_rxa_i_c3_msb_START  (0)
#define ABB_CH1_RXA_I_COEF2_ch1_rxa_i_c3_msb_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXA_Q_COEF2_UNION
 �ṹ˵��  : CH1_RXA_Q_COEF2 �Ĵ����ṹ���塣��ַƫ����:0x4CC����ֵ:0x01�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_q_c3_msb : 1;  /* bit[0]  : RXAͨ��I·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved         : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXA_Q_COEF2_UNION;
#define ABB_CH1_RXA_Q_COEF2_ch1_rxa_q_c3_msb_START  (0)
#define ABB_CH1_RXA_Q_COEF2_ch1_rxa_q_c3_msb_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXB_I_COEF2_UNION
 �ṹ˵��  : CH1_RXB_I_COEF2 �Ĵ����ṹ���塣��ַƫ����:0x4D2����ֵ:0x01�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxb_i_c3_msb : 1;  /* bit[0]  : RXBͨ��I·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved         : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXB_I_COEF2_UNION;
#define ABB_CH1_RXB_I_COEF2_ch1_rxb_i_c3_msb_START  (0)
#define ABB_CH1_RXB_I_COEF2_ch1_rxb_i_c3_msb_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXB_Q_COEF2_UNION
 �ṹ˵��  : CH1_RXB_Q_COEF2 �Ĵ����ṹ���塣��ַƫ����:0x4D8����ֵ:0x01�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxb_q_c3_msb : 1;  /* bit[0]  : RXBͨ��I·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved         : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXB_Q_COEF2_UNION;
#define ABB_CH1_RXB_Q_COEF2_ch1_rxb_q_c3_msb_START  (0)
#define ABB_CH1_RXB_Q_COEF2_ch1_rxb_q_c3_msb_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_RXA_DCR_CFG_UNION
 �ṹ˵��  : CH1_REG_RXA_DCR_CFG �Ĵ����ṹ���塣��ַƫ����:0x4DC����ֵ:0x46�����:8
 �Ĵ���˵��: RXAͨ��BLOCKING DCR���üĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : CH1_REG_RXB_DCR_CFG �Ĵ����ṹ���塣��ַƫ����:0x4DD����ֵ:0x46�����:8
 �Ĵ���˵��: RXBͨ��BLOCKING DCR���üĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : CH1_REG_RX_DCR_CTRL �Ĵ����ṹ���塣��ַƫ����:0x4DE����ֵ:0x00�����:8
 �Ĵ���˵��: BLOCKING DCR���ܿ��ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : CH1_RXA_BLOCKING �Ĵ����ṹ���塣��ַƫ����:0x4DF����ֵ:0x00�����:8
 �Ĵ���˵��: RXAͨ��BLOCKING�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_blk_coeff : 5;  /* bit[0-4]: RXA����BLOCKING�ϱ�ֵ,2���ݴ�M */
        unsigned long  ch1_rxa_blk_power : 3;  /* bit[5-7]: RXA����BLOCKING�ϱ�ֵ��ϵ��N��BLOCKING�ϱ����ΪN*2^M */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXA_BLOCKING_UNION;
#define ABB_CH1_RXA_BLOCKING_ch1_rxa_blk_coeff_START  (0)
#define ABB_CH1_RXA_BLOCKING_ch1_rxa_blk_coeff_END    (4)
#define ABB_CH1_RXA_BLOCKING_ch1_rxa_blk_power_START  (5)
#define ABB_CH1_RXA_BLOCKING_ch1_rxa_blk_power_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXB_BLOCKING_UNION
 �ṹ˵��  : CH1_RXB_BLOCKING �Ĵ����ṹ���塣��ַƫ����:0x4E0����ֵ:0x00�����:8
 �Ĵ���˵��: RXBͨ��BLOCKING�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxb_blk_coeff : 5;  /* bit[0-4]: RXB����BLOCKING�ϱ�ֵ,2���ݴ�M */
        unsigned long  ch1_rxb_blk_power : 3;  /* bit[5-7]: RXB����BLOCKING�ϱ�ֵ��ϵ��N��BLOCKING�ϱ����ΪN*2^M */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXB_BLOCKING_UNION;
#define ABB_CH1_RXB_BLOCKING_ch1_rxb_blk_coeff_START  (0)
#define ABB_CH1_RXB_BLOCKING_ch1_rxb_blk_coeff_END    (4)
#define ABB_CH1_RXB_BLOCKING_ch1_rxb_blk_power_START  (5)
#define ABB_CH1_RXB_BLOCKING_ch1_rxb_blk_power_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_REG_RXA_DC_I_2_UNION
 �ṹ˵��  : CH1_REG_RXA_DC_I_2 �Ĵ����ṹ���塣��ַƫ����:0x4E2����ֵ:0x00�����:8
 �Ĵ���˵��: RXAͨ��I·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : CH1_REG_RXA_DC_Q_2 �Ĵ����ṹ���塣��ַƫ����:0x4E4����ֵ:0x00�����:8
 �Ĵ���˵��: RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : CH1_REG_RXB_DC_I_2 �Ĵ����ṹ���塣��ַƫ����:0x4E6����ֵ:0x00�����:8
 �Ĵ���˵��: RXBͨ��I·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : CH1_REG_RXB_DC_Q_2 �Ĵ����ṹ���塣��ַƫ����:0x4E8����ֵ:0x00�����:8
 �Ĵ���˵��: RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ��    : ABB_CH1_FLUSH_CFG1_UNION
 �ṹ˵��  : CH1_FLUSH_CFG1 �Ĵ����ṹ���塣��ַƫ����:0x4EA����ֵ:0x40�����:8
 �Ĵ���˵��: ͨ��1���üĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_flush_width_msb : 3;  /* bit[0-2]: ͨ��1 flush���[10:8]����λΪ19.2Mʱ�����ڡ� */
        unsigned long  ch1_flush_value     : 5;  /* bit[3-7]: ͨ��1 FLUSHֵ��Ĭ��Ϊ8�� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_FLUSH_CFG1_UNION;
#define ABB_CH1_FLUSH_CFG1_ch1_flush_width_msb_START  (0)
#define ABB_CH1_FLUSH_CFG1_ch1_flush_width_msb_END    (2)
#define ABB_CH1_FLUSH_CFG1_ch1_flush_value_START      (3)
#define ABB_CH1_FLUSH_CFG1_ch1_flush_value_END        (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXAI_HB_GAIN_2_UNION
 �ṹ˵��  : CH1_RXAI_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x4EC����ֵ:0x02�����:8
 �Ĵ���˵��: CH1ͨ��RXA HB�˲������档
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxai_hb_gain_h : 2;  /* bit[0-1]: CH1ͨ��RXA I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512�� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXAI_HB_GAIN_2_UNION;
#define ABB_CH1_RXAI_HB_GAIN_2_ch1_rxai_hb_gain_h_START  (0)
#define ABB_CH1_RXAI_HB_GAIN_2_ch1_rxai_hb_gain_h_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXAQ_HB_GAIN_2_UNION
 �ṹ˵��  : CH1_RXAQ_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x4EE����ֵ:0x02�����:8
 �Ĵ���˵��: CH1ͨ��RXA HB�˲������档
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxaq_hb_gain_h : 2;  /* bit[0-1]: CH1ͨ��RXA Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512�� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXAQ_HB_GAIN_2_UNION;
#define ABB_CH1_RXAQ_HB_GAIN_2_ch1_rxaq_hb_gain_h_START  (0)
#define ABB_CH1_RXAQ_HB_GAIN_2_ch1_rxaq_hb_gain_h_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXBI_HB_GAIN_2_UNION
 �ṹ˵��  : CH1_RXBI_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x4F0����ֵ:0x02�����:8
 �Ĵ���˵��: CH1ͨ��RXB HB�˲������档
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxbi_hb_gain_h : 2;  /* bit[0-1]: CH1ͨ��RXB I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512�� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXBI_HB_GAIN_2_UNION;
#define ABB_CH1_RXBI_HB_GAIN_2_ch1_rxbi_hb_gain_h_START  (0)
#define ABB_CH1_RXBI_HB_GAIN_2_ch1_rxbi_hb_gain_h_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RXBQ_HB_GAIN_2_UNION
 �ṹ˵��  : CH1_RXBQ_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x4F2����ֵ:0x02�����:8
 �Ĵ���˵��: CH1ͨ��RXB HB�˲������档
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxbq_hb_gain_h : 2;  /* bit[0-1]: CH1ͨ��RXB Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512�� */
        unsigned long  reserved           : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RXBQ_HB_GAIN_2_UNION;
#define ABB_CH1_RXBQ_HB_GAIN_2_ch1_rxbq_hb_gain_h_START  (0)
#define ABB_CH1_RXBQ_HB_GAIN_2_ch1_rxbq_hb_gain_h_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH1_CTRL_UNION
 �ṹ˵��  : CH1_CTRL �Ĵ����ṹ���塣��ַƫ����:0x4F3����ֵ:0x03�����:8
 �Ĵ���˵��: ͨ�����ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_loop_out : 1;  /* bit[0]  : CH1ͨ��RXA������������źţ�0�����ز�����źţ�1������ͬʱ����źţ� */
        unsigned long  ch1_rxb_loop_out : 1;  /* bit[1]  : CH1ͨ��RXB������������źţ�0�����ز�����źţ�1������ͬʱ����źţ� */
        unsigned long  reserved         : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_CTRL_UNION;
#define ABB_CH1_CTRL_ch1_rxa_loop_out_START  (0)
#define ABB_CH1_CTRL_ch1_rxa_loop_out_END    (0)
#define ABB_CH1_CTRL_ch1_rxb_loop_out_START  (1)
#define ABB_CH1_CTRL_ch1_rxb_loop_out_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RX_LINE_SEL_UNION
 �ṹ˵��  : CH1_RX_LINE_SEL �Ĵ����ṹ���塣��ַƫ����:0x4F4����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�ǿ������ʹ�ܡ�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_en_sel : 1;  /* bit[0]  : RXAͨ���߿�ѡ��ǿ��ʹ��
                                                         0��ѡ���߿�ʹ��
                                                         1��ѡ��ǿ��ʹ�� */
        unsigned long  ch1_rxb_en_sel : 1;  /* bit[1]  : RXBͨ���߿�ѡ��ǿ��ʹ��
                                                         0��ѡ���߿�ʹ��
                                                         1��ѡ��ǿ��ʹ�� */
        unsigned long  reserved_0     : 2;  /* bit[2-3]: ���� */
        unsigned long  ch1_rxa_en_cfg : 1;  /* bit[4]  : RXAͨ��ǿ���߿� */
        unsigned long  ch1_rxb_en_cfg : 1;  /* bit[5]  : RXBͨ��ǿ���߿� */
        unsigned long  reserved_1     : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_LINE_SEL_UNION;
#define ABB_CH1_RX_LINE_SEL_ch1_rxa_en_sel_START  (0)
#define ABB_CH1_RX_LINE_SEL_ch1_rxa_en_sel_END    (0)
#define ABB_CH1_RX_LINE_SEL_ch1_rxb_en_sel_START  (1)
#define ABB_CH1_RX_LINE_SEL_ch1_rxb_en_sel_END    (1)
#define ABB_CH1_RX_LINE_SEL_ch1_rxa_en_cfg_START  (4)
#define ABB_CH1_RX_LINE_SEL_ch1_rxa_en_cfg_END    (4)
#define ABB_CH1_RX_LINE_SEL_ch1_rxb_en_cfg_START  (5)
#define ABB_CH1_RX_LINE_SEL_ch1_rxb_en_cfg_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RX_LINE_CFG_UNION
 �ṹ˵��  : CH1_RX_LINE_CFG �Ĵ����ṹ���塣��ַƫ����:0x4F5����ֵ:0x00�����:8
 �Ĵ���˵��: ģʽ�߿�ǿ�����á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rx_line_ctrl_mode_cfg : 3;  /* bit[0-2]: �߿��ź�CH1_RX_LINE_CTRL_MODEǿ������ֵ
                                                                    0��IDLE
                                                                    1��Gģ
                                                                    2��Wģ
                                                                    3��LTEģ
                                                                    4��TDSģ
                                                                    5��Xģ */
        unsigned long  ch1_rx_line_ctrl_mode_sel : 1;  /* bit[3]  : �߿��ź�CH1_RX_LINE_CTRL_MODEǿ������ʹ�� */
        unsigned long  reserved                  : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_LINE_CFG_UNION;
#define ABB_CH1_RX_LINE_CFG_ch1_rx_line_ctrl_mode_cfg_START  (0)
#define ABB_CH1_RX_LINE_CFG_ch1_rx_line_ctrl_mode_cfg_END    (2)
#define ABB_CH1_RX_LINE_CFG_ch1_rx_line_ctrl_mode_sel_START  (3)
#define ABB_CH1_RX_LINE_CFG_ch1_rx_line_ctrl_mode_sel_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_CH1_BLK_CFG_UNION
 �ṹ˵��  : CH1_BLK_CFG �Ĵ����ṹ���塣��ַƫ����:0x4F6����ֵ:0x00�����:8
 �Ĵ���˵��: blk���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0     : 1;  /* bit[0]  : ���� */
        unsigned long  ch1_blk_en_cfg : 1;  /* bit[1]  : �߿��ź�CH1_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ֵ */
        unsigned long  ch1_blk_en_sel : 1;  /* bit[2]  : �߿��ź�CH1_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ʹ�� */
        unsigned long  reserved_1     : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_BLK_CFG_UNION;
#define ABB_CH1_BLK_CFG_ch1_blk_en_cfg_START  (1)
#define ABB_CH1_BLK_CFG_ch1_blk_en_cfg_END    (1)
#define ABB_CH1_BLK_CFG_ch1_blk_en_sel_START  (2)
#define ABB_CH1_BLK_CFG_ch1_blk_en_sel_END    (2)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RX_LINE_RPT0_UNION
 �ṹ˵��  : CH1_RX_LINE_RPT0 �Ĵ����ṹ���塣��ַƫ����:0x4F7����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_en_rpt : 1;  /* bit[0]  : CH1_RXA_EN�߿�״̬�ϱ� */
        unsigned long  ch1_rxb_en_rpt : 1;  /* bit[1]  : CH1_RXB_EN�߿�״̬�ϱ� */
        unsigned long  reserved       : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_LINE_RPT0_UNION;
#define ABB_CH1_RX_LINE_RPT0_ch1_rxa_en_rpt_START  (0)
#define ABB_CH1_RX_LINE_RPT0_ch1_rxa_en_rpt_END    (0)
#define ABB_CH1_RX_LINE_RPT0_ch1_rxb_en_rpt_START  (1)
#define ABB_CH1_RX_LINE_RPT0_ch1_rxb_en_rpt_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RX_LINE_RPT1_UNION
 �ṹ˵��  : CH1_RX_LINE_RPT1 �Ĵ����ṹ���塣��ַƫ����:0x4F8����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved                  : 3;  /* bit[0-2]: ���� */
        unsigned long  ch1_rx_line_ctrl_mode_rpt : 3;  /* bit[3-5]: CH1 RX_LINE_CTRL_MODE״̬�ϱ���
                                                                    0��IDLE
                                                                    1��Gģ
                                                                    2��Wģ
                                                                    3��LTEģ
                                                                    4��TDSģ
                                                                    5��Xģ
                                                                    others��IDLE */
        unsigned long  ch1_rxa_blk_en_rpt        : 1;  /* bit[6]  : CH1_RXA_BLK_EN�߿�״̬�ϱ� */
        unsigned long  ch1_rxb_blk_en_rpt        : 1;  /* bit[7]  : CH1_RXB_BLK_EN�߿�״̬�ϱ� */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_LINE_RPT1_UNION;
#define ABB_CH1_RX_LINE_RPT1_ch1_rx_line_ctrl_mode_rpt_START  (3)
#define ABB_CH1_RX_LINE_RPT1_ch1_rx_line_ctrl_mode_rpt_END    (5)
#define ABB_CH1_RX_LINE_RPT1_ch1_rxa_blk_en_rpt_START         (6)
#define ABB_CH1_RX_LINE_RPT1_ch1_rxa_blk_en_rpt_END           (6)
#define ABB_CH1_RX_LINE_RPT1_ch1_rxb_blk_en_rpt_START         (7)
#define ABB_CH1_RX_LINE_RPT1_ch1_rxb_blk_en_rpt_END           (7)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RX_REG_DEBUG_DIG_UNION
 �ṹ˵��  : CH1_RX_REG_DEBUG_DIG �Ĵ����ṹ���塣��ַƫ����:0x4F9����ֵ:0x00�����:8
 �Ĵ���˵��: ���ֵ��ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rx_div_en_bp      : 1;  /* bit[0]  : RX��Ƶ��ʹ��bypass����
                                                                0����bypass
                                                                1��bypass */
        unsigned long  reserved              : 3;  /* bit[1-3]: ���� */
        unsigned long  ch1_rx_sw_rst_num_cfg : 3;  /* bit[4-6]: ģʽ�л���λ��������ֵ����λΪ8 cycles */
        unsigned long  ch1_rx_sw_rst_num_sel : 1;  /* bit[7]  : bit[7]��ģʽ�л���λ��������ʹ��
                                                                0����ʹ��
                                                                1��ʹ�� */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_REG_DEBUG_DIG_UNION;
#define ABB_CH1_RX_REG_DEBUG_DIG_ch1_rx_div_en_bp_START       (0)
#define ABB_CH1_RX_REG_DEBUG_DIG_ch1_rx_div_en_bp_END         (0)
#define ABB_CH1_RX_REG_DEBUG_DIG_ch1_rx_sw_rst_num_cfg_START  (4)
#define ABB_CH1_RX_REG_DEBUG_DIG_ch1_rx_sw_rst_num_cfg_END    (6)
#define ABB_CH1_RX_REG_DEBUG_DIG_ch1_rx_sw_rst_num_sel_START  (7)
#define ABB_CH1_RX_REG_DEBUG_DIG_ch1_rx_sw_rst_num_sel_END    (7)


/***======================================================================***
                     (4/4) register_define_abb_ana
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : ABB_SCPLL0_LOCK_CTRL_UNION
 �ṹ˵��  : SCPLL0_LOCK_CTRL �Ĵ����ṹ���塣��ַƫ����:0x800����ֵ:0x18�����:8
 �Ĵ���˵��: SC_PLL�������ƼĴ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll0_en      : 1;  /* bit[0]  : SCPLL0ʹ���źš�����ͨ��CFG�ӿ����ô�scpll0�� */
        unsigned long  scpll0_time    : 3;  /* bit[1-3]: SCPLL0ʱ���ȶ��ȴ�ʱ�����ã�����ʱ��Ϊ19.2M��
                                                         000��SCPLL0����10us��ʱ���ȶ���
                                                         001��SCPLL0����20us��ʱ���ȶ���
                                                         010��SCPLL0����50us��ʱ���ȶ���
                                                         011��SCPLL0����75us��ʱ���ȶ���
                                                         100��SCPLL0����100us��ʱ���ȶ���
                                                         101��SCPLL0����115us��ʱ���ȶ���
                                                         110��SCPLL0����125us��ʱ���ȶ���
                                                         default��100us */
        unsigned long  scpll0_gate_en : 1;  /* bit[4]  : SCPLL0�ſ�ʹ���źš� */
        unsigned long  scpll0_timeout : 1;  /* bit[5]  : SCPLL0�ȶ�ָʾ��0��ʾSCPLL0δ�ȶ���1��ʾSCPLL0�ȶ���SCPLL0�ȶ�����ʱ������� */
        unsigned long  scpll0_lock    : 1;  /* bit[6]  : SCPLL0����ָʾ�� */
        unsigned long  reserved       : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL0_LOCK_CTRL_UNION;
#define ABB_SCPLL0_LOCK_CTRL_scpll0_en_START       (0)
#define ABB_SCPLL0_LOCK_CTRL_scpll0_en_END         (0)
#define ABB_SCPLL0_LOCK_CTRL_scpll0_time_START     (1)
#define ABB_SCPLL0_LOCK_CTRL_scpll0_time_END       (3)
#define ABB_SCPLL0_LOCK_CTRL_scpll0_gate_en_START  (4)
#define ABB_SCPLL0_LOCK_CTRL_scpll0_gate_en_END    (4)
#define ABB_SCPLL0_LOCK_CTRL_scpll0_timeout_START  (5)
#define ABB_SCPLL0_LOCK_CTRL_scpll0_timeout_END    (5)
#define ABB_SCPLL0_LOCK_CTRL_scpll0_lock_START     (6)
#define ABB_SCPLL0_LOCK_CTRL_scpll0_lock_END       (6)


/*****************************************************************************
 �ṹ��    : ABB_SCPLL0_FBDIV_H_UNION
 �ṹ˵��  : SCPLL0_FBDIV_H �Ĵ����ṹ���塣��ַƫ����:0x803����ֵ:0x00�����:8
 �Ĵ���˵��: SC_PLL��Ƶ���������üĴ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll0_fbdiv_h : 4;  /* bit[0-3]: PLL������Ƶ����fbdiv[11:0]�ĸ�4bit�� */
        unsigned long  reserved       : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL0_FBDIV_H_UNION;
#define ABB_SCPLL0_FBDIV_H_scpll0_fbdiv_h_START  (0)
#define ABB_SCPLL0_FBDIV_H_scpll0_fbdiv_h_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_SCPLL0_REFDIV_UNION
 �ṹ˵��  : SCPLL0_REFDIV �Ĵ����ṹ���塣��ַƫ����:0x804����ֵ:0x01�����:8
 �Ĵ���˵��: SC_PLL��Ƶ���������üĴ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll0_refdiv : 6;  /* bit[0-5]: PLL�ο���Ƶ����refdiv[5:0]��Ĭ��ֵΪ1�� */
        unsigned long  reserved      : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL0_REFDIV_UNION;
#define ABB_SCPLL0_REFDIV_scpll0_refdiv_START  (0)
#define ABB_SCPLL0_REFDIV_scpll0_refdiv_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_SCPLL0_CFG_UPDATE_UNION
 �ṹ˵��  : SCPLL0_CFG_UPDATE �Ĵ����ṹ���塣��ַƫ����:0x809����ֵ:0x00�����:8
 �Ĵ���˵��: SC_PLL�������ƼĴ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll0_cfg_update : 1;  /* bit[0]  : SCPLL0�������ø���ָʾ��
                                                            scpll0_en�򿪺����������scpll0_postdiv��scpll0_fbdiv��scpll0_frac������������scpll0_sfg_update������ͬʱ���£�scpll0_en����ʱ�����ò����������£�����Ҫ����scpll0_sfg_update�� */
        unsigned long  reserved          : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL0_CFG_UPDATE_UNION;
#define ABB_SCPLL0_CFG_UPDATE_scpll0_cfg_update_START  (0)
#define ABB_SCPLL0_CFG_UPDATE_scpll0_cfg_update_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_SCPLL1_LOCK_CTRL_UNION
 �ṹ˵��  : SCPLL1_LOCK_CTRL �Ĵ����ṹ���塣��ַƫ����:0x80A����ֵ:0x18�����:8
 �Ĵ���˵��: SC_PLL�������ƼĴ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll1_en      : 1;  /* bit[0]  : SCPLL1ʹ���źš�����ͨ��CFG�ӿ����ô�scpll1�� */
        unsigned long  scpll1_time    : 3;  /* bit[1-3]: SCPLL1ʱ���ȶ��ȴ�ʱ�����ã�����ʱ��Ϊ19.2M��
                                                         000��SCPLL1����10us��ʱ���ȶ���
                                                         001��SCPLL1����20us��ʱ���ȶ���
                                                         010��SCPLL1����50us��ʱ���ȶ���
                                                         011��SCPLL1����75us��ʱ���ȶ���
                                                         100��SCPLL1����100us��ʱ���ȶ���
                                                         101��SCPLL1����115us��ʱ���ȶ���
                                                         110��SCPLL1����125us��ʱ���ȶ���
                                                         default��100us */
        unsigned long  scpll1_gate_en : 1;  /* bit[4]  : SCPLL1�ſ�ʹ���źš� */
        unsigned long  scpll1_timeout : 1;  /* bit[5]  : SCPLL1�ȶ�ָʾ��0��ʾSCPLL1δ�ȶ���1��ʾSCPLL1�ȶ���SCPLL1�ȶ�����ʱ������� */
        unsigned long  scpll1_lock    : 1;  /* bit[6]  : SCPLL1����ָʾ�� */
        unsigned long  reserved       : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL1_LOCK_CTRL_UNION;
#define ABB_SCPLL1_LOCK_CTRL_scpll1_en_START       (0)
#define ABB_SCPLL1_LOCK_CTRL_scpll1_en_END         (0)
#define ABB_SCPLL1_LOCK_CTRL_scpll1_time_START     (1)
#define ABB_SCPLL1_LOCK_CTRL_scpll1_time_END       (3)
#define ABB_SCPLL1_LOCK_CTRL_scpll1_gate_en_START  (4)
#define ABB_SCPLL1_LOCK_CTRL_scpll1_gate_en_END    (4)
#define ABB_SCPLL1_LOCK_CTRL_scpll1_timeout_START  (5)
#define ABB_SCPLL1_LOCK_CTRL_scpll1_timeout_END    (5)
#define ABB_SCPLL1_LOCK_CTRL_scpll1_lock_START     (6)
#define ABB_SCPLL1_LOCK_CTRL_scpll1_lock_END       (6)


/*****************************************************************************
 �ṹ��    : ABB_SCPLL1_FBDIV_H_UNION
 �ṹ˵��  : SCPLL1_FBDIV_H �Ĵ����ṹ���塣��ַƫ����:0x80D����ֵ:0x00�����:8
 �Ĵ���˵��: SC_PLL��Ƶ���������üĴ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll1_fbdiv_h : 4;  /* bit[0-3]: PLL������Ƶ����fbdiv[11:0]�ĸ�4bit�� */
        unsigned long  reserved       : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL1_FBDIV_H_UNION;
#define ABB_SCPLL1_FBDIV_H_scpll1_fbdiv_h_START  (0)
#define ABB_SCPLL1_FBDIV_H_scpll1_fbdiv_h_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_SCPLL1_REFDIV_UNION
 �ṹ˵��  : SCPLL1_REFDIV �Ĵ����ṹ���塣��ַƫ����:0x80E����ֵ:0x01�����:8
 �Ĵ���˵��: SC_PLL��Ƶ���������üĴ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll1_refdiv : 6;  /* bit[0-5]: PLL�ο���Ƶ����refdiv[5:0]��Ĭ��ֵΪ1�� */
        unsigned long  reserved      : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL1_REFDIV_UNION;
#define ABB_SCPLL1_REFDIV_scpll1_refdiv_START  (0)
#define ABB_SCPLL1_REFDIV_scpll1_refdiv_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_SCPLL1_CFG_UPDATE_UNION
 �ṹ˵��  : SCPLL1_CFG_UPDATE �Ĵ����ṹ���塣��ַƫ����:0x813����ֵ:0x00�����:8
 �Ĵ���˵��: SC_PLL�������ƼĴ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  scpll1_cfg_update : 1;  /* bit[0]  : SCPLL1�������ø���ָʾ��
                                                            scpll1_en�򿪺����������scpll1_postdiv��scpll1_fbdiv��scpll1_frac������������scpll1_sfg_update������ͬʱ���£�scpll1_en����ʱ�����ò����������£�����Ҫ����scpll1_sfg_update�� */
        unsigned long  reserved          : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_SCPLL1_CFG_UPDATE_UNION;
#define ABB_SCPLL1_CFG_UPDATE_scpll1_cfg_update_START  (0)
#define ABB_SCPLL1_CFG_UPDATE_scpll1_cfg_update_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_GPLL0_GATE_TIME_UNION
 �ṹ˵��  : GPLL0_GATE_TIME �Ĵ����ṹ���塣��ַƫ����:0x814����ֵ:0x12�����:8
 �Ĵ���˵��: GPLL���ʱ���ſ�ʱ������
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  gpll0_en     : 1;  /* bit[0]  : GPLLʹ�� */
        unsigned long  gpll_time    : 3;  /* bit[1-3]: GPLLʱ���ȶ��ȴ�ʱ�����ã�����ʱ��Ϊ19.2M��
                                                       000��GPLL����10us��ʱ���ȶ���
                                                       001��GPLL����20us��ʱ���ȶ���
                                                       010��GPLL����50us��ʱ���ȶ���
                                                       011��GPLL����75us��ʱ���ȶ���
                                                       100��GPLL����100us��ʱ���ȶ���
                                                       101��GPLL����115us��ʱ���ȶ���
                                                       110��GPLL1����125us��ʱ���ȶ���
                                                       default��20us */
        unsigned long  gpll_gate_en : 1;  /* bit[4]  : GPLLʱ���ſع���ʹ�ܣ�
                                                       0��gpllʱ���ſع��ܹرգ�
                                                       1��gpllʱ���ſع��ܴ򿪡� */
        unsigned long  gpll_timeout : 1;  /* bit[5]  : GPLL�ȶ�ָʾ��0��ʾGPLLδ�ȶ���1��ʾGPLL�ȶ���GPLL�ȶ�����ʱ������� */
        unsigned long  gpll_lock    : 1;  /* bit[6]  : GPLL����ָʾ�� */
        unsigned long  reserved     : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_GPLL0_GATE_TIME_UNION;
#define ABB_GPLL0_GATE_TIME_gpll0_en_START      (0)
#define ABB_GPLL0_GATE_TIME_gpll0_en_END        (0)
#define ABB_GPLL0_GATE_TIME_gpll_time_START     (1)
#define ABB_GPLL0_GATE_TIME_gpll_time_END       (3)
#define ABB_GPLL0_GATE_TIME_gpll_gate_en_START  (4)
#define ABB_GPLL0_GATE_TIME_gpll_gate_en_END    (4)
#define ABB_GPLL0_GATE_TIME_gpll_timeout_START  (5)
#define ABB_GPLL0_GATE_TIME_gpll_timeout_END    (5)
#define ABB_GPLL0_GATE_TIME_gpll_lock_START     (6)
#define ABB_GPLL0_GATE_TIME_gpll_lock_END       (6)


/*****************************************************************************
 �ṹ��    : ABB_GPL1L_GATE_TIME_UNION
 �ṹ˵��  : GPL1L_GATE_TIME �Ĵ����ṹ���塣��ַƫ����:0x815����ֵ:0x00�����:8
 �Ĵ���˵��: GPLL���ʱ���ſ�ʱ������
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  gpll1_en : 1;  /* bit[0]  : GPLLʹ�ܸ��� */
        unsigned long  reserved : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_GPL1L_GATE_TIME_UNION;
#define ABB_GPL1L_GATE_TIME_gpll1_en_START  (0)
#define ABB_GPL1L_GATE_TIME_gpll1_en_END    (0)




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
