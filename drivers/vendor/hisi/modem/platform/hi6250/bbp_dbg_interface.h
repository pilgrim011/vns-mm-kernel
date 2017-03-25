/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : bbp_dbg_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-12-04 13:44:10
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��12��4��
    ��    ��   : l00356384
    �޸�����   : �ӡ�bbp_dbg.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "soc_baseaddr_interface.h"

#ifndef __BBP_DBG_INTERFACE_H__
#define __BBP_DBG_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/***======================================================================***
                     (1/1) register_define_BBP_DBG
 ***======================================================================***/
/* �Ĵ���˵������λ�Ĵ���
 bit[31:8]   dbgģ��汾�š�
             �ɷ���ʱ���ʾ��bit31~24��ʾ�꣬bit23~16��ʾ�£�bit15~8��ʾ�ա���2012��5��20�հ汾���汾��Ϊ��0x120520
 bit[7:2]    ������
 bit[1]      sdrģ����λ�źš���λSDRͨ·�߼���·������dbg_reg��
             1����ʾ��λ
             0����ʾ�帴λ
 bit[0]      dbgģ����λ�źš���λDBG��tl_dbgģ��
             1����ʾ��λ
             0����ʾ�帴λ
   UNION�ṹ:  DBG_DBG_SRST_UNION */
#define DBG_DBG_SRST_ADDR                             (SOC_BBP_DBG_BASE_ADDR + 0x4000)

/* �Ĵ���˵����ʱ���ſؼĴ���
 bit[31:13]  ������
 bit[12]     ģ��RAMʱ���ſ�ѡ���źš�
             0��ʱ���ſ���Ч���ſؿ�����(ȱʡֵ)����
             1��ʱ���ſ���Ч���ſعرա�������������������������������
 bit[11:8]   Service ID��GUX SSID��Ϣ������Ϣ��
             ����ֵΪ��0xB
 bit[7:5]    ������
 bit[4]      Bus���ݵ�DMAͨ�������IDѡ��
             0��Bus���ݵ�DMAͨ��ID���֣�ID=F8��(ȱʡֵ)����
             1��Bus���ݱ��ΪDMA��Dataͨ��IDѡ��ID=0xF9��������������������������������
 bit[3:0]    DBG���ݵ�DMAͨ��8λIDֵ�ĸ�4λIDָʾ��
             DBGȱʡֵ=4'hF��
             Bus����ID=0xF8��
             Dat����ID=0xF9��
             Log����ID=0xFA��
   UNION�ṹ:  DBG_DBG_GATE_UNION */
#define DBG_DBG_GATE_ADDR                             (SOC_BBP_DBG_BASE_ADDR + 0x4004)

/* �Ĵ���˵����HDLC��ϱ�ʶ�Ĵ���
   ��      ����������ݱ�־��Ϣ��
               ����ֵΪ��0x48495349����ʾΪ��"HISI"
   UNION�ṹ ���� */
#define DBG_DBG_DIAG_ID_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4008)

/* �Ĵ���˵��������֡ͷ���üĴ���
 bit[31:24]  ��Ϣ����������Ϣ��
             ����ֵΪ��0x03
 bit[23:16]  Session ID������Ϣ��
             ����ֵΪ��0x01����������������������
 bit[15:12]  Service ID��LTE SSID��Ϣ������Ϣ��
             ����ֵΪ��0x4
 bit[11:8]   Service ID��TDS SSID��Ϣ������Ϣ��
             ����ֵΪ��0x8
 bit[7:0]    Service ID��SID��Ϣ������Ϣ��
             ����ֵΪ��0x02
   UNION�ṹ:  DBG_DBG_SRV_ID_UNION */
#define DBG_DBG_SRV_ID_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x400C)

/* �Ĵ���˵����DBG BUS ID�Ĵ���
   ��      ����DBG BUS֡ͷ��ID��ʶ��
               ȱʡ����ֵΪ��0x4f008000(�ںϰ汾)
   UNION�ṹ ���� */
#define DBG_DBG_BUS_ID_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x4010)

/* �Ĵ���˵��������֡���ȼĴ���
 bit[31:16]  ��������֡��������Ϣ��
             ����֡��������ϰ�ͷ��Service ID�Ȱ�ͷ��Ϣ����λΪbyte��
             ��ѡ֡������ֵ�У�
             0x0800(2048byte)(ȱʡֵ)��
             0x0200(512byte)��(ֻ֧��ASIC�汾)
             0x0400(1024byte)(ֻ֧��ASIC�汾)
 bit[15:0]   BUS��д����֡��������Ϣ��
             ����֡��������ϰ�ͷ��Service ID�Ȱ�ͷ��Ϣ����λΪbyte��
             ��ѡ֡������ֵ�У�
             0x0800(2048byte)(ȱʡֵ)��
             0x0200(512byte)��
             0x0400(1024byte)��������������������������
   UNION�ṹ:  DBG_DBG_FRM_LEN_UNION */
#define DBG_DBG_FRM_LEN_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4014)

/* �Ĵ���˵����LTE BUS�ɼ�����ѡ��Ĵ���
 bit[31:27]  GSM2ģ���BUS���ݲɼ�ѡ���źš�
             0����ѡ��1��ѡ��
             bit27��gtc_mem��reg_1ģ��(0x88_0000~0x88_1fff)��
             bit28��dec_rpt_mem��apc_mem��tsc_mem��ulcode_data_mem��reg_2ģ��(0x88_2000~0x88_3fff)��
             bit29��reg_3��dldem_mem1��dldem_mem2��dldem_mem3ģ��(0x88_4000~0x88_5fff)��
             bit30��agc_mem1��agc_mem2��gck_memģ��(0x880_6000~0x88_7fff)��
             bit31��fe_ctrl_mem��fe_ctrl��reg_4ģ��(0x88_8000~0x88_ffff)��
 bit[26:23]  GSM1ģ���BUS���ݲɼ�ѡ���źš�
             0����ѡ��1��ѡ��
             bit23��dec_rpt_mem��apc_mem��tsc_mem��ulcode_data_mem��reg_2ģ��(0x80_2000~0x80_3fff)��
             bit24��reg_3��dldem_mem1��dldem_mem2��dldem_mem3ģ��(0x80_4000~0x80_5fff)��
             bit25��agc_mem1��agc_mem2��gck_memģ��(0x80_6000~0x80_7fff)��
             bit26��fe_ctrl_mem��fe_ctrl��reg_4ģ��(0x80_8000~0x80_ffff)��
 bit[22:18]  U1ģ���BUS���ݲɼ�ʹ���źš�
             0����ʹ�ܣ�1��ʹ�ܡ�
             bit18��mp��mp_rpt_mem��cs��cs_rpt_mem��rf_ctrlģ��(0x90_2000~0x90_3fff)��
             bit19��dldem��pcģ��(0x90_4000~0x90_4fff��0x90_6000~0x90_6fff)��
             bit20��ul��ulcode_para_memģ��(0x90_c000~0x90_cfff��0x90_e000~0x90_efff)��
             bit21��lmmse��lmmse_mem��dldec_dpa��dldec_para_mem��dldec_dbg_rpt_mem��dldec_dpa_rpt_headģ��(0x90_8000~0x90_bfff)��
             bit22��dldec_r99_dc��lmmse_dc��lmmse_mem_dc��dldec_dpa_dc��dldec_dbg_rpt_dc_mem��dldec_dpa_rpt_head_dc��ul_dcģ��(0x92_7000~0x92_cfff)��
 bit[17:16]  DBG_BUS��д���������źš�
             0��ʹ��BUS������
             1������BUS������
             bit16:�����������źţ�
             bit17:д���������źš�
 bit[15]     COM(ctu��irm/gu_bbp_mst��et��abb)ģ���BUS���ݲɼ�ѡ���źš�
             0����ѡ��1��ѡ��
             ��ַ��0xf8_0000~0xf8_7fff��0xf8_8000~0xf8_ffff��0xf9_0000~0xf9_7fff��0xfa_0000~0xfa_7fff��
 bit[14]     LTE top(int��stu��crg)ģ���BUS���ݲɼ�ѡ���źš�(0x70_0000~0x7f_ffff)
             0����ѡ��1��ѡ��
 bit[13]     ����(ԭdbgģ��)��
 bit[12]     DMA(sctrl��dbg��dbg_trig��dma)ģ���BUS���ݲɼ�ѡ���źš�
             0����ѡ��1��ѡ��
             ��ַ��0xfc_0000~0xfc_ffff��
 bit[11]     GSM1ģ���BUS���ݲɼ�ѡ���ź�(ԭGSMģʽ)��
             0����ʹ�ܣ�1��ʹ�ܡ�
             gtc_mem��reg_1ģ��(0x80_0000~0x80_1fff)��
 bit[10]     U1ģ���BUS���ݲɼ�ʹ���ź�(ԭUMSTģʽ)��
             0����ѡ��1��ѡ��
             cm_timing��ck_mem��drx_2msģ��(0x90_1000~0x90_1fff)��
 bit[9:8]    ������
 bit[7]      LTE tdlģ���BUS���ݲɼ�ѡ���źš�(0xc0_0000~0xcf_ffff)
             0����ѡ��1��ѡ��
 bit[6]      LTE pduģ���BUS���ݲɼ�ѡ���źš�(0xb0_0000~0xbf_ffff)
             0����ѡ��1��ѡ��
 bit[5]      LTE vdlģ���BUS����ѡ���źš�(0x50_0000~0x5f_ffff)
             0����ѡ��1��ѡ��
 bit[4]      LTE cqiģ���BUS����ѡ���źš�(0xa0_0000~0xaf_ffff)
             0����ѡ��1��ѡ��
 bit[3]      LTE ulģ���BUS����ѡ���źš�(0x60_0000~0x6f_ffff)
             0����ѡ��1��ѡ��
 bit[2]      LTE fpuģ���BUS����ѡ���źš�(0x10_0000~0x1f_ffff)
             0����ѡ��1��ѡ��
 bit[1]      LTE rfinģ���BUS����ѡ���źš�(0x00_0000~0x0f_ffff)
             0����ѡ��1��ѡ��
 bit[0]      LTE pbģ���BUS����ѡ���źš�(0x40_0000~0x4f_ffff)
             0����ѡ��1��ѡ��
   UNION�ṹ:  DBG_LTE_BUS_SEL_UNION */
#define DBG_LTE_BUS_SEL_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4018)

/* �Ĵ���˵����TDS BUS�ɼ�����ѡ��Ĵ���
 bit[31:26]  C2ģ���BUS���ݲɼ�ѡ���źš�
             0����ѡ��
             1��ѡ��
             bit26��glbģ��(0x2e_0000~0x2e_0fff)��
             bit27��timing_intģ��(0x2e_1000~0x2e_1fff)��
             bit28��mps_csģ��(0x2e_2000~0x2e_2fff)��
             bit29��dldecģ��(0x2e_4000~0x2e_4fff)��
             bit30��ulcodeģ��(0x2e_b000~0x2e_bfff)��
             bit31��fe_ctrl��ssi_mem��mipi_mem��gpio_mem��hkadc_memģ��(0x2e_f000~0x2e_ffff)��
 bit[25]     WTC2 FEģ���BUS���ݲɼ�ѡ���źš�
             0����ѡ��
             1��ѡ��
             ����ģ�飺
             dl_fe��dl_fe_dc��dl_fe_mctrl��wc_dump��wc_dump_mem��ul_fe_mem��w_pa_pd��w_pa_pd_mem��ul_fe(0x0x29_0000~0x29_ffff)��
 bit[24]     WTC2 COMģ���BUS���ݲɼ�ѡ���źš�
             0����ѡ��
             1��ѡ��
             ����ģ�飺
             int��fe_ctrl_mem��fe_ctrl(0x0x20_0000~0x20_0fff)��
             dldec_r99_para_mem��dldec_r99_reg1��dldec_r99_vtb_head��dldec_r99_vtb_rpt_mem��dldec_r99_turbo_head��dldec_r99_turbo_rpt_mem��dldec_r99_reg2(0x20_7000~0x20_7fff)��
 bit[23:22]  ������
 bit[21:16]  C1ģ���BUS���ݲɼ�ѡ���źš�
             0����ѡ��
             1��ѡ��
             bit16��glbģ��(0x9e_0000~0x9e_0fff)��
             bit17��timing_intģ��(0x9e_1000~0x9e_1fff)��
             bit18��mps_csģ��(0x9e_2000~0x9e_2fff)��
             bit19��dldecģ��(0x9e_4000~0x9e_4fff)��
             bit20��ulcodeģ��(0x9e_b000~0x9e_bfff)��
             bit21��fe_ctrl��ssi_mem��mipi_mem��gpio_mem��hkadc_memģ��(0x9e_f000~0x9e_ffff)��
 bit[15:12]  U2ģ���BUS���ݲɼ�ʹ���źš�
             0����ʹ�ܣ�1��ʹ�ܡ�
             bit12��cm_timing��ck_mem��drx_2msģ��(0x20_1000~0x20_1fff)��
             bit13��mp��mp_rpt_mem��cs��cs_rpt_mem��rf_ctrlģ��(0x20_2000~0x20_3fff)��
             bit14��dldem��pcģ��(0x20_4000~0x20_4fff��0x20_6000~0x20_6fff)��
             bit15��ul��ulcode_para_memģ��(0x20_c000~0x20_cfff��0x20_e000~0x20_efff)��
 bit[11]     ������
 bit[10:0]   TDS ģ���BUS���ݲɼ�ѡ���źš�
             0����ѡ��1��ѡ��
             bit0��stuģ���BUS�ɼ�ѡ���źţ�(0xd0_0000~0xd0_3fff)
             bit1��������
             bit2��rfcģ���BUS�ɼ�ѡ���źţ�(0xd0_4000~0xd0_5fff)
             bit3��wtc1_comģ���BUSѡ���ź�(ԭviterbiģ��)��
             int��cpc_drx��fe_ctrl_mem��fe_ctrl(0x0x90_0000~0x90_0fff)��
             dldec_r99_para_mem��dldec_r99_reg1��dldec_r99_vtb_head��dldec_r99_vtb_rpt_mem��dldec_r99_turbo_head��dldec_r99_turbo_rpt_mem��dldec_r99_reg2(0x90_7000~0x90_7fff)��
             bit4��hsupaģ���BUS�ɼ�ѡ���źţ�(0xe1_0000~0xe1_3fff)
             bit5��turboģ���BUS�ɼ�ѡ���źţ�(0xe2_0000~0xe2_7fff)
             bit6��topģ���BUS�ɼ�ѡ���źţ�(0xe2_8000~0xe2_ffff)
             bit7��harq_regģ���BUS�ɼ�ѡ���źţ�(0xe3_0000~0xe3_ffff)
             bit8��wtc1_feģ���BUSѡ���ź�(ԭtds agcd(own)ģ��)��
             dl_fe��dl_fe_dc��dl_fe_mctrl��wc_dump��wc_dump_mem��ul_fe_mem��w_pa_pd��w_pa_pd_mem��ul_fe(0x0x99_0000~0x99_ffff)��
             bit9������(ԭtds agcc(ommon)ģ��)��
             bit10������(ԭtds agcu(p)ģ��)��
   UNION�ṹ:  DBG_TDS_BUS_SEL_UNION */
#define DBG_TDS_BUS_SEL_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x401C)

/* �Ĵ���˵����BUS����ʹ�ܼĴ���
 bit[31:1]   ������
 bit[0]      BUS���ݲ���ʹ���źš�
             0����ʹ�ܣ�
             1��ʹ�ܡ�
   UNION�ṹ:  DBG_DBG_BUS_EN_UNION */
#define DBG_DBG_BUS_EN_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x4020)

/* �Ĵ���˵����DATͨ��ѡ��Ĵ���
 bit[31:10]  ������
 bit[9:8]    ABB ch0/1ͨ��ѡ���źţ���ABB����ʹ�����ʹ�á�
             0��ѡ��ch1ͨ����
             1��ѡ��ch0ͨ����
             2��ѡ��ch0/1ͨ���Ĳ���CA��ABB����ѡ����������
 bit[7]      ������
 bit[6:4]    TDS��������ѡ��Ĵ�����
             ��DAT ID��ַ���ʹ�á�
             1����������0���ݲɼ���      ID=0x41000801��
             2����������1���ݲɼ���      ID=0x41000802��
             3������˫�������ݲɼ���     ID=0x41000803��
             4���������ݲɼ�����         ID=0x41000804��
             5������+��������0���ݲɼ��� ID=0x41000805��
             6������+��������1���ݲɼ��� ID=0x41000806��
             7������+����˫�������ݲɼ���ID=0x41000807��
             ������������
 bit[3:0]    DBGģ���ϱ�dat��������ѡ��
             0��RFIN�ϱ���dat����(ȱʡֵ)
             1��FPU�ϱ���dat����
             2��CQI�ϱ���dat����
             3��PDU�ϱ���dat����
             4��TDS�ϱ���dat����
             5��ABB�ϱ�����ͨ��dat����(��֧��FPGA�汾)
             6��ABB�ϱ�����ͨ��dat����(��֧��FPGA�汾)
             7��ABB�ϱ�ģ��ͨ��dat����(��֧��FPGA�汾)
             8��BBP COMMON�ϱ���dat����
             15~9������
   UNION�ṹ:  DBG_DBG_DAT_SEL_UNION */
#define DBG_DBG_DAT_SEL_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4024)

/* �Ĵ���˵����DAT����ʹ�ܼĴ���
 bit[31:1]   ������
 bit[0]      DAT���ݲ���ʹ���źš�
             0����ʹ�ܣ�
             1��ʹ�ܡ�
   UNION�ṹ:  DBG_DBG_DAT_EN_UNION */
#define DBG_DBG_DAT_EN_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x4028)

/* �Ĵ���˵����LOGͨ��ѡ��Ĵ���
 bit[31:3]   ������
 bit[2:0]    DBGģ���ϱ�LOG��������ѡ��
             0������(ȱʡֵ)
             1��FPU�ϱ���log����
             2��PB�ϱ���log����
             3��PDU�ϱ���log����
             4��TDL�ϱ���log����
             5��TDL2�ϱ���log����
             7~6��������������������
   UNION�ṹ:  DBG_DBG_LOG_SEL_UNION */
#define DBG_DBG_LOG_SEL_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x402C)

/* �Ĵ���˵����LOGͨ��ʹ�ܼĴ���
 bit[31:1]   ������
 bit[0]      LģLOG���ݴ���ʹ���źš�
             0����ʹ�ܣ�
             1��ʹ�ܡ�
   UNION�ṹ:  DBG_DBG_LOG_EN_UNION */
#define DBG_DBG_LOG_EN_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x4030)

/* �Ĵ���˵����DBG����ͨ��ģʽѡ��Ĵ���
 bit[31:12]  ������
 bit[11:8]   DBG������ģʱ��ѡ���źš�
             0������(ȱʡֵ)
             1��LTE��
             2��TDS��
             3��UMTS(U1)��
             4��EVDO&1X(X1)��
             5��1X(X2)��
             6��R99(U2)��
             7��GSM1��
             8��GSM2��
             9~15������
 bit[7:4]    DBG������ģʱ��ѡ���źš�
             0������(ȱʡֵ)
             1��LTE��
             2��TDS��
             3��UMTS(U1)��
             4��EVDO&1X(X1)��
             5��1X(X2)��
             6��R99(U2)��
             7��GSM1��
             8��GSM2��
             9~15������
 bit[3:0]    ������
   UNION�ṹ:  DBG_DBG_TL_SEL_UNION */
#define DBG_DBG_TL_SEL_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x4034)

/* �Ĵ���˵����DAT/BUS/LOGͨ���澯�Ĵ���
 bit[31:14]  ������
 bit[13:12]  BUSͨ���澯��Ϣ��ֻ������Ӧλд1��0��
             bit13��burst�����ݳ���澯�źţ�
             bit12��ͨ��fifo����澯�źš�
 bit[11:8]   lte��log������澯��Ϣ��ֻ������Ӧλд1��0��
             bit11������֡����С������ֵ���޽�����ʶ�ĸ澯��
             bit10������֡���ݴ�������ֵ�ĸ澯��
             bit9������֡����С������ֵ�ĸ澯��
             bit8��ͨ��fifo����澯�źš�
 bit[7:5]    ������
 bit[4:1]    DATA���ݽӿ�ָʾ��Ϣ��ֻ������Ӧλд1��0
             bit4��dat���ݽ���ָʾ��
             bit3��vld��Чָʾ��
             bit2��eop��Чָʾ��
             bit1��sop��Чָʾ��
 bit[0]      DATA����֡����澯��Ϣ��ֻ������Ӧλд1��0��
             bit0��ͨ��fifo����澯�źš�
   UNION�ṹ:  DBG_DBG_DIAG_ALARM_UNION */
#define DBG_DBG_DIAG_ALARM_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x403C)

/* �Ĵ���˵����BUS��ͨ������֡������
   ��      ����BUS���ݴ���֡��������
               ֻ����32λ��������ͨ��ʹ����0�����������֣�
   UNION�ṹ ���� */
#define DBG_DBG_BUS_CNT_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4040)

/* �Ĵ���˵����DAT����ͨ������֡������
   ��      ����DAT���ݴ���֡��������
               ֻ����32λ��������ͨ��ʹ����0�����������֣�
   UNION�ṹ ���� */
#define DBG_DBG_DAT_CNT_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4044)

/* �Ĵ���˵����LOGͨ������֡������
   ��      ����LOG���ݴ���֡��������
               ֻ����32λ��������ͨ��ʹ����0�����������֣�
   UNION�ṹ ���� */
#define DBG_DBG_LOG_CNT_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4048)

/* �Ĵ���˵����DBG��DMA����/��Ӧ����������
 bit[31:16]  DBG��DMA�ӿڵ�gnt��Ӧ������������
             ֻ����16λ��������Test_switch������Ч���ر���0��
 bit[15:0]   DBG��DMA�ӿڵ�req���������������
             ֻ����16λ��������Test_switch������Ч���ر���0��
   UNION�ṹ:  DBG_DBG_DMA_CNT_UNION */
#define DBG_DBG_DMA_CNT_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4058)

/* �Ĵ���˵����dbg֡��sop������
 bit[31:24]  dat���ݵ�sop������������
             ֻ����8λ����������0x003C��bit1д1��0��
 bit[23:10]  ������
 bit[9:0]    dat_bstģ��fifo���洢���ݸ�����
             ֻ����10λ�����������ݷ�Χ��0~512��
             ��0x003C��bit3д1��0��
   UNION�ṹ:  DBG_DBG_SOP_CNT_UNION */
#define DBG_DBG_SOP_CNT_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x405C)

/* �Ĵ���˵����dbg��ram״̬������
 bit[31:29]  ������
 bit[28]     ָʾDBGͨ��RAMʵʱ�ǿ�״̬��
             0��ramΪ�ա�1��ram�ǿգ�
 bit[27:25]  ������
 bit[24:16]  ָʾDBGͨ��RAM�ﵽ���burst�洢������
             Test_switch������Ч���ر���0��
             9λ�����������ݷ�Χ��0~256��
 bit[15:13]  ������
 bit[12:0]   ָʾDBGͨ��RAM�ﵽ���洢����(64bit)������
             Test_switch������Ч���ر���0��
             13λ�����������ݷ�Χ��0~4096��
   UNION�ṹ:  DBG_DBG_RAM_CNT_UNION */
#define DBG_DBG_RAM_CNT_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4068)

/* �Ĵ���˵����dbgͨ��req����Ӧʱ�������
 bit[31:24]  ������
 bit[23:0]   ָʾDBGͨ��RAM��req/gnt�����ʱ�������
             Test_switch������Ч���ر���0��
             24λ��������ʱ�������ʱ����ء�
   UNION�ṹ:  DBG_DBG_TIME_CNT_UNION */
#define DBG_DBG_TIME_CNT_ADDR                         (SOC_BBP_DBG_BASE_ADDR + 0x406C)

/* �Ĵ���˵����dbg��ͨ��ѡ��Ĵ���
 bit[31:9]   ������
 bit[8]      DBG��BUS��DATAͨ�����洫��ʹ���źš�
             0����������(ȱʡģʽ)��
             1������ʹ�ܡ�
 bit[7:5]    ������
 bit[4]      ��ʱ�����źš�(��֤������)
             0����ʱ��Ϣ�����ɼ��봫�䣻
             1����ʱ��Ϣ�����Σ�ֵ��Ϊ0��
 bit[3:1]    ������
 bit[0]      BUS������ַ��ģʽ��ʹ���źš�
             0����ʹ�ܣ�
             1��ʹ�ܡ�
   UNION�ṹ:  DBG_DBG_GLB_SEL_UNION */
#define DBG_DBG_GLB_SEL_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4090)

/* �Ĵ���˵����bus������ʼ��ַ�Ĵ���
 bit[31:24]  ������
 bit[23:0]   BUS������ַ��ģʽ����ʼ��ַ��ѡ��Χ��0~0xffffff
   UNION�ṹ:  DBG_BUS_ADDR_VALUE_UNION */
#define DBG_BUS_ADDR_VALUE_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x4094)

/* �Ĵ���˵����bus������ַ��Χ�Ĵ���
 bit[31:24]  ������
 bit[23:0]   BUS������ַ��ģʽ��ַ��Χ(��С)��ѡ��Χ��0~0xffffff
   UNION�ṹ:  DBG_BUS_ADDR_SIZE_UNION */
#define DBG_BUS_ADDR_SIZE_ADDR                        (SOC_BBP_DBG_BASE_ADDR + 0x4098)

/* �Ĵ���˵����TDS DAT ID�Ĵ���
   ��      ����TDS DAT ID��ַ��
               ȱʡ����ֵΪ��0x41000800(�ںϰ汾)
   UNION�ṹ ���� */
#define DBG_TDS_DAT_ID_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x40A0)

/* �Ĵ���˵����TDS DAT�ɼ�ģʽѡ��Ĵ���
 bit[31:16]  ����ģʽ��DAT�ɼ�֡������(֧��TDS/ABB)
 bit[15:2]   ������
 bit[1]      TDS/ABB DAT�ɼ�ģʽѡ���źš�
             0������ģʽ�������ֵ���ʹ�ã�
             1������ģʽ��
 bit[0]      ������
   UNION�ṹ:  DBG_TDS_DAT_MODE_UNION */
#define DBG_TDS_DAT_MODE_ADDR                         (SOC_BBP_DBG_BASE_ADDR + 0x40A8)

/* �Ĵ���˵����DAT�������üĴ���
 bit[31:10]  ������
 bit[9:8]    DAT�������������źš�
             Bit8�������滻ģʽ����ʵ��TDS����ģʽ�£���ȷ���Ĳ��������滻DAT�ӿ����ݣ�����ͨ��������ȷ�ԣ�
             Bit9�����ݲ���ģʽ����Ҫ����ΪTDS����ģʽ���ڲ��������ݽ�������ͨ���������ԣ�
             ������Ϣ��1��Ч��
 bit[7:0]    DAT�������ݴ��������źš�
             ��ֵΪʱ�Ӽ��������ֵ=F����ÿ��16cycle���ɼ�����1��64bit���ݣ���ʱ��Ƶ��=150MHz����������ݴ���=600Mbps��
   UNION�ṹ:  DBG_DAT_TEST_UNION */
#define DBG_DAT_TEST_ADDR                             (SOC_BBP_DBG_BASE_ADDR + 0x40AC)

/* �Ĵ���˵����TDS DAT�ӿ�״̬�Ĵ���
 bit[31:7]   ������
 bit[6:4]    TDS DAT�ӿ�����״ָ̬ʾ�źš�
             ֻ������Ӧλд1��0��
             Bit4�����е�������������״ָ̬ʾ��
             Bit5������˫������������״ָ̬ʾ��
             Bit6��������������״ָ̬ʾ��
 bit[3:1]    ������
 bit[0]      TDS DAT�������ô���ָʾ�źš�
             ֻ������Ӧλд1��0��
   UNION�ṹ:  DBG_TDS_DAT_STS_UNION */
#define DBG_TDS_DAT_STS_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x40B0)

/* �Ĵ���˵����DBG BUS�ɼ�ģʽѡ��Ĵ���
 bit[31:16]  ����ģʽ��BUS�ɼ�֡������
 bit[15:2]   ������
 bit[1]      DBG BUS�ɼ�ģʽѡ���źš�
             0������ģʽ�������ֵ���ʹ�ã�
             1������ģʽ��
 bit[0]      ������
   UNION�ṹ:  DBG_DBG_BUS_MODE_UNION */
