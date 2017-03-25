/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_otg_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-05-05 09:45:44
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��5��5��
    ��    ��   : s00249479
    �޸�����   : �ӡ�Hi6250V100 SOC�Ĵ����ֲ�_OTG.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_OTG_INTERFACE_H__
#define __SOC_OTG_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) OTG
 ****************************************************************************/
/* �Ĵ���˵����ȫ�ֿ��ƺ�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_GOTGCTL_UNION */
#define SOC_OTG_GOTGCTL_ADDR(base)                    ((base) + (0x0000))

/* �Ĵ���˵����ȫ��OTG�ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_GOTGINT_UNION */
#define SOC_OTG_GOTGINT_ADDR(base)                    ((base) + (0x0004))

/* �Ĵ���˵����ȫ��AHB���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_GAHBCFG_UNION */
#define SOC_OTG_GAHBCFG_ADDR(base)                    ((base) + (0x0008))

/* �Ĵ���˵����ȫ��USB���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_GUSBCFG_UNION */
#define SOC_OTG_GUSBCFG_ADDR(base)                    ((base) + (0x000C))

/* �Ĵ���˵����ȫ�ָ�λ���ƼĴ�����
   λ����UNION�ṹ:  SOC_OTG_GRSTCTL_UNION */
#define SOC_OTG_GRSTCTL_ADDR(base)                    ((base) + (0x0010))

/* �Ĵ���˵����ȫ���ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_GINTSTS_UNION */
#define SOC_OTG_GINTSTS_ADDR(base)                    ((base) + (0x0014))

/* �Ĵ���˵����ȫ���ж����μĴ�����
   λ����UNION�ṹ:  SOC_OTG_GINTMSK_UNION */
#define SOC_OTG_GINTMSK_ADDR(base)                    ((base) + (0x0018))

/* �Ĵ���˵����ȫ�ֽ���FIFO״̬�����Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_GRXSTSR_UNION */
#define SOC_OTG_GRXSTSR_ADDR(base)                    ((base) + (0x001C))

/* �Ĵ���˵����ȫ�ֽ���FIFO״̬�����Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_GRXSTSP_UNION */
#define SOC_OTG_GRXSTSP_ADDR(base)                    ((base) + (0x0020))

/* �Ĵ���˵����ȫ�ֽ���FIFO��С�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_GRXFSIZ_UNION */
#define SOC_OTG_GRXFSIZ_ADDR(base)                    ((base) + (0x0024))

/* �Ĵ���˵����ȫ�ַ����ڷ���FIFO��С�Ĵ����� (Host Mode and Device Shared FIFO Mode)
   λ����UNION�ṹ:  SOC_OTG_GNPTXFSIZ_UNION */
#define SOC_OTG_GNPTXFSIZ_ADDR(base)                  ((base) + (0x0028))

/* �Ĵ���˵����ȫ�ַ����ڷ���FIFO״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_GNPTXSTS_UNION */
#define SOC_OTG_GNPTXSTS_ADDR(base)                   ((base) + (0x002C))

/* �Ĵ���˵����USB IP�汾�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_GSNPSID_UNION */
#define SOC_OTG_GSNPSID_ADDR(base)                    ((base) + (0x0040))

/* �Ĵ���˵����Ӳ�����üĴ���1��
   λ����UNION�ṹ:  SOC_OTG_GHWCFG1_UNION */
#define SOC_OTG_GHWCFG1_ADDR(base)                    ((base) + (0x0044))

/* �Ĵ���˵����Ӳ�����üĴ���2��
   λ����UNION�ṹ:  SOC_OTG_GHWCFG2_UNION */
#define SOC_OTG_GHWCFG2_ADDR(base)                    ((base) + (0x0048))

/* �Ĵ���˵����Ӳ�����üĴ���3��
   λ����UNION�ṹ:  SOC_OTG_GHWCFG3_UNION */
#define SOC_OTG_GHWCFG3_ADDR(base)                    ((base) + (0x004C))

/* �Ĵ���˵����Ӳ�����üĴ���4��
   λ����UNION�ṹ:  SOC_OTG_GHWCFG4_UNION */
#define SOC_OTG_GHWCFG4_ADDR(base)                    ((base) + (0x0050))

/* �Ĵ���˵����LPM���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_GLPMCFG_UNION */
#define SOC_OTG_GLPMCFG_ADDR(base)                    ((base) + (0x0054))

/* �Ĵ���˵��������ģʽ������ƼĴ�����
   λ����UNION�ṹ:  SOC_OTG_GPWRDN_UNION */
#define SOC_OTG_GPWRDN_ADDR(base)                     ((base) + (0x0058))

/* �Ĵ���˵������̬FIFO���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_GDFIFOCFG_UNION */
#define SOC_OTG_GDFIFOCFG_ADDR(base)                  ((base) + (0x005C))

/* �Ĵ���˵����ADP���ƼĴ�����
   λ����UNION�ṹ:  SOC_OTG_GADPCTL_UNION */
#define SOC_OTG_GADPCTL_ADDR(base)                    ((base) + (0x0060))

/* �Ĵ���˵����Host���ڷ���FIFO���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_HPTXFSIZ_UNION */
#define SOC_OTG_HPTXFSIZ_ADDR(base)                   ((base) + (0x0100))

/* �Ĵ���˵����Device IN�˵�1����FIFO���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPTXF1_UNION */
#define SOC_OTG_DIEPTXF1_ADDR(base)                   ((base) + (0x0104))

/* �Ĵ���˵����Device IN�˵�2����FIFO���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPTXF2_UNION */
#define SOC_OTG_DIEPTXF2_ADDR(base)                   ((base) + (0x0108))

/* �Ĵ���˵����Device IN�˵�3����FIFO���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPTXF3_UNION */
#define SOC_OTG_DIEPTXF3_ADDR(base)                   ((base) + (0x010C))

/* �Ĵ���˵����Device IN�˵�4����FIFO���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPTXF4_UNION */
#define SOC_OTG_DIEPTXF4_ADDR(base)                   ((base) + (0x0110))

/* �Ĵ���˵����Device IN�˵�5����FIFO���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPTXF5_UNION */
#define SOC_OTG_DIEPTXF5_ADDR(base)                   ((base) + (0x0114))

/* �Ĵ���˵����Device IN�˵�6����FIFO���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPTXF6_UNION */
#define SOC_OTG_DIEPTXF6_ADDR(base)                   ((base) + (0x0118))

/* �Ĵ���˵����Device IN�˵�7����FIFO���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPTXF7_UNION */
#define SOC_OTG_DIEPTXF7_ADDR(base)                   ((base) + (0x011C))

/* �Ĵ���˵����Device IN�˵�8����FIFO���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPTXF8_UNION */
#define SOC_OTG_DIEPTXF8_ADDR(base)                   ((base) + (0x0120))

/* �Ĵ���˵����Device IN�˵�9����FIFO���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPTXF9_UNION */
#define SOC_OTG_DIEPTXF9_ADDR(base)                   ((base) + (0x0124))

/* �Ĵ���˵����Device IN�˵�10����FIFO���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPTXF10_UNION */
#define SOC_OTG_DIEPTXF10_ADDR(base)                  ((base) + (0x0128))

/* �Ĵ���˵����Device IN�˵�11����FIFO���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPTXF11_UNION */
#define SOC_OTG_DIEPTXF11_ADDR(base)                  ((base) + (0x012C))

/* �Ĵ���˵����Device IN�˵�12����FIFO���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPTXF12_UNION */
#define SOC_OTG_DIEPTXF12_ADDR(base)                  ((base) + (0x0130))

/* �Ĵ���˵����Device IN�˵�13����FIFO���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPTXF13_UNION */
#define SOC_OTG_DIEPTXF13_ADDR(base)                  ((base) + (0x0134))

/* �Ĵ���˵����Device IN�˵�14����FIFO���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPTXF14_UNION */
#define SOC_OTG_DIEPTXF14_ADDR(base)                  ((base) + (0x0138))

/* �Ĵ���˵����Device IN�˵�15����FIFO���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPTXF15_UNION */
#define SOC_OTG_DIEPTXF15_ADDR(base)                  ((base) + (0x013C))

/* �Ĵ���˵����Host���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_HCFG_UNION */
#define SOC_OTG_HCFG_ADDR(base)                       ((base) + (0x0400))

/* �Ĵ���˵����Host֡����Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_HFIR_UNION */
#define SOC_OTG_HFIR_ADDR(base)                       ((base) + (0x0404))

/* �Ĵ���˵����Host֡��żĴ�����
   λ����UNION�ṹ:  SOC_OTG_HFNUM_UNION */
#define SOC_OTG_HFNUM_ADDR(base)                      ((base) + (0x0408))

/* �Ĵ���˵����Host���ڷ���FIFO�Ͷ���״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_HPTXSTS_UNION */
#define SOC_OTG_HPTXSTS_ADDR(base)                    ((base) + (0x0410))

/* �Ĵ���˵����Host����ͨ���ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_HAINT_UNION */
#define SOC_OTG_HAINT_ADDR(base)                      ((base) + (0x0414))

/* �Ĵ���˵����Host����ͨ���ж����μĴ�����
   λ����UNION�ṹ:  SOC_OTG_HAINTMSK_UNION */
#define SOC_OTG_HAINTMSK_ADDR(base)                   ((base) + (0x0418))

/* �Ĵ���˵����֡�б����ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_HFLBAddr_UNION */
#define SOC_OTG_HFLBAddr_ADDR(base)                   ((base) + (0x041C))

/* �Ĵ���˵����Host�˿ڿ��ƺ�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_HPRT_UNION */
#define SOC_OTG_HPRT_ADDR(base)                       ((base) + (0x0440))

/* �Ĵ���˵����ͨ��p���ԼĴ�����
   λ����UNION�ṹ:  SOC_OTG_HCCHARp_UNION */
#define SOC_OTG_HCCHARp_ADDR(base, p)                 ((base) + (0x0500+0x20*(p)))

/* �Ĵ���˵����ͨ��p Split���ƼĴ�����
   λ����UNION�ṹ:  SOC_OTG_HCSPLTp_UNION */
#define SOC_OTG_HCSPLTp_ADDR(base, p)                 ((base) + (0x0504+(p)*0x20))

/* �Ĵ���˵����ͨ��p�ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_HCINTp_UNION */
#define SOC_OTG_HCINTp_ADDR(base, p)                  ((base) + (0x0508+(p)*0x20))

/* �Ĵ���˵����ͨ��p�ж����μĴ�����
   λ����UNION�ṹ:  SOC_OTG_HCINTMSKp_UNION */
#define SOC_OTG_HCINTMSKp_ADDR(base, p)               ((base) + (0x050C+(p)*0x20))

/* �Ĵ���˵����ͨ��p���䳤�ȼĴ�������scatter / gather DMAģʽ��
   λ����UNION�ṹ:  SOC_OTG_HCTSIZp_UNION */
#define SOC_OTG_HCTSIZp_ADDR(base, p)                 ((base) + (0x0510+(p)*0x20))

/* �Ĵ���˵����ͨ��p���䳤�ȼĴ���������scatter / gather DMAģʽ��
   λ����UNION�ṹ:  SOC_OTG_HCTSIZp_non_sg_UNION */
#define SOC_OTG_HCTSIZp_non_sg_ADDR(base, p)          ((base) + (0x0510+(p)*0x20))

/* �Ĵ���˵����ͨ��p DMA��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_HCDMAp_UNION */
#define SOC_OTG_HCDMAp_ADDR(base, p)                  ((base) + (0x0514+(p)*0x20))

/* �Ĵ���˵����ͨ��p DMA buffer��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_HCDMABp_UNION */
#define SOC_OTG_HCDMABp_ADDR(base, p)                 ((base) + (0x051C+(p)*0x20))

/* �Ĵ���˵����device���üĴ�����
   λ����UNION�ṹ:  SOC_OTG_DCFG_UNION */
#define SOC_OTG_DCFG_ADDR(base)                       ((base) + (0x0800))

/* �Ĵ���˵����device���ƼĴ�����
   λ����UNION�ṹ:  SOC_OTG_DCTL_UNION */
#define SOC_OTG_DCTL_ADDR(base)                       ((base) + (0x0804))

/* �Ĵ���˵����device״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_DSTS_UNION */
#define SOC_OTG_DSTS_ADDR(base)                       ((base) + (0x0808))

/* �Ĵ���˵����IN�˵���ͨ�ж����μĴ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPMSK_UNION */
#define SOC_OTG_DIEPMSK_ADDR(base)                    ((base) + (0x0810))

/* �Ĵ���˵����OUT�˵���ͨ�ж����μĴ�����
   λ����UNION�ṹ:  SOC_OTG_DOEPMSK_UNION */
#define SOC_OTG_DOEPMSK_ADDR(base)                    ((base) + (0x0814))

/* �Ĵ���˵�������ж˵��ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_DAINT_UNION */
#define SOC_OTG_DAINT_ADDR(base)                      ((base) + (0x0818))

/* �Ĵ���˵�������ж˵��ж����μĴ�����
   λ����UNION�ṹ:  SOC_OTG_DAINTMSK_UNION */
#define SOC_OTG_DAINTMSK_ADDR(base)                   ((base) + (0x081C))

/* �Ĵ���˵����Vbus�ŵ�ʱ�����üĴ�����
   λ����UNION�ṹ:  SOC_OTG_DVBUSDIS_UNION */
#define SOC_OTG_DVBUSDIS_ADDR(base)                   ((base) + (0x0828))

/* �Ĵ���˵����Vbus�������üĴ�����
   λ����UNION�ṹ:  SOC_OTG_DVBUSPULSE_UNION */
#define SOC_OTG_DVBUSPULSE_ADDR(base)                 ((base) + (0x082C))

/* �Ĵ���˵����deviceˮ�߿��ƼĴ�����
   λ����UNION�ṹ:  SOC_OTG_DTHRCTL_UNION */
#define SOC_OTG_DTHRCTL_ADDR(base)                    ((base) + (0x0830))

/* �Ĵ���˵����IN�˵�FIFO���ж����μĴ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPEMPMSK_UNION */
#define SOC_OTG_DIEPEMPMSK_ADDR(base)                 ((base) + (0x0834))

/* �Ĵ���˵����IN�˵�0���ƼĴ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPCTL0_UNION */
#define SOC_OTG_DIEPCTL0_ADDR(base)                   ((base) + (0x0900))

/* �Ĵ���˵����IN�˵�n���ƼĴ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPCTLn_UNION */
#define SOC_OTG_DIEPCTLn_ADDR(base, n)                ((base) + (0x0900+0x20*(n)))

/* �Ĵ���˵����IN�˵�m�ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPINTm_UNION */
#define SOC_OTG_DIEPINTm_ADDR(base, m)                ((base) + (0x0908+0x20*(m)))

/* �Ĵ���˵����IN�˵�0�����С�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPTSIZ0_UNION */
#define SOC_OTG_DIEPTSIZ0_ADDR(base)                  ((base) + (0x0910))

/* �Ĵ���˵����IN�˵�n�����С�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPTSIZn_UNION */
#define SOC_OTG_DIEPTSIZn_ADDR(base, n)               ((base) + (0x0910+0x20*(n)))

/* �Ĵ���˵����IN�˵�m DMA��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPDMAm_UNION */
#define SOC_OTG_DIEPDMAm_ADDR(base, m)                ((base) + (0x0914+0x20*(m)))

/* �Ĵ���˵����IN�˵�m����FIFO״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_DTXFSTSm_UNION */
#define SOC_OTG_DTXFSTSm_ADDR(base)                   ((base) + (0x0918))

/* �Ĵ���˵����IN�˵�m DMA buffer��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_DIEPDMABn_UNION */
#define SOC_OTG_DIEPDMABn_ADDR(base, m)               ((base) + (0x091C+0x20*(m)))

/* �Ĵ���˵����OUT�˵�0���ƼĴ�����
   λ����UNION�ṹ:  SOC_OTG_DOEPCTL0_UNION */
#define SOC_OTG_DOEPCTL0_ADDR(base)                   ((base) + (0x0B00))

/* �Ĵ���˵����OUT�˵�n���ƼĴ�����
   λ����UNION�ṹ:  SOC_OTG_DOEPCTLn_UNION */
#define SOC_OTG_DOEPCTLn_ADDR(base, n)                ((base) + (0x0B00+0x20*(n)))

/* �Ĵ���˵����OUT�˵�m�ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_DOEPINTm_UNION */
#define SOC_OTG_DOEPINTm_ADDR(base, m)                ((base) + (0x0B08+0x20*(m)))

/* �Ĵ���˵����OUT�˵�0�����С�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_DOEPTSIZ0_UNION */
#define SOC_OTG_DOEPTSIZ0_ADDR(base)                  ((base) + (0x0B10))

/* �Ĵ���˵����OUT�˵�n�����С�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_DOEPTSIZn_UNION */
#define SOC_OTG_DOEPTSIZn_ADDR(base, n)               ((base) + (0x0B10+0x20*(n)))

/* �Ĵ���˵����OUT�˵�m DMA��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_DOEPDMAm_UNION */
#define SOC_OTG_DOEPDMAm_ADDR(base, m)                ((base) + (0x0B14+0x20*(m)))

/* �Ĵ���˵����OUT�˵�m DMA buffer��ַ�Ĵ�����
   λ����UNION�ṹ:  SOC_OTG_DOEPDMABm_UNION */
#define SOC_OTG_DOEPDMABm_ADDR(base, m)               ((base) + (0x0B1C+0x20*(m)))

/* �Ĵ���˵�������ĺ�ʱ���ſؿ��ƼĴ�����
   λ����UNION�ṹ:  SOC_OTG_PCGCCTL_UNION */
#define SOC_OTG_PCGCCTL_ADDR(base)                    ((base) + (0x0E00))





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
                     (1/1) OTG
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_OTG_GOTGCTL_UNION
 �ṹ˵��  : GOTGCTL �Ĵ����ṹ���塣��ַƫ����:0x0000����ֵ:0x00010000�����:32
 �Ĵ���˵��: ȫ�ֿ��ƺ�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SesReqScs       : 1;  /* bit[0]    : �Ự�����Ƿ�ɹ���
                                                           0��ʧ�ܣ�
                                                           1���ɹ��� */
        unsigned int  SesReq          : 1;  /* bit[1]    : �Ự����
                                                           0���޻Ự����
                                                           1���Ự���� */
        unsigned int  VbvalidOvEn     : 1;  /* bit[2]    : ����PHY������vbusvalid�ź�ʹ�ܡ�
                                                           0����ʹ�ܣ�
                                                           1��ʹ�ܡ� */
        unsigned int  VbvalidOvVal    : 1;  /* bit[3]    : ��VbvalidOvEn��1ʱ����bit��������vbusvalidֵ������PHY������vbusvalid�źš�
                                                           0��vbusvalid��Ч��
                                                           1��vbusvalid��Ч�� */
        unsigned int  AvalidOvEn      : 1;  /* bit[4]    : ����PHY������avalid�ź�ʹ�ܡ�
                                                           0����ʹ�ܣ�
                                                           1��ʹ�ܡ� */
        unsigned int  AvalidOvVal     : 1;  /* bit[5]    : ��AvalidOvEn��1ʱ����bit��������avalidֵ������PHY������avalid�źš�
                                                           0��avalid��Ч��
                                                           1��avalid��Ч�� */
        unsigned int  BvalidOvEn      : 1;  /* bit[6]    : ����PHY������bvalid�ź�ʹ�ܡ�
                                                           0����ʹ�ܣ�
                                                           1��ʹ�ܡ� */
        unsigned int  BvalidOvVal     : 1;  /* bit[7]    : ��BvalidOvEn��1ʱ����bit��������bvalidֵ������PHY������bvalid�źš�
                                                           0��bvalid��Ч��
                                                           1��bvalid��Ч�� */
        unsigned int  HstNegScs       : 1;  /* bit[8]    : ����Э�̳ɹ�����deviceģʽ��Ч��
                                                           0��ʧ�ܣ�
                                                           1���ɹ��� */
        unsigned int  HNPReq          : 1;  /* bit[9]    : HNP���󣬶�deviceģʽ��Ч��������ø�bit����host����HNP�������ڽ��յ�GOTGINT.HstNegSucStsChng�ж�֮����������bit��
                                                           0��������
                                                           1�������� */
        unsigned int  HstSetHNPEn     : 1;  /* bit[10]   : HOST HNPʹ�ܣ���Hostģʽ��Ч��Host�ڷ���SetFeature.SetHNPEnabled����֮��������ø�bitΪ1��
                                                           0����ʹ�ܣ�
                                                           1��ʹ�ܡ� */
        unsigned int  DevHNPEn        : 1;  /* bit[11]   : device HNPʹ�ܣ���deviceģʽ��Ч�����յ�SetFeature.SetHNPEnabled����֮��������ø�bitΪ1��
                                                           0����ʹ�ܣ�
                                                           1��ʹ�ܡ� */
        unsigned int  EHEn            : 1;  /* bit[12]   : Embedded Host enable
                                                           1��ѡ��embedded host state machine
                                                           0��ѡ��OTG A device state machine */
        unsigned int  reserved_0      : 2;  /* bit[13-14]: ������ */
        unsigned int  DbnceFltrBypass : 1;  /* bit[15]   : Debounce Filter Bypass
                                                           0����ʹ�ܣ�
                                                           1��ʹ�ܡ� */
        unsigned int  conidsts        : 1;  /* bit[16]   : ����ID״̬��
                                                           0��A�豸ģʽ��
                                                           1��B�豸ģʽ�� */
        unsigned int  dbnc_time       : 1;  /* bit[17]   : debounceʱ��ѡ��Debounceʱ��ָЭ���Ϲ涨�ļ�⵽device����״̬֮�󵽷��͸�λ�ź�֮����ӳ١�
                                                           0��100ms+2.5us�������������ӣ�
                                                           1��2.5us�����������ӡ� */
        unsigned int  asessvld        : 1;  /* bit[18]   : Hostģʽ�շ���״̬��
                                                           0��a_session��Ч��
                                                           1��a_session��Ч�� */
        unsigned int  bsesvld         : 1;  /* bit[19]   : �豸����״ָ̬ʾ��
                                                           0��δ���ӣ�
                                                           1�����ӡ� */
        unsigned int  otg_version     : 1;  /* bit[20]   : OTGЭ��汾��
                                                           0��1.3��֧�������ߺ�VBUS����ʵ��SRPЭ�飻
                                                           1��2.0��ֻ֧������������ʵ��SRPЭ�顣 */
        unsigned int  reserved_1      : 1;  /* bit[21]   : ������ */
        unsigned int  multvaldidbc    : 5;  /* bit[22-26]: ACA ID�ܽ�״̬��
                                                           00001��rid_c��
                                                           00010��rid_b��
                                                           00100��rid_a��
                                                           01000��rid_gnd��
                                                           10000��rid_float��
                                                           others��reserved�� */
        unsigned int  chirpen         : 1;  /* bit[27]   : chirponʹ�ܡ�
                                                           ��bit����Ϊ1���������ڷ���chirp K֮ǰ��chirp_on�ź�Ϊ�ߵ�ƽ��
                                                           0����ʹ�ܣ�
                                                           1��ʹ�ܡ� */
        unsigned int  reserved_2      : 4;  /* bit[28-31]: ������ */
    } reg;
} SOC_OTG_GOTGCTL_UNION;
#endif
#define SOC_OTG_GOTGCTL_SesReqScs_START        (0)
#define SOC_OTG_GOTGCTL_SesReqScs_END          (0)
#define SOC_OTG_GOTGCTL_SesReq_START           (1)
#define SOC_OTG_GOTGCTL_SesReq_END             (1)
#define SOC_OTG_GOTGCTL_VbvalidOvEn_START      (2)
#define SOC_OTG_GOTGCTL_VbvalidOvEn_END        (2)
#define SOC_OTG_GOTGCTL_VbvalidOvVal_START     (3)
#define SOC_OTG_GOTGCTL_VbvalidOvVal_END       (3)
#define SOC_OTG_GOTGCTL_AvalidOvEn_START       (4)
#define SOC_OTG_GOTGCTL_AvalidOvEn_END         (4)
#define SOC_OTG_GOTGCTL_AvalidOvVal_START      (5)
#define SOC_OTG_GOTGCTL_AvalidOvVal_END        (5)
#define SOC_OTG_GOTGCTL_BvalidOvEn_START       (6)
#define SOC_OTG_GOTGCTL_BvalidOvEn_END         (6)
#define SOC_OTG_GOTGCTL_BvalidOvVal_START      (7)
#define SOC_OTG_GOTGCTL_BvalidOvVal_END        (7)
#define SOC_OTG_GOTGCTL_HstNegScs_START        (8)
#define SOC_OTG_GOTGCTL_HstNegScs_END          (8)
#define SOC_OTG_GOTGCTL_HNPReq_START           (9)
#define SOC_OTG_GOTGCTL_HNPReq_END             (9)
#define SOC_OTG_GOTGCTL_HstSetHNPEn_START      (10)
#define SOC_OTG_GOTGCTL_HstSetHNPEn_END        (10)
#define SOC_OTG_GOTGCTL_DevHNPEn_START         (11)
#define SOC_OTG_GOTGCTL_DevHNPEn_END           (11)
#define SOC_OTG_GOTGCTL_EHEn_START             (12)
#define SOC_OTG_GOTGCTL_EHEn_END               (12)
#define SOC_OTG_GOTGCTL_DbnceFltrBypass_START  (15)
#define SOC_OTG_GOTGCTL_DbnceFltrBypass_END    (15)
#define SOC_OTG_GOTGCTL_conidsts_START         (16)
#define SOC_OTG_GOTGCTL_conidsts_END           (16)
#define SOC_OTG_GOTGCTL_dbnc_time_START        (17)
#define SOC_OTG_GOTGCTL_dbnc_time_END          (17)
#define SOC_OTG_GOTGCTL_asessvld_START         (18)
#define SOC_OTG_GOTGCTL_asessvld_END           (18)
#define SOC_OTG_GOTGCTL_bsesvld_START          (19)
#define SOC_OTG_GOTGCTL_bsesvld_END            (19)
#define SOC_OTG_GOTGCTL_otg_version_START      (20)
#define SOC_OTG_GOTGCTL_otg_version_END        (20)
#define SOC_OTG_GOTGCTL_multvaldidbc_START     (22)
#define SOC_OTG_GOTGCTL_multvaldidbc_END       (26)
#define SOC_OTG_GOTGCTL_chirpen_START          (27)
#define SOC_OTG_GOTGCTL_chirpen_END            (27)


/*****************************************************************************
 �ṹ��    : SOC_OTG_GOTGINT_UNION
 �ṹ˵��  : GOTGINT �Ĵ����ṹ���塣��ַƫ����:0x0004����ֵ:0x00000000�����:32
 �Ĵ���˵��: ȫ��OTG�ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0       : 2;  /* bit[0-1]  : ������ */
        unsigned int  SesEndDet        : 1;  /* bit[2]    : ��⵽�Ự�����������ָʾutmisrp_bvalid�źű�Ϊ�͵�ƽ��
                                                            0�����жϣ�
                                                            1�����жϡ� */
        unsigned int  reserved_1       : 5;  /* bit[3-7]  : ������ */
        unsigned int  SesReqSucStsChng : 1;  /* bit[8]    : �Ự����״̬�仯�����Ự����ɹ�����ʧ��ʱ����bit��1���������ͨ����ѯ�Ĵ���GPTGCTL[SesReqScs]��ȷ���Ự�����ǳɹ�����ʧ�ܡ�
                                                            0�����жϣ�
                                                            1�����жϡ� */
        unsigned int  HstNegSucStsChng : 1;  /* bit[9]    : ����Э�̳ɹ�״̬�仯��
                                                            0�����жϣ�
                                                            1�����жϡ� */
        unsigned int  reserved_2       : 7;  /* bit[10-16]: ������ */
        unsigned int  HstNegDet        : 1;  /* bit[17]   : ��⵽����Э������
                                                            0�����жϣ�
                                                            1�����жϡ� */
        unsigned int  ADevTOUTChg      : 1;  /* bit[18]   : A�豸�ȴ�B�豸���ӳ�ʱ��
                                                            0�����жϣ�
                                                            1�����жϡ� */
        unsigned int  DbnceDone        : 1;  /* bit[19]   : debounce��ɣ���hostģʽ��Ч����⵽device����֮���ӳ�debounceʱ�䣬�������ø�bit��Ч������յ����ж�֮�󣬿������÷�����λ��������bit����GUSBCFG[HNPCap]����GUSBCFG[SRPCap]����֮����Ч��
                                                            0�����жϣ�
                                                            1�����жϡ� */
        unsigned int  MultValIDChng    : 1;  /* bit[20]   : ����һ��ACA�ܽ�״̬�����仯��
                                                            0�����жϣ�
                                                            1�����жϡ� */
        unsigned int  reserved_3       : 11; /* bit[21-31]: ���� */
    } reg;
} SOC_OTG_GOTGINT_UNION;
#endif
#define SOC_OTG_GOTGINT_SesEndDet_START         (2)
#define SOC_OTG_GOTGINT_SesEndDet_END           (2)
#define SOC_OTG_GOTGINT_SesReqSucStsChng_START  (8)
#define SOC_OTG_GOTGINT_SesReqSucStsChng_END    (8)
#define SOC_OTG_GOTGINT_HstNegSucStsChng_START  (9)
#define SOC_OTG_GOTGINT_HstNegSucStsChng_END    (9)
#define SOC_OTG_GOTGINT_HstNegDet_START         (17)
#define SOC_OTG_GOTGINT_HstNegDet_END           (17)
#define SOC_OTG_GOTGINT_ADevTOUTChg_START       (18)
#define SOC_OTG_GOTGINT_ADevTOUTChg_END         (18)
#define SOC_OTG_GOTGINT_DbnceDone_START         (19)
#define SOC_OTG_GOTGINT_DbnceDone_END           (19)
#define SOC_OTG_GOTGINT_MultValIDChng_START     (20)
#define SOC_OTG_GOTGINT_MultValIDChng_END       (20)


