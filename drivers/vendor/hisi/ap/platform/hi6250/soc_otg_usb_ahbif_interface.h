/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_otg_usb_ahbif_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-09-22 14:02:36
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��9��22��
    ��    ��   : s00249479
    �޸�����   : �ӡ�Hi6250V100 SOC�Ĵ����ֲ�_OTG_USB_AHBIF.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_OTG_USB_AHBIF_INTERFACE_H__
#define __SOC_OTG_USB_AHBIF_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) register_define
 ****************************************************************************/
/* �Ĵ���˵����ѡ����ƼĴ���0
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_UNION */
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_ADDR(base)    ((base) + (0x00))

/* �Ĵ���˵����ѡ����ƼĴ���1
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_USBOTG2_CTRL1_UNION */
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL1_ADDR(base)    ((base) + (0x04))

/* �Ĵ���˵����ѡ����ƼĴ���2
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_UNION */
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_ADDR(base)    ((base) + (0x08))

/* �Ĵ���˵�����������üĴ���
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_UNION */
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_ADDR(base)    ((base) + (0x0C))

/* �Ĵ���˵����ѡ����ƼĴ���4
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_UNION */
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_ADDR(base)    ((base) + (0x10))

/* �Ĵ���˵�����ο�ʱ�ӿ��ƼĴ���
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_UNION */
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_ADDR(base)    ((base) + (0x14))

/* �Ĵ���˵����BC�������Ĵ���0
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_BC_CTRL0_UNION */
#define SOC_OTG_USB_AHBIF_BC_CTRL0_ADDR(base)         ((base) + (0x18))

/* �Ĵ���˵����BC�������Ĵ���1
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_BC_CTRL1_UNION */
#define SOC_OTG_USB_AHBIF_BC_CTRL1_ADDR(base)         ((base) + (0x1C))

/* �Ĵ���˵����BC�������Ĵ���2
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_BC_CTRL2_UNION */
#define SOC_OTG_USB_AHBIF_BC_CTRL2_ADDR(base)         ((base) + (0x20))

/* �Ĵ���˵����BC�������Ĵ���3
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_BC_CTRL3_UNION */
#define SOC_OTG_USB_AHBIF_BC_CTRL3_ADDR(base)         ((base) + (0x24))

/* �Ĵ���˵����BC�������Ĵ���4
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_BC_CTRL4_UNION */
#define SOC_OTG_USB_AHBIF_BC_CTRL4_ADDR(base)         ((base) + (0x28))

/* �Ĵ���˵����BC�������Ĵ���5
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_BC_CTRL5_UNION */
#define SOC_OTG_USB_AHBIF_BC_CTRL5_ADDR(base)         ((base) + (0x2C))

/* �Ĵ���˵����BC�������Ĵ���6
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_BC_CTRL6_UNION */
#define SOC_OTG_USB_AHBIF_BC_CTRL6_ADDR(base)         ((base) + (0x30))

/* �Ĵ���˵����BC�������Ĵ���7
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_BC_CTRL7_UNION */
#define SOC_OTG_USB_AHBIF_BC_CTRL7_ADDR(base)         ((base) + (0x34))

/* �Ĵ���˵����BC�������Ĵ���8
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_BC_CTRL8_UNION */
#define SOC_OTG_USB_AHBIF_BC_CTRL8_ADDR(base)         ((base) + (0x38))

/* �Ĵ���˵����BC״̬�Ĵ���0
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_BC_STS0_UNION */
#define SOC_OTG_USB_AHBIF_BC_STS0_ADDR(base)          ((base) + (0x3C))

/* �Ĵ���˵����BC״̬�Ĵ���1
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_BC_STS1_UNION */
#define SOC_OTG_USB_AHBIF_BC_STS1_ADDR(base)          ((base) + (0x40))

/* �Ĵ���˵����BC״̬�Ĵ���2
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_BC_STS2_UNION */
#define SOC_OTG_USB_AHBIF_BC_STS2_ADDR(base)          ((base) + (0x44))

/* �Ĵ���˵����BC״̬�Ĵ���3
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_BC_STS3_UNION */
#define SOC_OTG_USB_AHBIF_BC_STS3_ADDR(base)          ((base) + (0x48))

/* �Ĵ���˵����BC״̬�Ĵ���4
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_BC_STS4_UNION */
#define SOC_OTG_USB_AHBIF_BC_STS4_ADDR(base)          ((base) + (0x4C))

/* �Ĵ���˵�������Խӿڿ��ƼĴ���
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_UNION */
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_ADDR(base)    ((base) + (0x50))

/* �Ĵ���˵����USB״̬�Ĵ���
   λ����UNION�ṹ:  SOC_OTG_USB_AHBIF_USBOTG2_STS_UNION */