#define DBG_DBG_BUS_MODE_ADDR                         (SOC_BBP_DBG_BASE_ADDR + 0x40C8)

/* �Ĵ���˵����DBG BUS�������üĴ���
 bit[31:9]   ������
 bit[8]      DBG BUS����ģʽ��BUSͨ����������
             ������Ϣ��1��Ч��
 bit[7:0]    DBG BUS�������ݴ��������źš�
             ��ֵΪʱ�Ӽ��������ֵ=0x07����ÿ��128cycle(0x7F)���ɼ�����1��64bit���ݣ���ʱ��Ƶ��=150MHz����������ݴ���=75Mbps��
   UNION�ṹ:  DBG_DBG_BUS_TEST_UNION */
#define DBG_DBG_BUS_TEST_ADDR                         (SOC_BBP_DBG_BASE_ADDR + 0x40CC)

/* �Ĵ���˵����SP MEM CTRL���üĴ���
 bit[31:16]  ������
 bit[15:0]   SPRAM��MEM_CTRL���á�
             ȱʡֵ��ͳһ�����ṩ��
   UNION�ṹ:  DBG_SP_MEM_CTRL_UNION */
#define DBG_SP_MEM_CTRL_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x40E0)

/* �Ĵ���˵����TP MEM CTRL���üĴ���
 bit[31:16]  ������
 bit[15:0]   TPRAM��MEM_CTRL���á�
             ȱʡֵ��ͳһ�����ṩ��
   UNION�ṹ:  DBG_TP_MEM_CTRL_UNION */
#define DBG_TP_MEM_CTRL_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x40E4)

/* �Ĵ���˵����ARBITER���ȼ�ѡ�����üĴ���
 bit[31:8]   ������
 bit[7:0]    DDRͨ·��arbiter���ȼ�ѡ�����á�
             0�������ȼ���1�������ȼ���
             bit0��sdrͨ����
             bit1��dbg_busͨ����
             bit2��dbg_dataͨ����
             bit3��dbg_logͨ����
             ���ౣ����
   UNION�ṹ:  DBG_ARB_PRIOR_SEL_UNION */
#define DBG_ARB_PRIOR_SEL_ADDR                        (SOC_BBP_DBG_BASE_ADDR + 0x4100)

/* �Ĵ���˵����TEST SWITCH���üĴ���
 bit[31:5]   ������
 bit[4]      Burst�ӿ�gnt��rd�źŶ���ѡ��
             0��gnt��rd������룻(ȱʡ����)
             1��gnt��rd���Բ����롣
 bit[3:1]    ������
 bit[0]      ģ����Թ�����ѡ�񿪹ء�
             0�����Թ��ܹرգ�(ȱʡ����)
             1�����Թ��ܿ�����
   UNION�ṹ:  DBG_TEST_SWITCH_UNION */
#define DBG_TEST_SWITCH_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4104)

/* �Ĵ���˵����GNT��RD����״̬�Ĵ���
 bit[31:5]   ������
 bit[4]      ָʾDMA��DDR�ӿ�gnt�ź���Чͬʱ��rd�ź�״̬����λд1��0״̬
 bit[3:1]    ������
 bit[0]      ָʾDMA��TCM�ӿ�gnt�ź���Чͬʱ��rd�ź�״̬����λд1��0״̬
   UNION�ṹ:  DBG_GNT_RD_STS_UNION */
#define DBG_GNT_RD_STS_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x411C)

/* �Ĵ���˵����TCMͨ����DMA����/��Ӧ����������
 bit[31:16]  TCM��DMA�ӿڵ�gnt��Ӧ������������
             Test_switch������Ч���ر���0��
             ֻ����16λ��������
 bit[15:0]   TCM��DMA�ӿڵ�req���������������
             Test_switch������Ч���ر���0��
             ֻ����16λ��������
   UNION�ṹ:  DBG_TCM_DMA_CNT_UNION */
#define DBG_TCM_DMA_CNT_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4120)

/* �Ĵ���˵����tcm��ram״̬������
 bit[31:29]  ������
 bit[28]     ָʾTCMͨ��RAMʵʱ�ǿ�״̬��
             0��ramΪ�ա�1��ram�ǿգ�
 bit[27:22]  ������
 bit[21:16]  ָʾTCMͨ��RAM�ﵽ���burst�洢������
             Test_switch������Ч���ر���0��
             6λ�����������ݷ�Χ��0~32��
 bit[15:10]  ������
 bit[9:0]    ָʾTCMͨ��RAM�ﵽ���洢���ݸ�����
             Test_switch������Ч���ر���0��
             10λ�����������ݷ�Χ��0~512��
   UNION�ṹ:  DBG_TCM_RAM_CNT_UNION */
#define DBG_TCM_RAM_CNT_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4124)

/* �Ĵ���˵����tcmͨ��req����Ӧʱ�������
 bit[31:24]  ������
 bit[23:0]   ָʾTCMͨ��RAM��req/gnt�����ʱ�������
             Test_switch������Ч���ر���0��
             24λ��������ʱ�������ʱ����ء�
   UNION�ṹ:  DBG_TCM_TIME_CNT_UNION */
#define DBG_TCM_TIME_CNT_ADDR                         (SOC_BBP_DBG_BASE_ADDR + 0x4128)

/* �Ĵ���˵����DBG �ɼ�DAT����ID���ͼĴ���
   ��      ����DAT���ݵ�ID�����ϱ�ָʾ��
               ֻ����DBG��DAT��������ʱ��0��
   UNION�ṹ ���� */
#define DBG_DBG_DAT_ID_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x4130)

/* �Ĵ���˵����DBG �ɼ�LOG����ID���ͼĴ���
   ��      ����LOG���ݵ�ID�����ϱ�ָʾ��
               ֻ����DBG��LOG��������ʱ��0��
   UNION�ṹ ���� */
#define DBG_DBG_LOG_ID_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x4134)

/* �Ĵ���˵����DBG�ж�״̬�Ĵ���
 bit[31:7]   ������
 bit[6:0]    DBG�ж�״ָ̬ʾ��
             0�����жϣ�
             1�����жϣ�
             bit0��dat������������жϣ�
             bit1��bus������������жϣ�
             bit2��bus����burst�����жϣ�
             bit3��log������������жϣ�
             bit4��log���ݴ���֡����С������ֵ�����жϣ�
             bit5��log���ݴ���֡���ݴ�������ֵ�����жϣ�
             bit6��log���ݴ���֡����С������ֵ���޽�����ʶ�����жϡ�
   UNION�ṹ:  DBG_DBG_INT_STS_UNION */
#define DBG_DBG_INT_STS_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4140)

/* �Ĵ���˵����DBG�ж�����Ĵ���
 bit[31:7]   ������
 bit[6:0]    DBG�ж��������Ӧλд1��0�жϡ�
             bit0��dat������������ж���0��
             bit1��bus������������ж���0��
             bit2��bus����burst�����ж���0��
             bit3��log������������ж���0��
             bit4��log���ݴ���֡����С������ֵ�����ж���0��
             bit5��log���ݴ���֡���ݴ�������ֵ�����ж���0��
             bit6��log���ݴ���֡����С������ֵ���޽�����ʶ�����ж���0��
   UNION�ṹ:  DBG_DBG_INT_CLR_UNION */
#define DBG_DBG_INT_CLR_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4144)

/* �Ĵ���˵����DBG�ж����μĴ���
 bit[31:7]   ������
 bit[6:0]    DBG�ж����Ρ�
             0���ж�����ʹ�ܣ��жϲ��ϱ�(ȱʡ״̬)
             1���жϿ��ϱ�
             bit0��dat������������ж�����λ��
             bit1��bus������������ж�����λ��
             bit2��bus����burst�����ж�����λ��
             bit3��log������������ж�����λ��
             bit4��log���ݴ���֡����С������ֵ�����ж�����λ��
             bit5��log���ݴ���֡���ݴ�������ֵ�����ж�����λ��
             bit6��log���ݴ���֡����С������ֵ���޽�����ʶ�����ж�����λ��
   UNION�ṹ:  DBG_DBG_INT_MSK_UNION */
#define DBG_DBG_INT_MSK_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4148)

/* �Ĵ���˵����DBG��������
 bit[31:2]   ����
 bit[1:0]    ģ������ID��Ĺ�������ÿ��bitָʾһ��ID�����磬bit0����ID��Ϊdbg_id + 1��bit1����ID��Ϊdbg_id + 1���������ơ�
             ���bitȡֵΪ1��������bit��Ӧ��ID��Ч��������Ч��
             0������ͨ��2��������ͬʱ�ɼ�
             1�����з���ͨ�����ݲɼ�
             2������ͨ��������RXA���ݲɼ�
             3������ͨ��������RXB���ݲɼ�
   UNION�ṹ:  DBG_RFIN_DBG_FLT_UNION */
#define DBG_RFIN_DBG_FLT_ADDR                         (SOC_BBP_DBG_BASE_ADDR + 0x4600)

/* �Ĵ���˵����DBG ID��
   ��      ���������ļ��е�ID��
   UNION�ṹ ���� */
#define DBG_RFIN_DBG_ID_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4604)

/* �Ĵ���˵����DBG����ѡ��
 bit[31:18]  ����
 bit[17:16]  ��������ʹ�ܣ�ÿ��bit��Ӧһ�������ز���ȡֵΪ1�������ز�����ʹ�ܣ�
             [1]�������ز�1����
             [0]�������ز�0����
 bit[15:4]   ����
 bit[3:0]    ��������ʹ�ܣ�ÿ��bit��Ӧһ�������ز���ȡֵΪ1������ͨ�ز�����ʹ�ܣ�
             [3]�������ز�3����
             [2]�������ز�2����
             [1]�������ز�1����
             [0]�������ز�0����
   UNION�ṹ:  DBG_RFIN_DBG_CH_UNION */
#define DBG_RFIN_DBG_CH_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4608)

/* �Ĵ���˵����DBG����ģʽ
 bit[31:16]  ���ɰ��ĸ���
 bit[15:1]   ����
 bit[0]      �����ϱ�ģʽ��
             1'b0�����ɹ��ܴ����󣬲���dbg_pkg_num�����ݰ����Զ�����
             1'b1��ֻҪdbg_enΪ1��һֱ�����ϱ�������dbg_pkg_num����
   UNION�ṹ:  DBG_RFIN_DBG_MODE_UNION */
#define DBG_RFIN_DBG_MODE_ADDR                        (SOC_BBP_DBG_BASE_ADDR + 0x460C)

/* �Ĵ���˵����DBG����ʹ��
 bit[31:1]   ����
 bit[0]      ����ʹ�ܣ�
             1'b0�����ɹ��ܲ�ʹ��
             1'b1�����ɹ���ʹ��
   UNION�ṹ:  DBG_RFIN_DBG_EN_UNION */
#define DBG_RFIN_DBG_EN_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x4610)

/* �Ĵ���˵�����Ĵ�����
   ��      ����ģ��LOG ID�������0
               �����±��ؿ������ó�1'b1��
               0~4/14/18/22/26/30
   UNION�ṹ ���� */
#define DBG_FPU_DBG_LOG_FLT0_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x8400)

/* �Ĵ���˵�����Ĵ�����
   ��      ����ģ��LOG ID�������1
               �����±��ؿ������ó�1'b1��
               2/6/10/11/14~18/23~25/27
   UNION�ṹ ���� */
#define DBG_FPU_DBG_LOG_FLT1_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x8404)

/* �Ĵ���˵�����Ĵ�����
 bit[31:16]  LOG��Ϣ��ά�ɲ�İ�����
 bit[15:1]   ����
 bit[0]      ��ά�ɲ������ϱ�ģʽ��
             'b0���������������fpu_log_pkg_num�����ݰ����Զ�������
             'b1��ֻҪfpu_log_enΪ1���ϱ���û���ϱ��������ơ�
   UNION�ṹ:  DBG_FPU_DBG_LOG_CFG_UNION */
#define DBG_FPU_DBG_LOG_CFG_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x8408)

/* �Ĵ���˵�����Ĵ�����
   ��      ����ǰ��log��ʼid��
   UNION�ṹ ���� */
#define DBG_FPU_DBG_LOG_ID_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x840C)

/* �Ĵ���˵�����Ĵ�����
 bit[31:16]  ����
 bit[15:0]   ģ��DAT ID�������
             [4] cfu�����źš�
             [9] fpu_lsѡ���źš�
             [11] fpu_lsuѡ���źš�
             [12] fpu_emuѡ���źš�
             [13] fpu_truѡ���źš�
             ����bit����
   UNION�ṹ:  DBG_FPU_DBG_DAT_FLT_UNION */
#define DBG_FPU_DBG_DAT_FLT_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x8410)

/* �Ĵ���˵�����Ĵ�����
 bit[31:16]  ����
 bit[15:3]   ����
 bit[2:1]    ��ά�ɲ������ϱ�����ƴ��ģʽ��
             'd0����ƴ�ӣ�
             'd1��������
             'd2����������0����ƴ��Ϊһ��64bit���� word�ϱ���
             'd3��2��������ƴ��Ϊһ��64bit���� word�ϱ���
 bit[0]      ��ά�ɲ������ϱ�ģʽ��
             'b0���������������fpu_dbg_pkg_num�����ݰ����Զ�������
             'b1��ֻҪfpu_dbg_enΪ1���ϱ���û���ϱ��������ơ�
   UNION�ṹ:  DBG_FPU_DBG_DAT_CFG0_UNION */
#define DBG_FPU_DBG_DAT_CFG0_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x8414)

/* �Ĵ���˵�����Ĵ�����
   ��      ����dbg��ʼid��,������
   UNION�ṹ ���� */
#define DBG_FPU_DBG_DAT_ID_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x8418)

/* �Ĵ���˵�����Ĵ�����
 bit[31:1]   ����
 bit[0]      LOG�ϱ�ʼ��
             1'b1:ʹ��
             1'b0:��ʹ��
   UNION�ṹ:  DBG_FPU_LOG_EN_UNION */
#define DBG_FPU_LOG_EN_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x8424)

/* �Ĵ���˵�����Ĵ�����
 bit[31:1]   ����
 bit[0]      dbg �ϱ��Ƿ�ʼ��
             1'b1:ʹ��
             1'b0:��ʹ��
   UNION�ṹ:  DBG_FPU_DBG_EN_UNION */
#define DBG_FPU_DBG_EN_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0x8428)

/* �Ĵ���˵�����Ĵ�����
 bit[31:4]   ����
 bit[3:2]    0: ѡ��pcc dbg���ݣ���������
             1��ѡ��cc1 dbg���ݣ���������
             2: ѡ��cc2 dbg���ݣ���������
             3��ѡ��cc3 dbg���ݣ���������
 bit[1:0]    0: ѡ��pcc log���ݣ���������
             1��ѡ��cc1 log���ݣ���������
             2: ѡ��cc2 log���ݣ���������
             3��ѡ��cc3 log���ݣ���������
   UNION�ṹ:  DBG_FPU_LOG_DBG_SEL_UNION */
#define DBG_FPU_LOG_DBG_SEL_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x842C)

/* �Ĵ���˵�����Ĵ�����
 bit[31:22]  ����
 bit[21:20]  FPU CC�ڲ�smu debug��Ϣͨ��ѡ��(������)
             2'b0���ϱ�ͨ��0
             2'b1���ϱ�ͨ��1
             2'b10���ϱ�ͨ��2
             2'b11���ϱ�ͨ��3
             ��Чʱ�̣�������Ч
 bit[19:18]  ����
 bit[17:16]  FPU CC�ڲ�smp debug�����ϱ�ģʽѡ��(������)
             2'b0��ѡ���ϱ�lsu�����ԭʼLS���ݣ�
             2'b1��ѡ���ϱ�ls_smp�����LS���ݣ�
             2'b10��ѡ���ϱ�em_smp�����emu��·�������ݣ�
             2'b11��ѡ���ϱ�tru_smp�����pdp����
             ��Чʱ�̣�������Ч
 bit[15:12]  FPU CC�ڲ�debug�����ϱ�ģʽѡ��(������)
             4'b0��ѡ���ϱ�cfu�ڲ�״̬��Ϣ��
             4'b1��ѡ���ϱ�dfu�ڲ�״̬��Ϣ��
             4'b10��ѡ���ϱ�smu�ڲ�״̬��Ϣ��
             4'b11��ѡ���ϱ�afc�ڲ�״̬��Ϣ��
             4'b100��ѡ���ϱ�tru�ڲ�״̬��Ϣ��
             4'b101��ѡ���ϱ�tau���ڲ�״̬��Ϣ��
             4'b110��ѡ���ϱ�����ȫͨ·״̬��Ϣ��
             4'b111��ѡ���ϱ����ȫͨ·״̬��Ϣ��
             4'b1000��ѡ���ϱ�smp�ڲ�״̬��Ϣ��
             4'b1001��ѡ���ϱ�cmu_buf�ڲ�״̬��Ϣ��
             ��Чʱ�̣�������Ч
 bit[11:10]  ����
 bit[9:8]    FPU rfin debug�Ĵ����ϱ�ѡ���ź�(������)
             2'b0��ѡ��pcc rfin debug���ݣ�
             2'b01��ѡ��cc1 rfin debug���ݣ�
             2'b10��ѡ��cc2 rfin debug���ݣ�
             2'b11��ѡ��cc3 rfin debug���ݣ�
             ��Чʱ�̣�������Ч
 bit[7]      ����
 bit[6:4]    FPU ��ccͨ·debug�Ĵ����ϱ�ѡ���ź�(������)
             3'b0,pcc debug���ݣ�
             3'b1,cc1 debug���ݣ�
             3'b10,cc2 debug���ݣ�
             3'b11,cc3 debug���ݣ�
             3'b100,mlafc debug���ݣ�
             3'b101,csu0 debug���ݣ�
             3'b110,csu1 debug���ݣ�
             ���ౣ��
             ��Чʱ�̣�������Ч
 bit[3:2]    ����
 bit[1:0]    FPU SMP debug���ݲɼ�ѡ���ź�(������)
             2'b0��ѡ��pcc smp���ݣ�
             2'b01��ѡ��cc1 smp���ݣ�
             2'b10��ѡ��cc2 smp���ݣ�
             2'b11��ѡ��cc3 smp���ݣ�
             ��Чʱ�̣�������Ч
   UNION�ṹ:  DBG_FPU_DEBUG_CTRL_UNION */
#define DBG_FPU_DEBUG_CTRL_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0xE1138610)

/* �Ĵ���˵�����Ĵ�����
 bit[31:11]  ����
 bit[10:8]   ����
 bit[7:5]    ����
 bit[4]      ����
 bit[3]      ����
 bit[2:0]    ����
   UNION�ṹ:  DBG_SMU_CC_DEBUG_SEL_UNION */
#define DBG_SMU_CC_DEBUG_SEL_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0xE1165950)

/* �Ĵ���˵�����Ĵ�����
 bit[31:11]  ����
 bit[10:8]   ����
 bit[7:5]    ����
 bit[4]      ����
 bit[3]      ����
 bit[2:0]    ����
   UNION�ṹ:  DBG_CC1_SMU_CC_DEBUG_SEL_UNION */
#define DBG_CC1_SMU_CC_DEBUG_SEL_ADDR                 (SOC_BBP_DBG_BASE_ADDR + 0xE1167950)

/* �Ĵ���˵�����Ĵ�����
 bit[31:11]  ����
 bit[10:8]   ����
 bit[7:5]    ����
 bit[4]      ����
 bit[3]      ����
 bit[2:0]    ����
   UNION�ṹ:  DBG_CC2_SMU_CC_DEBUG_SEL_UNION */
#define DBG_CC2_SMU_CC_DEBUG_SEL_ADDR                 (SOC_BBP_DBG_BASE_ADDR + 0xE1169950)

/* �Ĵ���˵�����Ĵ�����
 bit[31:11]  ����
 bit[10:8]   ����
 bit[7:5]    ����
 bit[4]      ����
 bit[3]      ����
 bit[2:0]    ����
   UNION�ṹ:  DBG_CC3_SMU_CC_DEBUG_SEL_UNION */
#define DBG_CC3_SMU_CC_DEBUG_SEL_ADDR                 (SOC_BBP_DBG_BASE_ADDR + 0xE116B950)

/* �Ĵ���˵����ģ��LOG ID�������
   ��      ����ģ��LOG ID�������
   UNION�ṹ ���� */
#define DBG_PDU_DBG_LOG_FLT0_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x8000)

/* �Ĵ���˵����ģ��LOG ID�������
   ��      ����ģ��LOG ID�������
   UNION�ṹ ���� */
#define DBG_PDU_DBG_LOG_FLT1_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x8004)

/* �Ĵ���˵����ģ��LOG ģʽ�Ĵ���
 bit[31:16]  LOG��Ϣ��ά�ɲ�İ�����
 bit[15:2]   ����
 bit[1]      ��ά�ɲ������ϱ�ģʽ��
             0���������������dbg_pkg_num�����ݰ����Զ�����
             1��ֻҪdbg_rpt_enΪ1���ϱ���û���ϱ��������ơ�
 bit[0]      ����
   UNION�ṹ:  DBG_PDU_DBG_LOG_MODE_UNION */
#define DBG_PDU_DBG_LOG_MODE_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x8008)

/* �Ĵ���˵����ģ��LOG EN�Ĵ���
 bit[31:1]   ����
 bit[0]      ģ��LOGʹ��                              
             0����ά�ɲ⹦�ܲ�ʹ��                             1����ά�ɲ⹦��ʹ��
   UNION�ṹ:  DBG_PDU_DBG_LOG_EN_UNION */
#define DBG_PDU_DBG_LOG_EN_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x800C)

/* �Ĵ���˵����ģ��LOG ID�Ĵ���
   ��      ������ά�ɲ�LOG ��Ϣͷ�ļ��е�ID�Ż�ַ
   UNION�ṹ ���� */
#define DBG_PDU_DBG_LOG_ID_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x8010)

/* �Ĵ���˵����ģ��DAT ID�������
   ��      ����ģ��DAT ID�������
   UNION�ṹ ���� */
#define DBG_PDU_DBG_DAT_FLT0_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x8014)

/* �Ĵ���˵����ģ��DAT ID�������
   ��      ����ģ��DAT ID�������
   UNION�ṹ ���� */
#define DBG_PDU_DBG_DAT_FLT1_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x8018)

/* �Ĵ���˵����ģ��DAT ģʽ�Ĵ���
 bit[31:16]  DAT��Ϣ��ά�ɲ�İ�����
 bit[15:2]   ����
 bit[1]      ��ά�ɲ������ϱ�ģʽ��
             0���������������dbg_pkg_num�����ݰ����Զ�����
             1��ֻҪdbg_rpt_enΪ1���ϱ���û���ϱ��������ơ�
 bit[0]      ����
   UNION�ṹ:  DBG_PDU_DBG_DAT_MODE_UNION */
#define DBG_PDU_DBG_DAT_MODE_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x801C)

/* �Ĵ���˵����ģ��DAT EN�Ĵ���
 bit[31:1]   ����
 bit[0]      ģ��DATʹ��                              
             0����ά�ɲ⹦�ܲ�ʹ��                             1����ά�ɲ⹦��ʹ��
   UNION�ṹ:  DBG_PDU_DBG_DAT_EN_UNION */
#define DBG_PDU_DBG_DAT_EN_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x8020)

/* �Ĵ���˵����ģ��DAT ID�Ĵ���
   ��      ������ά�ɲ�DAT ��Ϣͷ�ļ��е�ID�Ż�ַ
   UNION�ṹ ���� */
#define DBG_PDU_DBG_DAT_ID_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x8024)

/* �Ĵ���˵����ģ��LOG ID�������
   ��      ����ģ��LOG ID�������
   UNION�ṹ ���� */
#define DBG_PDU2_DBG_LOG_FLT0_ADDR                    (SOC_BBP_DBG_BASE_ADDR + 0xE1B18000)

/* �Ĵ���˵����ģ��LOG ID�������
   ��      ����ģ��LOG ID�������
   UNION�ṹ ���� */
#define DBG_PDU2_DBG_LOG_FLT1_ADDR                    (SOC_BBP_DBG_BASE_ADDR + 0xE1B18004)

/* �Ĵ���˵����ģ��LOG ģʽ�Ĵ���
 bit[31:16]  LOG��Ϣ��ά�ɲ�İ�����
 bit[15:2]   ����
 bit[1]      ��ά�ɲ������ϱ�ģʽ��
             0���������������dbg_pkg_num�����ݰ����Զ�����
             1��ֻҪdbg_rpt_enΪ1���ϱ���û���ϱ��������ơ�
 bit[0]      ����
   UNION�ṹ:  DBG_PDU2_DBG_LOG_MODE_UNION */
#define DBG_PDU2_DBG_LOG_MODE_ADDR                    (SOC_BBP_DBG_BASE_ADDR + 0xE1B18008)

/* �Ĵ���˵����ģ��LOG EN�Ĵ���
 bit[31:1]   ����
 bit[0]      ģ��LOGʹ��                              
             0����ά�ɲ⹦�ܲ�ʹ��                             1����ά�ɲ⹦��ʹ��
   UNION�ṹ:  DBG_PDU2_DBG_LOG_EN_UNION */
#define DBG_PDU2_DBG_LOG_EN_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0xE1B1800C)

/* �Ĵ���˵����ģ��LOG ID�Ĵ���
   ��      ������ά�ɲ�LOG ��Ϣͷ�ļ��е�ID�Ż�ַ
   UNION�ṹ ���� */
#define DBG_PDU2_DBG_LOG_ID_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0xE1B18010)

/* �Ĵ���˵����ģ��DAT ID�������
   ��      ����ģ��DAT ID�������
   UNION�ṹ ���� */
#define DBG_PDU2_DBG_DAT_FLT0_ADDR                    (SOC_BBP_DBG_BASE_ADDR + 0xE1B18014)

/* �Ĵ���˵����ģ��DAT ID�������
   ��      ����ģ��DAT ID�������
   UNION�ṹ ���� */
#define DBG_PDU2_DBG_DAT_FLT1_ADDR                    (SOC_BBP_DBG_BASE_ADDR + 0xE1B18018)

/* �Ĵ���˵����ģ��DAT ģʽ�Ĵ���
 bit[31:16]  DAT��Ϣ��ά�ɲ�İ�����
 bit[15:2]   ����
 bit[1]      ��ά�ɲ������ϱ�ģʽ��
             0���������������dbg_pkg_num�����ݰ����Զ�����
             1��ֻҪdbg_rpt_enΪ1���ϱ���û���ϱ��������ơ�
 bit[0]      ����
   UNION�ṹ:  DBG_PDU2_DBG_DAT_MODE_UNION */
#define DBG_PDU2_DBG_DAT_MODE_ADDR                    (SOC_BBP_DBG_BASE_ADDR + 0xE1B1801C)

/* �Ĵ���˵����ģ��DAT EN�Ĵ���
 bit[31:1]   ����
 bit[0]      ģ��DATʹ��                              
             0����ά�ɲ⹦�ܲ�ʹ��                             1����ά�ɲ⹦��ʹ��
   UNION�ṹ:  DBG_PDU2_DBG_DAT_EN_UNION */
#define DBG_PDU2_DBG_DAT_EN_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0xE1B18020)

/* �Ĵ���˵����ģ��DAT ID�Ĵ���
   ��      ������ά�ɲ�DAT ��Ϣͷ�ļ��е�ID�Ż�ַ
   UNION�ṹ ���� */
#define DBG_PDU2_DBG_DAT_ID_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0xE1B18024)

/* �Ĵ���˵������ά�ɲ�Ŀ�ʼʱ��
 bit[31:20]  ����
 bit[19:16]  ��ά�ɲ�����ʱ�䣬��ϵͳ��ʱ�ο�����֡�ڵķ��ż���
 bit[15:12]  ����
 bit[11:0]   ��ά�ɲ�����ʱ�䣬��ϵͳ��ʱ�ο���symbol��Ts����
   UNION�ṹ:  DBG_CQI_DBG_START_TIME_UNION */
#define DBG_CQI_DBG_START_TIME_ADDR                   (SOC_BBP_DBG_BASE_ADDR + 0x7300)

/* �Ĵ���˵��������ʹ�ܼĴ���
 bit[31:1]   ����
 bit[0:0]    ���ݲɼ�ʹ��
             0�����ɲ�ʹ��
             1������ʹ��
   UNION�ṹ:  DBG_CQI_DBG_DAT_EN_UNION */