/*****************************************************************************
 �ṹ��    : SOC_OTG_GAHBCFG_UNION
 �ṹ˵��  : GAHBCFG �Ĵ����ṹ���塣��ַƫ����:0x0008����ֵ:0x00000000�����:32
 �Ĵ���˵��: ȫ��AHB���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  GlblIntrMsk       : 1;  /* bit[0]    : ȫ���ж�����λ���������������жϵ��ϱ���
                                                             0�����Σ�
                                                             1�������Ρ� */
        unsigned int  HBstLen           : 4;  /* bit[1-4]  : burst���Ϳ��ƣ�����DMA AHB���ߴ���burst���͡�
                                                             0000��single��
                                                             0001��incr��
                                                             0011��incr4��
                                                             0101��incr8��
                                                             0111��incr16��
                                                             others��reserved�� */
        unsigned int  DMAEn             : 1;  /* bit[5]    : DMAʹ�ܡ�
                                                             0����ʹ�ܣ�
                                                             1��ʹ�ܡ� */
        unsigned int  reserved_0        : 1;  /* bit[6]    : ������ */
        unsigned int  NPTxFEmpLvl       : 1;  /* bit[7]    : ����FIFO��ˮ�꣬���÷���FIFO���ж�GINTSTS[NPTxFEmp]�Ĵ���������
                                                             0������FIFO��գ�
                                                             1������FIFOȫ�ա�
                                                             Dedicated FIFO in device mode
                                                             0��IN Endpoint TxFIFO���
                                                             1��IN Endpoint TxFIFOȫ�� */
        unsigned int  reserved_1        : 13; /* bit[8-20] : ������ */
        unsigned int  RemMemSupp        : 1;  /* bit[21]   : host��device��ȥmemory֧�� */
        unsigned int  NotiAllDmaWrit    : 1;  /* bit[22]   : host��device֪ͨ���е�DMAд����
                                                             1��֪ͨ���е�DMAд����
                                                             0��������Ӧ��ͨ����˵�֪ͨ���һ��DMAд���� */
        unsigned int  AHBsingle         : 1;  /* bit[23]   : AHB Master�ӿ�single�������á�
                                                             0������INCR burst��ʽ��
                                                             1������SINGLE burst��ʽ�� */
        unsigned int  InvDescEndianness : 1;  /* bit[24]   : Host and Device Inverse descriptor Endiannness
                                                             0��descriptor EndiannnessͬAHB Master��Endiannnessһ��
                                                             1����AHB Master��Endiannness�Ǵ�ˣ�descriptor EndiannnessΪС��
                                                             0����AHB Master��Endiannness��С�ˣ�descriptor EndiannnessΪ��� */
        unsigned int  reserved_2        : 7;  /* bit[25-31]:  */
    } reg;
} SOC_OTG_GAHBCFG_UNION;
#endif
#define SOC_OTG_GAHBCFG_GlblIntrMsk_START        (0)
#define SOC_OTG_GAHBCFG_GlblIntrMsk_END          (0)
#define SOC_OTG_GAHBCFG_HBstLen_START            (1)
#define SOC_OTG_GAHBCFG_HBstLen_END              (4)
#define SOC_OTG_GAHBCFG_DMAEn_START              (5)
#define SOC_OTG_GAHBCFG_DMAEn_END                (5)
#define SOC_OTG_GAHBCFG_NPTxFEmpLvl_START        (7)
#define SOC_OTG_GAHBCFG_NPTxFEmpLvl_END          (7)
#define SOC_OTG_GAHBCFG_RemMemSupp_START         (21)
#define SOC_OTG_GAHBCFG_RemMemSupp_END           (21)
#define SOC_OTG_GAHBCFG_NotiAllDmaWrit_START     (22)
#define SOC_OTG_GAHBCFG_NotiAllDmaWrit_END       (22)
#define SOC_OTG_GAHBCFG_AHBsingle_START          (23)
#define SOC_OTG_GAHBCFG_AHBsingle_END            (23)
#define SOC_OTG_GAHBCFG_InvDescEndianness_START  (24)
#define SOC_OTG_GAHBCFG_InvDescEndianness_END    (24)


/*****************************************************************************
 �ṹ��    : SOC_OTG_GUSBCFG_UNION
 �ṹ˵��  : GUSBCFG �Ĵ����ṹ���塣��ַƫ����:0x000C����ֵ:0x00001400�����:32
 �Ĵ���˵��: ȫ��USB���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  TOutCal              : 3;  /* bit[0-2]  : ���ٺ�ȫ�ٳ�ʱʱ���������λΪPHYʱ�����ڣ����ڵ�����׼��ʱʱ�䡣 */
        unsigned int  PHYIf                : 1;  /* bit[3]    : PHY����λ��ѡ��
                                                                0��8bit��
                                                                1��16bit�� */
        unsigned int  ULPI_UTMI_Sel        : 1;  /* bit[4]    : ULPI ��UTMI+ѡ��
                                                                0��ѡ��UTMI+�ӿ�
                                                                1��ѡ��ULPI�ӿ� */
        unsigned int  FSIntf               : 1;  /* bit[5]    : ȫ������ѡ��
                                                                0��6-pin�޷���FS���߽ӿ�
                                                                1��3-pin�з���FS���߽ӿ� */
        unsigned int  PHYSel               : 1;  /* bit[6]    : PHY ѡ��
                                                                0��ѡUSB2.0����UTMI+��ULPI PHY
                                                                1��ѡusb1.1ȫ���շ��� */
        unsigned int  DDRSel               : 1;  /* bit[7]    : ULPI DDRѡ��
                                                                0������Data Rate ULPI�ӿڣ�8λ��
                                                                1���ɶ�Data Rate ULPI�ӿڣ�4λ�� */
        unsigned int  SRPCap               : 1;  /* bit[8]    : SRP����ʹ�ܡ�
                                                                0����ʹ�ܣ�
                                                                1��ʹ�ܡ� */
        unsigned int  HNPCap               : 1;  /* bit[9]    : HNP����ʹ�ܡ�
                                                                0����ʹ�ܣ�
                                                                1��ʹ�ܡ� */
        unsigned int  USBTrdTim            : 4;  /* bit[10-13]: USB��תʱ�䡣ָʾ��MAC�������󵽴�FIFO��ȡ�����ݵ�ʱ�䣬��λΪPHYʱ�����ڡ�
                                                                �������ó�����ֵ��
                                                                0101��PHY����λ����16bit��
                                                                1001��PHY����λ����8bit�� */
        unsigned int  reserved             : 1;  /* bit[14]   : ������ */
        unsigned int  PhyPwrClkSel         : 1;  /* bit[15]   : PHY�͹���ģʽʱ��ѡ��
                                                                0��480MHz�ڲ�ʱ�ӣ�
                                                                1��48MHz�ⲿʱ�ӡ� */
        unsigned int  Otgl2CSel            : 1;  /* bit[16]   : ѡ��UTMIFS��I2C�ӿ�
                                                                0��OTG�ź�ʹ��UTMI USB1.1ȫ�ٽӿ�
                                                                1��OTG�ź�ʹ��I2C�ӿ� */
        unsigned int  ULPIFsLs             : 1;  /* bit[17]   : ULPI FS/LSѡ��
                                                                0: ULPI interface 
                                                                1: ULPI FS/LS serial interface */
        unsigned int  ULPIAutoRes          : 1;  /* bit[18]   : ULPI�Զ�����
                                                                0��PHY��ʹ��AutoResume����
                                                                1��PHYʹ��AutoResume���� */
        unsigned int  ULPIClkSusM          : 1;  /* bit[19]   : ULPIʱ�ӹ���
                                                                0��suspendʱ��PHY���ڲ�ʱ���µ�
                                                                1��PHY�����ڲ�ʱ���µ� */
        unsigned int  ULPIExVbusDrv        : 1;  /* bit[20]   : HOSTģʽ��ULPI�ⲿVBUS����
                                                                0��PHYʹ���ڲ�charge pump����VBUS
                                                                1��PHYʹ���ⲿ��Դ����VBUS */
        unsigned int  ULPIExtVbusIndicator : 1;  /* bit[21]   : HOSTģʽ��ULPI�ⲿVBUS�Ƚ�
                                                                0��PHYʹ���ڲ�VBUS�Ƚ�
                                                                1��PHYʹ���ⲿVBUS�Ƚ� */
        unsigned int  TermSelDLPulse       : 1;  /* bit[22]   : deviceģʽ��TermSel������ѡ��
                                                                0��ʹ��utmi_txvalid����Data line pulsing
                                                                1��ʹ��utmi_termsel����Data line pulsing */
        unsigned int  Complement           : 1;  /* bit[23]   : HOSTģʽ��Indicator Complement 
                                                                0��PHY����תExternalVbusIndicator�ź�
                                                                1��PHY��תExternalVbusIndicator�ź� */
        unsigned int  Indicator            : 1;  /* bit[24]   : HOSTģʽ��Indicator Pass Through
                                                                0��Complement Output�źŷ����ڲ�VbusValid comparator
                                                                1��Complement Output�źŲ������ڲ�VbusValid comparator */
        unsigned int  ULPI                 : 1;  /* bit[25]   : HOSTģʽ��ULPI�ӿڱ�����·ʹ��
                                                                0���ӿڱ�����·ʹ��
                                                                1���ӿڱ�����·��ʹ�� */
        unsigned int  IC_USBCap            : 1;  /* bit[26]   : IC_USB-Capable 
                                                                0����ѡ��IC_USB PHY Interface
                                                                1��ѡ��IC_USB PHY Interface */
        unsigned int  IC_USBTrafCtl        : 1;  /* bit[27]   : deviceģʽ��IC_USB TrafficPullRemove Control  */
        unsigned int  TxEndDelay           : 1;  /* bit[28]   : ���ͽ����ӳ١����ø�bit������UTMI 1.05�汾ʹ�ܷ��ͽ���timer��
                                                                0����ʹ�ܣ�
                                                                1��ʹ�ܡ� */
        unsigned int  ForceHstMode         : 1;  /* bit[29]   : ǿ��ΪHostģʽ��
                                                                0������ģʽ��
                                                                1��hostģʽ�� */
        unsigned int  ForceDevMode         : 1;  /* bit[30]   : ǿ��Ϊdeviceģʽ��
                                                                0������ģʽ��
                                                                1��deviceģʽ�� */
        unsigned int  CtptTxPkt            : 1;  /* bit[31]   : �ƻ������ͣ�����debug������ʹ��ʱ�������ø�bitΪ1��
                                                                0���������ƻ�����
                                                                1�������ƻ����� */
    } reg;
} SOC_OTG_GUSBCFG_UNION;
#endif
#define SOC_OTG_GUSBCFG_TOutCal_START               (0)
#define SOC_OTG_GUSBCFG_TOutCal_END                 (2)
#define SOC_OTG_GUSBCFG_PHYIf_START                 (3)
#define SOC_OTG_GUSBCFG_PHYIf_END                   (3)
#define SOC_OTG_GUSBCFG_ULPI_UTMI_Sel_START         (4)
#define SOC_OTG_GUSBCFG_ULPI_UTMI_Sel_END           (4)
#define SOC_OTG_GUSBCFG_FSIntf_START                (5)
#define SOC_OTG_GUSBCFG_FSIntf_END                  (5)
#define SOC_OTG_GUSBCFG_PHYSel_START                (6)
#define SOC_OTG_GUSBCFG_PHYSel_END                  (6)
#define SOC_OTG_GUSBCFG_DDRSel_START                (7)
#define SOC_OTG_GUSBCFG_DDRSel_END                  (7)
#define SOC_OTG_GUSBCFG_SRPCap_START                (8)
#define SOC_OTG_GUSBCFG_SRPCap_END                  (8)
#define SOC_OTG_GUSBCFG_HNPCap_START                (9)
#define SOC_OTG_GUSBCFG_HNPCap_END                  (9)
#define SOC_OTG_GUSBCFG_USBTrdTim_START             (10)
#define SOC_OTG_GUSBCFG_USBTrdTim_END               (13)
#define SOC_OTG_GUSBCFG_PhyPwrClkSel_START          (15)
#define SOC_OTG_GUSBCFG_PhyPwrClkSel_END            (15)
#define SOC_OTG_GUSBCFG_Otgl2CSel_START             (16)
#define SOC_OTG_GUSBCFG_Otgl2CSel_END               (16)
#define SOC_OTG_GUSBCFG_ULPIFsLs_START              (17)
#define SOC_OTG_GUSBCFG_ULPIFsLs_END                (17)
#define SOC_OTG_GUSBCFG_ULPIAutoRes_START           (18)
#define SOC_OTG_GUSBCFG_ULPIAutoRes_END             (18)
#define SOC_OTG_GUSBCFG_ULPIClkSusM_START           (19)
#define SOC_OTG_GUSBCFG_ULPIClkSusM_END             (19)
#define SOC_OTG_GUSBCFG_ULPIExVbusDrv_START         (20)
#define SOC_OTG_GUSBCFG_ULPIExVbusDrv_END           (20)
#define SOC_OTG_GUSBCFG_ULPIExtVbusIndicator_START  (21)
#define SOC_OTG_GUSBCFG_ULPIExtVbusIndicator_END    (21)
#define SOC_OTG_GUSBCFG_TermSelDLPulse_START        (22)
#define SOC_OTG_GUSBCFG_TermSelDLPulse_END          (22)
#define SOC_OTG_GUSBCFG_Complement_START            (23)
#define SOC_OTG_GUSBCFG_Complement_END              (23)
#define SOC_OTG_GUSBCFG_Indicator_START             (24)
#define SOC_OTG_GUSBCFG_Indicator_END               (24)
#define SOC_OTG_GUSBCFG_ULPI_START                  (25)
#define SOC_OTG_GUSBCFG_ULPI_END                    (25)
#define SOC_OTG_GUSBCFG_IC_USBCap_START             (26)
#define SOC_OTG_GUSBCFG_IC_USBCap_END               (26)
#define SOC_OTG_GUSBCFG_IC_USBTrafCtl_START         (27)
#define SOC_OTG_GUSBCFG_IC_USBTrafCtl_END           (27)
#define SOC_OTG_GUSBCFG_TxEndDelay_START            (28)
#define SOC_OTG_GUSBCFG_TxEndDelay_END              (28)
#define SOC_OTG_GUSBCFG_ForceHstMode_START          (29)
#define SOC_OTG_GUSBCFG_ForceHstMode_END            (29)
#define SOC_OTG_GUSBCFG_ForceDevMode_START          (30)
#define SOC_OTG_GUSBCFG_ForceDevMode_END            (30)
#define SOC_OTG_GUSBCFG_CtptTxPkt_START             (31)
#define SOC_OTG_GUSBCFG_CtptTxPkt_END               (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_GRSTCTL_UNION
 �ṹ˵��  : GRSTCTL �Ĵ����ṹ���塣��ַƫ����:0x0010����ֵ:0x80000000�����:32
 �Ĵ���˵��: ȫ�ָ�λ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CSftRst    : 1;  /* bit[0]    : ��λ���󡣸�λ����ʱ�����phyʱ���򡣲�����ɸ�bit�Զ����㡣
                                                      0����λ��ɣ�
                                                      1��������λ�� */
        unsigned int  reserved_0 : 1;  /* bit[1]    : ������ */
        unsigned int  FrmCntrRst : 1;  /* bit[2]    : ΢֡�ż�����λ��������ɸ�bit�Զ����㡣
                                                      0������λ��
                                                      1����λ�� */
        unsigned int  reserved_1 : 1;  /* bit[3]    : ������ */
        unsigned int  RxFFlsh    : 1;  /* bit[4]    : ��ս���FIFO��������ɣ���bit�Զ����㡣���ø�bit֮ǰ�����뱣֤�Խ���FIFOû�ж�д������
                                                      0����ս���FIFO��ɣ�
                                                      1����ս���FIFO�� */
        unsigned int  TxFFlsh    : 1;  /* bit[5]    : ��շ���FIFO���������TxFNumָ���ķ���FIFO����շ���FIFO��ɣ���bit�Զ����㡣
                                                      0����շ���FIFO��ɣ�
                                                      1����շ���FIFO��
                                                      �����ø�λ֮ǰ�����뱣֤��TxFIFOû�ж�д�������ڽ��С�����ͨ�����¼Ĵ���״̬ȷ�ϣ�
                                                      DIEPINTn[INEPNakEff]�ж�Ϊ1��֤������û�ж�����FIFO��
                                                      GRST[AHBIdle]Ϊ1��֤������û��д����FIFO��
                                                      ������FIFO�������û��߶˵㲻ʹ��ʱ��շ���FIFO�� */
        unsigned int  TxFNum     : 5;  /* bit[6-10] : ��շ���FIFO��š�ָʾ��TxFFlsh��������ķ���FIFO����TxFFlshλ����֮ǰ���ܸı�TxFNumֵ��
                                                      0��Hostģʽ����շ����ڷ���FIFO��Deviceģʽ����շ���FIFO 0��
                                                      1��Hostģʽ��������ڷ���FIFO��Deviceģʽ����շ���FIFO 1��
                                                      2��Deviceģʽ�£���շ���FIFO 2��
                                                      ����
                                                      F��Deviceģʽ�£���շ���FIFO 15��
                                                      10��������з���FIFO��
                                                      others��reserved�� */
        unsigned int  reserved_2 : 19; /* bit[11-29]: ������ */
        unsigned int  DMAReq     : 1;  /* bit[30]   : DMA����״̬��ָʾ�Ƿ����ڴ���DMA��������debug��
                                                      0����DMA����
                                                      1��DMA�������ڴ��� */
        unsigned int  AHBIdle    : 1;  /* bit[31]   : AHB����״̬��ָʾAHB master״̬�����ڿ���״̬��
                                                      0�������ڿ���״̬��
                                                      1�����ڿ���״̬�� */
    } reg;
} SOC_OTG_GRSTCTL_UNION;
#endif
#define SOC_OTG_GRSTCTL_CSftRst_START     (0)
#define SOC_OTG_GRSTCTL_CSftRst_END       (0)
#define SOC_OTG_GRSTCTL_FrmCntrRst_START  (2)
#define SOC_OTG_GRSTCTL_FrmCntrRst_END    (2)
#define SOC_OTG_GRSTCTL_RxFFlsh_START     (4)
#define SOC_OTG_GRSTCTL_RxFFlsh_END       (4)
#define SOC_OTG_GRSTCTL_TxFFlsh_START     (5)
#define SOC_OTG_GRSTCTL_TxFFlsh_END       (5)
#define SOC_OTG_GRSTCTL_TxFNum_START      (6)
#define SOC_OTG_GRSTCTL_TxFNum_END        (10)
#define SOC_OTG_GRSTCTL_DMAReq_START      (30)
#define SOC_OTG_GRSTCTL_DMAReq_END        (30)
#define SOC_OTG_GRSTCTL_AHBIdle_START     (31)
#define SOC_OTG_GRSTCTL_AHBIdle_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_GINTSTS_UNION
 �ṹ˵��  : GINTSTS �Ĵ����ṹ���塣��ַƫ����:0x0014����ֵ:0x14000020�����:32
 �Ĵ���˵��: ȫ���ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  CurMode      : 1;  /* bit[0] : ��ǰģʽ��
                                                     0��deviceģʽ��
                                                     1��hostģʽ�� */
        unsigned int  ModeMis      : 1;  /* bit[1] : ģʽ��ƥ���жϡ������ǰΪhostģʽ�������дdevice�Ĵ����������ǰΪdeviceģʽ�������дhost�Ĵ����ᴥ�����жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  OTGInt       : 1;  /* bit[2] : OTG�жϡ������Ҫ��ѯ�Ĵ���GOTGINTȷ���ж����͡�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  Sof          : 1;  /* bit[3] : SOF(Start Of microFrame)�жϡ�ָʾ���յ�SOF���ư���
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  RxFLvl       : 1;  /* bit[4] : ����FIFO�ǿ��жϡ�ָʾ����FIFO������1���������ݡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  NPTxFEmp     : 1;  /* bit[5] : �����ڷ���FIFO���жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  GINNakEff    : 1;  /* bit[6] : ������IN�˵�NAK��Ч�жϡ�ָʾ�Ĵ���DCTL[SGNPInNak]������Ч�������е�IN������ӦNAK����bit����ͨ��дDCTL[CGNPInNak]�������
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  GOUTNakEff   : 1;  /* bit[7] : OUT�˵�NAK��Ч�жϡ�ָʾ�Ĵ���DCTL[SGOUTNak]������Ч�������е�OUT���ư���ӦNAK����bit����ͨ��д�Ĵ���DCTL[CGOUTNak]�������
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  ULPICKINT    : 1;  /* bit[8] : ULPI Carkit�ж�
                                                     ���յ� ULPI Carkit�жϺ���Ч */
        unsigned int  I2CINT       : 1;  /* bit[9] : I2C�ӿ�
                                                     I2C������ɺ���Ч */
        unsigned int  ErlySusp     : 1;  /* bit[10]: Early suspend�жϡ�����⵽USB����IDLE״̬����3ms�ᴥ�����жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  USBSusp      : 1;  /* bit[11]: suspend�жϡ�ָʾ����suspend״̬��
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  USBRst       : 1;  /* bit[12]: USB��λ�жϡ�ָʾ��⵽USB��λ������
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  EnumDone     : 1;  /* bit[13]: ö������жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  ISOOutDrop   : 1;  /* bit[14]: Isochronous OUT�������жϡ����յ�Isochronous OUT�����������ڽ���FIFO�ռ䲻����USB�ᶪ���յ��İ�������λ���жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  EOPF         : 1;  /* bit[15]: EOPF��End of Period Frame���жϣ�ָʾ�ڵ�ǰ֡���ڴ��������
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  RstrDoneInt  : 1;  /* bit[16]: �Ĵ����ָ��жϡ�ָʾ�˳�����ģʽ�󣬼Ĵ����ָ�������ɡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  reserved     : 1;  /* bit[17]: ������ */
        unsigned int  IEPInt       : 1;  /* bit[18]: IN�˵��жϡ�ָʾIN�˵����жϲ����������Ҫ��ѯ�Ĵ���DAINTȷ���˵�ţ�Ȼ���ѯ��Ӧ�˵���ж�״̬�Ĵ���ȷ���ж����͡�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  OEPInt       : 1;  /* bit[19]: OUT�˵��жϡ�ָʾOUT�˵����жϲ����������Ҫ��ѯ�Ĵ���DAINTȷ���˵�ţ�Ȼ���ѯ��Ӧ�˵���ж�״̬�Ĵ���ȷ���ж����͡�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  incompISOIN  : 1;  /* bit[20]: Isochronous IN����δ����жϡ�ָʾ������1��IN�˵��Isochronous�����ڵ�ǰ��΢֡δ��ɡ����ж���EOPF�ж�ͬʱ������
                                                     0�����ж�
                                                     1�����ж� */
        unsigned int  incompISOOUT : 1;  /* bit[21]: Isochronous OUT����δ����жϡ�ָʾ������1��OUT�˵��Isochronous�����ڵ�ǰ��΢֡δ��ɡ����ж���EOPF�ж�ͬʱ������
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  FetSusp      : 1;  /* bit[22]: ȡ�������жϡ�����DMAģʽʱ��Ч�����ж�ָʾ���ڷ���FIFOû�пռ��ԭ��DMAֹͣ��IN�˵��memory��ȡ���ݡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  ResetDet     : 1;  /* bit[23]: ��⵽��λ�жϡ����豸����suspend״̬�����ֵ���ʱ����⵽USB�������и�λ�������ᴥ�����жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  HPrtInt      : 1;  /* bit[24]: Host�˿��жϡ������Ҫͨ��HPRT�Ĵ���ȷ�������жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  HChInt       : 1;  /* bit[25]: Hostͨ���жϡ�ָʾ�κ�һ��ͨ�����жϴ����������Ҫͨ��HCINTn�Ĵ���ȷ�������жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  PTxFEmp      : 1;  /* bit[26]: ���ڷ���FIFO���жϣ���hostģʽ��Ч��
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  LPM_Int      : 1;  /* bit[27]: LPM�����жϡ���USB���յ�LPM��������host��Ӧ��ERROR�����жϻᴥ������λ����LPM����ʹ��ʱ��Ч��
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  ConIDStsChg  : 1;  /* bit[28]: ID״̬�仯�жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  DisconnInt   : 1;  /* bit[29]: �Ͽ������жϣ���hostģʽ��Ч��
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  SessReqInt   : 1;  /* bit[30]: ��⵽�Ự�����жϡ���utmisrp_bvalid�ӵ͵�ƽ��ɸߵ�ƽ����������жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
        unsigned int  WkUpInt      : 1;  /* bit[31]: Resume/Remote Wakwup�жϡ���⵽host������resume���������ߴ�L1״̬���ѻᴥ�����жϡ�
                                                     0�����жϣ�
                                                     1�����жϡ� */
    } reg;
} SOC_OTG_GINTSTS_UNION;
#endif
#define SOC_OTG_GINTSTS_CurMode_START       (0)
#define SOC_OTG_GINTSTS_CurMode_END         (0)
#define SOC_OTG_GINTSTS_ModeMis_START       (1)
#define SOC_OTG_GINTSTS_ModeMis_END         (1)
#define SOC_OTG_GINTSTS_OTGInt_START        (2)
#define SOC_OTG_GINTSTS_OTGInt_END          (2)
#define SOC_OTG_GINTSTS_Sof_START           (3)
#define SOC_OTG_GINTSTS_Sof_END             (3)
#define SOC_OTG_GINTSTS_RxFLvl_START        (4)
#define SOC_OTG_GINTSTS_RxFLvl_END          (4)
#define SOC_OTG_GINTSTS_NPTxFEmp_START      (5)
#define SOC_OTG_GINTSTS_NPTxFEmp_END        (5)
#define SOC_OTG_GINTSTS_GINNakEff_START     (6)
#define SOC_OTG_GINTSTS_GINNakEff_END       (6)
#define SOC_OTG_GINTSTS_GOUTNakEff_START    (7)
#define SOC_OTG_GINTSTS_GOUTNakEff_END      (7)
#define SOC_OTG_GINTSTS_ULPICKINT_START     (8)
#define SOC_OTG_GINTSTS_ULPICKINT_END       (8)
#define SOC_OTG_GINTSTS_I2CINT_START        (9)
#define SOC_OTG_GINTSTS_I2CINT_END          (9)
#define SOC_OTG_GINTSTS_ErlySusp_START      (10)
#define SOC_OTG_GINTSTS_ErlySusp_END        (10)
#define SOC_OTG_GINTSTS_USBSusp_START       (11)
#define SOC_OTG_GINTSTS_USBSusp_END         (11)
#define SOC_OTG_GINTSTS_USBRst_START        (12)
#define SOC_OTG_GINTSTS_USBRst_END          (12)
#define SOC_OTG_GINTSTS_EnumDone_START      (13)
#define SOC_OTG_GINTSTS_EnumDone_END        (13)
#define SOC_OTG_GINTSTS_ISOOutDrop_START    (14)
#define SOC_OTG_GINTSTS_ISOOutDrop_END      (14)
#define SOC_OTG_GINTSTS_EOPF_START          (15)
#define SOC_OTG_GINTSTS_EOPF_END            (15)
#define SOC_OTG_GINTSTS_RstrDoneInt_START   (16)
#define SOC_OTG_GINTSTS_RstrDoneInt_END     (16)
#define SOC_OTG_GINTSTS_IEPInt_START        (18)
#define SOC_OTG_GINTSTS_IEPInt_END          (18)
#define SOC_OTG_GINTSTS_OEPInt_START        (19)
#define SOC_OTG_GINTSTS_OEPInt_END          (19)
#define SOC_OTG_GINTSTS_incompISOIN_START   (20)
#define SOC_OTG_GINTSTS_incompISOIN_END     (20)
#define SOC_OTG_GINTSTS_incompISOOUT_START  (21)
#define SOC_OTG_GINTSTS_incompISOOUT_END    (21)
#define SOC_OTG_GINTSTS_FetSusp_START       (22)
#define SOC_OTG_GINTSTS_FetSusp_END         (22)
#define SOC_OTG_GINTSTS_ResetDet_START      (23)
#define SOC_OTG_GINTSTS_ResetDet_END        (23)
#define SOC_OTG_GINTSTS_HPrtInt_START       (24)
#define SOC_OTG_GINTSTS_HPrtInt_END         (24)
#define SOC_OTG_GINTSTS_HChInt_START        (25)
#define SOC_OTG_GINTSTS_HChInt_END          (25)
#define SOC_OTG_GINTSTS_PTxFEmp_START       (26)
#define SOC_OTG_GINTSTS_PTxFEmp_END         (26)
#define SOC_OTG_GINTSTS_LPM_Int_START       (27)
#define SOC_OTG_GINTSTS_LPM_Int_END         (27)
#define SOC_OTG_GINTSTS_ConIDStsChg_START   (28)
#define SOC_OTG_GINTSTS_ConIDStsChg_END     (28)
#define SOC_OTG_GINTSTS_DisconnInt_START    (29)
#define SOC_OTG_GINTSTS_DisconnInt_END      (29)
#define SOC_OTG_GINTSTS_SessReqInt_START    (30)
#define SOC_OTG_GINTSTS_SessReqInt_END      (30)
#define SOC_OTG_GINTSTS_WkUpInt_START       (31)
#define SOC_OTG_GINTSTS_WkUpInt_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_GINTMSK_UNION
 �ṹ˵��  : GINTMSK �Ĵ����ṹ���塣��ַƫ����:0x0018����ֵ:0x00000000�����:32
 �Ĵ���˵��: ȫ���ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved        : 1;  /* bit[0] : ������ */
        unsigned int  ModeMisMsk      : 1;  /* bit[1] : Mode Mismatch Interrupt Mask (ModeMisMsk) */
        unsigned int  OTGIntMsk       : 1;  /* bit[2] : OTG�ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  SofMsk          : 1;  /* bit[3] : sof(Start Of microFrame)�ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  RxFLvlMsk       : 1;  /* bit[4] : ����FIFO�ǿ��ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  NPTxFEmpMsk     : 1;  /* bit[5] : �����ڷ���FIFO���ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  GINNakEffMsk    : 1;  /* bit[6] : IN�˵�NAK��Ч�ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  GOUTNakEffMsk   : 1;  /* bit[7] : OUT�˵�NAK��Ч�ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  ULPICKINTMsk    : 1;  /* bit[8] : ULPI Carkit�ж�mask(ULPICKINTMsk) 
                                                        I2C Carkit�ж�mask (I2CCKINTMsk) */
        unsigned int  I2CIntMsk       : 1;  /* bit[9] : I2C�ж�mask */
        unsigned int  ErlySuspMsk     : 1;  /* bit[10]: Early suspend�ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  USBSuspMsk      : 1;  /* bit[11]: suspend�ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  USBRstMsk       : 1;  /* bit[12]: USB��λ�ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  EnumDoneMsk     : 1;  /* bit[13]: ö������ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  ISOOutDropMsk   : 1;  /* bit[14]: Isochronous OUT�������ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  EOPFMsk         : 1;  /* bit[15]: EOPF��End of Period Frame���ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  RstrDoneMsk     : 1;  /* bit[16]: �Ĵ����ָ��ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  EPMisMsk        : 1;  /* bit[17]: Device only 
                                                        Endpoint Mismatch Interrupt Mask */
        unsigned int  IEPIntMsk       : 1;  /* bit[18]: IN�˵��ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  OEPIntMsk       : 1;  /* bit[19]: OUT�˵��ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  incompISOINMsk  : 1;  /* bit[20]: Isochronous IN����δ����ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  incompISOOUTMsk : 1;  /* bit[21]: Isochronous OUT����δ����ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  FetSuspMsk      : 1;  /* bit[22]: ȡ�������ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  ResetDetMsk     : 1;  /* bit[23]: ��⵽��λ�ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  HPrtIntMsk      : 1;  /* bit[24]: Host�˿��ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  HChIntMsk       : 1;  /* bit[25]: Hostͨ���ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  PTxFEmpMsk      : 1;  /* bit[26]: ���ڷ���FIFO���ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  LPM_IntMsk      : 1;  /* bit[27]: LPM�����ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  ConIDStsChngMsk : 1;  /* bit[28]: ID״̬�仯�ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  DisconnIntMsk   : 1;  /* bit[29]: �Ͽ������ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  SessReqIntMsk   : 1;  /* bit[30]: ��⵽�Ự�����ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  WkUpIntMsk      : 1;  /* bit[31]: Resume/Remote Wakwup�ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
    } reg;
} SOC_OTG_GINTMSK_UNION;
#endif
#define SOC_OTG_GINTMSK_ModeMisMsk_START       (1)
#define SOC_OTG_GINTMSK_ModeMisMsk_END         (1)
#define SOC_OTG_GINTMSK_OTGIntMsk_START        (2)
#define SOC_OTG_GINTMSK_OTGIntMsk_END          (2)
#define SOC_OTG_GINTMSK_SofMsk_START           (3)
#define SOC_OTG_GINTMSK_SofMsk_END             (3)
#define SOC_OTG_GINTMSK_RxFLvlMsk_START        (4)
#define SOC_OTG_GINTMSK_RxFLvlMsk_END          (4)
#define SOC_OTG_GINTMSK_NPTxFEmpMsk_START      (5)
#define SOC_OTG_GINTMSK_NPTxFEmpMsk_END        (5)
#define SOC_OTG_GINTMSK_GINNakEffMsk_START     (6)
#define SOC_OTG_GINTMSK_GINNakEffMsk_END       (6)
#define SOC_OTG_GINTMSK_GOUTNakEffMsk_START    (7)
#define SOC_OTG_GINTMSK_GOUTNakEffMsk_END      (7)
#define SOC_OTG_GINTMSK_ULPICKINTMsk_START     (8)
#define SOC_OTG_GINTMSK_ULPICKINTMsk_END       (8)
#define SOC_OTG_GINTMSK_I2CIntMsk_START        (9)
#define SOC_OTG_GINTMSK_I2CIntMsk_END          (9)
#define SOC_OTG_GINTMSK_ErlySuspMsk_START      (10)
#define SOC_OTG_GINTMSK_ErlySuspMsk_END        (10)
#define SOC_OTG_GINTMSK_USBSuspMsk_START       (11)
#define SOC_OTG_GINTMSK_USBSuspMsk_END         (11)
#define SOC_OTG_GINTMSK_USBRstMsk_START        (12)
#define SOC_OTG_GINTMSK_USBRstMsk_END          (12)
#define SOC_OTG_GINTMSK_EnumDoneMsk_START      (13)
#define SOC_OTG_GINTMSK_EnumDoneMsk_END        (13)
#define SOC_OTG_GINTMSK_ISOOutDropMsk_START    (14)
#define SOC_OTG_GINTMSK_ISOOutDropMsk_END      (14)
#define SOC_OTG_GINTMSK_EOPFMsk_START          (15)
#define SOC_OTG_GINTMSK_EOPFMsk_END            (15)
#define SOC_OTG_GINTMSK_RstrDoneMsk_START      (16)
#define SOC_OTG_GINTMSK_RstrDoneMsk_END        (16)
#define SOC_OTG_GINTMSK_EPMisMsk_START         (17)
#define SOC_OTG_GINTMSK_EPMisMsk_END           (17)
#define SOC_OTG_GINTMSK_IEPIntMsk_START        (18)
#define SOC_OTG_GINTMSK_IEPIntMsk_END          (18)
#define SOC_OTG_GINTMSK_OEPIntMsk_START        (19)
#define SOC_OTG_GINTMSK_OEPIntMsk_END          (19)
#define SOC_OTG_GINTMSK_incompISOINMsk_START   (20)
#define SOC_OTG_GINTMSK_incompISOINMsk_END     (20)
#define SOC_OTG_GINTMSK_incompISOOUTMsk_START  (21)
#define SOC_OTG_GINTMSK_incompISOOUTMsk_END    (21)
#define SOC_OTG_GINTMSK_FetSuspMsk_START       (22)
#define SOC_OTG_GINTMSK_FetSuspMsk_END         (22)
#define SOC_OTG_GINTMSK_ResetDetMsk_START      (23)
#define SOC_OTG_GINTMSK_ResetDetMsk_END        (23)
#define SOC_OTG_GINTMSK_HPrtIntMsk_START       (24)
#define SOC_OTG_GINTMSK_HPrtIntMsk_END         (24)
#define SOC_OTG_GINTMSK_HChIntMsk_START        (25)
#define SOC_OTG_GINTMSK_HChIntMsk_END          (25)
#define SOC_OTG_GINTMSK_PTxFEmpMsk_START       (26)
#define SOC_OTG_GINTMSK_PTxFEmpMsk_END         (26)
#define SOC_OTG_GINTMSK_LPM_IntMsk_START       (27)
#define SOC_OTG_GINTMSK_LPM_IntMsk_END         (27)
#define SOC_OTG_GINTMSK_ConIDStsChngMsk_START  (28)
#define SOC_OTG_GINTMSK_ConIDStsChngMsk_END    (28)
#define SOC_OTG_GINTMSK_DisconnIntMsk_START    (29)
#define SOC_OTG_GINTMSK_DisconnIntMsk_END      (29)
#define SOC_OTG_GINTMSK_SessReqIntMsk_START    (30)
#define SOC_OTG_GINTMSK_SessReqIntMsk_END      (30)
#define SOC_OTG_GINTMSK_WkUpIntMsk_START       (31)
#define SOC_OTG_GINTMSK_WkUpIntMsk_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_GRXSTSR_UNION
 �ṹ˵��  : GRXSTSR �Ĵ����ṹ���塣��ַƫ����:0x001C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ȫ�ֽ���FIFO״̬�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ChNum    : 4;  /* bit[0-3]  : Channel Number */
        unsigned int  BCnt     : 11; /* bit[4-14] : ���ݰ���С�����ֽ�Ϊ��λ�� */
        unsigned int  DPID     : 2;  /* bit[15-16]: ���ݰ�PID��
                                                    00��DATA0��
                                                    10��DATA1��
                                                    01��DATA2��
                                                    11��MDATA�� */
        unsigned int  PktSts   : 4;  /* bit[17-20]: ��״̬��ָʾ���յ������ݰ�״̬��
                                                    Hostģʽ�£�
                                                    0010�����յ�IN���ݰ���
                                                    0011��IN������ɣ�
                                                    0101�����ݰ�PID��ת����
                                                    0111��ͨ��ֹͣ��
                                                    others��reserved��
                                                    Deviceģʽ�£�
                                                    0001��OUT NAK��
                                                    0010�����յ�OUT���ݰ���
                                                    0011��OUT������ɣ�
                                                    0100��Setup������ɣ�
                                                    0110�����յ�Setup����
                                                    others��reserved�� */
        unsigned int  reserved : 11; /* bit[21-31]: ������ */
    } reg;
} SOC_OTG_GRXSTSR_UNION;
#endif
#define SOC_OTG_GRXSTSR_ChNum_START     (0)
#define SOC_OTG_GRXSTSR_ChNum_END       (3)
#define SOC_OTG_GRXSTSR_BCnt_START      (4)
#define SOC_OTG_GRXSTSR_BCnt_END        (14)
#define SOC_OTG_GRXSTSR_DPID_START      (15)
#define SOC_OTG_GRXSTSR_DPID_END        (16)
#define SOC_OTG_GRXSTSR_PktSts_START    (17)
#define SOC_OTG_GRXSTSR_PktSts_END      (20)


