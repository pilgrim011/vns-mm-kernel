/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : phy_abb_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-09-21 15:03:14
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��9��21��
    ��    ��   : x00347325
    �޸�����   : �ӡ�ComstarTV260 ABB�Ĵ�������_�ϲ���.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __ABB_INTERFACE_TV260_H__
#define __ABB_INTERFACE_TV260_H__
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
                     (1/1) register_define_abb
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
#define ABB_SCPLL0_LOCK_CTRL_ADDR                     (ABB_BASE_ADDR + 0x0)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
   ��      ����[7]:Reserved;
            [6:4]��PLL���Ƶ����postdiv2��Ĭ��ֵΪ1��
            [3]:Reserved;
            [2:0]��PLL���Ƶ����postdiv1��Ĭ��ֵΪ5��
   UNION�ṹ ���� */
#define ABB_SCPLL0_POSTDIV_ADDR                       (ABB_BASE_ADDR + 0x1)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
   ��      ����[7:0]��PLL������Ƶ����fbdiv[11:0]�ĵ�8bit��fbdiv[11:0]Ĭ��ֵΪ64.
   UNION�ṹ ���� */
#define ABB_SCPLL0_FBDIV_L_ADDR                       (ABB_BASE_ADDR + 0x2)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
 bit[7:4]    ����
 bit[3:0]    PLL������Ƶ����fbdiv[11:0]�ĸ�4bit��
   UNION�ṹ:  ABB_SCPLL0_FBDIV_H_UNION */
#define ABB_SCPLL0_FBDIV_H_ADDR                       (ABB_BASE_ADDR + 0x3)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
 bit[7:6]    ����
 bit[5:0]    PLL�ο���Ƶ����refdiv[5:0]��Ĭ��ֵΪ1��
   UNION�ṹ:  ABB_SCPLL0_REFDIV_UNION */
#define ABB_SCPLL0_REFDIV_ADDR                        (ABB_BASE_ADDR + 0x4)

/* �Ĵ���˵����SC_PLL��Ƶ�����ƼĴ���
   ��      ����[7:6]��Reserved��
            [5]��DACPD��Ĭ��ֵΪ0(��)��
            [4]��PLL FOUT4PHASEPD���ƣ�����Ч��Ĭ��ֵ1���رգ���
            [3]��DSMPD��С��ģʽPD�źţ�Ĭ��ֵ0���򿪣���
            [2]��PLL ��·���ƣ�Ĭ��ֵ0��PLL��·����bypass����
            [1]��PLL FOUTPOSTDIVPD���ƣ�����Ч��Ĭ��ֵ0���򿪣���
            [0]��PLL FOUTVCOPD���ƣ�����Ч��Ĭ��ֵ0���򿪣���
   UNION�ṹ ���� */
#define ABB_SCPLL0_FREQ_CTRL_ADDR                     (ABB_BASE_ADDR + 0x5)

/* �Ĵ���˵����SC_PLL�����������üĴ���
   ��      ����[7:0]��PLL������Ƶ����frac[23:0]��[7:0]λ��frac[23:0]Ĭ��ֵ0x0��
   UNION�ṹ ���� */
#define ABB_SCPLL0_FRAC1_ADDR                         (ABB_BASE_ADDR + 0x6)

/* �Ĵ���˵����SC_PLL�����������üĴ���
   ��      ����[7:0]��PLL������Ƶ����frac[23:0]��[15:8]λ��frac[23:0]Ĭ��ֵ0x0��
   UNION�ṹ ���� */
#define ABB_SCPLL0_FRAC2_ADDR                         (ABB_BASE_ADDR + 0x7)

/* �Ĵ���˵����SC_PLL�����������üĴ���
   ��      ����[7:0]��PLL������Ƶ����frac[23:0]��[23:16]λ��frac[23:0]Ĭ��ֵ0x0��
   UNION�ṹ ���� */
#define ABB_SCPLL0_FRAC3_ADDR                         (ABB_BASE_ADDR + 0x8)

/* �Ĵ���˵����SC_PLL�������ƼĴ���
 bit[7:1]    ����
 bit[0]      SCPLL0�������ø���ָʾ��
             scpll0_en�򿪺����������scpll0_postdiv��scpll0_fbdiv��scpll0_frac������������scpll0_sfg_update������ͬʱ���£�scpll0_en����ʱ�����ò����������£�����Ҫ����scpll0_sfg_update��
   UNION�ṹ:  ABB_SCPLL0_CFG_UPDATE_UNION */
#define ABB_SCPLL0_CFG_UPDATE_ADDR                    (ABB_BASE_ADDR + 0x9)

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
#define ABB_SCPLL1_LOCK_CTRL_ADDR                     (ABB_BASE_ADDR + 0xA)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
   ��      ����[7]:Reserved;
            [6:4]��PLL���Ƶ����postdiv2��Ĭ��ֵΪ1��
            [3]:Reserved;
            [2:0]��PLL���Ƶ����postdiv1��Ĭ��ֵΪ5��
   UNION�ṹ ���� */
#define ABB_SCPLL1_POSTDIV_ADDR                       (ABB_BASE_ADDR + 0xB)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
   ��      ����[7:0]��PLL������Ƶ����fbdiv[11:0]�ĵ�8bit��fbdiv[11:0]Ĭ��ֵΪ64.
   UNION�ṹ ���� */
#define ABB_SCPLL1_FBDIV_L_ADDR                       (ABB_BASE_ADDR + 0xC)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
 bit[7:4]    ����
 bit[3:0]    PLL������Ƶ����fbdiv[11:0]�ĸ�4bit��
   UNION�ṹ:  ABB_SCPLL1_FBDIV_H_UNION */
#define ABB_SCPLL1_FBDIV_H_ADDR                       (ABB_BASE_ADDR + 0xD)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
 bit[7:6]    ����
 bit[5:0]    PLL�ο���Ƶ����refdiv[5:0]��Ĭ��ֵΪ1��
   UNION�ṹ:  ABB_SCPLL1_REFDIV_UNION */
#define ABB_SCPLL1_REFDIV_ADDR                        (ABB_BASE_ADDR + 0xE)

/* �Ĵ���˵����SC_PLL��Ƶ�����ƼĴ���
   ��      ����[7:6]��Reserved��
            [5]��DACPD��Ĭ��ֵΪ0(��)��
            [4]��PLL FOUT4PHASEPD���ƣ�����Ч��Ĭ��ֵ1���رգ���
            [3]��DSMPD��С��ģʽPD�źţ�Ĭ��ֵ0���򿪣���
            [2]��PLL ��·���ƣ�Ĭ��ֵ0��PLL��·����bypass����
            [1]��PLL FOUTPOSTDIVPD���ƣ�����Ч��Ĭ��ֵ0���򿪣���
            [0]��PLL FOUTVCOPD���ƣ�����Ч��Ĭ��ֵ0���򿪣���
   UNION�ṹ ���� */
#define ABB_SCPLL1_FREQ_CTRL_ADDR                     (ABB_BASE_ADDR + 0xF)

/* �Ĵ���˵����SC_PLL�����������üĴ���
   ��      ����[7:0]��PLL������Ƶ����frac[23:0]��[7:0]λ��frac[23:0]Ĭ��ֵ0x0��
   UNION�ṹ ���� */
#define ABB_SCPLL1_FRAC1_ADDR                         (ABB_BASE_ADDR + 0x10)

/* �Ĵ���˵����SC_PLL�����������üĴ���
   ��      ����[7:0]��PLL������Ƶ����frac[23:0]��[15:8]λ��frac[23:0]Ĭ��ֵ0x0��
   UNION�ṹ ���� */
#define ABB_SCPLL1_FRAC2_ADDR                         (ABB_BASE_ADDR + 0x11)

/* �Ĵ���˵����SC_PLL�����������üĴ���
   ��      ����[7:0]��PLL������Ƶ����frac[23:0]��[23:16]λ��frac[23:0]Ĭ��ֵ0x0��
   UNION�ṹ ���� */
#define ABB_SCPLL1_FRAC3_ADDR                         (ABB_BASE_ADDR + 0x12)

/* �Ĵ���˵����SC_PLL�������ƼĴ���
 bit[7:1]    ����
 bit[0]      SCPLL1�������ø���ָʾ��
             scpll1_en�򿪺����������scpll1_postdiv��scpll1_fbdiv��scpll1_frac������������scpll1_sfg_update������ͬʱ���£�scpll1_en����ʱ�����ò����������£�����Ҫ����scpll1_sfg_update��
   UNION�ṹ:  ABB_SCPLL1_CFG_UPDATE_UNION */
#define ABB_SCPLL1_CFG_UPDATE_ADDR                    (ABB_BASE_ADDR + 0x13)

/* �Ĵ���˵����GPLL���ʱ���ſ�ʱ������
 bit[7:6]    ����
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
             default��100us
 bit[0]
   UNION�ṹ:  ABB_GPLL_GATE_TIME_UNION */
#define ABB_GPLL_GATE_TIME_ADDR                       (ABB_BASE_ADDR + 0x14)

/* �Ĵ���˵����WPLL���ʱ���ſ�ʱ������
 bit[7:6]    ����
 bit[5]      WPLL�ȶ�ָʾ��0��ʾWPLLδ�ȶ���1��ʾWPLL�ȶ���WPLL�ȶ�����ʱ�������
 bit[4]      WPLLʱ���ſع���ʹ�ܣ�
             0��wpllʱ���ſع��ܹرգ�
             1��wpllʱ���ſع��ܴ򿪡�
 bit[3:1]    WPLLʱ���ȶ��ȴ�ʱ�����ã�����ʱ��Ϊ19.2M��
             000��WPLL����10us��ʱ���ȶ���
             001��WPLL����20us��ʱ���ȶ���
             010��WPLL����50us��ʱ���ȶ���
             011��WPLL����75us��ʱ���ȶ���
             100��WPLL����100us��ʱ���ȶ���
             101��WPLL����115us��ʱ���ȶ���
             110��WPLL1����125us��ʱ���ȶ���
             default��100us
 bit[0]
   UNION�ṹ:  ABB_WPLL_GATE_TIME_UNION */
#define ABB_WPLL_GATE_TIME_ADDR                       (ABB_BASE_ADDR + 0x15)

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
#define ABB_TESTMODE_ADDR                             (ABB_BASE_ADDR + 0x16)

/* �Ĵ���˵����ABB���ֲ��ָ�λ�ź�
 bit[7:1]    ����
 bit[0]
   UNION�ṹ:  ABB_ABB_DIG_PWR_RST_UNION */
#define ABB_ABB_DIG_PWR_RST_ADDR                      (ABB_BASE_ADDR + 0x17)

/* �Ĵ���˵�������ֵ��ԼĴ�����
 bit[7:2]    ����
 bit[1:0]    ���ֵ��ԼĴ���
             bit[0]���ܽ�CH0_CLK_52M���ʱ��ѡ��
             1�����GPLL
             0�����SCPLL0
   UNION�ṹ:  ABB_CH0_COMM_REG_DEBUG_DIG_UNION */
#define ABB_CH0_COMM_REG_DEBUG_DIG_ADDR               (ABB_BASE_ADDR + 0x18)

/* �Ĵ���˵�������ֵ��ԼĴ�����
 bit[7:2]    ����
 bit[1:0]    ���ֵ��ԼĴ���
             bit[0]���ܽ�CH1_CLK_52M���ʱ��ѡ��
             1�����GPLL
             0�����SCPLL1
   UNION�ṹ:  ABB_CH1_COMM_REG_DEBUG_DIG_UNION */
#define ABB_CH1_COMM_REG_DEBUG_DIG_ADDR               (ABB_BASE_ADDR + 0x19)

/* �Ĵ���˵����ABB�汾�Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH0_VERSION_ADDR                          (ABB_BASE_ADDR + 0x40)

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
#define ABB_BIST_CFG_1_ADDR                           (ABB_BASE_ADDR + 0x41)

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
#define ABB_BIST_CFG_2_ADDR                           (ABB_BASE_ADDR + 0x42)

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
#define ABB_BIST_CFG_3_ADDR                           (ABB_BASE_ADDR + 0x43)

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
#define ABB_BIST_CFG_4_ADDR                           (ABB_BASE_ADDR + 0x44)

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
#define ABB_BIST_CFG_5_ADDR                           (ABB_BASE_ADDR + 0x45)

/* �Ĵ���˵����BIST���״̬�Ĵ���
 bit[7]      BIST���������Ĳ������Ƿ�ͨ������δbypass�Ĳ����Ƿ�ȫ��ͨ����
             0��δͨ����
             1��ͨ����
 bit[6:1]    ����
 bit[0]      SNDR�������״̬��
             0��û����ɣ�
             1����ɡ�
   UNION�ṹ:  ABB_BIST_RPT_1_UNION */
#define ABB_BIST_RPT_1_ADDR                           (ABB_BASE_ADDR + 0x46)

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
#define ABB_BIST_RPT_2_ADDR                           (ABB_BASE_ADDR + 0x47)

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
#define ABB_BIST_RPT_3_ADDR                           (ABB_BASE_ADDR + 0x48)

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
#define ABB_BIST_RPT_4_ADDR                           (ABB_BASE_ADDR + 0x49)

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
#define ABB_BIST_RPT_5_ADDR                           (ABB_BASE_ADDR + 0x4A)

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
#define ABB_BIST_RPT_6_ADDR                           (ABB_BASE_ADDR + 0x4B)

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
#define ABB_BIST_RPT_7_ADDR                           (ABB_BASE_ADDR + 0x4C)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
 bit[7:3]    ����
 bit[2:0]    I·dc�ϱ�ֵ��λ��
   UNION�ṹ:  ABB_BIST_RPT_8_UNION */
#define ABB_BIST_RPT_8_ADDR                           (ABB_BASE_ADDR + 0x4D)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����I·dc�ϱ�ֵ��λ��
   UNION�ṹ ���� */
#define ABB_BIST_RPT_9_ADDR                           (ABB_BASE_ADDR + 0x4E)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
 bit[7:3]    ����
 bit[2:0]    Q·dc�ϱ�ֵ��λ��
   UNION�ṹ:  ABB_BIST_RPT_10_UNION */
#define ABB_BIST_RPT_10_ADDR                          (ABB_BASE_ADDR + 0x4F)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����Q·dc�ϱ�ֵ��λ��
   UNION�ṹ ���� */
#define ABB_BIST_RPT_11_ADDR                          (ABB_BASE_ADDR + 0x50)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����I·������ϱ���8bit���޷�������
   UNION�ṹ ���� */
#define ABB_BIST_RPT_12_ADDR                          (ABB_BASE_ADDR + 0x51)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����Q·������ϱ���8bit���޷�������
   UNION�ṹ ���� */
#define ABB_BIST_RPT_13_ADDR                          (ABB_BASE_ADDR + 0x52)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����Gain_mismatch�ϱ����޷�������
   UNION�ṹ ���� */
#define ABB_BIST_RPT_14_ADDR                          (ABB_BASE_ADDR + 0x53)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����Gain_error�ϱ����޷�������
   UNION�ṹ ���� */
#define ABB_BIST_RPT_15_ADDR                          (ABB_BASE_ADDR + 0x54)

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
#define ABB_BIST_RPT_16_ADDR                          (ABB_BASE_ADDR + 0x55)

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
#define ABB_BIST_RPT_17_ADDR                          (ABB_BASE_ADDR + 0x56)

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
#define ABB_BIST_RPT_18_ADDR                          (ABB_BASE_ADDR + 0x57)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����I·������ϱ���8bit���޷�������
   UNION�ṹ ���� */
#define ABB_BIST_RPT_19_ADDR                          (ABB_BASE_ADDR + 0x58)

/* �Ĵ���˵����BIST����ϱ��Ĵ���
   ��      ����Q·������ϱ���8bit���޷�������
   UNION�ṹ ���� */
#define ABB_BIST_RPT_20_ADDR                          (ABB_BASE_ADDR + 0x59)

/* �Ĵ���˵����BIST�����׼�Ĵ���
 bit[7:6]    ����
 bit[5:0]    BIST DC������޸�6bit���з�������
   UNION�ṹ:  ABB_BIST_CFG_6_UNION */
#define ABB_BIST_CFG_6_ADDR                           (ABB_BASE_ADDR + 0x5A)

/* �Ĵ���˵����BIST�����׼�Ĵ���
   ��      ����BIST DC������޵�8bit���з�������
   UNION�ṹ ���� */
#define ABB_BIST_CFG_7_ADDR                           (ABB_BASE_ADDR + 0x5B)

/* �Ĵ���˵����BIST�����׼�Ĵ���
 bit[7:6]    ����
 bit[5:0]    BIST DC������޸�6bit���з�������
   UNION�ṹ:  ABB_BIST_CFG_8_UNION */
#define ABB_BIST_CFG_8_ADDR                           (ABB_BASE_ADDR + 0x5C)

/* �Ĵ���˵����BIST�����׼�Ĵ���
   ��      ����BIST DC������޵�8bit���з�������
   UNION�ṹ ���� */
#define ABB_BIST_CFG_9_ADDR                           (ABB_BASE_ADDR + 0x5D)

/* �Ĵ���˵����BIST�����׼�Ĵ���
   ��      ����BIST gain mismatch������ޣ��޷�������
   UNION�ṹ ���� */
#define ABB_BIST_CFG_10_ADDR                          (ABB_BASE_ADDR + 0x5E)

/* �Ĵ���˵����BIST�����׼�Ĵ���
   ��      ����BIST gain mismatch������ޣ��޷�������
   UNION�ṹ ���� */
#define ABB_BIST_CFG_11_ADDR                          (ABB_BASE_ADDR + 0x5F)

/* �Ĵ���˵����BIST�����׼�Ĵ���
   ��      ����BIST gain error������ޣ��޷�������
   UNION�ṹ ���� */
#define ABB_BIST_CFG_12_ADDR                          (ABB_BASE_ADDR + 0x60)

/* �Ĵ���˵����BIST�����׼�Ĵ���
   ��      ����BIST gain error������ޣ��޷�������
   UNION�ṹ ���� */
#define ABB_BIST_CFG_13_ADDR                          (ABB_BASE_ADDR + 0x61)

/* �Ĵ���˵����BIST SNDR 2Gģʽ���ֵ
   ��      ����BIST 2Gģʽ SNDR���ֵ[7:0]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_2G_0_ADDR                       (ABB_BASE_ADDR + 0x62)

/* �Ĵ���˵����BIST SNDR 2Gģʽ���ֵ
   ��      ����BIST 2Gģʽ SNDR���ֵ[15:8]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_2G_1_ADDR                       (ABB_BASE_ADDR + 0x63)

/* �Ĵ���˵����BIST SNDR 2Gģʽ���ֵ
   ��      ����BIST 2Gģʽ SNDR���ֵ[23:16]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_2G_2_ADDR                       (ABB_BASE_ADDR + 0x64)

/* �Ĵ���˵����BIST SNDR 3Gģʽ���ֵ
   ��      ����BIST 3Gģʽ SNDR���ֵ[7:0]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_3G_0_ADDR                       (ABB_BASE_ADDR + 0x65)

/* �Ĵ���˵����BIST SNDR 3Gģʽ���ֵ
   ��      ����BIST 3Gģʽ SNDR���ֵ[15:8]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_3G_1_ADDR                       (ABB_BASE_ADDR + 0x66)

/* �Ĵ���˵����BIST SNDR 3Gģʽ���ֵ
   ��      ����BIST 3Gģʽ SNDR���ֵ[23:16]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_3G_2_ADDR                       (ABB_BASE_ADDR + 0x67)

/* �Ĵ���˵����BIST SNDR TDSģʽ���ֵ
   ��      ����BIST TDSģʽ SNDR���ֵ[7:0]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_TDS_0_ADDR                      (ABB_BASE_ADDR + 0x68)

/* �Ĵ���˵����BIST SNDR TDSģʽ���ֵ
   ��      ����BIST TDSģʽ SNDR���ֵ[15:8]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_TDS_1_ADDR                      (ABB_BASE_ADDR + 0x69)

/* �Ĵ���˵����BIST SNDR TDSģʽ���ֵ
   ��      ����BIST TDSģʽ SNDR���ֵ[23:16]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_TDS_2_ADDR                      (ABB_BASE_ADDR + 0x6A)

/* �Ĵ���˵����BIST SNDR 4Gģʽ���ֵ
   ��      ����BIST 4Gģʽ SNDR���ֵ[7:0]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_4G_0_ADDR                       (ABB_BASE_ADDR + 0x6B)

/* �Ĵ���˵����BIST SNDR 4Gģʽ���ֵ
   ��      ����BIST 4Gģʽ SNDR���ֵ[15:8]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_4G_1_ADDR                       (ABB_BASE_ADDR + 0x6C)

/* �Ĵ���˵����BIST SNDR 4Gģʽ���ֵ
   ��      ����BIST 4Gģʽ SNDR���ֵ[23:16]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_4G_2_ADDR                       (ABB_BASE_ADDR + 0x6D)

/* �Ĵ���˵����BIST SNDR CDMAģʽ���ֵ
   ��      ����BIST CDMAģʽ SNDR���ֵ[7:0]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_CDMA_0_ADDR                     (ABB_BASE_ADDR + 0x6E)

/* �Ĵ���˵����BIST SNDR CDMAģʽ���ֵ
   ��      ����BIST CDMAģʽ SNDR���ֵ[15:8]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_CDMA_1_ADDR                     (ABB_BASE_ADDR + 0x6F)

/* �Ĵ���˵����BIST SNDR CDMAģʽ���ֵ
   ��      ����BIST CDMAģʽ SNDR���ֵ[23:16]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_CDMA_2_ADDR                     (ABB_BASE_ADDR + 0x70)

/* �Ĵ���˵����BIST SNDR CAģʽ���ֵ
   ��      ����BIST CAģʽ SNDR���ֵ[7:0]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_CA_0_ADDR                       (ABB_BASE_ADDR + 0x71)

/* �Ĵ���˵����BIST SNDR CAģʽ���ֵ
   ��      ����BIST CAģʽ SNDR���ֵ[15:8]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_CA_1_ADDR                       (ABB_BASE_ADDR + 0x72)

/* �Ĵ���˵����BIST SNDR CAģʽ���ֵ
   ��      ����BIST CAģʽ SNDR���ֵ[23:16]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_CA_2_ADDR                       (ABB_BASE_ADDR + 0x73)

/* �Ĵ���˵����BIST SNDR ET0ģʽ���ֵ
   ��      ����BIST ET0ģʽ SNDR���ֵ[7:0]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_ET0_0_ADDR                      (ABB_BASE_ADDR + 0x74)

/* �Ĵ���˵����BIST SNDR ET0ģʽ���ֵ
   ��      ����BIST ET0ģʽ SNDR���ֵ[15:8]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_ET0_1_ADDR                      (ABB_BASE_ADDR + 0x75)

/* �Ĵ���˵����BIST SNDR ET0ģʽ���ֵ
   ��      ����BIST ET0ģʽ SNDR���ֵ[23:16]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_ET0_2_ADDR                      (ABB_BASE_ADDR + 0x76)

/* �Ĵ���˵����BIST SNDR ET1ģʽ���ֵ
   ��      ����BIST ET1ģʽ SNDR���ֵ[7:0]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_ET1_0_ADDR                      (ABB_BASE_ADDR + 0x77)

/* �Ĵ���˵����BIST SNDR ET1ģʽ���ֵ
   ��      ����BIST ET1ģʽ SNDR���ֵ[15:8]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_ET1_1_ADDR                      (ABB_BASE_ADDR + 0x78)

/* �Ĵ���˵����BIST SNDR ET1ģʽ���ֵ
   ��      ����BIST ET1ģʽ SNDR���ֵ[23:16]
   UNION�ṹ ���� */
#define ABB_BIST_SNDR_ET1_2_ADDR                      (ABB_BASE_ADDR + 0x79)

/* �Ĵ���˵����IO_CFG�Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define ABB_IOCG_INPUT_ADDR                           (ABB_BASE_ADDR + 0x7A)

/* �Ĵ���˵����IO_CFG�Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define ABB_IOCG_OUTPUT_ADDR                          (ABB_BASE_ADDR + 0x7B)

/* �Ĵ���˵����IO_CFG�Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define ABB_IOCG_RX_MCLK_ADDR                         (ABB_BASE_ADDR + 0x7C)

/* �Ĵ���˵����IO_CFG�Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define ABB_IOCG_TCXO_ADDR                            (ABB_BASE_ADDR + 0x7D)

/* �Ĵ���˵����IO_CFG�Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define ABB_IOCG_SC_CLK_ADDR                          (ABB_BASE_ADDR + 0x7E)

/* �Ĵ���˵����IO_CFG�Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define ABB_IOCG_CFG_ADDR                             (ABB_BASE_ADDR + 0x7F)

/* �Ĵ���˵����ABB�汾�Ĵ���
   ��      ����
   UNION�ṹ ���� */
#define ABB_CH1_VERSION_ADDR                          (ABB_BASE_ADDR + 0xA0)

/* �Ĵ���˵����SC_PLL�������ƼĴ���
 bit[7]      ����
 bit[6]      ADPLL����ָʾ��
 bit[5]      ADPLL�ȶ�ָʾ��0��ʾADPLLδ�ȶ���1��ʾADPLL�ȶ���ADPLL�ȶ�����ʱ�������
 bit[4]      ADPLL�ſ�ʹ���źš�
 bit[3:1]    ADPLLʱ���ȶ��ȴ�ʱ�����ã�����ʱ��Ϊ19.2M��
             000��ADPLL����10us��ʱ���ȶ���
             001��ADPLL����20us��ʱ���ȶ���
             010��ADPLL����50us��ʱ���ȶ���
             011��ADPLL����75us��ʱ���ȶ���
             100��ADPLL����100us��ʱ���ȶ���
             101��ADPLL����115us��ʱ���ȶ���
             110��ADPLL1����125us��ʱ���ȶ���
             default��100us
 bit[0]      ADPLLʹ���źš�����ͨ��CFG�ӿ����ô�adpll��
   UNION�ṹ:  ABB_ADPLL_LOCK_CTRL_UNION */
#define ABB_ADPLL_LOCK_CTRL_ADDR                      (ABB_BASE_ADDR + 0xA1)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
   ��      ����[7]:Reserved;
            [6:4]��PLL���Ƶ����postdiv2��Ĭ��ֵΪ1��
            [3]:Reserved;
            [2:0]��PLL���Ƶ����postdiv1��Ĭ��ֵΪ1��
   UNION�ṹ ���� */
#define ABB_ADPLL_POSTDIV_ADDR                        (ABB_BASE_ADDR + 0xA2)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
   ��      ����[7:0]��PLL������Ƶ����fbdiv[11:0]�ĵ�8bit��fbdiv[11:0]Ĭ��ֵΪ128.
   UNION�ṹ ���� */
#define ABB_ADPLL_FBDIV_L_ADDR                        (ABB_BASE_ADDR + 0xA3)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
 bit[7:4]    ����
 bit[3:0]    PLL������Ƶ����fbdiv[11:0]�ĸ�4bit��
   UNION�ṹ:  ABB_ADPLL_FBDIV_H_UNION */
#define ABB_ADPLL_FBDIV_H_ADDR                        (ABB_BASE_ADDR + 0xA4)

/* �Ĵ���˵����SC_PLL��Ƶ���������üĴ���
 bit[7:6]    ����
 bit[5:0]    PLL�ο���Ƶ����refdiv[5:0]��Ĭ��ֵΪ1��
   UNION�ṹ:  ABB_ADPLL_REFDIV_UNION */
#define ABB_ADPLL_REFDIV_ADDR                         (ABB_BASE_ADDR + 0xA5)

/* �Ĵ���˵����SC_PLL�����������üĴ���
   ��      ����[7:0]��PLL������Ƶ����frac[23:0]��[7:0]λ��frac[23:0]Ĭ��ֵ0x0��
   UNION�ṹ ���� */
#define ABB_ADPLL_FRAC1_ADDR                          (ABB_BASE_ADDR + 0xA6)

/* �Ĵ���˵����SC_PLL�����������üĴ���
   ��      ����[7:0]��PLL������Ƶ����frac[23:0]��[15:8]λ��frac[23:0]Ĭ��ֵ0x0��
   UNION�ṹ ���� */
#define ABB_ADPLL_FRAC2_ADDR                          (ABB_BASE_ADDR + 0xA7)

/* �Ĵ���˵����SC_PLL�����������üĴ���
   ��      ����[7:0]��PLL������Ƶ����frac[23:0]��[23:16]λ��frac[23:0]Ĭ��ֵ0x0��
   UNION�ṹ ���� */
#define ABB_ADPLL_FRAC3_ADDR                          (ABB_BASE_ADDR + 0xA8)

/* �Ĵ���˵����SC_PLL��Ƶ�����ƼĴ���
   ��      ����[7:5]��Reserved��
            [4]��PLL FOUT4PHASEPD���ƣ�����Ч��Ĭ��ֵ1���رգ���
            [3]��
            [2]��PLL ��·���ƣ�Ĭ��ֵ0��PLL��·����bypass����
            [1]��PLL FOUTPOSTDIVPD���ƣ�����Ч��Ĭ��ֵ0���򿪣���
            [0]��PLL FOUTDCOPD���ƣ�����Ч��Ĭ��ֵ0���򿪣���
   UNION�ṹ ���� */
#define ABB_ADPLL_FREQ_CTRL_ADDR                      (ABB_BASE_ADDR + 0xA9)

/* �Ĵ���˵����SC_PLL�������ƼĴ���
 bit[7:1]    ����
 bit[0]      ADPLL�������ø���ָʾ��
             adpll_en�򿪺����������adpll_postdiv��adpll_fbdiv��adpll_frac������������adpll_sfg_update������ͬʱ���£�adpll_en����ʱ�����ò����������£�����Ҫ����adpll_sfg_update��
   UNION�ṹ:  ABB_ADPLL_CFG_UPDATE_UNION */
#define ABB_ADPLL_CFG_UPDATE_ADDR                     (ABB_BASE_ADDR + 0xAA)

/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define ABB_ADPLL_GPLLCFG0_ADDR                       (ABB_BASE_ADDR + 0xAB)

/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define ABB_ADPLL_GPLLCFG1_ADDR                       (ABB_BASE_ADDR + 0xAC)

/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define ABB_ADPLL_GPLLCFG2_ADDR                       (ABB_BASE_ADDR + 0xAD)

/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define ABB_ADPLL_GPLLCFG3_ADDR                       (ABB_BASE_ADDR + 0xAE)

/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define ABB_ADPLL_GPLLCFG4_ADDR                       (ABB_BASE_ADDR + 0xAF)

/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define ABB_ADPLL_GPLLCFG5_ADDR                       (ABB_BASE_ADDR + 0xB0)

/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define ABB_ADPLL_GPLLCFG6_ADDR                       (ABB_BASE_ADDR + 0xB1)

/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define ABB_ADPLL_GPLLCFG7_ADDR                       (ABB_BASE_ADDR + 0xB2)

/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define ABB_ADPLL_GPLLCFG8_ADDR                       (ABB_BASE_ADDR + 0xB3)

/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define ABB_ADPLL_GPLLCFG9_ADDR                       (ABB_BASE_ADDR + 0xB4)

/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define ABB_ADPLL_GPLLCFG10_ADDR                      (ABB_BASE_ADDR + 0xB5)

/* �Ĵ���˵����
 bit[7:2]    ����
 bit[1]
 bit[0]
   UNION�ṹ:  ABB_ADPLL_TEST_CFG_UNION */
#define ABB_ADPLL_TEST_CFG_ADDR                       (ABB_BASE_ADDR + 0xB6)

/* �Ĵ���˵����
 bit[7:1]    ����
 bit[0]
   UNION�ṹ:  ABB_ADPLL_CLKSSCG_CFG_UNION */
#define ABB_ADPLL_CLKSSCG_CFG_ADDR                    (ABB_BASE_ADDR + 0xB7)

/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define ABB_ADPLL_TEST_WDATA_LSB_ADDR                 (ABB_BASE_ADDR + 0xB8)

/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define ABB_ADPLL_TEST_WDATA_MSB_ADDR                 (ABB_BASE_ADDR + 0xB9)

/* �Ĵ���˵����TX ET�������üĴ���1��
 bit[7]      ����
 bit[6]      ETͨ��������bypass�ź�
             0����bypass��2����������Ĭ�ϣ���
             1��bypass�������н�������
 bit[5:3]    ����
 bit[2]      ETͨ����λ�Ĵ�����
             0������λ��
             1����λ��
 bit[1]      ETͨ������˲�����bypass�ź�
             0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
             1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate
 bit[0]      ETͨ�������˲���bypass���ƣ�
             0����bypass(Ĭ��)
             1��bypass
   UNION�ṹ:  ABB_TX_ET_DIG_1_UNION */
#define ABB_TX_ET_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x100)

/* �Ĵ���˵����TX ET�������üĴ���2��
 bit[7]      ET TXͨ��dem bypass��
             0��DEM��(Ĭ��)
             1��DEM bypass
 bit[6]      ����
 bit[5]      ET TXͨ��DEMģʽ���ƣ�
             0��ʹ��CLAģʽ(Ĭ��)
             1��ʹ��DWAģʽ
 bit[4]      ����
 bit[3]      ET LSB���bit���ֵ����
 bit[2:1]    TXͨ��DEM constϵ����
             0��0
             1��2
             2��4(Ĭ��)
             3��6
 bit[0]      ETͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!et_gating_en)|XX_TX_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_TX_ET_DIG_2_UNION */
#define ABB_TX_ET_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x101)

/* �Ĵ���˵����TX ET�������üĴ���3��
   ��      ��������
   UNION�ṹ ���� */
#define ABB_TX_ET_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x102)

/* �Ĵ���˵����TX ET�������üĴ���4��
 bit[7]
 bit[6]      ETͨ���㷨����ģʽʹ�ܡ���ģʽʹ�ܣ���ET TX����ͨ��CH1 RXͨ�����ء�
             0����ʹ�ܣ�
             1��ʹ�ܡ�
 bit[5]      ETͨ���ӿڻ���ģʽʹ�ܡ���ģʽʹ�ܣ���ET TX����ͨ��CH1 RXͨ�����ء�
             0����ʹ�ܣ�
             1��ʹ�ܡ�
 bit[4]      ET��Ƶ��ʹ��bypass����
             0����bypass
             1��bypass
 bit[3]      ETģʽǿ������ʹ�ܡ�
             0����ʹ�ܣ�
             1��ʹ�ܡ�
 bit[2]      ETģʽǿ������ֵ��
 bit[1]      ET�߿�ǿ������ʹ�ܡ�
             0����ʹ�ܣ�
             1��ʹ�ܡ�
 bit[0]      ET�߿�ǿ������ֵ��
   UNION�ṹ:  ABB_TX_ET_DIG_4_UNION */
#define ABB_TX_ET_DIG_4_ADDR                          (ABB_BASE_ADDR + 0x103)

/* �Ĵ���˵����ETͨ��offset���üĴ�����
   ��      ����ETͨ��offset���üĴ�����
   UNION�ṹ ���� */
#define ABB_ET_DC_OFFSET_ADDR                         (ABB_BASE_ADDR + 0x104)

/* �Ĵ���˵����ETͨ��״̬�ϱ��Ĵ���
 bit[7:3]    ����
 bit[2]      ET HB�˲������ָʾ��
 bit[1]      ET CIC6�˲������ָʾ��
 bit[0]      ET�����˲������ָʾ��
   UNION�ṹ:  ABB_ET_STATE_RPT_UNION */
#define ABB_ET_STATE_RPT_ADDR                         (ABB_BASE_ADDR + 0x105)

/* �Ĵ���˵����SINE���ͼĴ�����
 bit[7:4]    ���Ҳ�����Ƶ�ʿ��ƣ���λ(freq of tx_hb_clk)/32�����䷶ΧΪ1~f
 bit[3:2]    ���Ҳ����ͷ��ȿ���
             00��������
             01��3/4����
             10��1/2����
             11��1/4����
 bit[1]      ����
 bit[0]      etͨ�����Ҳ�����ʹ�ܡ���λʹ�ܣ���ETͨ���������Ҳ��źţ���ͨ��sine_sw_reqѡ��CH0����CH1�������Ҳ��źš�
             0��������
             1������
   UNION�ṹ:  ABB_ET_SINE_GENERATE_UNION */
#define ABB_ET_SINE_GENERATE_ADDR                     (ABB_BASE_ADDR + 0x106)

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
   UNION�ṹ:  ABB_TX_3G_DIG_1_UNION */
#define ABB_TX_3G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x20C)

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
   UNION�ṹ:  ABB_TX_3G_DIG_2_UNION */
#define ABB_TX_3G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x20D)

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
   UNION�ṹ:  ABB_TX_3G_DIG_3_UNION */
#define ABB_TX_3G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x20E)

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
   UNION�ṹ:  ABB_TX_4G_DIG_1_UNION */
#define ABB_TX_4G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x20F)

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
   UNION�ṹ:  ABB_TX_4G_DIG_2_UNION */
#define ABB_TX_4G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x210)

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
   UNION�ṹ:  ABB_TX_4G_DIG_3_UNION */
#define ABB_TX_4G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x211)

/* �Ĵ���˵��������ģʽ�Ĵ�����
 bit[7:1]    ����
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
   ��      ����TXͨ��ģʽ���ƣ�
            000��2G(Ĭ��)
            001��3G
            010��4G
            011��TDS
            100��CDMA
            Others��Reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x24A)

/* �Ĵ���˵����TX���ֹ���״̬�ϱ��Ĵ�����
   ��      ����TXͨ��FIFO����״̬
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
   ��      ��������
   UNION�ṹ ���� */
#define ABB_CH0_TX_LINE_RPT0_ADDR                     (ABB_BASE_ADDR + 0x253)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
   ��      ��������
   UNION�ṹ ���� */
#define ABB_CH0_TX_LINE_RPT1_ADDR                     (ABB_BASE_ADDR + 0x254)

/* �Ĵ���˵��������ģʽ�Ĵ�����
 bit[7:1]    ����
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
   ��      ����TXͨ��ģʽ�����ϱ���
            000��2G(Ĭ��)
            001��3G
            010��4G &amp; ET &amp; APT
            011��TDS
            Others��CA
   UNION�ṹ ���� */
#define ABB_CH1_TX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x26A)

/* �Ĵ���˵����TX���ֹ���״̬�ϱ��Ĵ�����
   ��      ����TXͨ��FIFO����״̬
   UNION�ṹ ���� */
#define ABB_CH1_TX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x26B)

/* �Ĵ���˵�������ֵ��ԼĴ�����
 bit[7]      ����
 bit[6]      TX SDģ������������·ʹ�ܣ�
             0��������������·��
             1������������·��Ĭ�ϣ���
 bit[5]      Tuning code��Դѡ��
             0���Ĵ�������
             1���Զ����£�Ĭ�ϣ�
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
   ��      ��������
   UNION�ṹ ���� */
#define ABB_CH1_TX_LINE_RPT0_ADDR                     (ABB_BASE_ADDR + 0x273)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
   ��      ��������
   UNION�ṹ ���� */
#define ABB_CH1_TX_LINE_RPT1_ADDR                     (ABB_BASE_ADDR + 0x274)

/* �Ĵ���˵����RX IDLEģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G_A(Ĭ��)
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             110��CA
             111��2G_B
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                       /TDS_B/4G_C,        /4G_B,
             00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��),122.88M,2.167M,
             others��reserved
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11���̶�ϵ��4��
   UNION�ṹ:  ABB_RX_IDLE_DIG_1_UNION */
#define ABB_RX_IDLE_DIG_1_ADDR                        (ABB_BASE_ADDR + 0x400)

/* �Ĵ���˵����RX IDLEģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵����
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
 bit[7:2]    ����
 bit[1:0]
   UNION�ṹ:  ABB_RX_IDLE_DIG_3_UNION */
#define ABB_RX_IDLE_DIG_3_ADDR                        (ABB_BASE_ADDR + 0x402)

/* �Ĵ���˵����RX 2Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G_A(Ĭ��)
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             110��CA
             111��2G_B
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                       /TDS_B/4G_C,        /4G_B,
             00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��),122.88M,2.167M,
             others��reserved
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11���̶�ϵ��4��
   UNION�ṹ:  ABB_RX_2G_DIG_1_UNION */
#define ABB_RX_2G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x403)

/* �Ĵ���˵����RX 2Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵����
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
 bit[7:2]    ����
 bit[1:0]
   UNION�ṹ:  ABB_RX_2G_DIG_3_UNION */
#define ABB_RX_2G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x405)

/* �Ĵ���˵����RX Cģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G_A(Ĭ��)
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             110��CA
             111��2G_B
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                       /TDS_B/4G_C,        /4G_B,
             00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��),122.88M,2.167M,
             others��reserved
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11���̶�ϵ��4��
   UNION�ṹ:  ABB_RX_C_DIG_1_UNION */
#define ABB_RX_C_DIG_1_ADDR                           (ABB_BASE_ADDR + 0x406)

/* �Ĵ���˵����RX Cģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵����
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
 bit[7:2]    ����
 bit[1:0]
   UNION�ṹ:  ABB_RX_C_DIG_3_UNION */
#define ABB_RX_C_DIG_3_ADDR                           (ABB_BASE_ADDR + 0x408)

/* �Ĵ���˵����RX TDSģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G_A(Ĭ��)
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             110��CA
             111��2G_B
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                       /TDS_B/4G_C,        /4G_B,
             00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��),122.88M,2.167M,
             others��reserved
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11���̶�ϵ��4��
   UNION�ṹ:  ABB_RX_TDS_DIG_1_UNION */
#define ABB_RX_TDS_DIG_1_ADDR                         (ABB_BASE_ADDR + 0x409)

/* �Ĵ���˵����RX TDSģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵����
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
 bit[7:2]    ����
 bit[1:0]
   UNION�ṹ:  ABB_RX_TDS_DIG_3_UNION */
#define ABB_RX_TDS_DIG_3_ADDR                         (ABB_BASE_ADDR + 0x40B)

/* �Ĵ���˵����RX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G_A(Ĭ��)
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             110��CA
             111��2G_B
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                       /TDS_B/4G_C,        /4G_B,
             00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��),122.88M,2.167M,
             others��reserved
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11���̶�ϵ��4��
   UNION�ṹ:  ABB_RX_3G_DIG_1_UNION */
#define ABB_RX_3G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x40C)

/* �Ĵ���˵����RX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵����
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
   UNION�ṹ:  ABB_RX_3G_DIG_2_UNION */
#define ABB_RX_3G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x40D)

/* �Ĵ���˵����RX 3Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:2]    ����
 bit[1:0]
   UNION�ṹ:  ABB_RX_3G_DIG_3_UNION */
#define ABB_RX_3G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x40E)

/* �Ĵ���˵����RX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G_A(Ĭ��)
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             110��CA
             111��2G_B
 bit[4:3]    RXͨ��CIC�˲���������ʿ���(Hz)��
                 2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                       /TDS_B/4G_C,        /4G_B,
             00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��),122.88M,2.167M,
             others��reserved
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11���̶�ϵ��4��
   UNION�ṹ:  ABB_RX_4G_DIG_1_UNION */
#define ABB_RX_4G_DIG_1_ADDR                          (ABB_BASE_ADDR + 0x40F)

/* �Ĵ���˵����RX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵����
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
   UNION�ṹ:  ABB_RX_4G_DIG_2_UNION */
#define ABB_RX_4G_DIG_2_ADDR                          (ABB_BASE_ADDR + 0x410)

/* �Ĵ���˵����RX 4Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
 bit[7:2]    ����
 bit[1:0]
   UNION�ṹ:  ABB_RX_4G_DIG_3_UNION */
#define ABB_RX_4G_DIG_3_ADDR                          (ABB_BASE_ADDR + 0x411)

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
#define ABB_RX_EN_DELAY_ADDR                          (ABB_BASE_ADDR + 0x420)

/* �Ĵ���˵����ģʽ�Ĵ���
 bit[7:1]    ����
 bit[0]
   UNION�ṹ:  ABB_COMB_MODE_UNION */
#define ABB_COMB_MODE_ADDR                            (ABB_BASE_ADDR + 0x421)

/* �Ĵ���˵��������ģʽ�Ĵ�����
 bit[7:6]    ����
 bit[5:4]
 bit[3:2]    ����
 bit[1]
 bit[0]      ���ֲ���RXͨ����λ�źţ�
             0������λ(Ĭ��)
             1����λ
   UNION�ṹ:  ABB_CH0_RX_TESTMODE_UNION */
#define ABB_CH0_RX_TESTMODE_ADDR                      (ABB_BASE_ADDR + 0x480)

/* �Ĵ���˵����PLLѡ��Ĵ���
 bit[7:4]    ����
 bit[3]
 bit[2]
 bit[1:0]
   UNION�ṹ:  ABB_CH0_PLL_SEL_UNION */
#define ABB_CH0_PLL_SEL_ADDR                          (ABB_BASE_ADDR + 0x481)

/* �Ĵ���˵����RX���ֹ���ģʽ�ϱ��Ĵ�����
   ��      ����RXͨ��ģʽ�����ϱ���
            000��2G(Ĭ��)
            001��3G_SC
            010��4G &amp; ET &amp; APT
            011��3G_DC
            100��TDS
            Others��CA
   UNION�ṹ ���� */
#define ABB_CH0_RX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x482)

/* �Ĵ���˵����RX���ֹ���״̬�ϱ��Ĵ�����
   ��      ��������
   UNION�ṹ ���� */
#define ABB_CH0_RX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x483)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x484)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXAͨ��I·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXAͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH0_RXA_I_COEF1_UNION */
#define ABB_CH0_RXA_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x485)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x486)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXAͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH0_RXA_I_COEF3_UNION */
#define ABB_CH0_RXA_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x487)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXA_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x488)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��Q·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x489)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXAͨ��Q·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXAͨ��Q·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH0_RXA_Q_COEF1_UNION */
#define ABB_CH0_RXA_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x48A)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��Q·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x48B)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXAͨ��Q·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH0_RXA_Q_COEF3_UNION */
#define ABB_CH0_RXA_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x48C)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��Q·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXA_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x48D)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x48E)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXBͨ��I·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXBͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH0_RXB_I_COEF1_UNION */
#define ABB_CH0_RXB_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x48F)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x490)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXBͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH0_RXB_I_COEF3_UNION */
#define ABB_CH0_RXB_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x491)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXB_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x492)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��Q·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x493)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXBͨ��Q·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXBͨ��Q·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH0_RXB_Q_COEF1_UNION */
#define ABB_CH0_RXB_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x494)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��Q·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x495)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXBͨ��Q·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH0_RXB_Q_COEF3_UNION */
#define ABB_CH0_RXB_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x496)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��Q·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH0_RXB_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x497)

/* �Ĵ���˵����RXAͨ��BLOCKING DCR���üĴ�����
 bit[7:5]    RXA����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ��
 bit[4:0]    RXA����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣
   UNION�ṹ:  ABB_CH0_REG_RXA_DCR_CFG_UNION */
#define ABB_CH0_REG_RXA_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x498)

/* �Ĵ���˵����RXBͨ��BLOCKING DCR���üĴ�����
 bit[7:5]    RXB����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ��
 bit[4:0]    RXB����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣
   UNION�ṹ:  ABB_CH0_REG_RXB_DCR_CFG_UNION */
#define ABB_CH0_REG_RXB_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x499)

/* �Ĵ���˵����BLOCKING DCR���ܿ��ƼĴ�����
 bit[7:2]    ����
 bit[1]      RXB����BLOCKING DCR����bypass���ơ�
             0��DCR���ܲ�bypasss��
             1��DCR����bypass��
 bit[0]      RXA����BLOCKING DCR����bypass���ơ�
             0��DCR���ܲ�bypasss��
             1��DCR����bypass��
   UNION�ṹ:  ABB_CH0_REG_RX_DCR_CTRL_UNION */
#define ABB_CH0_REG_RX_DCR_CTRL_ADDR                  (ABB_BASE_ADDR + 0x49A)

/* �Ĵ���˵����RXAͨ��BLOCKING�ϱ��Ĵ�����
 bit[7:5]    RXA����BLOCKING�ϱ�ֵ��ϵ��N��BLOCKING�ϱ����ΪN*2^M
 bit[4:0]    RXA����BLOCKING�ϱ�ֵ,2���ݴ�M
   UNION�ṹ:  ABB_CH0_RXA_BLOCKING_UNION */
#define ABB_CH0_RXA_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x49B)

/* �Ĵ���˵����RXBͨ��BLOCKING�ϱ��Ĵ�����
 bit[7:5]    RXB����BLOCKING�ϱ�ֵ��ϵ��N��BLOCKING�ϱ����ΪN*2^M
 bit[4:0]    RXB����BLOCKING�ϱ�ֵ,2���ݴ�M
   UNION�ṹ:  ABB_CH0_RXB_BLOCKING_UNION */
#define ABB_CH0_RXB_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x49C)

/* �Ĵ���˵����RXAͨ��I·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXA����I·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH0_REG_RXA_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x49D)

/* �Ĵ���˵����RXAͨ��I·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXA����I·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH0_REG_RXA_DC_I_2_UNION */
#define ABB_CH0_REG_RXA_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x49E)

/* �Ĵ���˵����RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH0_REG_RXA_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x49F)

/* �Ĵ���˵����RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH0_REG_RXA_DC_Q_2_UNION */
#define ABB_CH0_REG_RXA_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x4A0)

/* �Ĵ���˵����RXBͨ��I·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXB����I·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH0_REG_RXB_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x4A1)

/* �Ĵ���˵����RXBͨ��I·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXB����I·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH0_REG_RXB_DC_I_2_UNION */
#define ABB_CH0_REG_RXB_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x4A2)

/* �Ĵ���˵����RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH0_REG_RXB_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x4A3)

/* �Ĵ���˵����RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH0_REG_RXB_DC_Q_2_UNION */
#define ABB_CH0_REG_RXB_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x4A4)

/* �Ĵ���˵����ͨ��0���üĴ�����
   ��      ����ͨ��0 flush���[7:0]����λΪ19.2Mʱ�����ڡ�
   UNION�ṹ ���� */
#define ABB_CH0_FLUSH_CFG0_ADDR                       (ABB_BASE_ADDR + 0x4A5)

/* �Ĵ���˵����ͨ��0���üĴ�����
 bit[7:3]    ͨ��0 FLUSHֵ��Ĭ��Ϊ8��
 bit[2:0]    ͨ��0 flush���[10:8]����λΪ19.2Mʱ�����ڡ�
   UNION�ṹ:  ABB_CH0_FLUSH_CFG1_UNION */
#define ABB_CH0_FLUSH_CFG1_ADDR                       (ABB_BASE_ADDR + 0x4A6)

/* �Ĵ���˵����CH0ͨ��RXA HB�˲������档
   ��      ����CH0ͨ��RXA I· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH0_RXAI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4A7)

/* �Ĵ���˵����CH0ͨ��RXA HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH0ͨ��RXA I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH0_RXAI_HB_GAIN_2_UNION */
#define ABB_CH0_RXAI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4A8)

/* �Ĵ���˵����CH0ͨ��RXA HB�˲������档
   ��      ����CH0ͨ��RXA Q· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH0_RXAQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4A9)

/* �Ĵ���˵����CH0ͨ��RXA HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH0ͨ��RXA Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH0_RXAQ_HB_GAIN_2_UNION */
#define ABB_CH0_RXAQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4AA)

/* �Ĵ���˵����CH0ͨ��RXB HB�˲������档
   ��      ����CH0ͨ��RXB I· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH0_RXBI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4AB)

/* �Ĵ���˵����CH0ͨ��RXB HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH0ͨ��RXB I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH0_RXBI_HB_GAIN_2_UNION */
#define ABB_CH0_RXBI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4AC)

/* �Ĵ���˵����CH0ͨ��RXB HB�˲������档
   ��      ����CH0ͨ��RXB Q· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH0_RXBQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4AD)

/* �Ĵ���˵����CH0ͨ��RXB HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH0ͨ��RXB Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH0_RXBQ_HB_GAIN_2_UNION */
#define ABB_CH0_RXBQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4AE)

/* �Ĵ���˵����ͨ�����ƼĴ�����
 bit[7:2]    ����
 bit[1]      CH0ͨ��RXB������������źţ�0�����ز�����źţ�1������ͬʱ����źţ�
 bit[0]      CH0ͨ��RXA������������źţ�0�����ز�����źţ�1������ͬʱ����źţ�
   UNION�ṹ:  ABB_CH0_CTRL_UNION */
#define ABB_CH0_CTRL_ADDR                             (ABB_BASE_ADDR + 0x4AF)

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
#define ABB_CH0_RX_LINE_SEL_ADDR                      (ABB_BASE_ADDR + 0x4B0)

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
#define ABB_CH0_RX_LINE_CFG_ADDR                      (ABB_BASE_ADDR + 0x4B1)

/* �Ĵ���˵����blk���ƼĴ�����
 bit[7:3]    ����
 bit[2]      �߿��ź�CH0_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ʹ��
 bit[1]      �߿��ź�CH0_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ֵ
 bit[0]      BLOCKING�Զ��ſ�ʹ�ܣ�
             0��ʹ��
             1����ʹ��
   UNION�ṹ:  ABB_CH0_BLK_CFG_UNION */
#define ABB_CH0_BLK_CFG_ADDR                          (ABB_BASE_ADDR + 0x4B2)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
   ��      ��������
   UNION�ṹ ���� */
#define ABB_CH0_RX_LINE_RPT0_ADDR                     (ABB_BASE_ADDR + 0x4B3)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
   ��      ��������
   UNION�ṹ ���� */
#define ABB_CH0_RX_LINE_RPT1_ADDR                     (ABB_BASE_ADDR + 0x4B4)

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
#define ABB_CH0_RX_REG_DEBUG_DIG_ADDR                 (ABB_BASE_ADDR + 0x4B5)

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
 bit[3]
 bit[2]
 bit[1:0]
   UNION�ṹ:  ABB_CH1_PLL_SEL_UNION */
#define ABB_CH1_PLL_SEL_ADDR                          (ABB_BASE_ADDR + 0x4C1)

/* �Ĵ���˵����RX���ֹ���ģʽ�ϱ��Ĵ�����
   ��      ����RXͨ��ģʽ�����ϱ���
            000��2G(Ĭ��)
            001��3G_SC
            010��4G &amp; ET &amp; APT
            011��3G_DC
            100��TDS
            Others��CA
   UNION�ṹ ���� */
#define ABB_CH1_RX_MODE_RPT_ADDR                      (ABB_BASE_ADDR + 0x4C2)

/* �Ĵ���˵����RX���ֹ���״̬�ϱ��Ĵ�����
   ��      ��������
   UNION�ṹ ���� */
#define ABB_CH1_RX_STATE_RPT_ADDR                     (ABB_BASE_ADDR + 0x4C3)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXA_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4C4)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXAͨ��I·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXAͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH1_RXA_I_COEF1_UNION */
#define ABB_CH1_RXA_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x4C5)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH1_RXA_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x4C6)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXAͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH1_RXA_I_COEF3_UNION */
#define ABB_CH1_RXA_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x4C7)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXA_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x4C8)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��Q·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXA_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4C9)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXAͨ��Q·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXAͨ��Q·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH1_RXA_Q_COEF1_UNION */
#define ABB_CH1_RXA_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x4CA)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��Q·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH1_RXA_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x4CB)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXAͨ��Q·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH1_RXA_Q_COEF3_UNION */
#define ABB_CH1_RXA_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x4CC)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXAͨ��Q·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXA_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x4CD)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXB_I_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4CE)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXBͨ��I·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXBͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH1_RXB_I_COEF1_UNION */
#define ABB_CH1_RXB_I_COEF1_ADDR                      (ABB_BASE_ADDR + 0x4CF)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH1_RXB_I_COEF2_ADDR                      (ABB_BASE_ADDR + 0x4D0)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXBͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH1_RXB_I_COEF3_UNION */
#define ABB_CH1_RXB_I_COEF3_ADDR                      (ABB_BASE_ADDR + 0x4D1)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXB_I_COEF4_ADDR                      (ABB_BASE_ADDR + 0x4D2)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��Q·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXB_Q_COEF0_ADDR                      (ABB_BASE_ADDR + 0x4D3)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      RXBͨ��Q·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    RXBͨ��Q·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_CH1_RXB_Q_COEF1_UNION */
#define ABB_CH1_RXB_Q_COEF1_ADDR                      (ABB_BASE_ADDR + 0x4D4)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��Q·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_CH1_RXB_Q_COEF2_ADDR                      (ABB_BASE_ADDR + 0x4D5)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    RXBͨ��Q·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_CH1_RXB_Q_COEF3_UNION */
#define ABB_CH1_RXB_Q_COEF3_ADDR                      (ABB_BASE_ADDR + 0x4D6)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����RXBͨ��Q·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_CH1_RXB_Q_COEF4_ADDR                      (ABB_BASE_ADDR + 0x4D7)

/* �Ĵ���˵����RXAͨ��BLOCKING DCR���üĴ�����
 bit[7:5]    RXA����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ��
 bit[4:0]    RXA����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣
   UNION�ṹ:  ABB_CH1_REG_RXA_DCR_CFG_UNION */
#define ABB_CH1_REG_RXA_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x4D8)

/* �Ĵ���˵����RXBͨ��BLOCKING DCR���üĴ�����
 bit[7:5]    RXB����BLOCKING DCR �˲��������ٶ����á����÷�Χ0~7����Ӧ��ʾ�˲�����L����Ϊ8~15��ȡ�ϴ�ϵ������Ҫ����������ʱ�䣬�õ���С�Ĳ���DC���ֵ��
 bit[4:0]    RXB����BLOCKING DCR��������ʱ�����ã�ȡֵ��Χ0~19,��ʾ����ʱ����512~512*20�������㣬����Ϊ512�������㣬ÿ��������Ƶ��15.36MHz��DRC����ʱ��֮������Blocking�������㡣
   UNION�ṹ:  ABB_CH1_REG_RXB_DCR_CFG_UNION */
#define ABB_CH1_REG_RXB_DCR_CFG_ADDR                  (ABB_BASE_ADDR + 0x4D9)

/* �Ĵ���˵����BLOCKING DCR���ܿ��ƼĴ�����
 bit[7:2]    ����
 bit[1]      RXB����BLOCKING DCR����bypass���ơ�
             0��DCR���ܲ�bypasss��
             1��DCR����bypass��
 bit[0]      RXA����BLOCKING DCR����bypass���ơ�
             0��DCR���ܲ�bypasss��
             1��DCR����bypass��
   UNION�ṹ:  ABB_CH1_REG_RX_DCR_CTRL_UNION */
#define ABB_CH1_REG_RX_DCR_CTRL_ADDR                  (ABB_BASE_ADDR + 0x4DA)

/* �Ĵ���˵����RXAͨ��BLOCKING�ϱ��Ĵ�����
 bit[7:5]    RXA����BLOCKING�ϱ�ֵ��ϵ��N��BLOCKING�ϱ����ΪN*2^M
 bit[4:0]    RXA����BLOCKING�ϱ�ֵ,2���ݴ�M
   UNION�ṹ:  ABB_CH1_RXA_BLOCKING_UNION */
#define ABB_CH1_RXA_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x4DB)

/* �Ĵ���˵����RXBͨ��BLOCKING�ϱ��Ĵ�����
 bit[7:5]    RXB����BLOCKING�ϱ�ֵ��ϵ��N��BLOCKING�ϱ����ΪN*2^M
 bit[4:0]    RXB����BLOCKING�ϱ�ֵ,2���ݴ�M
   UNION�ṹ:  ABB_CH1_RXB_BLOCKING_UNION */
#define ABB_CH1_RXB_BLOCKING_ADDR                     (ABB_BASE_ADDR + 0x4DC)

/* �Ĵ���˵����RXAͨ��I·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXA����I·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH1_REG_RXA_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x4DD)

/* �Ĵ���˵����RXAͨ��I·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXA����I·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH1_REG_RXA_DC_I_2_UNION */
#define ABB_CH1_REG_RXA_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x4DE)

/* �Ĵ���˵����RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH1_REG_RXA_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x4DF)

/* �Ĵ���˵����RXAͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXA����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH1_REG_RXA_DC_Q_2_UNION */
#define ABB_CH1_REG_RXA_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x4E0)

/* �Ĵ���˵����RXBͨ��I·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXB����I·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH1_REG_RXB_DC_I_1_ADDR                   (ABB_BASE_ADDR + 0x4E1)

/* �Ĵ���˵����RXBͨ��I·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXB����I·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH1_REG_RXB_DC_I_2_UNION */
#define ABB_CH1_REG_RXB_DC_I_2_ADDR                   (ABB_BASE_ADDR + 0x4E2)

/* �Ĵ���˵����RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���1��
   ��      ����RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��8bit
   UNION�ṹ ���� */
#define ABB_CH1_REG_RXB_DC_Q_1_ADDR                   (ABB_BASE_ADDR + 0x4E3)

/* �Ĵ���˵����RXBͨ��Q·BLOCKING DC�ϱ��Ĵ���2��
 bit[7:4]    RXB����Q·�ź�BLOCKING DC�ϱ�ֵ��4bit
 bit[3:0]    ����
   UNION�ṹ:  ABB_CH1_REG_RXB_DC_Q_2_UNION */
#define ABB_CH1_REG_RXB_DC_Q_2_ADDR                   (ABB_BASE_ADDR + 0x4E4)

/* �Ĵ���˵����ͨ��1���üĴ�����
   ��      ����ͨ��1 flush���[7:0]����λΪ19.2Mʱ�����ڡ�
   UNION�ṹ ���� */
#define ABB_CH1_FLUSH_CFG0_ADDR                       (ABB_BASE_ADDR + 0x4E5)

/* �Ĵ���˵����ͨ��1���üĴ�����
 bit[7:3]    ͨ��1 FLUSHֵ��Ĭ��Ϊ8��
 bit[2:0]    ͨ��1 flush���[10:8]����λΪ19.2Mʱ�����ڡ�
   UNION�ṹ:  ABB_CH1_FLUSH_CFG1_UNION */
#define ABB_CH1_FLUSH_CFG1_ADDR                       (ABB_BASE_ADDR + 0x4E6)

/* �Ĵ���˵����CH1ͨ��RXA HB�˲������档
   ��      ����CH1ͨ��RXA I· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH1_RXAI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4E7)

/* �Ĵ���˵����CH1ͨ��RXA HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH1ͨ��RXA I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH1_RXAI_HB_GAIN_2_UNION */
#define ABB_CH1_RXAI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4E8)

/* �Ĵ���˵����CH1ͨ��RXA HB�˲������档
   ��      ����CH1ͨ��RXA Q· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH1_RXAQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4E9)

/* �Ĵ���˵����CH1ͨ��RXA HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH1ͨ��RXA Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH1_RXAQ_HB_GAIN_2_UNION */
#define ABB_CH1_RXAQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4EA)

/* �Ĵ���˵����CH1ͨ��RXB HB�˲������档
   ��      ����CH1ͨ��RXB I· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH1_RXBI_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4EB)

/* �Ĵ���˵����CH1ͨ��RXB HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH1ͨ��RXB I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH1_RXBI_HB_GAIN_2_UNION */
#define ABB_CH1_RXBI_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4EC)

/* �Ĵ���˵����CH1ͨ��RXB HB�˲������档
   ��      ����CH1ͨ��RXB Q· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_CH1_RXBQ_HB_GAIN_1_ADDR                   (ABB_BASE_ADDR + 0x4ED)

/* �Ĵ���˵����CH1ͨ��RXB HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH1ͨ��RXB Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_CH1_RXBQ_HB_GAIN_2_UNION */
#define ABB_CH1_RXBQ_HB_GAIN_2_ADDR                   (ABB_BASE_ADDR + 0x4EE)

/* �Ĵ���˵����ͨ�����ƼĴ�����
 bit[7:2]    ����
 bit[1]      CH1ͨ��RXB������������źţ�0�����ز�����źţ�1������ͬʱ����źţ�
 bit[0]      CH1ͨ��RXA������������źţ�0�����ز�����źţ�1������ͬʱ����źţ�
   UNION�ṹ:  ABB_CH1_CTRL_UNION */
#define ABB_CH1_CTRL_ADDR                             (ABB_BASE_ADDR + 0x4EF)

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
#define ABB_CH1_RX_LINE_SEL_ADDR                      (ABB_BASE_ADDR + 0x4F0)

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
#define ABB_CH1_RX_LINE_CFG_ADDR                      (ABB_BASE_ADDR + 0x4F1)

/* �Ĵ���˵����blk���ƼĴ�����
 bit[7:3]    ����
 bit[2]      �߿��ź�CH1_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ʹ��
 bit[1]      �߿��ź�CH1_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ֵ
 bit[0]      BLOCKING�Զ��ſ�ʹ�ܣ�
             0��ʹ��
             1����ʹ��
   UNION�ṹ:  ABB_CH1_BLK_CFG_UNION */
#define ABB_CH1_BLK_CFG_ADDR                          (ABB_BASE_ADDR + 0x4F2)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
   ��      ��������
   UNION�ṹ ���� */
#define ABB_CH1_RX_LINE_RPT0_ADDR                     (ABB_BASE_ADDR + 0x4F3)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
   ��      ��������
   UNION�ṹ ���� */
#define ABB_CH1_RX_LINE_RPT1_ADDR                     (ABB_BASE_ADDR + 0x4F4)

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
#define ABB_CH1_RX_REG_DEBUG_DIG_ADDR                 (ABB_BASE_ADDR + 0x4F5)

/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define ABB_MEM_CTRL_MSB_ADDR                         (ABB_BASE_ADDR + 0x600)

/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define ABB_MEM_CTRL_LSB_ADDR                         (ABB_BASE_ADDR + 0x601)

/* �Ĵ���˵����
 bit[7:1]    ����
 bit[0]
   UNION�ṹ:  ABB_DEBUG_RESET_UNION */
#define ABB_DEBUG_RESET_ADDR                          (ABB_BASE_ADDR + 0x602)

/* �Ĵ���˵����
 bit[7:6]    ����
 bit[5]
 bit[4]
 bit[3:2]
 bit[1:0]
   UNION�ṹ:  ABB_DEBUG_CHANNEL_SEL_UNION */
#define ABB_DEBUG_CHANNEL_SEL_ADDR                    (ABB_BASE_ADDR + 0x603)

/* �Ĵ���˵����
 bit[7:1]    ����
 bit[0]
   UNION�ṹ:  ABB_DEBUG_RAM_EN_UNION */
#define ABB_DEBUG_RAM_EN_ADDR                         (ABB_BASE_ADDR + 0x604)

/* �Ĵ���˵����
 bit[7:3]    ����
 bit[2]
 bit[1]
 bit[0]
   UNION�ṹ:  ABB_DEBUG_RAM_CFG_UNION */
#define ABB_DEBUG_RAM_CFG_ADDR                        (ABB_BASE_ADDR + 0x605)

/* �Ĵ���˵����
 bit[7:3]    ����
 bit[2]
 bit[1]      ����
 bit[0]
   UNION�ṹ:  ABB_DEBUG_RAM_RPT1_UNION */
#define ABB_DEBUG_RAM_RPT1_ADDR                       (ABB_BASE_ADDR + 0x606)

/* �Ĵ���˵����
 bit[7]      ����
 bit[6:0]
   UNION�ṹ:  ABB_DEBUG_RAM_RPT2_UNION */
#define ABB_DEBUG_RAM_RPT2_ADDR                       (ABB_BASE_ADDR + 0x607)

/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define ABB_DEBUG_RAM_RPT3_ADDR                       (ABB_BASE_ADDR + 0x608)

/* �Ĵ���˵����
 bit[7]      ����
 bit[6:0]
   UNION�ṹ:  ABB_DEBUG_RAM_RPT4_UNION */
#define ABB_DEBUG_RAM_RPT4_ADDR                       (ABB_BASE_ADDR + 0x609)

/* �Ĵ���˵����
   ��      ����
   UNION�ṹ ���� */
#define ABB_DEBUG_RAM_RPT5_ADDR                       (ABB_BASE_ADDR + 0x60A)

/* �Ĵ���˵����RX IDLEģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G_A(Ĭ��)
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             110��CA
             111��2G_B
 bit[4:3]    ����
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      {sar_comp_sel_b1,sar_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11���̶�ϵ��4��
   UNION�ṹ:  ABB_SAR_DIG_1_UNION */
#define ABB_SAR_DIG_1_ADDR                            (ABB_BASE_ADDR + 0x680)

/* �Ĵ���˵����RX IDLEģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      {sar_comp_sel_b1,sar_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�sar_comp_sel_b0˵����
 bit[6]      ����
 bit[5]      RXͨ����·ʱ��SAR_CLK����ʹ�ܣ�
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
 bit[1]      ����
 bit[0]      SARͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!sar_pd)|XX_SAR_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_SAR_DIG_2_UNION */
#define ABB_SAR_DIG_2_ADDR                            (ABB_BASE_ADDR + 0x681)

/* �Ĵ���˵��������ģʽ�Ĵ���
 bit[7:2]    ����
 bit[1]
 bit[0]      ���ֲ���RXͨ����λ�źţ�
             0������λ(Ĭ��)
             1����λ
   UNION�ṹ:  ABB_SAR_TESTMODE_UNION */
#define ABB_SAR_TESTMODE_ADDR                         (ABB_BASE_ADDR + 0x682)

/* �Ĵ���˵����PLLѡ��Ĵ���
 bit[7:4]    ����
 bit[3]
 bit[2]
 bit[1:0]
   UNION�ṹ:  ABB_SAR_PLL_SEL_UNION */
#define ABB_SAR_PLL_SEL_ADDR                          (ABB_BASE_ADDR + 0x683)

/* �Ĵ���˵����RX���ֹ���ģʽ�ϱ��Ĵ�����
   ��      ����RXͨ��ģʽ���ƣ�
            000��2G(Ĭ��)
            001��3G_SC/TDS_B/4G_C
            010��4G
            011��3G_DC/4G_B
            100��TDS
            101��CDMA
            Others��Reserved
   UNION�ṹ ���� */
#define ABB_SAR_MODE_RPT_ADDR                         (ABB_BASE_ADDR + 0x684)

/* �Ĵ���˵����RX���ֹ���״̬�ϱ��Ĵ�����
   ��      ��������
   UNION�ṹ ���� */
#define ABB_SAR_STATE_RPT_ADDR                        (ABB_BASE_ADDR + 0x685)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����SARͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_SAR_I_COEF0_ADDR                          (ABB_BASE_ADDR + 0x686)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      SARͨ��I·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    SARͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_SAR_I_COEF1_UNION */
#define ABB_SAR_I_COEF1_ADDR                          (ABB_BASE_ADDR + 0x687)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����SARͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_SAR_I_COEF2_ADDR                          (ABB_BASE_ADDR + 0x688)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    SARͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_SAR_I_COEF3_UNION */
#define ABB_SAR_I_COEF3_ADDR                          (ABB_BASE_ADDR + 0x689)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����SARͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_SAR_I_COEF4_ADDR                          (ABB_BASE_ADDR + 0x68A)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����SARͨ��Q·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_SAR_Q_COEF0_ADDR                          (ABB_BASE_ADDR + 0x68B)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      SARͨ��Q·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    SARͨ��Q·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_SAR_Q_COEF1_UNION */
#define ABB_SAR_Q_COEF1_ADDR                          (ABB_BASE_ADDR + 0x68C)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����SARͨ��Q·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_SAR_Q_COEF2_ADDR                          (ABB_BASE_ADDR + 0x68D)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    SARͨ��Q·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_SAR_Q_COEF3_UNION */
#define ABB_SAR_Q_COEF3_ADDR                          (ABB_BASE_ADDR + 0x68E)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����SARͨ��Q·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_SAR_Q_COEF4_ADDR                          (ABB_BASE_ADDR + 0x68F)

/* �Ĵ���˵����CH0ͨ��SAR HB�˲������档
   ��      ����CH0ͨ��SAR I· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_SARI_HB_GAIN_1_ADDR                       (ABB_BASE_ADDR + 0x690)

/* �Ĵ���˵����CH0ͨ��SAR HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH0ͨ��SAR I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_SARI_HB_GAIN_2_UNION */
#define ABB_SARI_HB_GAIN_2_ADDR                       (ABB_BASE_ADDR + 0x691)

/* �Ĵ���˵����CH0ͨ��SAR HB�˲������档
   ��      ����CH0ͨ��SAR Q· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_SARQ_HB_GAIN_1_ADDR                       (ABB_BASE_ADDR + 0x692)

/* �Ĵ���˵����CH0ͨ��SAR HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH0ͨ��SAR Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_SARQ_HB_GAIN_2_UNION */
#define ABB_SARQ_HB_GAIN_2_ADDR                       (ABB_BASE_ADDR + 0x693)

/* �Ĵ���˵����ͨ�����ƼĴ�����
 bit[7:2]    ����
 bit[1]      ����
 bit[0]      CH0ͨ��SAR������������źţ�0�����ز�����źţ�1������ͬʱ����źţ�
   UNION�ṹ:  ABB_SAR_CTRL_UNION */
#define ABB_SAR_CTRL_ADDR                             (ABB_BASE_ADDR + 0x694)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
   ��      ��������
   UNION�ṹ ���� */
#define ABB_SAR_LINE_RPT0_ADDR                        (ABB_BASE_ADDR + 0x695)

/* �Ĵ���˵�������ֵ��ԼĴ�����
 bit[7]      bit[7]��ģʽ�л���λ��������ʹ��
             0����ʹ��
             1��ʹ��
 bit[6:4]    ģʽ�л���λ��������ֵ����λΪ8 cycles
 bit[3:1]    ����
 bit[0]      RX��Ƶ��ʹ��bypass����
             0����bypass
             1��bypass
   UNION�ṹ:  ABB_SAR_REG_DEBUG_DIG_UNION */
#define ABB_SAR_REG_DEBUG_DIG_ADDR                    (ABB_BASE_ADDR + 0x696)

/* �Ĵ���˵����RX IDLEģʽ���üĴ���1�����߿ؾ����Ƿ������á�
 bit[7:5]    RXͨ��ģʽ���ƣ�
             000��2G_A(Ĭ��)
             001��3G_SC/TDS_B/4G_C
             010��4G
             011��3G_DC/4G_B
             100��TDS
             101��CDMA
             110��CA
             111��2G_B
 bit[4:3]    ����
 bit[2]      RXͨ������˲���bypass���ƣ�
             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate
 bit[1]      RXͨ�������˲�������ϵ���̶����ƣ�
             0��ϵ�����̶����ɼĴ�������
             1��ϵ���̶�
 bit[0]      {n50m_comp_sel_b1,n50m_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
             00���̶�ϵ��1��
             01���̶�ϵ��2��
             10���̶�ϵ��3��
             11���̶�ϵ��4��
   UNION�ṹ:  ABB_N50M_DIG_1_UNION */
#define ABB_N50M_DIG_1_ADDR                           (ABB_BASE_ADDR + 0x6B0)

/* �Ĵ���˵����RX IDLEģʽ���üĴ���2�����߿ؾ����Ƿ������á�
 bit[7]      {n50m_comp_sel_b1,n50m_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�n50m_comp_sel_b0˵����
 bit[6]      ����
 bit[5]      RXͨ����·ʱ��N50M_CLK����ʹ�ܣ�
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
 bit[1]      ����
 bit[0]      N50Mͨ��CLOCK GATING���ƣ�
             0����CLOCK GATING
             1��CLOCK GATING(Ĭ��)
             (!n50m_pd)|XX_N50M_EN = 1ʱ����������ر�
   UNION�ṹ:  ABB_N50M_DIG_2_UNION */
#define ABB_N50M_DIG_2_ADDR                           (ABB_BASE_ADDR + 0x6B1)

/* �Ĵ���˵��������ģʽ�Ĵ���
 bit[7:2]    ����
 bit[1]
 bit[0]      ���ֲ���RXͨ����λ�źţ�
             0������λ(Ĭ��)
             1����λ
   UNION�ṹ:  ABB_N50M_TESTMODE_UNION */
#define ABB_N50M_TESTMODE_ADDR                        (ABB_BASE_ADDR + 0x6B2)

/* �Ĵ���˵����PLLѡ��Ĵ���
 bit[7:4]    ����
 bit[3]
 bit[2]
 bit[1:0]
   UNION�ṹ:  ABB_N50M_PLL_SEL_UNION */
#define ABB_N50M_PLL_SEL_ADDR                         (ABB_BASE_ADDR + 0x6B3)

/* �Ĵ���˵����RX���ֹ���ģʽ�ϱ��Ĵ�����
   ��      ����RXͨ��ģʽ���ƣ�
            000��2G(Ĭ��)
            001��3G_SC/TDS_B/4G_C
            010��4G
            011��3G_DC/4G_B
            100��TDS
            101��CDMA
            Others��Reserved
   UNION�ṹ ���� */
#define ABB_N50M_MODE_RPT_ADDR                        (ABB_BASE_ADDR + 0x6B4)

/* �Ĵ���˵����RX���ֹ���״̬�ϱ��Ĵ�����
   ��      ��������
   UNION�ṹ ���� */
#define ABB_N50M_STATE_RPT_ADDR                       (ABB_BASE_ADDR + 0x6B5)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����N50Mͨ��I·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_N50M_I_COEF0_ADDR                         (ABB_BASE_ADDR + 0x6B6)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      N50Mͨ��I·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    N50Mͨ��I·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_N50M_I_COEF1_UNION */
#define ABB_N50M_I_COEF1_ADDR                         (ABB_BASE_ADDR + 0x6B7)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����N50Mͨ��I·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_N50M_I_COEF2_ADDR                         (ABB_BASE_ADDR + 0x6B8)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    N50Mͨ��I·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_N50M_I_COEF3_UNION */
#define ABB_N50M_I_COEF3_ADDR                         (ABB_BASE_ADDR + 0x6B9)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����N50Mͨ��I·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_N50M_I_COEF4_ADDR                         (ABB_BASE_ADDR + 0x6BA)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����N50Mͨ��Q·�����˲���ϵ��C0,�з�����
   UNION�ṹ ���� */
#define ABB_N50M_Q_COEF0_ADDR                         (ABB_BASE_ADDR + 0x6BB)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      N50Mͨ��Q·�����˲���ϵ��C3,�޷�����,���λ
 bit[6:0]    N50Mͨ��Q·�����˲���ϵ��C1,�з�����
   UNION�ṹ:  ABB_N50M_Q_COEF1_UNION */
#define ABB_N50M_Q_COEF1_ADDR                         (ABB_BASE_ADDR + 0x6BC)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����N50Mͨ��Q·�����˲���ϵ��C3,�޷�����,��8λ
   UNION�ṹ ���� */
#define ABB_N50M_Q_COEF2_ADDR                         (ABB_BASE_ADDR + 0x6BD)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
 bit[7]      ����
 bit[6:0]    N50Mͨ��Q·�����˲���ϵ��C5,�з�����
   UNION�ṹ:  ABB_N50M_Q_COEF3_UNION */
#define ABB_N50M_Q_COEF3_ADDR                         (ABB_BASE_ADDR + 0x6BE)

/* �Ĵ���˵����RXͨ������ϵ���Ĵ�����
   ��      ����N50Mͨ��Q·�����˲���ϵ��C6,�з�����
   UNION�ṹ ���� */
#define ABB_N50M_Q_COEF4_ADDR                         (ABB_BASE_ADDR + 0x6BF)

/* �Ĵ���˵����CH0ͨ��N50M HB�˲������档
   ��      ����CH0ͨ��N50M I· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_N50MI_HB_GAIN_1_ADDR                      (ABB_BASE_ADDR + 0x6C0)

/* �Ĵ���˵����CH0ͨ��N50M HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH0ͨ��N50M I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_N50MI_HB_GAIN_2_UNION */
#define ABB_N50MI_HB_GAIN_2_ADDR                      (ABB_BASE_ADDR + 0x6C1)

/* �Ĵ���˵����CH0ͨ��N50M HB�˲������档
   ��      ����CH0ͨ��N50M Q· HB�˲������棨10u���ĵ�8bit������Ĭ��ֵ512��
   UNION�ṹ ���� */
#define ABB_N50MQ_HB_GAIN_1_ADDR                      (ABB_BASE_ADDR + 0x6C2)

/* �Ĵ���˵����CH0ͨ��N50M HB�˲������档
 bit[7:2]    ����
 bit[1:0]    CH0ͨ��N50M Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512��
   UNION�ṹ:  ABB_N50MQ_HB_GAIN_2_UNION */
#define ABB_N50MQ_HB_GAIN_2_ADDR                      (ABB_BASE_ADDR + 0x6C3)

/* �Ĵ���˵����ͨ�����ƼĴ�����
 bit[7:2]    ����
 bit[1]      ����
 bit[0]      CH0ͨ��N50M������������źţ�0�����ز�����źţ�1������ͬʱ����źţ�
   UNION�ṹ:  ABB_N50M_CTRL_UNION */
#define ABB_N50M_CTRL_ADDR                            (ABB_BASE_ADDR + 0x6C4)

/* �Ĵ���˵�����߿�״̬�ϱ��Ĵ�����
   ��      ��������
   UNION�ṹ ���� */
#define ABB_N50M_LINE_RPT0_ADDR                       (ABB_BASE_ADDR + 0x6C5)

/* �Ĵ���˵�������ֵ��ԼĴ�����
 bit[7]      bit[7]��ģʽ�л���λ��������ʹ��
             0����ʹ��
             1��ʹ��
 bit[6:4]    ģʽ�л���λ��������ֵ����λΪ8 cycles
 bit[3:1]    ����
 bit[0]      RX��Ƶ��ʹ��bypass����
             0����bypass
             1��bypass
   UNION�ṹ:  ABB_N50M_REG_DEBUG_DIG_UNION */
#define ABB_N50M_REG_DEBUG_DIG_ADDR                   (ABB_BASE_ADDR + 0x6C6)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7] reserved
            [6] ADPLL_CLK_PAD_EN��adpll1����ʱ��ʹ��
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR00_ADDR                      (ABB_BASE_ADDR + 0x800)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:3] reserved
            [2:0] GPLL_SEL��gpllʱ��ѡ��
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR01_ADDR                      (ABB_BASE_ADDR + 0x801)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7] SC1_245M_SEL��scpll1 245M ʱ��ѡ��
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR02_ADDR                      (ABB_BASE_ADDR + 0x802)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:6] reserved
            [5] ADPLL_FREF_SEL��adpllʱ�Ӳο�ѡ��
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR03_ADDR                      (ABB_BASE_ADDR + 0x803)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7] GPLL_CLK104M_PD gpll 245Mʱ��power down����
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR04_ADDR                      (ABB_BASE_ADDR + 0x804)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7] WPLL_CLK245M_PD wpll 245Mʱ��power down����
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR05_ADDR                      (ABB_BASE_ADDR + 0x805)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:6] reserved
            [5] CH0_DAC_CLK_EN��ch0 dacʱ�����ʹ��
                  0��ʱ�ӹر�
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR06_ADDR                      (ABB_BASE_ADDR + 0x806)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:6] reserved
            [5] CH1_DAC_CLK_EN��ch1 dacʱ�����ʹ��
                  0��ʱ�ӹر�
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR07_ADDR                      (ABB_BASE_ADDR + 0x807)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:5] reserved
            [4] CH1_ADC_CLK_EN��ch1 adcʱ�����ʹ��
                  0��ʱ�ӹر�
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR08_ADDR                      (ABB_BASE_ADDR + 0x808)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:6] reserved
            [5] PD_TCXO1��tcxo1 power down����
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR09_ADDR                      (ABB_BASE_ADDR + 0x809)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:5] reserved
            [4] EXCLK_PD�����ʱ��power down����
                  0�������ʱ��ģ��
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR10_ADDR                      (ABB_BASE_ADDR + 0x80A)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:6] reserved
            [5:4] WG_VCSEL��wpll/gpll vc��ѹѡ��
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR11_ADDR                      (ABB_BASE_ADDR + 0x80B)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:5] reserved
            [4] REF_FS��ref������������
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR12_ADDR                      (ABB_BASE_ADDR + 0x80C)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:5] reserved
            [4] RCTUNE_CAP_SEL��rctune����ѡ��
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR13_ADDR                      (ABB_BASE_ADDR + 0x80D)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:6] reserved
            [5] CH3_SE_VCM_SEL��ch3����ģʽ��ģѡ��
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR14_ADDR                      (ABB_BASE_ADDR + 0x80E)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR15_ADDR                      (ABB_BASE_ADDR + 0x80F)

/* �Ĵ���˵����TX RCTUNE���üĴ���
   ��      ����[7] reversed
            [6:0] TX_RCTUNE ��TX TUNE RCУ׼ֵ
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR16_ADDR                      (ABB_BASE_ADDR + 0x810)

/* �Ĵ���˵����RX RCTUNE���üĴ���
   ��      ����[7] reversed
            [6:0] RX_RCTUNE ��RX TUNE RCУ׼ֵ
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR17_ADDR                      (ABB_BASE_ADDR + 0x811)

/* �Ĵ���˵����CH3 RX RCTUNE���üĴ���
   ��      ����[7] reversed
            [6:0] CH3_RX_RCTUNE ��CH3 RX TUNE RCУ׼ֵ
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR18_ADDR                      (ABB_BASE_ADDR + 0x812)

/* �Ĵ���˵����ET RCTUNE���üĴ���
   ��      ����[7] reversed
            [6:0] ET_RCTUNE ��ET TUNE RCУ׼ֵ
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR19_ADDR                      (ABB_BASE_ADDR + 0x813)

/* �Ĵ���˵����ģ��common��д�Ĵ���
 bit[7:5]    ����
 bit[4]
 bit[3]
 bit[2]
 bit[1]
 bit[0]
   UNION�ṹ:  ABB_ANA_COMMON_WR20_UNION */
#define ABB_ANA_COMMON_WR20_ADDR                      (ABB_BASE_ADDR + 0x814)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR21_ADDR                      (ABB_BASE_ADDR + 0x815)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR22_ADDR                      (ABB_BASE_ADDR + 0x816)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR23_ADDR                      (ABB_BASE_ADDR + 0x817)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR24_ADDR                      (ABB_BASE_ADDR + 0x818)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR25_ADDR                      (ABB_BASE_ADDR + 0x819)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR26_ADDR                      (ABB_BASE_ADDR + 0x81A)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR27_ADDR                      (ABB_BASE_ADDR + 0x81B)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR28_ADDR                      (ABB_BASE_ADDR + 0x81C)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR29_ADDR                      (ABB_BASE_ADDR + 0x81D)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR30_ADDR                      (ABB_BASE_ADDR + 0x81E)

/* �Ĵ���˵����ģ��common��д�Ĵ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_WR31_ADDR                      (ABB_BASE_ADDR + 0x81F)

/* �Ĵ���˵����ģ��commonֻ���Ĵ���
   ��      ����[7:1] reversed
            [0]  RC_TUNE_READY ��RCУ׼����ź�
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_RO00_ADDR                      (ABB_BASE_ADDR + 0x830)

/* �Ĵ���˵����ģ��commonֻ���Ĵ���
   ��      ����[7] reversed
            [6:0] RC_TUNE_DOUT ��RCУ׼ֵ
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_RO01_ADDR                      (ABB_BASE_ADDR + 0x831)

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
#define ABB_ANA_COMMON_RO02_ADDR                      (ABB_BASE_ADDR + 0x832)

/* �Ĵ���˵����ģ��commonֻ���Ĵ���
   ��      ����[7:6] reserved
            [5] CH3_OPCAL_OK_RXC_Q��ch3 rxc q·op1У׼����ź�
            [4] CH3_OPCAL_OK_RXC_I��ch3 rxc i·op1У׼����ź�
            [3] CH3_OPCAL_OK_RXB_Q��ch3 rxb q·op1У׼����ź�
            [2] CH3_OPCAL_OK_RXB_I��ch3 rxb i·op1У׼����ź�
            [1] CH3_OPCAL_OK_RXA_Q��ch3 rxa q·op1У׼����ź�
            [0] CH3_OPCAL_OK_RXA_I��ch3 rxa i·op1У׼����ź�
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_RO03_ADDR                      (ABB_BASE_ADDR + 0x833)

/* �Ĵ���˵����ģ��commonֻ���Ĵ���
   ��      ����[7:2] reserved
            [1] WPLL_LOCK_FLAG��wpll�����ź�
            [0] GPLL_LOCK_FLAG��gpll�����ź�
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_RO04_ADDR                      (ABB_BASE_ADDR + 0x834)

/* �Ĵ���˵����ģ��commonֻ���Ĵ���
   ��      ����[7:0] reserved tielow
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_RO05_ADDR                      (ABB_BASE_ADDR + 0x835)

/* �Ĵ���˵����ģ��commonֻ���Ĵ���
   ��      ����[7:0] reserved tielow
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_RO06_ADDR                      (ABB_BASE_ADDR + 0x836)

/* �Ĵ���˵����ģ��commonֻ���Ĵ���
   ��      ����[7:0] reserved tielow
   UNION�ṹ ���� */
#define ABB_ANA_COMMON_RO07_ADDR                      (ABB_BASE_ADDR + 0x837)

/* �Ĵ���˵����ETģʽ���üĴ����������߿��߼�������
   ��      ����[7:6] reserved
            [5]��ET_CLK_SEL��ѡ��CH0����CH1֧��ET��
   UNION�ṹ ���� */
#define ABB_ET_ET_ANA_1_ADDR                          (ABB_BASE_ADDR + 0x900)

/* �Ĵ���˵����ETģʽ���üĴ����������߿��߼�������
   ��      ����[7:1] reserved
            [0]   et_vcm_sel��ET VCMѡ��
                  0:0.9V      1:0.9V
   UNION�ṹ ���� */
#define ABB_ET_ET_ANA_2_ADDR                          (ABB_BASE_ADDR + 0x901)

/* �Ĵ���˵����APTģʽ���üĴ����������߿��߼�������
   ��      ����[7:6] reserved
            [5]��ET_CLK_SEL��ѡ��CH0����CH1֧��ET��
   UNION�ṹ ���� */
#define ABB_ET_APT_ANA_1_ADDR                         (ABB_BASE_ADDR + 0x902)

/* �Ĵ���˵����APTģʽ���üĴ����������߿��߼�������
   ��      ����[7:1] reserved
            [0]   et_vcm_sel��ET VCMѡ��
                  0:0.9V      1:0.9V
   UNION�ṹ ���� */
#define ABB_ET_APT_ANA_2_ADDR                         (ABB_BASE_ADDR + 0x903)

/* �Ĵ���˵����ETģʽ���üĴ����������߿��߼�������
   ��      ����[7:6] reserved
            [5]��ET_CLK_SEL��ѡ��CH0����CH1֧��ET��
   UNION�ṹ ���� */
#define ABB_ET_IDLE_ANA_1_ADDR                        (ABB_BASE_ADDR + 0x904)

/* �Ĵ���˵����ETģʽ���üĴ����������߿��߼�������
   ��      ����[7:1] reserved
            [0]   et_vcm_sel��ET VCMѡ��
                  0:0.9V      1:0.9V
   UNION�ṹ ���� */
#define ABB_ET_IDLE_ANA_2_ADDR                        (ABB_BASE_ADDR + 0x905)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH0_PD_TX_I��ch0 tx i·power down����
                  0: power ON
   UNION�ṹ ���� */
#define ABB_CH0_TX_2G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA00)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR01
   ��      ����[7:6] reserved
            [5:4] CH0_TX_FC��ch0 tx fcѡ��
                  00��20MHz
                  01��40MHz  CAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_TX_2G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA01)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR02
   ��      ����[7] CH0_TX_CLKD_CTRL��ch0 tx����ʱ�ӿ���
   UNION�ṹ ���� */
#define ABB_CH0_TX_2G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA02)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR03
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_2G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA03)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_2G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA04)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_2G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA05)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_2G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA06)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_2G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xA07)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH0_PD_TX_I��ch0 tx i·power down����
                  0: power ON
   UNION�ṹ ���� */
#define ABB_CH0_TX_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA08)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR01
   ��      ����[7:6] reserved
            [5:4] CH0_TX_FC��ch0 tx fcѡ��
                  00��20MHz
                  01��40MHz  CAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_TX_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA09)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR02
   ��      ����[7] CH0_TX_CLKD_CTRL��ch0 tx����ʱ�ӿ���
   UNION�ṹ ���� */
#define ABB_CH0_TX_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA0A)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR03
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA0B)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA0C)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA0D)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA0E)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_3G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xA0F)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH0_PD_TX_I��ch0 tx i·power down����
                  0: power ON
   UNION�ṹ ���� */
#define ABB_CH0_TX_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA10)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR01
   ��      ����[7:6] reserved
            [5:4] CH0_TX_FC��ch0 tx fcѡ��
                  00��20MHz
                  01��40MHz  CAģʽ
                  10��10MHz  ����ģʽ
   UNION�ṹ ���� */
#define ABB_CH0_TX_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA11)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR02
   ��      ����[7] CH0_TX_CLKD_CTRL��ch0 tx����ʱ�ӿ���
   UNION�ṹ ���� */
#define ABB_CH0_TX_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA12)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR03
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA13)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA14)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA15)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA16)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_4G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xA17)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH0_PD_TX_I��ch0 tx i·power down����
                  0: power ON
   UNION�ṹ ���� */
#define ABB_CH0_TX_TDS_ANA_1_ADDR                     (ABB_BASE_ADDR + 0xA18)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR01
   ��      ����[7:6] reserved
            [5:4] CH0_TX_FC��ch0 tx fcѡ��
                  00��20MHz
                  01��40MHz  CAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_TX_TDS_ANA_2_ADDR                     (ABB_BASE_ADDR + 0xA19)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR02
   ��      ����[7] CH0_TX_CLKD_CTRL��ch0 tx����ʱ�ӿ���
   UNION�ṹ ���� */
#define ABB_CH0_TX_TDS_ANA_3_ADDR                     (ABB_BASE_ADDR + 0xA1A)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR03
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_TDS_ANA_4_ADDR                     (ABB_BASE_ADDR + 0xA1B)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_TDS_ANA_5_ADDR                     (ABB_BASE_ADDR + 0xA1C)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_TDS_ANA_6_ADDR                     (ABB_BASE_ADDR + 0xA1D)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_TDS_ANA_7_ADDR                     (ABB_BASE_ADDR + 0xA1E)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_TDS_ANA_8_ADDR                     (ABB_BASE_ADDR + 0xA1F)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH0_PD_TX_I��ch0 tx i·power down����
                  0: power ON
   UNION�ṹ ���� */
#define ABB_CH0_TX_X_ANA_1_ADDR                       (ABB_BASE_ADDR + 0xA20)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR01
   ��      ����[7:6] reserved
            [5:4] CH0_TX_FC��ch0 tx fcѡ��
                  00��20MHz
                  01��40MHz  CAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_TX_X_ANA_2_ADDR                       (ABB_BASE_ADDR + 0xA21)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR02
   ��      ����[7] CH0_TX_CLKD_CTRL��ch0 tx����ʱ�ӿ���
   UNION�ṹ ���� */
#define ABB_CH0_TX_X_ANA_3_ADDR                       (ABB_BASE_ADDR + 0xA22)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR03
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_X_ANA_4_ADDR                       (ABB_BASE_ADDR + 0xA23)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_X_ANA_5_ADDR                       (ABB_BASE_ADDR + 0xA24)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_X_ANA_6_ADDR                       (ABB_BASE_ADDR + 0xA25)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_X_ANA_7_ADDR                       (ABB_BASE_ADDR + 0xA26)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_X_ANA_8_ADDR                       (ABB_BASE_ADDR + 0xA27)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH0_PD_TX_I��ch0 tx i·power down����
                  0: power ON
   UNION�ṹ ���� */
#define ABB_CH0_TX_IDLE_ANA_1_ADDR                    (ABB_BASE_ADDR + 0xA28)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR01
   ��      ����[7:6] reserved
            [5:4] CH0_TX_FC��ch0 tx fcѡ��
                  00��20MHz
                  01��40MHz  CAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_TX_IDLE_ANA_2_ADDR                    (ABB_BASE_ADDR + 0xA29)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR02
   ��      ����[7] CH0_TX_CLKD_CTRL��ch0 tx����ʱ�ӿ���
   UNION�ṹ ���� */
#define ABB_CH0_TX_IDLE_ANA_3_ADDR                    (ABB_BASE_ADDR + 0xA2A)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR03
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_IDLE_ANA_4_ADDR                    (ABB_BASE_ADDR + 0xA2B)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_IDLE_ANA_5_ADDR                    (ABB_BASE_ADDR + 0xA2C)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_IDLE_ANA_6_ADDR                    (ABB_BASE_ADDR + 0xA2D)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_IDLE_ANA_7_ADDR                    (ABB_BASE_ADDR + 0xA2E)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_TX_IDLE_ANA_8_ADDR                    (ABB_BASE_ADDR + 0xA2F)

/* �Ĵ���˵����TX ch0���üĴ���
   ��      ����[7:6] reserved
            [5] CH0_TX_DUM_EN_I��ch0 tx i channel dummy logic control signal
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA00_ADDR                  (ABB_BASE_ADDR + 0xA30)

/* �Ĵ���˵����TX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA01_ADDR                  (ABB_BASE_ADDR + 0xA31)

/* �Ĵ���˵����TX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA02_ADDR                  (ABB_BASE_ADDR + 0xA32)

/* �Ĵ���˵����TX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA03_ADDR                  (ABB_BASE_ADDR + 0xA33)

/* �Ĵ���˵����TX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA04_ADDR                  (ABB_BASE_ADDR + 0xA34)

/* �Ĵ���˵����TX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA05_ADDR                  (ABB_BASE_ADDR + 0xA35)

/* �Ĵ���˵����TX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA06_ADDR                  (ABB_BASE_ADDR + 0xA36)

/* �Ĵ���˵����TX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA07_ADDR                  (ABB_BASE_ADDR + 0xA37)

/* �Ĵ���˵����TX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA08_ADDR                  (ABB_BASE_ADDR + 0xA38)

/* �Ĵ���˵����TX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA09_ADDR                  (ABB_BASE_ADDR + 0xA39)

/* �Ĵ���˵����TX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA10_ADDR                  (ABB_BASE_ADDR + 0xA3A)

/* �Ĵ���˵����TX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA11_ADDR                  (ABB_BASE_ADDR + 0xA3B)

/* �Ĵ���˵����TX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA12_ADDR                  (ABB_BASE_ADDR + 0xA3C)

/* �Ĵ���˵����TX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA13_ADDR                  (ABB_BASE_ADDR + 0xA3D)

/* �Ĵ���˵����TX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA14_ADDR                  (ABB_BASE_ADDR + 0xA3E)

/* �Ĵ���˵����TX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA15_ADDR                  (ABB_BASE_ADDR + 0xA3F)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH1_PD_TX_I��ch1 tx i·power down����
                  0: power ON
                 1: power DOWN��Ĭ�ϣ�
            [4] CH1_PD_TX_Q��ch1 tx q·power down����
                  0: power ON
                 1: power DOWN��Ĭ�ϣ�
            [3] reserved
            [2:0] CH1_TX_MODE��ch1 txģʽѡ��
                  000: LTE(614.4M)
                  001: 3G(307.2M)
                  010: CA(614.4M)
                  011: 2G(156M)��Ĭ�ϣ�
                  100: X(245.76M)
   UNION�ṹ ���� */
#define ABB_CH1_TX_2G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA40)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR01
   ��      ����[7:6] reserved
            [5:4] CH1_TX_FC��ch1 tx fcѡ��
                  00��20MHz
                  01��40MHz  CAģʽ
                  10��10MHz  ����ģʽ��Ĭ�ϣ�
                  11��20MHz LTEģʽ
            [3:2] CH1_TX_DIV_MODE��ch1 tx divģʽѡ��
                  00:1��Ƶ��Ĭ�ϣ�
            [1:0] CH1_TX_LPF_MODE��ch1 tx LPF�˷�ƫ�õ�������
                  �˷ŵ�����  op1   op2
                  00��        10u   10u   CAģʽ
                  01��        5u    5u   LTEģʽ
                  10��        8u    8u
                  11��        3u    3u    ����ģʽ��Ĭ�ϣ�
   UNION�ṹ ���� */
#define ABB_CH1_TX_2G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA41)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR02
   ��      ����[7] CH1_TX_CLKD_CTRL��ch1 tx����ʱ�ӿ���
                  0������(Ĭ��)
                  1������
            [6:4] CH1_TX_LPF_CT��ch1 tx lpf��������
                 000��5u��Ĭ�ϣ�
                  001��2u
                  010��3u
                  011��4u
                  100��6u
                  101��7u
                  110��8u
                  111��9u
            [3:0] CH1_TX_LPF_OP_MODE��ch1 tx lpf�˷�ģʽѡ��
                  0101��CAģʽ
                 1111��LTEģʽ
                  1010������ģʽ
   UNION�ṹ ���� */
#define ABB_CH1_TX_2G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA42)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR03
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_2G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA43)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_2G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA44)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_2G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA45)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_2G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA46)

/* �Ĵ���˵����TX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_2G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xA47)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH1_PD_TX_I��ch1 tx i·power down����
                  0: power ON
                 1: power DOWN��Ĭ�ϣ�
            [4] CH1_PD_TX_Q��ch1 tx q·power down����
                  0: power ON
                 1: power DOWN��Ĭ�ϣ�
            [3] reserved
            [2:0] CH1_TX_MODE��ch1 txģʽѡ��
                  000: LTE(614.4M)
                  001: 3G(307.2M)��Ĭ�ϣ�
                  010: CA(614.4M)
                  011: 2G(156M)
                  100: X(245.76M)
   UNION�ṹ ���� */
#define ABB_CH1_TX_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA48)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR01
   ��      ����[7:6] reserved
            [5:4] CH1_TX_FC��ch1 tx fcѡ��
                  00��20MHz
                  01��40MHz  CAģʽ
                  10��10MHz  ����ģʽ��Ĭ�ϣ�
                  11��20MHz LTEģʽ
            [3:2] CH1_TX_DIV_MODE��ch1 tx divģʽѡ��
                  00:1��Ƶ��Ĭ�ϣ�
            [1:0] CH1_TX_LPF_MODE��ch1 tx LPF�˷�ƫ�õ�������
                  �˷ŵ�����  op1   op2
                  00��        10u   10u   CAģʽ
                  01��        5u    5u   LTEģʽ
                  10��        8u    8u
                  11��        3u    3u    ����ģʽ��Ĭ�ϣ�
   UNION�ṹ ���� */
#define ABB_CH1_TX_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA49)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR02
   ��      ����[7] CH1_TX_CLKD_CTRL��ch1 tx����ʱ�ӿ���
                  0������(Ĭ��)
                  1������
            [6:4] CH1_TX_LPF_CT��ch1 tx lpf��������
                 000��5u��Ĭ�ϣ�
                  001��2u
                  010��3u
                  011��4u
                  100��6u
                  101��7u
                  110��8u
                  111��9u
            [3:0] CH1_TX_LPF_OP_MODE��ch1 tx lpf�˷�ģʽѡ��
                  0101��CAģʽ
                 1111��LTEģʽ
                  1010������ģʽ
   UNION�ṹ ���� */
#define ABB_CH1_TX_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA4A)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR03
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA4B)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA4C)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA4D)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA4E)

/* �Ĵ���˵����TX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_3G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xA4F)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH1_PD_TX_I��ch1 tx i·power down����
                  0: power ON
                 1: power DOWN��Ĭ�ϣ�
            [4] CH1_PD_TX_Q��ch1 tx q·power down����
                  0: power ON
                 1: power DOWN��Ĭ�ϣ�
            [3] reserved
            [2:0] CH1_TX_MODE��ch1 txģʽѡ��
                  000: LTE(614.4M)��Ĭ�ϣ�
                  001: 3G(307.2M)
                  010: CA(614.4M)
                  011: 2G(156M)
                  100: X(245.76M)
   UNION�ṹ ���� */
#define ABB_CH1_TX_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xA50)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR01
   ��      ����[7:6] reserved
            [5:4] CH1_TX_FC��ch1 tx fcѡ��
                  00��20MHz
                  01��40MHz  CAģʽ
                  10��10MHz  ����ģʽ
                  11��20MHz LTEģʽ ��Ĭ�ϣ�
            [3:2] CH1_TX_DIV_MODE��ch1 tx divģʽѡ��
                  00:1��Ƶ��Ĭ�ϣ�
            [1:0] CH1_TX_LPF_MODE��ch1 tx LPF�˷�ƫ�õ�������
                  �˷ŵ�����  op1   op2
                  00��        10u   10u   CAģʽ
                  01��        5u    5u   LTEģʽ��Ĭ�ϣ�
                  10��        8u    8u
                  11��        3u    3u    ����ģʽ
   UNION�ṹ ���� */
#define ABB_CH1_TX_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xA51)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR02
   ��      ����[7] CH1_TX_CLKD_CTRL��ch1 tx����ʱ�ӿ���
                  0������(Ĭ��)
                  1������
            [6:4] CH1_TX_LPF_CT��ch1 tx lpf��������
                 000��5u��Ĭ�ϣ�
                  001��2u
                  010��3u
                  011��4u
                  100��6u
                  101��7u
                  110��8u
                  111��9u
            [3:0] CH1_TX_LPF_OP_MODE��ch1 tx lpf�˷�ģʽѡ��
                  0101��CAģʽ
                 1111��LTEģʽ��Ĭ�ϣ�
                  1010������ģʽ
   UNION�ṹ ���� */
#define ABB_CH1_TX_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xA52)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR03
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xA53)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xA54)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xA55)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xA56)

/* �Ĵ���˵����TX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_4G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xA57)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH1_PD_TX_I��ch1 tx i·power down����
                  0: power ON
                 1: power DOWN��Ĭ�ϣ�
            [4] CH1_PD_TX_Q��ch1 tx q·power down����
                  0: power ON
                 1: power DOWN��Ĭ�ϣ�
            [3] reserved
            [2:0] CH1_TX_MODE��ch1 txģʽѡ��
                  000: LTE(614.4M)
                  001: 3G(307.2M)��Ĭ�ϣ�
                  010: CA(614.4M)
                  011: 2G(156M)
                  100: X(245.76M)
   UNION�ṹ ���� */
#define ABB_CH1_TX_TDS_ANA_1_ADDR                     (ABB_BASE_ADDR + 0xA58)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR01
   ��      ����[7:6] reserved
            [5:4] CH1_TX_FC��ch1 tx fcѡ��
                  00��20MHz
                  01��40MHz  CAģʽ
                  10��10MHz  ����ģʽ ��Ĭ�ϣ�
                  11��20MHz LTEģʽ
            [3:2] CH1_TX_DIV_MODE��ch1 tx divģʽѡ��
                  00:1��Ƶ��Ĭ�ϣ�
            [1:0] CH1_TX_LPF_MODE��ch1 tx LPF�˷�ƫ�õ�������
                  �˷ŵ�����  op1   op2
                  00��        10u   10u   CAģʽ
                  01��        5u    5u   LTEģʽ
                  10��        8u    8u
                  11��        3u    3u    ����ģʽ��Ĭ�ϣ�
   UNION�ṹ ���� */
#define ABB_CH1_TX_TDS_ANA_2_ADDR                     (ABB_BASE_ADDR + 0xA59)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR02
   ��      ����[7] CH1_TX_CLKD_CTRL��ch1 tx����ʱ�ӿ���
                  0������(Ĭ��)
                  1������
            [6:4] CH1_TX_LPF_CT��ch1 tx lpf��������
                 000��5u��Ĭ�ϣ�
                  001��2u
                  010��3u
                  011��4u
                  100��6u
                  101��7u
                  110��8u
                  111��9u
            [3:0] CH1_TX_LPF_OP_MODE��ch1 tx lpf�˷�ģʽѡ��
                  0101��CAģʽ
                 1111��LTEģʽ
                  1010������ģʽ��Ĭ�ϣ�
   UNION�ṹ ���� */
#define ABB_CH1_TX_TDS_ANA_3_ADDR                     (ABB_BASE_ADDR + 0xA5A)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR03
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_TDS_ANA_4_ADDR                     (ABB_BASE_ADDR + 0xA5B)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_TDS_ANA_5_ADDR                     (ABB_BASE_ADDR + 0xA5C)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_TDS_ANA_6_ADDR                     (ABB_BASE_ADDR + 0xA5D)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_TDS_ANA_7_ADDR                     (ABB_BASE_ADDR + 0xA5E)

/* �Ĵ���˵����TX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_TDS_ANA_8_ADDR                     (ABB_BASE_ADDR + 0xA5F)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH1_PD_TX_I��ch1 tx i·power down����
                  0: power ON
                 1: power DOWN��Ĭ�ϣ�
            [4] CH1_PD_TX_Q��ch1 tx q·power down����
                  0: power ON
                 1: power DOWN��Ĭ�ϣ�
            [3] reserved
            [2:0] CH1_TX_MODE��ch1 txģʽѡ��
                  000: LTE(614.4M)
                  001: 3G(307.2M)
                  010: CA(614.4M)
                  011: 2G(156M)
                  100: X(245.76M)��Ĭ�ϣ�
   UNION�ṹ ���� */
#define ABB_CH1_TX_X_ANA_1_ADDR                       (ABB_BASE_ADDR + 0xA60)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR01
   ��      ����[7:6] reserved
            [5:4] CH1_TX_FC��ch1 tx fcѡ��
                  00��20MHz
                  01��40MHz  CAģʽ
                  10��10MHz  ����ģʽ ��Ĭ�ϣ�
                  11��20MHz LTEģʽ
            [3:2] CH1_TX_DIV_MODE��ch1 tx divģʽѡ��
                  00:1��Ƶ��Ĭ�ϣ�
   UNION�ṹ ���� */
#define ABB_CH1_TX_X_ANA_2_ADDR                       (ABB_BASE_ADDR + 0xA61)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR02
   ��      ����[7] CH1_TX_CLKD_CTRL��ch1 tx����ʱ�ӿ���
                  0������(Ĭ��)
                  1������
            [6:4] CH1_TX_LPF_CT��ch1 tx lpf��������
                 000��5u��Ĭ�ϣ�
                  001��2u
                  010��3u
                  011��4u
                  100��6u
                  101��7u
                  110��8u
                  111��9u
            [3:0] CH1_TX_LPF_OP_MODE��ch1 tx lpf�˷�ģʽѡ��
                  0101��CAģʽ
                 1111��LTEģʽ
                  1010������ģʽ��Ĭ�ϣ�
   UNION�ṹ ���� */
#define ABB_CH1_TX_X_ANA_3_ADDR                       (ABB_BASE_ADDR + 0xA62)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR03
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_X_ANA_4_ADDR                       (ABB_BASE_ADDR + 0xA63)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_X_ANA_5_ADDR                       (ABB_BASE_ADDR + 0xA64)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_X_ANA_6_ADDR                       (ABB_BASE_ADDR + 0xA65)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_X_ANA_7_ADDR                       (ABB_BASE_ADDR + 0xA66)

/* �Ĵ���˵����TX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_X_ANA_8_ADDR                       (ABB_BASE_ADDR + 0xA67)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR00
   ��      ����[7:6] reserved
            [5] CH1_PD_TX_I��ch1 tx i·power down����
                  0: power ON
                 1: power DOWN��Ĭ�ϣ�
            [4] CH1_PD_TX_Q��ch1 tx q·power down����
                  0: power ON
                 1: power DOWN��Ĭ�ϣ�
            [3] reserved
            [2:0] CH1_TX_MODE��ch1 txģʽѡ��
                  000: LTE(614.4M)
                  001: 3G(307.2M)
                  010: CA(614.4M)
                  011: 2G(156M)��Ĭ�ϣ�
                  100: X(245.76M)
   UNION�ṹ ���� */
#define ABB_CH1_TX_IDLE_ANA_1_ADDR                    (ABB_BASE_ADDR + 0xA68)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR01
   ��      ����[7:6] reserved
            [5:4] CH1_TX_FC��ch1 tx fcѡ��
                  00��20MHz
                  01��40MHz  CAģʽ
                  10��10MHz  ����ģʽ��Ĭ�ϣ�
                  11��20MHz LTEģʽ
            [3:2] CH1_TX_DIV_MODE��ch1 tx divģʽѡ��
                  00:1��Ƶ��Ĭ�ϣ�
            [1:0] CH1_TX_LPF_MODE��ch1 tx LPF�˷�ƫ�õ�������
                  �˷ŵ�����  op1   op2
                  00��        10u   10u   CAģʽ
                  01��        5u    5u   LTEģʽ
                  10��        8u    8u
                  11��        3u    3u    ����ģʽ��Ĭ�ϣ�
   UNION�ṹ ���� */
#define ABB_CH1_TX_IDLE_ANA_2_ADDR                    (ABB_BASE_ADDR + 0xA69)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR02
   ��      ����[7] CH1_TX_CLKD_CTRL��ch1 tx����ʱ�ӿ���
                  0������(Ĭ��)
                  1������
            [6:4] CH1_TX_LPF_CT��ch1 tx lpf��������
                 000��5u��Ĭ�ϣ�
                  001��2u
                  010��3u
                  011��4u
                  100��6u
                  101��7u
                  110��8u
                  111��9u
            [3:0] CH1_TX_LPF_OP_MODE��ch1 tx lpf�˷�ģʽѡ��
                  0101��CAģʽ
                 1111��LTEģʽ
                  1010������ģʽ
   UNION�ṹ ���� */
#define ABB_CH1_TX_IDLE_ANA_3_ADDR                    (ABB_BASE_ADDR + 0xA6A)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR03
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_IDLE_ANA_4_ADDR                    (ABB_BASE_ADDR + 0xA6B)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR04
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_IDLE_ANA_5_ADDR                    (ABB_BASE_ADDR + 0xA6C)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR05
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_IDLE_ANA_6_ADDR                    (ABB_BASE_ADDR + 0xA6D)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR06
   ��      ����
            [7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_IDLE_ANA_7_ADDR                    (ABB_BASE_ADDR + 0xA6E)

/* �Ĵ���˵����TX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR07
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_TX_IDLE_ANA_8_ADDR                    (ABB_BASE_ADDR + 0xA6F)

/* �Ĵ���˵����TX ch1���üĴ���
   ��      ����[7:6] reserved
            [5] CH1_TX_DUM_EN_I��ch1 tx i channel dummy logic control signal
                  1��enable(Ĭ��)
                  0��disable
            [4] CH1_TX_DUM_EN_Q��ch1 tx q channel dummy logic control signal
                  1��enable(Ĭ��)
                  0��disable
            [3] reserved
            [2] CH1_TX_VCM_SEL��ch1 TXDAC LPF��ģ��ѹѡ��
                  0��VCM=650mV�����TXDAC�����ģ��ѹΪ650mV�������
                  1��VCM=500mV�����TXDAC�����ģ��ѹΪ500mV�������(Ĭ��)
            [1:0] CH1_TX_VCM_SWITCH��ch1 TX�ڲ�ͨ�����������LPF����˵Ĺ�ģ��ѹ
                  00����ģ��ѹ�����������TXDAC�����ģ��ѹΪ650mV�������
                  01����ģ��ѹ����145mV�����TXDAC�����ģ��ѹΪ500mV�������
                  10����ģ��ѹ����21mV������Debug��
                  11����ģ��ѹ����166mV������Debug��
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA00_ADDR                  (ABB_BASE_ADDR + 0xA70)

/* �Ĵ���˵����TX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA01_ADDR                  (ABB_BASE_ADDR + 0xA71)

/* �Ĵ���˵����TX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA02_ADDR                  (ABB_BASE_ADDR + 0xA72)

/* �Ĵ���˵����TX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA03_ADDR                  (ABB_BASE_ADDR + 0xA73)

/* �Ĵ���˵����TX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA04_ADDR                  (ABB_BASE_ADDR + 0xA74)

/* �Ĵ���˵����TX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA05_ADDR                  (ABB_BASE_ADDR + 0xA75)

/* �Ĵ���˵����TX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA06_ADDR                  (ABB_BASE_ADDR + 0xA76)

/* �Ĵ���˵����TX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA07_ADDR                  (ABB_BASE_ADDR + 0xA77)

/* �Ĵ���˵����TX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA08_ADDR                  (ABB_BASE_ADDR + 0xA78)

/* �Ĵ���˵����TX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA09_ADDR                  (ABB_BASE_ADDR + 0xA79)

/* �Ĵ���˵����TX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA10_ADDR                  (ABB_BASE_ADDR + 0xA7A)

/* �Ĵ���˵����TX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA11_ADDR                  (ABB_BASE_ADDR + 0xA7B)

/* �Ĵ���˵����TX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA12_ADDR                  (ABB_BASE_ADDR + 0xA7C)

/* �Ĵ���˵����TX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA13_ADDR                  (ABB_BASE_ADDR + 0xA7D)

/* �Ĵ���˵����TX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA14_ADDR                  (ABB_BASE_ADDR + 0xA7E)

/* �Ĵ���˵����TX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA15_ADDR                  (ABB_BASE_ADDR + 0xA7F)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR08
   ��      ����[7] CH0_PD_RXA_I��ch0 rxa i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [6] CH0_PD_RXA_Q��ch0 rxa q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [5] CH0_PD_RXB_I��ch0 rxb i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [4] CH0_PD_RXB_Q��ch0 rxb q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [3] reserved
            [2:0] CH0_RX_MODE��ch0 rxģʽѡ��
                000��LTEģʽ
                001��W3Gģʽ
                010��WDCģʽ
                011��2GA/2GBģʽ
                100��CAģʽ
                101��Xģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xC00)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH0_MODE_IBCT2��ch0 op2ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
            [3:2] reserved
            [1:0] CH0_MODE_IBCT1��ch0 op1ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xC01)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR10
   ��      ����[7] CH0_DEM_ENB
                0:DEM Enable(Ĭ��)
                1:DEM Disable
            [6:4] CH0_DEM_MODE
                000:DWAģʽ��Ĭ�ϣ�
                001:CLA1ģʽ
                010:CLA2ģʽ
                ��
                111:CLA7ģʽ
            [3] CH0_PDM_CTRL
                0:��ͱ���(Ĭ��)
                1:����������
            [2] CH0_DEM_OUTPUT_SEL
                0:��ͱ���(Ĭ��)
                1:����������
            [1:0] CH0_MODE_IBCT3��ch0 op3ģʽѡ��
                00��W3G/2GAģʽ
                01��WDC/X/2GBģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xC02)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR11
   ��      ����[7:6] CH0_CTRL_RFF��ch0 ǰ������rffѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/X/TDSģʽ
            [5:4] CH0_CTRL_RIN1��ch0 ������1�������rin1ѡ��
                00��Off
                01��WDC/TDS/Xģʽ
                10��2GA/W3Gģʽ
                11��CA/LTE/2GBģʽ
            [3:2] CH0_CTRL_RIN2��ch0 ������2�������rin2ѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/Xģʽ
            [1] CH0_CTRL_RIN3��ch0 ������3�������rin3ѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
            [0] CH0_CTRL_RFB��ch0 ��������������rfbѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xC03)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH0_CTRL_RSIG��ch0 �������ź�ǰ������rsigѡ��
                00��Off
                01��2GA/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/X/2GBģʽ
            [3:0] CH0_CTRL_RZ��ch0 ������3�������rzѡ��
                x000��320 ohm
                x100��160 ohm
                x110��80 ohm
                xxx1��0 ohm��Ĭ��1111��
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xC04)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR13
   ��      ����[7:6] reserved
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xC05)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR14
   ��      ����[7:6] reserved
            [5:4] CH0_RX_CAP3_MODE��ch0 ������3����cap3ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [3:2] CH0_RX_CAP2_MODE��ch0 ������2����cap2ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [1:0] CH0_RX_CAP1_MODE��ch0 ������1����cap1ģʽѡ��
                01��CAģʽ
                10��LTE/WDC/TDS/X/W3G/2GA/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xC06)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH0_IBCT_OP2��ch0 rx op2������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH0_IBCT_OP1��ch0 rx op1������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xC07)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH0_IBCT_DAC��ch0 rx dac������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH0_IBCT_OP3��ch0 rx op3������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xC08)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR17
   ��      ����[7:6] reserved
            [5:4] CH0_MULTI_RATE_CAP3��ch0 rx������3����cap3�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [3:2] CH0_MULTI_RATE_CAP2��ch0 rx������2����cap2�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [1:0] CH0_MULTI_RATE_CAP1��ch0 rx������1����cap1�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xC09)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR18
   ��      ����[7] CH0_RXA_DCLK_INV��ch0 rxa dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH0_RXB_DCLK_INV��ch0 rxb dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH0_CLKDIV2_A2D��ch0 rx a2d clock����Ƶѡ��
                0��ѡ�����Ƶ����� CA/2GA/2GBģʽ
                1������Ƶ��� LTE/WDC/W3G/TDS/X
            [4] CH0_CLKDIV2_RX��ch0 rx clock����Ƶѡ��
                0��ѡ�����Ƶ����� W3Gģʽ
                1������Ƶ��� ����ģʽ
            [3] CH0_DCLK_A2D_INV��ch0 rx a2d clock����ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2:0] CH0_CLKMUX_CTRL��ch0 rx ģʽ��Ƶʱ��ѡ��
               000��8��Ƶ CAģʽ
               001��4��Ƶ LTEģʽ
               011��2��Ƶ WDC/TDS/X/2GBģʽ
               111��1��Ƶ W3G/2GAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xC0A)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR19
   ��      ����[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xC0B)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR20
   ��      ����[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xC0C)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR21
   ��      ����[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xC0D)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR22
   ��      ����[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xC0E)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR23
   ��      ����[7] CH0_CLKIN3_INV_RXB_Q��ch0 rxb q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH0_CLKIN3_INV_RXB_I��ch0 rxb i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH0_CLKIN2_INV_RXB_Q��ch0 rxb q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [4] CH0_CLKIN2_INV_RXB_I��ch0 rxb i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [3] CH0_CLKIN3_INV_RXA_Q��ch0 rxa q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2] CH0_CLKIN3_INV_RXA_I��ch0 rxa i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [1] CH0_CLKIN2_INV_RXA_Q��ch0 rxa q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [0] CH0_CLKIN2_INV_RXA_I��ch0 rxa i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
   UNION�ṹ ���� */
#define ABB_CH0_RX_2G_ANA_16_ADDR                     (ABB_BASE_ADDR + 0xC0F)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR08
   ��      ����[7] CH0_PD_RXA_I��ch0 rxa i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [6] CH0_PD_RXA_Q��ch0 rxa q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [5] CH0_PD_RXB_I��ch0 rxb i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [4] CH0_PD_RXB_Q��ch0 rxb q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [3] reserved
            [2:0] CH0_RX_MODE��ch0 rxģʽѡ��
                000��LTEģʽ
                001��W3Gģʽ
                010��WDCģʽ
                011��2GA/2GBģʽ
                100��CAģʽ
                101��Xģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xC10)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH0_MODE_IBCT2��ch0 op2ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
            [3:2] reserved
            [1:0] CH0_MODE_IBCT1��ch0 op1ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xC11)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR10
   ��      ����[7] CH0_DEM_ENB
                0:DEM Enable(Ĭ��)
                1:DEM Disable
            [6:4] CH0_DEM_MODE
                000:DWAģʽ��Ĭ�ϣ�
                001:CLA1ģʽ
                010:CLA2ģʽ
                ��
                111:CLA7ģʽ
            [3] CH0_PDM_CTRL
                0:��ͱ���(Ĭ��)
                1:����������
            [2] CH0_DEM_OUTPUT_SEL
                0:��ͱ���(Ĭ��)
                1:����������
            [1:0] CH0_MODE_IBCT3��ch0 op3ģʽѡ��
                00��W3G/2GAģʽ
                01��WDC/X/2GBģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xC12)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR11
   ��      ����[7:6] CH0_CTRL_RFF��ch0 ǰ������rffѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/X/TDSģʽ
            [5:4] CH0_CTRL_RIN1��ch0 ������1�������rin1ѡ��
                00��Off
                01��WDC/TDS/Xģʽ
                10��2GA/W3Gģʽ
                11��CA/LTE/2GBģʽ
            [3:2] CH0_CTRL_RIN2��ch0 ������2�������rin2ѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/Xģʽ
            [1] CH0_CTRL_RIN3��ch0 ������3�������rin3ѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
            [0] CH0_CTRL_RFB��ch0 ��������������rfbѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xC13)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH0_CTRL_RSIG��ch0 �������ź�ǰ������rsigѡ��
                00��Off
                01��2GA/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/X/2GBģʽ
            [3:0] CH0_CTRL_RZ��ch0 ������3�������rzѡ��
                x000��320 ohm
                x100��160 ohm
                x110��80 ohm
                xxx1��0 ohm��Ĭ��1111��
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xC14)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR13
   ��      ����[7:6] reserved
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xC15)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR14
   ��      ����[7:6] reserved
            [5:4] CH0_RX_CAP3_MODE��ch0 ������3����cap3ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [3:2] CH0_RX_CAP2_MODE��ch0 ������2����cap2ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [1:0] CH0_RX_CAP1_MODE��ch0 ������1����cap1ģʽѡ��
                01��CAģʽ
                10��LTE/WDC/TDS/X/W3G/2GA/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xC16)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH0_IBCT_OP2��ch0 rx op2������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH0_IBCT_OP1��ch0 rx op1������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xC17)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH0_IBCT_DAC��ch0 rx dac������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH0_IBCT_OP3��ch0 rx op3������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xC18)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR17
   ��      ����[7:6] reserved
            [5:4] CH0_MULTI_RATE_CAP3��ch0 rx������3����cap3�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [3:2] CH0_MULTI_RATE_CAP2��ch0 rx������2����cap2�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [1:0] CH0_MULTI_RATE_CAP1��ch0 rx������1����cap1�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xC19)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR18
   ��      ����[7] CH0_RXA_DCLK_INV��ch0 rxa dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH0_RXB_DCLK_INV��ch0 rxb dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH0_CLKDIV2_A2D��ch0 rx a2d clock����Ƶѡ��
                0��ѡ�����Ƶ����� CA/2GA/2GBģʽ
                1������Ƶ��� LTE/WDC/W3G/TDS/X
            [4] CH0_CLKDIV2_RX��ch0 rx clock����Ƶѡ��
                0��ѡ�����Ƶ����� W3Gģʽ
                1������Ƶ��� ����ģʽ
            [3] CH0_DCLK_A2D_INV��ch0 rx a2d clock����ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2:0] CH0_CLKMUX_CTRL��ch0 rx ģʽ��Ƶʱ��ѡ��
               000��8��Ƶ CAģʽ
               001��4��Ƶ LTEģʽ
               011��2��Ƶ WDC/TDS/X/2GBģʽ
               111��1��Ƶ W3G/2GAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xC1A)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR19
   ��      ����[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xC1B)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR20
   ��      ����[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xC1C)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR21
   ��      ����[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xC1D)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR22
   ��      ����[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xC1E)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR23
   ��      ����[7] CH0_CLKIN3_INV_RXB_Q��ch0 rxb q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH0_CLKIN3_INV_RXB_I��ch0 rxb i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH0_CLKIN2_INV_RXB_Q��ch0 rxb q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [4] CH0_CLKIN2_INV_RXB_I��ch0 rxb i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [3] CH0_CLKIN3_INV_RXA_Q��ch0 rxa q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2] CH0_CLKIN3_INV_RXA_I��ch0 rxa i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [1] CH0_CLKIN2_INV_RXA_Q��ch0 rxa q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [0] CH0_CLKIN2_INV_RXA_I��ch0 rxa i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
   UNION�ṹ ���� */
#define ABB_CH0_RX_3G_ANA_16_ADDR                     (ABB_BASE_ADDR + 0xC1F)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR08
   ��      ����[7] CH0_PD_RXA_I��ch0 rxa i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [6] CH0_PD_RXA_Q��ch0 rxa q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [5] CH0_PD_RXB_I��ch0 rxb i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [4] CH0_PD_RXB_Q��ch0 rxb q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [3] reserved
            [2:0] CH0_RX_MODE��ch0 rxģʽѡ��
                000��LTEģʽ
                001��W3Gģʽ
                010��WDCģʽ
                011��2GA/2GBģʽ
                100��CAģʽ
                101��Xģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xC20)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH0_MODE_IBCT2��ch0 op2ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
            [3:2] reserved
            [1:0] CH0_MODE_IBCT1��ch0 op1ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xC21)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR10
   ��      ����[7] CH0_DEM_ENB
                0:DEM Enable(Ĭ��)
                1:DEM Disable
            [6:4] CH0_DEM_MODE
                000:DWAģʽ��Ĭ�ϣ�
                001:CLA1ģʽ
                010:CLA2ģʽ
                ��
                111:CLA7ģʽ
            [3] CH0_PDM_CTRL
                0:��ͱ���(Ĭ��)
                1:����������
            [2] CH0_DEM_OUTPUT_SEL
                0:��ͱ���(Ĭ��)
                1:����������
            [1:0] CH0_MODE_IBCT3��ch0 op3ģʽѡ��
                00��W3G/2GAģʽ
                01��WDC/X/2GBģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xC22)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR11
   ��      ����[7:6] CH0_CTRL_RFF��ch0 ǰ������rffѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/X/TDSģʽ
            [5:4] CH0_CTRL_RIN1��ch0 ������1�������rin1ѡ��
                00��Off
                01��WDC/TDS/Xģʽ
                10��2GA/W3Gģʽ
                11��CA/LTE/2GBģʽ
            [3:2] CH0_CTRL_RIN2��ch0 ������2�������rin2ѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/Xģʽ
            [1] CH0_CTRL_RIN3��ch0 ������3�������rin3ѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
            [0] CH0_CTRL_RFB��ch0 ��������������rfbѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xC23)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH0_CTRL_RSIG��ch0 �������ź�ǰ������rsigѡ��
                00��Off
                01��2GA/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/X/2GBģʽ
            [3:0] CH0_CTRL_RZ��ch0 ������3�������rzѡ��
                x000��320 ohm
                x100��160 ohm
                x110��80 ohm
                xxx1��0 ohm��Ĭ��1111��
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xC24)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR13
   ��      ����[7:6] reserved
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xC25)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR14
   ��      ����[7:6] reserved
            [5:4] CH0_RX_CAP3_MODE��ch0 ������3����cap3ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [3:2] CH0_RX_CAP2_MODE��ch0 ������2����cap2ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [1:0] CH0_RX_CAP1_MODE��ch0 ������1����cap1ģʽѡ��
                01��CAģʽ
                10��LTE/WDC/TDS/X/W3G/2GA/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xC26)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH0_IBCT_OP2��ch0 rx op2������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH0_IBCT_OP1��ch0 rx op1������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xC27)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH0_IBCT_DAC��ch0 rx dac������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH0_IBCT_OP3��ch0 rx op3������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xC28)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR17
   ��      ����[7:6] reserved
            [5:4] CH0_MULTI_RATE_CAP3��ch0 rx������3����cap3�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [3:2] CH0_MULTI_RATE_CAP2��ch0 rx������2����cap2�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [1:0] CH0_MULTI_RATE_CAP1��ch0 rx������1����cap1�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xC29)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR18
   ��      ����[7] CH0_RXA_DCLK_INV��ch0 rxa dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH0_RXB_DCLK_INV��ch0 rxb dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH0_CLKDIV2_A2D��ch0 rx a2d clock����Ƶѡ��
                0��ѡ�����Ƶ����� CA/2GA/2GBģʽ
                1������Ƶ��� LTE/WDC/W3G/TDS/X
            [4] CH0_CLKDIV2_RX��ch0 rx clock����Ƶѡ��
                0��ѡ�����Ƶ����� W3Gģʽ
                1������Ƶ��� ����ģʽ
            [3] CH0_DCLK_A2D_INV��ch0 rx a2d clock����ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2:0] CH0_CLKMUX_CTRL��ch0 rx ģʽ��Ƶʱ��ѡ��
               000��8��Ƶ CAģʽ
               001��4��Ƶ LTEģʽ
               011��2��Ƶ WDC/TDS/X/2GBģʽ
               111��1��Ƶ W3G/2GAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xC2A)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR19
   ��      ����[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xC2B)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR20
   ��      ����[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xC2C)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR21
   ��      ����[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xC2D)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR22
   ��      ����[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xC2E)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH0_REG_ANALOG_WR23
   ��      ����[7] CH0_CLKIN3_INV_RXB_Q��ch0 rxb q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH0_CLKIN3_INV_RXB_I��ch0 rxb i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH0_CLKIN2_INV_RXB_Q��ch0 rxb q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [4] CH0_CLKIN2_INV_RXB_I��ch0 rxb i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [3] CH0_CLKIN3_INV_RXA_Q��ch0 rxa q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2] CH0_CLKIN3_INV_RXA_I��ch0 rxa i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [1] CH0_CLKIN2_INV_RXA_Q��ch0 rxa q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [0] CH0_CLKIN2_INV_RXA_I��ch0 rxa i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
   UNION�ṹ ���� */
#define ABB_CH0_RX_4G_ANA_16_ADDR                     (ABB_BASE_ADDR + 0xC2F)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR08
   ��      ����[7] CH0_PD_RXA_I��ch0 rxa i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [6] CH0_PD_RXA_Q��ch0 rxa q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [5] CH0_PD_RXB_I��ch0 rxb i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [4] CH0_PD_RXB_Q��ch0 rxb q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [3] reserved
            [2:0] CH0_RX_MODE��ch0 rxģʽѡ��
                000��LTEģʽ
                001��W3Gģʽ
                010��WDCģʽ
                011��2GA/2GBģʽ
                100��CAģʽ
                101��Xģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_1_ADDR                     (ABB_BASE_ADDR + 0xC30)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH0_MODE_IBCT2��ch0 op2ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
            [3:2] reserved
            [1:0] CH0_MODE_IBCT1��ch0 op1ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_2_ADDR                     (ABB_BASE_ADDR + 0xC31)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR10
   ��      ����[7] CH0_DEM_ENB
                0:DEM Enable(Ĭ��)
                1:DEM Disable
            [6:4] CH0_DEM_MODE
                000:DWAģʽ��Ĭ�ϣ�
                001:CLA1ģʽ
                010:CLA2ģʽ
                ��
                111:CLA7ģʽ
            [3] CH0_PDM_CTRL
                0:��ͱ���(Ĭ��)
                1:����������
            [2] CH0_DEM_OUTPUT_SEL
                0:��ͱ���(Ĭ��)
                1:����������
            [1:0] CH0_MODE_IBCT3��ch0 op3ģʽѡ��
                00��W3G/2GAģʽ
                01��WDC/X/2GBģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_3_ADDR                     (ABB_BASE_ADDR + 0xC32)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR11
   ��      ����[7:6] CH0_CTRL_RFF��ch0 ǰ������rffѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/X/TDSģʽ
            [5:4] CH0_CTRL_RIN1��ch0 ������1�������rin1ѡ��
                00��Off
                01��WDC/TDS/Xģʽ
                10��2GA/W3Gģʽ
                11��CA/LTE/2GBģʽ
            [3:2] CH0_CTRL_RIN2��ch0 ������2�������rin2ѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/Xģʽ
            [1] CH0_CTRL_RIN3��ch0 ������3�������rin3ѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
            [0] CH0_CTRL_RFB��ch0 ��������������rfbѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_4_ADDR                     (ABB_BASE_ADDR + 0xC33)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH0_CTRL_RSIG��ch0 �������ź�ǰ������rsigѡ��
                00��Off
                01��2GA/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/X/2GBģʽ
            [3:0] CH0_CTRL_RZ��ch0 ������3�������rzѡ��
                x000��320 ohm
                x100��160 ohm
                x110��80 ohm
                xxx1��0 ohm��Ĭ��1111��
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_5_ADDR                     (ABB_BASE_ADDR + 0xC34)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR13
   ��      ����[7:6] reserved
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_6_ADDR                     (ABB_BASE_ADDR + 0xC35)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR14
   ��      ����[7:6] reserved
            [5:4] CH0_RX_CAP3_MODE��ch0 ������3����cap3ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [3:2] CH0_RX_CAP2_MODE��ch0 ������2����cap2ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [1:0] CH0_RX_CAP1_MODE��ch0 ������1����cap1ģʽѡ��
                01��CAģʽ
                10��LTE/WDC/TDS/X/W3G/2GA/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_7_ADDR                     (ABB_BASE_ADDR + 0xC36)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH0_IBCT_OP2��ch0 rx op2������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH0_IBCT_OP1��ch0 rx op1������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_8_ADDR                     (ABB_BASE_ADDR + 0xC37)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH0_IBCT_DAC��ch0 rx dac������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH0_IBCT_OP3��ch0 rx op3������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_9_ADDR                     (ABB_BASE_ADDR + 0xC38)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR17
   ��      ����[7:6] reserved
            [5:4] CH0_MULTI_RATE_CAP3��ch0 rx������3����cap3�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [3:2] CH0_MULTI_RATE_CAP2��ch0 rx������2����cap2�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [1:0] CH0_MULTI_RATE_CAP1��ch0 rx������1����cap1�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_10_ADDR                    (ABB_BASE_ADDR + 0xC39)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR18
   ��      ����[7] CH0_RXA_DCLK_INV��ch0 rxa dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH0_RXB_DCLK_INV��ch0 rxb dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH0_CLKDIV2_A2D��ch0 rx a2d clock����Ƶѡ��
                0��ѡ�����Ƶ����� CA/2GA/2GBģʽ
                1������Ƶ��� LTE/WDC/W3G/TDS/X
            [4] CH0_CLKDIV2_RX��ch0 rx clock����Ƶѡ��
                0��ѡ�����Ƶ����� W3Gģʽ
                1������Ƶ��� ����ģʽ
            [3] CH0_DCLK_A2D_INV��ch0 rx a2d clock����ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2:0] CH0_CLKMUX_CTRL��ch0 rx ģʽ��Ƶʱ��ѡ��
               000��8��Ƶ CAģʽ
               001��4��Ƶ LTEģʽ
               011��2��Ƶ WDC/TDS/X/2GBģʽ
               111��1��Ƶ W3G/2GAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_11_ADDR                    (ABB_BASE_ADDR + 0xC3A)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR19
   ��      ����[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_12_ADDR                    (ABB_BASE_ADDR + 0xC3B)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR20
   ��      ����[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_13_ADDR                    (ABB_BASE_ADDR + 0xC3C)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR21
   ��      ����[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_14_ADDR                    (ABB_BASE_ADDR + 0xC3D)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR22
   ��      ����[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_15_ADDR                    (ABB_BASE_ADDR + 0xC3E)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH0_REG_ANALOG_WR23
   ��      ����[7] CH0_CLKIN3_INV_RXB_Q��ch0 rxb q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH0_CLKIN3_INV_RXB_I��ch0 rxb i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH0_CLKIN2_INV_RXB_Q��ch0 rxb q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [4] CH0_CLKIN2_INV_RXB_I��ch0 rxb i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [3] CH0_CLKIN3_INV_RXA_Q��ch0 rxa q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2] CH0_CLKIN3_INV_RXA_I��ch0 rxa i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [1] CH0_CLKIN2_INV_RXA_Q��ch0 rxa q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [0] CH0_CLKIN2_INV_RXA_I��ch0 rxa i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
   UNION�ṹ ���� */
#define ABB_CH0_RX_TDS_ANA_16_ADDR                    (ABB_BASE_ADDR + 0xC3F)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR08
   ��      ����[7] CH0_PD_RXA_I��ch0 rxa i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [6] CH0_PD_RXA_Q��ch0 rxa q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [5] CH0_PD_RXB_I��ch0 rxb i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [4] CH0_PD_RXB_Q��ch0 rxb q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [3] reserved
            [2:0] CH0_RX_MODE��ch0 rxģʽѡ��
                000��LTEģʽ
                001��W3Gģʽ
                010��WDCģʽ
                011��2GA/2GBģʽ
                100��CAģʽ
                101��Xģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_1_ADDR                       (ABB_BASE_ADDR + 0xC40)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH0_MODE_IBCT2��ch0 op2ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
            [3:2] reserved
            [1:0] CH0_MODE_IBCT1��ch0 op1ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_2_ADDR                       (ABB_BASE_ADDR + 0xC41)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR10
   ��      ����[7] CH0_DEM_ENB
                0:DEM Enable(Ĭ��)
                1:DEM Disable
            [6:4] CH0_DEM_MODE
                000:DWAģʽ��Ĭ�ϣ�
                001:CLA1ģʽ
                010:CLA2ģʽ
                ��
                111:CLA7ģʽ
            [3] CH0_PDM_CTRL
                0:��ͱ���(Ĭ��)
                1:����������
            [2] CH0_DEM_OUTPUT_SEL
                0:��ͱ���(Ĭ��)
                1:����������
            [1:0] CH0_MODE_IBCT3��ch0 op3ģʽѡ��
                00��W3G/2GAģʽ
                01��WDC/X/2GBģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_3_ADDR                       (ABB_BASE_ADDR + 0xC42)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR11
   ��      ����[7:6] CH0_CTRL_RFF��ch0 ǰ������rffѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/X/TDSģʽ
            [5:4] CH0_CTRL_RIN1��ch0 ������1�������rin1ѡ��
                00��Off
                01��WDC/TDS/Xģʽ
                10��2GA/W3Gģʽ
                11��CA/LTE/2GBģʽ
            [3:2] CH0_CTRL_RIN2��ch0 ������2�������rin2ѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/Xģʽ
            [1] CH0_CTRL_RIN3��ch0 ������3�������rin3ѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
            [0] CH0_CTRL_RFB��ch0 ��������������rfbѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_4_ADDR                       (ABB_BASE_ADDR + 0xC43)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH0_CTRL_RSIG��ch0 �������ź�ǰ������rsigѡ��
                00��Off
                01��2GA/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/X/2GBģʽ
            [3:0] CH0_CTRL_RZ��ch0 ������3�������rzѡ��
                x000��320 ohm
                x100��160 ohm
                x110��80 ohm
                xxx1��0 ohm��Ĭ��1111��
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_5_ADDR                       (ABB_BASE_ADDR + 0xC44)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR13
   ��      ����[7:6] reserved
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_6_ADDR                       (ABB_BASE_ADDR + 0xC45)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR14
   ��      ����[7:6] reserved
            [5:4] CH0_RX_CAP3_MODE��ch0 ������3����cap3ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [3:2] CH0_RX_CAP2_MODE��ch0 ������2����cap2ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [1:0] CH0_RX_CAP1_MODE��ch0 ������1����cap1ģʽѡ��
                01��CAģʽ
                10��LTE/WDC/TDS/X/W3G/2GA/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_7_ADDR                       (ABB_BASE_ADDR + 0xC46)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH0_IBCT_OP2��ch0 rx op2������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH0_IBCT_OP1��ch0 rx op1������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_8_ADDR                       (ABB_BASE_ADDR + 0xC47)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH0_IBCT_DAC��ch0 rx dac������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH0_IBCT_OP3��ch0 rx op3������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_9_ADDR                       (ABB_BASE_ADDR + 0xC48)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR17
   ��      ����[7:6] reserved
            [5:4] CH0_MULTI_RATE_CAP3��ch0 rx������3����cap3�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [3:2] CH0_MULTI_RATE_CAP2��ch0 rx������2����cap2�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [1:0] CH0_MULTI_RATE_CAP1��ch0 rx������1����cap1�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_10_ADDR                      (ABB_BASE_ADDR + 0xC49)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR18
   ��      ����[7] CH0_RXA_DCLK_INV��ch0 rxa dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH0_RXB_DCLK_INV��ch0 rxb dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH0_CLKDIV2_A2D��ch0 rx a2d clock����Ƶѡ��
                0��ѡ�����Ƶ����� CA/2GA/2GBģʽ
                1������Ƶ��� LTE/WDC/W3G/TDS/X
            [4] CH0_CLKDIV2_RX��ch0 rx clock����Ƶѡ��
                0��ѡ�����Ƶ����� W3Gģʽ
                1������Ƶ��� ����ģʽ
            [3] CH0_DCLK_A2D_INV��ch0 rx a2d clock����ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2:0] CH0_CLKMUX_CTRL��ch0 rx ģʽ��Ƶʱ��ѡ��
               000��8��Ƶ CAģʽ
               001��4��Ƶ LTEģʽ
               011��2��Ƶ WDC/TDS/X/2GBģʽ
               111��1��Ƶ W3G/2GAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_11_ADDR                      (ABB_BASE_ADDR + 0xC4A)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR19
   ��      ����[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_12_ADDR                      (ABB_BASE_ADDR + 0xC4B)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR20
   ��      ����[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_13_ADDR                      (ABB_BASE_ADDR + 0xC4C)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR21
   ��      ����[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_14_ADDR                      (ABB_BASE_ADDR + 0xC4D)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR22
   ��      ����[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_15_ADDR                      (ABB_BASE_ADDR + 0xC4E)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH0_REG_ANALOG_WR23
   ��      ����[7] CH0_CLKIN3_INV_RXB_Q��ch0 rxb q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH0_CLKIN3_INV_RXB_I��ch0 rxb i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH0_CLKIN2_INV_RXB_Q��ch0 rxb q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [4] CH0_CLKIN2_INV_RXB_I��ch0 rxb i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [3] CH0_CLKIN3_INV_RXA_Q��ch0 rxa q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2] CH0_CLKIN3_INV_RXA_I��ch0 rxa i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [1] CH0_CLKIN2_INV_RXA_Q��ch0 rxa q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [0] CH0_CLKIN2_INV_RXA_I��ch0 rxa i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
   UNION�ṹ ���� */
#define ABB_CH0_RX_X_ANA_16_ADDR                      (ABB_BASE_ADDR + 0xC4F)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR08
   ��      ����[7] CH0_PD_RXA_I��ch0 rxa i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [6] CH0_PD_RXA_Q��ch0 rxa q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [5] CH0_PD_RXB_I��ch0 rxb i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [4] CH0_PD_RXB_Q��ch0 rxb q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [3] reserved
            [2:0] CH0_RX_MODE��ch0 rxģʽѡ��
                000��LTEģʽ
                001��W3Gģʽ
                010��WDCģʽ
                011��2GA/2GBģʽ
                100��CAģʽ
                101��Xģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_1_ADDR                    (ABB_BASE_ADDR + 0xC50)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH0_MODE_IBCT2��ch0 op2ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
            [3:2] reserved
            [1:0] CH0_MODE_IBCT1��ch0 op1ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_2_ADDR                    (ABB_BASE_ADDR + 0xC51)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR10
   ��      ����[7] CH0_DEM_ENB
                0:DEM Enable(Ĭ��)
                1:DEM Disable
            [6:4] CH0_DEM_MODE
                000:DWAģʽ��Ĭ�ϣ�
                001:CLA1ģʽ
                010:CLA2ģʽ
                ��
                111:CLA7ģʽ
            [3] CH0_PDM_CTRL
                0:��ͱ���(Ĭ��)
                1:����������
            [2] CH0_DEM_OUTPUT_SEL
                0:��ͱ���(Ĭ��)
                1:����������
            [1:0] CH0_MODE_IBCT3��ch0 op3ģʽѡ��
                00��W3G/2GAģʽ
                01��WDC/X/2GBģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_3_ADDR                    (ABB_BASE_ADDR + 0xC52)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR11
   ��      ����[7:6] CH0_CTRL_RFF��ch0 ǰ������rffѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/X/TDSģʽ
            [5:4] CH0_CTRL_RIN1��ch0 ������1�������rin1ѡ��
                00��Off
                01��WDC/TDS/Xģʽ
                10��2GA/W3Gģʽ
                11��CA/LTE/2GBģʽ
            [3:2] CH0_CTRL_RIN2��ch0 ������2�������rin2ѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/Xģʽ
            [1] CH0_CTRL_RIN3��ch0 ������3�������rin3ѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
            [0] CH0_CTRL_RFB��ch0 ��������������rfbѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_4_ADDR                    (ABB_BASE_ADDR + 0xC53)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH0_CTRL_RSIG��ch0 �������ź�ǰ������rsigѡ��
                00��Off
                01��2GA/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/X/2GBģʽ
            [3:0] CH0_CTRL_RZ��ch0 ������3�������rzѡ��
                x000��320 ohm
                x100��160 ohm
                x110��80 ohm
                xxx1��0 ohm��Ĭ��1111��
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_5_ADDR                    (ABB_BASE_ADDR + 0xC54)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR13
   ��      ����[7:6] reserved
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_6_ADDR                    (ABB_BASE_ADDR + 0xC55)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR14
   ��      ����[7:6] reserved
            [5:4] CH0_RX_CAP3_MODE��ch0 ������3����cap3ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [3:2] CH0_RX_CAP2_MODE��ch0 ������2����cap2ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [1:0] CH0_RX_CAP1_MODE��ch0 ������1����cap1ģʽѡ��
                01��CAģʽ
                10��LTE/WDC/TDS/X/W3G/2GA/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_7_ADDR                    (ABB_BASE_ADDR + 0xC56)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH0_IBCT_OP2��ch0 rx op2������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH0_IBCT_OP1��ch0 rx op1������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_8_ADDR                    (ABB_BASE_ADDR + 0xC57)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH0_IBCT_DAC��ch0 rx dac������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH0_IBCT_OP3��ch0 rx op3������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_9_ADDR                    (ABB_BASE_ADDR + 0xC58)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR17
   ��      ����[7:6] reserved
            [5:4] CH0_MULTI_RATE_CAP3��ch0 rx������3����cap3�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [3:2] CH0_MULTI_RATE_CAP2��ch0 rx������2����cap2�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [1:0] CH0_MULTI_RATE_CAP1��ch0 rx������1����cap1�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_10_ADDR                   (ABB_BASE_ADDR + 0xC59)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR18
   ��      ����[7] CH0_RXA_DCLK_INV��ch0 rxa dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH0_RXB_DCLK_INV��ch0 rxb dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH0_CLKDIV2_A2D��ch0 rx a2d clock����Ƶѡ��
                0��ѡ�����Ƶ����� CA/2GA/2GBģʽ
                1������Ƶ��� LTE/WDC/W3G/TDS/X
            [4] CH0_CLKDIV2_RX��ch0 rx clock����Ƶѡ��
                0��ѡ�����Ƶ����� W3Gģʽ
                1������Ƶ��� ����ģʽ
            [3] CH0_DCLK_A2D_INV��ch0 rx a2d clock����ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2:0] CH0_CLKMUX_CTRL��ch0 rx ģʽ��Ƶʱ��ѡ��
               000��8��Ƶ CAģʽ
               001��4��Ƶ LTEģʽ
               011��2��Ƶ WDC/TDS/X/2GBģʽ
               111��1��Ƶ W3G/2GAģʽ
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_11_ADDR                   (ABB_BASE_ADDR + 0xC5A)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR19
   ��      ����[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_12_ADDR                   (ABB_BASE_ADDR + 0xC5B)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR20
   ��      ����[7:5] reserved
            [4:0] CH0_RXA_CLK_DAC3_CTRL��ch0 rxa qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_13_ADDR                   (ABB_BASE_ADDR + 0xC5C)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR21
   ��      ����[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_14_ADDR                   (ABB_BASE_ADDR + 0xC5D)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR22
   ��      ����[7:5] reserved
            [4:0] CH0_RXB_CLK_DAC3_CTRL��ch0 rxb qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_15_ADDR                   (ABB_BASE_ADDR + 0xC5E)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH0_REG_ANALOG_WR23
   ��      ����[7] CH0_CLKIN3_INV_RXB_Q��ch0 rxb q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH0_CLKIN3_INV_RXB_I��ch0 rxb i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH0_CLKIN2_INV_RXB_Q��ch0 rxb q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [4] CH0_CLKIN2_INV_RXB_I��ch0 rxb i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [3] CH0_CLKIN3_INV_RXA_Q��ch0 rxa q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2] CH0_CLKIN3_INV_RXA_I��ch0 rxa i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [1] CH0_CLKIN2_INV_RXA_Q��ch0 rxa q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [0] CH0_CLKIN2_INV_RXA_I��ch0 rxa i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
   UNION�ṹ ���� */
#define ABB_CH0_RX_IDLE_ANA_16_ADDR                   (ABB_BASE_ADDR + 0xC5F)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7:0] CH0_REG_TUNE1��ch0 rx cap1�ֶ����üĴ���
                0100 0000(Ĭ��)
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA16_ADDR                  (ABB_BASE_ADDR + 0xC60)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7:0] CH0_REG_TUNE2��ch0 rx cap2�ֶ����üĴ���
                0100 0000(Ĭ��)
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA17_ADDR                  (ABB_BASE_ADDR + 0xC61)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7:0] CH0_REG_TUNE3��ch0 rx cap3�ֶ����üĴ���
                0100 0000(Ĭ��)
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA18_ADDR                  (ABB_BASE_ADDR + 0xC62)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7] CH0_RX_TUNE_SEL
                0��tuning��������rctuneģ��
                1��tuning�������ڼĴ�������
            [6:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA19_ADDR                  (ABB_BASE_ADDR + 0xC63)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7] reserved
            [6:4] CH0_OL_CTRL��ch0 rx overload����ѡ��
                000��16����������������С�룬ͬʱ����int1��int2��int3��Ĭ�ϣ�
                001��8����������������С�룬ͬʱ����int1��int2��int3
                010��4����������������С�룬ͬʱ����int1��int2��int3
                011���ر�Overload��⣬ͬʱ����int1��int2��int3
                100��16����������������С�룬����˳��Ϊint3-->int2-->int1
                101��8����������������С�룬����˳��Ϊint3-->int2-->int1
                110��4����������������С�룬����˳��Ϊint3-->int2-->int1
                111���ر�Overload��⣬����˳��Ϊint3-->int2-->int1
            [3:2] reserved
            [1] CH0_PUP_CLK_CTRL��ch0 rx �����ϵ�ʱ�ӿ���
                0���ϵ���ɺ�ر��ϵ�ģ���ʱ�ӣ�Ĭ�ϣ�
                1���ϵ���ɺ󲻹ر��ϵ�ģ��ʱ��
            [0] CH0_PUP_MODE��ch0 rx �����ϵ�ģʽ
                0���Զ�ģʽ��Ĭ�ϣ�
                1�����üĴ����ϵ�ģʽ
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA20_ADDR                  (ABB_BASE_ADDR + 0xC64)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7] CH0_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��RST_CAP����
                0��Reset CAP3
                1����Reset CAP3
            [6] CH0_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��RST_CAP����
                0��Reset CAP2
                1����Reset CAP2
            [5] CH0_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��RST_CAP����
                0��Reset CAP1
                1����Reset CAP1
            [4] CH0_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��OP����
                0��OP Power Down
                1��OP Power On
            [3] CH0_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��DAC����
                0��DAC Power Down
                1��DAC Power On
            [2] CH0_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��QTУ������
                0��QT Calibration On
                1��QT Calibration Off
            [1] CH0_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��CLKGEN����
                0��CLKGEN Power Down
                1��CLKGEN Power On
            [0] CH0_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��QT����
                0��QT Power Down
                1��QT Power On
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA21_ADDR                  (ABB_BASE_ADDR + 0xC65)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7:6] reserved
            [5] CH0_QT_REF_SEL��ch0 rx qt��refѡ��
                0��vrefp/vrefn������refģ�飨Ĭ�ϣ�
                1��vrefp/vrefn�����ڱ��ط�ѹ
            [4] CH0_EN_QTCAL��ch0 rx qtУ׼enable
                0���Ƚ���У׼Disable��Ĭ�ϣ�
                1���Ƚ���У׼Enable��Ĭ�ϣ�
            [3] CH0_CAL_SW��ch0 rx op1У׼���ؿ���
                0��Ĭ��
                1������
            [2] CH0_CAL_TRIM_SW��ch0 rx op1У׼trim���ؿ���
                0��cal trim����disable��Ĭ�ϣ�
                1��cal trim����enable��Ĭ�ϣ�
            [1] CH0_OPCAL_VCM_SEL��ch0 rx op1У׼��ģѡ��
                0��op1У׼�̽�����˹�ģDisable��Ĭ�ϣ�
                1��op1У׼�̽�����˹�ģEnable��Ĭ�ϣ�
            [0] CH0_EN_OPCAL��ch0 rx op1У׼enable
                0��op1У׼Disable��Ĭ�ϣ�
                1��op1У׼Enable��Ĭ�ϣ�
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA22_ADDR                  (ABB_BASE_ADDR + 0xC66)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7] CH0_VCM_PATH_CTRL_Q��ch0 rxb q·��·����ͨ·ѡ��vcm
                0��ͨ·�Ͽ�����ѡ���ͨ·
                1��ͨ·��ͨ��ѡ���ͨ·
            [6] CH0_VCM_PATH_CTRL_I��ch0 rxb i·��·����ͨ·ѡ��vcm
                0��ͨ·�Ͽ�����ѡ���ͨ·
                1��ͨ·��ͨ��ѡ���ͨ·
            [5] CH0_TX_PATH_CTRL_Q��ch0 rxb q·��·����ͨ·ѡ��tx
                0��ͨ·�Ͽ�����ѡ���ͨ·
                1��ͨ·��ͨ��ѡ���ͨ·
            [4] CH0_TX_PATH_CTRL_I��ch0 rxb i·��·����ͨ·ѡ��tx
                0��ͨ·�Ͽ�����ѡ���ͨ·
                1��ͨ·��ͨ��ѡ���ͨ·
            [3] CH0_RXB_PATH_CTRL_Q��ch0 rxb q·��·����ͨ·ѡ��rxb����������ģʽ
                0��ͨ·�Ͽ�����ѡ���ͨ·
                1��ͨ·��ͨ��ѡ���ͨ·
            [2] CH0_RXB_PATH_CTRL_I��ch0 rxb i·��·����ͨ·ѡ��rxb����������ģʽ
                0��ͨ·�Ͽ�����ѡ���ͨ·
                1��ͨ·��ͨ��ѡ���ͨ·
            [1] CH0_RXA_PATH_CTRL_Q��ch0 rxa q·��·����ͨ·ѡ��rxa����������ģʽ
                0��ͨ·�Ͽ�����ѡ���ͨ·
                1��ͨ·��ͨ��ѡ���ͨ·
            [0] CH0_RXA_PATH_CTRL_I��ch0 rxa i·��·����ͨ·ѡ��rxa����������ģʽ
                0��ͨ·�Ͽ�����ѡ���ͨ·
                1��ͨ·��ͨ��ѡ���ͨ·
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA23_ADDR                  (ABB_BASE_ADDR + 0xC67)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7] CH0_RXA_SE_CTRLP_Q��ch0 rxa q·����ģʽp����˿���ѡ��
                0������ͨ�����˶˷���dac������ӹ̶���ƽ
                1����ͨ�����˶˷���dac����������˷�����
            [6] CH0_RXA_SE_CTRLN_Q��ch0 rxa q·����ģʽn����˿���ѡ��
                0������ͨ�����˶˷���dac������ӹ̶���ƽ
                1����ͨ�����˶˷���dac����������˷�����
            [5] CH0_RXA_SE_CTRLP_I��ch0 rxa i·����ģʽp����˿���ѡ��
                0������ͨ�����˶˷���dac������ӹ̶���ƽ
                1����ͨ�����˶˷���dac����������˷�����
            [4] CH0_RXA_SE_CTRLN_I��ch0 rxa i·����ģʽn����˿���ѡ��
                0������ͨ�����˶˷���dac������ӹ̶���ƽ
                1����ͨ�����˶˷���dac����������˷�����
            [3:2] CH0_RXA_MODE_IBCT_SE��ch0 rxa ����ģʽvcm buffer�˷�ģʽѡ��
                11��CAģʽ
                10��LTEģʽ
                01��WDCģʽ
                00��W3Gģʽ
            [1] CH0_RXA_PD_SE_Q��ch0 rxa i·����ģʽvcm buffer�˷�power down����
                0��power on
                1��power down
            [0] CH0_RXA_PD_SE_I��ch0 rxa q·����ģʽvcm buffer�˷�power down����
                0��power on
                1��power down
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA24_ADDR                  (ABB_BASE_ADDR + 0xC68)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7] CH0_RXB_SE_CTRLP_Q��ch0 rxb q·����ģʽp����˿���ѡ��
                0������ͨ�����˶˷���dac������ӹ̶���ƽ
                1����ͨ�����˶˷���dac����������˷�����
            [6] CH0_RXB_SE_CTRLN_Q��ch0 rxb q·����ģʽn����˿���ѡ��
                0������ͨ�����˶˷���dac������ӹ̶���ƽ
                1����ͨ�����˶˷���dac����������˷�����
            [5] CH0_RXB_SE_CTRLP_I��ch0 rxb i·����ģʽp����˿���ѡ��
                0������ͨ�����˶˷���dac������ӹ̶���ƽ
                1����ͨ�����˶˷���dac����������˷�����
            [4] CH0_RXB_SE_CTRLN_I��ch0 rxb i·����ģʽn����˿���ѡ��
                0������ͨ�����˶˷���dac������ӹ̶���ƽ
                1����ͨ�����˶˷���dac����������˷�����
            [3:2] CH0_RXB_MODE_IBCT_SE��ch0 rxb ����ģʽvcm buffer�˷�ģʽѡ��
                11��CAģʽ
                10��LTEģʽ
                01��WDCģʽ
                00��W3Gģʽ
            [1] CH0_RXB_PD_SE_Q��ch0 rxb i·����ģʽvcm buffer�˷�power down����
                0��power on
                1��power down
            [0] CH0_RXB_PD_SE_I��ch0 rxb q·����ģʽvcm buffer�˷�power down����
                0��power on
                1��power down
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA25_ADDR                  (ABB_BASE_ADDR + 0xC69)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7] reserved
            [6:4] CH0_IBCT_OPS��ch0 rxb ����ģʽ��������
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH0_IBCT_OP4���ڲ�����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
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

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA30_ADDR                  (ABB_BASE_ADDR + 0xC6E)

/* �Ĵ���˵����RX ch0���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH0_REG_DEBUG_ANA31_ADDR                  (ABB_BASE_ADDR + 0xC6F)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR08
   ��      ����[7] CH1_PD_RXA_I��ch1 rxa i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [6] CH1_PD_RXA_Q��ch1 rxa q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [5] CH1_PD_RXB_I��ch1 rxb i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [4] CH1_PD_RXB_Q��ch1 rxb q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [3] reserved
            [2:0] CH1_RX_MODE��ch1 rxģʽѡ��
                000��LTEģʽ
                001��W3Gģʽ
                010��WDCģʽ
                011��2GA/2GBģʽ
                100��CAģʽ
                101��Xģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xC80)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH1_MODE_IBCT2��ch1 op2ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
            [3:2] reserved
            [1:0] CH1_MODE_IBCT1��ch1 op1ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xC81)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR10
   ��      ����[7] CH1_DEM_ENB
                0:DEM Enable(Ĭ��)
                1:DEM Disable
            [6:4] CH1_DEM_MODE
                000:DWAģʽ��Ĭ�ϣ�
                001:CLA1ģʽ
                010:CLA2ģʽ
                ��
                111:CLA7ģʽ
            [3] CH1_PDM_CTRL
                0:��ͱ���(Ĭ��)
                1:����������
            [2] CH1_DEM_OUTPUT_SEL
                0:��ͱ���(Ĭ��)
                1:����������
            [1:0] CH1_MODE_IBCT3��ch1 op3ģʽѡ��
                00��W3G/2GAģʽ
                01��WDC/X/2GBģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xC82)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR11
   ��      ����[7:6] CH1_CTRL_RFF��ch1 ǰ������rffѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/X/TDSģʽ
            [5:4] CH1_CTRL_RIN1��ch1 ������1�������rin1ѡ��
                00��Off
                01��WDC/TDS/Xģʽ
                10��2GA/W3Gģʽ
                11��CA/LTE/2GBģʽ
            [3:2] CH1_CTRL_RIN2��ch1 ������2�������rin2ѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/Xģʽ
            [1] CH1_CTRL_RIN3��ch1 ������3�������rin3ѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
            [0] CH1_CTRL_RFB��ch1 ��������������rfbѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xC83)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH1_CTRL_RSIG��ch1 �������ź�ǰ������rsigѡ��
                00��Off
                01��2GA/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/X/2GBģʽ
            [3:0] CH1_CTRL_RZ��ch1 ������3�������rzѡ��
                x000��320 ohm
                x100��160 ohm
                x110��80 ohm
                xxx1��0 ohm��Ĭ��1111��
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xC84)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR13
   ��      ����[7:6] reserved
            [5] CH1_ADC_CLK_DIV2��ch1 adc���ʱ��2��Ƶ����
                  0��1��Ƶ ����ģʽ
                  1��2��Ƶ 2GAģʽ
            [4] CH1_DLY_CTRL2��ch1 0.6tsʱ�����ڿ���ѡ��
                  0��0.5Ts
                  1��0.6Ts
            [3] reserved
            [2] CH1_DCTRL23��ch1 dac23����ģʽѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
            [1:0] CH1_DCTRL1��ch1 dac1����ģʽѡ��
                00��2GA/W3Gģʽ
                01��Reserved
                10��WDC/TDS/Xģʽ
                01��CA/LTE/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xC85)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR14
   ��      ����[7:6] reserved
            [5:4] CH1_RX_CAP3_MODE��ch1 ������3����cap3ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [3:2] CH1_RX_CAP2_MODE��ch1 ������2����cap2ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [1:0] CH1_RX_CAP1_MODE��ch1 ������1����cap1ģʽѡ��
                01��CAģʽ
                10��LTE/WDC/TDS/X/W3G/2GA/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xC86)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH1_IBCT_OP2��ch1 rx op2������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH1_IBCT_OP1��ch1 rx op1������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xC87)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH1_IBCT_DAC��ch1 rx dac������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH1_IBCT_OP3��ch1 rx op3������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xC88)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR17
   ��      ����[7:6] reserved
            [5:4] CH1_MULTI_RATE_CAP3��ch1 rx������3����cap3�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [3:2] CH1_MULTI_RATE_CAP2��ch1 rx������2����cap2�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [1:0] CH1_MULTI_RATE_CAP1��ch1 rx������1����cap1�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xC89)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR18
   ��      ����[7] CH1_RXA_DCLK_INV��ch1 rxa dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH1_RXB_DCLK_INV��ch1 rxb dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH1_CLKDIV2_A2D��ch1 rx a2d clock����Ƶѡ��
                0��ѡ�����Ƶ����� CA/2GA/2GBģʽ
                1������Ƶ��� LTE/WDC/W3G/TDS/X
            [4] CH1_CLKDIV2_RX��ch1 rx clock����Ƶѡ��
                0��ѡ�����Ƶ����� W3Gģʽ
                1������Ƶ��� ����ģʽ
            [3] CH1_DCLK_A2D_INV��ch1 rx a2d clock����ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2:0] CH1_CLKMUX_CTRL��ch1 rx ģʽ��Ƶʱ��ѡ��
               000��8��Ƶ CAģʽ
               001��4��Ƶ LTEģʽ
               011��2��Ƶ WDC/TDS/X/2GBģʽ
               111��1��Ƶ W3G/2GAģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xC8A)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR19
   ��      ����[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL��ch1 rxa dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xC8B)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR20
   ��      ����[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL��ch1 rxa qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xC8C)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR21
   ��      ����[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL��ch1 rxb dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xC8D)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR22
   ��      ����[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL��ch1 rxb qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xC8E)

/* �Ĵ���˵����RX 2G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR23
   ��      ����[7] CH1_CLKIN3_INV_RXB_Q��ch1 rxb q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH1_CLKIN3_INV_RXB_I��ch1 rxb i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH1_CLKIN2_INV_RXB_Q��ch1 rxb q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [4] CH1_CLKIN2_INV_RXB_I��ch1 rxb i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [3] CH1_CLKIN3_INV_RXA_Q��ch1 rxa q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2] CH1_CLKIN3_INV_RXA_I��ch1 rxa i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [1] CH1_CLKIN2_INV_RXA_Q��ch1 rxa q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [0] CH1_CLKIN2_INV_RXA_I��ch1 rxa i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
   UNION�ṹ ���� */
#define ABB_CH1_RX_2G_ANA_16_ADDR                     (ABB_BASE_ADDR + 0xC8F)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR08
   ��      ����[7] CH1_PD_RXA_I��ch1 rxa i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [6] CH1_PD_RXA_Q��ch1 rxa q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [5] CH1_PD_RXB_I��ch1 rxb i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [4] CH1_PD_RXB_Q��ch1 rxb q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [3] reserved
            [2:0] CH1_RX_MODE��ch1 rxģʽѡ��
                000��LTEģʽ
                001��W3Gģʽ
                010��WDCģʽ
                011��2GA/2GBģʽ
                100��CAģʽ
                101��Xģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xC90)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH1_MODE_IBCT2��ch1 op2ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
            [3:2] reserved
            [1:0] CH1_MODE_IBCT1��ch1 op1ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xC91)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR10
   ��      ����[7] CH1_DEM_ENB
                0:DEM Enable(Ĭ��)
                1:DEM Disable
            [6:4] CH1_DEM_MODE
                000:DWAģʽ��Ĭ�ϣ�
                001:CLA1ģʽ
                010:CLA2ģʽ
                ��
                111:CLA7ģʽ
            [3] CH1_PDM_CTRL
                0:��ͱ���(Ĭ��)
                1:����������
            [2] CH1_DEM_OUTPUT_SEL
                0:��ͱ���(Ĭ��)
                1:����������
            [1:0] CH1_MODE_IBCT3��ch1 op3ģʽѡ��
                00��W3G/2GAģʽ
                01��WDC/X/2GBģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xC92)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR11
   ��      ����[7:6] CH1_CTRL_RFF��ch1 ǰ������rffѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/X/TDSģʽ
            [5:4] CH1_CTRL_RIN1��ch1 ������1�������rin1ѡ��
                00��Off
                01��WDC/TDS/Xģʽ
                10��2GA/W3Gģʽ
                11��CA/LTE/2GBģʽ
            [3:2] CH1_CTRL_RIN2��ch1 ������2�������rin2ѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/Xģʽ
            [1] CH1_CTRL_RIN3��ch1 ������3�������rin3ѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
            [0] CH1_CTRL_RFB��ch1 ��������������rfbѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xC93)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH1_CTRL_RSIG��ch1 �������ź�ǰ������rsigѡ��
                00��Off
                01��2GA/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/X/2GBģʽ
            [3:0] CH1_CTRL_RZ��ch1 ������3�������rzѡ��
                x000��320 ohm
                x100��160 ohm
                x110��80 ohm
                xxx1��0 ohm��Ĭ��1111��
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xC94)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR13
   ��      ����[7:6] reserved
            [5] CH1_ADC_CLK_DIV2��ch1 adc���ʱ��2��Ƶ����
                  0��1��Ƶ ����ģʽ
                  1��2��Ƶ 2GAģʽ
            [4] CH1_DLY_CTRL2��ch1 0.6tsʱ�����ڿ���ѡ��
                  0��0.5Ts
                  1��0.6Ts
            [3] reserved
            [2] CH1_DCTRL23��ch1 dac23����ģʽѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
            [1:0] CH1_DCTRL1��ch1 dac1����ģʽѡ��
                00��2GA/W3Gģʽ
                01��Reserved
                10��WDC/TDS/Xģʽ
                01��CA/LTE/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xC95)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR14
   ��      ����[7:6] reserved
            [5:4] CH1_RX_CAP3_MODE��ch1 ������3����cap3ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [3:2] CH1_RX_CAP2_MODE��ch1 ������2����cap2ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [1:0] CH1_RX_CAP1_MODE��ch1 ������1����cap1ģʽѡ��
                01��CAģʽ
                10��LTE/WDC/TDS/X/W3G/2GA/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xC96)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH1_IBCT_OP2��ch1 rx op2������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH1_IBCT_OP1��ch1 rx op1������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xC97)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH1_IBCT_DAC��ch1 rx dac������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH1_IBCT_OP3��ch1 rx op3������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xC98)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR17
   ��      ����[7:6] reserved
            [5:4] CH1_MULTI_RATE_CAP3��ch1 rx������3����cap3�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [3:2] CH1_MULTI_RATE_CAP2��ch1 rx������2����cap2�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [1:0] CH1_MULTI_RATE_CAP1��ch1 rx������1����cap1�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xC99)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR18
   ��      ����[7] CH1_RXA_DCLK_INV��ch1 rxa dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH1_RXB_DCLK_INV��ch1 rxb dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH1_CLKDIV2_A2D��ch1 rx a2d clock����Ƶѡ��
                0��ѡ�����Ƶ����� CA/2GA/2GBģʽ
                1������Ƶ��� LTE/WDC/W3G/TDS/X
            [4] CH1_CLKDIV2_RX��ch1 rx clock����Ƶѡ��
                0��ѡ�����Ƶ����� W3Gģʽ
                1������Ƶ��� ����ģʽ
            [3] CH1_DCLK_A2D_INV��ch1 rx a2d clock����ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2:0] CH1_CLKMUX_CTRL��ch1 rx ģʽ��Ƶʱ��ѡ��
               000��8��Ƶ CAģʽ
               001��4��Ƶ LTEģʽ
               011��2��Ƶ WDC/TDS/X/2GBģʽ
               111��1��Ƶ W3G/2GAģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xC9A)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR19
   ��      ����[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL��ch1 rxa dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xC9B)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR20
   ��      ����[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL��ch1 rxa qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xC9C)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR21
   ��      ����[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL��ch1 rxb dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xC9D)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR22
   ��      ����[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL��ch1 rxb qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xC9E)

/* �Ĵ���˵����RX 3G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR23
   ��      ����[7] CH1_CLKIN3_INV_RXB_Q��ch1 rxb q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH1_CLKIN3_INV_RXB_I��ch1 rxb i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH1_CLKIN2_INV_RXB_Q��ch1 rxb q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [4] CH1_CLKIN2_INV_RXB_I��ch1 rxb i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [3] CH1_CLKIN3_INV_RXA_Q��ch1 rxa q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2] CH1_CLKIN3_INV_RXA_I��ch1 rxa i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [1] CH1_CLKIN2_INV_RXA_Q��ch1 rxa q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [0] CH1_CLKIN2_INV_RXA_I��ch1 rxa i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
   UNION�ṹ ���� */
#define ABB_CH1_RX_3G_ANA_16_ADDR                     (ABB_BASE_ADDR + 0xC9F)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR08
   ��      ����[7] CH1_PD_RXA_I��ch1 rxa i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [6] CH1_PD_RXA_Q��ch1 rxa q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [5] CH1_PD_RXB_I��ch1 rxb i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [4] CH1_PD_RXB_Q��ch1 rxb q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [3] reserved
            [2:0] CH1_RX_MODE��ch1 rxģʽѡ��
                000��LTEģʽ
                001��W3Gģʽ
                010��WDCģʽ
                011��2GA/2GBģʽ
                100��CAģʽ
                101��Xģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_1_ADDR                      (ABB_BASE_ADDR + 0xCA0)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH1_MODE_IBCT2��ch1 op2ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
            [3:2] reserved
            [1:0] CH1_MODE_IBCT1��ch1 op1ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_2_ADDR                      (ABB_BASE_ADDR + 0xCA1)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR10
   ��      ����[7] CH1_DEM_ENB
                0:DEM Enable(Ĭ��)
                1:DEM Disable
            [6:4] CH1_DEM_MODE
                000:DWAģʽ��Ĭ�ϣ�
                001:CLA1ģʽ
                010:CLA2ģʽ
                ��
                111:CLA7ģʽ
            [3] CH1_PDM_CTRL
                0:��ͱ���(Ĭ��)
                1:����������
            [2] CH1_DEM_OUTPUT_SEL
                0:��ͱ���(Ĭ��)
                1:����������
            [1:0] CH1_MODE_IBCT3��ch1 op3ģʽѡ��
                00��W3G/2GAģʽ
                01��WDC/X/2GBģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_3_ADDR                      (ABB_BASE_ADDR + 0xCA2)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR11
   ��      ����[7:6] CH1_CTRL_RFF��ch1 ǰ������rffѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/X/TDSģʽ
            [5:4] CH1_CTRL_RIN1��ch1 ������1�������rin1ѡ��
                00��Off
                01��WDC/TDS/Xģʽ
                10��2GA/W3Gģʽ
                11��CA/LTE/2GBģʽ
            [3:2] CH1_CTRL_RIN2��ch1 ������2�������rin2ѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/Xģʽ
            [1] CH1_CTRL_RIN3��ch1 ������3�������rin3ѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
            [0] CH1_CTRL_RFB��ch1 ��������������rfbѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_4_ADDR                      (ABB_BASE_ADDR + 0xCA3)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH1_CTRL_RSIG��ch1 �������ź�ǰ������rsigѡ��
                00��Off
                01��2GA/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/X/2GBģʽ
            [3:0] CH1_CTRL_RZ��ch1 ������3�������rzѡ��
                x000��320 ohm
                x100��160 ohm
                x110��80 ohm
                xxx1��0 ohm��Ĭ��1111��
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_5_ADDR                      (ABB_BASE_ADDR + 0xCA4)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR13
   ��      ����[7:6] reserved
            [5] CH1_ADC_CLK_DIV2��ch1 adc���ʱ��2��Ƶ����
                  0��1��Ƶ ����ģʽ
                  1��2��Ƶ 2GAģʽ
            [4] CH1_DLY_CTRL2��ch1 0.6tsʱ�����ڿ���ѡ��
                  0��0.5Ts
                  1��0.6Ts
            [3] reserved
            [2] CH1_DCTRL23��ch1 dac23����ģʽѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
            [1:0] CH1_DCTRL1��ch1 dac1����ģʽѡ��
                00��2GA/W3Gģʽ
                01��Reserved
                10��WDC/TDS/Xģʽ
                01��CA/LTE/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_6_ADDR                      (ABB_BASE_ADDR + 0xCA5)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR14
   ��      ����[7:6] reserved
            [5:4] CH1_RX_CAP3_MODE��ch1 ������3����cap3ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [3:2] CH1_RX_CAP2_MODE��ch1 ������2����cap2ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [1:0] CH1_RX_CAP1_MODE��ch1 ������1����cap1ģʽѡ��
                01��CAģʽ
                10��LTE/WDC/TDS/X/W3G/2GA/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_7_ADDR                      (ABB_BASE_ADDR + 0xCA6)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH1_IBCT_OP2��ch1 rx op2������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH1_IBCT_OP1��ch1 rx op1������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_8_ADDR                      (ABB_BASE_ADDR + 0xCA7)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH1_IBCT_DAC��ch1 rx dac������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH1_IBCT_OP3��ch1 rx op3������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_9_ADDR                      (ABB_BASE_ADDR + 0xCA8)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR17
   ��      ����[7:6] reserved
            [5:4] CH1_MULTI_RATE_CAP3��ch1 rx������3����cap3�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [3:2] CH1_MULTI_RATE_CAP2��ch1 rx������2����cap2�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [1:0] CH1_MULTI_RATE_CAP1��ch1 rx������1����cap1�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_10_ADDR                     (ABB_BASE_ADDR + 0xCA9)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR18
   ��      ����[7] CH1_RXA_DCLK_INV��ch1 rxa dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH1_RXB_DCLK_INV��ch1 rxb dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH1_CLKDIV2_A2D��ch1 rx a2d clock����Ƶѡ��
                0��ѡ�����Ƶ����� CA/2GA/2GBģʽ
                1������Ƶ��� LTE/WDC/W3G/TDS/X
            [4] CH1_CLKDIV2_RX��ch1 rx clock����Ƶѡ��
                0��ѡ�����Ƶ����� W3Gģʽ
                1������Ƶ��� ����ģʽ
            [3] CH1_DCLK_A2D_INV��ch1 rx a2d clock����ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2:0] CH1_CLKMUX_CTRL��ch1 rx ģʽ��Ƶʱ��ѡ��
               000��8��Ƶ CAģʽ
               001��4��Ƶ LTEģʽ
               011��2��Ƶ WDC/TDS/X/2GBģʽ
               111��1��Ƶ W3G/2GAģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_11_ADDR                     (ABB_BASE_ADDR + 0xCAA)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR19
   ��      ����[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL��ch1 rxa dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_12_ADDR                     (ABB_BASE_ADDR + 0xCAB)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR20
   ��      ����[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL��ch1 rxa qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_13_ADDR                     (ABB_BASE_ADDR + 0xCAC)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR21
   ��      ����[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL��ch1 rxb dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_14_ADDR                     (ABB_BASE_ADDR + 0xCAD)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR22
   ��      ����[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL��ch1 rxb qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_15_ADDR                     (ABB_BASE_ADDR + 0xCAE)

/* �Ĵ���˵����RX 4G���üĴ����������߿��߼�������CH1_REG_ANALOG_WR23
   ��      ����[7] CH1_CLKIN3_INV_RXB_Q��ch1 rxb q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH1_CLKIN3_INV_RXB_I��ch1 rxb i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH1_CLKIN2_INV_RXB_Q��ch1 rxb q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [4] CH1_CLKIN2_INV_RXB_I��ch1 rxb i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [3] CH1_CLKIN3_INV_RXA_Q��ch1 rxa q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2] CH1_CLKIN3_INV_RXA_I��ch1 rxa i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [1] CH1_CLKIN2_INV_RXA_Q��ch1 rxa q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [0] CH1_CLKIN2_INV_RXA_I��ch1 rxa i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
   UNION�ṹ ���� */
#define ABB_CH1_RX_4G_ANA_16_ADDR                     (ABB_BASE_ADDR + 0xCAF)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR08
   ��      ����[7] CH1_PD_RXA_I��ch1 rxa i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [6] CH1_PD_RXA_Q��ch1 rxa q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [5] CH1_PD_RXB_I��ch1 rxb i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [4] CH1_PD_RXB_Q��ch1 rxb q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [3] reserved
            [2:0] CH1_RX_MODE��ch1 rxģʽѡ��
                000��LTEģʽ
                001��W3Gģʽ
                010��WDCģʽ
                011��2GA/2GBģʽ
                100��CAģʽ
                101��Xģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_1_ADDR                     (ABB_BASE_ADDR + 0xCB0)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH1_MODE_IBCT2��ch1 op2ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
            [3:2] reserved
            [1:0] CH1_MODE_IBCT1��ch1 op1ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_2_ADDR                     (ABB_BASE_ADDR + 0xCB1)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR10
   ��      ����[7] CH1_DEM_ENB
                0:DEM Enable(Ĭ��)
                1:DEM Disable
            [6:4] CH1_DEM_MODE
                000:DWAģʽ��Ĭ�ϣ�
                001:CLA1ģʽ
                010:CLA2ģʽ
                ��
                111:CLA7ģʽ
            [3] CH1_PDM_CTRL
                0:��ͱ���(Ĭ��)
                1:����������
            [2] CH1_DEM_OUTPUT_SEL
                0:��ͱ���(Ĭ��)
                1:����������
            [1:0] CH1_MODE_IBCT3��ch1 op3ģʽѡ��
                00��W3G/2GAģʽ
                01��WDC/X/2GBģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_3_ADDR                     (ABB_BASE_ADDR + 0xCB2)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR11
   ��      ����[7:6] CH1_CTRL_RFF��ch1 ǰ������rffѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/X/TDSģʽ
            [5:4] CH1_CTRL_RIN1��ch1 ������1�������rin1ѡ��
                00��Off
                01��WDC/TDS/Xģʽ
                10��2GA/W3Gģʽ
                11��CA/LTE/2GBģʽ
            [3:2] CH1_CTRL_RIN2��ch1 ������2�������rin2ѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/Xģʽ
            [1] CH1_CTRL_RIN3��ch1 ������3�������rin3ѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
            [0] CH1_CTRL_RFB��ch1 ��������������rfbѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_4_ADDR                     (ABB_BASE_ADDR + 0xCB3)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH1_CTRL_RSIG��ch1 �������ź�ǰ������rsigѡ��
                00��Off
                01��2GA/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/X/2GBģʽ
            [3:0] CH1_CTRL_RZ��ch1 ������3�������rzѡ��
                x000��320 ohm
                x100��160 ohm
                x110��80 ohm
                xxx1��0 ohm��Ĭ��1111��
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_5_ADDR                     (ABB_BASE_ADDR + 0xCB4)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR13
   ��      ����[7:6] reserved
            [5] CH1_ADC_CLK_DIV2��ch1 adc���ʱ��2��Ƶ����
                  0��1��Ƶ ����ģʽ
                  1��2��Ƶ 2GAģʽ
            [4] CH1_DLY_CTRL2��ch1 0.6tsʱ�����ڿ���ѡ��
                  0��0.5Ts
                  1��0.6Ts
            [3] reserved
            [2] CH1_DCTRL23��ch1 dac23����ģʽѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
            [1:0] CH1_DCTRL1��ch1 dac1����ģʽѡ��
                00��2GA/W3Gģʽ
                01��Reserved
                10��WDC/TDS/Xģʽ
                01��CA/LTE/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_6_ADDR                     (ABB_BASE_ADDR + 0xCB5)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR14
   ��      ����[7:6] reserved
            [5:4] CH1_RX_CAP3_MODE��ch1 ������3����cap3ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [3:2] CH1_RX_CAP2_MODE��ch1 ������2����cap2ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [1:0] CH1_RX_CAP1_MODE��ch1 ������1����cap1ģʽѡ��
                01��CAģʽ
                10��LTE/WDC/TDS/X/W3G/2GA/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_7_ADDR                     (ABB_BASE_ADDR + 0xCB6)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH1_IBCT_OP2��ch1 rx op2������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH1_IBCT_OP1��ch1 rx op1������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_8_ADDR                     (ABB_BASE_ADDR + 0xCB7)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH1_IBCT_DAC��ch1 rx dac������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH1_IBCT_OP3��ch1 rx op3������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_9_ADDR                     (ABB_BASE_ADDR + 0xCB8)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR17
   ��      ����[7:6] reserved
            [5:4] CH1_MULTI_RATE_CAP3��ch1 rx������3����cap3�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [3:2] CH1_MULTI_RATE_CAP2��ch1 rx������2����cap2�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [1:0] CH1_MULTI_RATE_CAP1��ch1 rx������1����cap1�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_10_ADDR                    (ABB_BASE_ADDR + 0xCB9)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR18
   ��      ����[7] CH1_RXA_DCLK_INV��ch1 rxa dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH1_RXB_DCLK_INV��ch1 rxb dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH1_CLKDIV2_A2D��ch1 rx a2d clock����Ƶѡ��
                0��ѡ�����Ƶ����� CA/2GA/2GBģʽ
                1������Ƶ��� LTE/WDC/W3G/TDS/X
            [4] CH1_CLKDIV2_RX��ch1 rx clock����Ƶѡ��
                0��ѡ�����Ƶ����� W3Gģʽ
                1������Ƶ��� ����ģʽ
            [3] CH1_DCLK_A2D_INV��ch1 rx a2d clock����ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2:0] CH1_CLKMUX_CTRL��ch1 rx ģʽ��Ƶʱ��ѡ��
               000��8��Ƶ CAģʽ
               001��4��Ƶ LTEģʽ
               011��2��Ƶ WDC/TDS/X/2GBģʽ
               111��1��Ƶ W3G/2GAģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_11_ADDR                    (ABB_BASE_ADDR + 0xCBA)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR19
   ��      ����[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL��ch1 rxa dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_12_ADDR                    (ABB_BASE_ADDR + 0xCBB)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR20
   ��      ����[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL��ch1 rxa qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_13_ADDR                    (ABB_BASE_ADDR + 0xCBC)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR21
   ��      ����[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL��ch1 rxb dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_14_ADDR                    (ABB_BASE_ADDR + 0xCBD)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR22
   ��      ����[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL��ch1 rxb qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_15_ADDR                    (ABB_BASE_ADDR + 0xCBE)

/* �Ĵ���˵����RX TDS���üĴ����������߿��߼�������CH1_REG_ANALOG_WR23
   ��      ����[7] CH1_CLKIN3_INV_RXB_Q��ch1 rxb q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH1_CLKIN3_INV_RXB_I��ch1 rxb i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH1_CLKIN2_INV_RXB_Q��ch1 rxb q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [4] CH1_CLKIN2_INV_RXB_I��ch1 rxb i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [3] CH1_CLKIN3_INV_RXA_Q��ch1 rxa q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2] CH1_CLKIN3_INV_RXA_I��ch1 rxa i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [1] CH1_CLKIN2_INV_RXA_Q��ch1 rxa q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [0] CH1_CLKIN2_INV_RXA_I��ch1 rxa i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
   UNION�ṹ ���� */
#define ABB_CH1_RX_TDS_ANA_16_ADDR                    (ABB_BASE_ADDR + 0xCBF)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR08
   ��      ����[7] CH1_PD_RXA_I��ch1 rxa i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [6] CH1_PD_RXA_Q��ch1 rxa q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [5] CH1_PD_RXB_I��ch1 rxb i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [4] CH1_PD_RXB_Q��ch1 rxb q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [3] reserved
            [2:0] CH1_RX_MODE��ch1 rxģʽѡ��
                000��LTEģʽ
                001��W3Gģʽ
                010��WDCģʽ
                011��2GA/2GBģʽ
                100��CAģʽ
                101��Xģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_1_ADDR                       (ABB_BASE_ADDR + 0xCC0)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH1_MODE_IBCT2��ch1 op2ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
            [3:2] reserved
            [1:0] CH1_MODE_IBCT1��ch1 op1ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_2_ADDR                       (ABB_BASE_ADDR + 0xCC1)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR10
   ��      ����[7] CH1_DEM_ENB
                0:DEM Enable(Ĭ��)
                1:DEM Disable
            [6:4] CH1_DEM_MODE
                000:DWAģʽ��Ĭ�ϣ�
                001:CLA1ģʽ
                010:CLA2ģʽ
                ��
                111:CLA7ģʽ
            [3] CH1_PDM_CTRL
                0:��ͱ���(Ĭ��)
                1:����������
            [2] CH1_DEM_OUTPUT_SEL
                0:��ͱ���(Ĭ��)
                1:����������
            [1:0] CH1_MODE_IBCT3��ch1 op3ģʽѡ��
                00��W3G/2GAģʽ
                01��WDC/X/2GBģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_3_ADDR                       (ABB_BASE_ADDR + 0xCC2)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR11
   ��      ����[7:6] CH1_CTRL_RFF��ch1 ǰ������rffѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/X/TDSģʽ
            [5:4] CH1_CTRL_RIN1��ch1 ������1�������rin1ѡ��
                00��Off
                01��WDC/TDS/Xģʽ
                10��2GA/W3Gģʽ
                11��CA/LTE/2GBģʽ
            [3:2] CH1_CTRL_RIN2��ch1 ������2�������rin2ѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/Xģʽ
            [1] CH1_CTRL_RIN3��ch1 ������3�������rin3ѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
            [0] CH1_CTRL_RFB��ch1 ��������������rfbѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_4_ADDR                       (ABB_BASE_ADDR + 0xCC3)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH1_CTRL_RSIG��ch1 �������ź�ǰ������rsigѡ��
                00��Off
                01��2GA/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/X/2GBģʽ
            [3:0] CH1_CTRL_RZ��ch1 ������3�������rzѡ��
                x000��320 ohm
                x100��160 ohm
                x110��80 ohm
                xxx1��0 ohm��Ĭ��1111��
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_5_ADDR                       (ABB_BASE_ADDR + 0xCC4)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR13
   ��      ����[7:6] reserved
            [5] CH1_ADC_CLK_DIV2��ch1 adc���ʱ��2��Ƶ����
                  0��1��Ƶ ����ģʽ
                  1��2��Ƶ 2GAģʽ
            [4] CH1_DLY_CTRL2��ch1 0.6tsʱ�����ڿ���ѡ��
                  0��0.5Ts
                  1��0.6Ts
            [3] reserved
            [2] CH1_DCTRL23��ch1 dac23����ģʽѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
            [1:0] CH1_DCTRL1��ch1 dac1����ģʽѡ��
                00��2GA/W3Gģʽ
                01��Reserved
                10��WDC/TDS/Xģʽ
                01��CA/LTE/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_6_ADDR                       (ABB_BASE_ADDR + 0xCC5)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR14
   ��      ����[7:6] reserved
            [5:4] CH1_RX_CAP3_MODE��ch1 ������3����cap3ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [3:2] CH1_RX_CAP2_MODE��ch1 ������2����cap2ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [1:0] CH1_RX_CAP1_MODE��ch1 ������1����cap1ģʽѡ��
                01��CAģʽ
                10��LTE/WDC/TDS/X/W3G/2GA/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_7_ADDR                       (ABB_BASE_ADDR + 0xCC6)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH1_IBCT_OP2��ch1 rx op2������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH1_IBCT_OP1��ch1 rx op1������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_8_ADDR                       (ABB_BASE_ADDR + 0xCC7)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH1_IBCT_DAC��ch1 rx dac������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH1_IBCT_OP3��ch1 rx op3������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_9_ADDR                       (ABB_BASE_ADDR + 0xCC8)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR17
   ��      ����[7:6] reserved
            [5:4] CH1_MULTI_RATE_CAP3��ch1 rx������3����cap3�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [3:2] CH1_MULTI_RATE_CAP2��ch1 rx������2����cap2�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [1:0] CH1_MULTI_RATE_CAP1��ch1 rx������1����cap1�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_10_ADDR                      (ABB_BASE_ADDR + 0xCC9)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR18
   ��      ����[7] CH1_RXA_DCLK_INV��ch1 rxa dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH1_RXB_DCLK_INV��ch1 rxb dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH1_CLKDIV2_A2D��ch1 rx a2d clock����Ƶѡ��
                0��ѡ�����Ƶ����� CA/2GA/2GBģʽ
                1������Ƶ��� LTE/WDC/W3G/TDS/X
            [4] CH1_CLKDIV2_RX��ch1 rx clock����Ƶѡ��
                0��ѡ�����Ƶ����� W3Gģʽ
                1������Ƶ��� ����ģʽ
            [3] CH1_DCLK_A2D_INV��ch1 rx a2d clock����ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2:0] CH1_CLKMUX_CTRL��ch1 rx ģʽ��Ƶʱ��ѡ��
               000��8��Ƶ CAģʽ
               001��4��Ƶ LTEģʽ
               011��2��Ƶ WDC/TDS/X/2GBģʽ
               111��1��Ƶ W3G/2GAģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_11_ADDR                      (ABB_BASE_ADDR + 0xCCA)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR19
   ��      ����[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL��ch1 rxa dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_12_ADDR                      (ABB_BASE_ADDR + 0xCCB)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR20
   ��      ����[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL��ch1 rxa qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_13_ADDR                      (ABB_BASE_ADDR + 0xCCC)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR21
   ��      ����[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL��ch1 rxb dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_14_ADDR                      (ABB_BASE_ADDR + 0xCCD)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR22
   ��      ����[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL��ch1 rxb qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_15_ADDR                      (ABB_BASE_ADDR + 0xCCE)

/* �Ĵ���˵����RX X���üĴ����������߿��߼�������CH1_REG_ANALOG_WR23
   ��      ����[7] CH1_CLKIN3_INV_RXB_Q��ch1 rxb q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH1_CLKIN3_INV_RXB_I��ch1 rxb i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH1_CLKIN2_INV_RXB_Q��ch1 rxb q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [4] CH1_CLKIN2_INV_RXB_I��ch1 rxb i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [3] CH1_CLKIN3_INV_RXA_Q��ch1 rxa q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2] CH1_CLKIN3_INV_RXA_I��ch1 rxa i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [1] CH1_CLKIN2_INV_RXA_Q��ch1 rxa q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [0] CH1_CLKIN2_INV_RXA_I��ch1 rxa i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
   UNION�ṹ ���� */
#define ABB_CH1_RX_X_ANA_16_ADDR                      (ABB_BASE_ADDR + 0xCCF)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR08
   ��      ����[7] CH1_PD_RXA_I��ch1 rxa i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [6] CH1_PD_RXA_Q��ch1 rxa q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [5] CH1_PD_RXB_I��ch1 rxb i·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [4] CH1_PD_RXB_Q��ch1 rxb q·power down����
                0��Power on
                1��Power Down��Ĭ�ϣ�
            [3] reserved
            [2:0] CH1_RX_MODE��ch1 rxģʽѡ��
                000��LTEģʽ
                001��W3Gģʽ
                010��WDCģʽ
                011��2GA/2GBģʽ
                100��CAģʽ
                101��Xģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_1_ADDR                    (ABB_BASE_ADDR + 0xCD0)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR09
   ��      ����[7:6] reserved
            [5:4] CH1_MODE_IBCT2��ch1 op2ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
            [3:2] reserved
            [1:0] CH1_MODE_IBCT1��ch1 op1ģʽѡ��
                00��W3Gģʽ
                01��WDCģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_2_ADDR                    (ABB_BASE_ADDR + 0xCD1)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR10
   ��      ����[7] CH1_DEM_ENB
                0:DEM Enable(Ĭ��)
                1:DEM Disable
            [6:4] CH1_DEM_MODE
                000:DWAģʽ��Ĭ�ϣ�
                001:CLA1ģʽ
                010:CLA2ģʽ
                ��
                111:CLA7ģʽ
            [3] CH1_PDM_CTRL
                0:��ͱ���(Ĭ��)
                1:����������
            [2] CH1_DEM_OUTPUT_SEL
                0:��ͱ���(Ĭ��)
                1:����������
            [1:0] CH1_MODE_IBCT3��ch1 op3ģʽѡ��
                00��W3G/2GAģʽ
                01��WDC/X/2GBģʽ
                10��LTEģʽ
                11��CAģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_3_ADDR                    (ABB_BASE_ADDR + 0xCD2)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR11
   ��      ����[7:6] CH1_CTRL_RFF��ch1 ǰ������rffѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/X/TDSģʽ
            [5:4] CH1_CTRL_RIN1��ch1 ������1�������rin1ѡ��
                00��Off
                01��WDC/TDS/Xģʽ
                10��2GA/W3Gģʽ
                11��CA/LTE/2GBģʽ
            [3:2] CH1_CTRL_RIN2��ch1 ������2�������rin2ѡ��
                00��Off
                01��2GA/2GB/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/Xģʽ
            [1] CH1_CTRL_RIN3��ch1 ������3�������rin3ѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
            [0] CH1_CTRL_RFB��ch1 ��������������rfbѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_4_ADDR                    (ABB_BASE_ADDR + 0xCD3)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR12
   ��      ����[7:6] reserved
            [5:4] CH1_CTRL_RSIG��ch1 �������ź�ǰ������rsigѡ��
                00��Off
                01��2GA/W3Gģʽ
                10��Reserved
                11��CA/LTE/WDC/TDS/X/2GBģʽ
            [3:0] CH1_CTRL_RZ��ch1 ������3�������rzѡ��
                x000��320 ohm
                x100��160 ohm
                x110��80 ohm
                xxx1��0 ohm��Ĭ��1111��
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_5_ADDR                    (ABB_BASE_ADDR + 0xCD4)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR13
   ��      ����[7:6] reserved
            [5] CH1_ADC_CLK_DIV2��ch1 adc���ʱ��2��Ƶ����
                  0��1��Ƶ ����ģʽ
                  1��2��Ƶ 2GAģʽ
            [4] CH1_DLY_CTRL2��ch1 0.6tsʱ�����ڿ���ѡ��
                  0��0.5Ts
                  1��0.6Ts
            [3] reserved
            [2] CH1_DCTRL23��ch1 dac23����ģʽѡ��
                0��2GA/W3Gģʽ
                1��CA/LTE/WDC/TDS/X/2GBģʽ
            [1:0] CH1_DCTRL1��ch1 dac1����ģʽѡ��
                00��2GA/W3Gģʽ
                01��Reserved
                10��WDC/TDS/Xģʽ
                01��CA/LTE/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_6_ADDR                    (ABB_BASE_ADDR + 0xCD5)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR14
   ��      ����[7:6] reserved
            [5:4] CH1_RX_CAP3_MODE��ch1 ������3����cap3ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [3:2] CH1_RX_CAP2_MODE��ch1 ������2����cap2ģʽѡ��
                00��CAģʽ
                01��LTEģʽ
                10��WDC/TDS/X/W3G/2GA/2GBģʽ
            [1:0] CH1_RX_CAP1_MODE��ch1 ������1����cap1ģʽѡ��
                01��CAģʽ
                10��LTE/WDC/TDS/X/W3G/2GA/2GBģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_7_ADDR                    (ABB_BASE_ADDR + 0xCD6)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR15
   ��      ����[7] reserved
            [6:4] CH1_IBCT_OP2��ch1 rx op2������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH1_IBCT_OP1��ch1 rx op1������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_8_ADDR                    (ABB_BASE_ADDR + 0xCD7)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR16
   ��      ����[7] reserved
            [6:4] CH1_IBCT_DAC��ch1 rx dac������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
            [3] reserved
            [2:0] CH1_IBCT_OP3��ch1 rx op3������С����
                000��5u��Ĭ�ϣ�
                001��4u
                010��3u
                011��2u
                100��10u
                101��9u
                110��8u
                111��7u
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_9_ADDR                    (ABB_BASE_ADDR + 0xCD8)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR17
   ��      ����[7:6] reserved
            [5:4] CH1_MULTI_RATE_CAP3��ch1 rx������3����cap3�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [3:2] CH1_MULTI_RATE_CAP2��ch1 rx������2����cap2�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
            [1:0] CH1_MULTI_RATE_CAP1��ch1 rx������1����cap1�˻�����ѡ��
                00��1�� ����ģʽ
                10��1.25�� Xģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_10_ADDR                   (ABB_BASE_ADDR + 0xCD9)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR18
   ��      ����[7] CH1_RXA_DCLK_INV��ch1 rxa dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH1_RXB_DCLK_INV��ch1 rxb dclk�������ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH1_CLKDIV2_A2D��ch1 rx a2d clock����Ƶѡ��
                0��ѡ�����Ƶ����� CA/2GA/2GBģʽ
                1������Ƶ��� LTE/WDC/W3G/TDS/X
            [4] CH1_CLKDIV2_RX��ch1 rx clock����Ƶѡ��
                0��ѡ�����Ƶ����� W3Gģʽ
                1������Ƶ��� ����ģʽ
            [3] CH1_DCLK_A2D_INV��ch1 rx a2d clock����ѡ��
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2:0] CH1_CLKMUX_CTRL��ch1 rx ģʽ��Ƶʱ��ѡ��
               000��8��Ƶ CAģʽ
               001��4��Ƶ LTEģʽ
               011��2��Ƶ WDC/TDS/X/2GBģʽ
               111��1��Ƶ W3G/2GAģʽ
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_11_ADDR                   (ABB_BASE_ADDR + 0xCDA)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR19
   ��      ����[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL��ch1 rxa dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_12_ADDR                   (ABB_BASE_ADDR + 0xCDB)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR20
   ��      ����[7:5] reserved
            [4:0] CH1_RXA_CLK_DAC3_CTRL��ch1 rxa qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_13_ADDR                   (ABB_BASE_ADDR + 0xCDC)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR21
   ��      ����[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL��ch1 rxb dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_14_ADDR                   (ABB_BASE_ADDR + 0xCDD)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR22
   ��      ����[7:5] reserved
            [4:0] CH1_RXB_CLK_DAC3_CTRL��ch1 rxb qt��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_15_ADDR                   (ABB_BASE_ADDR + 0xCDE)

/* �Ĵ���˵����RX IDLE���üĴ����������߿��߼�������CH1_REG_ANALOG_WR23
   ��      ����[7] CH1_CLKIN3_INV_RXB_Q��ch1 rxb q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [6] CH1_CLKIN3_INV_RXB_I��ch1 rxb i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [5] CH1_CLKIN2_INV_RXB_Q��ch1 rxb q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [4] CH1_CLKIN2_INV_RXB_I��ch1 rxb i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [3] CH1_CLKIN3_INV_RXA_Q��ch1 rxa q·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [2] CH1_CLKIN3_INV_RXA_I��ch1 rxa i·clkin3 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [1] CH1_CLKIN2_INV_RXA_Q��ch1 rxa q·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
            [0] CH1_CLKIN2_INV_RXA_I��ch1 rxa i·clkin2 dff�����ؿ���
                0�����ز�����Ĭ�ϣ�
                1�����ز���
   UNION�ṹ ���� */
#define ABB_CH1_RX_IDLE_ANA_16_ADDR                   (ABB_BASE_ADDR + 0xCDF)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7:0] CH1_REG_TUNE1��ch1 rx cap1�ֶ����üĴ���
                0100 0000(Ĭ��)
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA16_ADDR                  (ABB_BASE_ADDR + 0xCE0)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7:0] CH1_REG_TUNE2��ch1 rx cap2�ֶ����üĴ���
                0100 0000(Ĭ��)
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA17_ADDR                  (ABB_BASE_ADDR + 0xCE1)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7:0] CH1_REG_TUNE3��ch1 rx cap3�ֶ����üĴ���
                0100 0000(Ĭ��)
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA18_ADDR                  (ABB_BASE_ADDR + 0xCE2)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7] CH1_RX_TUNE_SEL
                0��tuning��������rctuneģ��
                1��tuning�������ڼĴ�������
            [6:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA19_ADDR                  (ABB_BASE_ADDR + 0xCE3)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7] reserved
            [6:4] CH1_OL_CTRL��ch1 rx overload����ѡ��
                000��16����������������С�룬ͬʱ����int1��int2��int3��Ĭ�ϣ�
                001��8����������������С�룬ͬʱ����int1��int2��int3
                010��4����������������С�룬ͬʱ����int1��int2��int3
                011���ر�Overload��⣬ͬʱ����int1��int2��int3
                100��16����������������С�룬����˳��Ϊint3-->int2-->int1
                101��8����������������С�룬����˳��Ϊint3-->int2-->int1
                110��4����������������С�룬����˳��Ϊint3-->int2-->int1
                111���ر�Overload��⣬����˳��Ϊint3-->int2-->int1
            [3:2] reserved
            [1] CH1_PUP_CLK_CTRL��ch1 rx �����ϵ�ʱ�ӿ���
                0���ϵ���ɺ�ر��ϵ�ģ���ʱ�ӣ�Ĭ�ϣ�
                1���ϵ���ɺ󲻹ر��ϵ�ģ��ʱ��
            [0] CH1_PUP_MODE��ch1 rx �����ϵ�ģʽ
                0���Զ�ģʽ��Ĭ�ϣ�
                1�����üĴ����ϵ�ģʽ
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA20_ADDR                  (ABB_BASE_ADDR + 0xCE4)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7] CH1_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��RST_CAP����
                0��Reset CAP3
                1����Reset CAP3
            [6] CH1_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��RST_CAP����
                0��Reset CAP2
                1����Reset CAP2
            [5] CH1_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��RST_CAP����
                0��Reset CAP1
                1����Reset CAP1
            [4] CH1_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��OP����
                0��OP Power Down
                1��OP Power On
            [3] CH1_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��DAC����
                0��DAC Power Down
                1��DAC Power On
            [2] CH1_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��QTУ������
                0��QT Calibration On
                1��QT Calibration Off
            [1] CH1_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��CLKGEN����
                0��CLKGEN Power Down
                1��CLKGEN Power On
            [0] CH1_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��QT����
                0��QT Power Down
                1��QT Power On
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA21_ADDR                  (ABB_BASE_ADDR + 0xCE5)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7:6] reserved
            [5] CH1_QT_REF_SEL��ch1 rx qt��refѡ��
                0��vrefp/vrefn������refģ�飨Ĭ�ϣ�
                1��vrefp/vrefn�����ڱ��ط�ѹ
            [4] CH1_EN_QTCAL��ch1 rx qtУ׼enable
                0���Ƚ���У׼Disable��Ĭ�ϣ�
                1���Ƚ���У׼Enable��Ĭ�ϣ�
            [3] CH1_CAL_SW��ch1 rx op1У׼���ؿ���
                0��Ĭ��
                1������
            [2] CH1_CAL_TRIM_SW��ch1 rx op1У׼trim���ؿ���
                0��cal trim����disable��Ĭ�ϣ�
                1��cal trim����enable��Ĭ�ϣ�
            [1] CH1_OPCAL_VCM_SEL��ch1 rx op1У׼��ģѡ��
                0��op1У׼�̽�����˹�ģDisable��Ĭ�ϣ�
                1��op1У׼�̽�����˹�ģEnable��Ĭ�ϣ�
            [0] CH1_EN_OPCAL��ch1 rx op1У׼enable
                0��op1У׼Disable��Ĭ�ϣ�
                1��op1У׼Enable��Ĭ�ϣ�
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA22_ADDR                  (ABB_BASE_ADDR + 0xCE6)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7:4] reserved
            [3] CH1_RXB_PATH_CTRL_Q��ch1 rxb q·��·����ͨ·ѡ��rxb����������ģʽ
                0��ͨ·�Ͽ�����ѡ���ͨ·
                1��ͨ·��ͨ��ѡ���ͨ·
            [2] CH1_RXB_PATH_CTRL_I��ch1 rxb i·��·����ͨ·ѡ��rxb����������ģʽ
                0��ͨ·�Ͽ�����ѡ���ͨ·
                1��ͨ·��ͨ��ѡ���ͨ·
            [1] CH1_RXA_PATH_CTRL_Q��ch1 rxa q·��·����ͨ·ѡ��rxa����������ģʽ
                0��ͨ·�Ͽ�����ѡ���ͨ·
                1��ͨ·��ͨ��ѡ���ͨ·
            [0] CH1_RXA_PATH_CTRL_I��ch1 rxa i·��·����ͨ·ѡ��rxa����������ģʽ
                0��ͨ·�Ͽ�����ѡ���ͨ·
                1��ͨ·��ͨ��ѡ���ͨ·
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA23_ADDR                  (ABB_BASE_ADDR + 0xCE7)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA24_ADDR                  (ABB_BASE_ADDR + 0xCE8)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA25_ADDR                  (ABB_BASE_ADDR + 0xCE9)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA26_ADDR                  (ABB_BASE_ADDR + 0xCEA)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA27_ADDR                  (ABB_BASE_ADDR + 0xCEB)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA28_ADDR                  (ABB_BASE_ADDR + 0xCEC)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA29_ADDR                  (ABB_BASE_ADDR + 0xCED)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA30_ADDR                  (ABB_BASE_ADDR + 0xCEE)

/* �Ĵ���˵����RX ch1���üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_CH1_REG_DEBUG_ANA31_ADDR                  (ABB_BASE_ADDR + 0xCEF)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:6] reserved
            [5] CH3_PD_RXC_Q��ch3 rxc q·power down����
            0:Power On
            1:Power Down��Ĭ�ϣ�
            [4] CH3_PD_RXC_I��ch3 rxc i·power down����
            0:Power On
            1:Power Down��Ĭ�ϣ�
            [3] CH3_PD_RXB_Q��ch3 rxb q·power down����
            0:Power On
            1:Power Down��Ĭ�ϣ�
            [2] CH3_PD_RXB_I��ch3 rxb i·power down����
            0:Power On
            1:Power Down��Ĭ�ϣ�
            [1] CH3_PD_RXA_Q��ch3 rxa q·power down����
            0:Power On
            1:Power Down��Ĭ�ϣ�
            [0] CH3_PD_RXA_I��ch3 rxa i·power down����
            0:Power On
            1:Power Down��Ĭ�ϣ�
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR26_ADDR                      (ABB_BASE_ADDR + 0xE00)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:3] reserved
            [2:0] CH3_RX_MODE��ch3 rxģʽѡ��
            000��CAģʽ
            001��3Gģʽ��Xģʽ
            010��3Gģʽ��Xģʽ
            011��2Gģʽ
            100��50Mģʽ
            101��LTEģʽ
            110��LTEģʽ
            111��LTEģʽ
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR27_ADDR                      (ABB_BASE_ADDR + 0xE01)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:6] reserved
            [5:4] CH3_MODE_IBCT2��ch3 op2����ģʽѡ��
            00��3Gģʽ&amp;2Gģʽ&amp;Xģʽ
            01��LTEģʽ
            10��CAģʽ
            11��50Mģʽ
            [3:2] reserved
            [1:0] CH3_MODE_IBCT1��ch3 op1����ģʽѡ��
            00��3Gģʽ&amp;2Gģʽ&amp;Xģʽ
            01��LTEģʽ
            10��CAģʽ
            11��50Mģʽ
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR28_ADDR                      (ABB_BASE_ADDR + 0xE02)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:6] reserved
            [5:4] CH3_MODE_IBCT4��ch3 op4����ģʽѡ��
            00��3Gģʽ&amp;2Gģʽ&amp;Xģʽ
            01��LTEģʽ
            10��CAģʽ
            11��50Mģʽ
            [3:2] reserved
            [1:0] CH3_MODE_IBCT3��ch3 op3����ģʽѡ��
            00��3Gģʽ&amp;2Gģʽ&amp;Xģʽ
            01��LTEģʽ
            10��CAģʽ
            11��50Mģʽ
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR29_ADDR                      (ABB_BASE_ADDR + 0xE03)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7] CH3_CTRL_RFF��ch3 ǰ������rffѡ��
            0��LTEģʽ&amp;3Gģʽ&amp;2Gģʽ&amp;Xģʽ
            1��50Mģʽ&amp;CAģʽ
            [6:5] CH3_CTRL_RIN1��ch3 ������1�������rin1ѡ��
            00��50Mģʽ
            01��CAģʽ
            10��LTEģʽ
            11��3Gģʽ&amp;2Gģʽ&amp;Xģʽ
            [4] CH3_CTRL_RIN2��ch3 ������2�������rin2ѡ��
            0��LTEģʽ&amp;3Gģʽ&amp;2Gģʽ&amp;Xģʽ
            1��50Mģʽ&amp;CAģʽ
            [3] CH3_CTRL_RIN3��ch3 ������3�������rin3ѡ��
            0��LTEģʽ&amp;3Gģʽ&amp;2Gģʽ&amp;Xģʽ
            1��50Mģʽ&amp;CAģʽ
            [2] CH3_CTRL_RIN4��ch3 ������4�������rin4ѡ��
            0��LTEģʽ&amp;3Gģʽ&amp;2Gģʽ&amp;Xģʽ
            1��50Mģʽ&amp;CAģʽ
            [1:0] CH3_CTRL_RSIG��ch3 �������ź�ǰ������rsigѡ��
            00��OFF
            01��LTEģʽ&amp;3Gģʽ&amp;2Gģʽ&amp;Xģʽ
            10��50Mģʽ&amp;CAģʽ
            11��50Mģʽ&amp;CAģʽ
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR30_ADDR                      (ABB_BASE_ADDR + 0xE04)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:6] CH3_CTRL_RFB1��ch3 ��������������rfb1ѡ��
            00��50Mģʽ
            01��CAģʽ
            10��LTEģʽ
            11��3Gģʽ&amp;2Gģʽ&amp;Xģʽ
            [5:4] CH3_CTRL_RFB2��ch3 ��������������rfb2ѡ��
            00��LTEģʽ&amp;3Gģʽ&amp;2Gģʽ&amp;Xģʽ(notch2���40Mģʽ)
            01��LTEģʽ&amp;3Gģʽ&amp;2Gģʽ&amp;Xģʽ(notch2���50Mģʽ)
            10��50Mģʽ&amp;CAģʽ(notch2���40Mģʽ)
            11��50Mģʽ&amp;CAģʽ(notch2���50Mģʽ)
            [3:0] CH3_CTRL_RZ��ch3 ������3�������rzѡ��
            1111������ģʽĬ��Ϊ1111
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR31_ADDR                      (ABB_BASE_ADDR + 0xE05)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:4] reserved
            [3] CH3_DCTRL234��ch3 dac234����ģʽѡ��
            0��LTEģʽ&amp;3Gģʽ&amp;2Gģʽ&amp;Xģʽ
            1��50Mģʽ&amp;CAģʽ
            [2:0] CH3_DCTRL1��ch3 dac1����ģʽѡ��
            000��������
            001��3Gģʽ&amp;2Gģʽ&amp;Xģʽ
            010��LTEģʽ
            011��CAģʽ
            111��50Mģʽ
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR32_ADDR                      (ABB_BASE_ADDR + 0xE06)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:6] reserved
            [5:4] CH3_RX_CAP4_MODE��ch3 ������4����cap4ģʽѡ��
            00������
            01��50Mģʽ&amp;LTEģʽ������*1
            10��CAģʽ&amp;3Gģʽ&amp;2Gģʽ&amp;Xģʽ������*2
            11������
            [3:2] CH3_RX_CAP23_MODE��ch3 ������23����cap23ģʽѡ��
            00������
            01��50Mģʽ&amp;LTEģʽ������*1
            10��CAģʽ&amp;3Gģʽ&amp;2Gģʽ&amp;Xģʽ������*2
            11������
            [1:0] CH3_RX_CAP1_MODE��ch3 ������1����cap1ģʽѡ��
            00������
            01��50Mģʽ&amp;CAģʽ&amp;LTEģʽ&amp;3Gģʽ&amp;2Gģʽ&amp;Xģʽ
            10������
            11������
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR33_ADDR                      (ABB_BASE_ADDR + 0xE07)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7] reserved
            [6:4] CH3_IBCT_OP2��ch3 rx op2������С����
            000��5u
            001��4u
            010��3u
            011��2u
            100��9u
            101��8u
            110��7u
            111��6u
            [3] reserved
            [2:0] CH3_IBCT_OP1��ch3 rx op1������С����
            000��5u
            001��4u
            010��3u
            011��2u
            100��9u
            101��8u
            110��7u
            111��6u
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR34_ADDR                      (ABB_BASE_ADDR + 0xE08)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7] reserved
            [6:4] CH3_IBCT_OP4��ch3 rx op4������С����
            000��5u
            001��4u
            010��3u
            011��2u
            100��9u
            101��8u
            110��7u
            111��6u
            [3] reserved
            [2:0] CH3_IBCT_OP3��ch3 rx op3������С����
            000��5u
            001��4u
            010��3u
            011��2u
            100��9u
            101��8u
            110��7u
            111��6u
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR35_ADDR                      (ABB_BASE_ADDR + 0xE09)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7] reserved
            [6:4] CH3_IBCT_OPS��ch3 rx ����ģʽ�˷ŵ�����С����
            000��5u
            001��4u
            010��3u
            011��2u
            100��9u
            101��8u
            110��7u
            111��6u
            [3] reserved
            [2:0] CH3_IBCT_DAC��ch3 rx dac������С����
            000��5u
            001��4u
            010��3u
            011��2u
            100��9u
            101��8u
            110��7u
            111��6u
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR36_ADDR                      (ABB_BASE_ADDR + 0xE0A)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7] reserved
            [6:4] CH3_MULTI_RATE_CAP23��ch3 rx������23����cap23�˻�����ѡ��
            000��X1
            001��X1.5
            010��X1.25
            011��X1.125
            100��X1.0625
            101��X1.5625
            110��X1.3125
            111��X1.1875
            [3] reserved
            [2:0] CH3_MULTI_RATE_CAP1��ch3 rx������1����cap1�˻�����ѡ��
            000��X1
            001��X1.5
            010��X1.25
            011��X1.125
            100��X1.0625
            101��X1.5625
            110��X1.3125
            111��X1.1875
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR37_ADDR                      (ABB_BASE_ADDR + 0xE0B)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:3] reserved
            [2:0] CH3_MULTI_RATE_CAP4��ch3 rx������4����cap4�˻�����ѡ��
            000��X1
            001��X1.5
            010��X1.25
            011��X1.125
            100��X1.0625
            101��X1.5625
            110��X1.3125
            111��X1.1875
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR38_ADDR                      (ABB_BASE_ADDR + 0xE0C)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:6] reserved
            [5] CH3_CLKDIV2_A2D��ch3 rx a2d clock����Ƶѡ��
            0��ѡ��2��Ƶ
            1����ѡ��2��Ƶ
            [4] CH3_CLKDIV2_RX��ch3 rx clock����Ƶѡ��
            0��ѡ��2��Ƶ
            1����ѡ��2��Ƶ
            [3] reserved
            [2:0] CH3_CLKMUX_CTRL��ch3 rx ģʽ��Ƶʱ��ѡ��
            000��8��Ƶ
            001��4��Ƶ
            011��2��Ƶ
            111��1��Ƶ
            ��������
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR39_ADDR                      (ABB_BASE_ADDR + 0xE0D)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:4] reserved
            [3] CH3_DCLK_A2D_INV��ch3 dclk����ѡ��
            0��������
            1������
            [2] CH3_RXC_DCLK_INV��ch3 rxc sync2digģ��dclk����ѡ��
            0���������ش���
            1�����÷��ش���
            [1] CH3_RXB_DCLK_INV��ch3 rxb sync2digģ��dclk����ѡ��
            0���������ش���
            1�����÷��ش���
            [0] CH3_RXA_DCLK_INV��ch3 rxa sync2digģ��dclk����ѡ��
            0���������ش���
            1�����÷��ش���
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR40_ADDR                      (ABB_BASE_ADDR + 0xE0E)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:5] reserved
            [4:0] CH3_RXA_CLK_DAC3_CTRL��ch3 rxa dac3��ʱѡ��
                00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR41_ADDR                      (ABB_BASE_ADDR + 0xE0F)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:5] reserved
            [4:0] CH3_RXA_CLK_DAC3_CTRL��ch3 rxa qt��ʱѡ��
            00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR42_ADDR                      (ABB_BASE_ADDR + 0xE10)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:5] reserved
            [4:0] CH3_RXB_CLK_DAC3_CTRL��ch3 rxb dac3��ʱѡ��
            00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR43_ADDR                      (ABB_BASE_ADDR + 0xE11)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:5] reserved
            [4:0] CH3_RXB_CLK_DAC3_CTRL��ch3 rxb qt��ʱѡ��
            00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR44_ADDR                      (ABB_BASE_ADDR + 0xE12)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:5] reserved
            [4:0] CH3_RXC_CLK_DAC3_CTRL��ch3 rxc dac3��ʱѡ��
            00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR45_ADDR                      (ABB_BASE_ADDR + 0xE13)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:5] reserved
            [4:0] CH3_RXC_CLK_DAC3_CTRL��ch3 rxc qt��ʱѡ��
            00000��4ps
                00001��25ps
                00010��47ps
                00011��69ps
                00100��90ps
                00101��112ps
                00110��134ps
                00111��156ps
                01000��177ps
                01001��199ps
                01010��222ps
                ��
                11110��667ps
                11111��688ps
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR46_ADDR                      (ABB_BASE_ADDR + 0xE14)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7] CH3_CLKIN3_INV_RXB_Q��ch3 rxb q·clkin3 dff�����ؿ���
            0�����ؿ���
            1�����ؿ���
            [6] CH3_CLKIN3_INV_RXB_I��ch3 rxb i·clkin3 dff�����ؿ���
            0�����ؿ���
            1�����ؿ���
            [5] CH3_CLKIN2_INV_RXB_Q��ch3 rxb q·clkin2 dff�����ؿ���
            0�����ؿ���
            1�����ؿ���
            [4] CH3_CLKIN2_INV_RXB_I��ch3 rxb i·clkin2 dff�����ؿ���
            0�����ؿ���
            1�����ؿ���
            [3] CH3_CLKIN3_INV_RXA_Q��ch3 rxa q·clkin3 dff�����ؿ���
            0�����ؿ���
            1�����ؿ���
            [2] CH3_CLKIN3_INV_RXA_I��ch3 rxa i·clkin3 dff�����ؿ���
            0�����ؿ���
            1�����ؿ���
            [1] CH3_CLKIN2_INV_RXA_Q��ch3 rxa q·clkin2 dff�����ؿ���
            0�����ؿ���
            1�����ؿ���
            [0] CH3_CLKIN2_INV_RXA_I��ch3 rxa i·clkin2 dff�����ؿ���
            0�����ؿ���
            1�����ؿ���
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR47_ADDR                      (ABB_BASE_ADDR + 0xE15)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:4] reserved
            [3] CH3_CLKIN3_INV_RXA_Q��ch3 rxa q·clkin3 dff�����ؿ���
            0�����ؿ���
            1�����ؿ���
            [2] CH3_CLKIN3_INV_RXA_I��ch3 rxa i·clkin3 dff�����ؿ���
            0�����ؿ���
            1�����ؿ���
            [1] CH3_CLKIN2_INV_RXA_Q��ch3 rxa q·clkin2 dff�����ؿ���
            0�����ؿ���
            1�����ؿ���
            [0] CH3_CLKIN2_INV_RXA_I��ch3 rxa i·clkin2 dff�����ؿ���
            0�����ؿ���
            1�����ؿ���
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR48_ADDR                      (ABB_BASE_ADDR + 0xE16)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR49_ADDR                      (ABB_BASE_ADDR + 0xE17)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR50_ADDR                      (ABB_BASE_ADDR + 0xE18)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:1] reserved
            [0] CH3_RX_TUNE_SEL��ch3 rx tuning��ѡ��
                0��tuning��������rctuneģ��
                1��tuning�������ڼĴ�������
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR51_ADDR                      (ABB_BASE_ADDR + 0xE19)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] CH3_REG_TUNE1��ch3 rx cap1�ֶ����üĴ���
            0100 0000(Ĭ��)
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR52_ADDR                      (ABB_BASE_ADDR + 0xE1A)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] CH3_REG_TUNE23��ch3 rx cap23�ֶ����üĴ���
            0100 0000(Ĭ��)
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR53_ADDR                      (ABB_BASE_ADDR + 0xE1B)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] CH3_REG_TUNE4��ch3 rx cap4�ֶ����üĴ���
            0100 0000(Ĭ��)
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR54_ADDR                      (ABB_BASE_ADDR + 0xE1C)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7] reserved
            [6] CH3_PDM_CTRL��ch3 rx pdm�����ѡ��
                0:��ͱ���(Ĭ��)
                1:����������
            [5] CH3_DEM_OUTPUT_SEL��ch3 rx dem���ģʽѡ��
             0:��ͱ���(Ĭ��)
                1:����������
            [4] CH3_DEM_ENB��ch3 rx dem enableѡ��
                0:DEM Enable(Ĭ��)
                1:DEM Disable
            [3] reserved
            [2:0] CH3_DEM_MODE��ch3 rx demģʽѡ��
                000:DWAģʽ��Ĭ�ϣ�
                001:CLA1ģʽ
                010:CLA2ģʽ
                ��
                111:CLA7ģʽ
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR55_ADDR                      (ABB_BASE_ADDR + 0xE1D)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7] reserved
            [6:4] CH3_OL_CTRL��ch3 rx overload����ѡ��
                000��16����������������С�룬ͬʱ����int1��int2��int3��Ĭ�ϣ�
                001��8����������������С�룬ͬʱ����int1��int2��int3
                010��4����������������С�룬ͬʱ����int1��int2��int3
                011���ر�Overload��⣬ͬʱ����int1��int2��int3
                100��16����������������С�룬����˳��Ϊint3-->int2-->int1
                101��8����������������С�룬����˳��Ϊint3-->int2-->int1
                110��4����������������С�룬����˳��Ϊint3-->int2-->int1
                111���ر�Overload��⣬����˳��Ϊint3-->int2-->int1
            [3:2] reserved
            [1] CH3_PUP_CLK_CTRL��ch3 rx �����ϵ�ʱ��ѡ��
                0���ϵ���ɺ�ر��ϵ�ģ���ʱ�ӣ�Ĭ�ϣ�
                1���ϵ���ɺ󲻹ر��ϵ�ģ��ʱ��
            [0] CH3_PUP_MODE��ch3 rx �����ϵ�ģʽ
                0���Զ�ģʽ��Ĭ�ϣ�
                1�����üĴ����ϵ�ģʽ
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR56_ADDR                      (ABB_BASE_ADDR + 0xE1E)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] CH3_PUP_CTRL��ch3 rx �����ϵ����
            [7] CH3_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��RST_CAP����
                0��Reset CAP3
                1����Reset CAP3
            [6] CH3_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��RST_CAP����
                0��Reset CAP2
                1����Reset CAP2
            [5] CH3_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��RST_CAP����
                0��Reset CAP1
                1����Reset CAP1
            [4] CH3_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��OP����
                0��OP Power Down
                1��OP Power On
            [3] CH3_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��DAC����
                0��DAC Power Down
                1��DAC Power On
            [2] CH3_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��QTУ������
                0��QT Calibration On
                1��QT Calibration Off
            [1] CH3_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��CLKGEN����
                0��CLKGEN Power Down
                1��CLKGEN Power On
            [0] CH3_PUP_CTRL�����üĴ����ϵ�ģʽʱADC��QT����
                0��QT Power Down
                1��QT Power On
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR57_ADDR                      (ABB_BASE_ADDR + 0xE1F)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:6] reserved
            [5] CH3_QT_REF_SEL��ch0 rx qt��refѡ��
                0��vrefp/vrefn������refģ�飨Ĭ�ϣ�
                1��vrefp/vrefn�����ڱ��ط�ѹ
            [4] CH3_EN_QTCAL��ch0 rx qtУ׼enable
                0���Ƚ���У׼Disable��Ĭ�ϣ�
                1���Ƚ���У׼Enable��Ĭ�ϣ�
            [3] CH3_CAL_SW��ch0 rx op1У׼���ؿ���
                0��Ĭ��
                1������
            [2] CH3_CAL_TRIM_SW��ch0 rx op1У׼trim���ؿ���
                0��cal trim����disable��Ĭ�ϣ�
                1��cal trim����enable��Ĭ�ϣ�
            [1] CH3_OPCAL_VCM_SEL��ch0 rx op1У׼��ģѡ��
                0��op1У׼�̽�����˹�ģDisable��Ĭ�ϣ�
                1��op1У׼�̽�����˹�ģEnable��Ĭ�ϣ�
            [0] CH3_EN_OPCAL��ch0 rx op1У׼enable
                0��op1У׼Disable��Ĭ�ϣ�
                1��op1У׼Enable��Ĭ�ϣ�
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR58_ADDR                      (ABB_BASE_ADDR + 0xE20)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:6] reserved
            [5] CH3_RXC_PATH_CTRL_Q��ch3 rxb q·��·����ͨ·ѡ��rxc����������ģʽ
                0��ͨ·�Ͽ�����ѡ���ͨ·
                1��ͨ·��ͨ��ѡ���ͨ·
            [4] CH3_RXC_PATH_CTRL_I��ch3 rxb i·��·����ͨ·ѡ��rxc����������ģʽ
                0��ͨ·�Ͽ�����ѡ���ͨ·
                1��ͨ·��ͨ��ѡ���ͨ·
            [3] CH3_RXB_PATH_CTRL_Q��ch3 rxb q·��·����ͨ·ѡ��rxb����������ģʽ
                0��ͨ·�Ͽ�����ѡ���ͨ·
                1��ͨ·��ͨ��ѡ���ͨ·
            [2] CH3_RXB_PATH_CTRL_I��ch3 rxb i·��·����ͨ·ѡ��rxb����������ģʽ
                0��ͨ·�Ͽ�����ѡ���ͨ·
                1��ͨ·��ͨ��ѡ���ͨ·
            [1] CH3_RXA_PATH_CTRL_Q��ch3 rxa q·��·����ͨ·ѡ��rxa����������ģʽ
                0��ͨ·�Ͽ�����ѡ���ͨ·
                1��ͨ·��ͨ��ѡ���ͨ·
            [0] CH3_RXA_PATH_CTRL_I��ch3 rxa i·��·����ͨ·ѡ��rxa����������ģʽ
                0��ͨ·�Ͽ�����ѡ���ͨ·
                1��ͨ·��ͨ��ѡ���ͨ·
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR59_ADDR                      (ABB_BASE_ADDR + 0xE21)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7] CH3_RXA_SE_CTRLP_Q��ch3 rxa q·����ģʽp����˿���ѡ��
                0������ͨ�����˶˷���dac������ӹ̶���ƽ
                1����ͨ�����˶˷���dac����������˷�����
            [6] CH3_RXA_SE_CTRLN_Q��ch3 rxa q·����ģʽn����˿���ѡ��
                0������ͨ�����˶˷���dac������ӹ̶���ƽ
                1����ͨ�����˶˷���dac����������˷�����
            [5] CH3_RXA_SE_CTRLP_I��ch3 rxa i·����ģʽp����˿���ѡ��
                0������ͨ�����˶˷���dac������ӹ̶���ƽ
                1����ͨ�����˶˷���dac����������˷�����
            [4] CH3_RXA_SE_CTRLN_I��ch3 rxa i·����ģʽn����˿���ѡ��
                0������ͨ�����˶˷���dac������ӹ̶���ƽ
                1����ͨ�����˶˷���dac����������˷�����
            [3:2] CH3_RXA_MODE_IBCT_SE��ch3 rxa ����ģʽvcm buffer�˷�ģʽѡ��
                11��CAģʽ
                10��LTEģʽ
                01��WDCģʽ
                00��W3Gģʽ
            [1] CH3_RXA_PD_SE_Q��ch3 rxa i·����ģʽvcm buffer�˷�power down����
                0��power on
                1��power down
            [0] CH3_RXA_PD_SE_I��ch3 rxa q·����ģʽvcm buffer�˷�power down����
                0��power on
                1��power down
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR60_ADDR                      (ABB_BASE_ADDR + 0xE22)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR61_ADDR                      (ABB_BASE_ADDR + 0xE23)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR62_ADDR                      (ABB_BASE_ADDR + 0xE24)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR63_ADDR                      (ABB_BASE_ADDR + 0xE25)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR64_ADDR                      (ABB_BASE_ADDR + 0xE26)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR65_ADDR                      (ABB_BASE_ADDR + 0xE27)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR66_ADDR                      (ABB_BASE_ADDR + 0xE28)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR67_ADDR                      (ABB_BASE_ADDR + 0xE29)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR68_ADDR                      (ABB_BASE_ADDR + 0xE2A)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR69_ADDR                      (ABB_BASE_ADDR + 0xE2B)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR70_ADDR                      (ABB_BASE_ADDR + 0xE2C)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR71_ADDR                      (ABB_BASE_ADDR + 0xE2D)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR72_ADDR                      (ABB_BASE_ADDR + 0xE2E)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR73_ADDR                      (ABB_BASE_ADDR + 0xE2F)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR74_ADDR                      (ABB_BASE_ADDR + 0xE30)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR75_ADDR                      (ABB_BASE_ADDR + 0xE31)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR76_ADDR                      (ABB_BASE_ADDR + 0xE32)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR77_ADDR                      (ABB_BASE_ADDR + 0xE33)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR78_ADDR                      (ABB_BASE_ADDR + 0xE34)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR79_ADDR                      (ABB_BASE_ADDR + 0xE35)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR80_ADDR                      (ABB_BASE_ADDR + 0xE36)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR81_ADDR                      (ABB_BASE_ADDR + 0xE37)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR82_ADDR                      (ABB_BASE_ADDR + 0xE38)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR83_ADDR                      (ABB_BASE_ADDR + 0xE39)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR84_ADDR                      (ABB_BASE_ADDR + 0xE3A)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR85_ADDR                      (ABB_BASE_ADDR + 0xE3B)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR86_ADDR                      (ABB_BASE_ADDR + 0xE3C)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR87_ADDR                      (ABB_BASE_ADDR + 0xE3D)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR88_ADDR                      (ABB_BASE_ADDR + 0xE3E)

/* �Ĵ���˵����RX ����ͨ�����üĴ���
   ��      ����[7:0] reserved
   UNION�ṹ ���� */
#define ABB_REG_ANALOG_WR89_ADDR                      (ABB_BASE_ADDR + 0xE3F)





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
                     (1/1) register_define_abb
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : ABB_SCPLL0_LOCK_CTRL_UNION
 �ṹ˵��  : SCPLL0_LOCK_CTRL �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x18�����:8
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
 �ṹ˵��  : SCPLL0_FBDIV_H �Ĵ����ṹ���塣��ַƫ����:0x003����ֵ:0x00�����:8
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
 �ṹ˵��  : SCPLL0_REFDIV �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x01�����:8
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
 �ṹ˵��  : SCPLL0_CFG_UPDATE �Ĵ����ṹ���塣��ַƫ����:0x009����ֵ:0x00�����:8
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
 �ṹ˵��  : SCPLL1_LOCK_CTRL �Ĵ����ṹ���塣��ַƫ����:0x00A����ֵ:0x18�����:8
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
 �ṹ˵��  : SCPLL1_FBDIV_H �Ĵ����ṹ���塣��ַƫ����:0x00D����ֵ:0x00�����:8
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
 �ṹ˵��  : SCPLL1_REFDIV �Ĵ����ṹ���塣��ַƫ����:0x00E����ֵ:0x01�����:8
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
 �ṹ˵��  : SCPLL1_CFG_UPDATE �Ĵ����ṹ���塣��ַƫ����:0x013����ֵ:0x00�����:8
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
 �ṹ��    : ABB_GPLL_GATE_TIME_UNION
 �ṹ˵��  : GPLL_GATE_TIME �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x12�����:8
 �Ĵ���˵��: GPLL���ʱ���ſ�ʱ������
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  gpll_en      : 1;  /* bit[0]  :  */
        unsigned long  gpll_time    : 3;  /* bit[1-3]: GPLLʱ���ȶ��ȴ�ʱ�����ã�����ʱ��Ϊ19.2M��
                                                       000��GPLL����10us��ʱ���ȶ���
                                                       001��GPLL����20us��ʱ���ȶ���
                                                       010��GPLL����50us��ʱ���ȶ���
                                                       011��GPLL����75us��ʱ���ȶ���
                                                       100��GPLL����100us��ʱ���ȶ���
                                                       101��GPLL����115us��ʱ���ȶ���
                                                       110��GPLL1����125us��ʱ���ȶ���
                                                       default��100us */
        unsigned long  gpll_gate_en : 1;  /* bit[4]  : GPLLʱ���ſع���ʹ�ܣ�
                                                       0��gpllʱ���ſع��ܹرգ�
                                                       1��gpllʱ���ſع��ܴ򿪡� */
        unsigned long  gpll_timeout : 1;  /* bit[5]  : GPLL�ȶ�ָʾ��0��ʾGPLLδ�ȶ���1��ʾGPLL�ȶ���GPLL�ȶ�����ʱ������� */
        unsigned long  reserved     : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_GPLL_GATE_TIME_UNION;
#define ABB_GPLL_GATE_TIME_gpll_en_START       (0)
#define ABB_GPLL_GATE_TIME_gpll_en_END         (0)
#define ABB_GPLL_GATE_TIME_gpll_time_START     (1)
#define ABB_GPLL_GATE_TIME_gpll_time_END       (3)
#define ABB_GPLL_GATE_TIME_gpll_gate_en_START  (4)
#define ABB_GPLL_GATE_TIME_gpll_gate_en_END    (4)
#define ABB_GPLL_GATE_TIME_gpll_timeout_START  (5)
#define ABB_GPLL_GATE_TIME_gpll_timeout_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_WPLL_GATE_TIME_UNION
 �ṹ˵��  : WPLL_GATE_TIME �Ĵ����ṹ���塣��ַƫ����:0x015����ֵ:0x12�����:8
 �Ĵ���˵��: WPLL���ʱ���ſ�ʱ������
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  wpll_en      : 1;  /* bit[0]  :  */
        unsigned long  wpll_time    : 3;  /* bit[1-3]: WPLLʱ���ȶ��ȴ�ʱ�����ã�����ʱ��Ϊ19.2M��
                                                       000��WPLL����10us��ʱ���ȶ���
                                                       001��WPLL����20us��ʱ���ȶ���
                                                       010��WPLL����50us��ʱ���ȶ���
                                                       011��WPLL����75us��ʱ���ȶ���
                                                       100��WPLL����100us��ʱ���ȶ���
                                                       101��WPLL����115us��ʱ���ȶ���
                                                       110��WPLL1����125us��ʱ���ȶ���
                                                       default��100us */
        unsigned long  wpll_gate_en : 1;  /* bit[4]  : WPLLʱ���ſع���ʹ�ܣ�
                                                       0��wpllʱ���ſع��ܹرգ�
                                                       1��wpllʱ���ſع��ܴ򿪡� */
        unsigned long  wpll_timeout : 1;  /* bit[5]  : WPLL�ȶ�ָʾ��0��ʾWPLLδ�ȶ���1��ʾWPLL�ȶ���WPLL�ȶ�����ʱ������� */
        unsigned long  reserved     : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_WPLL_GATE_TIME_UNION;
#define ABB_WPLL_GATE_TIME_wpll_en_START       (0)
#define ABB_WPLL_GATE_TIME_wpll_en_END         (0)
#define ABB_WPLL_GATE_TIME_wpll_time_START     (1)
#define ABB_WPLL_GATE_TIME_wpll_time_END       (3)
#define ABB_WPLL_GATE_TIME_wpll_gate_en_START  (4)
#define ABB_WPLL_GATE_TIME_wpll_gate_en_END    (4)
#define ABB_WPLL_GATE_TIME_wpll_timeout_START  (5)
#define ABB_WPLL_GATE_TIME_wpll_timeout_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_TESTMODE_UNION
 �ṹ˵��  : TESTMODE �Ĵ����ṹ���塣��ַƫ����:0x016����ֵ:0x00�����:8
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
 �ṹ��    : ABB_ABB_DIG_PWR_RST_UNION
 �ṹ˵��  : ABB_DIG_PWR_RST �Ĵ����ṹ���塣��ַƫ����:0x017����ֵ:0x00�����:8
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
 �ṹ˵��  : CH0_COMM_REG_DEBUG_DIG �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00�����:8
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
 �ṹ˵��  : CH1_COMM_REG_DEBUG_DIG �Ĵ����ṹ���塣��ַƫ����:0x019����ֵ:0x00�����:8
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
 �ṹ˵��  : BIST_CFG_1 �Ĵ����ṹ���塣��ַƫ����:0x041����ֵ:0x00�����:8
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
 �ṹ˵��  : BIST_CFG_4 �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x00�����:8
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
 �ṹ˵��  : BIST_CFG_5 �Ĵ����ṹ���塣��ַƫ����:0x045����ֵ:0x00�����:8
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
 �ṹ˵��  : BIST_RPT_1 �Ĵ����ṹ���塣��ַƫ����:0x046����ֵ:0x00�����:8
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
 �ṹ˵��  : BIST_RPT_2 �Ĵ����ṹ���塣��ַƫ����:0x047����ֵ:0x00�����:8
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
 �ṹ˵��  : BIST_RPT_8 �Ĵ����ṹ���塣��ַƫ����:0x04D����ֵ:0x00�����:8
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
 �ṹ˵��  : BIST_RPT_10 �Ĵ����ṹ���塣��ַƫ����:0x04F����ֵ:0x00�����:8
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
 �ṹ˵��  : BIST_CFG_6 �Ĵ����ṹ���塣��ַƫ����:0x05A����ֵ:0x3E�����:8
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
 �ṹ˵��  : BIST_CFG_8 �Ĵ����ṹ���塣��ַƫ����:0x05C����ֵ:0x01�����:8
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
 �ṹ��    : ABB_ADPLL_LOCK_CTRL_UNION
 �ṹ˵��  : ADPLL_LOCK_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0A1����ֵ:0x18�����:8
 �Ĵ���˵��: SC_PLL�������ƼĴ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  adpll_en      : 1;  /* bit[0]  : ADPLLʹ���źš�����ͨ��CFG�ӿ����ô�adpll�� */
        unsigned long  adpll_time    : 3;  /* bit[1-3]: ADPLLʱ���ȶ��ȴ�ʱ�����ã�����ʱ��Ϊ19.2M��
                                                        000��ADPLL����10us��ʱ���ȶ���
                                                        001��ADPLL����20us��ʱ���ȶ���
                                                        010��ADPLL����50us��ʱ���ȶ���
                                                        011��ADPLL����75us��ʱ���ȶ���
                                                        100��ADPLL����100us��ʱ���ȶ���
                                                        101��ADPLL����115us��ʱ���ȶ���
                                                        110��ADPLL1����125us��ʱ���ȶ���
                                                        default��100us */
        unsigned long  adpll_gate_en : 1;  /* bit[4]  : ADPLL�ſ�ʹ���źš� */
        unsigned long  adpll_timeout : 1;  /* bit[5]  : ADPLL�ȶ�ָʾ��0��ʾADPLLδ�ȶ���1��ʾADPLL�ȶ���ADPLL�ȶ�����ʱ������� */
        unsigned long  adpll_lock    : 1;  /* bit[6]  : ADPLL����ָʾ�� */
        unsigned long  reserved      : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_ADPLL_LOCK_CTRL_UNION;
#define ABB_ADPLL_LOCK_CTRL_adpll_en_START       (0)
#define ABB_ADPLL_LOCK_CTRL_adpll_en_END         (0)
#define ABB_ADPLL_LOCK_CTRL_adpll_time_START     (1)
#define ABB_ADPLL_LOCK_CTRL_adpll_time_END       (3)
#define ABB_ADPLL_LOCK_CTRL_adpll_gate_en_START  (4)
#define ABB_ADPLL_LOCK_CTRL_adpll_gate_en_END    (4)
#define ABB_ADPLL_LOCK_CTRL_adpll_timeout_START  (5)
#define ABB_ADPLL_LOCK_CTRL_adpll_timeout_END    (5)
#define ABB_ADPLL_LOCK_CTRL_adpll_lock_START     (6)
#define ABB_ADPLL_LOCK_CTRL_adpll_lock_END       (6)


/*****************************************************************************
 �ṹ��    : ABB_ADPLL_FBDIV_H_UNION
 �ṹ˵��  : ADPLL_FBDIV_H �Ĵ����ṹ���塣��ַƫ����:0x0A4����ֵ:0x00�����:8
 �Ĵ���˵��: SC_PLL��Ƶ���������üĴ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  adpll_fbdiv_h : 4;  /* bit[0-3]: PLL������Ƶ����fbdiv[11:0]�ĸ�4bit�� */
        unsigned long  reserved      : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_ADPLL_FBDIV_H_UNION;
#define ABB_ADPLL_FBDIV_H_adpll_fbdiv_h_START  (0)
#define ABB_ADPLL_FBDIV_H_adpll_fbdiv_h_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_ADPLL_REFDIV_UNION
 �ṹ˵��  : ADPLL_REFDIV �Ĵ����ṹ���塣��ַƫ����:0x0A5����ֵ:0x01�����:8
 �Ĵ���˵��: SC_PLL��Ƶ���������üĴ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  adpll_refdiv : 6;  /* bit[0-5]: PLL�ο���Ƶ����refdiv[5:0]��Ĭ��ֵΪ1�� */
        unsigned long  reserved     : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_ADPLL_REFDIV_UNION;
#define ABB_ADPLL_REFDIV_adpll_refdiv_START  (0)
#define ABB_ADPLL_REFDIV_adpll_refdiv_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_ADPLL_CFG_UPDATE_UNION
 �ṹ˵��  : ADPLL_CFG_UPDATE �Ĵ����ṹ���塣��ַƫ����:0x0AA����ֵ:0x00�����:8
 �Ĵ���˵��: SC_PLL�������ƼĴ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  adpll_cfg_update : 1;  /* bit[0]  : ADPLL�������ø���ָʾ��
                                                           adpll_en�򿪺����������adpll_postdiv��adpll_fbdiv��adpll_frac������������adpll_sfg_update������ͬʱ���£�adpll_en����ʱ�����ò����������£�����Ҫ����adpll_sfg_update�� */
        unsigned long  reserved         : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_ADPLL_CFG_UPDATE_UNION;
#define ABB_ADPLL_CFG_UPDATE_adpll_cfg_update_START  (0)
#define ABB_ADPLL_CFG_UPDATE_adpll_cfg_update_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_ADPLL_TEST_CFG_UNION
 �ṹ˵��  : ADPLL_TEST_CFG �Ĵ����ṹ���塣��ַƫ����:0x0B6����ֵ:0x00�����:8
 �Ĵ���˵��:
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  adpll_dcodiv2    : 1;  /* bit[0]  :  */
        unsigned long  adpll_fast_start : 1;  /* bit[1]  :  */
        unsigned long  reserved         : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_ADPLL_TEST_CFG_UNION;
#define ABB_ADPLL_TEST_CFG_adpll_dcodiv2_START     (0)
#define ABB_ADPLL_TEST_CFG_adpll_dcodiv2_END       (0)
#define ABB_ADPLL_TEST_CFG_adpll_fast_start_START  (1)
#define ABB_ADPLL_TEST_CFG_adpll_fast_start_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_ADPLL_CLKSSCG_CFG_UNION
 �ṹ˵��  : ADPLL_CLKSSCG_CFG �Ĵ����ṹ���塣��ַƫ����:0x0B7����ֵ:0x00�����:8
 �Ĵ���˵��:
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  adpll_clksscg_en : 1;  /* bit[0]  :  */
        unsigned long  reserved         : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_ADPLL_CLKSSCG_CFG_UNION;
#define ABB_ADPLL_CLKSSCG_CFG_adpll_clksscg_en_START  (0)
#define ABB_ADPLL_CLKSSCG_CFG_adpll_clksscg_en_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_TX_ET_DIG_1_UNION
 �ṹ˵��  : TX_ET_DIG_1 �Ĵ����ṹ���塣��ַƫ����:0x100����ֵ:0x40�����:8
 �Ĵ���˵��: TX ET�������üĴ���1��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_comp_bp : 1;  /* bit[0]  : ETͨ�������˲���bypass���ƣ�
                                                     0����bypass(Ĭ��)
                                                     1��bypass */
        unsigned long  et_hb_bp   : 1;  /* bit[1]  : ETͨ������˲�����bypass�ź�
                                                     0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                     1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  et_sw_rst  : 1;  /* bit[2]  : ETͨ����λ�Ĵ�����
                                                     0������λ��
                                                     1����λ�� */
        unsigned long  reserved_0 : 3;  /* bit[3-5]: ���� */
        unsigned long  et_ds_bp   : 1;  /* bit[6]  : ETͨ��������bypass�ź�
                                                     0����bypass��2����������Ĭ�ϣ���
                                                     1��bypass�������н������� */
        unsigned long  reserved_1 : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_DIG_1_UNION;
#define ABB_TX_ET_DIG_1_et_comp_bp_START  (0)
#define ABB_TX_ET_DIG_1_et_comp_bp_END    (0)
#define ABB_TX_ET_DIG_1_et_hb_bp_START    (1)
#define ABB_TX_ET_DIG_1_et_hb_bp_END      (1)
#define ABB_TX_ET_DIG_1_et_sw_rst_START   (2)
#define ABB_TX_ET_DIG_1_et_sw_rst_END     (2)
#define ABB_TX_ET_DIG_1_et_ds_bp_START    (6)
#define ABB_TX_ET_DIG_1_et_ds_bp_END      (6)


/*****************************************************************************
 �ṹ��    : ABB_TX_ET_DIG_2_UNION
 �ṹ˵��  : TX_ET_DIG_2 �Ĵ����ṹ���塣��ַƫ����:0x101����ֵ:0x05�����:8
 �Ĵ���˵��: TX ET�������üĴ���2��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_gating_en : 1;  /* bit[0]  : ETͨ��CLOCK GATING���ƣ�
                                                       0����CLOCK GATING
                                                       1��CLOCK GATING(Ĭ��)
                                                       (!et_gating_en)|XX_TX_EN = 1ʱ����������ر� */
        unsigned long  et_con       : 2;  /* bit[1-2]: TXͨ��DEM constϵ����
                                                       0��0
                                                       1��2
                                                       2��4(Ĭ��)
                                                       3��6 */
        unsigned long  et_lsb_value : 1;  /* bit[3]  : ET LSB���bit���ֵ���� */
        unsigned long  reserved_0   : 1;  /* bit[4]  : ���� */
        unsigned long  et_tx_dwa_en : 1;  /* bit[5]  : ET TXͨ��DEMģʽ���ƣ�
                                                       0��ʹ��CLAģʽ(Ĭ��)
                                                       1��ʹ��DWAģʽ  */
        unsigned long  reserved_1   : 1;  /* bit[6]  : ���� */
        unsigned long  et_tx_dem_bp : 1;  /* bit[7]  : ET TXͨ��dem bypass��
                                                       0��DEM��(Ĭ��)
                                                       1��DEM bypass */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_DIG_2_UNION;
#define ABB_TX_ET_DIG_2_et_gating_en_START  (0)
#define ABB_TX_ET_DIG_2_et_gating_en_END    (0)
#define ABB_TX_ET_DIG_2_et_con_START        (1)
#define ABB_TX_ET_DIG_2_et_con_END          (2)
#define ABB_TX_ET_DIG_2_et_lsb_value_START  (3)
#define ABB_TX_ET_DIG_2_et_lsb_value_END    (3)
#define ABB_TX_ET_DIG_2_et_tx_dwa_en_START  (5)
#define ABB_TX_ET_DIG_2_et_tx_dwa_en_END    (5)
#define ABB_TX_ET_DIG_2_et_tx_dem_bp_START  (7)
#define ABB_TX_ET_DIG_2_et_tx_dem_bp_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_TX_ET_DIG_4_UNION
 �ṹ˵��  : TX_ET_DIG_4 �Ĵ����ṹ���塣��ַƫ����:0x103����ֵ:0x00�����:8
 �Ĵ���˵��: TX ET�������üĴ���4��
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_tx_en_cfg : 1;  /* bit[0]: ET�߿�ǿ������ֵ�� */
        unsigned long  et_tx_en_sel : 1;  /* bit[1]: ET�߿�ǿ������ʹ�ܡ�
                                                     0����ʹ�ܣ�
                                                     1��ʹ�ܡ� */
        unsigned long  et_apt_cfg   : 1;  /* bit[2]: ETģʽǿ������ֵ�� */
        unsigned long  et_apt_sel   : 1;  /* bit[3]: ETģʽǿ������ʹ�ܡ�
                                                     0����ʹ�ܣ�
                                                     1��ʹ�ܡ� */
        unsigned long  et_div_bp    : 1;  /* bit[4]: ET��Ƶ��ʹ��bypass����
                                                     0����bypass
                                                     1��bypass */
        unsigned long  et_dig_loop  : 1;  /* bit[5]: ETͨ���ӿڻ���ģʽʹ�ܡ���ģʽʹ�ܣ���ET TX����ͨ��CH1 RXͨ�����ء�
                                                     0����ʹ�ܣ�
                                                     1��ʹ�ܡ� */
        unsigned long  et_alg_loop  : 1;  /* bit[6]: ETͨ���㷨����ģʽʹ�ܡ���ģʽʹ�ܣ���ET TX����ͨ��CH1 RXͨ�����ء�
                                                     0����ʹ�ܣ�
                                                     1��ʹ�ܡ� */
        unsigned long  et_ch_sel    : 1;  /* bit[7]:  */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_TX_ET_DIG_4_UNION;
#define ABB_TX_ET_DIG_4_et_tx_en_cfg_START  (0)
#define ABB_TX_ET_DIG_4_et_tx_en_cfg_END    (0)
#define ABB_TX_ET_DIG_4_et_tx_en_sel_START  (1)
#define ABB_TX_ET_DIG_4_et_tx_en_sel_END    (1)
#define ABB_TX_ET_DIG_4_et_apt_cfg_START    (2)
#define ABB_TX_ET_DIG_4_et_apt_cfg_END      (2)
#define ABB_TX_ET_DIG_4_et_apt_sel_START    (3)
#define ABB_TX_ET_DIG_4_et_apt_sel_END      (3)
#define ABB_TX_ET_DIG_4_et_div_bp_START     (4)
#define ABB_TX_ET_DIG_4_et_div_bp_END       (4)
#define ABB_TX_ET_DIG_4_et_dig_loop_START   (5)
#define ABB_TX_ET_DIG_4_et_dig_loop_END     (5)
#define ABB_TX_ET_DIG_4_et_alg_loop_START   (6)
#define ABB_TX_ET_DIG_4_et_alg_loop_END     (6)
#define ABB_TX_ET_DIG_4_et_ch_sel_START     (7)
#define ABB_TX_ET_DIG_4_et_ch_sel_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_ET_STATE_RPT_UNION
 �ṹ˵��  : ET_STATE_RPT �Ĵ����ṹ���塣��ַƫ����:0x105����ֵ:0x00�����:8
 �Ĵ���˵��: ETͨ��״̬�ϱ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_comp_overflow : 1;  /* bit[0]  : ET�����˲������ָʾ�� */
        unsigned long  et_cic6_overflow : 1;  /* bit[1]  : ET CIC6�˲������ָʾ�� */
        unsigned long  et_hb_overflow   : 1;  /* bit[2]  : ET HB�˲������ָʾ�� */
        unsigned long  reserved         : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_ET_STATE_RPT_UNION;
#define ABB_ET_STATE_RPT_et_comp_overflow_START  (0)
#define ABB_ET_STATE_RPT_et_comp_overflow_END    (0)
#define ABB_ET_STATE_RPT_et_cic6_overflow_START  (1)
#define ABB_ET_STATE_RPT_et_cic6_overflow_END    (1)
#define ABB_ET_STATE_RPT_et_hb_overflow_START    (2)
#define ABB_ET_STATE_RPT_et_hb_overflow_END      (2)


/*****************************************************************************
 �ṹ��    : ABB_ET_SINE_GENERATE_UNION
 �ṹ˵��  : ET_SINE_GENERATE �Ĵ����ṹ���塣��ַƫ����:0x106����ֵ:0x10�����:8
 �Ĵ���˵��: SINE���ͼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  et_sine_enable : 1;  /* bit[0]  : etͨ�����Ҳ�����ʹ�ܡ���λʹ�ܣ���ETͨ���������Ҳ��źţ���ͨ��sine_sw_reqѡ��CH0����CH1�������Ҳ��źš�
                                                         0��������
                                                         1������ */
        unsigned long  reserved       : 1;  /* bit[1]  : ���� */
        unsigned long  et_sine_amp    : 2;  /* bit[2-3]: ���Ҳ����ͷ��ȿ���
                                                         00��������
                                                         01��3/4����
                                                         10��1/2����
                                                         11��1/4���� */
        unsigned long  et_sine_freq   : 4;  /* bit[4-7]: ���Ҳ�����Ƶ�ʿ��ƣ���λ(freq of tx_hb_clk)/32�����䷶ΧΪ1~f */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_ET_SINE_GENERATE_UNION;
#define ABB_ET_SINE_GENERATE_et_sine_enable_START  (0)
#define ABB_ET_SINE_GENERATE_et_sine_enable_END    (0)
#define ABB_ET_SINE_GENERATE_et_sine_amp_START     (2)
#define ABB_ET_SINE_GENERATE_et_sine_amp_END       (3)
#define ABB_ET_SINE_GENERATE_et_sine_freq_START    (4)
#define ABB_ET_SINE_GENERATE_et_sine_freq_END      (7)


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
 �ṹ˵��  : tx_idle_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x201����ֵ:0x23�����:8
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
 �ṹ˵��  : tx_idle_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x202����ֵ:0x01�����:8
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
 �ṹ˵��  : tx_2g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x204����ֵ:0x23�����:8
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
 �ṹ˵��  : tx_2g_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x205����ֵ:0x01�����:8
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
 �ṹ˵��  : tx_c_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x207����ֵ:0x23�����:8
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
 �ṹ˵��  : tx_c_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x208����ֵ:0x09�����:8
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
 �ṹ˵��  : tx_tds_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x20A����ֵ:0x23�����:8
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
 �ṹ˵��  : tx_tds_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x20B����ֵ:0x01�����:8
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
 �ṹ��    : ABB_TX_3G_DIG_1_UNION
 �ṹ˵��  : tx_3g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x20C����ֵ:0x20�����:8
 �Ĵ���˵��: TX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_comp_bp_3g  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                         0����bypass(Ĭ��)
                                                         1��bypass */
        unsigned long  tx_hb_bp_3g    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                         0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                         1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  tx_rate_3g     : 3;  /* bit[2-4]: TXͨ��CIC�˲����������ʿ��ƣ�
                                                              2G,     3G,     4G,      TDS,      CDMA,    CA
                                                             (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
                                                         0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(Ĭ��)
                                                         1��2.16MHz,15.36MHz,30.72MHz, */
        unsigned long  tx_mode_dig_3g : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                         000��2G(Ĭ��)
                                                         001��3G
                                                         010��4G
                                                         011��TDS
                                                         100��CDMA
                                                         101��CA
                                                         Others��Reserved */
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
 �ṹ˵��  : tx_3g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x20D����ֵ:0x23�����:8
 �Ĵ���˵��: TX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
        unsigned long  dem_const_3g     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����
                                                           0��0(Ĭ��)
                                                           1��2
                                                           2��4
                                                           3��6 */
        unsigned long  uddwa_dith_en_3g : 1;  /* bit[4]  : TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                           0����ʹ��
                                                           1��ʹ�� */
        unsigned long  dem_dwa_en_3g    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                           0��ʹ��CLAģʽ
                                                           1��ʹ��DWAģʽ(Ĭ��)  */
        unsigned long  dem_lsb_bp_3g    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                           0��DEM LSB ��(Ĭ��)
                                                           1��DEM LSB bypass */
        unsigned long  dem_msb_bp_3g    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                           0��DEM MSB��(Ĭ��)
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
 �ṹ˵��  : tx_3g_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x20E����ֵ:0x01�����:8
 �Ĵ���˵��: TX 3Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0     : 1;  /* bit[0]  : ���� */
        unsigned long  tx_flush_en_3g : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                         0����ʹ��
                                                         1��ʹ�� */
        unsigned long  tx_comp_sel_3g : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                         00���̶�ϵ��1��
                                                         01���̶�ϵ��2��
                                                         10���̶�ϵ��3��
                                                         11������ϵ���� */
        unsigned long  reserved_1     : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_3G_DIG_3_UNION;
#define ABB_TX_3G_DIG_3_tx_flush_en_3g_START  (1)
#define ABB_TX_3G_DIG_3_tx_flush_en_3g_END    (1)
#define ABB_TX_3G_DIG_3_tx_comp_sel_3g_START  (2)
#define ABB_TX_3G_DIG_3_tx_comp_sel_3g_END    (3)


/*****************************************************************************
 �ṹ��    : ABB_TX_4G_DIG_1_UNION
 �ṹ˵��  : tx_4g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x20F����ֵ:0x40�����:8
 �Ĵ���˵��: TX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  tx_comp_bp_4g  : 1;  /* bit[0]  : TXͨ�������˲���bypass���ƣ�
                                                         0����bypass(Ĭ��)
                                                         1��bypass */
        unsigned long  tx_hb_bp_4g    : 1;  /* bit[1]  : TXͨ������˲���bypass���ƣ�
                                                         0����bypass����˲���,TXͨ�����data rate ΪTX CIC rate/2(Ĭ��)
                                                         1��bypass����˲���,TXͨ�����data rate ΪTX CIC rate */
        unsigned long  tx_rate_4g     : 3;  /* bit[2-4]: TXͨ��CIC�˲����������ʿ��ƣ�
                                                              2G,     3G,     4G,      TDS,      CDMA,    CA
                                                             (78M) (153.6M) (307.2M) (153.6M) (122.88M)  (614.4M)
                                                         0��4.33MHz,30.72MHz,61.44MHz,30.72MHz,4.9152MHz,122.88M(Ĭ��)
                                                         1��2.16MHz,15.36MHz,30.72MHz, */
        unsigned long  tx_mode_dig_4g : 3;  /* bit[5-7]: TXͨ��ģʽ���ƣ�
                                                         000��2G(Ĭ��)
                                                         001��3G
                                                         010��4G
                                                         011��TDS
                                                         100��CDMA
                                                         101��CA
                                                         Others��Reserved */
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
 �ṹ˵��  : tx_4g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x210����ֵ:0x23�����:8
 �Ĵ���˵��: TX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
        unsigned long  dem_const_4g     : 2;  /* bit[2-3]: TXͨ��DEM constϵ����
                                                           0��0(Ĭ��)
                                                           1��2
                                                           2��4
                                                           3��6 */
        unsigned long  uddwa_dith_en_4g : 1;  /* bit[4]  : TXͨ��DEM UDDWA_DITHģ��ʹ�ܿ��ƣ�
                                                           0����ʹ��
                                                           1��ʹ�� */
        unsigned long  dem_dwa_en_4g    : 1;  /* bit[5]  : TXͨ��DEMģʽ���ƣ�
                                                           0��ʹ��CLAģʽ
                                                           1��ʹ��DWAģʽ(Ĭ��)  */
        unsigned long  dem_lsb_bp_4g    : 1;  /* bit[6]  : TXͨ��DEM LSB bypass��
                                                           0��DEM LSB ��(Ĭ��)
                                                           1��DEM LSB bypass */
        unsigned long  dem_msb_bp_4g    : 1;  /* bit[7]  : TXͨ��DEM MSB bypass��
                                                           0��DEM MSB��(Ĭ��)
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
 �ṹ˵��  : tx_4g_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x211����ֵ:0x01�����:8
 �Ĵ���˵��: TX 4Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  reserved_0     : 1;  /* bit[0]  : ���� */
        unsigned long  tx_flush_en_4g : 1;  /* bit[1]  : TXͨ��FLUSHʹ�ܣ�
                                                         0����ʹ��
                                                         1��ʹ�� */
        unsigned long  tx_comp_sel_4g : 2;  /* bit[2-3]: TXͨ�������˲��������̶�ϵ��ѡ��
                                                         00���̶�ϵ��1��
                                                         01���̶�ϵ��2��
                                                         10���̶�ϵ��3��
                                                         11������ϵ���� */
        unsigned long  reserved_1     : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_TX_4G_DIG_3_UNION;
#define ABB_TX_4G_DIG_3_tx_flush_en_4g_START  (1)
#define ABB_TX_4G_DIG_3_tx_flush_en_4g_END    (1)
#define ABB_TX_4G_DIG_3_tx_comp_sel_4g_START  (2)
#define ABB_TX_4G_DIG_3_tx_comp_sel_4g_END    (3)


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
        unsigned long  ch0_tx_sw_rst : 1;  /* bit[0]  : ���ֲ���TXͨ����λ�źţ�
                                                        0������λ(Ĭ��)
                                                        1����λ */
        unsigned long  reserved      : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_TX_TESTMODE_UNION;
#define ABB_CH0_TX_TESTMODE_ch0_tx_sw_rst_START  (0)
#define ABB_CH0_TX_TESTMODE_ch0_tx_sw_rst_END    (0)


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
 �ṹ��    : ABB_CH1_TX_TESTMODE_UNION
 �ṹ˵��  : CH1_TX_TESTMODE �Ĵ����ṹ���塣��ַƫ����:0x260����ֵ:0x00�����:8
 �Ĵ���˵��: ����ģʽ�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_tx_sw_rst : 1;  /* bit[0]  : ���ֲ���TXͨ����λ�źţ�
                                                        0������λ(Ĭ��)
                                                        1����λ */
        unsigned long  reserved      : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_TX_TESTMODE_UNION;
#define ABB_CH1_TX_TESTMODE_ch1_tx_sw_rst_START  (0)
#define ABB_CH1_TX_TESTMODE_ch1_tx_sw_rst_END    (0)


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
 �ṹ˵��  : CH1_TX_REG_DEBUG_DIG0 �Ĵ����ṹ���塣��ַƫ����:0x26C����ֵ:0x64�����:8
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
        unsigned long  ch1_tuning_val_en : 1;  /* bit[5]  : Tuning code��Դѡ��
                                                            0���Ĵ�������
                                                            1���Զ����£�Ĭ�ϣ� */
        unsigned long  ch1_tx_main_sd_bp : 1;  /* bit[6]  : TX SDģ������������·ʹ�ܣ�
                                                            0��������������·��
                                                            1������������·��Ĭ�ϣ��� */
        unsigned long  reserved          : 1;  /* bit[7]  : ���� */
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
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_tuning_val_en_START  (5)
#define ABB_CH1_TX_REG_DEBUG_DIG0_ch1_tuning_val_en_END    (5)
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
 �ṹ��    : ABB_RX_IDLE_DIG_1_UNION
 �ṹ˵��  : rx_idle_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x400����ֵ:0x00�����:8
 �Ĵ���˵��: RX IDLEģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_comp_sel_b0_idle : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
                                                              00���̶�ϵ��1��
                                                              01���̶�ϵ��2��
                                                              10���̶�ϵ��3��
                                                              11���̶�ϵ��4�� */
        unsigned long  rx_comp_fix_idle    : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                              0��ϵ�����̶����ɼĴ�������
                                                              1��ϵ���̶� */
        unsigned long  rx_hb_bp_idle       : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                              0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                              1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  rx_rate_idle        : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                                  2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                                                                        /TDS_B/4G_C,        /4G_B,
                                                              00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��),122.88M,2.167M,
                                                              others��reserved */
        unsigned long  rx_mode_dig_idle    : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                              000��2G_A(Ĭ��)
                                                              001��3G_SC/TDS_B/4G_C
                                                              010��4G
                                                              011��3G_DC/4G_B
                                                              100��TDS
                                                              101��CDMA
                                                              110��CA
                                                              111��2G_B */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_DIG_1_UNION;
#define ABB_RX_IDLE_DIG_1_rx_comp_sel_b0_idle_START  (0)
#define ABB_RX_IDLE_DIG_1_rx_comp_sel_b0_idle_END    (0)
#define ABB_RX_IDLE_DIG_1_rx_comp_fix_idle_START     (1)
#define ABB_RX_IDLE_DIG_1_rx_comp_fix_idle_END       (1)
#define ABB_RX_IDLE_DIG_1_rx_hb_bp_idle_START        (2)
#define ABB_RX_IDLE_DIG_1_rx_hb_bp_idle_END          (2)
#define ABB_RX_IDLE_DIG_1_rx_rate_idle_START         (3)
#define ABB_RX_IDLE_DIG_1_rx_rate_idle_END           (4)
#define ABB_RX_IDLE_DIG_1_rx_mode_dig_idle_START     (5)
#define ABB_RX_IDLE_DIG_1_rx_mode_dig_idle_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_IDLE_DIG_2_UNION
 �ṹ˵��  : rx_idle_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x401����ֵ:0x13�����:8
 �Ĵ���˵��: RX IDLEģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_idle         : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                              0����CLOCK GATING
                                                              1��CLOCK GATING(Ĭ��)
                                                              (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_idle         : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                              0����CLOCK GATING
                                                              1��CLOCK GATING(Ĭ��)
                                                              (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_idle       : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                              00��gainΪ0.5(Ĭ��)
                                                              01��gainΪ0.75
                                                              10��gainΪ0.85
                                                              11��Reserved */
        unsigned long  rx_comp_bp_idle     : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                              0����bypass(Ĭ��)
                                                              1��bypass */
        unsigned long  rx_clk_inv_idle     : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                              0������
                                                              1������ */
        unsigned long  rx_flush_en_idle    : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                              0����ʹ��
                                                              1��ʹ�� */
        unsigned long  rx_comp_sel_b1_idle : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵���� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_DIG_2_UNION;
#define ABB_RX_IDLE_DIG_2_rxa_pd_idle_START          (0)
#define ABB_RX_IDLE_DIG_2_rxa_pd_idle_END            (0)
#define ABB_RX_IDLE_DIG_2_rxb_pd_idle_START          (1)
#define ABB_RX_IDLE_DIG_2_rxb_pd_idle_END            (1)
#define ABB_RX_IDLE_DIG_2_gain_sel_idle_START        (2)
#define ABB_RX_IDLE_DIG_2_gain_sel_idle_END          (3)
#define ABB_RX_IDLE_DIG_2_rx_comp_bp_idle_START      (4)
#define ABB_RX_IDLE_DIG_2_rx_comp_bp_idle_END        (4)
#define ABB_RX_IDLE_DIG_2_rx_clk_inv_idle_START      (5)
#define ABB_RX_IDLE_DIG_2_rx_clk_inv_idle_END        (5)
#define ABB_RX_IDLE_DIG_2_rx_flush_en_idle_START     (6)
#define ABB_RX_IDLE_DIG_2_rx_flush_en_idle_END       (6)
#define ABB_RX_IDLE_DIG_2_rx_comp_sel_b1_idle_START  (7)
#define ABB_RX_IDLE_DIG_2_rx_comp_sel_b1_idle_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_IDLE_DIG_3_UNION
 �ṹ˵��  : rx_idle_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x402����ֵ:0x00�����:8
 �Ĵ���˵��: RX IDLEģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  blk_len_sel_idle : 2;  /* bit[0-1]:  */
        unsigned long  reserved         : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_IDLE_DIG_3_UNION;
#define ABB_RX_IDLE_DIG_3_blk_len_sel_idle_START  (0)
#define ABB_RX_IDLE_DIG_3_blk_len_sel_idle_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_RX_2G_DIG_1_UNION
 �ṹ˵��  : rx_2g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x403����ֵ:0x00�����:8
 �Ĵ���˵��: RX 2Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_comp_sel_b0_2g : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
                                                            00���̶�ϵ��1��
                                                            01���̶�ϵ��2��
                                                            10���̶�ϵ��3��
                                                            11���̶�ϵ��4�� */
        unsigned long  rx_comp_fix_2g    : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                            0��ϵ�����̶����ɼĴ�������
                                                            1��ϵ���̶� */
        unsigned long  rx_hb_bp_2g       : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                            0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                            1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  rx_rate_2g        : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                                2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                                                                      /TDS_B/4G_C,        /4G_B,
                                                            00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��),122.88M,2.167M,
                                                            others��reserved */
        unsigned long  rx_mode_dig_2g    : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                            000��2G_A(Ĭ��)
                                                            001��3G_SC/TDS_B/4G_C
                                                            010��4G
                                                            011��3G_DC/4G_B
                                                            100��TDS
                                                            101��CDMA
                                                            110��CA
                                                            111��2G_B */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_DIG_1_UNION;
#define ABB_RX_2G_DIG_1_rx_comp_sel_b0_2g_START  (0)
#define ABB_RX_2G_DIG_1_rx_comp_sel_b0_2g_END    (0)
#define ABB_RX_2G_DIG_1_rx_comp_fix_2g_START     (1)
#define ABB_RX_2G_DIG_1_rx_comp_fix_2g_END       (1)
#define ABB_RX_2G_DIG_1_rx_hb_bp_2g_START        (2)
#define ABB_RX_2G_DIG_1_rx_hb_bp_2g_END          (2)
#define ABB_RX_2G_DIG_1_rx_rate_2g_START         (3)
#define ABB_RX_2G_DIG_1_rx_rate_2g_END           (4)
#define ABB_RX_2G_DIG_1_rx_mode_dig_2g_START     (5)
#define ABB_RX_2G_DIG_1_rx_mode_dig_2g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_2G_DIG_2_UNION
 �ṹ˵��  : rx_2g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x404����ֵ:0x13�����:8
 �Ĵ���˵��: RX 2Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_2g         : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                            0����CLOCK GATING
                                                            1��CLOCK GATING(Ĭ��)
                                                            (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_2g         : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                            0����CLOCK GATING
                                                            1��CLOCK GATING(Ĭ��)
                                                            (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_2g       : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                            00��gainΪ0.5(Ĭ��)
                                                            01��gainΪ0.75
                                                            10��gainΪ0.85
                                                            11��Reserved */
        unsigned long  rx_comp_bp_2g     : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                            0����bypass
                                                            1��bypass(Ĭ��) */
        unsigned long  rx_clk_inv_2g     : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                            0������
                                                            1������ */
        unsigned long  rx_flush_en_2g    : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                            0����ʹ��
                                                            1��ʹ�� */
        unsigned long  rx_comp_sel_b1_2g : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵���� */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_DIG_2_UNION;
#define ABB_RX_2G_DIG_2_rxa_pd_2g_START          (0)
#define ABB_RX_2G_DIG_2_rxa_pd_2g_END            (0)
#define ABB_RX_2G_DIG_2_rxb_pd_2g_START          (1)
#define ABB_RX_2G_DIG_2_rxb_pd_2g_END            (1)
#define ABB_RX_2G_DIG_2_gain_sel_2g_START        (2)
#define ABB_RX_2G_DIG_2_gain_sel_2g_END          (3)
#define ABB_RX_2G_DIG_2_rx_comp_bp_2g_START      (4)
#define ABB_RX_2G_DIG_2_rx_comp_bp_2g_END        (4)
#define ABB_RX_2G_DIG_2_rx_clk_inv_2g_START      (5)
#define ABB_RX_2G_DIG_2_rx_clk_inv_2g_END        (5)
#define ABB_RX_2G_DIG_2_rx_flush_en_2g_START     (6)
#define ABB_RX_2G_DIG_2_rx_flush_en_2g_END       (6)
#define ABB_RX_2G_DIG_2_rx_comp_sel_b1_2g_START  (7)
#define ABB_RX_2G_DIG_2_rx_comp_sel_b1_2g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_2G_DIG_3_UNION
 �ṹ˵��  : rx_2g_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x405����ֵ:0x00�����:8
 �Ĵ���˵��: RX 2Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  blk_len_sel_2g : 2;  /* bit[0-1]:  */
        unsigned long  reserved       : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_2G_DIG_3_UNION;
#define ABB_RX_2G_DIG_3_blk_len_sel_2g_START  (0)
#define ABB_RX_2G_DIG_3_blk_len_sel_2g_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_RX_C_DIG_1_UNION
 �ṹ˵��  : rx_c_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x406����ֵ:0xA6�����:8
 �Ĵ���˵��: RX Cģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_comp_sel_b0_c : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
                                                           00���̶�ϵ��1��
                                                           01���̶�ϵ��2��
                                                           10���̶�ϵ��3��
                                                           11���̶�ϵ��4�� */
        unsigned long  rx_comp_fix_c    : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                           0��ϵ�����̶����ɼĴ�������
                                                           1��ϵ���̶� */
        unsigned long  rx_hb_bp_c       : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                           0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                           1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  rx_rate_c        : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                               2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                                                                     /TDS_B/4G_C,        /4G_B,
                                                           00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��),122.88M,2.167M,
                                                           others��reserved */
        unsigned long  rx_mode_dig_c    : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                           000��2G_A(Ĭ��)
                                                           001��3G_SC/TDS_B/4G_C
                                                           010��4G
                                                           011��3G_DC/4G_B
                                                           100��TDS
                                                           101��CDMA
                                                           110��CA
                                                           111��2G_B */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_DIG_1_UNION;
#define ABB_RX_C_DIG_1_rx_comp_sel_b0_c_START  (0)
#define ABB_RX_C_DIG_1_rx_comp_sel_b0_c_END    (0)
#define ABB_RX_C_DIG_1_rx_comp_fix_c_START     (1)
#define ABB_RX_C_DIG_1_rx_comp_fix_c_END       (1)
#define ABB_RX_C_DIG_1_rx_hb_bp_c_START        (2)
#define ABB_RX_C_DIG_1_rx_hb_bp_c_END          (2)
#define ABB_RX_C_DIG_1_rx_rate_c_START         (3)
#define ABB_RX_C_DIG_1_rx_rate_c_END           (4)
#define ABB_RX_C_DIG_1_rx_mode_dig_c_START     (5)
#define ABB_RX_C_DIG_1_rx_mode_dig_c_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_C_DIG_2_UNION
 �ṹ˵��  : rx_c_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x407����ֵ:0x93�����:8
 �Ĵ���˵��: RX Cģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_c         : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_c         : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_c       : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                           00��gainΪ0.5(Ĭ��)
                                                           01��gainΪ0.75
                                                           10��gainΪ0.85
                                                           11��Reserved */
        unsigned long  rx_comp_bp_c     : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                           0����bypass
                                                           1��bypass(Ĭ��) */
        unsigned long  rx_clk_inv_c     : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                           0������
                                                           1������ */
        unsigned long  rx_flush_en_c    : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                           0����ʹ��
                                                           1��ʹ�� */
        unsigned long  rx_comp_sel_b1_c : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_DIG_2_UNION;
#define ABB_RX_C_DIG_2_rxa_pd_c_START          (0)
#define ABB_RX_C_DIG_2_rxa_pd_c_END            (0)
#define ABB_RX_C_DIG_2_rxb_pd_c_START          (1)
#define ABB_RX_C_DIG_2_rxb_pd_c_END            (1)
#define ABB_RX_C_DIG_2_gain_sel_c_START        (2)
#define ABB_RX_C_DIG_2_gain_sel_c_END          (3)
#define ABB_RX_C_DIG_2_rx_comp_bp_c_START      (4)
#define ABB_RX_C_DIG_2_rx_comp_bp_c_END        (4)
#define ABB_RX_C_DIG_2_rx_clk_inv_c_START      (5)
#define ABB_RX_C_DIG_2_rx_clk_inv_c_END        (5)
#define ABB_RX_C_DIG_2_rx_flush_en_c_START     (6)
#define ABB_RX_C_DIG_2_rx_flush_en_c_END       (6)
#define ABB_RX_C_DIG_2_rx_comp_sel_b1_c_START  (7)
#define ABB_RX_C_DIG_2_rx_comp_sel_b1_c_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_C_DIG_3_UNION
 �ṹ˵��  : rx_c_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x408����ֵ:0x00�����:8
 �Ĵ���˵��: RX Cģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  blk_len_sel_c : 2;  /* bit[0-1]:  */
        unsigned long  reserved      : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_RX_C_DIG_3_UNION;
#define ABB_RX_C_DIG_3_blk_len_sel_c_START  (0)
#define ABB_RX_C_DIG_3_blk_len_sel_c_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_DIG_1_UNION
 �ṹ˵��  : rx_tds_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x409����ֵ:0x26�����:8
 �Ĵ���˵��: RX TDSģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_comp_sel_b0_tds : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
                                                             00���̶�ϵ��1��
                                                             01���̶�ϵ��2��
                                                             10���̶�ϵ��3��
                                                             11���̶�ϵ��4�� */
        unsigned long  rx_comp_fix_tds    : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                             0��ϵ�����̶����ɼĴ�������
                                                             1��ϵ���̶� */
        unsigned long  rx_hb_bp_tds       : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                             0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                             1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  rx_rate_tds        : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                                 2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                                                                       /TDS_B/4G_C,        /4G_B,
                                                             00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��),122.88M,2.167M,
                                                             others��reserved */
        unsigned long  rx_mode_dig_tds    : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                             000��2G_A(Ĭ��)
                                                             001��3G_SC/TDS_B/4G_C
                                                             010��4G
                                                             011��3G_DC/4G_B
                                                             100��TDS
                                                             101��CDMA
                                                             110��CA
                                                             111��2G_B */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_DIG_1_UNION;
#define ABB_RX_TDS_DIG_1_rx_comp_sel_b0_tds_START  (0)
#define ABB_RX_TDS_DIG_1_rx_comp_sel_b0_tds_END    (0)
#define ABB_RX_TDS_DIG_1_rx_comp_fix_tds_START     (1)
#define ABB_RX_TDS_DIG_1_rx_comp_fix_tds_END       (1)
#define ABB_RX_TDS_DIG_1_rx_hb_bp_tds_START        (2)
#define ABB_RX_TDS_DIG_1_rx_hb_bp_tds_END          (2)
#define ABB_RX_TDS_DIG_1_rx_rate_tds_START         (3)
#define ABB_RX_TDS_DIG_1_rx_rate_tds_END           (4)
#define ABB_RX_TDS_DIG_1_rx_mode_dig_tds_START     (5)
#define ABB_RX_TDS_DIG_1_rx_mode_dig_tds_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_DIG_2_UNION
 �ṹ˵��  : rx_tds_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x40A����ֵ:0xD3�����:8
 �Ĵ���˵��: RX TDSģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_tds         : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                             0����CLOCK GATING
                                                             1��CLOCK GATING(Ĭ��)
                                                             (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_tds         : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                             0����CLOCK GATING
                                                             1��CLOCK GATING(Ĭ��)
                                                             (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_tds       : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                             00��gainΪ0.5(Ĭ��)
                                                             01��gainΪ0.75
                                                             10��gainΪ0.85
                                                             11��Reserved */
        unsigned long  rx_comp_bp_tds     : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                             0����bypass
                                                             1��bypass(Ĭ��) */
        unsigned long  rx_clk_inv_tds     : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                             0������
                                                             1������ */
        unsigned long  rx_flush_en_tds    : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  rx_comp_sel_b1_tds : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵���� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_DIG_2_UNION;
#define ABB_RX_TDS_DIG_2_rxa_pd_tds_START          (0)
#define ABB_RX_TDS_DIG_2_rxa_pd_tds_END            (0)
#define ABB_RX_TDS_DIG_2_rxb_pd_tds_START          (1)
#define ABB_RX_TDS_DIG_2_rxb_pd_tds_END            (1)
#define ABB_RX_TDS_DIG_2_gain_sel_tds_START        (2)
#define ABB_RX_TDS_DIG_2_gain_sel_tds_END          (3)
#define ABB_RX_TDS_DIG_2_rx_comp_bp_tds_START      (4)
#define ABB_RX_TDS_DIG_2_rx_comp_bp_tds_END        (4)
#define ABB_RX_TDS_DIG_2_rx_clk_inv_tds_START      (5)
#define ABB_RX_TDS_DIG_2_rx_clk_inv_tds_END        (5)
#define ABB_RX_TDS_DIG_2_rx_flush_en_tds_START     (6)
#define ABB_RX_TDS_DIG_2_rx_flush_en_tds_END       (6)
#define ABB_RX_TDS_DIG_2_rx_comp_sel_b1_tds_START  (7)
#define ABB_RX_TDS_DIG_2_rx_comp_sel_b1_tds_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_TDS_DIG_3_UNION
 �ṹ˵��  : rx_tds_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x40B����ֵ:0x00�����:8
 �Ĵ���˵��: RX TDSģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  blk_len_sel_tds : 2;  /* bit[0-1]:  */
        unsigned long  reserved        : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_RX_TDS_DIG_3_UNION;
#define ABB_RX_TDS_DIG_3_blk_len_sel_tds_START  (0)
#define ABB_RX_TDS_DIG_3_blk_len_sel_tds_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_RX_3G_DIG_1_UNION
 �ṹ˵��  : rx_3g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x40C����ֵ:0x26�����:8
 �Ĵ���˵��: RX 3Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_comp_sel_b0_3g : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
                                                            00���̶�ϵ��1��
                                                            01���̶�ϵ��2��
                                                            10���̶�ϵ��3��
                                                            11���̶�ϵ��4�� */
        unsigned long  rx_comp_fix_3g    : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                            0��ϵ�����̶����ɼĴ�������
                                                            1��ϵ���̶� */
        unsigned long  rx_hb_bp_3g       : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                            0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                            1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  rx_rate_3g        : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                                2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                                                                      /TDS_B/4G_C,        /4G_B,
                                                            00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��),122.88M,2.167M,
                                                            others��reserved */
        unsigned long  rx_mode_dig_3g    : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                            000��2G_A(Ĭ��)
                                                            001��3G_SC/TDS_B/4G_C
                                                            010��4G
                                                            011��3G_DC/4G_B
                                                            100��TDS
                                                            101��CDMA
                                                            110��CA
                                                            111��2G_B */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_3G_DIG_1_UNION;
#define ABB_RX_3G_DIG_1_rx_comp_sel_b0_3g_START  (0)
#define ABB_RX_3G_DIG_1_rx_comp_sel_b0_3g_END    (0)
#define ABB_RX_3G_DIG_1_rx_comp_fix_3g_START     (1)
#define ABB_RX_3G_DIG_1_rx_comp_fix_3g_END       (1)
#define ABB_RX_3G_DIG_1_rx_hb_bp_3g_START        (2)
#define ABB_RX_3G_DIG_1_rx_hb_bp_3g_END          (2)
#define ABB_RX_3G_DIG_1_rx_rate_3g_START         (3)
#define ABB_RX_3G_DIG_1_rx_rate_3g_END           (4)
#define ABB_RX_3G_DIG_1_rx_mode_dig_3g_START     (5)
#define ABB_RX_3G_DIG_1_rx_mode_dig_3g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_3G_DIG_2_UNION
 �ṹ˵��  : rx_3g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x40D����ֵ:0x03�����:8
 �Ĵ���˵��: RX 3Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_3g         : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                            0����CLOCK GATING
                                                            1��CLOCK GATING(Ĭ��)
                                                            (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_3g         : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                            0����CLOCK GATING
                                                            1��CLOCK GATING(Ĭ��)
                                                            (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_3g       : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                            00��gainΪ0.5(Ĭ��)
                                                            01��gainΪ0.75
                                                            10��gainΪ0.85
                                                            11��Reserved */
        unsigned long  rx_comp_bp_3g     : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                            0����bypass(Ĭ��)
                                                            1��bypass */
        unsigned long  rx_clk_inv_3g     : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                            0������
                                                            1������ */
        unsigned long  rx_flush_en_3g    : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                            0����ʹ��
                                                            1��ʹ�� */
        unsigned long  rx_comp_sel_b1_3g : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵���� */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_3G_DIG_2_UNION;
#define ABB_RX_3G_DIG_2_rxa_pd_3g_START          (0)
#define ABB_RX_3G_DIG_2_rxa_pd_3g_END            (0)
#define ABB_RX_3G_DIG_2_rxb_pd_3g_START          (1)
#define ABB_RX_3G_DIG_2_rxb_pd_3g_END            (1)
#define ABB_RX_3G_DIG_2_gain_sel_3g_START        (2)
#define ABB_RX_3G_DIG_2_gain_sel_3g_END          (3)
#define ABB_RX_3G_DIG_2_rx_comp_bp_3g_START      (4)
#define ABB_RX_3G_DIG_2_rx_comp_bp_3g_END        (4)
#define ABB_RX_3G_DIG_2_rx_clk_inv_3g_START      (5)
#define ABB_RX_3G_DIG_2_rx_clk_inv_3g_END        (5)
#define ABB_RX_3G_DIG_2_rx_flush_en_3g_START     (6)
#define ABB_RX_3G_DIG_2_rx_flush_en_3g_END       (6)
#define ABB_RX_3G_DIG_2_rx_comp_sel_b1_3g_START  (7)
#define ABB_RX_3G_DIG_2_rx_comp_sel_b1_3g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_3G_DIG_3_UNION
 �ṹ˵��  : rx_3g_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x40E����ֵ:0x00�����:8
 �Ĵ���˵��: RX 3Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  blk_len_sel_3g : 2;  /* bit[0-1]:  */
        unsigned long  reserved       : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_3G_DIG_3_UNION;
#define ABB_RX_3G_DIG_3_blk_len_sel_3g_START  (0)
#define ABB_RX_3G_DIG_3_blk_len_sel_3g_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_RX_4G_DIG_1_UNION
 �ṹ˵��  : rx_4g_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x40F����ֵ:0x42�����:8
 �Ĵ���˵��: RX 4Gģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_comp_sel_b0_4g : 1;  /* bit[0]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
                                                            00���̶�ϵ��1��
                                                            01���̶�ϵ��2��
                                                            10���̶�ϵ��3��
                                                            11���̶�ϵ��4�� */
        unsigned long  rx_comp_fix_4g    : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                            0��ϵ�����̶����ɼĴ�������
                                                            1��ϵ���̶� */
        unsigned long  rx_hb_bp_4g       : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                            0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                            1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  rx_rate_4g        : 2;  /* bit[3-4]: RXͨ��CIC�˲���������ʿ���(Hz)��
                                                                2G_A,     3G_SC      4G,    3G_DC    TDS,   CDMA,         CA,    2G_B
                                                                      /TDS_B/4G_C,        /4G_B,
                                                            00��2.167M, 15.36M,   61.44M, 30.72M, 30.72M, 4.9152(Ĭ��),122.88M,2.167M,
                                                            others��reserved */
        unsigned long  rx_mode_dig_4g    : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                            000��2G_A(Ĭ��)
                                                            001��3G_SC/TDS_B/4G_C
                                                            010��4G
                                                            011��3G_DC/4G_B
                                                            100��TDS
                                                            101��CDMA
                                                            110��CA
                                                            111��2G_B */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_4G_DIG_1_UNION;
#define ABB_RX_4G_DIG_1_rx_comp_sel_b0_4g_START  (0)
#define ABB_RX_4G_DIG_1_rx_comp_sel_b0_4g_END    (0)
#define ABB_RX_4G_DIG_1_rx_comp_fix_4g_START     (1)
#define ABB_RX_4G_DIG_1_rx_comp_fix_4g_END       (1)
#define ABB_RX_4G_DIG_1_rx_hb_bp_4g_START        (2)
#define ABB_RX_4G_DIG_1_rx_hb_bp_4g_END          (2)
#define ABB_RX_4G_DIG_1_rx_rate_4g_START         (3)
#define ABB_RX_4G_DIG_1_rx_rate_4g_END           (4)
#define ABB_RX_4G_DIG_1_rx_mode_dig_4g_START     (5)
#define ABB_RX_4G_DIG_1_rx_mode_dig_4g_END       (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_4G_DIG_2_UNION
 �ṹ˵��  : rx_4g_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x410����ֵ:0x03�����:8
 �Ĵ���˵��: RX 4Gģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rxa_pd_4g         : 1;  /* bit[0]  : RXAͨ��CLOCK GATING���ƣ�
                                                            0����CLOCK GATING
                                                            1��CLOCK GATING(Ĭ��)
                                                            (!rxa_pd)|XX_RXA_EN = 1ʱ����������ر� */
        unsigned long  rxb_pd_4g         : 1;  /* bit[1]  : RXBͨ��CLOCK GATING���ƣ�
                                                            0����CLOCK GATING
                                                            1��CLOCK GATING(Ĭ��)
                                                            (!rxb_pd)|XX_RXB_EN = 1ʱ����������ر� */
        unsigned long  gain_sel_4g       : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                            00��gainΪ0.5(Ĭ��)
                                                            01��gainΪ0.75
                                                            10��gainΪ0.85
                                                            11��Reserved */
        unsigned long  rx_comp_bp_4g     : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                            0����bypass(Ĭ��)
                                                            1��bypass */
        unsigned long  rx_clk_inv_4g     : 1;  /* bit[5]  : RXͨ����·ʱ��RX_CLK����ʹ�ܣ�
                                                            0������
                                                            1������ */
        unsigned long  rx_flush_en_4g    : 1;  /* bit[6]  : RXͨ��FLUSHʹ�ܣ�
                                                            0����ʹ��
                                                            1��ʹ�� */
        unsigned long  rx_comp_sel_b1_4g : 1;  /* bit[7]  : {rx_comp_sel_b1,rx_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�rx_comp_sel_b0˵���� */
        unsigned long  reserved_butt     : 24; /* bit[8-31] */
    } reg;
} ABB_RX_4G_DIG_2_UNION;
#define ABB_RX_4G_DIG_2_rxa_pd_4g_START          (0)
#define ABB_RX_4G_DIG_2_rxa_pd_4g_END            (0)
#define ABB_RX_4G_DIG_2_rxb_pd_4g_START          (1)
#define ABB_RX_4G_DIG_2_rxb_pd_4g_END            (1)
#define ABB_RX_4G_DIG_2_gain_sel_4g_START        (2)
#define ABB_RX_4G_DIG_2_gain_sel_4g_END          (3)
#define ABB_RX_4G_DIG_2_rx_comp_bp_4g_START      (4)
#define ABB_RX_4G_DIG_2_rx_comp_bp_4g_END        (4)
#define ABB_RX_4G_DIG_2_rx_clk_inv_4g_START      (5)
#define ABB_RX_4G_DIG_2_rx_clk_inv_4g_END        (5)
#define ABB_RX_4G_DIG_2_rx_flush_en_4g_START     (6)
#define ABB_RX_4G_DIG_2_rx_flush_en_4g_END       (6)
#define ABB_RX_4G_DIG_2_rx_comp_sel_b1_4g_START  (7)
#define ABB_RX_4G_DIG_2_rx_comp_sel_b1_4g_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_RX_4G_DIG_3_UNION
 �ṹ˵��  : rx_4g_dig_3 �Ĵ����ṹ���塣��ַƫ����:0x411����ֵ:0x00�����:8
 �Ĵ���˵��: RX 4Gģʽ���üĴ���3�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  blk_len_sel_4g : 2;  /* bit[0-1]:  */
        unsigned long  reserved       : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_RX_4G_DIG_3_UNION;
#define ABB_RX_4G_DIG_3_blk_len_sel_4g_START  (0)
#define ABB_RX_4G_DIG_3_blk_len_sel_4g_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_RX_EN_DELAY_UNION
 �ṹ˵��  : RX_EN_DELAY �Ĵ����ṹ���塣��ַƫ����:0x420����ֵ:0x01�����:8
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
 �ṹ˵��  : COMB_MODE �Ĵ����ṹ���塣��ַƫ����:0x421����ֵ:0x00�����:8
 �Ĵ���˵��: ģʽ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  comb_mode : 1;  /* bit[0]  :  */
        unsigned long  reserved  : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_COMB_MODE_UNION;
#define ABB_COMB_MODE_comb_mode_START  (0)
#define ABB_COMB_MODE_comb_mode_END    (0)


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
        unsigned long  reserved_0      : 2;  /* bit[2-3]: ���� */
        unsigned long  ch0_out_sel     : 2;  /* bit[4-5]:  */
        unsigned long  reserved_1      : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_RX_TESTMODE_UNION;
#define ABB_CH0_RX_TESTMODE_ch0_rx_sw_rst_START    (0)
#define ABB_CH0_RX_TESTMODE_ch0_rx_sw_rst_END      (0)
#define ABB_CH0_RX_TESTMODE_ch0_cic_gate_en_START  (1)
#define ABB_CH0_RX_TESTMODE_ch0_cic_gate_en_END    (1)
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
        unsigned long  ch0_g_pll_sel   : 2;  /* bit[0-1]:  */
        unsigned long  ch0_wtl_pll_sel : 1;  /* bit[2]  :  */
        unsigned long  ch0_c1_pll_sel  : 1;  /* bit[3]  :  */
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
 �ṹ��    : ABB_CH0_RXA_I_COEF1_UNION
 �ṹ˵��  : ch0_rxa_i_coef1 �Ĵ����ṹ���塣��ַƫ����:0x485����ֵ:0xC1�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : ch0_rxa_i_coef3 �Ĵ����ṹ���塣��ַƫ����:0x487����ֵ:0x41�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : ch0_rxa_q_coef1 �Ĵ����ṹ���塣��ַƫ����:0x48A����ֵ:0xC1�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : ch0_rxa_q_coef3 �Ĵ����ṹ���塣��ַƫ����:0x48C����ֵ:0x41�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : ch0_rxb_i_coef1 �Ĵ����ṹ���塣��ַƫ����:0x48F����ֵ:0xC1�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : ch0_rxb_i_coef3 �Ĵ����ṹ���塣��ַƫ����:0x491����ֵ:0x41�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : ch0_rxb_q_coef1 �Ĵ����ṹ���塣��ַƫ����:0x494����ֵ:0xC1�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : ch0_rxb_q_coef3 �Ĵ����ṹ���塣��ַƫ����:0x496����ֵ:0x41�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : ch0_reg_rxa_dcr_cfg �Ĵ����ṹ���塣��ַƫ����:0x498����ֵ:0x46�����:8
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
 �ṹ˵��  : ch0_reg_rxb_dcr_cfg �Ĵ����ṹ���塣��ַƫ����:0x499����ֵ:0x46�����:8
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
 �ṹ˵��  : ch0_reg_rx_dcr_ctrl �Ĵ����ṹ���塣��ַƫ����:0x49A����ֵ:0x00�����:8
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
 �ṹ˵��  : ch0_rxa_blocking �Ĵ����ṹ���塣��ַƫ����:0x49B����ֵ:0x00�����:8
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
 �ṹ˵��  : ch0_rxb_blocking �Ĵ����ṹ���塣��ַƫ����:0x49C����ֵ:0x00�����:8
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
 �ṹ˵��  : ch0_reg_rxa_dc_i_2 �Ĵ����ṹ���塣��ַƫ����:0x49E����ֵ:0x00�����:8
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
 �ṹ˵��  : ch0_reg_rxa_dc_q_2 �Ĵ����ṹ���塣��ַƫ����:0x4A0����ֵ:0x00�����:8
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
 �ṹ˵��  : ch0_reg_rxb_dc_i_2 �Ĵ����ṹ���塣��ַƫ����:0x4A2����ֵ:0x00�����:8
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
 �ṹ˵��  : ch0_reg_rxb_dc_q_2 �Ĵ����ṹ���塣��ַƫ����:0x4A4����ֵ:0x00�����:8
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
 �ṹ˵��  : CH0_FLUSH_CFG1 �Ĵ����ṹ���塣��ַƫ����:0x4A6����ֵ:0x40�����:8
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
 �ṹ˵��  : CH0_RXAI_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x4A8����ֵ:0x02�����:8
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
 �ṹ˵��  : CH0_RXAQ_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x4AA����ֵ:0x02�����:8
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
 �ṹ˵��  : CH0_RXBI_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x4AC����ֵ:0x02�����:8
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
 �ṹ˵��  : CH0_RXBQ_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x4AE����ֵ:0x02�����:8
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
 �ṹ˵��  : ch0_ctrl �Ĵ����ṹ���塣��ַƫ����:0x4AF����ֵ:0x03�����:8
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
 �ṹ˵��  : ch0_rx_line_sel �Ĵ����ṹ���塣��ַƫ����:0x4B0����ֵ:0x00�����:8
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
 �ṹ˵��  : ch0_rx_line_cfg �Ĵ����ṹ���塣��ַƫ����:0x4B1����ֵ:0x00�����:8
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
 �ṹ˵��  : ch0_blk_cfg �Ĵ����ṹ���塣��ַƫ����:0x4B2����ֵ:0x00�����:8
 �Ĵ���˵��: blk���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_blk_clk_sel : 1;  /* bit[0]  : BLOCKING�Զ��ſ�ʹ�ܣ�
                                                          0��ʹ��
                                                          1����ʹ�� */
        unsigned long  ch0_blk_en_cfg  : 1;  /* bit[1]  : �߿��ź�CH0_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ֵ */
        unsigned long  ch0_blk_en_sel  : 1;  /* bit[2]  : �߿��ź�CH0_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ʹ�� */
        unsigned long  reserved        : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_BLK_CFG_UNION;
#define ABB_CH0_BLK_CFG_ch0_blk_clk_sel_START  (0)
#define ABB_CH0_BLK_CFG_ch0_blk_clk_sel_END    (0)
#define ABB_CH0_BLK_CFG_ch0_blk_en_cfg_START   (1)
#define ABB_CH0_BLK_CFG_ch0_blk_en_cfg_END     (1)
#define ABB_CH0_BLK_CFG_ch0_blk_en_sel_START   (2)
#define ABB_CH0_BLK_CFG_ch0_blk_en_sel_END     (2)


/*****************************************************************************
 �ṹ��    : ABB_CH0_RX_REG_DEBUG_DIG_UNION
 �ṹ˵��  : ch0_rx_reg_debug_dig �Ĵ����ṹ���塣��ַƫ����:0x4B5����ֵ:0x00�����:8
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
 �ṹ˵��  : CH1_RX_TESTMODE �Ĵ����ṹ���塣��ַƫ����:0x4C0����ֵ:0x00�����:8
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
        unsigned long  reserved_0      : 2;  /* bit[2-3]: ���� */
        unsigned long  ch1_out_sel     : 2;  /* bit[4-5]:  */
        unsigned long  reserved_1      : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_RX_TESTMODE_UNION;
#define ABB_CH1_RX_TESTMODE_ch1_rx_sw_rst_START    (0)
#define ABB_CH1_RX_TESTMODE_ch1_rx_sw_rst_END      (0)
#define ABB_CH1_RX_TESTMODE_ch1_cic_gate_en_START  (1)
#define ABB_CH1_RX_TESTMODE_ch1_cic_gate_en_END    (1)
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
        unsigned long  ch1_g_pll_sel   : 2;  /* bit[0-1]:  */
        unsigned long  ch1_wtl_pll_sel : 1;  /* bit[2]  :  */
        unsigned long  ch1_c1_pll_sel  : 1;  /* bit[3]  :  */
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
 �ṹ��    : ABB_CH1_RXA_I_COEF1_UNION
 �ṹ˵��  : ch1_rxa_i_coef1 �Ĵ����ṹ���塣��ַƫ����:0x4C5����ֵ:0xC1�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : ch1_rxa_i_coef3 �Ĵ����ṹ���塣��ַƫ����:0x4C7����ֵ:0x41�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : ch1_rxa_q_coef1 �Ĵ����ṹ���塣��ַƫ����:0x4CA����ֵ:0xC1�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : ch1_rxa_q_coef3 �Ĵ����ṹ���塣��ַƫ����:0x4CC����ֵ:0x41�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : ch1_rxb_i_coef1 �Ĵ����ṹ���塣��ַƫ����:0x4CF����ֵ:0xC1�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : ch1_rxb_i_coef3 �Ĵ����ṹ���塣��ַƫ����:0x4D1����ֵ:0x41�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : ch1_rxb_q_coef1 �Ĵ����ṹ���塣��ַƫ����:0x4D4����ֵ:0xC1�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : ch1_rxb_q_coef3 �Ĵ����ṹ���塣��ַƫ����:0x4D6����ֵ:0x41�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
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
 �ṹ˵��  : ch1_reg_rxa_dcr_cfg �Ĵ����ṹ���塣��ַƫ����:0x4D8����ֵ:0x46�����:8
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
 �ṹ˵��  : ch1_reg_rxb_dcr_cfg �Ĵ����ṹ���塣��ַƫ����:0x4D9����ֵ:0x46�����:8
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
 �ṹ˵��  : ch1_reg_rx_dcr_ctrl �Ĵ����ṹ���塣��ַƫ����:0x4DA����ֵ:0x00�����:8
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
 �ṹ˵��  : ch1_rxa_blocking �Ĵ����ṹ���塣��ַƫ����:0x4DB����ֵ:0x00�����:8
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
 �ṹ˵��  : ch1_rxb_blocking �Ĵ����ṹ���塣��ַƫ����:0x4DC����ֵ:0x00�����:8
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
 �ṹ˵��  : ch1_reg_rxa_dc_i_2 �Ĵ����ṹ���塣��ַƫ����:0x4DE����ֵ:0x00�����:8
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
 �ṹ˵��  : ch1_reg_rxa_dc_q_2 �Ĵ����ṹ���塣��ַƫ����:0x4E0����ֵ:0x00�����:8
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
 �ṹ˵��  : ch1_reg_rxb_dc_i_2 �Ĵ����ṹ���塣��ַƫ����:0x4E2����ֵ:0x00�����:8
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
 �ṹ˵��  : ch1_reg_rxb_dc_q_2 �Ĵ����ṹ���塣��ַƫ����:0x4E4����ֵ:0x00�����:8
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
 �ṹ˵��  : CH1_FLUSH_CFG1 �Ĵ����ṹ���塣��ַƫ����:0x4E6����ֵ:0x40�����:8
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
 �ṹ˵��  : CH1_RXAI_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x4E8����ֵ:0x02�����:8
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
 �ṹ˵��  : CH1_RXAQ_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x4EA����ֵ:0x02�����:8
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
 �ṹ˵��  : CH1_RXBI_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x4EC����ֵ:0x02�����:8
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
 �ṹ˵��  : CH1_RXBQ_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x4EE����ֵ:0x02�����:8
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
 �ṹ˵��  : ch1_ctrl �Ĵ����ṹ���塣��ַƫ����:0x4EF����ֵ:0x03�����:8
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
 �ṹ˵��  : ch1_rx_line_sel �Ĵ����ṹ���塣��ַƫ����:0x4F0����ֵ:0x00�����:8
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
 �ṹ˵��  : ch1_rx_line_cfg �Ĵ����ṹ���塣��ַƫ����:0x4F1����ֵ:0x00�����:8
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
 �ṹ˵��  : ch1_blk_cfg �Ĵ����ṹ���塣��ַƫ����:0x4F2����ֵ:0x00�����:8
 �Ĵ���˵��: blk���ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_blk_clk_sel : 1;  /* bit[0]  : BLOCKING�Զ��ſ�ʹ�ܣ�
                                                          0��ʹ��
                                                          1����ʹ�� */
        unsigned long  ch1_blk_en_cfg  : 1;  /* bit[1]  : �߿��ź�CH1_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ֵ */
        unsigned long  ch1_blk_en_sel  : 1;  /* bit[2]  : �߿��ź�CH1_RXA_BLK_EN, CH1_RXB_BLK_ENǿ������ʹ�� */
        unsigned long  reserved        : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_BLK_CFG_UNION;
#define ABB_CH1_BLK_CFG_ch1_blk_clk_sel_START  (0)
#define ABB_CH1_BLK_CFG_ch1_blk_clk_sel_END    (0)
#define ABB_CH1_BLK_CFG_ch1_blk_en_cfg_START   (1)
#define ABB_CH1_BLK_CFG_ch1_blk_en_cfg_END     (1)
#define ABB_CH1_BLK_CFG_ch1_blk_en_sel_START   (2)
#define ABB_CH1_BLK_CFG_ch1_blk_en_sel_END     (2)


/*****************************************************************************
 �ṹ��    : ABB_CH1_RX_REG_DEBUG_DIG_UNION
 �ṹ˵��  : ch1_rx_reg_debug_dig �Ĵ����ṹ���塣��ַƫ����:0x4F5����ֵ:0x00�����:8
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


/*****************************************************************************
 �ṹ��    : ABB_DEBUG_RESET_UNION
 �ṹ˵��  : DEBUG_RESET �Ĵ����ṹ���塣��ַƫ����:0x602����ֵ:0x00�����:8
 �Ĵ���˵��:
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  dbg_sw_rst : 1;  /* bit[0]  :  */
        unsigned long  reserved   : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_DEBUG_RESET_UNION;
#define ABB_DEBUG_RESET_dbg_sw_rst_START  (0)
#define ABB_DEBUG_RESET_dbg_sw_rst_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_DEBUG_CHANNEL_SEL_UNION
 �ṹ˵��  : DEBUG_CHANNEL_SEL �Ĵ����ṹ���塣��ַƫ����:0x603����ֵ:0x00�����:8
 �Ĵ���˵��:
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  cpu_rx_ch3_sel        : 2;  /* bit[0-1]:  */
        unsigned long  cpu_rx_dbg_adc_sel    : 2;  /* bit[2-3]:  */
        unsigned long  cpu_rx_dbg_chab_sel   : 1;  /* bit[4]  :  */
        unsigned long  cpu_rx_dbg_pdm_hb_sel : 1;  /* bit[5]  :  */
        unsigned long  reserved              : 2;  /* bit[6-7]: ���� */
        unsigned long  reserved_butt         : 24; /* bit[8-31] */
    } reg;
} ABB_DEBUG_CHANNEL_SEL_UNION;
#define ABB_DEBUG_CHANNEL_SEL_cpu_rx_ch3_sel_START         (0)
#define ABB_DEBUG_CHANNEL_SEL_cpu_rx_ch3_sel_END           (1)
#define ABB_DEBUG_CHANNEL_SEL_cpu_rx_dbg_adc_sel_START     (2)
#define ABB_DEBUG_CHANNEL_SEL_cpu_rx_dbg_adc_sel_END       (3)
#define ABB_DEBUG_CHANNEL_SEL_cpu_rx_dbg_chab_sel_START    (4)
#define ABB_DEBUG_CHANNEL_SEL_cpu_rx_dbg_chab_sel_END      (4)
#define ABB_DEBUG_CHANNEL_SEL_cpu_rx_dbg_pdm_hb_sel_START  (5)
#define ABB_DEBUG_CHANNEL_SEL_cpu_rx_dbg_pdm_hb_sel_END    (5)


/*****************************************************************************
 �ṹ��    : ABB_DEBUG_RAM_EN_UNION
 �ṹ˵��  : DEBUG_RAM_EN �Ĵ����ṹ���塣��ַƫ����:0x604����ֵ:0x00�����:8
 �Ĵ���˵��:
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  cpu_rx_dbg_en : 1;  /* bit[0]  :  */
        unsigned long  reserved      : 7;  /* bit[1-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_DEBUG_RAM_EN_UNION;
#define ABB_DEBUG_RAM_EN_cpu_rx_dbg_en_START  (0)
#define ABB_DEBUG_RAM_EN_cpu_rx_dbg_en_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_DEBUG_RAM_CFG_UNION
 �ṹ˵��  : DEBUG_RAM_CFG �Ĵ����ṹ���塣��ַƫ����:0x605����ֵ:0x00�����:8
 �Ĵ���˵��:
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  cpu_rx_ram_wr_start : 1;  /* bit[0]  :  */
        unsigned long  cpu_rx_ram_wr_clr   : 1;  /* bit[1]  :  */
        unsigned long  cpu_rx_ram_rd_clr   : 1;  /* bit[2]  :  */
        unsigned long  reserved            : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_DEBUG_RAM_CFG_UNION;
#define ABB_DEBUG_RAM_CFG_cpu_rx_ram_wr_start_START  (0)
#define ABB_DEBUG_RAM_CFG_cpu_rx_ram_wr_start_END    (0)
#define ABB_DEBUG_RAM_CFG_cpu_rx_ram_wr_clr_START    (1)
#define ABB_DEBUG_RAM_CFG_cpu_rx_ram_wr_clr_END      (1)
#define ABB_DEBUG_RAM_CFG_cpu_rx_ram_rd_clr_START    (2)
#define ABB_DEBUG_RAM_CFG_cpu_rx_ram_rd_clr_END      (2)


/*****************************************************************************
 �ṹ��    : ABB_DEBUG_RAM_RPT1_UNION
 �ṹ˵��  : DEBUG_RAM_RPT1 �Ĵ����ṹ���塣��ַƫ����:0x606����ֵ:0x00�����:8
 �Ĵ���˵��:
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_ram_wr_en_cpu : 1;  /* bit[0]  :  */
        unsigned long  reserved_0       : 1;  /* bit[1]  : ���� */
        unsigned long  rx_ram_rd_en_cpu : 1;  /* bit[2]  :  */
        unsigned long  reserved_1       : 5;  /* bit[3-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_DEBUG_RAM_RPT1_UNION;
#define ABB_DEBUG_RAM_RPT1_rx_ram_wr_en_cpu_START  (0)
#define ABB_DEBUG_RAM_RPT1_rx_ram_wr_en_cpu_END    (0)
#define ABB_DEBUG_RAM_RPT1_rx_ram_rd_en_cpu_START  (2)
#define ABB_DEBUG_RAM_RPT1_rx_ram_rd_en_cpu_END    (2)


/*****************************************************************************
 �ṹ��    : ABB_DEBUG_RAM_RPT2_UNION
 �ṹ˵��  : DEBUG_RAM_RPT2 �Ĵ����ṹ���塣��ַƫ����:0x607����ֵ:0x00�����:8
 �Ĵ���˵��:
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_ram_wr_addr_cpu_msb : 7;  /* bit[0-6]:  */
        unsigned long  reserved               : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_DEBUG_RAM_RPT2_UNION;
#define ABB_DEBUG_RAM_RPT2_rx_ram_wr_addr_cpu_msb_START  (0)
#define ABB_DEBUG_RAM_RPT2_rx_ram_wr_addr_cpu_msb_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_DEBUG_RAM_RPT4_UNION
 �ṹ˵��  : DEBUG_RAM_RPT4 �Ĵ����ṹ���塣��ַƫ����:0x609����ֵ:0x00�����:8
 �Ĵ���˵��:
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  rx_ram_rd_addr_cpu_msb : 7;  /* bit[0-6]:  */
        unsigned long  reserved               : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt          : 24; /* bit[8-31] */
    } reg;
} ABB_DEBUG_RAM_RPT4_UNION;
#define ABB_DEBUG_RAM_RPT4_rx_ram_rd_addr_cpu_msb_START  (0)
#define ABB_DEBUG_RAM_RPT4_rx_ram_rd_addr_cpu_msb_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_SAR_DIG_1_UNION
 �ṹ˵��  : sar_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x680����ֵ:0x00�����:8
 �Ĵ���˵��: RX IDLEģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sar_comp_sel_b0 : 1;  /* bit[0]  : {sar_comp_sel_b1,sar_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
                                                          00���̶�ϵ��1��
                                                          01���̶�ϵ��2��
                                                          10���̶�ϵ��3��
                                                          11���̶�ϵ��4�� */
        unsigned long  sar_comp_fix    : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                          0��ϵ�����̶����ɼĴ�������
                                                          1��ϵ���̶� */
        unsigned long  sar_hb_bp       : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                          0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                          1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  reserved        : 2;  /* bit[3-4]: ���� */
        unsigned long  sar_mode        : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                          000��2G_A(Ĭ��)
                                                          001��3G_SC/TDS_B/4G_C
                                                          010��4G
                                                          011��3G_DC/4G_B
                                                          100��TDS
                                                          101��CDMA
                                                          110��CA
                                                          111��2G_B */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_SAR_DIG_1_UNION;
#define ABB_SAR_DIG_1_sar_comp_sel_b0_START  (0)
#define ABB_SAR_DIG_1_sar_comp_sel_b0_END    (0)
#define ABB_SAR_DIG_1_sar_comp_fix_START     (1)
#define ABB_SAR_DIG_1_sar_comp_fix_END       (1)
#define ABB_SAR_DIG_1_sar_hb_bp_START        (2)
#define ABB_SAR_DIG_1_sar_hb_bp_END          (2)
#define ABB_SAR_DIG_1_sar_mode_START         (5)
#define ABB_SAR_DIG_1_sar_mode_END           (7)


/*****************************************************************************
 �ṹ��    : ABB_SAR_DIG_2_UNION
 �ṹ˵��  : sar_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x681����ֵ:0x12�����:8
 �Ĵ���˵��: RX IDLEģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sar_en          : 1;  /* bit[0]  : SARͨ��CLOCK GATING���ƣ�
                                                          0����CLOCK GATING
                                                          1��CLOCK GATING(Ĭ��)
                                                          (!sar_pd)|XX_SAR_EN = 1ʱ����������ر� */
        unsigned long  reserved_0      : 1;  /* bit[1]  : ���� */
        unsigned long  sar_gain_sel    : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                          00��gainΪ0.5(Ĭ��)
                                                          01��gainΪ0.75
                                                          10��gainΪ0.85
                                                          11��Reserved */
        unsigned long  sar_comp_bp     : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                          0����bypass(Ĭ��)
                                                          1��bypass */
        unsigned long  sar_clk_inv     : 1;  /* bit[5]  : RXͨ����·ʱ��SAR_CLK����ʹ�ܣ�
                                                          0������
                                                          1������ */
        unsigned long  reserved_1      : 1;  /* bit[6]  : ���� */
        unsigned long  sar_comp_sel_b1 : 1;  /* bit[7]  : {sar_comp_sel_b1,sar_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�sar_comp_sel_b0˵���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_SAR_DIG_2_UNION;
#define ABB_SAR_DIG_2_sar_en_START           (0)
#define ABB_SAR_DIG_2_sar_en_END             (0)
#define ABB_SAR_DIG_2_sar_gain_sel_START     (2)
#define ABB_SAR_DIG_2_sar_gain_sel_END       (3)
#define ABB_SAR_DIG_2_sar_comp_bp_START      (4)
#define ABB_SAR_DIG_2_sar_comp_bp_END        (4)
#define ABB_SAR_DIG_2_sar_clk_inv_START      (5)
#define ABB_SAR_DIG_2_sar_clk_inv_END        (5)
#define ABB_SAR_DIG_2_sar_comp_sel_b1_START  (7)
#define ABB_SAR_DIG_2_sar_comp_sel_b1_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_SAR_TESTMODE_UNION
 �ṹ˵��  : SAR_TESTMODE �Ĵ����ṹ���塣��ַƫ����:0x682����ֵ:0x00�����:8
 �Ĵ���˵��: ����ģʽ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sar_sw_rst      : 1;  /* bit[0]  : ���ֲ���RXͨ����λ�źţ�
                                                          0������λ(Ĭ��)
                                                          1����λ */
        unsigned long  sar_cic_gate_en : 1;  /* bit[1]  :  */
        unsigned long  reserved        : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_SAR_TESTMODE_UNION;
#define ABB_SAR_TESTMODE_sar_sw_rst_START       (0)
#define ABB_SAR_TESTMODE_sar_sw_rst_END         (0)
#define ABB_SAR_TESTMODE_sar_cic_gate_en_START  (1)
#define ABB_SAR_TESTMODE_sar_cic_gate_en_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_SAR_PLL_SEL_UNION
 �ṹ˵��  : SAR_PLL_SEL �Ĵ����ṹ���塣��ַƫ����:0x683����ֵ:0x00�����:8
 �Ĵ���˵��: PLLѡ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sar_g_pll_sel   : 2;  /* bit[0-1]:  */
        unsigned long  sar_wtl_pll_sel : 1;  /* bit[2]  :  */
        unsigned long  sar_c1_pll_sel  : 1;  /* bit[3]  :  */
        unsigned long  reserved        : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_SAR_PLL_SEL_UNION;
#define ABB_SAR_PLL_SEL_sar_g_pll_sel_START    (0)
#define ABB_SAR_PLL_SEL_sar_g_pll_sel_END      (1)
#define ABB_SAR_PLL_SEL_sar_wtl_pll_sel_START  (2)
#define ABB_SAR_PLL_SEL_sar_wtl_pll_sel_END    (2)
#define ABB_SAR_PLL_SEL_sar_c1_pll_sel_START   (3)
#define ABB_SAR_PLL_SEL_sar_c1_pll_sel_END     (3)


/*****************************************************************************
 �ṹ��    : ABB_SAR_I_COEF1_UNION
 �ṹ˵��  : sar_i_coef1 �Ĵ����ṹ���塣��ַƫ����:0x687����ֵ:0xC1�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sar_i_c1     : 7;  /* bit[0-6]: SARͨ��I·�����˲���ϵ��C1,�з����� */
        unsigned long  sar_i_c3_msb : 1;  /* bit[7]  : SARͨ��I·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_SAR_I_COEF1_UNION;
#define ABB_SAR_I_COEF1_sar_i_c1_START      (0)
#define ABB_SAR_I_COEF1_sar_i_c1_END        (6)
#define ABB_SAR_I_COEF1_sar_i_c3_msb_START  (7)
#define ABB_SAR_I_COEF1_sar_i_c3_msb_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_SAR_I_COEF3_UNION
 �ṹ˵��  : sar_i_coef3 �Ĵ����ṹ���塣��ַƫ����:0x689����ֵ:0x41�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sar_i_c5 : 7;  /* bit[0-6]: SARͨ��I·�����˲���ϵ��C5,�з����� */
        unsigned long  reserved : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_SAR_I_COEF3_UNION;
#define ABB_SAR_I_COEF3_sar_i_c5_START  (0)
#define ABB_SAR_I_COEF3_sar_i_c5_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_SAR_Q_COEF1_UNION
 �ṹ˵��  : sar_q_coef1 �Ĵ����ṹ���塣��ַƫ����:0x68C����ֵ:0xC1�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sar_q_c1     : 7;  /* bit[0-6]: SARͨ��Q·�����˲���ϵ��C1,�з����� */
        unsigned long  sar_q_c3_msb : 1;  /* bit[7]  : SARͨ��Q·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_SAR_Q_COEF1_UNION;
#define ABB_SAR_Q_COEF1_sar_q_c1_START      (0)
#define ABB_SAR_Q_COEF1_sar_q_c1_END        (6)
#define ABB_SAR_Q_COEF1_sar_q_c3_msb_START  (7)
#define ABB_SAR_Q_COEF1_sar_q_c3_msb_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_SAR_Q_COEF3_UNION
 �ṹ˵��  : sar_q_coef3 �Ĵ����ṹ���塣��ַƫ����:0x68E����ֵ:0x41�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sar_q_c5 : 7;  /* bit[0-6]: SARͨ��Q·�����˲���ϵ��C5,�з����� */
        unsigned long  reserved : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_SAR_Q_COEF3_UNION;
#define ABB_SAR_Q_COEF3_sar_q_c5_START  (0)
#define ABB_SAR_Q_COEF3_sar_q_c5_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_SARI_HB_GAIN_2_UNION
 �ṹ˵��  : SARI_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x691����ֵ:0x02�����:8
 �Ĵ���˵��: CH0ͨ��SAR HB�˲������档
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sari_hb_gain_h : 2;  /* bit[0-1]: CH0ͨ��SAR I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512�� */
        unsigned long  reserved       : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_SARI_HB_GAIN_2_UNION;
#define ABB_SARI_HB_GAIN_2_sari_hb_gain_h_START  (0)
#define ABB_SARI_HB_GAIN_2_sari_hb_gain_h_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_SARQ_HB_GAIN_2_UNION
 �ṹ˵��  : SARQ_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x693����ֵ:0x02�����:8
 �Ĵ���˵��: CH0ͨ��SAR HB�˲������档
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sarq_hb_gain_h : 2;  /* bit[0-1]: CH0ͨ��SAR Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512�� */
        unsigned long  reserved       : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt  : 24; /* bit[8-31] */
    } reg;
} ABB_SARQ_HB_GAIN_2_UNION;
#define ABB_SARQ_HB_GAIN_2_sarq_hb_gain_h_START  (0)
#define ABB_SARQ_HB_GAIN_2_sarq_hb_gain_h_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_SAR_CTRL_UNION
 �ṹ˵��  : sar_ctrl �Ĵ����ṹ���塣��ַƫ����:0x694����ֵ:0x03�����:8
 �Ĵ���˵��: ͨ�����ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sar_loop_out : 1;  /* bit[0]  : CH0ͨ��SAR������������źţ�0�����ز�����źţ�1������ͬʱ����źţ� */
        unsigned long  reserved_0   : 1;  /* bit[1]  : ���� */
        unsigned long  reserved_1   : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_SAR_CTRL_UNION;
#define ABB_SAR_CTRL_sar_loop_out_START  (0)
#define ABB_SAR_CTRL_sar_loop_out_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_SAR_REG_DEBUG_DIG_UNION
 �ṹ˵��  : sar_reg_debug_dig �Ĵ����ṹ���塣��ַƫ����:0x696����ֵ:0x00�����:8
 �Ĵ���˵��: ���ֵ��ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  sar_div_en_bp      : 1;  /* bit[0]  : RX��Ƶ��ʹ��bypass����
                                                             0����bypass
                                                             1��bypass */
        unsigned long  reserved           : 3;  /* bit[1-3]: ���� */
        unsigned long  sar_sw_rst_num_cfg : 3;  /* bit[4-6]: ģʽ�л���λ��������ֵ����λΪ8 cycles */
        unsigned long  sar_sw_rst_num_sel : 1;  /* bit[7]  : bit[7]��ģʽ�л���λ��������ʹ��
                                                             0����ʹ��
                                                             1��ʹ�� */
        unsigned long  reserved_butt      : 24; /* bit[8-31] */
    } reg;
} ABB_SAR_REG_DEBUG_DIG_UNION;
#define ABB_SAR_REG_DEBUG_DIG_sar_div_en_bp_START       (0)
#define ABB_SAR_REG_DEBUG_DIG_sar_div_en_bp_END         (0)
#define ABB_SAR_REG_DEBUG_DIG_sar_sw_rst_num_cfg_START  (4)
#define ABB_SAR_REG_DEBUG_DIG_sar_sw_rst_num_cfg_END    (6)
#define ABB_SAR_REG_DEBUG_DIG_sar_sw_rst_num_sel_START  (7)
#define ABB_SAR_REG_DEBUG_DIG_sar_sw_rst_num_sel_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_N50M_DIG_1_UNION
 �ṹ˵��  : n50m_dig_1 �Ĵ����ṹ���塣��ַƫ����:0x6B0����ֵ:0x00�����:8
 �Ĵ���˵��: RX IDLEģʽ���üĴ���1�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50m_comp_sel_b0 : 1;  /* bit[0]  : {n50m_comp_sel_b1,n50m_comp_sel_b0}��ɲ����˲���ϵ��ѡ��RXͨ�������˲��������̶�ϵ��ѡ��
                                                           00���̶�ϵ��1��
                                                           01���̶�ϵ��2��
                                                           10���̶�ϵ��3��
                                                           11���̶�ϵ��4�� */
        unsigned long  n50m_comp_fix    : 1;  /* bit[1]  : RXͨ�������˲�������ϵ���̶����ƣ�
                                                           0��ϵ�����̶����ɼĴ�������
                                                           1��ϵ���̶� */
        unsigned long  n50m_hb_bp       : 1;  /* bit[2]  : RXͨ������˲���bypass���ƣ�
                                                           0����bypass����˲���,rxͨ�����data rate ΪRX CIC rate/2(Ĭ��)
                                                           1��bypass����˲���,rxͨ�����data rate ΪRX CIC rate */
        unsigned long  reserved         : 2;  /* bit[3-4]: ���� */
        unsigned long  n50m_mode        : 3;  /* bit[5-7]: RXͨ��ģʽ���ƣ�
                                                           000��2G_A(Ĭ��)
                                                           001��3G_SC/TDS_B/4G_C
                                                           010��4G
                                                           011��3G_DC/4G_B
                                                           100��TDS
                                                           101��CDMA
                                                           110��CA
                                                           111��2G_B */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_N50M_DIG_1_UNION;
#define ABB_N50M_DIG_1_n50m_comp_sel_b0_START  (0)
#define ABB_N50M_DIG_1_n50m_comp_sel_b0_END    (0)
#define ABB_N50M_DIG_1_n50m_comp_fix_START     (1)
#define ABB_N50M_DIG_1_n50m_comp_fix_END       (1)
#define ABB_N50M_DIG_1_n50m_hb_bp_START        (2)
#define ABB_N50M_DIG_1_n50m_hb_bp_END          (2)
#define ABB_N50M_DIG_1_n50m_mode_START         (5)
#define ABB_N50M_DIG_1_n50m_mode_END           (7)


/*****************************************************************************
 �ṹ��    : ABB_N50M_DIG_2_UNION
 �ṹ˵��  : n50m_dig_2 �Ĵ����ṹ���塣��ַƫ����:0x6B1����ֵ:0x12�����:8
 �Ĵ���˵��: RX IDLEģʽ���üĴ���2�����߿ؾ����Ƿ������á�
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50m_en          : 1;  /* bit[0]  : N50Mͨ��CLOCK GATING���ƣ�
                                                           0����CLOCK GATING
                                                           1��CLOCK GATING(Ĭ��)
                                                           (!n50m_pd)|XX_N50M_EN = 1ʱ����������ر� */
        unsigned long  reserved_0       : 1;  /* bit[1]  : ���� */
        unsigned long  n50m_gain_sel    : 2;  /* bit[2-3]: RXͨ����������ѡ��
                                                           00��gainΪ0.5(Ĭ��)
                                                           01��gainΪ0.75
                                                           10��gainΪ0.85
                                                           11��Reserved */
        unsigned long  n50m_comp_bp     : 1;  /* bit[4]  : RXͨ�������˲���bypass���ƣ�
                                                           0����bypass(Ĭ��)
                                                           1��bypass */
        unsigned long  n50m_clk_inv     : 1;  /* bit[5]  : RXͨ����·ʱ��N50M_CLK����ʹ�ܣ�
                                                           0������
                                                           1������ */
        unsigned long  reserved_1       : 1;  /* bit[6]  : ���� */
        unsigned long  n50m_comp_sel_b1 : 1;  /* bit[7]  : {n50m_comp_sel_b1,n50m_comp_sel_b0}��ɲ����˲���ϵ��ѡ�񣬲ο�n50m_comp_sel_b0˵���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_N50M_DIG_2_UNION;
#define ABB_N50M_DIG_2_n50m_en_START           (0)
#define ABB_N50M_DIG_2_n50m_en_END             (0)
#define ABB_N50M_DIG_2_n50m_gain_sel_START     (2)
#define ABB_N50M_DIG_2_n50m_gain_sel_END       (3)
#define ABB_N50M_DIG_2_n50m_comp_bp_START      (4)
#define ABB_N50M_DIG_2_n50m_comp_bp_END        (4)
#define ABB_N50M_DIG_2_n50m_clk_inv_START      (5)
#define ABB_N50M_DIG_2_n50m_clk_inv_END        (5)
#define ABB_N50M_DIG_2_n50m_comp_sel_b1_START  (7)
#define ABB_N50M_DIG_2_n50m_comp_sel_b1_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_N50M_TESTMODE_UNION
 �ṹ˵��  : N50M_TESTMODE �Ĵ����ṹ���塣��ַƫ����:0x6B2����ֵ:0x00�����:8
 �Ĵ���˵��: ����ģʽ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50m_sw_rst      : 1;  /* bit[0]  : ���ֲ���RXͨ����λ�źţ�
                                                           0������λ(Ĭ��)
                                                           1����λ */
        unsigned long  n50m_cic_gate_en : 1;  /* bit[1]  :  */
        unsigned long  reserved         : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_N50M_TESTMODE_UNION;
#define ABB_N50M_TESTMODE_n50m_sw_rst_START       (0)
#define ABB_N50M_TESTMODE_n50m_sw_rst_END         (0)
#define ABB_N50M_TESTMODE_n50m_cic_gate_en_START  (1)
#define ABB_N50M_TESTMODE_n50m_cic_gate_en_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_N50M_PLL_SEL_UNION
 �ṹ˵��  : N50M_PLL_SEL �Ĵ����ṹ���塣��ַƫ����:0x6B3����ֵ:0x00�����:8
 �Ĵ���˵��: PLLѡ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50m_g_pll_sel   : 2;  /* bit[0-1]:  */
        unsigned long  n50m_wtl_pll_sel : 1;  /* bit[2]  :  */
        unsigned long  n50m_c1_pll_sel  : 1;  /* bit[3]  :  */
        unsigned long  reserved         : 4;  /* bit[4-7]: ���� */
        unsigned long  reserved_butt    : 24; /* bit[8-31] */
    } reg;
} ABB_N50M_PLL_SEL_UNION;
#define ABB_N50M_PLL_SEL_n50m_g_pll_sel_START    (0)
#define ABB_N50M_PLL_SEL_n50m_g_pll_sel_END      (1)
#define ABB_N50M_PLL_SEL_n50m_wtl_pll_sel_START  (2)
#define ABB_N50M_PLL_SEL_n50m_wtl_pll_sel_END    (2)
#define ABB_N50M_PLL_SEL_n50m_c1_pll_sel_START   (3)
#define ABB_N50M_PLL_SEL_n50m_c1_pll_sel_END     (3)


/*****************************************************************************
 �ṹ��    : ABB_N50M_I_COEF1_UNION
 �ṹ˵��  : n50m_i_coef1 �Ĵ����ṹ���塣��ַƫ����:0x6B7����ֵ:0xC1�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50m_i_c1     : 7;  /* bit[0-6]: N50Mͨ��I·�����˲���ϵ��C1,�з����� */
        unsigned long  n50m_i_c3_msb : 1;  /* bit[7]  : N50Mͨ��I·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_N50M_I_COEF1_UNION;
#define ABB_N50M_I_COEF1_n50m_i_c1_START      (0)
#define ABB_N50M_I_COEF1_n50m_i_c1_END        (6)
#define ABB_N50M_I_COEF1_n50m_i_c3_msb_START  (7)
#define ABB_N50M_I_COEF1_n50m_i_c3_msb_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_N50M_I_COEF3_UNION
 �ṹ˵��  : n50m_i_coef3 �Ĵ����ṹ���塣��ַƫ����:0x6B9����ֵ:0x41�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50m_i_c5 : 7;  /* bit[0-6]: N50Mͨ��I·�����˲���ϵ��C5,�з����� */
        unsigned long  reserved  : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_N50M_I_COEF3_UNION;
#define ABB_N50M_I_COEF3_n50m_i_c5_START  (0)
#define ABB_N50M_I_COEF3_n50m_i_c5_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_N50M_Q_COEF1_UNION
 �ṹ˵��  : n50m_q_coef1 �Ĵ����ṹ���塣��ַƫ����:0x6BC����ֵ:0xC1�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50m_q_c1     : 7;  /* bit[0-6]: N50Mͨ��Q·�����˲���ϵ��C1,�з����� */
        unsigned long  n50m_q_c3_msb : 1;  /* bit[7]  : N50Mͨ��Q·�����˲���ϵ��C3,�޷�����,���λ */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_N50M_Q_COEF1_UNION;
#define ABB_N50M_Q_COEF1_n50m_q_c1_START      (0)
#define ABB_N50M_Q_COEF1_n50m_q_c1_END        (6)
#define ABB_N50M_Q_COEF1_n50m_q_c3_msb_START  (7)
#define ABB_N50M_Q_COEF1_n50m_q_c3_msb_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_N50M_Q_COEF3_UNION
 �ṹ˵��  : n50m_q_coef3 �Ĵ����ṹ���塣��ַƫ����:0x6BE����ֵ:0x41�����:8
 �Ĵ���˵��: RXͨ������ϵ���Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50m_q_c5 : 7;  /* bit[0-6]: N50Mͨ��Q·�����˲���ϵ��C5,�з����� */
        unsigned long  reserved  : 1;  /* bit[7]  : ���� */
        unsigned long  reserved_butt: 24; /* bit[8-31] */
    } reg;
} ABB_N50M_Q_COEF3_UNION;
#define ABB_N50M_Q_COEF3_n50m_q_c5_START  (0)
#define ABB_N50M_Q_COEF3_n50m_q_c5_END    (6)


/*****************************************************************************
 �ṹ��    : ABB_N50MI_HB_GAIN_2_UNION
 �ṹ˵��  : N50MI_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x6C1����ֵ:0x02�����:8
 �Ĵ���˵��: CH0ͨ��N50M HB�˲������档
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50mi_hb_gain_h : 2;  /* bit[0-1]: CH0ͨ��N50M I· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512�� */
        unsigned long  reserved        : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_N50MI_HB_GAIN_2_UNION;
#define ABB_N50MI_HB_GAIN_2_n50mi_hb_gain_h_START  (0)
#define ABB_N50MI_HB_GAIN_2_n50mi_hb_gain_h_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_N50MQ_HB_GAIN_2_UNION
 �ṹ˵��  : N50MQ_HB_GAIN_2 �Ĵ����ṹ���塣��ַƫ����:0x6C3����ֵ:0x02�����:8
 �Ĵ���˵��: CH0ͨ��N50M HB�˲������档
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50mq_hb_gain_h : 2;  /* bit[0-1]: CH0ͨ��N50M Q· HB�˲������棨10u���ĸ�2bit������Ĭ��ֵ512�� */
        unsigned long  reserved        : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt   : 24; /* bit[8-31] */
    } reg;
} ABB_N50MQ_HB_GAIN_2_UNION;
#define ABB_N50MQ_HB_GAIN_2_n50mq_hb_gain_h_START  (0)
#define ABB_N50MQ_HB_GAIN_2_n50mq_hb_gain_h_END    (1)


/*****************************************************************************
 �ṹ��    : ABB_N50M_CTRL_UNION
 �ṹ˵��  : n50m_ctrl �Ĵ����ṹ���塣��ַƫ����:0x6C4����ֵ:0x03�����:8
 �Ĵ���˵��: ͨ�����ƼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50m_loop_out : 1;  /* bit[0]  : CH0ͨ��N50M������������źţ�0�����ز�����źţ�1������ͬʱ����źţ� */
        unsigned long  reserved_0    : 1;  /* bit[1]  : ���� */
        unsigned long  reserved_1    : 6;  /* bit[2-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_N50M_CTRL_UNION;
#define ABB_N50M_CTRL_n50m_loop_out_START  (0)
#define ABB_N50M_CTRL_n50m_loop_out_END    (0)


/*****************************************************************************
 �ṹ��    : ABB_N50M_REG_DEBUG_DIG_UNION
 �ṹ˵��  : n50m_reg_debug_dig �Ĵ����ṹ���塣��ַƫ����:0x6C6����ֵ:0x00�����:8
 �Ĵ���˵��: ���ֵ��ԼĴ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  n50m_div_en_bp      : 1;  /* bit[0]  : RX��Ƶ��ʹ��bypass����
                                                              0����bypass
                                                              1��bypass */
        unsigned long  reserved            : 3;  /* bit[1-3]: ���� */
        unsigned long  n50m_sw_rst_num_cfg : 3;  /* bit[4-6]: ģʽ�л���λ��������ֵ����λΪ8 cycles */
        unsigned long  n50m_sw_rst_num_sel : 1;  /* bit[7]  : bit[7]��ģʽ�л���λ��������ʹ��
                                                              0����ʹ��
                                                              1��ʹ�� */
        unsigned long  reserved_butt       : 24; /* bit[8-31] */
    } reg;
} ABB_N50M_REG_DEBUG_DIG_UNION;
#define ABB_N50M_REG_DEBUG_DIG_n50m_div_en_bp_START       (0)
#define ABB_N50M_REG_DEBUG_DIG_n50m_div_en_bp_END         (0)
#define ABB_N50M_REG_DEBUG_DIG_n50m_sw_rst_num_cfg_START  (4)
#define ABB_N50M_REG_DEBUG_DIG_n50m_sw_rst_num_cfg_END    (6)
#define ABB_N50M_REG_DEBUG_DIG_n50m_sw_rst_num_sel_START  (7)
#define ABB_N50M_REG_DEBUG_DIG_n50m_sw_rst_num_sel_END    (7)


/*****************************************************************************
 �ṹ��    : ABB_ANA_COMMON_WR20_UNION
 �ṹ˵��  : ANA_COMMON_WR20 �Ĵ����ṹ���塣��ַƫ����:0x814����ֵ:0x1F�����:8
 �Ĵ���˵��: ģ��common��д�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  TX_AUTO_TUNE  : 1;  /* bit[0]  :  */
        unsigned long  RX_AUTO_TUNE  : 1;  /* bit[1]  :  */
        unsigned long  ET_AUTO_TUNE  : 1;  /* bit[2]  :  */
        unsigned long  CH3_AUTO_TUNE : 1;  /* bit[3]  :  */
        unsigned long  TUNING_VAL_EN : 1;  /* bit[4]  :  */
        unsigned long  reserved      : 3;  /* bit[5-7]: ���� */
        unsigned long  reserved_butt : 24; /* bit[8-31] */
    } reg;
} ABB_ANA_COMMON_WR20_UNION;
#define ABB_ANA_COMMON_WR20_TX_AUTO_TUNE_START   (0)
#define ABB_ANA_COMMON_WR20_TX_AUTO_TUNE_END     (0)
#define ABB_ANA_COMMON_WR20_RX_AUTO_TUNE_START   (1)
#define ABB_ANA_COMMON_WR20_RX_AUTO_TUNE_END     (1)
#define ABB_ANA_COMMON_WR20_ET_AUTO_TUNE_START   (2)
#define ABB_ANA_COMMON_WR20_ET_AUTO_TUNE_END     (2)
#define ABB_ANA_COMMON_WR20_CH3_AUTO_TUNE_START  (3)
#define ABB_ANA_COMMON_WR20_CH3_AUTO_TUNE_END    (3)
#define ABB_ANA_COMMON_WR20_TUNING_VAL_EN_START  (4)
#define ABB_ANA_COMMON_WR20_TUNING_VAL_EN_END    (4)

/*****************************************************************************
 �ṹ��    : ABB_CH0_LINE_RPT1_UNION
 �ṹ˵��  : CH0_LINE_RPT1 �Ĵ����ṹ���塣��ַƫ����:0x254����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rx_line_ctrl_mode_rpt : 3;  /* bit[0-2]: �߿��ź�LINE_CTRL_MODE״̬�ϱ�
                                                                    0��IDLE
                                                                    1��Gģ
                                                                    2��Wģ
                                                                    3��LTEģ
                                                                    4��TDSģ
                                                                    5��Xģ
                                                                    others��IDLE */
        unsigned long  ch0_reserved_1            : 1;  /* bit[3]  : Reserved */
        unsigned long  ch0_rxa_blk_en_rpt        : 1;  /* bit[4]  : RXA_BLK_EN�߿�״̬�ϱ� */
        unsigned long  ch0_rxb_blk_en_rpt        : 1;  /* bit[5]  : RXB_BLK_EN�߿�״̬�ϱ� */
        unsigned long  ch0_reserved_0            : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_LINE_RPT1_UNION;

/*****************************************************************************
 �ṹ��    : ABB_CH1_LINE_RPT1_UNION
 �ṹ˵��  : CH1_LINE_RPT1 �Ĵ����ṹ���塣��ַƫ����:0x454����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rx_line_ctrl_mode_rpt : 3;  /* bit[0-2]: �߿��ź�LINE_CTRL_MODE״̬�ϱ�
                                                                    0��IDLE
                                                                    1��Gģ
                                                                    2��Wģ
                                                                    3��LTEģ
                                                                    4��TDSģ
                                                                    5��Xģ
                                                                    others��IDLE */
        unsigned long  ch1_reserved_1            : 1;  /* bit[3]  : Reserved */
        unsigned long  ch1_rxa_blk_en_rpt        : 1;  /* bit[4]  : RXA_BLK_EN�߿�״̬�ϱ� */
        unsigned long  ch1_rxb_blk_en_rpt        : 1;  /* bit[5]  : RXB_BLK_EN�߿�״̬�ϱ� */
        unsigned long  ch1_reserved_0            : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_LINE_RPT1_UNION;

/*****************************************************************************
 �ṹ��    : ABB_CH0_LINE_RPT0_UNION
 �ṹ˵��  : CH0_LINE_RPT0 �Ĵ����ṹ���塣��ַƫ����:0x253����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch0_rxa_en_rpt            : 1;  /* bit[0]  : RXA_EN�߿�״̬�ϱ� */
        unsigned long  ch0_rxb_en_rpt            : 1;  /* bit[1]  : RXB_EN�߿�״̬�ϱ� */
        unsigned long  ch0_tx_en_rpt             : 1;  /* bit[2]  : TX_EN�߿�״̬�ϱ� */
        unsigned long  ch0_tx_line_ctrl_mode_rpt : 3;  /* bit[3-5]: �߿��ź�LINE_CTRL_MODE״̬�ϱ�
                                                                    0��IDLE
                                                                    1��Gģ
                                                                    2��Wģ
                                                                    3��LTEģ
                                                                    4��TDSģ
                                                                    5��Xģ
                                                                    others��IDLE */
        unsigned long  ch0_reserved              : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH0_LINE_RPT0_UNION;

/*****************************************************************************
 �ṹ��    : ABB_CH1_LINE_RPT0_UNION
 �ṹ˵��  : CH1_LINE_RPT0 �Ĵ����ṹ���塣��ַƫ����:0x453����ֵ:0x00�����:8
 �Ĵ���˵��: �߿�״̬�ϱ��Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned long      uwValue;
    struct
    {
        unsigned long  ch1_rxa_en_rpt            : 1;  /* bit[0]  : RXA_EN�߿�״̬�ϱ� */
        unsigned long  ch1_rxb_en_rpt            : 1;  /* bit[1]  : RXB_EN�߿�״̬�ϱ� */
        unsigned long  ch1_tx_en_rpt             : 1;  /* bit[2]  : TX_EN�߿�״̬�ϱ� */
        unsigned long  ch1_tx_line_ctrl_mode_rpt : 3;  /* bit[3-5]: �߿��ź�LINE_CTRL_MODE״̬�ϱ�
                                                                    0��IDLE
                                                                    1��Gģ
                                                                    2��Wģ
                                                                    3��LTEģ
                                                                    4��TDSģ
                                                                    5��Xģ
                                                                    others��IDLE */
        unsigned long  ch1_reserved              : 2;  /* bit[6-7]: Reserved */
        unsigned long  reserved_butt             : 24; /* bit[8-31] */
    } reg;
} ABB_CH1_LINE_RPT0_UNION;


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