#define DBG_CQI_DBG_DAT_EN_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x7318)

/* �Ĵ���˵��������ID�Ż�ַ
   ��      ����CQI ������Ϣͷ�ļ��е�ID�Ż�ַ��
   UNION�ṹ ���� */
#define DBG_CQI_DBG_DAT_ID_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x731C)

/* �Ĵ���˵����ģ��LOG ID�������
   ��      ����ģ��LOG ID�������
   UNION�ṹ ���� */
#define DBG_PB_DBG_LOG_FLT0_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x5508)

/* �Ĵ���˵����ģ��LOG ID�������
   ��      ����ģ��LOG ID�������
   UNION�ṹ ���� */
#define DBG_PB_DBG_LOG_FLT1_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x550C)

/* �Ĵ���˵����LOG��Ϣģʽ�Ĵ���
 bit[31:16]  LOG��Ϣ��ά�ɲ�İ�����
 bit[15:2]   ����
 bit[1]      ��ά�ɲ������ϱ�ģʽ��
             'b0���������������dbg_pkg_num�����ݰ����Զ�������
             'b1��ֻҪdbg_rpt_enΪ1���ϱ���û���ϱ��������ơ�
 bit[0]      ����
   UNION�ṹ:  DBG_PB_DBG_LOG_MODE_UNION */
#define DBG_PB_DBG_LOG_MODE_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x5510)

/* �Ĵ���˵����LOG��Ϣʹ�ܼĴ���
 bit[31:1]   ����
 bit[0]      ģ��LOGʹ��                              
             1'b0����ά�ɲ⹦�ܲ�ʹ��                             1'b1����ά�ɲ⹦��ʹ��
   UNION�ṹ:  DBG_PB_DBG_LOG_EN_UNION */
#define DBG_PB_DBG_LOG_EN_ADDR                        (SOC_BBP_DBG_BASE_ADDR + 0x5514)

/* �Ĵ���˵������ά�ɲ�LOG ��Ϣͷ�ļ��е�ID�Ż�ַ
   ��      ������ά�ɲ�LOG ��Ϣͷ�ļ��е�ID�Ż�ַ
   UNION�ṹ ���� */
#define DBG_PB_DBG_LOG_ID_ADDR                        (SOC_BBP_DBG_BASE_ADDR + 0x5518)

/* �Ĵ���˵������ά�ɲ��ϱ�LOG ID���������
 bit[31:4]   ����
 bit[3:0]    ��ά�ɲ��ϱ�����������Чָʾ��[n]��Ӧ��n���ϱ����ݣ�[0]��Ӧ��0���ϱ����ݣ�
             'b1����Ӧ��ά�ɲ��������ϱ������
             'b0����Ӧ��ά�ɲ������鲻�ϱ������
   UNION�ṹ:  DBG_TDL_DBG_LOG_FLT_UNION */
#define DBG_TDL_DBG_LOG_FLT_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0xE1C040D0)

/* �Ĵ���˵������ά�ɲ��ϱ����ƼĴ���
 bit[31:16]  
             LOG��Ϣ��ά�ɲ�İ�����
 bit[15:2]   ����
 bit[1]      ��ά�ɲ������ϱ�ģʽ��
             'b0���������������dbg_pkg_num�����ݰ����Զ�������
             'b1��ֻҪdbg_log_enΪ1���ϱ���û���ϱ��������ơ�
 bit[0]      ����
   UNION�ṹ:  DBG_TDL_DBG_LOG_MODE_UNION */
#define DBG_TDL_DBG_LOG_MODE_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0xE1C040D4)

/* �Ĵ���˵������ά�ɲ��ϱ����ݰ�ID�Ż�ַ
   ��      ������ά�ɲ��ϱ����ݰ�ID�Ż�ַ����ͨ��ʹ��0x40007000����ͨ��ʹ��0x40007010
   UNION�ṹ ���� */
#define DBG_TDL_DBG_LOG_ID_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0xE1C040D8)

/* �Ĵ���˵������ά�ɲ����ʹ�ܼĴ���
 bit[31:1]   ����
 bit[0]      ��ά�ɲ�LOGʹ���źţ���dbg_rpt_modeΪ0ʱ�߼����壬������Ҫд�塣
             1'b0����ά�ɲ⹦�ܲ�ʹ��                             1'b1����ά�ɲ⹦��ʹ��
   UNION�ṹ:  DBG_TDL_DBG_LOG_EN_UNION */
#define DBG_TDL_DBG_LOG_EN_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0xE1C040DC)

/* �Ĵ���˵������ά�ɲ��ϱ�LOG ID���������
 bit[31:4]   ����
 bit[3:0]    ��ά�ɲ��ϱ�����������Чָʾ��[n]��Ӧ��n���ϱ����ݣ�[0]��Ӧ��0���ϱ����ݣ�
             'b1����Ӧ��ά�ɲ��������ϱ������
             'b0����Ӧ��ά�ɲ������鲻�ϱ������
   UNION�ṹ:  DBG_TDL2_DBG_LOG_FLT_UNION */
#define DBG_TDL2_DBG_LOG_FLT_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0xE1C240D0)

/* �Ĵ���˵������ά�ɲ��ϱ����ƼĴ���
 bit[31:16]  
             LOG��Ϣ��ά�ɲ�İ�����
 bit[15:2]   ����
 bit[1]      ��ά�ɲ������ϱ�ģʽ��
             'b0���������������dbg_pkg_num�����ݰ����Զ�������
             'b1��ֻҪdbg_log_enΪ1���ϱ���û���ϱ��������ơ�
 bit[0]      ����
   UNION�ṹ:  DBG_TDL2_DBG_LOG_MODE_UNION */
#define DBG_TDL2_DBG_LOG_MODE_ADDR                    (SOC_BBP_DBG_BASE_ADDR + 0xE1C240D4)

/* �Ĵ���˵������ά�ɲ��ϱ����ݰ�ID�Ż�ַ
   ��      ������ά�ɲ��ϱ����ݰ�ID�Ż�ַ����ͨ��ʹ��0x40007000����ͨ��ʹ��0x40007010
   UNION�ṹ ���� */
#define DBG_TDL2_DBG_LOG_ID_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0xE1C240D8)

/* �Ĵ���˵������ά�ɲ����ʹ�ܼĴ���
 bit[31:1]   ����
 bit[0]      ��ά�ɲ�LOGʹ���źţ���dbg_rpt_modeΪ0ʱ�߼����壬������Ҫд�塣
             1'b0����ά�ɲ⹦�ܲ�ʹ��                             1'b1����ά�ɲ⹦��ʹ��
   UNION�ṹ:  DBG_TDL2_DBG_LOG_EN_UNION */
#define DBG_TDL2_DBG_LOG_EN_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0xE1C240DC)

/* �Ĵ���˵������ά�ɲ�BUSͨ��buffer��ַ�Ĵ���
 bit[31:3]   BUS buffer����ַ��DMA�����ݴӿ�ά�ɲ�ģ����Ƶ��Ըõ�ַΪ��ʼ��ַ��buffer�ڡ�8�ֽڶ��롣
 bit[2:0]    ������
   UNION�ṹ:  DBG_DMA_DBG_BUS_ADDR_UNION */
#define DBG_DMA_DBG_BUS_ADDR_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x4200)

/* �Ĵ���˵������ά�ɲ�BUSͨ��дָ��Ĵ���
 bit[31:3]   BUS bufferдָ�롣���ά����8�ֽڶ��롣
 bit[2:0]    ������
   UNION�ṹ:  DBG_DMA_DBG_BUS_WPTR_UNION */
#define DBG_DMA_DBG_BUS_WPTR_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x4204)

/* �Ĵ���˵������ά�ɲ�BUSͨ����ָ��Ĵ���
 bit[31:3]   BUS buffer��ָ�롣Ӳ����SOCPģ���ȡ���£����ֻ����8�ֽڶ��롣
 bit[2:0]    ������
   UNION�ṹ:  DBG_DMA_DBG_BUS_RPTR_UNION */
#define DBG_DMA_DBG_BUS_RPTR_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x4208)

/* �Ĵ���˵������ά�ɲ�BUSͨ�����üĴ���
 bit[31:24]  ������
 bit[23:3]   BUS buffer���ȡ�8�ֽڶ��롣
 bit[2:0]    ������
   UNION�ṹ:  DBG_DMA_DBG_BUS_CFG_UNION */
#define DBG_DMA_DBG_BUS_CFG_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x420C)

/* �Ĵ���˵������ά�ɲ�LOGͨ��buffer��ַ�Ĵ���
 bit[31:3]   LOG buffer����ַ��DMA�����ݴӿ�ά�ɲ�ģ����Ƶ��Ըõ�ַΪ��ʼ��ַ��buffer�ڡ�8�ֽڶ��롣
 bit[2:0]    ������
   UNION�ṹ:  DBG_DMA_DBG_LOG_ADDR_UNION */
#define DBG_DMA_DBG_LOG_ADDR_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x4210)

/* �Ĵ���˵������ά�ɲ�LOGͨ��дָ��Ĵ���
 bit[31:3]   LOG bufferдָ�롣���ά����8�ֽڶ��롣
 bit[2:0]    ������
   UNION�ṹ:  DBG_DMA_DBG_LOG_WPTR_UNION */
#define DBG_DMA_DBG_LOG_WPTR_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x4214)

/* �Ĵ���˵������ά�ɲ�LOGͨ����ָ��Ĵ���
 bit[31:3]   LOG buffer��ָ�롣Ӳ����SOCPģ���ȡ���£����ֻ����8�ֽڶ��롣
 bit[2:0]    ������
   UNION�ṹ:  DBG_DMA_DBG_LOG_RPTR_UNION */
#define DBG_DMA_DBG_LOG_RPTR_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x4218)

/* �Ĵ���˵������ά�ɲ�LOGͨ�����üĴ���
 bit[31:24]  ������
 bit[23:3]   LOG buffer���ȡ�8�ֽڶ��롣
 bit[2:0]    ������
   UNION�ṹ:  DBG_DMA_DBG_LOG_CFG_UNION */
#define DBG_DMA_DBG_LOG_CFG_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x421C)

/* �Ĵ���˵������ά�ɲ�����ͨ��buffer��ַ
 bit[31:3]   ��ά�ɲ����ݲɼ�ͨ��buffer��ʼ��ַ��8�ֽڶ��롣
 bit[2:0]    ������
   UNION�ṹ:  DBG_DMA_DBG_DS_ADDR_UNION */
#define DBG_DMA_DBG_DS_ADDR_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x4280)

/* �Ĵ���˵������ά�ɲ�����ͨ��дָ��Ĵ���
 bit[31:3]   ��ά�ɲ����ݲɼ�ͨ��дָ�롣���ά����8�ֽڶ��롣
 bit[2:0]    ������
   UNION�ṹ:  DBG_DMA_DBG_DS_WPTR_UNION */
#define DBG_DMA_DBG_DS_WPTR_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x4284)

/* �Ĵ���˵������ά�ɲ�����ͨ����ָ��Ĵ���
 bit[31:3]   ��ά�ɲ����ݲɼ�ͨ����ָ�롣ָʾ�����������ʼ��ַ�����ά����8�ֽڶ��롣
 bit[2:0]    ������
   UNION�ṹ:  DBG_DMA_DBG_DS_RPTR_UNION */
#define DBG_DMA_DBG_DS_RPTR_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x4288)

/* �Ĵ���˵������ά�ɲ�����ͨ�����üĴ���
 bit[31]     ��ά�ɲ����ݲɼ�ͨ��buffer���������ơ�
             0��stop������ǰbuffer�ĺ������ݶ�����
             1��buffer���ǣ��ص���ʼ��ַд�롣
 bit[30]     ��ά�ɲ����ݲɼ�ͨ��buffer���״̬��
             0��δ���(ds_overflow_ctrl=0)��δѭ������(ds_overflow_ctrl=1)
             1�������(ds_overflow_ctrl=0)����ѭ������(ds_overflow_ctrl=1)
 bit[29:28]  ������
 bit[27:3]   ��ά�ɲ����ݲɼ�ͨ��buffer���ȡ�8�ֽڶ��룬����Ϊ������������
 bit[2:0]    ������
   UNION�ṹ:  DBG_DMA_DBG_DS_CFG_UNION */
#define DBG_DMA_DBG_DS_CFG_ADDR                       (SOC_BBP_DBG_BASE_ADDR + 0x428C)

/* �Ĵ���˵������ά�ɲ�buffer��дָ����ʼ��ַ�Ĵ���
 bit[31:2]   ��ά�ɲ�ͨ��bufferдָ����ʼ��ַ����ŵ���LOG 0ͨ����дָ�룬�������ΰ��չ̶���ʽ�������LOGͨ��������ͨ��ָ�롣4�ֽڶ��롣
 bit[1:0]    ������
   UNION�ṹ:  DBG_DMA_DBG_PTR_ADDR_UNION */
#define DBG_DMA_DBG_PTR_ADDR_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x4290)

/* �Ĵ���˵������ά�ɲ�ͨ������ʹ�ܼĴ���
 bit[31:1]   ������
 bit[0]      ����ͨ��ʹ�ܡ�
             0����ʹ�ܣ�
             1��ʹ�ܡ�
   UNION�ṹ:  DBG_DMA_DBG_DS_CH_EN_UNION */
#define DBG_DMA_DBG_DS_CH_EN_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x4294)

/* �Ĵ���˵������ά�ɲ�ͨ��״̬�Ĵ���0
 bit[31:30]  ������
 bit[29]     ����ͨ�������쳣ָʾ��ָʾʵ�ʰ����ȴ��ڰ�ͷ������ָʾ�İ�����д1�����
             0�����쳣��
             1���쳣��
 bit[28:23]  ������
 bit[22]     LOG1ͨ�������쳣ָʾ��ָʾʵ�ʰ����ȴ��ڰ�ͷ������ָʾ�İ�����д1�����
             0�����쳣��
             1���쳣��
 bit[21]     LOG0ͨ�������쳣ָʾ��ָʾʵ�ʰ����ȴ��ڰ�ͷ������ָʾ�İ�����д1�����
             0�����쳣��
             1���쳣��
 bit[20]     ����ͨ����ͷ����βָʾ��ƥ�䡣ÿ�����ݰ������԰�ͷָʾsop��ʼ���԰�βָʾeop��������������յ�sop����eop����״̬�ᴥ����
             0�����쳣��
             1���쳣��
 bit[19:14]  ������
 bit[13]     LOG1ͨ����ͷ����βָʾ��ƥ�䡣
             0�����쳣��
             1���쳣��
 bit[12]     LOG0ͨ����ͷ����βָʾ��ƥ�䡣
             0�����쳣��
             1���쳣��
 bit[11:2]   ������
 bit[1]      LOG1ͨ��buffer���硣
             0�����쳣��
             1���쳣��
 bit[0]      LOG0ͨ��buffer���硣
             0�����쳣��
             1���쳣��
   UNION�ṹ:  DBG_DBG_CH_STS0_UNION */
#define DBG_DBG_CH_STS0_ADDR                          (SOC_BBP_DBG_BASE_ADDR + 0x429C)

/* �Ĵ���˵������ά�ɲ�LOGͨ��ʹ�ܼĴ���
 bit[31:1]   ������
 bit[0]      LOGͨ��ʹ�ܼĴ�����
             0����ʹ�ܣ�
             1��ʹ�ܡ�
   UNION�ṹ:  DBG_DMA_DBG_LOG_CH_EN_UNION */
#define DBG_DMA_DBG_LOG_CH_EN_ADDR                    (SOC_BBP_DBG_BASE_ADDR + 0x42B8)

/* �Ĵ���˵����COMʱ��ʹ��
 bit[31:7]   ����
 bit[6]      dbgʱ��ʹ���źš�ֻд�źţ�д1ʹ��
 bit[5:0]    ����
   UNION�ṹ:  DBG_COM_CLK_EN_UNION */
#define DBG_COM_CLK_EN_ADDR                           (SOC_BBP_DBG_BASE_ADDR + 0xE1FC40E0)

/* �Ĵ���˵����COM��λ���
 bit[31:7]   ����
 bit[6]      dbg��λ����źš�ֻд�źţ�д1ʹ������
 bit[5]      ����
 bit[4]      sdr��λ����źš�ֻд�źţ�д1ʹ������
 bit[3:0]    ����
   UNION�ṹ:  DBG_COM_SRST_DIS_UNION */
#define DBG_COM_SRST_DIS_ADDR                         (SOC_BBP_DBG_BASE_ADDR + 0xE1FC40F4)

/* �Ĵ���˵����RX��������ѡ��
 bit[31:10]  ����
 bit[9]      �����߲���ʹ���ߵ�ƽ��Ч��
 bit[8]      �����߲���ʹ�ܣ��ߵ�ƽ��Ч��
 bit[7:5]    ����
 bit[4:0]    �������ݰ���ѡ�񣬱�ʾ����λ�á�
             0��ADC����źţ�W��TDS���ã�
             1��spmv������źţ�W��TDS���ã�
             2��dcoc����źţ���TDSʹ�ã�
             3��dgt1����źţ���TDSʹ�ã�
             4��fir����źţ�W��TDS���ã�
             5��rxiq����źţ�W��TDS���ã�
             6��dwf����źţ�W��TDS���ã�
             7��codc����źţ�W��TDS��ʹ�ã�
             8��sc_filter����źţ�W��TDS��ʹ�ã�
             9��TDS��rrc����źţ���TDSʹ�ã�
             10��TDS��dgt2����źţ���TDSʹ�ã�
             11��W��rrc����źţ����ز��͸��ز���ʱ���ã�
             12��W��8bitDAGC����źţ����ز��͸��ز���ʱ���ã�
             13��W��4bitDAGC����źţ����ز��͸��ز���ʱ���ã�
             14��dwf�ĸ��ز�����źţ���Wʹ�ã�
             15��sc_filter�ĸ��ز������źţ���Wʹ�ã�
             16��rrc�ĸ��ز������źţ���Wʹ�ã�
             17������Ϊ2047�����ǲ�����Ӧ12bits���ݣ�
             18������Ϊ127�����ǲ�����Ӧ8bit���ݣ�
             19��Ƶ��У��freq_error�������12bitΪ���ݣ�
             20�����ز�FIFO�������12bitΪ���ݣ�
             21�����ز�FIFO�������12bitΪ���ݣ�
             defaultΪȥг���������źš�
             �������ݸ�ʽ��[11:0]Ϊ���ݣ�[12]Ϊ0��ʾ���ز���Ϊ1��ʾ���ز���[13]Ϊ0��ʾ����1��Ϊ1��ʾ����2��
   UNION�ṹ:  DBG_DBG_AGC_DATA_SEL_UNION */
#define DBG_DBG_AGC_DATA_SEL_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0xE19952DC)

/* �Ĵ���˵����TX��������ѡ��
 bit[31:3]   ����
 bit[2:0]    dbg����ѡ��
             3'd0: RRC���������
             3'd1: CFR/FIR���������
             3'd2: PC���������
             3'd3: phase comp�������
             3'd4: Txiq�������
             3'd5:FIFO�������
             3'd6:sc_filter�������
             3'd7:freq_error���������
   UNION�ṹ:  DBG_DBG_DATA_SEL_UNION */
#define DBG_DBG_DATA_SEL_ADDR                         (SOC_BBP_DBG_BASE_ADDR + 0xE19A2814)

/* �Ĵ���˵����ʹ�ܼĴ���
 bit[31:16]  ��ά�ɲ�İ�����
 bit[15:2]   ����
 bit[1]      ��ά�ɲ������ϱ�ģʽ��
             'b0���������������dbg_pkg_num�����ݰ����Զ�������
             'b1��ֻҪdbg_enΪ1���ϱ���û���ϱ��������ơ�
 bit[0]      ��ά�ɲ�ʹ���źţ���dbg_rpt_modeΪ0ʱ�߼����壬������Ҫд�塣
             1'b0����ά�ɲ⹦�ܲ�ʹ��1'b1����ά�ɲ⹦��ʹ��
   UNION�ṹ:  DBG_DBG_EN_UNION */
#define DBG_DBG_EN_ADDR                               (SOC_BBP_DBG_BASE_ADDR + 0x4708)

/* �Ĵ���˵����ID�Ĵ���
   ��      ������ά�ɲ��ϱ����ݰ�ID�Ż�ַ
   UNION�ṹ ���� */
#define DBG_DBG_ID_ADDR                               (SOC_BBP_DBG_BASE_ADDR + 0x470C)

/* �Ĵ���˵��������ѡ��Ĵ���
 bit[31:16]  ����
 bit[15:0]   ��ά�ɲ��ڲ�����ָʾ��
             1���ϱ�mipi����
             2���ϱ�ssi����
             3������dbg�ϱ�����
             ����������
   UNION�ṹ:  DBG_DBG_FLT_UNION */
#define DBG_DBG_FLT_ADDR                              (SOC_BBP_DBG_BASE_ADDR + 0x4710)

/* �Ĵ���˵����mipiͨ��ѡ��Ĵ���
 bit[31:4]   ����
 bit[3:0]    ��ά�ɲ�mipi�ɼ�����ͨ������ָʾ��
             dbg_mipi_ch_mask[X],X=0~3,��
             0��ͨ��X��mipi���ݲ��ɼ�
             1���ɼ�ͨ��X��mipi����
   UNION�ṹ:  DBG_DBG_MIPI_CH_MASK_UNION */
#define DBG_DBG_MIPI_CH_MASK_ADDR                     (SOC_BBP_DBG_BASE_ADDR + 0x4714)

/* �Ĵ���˵����ssiͨ��ѡ��Ĵ���
 bit[31:4]   ����
 bit[3:0]    ��ά�ɲ�ssi�ɼ�����ͨ������ָʾ��
             dbg_ssi_ch_mask[X],X=0~3,��
             0��ͨ��X��ssi���ݲ��ɼ�
             1���ɼ�ͨ��X��ssi����
   UNION�ṹ:  DBG_DBG_SSI_CH_MASK_UNION */
#define DBG_DBG_SSI_CH_MASK_ADDR                      (SOC_BBP_DBG_BASE_ADDR + 0x4718)

/* �Ĵ���˵��������ģʽ�Ĵ�����
 bit[7]      ���ֲ���TXͨ����λ�źţ�
             0������λ(Ĭ��)
             1����λ
 bit[6]      ���ֲ���RXͨ����λ�źţ�
             0������λ(Ĭ��)
             1����λ
 bit[5:3]    bit[4:3]����ģʽ���ƣ�
             00������ģʽ(Ĭ��)
             01�������㷨�߼�����ģʽ
             10��RXģ�����ģʽ(bypass RX�����˲���)
             11���ӿڻ���
             bit[5]Reserved
 bit[2:1]    RXģ�����ģʽ��ͨ��ѡ��
             00�����RXA Iģ�����������(Ĭ��)
             01�����RXA Qģ�����������
             10�����RXB Iģ�����������
             11�����RXB Qģ�����������
 bit[0]      ȫ����λ�źţ�
             0������λ(Ĭ��)
             1����λ�������ֵ�·��ģ���·
   UNION�ṹ:  DBG_ch1_testmode_UNION */
#define DBG_ch1_testmode_ADDR                         (SOC_BBP_DBG_BASE_ADDR + 0xE1FA4104)

/* �Ĵ���˵��������ģʽ�Ĵ�����
 bit[7]      ���ֲ���TXͨ����λ�źţ�
             0������λ(Ĭ��)
             1����λ
 bit[6]      ���ֲ���RXͨ����λ�źţ�
             0������λ(Ĭ��)
             1����λ
 bit[5:3]    bit[4:3]����ģʽ���ƣ�
             00������ģʽ(Ĭ��)
             01�������㷨�߼�����ģʽ
             10��RXģ�����ģʽ(bypass RX�����˲���)
             11���ӿڻ���
             bit[5] debug_en��
             1��ʹ�ܣ���debug�ź�ͨ���ܽŸ��ó�ȥ��
             0����ʹ�ܡ�
 bit[2:1]    RXģ�����ģʽ��ͨ��ѡ��
             00�����RXA Iģ�����������(Ĭ��)
             01�����RXA Qģ�����������
             10�����RXB Iģ�����������
             11�����RXB Qģ�����������
 bit[0]      ȫ����λ�źţ�
             0������λ(Ĭ��)
             1����λ�������ֵ�·��ģ���·
   UNION�ṹ:  DBG_ch0_testmode_UNION */
#define DBG_ch0_testmode_ADDR                         (SOC_BBP_DBG_BASE_ADDR + 0xE1FA4284)





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
                     (1/1) register_define_BBP_DBG
 ***======================================================================***/
/*****************************************************************************
 �ṹ��    : DBG_DBG_SRST_UNION
 �ṹ˵��  : DBG_SRST �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��λ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_srst_reg;
    struct
    {
        unsigned int  dbg_srst    : 1;  /* bit[0]   : dbgģ����λ�źš���λDBG��tl_dbgģ��
                                                      1����ʾ��λ
                                                      0����ʾ�帴λ */
        unsigned int  sdr_srst    : 1;  /* bit[1]   : sdrģ����λ�źš���λSDRͨ·�߼���·������dbg_reg��
                                                      1����ʾ��λ
                                                      0����ʾ�帴λ */
        unsigned int  reserved    : 6;  /* bit[2-7] : ������ */
        unsigned int  dbg_ver_num : 24; /* bit[8-31]: dbgģ��汾�š�
                                                      �ɷ���ʱ���ʾ��bit31~24��ʾ�꣬bit23~16��ʾ�£�bit15~8��ʾ�ա���2012��5��20�հ汾���汾��Ϊ��0x120520 */
    } reg;
} DBG_DBG_SRST_UNION;
#define DBG_DBG_SRST_dbg_srst_START     (0)
#define DBG_DBG_SRST_dbg_srst_END       (0)
#define DBG_DBG_SRST_sdr_srst_START     (1)
#define DBG_DBG_SRST_sdr_srst_END       (1)
#define DBG_DBG_SRST_dbg_ver_num_START  (8)
#define DBG_DBG_SRST_dbg_ver_num_END    (31)


/*****************************************************************************
 �ṹ��    : DBG_DBG_GATE_UNION
 �ṹ˵��  : DBG_GATE �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000B0F�����:32
 �Ĵ���˵��: ʱ���ſؼĴ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_gate_reg;
    struct
    {
        unsigned int  dbg_high_id       : 4;  /* bit[0-3]  : DBG���ݵ�DMAͨ��8λIDֵ�ĸ�4λIDָʾ��
                                                             DBGȱʡֵ=4'hF��
                                                             Bus����ID=0xF8��
                                                             Dat����ID=0xF9��
                                                             Log����ID=0xFA�� */
        unsigned int  dbg_bus_dmach_sel : 1;  /* bit[4]    : Bus���ݵ�DMAͨ�������IDѡ��
                                                             0��Bus���ݵ�DMAͨ��ID���֣�ID=F8��(ȱʡֵ)����
                                                             1��Bus���ݱ��ΪDMA��Dataͨ��IDѡ��ID=0xF9�������������������������������� */
        unsigned int  reserved_0        : 3;  /* bit[5-7]  : ������ */
        unsigned int  gux_lsrv_id       : 4;  /* bit[8-11] : Service ID��GUX SSID��Ϣ������Ϣ��
                                                             ����ֵΪ��0xB */
        unsigned int  dbg_gate_sel      : 1;  /* bit[12]   : ģ��RAMʱ���ſ�ѡ���źš�
                                                             0��ʱ���ſ���Ч���ſؿ�����(ȱʡֵ)����
                                                             1��ʱ���ſ���Ч���ſعرա������������������������������� */
        unsigned int  reserved_1        : 19; /* bit[13-31]: ������ */
    } reg;
} DBG_DBG_GATE_UNION;
#define DBG_DBG_GATE_dbg_high_id_START        (0)
#define DBG_DBG_GATE_dbg_high_id_END          (3)
#define DBG_DBG_GATE_dbg_bus_dmach_sel_START  (4)
#define DBG_DBG_GATE_dbg_bus_dmach_sel_END    (4)
#define DBG_DBG_GATE_gux_lsrv_id_START        (8)
#define DBG_DBG_GATE_gux_lsrv_id_END          (11)
#define DBG_DBG_GATE_dbg_gate_sel_START       (12)
#define DBG_DBG_GATE_dbg_gate_sel_END         (12)