/*****************************************************************************
 �ṹ��    : SOC_OTG_GRXSTSP_UNION
 �ṹ˵��  : GRXSTSP �Ĵ����ṹ���塣��ַƫ����:0x0020����ֵ:0x00000000�����:32
 �Ĵ���˵��: ȫ�ֽ���FIFO״̬�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  EPNum    : 4;  /* bit[0-3]  : Hostģʽ��ָʾͨ���ţ�deviceģʽ��ָʾ�˵�š� */
        unsigned int  BCnt     : 11; /* bit[4-14] : ���ݰ���С�����ֽ�Ϊ��λ�� */
        unsigned int  DPID     : 2;  /* bit[15-16]: ���ݰ�PID��
                                                    00��DATA0��
                                                    10��DATA1��
                                                    01��DATA2��
                                                    11��MDATA�� */
        unsigned int  PktSts   : 4;  /* bit[17-20]: ��״̬��ָʾ���յ������ݰ�״̬��
                                                    Hostģʽ�£�
                                                    0010�����յ�IN���ݰ���
                                                    0011��IN������ɣ�
                                                    0101�����ݰ�PID��ת����
                                                    0111��ͨ��ֹͣ��
                                                    others��reserved��
                                                    Deviceģʽ�£�
                                                    0001��OUT NAK��
                                                    0010�����յ�OUT���ݰ���
                                                    0011��OUT������ɣ�
                                                    0100��Setup������ɣ�
                                                    0110�����յ�Setup����
                                                    others��reserved�� */
        unsigned int  FN       : 4;  /* bit[21-24]: Hostģʽ�£���������
                                                    Deviceģʽ�£�֡��š�ָʾ֡��ŵĵ�4λ�����üĴ������ؽ���FIFO����״̬��ͬʱ��������FIFO���ݡ� */
        unsigned int  reserved : 7;  /* bit[25-31]: ������ */
    } reg;
} SOC_OTG_GRXSTSP_UNION;
#endif
#define SOC_OTG_GRXSTSP_EPNum_START     (0)
#define SOC_OTG_GRXSTSP_EPNum_END       (3)
#define SOC_OTG_GRXSTSP_BCnt_START      (4)
#define SOC_OTG_GRXSTSP_BCnt_END        (14)
#define SOC_OTG_GRXSTSP_DPID_START      (15)
#define SOC_OTG_GRXSTSP_DPID_END        (16)
#define SOC_OTG_GRXSTSP_PktSts_START    (17)
#define SOC_OTG_GRXSTSP_PktSts_END      (20)
#define SOC_OTG_GRXSTSP_FN_START        (21)
#define SOC_OTG_GRXSTSP_FN_END          (24)


/*****************************************************************************
 �ṹ��    : SOC_OTG_GRXFSIZ_UNION
 �ṹ˵��  : GRXFSIZ �Ĵ����ṹ���塣��ַƫ����:0x0024����ֵ:0x00001000�����:32
 �Ĵ���˵��: ȫ�ֽ���FIFO��С�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  RxFDep   : 16; /* bit[0-15] : ����FIFO��ȡ���4�ֽ�Ϊ��λ�� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_OTG_GRXFSIZ_UNION;
#endif
#define SOC_OTG_GRXFSIZ_RxFDep_START    (0)
#define SOC_OTG_GRXFSIZ_RxFDep_END      (15)


/*****************************************************************************
 �ṹ��    : SOC_OTG_GNPTXFSIZ_UNION
 �ṹ˵��  : GNPTXFSIZ �Ĵ����ṹ���塣��ַƫ����:0x0028����ֵ:0x10001000�����:32
 �Ĵ���˵��: ȫ�ַ����ڷ���FIFO��С�Ĵ����� (Host Mode and Device Shared FIFO Mode)
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  NPTxFStAddr : 16; /* bit[0-15] : �����ڷ���FIFO��ʼ��ַ����4�ֽ�Ϊ��λ�� */
        unsigned int  NPTxFDep    : 16; /* bit[16-31]: �����ڷ���FIFO��ȡ���4�ֽ�Ϊ��λ�� */
    } reg;
} SOC_OTG_GNPTXFSIZ_UNION;
#endif
#define SOC_OTG_GNPTXFSIZ_NPTxFStAddr_START  (0)
#define SOC_OTG_GNPTXFSIZ_NPTxFStAddr_END    (15)
#define SOC_OTG_GNPTXFSIZ_NPTxFDep_START     (16)
#define SOC_OTG_GNPTXFSIZ_NPTxFDep_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_GNPTXSTS_UNION
 �ṹ˵��  : GNPTXSTS �Ĵ����ṹ���塣��ַƫ����:0x002C����ֵ:0x00081000�����:32
 �Ĵ���˵��: ȫ�ַ����ڷ���FIFO״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  NPTxFSpcAvail : 16; /* bit[0-15] : �����ڷ���FIFOʣ��ռ䡣��4�ֽ�Ϊ��λ�� */
        unsigned int  NPTxQSpcAvail : 8;  /* bit[16-23]: �����ڷ����������ʣ��ռ䡣
                                                         �����ڷ�������������Ϊ8������ָʾ����������л����Ի��漸���������� */
        unsigned int  NPTxQTop      : 7;  /* bit[24-30]: �ȴ�����ķ����ڷ�������
                                                         Bit[30:27]:ͨ���ţ�
                                                         Bit[26:25]
                                                         00��OUT���ƣ�
                                                         01���㳤����
                                                         10��PING/CSPLIT���ƣ�
                                                         11��ͨ��ֹͣ���
                                                         Bit[24]:������־��ָʾ������Ϊ��ǰͨ�������һ������ */
        unsigned int  reserved      : 1;  /* bit[31]   : ������ */
    } reg;
} SOC_OTG_GNPTXSTS_UNION;
#endif
#define SOC_OTG_GNPTXSTS_NPTxFSpcAvail_START  (0)
#define SOC_OTG_GNPTXSTS_NPTxFSpcAvail_END    (15)
#define SOC_OTG_GNPTXSTS_NPTxQSpcAvail_START  (16)
#define SOC_OTG_GNPTXSTS_NPTxQSpcAvail_END    (23)
#define SOC_OTG_GNPTXSTS_NPTxQTop_START       (24)
#define SOC_OTG_GNPTXSTS_NPTxQTop_END         (30)


/*****************************************************************************
 �ṹ��    : SOC_OTG_GSNPSID_UNION
 �ṹ˵��  : GSNPSID �Ĵ����ṹ���塣��ַƫ����:0x0040����ֵ:0x4F54310A�����:32
 �Ĵ���˵��: USB IP�汾�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  UserID : 32; /* bit[0-31]: USB IP�汾�Ĵ������汾Ϊ3.10a�� */
    } reg;
} SOC_OTG_GSNPSID_UNION;
#endif
#define SOC_OTG_GSNPSID_UserID_START  (0)
#define SOC_OTG_GSNPSID_UserID_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_GHWCFG1_UNION
 �ṹ˵��  : GHWCFG1 �Ĵ����ṹ���塣��ַƫ����:0x0044����ֵ:0x00000000�����:32
 �Ĵ���˵��: Ӳ�����üĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  epdir : 32; /* bit[0-31]: �˵㷽��Ĵ�����
                                                Bit[31:30]���˵�15����
                                                bit[29:28]���˵�14����
                                                ����
                                                bit[1:0]���˵�0����
                                                �����˵�ֵ��
                                                00��˫��˵㣻
                                                01��IN�˵㣻
                                                10��OUT�˵㣻
                                                11�������� */
    } reg;
} SOC_OTG_GHWCFG1_UNION;
#endif
#define SOC_OTG_GHWCFG1_epdir_START  (0)
#define SOC_OTG_GHWCFG1_epdir_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_GHWCFG2_UNION
 �ṹ˵��  : GHWCFG2 �Ĵ����ṹ���塣��ַƫ����:0x0048����ֵ:0x22ACFC50�����:32
 �Ĵ���˵��: Ӳ�����üĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  OtgMode         : 3;  /* bit[0-2]  : OTGģʽ��
                                                           000��HNP��SRPʹ��OTG,����host��device��
                                                           001��SRPʹ��OTG,����host��device��
                                                           010��HNP��SRP��ʹ��OTG,����host��device��
                                                           011��SRPʹ��device��
                                                           100����OTG device��
                                                           101��SRPʹ��host��
                                                           110����OTG host��
                                                           111�������� */
        unsigned int  OtgArch         : 2;  /* bit[3-4]  : DMAģʽ���á�
                                                           00����DMAģʽ��ֻ��1��AHB slave�ӿڣ�
                                                           01���ⲿDMA��
                                                           10���ڲ�DMA
                                                           11�������� */
        unsigned int  SingPnt         : 1;  /* bit[5]    : Point-to-Potintģʽʹ�ܡ������ý����host��Ч��
                                                           0����ʹ�ܣ�
                                                           1��ʹ�ܡ� */
        unsigned int  HSPhyType       : 2;  /* bit[6-7]  : ����PHY�ӿ�����ѡ��
                                                           00����֧�ָ���ģʽ��
                                                           01��UTMI+��
                                                           10��ULPI��
                                                           11��UTMI+��ULPI��֧�֣���������á� */
        unsigned int  FSPhyType       : 2;  /* bit[8-9]  : ȫ��PHY�ӿ����͡�
                                                           00����֧��ȫ��PHY�ӿڣ�
                                                           01��ר��ȫ�ٽӿڣ�
                                                           10��ȫ�ٹܽ���UTMI+�ܽŸ��ã�
                                                           11��ȫ�ٹܽ���ULPI�ܽŸ��á� */
        unsigned int  NumDevEps       : 4;  /* bit[10-13]: ���˵�0֮��֧�ֵĶ˵���Ŀ����ΧΪ1~15�� */
        unsigned int  NumHstChnl      : 4;  /* bit[14-17]: Hostͨ����Ŀ����֧��host��Ч�� */
        unsigned int  PerioSupport    : 1;  /* bit[18]   : Hostģʽʱ���Ƿ�֧������OUTͨ����
                                                           0����֧�֣�
                                                           1��֧�֡� */
        unsigned int  DynFifoSizing   : 1;  /* bit[19]   : �Ƿ�֧��FIFO��С��̬���á�
                                                           0����֧�֣�
                                                           1��֧�֡� */
        unsigned int  MultiProcIntrpt : 1;  /* bit[20]   : �Ƿ�֧�ֶ��ж��ϱ���
                                                           0����֧�֣�
                                                           1��֧�֡� */
        unsigned int  reserved        : 1;  /* bit[21]   : ������ */
        unsigned int  NPTxQDepth      : 2;  /* bit[22-23]: ���������������ȡ�
                                                           00��2��
                                                           01��4��
                                                           10��8��
                                                           others��reserved�� */
        unsigned int  PTxQDepth       : 2;  /* bit[24-25]: hostģʽʱ���������������ȡ�
                                                           00��2��
                                                           01��4��
                                                           10��8��
                                                           others��reserved�� */
        unsigned int  TknQDepth       : 5;  /* bit[26-30]: deviceģʽʱ��IN����������ȡ� */
        unsigned int  OTG_IC_USB      : 1;  /* bit[31]   : �Ƿ�֧��IC_USBģʽ��
                                                           0����֧�֣�
                                                           1��֧�֡� */
    } reg;
} SOC_OTG_GHWCFG2_UNION;
#endif
#define SOC_OTG_GHWCFG2_OtgMode_START          (0)
#define SOC_OTG_GHWCFG2_OtgMode_END            (2)
#define SOC_OTG_GHWCFG2_OtgArch_START          (3)
#define SOC_OTG_GHWCFG2_OtgArch_END            (4)
#define SOC_OTG_GHWCFG2_SingPnt_START          (5)
#define SOC_OTG_GHWCFG2_SingPnt_END            (5)
#define SOC_OTG_GHWCFG2_HSPhyType_START        (6)
#define SOC_OTG_GHWCFG2_HSPhyType_END          (7)
#define SOC_OTG_GHWCFG2_FSPhyType_START        (8)
#define SOC_OTG_GHWCFG2_FSPhyType_END          (9)
#define SOC_OTG_GHWCFG2_NumDevEps_START        (10)
#define SOC_OTG_GHWCFG2_NumDevEps_END          (13)
#define SOC_OTG_GHWCFG2_NumHstChnl_START       (14)
#define SOC_OTG_GHWCFG2_NumHstChnl_END         (17)
#define SOC_OTG_GHWCFG2_PerioSupport_START     (18)
#define SOC_OTG_GHWCFG2_PerioSupport_END       (18)
#define SOC_OTG_GHWCFG2_DynFifoSizing_START    (19)
#define SOC_OTG_GHWCFG2_DynFifoSizing_END      (19)
#define SOC_OTG_GHWCFG2_MultiProcIntrpt_START  (20)
#define SOC_OTG_GHWCFG2_MultiProcIntrpt_END    (20)
#define SOC_OTG_GHWCFG2_NPTxQDepth_START       (22)
#define SOC_OTG_GHWCFG2_NPTxQDepth_END         (23)
#define SOC_OTG_GHWCFG2_PTxQDepth_START        (24)
#define SOC_OTG_GHWCFG2_PTxQDepth_END          (25)
#define SOC_OTG_GHWCFG2_TknQDepth_START        (26)
#define SOC_OTG_GHWCFG2_TknQDepth_END          (30)
#define SOC_OTG_GHWCFG2_OTG_IC_USB_START       (31)
#define SOC_OTG_GHWCFG2_OTG_IC_USB_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_GHWCFG3_UNION
 �ṹ˵��  : GHWCFG3 �Ĵ����ṹ���塣��ַƫ����:0x004C����ֵ:0x0F80D4E8�����:32
 �Ĵ���˵��: Ӳ�����üĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferSizeWidth   : 4;  /* bit[0-3]  : �����С��������ȡ�
                                                           0000��11bit��
                                                           0001��12bit��
                                                           ����
                                                           1000��19bit��
                                                           others��reserved�� */
        unsigned int  PktSizeWidth    : 3;  /* bit[4-6]  : ����С��������ȡ�
                                                           000��4bit��
                                                           001��5bit��
                                                           010��6bit��
                                                           011��7bit��
                                                           100��8bit��
                                                           101��9bit��
                                                           110��10bit��
                                                           others��reserved�� */
        unsigned int  OtgEn           : 1;  /* bit[7]    : �Ƿ�ʹ��OTG���ܡ���bit��OTG_MODE������������OTG_MODE����Ϊ0��1��2ʱ��OtgEn=1��
                                                           0����ʹ�ܣ�
                                                           1��ʹ�ܡ� */
        unsigned int  I2CIntSel       : 1;  /* bit[8]    : �Ƿ�֧��I2C�ӿڡ�
                                                           0����֧�֣�
                                                           1��֧�֡� */
        unsigned int  VndctlSupt      : 1;  /* bit[9]    : �Ƿ�֧��Vendor Control�ӿڡ�
                                                           0����֧�֣�
                                                           1��֧�֡� */
        unsigned int  OptFeature      : 1;  /* bit[10]   : �Ƿ�֧��ȡ�������ԣ�User ID�Ĵ�����GPIO�ӿڣ�SOF��ת�źźͼ������ӿڡ�
                                                           0����֧�֣�
                                                           1��֧�֡� */
        unsigned int  RstType         : 1;  /* bit[11]   : ��always����У���λ�����͡�
                                                           0���첽��λ��
                                                           1��ͬ����λ�� */
        unsigned int  OTG_ADP_SUPPORT : 1;  /* bit[12]   : �Ƿ�֧��ADP��
                                                           0����֧�֣�
                                                           1��֧�֡� */
        unsigned int  OTG_ENABLE_HSIC : 1;  /* bit[13]   : �Ƿ�֧��HSIC��
                                                           0����֧�֣�
                                                           1��֧�֡� */
        unsigned int  OTG_BC_SUPPORT  : 1;  /* bit[14]   : �Ƿ�֧��BC��
                                                           0����֧�֣�
                                                           1��֧�֡� */
        unsigned int  OTG_ENABLE_LPM  : 1;  /* bit[15]   : �Ƿ�֧��LPM��
                                                           0����֧�֣�
                                                           1��֧�֡� */
        unsigned int  DfifoDepth      : 16; /* bit[16-31]: ����FIFO����ȣ���4�ֽ�Ϊ��λ������FIFO�ͽ���FIFO��С֮�Ͳ��ܴ��ڸ�ֵ�� */
    } reg;
} SOC_OTG_GHWCFG3_UNION;
#endif
#define SOC_OTG_GHWCFG3_XferSizeWidth_START    (0)
#define SOC_OTG_GHWCFG3_XferSizeWidth_END      (3)
#define SOC_OTG_GHWCFG3_PktSizeWidth_START     (4)
#define SOC_OTG_GHWCFG3_PktSizeWidth_END       (6)
#define SOC_OTG_GHWCFG3_OtgEn_START            (7)
#define SOC_OTG_GHWCFG3_OtgEn_END              (7)
#define SOC_OTG_GHWCFG3_I2CIntSel_START        (8)
#define SOC_OTG_GHWCFG3_I2CIntSel_END          (8)
#define SOC_OTG_GHWCFG3_VndctlSupt_START       (9)
#define SOC_OTG_GHWCFG3_VndctlSupt_END         (9)
#define SOC_OTG_GHWCFG3_OptFeature_START       (10)
#define SOC_OTG_GHWCFG3_OptFeature_END         (10)
#define SOC_OTG_GHWCFG3_RstType_START          (11)
#define SOC_OTG_GHWCFG3_RstType_END            (11)
#define SOC_OTG_GHWCFG3_OTG_ADP_SUPPORT_START  (12)
#define SOC_OTG_GHWCFG3_OTG_ADP_SUPPORT_END    (12)
#define SOC_OTG_GHWCFG3_OTG_ENABLE_HSIC_START  (13)
#define SOC_OTG_GHWCFG3_OTG_ENABLE_HSIC_END    (13)
#define SOC_OTG_GHWCFG3_OTG_BC_SUPPORT_START   (14)
#define SOC_OTG_GHWCFG3_OTG_BC_SUPPORT_END     (14)
#define SOC_OTG_GHWCFG3_OTG_ENABLE_LPM_START   (15)
#define SOC_OTG_GHWCFG3_OTG_ENABLE_LPM_END     (15)
#define SOC_OTG_GHWCFG3_DfifoDepth_START       (16)
#define SOC_OTG_GHWCFG3_DfifoDepth_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_GHWCFG4_UNION
 �ṹ˵��  : GHWCFG4 �Ĵ����ṹ���塣��ַƫ����:0x0050����ֵ:0xFFF08060�����:32
 �Ĵ���˵��: Ӳ�����üĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  NumDevEps          : 4;  /* bit[0-3]  : ֧������IN�˵�������������DedFifoMode��0ʱ��Ч�� */
        unsigned int  EnablePwrOpt       : 1;  /* bit[4]    : �Ƿ�ʹ�ܹ����Ż���ʹ�ܹ����Ż���USBģ��ֳɵ�����Ͳ������򣬲��Ҽ���ʱ���ſ��߼���
                                                              0����ʹ�ܣ�
                                                              1��ʹ�ܡ� */
        unsigned int  AhbFreq            : 1;  /* bit[5]    : ��СAHBƵ���Ƿ�С��60MHz��
                                                              0�����ǣ�
                                                              1���ǡ� */
        unsigned int  Hibernation        : 1;  /* bit[6]    : ʹ��Hibernation��
                                                              0�� Hibernation feature��ʹ��
                                                              1�� Hibernation featureʹ�� */
        unsigned int  ExtndedHibernation : 1;  /* bit[7]    : �ⲿ Hibernation ʹ��
                                                              0�� Hibernation feature��ʹ��
                                                              1�� Hibernation featureʹ�� */
        unsigned int  reserved_0         : 6;  /* bit[8-13] : ������ */
        unsigned int  PhyDataWidth       : 2;  /* bit[14-15]: PHY�����߿�ȡ�
                                                              00��8bit��
                                                              01��16bit��
                                                              10�����������Ϊ8bit����16bit��
                                                              others��reserved�� */
        unsigned int  NumCtlEps          : 4;  /* bit[16-19]: ���˶˵�0֮��֧�ֵĿ��ƶ˵���Ŀ�� */
        unsigned int  IddigFltr          : 1;  /* bit[20]   : �Ƿ�֧���ź�iddig��ë�̡�
                                                              0����֧�֣�
                                                              1��֧�֡� */
        unsigned int  VBusValidFltr      : 1;  /* bit[21]   : �Ƿ�֧���ź�vbus_valid��ë�̡�
                                                              0����֧�֣�
                                                              1��֧�֡� */
        unsigned int  AValidFltr         : 1;  /* bit[22]   : �Ƿ�֧���ź�avalid��ë�̡�
                                                              0����֧�֣�
                                                              1��֧�֡� */
        unsigned int  BValidFltr         : 1;  /* bit[23]   : �Ƿ�֧���ź�bvalid��ë�̡�
                                                              0����֧�֣�
                                                              1��֧�֡� */
        unsigned int  SessEndFltr        : 1;  /* bit[24]   : �Ƿ�֧���ź�session_end��ë�̡�
                                                              0����֧�֣�
                                                              1��֧�֡� */
        unsigned int  DedFifoMode        : 1;  /* bit[25]   : �Ƿ�֧��IN�˵�ר�з���FIFO���ܡ�
                                                              0����֧�֣�
                                                              1��֧�֡� */
        unsigned int  INEps              : 4;  /* bit[26-29]: �������ƶ˵����ڣ�IN�˵����Ŀ��
                                                              0000��1����
                                                              0001��2����
                                                              ����
                                                              1111��16���� */
        unsigned int  SGDMA              : 1;  /* bit[30]   : �Ƿ�֧��Scatter/Gather DMA��
                                                              0����֧�֣�
                                                              1��֧�֡� */
        unsigned int  reserved_1         : 1;  /* bit[31]   : ������ */
    } reg;
} SOC_OTG_GHWCFG4_UNION;
#endif
#define SOC_OTG_GHWCFG4_NumDevEps_START           (0)
#define SOC_OTG_GHWCFG4_NumDevEps_END             (3)
#define SOC_OTG_GHWCFG4_EnablePwrOpt_START        (4)
#define SOC_OTG_GHWCFG4_EnablePwrOpt_END          (4)
#define SOC_OTG_GHWCFG4_AhbFreq_START             (5)
#define SOC_OTG_GHWCFG4_AhbFreq_END               (5)
#define SOC_OTG_GHWCFG4_Hibernation_START         (6)
#define SOC_OTG_GHWCFG4_Hibernation_END           (6)
#define SOC_OTG_GHWCFG4_ExtndedHibernation_START  (7)
#define SOC_OTG_GHWCFG4_ExtndedHibernation_END    (7)
#define SOC_OTG_GHWCFG4_PhyDataWidth_START        (14)
#define SOC_OTG_GHWCFG4_PhyDataWidth_END          (15)
#define SOC_OTG_GHWCFG4_NumCtlEps_START           (16)
#define SOC_OTG_GHWCFG4_NumCtlEps_END             (19)
#define SOC_OTG_GHWCFG4_IddigFltr_START           (20)
#define SOC_OTG_GHWCFG4_IddigFltr_END             (20)
#define SOC_OTG_GHWCFG4_VBusValidFltr_START       (21)
#define SOC_OTG_GHWCFG4_VBusValidFltr_END         (21)
#define SOC_OTG_GHWCFG4_AValidFltr_START          (22)
#define SOC_OTG_GHWCFG4_AValidFltr_END            (22)
#define SOC_OTG_GHWCFG4_BValidFltr_START          (23)
#define SOC_OTG_GHWCFG4_BValidFltr_END            (23)
#define SOC_OTG_GHWCFG4_SessEndFltr_START         (24)
#define SOC_OTG_GHWCFG4_SessEndFltr_END           (24)
#define SOC_OTG_GHWCFG4_DedFifoMode_START         (25)
#define SOC_OTG_GHWCFG4_DedFifoMode_END           (25)
#define SOC_OTG_GHWCFG4_INEps_START               (26)
#define SOC_OTG_GHWCFG4_INEps_END                 (29)
#define SOC_OTG_GHWCFG4_SGDMA_START               (30)
#define SOC_OTG_GHWCFG4_SGDMA_END                 (30)