#define SOC_OTG_USB_AHBIF_USBOTG2_STS_ADDR(base)      ((base) + (0x54))





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
                     (1/1) register_define
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_UNION
 �ṹ˵��  : USBOTG2_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x00����ֵ:0x00000040�����:32
 �Ĵ���˵��: ѡ����ƼĴ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  idpullup_sel      : 1;  /* bit[0]    : ID��������ʹ��ѡ��
                                                             0����������
                                                             1���Ĵ��� */
        unsigned int  idpullup          : 1;  /* bit[1]    : ID��������ʹ�� */
        unsigned int  acaenb_sel        : 1;  /* bit[2]    : ACA�ӿ�ʹ��ѡ����Դ��
                                                             0��������
                                                             1���Ĵ��� */
        unsigned int  acaenb            : 1;  /* bit[3]    : ACA�ӿ�ʹ�� */
        unsigned int  id_sel            : 2;  /* bit[4-5]  : ACA�ӿ���Դѡ��
                                                             00�����ԼĴ�����
                                                             01������PHY��iddig��
                                                             10������PHY��ACA�ӿڣ�
                                                             ���������� */
        unsigned int  id                : 1;  /* bit[6]    : ����ģʽʶ�� */
        unsigned int  drvvbus_sel       : 1;  /* bit[7]    : ����vbus��ѹѡ��
                                                             0�����Կ�������
                                                             1�����ԼĴ��� */
        unsigned int  drvvbus           : 1;  /* bit[8]    : ʹ��vbusʩ�ӵ�ѹ */
        unsigned int  vbusvalid_sel     : 1;  /* bit[9]    : ��������vbusvalid�ź���Դѡ��
                                                             0��ѡ��PHY�����vbusvalid;
                                                             1��ѡ���ڲ���drvvbus�ź� */
        unsigned int  sessvld_sel       : 1;  /* bit[10]   : ��������sessvld�ź���Դѡ��
                                                             0��ѡ��PHY�����sessvld;
                                                             1��ѡ��Ĵ�����sessvld */
        unsigned int  sessvld           : 1;  /* bit[11]   : session��Чָʾ */
        unsigned int  dpdmpulldown_sel  : 1;  /* bit[12]   : PHY��DP/DM��������ʹ��ѡ��
                                                             0��ѡ���������dp/mpulldown��
                                                             1��ѡ��Ĵ�����dp/mpulldown */
        unsigned int  dppulldown        : 1;  /* bit[13]   : ʹ��DP�źŵ��������� */
        unsigned int  dmpulldown        : 1;  /* bit[14]   : ʹ��DM�źŵ��������� */
        unsigned int  dbnce_fltr_bypass : 1;  /* bit[15]   : ȥ��vbusvalid,avalid,bvalid,sessend��iddig�źŵ��˲��� */
        unsigned int  reserved          : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_UNION;