/*****************************************************************************
 �ṹ��    : DBG_DBG_SRV_ID_UNION
 �ṹ˵��  : DBG_SRV_ID �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x03014802�����:32
 �Ĵ���˵��: ����֡ͷ���üĴ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_srv_id_reg;
    struct
    {
        unsigned int  hsrv_id     : 8;  /* bit[0-7]  : Service ID��SID��Ϣ������Ϣ��
                                                       ����ֵΪ��0x02 */
        unsigned int  tds_lsrv_id : 4;  /* bit[8-11] : Service ID��TDS SSID��Ϣ������Ϣ��
                                                       ����ֵΪ��0x8 */
        unsigned int  lte_lsrv_id : 4;  /* bit[12-15]: Service ID��LTE SSID��Ϣ������Ϣ��
                                                       ����ֵΪ��0x4 */
        unsigned int  session_id  : 8;  /* bit[16-23]: Session ID������Ϣ��
                                                       ����ֵΪ��0x01���������������������� */
        unsigned int  msg_type    : 8;  /* bit[24-31]: ��Ϣ����������Ϣ��
                                                       ����ֵΪ��0x03 */
    } reg;
} DBG_DBG_SRV_ID_UNION;
#define DBG_DBG_SRV_ID_hsrv_id_START      (0)
#define DBG_DBG_SRV_ID_hsrv_id_END        (7)
#define DBG_DBG_SRV_ID_tds_lsrv_id_START  (8)
#define DBG_DBG_SRV_ID_tds_lsrv_id_END    (11)
#define DBG_DBG_SRV_ID_lte_lsrv_id_START  (12)
#define DBG_DBG_SRV_ID_lte_lsrv_id_END    (15)
#define DBG_DBG_SRV_ID_session_id_START   (16)
#define DBG_DBG_SRV_ID_session_id_END     (23)
#define DBG_DBG_SRV_ID_msg_type_START     (24)
#define DBG_DBG_SRV_ID_msg_type_END       (31)


/*****************************************************************************
 �ṹ��    : DBG_DBG_FRM_LEN_UNION
 �ṹ˵��  : DBG_FRM_LEN �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x08000800�����:32
 �Ĵ���˵��: ����֡���ȼĴ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_frm_len_reg;
    struct
    {
        unsigned int  bus_frm_len  : 16; /* bit[0-15] : BUS��д����֡��������Ϣ��
                                                        ����֡��������ϰ�ͷ��Service ID�Ȱ�ͷ��Ϣ����λΪbyte��
                                                        ��ѡ֡������ֵ�У�
                                                        0x0800(2048byte)(ȱʡֵ)��
                                                        0x0200(512byte)��
                                                        0x0400(1024byte)�������������������������� */
        unsigned int  data_frm_len : 16; /* bit[16-31]: ��������֡��������Ϣ��
                                                        ����֡��������ϰ�ͷ��Service ID�Ȱ�ͷ��Ϣ����λΪbyte��
                                                        ��ѡ֡������ֵ�У�
                                                        0x0800(2048byte)(ȱʡֵ)��
                                                        0x0200(512byte)��(ֻ֧��ASIC�汾)
                                                        0x0400(1024byte)(ֻ֧��ASIC�汾) */
    } reg;
} DBG_DBG_FRM_LEN_UNION;
#define DBG_DBG_FRM_LEN_bus_frm_len_START   (0)
#define DBG_DBG_FRM_LEN_bus_frm_len_END     (15)
#define DBG_DBG_FRM_LEN_data_frm_len_START  (16)
#define DBG_DBG_FRM_LEN_data_frm_len_END    (31)


/*****************************************************************************
 �ṹ��    : DBG_LTE_BUS_SEL_UNION
 �ṹ˵��  : LTE_BUS_SEL �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00000000�����:32
 �Ĵ���˵��: LTE BUS�ɼ�����ѡ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      lte_bus_sel_reg;
    struct
    {
        unsigned int  lte_bus_pb_sel   : 1;  /* bit[0]    : LTE pbģ���BUS����ѡ���źš�(0x40_0000~0x4f_ffff)
                                                            0����ѡ��1��ѡ�� */
        unsigned int  lte_bus_rfin_sel : 1;  /* bit[1]    : LTE rfinģ���BUS����ѡ���źš�(0x00_0000~0x0f_ffff)
                                                            0����ѡ��1��ѡ�� */
        unsigned int  lte_bus_fpu_sel  : 1;  /* bit[2]    : LTE fpuģ���BUS����ѡ���źš�(0x10_0000~0x1f_ffff)
                                                            0����ѡ��1��ѡ�� */
        unsigned int  lte_bus_ul_sel   : 1;  /* bit[3]    : LTE ulģ���BUS����ѡ���źš�(0x60_0000~0x6f_ffff)
                                                            0����ѡ��1��ѡ�� */
        unsigned int  lte_bus_cqi_sel  : 1;  /* bit[4]    : LTE cqiģ���BUS����ѡ���źš�(0xa0_0000~0xaf_ffff)
                                                            0����ѡ��1��ѡ�� */
        unsigned int  lte_bus_vdl_sel  : 1;  /* bit[5]    : LTE vdlģ���BUS����ѡ���źš�(0x50_0000~0x5f_ffff)
                                                            0����ѡ��1��ѡ�� */
        unsigned int  lte_bus_pdu_sel  : 1;  /* bit[6]    : LTE pduģ���BUS���ݲɼ�ѡ���źš�(0xb0_0000~0xbf_ffff)
                                                            0����ѡ��1��ѡ�� */
        unsigned int  lte_bus_tdl_sel  : 1;  /* bit[7]    : LTE tdlģ���BUS���ݲɼ�ѡ���źš�(0xc0_0000~0xcf_ffff)
                                                            0����ѡ��1��ѡ�� */
        unsigned int  reserved         : 2;  /* bit[8-9]  : ������ */
        unsigned int  u1_bus_sel       : 1;  /* bit[10]   : U1ģ���BUS���ݲɼ�ʹ���ź�(ԭUMSTģʽ)��
                                                            0����ѡ��1��ѡ��
                                                            cm_timing��ck_mem��drx_2msģ��(0x90_1000~0x90_1fff)�� */
        unsigned int  gsm1_bus_sel     : 1;  /* bit[11]   : GSM1ģ���BUS���ݲɼ�ѡ���ź�(ԭGSMģʽ)��
                                                            0����ʹ�ܣ�1��ʹ�ܡ�
                                                            gtc_mem��reg_1ģ��(0x80_0000~0x80_1fff)�� */
        unsigned int  bus_dma_sel      : 1;  /* bit[12]   : DMA(sctrl��dbg��dbg_trig��dma)ģ���BUS���ݲɼ�ѡ���źš�
                                                            0����ѡ��1��ѡ��
                                                            ��ַ��0xfc_0000~0xfc_ffff�� */
        unsigned int  bus_dbg_sel      : 1;  /* bit[13]   : ����(ԭdbgģ��)�� */
        unsigned int  lte_bus_top_sel  : 1;  /* bit[14]   : LTE top(int��stu��crg)ģ���BUS���ݲɼ�ѡ���źš�(0x70_0000~0x7f_ffff)
                                                            0����ѡ��1��ѡ�� */
        unsigned int  bus_com_sel      : 1;  /* bit[15]   : COM(ctu��irm/gu_bbp_mst��et��abb)ģ���BUS���ݲɼ�ѡ���źš�
                                                            0����ѡ��1��ѡ��
                                                            ��ַ��0xf8_0000~0xf8_7fff��0xf8_8000~0xf8_ffff��0xf9_0000~0xf9_7fff��0xfa_0000~0xfa_7fff�� */
        unsigned int  dbg_bus_msk      : 2;  /* bit[16-17]: DBG_BUS��д���������źš�
                                                            0��ʹ��BUS������
                                                            1������BUS������
                                                            bit16:�����������źţ�
                                                            bit17:д���������źš� */
        unsigned int  u1_bus_sel2      : 5;  /* bit[18-22]: U1ģ���BUS���ݲɼ�ʹ���źš�
                                                            0����ʹ�ܣ�1��ʹ�ܡ�
                                                            bit18��mp��mp_rpt_mem��cs��cs_rpt_mem��rf_ctrlģ��(0x90_2000~0x90_3fff)��
                                                            bit19��dldem��pcģ��(0x90_4000~0x90_4fff��0x90_6000~0x90_6fff)��
                                                            bit20��ul��ulcode_para_memģ��(0x90_c000~0x90_cfff��0x90_e000~0x90_efff)��
                                                            bit21��lmmse��lmmse_mem��dldec_dpa��dldec_para_mem��dldec_dbg_rpt_mem��dldec_dpa_rpt_headģ��(0x90_8000~0x90_bfff)��
                                                            bit22��dldec_r99_dc��lmmse_dc��lmmse_mem_dc��dldec_dpa_dc��dldec_dbg_rpt_dc_mem��dldec_dpa_rpt_head_dc��ul_dcģ��(0x92_7000~0x92_cfff)�� */
        unsigned int  gsm1_bus_sel2    : 4;  /* bit[23-26]: GSM1ģ���BUS���ݲɼ�ѡ���źš�
                                                            0����ѡ��1��ѡ��
                                                            bit23��dec_rpt_mem��apc_mem��tsc_mem��ulcode_data_mem��reg_2ģ��(0x80_2000~0x80_3fff)��
                                                            bit24��reg_3��dldem_mem1��dldem_mem2��dldem_mem3ģ��(0x80_4000~0x80_5fff)��
                                                            bit25��agc_mem1��agc_mem2��gck_memģ��(0x80_6000~0x80_7fff)��
                                                            bit26��fe_ctrl_mem��fe_ctrl��reg_4ģ��(0x80_8000~0x80_ffff)�� */
        unsigned int  gsm2_bus_sel     : 5;  /* bit[27-31]: GSM2ģ���BUS���ݲɼ�ѡ���źš�
                                                            0����ѡ��1��ѡ��
                                                            bit27��gtc_mem��reg_1ģ��(0x88_0000~0x88_1fff)��
                                                            bit28��dec_rpt_mem��apc_mem��tsc_mem��ulcode_data_mem��reg_2ģ��(0x88_2000~0x88_3fff)��
                                                            bit29��reg_3��dldem_mem1��dldem_mem2��dldem_mem3ģ��(0x88_4000~0x88_5fff)��
                                                            bit30��agc_mem1��agc_mem2��gck_memģ��(0x880_6000~0x88_7fff)��
                                                            bit31��fe_ctrl_mem��fe_ctrl��reg_4ģ��(0x88_8000~0x88_ffff)�� */
    } reg;
} DBG_LTE_BUS_SEL_UNION;
#define DBG_LTE_BUS_SEL_lte_bus_pb_sel_START    (0)
#define DBG_LTE_BUS_SEL_lte_bus_pb_sel_END      (0)
#define DBG_LTE_BUS_SEL_lte_bus_rfin_sel_START  (1)
#define DBG_LTE_BUS_SEL_lte_bus_rfin_sel_END    (1)
#define DBG_LTE_BUS_SEL_lte_bus_fpu_sel_START   (2)
#define DBG_LTE_BUS_SEL_lte_bus_fpu_sel_END     (2)
#define DBG_LTE_BUS_SEL_lte_bus_ul_sel_START    (3)
#define DBG_LTE_BUS_SEL_lte_bus_ul_sel_END      (3)
#define DBG_LTE_BUS_SEL_lte_bus_cqi_sel_START   (4)
#define DBG_LTE_BUS_SEL_lte_bus_cqi_sel_END     (4)
#define DBG_LTE_BUS_SEL_lte_bus_vdl_sel_START   (5)
#define DBG_LTE_BUS_SEL_lte_bus_vdl_sel_END     (5)
#define DBG_LTE_BUS_SEL_lte_bus_pdu_sel_START   (6)
#define DBG_LTE_BUS_SEL_lte_bus_pdu_sel_END     (6)
#define DBG_LTE_BUS_SEL_lte_bus_tdl_sel_START   (7)
#define DBG_LTE_BUS_SEL_lte_bus_tdl_sel_END     (7)
#define DBG_LTE_BUS_SEL_u1_bus_sel_START        (10)
#define DBG_LTE_BUS_SEL_u1_bus_sel_END          (10)
#define DBG_LTE_BUS_SEL_gsm1_bus_sel_START      (11)
#define DBG_LTE_BUS_SEL_gsm1_bus_sel_END        (11)
#define DBG_LTE_BUS_SEL_bus_dma_sel_START       (12)
#define DBG_LTE_BUS_SEL_bus_dma_sel_END         (12)
#define DBG_LTE_BUS_SEL_bus_dbg_sel_START       (13)
#define DBG_LTE_BUS_SEL_bus_dbg_sel_END         (13)
#define DBG_LTE_BUS_SEL_lte_bus_top_sel_START   (14)
#define DBG_LTE_BUS_SEL_lte_bus_top_sel_END     (14)
#define DBG_LTE_BUS_SEL_bus_com_sel_START       (15)
#define DBG_LTE_BUS_SEL_bus_com_sel_END         (15)
#define DBG_LTE_BUS_SEL_dbg_bus_msk_START       (16)
#define DBG_LTE_BUS_SEL_dbg_bus_msk_END         (17)
#define DBG_LTE_BUS_SEL_u1_bus_sel2_START       (18)
#define DBG_LTE_BUS_SEL_u1_bus_sel2_END         (22)
#define DBG_LTE_BUS_SEL_gsm1_bus_sel2_START     (23)
#define DBG_LTE_BUS_SEL_gsm1_bus_sel2_END       (26)
#define DBG_LTE_BUS_SEL_gsm2_bus_sel_START      (27)
#define DBG_LTE_BUS_SEL_gsm2_bus_sel_END        (31)


/*****************************************************************************
 �ṹ��    : DBG_TDS_BUS_SEL_UNION
 �ṹ˵��  : TDS_BUS_SEL �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x00000000�����:32
 �Ĵ���˵��: TDS BUS�ɼ�����ѡ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_bus_sel_reg;
    struct
    {
        unsigned int  tds_bus_sel      : 11; /* bit[0-10] : TDS ģ���BUS���ݲɼ�ѡ���źš�
                                                            0����ѡ��1��ѡ��
                                                            bit0��stuģ���BUS�ɼ�ѡ���źţ�(0xd0_0000~0xd0_3fff)
                                                            bit1��������
                                                            bit2��rfcģ���BUS�ɼ�ѡ���źţ�(0xd0_4000~0xd0_5fff)
                                                            bit3��wtc1_comģ���BUSѡ���ź�(ԭviterbiģ��)��
                                                            int��cpc_drx��fe_ctrl_mem��fe_ctrl(0x0x90_0000~0x90_0fff)��
                                                            dldec_r99_para_mem��dldec_r99_reg1��dldec_r99_vtb_head��dldec_r99_vtb_rpt_mem��dldec_r99_turbo_head��dldec_r99_turbo_rpt_mem��dldec_r99_reg2(0x90_7000~0x90_7fff)��
                                                            bit4��hsupaģ���BUS�ɼ�ѡ���źţ�(0xe1_0000~0xe1_3fff)
                                                            bit5��turboģ���BUS�ɼ�ѡ���źţ�(0xe2_0000~0xe2_7fff)
                                                            bit6��topģ���BUS�ɼ�ѡ���źţ�(0xe2_8000~0xe2_ffff)
                                                            bit7��harq_regģ���BUS�ɼ�ѡ���źţ�(0xe3_0000~0xe3_ffff)
                                                            bit8��wtc1_feģ���BUSѡ���ź�(ԭtds agcd(own)ģ��)��
                                                            dl_fe��dl_fe_dc��dl_fe_mctrl��wc_dump��wc_dump_mem��ul_fe_mem��w_pa_pd��w_pa_pd_mem��ul_fe(0x0x99_0000~0x99_ffff)��
                                                            bit9������(ԭtds agcc(ommon)ģ��)��
                                                            bit10������(ԭtds agcu(p)ģ��)�� */
        unsigned int  reserved_0       : 1;  /* bit[11]   : ������ */
        unsigned int  u2_bus_sel       : 4;  /* bit[12-15]: U2ģ���BUS���ݲɼ�ʹ���źš�
                                                            0����ʹ�ܣ�1��ʹ�ܡ�
                                                            bit12��cm_timing��ck_mem��drx_2msģ��(0x20_1000~0x20_1fff)��
                                                            bit13��mp��mp_rpt_mem��cs��cs_rpt_mem��rf_ctrlģ��(0x20_2000~0x20_3fff)��
                                                            bit14��dldem��pcģ��(0x20_4000~0x20_4fff��0x20_6000~0x20_6fff)��
                                                            bit15��ul��ulcode_para_memģ��(0x20_c000~0x20_cfff��0x20_e000~0x20_efff)�� */
        unsigned int  c1_bus_sel       : 6;  /* bit[16-21]: C1ģ���BUS���ݲɼ�ѡ���źš�
                                                            0����ѡ��
                                                            1��ѡ��
                                                            bit16��glbģ��(0x9e_0000~0x9e_0fff)��
                                                            bit17��timing_intģ��(0x9e_1000~0x9e_1fff)��
                                                            bit18��mps_csģ��(0x9e_2000~0x9e_2fff)��
                                                            bit19��dldecģ��(0x9e_4000~0x9e_4fff)��
                                                            bit20��ulcodeģ��(0x9e_b000~0x9e_bfff)��
                                                            bit21��fe_ctrl��ssi_mem��mipi_mem��gpio_mem��hkadc_memģ��(0x9e_f000~0x9e_ffff)�� */
        unsigned int  reserved_1       : 2;  /* bit[22-23]: ������ */
        unsigned int  wtc2_com_bus_sel : 1;  /* bit[24]   : WTC2 COMģ���BUS���ݲɼ�ѡ���źš�
                                                            0����ѡ��
                                                            1��ѡ��
                                                            ����ģ�飺
                                                            int��fe_ctrl_mem��fe_ctrl(0x0x20_0000~0x20_0fff)��
                                                            dldec_r99_para_mem��dldec_r99_reg1��dldec_r99_vtb_head��dldec_r99_vtb_rpt_mem��dldec_r99_turbo_head��dldec_r99_turbo_rpt_mem��dldec_r99_reg2(0x20_7000~0x20_7fff)�� */
        unsigned int  wtc2_fe_bus_sel  : 1;  /* bit[25]   : WTC2 FEģ���BUS���ݲɼ�ѡ���źš�
                                                            0����ѡ��
                                                            1��ѡ��
                                                            ����ģ�飺
                                                            dl_fe��dl_fe_dc��dl_fe_mctrl��wc_dump��wc_dump_mem��ul_fe_mem��w_pa_pd��w_pa_pd_mem��ul_fe(0x0x29_0000~0x29_ffff)�� */
        unsigned int  c2_bus_sel       : 6;  /* bit[26-31]: C2ģ���BUS���ݲɼ�ѡ���źš�
                                                            0����ѡ��
                                                            1��ѡ��
                                                            bit26��glbģ��(0x2e_0000~0x2e_0fff)��
                                                            bit27��timing_intģ��(0x2e_1000~0x2e_1fff)��
                                                            bit28��mps_csģ��(0x2e_2000~0x2e_2fff)��
                                                            bit29��dldecģ��(0x2e_4000~0x2e_4fff)��
                                                            bit30��ulcodeģ��(0x2e_b000~0x2e_bfff)��
                                                            bit31��fe_ctrl��ssi_mem��mipi_mem��gpio_mem��hkadc_memģ��(0x2e_f000~0x2e_ffff)�� */
    } reg;
} DBG_TDS_BUS_SEL_UNION;
#define DBG_TDS_BUS_SEL_tds_bus_sel_START       (0)
#define DBG_TDS_BUS_SEL_tds_bus_sel_END         (10)
#define DBG_TDS_BUS_SEL_u2_bus_sel_START        (12)
#define DBG_TDS_BUS_SEL_u2_bus_sel_END          (15)
#define DBG_TDS_BUS_SEL_c1_bus_sel_START        (16)
#define DBG_TDS_BUS_SEL_c1_bus_sel_END          (21)
#define DBG_TDS_BUS_SEL_wtc2_com_bus_sel_START  (24)
#define DBG_TDS_BUS_SEL_wtc2_com_bus_sel_END    (24)
#define DBG_TDS_BUS_SEL_wtc2_fe_bus_sel_START   (25)
#define DBG_TDS_BUS_SEL_wtc2_fe_bus_sel_END     (25)
#define DBG_TDS_BUS_SEL_c2_bus_sel_START        (26)
#define DBG_TDS_BUS_SEL_c2_bus_sel_END          (31)


/*****************************************************************************
 �ṹ��    : DBG_DBG_BUS_EN_UNION
 �ṹ˵��  : DBG_BUS_EN �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00000000�����:32
 �Ĵ���˵��: BUS����ʹ�ܼĴ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_bus_en_reg;
    struct
    {
        unsigned int  dbg_bus_en : 1;  /* bit[0]   : BUS���ݲ���ʹ���źš�
                                                     0����ʹ�ܣ�
                                                     1��ʹ�ܡ� */
        unsigned int  reserved   : 31; /* bit[1-31]: ������ */
    } reg;
} DBG_DBG_BUS_EN_UNION;
#define DBG_DBG_BUS_EN_dbg_bus_en_START  (0)
#define DBG_DBG_BUS_EN_dbg_bus_en_END    (0)


/*****************************************************************************
 �ṹ��    : DBG_DBG_DAT_SEL_UNION
 �ṹ˵��  : DBG_DAT_SEL �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x00000000�����:32
 �Ĵ���˵��: DATͨ��ѡ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_dat_sel_reg;
    struct
    {
        unsigned int  dbg_dat_sel  : 4;  /* bit[0-3]  : DBGģ���ϱ�dat��������ѡ��
                                                        0��RFIN�ϱ���dat����(ȱʡֵ)
                                                        1��FPU�ϱ���dat����
                                                        2��CQI�ϱ���dat����
                                                        3��PDU�ϱ���dat����
                                                        4��TDS�ϱ���dat����
                                                        5��ABB�ϱ�����ͨ��dat����(��֧��FPGA�汾)
                                                        6��ABB�ϱ�����ͨ��dat����(��֧��FPGA�汾)
                                                        7��ABB�ϱ�ģ��ͨ��dat����(��֧��FPGA�汾)
                                                        8��BBP COMMON�ϱ���dat����
                                                        15~9������ */
        unsigned int  tds_type_sel : 3;  /* bit[4-6]  : TDS��������ѡ��Ĵ�����
                                                        ��DAT ID��ַ���ʹ�á�
                                                        1����������0���ݲɼ���      ID=0x41000801��
                                                        2����������1���ݲɼ���      ID=0x41000802��
                                                        3������˫�������ݲɼ���     ID=0x41000803��
                                                        4���������ݲɼ�����         ID=0x41000804��
                                                        5������+��������0���ݲɼ��� ID=0x41000805��
                                                        6������+��������1���ݲɼ��� ID=0x41000806��
                                                        7������+����˫�������ݲɼ���ID=0x41000807��
                                                        ������������ */
        unsigned int  reserved_0   : 1;  /* bit[7]    : ������ */
        unsigned int  dbg_abb_sel  : 2;  /* bit[8-9]  : ABB ch0/1ͨ��ѡ���źţ���ABB����ʹ�����ʹ�á�
                                                        0��ѡ��ch1ͨ����
                                                        1��ѡ��ch0ͨ����
                                                        2��ѡ��ch0/1ͨ���Ĳ���CA��ABB����ѡ���������� */
        unsigned int  reserved_1   : 22; /* bit[10-31]: ������ */
    } reg;
} DBG_DBG_DAT_SEL_UNION;
#define DBG_DBG_DAT_SEL_dbg_dat_sel_START   (0)
#define DBG_DBG_DAT_SEL_dbg_dat_sel_END     (3)
#define DBG_DBG_DAT_SEL_tds_type_sel_START  (4)
#define DBG_DBG_DAT_SEL_tds_type_sel_END    (6)
#define DBG_DBG_DAT_SEL_dbg_abb_sel_START   (8)
#define DBG_DBG_DAT_SEL_dbg_abb_sel_END     (9)


/*****************************************************************************
 �ṹ��    : DBG_DBG_DAT_EN_UNION
 �ṹ˵��  : DBG_DAT_EN �Ĵ����ṹ���塣��ַƫ����:0x028����ֵ:0x00000000�����:32
 �Ĵ���˵��: DAT����ʹ�ܼĴ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_dat_en_reg;
    struct
    {
        unsigned int  dbg_dat_en : 1;  /* bit[0]   : DAT���ݲ���ʹ���źš�
                                                     0����ʹ�ܣ�
                                                     1��ʹ�ܡ� */
        unsigned int  reserved   : 31; /* bit[1-31]: ������ */
    } reg;
} DBG_DBG_DAT_EN_UNION;
#define DBG_DBG_DAT_EN_dbg_dat_en_START  (0)
#define DBG_DBG_DAT_EN_dbg_dat_en_END    (0)


/*****************************************************************************
 �ṹ��    : DBG_DBG_LOG_SEL_UNION
 �ṹ˵��  : DBG_LOG_SEL �Ĵ����ṹ���塣��ַƫ����:0x02C����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOGͨ��ѡ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_log_sel_reg;
    struct
    {
        unsigned int  dbg_log_sel : 3;  /* bit[0-2] : DBGģ���ϱ�LOG��������ѡ��
                                                      0������(ȱʡֵ)
                                                      1��FPU�ϱ���log����
                                                      2��PB�ϱ���log����
                                                      3��PDU�ϱ���log����
                                                      4��TDL�ϱ���log����
                                                      5��TDL2�ϱ���log����
                                                      7~6�������������������� */
        unsigned int  reserved    : 29; /* bit[3-31]: ������ */
    } reg;
} DBG_DBG_LOG_SEL_UNION;
#define DBG_DBG_LOG_SEL_dbg_log_sel_START  (0)
#define DBG_DBG_LOG_SEL_dbg_log_sel_END    (2)


/*****************************************************************************
 �ṹ��    : DBG_DBG_LOG_EN_UNION
 �ṹ˵��  : DBG_LOG_EN �Ĵ����ṹ���塣��ַƫ����:0x030����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOGͨ��ʹ�ܼĴ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_log_en_reg;
    struct
    {
        unsigned int  dbg_log_en : 1;  /* bit[0]   : LģLOG���ݴ���ʹ���źš�
                                                     0����ʹ�ܣ�
                                                     1��ʹ�ܡ� */
        unsigned int  reserved   : 31; /* bit[1-31]: ������ */
    } reg;
} DBG_DBG_LOG_EN_UNION;
#define DBG_DBG_LOG_EN_dbg_log_en_START  (0)
#define DBG_DBG_LOG_EN_dbg_log_en_END    (0)


/*****************************************************************************
 �ṹ��    : DBG_DBG_TL_SEL_UNION
 �ṹ˵��  : DBG_TL_SEL �Ĵ����ṹ���塣��ַƫ����:0x034����ֵ:0x00000000�����:32
 �Ĵ���˵��: DBG����ͨ��ģʽѡ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_tl_sel_reg;
    struct
    {
        unsigned int  reserved_0     : 4;  /* bit[0-3]  : ������ */
        unsigned int  dbg_ptimer_sel : 4;  /* bit[4-7]  : DBG������ģʱ��ѡ���źš�
                                                          0������(ȱʡֵ)
                                                          1��LTE��
                                                          2��TDS��
                                                          3��UMTS(U1)��
                                                          4��EVDO&1X(X1)��
                                                          5��1X(X2)��
                                                          6��R99(U2)��
                                                          7��GSM1��
                                                          8��GSM2��
                                                          9~15������ */
        unsigned int  dbg_stimer_sel : 4;  /* bit[8-11] : DBG������ģʱ��ѡ���źš�
                                                          0������(ȱʡֵ)
                                                          1��LTE��
                                                          2��TDS��
                                                          3��UMTS(U1)��
                                                          4��EVDO&1X(X1)��
                                                          5��1X(X2)��
                                                          6��R99(U2)��
                                                          7��GSM1��
                                                          8��GSM2��
                                                          9~15������ */
        unsigned int  reserved_1     : 20; /* bit[12-31]: ������ */
    } reg;
} DBG_DBG_TL_SEL_UNION;
#define DBG_DBG_TL_SEL_dbg_ptimer_sel_START  (4)
#define DBG_DBG_TL_SEL_dbg_ptimer_sel_END    (7)
#define DBG_DBG_TL_SEL_dbg_stimer_sel_START  (8)
#define DBG_DBG_TL_SEL_dbg_stimer_sel_END    (11)