/*****************************************************************************
 �ṹ��    : SOC_OTG_GLPMCFG_UNION
 �ṹ˵��  : GLPMCFG �Ĵ����ṹ���塣��ַƫ����:0x0054����ֵ:0x00000000�����:32
 �Ĵ���˵��: LPM���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  LPMCap           : 1;  /* bit[0]    : LPMʹ�ܡ�
                                                            0����ʹ�ܣ�
                                                            1��ʹ�ܡ� */
        unsigned int  APPL1Res         : 1;  /* bit[1]    : LPM��Ӧ���ã�����deviceģʽ��Ч����LPM����ʹ�ܡ����LPM��ʹ�ܣ���һֱ����NYET��
                                                            0��NYET��
                                                            1��ACK�� */
        unsigned int  HIRD             : 4;  /* bit[2-5]  : Resume����ʱ�䡣
                                                            ����hostģʽ������ɶ�д���������ΪLPM�������HIRDֵ��
                                                            ����deviceģʽ������ֻ�����յ�LPM��֮����������¸���
                                                            0000��50us��
                                                            0001��125us��
                                                            0010��250us��
                                                            0011��275us��
                                                            0100��350us��
                                                            0101��425us��
                                                            0110��500us��
                                                            0111��575us��
                                                            1000��650us��
                                                            1001��725us��
                                                            1010��800us��
                                                            1011��875us��
                                                            1100��950us��
                                                            1101��1025us��
                                                            1110��1100us��
                                                            1111��1175us�� */
        unsigned int  bRemoteWake      : 1;  /* bit[6]    : Զ�̻���ʹ�ܡ���device�յ�bRemoteWake LPM��ʱ��������¡�
                                                            0����ʹ�ܣ�
                                                            1��ʹ�ܡ� */
        unsigned int  EnblSlpM         : 1;  /* bit[7]    : ʹ��utmi_sleep_n�����Ĵ���L1״̬ʱ��������ø�bit��ʹutmi_sleep_n�ź���Ϊ��Ч��
                                                            0����ʹ�ܣ�
                                                            1��ʹ�ܡ� */
        unsigned int  HIRD_Thres       : 5;  /* bit[8-12] : HIRDˮ�ߡ����bitΪʹ��λ����4bitΪˮ��ֵ��
                                                            ����deviceģʽ����HIRDʱ�䳬��ˮ��ֵʱ����������λSuspendM�ź�ʹPHY����͹���ģʽ��
                                                            0000��60us��
                                                            0001��135us��
                                                            0010��210us��
                                                            0011��285us��
                                                            0100��360us��
                                                            0101��435us��
                                                            0110��510us��
                                                            0111��585us��
                                                            1000��660us��
                                                            1001��735us��
                                                            1010��810us��
                                                            1011��885us��
                                                            1100��960us��
                                                            others��reserved�� */
        unsigned int  CoreL1Res        : 2;  /* bit[13-14]: LPM��Ӧ��
                                                            ����hostģʽ��ָʾ���յ������ְ�������deviceģʽ�����յ�LPM��֮���ո��������ְ���
                                                            00��ERROR��
                                                            01��STALL��
                                                            10��NYET��
                                                            11��ACK�� */
        unsigned int  SlpSts           : 1;  /* bit[15]   : sleep״ָ̬ʾ��
                                                            0��û�н���sleep״̬��
                                                            1������sleep״̬�� */
        unsigned int  L1ResumeOk       : 1;  /* bit[16]   : ָʾ�Ƿ���Դ�sleep״̬���ѡ�����sleep״̬50us֮�󣬸ñ�����λ��
                                                            0�������Դ�sleep״̬���ѣ�
                                                            1�����Դ�sleep״̬���ѡ� */
        unsigned int  LPM_Chnl_Index   : 4;  /* bit[17-20]: ����LPM��ͨ���ţ���hostģʽ��Ч�� */
        unsigned int  LPM_Retry_Cnt    : 3;  /* bit[21-23]: LPM Retry�������ã���hostģʽ��Ч��ָʾ�յ���Ч����Ӧ֮ǰ��host�������·���LPM�Ĵ����� */
        unsigned int  SndLPM           : 1;  /* bit[24]   : ����LPM���񣬶�hostģʽ��Ч��
                                                            ������ø�bit�����Ʒ�����չ���ư���LPM���ư������յ���Ч����Ӧ(STALL��NYET����ACK)֮��Ӳ�������bit��
                                                            0����ʹ�ܣ�
                                                            1��ʹ�ܡ� */
        unsigned int  LPM_RetryCnt_Sts : 3;  /* bit[25-27]: LPM retry״̬����hostģʽ��Ч��ָʾ��ǰLPM����ʣ���retry���� */
        unsigned int  EnBESL           : 1;  /* bit[28]   : ����latencyʹ�� */
        unsigned int  RstrSlpSts       : 1;  /* bit[29]   : Device only Restore SlpSts (RstrSlpSts)
                                                            0�� in Shallow Sleep mode 
                                                            1�� in Deep Sleep mode */
        unsigned int  HSICCon          : 1;  /* bit[30]   : hostģʽ������HSIC����ΪIDLE
                                                            deviceģʽ���ȴ�HSIC����ΪIDLE */
        unsigned int  InvSelHsic       : 1;  /* bit[31]   : HSIC-Invert Select HSIC
                                                            ��if_sel_hsic����1:
                                                            1��HSIC capability��ʹ��
                                                            0��HSIC capabilityʹ��
                                                            ��if_sel_hsic����0:
                                                            1��HSIC capabilityʹ��
                                                            0��HSIC capability��ʹ�� */
    } reg;
} SOC_OTG_GLPMCFG_UNION;
#endif
#define SOC_OTG_GLPMCFG_LPMCap_START            (0)
#define SOC_OTG_GLPMCFG_LPMCap_END              (0)
#define SOC_OTG_GLPMCFG_APPL1Res_START          (1)
#define SOC_OTG_GLPMCFG_APPL1Res_END            (1)
#define SOC_OTG_GLPMCFG_HIRD_START              (2)
#define SOC_OTG_GLPMCFG_HIRD_END                (5)
#define SOC_OTG_GLPMCFG_bRemoteWake_START       (6)
#define SOC_OTG_GLPMCFG_bRemoteWake_END         (6)
#define SOC_OTG_GLPMCFG_EnblSlpM_START          (7)
#define SOC_OTG_GLPMCFG_EnblSlpM_END            (7)
#define SOC_OTG_GLPMCFG_HIRD_Thres_START        (8)
#define SOC_OTG_GLPMCFG_HIRD_Thres_END          (12)
#define SOC_OTG_GLPMCFG_CoreL1Res_START         (13)
#define SOC_OTG_GLPMCFG_CoreL1Res_END           (14)
#define SOC_OTG_GLPMCFG_SlpSts_START            (15)
#define SOC_OTG_GLPMCFG_SlpSts_END              (15)
#define SOC_OTG_GLPMCFG_L1ResumeOk_START        (16)
#define SOC_OTG_GLPMCFG_L1ResumeOk_END          (16)
#define SOC_OTG_GLPMCFG_LPM_Chnl_Index_START    (17)
#define SOC_OTG_GLPMCFG_LPM_Chnl_Index_END      (20)
#define SOC_OTG_GLPMCFG_LPM_Retry_Cnt_START     (21)
#define SOC_OTG_GLPMCFG_LPM_Retry_Cnt_END       (23)
#define SOC_OTG_GLPMCFG_SndLPM_START            (24)
#define SOC_OTG_GLPMCFG_SndLPM_END              (24)
#define SOC_OTG_GLPMCFG_LPM_RetryCnt_Sts_START  (25)
#define SOC_OTG_GLPMCFG_LPM_RetryCnt_Sts_END    (27)
#define SOC_OTG_GLPMCFG_EnBESL_START            (28)
#define SOC_OTG_GLPMCFG_EnBESL_END              (28)
#define SOC_OTG_GLPMCFG_RstrSlpSts_START        (29)
#define SOC_OTG_GLPMCFG_RstrSlpSts_END          (29)
#define SOC_OTG_GLPMCFG_HSICCon_START           (30)
#define SOC_OTG_GLPMCFG_HSICCon_END             (30)
#define SOC_OTG_GLPMCFG_InvSelHsic_START        (31)
#define SOC_OTG_GLPMCFG_InvSelHsic_END          (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_GPWRDN_UNION
 �ṹ˵��  : GPWRDN �Ĵ����ṹ���塣��ַƫ����:0x0058����ֵ:0x00200010�����:32
 �Ĵ���˵��: ����ģʽ������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PMUIntSel           : 1;  /* bit[0]    : PMU�ж�ѡ�񡣸�bit����Ϊ1����PMU�������ж��ϱ����������������ж����Ρ�
                                                               0��ѡ��������������жϣ�
                                                               1��ѡ��PMU�������жϡ� */
        unsigned int  PMUActv             : 1;  /* bit[1]    : ʹ��PMU���ܡ�
                                                               0����ʹ�ܣ�
                                                               1��ʹ�ܡ� */
        unsigned int  Restore             : 1;  /* bit[2]    : �Ĵ����ָ����ơ�
                                                               0����ʹ�ܣ�
                                                               1��ʹ�ܡ� */
        unsigned int  PwrDnClmp           : 1;  /* bit[3]    : ������λ���ơ�������ø�bit�ǿ�����������źŹ̶���ȷ����״̬��
                                                               0����ʹ�ܣ�
                                                               1��ʹ�ܡ� */
        unsigned int  PwrDnRst_n          : 1;  /* bit[4]    : ���縴λ���ơ����˳�����ģʽ����ADP�ϵ�֮ǰ������������ø�bit�Կ��������и�λ��
                                                               0����λ��������
                                                               1������λ�������� */
        unsigned int  PwrDnSwtch          : 1;  /* bit[5]    : ���翪�ء�ָʾ��������Դ�ض�״̬��
                                                               0��ON��
                                                               1��OFF��
                                                               ����������״̬�²������ø�bit�� */
        unsigned int  VbusOff             : 1;  /* bit[6]    : ��Hostģʽ�£��ڽ��붬��ģʽ֮ǰ��
                                                               0��HPRT[PrtPwr]����û������Ϊ0��
                                                               1��HPRT[Prtpwr]����Ϊ0��
                                                               ��Deviceģʽ�£��ڶԿ���������֮ǰ��
                                                               0��bvalid��Ч��
                                                               1��bvalid��Ч��
                                                               ��bit����PMUActv��1��Ч�� */
        unsigned int  LnStsChng           : 1;  /* bit[7]    : ���LineState�仯�жϡ�
                                                               0�����жϣ�
                                                               1���жϡ� */
        unsigned int  LnStsChngMsk        : 1;  /* bit[8]    : LnStsChng�ж�����λ��
                                                               0�����Σ�
                                                               1�������Ρ� */
        unsigned int  ResetDetected       : 1;  /* bit[9]    : ��⵽��λ�����жϣ���deviceģʽ��Ч��
                                                               0�����жϣ�
                                                               1�����жϡ� */
        unsigned int  ResetDetMsk         : 1;  /* bit[10]   : ResetDetcted�ж�����λ����deviceģʽ��Ч��
                                                               0�����Σ�
                                                               1�������Ρ� */
        unsigned int  DisconnectDetect    : 1;  /* bit[11]   : �Ͽ������жϣ���hostģʽ��Ч��
                                                               0�����жϣ�
                                                               1�����жϡ� */
        unsigned int  DisconnectDetectMsk : 1;  /* bit[12]   : DisconnectDetect�ж�����λ����hostģʽ��Ч��
                                                               0�����Σ�
                                                               1�������Ρ� */
        unsigned int  ConnectDet          : 1;  /* bit[13]   : ��⵽�����жϡ�
                                                               0�����жϣ�
                                                               1�����жϡ� */
        unsigned int  ConnDetMsk          : 1;  /* bit[14]   : ConnectDet�ж�����λ��
                                                               0�����Σ�
                                                               1�������Ρ� */
        unsigned int  SRPDetect           : 1;  /* bit[15]   : ��⵽SRP�жϡ���hostģʽ��Ч��
                                                               0�����жϣ�
                                                               1�����жϡ� */
        unsigned int  SRPDetectMsk        : 1;  /* bit[16]   : SRPDetect�ж�����λ����hostģʽ��Ч��
                                                               0�������Σ�
                                                               1�����Ρ� */
        unsigned int  StsChngInt          : 1;  /* bit[17]   : StsChng�жϡ�ָʾIDDIG����bvalid״̬�仯��
                                                               0�����жϣ�
                                                               1�����жϡ� */
        unsigned int  StsChngMsk          : 1;  /* bit[18]   : StsChng�ж�����λ��
                                                               0�����Σ�
                                                               1�������Ρ� */
        unsigned int  LineState           : 2;  /* bit[19-20]: ��ǰlinestate��
                                                               00��DM=0��DP=0��
                                                               01��DM=0��DP=1��
                                                               10��DM=1��DP=0��
                                                               11��reserved�� */
        unsigned int  IDDIG               : 1;  /* bit[21]   : IDDIG״̬����PMUActv��1��Ч��
                                                               0���͵�ƽ��
                                                               1���ߵ�ƽ�� */
        unsigned int  BSessVld            : 1;  /* bit[22]   : bvalid��Ч״̬����PMUActv��1��Ч��
                                                               0����Ч��
                                                               1����Ч�� */
        unsigned int  ADPInt              : 1;  /* bit[23]   : ADP�ж�״̬��
                                                               0�����жϣ�
                                                               1�����жϡ� */
        unsigned int  MultValIdBc         : 5;  /* bit[24-28]: ACA����ID״̬��
                                                               00001��rid_c��
                                                               00010��rid_b��
                                                               00100��rid_a��
                                                               01000��rid_gnd��
                                                               10000��rid_float��
                                                               others��reserved�� */
        unsigned int  reserved            : 3;  /* bit[29-31]: ������ */
    } reg;
} SOC_OTG_GPWRDN_UNION;
#endif
#define SOC_OTG_GPWRDN_PMUIntSel_START            (0)
#define SOC_OTG_GPWRDN_PMUIntSel_END              (0)
#define SOC_OTG_GPWRDN_PMUActv_START              (1)
#define SOC_OTG_GPWRDN_PMUActv_END                (1)
#define SOC_OTG_GPWRDN_Restore_START              (2)
#define SOC_OTG_GPWRDN_Restore_END                (2)
#define SOC_OTG_GPWRDN_PwrDnClmp_START            (3)
#define SOC_OTG_GPWRDN_PwrDnClmp_END              (3)
#define SOC_OTG_GPWRDN_PwrDnRst_n_START           (4)
#define SOC_OTG_GPWRDN_PwrDnRst_n_END             (4)
#define SOC_OTG_GPWRDN_PwrDnSwtch_START           (5)
#define SOC_OTG_GPWRDN_PwrDnSwtch_END             (5)
#define SOC_OTG_GPWRDN_VbusOff_START              (6)
#define SOC_OTG_GPWRDN_VbusOff_END                (6)
#define SOC_OTG_GPWRDN_LnStsChng_START            (7)
#define SOC_OTG_GPWRDN_LnStsChng_END              (7)
#define SOC_OTG_GPWRDN_LnStsChngMsk_START         (8)
#define SOC_OTG_GPWRDN_LnStsChngMsk_END           (8)
#define SOC_OTG_GPWRDN_ResetDetected_START        (9)
#define SOC_OTG_GPWRDN_ResetDetected_END          (9)
#define SOC_OTG_GPWRDN_ResetDetMsk_START          (10)
#define SOC_OTG_GPWRDN_ResetDetMsk_END            (10)
#define SOC_OTG_GPWRDN_DisconnectDetect_START     (11)
#define SOC_OTG_GPWRDN_DisconnectDetect_END       (11)
#define SOC_OTG_GPWRDN_DisconnectDetectMsk_START  (12)
#define SOC_OTG_GPWRDN_DisconnectDetectMsk_END    (12)
#define SOC_OTG_GPWRDN_ConnectDet_START           (13)
#define SOC_OTG_GPWRDN_ConnectDet_END             (13)
#define SOC_OTG_GPWRDN_ConnDetMsk_START           (14)
#define SOC_OTG_GPWRDN_ConnDetMsk_END             (14)
#define SOC_OTG_GPWRDN_SRPDetect_START            (15)
#define SOC_OTG_GPWRDN_SRPDetect_END              (15)
#define SOC_OTG_GPWRDN_SRPDetectMsk_START         (16)
#define SOC_OTG_GPWRDN_SRPDetectMsk_END           (16)
#define SOC_OTG_GPWRDN_StsChngInt_START           (17)
#define SOC_OTG_GPWRDN_StsChngInt_END             (17)
#define SOC_OTG_GPWRDN_StsChngMsk_START           (18)
#define SOC_OTG_GPWRDN_StsChngMsk_END             (18)
#define SOC_OTG_GPWRDN_LineState_START            (19)
#define SOC_OTG_GPWRDN_LineState_END              (20)
#define SOC_OTG_GPWRDN_IDDIG_START                (21)
#define SOC_OTG_GPWRDN_IDDIG_END                  (21)
#define SOC_OTG_GPWRDN_BSessVld_START             (22)
#define SOC_OTG_GPWRDN_BSessVld_END               (22)
#define SOC_OTG_GPWRDN_ADPInt_START               (23)
#define SOC_OTG_GPWRDN_ADPInt_END                 (23)
#define SOC_OTG_GPWRDN_MultValIdBc_START          (24)
#define SOC_OTG_GPWRDN_MultValIdBc_END            (28)


/*****************************************************************************
 �ṹ��    : SOC_OTG_GDFIFOCFG_UNION
 �ṹ˵��  : GDFIFOCFG �Ĵ����ṹ���塣��ַƫ����:0x005C����ֵ:0x0F801000�����:32
 �Ĵ���˵��: ��̬FIFO���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  GDFIFOCfg      : 16; /* bit[0-15] : �ڲ�RAM��ȣ���4�ֽ�Ϊ��λ�� */
        unsigned int  EPInfoBaseAddr : 16; /* bit[16-31]: �������ڲ�RAM��ļĴ�����ʼ��ַ����4�ֽ�Ϊ��λ��ע���ⲿ�ֵ�ַ�ռ䲻������FIFO�ռ䣬���߼�Ҳû���������� */
    } reg;
} SOC_OTG_GDFIFOCFG_UNION;
#endif
#define SOC_OTG_GDFIFOCFG_GDFIFOCfg_START       (0)
#define SOC_OTG_GDFIFOCFG_GDFIFOCfg_END         (15)
#define SOC_OTG_GDFIFOCFG_EPInfoBaseAddr_START  (16)
#define SOC_OTG_GDFIFOCFG_EPInfoBaseAddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_GADPCTL_UNION
 �ṹ˵��  : GADPCTL �Ĵ����ṹ���塣��ַƫ����:0x0060����ֵ:0x00000000�����:32
 �Ĵ���˵��: ADP���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PrbDschng    : 2;  /* bit[0-1]  : Probe�����ŵ�ʱ�䡣
                                                        00��4���룻
                                                        01��8���룻
                                                        10��16���룻
                                                        11��32���롣 */
        unsigned int  PrbDelta     : 2;  /* bit[2-3]  : RTIMʱ��̶ȡ�
                                                        00��1��ʱ�����ڣ�
                                                        01��2��ʱ�����ڣ�
                                                        10��3��ʱ�����ڣ�
                                                        11��4��ʱ�����ڡ� */
        unsigned int  PrbPer       : 2;  /* bit[4-5]  : Probe���ڡ�
                                                        00��0.625�뵽0.925�루����ֵ0.775�룩��
                                                        01��1.25�뵽1.85�루����ֵ1.55�룩��
                                                        10��1.9�뵽2.6�루����ֵ2.275�룩��
                                                        11��reserved�� */
        unsigned int  RTIM         : 11; /* bit[6-16] : VBUS��Vadp_sink������Vadp_prb��ʱ�䡣��PrbDelta��ʾ��32KHzʱ������Ϊ��λ�� */
        unsigned int  EnaPrb       : 1;  /* bit[17]   : AdpPrbʹ�ܡ�
                                                        0����ʹ�ܣ�
                                                        1��ʹ�ܡ� */
        unsigned int  EnaSns       : 1;  /* bit[18]   : AdpSnsʹ�ܡ�
                                                        0����ʹ�ܣ�
                                                        1��ʹ�ܡ� */
        unsigned int  ADPRes       : 1;  /* bit[19]   : ADP��λ���ơ�
                                                        0������λ��
                                                        1����λ�� */
        unsigned int  ADPEn        : 1;  /* bit[20]   : ADPʹ�ܡ�
                                                        0����ʹ�ܣ�
                                                        1��ʹ�ܡ� */
        unsigned int  AdpPrbInt    : 1;  /* bit[21]   : AdpPrb�жϡ���VBUS��ѹ����Vadpprb�������жϡ�
                                                        0�����жϣ�
                                                        1�����жϡ� */
        unsigned int  AdpSnsInt    : 1;  /* bit[22]   : AdpSns�жϡ���VBUS��ѹ����Vadpsns�������жϡ�
                                                        0�����жϣ�
                                                        1�����жϡ� */
        unsigned int  AdpTmoutInt  : 1;  /* bit[23]   : ADP��ʱ�жϡ�
                                                        0�����жϣ�
                                                        1�����жϡ� */
        unsigned int  AdpPrbIntMsk : 1;  /* bit[24]   : AdpPrb�ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  AdpSnsIntMsk : 1;  /* bit[25]   : AdpSns�ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  AdpTmoutMsk  : 1;  /* bit[26]   : ADP��ʱ�ж�����λ��
                                                        0�����Σ�
                                                        1�������Ρ� */
        unsigned int  AR           : 2;  /* bit[27-28]: ��д����
                                                        00��������Ч���������Զ����£�
                                                        01����������
                                                        10��д������
                                                        11�������� */
        unsigned int  reserved     : 3;  /* bit[29-31]: ������ */
    } reg;
} SOC_OTG_GADPCTL_UNION;
#endif
#define SOC_OTG_GADPCTL_PrbDschng_START     (0)
#define SOC_OTG_GADPCTL_PrbDschng_END       (1)
#define SOC_OTG_GADPCTL_PrbDelta_START      (2)
#define SOC_OTG_GADPCTL_PrbDelta_END        (3)
#define SOC_OTG_GADPCTL_PrbPer_START        (4)
#define SOC_OTG_GADPCTL_PrbPer_END          (5)
#define SOC_OTG_GADPCTL_RTIM_START          (6)
#define SOC_OTG_GADPCTL_RTIM_END            (16)
#define SOC_OTG_GADPCTL_EnaPrb_START        (17)
#define SOC_OTG_GADPCTL_EnaPrb_END          (17)
#define SOC_OTG_GADPCTL_EnaSns_START        (18)
#define SOC_OTG_GADPCTL_EnaSns_END          (18)
#define SOC_OTG_GADPCTL_ADPRes_START        (19)
#define SOC_OTG_GADPCTL_ADPRes_END          (19)
#define SOC_OTG_GADPCTL_ADPEn_START         (20)
#define SOC_OTG_GADPCTL_ADPEn_END           (20)
#define SOC_OTG_GADPCTL_AdpPrbInt_START     (21)
#define SOC_OTG_GADPCTL_AdpPrbInt_END       (21)
#define SOC_OTG_GADPCTL_AdpSnsInt_START     (22)
#define SOC_OTG_GADPCTL_AdpSnsInt_END       (22)
#define SOC_OTG_GADPCTL_AdpTmoutInt_START   (23)
#define SOC_OTG_GADPCTL_AdpTmoutInt_END     (23)
#define SOC_OTG_GADPCTL_AdpPrbIntMsk_START  (24)
#define SOC_OTG_GADPCTL_AdpPrbIntMsk_END    (24)
#define SOC_OTG_GADPCTL_AdpSnsIntMsk_START  (25)
#define SOC_OTG_GADPCTL_AdpSnsIntMsk_END    (25)
#define SOC_OTG_GADPCTL_AdpTmoutMsk_START   (26)
#define SOC_OTG_GADPCTL_AdpTmoutMsk_END     (26)
#define SOC_OTG_GADPCTL_AR_START            (27)
#define SOC_OTG_GADPCTL_AR_END              (28)