#endif
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_idpullup_sel_START       (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_idpullup_sel_END         (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_idpullup_START           (1)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_idpullup_END             (1)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_acaenb_sel_START         (2)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_acaenb_sel_END           (2)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_acaenb_START             (3)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_acaenb_END               (3)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_id_sel_START             (4)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_id_sel_END               (5)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_id_START                 (6)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_id_END                   (6)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_drvvbus_sel_START        (7)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_drvvbus_sel_END          (7)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_drvvbus_START            (8)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_drvvbus_END              (8)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_vbusvalid_sel_START      (9)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_vbusvalid_sel_END        (9)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_sessvld_sel_START        (10)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_sessvld_sel_END          (10)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_sessvld_START            (11)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_sessvld_END              (11)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_dpdmpulldown_sel_START   (12)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_dpdmpulldown_sel_END     (12)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_dppulldown_START         (13)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_dppulldown_END           (13)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_dmpulldown_START         (14)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_dmpulldown_END           (14)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_dbnce_fltr_bypass_START  (15)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL0_dbnce_fltr_bypass_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_USBOTG2_CTRL1_UNION
 �ṹ˵��  : USBOTG2_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x04����ֵ:0x00000000�����:32
 �Ĵ���˵��: ѡ����ƼĴ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  scaledown_mode : 2;  /* bit[0-1] : ����������ģʽ��
                                                         00������ģʽ��
                                                         01������ӿ죬����deviceģʽ��suspend��resume���������ٶ�ö�ٹ��̣�HNP/SRP,hostģʽsuspend��resume����
                                                         10��ֻ�ӿ�deviceģʽ��suspend��resume����
                                                         11�����й��̼ӿ� */
        unsigned int  reserved       : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_USBOTG2_CTRL1_UNION;
#endif
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL1_scaledown_mode_START  (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL1_scaledown_mode_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_UNION
 �ṹ˵��  : USBOTG2_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x08����ֵ:0x000000B1�����:32
 �Ĵ���˵��: ѡ����ƼĴ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  commononn     : 1;  /* bit[0]    : PHY��COMMON��·��Դ���� */
        unsigned int  otgdisable    : 1;  /* bit[1]    : �ر�PHY��OTG���� */
        unsigned int  vbusvldsel    : 1;  /* bit[2]    : VBUS��Чѡ��
                                                         0������PHY�ڲ��Ƚ���
                                                         1�����ԼĴ��� */
        unsigned int  vbusvldext    : 1;  /* bit[3]    : VBUS��Ч */
        unsigned int  txbitstuffen  : 1;  /* bit[4]    : Function: This controller signal controls bit stuffing on DATAIN<#>[7:0] when 
                                                         OPMODE<#>[1:0] = 2��b11.
                                                         1: Bit stuffing is enabled.
                                                         0: Bit stuffing is disabled. */
        unsigned int  txbitstuffenh : 1;  /* bit[5]    : Function: This controller signal controls bit stuffing on DATAIN<#>[15:8] when 
                                                         OPMODE<#>[1:0] = 2��b11.
                                                         1: Bit stuffing is enabled.
                                                         0: Bit stuffing is disabled. */
        unsigned int  fsxcvrowner   : 1;  /* bit[6]    : Function: This controller signal enables the UTMI+ or serial interface.
                                                         1: The TXENABLEN<#>, FSDATAEXT<#>, and FSSE0EXT<#> inputs drive 
                                                         USB 2.0 picoPHY data output onto the D+ and D�C lines. Data that the USB 2.0 
                                                         picoPHY receives from the D+ and D�C lines appears on the FSVMINUS<#> and 
                                                         FSVPLUS<#> outputs.
                                                         0: Data on the D+ and D�C lines is transmitted and received through the UTMI+.
                                                         If FSXCVROWNER<#> is not used, set it to 1'b0. */
        unsigned int  txenablen     : 1;  /* bit[7]    : Function: This controller signal enables the FSDATAEXT<#> and FSSE0EXT<#> 
                                                         inputs. TXENABLEN<#> is valid only when the FSXCVROWNER<#> signal is set to 1��b1.
                                                         1: FSDATAEXT<#> and FSSE0EXT<#> are disabled.
                                                         0: FSDATAEXT<#> and FSSE0EXT<#> are enabled.
                                                         If TXENABLEN<#> is not used, set it to 1'b1. */
        unsigned int  fsdataext     : 1;  /* bit[8]    : ���нӿ�������� */
        unsigned int  fsse0ext      : 1;  /* bit[9]    : ���нӿ����SE0 */
        unsigned int  vatestenb     : 2;  /* bit[10-11]: Function: Enables analog test voltages to be placed on either the ANALOGTEST or ID0 pin.
                                                         11: Reserved. Invalid setting.
                                                         10: Analog test voltages can be viewed or applied on ANALOGTEST.
                                                         01: Analog test voltages can be viewed or applied on ID0.
                                                         00: Analog test voltages cannot be viewed or applied on either ANALOGTEST or ID0. */
        unsigned int  reserved      : 20; /* bit[12-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_UNION;
#endif
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_commononn_START      (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_commononn_END        (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_otgdisable_START     (1)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_otgdisable_END       (1)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_vbusvldsel_START     (2)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_vbusvldsel_END       (2)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_vbusvldext_START     (3)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_vbusvldext_END       (3)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_txbitstuffen_START   (4)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_txbitstuffen_END     (4)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_txbitstuffenh_START  (5)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_txbitstuffenh_END    (5)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_fsxcvrowner_START    (6)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_fsxcvrowner_END      (6)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_txenablen_START      (7)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_txenablen_END        (7)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_fsdataext_START      (8)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_fsdataext_END        (8)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_fsse0ext_START       (9)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_fsse0ext_END         (9)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_vatestenb_START      (10)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL2_vatestenb_END        (11)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_UNION
 �ṹ˵��  : USBOTG2_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x0C����ֵ:0x05CD06DB�����:32
 �Ĵ���˵��: �������üĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  comdistune        : 3;  /* bit[0-2]  : Function: This bus adjusts the voltage level for the threshold used to detect a disconnect event at the host.
                                                             111: + 12%
                                                             110: + 10%
                                                             101: + 7%
                                                             100: + 3%
                                                             011: Design default
                                                             010: �C 4%
                                                             001: �C 6%
                                                             000: �C 9% */
        unsigned int  otgtune           : 3;  /* bit[3-5]  : Function: This bus adjusts the voltage level for the VBUS Valid threshold.
                                                             111: + 12%
                                                             110: + 9%
                                                             101: + 6%
                                                             100: + 3%
                                                             011: Design default
                                                             010: �C 3%
                                                             001: �C 6%
                                                             000: �C 9% */
        unsigned int  sqrxtune          : 3;  /* bit[6-8]  : Function: This bus adjusts the voltage level for the threshold used to detect valid high-speed data.
                                                             111: �C 20%
                                                             110: �C 15%
                                                             101: �C 10%
                                                             100: �C 5%
                                                             011: Design default
                                                             010: + 5%
                                                             001: + 10%
                                                             000: + 15% */
        unsigned int  txfslstune        : 4;  /* bit[9-12] : Function: This bus adjusts the low- and full-speed single-ended source impedance while driving high. The following adjustment values are based on nominal process, voltage, and temperature.
                                                             1111: �C 10.7%
                                                             0111: �C 5.6%
                                                             0011: Design default
                                                             0001: + 6.5%
                                                             0000: + 14%
                                                             All other bit settings are reserved. */
        unsigned int  txpreempamptune   : 2;  /* bit[13-14]: Function: This signal controls the amount of current sourced to DP<#> and DM<#> after a J-to-K or K-to-J transition. The HS Transmitter pre-emphasis current is defined in terms of unit amounts. One unit amount is 
                                                             approximately 600 ��A and is defined as 1X pre-emphasis current.
                                                             11: HS Transmitter pre-emphasis circuit sources 3X pre-emphasis 
                                                             current.
                                                             10: HS Transmitter pre-emphasis circuit sources 2X pre-emphasis 
                                                             current.
                                                             01: HS Transmitter pre-emphasis circuit sources 1X pre-emphasis 
                                                             current.
                                                             00 (design default): HS Transmitter pre-emphasis is disabled. */
        unsigned int  txpreemppulsetune : 1;  /* bit[15]   : ʹ�������ء���������DP��DM�ϵ�Ԥ���ص�����ʱ�䡣Ԥ������580psΪһ����λ������Ϊ1XԤ���ء���ֵ����txpreempamptune[1]����txpreempamptune[0]Ϊ1ʱ��Ч��
                                                             1:1X���̵�Ԥ����ʱ��
                                                             0:2X������Ԥ����ʱ�䡣ȱʡֵ */
        unsigned int  txrisetune        : 2;  /* bit[16-17]: ������ͼб�ʡ�
                                                             11��-8.1%
                                                             10��-7.2%
                                                             01��ȱʡֵ
                                                             00��+5.4% */
        unsigned int  txvreftune        : 4;  /* bit[18-21]: ������ͼ���µ�ѹ��
                                                             1111: + 24%
                                                             1110: + 22%
                                                             1101: + 20%
                                                             1100: + 18%
                                                             1011: + 16%
                                                             1010: + 14%
                                                             1001: + 12%
                                                             1000: + 10%
                                                             0111: + 8%
                                                             0110: + 6%
                                                             0101: + 4%
                                                             0100: + 2%
                                                             0011: Design default
                                                             0010: �C 2%
                                                             0001: �C 4%
                                                             0000: �C 6% */
        unsigned int  txhsxvtune        : 2;  /* bit[22-23]: ������ͼ0������λ�á�
                                                             11: ȱʡֵ
                                                             10: + 15 mV
                                                             01: �C15 mV
                                                             00: ���� */
        unsigned int  txrestune         : 2;  /* bit[24-25]: �����迹ƥ�䡣����ЩӦ���У���PHY������֮������кܴ�Ĵ��е��衣�ò��������������������ӵ����Ӱ�졣
                                                             11: Դ�迹���� 5.6 ��
                                                             10: Դ�迹���� 3.6 ��
                                                             01: ȱʡֵ
                                                             00: Դ�迹����1.3 �� */
        unsigned int  vdatreftune       : 2;  /* bit[26-27]: ���ݹܽż���ѹ�������ò�������Vdat_ref��ֵ��
                                                             11: �C 20%
                                                             10: �C 10%
                                                             01: ȱʡֵ
                                                             00: +10% */
        unsigned int  reserved          : 4;  /* bit[28-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_UNION;
#endif
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_comdistune_START         (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_comdistune_END           (2)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_otgtune_START            (3)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_otgtune_END              (5)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_sqrxtune_START           (6)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_sqrxtune_END             (8)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txfslstune_START         (9)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txfslstune_END           (12)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txpreempamptune_START    (13)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txpreempamptune_END      (14)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txpreemppulsetune_START  (15)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txpreemppulsetune_END    (15)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txrisetune_START         (16)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txrisetune_END           (17)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txvreftune_START         (18)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txvreftune_END           (21)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txhsxvtune_START         (22)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txhsxvtune_END           (23)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txrestune_START          (24)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_txrestune_END            (25)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_vdatreftune_START        (26)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL3_vdatreftune_END          (27)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_UNION
 �ṹ˵��  : USBOTG2_CTRL4 �Ĵ����ṹ���塣��ַƫ����:0x10����ֵ:0x00000202�����:32
 �Ĵ���˵��: ѡ����ƼĴ���4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  siddq         : 1;  /* bit[0]    : IDDQģʽ */
        unsigned int  vregbypass    : 1;  /* bit[1]    : Vreg18ѡ����ơ�Scanģʽ�²��ܸı���ֵ��
                                                         1��VDDH��Ҫ�⹩1.8V��ѹ
                                                         0��VDDHҪ�⹩3.3V��ѹ */
        unsigned int  loopbackenb   : 1;  /* bit[2]    : ���ز���ʹ�ܿ��ơ����ڲ���ģʽ��ʹ�á� */
        unsigned int  bypasssel     : 1;  /* bit[3]    : �����շ�����bypassģʽ�� */
        unsigned int  bypassdmen    : 1;  /* bit[4]    : DM bypassʹ�� */
        unsigned int  bypassdpen    : 1;  /* bit[5]    : DP bypassʹ�� */
        unsigned int  bypassdmdata  : 1;  /* bit[6]    : DM bypass���� */
        unsigned int  bypassdpdata  : 1;  /* bit[7]    : DP bypass���� */
        unsigned int  hsxcvrrextctl : 1;  /* bit[8]    : HS�շ����첽���ơ����ڸ���ģʽ�������á� */
        unsigned int  retenablen    : 1;  /* bit[9]    : retionʹ�ܣ�ȱʡΪ1 */
        unsigned int  autorsmenb    : 1;  /* bit[10]   : �Զ����ѡ� */
        unsigned int  reserved      : 21; /* bit[11-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_UNION;
#endif
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_siddq_START          (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_siddq_END            (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_vregbypass_START     (1)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_vregbypass_END       (1)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_loopbackenb_START    (2)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_loopbackenb_END      (2)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_bypasssel_START      (3)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_bypasssel_END        (3)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_bypassdmen_START     (4)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_bypassdmen_END       (4)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_bypassdpen_START     (5)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_bypassdpen_END       (5)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_bypassdmdata_START   (6)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_bypassdmdata_END     (6)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_bypassdpdata_START   (7)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_bypassdpdata_END     (7)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_hsxcvrrextctl_START  (8)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_hsxcvrrextctl_END    (8)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_retenablen_START     (9)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_retenablen_END       (9)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_autorsmenb_START     (10)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL4_autorsmenb_END       (10)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_UNION
 �ṹ˵��  : USBOTG2_CTRL5 �Ĵ����ṹ���塣��ַƫ����:0x14����ֵ:0x00003106�����:32
 �Ĵ���˵��: �ο�ʱ�ӿ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  refclksel : 2;  /* bit[0-1]  : This signal selects the reference clock source for the PLL block.
                                                     11: Reserved
                                                     10: The PLL uses CLKCORE as reference.
                                                     01: The XO block uses an external, 1.8-V clock supplied on the XO pin.
                                                     00: The XO block uses the clock from a crystal */
        unsigned int  fsel      : 3;  /* bit[2-4]  : Function: Selects the USB 2.0 picoPHY reference clock requency. 
                                                     It's value depends on the pllbtune's value.The detail usage refers to the databook description */
        unsigned int  pllbtune  : 1;  /* bit[5]    : PLL Bandwidth adjustment
                                                     This adjustment doubles the bandwidth of the PLL as needed
                                                     for some input reference clock frequencies.
                                                     1: 2x bandwidth 
                                                     0: Design default */
        unsigned int  pllitune  : 2;  /* bit[6-7]  : PLL Integral Path Tune.Reserved */
        unsigned int  pllptune  : 4;  /* bit[8-11] : PLL Proportional Path Tune.Reserved */
        unsigned int  reserved  : 20; /* bit[12-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_UNION;
#endif
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_refclksel_START  (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_refclksel_END    (1)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_fsel_START       (2)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_fsel_END         (4)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_pllbtune_START   (5)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_pllbtune_END     (5)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_pllitune_START   (6)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_pllitune_END     (7)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_pllptune_START   (8)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL5_pllptune_END     (11)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_BC_CTRL0_UNION
 �ṹ˵��  : BC_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x18����ֵ:0x00000000�����:32
 �Ĵ���˵��: BC�������Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chrg_det_en : 1;  /* bit[0]   : ԭʼ���ʹ�� */
        unsigned int  reserved    : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_BC_CTRL0_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_CTRL0_chrg_det_en_START  (0)
#define SOC_OTG_USB_AHBIF_BC_CTRL0_chrg_det_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_BC_CTRL1_UNION
 �ṹ˵��  : BC_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x1C����ֵ:0x00000000�����:32
 �Ĵ���˵��: BC�������Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chrg_det_int_clr : 1;  /* bit[0]   : ԭʼ����ж���� */
        unsigned int  reserved         : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_BC_CTRL1_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_CTRL1_chrg_det_int_clr_START  (0)
#define SOC_OTG_USB_AHBIF_BC_CTRL1_chrg_det_int_clr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_BC_CTRL2_UNION
 �ṹ˵��  : BC_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x20����ֵ:0x00000000�����:32
 �Ĵ���˵��: BC�������Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chrg_det_int_msk : 1;  /* bit[0]   : ԭʼ����ж����� */
        unsigned int  reserved         : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_BC_CTRL2_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_CTRL2_chrg_det_int_msk_START  (0)
#define SOC_OTG_USB_AHBIF_BC_CTRL2_chrg_det_int_msk_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_BC_CTRL3_UNION
 �ṹ˵��  : BC_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x24����ֵ:0x00000000�����:32
 �Ĵ���˵��: BC�������Ĵ���3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_mode  : 1;  /* bit[0]   : BCģʽʹ�� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_BC_CTRL3_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_CTRL3_bc_mode_START   (0)
#define SOC_OTG_USB_AHBIF_BC_CTRL3_bc_mode_END     (0)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_BC_CTRL4_UNION
 �ṹ˵��  : BC_CTRL4 �Ĵ����ṹ���塣��ַƫ����:0x28����ֵ:0x00000C01�����:32
 �Ĵ���˵��: BC�������Ĵ���4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_opmode     : 2;  /* bit[0-1]  : This controller bus selects the UTMI+ operational mode.
                                                         11: Normal operation without SYNC or EOP generation. If the 
                                                         XCVRSEL<#>[1:0] bus is not set to 2��b00 while OPMODE<#>[1:0] is set to 2��b11, USB 2.0 picoPHY behavior is undefined.
                                                         10: Disable bit stuffing and NRZI encoding
                                                         01: Non-Driving
                                                         00: Normal */
        unsigned int  bc_xcvrselect : 2;  /* bit[2-3]  : �շ���ѡ�� */
        unsigned int  bc_termselect : 1;  /* bit[4]    : �ն�ѡ�� */
        unsigned int  bc_txvalid    : 1;  /* bit[5]    : UTMI+��8bit���ݷ���ʹ�� */
        unsigned int  bc_txvalidh   : 1;  /* bit[6]    : UTMI+��8bit���ݷ���ʹ�� */
        unsigned int  bc_idpullup   : 1;  /* bit[7]    : ID��������ʹ�� */
        unsigned int  bc_dppulldown : 1;  /* bit[8]    : DP��������ʹ�� */
        unsigned int  bc_dmpulldown : 1;  /* bit[9]    : DM��������ʹ�� */
        unsigned int  bc_suspendm   : 1;  /* bit[10]   : suspendģʽ */
        unsigned int  bc_sleepm     : 1;  /* bit[11]   : sleepģʽ */
        unsigned int  reserved      : 20; /* bit[12-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_BC_CTRL4_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_opmode_START      (0)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_opmode_END        (1)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_xcvrselect_START  (2)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_xcvrselect_END    (3)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_termselect_START  (4)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_termselect_END    (4)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_txvalid_START     (5)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_txvalid_END       (5)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_txvalidh_START    (6)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_txvalidh_END      (6)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_idpullup_START    (7)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_idpullup_END      (7)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_dppulldown_START  (8)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_dppulldown_END    (8)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_dmpulldown_START  (9)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_dmpulldown_END    (9)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_suspendm_START    (10)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_suspendm_END      (10)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_sleepm_START      (11)
#define SOC_OTG_USB_AHBIF_BC_CTRL4_bc_sleepm_END        (11)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_BC_CTRL5_UNION
 �ṹ˵��  : BC_CTRL5 �Ĵ����ṹ���塣��ַƫ����:0x2C����ֵ:0x00000000�����:32
 �Ĵ���˵��: BC�������Ĵ���5
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_aca_en      : 1;  /* bit[0]   : ACA�ӿ�ʹ�� */
        unsigned int  bc_chrg_sel    : 1;  /* bit[1]   : ѡ��ʩ�ӵ�ƽ������ */
        unsigned int  bc_vdat_src_en : 1;  /* bit[2]   : ���ݶ˿�ʩ�ӵ�ƽʹ�� */
        unsigned int  bc_vdat_det_en : 1;  /* bit[3]   : ���ݶ˿ڵ�ƽ���ʹ�� */
        unsigned int  bc_dcd_en      : 1;  /* bit[4]   : DCD���ʹ�� */
        unsigned int  reserved       : 27; /* bit[5-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_BC_CTRL5_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_CTRL5_bc_aca_en_START       (0)
#define SOC_OTG_USB_AHBIF_BC_CTRL5_bc_aca_en_END         (0)
#define SOC_OTG_USB_AHBIF_BC_CTRL5_bc_chrg_sel_START     (1)
#define SOC_OTG_USB_AHBIF_BC_CTRL5_bc_chrg_sel_END       (1)
#define SOC_OTG_USB_AHBIF_BC_CTRL5_bc_vdat_src_en_START  (2)
#define SOC_OTG_USB_AHBIF_BC_CTRL5_bc_vdat_src_en_END    (2)
#define SOC_OTG_USB_AHBIF_BC_CTRL5_bc_vdat_det_en_START  (3)
#define SOC_OTG_USB_AHBIF_BC_CTRL5_bc_vdat_det_en_END    (3)
#define SOC_OTG_USB_AHBIF_BC_CTRL5_bc_dcd_en_START       (4)
#define SOC_OTG_USB_AHBIF_BC_CTRL5_bc_dcd_en_END         (4)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_BC_CTRL6_UNION
 �ṹ˵��  : BC_CTRL6 �Ĵ����ṹ���塣��ַƫ����:0x30����ֵ:0x00000000�����:32
 �Ĵ���˵��: BC�������Ĵ���6
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_chirp_int_clr : 1;  /* bit[0]   : ���ӿ��ж���� */
        unsigned int  reserved         : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_BC_CTRL6_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_CTRL6_bc_chirp_int_clr_START  (0)
#define SOC_OTG_USB_AHBIF_BC_CTRL6_bc_chirp_int_clr_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_BC_CTRL7_UNION
 �ṹ˵��  : BC_CTRL7 �Ĵ����ṹ���塣��ַƫ����:0x34����ֵ:0x00000000�����:32
 �Ĵ���˵��: BC�������Ĵ���7
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_chirp_int_msk : 1;  /* bit[0]   : ���ӿ��ж����� */
        unsigned int  reserved         : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_BC_CTRL7_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_CTRL7_bc_chirp_int_msk_START  (0)
#define SOC_OTG_USB_AHBIF_BC_CTRL7_bc_chirp_int_msk_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_BC_CTRL8_UNION
 �ṹ˵��  : BC_CTRL8 �Ĵ����ṹ���塣��ַƫ����:0x38����ֵ:0xFFFFFFFF�����:32
 �Ĵ���˵��: BC�������Ĵ���8
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  filter_len : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_BC_CTRL8_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_CTRL8_filter_len_START  (0)
#define SOC_OTG_USB_AHBIF_BC_CTRL8_filter_len_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_BC_STS0_UNION
 �ṹ˵��  : BC_STS0 �Ĵ����ṹ���塣��ַƫ����:0x3C����ֵ:0x00000000�����:32
 �Ĵ���˵��: BC״̬�Ĵ���0
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chrg_det_rawint : 1;  /* bit[0]   : ԭʼ������ж�(DP/DMͬʱ��ʱ��Ϊfilter_len) */
        unsigned int  reserved        : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_BC_STS0_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_STS0_chrg_det_rawint_START  (0)
#define SOC_OTG_USB_AHBIF_BC_STS0_chrg_det_rawint_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_BC_STS1_UNION
 �ṹ˵��  : BC_STS1 �Ĵ����ṹ���塣��ַƫ����:0x40����ֵ:0x00000000�����:32
 �Ĵ���˵��: BC״̬�Ĵ���1
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  chrg_det_mskint : 1;  /* bit[0]   : �������κ��ж� */
        unsigned int  reserved        : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_BC_STS1_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_STS1_chrg_det_mskint_START  (0)
#define SOC_OTG_USB_AHBIF_BC_STS1_chrg_det_mskint_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_BC_STS2_UNION
 �ṹ˵��  : BC_STS2 �Ĵ����ṹ���塣��ַƫ����:0x44����ֵ:0x00000000�����:32
 �Ĵ���˵��: BC״̬�Ĵ���2
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_vbus_valid : 1;  /* bit[0]    : vbus ��Ч */
        unsigned int  bc_sess_valid : 1;  /* bit[1]    : session ��Ч */
        unsigned int  bc_fs_vplus   : 1;  /* bit[2]    : DP״̬ */
        unsigned int  bc_fs_vminus  : 1;  /* bit[3]    : DM״̬ */
        unsigned int  bc_chg_det    : 1;  /* bit[4]    : ���ڼ�� */
        unsigned int  bc_iddig      : 1;  /* bit[5]    : ID��ƽ */
        unsigned int  bc_rid_float  : 1;  /* bit[6]    : ACA�ӿ�״̬ */
        unsigned int  bc_rid_gnd    : 1;  /* bit[7]    : ACA�ӿ�״̬ */
        unsigned int  bc_rid_a      : 1;  /* bit[8]    : ACA�ӿ�״̬ */
        unsigned int  bc_rid_b      : 1;  /* bit[9]    : ACA�ӿ�״̬ */
        unsigned int  bc_rid_c      : 1;  /* bit[10]   : ACA�ӿ�״̬ */
        unsigned int  bc_chirp_on   : 1;  /* bit[11]   : chirp״̬ */
        unsigned int  bc_linestate  : 2;  /* bit[12-13]: ��������״̬ */
        unsigned int  reserved      : 18; /* bit[14-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_BC_STS2_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_vbus_valid_START  (0)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_vbus_valid_END    (0)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_sess_valid_START  (1)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_sess_valid_END    (1)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_fs_vplus_START    (2)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_fs_vplus_END      (2)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_fs_vminus_START   (3)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_fs_vminus_END     (3)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_chg_det_START     (4)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_chg_det_END       (4)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_iddig_START       (5)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_iddig_END         (5)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_rid_float_START   (6)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_rid_float_END     (6)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_rid_gnd_START     (7)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_rid_gnd_END       (7)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_rid_a_START       (8)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_rid_a_END         (8)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_rid_b_START       (9)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_rid_b_END         (9)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_rid_c_START       (10)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_rid_c_END         (10)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_chirp_on_START    (11)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_chirp_on_END      (11)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_linestate_START   (12)
#define SOC_OTG_USB_AHBIF_BC_STS2_bc_linestate_END     (13)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_BC_STS3_UNION
 �ṹ˵��  : BC_STS3 �Ĵ����ṹ���塣��ַƫ����:0x48����ֵ:0x00000000�����:32
 �Ĵ���˵��: BC״̬�Ĵ���3
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_rawint : 1;  /* bit[0]   : ������chirp_on��Ч�����ж� */
        unsigned int  reserved  : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_BC_STS3_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_STS3_bc_rawint_START  (0)
#define SOC_OTG_USB_AHBIF_BC_STS3_bc_rawint_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_BC_STS4_UNION
 �ṹ˵��  : BC_STS4 �Ĵ����ṹ���塣��ַƫ����:0x4C����ֵ:0x00000000�����:32
 �Ĵ���˵��: BC״̬�Ĵ���4
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bc_mskint : 1;  /* bit[0]   : bc_rawint�������κ��ж� */
        unsigned int  reserved  : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_BC_STS4_UNION;
#endif
#define SOC_OTG_USB_AHBIF_BC_STS4_bc_mskint_START  (0)
#define SOC_OTG_USB_AHBIF_BC_STS4_bc_mskint_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_UNION
 �ṹ˵��  : USBOTG2_CTRL6 �Ĵ����ṹ���塣��ַƫ����:0x50����ֵ:0x00000000�����:32
 �Ĵ���˵��: ���Խӿڿ��ƼĴ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  testclk        : 1;  /* bit[0]    : ����ʱ�ӡ�����Ҫһ��������ʱ�ӣ�����������Ч */
        unsigned int  testdataoutsel : 1;  /* bit[1]    : �����������ѡ��
                                                          1��ģʽ����Ĳ��ԼĴ������
                                                          0��ģʽ������ڲ������źŵ���� */
        unsigned int  test_sel       : 1;  /* bit[2]    : ���Խӿ�ѡ��
                                                          1��ѡ����SOC test�ܽ�����
                                                          0�����ڲ��Ĵ������� */
        unsigned int  reserved_0     : 1;  /* bit[3]    : ���� */
        unsigned int  testaddr       : 4;  /* bit[4-7]  : ���ԼĴ�����ַ */
        unsigned int  testdatain     : 8;  /* bit[8-15] : ��������д���� */
        unsigned int  test_mux       : 4;  /* bit[16-19]: ���Թܽ�ѡ�� */
        unsigned int  reserved_1     : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_UNION;
#endif
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_testclk_START         (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_testclk_END           (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_testdataoutsel_START  (1)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_testdataoutsel_END    (1)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_test_sel_START        (2)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_test_sel_END          (2)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_testaddr_START        (4)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_testaddr_END          (7)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_testdatain_START      (8)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_testdatain_END        (15)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_test_mux_START        (16)
#define SOC_OTG_USB_AHBIF_USBOTG2_CTRL6_test_mux_END          (19)


/*****************************************************************************
 �ṹ��    : SOC_OTG_USB_AHBIF_USBOTG2_STS_UNION
 �ṹ˵��  : USBOTG2_STS �Ĵ����ṹ���塣��ַƫ����:0x54����ֵ:0x00000000�����:32
 �Ĵ���˵��: USB״̬�Ĵ���
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  testdataout : 4;  /* bit[0-3] : �������߶����� */
        unsigned int  hssqyelch   : 1;  /* bit[4]   : HS squelch�������� */
        unsigned int  hsrxdat     : 1;  /* bit[5]   : HS�첽���� */
        unsigned int  fslsrcv     : 1;  /* bit[6]   : �����ֵָʾ��
                                                      1��D+�ϵĵ�ѹֵ����D-
                                                      0��D-�ϵĵ�ѹֵ����D+ */
        unsigned int  reserved    : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_OTG_USB_AHBIF_USBOTG2_STS_UNION;
#endif
#define SOC_OTG_USB_AHBIF_USBOTG2_STS_testdataout_START  (0)
#define SOC_OTG_USB_AHBIF_USBOTG2_STS_testdataout_END    (3)
#define SOC_OTG_USB_AHBIF_USBOTG2_STS_hssqyelch_START    (4)
#define SOC_OTG_USB_AHBIF_USBOTG2_STS_hssqyelch_END      (4)
#define SOC_OTG_USB_AHBIF_USBOTG2_STS_hsrxdat_START      (5)
#define SOC_OTG_USB_AHBIF_USBOTG2_STS_hsrxdat_END        (5)
#define SOC_OTG_USB_AHBIF_USBOTG2_STS_fslsrcv_START      (6)
#define SOC_OTG_USB_AHBIF_USBOTG2_STS_fslsrcv_END        (6)






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

#endif /* end of soc_otg_usb_ahbif_interface.h */