/*****************************************************************************
 �ṹ��    : DBG_DBG_DIAG_ALARM_UNION
 �ṹ˵��  : DBG_DIAG_ALARM �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x00000000�����:32
 �Ĵ���˵��: DAT/BUS/LOGͨ���澯�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_diag_alarm_reg;
    struct
    {
        unsigned int  col_data_alarm : 1;  /* bit[0]    : DATA����֡����澯��Ϣ��ֻ������Ӧλд1��0��
                                                          bit0��ͨ��fifo����澯�źš� */
        unsigned int  col_dat_sts    : 4;  /* bit[1-4]  : DATA���ݽӿ�ָʾ��Ϣ��ֻ������Ӧλд1��0
                                                          bit4��dat���ݽ���ָʾ��
                                                          bit3��vld��Чָʾ��
                                                          bit2��eop��Чָʾ��
                                                          bit1��sop��Чָʾ�� */
        unsigned int  reserved_0     : 3;  /* bit[5-7]  : ������ */
        unsigned int  lte_log_alarm  : 4;  /* bit[8-11] : lte��log������澯��Ϣ��ֻ������Ӧλд1��0��
                                                          bit11������֡����С������ֵ���޽�����ʶ�ĸ澯��
                                                          bit10������֡���ݴ�������ֵ�ĸ澯��
                                                          bit9������֡����С������ֵ�ĸ澯��
                                                          bit8��ͨ��fifo����澯�źš� */
        unsigned int  bus_alarm      : 2;  /* bit[12-13]: BUSͨ���澯��Ϣ��ֻ������Ӧλд1��0��
                                                          bit13��burst�����ݳ���澯�źţ�
                                                          bit12��ͨ��fifo����澯�źš� */
        unsigned int  reserved_1     : 18; /* bit[14-31]: ������ */
    } reg;
} DBG_DBG_DIAG_ALARM_UNION;
#define DBG_DBG_DIAG_ALARM_col_data_alarm_START  (0)
#define DBG_DBG_DIAG_ALARM_col_data_alarm_END    (0)
#define DBG_DBG_DIAG_ALARM_col_dat_sts_START     (1)
#define DBG_DBG_DIAG_ALARM_col_dat_sts_END       (4)
#define DBG_DBG_DIAG_ALARM_lte_log_alarm_START   (8)
#define DBG_DBG_DIAG_ALARM_lte_log_alarm_END     (11)
#define DBG_DBG_DIAG_ALARM_bus_alarm_START       (12)
#define DBG_DBG_DIAG_ALARM_bus_alarm_END         (13)


/*****************************************************************************
 �ṹ��    : DBG_DBG_DMA_CNT_UNION
 �ṹ˵��  : DBG_DMA_CNT �Ĵ����ṹ���塣��ַƫ����:0x058����ֵ:0x00000000�����:32
 �Ĵ���˵��: DBG��DMA����/��Ӧ����������
*****************************************************************************/
typedef union
{
    unsigned int      dbg_dma_cnt_reg;
    struct
    {
        unsigned int  dma_req_cnt : 16; /* bit[0-15] : DBG��DMA�ӿڵ�req���������������
                                                       ֻ����16λ��������Test_switch������Ч���ر���0�� */
        unsigned int  dma_gnt_cnt : 16; /* bit[16-31]: DBG��DMA�ӿڵ�gnt��Ӧ������������
                                                       ֻ����16λ��������Test_switch������Ч���ر���0�� */
    } reg;
} DBG_DBG_DMA_CNT_UNION;
#define DBG_DBG_DMA_CNT_dma_req_cnt_START  (0)
#define DBG_DBG_DMA_CNT_dma_req_cnt_END    (15)
#define DBG_DBG_DMA_CNT_dma_gnt_cnt_START  (16)
#define DBG_DBG_DMA_CNT_dma_gnt_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : DBG_DBG_SOP_CNT_UNION
 �ṹ˵��  : DBG_SOP_CNT �Ĵ����ṹ���塣��ַƫ����:0x05C����ֵ:0x00000000�����:32
 �Ĵ���˵��: dbg֡��sop������
*****************************************************************************/
typedef union
{
    unsigned int      dbg_sop_cnt_reg;
    struct
    {
        unsigned int  dat_fifo_max     : 10; /* bit[0-9]  : dat_bstģ��fifo���洢���ݸ�����
                                                            ֻ����10λ�����������ݷ�Χ��0~512��
                                                            ��0x003C��bit3д1��0�� */
        unsigned int  reserved         : 14; /* bit[10-23]: ������ */
        unsigned int  col_subframe_cnt : 8;  /* bit[24-31]: dat���ݵ�sop������������
                                                            ֻ����8λ����������0x003C��bit1д1��0�� */
    } reg;
} DBG_DBG_SOP_CNT_UNION;
#define DBG_DBG_SOP_CNT_dat_fifo_max_START      (0)
#define DBG_DBG_SOP_CNT_dat_fifo_max_END        (9)
#define DBG_DBG_SOP_CNT_col_subframe_cnt_START  (24)
#define DBG_DBG_SOP_CNT_col_subframe_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : DBG_DBG_RAM_CNT_UNION
 �ṹ˵��  : DBG_RAM_CNT �Ĵ����ṹ���塣��ַƫ����:0x068����ֵ:0x00000000�����:32
 �Ĵ���˵��: dbg��ram״̬������
*****************************************************************************/
typedef union
{
    unsigned int      dbg_ram_cnt_reg;
    struct
    {
        unsigned int  dbg_ram_peak_cnt : 13; /* bit[0-12] : ָʾDBGͨ��RAM�ﵽ���洢����(64bit)������
                                                            Test_switch������Ч���ر���0��
                                                            13λ�����������ݷ�Χ��0~4096�� */
        unsigned int  reserved_0       : 3;  /* bit[13-15]: ������ */
        unsigned int  dbg_bst_peak_cnt : 9;  /* bit[16-24]: ָʾDBGͨ��RAM�ﵽ���burst�洢������
                                                            Test_switch������Ч���ر���0��
                                                            9λ�����������ݷ�Χ��0~256�� */
        unsigned int  reserved_1       : 3;  /* bit[25-27]: ������ */
        unsigned int  dbg_ram_empty    : 1;  /* bit[28]   : ָʾDBGͨ��RAMʵʱ�ǿ�״̬��
                                                            0��ramΪ�ա�1��ram�ǿգ� */
        unsigned int  reserved_2       : 3;  /* bit[29-31]: ������ */
    } reg;
} DBG_DBG_RAM_CNT_UNION;
#define DBG_DBG_RAM_CNT_dbg_ram_peak_cnt_START  (0)
#define DBG_DBG_RAM_CNT_dbg_ram_peak_cnt_END    (12)
#define DBG_DBG_RAM_CNT_dbg_bst_peak_cnt_START  (16)
#define DBG_DBG_RAM_CNT_dbg_bst_peak_cnt_END    (24)
#define DBG_DBG_RAM_CNT_dbg_ram_empty_START     (28)
#define DBG_DBG_RAM_CNT_dbg_ram_empty_END       (28)


/*****************************************************************************
 �ṹ��    : DBG_DBG_TIME_CNT_UNION
 �ṹ˵��  : DBG_TIME_CNT �Ĵ����ṹ���塣��ַƫ����:0x06C����ֵ:0x00000000�����:32
 �Ĵ���˵��: dbgͨ��req����Ӧʱ�������
*****************************************************************************/
typedef union
{
    unsigned int      dbg_time_cnt_reg;
    struct
    {
        unsigned int  dbg_gnt_time_cnt : 24; /* bit[0-23] : ָʾDBGͨ��RAM��req/gnt�����ʱ�������
                                                            Test_switch������Ч���ر���0��
                                                            24λ��������ʱ�������ʱ����ء� */
        unsigned int  reserved         : 8;  /* bit[24-31]: ������ */
    } reg;
} DBG_DBG_TIME_CNT_UNION;
#define DBG_DBG_TIME_CNT_dbg_gnt_time_cnt_START  (0)
#define DBG_DBG_TIME_CNT_dbg_gnt_time_cnt_END    (23)


/*****************************************************************************
 �ṹ��    : DBG_DBG_GLB_SEL_UNION
 �ṹ˵��  : DBG_GLB_SEL �Ĵ����ṹ���塣��ַƫ����:0x090����ֵ:0x00000000�����:32
 �Ĵ���˵��: dbg��ͨ��ѡ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_glb_sel_reg;
    struct
    {
        unsigned int  bus_faddr_en       : 1;  /* bit[0]   : BUS������ַ��ģʽ��ʹ���źš�
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ� */
        unsigned int  reserved_0         : 3;  /* bit[1-3] : ������ */
        unsigned int  dbg_tc_msk         : 1;  /* bit[4]   : ��ʱ�����źš�(��֤������)
                                                             0����ʱ��Ϣ�����ɼ��봫�䣻
                                                             1����ʱ��Ϣ�����Σ�ֵ��Ϊ0�� */
        unsigned int  reserved_1         : 3;  /* bit[5-7] : ������ */
        unsigned int  dbg_bus_data_exchg : 1;  /* bit[8]   : DBG��BUS��DATAͨ�����洫��ʹ���źš�
                                                             0����������(ȱʡģʽ)��
                                                             1������ʹ�ܡ� */
        unsigned int  reserved_2         : 23; /* bit[9-31]: ������ */
    } reg;
} DBG_DBG_GLB_SEL_UNION;
#define DBG_DBG_GLB_SEL_bus_faddr_en_START        (0)
#define DBG_DBG_GLB_SEL_bus_faddr_en_END          (0)
#define DBG_DBG_GLB_SEL_dbg_tc_msk_START          (4)
#define DBG_DBG_GLB_SEL_dbg_tc_msk_END            (4)
#define DBG_DBG_GLB_SEL_dbg_bus_data_exchg_START  (8)
#define DBG_DBG_GLB_SEL_dbg_bus_data_exchg_END    (8)


/*****************************************************************************
 �ṹ��    : DBG_BUS_ADDR_VALUE_UNION
 �ṹ˵��  : BUS_ADDR_VALUE �Ĵ����ṹ���塣��ַƫ����:0x094����ֵ:0x00000000�����:32
 �Ĵ���˵��: bus������ʼ��ַ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      bus_addr_value_reg;
    struct
    {
        unsigned int  bus_faddr_value : 24; /* bit[0-23] : BUS������ַ��ģʽ����ʼ��ַ��ѡ��Χ��0~0xffffff */
        unsigned int  reserved        : 8;  /* bit[24-31]: ������ */
    } reg;
} DBG_BUS_ADDR_VALUE_UNION;
#define DBG_BUS_ADDR_VALUE_bus_faddr_value_START  (0)
#define DBG_BUS_ADDR_VALUE_bus_faddr_value_END    (23)


/*****************************************************************************
 �ṹ��    : DBG_BUS_ADDR_SIZE_UNION
 �ṹ˵��  : BUS_ADDR_SIZE �Ĵ����ṹ���塣��ַƫ����:0x098����ֵ:0x00000000�����:32
 �Ĵ���˵��: bus������ַ��Χ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      bus_addr_size_reg;
    struct
    {
        unsigned int  bus_faddr_size : 24; /* bit[0-23] : BUS������ַ��ģʽ��ַ��Χ(��С)��ѡ��Χ��0~0xffffff */
        unsigned int  reserved       : 8;  /* bit[24-31]: ������ */
    } reg;
} DBG_BUS_ADDR_SIZE_UNION;
#define DBG_BUS_ADDR_SIZE_bus_faddr_size_START  (0)
#define DBG_BUS_ADDR_SIZE_bus_faddr_size_END    (23)


/*****************************************************************************
 �ṹ��    : DBG_TDS_DAT_MODE_UNION
 �ṹ˵��  : TDS_DAT_MODE �Ĵ����ṹ���塣��ַƫ����:0x0A8����ֵ:0x00000002�����:32
 �Ĵ���˵��: TDS DAT�ɼ�ģʽѡ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_dat_mode_reg;
    struct
    {
        unsigned int  reserved_0   : 1;  /* bit[0]    : ������ */
        unsigned int  tds_dat_mode : 1;  /* bit[1]    : TDS/ABB DAT�ɼ�ģʽѡ���źš�
                                                        0������ģʽ�������ֵ���ʹ�ã�
                                                        1������ģʽ�� */
        unsigned int  reserved_1   : 14; /* bit[2-15] : ������ */
        unsigned int  tds_dat_frm  : 16; /* bit[16-31]: ����ģʽ��DAT�ɼ�֡������(֧��TDS/ABB) */
    } reg;
} DBG_TDS_DAT_MODE_UNION;
#define DBG_TDS_DAT_MODE_tds_dat_mode_START  (1)
#define DBG_TDS_DAT_MODE_tds_dat_mode_END    (1)
#define DBG_TDS_DAT_MODE_tds_dat_frm_START   (16)
#define DBG_TDS_DAT_MODE_tds_dat_frm_END     (31)


/*****************************************************************************
 �ṹ��    : DBG_DAT_TEST_UNION
 �ṹ˵��  : DAT_TEST �Ĵ����ṹ���塣��ַƫ����:0x0AC����ֵ:0x0000000F�����:32
 �Ĵ���˵��: DAT�������üĴ���
*****************************************************************************/
typedef union
{
    unsigned int      dat_test_reg;
    struct
    {
        unsigned int  dat_test_bandw : 8;  /* bit[0-7]  : DAT�������ݴ��������źš�
                                                          ��ֵΪʱ�Ӽ��������ֵ=F����ÿ��16cycle���ɼ�����1��64bit���ݣ���ʱ��Ƶ��=150MHz����������ݴ���=600Mbps�� */
        unsigned int  dat_test_md    : 2;  /* bit[8-9]  : DAT�������������źš�
                                                          Bit8�������滻ģʽ����ʵ��TDS����ģʽ�£���ȷ���Ĳ��������滻DAT�ӿ����ݣ�����ͨ��������ȷ�ԣ�
                                                          Bit9�����ݲ���ģʽ����Ҫ����ΪTDS����ģʽ���ڲ��������ݽ�������ͨ���������ԣ�
                                                          ������Ϣ��1��Ч�� */
        unsigned int  reserved       : 22; /* bit[10-31]: ������ */
    } reg;
} DBG_DAT_TEST_UNION;
#define DBG_DAT_TEST_dat_test_bandw_START  (0)
#define DBG_DAT_TEST_dat_test_bandw_END    (7)
#define DBG_DAT_TEST_dat_test_md_START     (8)
#define DBG_DAT_TEST_dat_test_md_END       (9)


/*****************************************************************************
 �ṹ��    : DBG_TDS_DAT_STS_UNION
 �ṹ˵��  : TDS_DAT_STS �Ĵ����ṹ���塣��ַƫ����:0x0B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: TDS DAT�ӿ�״̬�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      tds_dat_sts_reg;
    struct
    {
        unsigned int  tds_dat_cfg_err : 1;  /* bit[0]   : TDS DAT�������ô���ָʾ�źš�
                                                          ֻ������Ӧλд1��0�� */
        unsigned int  reserved_0      : 3;  /* bit[1-3] : ������ */
        unsigned int  tds_dat_sts     : 3;  /* bit[4-6] : TDS DAT�ӿ�����״ָ̬ʾ�źš�
                                                          ֻ������Ӧλд1��0��
                                                          Bit4�����е�������������״ָ̬ʾ��
                                                          Bit5������˫������������״ָ̬ʾ��
                                                          Bit6��������������״ָ̬ʾ�� */
        unsigned int  reserved_1      : 25; /* bit[7-31]: ������ */
    } reg;
} DBG_TDS_DAT_STS_UNION;
#define DBG_TDS_DAT_STS_tds_dat_cfg_err_START  (0)
#define DBG_TDS_DAT_STS_tds_dat_cfg_err_END    (0)
#define DBG_TDS_DAT_STS_tds_dat_sts_START      (4)
#define DBG_TDS_DAT_STS_tds_dat_sts_END        (6)


/*****************************************************************************
 �ṹ��    : DBG_DBG_BUS_MODE_UNION
 �ṹ˵��  : DBG_BUS_MODE �Ĵ����ṹ���塣��ַƫ����:0x0C8����ֵ:0x00000002�����:32
 �Ĵ���˵��: DBG BUS�ɼ�ģʽѡ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_bus_mode_reg;
    struct
    {
        unsigned int  reserved_0   : 1;  /* bit[0]    : ������ */
        unsigned int  dbg_bus_mode : 1;  /* bit[1]    : DBG BUS�ɼ�ģʽѡ���źš�
                                                        0������ģʽ�������ֵ���ʹ�ã�
                                                        1������ģʽ�� */
        unsigned int  reserved_1   : 14; /* bit[2-15] : ������ */
        unsigned int  dbg_bus_frm  : 16; /* bit[16-31]: ����ģʽ��BUS�ɼ�֡������ */
    } reg;
} DBG_DBG_BUS_MODE_UNION;
#define DBG_DBG_BUS_MODE_dbg_bus_mode_START  (1)
#define DBG_DBG_BUS_MODE_dbg_bus_mode_END    (1)
#define DBG_DBG_BUS_MODE_dbg_bus_frm_START   (16)
#define DBG_DBG_BUS_MODE_dbg_bus_frm_END     (31)


/*****************************************************************************
 �ṹ��    : DBG_DBG_BUS_TEST_UNION
 �ṹ˵��  : DBG_BUS_TEST �Ĵ����ṹ���塣��ַƫ����:0x0CC����ֵ:0x00000007�����:32
 �Ĵ���˵��: DBG BUS�������üĴ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_bus_test_reg;
    struct
    {
        unsigned int  dbg_bus_test_bandw : 8;  /* bit[0-7] : DBG BUS�������ݴ��������źš�
                                                             ��ֵΪʱ�Ӽ��������ֵ=0x07����ÿ��128cycle(0x7F)���ɼ�����1��64bit���ݣ���ʱ��Ƶ��=150MHz����������ݴ���=75Mbps�� */
        unsigned int  dbg_bus_test_md    : 1;  /* bit[8]   : DBG BUS����ģʽ��BUSͨ����������
                                                             ������Ϣ��1��Ч�� */
        unsigned int  reserved           : 23; /* bit[9-31]: ������ */
    } reg;
} DBG_DBG_BUS_TEST_UNION;
#define DBG_DBG_BUS_TEST_dbg_bus_test_bandw_START  (0)
#define DBG_DBG_BUS_TEST_dbg_bus_test_bandw_END    (7)
#define DBG_DBG_BUS_TEST_dbg_bus_test_md_START     (8)
#define DBG_DBG_BUS_TEST_dbg_bus_test_md_END       (8)


/*****************************************************************************
 �ṹ��    : DBG_SP_MEM_CTRL_UNION
 �ṹ˵��  : SP_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: SP MEM CTRL���üĴ���
*****************************************************************************/
typedef union
{
    unsigned int      sp_mem_ctrl_reg;
    struct
    {
        unsigned int  sp_mem_ctrl : 16; /* bit[0-15] : SPRAM��MEM_CTRL���á�
                                                       ȱʡֵ��ͳһ�����ṩ�� */
        unsigned int  reserved    : 16; /* bit[16-31]: ������ */
    } reg;
} DBG_SP_MEM_CTRL_UNION;
#define DBG_SP_MEM_CTRL_sp_mem_ctrl_START  (0)
#define DBG_SP_MEM_CTRL_sp_mem_ctrl_END    (15)


/*****************************************************************************
 �ṹ��    : DBG_TP_MEM_CTRL_UNION
 �ṹ˵��  : TP_MEM_CTRL �Ĵ����ṹ���塣��ַƫ����:0x0E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: TP MEM CTRL���üĴ���
*****************************************************************************/
typedef union
{
    unsigned int      tp_mem_ctrl_reg;
    struct
    {
        unsigned int  tp_mem_ctrl : 16; /* bit[0-15] : TPRAM��MEM_CTRL���á�
                                                       ȱʡֵ��ͳһ�����ṩ�� */
        unsigned int  reserved    : 16; /* bit[16-31]: ������ */
    } reg;
} DBG_TP_MEM_CTRL_UNION;
#define DBG_TP_MEM_CTRL_tp_mem_ctrl_START  (0)
#define DBG_TP_MEM_CTRL_tp_mem_ctrl_END    (15)


/*****************************************************************************
 �ṹ��    : DBG_ARB_PRIOR_SEL_UNION
 �ṹ˵��  : ARB_PRIOR_SEL �Ĵ����ṹ���塣��ַƫ����:0x100����ֵ:0x0000000B�����:32
 �Ĵ���˵��: ARBITER���ȼ�ѡ�����üĴ���
*****************************************************************************/
typedef union
{
    unsigned int      arb_prior_sel_reg;
    struct
    {
        unsigned int  ddr_prior_level : 8;  /* bit[0-7] : DDRͨ·��arbiter���ȼ�ѡ�����á�
                                                          0�������ȼ���1�������ȼ���
                                                          bit0��sdrͨ����
                                                          bit1��dbg_busͨ����
                                                          bit2��dbg_dataͨ����
                                                          bit3��dbg_logͨ����
                                                          ���ౣ���� */
        unsigned int  reserved        : 24; /* bit[8-31]: ������ */
    } reg;
} DBG_ARB_PRIOR_SEL_UNION;
#define DBG_ARB_PRIOR_SEL_ddr_prior_level_START  (0)
#define DBG_ARB_PRIOR_SEL_ddr_prior_level_END    (7)


/*****************************************************************************
 �ṹ��    : DBG_TEST_SWITCH_UNION
 �ṹ˵��  : TEST_SWITCH �Ĵ����ṹ���塣��ַƫ����:0x104����ֵ:0x00000000�����:32
 �Ĵ���˵��: TEST SWITCH���üĴ���
*****************************************************************************/
typedef union
{
    unsigned int      test_switch_reg;
    struct
    {
        unsigned int  test_switch : 1;  /* bit[0]   : ģ����Թ�����ѡ�񿪹ء�
                                                      0�����Թ��ܹرգ�(ȱʡ����)
                                                      1�����Թ��ܿ����� */
        unsigned int  reserved_0  : 3;  /* bit[1-3] : ������ */
        unsigned int  rd_dly_sel  : 1;  /* bit[4]   : Burst�ӿ�gnt��rd�źŶ���ѡ��
                                                      0��gnt��rd������룻(ȱʡ����)
                                                      1��gnt��rd���Բ����롣 */
        unsigned int  reserved_1  : 27; /* bit[5-31]: ������ */
    } reg;
} DBG_TEST_SWITCH_UNION;
#define DBG_TEST_SWITCH_test_switch_START  (0)
#define DBG_TEST_SWITCH_test_switch_END    (0)
#define DBG_TEST_SWITCH_rd_dly_sel_START   (4)
#define DBG_TEST_SWITCH_rd_dly_sel_END     (4)


/*****************************************************************************
 �ṹ��    : DBG_GNT_RD_STS_UNION
 �ṹ˵��  : GNT_RD_STS �Ĵ����ṹ���塣��ַƫ����:0x11C����ֵ:0x00000000�����:32
 �Ĵ���˵��: GNT��RD����״̬�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      gnt_rd_sts_reg;
    struct
    {
        unsigned int  tcm_gnt_nord : 1;  /* bit[0]   : ָʾDMA��TCM�ӿ�gnt�ź���Чͬʱ��rd�ź�״̬����λд1��0״̬ */
        unsigned int  reserved_0   : 3;  /* bit[1-3] : ������ */
        unsigned int  ddr_gnt_nord : 1;  /* bit[4]   : ָʾDMA��DDR�ӿ�gnt�ź���Чͬʱ��rd�ź�״̬����λд1��0״̬ */
        unsigned int  reserved_1   : 27; /* bit[5-31]: ������ */
    } reg;
} DBG_GNT_RD_STS_UNION;
#define DBG_GNT_RD_STS_tcm_gnt_nord_START  (0)
#define DBG_GNT_RD_STS_tcm_gnt_nord_END    (0)
#define DBG_GNT_RD_STS_ddr_gnt_nord_START  (4)
#define DBG_GNT_RD_STS_ddr_gnt_nord_END    (4)


/*****************************************************************************
 �ṹ��    : DBG_TCM_DMA_CNT_UNION
 �ṹ˵��  : TCM_DMA_CNT �Ĵ����ṹ���塣��ַƫ����:0x120����ֵ:0x00000000�����:32
 �Ĵ���˵��: TCMͨ����DMA����/��Ӧ����������
*****************************************************************************/
typedef union
{
    unsigned int      tcm_dma_cnt_reg;
    struct
    {
        unsigned int  tcm_req_cnt : 16; /* bit[0-15] : TCM��DMA�ӿڵ�req���������������
                                                       Test_switch������Ч���ر���0��
                                                       ֻ����16λ�������� */
        unsigned int  tcm_gnt_cnt : 16; /* bit[16-31]: TCM��DMA�ӿڵ�gnt��Ӧ������������
                                                       Test_switch������Ч���ر���0��
                                                       ֻ����16λ�������� */
    } reg;
} DBG_TCM_DMA_CNT_UNION;
#define DBG_TCM_DMA_CNT_tcm_req_cnt_START  (0)
#define DBG_TCM_DMA_CNT_tcm_req_cnt_END    (15)
#define DBG_TCM_DMA_CNT_tcm_gnt_cnt_START  (16)
#define DBG_TCM_DMA_CNT_tcm_gnt_cnt_END    (31)


/*****************************************************************************
 �ṹ��    : DBG_TCM_RAM_CNT_UNION
 �ṹ˵��  : TCM_RAM_CNT �Ĵ����ṹ���塣��ַƫ����:0x124����ֵ:0x00000000�����:32
 �Ĵ���˵��: tcm��ram״̬������
*****************************************************************************/
typedef union
{
    unsigned int      tcm_ram_cnt_reg;
    struct
    {
        unsigned int  tcm_ram_peak_cnt : 10; /* bit[0-9]  : ָʾTCMͨ��RAM�ﵽ���洢���ݸ�����
                                                            Test_switch������Ч���ر���0��
                                                            10λ�����������ݷ�Χ��0~512�� */
        unsigned int  reserved_0       : 6;  /* bit[10-15]: ������ */
        unsigned int  tcm_bst_peak_cnt : 6;  /* bit[16-21]: ָʾTCMͨ��RAM�ﵽ���burst�洢������
                                                            Test_switch������Ч���ر���0��
                                                            6λ�����������ݷ�Χ��0~32�� */
        unsigned int  reserved_1       : 6;  /* bit[22-27]: ������ */
        unsigned int  tcm_ram_empty    : 1;  /* bit[28]   : ָʾTCMͨ��RAMʵʱ�ǿ�״̬��
                                                            0��ramΪ�ա�1��ram�ǿգ� */
        unsigned int  reserved_2       : 3;  /* bit[29-31]: ������ */
    } reg;
} DBG_TCM_RAM_CNT_UNION;
#define DBG_TCM_RAM_CNT_tcm_ram_peak_cnt_START  (0)
#define DBG_TCM_RAM_CNT_tcm_ram_peak_cnt_END    (9)
#define DBG_TCM_RAM_CNT_tcm_bst_peak_cnt_START  (16)
#define DBG_TCM_RAM_CNT_tcm_bst_peak_cnt_END    (21)
#define DBG_TCM_RAM_CNT_tcm_ram_empty_START     (28)
#define DBG_TCM_RAM_CNT_tcm_ram_empty_END       (28)


/*****************************************************************************
 �ṹ��    : DBG_TCM_TIME_CNT_UNION
 �ṹ˵��  : TCM_TIME_CNT �Ĵ����ṹ���塣��ַƫ����:0x128����ֵ:0x00000000�����:32
 �Ĵ���˵��: tcmͨ��req����Ӧʱ�������
*****************************************************************************/
typedef union
{
    unsigned int      tcm_time_cnt_reg;
    struct
    {
        unsigned int  tcm_gnt_time_cnt : 24; /* bit[0-23] : ָʾTCMͨ��RAM��req/gnt�����ʱ�������
                                                            Test_switch������Ч���ر���0��
                                                            24λ��������ʱ�������ʱ����ء� */
        unsigned int  reserved         : 8;  /* bit[24-31]: ������ */
    } reg;
} DBG_TCM_TIME_CNT_UNION;
#define DBG_TCM_TIME_CNT_tcm_gnt_time_cnt_START  (0)
#define DBG_TCM_TIME_CNT_tcm_gnt_time_cnt_END    (23)