/*****************************************************************************
 �ṹ��    : SOC_OTG_HPTXFSIZ_UNION
 �ṹ˵��  : HPTXFSIZ �Ĵ����ṹ���塣��ַƫ����:0x0100����ֵ:0x00000000�����:32
 �Ĵ���˵��: Host���ڷ���FIFO���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PTxFStAddr : 16; /* bit[0-15] : Host���ڷ���FIFO��ʼ��ַ����4�ֽ�Ϊ��λ�� */
        unsigned int  PTxFSize   : 16; /* bit[16-31]: Host���ڷ���FIFO��ȣ���4�ֽ�Ϊ��λ�� */
    } reg;
} SOC_OTG_HPTXFSIZ_UNION;
#endif
#define SOC_OTG_HPTXFSIZ_PTxFStAddr_START  (0)
#define SOC_OTG_HPTXFSIZ_PTxFStAddr_END    (15)
#define SOC_OTG_HPTXFSIZ_PTxFSize_START    (16)
#define SOC_OTG_HPTXFSIZ_PTxFSize_END      (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPTXF1_UNION
 �ṹ˵��  : DIEPTXF1 �Ĵ����ṹ���塣��ַƫ����:0x0104����ֵ:0x10002000�����:32
 �Ĵ���˵��: Device IN�˵�1����FIFO���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN�˵㷢��FIFO��ʼ��ַ����4�ֽ�Ϊ��λ�� */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN�˵㷢��FIFO��ȣ���4�ֽ�Ϊ��λ�� */
    } reg;
} SOC_OTG_DIEPTXF1_UNION;
#endif
#define SOC_OTG_DIEPTXF1_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF1_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF1_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF1_INEPnTxFDep_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPTXF2_UNION
 �ṹ˵��  : DIEPTXF2 �Ĵ����ṹ���塣��ַƫ����:0x0108����ֵ:0x10003000�����:32
 �Ĵ���˵��: Device IN�˵�2����FIFO���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN�˵㷢��FIFO��ʼ��ַ����4�ֽ�Ϊ��λ�� */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN�˵㷢��FIFO��ȣ���4�ֽ�Ϊ��λ�� */
    } reg;
} SOC_OTG_DIEPTXF2_UNION;
#endif
#define SOC_OTG_DIEPTXF2_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF2_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF2_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF2_INEPnTxFDep_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPTXF3_UNION
 �ṹ˵��  : DIEPTXF3 �Ĵ����ṹ���塣��ַƫ����:0x010C����ֵ:0x10004000�����:32
 �Ĵ���˵��: Device IN�˵�3����FIFO���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN�˵㷢��FIFO��ʼ��ַ����4�ֽ�Ϊ��λ�� */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN�˵㷢��FIFO��ȣ���4�ֽ�Ϊ��λ�� */
    } reg;
} SOC_OTG_DIEPTXF3_UNION;
#endif
#define SOC_OTG_DIEPTXF3_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF3_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF3_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF3_INEPnTxFDep_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPTXF4_UNION
 �ṹ˵��  : DIEPTXF4 �Ĵ����ṹ���塣��ַƫ����:0x0110����ֵ:0x10005000�����:32
 �Ĵ���˵��: Device IN�˵�4����FIFO���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN�˵㷢��FIFO��ʼ��ַ����4�ֽ�Ϊ��λ�� */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN�˵㷢��FIFO��ȣ���4�ֽ�Ϊ��λ�� */
    } reg;
} SOC_OTG_DIEPTXF4_UNION;
#endif
#define SOC_OTG_DIEPTXF4_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF4_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF4_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF4_INEPnTxFDep_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPTXF5_UNION
 �ṹ˵��  : DIEPTXF5 �Ĵ����ṹ���塣��ַƫ����:0x0114����ֵ:0x10006000�����:32
 �Ĵ���˵��: Device IN�˵�5����FIFO���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN�˵㷢��FIFO��ʼ��ַ����4�ֽ�Ϊ��λ�� */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN�˵㷢��FIFO��ȣ���4�ֽ�Ϊ��λ�� */
    } reg;
} SOC_OTG_DIEPTXF5_UNION;
#endif
#define SOC_OTG_DIEPTXF5_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF5_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF5_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF5_INEPnTxFDep_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPTXF6_UNION
 �ṹ˵��  : DIEPTXF6 �Ĵ����ṹ���塣��ַƫ����:0x0118����ֵ:0x10007000�����:32
 �Ĵ���˵��: Device IN�˵�6����FIFO���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN�˵㷢��FIFO��ʼ��ַ����4�ֽ�Ϊ��λ�� */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN�˵㷢��FIFO��ȣ���4�ֽ�Ϊ��λ�� */
    } reg;
} SOC_OTG_DIEPTXF6_UNION;
#endif
#define SOC_OTG_DIEPTXF6_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF6_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF6_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF6_INEPnTxFDep_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPTXF7_UNION
 �ṹ˵��  : DIEPTXF7 �Ĵ����ṹ���塣��ַƫ����:0x011C����ֵ:0x10008000�����:32
 �Ĵ���˵��: Device IN�˵�7����FIFO���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN�˵㷢��FIFO��ʼ��ַ����4�ֽ�Ϊ��λ�� */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN�˵㷢��FIFO��ȣ���4�ֽ�Ϊ��λ�� */
    } reg;
} SOC_OTG_DIEPTXF7_UNION;
#endif
#define SOC_OTG_DIEPTXF7_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF7_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF7_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF7_INEPnTxFDep_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPTXF8_UNION
 �ṹ˵��  : DIEPTXF8 �Ĵ����ṹ���塣��ַƫ����:0x0120����ֵ:0x10009000�����:32
 �Ĵ���˵��: Device IN�˵�8����FIFO���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN�˵㷢��FIFO��ʼ��ַ����4�ֽ�Ϊ��λ�� */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN�˵㷢��FIFO��ȣ���4�ֽ�Ϊ��λ�� */
    } reg;
} SOC_OTG_DIEPTXF8_UNION;
#endif
#define SOC_OTG_DIEPTXF8_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF8_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF8_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF8_INEPnTxFDep_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPTXF9_UNION
 �ṹ˵��  : DIEPTXF9 �Ĵ����ṹ���塣��ַƫ����:0x0124����ֵ:0x1000A000�����:32
 �Ĵ���˵��: Device IN�˵�9����FIFO���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN�˵㷢��FIFO��ʼ��ַ����4�ֽ�Ϊ��λ�� */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN�˵㷢��FIFO��ȣ���4�ֽ�Ϊ��λ�� */
    } reg;
} SOC_OTG_DIEPTXF9_UNION;
#endif
#define SOC_OTG_DIEPTXF9_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF9_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF9_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF9_INEPnTxFDep_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPTXF10_UNION
 �ṹ˵��  : DIEPTXF10 �Ĵ����ṹ���塣��ַƫ����:0x0128����ֵ:0x1000B000�����:32
 �Ĵ���˵��: Device IN�˵�10����FIFO���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN�˵㷢��FIFO��ʼ��ַ����4�ֽ�Ϊ��λ�� */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN�˵㷢��FIFO��ȣ���4�ֽ�Ϊ��λ�� */
    } reg;
} SOC_OTG_DIEPTXF10_UNION;
#endif
#define SOC_OTG_DIEPTXF10_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF10_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF10_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF10_INEPnTxFDep_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPTXF11_UNION
 �ṹ˵��  : DIEPTXF11 �Ĵ����ṹ���塣��ַƫ����:0x012C����ֵ:0x1000C000�����:32
 �Ĵ���˵��: Device IN�˵�11����FIFO���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN�˵㷢��FIFO��ʼ��ַ����4�ֽ�Ϊ��λ�� */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN�˵㷢��FIFO��ȣ���4�ֽ�Ϊ��λ�� */
    } reg;
} SOC_OTG_DIEPTXF11_UNION;
#endif
#define SOC_OTG_DIEPTXF11_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF11_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF11_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF11_INEPnTxFDep_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPTXF12_UNION
 �ṹ˵��  : DIEPTXF12 �Ĵ����ṹ���塣��ַƫ����:0x0130����ֵ:0x1000D000�����:32
 �Ĵ���˵��: Device IN�˵�12����FIFO���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN�˵㷢��FIFO��ʼ��ַ����4�ֽ�Ϊ��λ�� */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN�˵㷢��FIFO��ȣ���4�ֽ�Ϊ��λ�� */
    } reg;
} SOC_OTG_DIEPTXF12_UNION;
#endif
#define SOC_OTG_DIEPTXF12_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF12_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF12_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF12_INEPnTxFDep_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPTXF13_UNION
 �ṹ˵��  : DIEPTXF13 �Ĵ����ṹ���塣��ַƫ����:0x0134����ֵ:0x1000E000�����:32
 �Ĵ���˵��: Device IN�˵�13����FIFO���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN�˵㷢��FIFO��ʼ��ַ����4�ֽ�Ϊ��λ�� */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN�˵㷢��FIFO��ȣ���4�ֽ�Ϊ��λ�� */
    } reg;
} SOC_OTG_DIEPTXF13_UNION;
#endif
#define SOC_OTG_DIEPTXF13_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF13_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF13_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF13_INEPnTxFDep_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPTXF14_UNION
 �ṹ˵��  : DIEPTXF14 �Ĵ����ṹ���塣��ַƫ����:0x0138����ֵ:0x1000F000�����:32
 �Ĵ���˵��: Device IN�˵�14����FIFO���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN�˵㷢��FIFO��ʼ��ַ����4�ֽ�Ϊ��λ�� */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN�˵㷢��FIFO��ȣ���4�ֽ�Ϊ��λ�� */
    } reg;
} SOC_OTG_DIEPTXF14_UNION;
#endif
#define SOC_OTG_DIEPTXF14_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF14_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF14_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF14_INEPnTxFDep_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPTXF15_UNION
 �ṹ˵��  : DIEPTXF15 �Ĵ����ṹ���塣��ַƫ����:0x013C����ֵ:0x10000000�����:32
 �Ĵ���˵��: Device IN�˵�15����FIFO���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPnTxFStAddr : 16; /* bit[0-15] : IN�˵㷢��FIFO��ʼ��ַ����4�ֽ�Ϊ��λ�� */
        unsigned int  INEPnTxFDep    : 16; /* bit[16-31]: IN�˵㷢��FIFO��ȣ���4�ֽ�Ϊ��λ�� */
    } reg;
} SOC_OTG_DIEPTXF15_UNION;
#endif
#define SOC_OTG_DIEPTXF15_INEPnTxFStAddr_START  (0)
#define SOC_OTG_DIEPTXF15_INEPnTxFStAddr_END    (15)
#define SOC_OTG_DIEPTXF15_INEPnTxFDep_START     (16)
#define SOC_OTG_DIEPTXF15_INEPnTxFDep_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_HCFG_UNION
 �ṹ˵��  : HCFG �Ĵ����ṹ���塣��ַƫ����:0x0400����ֵ:0x00000200�����:32
 �Ĵ���˵��: Host���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  FSLSPclkSel : 2;  /* bit[0-1]  : FS/LS PHY�ӿ�ʱ��ѡ��
                                                       00��30/60MHz��
                                                       01��48MHz��
                                                       others��reserved�� */
        unsigned int  FSLSSupp    : 1;  /* bit[2]    : ��֧��FS��LSʹ�ܡ�
                                                       ����ö���ٶȡ���bitʹ�ܣ���ʹdevice֧��HS��������Ҳ��ö�ٳ�FS Host��
                                                       0����ʹ�ܣ�
                                                       1��ʹ�ܡ� */
        unsigned int  reserved_0  : 4;  /* bit[3-6]  : ������ */
        unsigned int  Ena32KHzS   : 1;  /* bit[7]    : ʹ��32KHz suspendģʽ����bit��������Ϊ0����֧��32KHz suspendģʽ��
                                                       0����ʹ�ܣ�
                                                       1��ʹ�ܡ� */
        unsigned int  ResValid    : 8;  /* bit[8-15] : Resume��Ч���ȡ�
                                                       ����HCFG[Ena32KHz]����Ϊ1��Ч�����������resume�źţ�����ResValid��ʱ��������Ϊresume��Ч�� */
        unsigned int  reserved_1  : 7;  /* bit[16-22]: ������ */
        unsigned int  DescDMA     : 1;  /* bit[23]   : ʹ��Scatter/Gather DMAģʽ��
                                                       0����ʹ�ܣ�
                                                       1��ʹ�ܡ� */
        unsigned int  FrListEn    : 2;  /* bit[24-25]: ֡�б��С������Scatter/Gather DMAģʽ��Ч��
                                                       00��8��
                                                       01��16��
                                                       10��32��
                                                       11��64�� */
        unsigned int  PerSchedEna : 1;  /* bit[26]   : ʹ�����ڴ��䡣����Scatter/Gather DMAģʽ��Ч��
                                                       0����ʹ�ܣ�
                                                       1��ʹ�ܡ� */
        unsigned int  resered     : 4;  /* bit[27-30]: ������ */
        unsigned int  ModeChTimEn : 1;  /* bit[31]   : ģʽ�ı����ʹ�ܡ�
                                                       ʹ��Host��������Resume�����ȴ�200��PHYʱ�����ڣ�Ȼ��opmode�źŸı�Ϊ00��
                                                       0���ȴ�200��PHYʱ�����ڻ��ߵȴ�linestate���SE0��
                                                       1���ȴ�linestate���SE0�� */
    } reg;
} SOC_OTG_HCFG_UNION;
#endif
#define SOC_OTG_HCFG_FSLSPclkSel_START  (0)
#define SOC_OTG_HCFG_FSLSPclkSel_END    (1)
#define SOC_OTG_HCFG_FSLSSupp_START     (2)
#define SOC_OTG_HCFG_FSLSSupp_END       (2)
#define SOC_OTG_HCFG_Ena32KHzS_START    (7)
#define SOC_OTG_HCFG_Ena32KHzS_END      (7)
#define SOC_OTG_HCFG_ResValid_START     (8)
#define SOC_OTG_HCFG_ResValid_END       (15)
#define SOC_OTG_HCFG_DescDMA_START      (23)
#define SOC_OTG_HCFG_DescDMA_END        (23)
#define SOC_OTG_HCFG_FrListEn_START     (24)
#define SOC_OTG_HCFG_FrListEn_END       (25)
#define SOC_OTG_HCFG_PerSchedEna_START  (26)
#define SOC_OTG_HCFG_PerSchedEna_END    (26)
#define SOC_OTG_HCFG_resered_START      (27)
#define SOC_OTG_HCFG_resered_END        (30)
#define SOC_OTG_HCFG_ModeChTimEn_START  (31)
#define SOC_OTG_HCFG_ModeChTimEn_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_HFIR_UNION
 �ṹ˵��  : HFIR �Ĵ����ṹ���塣��ַƫ����:0x0404����ֵ:0x0000EA60�����:32
 �Ĵ���˵��: Host֡����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  FrInt       : 16; /* bit[0-15] : ֡�������PHY�ӿ�ʱ������Ϊ��λ��Host���FrInt��ʱ�����ڷ���1��SOF������HS����Ҫ���õļ������Ϊ125us������FS/LS��Ҫ���õļ������Ϊ1ms���û������ڳ�ʼ��ʱ���á� */
        unsigned int  HFIRRldCtrl : 1;  /* bit[16]   : ���¼��ؼ��������������üĴ����ڳ�ʼ��ʱ���á�
                                                       0��FrInt�����������Զ����أ�
                                                       1��FrInt���������Զ����ء� */
        unsigned int  reserved    : 15; /* bit[17-31]: ������ */
    } reg;
} SOC_OTG_HFIR_UNION;
#endif
#define SOC_OTG_HFIR_FrInt_START        (0)
#define SOC_OTG_HFIR_FrInt_END          (15)
#define SOC_OTG_HFIR_HFIRRldCtrl_START  (16)
#define SOC_OTG_HFIR_HFIRRldCtrl_END    (16)


/*****************************************************************************
 �ṹ��    : SOC_OTG_HFNUM_UNION
 �ṹ˵��  : HFNUM �Ĵ����ṹ���塣��ַƫ����:0x0408����ֵ:0x00003FFF�����:32
 �Ĵ���˵��: Host֡��żĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  FrNum : 16; /* bit[0-15] : ֡��š� */
        unsigned int  FrRem : 16; /* bit[16-31]: ֡ʣ��ʱ�����������FrInt��ʼ��������һֱ��0���¿�ʼ������ */
    } reg;
} SOC_OTG_HFNUM_UNION;
#endif
#define SOC_OTG_HFNUM_FrNum_START  (0)
#define SOC_OTG_HFNUM_FrNum_END    (15)
#define SOC_OTG_HFNUM_FrRem_START  (16)
#define SOC_OTG_HFNUM_FrRem_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_HPTXSTS_UNION
 �ṹ˵��  : HPTXSTS �Ĵ����ṹ���塣��ַƫ����:0x0410����ֵ:0x00081000�����:32
 �Ĵ���˵��: Host���ڷ���FIFO�Ͷ���״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PTxSpcAvail  : 16; /* bit[0-15] : ���ڷ���FIFOʣ��ռ䣬��4�ֽ�Ϊ��λ�� */
        unsigned int  PTxQSpcAvail : 8;  /* bit[16-23]: ���ڷ����������ʣ��ռ䡣
                                                        ���ڷ�������������Ϊ8������ָʾ����������л����Ի��漸���������� */
        unsigned int  PTxQTop      : 8;  /* bit[24-31]: ���ڷ���������е�ǰ��������debug�� */
    } reg;
} SOC_OTG_HPTXSTS_UNION;
#endif
#define SOC_OTG_HPTXSTS_PTxSpcAvail_START   (0)
#define SOC_OTG_HPTXSTS_PTxSpcAvail_END     (15)
#define SOC_OTG_HPTXSTS_PTxQSpcAvail_START  (16)
#define SOC_OTG_HPTXSTS_PTxQSpcAvail_END    (23)
#define SOC_OTG_HPTXSTS_PTxQTop_START       (24)
#define SOC_OTG_HPTXSTS_PTxQTop_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_HAINT_UNION
 �ṹ˵��  : HAINT �Ĵ����ṹ���塣��ַƫ����:0x0414����ֵ:0x00000000�����:32
 �Ĵ���˵��: Host����ͨ���ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  HAINT    : 16; /* bit[0-15] : ͨ���ж�״̬��
                                                    Bit0��Ӧͨ��0��bit15��Ӧͨ��15��
                                                    0�����жϣ�
                                                    1�����жϡ� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_OTG_HAINT_UNION;
#endif
#define SOC_OTG_HAINT_HAINT_START     (0)
#define SOC_OTG_HAINT_HAINT_END       (15)


/*****************************************************************************
 �ṹ��    : SOC_OTG_HAINTMSK_UNION
 �ṹ˵��  : HAINTMSK �Ĵ����ṹ���塣��ַƫ����:0x0418����ֵ:0x00000000�����:32
 �Ĵ���˵��: Host����ͨ���ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  HAINTMsk : 16; /* bit[0-15] : ͨ���ж����Ρ�
                                                    Bit0��Ӧͨ��0��bit15��Ӧͨ��15��
                                                    0�����Ρ�
                                                    1�������Ρ� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_OTG_HAINTMSK_UNION;
#endif
#define SOC_OTG_HAINTMSK_HAINTMsk_START  (0)
#define SOC_OTG_HAINTMSK_HAINTMsk_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_OTG_HFLBAddr_UNION
 �ṹ˵��  : HFLBAddr �Ĵ����ṹ���塣��ַƫ����:0x041C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ֡�б����ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  HFLBAddr : 32; /* bit[0-31]: ֡�б����ַ����scatter/gather DMAģʽ��Ч�� */
    } reg;
} SOC_OTG_HFLBAddr_UNION;
#endif
#define SOC_OTG_HFLBAddr_HFLBAddr_START  (0)
#define SOC_OTG_HFLBAddr_HFLBAddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_HPRT_UNION
 �ṹ˵��  : HPRT �Ĵ����ṹ���塣��ַƫ����:0x0440����ֵ:0x00000000�����:32
 �Ĵ���˵��: Host�˿ڿ��ƺ�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PrtConnSts     : 1;  /* bit[0]    : �˿�����״̬��
                                                          0��û��devie���ӵ��˿ڣ�
                                                          1����device���ӵ��˿ڡ� */
        unsigned int  PrtConnDet     : 1;  /* bit[1]    : ��⵽�˿������жϡ��������д1�����bit��
                                                          0�����жϣ�
                                                          1�����жϡ� */
        unsigned int  PrtEna         : 1;  /* bit[2]    : �˿�ʹ�ܡ�
                                                          ��λ���֮�󣬶˿ڱ�������ʹ�ܡ��������Ͽ����ӻ���������������bit��
                                                          0����ʹ�ܣ�
                                                          1��ʹ�ܡ� */
        unsigned int  PrtEnChng      : 1;  /* bit[3]    : �˿�ʹ��״̬�仯��
                                                          0���ޱ仯��
                                                          1���б仯�� */
        unsigned int  PrtOvrCurrAct  : 1;  /* bit[4]    : �˿ڹ���״ָ̬ʾ��
                                                          0����������
                                                          1�������� */
        unsigned int  PrtOvrCurrChng : 1;  /* bit[5]    : ����״̬�仯��ָʾPrtOvrCurrAct״̬�����仯��
                                                          0���ޱ仯��
                                                          1���б仯�� */
        unsigned int  PrtRes         : 1;  /* bit[6]    : �˿�resume���ơ������ڶ˿ڷ���resume�źš�
                                                          0����resumne��
                                                          1��resume�� */
        unsigned int  PrtSusp        : 1;  /* bit[7]    : �˿�suspend���ơ����ƶ˿ڽ���suspend״̬��
                                                          0��������suspend״̬��
                                                          1������suspend״̬�� */
        unsigned int  PrtRst         : 1;  /* bit[8]    : �˿ڸ�λ���ơ�
                                                          ���ø�bit���������ڶ˿��Ϸ�����λ���С����������㸴λʱ��ĳ��ȣ����ڸ�λ���֮�������bit������HighSpeed�豸����λ���뱣��50ms������FullSpeed��LowSpeed�豸����λ���뱣��10ms��
                                                          0������λ��
                                                          1����λ�� */
        unsigned int  reserved_0     : 1;  /* bit[9]    : ������ */
        unsigned int  PrtLnSts       : 2;  /* bit[10-11]: USB����״̬��
                                                          bit[10]��D+���߼���ƽ��
                                                          bit[11]��D-���߼���ƽ�� */
        unsigned int  PrtPwr         : 1;  /* bit[12]   : �˿ڹ��Ŀ��ơ����ֹ���������£��������Զ������bit��
                                                          0���ضϵ�Դ��
                                                          1���򿪵�Դ�� */
        unsigned int  PrtTstCtl      : 4;  /* bit[13-16]: �˿ڲ���ģʽ���ơ�
                                                          0000������ģʽ��ʹ�ܣ�
                                                          0001��Test_Jģʽ��
                                                          0010��Test_Kģʽ��
                                                          0011��Test_SE0_NAKģʽ��
                                                          0100��Test_Packetģʽ��
                                                          0101��Test_Force_Enable��
                                                          others��reserved�� */
        unsigned int  PrtSpd         : 2;  /* bit[17-18]: �˿��ٶȡ�
                                                          ָʾ�����ڸö˿��ϵ�device�ٶȡ�
                                                          00��High Speed��
                                                          01��Full Speed��
                                                          10��Low Speed��
                                                          11��reserved�� */
        unsigned int  reserved_1     : 13; /* bit[19-31]: ������ */
    } reg;
} SOC_OTG_HPRT_UNION;
#endif
#define SOC_OTG_HPRT_PrtConnSts_START      (0)
#define SOC_OTG_HPRT_PrtConnSts_END        (0)
#define SOC_OTG_HPRT_PrtConnDet_START      (1)
#define SOC_OTG_HPRT_PrtConnDet_END        (1)
#define SOC_OTG_HPRT_PrtEna_START          (2)
#define SOC_OTG_HPRT_PrtEna_END            (2)
#define SOC_OTG_HPRT_PrtEnChng_START       (3)
#define SOC_OTG_HPRT_PrtEnChng_END         (3)
#define SOC_OTG_HPRT_PrtOvrCurrAct_START   (4)
#define SOC_OTG_HPRT_PrtOvrCurrAct_END     (4)
#define SOC_OTG_HPRT_PrtOvrCurrChng_START  (5)
#define SOC_OTG_HPRT_PrtOvrCurrChng_END    (5)
#define SOC_OTG_HPRT_PrtRes_START          (6)
#define SOC_OTG_HPRT_PrtRes_END            (6)
#define SOC_OTG_HPRT_PrtSusp_START         (7)
#define SOC_OTG_HPRT_PrtSusp_END           (7)
#define SOC_OTG_HPRT_PrtRst_START          (8)
#define SOC_OTG_HPRT_PrtRst_END            (8)
#define SOC_OTG_HPRT_PrtLnSts_START        (10)
#define SOC_OTG_HPRT_PrtLnSts_END          (11)
#define SOC_OTG_HPRT_PrtPwr_START          (12)
#define SOC_OTG_HPRT_PrtPwr_END            (12)
#define SOC_OTG_HPRT_PrtTstCtl_START       (13)
#define SOC_OTG_HPRT_PrtTstCtl_END         (16)
#define SOC_OTG_HPRT_PrtSpd_START          (17)
#define SOC_OTG_HPRT_PrtSpd_END            (18)


