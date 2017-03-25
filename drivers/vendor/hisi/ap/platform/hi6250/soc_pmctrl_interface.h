/******************************************************************************

                 ��Ȩ���� (C), 2001-2015, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : soc_pmctrl_interface.h
  �� �� ��   : ����
  ��    ��   : Excel2Code
  ��������   : 2015-05-04 14:31:26
  ����޸�   :
  ��������   : �ӿ�ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2015��5��4��
    ��    ��   : s00249479
    �޸�����   : �ӡ�Hi6250V100 SOC�Ĵ����ֲ�_PMCTRL.xml���Զ�����

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __SOC_PMCTRL_INTERFACE_H__
#define __SOC_PMCTRL_INTERFACE_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/

/****************************************************************************
                     (1/1) reg_define
 ****************************************************************************/
/* �Ĵ���˵����PMC�ж�ʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_PMCINTEN_UNION */
#define SOC_PMCTRL_PMCINTEN_ADDR(base)                ((base) + (0x000))

/* �Ĵ���˵����PMC�ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_PMCINTSTAT_UNION */
#define SOC_PMCTRL_PMCINTSTAT_ADDR(base)              ((base) + (0x004))

/* �Ĵ���˵����PMC�ж�����Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_PMCINTCLR_UNION */
#define SOC_PMCTRL_PMCINTCLR_ADDR(base)               ((base) + (0x008))

/* �Ĵ���˵����PMC״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_PMCSTATUS_UNION */
#define SOC_PMCTRL_PMCSTATUS_ADDR(base)               ((base) + (0x00C))

/* �Ĵ���˵����APLL0���ƼĴ���0��
   λ����UNION�ṹ:  SOC_PMCTRL_APLL0CTRL0_UNION */
#define SOC_PMCTRL_APLL0CTRL0_ADDR(base)              ((base) + (0x010))

/* �Ĵ���˵����APLL0���ƼĴ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_APLL0CTRL1_UNION */
#define SOC_PMCTRL_APLL0CTRL1_ADDR(base)              ((base) + (0x014))

/* �Ĵ���˵����APLL1���ƼĴ���0��
   λ����UNION�ṹ:  SOC_PMCTRL_APLL1CTRL0_UNION */
#define SOC_PMCTRL_APLL1CTRL0_ADDR(base)              ((base) + (0x018))

/* �Ĵ���˵����APLL1���ƼĴ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_APLL1CTRL1_UNION */
#define SOC_PMCTRL_APLL1CTRL1_ADDR(base)              ((base) + (0x01C))

/* �Ĵ���˵����APLL2���ƼĴ���0��
   λ����UNION�ṹ:  SOC_PMCTRL_APLL2CTRL0_UNION */
#define SOC_PMCTRL_APLL2CTRL0_ADDR(base)              ((base) + (0x020))

/* �Ĵ���˵����APLL2���ƼĴ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_APLL2CTRL1_UNION */
#define SOC_PMCTRL_APLL2CTRL1_ADDR(base)              ((base) + (0x024))

/* �Ĵ���˵����PPLL1���ƼĴ���0��
   λ����UNION�ṹ:  SOC_PMCTRL_PPLL1CTRL0_UNION */
#define SOC_PMCTRL_PPLL1CTRL0_ADDR(base)              ((base) + (0x038))

/* �Ĵ���˵����PPLL1���ƼĴ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_PPLL1CTRL1_UNION */
#define SOC_PMCTRL_PPLL1CTRL1_ADDR(base)              ((base) + (0x03C))

/* �Ĵ���˵����PPLL2���ƼĴ���0��
   λ����UNION�ṹ:  SOC_PMCTRL_PPLL2CTRL0_UNION */
#define SOC_PMCTRL_PPLL2CTRL0_ADDR(base)              ((base) + (0x040))

/* �Ĵ���˵����PPLL2���ƼĴ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_PPLL2CTRL1_UNION */
#define SOC_PMCTRL_PPLL2CTRL1_ADDR(base)              ((base) + (0x044))

/* �Ĵ���˵����PPLL3���ƼĴ���0��
   λ����UNION�ṹ:  SOC_PMCTRL_PPLL3CTRL0_UNION */
#define SOC_PMCTRL_PPLL3CTRL0_ADDR(base)              ((base) + (0x048))

/* �Ĵ���˵����PPLL3���ƼĴ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_PPLL3CTRL1_UNION */
#define SOC_PMCTRL_PPLL3CTRL1_ADDR(base)              ((base) + (0x04C))

/* �Ĵ���˵����APLL0 SSC���ƼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_APLL0SSCCTRL_UNION */
#define SOC_PMCTRL_APLL0SSCCTRL_ADDR(base)            ((base) + (0x070))

/* �Ĵ���˵����APLL1 SSC���ƼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_APLL1SSCCTRL_UNION */
#define SOC_PMCTRL_APLL1SSCCTRL_ADDR(base)            ((base) + (0x074))

/* �Ĵ���˵����APLL2 SSC���ƼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_APLL2SSCCTRL_UNION */
#define SOC_PMCTRL_APLL2SSCCTRL_ADDR(base)            ((base) + (0x078))

/* �Ĵ���˵����PPLL1 SSC���ƼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_PPLL1SSCCTRL_UNION */
#define SOC_PMCTRL_PPLL1SSCCTRL_ADDR(base)            ((base) + (0x084))

/* �Ĵ���˵����PPLL2 SSC���ƼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_PPLL2SSCCTRL_UNION */
#define SOC_PMCTRL_PPLL2SSCCTRL_ADDR(base)            ((base) + (0x088))

/* �Ĵ���˵����PPLL3 SSC���ƼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_PPLL3SSCCTRL_UNION */
#define SOC_PMCTRL_PPLL3SSCCTRL_ADDR(base)            ((base) + (0x08C))

/* �Ĵ���˵����PMU����ģʽ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_PMUMOD_UNION */
#define SOC_PMCTRL_PMUMOD_ADDR(base)                  ((base) + (0x094))

/* �Ĵ���˵����CLUSTER0_CPU DVFSģʽ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUDVFSMOD_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUDVFSMOD_ADDR(base)     ((base) + (0x098))

/* �Ĵ���˵����CLUSTER0_CPU ʱ����Դѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUCLKSEL_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUCLKSEL_ADDR(base)      ((base) + (0x09C))

/* �Ĵ���˵����CLUSTER0_CPU DVFSʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUDVFSEN_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUDVFSEN_ADDR(base)      ((base) + (0x0A0))

/* �Ĵ���˵����CLUSTER0_CPU PLLѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUPLLSEL_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUPLLSEL_ADDR(base)      ((base) + (0x0A4))

/* �Ĵ���˵����CLUSTER0_CPUʱ�ӷ�Ƶ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUCLKDIV_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUCLKDIV_ADDR(base)      ((base) + (0x0A8))

/* �Ĵ���˵����CLUSTER0_CPU DVFS�����Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUDVFSSTART_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUDVFSSTART_ADDR(base)   ((base) + (0x0AC))

/* �Ĵ���˵����CLUSTER0_CPUƵ��Profile�Ĵ���0��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_ADDR(base) ((base) + (0x0B0))

/* �Ĵ���˵����CLUSTER0_CPUƵ��Profile�Ĵ���0_1��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_1_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_1_ADDR(base) ((base) + (0x0B4))

/* �Ĵ���˵����CLUSTER0_CPUƵ��Profile�Ĵ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE1_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE1_ADDR(base) ((base) + (0x0B8))

/* �Ĵ���˵����CLUSTER0_CPU DVFSʱ��ѹģʽ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUVOLMOD_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUVOLMOD_ADDR(base)      ((base) + (0x0BC))

/* �Ĵ���˵����CLUSTER0_CPU��ѹProfile�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUVOLPROFILE_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUVOLPROFILE_ADDR(base)  ((base) + (0x0C0))

/* �Ĵ���˵����CLUSTER0_CPU DVFSʱ����λģʽ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUPHASEMOD_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUPHASEMOD_ADDR(base)    ((base) + (0xC8))

/* �Ĵ���˵����CLUSTER0_CPU��λProfile�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUPHASEPROFILE_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUPHASEPROFILE_ADDR(base) ((base) + (0x0CC))

/* �Ĵ���˵����CLUSTER0_CPU��ѹ/��λ�����Ⱥ�ѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUVOLPHASESEL_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUVOLPHASESEL_ADDR(base) ((base) + (0x0D0))

/* �Ĵ���˵����CLUSTER0_��ѹ����һ���ȶ�����ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_VOLUPSTEPTIME_UNION */
#define SOC_PMCTRL_CLUSTER0_VOLUPSTEPTIME_ADDR(base)  ((base) + (0x0D4))

/* �Ĵ���˵����CLUSTER0_��ѹ�½�һ���ȶ�����ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_VOLDNSTEPTIME_UNION */
#define SOC_PMCTRL_CLUSTER0_VOLDNSTEPTIME_ADDR(base)  ((base) + (0x0D8))

/* �Ĵ���˵����CLUSTER0_ DVFSʱ�ı��ѹ��λ�������ȶ�ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_PHASEUPTIME_UNION */
#define SOC_PMCTRL_CLUSTER0_PHASEUPTIME_ADDR(base)    ((base) + (0x0DC))

/* �Ĵ���˵����CLUSTER0_ DVFSʱ�ı��ѹ��λ���½��ȶ�ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_PHASEDNTIME_UNION */
#define SOC_PMCTRL_CLUSTER0_PHASEDNTIME_ADDR(base)    ((base) + (0x0E0))

/* �Ĵ���˵����CLUSTER0_��ѹ�ȶ�ʱ��ԣ���Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_PMUHOLDTIME_UNION */
#define SOC_PMCTRL_CLUSTER0_PMUHOLDTIME_ADDR(base)    ((base) + (0x0E4))

/* �Ĵ���˵����CLUSTER0_PMUѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_PMUSEL_UNION */
#define SOC_PMCTRL_CLUSTER0_PMUSEL_ADDR(base)         ((base) + (0x0E8))

/* �Ĵ���˵����CLUSTER0_CPU AVSʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUAVSEN_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUAVSEN_ADDR(base)       ((base) + (0x0F0))

/* �Ĵ���˵����CLUSTER0_CPU AVS����ģʽ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUAVSPARAMOD_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARAMOD_ADDR(base)  ((base) + (0x0F4))

/* �Ĵ���˵����CLUSTER0_CPU AVS�����Ĵ���0��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUAVSPARA0_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA0_ADDR(base)    ((base) + (0x0F8))

/* �Ĵ���˵����CLUSTER0_CPU AVS�����Ĵ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUAVSPARA1_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA1_ADDR(base)    ((base) + (0x0FC))

/* �Ĵ���˵����CLUSTER0_CPU AVS�����Ĵ���2��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUAVSPARA2_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA2_ADDR(base)    ((base) + (0x100))

/* �Ĵ���˵����CLUSTER0_CPU AVS�����Ĵ���3��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUAVSPARA3_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA3_ADDR(base)    ((base) + (0x104))

/* �Ĵ���˵����CLUSTER0_CPU AVS�����Ĵ���4��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUAVSPARA4_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA4_ADDR(base)    ((base) + (0x108))

/* �Ĵ���˵����CLUSTER0_CPU AVS�����Ĵ���5��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUAVSPARA5_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA5_ADDR(base)    ((base) + (0x10C))

/* �Ĵ���˵����CLUSTER0_CPU AVSʹ�ܼĴ���6��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUAVSPARA6_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA6_ADDR(base)    ((base) + (0x110))

/* �Ĵ���˵����CLUSTER0_CPU HPM����ѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUHPMTYP_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_ADDR(base)      ((base) + (0x114))

/* �Ĵ���˵����CLUSTER0_CPU01 HPMʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPU01HPMEN_UNION */
#define SOC_PMCTRL_CLUSTER0_CPU01HPMEN_ADDR(base)     ((base) + (0x118))

/* �Ĵ���˵����CLUSTER0_CPU01 HPMXʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPU01HPMXEN_UNION */
#define SOC_PMCTRL_CLUSTER0_CPU01HPMXEN_ADDR(base)    ((base) + (0x11C))

/* �Ĵ���˵����CLUSTER0_CPU01 HPM OPC��Ч�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPU01HPMOPCVALID_UNION */
#define SOC_PMCTRL_CLUSTER0_CPU01HPMOPCVALID_ADDR(base) ((base) + (0x120))

/* �Ĵ���˵����CLUSTER0_CPU01 HPM OPC�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPU01HPMOPC_UNION */
#define SOC_PMCTRL_CLUSTER0_CPU01HPMOPC_ADDR(base)    ((base) + (0x124))

/* �Ĵ���˵����CLUSTER0_CPU01 HPMX OPC�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPU01HPMXOPC_UNION */
#define SOC_PMCTRL_CLUSTER0_CPU01HPMXOPC_ADDR(base)   ((base) + (0x128))

/* �Ĵ���˵����CLUSTER0_CPU01 HPM PC�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPU01HPMPC_UNION */
#define SOC_PMCTRL_CLUSTER0_CPU01HPMPC_ADDR(base)     ((base) + (0x12C))

/* �Ĵ���˵����CLUSTER0_CPU23 HPMʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPU23HPMEN_UNION */
#define SOC_PMCTRL_CLUSTER0_CPU23HPMEN_ADDR(base)     ((base) + (0x134))

/* �Ĵ���˵����CLUSTER0_CPU23 HPMXʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPU23HPMXEN_UNION */
#define SOC_PMCTRL_CLUSTER0_CPU23HPMXEN_ADDR(base)    ((base) + (0x138))

/* �Ĵ���˵����CLUSTER0_CPU23 HPM OPC��Ч�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPU23HPMOPCVALID_UNION */
#define SOC_PMCTRL_CLUSTER0_CPU23HPMOPCVALID_ADDR(base) ((base) + (0x13C))

/* �Ĵ���˵����CLUSTER0_CPU23 HPM OPC�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPU23HPMOPC_UNION */
#define SOC_PMCTRL_CLUSTER0_CPU23HPMOPC_ADDR(base)    ((base) + (0x140))

/* �Ĵ���˵����CLUSTER0_CPU23 HPMX OPC�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPU23HPMXOPC_UNION */
#define SOC_PMCTRL_CLUSTER0_CPU23HPMXOPC_ADDR(base)   ((base) + (0x144))

/* �Ĵ���˵����CLUSTER0_CPU23 HPM PC�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPU23HPMPC_UNION */
#define SOC_PMCTRL_CLUSTER0_CPU23HPMPC_ADDR(base)     ((base) + (0x148))

/* �Ĵ���˵����CLUSTER0_CPU HPMʱ�ӷ�Ƶ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUHPMCLKDIV_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUHPMCLKDIV_ADDR(base)   ((base) + (0x150))

/* �Ĵ���˵����CLUSTER0_CPU AVS��ѹ���ƼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER0_CPUAVSVOLIDX_UNION */
#define SOC_PMCTRL_CLUSTER0_CPUAVSVOLIDX_ADDR(base)   ((base) + (0x154))

/* �Ĵ���˵����CLUSTER1_CPU DVFSģʽ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUDVFSMOD_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUDVFSMOD_ADDR(base)     ((base) + (0x158))

/* �Ĵ���˵����CLUSTER1_CPU ʱ����Դѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUCLKSEL_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUCLKSEL_ADDR(base)      ((base) + (0x15C))

/* �Ĵ���˵����CLUSTER1_CPU DVFSʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUDVFSEN_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUDVFSEN_ADDR(base)      ((base) + (0x160))

/* �Ĵ���˵����CLUSTER1_CPU PLLѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUPLLSEL_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUPLLSEL_ADDR(base)      ((base) + (0x164))

/* �Ĵ���˵����CLUSTER1_CPUʱ�ӷ�Ƶ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUCLKDIV_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUCLKDIV_ADDR(base)      ((base) + (0x168))

/* �Ĵ���˵����CLUSTER1_CPU DVFS�����Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUDVFSSTART_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUDVFSSTART_ADDR(base)   ((base) + (0x16C))

/* �Ĵ���˵����CLUSTER1_CPUƵ��Profile�Ĵ���0��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_ADDR(base) ((base) + (0x170))

/* �Ĵ���˵����CLUSTER1_CPUƵ��Profile�Ĵ���0_1��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_1_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_1_ADDR(base) ((base) + (0x174))

/* �Ĵ���˵����CLUSTER1_CPUƵ��Profile�Ĵ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE1_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE1_ADDR(base) ((base) + (0x178))

/* �Ĵ���˵����CLUSTER1_CPU DVFSʱ�ĵ�ѹģʽ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUVOLMOD_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUVOLMOD_ADDR(base)      ((base) + (0x17C))

/* �Ĵ���˵����CLUSTER1_CPU��ѹProfile�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUVOLPROFILE_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUVOLPROFILE_ADDR(base)  ((base) + (0x180))

/* �Ĵ���˵����CLUSTER1_CPU DVFSʱ����λģʽ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUPHASEMOD_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUPHASEMOD_ADDR(base)    ((base) + (0x188))

/* �Ĵ���˵����CLUSTER1_CPU��λProfile�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUPHASEPROFILE_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUPHASEPROFILE_ADDR(base) ((base) + (0x18C))

/* �Ĵ���˵����CLUSTER1_CPU��ѹ/��λ����ѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUVOLPHASESEL_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUVOLPHASESEL_ADDR(base) ((base) + (0x190))

/* �Ĵ���˵����CLUSTER1_��ѹ����һ���ȶ�����ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_VOLUPSTEPTIME_UNION */
#define SOC_PMCTRL_CLUSTER1_VOLUPSTEPTIME_ADDR(base)  ((base) + (0x194))

/* �Ĵ���˵����CLUSTER1_��ѹ�½�һ���ȶ�����ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_VOLDNSTEPTIME_UNION */
#define SOC_PMCTRL_CLUSTER1_VOLDNSTEPTIME_ADDR(base)  ((base) + (0x198))

/* �Ĵ���˵����CLUSTER1_ DVFSʱ�ı��ѹ��λ�������ȶ�ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_PHASEUPTIME_UNION */
#define SOC_PMCTRL_CLUSTER1_PHASEUPTIME_ADDR(base)    ((base) + (0x19C))

/* �Ĵ���˵����CLUSTER1_ DVFSʱ�ı��ѹ��λ���½��ȶ�ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_PHASEDNTIME_UNION */
#define SOC_PMCTRL_CLUSTER1_PHASEDNTIME_ADDR(base)    ((base) + (0x1A0))

/* �Ĵ���˵����CLUSTER1_��ѹ�ȶ�ʱ��ԣ���Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_PMUHOLDTIME_UNION */
#define SOC_PMCTRL_CLUSTER1_PMUHOLDTIME_ADDR(base)    ((base) + (0x1A4))

/* �Ĵ���˵����CLUSTER1_PMUѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_PMUSEL_UNION */
#define SOC_PMCTRL_CLUSTER1_PMUSEL_ADDR(base)         ((base) + (0x1A8))

/* �Ĵ���˵����CLUSTER1_CPU AVSʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUAVSEN_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUAVSEN_ADDR(base)       ((base) + (0x1B0))

/* �Ĵ���˵����CLUSTER1_CPU AVS����ģʽ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUAVSPARAMOD_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARAMOD_ADDR(base)  ((base) + (0x1B4))

/* �Ĵ���˵����CLUSTER1_CPU AVS�����Ĵ���0��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUAVSPARA0_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA0_ADDR(base)    ((base) + (0x1B8))

/* �Ĵ���˵����CLUSTER1_CPU AVS�����Ĵ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUAVSPARA1_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA1_ADDR(base)    ((base) + (0x1BC))

/* �Ĵ���˵����CLUSTER1_CPU AVS�����Ĵ���2��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUAVSPARA2_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA2_ADDR(base)    ((base) + (0x1C0))

/* �Ĵ���˵����CLUSTER1_CPU AVS�����Ĵ���3��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUAVSPARA3_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA3_ADDR(base)    ((base) + (0x1C4))

/* �Ĵ���˵����CLUSTER1_CPU AVS�����Ĵ���4��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUAVSPARA4_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA4_ADDR(base)    ((base) + (0x1C8))

/* �Ĵ���˵����CLUSTER1_CPU AVS�����Ĵ���5��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUAVSPARA5_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA5_ADDR(base)    ((base) + (0x1CC))

/* �Ĵ���˵����CLUSTER1_CPU AVSʹ�ܼĴ���6��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUAVSPARA6_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA6_ADDR(base)    ((base) + (0x1D0))

/* �Ĵ���˵����CLUSTER1_CPU01 HPM����ѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUHPMTYP_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUHPMTYP_ADDR(base)      ((base) + (0x1D4))

/* �Ĵ���˵����CLUSTER1_CPU01 HPMʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPU01HPMEN_UNION */
#define SOC_PMCTRL_CLUSTER1_CPU01HPMEN_ADDR(base)     ((base) + (0x1D8))

/* �Ĵ���˵����CLUSTER1_CPU01 HPMXʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPU01HPMXEN_UNION */
#define SOC_PMCTRL_CLUSTER1_CPU01HPMXEN_ADDR(base)    ((base) + (0x1DC))

/* �Ĵ���˵����CLUSTER1_CPU01 HPM OPC��Ч�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPU01HPMOPCVALID_UNION */
#define SOC_PMCTRL_CLUSTER1_CPU01HPMOPCVALID_ADDR(base) ((base) + (0x1E0))

/* �Ĵ���˵����CLUSTER1_CPU01 HPM OPC�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPU01HPMOPC_UNION */
#define SOC_PMCTRL_CLUSTER1_CPU01HPMOPC_ADDR(base)    ((base) + (0x1E4))

/* �Ĵ���˵����CLUSTER1_CPU01 HPMX OPC�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPU01HPMXOPC_UNION */
#define SOC_PMCTRL_CLUSTER1_CPU01HPMXOPC_ADDR(base)   ((base) + (0x1E8))

/* �Ĵ���˵����CLUSTER1_CPU HPM PC�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPU01HPMPC_UNION */
#define SOC_PMCTRL_CLUSTER1_CPU01HPMPC_ADDR(base)     ((base) + (0x1EC))

/* �Ĵ���˵����CLUSTER1_CPU23 HPMʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPU23HPMEN_UNION */
#define SOC_PMCTRL_CLUSTER1_CPU23HPMEN_ADDR(base)     ((base) + (0x1F4))

/* �Ĵ���˵����CLUSTER1_CPU23 HPMXʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPU23HPMXEN_UNION */
#define SOC_PMCTRL_CLUSTER1_CPU23HPMXEN_ADDR(base)    ((base) + (0x1F8))

/* �Ĵ���˵����CLUSTER1_CPU23 HPM OPC��Ч�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPU23HPMOPCVALID_UNION */
#define SOC_PMCTRL_CLUSTER1_CPU23HPMOPCVALID_ADDR(base) ((base) + (0x1FC))

/* �Ĵ���˵����CLUSTER1_CPU23 HPM OPC�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPU23HPMOPC_UNION */
#define SOC_PMCTRL_CLUSTER1_CPU23HPMOPC_ADDR(base)    ((base) + (0x200))

/* �Ĵ���˵����CLUSTER1_CPU23 HPMX OPC�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPU23HPMXOPC_UNION */
#define SOC_PMCTRL_CLUSTER1_CPU23HPMXOPC_ADDR(base)   ((base) + (0x204))

/* �Ĵ���˵����CLUSTER1_CPU HPM PC�Ĵ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPU23HPMPC_UNION */
#define SOC_PMCTRL_CLUSTER1_CPU23HPMPC_ADDR(base)     ((base) + (0x208))

/* �Ĵ���˵����CLUSTER1_CPU HPMʱ�ӷ�Ƶ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUHPMCLKDIV_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUHPMCLKDIV_ADDR(base)   ((base) + (0x210))

/* �Ĵ���˵����CLUSTER1_CPU AVS��ѹ���ƼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_CLUSTER1_CPUAVSVOLIDX_UNION */
#define SOC_PMCTRL_CLUSTER1_CPUAVSVOLIDX_ADDR(base)   ((base) + (0x214))

/* �Ĵ���˵����G3D AXIʱ��ѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DCLKSEL_UNION */
#define SOC_PMCTRL_G3DCLKSEL_ADDR(base)               ((base) + (0x220))

/* �Ĵ���˵����G3D AXIʱ�ӷ�Ƶ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DCLKDIV_UNION */
#define SOC_PMCTRL_G3DCLKDIV_ADDR(base)               ((base) + (0x224))

/* �Ĵ���˵����G3D DVFSʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DDVFSEN_UNION */
#define SOC_PMCTRL_G3DDVFSEN_ADDR(base)               ((base) + (0x228))

/* �Ĵ���˵����G3D DVFS�����Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DDVFSSTART_UNION */
#define SOC_PMCTRL_G3DDVFSSTART_ADDR(base)            ((base) + (0x22C))

/* �Ĵ���˵����G3DƵ��Profile�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DCLKPROFILE_UNION */
#define SOC_PMCTRL_G3DCLKPROFILE_ADDR(base)           ((base) + (0x230))

/* �Ĵ���˵����G3D DVFS��ѹģʽ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DVOLMOD_UNION */
#define SOC_PMCTRL_G3DVOLMOD_ADDR(base)               ((base) + (0x234))

/* �Ĵ���˵����G3D��ѹProfile�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DVOLPROFILE_UNION */
#define SOC_PMCTRL_G3DVOLPROFILE_ADDR(base)           ((base) + (0x238))

/* �Ĵ���˵����G3D DVFS�ı��ѹ��λģʽ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DPHASEMOD_UNION */
#define SOC_PMCTRL_G3DPHASEMOD_ADDR(base)             ((base) + (0x240))

/* �Ĵ���˵����G3D��λProfile�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DPHASEPROFILE_UNION */
#define SOC_PMCTRL_G3DPHASEPROFILE_ADDR(base)         ((base) + (0x244))

/* �Ĵ���˵����G3D��ѹ/��λ����ѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DVOLPHASESEL_UNION */
#define SOC_PMCTRL_G3DVOLPHASESEL_ADDR(base)          ((base) + (0x248))

/* �Ĵ���˵����G3D���PMUѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DPMUSEL_UNION */
#define SOC_PMCTRL_G3DPMUSEL_ADDR(base)               ((base) + (0x24C))

/* �Ĵ���˵����G3D��ѹ����һ���ȶ�����ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DVOLUPSTEPTIME_UNION */
#define SOC_PMCTRL_G3DVOLUPSTEPTIME_ADDR(base)        ((base) + (0x250))

/* �Ĵ���˵����G3D��ѹ�½�һ���ȶ�����ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DVOLDNSTEPTIME_UNION */
#define SOC_PMCTRL_G3DVOLDNSTEPTIME_ADDR(base)        ((base) + (0x254))

/* �Ĵ���˵����G3D DVFSʱ�ı��ѹ��λ�������ȶ�ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DPHASEUPTIME_UNION */
#define SOC_PMCTRL_G3DPHASEUPTIME_ADDR(base)          ((base) + (0x258))

/* �Ĵ���˵����G3D DVFSʱ�ı��ѹ��λ���½��ȶ�ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DPHASEDNTIME_UNION */
#define SOC_PMCTRL_G3DPHASEDNTIME_ADDR(base)          ((base) + (0x25C))

/* �Ĵ���˵����G3D��ѹ�ȶ�ʱ��ԣ���Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DPMUHOLDTIME_UNION */
#define SOC_PMCTRL_G3DPMUHOLDTIME_ADDR(base)          ((base) + (0x260))

/* �Ĵ���˵����G3D HPMӲ������bypass�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DHPMBYPASS_UNION */
#define SOC_PMCTRL_G3DHPMBYPASS_ADDR(base)            ((base) + (0x264))

/* �Ĵ���˵����G3D�Զ���Ƶbypass���ƼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_UNION */
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_ADDR(base)     ((base) + (0x268))

/* �Ĵ���˵����G3D AVSʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DAVSEN_UNION */
#define SOC_PMCTRL_G3DAVSEN_ADDR(base)                ((base) + (0x270))

/* �Ĵ���˵����G3D AVS����ģʽ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DAVSPARAMOD_UNION */
#define SOC_PMCTRL_G3DAVSPARAMOD_ADDR(base)           ((base) + (0x274))

/* �Ĵ���˵����G3D AVS�����Ĵ���0��
   λ����UNION�ṹ:  SOC_PMCTRL_G3DAVSPARA0_UNION */
#define SOC_PMCTRL_G3DAVSPARA0_ADDR(base)             ((base) + (0x278))

/* �Ĵ���˵����G3D AVS�����Ĵ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_G3DAVSPARA1_UNION */
#define SOC_PMCTRL_G3DAVSPARA1_ADDR(base)             ((base) + (0x27C))

/* �Ĵ���˵����G3D AVS�����Ĵ���2��
   λ����UNION�ṹ:  SOC_PMCTRL_G3DAVSPARA2_UNION */
#define SOC_PMCTRL_G3DAVSPARA2_ADDR(base)             ((base) + (0x280))

/* �Ĵ���˵����G3D AVS�����Ĵ���3��
   λ����UNION�ṹ:  SOC_PMCTRL_G3DAVSPARA3_UNION */
#define SOC_PMCTRL_G3DAVSPARA3_ADDR(base)             ((base) + (0x284))

/* �Ĵ���˵����G3D AVS�����Ĵ���4��
   λ����UNION�ṹ:  SOC_PMCTRL_G3DAVSPARA4_UNION */
#define SOC_PMCTRL_G3DAVSPARA4_ADDR(base)             ((base) + (0x288))

/* �Ĵ���˵����G3D AVS�����Ĵ���5��
   λ����UNION�ṹ:  SOC_PMCTRL_G3DAVSPARA5_UNION */
#define SOC_PMCTRL_G3DAVSPARA5_ADDR(base)             ((base) + (0x28C))

/* �Ĵ���˵����G3D AVS�����Ĵ���6��
   λ����UNION�ṹ:  SOC_PMCTRL_G3DAVSPARA6_UNION */
#define SOC_PMCTRL_G3DAVSPARA6_ADDR(base)             ((base) + (0x290))

/* �Ĵ���˵����G3D HPM����ѡ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DHPMTYP_UNION */
#define SOC_PMCTRL_G3DHPMTYP_ADDR(base)               ((base) + (0x294))

/* �Ĵ���˵����G3D HPMʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DHPMEN_UNION */
#define SOC_PMCTRL_G3DHPMEN_ADDR(base)                ((base) + (0x298))

/* �Ĵ���˵����G3D HPMXʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DHPMXEN_UNION */
#define SOC_PMCTRL_G3DHPMXEN_ADDR(base)               ((base) + (0x29C))

/* �Ĵ���˵����G3D HPM OPC��Ч�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DHPMOPCVALID_UNION */
#define SOC_PMCTRL_G3DHPMOPCVALID_ADDR(base)          ((base) + (0x2A0))

/* �Ĵ���˵����G3D HPM OPC�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DHPMOPC_UNION */
#define SOC_PMCTRL_G3DHPMOPC_ADDR(base)               ((base) + (0x2A4))

/* �Ĵ���˵����G3D HPMX OPC�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DHPMXOPC_UNION */
#define SOC_PMCTRL_G3DHPMXOPC_ADDR(base)              ((base) + (0x2A8))

/* �Ĵ���˵����G3D HPM PC�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DHPMPC_UNION */
#define SOC_PMCTRL_G3DHPMPC_ADDR(base)                ((base) + (0x2AC))

/* �Ĵ���˵����G3D HPMʹ�ܼĴ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_G3DHPMEN1_UNION */
#define SOC_PMCTRL_G3DHPMEN1_ADDR(base)               ((base) + (0x2B4))

/* �Ĵ���˵����G3D HPMXʹ�ܼĴ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_G3DHPMXEN1_UNION */
#define SOC_PMCTRL_G3DHPMXEN1_ADDR(base)              ((base) + (0x2B8))

/* �Ĵ���˵����G3D HPM OPC��Ч�Ĵ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_G3DHPMOPCVALID1_UNION */
#define SOC_PMCTRL_G3DHPMOPCVALID1_ADDR(base)         ((base) + (0x2BC))

/* �Ĵ���˵����G3D HPM OPC�Ĵ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_G3DHPMOPC1_UNION */
#define SOC_PMCTRL_G3DHPMOPC1_ADDR(base)              ((base) + (0x2C0))

/* �Ĵ���˵����G3D HPMX OPC�Ĵ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_G3DHPMXOPC1_UNION */
#define SOC_PMCTRL_G3DHPMXOPC1_ADDR(base)             ((base) + (0x2C4))

/* �Ĵ���˵����G3D HPM PC�Ĵ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_G3DHPMPC1_UNION */
#define SOC_PMCTRL_G3DHPMPC1_ADDR(base)               ((base) + (0x2C8))

/* �Ĵ���˵����G3D HPM����״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DHPMMASKSTAT_UNION */
#define SOC_PMCTRL_G3DHPMMASKSTAT_ADDR(base)          ((base) + (0x2E8))

/* �Ĵ���˵����G3D HPMʱ�ӷ�Ƶ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DHPMCLKDIV_UNION */
#define SOC_PMCTRL_G3DHPMCLKDIV_ADDR(base)            ((base) + (0x2EC))

/* �Ĵ���˵����G3D AVS��ѹ���ƼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DAVSVOLIDX_UNION */
#define SOC_PMCTRL_G3DAVSVOLIDX_ADDR(base)            ((base) + (0x2F0))

/* �Ĵ���˵����DDRC LP���ƼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_DDRLPCTRL_UNION */
#define SOC_PMCTRL_DDRLPCTRL_ADDR(base)               ((base) + (0x30C))

/* �Ĵ���˵����PLL Lock�ȶ�ʱ��Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_PLLLOCKTIME_UNION */
#define SOC_PMCTRL_PLLLOCKTIME_ADDR(base)             ((base) + (0x320))

/* �Ĵ���˵����PLL�ȶ�ģʽ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_PLLLOCKMOD_UNION */
#define SOC_PMCTRL_PLLLOCKMOD_ADDR(base)              ((base) + (0x324))

/* �Ĵ���˵����AVS���������Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_AVSRUNROUND_UNION */
#define SOC_PMCTRL_AVSRUNROUND_ADDR(base)             ((base) + (0x32C))

/* �Ĵ���˵����PMUSSI AVSʹ���źš�
   λ����UNION�ṹ:  SOC_PMCTRL_PMUSSIAVSEN_UNION */
#define SOC_PMCTRL_PMUSSIAVSEN_ADDR(base)             ((base) + (0x330))

/* �Ĵ���˵��������ͨ�ÿ��ƼĴ���0��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_CTRL0_UNION */
#define SOC_PMCTRL_PERI_CTRL0_ADDR(base)              ((base) + (0x340))

/* �Ĵ���˵��������ͨ�ÿ��ƼĴ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_CTRL1_UNION */
#define SOC_PMCTRL_PERI_CTRL1_ADDR(base)              ((base) + (0x344))

/* �Ĵ���˵��������ͨ�ÿ��ƼĴ���2��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_CTRL2_UNION */
#define SOC_PMCTRL_PERI_CTRL2_ADDR(base)              ((base) + (0x348))

/* �Ĵ���˵��������ͨ�ÿ��ƼĴ���3��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_CTRL3_UNION */
#define SOC_PMCTRL_PERI_CTRL3_ADDR(base)              ((base) + (0x34C))

/* �Ĵ���˵��������ͨ�ÿ��ƼĴ���4��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_CTRL4_UNION */
#define SOC_PMCTRL_PERI_CTRL4_ADDR(base)              ((base) + (0x350))

/* �Ĵ���˵��������ͨ�ÿ��ƼĴ���5��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_CTRL5_UNION */
#define SOC_PMCTRL_PERI_CTRL5_ADDR(base)              ((base) + (0x354))

/* �Ĵ���˵��������ͨ�ÿ��ƼĴ���6��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_CTRL6_UNION */
#define SOC_PMCTRL_PERI_CTRL6_ADDR(base)              ((base) + (0x358))

/* �Ĵ���˵��������ͨ�ÿ��ƼĴ���7��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_CTRL7_UNION */
#define SOC_PMCTRL_PERI_CTRL7_ADDR(base)              ((base) + (0x35C))

/* �Ĵ���˵��������ͨ��״̬�Ĵ���0��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_STAT0_UNION */
#define SOC_PMCTRL_PERI_STAT0_ADDR(base)              ((base) + (0x360))

/* �Ĵ���˵��������ͨ��״̬�Ĵ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_STAT1_UNION */
#define SOC_PMCTRL_PERI_STAT1_ADDR(base)              ((base) + (0x364))

/* �Ĵ���˵��������ͨ��״̬�Ĵ���2��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_STAT2_UNION */
#define SOC_PMCTRL_PERI_STAT2_ADDR(base)              ((base) + (0x368))

/* �Ĵ���˵��������ͨ��״̬�Ĵ���3��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_STAT3_UNION */
#define SOC_PMCTRL_PERI_STAT3_ADDR(base)              ((base) + (0x36C))

/* �Ĵ���˵��������ͨ��״̬�Ĵ���4��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_STAT4_UNION */
#define SOC_PMCTRL_PERI_STAT4_ADDR(base)              ((base) + (0x370))

/* �Ĵ���˵��������ͨ��״̬�Ĵ���5��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_STAT5_UNION */
#define SOC_PMCTRL_PERI_STAT5_ADDR(base)              ((base) + (0x374))

/* �Ĵ���˵��������ͨ��״̬�Ĵ���6��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_STAT6_UNION */
#define SOC_PMCTRL_PERI_STAT6_ADDR(base)              ((base) + (0x378))

/* �Ĵ���˵��������ͨ��״̬�Ĵ���7��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_STAT7_UNION */
#define SOC_PMCTRL_PERI_STAT7_ADDR(base)              ((base) + (0x37C))

/* �Ĵ���˵����NOC�͹��������źżĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_NOC_POWER_IDLEREQ_UNION */
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_ADDR(base)       ((base) + (0x380))

/* �Ĵ���˵����NOC�͹�����Ӧ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_NOC_POWER_IDLEACK_UNION */
#define SOC_PMCTRL_NOC_POWER_IDLEACK_ADDR(base)       ((base) + (0x384))

/* �Ĵ���˵����NOC�͹���״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_NOC_POWER_IDLE_UNION */
#define SOC_PMCTRL_NOC_POWER_IDLE_ADDR(base)          ((base) + (0x388))

/* �Ĵ���˵���������ж����μĴ���0��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_INT0_MASK_UNION */
#define SOC_PMCTRL_PERI_INT0_MASK_ADDR(base)          ((base) + (0x3A0))

/* �Ĵ���˵���������ж�״̬�Ĵ���0��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_INT0_STAT_UNION */
#define SOC_PMCTRL_PERI_INT0_STAT_ADDR(base)          ((base) + (0x3A4))

/* �Ĵ���˵���������ж����μĴ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_INT1_MASK_UNION */
#define SOC_PMCTRL_PERI_INT1_MASK_ADDR(base)          ((base) + (0x3A8))

/* �Ĵ���˵���������ж����μĴ���2��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_INT1_STAT_UNION */
#define SOC_PMCTRL_PERI_INT1_STAT_ADDR(base)          ((base) + (0x3AC))

/* �Ĵ���˵���������ж����μĴ���3��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_INT2_MASK_UNION */
#define SOC_PMCTRL_PERI_INT2_MASK_ADDR(base)          ((base) + (0x3B0))

/* �Ĵ���˵���������ж�״̬�Ĵ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_INT2_STAT_UNION */
#define SOC_PMCTRL_PERI_INT2_STAT_ADDR(base)          ((base) + (0x3B4))

/* �Ĵ���˵���������ж�״̬�Ĵ���2��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_INT3_MASK_UNION */
#define SOC_PMCTRL_PERI_INT3_MASK_ADDR(base)          ((base) + (0x3B8))

/* �Ĵ���˵���������ж�״̬�Ĵ���3��
   λ����UNION�ṹ:  SOC_PMCTRL_PERI_INT3_STAT_UNION */
#define SOC_PMCTRL_PERI_INT3_STAT_ADDR(base)          ((base) + (0x3BC))

/* �Ĵ���˵����Vsensor����ʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_CTRL_EN_0_UNION */
#define SOC_PMCTRL_VS_CTRL_EN_0_ADDR(base)            ((base) + (0x3D0))

/* �Ĵ���˵����Vsensor bypass�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_CTRL_BYPASS_0_UNION */
#define SOC_PMCTRL_VS_CTRL_BYPASS_0_ADDR(base)        ((base) + (0x3D4))

/* �Ĵ���˵����Vsensor�������üĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_CTRL_0_UNION */
#define SOC_PMCTRL_VS_CTRL_0_ADDR(base)               ((base) + (0x3D8))

/* �Ĵ���˵����Vsensor�������ƼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_CNT_0_UNION */
#define SOC_PMCTRL_VS_CNT_0_ADDR(base)                ((base) + (0x3DC))

/* �Ĵ���˵����Vsensor�ο����ּĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_REF_CODE_0_UNION */
#define SOC_PMCTRL_VS_REF_CODE_0_ADDR(base)           ((base) + (0x3E0))

/* �Ĵ���˵����Vsensor��ͷ���ƼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_CALI_CODE_0_UNION */
#define SOC_PMCTRL_VS_CALI_CODE_0_ADDR(base)          ((base) + (0x3E4))

/* �Ĵ���˵����Vsensor���ּĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_CODE_0_UNION */
#define SOC_PMCTRL_VS_CODE_0_ADDR(base)               ((base) + (0x3E8))

/* �Ĵ���˵����Vsensor�ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_INTSTAT_0_UNION */
#define SOC_PMCTRL_VS_INTSTAT_0_ADDR(base)            ((base) + (0x3EC))

/* �Ĵ���˵����Vsensor�������üĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_SVFD_CTRL0_0_UNION */
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_ADDR(base)         ((base) + (0x3F0))

/* �Ĵ���˵����Vsensor�������üĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_SVFD_CTRL1_0_UNION */
#define SOC_PMCTRL_VS_SVFD_CTRL1_0_ADDR(base)         ((base) + (0x3F4))

/* �Ĵ���˵����Vsensor����ʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_CTRL_EN_1_UNION */
#define SOC_PMCTRL_VS_CTRL_EN_1_ADDR(base)            ((base) + (0x3F8))

/* �Ĵ���˵����Vsensor bypass�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_CTRL_BYPASS_1_UNION */
#define SOC_PMCTRL_VS_CTRL_BYPASS_1_ADDR(base)        ((base) + (0x3FC))

/* �Ĵ���˵����Vsensor�������üĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_CTRL_1_UNION */
#define SOC_PMCTRL_VS_CTRL_1_ADDR(base)               ((base) + (0x400))

/* �Ĵ���˵����Vsensor�������ƼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_CNT_1_UNION */
#define SOC_PMCTRL_VS_CNT_1_ADDR(base)                ((base) + (0x404))

/* �Ĵ���˵����Vsensor�ο����ּĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_REF_CODE_1_UNION */
#define SOC_PMCTRL_VS_REF_CODE_1_ADDR(base)           ((base) + (0x408))

/* �Ĵ���˵����Vsensor��ͷ���ƼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_CALI_CODE_1_UNION */
#define SOC_PMCTRL_VS_CALI_CODE_1_ADDR(base)          ((base) + (0x40C))

/* �Ĵ���˵����Vsensor���ּĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_CODE_1_UNION */
#define SOC_PMCTRL_VS_CODE_1_ADDR(base)               ((base) + (0x410))

/* �Ĵ���˵����Vsensor�ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_INTSTAT_1_UNION */
#define SOC_PMCTRL_VS_INTSTAT_1_ADDR(base)            ((base) + (0x414))

/* �Ĵ���˵����Vsensor�������üĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_SVFD_CTRL0_1_UNION */
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_ADDR(base)         ((base) + (0x418))

/* �Ĵ���˵����Vsensor�������üĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_SVFD_CTRL1_1_UNION */
#define SOC_PMCTRL_VS_SVFD_CTRL1_1_ADDR(base)         ((base) + (0x41C))

/* �Ĵ���˵����PERI HPMʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_PERIHPMEN_UNION */
#define SOC_PMCTRL_PERIHPMEN_ADDR(base)               ((base) + (0x430))

/* �Ĵ���˵����PERI HPMXʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_PERIHPMXEN_UNION */
#define SOC_PMCTRL_PERIHPMXEN_ADDR(base)              ((base) + (0x434))

/* �Ĵ���˵����PERI HPM OPC��Ч�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_PERIHPMOPCVALID_UNION */
#define SOC_PMCTRL_PERIHPMOPCVALID_ADDR(base)         ((base) + (0x438))

/* �Ĵ���˵����PERI HPM OPC�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_PERIHPMOPC_UNION */
#define SOC_PMCTRL_PERIHPMOPC_ADDR(base)              ((base) + (0x43C))

/* �Ĵ���˵����PERI HPMʱ�ӷ�Ƶ�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_PERIHPMCLKDIV_UNION */
#define SOC_PMCTRL_PERIHPMCLKDIV_ADDR(base)           ((base) + (0x440))

/* �Ĵ���˵����BOOTROM FLAG�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_BOOTROMFLAG_UNION */
#define SOC_PMCTRL_BOOTROMFLAG_ADDR(base)             ((base) + (0x460))

/* �Ĵ���˵����Vsensor����ʹ�ܼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_CTRL_EN_2_UNION */
#define SOC_PMCTRL_VS_CTRL_EN_2_ADDR(base)            ((base) + (0x464))

/* �Ĵ���˵����Vsensor bypass�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_CTRL_BYPASS_2_UNION */
#define SOC_PMCTRL_VS_CTRL_BYPASS_2_ADDR(base)        ((base) + (0x468))

/* �Ĵ���˵����Vsensor�������üĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_CTRL_2_UNION */
#define SOC_PMCTRL_VS_CTRL_2_ADDR(base)               ((base) + (0x46C))

/* �Ĵ���˵����Vsensor�������ƼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_CNT_2_UNION */
#define SOC_PMCTRL_VS_CNT_2_ADDR(base)                ((base) + (0x470))

/* �Ĵ���˵����Vsensor�ο����ּĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_REF_CODE_2_UNION */
#define SOC_PMCTRL_VS_REF_CODE_2_ADDR(base)           ((base) + (0x474))

/* �Ĵ���˵����Vsensor��ͷ���ƼĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_CALI_CODE_2_UNION */
#define SOC_PMCTRL_VS_CALI_CODE_2_ADDR(base)          ((base) + (0x47C))

/* �Ĵ���˵����Vsensor���ּĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_CODE_2_UNION */
#define SOC_PMCTRL_VS_CODE_2_ADDR(base)               ((base) + (0x480))

/* �Ĵ���˵����Vsensor�ж�״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_INTSTAT_2_UNION */
#define SOC_PMCTRL_VS_INTSTAT_2_ADDR(base)            ((base) + (0x484))

/* �Ĵ���˵����Vsensor�������üĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_SVFD_CTRL0_2_UNION */
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_ADDR(base)         ((base) + (0x48C))

/* �Ĵ���˵����Vsensor�������üĴ�����
   λ����UNION�ṹ:  SOC_PMCTRL_VS_SVFD_CTRL1_2_UNION */
#define SOC_PMCTRL_VS_SVFD_CTRL1_2_ADDR(base)         ((base) + (0x490))

/* �Ĵ���˵����APLL0����״̬�Ĵ���0��
   λ����UNION�ṹ:  SOC_PMCTRL_APLL0CTRL0_STAT_UNION */
#define SOC_PMCTRL_APLL0CTRL0_STAT_ADDR(base)         ((base) + (0x494))

/* �Ĵ���˵����APLL0����״̬�Ĵ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_APLL0CTRL1_STAT_UNION */
#define SOC_PMCTRL_APLL0CTRL1_STAT_ADDR(base)         ((base) + (0x498))

/* �Ĵ���˵����APLL1����״̬�Ĵ���0��
   λ����UNION�ṹ:  SOC_PMCTRL_APLL1CTRL0_STAT_UNION */
#define SOC_PMCTRL_APLL1CTRL0_STAT_ADDR(base)         ((base) + (0x49C))

/* �Ĵ���˵����APLL1����״̬�Ĵ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_APLL1CTRL1_STAT_UNION */
#define SOC_PMCTRL_APLL1CTRL1_STAT_ADDR(base)         ((base) + (0x4A0))

/* �Ĵ���˵����APLL2����״̬�Ĵ���0��
   λ����UNION�ṹ:  SOC_PMCTRL_APLL2CTRL0_STAT_UNION */
#define SOC_PMCTRL_APLL2CTRL0_STAT_ADDR(base)         ((base) + (0x4A4))

/* �Ĵ���˵����APLL2����״̬�Ĵ���1��
   λ����UNION�ṹ:  SOC_PMCTRL_APLL2CTRL1_STAT_UNION */
#define SOC_PMCTRL_APLL2CTRL1_STAT_ADDR(base)         ((base) + (0x4A8))

/* �Ĵ���˵����G3D AXIʱ�ӷ�Ƶ״̬�Ĵ�����
   λ����UNION�ṹ:  SOC_PMCTRL_G3DCLKDIV_STAT_UNION */
#define SOC_PMCTRL_G3DCLKDIV_STAT_ADDR(base)          ((base) + (0x4AC))





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
                     (1/1) reg_define
 ****************************************************************************/
/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PMCINTEN_UNION
 �ṹ˵��  : PMCINTEN �Ĵ����ṹ���塣��ַƫ����:0x000����ֵ:0x00000000�����:32
 �Ĵ���˵��: PMC�ж�ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_cluster0_cpu_dvfs_en       : 1;  /* bit[0-0]  : Cluster0_ DVFS����ж�ʹ�ܡ�
                                                                          0���ж����Σ�
                                                                          1���ж�ʹ�ܡ� */
        unsigned int  int_cluster0_cpu_avs_ok_en     : 1;  /* bit[1-1]  : Cluster0 AVS��ѹOK�ж�ʹ�ܡ�
                                                                          0���ж����Σ�
                                                                          1���ж�ʹ�ܡ� */
        unsigned int  int_cluster0_cpu_avs_up_err_en : 1;  /* bit[2-2]  : Cluster0 AVS������ѹ�����ж�ʹ�ܡ�
                                                                          0���ж����Σ�
                                                                          1���ж�ʹ�ܡ� */
        unsigned int  int_cluster0_cpu_avs_dn_err_en : 1;  /* bit[3-3]  : Cluster0 AVS���͵�ѹ�����ж�ʹ�ܡ�
                                                                          0���ж����Σ�
                                                                          1���ж�ʹ�ܡ� */
        unsigned int  int_cluster0_cpu_avs_pc_vld_en : 1;  /* bit[4-4]  : Cluster0 AVS���PC�ж�ʹ�ܡ�
                                                                          0���ж����Σ�
                                                                          1���ж�ʹ�ܡ� */
        unsigned int  int_cluster0_cpu_avs_idle_en   : 1;  /* bit[5-5]  : Cluster0 CPU AVS IDLE�ж�ʹ�ܡ�
                                                                          0���ж����Σ�
                                                                          1���ж�ʹ�ܡ� */
        unsigned int  int_cluster1_cpu_dvfs_en       : 1;  /* bit[6-6]  : Cluster1_ DVFS����ж�ʹ�ܡ�
                                                                          0���ж����Σ�
                                                                          1���ж�ʹ�ܡ� */
        unsigned int  int_cluster1_cpu_avs_ok_en     : 1;  /* bit[7-7]  : Cluster1 AVS��ѹOK�ж�ʹ�ܡ�
                                                                          0���ж����Σ�
                                                                          1���ж�ʹ�ܡ� */
        unsigned int  int_cluster1_cpu_avs_up_err_en : 1;  /* bit[8-8]  : Cluster1 AVS������ѹ�����ж�ʹ�ܡ�
                                                                          0���ж����Σ�
                                                                          1���ж�ʹ�ܡ� */
        unsigned int  int_cluster1_cpu_avs_dn_err_en : 1;  /* bit[9-9]  : Cluster1 AVS���͵�ѹ�����ж�ʹ�ܡ�
                                                                          0���ж����Σ�
                                                                          1���ж�ʹ�ܡ� */
        unsigned int  int_cluster1_cpu_avs_pc_vld_en : 1;  /* bit[10-10]: Cluster1 AVS���PC�ж�ʹ�ܡ�
                                                                          0���ж����Σ�
                                                                          1���ж�ʹ�ܡ� */
        unsigned int  int_cluster1_cpu_avs_idle_en   : 1;  /* bit[11-11]: Cluster1 CPU AVS IDLE�ж�ʹ�ܡ�
                                                                          0���ж����Σ�
                                                                          1���ж�ʹ�ܡ� */
        unsigned int  int_g3d_dvfs_en                : 1;  /* bit[12-12]: G3D DVFS����ж�ʹ�ܡ�
                                                                          0���ж����Σ�
                                                                          1���ж�ʹ�ܡ� */
        unsigned int  int_g3d_avs_ok_en              : 1;  /* bit[13-13]: G3D AVS��ѹOK�ж�ʹ�ܡ�
                                                                          0���ж����Σ�
                                                                          1���ж�ʹ�ܡ� */
        unsigned int  int_g3d_avs_up_err_en          : 1;  /* bit[14-14]: G3D AVS������ѹ�����ж�ʹ�ܡ�
                                                                          0���ж����Σ�
                                                                          1���ж�ʹ�ܡ� */
        unsigned int  int_g3d_avs_dn_err_en          : 1;  /* bit[15-15]: G3D AVS���͵�ѹ�����ж�ʹ�ܡ�
                                                                          0���ж����Σ�
                                                                          1���ж�ʹ�ܡ� */
        unsigned int  int_g3d_avs_pc_vld_en          : 1;  /* bit[16-16]: G3D AVS���PC�ж�ʹ�ܡ�
                                                                          0���ж����Σ�
                                                                          1���ж�ʹ�ܡ� */
        unsigned int  int_g3d_avs_idle_en            : 1;  /* bit[17-17]: G3D AVS IDLE�ж�ʹ�ܡ�
                                                                          0���ж����Σ�
                                                                          1���ж�ʹ�ܡ� */
        unsigned int  reserved                       : 14; /* bit[18-31]: ������ */
    } reg;
} SOC_PMCTRL_PMCINTEN_UNION;
#endif
#define SOC_PMCTRL_PMCINTEN_int_cluster0_cpu_dvfs_en_START        (0)
#define SOC_PMCTRL_PMCINTEN_int_cluster0_cpu_dvfs_en_END          (0)
#define SOC_PMCTRL_PMCINTEN_int_cluster0_cpu_avs_ok_en_START      (1)
#define SOC_PMCTRL_PMCINTEN_int_cluster0_cpu_avs_ok_en_END        (1)
#define SOC_PMCTRL_PMCINTEN_int_cluster0_cpu_avs_up_err_en_START  (2)
#define SOC_PMCTRL_PMCINTEN_int_cluster0_cpu_avs_up_err_en_END    (2)
#define SOC_PMCTRL_PMCINTEN_int_cluster0_cpu_avs_dn_err_en_START  (3)
#define SOC_PMCTRL_PMCINTEN_int_cluster0_cpu_avs_dn_err_en_END    (3)
#define SOC_PMCTRL_PMCINTEN_int_cluster0_cpu_avs_pc_vld_en_START  (4)
#define SOC_PMCTRL_PMCINTEN_int_cluster0_cpu_avs_pc_vld_en_END    (4)
#define SOC_PMCTRL_PMCINTEN_int_cluster0_cpu_avs_idle_en_START    (5)
#define SOC_PMCTRL_PMCINTEN_int_cluster0_cpu_avs_idle_en_END      (5)
#define SOC_PMCTRL_PMCINTEN_int_cluster1_cpu_dvfs_en_START        (6)
#define SOC_PMCTRL_PMCINTEN_int_cluster1_cpu_dvfs_en_END          (6)
#define SOC_PMCTRL_PMCINTEN_int_cluster1_cpu_avs_ok_en_START      (7)
#define SOC_PMCTRL_PMCINTEN_int_cluster1_cpu_avs_ok_en_END        (7)
#define SOC_PMCTRL_PMCINTEN_int_cluster1_cpu_avs_up_err_en_START  (8)
#define SOC_PMCTRL_PMCINTEN_int_cluster1_cpu_avs_up_err_en_END    (8)
#define SOC_PMCTRL_PMCINTEN_int_cluster1_cpu_avs_dn_err_en_START  (9)
#define SOC_PMCTRL_PMCINTEN_int_cluster1_cpu_avs_dn_err_en_END    (9)
#define SOC_PMCTRL_PMCINTEN_int_cluster1_cpu_avs_pc_vld_en_START  (10)
#define SOC_PMCTRL_PMCINTEN_int_cluster1_cpu_avs_pc_vld_en_END    (10)
#define SOC_PMCTRL_PMCINTEN_int_cluster1_cpu_avs_idle_en_START    (11)
#define SOC_PMCTRL_PMCINTEN_int_cluster1_cpu_avs_idle_en_END      (11)
#define SOC_PMCTRL_PMCINTEN_int_g3d_dvfs_en_START                 (12)
#define SOC_PMCTRL_PMCINTEN_int_g3d_dvfs_en_END                   (12)
#define SOC_PMCTRL_PMCINTEN_int_g3d_avs_ok_en_START               (13)
#define SOC_PMCTRL_PMCINTEN_int_g3d_avs_ok_en_END                 (13)
#define SOC_PMCTRL_PMCINTEN_int_g3d_avs_up_err_en_START           (14)
#define SOC_PMCTRL_PMCINTEN_int_g3d_avs_up_err_en_END             (14)
#define SOC_PMCTRL_PMCINTEN_int_g3d_avs_dn_err_en_START           (15)
#define SOC_PMCTRL_PMCINTEN_int_g3d_avs_dn_err_en_END             (15)
#define SOC_PMCTRL_PMCINTEN_int_g3d_avs_pc_vld_en_START           (16)
#define SOC_PMCTRL_PMCINTEN_int_g3d_avs_pc_vld_en_END             (16)
#define SOC_PMCTRL_PMCINTEN_int_g3d_avs_idle_en_START             (17)
#define SOC_PMCTRL_PMCINTEN_int_g3d_avs_idle_en_END               (17)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PMCINTSTAT_UNION
 �ṹ˵��  : PMCINTSTAT �Ĵ����ṹ���塣��ַƫ����:0x004����ֵ:0x00000000�����:32
 �Ĵ���˵��: PMC�ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_cluster0_cpu_dvfs_stat       : 1;  /* bit[0-0]  : Cluster0_ DVFS����жϡ�
                                                                            0���ж���Ч��
                                                                            1���ж���Ч�� */
        unsigned int  int_cluster0_cpu_avs_ok_stat     : 1;  /* bit[1-1]  : Cluster0 AVS��ѹOK�жϡ�
                                                                            0���ж���Ч��
                                                                            1���ж���Ч�� */
        unsigned int  int_cluster0_cpu_avs_up_err_stat : 1;  /* bit[2-2]  : Cluster0 AVS������ѹ�����жϡ�
                                                                            0���ж���Ч��
                                                                            1���ж���Ч�� */
        unsigned int  int_cluster0_cpu_avs_dn_err_stat : 1;  /* bit[3-3]  : Cluster0 AVS���͵�ѹ�����жϡ�
                                                                            0���ж���Ч��
                                                                            1���ж���Ч�� */
        unsigned int  int_cluster0_cpu_avs_pc_vld_stat : 1;  /* bit[4-4]  : Cluster0 AVS���PC�жϡ�
                                                                            0���ж���Ч��
                                                                            1���ж���Ч�� */
        unsigned int  int_cluster0_cpu_avs_idle_stat   : 1;  /* bit[5-5]  : Cluster0 CPU AVS IDLE�жϡ�
                                                                            0���ж���Ч��
                                                                            1���ж���Ч�� */
        unsigned int  int_cluster1_cpu_dvfs_stat       : 1;  /* bit[6-6]  : Cluster1_ DVFS����жϡ�
                                                                            0���ж���Ч��
                                                                            1���ж���Ч�� */
        unsigned int  int_cluster1_cpu_avs_ok_stat     : 1;  /* bit[7-7]  : Cluster1 AVS��ѹOK�жϡ�
                                                                            0���ж���Ч��
                                                                            1���ж���Ч�� */
        unsigned int  int_cluster1_cpu_avs_up_err_stat : 1;  /* bit[8-8]  : Cluster1 AVS������ѹ�����жϡ�
                                                                            0���ж���Ч��
                                                                            1���ж���Ч�� */
        unsigned int  int_cluster1_cpu_avs_dn_err_stat : 1;  /* bit[9-9]  : Cluster1 AVS���͵�ѹ�����жϡ�
                                                                            0���ж���Ч��
                                                                            1���ж���Ч�� */
        unsigned int  int_cluster1_cpu_avs_pc_vld_stat : 1;  /* bit[10-10]: Cluster1 AVS���PC�жϡ�
                                                                            0���ж���Ч��
                                                                            1���ж���Ч�� */
        unsigned int  int_cluster1_cpu_avs_idle_stat   : 1;  /* bit[11-11]: Cluster1 CPU AVS IDLE�жϡ�
                                                                            0���ж���Ч��
                                                                            1���ж���Ч�� */
        unsigned int  int_g3d_dvfs_stat                : 1;  /* bit[12-12]: G3D DVFS����жϡ�
                                                                            0���ж���Ч��
                                                                            1���ж���Ч�� */
        unsigned int  int_g3d_avs_ok_stat              : 1;  /* bit[13-13]: G3D AVS��ѹOK�жϡ�
                                                                            0���ж���Ч��
                                                                            1���ж���Ч�� */
        unsigned int  int_g3d_avs_up_err_stat          : 1;  /* bit[14-14]: G3D AVS������ѹ�����жϡ�
                                                                            0���ж���Ч��
                                                                            1���ж���Ч�� */
        unsigned int  int_g3d_avs_dn_err_stat          : 1;  /* bit[15-15]: G3D AVS���͵�ѹ�����жϡ�
                                                                            0���ж���Ч��
                                                                            1���ж���Ч�� */
        unsigned int  int_g3d_avs_pc_vld_stat          : 1;  /* bit[16-16]: G3D AVS���PC�жϡ�
                                                                            0���ж���Ч��
                                                                            1���ж���Ч�� */
        unsigned int  int_g3d_avs_idle_stat            : 1;  /* bit[17-17]: G3D AVS IDLE�жϡ�
                                                                            0���ж���Ч��
                                                                            1���ж���Ч�� */
        unsigned int  reserved                         : 14; /* bit[18-31]: ������ */
    } reg;
} SOC_PMCTRL_PMCINTSTAT_UNION;
#endif
#define SOC_PMCTRL_PMCINTSTAT_int_cluster0_cpu_dvfs_stat_START        (0)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster0_cpu_dvfs_stat_END          (0)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster0_cpu_avs_ok_stat_START      (1)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster0_cpu_avs_ok_stat_END        (1)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster0_cpu_avs_up_err_stat_START  (2)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster0_cpu_avs_up_err_stat_END    (2)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster0_cpu_avs_dn_err_stat_START  (3)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster0_cpu_avs_dn_err_stat_END    (3)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster0_cpu_avs_pc_vld_stat_START  (4)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster0_cpu_avs_pc_vld_stat_END    (4)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster0_cpu_avs_idle_stat_START    (5)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster0_cpu_avs_idle_stat_END      (5)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster1_cpu_dvfs_stat_START        (6)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster1_cpu_dvfs_stat_END          (6)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster1_cpu_avs_ok_stat_START      (7)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster1_cpu_avs_ok_stat_END        (7)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster1_cpu_avs_up_err_stat_START  (8)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster1_cpu_avs_up_err_stat_END    (8)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster1_cpu_avs_dn_err_stat_START  (9)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster1_cpu_avs_dn_err_stat_END    (9)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster1_cpu_avs_pc_vld_stat_START  (10)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster1_cpu_avs_pc_vld_stat_END    (10)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster1_cpu_avs_idle_stat_START    (11)
#define SOC_PMCTRL_PMCINTSTAT_int_cluster1_cpu_avs_idle_stat_END      (11)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_dvfs_stat_START                 (12)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_dvfs_stat_END                   (12)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_avs_ok_stat_START               (13)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_avs_ok_stat_END                 (13)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_avs_up_err_stat_START           (14)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_avs_up_err_stat_END             (14)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_avs_dn_err_stat_START           (15)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_avs_dn_err_stat_END             (15)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_avs_pc_vld_stat_START           (16)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_avs_pc_vld_stat_END             (16)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_avs_idle_stat_START             (17)
#define SOC_PMCTRL_PMCINTSTAT_int_g3d_avs_idle_stat_END               (17)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PMCINTCLR_UNION
 �ṹ˵��  : PMCINTCLR �Ĵ����ṹ���塣��ַƫ����:0x008����ֵ:0x00000000�����:32
 �Ĵ���˵��: PMC�ж�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  int_cluster0_cpu_dvfs_clr       : 1;  /* bit[0-0]  : Cluster0_ DVFS����ж������
                                                                           0����Ч��
                                                                           1������жϡ� */
        unsigned int  int_cluster0_cpu_avs_ok_clr     : 1;  /* bit[1-1]  : Cluster0 AVS��ѹOK�ж������
                                                                           0����Ч��
                                                                           1������жϡ� */
        unsigned int  int_cluster0_cpu_avs_up_err_clr : 1;  /* bit[2-2]  : Cluster0 AVS������ѹ�����ж������
                                                                           0����Ч��
                                                                           1������жϡ� */
        unsigned int  int_cluster0_cpu_avs_dn_err_clr : 1;  /* bit[3-3]  : Cluster0 AVS���͵�ѹ�����ж������
                                                                           0����Ч��
                                                                           1������жϡ� */
        unsigned int  int_cluster0_cpu_avs_pc_vld_clr : 1;  /* bit[4-4]  : Cluster0 AVS���PC�ж������
                                                                           0����Ч��
                                                                           1������жϡ� */
        unsigned int  int_cluster0_cpu_avs_idle_clr   : 1;  /* bit[5-5]  : Cluster0 CPU AVS IDLE�ж������
                                                                           0����Ч��
                                                                           1������жϡ� */
        unsigned int  int_cluster1_cpu_dvfs_clr       : 1;  /* bit[6-6]  : Cluster1_ DVFS����ж������
                                                                           0����Ч��
                                                                           1������жϡ� */
        unsigned int  int_cluster1_cpu_avs_ok_clr     : 1;  /* bit[7-7]  : Cluster1 AVS��ѹOK�ж������
                                                                           0����Ч��
                                                                           1������жϡ� */
        unsigned int  int_cluster1_cpu_avs_up_err_clr : 1;  /* bit[8-8]  : Cluster1 AVS������ѹ�����ж������
                                                                           0����Ч��
                                                                           1������жϡ� */
        unsigned int  int_cluster1_cpu_avs_dn_err_clr : 1;  /* bit[9-9]  : Cluster1 AVS���͵�ѹ�����ж������
                                                                           0����Ч��
                                                                           1������жϡ� */
        unsigned int  int_cluster1_cpu_avs_pc_vld_clr : 1;  /* bit[10-10]: Cluster1 AVS���PC�ж������
                                                                           0����Ч��
                                                                           1������жϡ� */
        unsigned int  int_cluster1_cpu_avs_idle_clr   : 1;  /* bit[11-11]: Cluster1 CPU AVS IDLE�ж������
                                                                           0����Ч��
                                                                           1������жϡ� */
        unsigned int  int_g3d_dvfs_clr                : 1;  /* bit[12-12]: G3D DVFS����ж������
                                                                           0����Ч��
                                                                           1������жϡ� */
        unsigned int  int_g3d_avs_ok_clr              : 1;  /* bit[13-13]: G3D AVS��ѹOK�ж������
                                                                           0����Ч��
                                                                           1������жϡ� */
        unsigned int  int_g3d_avs_up_err_clr          : 1;  /* bit[14-14]: G3D AVS������ѹ�����ж������
                                                                           0����Ч��
                                                                           1������жϡ� */
        unsigned int  int_g3d_avs_dn_err_clr          : 1;  /* bit[15-15]: G3D AVS���͵�ѹ�����ж������
                                                                           0����Ч��
                                                                           1������жϡ� */
        unsigned int  int_g3d_avs_pc_vld_clr          : 1;  /* bit[16-16]: G3D AVS���PC�ж������
                                                                           0����Ч��
                                                                           1������жϡ� */
        unsigned int  int_g3d_avs_idle_clr            : 1;  /* bit[17-17]: G3D AVS IDLE�ж������
                                                                           0����Ч��
                                                                           1������жϡ� */
        unsigned int  reserved                        : 14; /* bit[18-31]: ������ */
    } reg;
} SOC_PMCTRL_PMCINTCLR_UNION;
#endif
#define SOC_PMCTRL_PMCINTCLR_int_cluster0_cpu_dvfs_clr_START        (0)
#define SOC_PMCTRL_PMCINTCLR_int_cluster0_cpu_dvfs_clr_END          (0)
#define SOC_PMCTRL_PMCINTCLR_int_cluster0_cpu_avs_ok_clr_START      (1)
#define SOC_PMCTRL_PMCINTCLR_int_cluster0_cpu_avs_ok_clr_END        (1)
#define SOC_PMCTRL_PMCINTCLR_int_cluster0_cpu_avs_up_err_clr_START  (2)
#define SOC_PMCTRL_PMCINTCLR_int_cluster0_cpu_avs_up_err_clr_END    (2)
#define SOC_PMCTRL_PMCINTCLR_int_cluster0_cpu_avs_dn_err_clr_START  (3)
#define SOC_PMCTRL_PMCINTCLR_int_cluster0_cpu_avs_dn_err_clr_END    (3)
#define SOC_PMCTRL_PMCINTCLR_int_cluster0_cpu_avs_pc_vld_clr_START  (4)
#define SOC_PMCTRL_PMCINTCLR_int_cluster0_cpu_avs_pc_vld_clr_END    (4)
#define SOC_PMCTRL_PMCINTCLR_int_cluster0_cpu_avs_idle_clr_START    (5)
#define SOC_PMCTRL_PMCINTCLR_int_cluster0_cpu_avs_idle_clr_END      (5)
#define SOC_PMCTRL_PMCINTCLR_int_cluster1_cpu_dvfs_clr_START        (6)
#define SOC_PMCTRL_PMCINTCLR_int_cluster1_cpu_dvfs_clr_END          (6)
#define SOC_PMCTRL_PMCINTCLR_int_cluster1_cpu_avs_ok_clr_START      (7)
#define SOC_PMCTRL_PMCINTCLR_int_cluster1_cpu_avs_ok_clr_END        (7)
#define SOC_PMCTRL_PMCINTCLR_int_cluster1_cpu_avs_up_err_clr_START  (8)
#define SOC_PMCTRL_PMCINTCLR_int_cluster1_cpu_avs_up_err_clr_END    (8)
#define SOC_PMCTRL_PMCINTCLR_int_cluster1_cpu_avs_dn_err_clr_START  (9)
#define SOC_PMCTRL_PMCINTCLR_int_cluster1_cpu_avs_dn_err_clr_END    (9)
#define SOC_PMCTRL_PMCINTCLR_int_cluster1_cpu_avs_pc_vld_clr_START  (10)
#define SOC_PMCTRL_PMCINTCLR_int_cluster1_cpu_avs_pc_vld_clr_END    (10)
#define SOC_PMCTRL_PMCINTCLR_int_cluster1_cpu_avs_idle_clr_START    (11)
#define SOC_PMCTRL_PMCINTCLR_int_cluster1_cpu_avs_idle_clr_END      (11)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_dvfs_clr_START                 (12)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_dvfs_clr_END                   (12)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_avs_ok_clr_START               (13)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_avs_ok_clr_END                 (13)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_avs_up_err_clr_START           (14)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_avs_up_err_clr_END             (14)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_avs_dn_err_clr_START           (15)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_avs_dn_err_clr_END             (15)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_avs_pc_vld_clr_START           (16)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_avs_pc_vld_clr_END             (16)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_avs_idle_clr_START             (17)
#define SOC_PMCTRL_PMCINTCLR_int_g3d_avs_idle_clr_END               (17)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PMCSTATUS_UNION
 �ṹ˵��  : PMCSTATUS �Ĵ����ṹ���塣��ַƫ����:0x00C����ֵ:0x00000000�����:32
 �Ĵ���˵��: PMC״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_dvfs_stat : 4;  /* bit[0-3]  : Cluster0_ CPU DVFS״̬����ǰ״̬�� */
        unsigned int  cluster0_cpu_avs_stat  : 6;  /* bit[4-9]  : Cluster0 CPU AVS״̬����ǰ״̬�� */
        unsigned int  cluster1_cpu_dvfs_stat : 4;  /* bit[10-13]: Cluster1_ CPU DVFS״̬����ǰ״̬�� */
        unsigned int  cluster1_cpu_avs_stat  : 6;  /* bit[14-19]: Cluster1 CPU AVS״̬����ǰ״̬�� */
        unsigned int  g3d_dvfs_stat          : 4;  /* bit[20-23]: G3D DVFS״̬����ǰ״̬�� */
        unsigned int  g3d_avs_stat           : 6;  /* bit[24-29]: G3D AVS״̬����ǰ״̬�� */
        unsigned int  reserved               : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_PMCTRL_PMCSTATUS_UNION;
#endif
#define SOC_PMCTRL_PMCSTATUS_cluster0_cpu_dvfs_stat_START  (0)
#define SOC_PMCTRL_PMCSTATUS_cluster0_cpu_dvfs_stat_END    (3)
#define SOC_PMCTRL_PMCSTATUS_cluster0_cpu_avs_stat_START   (4)
#define SOC_PMCTRL_PMCSTATUS_cluster0_cpu_avs_stat_END     (9)
#define SOC_PMCTRL_PMCSTATUS_cluster1_cpu_dvfs_stat_START  (10)
#define SOC_PMCTRL_PMCSTATUS_cluster1_cpu_dvfs_stat_END    (13)
#define SOC_PMCTRL_PMCSTATUS_cluster1_cpu_avs_stat_START   (14)
#define SOC_PMCTRL_PMCSTATUS_cluster1_cpu_avs_stat_END     (19)
#define SOC_PMCTRL_PMCSTATUS_g3d_dvfs_stat_START           (20)
#define SOC_PMCTRL_PMCSTATUS_g3d_dvfs_stat_END             (23)
#define SOC_PMCTRL_PMCSTATUS_g3d_avs_stat_START            (24)
#define SOC_PMCTRL_PMCSTATUS_g3d_avs_stat_END              (29)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_APLL0CTRL0_UNION
 �ṹ˵��  : APLL0CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x010����ֵ:0x00B03E06�����:32
 �Ĵ���˵��: APLL0���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll0_en_cfg       : 1;  /* bit[0-0]  : APLL0 PowerDown���ơ�
                                                              0���رգ�
                                                              1��ʹ�ܡ� */
        unsigned int  apll0_bp_cfg       : 1;  /* bit[1-1]  : APLL0 Bypass���ơ�
                                                              0������������
                                                              1��Bypass�� */
        unsigned int  apll0_refdiv_cfg   : 6;  /* bit[2-7]  : APLL0����ʱ�ӷ�Ƶ���� */
        unsigned int  apll0_fbdiv_cfg    : 12; /* bit[8-19] : APLL0����ʱ��������Ƶ���� */
        unsigned int  apll0_postdiv1_cfg : 3;  /* bit[20-22]: APLL0���ʱ�ӷ�Ƶ��1�� */
        unsigned int  apll0_postdiv2_cfg : 3;  /* bit[23-25]: APLL0���ʱ�ӷ�Ƶ��2�� */
        unsigned int  apll0_lock         : 1;  /* bit[26-26]: APLL0 Lockָʾ��
                                                              0����Ч��
                                                              1��APLL0 Lock�� */
        unsigned int  reserved           : 5;  /* bit[27-31]: ������ */
    } reg;
} SOC_PMCTRL_APLL0CTRL0_UNION;
#endif
#define SOC_PMCTRL_APLL0CTRL0_apll0_en_cfg_START        (0)
#define SOC_PMCTRL_APLL0CTRL0_apll0_en_cfg_END          (0)
#define SOC_PMCTRL_APLL0CTRL0_apll0_bp_cfg_START        (1)
#define SOC_PMCTRL_APLL0CTRL0_apll0_bp_cfg_END          (1)
#define SOC_PMCTRL_APLL0CTRL0_apll0_refdiv_cfg_START    (2)
#define SOC_PMCTRL_APLL0CTRL0_apll0_refdiv_cfg_END      (7)
#define SOC_PMCTRL_APLL0CTRL0_apll0_fbdiv_cfg_START     (8)
#define SOC_PMCTRL_APLL0CTRL0_apll0_fbdiv_cfg_END       (19)
#define SOC_PMCTRL_APLL0CTRL0_apll0_postdiv1_cfg_START  (20)
#define SOC_PMCTRL_APLL0CTRL0_apll0_postdiv1_cfg_END    (22)
#define SOC_PMCTRL_APLL0CTRL0_apll0_postdiv2_cfg_START  (23)
#define SOC_PMCTRL_APLL0CTRL0_apll0_postdiv2_cfg_END    (25)
#define SOC_PMCTRL_APLL0CTRL0_apll0_lock_START          (26)
#define SOC_PMCTRL_APLL0CTRL0_apll0_lock_END            (26)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_APLL0CTRL1_UNION
 �ṹ˵��  : APLL0CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x014����ֵ:0x06F80000�����:32
 �Ĵ���˵��: APLL0���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll0_fracdiv_cfg : 24; /* bit[0-23] : APLL0����ʱ�ӷ�����Ƶ���� */
        unsigned int  apll0_int_mod_cfg : 1;  /* bit[24-24]: APLL0������Ƶģʽ��
                                                             0��������Ƶģʽ��
                                                             1��������Ƶģʽ��
                                                             ע�⣺��PLL֧�ַ�����Ƶ��������Ƶģʽ������SSC��ʱ��Ҫ�����ֻʹ�÷�����Ƶģʽ�� */
        unsigned int  apll0_cfg_vld_cfg : 1;  /* bit[25-25]: APLL0������Ч��־��
                                                             0��������Ч��
                                                             1��������Ч�� */
        unsigned int  gt_clk_apll0_cfg  : 1;  /* bit[26-26]: APLL0�ſ��źš�
                                                             0��APLL0���ʱ���ſأ�
                                                             1��APLL0���ʱ�Ӳ��ſء����ȴ�PLL�ȶ���������ø�bit���� */
        unsigned int  reserved          : 5;  /* bit[27-31]: ������ */
    } reg;
} SOC_PMCTRL_APLL0CTRL1_UNION;
#endif
#define SOC_PMCTRL_APLL0CTRL1_apll0_fracdiv_cfg_START  (0)
#define SOC_PMCTRL_APLL0CTRL1_apll0_fracdiv_cfg_END    (23)
#define SOC_PMCTRL_APLL0CTRL1_apll0_int_mod_cfg_START  (24)
#define SOC_PMCTRL_APLL0CTRL1_apll0_int_mod_cfg_END    (24)
#define SOC_PMCTRL_APLL0CTRL1_apll0_cfg_vld_cfg_START  (25)
#define SOC_PMCTRL_APLL0CTRL1_apll0_cfg_vld_cfg_END    (25)
#define SOC_PMCTRL_APLL0CTRL1_gt_clk_apll0_cfg_START   (26)
#define SOC_PMCTRL_APLL0CTRL1_gt_clk_apll0_cfg_END     (26)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_APLL1CTRL0_UNION
 �ṹ˵��  : APLL1CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x018����ֵ:0x00B03E06�����:32
 �Ĵ���˵��: APLL1���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll1_en_cfg       : 1;  /* bit[0-0]  : APLL1 PowerDown���ơ�
                                                              0���رգ�
                                                              1��ʹ�ܡ� */
        unsigned int  apll1_bp_cfg       : 1;  /* bit[1-1]  : APLL1 Bypass���ơ�
                                                              0������������
                                                              1��Bypass�� */
        unsigned int  apll1_refdiv_cfg   : 6;  /* bit[2-7]  : APLL1����ʱ�ӷ�Ƶ���� */
        unsigned int  apll1_fbdiv_cfg    : 12; /* bit[8-19] : APLL1����ʱ��������Ƶ���� */
        unsigned int  apll1_postdiv1_cfg : 3;  /* bit[20-22]: APLL1���ʱ�ӷ�Ƶ��1�� */
        unsigned int  apll1_postdiv2_cfg : 3;  /* bit[23-25]: APLL1���ʱ�ӷ�Ƶ��2�� */
        unsigned int  apll1_lock         : 1;  /* bit[26-26]: APLL1 Lockָʾ��
                                                              0����Ч��
                                                              1��APLL1 Lock�� */
        unsigned int  reserved           : 5;  /* bit[27-31]: ������ */
    } reg;
} SOC_PMCTRL_APLL1CTRL0_UNION;
#endif
#define SOC_PMCTRL_APLL1CTRL0_apll1_en_cfg_START        (0)
#define SOC_PMCTRL_APLL1CTRL0_apll1_en_cfg_END          (0)
#define SOC_PMCTRL_APLL1CTRL0_apll1_bp_cfg_START        (1)
#define SOC_PMCTRL_APLL1CTRL0_apll1_bp_cfg_END          (1)
#define SOC_PMCTRL_APLL1CTRL0_apll1_refdiv_cfg_START    (2)
#define SOC_PMCTRL_APLL1CTRL0_apll1_refdiv_cfg_END      (7)
#define SOC_PMCTRL_APLL1CTRL0_apll1_fbdiv_cfg_START     (8)
#define SOC_PMCTRL_APLL1CTRL0_apll1_fbdiv_cfg_END       (19)
#define SOC_PMCTRL_APLL1CTRL0_apll1_postdiv1_cfg_START  (20)
#define SOC_PMCTRL_APLL1CTRL0_apll1_postdiv1_cfg_END    (22)
#define SOC_PMCTRL_APLL1CTRL0_apll1_postdiv2_cfg_START  (23)
#define SOC_PMCTRL_APLL1CTRL0_apll1_postdiv2_cfg_END    (25)
#define SOC_PMCTRL_APLL1CTRL0_apll1_lock_START          (26)
#define SOC_PMCTRL_APLL1CTRL0_apll1_lock_END            (26)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_APLL1CTRL1_UNION
 �ṹ˵��  : APLL1CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x01C����ֵ:0x06F80000�����:32
 �Ĵ���˵��: APLL1���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll1_fracdiv_cfg : 24; /* bit[0-23] : APLL1����ʱ�ӷ�����Ƶ���� */
        unsigned int  apll1_int_mod_cfg : 1;  /* bit[24-24]: APLL1������Ƶģʽ��
                                                             0��������Ƶģʽ��
                                                             1��������Ƶģʽ��
                                                             ע�⣺��PLL֧�ַ�����Ƶ��������Ƶģʽ������SSC��ʱ��Ҫ�����ֻʹ�÷�����Ƶģʽ�� */
        unsigned int  apll1_cfg_vld_cfg : 1;  /* bit[25-25]: APLL1������Ч��־��
                                                             0��������Ч��
                                                             1��������Ч�� */
        unsigned int  gt_clk_apll1_cfg  : 1;  /* bit[26-26]: APLL1�ſ��źš�
                                                             0��APLL1���ʱ���ſأ�
                                                             1��APLL1���ʱ�Ӳ��ſء����ȴ�PLL�ȶ���������ø�bit���� */
        unsigned int  reserved          : 5;  /* bit[27-31]: ������ */
    } reg;
} SOC_PMCTRL_APLL1CTRL1_UNION;
#endif
#define SOC_PMCTRL_APLL1CTRL1_apll1_fracdiv_cfg_START  (0)
#define SOC_PMCTRL_APLL1CTRL1_apll1_fracdiv_cfg_END    (23)
#define SOC_PMCTRL_APLL1CTRL1_apll1_int_mod_cfg_START  (24)
#define SOC_PMCTRL_APLL1CTRL1_apll1_int_mod_cfg_END    (24)
#define SOC_PMCTRL_APLL1CTRL1_apll1_cfg_vld_cfg_START  (25)
#define SOC_PMCTRL_APLL1CTRL1_apll1_cfg_vld_cfg_END    (25)
#define SOC_PMCTRL_APLL1CTRL1_gt_clk_apll1_cfg_START   (26)
#define SOC_PMCTRL_APLL1CTRL1_gt_clk_apll1_cfg_END     (26)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_APLL2CTRL0_UNION
 �ṹ˵��  : APLL2CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x020����ֵ:0x00B03E06�����:32
 �Ĵ���˵��: APLL2���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll2_en_cfg       : 1;  /* bit[0-0]  : APLL2 PowerDown���ơ�
                                                              0���رգ�
                                                              1��ʹ�ܡ� */
        unsigned int  apll2_bp_cfg       : 1;  /* bit[1-1]  : APLL2 Bypass���ơ�
                                                              0������������
                                                              1��Bypass�� */
        unsigned int  apll2_refdiv_cfg   : 6;  /* bit[2-7]  : APLL2����ʱ�ӷ�Ƶ���� */
        unsigned int  apll2_fbdiv_cfg    : 12; /* bit[8-19] : APLL2����ʱ��������Ƶ���� */
        unsigned int  apll2_postdiv1_cfg : 3;  /* bit[20-22]: APLL2���ʱ�ӷ�Ƶ��1�� */
        unsigned int  apll2_postdiv2_cfg : 3;  /* bit[23-25]: APLL2���ʱ�ӷ�Ƶ��2�� */
        unsigned int  apll2_lock         : 1;  /* bit[26-26]: APLL2 Lockָʾ��
                                                              0����Ч��
                                                              1��APLL2 Lock�� */
        unsigned int  reserved           : 5;  /* bit[27-31]: ������ */
    } reg;
} SOC_PMCTRL_APLL2CTRL0_UNION;
#endif
#define SOC_PMCTRL_APLL2CTRL0_apll2_en_cfg_START        (0)
#define SOC_PMCTRL_APLL2CTRL0_apll2_en_cfg_END          (0)
#define SOC_PMCTRL_APLL2CTRL0_apll2_bp_cfg_START        (1)
#define SOC_PMCTRL_APLL2CTRL0_apll2_bp_cfg_END          (1)
#define SOC_PMCTRL_APLL2CTRL0_apll2_refdiv_cfg_START    (2)
#define SOC_PMCTRL_APLL2CTRL0_apll2_refdiv_cfg_END      (7)
#define SOC_PMCTRL_APLL2CTRL0_apll2_fbdiv_cfg_START     (8)
#define SOC_PMCTRL_APLL2CTRL0_apll2_fbdiv_cfg_END       (19)
#define SOC_PMCTRL_APLL2CTRL0_apll2_postdiv1_cfg_START  (20)
#define SOC_PMCTRL_APLL2CTRL0_apll2_postdiv1_cfg_END    (22)
#define SOC_PMCTRL_APLL2CTRL0_apll2_postdiv2_cfg_START  (23)
#define SOC_PMCTRL_APLL2CTRL0_apll2_postdiv2_cfg_END    (25)
#define SOC_PMCTRL_APLL2CTRL0_apll2_lock_START          (26)
#define SOC_PMCTRL_APLL2CTRL0_apll2_lock_END            (26)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_APLL2CTRL1_UNION
 �ṹ˵��  : APLL2CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x024����ֵ:0x06F80000�����:32
 �Ĵ���˵��: APLL2���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll2_fracdiv_cfg : 24; /* bit[0-23] : APLL2����ʱ�ӷ�����Ƶ���� */
        unsigned int  apll2_int_mod_cfg : 1;  /* bit[24-24]: APLL2������Ƶģʽ��
                                                             0��������Ƶģʽ��
                                                             1��������Ƶģʽ��
                                                             ע�⣺��PLL֧�ַ�����Ƶ��������Ƶģʽ������SSC��ʱ��Ҫ�����ֻʹ�÷�����Ƶģʽ�� */
        unsigned int  apll2_cfg_vld_cfg : 1;  /* bit[25-25]: APLL2������Ч��־��
                                                             0��������Ч��
                                                             1��������Ч�� */
        unsigned int  gt_clk_apll2_cfg  : 1;  /* bit[26-26]: APLL2�ſ��źš�
                                                             0��APLL2���ʱ���ſأ�
                                                             1��APLL2���ʱ�Ӳ��ſء����ȴ�PLL�ȶ���������ø�bit�� */
        unsigned int  reserved          : 5;  /* bit[27-31]: ������ */
    } reg;
} SOC_PMCTRL_APLL2CTRL1_UNION;
#endif
#define SOC_PMCTRL_APLL2CTRL1_apll2_fracdiv_cfg_START  (0)
#define SOC_PMCTRL_APLL2CTRL1_apll2_fracdiv_cfg_END    (23)
#define SOC_PMCTRL_APLL2CTRL1_apll2_int_mod_cfg_START  (24)
#define SOC_PMCTRL_APLL2CTRL1_apll2_int_mod_cfg_END    (24)
#define SOC_PMCTRL_APLL2CTRL1_apll2_cfg_vld_cfg_START  (25)
#define SOC_PMCTRL_APLL2CTRL1_apll2_cfg_vld_cfg_END    (25)
#define SOC_PMCTRL_APLL2CTRL1_gt_clk_apll2_cfg_START   (26)
#define SOC_PMCTRL_APLL2CTRL1_gt_clk_apll2_cfg_END     (26)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PPLL1CTRL0_UNION
 �ṹ˵��  : PPLL1CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x038����ֵ:0x00904B06�����:32
 �Ĵ���˵��: PPLL1���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll1_en       : 1;  /* bit[0-0]  : PPLL1 PowerDown���ơ�
                                                          0���رգ�
                                                          1��ʹ�ܡ� */
        unsigned int  ppll1_bp       : 1;  /* bit[1-1]  : PPLL1 Bypass���ơ�
                                                          0������������
                                                          1��Bypass�� */
        unsigned int  ppll1_refdiv   : 6;  /* bit[2-7]  : PPLL1����ʱ�ӷ�Ƶ���� */
        unsigned int  ppll1_fbdiv    : 12; /* bit[8-19] : PPLL1����ʱ��������Ƶ���� */
        unsigned int  ppll1_postdiv1 : 3;  /* bit[20-22]: PPLL1���ʱ�ӷ�Ƶ��1�� */
        unsigned int  ppll1_postdiv2 : 3;  /* bit[23-25]: PPLL1���ʱ�ӷ�Ƶ��2�� */
        unsigned int  ppll1_lock     : 1;  /* bit[26-26]: PPLL1 Lockָʾ��
                                                          0����Ч��
                                                          1��PPLL1 Lock�� */
        unsigned int  reserved       : 5;  /* bit[27-31]: ���� */
    } reg;
} SOC_PMCTRL_PPLL1CTRL0_UNION;
#endif
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_en_START        (0)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_en_END          (0)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_bp_START        (1)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_bp_END          (1)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_refdiv_START    (2)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_refdiv_END      (7)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_fbdiv_START     (8)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_fbdiv_END       (19)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_postdiv1_START  (20)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_postdiv1_END    (22)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_postdiv2_START  (23)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_postdiv2_END    (25)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_lock_START      (26)
#define SOC_PMCTRL_PPLL1CTRL0_ppll1_lock_END        (26)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PPLL1CTRL1_UNION
 �ṹ˵��  : PPLL1CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x03C����ֵ:0x06000000�����:32
 �Ĵ���˵��: PPLL1���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll1_fracdiv : 24; /* bit[0-23] : PPLL1����ʱ�ӷ�����Ƶ���� */
        unsigned int  ppll1_int_mod : 1;  /* bit[24-24]: PPLL1������Ƶģʽ��
                                                         0��������Ƶģʽ��
                                                         1��������Ƶģʽ��
                                                         ע�⣺��PLL֧�ַ�����Ƶ��������Ƶģʽ������SSC��ʱ��Ҫ�����ֻʹ�÷�����Ƶģʽ�� */
        unsigned int  ppll1_cfg_vld : 1;  /* bit[25-25]: PPLL1������Ч��־��
                                                         0��������Ч��
                                                         1��������Ч�� */
        unsigned int  gt_clk_ppll1  : 1;  /* bit[26-26]: PPLL1�ſ��źš�
                                                         0��PPLL1���ʱ���ſأ�
                                                         1��PPLL1���ʱ�Ӳ��ſء����ȴ�PLL�ȶ���������ø�bit�� */
        unsigned int  reserved      : 5;  /* bit[27-31]: ���� */
    } reg;
} SOC_PMCTRL_PPLL1CTRL1_UNION;
#endif
#define SOC_PMCTRL_PPLL1CTRL1_ppll1_fracdiv_START  (0)
#define SOC_PMCTRL_PPLL1CTRL1_ppll1_fracdiv_END    (23)
#define SOC_PMCTRL_PPLL1CTRL1_ppll1_int_mod_START  (24)
#define SOC_PMCTRL_PPLL1CTRL1_ppll1_int_mod_END    (24)
#define SOC_PMCTRL_PPLL1CTRL1_ppll1_cfg_vld_START  (25)
#define SOC_PMCTRL_PPLL1CTRL1_ppll1_cfg_vld_END    (25)
#define SOC_PMCTRL_PPLL1CTRL1_gt_clk_ppll1_START   (26)
#define SOC_PMCTRL_PPLL1CTRL1_gt_clk_ppll1_END     (26)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PPLL2CTRL0_UNION
 �ṹ˵��  : PPLL2CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x040����ֵ:0x00A03D06�����:32
 �Ĵ���˵��: PPLL2���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll2_en       : 1;  /* bit[0-0]  : PPLL2 PowerDown���ơ�
                                                          0���رգ�
                                                          1��ʹ�ܡ� */
        unsigned int  ppll2_bp       : 1;  /* bit[1-1]  : PPLL2 Bypass���ơ�
                                                          0������������
                                                          1��Bypass�� */
        unsigned int  ppll2_refdiv   : 6;  /* bit[2-7]  : PPLL2����ʱ�ӷ�Ƶ���� */
        unsigned int  ppll2_fbdiv    : 12; /* bit[8-19] : PPLL2����ʱ��������Ƶ���� */
        unsigned int  ppll2_postdiv1 : 3;  /* bit[20-22]: PPLL2���ʱ�ӷ�Ƶ��1�� */
        unsigned int  ppll2_postdiv2 : 3;  /* bit[23-25]: PPLL2���ʱ�ӷ�Ƶ��2�� */
        unsigned int  ppll2_lock     : 1;  /* bit[26-26]: PPLL2 Lockָʾ��
                                                          0����Ч��
                                                          1��PPLL2 Lock�� */
        unsigned int  reserved       : 5;  /* bit[27-31]: ���� */
    } reg;
} SOC_PMCTRL_PPLL2CTRL0_UNION;
#endif
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_en_START        (0)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_en_END          (0)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_bp_START        (1)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_bp_END          (1)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_refdiv_START    (2)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_refdiv_END      (7)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_fbdiv_START     (8)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_fbdiv_END       (19)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_postdiv1_START  (20)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_postdiv1_END    (22)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_postdiv2_START  (23)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_postdiv2_END    (25)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_lock_START      (26)
#define SOC_PMCTRL_PPLL2CTRL0_ppll2_lock_END        (26)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PPLL2CTRL1_UNION
 �ṹ˵��  : PPLL2CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x044����ֵ:0x06E00000�����:32
 �Ĵ���˵��: PPLL2���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll2_fracdiv : 24; /* bit[0-23] : PPLL2����ʱ�ӷ�����Ƶ���� */
        unsigned int  ppll2_int_mod : 1;  /* bit[24-24]: PPLL2������Ƶģʽ��
                                                         0��������Ƶģʽ��
                                                         1��������Ƶģʽ��
                                                         ע�⣺��PLL֧�ַ�����Ƶ��������Ƶģʽ������SSC��ʱ��Ҫ�����ֻʹ�÷�����Ƶģʽ�� */
        unsigned int  ppll2_cfg_vld : 1;  /* bit[25-25]: PPLL2������Ч��־��
                                                         0��������Ч��
                                                         1��������Ч�� */
        unsigned int  gt_clk_ppll2  : 1;  /* bit[26-26]: PPLL2�ſ��źš�
                                                         0��PPLL2���ʱ���ſأ�
                                                         1��PPLL2���ʱ�Ӳ��ſء����ȴ�PLL�ȶ���������ø�bit�� */
        unsigned int  reserved      : 5;  /* bit[27-31]: ���� */
    } reg;
} SOC_PMCTRL_PPLL2CTRL1_UNION;
#endif
#define SOC_PMCTRL_PPLL2CTRL1_ppll2_fracdiv_START  (0)
#define SOC_PMCTRL_PPLL2CTRL1_ppll2_fracdiv_END    (23)
#define SOC_PMCTRL_PPLL2CTRL1_ppll2_int_mod_START  (24)
#define SOC_PMCTRL_PPLL2CTRL1_ppll2_int_mod_END    (24)
#define SOC_PMCTRL_PPLL2CTRL1_ppll2_cfg_vld_START  (25)
#define SOC_PMCTRL_PPLL2CTRL1_ppll2_cfg_vld_END    (25)
#define SOC_PMCTRL_PPLL2CTRL1_gt_clk_ppll2_START   (26)
#define SOC_PMCTRL_PPLL2CTRL1_gt_clk_ppll2_END     (26)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PPLL3CTRL0_UNION
 �ṹ˵��  : PPLL3CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x048����ֵ:0x00905306�����:32
 �Ĵ���˵��: PPLL3���ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll3_en       : 1;  /* bit[0-0]  : PPLL3 PowerDown���ơ�
                                                          0���رգ�
                                                          1��ʹ�ܡ� */
        unsigned int  ppll3_bp       : 1;  /* bit[1-1]  : PPLL3 Bypass���ơ�
                                                          0������������
                                                          1��Bypass�� */
        unsigned int  ppll3_refdiv   : 6;  /* bit[2-7]  : PPLL3����ʱ�ӷ�Ƶ���� */
        unsigned int  ppll3_fbdiv    : 12; /* bit[8-19] : PPLL3����ʱ��������Ƶ���� */
        unsigned int  ppll3_postdiv1 : 3;  /* bit[20-22]: PPLL3���ʱ�ӷ�Ƶ��1�� */
        unsigned int  ppll3_postdiv2 : 3;  /* bit[23-25]: PPLL3���ʱ�ӷ�Ƶ��2�� */
        unsigned int  ppll3_lock     : 1;  /* bit[26-26]: PPLL3 Lockָʾ��
                                                          0����Ч��
                                                          1��PPLL3 Lock�� */
        unsigned int  reserved       : 5;  /* bit[27-31]: ���� */
    } reg;
} SOC_PMCTRL_PPLL3CTRL0_UNION;
#endif
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_en_START        (0)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_en_END          (0)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_bp_START        (1)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_bp_END          (1)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_refdiv_START    (2)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_refdiv_END      (7)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_fbdiv_START     (8)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_fbdiv_END       (19)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_postdiv1_START  (20)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_postdiv1_END    (22)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_postdiv2_START  (23)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_postdiv2_END    (25)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_lock_START      (26)
#define SOC_PMCTRL_PPLL3CTRL0_ppll3_lock_END        (26)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PPLL3CTRL1_UNION
 �ṹ˵��  : PPLL3CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x04C����ֵ:0x06555555�����:32
 �Ĵ���˵��: PPLL3���ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll3_fracdiv : 24; /* bit[0-23] : PPLL3����ʱ�ӷ�����Ƶ���� */
        unsigned int  ppll3_int_mod : 1;  /* bit[24-24]: PPLL3������Ƶģʽ��
                                                         0��������Ƶģʽ��
                                                         1��������Ƶģʽ��
                                                         ע�⣺��PLL֧�ַ�����Ƶ��������Ƶģʽ������SSC��ʱ��Ҫ�����ֻʹ�÷�����Ƶģʽ�� */
        unsigned int  ppll3_cfg_vld : 1;  /* bit[25-25]: PPLL3������Ч��־��
                                                         0��������Ч��
                                                         1��������Ч�� */
        unsigned int  gt_clk_ppll3  : 1;  /* bit[26-26]: PPLL3�ſ��źš�
                                                         0��PPLL3���ʱ���ſأ�
                                                         1��PPLL3���ʱ�Ӳ��ſء����ȴ�PLL�ȶ���������ø�bit�� */
        unsigned int  reserved      : 5;  /* bit[27-31]: ���� */
    } reg;
} SOC_PMCTRL_PPLL3CTRL1_UNION;
#endif
#define SOC_PMCTRL_PPLL3CTRL1_ppll3_fracdiv_START  (0)
#define SOC_PMCTRL_PPLL3CTRL1_ppll3_fracdiv_END    (23)
#define SOC_PMCTRL_PPLL3CTRL1_ppll3_int_mod_START  (24)
#define SOC_PMCTRL_PPLL3CTRL1_ppll3_int_mod_END    (24)
#define SOC_PMCTRL_PPLL3CTRL1_ppll3_cfg_vld_START  (25)
#define SOC_PMCTRL_PPLL3CTRL1_ppll3_cfg_vld_END    (25)
#define SOC_PMCTRL_PPLL3CTRL1_gt_clk_ppll3_START   (26)
#define SOC_PMCTRL_PPLL3CTRL1_gt_clk_ppll3_END     (26)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_APLL0SSCCTRL_UNION
 �ṹ˵��  : APLL0SSCCTRL �Ĵ����ṹ���塣��ַƫ����:0x070����ֵ:0x0000019F�����:32
 �Ĵ���˵��: APLL0 SSC���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll0_ssc_reset      : 1;  /* bit[0]    : ��λ�źţ�����Ч��
                                                                0����λȡ����
                                                                1����λ��Ч��
                                                                ע��������PLL���������и�λ������ᵼ��PLLʧ���� */
        unsigned int  apll0_ssc_disable    : 1;  /* bit[1]    : Bypass the modulator������Ч��
                                                                0������������
                                                                1��bypass�� */
        unsigned int  apll0_ssc_downspread : 1;  /* bit[2]    : ѡ��center spread��down spread��
                                                                0��Center Spread��
                                                                1��Down Spread�� */
        unsigned int  apll0_ssc_spread     : 3;  /* bit[3-5]  : ���õ������(spread%)��
                                                                3'b000 = 0��
                                                                3'b001 = 0.049%��
                                                                3'b010 = 0.098%��
                                                                3'b011 = 0.195%��
                                                                3'b100 = 0.391%��
                                                                3'b101 = 0.781%��
                                                                3'b110 = 1.563%��
                                                                3'b111 = 3.125%�� */
        unsigned int  apll0_ssc_divval     : 4;  /* bit[6-9]  : ����Ƶ�׵��Ƶ�Ƶ�ʣ�һ��ԼΪ32KHz��
                                                                freq=(CLKSSCG / (DIVVAL * #points))������pointsΪ128����REFDIV=1ʱ��CLKSSCG=FREF�� */
        unsigned int  reserved             : 22; /* bit[10-31]: ������ */
    } reg;
} SOC_PMCTRL_APLL0SSCCTRL_UNION;
#endif
#define SOC_PMCTRL_APLL0SSCCTRL_apll0_ssc_reset_START       (0)
#define SOC_PMCTRL_APLL0SSCCTRL_apll0_ssc_reset_END         (0)
#define SOC_PMCTRL_APLL0SSCCTRL_apll0_ssc_disable_START     (1)
#define SOC_PMCTRL_APLL0SSCCTRL_apll0_ssc_disable_END       (1)
#define SOC_PMCTRL_APLL0SSCCTRL_apll0_ssc_downspread_START  (2)
#define SOC_PMCTRL_APLL0SSCCTRL_apll0_ssc_downspread_END    (2)
#define SOC_PMCTRL_APLL0SSCCTRL_apll0_ssc_spread_START      (3)
#define SOC_PMCTRL_APLL0SSCCTRL_apll0_ssc_spread_END        (5)
#define SOC_PMCTRL_APLL0SSCCTRL_apll0_ssc_divval_START      (6)
#define SOC_PMCTRL_APLL0SSCCTRL_apll0_ssc_divval_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_APLL1SSCCTRL_UNION
 �ṹ˵��  : APLL1SSCCTRL �Ĵ����ṹ���塣��ַƫ����:0x074����ֵ:0x0000019F�����:32
 �Ĵ���˵��: APLL1 SSC���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll1_ssc_reset      : 1;  /* bit[0]    : ��λ�źţ�����Ч��
                                                                0����λȡ����
                                                                1����λ��Ч��
                                                                ע��������PLL���������и�λ������ᵼ��PLLʧ���� */
        unsigned int  apll1_ssc_disable    : 1;  /* bit[1]    : Bypass the modulator������Ч��
                                                                0������������
                                                                1��bypass�� */
        unsigned int  apll1_ssc_downspread : 1;  /* bit[2]    : ѡ��center spread��down spread��
                                                                0��Center Spread��
                                                                1��Down Spread�� */
        unsigned int  apll1_ssc_spread     : 3;  /* bit[3-5]  : ���õ������(spread%)��
                                                                3'b000 = 0��
                                                                3'b001 = 0.049%��
                                                                3'b010 = 0.098%��
                                                                3'b011 = 0.195%��
                                                                3'b100 = 0.391%��
                                                                3'b101 = 0.781%��
                                                                3'b110 = 1.563%��
                                                                3'b111 = 3.125%�� */
        unsigned int  apll1_ssc_divval     : 4;  /* bit[6-9]  : ����Ƶ�׵��Ƶ�Ƶ�ʣ�һ��ԼΪ32KHz��
                                                                freq=(CLKSSCG / (DIVVAL * #points))������pointsΪ128����REFDIV=1ʱ��CLKSSCG=FREF�� */
        unsigned int  reserved             : 22; /* bit[10-31]: ������ */
    } reg;
} SOC_PMCTRL_APLL1SSCCTRL_UNION;
#endif
#define SOC_PMCTRL_APLL1SSCCTRL_apll1_ssc_reset_START       (0)
#define SOC_PMCTRL_APLL1SSCCTRL_apll1_ssc_reset_END         (0)
#define SOC_PMCTRL_APLL1SSCCTRL_apll1_ssc_disable_START     (1)
#define SOC_PMCTRL_APLL1SSCCTRL_apll1_ssc_disable_END       (1)
#define SOC_PMCTRL_APLL1SSCCTRL_apll1_ssc_downspread_START  (2)
#define SOC_PMCTRL_APLL1SSCCTRL_apll1_ssc_downspread_END    (2)
#define SOC_PMCTRL_APLL1SSCCTRL_apll1_ssc_spread_START      (3)
#define SOC_PMCTRL_APLL1SSCCTRL_apll1_ssc_spread_END        (5)
#define SOC_PMCTRL_APLL1SSCCTRL_apll1_ssc_divval_START      (6)
#define SOC_PMCTRL_APLL1SSCCTRL_apll1_ssc_divval_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_APLL2SSCCTRL_UNION
 �ṹ˵��  : APLL2SSCCTRL �Ĵ����ṹ���塣��ַƫ����:0x078����ֵ:0x0000019F�����:32
 �Ĵ���˵��: APLL2 SSC���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll2_ssc_reset      : 1;  /* bit[0]    : ��λ�źţ�����Ч��
                                                                0����λȡ����
                                                                1����λ��Ч��
                                                                ע��������PLL���������и�λ������ᵼ��PLLʧ���� */
        unsigned int  apll2_ssc_disable    : 1;  /* bit[1]    : Bypass the modulator������Ч��
                                                                0������������
                                                                1��bypass�� */
        unsigned int  apll2_ssc_downspread : 1;  /* bit[2]    : ѡ��center spread��down spread��
                                                                0��Center Spread��
                                                                1��Down Spread�� */
        unsigned int  apll2_ssc_spread     : 3;  /* bit[3-5]  : ���õ������(spread%)��
                                                                3'b000 = 0��
                                                                3'b001 = 0.049%��
                                                                3'b010 = 0.098%��
                                                                3'b011 = 0.195%��
                                                                3'b100 = 0.391%��
                                                                3'b101 = 0.781%��
                                                                3'b110 = 1.563%��
                                                                3'b111 = 3.125%�� */
        unsigned int  apll2_ssc_divval     : 4;  /* bit[6-9]  : ����Ƶ�׵��Ƶ�Ƶ�ʣ�һ��ԼΪ32KHz��
                                                                freq=(CLKSSCG / (DIVVAL * #points))������pointsΪ128����REFDIV=1ʱ��CLKSSCG=FREF�� */
        unsigned int  reserved             : 22; /* bit[10-31]: ���� */
    } reg;
} SOC_PMCTRL_APLL2SSCCTRL_UNION;
#endif
#define SOC_PMCTRL_APLL2SSCCTRL_apll2_ssc_reset_START       (0)
#define SOC_PMCTRL_APLL2SSCCTRL_apll2_ssc_reset_END         (0)
#define SOC_PMCTRL_APLL2SSCCTRL_apll2_ssc_disable_START     (1)
#define SOC_PMCTRL_APLL2SSCCTRL_apll2_ssc_disable_END       (1)
#define SOC_PMCTRL_APLL2SSCCTRL_apll2_ssc_downspread_START  (2)
#define SOC_PMCTRL_APLL2SSCCTRL_apll2_ssc_downspread_END    (2)
#define SOC_PMCTRL_APLL2SSCCTRL_apll2_ssc_spread_START      (3)
#define SOC_PMCTRL_APLL2SSCCTRL_apll2_ssc_spread_END        (5)
#define SOC_PMCTRL_APLL2SSCCTRL_apll2_ssc_divval_START      (6)
#define SOC_PMCTRL_APLL2SSCCTRL_apll2_ssc_divval_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PPLL1SSCCTRL_UNION
 �ṹ˵��  : PPLL1SSCCTRL �Ĵ����ṹ���塣��ַƫ����:0x084����ֵ:0x0000019F�����:32
 �Ĵ���˵��: PPLL1 SSC���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll1_ssc_reset      : 1;  /* bit[0]    : ��λ�źţ�����Ч��
                                                                0����λȡ����
                                                                1����λ��Ч��
                                                                ע��������PLL���������и�λ������ᵼ��PLLʧ���� */
        unsigned int  ppll1_ssc_disable    : 1;  /* bit[1]    : Bypass the modulator������Ч��
                                                                0������������
                                                                1��bypass�� */
        unsigned int  ppll1_ssc_downspread : 1;  /* bit[2]    : ѡ��center spread��down spread��
                                                                0��Center Spread��
                                                                1��Down Spread�� */
        unsigned int  ppll1_ssc_spread     : 3;  /* bit[3-5]  : ���õ������(spread%)��
                                                                3'b000 = 0��
                                                                3'b001 = 0.049%��
                                                                3'b010 = 0.098%��
                                                                3'b011 = 0.195%��
                                                                3'b100 = 0.391%��
                                                                3'b101 = 0.781%��
                                                                3'b110 = 1.563%��
                                                                3'b111 = 3.125%�� */
        unsigned int  ppll1_ssc_divval     : 4;  /* bit[6-9]  : ����Ƶ�׵��Ƶ�Ƶ�ʣ�һ��ԼΪ32KHz��
                                                                freq=(CLKSSCG / (DIVVAL * #points))������pointsΪ128����REFDIV=1ʱ��CLKSSCG=FREF�� */
        unsigned int  reserved             : 22; /* bit[10-31]: ������ */
    } reg;
} SOC_PMCTRL_PPLL1SSCCTRL_UNION;
#endif
#define SOC_PMCTRL_PPLL1SSCCTRL_ppll1_ssc_reset_START       (0)
#define SOC_PMCTRL_PPLL1SSCCTRL_ppll1_ssc_reset_END         (0)
#define SOC_PMCTRL_PPLL1SSCCTRL_ppll1_ssc_disable_START     (1)
#define SOC_PMCTRL_PPLL1SSCCTRL_ppll1_ssc_disable_END       (1)
#define SOC_PMCTRL_PPLL1SSCCTRL_ppll1_ssc_downspread_START  (2)
#define SOC_PMCTRL_PPLL1SSCCTRL_ppll1_ssc_downspread_END    (2)
#define SOC_PMCTRL_PPLL1SSCCTRL_ppll1_ssc_spread_START      (3)
#define SOC_PMCTRL_PPLL1SSCCTRL_ppll1_ssc_spread_END        (5)
#define SOC_PMCTRL_PPLL1SSCCTRL_ppll1_ssc_divval_START      (6)
#define SOC_PMCTRL_PPLL1SSCCTRL_ppll1_ssc_divval_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PPLL2SSCCTRL_UNION
 �ṹ˵��  : PPLL2SSCCTRL �Ĵ����ṹ���塣��ַƫ����:0x088����ֵ:0x0000019F�����:32
 �Ĵ���˵��: PPLL2 SSC���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll2_ssc_reset      : 1;  /* bit[0]    : ��λ�źţ�����Ч��
                                                                0����λȡ����
                                                                1����λ��Ч��
                                                                ע��������PLL���������и�λ������ᵼ��PLLʧ���� */
        unsigned int  ppll2_ssc_disable    : 1;  /* bit[1]    : Bypass the modulator������Ч��
                                                                0������������
                                                                1��bypass�� */
        unsigned int  ppll2_ssc_downspread : 1;  /* bit[2]    : ѡ��center spread��down spread��
                                                                0��Center Spread��
                                                                1��Down Spread�� */
        unsigned int  ppll2_ssc_spread     : 3;  /* bit[3-5]  : ���õ������(spread%)��
                                                                3'b000 = 0��
                                                                3'b001 = 0.049%��
                                                                3'b010 = 0.098%��
                                                                3'b011 = 0.195%��
                                                                3'b100 = 0.391%��
                                                                3'b101 = 0.781%��
                                                                3'b110 = 1.563%��
                                                                3'b111 = 3.125%�� */
        unsigned int  ppll2_ssc_divval     : 4;  /* bit[6-9]  : ����Ƶ�׵��Ƶ�Ƶ�ʣ�һ��ԼΪ32KHz��
                                                                freq=(CLKSSCG / (DIVVAL * #points))������pointsΪ128����REFDIV=1ʱ��CLKSSCG=FREF�� */
        unsigned int  reserved             : 22; /* bit[10-31]: ������ */
    } reg;
} SOC_PMCTRL_PPLL2SSCCTRL_UNION;
#endif
#define SOC_PMCTRL_PPLL2SSCCTRL_ppll2_ssc_reset_START       (0)
#define SOC_PMCTRL_PPLL2SSCCTRL_ppll2_ssc_reset_END         (0)
#define SOC_PMCTRL_PPLL2SSCCTRL_ppll2_ssc_disable_START     (1)
#define SOC_PMCTRL_PPLL2SSCCTRL_ppll2_ssc_disable_END       (1)
#define SOC_PMCTRL_PPLL2SSCCTRL_ppll2_ssc_downspread_START  (2)
#define SOC_PMCTRL_PPLL2SSCCTRL_ppll2_ssc_downspread_END    (2)
#define SOC_PMCTRL_PPLL2SSCCTRL_ppll2_ssc_spread_START      (3)
#define SOC_PMCTRL_PPLL2SSCCTRL_ppll2_ssc_spread_END        (5)
#define SOC_PMCTRL_PPLL2SSCCTRL_ppll2_ssc_divval_START      (6)
#define SOC_PMCTRL_PPLL2SSCCTRL_ppll2_ssc_divval_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PPLL3SSCCTRL_UNION
 �ṹ˵��  : PPLL3SSCCTRL �Ĵ����ṹ���塣��ַƫ����:0x08C����ֵ:0x0000019F�����:32
 �Ĵ���˵��: PPLL3 SSC���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ppll3_ssc_reset      : 1;  /* bit[0]    : ��λ�źţ�����Ч��
                                                                0����λȡ����
                                                                1����λ��Ч��
                                                                ע��������PLL���������и�λ������ᵼ��PLLʧ���� */
        unsigned int  ppll3_ssc_disable    : 1;  /* bit[1]    : Bypass the modulator������Ч��
                                                                0������������
                                                                1��bypass�� */
        unsigned int  ppll3_ssc_downspread : 1;  /* bit[2]    : ѡ��center spread��down spread��
                                                                0��Center Spread��
                                                                1��Down Spread�� */
        unsigned int  ppll3_ssc_spread     : 3;  /* bit[3-5]  : ���õ������(spread%)��
                                                                3'b000 = 0��
                                                                3'b001 = 0.049%��
                                                                3'b010 = 0.098%��
                                                                3'b011 = 0.195%��
                                                                3'b100 = 0.391%��
                                                                3'b101 = 0.781%��
                                                                3'b110 = 1.563%��
                                                                3'b111 = 3.125%�� */
        unsigned int  ppll3_ssc_divval     : 4;  /* bit[6-9]  : ����Ƶ�׵��Ƶ�Ƶ�ʣ�һ��ԼΪ32KHz��
                                                                freq=(CLKSSCG / (DIVVAL * #points))������pointsΪ128����REFDIV=1ʱ��CLKSSCG=FREF�� */
        unsigned int  reserved             : 22; /* bit[10-31]: ������ */
    } reg;
} SOC_PMCTRL_PPLL3SSCCTRL_UNION;
#endif
#define SOC_PMCTRL_PPLL3SSCCTRL_ppll3_ssc_reset_START       (0)
#define SOC_PMCTRL_PPLL3SSCCTRL_ppll3_ssc_reset_END         (0)
#define SOC_PMCTRL_PPLL3SSCCTRL_ppll3_ssc_disable_START     (1)
#define SOC_PMCTRL_PPLL3SSCCTRL_ppll3_ssc_disable_END       (1)
#define SOC_PMCTRL_PPLL3SSCCTRL_ppll3_ssc_downspread_START  (2)
#define SOC_PMCTRL_PPLL3SSCCTRL_ppll3_ssc_downspread_END    (2)
#define SOC_PMCTRL_PPLL3SSCCTRL_ppll3_ssc_spread_START      (3)
#define SOC_PMCTRL_PPLL3SSCCTRL_ppll3_ssc_spread_END        (5)
#define SOC_PMCTRL_PPLL3SSCCTRL_ppll3_ssc_divval_START      (6)
#define SOC_PMCTRL_PPLL3SSCCTRL_ppll3_ssc_divval_END        (9)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PMUMOD_UNION
 �ṹ˵��  : PMUMOD �Ĵ����ṹ���塣��ַƫ����:0x094����ֵ:0x00000000�����:32
 �Ĵ���˵��: PMU����ģʽ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pmu_mode : 1;  /* bit[0-0] : PMU����ģʽѡ��
                                                   0��ͳһ����ģʽ��
                                                   1����������ģʽ�� */
        unsigned int  reserved : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_PMUMOD_UNION;
#endif
#define SOC_PMCTRL_PMUMOD_pmu_mode_START  (0)
#define SOC_PMCTRL_PMUMOD_pmu_mode_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUDVFSMOD_UNION
 �ṹ˵��  : CLUSTER0_CPUDVFSMOD �Ĵ����ṹ���塣��ַƫ����:0x098����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU DVFSģʽ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_dvfs_mod : 1;  /* bit[0-0] : Cluster0 DVFSģʽѡ��
                                                                0���л�APLLģʽ��
                                                                1������Ƶģʽ���̶�APLL����
                                                                ������Ϊ����Ƶģʽʱ��PLL Lock Mod��������Ϊ�ȴ���ʱģʽ�� */
        unsigned int  reserved              : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUDVFSMOD_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUDVFSMOD_cluster0_cpu_dvfs_mod_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPUDVFSMOD_cluster0_cpu_dvfs_mod_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUCLKSEL_UNION
 �ṹ˵��  : CLUSTER0_CPUCLKSEL �Ĵ����ṹ���塣��ַƫ����:0x09C����ֵ:0x00000002�����:32
 �Ĵ���˵��: CLUSTER0_CPU ʱ����Դѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_clk_sel : 2;  /* bit[0-1] : Cluster0_ʱ��ѡ���ĸ�ʱ����Դ��
                                                           00��Cluster0_ʱ��ѡ��480Mhz��
                                                           01��Cluster0_ʱ��ѡ��19.2MHz��
                                                           1X��Cluster0_ʱ��ѡ��APLL�� */
        unsigned int  reserved         : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUCLKSEL_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUCLKSEL_cluster0_clk_sel_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPUCLKSEL_cluster0_clk_sel_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUDVFSEN_UNION
 �ṹ˵��  : CLUSTER0_CPUDVFSEN �Ĵ����ṹ���塣��ַƫ����:0x0A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU DVFSʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_dvfs_en : 1;  /* bit[0-0] : Cluster0_ DVFSʹ�ܡ�
                                                               0��Cluster0_ DVFS���ܹرգ�
                                                               1��Cluster0_ DVFS���ܿ����� */
        unsigned int  reserved             : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUDVFSEN_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUDVFSEN_cluster0_cpu_dvfs_en_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPUDVFSEN_cluster0_cpu_dvfs_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUPLLSEL_UNION
 �ṹ˵��  : CLUSTER0_CPUPLLSEL �Ĵ����ṹ���塣��ַƫ����:0x0A4����ֵ:0x00000010�����:32
 �Ĵ���˵��: CLUSTER0_CPU PLLѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_apll_sel_cfg  : 2;  /* bit[0-1]  : Cluster0_ʱ��ѡ���ĸ�PLL��
                                                                  00��Cluster0_ʱ��ѡ��APLL0��
                                                                  01��Cluster0_ʱ��ѡ��APLL1��
                                                                  1X��Cluster0_ʱ��ѡ��APLL2�� */
        unsigned int  cluster0_pll_sw_ack    : 5;  /* bit[2-6]  : ��ǰCluster0_ʱ��ѡ���ĸ�ʱ�ӵ�״ָ̬ʾ��
                                                                  00001��Cluster0_ʱ��ѡ��480Mhz��
                                                                  00010��Cluster0_ʱ��ѡ��19.2MHz��
                                                                  00100��Cluster0_ʱ��ѡ��APLL0��
                                                                  01000��Cluster0_ʱ��ѡ��APLL1��
                                                                  10000��Cluster0_ʱ��ѡ��APLL2�� */
        unsigned int  reserved_0             : 1;  /* bit[7-7]  : ������ */
        unsigned int  cluster0_apll_sel_stat : 2;  /* bit[8-9]  : Cluster0_ʱ��ѡ���ĸ�PLL��
                                                                  00��Cluster0_ʱ��ѡ��APLL0��
                                                                  01��Cluster0_ʱ��ѡ��APLL1��
                                                                  1X��Cluster0_ʱ��ѡ��APLL2�� */
        unsigned int  reserved_1             : 22; /* bit[10-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUPLLSEL_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUPLLSEL_cluster0_apll_sel_cfg_START   (0)
#define SOC_PMCTRL_CLUSTER0_CPUPLLSEL_cluster0_apll_sel_cfg_END     (1)
#define SOC_PMCTRL_CLUSTER0_CPUPLLSEL_cluster0_pll_sw_ack_START     (2)
#define SOC_PMCTRL_CLUSTER0_CPUPLLSEL_cluster0_pll_sw_ack_END       (6)
#define SOC_PMCTRL_CLUSTER0_CPUPLLSEL_cluster0_apll_sel_stat_START  (8)
#define SOC_PMCTRL_CLUSTER0_CPUPLLSEL_cluster0_apll_sel_stat_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUCLKDIV_UNION
 �ṹ˵��  : CLUSTER0_CPUCLKDIV �Ĵ����ṹ���塣��ַƫ����:0x0A8����ֵ:0x0000A1A1�����:32
 �Ĵ���˵��: CLUSTER0_CPUʱ�ӷ�Ƶ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_pclkendbg_sel_cfg  : 2;  /* bit[0-1]  : Cluster0_ DebugAPB�ӿ�ʱ��Ƶ�ʱ�ѡ��
                                                                       000:1:2�� 
                                                                       001:1:4�� 
                                                                       010:1:6�� 
                                                                       011:1:8�� */
        unsigned int  cluster0_atclken_sel_cfg    : 2;  /* bit[2-3]  : Cluster0_ ATB�ӿ�ʱ��Ƶ�ʱ�ѡ�� 
                                                                       000:1:2�� 
                                                                       001:1:4�� 
                                                                       010:1:6�� 
                                                                       011:1:8�� */
        unsigned int  cluster0_aclkenm_sel_cfg    : 3;  /* bit[4-6]  : Cluster0_ ACE master�ӿ�ʱ��Ƶ�ʱ�ѡ��
                                                                       000:1:1�� 
                                                                       001:1:2�� 
                                                                       010:1:3�� 
                                                                       011:1:4��
                                                                       100:1:5�� 
                                                                       101:1:6�� 
                                                                       110:1:7�� 
                                                                       111:1:8�� */
        unsigned int  cluster0_atclken_l_sel_cfg  : 1;  /* bit[7-7]  : Cluster0_ traceʱ�Ӷ���Ƶ�ʱ�ѡ��
                                                                       0:1:2�� 
                                                                       1:1:4�� */
        unsigned int  cluster0_pclkendbg_sel_stat : 2;  /* bit[8-9]  : Cluster0_ DebugAPB�ӿ�ʱ��Ƶ�ʱ�ѡ��
                                                                       000:1:2�� 
                                                                       001:1:4�� 
                                                                       010:1:6�� 
                                                                       011:1:8�� */
        unsigned int  cluster0_atclken_sel_stat   : 2;  /* bit[10-11]: Cluster0_ ATB�ӿ�ʱ��Ƶ�ʱ�ѡ�� 
                                                                       000:1:2�� 
                                                                       001:1:4�� 
                                                                       010:1:6�� 
                                                                       011:1:8�� */
        unsigned int  cluster0_aclkenm_sel_stat   : 3;  /* bit[12-14]: Cluster0_ ACE master�ӿ�ʱ��Ƶ�ʱ�ѡ�� ��
                                                                       000:1:1�� 
                                                                       001:1:2�� 
                                                                       010:1:3�� 
                                                                       011:1:4��
                                                                       100:1:5�� 
                                                                       101:1:6�� 
                                                                       110:1:7�� 
                                                                       111:1:8�� */
        unsigned int  cluster0_atclken_l_sel_stat : 1;  /* bit[15-15]: Cluster0_ traceʱ�Ӷ���Ƶ�ʱ�ѡ�� 
                                                                       0:1:2�� 
                                                                       1:1:4�� */
        unsigned int  reserved                    : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUCLKDIV_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUCLKDIV_cluster0_pclkendbg_sel_cfg_START   (0)
#define SOC_PMCTRL_CLUSTER0_CPUCLKDIV_cluster0_pclkendbg_sel_cfg_END     (1)
#define SOC_PMCTRL_CLUSTER0_CPUCLKDIV_cluster0_atclken_sel_cfg_START     (2)
#define SOC_PMCTRL_CLUSTER0_CPUCLKDIV_cluster0_atclken_sel_cfg_END       (3)
#define SOC_PMCTRL_CLUSTER0_CPUCLKDIV_cluster0_aclkenm_sel_cfg_START     (4)
#define SOC_PMCTRL_CLUSTER0_CPUCLKDIV_cluster0_aclkenm_sel_cfg_END       (6)
#define SOC_PMCTRL_CLUSTER0_CPUCLKDIV_cluster0_atclken_l_sel_cfg_START   (7)
#define SOC_PMCTRL_CLUSTER0_CPUCLKDIV_cluster0_atclken_l_sel_cfg_END     (7)
#define SOC_PMCTRL_CLUSTER0_CPUCLKDIV_cluster0_pclkendbg_sel_stat_START  (8)
#define SOC_PMCTRL_CLUSTER0_CPUCLKDIV_cluster0_pclkendbg_sel_stat_END    (9)
#define SOC_PMCTRL_CLUSTER0_CPUCLKDIV_cluster0_atclken_sel_stat_START    (10)
#define SOC_PMCTRL_CLUSTER0_CPUCLKDIV_cluster0_atclken_sel_stat_END      (11)
#define SOC_PMCTRL_CLUSTER0_CPUCLKDIV_cluster0_aclkenm_sel_stat_START    (12)
#define SOC_PMCTRL_CLUSTER0_CPUCLKDIV_cluster0_aclkenm_sel_stat_END      (14)
#define SOC_PMCTRL_CLUSTER0_CPUCLKDIV_cluster0_atclken_l_sel_stat_START  (15)
#define SOC_PMCTRL_CLUSTER0_CPUCLKDIV_cluster0_atclken_l_sel_stat_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUDVFSSTART_UNION
 �ṹ˵��  : CLUSTER0_CPUDVFSSTART �Ĵ����ṹ���塣��ַƫ����:0x0AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU DVFS�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_profile_updn : 1;  /* bit[0-0] : Cluster0_ DVFS������
                                                                    0��Cluster0_ DVFS����Profile������
                                                                    1��Cluster0_ DVFS����Profile������ */
        unsigned int  reserved                  : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUDVFSSTART_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUDVFSSTART_cluster0_cpu_profile_updn_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPUDVFSSTART_cluster0_cpu_profile_updn_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_UNION
 �ṹ˵��  : CLUSTER0_CPUCLKPROFILE0 �Ĵ����ṹ���塣��ַƫ����:0x0B0����ֵ:0x002C0F81�����:32
 �Ĵ���˵��: CLUSTER0_CPUƵ��Profile�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_apll_refdiv    : 6;  /* bit[0-5]  : APLL����ʱ�ӷ�Ƶ������ */
        unsigned int  cluster0_apll_fbdiv     : 12; /* bit[6-17] : APLL����ʱ��������Ƶ������ */
        unsigned int  cluster0_apll_postdiv1  : 3;  /* bit[18-20]: APLL���ʱ�ӷ�Ƶ����1�� */
        unsigned int  cluster0_apll_postdiv2  : 3;  /* bit[21-23]: APLL���ʱ�ӷ�Ƶ����2�� */
        unsigned int  cluster0_apll_sw_target : 2;  /* bit[24-25]: APLL��תĿ�ꡣ */
        unsigned int  reserved                : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_cluster0_apll_refdiv_START     (0)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_cluster0_apll_refdiv_END       (5)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_cluster0_apll_fbdiv_START      (6)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_cluster0_apll_fbdiv_END        (17)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_cluster0_apll_postdiv1_START   (18)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_cluster0_apll_postdiv1_END     (20)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_cluster0_apll_postdiv2_START   (21)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_cluster0_apll_postdiv2_END     (23)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_cluster0_apll_sw_target_START  (24)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_cluster0_apll_sw_target_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_1_UNION
 �ṹ˵��  : CLUSTER0_CPUCLKPROFILE0_1 �Ĵ����ṹ���塣��ַƫ����:0x0B4����ֵ:0x02F80000�����:32
 �Ĵ���˵��: CLUSTER0_CPUƵ��Profile�Ĵ���0_1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_apll_fracdiv : 24; /* bit[0-23] : APLL����ʱ�ӷ�����Ƶ���� */
        unsigned int  cluster0_apll_int_mod : 1;  /* bit[24-24]: APLL������Ƶģʽ��
                                                                 0��������Ƶģʽ��
                                                                 1��������Ƶģʽ��
                                                                 ע�⣺��PLLҪ�����ֻʹ�÷�����Ƶģʽ */
        unsigned int  cluster0_apll_cfg_vld : 1;  /* bit[25-25]: APLL������Ч��־��
                                                                 0��������Ч��
                                                                 1��������Ч�� */
        unsigned int  reserved              : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_1_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_1_cluster0_apll_fracdiv_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_1_cluster0_apll_fracdiv_END    (23)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_1_cluster0_apll_int_mod_START  (24)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_1_cluster0_apll_int_mod_END    (24)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_1_cluster0_apll_cfg_vld_START  (25)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE0_1_cluster0_apll_cfg_vld_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE1_UNION
 �ṹ˵��  : CLUSTER0_CPUCLKPROFILE1 �Ĵ����ṹ���塣��ַƫ����:0x0B8����ֵ:0x000000A1�����:32
 �Ĵ���˵��: CLUSTER0_CPUƵ��Profile�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_pclkendbg_sel_prof : 2;  /* bit[0-1] : Cluster0_ DebugAPB�ӿ�ʱ��Ƶ�ʱ�ѡ��
                                                                      000:1:2�� 
                                                                      001:1:4�� 
                                                                      010:1:6�� 
                                                                      011:1:8�� */
        unsigned int  cluster0_atclken_sel_prof   : 2;  /* bit[2-3] : Cluster0_ ATB�ӿ�ʱ��Ƶ�ʱ�ѡ������� */
        unsigned int  cluster0_aclkenm_sel_prof   : 3;  /* bit[4-6] : Cluster0_ ACE master�ӿ�ʱ��Ƶ�ʱ�ѡ������� */
        unsigned int  cluster0_atclken_l_sel_prof : 1;  /* bit[7-7] : Cluster0_ traceʱ�Ӷ���Ƶ�ʱ�ѡ��
                                                                      0:1:2�� 
                                                                       1:1:4�� */
        unsigned int  reserved                    : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE1_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE1_cluster0_pclkendbg_sel_prof_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE1_cluster0_pclkendbg_sel_prof_END    (1)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE1_cluster0_atclken_sel_prof_START    (2)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE1_cluster0_atclken_sel_prof_END      (3)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE1_cluster0_aclkenm_sel_prof_START    (4)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE1_cluster0_aclkenm_sel_prof_END      (6)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE1_cluster0_atclken_l_sel_prof_START  (7)
#define SOC_PMCTRL_CLUSTER0_CPUCLKPROFILE1_cluster0_atclken_l_sel_prof_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUVOLMOD_UNION
 �ṹ˵��  : CLUSTER0_CPUVOLMOD �Ĵ����ṹ���塣��ַƫ����:0x0BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU DVFSʱ��ѹģʽ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_vol_mod         : 1;  /* bit[0-0] : Cluster0_ DVFSʱ���Ƿ���Ҫ��ѹ��
                                                                       0��Cluster0_ DVFSʱ������Ҫ��ѹ��
                                                                       1��Cluster0_ DVFSʱ����Ҫ��ѹ�� */
        unsigned int  cluster0_cpu_clk_off_vol_mod : 1;  /* bit[1-1] : Cluster0_��ѹʱ��Cluster0_ʱ���Ƿ�رա�
                                                                       0��Cluster0_��ѹʱ��Cluster0_ʱ�ӱ��ִ򿪣�
                                                                       1��Cluster0_��ѹʱ��Cluster0_ʱ��Ҫ��رա� */
        unsigned int  reserved                     : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUVOLMOD_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUVOLMOD_cluster0_cpu_vol_mod_START          (0)
#define SOC_PMCTRL_CLUSTER0_CPUVOLMOD_cluster0_cpu_vol_mod_END            (0)
#define SOC_PMCTRL_CLUSTER0_CPUVOLMOD_cluster0_cpu_clk_off_vol_mod_START  (1)
#define SOC_PMCTRL_CLUSTER0_CPUVOLMOD_cluster0_cpu_clk_off_vol_mod_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUVOLPROFILE_UNION
 �ṹ˵��  : CLUSTER0_CPUVOLPROFILE �Ĵ����ṹ���塣��ַƫ����:0x0C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU��ѹProfile�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_vol_idx : 8;  /* bit[0-7] : Cluster0_��ѹProfile������ */
        unsigned int  reserved             : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUVOLPROFILE_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUVOLPROFILE_cluster0_cpu_vol_idx_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPUVOLPROFILE_cluster0_cpu_vol_idx_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUPHASEMOD_UNION
 �ṹ˵��  : CLUSTER0_CPUPHASEMOD �Ĵ����ṹ���塣��ַƫ����:0xC8����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU DVFSʱ����λģʽ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_phase_mod         : 1;  /* bit[0-0] : Cluster0_ DVFSʱ���Ƿ�ı���λ��
                                                                         0��Cluster0_ DVFSʱ�����ı���λ��
                                                                         1��Cluster0_ DVFSʱ���ı���λ�� */
        unsigned int  cluster0_cpu_clk_off_phase_mod : 1;  /* bit[1-1] : Cluster0_ DVFS�ı���λʱ�Ƿ�ر�Cluster0_ʱ�ӡ�
                                                                         0��Cluster0_�ı���λʱ��Cluster0_ʱ�ӱ��ִ򿪣�
                                                                         1��Cluster0_�ı���λʱ��Cluster0_ʱ�ӹرա� */
        unsigned int  reserved                       : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUPHASEMOD_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUPHASEMOD_cluster0_cpu_phase_mod_START          (0)
#define SOC_PMCTRL_CLUSTER0_CPUPHASEMOD_cluster0_cpu_phase_mod_END            (0)
#define SOC_PMCTRL_CLUSTER0_CPUPHASEMOD_cluster0_cpu_clk_off_phase_mod_START  (1)
#define SOC_PMCTRL_CLUSTER0_CPUPHASEMOD_cluster0_cpu_clk_off_phase_mod_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUPHASEPROFILE_UNION
 �ṹ˵��  : CLUSTER0_CPUPHASEPROFILE �Ĵ����ṹ���塣��ַƫ����:0x0CC����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU��λProfile�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_phase_idx : 8;  /* bit[0-7] : Cluster0_��λProfile������ */
        unsigned int  reserved               : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUPHASEPROFILE_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUPHASEPROFILE_cluster0_cpu_phase_idx_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPUPHASEPROFILE_cluster0_cpu_phase_idx_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUVOLPHASESEL_UNION
 �ṹ˵��  : CLUSTER0_CPUVOLPHASESEL �Ĵ����ṹ���塣��ַƫ����:0x0D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU��ѹ/��λ�����Ⱥ�ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_vol_phase_sel : 1;  /* bit[0-0] : Cluster0_��ѹ/��λ�ź����ѡ��
                                                                     0��DVFSʱ�ȵ���λ�ٵ���ѹ������profile�Ĵ���ʱ����Ҫ�ı䣻
                                                                     1��DVFS�ȵ���ѹ�ڵ���λ������profile�Ĵ���ʱ��Ҫ�ı䣨��ѹprofile�Ĵ���������λ����λprofile�Ĵ������Ƶ�ѹ���� */
        unsigned int  reserved                   : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUVOLPHASESEL_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUVOLPHASESEL_cluster0_cpu_vol_phase_sel_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPUVOLPHASESEL_cluster0_cpu_vol_phase_sel_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_VOLUPSTEPTIME_UNION
 �ṹ˵��  : CLUSTER0_VOLUPSTEPTIME �Ĵ����ṹ���塣��ַƫ����:0x0D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_��ѹ����һ���ȶ�����ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_vol_up_step_time : 13; /* bit[0-12] : Cluster0_ CPU��ѹ�����ȶ�����ʱ�䡣 */
        unsigned int  reserved                  : 19; /* bit[13-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_VOLUPSTEPTIME_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_VOLUPSTEPTIME_cluster0_vol_up_step_time_START  (0)
#define SOC_PMCTRL_CLUSTER0_VOLUPSTEPTIME_cluster0_vol_up_step_time_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_VOLDNSTEPTIME_UNION
 �ṹ˵��  : CLUSTER0_VOLDNSTEPTIME �Ĵ����ṹ���塣��ַƫ����:0x0D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_��ѹ�½�һ���ȶ�����ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_vol_dn_step_time : 13; /* bit[0-12] : Cluster0_ CPU��ѹ�½��ȶ�����ʱ�䡣 */
        unsigned int  reserved                  : 19; /* bit[13-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_VOLDNSTEPTIME_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_VOLDNSTEPTIME_cluster0_vol_dn_step_time_START  (0)
#define SOC_PMCTRL_CLUSTER0_VOLDNSTEPTIME_cluster0_vol_dn_step_time_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_PHASEUPTIME_UNION
 �ṹ˵��  : CLUSTER0_PHASEUPTIME �Ĵ����ṹ���塣��ַƫ����:0x0DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_ DVFSʱ�ı��ѹ��λ�������ȶ�ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_dvfs_phase_up_time : 20; /* bit[0-19] : Cluster0_ DVFSʱ���ı��ѹ��λ�������ȶ�ʱ�䡣 */
        unsigned int  reserved                    : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_PHASEUPTIME_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_PHASEUPTIME_cluster0_dvfs_phase_up_time_START  (0)
#define SOC_PMCTRL_CLUSTER0_PHASEUPTIME_cluster0_dvfs_phase_up_time_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_PHASEDNTIME_UNION
 �ṹ˵��  : CLUSTER0_PHASEDNTIME �Ĵ����ṹ���塣��ַƫ����:0x0E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_ DVFSʱ�ı��ѹ��λ���½��ȶ�ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_dvfs_phase_dn_time : 20; /* bit[0-19] : Cluster0_ DVFSʱ���ı��ѹ��λ���½��ȶ�ʱ�䡣 */
        unsigned int  reserved                    : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_PHASEDNTIME_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_PHASEDNTIME_cluster0_dvfs_phase_dn_time_START  (0)
#define SOC_PMCTRL_CLUSTER0_PHASEDNTIME_cluster0_dvfs_phase_dn_time_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_PMUHOLDTIME_UNION
 �ṹ˵��  : CLUSTER0_PMUHOLDTIME �Ĵ����ṹ���塣��ַƫ����:0x0E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_��ѹ�ȶ�ʱ��ԣ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_pmu_vol_hold_time : 20; /* bit[0-19] : Cluster0_��ѹʱ�����ڶ˿ڴ���ʱ������ӵĵ�ѹ�ȶ�ʱ�� */
        unsigned int  reserved                   : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_PMUHOLDTIME_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_PMUHOLDTIME_cluster0_pmu_vol_hold_time_START  (0)
#define SOC_PMCTRL_CLUSTER0_PMUHOLDTIME_cluster0_pmu_vol_hold_time_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_PMUSEL_UNION
 �ṹ˵��  : CLUSTER0_PMUSEL �Ĵ����ṹ���塣��ַƫ����:0x0E8����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_PMUѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_pmu_sel : 1;  /* bit[0-0] : Cluster0_���PMUѡ��
                                                           0��Cluster0_������źŸ�PMUSSI��
                                                           1��Cluster0_������źŸ�PMUI2C����ֻ�ܾ�̬���ã��� */
        unsigned int  reserved         : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_PMUSEL_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_PMUSEL_cluster0_pmu_sel_START  (0)
#define SOC_PMCTRL_CLUSTER0_PMUSEL_cluster0_pmu_sel_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUAVSEN_UNION
 �ṹ˵��  : CLUSTER0_CPUAVSEN �Ĵ����ṹ���塣��ַƫ����:0x0F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU AVSʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_avs_en        : 1;  /* bit[0-0] : Cluster0_ AVSʹ�ܡ�
                                                                     0��Cluster0_ AVS���ܹرգ�
                                                                     1��Cluster0_ AVS���ܿ����� */
        unsigned int  cluster0_cpu_avs_pwctrl_en : 1;  /* bit[1-1] : Cluster0_ AVS��ѹʹ�ܡ�
                                                                     0��Cluster0_ AVS��ѹ���ܹرգ�
                                                                     1��Cluster0_ AVS��ѹ���ܿ����� */
        unsigned int  reserved                   : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUAVSEN_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUAVSEN_cluster0_cpu_avs_en_START         (0)
#define SOC_PMCTRL_CLUSTER0_CPUAVSEN_cluster0_cpu_avs_en_END           (0)
#define SOC_PMCTRL_CLUSTER0_CPUAVSEN_cluster0_cpu_avs_pwctrl_en_START  (1)
#define SOC_PMCTRL_CLUSTER0_CPUAVSEN_cluster0_cpu_avs_pwctrl_en_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUAVSPARAMOD_UNION
 �ṹ˵��  : CLUSTER0_CPUAVSPARAMOD �Ĵ����ṹ���塣��ַƫ����:0x0F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU AVS����ģʽ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_avspara_mod : 1;  /* bit[0-0] : Cluster0_ AVS����ʵʱ���¿��ơ�
                                                                   ͨ����Cluster0_ AVS������Cluster0_ DVFS����֮����£����������Ĵ���д1��AVS�����������£����������Ĵ���д0����Ч�� */
        unsigned int  reserved                 : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUAVSPARAMOD_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARAMOD_cluster0_cpu_avspara_mod_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARAMOD_cluster0_cpu_avspara_mod_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUAVSPARA0_UNION
 �ṹ˵��  : CLUSTER0_CPUAVSPARA0 �Ĵ����ṹ���塣��ַƫ����:0x0F8����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU AVS�����Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                  : 2;  /* bit[0-1]  : ������ */
        unsigned int  cluster0_cpu_avs_opc_offset : 10; /* bit[2-11] : Cluster0_ AVSԭʼ������ƫ�ơ� */
        unsigned int  cluster0_cpu_avs_rcc        : 5;  /* bit[12-16]: Cluster0_ AVS�ο�У׼�롣 */
        unsigned int  cluster0_cpu_avs_irgap      : 5;  /* bit[17-21]: Cluster0_ AVS IRDropԣ���� */
        unsigned int  cluster0_cpu_avs_opc_mod    : 2;  /* bit[22-23]: Cluster0_ AVS��ͬһ��HPM OPCֵ�Ķ�β�����δ���
                                                                       00��OPCȡ��ֵ��
                                                                       01��OPCȡ��Сֵ��
                                                                       10��OPCȡ���ֵ��
                                                                       11�������� */
        unsigned int  cluster0_cpu_avs_hpm_sel    : 4;  /* bit[24-27]: Cluster0_ AVS�ж��HPM��PCֵ��δ���
                                                                       0000��ȡCPU0 HPM��PCֵ��
                                                                       0001��ȡCPU1 HPM��PCֵ��
                                                                       0010��ȡCPU2 HPM��PCֵ��
                                                                       0011��ȡCPU3 HPM��PCֵ��
                                                                       0100��ȡSCU0 HPM��PCֵ��
                                                                       0101��ȡCPU4 HPM��PCֵ��
                                                                       0110��ȡCPU5 HPM��PCֵ��
                                                                       0111��ȡCPU6 HPM��PCֵ��
                                                                       1000��ȡCPU7 HPM��PCֵ��
                                                                       1001��ȡSCU1 HPM��PCֵ��
                                                                       1010��ȡHPM�е���Сֵ��
                                                                       ������ȡHPM�е����ֵ�� */
        unsigned int  cluster0_cpu_avs_opc_shift  : 3;  /* bit[28-30]: Cluster0_ AVSԭʼ��������λ�� */
        unsigned int  reserved_1                  : 1;  /* bit[31-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUAVSPARA0_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA0_cluster0_cpu_avs_opc_offset_START  (2)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA0_cluster0_cpu_avs_opc_offset_END    (11)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA0_cluster0_cpu_avs_rcc_START         (12)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA0_cluster0_cpu_avs_rcc_END           (16)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA0_cluster0_cpu_avs_irgap_START       (17)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA0_cluster0_cpu_avs_irgap_END         (21)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA0_cluster0_cpu_avs_opc_mod_START     (22)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA0_cluster0_cpu_avs_opc_mod_END       (23)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA0_cluster0_cpu_avs_hpm_sel_START     (24)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA0_cluster0_cpu_avs_hpm_sel_END       (27)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA0_cluster0_cpu_avs_opc_shift_START   (28)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA0_cluster0_cpu_avs_opc_shift_END     (30)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUAVSPARA1_UNION
 �ṹ˵��  : CLUSTER0_CPUAVSPARA1 �Ĵ����ṹ���塣��ַƫ����:0x0FC����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU AVS�����Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_avs_vol_up_gain1 : 4;  /* bit[0-3]  : Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_up_gain2 : 4;  /* bit[4-7]  : Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_up_gain3 : 4;  /* bit[8-11] : Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_up_gain4 : 4;  /* bit[12-15]: Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_up_gain5 : 4;  /* bit[16-19]: Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_up_gain6 : 4;  /* bit[20-23]: Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_up_gain7 : 4;  /* bit[24-27]: Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_up_gain8 : 4;  /* bit[28-31]: Cluster0_ AVS��ѹ���档 */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUAVSPARA1_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA1_cluster0_cpu_avs_vol_up_gain1_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA1_cluster0_cpu_avs_vol_up_gain1_END    (3)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA1_cluster0_cpu_avs_vol_up_gain2_START  (4)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA1_cluster0_cpu_avs_vol_up_gain2_END    (7)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA1_cluster0_cpu_avs_vol_up_gain3_START  (8)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA1_cluster0_cpu_avs_vol_up_gain3_END    (11)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA1_cluster0_cpu_avs_vol_up_gain4_START  (12)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA1_cluster0_cpu_avs_vol_up_gain4_END    (15)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA1_cluster0_cpu_avs_vol_up_gain5_START  (16)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA1_cluster0_cpu_avs_vol_up_gain5_END    (19)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA1_cluster0_cpu_avs_vol_up_gain6_START  (20)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA1_cluster0_cpu_avs_vol_up_gain6_END    (23)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA1_cluster0_cpu_avs_vol_up_gain7_START  (24)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA1_cluster0_cpu_avs_vol_up_gain7_END    (27)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA1_cluster0_cpu_avs_vol_up_gain8_START  (28)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA1_cluster0_cpu_avs_vol_up_gain8_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUAVSPARA2_UNION
 �ṹ˵��  : CLUSTER0_CPUAVSPARA2 �Ĵ����ṹ���塣��ַƫ����:0x100����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU AVS�����Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_avs_vol_up_gain9  : 4;  /* bit[0-3]  : Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_up_gain10 : 4;  /* bit[4-7]  : Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_up_gain11 : 4;  /* bit[8-11] : Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_up_gain12 : 4;  /* bit[12-15]: Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_up_gain13 : 4;  /* bit[16-19]: Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_up_gain14 : 4;  /* bit[20-23]: Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_up_gain15 : 7;  /* bit[24-30]: Cluster0_ AVS��ѹ���档 */
        unsigned int  reserved                       : 1;  /* bit[31-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUAVSPARA2_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA2_cluster0_cpu_avs_vol_up_gain9_START   (0)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA2_cluster0_cpu_avs_vol_up_gain9_END     (3)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA2_cluster0_cpu_avs_vol_up_gain10_START  (4)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA2_cluster0_cpu_avs_vol_up_gain10_END    (7)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA2_cluster0_cpu_avs_vol_up_gain11_START  (8)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA2_cluster0_cpu_avs_vol_up_gain11_END    (11)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA2_cluster0_cpu_avs_vol_up_gain12_START  (12)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA2_cluster0_cpu_avs_vol_up_gain12_END    (15)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA2_cluster0_cpu_avs_vol_up_gain13_START  (16)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA2_cluster0_cpu_avs_vol_up_gain13_END    (19)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA2_cluster0_cpu_avs_vol_up_gain14_START  (20)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA2_cluster0_cpu_avs_vol_up_gain14_END    (23)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA2_cluster0_cpu_avs_vol_up_gain15_START  (24)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA2_cluster0_cpu_avs_vol_up_gain15_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUAVSPARA3_UNION
 �ṹ˵��  : CLUSTER0_CPUAVSPARA3 �Ĵ����ṹ���塣��ַƫ����:0x104����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU AVS�����Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_avs_vol_dn_gain1 : 4;  /* bit[0-3]  : Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_dn_gain2 : 4;  /* bit[4-7]  : Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_dn_gain3 : 4;  /* bit[8-11] : Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_dn_gain4 : 4;  /* bit[12-15]: Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_dn_gain5 : 4;  /* bit[16-19]: Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_dn_gain6 : 4;  /* bit[20-23]: Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_dn_gain7 : 4;  /* bit[24-27]: Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_dn_gain8 : 4;  /* bit[28-31]: Cluster0_ AVS��ѹ���档 */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUAVSPARA3_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA3_cluster0_cpu_avs_vol_dn_gain1_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA3_cluster0_cpu_avs_vol_dn_gain1_END    (3)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA3_cluster0_cpu_avs_vol_dn_gain2_START  (4)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA3_cluster0_cpu_avs_vol_dn_gain2_END    (7)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA3_cluster0_cpu_avs_vol_dn_gain3_START  (8)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA3_cluster0_cpu_avs_vol_dn_gain3_END    (11)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA3_cluster0_cpu_avs_vol_dn_gain4_START  (12)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA3_cluster0_cpu_avs_vol_dn_gain4_END    (15)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA3_cluster0_cpu_avs_vol_dn_gain5_START  (16)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA3_cluster0_cpu_avs_vol_dn_gain5_END    (19)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA3_cluster0_cpu_avs_vol_dn_gain6_START  (20)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA3_cluster0_cpu_avs_vol_dn_gain6_END    (23)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA3_cluster0_cpu_avs_vol_dn_gain7_START  (24)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA3_cluster0_cpu_avs_vol_dn_gain7_END    (27)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA3_cluster0_cpu_avs_vol_dn_gain8_START  (28)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA3_cluster0_cpu_avs_vol_dn_gain8_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUAVSPARA4_UNION
 �ṹ˵��  : CLUSTER0_CPUAVSPARA4 �Ĵ����ṹ���塣��ַƫ����:0x108����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU AVS�����Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_avs_vol_dn_gain9  : 4;  /* bit[0-3]  : Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_dn_gain10 : 4;  /* bit[4-7]  : Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_dn_gain11 : 4;  /* bit[8-11] : Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_dn_gain12 : 4;  /* bit[12-15]: Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_dn_gain13 : 4;  /* bit[16-19]: Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_dn_gain14 : 4;  /* bit[20-23]: Cluster0_ AVS��ѹ���档 */
        unsigned int  cluster0_cpu_avs_vol_dn_gain15 : 7;  /* bit[24-30]: Cluster0_ AVS��ѹ���档 */
        unsigned int  reserved                       : 1;  /* bit[31-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUAVSPARA4_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA4_cluster0_cpu_avs_vol_dn_gain9_START   (0)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA4_cluster0_cpu_avs_vol_dn_gain9_END     (3)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA4_cluster0_cpu_avs_vol_dn_gain10_START  (4)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA4_cluster0_cpu_avs_vol_dn_gain10_END    (7)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA4_cluster0_cpu_avs_vol_dn_gain11_START  (8)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA4_cluster0_cpu_avs_vol_dn_gain11_END    (11)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA4_cluster0_cpu_avs_vol_dn_gain12_START  (12)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA4_cluster0_cpu_avs_vol_dn_gain12_END    (15)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA4_cluster0_cpu_avs_vol_dn_gain13_START  (16)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA4_cluster0_cpu_avs_vol_dn_gain13_END    (19)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA4_cluster0_cpu_avs_vol_dn_gain14_START  (20)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA4_cluster0_cpu_avs_vol_dn_gain14_END    (23)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA4_cluster0_cpu_avs_vol_dn_gain15_START  (24)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA4_cluster0_cpu_avs_vol_dn_gain15_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUAVSPARA5_UNION
 �ṹ˵��  : CLUSTER0_CPUAVSPARA5 �Ĵ����ṹ���塣��ַƫ����:0x10C����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU AVS�����Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_avs_max_vol : 7;  /* bit[0-6]  : Cluster0_ AVS����ѹ���ơ� */
        unsigned int  cluster0_cpu_avs_min_vol : 7;  /* bit[7-13] : Cluster0_ AVS��С��ѹ���ơ� */
        unsigned int  reserved                 : 18; /* bit[14-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUAVSPARA5_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA5_cluster0_cpu_avs_max_vol_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA5_cluster0_cpu_avs_max_vol_END    (6)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA5_cluster0_cpu_avs_min_vol_START  (7)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA5_cluster0_cpu_avs_min_vol_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUAVSPARA6_UNION
 �ṹ˵��  : CLUSTER0_CPUAVSPARA6 �Ĵ����ṹ���塣��ַƫ����:0x110����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU AVSʹ�ܼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_avs_sample_num : 22; /* bit[0-21] : Cluster0_ AVS�������������������ֵ������2��N�η��� */
        unsigned int  reserved                    : 10; /* bit[22-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUAVSPARA6_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA6_cluster0_cpu_avs_sample_num_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPUAVSPARA6_cluster0_cpu_avs_sample_num_END    (21)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUHPMTYP_UNION
 �ṹ˵��  : CLUSTER0_CPUHPMTYP �Ĵ����ṹ���塣��ַƫ����:0x114����ֵ:0x000007C0�����:32
 �Ĵ���˵��: CLUSTER0_CPU HPM����ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_hpm_type  : 1;  /* bit[0]    : AVSѡ��ʹ��CPU HPM���͡�
                                                                  0��AVSѡ��ʹ�ñ�׼HPM��
                                                                  1��AVSѡ��ʹ��X��HPM�� */
        unsigned int  cluster0_cpu0_hpm_mask : 1;  /* bit[1]    : AVS�����Ƿ�����CPU0 HPM��
                                                                  0�������Σ�
                                                                  1�����Ρ� */
        unsigned int  cluster0_cpu1_hpm_mask : 1;  /* bit[2]    : AVS�����Ƿ�����CPU1 HPM��
                                                                  0�������Σ�
                                                                  1�����Ρ� */
        unsigned int  cluster0_cpu2_hpm_mask : 1;  /* bit[3]    : AVS�����Ƿ�����CPU2 HPM��
                                                                  0�������Σ�
                                                                  1�����Ρ� */
        unsigned int  cluster0_cpu3_hpm_mask : 1;  /* bit[4]    : AVS�����Ƿ�����CPU3 HPM��
                                                                  0�������Σ�
                                                                  1�����Ρ� */
        unsigned int  cluster0_scu0_hpm_mask : 1;  /* bit[5]    : AVS�����Ƿ�����SCU0 HPM��
                                                                  0�������Σ�
                                                                  1�����Ρ� */
        unsigned int  cluster0_cpu4_hpm_mask : 1;  /* bit[6]    : AVS�����Ƿ�����CPU4 HPM��
                                                                  0�������Σ�
                                                                  1�����Ρ� */
        unsigned int  cluster0_cpu5_hpm_mask : 1;  /* bit[7]    : AVS�����Ƿ�����CPU5 HPM��
                                                                  0�������Σ�
                                                                  1�����Ρ� */
        unsigned int  cluster0_cpu6_hpm_mask : 1;  /* bit[8]    : AVS�����Ƿ�����CPU6 HPM��
                                                                  0�������Σ�
                                                                  1�����Ρ� */
        unsigned int  cluster0_cpu7_hpm_mask : 1;  /* bit[9]    : AVS�����Ƿ�����CPU7 HPM��
                                                                  0�������Σ�
                                                                  1�����Ρ� */
        unsigned int  cluster0_scu1_hpm_mask : 1;  /* bit[10]   : AVS�����Ƿ�����SCU1 HPM��
                                                                  0�������Σ�
                                                                  1�����Ρ� */
        unsigned int  reserved               : 5;  /* bit[11-15]: ������ */
        unsigned int  biten                  : 16; /* bit[16-31]: ÿ������λ��ʹ��λ��
                                                                  ֻ�е�biten��Ӧ�ı���λΪ1'b1����Ӧ�ı���λ�������á�biten[0]����bit 0��ʹ��λ��д1��Ч�� */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUHPMTYP_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_cpu_hpm_type_START   (0)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_cpu_hpm_type_END     (0)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_cpu0_hpm_mask_START  (1)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_cpu0_hpm_mask_END    (1)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_cpu1_hpm_mask_START  (2)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_cpu1_hpm_mask_END    (2)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_cpu2_hpm_mask_START  (3)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_cpu2_hpm_mask_END    (3)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_cpu3_hpm_mask_START  (4)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_cpu3_hpm_mask_END    (4)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_scu0_hpm_mask_START  (5)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_scu0_hpm_mask_END    (5)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_cpu4_hpm_mask_START  (6)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_cpu4_hpm_mask_END    (6)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_cpu5_hpm_mask_START  (7)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_cpu5_hpm_mask_END    (7)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_cpu6_hpm_mask_START  (8)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_cpu6_hpm_mask_END    (8)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_cpu7_hpm_mask_START  (9)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_cpu7_hpm_mask_END    (9)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_scu1_hpm_mask_START  (10)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_cluster0_scu1_hpm_mask_END    (10)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_biten_START                   (16)
#define SOC_PMCTRL_CLUSTER0_CPUHPMTYP_biten_END                     (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPU01HPMEN_UNION
 �ṹ˵��  : CLUSTER0_CPU01HPMEN �Ĵ����ṹ���塣��ַƫ����:0x118����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU01 HPMʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu0_hpm_en_cfg  : 1;  /* bit[0-0] : CPU0 HPMʹ�ܡ�
                                                                    HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster0_cpu1_hpm_en_cfg  : 1;  /* bit[1-1] : CPU1 HPMʹ�ܡ�
                                                                    HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster0_scu_hpm_en_cfg   : 1;  /* bit[2-2] : SCU HPMʹ�ܡ�
                                                                    HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_0                : 1;  /* bit[3-3] : ������ */
        unsigned int  cluster0_cpu0_hpm_en_stat : 1;  /* bit[4-4] : CPU0 HPMʹ�ܡ�
                                                                    HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster0_cpu1_hpm_en_stat : 1;  /* bit[5-5] : CPU1 HPMʹ�ܡ�
                                                                    HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster0_scu_hpm_en_stat  : 1;  /* bit[6-6] : SCU HPMʹ�ܡ�
                                                                    HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_1                : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPU01HPMEN_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPU01HPMEN_cluster0_cpu0_hpm_en_cfg_START   (0)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMEN_cluster0_cpu0_hpm_en_cfg_END     (0)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMEN_cluster0_cpu1_hpm_en_cfg_START   (1)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMEN_cluster0_cpu1_hpm_en_cfg_END     (1)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMEN_cluster0_scu_hpm_en_cfg_START    (2)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMEN_cluster0_scu_hpm_en_cfg_END      (2)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMEN_cluster0_cpu0_hpm_en_stat_START  (4)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMEN_cluster0_cpu0_hpm_en_stat_END    (4)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMEN_cluster0_cpu1_hpm_en_stat_START  (5)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMEN_cluster0_cpu1_hpm_en_stat_END    (5)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMEN_cluster0_scu_hpm_en_stat_START   (6)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMEN_cluster0_scu_hpm_en_stat_END     (6)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPU01HPMXEN_UNION
 �ṹ˵��  : CLUSTER0_CPU01HPMXEN �Ĵ����ṹ���塣��ַƫ����:0x11C����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU01 HPMXʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu0_hpmx_en_cfg  : 1;  /* bit[0-0] : CPU0 HPMʹ�ܡ�
                                                                     HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster0_cpu1_hpmx_en_cfg  : 1;  /* bit[1-1] : CPU1 HPMʹ�ܡ�
                                                                     HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster0_scu_hpmx_en_cfg   : 1;  /* bit[2-2] : SCU HPMʹ�ܡ�
                                                                     HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_0                 : 1;  /* bit[3-3] : ������ */
        unsigned int  cluster0_cpu0_hpmx_en_stat : 1;  /* bit[4-4] : CPU0 HPMʹ�ܡ�
                                                                     HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster0_cpu1_hpmx_en_stat : 1;  /* bit[5-5] : CPU1 HPMʹ�ܡ�
                                                                     HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster0_scu_hpmx_en_stat  : 1;  /* bit[6-6] : SCU HPMʹ�ܡ�
                                                                     HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_1                 : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPU01HPMXEN_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPU01HPMXEN_cluster0_cpu0_hpmx_en_cfg_START   (0)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMXEN_cluster0_cpu0_hpmx_en_cfg_END     (0)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMXEN_cluster0_cpu1_hpmx_en_cfg_START   (1)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMXEN_cluster0_cpu1_hpmx_en_cfg_END     (1)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMXEN_cluster0_scu_hpmx_en_cfg_START    (2)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMXEN_cluster0_scu_hpmx_en_cfg_END      (2)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMXEN_cluster0_cpu0_hpmx_en_stat_START  (4)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMXEN_cluster0_cpu0_hpmx_en_stat_END    (4)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMXEN_cluster0_cpu1_hpmx_en_stat_START  (5)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMXEN_cluster0_cpu1_hpmx_en_stat_END    (5)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMXEN_cluster0_scu_hpmx_en_stat_START   (6)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMXEN_cluster0_scu_hpmx_en_stat_END     (6)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPU01HPMOPCVALID_UNION
 �ṹ˵��  : CLUSTER0_CPU01HPMOPCVALID �Ĵ����ṹ���塣��ַƫ����:0x120����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU01 HPM OPC��Ч�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu0_hpm_opc_vld  : 1;  /* bit[0-0] : CPU0 HPMԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  cluster0_cpu1_hpm_opc_vld  : 1;  /* bit[1-1] : CPU1 HPMԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  cluster0_scu_hpm_opc_vld   : 1;  /* bit[2-2] : SCU HPMԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  cluster0_cpu0_hpmx_opc_vld : 1;  /* bit[3-3] : CPU0 HPMXԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  cluster0_cpu1_hpmx_opc_vld : 1;  /* bit[4-4] : CPU1 HPMXԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  cluster0_scu_hpmx_opc_vld  : 1;  /* bit[5-5] : SCU HPMXԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  reserved                   : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPU01HPMOPCVALID_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPU01HPMOPCVALID_cluster0_cpu0_hpm_opc_vld_START   (0)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMOPCVALID_cluster0_cpu0_hpm_opc_vld_END     (0)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMOPCVALID_cluster0_cpu1_hpm_opc_vld_START   (1)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMOPCVALID_cluster0_cpu1_hpm_opc_vld_END     (1)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMOPCVALID_cluster0_scu_hpm_opc_vld_START    (2)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMOPCVALID_cluster0_scu_hpm_opc_vld_END      (2)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMOPCVALID_cluster0_cpu0_hpmx_opc_vld_START  (3)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMOPCVALID_cluster0_cpu0_hpmx_opc_vld_END    (3)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMOPCVALID_cluster0_cpu1_hpmx_opc_vld_START  (4)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMOPCVALID_cluster0_cpu1_hpmx_opc_vld_END    (4)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMOPCVALID_cluster0_scu_hpmx_opc_vld_START   (5)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMOPCVALID_cluster0_scu_hpmx_opc_vld_END     (5)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPU01HPMOPC_UNION
 �ṹ˵��  : CLUSTER0_CPU01HPMOPC �Ĵ����ṹ���塣��ַƫ����:0x124����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU01 HPM OPC�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu0_hpm_opc : 10; /* bit[0-9]  : CPU0 HPMԭʼ�����롣 */
        unsigned int  cluster0_cpu1_hpm_opc : 10; /* bit[10-19]: CPU1 HPMԭʼ�����롣 */
        unsigned int  cluster0_scu_hpm_opc  : 10; /* bit[20-29]: SCU HPMԭʼ�����롣 */
        unsigned int  reserved              : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPU01HPMOPC_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPU01HPMOPC_cluster0_cpu0_hpm_opc_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMOPC_cluster0_cpu0_hpm_opc_END    (9)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMOPC_cluster0_cpu1_hpm_opc_START  (10)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMOPC_cluster0_cpu1_hpm_opc_END    (19)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMOPC_cluster0_scu_hpm_opc_START   (20)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMOPC_cluster0_scu_hpm_opc_END     (29)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPU01HPMXOPC_UNION
 �ṹ˵��  : CLUSTER0_CPU01HPMXOPC �Ĵ����ṹ���塣��ַƫ����:0x128����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU01 HPMX OPC�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu0_hpmx_opc : 10; /* bit[0-9]  : CPU0 HPMXԭʼ�����롣 */
        unsigned int  cluster0_cpu1_hpmx_opc : 10; /* bit[10-19]: CPU1 HPMXԭʼ�����롣 */
        unsigned int  cluster0_scu_hpmx_opc  : 10; /* bit[20-29]: SCU HPMXԭʼ�����롣 */
        unsigned int  reserved               : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPU01HPMXOPC_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPU01HPMXOPC_cluster0_cpu0_hpmx_opc_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMXOPC_cluster0_cpu0_hpmx_opc_END    (9)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMXOPC_cluster0_cpu1_hpmx_opc_START  (10)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMXOPC_cluster0_cpu1_hpmx_opc_END    (19)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMXOPC_cluster0_scu_hpmx_opc_START   (20)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMXOPC_cluster0_scu_hpmx_opc_END     (29)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPU01HPMPC_UNION
 �ṹ˵��  : CLUSTER0_CPU01HPMPC �Ĵ����ṹ���塣��ַƫ����:0x12C����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU01 HPM PC�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu0_hpm_pc_avs : 10; /* bit[0-9]  : CPU0 HPM�����롣 */
        unsigned int  cluster0_cpu1_hpm_pc_avs : 10; /* bit[10-19]: CPU1 HPM�����롣 */
        unsigned int  cluster0_scu_hpm_pc_avs  : 10; /* bit[20-29]: SCU HPM�����롣 */
        unsigned int  reserved                 : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPU01HPMPC_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPU01HPMPC_cluster0_cpu0_hpm_pc_avs_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMPC_cluster0_cpu0_hpm_pc_avs_END    (9)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMPC_cluster0_cpu1_hpm_pc_avs_START  (10)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMPC_cluster0_cpu1_hpm_pc_avs_END    (19)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMPC_cluster0_scu_hpm_pc_avs_START   (20)
#define SOC_PMCTRL_CLUSTER0_CPU01HPMPC_cluster0_scu_hpm_pc_avs_END     (29)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPU23HPMEN_UNION
 �ṹ˵��  : CLUSTER0_CPU23HPMEN �Ĵ����ṹ���塣��ַƫ����:0x134����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU23 HPMʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu2_hpm_en_cfg  : 1;  /* bit[0-0] : CPU2 HPMʹ�ܡ�
                                                                    HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster0_cpu3_hpm_en_cfg  : 1;  /* bit[1-1] : CPU3 HPMʹ�ܡ�
                                                                    HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_0                : 1;  /* bit[2-2] : ������ */
        unsigned int  reserved_1                : 1;  /* bit[3-3] : ������ */
        unsigned int  cluster0_cpu2_hpm_en_stat : 1;  /* bit[4-4] : CPU2 HPMʹ�ܡ�
                                                                    HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster0_cpu3_hpm_en_stat : 1;  /* bit[5-5] : CPU3 HPMʹ�ܡ�
                                                                    HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_2                : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPU23HPMEN_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPU23HPMEN_cluster0_cpu2_hpm_en_cfg_START   (0)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMEN_cluster0_cpu2_hpm_en_cfg_END     (0)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMEN_cluster0_cpu3_hpm_en_cfg_START   (1)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMEN_cluster0_cpu3_hpm_en_cfg_END     (1)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMEN_cluster0_cpu2_hpm_en_stat_START  (4)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMEN_cluster0_cpu2_hpm_en_stat_END    (4)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMEN_cluster0_cpu3_hpm_en_stat_START  (5)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMEN_cluster0_cpu3_hpm_en_stat_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPU23HPMXEN_UNION
 �ṹ˵��  : CLUSTER0_CPU23HPMXEN �Ĵ����ṹ���塣��ַƫ����:0x138����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU23 HPMXʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu2_hpmx_en_cfg  : 1;  /* bit[0-0] : CPU2 HPMXʹ�ܡ�
                                                                     HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster0_cpu3_hpmx_en_cfg  : 1;  /* bit[1-1] : CPU3 HPMXʹ�ܡ�
                                                                     HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_0                 : 1;  /* bit[2-2] : ������ */
        unsigned int  reserved_1                 : 1;  /* bit[3-3] : ������ */
        unsigned int  cluster0_cpu2_hpmx_en_stat : 1;  /* bit[4-4] : CPU2 HPMXʹ�ܡ�
                                                                     HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster0_cpu3_hpmx_en_stat : 1;  /* bit[5-5] : CPU3 HPMXʹ�ܡ�
                                                                     HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_2                 : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPU23HPMXEN_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPU23HPMXEN_cluster0_cpu2_hpmx_en_cfg_START   (0)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMXEN_cluster0_cpu2_hpmx_en_cfg_END     (0)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMXEN_cluster0_cpu3_hpmx_en_cfg_START   (1)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMXEN_cluster0_cpu3_hpmx_en_cfg_END     (1)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMXEN_cluster0_cpu2_hpmx_en_stat_START  (4)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMXEN_cluster0_cpu2_hpmx_en_stat_END    (4)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMXEN_cluster0_cpu3_hpmx_en_stat_START  (5)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMXEN_cluster0_cpu3_hpmx_en_stat_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPU23HPMOPCVALID_UNION
 �ṹ˵��  : CLUSTER0_CPU23HPMOPCVALID �Ĵ����ṹ���塣��ַƫ����:0x13C����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU23 HPM OPC��Ч�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu2_hpm_opc_vld  : 1;  /* bit[0-0] : CPU2 HPMԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  cluster0_cpu3_hpm_opc_vld  : 1;  /* bit[1-1] : CPU3 HPMԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  cluster0_cpu2_hpmx_opc_vld : 1;  /* bit[2-2] : CPU2 HPMXԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  cluster0_cpu3_hpmx_opc_vld : 1;  /* bit[3-3] : CPU3 HPMXԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  reserved                   : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPU23HPMOPCVALID_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPU23HPMOPCVALID_cluster0_cpu2_hpm_opc_vld_START   (0)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMOPCVALID_cluster0_cpu2_hpm_opc_vld_END     (0)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMOPCVALID_cluster0_cpu3_hpm_opc_vld_START   (1)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMOPCVALID_cluster0_cpu3_hpm_opc_vld_END     (1)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMOPCVALID_cluster0_cpu2_hpmx_opc_vld_START  (2)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMOPCVALID_cluster0_cpu2_hpmx_opc_vld_END    (2)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMOPCVALID_cluster0_cpu3_hpmx_opc_vld_START  (3)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMOPCVALID_cluster0_cpu3_hpmx_opc_vld_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPU23HPMOPC_UNION
 �ṹ˵��  : CLUSTER0_CPU23HPMOPC �Ĵ����ṹ���塣��ַƫ����:0x140����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU23 HPM OPC�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu2_hpm_opc : 10; /* bit[0-9]  : CPU2 HPMԭʼ�����롣 */
        unsigned int  cluster0_cpu3_hpm_opc : 10; /* bit[10-19]: CPU3 HPMԭʼ�����롣 */
        unsigned int  reserved              : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPU23HPMOPC_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPU23HPMOPC_cluster0_cpu2_hpm_opc_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMOPC_cluster0_cpu2_hpm_opc_END    (9)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMOPC_cluster0_cpu3_hpm_opc_START  (10)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMOPC_cluster0_cpu3_hpm_opc_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPU23HPMXOPC_UNION
 �ṹ˵��  : CLUSTER0_CPU23HPMXOPC �Ĵ����ṹ���塣��ַƫ����:0x144����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU23 HPMX OPC�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu2_hpmx_opc : 10; /* bit[0-9]  : CPU2 HPMXԭʼ�����롣 */
        unsigned int  cluster0_cpu3_hpmx_opc : 10; /* bit[10-19]: CPU3 HPMXԭʼ�����롣 */
        unsigned int  reserved               : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPU23HPMXOPC_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPU23HPMXOPC_cluster0_cpu2_hpmx_opc_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMXOPC_cluster0_cpu2_hpmx_opc_END    (9)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMXOPC_cluster0_cpu3_hpmx_opc_START  (10)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMXOPC_cluster0_cpu3_hpmx_opc_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPU23HPMPC_UNION
 �ṹ˵��  : CLUSTER0_CPU23HPMPC �Ĵ����ṹ���塣��ַƫ����:0x148����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU23 HPM PC�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu2_hpm_pc_avs : 10; /* bit[0-9]  : CPU2 HPM�����롣 */
        unsigned int  cluster0_cpu3_hpm_pc_avs : 10; /* bit[10-19]: CPU3 HPM�����롣 */
        unsigned int  reserved                 : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPU23HPMPC_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPU23HPMPC_cluster0_cpu2_hpm_pc_avs_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMPC_cluster0_cpu2_hpm_pc_avs_END    (9)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMPC_cluster0_cpu3_hpm_pc_avs_START  (10)
#define SOC_PMCTRL_CLUSTER0_CPU23HPMPC_cluster0_cpu3_hpm_pc_avs_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUHPMCLKDIV_UNION
 �ṹ˵��  : CLUSTER0_CPUHPMCLKDIV �Ĵ����ṹ���塣��ַƫ����:0x150����ֵ:0x00000001�����:32
 �Ĵ���˵��: CLUSTER0_CPU HPMʱ�ӷ�Ƶ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_avs_hpm_div : 6;  /* bit[0-5] : Cluster0 HPMʱ�ӷ�Ƶ���� */
        unsigned int  reserved                 : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUHPMCLKDIV_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUHPMCLKDIV_cluster0_cpu_avs_hpm_div_START  (0)
#define SOC_PMCTRL_CLUSTER0_CPUHPMCLKDIV_cluster0_cpu_avs_hpm_div_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER0_CPUAVSVOLIDX_UNION
 �ṹ˵��  : CLUSTER0_CPUAVSVOLIDX �Ĵ����ṹ���塣��ַƫ����:0x154����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER0_CPU AVS��ѹ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_avs_vol_idx_cfg  : 8;  /* bit[0-7]  : Cluster0 AVS��ǰ��ѹֵ����ֵ����ͨ����������øüĴ���ʱbit 8��д1������Ҫ�üĴ���ֵ��PMU��ѹֵ��ͬ��  */
        unsigned int  cluster0_cpu_vol_chg_sftreq   : 1;  /* bit[8-8]  : Cluster0 CPU��ѹ�ı���������źš�
                                                                         д1������ı��ѹ����ѹֵΪbit 7:0ֵ
                                                                         д0����Ч���� */
        unsigned int  reserved_0                    : 3;  /* bit[9-11] :  */
        unsigned int  cluster0_cpu_avs_vol_idx_stat : 8;  /* bit[12-19]: Cluster0 AVS��ǰ��ѹֵ����ֵ����ͨ����������øüĴ���ʱbit 8��д1������Ҫ�üĴ���ֵ��PMU��ѹֵ��ͬ�� */
        unsigned int  reserved_1                    : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER0_CPUAVSVOLIDX_UNION;
#endif
#define SOC_PMCTRL_CLUSTER0_CPUAVSVOLIDX_cluster0_cpu_avs_vol_idx_cfg_START   (0)
#define SOC_PMCTRL_CLUSTER0_CPUAVSVOLIDX_cluster0_cpu_avs_vol_idx_cfg_END     (7)
#define SOC_PMCTRL_CLUSTER0_CPUAVSVOLIDX_cluster0_cpu_vol_chg_sftreq_START    (8)
#define SOC_PMCTRL_CLUSTER0_CPUAVSVOLIDX_cluster0_cpu_vol_chg_sftreq_END      (8)
#define SOC_PMCTRL_CLUSTER0_CPUAVSVOLIDX_cluster0_cpu_avs_vol_idx_stat_START  (12)
#define SOC_PMCTRL_CLUSTER0_CPUAVSVOLIDX_cluster0_cpu_avs_vol_idx_stat_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUDVFSMOD_UNION
 �ṹ˵��  : CLUSTER1_CPUDVFSMOD �Ĵ����ṹ���塣��ַƫ����:0x158����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU DVFSģʽ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu_dvfs_mod : 1;  /* bit[0-0] : Cluster1 DVFSģʽѡ��
                                                                0���л�APLLģʽ��
                                                                1������Ƶģʽ���̶�APLL����
                                                                ������Ϊ����Ƶģʽʱ��PLL Lock Mod��������Ϊ�ȴ���ʱģʽ�� */
        unsigned int  reserved              : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUDVFSMOD_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUDVFSMOD_cluster1_cpu_dvfs_mod_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPUDVFSMOD_cluster1_cpu_dvfs_mod_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUCLKSEL_UNION
 �ṹ˵��  : CLUSTER1_CPUCLKSEL �Ĵ����ṹ���塣��ַƫ����:0x15C����ֵ:0x00000002�����:32
 �Ĵ���˵��: CLUSTER1_CPU ʱ����Դѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_clk_sel : 2;  /* bit[0-1] : Cluster1_ʱ��ѡ���ĸ�ʱ����Դ��
                                                           00��Cluster1_ʱ��ѡ��480Mhz��
                                                           01��Cluster1_ʱ��ѡ��19.2MHz��
                                                           1X��Cluster1_ʱ��ѡ��APLL�� */
        unsigned int  reserved         : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUCLKSEL_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUCLKSEL_cluster1_clk_sel_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPUCLKSEL_cluster1_clk_sel_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUDVFSEN_UNION
 �ṹ˵��  : CLUSTER1_CPUDVFSEN �Ĵ����ṹ���塣��ַƫ����:0x160����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU DVFSʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu_dvfs_en : 1;  /* bit[0-0] : Cluster1_ DVFSʹ�ܡ�
                                                               0��Cluster1_ DVFS���ܹرգ�
                                                               1��Cluster1_ DVFS���ܿ����� */
        unsigned int  reserved             : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUDVFSEN_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUDVFSEN_cluster1_cpu_dvfs_en_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPUDVFSEN_cluster1_cpu_dvfs_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUPLLSEL_UNION
 �ṹ˵��  : CLUSTER1_CPUPLLSEL �Ĵ����ṹ���塣��ַƫ����:0x164����ֵ:0x00000121�����:32
 �Ĵ���˵��: CLUSTER1_CPU PLLѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_apll_sel_cfg  : 2;  /* bit[0-1]  : Cluster1_ʱ��ѡ���ĸ�PLL��
                                                                  00��Cluster1_ʱ��ѡ��APLL0��
                                                                  01��Cluster1_ʱ��ѡ��APLL1��
                                                                  1X��Cluster1_ʱ��ѡ��APLL2�� */
        unsigned int  cluster1_pll_sw_ack    : 5;  /* bit[2-6]  : ��ǰCluster1_ʱ��ѡ���ĸ�ʱ�ӵ�״ָ̬ʾ��
                                                                  00001��Cluster1_ʱ��ѡ��480Mhz��
                                                                  00010��Cluster1_ʱ��ѡ��19.2MHz��
                                                                  00100��Cluster1_ʱ��ѡ��APLL0��
                                                                  01000��Cluster1_ʱ��ѡ��APLL1��
                                                                  10000��Cluster1_ʱ��ѡ��APLL2�� */
        unsigned int  reserved_0             : 1;  /* bit[7-7]  : ������ */
        unsigned int  cluster1_apll_sel_stat : 2;  /* bit[8-9]  : Cluster1_ʱ��ѡ���ĸ�PLL��
                                                                  00��Cluster1_ʱ��ѡ��APLL0��
                                                                  01��Cluster1_ʱ��ѡ��APLL1��
                                                                  1X��Cluster1_ʱ��ѡ��APLL2�� */
        unsigned int  reserved_1             : 22; /* bit[10-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUPLLSEL_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUPLLSEL_cluster1_apll_sel_cfg_START   (0)
#define SOC_PMCTRL_CLUSTER1_CPUPLLSEL_cluster1_apll_sel_cfg_END     (1)
#define SOC_PMCTRL_CLUSTER1_CPUPLLSEL_cluster1_pll_sw_ack_START     (2)
#define SOC_PMCTRL_CLUSTER1_CPUPLLSEL_cluster1_pll_sw_ack_END       (6)
#define SOC_PMCTRL_CLUSTER1_CPUPLLSEL_cluster1_apll_sel_stat_START  (8)
#define SOC_PMCTRL_CLUSTER1_CPUPLLSEL_cluster1_apll_sel_stat_END    (9)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUCLKDIV_UNION
 �ṹ˵��  : CLUSTER1_CPUCLKDIV �Ĵ����ṹ���塣��ַƫ����:0x168����ֵ:0x0000A1A1�����:32
 �Ĵ���˵��: CLUSTER1_CPUʱ�ӷ�Ƶ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_pclkendbg_sel_cfg  : 2;  /* bit[0-1]  : Cluster1_ DebugAPB�ӿ�ʱ��Ƶ�ʱ�ѡ�� 
                                                                       000:1:2�� 
                                                                       001:1:4�� 
                                                                       010:1:6�� 
                                                                       011:1:8�� */
        unsigned int  cluster1_atclken_sel_cfg    : 2;  /* bit[2-3]  : Cluster1_ ATB�ӿ�ʱ��Ƶ�ʱ�ѡ�� 
                                                                       000:1:2�� 
                                                                       001:1:4�� 
                                                                       010:1:6�� 
                                                                       011:1:8�� */
        unsigned int  cluster1_aclkenm_sel_cfg    : 3;  /* bit[4-6]  : Cluster1_ ACE master�ӿ�ʱ��Ƶ�ʱ�ѡ�� 
                                                                       000:1:1�� 
                                                                       001:1:2�� 
                                                                       010:1:3�� 
                                                                       011:1:4��
                                                                       100:1:5�� 
                                                                       101:1:6�� 
                                                                       110:1:7�� 
                                                                       111:1:8�� */
        unsigned int  cluster1_atclken_l_sel_cfg  : 1;  /* bit[7-7]  : Cluster1_ traceʱ�Ӷ���Ƶ�ʱ�ѡ�� 
                                                                       0:1:2��
                                                                       1:1:4�� */
        unsigned int  cluster1_pclkendbg_sel_stat : 2;  /* bit[8-9]  : Cluster1_ DebugAPB�ӿ�ʱ��Ƶ�ʱ�ѡ�� 
                                                                       000:1:2�� 
                                                                       001:1:4�� 
                                                                       010:1:6�� 
                                                                       011:1:8�� */
        unsigned int  cluster1_atclken_sel_stat   : 2;  /* bit[10-11]: Cluster1_ ATB�ӿ�ʱ��Ƶ�ʱ�ѡ�� 
                                                                       000:1:2��
                                                                       001:1:4�� 
                                                                       010:1:6�� 
                                                                       011:1:8�� */
        unsigned int  cluster1_aclkenm_sel_stat   : 3;  /* bit[12-14]: Cluster1_ ACE master�ӿ�ʱ��Ƶ�ʱ�ѡ��
                                                                       000:1:1��
                                                                       001:1:2�� 
                                                                       010:1:3�� 
                                                                       011:1:4��
                                                                       100:1:5�� 
                                                                       101:1:6�� 
                                                                       110:1:7�� 
                                                                       111:1:8�� */
        unsigned int  cluster1_atclken_l_sel_stat : 1;  /* bit[15-15]: Cluster1_ traceʱ�Ӷ���Ƶ�ʱ�ѡ�� 
                                                                       0:1:2�� 
                                                                       1:1:4�� */
        unsigned int  reserved                    : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUCLKDIV_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUCLKDIV_cluster1_pclkendbg_sel_cfg_START   (0)
#define SOC_PMCTRL_CLUSTER1_CPUCLKDIV_cluster1_pclkendbg_sel_cfg_END     (1)
#define SOC_PMCTRL_CLUSTER1_CPUCLKDIV_cluster1_atclken_sel_cfg_START     (2)
#define SOC_PMCTRL_CLUSTER1_CPUCLKDIV_cluster1_atclken_sel_cfg_END       (3)
#define SOC_PMCTRL_CLUSTER1_CPUCLKDIV_cluster1_aclkenm_sel_cfg_START     (4)
#define SOC_PMCTRL_CLUSTER1_CPUCLKDIV_cluster1_aclkenm_sel_cfg_END       (6)
#define SOC_PMCTRL_CLUSTER1_CPUCLKDIV_cluster1_atclken_l_sel_cfg_START   (7)
#define SOC_PMCTRL_CLUSTER1_CPUCLKDIV_cluster1_atclken_l_sel_cfg_END     (7)
#define SOC_PMCTRL_CLUSTER1_CPUCLKDIV_cluster1_pclkendbg_sel_stat_START  (8)
#define SOC_PMCTRL_CLUSTER1_CPUCLKDIV_cluster1_pclkendbg_sel_stat_END    (9)
#define SOC_PMCTRL_CLUSTER1_CPUCLKDIV_cluster1_atclken_sel_stat_START    (10)
#define SOC_PMCTRL_CLUSTER1_CPUCLKDIV_cluster1_atclken_sel_stat_END      (11)
#define SOC_PMCTRL_CLUSTER1_CPUCLKDIV_cluster1_aclkenm_sel_stat_START    (12)
#define SOC_PMCTRL_CLUSTER1_CPUCLKDIV_cluster1_aclkenm_sel_stat_END      (14)
#define SOC_PMCTRL_CLUSTER1_CPUCLKDIV_cluster1_atclken_l_sel_stat_START  (15)
#define SOC_PMCTRL_CLUSTER1_CPUCLKDIV_cluster1_atclken_l_sel_stat_END    (15)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUDVFSSTART_UNION
 �ṹ˵��  : CLUSTER1_CPUDVFSSTART �Ĵ����ṹ���塣��ַƫ����:0x16C����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU DVFS�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu_profile_updn : 1;  /* bit[0-0] : Cluster1_ DVFS������
                                                                    0��Cluster1_ DVFS����Profile������
                                                                    1��Cluster1_ DVFS����Profile������ */
        unsigned int  reserved                  : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUDVFSSTART_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUDVFSSTART_cluster1_cpu_profile_updn_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPUDVFSSTART_cluster1_cpu_profile_updn_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_UNION
 �ṹ˵��  : CLUSTER1_CPUCLKPROFILE0 �Ĵ����ṹ���塣��ַƫ����:0x170����ֵ:0x002C0F81�����:32
 �Ĵ���˵��: CLUSTER1_CPUƵ��Profile�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_apll_refdiv    : 6;  /* bit[0-5]  : APLL����ʱ�ӷ�Ƶ������ */
        unsigned int  cluster1_apll_fbdiv     : 12; /* bit[6-17] : APLL����ʱ��������Ƶ������ */
        unsigned int  cluster1_apll_postdiv1  : 3;  /* bit[18-20]: APLL���ʱ�ӷ�Ƶ����1�� */
        unsigned int  cluster1_apll_postdiv2  : 3;  /* bit[21-23]: APLL���ʱ�ӷ�Ƶ����2�� */
        unsigned int  cluster1_apll_sw_target : 2;  /* bit[24-25]: APLL��תĿ�ꡣ */
        unsigned int  reserved                : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_cluster1_apll_refdiv_START     (0)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_cluster1_apll_refdiv_END       (5)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_cluster1_apll_fbdiv_START      (6)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_cluster1_apll_fbdiv_END        (17)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_cluster1_apll_postdiv1_START   (18)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_cluster1_apll_postdiv1_END     (20)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_cluster1_apll_postdiv2_START   (21)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_cluster1_apll_postdiv2_END     (23)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_cluster1_apll_sw_target_START  (24)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_cluster1_apll_sw_target_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_1_UNION
 �ṹ˵��  : CLUSTER1_CPUCLKPROFILE0_1 �Ĵ����ṹ���塣��ַƫ����:0x174����ֵ:0x02F80000�����:32
 �Ĵ���˵��: CLUSTER1_CPUƵ��Profile�Ĵ���0_1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_apll_fracdiv : 24; /* bit[0-23] : APLL����ʱ�ӷ�����Ƶ���� */
        unsigned int  cluster1_apll_int_mod : 1;  /* bit[24-24]: APLL������Ƶģʽ��
                                                                 0��������Ƶģʽ��
                                                                 1��������Ƶģʽ��
                                                                 ע�⣺��PLLҪ�����ֻʹ�÷�����Ƶģʽ */
        unsigned int  cluster1_apll_cfg_vld : 1;  /* bit[25-25]: APLL������Ч��־��
                                                                 0��������Ч��
                                                                 1��������Ч�� */
        unsigned int  reserved              : 6;  /* bit[26-31]: ���� */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_1_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_1_cluster1_apll_fracdiv_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_1_cluster1_apll_fracdiv_END    (23)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_1_cluster1_apll_int_mod_START  (24)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_1_cluster1_apll_int_mod_END    (24)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_1_cluster1_apll_cfg_vld_START  (25)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE0_1_cluster1_apll_cfg_vld_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE1_UNION
 �ṹ˵��  : CLUSTER1_CPUCLKPROFILE1 �Ĵ����ṹ���塣��ַƫ����:0x178����ֵ:0x000000A1�����:32
 �Ĵ���˵��: CLUSTER1_CPUƵ��Profile�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_pclkendbg_sel_prof : 2;  /* bit[0-1] : Cluster1_ DebugAPB�ӿ�ʱ��Ƶ�ʱ�ѡ��
                                                                      000:1:2�� 
                                                                      001:1:4�� 
                                                                      010:1:6�� 
                                                                      011:1:8�� */
        unsigned int  cluster1_atclken_sel_prof   : 2;  /* bit[2-3] : Cluster1_ ATB�ӿ�ʱ��Ƶ�ʱ�ѡ������� */
        unsigned int  cluster1_aclkenm_sel_prof   : 3;  /* bit[4-6] : Cluster1_ ACE master�ӿ�ʱ��Ƶ�ʱ�ѡ������� */
        unsigned int  cluster1_atclken_l_sel_prof : 1;  /* bit[7-7] : Cluster1_ traceʱ�Ӷ���Ƶ�ʱ�ѡ��
                                                                      0:1:2�� 
                                                                      1:1:4�� */
        unsigned int  reserved                    : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE1_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE1_cluster1_pclkendbg_sel_prof_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE1_cluster1_pclkendbg_sel_prof_END    (1)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE1_cluster1_atclken_sel_prof_START    (2)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE1_cluster1_atclken_sel_prof_END      (3)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE1_cluster1_aclkenm_sel_prof_START    (4)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE1_cluster1_aclkenm_sel_prof_END      (6)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE1_cluster1_atclken_l_sel_prof_START  (7)
#define SOC_PMCTRL_CLUSTER1_CPUCLKPROFILE1_cluster1_atclken_l_sel_prof_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUVOLMOD_UNION
 �ṹ˵��  : CLUSTER1_CPUVOLMOD �Ĵ����ṹ���塣��ַƫ����:0x17C����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU DVFSʱ�ĵ�ѹģʽ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu_vol_mod         : 1;  /* bit[0-0] : Cluster1_ DVFSʱ���Ƿ���Ҫ��ѹ��
                                                                       0��Cluster1_ DVFSʱ������Ҫ��ѹ��
                                                                       1��Cluster1_ DVFSʱ����Ҫ��ѹ�� */
        unsigned int  cluster1_cpu_clk_off_vol_mod : 1;  /* bit[1-1] : Cluster1_��ѹʱ��Cluster1_ʱ���Ƿ�رա�
                                                                       0��Cluster1_��ѹʱ��Cluster1_ʱ�ӱ��ִ򿪣�
                                                                       1��Cluster1_��ѹʱ��Cluster1_ʱ��Ҫ��رա� */
        unsigned int  reserved                     : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUVOLMOD_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUVOLMOD_cluster1_cpu_vol_mod_START          (0)
#define SOC_PMCTRL_CLUSTER1_CPUVOLMOD_cluster1_cpu_vol_mod_END            (0)
#define SOC_PMCTRL_CLUSTER1_CPUVOLMOD_cluster1_cpu_clk_off_vol_mod_START  (1)
#define SOC_PMCTRL_CLUSTER1_CPUVOLMOD_cluster1_cpu_clk_off_vol_mod_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUVOLPROFILE_UNION
 �ṹ˵��  : CLUSTER1_CPUVOLPROFILE �Ĵ����ṹ���塣��ַƫ����:0x180����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU��ѹProfile�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu_vol_idx : 8;  /* bit[0-7] : Cluster1_��ѹProfile������ */
        unsigned int  reserved             : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUVOLPROFILE_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUVOLPROFILE_cluster1_cpu_vol_idx_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPUVOLPROFILE_cluster1_cpu_vol_idx_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUPHASEMOD_UNION
 �ṹ˵��  : CLUSTER1_CPUPHASEMOD �Ĵ����ṹ���塣��ַƫ����:0x188����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU DVFSʱ����λģʽ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu_phase_mod         : 1;  /* bit[0-0] : Cluster1_ DVFSʱ���Ƿ�ı���λ��
                                                                         0��Cluster1_ DVFSʱ�����ı���λ��
                                                                         1��Cluster1_ DVFSʱ���ı���λ�� */
        unsigned int  cluster1_cpu_clk_off_phase_mod : 1;  /* bit[1-1] : Cluster1_ DVFS�ı���λʱ�Ƿ�ر�Cluster1_ʱ�ӡ�
                                                                         0��Cluster1_�ı���λʱ��Cluster1_ʱ�ӱ��ִ򿪣�
                                                                         1��Cluster1_�ı���λʱ��Cluster1_ʱ�ӹرա� */
        unsigned int  reserved                       : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUPHASEMOD_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUPHASEMOD_cluster1_cpu_phase_mod_START          (0)
#define SOC_PMCTRL_CLUSTER1_CPUPHASEMOD_cluster1_cpu_phase_mod_END            (0)
#define SOC_PMCTRL_CLUSTER1_CPUPHASEMOD_cluster1_cpu_clk_off_phase_mod_START  (1)
#define SOC_PMCTRL_CLUSTER1_CPUPHASEMOD_cluster1_cpu_clk_off_phase_mod_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUPHASEPROFILE_UNION
 �ṹ˵��  : CLUSTER1_CPUPHASEPROFILE �Ĵ����ṹ���塣��ַƫ����:0x18C����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU��λProfile�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu_phase_idx : 8;  /* bit[0-7] : Cluster1_��λProfile������ */
        unsigned int  reserved               : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUPHASEPROFILE_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUPHASEPROFILE_cluster1_cpu_phase_idx_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPUPHASEPROFILE_cluster1_cpu_phase_idx_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUVOLPHASESEL_UNION
 �ṹ˵��  : CLUSTER1_CPUVOLPHASESEL �Ĵ����ṹ���塣��ַƫ����:0x190����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU��ѹ/��λ����ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu_vol_phase_sel : 1;  /* bit[0-0] : Cluster1_��ѹ/��λ�ź����ѡ��
                                                                     0��DVFSʱ�ȵ���λ�ٵ���ѹ������profile�Ĵ���ʱ����Ҫ�ı䣻
                                                                     1��DVFS�ȵ���ѹ�ڵ���λ������profile�Ĵ���ʱ��Ҫ�ı䣨��ѹprofile�Ĵ���������λ����λprofile�Ĵ������Ƶ�ѹ���� */
        unsigned int  reserved                   : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUVOLPHASESEL_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUVOLPHASESEL_cluster1_cpu_vol_phase_sel_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPUVOLPHASESEL_cluster1_cpu_vol_phase_sel_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_VOLUPSTEPTIME_UNION
 �ṹ˵��  : CLUSTER1_VOLUPSTEPTIME �Ĵ����ṹ���塣��ַƫ����:0x194����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_��ѹ����һ���ȶ�����ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_vol_up_step_time : 13; /* bit[0-12] : Cluster1_ CPU��ѹ�����ȶ�����ʱ�䡣 */
        unsigned int  reserved                  : 19; /* bit[13-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_VOLUPSTEPTIME_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_VOLUPSTEPTIME_cluster1_vol_up_step_time_START  (0)
#define SOC_PMCTRL_CLUSTER1_VOLUPSTEPTIME_cluster1_vol_up_step_time_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_VOLDNSTEPTIME_UNION
 �ṹ˵��  : CLUSTER1_VOLDNSTEPTIME �Ĵ����ṹ���塣��ַƫ����:0x198����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_��ѹ�½�һ���ȶ�����ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_vol_dn_step_time : 13; /* bit[0-12] : Cluster1_ CPU��ѹ�½��ȶ�����ʱ�䡣 */
        unsigned int  reserved                  : 19; /* bit[13-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_VOLDNSTEPTIME_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_VOLDNSTEPTIME_cluster1_vol_dn_step_time_START  (0)
#define SOC_PMCTRL_CLUSTER1_VOLDNSTEPTIME_cluster1_vol_dn_step_time_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_PHASEUPTIME_UNION
 �ṹ˵��  : CLUSTER1_PHASEUPTIME �Ĵ����ṹ���塣��ַƫ����:0x19C����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_ DVFSʱ�ı��ѹ��λ�������ȶ�ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_dvfs_phase_up_time : 20; /* bit[0-19] : Cluster1_ DVFSʱ���ı��ѹ��λ�������ȶ�ʱ�䡣 */
        unsigned int  reserved                    : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_PHASEUPTIME_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_PHASEUPTIME_cluster1_dvfs_phase_up_time_START  (0)
#define SOC_PMCTRL_CLUSTER1_PHASEUPTIME_cluster1_dvfs_phase_up_time_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_PHASEDNTIME_UNION
 �ṹ˵��  : CLUSTER1_PHASEDNTIME �Ĵ����ṹ���塣��ַƫ����:0x1A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_ DVFSʱ�ı��ѹ��λ���½��ȶ�ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_dvfs_phase_dn_time : 20; /* bit[0-19] : Cluster1_ DVFSʱ���ı��ѹ��λ���½��ȶ�ʱ�䡣 */
        unsigned int  reserved                    : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_PHASEDNTIME_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_PHASEDNTIME_cluster1_dvfs_phase_dn_time_START  (0)
#define SOC_PMCTRL_CLUSTER1_PHASEDNTIME_cluster1_dvfs_phase_dn_time_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_PMUHOLDTIME_UNION
 �ṹ˵��  : CLUSTER1_PMUHOLDTIME �Ĵ����ṹ���塣��ַƫ����:0x1A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_��ѹ�ȶ�ʱ��ԣ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_pmu_vol_hold_time : 20; /* bit[0-19] : Cluster1_��ѹʱ�����ڶ˿ڴ���ʱ������ӵĵ�ѹ�ȶ�ʱ�䡣 */
        unsigned int  reserved                   : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_PMUHOLDTIME_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_PMUHOLDTIME_cluster1_pmu_vol_hold_time_START  (0)
#define SOC_PMCTRL_CLUSTER1_PMUHOLDTIME_cluster1_pmu_vol_hold_time_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_PMUSEL_UNION
 �ṹ˵��  : CLUSTER1_PMUSEL �Ĵ����ṹ���塣��ַƫ����:0x1A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_PMUѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_pmu_sel : 1;  /* bit[0-0] : Cluster1_���PMUѡ��
                                                           0��Cluster1_������źŸ�PMUSSI��
                                                           1��Cluster1_������źŸ�PMUI2C����ֻ�ܾ�̬���ã��� */
        unsigned int  reserved         : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_PMUSEL_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_PMUSEL_cluster1_pmu_sel_START  (0)
#define SOC_PMCTRL_CLUSTER1_PMUSEL_cluster1_pmu_sel_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUAVSEN_UNION
 �ṹ˵��  : CLUSTER1_CPUAVSEN �Ĵ����ṹ���塣��ַƫ����:0x1B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU AVSʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu_avs_en        : 1;  /* bit[0-0] : Cluster1_ AVSʹ�ܡ�
                                                                     0��Cluster1_ AVS���ܹرգ�
                                                                     1��Cluster1_ AVS���ܿ����� */
        unsigned int  cluster1_cpu_avs_pwctrl_en : 1;  /* bit[1-1] : Cluster1_ AVS��ѹʹ�ܡ�
                                                                     0��Cluster1_ AVS��ѹ���ܹرգ�
                                                                     1��Cluster1_ AVS��ѹ���ܿ����� */
        unsigned int  reserved                   : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUAVSEN_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUAVSEN_cluster1_cpu_avs_en_START         (0)
#define SOC_PMCTRL_CLUSTER1_CPUAVSEN_cluster1_cpu_avs_en_END           (0)
#define SOC_PMCTRL_CLUSTER1_CPUAVSEN_cluster1_cpu_avs_pwctrl_en_START  (1)
#define SOC_PMCTRL_CLUSTER1_CPUAVSEN_cluster1_cpu_avs_pwctrl_en_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUAVSPARAMOD_UNION
 �ṹ˵��  : CLUSTER1_CPUAVSPARAMOD �Ĵ����ṹ���塣��ַƫ����:0x1B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU AVS����ģʽ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu_avspara_mod : 1;  /* bit[0-0] : Cluster1_ AVS����ʵʱ���¿��ơ�
                                                                   ͨ����Cluster1_ AVS������Cluster1_ DVFS����֮����£����������Ĵ���д1��AVS�����������£����������Ĵ���д0����Ч�� */
        unsigned int  reserved                 : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUAVSPARAMOD_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARAMOD_cluster1_cpu_avspara_mod_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARAMOD_cluster1_cpu_avspara_mod_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUAVSPARA0_UNION
 �ṹ˵��  : CLUSTER1_CPUAVSPARA0 �Ĵ����ṹ���塣��ַƫ����:0x1B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU AVS�����Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                  : 2;  /* bit[0-1]  : ������ */
        unsigned int  cluster1_cpu_avs_opc_offset : 10; /* bit[2-11] : Cluster1_ AVSԭʼ������ƫ�ơ� */
        unsigned int  cluster1_cpu_avs_rcc        : 5;  /* bit[12-16]: Cluster1_ AVS�ο�У׼�롣 */
        unsigned int  cluster1_cpu_avs_irgap      : 5;  /* bit[17-21]: Cluster1_ AVS IRDropԣ���� */
        unsigned int  cluster1_cpu_avs_opc_mod    : 2;  /* bit[22-23]: Cluster1_ AVS��ͬһ��HPM OPCֵ�Ķ�β�����δ���
                                                                       00��OPCȡ��ֵ��
                                                                       01��OPCȡ��Сֵ��
                                                                       10��OPCȡ���ֵ��
                                                                       11�������� */
        unsigned int  cluster1_cpu_avs_hpm_sel    : 4;  /* bit[24-27]: Cluster1_ AVS�ж��HPM��PCֵ��δ���
                                                                       0000��ȡCPU0 HPM��PCֵ��
                                                                       0001��ȡCPU1 HPM��PCֵ��
                                                                       0010��ȡCPU2 HPM��PCֵ��
                                                                       0011��ȡCPU3 HPM��PCֵ��
                                                                       0100��ȡSCU0 HPM��PCֵ��
                                                                       0101��reserved��
                                                                       0110��reserved��
                                                                       0111��reserved��
                                                                       1000��reserved��
                                                                       1001��reserved��
                                                                       1010��ȡHPM�е���Сֵ��
                                                                       ������ȡHPM�е����ֵ�� */
        unsigned int  cluster1_cpu_avs_opc_shift  : 3;  /* bit[28-30]: Cluster1_ AVSԭʼ��������λ�� */
        unsigned int  reserved_1                  : 1;  /* bit[31-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUAVSPARA0_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA0_cluster1_cpu_avs_opc_offset_START  (2)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA0_cluster1_cpu_avs_opc_offset_END    (11)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA0_cluster1_cpu_avs_rcc_START         (12)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA0_cluster1_cpu_avs_rcc_END           (16)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA0_cluster1_cpu_avs_irgap_START       (17)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA0_cluster1_cpu_avs_irgap_END         (21)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA0_cluster1_cpu_avs_opc_mod_START     (22)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA0_cluster1_cpu_avs_opc_mod_END       (23)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA0_cluster1_cpu_avs_hpm_sel_START     (24)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA0_cluster1_cpu_avs_hpm_sel_END       (27)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA0_cluster1_cpu_avs_opc_shift_START   (28)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA0_cluster1_cpu_avs_opc_shift_END     (30)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUAVSPARA1_UNION
 �ṹ˵��  : CLUSTER1_CPUAVSPARA1 �Ĵ����ṹ���塣��ַƫ����:0x1BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU AVS�����Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu_avs_vol_up_gain1 : 4;  /* bit[0-3]  : Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_up_gain2 : 4;  /* bit[4-7]  : Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_up_gain3 : 4;  /* bit[8-11] : Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_up_gain4 : 4;  /* bit[12-15]: Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_up_gain5 : 4;  /* bit[16-19]: Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_up_gain6 : 4;  /* bit[20-23]: Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_up_gain7 : 4;  /* bit[24-27]: Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_up_gain8 : 4;  /* bit[28-31]: Cluster1_ AVS��ѹ���档 */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUAVSPARA1_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA1_cluster1_cpu_avs_vol_up_gain1_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA1_cluster1_cpu_avs_vol_up_gain1_END    (3)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA1_cluster1_cpu_avs_vol_up_gain2_START  (4)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA1_cluster1_cpu_avs_vol_up_gain2_END    (7)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA1_cluster1_cpu_avs_vol_up_gain3_START  (8)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA1_cluster1_cpu_avs_vol_up_gain3_END    (11)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA1_cluster1_cpu_avs_vol_up_gain4_START  (12)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA1_cluster1_cpu_avs_vol_up_gain4_END    (15)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA1_cluster1_cpu_avs_vol_up_gain5_START  (16)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA1_cluster1_cpu_avs_vol_up_gain5_END    (19)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA1_cluster1_cpu_avs_vol_up_gain6_START  (20)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA1_cluster1_cpu_avs_vol_up_gain6_END    (23)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA1_cluster1_cpu_avs_vol_up_gain7_START  (24)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA1_cluster1_cpu_avs_vol_up_gain7_END    (27)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA1_cluster1_cpu_avs_vol_up_gain8_START  (28)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA1_cluster1_cpu_avs_vol_up_gain8_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUAVSPARA2_UNION
 �ṹ˵��  : CLUSTER1_CPUAVSPARA2 �Ĵ����ṹ���塣��ַƫ����:0x1C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU AVS�����Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu_avs_vol_up_gain9  : 4;  /* bit[0-3]  : Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_up_gain10 : 4;  /* bit[4-7]  : Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_up_gain11 : 4;  /* bit[8-11] : Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_up_gain12 : 4;  /* bit[12-15]: Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_up_gain13 : 4;  /* bit[16-19]: Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_up_gain14 : 4;  /* bit[20-23]: Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_up_gain15 : 7;  /* bit[24-30]: Cluster1_ AVS��ѹ���档 */
        unsigned int  reserved                       : 1;  /* bit[31-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUAVSPARA2_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA2_cluster1_cpu_avs_vol_up_gain9_START   (0)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA2_cluster1_cpu_avs_vol_up_gain9_END     (3)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA2_cluster1_cpu_avs_vol_up_gain10_START  (4)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA2_cluster1_cpu_avs_vol_up_gain10_END    (7)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA2_cluster1_cpu_avs_vol_up_gain11_START  (8)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA2_cluster1_cpu_avs_vol_up_gain11_END    (11)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA2_cluster1_cpu_avs_vol_up_gain12_START  (12)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA2_cluster1_cpu_avs_vol_up_gain12_END    (15)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA2_cluster1_cpu_avs_vol_up_gain13_START  (16)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA2_cluster1_cpu_avs_vol_up_gain13_END    (19)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA2_cluster1_cpu_avs_vol_up_gain14_START  (20)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA2_cluster1_cpu_avs_vol_up_gain14_END    (23)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA2_cluster1_cpu_avs_vol_up_gain15_START  (24)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA2_cluster1_cpu_avs_vol_up_gain15_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUAVSPARA3_UNION
 �ṹ˵��  : CLUSTER1_CPUAVSPARA3 �Ĵ����ṹ���塣��ַƫ����:0x1C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU AVS�����Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu_avs_vol_dn_gain1 : 4;  /* bit[0-3]  : Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_dn_gain2 : 4;  /* bit[4-7]  : Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_dn_gain3 : 4;  /* bit[8-11] : Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_dn_gain4 : 4;  /* bit[12-15]: Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_dn_gain5 : 4;  /* bit[16-19]: Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_dn_gain6 : 4;  /* bit[20-23]: Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_dn_gain7 : 4;  /* bit[24-27]: Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_dn_gain8 : 4;  /* bit[28-31]: Cluster1_ AVS��ѹ���档 */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUAVSPARA3_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA3_cluster1_cpu_avs_vol_dn_gain1_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA3_cluster1_cpu_avs_vol_dn_gain1_END    (3)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA3_cluster1_cpu_avs_vol_dn_gain2_START  (4)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA3_cluster1_cpu_avs_vol_dn_gain2_END    (7)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA3_cluster1_cpu_avs_vol_dn_gain3_START  (8)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA3_cluster1_cpu_avs_vol_dn_gain3_END    (11)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA3_cluster1_cpu_avs_vol_dn_gain4_START  (12)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA3_cluster1_cpu_avs_vol_dn_gain4_END    (15)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA3_cluster1_cpu_avs_vol_dn_gain5_START  (16)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA3_cluster1_cpu_avs_vol_dn_gain5_END    (19)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA3_cluster1_cpu_avs_vol_dn_gain6_START  (20)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA3_cluster1_cpu_avs_vol_dn_gain6_END    (23)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA3_cluster1_cpu_avs_vol_dn_gain7_START  (24)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA3_cluster1_cpu_avs_vol_dn_gain7_END    (27)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA3_cluster1_cpu_avs_vol_dn_gain8_START  (28)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA3_cluster1_cpu_avs_vol_dn_gain8_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUAVSPARA4_UNION
 �ṹ˵��  : CLUSTER1_CPUAVSPARA4 �Ĵ����ṹ���塣��ַƫ����:0x1C8����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU AVS�����Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu_avs_vol_dn_gain9  : 4;  /* bit[0-3]  : Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_dn_gain10 : 4;  /* bit[4-7]  : Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_dn_gain11 : 4;  /* bit[8-11] : Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_dn_gain12 : 4;  /* bit[12-15]: Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_dn_gain13 : 4;  /* bit[16-19]: Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_dn_gain14 : 4;  /* bit[20-23]: Cluster1_ AVS��ѹ���档 */
        unsigned int  cluster1_cpu_avs_vol_dn_gain15 : 7;  /* bit[24-30]: Cluster1_ AVS��ѹ���档 */
        unsigned int  reserved                       : 1;  /* bit[31-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUAVSPARA4_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA4_cluster1_cpu_avs_vol_dn_gain9_START   (0)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA4_cluster1_cpu_avs_vol_dn_gain9_END     (3)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA4_cluster1_cpu_avs_vol_dn_gain10_START  (4)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA4_cluster1_cpu_avs_vol_dn_gain10_END    (7)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA4_cluster1_cpu_avs_vol_dn_gain11_START  (8)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA4_cluster1_cpu_avs_vol_dn_gain11_END    (11)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA4_cluster1_cpu_avs_vol_dn_gain12_START  (12)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA4_cluster1_cpu_avs_vol_dn_gain12_END    (15)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA4_cluster1_cpu_avs_vol_dn_gain13_START  (16)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA4_cluster1_cpu_avs_vol_dn_gain13_END    (19)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA4_cluster1_cpu_avs_vol_dn_gain14_START  (20)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA4_cluster1_cpu_avs_vol_dn_gain14_END    (23)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA4_cluster1_cpu_avs_vol_dn_gain15_START  (24)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA4_cluster1_cpu_avs_vol_dn_gain15_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUAVSPARA5_UNION
 �ṹ˵��  : CLUSTER1_CPUAVSPARA5 �Ĵ����ṹ���塣��ַƫ����:0x1CC����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU AVS�����Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu_avs_max_vol : 7;  /* bit[0-6]  : Cluster1_ AVS����ѹ���ơ� */
        unsigned int  cluster1_cpu_avs_min_vol : 7;  /* bit[7-13] : Cluster1_ AVS��С��ѹ���ơ� */
        unsigned int  reserved                 : 18; /* bit[14-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUAVSPARA5_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA5_cluster1_cpu_avs_max_vol_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA5_cluster1_cpu_avs_max_vol_END    (6)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA5_cluster1_cpu_avs_min_vol_START  (7)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA5_cluster1_cpu_avs_min_vol_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUAVSPARA6_UNION
 �ṹ˵��  : CLUSTER1_CPUAVSPARA6 �Ĵ����ṹ���塣��ַƫ����:0x1D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU AVSʹ�ܼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu_avs_sample_num : 22; /* bit[0-21] : Cluster1_ AVS�������������������ֵ������2��N�η��� */
        unsigned int  reserved                    : 10; /* bit[22-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUAVSPARA6_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA6_cluster1_cpu_avs_sample_num_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPUAVSPARA6_cluster1_cpu_avs_sample_num_END    (21)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUHPMTYP_UNION
 �ṹ˵��  : CLUSTER1_CPUHPMTYP �Ĵ����ṹ���塣��ַƫ����:0x1D4����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU01 HPM����ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu_hpm_type  : 1;  /* bit[0-0]  : AVSѡ��ʹ��CPU HPM���͡�
                                                                  0��AVSѡ��ʹ�ñ�׼HPM��
                                                                  1��AVSѡ��ʹ��X��HPM�� */
        unsigned int  cluster1_cpu0_hpm_mask : 1;  /* bit[1-1]  : AVS�����Ƿ�����CPU0 HPM��
                                                                  0�������Σ�
                                                                  1�����Ρ� */
        unsigned int  cluster1_cpu1_hpm_mask : 1;  /* bit[2-2]  : AVS�����Ƿ�����CPU1 HPM��
                                                                  0�������Σ�
                                                                  1�����Ρ� */
        unsigned int  cluster1_cpu2_hpm_mask : 1;  /* bit[3-3]  : AVS�����Ƿ�����CPU2 HPM��
                                                                  0�������Σ�
                                                                  1�����Ρ� */
        unsigned int  cluster1_cpu3_hpm_mask : 1;  /* bit[4-4]  : AVS�����Ƿ�����CPU3 HPM��
                                                                  0�������Σ�
                                                                  1�����Ρ� */
        unsigned int  cluster1_scu_hpm_mask  : 1;  /* bit[5-5]  : AVS�����Ƿ�����SCU HPM��
                                                                  0�������Σ�
                                                                  1�����Ρ� */
        unsigned int  reserved               : 10; /* bit[6-15] : ������ */
        unsigned int  biten                  : 16; /* bit[16-31]: ÿ������λ��ʹ��λ��
                                                                  ֻ�е�biten��Ӧ�ı���λΪ1'b1����Ӧ�ı���λ�������á�biten[0]����bit 0��ʹ��λ��д1��Ч�� */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUHPMTYP_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUHPMTYP_cluster1_cpu_hpm_type_START   (0)
#define SOC_PMCTRL_CLUSTER1_CPUHPMTYP_cluster1_cpu_hpm_type_END     (0)
#define SOC_PMCTRL_CLUSTER1_CPUHPMTYP_cluster1_cpu0_hpm_mask_START  (1)
#define SOC_PMCTRL_CLUSTER1_CPUHPMTYP_cluster1_cpu0_hpm_mask_END    (1)
#define SOC_PMCTRL_CLUSTER1_CPUHPMTYP_cluster1_cpu1_hpm_mask_START  (2)
#define SOC_PMCTRL_CLUSTER1_CPUHPMTYP_cluster1_cpu1_hpm_mask_END    (2)
#define SOC_PMCTRL_CLUSTER1_CPUHPMTYP_cluster1_cpu2_hpm_mask_START  (3)
#define SOC_PMCTRL_CLUSTER1_CPUHPMTYP_cluster1_cpu2_hpm_mask_END    (3)
#define SOC_PMCTRL_CLUSTER1_CPUHPMTYP_cluster1_cpu3_hpm_mask_START  (4)
#define SOC_PMCTRL_CLUSTER1_CPUHPMTYP_cluster1_cpu3_hpm_mask_END    (4)
#define SOC_PMCTRL_CLUSTER1_CPUHPMTYP_cluster1_scu_hpm_mask_START   (5)
#define SOC_PMCTRL_CLUSTER1_CPUHPMTYP_cluster1_scu_hpm_mask_END     (5)
#define SOC_PMCTRL_CLUSTER1_CPUHPMTYP_biten_START                   (16)
#define SOC_PMCTRL_CLUSTER1_CPUHPMTYP_biten_END                     (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPU01HPMEN_UNION
 �ṹ˵��  : CLUSTER1_CPU01HPMEN �Ĵ����ṹ���塣��ַƫ����:0x1D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU01 HPMʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu0_hpm_en_cfg  : 1;  /* bit[0-0] : CPU0 HPMʹ�ܡ�
                                                                    HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster1_cpu1_hpm_en_cfg  : 1;  /* bit[1-1] : CPU1 HPMʹ�ܡ�
                                                                    HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster1_scu_hpm_en_cfg   : 1;  /* bit[2-2] : SCU HPMʹ�ܡ�
                                                                    HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_0                : 1;  /* bit[3-3] : ������ */
        unsigned int  cluster1_cpu0_hpm_en_stat : 1;  /* bit[4-4] : CPU0 HPMʹ�ܡ�
                                                                    HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster1_cpu1_hpm_en_stat : 1;  /* bit[5-5] : CPU1 HPMʹ�ܡ�
                                                                    HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster1_scu_hpm_en_stat  : 1;  /* bit[6-6] : SCU HPMʹ�ܡ�
                                                                    HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_1                : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPU01HPMEN_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPU01HPMEN_cluster1_cpu0_hpm_en_cfg_START   (0)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMEN_cluster1_cpu0_hpm_en_cfg_END     (0)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMEN_cluster1_cpu1_hpm_en_cfg_START   (1)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMEN_cluster1_cpu1_hpm_en_cfg_END     (1)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMEN_cluster1_scu_hpm_en_cfg_START    (2)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMEN_cluster1_scu_hpm_en_cfg_END      (2)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMEN_cluster1_cpu0_hpm_en_stat_START  (4)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMEN_cluster1_cpu0_hpm_en_stat_END    (4)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMEN_cluster1_cpu1_hpm_en_stat_START  (5)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMEN_cluster1_cpu1_hpm_en_stat_END    (5)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMEN_cluster1_scu_hpm_en_stat_START   (6)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMEN_cluster1_scu_hpm_en_stat_END     (6)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPU01HPMXEN_UNION
 �ṹ˵��  : CLUSTER1_CPU01HPMXEN �Ĵ����ṹ���塣��ַƫ����:0x1DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU01 HPMXʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu0_hpmx_en_cfg  : 1;  /* bit[0-0] : CPU0 HPMXʹ�ܡ�
                                                                     HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster1_cpu1_hpmx_en_cfg  : 1;  /* bit[1-1] : CPU1 HPMXʹ�ܡ�
                                                                     HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster1_scu_hpmx_en_cfg   : 1;  /* bit[2-2] : SCU HPMXʹ�ܡ�
                                                                     HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_0                 : 1;  /* bit[3-3] : ������ */
        unsigned int  cluster1_cpu0_hpmx_en_stat : 1;  /* bit[4-4] : CPU0 HPMXʹ�ܡ�
                                                                     HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster1_cpu1_hpmx_en_stat : 1;  /* bit[5-5] : CPU1 HPMXʹ�ܡ�
                                                                     HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster1_scu_hpmx_en_stat  : 1;  /* bit[6-6] : SCU HPMXʹ�ܡ�
                                                                     HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_1                 : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPU01HPMXEN_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPU01HPMXEN_cluster1_cpu0_hpmx_en_cfg_START   (0)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMXEN_cluster1_cpu0_hpmx_en_cfg_END     (0)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMXEN_cluster1_cpu1_hpmx_en_cfg_START   (1)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMXEN_cluster1_cpu1_hpmx_en_cfg_END     (1)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMXEN_cluster1_scu_hpmx_en_cfg_START    (2)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMXEN_cluster1_scu_hpmx_en_cfg_END      (2)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMXEN_cluster1_cpu0_hpmx_en_stat_START  (4)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMXEN_cluster1_cpu0_hpmx_en_stat_END    (4)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMXEN_cluster1_cpu1_hpmx_en_stat_START  (5)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMXEN_cluster1_cpu1_hpmx_en_stat_END    (5)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMXEN_cluster1_scu_hpmx_en_stat_START   (6)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMXEN_cluster1_scu_hpmx_en_stat_END     (6)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPU01HPMOPCVALID_UNION
 �ṹ˵��  : CLUSTER1_CPU01HPMOPCVALID �Ĵ����ṹ���塣��ַƫ����:0x1E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU01 HPM OPC��Ч�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu0_hpm_opc_vld  : 1;  /* bit[0-0] : CPU0 HPMԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  cluster1_cpu1_hpm_opc_vld  : 1;  /* bit[1-1] : CPU1 HPMԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  cluster1_scu_hpm_opc_vld   : 1;  /* bit[2-2] : SCU HPMԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  cluster1_cpu0_hpmx_opc_vld : 1;  /* bit[3-3] : CPU0 HPMXԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  cluster1_cpu1_hpmx_opc_vld : 1;  /* bit[4-4] : CPU1 HPMXԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  cluster1_scu_hpmx_opc_vld  : 1;  /* bit[5-5] : SCU HPMXԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  reserved                   : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPU01HPMOPCVALID_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPU01HPMOPCVALID_cluster1_cpu0_hpm_opc_vld_START   (0)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMOPCVALID_cluster1_cpu0_hpm_opc_vld_END     (0)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMOPCVALID_cluster1_cpu1_hpm_opc_vld_START   (1)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMOPCVALID_cluster1_cpu1_hpm_opc_vld_END     (1)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMOPCVALID_cluster1_scu_hpm_opc_vld_START    (2)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMOPCVALID_cluster1_scu_hpm_opc_vld_END      (2)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMOPCVALID_cluster1_cpu0_hpmx_opc_vld_START  (3)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMOPCVALID_cluster1_cpu0_hpmx_opc_vld_END    (3)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMOPCVALID_cluster1_cpu1_hpmx_opc_vld_START  (4)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMOPCVALID_cluster1_cpu1_hpmx_opc_vld_END    (4)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMOPCVALID_cluster1_scu_hpmx_opc_vld_START   (5)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMOPCVALID_cluster1_scu_hpmx_opc_vld_END     (5)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPU01HPMOPC_UNION
 �ṹ˵��  : CLUSTER1_CPU01HPMOPC �Ĵ����ṹ���塣��ַƫ����:0x1E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU01 HPM OPC�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu0_hpm_opc : 10; /* bit[0-9]  : CPU0 HPMԭʼ�����롣 */
        unsigned int  cluster1_cpu1_hpm_opc : 10; /* bit[10-19]: CPU1 HPMԭʼ�����롣 */
        unsigned int  cluster1_scu_hpm_opc  : 10; /* bit[20-29]: SCU HPMԭʼ�����롣 */
        unsigned int  reserved              : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPU01HPMOPC_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPU01HPMOPC_cluster1_cpu0_hpm_opc_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMOPC_cluster1_cpu0_hpm_opc_END    (9)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMOPC_cluster1_cpu1_hpm_opc_START  (10)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMOPC_cluster1_cpu1_hpm_opc_END    (19)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMOPC_cluster1_scu_hpm_opc_START   (20)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMOPC_cluster1_scu_hpm_opc_END     (29)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPU01HPMXOPC_UNION
 �ṹ˵��  : CLUSTER1_CPU01HPMXOPC �Ĵ����ṹ���塣��ַƫ����:0x1E8����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU01 HPMX OPC�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu0_hpmx_opc : 10; /* bit[0-9]  : CPU0 HPMXԭʼ�����롣 */
        unsigned int  cluster1_cpu1_hpmx_opc : 10; /* bit[10-19]: CPU1 HPMXԭʼ�����롣 */
        unsigned int  cluster1_scu_hpmx_opc  : 10; /* bit[20-29]: SCU HPMXԭʼ�����롣 */
        unsigned int  reserved               : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPU01HPMXOPC_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPU01HPMXOPC_cluster1_cpu0_hpmx_opc_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMXOPC_cluster1_cpu0_hpmx_opc_END    (9)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMXOPC_cluster1_cpu1_hpmx_opc_START  (10)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMXOPC_cluster1_cpu1_hpmx_opc_END    (19)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMXOPC_cluster1_scu_hpmx_opc_START   (20)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMXOPC_cluster1_scu_hpmx_opc_END     (29)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPU01HPMPC_UNION
 �ṹ˵��  : CLUSTER1_CPU01HPMPC �Ĵ����ṹ���塣��ַƫ����:0x1EC����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU HPM PC�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu0_hpm_pc_avs : 10; /* bit[0-9]  : CPU0 HPM�����롣 */
        unsigned int  cluster1_cpu1_hpm_pc_avs : 10; /* bit[10-19]: CPU1 HPM�����롣 */
        unsigned int  cluster1_scu_hpm_pc_avs  : 10; /* bit[20-29]: SCU HPM�����롣 */
        unsigned int  reserved                 : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPU01HPMPC_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPU01HPMPC_cluster1_cpu0_hpm_pc_avs_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMPC_cluster1_cpu0_hpm_pc_avs_END    (9)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMPC_cluster1_cpu1_hpm_pc_avs_START  (10)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMPC_cluster1_cpu1_hpm_pc_avs_END    (19)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMPC_cluster1_scu_hpm_pc_avs_START   (20)
#define SOC_PMCTRL_CLUSTER1_CPU01HPMPC_cluster1_scu_hpm_pc_avs_END     (29)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPU23HPMEN_UNION
 �ṹ˵��  : CLUSTER1_CPU23HPMEN �Ĵ����ṹ���塣��ַƫ����:0x1F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU23 HPMʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu2_hpm_en_cfg  : 1;  /* bit[0-0] : CPU2 HPMʹ�ܡ�
                                                                    HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster1_cpu3_hpm_en_cfg  : 1;  /* bit[1-1] : CPU3 HPMʹ�ܡ�
                                                                    HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_0                : 1;  /* bit[2-2] : ������ */
        unsigned int  reserved_1                : 1;  /* bit[3-3] : ������ */
        unsigned int  cluster1_cpu2_hpm_en_stat : 1;  /* bit[4-4] : CPU2 HPMʹ�ܡ�
                                                                    HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster1_cpu3_hpm_en_stat : 1;  /* bit[5-5] : CPU3 HPMʹ�ܡ�
                                                                    HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_2                : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPU23HPMEN_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPU23HPMEN_cluster1_cpu2_hpm_en_cfg_START   (0)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMEN_cluster1_cpu2_hpm_en_cfg_END     (0)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMEN_cluster1_cpu3_hpm_en_cfg_START   (1)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMEN_cluster1_cpu3_hpm_en_cfg_END     (1)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMEN_cluster1_cpu2_hpm_en_stat_START  (4)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMEN_cluster1_cpu2_hpm_en_stat_END    (4)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMEN_cluster1_cpu3_hpm_en_stat_START  (5)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMEN_cluster1_cpu3_hpm_en_stat_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPU23HPMXEN_UNION
 �ṹ˵��  : CLUSTER1_CPU23HPMXEN �Ĵ����ṹ���塣��ַƫ����:0x1F8����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU23 HPMXʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu2_hpmx_en_cfg  : 1;  /* bit[0-0] : CPU2 HPMXʹ�ܡ�
                                                                     HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster1_cpu3_hpmx_en_cfg  : 1;  /* bit[1-1] : CPU3 HPMXʹ�ܡ�
                                                                     HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_0                 : 1;  /* bit[2-2] : ������ */
        unsigned int  reserved_1                 : 1;  /* bit[3-3] : ������ */
        unsigned int  cluster1_cpu2_hpmx_en_stat : 1;  /* bit[4-4] : CPU2 HPMXʹ�ܡ�
                                                                     HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  cluster1_cpu3_hpmx_en_stat : 1;  /* bit[5-5] : CPU3 HPMXʹ�ܡ�
                                                                     HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_2                 : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPU23HPMXEN_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPU23HPMXEN_cluster1_cpu2_hpmx_en_cfg_START   (0)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMXEN_cluster1_cpu2_hpmx_en_cfg_END     (0)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMXEN_cluster1_cpu3_hpmx_en_cfg_START   (1)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMXEN_cluster1_cpu3_hpmx_en_cfg_END     (1)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMXEN_cluster1_cpu2_hpmx_en_stat_START  (4)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMXEN_cluster1_cpu2_hpmx_en_stat_END    (4)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMXEN_cluster1_cpu3_hpmx_en_stat_START  (5)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMXEN_cluster1_cpu3_hpmx_en_stat_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPU23HPMOPCVALID_UNION
 �ṹ˵��  : CLUSTER1_CPU23HPMOPCVALID �Ĵ����ṹ���塣��ַƫ����:0x1FC����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU23 HPM OPC��Ч�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu2_hpm_opc_vld  : 1;  /* bit[0-0] : CPU2 HPMԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  cluster1_cpu3_hpm_opc_vld  : 1;  /* bit[1-1] : CPU3 HPMԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  cluster1_cpu2_hpmx_opc_vld : 1;  /* bit[2-2] : CPU2 HPMXԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  cluster1_cpu3_hpmx_opc_vld : 1;  /* bit[3-3] : CPU3 HPMXԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  reserved                   : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPU23HPMOPCVALID_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPU23HPMOPCVALID_cluster1_cpu2_hpm_opc_vld_START   (0)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMOPCVALID_cluster1_cpu2_hpm_opc_vld_END     (0)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMOPCVALID_cluster1_cpu3_hpm_opc_vld_START   (1)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMOPCVALID_cluster1_cpu3_hpm_opc_vld_END     (1)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMOPCVALID_cluster1_cpu2_hpmx_opc_vld_START  (2)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMOPCVALID_cluster1_cpu2_hpmx_opc_vld_END    (2)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMOPCVALID_cluster1_cpu3_hpmx_opc_vld_START  (3)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMOPCVALID_cluster1_cpu3_hpmx_opc_vld_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPU23HPMOPC_UNION
 �ṹ˵��  : CLUSTER1_CPU23HPMOPC �Ĵ����ṹ���塣��ַƫ����:0x200����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU23 HPM OPC�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu2_hpm_opc : 10; /* bit[0-9]  : CPU2 HPMԭʼ�����롣 */
        unsigned int  cluster1_cpu3_hpm_opc : 10; /* bit[10-19]: CPU3 HPMԭʼ�����롣 */
        unsigned int  reserved              : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPU23HPMOPC_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPU23HPMOPC_cluster1_cpu2_hpm_opc_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMOPC_cluster1_cpu2_hpm_opc_END    (9)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMOPC_cluster1_cpu3_hpm_opc_START  (10)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMOPC_cluster1_cpu3_hpm_opc_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPU23HPMXOPC_UNION
 �ṹ˵��  : CLUSTER1_CPU23HPMXOPC �Ĵ����ṹ���塣��ַƫ����:0x204����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU23 HPMX OPC�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu2_hpmx_opc : 10; /* bit[0-9]  : CPU2 HPMXԭʼ�����롣 */
        unsigned int  cluster1_cpu3_hpmx_opc : 10; /* bit[10-19]: CPU3 HPMXԭʼ�����롣 */
        unsigned int  reserved               : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPU23HPMXOPC_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPU23HPMXOPC_cluster1_cpu2_hpmx_opc_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMXOPC_cluster1_cpu2_hpmx_opc_END    (9)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMXOPC_cluster1_cpu3_hpmx_opc_START  (10)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMXOPC_cluster1_cpu3_hpmx_opc_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPU23HPMPC_UNION
 �ṹ˵��  : CLUSTER1_CPU23HPMPC �Ĵ����ṹ���塣��ַƫ����:0x208����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU HPM PC�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu2_hpm_pc_avs : 10; /* bit[0-9]  : CPU2 HPM�����롣 */
        unsigned int  cluster1_cpu3_hpm_pc_avs : 10; /* bit[10-19]: CPU3 HPM�����롣 */
        unsigned int  reserved                 : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPU23HPMPC_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPU23HPMPC_cluster1_cpu2_hpm_pc_avs_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMPC_cluster1_cpu2_hpm_pc_avs_END    (9)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMPC_cluster1_cpu3_hpm_pc_avs_START  (10)
#define SOC_PMCTRL_CLUSTER1_CPU23HPMPC_cluster1_cpu3_hpm_pc_avs_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUHPMCLKDIV_UNION
 �ṹ˵��  : CLUSTER1_CPUHPMCLKDIV �Ĵ����ṹ���塣��ַƫ����:0x210����ֵ:0x00000001�����:32
 �Ĵ���˵��: CLUSTER1_CPU HPMʱ�ӷ�Ƶ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu_avs_hpm_div : 6;  /* bit[0-5] : Cluster1 HPMʱ�ӷ�Ƶ���� */
        unsigned int  reserved                 : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUHPMCLKDIV_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUHPMCLKDIV_cluster1_cpu_avs_hpm_div_START  (0)
#define SOC_PMCTRL_CLUSTER1_CPUHPMCLKDIV_cluster1_cpu_avs_hpm_div_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_CLUSTER1_CPUAVSVOLIDX_UNION
 �ṹ˵��  : CLUSTER1_CPUAVSVOLIDX �Ĵ����ṹ���塣��ַƫ����:0x214����ֵ:0x00000000�����:32
 �Ĵ���˵��: CLUSTER1_CPU AVS��ѹ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpu_avs_vol_idx_cfg  : 8;  /* bit[0-7]  : Cluster1 AVS��ǰ��ѹֵ����ֵ����ͨ����������øüĴ���ʱbit 8��д1������Ҫ�üĴ���ֵ��PMU��ѹֵ��ͬ�� */
        unsigned int  cluster1_cpu_vol_chg_sftreq   : 1;  /* bit[8-8]  : Cluster1 CPU��ѹ�ı���������źš�
                                                                         д1������ı��ѹ����ѹֵΪbit 7:0ֵ
                                                                         д0����Ч���� */
        unsigned int  reserved_0                    : 3;  /* bit[9-11] :  */
        unsigned int  cluster1_cpu_avs_vol_idx_stat : 8;  /* bit[12-19]: Cluster1 AVS��ǰ��ѹֵ����ֵ����ͨ����������øüĴ���ʱbit 8��д1������Ҫ�üĴ���ֵ��PMU��ѹֵ��ͬ�� */
        unsigned int  reserved_1                    : 12; /* bit[20-31]: ���� */
    } reg;
} SOC_PMCTRL_CLUSTER1_CPUAVSVOLIDX_UNION;
#endif
#define SOC_PMCTRL_CLUSTER1_CPUAVSVOLIDX_cluster1_cpu_avs_vol_idx_cfg_START   (0)
#define SOC_PMCTRL_CLUSTER1_CPUAVSVOLIDX_cluster1_cpu_avs_vol_idx_cfg_END     (7)
#define SOC_PMCTRL_CLUSTER1_CPUAVSVOLIDX_cluster1_cpu_vol_chg_sftreq_START    (8)
#define SOC_PMCTRL_CLUSTER1_CPUAVSVOLIDX_cluster1_cpu_vol_chg_sftreq_END      (8)
#define SOC_PMCTRL_CLUSTER1_CPUAVSVOLIDX_cluster1_cpu_avs_vol_idx_stat_START  (12)
#define SOC_PMCTRL_CLUSTER1_CPUAVSVOLIDX_cluster1_cpu_avs_vol_idx_stat_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DCLKSEL_UNION
 �ṹ˵��  : G3DCLKSEL �Ĵ����ṹ���塣��ַƫ����:0x220����ֵ:0x00000013�����:32
 �Ĵ���˵��: G3D AXIʱ��ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3da_sw_cfg  : 1;  /* bit[0-0] : G3D AXIʱ��ѡ����·ʱ�ӡ�
                                                       0��G3D AXIʱ����0·ʱ��������
                                                       1��G3D AXIʱ����1·ʱ�������� */
        unsigned int  g3da_sw_ack  : 1;  /* bit[1-1] : ��ǰG3D AXIʱ��ѡ����·ʱ�ӵ�״ָ̬ʾ��
                                                       0��G3D AXIʱ����0·ʱ��������
                                                       1��G3D AXIʱ����1·ʱ�������� */
        unsigned int  reserved_0   : 1;  /* bit[2-2] : ������ */
        unsigned int  reserved_1   : 1;  /* bit[3-3] : ������ */
        unsigned int  g3da_sw_stat : 1;  /* bit[4-4] : G3D AXIʱ��ѡ����·ʱ�ӡ�
                                                       0��G3D AXIʱ����0·ʱ��������
                                                       1��G3D AXIʱ����1·ʱ�������� */
        unsigned int  reserved_2   : 27; /* bit[5-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DCLKSEL_UNION;
#endif
#define SOC_PMCTRL_G3DCLKSEL_g3da_sw_cfg_START   (0)
#define SOC_PMCTRL_G3DCLKSEL_g3da_sw_cfg_END     (0)
#define SOC_PMCTRL_G3DCLKSEL_g3da_sw_ack_START   (1)
#define SOC_PMCTRL_G3DCLKSEL_g3da_sw_ack_END     (1)
#define SOC_PMCTRL_G3DCLKSEL_g3da_sw_stat_START  (4)
#define SOC_PMCTRL_G3DCLKSEL_g3da_sw_stat_END    (4)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DCLKDIV_UNION
 �ṹ˵��  : G3DCLKDIV �Ĵ����ṹ���塣��ַƫ����:0x224����ֵ:0x7DF31F1F�����:32
 �Ĵ���˵��: G3D AXIʱ�ӷ�Ƶ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3da_clk_div0_cfg : 8;  /* bit[0-7]  : G3D AXIʱ�ӷ�Ƶ��0����3bitΪPLLѡ��ѡ��PPLL0~4��APLL2����5bitΪ��Ƶϵ���� */
        unsigned int  g3da_clk_div1_cfg : 8;  /* bit[8-15] : G3D AXIʱ�ӷ�Ƶ��1����3bitΪPLLѡ��ѡ��PPLL0~4��APLL2����5bitΪ��Ƶϵ���� */
        unsigned int  g3da_clk_div0_ack : 1;  /* bit[16-16]: G3D AXIʱ�ӷ�Ƶ��0�л���ɱ�־�� */
        unsigned int  g3da_clk_div1_ack : 1;  /* bit[17-17]: G3D AXIʱ�ӷ�Ƶ��1�л���ɱ�־�� */
        unsigned int  reserved          : 2;  /* bit[18-19]: ������ */
        unsigned int  g3da_clk_div0_mux : 6;  /* bit[20-25]: 0·ʱ�ӵ�ǰ�������еķ�Ƶ״̬�� */
        unsigned int  g3da_clk_div1_mux : 6;  /* bit[26-31]: 1·ʱ�ӵ�ǰ�������еķ�Ƶ״̬�� */
    } reg;
} SOC_PMCTRL_G3DCLKDIV_UNION;
#endif
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div0_cfg_START  (0)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div0_cfg_END    (7)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div1_cfg_START  (8)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div1_cfg_END    (15)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div0_ack_START  (16)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div0_ack_END    (16)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div1_ack_START  (17)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div1_ack_END    (17)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div0_mux_START  (20)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div0_mux_END    (25)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div1_mux_START  (26)
#define SOC_PMCTRL_G3DCLKDIV_g3da_clk_div1_mux_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DDVFSEN_UNION
 �ṹ˵��  : G3DDVFSEN �Ĵ����ṹ���塣��ַƫ����:0x228����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D DVFSʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_dvfs_en : 1;  /* bit[0-0] : G3D DVFSʹ�ܡ�
                                                      0��G3D DVFS���ܹرգ�
                                                      1��G3D DVFS���ܿ����� */
        unsigned int  reserved    : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DDVFSEN_UNION;
#endif
#define SOC_PMCTRL_G3DDVFSEN_g3d_dvfs_en_START  (0)
#define SOC_PMCTRL_G3DDVFSEN_g3d_dvfs_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DDVFSSTART_UNION
 �ṹ˵��  : G3DDVFSSTART �Ĵ����ṹ���塣��ַƫ����:0x22C����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D DVFS�����Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_profile_updn : 1;  /* bit[0-0] : G3D DVFS������
                                                           0��G3D DVFS����Profile������
                                                           1��G3D DVFS����Profile������ */
        unsigned int  reserved         : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DDVFSSTART_UNION;
#endif
#define SOC_PMCTRL_G3DDVFSSTART_g3d_profile_updn_START  (0)
#define SOC_PMCTRL_G3DDVFSSTART_g3d_profile_updn_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DCLKPROFILE_UNION
 �ṹ˵��  : G3DCLKPROFILE �Ĵ����ṹ���塣��ַƫ����:0x230����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3DƵ��Profile�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3da_clk_div : 8;  /* bit[0-7] : G3D AXIʱ�ӷ�Ƶ��������3bitΪPLLѡ��ѡ��PPLL0~4��APLL2����5bitΪ��Ƶϵ���� */
        unsigned int  g3da_clk_sel : 1;  /* bit[8-8] : G3D AXIʱ��ѡ�������ѡ��DIV0����DIV1��ÿ��DVFS��Ҫ�л�DIV�� */
        unsigned int  reserved     : 23; /* bit[9-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DCLKPROFILE_UNION;
#endif
#define SOC_PMCTRL_G3DCLKPROFILE_g3da_clk_div_START  (0)
#define SOC_PMCTRL_G3DCLKPROFILE_g3da_clk_div_END    (7)
#define SOC_PMCTRL_G3DCLKPROFILE_g3da_clk_sel_START  (8)
#define SOC_PMCTRL_G3DCLKPROFILE_g3da_clk_sel_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DVOLMOD_UNION
 �ṹ˵��  : G3DVOLMOD �Ĵ����ṹ���塣��ַƫ����:0x234����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D DVFS��ѹģʽ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_vol_mod         : 1;  /* bit[0-0] : G3D DVFSʱ���Ƿ���Ҫ��ѹ��
                                                              0��G3D DVFSʱ������Ҫ��ѹ��
                                                              1��G3D DVFSʱ����Ҫ��ѹ�� */
        unsigned int  g3d_clk_off_vol_mod : 1;  /* bit[1-1] : G3Dʱ���Ƿ�رա�
                                                              0��G3Dʱ�ӱ��ִ򿪣�
                                                              1��G3Dʱ��Ҫ��رա� */
        unsigned int  reserved            : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DVOLMOD_UNION;
#endif
#define SOC_PMCTRL_G3DVOLMOD_g3d_vol_mod_START          (0)
#define SOC_PMCTRL_G3DVOLMOD_g3d_vol_mod_END            (0)
#define SOC_PMCTRL_G3DVOLMOD_g3d_clk_off_vol_mod_START  (1)
#define SOC_PMCTRL_G3DVOLMOD_g3d_clk_off_vol_mod_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DVOLPROFILE_UNION
 �ṹ˵��  : G3DVOLPROFILE �Ĵ����ṹ���塣��ַƫ����:0x238����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D��ѹProfile�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_vol_idx : 8;  /* bit[0-7] : G3D��ѹProfile������ */
        unsigned int  reserved    : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DVOLPROFILE_UNION;
#endif
#define SOC_PMCTRL_G3DVOLPROFILE_g3d_vol_idx_START  (0)
#define SOC_PMCTRL_G3DVOLPROFILE_g3d_vol_idx_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DPHASEMOD_UNION
 �ṹ˵��  : G3DPHASEMOD �Ĵ����ṹ���塣��ַƫ����:0x240����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D DVFS�ı��ѹ��λģʽ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_phase_mod         : 1;  /* bit[0-0] : G3D DVFSʱ���Ƿ�ı��ѹ��λ��
                                                                0��G3D DVFSʱ�����ı��ѹ��λ��
                                                                1��G3D DVFSʱ���ı��ѹ��λ�� */
        unsigned int  g3d_clk_off_phase_mod : 1;  /* bit[1-1] : G3D DVFS�ı��ѹ��λʱ�Ƿ�ر�G3Dʱ�ӡ�
                                                                0��G3D�ı��ѹ��λʱ��G3Dʱ�ӱ��ִ򿪣�
                                                                1��G3D�ı��ѹ��λʱ��G3Dʱ�ӹرա� */
        unsigned int  reserved              : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DPHASEMOD_UNION;
#endif
#define SOC_PMCTRL_G3DPHASEMOD_g3d_phase_mod_START          (0)
#define SOC_PMCTRL_G3DPHASEMOD_g3d_phase_mod_END            (0)
#define SOC_PMCTRL_G3DPHASEMOD_g3d_clk_off_phase_mod_START  (1)
#define SOC_PMCTRL_G3DPHASEMOD_g3d_clk_off_phase_mod_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DPHASEPROFILE_UNION
 �ṹ˵��  : G3DPHASEPROFILE �Ĵ����ṹ���塣��ַƫ����:0x244����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D��λProfile�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_phase_idx : 8;  /* bit[0-7] : G3D��λProfile������ */
        unsigned int  reserved      : 24; /* bit[8-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DPHASEPROFILE_UNION;
#endif
#define SOC_PMCTRL_G3DPHASEPROFILE_g3d_phase_idx_START  (0)
#define SOC_PMCTRL_G3DPHASEPROFILE_g3d_phase_idx_END    (7)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DVOLPHASESEL_UNION
 �ṹ˵��  : G3DVOLPHASESEL �Ĵ����ṹ���塣��ַƫ����:0x248����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D��ѹ/��λ����ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_vol_phase_sel : 1;  /* bit[0-0] : G3D��ѹ/��λ�ź����ѡ��
                                                            0��DVFSʱ�ȵ���λ�ٵ���ѹ������profile�Ĵ���ʱ����Ҫ�ı䣻
                                                            1��DVFS�ȵ���ѹ�ڵ���λ������profile�Ĵ���ʱ��Ҫ�ı䣨��ѹprofile�Ĵ���������λ����λprofile�Ĵ������Ƶ�ѹ���� */
        unsigned int  reserved          : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DVOLPHASESEL_UNION;
#endif
#define SOC_PMCTRL_G3DVOLPHASESEL_g3d_vol_phase_sel_START  (0)
#define SOC_PMCTRL_G3DVOLPHASESEL_g3d_vol_phase_sel_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DPMUSEL_UNION
 �ṹ˵��  : G3DPMUSEL �Ĵ����ṹ���塣��ַƫ����:0x24C����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D���PMUѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_pmu_sel : 1;  /* bit[0-0] : G3D���PMUѡ��
                                                      0��G3D������źŸ�PMUSSI��
                                                      1��G3D������źŸ�PMUI2C����ֻ�ܾ�̬���ã��� */
        unsigned int  reserved    : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DPMUSEL_UNION;
#endif
#define SOC_PMCTRL_G3DPMUSEL_g3d_pmu_sel_START  (0)
#define SOC_PMCTRL_G3DPMUSEL_g3d_pmu_sel_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DVOLUPSTEPTIME_UNION
 �ṹ˵��  : G3DVOLUPSTEPTIME �Ĵ����ṹ���塣��ַƫ����:0x250����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D��ѹ����һ���ȶ�����ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_vol_up_step_time : 13; /* bit[0-12] : G3D��ѹ�����ȶ�����ʱ�䡣 */
        unsigned int  reserved             : 19; /* bit[13-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DVOLUPSTEPTIME_UNION;
#endif
#define SOC_PMCTRL_G3DVOLUPSTEPTIME_g3d_vol_up_step_time_START  (0)
#define SOC_PMCTRL_G3DVOLUPSTEPTIME_g3d_vol_up_step_time_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DVOLDNSTEPTIME_UNION
 �ṹ˵��  : G3DVOLDNSTEPTIME �Ĵ����ṹ���塣��ַƫ����:0x254����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D��ѹ�½�һ���ȶ�����ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_vol_dn_step_time : 13; /* bit[0-12] : G3D��ѹ�½��ȶ�����ʱ�䡣 */
        unsigned int  reserved             : 19; /* bit[13-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DVOLDNSTEPTIME_UNION;
#endif
#define SOC_PMCTRL_G3DVOLDNSTEPTIME_g3d_vol_dn_step_time_START  (0)
#define SOC_PMCTRL_G3DVOLDNSTEPTIME_g3d_vol_dn_step_time_END    (12)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DPHASEUPTIME_UNION
 �ṹ˵��  : G3DPHASEUPTIME �Ĵ����ṹ���塣��ַƫ����:0x258����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D DVFSʱ�ı��ѹ��λ�������ȶ�ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_dvfs_phase_up_time : 20; /* bit[0-19] : G3D DVFSʱ���ı��ѹ��λ�������ȶ�ʱ�䡣 */
        unsigned int  reserved               : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DPHASEUPTIME_UNION;
#endif
#define SOC_PMCTRL_G3DPHASEUPTIME_g3d_dvfs_phase_up_time_START  (0)
#define SOC_PMCTRL_G3DPHASEUPTIME_g3d_dvfs_phase_up_time_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DPHASEDNTIME_UNION
 �ṹ˵��  : G3DPHASEDNTIME �Ĵ����ṹ���塣��ַƫ����:0x25C����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D DVFSʱ�ı��ѹ��λ���½��ȶ�ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_dvfs_phase_dn_time : 20; /* bit[0-19] : G3D DVFSʱ���ı��ѹ��λ���½��ȶ�ʱ�䡣 */
        unsigned int  reserved               : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DPHASEDNTIME_UNION;
#endif
#define SOC_PMCTRL_G3DPHASEDNTIME_g3d_dvfs_phase_dn_time_START  (0)
#define SOC_PMCTRL_G3DPHASEDNTIME_g3d_dvfs_phase_dn_time_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DPMUHOLDTIME_UNION
 �ṹ˵��  : G3DPMUHOLDTIME �Ĵ����ṹ���塣��ַƫ����:0x260����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D��ѹ�ȶ�ʱ��ԣ���Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_pmu_vol_hold_time : 20; /* bit[0-19] : G3D��ѹʱ�����ڶ˿ڴ���ʱ������ӵĵ�ѹ�ȶ�ʱ�� */
        unsigned int  reserved              : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DPMUHOLDTIME_UNION;
#endif
#define SOC_PMCTRL_G3DPMUHOLDTIME_g3d_pmu_vol_hold_time_START  (0)
#define SOC_PMCTRL_G3DPMUHOLDTIME_g3d_pmu_vol_hold_time_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DHPMBYPASS_UNION
 �ṹ˵��  : G3DHPMBYPASS �Ĵ����ṹ���塣��ַƫ����:0x264����ֵ:0x03F100FF�����:32
 �Ĵ���˵��: G3D HPMӲ������bypass�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_hpm0_bypass        : 1;  /* bit[0-0]  : G3D HPM0�Ƿ���G3DӲ��״̬�����ơ�
                                                                  0�����ƣ�
                                                                  1�������ơ� */
        unsigned int  g3d_hpm1_bypass        : 1;  /* bit[1-1]  : G3D HPM1�Ƿ���G3DӲ��״̬�����ơ�
                                                                  0�����ƣ�
                                                                  1�������ơ� */
        unsigned int  g3d_hpm2_bypass        : 1;  /* bit[2-2]  : G3D HPM2�Ƿ���G3DӲ��״̬�����ơ�
                                                                  0�����ƣ�
                                                                  1�������ơ� */
        unsigned int  g3d_hpm3_bypass        : 1;  /* bit[3-3]  : G3D HPM3�Ƿ���G3DӲ��״̬�����ơ�
                                                                  0�����ƣ�
                                                                  1�������ơ� */
        unsigned int  g3d_hpm_dly_cnt        : 12; /* bit[4-15] : G3D shader�������ϵ��HPM���õĵȴ�ʱ�䡣
                                                                  ��λΪPMCTRL����Ƶ�ʡ� */
        unsigned int  g3d_idle_clkdiv_bypass : 1;  /* bit[16-16]: G3D��ϵͳIDLEʱ�Զ���Ƶ���ܡ�
                                                                  0����Ч��
                                                                  1������Ч�� */
        unsigned int  reserved_0             : 3;  /* bit[17-19]: ������ */
        unsigned int  g3d_idle_clk_div       : 6;  /* bit[20-25]: G3D IDLEʱ�Զ���Ƶ�ķ�Ƶ�ȡ� */
        unsigned int  reserved_1             : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DHPMBYPASS_UNION;
#endif
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpm0_bypass_START         (0)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpm0_bypass_END           (0)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpm1_bypass_START         (1)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpm1_bypass_END           (1)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpm2_bypass_START         (2)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpm2_bypass_END           (2)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpm3_bypass_START         (3)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpm3_bypass_END           (3)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpm_dly_cnt_START         (4)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_hpm_dly_cnt_END           (15)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_idle_clkdiv_bypass_START  (16)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_idle_clkdiv_bypass_END    (16)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_idle_clk_div_START        (20)
#define SOC_PMCTRL_G3DHPMBYPASS_g3d_idle_clk_div_END          (25)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_UNION
 �ṹ˵��  : G3DAUTOCLKDIVBYPASS �Ĵ����ṹ���塣��ַƫ����:0x268����ֵ:0x000F3F15�����:32
 �Ĵ���˵��: G3D�Զ���Ƶbypass���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_auto_clkdiv_bypass : 1;  /* bit[0-0]  : G3D shader���µ�ʱӲ���Զ���Ƶ����bypass���ơ�
                                                                  0��G3D �Զ���Ƶ���ܿ�����
                                                                  1��G3D �Զ���Ƶ���ܹرա� */
        unsigned int  g3d_auto_clkdiv_time   : 7;  /* bit[1-7]  : G3D�Զ���Ƶ���ȶ�ʱ�䡣
                                                                  ������λ��PMCTRL����ʱ�ӡ� */
        unsigned int  g3d_pwr_dly_cnt        : 8;  /* bit[8-15] : G3D pwr_updn_ack��������������
                                                                  ������λ��PMCTRL����ʱ�ӡ� */
        unsigned int  g3d_auto_clk_div       : 2;  /* bit[16-17]: G3D shader���µ�ʱӲ���Զ���Ƶ������ */
        unsigned int  g3d_div_debounce       : 6;  /* bit[18-23]: G3D shader���µ�ʱ�Զ���Ƶ����ķ����������� */
        unsigned int  reserved               : 8;  /* bit[24-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_UNION;
#endif
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_g3d_auto_clkdiv_bypass_START  (0)
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_g3d_auto_clkdiv_bypass_END    (0)
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_g3d_auto_clkdiv_time_START    (1)
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_g3d_auto_clkdiv_time_END      (7)
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_g3d_pwr_dly_cnt_START         (8)
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_g3d_pwr_dly_cnt_END           (15)
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_g3d_auto_clk_div_START        (16)
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_g3d_auto_clk_div_END          (17)
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_g3d_div_debounce_START        (18)
#define SOC_PMCTRL_G3DAUTOCLKDIVBYPASS_g3d_div_debounce_END          (23)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DAVSEN_UNION
 �ṹ˵��  : G3DAVSEN �Ĵ����ṹ���塣��ַƫ����:0x270����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D AVSʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_avs_en        : 1;  /* bit[0-0] : G3D AVSʹ�ܡ�
                                                            0��G3D AVS���ܹرգ�
                                                            1��G3D AVS���ܿ����� */
        unsigned int  g3d_avs_pwctrl_en : 1;  /* bit[1-1] : G3D AVS��ѹʹ�ܡ�
                                                            0��G3D AVS��ѹ���ܹرգ�
                                                            1��G3D AVS��ѹ���ܿ����� */
        unsigned int  reserved          : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DAVSEN_UNION;
#endif
#define SOC_PMCTRL_G3DAVSEN_g3d_avs_en_START         (0)
#define SOC_PMCTRL_G3DAVSEN_g3d_avs_en_END           (0)
#define SOC_PMCTRL_G3DAVSEN_g3d_avs_pwctrl_en_START  (1)
#define SOC_PMCTRL_G3DAVSEN_g3d_avs_pwctrl_en_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DAVSPARAMOD_UNION
 �ṹ˵��  : G3DAVSPARAMOD �Ĵ����ṹ���塣��ַƫ����:0x274����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D AVS����ģʽ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_avspara_mod : 1;  /* bit[0-0] : G3D AVS����ʵʱ���¿��ơ�
                                                          ͨ����G3D AVS������G3D DVFS����֮����£����������Ĵ���д1��AVS�����������£����������Ĵ���д0����Ч�� */
        unsigned int  reserved        : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DAVSPARAMOD_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARAMOD_g3d_avspara_mod_START  (0)
#define SOC_PMCTRL_G3DAVSPARAMOD_g3d_avspara_mod_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DAVSPARA0_UNION
 �ṹ˵��  : G3DAVSPARA0 �Ĵ����ṹ���塣��ַƫ����:0x278����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D AVS�����Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0         : 2;  /* bit[0-1]  : ���� */
        unsigned int  g3d_avs_opc_offset : 10; /* bit[2-11] : G3D AVSԭʼ������ƫ�ơ� */
        unsigned int  g3d_avs_rcc        : 5;  /* bit[12-16]: G3D AVS�ο�У׼�롣 */
        unsigned int  g3d_avs_irgap      : 5;  /* bit[17-21]: G3D AVS IRDropԣ���� */
        unsigned int  g3d_avs_opc_mod    : 2;  /* bit[22-23]: G3D AVS��ͬһ��HPM OPCֵ�Ķ�β�����δ���
                                                              00��OPCȡ��ֵ��
                                                              01��OPCȡ��Сֵ��
                                                              10��OPCȡ���ֵ��
                                                              11�������� */
        unsigned int  g3d_avs_hpm_sel    : 3;  /* bit[24-26]: G3D AVS�ж��HPM��PCֵ��δ���
                                                              000��ȡG3D HPM0��PCֵ��
                                                              001��ȡG3D HPM1��PCֵ��
                                                              010��ȡG3D HPM2��PCֵ��
                                                              011��ȡG3D HPM3��PCֵ��
                                                              100��ȡG3D global HPM��PCֵ��
                                                              101��ȡHPM�е���Сֵ��
                                                              110��ȡHPM�е����ֵ��
                                                              ������������ */
        unsigned int  g3d_avs_opc_shift  : 3;  /* bit[27-29]: G3D AVSԭʼ��������λ�� */
        unsigned int  reserved_1         : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DAVSPARA0_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_opc_offset_START  (2)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_opc_offset_END    (11)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_rcc_START         (12)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_rcc_END           (16)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_irgap_START       (17)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_irgap_END         (21)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_opc_mod_START     (22)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_opc_mod_END       (23)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_hpm_sel_START     (24)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_hpm_sel_END       (26)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_opc_shift_START   (27)
#define SOC_PMCTRL_G3DAVSPARA0_g3d_avs_opc_shift_END     (29)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DAVSPARA1_UNION
 �ṹ˵��  : G3DAVSPARA1 �Ĵ����ṹ���塣��ַƫ����:0x27C����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D AVS�����Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_avs_vol_up_gain1 : 4;  /* bit[0-3]  : G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_up_gain2 : 4;  /* bit[4-7]  : G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_up_gain3 : 4;  /* bit[8-11] : G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_up_gain4 : 4;  /* bit[12-15]: G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_up_gain5 : 4;  /* bit[16-19]: G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_up_gain6 : 4;  /* bit[20-23]: G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_up_gain7 : 4;  /* bit[24-27]: G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_up_gain8 : 4;  /* bit[28-31]: G3D AVS��ѹ���档 */
    } reg;
} SOC_PMCTRL_G3DAVSPARA1_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain1_START  (0)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain1_END    (3)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain2_START  (4)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain2_END    (7)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain3_START  (8)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain3_END    (11)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain4_START  (12)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain4_END    (15)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain5_START  (16)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain5_END    (19)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain6_START  (20)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain6_END    (23)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain7_START  (24)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain7_END    (27)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain8_START  (28)
#define SOC_PMCTRL_G3DAVSPARA1_g3d_avs_vol_up_gain8_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DAVSPARA2_UNION
 �ṹ˵��  : G3DAVSPARA2 �Ĵ����ṹ���塣��ַƫ����:0x280����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D AVS�����Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_avs_vol_up_gain9  : 4;  /* bit[0-3]  : G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_up_gain10 : 4;  /* bit[4-7]  : G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_up_gain11 : 4;  /* bit[8-11] : G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_up_gain12 : 4;  /* bit[12-15]: G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_up_gain13 : 4;  /* bit[16-19]: G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_up_gain14 : 4;  /* bit[20-23]: G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_up_gain15 : 7;  /* bit[24-30]: G3D AVS��ѹ���档 */
        unsigned int  reserved              : 1;  /* bit[31-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DAVSPARA2_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain9_START   (0)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain9_END     (3)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain10_START  (4)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain10_END    (7)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain11_START  (8)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain11_END    (11)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain12_START  (12)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain12_END    (15)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain13_START  (16)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain13_END    (19)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain14_START  (20)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain14_END    (23)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain15_START  (24)
#define SOC_PMCTRL_G3DAVSPARA2_g3d_avs_vol_up_gain15_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DAVSPARA3_UNION
 �ṹ˵��  : G3DAVSPARA3 �Ĵ����ṹ���塣��ַƫ����:0x284����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D AVS�����Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_avs_vol_dn_gain1 : 4;  /* bit[0-3]  : G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_dn_gain2 : 4;  /* bit[4-7]  : G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_dn_gain3 : 4;  /* bit[8-11] : G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_dn_gain4 : 4;  /* bit[12-15]: G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_dn_gain5 : 4;  /* bit[16-19]: G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_dn_gain6 : 4;  /* bit[20-23]: G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_dn_gain7 : 4;  /* bit[24-27]: G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_dn_gain8 : 4;  /* bit[28-31]: G3D AVS��ѹ���档 */
    } reg;
} SOC_PMCTRL_G3DAVSPARA3_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain1_START  (0)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain1_END    (3)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain2_START  (4)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain2_END    (7)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain3_START  (8)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain3_END    (11)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain4_START  (12)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain4_END    (15)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain5_START  (16)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain5_END    (19)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain6_START  (20)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain6_END    (23)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain7_START  (24)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain7_END    (27)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain8_START  (28)
#define SOC_PMCTRL_G3DAVSPARA3_g3d_avs_vol_dn_gain8_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DAVSPARA4_UNION
 �ṹ˵��  : G3DAVSPARA4 �Ĵ����ṹ���塣��ַƫ����:0x288����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D AVS�����Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_avs_vol_dn_gain9  : 4;  /* bit[0-3]  : G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_dn_gain10 : 4;  /* bit[4-7]  : G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_dn_gain11 : 4;  /* bit[8-11] : G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_dn_gain12 : 4;  /* bit[12-15]: G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_dn_gain13 : 4;  /* bit[16-19]: G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_dn_gain14 : 4;  /* bit[20-23]: G3D AVS��ѹ���档 */
        unsigned int  g3d_avs_vol_dn_gain15 : 7;  /* bit[24-30]: G3D AVS��ѹ���档 */
        unsigned int  reserved              : 1;  /* bit[31-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DAVSPARA4_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain9_START   (0)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain9_END     (3)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain10_START  (4)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain10_END    (7)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain11_START  (8)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain11_END    (11)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain12_START  (12)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain12_END    (15)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain13_START  (16)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain13_END    (19)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain14_START  (20)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain14_END    (23)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain15_START  (24)
#define SOC_PMCTRL_G3DAVSPARA4_g3d_avs_vol_dn_gain15_END    (30)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DAVSPARA5_UNION
 �ṹ˵��  : G3DAVSPARA5 �Ĵ����ṹ���塣��ַƫ����:0x28C����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D AVS�����Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_avs_max_vol : 7;  /* bit[0-6]  : G3D AVS��ߵ�ѹ���ơ� */
        unsigned int  g3d_avs_min_vol : 7;  /* bit[7-13] : G3D AVS��͵�ѹ���ơ� */
        unsigned int  reserved        : 18; /* bit[14-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DAVSPARA5_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_max_vol_START  (0)
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_max_vol_END    (6)
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_min_vol_START  (7)
#define SOC_PMCTRL_G3DAVSPARA5_g3d_avs_min_vol_END    (13)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DAVSPARA6_UNION
 �ṹ˵��  : G3DAVSPARA6 �Ĵ����ṹ���塣��ַƫ����:0x290����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D AVS�����Ĵ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_avs_sample_num : 22; /* bit[0-21] : G3D AVS�������������������ֵ������2��N�η��� */
        unsigned int  reserved           : 10; /* bit[22-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DAVSPARA6_UNION;
#endif
#define SOC_PMCTRL_G3DAVSPARA6_g3d_avs_sample_num_START  (0)
#define SOC_PMCTRL_G3DAVSPARA6_g3d_avs_sample_num_END    (21)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DHPMTYP_UNION
 �ṹ˵��  : G3DHPMTYP �Ĵ����ṹ���塣��ַƫ����:0x294����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D HPM����ѡ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_hpm_type   : 1;  /* bit[0-0]  : AVSѡ��ʹ��G3D HPM���͡�
                                                          0��AVSѡ��ʹ�ñ�׼HPM��
                                                          1��AVSѡ��ʹ��X��HPM�� */
        unsigned int  g3ds_hpm0_mask : 1;  /* bit[1-1]  : AVS�����Ƿ�����HPM0��
                                                          0�������Σ�
                                                          1�����Ρ� */
        unsigned int  g3ds_hpm1_mask : 1;  /* bit[2-2]  : AVS�����Ƿ�����HPM1��
                                                          0�������Σ�
                                                          1�����Ρ� */
        unsigned int  g3ds_hpm2_mask : 1;  /* bit[3-3]  : AVS�����Ƿ�����HPM2��
                                                          0�������Σ�
                                                          1�����Ρ� */
        unsigned int  g3ds_hpm3_mask : 1;  /* bit[4-4]  : AVS�����Ƿ�����HPM3��
                                                          0�������Σ�
                                                          1�����Ρ� */
        unsigned int  g3dg_hpm_mask  : 1;  /* bit[5-5]  : AVS�����Ƿ�����global HPM��
                                                          0�������Σ�
                                                          1�����Ρ� */
        unsigned int  reserved       : 10; /* bit[6-15] : ������ */
        unsigned int  biten          : 16; /* bit[16-31]: ÿ������λ��ʹ��λ��
                                                          ֻ�е�biten��Ӧ�ı���λΪ1'b1����Ӧ�ı���λ�������á�biten[0]����bit 0��ʹ��λ��д1��Ч�� */
    } reg;
} SOC_PMCTRL_G3DHPMTYP_UNION;
#endif
#define SOC_PMCTRL_G3DHPMTYP_g3d_hpm_type_START    (0)
#define SOC_PMCTRL_G3DHPMTYP_g3d_hpm_type_END      (0)
#define SOC_PMCTRL_G3DHPMTYP_g3ds_hpm0_mask_START  (1)
#define SOC_PMCTRL_G3DHPMTYP_g3ds_hpm0_mask_END    (1)
#define SOC_PMCTRL_G3DHPMTYP_g3ds_hpm1_mask_START  (2)
#define SOC_PMCTRL_G3DHPMTYP_g3ds_hpm1_mask_END    (2)
#define SOC_PMCTRL_G3DHPMTYP_g3ds_hpm2_mask_START  (3)
#define SOC_PMCTRL_G3DHPMTYP_g3ds_hpm2_mask_END    (3)
#define SOC_PMCTRL_G3DHPMTYP_g3ds_hpm3_mask_START  (4)
#define SOC_PMCTRL_G3DHPMTYP_g3ds_hpm3_mask_END    (4)
#define SOC_PMCTRL_G3DHPMTYP_g3dg_hpm_mask_START   (5)
#define SOC_PMCTRL_G3DHPMTYP_g3dg_hpm_mask_END     (5)
#define SOC_PMCTRL_G3DHPMTYP_biten_START           (16)
#define SOC_PMCTRL_G3DHPMTYP_biten_END             (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DHPMEN_UNION
 �ṹ˵��  : G3DHPMEN �Ĵ����ṹ���塣��ַƫ����:0x298����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D HPMʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpm0_en_cfg  : 1;  /* bit[0-0] : G3D HPMʹ�ܡ�
                                                            HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  g3ds_hpm1_en_cfg  : 1;  /* bit[1-1] : G3D HPMʹ�ܡ�
                                                            HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  g3dg_hpm_en_cfg   : 1;  /* bit[2-2] : G3D global HPMʹ�ܡ�
                                                            HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_0        : 1;  /* bit[3-3] : ������ */
        unsigned int  g3ds_hpm0_en_stat : 1;  /* bit[4-4] : G3D HPMʹ�ܡ�
                                                            HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  g3ds_hpm1_en_stat : 1;  /* bit[5-5] : G3D HPMʹ�ܡ�
                                                            HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  g3dg_hpm_en_stat  : 1;  /* bit[6-6] : G3D global HPMʹ�ܡ�
                                                            HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_1        : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DHPMEN_UNION;
#endif
#define SOC_PMCTRL_G3DHPMEN_g3ds_hpm0_en_cfg_START   (0)
#define SOC_PMCTRL_G3DHPMEN_g3ds_hpm0_en_cfg_END     (0)
#define SOC_PMCTRL_G3DHPMEN_g3ds_hpm1_en_cfg_START   (1)
#define SOC_PMCTRL_G3DHPMEN_g3ds_hpm1_en_cfg_END     (1)
#define SOC_PMCTRL_G3DHPMEN_g3dg_hpm_en_cfg_START    (2)
#define SOC_PMCTRL_G3DHPMEN_g3dg_hpm_en_cfg_END      (2)
#define SOC_PMCTRL_G3DHPMEN_g3ds_hpm0_en_stat_START  (4)
#define SOC_PMCTRL_G3DHPMEN_g3ds_hpm0_en_stat_END    (4)
#define SOC_PMCTRL_G3DHPMEN_g3ds_hpm1_en_stat_START  (5)
#define SOC_PMCTRL_G3DHPMEN_g3ds_hpm1_en_stat_END    (5)
#define SOC_PMCTRL_G3DHPMEN_g3dg_hpm_en_stat_START   (6)
#define SOC_PMCTRL_G3DHPMEN_g3dg_hpm_en_stat_END     (6)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DHPMXEN_UNION
 �ṹ˵��  : G3DHPMXEN �Ĵ����ṹ���塣��ַƫ����:0x29C����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D HPMXʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpmx0_en_cfg  : 1;  /* bit[0-0] : G3D HPMXʹ�ܡ�
                                                             HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  g3ds_hpmx1_en_cfg  : 1;  /* bit[1-1] : G3D HPMXʹ�ܡ�
                                                             HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  g3dg_hpmx_en_cfg   : 1;  /* bit[2-2] : G3D global HPMXʹ�ܡ�
                                                             HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_0         : 1;  /* bit[3-3] : ������ */
        unsigned int  g3ds_hpmx0_en_stat : 1;  /* bit[4-4] : G3D HPMXʹ�ܡ�
                                                             HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  g3ds_hpmx1_en_stat : 1;  /* bit[5-5] : G3D HPMXʹ�ܡ�
                                                             HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  g3dg_hpmx_en_stat  : 1;  /* bit[6-6] : G3D global HPMXʹ�ܡ�
                                                             HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_1         : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DHPMXEN_UNION;
#endif
#define SOC_PMCTRL_G3DHPMXEN_g3ds_hpmx0_en_cfg_START   (0)
#define SOC_PMCTRL_G3DHPMXEN_g3ds_hpmx0_en_cfg_END     (0)
#define SOC_PMCTRL_G3DHPMXEN_g3ds_hpmx1_en_cfg_START   (1)
#define SOC_PMCTRL_G3DHPMXEN_g3ds_hpmx1_en_cfg_END     (1)
#define SOC_PMCTRL_G3DHPMXEN_g3dg_hpmx_en_cfg_START    (2)
#define SOC_PMCTRL_G3DHPMXEN_g3dg_hpmx_en_cfg_END      (2)
#define SOC_PMCTRL_G3DHPMXEN_g3ds_hpmx0_en_stat_START  (4)
#define SOC_PMCTRL_G3DHPMXEN_g3ds_hpmx0_en_stat_END    (4)
#define SOC_PMCTRL_G3DHPMXEN_g3ds_hpmx1_en_stat_START  (5)
#define SOC_PMCTRL_G3DHPMXEN_g3ds_hpmx1_en_stat_END    (5)
#define SOC_PMCTRL_G3DHPMXEN_g3dg_hpmx_en_stat_START   (6)
#define SOC_PMCTRL_G3DHPMXEN_g3dg_hpmx_en_stat_END     (6)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DHPMOPCVALID_UNION
 �ṹ˵��  : G3DHPMOPCVALID �Ĵ����ṹ���塣��ַƫ����:0x2A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D HPM OPC��Ч�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpm0_opc_vld  : 1;  /* bit[0-0] : G3D HPMԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  g3ds_hpm1_opc_vld  : 1;  /* bit[1-1] : G3D HPMԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  g3dg_hpm_opc_vld   : 1;  /* bit[2-2] : G3D global HPMԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  g3ds_hpmx0_opc_vld : 1;  /* bit[3-3] : G3D HPMXԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  g3ds_hpmx1_opc_vld : 1;  /* bit[4-4] : G3D HPMXԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  g3dg_hpmx_opc_vld  : 1;  /* bit[5-5] : G3D global HPMXԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  reserved           : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DHPMOPCVALID_UNION;
#endif
#define SOC_PMCTRL_G3DHPMOPCVALID_g3ds_hpm0_opc_vld_START   (0)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3ds_hpm0_opc_vld_END     (0)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3ds_hpm1_opc_vld_START   (1)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3ds_hpm1_opc_vld_END     (1)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3dg_hpm_opc_vld_START    (2)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3dg_hpm_opc_vld_END      (2)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3ds_hpmx0_opc_vld_START  (3)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3ds_hpmx0_opc_vld_END    (3)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3ds_hpmx1_opc_vld_START  (4)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3ds_hpmx1_opc_vld_END    (4)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3dg_hpmx_opc_vld_START   (5)
#define SOC_PMCTRL_G3DHPMOPCVALID_g3dg_hpmx_opc_vld_END     (5)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DHPMOPC_UNION
 �ṹ˵��  : G3DHPMOPC �Ĵ����ṹ���塣��ַƫ����:0x2A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D HPM OPC�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpm0_opc : 10; /* bit[0-9]  : G3D HPMԭʼ�����롣 */
        unsigned int  g3ds_hpm1_opc : 10; /* bit[10-19]: G3D HPMԭʼ�����롣 */
        unsigned int  g3dg_hpm_opc  : 10; /* bit[20-29]: G3D global HPMԭʼ�����롣 */
        unsigned int  reserved      : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DHPMOPC_UNION;
#endif
#define SOC_PMCTRL_G3DHPMOPC_g3ds_hpm0_opc_START  (0)
#define SOC_PMCTRL_G3DHPMOPC_g3ds_hpm0_opc_END    (9)
#define SOC_PMCTRL_G3DHPMOPC_g3ds_hpm1_opc_START  (10)
#define SOC_PMCTRL_G3DHPMOPC_g3ds_hpm1_opc_END    (19)
#define SOC_PMCTRL_G3DHPMOPC_g3dg_hpm_opc_START   (20)
#define SOC_PMCTRL_G3DHPMOPC_g3dg_hpm_opc_END     (29)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DHPMXOPC_UNION
 �ṹ˵��  : G3DHPMXOPC �Ĵ����ṹ���塣��ַƫ����:0x2A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D HPMX OPC�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpmx0_opc : 10; /* bit[0-9]  : G3D HPMXԭʼ�����롣 */
        unsigned int  g3ds_hpmx1_opc : 10; /* bit[10-19]: G3D HPMXԭʼ�����롣 */
        unsigned int  g3dg_hpmx_opc  : 10; /* bit[20-29]: G3D global HPMXԭʼ�����롣 */
        unsigned int  reserved       : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DHPMXOPC_UNION;
#endif
#define SOC_PMCTRL_G3DHPMXOPC_g3ds_hpmx0_opc_START  (0)
#define SOC_PMCTRL_G3DHPMXOPC_g3ds_hpmx0_opc_END    (9)
#define SOC_PMCTRL_G3DHPMXOPC_g3ds_hpmx1_opc_START  (10)
#define SOC_PMCTRL_G3DHPMXOPC_g3ds_hpmx1_opc_END    (19)
#define SOC_PMCTRL_G3DHPMXOPC_g3dg_hpmx_opc_START   (20)
#define SOC_PMCTRL_G3DHPMXOPC_g3dg_hpmx_opc_END     (29)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DHPMPC_UNION
 �ṹ˵��  : G3DHPMPC �Ĵ����ṹ���塣��ַƫ����:0x2AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D HPM PC�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpm0_pc_avs : 10; /* bit[0-9]  : G3D HPM�����롣 */
        unsigned int  g3ds_hpm1_pc_avs : 10; /* bit[10-19]: G3D HPM�����롣 */
        unsigned int  g3dg_hpm_pc_avs  : 10; /* bit[20-29]: G3D global HPM�����롣 */
        unsigned int  reserved         : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DHPMPC_UNION;
#endif
#define SOC_PMCTRL_G3DHPMPC_g3ds_hpm0_pc_avs_START  (0)
#define SOC_PMCTRL_G3DHPMPC_g3ds_hpm0_pc_avs_END    (9)
#define SOC_PMCTRL_G3DHPMPC_g3ds_hpm1_pc_avs_START  (10)
#define SOC_PMCTRL_G3DHPMPC_g3ds_hpm1_pc_avs_END    (19)
#define SOC_PMCTRL_G3DHPMPC_g3dg_hpm_pc_avs_START   (20)
#define SOC_PMCTRL_G3DHPMPC_g3dg_hpm_pc_avs_END     (29)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DHPMEN1_UNION
 �ṹ˵��  : G3DHPMEN1 �Ĵ����ṹ���塣��ַƫ����:0x2B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D HPMʹ�ܼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpm2_en_cfg  : 1;  /* bit[0-0] : G3D HPMʹ�ܡ�
                                                            HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  g3ds_hpm3_en_cfg  : 1;  /* bit[1-1] : G3D HPMʹ�ܡ�
                                                            HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_0        : 1;  /* bit[2-2] : ������ */
        unsigned int  reserved_1        : 1;  /* bit[3-3] : ������ */
        unsigned int  g3ds_hpm2_en_stat : 1;  /* bit[4-4] : G3D HPMʹ�ܡ�
                                                            HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  g3ds_hpm3_en_stat : 1;  /* bit[5-5] : G3D HPMʹ�ܡ�
                                                            HPMʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_2        : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DHPMEN1_UNION;
#endif
#define SOC_PMCTRL_G3DHPMEN1_g3ds_hpm2_en_cfg_START   (0)
#define SOC_PMCTRL_G3DHPMEN1_g3ds_hpm2_en_cfg_END     (0)
#define SOC_PMCTRL_G3DHPMEN1_g3ds_hpm3_en_cfg_START   (1)
#define SOC_PMCTRL_G3DHPMEN1_g3ds_hpm3_en_cfg_END     (1)
#define SOC_PMCTRL_G3DHPMEN1_g3ds_hpm2_en_stat_START  (4)
#define SOC_PMCTRL_G3DHPMEN1_g3ds_hpm2_en_stat_END    (4)
#define SOC_PMCTRL_G3DHPMEN1_g3ds_hpm3_en_stat_START  (5)
#define SOC_PMCTRL_G3DHPMEN1_g3ds_hpm3_en_stat_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DHPMXEN1_UNION
 �ṹ˵��  : G3DHPMXEN1 �Ĵ����ṹ���塣��ַƫ����:0x2B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D HPMXʹ�ܼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpmx2_en_cfg  : 1;  /* bit[0-0] : G3D HPMXʹ�ܡ�
                                                             HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  g3ds_hpmx3_en_cfg  : 1;  /* bit[1-1] : G3D HPMXʹ�ܡ�
                                                             HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_0         : 1;  /* bit[2-2] : ������ */
        unsigned int  reserved_1         : 1;  /* bit[3-3] : ������ */
        unsigned int  g3ds_hpmx2_en_stat : 1;  /* bit[4-4] : G3D HPMXʹ�ܡ�
                                                             HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  g3ds_hpmx3_en_stat : 1;  /* bit[5-5] : G3D HPMXʹ�ܡ�
                                                             HPMXʹ�ܿ��Ƴ������������λ���������AVS������Ҳ�ᱻAVS�����߼��Զ���λ������� */
        unsigned int  reserved_2         : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DHPMXEN1_UNION;
#endif
#define SOC_PMCTRL_G3DHPMXEN1_g3ds_hpmx2_en_cfg_START   (0)
#define SOC_PMCTRL_G3DHPMXEN1_g3ds_hpmx2_en_cfg_END     (0)
#define SOC_PMCTRL_G3DHPMXEN1_g3ds_hpmx3_en_cfg_START   (1)
#define SOC_PMCTRL_G3DHPMXEN1_g3ds_hpmx3_en_cfg_END     (1)
#define SOC_PMCTRL_G3DHPMXEN1_g3ds_hpmx2_en_stat_START  (4)
#define SOC_PMCTRL_G3DHPMXEN1_g3ds_hpmx2_en_stat_END    (4)
#define SOC_PMCTRL_G3DHPMXEN1_g3ds_hpmx3_en_stat_START  (5)
#define SOC_PMCTRL_G3DHPMXEN1_g3ds_hpmx3_en_stat_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DHPMOPCVALID1_UNION
 �ṹ˵��  : G3DHPMOPCVALID1 �Ĵ����ṹ���塣��ַƫ����:0x2BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D HPM OPC��Ч�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpm2_opc_vld  : 1;  /* bit[0-0] : G3D HPMԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  g3ds_hpm3_opc_vld  : 1;  /* bit[1-1] : G3D HPMԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  g3ds_hpmx2_opc_vld : 1;  /* bit[2-2] : G3D HPMXԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  g3ds_hpmx3_opc_vld : 1;  /* bit[3-3] : G3D HPMXԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  reserved           : 28; /* bit[4-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DHPMOPCVALID1_UNION;
#endif
#define SOC_PMCTRL_G3DHPMOPCVALID1_g3ds_hpm2_opc_vld_START   (0)
#define SOC_PMCTRL_G3DHPMOPCVALID1_g3ds_hpm2_opc_vld_END     (0)
#define SOC_PMCTRL_G3DHPMOPCVALID1_g3ds_hpm3_opc_vld_START   (1)
#define SOC_PMCTRL_G3DHPMOPCVALID1_g3ds_hpm3_opc_vld_END     (1)
#define SOC_PMCTRL_G3DHPMOPCVALID1_g3ds_hpmx2_opc_vld_START  (2)
#define SOC_PMCTRL_G3DHPMOPCVALID1_g3ds_hpmx2_opc_vld_END    (2)
#define SOC_PMCTRL_G3DHPMOPCVALID1_g3ds_hpmx3_opc_vld_START  (3)
#define SOC_PMCTRL_G3DHPMOPCVALID1_g3ds_hpmx3_opc_vld_END    (3)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DHPMOPC1_UNION
 �ṹ˵��  : G3DHPMOPC1 �Ĵ����ṹ���塣��ַƫ����:0x2C0����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D HPM OPC�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpm2_opc : 10; /* bit[0-9]  : G3D HPMԭʼ�����롣 */
        unsigned int  g3ds_hpm3_opc : 10; /* bit[10-19]: G3D HPMԭʼ�����롣 */
        unsigned int  reserved      : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DHPMOPC1_UNION;
#endif
#define SOC_PMCTRL_G3DHPMOPC1_g3ds_hpm2_opc_START  (0)
#define SOC_PMCTRL_G3DHPMOPC1_g3ds_hpm2_opc_END    (9)
#define SOC_PMCTRL_G3DHPMOPC1_g3ds_hpm3_opc_START  (10)
#define SOC_PMCTRL_G3DHPMOPC1_g3ds_hpm3_opc_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DHPMXOPC1_UNION
 �ṹ˵��  : G3DHPMXOPC1 �Ĵ����ṹ���塣��ַƫ����:0x2C4����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D HPMX OPC�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpmx2_opc : 10; /* bit[0-9]  : G3D HPMXԭʼ�����롣 */
        unsigned int  g3ds_hpmx3_opc : 10; /* bit[10-19]: G3D HPMXԭʼ�����롣 */
        unsigned int  reserved       : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DHPMXOPC1_UNION;
#endif
#define SOC_PMCTRL_G3DHPMXOPC1_g3ds_hpmx2_opc_START  (0)
#define SOC_PMCTRL_G3DHPMXOPC1_g3ds_hpmx2_opc_END    (9)
#define SOC_PMCTRL_G3DHPMXOPC1_g3ds_hpmx3_opc_START  (10)
#define SOC_PMCTRL_G3DHPMXOPC1_g3ds_hpmx3_opc_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DHPMPC1_UNION
 �ṹ˵��  : G3DHPMPC1 �Ĵ����ṹ���塣��ַƫ����:0x2C8����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D HPM PC�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpm2_pc_avs : 10; /* bit[0-9]  : G3D HPM�����롣 */
        unsigned int  g3ds_hpm3_pc_avs : 10; /* bit[10-19]: G3D HPM�����롣 */
        unsigned int  reserved         : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DHPMPC1_UNION;
#endif
#define SOC_PMCTRL_G3DHPMPC1_g3ds_hpm2_pc_avs_START  (0)
#define SOC_PMCTRL_G3DHPMPC1_g3ds_hpm2_pc_avs_END    (9)
#define SOC_PMCTRL_G3DHPMPC1_g3ds_hpm3_pc_avs_START  (10)
#define SOC_PMCTRL_G3DHPMPC1_g3ds_hpm3_pc_avs_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DHPMMASKSTAT_UNION
 �ṹ˵��  : G3DHPMMASKSTAT �Ĵ����ṹ���塣��ַƫ����:0x2E8����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D HPM����״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3ds_hpm0_mask_stat : 1;  /* bit[0-0] : G3D HPM0 ����״̬��
                                                              0��G3D HPM0û�б����Σ�
                                                              1��G3D HPM0�����Ρ� */
        unsigned int  g3ds_hpm1_mask_stat : 1;  /* bit[1-1] : G3D HPM1 ����״̬��
                                                              0��G3D HPM1û�б����Σ�
                                                              1��G3D HPM1�����Ρ� */
        unsigned int  g3ds_hpm2_mask_stat : 1;  /* bit[2-2] : G3D HPM2 ����״̬��
                                                              0��G3D HPM2û�б����Σ�
                                                              1��G3D HPM2�����Ρ� */
        unsigned int  g3ds_hpm3_mask_stat : 1;  /* bit[3-3] : G3D HPM3 ����״̬��
                                                              0��G3D HPM3û�б����Σ�
                                                              1��G3D HPM3�����Ρ� */
        unsigned int  g3dg_hpm_mask_stat  : 1;  /* bit[4-4] : G3D global HPM ����״̬��
                                                              0��G3D global HPMû�б����Σ�
                                                              1��G3D global HPM�����Ρ� */
        unsigned int  reserved            : 27; /* bit[5-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DHPMMASKSTAT_UNION;
#endif
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3ds_hpm0_mask_stat_START  (0)
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3ds_hpm0_mask_stat_END    (0)
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3ds_hpm1_mask_stat_START  (1)
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3ds_hpm1_mask_stat_END    (1)
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3ds_hpm2_mask_stat_START  (2)
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3ds_hpm2_mask_stat_END    (2)
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3ds_hpm3_mask_stat_START  (3)
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3ds_hpm3_mask_stat_END    (3)
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3dg_hpm_mask_stat_START   (4)
#define SOC_PMCTRL_G3DHPMMASKSTAT_g3dg_hpm_mask_stat_END     (4)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DHPMCLKDIV_UNION
 �ṹ˵��  : G3DHPMCLKDIV �Ĵ����ṹ���塣��ַƫ����:0x2EC����ֵ:0x00000001�����:32
 �Ĵ���˵��: G3D HPMʱ�ӷ�Ƶ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_avs_hpm_div : 6;  /* bit[0-5] : G3D HPMʱ�ӷ�Ƶ���� */
        unsigned int  reserved        : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DHPMCLKDIV_UNION;
#endif
#define SOC_PMCTRL_G3DHPMCLKDIV_g3d_avs_hpm_div_START  (0)
#define SOC_PMCTRL_G3DHPMCLKDIV_g3d_avs_hpm_div_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DAVSVOLIDX_UNION
 �ṹ˵��  : G3DAVSVOLIDX �Ĵ����ṹ���塣��ַƫ����:0x2F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: G3D AVS��ѹ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_avs_vol_idx_cfg  : 8;  /* bit[0-7]  : G3D AVS��ǰ��ѹֵ����ֵ����ͨ����������øüĴ���ʱbit 8��д1������Ҫ�üĴ���ֵ��PMU��ѹֵ��ͬ�� */
        unsigned int  g3d_vol_chg_sftreq   : 1;  /* bit[8-8]  : G3D��ѹ�ı���������źš�
                                                                д1������ı��ѹ����ѹֵΪbit 7:0ֵ
                                                                д0����Ч���� */
        unsigned int  reserved_0           : 3;  /* bit[9-11] :  */
        unsigned int  g3d_avs_vol_idx_stat : 8;  /* bit[12-19]: G3D AVS��ǰ��ѹֵ����ֵ����ͨ����������øüĴ���ʱbit 8��д1������Ҫ�üĴ���ֵ��PMU��ѹֵ��ͬ�� */
        unsigned int  reserved_1           : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DAVSVOLIDX_UNION;
#endif
#define SOC_PMCTRL_G3DAVSVOLIDX_g3d_avs_vol_idx_cfg_START   (0)
#define SOC_PMCTRL_G3DAVSVOLIDX_g3d_avs_vol_idx_cfg_END     (7)
#define SOC_PMCTRL_G3DAVSVOLIDX_g3d_vol_chg_sftreq_START    (8)
#define SOC_PMCTRL_G3DAVSVOLIDX_g3d_vol_chg_sftreq_END      (8)
#define SOC_PMCTRL_G3DAVSVOLIDX_g3d_avs_vol_idx_stat_START  (12)
#define SOC_PMCTRL_G3DAVSVOLIDX_g3d_avs_vol_idx_stat_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_DDRLPCTRL_UNION
 �ṹ˵��  : DDRLPCTRL �Ĵ����ṹ���塣��ַƫ����:0x30C����ֵ:0x000000F0�����:32
 �Ĵ���˵��: DDRC LP���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ddrc_csysreq_cfg  : 1;  /* bit[0-0]  : ����DDRC Aͨ������͹���ģʽ��
                                                             0������DDRC����͹���ģʽ��
                                                             1������DDRC�˳��͹���ģʽ�� */
        unsigned int  reserved_0        : 1;  /* bit[1-1]  : ������ */
        unsigned int  reserved_1        : 1;  /* bit[2-2]  : ������ */
        unsigned int  reserved_2        : 1;  /* bit[3-3]  : ������ */
        unsigned int  ddrc_csysack      : 1;  /* bit[4-4]  : DDRC Aͨ�������������Ӧ��
                                                             0����������DDRC����͹���ģʽ����Ӧ��
                                                             1����������DDRC�˳��͹���ģʽ����Ӧ�� */
        unsigned int  reserved_3        : 1;  /* bit[5-5]  : ������ */
        unsigned int  reserved_4        : 1;  /* bit[6-6]  : ������ */
        unsigned int  reserved_5        : 1;  /* bit[7-7]  : ������ */
        unsigned int  ddrc_csysreq_stat : 1;  /* bit[8-8]  : ����DDRC Aͨ������͹���ģʽ��
                                                             0������DDRC����͹���ģʽ��
                                                             1������DDRC�˳��͹���ģʽ�� */
        unsigned int  reserved_6        : 1;  /* bit[9-9]  : ������ */
        unsigned int  reserved_7        : 1;  /* bit[10-10]: ������ */
        unsigned int  reserved_8        : 1;  /* bit[11-11]: ������ */
        unsigned int  reserved_9        : 20; /* bit[12-31]: ������ */
    } reg;
} SOC_PMCTRL_DDRLPCTRL_UNION;
#endif
#define SOC_PMCTRL_DDRLPCTRL_ddrc_csysreq_cfg_START   (0)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_csysreq_cfg_END     (0)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_csysack_START       (4)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_csysack_END         (4)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_csysreq_stat_START  (8)
#define SOC_PMCTRL_DDRLPCTRL_ddrc_csysreq_stat_END    (8)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PLLLOCKTIME_UNION
 �ṹ˵��  : PLLLOCKTIME �Ĵ����ṹ���塣��ַƫ����:0x320����ֵ:0x000FFAEB�����:32
 �Ĵ���˵��: PLL Lock�ȶ�ʱ��Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pll_lock_time : 20; /* bit[0-19] : PLL Lock�ȶ�ʱ�䡣 */
        unsigned int  reserved      : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_PLLLOCKTIME_UNION;
#endif
#define SOC_PMCTRL_PLLLOCKTIME_pll_lock_time_START  (0)
#define SOC_PMCTRL_PLLLOCKTIME_pll_lock_time_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PLLLOCKMOD_UNION
 �ṹ˵��  : PLLLOCKMOD �Ĵ����ṹ���塣��ַƫ����:0x324����ֵ:0x00000001�����:32
 �Ĵ���˵��: PLL�ȶ�ģʽ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  pll_lock_mod : 1;  /* bit[0-0] : PLL �ȶ�ģʽ��
                                                       0��ʹ��PLL��Lock��־����ʾPLL���ȶ���
                                                       1��ʹ��PLL���ȶ���ʱ����ʾPLL���ȶ��� */
        unsigned int  reserved     : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_PLLLOCKMOD_UNION;
#endif
#define SOC_PMCTRL_PLLLOCKMOD_pll_lock_mod_START  (0)
#define SOC_PMCTRL_PLLLOCKMOD_pll_lock_mod_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_AVSRUNROUND_UNION
 �ṹ˵��  : AVSRUNROUND �Ĵ����ṹ���塣��ַƫ����:0x32C����ֵ:0x00000000�����:32
 �Ĵ���˵��: AVS���������Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpu_avs_round : 8;  /* bit[0-7]  : Cluster0_ AVS����������
                                                                  Cluster0_ AVSÿ����һ�֣��������1��
                                                                  ��Cluster0_ AVS��ѹOK�ж���Чʱ������ά�ֲ��䣬�Ա������ȡ��
                                                                  ��Cluster0_ AVS��ѹOK�ж����ʱ��������0�����¿�ʼ�� */
        unsigned int  cluster1_cpu_avs_round : 8;  /* bit[8-15] : Cluster1_ AVS����������
                                                                  Cluster1_ AVSÿ����һ�֣��������1��
                                                                  ��Cluster1_ AVS��ѹOK�ж���Чʱ������ά�ֲ��䣬�Ա������ȡ��
                                                                  ��Cluster1_ AVS��ѹOK�ж����ʱ��������0�����¿�ʼ�� */
        unsigned int  g3d_avs_round          : 8;  /* bit[16-23]: G3D Core AVS����������
                                                                  G3D Core AVSÿ����һ�֣��������1��
                                                                  ��G3D Core AVS��ѹOK�ж���Чʱ������ά�ֲ��䣬�Ա������ȡ��
                                                                  ��G3D Core AVS��ѹOK�ж����ʱ��������0�����¿�ʼ�� */
        unsigned int  reserved               : 8;  /* bit[24-31]: ������ */
    } reg;
} SOC_PMCTRL_AVSRUNROUND_UNION;
#endif
#define SOC_PMCTRL_AVSRUNROUND_cluster0_cpu_avs_round_START  (0)
#define SOC_PMCTRL_AVSRUNROUND_cluster0_cpu_avs_round_END    (7)
#define SOC_PMCTRL_AVSRUNROUND_cluster1_cpu_avs_round_START  (8)
#define SOC_PMCTRL_AVSRUNROUND_cluster1_cpu_avs_round_END    (15)
#define SOC_PMCTRL_AVSRUNROUND_g3d_avs_round_START           (16)
#define SOC_PMCTRL_AVSRUNROUND_g3d_avs_round_END             (23)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PMUSSIAVSEN_UNION
 �ṹ˵��  : PMUSSIAVSEN �Ĵ����ṹ���塣��ַƫ����:0x330����ֵ:0x00000000�����:32
 �Ĵ���˵��: PMUSSI AVSʹ���źš�
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  avs_en_ssi : 1;  /* bit[0-0] : PMUSSI AVSʹ���źţ������ź�Ϊ1'b1ʱ��PMUSSI����PMC�ĵ�ѹ����������ת��ΪSSIʱ���źŸ�PMU��
                                                     ������ø��źŵ�˳��Ϊ������ҪӲ����ѹ��DVFS��AVS��֮ǰ�������ź�������Ч��������ҪӲ����ѹ�������Ҫ����PMUʱ���ȴ���ǰ��ѹ�����������ٽ����ź�������Ч�� */
        unsigned int  reserved   : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_PMUSSIAVSEN_UNION;
#endif
#define SOC_PMCTRL_PMUSSIAVSEN_avs_en_ssi_START  (0)
#define SOC_PMCTRL_PMUSSIAVSEN_avs_en_ssi_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_CTRL0_UNION
 �ṹ˵��  : PERI_CTRL0 �Ĵ����ṹ���塣��ַƫ����:0x340����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ�ÿ��ƼĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_ctrl_ddrc  : 1;  /* bit[0-0] : debug�����źš� */
        unsigned int  dbg_ctrl_cssys : 1;  /* bit[1-1] : debug�����źš� */
        unsigned int  dbg_ctrl_ssi   : 1;  /* bit[2-2] : debug�����źš� */
        unsigned int  dbg_ctrl_i2c   : 1;  /* bit[3-3] : debug�����źš� */
        unsigned int  dbg_ctrl_ssi1  : 1;  /* bit[4-4] : debug�����źš� */
        unsigned int  reserved       : 27; /* bit[5-31]: ������ */
    } reg;
} SOC_PMCTRL_PERI_CTRL0_UNION;
#endif
#define SOC_PMCTRL_PERI_CTRL0_dbg_ctrl_ddrc_START   (0)
#define SOC_PMCTRL_PERI_CTRL0_dbg_ctrl_ddrc_END     (0)
#define SOC_PMCTRL_PERI_CTRL0_dbg_ctrl_cssys_START  (1)
#define SOC_PMCTRL_PERI_CTRL0_dbg_ctrl_cssys_END    (1)
#define SOC_PMCTRL_PERI_CTRL0_dbg_ctrl_ssi_START    (2)
#define SOC_PMCTRL_PERI_CTRL0_dbg_ctrl_ssi_END      (2)
#define SOC_PMCTRL_PERI_CTRL0_dbg_ctrl_i2c_START    (3)
#define SOC_PMCTRL_PERI_CTRL0_dbg_ctrl_i2c_END      (3)
#define SOC_PMCTRL_PERI_CTRL0_dbg_ctrl_ssi1_START   (4)
#define SOC_PMCTRL_PERI_CTRL0_dbg_ctrl_ssi1_END     (4)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_CTRL1_UNION
 �ṹ˵��  : PERI_CTRL1 �Ĵ����ṹ���塣��ַƫ����:0x344����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ�ÿ��ƼĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_pmu_vol_addr0 : 10; /* bit[0-9]  : PMUSSI���õ�ַ����ӦCluster1_��������� */
        unsigned int  reserved_0             : 6;  /* bit[10-15]: ������ */
        unsigned int  cluster1_pmu_vol_addr1 : 10; /* bit[16-25]: PMUSSI���õ�ַ����ӦCluster1_��ѹ������ */
        unsigned int  reserved_1             : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_PMCTRL_PERI_CTRL1_UNION;
#endif
#define SOC_PMCTRL_PERI_CTRL1_cluster1_pmu_vol_addr0_START  (0)
#define SOC_PMCTRL_PERI_CTRL1_cluster1_pmu_vol_addr0_END    (9)
#define SOC_PMCTRL_PERI_CTRL1_cluster1_pmu_vol_addr1_START  (16)
#define SOC_PMCTRL_PERI_CTRL1_cluster1_pmu_vol_addr1_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_CTRL2_UNION
 �ṹ˵��  : PERI_CTRL2 �Ĵ����ṹ���塣��ַƫ����:0x348����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ�ÿ��ƼĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_pmu_vol_addr0 : 10; /* bit[0-9]  : PMUSSI���õ�ַ����ӦCluster0_��������� */
        unsigned int  reserved_0             : 6;  /* bit[10-15]: ������ */
        unsigned int  cluster0_pmu_vol_addr1 : 10; /* bit[16-25]: PMUSSI���õ�ַ����ӦCluster0_��ѹ������ */
        unsigned int  reserved_1             : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_PMCTRL_PERI_CTRL2_UNION;
#endif
#define SOC_PMCTRL_PERI_CTRL2_cluster0_pmu_vol_addr0_START  (0)
#define SOC_PMCTRL_PERI_CTRL2_cluster0_pmu_vol_addr0_END    (9)
#define SOC_PMCTRL_PERI_CTRL2_cluster0_pmu_vol_addr1_START  (16)
#define SOC_PMCTRL_PERI_CTRL2_cluster0_pmu_vol_addr1_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_CTRL3_UNION
 �ṹ˵��  : PERI_CTRL3 �Ĵ����ṹ���塣��ַƫ����:0x34C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ�ÿ��ƼĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_pmu_vol_addr2 : 10; /* bit[0-9]  : G3D PMUSSI���õ�ַ����ӦG3D��������� */
        unsigned int  reserved_0        : 6;  /* bit[10-15]: ������ */
        unsigned int  g3d_pmu_vol_addr3 : 10; /* bit[16-25]: G3D PMUSSI���õ�ַ����ӦG3D��ѹ������ */
        unsigned int  reserved_1        : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_PMCTRL_PERI_CTRL3_UNION;
#endif
#define SOC_PMCTRL_PERI_CTRL3_g3d_pmu_vol_addr2_START  (0)
#define SOC_PMCTRL_PERI_CTRL3_g3d_pmu_vol_addr2_END    (9)
#define SOC_PMCTRL_PERI_CTRL3_g3d_pmu_vol_addr3_START  (16)
#define SOC_PMCTRL_PERI_CTRL3_g3d_pmu_vol_addr3_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_CTRL4_UNION
 �ṹ˵��  : PERI_CTRL4 �Ĵ����ṹ���塣��ַƫ����:0x350����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ�ÿ��ƼĴ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0: 16; /* bit[0-15] : ������ */
        unsigned int  reserved_1: 16; /* bit[16-31]: ������ */
    } reg;
} SOC_PMCTRL_PERI_CTRL4_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_CTRL5_UNION
 �ṹ˵��  : PERI_CTRL5 �Ĵ����ṹ���塣��ַƫ����:0x354����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ�ÿ��ƼĴ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_PMCTRL_PERI_CTRL5_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_CTRL6_UNION
 �ṹ˵��  : PERI_CTRL6 �Ĵ����ṹ���塣��ַƫ����:0x358����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ�ÿ��ƼĴ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_PMCTRL_PERI_CTRL6_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_CTRL7_UNION
 �ṹ˵��  : PERI_CTRL7 �Ĵ����ṹ���塣��ַƫ����:0x35C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ�ÿ��ƼĴ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_PMCTRL_PERI_CTRL7_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_STAT0_UNION
 �ṹ˵��  : PERI_STAT0 �Ĵ����ṹ���塣��ַƫ����:0x360����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��״̬�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_info_ddrc : 32; /* bit[0-31]: debug״̬�� */
    } reg;
} SOC_PMCTRL_PERI_STAT0_UNION;
#endif
#define SOC_PMCTRL_PERI_STAT0_dbg_info_ddrc_START  (0)
#define SOC_PMCTRL_PERI_STAT0_dbg_info_ddrc_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_STAT1_UNION
 �ṹ˵��  : PERI_STAT1 �Ĵ����ṹ���塣��ַƫ����:0x364����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��״̬�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_info_cssys : 32; /* bit[0-31]: debug״̬�� */
    } reg;
} SOC_PMCTRL_PERI_STAT1_UNION;
#endif
#define SOC_PMCTRL_PERI_STAT1_dbg_info_cssys_START  (0)
#define SOC_PMCTRL_PERI_STAT1_dbg_info_cssys_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_STAT2_UNION
 �ṹ˵��  : PERI_STAT2 �Ĵ����ṹ���塣��ַƫ����:0x368����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��״̬�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_info_ssi : 32; /* bit[0-31]: debug״̬�� */
    } reg;
} SOC_PMCTRL_PERI_STAT2_UNION;
#endif
#define SOC_PMCTRL_PERI_STAT2_dbg_info_ssi_START  (0)
#define SOC_PMCTRL_PERI_STAT2_dbg_info_ssi_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_STAT3_UNION
 �ṹ˵��  : PERI_STAT3 �Ĵ����ṹ���塣��ַƫ����:0x36C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��״̬�Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_info_i2c : 32; /* bit[0-31]: debug״̬�� */
    } reg;
} SOC_PMCTRL_PERI_STAT3_UNION;
#endif
#define SOC_PMCTRL_PERI_STAT3_dbg_info_i2c_START  (0)
#define SOC_PMCTRL_PERI_STAT3_dbg_info_i2c_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_STAT4_UNION
 �ṹ˵��  : PERI_STAT4 �Ĵ����ṹ���塣��ַƫ����:0x370����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��״̬�Ĵ���4��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  dbg_info_ssi1 : 32; /* bit[0-31]: debug״̬�� */
    } reg;
} SOC_PMCTRL_PERI_STAT4_UNION;
#endif
#define SOC_PMCTRL_PERI_STAT4_dbg_info_ssi1_START  (0)
#define SOC_PMCTRL_PERI_STAT4_dbg_info_ssi1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_STAT5_UNION
 �ṹ˵��  : PERI_STAT5 �Ĵ����ṹ���塣��ַƫ����:0x374����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��״̬�Ĵ���5��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  svfd_test_out_0     : 4;  /* bit[0-3]  : Ԥ����������� */
        unsigned int  svfd_test_out_1     : 4;  /* bit[4-7]  : Ԥ����������� */
        unsigned int  svfd_test_out_2     : 4;  /* bit[8-11] : Ԥ����������� */
        unsigned int  svfd_match_result_0 : 1;  /* bit[12-12]: ƥ��������1Ϊͨ��������DFT����ɸѡ�� */
        unsigned int  svfd_match_result_1 : 1;  /* bit[13-13]: ƥ��������1Ϊͨ��������DFT����ɸѡ�� */
        unsigned int  svfd_match_result_2 : 1;  /* bit[14-14]: ƥ��������1Ϊͨ��������DFT����ɸѡ�� */
        unsigned int  reserved            : 17; /* bit[15-31]: ������ */
    } reg;
} SOC_PMCTRL_PERI_STAT5_UNION;
#endif
#define SOC_PMCTRL_PERI_STAT5_svfd_test_out_0_START      (0)
#define SOC_PMCTRL_PERI_STAT5_svfd_test_out_0_END        (3)
#define SOC_PMCTRL_PERI_STAT5_svfd_test_out_1_START      (4)
#define SOC_PMCTRL_PERI_STAT5_svfd_test_out_1_END        (7)
#define SOC_PMCTRL_PERI_STAT5_svfd_test_out_2_START      (8)
#define SOC_PMCTRL_PERI_STAT5_svfd_test_out_2_END        (11)
#define SOC_PMCTRL_PERI_STAT5_svfd_match_result_0_START  (12)
#define SOC_PMCTRL_PERI_STAT5_svfd_match_result_0_END    (12)
#define SOC_PMCTRL_PERI_STAT5_svfd_match_result_1_START  (13)
#define SOC_PMCTRL_PERI_STAT5_svfd_match_result_1_END    (13)
#define SOC_PMCTRL_PERI_STAT5_svfd_match_result_2_START  (14)
#define SOC_PMCTRL_PERI_STAT5_svfd_match_result_2_END    (14)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_STAT6_UNION
 �ṹ˵��  : PERI_STAT6 �Ĵ����ṹ���塣��ַƫ����:0x378����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��״̬�Ĵ���6��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_cpm_data : 16; /* bit[0-15] : Cluster1��cpm ���֡� */
        unsigned int  cluster0_cpm_data : 16; /* bit[16-31]: Cluster0��cpm ���֡� */
    } reg;
} SOC_PMCTRL_PERI_STAT6_UNION;
#endif
#define SOC_PMCTRL_PERI_STAT6_cluster1_cpm_data_START  (0)
#define SOC_PMCTRL_PERI_STAT6_cluster1_cpm_data_END    (15)
#define SOC_PMCTRL_PERI_STAT6_cluster0_cpm_data_START  (16)
#define SOC_PMCTRL_PERI_STAT6_cluster0_cpm_data_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_STAT7_UNION
 �ṹ˵��  : PERI_STAT7 �Ĵ����ṹ���塣��ַƫ����:0x37C����ֵ:0x00000000�����:32
 �Ĵ���˵��: ����ͨ��״̬�Ĵ���7��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_cpm_data_vld       : 1;  /* bit[0-0]  : Cluster0 cpm���ֵ�VLD�źš� */
        unsigned int  cluster1_cpm_data_vld       : 1;  /* bit[1-1]  : Cluster1 cpm���ֵ�VLD�źš� */
        unsigned int  g3d_cpm_data_vld            : 1;  /* bit[2-2]  : GPU cpm���ֵ�VLD�źš� */
        unsigned int  reserved_0                  : 1;  /* bit[3-3]  : ������ */
        unsigned int  cluster0_svfd_glitch_result : 1;  /* bit[4-4]  : Cluster0 svfd glitch������� */
        unsigned int  cluster1_svfd_glitch_result : 1;  /* bit[5-5]  : Cluster1 svfd glitch������� */
        unsigned int  g3d_svfd_glitch_result      : 1;  /* bit[6-6]  : GPU svfd glitch������� */
        unsigned int  reserved_1                  : 9;  /* bit[7-15] : ������ */
        unsigned int  g3d_cpm_data                : 16; /* bit[16-31]: GPU��cpm ���֡� */
    } reg;
} SOC_PMCTRL_PERI_STAT7_UNION;
#endif
#define SOC_PMCTRL_PERI_STAT7_cluster0_cpm_data_vld_START        (0)
#define SOC_PMCTRL_PERI_STAT7_cluster0_cpm_data_vld_END          (0)
#define SOC_PMCTRL_PERI_STAT7_cluster1_cpm_data_vld_START        (1)
#define SOC_PMCTRL_PERI_STAT7_cluster1_cpm_data_vld_END          (1)
#define SOC_PMCTRL_PERI_STAT7_g3d_cpm_data_vld_START             (2)
#define SOC_PMCTRL_PERI_STAT7_g3d_cpm_data_vld_END               (2)
#define SOC_PMCTRL_PERI_STAT7_cluster0_svfd_glitch_result_START  (4)
#define SOC_PMCTRL_PERI_STAT7_cluster0_svfd_glitch_result_END    (4)
#define SOC_PMCTRL_PERI_STAT7_cluster1_svfd_glitch_result_START  (5)
#define SOC_PMCTRL_PERI_STAT7_cluster1_svfd_glitch_result_END    (5)
#define SOC_PMCTRL_PERI_STAT7_g3d_svfd_glitch_result_START       (6)
#define SOC_PMCTRL_PERI_STAT7_g3d_svfd_glitch_result_END         (6)
#define SOC_PMCTRL_PERI_STAT7_g3d_cpm_data_START                 (16)
#define SOC_PMCTRL_PERI_STAT7_g3d_cpm_data_END                   (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_NOC_POWER_IDLEREQ_UNION
 �ṹ˵��  : NOC_POWER_IDLEREQ �Ĵ����ṹ���塣��ַƫ����:0x380����ֵ:0x00002C38�����:32
 �Ĵ���˵��: NOC�͹��������źżĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  ddrphy_bypass_mode        : 1;  /* bit[0-0]  : DDRPHY����ģʽ��
                                                                     0����bypassģʽ��
                                                                     1��bypassģʽ�� */
        unsigned int  noc_mmc0bus_power_idlereq : 1;  /* bit[1-1]  : noc�͹��������źš�
                                                                     0������noc�˳��͹���ģʽ��
                                                                     1������noc����͹���ģʽ�� */
        unsigned int  noc_mmc1bus_power_idlereq : 1;  /* bit[2-2]  : noc�͹��������źš�
                                                                     0������noc�˳��͹���ģʽ��
                                                                     1������noc����͹���ģʽ�� */
        unsigned int  noc_modem_power_idlereq   : 1;  /* bit[3-3]  : noc�͹��������źš�
                                                                     0������noc�˳��͹���ģʽ��
                                                                     1������noc����͹���ģʽ�� */
        unsigned int  noc_vcodec_power_idlereq  : 1;  /* bit[4-4]  : noc�͹��������ź�
                                                                     0������noc�˳��͹���ģʽ��
                                                                     1������noc����͹���ģʽ�� */
        unsigned int  noc_isp_power_idlereq     : 1;  /* bit[5-5]  : noc�͹��������źš�
                                                                     0������noc�˳��͹���ģʽ��
                                                                     1������noc����͹���ģʽ�� */
        unsigned int  noc_sysbus_power_idlereq  : 1;  /* bit[6-6]  : noc�͹��������źš�
                                                                     0������noc�˳��͹���ģʽ��
                                                                     1������noc����͹���ģʽ�� */
        unsigned int  noc_cfgbus_power_idlereq  : 1;  /* bit[7-7]  : noc�͹��������źš�
                                                                     0������noc�˳��͹���ģʽ��
                                                                     1������noc����͹���ģʽ�� */
        unsigned int  noc_dmabus_power_idlereq  : 1;  /* bit[8-8]  : noc�͹��������źš�
                                                                     0������noc�˳��͹���ģʽ��
                                                                     1������noc����͹���ģʽ�� */
        unsigned int  noc_dbgbus_power_idlereq  : 1;  /* bit[9-9]  : noc�͹��������źš�
                                                                     0������noc�˳��͹���ģʽ��
                                                                     1������noc����͹���ģʽ�� */
        unsigned int  noc_vdec_power_idlereq    : 1;  /* bit[10-10]: noc�͹��������źš�
                                                                     0������noc�˳��͹���ģʽ��
                                                                     1������noc����͹���ģʽ�� */
        unsigned int  noc_venc_power_idlereq    : 1;  /* bit[11-11]: noc�͹��������źš�
                                                                     0������noc�˳��͹���ģʽ��
                                                                     1������noc����͹���ģʽ�� */
        unsigned int  reserved_0                : 1;  /* bit[12-12]: reserved�� */
        unsigned int  noc_dss_power_idlereq     : 1;  /* bit[13-13]: noc�͹��������źš�
                                                                     0������noc�˳��͹���ģʽ��
                                                                     1������noc����͹���ģʽ�� */
        unsigned int  reserved_1                : 2;  /* bit[14-15]: reserved�� */
        unsigned int  biten                     : 16; /* bit[16-31]: ÿ������λ��ʹ��λ��
                                                                     ֻ�е�biten��Ӧ�ı���λΪ1'b1����Ӧ�ı���λ�������á�biten[0]����bit 0��ʹ��λ��д1��Ч�� */
    } reg;
} SOC_PMCTRL_NOC_POWER_IDLEREQ_UNION;
#endif
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_ddrphy_bypass_mode_START         (0)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_ddrphy_bypass_mode_END           (0)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_mmc0bus_power_idlereq_START  (1)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_mmc0bus_power_idlereq_END    (1)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_mmc1bus_power_idlereq_START  (2)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_mmc1bus_power_idlereq_END    (2)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_modem_power_idlereq_START    (3)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_modem_power_idlereq_END      (3)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_vcodec_power_idlereq_START   (4)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_vcodec_power_idlereq_END     (4)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_isp_power_idlereq_START      (5)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_isp_power_idlereq_END        (5)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_sysbus_power_idlereq_START   (6)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_sysbus_power_idlereq_END     (6)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_cfgbus_power_idlereq_START   (7)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_cfgbus_power_idlereq_END     (7)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_dmabus_power_idlereq_START   (8)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_dmabus_power_idlereq_END     (8)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_dbgbus_power_idlereq_START   (9)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_dbgbus_power_idlereq_END     (9)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_vdec_power_idlereq_START     (10)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_vdec_power_idlereq_END       (10)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_venc_power_idlereq_START     (11)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_venc_power_idlereq_END       (11)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_dss_power_idlereq_START      (13)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_noc_dss_power_idlereq_END        (13)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_biten_START                      (16)
#define SOC_PMCTRL_NOC_POWER_IDLEREQ_biten_END                        (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_NOC_POWER_IDLEACK_UNION
 �ṹ˵��  : NOC_POWER_IDLEACK �Ĵ����ṹ���塣��ַƫ����:0x384����ֵ:0x00000000�����:32
 �Ĵ���˵��: NOC�͹�����Ӧ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0                : 1;  /* bit[0-0]  : ������ */
        unsigned int  noc_mmc0bus_power_idleack : 1;  /* bit[1-1]  : noc���ڵ͹����������Ӧ��
                                                                     0����������noc�˳��͹���ģʽ����Ӧ��
                                                                     1����������noc����͹���ģʽ����Ӧ�� */
        unsigned int  noc_mmc1bus_power_idleack : 1;  /* bit[2-2]  : noc���ڵ͹����������Ӧ��
                                                                     0����������noc�˳��͹���ģʽ����Ӧ��
                                                                     1����������noc����͹���ģʽ����Ӧ�� */
        unsigned int  noc_modem_power_idleack   : 1;  /* bit[3-3]  : noc���ڵ͹����������Ӧ��
                                                                     0����������noc�˳��͹���ģʽ����Ӧ��
                                                                     1����������noc����͹���ģʽ����Ӧ�� */
        unsigned int  noc_vcodec_power_idleack  : 1;  /* bit[4-4]  : noc���ڵ͹����������Ӧ��
                                                                     0����������noc�˳��͹���ģʽ����Ӧ��
                                                                     1����������noc����͹���ģʽ����Ӧ�� */
        unsigned int  noc_isp_power_idleack     : 1;  /* bit[5-5]  : noc���ڵ͹����������Ӧ��
                                                                     0����������noc�˳��͹���ģʽ����Ӧ��
                                                                     1����������noc����͹���ģʽ����Ӧ�� */
        unsigned int  noc_sysbus_power_idleack  : 1;  /* bit[6-6]  : noc���ڵ͹����������Ӧ��
                                                                     0����������noc�˳��͹���ģʽ����Ӧ��
                                                                     1����������noc����͹���ģʽ����Ӧ�� */
        unsigned int  noc_cfgbus_power_idleack  : 1;  /* bit[7-7]  : noc���ڵ͹����������Ӧ��
                                                                     0����������noc�˳��͹���ģʽ����Ӧ��
                                                                     1����������noc����͹���ģʽ����Ӧ�� */
        unsigned int  noc_dmabus_power_idleack  : 1;  /* bit[8-8]  : noc���ڵ͹����������Ӧ��
                                                                     0����������noc�˳��͹���ģʽ����Ӧ��
                                                                     1����������noc����͹���ģʽ����Ӧ�� */
        unsigned int  noc_dbgbus_power_idleack  : 1;  /* bit[9-9]  : noc���ڵ͹����������Ӧ��
                                                                     0����������noc�˳��͹���ģʽ����Ӧ��
                                                                     1����������noc����͹���ģʽ����Ӧ�� */
        unsigned int  noc_vdec_power_idleack    : 1;  /* bit[10-10]: noc���ڵ͹����������Ӧ��
                                                                     0����������noc�˳��͹���ģʽ����Ӧ��
                                                                     1����������noc����͹���ģʽ����Ӧ�� */
        unsigned int  noc_venc_power_idleack    : 1;  /* bit[11-11]: noc���ڵ͹����������Ӧ��
                                                                     0����������noc�˳��͹���ģʽ����Ӧ��
                                                                     1����������noc����͹���ģʽ����Ӧ�� */
        unsigned int  reserved_1                : 1;  /* bit[12-12]: reserved�� */
        unsigned int  noc_dss_power_idleack     : 1;  /* bit[13-13]: noc���ڵ͹����������Ӧ��
                                                                     0����������noc�˳��͹���ģʽ����Ӧ��
                                                                     1����������noc����͹���ģʽ����Ӧ�� */
        unsigned int  reserved_2                : 18; /* bit[14-31]: ������ */
    } reg;
} SOC_PMCTRL_NOC_POWER_IDLEACK_UNION;
#endif
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_mmc0bus_power_idleack_START  (1)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_mmc0bus_power_idleack_END    (1)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_mmc1bus_power_idleack_START  (2)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_mmc1bus_power_idleack_END    (2)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_modem_power_idleack_START    (3)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_modem_power_idleack_END      (3)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_vcodec_power_idleack_START   (4)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_vcodec_power_idleack_END     (4)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_isp_power_idleack_START      (5)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_isp_power_idleack_END        (5)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_sysbus_power_idleack_START   (6)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_sysbus_power_idleack_END     (6)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_cfgbus_power_idleack_START   (7)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_cfgbus_power_idleack_END     (7)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_dmabus_power_idleack_START   (8)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_dmabus_power_idleack_END     (8)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_dbgbus_power_idleack_START   (9)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_dbgbus_power_idleack_END     (9)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_vdec_power_idleack_START     (10)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_vdec_power_idleack_END       (10)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_venc_power_idleack_START     (11)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_venc_power_idleack_END       (11)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_dss_power_idleack_START      (13)
#define SOC_PMCTRL_NOC_POWER_IDLEACK_noc_dss_power_idleack_END        (13)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_NOC_POWER_IDLE_UNION
 �ṹ˵��  : NOC_POWER_IDLE �Ĵ����ṹ���塣��ַƫ����:0x388����ֵ:0x00000000�����:32
 �Ĵ���˵��: NOC�͹���״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved_0             : 1;  /* bit[0-0]  : ������ */
        unsigned int  noc_mmc0bus_power_idle : 1;  /* bit[1-1]  : noc����͹���ģʽ��״ָ̬ʾ��
                                                                  0����������noc�˳��͹���ģʽ��״ָ̬ʾ��
                                                                  1����������noc����͹���ģʽ��״ָ̬ʾ�� */
        unsigned int  noc_mmc1bus_power_idle : 1;  /* bit[2-2]  : noc����͹���ģʽ��״ָ̬ʾ��
                                                                  0����������noc�˳��͹���ģʽ��״ָ̬ʾ��
                                                                  1����������noc����͹���ģʽ��״ָ̬ʾ�� */
        unsigned int  noc_modem_power_idle   : 1;  /* bit[3-3]  : noc����͹���ģʽ��״ָ̬ʾ��
                                                                  0����������noc�˳��͹���ģʽ��״ָ̬ʾ��
                                                                  1����������noc����͹���ģʽ��״ָ̬ʾ�� */
        unsigned int  noc_vcodec_power_idle  : 1;  /* bit[4-4]  : noc����͹���ģʽ��״ָ̬ʾ��
                                                                  0����������noc�˳��͹���ģʽ��״ָ̬ʾ��
                                                                  1����������noc����͹���ģʽ��״ָ̬ʾ�� */
        unsigned int  noc_isp_power_idle     : 1;  /* bit[5-5]  : noc����͹���ģʽ��״ָ̬ʾ��
                                                                  0����������noc�˳��͹���ģʽ��״ָ̬ʾ��
                                                                  1����������noc����͹���ģʽ��״ָ̬ʾ�� */
        unsigned int  noc_sysbus_power_idle  : 1;  /* bit[6-6]  : noc����͹���ģʽ��״ָ̬ʾ��
                                                                  0����������noc�˳��͹���ģʽ��״ָ̬ʾ��
                                                                  1����������noc����͹���ģʽ��״ָ̬ʾ�� */
        unsigned int  noc_cfgbus_power_idle  : 1;  /* bit[7-7]  : noc����͹���ģʽ��״ָ̬ʾ��
                                                                  0����������noc�˳��͹���ģʽ��״ָ̬ʾ��
                                                                  1����������noc����͹���ģʽ��״ָ̬ʾ�� */
        unsigned int  noc_dmabus_power_idle  : 1;  /* bit[8-8]  : noc����͹���ģʽ��״ָ̬ʾ��
                                                                  0����������noc�˳��͹���ģʽ��״ָ̬ʾ��
                                                                  1����������noc����͹���ģʽ��״ָ̬ʾ�� */
        unsigned int  noc_dbgbus_power_idle  : 1;  /* bit[9-9]  : noc����͹���ģʽ��״ָ̬ʾ��
                                                                  0����������noc�˳��͹���ģʽ��״ָ̬ʾ��
                                                                  1����������noc����͹���ģʽ��״ָ̬ʾ�� */
        unsigned int  noc_vdec_power_idle    : 1;  /* bit[10-10]: noc����͹���ģʽ��״ָ̬ʾ��
                                                                  0����������noc�˳��͹���ģʽ��״ָ̬ʾ��
                                                                  1����������noc����͹���ģʽ��״ָ̬ʾ�� */
        unsigned int  noc_venc_power_idle    : 1;  /* bit[11-11]: noc����͹���ģʽ��״ָ̬ʾ��
                                                                  0����������noc�˳��͹���ģʽ��״ָ̬ʾ��
                                                                  1����������noc����͹���ģʽ��״ָ̬ʾ�� */
        unsigned int  reserved_1             : 1;  /* bit[12-12]: ������ */
        unsigned int  noc_dss_power_idle     : 1;  /* bit[13-13]: noc����͹���ģʽ��״ָ̬ʾ��
                                                                  0����������noc�˳��͹���ģʽ��״ָ̬ʾ��
                                                                  1����������noc����͹���ģʽ��״ָ̬ʾ�� */
        unsigned int  reserved_2             : 18; /* bit[14-31]: ������ */
    } reg;
} SOC_PMCTRL_NOC_POWER_IDLE_UNION;
#endif
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_mmc0bus_power_idle_START  (1)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_mmc0bus_power_idle_END    (1)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_mmc1bus_power_idle_START  (2)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_mmc1bus_power_idle_END    (2)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_modem_power_idle_START    (3)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_modem_power_idle_END      (3)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_vcodec_power_idle_START   (4)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_vcodec_power_idle_END     (4)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_isp_power_idle_START      (5)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_isp_power_idle_END        (5)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_sysbus_power_idle_START   (6)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_sysbus_power_idle_END     (6)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_cfgbus_power_idle_START   (7)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_cfgbus_power_idle_END     (7)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_dmabus_power_idle_START   (8)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_dmabus_power_idle_END     (8)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_dbgbus_power_idle_START   (9)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_dbgbus_power_idle_END     (9)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_vdec_power_idle_START     (10)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_vdec_power_idle_END       (10)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_venc_power_idle_START     (11)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_venc_power_idle_END       (11)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_dss_power_idle_START      (13)
#define SOC_PMCTRL_NOC_POWER_IDLE_noc_dss_power_idle_END        (13)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_INT0_MASK_UNION
 �ṹ˵��  : PERI_INT0_MASK �Ĵ����ṹ���塣��ַƫ����:0x3A0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����ж����μĴ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  noc_maintimeout_mask : 25; /* bit[0-24] : NOC target�˿ڼ�����ʱ�����źţ�
                                                                0�������μ�����ʱ�źţ�
                                                                1�����μ�����ʱ�źš� */
        unsigned int  reserved             : 7;  /* bit[25-31]: ������ */
    } reg;
} SOC_PMCTRL_PERI_INT0_MASK_UNION;
#endif
#define SOC_PMCTRL_PERI_INT0_MASK_noc_maintimeout_mask_START  (0)
#define SOC_PMCTRL_PERI_INT0_MASK_noc_maintimeout_mask_END    (24)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_INT0_STAT_UNION
 �ṹ˵��  : PERI_INT0_STAT �Ĵ����ṹ���塣��ַƫ����:0x3A4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����ж�״̬�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  noc_gic_t_maintimeout               : 1;  /* bit[0-0]  : NOC target�˿ڼ�����ʱ�źţ�����ʱ�ź�Ϊ��ʱ����ʾmaster����slaverû��Ӧ��slaver�ѹ����� */
        unsigned int  noc_hkadc_ssi_t_maintimeout         : 1;  /* bit[1-1]  : NOC target�˿ڼ�����ʱ�źţ�����ʱ�ź�Ϊ��ʱ����ʾmaster����slaverû��Ӧ��slaver�ѹ����� */
        unsigned int  reserved_0                          : 1;  /* bit[2-2]  : ������ */
        unsigned int  noc_lpm3_slv_t_maintimeout          : 1;  /* bit[3-3]  : NOC target�˿ڼ�����ʱ�źţ�����ʱ�ź�Ϊ��ʱ����ʾmaster����slaverû��Ӧ��slaver�ѹ����� */
        unsigned int  noc_sys_peri0_cfg_t_maintimeout     : 1;  /* bit[4-4]  : NOC target�˿ڼ�����ʱ�źţ�����ʱ�ź�Ϊ��ʱ����ʾmaster����slaverû��Ӧ��slaver�ѹ����� */
        unsigned int  noc_sys_peri1_cfg_t_maintimeout     : 1;  /* bit[5-5]  : NOC target�˿ڼ�����ʱ�źţ�����ʱ�ź�Ϊ��ʱ����ʾmaster����slaverû��Ӧ��slaver�ѹ����� */
        unsigned int  noc_sys_peri2_cfg_t_maintimeout     : 1;  /* bit[6-6]  : NOC target�˿ڼ�����ʱ�źţ�����ʱ�ź�Ϊ��ʱ����ʾmaster����slaverû��Ӧ��slaver�ѹ����� */
        unsigned int  noc_sys_peri3_cfg_t_maintimeout     : 1;  /* bit[7-7]  : NOC target�˿ڼ�����ʱ�źţ�����ʱ�ź�Ϊ��ʱ����ʾmaster����slaverû��Ӧ��slaver�ѹ����� */
        unsigned int  reserved_1                          : 1;  /* bit[8-8]  : ������ */
        unsigned int  noc_dmac_cfg_t_maintimeout          : 1;  /* bit[9-9]  : NOC target�˿ڼ�����ʱ�źţ�����ʱ�ź�Ϊ��ʱ����ʾmaster����slaverû��Ӧ��slaver�ѹ����� */
        unsigned int  reserved_2                          : 2;  /* bit[10-11]: ������ */
        unsigned int  reserved_3                          : 1;  /* bit[12-12]: reserved�� */
        unsigned int  noc_top_cssys_slv_cfg_t_maintimeout : 1;  /* bit[13-13]: NOC target�˿ڼ�����ʱ�źţ�����ʱ�ź�Ϊ��ʱ����ʾmaster����slaverû��Ӧ��slaver�ѹ����� */
        unsigned int  reserved_4                          : 1;  /* bit[14-14]: ������ */
        unsigned int  noc_modem_bus_cfg_t_maintimeout     : 1;  /* bit[15-15]: NOC target�˿ڼ�����ʱ�źţ�����ʱ�ź�Ϊ��ʱ����ʾmaster����slaverû��Ӧ��slaver�ѹ����� */
        unsigned int  reserved_5                          : 1;  /* bit[16-16]: reserved�� */
        unsigned int  noc_emmc0_cfg_t_maintimeout         : 1;  /* bit[17-17]: NOC target�˿ڼ�����ʱ�źţ�����ʱ�ź�Ϊ��ʱ����ʾmaster����slaverû��Ӧ��slaver�ѹ����� */
        unsigned int  reserved_6                          : 2;  /* bit[18-19]: reserved�� */
        unsigned int  noc_sys2hkmem_t_maintimeout         : 1;  /* bit[20-20]: NOC target�˿ڼ�����ʱ�źţ�����ʱ�ź�Ϊ��ʱ����ʾmaster����slaverû��Ӧ��slaver�ѹ����� */
        unsigned int  noc_emmc1bus_apb_cfg_t_maintimeout  : 1;  /* bit[21-21]: NOC target�˿ڼ�����ʱ�źţ�����ʱ�ź�Ϊ��ʱ����ʾmaster����slaverû��Ӧ��slaver�ѹ����� */
        unsigned int  noc_debug_ahb_cfg_t_maintimeout     : 1;  /* bit[22-22]: debug ��ϵͳ�� ���ÿ��źš� */
        unsigned int  noc_cfg2vivo_t_maintimeout          : 1;  /* bit[23-23]: NOC target�˿ڼ�����ʱ�źţ�����ʱ�ź�Ϊ��ʱ����ʾmaster����slaverû��Ӧ��slaver�ѹ����� */
        unsigned int  noc_debug_apb_cfg_t_maintimeout     : 1;  /* bit[24-24]: NOC target�˿ڼ�����ʱ�źţ�����ʱ�ź�Ϊ��ʱ����ʾmaster����slaverû��Ӧ��slaver�ѹ����� */
        unsigned int  noc_cci_cfg_t_maintimeout           : 1;  /* bit[25-25]: cci ���ߵ����ÿ��źš� */
        unsigned int  reserved_7                          : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_PMCTRL_PERI_INT0_STAT_UNION;
#endif
#define SOC_PMCTRL_PERI_INT0_STAT_noc_gic_t_maintimeout_START                (0)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_gic_t_maintimeout_END                  (0)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_hkadc_ssi_t_maintimeout_START          (1)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_hkadc_ssi_t_maintimeout_END            (1)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_lpm3_slv_t_maintimeout_START           (3)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_lpm3_slv_t_maintimeout_END             (3)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_sys_peri0_cfg_t_maintimeout_START      (4)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_sys_peri0_cfg_t_maintimeout_END        (4)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_sys_peri1_cfg_t_maintimeout_START      (5)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_sys_peri1_cfg_t_maintimeout_END        (5)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_sys_peri2_cfg_t_maintimeout_START      (6)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_sys_peri2_cfg_t_maintimeout_END        (6)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_sys_peri3_cfg_t_maintimeout_START      (7)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_sys_peri3_cfg_t_maintimeout_END        (7)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_dmac_cfg_t_maintimeout_START           (9)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_dmac_cfg_t_maintimeout_END             (9)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_top_cssys_slv_cfg_t_maintimeout_START  (13)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_top_cssys_slv_cfg_t_maintimeout_END    (13)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_modem_bus_cfg_t_maintimeout_START      (15)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_modem_bus_cfg_t_maintimeout_END        (15)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_emmc0_cfg_t_maintimeout_START          (17)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_emmc0_cfg_t_maintimeout_END            (17)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_sys2hkmem_t_maintimeout_START          (20)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_sys2hkmem_t_maintimeout_END            (20)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_emmc1bus_apb_cfg_t_maintimeout_START   (21)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_emmc1bus_apb_cfg_t_maintimeout_END     (21)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_debug_ahb_cfg_t_maintimeout_START      (22)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_debug_ahb_cfg_t_maintimeout_END        (22)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_cfg2vivo_t_maintimeout_START           (23)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_cfg2vivo_t_maintimeout_END             (23)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_debug_apb_cfg_t_maintimeout_START      (24)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_debug_apb_cfg_t_maintimeout_END        (24)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_cci_cfg_t_maintimeout_START            (25)
#define SOC_PMCTRL_PERI_INT0_STAT_noc_cci_cfg_t_maintimeout_END              (25)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_INT1_MASK_UNION
 �ṹ˵��  : PERI_INT1_MASK �Ĵ����ṹ���塣��ַƫ����:0x3A8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����ж����μĴ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_PMCTRL_PERI_INT1_MASK_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_INT1_STAT_UNION
 �ṹ˵��  : PERI_INT1_STAT �Ĵ����ṹ���塣��ַƫ����:0x3AC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����ж����μĴ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_PMCTRL_PERI_INT1_STAT_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_INT2_MASK_UNION
 �ṹ˵��  : PERI_INT2_MASK �Ĵ����ṹ���塣��ַƫ����:0x3B0����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����ж����μĴ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_PMCTRL_PERI_INT2_MASK_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_INT2_STAT_UNION
 �ṹ˵��  : PERI_INT2_STAT �Ĵ����ṹ���塣��ַƫ����:0x3B4����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����ж�״̬�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_PMCTRL_PERI_INT2_STAT_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_INT3_MASK_UNION
 �ṹ˵��  : PERI_INT3_MASK �Ĵ����ṹ���塣��ַƫ����:0x3B8����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����ж�״̬�Ĵ���2��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_PMCTRL_PERI_INT3_MASK_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERI_INT3_STAT_UNION
 �ṹ˵��  : PERI_INT3_STAT �Ĵ����ṹ���塣��ַƫ����:0x3BC����ֵ:0x00000000�����:32
 �Ĵ���˵��: �����ж�״̬�Ĵ���3��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  reserved : 32; /* bit[0-31]: ������ */
    } reg;
} SOC_PMCTRL_PERI_INT3_STAT_UNION;
#endif


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_CTRL_EN_0_UNION
 �ṹ˵��  : VS_CTRL_EN_0 �Ĵ����ṹ���塣��ַƫ����:0x3D0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor����ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_ctrl_en_0 : 1;  /* bit[0-0] : Cluster0 Vsensor����ʹ�ܡ�
                                                       0��Vsensor��ʹ�ܣ�
                                                       1��Vsensorʹ�ܡ� */
        unsigned int  reserved     : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_CTRL_EN_0_UNION;
#endif
#define SOC_PMCTRL_VS_CTRL_EN_0_vs_ctrl_en_0_START  (0)
#define SOC_PMCTRL_VS_CTRL_EN_0_vs_ctrl_en_0_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_CTRL_BYPASS_0_UNION
 �ṹ˵��  : VS_CTRL_BYPASS_0 �Ĵ����ṹ���塣��ַƫ����:0x3D4����ֵ:0x00000001�����:32
 �Ĵ���˵��: Vsensor bypass�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_ctrl_bypass_0 : 1;  /* bit[0-0] : Cluster0 Vsensor bypass�źš�
                                                           0��Vsensor�����߼�����ſ��źſ���ICG��
                                                           1��Vsensor�����߼�bypass���ſ��ź�һֱΪ1�� */
        unsigned int  reserved         : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_CTRL_BYPASS_0_UNION;
#endif
#define SOC_PMCTRL_VS_CTRL_BYPASS_0_vs_ctrl_bypass_0_START  (0)
#define SOC_PMCTRL_VS_CTRL_BYPASS_0_vs_ctrl_bypass_0_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_CTRL_0_UNION
 �ṹ˵��  : VS_CTRL_0 �Ĵ����ṹ���塣��ַƫ����:0x3D8����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor�������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_mod_cluster0                    : 1;  /* bit[0-0]  : Cluster0 Vsensorģʽ��
                                                                              0�����ж�ģʽ��
                                                                              1���ж�ģʽ�� */
        unsigned int  cluster0_cpu0_wfi_wfe_bypass       : 1;  /* bit[1-1]  : CPU0 WFI/WFE����������bypass��
                                                                              1'b1:bypass;
                                                                              1'b0:ʹ�ܡ� */
        unsigned int  cluster0_cpu1_wfi_wfe_bypass       : 1;  /* bit[2-2]  : CPU1 WFI/WFE����������bypass��
                                                                              1'b1:bypass;
                                                                              1'b0:ʹ�ܡ� */
        unsigned int  cluster0_cpu2_wfi_wfe_bypass       : 1;  /* bit[3-3]  : CPU2 WFI/WFE����������bypass��
                                                                              1'b1:bypass;
                                                                              1'b0:ʹ�ܡ� */
        unsigned int  cluster0_cpu3_wfi_wfe_bypass       : 1;  /* bit[4-4]  : CPU3 WFI/WFE����������bypass��
                                                                              1'b1:bypass;
                                                                              1'b0:ʹ�ܡ� */
        unsigned int  cluster0_l2_idle_div_mod           : 2;  /* bit[5-6]  : l2 idle�Զ���Ƶ��Ƶģʽ��
                                                                              00:4��Ƶ��
                                                                              01:8��Ƶ��
                                                                              10:16��Ƶ��
                                                                              11:32��Ƶ�� */
        unsigned int  cluster0_cfg_cnt_cpu_wake_quit     : 8;  /* bit[7-14] : Cluster0 WFI/WFE���������˳���ʱ����������ΪVDM����ʱ�ӡ� */
        unsigned int  cluster0_cfg_cnt_cpu_l2_idle_quit  : 8;  /* bit[15-22]: Cluster0 L2 IDLE���������˳���ʱ����������ΪVDM����ʱ�ӡ� */
        unsigned int  cluster0_cpu_wake_up_mode          : 2;  /* bit[23-24]: Cluster0 WFI/WFE��������ģʽ��
                                                                              2'b00:һ����һ�������˳�WFI/WFE,������������;
                                                                              2'b01:���������������˳�WFI/WFE,������������;
                                                                              2'b10:���������������˳�WFI/WFE,������������;
                                                                              2'b11:�ĸ�ͬʱ�˳�WFI/WFE,�������������� */
        unsigned int  cluster0_cpu_l2_idle_switch_bypass : 1;  /* bit[25]   : Cluster0 �˳�L2������������bypass��
                                                                              1'b1:bypass;
                                                                              1'b0:ʹ�ܡ� */
        unsigned int  cluster0_cpu_l2_idle_gt_en         : 1;  /* bit[26-26]: Cluster0 ����L2 IDLE���Զ���Ƶ����ʹ���źš�
                                                                              1'b0:��ʹ��;
                                                                              1'b1:ʹ�ܣ�����L2 IDLE����Ƶ�����Զ���Ƶģʽ���з�Ƶ�� */
        unsigned int  cluster0_compare_mod               : 2;  /* bit[27-28]: Cluster0���ݱȽ�ģʽ��
                                                                              00�������������ֱ����ref_code�Ƚϣ�
                                                                              01��������32���ۼ�������ref_code�Ƚϣ�
                                                                              10��������64���ۼ�������ref_code�Ƚϣ�
                                                                              11��������128���ۼ�������ref_code�Ƚϡ� */
        unsigned int  sel_ckmux_cluster0_icg             : 1;  /* bit[29]   : ʱ��ѡ��Դͷ��
                                                                              1'b0��CRGֱ�������ʱ�ӣ�
                                                                              1'b1��SVFD�����ʱ�ӡ� */
        unsigned int  reserved                           : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_CTRL_0_UNION;
#endif
#define SOC_PMCTRL_VS_CTRL_0_vs_mod_cluster0_START                     (0)
#define SOC_PMCTRL_VS_CTRL_0_vs_mod_cluster0_END                       (0)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_cpu0_wfi_wfe_bypass_START        (1)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_cpu0_wfi_wfe_bypass_END          (1)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_cpu1_wfi_wfe_bypass_START        (2)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_cpu1_wfi_wfe_bypass_END          (2)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_cpu2_wfi_wfe_bypass_START        (3)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_cpu2_wfi_wfe_bypass_END          (3)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_cpu3_wfi_wfe_bypass_START        (4)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_cpu3_wfi_wfe_bypass_END          (4)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_l2_idle_div_mod_START            (5)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_l2_idle_div_mod_END              (6)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_cfg_cnt_cpu_wake_quit_START      (7)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_cfg_cnt_cpu_wake_quit_END        (14)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_cfg_cnt_cpu_l2_idle_quit_START   (15)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_cfg_cnt_cpu_l2_idle_quit_END     (22)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_cpu_wake_up_mode_START           (23)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_cpu_wake_up_mode_END             (24)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_cpu_l2_idle_switch_bypass_START  (25)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_cpu_l2_idle_switch_bypass_END    (25)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_cpu_l2_idle_gt_en_START          (26)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_cpu_l2_idle_gt_en_END            (26)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_compare_mod_START                (27)
#define SOC_PMCTRL_VS_CTRL_0_cluster0_compare_mod_END                  (28)
#define SOC_PMCTRL_VS_CTRL_0_sel_ckmux_cluster0_icg_START              (29)
#define SOC_PMCTRL_VS_CTRL_0_sel_ckmux_cluster0_icg_END                (29)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_CNT_0_UNION
 �ṹ˵��  : VS_CNT_0 �Ĵ����ṹ���塣��ַƫ����:0x3DC����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor�������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_cnt_quit_0  : 16; /* bit[0-15] : �˳��ſ���ʱ��ÿ�ν����ſغ󣬻�ȴ���Ӧʱ����ٴν��е�ѹ�жϣ����ж�ģʽ���ã��� */
        unsigned int  vs_cnt_enter_0 : 16; /* bit[16-31]: �����ſ���ʱ��ÿ���˳��ſغ󣬻�ȴ���Ӧʱ����ٴν��е�ѹ�жϡ� */
    } reg;
} SOC_PMCTRL_VS_CNT_0_UNION;
#endif
#define SOC_PMCTRL_VS_CNT_0_vs_cnt_quit_0_START   (0)
#define SOC_PMCTRL_VS_CNT_0_vs_cnt_quit_0_END     (15)
#define SOC_PMCTRL_VS_CNT_0_vs_cnt_enter_0_START  (16)
#define SOC_PMCTRL_VS_CNT_0_vs_cnt_enter_0_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_REF_CODE_0_UNION
 �ṹ˵��  : VS_REF_CODE_0 �Ĵ����ṹ���塣��ַƫ����:0x3E0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor�ο����ּĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_vs_ref_code_l : 6;  /* bit[0-5]  : Cluster0�����ſ����֡� */
        unsigned int  cluster0_vs_ref_code_h : 6;  /* bit[6-11] : Cluster0�˳��ſ����֡� */
        unsigned int  cluster0_ext_ref_code  : 7;  /* bit[12-18]: Cluster0 ref_code�ĸ�bit�����ref_code_h��ref_code_lһ��ʹ�ã���compare_mod��ء� */
        unsigned int  reserved               : 13; /* bit[19-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_REF_CODE_0_UNION;
#endif
#define SOC_PMCTRL_VS_REF_CODE_0_cluster0_vs_ref_code_l_START  (0)
#define SOC_PMCTRL_VS_REF_CODE_0_cluster0_vs_ref_code_l_END    (5)
#define SOC_PMCTRL_VS_REF_CODE_0_cluster0_vs_ref_code_h_START  (6)
#define SOC_PMCTRL_VS_REF_CODE_0_cluster0_vs_ref_code_h_END    (11)
#define SOC_PMCTRL_VS_REF_CODE_0_cluster0_ext_ref_code_START   (12)
#define SOC_PMCTRL_VS_REF_CODE_0_cluster0_ext_ref_code_END     (18)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_CALI_CODE_0_UNION
 �ṹ˵��  : VS_CALI_CODE_0 �Ĵ����ṹ���塣��ַƫ����:0x3E4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor��ͷ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_vs_cali_code : 7;  /* bit[0-6] : Cluster0 Vsensor��ͷУ׼���֡� */
        unsigned int  reserved              : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_CALI_CODE_0_UNION;
#endif
#define SOC_PMCTRL_VS_CALI_CODE_0_cluster0_vs_cali_code_START  (0)
#define SOC_PMCTRL_VS_CALI_CODE_0_cluster0_vs_cali_code_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_CODE_0_UNION
 �ṹ˵��  : VS_CODE_0 �Ĵ����ṹ���塣��ַƫ����:0x3E8����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor���ּĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_vs_code : 6;  /* bit[0-5] : Cluster0 Vsensor���֡� */
        unsigned int  reserved         : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_CODE_0_UNION;
#endif
#define SOC_PMCTRL_VS_CODE_0_cluster0_vs_code_START  (0)
#define SOC_PMCTRL_VS_CODE_0_cluster0_vs_code_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_INTSTAT_0_UNION
 �ṹ˵��  : VS_INTSTAT_0 �Ĵ����ṹ���塣��ַƫ����:0x3EC����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor�ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_vdm_stat_0 : 1;  /* bit[0-0] : VDM�ж�״̬���ñ���д1�����VDM�е�intr_vdm�� */
        unsigned int  dll_lock_0      : 1;  /* bit[1-1] : DLL lockָʾ�Ĵ����� */
        unsigned int  reserved        : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_INTSTAT_0_UNION;
#endif
#define SOC_PMCTRL_VS_INTSTAT_0_intr_vdm_stat_0_START  (0)
#define SOC_PMCTRL_VS_INTSTAT_0_intr_vdm_stat_0_END    (0)
#define SOC_PMCTRL_VS_INTSTAT_0_dll_lock_0_START       (1)
#define SOC_PMCTRL_VS_INTSTAT_0_dll_lock_0_END         (1)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_SVFD_CTRL0_0_UNION
 �ṹ˵��  : VS_SVFD_CTRL0_0 �Ĵ����ṹ���塣��ַƫ����:0x3F0����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor�������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  svfd_test_in_0              : 4;  /* bit[0-3]  : Ԥ���������롣 */
        unsigned int  svfd_ulvt_ll_0              : 4;  /* bit[4-7]  : ULVT���߼�������������PIN�� */
        unsigned int  svfd_ulvt_sl_0              : 4;  /* bit[8-11] : ULVT���߼�������������PIN�� */
        unsigned int  svfd_lvt_ll_0               : 4;  /* bit[12-15]: LVT���߼�������������PIN�� */
        unsigned int  svfd_lvt_sl_0               : 4;  /* bit[16-19]: LVT���߼�������������PIN�� */
        unsigned int  svfd_vdm_mode_0             : 2;  /* bit[20-21]: ��ѹ���ģʽѡ��
                                                                       00 :reserve��
                                                                       01 : IP�ڲ���ѹ���(CPM)��
                                                                       10 : IP�ⲿ��ѹ���(VDM)��
                                                                       11 :VDM+CPM�� */
        unsigned int  svfd_match_detect_0         : 1;  /* bit[22-22]: ƥ������ʹ�ܣ�1��Ч��
                                                                       ����״̬��Ҫ����Ϊ0��
                                                                       ����DFT����ɸѡ�� */
        unsigned int  svfd_trim_0                 : 1;  /* bit[23-23]: trim�źš� */
        unsigned int  svfd_d_rate_0               : 2;  /* bit[24-25]: Cluster0 DLL�������ʡ�
                                                                       00 : 10%��
                                                                       01 : 20%��
                                                                       10 : 30%��
                                                                       11 : reseved�� */
        unsigned int  cluster0_svfd_off_mode      : 1;  /* bit[26]   : svfd��Ƶģʽ��
                                                                       1'b0��ֱ�ӽ�Ƶ��
                                                                       1'b1���𼶽�Ƶ�� */
        unsigned int  cluster0_svfd_div64_en      : 1;  /* bit[27]   : ʹ���źţ�����ģʽ����ת�� */
        unsigned int  cluster0_svfd_vdm_period    : 1;  /* bit[28]   : ��ѹ���������ڡ�
                                                                       1'b0��1cycle��
                                                                       1'b1��2cycle�� */
        unsigned int  cluster0_svfd_edge_sel      : 1;  /* bit[29]   : svdf����ѡ��
                                                                       1'b0�������ؼ�⣻ 
                                                                       1'b1��˫�ؼ�⣨������+�½��أ��� */
        unsigned int  cluster0_svfd_cmp_data_mode : 2;  /* bit[30-31]: CPM���ֵ����ģʽ��
                                                                       00��ֱ�������
                                                                       01����Сֵ�����
                                                                       10�����ֵ�����
                                                                       11������ת�� */
    } reg;
} SOC_PMCTRL_VS_SVFD_CTRL0_0_UNION;
#endif
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_svfd_test_in_0_START               (0)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_svfd_test_in_0_END                 (3)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_svfd_ulvt_ll_0_START               (4)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_svfd_ulvt_ll_0_END                 (7)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_svfd_ulvt_sl_0_START               (8)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_svfd_ulvt_sl_0_END                 (11)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_svfd_lvt_ll_0_START                (12)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_svfd_lvt_ll_0_END                  (15)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_svfd_lvt_sl_0_START                (16)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_svfd_lvt_sl_0_END                  (19)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_svfd_vdm_mode_0_START              (20)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_svfd_vdm_mode_0_END                (21)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_svfd_match_detect_0_START          (22)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_svfd_match_detect_0_END            (22)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_svfd_trim_0_START                  (23)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_svfd_trim_0_END                    (23)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_svfd_d_rate_0_START                (24)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_svfd_d_rate_0_END                  (25)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_cluster0_svfd_off_mode_START       (26)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_cluster0_svfd_off_mode_END         (26)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_cluster0_svfd_div64_en_START       (27)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_cluster0_svfd_div64_en_END         (27)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_cluster0_svfd_vdm_period_START     (28)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_cluster0_svfd_vdm_period_END       (28)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_cluster0_svfd_edge_sel_START       (29)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_cluster0_svfd_edge_sel_END         (29)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_cluster0_svfd_cmp_data_mode_START  (30)
#define SOC_PMCTRL_VS_SVFD_CTRL0_0_cluster0_svfd_cmp_data_mode_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_SVFD_CTRL1_0_UNION
 �ṹ˵��  : VS_SVFD_CTRL1_0 �Ĵ����ṹ���塣��ַƫ����:0x3F4����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor�������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster0_svfd_data_limit_e : 1;  /* bit[0]   : ����ֵ���״̬�£�ʹ���źš�
                                                                     1'b0�����ǰһ����ֵ��
                                                                     1'b1��ʹ�ܼ�����ֵ�� */
        unsigned int  cluster0_svfd_glitch_test  : 1;  /* bit[1]   : Glitch����ʹ�ܡ� */
        unsigned int  cluster0_svfd_out_div_sel  : 4;  /* bit[2-5] : CPM���ַ�Ƶ���ѡ�� */
        unsigned int  reserved                   : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_SVFD_CTRL1_0_UNION;
#endif
#define SOC_PMCTRL_VS_SVFD_CTRL1_0_cluster0_svfd_data_limit_e_START  (0)
#define SOC_PMCTRL_VS_SVFD_CTRL1_0_cluster0_svfd_data_limit_e_END    (0)
#define SOC_PMCTRL_VS_SVFD_CTRL1_0_cluster0_svfd_glitch_test_START   (1)
#define SOC_PMCTRL_VS_SVFD_CTRL1_0_cluster0_svfd_glitch_test_END     (1)
#define SOC_PMCTRL_VS_SVFD_CTRL1_0_cluster0_svfd_out_div_sel_START   (2)
#define SOC_PMCTRL_VS_SVFD_CTRL1_0_cluster0_svfd_out_div_sel_END     (5)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_CTRL_EN_1_UNION
 �ṹ˵��  : VS_CTRL_EN_1 �Ĵ����ṹ���塣��ַƫ����:0x3F8����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor����ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_ctrl_en_1 : 1;  /* bit[0-0] : Cluster1 Vsensor����ʹ�ܡ�
                                                       0��Vsensor��ʹ�ܣ�
                                                       1��Vsensorʹ�ܡ� */
        unsigned int  reserved     : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_CTRL_EN_1_UNION;
#endif
#define SOC_PMCTRL_VS_CTRL_EN_1_vs_ctrl_en_1_START  (0)
#define SOC_PMCTRL_VS_CTRL_EN_1_vs_ctrl_en_1_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_CTRL_BYPASS_1_UNION
 �ṹ˵��  : VS_CTRL_BYPASS_1 �Ĵ����ṹ���塣��ַƫ����:0x3FC����ֵ:0x00000001�����:32
 �Ĵ���˵��: Vsensor bypass�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_ctrl_bypass_1 : 1;  /* bit[0-0] : Cluster1 Vsensor bypass�źš�
                                                           0��Vsensor�����߼�����ſ��źſ���ICG��
                                                           1��Vsensor�����߼�bypass���ſ��ź�һֱΪ1�� */
        unsigned int  reserved         : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_CTRL_BYPASS_1_UNION;
#endif
#define SOC_PMCTRL_VS_CTRL_BYPASS_1_vs_ctrl_bypass_1_START  (0)
#define SOC_PMCTRL_VS_CTRL_BYPASS_1_vs_ctrl_bypass_1_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_CTRL_1_UNION
 �ṹ˵��  : VS_CTRL_1 �Ĵ����ṹ���塣��ַƫ����:0x400����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor�������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_mod_cluster1                    : 1;  /* bit[0-0]  : Cluster1 Vsensorģʽ��
                                                                              0�����ж�ģʽ��
                                                                              1���ж�ģʽ�� */
        unsigned int  cluster1_cpu0_wfi_wfe_bypass       : 1;  /* bit[1-1]  : CPU0 WFI/WFE����������bypass��
                                                                              1'b1:bypass;
                                                                              1'b0:ʹ�ܡ� */
        unsigned int  cluster1_cpu1_wfi_wfe_bypass       : 1;  /* bit[2-2]  : CPU1 WFI/WFE����������bypass��
                                                                              1'b1:bypass;
                                                                              1'b0:ʹ�ܡ� */
        unsigned int  cluster1_cpu2_wfi_wfe_bypass       : 1;  /* bit[3-3]  : CPU2 WFI/WFE����������bypass��
                                                                              1'b1:bypass;
                                                                              1'b0:ʹ�ܡ� */
        unsigned int  cluster1_cpu3_wfi_wfe_bypass       : 1;  /* bit[4-4]  : CPU3 WFI/WFE����������bypass��
                                                                              1'b1:bypass;
                                                                              1'b0:ʹ�ܡ� */
        unsigned int  cluster1_l2_idle_div_mod           : 2;  /* bit[5-6]  : l2 idle�Զ���Ƶ��Ƶģʽ��
                                                                              00:4��Ƶ��
                                                                              01:8��Ƶ��
                                                                              10:16��Ƶ��
                                                                              11:32��Ƶ�� */
        unsigned int  cluster1_cfg_cnt_cpu_wake_quit     : 8;  /* bit[7-14] : Cluster1 WFI/WFE���������˳���ʱ����������ΪVDM����ʱ�ӡ� */
        unsigned int  cluster1_cfg_cnt_cpu_l2_idle_quit  : 8;  /* bit[15-22]: Cluster1 L2 IDLE���������˳���ʱ����������ΪVDM����ʱ�ӡ� */
        unsigned int  cluster1_cpu_wake_up_mode          : 2;  /* bit[23-24]: Cluster1 WFI/WFE��������ģʽ��
                                                                              2'b00:һ����һ�������˳�WFI/WFE,������������;
                                                                              2'b01:���������������˳�WFI/WFE,������������;
                                                                              2'b10:���������������˳�WFI/WFE,������������;
                                                                              2'b11:�ĸ�ͬʱ�˳�WFI/WFE,�������������� */
        unsigned int  cluster1_cpu_l2_idle_switch_bypass : 1;  /* bit[25]   : Cluster1 �˳�L2������������bypass��
                                                                              1'b1:bypass;
                                                                              1'b0:ʹ�ܡ� */
        unsigned int  cluster1_cpu_l2_idle_gt_en         : 1;  /* bit[26-26]: Cluster1 ����L2 IDLE���Զ���Ƶ����ʹ���źš�
                                                                              1'b0:��ʹ��;
                                                                              1'b1:ʹ�ܣ�����L2 IDLE����Ƶ�����Զ���Ƶģʽ���з�Ƶ�� */
        unsigned int  cluster1_compare_mod               : 2;  /* bit[27-28]: Cluster1���ݱȽ�ģʽ��
                                                                              00�������������ֱ����ref_code�Ƚϣ�
                                                                              01��������32���ۼ�������ref_code�Ƚϣ�
                                                                              10��������64���ۼ�������ref_code�Ƚϣ�
                                                                              11��������128���ۼ�������ref_code�Ƚϡ� */
        unsigned int  sel_ckmux_cluster1_icg             : 1;  /* bit[29]   : ʱ��ѡ��Դͷ��
                                                                              1'b0��CRGֱ�������ʱ�ӣ�
                                                                              1'b1��SVFD�����ʱ�ӡ� */
        unsigned int  reserved                           : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_CTRL_1_UNION;
#endif
#define SOC_PMCTRL_VS_CTRL_1_vs_mod_cluster1_START                     (0)
#define SOC_PMCTRL_VS_CTRL_1_vs_mod_cluster1_END                       (0)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_cpu0_wfi_wfe_bypass_START        (1)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_cpu0_wfi_wfe_bypass_END          (1)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_cpu1_wfi_wfe_bypass_START        (2)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_cpu1_wfi_wfe_bypass_END          (2)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_cpu2_wfi_wfe_bypass_START        (3)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_cpu2_wfi_wfe_bypass_END          (3)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_cpu3_wfi_wfe_bypass_START        (4)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_cpu3_wfi_wfe_bypass_END          (4)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_l2_idle_div_mod_START            (5)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_l2_idle_div_mod_END              (6)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_cfg_cnt_cpu_wake_quit_START      (7)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_cfg_cnt_cpu_wake_quit_END        (14)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_cfg_cnt_cpu_l2_idle_quit_START   (15)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_cfg_cnt_cpu_l2_idle_quit_END     (22)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_cpu_wake_up_mode_START           (23)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_cpu_wake_up_mode_END             (24)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_cpu_l2_idle_switch_bypass_START  (25)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_cpu_l2_idle_switch_bypass_END    (25)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_cpu_l2_idle_gt_en_START          (26)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_cpu_l2_idle_gt_en_END            (26)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_compare_mod_START                (27)
#define SOC_PMCTRL_VS_CTRL_1_cluster1_compare_mod_END                  (28)
#define SOC_PMCTRL_VS_CTRL_1_sel_ckmux_cluster1_icg_START              (29)
#define SOC_PMCTRL_VS_CTRL_1_sel_ckmux_cluster1_icg_END                (29)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_CNT_1_UNION
 �ṹ˵��  : VS_CNT_1 �Ĵ����ṹ���塣��ַƫ����:0x404����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor�������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_cnt_quit_1  : 16; /* bit[0-15] : �˳��ſ���ʱ��ÿ�ν����ſغ󣬻�ȴ���Ӧʱ����ٴν��е�ѹ�жϣ����ж�ģʽ���ã��� */
        unsigned int  vs_cnt_enter_1 : 16; /* bit[16-31]: �����ſ���ʱ��ÿ���˳��ſغ󣬻�ȴ���Ӧʱ����ٴν��е�ѹ�жϡ� */
    } reg;
} SOC_PMCTRL_VS_CNT_1_UNION;
#endif
#define SOC_PMCTRL_VS_CNT_1_vs_cnt_quit_1_START   (0)
#define SOC_PMCTRL_VS_CNT_1_vs_cnt_quit_1_END     (15)
#define SOC_PMCTRL_VS_CNT_1_vs_cnt_enter_1_START  (16)
#define SOC_PMCTRL_VS_CNT_1_vs_cnt_enter_1_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_REF_CODE_1_UNION
 �ṹ˵��  : VS_REF_CODE_1 �Ĵ����ṹ���塣��ַƫ����:0x408����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor�ο����ּĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_vs_ref_code_l : 6;  /* bit[0-5]  : Cluster1�����ſ����֡� */
        unsigned int  cluster1_vs_ref_code_h : 6;  /* bit[6-11] : Cluster1�˳��ſ����֡� */
        unsigned int  cluster1_ext_ref_code  : 7;  /* bit[12-18]: Cluster1 ref_code�ĸ�bit�����ref_code_h��ref_code_lһ��ʹ�ã���compare_mod��ء� */
        unsigned int  reserved               : 13; /* bit[19-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_REF_CODE_1_UNION;
#endif
#define SOC_PMCTRL_VS_REF_CODE_1_cluster1_vs_ref_code_l_START  (0)
#define SOC_PMCTRL_VS_REF_CODE_1_cluster1_vs_ref_code_l_END    (5)
#define SOC_PMCTRL_VS_REF_CODE_1_cluster1_vs_ref_code_h_START  (6)
#define SOC_PMCTRL_VS_REF_CODE_1_cluster1_vs_ref_code_h_END    (11)
#define SOC_PMCTRL_VS_REF_CODE_1_cluster1_ext_ref_code_START   (12)
#define SOC_PMCTRL_VS_REF_CODE_1_cluster1_ext_ref_code_END     (18)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_CALI_CODE_1_UNION
 �ṹ˵��  : VS_CALI_CODE_1 �Ĵ����ṹ���塣��ַƫ����:0x40C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor��ͷ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_vs_cali_code : 7;  /* bit[0-6] : Cluster1 Vsensor��ͷУ׼���֡� */
        unsigned int  reserved              : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_CALI_CODE_1_UNION;
#endif
#define SOC_PMCTRL_VS_CALI_CODE_1_cluster1_vs_cali_code_START  (0)
#define SOC_PMCTRL_VS_CALI_CODE_1_cluster1_vs_cali_code_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_CODE_1_UNION
 �ṹ˵��  : VS_CODE_1 �Ĵ����ṹ���塣��ַƫ����:0x410����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor���ּĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_vs_code : 6;  /* bit[0-5] : Cluster1 Vsensor���֡� */
        unsigned int  reserved         : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_CODE_1_UNION;
#endif
#define SOC_PMCTRL_VS_CODE_1_cluster1_vs_code_START  (0)
#define SOC_PMCTRL_VS_CODE_1_cluster1_vs_code_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_INTSTAT_1_UNION
 �ṹ˵��  : VS_INTSTAT_1 �Ĵ����ṹ���塣��ַƫ����:0x414����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor�ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_vdm_stat_1 : 1;  /* bit[0-0] : VDM�ж�״̬���ñ���д1�����VDM�е�intr_vdm�� */
        unsigned int  dll_lock_1      : 1;  /* bit[1-1] : DLL lockָʾ�Ĵ����� */
        unsigned int  reserved        : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_INTSTAT_1_UNION;
#endif
#define SOC_PMCTRL_VS_INTSTAT_1_intr_vdm_stat_1_START  (0)
#define SOC_PMCTRL_VS_INTSTAT_1_intr_vdm_stat_1_END    (0)
#define SOC_PMCTRL_VS_INTSTAT_1_dll_lock_1_START       (1)
#define SOC_PMCTRL_VS_INTSTAT_1_dll_lock_1_END         (1)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_SVFD_CTRL0_1_UNION
 �ṹ˵��  : VS_SVFD_CTRL0_1 �Ĵ����ṹ���塣��ַƫ����:0x418����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor�������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  svfd_test_in_1              : 4;  /* bit[0-3]  : Ԥ���������롣 */
        unsigned int  svfd_ulvt_ll_1              : 4;  /* bit[4-7]  : ULVT���߼�������������PIN�� */
        unsigned int  svfd_ulvt_sl_1              : 4;  /* bit[8-11] : ULVT���߼�������������PIN�� */
        unsigned int  svfd_lvt_ll_1               : 4;  /* bit[12-15]: LVT���߼�������������PIN�� */
        unsigned int  svfd_lvt_sl_1               : 4;  /* bit[16-19]: LVT���߼�������������PIN�� */
        unsigned int  svfd_vdm_mode_1             : 2;  /* bit[20-21]: ��ѹ���ģʽѡ��
                                                                       00 :reserve��
                                                                       01 : IP�ڲ���ѹ���(CPM)��
                                                                       10 : IP�ⲿ��ѹ���(VDM)��
                                                                       11 :VDM+CPM�� */
        unsigned int  svfd_match_detect_1         : 1;  /* bit[22-22]: ƥ������ʹ�ܣ�1��Ч��
                                                                       ����״̬��Ҫ����Ϊ0��
                                                                       ����DFT����ɸѡ�� */
        unsigned int  svfd_trim_1                 : 1;  /* bit[23-23]: trim�źš� */
        unsigned int  svfd_d_rate_1               : 2;  /* bit[24-25]: Cluster1 DLL�������ʡ�
                                                                       00 : 10%��
                                                                       01 : 20%��
                                                                       10 : 30%��
                                                                       11 : reseved�� */
        unsigned int  cluster1_svfd_off_mode      : 1;  /* bit[26]   : svfd��Ƶģʽ��
                                                                       1'b0��ֱ�ӽ�Ƶ��
                                                                       1'b1���𼶽�Ƶ�� */
        unsigned int  cluster1_svfd_div64_en      : 1;  /* bit[27]   : ʹ���źţ�����ģʽ����ת�� */
        unsigned int  cluster1_svfd_vdm_period    : 1;  /* bit[28]   : ��ѹ���������ڡ�
                                                                       1'b0��1cycle��
                                                                       1'b1��2cycle�� */
        unsigned int  cluster1_svfd_edge_sel      : 1;  /* bit[29]   : svdf����ѡ��
                                                                       1'b0�������ؼ�⣻ 
                                                                       1'b1��˫�ؼ�⣨������+�½��أ��� */
        unsigned int  cluster1_svfd_cmp_data_mode : 2;  /* bit[30-31]: CPM���ֵ����ģʽ��
                                                                       00��ֱ�������
                                                                       01����Сֵ�����
                                                                       10�����ֵ�����
                                                                       11������ת�� */
    } reg;
} SOC_PMCTRL_VS_SVFD_CTRL0_1_UNION;
#endif
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_svfd_test_in_1_START               (0)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_svfd_test_in_1_END                 (3)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_svfd_ulvt_ll_1_START               (4)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_svfd_ulvt_ll_1_END                 (7)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_svfd_ulvt_sl_1_START               (8)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_svfd_ulvt_sl_1_END                 (11)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_svfd_lvt_ll_1_START                (12)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_svfd_lvt_ll_1_END                  (15)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_svfd_lvt_sl_1_START                (16)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_svfd_lvt_sl_1_END                  (19)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_svfd_vdm_mode_1_START              (20)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_svfd_vdm_mode_1_END                (21)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_svfd_match_detect_1_START          (22)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_svfd_match_detect_1_END            (22)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_svfd_trim_1_START                  (23)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_svfd_trim_1_END                    (23)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_svfd_d_rate_1_START                (24)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_svfd_d_rate_1_END                  (25)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_cluster1_svfd_off_mode_START       (26)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_cluster1_svfd_off_mode_END         (26)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_cluster1_svfd_div64_en_START       (27)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_cluster1_svfd_div64_en_END         (27)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_cluster1_svfd_vdm_period_START     (28)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_cluster1_svfd_vdm_period_END       (28)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_cluster1_svfd_edge_sel_START       (29)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_cluster1_svfd_edge_sel_END         (29)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_cluster1_svfd_cmp_data_mode_START  (30)
#define SOC_PMCTRL_VS_SVFD_CTRL0_1_cluster1_svfd_cmp_data_mode_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_SVFD_CTRL1_1_UNION
 �ṹ˵��  : VS_SVFD_CTRL1_1 �Ĵ����ṹ���塣��ַƫ����:0x41C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor�������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  cluster1_svfd_data_limit_e : 1;  /* bit[0]   : ����ֵ���״̬�£�ʹ���źš�
                                                                     1'b0�����ǰһ����ֵ��
                                                                     1'b1��ʹ�ܼ�����ֵ�� */
        unsigned int  cluster1_svfd_glitch_test  : 1;  /* bit[1]   : Glitch����ʹ�ܡ� */
        unsigned int  cluster1_svfd_out_div_sel  : 4;  /* bit[2-5] : CPM���ַ�Ƶ���ѡ�� */
        unsigned int  reserved                   : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_SVFD_CTRL1_1_UNION;
#endif
#define SOC_PMCTRL_VS_SVFD_CTRL1_1_cluster1_svfd_data_limit_e_START  (0)
#define SOC_PMCTRL_VS_SVFD_CTRL1_1_cluster1_svfd_data_limit_e_END    (0)
#define SOC_PMCTRL_VS_SVFD_CTRL1_1_cluster1_svfd_glitch_test_START   (1)
#define SOC_PMCTRL_VS_SVFD_CTRL1_1_cluster1_svfd_glitch_test_END     (1)
#define SOC_PMCTRL_VS_SVFD_CTRL1_1_cluster1_svfd_out_div_sel_START   (2)
#define SOC_PMCTRL_VS_SVFD_CTRL1_1_cluster1_svfd_out_div_sel_END     (5)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERIHPMEN_UNION
 �ṹ˵��  : PERIHPMEN �Ĵ����ṹ���塣��ַƫ����:0x430����ֵ:0x00000000�����:32
 �Ĵ���˵��: PERI HPMʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_hpm_en : 1;  /* bit[0-0] : PERI HPMʹ�ܡ� */
        unsigned int  reserved    : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_PERIHPMEN_UNION;
#endif
#define SOC_PMCTRL_PERIHPMEN_peri_hpm_en_START  (0)
#define SOC_PMCTRL_PERIHPMEN_peri_hpm_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERIHPMXEN_UNION
 �ṹ˵��  : PERIHPMXEN �Ĵ����ṹ���塣��ַƫ����:0x434����ֵ:0x00000000�����:32
 �Ĵ���˵��: PERI HPMXʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_hpmx_en : 1;  /* bit[0-0] : PERI HPMXʹ�ܡ� */
        unsigned int  reserved     : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_PERIHPMXEN_UNION;
#endif
#define SOC_PMCTRL_PERIHPMXEN_peri_hpmx_en_START  (0)
#define SOC_PMCTRL_PERIHPMXEN_peri_hpmx_en_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERIHPMOPCVALID_UNION
 �ṹ˵��  : PERIHPMOPCVALID �Ĵ����ṹ���塣��ַƫ����:0x438����ֵ:0x00000000�����:32
 �Ĵ���˵��: PERI HPM OPC��Ч�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_hpm_opc_vld  : 1;  /* bit[0-0] : PERI HPMԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  peri_hpmx_opc_vld : 1;  /* bit[1-1] : PERI HPMXԭʼ��������Ч��״ָ̬ʾ�� */
        unsigned int  reserved          : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_PMCTRL_PERIHPMOPCVALID_UNION;
#endif
#define SOC_PMCTRL_PERIHPMOPCVALID_peri_hpm_opc_vld_START   (0)
#define SOC_PMCTRL_PERIHPMOPCVALID_peri_hpm_opc_vld_END     (0)
#define SOC_PMCTRL_PERIHPMOPCVALID_peri_hpmx_opc_vld_START  (1)
#define SOC_PMCTRL_PERIHPMOPCVALID_peri_hpmx_opc_vld_END    (1)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERIHPMOPC_UNION
 �ṹ˵��  : PERIHPMOPC �Ĵ����ṹ���塣��ַƫ����:0x43C����ֵ:0x00000000�����:32
 �Ĵ���˵��: PERI HPM OPC�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_hpm_opc  : 10; /* bit[0-9]  : PERI HPMԭʼ�����롣 */
        unsigned int  peri_hpmx_opc : 10; /* bit[10-19]: PERI HPMXԭʼ�����롣 */
        unsigned int  reserved      : 12; /* bit[20-31]: ������ */
    } reg;
} SOC_PMCTRL_PERIHPMOPC_UNION;
#endif
#define SOC_PMCTRL_PERIHPMOPC_peri_hpm_opc_START   (0)
#define SOC_PMCTRL_PERIHPMOPC_peri_hpm_opc_END     (9)
#define SOC_PMCTRL_PERIHPMOPC_peri_hpmx_opc_START  (10)
#define SOC_PMCTRL_PERIHPMOPC_peri_hpmx_opc_END    (19)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_PERIHPMCLKDIV_UNION
 �ṹ˵��  : PERIHPMCLKDIV �Ĵ����ṹ���塣��ַƫ����:0x440����ֵ:0x00000001�����:32
 �Ĵ���˵��: PERI HPMʱ�ӷ�Ƶ�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  peri_hpm_clk_div : 6;  /* bit[0-5] : PERI HPMʱ�ӷ�Ƶ���� */
        unsigned int  reserved         : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMCTRL_PERIHPMCLKDIV_UNION;
#endif
#define SOC_PMCTRL_PERIHPMCLKDIV_peri_hpm_clk_div_START  (0)
#define SOC_PMCTRL_PERIHPMCLKDIV_peri_hpm_clk_div_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_BOOTROMFLAG_UNION
 �ṹ˵��  : BOOTROMFLAG �Ĵ����ṹ���塣��ַƫ����:0x460����ֵ:0x00000000�����:32
 �Ĵ���˵��: BOOTROM FLAG�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  bootrom_flag : 1;  /* bit[0-0] : BOOTROM����ʱ��ÿһ��ָ�������ת��bit������test����� */
        unsigned int  reserved     : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_BOOTROMFLAG_UNION;
#endif
#define SOC_PMCTRL_BOOTROMFLAG_bootrom_flag_START  (0)
#define SOC_PMCTRL_BOOTROMFLAG_bootrom_flag_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_CTRL_EN_2_UNION
 �ṹ˵��  : VS_CTRL_EN_2 �Ĵ����ṹ���塣��ַƫ����:0x464����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor����ʹ�ܼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_ctrl_en_2 : 1;  /* bit[0-0] : G3D Vsensor����ʹ�ܡ�
                                                       0��Vsensor��ʹ�ܣ�
                                                       1��Vsensorʹ�ܡ� */
        unsigned int  reserved     : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_CTRL_EN_2_UNION;
#endif
#define SOC_PMCTRL_VS_CTRL_EN_2_vs_ctrl_en_2_START  (0)
#define SOC_PMCTRL_VS_CTRL_EN_2_vs_ctrl_en_2_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_CTRL_BYPASS_2_UNION
 �ṹ˵��  : VS_CTRL_BYPASS_2 �Ĵ����ṹ���塣��ַƫ����:0x468����ֵ:0x00000001�����:32
 �Ĵ���˵��: Vsensor bypass�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_ctrl_bypass_2 : 1;  /* bit[0-0] : G3D Vsensor bypass�źš�
                                                           0��Vsensor�����߼�����ſ��źſ���ICG��
                                                           1��Vsensor�����߼�bypass���ſ��ź�һֱΪ1�� */
        unsigned int  reserved         : 31; /* bit[1-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_CTRL_BYPASS_2_UNION;
#endif
#define SOC_PMCTRL_VS_CTRL_BYPASS_2_vs_ctrl_bypass_2_START  (0)
#define SOC_PMCTRL_VS_CTRL_BYPASS_2_vs_ctrl_bypass_2_END    (0)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_CTRL_2_UNION
 �ṹ˵��  : VS_CTRL_2 �Ĵ����ṹ���塣��ַƫ����:0x46C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor�������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_mod_g3d                    : 1;  /* bit[0-0]  : G3D Vsensorģʽ��
                                                                         0�����ж�ģʽ��
                                                                         1���ж�ģʽ�� */
        unsigned int  g3d_cpu0_wfi_wfe_bypass       : 1;  /* bit[1-1]  : CPU0 WFI/WFE����������bypass��
                                                                         1'b1:bypass;
                                                                         1'b0:ʹ�ܡ� */
        unsigned int  g3d_cpu1_wfi_wfe_bypass       : 1;  /* bit[2-2]  : CPU1 WFI/WFE����������bypass��
                                                                         1'b1:bypass;
                                                                         1'b0:ʹ�ܡ� */
        unsigned int  g3d_cpu2_wfi_wfe_bypass       : 1;  /* bit[3-3]  : CPU2 WFI/WFE����������bypass��
                                                                         1'b1:bypass;
                                                                         1'b0:ʹ�ܡ� */
        unsigned int  g3d_cpu3_wfi_wfe_bypass       : 1;  /* bit[4-4]  : CPU3 WFI/WFE����������bypass��
                                                                         1'b1:bypass;
                                                                         1'b0:ʹ�ܡ� */
        unsigned int  g3d_l2_idle_div_mod           : 2;  /* bit[5-6]  : l2 idle�Զ���Ƶ��Ƶģʽ��
                                                                         00:4��Ƶ��
                                                                         01:8��Ƶ��
                                                                         10:16��Ƶ��
                                                                         11:32��Ƶ�� */
        unsigned int  g3d_cfg_cnt_cpu_wake_quit     : 8;  /* bit[7-14] : G3D WFI/WFE���������˳���ʱ����������ΪVDM����ʱ�ӡ� */
        unsigned int  g3d_cfg_cnt_cpu_l2_idle_quit  : 8;  /* bit[15-22]: G3D L2 IDLE���������˳���ʱ����������ΪVDM����ʱ�ӡ� */
        unsigned int  g3d_cpu_wake_up_mode          : 2;  /* bit[23-24]: G3D WFI/WFE��������ģʽ��
                                                                         2'b00:һ����һ�������˳�WFI/WFE,������������;
                                                                         2'b01:���������������˳�WFI/WFE,������������;
                                                                         2'b10:���������������˳�WFI/WFE,������������;
                                                                         2'b11:�ĸ�ͬʱ�˳�WFI/WFE,�������������� */
        unsigned int  g3d_cpu_l2_idle_switch_bypass : 1;  /* bit[25-25]: G3D �˳�L2������������bypass��
                                                                         1'b1:bypass;
                                                                         1'b0:ʹ�ܡ� */
        unsigned int  g3d_cpu_l2_idle_gt_en         : 1;  /* bit[26-26]: G3D ����L2 IDLE���Զ���Ƶ����ʹ���źš�
                                                                         1'b0:��ʹ��;
                                                                         1'b1:ʹ�ܣ�����L2 IDLE����Ƶ�����Զ���Ƶģʽ���з�Ƶ�� */
        unsigned int  g3d_compare_mod               : 2;  /* bit[27-28]: G3D���ݱȽ�ģʽ��
                                                                         00�������������ֱ����ref_code�Ƚϣ�
                                                                         01��������32���ۼ�������ref_code�Ƚϣ�
                                                                         10��������64���ۼ�������ref_code�Ƚϣ�
                                                                         11��������128���ۼ�������ref_code�Ƚϡ� */
        unsigned int  sel_ckmux_g3d_icg             : 1;  /* bit[29-29]: ʱ��ѡ��Դͷ��
                                                                         1'b0��CRGֱ�������ʱ�ӣ�
                                                                         1'b1��SVFD�����ʱ�ӡ� */
        unsigned int  reserved                      : 2;  /* bit[30-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_CTRL_2_UNION;
#endif
#define SOC_PMCTRL_VS_CTRL_2_vs_mod_g3d_START                     (0)
#define SOC_PMCTRL_VS_CTRL_2_vs_mod_g3d_END                       (0)
#define SOC_PMCTRL_VS_CTRL_2_g3d_cpu0_wfi_wfe_bypass_START        (1)
#define SOC_PMCTRL_VS_CTRL_2_g3d_cpu0_wfi_wfe_bypass_END          (1)
#define SOC_PMCTRL_VS_CTRL_2_g3d_cpu1_wfi_wfe_bypass_START        (2)
#define SOC_PMCTRL_VS_CTRL_2_g3d_cpu1_wfi_wfe_bypass_END          (2)
#define SOC_PMCTRL_VS_CTRL_2_g3d_cpu2_wfi_wfe_bypass_START        (3)
#define SOC_PMCTRL_VS_CTRL_2_g3d_cpu2_wfi_wfe_bypass_END          (3)
#define SOC_PMCTRL_VS_CTRL_2_g3d_cpu3_wfi_wfe_bypass_START        (4)
#define SOC_PMCTRL_VS_CTRL_2_g3d_cpu3_wfi_wfe_bypass_END          (4)
#define SOC_PMCTRL_VS_CTRL_2_g3d_l2_idle_div_mod_START            (5)
#define SOC_PMCTRL_VS_CTRL_2_g3d_l2_idle_div_mod_END              (6)
#define SOC_PMCTRL_VS_CTRL_2_g3d_cfg_cnt_cpu_wake_quit_START      (7)
#define SOC_PMCTRL_VS_CTRL_2_g3d_cfg_cnt_cpu_wake_quit_END        (14)
#define SOC_PMCTRL_VS_CTRL_2_g3d_cfg_cnt_cpu_l2_idle_quit_START   (15)
#define SOC_PMCTRL_VS_CTRL_2_g3d_cfg_cnt_cpu_l2_idle_quit_END     (22)
#define SOC_PMCTRL_VS_CTRL_2_g3d_cpu_wake_up_mode_START           (23)
#define SOC_PMCTRL_VS_CTRL_2_g3d_cpu_wake_up_mode_END             (24)
#define SOC_PMCTRL_VS_CTRL_2_g3d_cpu_l2_idle_switch_bypass_START  (25)
#define SOC_PMCTRL_VS_CTRL_2_g3d_cpu_l2_idle_switch_bypass_END    (25)
#define SOC_PMCTRL_VS_CTRL_2_g3d_cpu_l2_idle_gt_en_START          (26)
#define SOC_PMCTRL_VS_CTRL_2_g3d_cpu_l2_idle_gt_en_END            (26)
#define SOC_PMCTRL_VS_CTRL_2_g3d_compare_mod_START                (27)
#define SOC_PMCTRL_VS_CTRL_2_g3d_compare_mod_END                  (28)
#define SOC_PMCTRL_VS_CTRL_2_sel_ckmux_g3d_icg_START              (29)
#define SOC_PMCTRL_VS_CTRL_2_sel_ckmux_g3d_icg_END                (29)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_CNT_2_UNION
 �ṹ˵��  : VS_CNT_2 �Ĵ����ṹ���塣��ַƫ����:0x470����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor�������ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  vs_cnt_quit_2  : 16; /* bit[0-15] : �˳��ſ���ʱ��ÿ�ν����ſغ󣬻�ȴ���Ӧʱ����ٴν��е�ѹ�жϣ����ж�ģʽ���ã��� */
        unsigned int  vs_cnt_enter_2 : 16; /* bit[16-31]: �����ſ���ʱ��ÿ���˳��ſغ󣬻�ȴ���Ӧʱ����ٴν��е�ѹ�жϡ� */
    } reg;
} SOC_PMCTRL_VS_CNT_2_UNION;
#endif
#define SOC_PMCTRL_VS_CNT_2_vs_cnt_quit_2_START   (0)
#define SOC_PMCTRL_VS_CNT_2_vs_cnt_quit_2_END     (15)
#define SOC_PMCTRL_VS_CNT_2_vs_cnt_enter_2_START  (16)
#define SOC_PMCTRL_VS_CNT_2_vs_cnt_enter_2_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_REF_CODE_2_UNION
 �ṹ˵��  : VS_REF_CODE_2 �Ĵ����ṹ���塣��ַƫ����:0x474����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor�ο����ּĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_vs_ref_code_l : 6;  /* bit[0-5]  : G3D�����ſ����֡� */
        unsigned int  g3d_vs_ref_code_h : 6;  /* bit[6-11] : G3D�˳��ſ����֡� */
        unsigned int  g3d_ext_ref_code  : 7;  /* bit[12-18]: G3D ref_code�ĸ�bit�����ref_code_h��ref_code_lһ��ʹ�ã���compare_mod��ء� */
        unsigned int  reserved          : 13; /* bit[19-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_REF_CODE_2_UNION;
#endif
#define SOC_PMCTRL_VS_REF_CODE_2_g3d_vs_ref_code_l_START  (0)
#define SOC_PMCTRL_VS_REF_CODE_2_g3d_vs_ref_code_l_END    (5)
#define SOC_PMCTRL_VS_REF_CODE_2_g3d_vs_ref_code_h_START  (6)
#define SOC_PMCTRL_VS_REF_CODE_2_g3d_vs_ref_code_h_END    (11)
#define SOC_PMCTRL_VS_REF_CODE_2_g3d_ext_ref_code_START   (12)
#define SOC_PMCTRL_VS_REF_CODE_2_g3d_ext_ref_code_END     (18)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_CALI_CODE_2_UNION
 �ṹ˵��  : VS_CALI_CODE_2 �Ĵ����ṹ���塣��ַƫ����:0x47C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor��ͷ���ƼĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_vs_cali_code : 7;  /* bit[0-6] : G3D Vsensor��ͷУ׼���֡� */
        unsigned int  reserved         : 25; /* bit[7-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_CALI_CODE_2_UNION;
#endif
#define SOC_PMCTRL_VS_CALI_CODE_2_g3d_vs_cali_code_START  (0)
#define SOC_PMCTRL_VS_CALI_CODE_2_g3d_vs_cali_code_END    (6)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_CODE_2_UNION
 �ṹ˵��  : VS_CODE_2 �Ĵ����ṹ���塣��ַƫ����:0x480����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor���ּĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_vs_code : 6;  /* bit[0-5] : G3D Vsensor���֡� */
        unsigned int  reserved    : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_CODE_2_UNION;
#endif
#define SOC_PMCTRL_VS_CODE_2_g3d_vs_code_START  (0)
#define SOC_PMCTRL_VS_CODE_2_g3d_vs_code_END    (5)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_INTSTAT_2_UNION
 �ṹ˵��  : VS_INTSTAT_2 �Ĵ����ṹ���塣��ַƫ����:0x484����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor�ж�״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  intr_vdm_stat_2 : 1;  /* bit[0-0] : VDM�ж�״̬���ñ���д1�����VDM�е�intr_vdm�� */
        unsigned int  dll_lock_2      : 1;  /* bit[1-1] : DLL lockָʾ�Ĵ����� */
        unsigned int  reserved        : 30; /* bit[2-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_INTSTAT_2_UNION;
#endif
#define SOC_PMCTRL_VS_INTSTAT_2_intr_vdm_stat_2_START  (0)
#define SOC_PMCTRL_VS_INTSTAT_2_intr_vdm_stat_2_END    (0)
#define SOC_PMCTRL_VS_INTSTAT_2_dll_lock_2_START       (1)
#define SOC_PMCTRL_VS_INTSTAT_2_dll_lock_2_END         (1)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_SVFD_CTRL0_2_UNION
 �ṹ˵��  : VS_SVFD_CTRL0_2 �Ĵ����ṹ���塣��ַƫ����:0x48C����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor�������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  svfd_test_in_2         : 4;  /* bit[0-3]  : Ԥ���������롣 */
        unsigned int  svfd_ulvt_ll_2         : 4;  /* bit[4-7]  : ULVT���߼�������������PIN�� */
        unsigned int  svfd_ulvt_sl_2         : 4;  /* bit[8-11] : ULVT���߼�������������PIN�� */
        unsigned int  svfd_lvt_ll_2          : 4;  /* bit[12-15]: LVT���߼�������������PIN�� */
        unsigned int  svfd_lvt_sl_2          : 4;  /* bit[16-19]: LVT���߼�������������PIN�� */
        unsigned int  svfd_vdm_mode_2        : 2;  /* bit[20-21]: ��ѹ���ģʽѡ��
                                                                  00 :reserve��
                                                                  01 : IP�ڲ���ѹ���(CPM)��
                                                                  10 : IP�ⲿ��ѹ���(VDM)��
                                                                  11 :VDM+CPM�� */
        unsigned int  svfd_match_detect_2    : 1;  /* bit[22-22]: ƥ������ʹ�ܣ�1��Ч��
                                                                  ����״̬��Ҫ����Ϊ0��
                                                                  ����DFT����ɸѡ�� */
        unsigned int  svfd_trim_2            : 1;  /* bit[23-23]: trim�źš� */
        unsigned int  svfd_d_rate_2          : 2;  /* bit[24-25]: G3D DLL�������ʡ�
                                                                  00 : 10%��
                                                                  01 : 20%��
                                                                  10 : 30%��
                                                                  11 : reseved�� */
        unsigned int  g3d_svfd_off_mode      : 1;  /* bit[26]   : svfd��Ƶģʽ��
                                                                  1'b0��ֱ�ӽ�Ƶ��
                                                                  1'b1���𼶽�Ƶ�� */
        unsigned int  g3d_svfd_div64_en      : 1;  /* bit[27]   : ʹ���źţ�����ģʽ����ת�� */
        unsigned int  g3d_svfd_vdm_period    : 1;  /* bit[28]   : ��ѹ���������ڡ�
                                                                  1'b0��1cycle��
                                                                  1'b1��2cycle�� */
        unsigned int  g3d_svfd_edge_sel      : 1;  /* bit[29]   : svdf����ѡ��
                                                                  1'b0�������ؼ�⣻ 
                                                                  1'b1��˫�ؼ�⣨������+�½��أ��� */
        unsigned int  g3d_svfd_cmp_data_mode : 2;  /* bit[30-31]: CPM���ֵ����ģʽ��
                                                                  00��ֱ�������
                                                                  01����Сֵ�����
                                                                  10�����ֵ�����
                                                                  11������ת�� */
    } reg;
} SOC_PMCTRL_VS_SVFD_CTRL0_2_UNION;
#endif
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_svfd_test_in_2_START          (0)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_svfd_test_in_2_END            (3)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_svfd_ulvt_ll_2_START          (4)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_svfd_ulvt_ll_2_END            (7)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_svfd_ulvt_sl_2_START          (8)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_svfd_ulvt_sl_2_END            (11)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_svfd_lvt_ll_2_START           (12)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_svfd_lvt_ll_2_END             (15)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_svfd_lvt_sl_2_START           (16)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_svfd_lvt_sl_2_END             (19)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_svfd_vdm_mode_2_START         (20)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_svfd_vdm_mode_2_END           (21)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_svfd_match_detect_2_START     (22)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_svfd_match_detect_2_END       (22)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_svfd_trim_2_START             (23)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_svfd_trim_2_END               (23)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_svfd_d_rate_2_START           (24)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_svfd_d_rate_2_END             (25)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_g3d_svfd_off_mode_START       (26)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_g3d_svfd_off_mode_END         (26)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_g3d_svfd_div64_en_START       (27)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_g3d_svfd_div64_en_END         (27)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_g3d_svfd_vdm_period_START     (28)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_g3d_svfd_vdm_period_END       (28)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_g3d_svfd_edge_sel_START       (29)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_g3d_svfd_edge_sel_END         (29)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_g3d_svfd_cmp_data_mode_START  (30)
#define SOC_PMCTRL_VS_SVFD_CTRL0_2_g3d_svfd_cmp_data_mode_END    (31)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_VS_SVFD_CTRL1_2_UNION
 �ṹ˵��  : VS_SVFD_CTRL1_2 �Ĵ����ṹ���塣��ַƫ����:0x490����ֵ:0x00000000�����:32
 �Ĵ���˵��: Vsensor�������üĴ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3d_svfd_data_limit_e : 1;  /* bit[0]   : ����ֵ���״̬�£�ʹ���źš�
                                                                1'b0�����ǰһ����ֵ��
                                                                1'b1��ʹ�ܼ�����ֵ�� */
        unsigned int  g3d_svfd_glitch_test  : 1;  /* bit[1]   : Glitch����ʹ�ܡ� */
        unsigned int  g3d_svfd_out_div_sel  : 4;  /* bit[2-5] : CPM���ַ�Ƶ���ѡ�� */
        unsigned int  reserved              : 26; /* bit[6-31]: ������ */
    } reg;
} SOC_PMCTRL_VS_SVFD_CTRL1_2_UNION;
#endif
#define SOC_PMCTRL_VS_SVFD_CTRL1_2_g3d_svfd_data_limit_e_START  (0)
#define SOC_PMCTRL_VS_SVFD_CTRL1_2_g3d_svfd_data_limit_e_END    (0)
#define SOC_PMCTRL_VS_SVFD_CTRL1_2_g3d_svfd_glitch_test_START   (1)
#define SOC_PMCTRL_VS_SVFD_CTRL1_2_g3d_svfd_glitch_test_END     (1)
#define SOC_PMCTRL_VS_SVFD_CTRL1_2_g3d_svfd_out_div_sel_START   (2)
#define SOC_PMCTRL_VS_SVFD_CTRL1_2_g3d_svfd_out_div_sel_END     (5)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_APLL0CTRL0_STAT_UNION
 �ṹ˵��  : APLL0CTRL0_STAT �Ĵ����ṹ���塣��ַƫ����:0x494����ֵ:0x00B03E06�����:32
 �Ĵ���˵��: APLL0����״̬�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll0_en_stat       : 1;  /* bit[0-0]  : APLL0 PowerDown���ơ�
                                                               0���رգ�
                                                               1��ʹ�ܡ� */
        unsigned int  apll0_bp_stat       : 1;  /* bit[1-1]  : APLL0 Bypass���ơ�
                                                               0������������
                                                               1��Bypass�� */
        unsigned int  apll0_refdiv_stat   : 6;  /* bit[2-7]  : APLL0����ʱ�ӷ�Ƶ���� */
        unsigned int  apll0_fbdiv_stat    : 12; /* bit[8-19] : APLL0����ʱ��������Ƶ���� */
        unsigned int  apll0_postdiv1_stat : 3;  /* bit[20-22]: APLL0���ʱ�ӷ�Ƶ��1�� */
        unsigned int  apll0_postdiv2_stat : 3;  /* bit[23-25]: APLL0���ʱ�ӷ�Ƶ��2�� */
        unsigned int  reserved            : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_PMCTRL_APLL0CTRL0_STAT_UNION;
#endif
#define SOC_PMCTRL_APLL0CTRL0_STAT_apll0_en_stat_START        (0)
#define SOC_PMCTRL_APLL0CTRL0_STAT_apll0_en_stat_END          (0)
#define SOC_PMCTRL_APLL0CTRL0_STAT_apll0_bp_stat_START        (1)
#define SOC_PMCTRL_APLL0CTRL0_STAT_apll0_bp_stat_END          (1)
#define SOC_PMCTRL_APLL0CTRL0_STAT_apll0_refdiv_stat_START    (2)
#define SOC_PMCTRL_APLL0CTRL0_STAT_apll0_refdiv_stat_END      (7)
#define SOC_PMCTRL_APLL0CTRL0_STAT_apll0_fbdiv_stat_START     (8)
#define SOC_PMCTRL_APLL0CTRL0_STAT_apll0_fbdiv_stat_END       (19)
#define SOC_PMCTRL_APLL0CTRL0_STAT_apll0_postdiv1_stat_START  (20)
#define SOC_PMCTRL_APLL0CTRL0_STAT_apll0_postdiv1_stat_END    (22)
#define SOC_PMCTRL_APLL0CTRL0_STAT_apll0_postdiv2_stat_START  (23)
#define SOC_PMCTRL_APLL0CTRL0_STAT_apll0_postdiv2_stat_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_APLL0CTRL1_STAT_UNION
 �ṹ˵��  : APLL0CTRL1_STAT �Ĵ����ṹ���塣��ַƫ����:0x498����ֵ:0x06F80000�����:32
 �Ĵ���˵��: APLL0����״̬�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll0_fracdiv_stat : 24; /* bit[0-23] : APLL0����ʱ�ӷ�����Ƶ���� */
        unsigned int  apll0_int_mod_stat : 1;  /* bit[24-24]: APLL0������Ƶģʽ��
                                                              0��������Ƶģʽ��
                                                              1��������Ƶģʽ��
                                                              ע�⣺��PLL֧�ַ�����Ƶ��������Ƶģʽ������SSC��ʱ��Ҫ�����ֻʹ�÷�����Ƶģʽ�� */
        unsigned int  apll0_cfg_vld_stat : 1;  /* bit[25-25]: APLL0������Ч��־��
                                                              0��������Ч��
                                                              1��������Ч�� */
        unsigned int  gt_clk_apll0_stat  : 1;  /* bit[26-26]: APLL0�ſ��źš�
                                                              0��APLL0���ʱ���ſأ�
                                                              1��APLL0���ʱ�Ӳ��ſء����ȴ�PLL�ȶ���������ø�bit�� */
        unsigned int  reserved           : 5;  /* bit[27-31]: ������ */
    } reg;
} SOC_PMCTRL_APLL0CTRL1_STAT_UNION;
#endif
#define SOC_PMCTRL_APLL0CTRL1_STAT_apll0_fracdiv_stat_START  (0)
#define SOC_PMCTRL_APLL0CTRL1_STAT_apll0_fracdiv_stat_END    (23)
#define SOC_PMCTRL_APLL0CTRL1_STAT_apll0_int_mod_stat_START  (24)
#define SOC_PMCTRL_APLL0CTRL1_STAT_apll0_int_mod_stat_END    (24)
#define SOC_PMCTRL_APLL0CTRL1_STAT_apll0_cfg_vld_stat_START  (25)
#define SOC_PMCTRL_APLL0CTRL1_STAT_apll0_cfg_vld_stat_END    (25)
#define SOC_PMCTRL_APLL0CTRL1_STAT_gt_clk_apll0_stat_START   (26)
#define SOC_PMCTRL_APLL0CTRL1_STAT_gt_clk_apll0_stat_END     (26)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_APLL1CTRL0_STAT_UNION
 �ṹ˵��  : APLL1CTRL0_STAT �Ĵ����ṹ���塣��ַƫ����:0x49C����ֵ:0x00B03E06�����:32
 �Ĵ���˵��: APLL1����״̬�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll1_en_stat       : 1;  /* bit[0-0]  : APLL1 PowerDown���ơ�
                                                               0���رգ�
                                                               1��ʹ�ܡ� */
        unsigned int  apll1_bp_stat       : 1;  /* bit[1-1]  : APLL1 Bypass���ơ�
                                                               0������������
                                                               1��Bypass�� */
        unsigned int  apll1_refdiv_stat   : 6;  /* bit[2-7]  : APLL1����ʱ�ӷ�Ƶ���� */
        unsigned int  apll1_fbdiv_stat    : 12; /* bit[8-19] : APLL1����ʱ��������Ƶ���� */
        unsigned int  apll1_postdiv1_stat : 3;  /* bit[20-22]: APLL1���ʱ�ӷ�Ƶ��1�� */
        unsigned int  apll1_postdiv2_stat : 3;  /* bit[23-25]: APLL1���ʱ�ӷ�Ƶ��2�� */
        unsigned int  reserved            : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_PMCTRL_APLL1CTRL0_STAT_UNION;
#endif
#define SOC_PMCTRL_APLL1CTRL0_STAT_apll1_en_stat_START        (0)
#define SOC_PMCTRL_APLL1CTRL0_STAT_apll1_en_stat_END          (0)
#define SOC_PMCTRL_APLL1CTRL0_STAT_apll1_bp_stat_START        (1)
#define SOC_PMCTRL_APLL1CTRL0_STAT_apll1_bp_stat_END          (1)
#define SOC_PMCTRL_APLL1CTRL0_STAT_apll1_refdiv_stat_START    (2)
#define SOC_PMCTRL_APLL1CTRL0_STAT_apll1_refdiv_stat_END      (7)
#define SOC_PMCTRL_APLL1CTRL0_STAT_apll1_fbdiv_stat_START     (8)
#define SOC_PMCTRL_APLL1CTRL0_STAT_apll1_fbdiv_stat_END       (19)
#define SOC_PMCTRL_APLL1CTRL0_STAT_apll1_postdiv1_stat_START  (20)
#define SOC_PMCTRL_APLL1CTRL0_STAT_apll1_postdiv1_stat_END    (22)
#define SOC_PMCTRL_APLL1CTRL0_STAT_apll1_postdiv2_stat_START  (23)
#define SOC_PMCTRL_APLL1CTRL0_STAT_apll1_postdiv2_stat_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_APLL1CTRL1_STAT_UNION
 �ṹ˵��  : APLL1CTRL1_STAT �Ĵ����ṹ���塣��ַƫ����:0x4A0����ֵ:0x06F80000�����:32
 �Ĵ���˵��: APLL1����״̬�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll1_fracdiv_stat : 24; /* bit[0-23] : APLL1����ʱ�ӷ�����Ƶ���� */
        unsigned int  apll1_int_mod_stat : 1;  /* bit[24-24]: APLL1������Ƶģʽ��
                                                              0��������Ƶģʽ��
                                                              1��������Ƶģʽ��
                                                              ע�⣺��PLL֧�ַ�����Ƶ��������Ƶģʽ������SSC��ʱ��Ҫ�����ֻʹ�÷�����Ƶģʽ�� */
        unsigned int  apll1_cfg_vld_stat : 1;  /* bit[25-25]: APLL1������Ч��־��
                                                              0��������Ч��
                                                              1��������Ч�� */
        unsigned int  gt_clk_apll1_stat  : 1;  /* bit[26-26]: APLL1�ſ��źš�
                                                              0��APLL1���ʱ���ſأ�
                                                              1��APLL1���ʱ�Ӳ��ſء����ȴ�PLL�ȶ���������ø�bit�� */
        unsigned int  reserved           : 5;  /* bit[27-31]: ������ */
    } reg;
} SOC_PMCTRL_APLL1CTRL1_STAT_UNION;
#endif
#define SOC_PMCTRL_APLL1CTRL1_STAT_apll1_fracdiv_stat_START  (0)
#define SOC_PMCTRL_APLL1CTRL1_STAT_apll1_fracdiv_stat_END    (23)
#define SOC_PMCTRL_APLL1CTRL1_STAT_apll1_int_mod_stat_START  (24)
#define SOC_PMCTRL_APLL1CTRL1_STAT_apll1_int_mod_stat_END    (24)
#define SOC_PMCTRL_APLL1CTRL1_STAT_apll1_cfg_vld_stat_START  (25)
#define SOC_PMCTRL_APLL1CTRL1_STAT_apll1_cfg_vld_stat_END    (25)
#define SOC_PMCTRL_APLL1CTRL1_STAT_gt_clk_apll1_stat_START   (26)
#define SOC_PMCTRL_APLL1CTRL1_STAT_gt_clk_apll1_stat_END     (26)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_APLL2CTRL0_STAT_UNION
 �ṹ˵��  : APLL2CTRL0_STAT �Ĵ����ṹ���塣��ַƫ����:0x4A4����ֵ:0x00B03E06�����:32
 �Ĵ���˵��: APLL2����״̬�Ĵ���0��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll2_en_stat       : 1;  /* bit[0-0]  : APLL2 PowerDown���ơ�
                                                               0���رգ�
                                                               1��ʹ�ܡ� */
        unsigned int  apll2_bp_stat       : 1;  /* bit[1-1]  : APLL2 Bypass���ơ�
                                                               0������������
                                                               1��Bypass�� */
        unsigned int  apll2_refdiv_stat   : 6;  /* bit[2-7]  : APLL2����ʱ�ӷ�Ƶ���� */
        unsigned int  apll2_fbdiv_stat    : 12; /* bit[8-19] : APLL2����ʱ��������Ƶ���� */
        unsigned int  apll2_postdiv1_stat : 3;  /* bit[20-22]: APLL2���ʱ�ӷ�Ƶ��1�� */
        unsigned int  apll2_postdiv2_stat : 3;  /* bit[23-25]: APLL2���ʱ�ӷ�Ƶ��2�� */
        unsigned int  reserved            : 6;  /* bit[26-31]: ������ */
    } reg;
} SOC_PMCTRL_APLL2CTRL0_STAT_UNION;
#endif
#define SOC_PMCTRL_APLL2CTRL0_STAT_apll2_en_stat_START        (0)
#define SOC_PMCTRL_APLL2CTRL0_STAT_apll2_en_stat_END          (0)
#define SOC_PMCTRL_APLL2CTRL0_STAT_apll2_bp_stat_START        (1)
#define SOC_PMCTRL_APLL2CTRL0_STAT_apll2_bp_stat_END          (1)
#define SOC_PMCTRL_APLL2CTRL0_STAT_apll2_refdiv_stat_START    (2)
#define SOC_PMCTRL_APLL2CTRL0_STAT_apll2_refdiv_stat_END      (7)
#define SOC_PMCTRL_APLL2CTRL0_STAT_apll2_fbdiv_stat_START     (8)
#define SOC_PMCTRL_APLL2CTRL0_STAT_apll2_fbdiv_stat_END       (19)
#define SOC_PMCTRL_APLL2CTRL0_STAT_apll2_postdiv1_stat_START  (20)
#define SOC_PMCTRL_APLL2CTRL0_STAT_apll2_postdiv1_stat_END    (22)
#define SOC_PMCTRL_APLL2CTRL0_STAT_apll2_postdiv2_stat_START  (23)
#define SOC_PMCTRL_APLL2CTRL0_STAT_apll2_postdiv2_stat_END    (25)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_APLL2CTRL1_STAT_UNION
 �ṹ˵��  : APLL2CTRL1_STAT �Ĵ����ṹ���塣��ַƫ����:0x4A8����ֵ:0x06F80000�����:32
 �Ĵ���˵��: APLL2����״̬�Ĵ���1��
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  apll2_fracdiv_stat : 24; /* bit[0-23] : APLL2����ʱ�ӷ�����Ƶ���� */
        unsigned int  apll2_int_mod_stat : 1;  /* bit[24-24]: APLL2������Ƶģʽ��
                                                              0��������Ƶģʽ��
                                                              1��������Ƶģʽ��
                                                              ע�⣺��PLL֧�ַ�����Ƶ��������Ƶģʽ������SSC��ʱ��Ҫ�����ֻʹ�÷�����Ƶģʽ�� */
        unsigned int  apll2_cfg_vld_stat : 1;  /* bit[25-25]: APLL2������Ч��־��
                                                              0��������Ч��
                                                              1��������Ч�� */
        unsigned int  gt_clk_apll2_stat  : 1;  /* bit[26-26]: APLL2�ſ��źš�
                                                              0��APLL2���ʱ���ſأ�
                                                              1��APLL2���ʱ�Ӳ��ſء����ȴ�PLL�ȶ���������ø�bit�� */
        unsigned int  reserved           : 5;  /* bit[27-31]: ������ */
    } reg;
} SOC_PMCTRL_APLL2CTRL1_STAT_UNION;
#endif
#define SOC_PMCTRL_APLL2CTRL1_STAT_apll2_fracdiv_stat_START  (0)
#define SOC_PMCTRL_APLL2CTRL1_STAT_apll2_fracdiv_stat_END    (23)
#define SOC_PMCTRL_APLL2CTRL1_STAT_apll2_int_mod_stat_START  (24)
#define SOC_PMCTRL_APLL2CTRL1_STAT_apll2_int_mod_stat_END    (24)
#define SOC_PMCTRL_APLL2CTRL1_STAT_apll2_cfg_vld_stat_START  (25)
#define SOC_PMCTRL_APLL2CTRL1_STAT_apll2_cfg_vld_stat_END    (25)
#define SOC_PMCTRL_APLL2CTRL1_STAT_gt_clk_apll2_stat_START   (26)
#define SOC_PMCTRL_APLL2CTRL1_STAT_gt_clk_apll2_stat_END     (26)


/*****************************************************************************
 �ṹ��    : SOC_PMCTRL_G3DCLKDIV_STAT_UNION
 �ṹ˵��  : G3DCLKDIV_STAT �Ĵ����ṹ���塣��ַƫ����:0x4AC����ֵ:0x00001F1F�����:32
 �Ĵ���˵��: G3D AXIʱ�ӷ�Ƶ״̬�Ĵ�����
*****************************************************************************/
#ifndef __SOC_H_FOR_ASM__
typedef union
{
    unsigned int      value;
    struct
    {
        unsigned int  g3da_clk_div0_stat : 8;  /* bit[0-7]  : G3D AXIʱ�ӷ�Ƶ��0����3bitΪPLLѡ��ѡ��PPLL0~4��APLL2����5bitΪ��Ƶϵ���� */
        unsigned int  g3da_clk_div1_stat : 8;  /* bit[8-15] : G3D AXIʱ�ӷ�Ƶ��1����3bitΪPLLѡ��ѡ��PPLL0~4��APLL2����5bitΪ��Ƶϵ���� */
        unsigned int  reserved           : 16; /* bit[16-31]: ������ */
    } reg;
} SOC_PMCTRL_G3DCLKDIV_STAT_UNION;
#endif
#define SOC_PMCTRL_G3DCLKDIV_STAT_g3da_clk_div0_stat_START  (0)
#define SOC_PMCTRL_G3DCLKDIV_STAT_g3da_clk_div0_stat_END    (7)
#define SOC_PMCTRL_G3DCLKDIV_STAT_g3da_clk_div1_stat_START  (8)
#define SOC_PMCTRL_G3DCLKDIV_STAT_g3da_clk_div1_stat_END    (15)






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

#endif /* end of soc_pmctrl_interface.h */