/*****************************************************************************
 �ṹ��    : DBG_DBG_INT_STS_UNION
 �ṹ˵��  : DBG_INT_STS �Ĵ����ṹ���塣��ַƫ����:0x140����ֵ:0x00000000�����:32
 �Ĵ���˵��: DBG�ж�״̬�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_int_sts_reg;
    struct
    {
        unsigned int  dbg_int_sts : 7;  /* bit[0-6] : DBG�ж�״ָ̬ʾ��
                                                      0�����жϣ�
                                                      1�����жϣ�
                                                      bit0��dat������������жϣ�
                                                      bit1��bus������������жϣ�
                                                      bit2��bus����burst�����жϣ�
                                                      bit3��log������������жϣ�
                                                      bit4��log���ݴ���֡����С������ֵ�����жϣ�
                                                      bit5��log���ݴ���֡���ݴ�������ֵ�����жϣ�
                                                      bit6��log���ݴ���֡����С������ֵ���޽�����ʶ�����жϡ� */
        unsigned int  reserved    : 25; /* bit[7-31]: ������ */
    } reg;
} DBG_DBG_INT_STS_UNION;
#define DBG_DBG_INT_STS_dbg_int_sts_START  (0)
#define DBG_DBG_INT_STS_dbg_int_sts_END    (6)


/*****************************************************************************
 �ṹ��    : DBG_DBG_INT_CLR_UNION
 �ṹ˵��  : DBG_INT_CLR �Ĵ����ṹ���塣��ַƫ����:0x144����ֵ:0x00000000�����:32
 �Ĵ���˵��: DBG�ж�����Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_int_clr_reg;
    struct
    {
        unsigned int  dbg_int_clr : 7;  /* bit[0-6] : DBG�ж��������Ӧλд1��0�жϡ�
                                                      bit0��dat������������ж���0��
                                                      bit1��bus������������ж���0��
                                                      bit2��bus����burst�����ж���0��
                                                      bit3��log������������ж���0��
                                                      bit4��log���ݴ���֡����С������ֵ�����ж���0��
                                                      bit5��log���ݴ���֡���ݴ�������ֵ�����ж���0��
                                                      bit6��log���ݴ���֡����С������ֵ���޽�����ʶ�����ж���0�� */
        unsigned int  reserved    : 25; /* bit[7-31]: ������ */
    } reg;
} DBG_DBG_INT_CLR_UNION;
#define DBG_DBG_INT_CLR_dbg_int_clr_START  (0)
#define DBG_DBG_INT_CLR_dbg_int_clr_END    (6)


/*****************************************************************************
 �ṹ��    : DBG_DBG_INT_MSK_UNION
 �ṹ˵��  : DBG_INT_MSK �Ĵ����ṹ���塣��ַƫ����:0x148����ֵ:0x00000000�����:32
 �Ĵ���˵��: DBG�ж����μĴ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_int_msk_reg;
    struct
    {
        unsigned int  dbg_int_msk : 7;  /* bit[0-6] : DBG�ж����Ρ�
                                                      0���ж�����ʹ�ܣ��жϲ��ϱ�(ȱʡ״̬)
                                                      1���жϿ��ϱ�
                                                      bit0��dat������������ж�����λ��
                                                      bit1��bus������������ж�����λ��
                                                      bit2��bus����burst�����ж�����λ��
                                                      bit3��log������������ж�����λ��
                                                      bit4��log���ݴ���֡����С������ֵ�����ж�����λ��
                                                      bit5��log���ݴ���֡���ݴ�������ֵ�����ж�����λ��
                                                      bit6��log���ݴ���֡����С������ֵ���޽�����ʶ�����ж�����λ�� */
        unsigned int  reserved    : 25; /* bit[7-31]: ������ */
    } reg;
} DBG_DBG_INT_MSK_UNION;
#define DBG_DBG_INT_MSK_dbg_int_msk_START  (0)
#define DBG_DBG_INT_MSK_dbg_int_msk_END    (6)


/*****************************************************************************
 �ṹ��    : DBG_RFIN_DBG_FLT_UNION
 �ṹ˵��  : RFIN_DBG_FLT �Ĵ����ṹ���塣��ַƫ����:0x00600����ֵ:0x00000000�����:32
 �Ĵ���˵��: DBG��������
*****************************************************************************/
typedef union
{
    unsigned int      rfin_dbg_flt_reg;
    struct
    {
        unsigned int  dbg_flt  : 2;  /* bit[0-1] : ģ������ID��Ĺ�������ÿ��bitָʾһ��ID�����磬bit0����ID��Ϊdbg_id + 1��bit1����ID��Ϊdbg_id + 1���������ơ�
                                                   ���bitȡֵΪ1��������bit��Ӧ��ID��Ч��������Ч��
                                                   0������ͨ��2��������ͬʱ�ɼ�
                                                   1�����з���ͨ�����ݲɼ�
                                                   2������ͨ��������RXA���ݲɼ�
                                                   3������ͨ��������RXB���ݲɼ� */
        unsigned int  reserved : 30; /* bit[2-31]: ���� */
    } reg;
} DBG_RFIN_DBG_FLT_UNION;
#define DBG_RFIN_DBG_FLT_dbg_flt_START   (0)
#define DBG_RFIN_DBG_FLT_dbg_flt_END     (1)


/*****************************************************************************
 �ṹ��    : DBG_RFIN_DBG_CH_UNION
 �ṹ˵��  : RFIN_DBG_CH �Ĵ����ṹ���塣��ַƫ����:0x00608����ֵ:0x00000000�����:32
 �Ĵ���˵��: DBG����ѡ��
*****************************************************************************/
typedef union
{
    unsigned int      rfin_dbg_ch_reg;
    struct
    {
        unsigned int  dbg_dl_sel : 4;  /* bit[0-3]  : ��������ʹ�ܣ�ÿ��bit��Ӧһ�������ز���ȡֵΪ1������ͨ�ز�����ʹ�ܣ�
                                                      [3]�������ز�3����
                                                      [2]�������ز�2����
                                                      [1]�������ز�1����
                                                      [0]�������ز�0���� */
        unsigned int  reserved_0 : 12; /* bit[4-15] : ���� */
        unsigned int  dbg_ul_sel : 2;  /* bit[16-17]: ��������ʹ�ܣ�ÿ��bit��Ӧһ�������ز���ȡֵΪ1�������ز�����ʹ�ܣ�
                                                      [1]�������ز�1����
                                                      [0]�������ز�0���� */
        unsigned int  reserved_1 : 14; /* bit[18-31]: ���� */
    } reg;
} DBG_RFIN_DBG_CH_UNION;
#define DBG_RFIN_DBG_CH_dbg_dl_sel_START  (0)
#define DBG_RFIN_DBG_CH_dbg_dl_sel_END    (3)
#define DBG_RFIN_DBG_CH_dbg_ul_sel_START  (16)
#define DBG_RFIN_DBG_CH_dbg_ul_sel_END    (17)


/*****************************************************************************
 �ṹ��    : DBG_RFIN_DBG_MODE_UNION
 �ṹ˵��  : RFIN_DBG_MODE �Ĵ����ṹ���塣��ַƫ����:0x0060C����ֵ:0x00000001�����:32
 �Ĵ���˵��: DBG����ģʽ
*****************************************************************************/
typedef union
{
    unsigned int      rfin_dbg_mode_reg;
    struct
    {
        unsigned int  dbg_rpt_mode : 1;  /* bit[0]    : �����ϱ�ģʽ��
                                                        1'b0�����ɹ��ܴ����󣬲���dbg_pkg_num�����ݰ����Զ�����
                                                        1'b1��ֻҪdbg_enΪ1��һֱ�����ϱ�������dbg_pkg_num���� */
        unsigned int  reserved     : 15; /* bit[1-15] : ���� */
        unsigned int  dbg_pkg_num  : 16; /* bit[16-31]: ���ɰ��ĸ��� */
    } reg;
} DBG_RFIN_DBG_MODE_UNION;
#define DBG_RFIN_DBG_MODE_dbg_rpt_mode_START  (0)
#define DBG_RFIN_DBG_MODE_dbg_rpt_mode_END    (0)
#define DBG_RFIN_DBG_MODE_dbg_pkg_num_START   (16)
#define DBG_RFIN_DBG_MODE_dbg_pkg_num_END     (31)


/*****************************************************************************
 �ṹ��    : DBG_RFIN_DBG_EN_UNION
 �ṹ˵��  : RFIN_DBG_EN �Ĵ����ṹ���塣��ַƫ����:0x00610����ֵ:0x00000000�����:32
 �Ĵ���˵��: DBG����ʹ��
*****************************************************************************/
typedef union
{
    unsigned int      rfin_dbg_en_reg;
    struct
    {
        unsigned int  dbg_en   : 1;  /* bit[0]   : ����ʹ�ܣ�
                                                   1'b0�����ɹ��ܲ�ʹ��
                                                   1'b1�����ɹ���ʹ�� */
        unsigned int  reserved : 31; /* bit[1-31]: ���� */
    } reg;
} DBG_RFIN_DBG_EN_UNION;
#define DBG_RFIN_DBG_EN_dbg_en_START    (0)
#define DBG_RFIN_DBG_EN_dbg_en_END      (0)


/*****************************************************************************
 �ṹ��    : DBG_FPU_DBG_LOG_CFG_UNION
 �ṹ˵��  : FPU_DBG_LOG_CFG �Ĵ����ṹ���塣��ַƫ����:0x4408����ֵ:0x00000001�����:32
 �Ĵ���˵��: �Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned int      fpu_dbg_log_cfg_reg;
    struct
    {
        unsigned int  fpu_log_rpt_mode : 1;  /* bit[0]    : ��ά�ɲ������ϱ�ģʽ��
                                                            'b0���������������fpu_log_pkg_num�����ݰ����Զ�������
                                                            'b1��ֻҪfpu_log_enΪ1���ϱ���û���ϱ��������ơ� */
        unsigned int  reserved         : 15; /* bit[1-15] : ���� */
        unsigned int  fpu_log_pkg_num  : 16; /* bit[16-31]: LOG��Ϣ��ά�ɲ�İ����� */
    } reg;
} DBG_FPU_DBG_LOG_CFG_UNION;
#define DBG_FPU_DBG_LOG_CFG_fpu_log_rpt_mode_START  (0)
#define DBG_FPU_DBG_LOG_CFG_fpu_log_rpt_mode_END    (0)
#define DBG_FPU_DBG_LOG_CFG_fpu_log_pkg_num_START   (16)
#define DBG_FPU_DBG_LOG_CFG_fpu_log_pkg_num_END     (31)


/*****************************************************************************
 �ṹ��    : DBG_FPU_DBG_DAT_FLT_UNION
 �ṹ˵��  : FPU_DBG_DAT_FLT �Ĵ����ṹ���塣��ַƫ����:0x4410����ֵ:0x00000010�����:32
 �Ĵ���˵��: �Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned int      fpu_dbg_dat_flt_reg;
    struct
    {
        unsigned int  fpu_dbg_filtrat : 16; /* bit[0-15] : ģ��DAT ID�������
                                                           [4] cfu�����źš�
                                                           [9] fpu_lsѡ���źš�
                                                           [11] fpu_lsuѡ���źš�
                                                           [12] fpu_emuѡ���źš�
                                                           [13] fpu_truѡ���źš�
                                                           ����bit���� */
        unsigned int  reserved        : 16; /* bit[16-31]: ���� */
    } reg;
} DBG_FPU_DBG_DAT_FLT_UNION;
#define DBG_FPU_DBG_DAT_FLT_fpu_dbg_filtrat_START  (0)
#define DBG_FPU_DBG_DAT_FLT_fpu_dbg_filtrat_END    (15)


/*****************************************************************************
 �ṹ��    : DBG_FPU_DBG_DAT_CFG0_UNION
 �ṹ˵��  : FPU_DBG_DAT_CFG0 �Ĵ����ṹ���塣��ַƫ����:0x4414����ֵ:0x03C00007�����:32
 �Ĵ���˵��: �Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned int      fpu_dbg_dat_cfg0_reg;
    struct
    {
        unsigned int  fpu_dbg_rpt_mode     : 1;  /* bit[0]    : ��ά�ɲ������ϱ�ģʽ��
                                                                'b0���������������fpu_dbg_pkg_num�����ݰ����Զ�������
                                                                'b1��ֻҪfpu_dbg_enΪ1���ϱ���û���ϱ��������ơ� */
        unsigned int  fpu_FPU_DBG_comp_mod : 2;  /* bit[1-2]  : ��ά�ɲ������ϱ�����ƴ��ģʽ��
                                                                'd0����ƴ�ӣ�
                                                                'd1��������
                                                                'd2����������0����ƴ��Ϊһ��64bit���� word�ϱ���
                                                                'd3��2��������ƴ��Ϊһ��64bit���� word�ϱ��� */
        unsigned int  reserved             : 13; /* bit[3-15] : ���� */
        unsigned int  fpu_dbg_pkg_num      : 16; /* bit[16-31]: ���� */
    } reg;
} DBG_FPU_DBG_DAT_CFG0_UNION;
#define DBG_FPU_DBG_DAT_CFG0_fpu_dbg_rpt_mode_START      (0)
#define DBG_FPU_DBG_DAT_CFG0_fpu_dbg_rpt_mode_END        (0)
#define DBG_FPU_DBG_DAT_CFG0_fpu_FPU_DBG_comp_mod_START  (1)
#define DBG_FPU_DBG_DAT_CFG0_fpu_FPU_DBG_comp_mod_END    (2)
#define DBG_FPU_DBG_DAT_CFG0_fpu_dbg_pkg_num_START       (16)
#define DBG_FPU_DBG_DAT_CFG0_fpu_dbg_pkg_num_END         (31)


/*****************************************************************************
 �ṹ��    : DBG_FPU_LOG_EN_UNION
 �ṹ˵��  : FPU_LOG_EN �Ĵ����ṹ���塣��ַƫ����:0x4424����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned int      fpu_log_en_reg;
    struct
    {
        unsigned int  fpu_log_en : 1;  /* bit[0]   : LOG�ϱ�ʼ��
                                                     1'b1:ʹ��
                                                     1'b0:��ʹ�� */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} DBG_FPU_LOG_EN_UNION;
#define DBG_FPU_LOG_EN_fpu_log_en_START  (0)
#define DBG_FPU_LOG_EN_fpu_log_en_END    (0)


/*****************************************************************************
 �ṹ��    : DBG_FPU_DBG_EN_UNION
 �ṹ˵��  : FPU_DBG_EN �Ĵ����ṹ���塣��ַƫ����:0x4428����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned int      fpu_dbg_en_reg;
    struct
    {
        unsigned int  fpu_dbg_en : 1;  /* bit[0]   : dbg �ϱ��Ƿ�ʼ��
                                                     1'b1:ʹ��
                                                     1'b0:��ʹ�� */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} DBG_FPU_DBG_EN_UNION;
#define DBG_FPU_DBG_EN_fpu_dbg_en_START  (0)
#define DBG_FPU_DBG_EN_fpu_dbg_en_END    (0)


/*****************************************************************************
 �ṹ��    : DBG_FPU_LOG_DBG_SEL_UNION
 �ṹ˵��  : FPU_LOG_DBG_SEL �Ĵ����ṹ���塣��ַƫ����:0x442C����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned int      fpu_log_dbg_sel_reg;
    struct
    {
        unsigned int  fpu_cc_log_sel : 2;  /* bit[0-1] : 0: ѡ��pcc log���ݣ���������
                                                         1��ѡ��cc1 log���ݣ���������
                                                         2: ѡ��cc2 log���ݣ���������
                                                         3��ѡ��cc3 log���ݣ��������� */
        unsigned int  fpu_cc_dbg_sel : 2;  /* bit[2-3] : 0: ѡ��pcc dbg���ݣ���������
                                                         1��ѡ��cc1 dbg���ݣ���������
                                                         2: ѡ��cc2 dbg���ݣ���������
                                                         3��ѡ��cc3 dbg���ݣ��������� */
        unsigned int  reserved       : 28; /* bit[4-31]: ���� */
    } reg;
} DBG_FPU_LOG_DBG_SEL_UNION;
#define DBG_FPU_LOG_DBG_SEL_fpu_cc_log_sel_START  (0)
#define DBG_FPU_LOG_DBG_SEL_fpu_cc_log_sel_END    (1)
#define DBG_FPU_LOG_DBG_SEL_fpu_cc_dbg_sel_START  (2)
#define DBG_FPU_LOG_DBG_SEL_fpu_cc_dbg_sel_END    (3)


/*****************************************************************************
 �ṹ��    : DBG_FPU_DEBUG_CTRL_UNION
 �ṹ˵��  : FPU_DEBUG_CTRL �Ĵ����ṹ���塣��ַƫ����:0xE1134610����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned int      fpu_debug_ctrl_reg;
    struct
    {
        unsigned int  fpu_smp_dbg_sel    : 2;  /* bit[0-1]  : FPU SMP debug���ݲɼ�ѡ���ź�(������)
                                                              2'b0��ѡ��pcc smp���ݣ�
                                                              2'b01��ѡ��cc1 smp���ݣ�
                                                              2'b10��ѡ��cc2 smp���ݣ�
                                                              2'b11��ѡ��cc3 smp���ݣ�
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved_0         : 2;  /* bit[2-3]  : ���� */
        unsigned int  fpu_dbg_sel        : 3;  /* bit[4-6]  : FPU ��ccͨ·debug�Ĵ����ϱ�ѡ���ź�(������)
                                                              3'b0,pcc debug���ݣ�
                                                              3'b1,cc1 debug���ݣ�
                                                              3'b10,cc2 debug���ݣ�
                                                              3'b11,cc3 debug���ݣ�
                                                              3'b100,mlafc debug���ݣ�
                                                              3'b101,csu0 debug���ݣ�
                                                              3'b110,csu1 debug���ݣ�
                                                              ���ౣ��
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved_1         : 1;  /* bit[7]    : ���� */
        unsigned int  fpu_rfin_dbg_sel   : 2;  /* bit[8-9]  : FPU rfin debug�Ĵ����ϱ�ѡ���ź�(������)
                                                              2'b0��ѡ��pcc rfin debug���ݣ�
                                                              2'b01��ѡ��cc1 rfin debug���ݣ�
                                                              2'b10��ѡ��cc2 rfin debug���ݣ�
                                                              2'b11��ѡ��cc3 rfin debug���ݣ�
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved_2         : 2;  /* bit[10-11]: ���� */
        unsigned int  fpu_cc_dbg_mode    : 4;  /* bit[12-15]: FPU CC�ڲ�debug�����ϱ�ģʽѡ��(������)
                                                              4'b0��ѡ���ϱ�cfu�ڲ�״̬��Ϣ��
                                                              4'b1��ѡ���ϱ�dfu�ڲ�״̬��Ϣ��
                                                              4'b10��ѡ���ϱ�smu�ڲ�״̬��Ϣ��
                                                              4'b11��ѡ���ϱ�afc�ڲ�״̬��Ϣ��
                                                              4'b100��ѡ���ϱ�tru�ڲ�״̬��Ϣ��
                                                              4'b101��ѡ���ϱ�tau���ڲ�״̬��Ϣ��
                                                              4'b110��ѡ���ϱ�����ȫͨ·״̬��Ϣ��
                                                              4'b111��ѡ���ϱ����ȫͨ·״̬��Ϣ��
                                                              4'b1000��ѡ���ϱ�smp�ڲ�״̬��Ϣ��
                                                              4'b1001��ѡ���ϱ�cmu_buf�ڲ�״̬��Ϣ��
                                                              ��Чʱ�̣�������Ч */
        unsigned int  fpu_cc_smp_dbg_sel : 2;  /* bit[16-17]: FPU CC�ڲ�smp debug�����ϱ�ģʽѡ��(������)
                                                              2'b0��ѡ���ϱ�lsu�����ԭʼLS���ݣ�
                                                              2'b1��ѡ���ϱ�ls_smp�����LS���ݣ�
                                                              2'b10��ѡ���ϱ�em_smp�����emu��·�������ݣ�
                                                              2'b11��ѡ���ϱ�tru_smp�����pdp����
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved_3         : 2;  /* bit[18-19]: ���� */
        unsigned int  fpu_smu_dbg_ch_sel : 2;  /* bit[20-21]: FPU CC�ڲ�smu debug��Ϣͨ��ѡ��(������)
                                                              2'b0���ϱ�ͨ��0
                                                              2'b1���ϱ�ͨ��1
                                                              2'b10���ϱ�ͨ��2
                                                              2'b11���ϱ�ͨ��3
                                                              ��Чʱ�̣�������Ч */
        unsigned int  reserved_4         : 10; /* bit[22-31]: ���� */
    } reg;
} DBG_FPU_DEBUG_CTRL_UNION;
#define DBG_FPU_DEBUG_CTRL_fpu_smp_dbg_sel_START     (0)
#define DBG_FPU_DEBUG_CTRL_fpu_smp_dbg_sel_END       (1)
#define DBG_FPU_DEBUG_CTRL_fpu_dbg_sel_START         (4)
#define DBG_FPU_DEBUG_CTRL_fpu_dbg_sel_END           (6)
#define DBG_FPU_DEBUG_CTRL_fpu_rfin_dbg_sel_START    (8)
#define DBG_FPU_DEBUG_CTRL_fpu_rfin_dbg_sel_END      (9)
#define DBG_FPU_DEBUG_CTRL_fpu_cc_dbg_mode_START     (12)
#define DBG_FPU_DEBUG_CTRL_fpu_cc_dbg_mode_END       (15)
#define DBG_FPU_DEBUG_CTRL_fpu_cc_smp_dbg_sel_START  (16)
#define DBG_FPU_DEBUG_CTRL_fpu_cc_smp_dbg_sel_END    (17)
#define DBG_FPU_DEBUG_CTRL_fpu_smu_dbg_ch_sel_START  (20)
#define DBG_FPU_DEBUG_CTRL_fpu_smu_dbg_ch_sel_END    (21)


/*****************************************************************************
 �ṹ��    : DBG_SMU_CC_DEBUG_SEL_UNION
 �ṹ˵��  : SMU_CC_DEBUG_SEL �Ĵ����ṹ���塣��ַƫ����:0xE1161950����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned int      smu_cc_debug_sel_reg;
    struct
    {
        unsigned int  smu_cc_debug_sel : 3;  /* bit[0-2]  : ���� */
        unsigned int  reserved_0       : 1;  /* bit[3]    : ���� */
        unsigned int  smu_cc_debug_en  : 1;  /* bit[4]    : ���� */
        unsigned int  reserved_1       : 3;  /* bit[5-7]  : ���� */
        unsigned int  smu_ila_sel      : 3;  /* bit[8-10] : ���� */
        unsigned int  reserved_2       : 21; /* bit[11-31]: ���� */
    } reg;
} DBG_SMU_CC_DEBUG_SEL_UNION;
#define DBG_SMU_CC_DEBUG_SEL_smu_cc_debug_sel_START  (0)
#define DBG_SMU_CC_DEBUG_SEL_smu_cc_debug_sel_END    (2)
#define DBG_SMU_CC_DEBUG_SEL_smu_cc_debug_en_START   (4)
#define DBG_SMU_CC_DEBUG_SEL_smu_cc_debug_en_END     (4)
#define DBG_SMU_CC_DEBUG_SEL_smu_ila_sel_START       (8)
#define DBG_SMU_CC_DEBUG_SEL_smu_ila_sel_END         (10)


/*****************************************************************************
 �ṹ��    : DBG_CC1_SMU_CC_DEBUG_SEL_UNION
 �ṹ˵��  : CC1_SMU_CC_DEBUG_SEL �Ĵ����ṹ���塣��ַƫ����:0xE1163950����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned int      cc1_smu_cc_debug_sel_reg;
    struct
    {
        unsigned int  cc1_smu_cc_debug_sel : 3;  /* bit[0-2]  : ���� */
        unsigned int  reserved_0           : 1;  /* bit[3]    : ���� */
        unsigned int  cc1_smu_cc_debug_en  : 1;  /* bit[4]    : ���� */
        unsigned int  reserved_1           : 3;  /* bit[5-7]  : ���� */
        unsigned int  cc1_smu_ila_sel      : 3;  /* bit[8-10] : ���� */
        unsigned int  reserved_2           : 21; /* bit[11-31]: ���� */
    } reg;
} DBG_CC1_SMU_CC_DEBUG_SEL_UNION;
#define DBG_CC1_SMU_CC_DEBUG_SEL_cc1_smu_cc_debug_sel_START  (0)
#define DBG_CC1_SMU_CC_DEBUG_SEL_cc1_smu_cc_debug_sel_END    (2)
#define DBG_CC1_SMU_CC_DEBUG_SEL_cc1_smu_cc_debug_en_START   (4)
#define DBG_CC1_SMU_CC_DEBUG_SEL_cc1_smu_cc_debug_en_END     (4)
#define DBG_CC1_SMU_CC_DEBUG_SEL_cc1_smu_ila_sel_START       (8)
#define DBG_CC1_SMU_CC_DEBUG_SEL_cc1_smu_ila_sel_END         (10)


/*****************************************************************************
 �ṹ��    : DBG_CC2_SMU_CC_DEBUG_SEL_UNION
 �ṹ˵��  : CC2_SMU_CC_DEBUG_SEL �Ĵ����ṹ���塣��ַƫ����:0xE1165950����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned int      cc2_smu_cc_debug_sel_reg;
    struct
    {
        unsigned int  cc2_smu_cc_debug_sel : 3;  /* bit[0-2]  : ���� */
        unsigned int  reserved_0           : 1;  /* bit[3]    : ���� */
        unsigned int  cc2_smu_cc_debug_en  : 1;  /* bit[4]    : ���� */
        unsigned int  reserved_1           : 3;  /* bit[5-7]  : ���� */
        unsigned int  cc2_smu_ila_sel      : 3;  /* bit[8-10] : ���� */
        unsigned int  reserved_2           : 21; /* bit[11-31]: ���� */
    } reg;
} DBG_CC2_SMU_CC_DEBUG_SEL_UNION;
#define DBG_CC2_SMU_CC_DEBUG_SEL_cc2_smu_cc_debug_sel_START  (0)
#define DBG_CC2_SMU_CC_DEBUG_SEL_cc2_smu_cc_debug_sel_END    (2)
#define DBG_CC2_SMU_CC_DEBUG_SEL_cc2_smu_cc_debug_en_START   (4)
#define DBG_CC2_SMU_CC_DEBUG_SEL_cc2_smu_cc_debug_en_END     (4)
#define DBG_CC2_SMU_CC_DEBUG_SEL_cc2_smu_ila_sel_START       (8)
#define DBG_CC2_SMU_CC_DEBUG_SEL_cc2_smu_ila_sel_END         (10)


/*****************************************************************************
 �ṹ��    : DBG_CC3_SMU_CC_DEBUG_SEL_UNION
 �ṹ˵��  : CC3_SMU_CC_DEBUG_SEL �Ĵ����ṹ���塣��ַƫ����:0xE1167950����ֵ:0x00000000�����:32
 �Ĵ���˵��: �Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned int      cc3_smu_cc_debug_sel_reg;
    struct
    {
        unsigned int  cc3_smu_cc_debug_sel : 3;  /* bit[0-2]  : ���� */
        unsigned int  reserved_0           : 1;  /* bit[3]    : ���� */
        unsigned int  cc3_smu_cc_debug_en  : 1;  /* bit[4]    : ���� */
        unsigned int  reserved_1           : 3;  /* bit[5-7]  : ���� */
        unsigned int  cc3_smu_ila_sel      : 3;  /* bit[8-10] : ���� */
        unsigned int  reserved_2           : 21; /* bit[11-31]: ���� */
    } reg;
} DBG_CC3_SMU_CC_DEBUG_SEL_UNION;
#define DBG_CC3_SMU_CC_DEBUG_SEL_cc3_smu_cc_debug_sel_START  (0)
#define DBG_CC3_SMU_CC_DEBUG_SEL_cc3_smu_cc_debug_sel_END    (2)
#define DBG_CC3_SMU_CC_DEBUG_SEL_cc3_smu_cc_debug_en_START   (4)
#define DBG_CC3_SMU_CC_DEBUG_SEL_cc3_smu_cc_debug_en_END     (4)
#define DBG_CC3_SMU_CC_DEBUG_SEL_cc3_smu_ila_sel_START       (8)
#define DBG_CC3_SMU_CC_DEBUG_SEL_cc3_smu_ila_sel_END         (10)