/*****************************************************************************
 �ṹ��    : SOC_OTG_HCCHARp_UNION
 �ṹ˵��  : HCCHARp �Ĵ����ṹ���塣��ַƫ����:0x0500+0x20*(p)����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��p���ԼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MPS      : 11; /* bit[0-10] : �����������ֽ�Ϊ��λ�� */
        unsigned int  EPNum    : 4;  /* bit[11-14]: �˵�š� */
        unsigned int  EPDir    : 1;  /* bit[15]   : �˵㷽��
                                                    0��OUT��
                                                    1��IN�� */
        unsigned int  reserved : 1;  /* bit[16]   : ������ */
        unsigned int  LSpdDev  : 1;  /* bit[17]   : LowSpeed�豸ָʾ��
                                                    ������ã�ָʾ��ͨ����LowSpeed�豸ͨ�š�
                                                    0������LowSpeed�豸��
                                                    1����LowSpeed�豸�� */
        unsigned int  EPType   : 2;  /* bit[18-19]: �˵����͡�
                                                    00��control��
                                                    01��isochronous��
                                                    10��bulk��
                                                    11��interrupt�� */
        unsigned int  MC_EC    : 2;  /* bit[20-21]: ��split����ʹ�ܣ��������ڴ��䣬����ÿ��΢֡��������������ڷ����ڴ��䣬�����ڲ�DMA�����ٲ�֮ǰ��ͨ������İ�������
                                                    00��������
                                                    01��1��
                                                    10��2��
                                                    11��3��
                                                    ���������������Ϊ2'b01�� */
        unsigned int  DevAddr  : 7;  /* bit[22-28]: Device��ַ�� */
        unsigned int  OddFrm   : 1;  /* bit[29]   : ��ż֡���ơ�
                                                    ������ø�bit��ָʾHost������֡����ż��֡�������ڴ��䡣
                                                    0��ż��֡��
                                                    1������֡�� */
        unsigned int  ChDis    : 1;  /* bit[30]   : ͨ����ʹ�ܡ�
                                                    ������ø�bitֹͣ���ͻ��߽������ݡ� */
        unsigned int  ChEna    : 1;  /* bit[31]   : ͨ��ʹ�ܡ�
                                                    ��Scatter/Gather DMAʹ��ʱ��
                                                    0��ָʾ��������û��׼���ã�
                                                    1��ָʾ������������buffer׼���ã�ͨ�����Զ�ȡ��������
                                                    ��Scatter/Gather DMA��ʹ��ʱ��
                                                    0��ͨ����ʹ�ܣ�
                                                    1��ͨ��ʹ�ܡ� */
    } reg;
} SOC_OTG_HCCHARp_UNION;
#endif
#define SOC_OTG_HCCHARp_MPS_START       (0)
#define SOC_OTG_HCCHARp_MPS_END         (10)
#define SOC_OTG_HCCHARp_EPNum_START     (11)
#define SOC_OTG_HCCHARp_EPNum_END       (14)
#define SOC_OTG_HCCHARp_EPDir_START     (15)
#define SOC_OTG_HCCHARp_EPDir_END       (15)
#define SOC_OTG_HCCHARp_LSpdDev_START   (17)
#define SOC_OTG_HCCHARp_LSpdDev_END     (17)
#define SOC_OTG_HCCHARp_EPType_START    (18)
#define SOC_OTG_HCCHARp_EPType_END      (19)
#define SOC_OTG_HCCHARp_MC_EC_START     (20)
#define SOC_OTG_HCCHARp_MC_EC_END       (21)
#define SOC_OTG_HCCHARp_DevAddr_START   (22)
#define SOC_OTG_HCCHARp_DevAddr_END     (28)
#define SOC_OTG_HCCHARp_OddFrm_START    (29)
#define SOC_OTG_HCCHARp_OddFrm_END      (29)
#define SOC_OTG_HCCHARp_ChDis_START     (30)
#define SOC_OTG_HCCHARp_ChDis_END       (30)
#define SOC_OTG_HCCHARp_ChEna_START     (31)
#define SOC_OTG_HCCHARp_ChEna_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_HCSPLTp_UNION
 �ṹ˵��  : HCSPLTp �Ĵ����ṹ���塣��ַƫ����:0x0504+(p)*0x20����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��p Split���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  PrtAddr  : 7;  /* bit[0-6]  : �˿ڵ�ַ�� */
        unsigned int  HubAddr  : 7;  /* bit[7-13] : Hub��ַ�� */
        unsigned int  XactPos  : 2;  /* bit[14-15]: ����λ�á�
                                                    ����OUT�����Ƿ���all��first��middle����last payload��
                                                    11��All���������е�payload��С�ڻ����188�ֽڣ���
                                                    10��Begin������First payload������188�ֽڣ���
                                                    01��End������last payload������188�ֽڣ���
                                                    00��Mid������middle payload������188�ֽڣ��� */
        unsigned int  CompSplt : 1;  /* bit[16]   : Split��ɲ�������
                                                    ������ã��������������split��ɴ��䡣
                                                    0��������
                                                    1�������� */
        unsigned int  reserved : 14; /* bit[17-30]: ������ */
        unsigned int  SpltEna  : 1;  /* bit[31]   : Splitʹ�ܡ�
                                                    ʹ�ܸ�ͨ������split���䡣
                                                    0����ʹ�ܣ�
                                                    1��ʹ�ܡ� */
    } reg;
} SOC_OTG_HCSPLTp_UNION;
#endif
#define SOC_OTG_HCSPLTp_PrtAddr_START   (0)
#define SOC_OTG_HCSPLTp_PrtAddr_END     (6)
#define SOC_OTG_HCSPLTp_HubAddr_START   (7)
#define SOC_OTG_HCSPLTp_HubAddr_END     (13)
#define SOC_OTG_HCSPLTp_XactPos_START   (14)
#define SOC_OTG_HCSPLTp_XactPos_END     (15)
#define SOC_OTG_HCSPLTp_CompSplt_START  (16)
#define SOC_OTG_HCSPLTp_CompSplt_END    (16)
#define SOC_OTG_HCSPLTp_SpltEna_START   (31)
#define SOC_OTG_HCSPLTp_SpltEna_END     (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_HCINTp_UNION
 �ṹ˵��  : HCINTp �Ĵ����ṹ���塣��ַƫ����:0x0508+(p)*0x20����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��p�ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferCompl         : 1;  /* bit[0]    : ��������жϡ�
                                                             ����scatter/gather DMAģʽ��ָʾ������IOC��־��Ч����������
                                                             ���ڷ�scatter/gather DMAģʽ��ָʾ��������������
                                                             0�����жϣ�
                                                             1�����жϡ� */
        unsigned int  ChHlted           : 1;  /* bit[1]    : ͨ��ֹͣ�жϡ�
                                                             ���ڷ�scatter/gather DMAģʽ��ָʾ�����쳣������
                                                             ����scatter/gather DMAģʽ��ָʾͨ����������ԭ���������������EOL��־��Ч��AHB���ߴ�����֤����������������ͨ����ʹ�ܣ�babble��stall��Ӧ��
                                                             0�����жϣ�
                                                             1�����жϡ� */
        unsigned int  AHBErr            : 1;  /* bit[2]    : AHB���ߴ����жϡ�
                                                             0�����жϣ�
                                                             1�����жϡ� */
        unsigned int  STALL             : 1;  /* bit[3]    : ���յ�STALL��Ӧ�жϡ�
                                                             ����scatter/gather DMAģʽ�����������θ��жϡ�
                                                             0�����жϣ�
                                                             1�����жϡ� */
        unsigned int  NAK               : 1;  /* bit[4]    : ���յ�NAK��Ӧ�жϡ�
                                                             ����scatter/gather DMAģʽ�����������θ��жϡ�
                                                             0�����жϣ�
                                                             1�����жϡ� */
        unsigned int  ACK               : 1;  /* bit[5]    : ���ջ��߷���ACK��Ӧ�жϡ�
                                                             ����scatter/gather DMAģʽ�����������θ��жϡ�
                                                             0�����жϣ�
                                                             1�����жϡ� */
        unsigned int  NYET              : 1;  /* bit[6]    : ���յ�NYET��Ӧ�жϡ�
                                                             ����scatter/gather DMAģʽ�����������θ��жϡ�
                                                             0�����жϣ�
                                                             1�����жϡ� */
        unsigned int  XactErr           : 1;  /* bit[7]    : ��������жϡ�
                                                             ָʾ�������¼��ִ������֮һ��
                                                             CRCУ����󣬳�ʱ��λ��������ٵ�EOP��
                                                             ����scatter/gather DMAģʽ�����������θ��жϡ�
                                                             0�����жϣ�
                                                             1�����жϡ� */
        unsigned int  BblErr            : 1;  /* bit[8]    : Babble�����жϡ�
                                                             ����scatter/gather DMAģʽ�����������θ��жϡ�
                                                             0�����жϣ�
                                                             1�����жϡ� */
        unsigned int  FrmOvrun          : 1;  /* bit[9]    : ֡������ת�жϡ�
                                                             ����scatter/gather DMAģʽ�����������θ��жϡ�
                                                             0�����жϣ�
                                                             1�����жϡ� */
        unsigned int  DataTglErr        : 1;  /* bit[10]   : ����PID��ת�����жϡ�
                                                             ����scatter/gather DMAģʽ�����������θ��жϡ�
                                                             0�����жϣ�
                                                             1�����жϡ� */
        unsigned int  BNAIntr           : 1;  /* bit[11]   : buffer��Ч�жϡ�
                                                             ��scatter/gather DMAģʽ��Ч��
                                                             0�����жϣ�
                                                             1�����жϡ� */
        unsigned int  XCS_XACT_ERR      : 1;  /* bit[12]   : ���ص���������жϡ�
                                                             ��scatter/gather DMAģʽ��Ч��ָʾ����3������������
                                                             0�����жϣ�
                                                             1�����жϡ� */
        unsigned int  DESC_LST_ROLLIntr : 1;  /* bit[13]   : ��������ת�жϡ�
                                                             ��scatter/gather DMAģʽ��Ч��
                                                             0�����жϣ�
                                                             1�����жϡ� */
        unsigned int  reserved          : 18; /* bit[14-31]: ������ */
    } reg;
} SOC_OTG_HCINTp_UNION;
#endif
#define SOC_OTG_HCINTp_XferCompl_START          (0)
#define SOC_OTG_HCINTp_XferCompl_END            (0)
#define SOC_OTG_HCINTp_ChHlted_START            (1)
#define SOC_OTG_HCINTp_ChHlted_END              (1)
#define SOC_OTG_HCINTp_AHBErr_START             (2)
#define SOC_OTG_HCINTp_AHBErr_END               (2)
#define SOC_OTG_HCINTp_STALL_START              (3)
#define SOC_OTG_HCINTp_STALL_END                (3)
#define SOC_OTG_HCINTp_NAK_START                (4)
#define SOC_OTG_HCINTp_NAK_END                  (4)
#define SOC_OTG_HCINTp_ACK_START                (5)
#define SOC_OTG_HCINTp_ACK_END                  (5)
#define SOC_OTG_HCINTp_NYET_START               (6)
#define SOC_OTG_HCINTp_NYET_END                 (6)
#define SOC_OTG_HCINTp_XactErr_START            (7)
#define SOC_OTG_HCINTp_XactErr_END              (7)
#define SOC_OTG_HCINTp_BblErr_START             (8)
#define SOC_OTG_HCINTp_BblErr_END               (8)
#define SOC_OTG_HCINTp_FrmOvrun_START           (9)
#define SOC_OTG_HCINTp_FrmOvrun_END             (9)
#define SOC_OTG_HCINTp_DataTglErr_START         (10)
#define SOC_OTG_HCINTp_DataTglErr_END           (10)
#define SOC_OTG_HCINTp_BNAIntr_START            (11)
#define SOC_OTG_HCINTp_BNAIntr_END              (11)
#define SOC_OTG_HCINTp_XCS_XACT_ERR_START       (12)
#define SOC_OTG_HCINTp_XCS_XACT_ERR_END         (12)
#define SOC_OTG_HCINTp_DESC_LST_ROLLIntr_START  (13)
#define SOC_OTG_HCINTp_DESC_LST_ROLLIntr_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_OTG_HCINTMSKp_UNION
 �ṹ˵��  : HCINTMSKp �Ĵ����ṹ���塣��ַƫ����:0x050C+(p)*0x20����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��p�ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferCompl            : 1;  /* bit[0]    : ��������ж�����λ��
                                                                0�����Σ�
                                                                1�������Ρ� */
        unsigned int  ChHlted              : 1;  /* bit[1]    : ͨ��ֹͣ�ж�����λ��
                                                                0�����Σ�
                                                                1�������Ρ� */
        unsigned int  AHBErr               : 1;  /* bit[2]    : AHB���ߴ����ж�����λ��
                                                                0�����Σ�
                                                                1�������Ρ� */
        unsigned int  STALL                : 1;  /* bit[3]    : ���յ�STALL��Ӧ�ж�����λ��
                                                                0�����Σ�
                                                                1�������Ρ� */
        unsigned int  NAK                  : 1;  /* bit[4]    : ���յ�NAK��Ӧ�ж�����λ��
                                                                0�����Σ�
                                                                1�������Ρ� */
        unsigned int  ACK                  : 1;  /* bit[5]    : ���ջ��߷���ACK��Ӧ�ж�����λ��
                                                                0�����Σ�
                                                                1�������Ρ� */
        unsigned int  NYET                 : 1;  /* bit[6]    : ���յ�NYET��Ӧ�ж�����λ��
                                                                0�����Σ�
                                                                1�������Ρ� */
        unsigned int  XactErr              : 1;  /* bit[7]    : ��������ж�����λ��
                                                                0�����Σ�
                                                                1�������Ρ� */
        unsigned int  BblErr               : 1;  /* bit[8]    : Babble�����ж�����λ��
                                                                0�����Σ�
                                                                1�������Ρ� */
        unsigned int  FrmOvrunMsk          : 1;  /* bit[9]    : ֡������ת�ж�����λ��
                                                                0�����Σ�
                                                                1�������Ρ� */
        unsigned int  DataTglErrMsk        : 1;  /* bit[10]   : ����PID��ת�����ж�����λ��
                                                                0�����Σ�
                                                                1�������Ρ� */
        unsigned int  BNAIntrMsk           : 1;  /* bit[11]   : buffer��Ч�ж�����λ��
                                                                0�����Σ�
                                                                1�������Ρ� */
        unsigned int  reserved_0           : 1;  /* bit[12]   : ������ */
        unsigned int  DESC_LST_ROLLIntrMsk : 1;  /* bit[13]   : ��������ת�ж�����λ��
                                                                0�����Σ�
                                                                1�������Ρ� */
        unsigned int  reserved_1           : 18; /* bit[14-31]: ������ */
    } reg;
} SOC_OTG_HCINTMSKp_UNION;
#endif
#define SOC_OTG_HCINTMSKp_XferCompl_START             (0)
#define SOC_OTG_HCINTMSKp_XferCompl_END               (0)
#define SOC_OTG_HCINTMSKp_ChHlted_START               (1)
#define SOC_OTG_HCINTMSKp_ChHlted_END                 (1)
#define SOC_OTG_HCINTMSKp_AHBErr_START                (2)
#define SOC_OTG_HCINTMSKp_AHBErr_END                  (2)
#define SOC_OTG_HCINTMSKp_STALL_START                 (3)
#define SOC_OTG_HCINTMSKp_STALL_END                   (3)
#define SOC_OTG_HCINTMSKp_NAK_START                   (4)
#define SOC_OTG_HCINTMSKp_NAK_END                     (4)
#define SOC_OTG_HCINTMSKp_ACK_START                   (5)
#define SOC_OTG_HCINTMSKp_ACK_END                     (5)
#define SOC_OTG_HCINTMSKp_NYET_START                  (6)
#define SOC_OTG_HCINTMSKp_NYET_END                    (6)
#define SOC_OTG_HCINTMSKp_XactErr_START               (7)
#define SOC_OTG_HCINTMSKp_XactErr_END                 (7)
#define SOC_OTG_HCINTMSKp_BblErr_START                (8)
#define SOC_OTG_HCINTMSKp_BblErr_END                  (8)
#define SOC_OTG_HCINTMSKp_FrmOvrunMsk_START           (9)
#define SOC_OTG_HCINTMSKp_FrmOvrunMsk_END             (9)
#define SOC_OTG_HCINTMSKp_DataTglErrMsk_START         (10)
#define SOC_OTG_HCINTMSKp_DataTglErrMsk_END           (10)
#define SOC_OTG_HCINTMSKp_BNAIntrMsk_START            (11)
#define SOC_OTG_HCINTMSKp_BNAIntrMsk_END              (11)
#define SOC_OTG_HCINTMSKp_DESC_LST_ROLLIntrMsk_START  (13)
#define SOC_OTG_HCINTMSKp_DESC_LST_ROLLIntrMsk_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_OTG_HCTSIZp_UNION
 �ṹ˵��  : HCTSIZp �Ĵ����ṹ���塣��ַƫ����:0x0510+(p)*0x20����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��p���䳤�ȼĴ�������scatter / gather DMAģʽ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SCHED_INFO : 8;  /* bit[0-7]  : ������Ϣ��
                                                      �������ڴ�����Ч��ÿbitָʾ��Ӧ��΢֡���ȿ��ơ�Bit[0]��Ӧ��1��΢֡��bit[7]��Ӧ��8��΢֡��
                                                      8'b11111111ָʾ�ڸ�֡�ڣ���ͨ��ÿ��΢֡����һ�Σ�������Ӧ�����ư���8'b10101010ָʾ��һ��΢֡����һ�Ρ� */
        unsigned int  NTD        : 8;  /* bit[8-15] : ����scatter/gather DMAģʽ��ָʾ������������ */
        unsigned int  reserved   : 13; /* bit[16-28]: ������ */
        unsigned int  PID        : 2;  /* bit[29-30]: PID���á�
                                                      ������ʼ�����PID��������ά������������PID��
                                                      00��DATA0��
                                                      01��DATA2��
                                                      10��DATA1��
                                                      11��MDATA�� */
        unsigned int  DoPng      : 1;  /* bit[31]   : PING�������á�
                                                      ��Bit����OUT������Ч�����ø�bit��host����Э�����PING������
                                                      ��IN�������ø�bit���ᵼ��ͨ����ʹ�ܡ� */
    } reg;
} SOC_OTG_HCTSIZp_UNION;
#endif
#define SOC_OTG_HCTSIZp_SCHED_INFO_START  (0)
#define SOC_OTG_HCTSIZp_SCHED_INFO_END    (7)
#define SOC_OTG_HCTSIZp_NTD_START         (8)
#define SOC_OTG_HCTSIZp_NTD_END           (15)
#define SOC_OTG_HCTSIZp_PID_START         (29)
#define SOC_OTG_HCTSIZp_PID_END           (30)
#define SOC_OTG_HCTSIZp_DoPng_START       (31)
#define SOC_OTG_HCTSIZp_DoPng_END         (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_HCTSIZp_non_sg_UNION
 �ṹ˵��  : HCTSIZp_non_sg �Ĵ����ṹ���塣��ַƫ����:0x0510+(p)*0x20����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��p���䳤�ȼĴ���������scatter / gather DMAģʽ��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferSize : 19; /* bit[0-18] : �����С�����ֽ�Ϊ��λ��
                                                    ����OUT���䣬��ʾHost����δ�����Ҫ������ֽ�����
                                                    ����IN���䣬��ʾ���������ʣ����ֽ����������Ҫ����������Ϊ��󱣻��������������� */
        unsigned int  PktCnt   : 10; /* bit[19-28]: ���������á� */
        unsigned int  PID      : 2;  /* bit[29-30]: PID���á�
                                                    ������ʼ�����PID��������ά������������PID��
                                                    00��DATA0��
                                                    01��DATA2��
                                                    10��DATA1��
                                                    11��MDATA���ǿ��ƶ˵㣩/setup�����ƶ˵㣩�� */
        unsigned int  DoPng    : 1;  /* bit[31]   : PING�������á�
                                                    ��Bit����OUT������Ч�����ø�bit��host����Э�����PING������
                                                    ��IN�������ø�bit���ᵼ��ͨ����ʹ�ܡ� */
    } reg;
} SOC_OTG_HCTSIZp_non_sg_UNION;
#endif
#define SOC_OTG_HCTSIZp_non_sg_XferSize_START  (0)
#define SOC_OTG_HCTSIZp_non_sg_XferSize_END    (18)
#define SOC_OTG_HCTSIZp_non_sg_PktCnt_START    (19)
#define SOC_OTG_HCTSIZp_non_sg_PktCnt_END      (28)
#define SOC_OTG_HCTSIZp_non_sg_PID_START       (29)
#define SOC_OTG_HCTSIZp_non_sg_PID_END         (30)
#define SOC_OTG_HCTSIZp_non_sg_DoPng_START     (31)
#define SOC_OTG_HCTSIZp_non_sg_DoPng_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_HCDMAp_UNION
 �ṹ˵��  : HCDMAp �Ĵ����ṹ���塣��ַƫ����:0x0514+(p)*0x20����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��p DMA��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DMAAddr : 32; /* bit[0-31]: DMA��ʼ��ַ�� */
    } reg;
} SOC_OTG_HCDMAp_UNION;
#endif
#define SOC_OTG_HCDMAp_DMAAddr_START  (0)
#define SOC_OTG_HCDMAp_DMAAddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_HCDMABp_UNION
 �ṹ˵��  : HCDMABp �Ĵ����ṹ���塣��ַƫ����:0x051C+(p)*0x20����ֵ:0x00000000�����:32
 �Ĵ���˵��: ͨ��p DMA buffer��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  HCDMA : 32; /* bit[0-31]: ��ǰbuffer��ַ����scatter/gather DMAģʽ��Ч�� */
    } reg;
} SOC_OTG_HCDMABp_UNION;
#endif
#define SOC_OTG_HCDMABp_HCDMA_START  (0)
#define SOC_OTG_HCDMABp_HCDMA_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DCFG_UNION
 �ṹ˵��  : DCFG �Ĵ����ṹ���塣��ַƫ����:0x0800����ֵ:0x08200000�����:32
 �Ĵ���˵��: device���üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DevSpd       : 2;  /* bit[0-1]  : Device�ٶ�ģʽ���á�
                                                        00��High-speed��
                                                        01��Full-speed��
                                                        others��reserved�� */
        unsigned int  NZStsOUTHShk : 1;  /* bit[2]    : ��0���ȵ�OUT���ֲ���ѡ���ڿ��ƴ����״̬�׶Σ����յ���0���ȵ����ݰ�ʱ����Ҫ����1�����ְ������ø�bitѡ���ͳ�ʲô���ְ���
                                                        0�����յ������ݰ��͸��������������Ӧ�˵���ƼĴ�����NAK��STALLλ�ͳ����ְ���
                                                        1���ͳ�STALL���ְ����������յ������ݰ��� */
        unsigned int  reserved_0   : 1;  /* bit[3]    : ������ */
        unsigned int  DevAddr      : 7;  /* bit[4-10] : device��ַ��ÿ���յ�SetAddr�����������뽫device��ַд����� */
        unsigned int  PerFrInt     : 2;  /* bit[11-12]: ����֡�������1��΢֡�ڣ�������֡����ﵽ�����ֵ���ϱ�����֡�����жϡ�
                                                        00��΢֡���ȵ�80����
                                                        01��΢֡���ȵ�85����
                                                        10��΢֡���ȵ�90����
                                                        11��΢֡���ȵ�95���� */
        unsigned int  EnDevOutNak  : 1;  /* bit[13]   : Device OUT NAKʹ��
                                                        0��Bulk OUT��ɺ󲻷���NAK
                                                        1��Bulk OUT��ɺ���NAK */
        unsigned int  reserved_1   : 4;  /* bit[14-17]: ������ */
        unsigned int  EpMisCnt     : 5;  /* bit[18-22]: IN�˵�Mismatch���� */
        unsigned int  DescDMA      : 1;  /* bit[23]   : Scatter/Gather DMAʹ�ܡ�
                                                        0����ʹ�ܣ�
                                                        1��ʹ�ܡ� */
        unsigned int  PerSchIntvl  : 2;  /* bit[24-25]: ���ڵ��ȼ��������DMA�������������IN�˵����ݵ�ʱ�䡣��������ڶ˵㱻���DMA�������������õ�ʱ�����ڰ��Ʒ�����IN�˵����ݣ�����DMAΪ�����ڶ˵���񡣸������õ�ʱ��֮��DMA��ʼ���Ʒ����ڶ˵����ݡ�
                                                        00��΢֡���ȵ�25%��
                                                        01��΢֡���ȵ�50%��
                                                        10��΢֡���ȵ�75%��
                                                        11�������� */
        unsigned int  reserved_2   : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_OTG_DCFG_UNION;
#endif
#define SOC_OTG_DCFG_DevSpd_START        (0)
#define SOC_OTG_DCFG_DevSpd_END          (1)
#define SOC_OTG_DCFG_NZStsOUTHShk_START  (2)
#define SOC_OTG_DCFG_NZStsOUTHShk_END    (2)
#define SOC_OTG_DCFG_DevAddr_START       (4)
#define SOC_OTG_DCFG_DevAddr_END         (10)
#define SOC_OTG_DCFG_PerFrInt_START      (11)
#define SOC_OTG_DCFG_PerFrInt_END        (12)
#define SOC_OTG_DCFG_EnDevOutNak_START   (13)
#define SOC_OTG_DCFG_EnDevOutNak_END     (13)
#define SOC_OTG_DCFG_EpMisCnt_START      (18)
#define SOC_OTG_DCFG_EpMisCnt_END        (22)
#define SOC_OTG_DCFG_DescDMA_START       (23)
#define SOC_OTG_DCFG_DescDMA_END         (23)
#define SOC_OTG_DCFG_PerSchIntvl_START   (24)
#define SOC_OTG_DCFG_PerSchIntvl_END     (25)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DCTL_UNION
 �ṹ˵��  : DCTL �Ĵ����ṹ���塣��ַƫ����:0x0804����ֵ:0x00000002�����:32
 �Ĵ���˵��: device���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  RmtWkUpSig          : 1;  /* bit[0]    : Զ�̻��ѿ��ơ�
                                                               ���ø�bit��������Զ�̻���host�����ͨ�����ø�bit��ʹdevice�˳�suspend״̬������Э�飬������������ø�bit֮��1��15ms�������bit��
                                                               ��LPMʹ����device����L1(sleep)״̬�����ͨ�����ø�bit����host����ʹdevice�˳�L1״̬��Ӳ����50us֮���Զ������bit��
                                                               0��������Զ�̻��Ѳ�����
                                                               1������Զ�̻��Ѳ����� */
        unsigned int  SftDiscon           : 1;  /* bit[1]    : ����Ͽ����ӿ��ơ�
                                                               0������������
                                                               1������������UTMI+�ӿڵ�opmode�ź�Ϊ2'b01����USB host�˲���device�Ͽ������¼��� */
        unsigned int  GNPINNakSts         : 1;  /* bit[2]    : ȫ�ַ�����IN����NAK״̬��
                                                               0�����ݷ���FIFO�����ݷ������ְ���
                                                               1������NAK�� */
        unsigned int  GOUTNakSts          : 1;  /* bit[3]    : ȫ�ַ�����OUT����NAK״̬��
                                                               0�����ְ��Ѿ����ͣ�
                                                               1������NAK�������Խ��յ������ݡ� */
        unsigned int  TstCtl              : 3;  /* bit[4-6]  : ����ģʽ���ơ�
                                                               000������ģʽ��ʹ�ܣ�
                                                               001������Jģʽ��
                                                               010������Kģʽ��
                                                               011������SE0_NAKģʽ��
                                                               100�����԰�ģʽ��
                                                               101������Force_Enableģʽ��
                                                               others�������� */
        unsigned int  SGNPInNak           : 1;  /* bit[7]    : ȫ�ַ�����IN����NAK���á�����Ը�bitд��1����device�����еķ�����IN������ӦNAK�����������GINTSTS[GINNakEff]�����������ø�bit��
                                                               0��������NAK��
                                                               1������NAK�� */
        unsigned int  CGNPInNak           : 1;  /* bit[8]    : ���ȫ�ַ�����IN����NAK���á��Ը�bit��д��1�����ȫ��IN NAK��
                                                               0���������
                                                               1������� */
        unsigned int  SGOUTNak            : 1;  /* bit[9]    : ȫ�ַ�����OUT����NAK���á�����Ը�bitд��1����device�����еķ�����OUT������ӦNAK�����������GINTSTS[GOUTNakEff]�����������ø�bit��
                                                               0��������NAK��
                                                               1������NAK�� */
        unsigned int  CGOUTNak            : 1;  /* bit[10]   : ���ȫ�ַ�����IN����NAK���á��Ը�bit��д��1�����ȫ��OUT NAK��
                                                               0���������
                                                               1������� */
        unsigned int  PWROnPrgDone        : 1;  /* bit[11]   : �ϵ�����ϡ�������ø�bit��ָʾ�˳�Power Downģʽ��������üĴ�����ϡ�
                                                               0��δ��ɣ�
                                                               1����ɡ� */
        unsigned int  reserved_0          : 1;  /* bit[12]   : ������ */
        unsigned int  GMC                 : 2;  /* bit[13-14]: ��Scatter/Gather DMAģʽ�£�����DMA������1���˵�֮ǰ�����񱾶˵�İ�����������Է����ڶ˵㡣
                                                               00��reserved��
                                                               01��1������
                                                               10��2������
                                                               11��3������ */
        unsigned int  IgnrFrmNum          : 1;  /* bit[15]   : ��Scatter/Gather DMAģʽ�£�����ͬ���˵��֡��š���bitʹ�ܣ��������е�֡��űȵ�ǰ֡���С��Ҳ���������FIFO�е����ݡ�
                                                               0����ʹ�ܣ�
                                                               1��ʹ�ܡ� */
        unsigned int  NakOnBble           : 1;  /* bit[16]   : �����յ�babble֮���Զ��ظ�NAK��
                                                               0����ʹ�ܣ�
                                                               1��ʹ�ܡ� */
        unsigned int  EnContOnBNA         : 1;  /* bit[17]   : Enable Continue on BNA
                                                               0��starts processing from the DOEPDMA descriptor
                                                               1��starts processing from the descriptor that received the BNA interrupt */
        unsigned int  DeepSleepBESLReject : 1;  /* bit[18]   : Deep Sleep BESL Reject */
        unsigned int  reserved_1          : 13; /* bit[19-31]: ������ */
    } reg;
} SOC_OTG_DCTL_UNION;
#endif
#define SOC_OTG_DCTL_RmtWkUpSig_START           (0)
#define SOC_OTG_DCTL_RmtWkUpSig_END             (0)
#define SOC_OTG_DCTL_SftDiscon_START            (1)
#define SOC_OTG_DCTL_SftDiscon_END              (1)
#define SOC_OTG_DCTL_GNPINNakSts_START          (2)
#define SOC_OTG_DCTL_GNPINNakSts_END            (2)
#define SOC_OTG_DCTL_GOUTNakSts_START           (3)
#define SOC_OTG_DCTL_GOUTNakSts_END             (3)
#define SOC_OTG_DCTL_TstCtl_START               (4)
#define SOC_OTG_DCTL_TstCtl_END                 (6)
#define SOC_OTG_DCTL_SGNPInNak_START            (7)
#define SOC_OTG_DCTL_SGNPInNak_END              (7)
#define SOC_OTG_DCTL_CGNPInNak_START            (8)
#define SOC_OTG_DCTL_CGNPInNak_END              (8)
#define SOC_OTG_DCTL_SGOUTNak_START             (9)
#define SOC_OTG_DCTL_SGOUTNak_END               (9)
#define SOC_OTG_DCTL_CGOUTNak_START             (10)
#define SOC_OTG_DCTL_CGOUTNak_END               (10)
#define SOC_OTG_DCTL_PWROnPrgDone_START         (11)
#define SOC_OTG_DCTL_PWROnPrgDone_END           (11)
#define SOC_OTG_DCTL_GMC_START                  (13)
#define SOC_OTG_DCTL_GMC_END                    (14)
#define SOC_OTG_DCTL_IgnrFrmNum_START           (15)
#define SOC_OTG_DCTL_IgnrFrmNum_END             (15)
#define SOC_OTG_DCTL_NakOnBble_START            (16)
#define SOC_OTG_DCTL_NakOnBble_END              (16)
#define SOC_OTG_DCTL_EnContOnBNA_START          (17)
#define SOC_OTG_DCTL_EnContOnBNA_END            (17)
#define SOC_OTG_DCTL_DeepSleepBESLReject_START  (18)
#define SOC_OTG_DCTL_DeepSleepBESLReject_END    (18)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DSTS_UNION
 �ṹ˵��  : DSTS �Ĵ����ṹ���塣��ַƫ����:0x0808����ֵ:0x0007FF02�����:32
 �Ĵ���˵��: device״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  SuspSts   : 1;  /* bit[0]    : suspend״ָ̬ʾ��
                                                     0��������suspend״̬��
                                                     1������suspend״̬�� */
        unsigned int  EnumSpd   : 2;  /* bit[1-2]  : ö���ٶȡ�
                                                     00�����٣�PHYʱ��Ϊ30��60MHz����
                                                     01��ȫ�٣�PHYʱ��Ϊ30��60MHz����
                                                     others�������� */
        unsigned int  ErrticErr : 1;  /* bit[3]    : ����ָʾ�κ�UTMI+�Ͻ��յ��Ĳ�ȷ���Ĵ��󡣲������ִ���ʱ������������suspend״̬�����ϱ��ж�GINTSTS[ErlySusp]��
                                                     0��û��UTMI+�ӿڴ���
                                                     1����UTMI+�ӿڴ��� */
        unsigned int  reserved_0: 4;  /* bit[4-7]  : ������ */
        unsigned int  SOFFN     : 14; /* bit[8-21] : ��ǰ֡����΢֡��֡��š� */
        unsigned int  DevLnSts  : 2;  /* bit[22-23]: Device Line Status (DevLnSts)  */
        unsigned int  reserved_1: 8;  /* bit[24-31]: ������ */
    } reg;
} SOC_OTG_DSTS_UNION;
#endif
#define SOC_OTG_DSTS_SuspSts_START    (0)
#define SOC_OTG_DSTS_SuspSts_END      (0)
#define SOC_OTG_DSTS_EnumSpd_START    (1)
#define SOC_OTG_DSTS_EnumSpd_END      (2)
#define SOC_OTG_DSTS_ErrticErr_START  (3)
#define SOC_OTG_DSTS_ErrticErr_END    (3)
#define SOC_OTG_DSTS_SOFFN_START      (8)
#define SOC_OTG_DSTS_SOFFN_END        (21)
#define SOC_OTG_DSTS_DevLnSts_START   (22)
#define SOC_OTG_DSTS_DevLnSts_END     (23)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPMSK_UNION
 �ṹ˵��  : DIEPMSK �Ĵ����ṹ���塣��ַƫ����:0x0810����ֵ:0x00000000�����:32
 �Ĵ���˵��: IN�˵���ͨ�ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferComplMsk   : 1;  /* bit[0]    : ��������ж����Ρ�
                                                          0�����Σ�
                                                          1�������Ρ� */
        unsigned int  EPDisbldMsk    : 1;  /* bit[1]    : �˵㲻ʹ���ж����Ρ�
                                                          0�����Σ�
                                                          1�������Ρ� */
        unsigned int  AHBErrMsk      : 1;  /* bit[2]    : AHB���ߴ����ж����Ρ�
                                                          0�����Σ�
                                                          1�������Ρ� */
        unsigned int  TimeOUTMsk     : 1;  /* bit[3]    : ��ʱ�ж����Ρ�
                                                          0�����Σ�
                                                          1�������Ρ� */
        unsigned int  INTknTXFEmpMsk : 1;  /* bit[4]    : ���յ�IN���ƣ����Ƿ���FIFO���ж����Ρ�
                                                          0�����Σ�
                                                          1�������Ρ� */
        unsigned int  reserved_0     : 1;  /* bit[5]    : ������ */
        unsigned int  INEPNakEffMsk  : 1;  /* bit[6]    : IN�˵�NAK��Ч���Ρ�
                                                          0�����Σ�
                                                          1�������Ρ� */
        unsigned int  reserved_1     : 1;  /* bit[7]    : ������ */
        unsigned int  TxfifoUndrnMsk : 1;  /* bit[8]    : ����FIFO�����ж����Ρ�
                                                          0�����Σ�
                                                          1�������Ρ� */
        unsigned int  BNAInIntrMsk   : 1;  /* bit[9]    : IN�˵�BNA�ж����Ρ�
                                                          0�����Σ�
                                                          1�������Ρ� */
        unsigned int  reserved_2     : 3;  /* bit[10-12]: ������ */
        unsigned int  NAKMsk         : 1;  /* bit[13]   : IN�˵�NAK�ж�����λ��
                                                          0�����Σ�
                                                          1�������Ρ� */
        unsigned int  reserved_3     : 18; /* bit[14-31]: ������ */
    } reg;
} SOC_OTG_DIEPMSK_UNION;
#endif
#define SOC_OTG_DIEPMSK_XferComplMsk_START    (0)
#define SOC_OTG_DIEPMSK_XferComplMsk_END      (0)
#define SOC_OTG_DIEPMSK_EPDisbldMsk_START     (1)
#define SOC_OTG_DIEPMSK_EPDisbldMsk_END       (1)
#define SOC_OTG_DIEPMSK_AHBErrMsk_START       (2)
#define SOC_OTG_DIEPMSK_AHBErrMsk_END         (2)
#define SOC_OTG_DIEPMSK_TimeOUTMsk_START      (3)
#define SOC_OTG_DIEPMSK_TimeOUTMsk_END        (3)
#define SOC_OTG_DIEPMSK_INTknTXFEmpMsk_START  (4)
#define SOC_OTG_DIEPMSK_INTknTXFEmpMsk_END    (4)
#define SOC_OTG_DIEPMSK_INEPNakEffMsk_START   (6)
#define SOC_OTG_DIEPMSK_INEPNakEffMsk_END     (6)
#define SOC_OTG_DIEPMSK_TxfifoUndrnMsk_START  (8)
#define SOC_OTG_DIEPMSK_TxfifoUndrnMsk_END    (8)
#define SOC_OTG_DIEPMSK_BNAInIntrMsk_START    (9)
#define SOC_OTG_DIEPMSK_BNAInIntrMsk_END      (9)
#define SOC_OTG_DIEPMSK_NAKMsk_START          (13)
#define SOC_OTG_DIEPMSK_NAKMsk_END            (13)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DOEPMSK_UNION
 �ṹ˵��  : DOEPMSK �Ĵ����ṹ���塣��ַƫ����:0x0814����ֵ:0x00000000�����:32
 �Ĵ���˵��: OUT�˵���ͨ�ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferComplMsk   : 1;  /* bit[0]    : ��������ж����Ρ�
                                                          0�����Σ�
                                                          1�������Ρ� */
        unsigned int  EPDisbldMsk    : 1;  /* bit[1]    : �˵㲻ʹ���ж����Ρ�
                                                          0�����Σ�
                                                          1�������Ρ� */
        unsigned int  AHBErrMsk      : 1;  /* bit[2]    : AHB���ߴ����ж����Ρ�
                                                          0�����Σ�
                                                          1�������Ρ� */
        unsigned int  SetUPMsk       : 1;  /* bit[3]    : setup�׶�����ж����Ρ�
                                                          0�����Σ�
                                                          1�������Ρ� */
        unsigned int  OUTTknEPdisMsk : 1;  /* bit[4]    : ���յ�OUT���ƣ����˵�û��ʹ���ж����Ρ�
                                                          0�����Σ�
                                                          1�������Ρ� */
        unsigned int  reserved_0     : 1;  /* bit[5]    : ������ */
        unsigned int  Back2BackSetup : 1;  /* bit[6]    : ������SETUP�������жϡ�
                                                          0�����Σ�
                                                          1�������Ρ� */
        unsigned int  reserved_1     : 1;  /* bit[7]    : ������ */
        unsigned int  OutPktErrMsk   : 1;  /* bit[8]    : OUT�������ж����Ρ�
                                                          0�����Σ�
                                                          1�������Ρ� */
        unsigned int  BNAOutIntrMsk  : 1;  /* bit[9]    : OUT�˵�BNA�ж����Ρ�
                                                          0�����Σ�
                                                          1�������Ρ� */
        unsigned int  reserved_2     : 2;  /* bit[10-11]: ������ */
        unsigned int  BbleErrMsk     : 1;  /* bit[12]   : babble�����ж����Ρ�
                                                          0�����Σ�
                                                          1�������Ρ� */
        unsigned int  NAKMsk         : 1;  /* bit[13]   : NAK�ж�����λ��
                                                          0������
                                                          1�������� */
        unsigned int  NYETMsk        : 1;  /* bit[14]   : NYET�ж����Ρ�
                                                          0�����Σ�
                                                          1�������Ρ� */
        unsigned int  reserved_3     : 17; /* bit[15-31]: ������ */
    } reg;
} SOC_OTG_DOEPMSK_UNION;
#endif
#define SOC_OTG_DOEPMSK_XferComplMsk_START    (0)
#define SOC_OTG_DOEPMSK_XferComplMsk_END      (0)
#define SOC_OTG_DOEPMSK_EPDisbldMsk_START     (1)
#define SOC_OTG_DOEPMSK_EPDisbldMsk_END       (1)
#define SOC_OTG_DOEPMSK_AHBErrMsk_START       (2)
#define SOC_OTG_DOEPMSK_AHBErrMsk_END         (2)
#define SOC_OTG_DOEPMSK_SetUPMsk_START        (3)
#define SOC_OTG_DOEPMSK_SetUPMsk_END          (3)
#define SOC_OTG_DOEPMSK_OUTTknEPdisMsk_START  (4)
#define SOC_OTG_DOEPMSK_OUTTknEPdisMsk_END    (4)
#define SOC_OTG_DOEPMSK_Back2BackSetup_START  (6)
#define SOC_OTG_DOEPMSK_Back2BackSetup_END    (6)
#define SOC_OTG_DOEPMSK_OutPktErrMsk_START    (8)
#define SOC_OTG_DOEPMSK_OutPktErrMsk_END      (8)
#define SOC_OTG_DOEPMSK_BNAOutIntrMsk_START   (9)
#define SOC_OTG_DOEPMSK_BNAOutIntrMsk_END     (9)
#define SOC_OTG_DOEPMSK_BbleErrMsk_START      (12)
#define SOC_OTG_DOEPMSK_BbleErrMsk_END        (12)
#define SOC_OTG_DOEPMSK_NAKMsk_START          (13)
#define SOC_OTG_DOEPMSK_NAKMsk_END            (13)
#define SOC_OTG_DOEPMSK_NYETMsk_START         (14)
#define SOC_OTG_DOEPMSK_NYETMsk_END           (14)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DAINT_UNION
 �ṹ˵��  : DAINT �Ĵ����ṹ���塣��ַƫ����:0x0818����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ж˵��ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  InEpInt  : 16; /* bit[0-15] : IN�˵��жϡ�ÿbit��Ӧ1���˵㣬bit[0]��Ӧ�˵�0��bit[15]��Ӧ�˵�15�� */
        unsigned int  OutEpInt : 16; /* bit[16-31]: OUT�˵��жϡ�ÿbit��Ӧ1���˵㣬bit[16��Ӧ�˵�0��bit[31]��Ӧ�˵�15�� */
    } reg;
} SOC_OTG_DAINT_UNION;
#endif
#define SOC_OTG_DAINT_InEpInt_START   (0)
#define SOC_OTG_DAINT_InEpInt_END     (15)
#define SOC_OTG_DAINT_OutEpInt_START  (16)
#define SOC_OTG_DAINT_OutEpInt_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DAINTMSK_UNION
 �ṹ˵��  : DAINTMSK �Ĵ����ṹ���塣��ַƫ����:0x081C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���ж˵��ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  InEpMsk  : 16; /* bit[0-15] : IN�˵���ж����Ρ�ÿbit��Ӧһ���˵㣬bit[0]��Ӧ�˵�0��bit[15]��Ӧ�˵�15��
                                                    0�����Σ�
                                                    1�������Ρ� */
        unsigned int  OutEpMsk : 16; /* bit[16-31]: OUT�˵���ж����Ρ�ÿbit��Ӧһ���˵㣬bit[16]��Ӧ�˵�0��bit[31]��Ӧ�˵�15��
                                                    0�����Σ�
                                                    1�������Ρ� */
    } reg;
} SOC_OTG_DAINTMSK_UNION;
#endif
#define SOC_OTG_DAINTMSK_InEpMsk_START   (0)
#define SOC_OTG_DAINTMSK_InEpMsk_END     (15)
#define SOC_OTG_DAINTMSK_OutEpMsk_START  (16)
#define SOC_OTG_DAINTMSK_OutEpMsk_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DVBUSDIS_UNION
 �ṹ˵��  : DVBUSDIS �Ĵ����ṹ���塣��ַƫ����:0x0828����ֵ:0x000017D7�����:32
 �Ĵ���˵��: Vbus�ŵ�ʱ�����üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DVBUSDis : 16; /* bit[0-15] : Vbus�ŵ�ʱ�䡣������SRP������Vbus�ķŵ�ʱ�䡣�����ֵ����Vbus�ŵ�ʱ���PHYʱ��������/1024�� */
        unsigned int  reserved : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_OTG_DVBUSDIS_UNION;