/*****************************************************************************
 �ṹ��    : DBG_PDU_DBG_LOG_MODE_UNION
 �ṹ˵��  : PDU_DBG_LOG_MODE �Ĵ����ṹ���塣��ַƫ����:0x4008����ֵ:0x00000002�����:32
 �Ĵ���˵��: ģ��LOG ģʽ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      pdu_dbg_log_mode_reg;
    struct
    {
        unsigned int  reserved_0          : 1;  /* bit[0]    : ���� */
        unsigned int  cr2dbg_log_rpt_mode : 1;  /* bit[1]    : ��ά�ɲ������ϱ�ģʽ��
                                                               0���������������dbg_pkg_num�����ݰ����Զ�����
                                                               1��ֻҪdbg_rpt_enΪ1���ϱ���û���ϱ��������ơ� */
        unsigned int  reserved_1          : 14; /* bit[2-15] : ���� */
        unsigned int  cr2dbg_log_pkt_num  : 16; /* bit[16-31]: LOG��Ϣ��ά�ɲ�İ����� */
    } reg;
} DBG_PDU_DBG_LOG_MODE_UNION;
#define DBG_PDU_DBG_LOG_MODE_cr2dbg_log_rpt_mode_START  (1)
#define DBG_PDU_DBG_LOG_MODE_cr2dbg_log_rpt_mode_END    (1)
#define DBG_PDU_DBG_LOG_MODE_cr2dbg_log_pkt_num_START   (16)
#define DBG_PDU_DBG_LOG_MODE_cr2dbg_log_pkt_num_END     (31)


/*****************************************************************************
 �ṹ��    : DBG_PDU_DBG_LOG_EN_UNION
 �ṹ˵��  : PDU_DBG_LOG_EN �Ĵ����ṹ���塣��ַƫ����:0x400C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ģ��LOG EN�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      pdu_dbg_log_en_reg;
    struct
    {
        unsigned int  cr2dbg_log_en : 1;  /* bit[0]   : ģ��LOGʹ��                              
                                                        0����ά�ɲ⹦�ܲ�ʹ��                             1����ά�ɲ⹦��ʹ�� */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} DBG_PDU_DBG_LOG_EN_UNION;
#define DBG_PDU_DBG_LOG_EN_cr2dbg_log_en_START  (0)
#define DBG_PDU_DBG_LOG_EN_cr2dbg_log_en_END    (0)


/*****************************************************************************
 �ṹ��    : DBG_PDU_DBG_DAT_MODE_UNION
 �ṹ˵��  : PDU_DBG_DAT_MODE �Ĵ����ṹ���塣��ַƫ����:0x401C����ֵ:0x00000002�����:32
 �Ĵ���˵��: ģ��DAT ģʽ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      pdu_dbg_dat_mode_reg;
    struct
    {
        unsigned int  reserved_0          : 1;  /* bit[0]    : ���� */
        unsigned int  cr2dbg_dat_rpt_mode : 1;  /* bit[1]    : ��ά�ɲ������ϱ�ģʽ��
                                                               0���������������dbg_pkg_num�����ݰ����Զ�����
                                                               1��ֻҪdbg_rpt_enΪ1���ϱ���û���ϱ��������ơ� */
        unsigned int  reserved_1          : 14; /* bit[2-15] : ���� */
        unsigned int  cr2dbg_dat_pkt_num  : 16; /* bit[16-31]: DAT��Ϣ��ά�ɲ�İ����� */
    } reg;
} DBG_PDU_DBG_DAT_MODE_UNION;
#define DBG_PDU_DBG_DAT_MODE_cr2dbg_dat_rpt_mode_START  (1)
#define DBG_PDU_DBG_DAT_MODE_cr2dbg_dat_rpt_mode_END    (1)
#define DBG_PDU_DBG_DAT_MODE_cr2dbg_dat_pkt_num_START   (16)
#define DBG_PDU_DBG_DAT_MODE_cr2dbg_dat_pkt_num_END     (31)


/*****************************************************************************
 �ṹ��    : DBG_PDU_DBG_DAT_EN_UNION
 �ṹ˵��  : PDU_DBG_DAT_EN �Ĵ����ṹ���塣��ַƫ����:0x4020����ֵ:0x00000000�����:32
 �Ĵ���˵��: ģ��DAT EN�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      pdu_dbg_dat_en_reg;
    struct
    {
        unsigned int  cr2dbg_dat_en : 1;  /* bit[0]   : ģ��DATʹ��                              
                                                        0����ά�ɲ⹦�ܲ�ʹ��                             1����ά�ɲ⹦��ʹ�� */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} DBG_PDU_DBG_DAT_EN_UNION;
#define DBG_PDU_DBG_DAT_EN_cr2dbg_dat_en_START  (0)
#define DBG_PDU_DBG_DAT_EN_cr2dbg_dat_en_END    (0)


/*****************************************************************************
 �ṹ��    : DBG_PDU2_DBG_LOG_MODE_UNION
 �ṹ˵��  : PDU2_DBG_LOG_MODE �Ĵ����ṹ���塣��ַƫ����:0xE1B14008����ֵ:0x00000002�����:32
 �Ĵ���˵��: ģ��LOG ģʽ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      pdu2_dbg_log_mode_reg;
    struct
    {
        unsigned int  reserved_0          : 1;  /* bit[0]    : ���� */
        unsigned int  cr2dbg_log_rpt_mode : 1;  /* bit[1]    : ��ά�ɲ������ϱ�ģʽ��
                                                               0���������������dbg_pkg_num�����ݰ����Զ�����
                                                               1��ֻҪdbg_rpt_enΪ1���ϱ���û���ϱ��������ơ� */
        unsigned int  reserved_1          : 14; /* bit[2-15] : ���� */
        unsigned int  cr2dbg_log_pkt_num  : 16; /* bit[16-31]: LOG��Ϣ��ά�ɲ�İ����� */
    } reg;
} DBG_PDU2_DBG_LOG_MODE_UNION;
#define DBG_PDU2_DBG_LOG_MODE_cr2dbg_log_rpt_mode_START  (1)
#define DBG_PDU2_DBG_LOG_MODE_cr2dbg_log_rpt_mode_END    (1)
#define DBG_PDU2_DBG_LOG_MODE_cr2dbg_log_pkt_num_START   (16)
#define DBG_PDU2_DBG_LOG_MODE_cr2dbg_log_pkt_num_END     (31)


/*****************************************************************************
 �ṹ��    : DBG_PDU2_DBG_LOG_EN_UNION
 �ṹ˵��  : PDU2_DBG_LOG_EN �Ĵ����ṹ���塣��ַƫ����:0xE1B1400C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ģ��LOG EN�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      pdu2_dbg_log_en_reg;
    struct
    {
        unsigned int  cr2dbg_log_en : 1;  /* bit[0]   : ģ��LOGʹ��                              
                                                        0����ά�ɲ⹦�ܲ�ʹ��                             1����ά�ɲ⹦��ʹ�� */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} DBG_PDU2_DBG_LOG_EN_UNION;
#define DBG_PDU2_DBG_LOG_EN_cr2dbg_log_en_START  (0)
#define DBG_PDU2_DBG_LOG_EN_cr2dbg_log_en_END    (0)


/*****************************************************************************
 �ṹ��    : DBG_PDU2_DBG_DAT_MODE_UNION
 �ṹ˵��  : PDU2_DBG_DAT_MODE �Ĵ����ṹ���塣��ַƫ����:0xE1B1401C����ֵ:0x00000002�����:32
 �Ĵ���˵��: ģ��DAT ģʽ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      pdu2_dbg_dat_mode_reg;
    struct
    {
        unsigned int  reserved_0          : 1;  /* bit[0]    : ���� */
        unsigned int  cr2dbg_dat_rpt_mode : 1;  /* bit[1]    : ��ά�ɲ������ϱ�ģʽ��
                                                               0���������������dbg_pkg_num�����ݰ����Զ�����
                                                               1��ֻҪdbg_rpt_enΪ1���ϱ���û���ϱ��������ơ� */
        unsigned int  reserved_1          : 14; /* bit[2-15] : ���� */
        unsigned int  cr2dbg_dat_pkt_num  : 16; /* bit[16-31]: DAT��Ϣ��ά�ɲ�İ����� */
    } reg;
} DBG_PDU2_DBG_DAT_MODE_UNION;
#define DBG_PDU2_DBG_DAT_MODE_cr2dbg_dat_rpt_mode_START  (1)
#define DBG_PDU2_DBG_DAT_MODE_cr2dbg_dat_rpt_mode_END    (1)
#define DBG_PDU2_DBG_DAT_MODE_cr2dbg_dat_pkt_num_START   (16)
#define DBG_PDU2_DBG_DAT_MODE_cr2dbg_dat_pkt_num_END     (31)


/*****************************************************************************
 �ṹ��    : DBG_PDU2_DBG_DAT_EN_UNION
 �ṹ˵��  : PDU2_DBG_DAT_EN �Ĵ����ṹ���塣��ַƫ����:0xE1B14020����ֵ:0x00000000�����:32
 �Ĵ���˵��: ģ��DAT EN�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      pdu2_dbg_dat_en_reg;
    struct
    {
        unsigned int  cr2dbg_dat_en : 1;  /* bit[0]   : ģ��DATʹ��                              
                                                        0����ά�ɲ⹦�ܲ�ʹ��                             1����ά�ɲ⹦��ʹ�� */
        unsigned int  reserved      : 31; /* bit[1-31]: ���� */
    } reg;
} DBG_PDU2_DBG_DAT_EN_UNION;
#define DBG_PDU2_DBG_DAT_EN_cr2dbg_dat_en_START  (0)
#define DBG_PDU2_DBG_DAT_EN_cr2dbg_dat_en_END    (0)


/*****************************************************************************
 �ṹ��    : DBG_CQI_DBG_START_TIME_UNION
 �ṹ˵��  : CQI_DBG_START_TIME �Ĵ����ṹ���塣��ַƫ����:0x3300����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�Ŀ�ʼʱ��
*****************************************************************************/
typedef union
{
    unsigned int      cqi_dbg_start_time_reg;
    struct
    {
        unsigned int  dbg_at_ts_num  : 12; /* bit[0-11] : ��ά�ɲ�����ʱ�䣬��ϵͳ��ʱ�ο���symbol��Ts���� */
        unsigned int  reserved_0     : 4;  /* bit[12-15]: ���� */
        unsigned int  dbg_at_sym_num : 4;  /* bit[16-19]: ��ά�ɲ�����ʱ�䣬��ϵͳ��ʱ�ο�����֡�ڵķ��ż��� */
        unsigned int  reserved_1     : 12; /* bit[20-31]: ���� */
    } reg;
} DBG_CQI_DBG_START_TIME_UNION;
#define DBG_CQI_DBG_START_TIME_dbg_at_ts_num_START   (0)
#define DBG_CQI_DBG_START_TIME_dbg_at_ts_num_END     (11)
#define DBG_CQI_DBG_START_TIME_dbg_at_sym_num_START  (16)
#define DBG_CQI_DBG_START_TIME_dbg_at_sym_num_END    (19)


/*****************************************************************************
 �ṹ��    : DBG_CQI_DBG_DAT_EN_UNION
 �ṹ˵��  : CQI_DBG_DAT_EN �Ĵ����ṹ���塣��ַƫ����:0x3318����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ʹ�ܼĴ���
*****************************************************************************/
typedef union
{
    unsigned int      cqi_dbg_dat_en_reg;
    struct
    {
        unsigned int  dbg_dat_en : 1;  /* bit[0-0] : ���ݲɼ�ʹ��
                                                     0�����ɲ�ʹ��
                                                     1������ʹ�� */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} DBG_CQI_DBG_DAT_EN_UNION;
#define DBG_CQI_DBG_DAT_EN_dbg_dat_en_START  (0)
#define DBG_CQI_DBG_DAT_EN_dbg_dat_en_END    (0)


/*****************************************************************************
 �ṹ��    : DBG_PB_DBG_LOG_MODE_UNION
 �ṹ˵��  : PB_DBG_LOG_MODE �Ĵ����ṹ���塣��ַƫ����:0x1510����ֵ:0x00000002�����:32
 �Ĵ���˵��: LOG��Ϣģʽ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      pb_dbg_log_mode_reg;
    struct
    {
        unsigned int  reserved_0   : 1;  /* bit[0]    : ���� */
        unsigned int  dbg_rpt_mode : 1;  /* bit[1]    : ��ά�ɲ������ϱ�ģʽ��
                                                        'b0���������������dbg_pkg_num�����ݰ����Զ�������
                                                        'b1��ֻҪdbg_rpt_enΪ1���ϱ���û���ϱ��������ơ� */
        unsigned int  reserved_1   : 14; /* bit[2-15] : ���� */
        unsigned int  dbg_pkg_num  : 16; /* bit[16-31]: LOG��Ϣ��ά�ɲ�İ����� */
    } reg;
} DBG_PB_DBG_LOG_MODE_UNION;
#define DBG_PB_DBG_LOG_MODE_dbg_rpt_mode_START  (1)
#define DBG_PB_DBG_LOG_MODE_dbg_rpt_mode_END    (1)
#define DBG_PB_DBG_LOG_MODE_dbg_pkg_num_START   (16)
#define DBG_PB_DBG_LOG_MODE_dbg_pkg_num_END     (31)


/*****************************************************************************
 �ṹ��    : DBG_PB_DBG_LOG_EN_UNION
 �ṹ˵��  : PB_DBG_LOG_EN �Ĵ����ṹ���塣��ַƫ����:0x1514����ֵ:0x00000000�����:32
 �Ĵ���˵��: LOG��Ϣʹ�ܼĴ���
*****************************************************************************/
typedef union
{
    unsigned int      pb_dbg_log_en_reg;
    struct
    {
        unsigned int  dbg_log_en : 1;  /* bit[0]   : ģ��LOGʹ��                              
                                                     1'b0����ά�ɲ⹦�ܲ�ʹ��                             1'b1����ά�ɲ⹦��ʹ�� */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} DBG_PB_DBG_LOG_EN_UNION;
#define DBG_PB_DBG_LOG_EN_dbg_log_en_START  (0)
#define DBG_PB_DBG_LOG_EN_dbg_log_en_END    (0)


/*****************************************************************************
 �ṹ��    : DBG_TDL_DBG_LOG_FLT_UNION
 �ṹ˵��  : TDL_DBG_LOG_FLT �Ĵ����ṹ���塣��ַƫ����:0xE1C000D0����ֵ:0x0000000F�����:32
 �Ĵ���˵��: ��ά�ɲ��ϱ�LOG ID���������
*****************************************************************************/
typedef union
{
    unsigned int      tdl_dbg_log_flt_reg;
    struct
    {
        unsigned int  dbg_log_flt : 4;  /* bit[0-3] : ��ά�ɲ��ϱ�����������Чָʾ��[n]��Ӧ��n���ϱ����ݣ�[0]��Ӧ��0���ϱ����ݣ�
                                                      'b1����Ӧ��ά�ɲ��������ϱ������
                                                      'b0����Ӧ��ά�ɲ������鲻�ϱ������ */
        unsigned int  reserved    : 28; /* bit[4-31]: ���� */
    } reg;
} DBG_TDL_DBG_LOG_FLT_UNION;
#define DBG_TDL_DBG_LOG_FLT_dbg_log_flt_START  (0)
#define DBG_TDL_DBG_LOG_FLT_dbg_log_flt_END    (3)


/*****************************************************************************
 �ṹ��    : DBG_TDL_DBG_LOG_MODE_UNION
 �ṹ˵��  : TDL_DBG_LOG_MODE �Ĵ����ṹ���塣��ַƫ����:0xE1C000D4����ֵ:0x00000002�����:32
 �Ĵ���˵��: ��ά�ɲ��ϱ����ƼĴ���
*****************************************************************************/
typedef union
{
    unsigned int      tdl_dbg_log_mode_reg;
    struct
    {
        unsigned int  reserved_0   : 1;  /* bit[0]    : ���� */
        unsigned int  dbg_rpt_mode : 1;  /* bit[1]    : ��ά�ɲ������ϱ�ģʽ��
                                                        'b0���������������dbg_pkg_num�����ݰ����Զ�������
                                                        'b1��ֻҪdbg_log_enΪ1���ϱ���û���ϱ��������ơ� */
        unsigned int  reserved_1   : 14; /* bit[2-15] : ���� */
        unsigned int  dbg_pkg_num  : 16; /* bit[16-31]: 
                                                        LOG��Ϣ��ά�ɲ�İ����� */
    } reg;
} DBG_TDL_DBG_LOG_MODE_UNION;
#define DBG_TDL_DBG_LOG_MODE_dbg_rpt_mode_START  (1)
#define DBG_TDL_DBG_LOG_MODE_dbg_rpt_mode_END    (1)
#define DBG_TDL_DBG_LOG_MODE_dbg_pkg_num_START   (16)
#define DBG_TDL_DBG_LOG_MODE_dbg_pkg_num_END     (31)


/*****************************************************************************
 �ṹ��    : DBG_TDL_DBG_LOG_EN_UNION
 �ṹ˵��  : TDL_DBG_LOG_EN �Ĵ����ṹ���塣��ַƫ����:0xE1C000DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ����ʹ�ܼĴ���
*****************************************************************************/
typedef union
{
    unsigned int      tdl_dbg_log_en_reg;
    struct
    {
        unsigned int  dbg_log_en : 1;  /* bit[0]   : ��ά�ɲ�LOGʹ���źţ���dbg_rpt_modeΪ0ʱ�߼����壬������Ҫд�塣
                                                     1'b0����ά�ɲ⹦�ܲ�ʹ��                             1'b1����ά�ɲ⹦��ʹ�� */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} DBG_TDL_DBG_LOG_EN_UNION;
#define DBG_TDL_DBG_LOG_EN_dbg_log_en_START  (0)
#define DBG_TDL_DBG_LOG_EN_dbg_log_en_END    (0)


/*****************************************************************************
 �ṹ��    : DBG_TDL2_DBG_LOG_FLT_UNION
 �ṹ˵��  : TDL2_DBG_LOG_FLT �Ĵ����ṹ���塣��ַƫ����:0xE1C200D0����ֵ:0x0000000F�����:32
 �Ĵ���˵��: ��ά�ɲ��ϱ�LOG ID���������
*****************************************************************************/
typedef union
{
    unsigned int      tdl2_dbg_log_flt_reg;
    struct
    {
        unsigned int  dbg_log_flt : 4;  /* bit[0-3] : ��ά�ɲ��ϱ�����������Чָʾ��[n]��Ӧ��n���ϱ����ݣ�[0]��Ӧ��0���ϱ����ݣ�
                                                      'b1����Ӧ��ά�ɲ��������ϱ������
                                                      'b0����Ӧ��ά�ɲ������鲻�ϱ������ */
        unsigned int  reserved    : 28; /* bit[4-31]: ���� */
    } reg;
} DBG_TDL2_DBG_LOG_FLT_UNION;
#define DBG_TDL2_DBG_LOG_FLT_dbg_log_flt_START  (0)
#define DBG_TDL2_DBG_LOG_FLT_dbg_log_flt_END    (3)


/*****************************************************************************
 �ṹ��    : DBG_TDL2_DBG_LOG_MODE_UNION
 �ṹ˵��  : TDL2_DBG_LOG_MODE �Ĵ����ṹ���塣��ַƫ����:0xE1C200D4����ֵ:0x00000002�����:32
 �Ĵ���˵��: ��ά�ɲ��ϱ����ƼĴ���
*****************************************************************************/
typedef union
{
    unsigned int      tdl2_dbg_log_mode_reg;
    struct
    {
        unsigned int  reserved_0   : 1;  /* bit[0]    : ���� */
        unsigned int  dbg_rpt_mode : 1;  /* bit[1]    : ��ά�ɲ������ϱ�ģʽ��
                                                        'b0���������������dbg_pkg_num�����ݰ����Զ�������
                                                        'b1��ֻҪdbg_log_enΪ1���ϱ���û���ϱ��������ơ� */
        unsigned int  reserved_1   : 14; /* bit[2-15] : ���� */
        unsigned int  dbg_pkg_num  : 16; /* bit[16-31]: 
                                                        LOG��Ϣ��ά�ɲ�İ����� */
    } reg;
} DBG_TDL2_DBG_LOG_MODE_UNION;
#define DBG_TDL2_DBG_LOG_MODE_dbg_rpt_mode_START  (1)
#define DBG_TDL2_DBG_LOG_MODE_dbg_rpt_mode_END    (1)
#define DBG_TDL2_DBG_LOG_MODE_dbg_pkg_num_START   (16)
#define DBG_TDL2_DBG_LOG_MODE_dbg_pkg_num_END     (31)


/*****************************************************************************
 �ṹ��    : DBG_TDL2_DBG_LOG_EN_UNION
 �ṹ˵��  : TDL2_DBG_LOG_EN �Ĵ����ṹ���塣��ַƫ����:0xE1C200DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ����ʹ�ܼĴ���
*****************************************************************************/
typedef union
{
    unsigned int      tdl2_dbg_log_en_reg;
    struct
    {
        unsigned int  dbg_log_en : 1;  /* bit[0]   : ��ά�ɲ�LOGʹ���źţ���dbg_rpt_modeΪ0ʱ�߼����壬������Ҫд�塣
                                                     1'b0����ά�ɲ⹦�ܲ�ʹ��                             1'b1����ά�ɲ⹦��ʹ�� */
        unsigned int  reserved   : 31; /* bit[1-31]: ���� */
    } reg;
} DBG_TDL2_DBG_LOG_EN_UNION;
#define DBG_TDL2_DBG_LOG_EN_dbg_log_en_START  (0)
#define DBG_TDL2_DBG_LOG_EN_dbg_log_en_END    (0)


/*****************************************************************************
 �ṹ��    : DBG_DMA_DBG_BUS_ADDR_UNION
 �ṹ˵��  : DMA_DBG_BUS_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0200����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�BUSͨ��buffer��ַ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_bus_addr_reg;
    struct
    {
        unsigned int  reserved      : 3;  /* bit[0-2] : ������ */
        unsigned int  dma_bus_baddr : 29; /* bit[3-31]: BUS buffer����ַ��DMA�����ݴӿ�ά�ɲ�ģ����Ƶ��Ըõ�ַΪ��ʼ��ַ��buffer�ڡ�8�ֽڶ��롣 */
    } reg;
} DBG_DMA_DBG_BUS_ADDR_UNION;
#define DBG_DMA_DBG_BUS_ADDR_dma_bus_baddr_START  (3)
#define DBG_DMA_DBG_BUS_ADDR_dma_bus_baddr_END    (31)


/*****************************************************************************
 �ṹ��    : DBG_DMA_DBG_BUS_WPTR_UNION
 �ṹ˵��  : DMA_DBG_BUS_WPTR �Ĵ����ṹ���塣��ַƫ����:0x0204����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�BUSͨ��дָ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_bus_wptr_reg;
    struct
    {
        unsigned int  reserved     : 3;  /* bit[0-2] : ������ */
        unsigned int  dma_bus_wptr : 29; /* bit[3-31]: BUS bufferдָ�롣���ά����8�ֽڶ��롣 */
    } reg;
} DBG_DMA_DBG_BUS_WPTR_UNION;
#define DBG_DMA_DBG_BUS_WPTR_dma_bus_wptr_START  (3)
#define DBG_DMA_DBG_BUS_WPTR_dma_bus_wptr_END    (31)


/*****************************************************************************
 �ṹ��    : DBG_DMA_DBG_BUS_RPTR_UNION
 �ṹ˵��  : DMA_DBG_BUS_RPTR �Ĵ����ṹ���塣��ַƫ����:0x0208����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�BUSͨ����ָ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_bus_rptr_reg;
    struct
    {
        unsigned int  reserved     : 3;  /* bit[0-2] : ������ */
        unsigned int  dma_bus_rptr : 29; /* bit[3-31]: BUS buffer��ָ�롣Ӳ����SOCPģ���ȡ���£����ֻ����8�ֽڶ��롣 */
    } reg;
} DBG_DMA_DBG_BUS_RPTR_UNION;
#define DBG_DMA_DBG_BUS_RPTR_dma_bus_rptr_START  (3)
#define DBG_DMA_DBG_BUS_RPTR_dma_bus_rptr_END    (31)


/*****************************************************************************
 �ṹ��    : DBG_DMA_DBG_BUS_CFG_UNION
 �ṹ˵��  : DMA_DBG_BUS_CFG �Ĵ����ṹ���塣��ַƫ����:0x020C����ֵ:0x00000008�����:32
 �Ĵ���˵��: ��ά�ɲ�BUSͨ�����üĴ���
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_bus_cfg_reg;
    struct
    {
        unsigned int  reserved_0      : 3;  /* bit[0-2]  : ������ */
        unsigned int  dma_bus_buf_len : 21; /* bit[3-23] : BUS buffer���ȡ�8�ֽڶ��롣 */
        unsigned int  reserved_1      : 8;  /* bit[24-31]: ������ */
    } reg;
} DBG_DMA_DBG_BUS_CFG_UNION;
#define DBG_DMA_DBG_BUS_CFG_dma_bus_buf_len_START  (3)
#define DBG_DMA_DBG_BUS_CFG_dma_bus_buf_len_END    (23)


/*****************************************************************************
 �ṹ��    : DBG_DMA_DBG_LOG_ADDR_UNION
 �ṹ˵��  : DMA_DBG_LOG_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0210����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�LOGͨ��buffer��ַ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_log_addr_reg;
    struct
    {
        unsigned int  reserved  : 3;  /* bit[0-2] : ������ */
        unsigned int  log_baddr : 29; /* bit[3-31]: LOG buffer����ַ��DMA�����ݴӿ�ά�ɲ�ģ����Ƶ��Ըõ�ַΪ��ʼ��ַ��buffer�ڡ�8�ֽڶ��롣 */
    } reg;
} DBG_DMA_DBG_LOG_ADDR_UNION;
#define DBG_DMA_DBG_LOG_ADDR_log_baddr_START  (3)
#define DBG_DMA_DBG_LOG_ADDR_log_baddr_END    (31)


/*****************************************************************************
 �ṹ��    : DBG_DMA_DBG_LOG_WPTR_UNION
 �ṹ˵��  : DMA_DBG_LOG_WPTR �Ĵ����ṹ���塣��ַƫ����:0x0214����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�LOGͨ��дָ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_log_wptr_reg;
    struct
    {
        unsigned int  reserved : 3;  /* bit[0-2] : ������ */
        unsigned int  log_wptr : 29; /* bit[3-31]: LOG bufferдָ�롣���ά����8�ֽڶ��롣 */
    } reg;
} DBG_DMA_DBG_LOG_WPTR_UNION;
#define DBG_DMA_DBG_LOG_WPTR_log_wptr_START  (3)
#define DBG_DMA_DBG_LOG_WPTR_log_wptr_END    (31)


/*****************************************************************************
 �ṹ��    : DBG_DMA_DBG_LOG_RPTR_UNION
 �ṹ˵��  : DMA_DBG_LOG_RPTR �Ĵ����ṹ���塣��ַƫ����:0x0218����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�LOGͨ����ָ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_log_rptr_reg;
    struct
    {
        unsigned int  reserved : 3;  /* bit[0-2] : ������ */
        unsigned int  log_rptr : 29; /* bit[3-31]: LOG buffer��ָ�롣Ӳ����SOCPģ���ȡ���£����ֻ����8�ֽڶ��롣 */
    } reg;
} DBG_DMA_DBG_LOG_RPTR_UNION;
#define DBG_DMA_DBG_LOG_RPTR_log_rptr_START  (3)
#define DBG_DMA_DBG_LOG_RPTR_log_rptr_END    (31)