#endif
#define SOC_OTG_DVBUSDIS_DVBUSDis_START  (0)
#define SOC_OTG_DVBUSDIS_DVBUSDis_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DVBUSPULSE_UNION
 �ṹ˵��  : DVBUSPULSE �Ĵ����ṹ���塣��ַƫ����:0x082C����ֵ:0x000005B8�����:32
 �Ĵ���˵��: Vbus�������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DVBUSPulse : 12; /* bit[0-11] : Vbus����ʱ�䡣������SRP������Vbus����ʱ�䡣�����ֵ����Vbus����ʱ���PHYʱ��������/1024�� */
        unsigned int  reserved   : 20; /* bit[12-31]: ������ */
    } reg;
} SOC_OTG_DVBUSPULSE_UNION;
#endif
#define SOC_OTG_DVBUSPULSE_DVBUSPulse_START  (0)
#define SOC_OTG_DVBUSPULSE_DVBUSPulse_END    (11)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DTHRCTL_UNION
 �ṹ˵��  : DTHRCTL �Ĵ����ṹ���塣��ַƫ����:0x0830����ֵ:0x0C100020�����:32
 �Ĵ���˵��: deviceˮ�߿��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  NonISOThrEn : 1;  /* bit[0]    : ��Isochronous IN�˵�ˮ��ʹ�ܡ�
                                                       0����ʹ�ܣ�
                                                       1��ʹ�ܡ� */
        unsigned int  ISOThrEn    : 1;  /* bit[1]    : Isochronous IN�˵�ˮ��ʹ�ܡ�
                                                       0����ʹ�ܣ�
                                                       1��ʹ�ܡ� */
        unsigned int  TxThrLen    : 9;  /* bit[2-10] : ����FIFOˮ�ߣ�����ͬʱҲ��MACˮ�ߡ���λΪ32bit��������FIFO�����ݴ���ˮ�ߣ���USB�������ݡ�
                                                       ��AHBThrRatio=2'b00ʱ��ˮ����������Ϊ8����AHBThrRation��Ϊ0ʱ���������õ�ֵ���뱣֤AHBˮ�߲�С��8��
                                                       �����isochronous�ͷ�isochronous���䶼��Ч��
                                                       ��������ֵ�����õ�AHB burst������ȡ� */
        unsigned int  AHBThrRatio : 2;  /* bit[11-12]: ��������ʱ��AHBˮ����MACˮ�ߵı�����
                                                       00��AHBˮ�ߣ�MACˮ�ߣ�
                                                       01��AHBˮ�ߣ�MACˮ��/2;
                                                       10��AHBˮ�ߣ�MACˮ��/4��
                                                       11��AHBˮ�ߣ�MACˮ��/8 */
        unsigned int  reserved_0  : 3;  /* bit[13-15]: ������ */
        unsigned int  RxThrEn     : 1;  /* bit[16]   : ����ˮ��ʹ�ܡ�
                                                       0����ʹ�ܣ�
                                                       1��ʹ�ܡ� */
        unsigned int  RxThrLen    : 9;  /* bit[17-25]: ����FIFOˮ�ߡ���λΪ32bit������USB�����Ͻ��յ������ݴ��ڸ�������ֵʱ������AHB���䡣��������ֵ����С��8�������������ֵ����AHB burst���ȡ� */
        unsigned int  reserved_1  : 1;  /* bit[26]   : ������ */
        unsigned int  ArbPkEn     : 1;  /* bit[27]   : DMA�ٲ����á���bit����IN�˵��DMA�ٲá�����bitʹ�ܣ����ĳIN�˵���յ�IN���ƣ���IN�˵��һֱ�õ�DMA���ٲá���bit���Է�ֹ����FIFO���硣
                                                       0����ʹ�ܣ�
                                                       1��ʹ�ܡ� */
        unsigned int  reserved_2  : 4;  /* bit[28-31]: ������ */
    } reg;
} SOC_OTG_DTHRCTL_UNION;
#endif
#define SOC_OTG_DTHRCTL_NonISOThrEn_START  (0)
#define SOC_OTG_DTHRCTL_NonISOThrEn_END    (0)
#define SOC_OTG_DTHRCTL_ISOThrEn_START     (1)
#define SOC_OTG_DTHRCTL_ISOThrEn_END       (1)
#define SOC_OTG_DTHRCTL_TxThrLen_START     (2)
#define SOC_OTG_DTHRCTL_TxThrLen_END       (10)
#define SOC_OTG_DTHRCTL_AHBThrRatio_START  (11)
#define SOC_OTG_DTHRCTL_AHBThrRatio_END    (12)
#define SOC_OTG_DTHRCTL_RxThrEn_START      (16)
#define SOC_OTG_DTHRCTL_RxThrEn_END        (16)
#define SOC_OTG_DTHRCTL_RxThrLen_START     (17)
#define SOC_OTG_DTHRCTL_RxThrLen_END       (25)
#define SOC_OTG_DTHRCTL_ArbPkEn_START      (27)
#define SOC_OTG_DTHRCTL_ArbPkEn_END        (27)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPEMPMSK_UNION
 �ṹ˵��  : DIEPEMPMSK �Ĵ����ṹ���塣��ַƫ����:0x0834����ֵ:0x00000000�����:32
 �Ĵ���˵��: IN�˵�FIFO���ж����μĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  InEpTxfEmpMsk : 16; /* bit[0-15] : IN�˵㷢��FIFO���ж����μĴ�����ÿbit��Ӧһ���˵㣬bit[0]��Ӧ�˵�0��bit[15]��Ӧ�˵�15��
                                                         ÿbit���壺
                                                         0�����Σ�
                                                         1�������Ρ� */
        unsigned int  reserved      : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_OTG_DIEPEMPMSK_UNION;
#endif
#define SOC_OTG_DIEPEMPMSK_InEpTxfEmpMsk_START  (0)
#define SOC_OTG_DIEPEMPMSK_InEpTxfEmpMsk_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPCTL0_UNION
 �ṹ˵��  : DIEPCTL0 �Ĵ����ṹ���塣��ַƫ����:0x0900����ֵ:0x00008000�����:32
 �Ĵ���˵��: IN�˵�0���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MPS      : 2;  /* bit[0-1]  : ������С����IN�˵��OUT�˵㶼��Ч��
                                                    00��64�ֽڣ�
                                                    01��32�ֽڣ�
                                                    10��16�ֽڣ�
                                                    11��8�ֽڡ� */
        unsigned int  reserved_0: 9;  /* bit[2-10] : ������ */
        unsigned int  NextEp   : 4;  /* bit[11-14]: Next Endpoint (NextEp)  */
        unsigned int  USBActEP : 1;  /* bit[15]   : �˵��Ƿ񼤻��bitһֱΪ1����ʾ�˵�0һֱ���ڼ���״̬�� */
        unsigned int  reserved_1: 1;  /* bit[16]   : ������ */
        unsigned int  NAKSts   : 1;  /* bit[17]   : NAK״̬��
                                                    0������FIFO״̬�������ְ���
                                                    1���Ըö˵�Ĵ�������һֱ����NAK���ְ��� */
        unsigned int  EPType   : 2;  /* bit[18-19]: �˵����͡�һֱΪ0����ʾ�˵�0�ǿ��ƶ˵㡣 */
        unsigned int  reserved_2: 1;  /* bit[20]   : ������ */
        unsigned int  Stall    : 1;  /* bit[21]   : STALL�������á�������ø�bitʹ�ܣ�Ӳ���յ�setup���������bit����bitʹ�ܣ��Ըö˵������һֱ��ӦSTALL���֡���bit�����ȼ�����NAK���á�
                                                    0����ʹ�ܣ�
                                                    1��ʹ�ܡ� */
        unsigned int  TxFNum   : 4;  /* bit[22-25]: �˵�0�ķ���FIFO��š� */
        unsigned int  CNAK     : 1;  /* bit[26]   : ���NAK���á����bitд1���NAK���á�
                                                    0���������
                                                    1������� */
        unsigned int  SNAK     : 1;  /* bit[27]   : NAK���á����ø�bit�󣬼�ʹ����FIFO�����ݣ�Ӳ��Ҳ�����ⷢ�͡����Խ��յ���setup������NAK���֡�
                                                    0����ʹ�ܣ�
                                                    1��ʹ�ܡ� */
        unsigned int  reserved_3: 2;  /* bit[28-29]: ������ */
        unsigned int  EPDis    : 1;  /* bit[30]   : �˵�ʹ�������
                                                    0���������
                                                    1������� */
        unsigned int  EPEna    : 1;  /* bit[31]   : �˵�ʹ�ܡ�
                                                    0����ʹ�ܣ�
                                                    1��ʹ�ܡ� */
    } reg;
} SOC_OTG_DIEPCTL0_UNION;
#endif
#define SOC_OTG_DIEPCTL0_MPS_START       (0)
#define SOC_OTG_DIEPCTL0_MPS_END         (1)
#define SOC_OTG_DIEPCTL0_NextEp_START    (11)
#define SOC_OTG_DIEPCTL0_NextEp_END      (14)
#define SOC_OTG_DIEPCTL0_USBActEP_START  (15)
#define SOC_OTG_DIEPCTL0_USBActEP_END    (15)
#define SOC_OTG_DIEPCTL0_NAKSts_START    (17)
#define SOC_OTG_DIEPCTL0_NAKSts_END      (17)
#define SOC_OTG_DIEPCTL0_EPType_START    (18)
#define SOC_OTG_DIEPCTL0_EPType_END      (19)
#define SOC_OTG_DIEPCTL0_Stall_START     (21)
#define SOC_OTG_DIEPCTL0_Stall_END       (21)
#define SOC_OTG_DIEPCTL0_TxFNum_START    (22)
#define SOC_OTG_DIEPCTL0_TxFNum_END      (25)
#define SOC_OTG_DIEPCTL0_CNAK_START      (26)
#define SOC_OTG_DIEPCTL0_CNAK_END        (26)
#define SOC_OTG_DIEPCTL0_SNAK_START      (27)
#define SOC_OTG_DIEPCTL0_SNAK_END        (27)
#define SOC_OTG_DIEPCTL0_EPDis_START     (30)
#define SOC_OTG_DIEPCTL0_EPDis_END       (30)
#define SOC_OTG_DIEPCTL0_EPEna_START     (31)
#define SOC_OTG_DIEPCTL0_EPEna_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPCTLn_UNION
 �ṹ˵��  : DIEPCTLn �Ĵ����ṹ���塣��ַƫ����:0x0900+0x20*(n)����ֵ:0x00000000�����:32
 �Ĵ���˵��: IN�˵�n���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MPS      : 11; /* bit[0-10] : ����������λΪ�ֽڡ� */
        unsigned int  reserved_0: 4;  /* bit[11-14]: ������ */
        unsigned int  USBActEp : 1;  /* bit[15]   : �˵㼤�
                                                    0��û�м��
                                                    1����� */
        unsigned int  DPID     : 1;  /* bit[16]   : ���ݰ�PID״̬������interrupt��bulk������Ч��
                                                    0��DATA0��
                                                    1��DATA1�� */
        unsigned int  NAKSts   : 1;  /* bit[17]   : NAK״̬��
                                                    0������FIFO״̬�������ְ���
                                                    1���Ըö˵�Ĵ�������һֱ����NAK���ְ��� */
        unsigned int  EPType   : 2;  /* bit[18-19]: �˵����͡�
                                                    00��control��
                                                    01��isochronous��
                                                    10��bulk��
                                                    11��interrupt�� */
        unsigned int  reserved_1: 1;  /* bit[20]   : ������ */
        unsigned int  Stall    : 1;  /* bit[21]   : Stall�������á�
                                                    ���ڷ�control�ͷ�isochronous�˵㣬ʹ�ܸ�bit�󣬶����еĴ������󷵻�stall���ְ������ȼ���NAK���øߡ�
                                                    0����ʹ�ܣ�
                                                    1��ʹ�ܡ� */
        unsigned int  TxFNum   : 4;  /* bit[22-25]: ��Ӧ�ö˵�ķ���FIFO��š� */
        unsigned int  CNAK     : 1;  /* bit[26]   : ���NAK���á����bitд1���NAK���á�
                                                    0���������
                                                    1������� */
        unsigned int  SNAK     : 1;  /* bit[27]   : NAK���á����ø�bit�󣬼�ʹ����FIFO�����ݣ�Ӳ��Ҳ�����ⷢ�͡����Խ��յ���setup������NAK���֡�
                                                    0������FIFO״̬�������ְ���
                                                    1���Ըö˵�Ĵ�������һֱ����NAK���ְ��� */
        unsigned int  SetD0PID : 1;  /* bit[28]   : �������ݰ�PIDΪdata0��
                                                    0�������ã�
                                                    1�����á� */
        unsigned int  SetD1PID : 1;  /* bit[29]   : �������ݰ�PIDΪdata1��
                                                    0�������ã�
                                                    1�����á� */
        unsigned int  EPDis    : 1;  /* bit[30]   : ���ö˵㲻ʹ�ܡ�
                                                    0�������ã�
                                                    1�����á� */
        unsigned int  EPEna    : 1;  /* bit[31]   : ���ö˵�ʹ�ܡ�
                                                    0�������ã�
                                                    1�����á� */
    } reg;
} SOC_OTG_DIEPCTLn_UNION;
#endif
#define SOC_OTG_DIEPCTLn_MPS_START       (0)
#define SOC_OTG_DIEPCTLn_MPS_END         (10)
#define SOC_OTG_DIEPCTLn_USBActEp_START  (15)
#define SOC_OTG_DIEPCTLn_USBActEp_END    (15)
#define SOC_OTG_DIEPCTLn_DPID_START      (16)
#define SOC_OTG_DIEPCTLn_DPID_END        (16)
#define SOC_OTG_DIEPCTLn_NAKSts_START    (17)
#define SOC_OTG_DIEPCTLn_NAKSts_END      (17)
#define SOC_OTG_DIEPCTLn_EPType_START    (18)
#define SOC_OTG_DIEPCTLn_EPType_END      (19)
#define SOC_OTG_DIEPCTLn_Stall_START     (21)
#define SOC_OTG_DIEPCTLn_Stall_END       (21)
#define SOC_OTG_DIEPCTLn_TxFNum_START    (22)
#define SOC_OTG_DIEPCTLn_TxFNum_END      (25)
#define SOC_OTG_DIEPCTLn_CNAK_START      (26)
#define SOC_OTG_DIEPCTLn_CNAK_END        (26)
#define SOC_OTG_DIEPCTLn_SNAK_START      (27)
#define SOC_OTG_DIEPCTLn_SNAK_END        (27)
#define SOC_OTG_DIEPCTLn_SetD0PID_START  (28)
#define SOC_OTG_DIEPCTLn_SetD0PID_END    (28)
#define SOC_OTG_DIEPCTLn_SetD1PID_START  (29)
#define SOC_OTG_DIEPCTLn_SetD1PID_END    (29)
#define SOC_OTG_DIEPCTLn_EPDis_START     (30)
#define SOC_OTG_DIEPCTLn_EPDis_END       (30)
#define SOC_OTG_DIEPCTLn_EPEna_START     (31)
#define SOC_OTG_DIEPCTLn_EPEna_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPINTm_UNION
 �ṹ˵��  : DIEPINTm �Ĵ����ṹ���塣��ַƫ����:0x0908+0x20*(m)����ֵ:0x00000080�����:32
 �Ĵ���˵��: IN�˵�m�ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferCompl   : 1;  /* bit[0]    : ��������жϡ�
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  EPDisbld    : 1;  /* bit[1]    : �˵�û��ʹ���жϡ�ָʾ������������󣬸ö˵�û�б�ʹ�ܡ�
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  AHBErr      : 1;  /* bit[2]    : AHB�����жϡ�ָʾAHB���ߴ����������ͨ����Ӧ�˵��DMA��ַ�Ĵ������õ�����ĵ�ַ��
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  reserved_0  : 1;  /* bit[3]    : ������ */
        unsigned int  INTknTXFEmp : 1;  /* bit[4]    : ���յ�IN����ʱ������FIFO���жϡ�
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  reserved_1  : 1;  /* bit[5]    : ������ */
        unsigned int  INEPNakEff  : 1;  /* bit[6]    : NAK������Чָʾ��
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  TxFEmp      : 1;  /* bit[7]    : ����FIFO���жϡ�ָʾ����FIFO��ջ���ȫ�ա���ָʾ��ջ���ȫ��״̬����GAHB[NPTxFEmpLvl]������ֵ������
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  TxfifoUndrn : 1;  /* bit[8]    : ����FIFO�����жϡ�
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  BNAIntr     : 1;  /* bit[9]    : BNA(Buffer Not Available)�жϡ�����Scatter/Gather DMAʹ��ʱ��Ч��
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  reserved_2  : 1;  /* bit[10]   : ������ */
        unsigned int  PktDrpSts   : 1;  /* bit[11]   : Packet Dropped Status (PktDrpSts) */
        unsigned int  BbleErr     : 1;  /* bit[12]   : Bable�����жϡ� */
        unsigned int  NAKIntrpt   : 1;  /* bit[13]   : NAK�жϡ�ָʾ�˵���յ�NAK���ְ���
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  NYETIntrpt  : 1;  /* bit[14]   : NYET interrupt (NYETIntrpt) */
        unsigned int  StupPktRcvd : 1;  /* bit[15]   : Setup Packet Received 
                                                       0��No Setup packet received��
                                                       1��Setup packet received�� */
        unsigned int  reserved_3  : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_OTG_DIEPINTm_UNION;