/*****************************************************************************
 �ṹ��    : DBG_DMA_DBG_LOG_CFG_UNION
 �ṹ˵��  : DMA_DBG_LOG_CFG �Ĵ����ṹ���塣��ַƫ����:0x021C����ֵ:0x00000008�����:32
 �Ĵ���˵��: ��ά�ɲ�LOGͨ�����üĴ���
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_log_cfg_reg;
    struct
    {
        unsigned int  reserved_0  : 3;  /* bit[0-2]  : ������ */
        unsigned int  log_buf_len : 21; /* bit[3-23] : LOG buffer���ȡ�8�ֽڶ��롣 */
        unsigned int  reserved_1  : 8;  /* bit[24-31]: ������ */
    } reg;
} DBG_DMA_DBG_LOG_CFG_UNION;
#define DBG_DMA_DBG_LOG_CFG_log_buf_len_START  (3)
#define DBG_DMA_DBG_LOG_CFG_log_buf_len_END    (23)


/*****************************************************************************
 �ṹ��    : DBG_DMA_DBG_DS_ADDR_UNION
 �ṹ˵��  : DMA_DBG_DS_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0280����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�����ͨ��buffer��ַ
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_ds_addr_reg;
    struct
    {
        unsigned int  reserved : 3;  /* bit[0-2] : ������ */
        unsigned int  ds_baddr : 29; /* bit[3-31]: ��ά�ɲ����ݲɼ�ͨ��buffer��ʼ��ַ��8�ֽڶ��롣 */
    } reg;
} DBG_DMA_DBG_DS_ADDR_UNION;
#define DBG_DMA_DBG_DS_ADDR_ds_baddr_START  (3)
#define DBG_DMA_DBG_DS_ADDR_ds_baddr_END    (31)


/*****************************************************************************
 �ṹ��    : DBG_DMA_DBG_DS_WPTR_UNION
 �ṹ˵��  : DMA_DBG_DS_WPTR �Ĵ����ṹ���塣��ַƫ����:0x0284����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�����ͨ��дָ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_ds_wptr_reg;
    struct
    {
        unsigned int  reserved : 3;  /* bit[0-2] : ������ */
        unsigned int  ds_wptr  : 29; /* bit[3-31]: ��ά�ɲ����ݲɼ�ͨ��дָ�롣���ά����8�ֽڶ��롣 */
    } reg;
} DBG_DMA_DBG_DS_WPTR_UNION;
#define DBG_DMA_DBG_DS_WPTR_ds_wptr_START   (3)
#define DBG_DMA_DBG_DS_WPTR_ds_wptr_END     (31)


/*****************************************************************************
 �ṹ��    : DBG_DMA_DBG_DS_RPTR_UNION
 �ṹ˵��  : DMA_DBG_DS_RPTR �Ĵ����ṹ���塣��ַƫ����:0x0288����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�����ͨ����ָ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_ds_rptr_reg;
    struct
    {
        unsigned int  reserved : 3;  /* bit[0-2] : ������ */
        unsigned int  ds_rptr  : 29; /* bit[3-31]: ��ά�ɲ����ݲɼ�ͨ����ָ�롣ָʾ�����������ʼ��ַ�����ά����8�ֽڶ��롣 */
    } reg;
} DBG_DMA_DBG_DS_RPTR_UNION;
#define DBG_DMA_DBG_DS_RPTR_ds_rptr_START   (3)
#define DBG_DMA_DBG_DS_RPTR_ds_rptr_END     (31)


/*****************************************************************************
 �ṹ��    : DBG_DMA_DBG_DS_CFG_UNION
 �ṹ˵��  : DMA_DBG_DS_CFG �Ĵ����ṹ���塣��ַƫ����:0x028C����ֵ:0x00000008�����:32
 �Ĵ���˵��: ��ά�ɲ�����ͨ�����üĴ���
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_ds_cfg_reg;
    struct
    {
        unsigned int  reserved_0       : 3;  /* bit[0-2]  : ������ */
        unsigned int  ds_buf_len       : 25; /* bit[3-27] : ��ά�ɲ����ݲɼ�ͨ��buffer���ȡ�8�ֽڶ��룬����Ϊ������������ */
        unsigned int  reserved_1       : 2;  /* bit[28-29]: ������ */
        unsigned int  ds_overflow_sts  : 1;  /* bit[30]   : ��ά�ɲ����ݲɼ�ͨ��buffer���״̬��
                                                            0��δ���(ds_overflow_ctrl=0)��δѭ������(ds_overflow_ctrl=1)
                                                            1�������(ds_overflow_ctrl=0)����ѭ������(ds_overflow_ctrl=1) */
        unsigned int  ds_overflow_ctrl : 1;  /* bit[31]   : ��ά�ɲ����ݲɼ�ͨ��buffer���������ơ�
                                                            0��stop������ǰbuffer�ĺ������ݶ�����
                                                            1��buffer���ǣ��ص���ʼ��ַд�롣 */
    } reg;
} DBG_DMA_DBG_DS_CFG_UNION;
#define DBG_DMA_DBG_DS_CFG_ds_buf_len_START        (3)
#define DBG_DMA_DBG_DS_CFG_ds_buf_len_END          (27)
#define DBG_DMA_DBG_DS_CFG_ds_overflow_sts_START   (30)
#define DBG_DMA_DBG_DS_CFG_ds_overflow_sts_END     (30)
#define DBG_DMA_DBG_DS_CFG_ds_overflow_ctrl_START  (31)
#define DBG_DMA_DBG_DS_CFG_ds_overflow_ctrl_END    (31)


/*****************************************************************************
 �ṹ��    : DBG_DMA_DBG_PTR_ADDR_UNION
 �ṹ˵��  : DMA_DBG_PTR_ADDR �Ĵ����ṹ���塣��ַƫ����:0x0290����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�buffer��дָ����ʼ��ַ�Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_ptr_addr_reg;
    struct
    {
        unsigned int  reserved : 2;  /* bit[0-1] : ������ */
        unsigned int  ptr_addr : 30; /* bit[2-31]: ��ά�ɲ�ͨ��bufferдָ����ʼ��ַ����ŵ���LOG 0ͨ����дָ�룬�������ΰ��չ̶���ʽ�������LOGͨ��������ͨ��ָ�롣4�ֽڶ��롣 */
    } reg;
} DBG_DMA_DBG_PTR_ADDR_UNION;
#define DBG_DMA_DBG_PTR_ADDR_ptr_addr_START  (2)
#define DBG_DMA_DBG_PTR_ADDR_ptr_addr_END    (31)


/*****************************************************************************
 �ṹ��    : DBG_DMA_DBG_DS_CH_EN_UNION
 �ṹ˵��  : DMA_DBG_DS_CH_EN �Ĵ����ṹ���塣��ַƫ����:0x0294����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�ͨ������ʹ�ܼĴ���
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_ds_ch_en_reg;
    struct
    {
        unsigned int  ds_ch_en : 1;  /* bit[0]   : ����ͨ��ʹ�ܡ�
                                                   0����ʹ�ܣ�
                                                   1��ʹ�ܡ� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} DBG_DMA_DBG_DS_CH_EN_UNION;
#define DBG_DMA_DBG_DS_CH_EN_ds_ch_en_START  (0)
#define DBG_DMA_DBG_DS_CH_EN_ds_ch_en_END    (0)


/*****************************************************************************
 �ṹ��    : DBG_DBG_CH_STS0_UNION
 �ṹ˵��  : DBG_CH_STS0 �Ĵ����ṹ���塣��ַƫ����:0x029C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�ͨ��״̬�Ĵ���0
*****************************************************************************/
typedef union
{
    unsigned int      dbg_ch_sts0_reg;
    struct
    {
        unsigned int  log0_overflow : 1;  /* bit[0]    : LOG0ͨ��buffer���硣
                                                         0�����쳣��
                                                         1���쳣�� */
        unsigned int  log1_overflow : 1;  /* bit[1]    : LOG1ͨ��buffer���硣
                                                         0�����쳣��
                                                         1���쳣�� */
        unsigned int  reserved_0    : 10; /* bit[2-11] : ������ */
        unsigned int  log0_unmtch   : 1;  /* bit[12]   : LOG0ͨ����ͷ����βָʾ��ƥ�䡣
                                                         0�����쳣��
                                                         1���쳣�� */
        unsigned int  log1_unmtch   : 1;  /* bit[13]   : LOG1ͨ����ͷ����βָʾ��ƥ�䡣
                                                         0�����쳣��
                                                         1���쳣�� */
        unsigned int  reserved_1    : 6;  /* bit[14-19]: ������ */
        unsigned int  ds_unmtch     : 1;  /* bit[20]   : ����ͨ����ͷ����βָʾ��ƥ�䡣ÿ�����ݰ������԰�ͷָʾsop��ʼ���԰�βָʾeop��������������յ�sop����eop����״̬�ᴥ����
                                                         0�����쳣��
                                                         1���쳣�� */
        unsigned int  log0_long_pkt : 1;  /* bit[21]   : LOG0ͨ�������쳣ָʾ��ָʾʵ�ʰ����ȴ��ڰ�ͷ������ָʾ�İ�����д1�����
                                                         0�����쳣��
                                                         1���쳣�� */
        unsigned int  log1_long_pkt : 1;  /* bit[22]   : LOG1ͨ�������쳣ָʾ��ָʾʵ�ʰ����ȴ��ڰ�ͷ������ָʾ�İ�����д1�����
                                                         0�����쳣��
                                                         1���쳣�� */
        unsigned int  reserved_2    : 6;  /* bit[23-28]: ������ */
        unsigned int  ds_long_pkt   : 1;  /* bit[29]   : ����ͨ�������쳣ָʾ��ָʾʵ�ʰ����ȴ��ڰ�ͷ������ָʾ�İ�����д1�����
                                                         0�����쳣��
                                                         1���쳣�� */
        unsigned int  reserved_3    : 2;  /* bit[30-31]: ������ */
    } reg;
} DBG_DBG_CH_STS0_UNION;
#define DBG_DBG_CH_STS0_log0_overflow_START  (0)
#define DBG_DBG_CH_STS0_log0_overflow_END    (0)
#define DBG_DBG_CH_STS0_log1_overflow_START  (1)
#define DBG_DBG_CH_STS0_log1_overflow_END    (1)
#define DBG_DBG_CH_STS0_log0_unmtch_START    (12)
#define DBG_DBG_CH_STS0_log0_unmtch_END      (12)
#define DBG_DBG_CH_STS0_log1_unmtch_START    (13)
#define DBG_DBG_CH_STS0_log1_unmtch_END      (13)
#define DBG_DBG_CH_STS0_ds_unmtch_START      (20)
#define DBG_DBG_CH_STS0_ds_unmtch_END        (20)
#define DBG_DBG_CH_STS0_log0_long_pkt_START  (21)
#define DBG_DBG_CH_STS0_log0_long_pkt_END    (21)
#define DBG_DBG_CH_STS0_log1_long_pkt_START  (22)
#define DBG_DBG_CH_STS0_log1_long_pkt_END    (22)
#define DBG_DBG_CH_STS0_ds_long_pkt_START    (29)
#define DBG_DBG_CH_STS0_ds_long_pkt_END      (29)


/*****************************************************************************
 �ṹ��    : DBG_DMA_DBG_LOG_CH_EN_UNION
 �ṹ˵��  : DMA_DBG_LOG_CH_EN �Ĵ����ṹ���塣��ַƫ����:0x02B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: ��ά�ɲ�LOGͨ��ʹ�ܼĴ���
*****************************************************************************/
typedef union
{
    unsigned int      dma_dbg_log_ch_en_reg;
    struct
    {
        unsigned int  log_ch_en : 1;  /* bit[0]   : LOGͨ��ʹ�ܼĴ�����
                                                    0����ʹ�ܣ�
                                                    1��ʹ�ܡ� */
        unsigned int  reserved  : 31; /* bit[1-31]: ������ */
    } reg;
} DBG_DMA_DBG_LOG_CH_EN_UNION;
#define DBG_DMA_DBG_LOG_CH_EN_log_ch_en_START  (0)
#define DBG_DMA_DBG_LOG_CH_EN_log_ch_en_END    (0)


/*****************************************************************************
 �ṹ��    : DBG_COM_CLK_EN_UNION
 �ṹ˵��  : COM_CLK_EN �Ĵ����ṹ���塣��ַƫ����:0xE1FC00E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: COMʱ��ʹ��
*****************************************************************************/
typedef union
{
    unsigned int      com_clk_en_reg;
    struct
    {
        unsigned int  reserved_0        : 6;  /* bit[0-5] : ���� */
        unsigned int  com_tl_dbg_clk_en : 1;  /* bit[6]   : dbgʱ��ʹ���źš�ֻд�źţ�д1ʹ�� */
        unsigned int  reserved_1        : 25; /* bit[7-31]: ���� */
    } reg;
} DBG_COM_CLK_EN_UNION;
#define DBG_COM_CLK_EN_com_tl_dbg_clk_en_START  (6)
#define DBG_COM_CLK_EN_com_tl_dbg_clk_en_END    (6)


/*****************************************************************************
 �ṹ��    : DBG_COM_SRST_DIS_UNION
 �ṹ˵��  : COM_SRST_DIS �Ĵ����ṹ���塣��ַƫ����:0xE1FC00F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: COM��λ���
*****************************************************************************/
typedef union
{
    unsigned int      com_srst_dis_reg;
    struct
    {
        unsigned int  reserved_0          : 4;  /* bit[0-3] : ���� */
        unsigned int  com_l_sdr_srst_dis  : 1;  /* bit[4]   : sdr��λ����źš�ֻд�źţ�д1ʹ������ */
        unsigned int  reserved_1          : 1;  /* bit[5]   : ���� */
        unsigned int  com_tl_dbg_srst_dis : 1;  /* bit[6]   : dbg��λ����źš�ֻд�źţ�д1ʹ������ */
        unsigned int  reserved_2          : 25; /* bit[7-31]: ���� */
    } reg;
} DBG_COM_SRST_DIS_UNION;
#define DBG_COM_SRST_DIS_com_l_sdr_srst_dis_START   (4)
#define DBG_COM_SRST_DIS_com_l_sdr_srst_dis_END     (4)
#define DBG_COM_SRST_DIS_com_tl_dbg_srst_dis_START  (6)
#define DBG_COM_SRST_DIS_com_tl_dbg_srst_dis_END    (6)


/*****************************************************************************
 �ṹ��    : DBG_DBG_AGC_DATA_SEL_UNION
 �ṹ˵��  : DBG_AGC_DATA_SEL �Ĵ����ṹ���塣��ַƫ����:0xE19912DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: RX��������ѡ��
*****************************************************************************/
typedef union
{
    unsigned int      dbg_agc_data_sel_reg;
    struct
    {
        unsigned int  dbg_data_sel : 5;  /* bit[0-4]  : �������ݰ���ѡ�񣬱�ʾ����λ�á�
                                                        0��ADC����źţ�W��TDS���ã�
                                                        1��spmv������źţ�W��TDS���ã�
                                                        2��dcoc����źţ���TDSʹ�ã�
                                                        3��dgt1����źţ���TDSʹ�ã�
                                                        4��fir����źţ�W��TDS���ã�
                                                        5��rxiq����źţ�W��TDS���ã�
                                                        6��dwf����źţ�W��TDS���ã�
                                                        7��codc����źţ�W��TDS��ʹ�ã�
                                                        8��sc_filter����źţ�W��TDS��ʹ�ã�
                                                        9��TDS��rrc����źţ���TDSʹ�ã�
                                                        10��TDS��dgt2����źţ���TDSʹ�ã�
                                                        11��W��rrc����źţ����ز��͸��ز���ʱ���ã�
                                                        12��W��8bitDAGC����źţ����ز��͸��ز���ʱ���ã�
                                                        13��W��4bitDAGC����źţ����ز��͸��ز���ʱ���ã�
                                                        14��dwf�ĸ��ز�����źţ���Wʹ�ã�
                                                        15��sc_filter�ĸ��ز������źţ���Wʹ�ã�
                                                        16��rrc�ĸ��ز������źţ���Wʹ�ã�
                                                        17������Ϊ2047�����ǲ�����Ӧ12bits���ݣ�
                                                        18������Ϊ127�����ǲ�����Ӧ8bit���ݣ�
                                                        19��Ƶ��У��freq_error�������12bitΪ���ݣ�
                                                        20�����ز�FIFO�������12bitΪ���ݣ�
                                                        21�����ز�FIFO�������12bitΪ���ݣ�
                                                        defaultΪȥг���������źš�
                                                        �������ݸ�ʽ��[11:0]Ϊ���ݣ�[12]Ϊ0��ʾ���ز���Ϊ1��ʾ���ز���[13]Ϊ0��ʾ����1��Ϊ1��ʾ����2�� */
        unsigned int  reserved_0   : 3;  /* bit[5-7]  : ���� */
        unsigned int  at1_dbg_en   : 1;  /* bit[8]    : �����߲���ʹ�ܣ��ߵ�ƽ��Ч�� */
        unsigned int  at2_dbg_en   : 1;  /* bit[9]    : �����߲���ʹ���ߵ�ƽ��Ч�� */
        unsigned int  reserved_1   : 22; /* bit[10-31]: ���� */
    } reg;
} DBG_DBG_AGC_DATA_SEL_UNION;
#define DBG_DBG_AGC_DATA_SEL_dbg_data_sel_START  (0)
#define DBG_DBG_AGC_DATA_SEL_dbg_data_sel_END    (4)
#define DBG_DBG_AGC_DATA_SEL_at1_dbg_en_START    (8)
#define DBG_DBG_AGC_DATA_SEL_at1_dbg_en_END      (8)
#define DBG_DBG_AGC_DATA_SEL_at2_dbg_en_START    (9)
#define DBG_DBG_AGC_DATA_SEL_at2_dbg_en_END      (9)


/*****************************************************************************
 �ṹ��    : DBG_DBG_DATA_SEL_UNION
 �ṹ˵��  : DBG_DATA_SEL �Ĵ����ṹ���塣��ַƫ����:0xE199E814����ֵ:0x00000000�����:32
 �Ĵ���˵��: TX��������ѡ��
*****************************************************************************/
typedef union
{
    unsigned int      dbg_data_sel_reg;
    struct
    {
        unsigned int  tds_dbg_data_sel : 3;  /* bit[0-2] : dbg����ѡ��
                                                           3'd0: RRC���������
                                                           3'd1: CFR/FIR���������
                                                           3'd2: PC���������
                                                           3'd3: phase comp�������
                                                           3'd4: Txiq�������
                                                           3'd5:FIFO�������
                                                           3'd6:sc_filter�������
                                                           3'd7:freq_error��������� */
        unsigned int  reserved         : 29; /* bit[3-31]: ���� */
    } reg;
} DBG_DBG_DATA_SEL_UNION;
#define DBG_DBG_DATA_SEL_tds_dbg_data_sel_START  (0)
#define DBG_DBG_DATA_SEL_tds_dbg_data_sel_END    (2)


/*****************************************************************************
 �ṹ��    : DBG_DBG_EN_UNION
 �ṹ˵��  : DBG_EN �Ĵ����ṹ���塣��ַƫ����:0x0708����ֵ:0x00000002�����:32
 �Ĵ���˵��: ʹ�ܼĴ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_en_reg;
    struct
    {
        unsigned int  dbg_en       : 1;  /* bit[0]    : ��ά�ɲ�ʹ���źţ���dbg_rpt_modeΪ0ʱ�߼����壬������Ҫд�塣
                                                        1'b0����ά�ɲ⹦�ܲ�ʹ��1'b1����ά�ɲ⹦��ʹ�� */
        unsigned int  dbg_rpt_mode : 1;  /* bit[1]    : ��ά�ɲ������ϱ�ģʽ��
                                                        'b0���������������dbg_pkg_num�����ݰ����Զ�������
                                                        'b1��ֻҪdbg_enΪ1���ϱ���û���ϱ��������ơ� */
        unsigned int  reserved     : 14; /* bit[2-15] : ���� */
        unsigned int  dbg_pkg_num  : 16; /* bit[16-31]: ��ά�ɲ�İ����� */
    } reg;
} DBG_DBG_EN_UNION;
#define DBG_DBG_EN_dbg_en_START        (0)
#define DBG_DBG_EN_dbg_en_END          (0)
#define DBG_DBG_EN_dbg_rpt_mode_START  (1)
#define DBG_DBG_EN_dbg_rpt_mode_END    (1)
#define DBG_DBG_EN_dbg_pkg_num_START   (16)
#define DBG_DBG_EN_dbg_pkg_num_END     (31)


/*****************************************************************************
 �ṹ��    : DBG_DBG_FLT_UNION
 �ṹ˵��  : DBG_FLT �Ĵ����ṹ���塣��ַƫ����:0x0710����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ѡ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_flt_reg;
    struct
    {
        unsigned int  dbg_flt  : 16; /* bit[0-15] : ��ά�ɲ��ڲ�����ָʾ��
                                                    1���ϱ�mipi����
                                                    2���ϱ�ssi����
                                                    3������dbg�ϱ�����
                                                    ���������� */
        unsigned int  reserved : 16; /* bit[16-31]: ���� */
    } reg;
} DBG_DBG_FLT_UNION;
#define DBG_DBG_FLT_dbg_flt_START   (0)
#define DBG_DBG_FLT_dbg_flt_END     (15)


/*****************************************************************************
 �ṹ��    : DBG_DBG_MIPI_CH_MASK_UNION
 �ṹ˵��  : DBG_MIPI_CH_MASK �Ĵ����ṹ���塣��ַƫ����:0x0714����ֵ:0x00000000�����:32
 �Ĵ���˵��: mipiͨ��ѡ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_mipi_ch_mask_reg;
    struct
    {
        unsigned int  dbg_mipi_ch_mask : 4;  /* bit[0-3] : ��ά�ɲ�mipi�ɼ�����ͨ������ָʾ��
                                                           dbg_mipi_ch_mask[X],X=0~3,��
                                                           0��ͨ��X��mipi���ݲ��ɼ�
                                                           1���ɼ�ͨ��X��mipi���� */
        unsigned int  reserved         : 28; /* bit[4-31]: ���� */
    } reg;
} DBG_DBG_MIPI_CH_MASK_UNION;
#define DBG_DBG_MIPI_CH_MASK_dbg_mipi_ch_mask_START  (0)
#define DBG_DBG_MIPI_CH_MASK_dbg_mipi_ch_mask_END    (3)


/*****************************************************************************
 �ṹ��    : DBG_DBG_SSI_CH_MASK_UNION
 �ṹ˵��  : DBG_SSI_CH_MASK �Ĵ����ṹ���塣��ַƫ����:0x0718����ֵ:0x00000000�����:32
 �Ĵ���˵��: ssiͨ��ѡ��Ĵ���
*****************************************************************************/
typedef union
{
    unsigned int      dbg_ssi_ch_mask_reg;
    struct
    {
        unsigned int  dbg_ssi_ch_mask : 4;  /* bit[0-3] : ��ά�ɲ�ssi�ɼ�����ͨ������ָʾ��
                                                          dbg_ssi_ch_mask[X],X=0~3,��
                                                          0��ͨ��X��ssi���ݲ��ɼ�
                                                          1���ɼ�ͨ��X��ssi���� */
        unsigned int  reserved        : 28; /* bit[4-31]: ���� */
    } reg;
} DBG_DBG_SSI_CH_MASK_UNION;
#define DBG_DBG_SSI_CH_MASK_dbg_ssi_ch_mask_START  (0)
#define DBG_DBG_SSI_CH_MASK_dbg_ssi_ch_mask_END    (3)


/*****************************************************************************
 �ṹ��    : DBG_ch1_testmode_UNION
 �ṹ˵��  : ch1_testmode �Ĵ����ṹ���塣��ַƫ����:0xE1FA0104����ֵ:0x00�����:8
 �Ĵ���˵��: ����ģʽ�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned char      ch1_testmode_reg;
    struct
    {
        unsigned char  ch1_pwr_on_rst  : 1;  /* bit[0]  : ȫ����λ�źţ�
                                                          0������λ(Ĭ��)
                                                          1����λ�������ֵ�·��ģ���· */
        unsigned char  ch1_rx_chnl_sel : 2;  /* bit[1-2]: RXģ�����ģʽ��ͨ��ѡ��
                                                          00�����RXA Iģ�����������(Ĭ��)
                                                          01�����RXA Qģ�����������
                                                          10�����RXB Iģ�����������
                                                          11�����RXB Qģ����������� */
        unsigned char  ch1_test_mode   : 3;  /* bit[3-5]: bit[4:3]����ģʽ���ƣ�
                                                          00������ģʽ(Ĭ��)
                                                          01�������㷨�߼�����ģʽ
                                                          10��RXģ�����ģʽ(bypass RX�����˲���)
                                                          11���ӿڻ���
                                                          bit[5]Reserved */
        unsigned char  ch1_rx_sw_rst   : 1;  /* bit[6]  : ���ֲ���RXͨ����λ�źţ�
                                                          0������λ(Ĭ��)
                                                          1����λ */
        unsigned char  ch1_tx_sw_rst   : 1;  /* bit[7]  : ���ֲ���TXͨ����λ�źţ�
                                                          0������λ(Ĭ��)
                                                          1����λ */
    } reg;
} DBG_ch1_testmode_UNION;
#define DBG_ch1_testmode_ch1_pwr_on_rst_START   (0)
#define DBG_ch1_testmode_ch1_pwr_on_rst_END     (0)
#define DBG_ch1_testmode_ch1_rx_chnl_sel_START  (1)
#define DBG_ch1_testmode_ch1_rx_chnl_sel_END    (2)
#define DBG_ch1_testmode_ch1_test_mode_START    (3)
#define DBG_ch1_testmode_ch1_test_mode_END      (5)
#define DBG_ch1_testmode_ch1_rx_sw_rst_START    (6)
#define DBG_ch1_testmode_ch1_rx_sw_rst_END      (6)
#define DBG_ch1_testmode_ch1_tx_sw_rst_START    (7)
#define DBG_ch1_testmode_ch1_tx_sw_rst_END      (7)


/*****************************************************************************
 �ṹ��    : DBG_ch0_testmode_UNION
 �ṹ˵��  : ch0_testmode �Ĵ����ṹ���塣��ַƫ����:0xE1FA0284����ֵ:0x00�����:8
 �Ĵ���˵��: ����ģʽ�Ĵ�����
*****************************************************************************/
typedef union
{
    unsigned char      ch0_testmode_reg;
    struct
    {
        unsigned char  ch0_pwr_on_rst  : 1;  /* bit[0]  : ȫ����λ�źţ�
                                                          0������λ(Ĭ��)
                                                          1����λ�������ֵ�·��ģ���· */
        unsigned char  ch0_rx_chnl_sel : 2;  /* bit[1-2]: RXģ�����ģʽ��ͨ��ѡ��
                                                          00�����RXA Iģ�����������(Ĭ��)
                                                          01�����RXA Qģ�����������
                                                          10�����RXB Iģ�����������
                                                          11�����RXB Qģ����������� */
        unsigned char  ch0_test_mode   : 3;  /* bit[3-5]: bit[4:3]����ģʽ���ƣ�
                                                          00������ģʽ(Ĭ��)
                                                          01�������㷨�߼�����ģʽ
                                                          10��RXģ�����ģʽ(bypass RX�����˲���)
                                                          11���ӿڻ���
                                                          bit[5] debug_en��
                                                          1��ʹ�ܣ���debug�ź�ͨ���ܽŸ��ó�ȥ��
                                                          0����ʹ�ܡ� */
        unsigned char  ch0_rx_sw_rst   : 1;  /* bit[6]  : ���ֲ���RXͨ����λ�źţ�
                                                          0������λ(Ĭ��)
                                                          1����λ */
        unsigned char  ch0_tx_sw_rst   : 1;  /* bit[7]  : ���ֲ���TXͨ����λ�źţ�
                                                          0������λ(Ĭ��)
                                                          1����λ */
    } reg;
} DBG_ch0_testmode_UNION;
#define DBG_ch0_testmode_ch0_pwr_on_rst_START   (0)
#define DBG_ch0_testmode_ch0_pwr_on_rst_END     (0)
#define DBG_ch0_testmode_ch0_rx_chnl_sel_START  (1)
#define DBG_ch0_testmode_ch0_rx_chnl_sel_END    (2)
#define DBG_ch0_testmode_ch0_test_mode_START    (3)
#define DBG_ch0_testmode_ch0_test_mode_END      (5)
#define DBG_ch0_testmode_ch0_rx_sw_rst_START    (6)
#define DBG_ch0_testmode_ch0_rx_sw_rst_END      (6)
#define DBG_ch0_testmode_ch0_tx_sw_rst_START    (7)
#define DBG_ch0_testmode_ch0_tx_sw_rst_END      (7)




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

#endif /* end of bbp_dbg_interface.h */