#endif
#define SOC_OTG_DIEPINTm_XferCompl_START    (0)
#define SOC_OTG_DIEPINTm_XferCompl_END      (0)
#define SOC_OTG_DIEPINTm_EPDisbld_START     (1)
#define SOC_OTG_DIEPINTm_EPDisbld_END       (1)
#define SOC_OTG_DIEPINTm_AHBErr_START       (2)
#define SOC_OTG_DIEPINTm_AHBErr_END         (2)
#define SOC_OTG_DIEPINTm_INTknTXFEmp_START  (4)
#define SOC_OTG_DIEPINTm_INTknTXFEmp_END    (4)
#define SOC_OTG_DIEPINTm_INEPNakEff_START   (6)
#define SOC_OTG_DIEPINTm_INEPNakEff_END     (6)
#define SOC_OTG_DIEPINTm_TxFEmp_START       (7)
#define SOC_OTG_DIEPINTm_TxFEmp_END         (7)
#define SOC_OTG_DIEPINTm_TxfifoUndrn_START  (8)
#define SOC_OTG_DIEPINTm_TxfifoUndrn_END    (8)
#define SOC_OTG_DIEPINTm_BNAIntr_START      (9)
#define SOC_OTG_DIEPINTm_BNAIntr_END        (9)
#define SOC_OTG_DIEPINTm_PktDrpSts_START    (11)
#define SOC_OTG_DIEPINTm_PktDrpSts_END      (11)
#define SOC_OTG_DIEPINTm_BbleErr_START      (12)
#define SOC_OTG_DIEPINTm_BbleErr_END        (12)
#define SOC_OTG_DIEPINTm_NAKIntrpt_START    (13)
#define SOC_OTG_DIEPINTm_NAKIntrpt_END      (13)
#define SOC_OTG_DIEPINTm_NYETIntrpt_START   (14)
#define SOC_OTG_DIEPINTm_NYETIntrpt_END     (14)
#define SOC_OTG_DIEPINTm_StupPktRcvd_START  (15)
#define SOC_OTG_DIEPINTm_StupPktRcvd_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPTSIZ0_UNION
 �ṹ˵��  : DIEPTSIZ0 �Ĵ����ṹ���塣��ַƫ����:0x0910����ֵ:0x00000000�����:32
 �Ĵ���˵��: IN�˵�0�����С�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferSize : 7;  /* bit[0-6]  : �����С����λΪbyte�����������0�ᴥ����������жϡ�ÿ��1����������д�뷢��FIFOʱ��������ȥ���������¡� */
        unsigned int  reserved_0: 12; /* bit[7-18] : ������ */
        unsigned int  PktCnt   : 2;  /* bit[19-20]: ��������ÿ��1�����ӷ���FIFO����ʱ��������еݼ��� */
        unsigned int  reserved_1: 11; /* bit[21-31]: ������ */
    } reg;
} SOC_OTG_DIEPTSIZ0_UNION;
#endif
#define SOC_OTG_DIEPTSIZ0_XferSize_START  (0)
#define SOC_OTG_DIEPTSIZ0_XferSize_END    (6)
#define SOC_OTG_DIEPTSIZ0_PktCnt_START    (19)
#define SOC_OTG_DIEPTSIZ0_PktCnt_END      (20)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPTSIZn_UNION
 �ṹ˵��  : DIEPTSIZn �Ĵ����ṹ���塣��ַƫ����:0x0910+0x20*(n)����ֵ:0x00000000�����:32
 �Ĵ���˵��: IN�˵�n�����С�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferSize : 19; /* bit[0-18] : �����С����λΪbyte�����������0�ᴥ����������жϡ�ÿ��1����������д�뷢��FIFOʱ��������ȥ���������¡� */
        unsigned int  PktCnt   : 10; /* bit[19-28]: ��������ָʾ�ô�������ݰ�������ÿ��1�����ӷ���FIFO����ʱ��������еݼ��� */
        unsigned int  MC       : 2;  /* bit[29-30]: �������ڶ˵㣬����ָʾÿ��΢֡�ڱ��봫��İ�������Ӳ�����ݸ����ֵ����IN���ݰ���PID��
                                                    ���ڷ����ڴ��䣬����ָʾ�л�����1���˵�ǰ����ǰ�˵���봫��İ������� */
        unsigned int  reserved : 1;  /* bit[31]   : ������ */
    } reg;
} SOC_OTG_DIEPTSIZn_UNION;
#endif
#define SOC_OTG_DIEPTSIZn_XferSize_START  (0)
#define SOC_OTG_DIEPTSIZn_XferSize_END    (18)
#define SOC_OTG_DIEPTSIZn_PktCnt_START    (19)
#define SOC_OTG_DIEPTSIZn_PktCnt_END      (28)
#define SOC_OTG_DIEPTSIZn_MC_START        (29)
#define SOC_OTG_DIEPTSIZn_MC_END          (30)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPDMAm_UNION
 �ṹ˵��  : DIEPDMAm �Ĵ����ṹ���塣��ַƫ����:0x0914+0x20*(m)����ֵ:0x00000000�����:32
 �Ĵ���˵��: IN�˵�m DMA��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DMAADDR : 32; /* bit[0-31]: DMA��ַ����Scatter/Gatherʹ��ʱ��������������ʼ��ַ������32bit���롣 */
    } reg;
} SOC_OTG_DIEPDMAm_UNION;
#endif
#define SOC_OTG_DIEPDMAm_DMAADDR_START  (0)
#define SOC_OTG_DIEPDMAm_DMAADDR_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DTXFSTSm_UNION
 �ṹ˵��  : DTXFSTSm �Ĵ����ṹ���塣��ַƫ����:0x0918����ֵ:0x00001000�����:32
 �Ĵ���˵��: IN�˵�m����FIFO״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  INEPTxFSpcAvail : 16; /* bit[0-15] : ����FIFO���ÿռ䣬��λΪ32bit�� */
        unsigned int  reserved        : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_OTG_DTXFSTSm_UNION;
#endif
#define SOC_OTG_DTXFSTSm_INEPTxFSpcAvail_START  (0)
#define SOC_OTG_DTXFSTSm_INEPTxFSpcAvail_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DIEPDMABn_UNION
 �ṹ˵��  : DIEPDMABn �Ĵ����ṹ���塣��ַƫ����:0x091C+0x20*(m)����ֵ:0x00000000�����:32
 �Ĵ���˵��: IN�˵�m DMA buffer��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DMABufferAddr : 32; /* bit[0-31]: DMA buffer��ַ������Scatter/Gatherʹ��ʱ��Ч��ָʾ��ǰbuffer�ĵ�ַ�� */
    } reg;
} SOC_OTG_DIEPDMABn_UNION;
#endif
#define SOC_OTG_DIEPDMABn_DMABufferAddr_START  (0)
#define SOC_OTG_DIEPDMABn_DMABufferAddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DOEPCTL0_UNION
 �ṹ˵��  : DOEPCTL0 �Ĵ����ṹ���塣��ַƫ����:0x0B00����ֵ:0x00008000�����:32
 �Ĵ���˵��: OUT�˵�0���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MPS      : 2;  /* bit[0-1]  : ������С����IN�˵�0������һ���� */
        unsigned int  reserved_0: 13; /* bit[2-14] : ������ */
        unsigned int  USBActEP : 1;  /* bit[15]   : �˵��Ƿ񼤻��bitһֱΪ1����ʾ�˵�0һֱ���ڼ���״̬�� */
        unsigned int  reserved_1: 1;  /* bit[16]   : ������ */
        unsigned int  NAKSts   : 1;  /* bit[17]   : NAK״̬��
                                                    0������FIFO״̬�������ְ���
                                                    1���Ըö˵�Ĵ�������һֱ����NAK���ְ��� */
        unsigned int  EPType   : 2;  /* bit[18-19]: �˵����͡�һֱΪ0����ʾ�˵�0�ǿ��ƶ˵㡣 */
        unsigned int  Snp      : 1;  /* bit[20]   : ̽��ģʽ���á�ʹ�ܸ�ģʽ��Ӳ�������OUT����ֱ�ӽ����յ�������д��memory�С�
                                                    0����ʹ�ܣ�
                                                    1��ʹ�ܡ� */
        unsigned int  Stall    : 1;  /* bit[21]   : STALL�������á�������ø�bitʹ�ܣ�Ӳ���յ�setup���������bit����bitʹ�ܣ��Ըö˵������һֱ��ӦSTALL���֡���bit�����ȼ�����NAK���á�
                                                    0����ʹ�ܣ�
                                                    1��ʹ�ܡ� */
        unsigned int  reserved_2: 4;  /* bit[22-25]: ������ */
        unsigned int  CNAK     : 1;  /* bit[26]   : ���NAK���á����bitд1���NAK���á�
                                                    0���������
                                                    1������� */
        unsigned int  SNAK     : 1;  /* bit[27]   : NAK���á����ø�bit��Ӳ���ᶪ�����н��յ������ݣ���ʹ����FIFO�пռ䡣
                                                    0������FIFO״̬�������ְ���
                                                    1���Ըö˵�Ĵ�������һֱ����NAK���ְ��� */
        unsigned int  reserved_3: 2;  /* bit[28-29]: ������ */
        unsigned int  EPDis    : 1;  /* bit[30]   : �˵�ʹ�������
                                                    0���������
                                                    1������� */
        unsigned int  EPEna    : 1;  /* bit[31]   : �˵�ʹ�ܡ���������������»������λ�����ƴ���setup�׶ν������˵�ʹ����������������
                                                    0����ʹ�ܣ�
                                                    1��ʹ�ܡ� */
    } reg;
} SOC_OTG_DOEPCTL0_UNION;
#endif
#define SOC_OTG_DOEPCTL0_MPS_START       (0)
#define SOC_OTG_DOEPCTL0_MPS_END         (1)
#define SOC_OTG_DOEPCTL0_USBActEP_START  (15)
#define SOC_OTG_DOEPCTL0_USBActEP_END    (15)
#define SOC_OTG_DOEPCTL0_NAKSts_START    (17)
#define SOC_OTG_DOEPCTL0_NAKSts_END      (17)
#define SOC_OTG_DOEPCTL0_EPType_START    (18)
#define SOC_OTG_DOEPCTL0_EPType_END      (19)
#define SOC_OTG_DOEPCTL0_Snp_START       (20)
#define SOC_OTG_DOEPCTL0_Snp_END         (20)
#define SOC_OTG_DOEPCTL0_Stall_START     (21)
#define SOC_OTG_DOEPCTL0_Stall_END       (21)
#define SOC_OTG_DOEPCTL0_CNAK_START      (26)
#define SOC_OTG_DOEPCTL0_CNAK_END        (26)
#define SOC_OTG_DOEPCTL0_SNAK_START      (27)
#define SOC_OTG_DOEPCTL0_SNAK_END        (27)
#define SOC_OTG_DOEPCTL0_EPDis_START     (30)
#define SOC_OTG_DOEPCTL0_EPDis_END       (30)
#define SOC_OTG_DOEPCTL0_EPEna_START     (31)
#define SOC_OTG_DOEPCTL0_EPEna_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DOEPCTLn_UNION
 �ṹ˵��  : DOEPCTLn �Ĵ����ṹ���塣��ַƫ����:0x0B00+0x20*(n)����ֵ:0x00000000�����:32
 �Ĵ���˵��: OUT�˵�n���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  MPS      : 11; /* bit[0-10] : ����������λΪ�ֽڡ� */
        unsigned int  reserved : 4;  /* bit[11-14]: ������ */
        unsigned int  USBActEp : 1;  /* bit[15]   : �˵㼤�
                                                    1�����
                                                    0��û�м�� */
        unsigned int  DPID     : 1;  /* bit[16]   : ���ݰ�PID״̬������intterupt��bulk������Ч��
                                                    0��DATA0��
                                                    1��DATA1�� */
        unsigned int  NAKSts   : 1;  /* bit[17]   : NAK״̬��
                                                    0������FIFO״̬�������ְ���
                                                    1���Ըö˵�Ĵ�������һֱ����NAK���ְ��� */
        unsigned int  EPType   : 2;  /* bit[18-19]: �˵����͡�
                                                    00��control��
                                                    01��isochronous��
                                                    10��bulk��
                                                    11��interrupt�� */
        unsigned int  Snp      : 1;  /* bit[20]   : ̽��ģʽ���á�ʹ�ܸ�ģʽ��Ӳ�������OUT����ֱ�ӽ����յ�������д��memory�С�
                                                    0����ʹ�ܣ�
                                                    1��ʹ�ܡ� */
        unsigned int  Stall    : 1;  /* bit[21]   : Stall�������á�
                                                    ���ڷ�control�ͷ�isochronous�˵㣬ʹ�ܸ�bit�󣬶����еĴ������󷵻�stall���ְ������ȼ���NAK���øߡ�
                                                    0����ʹ�ܣ�
                                                    1��ʹ�ܡ� */
        unsigned int  TxFNum   : 4;  /* bit[22-25]: ��Ӧ�ö˵�ķ���FIFO��š� */
        unsigned int  CNAK     : 1;  /* bit[26]   : ���NAK���á����bitд1���NAK���á�
                                                    0���������
                                                    1������� */
        unsigned int  SNAK     : 1;  /* bit[27]   : NAK���á����ø�bit��Ӳ���ᶪ�����н��յ������ݣ���ʹ����FIFO�пռ䡣
                                                    0������FIFO״̬�������ְ���
                                                    1���Ըö˵�Ĵ�������һֱ����NAK���ְ��� */
        unsigned int  SetD0PID : 1;  /* bit[28]   : �������ݰ�PIDΪdata0��
                                                    0�������ã�
                                                    1�����á� */
        unsigned int  SetD1PID : 1;  /* bit[29]   : �������ݰ�PIDΪdata1��
                                                    0�������ã�
                                                    1�����á� */
        unsigned int  EPDis    : 1;  /* bit[30]   : ���ö˵㲻ʹ�ܡ�
                                                    0�������ã�
                                                    1�����á� */
        unsigned int  EPEna    : 1;  /* bit[31]   : ���ö˵�ʹ�ܡ�
                                                    0�������ã�
                                                    1�����á� */
    } reg;
} SOC_OTG_DOEPCTLn_UNION;
#endif
#define SOC_OTG_DOEPCTLn_MPS_START       (0)
#define SOC_OTG_DOEPCTLn_MPS_END         (10)
#define SOC_OTG_DOEPCTLn_USBActEp_START  (15)
#define SOC_OTG_DOEPCTLn_USBActEp_END    (15)
#define SOC_OTG_DOEPCTLn_DPID_START      (16)
#define SOC_OTG_DOEPCTLn_DPID_END        (16)
#define SOC_OTG_DOEPCTLn_NAKSts_START    (17)
#define SOC_OTG_DOEPCTLn_NAKSts_END      (17)
#define SOC_OTG_DOEPCTLn_EPType_START    (18)
#define SOC_OTG_DOEPCTLn_EPType_END      (19)
#define SOC_OTG_DOEPCTLn_Snp_START       (20)
#define SOC_OTG_DOEPCTLn_Snp_END         (20)
#define SOC_OTG_DOEPCTLn_Stall_START     (21)
#define SOC_OTG_DOEPCTLn_Stall_END       (21)
#define SOC_OTG_DOEPCTLn_TxFNum_START    (22)
#define SOC_OTG_DOEPCTLn_TxFNum_END      (25)
#define SOC_OTG_DOEPCTLn_CNAK_START      (26)
#define SOC_OTG_DOEPCTLn_CNAK_END        (26)
#define SOC_OTG_DOEPCTLn_SNAK_START      (27)
#define SOC_OTG_DOEPCTLn_SNAK_END        (27)
#define SOC_OTG_DOEPCTLn_SetD0PID_START  (28)
#define SOC_OTG_DOEPCTLn_SetD0PID_END    (28)
#define SOC_OTG_DOEPCTLn_SetD1PID_START  (29)
#define SOC_OTG_DOEPCTLn_SetD1PID_END    (29)
#define SOC_OTG_DOEPCTLn_EPDis_START     (30)
#define SOC_OTG_DOEPCTLn_EPDis_END       (30)
#define SOC_OTG_DOEPCTLn_EPEna_START     (31)
#define SOC_OTG_DOEPCTLn_EPEna_END       (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DOEPINTm_UNION
 �ṹ˵��  : DOEPINTm �Ĵ����ṹ���塣��ַƫ����:0x0B08+0x20*(m)����ֵ:0x00000000�����:32
 �Ĵ���˵��: OUT�˵�m�ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferCompl   : 1;  /* bit[0]    : ��������жϡ�
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  EPDisbld    : 1;  /* bit[1]    : �˵�û��ʹ���жϡ�ָʾ������������󣬸ö˵�û�б�ʹ�ܡ�
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  AHBErr      : 1;  /* bit[2]    : AHB�����жϡ�ָʾAHB���ߴ����������ͨ����Ӧ�˵��DMA��ַ�Ĵ����õ�����ĵ�ַ��
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  reserved_0  : 1;  /* bit[3]    : ������ */
        unsigned int  INTknTXFEmp : 1;  /* bit[4]    : ���յ�IN����ʱ������FIFO���жϡ�
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  reserved_1  : 1;  /* bit[5]    : ������ */
        unsigned int  INEPNakEff  : 1;  /* bit[6]    : NAK������Чָʾ��
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  reserved_2  : 1;  /* bit[7]    : ������ */
        unsigned int  OutPktErr   : 1;  /* bit[8]    : OUT������ָʾ����FIFO�������OUT����CRC���󡣸�bit��ˮ��ʹ��ʱ��Ч��
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  BNAIntr     : 1;  /* bit[9]    : BNA(Buffer Not Available)�жϡ�����Scatter/Gather DMAʹ��ʱ��Ч��
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  reserved_3  : 1;  /* bit[10]   : ������ */
        unsigned int  PktDrpSts   : 1;  /* bit[11]   : ������״̬��ָʾ��1��isochronous������������bitû������λ���Ҳ�������ж��ϱ�������Scatter/Gather DMAģʽ��ʹ��ʱ��Ч��
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  BbleErr     : 1;  /* bit[12]   : Bable�����жϡ�
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  NAKIntrpt   : 1;  /* bit[13]   : NAK�жϡ�ָʾ�˵���յ�NAK���ְ���
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  NYET        : 1;  /* bit[14]   : NYET�жϡ��ö˵���Ϊ��isochronous�˵�ʱ��NYET���ְ����ͻᴥ�����жϡ�
                                                       0�����жϣ�
                                                       1�����жϡ� */
        unsigned int  StupPktRcvd : 1;  /* bit[15]   : Setup Packet Received 
                                                       0��No Setup packet received��
                                                       1��Setup packet received�� */
        unsigned int  reserved_4  : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_OTG_DOEPINTm_UNION;
#endif
#define SOC_OTG_DOEPINTm_XferCompl_START    (0)
#define SOC_OTG_DOEPINTm_XferCompl_END      (0)
#define SOC_OTG_DOEPINTm_EPDisbld_START     (1)
#define SOC_OTG_DOEPINTm_EPDisbld_END       (1)
#define SOC_OTG_DOEPINTm_AHBErr_START       (2)
#define SOC_OTG_DOEPINTm_AHBErr_END         (2)
#define SOC_OTG_DOEPINTm_INTknTXFEmp_START  (4)
#define SOC_OTG_DOEPINTm_INTknTXFEmp_END    (4)
#define SOC_OTG_DOEPINTm_INEPNakEff_START   (6)
#define SOC_OTG_DOEPINTm_INEPNakEff_END     (6)
#define SOC_OTG_DOEPINTm_OutPktErr_START    (8)
#define SOC_OTG_DOEPINTm_OutPktErr_END      (8)
#define SOC_OTG_DOEPINTm_BNAIntr_START      (9)
#define SOC_OTG_DOEPINTm_BNAIntr_END        (9)
#define SOC_OTG_DOEPINTm_PktDrpSts_START    (11)
#define SOC_OTG_DOEPINTm_PktDrpSts_END      (11)
#define SOC_OTG_DOEPINTm_BbleErr_START      (12)
#define SOC_OTG_DOEPINTm_BbleErr_END        (12)
#define SOC_OTG_DOEPINTm_NAKIntrpt_START    (13)
#define SOC_OTG_DOEPINTm_NAKIntrpt_END      (13)
#define SOC_OTG_DOEPINTm_NYET_START         (14)
#define SOC_OTG_DOEPINTm_NYET_END           (14)
#define SOC_OTG_DOEPINTm_StupPktRcvd_START  (15)
#define SOC_OTG_DOEPINTm_StupPktRcvd_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DOEPTSIZ0_UNION
 �ṹ˵��  : DOEPTSIZ0 �Ĵ����ṹ���塣��ַƫ����:0x0B10����ֵ:0x00000000�����:32
 �Ĵ���˵��: OUT�˵�0�����С�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferSize : 7;  /* bit[0-6]  : �����С����λΪbyte�����������0�ᴥ����������жϡ�ÿ��1���������ݴӽ���FIFO����д���ⲿmemory��ʱ��������ȥ���������¡� */
        unsigned int  reserved_0: 12; /* bit[7-18] : ������ */
        unsigned int  PktCnt   : 1;  /* bit[19]   : ��������ÿ��1����д�����FIFO��ʱ��������еݼ��� */
        unsigned int  reserved_1: 9;  /* bit[20-28]: ������ */
        unsigned int  SUPCnt   : 2;  /* bit[29-30]: setup������������ָʾ���������յ�setup���������� */
        unsigned int  reserved_2: 1;  /* bit[31]   : ������ */
    } reg;
} SOC_OTG_DOEPTSIZ0_UNION;
#endif
#define SOC_OTG_DOEPTSIZ0_XferSize_START  (0)
#define SOC_OTG_DOEPTSIZ0_XferSize_END    (6)
#define SOC_OTG_DOEPTSIZ0_PktCnt_START    (19)
#define SOC_OTG_DOEPTSIZ0_PktCnt_END      (19)
#define SOC_OTG_DOEPTSIZ0_SUPCnt_START    (29)
#define SOC_OTG_DOEPTSIZ0_SUPCnt_END      (30)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DOEPTSIZn_UNION
 �ṹ˵��  : DOEPTSIZn �Ĵ����ṹ���塣��ַƫ����:0x0B10+0x20*(n)����ֵ:0x00000000�����:32
 �Ĵ���˵��: OUT�˵�n�����С�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  XferSize : 19; /* bit[0-18] : �����С����λΪbyte�����������0�ᴥ����������жϡ�ÿ��1���������ݴӽ���FIFO����д���ⲿmemory��ʱ��������ȥ���������¡� */
        unsigned int  PktCnt   : 10; /* bit[19-28]: ��������ÿ��1����д�����FIFO��ʱ��������еݼ��� */
        unsigned int  RxDPID   : 2;  /* bit[29-30]: ����isochronous�˵㣬ָʾ���յ������ݰ�PID��
                                                    00��DATA0��
                                                    01��DATA1��
                                                    10��DATA2��
                                                    11��MDATA��
                                                    ���ڿ��ƶ˵㣬ָʾ���Խ��յı�����setup��������
                                                    00��reserved��
                                                    01��1����
                                                    10��2����
                                                    11��3���� */
        unsigned int  reserved : 1;  /* bit[31]   : ������ */
    } reg;
} SOC_OTG_DOEPTSIZn_UNION;
#endif
#define SOC_OTG_DOEPTSIZn_XferSize_START  (0)
#define SOC_OTG_DOEPTSIZn_XferSize_END    (18)
#define SOC_OTG_DOEPTSIZn_PktCnt_START    (19)
#define SOC_OTG_DOEPTSIZn_PktCnt_END      (28)
#define SOC_OTG_DOEPTSIZn_RxDPID_START    (29)
#define SOC_OTG_DOEPTSIZn_RxDPID_END      (30)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DOEPDMAm_UNION
 �ṹ˵��  : DOEPDMAm �Ĵ����ṹ���塣��ַƫ����:0x0B14+0x20*(m)����ֵ:0x00000000�����:32
 �Ĵ���˵��: OUT�˵�m DMA��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DMAAddr : 32; /* bit[0-31]: DMA��ַ����Scatter/Gatherʹ��ʱ������Ϊ��������ʼ��ַ�� */
    } reg;
} SOC_OTG_DOEPDMAm_UNION;
#endif
#define SOC_OTG_DOEPDMAm_DMAAddr_START  (0)
#define SOC_OTG_DOEPDMAm_DMAAddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_DOEPDMABm_UNION
 �ṹ˵��  : DOEPDMABm �Ĵ����ṹ���塣��ַƫ����:0x0B1C+0x20*(m)����ֵ:0x00000000�����:32
 �Ĵ���˵��: OUT�˵�m DMA buffer��ַ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  DMABufferAddr : 32; /* bit[0-31]: DMA buffer��ַ������Scatter/Gatherʹ��ʱ��Ч��ָʾ��ǰbuffer�ĵ�ַ�� */
    } reg;
} SOC_OTG_DOEPDMABm_UNION;
#endif
#define SOC_OTG_DOEPDMABm_DMABufferAddr_START  (0)
#define SOC_OTG_DOEPDMABm_DMABufferAddr_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_PCGCCTL_UNION
 �ṹ˵��  : PCGCCTL �Ĵ����ṹ���塣��ַƫ����:0x0E00����ֵ:0xA80A8000�����:32
 �Ĵ���˵��: ���ĺ�ʱ���ſؿ��ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  StopPclk                 : 1;  /* bit[0]    : �ض�PHYʱ�ӡ���USB����suspend״̬���߻Ự��Чʱ���������ͨ�����ø�bit�ض�PHYʱ�ӡ�USB����resume״̬�����µĻỰ��ʼʱ�������Ҫ�����bit��
                                                                    0�����ض�PHYʱ�ӣ�
                                                                    1���ض�PHYʱ�ӡ� */
        unsigned int  GateHclk                 : 1;  /* bit[1]    : �ض�����ʱ�ӡ���USB����suspend״̬���߻Ự��Чʱ���������ͨ�����ø�bit�ض�����ʱ�ӡ�USB����resume״̬�����µĻỰ��ʼʱ�������Ҫ�����bit��
                                                                    0�����ض�����ʱ�ӣ�
                                                                    1���ض�����ʱ�ӡ� */
        unsigned int  PwrClmp                  : 1;  /* bit[2]    : �ź����ƿ��ơ��ڵ��������֮ǰ�������Ҫ���ø�bit��ʹ��Խ��Դ����ź������ڹ̶�״̬�������Ҫ�������ϵ�֮ǰ�����bit��
                                                                    0���źŲ����ƣ�
                                                                    1���ź����ơ� */
        unsigned int  RstPdenModule            : 1;  /* bit[3]    : ������λ���ơ�����ڵ���֮ǰ���ø�bit���������ϵ�֮����PHYʱ���ȶ�֮�������bit��
                                                                    0�����������λ��
                                                                    1���Ե�����λ�� */
        unsigned int  reserved                 : 1;  /* bit[4]    : ������ */
        unsigned int  Enbl_L1Gating            : 1;  /* bit[5]    : L1״̬ʱ���ſ�ʹ�ܡ���bitʹ�ܺ󣬽���L1״̬���ڲ��ض�PHYʱ�ӡ�
                                                                    0����ʹ�ܣ�
                                                                    1��ʹ�ܡ� */
        unsigned int  PhySleep                 : 1;  /* bit[6]    : sleep״ָ̬ʾ��ָʾPHY����sleep״̬��
                                                                    0��������sleep״̬��
                                                                    1������sleep״̬�� */
        unsigned int  L1_suspended             : 1;  /* bit[7]    : ָʾ������L1״̬ʱ��PHY����deep sleep״̬��
                                                                    0��������deep sleep״̬��
                                                                    1������deep sleep״̬�� */
        unsigned int  ResetAfterSusp           : 1;  /* bit[8]    : ����suspend״̬֮��λ���ơ�
                                                                    0������λ��
                                                                    1����λ�� */
        unsigned int  RestoreMode              : 1;  /* bit[9]    : �ָ�ģʽ��
                                                                    ����hostģʽ��
                                                                    0��Host����resume�����͸�λ������
                                                                    1��device����Զ�̻��Ѳ�����
                                                                    ����deviceģʽ��
                                                                    0��device����Զ�̻��Ѳ�����
                                                                    1��host����resume�����͸�λ������ */
        unsigned int  EnExtndedHibernation     : 1;  /* bit[10]   : Enable Extended Hibernation
                                                                    0��Extended Hibernation feature��ʹ��
                                                                    1��Extended Hibernation featureʹ�� */
        unsigned int  ExtndedHibernationClamp  : 1;  /* bit[11]   : Extended Hibernation Clamp 
                                                                    0��Extended hibernation Clamp��ʹ��
                                                                    1��Extended hibernation Clampʹ�� */
        unsigned int  ExtndedHibernationSwitch : 1;  /* bit[12]   : Extended Hibernation Switch
                                                                    0��Extended hibernation power���ز�ʹ��
                                                                    1��Extended hibernation power����ʹ�� */
        unsigned int  EssRegRestored           : 1;  /* bit[13]   : ��Ҫ�Ĵ����ָ���
                                                                    д1��ʾ��Ҫ�Ĵ���ֵ�Ѿ��ָ��� */
        unsigned int  RestoreValue             : 18; /* bit[14-31]: �ָ�ֵ��
                                                                    Bit[31]��deviceģʽ��
                                                                    0��hostģʽ��
                                                                    1��deviceģʽ��
                                                                    Bit[30:29]���˿��ٶȡ�
                                                                    00�����٣�
                                                                    01��ȫ�٣�
                                                                    others��reserved��
                                                                    Bit[26:20]��device��ַ��
                                                                    Bit[19]��mac_termselect�� 
                                                                    0��HS_TERM��
                                                                    1��FS_TERM��
                                                                    Bit[18:17]��mac_xcvrselect��
                                                                    00��HS_XCVR��
                                                                    01��FS_XCVR��
                                                                    10��LS_XCVR��
                                                                    11��LFS_XCVR��
                                                                    Bit[16]���˿ڵ�Դ���ơ�
                                                                    0���˿ڵ�Դ��ʹ�ܣ�
                                                                    1���˿ڵ�Դʹ�ܡ�
                                                                    bit[15:14]��prt_clk_sel�� */
    } reg;
} SOC_OTG_PCGCCTL_UNION;
#endif
#define SOC_OTG_PCGCCTL_StopPclk_START                  (0)
#define SOC_OTG_PCGCCTL_StopPclk_END                    (0)
#define SOC_OTG_PCGCCTL_GateHclk_START                  (1)
#define SOC_OTG_PCGCCTL_GateHclk_END                    (1)
#define SOC_OTG_PCGCCTL_PwrClmp_START                   (2)
#define SOC_OTG_PCGCCTL_PwrClmp_END                     (2)
#define SOC_OTG_PCGCCTL_RstPdenModule_START             (3)
#define SOC_OTG_PCGCCTL_RstPdenModule_END               (3)
#define SOC_OTG_PCGCCTL_Enbl_L1Gating_START             (5)
#define SOC_OTG_PCGCCTL_Enbl_L1Gating_END               (5)
#define SOC_OTG_PCGCCTL_PhySleep_START                  (6)
#define SOC_OTG_PCGCCTL_PhySleep_END                    (6)
#define SOC_OTG_PCGCCTL_L1_suspended_START              (7)
#define SOC_OTG_PCGCCTL_L1_suspended_END                (7)
#define SOC_OTG_PCGCCTL_ResetAfterSusp_START            (8)
#define SOC_OTG_PCGCCTL_ResetAfterSusp_END              (8)
#define SOC_OTG_PCGCCTL_RestoreMode_START               (9)
#define SOC_OTG_PCGCCTL_RestoreMode_END                 (9)
#define SOC_OTG_PCGCCTL_EnExtndedHibernation_START      (10)
#define SOC_OTG_PCGCCTL_EnExtndedHibernation_END        (10)
#define SOC_OTG_PCGCCTL_ExtndedHibernationClamp_START   (11)
#define SOC_OTG_PCGCCTL_ExtndedHibernationClamp_END     (11)
#define SOC_OTG_PCGCCTL_ExtndedHibernationSwitch_START  (12)
#define SOC_OTG_PCGCCTL_ExtndedHibernationSwitch_END    (12)
#define SOC_OTG_PCGCCTL_EssRegRestored_START            (13)
#define SOC_OTG_PCGCCTL_EssRegRestored_END              (13)
#define SOC_OTG_PCGCCTL_RestoreValue_START              (14)
#define SOC_OTG_PCGCCTL_RestoreValue_END                (31)






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

#endif /* end of soc_otg_interface.h */
